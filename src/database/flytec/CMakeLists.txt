include_directories(${CMAKE_SOURCE_DIR}/src/common/container
                    ${CMAKE_SOURCE_DIR}/src/common/qextserialport
                    ${CMAKE_SOURCE_DIR}/src/common/utils
                    ${CMAKE_SOURCE_DIR}/src/database
                    ${QT_INCLUDES})

set(dbflytec_SRCS Flytec.cpp
                  Protocol.cpp
                  Protocol5020.cpp
                  Protocol6015.cpp
                  Device.cpp)

add_library(dbflytec ${dbflytec_SRCS})
