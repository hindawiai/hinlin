<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011-2013 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <soc/imx/revision.h>
#समावेश <dt-bindings/घड़ी/imx6qdl-घड़ी.h>

#समावेश "clk.h"

अटल स्थिर अक्षर *step_sels[]	= अणु "osc", "pll2_pfd2_396m", पूर्ण;
अटल स्थिर अक्षर *pll1_sw_sels[]	= अणु "pll1_sys", "step", पूर्ण;
अटल स्थिर अक्षर *periph_pre_sels[]	= अणु "pll2_bus", "pll2_pfd2_396m", "pll2_pfd0_352m", "pll2_198m", पूर्ण;
अटल स्थिर अक्षर *periph_clk2_sels[]	= अणु "pll3_usb_otg", "osc", "osc", "dummy", पूर्ण;
अटल स्थिर अक्षर *periph2_clk2_sels[]	= अणु "pll3_usb_otg", "pll2_bus", पूर्ण;
अटल स्थिर अक्षर *periph_sels[]	= अणु "periph_pre", "periph_clk2", पूर्ण;
अटल स्थिर अक्षर *periph2_sels[]	= अणु "periph2_pre", "periph2_clk2", पूर्ण;
अटल स्थिर अक्षर *axi_sels[]		= अणु "periph", "pll2_pfd2_396m", "periph", "pll3_pfd1_540m", पूर्ण;
अटल स्थिर अक्षर *audio_sels[]	= अणु "pll4_audio_div", "pll3_pfd2_508m", "pll3_pfd3_454m", "pll3_usb_otg", पूर्ण;
अटल स्थिर अक्षर *gpu_axi_sels[]	= अणु "axi", "ahb", पूर्ण;
अटल स्थिर अक्षर *pre_axi_sels[]	= अणु "axi", "ahb", पूर्ण;
अटल स्थिर अक्षर *gpu2d_core_sels[]	= अणु "axi", "pll3_usb_otg", "pll2_pfd0_352m", "pll2_pfd2_396m", पूर्ण;
अटल स्थिर अक्षर *gpu2d_core_sels_2[]	= अणु "mmdc_ch0_axi", "pll3_usb_otg", "pll2_pfd1_594m", "pll3_pfd0_720m",पूर्ण;
अटल स्थिर अक्षर *gpu3d_core_sels[]	= अणु "mmdc_ch0_axi", "pll3_usb_otg", "pll2_pfd1_594m", "pll2_pfd2_396m", पूर्ण;
अटल स्थिर अक्षर *gpu3d_shader_sels[] = अणु "mmdc_ch0_axi", "pll3_usb_otg", "pll2_pfd1_594m", "pll3_pfd0_720m", पूर्ण;
अटल स्थिर अक्षर *ipu_sels[]		= अणु "mmdc_ch0_axi", "pll2_pfd2_396m", "pll3_120m", "pll3_pfd1_540m", पूर्ण;
अटल स्थिर अक्षर *ldb_di_sels[]	= अणु "pll5_video_div", "pll2_pfd0_352m", "pll2_pfd2_396m", "mmdc_ch1_axi", "pll3_usb_otg", पूर्ण;
अटल स्थिर अक्षर *ipu_di_pre_sels[]	= अणु "mmdc_ch0_axi", "pll3_usb_otg", "pll5_video_div", "pll2_pfd0_352m", "pll2_pfd2_396m", "pll3_pfd1_540m", पूर्ण;
अटल स्थिर अक्षर *ipu1_di0_sels[]	= अणु "ipu1_di0_pre", "dummy", "dummy", "ldb_di0", "ldb_di1", पूर्ण;
अटल स्थिर अक्षर *ipu1_di1_sels[]	= अणु "ipu1_di1_pre", "dummy", "dummy", "ldb_di0", "ldb_di1", पूर्ण;
अटल स्थिर अक्षर *ipu2_di0_sels[]	= अणु "ipu2_di0_pre", "dummy", "dummy", "ldb_di0", "ldb_di1", पूर्ण;
अटल स्थिर अक्षर *ipu2_di1_sels[]	= अणु "ipu2_di1_pre", "dummy", "dummy", "ldb_di0", "ldb_di1", पूर्ण;
अटल स्थिर अक्षर *ipu1_di0_sels_2[]	= अणु "ipu1_di0_pre", "dummy", "dummy", "ldb_di0_podf", "ldb_di1_podf", पूर्ण;
अटल स्थिर अक्षर *ipu1_di1_sels_2[]	= अणु "ipu1_di1_pre", "dummy", "dummy", "ldb_di0_podf", "ldb_di1_podf", पूर्ण;
अटल स्थिर अक्षर *ipu2_di0_sels_2[]	= अणु "ipu2_di0_pre", "dummy", "dummy", "ldb_di0_podf", "ldb_di1_podf", पूर्ण;
अटल स्थिर अक्षर *ipu2_di1_sels_2[]	= अणु "ipu2_di1_pre", "dummy", "dummy", "ldb_di0_podf", "ldb_di1_podf", पूर्ण;
अटल स्थिर अक्षर *hsi_tx_sels[]	= अणु "pll3_120m", "pll2_pfd2_396m", पूर्ण;
अटल स्थिर अक्षर *pcie_axi_sels[]	= अणु "axi", "ahb", पूर्ण;
अटल स्थिर अक्षर *ssi_sels[]		= अणु "pll3_pfd2_508m", "pll3_pfd3_454m", "pll4_audio_div", पूर्ण;
अटल स्थिर अक्षर *usdhc_sels[]	= अणु "pll2_pfd2_396m", "pll2_pfd0_352m", पूर्ण;
अटल स्थिर अक्षर *enfc_sels[]	= अणु "pll2_pfd0_352m", "pll2_bus", "pll3_usb_otg", "pll2_pfd2_396m", पूर्ण;
अटल स्थिर अक्षर *enfc_sels_2[] = अणु"pll2_pfd0_352m", "pll2_bus", "pll3_usb_otg", "pll2_pfd2_396m", "pll3_pfd3_454m", "dummy", पूर्ण;
अटल स्थिर अक्षर *eim_sels[]		= अणु "pll2_pfd2_396m", "pll3_usb_otg", "axi", "pll2_pfd0_352m", पूर्ण;
अटल स्थिर अक्षर *eim_slow_sels[]      = अणु "axi", "pll3_usb_otg", "pll2_pfd2_396m", "pll2_pfd0_352m", पूर्ण;
अटल स्थिर अक्षर *vकरो_axi_sels[]	= अणु "axi", "ahb", पूर्ण;
अटल स्थिर अक्षर *vpu_axi_sels[]	= अणु "axi", "pll2_pfd2_396m", "pll2_pfd0_352m", पूर्ण;
अटल स्थिर अक्षर *uart_sels[] = अणु "pll3_80m", "osc", पूर्ण;
अटल स्थिर अक्षर *ipg_per_sels[] = अणु "ipg", "osc", पूर्ण;
अटल स्थिर अक्षर *ecspi_sels[] = अणु "pll3_60m", "osc", पूर्ण;
अटल स्थिर अक्षर *can_sels[] = अणु "pll3_60m", "osc", "pll3_80m", पूर्ण;
अटल स्थिर अक्षर *cko1_sels[]	= अणु "pll3_usb_otg", "pll2_bus", "pll1_sys", "pll5_video_div",
				    "video_27m", "axi", "enfc", "ipu1_di0", "ipu1_di1", "ipu2_di0",
				    "ipu2_di1", "ahb", "ipg", "ipg_per", "ckil", "pll4_audio_div", पूर्ण;
अटल स्थिर अक्षर *cko2_sels[] = अणु
	"mmdc_ch0_axi", "mmdc_ch1_axi", "usdhc4", "usdhc1",
	"gpu2d_axi", "dummy", "ecspi_root", "gpu3d_axi",
	"usdhc3", "dummy", "arm", "ipu1",
	"ipu2", "vdo_axi", "osc", "gpu2d_core",
	"gpu3d_core", "usdhc2", "ssi1", "ssi2",
	"ssi3", "gpu3d_shader", "vpu_axi", "can_root",
	"ldb_di0", "ldb_di1", "esai_extal", "eim_slow",
	"uart_serial", "spdif", "asrc", "hsi_tx",
पूर्ण;
अटल स्थिर अक्षर *cko_sels[] = अणु "cko1", "cko2", पूर्ण;
अटल स्थिर अक्षर *lvds_sels[] = अणु
	"dummy", "dummy", "dummy", "dummy", "dummy", "dummy",
	"pll4_audio", "pll5_video", "pll8_mlb", "enet_ref",
	"pcie_ref_125m", "sata_ref_100m",  "usbphy1", "usbphy2",
	"dummy", "dummy", "dummy", "dummy", "osc",
पूर्ण;
अटल स्थिर अक्षर *pll_bypass_src_sels[] = अणु "osc", "lvds1_in", "lvds2_in", "dummy", पूर्ण;
अटल स्थिर अक्षर *pll1_bypass_sels[] = अणु "pll1", "pll1_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll2_bypass_sels[] = अणु "pll2", "pll2_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll3_bypass_sels[] = अणु "pll3", "pll3_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll4_bypass_sels[] = अणु "pll4", "pll4_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll5_bypass_sels[] = अणु "pll5", "pll5_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll6_bypass_sels[] = अणु "pll6", "pll6_bypass_src", पूर्ण;
अटल स्थिर अक्षर *pll7_bypass_sels[] = अणु "pll7", "pll7_bypass_src", पूर्ण;

अटल काष्ठा clk_hw **hws;
अटल काष्ठा clk_hw_onecell_data *clk_hw_data;

अटल काष्ठा clk_भाग_प्रकारable clk_enet_ref_table[] = अणु
	अणु .val = 0, .भाग = 20, पूर्ण,
	अणु .val = 1, .भाग = 10, पूर्ण,
	अणु .val = 2, .भाग = 5, पूर्ण,
	अणु .val = 3, .भाग = 4, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable post_भाग_प्रकारable[] = अणु
	अणु .val = 2, .भाग = 1, पूर्ण,
	अणु .val = 1, .भाग = 2, पूर्ण,
	अणु .val = 0, .भाग = 4, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable video_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 1, पूर्ण,
	अणु .val = 1, .भाग = 2, पूर्ण,
	अणु .val = 2, .भाग = 1, पूर्ण,
	अणु .val = 3, .भाग = 4, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक share_count_esai;
अटल अचिन्हित पूर्णांक share_count_asrc;
अटल अचिन्हित पूर्णांक share_count_ssi1;
अटल अचिन्हित पूर्णांक share_count_ssi2;
अटल अचिन्हित पूर्णांक share_count_ssi3;
अटल अचिन्हित पूर्णांक share_count_mipi_core_cfg;
अटल अचिन्हित पूर्णांक share_count_spdअगर;
अटल अचिन्हित पूर्णांक share_count_prg0;
अटल अचिन्हित पूर्णांक share_count_prg1;

