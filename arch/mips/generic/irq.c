<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/समय.स>

पूर्णांक get_c0_fdc_पूर्णांक(व्योम)
अणु
	पूर्णांक mips_cpu_fdc_irq;

	अगर (mips_gic_present())
		mips_cpu_fdc_irq = gic_get_c0_fdc_पूर्णांक();
	अन्यथा अगर (cpu_has_veic)
		panic("Unimplemented!");
	अन्यथा अगर (cp0_fdc_irq >= 0)
		mips_cpu_fdc_irq = MIPS_CPU_IRQ_BASE + cp0_fdc_irq;
	अन्यथा
		mips_cpu_fdc_irq = -1;

	वापस mips_cpu_fdc_irq;
पूर्ण

पूर्णांक get_c0_perfcount_पूर्णांक(व्योम)
अणु
	पूर्णांक mips_cpu_perf_irq;

	अगर (mips_gic_present())
		mips_cpu_perf_irq = gic_get_c0_perfcount_पूर्णांक();
	अन्यथा अगर (cpu_has_veic)
		panic("Unimplemented!");
	अन्यथा अगर (cp0_perfcount_irq >= 0)
		mips_cpu_perf_irq = MIPS_CPU_IRQ_BASE + cp0_perfcount_irq;
	अन्यथा
		mips_cpu_perf_irq = -1;

	वापस mips_cpu_perf_irq;
पूर्ण

अचिन्हित पूर्णांक get_c0_compare_पूर्णांक(व्योम)
अणु
	पूर्णांक mips_cpu_समयr_irq;

	अगर (mips_gic_present())
		mips_cpu_समयr_irq = gic_get_c0_compare_पूर्णांक();
	अन्यथा अगर (cpu_has_veic)
		panic("Unimplemented!");
	अन्यथा
		mips_cpu_समयr_irq = MIPS_CPU_IRQ_BASE + cp0_compare_irq;

	वापस mips_cpu_समयr_irq;
पूर्ण
