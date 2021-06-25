<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	pit.c -- Freescale ColdFire PIT समयr. Currently this type of
 *	         hardware समयr only exists in the Freescale ColdFire
 *		 5270/5271, 5282 and 5208 CPUs. No करोubt newer ColdFire
 *		 family members will probably use it too.
 *
 *	Copyright (C) 1999-2008, Greg Ungerer (gerg@snapgear.com)
 *	Copyright (C) 2001-2004, SnapGear Inc. (www.snapgear.com)
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfpit.h>
#समावेश <यंत्र/mcfsim.h>

/***************************************************************************/

/*
 *	By शेष use समयr1 as the प्रणाली घड़ी समयr.
 */
#घोषणा	FREQ	((MCF_CLK / 2) / 64)
#घोषणा	TA(a)	(MCFPIT_BASE1 + (a))
#घोषणा PIT_CYCLES_PER_JIFFY (FREQ / HZ)

अटल u32 pit_cnt;

/*
 * Initialize the PIT समयr.
 *
 * This is also called after resume to bring the PIT पूर्णांकo operation again.
 */

अटल पूर्णांक cf_pit_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	__raw_ग_लिखोw(MCFPIT_PCSR_DISABLE, TA(MCFPIT_PCSR));
	__raw_ग_लिखोw(PIT_CYCLES_PER_JIFFY, TA(MCFPIT_PMR));
	__raw_ग_लिखोw(MCFPIT_PCSR_EN | MCFPIT_PCSR_PIE |
		     MCFPIT_PCSR_OVW | MCFPIT_PCSR_RLD |
		     MCFPIT_PCSR_CLK64, TA(MCFPIT_PCSR));
	वापस 0;
पूर्ण

अटल पूर्णांक cf_pit_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	__raw_ग_लिखोw(MCFPIT_PCSR_DISABLE, TA(MCFPIT_PCSR));
	__raw_ग_लिखोw(MCFPIT_PCSR_EN | MCFPIT_PCSR_PIE |
		     MCFPIT_PCSR_OVW | MCFPIT_PCSR_CLK64, TA(MCFPIT_PCSR));
	वापस 0;
पूर्ण

अटल पूर्णांक cf_pit_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	__raw_ग_लिखोw(MCFPIT_PCSR_DISABLE, TA(MCFPIT_PCSR));
	वापस 0;
पूर्ण

/*
 * Program the next event in oneshot mode
 *
 * Delta is given in PIT ticks
 */
अटल पूर्णांक cf_pit_next_event(अचिन्हित दीर्घ delta,
		काष्ठा घड़ी_event_device *evt)
अणु
	__raw_ग_लिखोw(delta, TA(MCFPIT_PMR));
	वापस 0;
पूर्ण

काष्ठा घड़ी_event_device cf_pit_घड़ीevent = अणु
	.name			= "pit",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn	= cf_pit_shutकरोwn,
	.set_state_periodic	= cf_pit_set_periodic,
	.set_state_oneshot	= cf_pit_set_oneshot,
	.set_next_event		= cf_pit_next_event,
	.shअगरt			= 32,
	.irq			= MCF_IRQ_PIT1,
पूर्ण;



/***************************************************************************/

अटल irqवापस_t pit_tick(पूर्णांक irq, व्योम *dummy)
अणु
	काष्ठा घड़ी_event_device *evt = &cf_pit_घड़ीevent;
	u16 pcsr;

	/* Reset the ColdFire समयr */
	pcsr = __raw_पढ़ोw(TA(MCFPIT_PCSR));
	__raw_ग_लिखोw(pcsr | MCFPIT_PCSR_PIF, TA(MCFPIT_PCSR));

	pit_cnt += PIT_CYCLES_PER_JIFFY;
	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

/***************************************************************************/

अटल u64 pit_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	u32 cycles;
	u16 pcntr;

	local_irq_save(flags);
	pcntr = __raw_पढ़ोw(TA(MCFPIT_PCNTR));
	cycles = pit_cnt;
	local_irq_restore(flags);

	वापस cycles + PIT_CYCLES_PER_JIFFY - pcntr;
पूर्ण

/***************************************************************************/

अटल काष्ठा घड़ीsource pit_clk = अणु
	.name	= "pit",
	.rating	= 100,
	.पढ़ो	= pit_पढ़ो_clk,
	.mask	= CLOCKSOURCE_MASK(32),
पूर्ण;

/***************************************************************************/

व्योम hw_समयr_init(व्योम)
अणु
	पूर्णांक ret;

	cf_pit_घड़ीevent.cpumask = cpumask_of(smp_processor_id());
	cf_pit_घड़ीevent.mult = भाग_sc(FREQ, NSEC_PER_SEC, 32);
	cf_pit_घड़ीevent.max_delta_ns =
		घड़ीevent_delta2ns(0xFFFF, &cf_pit_घड़ीevent);
	cf_pit_घड़ीevent.max_delta_ticks = 0xFFFF;
	cf_pit_घड़ीevent.min_delta_ns =
		घड़ीevent_delta2ns(0x3f, &cf_pit_घड़ीevent);
	cf_pit_घड़ीevent.min_delta_ticks = 0x3f;
	घड़ीevents_रेजिस्टर_device(&cf_pit_घड़ीevent);

	ret = request_irq(MCF_IRQ_PIT1, pit_tick, IRQF_TIMER, "timer", शून्य);
	अगर (ret) अणु
		pr_err("Failed to request irq %d (timer): %pe\n", MCF_IRQ_PIT1,
		       ERR_PTR(ret));
	पूर्ण

	घड़ीsource_रेजिस्टर_hz(&pit_clk, FREQ);
पूर्ण

/***************************************************************************/
