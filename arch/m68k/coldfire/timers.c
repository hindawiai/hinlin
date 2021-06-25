<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	समयrs.c -- generic ColdFire hardware समयr support.
 *
 *	Copyright (C) 1999-2008, Greg Ungerer <gerg@snapgear.com>
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/profile.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfसमयr.h>
#समावेश <यंत्र/mcfsim.h>

/***************************************************************************/

/*
 *	By शेष use समयr1 as the प्रणाली घड़ी समयr.
 */
#घोषणा	FREQ	(MCF_BUSCLK / 16)
#घोषणा	TA(a)	(MCFTIMER_BASE1 + (a))

/*
 *	These provide the underlying पूर्णांकerrupt vector support.
 *	Unक्रमtunately it is a little dअगरferent on each ColdFire.
 */
व्योम coldfire_profile_init(व्योम);

#अगर defined(CONFIG_M53xx) || defined(CONFIG_M5441x)
#घोषणा	__raw_पढ़ोtrr	__raw_पढ़ोl
#घोषणा	__raw_ग_लिखोtrr	__raw_ग_लिखोl
#अन्यथा
#घोषणा	__raw_पढ़ोtrr	__raw_पढ़ोw
#घोषणा	__raw_ग_लिखोtrr	__raw_ग_लिखोw
#पूर्ण_अगर

अटल u32 mcfपंचांगr_cycles_per_jअगरfy;
अटल u32 mcfपंचांगr_cnt;

/***************************************************************************/

अटल व्योम init_समयr_irq(व्योम)
अणु
#अगर_घोषित MCFSIM_ICR_AUTOVEC
	/* Timer1 is always used as प्रणाली समयr */
	ग_लिखोb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL6 | MCFSIM_ICR_PRI3,
		MCFSIM_TIMER1ICR);
	mcf_mapirq2imr(MCF_IRQ_TIMER, MCFINTC_TIMER1);

#अगर_घोषित CONFIG_HIGHPROखाता
	/* Timer2 is to be used as a high speed profile समयr  */
	ग_लिखोb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL7 | MCFSIM_ICR_PRI3,
		MCFSIM_TIMER2ICR);
	mcf_mapirq2imr(MCF_IRQ_PROखाताR, MCFINTC_TIMER2);
#पूर्ण_अगर
#पूर्ण_अगर /* MCFSIM_ICR_AUTOVEC */
पूर्ण

/***************************************************************************/

अटल irqवापस_t mcfपंचांगr_tick(पूर्णांक irq, व्योम *dummy)
अणु
	/* Reset the ColdFire समयr */
	__raw_ग_लिखोb(MCFTIMER_TER_CAP | MCFTIMER_TER_REF, TA(MCFTIMER_TER));

	mcfपंचांगr_cnt += mcfपंचांगr_cycles_per_jअगरfy;
	legacy_समयr_tick(1);
	वापस IRQ_HANDLED;
पूर्ण

/***************************************************************************/

अटल u64 mcfपंचांगr_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	u32 cycles;
	u16 tcn;

	local_irq_save(flags);
	tcn = __raw_पढ़ोw(TA(MCFTIMER_TCN));
	cycles = mcfपंचांगr_cnt;
	local_irq_restore(flags);

	वापस cycles + tcn;
पूर्ण

/***************************************************************************/

अटल काष्ठा घड़ीsource mcfपंचांगr_clk = अणु
	.name	= "tmr",
	.rating	= 250,
	.पढ़ो	= mcfपंचांगr_पढ़ो_clk,
	.mask	= CLOCKSOURCE_MASK(32),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

/***************************************************************************/

व्योम hw_समयr_init(व्योम)
अणु
	पूर्णांक r;

	__raw_ग_लिखोw(MCFTIMER_TMR_DISABLE, TA(MCFTIMER_TMR));
	mcfपंचांगr_cycles_per_jअगरfy = FREQ / HZ;
	/*
	 *	The coldfire समयr runs from 0 to TRR included, then 0
	 *	again and so on.  It counts thus actually TRR + 1 steps
	 *	क्रम 1 tick, not TRR.  So अगर you want n cycles,
	 *	initialize TRR with n - 1.
	 */
	__raw_ग_लिखोtrr(mcfपंचांगr_cycles_per_jअगरfy - 1, TA(MCFTIMER_TRR));
	__raw_ग_लिखोw(MCFTIMER_TMR_ENORI | MCFTIMER_TMR_CLK16 |
		MCFTIMER_TMR_RESTART | MCFTIMER_TMR_ENABLE, TA(MCFTIMER_TMR));

	घड़ीsource_रेजिस्टर_hz(&mcfपंचांगr_clk, FREQ);

	init_समयr_irq();
	r = request_irq(MCF_IRQ_TIMER, mcfपंचांगr_tick, IRQF_TIMER, "timer", शून्य);
	अगर (r) अणु
		pr_err("Failed to request irq %d (timer): %pe\n", MCF_IRQ_TIMER,
		       ERR_PTR(r));
	पूर्ण

#अगर_घोषित CONFIG_HIGHPROखाता
	coldfire_profile_init();
#पूर्ण_अगर
पूर्ण

/***************************************************************************/
#अगर_घोषित CONFIG_HIGHPROखाता
/***************************************************************************/

/*
 *	By शेष use समयr2 as the profiler घड़ी समयr.
 */
#घोषणा	PA(a)	(MCFTIMER_BASE2 + (a))

/*
 *	Choose a reasonably fast profile समयr. Make it an odd value to
 *	try and get good coverage of kernel operations.
 */
#घोषणा	PROखाताHZ	1013

/*
 *	Use the other समयr to provide high accuracy profiling info.
 */
irqवापस_t coldfire_profile_tick(पूर्णांक irq, व्योम *dummy)
अणु
	/* Reset ColdFire समयr2 */
	__raw_ग_लिखोb(MCFTIMER_TER_CAP | MCFTIMER_TER_REF, PA(MCFTIMER_TER));
	अगर (current->pid)
		profile_tick(CPU_PROFILING);
	वापस IRQ_HANDLED;
पूर्ण

/***************************************************************************/

व्योम coldfire_profile_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "PROFILE: lodging TIMER2 @ %dHz as profile timer\n",
	       PROखाताHZ);

	/* Set up TIMER 2 as high speed profile घड़ी */
	__raw_ग_लिखोw(MCFTIMER_TMR_DISABLE, PA(MCFTIMER_TMR));

	__raw_ग_लिखोtrr(((MCF_BUSCLK / 16) / PROखाताHZ), PA(MCFTIMER_TRR));
	__raw_ग_लिखोw(MCFTIMER_TMR_ENORI | MCFTIMER_TMR_CLK16 |
		MCFTIMER_TMR_RESTART | MCFTIMER_TMR_ENABLE, PA(MCFTIMER_TMR));

	ret = request_irq(MCF_IRQ_PROखाताR, coldfire_profile_tick, IRQF_TIMER,
			  "profile timer", शून्य);
	अगर (ret) अणु
		pr_err("Failed to request irq %d (profile timer): %pe\n",
		       MCF_IRQ_PROखाताR, ERR_PTR(ret));
	पूर्ण
पूर्ण

/***************************************************************************/
#पूर्ण_अगर	/* CONFIG_HIGHPROखाता */
/***************************************************************************/
