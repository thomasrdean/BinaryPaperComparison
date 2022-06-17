#inputs:
# REQURED:
#   ANTLR4CPP_JAR_LOCATION - location of the antlr C++ generator jar
#   ANTLR4CPP_RUUNTIME - location of the antlr C++ runtime folder (assumes a subcirectory usr with lib and include
# Optional
#   ANTLR4CPP_GENERATED_SRC_DIR - location where antler generated files will be located

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.2)

# only JRE required
FIND_PACKAGE(Java COMPONENTS Runtime REQUIRED)

if(NOT ANTLR4CPP_JAR_LOCATION)
  message(FATAL_ERROR "Must specify Location of ANTLR jar file")
endif()

if(NOT ANTLR4CPP_RUNTIME)
  message(FATAL_ERROR "Must specify Location of ANTLR C++ runtime")
endif()

if(NOT EXISTS "${ANTLR4CPP_JAR_LOCATION}")
  message(FATAL_ERROR "Unable to find antlr tool. ANTLR4CPP_JAR_LOCATION:${ANTLR4CPP_JAR_LOCATION}")
endif()

if(NOT EXISTS "${ANTLR4CPP_RUNTIME}")
  message(FATAL_ERROR "Unable to find antlr runtime. ANTLR4CPP_RUNTIME:${ANTLR4CPP_RUNTIME}")
endif()

# default path for source files
if (NOT ANTLR4CPP_GENERATED_SRC_DIR)
  set(ANTLR4CPP_GENERATED_SRC_DIR ${CMAKE_BINARY_DIR}/antlr4cpp_generated_src)
endif()


set(ANTLR4CPP_INCLUDE_DIRS ${ANTLR4CPP_RUNTIME}/runtime/src)
set(ANTLR4CPP_LIB_DIRS "${ANTLR4CPP_RUNTIME}/dist")

############ Generate runtime #################
# macro to add dependencies to target
#
# Param 1 namespace (postfix for dependencies)
# Param 3 Parser File (full path)
#
# output
#
# antlr4cpp_src_files_{namespace} - src files for add_executable
# antlr4cpp_include_dirs_{namespace} - include dir for generated headers

macro(antlr4cpp_process_grammar
    antlr4cpp_project_namespace
    antlr4cpp_grammar_parser)

    if(EXISTS "${ANTLR4CPP_JAR_LOCATION}")
	message(STATUS "Found antlr tool: ${ANTLR4CPP_JAR_LOCATION}")
    else()
	message(FATAL_ERROR "Unable to find antlr tool. ANTLR4CPP_JAR_LOCATION:${ANTLR4CPP_JAR_LOCATION}")
    endif()

    # directory for .h files
    set(antlr4cpp_include_dirs_${antlr4cpp_project_namespace} ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace})
    # build list of cpp files that will be generated
    list(APPEND antlr4cpp_src_files_${antlr4cpp_project_namespace} ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Lexer.cpp)
    list(APPEND antlr4cpp_src_files_${antlr4cpp_project_namespace} ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Parser.cpp)
    list(APPEND antlr4cpp_src_files_${antlr4cpp_project_namespace} ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Listener.cpp)
    list(APPEND antlr4cpp_src_files_${antlr4cpp_project_namespace} ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}BaseListener.cpp)
    list(APPEND antlr4cpp_src_files_${antlr4cpp_project_namespace} ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Visitor.cpp)
    list(APPEND antlr4cpp_src_files_${antlr4cpp_project_namespace} ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}BaseVisitor.cpp)


    add_custom_command(
	OUTPUT
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Lexer.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Parser.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Listener.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}BaseListener.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Visitor.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}BaseVisitor.cpp
	    
	COMMAND
	    "${Java_JAVA_EXECUTABLE}" -jar "${ANTLR4CPP_JAR_LOCATION}" -Werror -Dlanguage=Cpp -listener -visitor -o ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace} -package ${antlr4cpp_project_namespace} ${antlr4cpp_grammar_parser}
	DEPENDS ${antlr4cpp_grammar_lexer} ${antlr4cpp_grammar_parser}
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
	COMMENT "Generating ${antlr4cpp_project_namespace} Parser Classes"
    )

    add_custom_target(${antlr4cpp_project_namespace} DEPENDS
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Lexer.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Parser.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Listener.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}BaseListener.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}Visitor.cpp
	    ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_project_namespace}BaseVisitor.cpp
    )


    message(STATUS "Antlr4Cpp  ${antlr4cpp_project_namespace} Generated: ${generated_files}")

    # export generated include directory
    message(STATUS "Antlr4Cpp ${antlr4cpp_project_namespace} include: ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}")

endmacro()
