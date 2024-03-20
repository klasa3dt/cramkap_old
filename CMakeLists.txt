cmake_minimum_required(VERSION 3.16)

project(cramkap)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CRAMKAP_SOURCES
src/server.css.cs.php.html.xaml.xml.xhtml.js.ts.jsx.tsx.svelte.scss.sass.lua.htm.c
src/client.cs.c.asm.obj.bin.out.in.cpp.c++.php.js.lua.css.sass.scss.xaml.xml.xht.htmx.html.xhtml.toml.json.jsx.tsx.ts.svelte.vue.asp.cshtml.html.lua.c
src/main.js.php.cpp.c
)

set(CRAMKAP_INCLUDE
include/
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${CRAMKAP_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CRAMKAP_INCLUDE})

include(Vendor.cmake)