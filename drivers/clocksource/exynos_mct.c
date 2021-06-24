<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/arch/arm/mach-exynos4/mct.c
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Exynos4 MCT(Multi-Core Timer) support
*/

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/percpu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched_घड़ी.h>

#घोषणा EXYNOS4_MCTREG(x)		(x)
#घोषणा EXYNOS4_MCT_G_CNT_L		EXYNOS4_MCTREG(0x100)
#घोषणा EXYNOS4_MCT_G_CNT_U		EXYNOS4_MCTREG(0x104)
#घोषणा EXYNOS4_MCT_G_CNT_WSTAT		EXYNOS4_MCTREG(0x110)
#घोषणा EXYNOS4_MCT_G_COMP0_L		EXYNOS4_MCTREG(0x200)
#घोषणा EXYNOS4_MCT_G_COMP0_U		EXYNOS4_MCTREG(0x204)
#घोषणा EXYNOS4_MCT_G_COMP0_ADD_INCR	EXYNOS4_MCTREG(0x208)
#घोषणा EXYNOS4_MCT_G_TCON		EXYNOS4_MCTREG(0x240)
#घोषणा EXYNOS4_MCT_G_INT_CSTAT		EXYNOS4_MCTREG(0x244)
#घोषणा EXYNOS4_MCT_G_INT_ENB		EXYNOS4_MCTREG(0x248)
#घोषणा EXYNOS4_MCT_G_WSTAT		EXYNOS4_MCTREG(0x24C)
#घोषणा _EXYNOS4_MCT_L_BASE		EXYNOS4_MCTREG(0x300)
#घोषणा EXYNOS4_MCT_L_BASE(x)		(_EXYNOS4_MCT_L_BASE + (0x100 * x))
#घोषणा EXYNOS4_MCT_L_MASK		(0xffffff00)

#घोषणा MCT_L_TCNTB_OFFSET		(0x00)
#घोषणा MCT_L_ICNTB_OFFSET		(0x08)
#घोषणा MCT_L_TCON_OFFSET		(0x20)
#घोषणा MCT_L_INT_CSTAT_OFFSET		(0x30)
#घोषणा MCT_L_INT_ENB_OFFSET		(0x34)
#घोषणा MCT_L_WSTAT_OFFSET		(0x40)
#घोषणा MCT_G_TCON_START		(1 << 8)
#घोषणा MCT_G_TCON_COMP0_AUTO_INC	(1 << 1)
#घोषणा MCT_G_TCON_COMP0_ENABLE		(1 << 0)
#घोषणा MCT_L_TCON_INTERVAL_MODE	(1 << 2)
#घोषणा MCT_L_TCON_INT_START		(1 << 1)
#घोषणा MCT_L_TCON_TIMER_START		(1 << 0)

#घोषणा TICK_BASE_CNT	1

क्रमागत अणु
	MCT_INT_SPI,
	MCT_INT_PPI
पूर्ण;

क्रमागत अणु
	MCT_G0_IRQ,
	MCT_G1_IRQ,
	MCT_G2_IRQ,
	MCT_G3_IRQ,
	MCT_L0_IRQ,
	MCT_L1_IRQ,
	MCT_L2_IRQ,
	MCT_L3_IRQ,
	MCT_L4_IRQ,
	MCT_L5_IRQ,
	MCT_L6_IRQ,
	MCT_L7_IRQ,
	MCT_NR_IRQS,
पूर्ण;

अटल व्योम __iomem *reg_base;
अटल अचिन्हित दीर्घ clk_rate;
अटल अचिन्हित पूर्णांक mct_पूर्णांक_type;
अटल पूर्णांक mct_irqs[MCT_NR_IRQS];

काष्ठा mct_घड़ी_event_device अणु
	काष्ठा घड़ी_event_device evt;
	अचिन्हित दीर्घ base;
	अक्षर name[10];
पूर्ण;

