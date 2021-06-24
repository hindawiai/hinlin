<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk/mxs.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश "clk.h"

अटल व्योम __iomem *clkctrl;
अटल व्योम __iomem *digctrl;

#घोषणा CLKCTRL clkctrl
#घोषणा DIGCTRL digctrl

#घोषणा PLLCTRL0		(CLKCTRL + 0x0000)
#घोषणा CPU			(CLKCTRL + 0x0020)
#घोषणा HBUS			(CLKCTRL + 0x0030)
#घोषणा XBUS			(CLKCTRL + 0x0040)
#घोषणा XTAL			(CLKCTRL + 0x0050)
#घोषणा PIX			(CLKCTRL + 0x0060)
#घोषणा SSP			(CLKCTRL + 0x0070)
#घोषणा GPMI			(CLKCTRL + 0x0080)
#घोषणा SPDIF			(CLKCTRL + 0x0090)
#घोषणा EMI			(CLKCTRL + 0x00a0)
#घोषणा SAIF			(CLKCTRL + 0x00c0)
#घोषणा TV			(CLKCTRL + 0x00d0)
#घोषणा ETM			(CLKCTRL + 0x00e0)
#घोषणा FRAC			(CLKCTRL + 0x00f0)
#घोषणा CLKSEQ			(CLKCTRL + 0x0110)

#घोषणा BP_CPU_INTERRUPT_WAIT	12
#घोषणा BP_CLKSEQ_BYPASS_SAIF	0
#घोषणा BP_CLKSEQ_BYPASS_SSP	5
#घोषणा BP_SAIF_DIV_FRAC_EN	16
#घोषणा BP_FRAC_IOFRAC		24

अटल व्योम __init clk_misc_init(व्योम)
अणु
	u32 val;

	/* Gate off cpu घड़ी in WFI क्रम घातer saving */
	ग_लिखोl_relaxed(1 << BP_CPU_INTERRUPT_WAIT, CPU + SET);

	/* Clear BYPASS क्रम SAIF */
	ग_लिखोl_relaxed(1 << BP_CLKSEQ_BYPASS_SAIF, CLKSEQ + CLR);

	/* SAIF has to use frac भाग क्रम functional operation */
	val = पढ़ोl_relaxed(SAIF);
	val |= 1 << BP_SAIF_DIV_FRAC_EN;
	ग_लिखोl_relaxed(val, SAIF);

	/*
	 * Source ssp घड़ी from ref_io than ref_xtal,
	 * as ref_xtal only provides 24 MHz as maximum.
	 */
	ग_लिखोl_relaxed(1 << BP_CLKSEQ_BYPASS_SSP, CLKSEQ + CLR);

	/*
	 * 480 MHz seems too high to be ssp घड़ी source directly,
	 * so set frac to get a 288 MHz ref_io.
	 */
	ग_लिखोl_relaxed(0x3f << BP_FRAC_IOFRAC, FRAC + CLR);
	ग_लिखोl_relaxed(30 << BP_FRAC_IOFRAC, FRAC + SET);
पूर्ण

अटल स्थिर अक्षर *स्थिर sel_pll[]  __initस्थिर = अणु "pll", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर sel_cpu[]  __initस्थिर = अणु "ref_cpu", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर sel_pix[]  __initस्थिर = अणु "ref_pix", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर sel_io[]   __initस्थिर = अणु "ref_io", "ref_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर cpu_sels[] __initस्थिर = अणु "cpu_pll", "cpu_xtal", पूर्ण;
अटल स्थिर अक्षर *स्थिर emi_sels[] __initस्थिर = अणु "emi_pll", "emi_xtal", पूर्ण;

क्रमागत imx23_clk अणु
	ref_xtal, pll, ref_cpu, ref_emi, ref_pix, ref_io, saअगर_sel,
	lcdअगर_sel, gpmi_sel, ssp_sel, emi_sel, cpu, eपंचांग_sel, cpu_pll,
	cpu_xtal, hbus, xbus, lcdअगर_भाग, ssp_भाग, gpmi_भाग, emi_pll,
	emi_xtal, eपंचांग_भाग, saअगर_भाग, clk32k_भाग, rtc, adc, spdअगर_भाग,
	clk32k, dri, pwm, filt, uart, ssp, gpmi, spdअगर, emi, saअगर,
	lcdअगर, eपंचांग, usb, usb_phy,
	clk_max
पूर्ण;

अटल काष्ठा clk *clks[clk_max];
अटल काष्ठा clk_onecell_data clk_data;

अटल क्रमागत imx23_clk clks_init_on[] __initdata = अणु
	cpu, hbus, xbus, emi, uart,
पूर्ण;

