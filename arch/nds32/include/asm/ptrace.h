<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __ASM_NDS32_PTRACE_H
#घोषणा __ASM_NDS32_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>

/*
 * If pt_regs.syscallno == NO_SYSCALL, then the thपढ़ो is not executing
 * a syscall -- i.e., its most recent entry पूर्णांकo the kernel from
 * userspace was not via syscall, or otherwise a tracer cancelled the
 * syscall.
 *
 * This must have the value -1, क्रम ABI compatibility with ptrace etc.
 */
#घोषणा NO_SYSCALL (-1)
#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

काष्ठा pt_regs अणु
	जोड़ अणु
		काष्ठा user_pt_regs user_regs;
		काष्ठा अणु
			दीर्घ uregs[26];
			दीर्घ fp;
			दीर्घ gp;
			दीर्घ lp;
			दीर्घ sp;
			दीर्घ ipc;
#अगर defined(CONFIG_HWZOL)
			दीर्घ lb;
			दीर्घ le;
			दीर्घ lc;
#अन्यथा
			दीर्घ dummy[3];
#पूर्ण_अगर
			दीर्घ syscallno;
		पूर्ण;
	पूर्ण;
	दीर्घ orig_r0;
	दीर्घ ir0;
	दीर्घ ipsw;
	दीर्घ pipsw;
	दीर्घ pipc;
	दीर्घ pp0;
	दीर्घ pp1;
	दीर्घ fucop_ctl;
	दीर्घ osp;
पूर्ण;

अटल अंतरभूत bool in_syscall(काष्ठा pt_regs स्थिर *regs)
अणु
	वापस regs->syscallno != NO_SYSCALL;
पूर्ण

अटल अंतरभूत व्योम क्रमget_syscall(काष्ठा pt_regs *regs)
अणु
	regs->syscallno = NO_SYSCALL;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->uregs[0];
पूर्ण
बाह्य व्योम show_regs(काष्ठा pt_regs *);
/* Aव्योम circular header include via sched.h */
काष्ठा task_काष्ठा;

#घोषणा arch_has_single_step()		(1)
#घोषणा user_mode(regs)			(((regs)->ipsw & PSW_mskPOM) == 0)
#घोषणा पूर्णांकerrupts_enabled(regs)	(!!((regs)->ipsw & PSW_mskGIE))
#घोषणा user_stack_poपूर्णांकer(regs)	((regs)->sp)
#घोषणा inकाष्ठाion_poपूर्णांकer(regs)	((regs)->ipc)
#घोषणा profile_pc(regs) 		inकाष्ठाion_poपूर्णांकer(regs)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर
