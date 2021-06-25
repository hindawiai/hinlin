<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP 32ksynस_समयr/counter_32k-related code
 *
 * Copyright (C) 2009 Texas Instruments
 * Copyright (C) 2010 Nokia Corporation
 * Tony Lindgren <tony@atomide.com>
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * NOTE: This समयr is not the same समयr as the old OMAP1 MPU समयr.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/mach/समय.स>

#समावेश <plat/counter-32k.h>

/* OMAP2_32KSYNCNT_CR_OFF: offset of 32ksync counter रेजिस्टर */
#घोषणा OMAP2_32KSYNCNT_REV_OFF		0x0
#घोषणा OMAP2_32KSYNCNT_REV_SCHEME	(0x3 << 30)
#घोषणा OMAP2_32KSYNCNT_CR_OFF_LOW	0x10
#घोषणा OMAP2_32KSYNCNT_CR_OFF_HIGH	0x30

/*
 * 32KHz घड़ीsource ... always available, on pretty most chips except
 * OMAP 730 and 1510.  Other समयrs could be used as घड़ीsources, with
 * higher resolution in मुक्त-running counter modes (e.g. 12 MHz xtal),
 * but प्रणालीs won't necessarily want to spend resources that way.
 */
अटल व्योम __iomem *sync32k_cnt_reg;

अटल u64 notrace omap_32k_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस sync32k_cnt_reg ? पढ़ोl_relaxed(sync32k_cnt_reg) : 0;
पूर्ण

/**
 * omap_पढ़ो_persistent_घड़ी64 -  Return समय from a persistent घड़ी.
 *
 * Reads the समय from a source which isn't disabled during PM, the
 * 32k sync समयr.  Convert the cycles elapsed since last पढ़ो पूर्णांकo
 * nsecs and adds to a monotonically increasing बारpec64.
 */
अटल काष्ठा बारpec64 persistent_ts;
अटल cycles_t cycles;
अटल अचिन्हित पूर्णांक persistent_mult, persistent_shअगरt;

अटल व्योम omap_पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	अचिन्हित दीर्घ दीर्घ nsecs;
	cycles_t last_cycles;

	last_cycles = cycles;
	cycles = sync32k_cnt_reg ? पढ़ोl_relaxed(sync32k_cnt_reg) : 0;

	nsecs = घड़ीsource_cyc2ns(cycles - last_cycles,
					persistent_mult, persistent_shअगरt);

	बारpec64_add_ns(&persistent_ts, nsecs);

	*ts = persistent_ts;
पूर्ण

/**
 * omap_init_घड़ीsource_32k - setup and रेजिस्टर counter 32k as a
 * kernel घड़ीsource
 * @pbase: base addr of counter_32k module
 * @size: size of counter_32k to map
 *
 * Returns 0 upon success or negative error code upon failure.
 *
 */
पूर्णांक __init omap_init_घड़ीsource_32k(व्योम __iomem *vbase)
अणु
	पूर्णांक ret;

	/*
	 * 32k sync Counter IP रेजिस्टर offsets vary between the
	 * highlander version and the legacy ones.
	 * The 'SCHEME' bits(30-31) of the revision रेजिस्टर is used
	 * to identअगरy the version.
	 */
	अगर (पढ़ोl_relaxed(vbase + OMAP2_32KSYNCNT_REV_OFF) &
						OMAP2_32KSYNCNT_REV_SCHEME)
		sync32k_cnt_reg = vbase + OMAP2_32KSYNCNT_CR_OFF_HIGH;
	अन्यथा
		sync32k_cnt_reg = vbase + OMAP2_32KSYNCNT_CR_OFF_LOW;

	/*
	 * 120000 rough estimate from the calculations in
	 * __घड़ीsource_update_freq_scale.
	 */
	घड़ीs_calc_mult_shअगरt(&persistent_mult, &persistent_shअगरt,
			32768, NSEC_PER_SEC, 120000);

	ret = घड़ीsource_mmio_init(sync32k_cnt_reg, "32k_counter", 32768,
				250, 32, घड़ीsource_mmio_पढ़ोl_up);
	अगर (ret) अणु
		pr_err("32k_counter: can't register clocksource\n");
		वापस ret;
	पूर्ण

	sched_घड़ी_रेजिस्टर(omap_32k_पढ़ो_sched_घड़ी, 32, 32768);
	रेजिस्टर_persistent_घड़ी(omap_पढ़ो_persistent_घड़ी64);
	pr_info("OMAP clocksource: 32k_counter at 32768 Hz\n");

	वापस 0;
पूर्ण
