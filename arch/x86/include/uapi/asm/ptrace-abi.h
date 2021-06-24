<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_X86_PTRACE_ABI_H
#घोषणा _ASM_X86_PTRACE_ABI_H

#अगर_घोषित __i386__

#घोषणा EBX 0
#घोषणा ECX 1
#घोषणा EDX 2
#घोषणा ESI 3
#घोषणा EDI 4
#घोषणा EBP 5
#घोषणा EAX 6
#घोषणा DS 7
#घोषणा ES 8
#घोषणा FS 9
#घोषणा GS 10
#घोषणा ORIG_EAX 11
#घोषणा EIP 12
#घोषणा CS  13
#घोषणा EFL 14
#घोषणा UESP 15
#घोषणा SS   16
#घोषणा FRAME_SIZE 17

#अन्यथा /* __i386__ */

#अगर defined(__ASSEMBLY__) || defined(__FRAME_OFFSETS)
/*
 * C ABI says these regs are callee-preserved. They aren't saved on kernel entry
 * unless syscall needs a complete, fully filled "struct pt_regs".
 */
#घोषणा R15 0
#घोषणा R14 8
#घोषणा R13 16
#घोषणा R12 24
#घोषणा RBP 32
#घोषणा RBX 40
/* These regs are callee-clobbered. Always saved on kernel entry. */
#घोषणा R11 48
#घोषणा R10 56
#घोषणा R9 64
#घोषणा R8 72
#घोषणा RAX 80
#घोषणा RCX 88
#घोषणा RDX 96
#घोषणा RSI 104
#घोषणा RDI 112
/*
 * On syscall entry, this is syscall#. On CPU exception, this is error code.
 * On hw पूर्णांकerrupt, it's IRQ number:
 */
#घोषणा ORIG_RAX 120
/* Return frame क्रम iretq */
#घोषणा RIP 128
#घोषणा CS 136
#घोषणा EFLAGS 144
#घोषणा RSP 152
#घोषणा SS 160
#पूर्ण_अगर /* __ASSEMBLY__ */

/* top of stack page */
#घोषणा FRAME_SIZE 168

#पूर्ण_अगर /* !__i386__ */

/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
#घोषणा PTRACE_GETREGS            12
#घोषणा PTRACE_SETREGS            13
#घोषणा PTRACE_GETFPREGS          14
#घोषणा PTRACE_SETFPREGS          15
#घोषणा PTRACE_GETFPXREGS         18
#घोषणा PTRACE_SETFPXREGS         19

#घोषणा PTRACE_OLDSETOPTIONS      21

/* only useful क्रम access 32bit programs / kernels */
#घोषणा PTRACE_GET_THREAD_AREA    25
#घोषणा PTRACE_SET_THREAD_AREA    26

#अगर_घोषित __x86_64__
# define PTRACE_ARCH_PRCTL	  30
#पूर्ण_अगर

#घोषणा PTRACE_SYSEMU		  31
#घोषणा PTRACE_SYSEMU_SINGLESTEP  32

#घोषणा PTRACE_SINGLEBLOCK	33	/* resume execution until next branch */

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_PTRACE_ABI_H */
