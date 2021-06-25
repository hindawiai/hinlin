<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 *
 * Setting up the घड़ी on the MIPS boards.
 */
#समावेश <linux/types.h>
#समावेश <linux/i8253.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/libfdt.h>
#समावेश <linux/math64.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयx.h>
#समावेश <linux/mc146818rtc.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/hardirq.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mc146818-समय.स>
#समावेश <यंत्र/msc01_ic.h>
#समावेश <यंत्र/mips-cps.h>

#समावेश <यंत्र/mips-boards/generic.h>
#समावेश <यंत्र/mips-boards/maltaपूर्णांक.h>

अटल पूर्णांक mips_cpu_समयr_irq;
अटल पूर्णांक mips_cpu_perf_irq;
बाह्य पूर्णांक cp0_perfcount_irq;

अटल अचिन्हित पूर्णांक gic_frequency;

अटल व्योम mips_समयr_dispatch(व्योम)
अणु
	करो_IRQ(mips_cpu_समयr_irq);
पूर्ण

अटल व्योम mips_perf_dispatch(व्योम)
अणु
	करो_IRQ(mips_cpu_perf_irq);
पूर्ण

अटल अचिन्हित पूर्णांक freqround(अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक amount)
अणु
	freq += amount;
	freq -= freq % (amount*2);
	वापस freq;
पूर्ण

/*
 * Estimate CPU and GIC frequencies.
 */