अटल व्योम __init mx23_घड़ीs_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *dcnp;
	u32 i;

	dcnp = of_find_compatible_node(शून्य, शून्य, "fsl,imx23-digctl");
	digctrl = of_iomap(dcnp, 0);
	WARN_ON(!digctrl);
	of_node_put(dcnp);

	clkctrl = of_iomap(np, 0);
	WARN_ON(!clkctrl);

	clk_misc_init();

	clks[ref_xtal] = mxs_clk_fixed("ref_xtal", 24000000);
	clks[pll] = mxs_clk_pll("pll", "ref_xtal", PLLCTRL0, 16, 480000000);
	clks[ref_cpu] = mxs_clk_ref("ref_cpu", "pll", FRAC, 0);
	clks[ref_emi] = mxs_clk_ref("ref_emi", "pll", FRAC, 1);
	clks[ref_pix] = mxs_clk_ref("ref_pix", "pll", FRAC, 2);
	clks[ref_io] = mxs_clk_ref("ref_io", "pll", FRAC, 3);
	clks[saअगर_sel] = mxs_clk_mux("saif_sel", CLKSEQ, 0, 1, sel_pll, ARRAY_SIZE(sel_pll));
	clks[lcdअगर_sel] = mxs_clk_mux("lcdif_sel", CLKSEQ, 1, 1, sel_pix, ARRAY_SIZE(sel_pix));
	clks[gpmi_sel] = mxs_clk_mux("gpmi_sel", CLKSEQ, 4, 1, sel_io, ARRAY_SIZE(sel_io));
	clks[ssp_sel] = mxs_clk_mux("ssp_sel", CLKSEQ, 5, 1, sel_io, ARRAY_SIZE(sel_io));
	clks[emi_sel] = mxs_clk_mux("emi_sel", CLKSEQ, 6, 1, emi_sels, ARRAY_SIZE(emi_sels));
	clks[cpu] = mxs_clk_mux("cpu", CLKSEQ, 7, 1, cpu_sels, ARRAY_SIZE(cpu_sels));
	clks[eपंचांग_sel] = mxs_clk_mux("etm_sel", CLKSEQ, 8, 1, sel_cpu, ARRAY_SIZE(sel_cpu));
	clks[cpu_pll] = mxs_clk_भाग("cpu_pll", "ref_cpu", CPU, 0, 6, 28);
	clks[cpu_xtal] = mxs_clk_भाग("cpu_xtal", "ref_xtal", CPU, 16, 10, 29);
	clks[hbus] = mxs_clk_भाग("hbus", "cpu", HBUS, 0, 5, 29);
	clks[xbus] = mxs_clk_भाग("xbus", "ref_xtal", XBUS, 0, 10, 31);
	clks[lcdअगर_भाग] = mxs_clk_भाग("lcdif_div", "lcdif_sel", PIX, 0, 12, 29);
	clks[ssp_भाग] = mxs_clk_भाग("ssp_div", "ssp_sel", SSP, 0, 9, 29);
	clks[gpmi_भाग] = mxs_clk_भाग("gpmi_div", "gpmi_sel", GPMI, 0, 10, 29);
	clks[emi_pll] = mxs_clk_भाग("emi_pll", "ref_emi", EMI, 0, 6, 28);
	clks[emi_xtal] = mxs_clk_भाग("emi_xtal", "ref_xtal", EMI, 8, 4, 29);
	clks[eपंचांग_भाग] = mxs_clk_भाग("etm_div", "etm_sel", ETM, 0, 6, 29);
	clks[saअगर_भाग] = mxs_clk_frac("saif_div", "saif_sel", SAIF, 0, 16, 29);
	clks[clk32k_भाग] = mxs_clk_fixed_factor("clk32k_div", "ref_xtal", 1, 750);
	clks[rtc] = mxs_clk_fixed_factor("rtc", "ref_xtal", 1, 768);
	clks[adc] = mxs_clk_fixed_factor("adc", "clk32k", 1, 16);
	clks[spdअगर_भाग] = mxs_clk_fixed_factor("spdif_div", "pll", 1, 4);
	clks[clk32k] = mxs_clk_gate("clk32k", "clk32k_div", XTAL, 26);
	clks[dri] = mxs_clk_gate("dri", "ref_xtal", XTAL, 28);
	clks[pwm] = mxs_clk_gate("pwm", "ref_xtal", XTAL, 29);
	clks[filt] = mxs_clk_gate("filt", "ref_xtal", XTAL, 30);
	clks[uart] = mxs_clk_gate("uart", "ref_xtal", XTAL, 31);
	clks[ssp] = mxs_clk_gate("ssp", "ssp_div", SSP, 31);
	clks[gpmi] = mxs_clk_gate("gpmi", "gpmi_div", GPMI, 31);
	clks[spdअगर] = mxs_clk_gate("spdif", "spdif_div", SPDIF, 31);
	clks[emi] = mxs_clk_gate("emi", "emi_sel", EMI, 31);
	clks[saअगर] = mxs_clk_gate("saif", "saif_div", SAIF, 31);
	clks[lcdअगर] = mxs_clk_gate("lcdif", "lcdif_div", PIX, 31);
	clks[eपंचांग] = mxs_clk_gate("etm", "etm_div", ETM, 31);
	clks[usb] = mxs_clk_gate("usb", "usb_phy", DIGCTRL, 2);
	clks[usb_phy] = clk_रेजिस्टर_gate(शून्य, "usb_phy", "pll", 0, PLLCTRL0, 18, 0, &mxs_lock);

	क्रम (i = 0; i < ARRAY_SIZE(clks); i++)
		अगर (IS_ERR(clks[i])) अणु
			pr_err("i.MX23 clk %d: register failed with %ld\n",
				i, PTR_ERR(clks[i]));
			वापस;
		पूर्ण

	clk_data.clks = clks;
	clk_data.clk_num = ARRAY_SIZE(clks);
	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data);

	क्रम (i = 0; i < ARRAY_SIZE(clks_init_on); i++)
		clk_prepare_enable(clks[clks_init_on[i]]);

पूर्ण
CLK_OF_DECLARE(imx23_clkctrl, "fsl,imx23-clkctrl", mx23_घड़ीs_init);
