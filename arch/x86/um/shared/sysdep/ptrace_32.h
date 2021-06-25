<शैली गुरु>
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#अगर_अघोषित __SYSDEP_I386_PTRACE_H
#घोषणा __SYSDEP_I386_PTRACE_H

#घोषणा MAX_FP_NR HOST_FPX_SIZE

व्योम set_using_sysemu(पूर्णांक value);
पूर्णांक get_using_sysemu(व्योम);
बाह्य पूर्णांक sysemu_supported;

#घोषणा UPT_SYSCALL_ARG1(r) UPT_BX(r)
#घोषणा UPT_SYSCALL_ARG2(r) UPT_CX(r)
#घोषणा UPT_SYSCALL_ARG3(r) UPT_DX(r)
#घोषणा UPT_SYSCALL_ARG4(r) UPT_SI(r)
#घोषणा UPT_SYSCALL_ARG5(r) UPT_DI(r)
#घोषणा UPT_SYSCALL_ARG6(r) UPT_BP(r)

बाह्य व्योम arch_init_रेजिस्टरs(पूर्णांक pid);

#पूर्ण_अगर
