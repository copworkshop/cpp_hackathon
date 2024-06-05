
find_package(nlohmann_json REQUIRED)
find_package(MySQL REQUIRED)

add_library(PW_Server)
add_library(PW::SERVER ALIAS PW_Server)

target_sources(PW_Server
    PRIVATE
        PWInventory.cpp
        PWInventory.h
        PWServer.cpp
        PWServer.h
        inventory.json
        db.json
)

target_link_libraries(PW_Server
    PUBLIC
        PW::COMMON
        nlohmann_json::nlohmann_json
        MySQL::MySQL
)

target_include_directories(PW_Server 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

add_executable(PWServerExe)

target_sources(PWServerExe
    PRIVATE
        main.cpp
)

target_link_libraries(PWServerExe
    PRIVATE
        PW::SERVER
)

install(TARGETS PWServerExe
    RUNTIME DESTINATION .
)

install(FILES inventory.json
    db.json
    DESTINATION .
)
