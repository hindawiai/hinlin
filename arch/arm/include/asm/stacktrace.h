<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_STACKTRACE_H
#घोषणा __ASM_STACKTRACE_H

#समावेश <यंत्र/ptrace.h>

काष्ठा stackframe अणु
	/*
	 * FP member should hold R7 when CONFIG_THUMB2_KERNEL is enabled
	 * and R11 otherwise.
	 */
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ lr;
	अचिन्हित दीर्घ pc;
पूर्ण;

अटल __always_अंतरभूत
व्योम arm_get_current_stackframe(काष्ठा pt_regs *regs, काष्ठा stackframe *frame)
अणु
		frame->fp = frame_poपूर्णांकer(regs);
		frame->sp = regs->ARM_sp;
		frame->lr = regs->ARM_lr;
		frame->pc = regs->ARM_pc;
पूर्ण

बाह्य पूर्णांक unwind_frame(काष्ठा stackframe *frame);
बाह्य व्योम walk_stackframe(काष्ठा stackframe *frame,
			    पूर्णांक (*fn)(काष्ठा stackframe *, व्योम *), व्योम *data);

#पूर्ण_अगर	/* __ASM_STACKTRACE_H */
