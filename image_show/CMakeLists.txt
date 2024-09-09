
set(DEMO_NAME "image_show")

aux_source_directory(${PROJECT_SOURCE_DIR}/${DEMO_NAME}/ SRC_FILES)

add_executable(${DEMO_NAME} ${SRC_FILES})
target_link_libraries(${DEMO_NAME} PUBLIC -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc)