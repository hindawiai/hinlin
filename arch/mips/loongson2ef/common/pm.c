<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * loongson-specअगरic suspend support
 *
 *  Copyright (C) 2009 Lemote Inc.
 *  Author: Wu Zhangjin <wuzhangjin@gmail.com>
 */
#समावेश <linux/suspend.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/mipsregs.h>

#समावेश <loongson.h>

अटल अचिन्हित पूर्णांक __maybe_unused cached_master_mask;	/* i8259A */
अटल अचिन्हित पूर्णांक __maybe_unused cached_slave_mask;
अटल अचिन्हित पूर्णांक __maybe_unused cached_bonito_irq_mask; /* bonito */

व्योम arch_suspend_disable_irqs(व्योम)
अणु
	/* disable all mips events */
	local_irq_disable();

#अगर_घोषित CONFIG_I8259
	/* disable all events of i8259A */
	cached_slave_mask = inb(PIC_SLAVE_IMR);
	cached_master_mask = inb(PIC_MASTER_IMR);

	outb(0xff, PIC_SLAVE_IMR);
	inb(PIC_SLAVE_IMR);
	outb(0xff, PIC_MASTER_IMR);
	inb(PIC_MASTER_IMR);
#पूर्ण_अगर
	/* disable all events of bonito */
	cached_bonito_irq_mask = LOONGSON_INTEN;
	LOONGSON_INTENCLR = 0xffff;
	(व्योम)LOONGSON_INTENCLR;
पूर्ण

व्योम arch_suspend_enable_irqs(व्योम)
अणु
	/* enable all mips events */
	local_irq_enable();
#अगर_घोषित CONFIG_I8259
	/* only enable the cached events of i8259A */
	outb(cached_slave_mask, PIC_SLAVE_IMR);
	outb(cached_master_mask, PIC_MASTER_IMR);
#पूर्ण_अगर
	/* enable all cached events of bonito */
	LOONGSON_INTENSET = cached_bonito_irq_mask;
	(व्योम)LOONGSON_INTENSET;
पूर्ण

/*
 * Setup the board-specअगरic events क्रम waking up loongson from रुको mode
 */
व्योम __weak setup_wakeup_events(व्योम)
अणु
पूर्ण

/*
 * Check wakeup events
 */
पूर्णांक __weak wakeup_loongson(व्योम)
अणु
	वापस 1;
पूर्ण

/*
 * If the events are really what we want to wakeup the CPU, wake it up
 * otherwise put the CPU asleep again.
 */
अटल व्योम रुको_क्रम_wakeup_events(व्योम)
अणु
	जबतक (!wakeup_loongson())
		ग_लिखोl(पढ़ोl(LOONGSON_CHIPCFG) & ~0x7, LOONGSON_CHIPCFG);
पूर्ण

/*
 * Stop all perf counters
 *
 * $24 is the control रेजिस्टर of Loongson perf counter
 */
अटल अंतरभूत व्योम stop_perf_counters(व्योम)
अणु
	__ग_लिखो_64bit_c0_रेजिस्टर($24, 0, 0);
पूर्ण


अटल व्योम loongson_suspend_enter(व्योम)
अणु
	अचिन्हित पूर्णांक cached_cpu_freq;

	/* setup wakeup events via enabling the IRQs */
	setup_wakeup_events();

	stop_perf_counters();

	cached_cpu_freq = पढ़ोl(LOONGSON_CHIPCFG);

	/* Put CPU पूर्णांकo रुको mode */
	ग_लिखोl(पढ़ोl(LOONGSON_CHIPCFG) & ~0x7, LOONGSON_CHIPCFG);

	/* रुको क्रम the given events to wakeup cpu from रुको mode */
	रुको_क्रम_wakeup_events();

	ग_लिखोl(cached_cpu_freq, LOONGSON_CHIPCFG);

	mmiowb();
पूर्ण

व्योम __weak mach_suspend(व्योम)
अणु
पूर्ण

व्योम __weak mach_resume(व्योम)
अणु
पूर्ण

अटल पूर्णांक loongson_pm_enter(suspend_state_t state)
अणु
	mach_suspend();

	/* processor specअगरic suspend */
	loongson_suspend_enter();

	mach_resume();

	वापस 0;
पूर्ण

अटल पूर्णांक loongson_pm_valid_state(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_ON:
	हाल PM_SUSPEND_STANDBY:
	हाल PM_SUSPEND_MEM:
		वापस 1;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops loongson_pm_ops = अणु
	.valid	= loongson_pm_valid_state,
	.enter	= loongson_pm_enter,
पूर्ण;

अटल पूर्णांक __init loongson_pm_init(व्योम)
अणु
	suspend_set_ops(&loongson_pm_ops);

	वापस 0;
पूर्ण
arch_initcall(loongson_pm_init);
