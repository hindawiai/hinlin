<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 OR MIT */
/* nolibc.h
 * Copyright (C) 2017-2018 Willy Tarreau <w@1wt.eu>
 */

/*
 * This file is deचिन्हित to be used as a libc alternative क्रम minimal programs
 * with very limited requirements. It consists of a small number of syscall and
 * type definitions, and the minimal startup code needed to call मुख्य().
 * All syscalls are declared as अटल functions so that they can be optimized
 * away by the compiler when not used.
 *
 * Syscalls are split पूर्णांकo 3 levels:
 *   - The lower level is the arch-specअगरic syscall() definition, consisting in
 *     assembly code in compound expressions. These are called my_syscall0() to
 *     my_syscall6() depending on the number of arguments. The MIPS
 *     implementation is limited to 5 arguments. All input arguments are cast
 *     to a दीर्घ stored in a रेजिस्टर. These expressions always वापस the
 *     syscall's वापस value as a चिन्हित दीर्घ value which is often either a
 *     poपूर्णांकer or the negated त्रुटि_सं value.
 *
 *   - The second level is mostly architecture-independent. It is made of
 *     अटल functions called sys_<name>() which rely on my_syscallN()
 *     depending on the syscall definition. These functions are responsible
 *     क्रम exposing the appropriate types क्रम the syscall arguments (पूर्णांक,
 *     poपूर्णांकers, etc) and क्रम setting the appropriate वापस type (often पूर्णांक).
 *     A few of them are architecture-specअगरic because the syscalls are not all
 *     mapped exactly the same among architectures. For example, some archs करो
 *     not implement select() and need pselect6() instead, so the sys_select()
 *     function will have to असलtract this.
 *
 *   - The third level is the libc call definition. It exposes the lower raw
 *     sys_<name>() calls in a way that looks like what a libc usually करोes,
 *     takes care of specअगरic input values, and of setting त्रुटि_सं upon error.
 *     There can be minor variations compared to standard libc calls. For
 *     example the खोलो() call always takes 3 args here.
 *
 * The त्रुटि_सं variable is declared अटल and unused. This way it can be
 * optimized away अगर not used. However this means that a program made of
 * multiple C files may observe dअगरferent त्रुटि_सं values (one per C file). For
 * the type of programs this project tarमाला_लो it usually is not a problem. The
 * resulting program may even be reduced by defining the NOLIBC_IGNORE_ERRNO
 * macro, in which हाल the त्रुटि_सं value will never be asचिन्हित.
 *
 * Some मानक_निवेशt-like पूर्णांकeger types are defined. These are valid on all currently
 * supported architectures, because signs are enक्रमced, पूर्णांकs are assumed to be
 * 32 bits, दीर्घs the size of a poपूर्णांकer and दीर्घ दीर्घ 64 bits. If more
 * architectures have to be supported, this may need to be adapted.
 *
 * Some macro definitions like the O_* values passed to खोलो(), and some
 * काष्ठाures like the sys_stat काष्ठा depend on the architecture.
 *
 * The definitions start with the architecture-specअगरic parts, which are picked
 * based on what the compiler knows about the target architecture, and are
 * completed with the generic code. Since it is the compiler which sets the
 * target architecture, cross-compiling normally works out of the box without
 * having to specअगरy anything.
 *
 * Finally some very common libc-level functions are provided. It is the हाल
 * क्रम a few functions usually found in माला.स, प्रकार.स, or मानककोष.स. Nothing
 * is currently provided regarding stdio emulation.
 *
 * The macro NOLIBC is always defined, so that it is possible क्रम a program to
 * check this macro to know अगर it is being built against and decide to disable
 * some features or simply not to include some standard libc files.
 *
 * Ideally this file should be split in multiple files क्रम easier दीर्घ term
 * मुख्यtenance, but provided as a single file as it is now, it's quite
 * convenient to use. Maybe some variations involving a set of includes at the
 * top could work.
 *
 * A simple अटल executable may be built this way :
 *      $ gcc -fno-asynchronous-unwind-tables -fno-ident -s -Os -nostdlib \
 *            -अटल -include nolibc.h -o hello hello.c -lgcc
 *
 * A very useful calling convention table may be found here :
 *      http://man7.org/linux/man-pages/man2/syscall.2.hपंचांगl
 *
 * This करोc is quite convenient though not necessarily up to date :
 *      https://w3challs.com/syscalls/
 *
 */

#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/loop.h>
#समावेश <linux/समय.स>

#घोषणा NOLIBC

/* this way it will be हटाओd अगर unused */
अटल पूर्णांक त्रुटि_सं;

#अगर_अघोषित NOLIBC_IGNORE_ERRNO
#घोषणा SET_ERRNO(v) करो अणु त्रुटि_सं = (v); पूर्ण जबतक (0)
#अन्यथा
#घोषणा SET_ERRNO(v) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* त्रुटि_सं codes all ensure that they will not conflict with a valid poपूर्णांकer
 * because they all correspond to the highest addressable memory page.
 */
#घोषणा MAX_ERRNO 4095

/* Declare a few quite common macros and types that usually are in मानककोष.स,
 * मानक_निवेशt.h, प्रकार.स, unistd.h and a few other common locations.
 */

#घोषणा शून्य ((व्योम *)0)

/* मानक_निवेशt types */
प्रकार अचिन्हित अक्षर       uपूर्णांक8_t;
प्रकार   चिन्हित अक्षर        पूर्णांक8_t;
प्रकार अचिन्हित लघु     uपूर्णांक16_t;
प्रकार   चिन्हित लघु      पूर्णांक16_t;
प्रकार अचिन्हित पूर्णांक       uपूर्णांक32_t;
प्रकार   चिन्हित पूर्णांक        पूर्णांक32_t;
प्रकार अचिन्हित दीर्घ दीर्घ uपूर्णांक64_t;
प्रकार   चिन्हित दीर्घ दीर्घ  पूर्णांक64_t;
प्रकार अचिन्हित दीर्घ        माप_प्रकार;
प्रकार   चिन्हित दीर्घ       sमाप_प्रकार;
प्रकार अचिन्हित दीर्घ     uपूर्णांकptr_t;
प्रकार   चिन्हित दीर्घ      पूर्णांकptr_t;
प्रकार   चिन्हित दीर्घ     सूचक_भेद_प्रकार;

/* क्रम stat() */
प्रकार अचिन्हित पूर्णांक          dev_t;
प्रकार अचिन्हित दीर्घ         ino_t;
प्रकार अचिन्हित पूर्णांक         mode_t;
प्रकार   चिन्हित पूर्णांक          pid_t;
प्रकार अचिन्हित पूर्णांक          uid_t;
प्रकार अचिन्हित पूर्णांक          gid_t;
प्रकार अचिन्हित दीर्घ       nlink_t;
प्रकार   चिन्हित दीर्घ         off_t;
प्रकार   चिन्हित दीर्घ     blkमाप_प्रकार;
प्रकार   चिन्हित दीर्घ      blkcnt_t;
प्रकार   चिन्हित दीर्घ        समय_प्रकार;

/* क्रम poll() */
काष्ठा pollfd अणु
	पूर्णांक fd;
	लघु पूर्णांक events;
	लघु पूर्णांक revents;
पूर्ण;

/* क्रम getdents64() */
काष्ठा linux_dirent64 अणु
	uपूर्णांक64_t       d_ino;
	पूर्णांक64_t        d_off;
	अचिन्हित लघु d_reclen;
	अचिन्हित अक्षर  d_type;
	अक्षर           d_name[];
पूर्ण;

/* commonly an fd_set represents 256 FDs */
#घोषणा FD_SETSIZE 256
प्रकार काष्ठा अणु uपूर्णांक32_t fd32[FD_SETSIZE/32]; पूर्ण fd_set;

/* needed by रुको4() */
काष्ठा rusage अणु
	काष्ठा समयval ru_uसमय;
	काष्ठा समयval ru_sसमय;
	दीर्घ   ru_maxrss;
	दीर्घ   ru_ixrss;
	दीर्घ   ru_idrss;
	दीर्घ   ru_isrss;
	दीर्घ   ru_minflt;
	दीर्घ   ru_majflt;
	दीर्घ   ru_nswap;
	दीर्घ   ru_inblock;
	दीर्घ   ru_oublock;
	दीर्घ   ru_msgsnd;
	दीर्घ   ru_msgrcv;
	दीर्घ   ru_nसंकेतs;
	दीर्घ   ru_nvcsw;
	दीर्घ   ru_nivcsw;
पूर्ण;

/* stat flags (WARNING, octal here) */
#घोषणा S_IFसूची       0040000
#घोषणा S_IFCHR       0020000
#घोषणा S_IFBLK       0060000
#घोषणा S_IFREG       0100000
#घोषणा S_IFIFO       0010000
#घोषणा S_IFLNK       0120000
#घोषणा S_IFSOCK      0140000
#घोषणा S_IFMT        0170000

#घोषणा S_ISसूची(mode)  (((mode) & S_IFसूची) == S_IFसूची)
#घोषणा S_ISCHR(mode)  (((mode) & S_IFCHR) == S_IFCHR)
#घोषणा S_ISBLK(mode)  (((mode) & S_IFBLK) == S_IFBLK)
#घोषणा S_ISREG(mode)  (((mode) & S_IFREG) == S_IFREG)
#घोषणा S_ISFIFO(mode) (((mode) & S_IFIFO) == S_IFIFO)
#घोषणा S_ISLNK(mode)  (((mode) & S_IFLNK) == S_IFLNK)
#घोषणा S_ISSOCK(mode) (((mode) & S_IFSOCK) == S_IFSOCK)

#घोषणा DT_UNKNOWN 0
#घोषणा DT_FIFO    1
#घोषणा DT_CHR     2
#घोषणा DT_सूची     4
#घोषणा DT_BLK     6
#घोषणा DT_REG     8
#घोषणा DT_LNK    10
#घोषणा DT_SOCK   12

