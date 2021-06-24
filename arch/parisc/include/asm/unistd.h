<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_UNISTD_H_
#घोषणा _ASM_PARISC_UNISTD_H_

#समावेश <uapi/यंत्र/unistd.h>

#घोषणा __NR_Linux_syscalls	__NR_syscalls

#अगर_अघोषित __ASSEMBLY__

#घोषणा SYS_अगरy(syscall_name)   __NR_##syscall_name

#घोषणा __IGNORE_fadvise64		/* fadvise64_64 */

#अगर_अघोषित ASM_LINE_SEP
# define ASM_LINE_SEP ;
#पूर्ण_अगर

/* Definition taken from glibc 2.3.3
 * sysdeps/unix/sysv/linux/hppa/sysdep.h
 */

#अगर_घोषित PIC
/* WARNING: CANNOT BE USED IN A NOP! */
# define K_STW_ASM_PIC	"       copy %%r19, %%r4\n"
# define K_LDW_ASM_PIC	"       copy %%r4, %%r19\n"
# define K_USING_GR4	"%r4",
#अन्यथा
# define K_STW_ASM_PIC	" \n"
# define K_LDW_ASM_PIC	" \n"
# define K_USING_GR4
#पूर्ण_अगर

/* GCC has to be warned that a syscall may clobber all the ABI
   रेजिस्टरs listed as "caller-saves", see page 8, Table 2
   in section 2.2.6 of the PA-RISC RUN-TIME architecture
   करोcument. However! r28 is the result and will conflict with
   the clobber list so it is left out. Also the input arguments
   रेजिस्टरs r20 -> r26 will conflict with the list so they
   are treated specially. Although r19 is clobbered by the syscall
   we cannot say this because it would violate ABI, thus we say
   r4 is clobbered and use that रेजिस्टर to save/restore r19
   across the syscall. */

#घोषणा K_CALL_CLOB_REGS "%r1", "%r2", K_USING_GR4 \
	        	 "%r20", "%r29", "%r31"

#अघोषित K_INLINE_SYSCALL
#घोषणा K_INLINE_SYSCALL(name, nr, args...)	(अणु			\
	दीर्घ __sys_res;							\
	अणु								\
		रेजिस्टर अचिन्हित दीर्घ __res __यंत्र__("r28");		\
		K_LOAD_ARGS_##nr(args)					\
		/* FIXME: HACK stw/ldw r19 around syscall */		\
		__यंत्र__ अस्थिर(					\
			K_STW_ASM_PIC					\
			"	ble  0x100(%%sr2, %%r0)\n"		\
			"	ldi %1, %%r20\n"			\
			K_LDW_ASM_PIC					\
			: "=r" (__res)					\
			: "i" (SYS_अगरy(name)) K_ASM_ARGS_##nr   	\
			: "memory", K_CALL_CLOB_REGS K_CLOB_ARGS_##nr	\
		);							\
		__sys_res = (दीर्घ)__res;				\
	पूर्ण								\
	अगर ( (अचिन्हित दीर्घ)__sys_res >= (अचिन्हित दीर्घ)-4095 )अणु	\
		त्रुटि_सं = -__sys_res;		        		\
		__sys_res = -1;						\
	पूर्ण								\
	__sys_res;							\
पूर्ण)

#घोषणा K_LOAD_ARGS_0()
#घोषणा K_LOAD_ARGS_1(r26)					\
	रेजिस्टर अचिन्हित दीर्घ __r26 __यंत्र__("r26") = (अचिन्हित दीर्घ)(r26);   \
	K_LOAD_ARGS_0()
#घोषणा K_LOAD_ARGS_2(r26,r25)					\
	रेजिस्टर अचिन्हित दीर्घ __r25 __यंत्र__("r25") = (अचिन्हित दीर्घ)(r25);   \
	K_LOAD_ARGS_1(r26)
#घोषणा K_LOAD_ARGS_3(r26,r25,r24)				\
	रेजिस्टर अचिन्हित दीर्घ __r24 __यंत्र__("r24") = (अचिन्हित दीर्घ)(r24);   \
	K_LOAD_ARGS_2(r26,r25)
#घोषणा K_LOAD_ARGS_4(r26,r25,r24,r23)				\
	रेजिस्टर अचिन्हित दीर्घ __r23 __यंत्र__("r23") = (अचिन्हित दीर्घ)(r23);   \
	K_LOAD_ARGS_3(r26,r25,r24)
#घोषणा K_LOAD_ARGS_5(r26,r25,r24,r23,r22)			\
	रेजिस्टर अचिन्हित दीर्घ __r22 __यंत्र__("r22") = (अचिन्हित दीर्घ)(r22);   \
	K_LOAD_ARGS_4(r26,r25,r24,r23)
