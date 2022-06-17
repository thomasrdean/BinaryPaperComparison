# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(BinaryInANTLR)

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

# compiler must be 11 or 14
SET (CMAKE_CXX_STANDARD 17)

#################### ANTLR SETUP##################################
# set variable pointing to the antlr tool for C++
set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/../antlr4Complete/antlr-4.10.1-complete.jar)
# set variable pointing to the antlr runtime forC++
set(ANTLR4CPP_RUNTIME ${PROJECT_SOURCE_DIR}/../antlr4cpp/)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
include_directories(${ANTLR4CPP_INCLUDE_DIRS})
link_directories(${ANTLR4CPP_LIB_DIRS})
##################################################################

antlr4cpp_process_grammar(ARP
  ${PROJECT_SOURCE_DIR}/grammars/ARP.g4)
antlr4cpp_process_grammar(DNS
  ${PROJECT_SOURCE_DIR}/grammars/DNS.g4)

# add generated grammar to demo binary target
add_executable(parser 
      ${moe_generated_files}
      ${antlr4cpp_src_files_ARP}
      ${antlr4cpp_src_files_DNS}
      ${PROJECT_SOURCE_DIR}/pmain.cpp
      ${PROJECT_SOURCE_DIR}/ByteInputStream.cpp
)
target_link_libraries(parser antlr4-runtime)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/build/)

find_library(LIBPCAP pcap)
target_link_libraries(parser ${LIBPCAP})
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
