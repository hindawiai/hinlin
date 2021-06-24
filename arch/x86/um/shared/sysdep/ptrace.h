<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SYSDEP_X86_PTRACE_H
#घोषणा __SYSDEP_X86_PTRACE_H

#समावेश <generated/user_स्थिरants.h>
#समावेश <sysdep/faultinfo.h>

#घोषणा MAX_REG_OFFSET (UM_FRAME_SIZE)
#घोषणा MAX_REG_NR ((MAX_REG_OFFSET) / माप(अचिन्हित दीर्घ))

#घोषणा REGS_IP(r) ((r)[HOST_IP])
#घोषणा REGS_SP(r) ((r)[HOST_SP])
#घोषणा REGS_EFLAGS(r) ((r)[HOST_EFLAGS])
#घोषणा REGS_AX(r) ((r)[HOST_AX])
#घोषणा REGS_BX(r) ((r)[HOST_BX])
#घोषणा REGS_CX(r) ((r)[HOST_CX])
#घोषणा REGS_DX(r) ((r)[HOST_DX])
#घोषणा REGS_SI(r) ((r)[HOST_SI])
#घोषणा REGS_DI(r) ((r)[HOST_DI])
#घोषणा REGS_BP(r) ((r)[HOST_BP])
#घोषणा REGS_CS(r) ((r)[HOST_CS])
#घोषणा REGS_SS(r) ((r)[HOST_SS])
#घोषणा REGS_DS(r) ((r)[HOST_DS])
#घोषणा REGS_ES(r) ((r)[HOST_ES])

#घोषणा UPT_IP(r) REGS_IP((r)->gp)
#घोषणा UPT_SP(r) REGS_SP((r)->gp)
#घोषणा UPT_EFLAGS(r) REGS_EFLAGS((r)->gp)
#घोषणा UPT_AX(r) REGS_AX((r)->gp)
#घोषणा UPT_BX(r) REGS_BX((r)->gp)
#घोषणा UPT_CX(r) REGS_CX((r)->gp)
#घोषणा UPT_DX(r) REGS_DX((r)->gp)
#घोषणा UPT_SI(r) REGS_SI((r)->gp)
#घोषणा UPT_DI(r) REGS_DI((r)->gp)
#घोषणा UPT_BP(r) REGS_BP((r)->gp)
#घोषणा UPT_CS(r) REGS_CS((r)->gp)
#घोषणा UPT_SS(r) REGS_SS((r)->gp)
#घोषणा UPT_DS(r) REGS_DS((r)->gp)
#घोषणा UPT_ES(r) REGS_ES((r)->gp)

#अगर_घोषित __i386__
#समावेश "ptrace_32.h"
#अन्यथा
#समावेश "ptrace_64.h"
#पूर्ण_अगर

काष्ठा syscall_args अणु
	अचिन्हित दीर्घ args[6];
पूर्ण;

#घोषणा SYSCALL_ARGS(r) ((काष्ठा syscall_args) \
			 अणु .args = अणु UPT_SYSCALL_ARG1(r),	 \
				     UPT_SYSCALL_ARG2(r),	 \
				     UPT_SYSCALL_ARG3(r),	 \
				     UPT_SYSCALL_ARG4(r),	 \
				     UPT_SYSCALL_ARG5(r),	 \
				     UPT_SYSCALL_ARG6(r) पूर्ण पूर्ण )

काष्ठा uml_pt_regs अणु
	अचिन्हित दीर्घ gp[MAX_REG_NR];
	अचिन्हित दीर्घ fp[MAX_FP_NR];
	काष्ठा faultinfo faultinfo;
	दीर्घ syscall;
	पूर्णांक is_user;
पूर्ण;

#घोषणा EMPTY_UML_PT_REGS अणु पूर्ण

#घोषणा UPT_SYSCALL_NR(r) ((r)->syscall)
#घोषणा UPT_FAULTINFO(r) (&(r)->faultinfo)
#घोषणा UPT_IS_USER(r) ((r)->is_user)

बाह्य पूर्णांक user_context(अचिन्हित दीर्घ sp);

#पूर्ण_अगर /* __SYSDEP_X86_PTRACE_H */
