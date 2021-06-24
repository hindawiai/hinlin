<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Clock definitions क्रम u8500 platक्रमm.
 *
 * Copyright (C) 2012 ST-Ericsson SA
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/dbx500-prcmu.h>
#समावेश "clk.h"

#घोषणा PRCC_NUM_PERIPH_CLUSTERS 6
#घोषणा PRCC_PERIPHS_PER_CLUSTER 32

अटल काष्ठा clk *prcmu_clk[PRCMU_NUM_CLKS];
अटल काष्ठा clk *prcc_pclk[(PRCC_NUM_PERIPH_CLUSTERS + 1) * PRCC_PERIPHS_PER_CLUSTER];
अटल काष्ठा clk *prcc_kclk[(PRCC_NUM_PERIPH_CLUSTERS + 1) * PRCC_PERIPHS_PER_CLUSTER];

#घोषणा PRCC_SHOW(clk, base, bit) \
	clk[(base * PRCC_PERIPHS_PER_CLUSTER) + bit]
#घोषणा PRCC_PCLK_STORE(clk, base, bit)	\
	prcc_pclk[(base * PRCC_PERIPHS_PER_CLUSTER) + bit] = clk
#घोषणा PRCC_KCLK_STORE(clk, base, bit)        \
	prcc_kclk[(base * PRCC_PERIPHS_PER_CLUSTER) + bit] = clk

अटल काष्ठा clk *ux500_twocell_get(काष्ठा of_phandle_args *clkspec,
				     व्योम *data)
अणु
	काष्ठा clk **clk_data = data;
	अचिन्हित पूर्णांक base, bit;

	अगर (clkspec->args_count != 2)
		वापस  ERR_PTR(-EINVAL);

	base = clkspec->args[0];
	bit = clkspec->args[1];

	अगर (base != 1 && base != 2 && base != 3 && base != 5 && base != 6) अणु
		pr_err("%s: invalid PRCC base %d\n", __func__, base);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस PRCC_SHOW(clk_data, base, bit);
पूर्ण

/* CLKRST4 is missing making it hard to index things */
क्रमागत clkrst_index अणु
	CLKRST1_INDEX = 0,
	CLKRST2_INDEX,
	CLKRST3_INDEX,
	CLKRST5_INDEX,
	CLKRST6_INDEX,
	CLKRST_MAX,
पूर्ण;

