<शैली गुरु>
/*
 * Copyright (C) 2004 Jeff Dike (jdike@addtoit.com)
 * Licensed under the GPL
 */

#अगर_अघोषित __SYSDEP_STUB_H
#घोषणा __SYSDEP_STUB_H

#समावेश <sysdep/ptrace_user.h>
#समावेश <generated/यंत्र-offsets.h>

#घोषणा STUB_MMAP_NR __NR_mmap
#घोषणा MMAP_OFFSET(o) (o)

#घोषणा __syscall_clobber "r11","rcx","memory"
#घोषणा __syscall "syscall"

अटल अंतरभूत दीर्घ stub_syscall0(दीर्घ syscall)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर (__syscall
		: "=a" (ret)
		: "0" (syscall) : __syscall_clobber );

	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ stub_syscall2(दीर्घ syscall, दीर्घ arg1, दीर्घ arg2)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर (__syscall
		: "=a" (ret)
		: "0" (syscall), "D" (arg1), "S" (arg2) : __syscall_clobber );

	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ stub_syscall3(दीर्घ syscall, दीर्घ arg1, दीर्घ arg2, दीर्घ arg3)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर (__syscall
		: "=a" (ret)
		: "0" (syscall), "D" (arg1), "S" (arg2), "d" (arg3)
		: __syscall_clobber );

	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ stub_syscall4(दीर्घ syscall, दीर्घ arg1, दीर्घ arg2, दीर्घ arg3,
				 दीर्घ arg4)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर ("movq %5,%%r10 ; " __syscall
		: "=a" (ret)
		: "0" (syscall), "D" (arg1), "S" (arg2), "d" (arg3),
		  "g" (arg4)
		: __syscall_clobber, "r10" );

	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ stub_syscall5(दीर्घ syscall, दीर्घ arg1, दीर्घ arg2, दीर्घ arg3,
				 दीर्घ arg4, दीर्घ arg5)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर ("movq %5,%%r10 ; movq %6,%%r8 ; " __syscall
		: "=a" (ret)
		: "0" (syscall), "D" (arg1), "S" (arg2), "d" (arg3),
		  "g" (arg4), "g" (arg5)
		: __syscall_clobber, "r10", "r8" );

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम trap_myself(व्योम)
अणु
	__यंत्र("int3");
पूर्ण

अटल अंतरभूत व्योम remap_stack_and_trap(व्योम)
अणु
	__यंत्र__ अस्थिर (
		"movq %0,%%rax ;"
		"movq %%rsp,%%rdi ;"
		"andq %1,%%rdi ;"
		"movq %2,%%r10 ;"
		"movq %%rdi,%%r8 ; addq %3,%%r8 ; movq (%%r8),%%r8 ;"
		"movq %%rdi,%%r9 ; addq %4,%%r9 ; movq (%%r9),%%r9 ;"
		__syscall ";"
		"movq %%rsp,%%rdi ; andq %1,%%rdi ;"
		"addq %5,%%rdi ; movq %%rax, (%%rdi) ;"
		"int3"
		: :
		"g" (STUB_MMAP_NR),
		"g" (~(UM_KERN_PAGE_SIZE - 1)),
		"g" (MAP_FIXED | MAP_SHARED),
		"g" (UML_STUB_FIELD_FD),
		"g" (UML_STUB_FIELD_OFFSET),
		"g" (UML_STUB_FIELD_CHILD_ERR),
		"S" (UM_KERN_PAGE_SIZE),
		"d" (PROT_READ | PROT_WRITE)
		:
		__syscall_clobber, "r10", "r8", "r9");
पूर्ण

#पूर्ण_अगर
