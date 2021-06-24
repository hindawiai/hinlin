<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell PXA3xxx family घड़ीs
 *
 * Copyright (C) 2014 Robert Jarzmik
 *
 * Heavily inspired from क्रमmer arch/arm/mach-pxa/pxa3xx.c
 *
 * For non-devicetree platक्रमms. Once pxa is fully converted to devicetree, this
 * should go away.
 */
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of.h>
#समावेश <mach/smemc.h>
#समावेश <mach/pxa3xx-regs.h>

#समावेश <dt-bindings/घड़ी/pxa-घड़ी.h>
#समावेश "clk-pxa.h"

#घोषणा KHz 1000
#घोषणा MHz (1000 * 1000)

क्रमागत अणु
	PXA_CORE_60Mhz = 0,
	PXA_CORE_RUN,
	PXA_CORE_TURBO,
पूर्ण;

क्रमागत अणु
	PXA_BUS_60Mhz = 0,
	PXA_BUS_HSS,
पूर्ण;

/* crystal frequency to HSIO bus frequency multiplier (HSS) */
अटल अचिन्हित अक्षर hss_mult[4] = अणु 8, 12, 16, 24 पूर्ण;

/* crystal frequency to अटल memory controller multiplier (SMCFS) */
अटल अचिन्हित पूर्णांक smcfs_mult[8] = अणु 6, 0, 8, 0, 0, 16, पूर्ण;
अटल अचिन्हित पूर्णांक df_clkभाग[4] = अणु 1, 2, 4, 1 पूर्ण;

अटल स्थिर अक्षर * स्थिर get_freq_khz[] = अणु
	"core", "ring_osc_60mhz", "run", "cpll", "system_bus"
पूर्ण;

/*
 * Get the घड़ी frequency as reflected by ACSR and the turbo flag.
 * We assume these values have been applied via a fcs.
 * If info is not 0 we also display the current settings.
 */
अचिन्हित पूर्णांक pxa3xx_get_clk_frequency_khz(पूर्णांक info)
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
		pr_info("RO Mode clock: %ld.%02ldMHz\n",
			clks[1] / 1000000, (clks[0] % 1000000) / 10000);
		pr_info("Run Mode clock: %ld.%02ldMHz\n",
			clks[2] / 1000000, (clks[1] % 1000000) / 10000);
		pr_info("Turbo Mode clock: %ld.%02ldMHz\n",
			clks[3] / 1000000, (clks[2] % 1000000) / 10000);
		pr_info("System bus clock: %ld.%02ldMHz\n",
			clks[4] / 1000000, (clks[4] % 1000000) / 10000);
	पूर्ण
	वापस (अचिन्हित पूर्णांक)clks[0] / KHz;
पूर्ण

अटल अचिन्हित दीर्घ clk_pxa3xx_ac97_get_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ ac97_भाग, rate;

	ac97_भाग = AC97_DIV;

	/* This may loose precision क्रम some rates but won't क्रम the
	 * standard 24.576MHz.
	 */
	rate = parent_rate / 2;
	rate /= ((ac97_भाग >> 12) & 0x7fff);
	rate *= (ac97_भाग & 0xfff);

	वापस rate;
पूर्ण
PARENTS(clk_pxa3xx_ac97) = अणु "spll_624mhz" पूर्ण;
RATE_RO_OPS(clk_pxa3xx_ac97, "ac97");

अटल अचिन्हित दीर्घ clk_pxa3xx_smemc_get_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ acsr = ACSR;
	अचिन्हित दीर्घ memclkcfg = __raw_पढ़ोl(MEMCLKCFG);

	वापस (parent_rate / 48)  * smcfs_mult[(acsr >> 23) & 0x7] /
		df_clkभाग[(memclkcfg >> 16) & 0x3];
पूर्ण
PARENTS(clk_pxa3xx_smemc) = अणु "spll_624mhz" पूर्ण;
RATE_RO_OPS(clk_pxa3xx_smemc, "smemc");

