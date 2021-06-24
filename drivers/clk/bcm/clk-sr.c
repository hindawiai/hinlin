<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Broadcom
 */

#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/घड़ी/bcm-sr.h>
#समावेश "clk-iproc.h"

#घोषणा REG_VAL(o, s, w) अणु .offset = o, .shअगरt = s, .width = w, पूर्ण

#घोषणा AON_VAL(o, pw, ps, is) अणु .offset = o, .pwr_width = pw, \
	.pwr_shअगरt = ps, .iso_shअगरt = is पूर्ण

#घोषणा SW_CTRL_VAL(o, s) अणु .offset = o, .shअगरt = s, पूर्ण

#घोषणा RESET_VAL(o, rs, prs) अणु .offset = o, .reset_shअगरt = rs, \
	.p_reset_shअगरt = prs पूर्ण

#घोषणा DF_VAL(o, kis, kiw, kps, kpw, kas, kaw) अणु .offset = o, \
	.ki_shअगरt = kis, .ki_width = kiw, .kp_shअगरt = kps, .kp_width = kpw, \
	.ka_shअगरt = kas, .ka_width = kaw पूर्ण

#घोषणा VCO_CTRL_VAL(uo, lo) अणु .u_offset = uo, .l_offset = lo पूर्ण

#घोषणा ENABLE_VAL(o, es, hs, bs) अणु .offset = o, .enable_shअगरt = es, \
	.hold_shअगरt = hs, .bypass_shअगरt = bs पूर्ण


अटल स्थिर काष्ठा iproc_pll_ctrl sr_genpll0 = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_HAS_NDIV_FRAC |
		IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 5, 1, 0),
	.reset = RESET_VAL(0x0, 12, 11),
	.dig_filter = DF_VAL(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctrl = SW_CTRL_VAL(0x10, 31),
	.nभाग_पूर्णांक = REG_VAL(0x10, 20, 10),
	.nभाग_frac = REG_VAL(0x10, 0, 20),
	.pभाग = REG_VAL(0x14, 0, 4),
	.status = REG_VAL(0x30, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl sr_genpll0_clk[] = अणु
	[BCM_SR_GENPLL0_125M_CLK] = अणु
		.channel = BCM_SR_GENPLL0_125M_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 6, 0, 12),
		.mभाग = REG_VAL(0x18, 0, 9),
	पूर्ण,
	[BCM_SR_GENPLL0_SCR_CLK] = अणु
		.channel = BCM_SR_GENPLL0_SCR_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 7, 1, 13),
		.mभाग = REG_VAL(0x18, 10, 9),
	पूर्ण,
	[BCM_SR_GENPLL0_250M_CLK] = अणु
		.channel = BCM_SR_GENPLL0_250M_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 8, 2, 14),
		.mभाग = REG_VAL(0x18, 20, 9),
	पूर्ण,
	[BCM_SR_GENPLL0_PCIE_AXI_CLK] = अणु
		.channel = BCM_SR_GENPLL0_PCIE_AXI_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 9, 3, 15),
		.mभाग = REG_VAL(0x1c, 0, 9),
	पूर्ण,
	[BCM_SR_GENPLL0_PAXC_AXI_X2_CLK] = अणु
		.channel = BCM_SR_GENPLL0_PAXC_AXI_X2_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 10, 4, 16),
		.mभाग = REG_VAL(0x1c, 10, 9),
	पूर्ण,
	[BCM_SR_GENPLL0_PAXC_AXI_CLK] = अणु
		.channel = BCM_SR_GENPLL0_PAXC_AXI_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 11, 5, 17),
		.mभाग = REG_VAL(0x1c, 20, 9),
	पूर्ण,
पूर्ण;

