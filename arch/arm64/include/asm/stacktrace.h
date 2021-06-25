<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_STACKTRACE_H
#घोषणा __ASM_STACKTRACE_H

#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sdei.h>

क्रमागत stack_type अणु
	STACK_TYPE_UNKNOWN,
	STACK_TYPE_TASK,
	STACK_TYPE_IRQ,
	STACK_TYPE_OVERFLOW,
	STACK_TYPE_SDEI_NORMAL,
	STACK_TYPE_SDEI_CRITICAL,
	__NR_STACK_TYPES
पूर्ण;

काष्ठा stack_info अणु
	अचिन्हित दीर्घ low;
	अचिन्हित दीर्घ high;
	क्रमागत stack_type type;
पूर्ण;

/*
 * A snapshot of a frame record or fp/lr रेजिस्टर values, aदीर्घ with some
 * accounting inक्रमmation necessary क्रम robust unwinding.
 *
 * @fp:          The fp value in the frame record (or the real fp)
 * @pc:          The fp value in the frame record (or the real lr)
 *
 * @stacks_करोne: Stacks which have been entirely unwound, क्रम which it is no
 *               दीर्घer valid to unwind to.
 *
 * @prev_fp:     The fp that poपूर्णांकed to this frame record, or a synthetic value
 *               of 0. This is used to ensure that within a stack, each
 *               subsequent frame record is at an increasing address.
 * @prev_type:   The type of stack this frame record was on, or a synthetic
 *               value of STACK_TYPE_UNKNOWN. This is used to detect a
 *               transition from one stack to another.
 *
 * @graph:       When FUNCTION_GRAPH_TRACER is selected, holds the index of a
 *               replacement lr value in the ftrace graph stack.
 */
काष्ठा stackframe अणु
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ pc;
	DECLARE_BITMAP(stacks_करोne, __NR_STACK_TYPES);
	अचिन्हित दीर्घ prev_fp;
	क्रमागत stack_type prev_type;
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	पूर्णांक graph;
#पूर्ण_अगर
पूर्ण;

बाह्य पूर्णांक unwind_frame(काष्ठा task_काष्ठा *tsk, काष्ठा stackframe *frame);
बाह्य व्योम walk_stackframe(काष्ठा task_काष्ठा *tsk, काष्ठा stackframe *frame,
			    bool (*fn)(व्योम *, अचिन्हित दीर्घ), व्योम *data);
बाह्य व्योम dump_backtrace(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *tsk,
			   स्थिर अक्षर *loglvl);

DECLARE_PER_CPU(अचिन्हित दीर्घ *, irq_stack_ptr);

अटल अंतरभूत bool on_stack(अचिन्हित दीर्घ sp, अचिन्हित दीर्घ low,
				अचिन्हित दीर्घ high, क्रमागत stack_type type,
				काष्ठा stack_info *info)
अणु
	अगर (!low)
		वापस false;

	अगर (sp < low || sp >= high)
		वापस false;

	अगर (info) अणु
		info->low = low;
		info->high = high;
		info->type = type;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत bool on_irq_stack(अचिन्हित दीर्घ sp,
				काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ low = (अचिन्हित दीर्घ)raw_cpu_पढ़ो(irq_stack_ptr);
	अचिन्हित दीर्घ high = low + IRQ_STACK_SIZE;

	वापस on_stack(sp, low, high, STACK_TYPE_IRQ, info);
पूर्ण

अटल अंतरभूत bool on_task_stack(स्थिर काष्ठा task_काष्ठा *tsk,
				 अचिन्हित दीर्घ sp,
				 काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ low = (अचिन्हित दीर्घ)task_stack_page(tsk);
	अचिन्हित दीर्घ high = low + THREAD_SIZE;

	वापस on_stack(sp, low, high, STACK_TYPE_TASK, info);
पूर्ण

#अगर_घोषित CONFIG_VMAP_STACK
DECLARE_PER_CPU(अचिन्हित दीर्घ [OVERFLOW_STACK_SIZE/माप(दीर्घ)], overflow_stack);

अटल अंतरभूत bool on_overflow_stack(अचिन्हित दीर्घ sp,
				काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ low = (अचिन्हित दीर्घ)raw_cpu_ptr(overflow_stack);
	अचिन्हित दीर्घ high = low + OVERFLOW_STACK_SIZE;

	वापस on_stack(sp, low, high, STACK_TYPE_OVERFLOW, info);
पूर्ण
#अन्यथा
अटल अंतरभूत bool on_overflow_stack(अचिन्हित दीर्घ sp,
			काष्ठा stack_info *info) अणु वापस false; पूर्ण
#पूर्ण_अगर


/*
 * We can only safely access per-cpu stacks from current in a non-preemptible
 * context.
 */
अटल अंतरभूत bool on_accessible_stack(स्थिर काष्ठा task_काष्ठा *tsk,
				       अचिन्हित दीर्घ sp,
				       काष्ठा stack_info *info)
अणु
	अगर (info)
		info->type = STACK_TYPE_UNKNOWN;

	अगर (on_task_stack(tsk, sp, info))
		वापस true;
	अगर (tsk != current || preemptible())
		वापस false;
	अगर (on_irq_stack(sp, info))
		वापस true;
	अगर (on_overflow_stack(sp, info))
		वापस true;
	अगर (on_sdei_stack(sp, info))
		वापस true;

	वापस false;
पूर्ण

व्योम start_backtrace(काष्ठा stackframe *frame, अचिन्हित दीर्घ fp,
		     अचिन्हित दीर्घ pc);

#पूर्ण_अगर	/* __ASM_STACKTRACE_H */
