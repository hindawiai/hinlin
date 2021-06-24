<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	slसमयrs.c -- generic ColdFire slice समयr support.
 *
 *	Copyright (C) 2009-2010, Philippe De Muyter <phdm@macqel.be>
 *	based on
 *	समयrs.c -- generic ColdFire hardware समयr support.
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
#समावेश <यंत्र/mcfslt.h>
#समावेश <यंत्र/mcfsim.h>

/***************************************************************************/

#अगर_घोषित CONFIG_HIGHPROखाता

/*
 *	By शेष use Slice Timer 1 as the profiler घड़ी समयr.
 */
#घोषणा	PA(a)	(MCFSLT_TIMER1 + (a))

/*
 *	Choose a reasonably fast profile समयr. Make it an odd value to
 *	try and get good coverage of kernel operations.
 */
#घोषणा	PROखाताHZ	1013

irqवापस_t mcfslt_profile_tick(पूर्णांक irq, व्योम *dummy)
अणु
	/* Reset Slice Timer 1 */
	__raw_ग_लिखोl(MCFSLT_SSR_BE | MCFSLT_SSR_TE, PA(MCFSLT_SSR));
	अगर (current->pid)
		profile_tick(CPU_PROFILING);
	वापस IRQ_HANDLED;
पूर्ण

व्योम mcfslt_profile_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "PROFILE: lodging TIMER 1 @ %dHz as profile timer\n",
	       PROखाताHZ);

	ret = request_irq(MCF_IRQ_PROखाताR, mcfslt_profile_tick, IRQF_TIMER,
			  "profile timer", शून्य);
	अगर (ret) अणु
		pr_err("Failed to request irq %d (profile timer): %pe\n",
		       MCF_IRQ_PROखाताR, ERR_PTR(ret));
	पूर्ण

	/* Set up TIMER 2 as high speed profile घड़ी */
	__raw_ग_लिखोl(MCF_BUSCLK / PROखाताHZ - 1, PA(MCFSLT_STCNT));
	__raw_ग_लिखोl(MCFSLT_SCR_RUN | MCFSLT_SCR_IEN | MCFSLT_SCR_TEN,
								PA(MCFSLT_SCR));

पूर्ण

#पूर्ण_अगर	/* CONFIG_HIGHPROखाता */

/***************************************************************************/

/*
 *	By शेष use Slice Timer 0 as the प्रणाली घड़ी समयr.
 */
#घोषणा	TA(a)	(MCFSLT_TIMER0 + (a))

अटल u32 mcfslt_cycles_per_jअगरfy;
अटल u32 mcfslt_cnt;

अटल irqवापस_t mcfslt_tick(पूर्णांक irq, व्योम *dummy)
अणु
	/* Reset Slice Timer 0 */
	__raw_ग_लिखोl(MCFSLT_SSR_BE | MCFSLT_SSR_TE, TA(MCFSLT_SSR));
	mcfslt_cnt += mcfslt_cycles_per_jअगरfy;
	legacy_समयr_tick(1);
	वापस IRQ_HANDLED;
पूर्ण

अटल u64 mcfslt_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	u32 cycles, scnt;

	local_irq_save(flags);
	scnt = __raw_पढ़ोl(TA(MCFSLT_SCNT));
	cycles = mcfslt_cnt;
	अगर (__raw_पढ़ोl(TA(MCFSLT_SSR)) & MCFSLT_SSR_TE) अणु
		cycles += mcfslt_cycles_per_jअगरfy;
		scnt = __raw_पढ़ोl(TA(MCFSLT_SCNT));
	पूर्ण
	local_irq_restore(flags);

	/* subtract because slice समयrs count करोwn */
	वापस cycles + ((mcfslt_cycles_per_jअगरfy - 1) - scnt);
पूर्ण

अटल काष्ठा घड़ीsource mcfslt_clk = अणु
	.name	= "slt",
	.rating	= 250,
	.पढ़ो	= mcfslt_पढ़ो_clk,
	.mask	= CLOCKSOURCE_MASK(32),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

व्योम hw_समयr_init(व्योम)
अणु
	पूर्णांक r;

	mcfslt_cycles_per_jअगरfy = MCF_BUSCLK / HZ;
	/*
	 *	The coldfire slice समयr (SLT) runs from STCNT to 0 included,
	 *	then STCNT again and so on.  It counts thus actually
	 *	STCNT + 1 steps क्रम 1 tick, not STCNT.  So अगर you want
	 *	n cycles, initialize STCNT with n - 1.
	 */
	__raw_ग_लिखोl(mcfslt_cycles_per_jअगरfy - 1, TA(MCFSLT_STCNT));
	__raw_ग_लिखोl(MCFSLT_SCR_RUN | MCFSLT_SCR_IEN | MCFSLT_SCR_TEN,
								TA(MCFSLT_SCR));
	/* initialize mcfslt_cnt knowing that slice समयrs count करोwn */
	mcfslt_cnt = mcfslt_cycles_per_jअगरfy;

	r = request_irq(MCF_IRQ_TIMER, mcfslt_tick, IRQF_TIMER, "timer", शून्य);
	अगर (r) अणु
		pr_err("Failed to request irq %d (timer): %pe\n", MCF_IRQ_TIMER,
		       ERR_PTR(r));
	पूर्ण

	घड़ीsource_रेजिस्टर_hz(&mcfslt_clk, MCF_BUSCLK);

#अगर_घोषित CONFIG_HIGHPROखाता
	mcfslt_profile_init();
#पूर्ण_अगर
पूर्ण
