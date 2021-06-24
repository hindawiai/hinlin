<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk/mxs.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश "clk.h"

अटल व्योम __iomem *clkctrl;
#घोषणा CLKCTRL clkctrl

#घोषणा PLL0CTRL0		(CLKCTRL + 0x0000)
#घोषणा PLL1CTRL0		(CLKCTRL + 0x0020)
#घोषणा PLL2CTRL0		(CLKCTRL + 0x0040)
#घोषणा CPU			(CLKCTRL + 0x0050)
#घोषणा HBUS			(CLKCTRL + 0x0060)
#घोषणा XBUS			(CLKCTRL + 0x0070)
#घोषणा XTAL			(CLKCTRL + 0x0080)
#घोषणा SSP0			(CLKCTRL + 0x0090)
#घोषणा SSP1			(CLKCTRL + 0x00a0)
#घोषणा SSP2			(CLKCTRL + 0x00b0)
#घोषणा SSP3			(CLKCTRL + 0x00c0)
#घोषणा GPMI			(CLKCTRL + 0x00d0)
#घोषणा SPDIF			(CLKCTRL + 0x00e0)
#घोषणा EMI			(CLKCTRL + 0x00f0)
#घोषणा SAIF0			(CLKCTRL + 0x0100)
#घोषणा SAIF1			(CLKCTRL + 0x0110)
#घोषणा LCDIF			(CLKCTRL + 0x0120)
#घोषणा ETM			(CLKCTRL + 0x0130)
#घोषणा ENET			(CLKCTRL + 0x0140)
#घोषणा FLEXCAN			(CLKCTRL + 0x0160)
#घोषणा FRAC0			(CLKCTRL + 0x01b0)
#घोषणा FRAC1			(CLKCTRL + 0x01c0)
#घोषणा CLKSEQ			(CLKCTRL + 0x01d0)

#घोषणा BP_CPU_INTERRUPT_WAIT	12
#घोषणा BP_SAIF_DIV_FRAC_EN	16
#घोषणा BP_ENET_DIV_TIME	21
#घोषणा BP_ENET_SLEEP		31
#घोषणा BP_CLKSEQ_BYPASS_SAIF0	0
#घोषणा BP_CLKSEQ_BYPASS_SSP0	3
#घोषणा BP_FRAC0_IO1FRAC	16
#घोषणा BP_FRAC0_IO0FRAC	24

अटल व्योम __iomem *digctrl;
#घोषणा DIGCTRL digctrl
#घोषणा BP_SAIF_CLKMUX		10

/*
 * HW_SAIF_CLKMUX_SEL:
 *  सूचीECT(0x0): SAIF0 घड़ी pins selected क्रम SAIF0 input घड़ीs, and SAIF1
 *		घड़ी pins selected क्रम SAIF1 input घड़ीs.
 *  CROSSINPUT(0x1): SAIF1 घड़ी inमाला_दो selected क्रम SAIF0 input घड़ीs, and
 *		SAIF0 घड़ी inमाला_दो selected क्रम SAIF1 input घड़ीs.
 *  EXTMSTR0(0x2): SAIF0 घड़ी pin selected क्रम both SAIF0 and SAIF1 input
 *		घड़ीs.
 *  EXTMSTR1(0x3): SAIF1 घड़ी pin selected क्रम both SAIF0 and SAIF1 input
 *		घड़ीs.
 */
पूर्णांक mxs_saअगर_clkmux_select(अचिन्हित पूर्णांक clkmux)
अणु
	अगर (clkmux > 0x3)
		वापस -EINVAL;

	ग_लिखोl_relaxed(0x3 << BP_SAIF_CLKMUX, DIGCTRL + CLR);
	ग_लिखोl_relaxed(clkmux << BP_SAIF_CLKMUX, DIGCTRL + SET);

	वापस 0;
पूर्ण

