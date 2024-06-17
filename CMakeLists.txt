cmake_minimum_required(VERSION 3.7...3.16 FATAL_ERROR)

set(CURL_DIR "D:/software/CURL")

include_directories(${CURL_DIR}/include)

link_directories(${CURL_DIR}/lib)

add_executable(qchat main.cpp)

target_link_libraries(qchat D:/software/CURL/lib/libcurl_imp.lib)

target_compile_definitions(qchat PRIVATE BUILD_LIBCURL)
