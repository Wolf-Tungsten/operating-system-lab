#include<unistd.h>
#include<stdio.h>
#include<bits/types.h>

int main(){
    int pid = getpid();
    printf("开始测试进程隐藏功能，当前进程 pid ： %d\n",pid);
    printf("按回车键隐藏\n");
    getchar();
    
    syscall(335,pid,1);
    printf("请检查隐藏情况， 按回车键退出\n");
    getchar();
    printf("隐藏全部root进程\n");
    syscall(336,0,1);
    printf("请检查隐藏情况， 按回车键恢复并退出\n");
    getchar();
    syscall(336,0,0);
    return 0;
}
