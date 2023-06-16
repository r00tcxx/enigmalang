function(get_version_info major minor build commit)
  # 使用一条 git 命令获取标签、commit 数量和哈希
  execute_process(
    COMMAND git describe --tags --long --always
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_DESCRIBE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )

  # 如果没有 git 信息，设置所有值为 0
  if(NOT GIT_DESCRIBE)
    set(${major} 0 PARENT_SCOPE)
    set(${minor} 0 PARENT_SCOPE)
    set(${build} 0 PARENT_SCOPE)
    set(${commit} 0 PARENT_SCOPE)
  else()
    # 使用正则表达式从 git 输出中提取 MAJOR、MINOR、BUILD 和 COMMIT
    string(REGEX MATCH "([0-9]+)\\.([0-9]+)-([0-9]+)-g([0-9a-f]+)" VERSION_MATCHES ${GIT_DESCRIBE})
    set(${major} ${CMAKE_MATCH_1} PARENT_SCOPE)
    set(${minor} ${CMAKE_MATCH_2} PARENT_SCOPE)
    set(${build} ${CMAKE_MATCH_3} PARENT_SCOPE)
    set(${commit} ${CMAKE_MATCH_4} PARENT_SCOPE)
  endif()
endfunction()