<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013-2014 Freescale Semiconductor, Inc.
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/imx.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <dt-bindings/घड़ी/imx6sl-घड़ी.h>

#समावेश "clk.h"

#घोषणा CCSR			0xc
#घोषणा BM_CCSR_PLL1_SW_CLK_SEL	BIT(2)
#घोषणा CACRR			0x10
#घोषणा CDHIPR			0x48
#घोषणा BM_CDHIPR_ARM_PODF_BUSY	BIT(16)
#घोषणा ARM_WAIT_DIV_396M	2
#घोषणा ARM_WAIT_DIV_792M	4
#घोषणा ARM_WAIT_DIV_996M	6

#घोषणा PLL_ARM			0x0
#घोषणा BM_PLL_ARM_DIV_SELECT	0x7f
#घोषणा BM_PLL_ARM_POWERDOWN	BIT(12)
#घोषणा BM_PLL_ARM_ENABLE	BIT(13)
#घोषणा BM_PLL_ARM_LOCK		BIT(31)
#घोषणा PLL_ARM_DIV_792M	66

अटल स्थिर अक्षर *step_sels[]		= अणु "osc", "pll2_pfd2", पूर्ण;
अटल स्थिर अक्षर *pll1_sw_sels[]	= अणु "pll1_sys", "step", पूर्ण;
अटल स्थिर अक्षर *ocram_alt_sels[]	= अणु "pll2_pfd2", "pll3_pfd1", पूर्ण;
अटल स्थिर अक्षर *ocram_sels[]		= अणु "periph", "ocram_alt_sels", पूर्ण;
अटल स्थिर अक्षर *pre_periph_sels[]	= अणु "pll2_bus", "pll2_pfd2", "pll2_pfd0", "pll2_198m", पूर्ण;
अटल स्थिर अक्षर *periph_clk2_sels[]	= अणु "pll3_usb_otg", "osc", "osc", "dummy", पूर्ण;
अटल स्थिर अक्षर *periph2_clk2_sels[]	= अणु "pll3_usb_otg", "pll2_bus", पूर्ण;
अटल स्थिर अक्षर *periph_sels[]	= अणु "pre_periph_sel", "periph_clk2_podf", पूर्ण;
अटल स्थिर अक्षर *periph2_sels[]	= अणु "pre_periph2_sel", "periph2_clk2_podf", पूर्ण;
अटल स्थिर अक्षर *csi_sels[]		= अणु "osc", "pll2_pfd2", "pll3_120m", "pll3_pfd1", पूर्ण;
अटल स्थिर अक्षर *lcdअगर_axi_sels[]	= अणु "pll2_bus", "pll2_pfd2", "pll3_usb_otg", "pll3_pfd1", पूर्ण;
अटल स्थिर अक्षर *usdhc_sels[]		= अणु "pll2_pfd2", "pll2_pfd0", पूर्ण;
अटल स्थिर अक्षर *ssi_sels[]		= अणु "pll3_pfd2", "pll3_pfd3", "pll4_audio_div", "dummy", पूर्ण;
अटल स्थिर अक्षर *perclk_sels[]	= अणु "ipg", "osc", पूर्ण;
अटल स्थिर अक्षर *pxp_axi_sels[]	= अणु "pll2_bus", "pll3_usb_otg", "pll5_video_div", "pll2_pfd0", "pll2_pfd2", "pll3_pfd3", पूर्ण;
अटल स्थिर अक्षर *epdc_axi_sels[]	= अणु "pll2_bus", "pll3_usb_otg", "pll5_video_div", "pll2_pfd0", "pll2_pfd2", "pll3_pfd2", पूर्ण;
अटल स्थिर अक्षर *gpu2d_ovg_sels[]	= अणु "pll3_pfd1", "pll3_usb_otg", "pll2_bus", "pll2_pfd2", पूर्ण;
अटल स्थिर अक्षर *gpu2d_sels[]		= अणु "pll2_pfd2", "pll3_usb_otg", "pll3_pfd1", "pll2_bus", पूर्ण;
अटल स्थिर अक्षर *lcdअगर_pix_sels[]	= अणु "pll2_bus", "pll3_usb_otg", "pll5_video_div", "pll2_pfd0", "pll3_pfd0", "pll3_pfd1", पूर्ण;
अटल स्थिर अक्षर *epdc_pix_sels[]	= अणु "pll2_bus", "pll3_usb_otg", "pll5_video_div", "pll2_pfd0", "pll2_pfd1", "pll3_pfd1", पूर्ण;
अटल स्थिर अक्षर *audio_sels[]		= अणु "pll4_audio_div", "pll3_pfd2", "pll3_pfd3", "pll3_usb_otg", पूर्ण;
अटल स्थिर अक्षर *ecspi_sels[]		= अणु "pll3_60m", "osc", पूर्ण;
अटल स्थिर अक्षर *uart_sels[]		= अणु "pll3_80m", "osc", पूर्ण;
अटल स्थिर अक्षर *lvds_sels[]		= अणु
	"pll1_sys", "pll2_bus", "pll2_pfd0", "pll2_pfd1", "pll2_pfd2", "dummy", "pll4_audio", "pll5_video",
	"dummy", "enet_ref", "dummy", "dummy", "pll3_usb_otg", "pll7_usb_host", "pll3_pfd0", "pll3_pfd1",
	"pll3_pfd2", "pll3_pfd3", "osc", "dummy", "dummy", "dummy", "dummy", "dummy",
	 "dummy", "dummy", "dummy", "dummy", "dummy", "dummy", "dummy", "dummy",
