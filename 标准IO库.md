#标准I/O库

###5.2 流和FILE对象

>流的定向：对于ASCII字符集，一个字符用一个字节表示。对于国际字符集，一个字符可用多个字节表示。标准I/O文件流可用于单字节或宽字符集。**流的定向：**决定了所读、写的字符是单字节还是多字节。只有两个函数可改变流的定向。freopen函数清除一个流的定向，fwide函数可用于设置流的定向。

		#include <stdio.h>
		#include <wchar.h>
		int fwide(FILE *fp, int mode);
				返回值：若流是宽定向的，返回正值；字节定向的，返回负值；未定向，返回0

###5.4 缓冲

>三种类型的缓冲：全缓冲，行缓冲，不带缓冲。

更改缓冲类型的函数：

		#include <stdio.h>
		void setbuf(FILE *restrict fp, char *restrict buf);
		int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);

强制冲洗一个流：

		#include<stdio.h>
		int fflush(FILE *fp);

###5.5 打开流

		#include <stdio.h>
		FILE *fopen(const char *restrict pathname, const char *restrict type);
		FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);
		FILE *fdopen(int fd, const char *type);

###5.6 读和写流

1. 输入函数

		#include <stdio.h>
		int getc(FILE *fp);
		int fgetc(FILE *fp);
		int getchar(void);

		int ferror(FILE *fp);
		int feof(FILE *fp);

		void clearerr(FILE *fp);

		int ungetc(int c, FILE *fp);

2.输出函数

		#include <stdio.h>
		int putc(int c, FILE *fp);
		int fputc(int c, FILE *fp);
		int putchar(int c);

###5.7 每次一行I/O

		#include <stdio.h>
		char *fgets(char *restrict buf, int n, FILE *restrict fp);
		char *gets(char *buf);

		int fputs(const char *restrict str, FILE *restrict fp);
		int puts(const char *str);

###5.9 二进制I/O

		#include<stdio.h>
		size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
		size_t fwrite(cont void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);

###5.10 定位流

> 有3种方法定位标准I/O流：  
>1.ftell 和 fseek 函数。这两个函数自V7以来就存在了，但是他们都假定文件的位置可以存放在一个长整形中。  
>2. ftello 和 fseeko 函数。Single UNIX Specification 引入了这连个函数，使文件偏移量可以不必一定使用长整形。它们使用off_t数据类型代替了长整形。  
>3. fgetpos 和 fsetpos 函数。这两个函数是由ISO C 引入的。

		#include <stdio.h>
		long ftell(FILE *fp);
						返回值：若成功，返回当前文件位置指示；若出错，返回-1L
		int fseek(FILE *fp, long offset, int whence);
		
		void rewind(FILE *fp);
		
		off_t ftello(FILE *fp);
		int fseeko(FILE *fp, off_t offset, int whence);
		
		int fgetpos(FILE *restrict fp, fpos_t *restrict pos);
		int fsetpos(FILE *fp, const char *pos);

###5.11 格式化I/O

>1. 格式化输出  
>
		int printf(const char *restrict format, ... );
		int fprintf(FILE *restrict fp, const char *restrict format, ... );
		int dprintf(int fd, const char* restrict format, .. );
		int sprintf(char *restrict buf, const char *restrict format, ... );
		int snprintf(char *restrict buf, size_t n, const char *restrict format, ... );
		
###5.13 临时文件

		#include <stdio.h>
		char *tmpnam(char *ptr);
		FILE *tmpfile(void);

###5.14 内存流

		#include <stdio.h>
		FILE *fmemopen(void *restrict buf, size_t size, const char *restrict type);
		