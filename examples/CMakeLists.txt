set( exe simple )

set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )

find_package( Boost 1.39.0 REQUIRED )

set( ROOT "${CMAKE_CURRENT_SOURCE_DIR}" )

set( HDRS
    ${ROOT}/DeclareTypes.h
    ${ROOT}/MoreProperty.h
    ${ROOT}/Property.h
    ${ROOT}/ThreadSafePrinter.hpp
    ${ROOT}/Worker.h
)

set ( SRCS
    ${ROOT}/main.cpp
    ${ROOT}/Worker.cpp
)

include_directories(
    ${ROOT}
    ${Boost_INCLUDE_DIRS}
)

add_executable( ${exe} ${SRCS} ${HDRS} )

target_link_libraries( ${exe} static_settings )
