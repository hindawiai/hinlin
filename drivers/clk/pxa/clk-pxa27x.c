<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell PXA27x family घड़ीs
 *
 * Copyright (C) 2014 Robert Jarzmik
 *
 * Heavily inspired from क्रमmer arch/arm/mach-pxa/घड़ी.c.
 */
#समावेश <linux/clk-provider.h>
#समावेश <mach/pxa2xx-regs.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of.h>

#समावेश <mach/smemc.h>

#समावेश <dt-bindings/घड़ी/pxa-घड़ी.h>
#समावेश "clk-pxa.h"

#घोषणा KHz 1000
#घोषणा MHz (1000 * 1000)

क्रमागत अणु
	PXA_CORE_13Mhz = 0,
	PXA_CORE_RUN,
	PXA_CORE_TURBO,
पूर्ण;

क्रमागत अणु
	PXA_BUS_13Mhz = 0,
	PXA_BUS_RUN,
पूर्ण;

क्रमागत अणु
	PXA_LCD_13Mhz = 0,
	PXA_LCD_RUN,
पूर्ण;

क्रमागत अणु
	PXA_MEM_13Mhz = 0,
	PXA_MEM_SYSTEM_BUS,
	PXA_MEM_RUN,
पूर्ण;

#घोषणा PXA27x_CLKCFG(B, HT, T)			\
	(CLKCFG_FCS |				\
	 ((B)  ? CLKCFG_FASTBUS : 0) |		\
	 ((HT) ? CLKCFG_HALFTURBO : 0) |	\
	 ((T)  ? CLKCFG_TURBO : 0))
#घोषणा PXA27x_CCCR(A, L, N2) (A << 25 | N2 << 7 | L)

#घोषणा MDCNFG_DRAC2(mdcnfg)	(((mdcnfg) >> 21) & 0x3)
#घोषणा MDCNFG_DRAC0(mdcnfg)	(((mdcnfg) >> 5) & 0x3)

/* Define the refresh period in mSec क्रम the SDRAM and the number of rows */
#घोषणा SDRAM_TREF	64	/* standard 64ms SDRAM */

अटल स्थिर अक्षर * स्थिर get_freq_khz[] = अणु
	"core", "run", "cpll", "memory",
	"system_bus"
पूर्ण;

अटल पूर्णांक get_sdram_rows(व्योम)
अणु
	अटल पूर्णांक sdram_rows;
	अचिन्हित पूर्णांक drac2 = 0, drac0 = 0;
	u32 mdcnfg;

	अगर (sdram_rows)
		वापस sdram_rows;

	mdcnfg = पढ़ोl_relaxed(MDCNFG);

	अगर (mdcnfg & (MDCNFG_DE2 | MDCNFG_DE3))
		drac2 = MDCNFG_DRAC2(mdcnfg);

	अगर (mdcnfg & (MDCNFG_DE0 | MDCNFG_DE1))
		drac0 = MDCNFG_DRAC0(mdcnfg);

	sdram_rows = 1 << (11 + max(drac0, drac2));
	वापस sdram_rows;
पूर्ण

अटल u32 mdrefr_dri(अचिन्हित पूर्णांक freq_khz)
अणु
	u32 पूर्णांकerval = freq_khz * SDRAM_TREF / get_sdram_rows();

	वापस (पूर्णांकerval - 31) / 32;
पूर्ण

/*
 * Get the घड़ी frequency as reflected by CCSR and the turbo flag.
 * We assume these values have been applied via a fcs.
 * If info is not 0 we also display the current settings.
 */
