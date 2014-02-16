cmake_minimum_required(VERSION 2.8)

set(TARGET hello)
# プロジェクト名
project(${TARGET})

set(SRC_FILES hello.cpp)


# ODEパス
set(ODE_PATH /Users/xxx/work/ode-0.13)
# インクルードパス
include_directories(${ODE_PATH}/include)
# ライブラリパスの追加
link_directories(
  ${ODE_PATH}/ode/src/.libs
  ${ODE_PATH}/drawstuff/src/.libs
)

# マクロ設定 [-D]
#add_definitions(-DdDOUBLE)

# 実行ファイルとソースファイル群
add_executable(${TARGET} ${SRC_FILES})

# ライブラリ
if(APPLE)
  target_link_libraries(${TARGET} m ode drawstuff)
  target_link_libraries(${TARGET} "-framework OpenGL")
  target_link_libraries(${TARGET} "-framework GLUT")
elseif(UNIX)
  target_link_libraries(${TARGET} m ode drawstuff GLU GL)
endif()

