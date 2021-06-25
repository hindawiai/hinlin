<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2011
 *
 * Author: Mattias Wallin <mattias.wallin@stericsson.com> क्रम ST-Ericsson
 * Author: Sundar Iyer क्रम ST-Ericsson
 * sched_घड़ी implementation is based on:
 * plat-nomadik/समयr.c Linus Walleij <linus.walleij@stericsson.com>
 *
 * DBx500-PRCMU Timer
 * The PRCMU has 5 समयrs which are available in a always-on
 * घातer करोमुख्य.  We use the Timer 4 क्रम our always-on घड़ी
 * source on DB8500.
 */
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/घड़ीchips.h>

#घोषणा RATE_32K		32768

#घोषणा TIMER_MODE_CONTINUOUS	0x1
#घोषणा TIMER_DOWNCOUNT_VAL	0xffffffff

#घोषणा PRCMU_TIMER_REF		0
#घोषणा PRCMU_TIMER_DOWNCOUNT	0x4
#घोषणा PRCMU_TIMER_MODE	0x8

अटल व्योम __iomem *clksrc_dbx500_समयr_base;

अटल u64 notrace clksrc_dbx500_prcmu_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	व्योम __iomem *base = clksrc_dbx500_समयr_base;
	u32 count, count2;

	करो अणु
		count = पढ़ोl_relaxed(base + PRCMU_TIMER_DOWNCOUNT);
		count2 = पढ़ोl_relaxed(base + PRCMU_TIMER_DOWNCOUNT);
	पूर्ण जबतक (count2 != count);

	/* Negate because the समयr is a decrementing counter */
	वापस ~count;
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_dbx500_prcmu = अणु
	.name		= "dbx500-prcmu-timer",
	.rating		= 100,
	.पढ़ो		= clksrc_dbx500_prcmu_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS | CLOCK_SOURCE_SUSPEND_NONSTOP,
पूर्ण;

अटल पूर्णांक __init clksrc_dbx500_prcmu_init(काष्ठा device_node *node)
अणु
	clksrc_dbx500_समयr_base = of_iomap(node, 0);

	/*
	 * The A9 sub प्रणाली expects the समयr to be configured as
	 * a continuous looping समयr.
	 * The PRCMU should configure it but अगर it क्रम some reason
	 * करोn't we करो it here.
	 */
	अगर (पढ़ोl(clksrc_dbx500_समयr_base + PRCMU_TIMER_MODE) !=
	    TIMER_MODE_CONTINUOUS) अणु
		ग_लिखोl(TIMER_MODE_CONTINUOUS,
		       clksrc_dbx500_समयr_base + PRCMU_TIMER_MODE);
		ग_लिखोl(TIMER_DOWNCOUNT_VAL,
		       clksrc_dbx500_समयr_base + PRCMU_TIMER_REF);
	पूर्ण
	वापस घड़ीsource_रेजिस्टर_hz(&घड़ीsource_dbx500_prcmu, RATE_32K);
पूर्ण
TIMER_OF_DECLARE(dbx500_prcmu, "stericsson,db8500-prcmu-timer-4",
		       clksrc_dbx500_prcmu_init);
