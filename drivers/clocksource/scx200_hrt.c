<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006 Jim Cromie
 *
 * This is a घड़ीsource driver क्रम the Geode SCx200's 1 or 27 MHz
 * high-resolution समयr.  The Geode SC-1100 (at least) has a buggy
 * समय stamp counter (TSC), which loses समय unless 'idle=poll' is
 * given as a boot-arg. In its असलence, the Generic Timekeeping code
 * will detect and de-rate the bad TSC, allowing this समयr to take
 * over समयkeeping duties.
 *
 * Based on work by John Stultz, and Ted Phelps (in a 2.6.12-rc6 patch)
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/scx200.h>

#घोषणा NAME "scx200_hrt"

अटल पूर्णांक mhz27;
module_param(mhz27, पूर्णांक, 0);	/* load समय only */
MODULE_PARM_DESC(mhz27, "count at 27.0 MHz (default is 1.0 MHz)");

अटल पूर्णांक ppm;
module_param(ppm, पूर्णांक, 0);	/* load समय only */
MODULE_PARM_DESC(ppm, "+-adjust to actual XO freq (ppm)");

/* HiRes Timer configuration रेजिस्टर address */
#घोषणा SCx200_TMCNFG_OFFSET (SCx200_TIMER_OFFSET + 5)

/* and config settings */
#घोषणा HR_TMEN (1 << 0)	/* समयr पूर्णांकerrupt enable */
#घोषणा HR_TMCLKSEL (1 << 1)	/* 1|0 counts at 27|1 MHz */
#घोषणा HR_TM27MPD (1 << 2)	/* 1 turns off input घड़ी (घातer-करोwn) */

/* The base समयr frequency, * 27 अगर selected */
#घोषणा HRT_FREQ   1000000

अटल u64 पढ़ो_hrt(काष्ठा घड़ीsource *cs)
अणु
	/* Read the समयr value */
	वापस (u64) inl(scx200_cb_base + SCx200_TIMER_OFFSET);
पूर्ण

अटल काष्ठा घड़ीsource cs_hrt = अणु
	.name		= "scx200_hrt",
	.rating		= 250,
	.पढ़ो		= पढ़ो_hrt,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	/* mult, shअगरt are set based on mhz27 flag */
पूर्ण;

अटल पूर्णांक __init init_hrt_घड़ीsource(व्योम)
अणु
	u32 freq;
	/* Make sure scx200 has initialized the configuration block */
	अगर (!scx200_cb_present())
		वापस -ENODEV;

	/* Reserve the समयr's ISA io-region क्रम ourselves */
	अगर (!request_region(scx200_cb_base + SCx200_TIMER_OFFSET,
			    SCx200_TIMER_SIZE,
			    "NatSemi SCx200 High-Resolution Timer")) अणु
		pr_warn("unable to lock timer region\n");
		वापस -ENODEV;
	पूर्ण

	/* ग_लिखो समयr config */
	outb(HR_TMEN | (mhz27 ? HR_TMCLKSEL : 0),
	     scx200_cb_base + SCx200_TMCNFG_OFFSET);

	freq = (HRT_FREQ + ppm);
	अगर (mhz27)
		freq *= 27;

	pr_info("enabling scx200 high-res timer (%s MHz +%d ppm)\n", mhz27 ? "27":"1", ppm);

	वापस घड़ीsource_रेजिस्टर_hz(&cs_hrt, freq);
पूर्ण

module_init(init_hrt_घड़ीsource);

MODULE_AUTHOR("Jim Cromie <jim.cromie@gmail.com>");
MODULE_DESCRIPTION("clocksource on SCx200 HiRes Timer");
MODULE_LICENSE("GPL");
