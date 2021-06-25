<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000,2001,2004 Broadcom Corporation
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/समय.स>

#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/bcm1480_पूर्णांक.h>
#समावेश <यंत्र/sibyte/bcm1480_scd.h>

#समावेश <यंत्र/sibyte/sb1250.h>

अटल u64 bcm1480_hpt_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64) __raw_पढ़ोq(IOADDR(A_SCD_ZBBUS_CYCLE_COUNT));
पूर्ण

काष्ठा घड़ीsource bcm1480_घड़ीsource = अणु
	.name	= "zbbus-cycles",
	.rating = 200,
	.पढ़ो	= bcm1480_hpt_पढ़ो,
	.mask	= CLOCKSOURCE_MASK(64),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u64 notrace sb1480_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस __raw_पढ़ोq(IOADDR(A_SCD_ZBBUS_CYCLE_COUNT));
पूर्ण

व्योम __init sb1480_घड़ीsource_init(व्योम)
अणु
	काष्ठा घड़ीsource *cs = &bcm1480_घड़ीsource;
	अचिन्हित पूर्णांक plद_भाग;
	अचिन्हित दीर्घ zbbus;

	plद_भाग = G_BCM1480_SYS_PLL_DIV(__raw_पढ़ोq(IOADDR(A_SCD_SYSTEM_CFG)));
	zbbus = ((plद_भाग >> 1) * 50000000) + ((plद_भाग & 1) * 25000000);
	घड़ीsource_रेजिस्टर_hz(cs, zbbus);

	sched_घड़ी_रेजिस्टर(sb1480_पढ़ो_sched_घड़ी, 64, zbbus);
पूर्ण
