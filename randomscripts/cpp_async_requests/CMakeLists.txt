cmake_minimum_required(VERSION "3.20.4")

project("CppAsyncRequest")

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG f4622efcb59d84071ae11404ae61bd821c1c344b) # the commit hash v1.6.2
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.4)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(NAME_SRC
	main.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ${NAME_SRC})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