अटल अंतरभूत पूर्णांक clk_on_imx6q(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,imx6q");
पूर्ण

अटल अंतरभूत पूर्णांक clk_on_imx6qp(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,imx6qp");
पूर्ण

अटल अंतरभूत पूर्णांक clk_on_imx6dl(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,imx6dl");
पूर्ण

अटल पूर्णांक ldb_di_sel_by_घड़ी_id(पूर्णांक घड़ी_id)
अणु
	चयन (घड़ी_id) अणु
	हाल IMX6QDL_CLK_PLL5_VIDEO_DIV:
		अगर (clk_on_imx6q() &&
		    imx_get_soc_revision() == IMX_CHIP_REVISION_1_0)
			वापस -ENOENT;
		वापस 0;
	हाल IMX6QDL_CLK_PLL2_PFD0_352M:
		वापस 1;
	हाल IMX6QDL_CLK_PLL2_PFD2_396M:
		वापस 2;
	हाल IMX6QDL_CLK_MMDC_CH1_AXI:
		वापस 3;
	हाल IMX6QDL_CLK_PLL3_USB_OTG:
		वापस 4;
	शेष:
		वापस -ENOENT;
	पूर्ण
पूर्ण

अटल व्योम of_asचिन्हित_ldb_sels(काष्ठा device_node *node,
				 अचिन्हित पूर्णांक *ldb_di0_sel,
				 अचिन्हित पूर्णांक *ldb_di1_sel)
अणु
	काष्ठा of_phandle_args clkspec;
	पूर्णांक index, rc, num_parents;
	पूर्णांक parent, child, sel;

	num_parents = of_count_phandle_with_args(node, "assigned-clock-parents",
						 "#clock-cells");
	क्रम (index = 0; index < num_parents; index++) अणु
		rc = of_parse_phandle_with_args(node, "assigned-clock-parents",
					"#clock-cells", index, &clkspec);
		अगर (rc < 0) अणु
			/* skip empty (null) phandles */
			अगर (rc == -ENOENT)
				जारी;
			अन्यथा
				वापस;
		पूर्ण
		अगर (clkspec.np != node || clkspec.args[0] >= IMX6QDL_CLK_END) अणु
			pr_err("ccm: parent clock %d not in ccm\n", index);
			वापस;
		पूर्ण
		parent = clkspec.args[0];

		rc = of_parse_phandle_with_args(node, "assigned-clocks",
				"#clock-cells", index, &clkspec);
		अगर (rc < 0)
			वापस;
		अगर (clkspec.np != node || clkspec.args[0] >= IMX6QDL_CLK_END) अणु
			pr_err("ccm: child clock %d not in ccm\n", index);
			वापस;
		पूर्ण
		child = clkspec.args[0];

		अगर (child != IMX6QDL_CLK_LDB_DI0_SEL &&
		    child != IMX6QDL_CLK_LDB_DI1_SEL)
			जारी;

		sel = ldb_di_sel_by_घड़ी_id(parent);
		अगर (sel < 0) अणु
			pr_err("ccm: invalid ldb_di%d parent clock: %d\n",
			       child == IMX6QDL_CLK_LDB_DI1_SEL, parent);
			जारी;
		पूर्ण

		अगर (child == IMX6QDL_CLK_LDB_DI0_SEL)
			*ldb_di0_sel = sel;
		अगर (child == IMX6QDL_CLK_LDB_DI1_SEL)
			*ldb_di1_sel = sel;
	पूर्ण
पूर्ण

अटल bool pll6_bypassed(काष्ठा device_node *node)
अणु
	पूर्णांक index, ret, num_घड़ीs;
	काष्ठा of_phandle_args clkspec;

	num_घड़ीs = of_count_phandle_with_args(node, "assigned-clocks",
						"#clock-cells");
	अगर (num_घड़ीs < 0)
		वापस false;

	क्रम (index = 0; index < num_घड़ीs; index++) अणु
		ret = of_parse_phandle_with_args(node, "assigned-clocks",
						 "#clock-cells", index,
						 &clkspec);
		अगर (ret < 0)
			वापस false;

		अगर (clkspec.np == node &&
		    clkspec.args[0] == IMX6QDL_PLL6_BYPASS)
			अवरोध;
	पूर्ण

	/* PLL6 bypass is not part of the asचिन्हित घड़ी list */
	अगर (index == num_घड़ीs)
		वापस false;

	ret = of_parse_phandle_with_args(node, "assigned-clock-parents",
					 "#clock-cells", index, &clkspec);

	अगर (clkspec.args[0] != IMX6QDL_CLK_PLL6)
		वापस true;

	वापस false;
पूर्ण

#घोषणा CCM_CCSR		0x0c
#घोषणा CCM_CS2CDR		0x2c

#घोषणा CCSR_PLL3_SW_CLK_SEL		BIT(0)

#घोषणा CS2CDR_LDB_DI0_CLK_SEL_SHIFT	9
#घोषणा CS2CDR_LDB_DI1_CLK_SEL_SHIFT	12

/*
 * The only way to disable the MMDC_CH1 घड़ी is to move it to pll3_sw_clk
 * via periph2_clk2_sel and then to disable pll3_sw_clk by selecting the
 * bypass घड़ी source, since there is no CG bit क्रम mmdc_ch1.
 */
अटल व्योम mmdc_ch1_disable(व्योम __iomem *ccm_base)
अणु
	अचिन्हित पूर्णांक reg;

	clk_set_parent(hws[IMX6QDL_CLK_PERIPH2_CLK2_SEL]->clk,
		       hws[IMX6QDL_CLK_PLL3_USB_OTG]->clk);

	/* Disable pll3_sw_clk by selecting the bypass घड़ी source */
	reg = पढ़ोl_relaxed(ccm_base + CCM_CCSR);
	reg |= CCSR_PLL3_SW_CLK_SEL;
	ग_लिखोl_relaxed(reg, ccm_base + CCM_CCSR);
पूर्ण

अटल व्योम mmdc_ch1_reenable(व्योम __iomem *ccm_base)
अणु
	अचिन्हित पूर्णांक reg;

	/* Enable pll3_sw_clk by disabling the bypass */
	reg = पढ़ोl_relaxed(ccm_base + CCM_CCSR);
	reg &= ~CCSR_PLL3_SW_CLK_SEL;
	ग_लिखोl_relaxed(reg, ccm_base + CCM_CCSR);
पूर्ण

/*
 * We have to follow a strict procedure when changing the LDB घड़ी source,
 * otherwise we risk पूर्णांकroducing a glitch that can lock up the LDB भागider.
 * Things to keep in mind:
 *
 * 1. The current and new parent घड़ी inमाला_दो to the mux must be disabled.
 * 2. The शेष घड़ी input क्रम ldb_di0/1_clk_sel is mmdc_ch1_axi, which
 *    has no CG bit.
 * 3. pll2_pfd2_396m can not be gated अगर it is used as memory घड़ी.
 * 4. In the RTL implementation of the LDB_DI_CLK_SEL muxes the top four
 *    options are in one mux and the PLL3 option aदीर्घ with three unused
 *    inमाला_दो is in a second mux. There is a third mux with two inमाला_दो used
 *    to decide between the first and second 4-port mux:
 *
 *    pll5_video_भाग 0 --|\
 *    pll2_pfd0_352m 1 --| |_
 *    pll2_pfd2_396m 2 --| | `-|\
 *    mmdc_ch1_axi   3 --|/    | |
 *                             | |--
 *    pll3_usb_otg   4 --|\    | |
 *                   5 --| |_,-|/
 *                   6 --| |
 *                   7 --|/
 *
 * The ldb_di0/1_clk_sel[1:0] bits control both 4-port muxes at the same समय.
 * The ldb_di0/1_clk_sel[2] bit controls the 2-port mux. The code below
 * चयनes the parent to the bottom mux first and then manipulates the top
 * mux to ensure that no glitch will enter the भागider.
 */
अटल व्योम init_ldb_clks(काष्ठा device_node *np, व्योम __iomem *ccm_base)
अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक sel[2][4];
	पूर्णांक i;

	reg = पढ़ोl_relaxed(ccm_base + CCM_CS2CDR);
	sel[0][0] = (reg >> CS2CDR_LDB_DI0_CLK_SEL_SHIFT) & 7;
	sel[1][0] = (reg >> CS2CDR_LDB_DI1_CLK_SEL_SHIFT) & 7;

	sel[0][3] = sel[0][2] = sel[0][1] = sel[0][0];
	sel[1][3] = sel[1][2] = sel[1][1] = sel[1][0];

	of_asचिन्हित_ldb_sels(np, &sel[0][3], &sel[1][3]);

	क्रम (i = 0; i < 2; i++) अणु
		/* Prपूर्णांक a notice अगर a glitch might have been पूर्णांकroduced alपढ़ोy */
		अगर (sel[i][0] != 3) अणु
			pr_notice("ccm: possible glitch: ldb_di%d_sel already changed from reset value: %d\n",
				  i, sel[i][0]);
		पूर्ण

		अगर (sel[i][0] == sel[i][3])
			जारी;

		/* Only चयन to or from pll2_pfd2_396m अगर it is disabled */
		अगर ((sel[i][0] == 2 || sel[i][3] == 2) &&
		    (clk_get_parent(hws[IMX6QDL_CLK_PERIPH_PRE]->clk) ==
		     hws[IMX6QDL_CLK_PLL2_PFD2_396M]->clk)) अणु
			pr_err("ccm: ldb_di%d_sel: couldn't disable pll2_pfd2_396m\n",
			       i);
			sel[i][3] = sel[i][2] = sel[i][1] = sel[i][0];
			जारी;
		पूर्ण

		/* First चयन to the bottom mux */
		sel[i][1] = sel[i][0] | 4;

		/* Then configure the top mux beक्रमe चयनing back to it */
		sel[i][2] = sel[i][3] | 4;

		pr_debug("ccm: switching ldb_di%d_sel: %d->%d->%d->%d\n", i,
			 sel[i][0], sel[i][1], sel[i][2], sel[i][3]);
	पूर्ण

	अगर (sel[0][0] == sel[0][3] && sel[1][0] == sel[1][3])
		वापस;

	mmdc_ch1_disable(ccm_base);

	क्रम (i = 1; i < 4; i++) अणु
		reg = पढ़ोl_relaxed(ccm_base + CCM_CS2CDR);
		reg &= ~((7 << CS2CDR_LDB_DI0_CLK_SEL_SHIFT) |
			 (7 << CS2CDR_LDB_DI1_CLK_SEL_SHIFT));
		reg |= ((sel[0][i] << CS2CDR_LDB_DI0_CLK_SEL_SHIFT) |
			(sel[1][i] << CS2CDR_LDB_DI1_CLK_SEL_SHIFT));
		ग_लिखोl_relaxed(reg, ccm_base + CCM_CS2CDR);
	पूर्ण

	mmdc_ch1_reenable(ccm_base);
पूर्ण

#घोषणा CCM_ANALOG_PLL_VIDEO	0xa0
#घोषणा CCM_ANALOG_PFD_480	0xf0
#घोषणा CCM_ANALOG_PFD_528	0x100

#घोषणा PLL_ENABLE		BIT(13)

#घोषणा PFD0_CLKGATE		BIT(7)
#घोषणा PFD1_CLKGATE		BIT(15)
#घोषणा PFD2_CLKGATE		BIT(23)
#घोषणा PFD3_CLKGATE		BIT(31)

अटल व्योम disable_anatop_घड़ीs(व्योम __iomem *anatop_base)
अणु
	अचिन्हित पूर्णांक reg;

	/* Make sure PLL2 PFDs 0-2 are gated */
	reg = पढ़ोl_relaxed(anatop_base + CCM_ANALOG_PFD_528);
	/* Cannot gate PFD2 अगर pll2_pfd2_396m is the parent of MMDC घड़ी */
	अगर (clk_get_parent(hws[IMX6QDL_CLK_PERIPH_PRE]->clk) ==
	    hws[IMX6QDL_CLK_PLL2_PFD2_396M]->clk)
		reg |= PFD0_CLKGATE | PFD1_CLKGATE;
	अन्यथा
		reg |= PFD0_CLKGATE | PFD1_CLKGATE | PFD2_CLKGATE;
	ग_लिखोl_relaxed(reg, anatop_base + CCM_ANALOG_PFD_528);

	/* Make sure PLL3 PFDs 0-3 are gated */
	reg = पढ़ोl_relaxed(anatop_base + CCM_ANALOG_PFD_480);
	reg |= PFD0_CLKGATE | PFD1_CLKGATE | PFD2_CLKGATE | PFD3_CLKGATE;
	ग_लिखोl_relaxed(reg, anatop_base + CCM_ANALOG_PFD_480);

	/* Make sure PLL5 is disabled */
	reg = पढ़ोl_relaxed(anatop_base + CCM_ANALOG_PLL_VIDEO);
	reg &= ~PLL_ENABLE;
	ग_लिखोl_relaxed(reg, anatop_base + CCM_ANALOG_PLL_VIDEO);
पूर्ण

अटल काष्ठा clk_hw * __init imx6q_obtain_fixed_clk_hw(काष्ठा device_node *np,
							स्थिर अक्षर *name,
							अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk *clk = of_clk_get_by_name(np, name);
	काष्ठा clk_hw *hw;

	अगर (IS_ERR(clk))
		hw = imx_obtain_fixed_घड़ी_hw(name, rate);
	अन्यथा
		hw = __clk_get_hw(clk);

	वापस hw;
पूर्ण

अटल व्योम __init imx6q_घड़ीs_init(काष्ठा device_node *ccm_node)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *anatop_base, *base;
	पूर्णांक ret;

	clk_hw_data = kzalloc(काष्ठा_size(clk_hw_data, hws,
					  IMX6QDL_CLK_END), GFP_KERNEL);
	अगर (WARN_ON(!clk_hw_data))
		वापस;

	clk_hw_data->num = IMX6QDL_CLK_END;
	hws = clk_hw_data->hws;

	hws[IMX6QDL_CLK_DUMMY] = imx_clk_hw_fixed("dummy", 0);

	hws[IMX6QDL_CLK_CKIL] = imx6q_obtain_fixed_clk_hw(ccm_node, "ckil", 0);
	hws[IMX6QDL_CLK_CKIH] = imx6q_obtain_fixed_clk_hw(ccm_node, "ckih1", 0);
	hws[IMX6QDL_CLK_OSC] = imx6q_obtain_fixed_clk_hw(ccm_node, "osc", 0);

	/* Clock source from बाह्यal घड़ी via CLK1/2 PADs */
	hws[IMX6QDL_CLK_ANACLK1] = imx6q_obtain_fixed_clk_hw(ccm_node, "anaclk1", 0);
	hws[IMX6QDL_CLK_ANACLK2] = imx6q_obtain_fixed_clk_hw(ccm_node, "anaclk2", 0);

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx6q-anatop");
	anatop_base = base = of_iomap(np, 0);
	WARN_ON(!base);
	of_node_put(np);

	/* Audio/video PLL post भागiders करो not work on i.MX6q revision 1.0 */
	अगर (clk_on_imx6q() && imx_get_soc_revision() == IMX_CHIP_REVISION_1_0) अणु
		post_भाग_प्रकारable[1].भाग = 1;
		post_भाग_प्रकारable[2].भाग = 1;
		video_भाग_प्रकारable[1].भाग = 1;
		video_भाग_प्रकारable[3].भाग = 1;
	पूर्ण

	hws[IMX6QDL_PLL1_BYPASS_SRC] = imx_clk_hw_mux("pll1_bypass_src", base + 0x00, 14, 2, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6QDL_PLL2_BYPASS_SRC] = imx_clk_hw_mux("pll2_bypass_src", base + 0x30, 14, 2, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6QDL_PLL3_BYPASS_SRC] = imx_clk_hw_mux("pll3_bypass_src", base + 0x10, 14, 2, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6QDL_PLL4_BYPASS_SRC] = imx_clk_hw_mux("pll4_bypass_src", base + 0x70, 14, 2, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6QDL_PLL5_BYPASS_SRC] = imx_clk_hw_mux("pll5_bypass_src", base + 0xa0, 14, 2, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6QDL_PLL6_BYPASS_SRC] = imx_clk_hw_mux("pll6_bypass_src", base + 0xe0, 14, 2, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));
	hws[IMX6QDL_PLL7_BYPASS_SRC] = imx_clk_hw_mux("pll7_bypass_src", base + 0x20, 14, 2, pll_bypass_src_sels, ARRAY_SIZE(pll_bypass_src_sels));

	/*                                    type               name    parent_name        base         भाग_mask */
	hws[IMX6QDL_CLK_PLL1] = imx_clk_hw_pllv3(IMX_PLLV3_SYS,     "pll1", "osc", base + 0x00, 0x7f);
	hws[IMX6QDL_CLK_PLL2] = imx_clk_hw_pllv3(IMX_PLLV3_GENERIC, "pll2", "osc", base + 0x30, 0x1);
	hws[IMX6QDL_CLK_PLL3] = imx_clk_hw_pllv3(IMX_PLLV3_USB,     "pll3", "osc", base + 0x10, 0x3);
	hws[IMX6QDL_CLK_PLL4] = imx_clk_hw_pllv3(IMX_PLLV3_AV,      "pll4", "osc", base + 0x70, 0x7f);
	hws[IMX6QDL_CLK_PLL5] = imx_clk_hw_pllv3(IMX_PLLV3_AV,      "pll5", "osc", base + 0xa0, 0x7f);
	hws[IMX6QDL_CLK_PLL6] = imx_clk_hw_pllv3(IMX_PLLV3_ENET,    "pll6", "osc", base + 0xe0, 0x3);
	hws[IMX6QDL_CLK_PLL7] = imx_clk_hw_pllv3(IMX_PLLV3_USB,     "pll7", "osc", base + 0x20, 0x3);

	hws[IMX6QDL_PLL1_BYPASS] = imx_clk_hw_mux_flags("pll1_bypass", base + 0x00, 16, 1, pll1_bypass_sels, ARRAY_SIZE(pll1_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_PLL2_BYPASS] = imx_clk_hw_mux_flags("pll2_bypass", base + 0x30, 16, 1, pll2_bypass_sels, ARRAY_SIZE(pll2_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_PLL3_BYPASS] = imx_clk_hw_mux_flags("pll3_bypass", base + 0x10, 16, 1, pll3_bypass_sels, ARRAY_SIZE(pll3_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_PLL4_BYPASS] = imx_clk_hw_mux_flags("pll4_bypass", base + 0x70, 16, 1, pll4_bypass_sels, ARRAY_SIZE(pll4_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_PLL5_BYPASS] = imx_clk_hw_mux_flags("pll5_bypass", base + 0xa0, 16, 1, pll5_bypass_sels, ARRAY_SIZE(pll5_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_PLL6_BYPASS] = imx_clk_hw_mux_flags("pll6_bypass", base + 0xe0, 16, 1, pll6_bypass_sels, ARRAY_SIZE(pll6_bypass_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_PLL7_BYPASS] = imx_clk_hw_mux_flags("pll7_bypass", base + 0x20, 16, 1, pll7_bypass_sels, ARRAY_SIZE(pll7_bypass_sels), CLK_SET_RATE_PARENT);

	/* Do not bypass PLLs initially */
	clk_set_parent(hws[IMX6QDL_PLL1_BYPASS]->clk, hws[IMX6QDL_CLK_PLL1]->clk);
	clk_set_parent(hws[IMX6QDL_PLL2_BYPASS]->clk, hws[IMX6QDL_CLK_PLL2]->clk);
	clk_set_parent(hws[IMX6QDL_PLL3_BYPASS]->clk, hws[IMX6QDL_CLK_PLL3]->clk);
	clk_set_parent(hws[IMX6QDL_PLL4_BYPASS]->clk, hws[IMX6QDL_CLK_PLL4]->clk);
	clk_set_parent(hws[IMX6QDL_PLL5_BYPASS]->clk, hws[IMX6QDL_CLK_PLL5]->clk);
	clk_set_parent(hws[IMX6QDL_PLL6_BYPASS]->clk, hws[IMX6QDL_CLK_PLL6]->clk);
	clk_set_parent(hws[IMX6QDL_PLL7_BYPASS]->clk, hws[IMX6QDL_CLK_PLL7]->clk);

	hws[IMX6QDL_CLK_PLL1_SYS]      = imx_clk_hw_gate("pll1_sys",      "pll1_bypass", base + 0x00, 13);
	hws[IMX6QDL_CLK_PLL2_BUS]      = imx_clk_hw_gate("pll2_bus",      "pll2_bypass", base + 0x30, 13);
	hws[IMX6QDL_CLK_PLL3_USB_OTG]  = imx_clk_hw_gate("pll3_usb_otg",  "pll3_bypass", base + 0x10, 13);
	hws[IMX6QDL_CLK_PLL4_AUDIO]    = imx_clk_hw_gate("pll4_audio",    "pll4_bypass", base + 0x70, 13);
	hws[IMX6QDL_CLK_PLL5_VIDEO]    = imx_clk_hw_gate("pll5_video",    "pll5_bypass", base + 0xa0, 13);
	hws[IMX6QDL_CLK_PLL6_ENET]     = imx_clk_hw_gate("pll6_enet",     "pll6_bypass", base + 0xe0, 13);
	hws[IMX6QDL_CLK_PLL7_USB_HOST] = imx_clk_hw_gate("pll7_usb_host", "pll7_bypass", base + 0x20, 13);

	/*
	 * Bit 20 is the reserved and पढ़ो-only bit, we करो this only क्रम:
	 * - Do nothing क्रम usbphy clk_enable/disable
	 * - Keep refcount when करो usbphy clk_enable/disable, in that हाल,
	 * the clk framework may need to enable/disable usbphy's parent
	 */
	hws[IMX6QDL_CLK_USBPHY1] = imx_clk_hw_gate("usbphy1", "pll3_usb_otg", base + 0x10, 20);
	hws[IMX6QDL_CLK_USBPHY2] = imx_clk_hw_gate("usbphy2", "pll7_usb_host", base + 0x20, 20);

	/*
	 * usbphy*_gate needs to be on after प्रणाली boots up, and software
	 * never needs to control it anymore.
	 */
	hws[IMX6QDL_CLK_USBPHY1_GATE] = imx_clk_hw_gate("usbphy1_gate", "dummy", base + 0x10, 6);
	hws[IMX6QDL_CLK_USBPHY2_GATE] = imx_clk_hw_gate("usbphy2_gate", "dummy", base + 0x20, 6);

	/*
	 * The ENET PLL is special in that is has multiple outमाला_दो with
	 * dअगरferent post-भागiders that are all affected by the single bypass
	 * bit, so a single mux bit affects 3 independent branches of the घड़ी
	 * tree. There is no good way to model this in the घड़ी framework and
	 * dynamically changing the bypass bit, will yield unexpected results.
	 * So we treat any configuration that bypasses the ENET PLL as
	 * essentially अटल with the भागider ratios reflecting the bypass
	 * status.
	 *
	 */
	अगर (!pll6_bypassed(ccm_node)) अणु
		hws[IMX6QDL_CLK_SATA_REF] = imx_clk_hw_fixed_factor("sata_ref", "pll6_enet", 1, 5);
		hws[IMX6QDL_CLK_PCIE_REF] = imx_clk_hw_fixed_factor("pcie_ref", "pll6_enet", 1, 4);
		hws[IMX6QDL_CLK_ENET_REF] = clk_hw_रेजिस्टर_भागider_table(शून्य, "enet_ref", "pll6_enet", 0,
						base + 0xe0, 0, 2, 0, clk_enet_ref_table,
						&imx_ccm_lock);
	पूर्ण अन्यथा अणु
		hws[IMX6QDL_CLK_SATA_REF] = imx_clk_hw_fixed_factor("sata_ref", "pll6_enet", 1, 1);
		hws[IMX6QDL_CLK_PCIE_REF] = imx_clk_hw_fixed_factor("pcie_ref", "pll6_enet", 1, 1);
		hws[IMX6QDL_CLK_ENET_REF] = imx_clk_hw_fixed_factor("enet_ref", "pll6_enet", 1, 1);
	पूर्ण

	hws[IMX6QDL_CLK_SATA_REF_100M] = imx_clk_hw_gate("sata_ref_100m", "sata_ref", base + 0xe0, 20);
	hws[IMX6QDL_CLK_PCIE_REF_125M] = imx_clk_hw_gate("pcie_ref_125m", "pcie_ref", base + 0xe0, 19);

	hws[IMX6QDL_CLK_LVDS1_SEL] = imx_clk_hw_mux("lvds1_sel", base + 0x160, 0, 5, lvds_sels, ARRAY_SIZE(lvds_sels));
	hws[IMX6QDL_CLK_LVDS2_SEL] = imx_clk_hw_mux("lvds2_sel", base + 0x160, 5, 5, lvds_sels, ARRAY_SIZE(lvds_sels));

	/*
	 * lvds1_gate and lvds2_gate are pseuकरो-gates.  Both can be
	 * independently configured as घड़ी inमाला_दो or outमाला_दो.  We treat
	 * the "output_enable" bit as a gate, even though it's really just
	 * enabling घड़ी output. Initially the gate bits are cleared, as
	 * otherwise the exclusive configuration माला_लो locked in the setup करोne
	 * by software running beक्रमe the घड़ी driver, with no way to change
	 * it.
	 */
	ग_लिखोl(पढ़ोl(base + 0x160) & ~0x3c00, base + 0x160);
	hws[IMX6QDL_CLK_LVDS1_GATE] = imx_clk_hw_gate_exclusive("lvds1_gate", "lvds1_sel", base + 0x160, 10, BIT(12));
	hws[IMX6QDL_CLK_LVDS2_GATE] = imx_clk_hw_gate_exclusive("lvds2_gate", "lvds2_sel", base + 0x160, 11, BIT(13));

	hws[IMX6QDL_CLK_LVDS1_IN] = imx_clk_hw_gate_exclusive("lvds1_in", "anaclk1", base + 0x160, 12, BIT(10));
	hws[IMX6QDL_CLK_LVDS2_IN] = imx_clk_hw_gate_exclusive("lvds2_in", "anaclk2", base + 0x160, 13, BIT(11));

	/*                                            name              parent_name        reg       idx */
	hws[IMX6QDL_CLK_PLL2_PFD0_352M] = imx_clk_hw_pfd("pll2_pfd0_352m", "pll2_bus",     base + 0x100, 0);
	hws[IMX6QDL_CLK_PLL2_PFD1_594M] = imx_clk_hw_pfd("pll2_pfd1_594m", "pll2_bus",     base + 0x100, 1);
	hws[IMX6QDL_CLK_PLL2_PFD2_396M] = imx_clk_hw_pfd("pll2_pfd2_396m", "pll2_bus",     base + 0x100, 2);
	hws[IMX6QDL_CLK_PLL3_PFD0_720M] = imx_clk_hw_pfd("pll3_pfd0_720m", "pll3_usb_otg", base + 0xf0,  0);
	hws[IMX6QDL_CLK_PLL3_PFD1_540M] = imx_clk_hw_pfd("pll3_pfd1_540m", "pll3_usb_otg", base + 0xf0,  1);
	hws[IMX6QDL_CLK_PLL3_PFD2_508M] = imx_clk_hw_pfd("pll3_pfd2_508m", "pll3_usb_otg", base + 0xf0,  2);
	hws[IMX6QDL_CLK_PLL3_PFD3_454M] = imx_clk_hw_pfd("pll3_pfd3_454m", "pll3_usb_otg", base + 0xf0,  3);

	/*                                                name         parent_name     mult भाग */
	hws[IMX6QDL_CLK_PLL2_198M] = imx_clk_hw_fixed_factor("pll2_198m", "pll2_pfd2_396m", 1, 2);
	hws[IMX6QDL_CLK_PLL3_120M] = imx_clk_hw_fixed_factor("pll3_120m", "pll3_usb_otg",   1, 4);
	hws[IMX6QDL_CLK_PLL3_80M]  = imx_clk_hw_fixed_factor("pll3_80m",  "pll3_usb_otg",   1, 6);
	hws[IMX6QDL_CLK_PLL3_60M]  = imx_clk_hw_fixed_factor("pll3_60m",  "pll3_usb_otg",   1, 8);
	hws[IMX6QDL_CLK_TWD]       = imx_clk_hw_fixed_factor("twd",       "arm",            1, 2);
	hws[IMX6QDL_CLK_GPT_3M]    = imx_clk_hw_fixed_factor("gpt_3m",    "osc",            1, 8);
	hws[IMX6QDL_CLK_VIDEO_27M] = imx_clk_hw_fixed_factor("video_27m", "pll3_pfd1_540m", 1, 20);
	अगर (clk_on_imx6dl() || clk_on_imx6qp()) अणु
		hws[IMX6QDL_CLK_GPU2D_AXI] = imx_clk_hw_fixed_factor("gpu2d_axi", "mmdc_ch0_axi_podf", 1, 1);
		hws[IMX6QDL_CLK_GPU3D_AXI] = imx_clk_hw_fixed_factor("gpu3d_axi", "mmdc_ch0_axi_podf", 1, 1);
	पूर्ण

	hws[IMX6QDL_CLK_PLL4_POST_DIV] = clk_hw_रेजिस्टर_भागider_table(शून्य, "pll4_post_div", "pll4_audio", CLK_SET_RATE_PARENT, base + 0x70, 19, 2, 0, post_भाग_प्रकारable, &imx_ccm_lock);
	अगर (clk_on_imx6q() || clk_on_imx6qp())
		hws[IMX6QDL_CLK_PLL4_AUDIO_DIV] = imx_clk_hw_fixed_factor("pll4_audio_div", "pll4_post_div", 1, 1);
	अन्यथा
		hws[IMX6QDL_CLK_PLL4_AUDIO_DIV] = clk_hw_रेजिस्टर_भागider(शून्य, "pll4_audio_div", "pll4_post_div", CLK_SET_RATE_PARENT, base + 0x170, 15, 1, 0, &imx_ccm_lock);
	hws[IMX6QDL_CLK_PLL5_POST_DIV] = clk_hw_रेजिस्टर_भागider_table(शून्य, "pll5_post_div", "pll5_video", CLK_SET_RATE_PARENT, base + 0xa0, 19, 2, 0, post_भाग_प्रकारable, &imx_ccm_lock);
	hws[IMX6QDL_CLK_PLL5_VIDEO_DIV] = clk_hw_रेजिस्टर_भागider_table(शून्य, "pll5_video_div", "pll5_post_div", CLK_SET_RATE_PARENT, base + 0x170, 30, 2, 0, video_भाग_प्रकारable, &imx_ccm_lock);

	np = ccm_node;
	base = of_iomap(np, 0);
	WARN_ON(!base);

	/*                                              name                reg       shअगरt width parent_names     num_parents */
	hws[IMX6QDL_CLK_STEP]             = imx_clk_hw_mux("step",	            base + 0xc,  8,  1, step_sels,	   ARRAY_SIZE(step_sels));
	hws[IMX6QDL_CLK_PLL1_SW]          = imx_clk_hw_mux("pll1_sw",	    base + 0xc,  2,  1, pll1_sw_sels,      ARRAY_SIZE(pll1_sw_sels));
	hws[IMX6QDL_CLK_PERIPH_PRE]       = imx_clk_hw_mux("periph_pre",       base + 0x18, 18, 2, periph_pre_sels,   ARRAY_SIZE(periph_pre_sels));
	hws[IMX6QDL_CLK_PERIPH2_PRE]      = imx_clk_hw_mux("periph2_pre",      base + 0x18, 21, 2, periph_pre_sels,   ARRAY_SIZE(periph_pre_sels));
	hws[IMX6QDL_CLK_PERIPH_CLK2_SEL]  = imx_clk_hw_mux("periph_clk2_sel",  base + 0x18, 12, 2, periph_clk2_sels,  ARRAY_SIZE(periph_clk2_sels));
	hws[IMX6QDL_CLK_PERIPH2_CLK2_SEL] = imx_clk_hw_mux("periph2_clk2_sel", base + 0x18, 20, 1, periph2_clk2_sels, ARRAY_SIZE(periph2_clk2_sels));
	hws[IMX6QDL_CLK_AXI_SEL]          = imx_clk_hw_mux("axi_sel",          base + 0x14, 6,  2, axi_sels,          ARRAY_SIZE(axi_sels));
	hws[IMX6QDL_CLK_ESAI_SEL]         = imx_clk_hw_mux("esai_sel",         base + 0x20, 19, 2, audio_sels,        ARRAY_SIZE(audio_sels));
	hws[IMX6QDL_CLK_ASRC_SEL]         = imx_clk_hw_mux("asrc_sel",         base + 0x30, 7,  2, audio_sels,        ARRAY_SIZE(audio_sels));
	hws[IMX6QDL_CLK_SPDIF_SEL]        = imx_clk_hw_mux("spdif_sel",        base + 0x30, 20, 2, audio_sels,        ARRAY_SIZE(audio_sels));
	अगर (clk_on_imx6q()) अणु
		hws[IMX6QDL_CLK_GPU2D_AXI]        = imx_clk_hw_mux("gpu2d_axi",        base + 0x18, 0,  1, gpu_axi_sels,      ARRAY_SIZE(gpu_axi_sels));
		hws[IMX6QDL_CLK_GPU3D_AXI]        = imx_clk_hw_mux("gpu3d_axi",        base + 0x18, 1,  1, gpu_axi_sels,      ARRAY_SIZE(gpu_axi_sels));
	पूर्ण
	अगर (clk_on_imx6qp()) अणु
		hws[IMX6QDL_CLK_CAN_SEL]   = imx_clk_hw_mux("can_sel",	base + 0x20, 8,  2, can_sels, ARRAY_SIZE(can_sels));
		hws[IMX6QDL_CLK_ECSPI_SEL] = imx_clk_hw_mux("ecspi_sel",	base + 0x38, 18, 1, ecspi_sels,  ARRAY_SIZE(ecspi_sels));
		hws[IMX6QDL_CLK_IPG_PER_SEL] = imx_clk_hw_mux("ipg_per_sel", base + 0x1c, 6, 1, ipg_per_sels, ARRAY_SIZE(ipg_per_sels));
		hws[IMX6QDL_CLK_UART_SEL] = imx_clk_hw_mux("uart_sel", base + 0x24, 6, 1, uart_sels, ARRAY_SIZE(uart_sels));
		hws[IMX6QDL_CLK_GPU2D_CORE_SEL] = imx_clk_hw_mux("gpu2d_core_sel", base + 0x18, 16, 2, gpu2d_core_sels_2, ARRAY_SIZE(gpu2d_core_sels_2));
	पूर्ण अन्यथा अगर (clk_on_imx6dl()) अणु
		hws[IMX6QDL_CLK_MLB_SEL] = imx_clk_hw_mux("mlb_sel",   base + 0x18, 16, 2, gpu2d_core_sels,   ARRAY_SIZE(gpu2d_core_sels));
	पूर्ण अन्यथा अणु
		hws[IMX6QDL_CLK_GPU2D_CORE_SEL] = imx_clk_hw_mux("gpu2d_core_sel",   base + 0x18, 16, 2, gpu2d_core_sels,   ARRAY_SIZE(gpu2d_core_sels));
	पूर्ण
	hws[IMX6QDL_CLK_GPU3D_CORE_SEL]   = imx_clk_hw_mux("gpu3d_core_sel",   base + 0x18, 4,  2, gpu3d_core_sels,   ARRAY_SIZE(gpu3d_core_sels));
	अगर (clk_on_imx6dl())
		hws[IMX6QDL_CLK_GPU2D_CORE_SEL] = imx_clk_hw_mux("gpu2d_core_sel", base + 0x18, 8,  2, gpu3d_shader_sels, ARRAY_SIZE(gpu3d_shader_sels));
	अन्यथा
		hws[IMX6QDL_CLK_GPU3D_SHADER_SEL] = imx_clk_hw_mux("gpu3d_shader_sel", base + 0x18, 8,  2, gpu3d_shader_sels, ARRAY_SIZE(gpu3d_shader_sels));
	hws[IMX6QDL_CLK_IPU1_SEL]         = imx_clk_hw_mux("ipu1_sel",         base + 0x3c, 9,  2, ipu_sels,          ARRAY_SIZE(ipu_sels));
	hws[IMX6QDL_CLK_IPU2_SEL]         = imx_clk_hw_mux("ipu2_sel",         base + 0x3c, 14, 2, ipu_sels,          ARRAY_SIZE(ipu_sels));

	disable_anatop_घड़ीs(anatop_base);

	imx_mmdc_mask_handshake(base, 1);

	अगर (clk_on_imx6qp()) अणु
		hws[IMX6QDL_CLK_LDB_DI0_SEL]      = imx_clk_hw_mux_flags("ldb_di0_sel", base + 0x2c, 9,  3, ldb_di_sels,      ARRAY_SIZE(ldb_di_sels), CLK_SET_RATE_PARENT);
		hws[IMX6QDL_CLK_LDB_DI1_SEL]      = imx_clk_hw_mux_flags("ldb_di1_sel", base + 0x2c, 12, 3, ldb_di_sels,      ARRAY_SIZE(ldb_di_sels), CLK_SET_RATE_PARENT);
	पूर्ण अन्यथा अणु
		/*
		 * The LDB_DI0/1_SEL muxes are रेजिस्टरed पढ़ो-only due to a hardware
		 * bug. Set the muxes to the requested values beक्रमe रेजिस्टरing the
		 * ldb_di_sel घड़ीs.
		 */
		init_ldb_clks(np, base);

		hws[IMX6QDL_CLK_LDB_DI0_SEL]      = imx_clk_hw_mux_ldb("ldb_di0_sel", base + 0x2c, 9,  3, ldb_di_sels,      ARRAY_SIZE(ldb_di_sels));
		hws[IMX6QDL_CLK_LDB_DI1_SEL]      = imx_clk_hw_mux_ldb("ldb_di1_sel", base + 0x2c, 12, 3, ldb_di_sels,      ARRAY_SIZE(ldb_di_sels));
	पूर्ण

	hws[IMX6QDL_CLK_IPU1_DI0_PRE_SEL] = imx_clk_hw_mux_flags("ipu1_di0_pre_sel", base + 0x34, 6,  3, ipu_di_pre_sels,   ARRAY_SIZE(ipu_di_pre_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_CLK_IPU1_DI1_PRE_SEL] = imx_clk_hw_mux_flags("ipu1_di1_pre_sel", base + 0x34, 15, 3, ipu_di_pre_sels,   ARRAY_SIZE(ipu_di_pre_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_CLK_IPU2_DI0_PRE_SEL] = imx_clk_hw_mux_flags("ipu2_di0_pre_sel", base + 0x38, 6,  3, ipu_di_pre_sels,   ARRAY_SIZE(ipu_di_pre_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_CLK_IPU2_DI1_PRE_SEL] = imx_clk_hw_mux_flags("ipu2_di1_pre_sel", base + 0x38, 15, 3, ipu_di_pre_sels,   ARRAY_SIZE(ipu_di_pre_sels), CLK_SET_RATE_PARENT);
	hws[IMX6QDL_CLK_HSI_TX_SEL]       = imx_clk_hw_mux("hsi_tx_sel",       base + 0x30, 28, 1, hsi_tx_sels,       ARRAY_SIZE(hsi_tx_sels));
	hws[IMX6QDL_CLK_PCIE_AXI_SEL]     = imx_clk_hw_mux("pcie_axi_sel",     base + 0x18, 10, 1, pcie_axi_sels,     ARRAY_SIZE(pcie_axi_sels));

	अगर (clk_on_imx6qp()) अणु
		hws[IMX6QDL_CLK_IPU1_DI0_SEL]     = imx_clk_hw_mux_flags("ipu1_di0_sel",     base + 0x34, 0,  3, ipu1_di0_sels_2,     ARRAY_SIZE(ipu1_di0_sels_2), CLK_SET_RATE_PARENT);
		hws[IMX6QDL_CLK_IPU1_DI1_SEL]     = imx_clk_hw_mux_flags("ipu1_di1_sel",     base + 0x34, 9,  3, ipu1_di1_sels_2,     ARRAY_SIZE(ipu1_di1_sels_2), CLK_SET_RATE_PARENT);
		hws[IMX6QDL_CLK_IPU2_DI0_SEL]     = imx_clk_hw_mux_flags("ipu2_di0_sel",     base + 0x38, 0,  3, ipu2_di0_sels_2,     ARRAY_SIZE(ipu2_di0_sels_2), CLK_SET_RATE_PARENT);
		hws[IMX6QDL_CLK_IPU2_DI1_SEL]     = imx_clk_hw_mux_flags("ipu2_di1_sel",     base + 0x38, 9,  3, ipu2_di1_sels_2,     ARRAY_SIZE(ipu2_di1_sels_2), CLK_SET_RATE_PARENT);
		hws[IMX6QDL_CLK_SSI1_SEL]         = imx_clk_hw_mux("ssi1_sel",   base + 0x1c, 10, 2, ssi_sels,          ARRAY_SIZE(ssi_sels));
		hws[IMX6QDL_CLK_SSI2_SEL]         = imx_clk_hw_mux("ssi2_sel",   base + 0x1c, 12, 2, ssi_sels,          ARRAY_SIZE(ssi_sels));
		hws[IMX6QDL_CLK_SSI3_SEL]         = imx_clk_hw_mux("ssi3_sel",   base + 0x1c, 14, 2, ssi_sels,          ARRAY_SIZE(ssi_sels));
		hws[IMX6QDL_CLK_USDHC1_SEL]       = imx_clk_hw_mux("usdhc1_sel", base + 0x1c, 16, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels));
		hws[IMX6QDL_CLK_USDHC2_SEL]       = imx_clk_hw_mux("usdhc2_sel", base + 0x1c, 17, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels));
		hws[IMX6QDL_CLK_USDHC3_SEL]       = imx_clk_hw_mux("usdhc3_sel", base + 0x1c, 18, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels));
		hws[IMX6QDL_CLK_USDHC4_SEL]       = imx_clk_hw_mux("usdhc4_sel", base + 0x1c, 19, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels));
		hws[IMX6QDL_CLK_ENFC_SEL]         = imx_clk_hw_mux("enfc_sel",         base + 0x2c, 15, 3, enfc_sels_2,         ARRAY_SIZE(enfc_sels_2));
		hws[IMX6QDL_CLK_EIM_SEL]          = imx_clk_hw_mux("eim_sel",      base + 0x1c, 27, 2, eim_sels,        ARRAY_SIZE(eim_sels));
		hws[IMX6QDL_CLK_EIM_SLOW_SEL]     = imx_clk_hw_mux("eim_slow_sel", base + 0x1c, 29, 2, eim_slow_sels,   ARRAY_SIZE(eim_slow_sels));
		hws[IMX6QDL_CLK_PRE_AXI]	  = imx_clk_hw_mux("pre_axi",	base + 0x18, 1,  1, pre_axi_sels,    ARRAY_SIZE(pre_axi_sels));
	पूर्ण अन्यथा अणु
		hws[IMX6QDL_CLK_IPU1_DI0_SEL]     = imx_clk_hw_mux_flags("ipu1_di0_sel",     base + 0x34, 0,  3, ipu1_di0_sels,     ARRAY_SIZE(ipu1_di0_sels), CLK_SET_RATE_PARENT);
		hws[IMX6QDL_CLK_IPU1_DI1_SEL]     = imx_clk_hw_mux_flags("ipu1_di1_sel",     base + 0x34, 9,  3, ipu1_di1_sels,     ARRAY_SIZE(ipu1_di1_sels), CLK_SET_RATE_PARENT);
		hws[IMX6QDL_CLK_IPU2_DI0_SEL]     = imx_clk_hw_mux_flags("ipu2_di0_sel",     base + 0x38, 0,  3, ipu2_di0_sels,     ARRAY_SIZE(ipu2_di0_sels), CLK_SET_RATE_PARENT);
		hws[IMX6QDL_CLK_IPU2_DI1_SEL]     = imx_clk_hw_mux_flags("ipu2_di1_sel",     base + 0x38, 9,  3, ipu2_di1_sels,     ARRAY_SIZE(ipu2_di1_sels), CLK_SET_RATE_PARENT);
		hws[IMX6QDL_CLK_SSI1_SEL]         = imx_clk_hw_fixup_mux("ssi1_sel",   base + 0x1c, 10, 2, ssi_sels,          ARRAY_SIZE(ssi_sels), imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_SSI2_SEL]         = imx_clk_hw_fixup_mux("ssi2_sel",   base + 0x1c, 12, 2, ssi_sels,          ARRAY_SIZE(ssi_sels), imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_SSI3_SEL]         = imx_clk_hw_fixup_mux("ssi3_sel",   base + 0x1c, 14, 2, ssi_sels,          ARRAY_SIZE(ssi_sels), imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_USDHC1_SEL]       = imx_clk_hw_fixup_mux("usdhc1_sel", base + 0x1c, 16, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels), imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_USDHC2_SEL]       = imx_clk_hw_fixup_mux("usdhc2_sel", base + 0x1c, 17, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels), imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_USDHC3_SEL]       = imx_clk_hw_fixup_mux("usdhc3_sel", base + 0x1c, 18, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels), imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_USDHC4_SEL]       = imx_clk_hw_fixup_mux("usdhc4_sel", base + 0x1c, 19, 1, usdhc_sels,        ARRAY_SIZE(usdhc_sels), imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_ENFC_SEL]         = imx_clk_hw_mux("enfc_sel",         base + 0x2c, 16, 2, enfc_sels,         ARRAY_SIZE(enfc_sels));
		hws[IMX6QDL_CLK_EIM_SEL]          = imx_clk_hw_fixup_mux("eim_sel",      base + 0x1c, 27, 2, eim_sels,        ARRAY_SIZE(eim_sels), imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_EIM_SLOW_SEL]     = imx_clk_hw_fixup_mux("eim_slow_sel", base + 0x1c, 29, 2, eim_slow_sels,   ARRAY_SIZE(eim_slow_sels), imx_cscmr1_fixup);
	पूर्ण

	hws[IMX6QDL_CLK_VDO_AXI_SEL]      = imx_clk_hw_mux("vdo_axi_sel",      base + 0x18, 11, 1, vकरो_axi_sels,      ARRAY_SIZE(vकरो_axi_sels));
	hws[IMX6QDL_CLK_VPU_AXI_SEL]      = imx_clk_hw_mux("vpu_axi_sel",      base + 0x18, 14, 2, vpu_axi_sels,      ARRAY_SIZE(vpu_axi_sels));
	hws[IMX6QDL_CLK_CKO1_SEL]         = imx_clk_hw_mux("cko1_sel",         base + 0x60, 0,  4, cko1_sels,         ARRAY_SIZE(cko1_sels));
	hws[IMX6QDL_CLK_CKO2_SEL]         = imx_clk_hw_mux("cko2_sel",         base + 0x60, 16, 5, cko2_sels,         ARRAY_SIZE(cko2_sels));
	hws[IMX6QDL_CLK_CKO]              = imx_clk_hw_mux("cko",              base + 0x60, 8, 1,  cko_sels,          ARRAY_SIZE(cko_sels));

	/*                                          name         reg      shअगरt width busy: reg, shअगरt parent_names  num_parents */
	hws[IMX6QDL_CLK_PERIPH]  = imx_clk_hw_busy_mux("periph",  base + 0x14, 25,  1,   base + 0x48, 5,  periph_sels,  ARRAY_SIZE(periph_sels));
	hws[IMX6QDL_CLK_PERIPH2] = imx_clk_hw_busy_mux("periph2", base + 0x14, 26,  1,   base + 0x48, 3,  periph2_sels, ARRAY_SIZE(periph2_sels));

	/*                                                  name                parent_name          reg       shअगरt width */
	hws[IMX6QDL_CLK_PERIPH_CLK2]      = imx_clk_hw_भागider("periph_clk2",      "periph_clk2_sel",   base + 0x14, 27, 3);
	hws[IMX6QDL_CLK_PERIPH2_CLK2]     = imx_clk_hw_भागider("periph2_clk2",     "periph2_clk2_sel",  base + 0x14, 0,  3);
	hws[IMX6QDL_CLK_IPG]              = imx_clk_hw_भागider("ipg",              "ahb",               base + 0x14, 8,  2);
	hws[IMX6QDL_CLK_ESAI_PRED]        = imx_clk_hw_भागider("esai_pred",        "esai_sel",          base + 0x28, 9,  3);
	hws[IMX6QDL_CLK_ESAI_PODF]        = imx_clk_hw_भागider("esai_podf",        "esai_pred",         base + 0x28, 25, 3);
	hws[IMX6QDL_CLK_ASRC_PRED]        = imx_clk_hw_भागider("asrc_pred",        "asrc_sel",          base + 0x30, 12, 3);
	hws[IMX6QDL_CLK_ASRC_PODF]        = imx_clk_hw_भागider("asrc_podf",        "asrc_pred",         base + 0x30, 9,  3);
	hws[IMX6QDL_CLK_SPDIF_PRED]       = imx_clk_hw_भागider("spdif_pred",       "spdif_sel",         base + 0x30, 25, 3);
	hws[IMX6QDL_CLK_SPDIF_PODF]       = imx_clk_hw_भागider("spdif_podf",       "spdif_pred",        base + 0x30, 22, 3);

	अगर (clk_on_imx6qp()) अणु
		hws[IMX6QDL_CLK_IPG_PER] = imx_clk_hw_भागider("ipg_per", "ipg_per_sel", base + 0x1c, 0, 6);
		hws[IMX6QDL_CLK_ECSPI_ROOT] = imx_clk_hw_भागider("ecspi_root", "ecspi_sel", base + 0x38, 19, 6);
		hws[IMX6QDL_CLK_CAN_ROOT] = imx_clk_hw_भागider("can_root", "can_sel", base + 0x20, 2, 6);
		hws[IMX6QDL_CLK_UART_SERIAL_PODF] = imx_clk_hw_भागider("uart_serial_podf", "uart_sel", base + 0x24, 0, 6);
		hws[IMX6QDL_CLK_LDB_DI0_DIV_3_5] = imx_clk_hw_fixed_factor("ldb_di0_div_3_5", "ldb_di0", 2, 7);
		hws[IMX6QDL_CLK_LDB_DI1_DIV_3_5] = imx_clk_hw_fixed_factor("ldb_di1_div_3_5", "ldb_di1", 2, 7);
	पूर्ण अन्यथा अणु
		hws[IMX6QDL_CLK_ECSPI_ROOT] = imx_clk_hw_भागider("ecspi_root", "pll3_60m", base + 0x38, 19, 6);
		hws[IMX6QDL_CLK_CAN_ROOT] = imx_clk_hw_भागider("can_root", "pll3_60m", base + 0x20, 2, 6);
		hws[IMX6QDL_CLK_IPG_PER] = imx_clk_hw_fixup_भागider("ipg_per", "ipg", base + 0x1c, 0, 6, imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_UART_SERIAL_PODF] = imx_clk_hw_भागider("uart_serial_podf", "pll3_80m",          base + 0x24, 0,  6);
		hws[IMX6QDL_CLK_LDB_DI0_DIV_3_5] = imx_clk_hw_fixed_factor("ldb_di0_div_3_5", "ldb_di0_sel", 2, 7);
		hws[IMX6QDL_CLK_LDB_DI1_DIV_3_5] = imx_clk_hw_fixed_factor("ldb_di1_div_3_5", "ldb_di1_sel", 2, 7);
	पूर्ण

	अगर (clk_on_imx6dl())
		hws[IMX6QDL_CLK_MLB_PODF]  = imx_clk_hw_भागider("mlb_podf",  "mlb_sel",    base + 0x18, 23, 3);
	अन्यथा
		hws[IMX6QDL_CLK_GPU2D_CORE_PODF]  = imx_clk_hw_भागider("gpu2d_core_podf",  "gpu2d_core_sel",    base + 0x18, 23, 3);
	hws[IMX6QDL_CLK_GPU3D_CORE_PODF]  = imx_clk_hw_भागider("gpu3d_core_podf",  "gpu3d_core_sel",    base + 0x18, 26, 3);
	अगर (clk_on_imx6dl())
		hws[IMX6QDL_CLK_GPU2D_CORE_PODF]  = imx_clk_hw_भागider("gpu2d_core_podf",     "gpu2d_core_sel",  base + 0x18, 29, 3);
	अन्यथा
		hws[IMX6QDL_CLK_GPU3D_SHADER]     = imx_clk_hw_भागider("gpu3d_shader",     "gpu3d_shader_sel",  base + 0x18, 29, 3);
	hws[IMX6QDL_CLK_IPU1_PODF]        = imx_clk_hw_भागider("ipu1_podf",        "ipu1_sel",          base + 0x3c, 11, 3);
	hws[IMX6QDL_CLK_IPU2_PODF]        = imx_clk_hw_भागider("ipu2_podf",        "ipu2_sel",          base + 0x3c, 16, 3);
	hws[IMX6QDL_CLK_LDB_DI0_PODF]     = imx_clk_hw_भागider_flags("ldb_di0_podf", "ldb_di0_div_3_5", base + 0x20, 10, 1, 0);
	hws[IMX6QDL_CLK_LDB_DI1_PODF]     = imx_clk_hw_भागider_flags("ldb_di1_podf", "ldb_di1_div_3_5", base + 0x20, 11, 1, 0);
	hws[IMX6QDL_CLK_IPU1_DI0_PRE]     = imx_clk_hw_भागider("ipu1_di0_pre",     "ipu1_di0_pre_sel",  base + 0x34, 3,  3);
	hws[IMX6QDL_CLK_IPU1_DI1_PRE]     = imx_clk_hw_भागider("ipu1_di1_pre",     "ipu1_di1_pre_sel",  base + 0x34, 12, 3);
	hws[IMX6QDL_CLK_IPU2_DI0_PRE]     = imx_clk_hw_भागider("ipu2_di0_pre",     "ipu2_di0_pre_sel",  base + 0x38, 3,  3);
	hws[IMX6QDL_CLK_IPU2_DI1_PRE]     = imx_clk_hw_भागider("ipu2_di1_pre",     "ipu2_di1_pre_sel",  base + 0x38, 12, 3);
	hws[IMX6QDL_CLK_HSI_TX_PODF]      = imx_clk_hw_भागider("hsi_tx_podf",      "hsi_tx_sel",        base + 0x30, 29, 3);
	hws[IMX6QDL_CLK_SSI1_PRED]        = imx_clk_hw_भागider("ssi1_pred",        "ssi1_sel",          base + 0x28, 6,  3);
	hws[IMX6QDL_CLK_SSI1_PODF]        = imx_clk_hw_भागider("ssi1_podf",        "ssi1_pred",         base + 0x28, 0,  6);
	hws[IMX6QDL_CLK_SSI2_PRED]        = imx_clk_hw_भागider("ssi2_pred",        "ssi2_sel",          base + 0x2c, 6,  3);
	hws[IMX6QDL_CLK_SSI2_PODF]        = imx_clk_hw_भागider("ssi2_podf",        "ssi2_pred",         base + 0x2c, 0,  6);
	hws[IMX6QDL_CLK_SSI3_PRED]        = imx_clk_hw_भागider("ssi3_pred",        "ssi3_sel",          base + 0x28, 22, 3);
	hws[IMX6QDL_CLK_SSI3_PODF]        = imx_clk_hw_भागider("ssi3_podf",        "ssi3_pred",         base + 0x28, 16, 6);
	hws[IMX6QDL_CLK_USDHC1_PODF]      = imx_clk_hw_भागider("usdhc1_podf",      "usdhc1_sel",        base + 0x24, 11, 3);
	hws[IMX6QDL_CLK_USDHC2_PODF]      = imx_clk_hw_भागider("usdhc2_podf",      "usdhc2_sel",        base + 0x24, 16, 3);
	hws[IMX6QDL_CLK_USDHC3_PODF]      = imx_clk_hw_भागider("usdhc3_podf",      "usdhc3_sel",        base + 0x24, 19, 3);
	hws[IMX6QDL_CLK_USDHC4_PODF]      = imx_clk_hw_भागider("usdhc4_podf",      "usdhc4_sel",        base + 0x24, 22, 3);
	hws[IMX6QDL_CLK_ENFC_PRED]        = imx_clk_hw_भागider("enfc_pred",        "enfc_sel",          base + 0x2c, 18, 3);
	hws[IMX6QDL_CLK_ENFC_PODF]        = imx_clk_hw_भागider("enfc_podf",        "enfc_pred",         base + 0x2c, 21, 6);
	अगर (clk_on_imx6qp()) अणु
		hws[IMX6QDL_CLK_EIM_PODF]         = imx_clk_hw_भागider("eim_podf",   "eim_sel",           base + 0x1c, 20, 3);
		hws[IMX6QDL_CLK_EIM_SLOW_PODF]    = imx_clk_hw_भागider("eim_slow_podf", "eim_slow_sel",   base + 0x1c, 23, 3);
	पूर्ण अन्यथा अणु
		hws[IMX6QDL_CLK_EIM_PODF]         = imx_clk_hw_fixup_भागider("eim_podf",   "eim_sel",           base + 0x1c, 20, 3, imx_cscmr1_fixup);
		hws[IMX6QDL_CLK_EIM_SLOW_PODF]    = imx_clk_hw_fixup_भागider("eim_slow_podf", "eim_slow_sel",   base + 0x1c, 23, 3, imx_cscmr1_fixup);
	पूर्ण

	hws[IMX6QDL_CLK_VPU_AXI_PODF]     = imx_clk_hw_भागider("vpu_axi_podf",     "vpu_axi_sel",       base + 0x24, 25, 3);
	hws[IMX6QDL_CLK_CKO1_PODF]        = imx_clk_hw_भागider("cko1_podf",        "cko1_sel",          base + 0x60, 4,  3);
	hws[IMX6QDL_CLK_CKO2_PODF]        = imx_clk_hw_भागider("cko2_podf",        "cko2_sel",          base + 0x60, 21, 3);

	/*                                                        name                 parent_name    reg        shअगरt width busy: reg, shअगरt */
	hws[IMX6QDL_CLK_AXI]               = imx_clk_hw_busy_भागider("axi",               "axi_sel",     base + 0x14, 16,  3,   base + 0x48, 0);
	hws[IMX6QDL_CLK_MMDC_CH0_AXI_PODF] = imx_clk_hw_busy_भागider("mmdc_ch0_axi_podf", "periph",      base + 0x14, 19,  3,   base + 0x48, 4);
	अगर (clk_on_imx6qp()) अणु
		hws[IMX6QDL_CLK_MMDC_CH1_AXI_CG] = imx_clk_hw_gate("mmdc_ch1_axi_cg", "periph2", base + 0x4, 18);
		hws[IMX6QDL_CLK_MMDC_CH1_AXI_PODF] = imx_clk_hw_busy_भागider("mmdc_ch1_axi_podf", "mmdc_ch1_axi_cg", base + 0x14, 3, 3, base + 0x48, 2);
	पूर्ण अन्यथा अणु
		hws[IMX6QDL_CLK_MMDC_CH1_AXI_PODF] = imx_clk_hw_busy_भागider("mmdc_ch1_axi_podf", "periph2",     base + 0x14, 3,   3,   base + 0x48, 2);
	पूर्ण
	hws[IMX6QDL_CLK_ARM]               = imx_clk_hw_busy_भागider("arm",               "pll1_sw",     base + 0x10, 0,   3,   base + 0x48, 16);
	hws[IMX6QDL_CLK_AHB]               = imx_clk_hw_busy_भागider("ahb",               "periph",      base + 0x14, 10,  3,   base + 0x48, 1);

	/*                                            name             parent_name          reg         shअगरt */
	hws[IMX6QDL_CLK_APBH_DMA]     = imx_clk_hw_gate2("apbh_dma",      "usdhc3",            base + 0x68, 4);
	hws[IMX6QDL_CLK_ASRC]         = imx_clk_hw_gate2_shared("asrc",         "asrc_podf",   base + 0x68, 6, &share_count_asrc);
	hws[IMX6QDL_CLK_ASRC_IPG]     = imx_clk_hw_gate2_shared("asrc_ipg",     "ahb",         base + 0x68, 6, &share_count_asrc);
	hws[IMX6QDL_CLK_ASRC_MEM]     = imx_clk_hw_gate2_shared("asrc_mem",     "ahb",         base + 0x68, 6, &share_count_asrc);
	hws[IMX6QDL_CLK_CAAM_MEM]     = imx_clk_hw_gate2("caam_mem",      "ahb",               base + 0x68, 8);
	hws[IMX6QDL_CLK_CAAM_ACLK]    = imx_clk_hw_gate2("caam_aclk",     "ahb",               base + 0x68, 10);
	hws[IMX6QDL_CLK_CAAM_IPG]     = imx_clk_hw_gate2("caam_ipg",      "ipg",               base + 0x68, 12);
	hws[IMX6QDL_CLK_CAN1_IPG]     = imx_clk_hw_gate2("can1_ipg",      "ipg",               base + 0x68, 14);
	hws[IMX6QDL_CLK_CAN1_SERIAL]  = imx_clk_hw_gate2("can1_serial",   "can_root",          base + 0x68, 16);
	hws[IMX6QDL_CLK_CAN2_IPG]     = imx_clk_hw_gate2("can2_ipg",      "ipg",               base + 0x68, 18);
	hws[IMX6QDL_CLK_CAN2_SERIAL]  = imx_clk_hw_gate2("can2_serial",   "can_root",          base + 0x68, 20);
	hws[IMX6QDL_CLK_DCIC1]        = imx_clk_hw_gate2("dcic1",         "ipu1_podf",         base + 0x68, 24);
	hws[IMX6QDL_CLK_DCIC2]        = imx_clk_hw_gate2("dcic2",         "ipu2_podf",         base + 0x68, 26);
	hws[IMX6QDL_CLK_ECSPI1]       = imx_clk_hw_gate2("ecspi1",        "ecspi_root",        base + 0x6c, 0);
	hws[IMX6QDL_CLK_ECSPI2]       = imx_clk_hw_gate2("ecspi2",        "ecspi_root",        base + 0x6c, 2);
	hws[IMX6QDL_CLK_ECSPI3]       = imx_clk_hw_gate2("ecspi3",        "ecspi_root",        base + 0x6c, 4);
	hws[IMX6QDL_CLK_ECSPI4]       = imx_clk_hw_gate2("ecspi4",        "ecspi_root",        base + 0x6c, 6);
	अगर (clk_on_imx6dl())
		hws[IMX6DL_CLK_I2C4]  = imx_clk_hw_gate2("i2c4",          "ipg_per",           base + 0x6c, 8);
	अन्यथा
		hws[IMX6Q_CLK_ECSPI5] = imx_clk_hw_gate2("ecspi5",        "ecspi_root",        base + 0x6c, 8);
	hws[IMX6QDL_CLK_ENET]         = imx_clk_hw_gate2("enet",          "ipg",               base + 0x6c, 10);
	hws[IMX6QDL_CLK_EPIT1]        = imx_clk_hw_gate2("epit1",         "ipg",               base + 0x6c, 12);
	hws[IMX6QDL_CLK_EPIT2]        = imx_clk_hw_gate2("epit2",         "ipg",               base + 0x6c, 14);
	hws[IMX6QDL_CLK_ESAI_EXTAL]   = imx_clk_hw_gate2_shared("esai_extal",   "esai_podf",   base + 0x6c, 16, &share_count_esai);
	hws[IMX6QDL_CLK_ESAI_IPG]     = imx_clk_hw_gate2_shared("esai_ipg",   "ahb",           base + 0x6c, 16, &share_count_esai);
	hws[IMX6QDL_CLK_ESAI_MEM]     = imx_clk_hw_gate2_shared("esai_mem", "ahb",             base + 0x6c, 16, &share_count_esai);
	hws[IMX6QDL_CLK_GPT_IPG]      = imx_clk_hw_gate2("gpt_ipg",       "ipg",               base + 0x6c, 20);
	hws[IMX6QDL_CLK_GPT_IPG_PER]  = imx_clk_hw_gate2("gpt_ipg_per",   "ipg_per",           base + 0x6c, 22);
	hws[IMX6QDL_CLK_GPU2D_CORE] = imx_clk_hw_gate2("gpu2d_core", "gpu2d_core_podf", base + 0x6c, 24);
	hws[IMX6QDL_CLK_GPU3D_CORE]   = imx_clk_hw_gate2("gpu3d_core",    "gpu3d_core_podf",   base + 0x6c, 26);
	hws[IMX6QDL_CLK_HDMI_IAHB]    = imx_clk_hw_gate2("hdmi_iahb",     "ahb",               base + 0x70, 0);
	hws[IMX6QDL_CLK_HDMI_ISFR]    = imx_clk_hw_gate2("hdmi_isfr",     "mipi_core_cfg",     base + 0x70, 4);
	hws[IMX6QDL_CLK_I2C1]         = imx_clk_hw_gate2("i2c1",          "ipg_per",           base + 0x70, 6);
	hws[IMX6QDL_CLK_I2C2]         = imx_clk_hw_gate2("i2c2",          "ipg_per",           base + 0x70, 8);
	hws[IMX6QDL_CLK_I2C3]         = imx_clk_hw_gate2("i2c3",          "ipg_per",           base + 0x70, 10);
	hws[IMX6QDL_CLK_IIM]          = imx_clk_hw_gate2("iim",           "ipg",               base + 0x70, 12);
	hws[IMX6QDL_CLK_ENFC]         = imx_clk_hw_gate2("enfc",          "enfc_podf",         base + 0x70, 14);
	hws[IMX6QDL_CLK_VDOA]         = imx_clk_hw_gate2("vdoa",          "vdo_axi",           base + 0x70, 26);
	hws[IMX6QDL_CLK_IPU1]         = imx_clk_hw_gate2("ipu1",          "ipu1_podf",         base + 0x74, 0);
	hws[IMX6QDL_CLK_IPU1_DI0]     = imx_clk_hw_gate2("ipu1_di0",      "ipu1_di0_sel",      base + 0x74, 2);
	hws[IMX6QDL_CLK_IPU1_DI1]     = imx_clk_hw_gate2("ipu1_di1",      "ipu1_di1_sel",      base + 0x74, 4);
	hws[IMX6QDL_CLK_IPU2]         = imx_clk_hw_gate2("ipu2",          "ipu2_podf",         base + 0x74, 6);
	hws[IMX6QDL_CLK_IPU2_DI0]     = imx_clk_hw_gate2("ipu2_di0",      "ipu2_di0_sel",      base + 0x74, 8);
	अगर (clk_on_imx6qp()) अणु
		hws[IMX6QDL_CLK_LDB_DI0]      = imx_clk_hw_gate2("ldb_di0",       "ldb_di0_sel",      base + 0x74, 12);
		hws[IMX6QDL_CLK_LDB_DI1]      = imx_clk_hw_gate2("ldb_di1",       "ldb_di1_sel",      base + 0x74, 14);
	पूर्ण अन्यथा अणु
		hws[IMX6QDL_CLK_LDB_DI0]      = imx_clk_hw_gate2("ldb_di0",       "ldb_di0_podf",      base + 0x74, 12);
		hws[IMX6QDL_CLK_LDB_DI1]      = imx_clk_hw_gate2("ldb_di1",       "ldb_di1_podf",      base + 0x74, 14);
	पूर्ण
	hws[IMX6QDL_CLK_IPU2_DI1]     = imx_clk_hw_gate2("ipu2_di1",      "ipu2_di1_sel",      base + 0x74, 10);
	hws[IMX6QDL_CLK_HSI_TX]       = imx_clk_hw_gate2_shared("hsi_tx", "hsi_tx_podf",       base + 0x74, 16, &share_count_mipi_core_cfg);
	hws[IMX6QDL_CLK_MIPI_CORE_CFG] = imx_clk_hw_gate2_shared("mipi_core_cfg", "video_27m", base + 0x74, 16, &share_count_mipi_core_cfg);
	hws[IMX6QDL_CLK_MIPI_IPG]     = imx_clk_hw_gate2_shared("mipi_ipg", "ipg",             base + 0x74, 16, &share_count_mipi_core_cfg);

	अगर (clk_on_imx6dl())
		/*
		 * The multiplexer and भागider of the imx6q घड़ी gpu2d get
		 * redefined/reused as mlb_sys_sel and mlb_sys_clk_podf on imx6dl.
		 */
		hws[IMX6QDL_CLK_MLB] = imx_clk_hw_gate2("mlb",            "mlb_podf",   base + 0x74, 18);
	अन्यथा
		hws[IMX6QDL_CLK_MLB] = imx_clk_hw_gate2("mlb",            "axi",               base + 0x74, 18);
	hws[IMX6QDL_CLK_MMDC_CH0_AXI] = imx_clk_hw_gate2_flags("mmdc_ch0_axi",  "mmdc_ch0_axi_podf", base + 0x74, 20, CLK_IS_CRITICAL);
	hws[IMX6QDL_CLK_MMDC_CH1_AXI] = imx_clk_hw_gate2("mmdc_ch1_axi",  "mmdc_ch1_axi_podf", base + 0x74, 22);
	hws[IMX6QDL_CLK_MMDC_P0_IPG]  = imx_clk_hw_gate2_flags("mmdc_p0_ipg",   "ipg",         base + 0x74, 24, CLK_IS_CRITICAL);
	hws[IMX6QDL_CLK_OCRAM]        = imx_clk_hw_gate2("ocram",         "ahb",               base + 0x74, 28);
	hws[IMX6QDL_CLK_OPENVG_AXI]   = imx_clk_hw_gate2("openvg_axi",    "axi",               base + 0x74, 30);
	hws[IMX6QDL_CLK_PCIE_AXI]     = imx_clk_hw_gate2("pcie_axi",      "pcie_axi_sel",      base + 0x78, 0);
	hws[IMX6QDL_CLK_PER1_BCH]     = imx_clk_hw_gate2("per1_bch",      "usdhc3",            base + 0x78, 12);
	hws[IMX6QDL_CLK_PWM1]         = imx_clk_hw_gate2("pwm1",          "ipg_per",           base + 0x78, 16);
	hws[IMX6QDL_CLK_PWM2]         = imx_clk_hw_gate2("pwm2",          "ipg_per",           base + 0x78, 18);
	hws[IMX6QDL_CLK_PWM3]         = imx_clk_hw_gate2("pwm3",          "ipg_per",           base + 0x78, 20);
	hws[IMX6QDL_CLK_PWM4]         = imx_clk_hw_gate2("pwm4",          "ipg_per",           base + 0x78, 22);
	hws[IMX6QDL_CLK_GPMI_BCH_APB] = imx_clk_hw_gate2("gpmi_bch_apb",  "usdhc3",            base + 0x78, 24);
	hws[IMX6QDL_CLK_GPMI_BCH]     = imx_clk_hw_gate2("gpmi_bch",      "usdhc4",            base + 0x78, 26);
	hws[IMX6QDL_CLK_GPMI_IO]      = imx_clk_hw_gate2("gpmi_io",       "enfc",              base + 0x78, 28);
	hws[IMX6QDL_CLK_GPMI_APB]     = imx_clk_hw_gate2("gpmi_apb",      "usdhc3",            base + 0x78, 30);
	hws[IMX6QDL_CLK_ROM]          = imx_clk_hw_gate2_flags("rom",     "ahb",               base + 0x7c, 0, CLK_IS_CRITICAL);
	hws[IMX6QDL_CLK_SATA]         = imx_clk_hw_gate2("sata",          "ahb",               base + 0x7c, 4);
	hws[IMX6QDL_CLK_SDMA]         = imx_clk_hw_gate2("sdma",          "ahb",               base + 0x7c, 6);
	hws[IMX6QDL_CLK_SPBA]         = imx_clk_hw_gate2("spba",          "ipg",               base + 0x7c, 12);
	hws[IMX6QDL_CLK_SPDIF]        = imx_clk_hw_gate2_shared("spdif",     "spdif_podf",     base + 0x7c, 14, &share_count_spdअगर);
	hws[IMX6QDL_CLK_SPDIF_GCLK]   = imx_clk_hw_gate2_shared("spdif_gclk", "ipg",           base + 0x7c, 14, &share_count_spdअगर);
	hws[IMX6QDL_CLK_SSI1_IPG]     = imx_clk_hw_gate2_shared("ssi1_ipg",      "ipg",        base + 0x7c, 18, &share_count_ssi1);
	hws[IMX6QDL_CLK_SSI2_IPG]     = imx_clk_hw_gate2_shared("ssi2_ipg",      "ipg",        base + 0x7c, 20, &share_count_ssi2);
	hws[IMX6QDL_CLK_SSI3_IPG]     = imx_clk_hw_gate2_shared("ssi3_ipg",      "ipg",        base + 0x7c, 22, &share_count_ssi3);
	hws[IMX6QDL_CLK_SSI1]         = imx_clk_hw_gate2_shared("ssi1",          "ssi1_podf",  base + 0x7c, 18, &share_count_ssi1);
	hws[IMX6QDL_CLK_SSI2]         = imx_clk_hw_gate2_shared("ssi2",          "ssi2_podf",  base + 0x7c, 20, &share_count_ssi2);
	hws[IMX6QDL_CLK_SSI3]         = imx_clk_hw_gate2_shared("ssi3",          "ssi3_podf",  base + 0x7c, 22, &share_count_ssi3);
	hws[IMX6QDL_CLK_UART_IPG]     = imx_clk_hw_gate2("uart_ipg",      "ipg",               base + 0x7c, 24);
	hws[IMX6QDL_CLK_UART_SERIAL]  = imx_clk_hw_gate2("uart_serial",   "uart_serial_podf",  base + 0x7c, 26);
	hws[IMX6QDL_CLK_USBOH3]       = imx_clk_hw_gate2("usboh3",        "ipg",               base + 0x80, 0);
	hws[IMX6QDL_CLK_USDHC1]       = imx_clk_hw_gate2("usdhc1",        "usdhc1_podf",       base + 0x80, 2);
	hws[IMX6QDL_CLK_USDHC2]       = imx_clk_hw_gate2("usdhc2",        "usdhc2_podf",       base + 0x80, 4);
	hws[IMX6QDL_CLK_USDHC3]       = imx_clk_hw_gate2("usdhc3",        "usdhc3_podf",       base + 0x80, 6);
	hws[IMX6QDL_CLK_USDHC4]       = imx_clk_hw_gate2("usdhc4",        "usdhc4_podf",       base + 0x80, 8);
	hws[IMX6QDL_CLK_EIM_SLOW]     = imx_clk_hw_gate2("eim_slow",      "eim_slow_podf",     base + 0x80, 10);
	hws[IMX6QDL_CLK_VDO_AXI]      = imx_clk_hw_gate2("vdo_axi",       "vdo_axi_sel",       base + 0x80, 12);
	hws[IMX6QDL_CLK_VPU_AXI]      = imx_clk_hw_gate2("vpu_axi",       "vpu_axi_podf",      base + 0x80, 14);
	अगर (clk_on_imx6qp()) अणु
		hws[IMX6QDL_CLK_PRE0] = imx_clk_hw_gate2("pre0",	       "pre_axi",	    base + 0x80, 16);
		hws[IMX6QDL_CLK_PRE1] = imx_clk_hw_gate2("pre1",	       "pre_axi",	    base + 0x80, 18);
		hws[IMX6QDL_CLK_PRE2] = imx_clk_hw_gate2("pre2",	       "pre_axi",         base + 0x80, 20);
		hws[IMX6QDL_CLK_PRE3] = imx_clk_hw_gate2("pre3",	       "pre_axi",	    base + 0x80, 22);
		hws[IMX6QDL_CLK_PRG0_AXI] = imx_clk_hw_gate2_shared("prg0_axi",  "ipu1_podf",  base + 0x80, 24, &share_count_prg0);
		hws[IMX6QDL_CLK_PRG1_AXI] = imx_clk_hw_gate2_shared("prg1_axi",  "ipu2_podf",  base + 0x80, 26, &share_count_prg1);
		hws[IMX6QDL_CLK_PRG0_APB] = imx_clk_hw_gate2_shared("prg0_apb",  "ipg",	    base + 0x80, 24, &share_count_prg0);
		hws[IMX6QDL_CLK_PRG1_APB] = imx_clk_hw_gate2_shared("prg1_apb",  "ipg",	    base + 0x80, 26, &share_count_prg1);
	पूर्ण
	hws[IMX6QDL_CLK_CKO1]         = imx_clk_hw_gate("cko1",           "cko1_podf",         base + 0x60, 7);
	hws[IMX6QDL_CLK_CKO2]         = imx_clk_hw_gate("cko2",           "cko2_podf",         base + 0x60, 24);

	/*
	 * The gpt_3m घड़ी is not available on i.MX6Q TO1.0.  Let's poपूर्णांक it
	 * to घड़ी gpt_ipg_per to ease the gpt driver code.
	 */
	अगर (clk_on_imx6q() && imx_get_soc_revision() == IMX_CHIP_REVISION_1_0)
		hws[IMX6QDL_CLK_GPT_3M] = hws[IMX6QDL_CLK_GPT_IPG_PER];

	imx_check_clk_hws(hws, IMX6QDL_CLK_END);

	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_hw_data);

	clk_hw_रेजिस्टर_clkdev(hws[IMX6QDL_CLK_ENET_REF], "enet_ref", शून्य);

	clk_set_rate(hws[IMX6QDL_CLK_PLL3_PFD1_540M]->clk, 540000000);
	अगर (clk_on_imx6dl())
		clk_set_parent(hws[IMX6QDL_CLK_IPU1_SEL]->clk, hws[IMX6QDL_CLK_PLL3_PFD1_540M]->clk);

	clk_set_parent(hws[IMX6QDL_CLK_IPU1_DI0_PRE_SEL]->clk, hws[IMX6QDL_CLK_PLL5_VIDEO_DIV]->clk);
	clk_set_parent(hws[IMX6QDL_CLK_IPU1_DI1_PRE_SEL]->clk, hws[IMX6QDL_CLK_PLL5_VIDEO_DIV]->clk);
	clk_set_parent(hws[IMX6QDL_CLK_IPU2_DI0_PRE_SEL]->clk, hws[IMX6QDL_CLK_PLL5_VIDEO_DIV]->clk);
	clk_set_parent(hws[IMX6QDL_CLK_IPU2_DI1_PRE_SEL]->clk, hws[IMX6QDL_CLK_PLL5_VIDEO_DIV]->clk);
	clk_set_parent(hws[IMX6QDL_CLK_IPU1_DI0_SEL]->clk, hws[IMX6QDL_CLK_IPU1_DI0_PRE]->clk);
	clk_set_parent(hws[IMX6QDL_CLK_IPU1_DI1_SEL]->clk, hws[IMX6QDL_CLK_IPU1_DI1_PRE]->clk);
	clk_set_parent(hws[IMX6QDL_CLK_IPU2_DI0_SEL]->clk, hws[IMX6QDL_CLK_IPU2_DI0_PRE]->clk);
	clk_set_parent(hws[IMX6QDL_CLK_IPU2_DI1_SEL]->clk, hws[IMX6QDL_CLK_IPU2_DI1_PRE]->clk);

	/*
	 * The gpmi needs 100MHz frequency in the EDO/Sync mode,
	 * We can not get the 100MHz from the pll2_pfd0_352m.
	 * So choose pll2_pfd2_396m as enfc_sel's parent.
	 */
	clk_set_parent(hws[IMX6QDL_CLK_ENFC_SEL]->clk, hws[IMX6QDL_CLK_PLL2_PFD2_396M]->clk);

	अगर (IS_ENABLED(CONFIG_USB_MXS_PHY)) अणु
		clk_prepare_enable(hws[IMX6QDL_CLK_USBPHY1_GATE]->clk);
		clk_prepare_enable(hws[IMX6QDL_CLK_USBPHY2_GATE]->clk);
	पूर्ण

	/*
	 * Let's initially set up CLKO with OSC24M, since this configuration
	 * is widely used by imx6q board designs to घड़ी audio codec.
	 */
	ret = clk_set_parent(hws[IMX6QDL_CLK_CKO2_SEL]->clk, hws[IMX6QDL_CLK_OSC]->clk);
	अगर (!ret)
		ret = clk_set_parent(hws[IMX6QDL_CLK_CKO]->clk, hws[IMX6QDL_CLK_CKO2]->clk);
	अगर (ret)
		pr_warn("failed to set up CLKO: %d\n", ret);

	/* Audio-related घड़ीs configuration */
	clk_set_parent(hws[IMX6QDL_CLK_SPDIF_SEL]->clk, hws[IMX6QDL_CLK_PLL3_PFD3_454M]->clk);

	/* All existing boards with PCIe use LVDS1 */
	अगर (IS_ENABLED(CONFIG_PCI_IMX6))
		clk_set_parent(hws[IMX6QDL_CLK_LVDS1_SEL]->clk, hws[IMX6QDL_CLK_SATA_REF_100M]->clk);

	/*
	 * Initialize the GPU घड़ी muxes, so that the maximum specअगरied घड़ी
	 * rates क्रम the respective SoC are not exceeded.
	 */
	अगर (clk_on_imx6dl()) अणु
		clk_set_parent(hws[IMX6QDL_CLK_GPU3D_CORE_SEL]->clk,
			       hws[IMX6QDL_CLK_PLL2_PFD1_594M]->clk);
		clk_set_parent(hws[IMX6QDL_CLK_GPU2D_CORE_SEL]->clk,
			       hws[IMX6QDL_CLK_PLL2_PFD1_594M]->clk);
	पूर्ण अन्यथा अगर (clk_on_imx6q()) अणु
		clk_set_parent(hws[IMX6QDL_CLK_GPU3D_CORE_SEL]->clk,
			       hws[IMX6QDL_CLK_MMDC_CH0_AXI]->clk);
		clk_set_parent(hws[IMX6QDL_CLK_GPU3D_SHADER_SEL]->clk,
			       hws[IMX6QDL_CLK_PLL2_PFD1_594M]->clk);
		clk_set_parent(hws[IMX6QDL_CLK_GPU2D_CORE_SEL]->clk,
			       hws[IMX6QDL_CLK_PLL3_USB_OTG]->clk);
	पूर्ण

	imx_रेजिस्टर_uart_घड़ीs(1);
पूर्ण
CLK_OF_DECLARE(imx6q, "fsl,imx6q-ccm", imx6q_घड़ीs_init);
