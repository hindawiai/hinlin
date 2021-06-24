<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * समयr-ti-32k.c - OMAP2 32k Timer Support
 *
 * Copyright (C) 2009 Nokia Corporation
 *
 * Update to use new घड़ीsource/घड़ीevent layers
 * Author: Kevin Hilman, MontaVista Software, Inc. <source@mvista.com>
 * Copyright (C) 2007 MontaVista Software, Inc.
 *
 * Original driver:
 * Copyright (C) 2005 Nokia Corporation
 * Author: Paul Mundt <paul.mundt@nokia.com>
 *         Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 * OMAP Dual-mode समयr framework support by Timo Teras
 *
 * Some parts based off of TI's 24xx code:
 *
 * Copyright (C) 2004-2009 Texas Instruments, Inc.
 *
 * Roughly modelled after the OMAP1 MPU समयr code.
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

/*
 * 32KHz घड़ीsource ... always available, on pretty most chips except
 * OMAP 730 and 1510.  Other समयrs could be used as घड़ीsources, with
 * higher resolution in मुक्त-running counter modes (e.g. 12 MHz xtal),
 * but प्रणालीs won't necessarily want to spend resources that way.
 */

#घोषणा OMAP2_32KSYNCNT_REV_OFF		0x0
#घोषणा OMAP2_32KSYNCNT_REV_SCHEME	(0x3 << 30)
#घोषणा OMAP2_32KSYNCNT_CR_OFF_LOW	0x10
#घोषणा OMAP2_32KSYNCNT_CR_OFF_HIGH	0x30

काष्ठा ti_32k अणु
	व्योम __iomem		*base;
	व्योम __iomem		*counter;
	काष्ठा घड़ीsource	cs;
पूर्ण;

अटल अंतरभूत काष्ठा ti_32k *to_ti_32k(काष्ठा घड़ीsource *cs)
अणु
	वापस container_of(cs, काष्ठा ti_32k, cs);
पूर्ण

अटल u64 notrace ti_32k_पढ़ो_cycles(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा ti_32k *ti = to_ti_32k(cs);

	वापस (u64)पढ़ोl_relaxed(ti->counter);
पूर्ण

अटल काष्ठा ti_32k ti_32k_समयr = अणु
	.cs = अणु
		.name		= "32k_counter",
		.rating		= 250,
		.पढ़ो		= ti_32k_पढ़ो_cycles,
		.mask		= CLOCKSOURCE_MASK(32),
		.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
	पूर्ण,
पूर्ण;

अटल u64 notrace omap_32k_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ti_32k_पढ़ो_cycles(&ti_32k_समयr.cs);
पूर्ण

अटल व्योम __init ti_32k_समयr_enable_घड़ी(काष्ठा device_node *np,
					     स्थिर अक्षर *name)
अणु
	काष्ठा clk *घड़ी;
	पूर्णांक error;

	घड़ी = of_clk_get_by_name(np->parent, name);
	अगर (IS_ERR(घड़ी)) अणु
		/* Only some SoCs have a separate पूर्णांकerface घड़ी */
		अगर (PTR_ERR(घड़ी) == -EINVAL && !म_भेदन("ick", name, 3))
			वापस;

		pr_warn("%s: could not get clock %s %li\n",
			__func__, name, PTR_ERR(घड़ी));
		वापस;
	पूर्ण

	error = clk_prepare_enable(घड़ी);
	अगर (error) अणु
		pr_warn("%s: could not enable %s: %i\n",
			__func__, name, error);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम __init ti_32k_समयr_module_init(काष्ठा device_node *np,
					    व्योम __iomem *base)
अणु
	व्योम __iomem *sysc = base + 4;

	अगर (!of_device_is_compatible(np->parent, "ti,sysc"))
		वापस;

	ti_32k_समयr_enable_घड़ी(np, "fck");
	ti_32k_समयr_enable_घड़ी(np, "ick");

	/*
	 * Force idle module as wkup करोमुख्य is active with MPU.
	 * No need to tag the module disabled क्रम ti-sysc probe.
	 */
	ग_लिखोl_relaxed(0, sysc);
पूर्ण

अटल पूर्णांक __init ti_32k_समयr_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	ti_32k_समयr.base = of_iomap(np, 0);
	अगर (!ti_32k_समयr.base) अणु
		pr_err("Can't ioremap 32k timer base\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!of_machine_is_compatible("ti,am43"))
		ti_32k_समयr.cs.flags |= CLOCK_SOURCE_SUSPEND_NONSTOP;

	ti_32k_समयr.counter = ti_32k_समयr.base;
	ti_32k_समयr_module_init(np, ti_32k_समयr.base);

	/*
	 * 32k sync Counter IP रेजिस्टर offsets vary between the highlander
	 * version and the legacy ones.
	 *
	 * The 'SCHEME' bits(30-31) of the revision रेजिस्टर is used to identअगरy
	 * the version.
	 */
	अगर (पढ़ोl_relaxed(ti_32k_समयr.base + OMAP2_32KSYNCNT_REV_OFF) &
			OMAP2_32KSYNCNT_REV_SCHEME)
		ti_32k_समयr.counter += OMAP2_32KSYNCNT_CR_OFF_HIGH;
	अन्यथा
		ti_32k_समयr.counter += OMAP2_32KSYNCNT_CR_OFF_LOW;

	pr_info("OMAP clocksource: 32k_counter at 32768 Hz\n");

	ret = घड़ीsource_रेजिस्टर_hz(&ti_32k_समयr.cs, 32768);
	अगर (ret) अणु
		pr_err("32k_counter: can't register clocksource\n");
		वापस ret;
	पूर्ण

	sched_घड़ी_रेजिस्टर(omap_32k_पढ़ो_sched_घड़ी, 32, 32768);

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(ti_32k_समयr, "ti,omap-counter32k",
		ti_32k_समयr_init);