/* all the *at functions */
#अगर_अघोषित AT_FDCWD
#घोषणा AT_FDCWD             -100
#पूर्ण_अगर

/* lseek */
#घोषणा शुरू_से        0
#घोषणा प्रस्तुत_से        1
#घोषणा अंत_से        2

/* reboot */
#घोषणा LINUX_REBOOT_MAGIC1         0xfee1dead
#घोषणा LINUX_REBOOT_MAGIC2         0x28121969
#घोषणा LINUX_REBOOT_CMD_HALT       0xcdef0123
#घोषणा LINUX_REBOOT_CMD_POWER_OFF  0x4321fedc
#घोषणा LINUX_REBOOT_CMD_RESTART    0x01234567
#घोषणा LINUX_REBOOT_CMD_SW_SUSPEND 0xd000fce2


/* The क्रमmat of the काष्ठा as वापसed by the libc to the application, which
 * signअगरicantly dअगरfers from the क्रमmat वापसed by the stat() syscall flavours.
 */
काष्ठा stat अणु
	dev_t     st_dev;     /* ID of device containing file */
	ino_t     st_ino;     /* inode number */
	mode_t    st_mode;    /* protection */
	nlink_t   st_nlink;   /* number of hard links */
	uid_t     st_uid;     /* user ID of owner */
	gid_t     st_gid;     /* group ID of owner */
	dev_t     st_rdev;    /* device ID (अगर special file) */
	off_t     st_size;    /* total size, in bytes */
	blkमाप_प्रकार st_blksize; /* blocksize क्रम file प्रणाली I/O */
	blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
	समय_प्रकार    st_aसमय;   /* समय of last access */
	समय_प्रकार    st_mसमय;   /* समय of last modअगरication */
	समय_प्रकार    st_स_समय;   /* समय of last status change */
पूर्ण;

#घोषणा WEXITSTATUS(status)   (((status) & 0xff00) >> 8)
#घोषणा WIFEXITED(status)     (((status) & 0x7f) == 0)

/* क्रम SIGCHLD */
#समावेश <यंत्र/संकेत.स>

/* Below comes the architecture-specअगरic code. For each architecture, we have
 * the syscall declarations and the _start code definition. This is the only
 * global part. On all architectures the kernel माला_दो everything in the stack
 * beक्रमe jumping to _start just above us, without any वापस address (_start
 * is not a function but an entry pपूर्णांक). So at the stack poपूर्णांकer we find argc.
 * Then argv[] begins, and ends at the first शून्य. Then we have envp which
 * starts and ends with a शून्य as well. So envp=argv+argc+1.
 */

#अगर defined(__x86_64__)
/* Syscalls क्रम x86_64 :
 *   - रेजिस्टरs are 64-bit
 *   - syscall number is passed in rax
 *   - arguments are in rdi, rsi, rdx, r10, r8, r9 respectively
 *   - the प्रणाली call is perक्रमmed by calling the syscall inकाष्ठाion
 *   - syscall वापस comes in rax
 *   - rcx and r8..r11 may be clobbered, others are preserved.
 *   - the arguments are cast to दीर्घ and asचिन्हित पूर्णांकo the target रेजिस्टरs
 *     which are then simply passed as रेजिस्टरs to the यंत्र code, so that we
 *     करोn't have to experience issues with रेजिस्टर स्थिरraपूर्णांकs.
 *   - the syscall number is always specअगरied last in order to allow to क्रमce
 *     some रेजिस्टरs beक्रमe (gcc refuses a %-रेजिस्टर at the last position).
 */

#घोषणा my_syscall0(num)                                                      \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("rax") = (num);                               \
									      \
	यंत्र अस्थिर (                                                        \
		"syscall\n"                                                   \
		: "=a" (_ret)                                                 \
		: "0"(_num)                                                   \
		: "rcx", "r8", "r9", "r10", "r11", "memory", "cc"             \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall1(num, arg1)                                                \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("rax") = (num);                               \
	रेजिस्टर दीर्घ _arg1 यंत्र("rdi") = (दीर्घ)(arg1);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"syscall\n"                                                   \
		: "=a" (_ret)                                                 \
		: "r"(_arg1),                                                 \
		  "0"(_num)                                                   \
		: "rcx", "r8", "r9", "r10", "r11", "memory", "cc"             \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall2(num, arg1, arg2)                                          \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("rax") = (num);                               \
	रेजिस्टर दीर्घ _arg1 यंत्र("rdi") = (दीर्घ)(arg1);                        \
	रेजिस्टर दीर्घ _arg2 यंत्र("rsi") = (दीर्घ)(arg2);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"syscall\n"                                                   \
		: "=a" (_ret)                                                 \
		: "r"(_arg1), "r"(_arg2),                                     \
		  "0"(_num)                                                   \
		: "rcx", "r8", "r9", "r10", "r11", "memory", "cc"             \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall3(num, arg1, arg2, arg3)                                    \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("rax") = (num);                               \
	रेजिस्टर दीर्घ _arg1 यंत्र("rdi") = (दीर्घ)(arg1);                        \
	रेजिस्टर दीर्घ _arg2 यंत्र("rsi") = (दीर्घ)(arg2);                        \
	रेजिस्टर दीर्घ _arg3 यंत्र("rdx") = (दीर्घ)(arg3);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"syscall\n"                                                   \
		: "=a" (_ret)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3),                         \
		  "0"(_num)                                                   \
		: "rcx", "r8", "r9", "r10", "r11", "memory", "cc"             \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall4(num, arg1, arg2, arg3, arg4)                              \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("rax") = (num);                               \
	रेजिस्टर दीर्घ _arg1 यंत्र("rdi") = (दीर्घ)(arg1);                        \
	रेजिस्टर दीर्घ _arg2 यंत्र("rsi") = (दीर्घ)(arg2);                        \
	रेजिस्टर दीर्घ _arg3 यंत्र("rdx") = (दीर्घ)(arg3);                        \
	रेजिस्टर दीर्घ _arg4 यंत्र("r10") = (दीर्घ)(arg4);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"syscall\n"                                                   \
		: "=a" (_ret), "=r"(_arg4)                                    \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4),             \
		  "0"(_num)                                                   \
		: "rcx", "r8", "r9", "r11", "memory", "cc"                    \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall5(num, arg1, arg2, arg3, arg4, arg5)                        \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("rax") = (num);                               \
	रेजिस्टर दीर्घ _arg1 यंत्र("rdi") = (दीर्घ)(arg1);                        \
	रेजिस्टर दीर्घ _arg2 यंत्र("rsi") = (दीर्घ)(arg2);                        \
	रेजिस्टर दीर्घ _arg3 यंत्र("rdx") = (दीर्घ)(arg3);                        \
	रेजिस्टर दीर्घ _arg4 यंत्र("r10") = (दीर्घ)(arg4);                        \
	रेजिस्टर दीर्घ _arg5 यंत्र("r8")  = (दीर्घ)(arg5);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"syscall\n"                                                   \
		: "=a" (_ret), "=r"(_arg4), "=r"(_arg5)                       \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5), \
		  "0"(_num)                                                   \
		: "rcx", "r9", "r11", "memory", "cc"                          \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall6(num, arg1, arg2, arg3, arg4, arg5, arg6)                  \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("rax") = (num);                               \
	रेजिस्टर दीर्घ _arg1 यंत्र("rdi") = (दीर्घ)(arg1);                        \
	रेजिस्टर दीर्घ _arg2 यंत्र("rsi") = (दीर्घ)(arg2);                        \
	रेजिस्टर दीर्घ _arg3 यंत्र("rdx") = (दीर्घ)(arg3);                        \
	रेजिस्टर दीर्घ _arg4 यंत्र("r10") = (दीर्घ)(arg4);                        \
	रेजिस्टर दीर्घ _arg5 यंत्र("r8")  = (दीर्घ)(arg5);                        \
	रेजिस्टर दीर्घ _arg6 यंत्र("r9")  = (दीर्घ)(arg6);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"syscall\n"                                                   \
		: "=a" (_ret), "=r"(_arg4), "=r"(_arg5)                       \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5), \
		  "r"(_arg6), "0"(_num)                                       \
		: "rcx", "r11", "memory", "cc"                                \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

/* startup code */
यंत्र(".section .text\n"
    ".global _start\n"
    "_start:\n"
    "pop %rdi\n"                // argc   (first arg, %rdi)
    "mov %rsp, %rsi\n"          // argv[] (second arg, %rsi)
    "lea 8(%rsi,%rdi,8),%rdx\n" // then a शून्य then envp (third arg, %rdx)
    "and $-16, %rsp\n"          // x86 ABI : esp must be 16-byte aligned when
    "sub $8, %rsp\n"            // entering the callee
    "call main\n"               // मुख्य() वापसs the status code, we'll निकास with it.
    "movzb %al, %rdi\n"         // retrieve निकास code from 8 lower bits
    "mov $60, %rax\n"           // NR_निकास == 60
    "syscall\n"                 // really निकास
    "hlt\n"                     // ensure it करोes not वापस
    "");

/* fcntl / खोलो */
#घोषणा O_RDONLY            0
#घोषणा O_WRONLY            1
#घोषणा O_RDWR              2
#घोषणा O_CREAT          0x40
#घोषणा O_EXCL           0x80
#घोषणा O_NOCTTY        0x100
#घोषणा O_TRUNC         0x200
#घोषणा O_APPEND        0x400
#घोषणा O_NONBLOCK      0x800
#घोषणा O_सूचीECTORY   0x10000

/* The काष्ठा वापसed by the stat() syscall, equivalent to stat64(). The
 * syscall वापसs 116 bytes and stops in the middle of __unused.
 */
