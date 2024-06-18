cmake_minimum_required(VERSION 3.28)
project(ForExam C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 17)


add_executable(ForExam_merge3 merge3.c)
add_executable(dequeue_reverse dequeue_reverse.c)
add_executable(file_reverse file_reverse.c)
add_executable(transpose_fromFile transpose_fromFile.c)
add_executable(list_comparison list_comparison.c)
add_executable(quick_hoare_nonrecursive quick_hoare_nonrecursive.c)
add_executable(bool bool.c
        test.cpp
        test.h)
add_executable(queue_on_stacks queue_on_stacks.c)
add_executable(list_lambda list_lambda.cpp)
add_executable(hoare quich_hoare.c)
