target_sources(jadxjni
  INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/ArgType.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/PrimitiveType.hpp"
  INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/ArgType.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PrimitiveType.cpp"
)
