<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_H8300_SYSCALLS_32_H
#घोषणा __ASM_H8300_SYSCALLS_32_H

#अगर_घोषित __KERNEL__

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <uapi/linux/audit.h>

अटल अंतरभूत पूर्णांक
syscall_get_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs->orig_er0;
पूर्ण

अटल अंतरभूत व्योम
syscall_get_arguments(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		      अचिन्हित दीर्घ *args)
अणु
	*args++ = regs->er1;
	*args++ = regs->er2;
	*args++ = regs->er3;
	*args++ = regs->er4;
	*args++ = regs->er5;
	*args   = regs->er6;
पूर्ण

अटल अंतरभूत पूर्णांक
syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस AUDIT_ARCH_H8300;
पूर्ण


/* Misc syscall related bits */
यंत्रlinkage दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASM_H8300_SYSCALLS_32_H */
