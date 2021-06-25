<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 */

#समावेश <dt-bindings/घड़ी/imx6ul-घड़ी.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/types.h>

#समावेश "clk.h"

अटल स्थिर अक्षर *pll_bypass_src_sels[] = अणु "osc", "dummy", पूर्ण;
अटल स्थिर अक्षर *pll1_bypass_sels[] = अणु "pll1", "pll1_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll2_bypass_sels[] = अणु "pll2", "pll2_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll3_bypass_sels[] = अणु "pll3", "pll3_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll4_bypass_sels[] = अणु "pll4", "pll4_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll5_bypass_sels[] = अणु "pll5", "pll5_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll6_bypass_sels[] = अणु "pll6", "pll6_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll7_bypass_sels[] = अणु "pll7", "pll7_bypass_src", पूर्ण;
अटल स्थिर अक्षर *ca7_secondary_sels[] = अणु "pll2_pfd2_396m", "pll2_bus", पूर्ण;
अटल स्थिर अक्षर *step_sels[] = अणु "osc", "ca7_secondary_sel", पूर्ण;
अटल स्थिर अक्षर *pll1_sw_sels[] = अणु "pll1_sys", "step", पूर्ण;
अटल स्थिर अक्षर *axi_alt_sels[] = अणु "pll2_pfd2_396m", "pll3_pfd1_540m", पूर्ण;
अटल स्थिर अक्षर *axi_sels[] = अणु"periph", "axi_alt_sel", पूर्ण;
अटल स्थिर अक्षर *periph_pre_sels[] = अणु "pll2_bus", "pll2_pfd2_396m", "pll2_pfd0_352m", "pll2_198m", पूर्ण;
अटल स्थिर अक्षर *periph2_pre_sels[] = अणु "pll2_bus", "pll2_pfd2_396m", "pll2_pfd0_352m", "pll4_audio_div", पूर्ण;
अटल स्थिर अक्षर *periph_clk2_sels[] = अणु "pll3_usb_otg", "osc", "pll2_bypass_src", पूर्ण;
अटल स्थिर अक्षर *periph2_clk2_sels[] = अणु "pll3_usb_otg", "osc", पूर्ण;
अटल स्थिर अक्षर *periph_sels[] = अणु "periph_pre", "periph_clk2", पूर्ण;
अटल स्थिर अक्षर *periph2_sels[] = अणु "periph2_pre", "periph2_clk2", पूर्ण;
अटल स्थिर अक्षर *usdhc_sels[] = अणु "pll2_pfd2_396m", "pll2_pfd0_352m", पूर्ण;
अटल स्थिर अक्षर *bch_sels[] = अणु "pll2_pfd2_396m", "pll2_pfd0_352m", पूर्ण;
अटल स्थिर अक्षर *gpmi_sels[] = अणु "pll2_pfd2_396m", "pll2_pfd0_352m", पूर्ण;
अटल स्थिर अक्षर *eim_slow_sels[] =  अणु "axi", "pll3_usb_otg", "pll2_pfd2_396m", "pll3_pfd0_720m", पूर्ण;
अटल स्थिर अक्षर *spdअगर_sels[] = अणु "pll4_audio_div", "pll3_pfd2_508m", "pll5_video_div", "pll3_usb_otg", पूर्ण;
अटल स्थिर अक्षर *sai_sels[] = अणु "pll3_pfd2_508m", "pll5_video_div", "pll4_audio_div", पूर्ण;
अटल स्थिर अक्षर *lcdअगर_pre_sels[] = अणु "pll2_bus", "pll3_pfd3_454m", "pll5_video_div", "pll2_pfd0_352m", "pll2_pfd1_594m", "pll3_pfd1_540m", पूर्ण;
अटल स्थिर अक्षर *sim_pre_sels[] = अणु "pll2_bus", "pll3_usb_otg", "pll5_video_div", "pll2_pfd0_352m", "pll2_pfd2_396m", "pll3_pfd2_508m", पूर्ण;
अटल स्थिर अक्षर *ldb_di0_sels[] = अणु "pll5_video_div", "pll2_pfd0_352m", "pll2_pfd2_396m", "pll2_pfd3_594m", "pll2_pfd1_594m", "pll3_pfd3_454m", पूर्ण;
अटल स्थिर अक्षर *ldb_di0_भाग_sels[] = अणु "ldb_di0_div_3_5", "ldb_di0_div_7", पूर्ण;
अटल स्थिर अक्षर *ldb_di1_भाग_sels[] = अणु "ldb_di1_div_3_5", "ldb_di1_div_7", पूर्ण;
अटल स्थिर अक्षर *qspi1_sels[] = अणु "pll3_usb_otg", "pll2_pfd0_352m", "pll2_pfd2_396m", "pll2_bus", "pll3_pfd3_454m", "pll3_pfd2_508m", पूर्ण;
अटल स्थिर अक्षर *enfc_sels[] = अणु "pll2_pfd0_352m", "pll2_bus", "pll3_usb_otg", "pll2_pfd2_396m", "pll3_pfd3_454m", "dummy", "dummy", "dummy", पूर्ण;
अटल स्थिर अक्षर *can_sels[] = अणु "pll3_60m", "osc", "pll3_80m", "dummy", पूर्ण;
अटल स्थिर अक्षर *ecspi_sels[] = अणु "pll3_60m", "osc", पूर्ण;
अटल स्थिर अक्षर *uart_sels[] = अणु "pll3_80m", "osc", पूर्ण;
अटल स्थिर अक्षर *perclk_sels[] = अणु "ipg", "osc", पूर्ण;
अटल स्थिर अक्षर *lcdअगर_sels[] = अणु "lcdif_podf", "ipp_di0", "ipp_di1", "ldb_di0", "ldb_di1", पूर्ण;
अटल स्थिर अक्षर *csi_sels[] = अणु "osc", "pll2_pfd2_396m", "pll3_120m", "pll3_pfd1_540m", पूर्ण;
अटल स्थिर अक्षर *sim_sels[] = अणु "sim_podf", "ipp_di0", "ipp_di1", "ldb_di0", "ldb_di1", पूर्ण;
/* epdc_pre_sels, epdc_sels, esai_sels only exists on i.MX6ULL */
अटल स्थिर अक्षर *epdc_pre_sels[] = अणु "pll2_bus", "pll3_usb_otg", "pll5_video_div", "pll2_pfd0_352m", "pll2_pfd2_396m", "pll3_pfd2_508m", पूर्ण;
अटल स्थिर अक्षर *esai_sels[] = अणु "pll4_audio_div", "pll3_pfd2_508m", "pll5_video_div", "pll3_usb_otg", पूर्ण;
अटल स्थिर अक्षर *epdc_sels[] = अणु "epdc_podf", "ipp_di0", "ipp_di1", "ldb_di0", "ldb_di1", पूर्ण;
अटल स्थिर अक्षर *cko1_sels[] = अणु "dummy", "dummy", "dummy", "dummy", "dummy", "axi", "enfc", "dummy", "dummy",
				   "dummy", "lcdif_pix", "ahb", "ipg", "ipg_per", "ckil", "pll4_audio_div", पूर्ण;
अटल स्थिर अक्षर *cko2_sels[] = अणु "dummy", "dummy", "dummy", "usdhc1", "dummy", "dummy", "ecspi_root", "dummy",
				   "dummy", "dummy", "dummy", "dummy", "dummy", "dummy", "osc", "dummy",
				   "dummy", "usdhc2", "sai1", "sai2", "sai3", "dummy", "dummy", "can_root",
				   "dummy", "dummy", "dummy", "dummy", "uart_serial", "spdif", "dummy", "dummy", पूर्ण;
