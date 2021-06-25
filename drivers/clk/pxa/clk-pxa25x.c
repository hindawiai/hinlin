<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell PXA25x family घड़ीs
 *
 * Copyright (C) 2014 Robert Jarzmik
 *
 * Heavily inspired from क्रमmer arch/arm/mach-pxa/pxa25x.c.
 *
 * For non-devicetree platक्रमms. Once pxa is fully converted to devicetree, this
 * should go away.
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <mach/pxa2xx-regs.h>
#समावेश <mach/smemc.h>

#समावेश <dt-bindings/घड़ी/pxa-घड़ी.h>
#समावेश "clk-pxa.h"

#घोषणा KHz 1000
#घोषणा MHz (1000 * 1000)

क्रमागत अणु
	PXA_CORE_RUN = 0,
	PXA_CORE_TURBO,
पूर्ण;

#घोषणा PXA25x_CLKCFG(T)			\
	(CLKCFG_FCS |				\
	 ((T) ? CLKCFG_TURBO : 0))
#घोषणा PXA25x_CCCR(N2, M, L) (N2 << 7 | M << 5 | L)

#घोषणा MDCNFG_DRAC2(mdcnfg)	(((mdcnfg) >> 21) & 0x3)
#घोषणा MDCNFG_DRAC0(mdcnfg)	(((mdcnfg) >> 5) & 0x3)

/* Define the refresh period in mSec क्रम the SDRAM and the number of rows */
#घोषणा SDRAM_TREF	64	/* standard 64ms SDRAM */

/*
 * Various घड़ी factors driven by the CCCR रेजिस्टर.
 */

/* Crystal Frequency to Memory Frequency Multiplier (L) */
अटल अचिन्हित अक्षर L_clk_mult[32] = अणु 0, 27, 32, 36, 40, 45, 0, पूर्ण;

/* Memory Frequency to Run Mode Frequency Multiplier (M) */
अटल अचिन्हित अक्षर M_clk_mult[4] = अणु 0, 1, 2, 4 पूर्ण;

/* Run Mode Frequency to Turbo Mode Frequency Multiplier (N) */
/* Note: we store the value N * 2 here. */
अटल अचिन्हित अक्षर N2_clk_mult[8] = अणु 0, 0, 2, 3, 4, 0, 6, 0 पूर्ण;

अटल स्थिर अक्षर * स्थिर get_freq_khz[] = अणु
	"core", "run", "cpll", "memory"
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

	वापस पूर्णांकerval / 32;
पूर्ण

/*
 * Get the घड़ी frequency as reflected by CCCR and the turbo flag.
 * We assume these values have been applied via a fcs.
 * If info is not 0 we also display the current settings.
 */
अचिन्हित पूर्णांक pxa25x_get_clk_frequency_khz(पूर्णांक info)
अणु
	काष्ठा clk *clk;
	अचिन्हित दीर्घ clks[5];
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(get_freq_khz); i++) अणु
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
	पूर्ण

	वापस (अचिन्हित पूर्णांक)clks[0] / KHz;
पूर्ण

अटल अचिन्हित दीर्घ clk_pxa25x_memory_get_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ cccr = पढ़ोl(CCCR);
	अचिन्हित पूर्णांक m = M_clk_mult[(cccr >> 5) & 0x03];

	वापस parent_rate / m;
पूर्ण
PARENTS(clk_pxa25x_memory) = अणु "run" पूर्ण;
RATE_RO_OPS(clk_pxa25x_memory, "memory");

PARENTS(pxa25x_pbus95) = अणु "ppll_95_85mhz", "ppll_95_85mhz" पूर्ण;
PARENTS(pxa25x_pbus147) = अणु "ppll_147_46mhz", "ppll_147_46mhz" पूर्ण;
PARENTS(pxa25x_osc3) = अणु "osc_3_6864mhz", "osc_3_6864mhz" पूर्ण;

