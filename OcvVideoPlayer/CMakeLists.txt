cmake_minimum_required(VERSION 3.0)
set( CMAKE_VERBOSE_MAKEFILE ON )
execute_process(COMMAND basename ${CMAKE_CURRENT_SOURCE_DIR} 
                OUTPUT_VARIABLE WD
                OUTPUT_STRIP_TRAILING_WHITESPACE
                )
set( PROJECT "${WD}" )

project(${PROJECT})

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

ci_make_app(
	APP_NAME	"${PROJECT}"
	CINDER_PATH ${CINDER_PATH}
	#SOURCES		${APP_PATH}/src/toolsApp.cpp
	SOURCES		${APP_PATH}/src/${PROJECT}App.cpp
    #SOURCES		${APP_PATH}/src/ParticleSystem.cpp
    #SOURCES		${APP_PATH}/src/Particle.cpp
    INCLUDES    ${APP_PATH}/include
    INCLUDES    ${APP_PATH}/src

)