अटल व्योम u8500_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा prcmu_fw_version *fw_version;
	काष्ठा device_node *child = शून्य;
	स्थिर अक्षर *sgaclk_parent = शून्य;
	काष्ठा clk *clk, *rtc_clk, *twd_clk;
	u32 bases[CLKRST_MAX];
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bases); i++) अणु
		काष्ठा resource r;

		अगर (of_address_to_resource(np, i, &r))
			/* Not much choice but to जारी */
			pr_err("failed to get CLKRST %d base address\n",
			       i + 1);
		bases[i] = r.start;
	पूर्ण

	/* Clock sources */
	clk = clk_reg_prcmu_gate("soc0_pll", शून्य, PRCMU_PLLSOC0,
				CLK_IGNORE_UNUSED);
	prcmu_clk[PRCMU_PLLSOC0] = clk;

	clk = clk_reg_prcmu_gate("soc1_pll", शून्य, PRCMU_PLLSOC1,
				CLK_IGNORE_UNUSED);
	prcmu_clk[PRCMU_PLLSOC1] = clk;

	clk = clk_reg_prcmu_gate("ddr_pll", शून्य, PRCMU_PLLDDR,
				CLK_IGNORE_UNUSED);
	prcmu_clk[PRCMU_PLLDDR] = clk;

	/* FIXME: Add sys, ulp and पूर्णांक घड़ीs here. */

	rtc_clk = clk_रेजिस्टर_fixed_rate(शून्य, "rtc32k", "NULL",
				CLK_IGNORE_UNUSED,
				32768);

	/* PRCMU घड़ीs */
	fw_version = prcmu_get_fw_version();
	अगर (fw_version != शून्य) अणु
		चयन (fw_version->project) अणु
		हाल PRCMU_FW_PROJECT_U8500_C2:
		हाल PRCMU_FW_PROJECT_U8500_MBL:
		हाल PRCMU_FW_PROJECT_U8520:
		हाल PRCMU_FW_PROJECT_U8420:
		हाल PRCMU_FW_PROJECT_U8420_SYSCLK:
			sgaclk_parent = "soc0_pll";
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (sgaclk_parent)
		clk = clk_reg_prcmu_gate("sgclk", sgaclk_parent,
					PRCMU_SGACLK, 0);
	अन्यथा
		clk = clk_reg_prcmu_gate("sgclk", शून्य, PRCMU_SGACLK, 0);
	prcmu_clk[PRCMU_SGACLK] = clk;

	clk = clk_reg_prcmu_gate("uartclk", शून्य, PRCMU_UARTCLK, 0);
	prcmu_clk[PRCMU_UARTCLK] = clk;

	clk = clk_reg_prcmu_gate("msp02clk", शून्य, PRCMU_MSP02CLK, 0);
	prcmu_clk[PRCMU_MSP02CLK] = clk;

	clk = clk_reg_prcmu_gate("msp1clk", शून्य, PRCMU_MSP1CLK, 0);
	prcmu_clk[PRCMU_MSP1CLK] = clk;

	clk = clk_reg_prcmu_gate("i2cclk", शून्य, PRCMU_I2CCLK, 0);
	prcmu_clk[PRCMU_I2CCLK] = clk;

	clk = clk_reg_prcmu_gate("slimclk", शून्य, PRCMU_SLIMCLK, 0);
	prcmu_clk[PRCMU_SLIMCLK] = clk;

	clk = clk_reg_prcmu_gate("per1clk", शून्य, PRCMU_PER1CLK, 0);
	prcmu_clk[PRCMU_PER1CLK] = clk;

	clk = clk_reg_prcmu_gate("per2clk", शून्य, PRCMU_PER2CLK, 0);
	prcmu_clk[PRCMU_PER2CLK] = clk;

	clk = clk_reg_prcmu_gate("per3clk", शून्य, PRCMU_PER3CLK, 0);
	prcmu_clk[PRCMU_PER3CLK] = clk;

	clk = clk_reg_prcmu_gate("per5clk", शून्य, PRCMU_PER5CLK, 0);
	prcmu_clk[PRCMU_PER5CLK] = clk;

	clk = clk_reg_prcmu_gate("per6clk", शून्य, PRCMU_PER6CLK, 0);
	prcmu_clk[PRCMU_PER6CLK] = clk;

	clk = clk_reg_prcmu_gate("per7clk", शून्य, PRCMU_PER7CLK, 0);
	prcmu_clk[PRCMU_PER7CLK] = clk;

	clk = clk_reg_prcmu_scalable("lcdclk", शून्य, PRCMU_LCDCLK, 0,
				CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_LCDCLK] = clk;

	clk = clk_reg_prcmu_opp_gate("bmlclk", शून्य, PRCMU_BMLCLK, 0);
	prcmu_clk[PRCMU_BMLCLK] = clk;

	clk = clk_reg_prcmu_scalable("hsitxclk", शून्य, PRCMU_HSITXCLK, 0,
				CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_HSITXCLK] = clk;

	clk = clk_reg_prcmu_scalable("hsirxclk", शून्य, PRCMU_HSIRXCLK, 0,
				CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_HSIRXCLK] = clk;

	clk = clk_reg_prcmu_scalable("hdmiclk", शून्य, PRCMU_HDMICLK, 0,
				CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_HDMICLK] = clk;

	clk = clk_reg_prcmu_gate("apeatclk", शून्य, PRCMU_APEATCLK, 0);
	prcmu_clk[PRCMU_APEATCLK] = clk;

	clk = clk_reg_prcmu_scalable("apetraceclk", शून्य, PRCMU_APETRACECLK, 0,
				CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_APETRACECLK] = clk;

	clk = clk_reg_prcmu_gate("mcdeclk", शून्य, PRCMU_MCDECLK, 0);
	prcmu_clk[PRCMU_MCDECLK] = clk;

	clk = clk_reg_prcmu_opp_gate("ipi2cclk", शून्य, PRCMU_IPI2CCLK, 0);
	prcmu_clk[PRCMU_IPI2CCLK] = clk;

	clk = clk_reg_prcmu_gate("dsialtclk", शून्य, PRCMU_DSIALTCLK, 0);
	prcmu_clk[PRCMU_DSIALTCLK] = clk;

	clk = clk_reg_prcmu_gate("dmaclk", शून्य, PRCMU_DMACLK, 0);
	prcmu_clk[PRCMU_DMACLK] = clk;

	clk = clk_reg_prcmu_gate("b2r2clk", शून्य, PRCMU_B2R2CLK, 0);
	prcmu_clk[PRCMU_B2R2CLK] = clk;

	clk = clk_reg_prcmu_scalable("tvclk", शून्य, PRCMU_TVCLK, 0,
				CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_TVCLK] = clk;

	clk = clk_reg_prcmu_gate("sspclk", शून्य, PRCMU_SSPCLK, 0);
	prcmu_clk[PRCMU_SSPCLK] = clk;

	clk = clk_reg_prcmu_gate("rngclk", शून्य, PRCMU_RNGCLK, 0);
	prcmu_clk[PRCMU_RNGCLK] = clk;

	clk = clk_reg_prcmu_gate("uiccclk", शून्य, PRCMU_UICCCLK, 0);
	prcmu_clk[PRCMU_UICCCLK] = clk;

	clk = clk_reg_prcmu_gate("timclk", शून्य, PRCMU_TIMCLK, 0);
	prcmu_clk[PRCMU_TIMCLK] = clk;

	clk = clk_reg_prcmu_gate("ab8500_sysclk", शून्य, PRCMU_SYSCLK, 0);
	prcmu_clk[PRCMU_SYSCLK] = clk;

	clk = clk_reg_prcmu_opp_volt_scalable("sdmmcclk", शून्य, PRCMU_SDMMCCLK,
					100000000, CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_SDMMCCLK] = clk;

	clk = clk_reg_prcmu_scalable("dsi_pll", "hdmiclk",
				PRCMU_PLLDSI, 0, CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_PLLDSI] = clk;

	clk = clk_reg_prcmu_scalable("dsi0clk", "dsi_pll",
				PRCMU_DSI0CLK, 0, CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_DSI0CLK] = clk;

	clk = clk_reg_prcmu_scalable("dsi1clk", "dsi_pll",
				PRCMU_DSI1CLK, 0, CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_DSI1CLK] = clk;

	clk = clk_reg_prcmu_scalable("dsi0escclk", "tvclk",
				PRCMU_DSI0ESCCLK, 0, CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_DSI0ESCCLK] = clk;

	clk = clk_reg_prcmu_scalable("dsi1escclk", "tvclk",
				PRCMU_DSI1ESCCLK, 0, CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_DSI1ESCCLK] = clk;

	clk = clk_reg_prcmu_scalable("dsi2escclk", "tvclk",
				PRCMU_DSI2ESCCLK, 0, CLK_SET_RATE_GATE);
	prcmu_clk[PRCMU_DSI2ESCCLK] = clk;

	clk = clk_reg_prcmu_scalable_rate("armss", शून्य,
				PRCMU_ARMSS, 0, CLK_IGNORE_UNUSED);
	prcmu_clk[PRCMU_ARMSS] = clk;

	twd_clk = clk_रेजिस्टर_fixed_factor(शून्य, "smp_twd", "armss",
				CLK_IGNORE_UNUSED, 1, 2);

	/*
	 * FIXME: Add special handled PRCMU घड़ीs here:
	 * 1. clkout0yuv, use PRCMU as parent + need regulator + pinctrl.
	 * 2. ab9540_clkout1yuv, see clkout0yuv
	 */

	/* PRCC P-घड़ीs */
	clk = clk_reg_prcc_pclk("p1_pclk0", "per1clk", bases[CLKRST1_INDEX],
				BIT(0), 0);
	PRCC_PCLK_STORE(clk, 1, 0);

	clk = clk_reg_prcc_pclk("p1_pclk1", "per1clk", bases[CLKRST1_INDEX],
				BIT(1), 0);
	PRCC_PCLK_STORE(clk, 1, 1);

	clk = clk_reg_prcc_pclk("p1_pclk2", "per1clk", bases[CLKRST1_INDEX],
				BIT(2), 0);
	PRCC_PCLK_STORE(clk, 1, 2);

	clk = clk_reg_prcc_pclk("p1_pclk3", "per1clk", bases[CLKRST1_INDEX],
				BIT(3), 0);
	PRCC_PCLK_STORE(clk, 1, 3);

	clk = clk_reg_prcc_pclk("p1_pclk4", "per1clk", bases[CLKRST1_INDEX],
				BIT(4), 0);
	PRCC_PCLK_STORE(clk, 1, 4);

	clk = clk_reg_prcc_pclk("p1_pclk5", "per1clk", bases[CLKRST1_INDEX],
				BIT(5), 0);
	PRCC_PCLK_STORE(clk, 1, 5);

	clk = clk_reg_prcc_pclk("p1_pclk6", "per1clk", bases[CLKRST1_INDEX],
				BIT(6), 0);
	PRCC_PCLK_STORE(clk, 1, 6);

	clk = clk_reg_prcc_pclk("p1_pclk7", "per1clk", bases[CLKRST1_INDEX],
				BIT(7), 0);
	PRCC_PCLK_STORE(clk, 1, 7);

	clk = clk_reg_prcc_pclk("p1_pclk8", "per1clk", bases[CLKRST1_INDEX],
				BIT(8), 0);
	PRCC_PCLK_STORE(clk, 1, 8);

	clk = clk_reg_prcc_pclk("p1_pclk9", "per1clk", bases[CLKRST1_INDEX],
				BIT(9), 0);
	PRCC_PCLK_STORE(clk, 1, 9);

	clk = clk_reg_prcc_pclk("p1_pclk10", "per1clk", bases[CLKRST1_INDEX],
				BIT(10), 0);
	PRCC_PCLK_STORE(clk, 1, 10);

	clk = clk_reg_prcc_pclk("p1_pclk11", "per1clk", bases[CLKRST1_INDEX],
				BIT(11), 0);
	PRCC_PCLK_STORE(clk, 1, 11);

	clk = clk_reg_prcc_pclk("p2_pclk0", "per2clk", bases[CLKRST2_INDEX],
				BIT(0), 0);
	PRCC_PCLK_STORE(clk, 2, 0);

	clk = clk_reg_prcc_pclk("p2_pclk1", "per2clk", bases[CLKRST2_INDEX],
				BIT(1), 0);
	PRCC_PCLK_STORE(clk, 2, 1);

	clk = clk_reg_prcc_pclk("p2_pclk2", "per2clk", bases[CLKRST2_INDEX],
				BIT(2), 0);
	PRCC_PCLK_STORE(clk, 2, 2);

	clk = clk_reg_prcc_pclk("p2_pclk3", "per2clk", bases[CLKRST2_INDEX],
				BIT(3), 0);
	PRCC_PCLK_STORE(clk, 2, 3);

	clk = clk_reg_prcc_pclk("p2_pclk4", "per2clk", bases[CLKRST2_INDEX],
				BIT(4), 0);
	PRCC_PCLK_STORE(clk, 2, 4);

	clk = clk_reg_prcc_pclk("p2_pclk5", "per2clk", bases[CLKRST2_INDEX],
				BIT(5), 0);
	PRCC_PCLK_STORE(clk, 2, 5);

	clk = clk_reg_prcc_pclk("p2_pclk6", "per2clk", bases[CLKRST2_INDEX],
				BIT(6), 0);
	PRCC_PCLK_STORE(clk, 2, 6);

	clk = clk_reg_prcc_pclk("p2_pclk7", "per2clk", bases[CLKRST2_INDEX],
				BIT(7), 0);
	PRCC_PCLK_STORE(clk, 2, 7);

	clk = clk_reg_prcc_pclk("p2_pclk8", "per2clk", bases[CLKRST2_INDEX],
				BIT(8), 0);
	PRCC_PCLK_STORE(clk, 2, 8);

	clk = clk_reg_prcc_pclk("p2_pclk9", "per2clk", bases[CLKRST2_INDEX],
				BIT(9), 0);
	PRCC_PCLK_STORE(clk, 2, 9);

	clk = clk_reg_prcc_pclk("p2_pclk10", "per2clk", bases[CLKRST2_INDEX],
				BIT(10), 0);
	PRCC_PCLK_STORE(clk, 2, 10);

	clk = clk_reg_prcc_pclk("p2_pclk11", "per2clk", bases[CLKRST2_INDEX],
				BIT(11), 0);
	PRCC_PCLK_STORE(clk, 2, 11);

	clk = clk_reg_prcc_pclk("p2_pclk12", "per2clk", bases[CLKRST2_INDEX],
				BIT(12), 0);
	PRCC_PCLK_STORE(clk, 2, 12);

	clk = clk_reg_prcc_pclk("p3_pclk0", "per3clk", bases[CLKRST3_INDEX],
				BIT(0), 0);
	PRCC_PCLK_STORE(clk, 3, 0);

	clk = clk_reg_prcc_pclk("p3_pclk1", "per3clk", bases[CLKRST3_INDEX],
				BIT(1), 0);
	PRCC_PCLK_STORE(clk, 3, 1);

	clk = clk_reg_prcc_pclk("p3_pclk2", "per3clk", bases[CLKRST3_INDEX],
				BIT(2), 0);
	PRCC_PCLK_STORE(clk, 3, 2);

	clk = clk_reg_prcc_pclk("p3_pclk3", "per3clk", bases[CLKRST3_INDEX],
				BIT(3), 0);
	PRCC_PCLK_STORE(clk, 3, 3);

	clk = clk_reg_prcc_pclk("p3_pclk4", "per3clk", bases[CLKRST3_INDEX],
				BIT(4), 0);
	PRCC_PCLK_STORE(clk, 3, 4);

	clk = clk_reg_prcc_pclk("p3_pclk5", "per3clk", bases[CLKRST3_INDEX],
				BIT(5), 0);
	PRCC_PCLK_STORE(clk, 3, 5);

	clk = clk_reg_prcc_pclk("p3_pclk6", "per3clk", bases[CLKRST3_INDEX],
				BIT(6), 0);
	PRCC_PCLK_STORE(clk, 3, 6);

	clk = clk_reg_prcc_pclk("p3_pclk7", "per3clk", bases[CLKRST3_INDEX],
				BIT(7), 0);
	PRCC_PCLK_STORE(clk, 3, 7);

	clk = clk_reg_prcc_pclk("p3_pclk8", "per3clk", bases[CLKRST3_INDEX],
				BIT(8), 0);
	PRCC_PCLK_STORE(clk, 3, 8);

	clk = clk_reg_prcc_pclk("p5_pclk0", "per5clk", bases[CLKRST5_INDEX],
				BIT(0), 0);
	PRCC_PCLK_STORE(clk, 5, 0);

	clk = clk_reg_prcc_pclk("p5_pclk1", "per5clk", bases[CLKRST5_INDEX],
				BIT(1), 0);
	PRCC_PCLK_STORE(clk, 5, 1);

	clk = clk_reg_prcc_pclk("p6_pclk0", "per6clk", bases[CLKRST6_INDEX],
				BIT(0), 0);
	PRCC_PCLK_STORE(clk, 6, 0);

	clk = clk_reg_prcc_pclk("p6_pclk1", "per6clk", bases[CLKRST6_INDEX],
				BIT(1), 0);
	PRCC_PCLK_STORE(clk, 6, 1);

	clk = clk_reg_prcc_pclk("p6_pclk2", "per6clk", bases[CLKRST6_INDEX],
				BIT(2), 0);
	PRCC_PCLK_STORE(clk, 6, 2);

	clk = clk_reg_prcc_pclk("p6_pclk3", "per6clk", bases[CLKRST6_INDEX],
				BIT(3), 0);
	PRCC_PCLK_STORE(clk, 6, 3);

	clk = clk_reg_prcc_pclk("p6_pclk4", "per6clk", bases[CLKRST6_INDEX],
				BIT(4), 0);
	PRCC_PCLK_STORE(clk, 6, 4);

	clk = clk_reg_prcc_pclk("p6_pclk5", "per6clk", bases[CLKRST6_INDEX],
				BIT(5), 0);
	PRCC_PCLK_STORE(clk, 6, 5);

	clk = clk_reg_prcc_pclk("p6_pclk6", "per6clk", bases[CLKRST6_INDEX],
				BIT(6), 0);
	PRCC_PCLK_STORE(clk, 6, 6);

	clk = clk_reg_prcc_pclk("p6_pclk7", "per6clk", bases[CLKRST6_INDEX],
				BIT(7), 0);
	PRCC_PCLK_STORE(clk, 6, 7);

	/* PRCC K-घड़ीs
	 *
	 * FIXME: Some drivers requires PERPIH[n| to be स्वतःmatically enabled
	 * by enabling just the K-घड़ी, even अगर it is not a valid parent to
	 * the K-घड़ी. Until drivers get fixed we might need some kind of
	 * "parent muxed join".
	 */

	/* Periph1 */
	clk = clk_reg_prcc_kclk("p1_uart0_kclk", "uartclk",
			bases[CLKRST1_INDEX], BIT(0), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 0);

	clk = clk_reg_prcc_kclk("p1_uart1_kclk", "uartclk",
			bases[CLKRST1_INDEX], BIT(1), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 1);

	clk = clk_reg_prcc_kclk("p1_i2c1_kclk", "i2cclk",
			bases[CLKRST1_INDEX], BIT(2), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 2);

	clk = clk_reg_prcc_kclk("p1_msp0_kclk", "msp02clk",
			bases[CLKRST1_INDEX], BIT(3), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 3);

	clk = clk_reg_prcc_kclk("p1_msp1_kclk", "msp1clk",
			bases[CLKRST1_INDEX], BIT(4), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 4);

	clk = clk_reg_prcc_kclk("p1_sdi0_kclk", "sdmmcclk",
			bases[CLKRST1_INDEX], BIT(5), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 5);

	clk = clk_reg_prcc_kclk("p1_i2c2_kclk", "i2cclk",
			bases[CLKRST1_INDEX], BIT(6), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 6);

	clk = clk_reg_prcc_kclk("p1_slimbus0_kclk", "slimclk",
			bases[CLKRST1_INDEX], BIT(8), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 8);

	clk = clk_reg_prcc_kclk("p1_i2c4_kclk", "i2cclk",
			bases[CLKRST1_INDEX], BIT(9), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 9);

	clk = clk_reg_prcc_kclk("p1_msp3_kclk", "msp1clk",
			bases[CLKRST1_INDEX], BIT(10), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 1, 10);

	/* Periph2 */
	clk = clk_reg_prcc_kclk("p2_i2c3_kclk", "i2cclk",
			bases[CLKRST2_INDEX], BIT(0), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 2, 0);

	clk = clk_reg_prcc_kclk("p2_sdi4_kclk", "sdmmcclk",
			bases[CLKRST2_INDEX], BIT(2), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 2, 2);

	clk = clk_reg_prcc_kclk("p2_msp2_kclk", "msp02clk",
			bases[CLKRST2_INDEX], BIT(3), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 2, 3);

	clk = clk_reg_prcc_kclk("p2_sdi1_kclk", "sdmmcclk",
			bases[CLKRST2_INDEX], BIT(4), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 2, 4);

	clk = clk_reg_prcc_kclk("p2_sdi3_kclk", "sdmmcclk",
			bases[CLKRST2_INDEX], BIT(5), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 2, 5);

	/* Note that rate is received from parent. */
	clk = clk_reg_prcc_kclk("p2_ssirx_kclk", "hsirxclk",
			bases[CLKRST2_INDEX], BIT(6),
			CLK_SET_RATE_GATE|CLK_SET_RATE_PARENT);
	PRCC_KCLK_STORE(clk, 2, 6);

	clk = clk_reg_prcc_kclk("p2_ssitx_kclk", "hsitxclk",
			bases[CLKRST2_INDEX], BIT(7),
			CLK_SET_RATE_GATE|CLK_SET_RATE_PARENT);
	PRCC_KCLK_STORE(clk, 2, 7);

	/* Periph3 */
	clk = clk_reg_prcc_kclk("p3_ssp0_kclk", "sspclk",
			bases[CLKRST3_INDEX], BIT(1), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 3, 1);

	clk = clk_reg_prcc_kclk("p3_ssp1_kclk", "sspclk",
			bases[CLKRST3_INDEX], BIT(2), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 3, 2);

	clk = clk_reg_prcc_kclk("p3_i2c0_kclk", "i2cclk",
			bases[CLKRST3_INDEX], BIT(3), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 3, 3);

	clk = clk_reg_prcc_kclk("p3_sdi2_kclk", "sdmmcclk",
			bases[CLKRST3_INDEX], BIT(4), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 3, 4);

	clk = clk_reg_prcc_kclk("p3_ske_kclk", "rtc32k",
			bases[CLKRST3_INDEX], BIT(5), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 3, 5);

	clk = clk_reg_prcc_kclk("p3_uart2_kclk", "uartclk",
			bases[CLKRST3_INDEX], BIT(6), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 3, 6);

	clk = clk_reg_prcc_kclk("p3_sdi5_kclk", "sdmmcclk",
			bases[CLKRST3_INDEX], BIT(7), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 3, 7);

	/* Periph6 */
	clk = clk_reg_prcc_kclk("p3_rng_kclk", "rngclk",
			bases[CLKRST6_INDEX], BIT(0), CLK_SET_RATE_GATE);
	PRCC_KCLK_STORE(clk, 6, 0);

	क्रम_each_child_of_node(np, child) अणु
		अटल काष्ठा clk_onecell_data clk_data;

		अगर (of_node_name_eq(child, "prcmu-clock")) अणु
			clk_data.clks = prcmu_clk;
			clk_data.clk_num = ARRAY_SIZE(prcmu_clk);
			of_clk_add_provider(child, of_clk_src_onecell_get, &clk_data);
		पूर्ण
		अगर (of_node_name_eq(child, "prcc-periph-clock"))
			of_clk_add_provider(child, ux500_twocell_get, prcc_pclk);

		अगर (of_node_name_eq(child, "prcc-kernel-clock"))
			of_clk_add_provider(child, ux500_twocell_get, prcc_kclk);

		अगर (of_node_name_eq(child, "rtc32k-clock"))
			of_clk_add_provider(child, of_clk_src_simple_get, rtc_clk);

		अगर (of_node_name_eq(child, "smp-twd-clock"))
			of_clk_add_provider(child, of_clk_src_simple_get, twd_clk);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(u8500_clks, "stericsson,u8500-clks", u8500_clk_init);
