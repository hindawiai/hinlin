<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012-2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/of_address.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/syscore_ops.h>
#समावेश <dt-bindings/घड़ी/vf610-घड़ी.h>

#समावेश "clk.h"

#घोषणा CCM_CCR			(ccm_base + 0x00)
#घोषणा CCM_CSR			(ccm_base + 0x04)
#घोषणा CCM_CCSR		(ccm_base + 0x08)
#घोषणा CCM_CACRR		(ccm_base + 0x0c)
#घोषणा CCM_CSCMR1		(ccm_base + 0x10)
#घोषणा CCM_CSCDR1		(ccm_base + 0x14)
#घोषणा CCM_CSCDR2		(ccm_base + 0x18)
#घोषणा CCM_CSCDR3		(ccm_base + 0x1c)
#घोषणा CCM_CSCMR2		(ccm_base + 0x20)
#घोषणा CCM_CSCDR4		(ccm_base + 0x24)
#घोषणा CCM_CLPCR		(ccm_base + 0x2c)
#घोषणा CCM_CISR		(ccm_base + 0x30)
#घोषणा CCM_CIMR		(ccm_base + 0x34)
#घोषणा CCM_CGPR		(ccm_base + 0x3c)
#घोषणा CCM_CCGR0		(ccm_base + 0x40)
#घोषणा CCM_CCGR1		(ccm_base + 0x44)
#घोषणा CCM_CCGR2		(ccm_base + 0x48)
#घोषणा CCM_CCGR3		(ccm_base + 0x4c)
#घोषणा CCM_CCGR4		(ccm_base + 0x50)
#घोषणा CCM_CCGR5		(ccm_base + 0x54)
#घोषणा CCM_CCGR6		(ccm_base + 0x58)
#घोषणा CCM_CCGR7		(ccm_base + 0x5c)
#घोषणा CCM_CCGR8		(ccm_base + 0x60)
#घोषणा CCM_CCGR9		(ccm_base + 0x64)
#घोषणा CCM_CCGR10		(ccm_base + 0x68)
#घोषणा CCM_CCGR11		(ccm_base + 0x6c)
#घोषणा CCM_CCGRx(x)		(CCM_CCGR0 + (x) * 4)
#घोषणा CCM_CMEOR0		(ccm_base + 0x70)
#घोषणा CCM_CMEOR1		(ccm_base + 0x74)
#घोषणा CCM_CMEOR2		(ccm_base + 0x78)
#घोषणा CCM_CMEOR3		(ccm_base + 0x7c)
#घोषणा CCM_CMEOR4		(ccm_base + 0x80)
#घोषणा CCM_CMEOR5		(ccm_base + 0x84)
#घोषणा CCM_CPPDSR		(ccm_base + 0x88)
#घोषणा CCM_CCOWR		(ccm_base + 0x8c)
#घोषणा CCM_CCPGR0		(ccm_base + 0x90)
#घोषणा CCM_CCPGR1		(ccm_base + 0x94)
#घोषणा CCM_CCPGR2		(ccm_base + 0x98)
#घोषणा CCM_CCPGR3		(ccm_base + 0x9c)

#घोषणा CCM_CCGRx_CGn(n)	((n) * 2)

#घोषणा PFD_PLL1_BASE		(anatop_base + 0x2b0)
#घोषणा PFD_PLL2_BASE		(anatop_base + 0x100)
#घोषणा PFD_PLL3_BASE		(anatop_base + 0xf0)
#घोषणा PLL1_CTRL		(anatop_base + 0x270)
#घोषणा PLL2_CTRL		(anatop_base + 0x30)
#घोषणा PLL3_CTRL		(anatop_base + 0x10)
#घोषणा PLL4_CTRL		(anatop_base + 0x70)
#घोषणा PLL5_CTRL		(anatop_base + 0xe0)
#घोषणा PLL6_CTRL		(anatop_base + 0xa0)
#घोषणा PLL7_CTRL		(anatop_base + 0x20)
#घोषणा ANA_MISC1		(anatop_base + 0x160)

अटल व्योम __iomem *anatop_base;
अटल व्योम __iomem *ccm_base;

