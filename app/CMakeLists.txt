set(EXE_CLIENT_SOURCES
    # "test.cc"
    # "main.cc"
    "SimpleClient.cc")

set(EXE_SERVER_SOURCES
    "SimpleServer.cc")

add_executable(${EXECUTABLE_CLIENT_NAME} ${EXE_CLIENT_SOURCES}) 
add_executable(${EXECUTABLE_SERVER_NAME} ${EXE_SERVER_SOURCES})


target_link_libraries(${EXECUTABLE_CLIENT_NAME} PUBLIC 
    ${LIBRARY_NAME})
target_link_libraries(${EXECUTABLE_SERVER_NAME} PUBLIC ${LIBRARY_NAME})