पूर्ण;
अटल स्थिर अक्षर *pll_bypass_src_sels[] = अणु "osc", "lvds1_in", पूर्ण;
अटल स्थिर अक्षर *pll1_bypass_sels[]	= अणु "pll1", "pll1_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll2_bypass_sels[]	= अणु "pll2", "pll2_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll3_bypass_sels[]	= अणु "pll3", "pll3_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll4_bypass_sels[]	= अणु "pll4", "pll4_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll5_bypass_sels[]	= अणु "pll5", "pll5_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll6_bypass_sels[]	= अणु "pll6", "pll6_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll7_bypass_sels[]	= अणु "pll7", "pll7_bypass_src", पूर्ण;

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

अटल अचिन्हित पूर्णांक share_count_ssi1;
अटल अचिन्हित पूर्णांक share_count_ssi2;
अटल अचिन्हित पूर्णांक share_count_ssi3;
अटल अचिन्हित पूर्णांक share_count_spdअगर;

अटल काष्ठा clk_hw **hws;
अटल काष्ठा clk_hw_onecell_data *clk_hw_data;
अटल व्योम __iomem *ccm_base;
अटल व्योम __iomem *anatop_base;

/*
 * ERR005311 CCM: After निकास from WAIT mode, unwanted पूर्णांकerrupt(s) taken
 *           during WAIT mode entry process could cause cache memory
 *           corruption.
 *
 * Software workaround:
 *     To prevent this issue from occurring, software should ensure that the
 * ARM to IPG घड़ी ratio is less than 12:5 (that is < 2.4x), beक्रमe
 * entering WAIT mode.
 *
 * This function will set the ARM clk to max value within the 12:5 limit.
 * As IPG घड़ी is fixed at 66MHz(so ARM freq must not exceed 158.4MHz),
 * ARM freq are one of below setpoपूर्णांकs: 396MHz, 792MHz and 996MHz, since
 * the clk APIs can NOT be called in idle thपढ़ो(may cause kernel schedule
 * as there is sleep function in PLL रुको function), so here we just slow
 * करोwn ARM to below freq according to previous freq:
 *
 * run mode      रुको mode
 * 396MHz   ->   132MHz;
 * 792MHz   ->   158.4MHz;
 * 996MHz   ->   142.3MHz;
 */
अटल पूर्णांक imx6sl_get_arm_भागider_क्रम_रुको(व्योम)
अणु
	अगर (पढ़ोl_relaxed(ccm_base + CCSR) & BM_CCSR_PLL1_SW_CLK_SEL) अणु
		वापस ARM_WAIT_DIV_396M;
	पूर्ण अन्यथा अणु
		अगर ((पढ़ोl_relaxed(anatop_base + PLL_ARM) &
			BM_PLL_ARM_DIV_SELECT) == PLL_ARM_DIV_792M)
			वापस ARM_WAIT_DIV_792M;
		अन्यथा
			वापस ARM_WAIT_DIV_996M;
	पूर्ण
पूर्ण

अटल व्योम imx6sl_enable_pll_arm(bool enable)
अणु
	अटल u32 saved_pll_arm;
	u32 val;

	अगर (enable) अणु
		saved_pll_arm = val = पढ़ोl_relaxed(anatop_base + PLL_ARM);
		val |= BM_PLL_ARM_ENABLE;
		val &= ~BM_PLL_ARM_POWERDOWN;
		ग_लिखोl_relaxed(val, anatop_base + PLL_ARM);
		जबतक (!(पढ़ोl_relaxed(anatop_base + PLL_ARM) & BM_PLL_ARM_LOCK))
			;
	पूर्ण अन्यथा अणु
		 ग_लिखोl_relaxed(saved_pll_arm, anatop_base + PLL_ARM);
	पूर्ण
पूर्ण

व्योम imx6sl_set_रुको_clk(bool enter)
अणु
	अटल अचिन्हित दीर्घ saved_arm_भाग;
	पूर्णांक arm_भाग_क्रम_रुको = imx6sl_get_arm_भागider_क्रम_रुको();

	/*
	 * According to hardware design, arm podf change need
	 * PLL1 घड़ी enabled.
	 */
	अगर (arm_भाग_क्रम_रुको == ARM_WAIT_DIV_396M)
		imx6sl_enable_pll_arm(true);

	अगर (enter) अणु
		saved_arm_भाग = पढ़ोl_relaxed(ccm_base + CACRR);
		ग_लिखोl_relaxed(arm_भाग_क्रम_रुको, ccm_base + CACRR);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(saved_arm_भाग, ccm_base + CACRR);
	पूर्ण
	जबतक (__raw_पढ़ोl(ccm_base + CDHIPR) & BM_CDHIPR_ARM_PODF_BUSY)
		;

	अगर (arm_भाग_क्रम_रुको == ARM_WAIT_DIV_396M)
		imx6sl_enable_pll_arm(false);
पूर्ण

