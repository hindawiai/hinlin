<शैली गुरु>
/*
 * Copyright 2003 PathScale, Inc.
 * Copyright (C) 2003 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 *
 * Licensed under the GPL
 */

#अगर_अघोषित __SYSDEP_X86_64_PTRACE_H
#घोषणा __SYSDEP_X86_64_PTRACE_H

#घोषणा MAX_FP_NR HOST_FP_SIZE

#घोषणा REGS_R8(r) ((r)[HOST_R8])
#घोषणा REGS_R9(r) ((r)[HOST_R9])
#घोषणा REGS_R10(r) ((r)[HOST_R10])
#घोषणा REGS_R11(r) ((r)[HOST_R11])
#घोषणा REGS_R12(r) ((r)[HOST_R12])
#घोषणा REGS_R13(r) ((r)[HOST_R13])
#घोषणा REGS_R14(r) ((r)[HOST_R14])
#घोषणा REGS_R15(r) ((r)[HOST_R15])

#घोषणा HOST_FS_BASE 21
#घोषणा HOST_GS_BASE 22
#घोषणा HOST_DS 23
#घोषणा HOST_ES 24
#घोषणा HOST_FS 25
#घोषणा HOST_GS 26

/* Also defined in यंत्र/ptrace-x86_64.h, but not in libc headers.  So, these
 * are alपढ़ोy defined क्रम kernel code, but not क्रम userspace code.
 */
#अगर_अघोषित FS_BASE
/* These aren't defined in ptrace.h, but exist in काष्ठा user_regs_काष्ठा,
 * which is what x86_64 ptrace actually uses.
 */
#घोषणा FS_BASE (HOST_FS_BASE * माप(दीर्घ))
#घोषणा GS_BASE (HOST_GS_BASE * माप(दीर्घ))
#घोषणा DS (HOST_DS * माप(दीर्घ))
#घोषणा ES (HOST_ES * माप(दीर्घ))
#घोषणा FS (HOST_FS * माप(दीर्घ))
#घोषणा GS (HOST_GS * माप(दीर्घ))
#पूर्ण_अगर

#घोषणा UPT_R8(r) REGS_R8((r)->gp)
#घोषणा UPT_R9(r) REGS_R9((r)->gp)
#घोषणा UPT_R10(r) REGS_R10((r)->gp)
#घोषणा UPT_R11(r) REGS_R11((r)->gp)
#घोषणा UPT_R12(r) REGS_R12((r)->gp)
#घोषणा UPT_R13(r) REGS_R13((r)->gp)
#घोषणा UPT_R14(r) REGS_R14((r)->gp)
#घोषणा UPT_R15(r) REGS_R15((r)->gp)

#घोषणा UPT_SYSCALL_ARG1(r) UPT_DI(r)
#घोषणा UPT_SYSCALL_ARG2(r) UPT_SI(r)
#घोषणा UPT_SYSCALL_ARG3(r) UPT_DX(r)
#घोषणा UPT_SYSCALL_ARG4(r) UPT_R10(r)
#घोषणा UPT_SYSCALL_ARG5(r) UPT_R8(r)
#घोषणा UPT_SYSCALL_ARG6(r) UPT_R9(r)

बाह्य व्योम arch_init_रेजिस्टरs(पूर्णांक pid);

#पूर्ण_अगर