#घोषणा PXA25X_CKEN(dev_id, con_id, parents, mult, भाग,			\
		    bit, is_lp, flags)					\
	PXA_CKEN(dev_id, con_id, bit, parents, mult, भाग, mult, भाग,	\
		 is_lp,  CKEN, CKEN_ ## bit, flags)
#घोषणा PXA25X_PBUS95_CKEN(dev_id, con_id, bit, mult_hp, भाग_hp, delay)	\
	PXA25X_CKEN(dev_id, con_id, pxa25x_pbus95_parents, mult_hp,	\
		    भाग_hp, bit, शून्य, 0)
#घोषणा PXA25X_PBUS147_CKEN(dev_id, con_id, bit, mult_hp, भाग_hp, delay)\
	PXA25X_CKEN(dev_id, con_id, pxa25x_pbus147_parents, mult_hp,	\
		    भाग_hp, bit, शून्य, 0)
#घोषणा PXA25X_OSC3_CKEN(dev_id, con_id, bit, mult_hp, भाग_hp, delay)	\
	PXA25X_CKEN(dev_id, con_id, pxa25x_osc3_parents, mult_hp,	\
		    भाग_hp, bit, शून्य, 0)

#घोषणा PXA25X_CKEN_1RATE(dev_id, con_id, bit, parents, delay)		\
	PXA_CKEN_1RATE(dev_id, con_id, bit, parents,			\
		       CKEN, CKEN_ ## bit, 0)
#घोषणा PXA25X_CKEN_1RATE_AO(dev_id, con_id, bit, parents, delay)	\
	PXA_CKEN_1RATE(dev_id, con_id, bit, parents,			\
		       CKEN, CKEN_ ## bit, CLK_IGNORE_UNUSED)

अटल काष्ठा desc_clk_cken pxa25x_घड़ीs[] __initdata = अणु
	PXA25X_PBUS95_CKEN("pxa2xx-mci.0", शून्य, MMC, 1, 5, 0),
	PXA25X_PBUS95_CKEN("pxa2xx-i2c.0", शून्य, I2C, 1, 3, 0),
	PXA25X_PBUS95_CKEN("pxa2xx-ir", "FICPCLK", FICP, 1, 2, 0),
	PXA25X_PBUS95_CKEN("pxa25x-udc", शून्य, USB, 1, 2, 5),
	PXA25X_PBUS147_CKEN("pxa2xx-uart.0", शून्य, FFUART, 1, 10, 1),
	PXA25X_PBUS147_CKEN("pxa2xx-uart.1", शून्य, BTUART, 1, 10, 1),
	PXA25X_PBUS147_CKEN("pxa2xx-uart.2", शून्य, STUART, 1, 10, 1),
	PXA25X_PBUS147_CKEN("pxa2xx-uart.3", शून्य, HWUART, 1, 10, 1),
	PXA25X_PBUS147_CKEN("pxa2xx-i2s", शून्य, I2S, 1, 10, 0),
	PXA25X_PBUS147_CKEN(शून्य, "AC97CLK", AC97, 1, 12, 0),
	PXA25X_OSC3_CKEN("pxa25x-ssp.0", शून्य, SSP, 1, 1, 0),
	PXA25X_OSC3_CKEN("pxa25x-nssp.1", शून्य, NSSP, 1, 1, 0),
	PXA25X_OSC3_CKEN("pxa25x-nssp.2", शून्य, ASSP, 1, 1, 0),
	PXA25X_OSC3_CKEN("pxa25x-pwm.0", शून्य, PWM0, 1, 1, 0),
	PXA25X_OSC3_CKEN("pxa25x-pwm.1", शून्य, PWM1, 1, 1, 0),

	PXA25X_CKEN_1RATE("pxa2xx-fb", शून्य, LCD, clk_pxa25x_memory_parents, 0),
	PXA25X_CKEN_1RATE_AO("pxa2xx-pcmcia", शून्य, MEMC,
			     clk_pxa25x_memory_parents, 0),
पूर्ण;

/*
 * In this table, PXA25x_CCCR(N2, M, L) has the following meaning, where :
 *   - freq_cpll = n * m * L * 3.6864 MHz
 *   - n = N2 / 2
 *   - m = 2^(M - 1), where 1 <= M <= 3
 *   - l = L_clk_mult[L], ie. अणु 0, 27, 32, 36, 40, 45, 0, पूर्ण[L]
 */
अटल काष्ठा pxa2xx_freq pxa25x_freqs[] = अणु
	/* CPU  MEMBUS  CCCR                  DIV2 CCLKCFG      */
	अणु 99532800, 99500, PXA25x_CCCR(2,  1, 1),  1, PXA25x_CLKCFG(1)पूर्ण,
	अणु199065600, 99500, PXA25x_CCCR(4,  1, 1),  0, PXA25x_CLKCFG(1)पूर्ण,
	अणु298598400, 99500, PXA25x_CCCR(3,  2, 1),  0, PXA25x_CLKCFG(1)पूर्ण,
	अणु398131200, 99500, PXA25x_CCCR(4,  2, 1),  0, PXA25x_CLKCFG(1)पूर्ण,
पूर्ण;

अटल u8 clk_pxa25x_core_get_parent(काष्ठा clk_hw *hw)
अणु
	अचिन्हित दीर्घ clkcfg;
	अचिन्हित पूर्णांक t;

	यंत्र("mrc\tp14, 0, %0, c6, c0, 0" : "=r" (clkcfg));
	t  = clkcfg & (1 << 0);
	अगर (t)
		वापस PXA_CORE_TURBO;
	वापस PXA_CORE_RUN;
पूर्ण

अटल पूर्णांक clk_pxa25x_core_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	अगर (index > PXA_CORE_TURBO)
		वापस -EINVAL;

	pxa2xx_core_turbo_चयन(index == PXA_CORE_TURBO);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pxa25x_core_determine_rate(काष्ठा clk_hw *hw,
					  काष्ठा clk_rate_request *req)
अणु
	वापस __clk_mux_determine_rate(hw, req);
पूर्ण

PARENTS(clk_pxa25x_core) = अणु "run", "cpll" पूर्ण;
MUX_OPS(clk_pxa25x_core, "core", CLK_SET_RATE_PARENT);

अटल अचिन्हित दीर्घ clk_pxa25x_run_get_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ cccr = पढ़ोl(CCCR);
	अचिन्हित पूर्णांक n2 = N2_clk_mult[(cccr >> 7) & 0x07];

	वापस (parent_rate / n2) * 2;
पूर्ण
PARENTS(clk_pxa25x_run) = अणु "cpll" पूर्ण;
RATE_RO_OPS(clk_pxa25x_run, "run");

अटल अचिन्हित दीर्घ clk_pxa25x_cpll_get_rate(काष्ठा clk_hw *hw,
	अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ clkcfg, cccr = पढ़ोl(CCCR);
	अचिन्हित पूर्णांक l, m, n2, t;

	यंत्र("mrc\tp14, 0, %0, c6, c0, 0" : "=r" (clkcfg));
	t = clkcfg & (1 << 0);
	l  =  L_clk_mult[(cccr >> 0) & 0x1f];
	m = M_clk_mult[(cccr >> 5) & 0x03];
	n2 = N2_clk_mult[(cccr >> 7) & 0x07];

	वापस m * l * n2 * parent_rate / 2;
पूर्ण

अटल पूर्णांक clk_pxa25x_cpll_determine_rate(काष्ठा clk_hw *hw,
					  काष्ठा clk_rate_request *req)
अणु
	वापस pxa2xx_determine_rate(req, pxa25x_freqs,
				     ARRAY_SIZE(pxa25x_freqs));
पूर्ण

अटल पूर्णांक clk_pxa25x_cpll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक i;

	pr_debug("%s(rate=%lu parent_rate=%lu)\n", __func__, rate, parent_rate);
	क्रम (i = 0; i < ARRAY_SIZE(pxa25x_freqs); i++)
		अगर (pxa25x_freqs[i].cpll == rate)
			अवरोध;

	अगर (i >= ARRAY_SIZE(pxa25x_freqs))
		वापस -EINVAL;

	pxa2xx_cpll_change(&pxa25x_freqs[i], mdrefr_dri, MDREFR, CCCR);

	वापस 0;
पूर्ण
PARENTS(clk_pxa25x_cpll) = अणु "osc_3_6864mhz" पूर्ण;
RATE_OPS(clk_pxa25x_cpll, "cpll");

अटल व्योम __init pxa25x_रेजिस्टर_core(व्योम)
अणु
	clkdev_pxa_रेजिस्टर(CLK_NONE, "cpll", शून्य,
			    clk_रेजिस्टर_clk_pxa25x_cpll());
	clkdev_pxa_रेजिस्टर(CLK_NONE, "run", शून्य,
			    clk_रेजिस्टर_clk_pxa25x_run());
	clkdev_pxa_रेजिस्टर(CLK_CORE, "core", शून्य,
			    clk_रेजिस्टर_clk_pxa25x_core());
पूर्ण

अटल व्योम __init pxa25x_रेजिस्टर_plls(व्योम)
अणु
	clk_रेजिस्टर_fixed_rate(शून्य, "osc_3_6864mhz", शून्य,
				CLK_GET_RATE_NOCACHE, 3686400);
	clkdev_pxa_रेजिस्टर(CLK_OSC32k768, "osc_32_768khz", शून्य,
			    clk_रेजिस्टर_fixed_rate(शून्य, "osc_32_768khz", शून्य,
						    CLK_GET_RATE_NOCACHE,
						    32768));
	clk_रेजिस्टर_fixed_rate(शून्य, "clk_dummy", शून्य, 0, 0);
	clk_रेजिस्टर_fixed_factor(शून्य, "ppll_95_85mhz", "osc_3_6864mhz",
				  0, 26, 1);
	clk_रेजिस्टर_fixed_factor(शून्य, "ppll_147_46mhz", "osc_3_6864mhz",
				  0, 40, 1);
पूर्ण

अटल व्योम __init pxa25x_base_घड़ीs_init(व्योम)
अणु
	pxa25x_रेजिस्टर_plls();
	pxa25x_रेजिस्टर_core();
	clkdev_pxa_रेजिस्टर(CLK_NONE, "system_bus", शून्य,
			    clk_रेजिस्टर_clk_pxa25x_memory());
पूर्ण

#घोषणा DUMMY_CLK(_con_id, _dev_id, _parent) \
	अणु .con_id = _con_id, .dev_id = _dev_id, .parent = _parent पूर्ण
काष्ठा dummy_clk अणु
	स्थिर अक्षर *con_id;
	स्थिर अक्षर *dev_id;
	स्थिर अक्षर *parent;
पूर्ण;
अटल काष्ठा dummy_clk dummy_clks[] __initdata = अणु
	DUMMY_CLK(शून्य, "pxa25x-gpio", "osc_32_768khz"),
	DUMMY_CLK(शून्य, "pxa26x-gpio", "osc_32_768khz"),
	DUMMY_CLK("GPIO11_CLK", शून्य, "osc_3_6864mhz"),
	DUMMY_CLK("GPIO12_CLK", शून्य, "osc_32_768khz"),
	DUMMY_CLK(शून्य, "sa1100-rtc", "osc_32_768khz"),
	DUMMY_CLK("OSTIMER0", शून्य, "osc_3_6864mhz"),
	DUMMY_CLK("UARTCLK", "pxa2xx-ir", "STUART"),
पूर्ण;

अटल व्योम __init pxa25x_dummy_घड़ीs_init(व्योम)
अणु
	काष्ठा clk *clk;
	काष्ठा dummy_clk *d;
	स्थिर अक्षर *name;
	पूर्णांक i;

	/*
	 * All pinctrl logic has been wiped out of the घड़ी driver, especially
	 * क्रम gpio11 and gpio12 outमाला_दो. Machine code should ensure proper pin
	 * control (ie. pxa2xx_mfp_config() invocation).
	 */
	क्रम (i = 0; i < ARRAY_SIZE(dummy_clks); i++) अणु
		d = &dummy_clks[i];
		name = d->dev_id ? d->dev_id : d->con_id;
		clk = clk_रेजिस्टर_fixed_factor(शून्य, name, d->parent, 0, 1, 1);
		clk_रेजिस्टर_clkdev(clk, d->con_id, d->dev_id);
	पूर्ण
पूर्ण

पूर्णांक __init pxa25x_घड़ीs_init(व्योम)
अणु
	pxa25x_base_घड़ीs_init();
	pxa25x_dummy_घड़ीs_init();
	वापस clk_pxa_cken_init(pxa25x_घड़ीs, ARRAY_SIZE(pxa25x_घड़ीs));
पूर्ण

अटल व्योम __init pxa25x_dt_घड़ीs_init(काष्ठा device_node *np)
अणु
	pxa25x_घड़ीs_init();
	clk_pxa_dt_common_init(np);
पूर्ण
CLK_OF_DECLARE(pxa25x_clks, "marvell,pxa250-core-clocks",
	       pxa25x_dt_घड़ीs_init);
