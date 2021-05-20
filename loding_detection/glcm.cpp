#include "glcm.h"

//将灰度图中的所有像素值量级化，可以被量化为4/8/16个等级
void GLCM::GrayMagnitude(Mat src, Mat& dst, GrayLevel level)
{
    Mat tmp;
    src.copyTo(tmp);
    if(tmp.channels() == 3)
        cvtColor(tmp, tmp, CV_BGR2GRAY);

    // 直方图均衡化
    equalizeHist(tmp, tmp);

    for(int j = 0; j < tmp.rows; j++)
    {
        const uchar* current = tmp.ptr<uchar>(j);
        uchar* output = dst.ptr<uchar>(j);

        for(int i = 0; i < tmp.cols; i++)
        {
            switch(level)
            {
            case GRAY_4:
                output[i] = cv::saturate_cast<uchar>(current[i] / 64);
                break;
            case GRAY_8:
                output[i] = cv::saturate_cast<uchar>(current[i] / 32);
                break;
            case GRAY_16:
                output[i] = cv::saturate_cast<uchar>(current[i] / 16);
                break;
            default:
                cout<<"ERROR in GrayMagnitude(): No Such GrayLevel."<<endl;
                return ;
            }
        }
    }
}

/*
 计算一个矩阵窗口中，按照某个方向统计的灰度共生矩阵
 int src_i:  矩阵窗口中心点的行值
 int src_j:  矩阵窗口中心点的列值
 int size:  窗口尺寸（仅支持5*5, 7*7）*/
