<शैली गुरु>
/* 
 * Copyright (C) 2000 - 2008 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#समावेश <यंत्र/unistd.h>
#समावेश <sysdep/ptrace.h>

प्रकार दीर्घ syscall_handler_t(काष्ठा pt_regs);

बाह्य syscall_handler_t *sys_call_table[];

#घोषणा EXECUTE_SYSCALL(syscall, regs) \
	((दीर्घ (*)(काष्ठा syscall_args)) \
	 (*sys_call_table[syscall]))(SYSCALL_ARGS(&regs->regs))