अटल पूर्णांक sr_genpll0_clk_init(काष्ठा platक्रमm_device *pdev)
अणु
	iproc_pll_clk_setup(pdev->dev.of_node,
			    &sr_genpll0, शून्य, 0, sr_genpll0_clk,
			    ARRAY_SIZE(sr_genpll0_clk));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iproc_pll_ctrl sr_genpll2 = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_HAS_NDIV_FRAC |
		IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 1, 13, 12),
	.reset = RESET_VAL(0x0, 12, 11),
	.dig_filter = DF_VAL(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctrl = SW_CTRL_VAL(0x10, 31),
	.nभाग_पूर्णांक = REG_VAL(0x10, 20, 10),
	.nभाग_frac = REG_VAL(0x10, 0, 20),
	.pभाग = REG_VAL(0x14, 0, 4),
	.status = REG_VAL(0x30, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl sr_genpll2_clk[] = अणु
	[BCM_SR_GENPLL2_NIC_CLK] = अणु
		.channel = BCM_SR_GENPLL2_NIC_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 6, 0, 12),
		.mभाग = REG_VAL(0x18, 0, 9),
	पूर्ण,
	[BCM_SR_GENPLL2_TS_500_CLK] = अणु
		.channel = BCM_SR_GENPLL2_TS_500_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 7, 1, 13),
		.mभाग = REG_VAL(0x18, 10, 9),
	पूर्ण,
	[BCM_SR_GENPLL2_125_NITRO_CLK] = अणु
		.channel = BCM_SR_GENPLL2_125_NITRO_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 8, 2, 14),
		.mभाग = REG_VAL(0x18, 20, 9),
	पूर्ण,
	[BCM_SR_GENPLL2_CHIMP_CLK] = अणु
		.channel = BCM_SR_GENPLL2_CHIMP_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 9, 3, 15),
		.mभाग = REG_VAL(0x1c, 0, 9),
	पूर्ण,
	[BCM_SR_GENPLL2_NIC_FLASH_CLK] = अणु
		.channel = BCM_SR_GENPLL2_NIC_FLASH_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 10, 4, 16),
		.mभाग = REG_VAL(0x1c, 10, 9),
	पूर्ण,
	[BCM_SR_GENPLL2_FS4_CLK] = अणु
		.channel = BCM_SR_GENPLL2_FS4_CLK,
		.enable = ENABLE_VAL(0x4, 11, 5, 17),
		.mभाग = REG_VAL(0x1c, 20, 9),
	पूर्ण,
पूर्ण;

अटल पूर्णांक sr_genpll2_clk_init(काष्ठा platक्रमm_device *pdev)
अणु
	iproc_pll_clk_setup(pdev->dev.of_node,
			    &sr_genpll2, शून्य, 0, sr_genpll2_clk,
			    ARRAY_SIZE(sr_genpll2_clk));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iproc_pll_ctrl sr_genpll3 = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_HAS_NDIV_FRAC |
		IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 1, 19, 18),
	.reset = RESET_VAL(0x0, 12, 11),
	.dig_filter = DF_VAL(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctrl = SW_CTRL_VAL(0x10, 31),
	.nभाग_पूर्णांक = REG_VAL(0x10, 20, 10),
	.nभाग_frac = REG_VAL(0x10, 0, 20),
	.pभाग = REG_VAL(0x14, 0, 4),
	.status = REG_VAL(0x30, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl sr_genpll3_clk[] = अणु
	[BCM_SR_GENPLL3_HSLS_CLK] = अणु
		.channel = BCM_SR_GENPLL3_HSLS_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 6, 0, 12),
		.mभाग = REG_VAL(0x18, 0, 9),
	पूर्ण,
	[BCM_SR_GENPLL3_SDIO_CLK] = अणु
		.channel = BCM_SR_GENPLL3_SDIO_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 7, 1, 13),
		.mभाग = REG_VAL(0x18, 10, 9),
	पूर्ण,
पूर्ण;

अटल व्योम sr_genpll3_clk_init(काष्ठा device_node *node)
अणु
	iproc_pll_clk_setup(node, &sr_genpll3, शून्य, 0, sr_genpll3_clk,
			    ARRAY_SIZE(sr_genpll3_clk));
पूर्ण
CLK_OF_DECLARE(sr_genpll3_clk, "brcm,sr-genpll3", sr_genpll3_clk_init);

अटल स्थिर काष्ठा iproc_pll_ctrl sr_genpll4 = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_HAS_NDIV_FRAC |
		IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 1, 25, 24),
	.reset = RESET_VAL(0x0, 12, 11),
	.dig_filter = DF_VAL(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctrl = SW_CTRL_VAL(0x10, 31),
	.nभाग_पूर्णांक = REG_VAL(0x10, 20, 10),
	.nभाग_frac = REG_VAL(0x10, 0, 20),
	.pभाग = REG_VAL(0x14, 0, 4),
	.status = REG_VAL(0x30, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl sr_genpll4_clk[] = अणु
	[BCM_SR_GENPLL4_CCN_CLK] = अणु
		.channel = BCM_SR_GENPLL4_CCN_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 6, 0, 12),
		.mभाग = REG_VAL(0x18, 0, 9),
	पूर्ण,
	[BCM_SR_GENPLL4_TPIU_PLL_CLK] = अणु
		.channel = BCM_SR_GENPLL4_TPIU_PLL_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 7, 1, 13),
		.mभाग = REG_VAL(0x18, 10, 9),
	पूर्ण,
	[BCM_SR_GENPLL4_NOC_CLK] = अणु
		.channel = BCM_SR_GENPLL4_NOC_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 8, 2, 14),
		.mभाग = REG_VAL(0x18, 20, 9),
	पूर्ण,
	[BCM_SR_GENPLL4_CHCLK_FS4_CLK] = अणु
		.channel = BCM_SR_GENPLL4_CHCLK_FS4_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 9, 3, 15),
		.mभाग = REG_VAL(0x1c, 0, 9),
	पूर्ण,
	[BCM_SR_GENPLL4_BRIDGE_FSCPU_CLK] = अणु
		.channel = BCM_SR_GENPLL4_BRIDGE_FSCPU_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x4, 10, 4, 16),
		.mभाग = REG_VAL(0x1c, 10, 9),
	पूर्ण,