void GLCM::CalcuOneGLCM(Mat src, Mat& dst, int src_i, int src_j, int size, GrayLevel level, GrayDirection direct)
{
    // 灰度共生矩阵
    Mat glcm;

    // 窗口矩阵
    Mat srcCut;

    // 原图像尺寸判断
    if(src.cols <= 0 || src.rows <= 0)
    {
        cout<<"ERROR in CalcuOneGLCM(): source Mat's size is smaller than 0."<<endl;
        return ;
    }

    // 强制将尺寸转为奇数
    size = size / 2 * 2 + 1;

    // 边缘部分创建窗口矩阵
    if(src_i + (size/2) + 1 > src.rows
            || src_j + (size/2) + 1 > src.cols
            || src_i < (size/2)
            || src_j < (size/2))
    {
        size = 3;
        if(src_i <= size/2)
        {
            if(src_j <= size/2)
                srcCut = Mat(src, Range(0, 3), Range(0, 3));
            else if(src_j + (size/2) + 1 > src.cols)
                srcCut = Mat(src, Range(0, 3), Range(src.cols - 3, src.cols));
            else
                srcCut = Mat(src, Range(0, 3), Range(src_j - size/2, src_j + size/2 + 1));
        }
        else if(src_i >= src.rows - size/2)
        {
            if(src_j <= size/2)
                srcCut = Mat(src, Range(src.rows - 3, src.rows), Range(0, 3));
            else if(src_j + (size/2) + 1 > src.cols)
                srcCut = Mat(src, Range(src.rows - 3, src.rows), Range(src.cols - 3, src.cols));
            else
                srcCut = Mat(src, Range(src.rows - 3, src.rows), Range(src_j - size/2, src_j + size/2 + 1));
        }
        else if(src_j <= size/2)
        {
            if(src_i <= size/2)
                srcCut = Mat(src, Range(0, 3), Range(0, 3));
            else if(src_i + (size/2) + 1 > src.rows)
                srcCut = Mat(src, Range(src.rows - 3, src.rows), Range(0, 3));
            else
                srcCut = Mat(src, Range(src_i - size/2, src_i + size/2 + 1), Range(0, 3));
        }
        else if(src_j >= src.cols - size/2)
        {
            if(src_i <= size/2)
                srcCut = Mat(src, Range(0, 3), Range(src.cols - 3, src.cols));
            else if(src_i + (size/2) + 1 > src.rows)
                srcCut = Mat(src, Range(src.rows - 3, src.rows), Range(src.cols - 3, src.cols));
            else
                srcCut = Mat(src, Range(src_i - size/2, src_i + size/2 + 1), Range(src.cols - 3, src.cols));
        }
        else
            srcCut = Mat(src, Range(src_i - size/2, src_i + size/2 + 1), Range(src_j - size/2, src_j + size/2 + 1));
    }
    else
        srcCut = Mat(src, Range(src_i - size/2, src_i + size/2 + 1), Range(src_j - size/2, src_j + size/2 + 1));

    // 根据灰度等级初始化灰度共生矩阵
    switch(level)
    {
    case GRAY_4:
    {
        glcm = Mat_<uchar>(4, 4);
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                glcm.at<uchar>(j, i) = 0;
        break;
    }
    case GRAY_8:
    {
        glcm = Mat_<uchar>(8, 8);
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                glcm.at<uchar>(j, i) = 0;
        break;
    }
    case GRAY_16:
    {
        glcm = Mat_<uchar>(16, 16);
        for(int i = 0; i < 16; i++)
            for(int j = 0; j < 16; j++)
                glcm.at<uchar>(j, i) = 0;
        break;
    }
    default:
        cout<<"ERROR in CalcuOneGLCM(): No Such Gray Level."<<endl;
        break;
    }

    // 根据统计方向填充灰度共生矩阵
    switch(direct)
    {
    case DIR_0:
        for(int i = 0; i < srcCut.rows; i++)
            for(int j = 0; j < srcCut.cols - 1; j++)
                glcm.at<uchar>(srcCut.at<uchar>(j, i), srcCut.at<uchar>(j+1, i))++;
        break;
    case DIR_45:
        for(int i = 0; i < srcCut.rows - 1; i++)
            for(int j = 0; j < srcCut.cols - 1; j++)
                glcm.at<uchar>(srcCut.at<uchar>(j, i), srcCut.at<uchar>(j+1, i+1))++;
        break;
    case DIR_90:
        for(int i = 0; i < srcCut.rows - 1; i++)
            for(int j = 0; j < srcCut.cols; j++)
                glcm.at<uchar>(srcCut.at<uchar>(j, i), srcCut.at<uchar>(j, i+1))++;
        break;
    case DIR_135:
        for(int i = 1; i < srcCut.rows; i++)
            for(int j = 0; j < srcCut.cols - 1; j++)
                glcm.at<uchar>(srcCut.at<uchar>(j, i), srcCut.at<uchar>(j+1, i-1))++;
        break;
    default:
        cout<<"ERROR in CalcuOneGLCM(): No such Direct."<<endl;
        break;
    }
    glcm.copyTo(dst);
}

 //说明：矩阵的归一化，将矩阵所有元素与矩阵中所有元素之和作除运算，得到概率矩阵
void GLCM::NormalizeMat(Mat src, Mat& dst)
{
    Mat tmp;
    src.convertTo(tmp, CV_32F);

    float sum = 0;
    for(int i = 0; i < tmp.rows; i++)
        for(int j = 0; j < tmp.cols; j++)
            sum += tmp.at<float>(j, i);
    if(sum == 0)    sum = 1;

    for(int i = 0; i < tmp.rows; i++)
        for(int j = 0; j < tmp.cols; j++)
            tmp.at<float>(j, i) /= sum;

    tmp.copyTo(dst);
}

 //说明：计算单个窗口矩阵的图像纹理特征值，包括能量、对比度、相关度、熵
void GLCM::CalcuOneTextureEValue(Mat src, TextureEValues& EValue, bool ToCheckMat)
{
    if(ToCheckMat)
    {
        float sum = 0;
        for(int i = 0; i < src.rows; i++)
            for(int j = 0; j < src.cols; j++)
                sum += src.at<float>(j, i);
        if(sum < 0.99 || sum > 1.01)
        {
            cout<<"ERROR in CalcuOneTextureEValue(): Sum of the Mat is not equal to 1.00."<<endl;
            return ;
        }
    }

 //   EValue.contrast = 0;
    EValue.energy = 0;
//    EValue.entropy = 0;
//    EValue.homogenity = 0;

    for(int i = 0; i < src.rows; i+=5)
        for(int j = 0; j < src.cols; j+=5)
        {
            EValue.energy += powf(src.at<float>(j, i), 2);
//            EValue.contrast += (powf((i - j), 2) * src.at<float>(j, i) );
//            EValue.homogenity += (src.at<float>(j, i) / (1 + fabs((float)(i - j))) );
//            if(src.at<float>(j, i) != 0)
//                EValue.entropy -= (src.at<float>(j, i) * log10(src.at<float>(j, i)) );
        }
}
 //计算全图的图像纹理特征值，包括能量、对比度、相关度、熵
