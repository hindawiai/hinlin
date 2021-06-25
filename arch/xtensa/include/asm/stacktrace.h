<शैली गुरु>
/*
 * arch/xtensa/include/यंत्र/stacktrace.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 */
#अगर_अघोषित _XTENSA_STACKTRACE_H
#घोषणा _XTENSA_STACKTRACE_H

#समावेश <linux/sched.h>

काष्ठा stackframe अणु
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ sp;
पूर्ण;

अटल __always_अंतरभूत अचिन्हित दीर्घ *stack_poपूर्णांकer(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ *sp;

	अगर (!task || task == current)
		__यंत्र__ __अस्थिर__ ("mov %0, a1\n" : "=a"(sp));
	अन्यथा
		sp = (अचिन्हित दीर्घ *)task->thपढ़ो.sp;

	वापस sp;
पूर्ण

व्योम walk_stackframe(अचिन्हित दीर्घ *sp,
		पूर्णांक (*fn)(काष्ठा stackframe *frame, व्योम *data),
		व्योम *data);

व्योम xtensa_backtrace_kernel(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक depth,
			     पूर्णांक (*kfn)(काष्ठा stackframe *frame, व्योम *data),
			     पूर्णांक (*ufn)(काष्ठा stackframe *frame, व्योम *data),
			     व्योम *data);
व्योम xtensa_backtrace_user(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक depth,
			   पूर्णांक (*ufn)(काष्ठा stackframe *frame, व्योम *data),
			   व्योम *data);

#पूर्ण_अगर /* _XTENSA_STACKTRACE_H */