काष्ठा sys_stat_काष्ठा अणु
	अचिन्हित दीर्घ st_dev;
	अचिन्हित दीर्घ st_ino;
	अचिन्हित दीर्घ st_nlink;
	अचिन्हित पूर्णांक  st_mode;
	अचिन्हित पूर्णांक  st_uid;

	अचिन्हित पूर्णांक  st_gid;
	अचिन्हित पूर्णांक  __pad0;
	अचिन्हित दीर्घ st_rdev;
	दीर्घ          st_size;
	दीर्घ          st_blksize;

	दीर्घ          st_blocks;
	अचिन्हित दीर्घ st_aसमय;
	अचिन्हित दीर्घ st_aसमय_nsec;
	अचिन्हित दीर्घ st_mसमय;

	अचिन्हित दीर्घ st_mसमय_nsec;
	अचिन्हित दीर्घ st_स_समय;
	अचिन्हित दीर्घ st_स_समय_nsec;
	दीर्घ          __unused[3];
पूर्ण;

#या_अगर defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
/* Syscalls क्रम i386 :
 *   - mostly similar to x86_64
 *   - रेजिस्टरs are 32-bit
 *   - syscall number is passed in eax
 *   - arguments are in ebx, ecx, edx, esi, edi, ebp respectively
 *   - all रेजिस्टरs are preserved (except eax of course)
 *   - the प्रणाली call is perक्रमmed by calling पूर्णांक $0x80
 *   - syscall वापस comes in eax
 *   - the arguments are cast to दीर्घ and asचिन्हित पूर्णांकo the target रेजिस्टरs
 *     which are then simply passed as रेजिस्टरs to the यंत्र code, so that we
 *     करोn't have to experience issues with रेजिस्टर स्थिरraपूर्णांकs.
 *   - the syscall number is always specअगरied last in order to allow to क्रमce
 *     some रेजिस्टरs beक्रमe (gcc refuses a %-रेजिस्टर at the last position).
 *
 * Also, i386 supports the old_select syscall अगर newselect is not available
 */
#घोषणा __ARCH_WANT_SYS_OLD_SELECT

#घोषणा my_syscall0(num)                                                      \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num यंत्र("eax") = (num);                                \
									      \
	यंत्र अस्थिर (                                                        \
		"int $0x80\n"                                                 \
		: "=a" (_ret)                                                 \
		: "0"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall1(num, arg1)                                                \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num यंत्र("eax") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("ebx") = (दीर्घ)(arg1);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"int $0x80\n"                                                 \
		: "=a" (_ret)                                                 \
		: "r"(_arg1),                                                 \
		  "0"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall2(num, arg1, arg2)                                          \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num यंत्र("eax") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("ebx") = (दीर्घ)(arg1);                        \
	रेजिस्टर दीर्घ _arg2 यंत्र("ecx") = (दीर्घ)(arg2);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"int $0x80\n"                                                 \
		: "=a" (_ret)                                                 \
		: "r"(_arg1), "r"(_arg2),                                     \
		  "0"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall3(num, arg1, arg2, arg3)                                    \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num यंत्र("eax") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("ebx") = (दीर्घ)(arg1);                        \
	रेजिस्टर दीर्घ _arg2 यंत्र("ecx") = (दीर्घ)(arg2);                        \
	रेजिस्टर दीर्घ _arg3 यंत्र("edx") = (दीर्घ)(arg3);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"int $0x80\n"                                                 \
		: "=a" (_ret)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3),                         \
		  "0"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall4(num, arg1, arg2, arg3, arg4)                              \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num यंत्र("eax") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("ebx") = (दीर्घ)(arg1);                        \
	रेजिस्टर दीर्घ _arg2 यंत्र("ecx") = (दीर्घ)(arg2);                        \
	रेजिस्टर दीर्घ _arg3 यंत्र("edx") = (दीर्घ)(arg3);                        \
	रेजिस्टर दीर्घ _arg4 यंत्र("esi") = (दीर्घ)(arg4);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"int $0x80\n"                                                 \
		: "=a" (_ret)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4),             \
		  "0"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

#घोषणा my_syscall5(num, arg1, arg2, arg3, arg4, arg5)                        \
(अणु                                                                            \
	दीर्घ _ret;                                                            \
	रेजिस्टर दीर्घ _num यंत्र("eax") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("ebx") = (दीर्घ)(arg1);                        \
	रेजिस्टर दीर्घ _arg2 यंत्र("ecx") = (दीर्घ)(arg2);                        \
	रेजिस्टर दीर्घ _arg3 यंत्र("edx") = (दीर्घ)(arg3);                        \
	रेजिस्टर दीर्घ _arg4 यंत्र("esi") = (दीर्घ)(arg4);                        \
	रेजिस्टर दीर्घ _arg5 यंत्र("edi") = (दीर्घ)(arg5);                        \
									      \
	यंत्र अस्थिर (                                                        \
		"int $0x80\n"                                                 \
		: "=a" (_ret)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5), \
		  "0"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_ret;                                                                 \
पूर्ण)

/* startup code */
यंत्र(".section .text\n"
    ".global _start\n"
    "_start:\n"
    "pop %eax\n"                // argc   (first arg, %eax)
    "mov %esp, %ebx\n"          // argv[] (second arg, %ebx)
    "lea 4(%ebx,%eax,4),%ecx\n" // then a शून्य then envp (third arg, %ecx)
    "and $-16, %esp\n"          // x86 ABI : esp must be 16-byte aligned when
    "push %ecx\n"               // push all रेजिस्टरs on the stack so that we
    "push %ebx\n"               // support both regparm and plain stack modes
    "push %eax\n"
    "call main\n"               // मुख्य() वापसs the status code in %eax
    "movzbl %al, %ebx\n"        // retrieve निकास code from lower 8 bits
    "movl   $1, %eax\n"         // NR_निकास == 1
    "int    $0x80\n"            // निकास now
    "hlt\n"                     // ensure it करोes not
    "");

/* fcntl / खोलो */
#घोषणा O_RDONLY            0
#घोषणा O_WRONLY            1
#घोषणा O_RDWR              2
#घोषणा O_CREAT          0x40
#घोषणा O_EXCL           0x80
#घोषणा O_NOCTTY        0x100
#घोषणा O_TRUNC         0x200
#घोषणा O_APPEND        0x400
#घोषणा O_NONBLOCK      0x800
#घोषणा O_सूचीECTORY   0x10000

/* The काष्ठा वापसed by the stat() syscall, 32-bit only, the syscall वापसs
 * exactly 56 bytes (stops beक्रमe the unused array).
 */
काष्ठा sys_stat_काष्ठा अणु
	अचिन्हित दीर्घ  st_dev;
	अचिन्हित दीर्घ  st_ino;
	अचिन्हित लघु st_mode;
	अचिन्हित लघु st_nlink;
	अचिन्हित लघु st_uid;
	अचिन्हित लघु st_gid;

	अचिन्हित दीर्घ  st_rdev;
	अचिन्हित दीर्घ  st_size;
	अचिन्हित दीर्घ  st_blksize;
	अचिन्हित दीर्घ  st_blocks;

	अचिन्हित दीर्घ  st_aसमय;
	अचिन्हित दीर्घ  st_aसमय_nsec;
	अचिन्हित दीर्घ  st_mसमय;
	अचिन्हित दीर्घ  st_mसमय_nsec;

	अचिन्हित दीर्घ  st_स_समय;
	अचिन्हित दीर्घ  st_स_समय_nsec;
	अचिन्हित दीर्घ  __unused[2];
पूर्ण;

#या_अगर defined(__ARM_EABI__)
/* Syscalls क्रम ARM in ARM or Thumb modes :
 *   - रेजिस्टरs are 32-bit
 *   - stack is 8-byte aligned
 *     ( http://infocenter.arm.com/help/index.jsp?topic=/com.arm.करोc.faqs/ka4127.hपंचांगl)
 *   - syscall number is passed in r7
 *   - arguments are in r0, r1, r2, r3, r4, r5
 *   - the प्रणाली call is perक्रमmed by calling svc #0
 *   - syscall वापस comes in r0.
 *   - only lr is clobbered.
 *   - the arguments are cast to दीर्घ and asचिन्हित पूर्णांकo the target रेजिस्टरs
 *     which are then simply passed as रेजिस्टरs to the यंत्र code, so that we
 *     करोn't have to experience issues with रेजिस्टर स्थिरraपूर्णांकs.
 *   - the syscall number is always specअगरied last in order to allow to क्रमce
 *     some रेजिस्टरs beक्रमe (gcc refuses a %-रेजिस्टर at the last position).
 *
 * Also, ARM supports the old_select syscall अगर newselect is not available
 */
#घोषणा __ARCH_WANT_SYS_OLD_SELECT

#घोषणा my_syscall0(num)                                                      \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("r7") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("r0");                                        \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall1(num, arg1)                                                \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("r7") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("r0") = (दीर्घ)(arg1);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1),                                                 \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall2(num, arg1, arg2)                                          \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("r7") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("r0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("r1") = (दीर्घ)(arg2);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1), "r"(_arg2),                                     \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall3(num, arg1, arg2, arg3)                                    \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("r7") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("r0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("r1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("r2") = (दीर्घ)(arg3);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3),                         \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall4(num, arg1, arg2, arg3, arg4)                              \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("r7") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("r0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("r1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("r2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("r3") = (दीर्घ)(arg4);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4),             \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall5(num, arg1, arg2, arg3, arg4, arg5)                        \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("r7") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("r0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("r1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("r2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("r3") = (दीर्घ)(arg4);                         \
	रेजिस्टर दीर्घ _arg5 यंत्र("r4") = (दीर्घ)(arg5);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r" (_arg1)                                                \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5), \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

