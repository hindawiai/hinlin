<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Preempt / IRQ disable delay thपढ़ो to test latency tracers
 *
 * Copyright (C) 2018 Joel Fernandes (Google) <joel@joelfernandes.org>
 */

#समावेश <linux/trace_घड़ी.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/completion.h>

अटल uदीर्घ delay = 100;
अटल अक्षर test_mode[12] = "irq";
अटल uपूर्णांक burst_size = 1;
अटल पूर्णांक  cpu_affinity = -1;

module_param_named(delay, delay, uदीर्घ, 0444);
module_param_string(test_mode, test_mode, 12, 0444);
module_param_named(burst_size, burst_size, uपूर्णांक, 0444);
module_param_named(cpu_affinity, cpu_affinity, पूर्णांक, 0444);
MODULE_PARM_DESC(delay, "Period in microseconds (100 us default)");
MODULE_PARM_DESC(test_mode, "Mode of the test such as preempt, irq, or alternate (default irq)");
MODULE_PARM_DESC(burst_size, "The size of a burst (default 1)");
MODULE_PARM_DESC(cpu_affinity, "Cpu num test is running on");

अटल काष्ठा completion करोne;

#घोषणा MIN(x, y) ((x) < (y) ? (x) : (y))

अटल व्योम busy_रुको(uदीर्घ समय)
अणु
	u64 start, end;

	start = trace_घड़ी_local();

	करो अणु
		end = trace_घड़ी_local();
		अगर (kthपढ़ो_should_stop())
			अवरोध;
	पूर्ण जबतक ((end - start) < (समय * 1000));
पूर्ण

अटल __always_अंतरभूत व्योम irqoff_test(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	busy_रुको(delay);
	local_irq_restore(flags);
पूर्ण

अटल __always_अंतरभूत व्योम preemptoff_test(व्योम)
अणु
	preempt_disable();
	busy_रुको(delay);
	preempt_enable();
पूर्ण

अटल व्योम execute_preemptirqtest(पूर्णांक idx)
अणु
	अगर (!म_भेद(test_mode, "irq"))
		irqoff_test();
	अन्यथा अगर (!म_भेद(test_mode, "preempt"))
		preemptoff_test();
	अन्यथा अगर (!म_भेद(test_mode, "alternate")) अणु
		अगर (idx % 2 == 0)
			irqoff_test();
		अन्यथा
			preemptoff_test();
	पूर्ण
पूर्ण

#घोषणा DECLARE_TESTFN(POSTFIX)				\
	अटल व्योम preemptirqtest_##POSTFIX(पूर्णांक idx)	\
	अणु						\
		execute_preemptirqtest(idx);		\
	पूर्ण						\

/*
 * We create 10 dअगरferent functions, so that we can get 10 dअगरferent
 * backtraces.
 */
DECLARE_TESTFN(0)
DECLARE_TESTFN(1)
DECLARE_TESTFN(2)
DECLARE_TESTFN(3)
DECLARE_TESTFN(4)
DECLARE_TESTFN(5)
DECLARE_TESTFN(6)
DECLARE_TESTFN(7)
DECLARE_TESTFN(8)
DECLARE_TESTFN(9)

अटल व्योम (*testfuncs[])(पूर्णांक)  = अणु
	preemptirqtest_0,
	preemptirqtest_1,
	preemptirqtest_2,
	preemptirqtest_3,
	preemptirqtest_4,
	preemptirqtest_5,
	preemptirqtest_6,
	preemptirqtest_7,
	preemptirqtest_8,
	preemptirqtest_9,
पूर्ण;

#घोषणा NR_TEST_FUNCS ARRAY_SIZE(testfuncs)

अटल पूर्णांक preemptirq_delay_run(व्योम *data)
अणु
	पूर्णांक i;
	पूर्णांक s = MIN(burst_size, NR_TEST_FUNCS);
	काष्ठा cpumask cpu_mask;

	अगर (cpu_affinity > -1) अणु
		cpumask_clear(&cpu_mask);
		cpumask_set_cpu(cpu_affinity, &cpu_mask);
		अगर (set_cpus_allowed_ptr(current, &cpu_mask))
			pr_err("cpu_affinity:%d, failed\n", cpu_affinity);
	पूर्ण

	क्रम (i = 0; i < s; i++)
		(testfuncs[i])(i);

	complete(&करोne);

	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule();
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण

	__set_current_state(TASK_RUNNING);

	वापस 0;
पूर्ण

अटल पूर्णांक preemptirq_run_test(व्योम)
अणु
	काष्ठा task_काष्ठा *task;
	अक्षर task_name[50];

	init_completion(&करोne);

	snम_लिखो(task_name, माप(task_name), "%s_test", test_mode);
	task =  kthपढ़ो_run(preemptirq_delay_run, शून्य, task_name);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	अगर (task) अणु
		रुको_क्रम_completion(&करोne);
		kthपढ़ो_stop(task);
	पूर्ण
	वापस 0;
पूर्ण


अटल sमाप_प्रकार trigger_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

	ret = preemptirq_run_test();
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute trigger_attribute =
	__ATTR(trigger, 0200, शून्य, trigger_store);

अटल काष्ठा attribute *attrs[] = अणु
	&trigger_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group attr_group = अणु
	.attrs = attrs,
पूर्ण;

अटल काष्ठा kobject *preemptirq_delay_kobj;

अटल पूर्णांक __init preemptirq_delay_init(व्योम)
अणु
	पूर्णांक retval;

	retval = preemptirq_run_test();
	अगर (retval != 0)
		वापस retval;

	preemptirq_delay_kobj = kobject_create_and_add("preemptirq_delay_test",
						       kernel_kobj);
	अगर (!preemptirq_delay_kobj)
		वापस -ENOMEM;

	retval = sysfs_create_group(preemptirq_delay_kobj, &attr_group);
	अगर (retval)
		kobject_put(preemptirq_delay_kobj);

	वापस retval;
पूर्ण

अटल व्योम __निकास preemptirq_delay_निकास(व्योम)
अणु
	kobject_put(preemptirq_delay_kobj);
पूर्ण

module_init(preemptirq_delay_init)
module_निकास(preemptirq_delay_निकास)
MODULE_LICENSE("GPL v2");