अचिन्हित पूर्णांक pxa27x_get_clk_frequency_khz(पूर्णांक info)
अणु
	काष्ठा clk *clk;
	अचिन्हित दीर्घ clks[5];
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		clk = clk_get(शून्य, get_freq_khz[i]);
		अगर (IS_ERR(clk)) अणु
			clks[i] = 0;
		पूर्ण अन्यथा अणु
			clks[i] = clk_get_rate(clk);
			clk_put(clk);
		पूर्ण
	पूर्ण
	अगर (info) अणु
		pr_info("Run Mode clock: %ld.%02ldMHz\n",
			clks[1] / 1000000, (clks[1] % 1000000) / 10000);
		pr_info("Turbo Mode clock: %ld.%02ldMHz\n",
			clks[2] / 1000000, (clks[2] % 1000000) / 10000);
		pr_info("Memory clock: %ld.%02ldMHz\n",
			clks[3] / 1000000, (clks[3] % 1000000) / 10000);
		pr_info("System bus clock: %ld.%02ldMHz\n",
			clks[4] / 1000000, (clks[4] % 1000000) / 10000);
	पूर्ण
	वापस (अचिन्हित पूर्णांक)clks[0] / KHz;
पूर्ण

bool pxa27x_is_ppll_disabled(व्योम)
अणु
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);

	वापस ccsr & (1 << CCCR_PPDIS_BIT);
पूर्ण

#घोषणा PXA27X_CKEN(dev_id, con_id, parents, mult_hp, भाग_hp,		\
		    bit, is_lp, flags)					\
	PXA_CKEN(dev_id, con_id, bit, parents, 1, 1, mult_hp, भाग_hp,	\
		 is_lp,  CKEN, CKEN_ ## bit, flags)
#घोषणा PXA27X_PBUS_CKEN(dev_id, con_id, bit, mult_hp, भाग_hp, delay)	\
	PXA27X_CKEN(dev_id, con_id, pxa27x_pbus_parents, mult_hp,	\
		    भाग_hp, bit, pxa27x_is_ppll_disabled, 0)

PARENTS(pxa27x_pbus) = अणु "osc_13mhz", "ppll_312mhz" पूर्ण;
PARENTS(pxa27x_sbus) = अणु "system_bus", "system_bus" पूर्ण;
PARENTS(pxa27x_32Mhz_bus) = अणु "osc_32_768khz", "osc_32_768khz" पूर्ण;
PARENTS(pxa27x_lcd_bus) = अणु "lcd_base", "lcd_base" पूर्ण;
PARENTS(pxa27x_membus) = अणु "lcd_base", "lcd_base" पूर्ण;

#घोषणा PXA27X_CKEN_1RATE(dev_id, con_id, bit, parents, delay)		\
	PXA_CKEN_1RATE(dev_id, con_id, bit, parents,			\
		       CKEN, CKEN_ ## bit, 0)
#घोषणा PXA27X_CKEN_1RATE_AO(dev_id, con_id, bit, parents, delay)	\
	PXA_CKEN_1RATE(dev_id, con_id, bit, parents,			\
		       CKEN, CKEN_ ## bit, CLK_IGNORE_UNUSED)

अटल काष्ठा desc_clk_cken pxa27x_घड़ीs[] __initdata = अणु
	PXA27X_PBUS_CKEN("pxa2xx-uart.0", शून्य, FFUART, 2, 42, 1),
	PXA27X_PBUS_CKEN("pxa2xx-uart.1", शून्य, BTUART, 2, 42, 1),
	PXA27X_PBUS_CKEN("pxa2xx-uart.2", शून्य, STUART, 2, 42, 1),
	PXA27X_PBUS_CKEN("pxa2xx-i2s", शून्य, I2S, 2, 51, 0),
	PXA27X_PBUS_CKEN("pxa2xx-i2c.0", शून्य, I2C, 2, 19, 0),
	PXA27X_PBUS_CKEN("pxa27x-udc", शून्य, USB, 2, 13, 5),
	PXA27X_PBUS_CKEN("pxa2xx-mci.0", शून्य, MMC, 2, 32, 0),
	PXA27X_PBUS_CKEN("pxa2xx-ir", "FICPCLK", FICP, 2, 13, 0),
	PXA27X_PBUS_CKEN("pxa27x-ohci", शून्य, USBHOST, 2, 13, 0),
	PXA27X_PBUS_CKEN("pxa2xx-i2c.1", शून्य, PWRI2C, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-ssp.0", शून्य, SSP1, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-ssp.1", शून्य, SSP2, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-ssp.2", शून्य, SSP3, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-pwm.0", शून्य, PWM0, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-pwm.1", शून्य, PWM1, 1, 24, 0),
	PXA27X_PBUS_CKEN(शून्य, "MSLCLK", MSL, 2, 13, 0),
	PXA27X_PBUS_CKEN(शून्य, "USIMCLK", USIM, 2, 13, 0),
	PXA27X_PBUS_CKEN(शून्य, "MSTKCLK", MEMSTK, 2, 32, 0),
	PXA27X_PBUS_CKEN(शून्य, "AC97CLK", AC97, 1, 1, 0),
	PXA27X_PBUS_CKEN(शून्य, "AC97CONFCLK", AC97CONF, 1, 1, 0),
	PXA27X_PBUS_CKEN(शून्य, "OSTIMER0", OSTIMER, 1, 96, 0),

	PXA27X_CKEN_1RATE("pxa27x-keypad", शून्य, KEYPAD,
			  pxa27x_32Mhz_bus_parents, 0),
	PXA27X_CKEN_1RATE(शून्य, "IMCLK", IM, pxa27x_sbus_parents, 0),
	PXA27X_CKEN_1RATE("pxa2xx-fb", शून्य, LCD, pxa27x_lcd_bus_parents, 0),
	PXA27X_CKEN_1RATE("pxa27x-camera.0", शून्य, CAMERA,
			  pxa27x_lcd_bus_parents, 0),
	PXA27X_CKEN_1RATE_AO("pxa2xx-pcmcia", शून्य, MEMC,
			     pxa27x_membus_parents, 0),

पूर्ण;

/*
 * PXA270 definitions
 *
 * For the PXA27x:
 * Control variables are A, L, 2N क्रम CCCR; B, HT, T क्रम CLKCFG.
 *
 * A = 0 => memory controller घड़ी from table 3-7,
 * A = 1 => memory controller घड़ी = प्रणाली bus घड़ी
 * Run mode frequency	= 13 MHz * L
 * Turbo mode frequency = 13 MHz * L * N
 * System bus frequency = 13 MHz * L / (B + 1)
 *
 * In CCCR:
 * A = 1
 * L = 16	  oscillator to run mode ratio
 * 2N = 6	  2 * (turbo mode to run mode ratio)
 *
 * In CCLKCFG:
 * B = 1	  Fast bus mode
 * HT = 0	  Half-Turbo mode
 * T = 1	  Turbo mode
 *
 * For now, just support some of the combinations in table 3-7 of
 * PXA27x Processor Family Developer's Manual to simplअगरy frequency
 * change sequences.
 */
अटल काष्ठा pxa2xx_freq pxa27x_freqs[] = अणु
	अणु104000000, 104000, PXA27x_CCCR(1,  8, 2), 0, PXA27x_CLKCFG(1, 0, 1) पूर्ण,
	अणु156000000, 104000, PXA27x_CCCR(1,  8, 3), 0, PXA27x_CLKCFG(1, 0, 1) पूर्ण,
	अणु208000000, 208000, PXA27x_CCCR(0, 16, 2), 1, PXA27x_CLKCFG(0, 0, 1) पूर्ण,
	अणु312000000, 208000, PXA27x_CCCR(1, 16, 3), 1, PXA27x_CLKCFG(1, 0, 1) पूर्ण,
	अणु416000000, 208000, PXA27x_CCCR(1, 16, 4), 1, PXA27x_CLKCFG(1, 0, 1) पूर्ण,
	अणु520000000, 208000, PXA27x_CCCR(1, 16, 5), 1, PXA27x_CLKCFG(1, 0, 1) पूर्ण,
	अणु624000000, 208000, PXA27x_CCCR(1, 16, 6), 1, PXA27x_CLKCFG(1, 0, 1) पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ clk_pxa27x_cpll_get_rate(काष्ठा clk_hw *hw,
	अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ clkcfg;
	अचिन्हित पूर्णांक t, ht;
	अचिन्हित पूर्णांक l, L, n2, N;
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);

	यंत्र("mrc\tp14, 0, %0, c6, c0, 0" : "=r" (clkcfg));
	t  = clkcfg & (1 << 0);
	ht = clkcfg & (1 << 2);

	l  = ccsr & CCSR_L_MASK;
	n2 = (ccsr & CCSR_N2_MASK) >> CCSR_N2_SHIFT;
	L  = l * parent_rate;
	N  = (L * n2) / 2;

	वापस N;
पूर्ण

अटल पूर्णांक clk_pxa27x_cpll_determine_rate(काष्ठा clk_hw *hw,
					  काष्ठा clk_rate_request *req)
अणु
	वापस pxa2xx_determine_rate(req, pxa27x_freqs,
				     ARRAY_SIZE(pxa27x_freqs));
पूर्ण

अटल पूर्णांक clk_pxa27x_cpll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक i;

	pr_debug("%s(rate=%lu parent_rate=%lu)\n", __func__, rate, parent_rate);
	क्रम (i = 0; i < ARRAY_SIZE(pxa27x_freqs); i++)
		अगर (pxa27x_freqs[i].cpll == rate)
			अवरोध;

	अगर (i >= ARRAY_SIZE(pxa27x_freqs))
		वापस -EINVAL;

	pxa2xx_cpll_change(&pxa27x_freqs[i], mdrefr_dri, MDREFR, CCCR);
	वापस 0;
पूर्ण

PARENTS(clk_pxa27x_cpll) = अणु "osc_13mhz" पूर्ण;
RATE_OPS(clk_pxa27x_cpll, "cpll");

अटल अचिन्हित दीर्घ clk_pxa27x_lcd_base_get_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित पूर्णांक l, osc_क्रमced;
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);
	अचिन्हित दीर्घ cccr = पढ़ोl(CCCR);

	l  = ccsr & CCSR_L_MASK;
	osc_क्रमced = ccsr & (1 << CCCR_CPDIS_BIT);
	अगर (osc_क्रमced) अणु
		अगर (cccr & (1 << CCCR_LCD_26_BIT))
			वापस parent_rate * 2;
		अन्यथा
			वापस parent_rate;
	पूर्ण

	अगर (l <= 7)
		वापस parent_rate;
	अगर (l <= 16)
		वापस parent_rate / 2;
	वापस parent_rate / 4;
पूर्ण

अटल u8 clk_pxa27x_lcd_base_get_parent(काष्ठा clk_hw *hw)
अणु
	अचिन्हित पूर्णांक osc_क्रमced;
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);

	osc_क्रमced = ccsr & (1 << CCCR_CPDIS_BIT);
	अगर (osc_क्रमced)
		वापस PXA_LCD_13Mhz;
	अन्यथा
		वापस PXA_LCD_RUN;
पूर्ण

PARENTS(clk_pxa27x_lcd_base) = अणु "osc_13mhz", "run" पूर्ण;
MUX_RO_RATE_RO_OPS(clk_pxa27x_lcd_base, "lcd_base");

अटल व्योम __init pxa27x_रेजिस्टर_plls(व्योम)
अणु
	clk_रेजिस्टर_fixed_rate(शून्य, "osc_13mhz", शून्य,
				CLK_GET_RATE_NOCACHE,
				13 * MHz);
	clkdev_pxa_रेजिस्टर(CLK_OSC32k768, "osc_32_768khz", शून्य,
			    clk_रेजिस्टर_fixed_rate(शून्य, "osc_32_768khz", शून्य,
						    CLK_GET_RATE_NOCACHE,
						    32768 * KHz));
	clk_रेजिस्टर_fixed_rate(शून्य, "clk_dummy", शून्य, 0, 0);
	clk_रेजिस्टर_fixed_factor(शून्य, "ppll_312mhz", "osc_13mhz", 0, 24, 1);
पूर्ण

अटल u8 clk_pxa27x_core_get_parent(काष्ठा clk_hw *hw)
अणु
	अचिन्हित दीर्घ clkcfg;
	अचिन्हित पूर्णांक t, ht, osc_क्रमced;
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);

	osc_क्रमced = ccsr & (1 << CCCR_CPDIS_BIT);
	अगर (osc_क्रमced)
		वापस PXA_CORE_13Mhz;

	यंत्र("mrc\tp14, 0, %0, c6, c0, 0" : "=r" (clkcfg));
	t  = clkcfg & (1 << 0);
	ht = clkcfg & (1 << 2);

	अगर (ht || t)
		वापस PXA_CORE_TURBO;
	वापस PXA_CORE_RUN;
पूर्ण

अटल पूर्णांक clk_pxa27x_core_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	अगर (index > PXA_CORE_TURBO)
		वापस -EINVAL;

	pxa2xx_core_turbo_चयन(index == PXA_CORE_TURBO);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pxa27x_core_determine_rate(काष्ठा clk_hw *hw,
					  काष्ठा clk_rate_request *req)
अणु
	वापस __clk_mux_determine_rate(hw, req);
पूर्ण

PARENTS(clk_pxa27x_core) = अणु "osc_13mhz", "run", "cpll" पूर्ण;
MUX_OPS(clk_pxa27x_core, "core", CLK_SET_RATE_PARENT);

अटल अचिन्हित दीर्घ clk_pxa27x_run_get_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);
	अचिन्हित पूर्णांक n2 = (ccsr & CCSR_N2_MASK) >> CCSR_N2_SHIFT;

	वापस (parent_rate / n2) * 2;
पूर्ण
PARENTS(clk_pxa27x_run) = अणु "cpll" पूर्ण;
RATE_RO_OPS(clk_pxa27x_run, "run");

अटल व्योम __init pxa27x_रेजिस्टर_core(व्योम)
अणु
	clkdev_pxa_रेजिस्टर(CLK_NONE, "cpll", शून्य,
			    clk_रेजिस्टर_clk_pxa27x_cpll());
	clkdev_pxa_रेजिस्टर(CLK_NONE, "run", शून्य,
			    clk_रेजिस्टर_clk_pxa27x_run());
	clkdev_pxa_रेजिस्टर(CLK_CORE, "core", शून्य,
			    clk_रेजिस्टर_clk_pxa27x_core());
पूर्ण

अटल अचिन्हित दीर्घ clk_pxa27x_प्रणाली_bus_get_rate(काष्ठा clk_hw *hw,
						    अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ clkcfg;
	अचिन्हित पूर्णांक b, osc_क्रमced;
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);

	osc_क्रमced = ccsr & (1 << CCCR_CPDIS_BIT);
	यंत्र("mrc\tp14, 0, %0, c6, c0, 0" : "=r" (clkcfg));
	b  = clkcfg & (1 << 3);

	अगर (osc_क्रमced)
		वापस parent_rate;
	अगर (b)
		वापस parent_rate;
	अन्यथा
		वापस parent_rate / 2;