अटल व्योम exynos4_mct_ग_लिखो(अचिन्हित पूर्णांक value, अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ stat_addr;
	u32 mask;
	u32 i;

	ग_लिखोl_relaxed(value, reg_base + offset);

	अगर (likely(offset >= EXYNOS4_MCT_L_BASE(0))) अणु
		stat_addr = (offset & EXYNOS4_MCT_L_MASK) + MCT_L_WSTAT_OFFSET;
		चयन (offset & ~EXYNOS4_MCT_L_MASK) अणु
		हाल MCT_L_TCON_OFFSET:
			mask = 1 << 3;		/* L_TCON ग_लिखो status */
			अवरोध;
		हाल MCT_L_ICNTB_OFFSET:
			mask = 1 << 1;		/* L_ICNTB ग_लिखो status */
			अवरोध;
		हाल MCT_L_TCNTB_OFFSET:
			mask = 1 << 0;		/* L_TCNTB ग_लिखो status */
			अवरोध;
		शेष:
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (offset) अणु
		हाल EXYNOS4_MCT_G_TCON:
			stat_addr = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 16;		/* G_TCON ग_लिखो status */
			अवरोध;
		हाल EXYNOS4_MCT_G_COMP0_L:
			stat_addr = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 0;		/* G_COMP0_L ग_लिखो status */
			अवरोध;
		हाल EXYNOS4_MCT_G_COMP0_U:
			stat_addr = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 1;		/* G_COMP0_U ग_लिखो status */
			अवरोध;
		हाल EXYNOS4_MCT_G_COMP0_ADD_INCR:
			stat_addr = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 2;		/* G_COMP0_ADD_INCR w status */
			अवरोध;
		हाल EXYNOS4_MCT_G_CNT_L:
			stat_addr = EXYNOS4_MCT_G_CNT_WSTAT;
			mask = 1 << 0;		/* G_CNT_L ग_लिखो status */
			अवरोध;
		हाल EXYNOS4_MCT_G_CNT_U:
			stat_addr = EXYNOS4_MCT_G_CNT_WSTAT;
			mask = 1 << 1;		/* G_CNT_U ग_लिखो status */
			अवरोध;
		शेष:
			वापस;
		पूर्ण
	पूर्ण

	/* Wait maximum 1 ms until written values are applied */
	क्रम (i = 0; i < loops_per_jअगरfy / 1000 * HZ; i++)
		अगर (पढ़ोl_relaxed(reg_base + stat_addr) & mask) अणु
			ग_लिखोl_relaxed(mask, reg_base + stat_addr);
			वापस;
		पूर्ण

	panic("MCT hangs after writing %d (offset:0x%lx)\n", value, offset);
पूर्ण

/* Clocksource handling */
अटल व्योम exynos4_mct_frc_start(व्योम)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(reg_base + EXYNOS4_MCT_G_TCON);
	reg |= MCT_G_TCON_START;
	exynos4_mct_ग_लिखो(reg, EXYNOS4_MCT_G_TCON);
पूर्ण

/**
 * exynos4_पढ़ो_count_64 - Read all 64-bits of the global counter
 *
 * This will पढ़ो all 64-bits of the global counter taking care to make sure
 * that the upper and lower half match.  Note that पढ़ोing the MCT can be quite
 * slow (hundreds of nanoseconds) so you should use the 32-bit (lower half
 * only) version when possible.
 *
 * Returns the number of cycles in the global counter.
 */
अटल u64 exynos4_पढ़ो_count_64(व्योम)
अणु
	अचिन्हित पूर्णांक lo, hi;
	u32 hi2 = पढ़ोl_relaxed(reg_base + EXYNOS4_MCT_G_CNT_U);

	करो अणु
		hi = hi2;
		lo = पढ़ोl_relaxed(reg_base + EXYNOS4_MCT_G_CNT_L);
		hi2 = पढ़ोl_relaxed(reg_base + EXYNOS4_MCT_G_CNT_U);
	पूर्ण जबतक (hi != hi2);

	वापस ((u64)hi << 32) | lo;
पूर्ण

/**
 * exynos4_पढ़ो_count_32 - Read the lower 32-bits of the global counter
 *
 * This will पढ़ो just the lower 32-bits of the global counter.  This is marked
 * as notrace so it can be used by the scheduler घड़ी.
 *
 * Returns the number of cycles in the global counter (lower 32 bits).
 */
अटल u32 notrace exynos4_पढ़ो_count_32(व्योम)
अणु
	वापस पढ़ोl_relaxed(reg_base + EXYNOS4_MCT_G_CNT_L);
पूर्ण

अटल u64 exynos4_frc_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस exynos4_पढ़ो_count_32();
पूर्ण

अटल व्योम exynos4_frc_resume(काष्ठा घड़ीsource *cs)
अणु
	exynos4_mct_frc_start();
पूर्ण

अटल काष्ठा घड़ीsource mct_frc = अणु
	.name		= "mct-frc",
	.rating		= 450,	/* use value higher than ARM arch समयr */
	.पढ़ो		= exynos4_frc_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	.resume		= exynos4_frc_resume,
पूर्ण;

अटल u64 notrace exynos4_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस exynos4_पढ़ो_count_32();
पूर्ण

#अगर defined(CONFIG_ARM)
अटल काष्ठा delay_समयr exynos4_delay_समयr;

अटल cycles_t exynos4_पढ़ो_current_समयr(व्योम)
अणु
	BUILD_BUG_ON_MSG(माप(cycles_t) != माप(u32),
			 "cycles_t needs to move to 32-bit for ARM64 usage");
	वापस exynos4_पढ़ो_count_32();
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init exynos4_घड़ीsource_init(व्योम)
अणु
	exynos4_mct_frc_start();

#अगर defined(CONFIG_ARM)
	exynos4_delay_समयr.पढ़ो_current_समयr = &exynos4_पढ़ो_current_समयr;
	exynos4_delay_समयr.freq = clk_rate;
	रेजिस्टर_current_समयr_delay(&exynos4_delay_समयr);
#पूर्ण_अगर

	अगर (घड़ीsource_रेजिस्टर_hz(&mct_frc, clk_rate))
		panic("%s: can't register clocksource\n", mct_frc.name);

	sched_घड़ी_रेजिस्टर(exynos4_पढ़ो_sched_घड़ी, 32, clk_rate);

	वापस 0;
पूर्ण

अटल व्योम exynos4_mct_comp0_stop(व्योम)
अणु
	अचिन्हित पूर्णांक tcon;

	tcon = पढ़ोl_relaxed(reg_base + EXYNOS4_MCT_G_TCON);
	tcon &= ~(MCT_G_TCON_COMP0_ENABLE | MCT_G_TCON_COMP0_AUTO_INC);

	exynos4_mct_ग_लिखो(tcon, EXYNOS4_MCT_G_TCON);
	exynos4_mct_ग_लिखो(0, EXYNOS4_MCT_G_INT_ENB);
पूर्ण

अटल व्योम exynos4_mct_comp0_start(bool periodic, अचिन्हित दीर्घ cycles)
अणु
	अचिन्हित पूर्णांक tcon;
	u64 comp_cycle;

	tcon = पढ़ोl_relaxed(reg_base + EXYNOS4_MCT_G_TCON);

	अगर (periodic) अणु
		tcon |= MCT_G_TCON_COMP0_AUTO_INC;
		exynos4_mct_ग_लिखो(cycles, EXYNOS4_MCT_G_COMP0_ADD_INCR);
	पूर्ण

	comp_cycle = exynos4_पढ़ो_count_64() + cycles;
	exynos4_mct_ग_लिखो((u32)comp_cycle, EXYNOS4_MCT_G_COMP0_L);
	exynos4_mct_ग_लिखो((u32)(comp_cycle >> 32), EXYNOS4_MCT_G_COMP0_U);

	exynos4_mct_ग_लिखो(0x1, EXYNOS4_MCT_G_INT_ENB);

	tcon |= MCT_G_TCON_COMP0_ENABLE;
	exynos4_mct_ग_लिखो(tcon , EXYNOS4_MCT_G_TCON);
पूर्ण

अटल पूर्णांक exynos4_comp_set_next_event(अचिन्हित दीर्घ cycles,
				       काष्ठा घड़ी_event_device *evt)
अणु
	exynos4_mct_comp0_start(false, cycles);

	वापस 0;
पूर्ण

अटल पूर्णांक mct_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	exynos4_mct_comp0_stop();
	वापस 0;
पूर्ण

अटल पूर्णांक mct_set_state_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ cycles_per_jअगरfy;

	cycles_per_jअगरfy = (((अचिन्हित दीर्घ दीर्घ)NSEC_PER_SEC / HZ * evt->mult)
			    >> evt->shअगरt);
	exynos4_mct_comp0_stop();
	exynos4_mct_comp0_start(true, cycles_per_jअगरfy);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device mct_comp_device = अणु
	.name			= "mct-comp",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.rating			= 250,
	.set_next_event		= exynos4_comp_set_next_event,
	.set_state_periodic	= mct_set_state_periodic,
	.set_state_shutकरोwn	= mct_set_state_shutकरोwn,
	.set_state_oneshot	= mct_set_state_shutकरोwn,
	.set_state_oneshot_stopped = mct_set_state_shutकरोwn,
	.tick_resume		= mct_set_state_shutकरोwn,
पूर्ण;

अटल irqवापस_t exynos4_mct_comp_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	exynos4_mct_ग_लिखो(0x1, EXYNOS4_MCT_G_INT_CSTAT);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक exynos4_घड़ीevent_init(व्योम)
अणु
	mct_comp_device.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&mct_comp_device, clk_rate,
					0xf, 0xffffffff);
	अगर (request_irq(mct_irqs[MCT_G0_IRQ], exynos4_mct_comp_isr,
			IRQF_TIMER | IRQF_IRQPOLL, "mct_comp_irq",
			&mct_comp_device))
		pr_err("%s: request_irq() failed\n", "mct_comp_irq");

	वापस 0;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा mct_घड़ी_event_device, percpu_mct_tick);

