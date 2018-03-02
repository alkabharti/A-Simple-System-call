#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<errno.h>
int main()
{
int a;
char buff[30];
printf("Enter the input\n");
scanf("%d",&a);
printf("Enter name of file\n");
scanf("%s",buff);
long int an=syscall(314,a,buff);
//printf("%d\n",an);
//printf("%d\n",errno);
return 0;
}