पूर्ण

अटल u8 clk_pxa27x_प्रणाली_bus_get_parent(काष्ठा clk_hw *hw)
अणु
	अचिन्हित पूर्णांक osc_क्रमced;
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);

	osc_क्रमced = ccsr & (1 << CCCR_CPDIS_BIT);
	अगर (osc_क्रमced)
		वापस PXA_BUS_13Mhz;
	अन्यथा
		वापस PXA_BUS_RUN;
पूर्ण

PARENTS(clk_pxa27x_प्रणाली_bus) = अणु "osc_13mhz", "run" पूर्ण;
MUX_RO_RATE_RO_OPS(clk_pxa27x_प्रणाली_bus, "system_bus");

अटल अचिन्हित दीर्घ clk_pxa27x_memory_get_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित पूर्णांक a, l, osc_क्रमced;
	अचिन्हित दीर्घ cccr = पढ़ोl(CCCR);
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);

	osc_क्रमced = ccsr & (1 << CCCR_CPDIS_BIT);
	a = cccr & (1 << CCCR_A_BIT);
	l  = ccsr & CCSR_L_MASK;

	अगर (osc_क्रमced || a)
		वापस parent_rate;
	अगर (l <= 10)
		वापस parent_rate;
	अगर (l <= 20)
		वापस parent_rate / 2;
	वापस parent_rate / 4;
