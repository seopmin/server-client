set(EXE_SOURCES
    # "main.cc"
    "SimpleClient.cc")

add_executable(${EXECUTABLE_NAME} ${EXE_SOURCES}) 
add_executable(server SimpleServer.cc)


target_link_libraries(${EXECUTABLE_NAME} PUBLIC 
    ${LIBRARY_NAME})
target_link_libraries(server PUBLIC ${LIBRARY_NAME})