अटल व्योम __init clk_misc_init(व्योम)
अणु
	u32 val;

	/* Gate off cpu घड़ी in WFI क्रम घातer saving */
	ग_लिखोl_relaxed(1 << BP_CPU_INTERRUPT_WAIT, CPU + SET);

	/* 0 is a bad शेष value क्रम a भागider */
	ग_लिखोl_relaxed(1 << BP_ENET_DIV_TIME, ENET + SET);

	/* Clear BYPASS क्रम SAIF */
	ग_लिखोl_relaxed(0x3 << BP_CLKSEQ_BYPASS_SAIF0, CLKSEQ + CLR);

	/* SAIF has to use frac भाग क्रम functional operation */
	val = पढ़ोl_relaxed(SAIF0);
	val |= 1 << BP_SAIF_DIV_FRAC_EN;
	ग_लिखोl_relaxed(val, SAIF0);

	val = पढ़ोl_relaxed(SAIF1);
	val |= 1 << BP_SAIF_DIV_FRAC_EN;
	ग_लिखोl_relaxed(val, SAIF1);

	/* Extra fec घड़ी setting */
	val = पढ़ोl_relaxed(ENET);
	val &= ~(1 << BP_ENET_SLEEP);
	ग_लिखोl_relaxed(val, ENET);

	/*
	 * Source ssp घड़ी from ref_io than ref_xtal,
	 * as ref_xtal only provides 24 MHz as maximum.
	 */
	ग_लिखोl_relaxed(0xf << BP_CLKSEQ_BYPASS_SSP0, CLKSEQ + CLR);

	/*
	 * 480 MHz seems too high to be ssp घड़ी source directly,
	 * so set frac0 to get a 288 MHz ref_io0 and ref_io1.
	 */
	val = पढ़ोl_relaxed(FRAC0);
	val &= ~((0x3f << BP_FRAC0_IO0FRAC) | (0x3f << BP_FRAC0_IO1FRAC));
	val |= (30 << BP_FRAC0_IO0FRAC) | (30 << BP_FRAC0_IO1FRAC);
	ग_लिखोl_relaxed(val, FRAC0);
पूर्ण

अटल स्थिर अक्षर *स्थिर sel_cpu[]  __initस्थिर = अणु "ref_cpu", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर sel_io0[]  __initस्थिर = अणु "ref_io0", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर sel_io1[]  __initस्थिर = अणु "ref_io1", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर sel_pix[]  __initस्थिर = अणु "ref_pix", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर sel_gpmi[] __initस्थिर = अणु "ref_gpmi", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर sel_pll0[] __initस्थिर = अणु "pll0", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर cpu_sels[] __initस्थिर = अणु "cpu_pll", "cpu_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर emi_sels[] __initस्थिर = अणु "emi_pll", "emi_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर ptp_sels[] __initस्थिर = अणु "ref_xtal", "pll0", पूर्ण;

क्रमागत imx28_clk अणु
	ref_xtal, pll0, pll1, pll2, ref_cpu, ref_emi, ref_io0, ref_io1,
	ref_pix, ref_hsadc, ref_gpmi, saअगर0_sel, saअगर1_sel, gpmi_sel,
	ssp0_sel, ssp1_sel, ssp2_sel, ssp3_sel, emi_sel, eपंचांग_sel,
	lcdअगर_sel, cpu, ptp_sel, cpu_pll, cpu_xtal, hbus, xbus,
	ssp0_भाग, ssp1_भाग, ssp2_भाग, ssp3_भाग, gpmi_भाग, emi_pll,
	emi_xtal, lcdअगर_भाग, eपंचांग_भाग, ptp, saअगर0_भाग, saअगर1_भाग,
	clk32k_भाग, rtc, lradc, spdअगर_भाग, clk32k, pwm, uart, ssp0,
	ssp1, ssp2, ssp3, gpmi, spdअगर, emi, saअगर0, saअगर1, lcdअगर, eपंचांग,
	fec, can0, can1, usb0, usb1, usb0_phy, usb1_phy, enet_out,
	clk_max
पूर्ण;

अटल काष्ठा clk *clks[clk_max];
अटल काष्ठा clk_onecell_data clk_data;

अटल क्रमागत imx28_clk clks_init_on[] __initdata = अणु
	cpu, hbus, xbus, emi, uart,
पूर्ण;