पूर्ण;

अटल पूर्णांक sr_genpll4_clk_init(काष्ठा platक्रमm_device *pdev)
अणु
	iproc_pll_clk_setup(pdev->dev.of_node,
			    &sr_genpll4, शून्य, 0, sr_genpll4_clk,
			    ARRAY_SIZE(sr_genpll4_clk));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iproc_pll_ctrl sr_genpll5 = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_HAS_NDIV_FRAC |
		IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 1, 1, 0),
	.reset = RESET_VAL(0x0, 12, 11),
	.dig_filter = DF_VAL(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctrl = SW_CTRL_VAL(0x10, 31),
	.nभाग_पूर्णांक = REG_VAL(0x10, 20, 10),
	.nभाग_frac = REG_VAL(0x10, 0, 20),
	.pभाग = REG_VAL(0x14, 0, 4),
	.status = REG_VAL(0x30, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl sr_genpll5_clk[] = अणु
	[BCM_SR_GENPLL5_FS4_HF_CLK] = अणु
		.channel = BCM_SR_GENPLL5_FS4_HF_CLK,
		.enable = ENABLE_VAL(0x4, 6, 0, 12),
		.mभाग = REG_VAL(0x18, 0, 9),
	पूर्ण,
	[BCM_SR_GENPLL5_CRYPTO_AE_CLK] = अणु
		.channel = BCM_SR_GENPLL5_CRYPTO_AE_CLK,
		.enable = ENABLE_VAL(0x4, 7, 1, 12),
		.mभाग = REG_VAL(0x18, 10, 9),
	पूर्ण,
	[BCM_SR_GENPLL5_RAID_AE_CLK] = अणु
		.channel = BCM_SR_GENPLL5_RAID_AE_CLK,
		.enable = ENABLE_VAL(0x4, 8, 2, 14),
		.mभाग = REG_VAL(0x18, 20, 9),
	पूर्ण,
पूर्ण;

अटल पूर्णांक sr_genpll5_clk_init(काष्ठा platक्रमm_device *pdev)
अणु
	iproc_pll_clk_setup(pdev->dev.of_node,
			    &sr_genpll5, शून्य, 0, sr_genpll5_clk,
			    ARRAY_SIZE(sr_genpll5_clk));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iproc_pll_ctrl sr_lcpll0 = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 2, 19, 18),
	.reset = RESET_VAL(0x0, 31, 30),
	.sw_ctrl = SW_CTRL_VAL(0x4, 31),
	.nभाग_पूर्णांक = REG_VAL(0x4, 16, 10),
	.pभाग = REG_VAL(0x4, 26, 4),
	.status = REG_VAL(0x38, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl sr_lcpll0_clk[] = अणु
	[BCM_SR_LCPLL0_SATA_REFP_CLK] = अणु
		.channel = BCM_SR_LCPLL0_SATA_REFP_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 7, 1, 13),
		.mभाग = REG_VAL(0x14, 0, 9),
	पूर्ण,
	[BCM_SR_LCPLL0_SATA_REFN_CLK] = अणु
		.channel = BCM_SR_LCPLL0_SATA_REFN_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 8, 2, 14),
		.mभाग = REG_VAL(0x14, 10, 9),
	पूर्ण,
	[BCM_SR_LCPLL0_SATA_350_CLK] = अणु
		.channel = BCM_SR_LCPLL0_SATA_350_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 9, 3, 15),
		.mभाग = REG_VAL(0x14, 20, 9),
	पूर्ण,
	[BCM_SR_LCPLL0_SATA_500_CLK] = अणु
		.channel = BCM_SR_LCPLL0_SATA_500_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 10, 4, 16),
		.mभाग = REG_VAL(0x18, 0, 9),
	पूर्ण,
पूर्ण;

