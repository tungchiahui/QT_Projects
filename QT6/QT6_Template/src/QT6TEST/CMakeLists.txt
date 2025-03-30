# 定义包前缀变量
set(PREFIX "QT6TEST")
message(STATUS "it's ${PREFIX}:")

# 查找 src 目录及其子目录中的所有.c和.cpp 文件添加到列表(获取的是完整的文件绝对路径)
file(GLOB_RECURSE ${PREFIX}_SRC_LIST "${CMAKE_CURRENT_LIST_DIR}/src/*.c" "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
# 输出一下SRC目录
message(STATUS "${PREFIX}_SRC_LIST: ${${PREFIX}_SRC_LIST}")

# 查找 inc 目录及其子目录中的所有.h和.hpp 文件添加到列表(获取的是完整的文件绝对路径)
file(GLOB_RECURSE ${PREFIX}_HEADER_LIST "${CMAKE_CURRENT_LIST_DIR}/inc/*.h" "${CMAKE_CURRENT_LIST_DIR}/inc/*.hpp")
# 输出一下INC目录
message(STATUS "${PREFIX}_HEADER_LIST: ${${PREFIX}_HEADER_LIST}")



# 引用 Qt6 库（假设需要 Core、Gui、Widgets 模块）
find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL Tools REQUIRED)

# 设置 UIC 查找路径为 form 目录
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_LIST_DIR}/form")

# 查找 src 目录及其子目录中的所有.ui 文件添加到列表(获取的是完整的文件绝对路径)
file(GLOB ${PREFIX}_UI_FILES "${CMAKE_CURRENT_LIST_DIR}/form/*.ui")

# 生成 UI 头文件（自动生成 ui_*.h）
qt6_wrap_ui(${PREFIX}_UI_HEADERS ${${PREFIX}_UI_FILES})
# 查看.ui是否被转化
message(STATUS "UI Files: ${${PREFIX}_UI_FILES}")
message(STATUS "Generated UI Headers: ${${PREFIX}_UI_HEADERS}")


# 添加库 将${SRC_LIST}中的库全部创建为src_lib动态库
add_library(${PREFIX}_src_lib SHARED 
    ${${PREFIX}_SRC_LIST}
    ${${PREFIX}_UI_HEADERS}  # 必须包含生成的 UI 头文件
    )

# 使动态库能够正常找到他自己的头文件
# target_include_directories(${PREFIX}_src_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
# 安装头文件到 install 目录的 include 子目录中再寻找
install(FILES ${${PREFIX}_HEADER_LIST} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PREFIX})


# 引用第三方库(例如引用Eigen3矩阵库)
# 查找 库 的包
find_package(Eigen3 REQUIRED)
# 创建一个INTERFACE库(创建了一个不包含源代码的目标，专门用于传递编译选项、包含路径和链接库。)
add_library(${PREFIX}_eigen3_lib INTERFACE)
# 查找 库 头文件
target_include_directories(${PREFIX}_eigen3_lib INTERFACE ${EIGEN3_INCLUDE_DIRS})
# 将 库 链接给目标
target_link_libraries(${PREFIX}_src_lib PUBLIC ${PREFIX}_eigen3_lib)
# 提示是否找到 库
message(STATUS "Eigen3 include dirs: ${EIGEN3_INCLUDE_DIRS}")

# 引用 Qt6 库（假设需要 Core、Gui、Widgets 模块）
# 已经将该句移到上面，防止上面命令找不到
# find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL Tools REQUIRED)
# 创建唯一命名的 INTERFACE 库（例如前缀_qt6_lib）
add_library(${PREFIX}_qt6_lib INTERFACE)
# 链接 Qt6 库到 INTERFACE 目标（注意使用 Qt6:: 命名空间）
target_link_libraries(${PREFIX}_qt6_lib INTERFACE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
)
# 让动态库能够找到头文件（特别是 Qt6 生成的 `ui_*.h` 头文件）
target_include_directories(${PREFIX}_src_lib PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}  # Qt6 生成的 `ui_*.h` 头文件会放这里
)
# 将 Qt6 库链接到当前模块的动态库
target_link_libraries(${PREFIX}_src_lib PUBLIC ${PREFIX}_qt6_lib)
# 输出信息
message(STATUS "Qt6 library status:")
message(STATUS "> version: ${Qt6_VERSION}")