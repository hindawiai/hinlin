<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright (C) 2013 Riअक्षरd Weinberger <richrd@nod.at>
 */

#समावेश <linux/kallsyms.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/sysrq.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <os.h>

अटल व्योम _prपूर्णांक_addr(व्योम *data, अचिन्हित दीर्घ address, पूर्णांक reliable)
अणु
	स्थिर अक्षर *loglvl = data;

	prपूर्णांकk("%s [<%08lx>] %s%pS\n", loglvl, address, reliable ? "" : "? ",
		(व्योम *)address);
पूर्ण

अटल स्थिर काष्ठा stacktrace_ops stackops = अणु
	.address = _prपूर्णांक_addr
पूर्ण;

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *stack,
		       स्थिर अक्षर *loglvl)
अणु
	काष्ठा pt_regs *segv_regs = current->thपढ़ो.segv_regs;
	पूर्णांक i;

	अगर (!segv_regs && os_is_संकेत_stack()) अणु
		pr_err("Received SIGSEGV in SIGSEGV handler,"
				" aborting stack trace!\n");
		वापस;
	पूर्ण

	अगर (!stack)
		stack = get_stack_poपूर्णांकer(task, segv_regs);

	prपूर्णांकk("%sStack:\n", loglvl);
	क्रम (i = 0; i < 3 * STACKSLOTS_PER_LINE; i++) अणु
		अगर (kstack_end(stack))
			अवरोध;
		अगर (i && ((i % STACKSLOTS_PER_LINE) == 0))
			pr_cont("\n");
		pr_cont(" %08lx", *stack++);
	पूर्ण

	prपूर्णांकk("%sCall Trace:\n", loglvl);
	dump_trace(current, &stackops, (व्योम *)loglvl);
पूर्ण
