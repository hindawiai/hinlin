<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <generated/user_स्थिरants.h>

#घोषणा PT_OFFSET(r) ((r) * माप(दीर्घ))

#घोषणा PT_SYSCALL_NR(regs) ((regs)[HOST_ORIG_AX])
#घोषणा PT_SYSCALL_NR_OFFSET PT_OFFSET(HOST_ORIG_AX)

#घोषणा PT_SYSCALL_RET_OFFSET PT_OFFSET(HOST_AX)

#घोषणा REGS_IP_INDEX HOST_IP
#घोषणा REGS_SP_INDEX HOST_SP

#अगर_घोषित __i386__
#घोषणा FP_SIZE ((HOST_FPX_SIZE > HOST_FP_SIZE) ? HOST_FPX_SIZE : HOST_FP_SIZE)
#अन्यथा
#घोषणा FP_SIZE HOST_FP_SIZE

/*
 * x86_64 FC3 करोesn't define this in /usr/include/linux/ptrace.h even though
 * it's defined in the kernel's include/linux/ptrace.h. Additionally, use the
 * 2.4 name and value क्रम 2.4 host compatibility.
 */
#अगर_अघोषित PTRACE_OLDSETOPTIONS
#घोषणा PTRACE_OLDSETOPTIONS 21
#पूर्ण_अगर

#पूर्ण_अगर