void GLCM::CalcuTextureEValue(Mat src, TextureEValues& EValue, int size, GrayLevel level)
{
    // 原图像的灰度图
    Mat imgGray;

    // 窗口矩阵
    Mat glcm_win;

    // 归一化后的概率矩阵
    Mat glcm_norm;

    // 纹理特征值缓存变量
    TextureEValues EValue_temp;

    // 初始化目标纹理特征值
    EValue.energy = 0;
    //EValue.contrast = 0;  EValue.entropy = 0; EValue.homogenity = 0;

    // 检查输入图像是否为单通道图像，如果不是，则转换其格式
    if(src.channels() != 1)
        cvtColor(src, imgGray, CV_BGR2GRAY);
    else
        src.copyTo(imgGray);

    for(int i = 0; i < imgGray.rows; i+=5)
    {
        for(int j = 0; j < imgGray.cols; j+=5)
        {
            // 计算所有统计方向的灰度共生矩阵与对应的特征值，并累加至缓存变量中
            float energy, contrast, homogenity, entropy;
            energy = contrast = homogenity = entropy = 0;

            CalcuOneGLCM(imgGray, glcm_win, i, j, size, level, DIR_0);
            NormalizeMat(glcm_win, glcm_norm);
            CalcuOneTextureEValue(glcm_norm, EValue_temp, false);
            energy += EValue_temp.energy;
//            contrast += EValue_temp.contrast;
//            homogenity += EValue_temp.homogenity; entropy += EValue_temp.entropy;

            CalcuOneGLCM(imgGray, glcm_win, i, j, size, level, DIR_45);
            NormalizeMat(glcm_win, glcm_norm);
            CalcuOneTextureEValue(glcm_norm, EValue_temp, false);
            energy += EValue_temp.energy;
//            contrast += EValue_temp.contrast;
//            homogenity += EValue_temp.homogenity; entropy += EValue_temp.entropy;

            CalcuOneGLCM(imgGray, glcm_win, i, j, size, level, DIR_90);
            NormalizeMat(glcm_win, glcm_norm);
            CalcuOneTextureEValue(glcm_norm, EValue_temp, false);
            energy += EValue_temp.energy;
//            contrast += EValue_temp.contrast;
//            homogenity += EValue_temp.homogenity; entropy += EValue_temp.entropy;

            CalcuOneGLCM(imgGray, glcm_win, i, j, size, level, DIR_135);
            NormalizeMat(glcm_win, glcm_norm);
            CalcuOneTextureEValue(glcm_norm, EValue_temp, false);
            energy += EValue_temp.energy;
//            contrast += EValue_temp.contrast;
//            homogenity += EValue_temp.homogenity; entropy += EValue_temp.entropy;

            // 将所有方向计算得到的特征值平均化，得到的值即可消除统计方向影响
            energy /= 4; contrast /= 4;
            homogenity /= 4; entropy /= 4;

            // 累加当前单个窗口的纹理特征值，作为整个图像的纹理特征值
            EValue.energy += energy;

//            EValue.contrast += contrast;
//            EValue.entropy += entropy;
//            EValue.homogenity += homogenity;
        }
    }
    EValue.energy =  EValue.energy/(glcm_norm.cols*glcm_norm.rows);
//    EValue.contrast = EValue.contrast/(glcm_norm.cols*glcm_norm.rows);
//    EValue.entropy = EValue.entropy/(glcm_norm.cols*glcm_norm.rows);
//    EValue.homogenity = EValue.homogenity/(glcm_norm.cols*glcm_norm.rows);
}

