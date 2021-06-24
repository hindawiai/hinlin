<शैली गुरु>
/*
 * OMAP2 Clock init
 *
 * Copyright (C) 2013 Texas Instruments, Inc
 *     Tero Kristo (t-kristo@ti.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

अटल काष्ठा ti_dt_clk omap2xxx_clks[] = अणु
	DT_CLK(शून्य, "func_32k_ck", "func_32k_ck"),
	DT_CLK(शून्य, "secure_32k_ck", "secure_32k_ck"),
	DT_CLK(शून्य, "virt_12m_ck", "virt_12m_ck"),
	DT_CLK(शून्य, "virt_13m_ck", "virt_13m_ck"),
	DT_CLK(शून्य, "virt_19200000_ck", "virt_19200000_ck"),
	DT_CLK(शून्य, "virt_26m_ck", "virt_26m_ck"),
	DT_CLK(शून्य, "aplls_clkin_ck", "aplls_clkin_ck"),
	DT_CLK(शून्य, "aplls_clkin_x2_ck", "aplls_clkin_x2_ck"),
	DT_CLK(शून्य, "osc_ck", "osc_ck"),
	DT_CLK(शून्य, "sys_ck", "sys_ck"),
	DT_CLK(शून्य, "alt_ck", "alt_ck"),
	DT_CLK(शून्य, "mcbsp_clks", "mcbsp_clks"),
	DT_CLK(शून्य, "dpll_ck", "dpll_ck"),
	DT_CLK(शून्य, "apll96_ck", "apll96_ck"),
	DT_CLK(शून्य, "apll54_ck", "apll54_ck"),
	DT_CLK(शून्य, "func_54m_ck", "func_54m_ck"),
	DT_CLK(शून्य, "core_ck", "core_ck"),
	DT_CLK(शून्य, "func_96m_ck", "func_96m_ck"),
	DT_CLK(शून्य, "func_48m_ck", "func_48m_ck"),
	DT_CLK(शून्य, "func_12m_ck", "func_12m_ck"),
	DT_CLK(शून्य, "sys_clkout_src", "sys_clkout_src"),
	DT_CLK(शून्य, "sys_clkout", "sys_clkout"),
	DT_CLK(शून्य, "emul_ck", "emul_ck"),
	DT_CLK(शून्य, "mpu_ck", "mpu_ck"),
	DT_CLK(शून्य, "dsp_fck", "dsp_fck"),
	DT_CLK(शून्य, "gfx_3d_fck", "gfx_3d_fck"),
	DT_CLK(शून्य, "gfx_2d_fck", "gfx_2d_fck"),
	DT_CLK(शून्य, "gfx_ick", "gfx_ick"),
	DT_CLK("omapdss_dss", "ick", "dss_ick"),
	DT_CLK(शून्य, "dss_ick", "dss_ick"),
	DT_CLK(शून्य, "dss1_fck", "dss1_fck"),
	DT_CLK(शून्य, "dss2_fck", "dss2_fck"),
	DT_CLK(शून्य, "dss_54m_fck", "dss_54m_fck"),
	DT_CLK(शून्य, "core_l3_ck", "core_l3_ck"),
	DT_CLK(शून्य, "ssi_fck", "ssi_ssr_sst_fck"),
	DT_CLK(शून्य, "usb_l4_ick", "usb_l4_ick"),
	DT_CLK(शून्य, "l4_ck", "l4_ck"),
	DT_CLK(शून्य, "ssi_l4_ick", "ssi_l4_ick"),
	DT_CLK(शून्य, "gpt1_ick", "gpt1_ick"),
	DT_CLK(शून्य, "gpt1_fck", "gpt1_fck"),
	DT_CLK(शून्य, "gpt2_ick", "gpt2_ick"),
	DT_CLK(शून्य, "gpt2_fck", "gpt2_fck"),
	DT_CLK(शून्य, "gpt3_ick", "gpt3_ick"),
	DT_CLK(शून्य, "gpt3_fck", "gpt3_fck"),
	DT_CLK(शून्य, "gpt4_ick", "gpt4_ick"),
	DT_CLK(शून्य, "gpt4_fck", "gpt4_fck"),
	DT_CLK(शून्य, "gpt5_ick", "gpt5_ick"),
	DT_CLK(शून्य, "gpt5_fck", "gpt5_fck"),
	DT_CLK(शून्य, "gpt6_ick", "gpt6_ick"),
	DT_CLK(शून्य, "gpt6_fck", "gpt6_fck"),
	DT_CLK(शून्य, "gpt7_ick", "gpt7_ick"),
	DT_CLK(शून्य, "gpt7_fck", "gpt7_fck"),
	DT_CLK(शून्य, "gpt8_ick", "gpt8_ick"),
	DT_CLK(शून्य, "gpt8_fck", "gpt8_fck"),
	DT_CLK(शून्य, "gpt9_ick", "gpt9_ick"),
	DT_CLK(शून्य, "gpt9_fck", "gpt9_fck"),
	DT_CLK(शून्य, "gpt10_ick", "gpt10_ick"),
	DT_CLK(शून्य, "gpt10_fck", "gpt10_fck"),
	DT_CLK(शून्य, "gpt11_ick", "gpt11_ick"),
	DT_CLK(शून्य, "gpt11_fck", "gpt11_fck"),
	DT_CLK(शून्य, "gpt12_ick", "gpt12_ick"),
	DT_CLK(शून्य, "gpt12_fck", "gpt12_fck"),
	DT_CLK("omap-mcbsp.1", "ick", "mcbsp1_ick"),
	DT_CLK(शून्य, "mcbsp1_ick", "mcbsp1_ick"),
	DT_CLK(शून्य, "mcbsp1_fck", "mcbsp1_fck"),
	DT_CLK("omap-mcbsp.2", "ick", "mcbsp2_ick"),
	DT_CLK(शून्य, "mcbsp2_ick", "mcbsp2_ick"),
	DT_CLK(शून्य, "mcbsp2_fck", "mcbsp2_fck"),
	DT_CLK("omap2_mcspi.1", "ick", "mcspi1_ick"),
	DT_CLK(शून्य, "mcspi1_ick", "mcspi1_ick"),
	DT_CLK(शून्य, "mcspi1_fck", "mcspi1_fck"),
	DT_CLK("omap2_mcspi.2", "ick", "mcspi2_ick"),
	DT_CLK(शून्य, "mcspi2_ick", "mcspi2_ick"),
	DT_CLK(शून्य, "mcspi2_fck", "mcspi2_fck"),
	DT_CLK(शून्य, "uart1_ick", "uart1_ick"),
	DT_CLK(शून्य, "uart1_fck", "uart1_fck"),
	DT_CLK(शून्य, "uart2_ick", "uart2_ick"),
	DT_CLK(शून्य, "uart2_fck", "uart2_fck"),
	DT_CLK(शून्य, "uart3_ick", "uart3_ick"),
	DT_CLK(शून्य, "uart3_fck", "uart3_fck"),
	DT_CLK(शून्य, "gpios_ick", "gpios_ick"),
	DT_CLK(शून्य, "gpios_fck", "gpios_fck"),
	DT_CLK("omap_wdt", "ick", "mpu_wdt_ick"),
	DT_CLK(शून्य, "mpu_wdt_ick", "mpu_wdt_ick"),
	DT_CLK(शून्य, "mpu_wdt_fck", "mpu_wdt_fck"),
	DT_CLK(शून्य, "sync_32k_ick", "sync_32k_ick"),
	DT_CLK(शून्य, "wdt1_ick", "wdt1_ick"),
	DT_CLK(शून्य, "omapctrl_ick", "omapctrl_ick"),
	DT_CLK("omap24xxcam", "fck", "cam_fck"),
	DT_CLK(शून्य, "cam_fck", "cam_fck"),
	DT_CLK("omap24xxcam", "ick", "cam_ick"),
	DT_CLK(शून्य, "cam_ick", "cam_ick"),
	DT_CLK(शून्य, "mailboxes_ick", "mailboxes_ick"),
	DT_CLK(शून्य, "wdt4_ick", "wdt4_ick"),
	DT_CLK(शून्य, "wdt4_fck", "wdt4_fck"),
	DT_CLK(शून्य, "mspro_ick", "mspro_ick"),
	DT_CLK(शून्य, "mspro_fck", "mspro_fck"),
	DT_CLK(शून्य, "fac_ick", "fac_ick"),
	DT_CLK(शून्य, "fac_fck", "fac_fck"),
	DT_CLK("omap_hdq.0", "ick", "hdq_ick"),
	DT_CLK(शून्य, "hdq_ick", "hdq_ick"),
	DT_CLK("omap_hdq.0", "fck", "hdq_fck"),
	DT_CLK(शून्य, "hdq_fck", "hdq_fck"),
	DT_CLK("omap_i2c.1", "ick", "i2c1_ick"),
	DT_CLK(शून्य, "i2c1_ick", "i2c1_ick"),
	DT_CLK("omap_i2c.2", "ick", "i2c2_ick"),
	DT_CLK(शून्य, "i2c2_ick", "i2c2_ick"),
	DT_CLK(शून्य, "gpmc_fck", "gpmc_fck"),
	DT_CLK(शून्य, "sdma_fck", "sdma_fck"),
	DT_CLK(शून्य, "sdma_ick", "sdma_ick"),
	DT_CLK(शून्य, "sdrc_ick", "sdrc_ick"),
	DT_CLK(शून्य, "des_ick", "des_ick"),
	DT_CLK("omap-sham", "ick", "sha_ick"),
	DT_CLK(शून्य, "sha_ick", "sha_ick"),
	DT_CLK("omap_rng", "ick", "rng_ick"),
	DT_CLK(शून्य, "rng_ick", "rng_ick"),
	DT_CLK("omap-aes", "ick", "aes_ick"),
	DT_CLK(शून्य, "aes_ick", "aes_ick"),
	DT_CLK(शून्य, "pka_ick", "pka_ick"),
	DT_CLK(शून्य, "usb_fck", "usb_fck"),
	DT_CLK(शून्य, "timer_32k_ck", "func_32k_ck"),
	DT_CLK(शून्य, "timer_sys_ck", "sys_ck"),
	DT_CLK(शून्य, "timer_ext_ck", "alt_ck"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk omap2420_clks[] = अणु
	DT_CLK(शून्य, "sys_clkout2_src", "sys_clkout2_src"),
	DT_CLK(शून्य, "sys_clkout2", "sys_clkout2"),
	DT_CLK(शून्य, "dsp_ick", "dsp_ick"),
	DT_CLK(शून्य, "iva1_ifck", "iva1_ifck"),
	DT_CLK(शून्य, "iva1_mpu_int_ifck", "iva1_mpu_int_ifck"),
	DT_CLK(शून्य, "wdt3_ick", "wdt3_ick"),
	DT_CLK(शून्य, "wdt3_fck", "wdt3_fck"),
	DT_CLK("mmci-omap.0", "ick", "mmc_ick"),
	DT_CLK(शून्य, "mmc_ick", "mmc_ick"),
	DT_CLK("mmci-omap.0", "fck", "mmc_fck"),
	DT_CLK(शून्य, "mmc_fck", "mmc_fck"),
	DT_CLK(शून्य, "eac_ick", "eac_ick"),
	DT_CLK(शून्य, "eac_fck", "eac_fck"),
	DT_CLK(शून्य, "i2c1_fck", "i2c1_fck"),
	DT_CLK(शून्य, "i2c2_fck", "i2c2_fck"),
	DT_CLK(शून्य, "vlynq_ick", "vlynq_ick"),
	DT_CLK(शून्य, "vlynq_fck", "vlynq_fck"),
	DT_CLK("musb-hdrc", "fck", "osc_ck"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk omap2430_clks[] = अणु
	DT_CLK("twl", "fck", "osc_ck"),
	DT_CLK(शून्य, "iva2_1_ick", "iva2_1_ick"),
	DT_CLK(शून्य, "mdm_ick", "mdm_ick"),
	DT_CLK(शून्य, "mdm_osc_ck", "mdm_osc_ck"),
	DT_CLK("omap-mcbsp.3", "ick", "mcbsp3_ick"),
	DT_CLK(शून्य, "mcbsp3_ick", "mcbsp3_ick"),
	DT_CLK(शून्य, "mcbsp3_fck", "mcbsp3_fck"),
	DT_CLK("omap-mcbsp.4", "ick", "mcbsp4_ick"),
	DT_CLK(शून्य, "mcbsp4_ick", "mcbsp4_ick"),
	DT_CLK(शून्य, "mcbsp4_fck", "mcbsp4_fck"),
	DT_CLK("omap-mcbsp.5", "ick", "mcbsp5_ick"),
	DT_CLK(शून्य, "mcbsp5_ick", "mcbsp5_ick"),
	DT_CLK(शून्य, "mcbsp5_fck", "mcbsp5_fck"),
	DT_CLK("omap2_mcspi.3", "ick", "mcspi3_ick"),
	DT_CLK(शून्य, "mcspi3_ick", "mcspi3_ick"),
	DT_CLK(शून्य, "mcspi3_fck", "mcspi3_fck"),
	DT_CLK(शून्य, "icr_ick", "icr_ick"),
	DT_CLK(शून्य, "i2chs1_fck", "i2chs1_fck"),
	DT_CLK(शून्य, "i2chs2_fck", "i2chs2_fck"),
	DT_CLK("musb-omap2430", "ick", "usbhs_ick"),
	DT_CLK(शून्य, "usbhs_ick", "usbhs_ick"),
	DT_CLK("omap_hsmmc.0", "ick", "mmchs1_ick"),
	DT_CLK(शून्य, "mmchs1_ick", "mmchs1_ick"),
	DT_CLK(शून्य, "mmchs1_fck", "mmchs1_fck"),
	DT_CLK("omap_hsmmc.1", "ick", "mmchs2_ick"),
	DT_CLK(शून्य, "mmchs2_ick", "mmchs2_ick"),
	DT_CLK(शून्य, "mmchs2_fck", "mmchs2_fck"),
	DT_CLK(शून्य, "gpio5_ick", "gpio5_ick"),
	DT_CLK(शून्य, "gpio5_fck", "gpio5_fck"),
	DT_CLK(शून्य, "mdm_intc_ick", "mdm_intc_ick"),
	DT_CLK("omap_hsmmc.0", "mmchsdb_fck", "mmchsdb1_fck"),
	DT_CLK(शून्य, "mmchsdb1_fck", "mmchsdb1_fck"),
	DT_CLK("omap_hsmmc.1", "mmchsdb_fck", "mmchsdb2_fck"),
	DT_CLK(शून्य, "mmchsdb2_fck", "mmchsdb2_fck"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *enable_init_clks[] = अणु
	"apll96_ck",
	"apll54_ck",
	"sync_32k_ick",
	"omapctrl_ick",
	"gpmc_fck",
	"sdrc_ick",
पूर्ण;

क्रमागत अणु
	OMAP2_SOC_OMAP2420,
	OMAP2_SOC_OMAP2430,
पूर्ण;

अटल पूर्णांक __init omap2xxx_dt_clk_init(पूर्णांक soc_type)
अणु
	ti_dt_घड़ीs_रेजिस्टर(omap2xxx_clks);

	अगर (soc_type == OMAP2_SOC_OMAP2420)
		ti_dt_घड़ीs_रेजिस्टर(omap2420_clks);
	अन्यथा
		ti_dt_घड़ीs_रेजिस्टर(omap2430_clks);

	omap2xxx_clkt_vps_init();

	omap2_clk_disable_स्वतःidle_all();

	omap2_clk_enable_init_घड़ीs(enable_init_clks,
				     ARRAY_SIZE(enable_init_clks));

	pr_info("Clocking rate (Crystal/DPLL/MPU): %ld.%01ld/%ld/%ld MHz\n",
		(clk_get_rate(clk_get_sys(शून्य, "sys_ck")) / 1000000),
		(clk_get_rate(clk_get_sys(शून्य, "sys_ck")) / 100000) % 10,
		(clk_get_rate(clk_get_sys(शून्य, "dpll_ck")) / 1000000),
		(clk_get_rate(clk_get_sys(शून्य, "mpu_ck")) / 1000000));

	वापस 0;
पूर्ण

पूर्णांक __init omap2420_dt_clk_init(व्योम)
अणु
	वापस omap2xxx_dt_clk_init(OMAP2_SOC_OMAP2420);
पूर्ण

पूर्णांक __init omap2430_dt_clk_init(व्योम)
अणु
	वापस omap2xxx_dt_clk_init(OMAP2_SOC_OMAP2430);
पूर्ण
