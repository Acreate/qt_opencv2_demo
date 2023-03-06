
message("============ ${CURRENT_FOLDER}")
STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
message("name =" ${CURRENT_FOLDER})
project(${CURRENT_FOLDER}  VERSION 0.1 LANGUAGES CXX)
message("============ ${CURRENT_FOLDER}")


# 当前目录下也有代码
FILE(GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h" )
# FILE(GLOB TS_FILES  "*.ts")
# FILE(GLOB UI_FILES  "*.ui")
# list(APPEND SRC_LIST ${TS_FILES})
# list(APPEND SRC_LIST ${UI_FILES})

add_library(${PROJECT_NAME} SHARED
	${SRC_LIST}
)
target_link_libraries(
	${PROJECT_NAME} 
PRIVATE 
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Core
	${OpenCV_LIBS}
)

STRING( SUBSTRING "${PROJECT_NAME}" 0 1 exportFileStartName )
STRING( SUBSTRING "${PROJECT_NAME}" 1 -1 exportFileName )
STRING( TOUPPER ${exportFileStartName} exportFileStartName )
SET( exportFileName ${CMAKE_CURRENT_SOURCE_DIR}/${exportFileStartName}${exportFileName}_export.h )
GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
	EXPORT_FILE_NAME
	${exportFileName}
)
TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