#घोषणा K_LOAD_ARGS_6(r26,r25,r24,r23,r22,r21)			\
	रेजिस्टर अचिन्हित दीर्घ __r21 __यंत्र__("r21") = (अचिन्हित दीर्घ)(r21);   \
	K_LOAD_ARGS_5(r26,r25,r24,r23,r22)

/* Even with zero args we use r20 क्रम the syscall number */
#घोषणा K_ASM_ARGS_0
#घोषणा K_ASM_ARGS_1 K_ASM_ARGS_0, "r" (__r26)
#घोषणा K_ASM_ARGS_2 K_ASM_ARGS_1, "r" (__r25)
#घोषणा K_ASM_ARGS_3 K_ASM_ARGS_2, "r" (__r24)
#घोषणा K_ASM_ARGS_4 K_ASM_ARGS_3, "r" (__r23)
#घोषणा K_ASM_ARGS_5 K_ASM_ARGS_4, "r" (__r22)
#घोषणा K_ASM_ARGS_6 K_ASM_ARGS_5, "r" (__r21)

/* The रेजिस्टरs not listed as inमाला_दो but clobbered */
#घोषणा K_CLOB_ARGS_6
#घोषणा K_CLOB_ARGS_5 K_CLOB_ARGS_6, "%r21"
#घोषणा K_CLOB_ARGS_4 K_CLOB_ARGS_5, "%r22"
#घोषणा K_CLOB_ARGS_3 K_CLOB_ARGS_4, "%r23"
#घोषणा K_CLOB_ARGS_2 K_CLOB_ARGS_3, "%r24"
#घोषणा K_CLOB_ARGS_1 K_CLOB_ARGS_2, "%r25"
#घोषणा K_CLOB_ARGS_0 K_CLOB_ARGS_1, "%r26"

#घोषणा _syscall0(type,name)						\
type name(व्योम)								\
अणु									\
    वापस K_INLINE_SYSCALL(name, 0);	                                \
पूर्ण

#घोषणा _syscall1(type,name,type1,arg1)					\
type name(type1 arg1)							\
अणु									\
    वापस K_INLINE_SYSCALL(name, 1, arg1);	                        \
पूर्ण

#घोषणा _syscall2(type,name,type1,arg1,type2,arg2)			\
type name(type1 arg1, type2 arg2)					\
अणु									\
    वापस K_INLINE_SYSCALL(name, 2, arg1, arg2);	                \
पूर्ण

#घोषणा _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)		\
type name(type1 arg1, type2 arg2, type3 arg3)				\
अणु									\
    वापस K_INLINE_SYSCALL(name, 3, arg1, arg2, arg3);	                \
पूर्ण

#घोषणा _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) \
type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4)		\
अणु									\
    वापस K_INLINE_SYSCALL(name, 4, arg1, arg2, arg3, arg4);	        \
पूर्ण

/* select takes 5 arguments */
#घोषणा _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5) \
type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5)	\
अणु									\
    वापस K_INLINE_SYSCALL(name, 5, arg1, arg2, arg3, arg4, arg5);	\
पूर्ण

#घोषणा __ARCH_WANT_NEW_STAT
#घोषणा __ARCH_WANT_OLD_READसूची
#घोषणा __ARCH_WANT_STAT64
#घोषणा __ARCH_WANT_SYS_ALARM
#घोषणा __ARCH_WANT_SYS_GETHOSTNAME
#घोषणा __ARCH_WANT_SYS_PAUSE
#घोषणा __ARCH_WANT_SYS_SIGNAL
#घोषणा __ARCH_WANT_SYS_TIME32
#घोषणा __ARCH_WANT_COMPAT_SYS_SCHED_RR_GET_INTERVAL
#घोषणा __ARCH_WANT_SYS_UTIME32
#घोषणा __ARCH_WANT_SYS_WAITPID
#घोषणा __ARCH_WANT_SYS_SOCKETCALL
#घोषणा __ARCH_WANT_SYS_FADVISE64
#घोषणा __ARCH_WANT_SYS_GETPGRP
#घोषणा __ARCH_WANT_SYS_NICE
#घोषणा __ARCH_WANT_SYS_OLDUMOUNT
#घोषणा __ARCH_WANT_SYS_SIGPENDING
#घोषणा __ARCH_WANT_SYS_SIGPROCMASK
#घोषणा __ARCH_WANT_SYS_FORK
#घोषणा __ARCH_WANT_SYS_VFORK
#घोषणा __ARCH_WANT_SYS_CLONE
#घोषणा __ARCH_WANT_SYS_CLONE3
#घोषणा __ARCH_WANT_COMPAT_SYS_SENDखाता

#अगर_घोषित CONFIG_64BIT
#घोषणा __ARCH_WANT_SYS_TIME
#घोषणा __ARCH_WANT_SYS_UTIME
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#अघोषित STR

#पूर्ण_अगर /* _ASM_PARISC_UNISTD_H_ */
