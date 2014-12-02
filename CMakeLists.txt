cmake_minimum_required(VERSION 2.8.3)
project(librms)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)

###################################################
## Declare things to be passed to other projects ##
###################################################

## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES rms mysqlclient
)

###########
## Build ##
###########

## Specify additional locations of header files
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(LIBRMS_SOURCE
  src/rms.cpp
  src/study.cpp
  src/condition.cpp
  src/log.cpp
  src/slot.cpp
  src/appointment.cpp
)

## Declare a cpp library
add_library(rms ${LIBRMS_SOURCE})

## Specify libraries to link a library or executable target against
target_link_libraries(rms
  ${catkin_LIBRARIES}
  mysqlclient
)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS rms
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

## Copy header files
install(DIRECTORY include/rms/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)