/* sources क्रम multiplexer घड़ीs, this is used multiple बार */
अटल स्थिर अक्षर *fast_sels[]	= अणु "firc", "fxosc", पूर्ण;
अटल स्थिर अक्षर *slow_sels[]	= अणु "sirc_32k", "sxosc", पूर्ण;
अटल स्थिर अक्षर *pll1_sels[]	= अणु "pll1_sys", "pll1_pfd1", "pll1_pfd2", "pll1_pfd3", "pll1_pfd4", पूर्ण;
अटल स्थिर अक्षर *pll2_sels[]	= अणु "pll2_bus", "pll2_pfd1", "pll2_pfd2", "pll2_pfd3", "pll2_pfd4", पूर्ण;
अटल स्थिर अक्षर *pll_bypass_src_sels[] = अणु "fast_clk_sel", "lvds1_in", पूर्ण;
अटल स्थिर अक्षर *pll1_bypass_sels[] = अणु "pll1", "pll1_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll2_bypass_sels[] = अणु "pll2", "pll2_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll3_bypass_sels[] = अणु "pll3", "pll3_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll4_bypass_sels[] = अणु "pll4", "pll4_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll5_bypass_sels[] = अणु "pll5", "pll5_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll6_bypass_sels[] = अणु "pll6", "pll6_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll7_bypass_sels[] = अणु "pll7", "pll7_bypass_src", पूर्ण;
अटल स्थिर अक्षर *sys_sels[]	= अणु "fast_clk_sel", "slow_clk_sel", "pll2_pfd_sel", "pll2_bus", "pll1_pfd_sel", "pll3_usb_otg", पूर्ण;
अटल स्थिर अक्षर *ddr_sels[]	= अणु "pll2_pfd2", "sys_sel", पूर्ण;
अटल स्थिर अक्षर *rmii_sels[]	= अणु "enet_ext", "audio_ext", "enet_50m", "enet_25m", पूर्ण;
अटल स्थिर अक्षर *enet_ts_sels[]	= अणु "enet_ext", "fxosc", "audio_ext", "usb", "enet_ts", "enet_25m", "enet_50m", पूर्ण;
अटल स्थिर अक्षर *esai_sels[]	= अणु "audio_ext", "mlb", "spdif_rx", "pll4_audio_div", पूर्ण;
अटल स्थिर अक्षर *sai_sels[]	= अणु "audio_ext", "mlb", "spdif_rx", "pll4_audio_div", पूर्ण;
अटल स्थिर अक्षर *nfc_sels[]	= अणु "platform_bus", "pll1_pfd1", "pll3_pfd1", "pll3_pfd3", पूर्ण;
अटल स्थिर अक्षर *qspi_sels[]	= अणु "pll3_usb_otg", "pll3_pfd4", "pll2_pfd4", "pll1_pfd4", पूर्ण;
अटल स्थिर अक्षर *esdhc_sels[]	= अणु "pll3_usb_otg", "pll3_pfd3", "pll1_pfd3", "platform_bus", पूर्ण;
अटल स्थिर अक्षर *dcu_sels[]	= अणु "pll1_pfd2", "pll3_usb_otg", पूर्ण;
अटल स्थिर अक्षर *gpu_sels[]	= अणु "pll2_pfd2", "pll3_pfd2", पूर्ण;
अटल स्थिर अक्षर *vadc_sels[]	= अणु "pll6_video_div", "pll3_usb_otg_div", "pll3_usb_otg", पूर्ण;
/* FTM counter घड़ी source, not module घड़ी */
अटल स्थिर अक्षर *fपंचांग_ext_sels[]	= अणु"sirc_128k", "sxosc", "fxosc_half", "audio_ext", पूर्ण;
अटल स्थिर अक्षर *fपंचांग_fix_sels[]	= अणु "sxosc", "ipg_bus", पूर्ण;


अटल स्थिर काष्ठा clk_भाग_प्रकारable pll4_audio_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 6 पूर्ण,
	अणु .val = 3, .भाग = 8 पूर्ण,
	अणु .val = 4, .भाग = 10 पूर्ण,
	अणु .val = 5, .भाग = 12 पूर्ण,
	अणु .val = 6, .भाग = 14 पूर्ण,
	अणु .val = 7, .भाग = 16 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा clk *clk[VF610_CLK_END];
अटल काष्ठा clk_onecell_data clk_data;

अटल u32 cscmr1;
अटल u32 cscmr2;
अटल u32 cscdr1;
अटल u32 cscdr2;
अटल u32 cscdr3;
अटल u32 ccgr[12];

अटल अचिन्हित पूर्णांक स्थिर clks_init_on[] __initस्थिर = अणु
	VF610_CLK_SYS_BUS,
	VF610_CLK_DDR_SEL,
	VF610_CLK_DAP,
	VF610_CLK_DDRMC,
	VF610_CLK_WKPU,
पूर्ण;

अटल काष्ठा clk * __init vf610_get_fixed_घड़ी(
				काष्ठा device_node *ccm_node, स्थिर अक्षर *name)
अणु
	काष्ठा clk *clk = of_clk_get_by_name(ccm_node, name);

	/* Backward compatibility अगर device tree is missing clks assignments */
	अगर (IS_ERR(clk))
		clk = imx_obtain_fixed_घड़ी(name, 0);
	वापस clk;
पूर्ण;

अटल पूर्णांक vf610_clk_suspend(व्योम)
अणु
	पूर्णांक i;

	cscmr1 = पढ़ोl_relaxed(CCM_CSCMR1);
	cscmr2 = पढ़ोl_relaxed(CCM_CSCMR2);

	cscdr1 = पढ़ोl_relaxed(CCM_CSCDR1);
	cscdr2 = पढ़ोl_relaxed(CCM_CSCDR2);
	cscdr3 = पढ़ोl_relaxed(CCM_CSCDR3);

	क्रम (i = 0; i < 12; i++)
		ccgr[i] = पढ़ोl_relaxed(CCM_CCGRx(i));

	वापस 0;
पूर्ण

अटल व्योम vf610_clk_resume(व्योम)
अणु
	पूर्णांक i;

	ग_लिखोl_relaxed(cscmr1, CCM_CSCMR1);
	ग_लिखोl_relaxed(cscmr2, CCM_CSCMR2);

	ग_लिखोl_relaxed(cscdr1, CCM_CSCDR1);
	ग_लिखोl_relaxed(cscdr2, CCM_CSCDR2);
	ग_लिखोl_relaxed(cscdr3, CCM_CSCDR3);

	क्रम (i = 0; i < 12; i++)
		ग_लिखोl_relaxed(ccgr[i], CCM_CCGRx(i));
पूर्ण

अटल काष्ठा syscore_ops vf610_clk_syscore_ops = अणु
	.suspend = vf610_clk_suspend,
	.resume = vf610_clk_resume,
पूर्ण;

