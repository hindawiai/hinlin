<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000, 2001 Broadcom Corporation
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/समय.स>

#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>
#समावेश <यंत्र/sibyte/sb1250_scd.h>

#घोषणा SB1250_HPT_NUM		3
#घोषणा SB1250_HPT_VALUE	M_SCD_TIMER_CNT /* max value */

/*
 * The HPT is मुक्त running from SB1250_HPT_VALUE करोwn to 0 then starts over
 * again.
 */
अटल अंतरभूत u64 sb1250_hpt_get_cycles(व्योम)
अणु
	अचिन्हित पूर्णांक count;
	व्योम __iomem *addr;

	addr = IOADDR(A_SCD_TIMER_REGISTER(SB1250_HPT_NUM, R_SCD_TIMER_CNT));
	count = G_SCD_TIMER_CNT(__raw_पढ़ोq(addr));

	वापस SB1250_HPT_VALUE - count;
पूर्ण

अटल u64 sb1250_hpt_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस sb1250_hpt_get_cycles();
पूर्ण

काष्ठा घड़ीsource bcm1250_घड़ीsource = अणु
	.name	= "bcm1250-counter-3",
	.rating = 200,
	.पढ़ो	= sb1250_hpt_पढ़ो,
	.mask	= CLOCKSOURCE_MASK(23),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u64 notrace sb1250_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस sb1250_hpt_get_cycles();
पूर्ण

व्योम __init sb1250_घड़ीsource_init(व्योम)
अणु
	काष्ठा घड़ीsource *cs = &bcm1250_घड़ीsource;

	/* Setup hpt using समयr #3 but करो not enable irq क्रम it */
	__raw_ग_लिखोq(0,
		     IOADDR(A_SCD_TIMER_REGISTER(SB1250_HPT_NUM,
						 R_SCD_TIMER_CFG)));
	__raw_ग_लिखोq(SB1250_HPT_VALUE,
		     IOADDR(A_SCD_TIMER_REGISTER(SB1250_HPT_NUM,
						 R_SCD_TIMER_INIT)));
	__raw_ग_लिखोq(M_SCD_TIMER_ENABLE | M_SCD_TIMER_MODE_CONTINUOUS,
		     IOADDR(A_SCD_TIMER_REGISTER(SB1250_HPT_NUM,
						 R_SCD_TIMER_CFG)));

	घड़ीsource_रेजिस्टर_hz(cs, V_SCD_TIMER_FREQ);

	sched_घड़ी_रेजिस्टर(sb1250_पढ़ो_sched_घड़ी, 23, V_SCD_TIMER_FREQ);
पूर्ण