/*===================================================================
 *计算整幅图像的纹理特征，并将结果输出到相应矩阵中
 *   Mat& imgEnergy:  目标能量矩阵
 *   Mat& imgContrast:  目标对比度矩阵
 *   Mat& imgHomogenity:  目标相关度矩阵
 *   Mat& imgEntropy:  目标熵矩阵
=====================================================================
*/
void GLCM::CalcuTextureImages(Mat src, Mat& imgEnergy, Mat& imgContrast, Mat& imgHomogenity, Mat& imgEntropy,
                        int size, GrayLevel level, bool ToAdjustImg)
{
    // 窗口矩阵
    Mat glcm_win;

    // 归一化后的概率矩阵
    Mat glcm_norm;

    // 纹理特征值缓存变量
    TextureEValues EValue;

    imgEnergy.create(src.size(), CV_32FC1);
    imgContrast.create(src.size(), CV_32FC1);
    imgHomogenity.create(src.size(), CV_32FC1);
    imgEntropy.create(src.size(), CV_32FC1);

    for(int i = 0; i < src.rows; i++)
    {
        float* energyData = imgEnergy.ptr<float>(i);
        float* contrastData = imgContrast.ptr<float>(i);
        float* homogenityData = imgHomogenity.ptr<float>(i);
        float* entropyData = imgEntropy.ptr<float>(i);

        for(int j = 0; j < src.cols; j++)
        {
            // 计算所有统计方向的灰度共生矩阵与对应的特征值，并累加至缓存变量中
            float energy, contrast, homogenity, entropy;
            energy = contrast = homogenity = entropy = 0;

            CalcuOneGLCM(src, glcm_win, i, j, size, level, DIR_0);
            NormalizeMat(glcm_win, glcm_norm);
            CalcuOneTextureEValue(glcm_norm, EValue, false);
            energy += EValue.energy;
//            contrast += EValue.contrast;
//            homogenity += EValue.homogenity; entropy += EValue.entropy;

            CalcuOneGLCM(src, glcm_win, i, j, size, level, DIR_45);
            NormalizeMat(glcm_win, glcm_norm);
            CalcuOneTextureEValue(glcm_norm, EValue, false);
            energy += EValue.energy;
//            contrast += EValue.contrast;
//            homogenity += EValue.homogenity; entropy += EValue.entropy;

            CalcuOneGLCM(src, glcm_win, i, j, size, level, DIR_90);
            NormalizeMat(glcm_win, glcm_norm);
            CalcuOneTextureEValue(glcm_norm, EValue, false);
            energy += EValue.energy;
//            contrast += EValue.contrast;
//            homogenity += EValue.homogenity; entropy += EValue.entropy;

            CalcuOneGLCM(src, glcm_win, i, j, size, level, DIR_135);
            NormalizeMat(glcm_win, glcm_norm);
            CalcuOneTextureEValue(glcm_norm, EValue, false);
            energy += EValue.energy;
//            contrast += EValue.contrast;
//            homogenity += EValue.homogenity; entropy += EValue.entropy;

            // 将所有方向计算得到的特征值平均化，得到的值即可消除统计方向影响
            energy /= 4; contrast /= 4;
            homogenity /= 4; entropy /= 4;

            energyData[j] = energy;
            contrastData[j] = contrast;
            homogenityData[j] = homogenity;
            entropyData[j] = entropy;
        }
    }
    // 调整输出特征图像，类型由CV_32FC1改为CV_8UC1，取值范围0--255
    if(ToAdjustImg)
    {
        cv::normalize(imgEnergy, imgEnergy, 0, 255, NORM_MINMAX);
        cv::normalize(imgContrast, imgContrast, 0, 255, NORM_MINMAX);
        cv::normalize(imgEntropy, imgEntropy, 0, 255, NORM_MINMAX);
        cv::normalize(imgHomogenity, imgHomogenity, 0, 255, NORM_MINMAX);
        imgEnergy.convertTo(imgEnergy, CV_8UC1);
        imgContrast.convertTo(imgContrast, CV_8UC1);
        imgEntropy.convertTo(imgEntropy, CV_8UC1);
        imgHomogenity.convertTo(imgHomogenity, CV_8UC1);
    }
}