अटल व्योम __init vf610_घड़ीs_init(काष्ठा device_node *ccm_node)
अणु
	काष्ठा device_node *np;
	पूर्णांक i;

	clk[VF610_CLK_DUMMY] = imx_clk_fixed("dummy", 0);
	clk[VF610_CLK_SIRC_128K] = imx_clk_fixed("sirc_128k", 128000);
	clk[VF610_CLK_SIRC_32K] = imx_clk_fixed("sirc_32k", 32000);
	clk[VF610_CLK_FIRC] = imx_clk_fixed("firc", 24000000);

	clk[VF610_CLK_SXOSC] = vf610_get_fixed_घड़ी(ccm_node, "sxosc");
	clk[VF610_CLK_FXOSC] = vf610_get_fixed_घड़ी(ccm_node, "fxosc");
	clk[VF610_CLK_AUDIO_EXT] = vf610_get_fixed_घड़ी(ccm_node, "audio_ext");
	clk[VF610_CLK_ENET_EXT] = vf610_get_fixed_घड़ी(ccm_node, "enet_ext");

	/* Clock source from बाह्यal घड़ी via LVDs PAD */
	clk[VF610_CLK_ANACLK1] = vf610_get_fixed_घड़ी(ccm_node, "anaclk1");

	clk[VF610_CLK_FXOSC_HALF] = imx_clk_fixed_factor("fxosc_half", "fxosc", 1, 2);

	np = of_find_compatible_node(शून्य, शून्य, "fsl,vf610-anatop");
	anatop_base = of_iomap(np, 0);
	BUG_ON(!anatop_base);
	of_node_put(np);

	np = ccm_node;
	ccm_base = of_iomap(np, 0);
	BUG_ON(!ccm_base);

	clk[VF610_CLK_SLOW_CLK_SEL] = imx_clk_mux("slow_clk_sel", CCM_CCSR, 4, 1, slow_sels, ARRAY_SIZE(slow_sels));
	clk[VF610_CLK_FASK_CLK_SEL] = imx_clk_mux("fast_clk_sel", CCM_CCSR, 5, 1, fast_sels, ARRAY_SIZE(fast_sels));

	clk[VF610_CLK_PLL1_BYPASS_SRC] = imx_clk_mux("pll1_bypass_src", PLL1_CTRL, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	clk[VF610_CLK_PLL2_BYPASS_SRC] = imx_clk_mux("pll2_bypass_src", PLL2_CTRL, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	clk[VF610_CLK_PLL3_BYPASS_SRC] = imx_clk_mux("pll3_bypass_src", PLL3_CTRL, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	clk[VF610_CLK_PLL4_BYPASS_SRC] = imx_clk_mux("pll4_bypass_src", PLL4_CTRL, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	clk[VF610_CLK_PLL5_BYPASS_SRC] = imx_clk_mux("pll5_bypass_src", PLL5_CTRL, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	clk[VF610_CLK_PLL6_BYPASS_SRC] = imx_clk_mux("pll6_bypass_src", PLL6_CTRL, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	clk[VF610_CLK_PLL7_BYPASS_SRC] = imx_clk_mux("pll7_bypass_src", PLL7_CTRL, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));

	clk[VF610_CLK_PLL1] = imx_clk_pllv3(IMX_PLLV3_SYS_VF610, "pll1", "pll1_bypass_src", PLL1_CTRL, 0x1);
	clk[VF610_CLK_PLL2] = imx_clk_pllv3(IMX_PLLV3_SYS_VF610, "pll2", "pll2_bypass_src", PLL2_CTRL, 0x1);
	clk[VF610_CLK_PLL3] = imx_clk_pllv3(IMX_PLLV3_USB_VF610,     "pll3", "pll3_bypass_src", PLL3_CTRL, 0x2);
	clk[VF610_CLK_PLL4] = imx_clk_pllv3(IMX_PLLV3_AV,      "pll4", "pll4_bypass_src", PLL4_CTRL, 0x7f);
	clk[VF610_CLK_PLL5] = imx_clk_pllv3(IMX_PLLV3_ENET,    "pll5", "pll5_bypass_src", PLL5_CTRL, 0x3);
	clk[VF610_CLK_PLL6] = imx_clk_pllv3(IMX_PLLV3_AV,      "pll6", "pll6_bypass_src", PLL6_CTRL, 0x7f);
	clk[VF610_CLK_PLL7] = imx_clk_pllv3(IMX_PLLV3_USB_VF610,     "pll7", "pll7_bypass_src", PLL7_CTRL, 0x2);

	clk[VF610_PLL1_BYPASS] = imx_clk_mux_flags("pll1_bypass", PLL1_CTRL, 16, 1, pll1_bypass_sels, ARRAY_SIZE(pll1_bypass_sels), CLK_SET_RATE_PARENT);
	clk[VF610_PLL2_BYPASS] = imx_clk_mux_flags("pll2_bypass", PLL2_CTRL, 16, 1, pll2_bypass_sels, ARRAY_SIZE(pll2_bypass_sels), CLK_SET_RATE_PARENT);
	clk[VF610_PLL3_BYPASS] = imx_clk_mux_flags("pll3_bypass", PLL3_CTRL, 16, 1, pll3_bypass_sels, ARRAY_SIZE(pll3_bypass_sels), CLK_SET_RATE_PARENT);
	clk[VF610_PLL4_BYPASS] = imx_clk_mux_flags("pll4_bypass", PLL4_CTRL, 16, 1, pll4_bypass_sels, ARRAY_SIZE(pll4_bypass_sels), CLK_SET_RATE_PARENT);
	clk[VF610_PLL5_BYPASS] = imx_clk_mux_flags("pll5_bypass", PLL5_CTRL, 16, 1, pll5_bypass_sels, ARRAY_SIZE(pll5_bypass_sels), CLK_SET_RATE_PARENT);
	clk[VF610_PLL6_BYPASS] = imx_clk_mux_flags("pll6_bypass", PLL6_CTRL, 16, 1, pll6_bypass_sels, ARRAY_SIZE(pll6_bypass_sels), CLK_SET_RATE_PARENT);
	clk[VF610_PLL7_BYPASS] = imx_clk_mux_flags("pll7_bypass", PLL7_CTRL, 16, 1, pll7_bypass_sels, ARRAY_SIZE(pll7_bypass_sels), CLK_SET_RATE_PARENT);

	/* Do not bypass PLLs initially */
	clk_set_parent(clk[VF610_PLL1_BYPASS], clk[VF610_CLK_PLL1]);
	clk_set_parent(clk[VF610_PLL2_BYPASS], clk[VF610_CLK_PLL2]);
	clk_set_parent(clk[VF610_PLL3_BYPASS], clk[VF610_CLK_PLL3]);
	clk_set_parent(clk[VF610_PLL4_BYPASS], clk[VF610_CLK_PLL4]);
	clk_set_parent(clk[VF610_PLL5_BYPASS], clk[VF610_CLK_PLL5]);
	clk_set_parent(clk[VF610_PLL6_BYPASS], clk[VF610_CLK_PLL6]);
	clk_set_parent(clk[VF610_PLL7_BYPASS], clk[VF610_CLK_PLL7]);

	clk[VF610_CLK_PLL1_SYS]      = imx_clk_gate("pll1_sys",      "pll1_bypass", PLL1_CTRL, 13);
	clk[VF610_CLK_PLL2_BUS]      = imx_clk_gate("pll2_bus",      "pll2_bypass", PLL2_CTRL, 13);
	clk[VF610_CLK_PLL3_USB_OTG]  = imx_clk_gate("pll3_usb_otg",  "pll3_bypass", PLL3_CTRL, 13);
	clk[VF610_CLK_PLL4_AUDIO]    = imx_clk_gate("pll4_audio",    "pll4_bypass", PLL4_CTRL, 13);
	clk[VF610_CLK_PLL5_ENET]     = imx_clk_gate("pll5_enet",     "pll5_bypass", PLL5_CTRL, 13);
	clk[VF610_CLK_PLL6_VIDEO]    = imx_clk_gate("pll6_video",    "pll6_bypass", PLL6_CTRL, 13);
	clk[VF610_CLK_PLL7_USB_HOST] = imx_clk_gate("pll7_usb_host", "pll7_bypass", PLL7_CTRL, 13);

	clk[VF610_CLK_LVDS1_IN]  = imx_clk_gate_exclusive("lvds1_in", "anaclk1", ANA_MISC1, 12, BIT(10));

	clk[VF610_CLK_PLL1_PFD1] = imx_clk_pfd("pll1_pfd1", "pll1_sys", PFD_PLL1_BASE, 0);
	clk[VF610_CLK_PLL1_PFD2] = imx_clk_pfd("pll1_pfd2", "pll1_sys", PFD_PLL1_BASE, 1);
	clk[VF610_CLK_PLL1_PFD3] = imx_clk_pfd("pll1_pfd3", "pll1_sys", PFD_PLL1_BASE, 2);
	clk[VF610_CLK_PLL1_PFD4] = imx_clk_pfd("pll1_pfd4", "pll1_sys", PFD_PLL1_BASE, 3);

	clk[VF610_CLK_PLL2_PFD1] = imx_clk_pfd("pll2_pfd1", "pll2_bus", PFD_PLL2_BASE, 0);
	clk[VF610_CLK_PLL2_PFD2] = imx_clk_pfd("pll2_pfd2", "pll2_bus", PFD_PLL2_BASE, 1);
	clk[VF610_CLK_PLL2_PFD3] = imx_clk_pfd("pll2_pfd3", "pll2_bus", PFD_PLL2_BASE, 2);
	clk[VF610_CLK_PLL2_PFD4] = imx_clk_pfd("pll2_pfd4", "pll2_bus", PFD_PLL2_BASE, 3);

	clk[VF610_CLK_PLL3_PFD1] = imx_clk_pfd("pll3_pfd1", "pll3_usb_otg", PFD_PLL3_BASE, 0);
	clk[VF610_CLK_PLL3_PFD2] = imx_clk_pfd("pll3_pfd2", "pll3_usb_otg", PFD_PLL3_BASE, 1);
	clk[VF610_CLK_PLL3_PFD3] = imx_clk_pfd("pll3_pfd3", "pll3_usb_otg", PFD_PLL3_BASE, 2);
	clk[VF610_CLK_PLL3_PFD4] = imx_clk_pfd("pll3_pfd4", "pll3_usb_otg", PFD_PLL3_BASE, 3);

	clk[VF610_CLK_PLL1_PFD_SEL] = imx_clk_mux("pll1_pfd_sel", CCM_CCSR, 16, 3, pll1_sels, 5);
	clk[VF610_CLK_PLL2_PFD_SEL] = imx_clk_mux("pll2_pfd_sel", CCM_CCSR, 19, 3, pll2_sels, 5);
	clk[VF610_CLK_SYS_SEL] = imx_clk_mux("sys_sel", CCM_CCSR, 0, 3, sys_sels, ARRAY_SIZE(sys_sels));
	clk[VF610_CLK_DDR_SEL] = imx_clk_mux("ddr_sel", CCM_CCSR, 6, 1, ddr_sels, ARRAY_SIZE(ddr_sels));
	clk[VF610_CLK_SYS_BUS] = imx_clk_भागider("sys_bus", "sys_sel", CCM_CACRR, 0, 3);
	clk[VF610_CLK_PLATFORM_BUS] = imx_clk_भागider("platform_bus", "sys_bus", CCM_CACRR, 3, 3);
	clk[VF610_CLK_IPG_BUS] = imx_clk_भागider("ipg_bus", "platform_bus", CCM_CACRR, 11, 2);

	clk[VF610_CLK_PLL3_MAIN_DIV] = imx_clk_भागider("pll3_usb_otg_div", "pll3_usb_otg", CCM_CACRR, 20, 1);
	clk[VF610_CLK_PLL4_MAIN_DIV] = clk_रेजिस्टर_भागider_table(शून्य, "pll4_audio_div", "pll4_audio", 0, CCM_CACRR, 6, 3, 0, pll4_audio_भाग_प्रकारable, &imx_ccm_lock);
	clk[VF610_CLK_PLL6_MAIN_DIV] = imx_clk_भागider("pll6_video_div", "pll6_video", CCM_CACRR, 21, 1);

	clk[VF610_CLK_DDRMC] = imx_clk_gate2_cgr("ddrmc", "ddr_sel", CCM_CCGR6, CCM_CCGRx_CGn(14), 0x2);
	clk[VF610_CLK_WKPU] = imx_clk_gate2_cgr("wkpu", "ipg_bus", CCM_CCGR4, CCM_CCGRx_CGn(10), 0x2);

	clk[VF610_CLK_USBPHY0] = imx_clk_gate("usbphy0", "pll3_usb_otg", PLL3_CTRL, 6);
	clk[VF610_CLK_USBPHY1] = imx_clk_gate("usbphy1", "pll7_usb_host", PLL7_CTRL, 6);

	clk[VF610_CLK_USBC0] = imx_clk_gate2("usbc0", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(4));
	clk[VF610_CLK_USBC1] = imx_clk_gate2("usbc1", "ipg_bus", CCM_CCGR7, CCM_CCGRx_CGn(4));

	clk[VF610_CLK_QSPI0_SEL] = imx_clk_mux("qspi0_sel", CCM_CSCMR1, 22, 2, qspi_sels, 4);
	clk[VF610_CLK_QSPI0_EN] = imx_clk_gate("qspi0_en", "qspi0_sel", CCM_CSCDR3, 4);
	clk[VF610_CLK_QSPI0_X4_DIV] = imx_clk_भागider("qspi0_x4", "qspi0_en", CCM_CSCDR3, 0, 2);
	clk[VF610_CLK_QSPI0_X2_DIV] = imx_clk_भागider("qspi0_x2", "qspi0_x4", CCM_CSCDR3, 2, 1);
	clk[VF610_CLK_QSPI0_X1_DIV] = imx_clk_भागider("qspi0_x1", "qspi0_x2", CCM_CSCDR3, 3, 1);
	clk[VF610_CLK_QSPI0] = imx_clk_gate2("qspi0", "qspi0_x1", CCM_CCGR2, CCM_CCGRx_CGn(4));

	clk[VF610_CLK_QSPI1_SEL] = imx_clk_mux("qspi1_sel", CCM_CSCMR1, 24, 2, qspi_sels, 4);
	clk[VF610_CLK_QSPI1_EN] = imx_clk_gate("qspi1_en", "qspi1_sel", CCM_CSCDR3, 12);
	clk[VF610_CLK_QSPI1_X4_DIV] = imx_clk_भागider("qspi1_x4", "qspi1_en", CCM_CSCDR3, 8, 2);
	clk[VF610_CLK_QSPI1_X2_DIV] = imx_clk_भागider("qspi1_x2", "qspi1_x4", CCM_CSCDR3, 10, 1);
	clk[VF610_CLK_QSPI1_X1_DIV] = imx_clk_भागider("qspi1_x1", "qspi1_x2", CCM_CSCDR3, 11, 1);
	clk[VF610_CLK_QSPI1] = imx_clk_gate2("qspi1", "qspi1_x1", CCM_CCGR8, CCM_CCGRx_CGn(4));

	clk[VF610_CLK_ENET_50M] = imx_clk_fixed_factor("enet_50m", "pll5_enet", 1, 10);
	clk[VF610_CLK_ENET_25M] = imx_clk_fixed_factor("enet_25m", "pll5_enet", 1, 20);
	clk[VF610_CLK_ENET_SEL] = imx_clk_mux("enet_sel", CCM_CSCMR2, 4, 2, rmii_sels, 4);
	clk[VF610_CLK_ENET_TS_SEL] = imx_clk_mux("enet_ts_sel", CCM_CSCMR2, 0, 3, enet_ts_sels, 7);
	clk[VF610_CLK_ENET] = imx_clk_gate("enet", "enet_sel", CCM_CSCDR1, 24);
	clk[VF610_CLK_ENET_TS] = imx_clk_gate("enet_ts", "enet_ts_sel", CCM_CSCDR1, 23);
	clk[VF610_CLK_ENET0] = imx_clk_gate2("enet0", "ipg_bus", CCM_CCGR9, CCM_CCGRx_CGn(0));
	clk[VF610_CLK_ENET1] = imx_clk_gate2("enet1", "ipg_bus", CCM_CCGR9, CCM_CCGRx_CGn(1));

	clk[VF610_CLK_PIT] = imx_clk_gate2("pit", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(7));

	clk[VF610_CLK_UART0] = imx_clk_gate2_cgr("uart0", "ipg_bus", CCM_CCGR0, CCM_CCGRx_CGn(7), 0x2);
	clk[VF610_CLK_UART1] = imx_clk_gate2_cgr("uart1", "ipg_bus", CCM_CCGR0, CCM_CCGRx_CGn(8), 0x2);
	clk[VF610_CLK_UART2] = imx_clk_gate2_cgr("uart2", "ipg_bus", CCM_CCGR0, CCM_CCGRx_CGn(9), 0x2);
	clk[VF610_CLK_UART3] = imx_clk_gate2_cgr("uart3", "ipg_bus", CCM_CCGR0, CCM_CCGRx_CGn(10), 0x2);
	clk[VF610_CLK_UART4] = imx_clk_gate2_cgr("uart4", "ipg_bus", CCM_CCGR6, CCM_CCGRx_CGn(9), 0x2);
	clk[VF610_CLK_UART5] = imx_clk_gate2_cgr("uart5", "ipg_bus", CCM_CCGR6, CCM_CCGRx_CGn(10), 0x2);

	clk[VF610_CLK_I2C0] = imx_clk_gate2("i2c0", "ipg_bus", CCM_CCGR4, CCM_CCGRx_CGn(6));
	clk[VF610_CLK_I2C1] = imx_clk_gate2("i2c1", "ipg_bus", CCM_CCGR4, CCM_CCGRx_CGn(7));
	clk[VF610_CLK_I2C2] = imx_clk_gate2("i2c2", "ipg_bus", CCM_CCGR10, CCM_CCGRx_CGn(6));
	clk[VF610_CLK_I2C3] = imx_clk_gate2("i2c3", "ipg_bus", CCM_CCGR10, CCM_CCGRx_CGn(7));

	clk[VF610_CLK_DSPI0] = imx_clk_gate2("dspi0", "ipg_bus", CCM_CCGR0, CCM_CCGRx_CGn(12));
	clk[VF610_CLK_DSPI1] = imx_clk_gate2("dspi1", "ipg_bus", CCM_CCGR0, CCM_CCGRx_CGn(13));
	clk[VF610_CLK_DSPI2] = imx_clk_gate2("dspi2", "ipg_bus", CCM_CCGR6, CCM_CCGRx_CGn(12));
	clk[VF610_CLK_DSPI3] = imx_clk_gate2("dspi3", "ipg_bus", CCM_CCGR6, CCM_CCGRx_CGn(13));

	clk[VF610_CLK_CRC] = imx_clk_gate2("crc", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(3));
	clk[VF610_CLK_WDT] = imx_clk_gate2("wdt", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(14));

	clk[VF610_CLK_ESDHC0_SEL] = imx_clk_mux("esdhc0_sel", CCM_CSCMR1, 16, 2, esdhc_sels, 4);
	clk[VF610_CLK_ESDHC0_EN] = imx_clk_gate("esdhc0_en", "esdhc0_sel", CCM_CSCDR2, 28);
	clk[VF610_CLK_ESDHC0_DIV] = imx_clk_भागider("esdhc0_div", "esdhc0_en", CCM_CSCDR2, 16, 4);
	clk[VF610_CLK_ESDHC0] = imx_clk_gate2("eshc0", "esdhc0_div", CCM_CCGR7, CCM_CCGRx_CGn(1));

	clk[VF610_CLK_ESDHC1_SEL] = imx_clk_mux("esdhc1_sel", CCM_CSCMR1, 18, 2, esdhc_sels, 4);
	clk[VF610_CLK_ESDHC1_EN] = imx_clk_gate("esdhc1_en", "esdhc1_sel", CCM_CSCDR2, 29);
	clk[VF610_CLK_ESDHC1_DIV] = imx_clk_भागider("esdhc1_div", "esdhc1_en", CCM_CSCDR2, 20, 4);
	clk[VF610_CLK_ESDHC1] = imx_clk_gate2("eshc1", "esdhc1_div", CCM_CCGR7, CCM_CCGRx_CGn(2));

	/*
	 * fपंचांग_ext_clk and fपंचांग_fix_clk are FTM समयr counter's
	 * selectable घड़ी sources, both use a common enable bit
	 * in CCM_CSCDR1, selecting "dummy" घड़ी as parent of
	 * "ftm0_ext_fix" make it serve only क्रम enable/disable.
	 */
	clk[VF610_CLK_FTM0_EXT_SEL] = imx_clk_mux("ftm0_ext_sel", CCM_CSCMR2, 6, 2, fपंचांग_ext_sels, 4);
	clk[VF610_CLK_FTM0_FIX_SEL] = imx_clk_mux("ftm0_fix_sel", CCM_CSCMR2, 14, 1, fपंचांग_fix_sels, 2);
	clk[VF610_CLK_FTM0_EXT_FIX_EN] = imx_clk_gate("ftm0_ext_fix_en", "dummy", CCM_CSCDR1, 25);
	clk[VF610_CLK_FTM1_EXT_SEL] = imx_clk_mux("ftm1_ext_sel", CCM_CSCMR2, 8, 2, fपंचांग_ext_sels, 4);
	clk[VF610_CLK_FTM1_FIX_SEL] = imx_clk_mux("ftm1_fix_sel", CCM_CSCMR2, 15, 1, fपंचांग_fix_sels, 2);
	clk[VF610_CLK_FTM1_EXT_FIX_EN] = imx_clk_gate("ftm1_ext_fix_en", "dummy", CCM_CSCDR1, 26);
	clk[VF610_CLK_FTM2_EXT_SEL] = imx_clk_mux("ftm2_ext_sel", CCM_CSCMR2, 10, 2, fपंचांग_ext_sels, 4);
	clk[VF610_CLK_FTM2_FIX_SEL] = imx_clk_mux("ftm2_fix_sel", CCM_CSCMR2, 16, 1, fपंचांग_fix_sels, 2);
	clk[VF610_CLK_FTM2_EXT_FIX_EN] = imx_clk_gate("ftm2_ext_fix_en", "dummy", CCM_CSCDR1, 27);
	clk[VF610_CLK_FTM3_EXT_SEL] = imx_clk_mux("ftm3_ext_sel", CCM_CSCMR2, 12, 2, fपंचांग_ext_sels, 4);
	clk[VF610_CLK_FTM3_FIX_SEL] = imx_clk_mux("ftm3_fix_sel", CCM_CSCMR2, 17, 1, fपंचांग_fix_sels, 2);
	clk[VF610_CLK_FTM3_EXT_FIX_EN] = imx_clk_gate("ftm3_ext_fix_en", "dummy", CCM_CSCDR1, 28);

	/* fपंचांग(n)_clk are FTM module operation घड़ी */
	clk[VF610_CLK_FTM0] = imx_clk_gate2("ftm0", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(8));
	clk[VF610_CLK_FTM1] = imx_clk_gate2("ftm1", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(9));
	clk[VF610_CLK_FTM2] = imx_clk_gate2("ftm2", "ipg_bus", CCM_CCGR7, CCM_CCGRx_CGn(8));
	clk[VF610_CLK_FTM3] = imx_clk_gate2("ftm3", "ipg_bus", CCM_CCGR7, CCM_CCGRx_CGn(9));

	clk[VF610_CLK_DCU0_SEL] = imx_clk_mux("dcu0_sel", CCM_CSCMR1, 28, 1, dcu_sels, 2);
	clk[VF610_CLK_DCU0_EN] = imx_clk_gate("dcu0_en", "dcu0_sel", CCM_CSCDR3, 19);
	clk[VF610_CLK_DCU0_DIV] = imx_clk_भागider("dcu0_div", "dcu0_en", CCM_CSCDR3, 16, 3);
	clk[VF610_CLK_DCU0] = imx_clk_gate2("dcu0", "ipg_bus", CCM_CCGR3, CCM_CCGRx_CGn(8));
	clk[VF610_CLK_DCU1_SEL] = imx_clk_mux("dcu1_sel", CCM_CSCMR1, 29, 1, dcu_sels, 2);
	clk[VF610_CLK_DCU1_EN] = imx_clk_gate("dcu1_en", "dcu1_sel", CCM_CSCDR3, 23);
	clk[VF610_CLK_DCU1_DIV] = imx_clk_भागider("dcu1_div", "dcu1_en", CCM_CSCDR3, 20, 3);
	clk[VF610_CLK_DCU1] = imx_clk_gate2("dcu1", "ipg_bus", CCM_CCGR9, CCM_CCGRx_CGn(8));

	clk[VF610_CLK_TCON0] = imx_clk_gate2("tcon0", "platform_bus", CCM_CCGR1, CCM_CCGRx_CGn(13));
	clk[VF610_CLK_TCON1] = imx_clk_gate2("tcon1", "platform_bus", CCM_CCGR7, CCM_CCGRx_CGn(13));

	clk[VF610_CLK_ESAI_SEL] = imx_clk_mux("esai_sel", CCM_CSCMR1, 20, 2, esai_sels, 4);
	clk[VF610_CLK_ESAI_EN] = imx_clk_gate("esai_en", "esai_sel", CCM_CSCDR2, 30);
	clk[VF610_CLK_ESAI_DIV] = imx_clk_भागider("esai_div", "esai_en", CCM_CSCDR2, 24, 4);
	clk[VF610_CLK_ESAI] = imx_clk_gate2("esai", "esai_div", CCM_CCGR4, CCM_CCGRx_CGn(2));

	clk[VF610_CLK_SAI0_SEL] = imx_clk_mux("sai0_sel", CCM_CSCMR1, 0, 2, sai_sels, 4);
	clk[VF610_CLK_SAI0_EN] = imx_clk_gate("sai0_en", "sai0_sel", CCM_CSCDR1, 16);
	clk[VF610_CLK_SAI0_DIV] = imx_clk_भागider("sai0_div", "sai0_en", CCM_CSCDR1, 0, 4);
	clk[VF610_CLK_SAI0] = imx_clk_gate2("sai0", "ipg_bus", CCM_CCGR0, CCM_CCGRx_CGn(15));

	clk[VF610_CLK_SAI1_SEL] = imx_clk_mux("sai1_sel", CCM_CSCMR1, 2, 2, sai_sels, 4);
	clk[VF610_CLK_SAI1_EN] = imx_clk_gate("sai1_en", "sai1_sel", CCM_CSCDR1, 17);
	clk[VF610_CLK_SAI1_DIV] = imx_clk_भागider("sai1_div", "sai1_en", CCM_CSCDR1, 4, 4);
	clk[VF610_CLK_SAI1] = imx_clk_gate2("sai1", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(0));

	clk[VF610_CLK_SAI2_SEL] = imx_clk_mux("sai2_sel", CCM_CSCMR1, 4, 2, sai_sels, 4);
	clk[VF610_CLK_SAI2_EN] = imx_clk_gate("sai2_en", "sai2_sel", CCM_CSCDR1, 18);
	clk[VF610_CLK_SAI2_DIV] = imx_clk_भागider("sai2_div", "sai2_en", CCM_CSCDR1, 8, 4);
	clk[VF610_CLK_SAI2] = imx_clk_gate2("sai2", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(1));

	clk[VF610_CLK_SAI3_SEL] = imx_clk_mux("sai3_sel", CCM_CSCMR1, 6, 2, sai_sels, 4);
	clk[VF610_CLK_SAI3_EN] = imx_clk_gate("sai3_en", "sai3_sel", CCM_CSCDR1, 19);
	clk[VF610_CLK_SAI3_DIV] = imx_clk_भागider("sai3_div", "sai3_en", CCM_CSCDR1, 12, 4);
	clk[VF610_CLK_SAI3] = imx_clk_gate2("sai3", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(2));

	clk[VF610_CLK_NFC_SEL] = imx_clk_mux("nfc_sel", CCM_CSCMR1, 12, 2, nfc_sels, 4);
	clk[VF610_CLK_NFC_EN] = imx_clk_gate("nfc_en", "nfc_sel", CCM_CSCDR2, 9);
	clk[VF610_CLK_NFC_PRE_DIV] = imx_clk_भागider("nfc_pre_div", "nfc_en", CCM_CSCDR3, 13, 3);
	clk[VF610_CLK_NFC_FRAC_DIV] = imx_clk_भागider("nfc_frac_div", "nfc_pre_div", CCM_CSCDR2, 4, 4);
	clk[VF610_CLK_NFC] = imx_clk_gate2("nfc", "nfc_frac_div", CCM_CCGR10, CCM_CCGRx_CGn(0));

	clk[VF610_CLK_GPU_SEL] = imx_clk_mux("gpu_sel", CCM_CSCMR1, 14, 1, gpu_sels, 2);
	clk[VF610_CLK_GPU_EN] = imx_clk_gate("gpu_en", "gpu_sel", CCM_CSCDR2, 10);
	clk[VF610_CLK_GPU2D] = imx_clk_gate2("gpu", "gpu_en", CCM_CCGR8, CCM_CCGRx_CGn(15));

	clk[VF610_CLK_VADC_SEL] = imx_clk_mux("vadc_sel", CCM_CSCMR1, 8, 2, vadc_sels, 3);
	clk[VF610_CLK_VADC_EN] = imx_clk_gate("vadc_en", "vadc_sel", CCM_CSCDR1, 22);
	clk[VF610_CLK_VADC_DIV] = imx_clk_भागider("vadc_div", "vadc_en", CCM_CSCDR1, 20, 2);
	clk[VF610_CLK_VADC_DIV_HALF] = imx_clk_fixed_factor("vadc_div_half", "vadc_div", 1, 2);
	clk[VF610_CLK_VADC] = imx_clk_gate2("vadc", "vadc_div", CCM_CCGR8, CCM_CCGRx_CGn(7));

	clk[VF610_CLK_ADC0] = imx_clk_gate2("adc0", "ipg_bus", CCM_CCGR1, CCM_CCGRx_CGn(11));
	clk[VF610_CLK_ADC1] = imx_clk_gate2("adc1", "ipg_bus", CCM_CCGR7, CCM_CCGRx_CGn(11));
	clk[VF610_CLK_DAC0] = imx_clk_gate2("dac0", "ipg_bus", CCM_CCGR8, CCM_CCGRx_CGn(12));
	clk[VF610_CLK_DAC1] = imx_clk_gate2("dac1", "ipg_bus", CCM_CCGR8, CCM_CCGRx_CGn(13));

	clk[VF610_CLK_ASRC] = imx_clk_gate2("asrc", "ipg_bus", CCM_CCGR4, CCM_CCGRx_CGn(1));

	clk[VF610_CLK_FLEXCAN0_EN] = imx_clk_gate("flexcan0_en", "ipg_bus", CCM_CSCDR2, 11);
	clk[VF610_CLK_FLEXCAN0] = imx_clk_gate2("flexcan0", "flexcan0_en", CCM_CCGR0, CCM_CCGRx_CGn(0));
	clk[VF610_CLK_FLEXCAN1_EN] = imx_clk_gate("flexcan1_en", "ipg_bus", CCM_CSCDR2, 12);
	clk[VF610_CLK_FLEXCAN1] = imx_clk_gate2("flexcan1", "flexcan1_en", CCM_CCGR9, CCM_CCGRx_CGn(4));

	clk[VF610_CLK_DMAMUX0] = imx_clk_gate2("dmamux0", "platform_bus", CCM_CCGR0, CCM_CCGRx_CGn(4));
	clk[VF610_CLK_DMAMUX1] = imx_clk_gate2("dmamux1", "platform_bus", CCM_CCGR0, CCM_CCGRx_CGn(5));
	clk[VF610_CLK_DMAMUX2] = imx_clk_gate2("dmamux2", "platform_bus", CCM_CCGR6, CCM_CCGRx_CGn(1));
	clk[VF610_CLK_DMAMUX3] = imx_clk_gate2("dmamux3", "platform_bus", CCM_CCGR6, CCM_CCGRx_CGn(2));

	clk[VF610_CLK_SNVS] = imx_clk_gate2("snvs-rtc", "ipg_bus", CCM_CCGR6, CCM_CCGRx_CGn(7));
	clk[VF610_CLK_DAP] = imx_clk_gate("dap", "platform_bus", CCM_CCSR, 24);
	clk[VF610_CLK_OCOTP] = imx_clk_gate("ocotp", "ipg_bus", CCM_CCGR6, CCM_CCGRx_CGn(5));
	clk[VF610_CLK_CAAM] = imx_clk_gate2("caam", "ipg_bus", CCM_CCGR11, CCM_CCGRx_CGn(0));

	imx_check_घड़ीs(clk, ARRAY_SIZE(clk));

	clk_set_parent(clk[VF610_CLK_QSPI0_SEL], clk[VF610_CLK_PLL1_PFD4]);
	clk_set_rate(clk[VF610_CLK_QSPI0_X4_DIV], clk_get_rate(clk[VF610_CLK_QSPI0_SEL]) / 2);
	clk_set_rate(clk[VF610_CLK_QSPI0_X2_DIV], clk_get_rate(clk[VF610_CLK_QSPI0_X4_DIV]) / 2);
	clk_set_rate(clk[VF610_CLK_QSPI0_X1_DIV], clk_get_rate(clk[VF610_CLK_QSPI0_X2_DIV]) / 2);

	clk_set_parent(clk[VF610_CLK_QSPI1_SEL], clk[VF610_CLK_PLL1_PFD4]);
	clk_set_rate(clk[VF610_CLK_QSPI1_X4_DIV], clk_get_rate(clk[VF610_CLK_QSPI1_SEL]) / 2);
	clk_set_rate(clk[VF610_CLK_QSPI1_X2_DIV], clk_get_rate(clk[VF610_CLK_QSPI1_X4_DIV]) / 2);
	clk_set_rate(clk[VF610_CLK_QSPI1_X1_DIV], clk_get_rate(clk[VF610_CLK_QSPI1_X2_DIV]) / 2);

	clk_set_parent(clk[VF610_CLK_SAI0_SEL], clk[VF610_CLK_AUDIO_EXT]);
	clk_set_parent(clk[VF610_CLK_SAI1_SEL], clk[VF610_CLK_AUDIO_EXT]);
	clk_set_parent(clk[VF610_CLK_SAI2_SEL], clk[VF610_CLK_AUDIO_EXT]);
	clk_set_parent(clk[VF610_CLK_SAI3_SEL], clk[VF610_CLK_AUDIO_EXT]);

	क्रम (i = 0; i < ARRAY_SIZE(clks_init_on); i++)
		clk_prepare_enable(clk[clks_init_on[i]]);

	रेजिस्टर_syscore_ops(&vf610_clk_syscore_ops);

	/* Add the घड़ीs to provider list */
	clk_data.clks = clk;
	clk_data.clk_num = ARRAY_SIZE(clk);
	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data);
पूर्ण
CLK_OF_DECLARE(vf610, "fsl,vf610-ccm", vf610_घड़ीs_init);