/* startup code */
यंत्र(".section .text\n"
    ".global _start\n"
    "_start:\n"
#अगर defined(__THUMBEB__) || defined(__THUMBEL__)
    /* We enter here in 32-bit mode but अगर some previous functions were in
     * 16-bit mode, the assembler cannot know, so we need to tell it we're in
     * 32-bit now, then चयन to 16-bit (is there a better way to करो it than
     * adding 1 by hand ?) and tell the यंत्र we're now in 16-bit mode so that
     * it generates correct inकाष्ठाions. Note that we करो not support thumb1.
     */
    ".code 32\n"
    "add     r0, pc, #1\n"
    "bx      r0\n"
    ".code 16\n"
#पूर्ण_अगर
    "pop {%r0}\n"                 // argc was in the stack
    "mov %r1, %sp\n"              // argv = sp
    "add %r2, %r1, %r0, lsl #2\n" // envp = argv + 4*argc ...
    "add %r2, %r2, $4\n"          //        ... + 4
    "and %r3, %r1, $-8\n"         // AAPCS : sp must be 8-byte aligned in the
    "mov %sp, %r3\n"              //         callee, an bl करोesn't push (lr=pc)
    "bl main\n"                   // मुख्य() वापसs the status code, we'll निकास with it.
    "and %r0, %r0, $0xff\n"       // limit निकास code to 8 bits
    "movs r7, $1\n"               // NR_निकास == 1
    "svc $0x00\n"
    "");

/* fcntl / खोलो */
#घोषणा O_RDONLY            0
#घोषणा O_WRONLY            1
#घोषणा O_RDWR              2
#घोषणा O_CREAT          0x40
#घोषणा O_EXCL           0x80
#घोषणा O_NOCTTY        0x100
#घोषणा O_TRUNC         0x200
#घोषणा O_APPEND        0x400
#घोषणा O_NONBLOCK      0x800
#घोषणा O_सूचीECTORY    0x4000

/* The काष्ठा वापसed by the stat() syscall, 32-bit only, the syscall वापसs
 * exactly 56 bytes (stops beक्रमe the unused array). In big endian, the क्रमmat
 * dअगरfers as devices are वापसed as लघु only.
 */
काष्ठा sys_stat_काष्ठा अणु
#अगर defined(__ARMEB__)
	अचिन्हित लघु st_dev;
	अचिन्हित लघु __pad1;
#अन्यथा
	अचिन्हित दीर्घ  st_dev;
#पूर्ण_अगर
	अचिन्हित दीर्घ  st_ino;
	अचिन्हित लघु st_mode;
	अचिन्हित लघु st_nlink;
	अचिन्हित लघु st_uid;
	अचिन्हित लघु st_gid;
#अगर defined(__ARMEB__)
	अचिन्हित लघु st_rdev;
	अचिन्हित लघु __pad2;
#अन्यथा
	अचिन्हित दीर्घ  st_rdev;
#पूर्ण_अगर
	अचिन्हित दीर्घ  st_size;
	अचिन्हित दीर्घ  st_blksize;
	अचिन्हित दीर्घ  st_blocks;
	अचिन्हित दीर्घ  st_aसमय;
	अचिन्हित दीर्घ  st_aसमय_nsec;
	अचिन्हित दीर्घ  st_mसमय;
	अचिन्हित दीर्घ  st_mसमय_nsec;
	अचिन्हित दीर्घ  st_स_समय;
	अचिन्हित दीर्घ  st_स_समय_nsec;
	अचिन्हित दीर्घ  __unused[2];
पूर्ण;

#या_अगर defined(__aarch64__)
/* Syscalls क्रम AARCH64 :
 *   - रेजिस्टरs are 64-bit
 *   - stack is 16-byte aligned
 *   - syscall number is passed in x8
 *   - arguments are in x0, x1, x2, x3, x4, x5
 *   - the प्रणाली call is perक्रमmed by calling svc 0
 *   - syscall वापस comes in x0.
 *   - the arguments are cast to दीर्घ and asचिन्हित पूर्णांकo the target रेजिस्टरs
 *     which are then simply passed as रेजिस्टरs to the यंत्र code, so that we
 *     करोn't have to experience issues with रेजिस्टर स्थिरraपूर्णांकs.
 *
 * On aarch64, select() is not implemented so we have to use pselect6().
 */
#घोषणा __ARCH_WANT_SYS_PSELECT6

#घोषणा my_syscall0(num)                                                      \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("x8") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("x0");                                        \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall1(num, arg1)                                                \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("x8") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("x0") = (दीर्घ)(arg1);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1),                                                 \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall2(num, arg1, arg2)                                          \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("x8") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("x0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("x1") = (दीर्घ)(arg2);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1), "r"(_arg2),                                     \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall3(num, arg1, arg2, arg3)                                    \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("x8") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("x0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("x1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("x2") = (दीर्घ)(arg3);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3),                         \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall4(num, arg1, arg2, arg3, arg4)                              \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("x8") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("x0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("x1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("x2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("x3") = (दीर्घ)(arg4);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4),             \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall5(num, arg1, arg2, arg3, arg4, arg5)                        \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("x8") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("x0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("x1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("x2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("x3") = (दीर्घ)(arg4);                         \
	रेजिस्टर दीर्घ _arg5 यंत्र("x4") = (दीर्घ)(arg5);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r" (_arg1)                                                \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5), \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall6(num, arg1, arg2, arg3, arg4, arg5, arg6)                  \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("x8") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("x0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("x1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("x2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("x3") = (दीर्घ)(arg4);                         \
	रेजिस्टर दीर्घ _arg5 यंत्र("x4") = (दीर्घ)(arg5);                         \
	रेजिस्टर दीर्घ _arg6 यंत्र("x5") = (दीर्घ)(arg6);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"svc #0\n"                                                    \
		: "=r" (_arg1)                                                \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5), \
		  "r"(_arg6), "r"(_num)                                       \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

/* startup code */
यंत्र(".section .text\n"
    ".global _start\n"
    "_start:\n"
    "ldr x0, [sp]\n"              // argc (x0) was in the stack
    "add x1, sp, 8\n"             // argv (x1) = sp
    "lsl x2, x0, 3\n"             // envp (x2) = 8*argc ...
    "add x2, x2, 8\n"             //           + 8 (skip null)
    "add x2, x2, x1\n"            //           + argv
    "and sp, x1, -16\n"           // sp must be 16-byte aligned in the callee
    "bl main\n"                   // मुख्य() वापसs the status code, we'll निकास with it.
    "and x0, x0, 0xff\n"          // limit निकास code to 8 bits
    "mov x8, 93\n"                // NR_निकास == 93
    "svc #0\n"
    "");

/* fcntl / खोलो */
#घोषणा O_RDONLY            0
#घोषणा O_WRONLY            1
#घोषणा O_RDWR              2
#घोषणा O_CREAT          0x40
#घोषणा O_EXCL           0x80
#घोषणा O_NOCTTY        0x100
#घोषणा O_TRUNC         0x200
#घोषणा O_APPEND        0x400
#घोषणा O_NONBLOCK      0x800
#घोषणा O_सूचीECTORY    0x4000

/* The काष्ठा वापसed by the newख_स्थितिat() syscall. Dअगरfers slightly from the
 * x86_64's stat one by field ordering, so be careful.
 */
काष्ठा sys_stat_काष्ठा अणु
	अचिन्हित दीर्घ   st_dev;
	अचिन्हित दीर्घ   st_ino;
	अचिन्हित पूर्णांक    st_mode;
	अचिन्हित पूर्णांक    st_nlink;
	अचिन्हित पूर्णांक    st_uid;
	अचिन्हित पूर्णांक    st_gid;

	अचिन्हित दीर्घ   st_rdev;
	अचिन्हित दीर्घ   __pad1;
	दीर्घ            st_size;
	पूर्णांक             st_blksize;
	पूर्णांक             __pad2;

	दीर्घ            st_blocks;
	दीर्घ            st_aसमय;
	अचिन्हित दीर्घ   st_aसमय_nsec;
	दीर्घ            st_mसमय;

	अचिन्हित दीर्घ   st_mसमय_nsec;
	दीर्घ            st_स_समय;
	अचिन्हित दीर्घ   st_स_समय_nsec;
	अचिन्हित पूर्णांक    __unused[2];
पूर्ण;

#या_अगर defined(__mips__) && defined(_ABIO32)
/* Syscalls क्रम MIPS ABI O32 :
 *   - WARNING! there's always a delayed slot!
 *   - WARNING again, the syntax is dअगरferent, रेजिस्टरs take a '$' and numbers
 *     करो not.
 *   - रेजिस्टरs are 32-bit
 *   - stack is 8-byte aligned
 *   - syscall number is passed in v0 (starts at 0xfa0).
 *   - arguments are in a0, a1, a2, a3, then the stack. The caller needs to
 *     leave some room in the stack क्रम the callee to save a0..a3 अगर needed.
 *   - Many रेजिस्टरs are clobbered, in fact only a0..a2 and s0..s8 are
 *     preserved. See: https://www.linux-mips.org/wiki/Syscall as well as
 *     scall32-o32.S in the kernel sources.
 *   - the प्रणाली call is perक्रमmed by calling "syscall"
 *   - syscall वापस comes in v0, and रेजिस्टर a3 needs to be checked to know
 *     अगर an error occured, in which हाल त्रुटि_सं is in v0.
 *   - the arguments are cast to दीर्घ and asचिन्हित पूर्णांकo the target रेजिस्टरs
 *     which are then simply passed as रेजिस्टरs to the यंत्र code, so that we
 *     करोn't have to experience issues with रेजिस्टर स्थिरraपूर्णांकs.
 */

#घोषणा my_syscall0(num)                                                      \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("v0") = (num);                                 \
	रेजिस्टर दीर्घ _arg4 यंत्र("a3");                                        \
									      \
	यंत्र अस्थिर (                                                        \
		"addiu $sp, $sp, -32\n"                                       \
		"syscall\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=r"(_num), "=r"(_arg4)                                     \
		: "r"(_num)                                                   \
		: "memory", "cc", "at", "v1", "hi", "lo",                     \
		  "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"  \
	);                                                                    \
	_arg4 ? -_num : _num;                                                 \
