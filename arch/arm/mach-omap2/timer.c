<शैली गुरु>
/*
 * linux/arch/arm/mach-omap2/समयr.c
 *
 * OMAP2 GP समयr support.
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
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>

#समावेश "soc.h"
#समावेश "common.h"
#समावेश "control.h"
#समावेश "omap-secure.h"

#घोषणा REALTIME_COUNTER_BASE				0x48243200
#घोषणा INCREMENTER_NUMERATOR_OFFSET			0x10
#घोषणा INCREMENTER_DENUMERATOR_RELOAD_OFFSET		0x14
#घोषणा NUMERATOR_DENUMERATOR_MASK			0xfffff000

अटल अचिन्हित दीर्घ arch_समयr_freq;

व्योम set_cntfreq(व्योम)
अणु
	omap_smc1(OMAP5_DRA7_MON_SET_CNTFRQ_INDEX, arch_समयr_freq);
पूर्ण

/*
 * The realसमय counter also called master counter, is a मुक्त-running
 * counter, which is related to real समय. It produces the count used
 * by the CPU local समयr peripherals in the MPU cluster. The समयr counts
 * at a rate of 6.144 MHz. Because the device operates on dअगरferent घड़ीs
 * in dअगरferent घातer modes, the master counter shअगरts operation between
 * घड़ीs, adjusting the increment per घड़ी in hardware accordingly to
 * मुख्यtain a स्थिरant count rate.
 */
अटल व्योम __init realसमय_counter_init(व्योम)
अणु
	व्योम __iomem *base;
	अटल काष्ठा clk *sys_clk;
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक reg;
	अचिन्हित दीर्घ दीर्घ num, den;

	base = ioremap(REALTIME_COUNTER_BASE, SZ_32);
	अगर (!base) अणु
		pr_err("%s: ioremap failed\n", __func__);
		वापस;
	पूर्ण
	sys_clk = clk_get(शून्य, "sys_clkin");
	अगर (IS_ERR(sys_clk)) अणु
		pr_err("%s: failed to get system clock handle\n", __func__);
		iounmap(base);
		वापस;
	पूर्ण

	rate = clk_get_rate(sys_clk);

	अगर (soc_is_dra7xx()) अणु
		/*
		 * Errata i856 says the 32.768KHz crystal करोes not start at
		 * घातer on, so the CPU falls back to an emulated 32KHz घड़ी
		 * based on sysclk / 610 instead. This causes the master counter
		 * frequency to not be 6.144MHz but at sysclk / 610 * 375 / 2
		 * (OR sysclk * 75 / 244)
		 *
		 * This affects at least the DRA7/AM572x 1.0, 1.1 revisions.
		 * Of course any board built without a populated 32.768KHz
		 * crystal would also need this fix even अगर the CPU is fixed
		 * later.
		 *
		 * Either हाल can be detected by using the two speedselect bits
		 * If they are not 0, then the 32.768KHz घड़ी driving the
		 * coarse counter that corrects the fine counter every समय it
		 * ticks is actually rate/610 rather than 32.768KHz and we
		 * should compensate to aव्योम the 570ppm (at 20MHz, much worse
		 * at other rates) too fast प्रणाली समय.
		 */
		reg = omap_ctrl_पढ़ोl(DRA7_CTRL_CORE_BOOTSTRAP);
		अगर (reg & DRA7_SPEEDSELECT_MASK) अणु
			num = 75;
			den = 244;
			जाओ sysclk1_based;
		पूर्ण
	पूर्ण

	/* Numerator/dक्रमागतerator values refer TRM Realसमय Counter section */
	चयन (rate) अणु
	हाल 12000000:
		num = 64;
		den = 125;
		अवरोध;
	हाल 13000000:
		num = 768;
		den = 1625;
		अवरोध;
	हाल 19200000:
		num = 8;
		den = 25;
		अवरोध;
	हाल 20000000:
		num = 192;
		den = 625;
		अवरोध;
	हाल 26000000:
		num = 384;
		den = 1625;
		अवरोध;
	हाल 27000000:
		num = 256;
		den = 1125;
		अवरोध;
	हाल 38400000:
	शेष:
		/* Program it क्रम 38.4 MHz */
		num = 4;
		den = 25;
		अवरोध;
	पूर्ण

sysclk1_based:
	/* Program numerator and dक्रमागतerator रेजिस्टरs */
	reg = पढ़ोl_relaxed(base + INCREMENTER_NUMERATOR_OFFSET) &
			NUMERATOR_DENUMERATOR_MASK;
	reg |= num;
	ग_लिखोl_relaxed(reg, base + INCREMENTER_NUMERATOR_OFFSET);

	reg = पढ़ोl_relaxed(base + INCREMENTER_DENUMERATOR_RELOAD_OFFSET) &
			NUMERATOR_DENUMERATOR_MASK;
	reg |= den;
	ग_लिखोl_relaxed(reg, base + INCREMENTER_DENUMERATOR_RELOAD_OFFSET);

	arch_समयr_freq = DIV_ROUND_UP_ULL(rate * num, den);
	set_cntfreq();

	iounmap(base);
पूर्ण

व्योम __init omap5_realसमय_प्रकारimer_init(व्योम)
अणु
	omap_clk_init();
	realसमय_counter_init();

	समयr_probe();
पूर्ण