अटल व्योम __init imx6sl_घड़ीs_init(काष्ठा device_node *ccm_node)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *base;
	पूर्णांक ret;

	clk_hw_data = kzalloc(काष्ठा_size(clk_hw_data, hws,
					  IMX6SL_CLK_END), GFP_KERNEL);
	अगर (WARN_ON(!clk_hw_data))
		वापस;

	clk_hw_data->num = IMX6SL_CLK_END;
	hws = clk_hw_data->hws;

	hws[IMX6SL_CLK_DUMMY] = imx_clk_hw_fixed("dummy", 0);
	hws[IMX6SL_CLK_CKIL] = imx_obtain_fixed_घड़ी_hw("ckil", 0);
	hws[IMX6SL_CLK_OSC] = imx_obtain_fixed_घड़ी_hw("osc", 0);
	/* Clock source from बाह्यal घड़ी via CLK1 PAD */
	hws[IMX6SL_CLK_ANACLK1] = imx_obtain_fixed_घड़ी_hw("anaclk1", 0);

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx6sl-anatop");
	base = of_iomap(np, 0);
	WARN_ON(!base);
	of_node_put(np);
	anatop_base = base;

	hws[IMX6SL_PLL1_BYPASS_SRC] = imx_clk_hw_mux("pll1_bypass_src", base + 0x00, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6SL_PLL2_BYPASS_SRC] = imx_clk_hw_mux("pll2_bypass_src", base + 0x30, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6SL_PLL3_BYPASS_SRC] = imx_clk_hw_mux("pll3_bypass_src", base + 0x10, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6SL_PLL4_BYPASS_SRC] = imx_clk_hw_mux("pll4_bypass_src", base + 0x70, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6SL_PLL5_BYPASS_SRC] = imx_clk_hw_mux("pll5_bypass_src", base + 0xa0, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6SL_PLL6_BYPASS_SRC] = imx_clk_hw_mux("pll6_bypass_src", base + 0xe0, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6SL_PLL7_BYPASS_SRC] = imx_clk_hw_mux("pll7_bypass_src", base + 0x20, 14, 1, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));

	/*                                    type               name    parent_name        base         भाग_mask */
	hws[IMX6SL_CLK_PLL1] = imx_clk_hw_pllv3(IMX_PLLV3_SYS,     "pll1", "osc", base + 0x00, 0x7f);
	hws[IMX6SL_CLK_PLL2] = imx_clk_hw_pllv3(IMX_PLLV3_GENERIC, "pll2", "osc", base + 0x30, 0x1);
	hws[IMX6SL_CLK_PLL3] = imx_clk_hw_pllv3(IMX_PLLV3_USB,     "pll3", "osc", base + 0x10, 0x3);
	hws[IMX6SL_CLK_PLL4] = imx_clk_hw_pllv3(IMX_PLLV3_AV,      "pll4", "osc", base + 0x70, 0x7f);
	hws[IMX6SL_CLK_PLL5] = imx_clk_hw_pllv3(IMX_PLLV3_AV,      "pll5", "osc", base + 0xa0, 0x7f);
	hws[IMX6SL_CLK_PLL6] = imx_clk_hw_pllv3(IMX_PLLV3_ENET,    "pll6", "osc", base + 0xe0, 0x3);
	hws[IMX6SL_CLK_PLL7] = imx_clk_hw_pllv3(IMX_PLLV3_USB,     "pll7", "osc", base + 0x20, 0x3);

	hws[IMX6SL_PLL1_BYPASS] = imx_clk_hw_mux_flags("pll1_bypass", base + 0x00, 16, 1, pll1_bypass_sels, ARRAY_SIZE(pll1_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6SL_PLL2_BYPASS] = imx_clk_hw_mux_flags("pll2_bypass", base + 0x30, 16, 1, pll2_bypass_sels, ARRAY_SIZE(pll2_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6SL_PLL3_BYPASS] = imx_clk_hw_mux_flags("pll3_bypass", base + 0x10, 16, 1, pll3_bypass_sels, ARRAY_SIZE(pll3_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6SL_PLL4_BYPASS] = imx_clk_hw_mux_flags("pll4_bypass", base + 0x70, 16, 1, pll4_bypass_sels, ARRAY_SIZE(pll4_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6SL_PLL5_BYPASS] = imx_clk_hw_mux_flags("pll5_bypass", base + 0xa0, 16, 1, pll5_bypass_sels, ARRAY_SIZE(pll5_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6SL_PLL6_BYPASS] = imx_clk_hw_mux_flags("pll6_bypass", base + 0xe0, 16, 1, pll6_bypass_sels, ARRAY_SIZE(pll6_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6SL_PLL7_BYPASS] = imx_clk_hw_mux_flags("pll7_bypass", base + 0x20, 16, 1, pll7_bypass_sels, ARRAY_SIZE(pll7_bypass_sels), CLK_SET_RATE_PARENT);

	/* Do not bypass PLLs initially */
	clk_set_parent(hws[IMX6SL_PLL1_BYPASS]->clk, hws[IMX6SL_CLK_PLL1]->clk);
	clk_set_parent(hws[IMX6SL_PLL2_BYPASS]->clk, hws[IMX6SL_CLK_PLL2]->clk);
	clk_set_parent(hws[IMX6SL_PLL3_BYPASS]->clk, hws[IMX6SL_CLK_PLL3]->clk);
	clk_set_parent(hws[IMX6SL_PLL4_BYPASS]->clk, hws[IMX6SL_CLK_PLL4]->clk);
	clk_set_parent(hws[IMX6SL_PLL5_BYPASS]->clk, hws[IMX6SL_CLK_PLL5]->clk);
	clk_set_parent(hws[IMX6SL_PLL6_BYPASS]->clk, hws[IMX6SL_CLK_PLL6]->clk);
	clk_set_parent(hws[IMX6SL_PLL7_BYPASS]->clk, hws[IMX6SL_CLK_PLL7]->clk);

	hws[IMX6SL_CLK_PLL1_SYS]      = imx_clk_hw_gate("pll1_sys",      "pll1_bypass", base + 0x00, 13);
	hws[IMX6SL_CLK_PLL2_BUS]      = imx_clk_hw_gate("pll2_bus",      "pll2_bypass", base + 0x30, 13);
	hws[IMX6SL_CLK_PLL3_USB_OTG]  = imx_clk_hw_gate("pll3_usb_otg",  "pll3_bypass", base + 0x10, 13);
	hws[IMX6SL_CLK_PLL4_AUDIO]    = imx_clk_hw_gate("pll4_audio",    "pll4_bypass", base + 0x70, 13);
	hws[IMX6SL_CLK_PLL5_VIDEO]    = imx_clk_hw_gate("pll5_video",    "pll5_bypass", base + 0xa0, 13);
	hws[IMX6SL_CLK_PLL6_ENET]     = imx_clk_hw_gate("pll6_enet",     "pll6_bypass", base + 0xe0, 13);
	hws[IMX6SL_CLK_PLL7_USB_HOST] = imx_clk_hw_gate("pll7_usb_host", "pll7_bypass", base + 0x20, 13);

	hws[IMX6SL_CLK_LVDS1_SEL] = imx_clk_hw_mux("lvds1_sel", base + 0x160, 0, 5, lvds_sels, ARRAY_SIZE(lvds_sels));
	hws[IMX6SL_CLK_LVDS1_OUT] = imx_clk_hw_gate_exclusive("lvds1_out", "lvds1_sel", base + 0x160, 10, BIT(12));
	hws[IMX6SL_CLK_LVDS1_IN] = imx_clk_hw_gate_exclusive("lvds1_in", "anaclk1", base + 0x160, 12, BIT(10));

	/*
	 * usbphy1 and usbphy2 are implemented as dummy gates using reserve
	 * bit 20.  They are used by phy driver to keep the refcount of
	 * parent PLL correct. usbphy1_gate and usbphy2_gate only needs to be
	 * turned on during boot, and software will not need to control it
	 * anymore after that.
	 */
	hws[IMX6SL_CLK_USBPHY1]      = imx_clk_hw_gate("usbphy1",      "pll3_usb_otg",  base + 0x10, 20);
	hws[IMX6SL_CLK_USBPHY2]      = imx_clk_hw_gate("usbphy2",      "pll7_usb_host", base + 0x20, 20);
	hws[IMX6SL_CLK_USBPHY1_GATE] = imx_clk_hw_gate("usbphy1_gate", "dummy",         base + 0x10, 6);
	hws[IMX6SL_CLK_USBPHY2_GATE] = imx_clk_hw_gate("usbphy2_gate", "dummy",         base + 0x20, 6);

	/*                                                           dev   name              parent_name      flags                reg        shअगरt width भाग: flags, भाग_प्रकारable lock */
	hws[IMX6SL_CLK_PLL4_POST_DIV]  = clk_hw_रेजिस्टर_भागider_table(शून्य, "pll4_post_div",  "pll4_audio",    CLK_SET_RATE_PARENT, base + 0x70,  19, 2,   0, post_भाग_प्रकारable, &imx_ccm_lock);
	hws[IMX6SL_CLK_PLL4_AUDIO_DIV] =       clk_hw_रेजिस्टर_भागider(शून्य, "pll4_audio_div", "pll4_post_div", CLK_SET_RATE_PARENT, base + 0x170, 15, 1,   0, &imx_ccm_lock);
	hws[IMX6SL_CLK_PLL5_POST_DIV]  = clk_hw_रेजिस्टर_भागider_table(शून्य, "pll5_post_div",  "pll5_video",    CLK_SET_RATE_PARENT, base + 0xa0,  19, 2,   0, post_भाग_प्रकारable, &imx_ccm_lock);
	hws[IMX6SL_CLK_PLL5_VIDEO_DIV] = clk_hw_रेजिस्टर_भागider_table(शून्य, "pll5_video_div", "pll5_post_div", CLK_SET_RATE_PARENT, base + 0x170, 30, 2,   0, video_भाग_प्रकारable, &imx_ccm_lock);
	hws[IMX6SL_CLK_ENET_REF]       = clk_hw_रेजिस्टर_भागider_table(शून्य, "enet_ref",       "pll6_enet",     0,                   base + 0xe0,  0,  2,   0, clk_enet_ref_table, &imx_ccm_lock);

	/*                                       name         parent_name     reg           idx */
	hws[IMX6SL_CLK_PLL2_PFD0] = imx_clk_hw_pfd("pll2_pfd0", "pll2_bus",     base + 0x100, 0);
	hws[IMX6SL_CLK_PLL2_PFD1] = imx_clk_hw_pfd("pll2_pfd1", "pll2_bus",     base + 0x100, 1);
	hws[IMX6SL_CLK_PLL2_PFD2] = imx_clk_hw_pfd("pll2_pfd2", "pll2_bus",     base + 0x100, 2);
	hws[IMX6SL_CLK_PLL3_PFD0] = imx_clk_hw_pfd("pll3_pfd0", "pll3_usb_otg", base + 0xf0,  0);
	hws[IMX6SL_CLK_PLL3_PFD1] = imx_clk_hw_pfd("pll3_pfd1", "pll3_usb_otg", base + 0xf0,  1);
	hws[IMX6SL_CLK_PLL3_PFD2] = imx_clk_hw_pfd("pll3_pfd2", "pll3_usb_otg", base + 0xf0,  2);
	hws[IMX6SL_CLK_PLL3_PFD3] = imx_clk_hw_pfd("pll3_pfd3", "pll3_usb_otg", base + 0xf0,  3);

	/*                                                name         parent_name     mult भाग */
	hws[IMX6SL_CLK_PLL2_198M] = imx_clk_hw_fixed_factor("pll2_198m", "pll2_pfd2",      1, 2);
	hws[IMX6SL_CLK_PLL3_120M] = imx_clk_hw_fixed_factor("pll3_120m", "pll3_usb_otg",   1, 4);
	hws[IMX6SL_CLK_PLL3_80M]  = imx_clk_hw_fixed_factor("pll3_80m",  "pll3_usb_otg",   1, 6);
	hws[IMX6SL_CLK_PLL3_60M]  = imx_clk_hw_fixed_factor("pll3_60m",  "pll3_usb_otg",   1, 8);

	np = ccm_node;
	base = of_iomap(np, 0);
	WARN_ON(!base);
	ccm_base = base;

	/*                                              name                reg       shअगरt width parent_names     num_parents */
	hws[IMX6SL_CLK_STEP]             = imx_clk_hw_mux("step",             base + 0xc,  8,  1, step_sels,         ARRAY_SIZE(step_sels));
	hws[IMX6SL_CLK_PLL1_SW]          = imx_clk_hw_mux("pll1_sw",          base + 0xc,  2,  1, pll1_sw_sels,      ARRAY_SIZE(pll1_sw_sels));
	hws[IMX6SL_CLK_OCRAM_ALT_SEL]    = imx_clk_hw_mux("ocram_alt_sel",    base + 0x14, 7,  1, ocram_alt_sels,    ARRAY_SIZE(ocram_alt_sels));
	hws[IMX6SL_CLK_OCRAM_SEL]        = imx_clk_hw_mux("ocram_sel",        base + 0x14, 6,  1, ocram_sels,        ARRAY_SIZE(ocram_sels));
	hws[IMX6SL_CLK_PRE_PERIPH2_SEL]  = imx_clk_hw_mux("pre_periph2_sel",  base + 0x18, 21, 2, pre_periph_sels,   ARRAY_SIZE(pre_periph_sels));
	hws[IMX6SL_CLK_PRE_PERIPH_SEL]   = imx_clk_hw_mux("pre_periph_sel",   base + 0x18, 18, 2, pre_periph_sels,   ARRAY_SIZE(pre_periph_sels));
	hws[IMX6SL_CLK_PERIPH2_CLK2_SEL] = imx_clk_hw_mux("periph2_clk2_sel", base + 0x18, 20, 1, periph2_clk2_sels, ARRAY_SIZE(periph2_clk2_sels));
	hws[IMX6SL_CLK_PERIPH_CLK2_SEL]  = imx_clk_hw_mux("periph_clk2_sel",  base + 0x18, 12, 2, periph_clk2_sels,  ARRAY_SIZE(periph_clk2_sels));
	hws[IMX6SL_CLK_CSI_SEL]          = imx_clk_hw_mux("csi_sel",          base + 0x3c, 9,  2, csi_sels,          ARRAY_SIZE(csi_sels));
	hws[IMX6SL_CLK_LCDIF_AXI_SEL]    = imx_clk_hw_mux("lcdif_axi_sel",    base + 0x3c, 14, 2, lcdअगर_axi_sels,    ARRAY_SIZE(lcdअगर_axi_sels));
	hws[IMX6SL_CLK_USDHC1_SEL]       = imx_clk_hw_fixup_mux("usdhc1_sel", base + 0x1c, 16, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels),  imx_cscmr1_fixup);
	hws[IMX6SL_CLK_USDHC2_SEL]       = imx_clk_hw_fixup_mux("usdhc2_sel", base + 0x1c, 17, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels),  imx_cscmr1_fixup);
	hws[IMX6SL_CLK_USDHC3_SEL]       = imx_clk_hw_fixup_mux("usdhc3_sel", base + 0x1c, 18, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels),  imx_cscmr1_fixup);
	hws[IMX6SL_CLK_USDHC4_SEL]       = imx_clk_hw_fixup_mux("usdhc4_sel", base + 0x1c, 19, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels),  imx_cscmr1_fixup);
	hws[IMX6SL_CLK_SSI1_SEL]         = imx_clk_hw_fixup_mux("ssi1_sel",   base + 0x1c, 10, 2, ssi_sels,          ARRAY_SIZE(ssi_sels),    imx_cscmr1_fixup);
	hws[IMX6SL_CLK_SSI2_SEL]         = imx_clk_hw_fixup_mux("ssi2_sel",   base + 0x1c, 12, 2, ssi_sels,          ARRAY_SIZE(ssi_sels),    imx_cscmr1_fixup);
	hws[IMX6SL_CLK_SSI3_SEL]         = imx_clk_hw_fixup_mux("ssi3_sel",   base + 0x1c, 14, 2, ssi_sels,          ARRAY_SIZE(ssi_sels),    imx_cscmr1_fixup);
	hws[IMX6SL_CLK_PERCLK_SEL]       = imx_clk_hw_fixup_mux("perclk_sel", base + 0x1c, 6,  1, perclk_sels,       ARRAY_SIZE(perclk_sels), imx_cscmr1_fixup);
	hws[IMX6SL_CLK_PXP_AXI_SEL]      = imx_clk_hw_mux("pxp_axi_sel",      base + 0x34, 6,  3, pxp_axi_sels,      ARRAY_SIZE(pxp_axi_sels));
	hws[IMX6SL_CLK_EPDC_AXI_SEL]     = imx_clk_hw_mux("epdc_axi_sel",     base + 0x34, 15, 3, epdc_axi_sels,     ARRAY_SIZE(epdc_axi_sels));
	hws[IMX6SL_CLK_GPU2D_OVG_SEL]    = imx_clk_hw_mux("gpu2d_ovg_sel",    base + 0x18, 4,  2, gpu2d_ovg_sels,    ARRAY_SIZE(gpu2d_ovg_sels));
	hws[IMX6SL_CLK_GPU2D_SEL]        = imx_clk_hw_mux("gpu2d_sel",        base + 0x18, 8,  2, gpu2d_sels,        ARRAY_SIZE(gpu2d_sels));
	hws[IMX6SL_CLK_LCDIF_PIX_SEL]    = imx_clk_hw_mux("lcdif_pix_sel",    base + 0x38, 6,  3, lcdअगर_pix_sels,    ARRAY_SIZE(lcdअगर_pix_sels));
	hws[IMX6SL_CLK_EPDC_PIX_SEL]     = imx_clk_hw_mux("epdc_pix_sel",     base + 0x38, 15, 3, epdc_pix_sels,     ARRAY_SIZE(epdc_pix_sels));
	hws[IMX6SL_CLK_SPDIF0_SEL]       = imx_clk_hw_mux("spdif0_sel",       base + 0x30, 20, 2, audio_sels,        ARRAY_SIZE(audio_sels));
	hws[IMX6SL_CLK_SPDIF1_SEL]       = imx_clk_hw_mux("spdif1_sel",       base + 0x30, 7,  2, audio_sels,        ARRAY_SIZE(audio_sels));
	hws[IMX6SL_CLK_EXTERN_AUDIO_SEL] = imx_clk_hw_mux("extern_audio_sel", base + 0x20, 19, 2, audio_sels,        ARRAY_SIZE(audio_sels));
	hws[IMX6SL_CLK_ECSPI_SEL]        = imx_clk_hw_mux("ecspi_sel",        base + 0x38, 18, 1, ecspi_sels,        ARRAY_SIZE(ecspi_sels));
	hws[IMX6SL_CLK_UART_SEL]         = imx_clk_hw_mux("uart_sel",         base + 0x24, 6,  1, uart_sels,         ARRAY_SIZE(uart_sels));

	/*                                          name       reg        shअगरt width busy: reg, shअगरt parent_names  num_parents */
	hws[IMX6SL_CLK_PERIPH]  = imx_clk_hw_busy_mux("periph",  base + 0x14, 25,  1,   base + 0x48, 5,  periph_sels,  ARRAY_SIZE(periph_sels));
	hws[IMX6SL_CLK_PERIPH2] = imx_clk_hw_busy_mux("periph2", base + 0x14, 26,  1,   base + 0x48, 3,  periph2_sels, ARRAY_SIZE(periph2_sels));

	/*                                                   name                 parent_name          reg       shअगरt width */
	hws[IMX6SL_CLK_OCRAM_PODF]        = imx_clk_hw_busy_भागider("ocram_podf",   "ocram_sel",         base + 0x14, 16, 3, base + 0x48, 0);
	hws[IMX6SL_CLK_PERIPH_CLK2_PODF]  = imx_clk_hw_भागider("periph_clk2_podf",  "periph_clk2_sel",   base + 0x14, 27, 3);
	hws[IMX6SL_CLK_PERIPH2_CLK2_PODF] = imx_clk_hw_भागider("periph2_clk2_podf", "periph2_clk2_sel",  base + 0x14, 0,  3);
	hws[IMX6SL_CLK_IPG]               = imx_clk_hw_भागider("ipg",               "ahb",               base + 0x14, 8,  2);
	hws[IMX6SL_CLK_CSI_PODF]          = imx_clk_hw_भागider("csi_podf",          "csi_sel",           base + 0x3c, 11, 3);
	hws[IMX6SL_CLK_LCDIF_AXI_PODF]    = imx_clk_hw_भागider("lcdif_axi_podf",    "lcdif_axi_sel",     base + 0x3c, 16, 3);
	hws[IMX6SL_CLK_USDHC1_PODF]       = imx_clk_hw_भागider("usdhc1_podf",       "usdhc1_sel",        base + 0x24, 11, 3);
	hws[IMX6SL_CLK_USDHC2_PODF]       = imx_clk_hw_भागider("usdhc2_podf",       "usdhc2_sel",        base + 0x24, 16, 3);
	hws[IMX6SL_CLK_USDHC3_PODF]       = imx_clk_hw_भागider("usdhc3_podf",       "usdhc3_sel",        base + 0x24, 19, 3);
	hws[IMX6SL_CLK_USDHC4_PODF]       = imx_clk_hw_भागider("usdhc4_podf",       "usdhc4_sel",        base + 0x24, 22, 3);
	hws[IMX6SL_CLK_SSI1_PRED]         = imx_clk_hw_भागider("ssi1_pred",         "ssi1_sel",          base + 0x28, 6,  3);
	hws[IMX6SL_CLK_SSI1_PODF]         = imx_clk_hw_भागider("ssi1_podf",         "ssi1_pred",         base + 0x28, 0,  6);
	hws[IMX6SL_CLK_SSI2_PRED]         = imx_clk_hw_भागider("ssi2_pred",         "ssi2_sel",          base + 0x2c, 6,  3);
	hws[IMX6SL_CLK_SSI2_PODF]         = imx_clk_hw_भागider("ssi2_podf",         "ssi2_pred",         base + 0x2c, 0,  6);
	hws[IMX6SL_CLK_SSI3_PRED]         = imx_clk_hw_भागider("ssi3_pred",         "ssi3_sel",          base + 0x28, 22, 3);
	hws[IMX6SL_CLK_SSI3_PODF]         = imx_clk_hw_भागider("ssi3_podf",         "ssi3_pred",         base + 0x28, 16, 6);
	hws[IMX6SL_CLK_PERCLK]            = imx_clk_hw_fixup_भागider("perclk",      "perclk_sel",        base + 0x1c, 0,  6, imx_cscmr1_fixup);
	hws[IMX6SL_CLK_PXP_AXI_PODF]      = imx_clk_hw_भागider("pxp_axi_podf",      "pxp_axi_sel",       base + 0x34, 3,  3);
	hws[IMX6SL_CLK_EPDC_AXI_PODF]     = imx_clk_hw_भागider("epdc_axi_podf",     "epdc_axi_sel",      base + 0x34, 12, 3);
	hws[IMX6SL_CLK_GPU2D_OVG_PODF]    = imx_clk_hw_भागider("gpu2d_ovg_podf",    "gpu2d_ovg_sel",     base + 0x18, 26, 3);
	hws[IMX6SL_CLK_GPU2D_PODF]        = imx_clk_hw_भागider("gpu2d_podf",        "gpu2d_sel",         base + 0x18, 29, 3);
	hws[IMX6SL_CLK_LCDIF_PIX_PRED]    = imx_clk_hw_भागider("lcdif_pix_pred",    "lcdif_pix_sel",     base + 0x38, 3,  3);
	hws[IMX6SL_CLK_EPDC_PIX_PRED]     = imx_clk_hw_भागider("epdc_pix_pred",     "epdc_pix_sel",      base + 0x38, 12, 3);
	hws[IMX6SL_CLK_LCDIF_PIX_PODF]    = imx_clk_hw_fixup_भागider("lcdif_pix_podf", "lcdif_pix_pred", base + 0x1c, 20, 3, imx_cscmr1_fixup);
	hws[IMX6SL_CLK_EPDC_PIX_PODF]     = imx_clk_hw_भागider("epdc_pix_podf",     "epdc_pix_pred",     base + 0x18, 23, 3);
	hws[IMX6SL_CLK_SPDIF0_PRED]       = imx_clk_hw_भागider("spdif0_pred",       "spdif0_sel",        base + 0x30, 25, 3);
	hws[IMX6SL_CLK_SPDIF0_PODF]       = imx_clk_hw_भागider("spdif0_podf",       "spdif0_pred",       base + 0x30, 22, 3);
	hws[IMX6SL_CLK_SPDIF1_PRED]       = imx_clk_hw_भागider("spdif1_pred",       "spdif1_sel",        base + 0x30, 12, 3);
	hws[IMX6SL_CLK_SPDIF1_PODF]       = imx_clk_hw_भागider("spdif1_podf",       "spdif1_pred",       base + 0x30, 9,  3);
	hws[IMX6SL_CLK_EXTERN_AUDIO_PRED] = imx_clk_hw_भागider("extern_audio_pred", "extern_audio_sel",  base + 0x28, 9,  3);
	hws[IMX6SL_CLK_EXTERN_AUDIO_PODF] = imx_clk_hw_भागider("extern_audio_podf", "extern_audio_pred", base + 0x28, 25, 3);
	hws[IMX6SL_CLK_ECSPI_ROOT]        = imx_clk_hw_भागider("ecspi_root",        "ecspi_sel",         base + 0x38, 19, 6);
	hws[IMX6SL_CLK_UART_ROOT]         = imx_clk_hw_भागider("uart_root",         "uart_sel",          base + 0x24, 0,  6);

	/*                                                name         parent_name reg       shअगरt width busy: reg, shअगरt */
	hws[IMX6SL_CLK_AHB]       = imx_clk_hw_busy_भागider("ahb",       "periph",  base + 0x14, 10, 3,    base + 0x48, 1);
	hws[IMX6SL_CLK_MMDC_ROOT] = imx_clk_hw_busy_भागider("mmdc",      "periph2", base + 0x14, 3,  3,    base + 0x48, 2);
	hws[IMX6SL_CLK_ARM]       = imx_clk_hw_busy_भागider("arm",       "pll1_sw", base + 0x10, 0,  3,    base + 0x48, 16);

	/*                                            name            parent_name          reg         shअगरt */
	hws[IMX6SL_CLK_ECSPI1]       = imx_clk_hw_gate2("ecspi1",       "ecspi_root",        base + 0x6c, 0);
	hws[IMX6SL_CLK_ECSPI2]       = imx_clk_hw_gate2("ecspi2",       "ecspi_root",        base + 0x6c, 2);
	hws[IMX6SL_CLK_ECSPI3]       = imx_clk_hw_gate2("ecspi3",       "ecspi_root",        base + 0x6c, 4);
	hws[IMX6SL_CLK_ECSPI4]       = imx_clk_hw_gate2("ecspi4",       "ecspi_root",        base + 0x6c, 6);
	hws[IMX6SL_CLK_ENET]         = imx_clk_hw_gate2("enet",         "ipg",               base + 0x6c, 10);
	hws[IMX6SL_CLK_EPIT1]        = imx_clk_hw_gate2("epit1",        "perclk",            base + 0x6c, 12);
	hws[IMX6SL_CLK_EPIT2]        = imx_clk_hw_gate2("epit2",        "perclk",            base + 0x6c, 14);
	hws[IMX6SL_CLK_EXTERN_AUDIO] = imx_clk_hw_gate2("extern_audio", "extern_audio_podf", base + 0x6c, 16);
	hws[IMX6SL_CLK_GPT]          = imx_clk_hw_gate2("gpt",          "perclk",            base + 0x6c, 20);
	hws[IMX6SL_CLK_GPT_SERIAL]   = imx_clk_hw_gate2("gpt_serial",   "perclk",            base + 0x6c, 22);
	hws[IMX6SL_CLK_GPU2D_OVG]    = imx_clk_hw_gate2("gpu2d_ovg",    "gpu2d_ovg_podf",    base + 0x6c, 26);
	hws[IMX6SL_CLK_I2C1]         = imx_clk_hw_gate2("i2c1",         "perclk",            base + 0x70, 6);
	hws[IMX6SL_CLK_I2C2]         = imx_clk_hw_gate2("i2c2",         "perclk",            base + 0x70, 8);
	hws[IMX6SL_CLK_I2C3]         = imx_clk_hw_gate2("i2c3",         "perclk",            base + 0x70, 10);
	hws[IMX6SL_CLK_OCOTP]        = imx_clk_hw_gate2("ocotp",        "ipg",               base + 0x70, 12);
	hws[IMX6SL_CLK_CSI]          = imx_clk_hw_gate2("csi",          "csi_podf",          base + 0x74, 0);
	hws[IMX6SL_CLK_PXP_AXI]      = imx_clk_hw_gate2("pxp_axi",      "pxp_axi_podf",      base + 0x74, 2);
	hws[IMX6SL_CLK_EPDC_AXI]     = imx_clk_hw_gate2("epdc_axi",     "epdc_axi_podf",     base + 0x74, 4);
	hws[IMX6SL_CLK_LCDIF_AXI]    = imx_clk_hw_gate2("lcdif_axi",    "lcdif_axi_podf",    base + 0x74, 6);
	hws[IMX6SL_CLK_LCDIF_PIX]    = imx_clk_hw_gate2("lcdif_pix",    "lcdif_pix_podf",    base + 0x74, 8);
	hws[IMX6SL_CLK_EPDC_PIX]     = imx_clk_hw_gate2("epdc_pix",     "epdc_pix_podf",     base + 0x74, 10);
	hws[IMX6SL_CLK_MMDC_P0_IPG]  = imx_clk_hw_gate2_flags("mmdc_p0_ipg",  "ipg",         base + 0x74, 24, CLK_IS_CRITICAL);
	hws[IMX6SL_CLK_MMDC_P1_IPG]  = imx_clk_hw_gate2("mmdc_p1_ipg",  "ipg",               base + 0x74, 26);
	hws[IMX6SL_CLK_OCRAM]        = imx_clk_hw_gate2("ocram",        "ocram_podf",        base + 0x74, 28);
	hws[IMX6SL_CLK_PWM1]         = imx_clk_hw_gate2("pwm1",         "perclk",            base + 0x78, 16);
	hws[IMX6SL_CLK_PWM2]         = imx_clk_hw_gate2("pwm2",         "perclk",            base + 0x78, 18);
	hws[IMX6SL_CLK_PWM3]         = imx_clk_hw_gate2("pwm3",         "perclk",            base + 0x78, 20);
	hws[IMX6SL_CLK_PWM4]         = imx_clk_hw_gate2("pwm4",         "perclk",            base + 0x78, 22);
	hws[IMX6SL_CLK_SDMA]         = imx_clk_hw_gate2("sdma",         "ipg",               base + 0x7c, 6);
	hws[IMX6SL_CLK_SPBA]         = imx_clk_hw_gate2("spba",         "ipg",               base + 0x7c, 12);
	hws[IMX6SL_CLK_SPDIF]        = imx_clk_hw_gate2_shared("spdif",     "spdif0_podf",   base + 0x7c, 14, &share_count_spdअगर);
	hws[IMX6SL_CLK_SPDIF_GCLK]   = imx_clk_hw_gate2_shared("spdif_gclk",  "ipg",         base + 0x7c, 14, &share_count_spdअगर);
	hws[IMX6SL_CLK_SSI1_IPG]     = imx_clk_hw_gate2_shared("ssi1_ipg",     "ipg",        base + 0x7c, 18, &share_count_ssi1);
	hws[IMX6SL_CLK_SSI2_IPG]     = imx_clk_hw_gate2_shared("ssi2_ipg",     "ipg",        base + 0x7c, 20, &share_count_ssi2);
	hws[IMX6SL_CLK_SSI3_IPG]     = imx_clk_hw_gate2_shared("ssi3_ipg",     "ipg",        base + 0x7c, 22, &share_count_ssi3);
	hws[IMX6SL_CLK_SSI1]         = imx_clk_hw_gate2_shared("ssi1",         "ssi1_podf",  base + 0x7c, 18, &share_count_ssi1);
	hws[IMX6SL_CLK_SSI2]         = imx_clk_hw_gate2_shared("ssi2",         "ssi2_podf",  base + 0x7c, 20, &share_count_ssi2);
	hws[IMX6SL_CLK_SSI3]         = imx_clk_hw_gate2_shared("ssi3",         "ssi3_podf",  base + 0x7c, 22, &share_count_ssi3);
	hws[IMX6SL_CLK_UART]         = imx_clk_hw_gate2("uart",         "ipg",               base + 0x7c, 24);
	hws[IMX6SL_CLK_UART_SERIAL]  = imx_clk_hw_gate2("uart_serial",  "uart_root",         base + 0x7c, 26);
	hws[IMX6SL_CLK_USBOH3]       = imx_clk_hw_gate2("usboh3",       "ipg",               base + 0x80, 0);
	hws[IMX6SL_CLK_USDHC1]       = imx_clk_hw_gate2("usdhc1",       "usdhc1_podf",       base + 0x80, 2);
	hws[IMX6SL_CLK_USDHC2]       = imx_clk_hw_gate2("usdhc2",       "usdhc2_podf",       base + 0x80, 4);
	hws[IMX6SL_CLK_USDHC3]       = imx_clk_hw_gate2("usdhc3",       "usdhc3_podf",       base + 0x80, 6);
	hws[IMX6SL_CLK_USDHC4]       = imx_clk_hw_gate2("usdhc4",       "usdhc4_podf",       base + 0x80, 8);

	/* Ensure the MMDC CH0 handshake is bypassed */
	imx_mmdc_mask_handshake(base, 0);

	imx_check_clk_hws(hws, IMX6SL_CLK_END);

	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_hw_data);

	/* Ensure the AHB clk is at 132MHz. */
	ret = clk_set_rate(hws[IMX6SL_CLK_AHB]->clk, 132000000);
	अगर (ret)
		pr_warn("%s: failed to set AHB clock rate %d!\n",
			__func__, ret);

	अगर (IS_ENABLED(CONFIG_USB_MXS_PHY)) अणु
		clk_prepare_enable(hws[IMX6SL_CLK_USBPHY1_GATE]->clk);
		clk_prepare_enable(hws[IMX6SL_CLK_USBPHY2_GATE]->clk);
	पूर्ण

	/* Audio-related घड़ीs configuration */
	clk_set_parent(hws[IMX6SL_CLK_SPDIF0_SEL]->clk, hws[IMX6SL_CLK_PLL3_PFD3]->clk);

	/* set PLL5 video as lcdअगर pix parent घड़ी */
	clk_set_parent(hws[IMX6SL_CLK_LCDIF_PIX_SEL]->clk,
			hws[IMX6SL_CLK_PLL5_VIDEO_DIV]->clk);

	clk_set_parent(hws[IMX6SL_CLK_LCDIF_AXI_SEL]->clk,
		       hws[IMX6SL_CLK_PLL2_PFD2]->clk);

	imx_रेजिस्टर_uart_घड़ीs(2);
पूर्ण
CLK_OF_DECLARE(imx6sl, "fsl,imx6sl-ccm", imx6sl_घड़ीs_init);