/* Clock event handling */
अटल व्योम exynos4_mct_tick_stop(काष्ठा mct_घड़ी_event_device *mevt)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित दीर्घ mask = MCT_L_TCON_INT_START | MCT_L_TCON_TIMER_START;
	अचिन्हित दीर्घ offset = mevt->base + MCT_L_TCON_OFFSET;

	पंचांगp = पढ़ोl_relaxed(reg_base + offset);
	अगर (पंचांगp & mask) अणु
		पंचांगp &= ~mask;
		exynos4_mct_ग_लिखो(पंचांगp, offset);
	पूर्ण
पूर्ण

अटल व्योम exynos4_mct_tick_start(अचिन्हित दीर्घ cycles,
				   काष्ठा mct_घड़ी_event_device *mevt)
अणु
	अचिन्हित दीर्घ पंचांगp;

	exynos4_mct_tick_stop(mevt);

	पंचांगp = (1 << 31) | cycles;	/* MCT_L_UPDATE_ICNTB */

	/* update पूर्णांकerrupt count buffer */
	exynos4_mct_ग_लिखो(पंचांगp, mevt->base + MCT_L_ICNTB_OFFSET);

	/* enable MCT tick पूर्णांकerrupt */
	exynos4_mct_ग_लिखो(0x1, mevt->base + MCT_L_INT_ENB_OFFSET);

	पंचांगp = पढ़ोl_relaxed(reg_base + mevt->base + MCT_L_TCON_OFFSET);
	पंचांगp |= MCT_L_TCON_INT_START | MCT_L_TCON_TIMER_START |
	       MCT_L_TCON_INTERVAL_MODE;
	exynos4_mct_ग_लिखो(पंचांगp, mevt->base + MCT_L_TCON_OFFSET);