पूर्ण)

#घोषणा my_syscall1(num, arg1)                                                \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("v0") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("a3");                                        \
									      \
	यंत्र अस्थिर (                                                        \
		"addiu $sp, $sp, -32\n"                                       \
		"syscall\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=r"(_num), "=r"(_arg4)                                     \
		: "0"(_num),                                                  \
		  "r"(_arg1)                                                  \
		: "memory", "cc", "at", "v1", "hi", "lo",                     \
		  "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"  \
	);                                                                    \
	_arg4 ? -_num : _num;                                                 \
पूर्ण)

#घोषणा my_syscall2(num, arg1, arg2)                                          \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("v0") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("a1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("a3");                                        \
									      \
	यंत्र अस्थिर (                                                        \
		"addiu $sp, $sp, -32\n"                                       \
		"syscall\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=r"(_num), "=r"(_arg4)                                     \
		: "0"(_num),                                                  \
		  "r"(_arg1), "r"(_arg2)                                      \
		: "memory", "cc", "at", "v1", "hi", "lo",                     \
		  "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"  \
	);                                                                    \
	_arg4 ? -_num : _num;                                                 \
पूर्ण)

#घोषणा my_syscall3(num, arg1, arg2, arg3)                                    \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("v0")  = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("a1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("a2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("a3");                                        \
									      \
	यंत्र अस्थिर (                                                        \
		"addiu $sp, $sp, -32\n"                                       \
		"syscall\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=r"(_num), "=r"(_arg4)                                     \
		: "0"(_num),                                                  \
		  "r"(_arg1), "r"(_arg2), "r"(_arg3)                          \
		: "memory", "cc", "at", "v1", "hi", "lo",                     \
		  "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"  \
	);                                                                    \
	_arg4 ? -_num : _num;                                                 \
पूर्ण)

#घोषणा my_syscall4(num, arg1, arg2, arg3, arg4)                              \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("v0") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("a1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("a2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("a3") = (दीर्घ)(arg4);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"addiu $sp, $sp, -32\n"                                       \
		"syscall\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=r" (_num), "=r"(_arg4)                                    \
		: "0"(_num),                                                  \
		  "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4)              \
		: "memory", "cc", "at", "v1", "hi", "lo",                     \
		  "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"  \
	);                                                                    \
	_arg4 ? -_num : _num;                                                 \
पूर्ण)

