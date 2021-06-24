<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ledtrig-cpu.c - LED trigger based on CPU activity
 *
 * This LED trigger will be रेजिस्टरed क्रम first 8 CPUs and named
 * as cpu0..cpu7. There's additional trigger called cpu that
 * is on when any CPU is active.
 *
 * If you want support क्रम arbitrary number of CPUs, make it one trigger,
 * with additional sysfs file selecting which CPU to watch.
 *
 * It can be bound to any LED just like other triggers using either a
 * board file or via sysfs पूर्णांकerface.
 *
 * An API named ledtrig_cpu is exported क्रम any user, who want to add CPU
 * activity indication in their code.
 *
 * Copyright 2011 Linus Walleij <linus.walleij@linaro.org>
 * Copyright 2011 - 2012 Bryan Wu <bryan.wu@canonical.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/percpu.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/cpu.h>
#समावेश "../leds.h"

#घोषणा MAX_NAME_LEN	8

काष्ठा led_trigger_cpu अणु
	bool is_active;
	अक्षर name[MAX_NAME_LEN];
	काष्ठा led_trigger *_trig;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा led_trigger_cpu, cpu_trig);

अटल काष्ठा led_trigger *trig_cpu_all;
अटल atomic_t num_active_cpus = ATOMIC_INIT(0);

/**
 * ledtrig_cpu - emit a CPU event as a trigger
 * @evt: CPU event to be emitted
 *
 * Emit a CPU event on a CPU core, which will trigger a
 * bound LED to turn on or turn off.
 */
व्योम ledtrig_cpu(क्रमागत cpu_led_event ledevt)
अणु
	काष्ठा led_trigger_cpu *trig = this_cpu_ptr(&cpu_trig);
	bool is_active = trig->is_active;

	/* Locate the correct CPU LED */
	चयन (ledevt) अणु
	हाल CPU_LED_IDLE_END:
	हाल CPU_LED_START:
		/* Will turn the LED on, max brightness */
		is_active = true;
		अवरोध;

	हाल CPU_LED_IDLE_START:
	हाल CPU_LED_STOP:
	हाल CPU_LED_HALTED:
		/* Will turn the LED off */
		is_active = false;
		अवरोध;

	शेष:
		/* Will leave the LED as it is */
		अवरोध;
	पूर्ण

	अगर (is_active != trig->is_active) अणु
		अचिन्हित पूर्णांक active_cpus;
		अचिन्हित पूर्णांक total_cpus;

		/* Update trigger state */
		trig->is_active = is_active;
		atomic_add(is_active ? 1 : -1, &num_active_cpus);
		active_cpus = atomic_पढ़ो(&num_active_cpus);
		total_cpus = num_present_cpus();

		led_trigger_event(trig->_trig,
			is_active ? LED_FULL : LED_OFF);


		led_trigger_event(trig_cpu_all,
			DIV_ROUND_UP(LED_FULL * active_cpus, total_cpus));

	पूर्ण
पूर्ण
EXPORT_SYMBOL(ledtrig_cpu);

अटल पूर्णांक ledtrig_cpu_syscore_suspend(व्योम)
अणु
	ledtrig_cpu(CPU_LED_STOP);
	वापस 0;
पूर्ण

अटल व्योम ledtrig_cpu_syscore_resume(व्योम)
अणु
	ledtrig_cpu(CPU_LED_START);
पूर्ण

अटल व्योम ledtrig_cpu_syscore_shutकरोwn(व्योम)
अणु
	ledtrig_cpu(CPU_LED_HALTED);
पूर्ण

अटल काष्ठा syscore_ops ledtrig_cpu_syscore_ops = अणु
	.shutकरोwn	= ledtrig_cpu_syscore_shutकरोwn,
	.suspend	= ledtrig_cpu_syscore_suspend,
	.resume		= ledtrig_cpu_syscore_resume,
पूर्ण;

अटल पूर्णांक ledtrig_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	ledtrig_cpu(CPU_LED_START);
	वापस 0;
पूर्ण

अटल पूर्णांक ledtrig_prepare_करोwn_cpu(अचिन्हित पूर्णांक cpu)
अणु
	ledtrig_cpu(CPU_LED_STOP);
	वापस 0;
पूर्ण

अटल पूर्णांक __init ledtrig_cpu_init(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक ret;

	/* Supports up to 9999 cpu cores */
	BUILD_BUG_ON(CONFIG_NR_CPUS > 9999);

	/*
	 * Registering a trigger क्रम all CPUs.
	 */
	led_trigger_रेजिस्टर_simple("cpu", &trig_cpu_all);

	/*
	 * Registering CPU led trigger क्रम each CPU core here
	 * ignores CPU hotplug, but after this CPU hotplug works
	 * fine with this trigger.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा led_trigger_cpu *trig = &per_cpu(cpu_trig, cpu);

		अगर (cpu >= 8)
			जारी;

		snम_लिखो(trig->name, MAX_NAME_LEN, "cpu%d", cpu);

		led_trigger_रेजिस्टर_simple(trig->name, &trig->_trig);
	पूर्ण

	रेजिस्टर_syscore_ops(&ledtrig_cpu_syscore_ops);

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "leds/trigger:starting",
				ledtrig_online_cpu, ledtrig_prepare_करोwn_cpu);
	अगर (ret < 0)
		pr_err("CPU hotplug notifier for ledtrig-cpu could not be registered: %d\n",
		       ret);

	pr_info("ledtrig-cpu: registered to indicate activity on CPUs\n");

	वापस 0;
पूर्ण
device_initcall(ledtrig_cpu_init);