पूर्ण

अटल व्योम exynos4_mct_tick_clear(काष्ठा mct_घड़ी_event_device *mevt)
अणु
	/* Clear the MCT tick पूर्णांकerrupt */
	अगर (पढ़ोl_relaxed(reg_base + mevt->base + MCT_L_INT_CSTAT_OFFSET) & 1)
		exynos4_mct_ग_लिखो(0x1, mevt->base + MCT_L_INT_CSTAT_OFFSET);
पूर्ण

अटल पूर्णांक exynos4_tick_set_next_event(अचिन्हित दीर्घ cycles,
				       काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा mct_घड़ी_event_device *mevt;

	mevt = container_of(evt, काष्ठा mct_घड़ी_event_device, evt);
	exynos4_mct_tick_start(cycles, mevt);
	वापस 0;
पूर्ण

अटल पूर्णांक set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा mct_घड़ी_event_device *mevt;

	mevt = container_of(evt, काष्ठा mct_घड़ी_event_device, evt);
	exynos4_mct_tick_stop(mevt);
	exynos4_mct_tick_clear(mevt);
	वापस 0;
पूर्ण

अटल पूर्णांक set_state_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा mct_घड़ी_event_device *mevt;
	अचिन्हित दीर्घ cycles_per_jअगरfy;

	mevt = container_of(evt, काष्ठा mct_घड़ी_event_device, evt);
	cycles_per_jअगरfy = (((अचिन्हित दीर्घ दीर्घ)NSEC_PER_SEC / HZ * evt->mult)
			    >> evt->shअगरt);
	exynos4_mct_tick_stop(mevt);
	exynos4_mct_tick_start(cycles_per_jअगरfy, mevt);
	वापस 0;
पूर्ण

अटल irqवापस_t exynos4_mct_tick_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mct_घड़ी_event_device *mevt = dev_id;
	काष्ठा घड़ी_event_device *evt = &mevt->evt;

	/*
	 * This is क्रम supporting oneshot mode.
	 * Mct would generate पूर्णांकerrupt periodically
	 * without explicit stopping.
	 */
	अगर (!घड़ीevent_state_periodic(&mevt->evt))
		exynos4_mct_tick_stop(mevt);

	exynos4_mct_tick_clear(mevt);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक exynos4_mct_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा mct_घड़ी_event_device *mevt =
		per_cpu_ptr(&percpu_mct_tick, cpu);
	काष्ठा घड़ी_event_device *evt = &mevt->evt;

	mevt->base = EXYNOS4_MCT_L_BASE(cpu);
	snम_लिखो(mevt->name, माप(mevt->name), "mct_tick%d", cpu);

	evt->name = mevt->name;
	evt->cpumask = cpumask_of(cpu);
	evt->set_next_event = exynos4_tick_set_next_event;
	evt->set_state_periodic = set_state_periodic;
	evt->set_state_shutकरोwn = set_state_shutकरोwn;
	evt->set_state_oneshot = set_state_shutकरोwn;
	evt->set_state_oneshot_stopped = set_state_shutकरोwn;
	evt->tick_resume = set_state_shutकरोwn;
	evt->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	evt->rating = 500;	/* use value higher than ARM arch समयr */

	exynos4_mct_ग_लिखो(TICK_BASE_CNT, mevt->base + MCT_L_TCNTB_OFFSET);

	अगर (mct_पूर्णांक_type == MCT_INT_SPI) अणु

		अगर (evt->irq == -1)
			वापस -EIO;

		irq_क्रमce_affinity(evt->irq, cpumask_of(cpu));
		enable_irq(evt->irq);
	पूर्ण अन्यथा अणु
		enable_percpu_irq(mct_irqs[MCT_L0_IRQ], 0);
	पूर्ण
	घड़ीevents_config_and_रेजिस्टर(evt, clk_rate / (TICK_BASE_CNT + 1),
					0xf, 0x7fffffff);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos4_mct_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा mct_घड़ी_event_device *mevt =
		per_cpu_ptr(&percpu_mct_tick, cpu);
	काष्ठा घड़ी_event_device *evt = &mevt->evt;

	evt->set_state_shutकरोwn(evt);
	अगर (mct_पूर्णांक_type == MCT_INT_SPI) अणु
		अगर (evt->irq != -1)
			disable_irq_nosync(evt->irq);
		exynos4_mct_ग_लिखो(0x1, mevt->base + MCT_L_INT_CSTAT_OFFSET);
	पूर्ण अन्यथा अणु
		disable_percpu_irq(mct_irqs[MCT_L0_IRQ]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init exynos4_समयr_resources(काष्ठा device_node *np, व्योम __iomem *base)
अणु
	पूर्णांक err, cpu;
	काष्ठा clk *mct_clk, *tick_clk;

	tick_clk = of_clk_get_by_name(np, "fin_pll");
	अगर (IS_ERR(tick_clk))
		panic("%s: unable to determine tick clock rate\n", __func__);
	clk_rate = clk_get_rate(tick_clk);

	mct_clk = of_clk_get_by_name(np, "mct");
	अगर (IS_ERR(mct_clk))
		panic("%s: unable to retrieve mct clock instance\n", __func__);
	clk_prepare_enable(mct_clk);

	reg_base = base;
	अगर (!reg_base)
		panic("%s: unable to ioremap mct address space\n", __func__);

	अगर (mct_पूर्णांक_type == MCT_INT_PPI) अणु

		err = request_percpu_irq(mct_irqs[MCT_L0_IRQ],
					 exynos4_mct_tick_isr, "MCT",
					 &percpu_mct_tick);
		WARN(err, "MCT: can't request IRQ %d (%d)\n",
		     mct_irqs[MCT_L0_IRQ], err);
	पूर्ण अन्यथा अणु
		क्रम_each_possible_cpu(cpu) अणु
			पूर्णांक mct_irq = mct_irqs[MCT_L0_IRQ + cpu];
			काष्ठा mct_घड़ी_event_device *pcpu_mevt =
				per_cpu_ptr(&percpu_mct_tick, cpu);

			pcpu_mevt->evt.irq = -1;

			irq_set_status_flags(mct_irq, IRQ_NOAUTOEN);
			अगर (request_irq(mct_irq,
					exynos4_mct_tick_isr,
					IRQF_TIMER | IRQF_NOBALANCING,
					pcpu_mevt->name, pcpu_mevt)) अणु
				pr_err("exynos-mct: cannot register IRQ (cpu%d)\n",
									cpu);

				जारी;
			पूर्ण
			pcpu_mevt->evt.irq = mct_irq;
		पूर्ण
	पूर्ण

	/* Install hotplug callbacks which configure the समयr on this CPU */
	err = cpuhp_setup_state(CPUHP_AP_EXYNOS4_MCT_TIMER_STARTING,
				"clockevents/exynos4/mct_timer:starting",
				exynos4_mct_starting_cpu,
				exynos4_mct_dying_cpu);
	अगर (err)
		जाओ out_irq;

	वापस 0;

out_irq:
	अगर (mct_पूर्णांक_type == MCT_INT_PPI) अणु
		मुक्त_percpu_irq(mct_irqs[MCT_L0_IRQ], &percpu_mct_tick);
	पूर्ण अन्यथा अणु
		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा mct_घड़ी_event_device *pcpu_mevt =
				per_cpu_ptr(&percpu_mct_tick, cpu);

			अगर (pcpu_mevt->evt.irq != -1) अणु
				मुक्त_irq(pcpu_mevt->evt.irq, pcpu_mevt);
				pcpu_mevt->evt.irq = -1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __init mct_init_dt(काष्ठा device_node *np, अचिन्हित पूर्णांक पूर्णांक_type)
अणु
	u32 nr_irqs, i;
	पूर्णांक ret;

	mct_पूर्णांक_type = पूर्णांक_type;

	/* This driver uses only one global समयr पूर्णांकerrupt */
	mct_irqs[MCT_G0_IRQ] = irq_of_parse_and_map(np, MCT_G0_IRQ);

	/*
	 * Find out the number of local irqs specअगरied. The local
	 * समयr irqs are specअगरied after the four global समयr
	 * irqs are specअगरied.
	 */
	nr_irqs = of_irq_count(np);
	क्रम (i = MCT_L0_IRQ; i < nr_irqs; i++)
		mct_irqs[i] = irq_of_parse_and_map(np, i);

	ret = exynos4_समयr_resources(np, of_iomap(np, 0));
	अगर (ret)
		वापस ret;

	ret = exynos4_घड़ीsource_init();
	अगर (ret)
		वापस ret;

	वापस exynos4_घड़ीevent_init();
पूर्ण


अटल पूर्णांक __init mct_init_spi(काष्ठा device_node *np)
अणु
	वापस mct_init_dt(np, MCT_INT_SPI);
पूर्ण

अटल पूर्णांक __init mct_init_ppi(काष्ठा device_node *np)
अणु
	वापस mct_init_dt(np, MCT_INT_PPI);
पूर्ण
TIMER_OF_DECLARE(exynos4210, "samsung,exynos4210-mct", mct_init_spi);
TIMER_OF_DECLARE(exynos4412, "samsung,exynos4412-mct", mct_init_ppi);
