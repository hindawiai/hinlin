<शैली गुरु>
/*
 * Copyright 2003 PathScale, Inc.
 *
 * Licensed under the GPL
 */

#अगर_अघोषित __SYSDEP_X86_64_SYSCALLS_H__
#घोषणा __SYSDEP_X86_64_SYSCALLS_H__

#समावेश <linux/msg.h>
#समावेश <linux/shm.h>

प्रकार दीर्घ syscall_handler_t(व्योम);

बाह्य syscall_handler_t *sys_call_table[];

#घोषणा EXECUTE_SYSCALL(syscall, regs) \
	(((दीर्घ (*)(दीर्घ, दीर्घ, दीर्घ, दीर्घ, दीर्घ, दीर्घ)) \
	  (*sys_call_table[syscall]))(UPT_SYSCALL_ARG1(&regs->regs), \
		 		      UPT_SYSCALL_ARG2(&regs->regs), \
				      UPT_SYSCALL_ARG3(&regs->regs), \
				      UPT_SYSCALL_ARG4(&regs->regs), \
				      UPT_SYSCALL_ARG5(&regs->regs), \
				      UPT_SYSCALL_ARG6(&regs->regs)))

बाह्य दीर्घ old_mmap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		     अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
		     अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff);
बाह्य syscall_handler_t sys_modअगरy_ldt;
बाह्य syscall_handler_t sys_arch_prctl;

#पूर्ण_अगर
