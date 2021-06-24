<शैली गुरु>
/*
 * Copyright (C) 2004 Jeff Dike (jdike@addtoit.com)
 * Licensed under the GPL
 */

#अगर_अघोषित __SYSDEP_STUB_H
#घोषणा __SYSDEP_STUB_H

#समावेश <यंत्र/ptrace.h>
#समावेश <generated/यंत्र-offsets.h>

#घोषणा STUB_MMAP_NR __NR_mmap2
#घोषणा MMAP_OFFSET(o) ((o) >> UM_KERN_PAGE_SHIFT)

अटल अंतरभूत दीर्घ stub_syscall0(दीर्घ syscall)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर ("int $0x80" : "=a" (ret) : "0" (syscall));

	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ stub_syscall1(दीर्घ syscall, दीर्घ arg1)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1));

	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ stub_syscall2(दीर्घ syscall, दीर्घ arg1, दीर्घ arg2)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1),
			"c" (arg2));

	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ stub_syscall3(दीर्घ syscall, दीर्घ arg1, दीर्घ arg2, दीर्घ arg3)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1),
			"c" (arg2), "d" (arg3));

	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ stub_syscall4(दीर्घ syscall, दीर्घ arg1, दीर्घ arg2, दीर्घ arg3,
				 दीर्घ arg4)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1),
			"c" (arg2), "d" (arg3), "S" (arg4));

	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ stub_syscall5(दीर्घ syscall, दीर्घ arg1, दीर्घ arg2, दीर्घ arg3,
				 दीर्घ arg4, दीर्घ arg5)
अणु
	दीर्घ ret;

	__यंत्र__ अस्थिर ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1),
			"c" (arg2), "d" (arg3), "S" (arg4), "D" (arg5));

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम trap_myself(व्योम)
अणु
	__यंत्र("int3");
पूर्ण

अटल अंतरभूत व्योम remap_stack_and_trap(व्योम)
अणु
	__यंत्र__ अस्थिर (
		"movl %%esp,%%ebx ;"
		"andl %0,%%ebx ;"
		"movl %1,%%eax ;"
		"movl %%ebx,%%edi ; addl %2,%%edi ; movl (%%edi),%%edi ;"
		"movl %%ebx,%%ebp ; addl %3,%%ebp ; movl (%%ebp),%%ebp ;"
		"int $0x80 ;"
		"addl %4,%%ebx ; movl %%eax, (%%ebx) ;"
		"int $3"
		: :
		"g" (~(UM_KERN_PAGE_SIZE - 1)),
		"g" (STUB_MMAP_NR),
		"g" (UML_STUB_FIELD_FD),
		"g" (UML_STUB_FIELD_OFFSET),
		"g" (UML_STUB_FIELD_CHILD_ERR),
		"c" (UM_KERN_PAGE_SIZE),
		"d" (PROT_READ | PROT_WRITE),
		"S" (MAP_FIXED | MAP_SHARED)
		:
		"memory");
पूर्ण

#पूर्ण_अगर
