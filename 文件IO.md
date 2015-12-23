#文件I/O

###3.3 函数open和函数openat

		#inlcude <fcntl.h>
		int open(const char *path, int oflag, ... /* mode_t mode */);
		int openat(int fd, const char *path, int oflag, ... /* mode_t mode */);

###3.4 函数create

		#include <fcntl.h>
		int create(const char *path, mode_t mode);

###3.5 函数close

		#include <fcntl.h>
		int close(int fd);

###3.6 函数 lseek

		#include <unistd.h>
		off_t lseek(int fd, off_t offset, int whence);
		                                     返回值：若成功，返回新的文件偏移量；若出错，返回-1

>whence的取值有:  SEEK_SET,SEEK_CUR,SEEK_END

###3.7 函数read

		#include <unistd.h>
		ssize_t read(int fd, void *buf, size_t nbytes);
		                                     返回值：读到的字节数，若已到文件尾，返回0；若出错，返回-1

###3.8 函数write

		#include<unistd.h>
		ssize_t write(int fd, void *buf, size_t nbytes);
		                                      返回值：若成功，返回已写的字节数；若出错，返回-1

###3.12 函数dup和dup2

		#include<unistd.h>
		int dup(int fd);
		int dup2(int fd1, int fd2);
		                                     两函数的返回值：若成功，返回新的文件描述符；若出错，返回-1
>由dup返回的新文件描述符一定是当前可用文件描述符中的最小数值。

###3.13 函数sync、fsync和fdatasync

		#include<unistd.h>
		int fsync(int fd);
		int fdatasync(int fd);
		void sync(void);

>sync只是将所有修改过的块缓冲区排入写队列，然后就返回，并不实际等待写磁盘操作结束。  
>fsync函数只对文件描述符fd指定的文件起作用，并且等待写磁盘操作结束才返回。  
>fdatasync函数类似于fsync，但它只影响文件的数据部分。而除数据外，fsync还会同时更新文件的属性。

###3.14 函数fcntl

>fcntl函数可以改变已经打开文件的属性

		#include<fcntl.h>
		int fcntl(int fd, int cmd, .../* int arg */);
		                                   返回值：若成功，则依赖于cmd；若出错，返回-1

>fcntl函数有以下5中功能：  
>
1. 复制一个已有的描述符 （cmd = F_DUPFD 或 F_DUPFD_CLOEXEC ).  
2. 获取/设置文件描述符标志 （cmd = F_GETFD 或 F_SETFD ）  
3. 获取/设置文件状态标志 （cmd = F_GETFL 或 F_SETFL ）  
4. 获取/设置异步I/O所有权 （cmd = F_GETOWN 或 F_SETOWN）  
5. 获取/设置记录所 （cmd = F_GETLK、F_SETLK 或 F_SETLKW）  

###3.15 函数ioctl

		#include <unistd.h>		/* System V */
		#inlcude <sys/ioctl.h>	/* BSD and Linux */
		int ioctl(int fd, int request, ...);