अटल व्योम __init estimate_frequencies(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक count, start;
	अचिन्हित अक्षर secs1, secs2, ctrl;
	पूर्णांक secs;
	u64 giccount = 0, gicstart = 0;

	local_irq_save(flags);

	अगर (mips_gic_present())
		clear_gic_config(GIC_CONFIG_COUNTSTOP);

	/*
	 * Read counters exactly on rising edge of update flag.
	 * This helps get an accurate पढ़ोing under भवisation.
	 */
	जबतक (CMOS_READ(RTC_REG_A) & RTC_UIP);
	जबतक (!(CMOS_READ(RTC_REG_A) & RTC_UIP));
	start = पढ़ो_c0_count();
	अगर (mips_gic_present())
		gicstart = पढ़ो_gic_counter();

	/* Wait क्रम falling edge beक्रमe पढ़ोing RTC. */
	जबतक (CMOS_READ(RTC_REG_A) & RTC_UIP);
	secs1 = CMOS_READ(RTC_SECONDS);

	/* Read counters again exactly on rising edge of update flag. */
	जबतक (!(CMOS_READ(RTC_REG_A) & RTC_UIP));
	count = पढ़ो_c0_count();
	अगर (mips_gic_present())
		giccount = पढ़ो_gic_counter();

	/* Wait क्रम falling edge beक्रमe पढ़ोing RTC again. */
	जबतक (CMOS_READ(RTC_REG_A) & RTC_UIP);
	secs2 = CMOS_READ(RTC_SECONDS);

	ctrl = CMOS_READ(RTC_CONTROL);

	local_irq_restore(flags);

	अगर (!(ctrl & RTC_DM_BINARY) || RTC_ALWAYS_BCD) अणु
		secs1 = bcd2bin(secs1);
		secs2 = bcd2bin(secs2);
	पूर्ण
	secs = secs2 - secs1;
	अगर (secs < 1)
		secs += 60;

	count -= start;
	count /= secs;
	mips_hpt_frequency = count;

	अगर (mips_gic_present()) अणु
		giccount = भाग_u64(giccount - gicstart, secs);
		gic_frequency = giccount;
	पूर्ण
पूर्ण

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	ts->tv_sec = mc146818_get_cmos_समय();
	ts->tv_nsec = 0;
पूर्ण

पूर्णांक get_c0_fdc_पूर्णांक(व्योम)
अणु
	/*
	 * Some cores claim the FDC is routable through the GIC, but it करोesn't
	 * actually seem to be connected क्रम those Malta bitstreams.
	 */
	चयन (current_cpu_type()) अणु
	हाल CPU_INTERAPTIV:
	हाल CPU_PROAPTIV:
		वापस -1;
	पूर्ण

	अगर (cpu_has_veic)
		वापस -1;
	अन्यथा अगर (mips_gic_present())
		वापस gic_get_c0_fdc_पूर्णांक();
	अन्यथा अगर (cp0_fdc_irq >= 0)
		वापस MIPS_CPU_IRQ_BASE + cp0_fdc_irq;
	अन्यथा
		वापस -1;
पूर्ण

पूर्णांक get_c0_perfcount_पूर्णांक(व्योम)
अणु
	अगर (cpu_has_veic) अणु
		set_vi_handler(MSC01E_INT_PERFCTR, mips_perf_dispatch);
		mips_cpu_perf_irq = MSC01E_INT_BASE + MSC01E_INT_PERFCTR;
	पूर्ण अन्यथा अगर (mips_gic_present()) अणु
		mips_cpu_perf_irq = gic_get_c0_perfcount_पूर्णांक();
	पूर्ण अन्यथा अगर (cp0_perfcount_irq >= 0) अणु
		mips_cpu_perf_irq = MIPS_CPU_IRQ_BASE + cp0_perfcount_irq;
	पूर्ण अन्यथा अणु
		mips_cpu_perf_irq = -1;
	पूर्ण

	वापस mips_cpu_perf_irq;
पूर्ण
EXPORT_SYMBOL_GPL(get_c0_perfcount_पूर्णांक);

अचिन्हित पूर्णांक get_c0_compare_पूर्णांक(व्योम)
अणु
	अगर (cpu_has_veic) अणु
		set_vi_handler(MSC01E_INT_CPUCTR, mips_समयr_dispatch);
		mips_cpu_समयr_irq = MSC01E_INT_BASE + MSC01E_INT_CPUCTR;
	पूर्ण अन्यथा अगर (mips_gic_present()) अणु
		mips_cpu_समयr_irq = gic_get_c0_compare_पूर्णांक();
	पूर्ण अन्यथा अणु
		mips_cpu_समयr_irq = MIPS_CPU_IRQ_BASE + cp0_compare_irq;
	पूर्ण

	वापस mips_cpu_समयr_irq;
पूर्ण

अटल व्योम __init init_rtc(व्योम)
अणु
	अचिन्हित अक्षर freq, ctrl;

	/* Set 32KHz समय base अगर not alपढ़ोy set */
	freq = CMOS_READ(RTC_FREQ_SELECT);
	अगर ((freq & RTC_DIV_CTL) != RTC_REF_CLCK_32KHZ)
		CMOS_WRITE(RTC_REF_CLCK_32KHZ, RTC_FREQ_SELECT);

	/* Ensure SET bit is clear so RTC can run */
	ctrl = CMOS_READ(RTC_CONTROL);
	अगर (ctrl & RTC_SET)
		CMOS_WRITE(ctrl & ~RTC_SET, RTC_CONTROL);
पूर्ण

#अगर_घोषित CONFIG_CLKSRC_MIPS_GIC
अटल u32 gic_frequency_dt;

अटल काष्ठा property gic_frequency_prop = अणु
	.name = "clock-frequency",
	.length = माप(u32),
	.value = &gic_frequency_dt,
पूर्ण;

अटल व्योम update_gic_frequency_dt(व्योम)
अणु
	काष्ठा device_node *node;

	gic_frequency_dt = cpu_to_be32(gic_frequency);

	node = of_find_compatible_node(शून्य, शून्य, "mti,gic-timer");
	अगर (!node) अणु
		pr_err("mti,gic-timer device node not found\n");
		वापस;
	पूर्ण

	अगर (of_update_property(node, &gic_frequency_prop) < 0)
		pr_err("error updating gic frequency property\n");
पूर्ण

#पूर्ण_अगर

व्योम __init plat_समय_init(व्योम)
अणु
	अचिन्हित पूर्णांक prid = पढ़ो_c0_prid() & (PRID_COMP_MASK | PRID_IMP_MASK);
	अचिन्हित पूर्णांक freq;

	init_rtc();
	estimate_frequencies();

	freq = mips_hpt_frequency;
	अगर ((prid != (PRID_COMP_MIPS | PRID_IMP_20KC)) &&
	    (prid != (PRID_COMP_MIPS | PRID_IMP_25KF)))
		freq *= 2;
	freq = freqround(freq, 5000);
	prपूर्णांकk("CPU frequency %d.%02d MHz\n", freq/1000000,
	       (freq%1000000)*100/1000000);

#अगर_घोषित CONFIG_I8253
	/* Only Malta has a PIT. */
	setup_pit_समयr();
#पूर्ण_अगर

	अगर (mips_gic_present()) अणु
		freq = freqround(gic_frequency, 5000);
		prपूर्णांकk("GIC frequency %d.%02d MHz\n", freq/1000000,
		       (freq%1000000)*100/1000000);
#अगर_घोषित CONFIG_CLKSRC_MIPS_GIC
		update_gic_frequency_dt();
		समयr_probe();
#पूर्ण_अगर
	पूर्ण
पूर्ण
