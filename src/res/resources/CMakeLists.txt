message( "============ ${CURRENT_FOLDER}" )
STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
message( "name =" ${CURRENT_FOLDER} )
project( ${CURRENT_FOLDER} VERSION 0.1 LANGUAGES CXX )
message( "============ ${CURRENT_FOLDER}" )

execute_process(
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/test.jpg" "${EXECUTABLE_OUTPUT_PATH}/"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/test2.jpg" "${EXECUTABLE_OUTPUT_PATH}/"
)
