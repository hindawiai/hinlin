<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __PTRACE_USER_H__
#घोषणा __PTRACE_USER_H__

#समावेश <sys/ptrace.h>
#समावेश <sysdep/ptrace_user.h>

बाह्य पूर्णांक ptrace_getregs(दीर्घ pid, अचिन्हित दीर्घ *regs_out);
बाह्य पूर्णांक ptrace_setregs(दीर्घ pid, अचिन्हित दीर्घ *regs_in);

/* syscall emulation path in ptrace */

#अगर_अघोषित PTRACE_SYSEMU
#घोषणा PTRACE_SYSEMU 31
#पूर्ण_अगर
#अगर_अघोषित PTRACE_SYSEMU_SINGLESTEP
#घोषणा PTRACE_SYSEMU_SINGLESTEP 32
#पूर्ण_अगर

/* On architectures, that started to support PTRACE_O_TRACESYSGOOD
 * in linux 2.4, there are two dअगरferent definitions of
 * PTRACE_SETOPTIONS: linux 2.4 uses 21 जबतक linux 2.6 uses 0x4200.
 * For binary compatibility, 2.6 also supports the old "21", named
 * PTRACE_OLDSETOPTION. On these architectures, UML always must use
 * "21", to ensure the kernel runs on 2.4 and 2.6 host without
 * recompilation. So, we use PTRACE_OLDSETOPTIONS in UML.
 * We also want to be able to build the kernel on 2.4, which करोesn't
 * have PTRACE_OLDSETOPTIONS. So, अगर it is missing, we declare
 * PTRACE_OLDSETOPTIONS to be the same as PTRACE_SETOPTIONS.
 *
 * On architectures, that start to support PTRACE_O_TRACESYSGOOD on
 * linux 2.6, PTRACE_OLDSETOPTIONS never is defined, and also isn't
 * supported by the host kernel. In that हाल, our trick lets us use
 * the new 0x4200 with the name PTRACE_OLDSETOPTIONS.
 */
#अगर_अघोषित PTRACE_OLDSETOPTIONS
#घोषणा PTRACE_OLDSETOPTIONS PTRACE_SETOPTIONS
#पूर्ण_अगर

व्योम set_using_sysemu(पूर्णांक value);
पूर्णांक get_using_sysemu(व्योम);
बाह्य पूर्णांक sysemu_supported;

#घोषणा SELECT_PTRACE_OPERATION(sysemu_mode, singlestep_mode) \
	(((पूर्णांक[3][3] ) अणु \
		अणु PTRACE_SYSCALL, PTRACE_SYSCALL, PTRACE_SINGLESTEP पूर्ण, \
		अणु PTRACE_SYSEMU, PTRACE_SYSEMU, PTRACE_SINGLESTEP पूर्ण, \
		अणु PTRACE_SYSEMU, PTRACE_SYSEMU_SINGLESTEP, \
		  PTRACE_SYSEMU_SINGLESTEP पूर्ण पूर्ण) \
		[sysemu_mode][singlestep_mode])

#पूर्ण_अगर
