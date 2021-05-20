# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "test_action: 7 messages, 0 services")

set(MSG_I_FLAGS "-Itest_action:/home/yangzt/catkin_ws/devel/share/test_action/msg;-Iactionlib_msgs:/opt/ros/melodic/share/actionlib_msgs/cmake/../msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(test_action_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg" NAME_WE)
add_custom_target(_test_action_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test_action" "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg" "actionlib_msgs/GoalID:test_action/demoGoal:std_msgs/Header"
)

get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg" NAME_WE)
add_custom_target(_test_action_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test_action" "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg" ""
)

get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg" NAME_WE)
add_custom_target(_test_action_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test_action" "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg" ""
)

get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg" NAME_WE)
add_custom_target(_test_action_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test_action" "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg" "actionlib_msgs/GoalID:test_action/demoActionGoal:test_action/demoResult:actionlib_msgs/GoalStatus:std_msgs/Header:test_action/demoGoal:test_action/demoActionFeedback:test_action/demoFeedback:test_action/demoActionResult"
)

get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg" NAME_WE)
add_custom_target(_test_action_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test_action" "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg" "actionlib_msgs/GoalID:actionlib_msgs/GoalStatus:test_action/demoFeedback:std_msgs/Header"
)

get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg" NAME_WE)
add_custom_target(_test_action_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test_action" "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg" "actionlib_msgs/GoalID:actionlib_msgs/GoalStatus:test_action/demoResult:std_msgs/Header"
)

get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg" NAME_WE)
add_custom_target(_test_action_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test_action" "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action
)
_generate_msg_cpp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action
)
_generate_msg_cpp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action
)
_generate_msg_cpp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action
)
_generate_msg_cpp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action
)
_generate_msg_cpp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action
)
_generate_msg_cpp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action
)

### Generating Services

### Generating Module File
_generate_module_cpp(test_action
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(test_action_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(test_action_generate_messages test_action_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_cpp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_cpp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_cpp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg" NAME_WE)
add_dependencies(test_action_generate_messages_cpp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_cpp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_cpp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_cpp _test_action_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_action_gencpp)
add_dependencies(test_action_gencpp test_action_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_action_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action
)
_generate_msg_eus(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action
)
_generate_msg_eus(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action
)
_generate_msg_eus(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action
)
_generate_msg_eus(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action
)
_generate_msg_eus(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action
)
_generate_msg_eus(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action
)

### Generating Services

### Generating Module File
_generate_module_eus(test_action
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(test_action_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(test_action_generate_messages test_action_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_eus _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_eus _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_eus _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg" NAME_WE)
add_dependencies(test_action_generate_messages_eus _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_eus _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_eus _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_eus _test_action_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_action_geneus)
add_dependencies(test_action_geneus test_action_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_action_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action
)
_generate_msg_lisp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action
)
_generate_msg_lisp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action
)
_generate_msg_lisp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action
)
_generate_msg_lisp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action
)
_generate_msg_lisp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action
)
_generate_msg_lisp(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action
)

### Generating Services

### Generating Module File
_generate_module_lisp(test_action
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(test_action_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(test_action_generate_messages test_action_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_lisp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_lisp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_lisp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg" NAME_WE)
add_dependencies(test_action_generate_messages_lisp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_lisp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_lisp _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_lisp _test_action_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_action_genlisp)
add_dependencies(test_action_genlisp test_action_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_action_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action
)
_generate_msg_nodejs(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action
)
_generate_msg_nodejs(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action
)
_generate_msg_nodejs(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action
)
_generate_msg_nodejs(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action
)
_generate_msg_nodejs(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action
)
_generate_msg_nodejs(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action
)

### Generating Services

### Generating Module File
_generate_module_nodejs(test_action
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(test_action_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(test_action_generate_messages test_action_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_nodejs _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_nodejs _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_nodejs _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg" NAME_WE)
add_dependencies(test_action_generate_messages_nodejs _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_nodejs _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_nodejs _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_nodejs _test_action_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_action_gennodejs)
add_dependencies(test_action_gennodejs test_action_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_action_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action
)
_generate_msg_py(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action
)
_generate_msg_py(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action
)
_generate_msg_py(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action
)
_generate_msg_py(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action
)
_generate_msg_py(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/melodic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action
)
_generate_msg_py(test_action
  "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action
)

### Generating Services

### Generating Module File
_generate_module_py(test_action
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(test_action_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(test_action_generate_messages test_action_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_py _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_py _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoGoal.msg" NAME_WE)
add_dependencies(test_action_generate_messages_py _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoAction.msg" NAME_WE)
add_dependencies(test_action_generate_messages_py _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_py _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoActionResult.msg" NAME_WE)
add_dependencies(test_action_generate_messages_py _test_action_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/yangzt/catkin_ws/devel/share/test_action/msg/demoFeedback.msg" NAME_WE)
add_dependencies(test_action_generate_messages_py _test_action_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_action_genpy)
add_dependencies(test_action_genpy test_action_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_action_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_action
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_cpp)
  add_dependencies(test_action_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_action
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_eus)
  add_dependencies(test_action_generate_messages_eus actionlib_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_action
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_lisp)
  add_dependencies(test_action_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_action
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_nodejs)
  add_dependencies(test_action_generate_messages_nodejs actionlib_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_action
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_py)
  add_dependencies(test_action_generate_messages_py actionlib_msgs_generate_messages_py)
endif()
