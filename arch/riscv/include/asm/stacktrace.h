<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_RISCV_STACKTRACE_H
#घोषणा _ASM_RISCV_STACKTRACE_H

#समावेश <linux/sched.h>
#समावेश <यंत्र/ptrace.h>

काष्ठा stackframe अणु
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ ra;
पूर्ण;

बाह्य व्योम notrace walk_stackframe(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
				    bool (*fn)(व्योम *, अचिन्हित दीर्घ), व्योम *arg);
बाह्य व्योम dump_backtrace(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *task,
			   स्थिर अक्षर *loglvl);

#पूर्ण_अगर /* _ASM_RISCV_STACKTRACE_H */
