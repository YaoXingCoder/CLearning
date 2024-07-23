/* 
Date:2024.7.11
Title:退出处理函数atexit()和onexit()
Author:JiaZiChunQiu
Content:
return 0 本质也会执行exit(0);
return 1 则传入1，同样执行exit(1)
 */

#include <my_header.h>
// atexit()
#include <stdlib.h>
// error
#include <error.h>
#include <errno.h>
// _exit()
#include <unistd.h>

void exitFunc1(void) {
    printf("I'm going to die1\n"); // 先执行退出处理函数->刷新缓冲区->执行_exit()
}
void exitFunc2(void) {
    printf("I'm going to die2\n"); // 先执行退出处理函数->刷新缓冲区->执行_exit()
}
void exitFunc3(void) {
    printf("I'm going to die3\n"); // 先执行退出处理函数->刷新缓冲区->执行_exit()
}
void onexitFunc1(int exitStatus, void* arg) {
    printf("on_eixt_function called: status = %d, arg = %ld\n", exitStatus,(long)arg);
}
void onexitFunc2(int exitStatus, void* arg) {
    printf("on_eixt_function called: status = %d, arg = %ld\n", exitStatus, (long)arg);
}

int main(int argc, char* argv[]) {
    if(on_exit(onexitFunc1,(void*) 10) != 0) error(1, errno, "on_exit onexitFunc1");
    if(atexit(exitFunc1) != 0) error(1, errno, "atexit exitFunc1");
    if(atexit(exitFunc2) != 0) error(1, errno, "atexit exitFunc2");
    if(atexit(exitFunc3) != 0) error(1, errno, "atexit exitFunc3");
    if(on_exit(onexitFunc2,(void*) 20) != 0) error(1, errno, "on_exit onexitFunc1");
    printf("BEGIN...\n");
    // exit(3);
    printf("END...\n");
    // exit(0);
    // return 0;
    // return 2;
    _exit(0); // 系统调用，不会执行退出处理函数，不会刷新缓冲区
}
