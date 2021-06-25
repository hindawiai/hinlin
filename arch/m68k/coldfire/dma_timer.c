<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dma_समयr.c -- Freescale ColdFire DMA Timer.
 *
 * Copyright (C) 2007, Benedikt Spranger <b.spranger@linutronix.de>
 * Copyright (C) 2008. Sebastian Siewior, Linutronix
 *
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfpit.h>
#समावेश <यंत्र/mcfsim.h>

#घोषणा DMA_TIMER_0	(0x00)
#घोषणा DMA_TIMER_1	(0x40)
#घोषणा DMA_TIMER_2	(0x80)
#घोषणा DMA_TIMER_3	(0xc0)

#घोषणा DTMR0	(MCF_IPSBAR + DMA_TIMER_0 + 0x400)
#घोषणा DTXMR0	(MCF_IPSBAR + DMA_TIMER_0 + 0x402)
#घोषणा DTER0	(MCF_IPSBAR + DMA_TIMER_0 + 0x403)
#घोषणा DTRR0	(MCF_IPSBAR + DMA_TIMER_0 + 0x404)
#घोषणा DTCR0	(MCF_IPSBAR + DMA_TIMER_0 + 0x408)
#घोषणा DTCN0	(MCF_IPSBAR + DMA_TIMER_0 + 0x40c)

#घोषणा DMA_FREQ    ((MCF_CLK / 2) / 16)

/* DTMR */
#घोषणा DMA_DTMR_RESTART	(1 << 3)
#घोषणा DMA_DTMR_CLK_DIV_1	(1 << 1)
#घोषणा DMA_DTMR_CLK_DIV_16	(2 << 1)
#घोषणा DMA_DTMR_ENABLE		(1 << 0)

अटल u64 cf_dt_get_cycles(काष्ठा घड़ीsource *cs)
अणु
	वापस __raw_पढ़ोl(DTCN0);
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_cf_dt = अणु
	.name		= "coldfire_dma_timer",
	.rating		= 200,
	.पढ़ो		= cf_dt_get_cycles,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक __init  init_cf_dt_घड़ीsource(व्योम)
अणु
	/*
	 * We setup DMA समयr 0 in मुक्त run mode. This incrementing counter is
	 * used as a highly precious घड़ी source. With MCF_CLOCK = 150 MHz we
	 * get a ~213 ns resolution and the 32bit रेजिस्टर will overflow almost
	 * every 15 minutes.
	 */
	__raw_ग_लिखोb(0x00, DTXMR0);
	__raw_ग_लिखोb(0x00, DTER0);
	__raw_ग_लिखोl(0x00000000, DTRR0);
	__raw_ग_लिखोw(DMA_DTMR_CLK_DIV_16 | DMA_DTMR_ENABLE, DTMR0);
	वापस घड़ीsource_रेजिस्टर_hz(&घड़ीsource_cf_dt, DMA_FREQ);
पूर्ण

arch_initcall(init_cf_dt_घड़ीsource);

#घोषणा CYC2NS_SCALE_FACTOR 10 /* 2^10, carefully chosen */
#घोषणा CYC2NS_SCALE	((1000000 << CYC2NS_SCALE_FACTOR) / (DMA_FREQ / 1000))

अटल अचिन्हित दीर्घ दीर्घ cycles2ns(अचिन्हित दीर्घ cycl)
अणु
	वापस (अचिन्हित दीर्घ दीर्घ) ((अचिन्हित दीर्घ दीर्घ)cycl *
			CYC2NS_SCALE) >> CYC2NS_SCALE_FACTOR;
पूर्ण

अचिन्हित दीर्घ दीर्घ sched_घड़ी(व्योम)
अणु
	अचिन्हित दीर्घ cycl = __raw_पढ़ोl(DTCN0);

	वापस cycles2ns(cycl);
पूर्ण