अटल पूर्णांक sr_lcpll0_clk_init(काष्ठा platक्रमm_device *pdev)
अणु
	iproc_pll_clk_setup(pdev->dev.of_node,
			    &sr_lcpll0, शून्य, 0, sr_lcpll0_clk,
			    ARRAY_SIZE(sr_lcpll0_clk));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iproc_pll_ctrl sr_lcpll1 = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 2, 22, 21),
	.reset = RESET_VAL(0x0, 31, 30),
	.sw_ctrl = SW_CTRL_VAL(0x4, 31),
	.nभाग_पूर्णांक = REG_VAL(0x4, 16, 10),
	.pभाग = REG_VAL(0x4, 26, 4),
	.status = REG_VAL(0x38, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl sr_lcpll1_clk[] = अणु
	[BCM_SR_LCPLL1_WAN_CLK] = अणु
		.channel = BCM_SR_LCPLL1_WAN_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 7, 1, 13),
		.mभाग = REG_VAL(0x14, 0, 9),
	पूर्ण,
	[BCM_SR_LCPLL1_USB_REF_CLK] = अणु
		.channel = BCM_SR_LCPLL1_USB_REF_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 8, 2, 14),
		.mभाग = REG_VAL(0x14, 10, 9),
	पूर्ण,
	[BCM_SR_LCPLL1_CRMU_TS_CLK] = अणु
		.channel = BCM_SR_LCPLL1_CRMU_TS_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 9, 3, 15),
		.mभाग = REG_VAL(0x14, 20, 9),
	पूर्ण,
पूर्ण;

अटल पूर्णांक sr_lcpll1_clk_init(काष्ठा platक्रमm_device *pdev)
अणु
	iproc_pll_clk_setup(pdev->dev.of_node,
			    &sr_lcpll1, शून्य, 0, sr_lcpll1_clk,
			    ARRAY_SIZE(sr_lcpll1_clk));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iproc_pll_ctrl sr_lcpll_pcie = अणु
	.flags = IPROC_CLK_AON | IPROC_CLK_PLL_NEEDS_SW_CFG,
	.aon = AON_VAL(0x0, 2, 25, 24),
	.reset = RESET_VAL(0x0, 31, 30),
	.sw_ctrl = SW_CTRL_VAL(0x4, 31),
	.nभाग_पूर्णांक = REG_VAL(0x4, 16, 10),
	.pभाग = REG_VAL(0x4, 26, 4),
	.status = REG_VAL(0x38, 12, 1),
पूर्ण;

अटल स्थिर काष्ठा iproc_clk_ctrl sr_lcpll_pcie_clk[] = अणु
	[BCM_SR_LCPLL_PCIE_PHY_REF_CLK] = अणु
		.channel = BCM_SR_LCPLL_PCIE_PHY_REF_CLK,
		.flags = IPROC_CLK_AON,
		.enable = ENABLE_VAL(0x0, 7, 1, 13),
		.mभाग = REG_VAL(0x14, 0, 9),
	पूर्ण,
पूर्ण;

अटल पूर्णांक sr_lcpll_pcie_clk_init(काष्ठा platक्रमm_device *pdev)
अणु
	iproc_pll_clk_setup(pdev->dev.of_node,
			    &sr_lcpll_pcie, शून्य, 0, sr_lcpll_pcie_clk,
			    ARRAY_SIZE(sr_lcpll_pcie_clk));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sr_clk_dt_ids[] = अणु
	अणु .compatible = "brcm,sr-genpll0", .data = sr_genpll0_clk_init पूर्ण,
	अणु .compatible = "brcm,sr-genpll2", .data = sr_genpll2_clk_init पूर्ण,
	अणु .compatible = "brcm,sr-genpll4", .data = sr_genpll4_clk_init पूर्ण,
	अणु .compatible = "brcm,sr-genpll5", .data = sr_genpll5_clk_init पूर्ण,
	अणु .compatible = "brcm,sr-lcpll0", .data = sr_lcpll0_clk_init पूर्ण,
	अणु .compatible = "brcm,sr-lcpll1", .data = sr_lcpll1_clk_init पूर्ण,
	अणु .compatible = "brcm,sr-lcpll-pcie", .data = sr_lcpll_pcie_clk_init पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक sr_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक (*probe_func)(काष्ठा platक्रमm_device *);

	probe_func = of_device_get_match_data(&pdev->dev);
	अगर (!probe_func)
		वापस -ENODEV;

	वापस probe_func(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver sr_clk_driver = अणु
	.driver = अणु
		.name = "sr-clk",
		.of_match_table = sr_clk_dt_ids,
	पूर्ण,
	.probe = sr_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(sr_clk_driver);