#घोषणा my_syscall5(num, arg1, arg2, arg3, arg4, arg5)                        \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num यंत्र("v0") = (num);                                 \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("a1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("a2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("a3") = (दीर्घ)(arg4);                         \
	रेजिस्टर दीर्घ _arg5 = (दीर्घ)(arg5);				      \
									      \
	यंत्र अस्थिर (                                                        \
		"addiu $sp, $sp, -32\n"                                       \
		"sw %7, 16($sp)\n"                                            \
		"syscall\n  "                                                 \
		"addiu $sp, $sp, 32\n"                                        \
		: "=r" (_num), "=r"(_arg4)                                    \
		: "0"(_num),                                                  \
		  "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5)  \
		: "memory", "cc", "at", "v1", "hi", "lo",                     \
		  "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"  \
	);                                                                    \
	_arg4 ? -_num : _num;                                                 \
पूर्ण)

/* startup code, note that it's called __start on MIPS */
यंत्र(".section .text\n"
    ".set nomips16\n"
    ".global __start\n"
    ".set    noreorder\n"
    ".option pic0\n"
    ".ent __start\n"
    "__start:\n"
    "lw $a0,($sp)\n"              // argc was in the stack
    "addiu  $a1, $sp, 4\n"        // argv = sp + 4
    "sll $a2, $a0, 2\n"           // a2 = argc * 4
    "add   $a2, $a2, $a1\n"       // envp = argv + 4*argc ...
    "addiu $a2, $a2, 4\n"         //        ... + 4
    "li $t0, -8\n"
    "and $sp, $sp, $t0\n"         // sp must be 8-byte aligned
    "addiu $sp,$sp,-16\n"         // the callee expects to save a0..a3 there!
    "jal main\n"                  // मुख्य() वापसs the status code, we'll निकास with it.
    "nop\n"                       // delayed slot
    "and $a0, $v0, 0xff\n"        // limit निकास code to 8 bits
    "li $v0, 4001\n"              // NR_निकास == 4001
    "syscall\n"
    ".end __start\n"
    "");

/* fcntl / खोलो */
#घोषणा O_RDONLY            0
#घोषणा O_WRONLY            1
#घोषणा O_RDWR              2
#घोषणा O_APPEND       0x0008
#घोषणा O_NONBLOCK     0x0080
#घोषणा O_CREAT        0x0100
#घोषणा O_TRUNC        0x0200
#घोषणा O_EXCL         0x0400
#घोषणा O_NOCTTY       0x0800
#घोषणा O_सूचीECTORY   0x10000

/* The काष्ठा वापसed by the stat() syscall. 88 bytes are वापसed by the
 * syscall.
 */
काष्ठा sys_stat_काष्ठा अणु
	अचिन्हित पूर्णांक  st_dev;
	दीर्घ          st_pad1[3];
	अचिन्हित दीर्घ st_ino;
	अचिन्हित पूर्णांक  st_mode;
	अचिन्हित पूर्णांक  st_nlink;
	अचिन्हित पूर्णांक  st_uid;
	अचिन्हित पूर्णांक  st_gid;
	अचिन्हित पूर्णांक  st_rdev;
	दीर्घ          st_pad2[2];
	दीर्घ          st_size;
	दीर्घ          st_pad3;
	दीर्घ          st_aसमय;
	दीर्घ          st_aसमय_nsec;
	दीर्घ          st_mसमय;
	दीर्घ          st_mसमय_nsec;
	दीर्घ          st_स_समय;
	दीर्घ          st_स_समय_nsec;
	दीर्घ          st_blksize;
	दीर्घ          st_blocks;
	दीर्घ          st_pad4[14];
पूर्ण;

#या_अगर defined(__riscv)

#अगर   __riscv_xlen == 64
#घोषणा PTRLOG "3"
#घोषणा SZREG  "8"
#या_अगर __riscv_xlen == 32
#घोषणा PTRLOG "2"
#घोषणा SZREG  "4"
#पूर्ण_अगर

/* Syscalls क्रम RISCV :
 *   - stack is 16-byte aligned
 *   - syscall number is passed in a7
 *   - arguments are in a0, a1, a2, a3, a4, a5
 *   - the प्रणाली call is perक्रमmed by calling ecall
 *   - syscall वापस comes in a0
 *   - the arguments are cast to दीर्घ and asचिन्हित पूर्णांकo the target
 *     रेजिस्टरs which are then simply passed as रेजिस्टरs to the यंत्र code,
 *     so that we करोn't have to experience issues with रेजिस्टर स्थिरraपूर्णांकs.
 */

#घोषणा my_syscall0(num)                                                      \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("a7") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0");                                        \
									      \
	यंत्र अस्थिर (                                                        \
		"ecall\n\t"                                                   \
		: "=r"(_arg1)                                                 \
		: "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall1(num, arg1)                                                \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("a7") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);		              \
									      \
	यंत्र अस्थिर (                                                        \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall2(num, arg1, arg2)                                          \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("a7") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("a1") = (दीर्घ)(arg2);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2),                                                 \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall3(num, arg1, arg2, arg3)                                    \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("a7") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("a1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("a2") = (दीर्घ)(arg3);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"ecall\n\t"                                                   \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2), "r"(_arg3),                                     \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall4(num, arg1, arg2, arg3, arg4)                              \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("a7") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("a1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("a2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("a3") = (दीर्घ)(arg4);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2), "r"(_arg3), "r"(_arg4),                         \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall5(num, arg1, arg2, arg3, arg4, arg5)                        \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("a7") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("a1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("a2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("a3") = (दीर्घ)(arg4);                         \
	रेजिस्टर दीर्घ _arg5 यंत्र("a4") = (दीर्घ)(arg5);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5),             \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

#घोषणा my_syscall6(num, arg1, arg2, arg3, arg4, arg5, arg6)                  \
(अणु                                                                            \
	रेजिस्टर दीर्घ _num  यंत्र("a7") = (num);                                \
	रेजिस्टर दीर्घ _arg1 यंत्र("a0") = (दीर्घ)(arg1);                         \
	रेजिस्टर दीर्घ _arg2 यंत्र("a1") = (दीर्घ)(arg2);                         \
	रेजिस्टर दीर्घ _arg3 यंत्र("a2") = (दीर्घ)(arg3);                         \
	रेजिस्टर दीर्घ _arg4 यंत्र("a3") = (दीर्घ)(arg4);                         \
	रेजिस्टर दीर्घ _arg5 यंत्र("a4") = (दीर्घ)(arg5);                         \
	रेजिस्टर दीर्घ _arg6 यंत्र("a5") = (दीर्घ)(arg6);                         \
									      \
	यंत्र अस्थिर (                                                        \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5), "r"(_arg6), \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
पूर्ण)

/* startup code */
यंत्र(".section .text\n"
    ".global _start\n"
    "_start:\n"
    ".option push\n"
    ".option norelax\n"
    "lla   gp, __global_pointer$\n"
    ".option pop\n"
    "ld    a0, 0(sp)\n"          // argc (a0) was in the stack
    "add   a1, sp, "SZREG"\n"    // argv (a1) = sp
    "slli  a2, a0, "PTRLOG"\n"   // envp (a2) = SZREG*argc ...
    "add   a2, a2, "SZREG"\n"    //             + SZREG (skip null)
    "add   a2,a2,a1\n"           //             + argv
    "andi  sp,a1,-16\n"          // sp must be 16-byte aligned
    "call  main\n"               // मुख्य() वापसs the status code, we'll निकास with it.
    "andi  a0, a0, 0xff\n"       // limit निकास code to 8 bits
    "li a7, 93\n"                // NR_निकास == 93
    "ecall\n"
    "");

/* fcntl / खोलो */
#घोषणा O_RDONLY            0
#घोषणा O_WRONLY            1
#घोषणा O_RDWR              2
#घोषणा O_CREAT         0x100
#घोषणा O_EXCL          0x200
#घोषणा O_NOCTTY        0x400
#घोषणा O_TRUNC        0x1000
#घोषणा O_APPEND       0x2000
#घोषणा O_NONBLOCK     0x4000
#घोषणा O_सूचीECTORY  0x200000

काष्ठा sys_stat_काष्ठा अणु
	अचिन्हित दीर्घ	st_dev;		/* Device.  */
	अचिन्हित दीर्घ	st_ino;		/* File serial number.  */
	अचिन्हित पूर्णांक	st_mode;	/* File mode.  */
	अचिन्हित पूर्णांक	st_nlink;	/* Link count.  */
	अचिन्हित पूर्णांक	st_uid;		/* User ID of the file's owner.  */
	अचिन्हित पूर्णांक	st_gid;		/* Group ID of the file's group. */
	अचिन्हित दीर्घ	st_rdev;	/* Device number, अगर device.  */
	अचिन्हित दीर्घ	__pad1;
	दीर्घ		st_size;	/* Size of file, in bytes.  */
	पूर्णांक		st_blksize;	/* Optimal block size क्रम I/O.  */
	पूर्णांक		__pad2;
	दीर्घ		st_blocks;	/* Number 512-byte blocks allocated. */
	दीर्घ		st_aसमय;	/* Time of last access.  */
	अचिन्हित दीर्घ	st_aसमय_nsec;
	दीर्घ		st_mसमय;	/* Time of last modअगरication.  */
	अचिन्हित दीर्घ	st_mसमय_nsec;
	दीर्घ		st_स_समय;	/* Time of last status change.  */
	अचिन्हित दीर्घ	st_स_समय_nsec;
	अचिन्हित पूर्णांक	__unused4;
	अचिन्हित पूर्णांक	__unused5;
पूर्ण;

#पूर्ण_अगर


/* Below are the C functions used to declare the raw syscalls. They try to be
 * architecture-agnostic, and वापस either a success or -त्रुटि_सं. Declaring them
 * अटल will lead to them being अंतरभूतd in most हालs, but it's still possible
 * to reference them by a poपूर्णांकer अगर needed.
 */
अटल __attribute__((unused))
व्योम *sys_brk(व्योम *addr)
अणु
	वापस (व्योम *)my_syscall1(__NR_brk, addr);
पूर्ण

अटल __attribute__((noवापस,unused))
व्योम sys_निकास(पूर्णांक status)
अणु
	my_syscall1(__NR_निकास, status & 255);
	जबतक(1); // shut the "noreturn" warnings.
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_स_बदलो(स्थिर अक्षर *path)
अणु
	वापस my_syscall1(__NR_स_बदलो, path);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_chmod(स्थिर अक्षर *path, mode_t mode)
अणु
#अगर_घोषित __NR_fchmodat
	वापस my_syscall4(__NR_fchmodat, AT_FDCWD, path, mode, 0);
#या_अगर defined(__NR_chmod)
	वापस my_syscall2(__NR_chmod, path, mode);
#अन्यथा
#त्रुटि Neither __NR_fchmodat nor __NR_chmod defined, cannot implement sys_chmod()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_chown(स्थिर अक्षर *path, uid_t owner, gid_t group)
अणु
#अगर_घोषित __NR_fchownat
	वापस my_syscall5(__NR_fchownat, AT_FDCWD, path, owner, group, 0);
#या_अगर defined(__NR_chown)
	वापस my_syscall3(__NR_chown, path, owner, group);
#अन्यथा
#त्रुटि Neither __NR_fchownat nor __NR_chown defined, cannot implement sys_chown()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_chroot(स्थिर अक्षर *path)
अणु
	वापस my_syscall1(__NR_chroot, path);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_बंद(पूर्णांक fd)
अणु
	वापस my_syscall1(__NR_बंद, fd);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_dup(पूर्णांक fd)
अणु
	वापस my_syscall1(__NR_dup, fd);
पूर्ण

#अगर_घोषित __NR_dup3
अटल __attribute__((unused))
पूर्णांक sys_dup3(पूर्णांक old, पूर्णांक new, पूर्णांक flags)
अणु
	वापस my_syscall3(__NR_dup3, old, new, flags);
पूर्ण
#पूर्ण_अगर

अटल __attribute__((unused))
पूर्णांक sys_dup2(पूर्णांक old, पूर्णांक new)
अणु
#अगर_घोषित __NR_dup3
	वापस my_syscall3(__NR_dup3, old, new, 0);
#या_अगर defined(__NR_dup2)
	वापस my_syscall2(__NR_dup2, old, new);
#अन्यथा
#त्रुटि Neither __NR_dup3 nor __NR_dup2 defined, cannot implement sys_dup2()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_execve(स्थिर अक्षर *filename, अक्षर *स्थिर argv[], अक्षर *स्थिर envp[])
अणु
	वापस my_syscall3(__NR_execve, filename, argv, envp);
पूर्ण

अटल __attribute__((unused))
pid_t sys_विभाजन(व्योम)
अणु
#अगर_घोषित __NR_clone
	/* note: some archs only have clone() and not विभाजन(). Dअगरferent archs
	 * have a dअगरferent API, but most archs have the flags on first arg and
	 * will not use the rest with no other flag.
	 */
	वापस my_syscall5(__NR_clone, SIGCHLD, 0, 0, 0, 0);
#या_अगर defined(__NR_विभाजन)
	वापस my_syscall0(__NR_विभाजन);
#अन्यथा
#त्रुटि Neither __NR_clone nor __NR_विभाजन defined, cannot implement sys_विभाजन()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_fsync(पूर्णांक fd)
अणु
	वापस my_syscall1(__NR_fsync, fd);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_getdents64(पूर्णांक fd, काष्ठा linux_dirent64 *dirp, पूर्णांक count)
अणु
	वापस my_syscall3(__NR_getdents64, fd, dirp, count);
पूर्ण

अटल __attribute__((unused))
pid_t sys_getpgid(pid_t pid)
अणु
	वापस my_syscall1(__NR_getpgid, pid);
पूर्ण

अटल __attribute__((unused))
pid_t sys_getpgrp(व्योम)
अणु
	वापस sys_getpgid(0);
पूर्ण

अटल __attribute__((unused))
pid_t sys_getpid(व्योम)
अणु
	वापस my_syscall0(__NR_getpid);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_समय_लोofday(काष्ठा समयval *tv, काष्ठा समयzone *tz)
अणु
	वापस my_syscall2(__NR_समय_लोofday, tv, tz);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_ioctl(पूर्णांक fd, अचिन्हित दीर्घ req, व्योम *value)
अणु
	वापस my_syscall3(__NR_ioctl, fd, req, value);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_समाप्त(pid_t pid, पूर्णांक संकेत)
अणु
	वापस my_syscall2(__NR_समाप्त, pid, संकेत);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_link(स्थिर अक्षर *old, स्थिर अक्षर *new)
अणु
#अगर_घोषित __NR_linkat
	वापस my_syscall5(__NR_linkat, AT_FDCWD, old, AT_FDCWD, new, 0);
#या_अगर defined(__NR_link)
	वापस my_syscall2(__NR_link, old, new);
#अन्यथा
#त्रुटि Neither __NR_linkat nor __NR_link defined, cannot implement sys_link()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
off_t sys_lseek(पूर्णांक fd, off_t offset, पूर्णांक whence)
अणु
	वापस my_syscall3(__NR_lseek, fd, offset, whence);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_सूची_गढ़ो(स्थिर अक्षर *path, mode_t mode)
अणु
#अगर_घोषित __NR_सूची_गढ़ोat
	वापस my_syscall3(__NR_सूची_गढ़ोat, AT_FDCWD, path, mode);
#या_अगर defined(__NR_सूची_गढ़ो)
	वापस my_syscall2(__NR_सूची_गढ़ो, path, mode);
#अन्यथा
#त्रुटि Neither __NR_सूची_गढ़ोat nor __NR_सूची_गढ़ो defined, cannot implement sys_सूची_गढ़ो()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
दीर्घ sys_mknod(स्थिर अक्षर *path, mode_t mode, dev_t dev)
अणु
#अगर_घोषित __NR_mknodat
	वापस my_syscall4(__NR_mknodat, AT_FDCWD, path, mode, dev);
#या_अगर defined(__NR_mknod)
	वापस my_syscall3(__NR_mknod, path, mode, dev);
#अन्यथा
#त्रुटि Neither __NR_mknodat nor __NR_mknod defined, cannot implement sys_mknod()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_mount(स्थिर अक्षर *src, स्थिर अक्षर *tgt, स्थिर अक्षर *fst,
	      अचिन्हित दीर्घ flags, स्थिर व्योम *data)
अणु
	वापस my_syscall5(__NR_mount, src, tgt, fst, flags, data);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_खोलो(स्थिर अक्षर *path, पूर्णांक flags, mode_t mode)
अणु
#अगर_घोषित __NR_खोलोat
	वापस my_syscall4(__NR_खोलोat, AT_FDCWD, path, flags, mode);
#या_अगर defined(__NR_खोलो)
	वापस my_syscall3(__NR_खोलो, path, flags, mode);
#अन्यथा
#त्रुटि Neither __NR_खोलोat nor __NR_खोलो defined, cannot implement sys_खोलो()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_pivot_root(स्थिर अक्षर *new, स्थिर अक्षर *old)
अणु
	वापस my_syscall2(__NR_pivot_root, new, old);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_poll(काष्ठा pollfd *fds, पूर्णांक nfds, पूर्णांक समयout)