अटल स्थिर अक्षर *cko_sels[] = अणु "cko1", "cko2", पूर्ण;

अटल काष्ठा clk_hw **hws;
अटल काष्ठा clk_hw_onecell_data *clk_hw_data;

अटल स्थिर काष्ठा clk_भाग_प्रकारable clk_enet_ref_table[] = अणु
	अणु .val = 0, .भाग = 20, पूर्ण,
	अणु .val = 1, .भाग = 10, पूर्ण,
	अणु .val = 2, .भाग = 5, पूर्ण,
	अणु .val = 3, .भाग = 4, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable[] = अणु
	अणु .val = 2, .भाग = 1, पूर्ण,
	अणु .val = 1, .भाग = 2, पूर्ण,
	अणु .val = 0, .भाग = 4, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable video_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 1, पूर्ण,
	अणु .val = 1, .भाग = 2, पूर्ण,
	अणु .val = 2, .भाग = 1, पूर्ण,
	अणु .val = 3, .भाग = 4, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल u32 share_count_asrc;
अटल u32 share_count_audio;
अटल u32 share_count_sai1;
अटल u32 share_count_sai2;
अटल u32 share_count_sai3;
अटल u32 share_count_esai;

अटल अंतरभूत पूर्णांक clk_on_imx6ul(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,imx6ul");
पूर्ण

अटल अंतरभूत पूर्णांक clk_on_imx6ull(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,imx6ull");
पूर्ण

अटल व्योम __init imx6ul_घड़ीs_init(काष्ठा device_node *ccm_node)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *base;

	clk_hw_data = kzalloc(काष्ठा_size(clk_hw_data, hws,
					  IMX6UL_CLK_END), GFP_KERNEL);
	अगर (WARN_ON(!clk_hw_data))
		वापस;

	clk_hw_data->num = IMX6UL_CLK_END;
	hws = clk_hw_data->hws;

	hws[IMX6UL_CLK_DUMMY] = imx_clk_hw_fixed("dummy", 0);

	hws[IMX6UL_CLK_CKIL] = imx_obtain_fixed_clk_hw(ccm_node, "ckil");
	hws[IMX6UL_CLK_OSC] = imx_obtain_fixed_clk_hw(ccm_node, "osc");

	/* ipp_di घड़ी is बाह्यal input */
	hws[IMX6UL_CLK_IPP_DI0] = imx_obtain_fixed_clk_hw(ccm_node, "ipp_di0");
	hws[IMX6UL_CLK_IPP_DI1] = imx_obtain_fixed_clk_hw(ccm_node, "ipp_di1");

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx6ul-anatop");
	base = of_iomap(np, 0);
	of_node_put(np);
	WARN_ON(!base);

	hws[IMX6UL_PLL1_BYPASS_SRC] = imx_clk_hw_mux("pll1_bypass_src", base + 0x00, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6UL_PLL2_BYPASS_SRC] = imx_clk_hw_mux("pll2_bypass_src", base + 0x30, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6UL_PLL3_BYPASS_SRC] = imx_clk_hw_mux("pll3_bypass_src", base + 0x10, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6UL_PLL4_BYPASS_SRC] = imx_clk_hw_mux("pll4_bypass_src", base + 0x70, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6UL_PLL5_BYPASS_SRC] = imx_clk_hw_mux("pll5_bypass_src", base + 0xa0, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6UL_PLL6_BYPASS_SRC] = imx_clk_hw_mux("pll6_bypass_src", base + 0xe0, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6UL_PLL7_BYPASS_SRC] = imx_clk_hw_mux("pll7_bypass_src", base + 0x20, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));

	hws[IMX6UL_CLK_PLL1] = imx_clk_hw_pllv3(IMX_PLLV3_SYS,	 "pll1", "osc", base + 0x00, 0x7f);
	hws[IMX6UL_CLK_PLL2] = imx_clk_hw_pllv3(IMX_PLLV3_GENERIC, "pll2", "osc", base + 0x30, 0x1);
	hws[IMX6UL_CLK_PLL3] = imx_clk_hw_pllv3(IMX_PLLV3_USB,	 "pll3", "osc", base + 0x10, 0x3);
	hws[IMX6UL_CLK_PLL4] = imx_clk_hw_pllv3(IMX_PLLV3_AV,	 "pll4", "osc", base + 0x70, 0x7f);
	hws[IMX6UL_CLK_PLL5] = imx_clk_hw_pllv3(IMX_PLLV3_AV,	 "pll5", "osc", base + 0xa0, 0x7f);
	hws[IMX6UL_CLK_PLL6] = imx_clk_hw_pllv3(IMX_PLLV3_ENET,	 "pll6", "osc", base + 0xe0, 0x3);
	hws[IMX6UL_CLK_PLL7] = imx_clk_hw_pllv3(IMX_PLLV3_USB,	 "pll7", "osc", base + 0x20, 0x3);

	hws[IMX6UL_PLL1_BYPASS] = imx_clk_hw_mux_flags("pll1_bypass", base + 0x00, 16, 1, pll1_bypass_sels, ARRAY_SIZE(pll1_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6UL_PLL2_BYPASS] = imx_clk_hw_mux_flags("pll2_bypass", base + 0x30, 16, 1, pll2_bypass_sels, ARRAY_SIZE(pll2_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6UL_PLL3_BYPASS] = imx_clk_hw_mux_flags("pll3_bypass", base + 0x10, 16, 1, pll3_bypass_sels, ARRAY_SIZE(pll3_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6UL_PLL4_BYPASS] = imx_clk_hw_mux_flags("pll4_bypass", base + 0x70, 16, 1, pll4_bypass_sels, ARRAY_SIZE(pll4_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6UL_PLL5_BYPASS] = imx_clk_hw_mux_flags("pll5_bypass", base + 0xa0, 16, 1, pll5_bypass_sels, ARRAY_SIZE(pll5_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6UL_PLL6_BYPASS] = imx_clk_hw_mux_flags("pll6_bypass", base + 0xe0, 16, 1, pll6_bypass_sels, ARRAY_SIZE(pll6_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6UL_PLL7_BYPASS] = imx_clk_hw_mux_flags("pll7_bypass", base + 0x20, 16, 1, pll7_bypass_sels, ARRAY_SIZE(pll7_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6UL_CLK_CSI_SEL] = imx_clk_hw_mux_flags("csi_sel", base + 0x3c, 9, 2, csi_sels, ARRAY_SIZE(csi_sels), CLK_SET_RATE_PARENT);

	/* Do not bypass PLLs initially */
	clk_set_parent(hws[IMX6UL_PLL1_BYPASS]->clk, hws[IMX6UL_CLK_PLL1]->clk);
	clk_set_parent(hws[IMX6UL_PLL2_BYPASS]->clk, hws[IMX6UL_CLK_PLL2]->clk);
	clk_set_parent(hws[IMX6UL_PLL3_BYPASS]->clk, hws[IMX6UL_CLK_PLL3]->clk);
	clk_set_parent(hws[IMX6UL_PLL4_BYPASS]->clk, hws[IMX6UL_CLK_PLL4]->clk);
	clk_set_parent(hws[IMX6UL_PLL5_BYPASS]->clk, hws[IMX6UL_CLK_PLL5]->clk);
	clk_set_parent(hws[IMX6UL_PLL6_BYPASS]->clk, hws[IMX6UL_CLK_PLL6]->clk);
	clk_set_parent(hws[IMX6UL_PLL7_BYPASS]->clk, hws[IMX6UL_CLK_PLL7]->clk);

	hws[IMX6UL_CLK_PLL1_SYS]	= imx_clk_hw_fixed_factor("pll1_sys",	"pll1_bypass", 1, 1);
	hws[IMX6UL_CLK_PLL2_BUS]	= imx_clk_hw_gate("pll2_bus",	"pll2_bypass", base + 0x30, 13);
	hws[IMX6UL_CLK_PLL3_USB_OTG]	= imx_clk_hw_gate("pll3_usb_otg",	"pll3_bypass", base + 0x10, 13);
	hws[IMX6UL_CLK_PLL4_AUDIO]	= imx_clk_hw_gate("pll4_audio",	"pll4_bypass", base + 0x70, 13);
	hws[IMX6UL_CLK_PLL5_VIDEO]	= imx_clk_hw_gate("pll5_video",	"pll5_bypass", base + 0xa0, 13);
	hws[IMX6UL_CLK_PLL6_ENET]	= imx_clk_hw_gate("pll6_enet",	"pll6_bypass", base + 0xe0, 13);
	hws[IMX6UL_CLK_PLL7_USB_HOST]	= imx_clk_hw_gate("pll7_usb_host",	"pll7_bypass", base + 0x20, 13);

	/*
	 * Bit 20 is the reserved and पढ़ो-only bit, we करो this only क्रम:
	 * - Do nothing क्रम usbphy clk_enable/disable
	 * - Keep refcount when करो usbphy clk_enable/disable, in that हाल,
	 * the clk framework many need to enable/disable usbphy's parent
	 */
	hws[IMX6UL_CLK_USBPHY1] = imx_clk_hw_gate("usbphy1", "pll3_usb_otg",  base + 0x10, 20);
	hws[IMX6UL_CLK_USBPHY2] = imx_clk_hw_gate("usbphy2", "pll7_usb_host", base + 0x20, 20);

	/*
	 * usbphy*_gate needs to be on after प्रणाली boots up, and software
	 * never needs to control it anymore.
	 */
	hws[IMX6UL_CLK_USBPHY1_GATE] = imx_clk_hw_gate("usbphy1_gate", "dummy", base + 0x10, 6);
	hws[IMX6UL_CLK_USBPHY2_GATE] = imx_clk_hw_gate("usbphy2_gate", "dummy", base + 0x20, 6);

	/*					name		   parent_name	   reg		idx */
	hws[IMX6UL_CLK_PLL2_PFD0] = imx_clk_hw_pfd("pll2_pfd0_352m", "pll2_bus",	   base + 0x100, 0);
	hws[IMX6UL_CLK_PLL2_PFD1] = imx_clk_hw_pfd("pll2_pfd1_594m", "pll2_bus",	   base + 0x100, 1);
	hws[IMX6UL_CLK_PLL2_PFD2] = imx_clk_hw_pfd("pll2_pfd2_396m", "pll2_bus",	   base + 0x100, 2);
	hws[IMX6UL_CLK_PLL2_PFD3] = imx_clk_hw_pfd("pll2_pfd3_594m", "pll2_bus",	   base + 0x100, 3);
	hws[IMX6UL_CLK_PLL3_PFD0] = imx_clk_hw_pfd("pll3_pfd0_720m", "pll3_usb_otg", base + 0xf0,  0);
	hws[IMX6UL_CLK_PLL3_PFD1] = imx_clk_hw_pfd("pll3_pfd1_540m", "pll3_usb_otg", base + 0xf0,  1);
	hws[IMX6UL_CLK_PLL3_PFD2] = imx_clk_hw_pfd("pll3_pfd2_508m", "pll3_usb_otg", base + 0xf0,	 2);
	hws[IMX6UL_CLK_PLL3_PFD3] = imx_clk_hw_pfd("pll3_pfd3_454m", "pll3_usb_otg", base + 0xf0,	 3);

	hws[IMX6UL_CLK_ENET_REF] = clk_hw_रेजिस्टर_भागider_table(शून्य, "enet_ref", "pll6_enet", 0,
			base + 0xe0, 0, 2, 0, clk_enet_ref_table, &imx_ccm_lock);
	hws[IMX6UL_CLK_ENET2_REF] = clk_hw_रेजिस्टर_भागider_table(शून्य, "enet2_ref", "pll6_enet", 0,
			base + 0xe0, 2, 2, 0, clk_enet_ref_table, &imx_ccm_lock);

	hws[IMX6UL_CLK_ENET2_REF_125M] = imx_clk_hw_gate("enet_ref_125m", "enet2_ref", base + 0xe0, 20);
	hws[IMX6UL_CLK_ENET_PTP_REF]	= imx_clk_hw_fixed_factor("enet_ptp_ref", "pll6_enet", 1, 20);
	hws[IMX6UL_CLK_ENET_PTP]	= imx_clk_hw_gate("enet_ptp", "enet_ptp_ref", base + 0xe0, 21);

	hws[IMX6UL_CLK_PLL4_POST_DIV]  = clk_hw_रेजिस्टर_भागider_table(शून्य, "pll4_post_div", "pll4_audio",
		 CLK_SET_RATE_PARENT | CLK_SET_RATE_GATE, base + 0x70, 19, 2, 0, post_भाग_प्रकारable, &imx_ccm_lock);
	hws[IMX6UL_CLK_PLL4_AUDIO_DIV] = clk_hw_रेजिस्टर_भागider(शून्य, "pll4_audio_div", "pll4_post_div",
		 CLK_SET_RATE_PARENT | CLK_SET_RATE_GATE, base + 0x170, 15, 1, 0, &imx_ccm_lock);
	hws[IMX6UL_CLK_PLL5_POST_DIV]  = clk_hw_रेजिस्टर_भागider_table(शून्य, "pll5_post_div", "pll5_video",
		 CLK_SET_RATE_PARENT | CLK_SET_RATE_GATE, base + 0xa0, 19, 2, 0, post_भाग_प्रकारable, &imx_ccm_lock);
	hws[IMX6UL_CLK_PLL5_VIDEO_DIV] = clk_hw_रेजिस्टर_भागider_table(शून्य, "pll5_video_div", "pll5_post_div",
		 CLK_SET_RATE_PARENT | CLK_SET_RATE_GATE, base + 0x170, 30, 2, 0, video_भाग_प्रकारable, &imx_ccm_lock);

	/*						   name		parent_name	 mult  भाग */
	hws[IMX6UL_CLK_PLL2_198M] = imx_clk_hw_fixed_factor("pll2_198m", "pll2_pfd2_396m", 1,	2);
	hws[IMX6UL_CLK_PLL3_80M]  = imx_clk_hw_fixed_factor("pll3_80m",  "pll3_usb_otg",   1,	6);
	hws[IMX6UL_CLK_PLL3_60M]  = imx_clk_hw_fixed_factor("pll3_60m",  "pll3_usb_otg",   1,	8);
	hws[IMX6UL_CLK_GPT_3M]	   = imx_clk_hw_fixed_factor("gpt_3m",	"osc",		 1,	8);

	np = ccm_node;
	base = of_iomap(np, 0);
	WARN_ON(!base);

	hws[IMX6UL_CA7_SECONDARY_SEL]	  = imx_clk_hw_mux("ca7_secondary_sel", base + 0xc, 3, 1, ca7_secondary_sels, ARRAY_SIZE(ca7_secondary_sels));
	hws[IMX6UL_CLK_STEP]		  = imx_clk_hw_mux("step", base + 0x0c, 8, 1, step_sels, ARRAY_SIZE(step_sels));
	hws[IMX6UL_CLK_PLL1_SW]	  = imx_clk_hw_mux_flags("pll1_sw",   base + 0x0c, 2,  1, pll1_sw_sels, ARRAY_SIZE(pll1_sw_sels), 0);
	hws[IMX6UL_CLK_AXI_ALT_SEL]	  = imx_clk_hw_mux("axi_alt_sel",		base + 0x14, 7,  1, axi_alt_sels, ARRAY_SIZE(axi_alt_sels));
	hws[IMX6UL_CLK_AXI_SEL]	  = imx_clk_hw_mux_flags("axi_sel",	base + 0x14, 6,  1, axi_sels, ARRAY_SIZE(axi_sels), 0);
	hws[IMX6UL_CLK_PERIPH_PRE]	  = imx_clk_hw_mux("periph_pre",       base + 0x18, 18, 2, periph_pre_sels, ARRAY_SIZE(periph_pre_sels));
	hws[IMX6UL_CLK_PERIPH2_PRE]	  = imx_clk_hw_mux("periph2_pre",      base + 0x18, 21, 2, periph2_pre_sels, ARRAY_SIZE(periph2_pre_sels));
	hws[IMX6UL_CLK_PERIPH_CLK2_SEL]  = imx_clk_hw_mux("periph_clk2_sel",  base + 0x18, 12, 2, periph_clk2_sels, ARRAY_SIZE(periph_clk2_sels));
	hws[IMX6UL_CLK_PERIPH2_CLK2_SEL] = imx_clk_hw_mux("periph2_clk2_sel", base + 0x18, 20, 1, periph2_clk2_sels, ARRAY_SIZE(periph2_clk2_sels));
	hws[IMX6UL_CLK_EIM_SLOW_SEL]	  = imx_clk_hw_mux("eim_slow_sel", base + 0x1c, 29, 2, eim_slow_sels, ARRAY_SIZE(eim_slow_sels));
	hws[IMX6UL_CLK_GPMI_SEL]	  = imx_clk_hw_mux("gpmi_sel",     base + 0x1c, 19, 1, gpmi_sels, ARRAY_SIZE(gpmi_sels));
	hws[IMX6UL_CLK_BCH_SEL]	  = imx_clk_hw_mux("bch_sel",	base + 0x1c, 18, 1, bch_sels, ARRAY_SIZE(bch_sels));
	hws[IMX6UL_CLK_USDHC2_SEL]	  = imx_clk_hw_mux("usdhc2_sel",   base + 0x1c, 17, 1, usdhc_sels, ARRAY_SIZE(usdhc_sels));
	hws[IMX6UL_CLK_USDHC1_SEL]	  = imx_clk_hw_mux("usdhc1_sel",   base + 0x1c, 16, 1, usdhc_sels, ARRAY_SIZE(usdhc_sels));
	hws[IMX6UL_CLK_SAI3_SEL]	  = imx_clk_hw_mux("sai3_sel",     base + 0x1c, 14, 2, sai_sels, ARRAY_SIZE(sai_sels));
	hws[IMX6UL_CLK_SAI2_SEL]         = imx_clk_hw_mux("sai2_sel",     base + 0x1c, 12, 2, sai_sels, ARRAY_SIZE(sai_sels));
	hws[IMX6UL_CLK_SAI1_SEL]	  = imx_clk_hw_mux("sai1_sel",     base + 0x1c, 10, 2, sai_sels, ARRAY_SIZE(sai_sels));
	hws[IMX6UL_CLK_QSPI1_SEL]	  = imx_clk_hw_mux("qspi1_sel",    base + 0x1c, 7,  3, qspi1_sels, ARRAY_SIZE(qspi1_sels));
	hws[IMX6UL_CLK_PERCLK_SEL]	  = imx_clk_hw_mux("perclk_sel",	base + 0x1c, 6,  1, perclk_sels, ARRAY_SIZE(perclk_sels));
	hws[IMX6UL_CLK_CAN_SEL]	  = imx_clk_hw_mux("can_sel",	base + 0x20, 8,  2, can_sels, ARRAY_SIZE(can_sels));
	अगर (clk_on_imx6ull())
		hws[IMX6ULL_CLK_ESAI_SEL]	  = imx_clk_hw_mux("esai_sel",	base + 0x20, 19, 2, esai_sels, ARRAY_SIZE(esai_sels));
	hws[IMX6UL_CLK_UART_SEL]	  = imx_clk_hw_mux("uart_sel",	base + 0x24, 6,  1, uart_sels, ARRAY_SIZE(uart_sels));
	hws[IMX6UL_CLK_ENFC_SEL]	  = imx_clk_hw_mux("enfc_sel",	base + 0x2c, 15, 3, enfc_sels, ARRAY_SIZE(enfc_sels));
	hws[IMX6UL_CLK_LDB_DI0_SEL]	  = imx_clk_hw_mux("ldb_di0_sel",	base + 0x2c, 9,  3, ldb_di0_sels, ARRAY_SIZE(ldb_di0_sels));
	hws[IMX6UL_CLK_SPDIF_SEL]	  = imx_clk_hw_mux("spdif_sel",	base + 0x30, 20, 2, spdअगर_sels, ARRAY_SIZE(spdअगर_sels));
	अगर (clk_on_imx6ul()) अणु
		hws[IMX6UL_CLK_SIM_PRE_SEL]	= imx_clk_hw_mux("sim_pre_sel",	base + 0x34, 15, 3, sim_pre_sels, ARRAY_SIZE(sim_pre_sels));
		hws[IMX6UL_CLK_SIM_SEL]		= imx_clk_hw_mux("sim_sel",	base + 0x34, 9, 3, sim_sels, ARRAY_SIZE(sim_sels));
	पूर्ण अन्यथा अगर (clk_on_imx6ull()) अणु
		hws[IMX6ULL_CLK_EPDC_PRE_SEL]	= imx_clk_hw_mux("epdc_pre_sel",	base + 0x34, 15, 3, epdc_pre_sels, ARRAY_SIZE(epdc_pre_sels));
		hws[IMX6ULL_CLK_EPDC_SEL]	= imx_clk_hw_mux("epdc_sel",	base + 0x34, 9, 3, epdc_sels, ARRAY_SIZE(epdc_sels));
	पूर्ण
	hws[IMX6UL_CLK_ECSPI_SEL]	  = imx_clk_hw_mux("ecspi_sel",	base + 0x38, 18, 1, ecspi_sels, ARRAY_SIZE(ecspi_sels));
	hws[IMX6UL_CLK_LCDIF_PRE_SEL]	  = imx_clk_hw_mux_flags("lcdif_pre_sel", base + 0x38, 15, 3, lcdअगर_pre_sels, ARRAY_SIZE(lcdअगर_pre_sels), CLK_SET_RATE_PARENT);
	hws[IMX6UL_CLK_LCDIF_SEL]	  = imx_clk_hw_mux("lcdif_sel",	base + 0x38, 9, 3, lcdअगर_sels, ARRAY_SIZE(lcdअगर_sels));

	hws[IMX6UL_CLK_LDB_DI0_DIV_SEL]  = imx_clk_hw_mux("ldb_di0", base + 0x20, 10, 1, ldb_di0_भाग_sels, ARRAY_SIZE(ldb_di0_भाग_sels));
	hws[IMX6UL_CLK_LDB_DI1_DIV_SEL]  = imx_clk_hw_mux("ldb_di1", base + 0x20, 11, 1, ldb_di1_भाग_sels, ARRAY_SIZE(ldb_di1_भाग_sels));

	hws[IMX6UL_CLK_CKO1_SEL]	  = imx_clk_hw_mux("cko1_sel", base + 0x60, 0,  4, cko1_sels, ARRAY_SIZE(cko1_sels));
	hws[IMX6UL_CLK_CKO2_SEL]	  = imx_clk_hw_mux("cko2_sel", base + 0x60, 16, 5, cko2_sels, ARRAY_SIZE(cko2_sels));
	hws[IMX6UL_CLK_CKO]		  = imx_clk_hw_mux("cko", base + 0x60, 8, 1, cko_sels, ARRAY_SIZE(cko_sels));

	hws[IMX6UL_CLK_LDB_DI0_DIV_3_5] = imx_clk_hw_fixed_factor("ldb_di0_div_3_5", "ldb_di0_sel", 2, 7);
	hws[IMX6UL_CLK_LDB_DI0_DIV_7]	 = imx_clk_hw_fixed_factor("ldb_di0_div_7",   "ldb_di0_sel", 1, 7);
	hws[IMX6UL_CLK_LDB_DI1_DIV_3_5] = imx_clk_hw_fixed_factor("ldb_di1_div_3_5", "qspi1_sel", 2, 7);
	hws[IMX6UL_CLK_LDB_DI1_DIV_7]	 = imx_clk_hw_fixed_factor("ldb_di1_div_7",   "qspi1_sel", 1, 7);

	hws[IMX6UL_CLK_PERIPH]  = imx_clk_hw_busy_mux("periph",  base + 0x14, 25, 1, base + 0x48, 5, periph_sels, ARRAY_SIZE(periph_sels));
	hws[IMX6UL_CLK_PERIPH2] = imx_clk_hw_busy_mux("periph2", base + 0x14, 26, 1, base + 0x48, 3, periph2_sels, ARRAY_SIZE(periph2_sels));

	hws[IMX6UL_CLK_PERIPH_CLK2]	= imx_clk_hw_भागider("periph_clk2",   "periph_clk2_sel",	base + 0x14, 27, 3);
	hws[IMX6UL_CLK_PERIPH2_CLK2]	= imx_clk_hw_भागider("periph2_clk2",  "periph2_clk2_sel",	base + 0x14, 0,  3);
	hws[IMX6UL_CLK_IPG]		= imx_clk_hw_भागider("ipg",	   "ahb",		base + 0x14, 8,	 2);
	hws[IMX6UL_CLK_LCDIF_PODF]	= imx_clk_hw_भागider("lcdif_podf",	   "lcdif_pred",	base + 0x18, 23, 3);
	hws[IMX6UL_CLK_QSPI1_PDOF]	= imx_clk_hw_भागider("qspi1_podf",	   "qspi1_sel",		base + 0x1c, 26, 3);
	hws[IMX6UL_CLK_EIM_SLOW_PODF]	= imx_clk_hw_भागider("eim_slow_podf", "eim_slow_sel",	base + 0x1c, 23, 3);
	hws[IMX6UL_CLK_PERCLK]		= imx_clk_hw_भागider("perclk",	   "perclk_sel",	base + 0x1c, 0,  6);
	hws[IMX6UL_CLK_CAN_PODF]	= imx_clk_hw_भागider("can_podf",	   "can_sel",		base + 0x20, 2,  6);
	hws[IMX6UL_CLK_GPMI_PODF]	= imx_clk_hw_भागider("gpmi_podf",	   "gpmi_sel",		base + 0x24, 22, 3);
	hws[IMX6UL_CLK_BCH_PODF]	= imx_clk_hw_भागider("bch_podf",	   "bch_sel",		base + 0x24, 19, 3);
	hws[IMX6UL_CLK_USDHC2_PODF]	= imx_clk_hw_भागider("usdhc2_podf",   "usdhc2_sel",	base + 0x24, 16, 3);
	hws[IMX6UL_CLK_USDHC1_PODF]	= imx_clk_hw_भागider("usdhc1_podf",   "usdhc1_sel",	base + 0x24, 11, 3);
	hws[IMX6UL_CLK_UART_PODF]	= imx_clk_hw_भागider("uart_podf",	   "uart_sel",		base + 0x24, 0,  6);
	hws[IMX6UL_CLK_SAI3_PRED]	= imx_clk_hw_भागider("sai3_pred",	   "sai3_sel",		base + 0x28, 22, 3);
	hws[IMX6UL_CLK_SAI3_PODF]	= imx_clk_hw_भागider("sai3_podf",	   "sai3_pred",		base + 0x28, 16, 6);
	hws[IMX6UL_CLK_SAI1_PRED]	= imx_clk_hw_भागider("sai1_pred",	   "sai1_sel",		base + 0x28, 6,	 3);
	hws[IMX6UL_CLK_SAI1_PODF]	= imx_clk_hw_भागider("sai1_podf",	   "sai1_pred",		base + 0x28, 0,	 6);
	अगर (clk_on_imx6ull()) अणु
		hws[IMX6ULL_CLK_ESAI_PRED]	= imx_clk_hw_भागider("esai_pred",     "esai_sel",		base + 0x28, 9,  3);
		hws[IMX6ULL_CLK_ESAI_PODF]	= imx_clk_hw_भागider("esai_podf",     "esai_pred",		base + 0x28, 25, 3);
	पूर्ण
	hws[IMX6UL_CLK_ENFC_PRED]	= imx_clk_hw_भागider("enfc_pred",	   "enfc_sel",		base + 0x2c, 18, 3);
	hws[IMX6UL_CLK_ENFC_PODF]	= imx_clk_hw_भागider("enfc_podf",	   "enfc_pred",		base + 0x2c, 21, 6);
	hws[IMX6UL_CLK_SAI2_PRED]	= imx_clk_hw_भागider("sai2_pred",	   "sai2_sel",		base + 0x2c, 6,	 3);
	hws[IMX6UL_CLK_SAI2_PODF]	= imx_clk_hw_भागider("sai2_podf",	   "sai2_pred",		base + 0x2c, 0,  6);
	hws[IMX6UL_CLK_SPDIF_PRED]	= imx_clk_hw_भागider("spdif_pred",	   "spdif_sel",		base + 0x30, 25, 3);
	hws[IMX6UL_CLK_SPDIF_PODF]	= imx_clk_hw_भागider("spdif_podf",	   "spdif_pred",	base + 0x30, 22, 3);
	अगर (clk_on_imx6ul())
		hws[IMX6UL_CLK_SIM_PODF]	= imx_clk_hw_भागider("sim_podf",	   "sim_pre_sel",	base + 0x34, 12, 3);
	अन्यथा अगर (clk_on_imx6ull())
		hws[IMX6ULL_CLK_EPDC_PODF]	= imx_clk_hw_भागider("epdc_podf",	   "epdc_pre_sel",	base + 0x34, 12, 3);
	hws[IMX6UL_CLK_ECSPI_PODF]	= imx_clk_hw_भागider("ecspi_podf",	   "ecspi_sel",		base + 0x38, 19, 6);
	hws[IMX6UL_CLK_LCDIF_PRED]	= imx_clk_hw_भागider("lcdif_pred",	   "lcdif_pre_sel",	base + 0x38, 12, 3);
	hws[IMX6UL_CLK_CSI_PODF]       = imx_clk_hw_भागider("csi_podf",      "csi_sel",           base + 0x3c, 11, 3);

	hws[IMX6UL_CLK_CKO1_PODF]	= imx_clk_hw_भागider("cko1_podf",     "cko1_sel",          base + 0x60, 4,  3);
	hws[IMX6UL_CLK_CKO2_PODF]	= imx_clk_hw_भागider("cko2_podf",     "cko2_sel",          base + 0x60, 21, 3);

	hws[IMX6UL_CLK_ARM]		= imx_clk_hw_busy_भागider("arm",	    "pll1_sw",	base +	0x10, 0,  3,  base + 0x48, 16);
	hws[IMX6UL_CLK_MMDC_PODF]	= imx_clk_hw_busy_भागider("mmdc_podf", "periph2",	base +  0x14, 3,  3,  base + 0x48, 2);
	hws[IMX6UL_CLK_AXI_PODF]	= imx_clk_hw_busy_भागider("axi_podf",  "axi_sel",	base +  0x14, 16, 3,  base + 0x48, 0);
	hws[IMX6UL_CLK_AHB]		= imx_clk_hw_busy_भागider("ahb",	    "periph",	base +  0x14, 10, 3,  base + 0x48, 1);

	/* CCGR0 */
	hws[IMX6UL_CLK_AIPSTZ1]	= imx_clk_hw_gate2_flags("aips_tz1", "ahb", base + 0x68, 0, CLK_IS_CRITICAL);
	hws[IMX6UL_CLK_AIPSTZ2]	= imx_clk_hw_gate2_flags("aips_tz2", "ahb", base + 0x68, 2, CLK_IS_CRITICAL);
	hws[IMX6UL_CLK_APBHDMA]	= imx_clk_hw_gate2("apbh_dma",	"bch_podf",	base + 0x68,	4);
	hws[IMX6UL_CLK_ASRC_IPG]	= imx_clk_hw_gate2_shared("asrc_ipg",	"ahb",	base + 0x68,	6, &share_count_asrc);
	hws[IMX6UL_CLK_ASRC_MEM]	= imx_clk_hw_gate2_shared("asrc_mem",	"ahb",	base + 0x68,	6, &share_count_asrc);
	अगर (clk_on_imx6ul()) अणु
		hws[IMX6UL_CLK_CAAM_MEM]	= imx_clk_hw_gate2("caam_mem",	"ahb",		base + 0x68,	8);
		hws[IMX6UL_CLK_CAAM_ACLK]	= imx_clk_hw_gate2("caam_aclk",	"ahb",		base + 0x68,	10);
		hws[IMX6UL_CLK_CAAM_IPG]	= imx_clk_hw_gate2("caam_ipg",	"ipg",		base + 0x68,	12);
	पूर्ण अन्यथा अगर (clk_on_imx6ull()) अणु
		hws[IMX6ULL_CLK_DCP_CLK]	= imx_clk_hw_gate2("dcp",		"ahb",		base + 0x68,	10);
		hws[IMX6UL_CLK_ENET]		= imx_clk_hw_gate2("enet",		"ipg",		base + 0x68,	12);
		hws[IMX6UL_CLK_ENET_AHB]	= imx_clk_hw_gate2("enet_ahb",	"ahb",		base + 0x68,	12);
	पूर्ण
	hws[IMX6UL_CLK_CAN1_IPG]	= imx_clk_hw_gate2("can1_ipg",	"ipg",		base + 0x68,	14);
	hws[IMX6UL_CLK_CAN1_SERIAL]	= imx_clk_hw_gate2("can1_serial",	"can_podf",	base + 0x68,	16);
	hws[IMX6UL_CLK_CAN2_IPG]	= imx_clk_hw_gate2("can2_ipg",	"ipg",		base + 0x68,	18);
	hws[IMX6UL_CLK_CAN2_SERIAL]	= imx_clk_hw_gate2("can2_serial",	"can_podf",	base + 0x68,	20);
	hws[IMX6UL_CLK_GPT2_BUS]	= imx_clk_hw_gate2("gpt2_bus",	"perclk",	base + 0x68,	24);
	hws[IMX6UL_CLK_GPT2_SERIAL]	= imx_clk_hw_gate2("gpt2_serial",	"perclk",	base + 0x68,	26);
	hws[IMX6UL_CLK_UART2_IPG]	= imx_clk_hw_gate2("uart2_ipg",	"ipg",		base + 0x68,	28);
	hws[IMX6UL_CLK_UART2_SERIAL]	= imx_clk_hw_gate2("uart2_serial",	"uart_podf",	base + 0x68,	28);
	अगर (clk_on_imx6ull())
		hws[IMX6UL_CLK_AIPSTZ3]	= imx_clk_hw_gate2("aips_tz3",	"ahb",		 base + 0x80,	18);
	hws[IMX6UL_CLK_GPIO2]		= imx_clk_hw_gate2("gpio2",	"ipg",		base + 0x68,	30);

	/* CCGR1 */
	hws[IMX6UL_CLK_ECSPI1]		= imx_clk_hw_gate2("ecspi1",	"ecspi_podf",	base + 0x6c,	0);
	hws[IMX6UL_CLK_ECSPI2]		= imx_clk_hw_gate2("ecspi2",	"ecspi_podf",	base + 0x6c,	2);
	hws[IMX6UL_CLK_ECSPI3]		= imx_clk_hw_gate2("ecspi3",	"ecspi_podf",	base + 0x6c,	4);
	hws[IMX6UL_CLK_ECSPI4]		= imx_clk_hw_gate2("ecspi4",	"ecspi_podf",	base + 0x6c,	6);
	hws[IMX6UL_CLK_ADC2]		= imx_clk_hw_gate2("adc2",		"ipg",		base + 0x6c,	8);
	hws[IMX6UL_CLK_UART3_IPG]	= imx_clk_hw_gate2("uart3_ipg",	"ipg",		base + 0x6c,	10);
	hws[IMX6UL_CLK_UART3_SERIAL]	= imx_clk_hw_gate2("uart3_serial",	"uart_podf",	base + 0x6c,	10);
	hws[IMX6UL_CLK_EPIT1]		= imx_clk_hw_gate2("epit1",	"perclk",	base + 0x6c,	12);
	hws[IMX6UL_CLK_EPIT2]		= imx_clk_hw_gate2("epit2",	"perclk",	base + 0x6c,	14);
	hws[IMX6UL_CLK_ADC1]		= imx_clk_hw_gate2("adc1",		"ipg",		base + 0x6c,	16);
	hws[IMX6UL_CLK_GPT1_BUS]	= imx_clk_hw_gate2("gpt1_bus",	"perclk",	base + 0x6c,	20);
	hws[IMX6UL_CLK_GPT1_SERIAL]	= imx_clk_hw_gate2("gpt1_serial",	"perclk",	base + 0x6c,	22);
	hws[IMX6UL_CLK_UART4_IPG]	= imx_clk_hw_gate2("uart4_ipg",	"ipg",		base + 0x6c,	24);
	hws[IMX6UL_CLK_UART4_SERIAL]	= imx_clk_hw_gate2("uart4_serial",	"uart_podf",	base + 0x6c,	24);
	hws[IMX6UL_CLK_GPIO1]		= imx_clk_hw_gate2("gpio1",	"ipg",		base + 0x6c,	26);
	hws[IMX6UL_CLK_GPIO5]		= imx_clk_hw_gate2("gpio5",	"ipg",		base + 0x6c,	30);

	/* CCGR2 */
	अगर (clk_on_imx6ull()) अणु
		hws[IMX6ULL_CLK_ESAI_EXTAL]	= imx_clk_hw_gate2_shared("esai_extal",	"esai_podf",	base + 0x70,	0, &share_count_esai);
		hws[IMX6ULL_CLK_ESAI_IPG]	= imx_clk_hw_gate2_shared("esai_ipg",	"ahb",		base + 0x70,	0, &share_count_esai);
		hws[IMX6ULL_CLK_ESAI_MEM]	= imx_clk_hw_gate2_shared("esai_mem",	"ahb",		base + 0x70,	0, &share_count_esai);
	पूर्ण
	hws[IMX6UL_CLK_CSI]		= imx_clk_hw_gate2("csi",		"csi_podf",		base + 0x70,	2);
	hws[IMX6UL_CLK_I2C1]		= imx_clk_hw_gate2("i2c1",		"perclk",	base + 0x70,	6);
	hws[IMX6UL_CLK_I2C2]		= imx_clk_hw_gate2("i2c2",		"perclk",	base + 0x70,	8);
	hws[IMX6UL_CLK_I2C3]		= imx_clk_hw_gate2("i2c3",		"perclk",	base + 0x70,	10);
	hws[IMX6UL_CLK_OCOTP]		= imx_clk_hw_gate2("ocotp",	"ipg",		base + 0x70,	12);
	hws[IMX6UL_CLK_IOMUXC]		= imx_clk_hw_gate2("iomuxc",	"lcdif_podf",	base + 0x70,	14);
	hws[IMX6UL_CLK_GPIO3]		= imx_clk_hw_gate2("gpio3",	"ipg",		base + 0x70,	26);
	hws[IMX6UL_CLK_LCDIF_APB]	= imx_clk_hw_gate2("lcdif_apb",	"axi",		base + 0x70,	28);
	hws[IMX6UL_CLK_PXP]		= imx_clk_hw_gate2("pxp",		"axi",		base + 0x70,	30);

	/* CCGR3 */
	hws[IMX6UL_CLK_UART5_IPG]	= imx_clk_hw_gate2("uart5_ipg",	"ipg",		base + 0x74,	2);
	hws[IMX6UL_CLK_UART5_SERIAL]	= imx_clk_hw_gate2("uart5_serial",	"uart_podf",	base + 0x74,	2);
	अगर (clk_on_imx6ul()) अणु
		hws[IMX6UL_CLK_ENET]		= imx_clk_hw_gate2("enet",		"ipg",		base + 0x74,	4);
		hws[IMX6UL_CLK_ENET_AHB]	= imx_clk_hw_gate2("enet_ahb",	"ahb",		base + 0x74,	4);
	पूर्ण अन्यथा अगर (clk_on_imx6ull()) अणु
		hws[IMX6ULL_CLK_EPDC_ACLK]	= imx_clk_hw_gate2("epdc_aclk",	"axi",		base + 0x74,	4);
		hws[IMX6ULL_CLK_EPDC_PIX]	= imx_clk_hw_gate2("epdc_pix",	"epdc_podf",	base + 0x74,	4);
	पूर्ण
	hws[IMX6UL_CLK_UART6_IPG]	= imx_clk_hw_gate2("uart6_ipg",	"ipg",		base + 0x74,	6);
	hws[IMX6UL_CLK_UART6_SERIAL]	= imx_clk_hw_gate2("uart6_serial",	"uart_podf",	base + 0x74,	6);
	hws[IMX6UL_CLK_LCDIF_PIX]	= imx_clk_hw_gate2("lcdif_pix",	"lcdif_podf",	base + 0x74,	10);
	hws[IMX6UL_CLK_GPIO4]		= imx_clk_hw_gate2("gpio4",	"ipg",		base + 0x74,	12);
	hws[IMX6UL_CLK_QSPI]		= imx_clk_hw_gate2("qspi1",	"qspi1_podf",	base + 0x74,	14);
	hws[IMX6UL_CLK_WDOG1]		= imx_clk_hw_gate2("wdog1",	"ipg",		base + 0x74,	16);
	hws[IMX6UL_CLK_MMDC_P0_FAST]	= imx_clk_hw_gate_flags("mmdc_p0_fast", "mmdc_podf", base + 0x74,	20, CLK_IS_CRITICAL);
	hws[IMX6UL_CLK_MMDC_P0_IPG]	= imx_clk_hw_gate2_flags("mmdc_p0_ipg",	"ipg",		base + 0x74,	24, CLK_IS_CRITICAL);
	hws[IMX6UL_CLK_MMDC_P1_IPG]	= imx_clk_hw_gate2_flags("mmdc_p1_ipg",	"ipg",		base + 0x74,	26, CLK_IS_CRITICAL);
	hws[IMX6UL_CLK_AXI]		= imx_clk_hw_gate_flags("axi",	"axi_podf",	base + 0x74,	28, CLK_IS_CRITICAL);

	/* CCGR4 */
	hws[IMX6UL_CLK_PER_BCH]	= imx_clk_hw_gate2("per_bch",	"bch_podf",	base + 0x78,	12);
	hws[IMX6UL_CLK_PWM1]		= imx_clk_hw_gate2("pwm1",		"perclk",	base + 0x78,	16);
	hws[IMX6UL_CLK_PWM2]		= imx_clk_hw_gate2("pwm2",		"perclk",	base + 0x78,	18);
	hws[IMX6UL_CLK_PWM3]		= imx_clk_hw_gate2("pwm3",		"perclk",	base + 0x78,	20);
	hws[IMX6UL_CLK_PWM4]		= imx_clk_hw_gate2("pwm4",		"perclk",	base + 0x78,	22);
	hws[IMX6UL_CLK_GPMI_BCH_APB]	= imx_clk_hw_gate2("gpmi_bch_apb",	"bch_podf",	base + 0x78,	24);
	hws[IMX6UL_CLK_GPMI_BCH]	= imx_clk_hw_gate2("gpmi_bch",	"gpmi_podf",	base + 0x78,	26);
	hws[IMX6UL_CLK_GPMI_IO]	= imx_clk_hw_gate2("gpmi_io",	"enfc_podf",	base + 0x78,	28);
	hws[IMX6UL_CLK_GPMI_APB]	= imx_clk_hw_gate2("gpmi_apb",	"bch_podf",	base + 0x78,	30);

	/* CCGR5 */
	hws[IMX6UL_CLK_ROM]		= imx_clk_hw_gate2_flags("rom",	"ahb",		base + 0x7c,	0,	CLK_IS_CRITICAL);
	hws[IMX6UL_CLK_SDMA]		= imx_clk_hw_gate2("sdma",		"ahb",		base + 0x7c,	6);
	hws[IMX6UL_CLK_KPP]		= imx_clk_hw_gate2("kpp",		"ipg",		base + 0x7c,	8);
	hws[IMX6UL_CLK_WDOG2]		= imx_clk_hw_gate2("wdog2",	"ipg",		base + 0x7c,	10);
	hws[IMX6UL_CLK_SPBA]		= imx_clk_hw_gate2("spba",		"ipg",		base + 0x7c,	12);
	hws[IMX6UL_CLK_SPDIF]		= imx_clk_hw_gate2_shared("spdif",		"spdif_podf",	base + 0x7c,	14, &share_count_audio);
	hws[IMX6UL_CLK_SPDIF_GCLK]	= imx_clk_hw_gate2_shared("spdif_gclk",	"ipg",		base + 0x7c,	14, &share_count_audio);
	hws[IMX6UL_CLK_SAI3]		= imx_clk_hw_gate2_shared("sai3",		"sai3_podf",	base + 0x7c,	22, &share_count_sai3);
	hws[IMX6UL_CLK_SAI3_IPG]	= imx_clk_hw_gate2_shared("sai3_ipg",	"ipg",		base + 0x7c,	22, &share_count_sai3);
	hws[IMX6UL_CLK_UART1_IPG]	= imx_clk_hw_gate2("uart1_ipg",	"ipg",		base + 0x7c,	24);
	hws[IMX6UL_CLK_UART1_SERIAL]	= imx_clk_hw_gate2("uart1_serial",	"uart_podf",	base + 0x7c,	24);
	hws[IMX6UL_CLK_UART7_IPG]	= imx_clk_hw_gate2("uart7_ipg",	"ipg",		base + 0x7c,	26);
	hws[IMX6UL_CLK_UART7_SERIAL]	= imx_clk_hw_gate2("uart7_serial",	"uart_podf",	base + 0x7c,	26);
	hws[IMX6UL_CLK_SAI1]		= imx_clk_hw_gate2_shared("sai1",		"sai1_podf",	base + 0x7c,	28, &share_count_sai1);
	hws[IMX6UL_CLK_SAI1_IPG]	= imx_clk_hw_gate2_shared("sai1_ipg",	"ipg",		base + 0x7c,	28, &share_count_sai1);
	hws[IMX6UL_CLK_SAI2]		= imx_clk_hw_gate2_shared("sai2",		"sai2_podf",	base + 0x7c,	30, &share_count_sai2);
	hws[IMX6UL_CLK_SAI2_IPG]	= imx_clk_hw_gate2_shared("sai2_ipg",	"ipg",		base + 0x7c,	30, &share_count_sai2);

	/* CCGR6 */
	hws[IMX6UL_CLK_USBOH3]		= imx_clk_hw_gate2("usboh3",	"ipg",		 base + 0x80,	0);
	hws[IMX6UL_CLK_USDHC1]		= imx_clk_hw_gate2("usdhc1",	"usdhc1_podf",	 base + 0x80,	2);
	hws[IMX6UL_CLK_USDHC2]		= imx_clk_hw_gate2("usdhc2",	"usdhc2_podf",	 base + 0x80,	4);
	अगर (clk_on_imx6ul()) अणु
		hws[IMX6UL_CLK_SIM1]		= imx_clk_hw_gate2("sim1",		"sim_sel",	 base + 0x80,	6);
		hws[IMX6UL_CLK_SIM2]		= imx_clk_hw_gate2("sim2",		"sim_sel",	 base + 0x80,	8);
	पूर्ण
	hws[IMX6UL_CLK_EIM]		= imx_clk_hw_gate2("eim",		"eim_slow_podf", base + 0x80,	10);
	hws[IMX6UL_CLK_PWM8]		= imx_clk_hw_gate2("pwm8",		"perclk",	 base + 0x80,	16);
	hws[IMX6UL_CLK_UART8_IPG]	= imx_clk_hw_gate2("uart8_ipg",	"ipg",		 base + 0x80,	14);
	hws[IMX6UL_CLK_UART8_SERIAL]	= imx_clk_hw_gate2("uart8_serial", "uart_podf",	 base + 0x80,	14);
	hws[IMX6UL_CLK_WDOG3]		= imx_clk_hw_gate2("wdog3",	"ipg",		 base + 0x80,	20);
	hws[IMX6UL_CLK_I2C4]		= imx_clk_hw_gate2("i2c4",		"perclk",	 base + 0x80,	24);
	hws[IMX6UL_CLK_PWM5]		= imx_clk_hw_gate2("pwm5",		"perclk",	 base + 0x80,	26);
	hws[IMX6UL_CLK_PWM6]		= imx_clk_hw_gate2("pwm6",		"perclk",	 base +	0x80,	28);
	hws[IMX6UL_CLK_PWM7]		= imx_clk_hw_gate2("pwm7",		"perclk",	 base + 0x80,	30);

	/* CCOSR */
	hws[IMX6UL_CLK_CKO1]		= imx_clk_hw_gate("cko1",		"cko1_podf",	 base + 0x60,	7);
	hws[IMX6UL_CLK_CKO2]		= imx_clk_hw_gate("cko2",		"cko2_podf",	 base + 0x60,	24);

	/* mask handshake of mmdc */
	imx_mmdc_mask_handshake(base, 0);

	imx_check_clk_hws(hws, IMX6UL_CLK_END);

	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_hw_data);

	/*
	 * Lower the AHB घड़ी rate beक्रमe changing the parent घड़ी source,
	 * as AHB घड़ी rate can NOT be higher than 133MHz, but its parent
	 * will be चयनed from 396MHz PFD to 528MHz PLL in order to increase
	 * AXI घड़ी rate, so we need to lower AHB rate first to make sure at
	 * any समय, AHB rate is <= 133MHz.
	 */
	clk_set_rate(hws[IMX6UL_CLK_AHB]->clk, 99000000);

	/* Change periph_pre घड़ी to pll2_bus to adjust AXI rate to 264MHz */
	clk_set_parent(hws[IMX6UL_CLK_PERIPH_CLK2_SEL]->clk, hws[IMX6UL_CLK_OSC]->clk);
	clk_set_parent(hws[IMX6UL_CLK_PERIPH]->clk, hws[IMX6UL_CLK_PERIPH_CLK2]->clk);
	clk_set_parent(hws[IMX6UL_CLK_PERIPH_PRE]->clk, hws[IMX6UL_CLK_PLL2_BUS]->clk);
	clk_set_parent(hws[IMX6UL_CLK_PERIPH]->clk, hws[IMX6UL_CLK_PERIPH_PRE]->clk);

	/* Make sure AHB rate is 132MHz  */
	clk_set_rate(hws[IMX6UL_CLK_AHB]->clk, 132000000);

	/* set perclk to from OSC */
	clk_set_parent(hws[IMX6UL_CLK_PERCLK_SEL]->clk, hws[IMX6UL_CLK_OSC]->clk);

	clk_set_rate(hws[IMX6UL_CLK_ENET_REF]->clk, 50000000);
	clk_set_rate(hws[IMX6UL_CLK_ENET2_REF]->clk, 50000000);
	clk_set_rate(hws[IMX6UL_CLK_CSI]->clk, 24000000);

	अगर (clk_on_imx6ull())
		clk_prepare_enable(hws[IMX6UL_CLK_AIPSTZ3]->clk);

	अगर (IS_ENABLED(CONFIG_USB_MXS_PHY)) अणु
		clk_prepare_enable(hws[IMX6UL_CLK_USBPHY1_GATE]->clk);
		clk_prepare_enable(hws[IMX6UL_CLK_USBPHY2_GATE]->clk);
	पूर्ण

	clk_set_parent(hws[IMX6UL_CLK_CAN_SEL]->clk, hws[IMX6UL_CLK_PLL3_80M]->clk);
	अगर (clk_on_imx6ul())
		clk_set_parent(hws[IMX6UL_CLK_SIM_PRE_SEL]->clk, hws[IMX6UL_CLK_PLL3_USB_OTG]->clk);
	अन्यथा अगर (clk_on_imx6ull())
		clk_set_parent(hws[IMX6ULL_CLK_EPDC_PRE_SEL]->clk, hws[IMX6UL_CLK_PLL3_PFD2]->clk);

	clk_set_parent(hws[IMX6UL_CLK_ENFC_SEL]->clk, hws[IMX6UL_CLK_PLL2_PFD2]->clk);
पूर्ण

CLK_OF_DECLARE(imx6ul, "fsl,imx6ul-ccm", imx6ul_घड़ीs_init);
