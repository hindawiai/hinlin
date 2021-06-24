<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __UM_PTRACE_GENERIC_H
#घोषणा __UM_PTRACE_GENERIC_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <sysdep/ptrace.h>

काष्ठा pt_regs अणु
	काष्ठा uml_pt_regs regs;
पूर्ण;

#घोषणा arch_has_single_step()	(1)

#घोषणा EMPTY_REGS अणु .regs = EMPTY_UML_PT_REGS पूर्ण

#घोषणा PT_REGS_IP(r) UPT_IP(&(r)->regs)
#घोषणा PT_REGS_SP(r) UPT_SP(&(r)->regs)

#घोषणा PT_REGS_RESTART_SYSCALL(r) UPT_RESTART_SYSCALL(&(r)->regs)

#घोषणा PT_REGS_SYSCALL_NR(r) UPT_SYSCALL_NR(&(r)->regs)

#घोषणा inकाष्ठाion_poपूर्णांकer(regs) PT_REGS_IP(regs)

#घोषणा PTRACE_OLDSETOPTIONS 21

काष्ठा task_काष्ठा;

बाह्य दीर्घ subarch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
	अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data);
बाह्य अचिन्हित दीर्घ getreg(काष्ठा task_काष्ठा *child, पूर्णांक regno);
बाह्य पूर्णांक putreg(काष्ठा task_काष्ठा *child, पूर्णांक regno, अचिन्हित दीर्घ value);

बाह्य पूर्णांक arch_set_tls(काष्ठा task_काष्ठा *new, अचिन्हित दीर्घ tls);
बाह्य व्योम clear_flushed_tls(काष्ठा task_काष्ठा *task);
बाह्य पूर्णांक syscall_trace_enter(काष्ठा pt_regs *regs);
बाह्य व्योम syscall_trace_leave(काष्ठा pt_regs *regs);

#पूर्ण_अगर

#पूर्ण_अगर