अणु
#अगर defined(__NR_ppoll)
	काष्ठा बारpec t;

	अगर (समयout >= 0) अणु
		t.tv_sec  = समयout / 1000;
		t.tv_nsec = (समयout % 1000) * 1000000;
	पूर्ण
	वापस my_syscall4(__NR_ppoll, fds, nfds, (समयout >= 0) ? &t : शून्य, शून्य);
#या_अगर defined(__NR_poll)
	वापस my_syscall3(__NR_poll, fds, nfds, समयout);
#अन्यथा
#त्रुटि Neither __NR_ppoll nor __NR_poll defined, cannot implement sys_poll()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
sमाप_प्रकार sys_पढ़ो(पूर्णांक fd, व्योम *buf, माप_प्रकार count)
अणु
	वापस my_syscall3(__NR_पढ़ो, fd, buf, count);
पूर्ण

अटल __attribute__((unused))
sमाप_प्रकार sys_reboot(पूर्णांक magic1, पूर्णांक magic2, पूर्णांक cmd, व्योम *arg)
अणु
	वापस my_syscall4(__NR_reboot, magic1, magic2, cmd, arg);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_sched_yield(व्योम)
अणु
	वापस my_syscall0(__NR_sched_yield);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_select(पूर्णांक nfds, fd_set *rfds, fd_set *wfds, fd_set *efds, काष्ठा समयval *समयout)
अणु
#अगर defined(__ARCH_WANT_SYS_OLD_SELECT) && !defined(__NR__newselect)
	काष्ठा sel_arg_काष्ठा अणु
		अचिन्हित दीर्घ n;
		fd_set *r, *w, *e;
		काष्ठा समयval *t;
	पूर्ण arg = अणु .n = nfds, .r = rfds, .w = wfds, .e = efds, .t = समयout पूर्ण;
	वापस my_syscall1(__NR_select, &arg);
#या_अगर defined(__ARCH_WANT_SYS_PSELECT6) && defined(__NR_pselect6)
	काष्ठा बारpec t;

	अगर (समयout) अणु
		t.tv_sec  = समयout->tv_sec;
		t.tv_nsec = समयout->tv_usec * 1000;
	पूर्ण
	वापस my_syscall6(__NR_pselect6, nfds, rfds, wfds, efds, समयout ? &t : शून्य, शून्य);
#या_अगर defined(__NR__newselect) || defined(__NR_select)
#अगर_अघोषित __NR__newselect
#घोषणा __NR__newselect __NR_select
#पूर्ण_अगर
	वापस my_syscall5(__NR__newselect, nfds, rfds, wfds, efds, समयout);
#अन्यथा
#त्रुटि None of __NR_select, __NR_pselect6, nor __NR__newselect defined, cannot implement sys_select()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_setpgid(pid_t pid, pid_t pgid)
अणु
	वापस my_syscall2(__NR_setpgid, pid, pgid);
पूर्ण

अटल __attribute__((unused))
pid_t sys_setsid(व्योम)
अणु
	वापस my_syscall0(__NR_setsid);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_stat(स्थिर अक्षर *path, काष्ठा stat *buf)
अणु
	काष्ठा sys_stat_काष्ठा stat;
	दीर्घ ret;

#अगर_घोषित __NR_newख_स्थितिat
	/* only solution क्रम arm64 */
	ret = my_syscall4(__NR_newख_स्थितिat, AT_FDCWD, path, &stat, 0);
#या_अगर defined(__NR_stat)
	ret = my_syscall2(__NR_stat, path, &stat);
#अन्यथा
#त्रुटि Neither __NR_newख_स्थितिat nor __NR_stat defined, cannot implement sys_stat()
#पूर्ण_अगर
	buf->st_dev     = stat.st_dev;
	buf->st_ino     = stat.st_ino;
	buf->st_mode    = stat.st_mode;
	buf->st_nlink   = stat.st_nlink;
	buf->st_uid     = stat.st_uid;
	buf->st_gid     = stat.st_gid;
	buf->st_rdev    = stat.st_rdev;
	buf->st_size    = stat.st_size;
	buf->st_blksize = stat.st_blksize;
	buf->st_blocks  = stat.st_blocks;
	buf->st_aसमय   = stat.st_aसमय;
	buf->st_mसमय   = stat.st_mसमय;
	buf->st_स_समय   = stat.st_स_समय;
	वापस ret;
पूर्ण


अटल __attribute__((unused))
पूर्णांक sys_symlink(स्थिर अक्षर *old, स्थिर अक्षर *new)
अणु
#अगर_घोषित __NR_symlinkat
	वापस my_syscall3(__NR_symlinkat, old, AT_FDCWD, new);
#या_अगर defined(__NR_symlink)
	वापस my_syscall2(__NR_symlink, old, new);
#अन्यथा
#त्रुटि Neither __NR_symlinkat nor __NR_symlink defined, cannot implement sys_symlink()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
mode_t sys_umask(mode_t mode)
अणु
	वापस my_syscall1(__NR_umask, mode);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_umount2(स्थिर अक्षर *path, पूर्णांक flags)
अणु
	वापस my_syscall2(__NR_umount2, path, flags);
पूर्ण

अटल __attribute__((unused))
पूर्णांक sys_unlink(स्थिर अक्षर *path)
अणु
#अगर_घोषित __NR_unlinkat
	वापस my_syscall3(__NR_unlinkat, AT_FDCWD, path, 0);
#या_अगर defined(__NR_unlink)
	वापस my_syscall1(__NR_unlink, path);
#अन्यथा
#त्रुटि Neither __NR_unlinkat nor __NR_unlink defined, cannot implement sys_unlink()
#पूर्ण_अगर
पूर्ण

अटल __attribute__((unused))
pid_t sys_रुको4(pid_t pid, पूर्णांक *status, पूर्णांक options, काष्ठा rusage *rusage)
अणु
	वापस my_syscall4(__NR_रुको4, pid, status, options, rusage);
पूर्ण

अटल __attribute__((unused))
pid_t sys_रुकोpid(pid_t pid, पूर्णांक *status, पूर्णांक options)
अणु
	वापस sys_रुको4(pid, status, options, 0);
पूर्ण

अटल __attribute__((unused))
pid_t sys_रुको(पूर्णांक *status)
अणु
	वापस sys_रुकोpid(-1, status, 0);
पूर्ण