अटल bool pxa3xx_is_ring_osc_क्रमced(व्योम)
अणु
	अचिन्हित दीर्घ acsr = ACSR;

	वापस acsr & ACCR_D0CS;
पूर्ण

PARENTS(pxa3xx_pbus) = अणु "ring_osc_60mhz", "spll_624mhz" पूर्ण;
PARENTS(pxa3xx_32Khz_bus) = अणु "osc_32_768khz", "osc_32_768khz" पूर्ण;
PARENTS(pxa3xx_13MHz_bus) = अणु "osc_13mhz", "osc_13mhz" पूर्ण;
PARENTS(pxa3xx_ac97_bus) = अणु "ring_osc_60mhz", "ac97" पूर्ण;
PARENTS(pxa3xx_sbus) = अणु "ring_osc_60mhz", "system_bus" पूर्ण;
PARENTS(pxa3xx_smemcbus) = अणु "ring_osc_60mhz", "smemc" पूर्ण;

#घोषणा CKEN_AB(bit) ((CKEN_ ## bit > 31) ? &CKENB : &CKENA)
#घोषणा PXA3XX_CKEN(dev_id, con_id, parents, mult_lp, भाग_lp, mult_hp,	\
		    भाग_hp, bit, is_lp, flags)				\
	PXA_CKEN(dev_id, con_id, bit, parents, mult_lp, भाग_lp,		\
		 mult_hp, भाग_hp, is_lp,  CKEN_AB(bit),			\
		 (CKEN_ ## bit % 32), flags)
#घोषणा PXA3XX_PBUS_CKEN(dev_id, con_id, bit, mult_lp, भाग_lp,		\
			 mult_hp, भाग_hp, delay)			\
	PXA3XX_CKEN(dev_id, con_id, pxa3xx_pbus_parents, mult_lp,	\
		    भाग_lp, mult_hp, भाग_hp, bit, pxa3xx_is_ring_osc_क्रमced, 0)
#घोषणा PXA3XX_CKEN_1RATE(dev_id, con_id, bit, parents)			\
	PXA_CKEN_1RATE(dev_id, con_id, bit, parents,			\
		       CKEN_AB(bit), (CKEN_ ## bit % 32), 0)

अटल काष्ठा desc_clk_cken pxa3xx_घड़ीs[] __initdata = अणु
	PXA3XX_PBUS_CKEN("pxa2xx-uart.0", शून्य, FFUART, 1, 4, 1, 42, 1),
	PXA3XX_PBUS_CKEN("pxa2xx-uart.1", शून्य, BTUART, 1, 4, 1, 42, 1),
	PXA3XX_PBUS_CKEN("pxa2xx-uart.2", शून्य, STUART, 1, 4, 1, 42, 1),
	PXA3XX_PBUS_CKEN("pxa2xx-i2c.0", शून्य, I2C, 2, 5, 1, 19, 0),
	PXA3XX_PBUS_CKEN("pxa27x-udc", शून्य, UDC, 1, 4, 1, 13, 5),
	PXA3XX_PBUS_CKEN("pxa27x-ohci", शून्य, USBH, 1, 4, 1, 13, 0),
	PXA3XX_PBUS_CKEN("pxa3xx-u2d", शून्य, USB2, 1, 4, 1, 13, 0),
	PXA3XX_PBUS_CKEN("pxa27x-pwm.0", शून्य, PWM0, 1, 6, 1, 48, 0),
	PXA3XX_PBUS_CKEN("pxa27x-pwm.1", शून्य, PWM1, 1, 6, 1, 48, 0),
	PXA3XX_PBUS_CKEN("pxa2xx-mci.0", शून्य, MMC1, 1, 4, 1, 24, 0),
	PXA3XX_PBUS_CKEN("pxa2xx-mci.1", शून्य, MMC2, 1, 4, 1, 24, 0),
	PXA3XX_PBUS_CKEN("pxa2xx-mci.2", शून्य, MMC3, 1, 4, 1, 24, 0),

	PXA3XX_CKEN_1RATE("pxa27x-keypad", शून्य, KEYPAD,
			  pxa3xx_32Khz_bus_parents),
	PXA3XX_CKEN_1RATE("pxa3xx-ssp.0", शून्य, SSP1, pxa3xx_13MHz_bus_parents),
	PXA3XX_CKEN_1RATE("pxa3xx-ssp.1", शून्य, SSP2, pxa3xx_13MHz_bus_parents),
	PXA3XX_CKEN_1RATE("pxa3xx-ssp.2", शून्य, SSP3, pxa3xx_13MHz_bus_parents),
	PXA3XX_CKEN_1RATE("pxa3xx-ssp.3", शून्य, SSP4, pxa3xx_13MHz_bus_parents),

	PXA3XX_CKEN(शून्य, "AC97CLK", pxa3xx_ac97_bus_parents, 1, 4, 1, 1, AC97,
		    pxa3xx_is_ring_osc_क्रमced, 0),
	PXA3XX_CKEN(शून्य, "CAMCLK", pxa3xx_sbus_parents, 1, 2, 1, 1, CAMERA,
		    pxa3xx_is_ring_osc_क्रमced, 0),
	PXA3XX_CKEN("pxa2xx-fb", शून्य, pxa3xx_sbus_parents, 1, 1, 1, 1, LCD,
		    pxa3xx_is_ring_osc_क्रमced, 0),
	PXA3XX_CKEN("pxa2xx-pcmcia", शून्य, pxa3xx_smemcbus_parents, 1, 4,
		    1, 1, SMC, pxa3xx_is_ring_osc_क्रमced, CLK_IGNORE_UNUSED),
पूर्ण;

अटल काष्ठा desc_clk_cken pxa300_310_घड़ीs[] __initdata = अणु

	PXA3XX_PBUS_CKEN("pxa3xx-gcu", शून्य, PXA300_GCU, 1, 1, 1, 1, 0),
	PXA3XX_PBUS_CKEN("pxa3xx-nand", शून्य, न_अंकD, 1, 2, 1, 4, 0),
	PXA3XX_CKEN_1RATE("pxa3xx-gpio", शून्य, GPIO, pxa3xx_13MHz_bus_parents),
पूर्ण;

अटल काष्ठा desc_clk_cken pxa320_घड़ीs[] __initdata = अणु
	PXA3XX_PBUS_CKEN("pxa3xx-nand", शून्य, न_अंकD, 1, 2, 1, 6, 0),
	PXA3XX_PBUS_CKEN("pxa3xx-gcu", शून्य, PXA320_GCU, 1, 1, 1, 1, 0),
	PXA3XX_CKEN_1RATE("pxa3xx-gpio", शून्य, GPIO, pxa3xx_13MHz_bus_parents),
पूर्ण;

अटल काष्ठा desc_clk_cken pxa93x_घड़ीs[] __initdata = अणु

	PXA3XX_PBUS_CKEN("pxa3xx-gcu", शून्य, PXA300_GCU, 1, 1, 1, 1, 0),
	PXA3XX_PBUS_CKEN("pxa3xx-nand", शून्य, न_अंकD, 1, 2, 1, 4, 0),
	PXA3XX_CKEN_1RATE("pxa93x-gpio", शून्य, GPIO, pxa3xx_13MHz_bus_parents),
पूर्ण;

अटल अचिन्हित दीर्घ clk_pxa3xx_प्रणाली_bus_get_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ acsr = ACSR;
	अचिन्हित पूर्णांक hss = (acsr >> 14) & 0x3;

	अगर (pxa3xx_is_ring_osc_क्रमced())
		वापस parent_rate;
	वापस parent_rate / 48 * hss_mult[hss];
पूर्ण

अटल u8 clk_pxa3xx_प्रणाली_bus_get_parent(काष्ठा clk_hw *hw)
अणु
	अगर (pxa3xx_is_ring_osc_क्रमced())
		वापस PXA_BUS_60Mhz;
	अन्यथा
		वापस PXA_BUS_HSS;
पूर्ण

PARENTS(clk_pxa3xx_प्रणाली_bus) = अणु "ring_osc_60mhz", "spll_624mhz" पूर्ण;
MUX_RO_RATE_RO_OPS(clk_pxa3xx_प्रणाली_bus, "system_bus");

अटल अचिन्हित दीर्घ clk_pxa3xx_core_get_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	वापस parent_rate;
पूर्ण

अटल u8 clk_pxa3xx_core_get_parent(काष्ठा clk_hw *hw)
अणु
	अचिन्हित दीर्घ xclkcfg;
	अचिन्हित पूर्णांक t;

	अगर (pxa3xx_is_ring_osc_क्रमced())
		वापस PXA_CORE_60Mhz;

	/* Read XCLKCFG रेजिस्टर turbo bit */
	__यंत्र__ __अस्थिर__("mrc\tp14, 0, %0, c6, c0, 0" : "=r"(xclkcfg));
	t = xclkcfg & 0x1;

	अगर (t)
		वापस PXA_CORE_TURBO;
	वापस PXA_CORE_RUN;
पूर्ण
PARENTS(clk_pxa3xx_core) = अणु "ring_osc_60mhz", "run", "cpll" पूर्ण;
MUX_RO_RATE_RO_OPS(clk_pxa3xx_core, "core");

अटल अचिन्हित दीर्घ clk_pxa3xx_run_get_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ acsr = ACSR;
	अचिन्हित पूर्णांक xn = (acsr & ACCR_XN_MASK) >> 8;
	अचिन्हित पूर्णांक t, xclkcfg;

	/* Read XCLKCFG रेजिस्टर turbo bit */
	__यंत्र__ __अस्थिर__("mrc\tp14, 0, %0, c6, c0, 0" : "=r"(xclkcfg));
	t = xclkcfg & 0x1;

	वापस t ? (parent_rate / xn) * 2 : parent_rate;
पूर्ण
PARENTS(clk_pxa3xx_run) = अणु "cpll" पूर्ण;
RATE_RO_OPS(clk_pxa3xx_run, "run");

अटल अचिन्हित दीर्घ clk_pxa3xx_cpll_get_rate(काष्ठा clk_hw *hw,
	अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ acsr = ACSR;
	अचिन्हित पूर्णांक xn = (acsr & ACCR_XN_MASK) >> 8;
	अचिन्हित पूर्णांक xl = acsr & ACCR_XL_MASK;
	अचिन्हित पूर्णांक t, xclkcfg;

	/* Read XCLKCFG रेजिस्टर turbo bit */
	__यंत्र__ __अस्थिर__("mrc\tp14, 0, %0, c6, c0, 0" : "=r"(xclkcfg));
	t = xclkcfg & 0x1;

	pr_info("RJK: parent_rate=%lu, xl=%u, xn=%u\n", parent_rate, xl, xn);
	वापस t ? parent_rate * xl * xn : parent_rate * xl;
पूर्ण
PARENTS(clk_pxa3xx_cpll) = अणु "osc_13mhz" पूर्ण;
RATE_RO_OPS(clk_pxa3xx_cpll, "cpll");

अटल व्योम __init pxa3xx_रेजिस्टर_core(व्योम)
अणु
	clk_रेजिस्टर_clk_pxa3xx_cpll();
	clk_रेजिस्टर_clk_pxa3xx_run();

	clkdev_pxa_रेजिस्टर(CLK_CORE, "core", शून्य,
			    clk_रेजिस्टर_clk_pxa3xx_core());
पूर्ण

अटल व्योम __init pxa3xx_रेजिस्टर_plls(व्योम)
अणु
	clk_रेजिस्टर_fixed_rate(शून्य, "osc_13mhz", शून्य,
				CLK_GET_RATE_NOCACHE,
				13 * MHz);
	clkdev_pxa_रेजिस्टर(CLK_OSC32k768, "osc_32_768khz", शून्य,
			    clk_रेजिस्टर_fixed_rate(शून्य, "osc_32_768khz", शून्य,
						    CLK_GET_RATE_NOCACHE,
						    32768));
	clk_रेजिस्टर_fixed_rate(शून्य, "ring_osc_120mhz", शून्य,
				CLK_GET_RATE_NOCACHE,
				120 * MHz);
	clk_रेजिस्टर_fixed_rate(शून्य, "clk_dummy", शून्य, 0, 0);
	clk_रेजिस्टर_fixed_factor(शून्य, "spll_624mhz", "osc_13mhz", 0, 48, 1);
	clk_रेजिस्टर_fixed_factor(शून्य, "ring_osc_60mhz", "ring_osc_120mhz",
				  0, 1, 2);
पूर्ण

#घोषणा DUMMY_CLK(_con_id, _dev_id, _parent) \
	अणु .con_id = _con_id, .dev_id = _dev_id, .parent = _parent पूर्ण
काष्ठा dummy_clk अणु
	स्थिर अक्षर *con_id;
	स्थिर अक्षर *dev_id;
	स्थिर अक्षर *parent;
पूर्ण;
अटल काष्ठा dummy_clk dummy_clks[] __initdata = अणु
	DUMMY_CLK(शून्य, "pxa93x-gpio", "osc_13mhz"),
	DUMMY_CLK(शून्य, "sa1100-rtc", "osc_32_768khz"),
	DUMMY_CLK("UARTCLK", "pxa2xx-ir", "STUART"),
	DUMMY_CLK(शून्य, "pxa3xx-pwri2c.1", "osc_13mhz"),
पूर्ण;

अटल व्योम __init pxa3xx_dummy_घड़ीs_init(व्योम)
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

अटल व्योम __init pxa3xx_base_घड़ीs_init(व्योम)
अणु
	काष्ठा clk *clk;

	pxa3xx_रेजिस्टर_plls();
	pxa3xx_रेजिस्टर_core();
	clk_रेजिस्टर_clk_pxa3xx_प्रणाली_bus();
	clk_रेजिस्टर_clk_pxa3xx_ac97();
	clk_रेजिस्टर_clk_pxa3xx_smemc();
	clk = clk_रेजिस्टर_gate(शून्य, "CLK_POUT",
				"osc_13mhz", 0, OSCC, 11, 0, शून्य);
	clk_रेजिस्टर_clkdev(clk, "CLK_POUT", शून्य);
	clkdev_pxa_रेजिस्टर(CLK_OSTIMER, "OSTIMER0", शून्य,
			    clk_रेजिस्टर_fixed_factor(शून्य, "os-timer0",
						      "osc_13mhz", 0, 1, 4));
पूर्ण

पूर्णांक __init pxa3xx_घड़ीs_init(व्योम)
अणु
	पूर्णांक ret;

	pxa3xx_base_घड़ीs_init();
	pxa3xx_dummy_घड़ीs_init();
	ret = clk_pxa_cken_init(pxa3xx_घड़ीs, ARRAY_SIZE(pxa3xx_घड़ीs));
	अगर (ret)
		वापस ret;
	अगर (cpu_is_pxa320())
		वापस clk_pxa_cken_init(pxa320_घड़ीs,
					 ARRAY_SIZE(pxa320_घड़ीs));
	अगर (cpu_is_pxa300() || cpu_is_pxa310())
		वापस clk_pxa_cken_init(pxa300_310_घड़ीs,
					 ARRAY_SIZE(pxa300_310_घड़ीs));
	वापस clk_pxa_cken_init(pxa93x_घड़ीs, ARRAY_SIZE(pxa93x_घड़ीs));
पूर्ण

अटल व्योम __init pxa3xx_dt_घड़ीs_init(काष्ठा device_node *np)
अणु
	pxa3xx_घड़ीs_init();
	clk_pxa_dt_common_init(np);
पूर्ण
CLK_OF_DECLARE(pxa_clks, "marvell,pxa300-clocks", pxa3xx_dt_घड़ीs_init);
