<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Simple stack backtrace regression test module
 *
 * (C) Copyright 2008 Intel Corporation
 * Author: Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/stacktrace.h>

अटल व्योम backtrace_test_normal(व्योम)
अणु
	pr_info("Testing a backtrace from process context.\n");
	pr_info("The following trace is a kernel self test and not a bug!\n");

	dump_stack();
पूर्ण

अटल DECLARE_COMPLETION(backtrace_work);

अटल व्योम backtrace_test_irq_callback(अचिन्हित दीर्घ data)
अणु
	dump_stack();
	complete(&backtrace_work);
पूर्ण

अटल DECLARE_TASKLET_OLD(backtrace_tasklet, &backtrace_test_irq_callback);

अटल व्योम backtrace_test_irq(व्योम)
अणु
	pr_info("Testing a backtrace from irq context.\n");
	pr_info("The following trace is a kernel self test and not a bug!\n");

	init_completion(&backtrace_work);
	tasklet_schedule(&backtrace_tasklet);
	रुको_क्रम_completion(&backtrace_work);
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE
अटल व्योम backtrace_test_saved(व्योम)
अणु
	अचिन्हित दीर्घ entries[8];
	अचिन्हित पूर्णांक nr_entries;

	pr_info("Testing a saved backtrace.\n");
	pr_info("The following trace is a kernel self test and not a bug!\n");

	nr_entries = stack_trace_save(entries, ARRAY_SIZE(entries), 0);
	stack_trace_prपूर्णांक(entries, nr_entries, 0);
पूर्ण
#अन्यथा
अटल व्योम backtrace_test_saved(व्योम)
अणु
	pr_info("Saved backtrace test skipped.\n");
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक backtrace_regression_test(व्योम)
अणु
	pr_info("====[ backtrace testing ]===========\n");

	backtrace_test_normal();
	backtrace_test_irq();
	backtrace_test_saved();

	pr_info("====[ end of backtrace testing ]====\n");
	वापस 0;
पूर्ण

अटल व्योम निकासf(व्योम)
अणु
पूर्ण

module_init(backtrace_regression_test);
module_निकास(निकासf);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arjan van de Ven <arjan@linux.intel.com>");
