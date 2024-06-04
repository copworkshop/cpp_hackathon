
find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

# Proto 

set(PROTO_FILES
    proto/inventory.proto
)

add_library(PW_GRPC_PROTO ${PROTO_FILES})
target_link_libraries(PW_GRPC_PROTO
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
target_include_directories(PW_GRPC_PROTO PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET PW_GRPC_PROTO LANGUAGE cpp)
protobuf_generate(TARGET PW_GRPC_PROTO LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

# Service

add_library(PW_GRPC_SERVICE)

target_sources(PW_GRPC_SERVICE
    PRIVATE
        PWGRPCService.cpp
        PWGRPCService.h
)

target_link_libraries(PW_GRPC_SERVICE
    PUBLIC
        gRPC::grpc
        gRPC::grpc++
        ${PROTO_SRCS}
        ${GRPC_SRCS}
)

target_include_directories(PW_GRPC_SERVICE 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Server
add_executable(server
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)
target_link_libraries(server
    PW_GRPC_SERVICE
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)

# Client
add_executable(client
    ${CMAKE_CURRENT_SOURCE_DIR}/Client.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)
target_link_libraries(client
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)