अटल __attribute__((unused))
sमाप_प्रकार sys_ग_लिखो(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	वापस my_syscall3(__NR_ग_लिखो, fd, buf, count);
पूर्ण


/* Below are the libc-compatible syscalls which वापस x or -1 and set त्रुटि_सं.
 * They rely on the functions above. Similarly they're marked अटल so that it
 * is possible to assign poपूर्णांकers to them अगर needed.
 */

अटल __attribute__((unused))
पूर्णांक brk(व्योम *addr)
अणु
	व्योम *ret = sys_brk(addr);

	अगर (!ret) अणु
		SET_ERRNO(ENOMEM);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल __attribute__((noवापस,unused))
व्योम निकास(पूर्णांक status)
अणु
	sys_निकास(status);
पूर्ण

अटल __attribute__((unused))
पूर्णांक स_बदलो(स्थिर अक्षर *path)
अणु
	पूर्णांक ret = sys_स_बदलो(path);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक chmod(स्थिर अक्षर *path, mode_t mode)
अणु
	पूर्णांक ret = sys_chmod(path, mode);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक chown(स्थिर अक्षर *path, uid_t owner, gid_t group)
अणु
	पूर्णांक ret = sys_chown(path, owner, group);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक chroot(स्थिर अक्षर *path)
अणु
	पूर्णांक ret = sys_chroot(path);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक बंद(पूर्णांक fd)
अणु
	पूर्णांक ret = sys_बंद(fd);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक dup(पूर्णांक fd)
अणु
	पूर्णांक ret = sys_dup(fd);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक dup2(पूर्णांक old, पूर्णांक new)
अणु
	पूर्णांक ret = sys_dup2(old, new);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित __NR_dup3
अटल __attribute__((unused))
पूर्णांक dup3(पूर्णांक old, पूर्णांक new, पूर्णांक flags)
अणु
	पूर्णांक ret = sys_dup3(old, new, flags);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल __attribute__((unused))
पूर्णांक execve(स्थिर अक्षर *filename, अक्षर *स्थिर argv[], अक्षर *स्थिर envp[])
अणु
	पूर्णांक ret = sys_execve(filename, argv, envp);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
pid_t विभाजन(व्योम)
अणु
	pid_t ret = sys_विभाजन();

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक fsync(पूर्णांक fd)
अणु
	पूर्णांक ret = sys_fsync(fd);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक getdents64(पूर्णांक fd, काष्ठा linux_dirent64 *dirp, पूर्णांक count)
अणु
	पूर्णांक ret = sys_getdents64(fd, dirp, count);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
pid_t getpgid(pid_t pid)
अणु
	pid_t ret = sys_getpgid(pid);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
pid_t getpgrp(व्योम)
अणु
	pid_t ret = sys_getpgrp();

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
pid_t getpid(व्योम)
अणु
	pid_t ret = sys_getpid();

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक समय_लोofday(काष्ठा समयval *tv, काष्ठा समयzone *tz)
अणु
	पूर्णांक ret = sys_समय_लोofday(tv, tz);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक ioctl(पूर्णांक fd, अचिन्हित दीर्घ req, व्योम *value)
अणु
	पूर्णांक ret = sys_ioctl(fd, req, value);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक समाप्त(pid_t pid, पूर्णांक संकेत)
अणु
	पूर्णांक ret = sys_समाप्त(pid, संकेत);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक link(स्थिर अक्षर *old, स्थिर अक्षर *new)
अणु
	पूर्णांक ret = sys_link(old, new);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
off_t lseek(पूर्णांक fd, off_t offset, पूर्णांक whence)
अणु
	off_t ret = sys_lseek(fd, offset, whence);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक सूची_गढ़ो(स्थिर अक्षर *path, mode_t mode)
अणु
	पूर्णांक ret = sys_सूची_गढ़ो(path, mode);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक mknod(स्थिर अक्षर *path, mode_t mode, dev_t dev)
अणु
	पूर्णांक ret = sys_mknod(path, mode, dev);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक mount(स्थिर अक्षर *src, स्थिर अक्षर *tgt,
	  स्थिर अक्षर *fst, अचिन्हित दीर्घ flags,
	  स्थिर व्योम *data)
अणु
	पूर्णांक ret = sys_mount(src, tgt, fst, flags, data);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक खोलो(स्थिर अक्षर *path, पूर्णांक flags, mode_t mode)
अणु
	पूर्णांक ret = sys_खोलो(path, flags, mode);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक pivot_root(स्थिर अक्षर *new, स्थिर अक्षर *old)
अणु
	पूर्णांक ret = sys_pivot_root(new, old);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक poll(काष्ठा pollfd *fds, पूर्णांक nfds, पूर्णांक समयout)
अणु
	पूर्णांक ret = sys_poll(fds, nfds, समयout);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
sमाप_प्रकार पढ़ो(पूर्णांक fd, व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret = sys_पढ़ो(fd, buf, count);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक reboot(पूर्णांक cmd)
अणु
	पूर्णांक ret = sys_reboot(LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2, cmd, 0);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
व्योम *sbrk(पूर्णांकptr_t inc)
अणु
	व्योम *ret;

	/* first call to find current end */
	अगर ((ret = sys_brk(0)) && (sys_brk(ret + inc) == ret + inc))
		वापस ret + inc;

	SET_ERRNO(ENOMEM);
	वापस (व्योम *)-1;
पूर्ण

अटल __attribute__((unused))
पूर्णांक sched_yield(व्योम)
अणु
	पूर्णांक ret = sys_sched_yield();

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक select(पूर्णांक nfds, fd_set *rfds, fd_set *wfds, fd_set *efds, काष्ठा समयval *समयout)
अणु
	पूर्णांक ret = sys_select(nfds, rfds, wfds, efds, समयout);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक setpgid(pid_t pid, pid_t pgid)
अणु
	पूर्णांक ret = sys_setpgid(pid, pgid);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
pid_t setsid(व्योम)
अणु
	pid_t ret = sys_setsid();

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
अचिन्हित पूर्णांक sleep(अचिन्हित पूर्णांक seconds)
अणु
	काष्ठा समयval my_समयval = अणु seconds, 0 पूर्ण;

	अगर (sys_select(0, 0, 0, 0, &my_समयval) < 0)
		वापस my_समयval.tv_sec + !!my_समयval.tv_usec;
	अन्यथा
		वापस 0;
पूर्ण

अटल __attribute__((unused))
पूर्णांक stat(स्थिर अक्षर *path, काष्ठा stat *buf)
अणु
	पूर्णांक ret = sys_stat(path, buf);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक symlink(स्थिर अक्षर *old, स्थिर अक्षर *new)
अणु
	पूर्णांक ret = sys_symlink(old, new);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक tcsetpgrp(पूर्णांक fd, pid_t pid)
अणु
	वापस ioctl(fd, TIOCSPGRP, &pid);
पूर्ण

अटल __attribute__((unused))
mode_t umask(mode_t mode)
अणु
	वापस sys_umask(mode);
पूर्ण

अटल __attribute__((unused))
पूर्णांक umount2(स्थिर अक्षर *path, पूर्णांक flags)
अणु
	पूर्णांक ret = sys_umount2(path, flags);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक unlink(स्थिर अक्षर *path)
अणु
	पूर्णांक ret = sys_unlink(path);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
pid_t रुको4(pid_t pid, पूर्णांक *status, पूर्णांक options, काष्ठा rusage *rusage)
अणु
	pid_t ret = sys_रुको4(pid, status, options, rusage);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
pid_t रुकोpid(pid_t pid, पूर्णांक *status, पूर्णांक options)
अणु
	pid_t ret = sys_रुकोpid(pid, status, options);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
pid_t रुको(पूर्णांक *status)
अणु
	pid_t ret = sys_रुको(status);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
sमाप_प्रकार ग_लिखो(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret = sys_ग_लिखो(fd, buf, count);

	अगर (ret < 0) अणु
		SET_ERRNO(-ret);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

/* some size-optimized reimplementations of a few common str* and mem*
 * functions. They're marked अटल, except स_नकल() and उठाओ() which are used
 * by libgcc on ARM, so they are marked weak instead in order not to cause an
 * error when building a program made of multiple files (not recommended).
 */

अटल __attribute__((unused))
व्योम *स_हटाओ(व्योम *dst, स्थिर व्योम *src, माप_प्रकार len)
अणु
	sमाप_प्रकार pos = (dst <= src) ? -1 : (दीर्घ)len;
	व्योम *ret = dst;

	जबतक (len--) अणु
		pos += (dst <= src) ? 1 : -1;
		((अक्षर *)dst)[pos] = ((अक्षर *)src)[pos];
	पूर्ण
	वापस ret;
पूर्ण

अटल __attribute__((unused))
व्योम *स_रखो(व्योम *dst, पूर्णांक b, माप_प्रकार len)
अणु
	अक्षर *p = dst;

	जबतक (len--)
		*(p++) = b;
	वापस dst;
पूर्ण

अटल __attribute__((unused))
पूर्णांक स_भेद(स्थिर व्योम *s1, स्थिर व्योम *s2, माप_प्रकार n)
अणु
	माप_प्रकार ofs = 0;
	अक्षर c1 = 0;

	जबतक (ofs < n && !(c1 = ((अक्षर *)s1)[ofs] - ((अक्षर *)s2)[ofs])) अणु
		ofs++;
	पूर्ण
	वापस c1;
पूर्ण

अटल __attribute__((unused))
अक्षर *म_नकल(अक्षर *dst, स्थिर अक्षर *src)
अणु
	अक्षर *ret = dst;

	जबतक ((*dst++ = *src++));
	वापस ret;
पूर्ण

अटल __attribute__((unused))
अक्षर *म_अक्षर(स्थिर अक्षर *s, पूर्णांक c)
अणु
	जबतक (*s) अणु
		अगर (*s == (अक्षर)c)
			वापस (अक्षर *)s;
		s++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल __attribute__((unused))
अक्षर *म_खोजप(स्थिर अक्षर *s, पूर्णांक c)
अणु
	स्थिर अक्षर *ret = शून्य;

	जबतक (*s) अणु
		अगर (*s == (अक्षर)c)
			ret = s;
		s++;
	पूर्ण
	वापस (अक्षर *)ret;
पूर्ण

अटल __attribute__((unused))
माप_प्रकार nolibc_म_माप(स्थिर अक्षर *str)
अणु
	माप_प्रकार len;

	क्रम (len = 0; str[len]; len++);
	वापस len;
पूर्ण

#घोषणा म_माप(str) (अणु                          \
	__builtin_स्थिरant_p((str)) ?           \
		__builtin_म_माप((str)) :       \
		nolibc_म_माप((str));           \
पूर्ण)

अटल __attribute__((unused))
पूर्णांक है_अंक(पूर्णांक c)
अणु
	वापस (अचिन्हित पूर्णांक)(c - '0') <= 9;
पूर्ण

अटल __attribute__((unused))
दीर्घ म_से_द(स्थिर अक्षर *s)
अणु
	अचिन्हित दीर्घ ret = 0;
	अचिन्हित दीर्घ d;
	पूर्णांक neg = 0;

	अगर (*s == '-') अणु
		neg = 1;
		s++;
	पूर्ण

	जबतक (1) अणु
		d = (*s++) - '0';
		अगर (d > 9)
			अवरोध;
		ret *= 10;
		ret += d;
	पूर्ण

	वापस neg ? -ret : ret;
पूर्ण

अटल __attribute__((unused))
पूर्णांक म_से_प(स्थिर अक्षर *s)
अणु
	वापस म_से_द(s);
पूर्ण

अटल __attribute__((unused))
स्थिर अक्षर *ltoa(दीर्घ in)
अणु
	/* large enough क्रम -9223372036854775808 */
	अटल अक्षर buffer[21];
	अक्षर       *pos = buffer + माप(buffer) - 1;
	पूर्णांक         neg = in < 0;
	अचिन्हित दीर्घ n = neg ? -in : in;

	*pos-- = '\0';
	करो अणु
		*pos-- = '0' + n % 10;
		n /= 10;
		अगर (pos < buffer)
			वापस pos + 1;
	पूर्ण जबतक (n);

	अगर (neg)
		*pos-- = '-';
	वापस pos + 1;
पूर्ण

__attribute__((weak,unused))
व्योम *स_नकल(व्योम *dst, स्थिर व्योम *src, माप_प्रकार len)
अणु
	वापस स_हटाओ(dst, src, len);
पूर्ण

/* needed by libgcc क्रम भागide by zero */
__attribute__((weak,unused))
पूर्णांक उठाओ(पूर्णांक संकेत)
अणु
	वापस समाप्त(getpid(), संकेत);
पूर्ण

/* Here come a few helper functions */

अटल __attribute__((unused))
व्योम FD_ZERO(fd_set *set)
अणु
	स_रखो(set, 0, माप(*set));
पूर्ण

अटल __attribute__((unused))
व्योम FD_SET(पूर्णांक fd, fd_set *set)
अणु
	अगर (fd < 0 || fd >= FD_SETSIZE)
		वापस;
	set->fd32[fd / 32] |= 1 << (fd & 31);
पूर्ण

/* WARNING, it only deals with the 4096 first majors and 256 first minors */
अटल __attribute__((unused))
dev_t makedev(अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक minor)
अणु
	वापस ((major & 0xfff) << 8) | (minor & 0xff);
पूर्ण
