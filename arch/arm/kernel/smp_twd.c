<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/smp_twd.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/smp.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/smp_twd.h>

/* set up by the platक्रमm code */
अटल व्योम __iomem *twd_base;

अटल काष्ठा clk *twd_clk;
अटल अचिन्हित दीर्घ twd_समयr_rate;
अटल DEFINE_PER_CPU(bool, percpu_setup_called);

अटल काष्ठा घड़ी_event_device __percpu *twd_evt;
अटल अचिन्हित पूर्णांक twd_features =
		CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
अटल पूर्णांक twd_ppi;

अटल पूर्णांक twd_shutकरोwn(काष्ठा घड़ी_event_device *clk)
अणु
	ग_लिखोl_relaxed(0, twd_base + TWD_TIMER_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक twd_set_oneshot(काष्ठा घड़ी_event_device *clk)
अणु
	/* period set, and समयr enabled in 'next_event' hook */
	ग_लिखोl_relaxed(TWD_TIMER_CONTROL_IT_ENABLE | TWD_TIMER_CONTROL_ONESHOT,
		       twd_base + TWD_TIMER_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक twd_set_periodic(काष्ठा घड़ी_event_device *clk)
अणु
	अचिन्हित दीर्घ ctrl = TWD_TIMER_CONTROL_ENABLE |
			     TWD_TIMER_CONTROL_IT_ENABLE |
			     TWD_TIMER_CONTROL_PERIODIC;

	ग_लिखोl_relaxed(DIV_ROUND_CLOSEST(twd_समयr_rate, HZ),
		       twd_base + TWD_TIMER_LOAD);
	ग_लिखोl_relaxed(ctrl, twd_base + TWD_TIMER_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक twd_set_next_event(अचिन्हित दीर्घ evt,
			काष्ठा घड़ी_event_device *unused)
अणु
	अचिन्हित दीर्घ ctrl = पढ़ोl_relaxed(twd_base + TWD_TIMER_CONTROL);

	ctrl |= TWD_TIMER_CONTROL_ENABLE;

	ग_लिखोl_relaxed(evt, twd_base + TWD_TIMER_COUNTER);
	ग_लिखोl_relaxed(ctrl, twd_base + TWD_TIMER_CONTROL);

	वापस 0;
पूर्ण

/*
 * local_समयr_ack: checks क्रम a local समयr पूर्णांकerrupt.
 *
 * If a local समयr पूर्णांकerrupt has occurred, acknowledge and वापस 1.
 * Otherwise, वापस 0.
 */
अटल पूर्णांक twd_समयr_ack(व्योम)
अणु
	अगर (पढ़ोl_relaxed(twd_base + TWD_TIMER_INTSTAT)) अणु
		ग_लिखोl_relaxed(1, twd_base + TWD_TIMER_INTSTAT);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम twd_समयr_stop(व्योम)
अणु
	काष्ठा घड़ी_event_device *clk = raw_cpu_ptr(twd_evt);

	twd_shutकरोwn(clk);
	disable_percpu_irq(clk->irq);
पूर्ण

/*
 * Updates घड़ीevent frequency when the cpu frequency changes.
 * Called on the cpu that is changing frequency with पूर्णांकerrupts disabled.
 */
अटल व्योम twd_update_frequency(व्योम *new_rate)
अणु
	twd_समयr_rate = *((अचिन्हित दीर्घ *) new_rate);

	घड़ीevents_update_freq(raw_cpu_ptr(twd_evt), twd_समयr_rate);
पूर्ण

अटल पूर्णांक twd_rate_change(काष्ठा notअगरier_block *nb,
	अचिन्हित दीर्घ flags, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *cnd = data;

	/*
	 * The twd घड़ी events must be reprogrammed to account क्रम the new
	 * frequency.  The समयr is local to a cpu, so cross-call to the
	 * changing cpu.
	 */
	अगर (flags == POST_RATE_CHANGE)
		on_each_cpu(twd_update_frequency,
				  (व्योम *)&cnd->new_rate, 1);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block twd_clk_nb = अणु
	.notअगरier_call = twd_rate_change,
पूर्ण;

अटल पूर्णांक twd_clk_init(व्योम)
अणु
	अगर (twd_evt && raw_cpu_ptr(twd_evt) && !IS_ERR(twd_clk))
		वापस clk_notअगरier_रेजिस्टर(twd_clk, &twd_clk_nb);

	वापस 0;
पूर्ण
core_initcall(twd_clk_init);

अटल व्योम twd_calibrate_rate(व्योम)
अणु
	अचिन्हित दीर्घ count;
	u64 रुकोjअगरfies;

	/*
	 * If this is the first समय round, we need to work out how fast
	 * the समयr ticks
	 */
	अगर (twd_समयr_rate == 0) अणु
		pr_info("Calibrating local timer... ");

		/* Wait क्रम a tick to start */
		रुकोjअगरfies = get_jअगरfies_64() + 1;

		जबतक (get_jअगरfies_64() < रुकोjअगरfies)
			udelay(10);

		/* OK, now the tick has started, let's get the समयr going */
		रुकोjअगरfies += 5;

				 /* enable, no पूर्णांकerrupt or reload */
		ग_लिखोl_relaxed(0x1, twd_base + TWD_TIMER_CONTROL);

				 /* maximum value */
		ग_लिखोl_relaxed(0xFFFFFFFFU, twd_base + TWD_TIMER_COUNTER);

		जबतक (get_jअगरfies_64() < रुकोjअगरfies)
			udelay(10);

		count = पढ़ोl_relaxed(twd_base + TWD_TIMER_COUNTER);

		twd_समयr_rate = (0xFFFFFFFFU - count) * (HZ / 5);

		pr_cont("%lu.%02luMHz.\n", twd_समयr_rate / 1000000,
			(twd_समयr_rate / 10000) % 100);
	पूर्ण
पूर्ण

अटल irqवापस_t twd_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	अगर (twd_समयr_ack()) अणु
		evt->event_handler(evt);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल व्योम twd_get_घड़ी(काष्ठा device_node *np)
अणु
	पूर्णांक err;

	अगर (np)
		twd_clk = of_clk_get(np, 0);
	अन्यथा
		twd_clk = clk_get_sys("smp_twd", शून्य);

	अगर (IS_ERR(twd_clk)) अणु
		pr_err("smp_twd: clock not found %d\n", (पूर्णांक) PTR_ERR(twd_clk));
		वापस;
	पूर्ण

	err = clk_prepare_enable(twd_clk);
	अगर (err) अणु
		pr_err("smp_twd: clock failed to prepare+enable: %d\n", err);
		clk_put(twd_clk);
		वापस;
	पूर्ण

	twd_समयr_rate = clk_get_rate(twd_clk);
पूर्ण

/*
 * Setup the local घड़ी events क्रम a CPU.
 */
अटल व्योम twd_समयr_setup(व्योम)
अणु
	काष्ठा घड़ी_event_device *clk = raw_cpu_ptr(twd_evt);
	पूर्णांक cpu = smp_processor_id();

	/*
	 * If the basic setup क्रम this CPU has been करोne beक्रमe करोn't
	 * bother with the below.
	 */
	अगर (per_cpu(percpu_setup_called, cpu)) अणु
		ग_लिखोl_relaxed(0, twd_base + TWD_TIMER_CONTROL);
		घड़ीevents_रेजिस्टर_device(clk);
		enable_percpu_irq(clk->irq, 0);
		वापस;
	पूर्ण
	per_cpu(percpu_setup_called, cpu) = true;

	twd_calibrate_rate();

	/*
	 * The following is करोne once per CPU the first समय .setup() is
	 * called.
	 */
	ग_लिखोl_relaxed(0, twd_base + TWD_TIMER_CONTROL);

	clk->name = "local_timer";
	clk->features = twd_features;
	clk->rating = 350;
	clk->set_state_shutकरोwn = twd_shutकरोwn;
	clk->set_state_periodic = twd_set_periodic;
	clk->set_state_oneshot = twd_set_oneshot;
	clk->tick_resume = twd_shutकरोwn;
	clk->set_next_event = twd_set_next_event;
	clk->irq = twd_ppi;
	clk->cpumask = cpumask_of(cpu);

	घड़ीevents_config_and_रेजिस्टर(clk, twd_समयr_rate,
					0xf, 0xffffffff);
	enable_percpu_irq(clk->irq, 0);
पूर्ण

अटल पूर्णांक twd_समयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	twd_समयr_setup();
	वापस 0;
पूर्ण

अटल पूर्णांक twd_समयr_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	twd_समयr_stop();
	वापस 0;
पूर्ण

अटल पूर्णांक __init twd_local_समयr_common_रेजिस्टर(काष्ठा device_node *np)
अणु
	पूर्णांक err;

	twd_evt = alloc_percpu(काष्ठा घड़ी_event_device);
	अगर (!twd_evt) अणु
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	err = request_percpu_irq(twd_ppi, twd_handler, "twd", twd_evt);
	अगर (err) अणु
		pr_err("twd: can't register interrupt %d (%d)\n", twd_ppi, err);
		जाओ out_मुक्त;
	पूर्ण

	cpuhp_setup_state_nocalls(CPUHP_AP_ARM_TWD_STARTING,
				  "arm/timer/twd:starting",
				  twd_समयr_starting_cpu, twd_समयr_dying_cpu);

	twd_get_घड़ी(np);
	अगर (!of_property_पढ़ो_bool(np, "always-on"))
		twd_features |= CLOCK_EVT_FEAT_C3STOP;

	/*
	 * Immediately configure the समयr on the boot CPU, unless we need
	 * jअगरfies to be incrementing to calibrate the rate in which हाल
	 * setup the समयr in late_समय_init.
	 */
	अगर (twd_समयr_rate)
		twd_समयr_setup();
	अन्यथा
		late_समय_init = twd_समयr_setup;

	वापस 0;

out_मुक्त:
	iounmap(twd_base);
	twd_base = शून्य;
	मुक्त_percpu(twd_evt);

	वापस err;
पूर्ण

अटल पूर्णांक __init twd_local_समयr_of_रेजिस्टर(काष्ठा device_node *np)
अणु
	पूर्णांक err;

	twd_ppi = irq_of_parse_and_map(np, 0);
	अगर (!twd_ppi) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	twd_base = of_iomap(np, 0);
	अगर (!twd_base) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = twd_local_समयr_common_रेजिस्टर(np);

out:
	WARN(err, "twd_local_timer_of_register failed (%d)\n", err);
	वापस err;
पूर्ण
TIMER_OF_DECLARE(arm_twd_a9, "arm,cortex-a9-twd-timer", twd_local_समयr_of_रेजिस्टर);
TIMER_OF_DECLARE(arm_twd_a5, "arm,cortex-a5-twd-timer", twd_local_समयr_of_रेजिस्टर);
TIMER_OF_DECLARE(arm_twd_11mp, "arm,arm11mp-twd-timer", twd_local_समयr_of_रेजिस्टर);