अटल व्योम __init mx28_घड़ीs_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *dcnp;
	u32 i;

	dcnp = of_find_compatible_node(शून्य, शून्य, "fsl,imx28-digctl");
	digctrl = of_iomap(dcnp, 0);
	WARN_ON(!digctrl);
	of_node_put(dcnp);

	clkctrl = of_iomap(np, 0);
	WARN_ON(!clkctrl);

	clk_misc_init();

	clks[ref_xtal] = mxs_clk_fixed("ref_xtal", 24000000);
	clks[pll0] = mxs_clk_pll("pll0", "ref_xtal", PLL0CTRL0, 17, 480000000);
	clks[pll1] = mxs_clk_pll("pll1", "ref_xtal", PLL1CTRL0, 17, 480000000);
	clks[pll2] = mxs_clk_pll("pll2", "ref_xtal", PLL2CTRL0, 23, 50000000);
	clks[ref_cpu] = mxs_clk_ref("ref_cpu", "pll0", FRAC0, 0);
	clks[ref_emi] = mxs_clk_ref("ref_emi", "pll0", FRAC0, 1);
	clks[ref_io1] = mxs_clk_ref("ref_io1", "pll0", FRAC0, 2);
	clks[ref_io0] = mxs_clk_ref("ref_io0", "pll0", FRAC0, 3);
	clks[ref_pix] = mxs_clk_ref("ref_pix", "pll0", FRAC1, 0);
	clks[ref_hsadc] = mxs_clk_ref("ref_hsadc", "pll0", FRAC1, 1);
	clks[ref_gpmi] = mxs_clk_ref("ref_gpmi", "pll0", FRAC1, 2);
	clks[saअगर0_sel] = mxs_clk_mux("saif0_sel", CLKSEQ, 0, 1, sel_pll0, ARRAY_SIZE(sel_pll0));
	clks[saअगर1_sel] = mxs_clk_mux("saif1_sel", CLKSEQ, 1, 1, sel_pll0, ARRAY_SIZE(sel_pll0));
	clks[gpmi_sel] = mxs_clk_mux("gpmi_sel", CLKSEQ, 2, 1, sel_gpmi, ARRAY_SIZE(sel_gpmi));
	clks[ssp0_sel] = mxs_clk_mux("ssp0_sel", CLKSEQ, 3, 1, sel_io0, ARRAY_SIZE(sel_io0));
	clks[ssp1_sel] = mxs_clk_mux("ssp1_sel", CLKSEQ, 4, 1, sel_io0, ARRAY_SIZE(sel_io0));
	clks[ssp2_sel] = mxs_clk_mux("ssp2_sel", CLKSEQ, 5, 1, sel_io1, ARRAY_SIZE(sel_io1));
	clks[ssp3_sel] = mxs_clk_mux("ssp3_sel", CLKSEQ, 6, 1, sel_io1, ARRAY_SIZE(sel_io1));
	clks[emi_sel] = mxs_clk_mux("emi_sel", CLKSEQ, 7, 1, emi_sels, ARRAY_SIZE(emi_sels));
	clks[eपंचांग_sel] = mxs_clk_mux("etm_sel", CLKSEQ, 8, 1, sel_cpu, ARRAY_SIZE(sel_cpu));
	clks[lcdअगर_sel] = mxs_clk_mux("lcdif_sel", CLKSEQ, 14, 1, sel_pix, ARRAY_SIZE(sel_pix));
	clks[cpu] = mxs_clk_mux("cpu", CLKSEQ, 18, 1, cpu_sels, ARRAY_SIZE(cpu_sels));
	clks[ptp_sel] = mxs_clk_mux("ptp_sel", ENET, 19, 1, ptp_sels, ARRAY_SIZE(ptp_sels));
	clks[cpu_pll] = mxs_clk_भाग("cpu_pll", "ref_cpu", CPU, 0, 6, 28);
	clks[cpu_xtal] = mxs_clk_भाग("cpu_xtal", "ref_xtal", CPU, 16, 10, 29);
	clks[hbus] = mxs_clk_भाग("hbus", "cpu", HBUS, 0, 5, 31);
	clks[xbus] = mxs_clk_भाग("xbus", "ref_xtal", XBUS, 0, 10, 31);
	clks[ssp0_भाग] = mxs_clk_भाग("ssp0_div", "ssp0_sel", SSP0, 0, 9, 29);
	clks[ssp1_भाग] = mxs_clk_भाग("ssp1_div", "ssp1_sel", SSP1, 0, 9, 29);
	clks[ssp2_भाग] = mxs_clk_भाग("ssp2_div", "ssp2_sel", SSP2, 0, 9, 29);
	clks[ssp3_भाग] = mxs_clk_भाग("ssp3_div", "ssp3_sel", SSP3, 0, 9, 29);
	clks[gpmi_भाग] = mxs_clk_भाग("gpmi_div", "gpmi_sel", GPMI, 0, 10, 29);
	clks[emi_pll] = mxs_clk_भाग("emi_pll", "ref_emi", EMI, 0, 6, 28);
	clks[emi_xtal] = mxs_clk_भाग("emi_xtal", "ref_xtal", EMI, 8, 4, 29);
	clks[lcdअगर_भाग] = mxs_clk_भाग("lcdif_div", "lcdif_sel", LCDIF, 0, 13, 29);
	clks[eपंचांग_भाग] = mxs_clk_भाग("etm_div", "etm_sel", ETM, 0, 7, 29);
	clks[ptp] = mxs_clk_भाग("ptp", "ptp_sel", ENET, 21, 6, 27);
	clks[saअगर0_भाग] = mxs_clk_frac("saif0_div", "saif0_sel", SAIF0, 0, 16, 29);
	clks[saअगर1_भाग] = mxs_clk_frac("saif1_div", "saif1_sel", SAIF1, 0, 16, 29);
	clks[clk32k_भाग] = mxs_clk_fixed_factor("clk32k_div", "ref_xtal", 1, 750);
	clks[rtc] = mxs_clk_fixed_factor("rtc", "ref_xtal", 1, 768);
	clks[lradc] = mxs_clk_fixed_factor("lradc", "clk32k", 1, 16);
	clks[spdअगर_भाग] = mxs_clk_fixed_factor("spdif_div", "pll0", 1, 4);
	clks[clk32k] = mxs_clk_gate("clk32k", "clk32k_div", XTAL, 26);
	clks[pwm] = mxs_clk_gate("pwm", "ref_xtal", XTAL, 29);
	clks[uart] = mxs_clk_gate("uart", "ref_xtal", XTAL, 31);
	clks[ssp0] = mxs_clk_gate("ssp0", "ssp0_div", SSP0, 31);
	clks[ssp1] = mxs_clk_gate("ssp1", "ssp1_div", SSP1, 31);
	clks[ssp2] = mxs_clk_gate("ssp2", "ssp2_div", SSP2, 31);
	clks[ssp3] = mxs_clk_gate("ssp3", "ssp3_div", SSP3, 31);
	clks[gpmi] = mxs_clk_gate("gpmi", "gpmi_div", GPMI, 31);
	clks[spdअगर] = mxs_clk_gate("spdif", "spdif_div", SPDIF, 31);
	clks[emi] = mxs_clk_gate("emi", "emi_sel", EMI, 31);
	clks[saअगर0] = mxs_clk_gate("saif0", "saif0_div", SAIF0, 31);
	clks[saअगर1] = mxs_clk_gate("saif1", "saif1_div", SAIF1, 31);
	clks[lcdअगर] = mxs_clk_gate("lcdif", "lcdif_div", LCDIF, 31);
	clks[eपंचांग] = mxs_clk_gate("etm", "etm_div", ETM, 31);
	clks[fec] = mxs_clk_gate("fec", "hbus", ENET, 30);
	clks[can0] = mxs_clk_gate("can0", "ref_xtal", FLEXCAN, 30);
	clks[can1] = mxs_clk_gate("can1", "ref_xtal", FLEXCAN, 28);
	clks[usb0] = mxs_clk_gate("usb0", "usb0_phy", DIGCTRL, 2);
	clks[usb1] = mxs_clk_gate("usb1", "usb1_phy", DIGCTRL, 16);
	clks[usb0_phy] = clk_रेजिस्टर_gate(शून्य, "usb0_phy", "pll0", 0, PLL0CTRL0, 18, 0, &mxs_lock);
	clks[usb1_phy] = clk_रेजिस्टर_gate(शून्य, "usb1_phy", "pll1", 0, PLL1CTRL0, 18, 0, &mxs_lock);
	clks[enet_out] = clk_रेजिस्टर_gate(शून्य, "enet_out", "pll2", 0, ENET, 18, 0, &mxs_lock);

	क्रम (i = 0; i < ARRAY_SIZE(clks); i++)
		अगर (IS_ERR(clks[i])) अणु
			pr_err("i.MX28 clk %d: register failed with %ld\n",
				i, PTR_ERR(clks[i]));
			वापस;
		पूर्ण

	clk_data.clks = clks;
	clk_data.clk_num = ARRAY_SIZE(clks);
	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data);

	clk_रेजिस्टर_clkdev(clks[enet_out], शून्य, "enet_out");

	क्रम (i = 0; i < ARRAY_SIZE(clks_init_on); i++)
		clk_prepare_enable(clks[clks_init_on[i]]);
पूर्ण
CLK_OF_DECLARE(imx28_clkctrl, "fsl,imx28-clkctrl", mx28_घड़ीs_init);
