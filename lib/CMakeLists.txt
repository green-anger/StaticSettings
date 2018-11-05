set( lib static_settings )

set( CMAKE_INCLUDE_CURRENT_DIR ON )

set( HEADERS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" )

set( HDRS
    ${HEADERS_ROOT}/StaticSettings.hpp
    ${HEADERS_ROOT}/TypeRegister.hpp
)

# include_directories(
    # ${HEADERS_ROOT}
    # ${Boost_INCLUDE_DIRS}
# )

add_library( ${lib} INTERFACE )
# set_target_properties( ${lib} PROPERTIES LINKER_LANGUAGE CXX )

target_include_directories( ${lib} INTERFACE
    ${HEADERS_ROOT}
)