पूर्ण

अटल u8 clk_pxa27x_memory_get_parent(काष्ठा clk_hw *hw)
अणु
	अचिन्हित पूर्णांक osc_क्रमced, a;
	अचिन्हित दीर्घ cccr = पढ़ोl(CCCR);
	अचिन्हित दीर्घ ccsr = पढ़ोl(CCSR);

	osc_क्रमced = ccsr & (1 << CCCR_CPDIS_BIT);
	a = cccr & (1 << CCCR_A_BIT);
	अगर (osc_क्रमced)
		वापस PXA_MEM_13Mhz;
	अगर (a)
		वापस PXA_MEM_SYSTEM_BUS;
	अन्यथा
		वापस PXA_MEM_RUN;
पूर्ण

PARENTS(clk_pxa27x_memory) = अणु "osc_13mhz", "system_bus", "run" पूर्ण;
MUX_RO_RATE_RO_OPS(clk_pxa27x_memory, "memory");

#घोषणा DUMMY_CLK(_con_id, _dev_id, _parent) \
	अणु .con_id = _con_id, .dev_id = _dev_id, .parent = _parent पूर्ण
काष्ठा dummy_clk अणु
	स्थिर अक्षर *con_id;
	स्थिर अक्षर *dev_id;
	स्थिर अक्षर *parent;
पूर्ण;
अटल काष्ठा dummy_clk dummy_clks[] __initdata = अणु
	DUMMY_CLK(शून्य, "pxa27x-gpio", "osc_32_768khz"),
	DUMMY_CLK(शून्य, "pxa-rtc", "osc_32_768khz"),
	DUMMY_CLK(शून्य, "sa1100-rtc", "osc_32_768khz"),
	DUMMY_CLK("UARTCLK", "pxa2xx-ir", "STUART"),
पूर्ण;

अटल व्योम __init pxa27x_dummy_घड़ीs_init(व्योम)
अणु
	काष्ठा clk *clk;
	काष्ठा dummy_clk *d;
	स्थिर अक्षर *name;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dummy_clks); i++) अणु
		d = &dummy_clks[i];
		name = d->dev_id ? d->dev_id : d->con_id;
		clk = clk_रेजिस्टर_fixed_factor(शून्य, name, d->parent, 0, 1, 1);
		clk_रेजिस्टर_clkdev(clk, d->con_id, d->dev_id);
	पूर्ण
पूर्ण

अटल व्योम __init pxa27x_base_घड़ीs_init(व्योम)
अणु
	pxa27x_रेजिस्टर_plls();
	pxa27x_रेजिस्टर_core();
	clkdev_pxa_रेजिस्टर(CLK_NONE, "system_bus", शून्य,
			    clk_रेजिस्टर_clk_pxa27x_प्रणाली_bus());
	clkdev_pxa_रेजिस्टर(CLK_NONE, "memory", शून्य,
			    clk_रेजिस्टर_clk_pxa27x_memory());
	clk_रेजिस्टर_clk_pxa27x_lcd_base();
पूर्ण

पूर्णांक __init pxa27x_घड़ीs_init(व्योम)
अणु
	pxa27x_base_घड़ीs_init();
	pxa27x_dummy_घड़ीs_init();
	वापस clk_pxa_cken_init(pxa27x_घड़ीs, ARRAY_SIZE(pxa27x_घड़ीs));
पूर्ण

अटल व्योम __init pxa27x_dt_घड़ीs_init(काष्ठा device_node *np)
अणु
	pxa27x_घड़ीs_init();
	clk_pxa_dt_common_init(np);
पूर्ण
CLK_OF_DECLARE(pxa_clks, "marvell,pxa270-clocks", pxa27x_dt_घड़ीs_init);
