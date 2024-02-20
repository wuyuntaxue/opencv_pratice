
set(DEMO_NAME "capture_start")

aux_source_directory(${PROJECT_SOURCE_DIR}/${DEMO_NAME}/ SRC_FILES)

add_executable(${DEMO_NAME} ${SRC_FILES})
target_link_libraries(${DEMO_NAME} PUBLIC -lopencv_core -lopencv_video -lopencv_videoio -lopencv_highgui)