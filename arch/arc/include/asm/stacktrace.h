<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 * Copyright (C) 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_STACKTRACE_H
#घोषणा __ASM_STACKTRACE_H

#समावेश <linux/sched.h>

/**
 * arc_unwind_core - Unwind the kernel mode stack क्रम an execution context
 * @tsk:		शून्य क्रम current task, specअगरic task otherwise
 * @regs:		pt_regs used to seed the unwinder अणुSP, FP, BLINK, PCपूर्ण
 * 			If शून्य, use pt_regs of @tsk (अगर !शून्य) otherwise
 * 			use the current values of अणुSP, FP, BLINK, PCपूर्ण
 * @consumer_fn:	Callback invoked क्रम each frame unwound
 * 			Returns 0 to जारी unwinding, -1 to stop
 * @arg:		Arg to callback
 *
 * Returns the address of first function in stack
 *
 * Semantics:
 *  - synchronous unwinding (e.g. dump_stack): @tsk  शून्य, @regs  शून्य
 *  - Asynchronous unwinding of sleeping task: @tsk !शून्य, @regs  शून्य
 *  - Asynchronous unwinding of पूर्णांकr/excp etc: @tsk !शून्य, @regs !शून्य
 */
notrace noअंतरभूत अचिन्हित पूर्णांक arc_unwind_core(
	काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs,
	पूर्णांक (*consumer_fn) (अचिन्हित पूर्णांक, व्योम *),
	व्योम *arg);

#पूर्ण_अगर /* __ASM_STACKTRACE_H */
