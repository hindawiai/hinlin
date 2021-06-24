<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "xusb.h"

#घोषणा FUSE_SKU_CALIB_HS_CURR_LEVEL_PADX_SHIFT(x) ((x) ? 15 : 0)
#घोषणा FUSE_SKU_CALIB_HS_CURR_LEVEL_PAD_MASK 0x3f
#घोषणा FUSE_SKU_CALIB_HS_IREF_CAP_SHIFT 13
#घोषणा FUSE_SKU_CALIB_HS_IREF_CAP_MASK 0x3
#घोषणा FUSE_SKU_CALIB_HS_SQUELCH_LEVEL_SHIFT 11
#घोषणा FUSE_SKU_CALIB_HS_SQUELCH_LEVEL_MASK 0x3
#घोषणा FUSE_SKU_CALIB_HS_TERM_RANGE_ADJ_SHIFT 7
#घोषणा FUSE_SKU_CALIB_HS_TERM_RANGE_ADJ_MASK 0xf

#घोषणा XUSB_PADCTL_USB2_PORT_CAP 0x008
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_SHIFT(x) ((x) * 4)
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_PORT_CAP_MASK 0x3
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_DISABLED 0x0
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_HOST 0x1
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_DEVICE 0x2
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_OTG 0x3

#घोषणा XUSB_PADCTL_SS_PORT_MAP 0x014
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORTX_INTERNAL(x) (1 << (((x) * 4) + 3))
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP_SHIFT(x) ((x) * 4)
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP_MASK(x) (0x7 << ((x) * 4))
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP(x, v) (((v) & 0x7) << ((x) * 4))
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORT_MAP_MASK 0x7

#घोषणा XUSB_PADCTL_ELPG_PROGRAM 0x01c
#घोषणा XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN (1 << 26)
#घोषणा XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY (1 << 25)
#घोषणा XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN (1 << 24)
#घोषणा XUSB_PADCTL_ELPG_PROGRAM_SSPX_ELPG_VCORE_DOWN(x) (1 << (18 + (x) * 4))
#घोषणा XUSB_PADCTL_ELPG_PROGRAM_SSPX_ELPG_CLAMP_EN_EARLY(x) \
							(1 << (17 + (x) * 4))
#घोषणा XUSB_PADCTL_ELPG_PROGRAM_SSPX_ELPG_CLAMP_EN(x) (1 << (16 + (x) * 4))

#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL1 0x040
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL0_LOCKDET (1 << 19)
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL1_REFCLK_SEL_MASK (0xf << 12)
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL_RST (1 << 1)

#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL2 0x044
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL2_REFCLKBUF_EN (1 << 6)
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_EN (1 << 5)
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_SEL (1 << 4)

#घोषणा XUSB_PADCTL_IOPHY_USB3_PADX_CTL2(x) (0x058 + (x) * 4)
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_CDR_CNTL_SHIFT 24
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_CDR_CNTL_MASK 0xff
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_CDR_CNTL_VAL 0x24
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_Z_SHIFT 16
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_Z_MASK 0x3f
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_G_SHIFT 8
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_G_MASK 0x3f
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_SHIFT 8
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_MASK 0xffff
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_VAL 0xf070
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_WANDER_SHIFT 4
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_WANDER_MASK 0xf
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_WANDER_VAL 0xf

#घोषणा XUSB_PADCTL_IOPHY_USB3_PADX_CTL4(x) (0x068 + (x) * 4)
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_TAP_SHIFT 24
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_TAP_MASK 0x1f
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_AMP_SHIFT 16
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_AMP_MASK 0x7f
#घोषणा XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_VAL 0x002008ee

#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_PX_CTL2(x) ((x) < 2 ? 0x078 + (x) * 4 : \
					       0x0f8 + (x) * 4)
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL2_SPARE_IN_SHIFT 28
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL2_SPARE_IN_MASK 0x3
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL2_SPARE_IN_VAL 0x1

#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_PX_CTL5(x) ((x) < 2 ? 0x090 + (x) * 4 : \
					       0x11c + (x) * 4)
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL5_RX_QEYE_EN (1 << 8)

#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_PX_CTL6(x) ((x) < 2 ? 0x098 + (x) * 4 : \
					       0x128 + (x) * 4)
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SHIFT 24
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_G_Z_MASK 0x3f
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_TAP_MASK 0x1f
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_AMP_MASK 0x7f
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT 16
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_MASK 0xff
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_G_Z 0x21
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_TAP 0x32
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_AMP 0x33
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_CTLE_Z 0x48
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_LATCH_G_Z 0xa1

#घोषणा XUSB_PADCTL_USB2_OTG_PADX_CTL0(x) (0x0a0 + (x) * 4)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD_ZI (1 << 21)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD2 (1 << 20)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD (1 << 19)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_SHIFT 14
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_MASK 0x3
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_VAL(x) ((x) ? 0x0 : 0x3)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_SHIFT 6
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_MASK 0x3f
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_VAL 0x0e
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_SHIFT 0
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_MASK 0x3f

#घोषणा XUSB_PADCTL_USB2_OTG_PADX_CTL1(x) (0x0ac + (x) * 4)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_SHIFT 9
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_MASK 0x3
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_SHIFT 3
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_MASK 0x7
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DR (1 << 2)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DISC_FORCE_POWERUP (1 << 1)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_CHRP_FORCE_POWERUP (1 << 0)

#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0 0x0b8
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD (1 << 12)
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_SHIFT 2
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_MASK 0x7
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_VAL 0x5
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_SHIFT 0
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_MASK 0x3

#घोषणा XUSB_PADCTL_HSIC_PADX_CTL0(x) (0x0c0 + (x) * 4)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWN_SHIFT 12
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWN_MASK 0x7
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWP_SHIFT 8
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWP_MASK 0x7
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEN_SHIFT 4
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEN_MASK 0x7
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEP_SHIFT 0
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEP_MASK 0x7

#घोषणा XUSB_PADCTL_HSIC_PADX_CTL1(x) (0x0c8 + (x) * 4)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_RPU_STROBE (1 << 10)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_RPU_DATA (1 << 9)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_RPD_STROBE (1 << 8)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_RPD_DATA (1 << 7)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_PD_ZI (1 << 5)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_PD_RX (1 << 4)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_PD_TRX (1 << 3)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_PD_TX (1 << 2)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_AUTO_TERM_EN (1 << 0)

#घोषणा XUSB_PADCTL_HSIC_PADX_CTL2(x) (0x0d0 + (x) * 4)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_SHIFT 4
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_MASK 0x7
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_SHIFT 0
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_MASK 0x7

#घोषणा XUSB_PADCTL_HSIC_STRB_TRIM_CONTROL 0x0e0
#घोषणा XUSB_PADCTL_HSIC_STRB_TRIM_CONTROL_STRB_TRIM_MASK 0x1f

#घोषणा XUSB_PADCTL_USB3_PAD_MUX 0x134
#घोषणा XUSB_PADCTL_USB3_PAD_MUX_PCIE_IDDQ_DISABLE(x) (1 << (1 + (x)))
#घोषणा XUSB_PADCTL_USB3_PAD_MUX_SATA_IDDQ_DISABLE(x) (1 << (6 + (x)))

#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1 0x138
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_LOCKDET (1 << 27)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE (1 << 24)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL0_REFCLK_NDIV_SHIFT 20
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL0_REFCLK_NDIV_MASK 0x3
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD (1 << 3)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST (1 << 1)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ (1 << 0)

#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL2 0x13c
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL1_CP_CNTL_SHIFT 20
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL1_CP_CNTL_MASK 0xf
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL0_CP_CNTL_SHIFT 16
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL0_CP_CNTL_MASK 0xf
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL2_TCLKOUT_EN (1 << 12)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL2_TXCLKREF_SEL (1 << 4)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL2_XDIGCLK_SEL_SHIFT 0
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL2_XDIGCLK_SEL_MASK 0x7

#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL3 0x140
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL3_RCAL_BYPASS (1 << 7)

#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1 0x148
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD (1 << 1)
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ (1 << 0)

#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL2 0x14c

#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL5 0x158

#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL6 0x15c

काष्ठा tegra124_xusb_fuse_calibration अणु
	u32 hs_curr_level[3];
	u32 hs_iref_cap;
	u32 hs_term_range_adj;
	u32 hs_squelch_level;
पूर्ण;

काष्ठा tegra124_xusb_padctl अणु
	काष्ठा tegra_xusb_padctl base;

	काष्ठा tegra124_xusb_fuse_calibration fuse;
पूर्ण;

अटल अंतरभूत काष्ठा tegra124_xusb_padctl *
to_tegra124_xusb_padctl(काष्ठा tegra_xusb_padctl *padctl)
अणु
	वापस container_of(padctl, काष्ठा tegra124_xusb_padctl, base);
पूर्ण

अटल पूर्णांक tegra124_xusb_padctl_enable(काष्ठा tegra_xusb_padctl *padctl)
अणु
	u32 value;

	mutex_lock(&padctl->lock);

	अगर (padctl->enable++ > 0)
		जाओ out;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

out:
	mutex_unlock(&padctl->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra124_xusb_padctl_disable(काष्ठा tegra_xusb_padctl *padctl)
अणु
	u32 value;

	mutex_lock(&padctl->lock);

	अगर (WARN_ON(padctl->enable == 0))
		जाओ out;

	अगर (--padctl->enable > 0)
		जाओ out;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value |= XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value |= XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value |= XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

out:
	mutex_unlock(&padctl->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra124_usb3_save_context(काष्ठा tegra_xusb_padctl *padctl,
				      अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_usb3_port *port;
	काष्ठा tegra_xusb_lane *lane;
	u32 value, offset;

	port = tegra_xusb_find_usb3_port(padctl, index);
	अगर (!port)
		वापस -ENODEV;

	port->context_saved = true;
	lane = port->base.lane;

	अगर (lane->pad == padctl->pcie)
		offset = XUSB_PADCTL_IOPHY_MISC_PAD_PX_CTL6(lane->index);
	अन्यथा
		offset = XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL6;

	value = padctl_पढ़ोl(padctl, offset);
	value &= ~(XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_MASK <<
		   XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT);
	value |= XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_TAP <<
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT;
	padctl_ग_लिखोl(padctl, value, offset);

	value = padctl_पढ़ोl(padctl, offset) >>
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SHIFT;
	port->tap1 = value & XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_TAP_MASK;

	value = padctl_पढ़ोl(padctl, offset);
	value &= ~(XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_MASK <<
		   XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT);
	value |= XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_AMP <<
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT;
	padctl_ग_लिखोl(padctl, value, offset);

	value = padctl_पढ़ोl(padctl, offset) >>
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SHIFT;
	port->amp = value & XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_AMP_MASK;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_USB3_PADX_CTL4(index));
	value &= ~((XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_TAP_MASK <<
		    XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_TAP_SHIFT) |
		   (XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_AMP_MASK <<
		    XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_AMP_SHIFT));
	value |= (port->tap1 <<
		  XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_TAP_SHIFT) |
		 (port->amp <<
		  XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_AMP_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_USB3_PADX_CTL4(index));

	value = padctl_पढ़ोl(padctl, offset);
	value &= ~(XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_MASK <<
		   XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT);
	value |= XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_LATCH_G_Z <<
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT;
	padctl_ग_लिखोl(padctl, value, offset);

	value = padctl_पढ़ोl(padctl, offset);
	value &= ~(XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_MASK <<
		   XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT);
	value |= XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_G_Z <<
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT;
	padctl_ग_लिखोl(padctl, value, offset);

	value = padctl_पढ़ोl(padctl, offset) >>
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SHIFT;
	port->ctle_g = value &
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_G_Z_MASK;

	value = padctl_पढ़ोl(padctl, offset);
	value &= ~(XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_MASK <<
		   XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT);
	value |= XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_CTLE_Z <<
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SEL_SHIFT;
	padctl_ग_लिखोl(padctl, value, offset);

	value = padctl_पढ़ोl(padctl, offset) >>
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_SHIFT;
	port->ctle_z = value &
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL6_MISC_OUT_G_Z_MASK;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_USB3_PADX_CTL2(index));
	value &= ~((XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_G_MASK <<
		    XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_G_SHIFT) |
		   (XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_Z_MASK <<
		    XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_Z_SHIFT));
	value |= (port->ctle_g <<
		  XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_G_SHIFT) |
		 (port->ctle_z <<
		  XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_Z_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_USB3_PADX_CTL2(index));

	वापस 0;
पूर्ण

अटल पूर्णांक tegra124_hsic_set_idle(काष्ठा tegra_xusb_padctl *padctl,
				  अचिन्हित पूर्णांक index, bool idle)
अणु
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PADX_CTL1(index));

	अगर (idle)
		value |= XUSB_PADCTL_HSIC_PAD_CTL1_RPD_DATA |
			 XUSB_PADCTL_HSIC_PAD_CTL1_RPU_STROBE;
	अन्यथा
		value &= ~(XUSB_PADCTL_HSIC_PAD_CTL1_RPD_DATA |
			   XUSB_PADCTL_HSIC_PAD_CTL1_RPU_STROBE);

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL1(index));

	वापस 0;
पूर्ण

#घोषणा TEGRA124_LANE(_name, _offset, _shअगरt, _mask, _type)		\
	अणु								\
		.name = _name,						\
		.offset = _offset,					\
		.shअगरt = _shअगरt,					\
		.mask = _mask,						\
		.num_funcs = ARRAY_SIZE(tegra124_##_type##_functions),	\
		.funcs = tegra124_##_type##_functions,			\
	पूर्ण

अटल स्थिर अक्षर * स्थिर tegra124_usb2_functions[] = अणु
	"snps",
	"xusb",
	"uart",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra124_usb2_lanes[] = अणु
	TEGRA124_LANE("usb2-0", 0x004,  0, 0x3, usb2),
	TEGRA124_LANE("usb2-1", 0x004,  2, 0x3, usb2),
	TEGRA124_LANE("usb2-2", 0x004,  4, 0x3, usb2),
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra124_usb2_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
			 अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_usb2_lane *usb2;
	पूर्णांक err;

	usb2 = kzalloc(माप(*usb2), GFP_KERNEL);
	अगर (!usb2)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&usb2->base.list);
	usb2->base.soc = &pad->soc->lanes[index];
	usb2->base.index = index;
	usb2->base.pad = pad;
	usb2->base.np = np;

	err = tegra_xusb_lane_parse_dt(&usb2->base, np);
	अगर (err < 0) अणु
		kमुक्त(usb2);
		वापस ERR_PTR(err);
	पूर्ण

	वापस &usb2->base;
पूर्ण

अटल व्योम tegra124_usb2_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_usb2_lane *usb2 = to_usb2_lane(lane);

	kमुक्त(usb2);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra124_usb2_lane_ops = अणु
	.probe = tegra124_usb2_lane_probe,
	.हटाओ = tegra124_usb2_lane_हटाओ,
पूर्ण;

अटल पूर्णांक tegra124_usb2_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_enable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_usb2_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_disable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_usb2_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_usb2_lane *usb2 = to_usb2_lane(lane);
	काष्ठा tegra_xusb_usb2_pad *pad = to_usb2_pad(lane->pad);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra124_xusb_padctl *priv;
	काष्ठा tegra_xusb_usb2_port *port;
	अचिन्हित पूर्णांक index = lane->index;
	u32 value;
	पूर्णांक err;

	port = tegra_xusb_find_usb2_port(padctl, index);
	अगर (!port) अणु
		dev_err(&phy->dev, "no port found for USB2 lane %u\n", index);
		वापस -ENODEV;
	पूर्ण

	priv = to_tegra124_xusb_padctl(padctl);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value &= ~((XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_MASK <<
		    XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_SHIFT) |
		   (XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_MASK <<
		    XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_SHIFT));
	value |= (priv->fuse.hs_squelch_level <<
		  XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_SHIFT) |
		 (XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_VAL <<
		  XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_PORT_CAP);
	value &= ~(XUSB_PADCTL_USB2_PORT_CAP_PORT_CAP_MASK <<
		   XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_SHIFT(index));
	value |= XUSB_PADCTL_USB2_PORT_CAP_HOST <<
		XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_SHIFT(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_PORT_CAP);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));
	value &= ~((XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_SHIFT) |
		   (XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_SHIFT) |
		   (XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_SHIFT) |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD2 |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD_ZI);
	value |= (priv->fuse.hs_curr_level[index] +
		  usb2->hs_curr_level_offset) <<
		XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_SHIFT;
	value |= XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_VAL <<
		XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_SHIFT;
	value |= XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_VAL(index) <<
		XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));
	value &= ~((XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_SHIFT) |
		   (XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_SHIFT) |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DR |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_CHRP_FORCE_POWERUP |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DISC_FORCE_POWERUP);
	value |= (priv->fuse.hs_term_range_adj <<
		  XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_SHIFT) |
		 (priv->fuse.hs_iref_cap <<
		  XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));

	err = regulator_enable(port->supply);
	अगर (err)
		वापस err;

	mutex_lock(&pad->lock);

	अगर (pad->enable++ > 0)
		जाओ out;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value &= ~XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

out:
	mutex_unlock(&pad->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra124_usb2_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_usb2_pad *pad = to_usb2_pad(lane->pad);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra_xusb_usb2_port *port;
	u32 value;

	port = tegra_xusb_find_usb2_port(padctl, lane->index);
	अगर (!port) अणु
		dev_err(&phy->dev, "no port found for USB2 lane %u\n",
			lane->index);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&pad->lock);

	अगर (WARN_ON(pad->enable == 0))
		जाओ out;

	अगर (--pad->enable > 0)
		जाओ out;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value |= XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

out:
	regulator_disable(port->supply);
	mutex_unlock(&pad->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops tegra124_usb2_phy_ops = अणु
	.init = tegra124_usb2_phy_init,
	.निकास = tegra124_usb2_phy_निकास,
	.घातer_on = tegra124_usb2_phy_घातer_on,
	.घातer_off = tegra124_usb2_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra124_usb2_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
			स्थिर काष्ठा tegra_xusb_pad_soc *soc,
			काष्ठा device_node *np)
अणु
	काष्ठा tegra_xusb_usb2_pad *usb2;
	काष्ठा tegra_xusb_pad *pad;
	पूर्णांक err;

	usb2 = kzalloc(माप(*usb2), GFP_KERNEL);
	अगर (!usb2)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&usb2->lock);

	pad = &usb2->base;
	pad->ops = &tegra124_usb2_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(usb2);
		जाओ out;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &tegra124_usb2_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra124_usb2_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_usb2_pad *usb2 = to_usb2_pad(pad);

	kमुक्त(usb2);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra124_usb2_ops = अणु
	.probe = tegra124_usb2_pad_probe,
	.हटाओ = tegra124_usb2_pad_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra124_usb2_pad = अणु
	.name = "usb2",
	.num_lanes = ARRAY_SIZE(tegra124_usb2_lanes),
	.lanes = tegra124_usb2_lanes,
	.ops = &tegra124_usb2_ops,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_ulpi_functions[] = अणु
	"snps",
	"xusb",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra124_ulpi_lanes[] = अणु
	TEGRA124_LANE("ulpi-0", 0x004, 12, 0x1, ulpi),
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra124_ulpi_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
			 अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_ulpi_lane *ulpi;
	पूर्णांक err;

	ulpi = kzalloc(माप(*ulpi), GFP_KERNEL);
	अगर (!ulpi)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&ulpi->base.list);
	ulpi->base.soc = &pad->soc->lanes[index];
	ulpi->base.index = index;
	ulpi->base.pad = pad;
	ulpi->base.np = np;

	err = tegra_xusb_lane_parse_dt(&ulpi->base, np);
	अगर (err < 0) अणु
		kमुक्त(ulpi);
		वापस ERR_PTR(err);
	पूर्ण

	वापस &ulpi->base;
पूर्ण

अटल व्योम tegra124_ulpi_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_ulpi_lane *ulpi = to_ulpi_lane(lane);

	kमुक्त(ulpi);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra124_ulpi_lane_ops = अणु
	.probe = tegra124_ulpi_lane_probe,
	.हटाओ = tegra124_ulpi_lane_हटाओ,
पूर्ण;

अटल पूर्णांक tegra124_ulpi_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_enable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_ulpi_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_disable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_ulpi_phy_घातer_on(काष्ठा phy *phy)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tegra124_ulpi_phy_घातer_off(काष्ठा phy *phy)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops tegra124_ulpi_phy_ops = अणु
	.init = tegra124_ulpi_phy_init,
	.निकास = tegra124_ulpi_phy_निकास,
	.घातer_on = tegra124_ulpi_phy_घातer_on,
	.घातer_off = tegra124_ulpi_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra124_ulpi_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
			स्थिर काष्ठा tegra_xusb_pad_soc *soc,
			काष्ठा device_node *np)
अणु
	काष्ठा tegra_xusb_ulpi_pad *ulpi;
	काष्ठा tegra_xusb_pad *pad;
	पूर्णांक err;

	ulpi = kzalloc(माप(*ulpi), GFP_KERNEL);
	अगर (!ulpi)
		वापस ERR_PTR(-ENOMEM);

	pad = &ulpi->base;
	pad->ops = &tegra124_ulpi_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(ulpi);
		जाओ out;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &tegra124_ulpi_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra124_ulpi_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_ulpi_pad *ulpi = to_ulpi_pad(pad);

	kमुक्त(ulpi);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra124_ulpi_ops = अणु
	.probe = tegra124_ulpi_pad_probe,
	.हटाओ = tegra124_ulpi_pad_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra124_ulpi_pad = अणु
	.name = "ulpi",
	.num_lanes = ARRAY_SIZE(tegra124_ulpi_lanes),
	.lanes = tegra124_ulpi_lanes,
	.ops = &tegra124_ulpi_ops,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_hsic_functions[] = अणु
	"snps",
	"xusb",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra124_hsic_lanes[] = अणु
	TEGRA124_LANE("hsic-0", 0x004, 14, 0x1, hsic),
	TEGRA124_LANE("hsic-1", 0x004, 15, 0x1, hsic),
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra124_hsic_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
			 अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_hsic_lane *hsic;
	पूर्णांक err;

	hsic = kzalloc(माप(*hsic), GFP_KERNEL);
	अगर (!hsic)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&hsic->base.list);
	hsic->base.soc = &pad->soc->lanes[index];
	hsic->base.index = index;
	hsic->base.pad = pad;
	hsic->base.np = np;

	err = tegra_xusb_lane_parse_dt(&hsic->base, np);
	अगर (err < 0) अणु
		kमुक्त(hsic);
		वापस ERR_PTR(err);
	पूर्ण

	वापस &hsic->base;
पूर्ण

अटल व्योम tegra124_hsic_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_hsic_lane *hsic = to_hsic_lane(lane);

	kमुक्त(hsic);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra124_hsic_lane_ops = अणु
	.probe = tegra124_hsic_lane_probe,
	.हटाओ = tegra124_hsic_lane_हटाओ,
पूर्ण;

अटल पूर्णांक tegra124_hsic_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_enable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_hsic_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_disable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_hsic_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_hsic_lane *hsic = to_hsic_lane(lane);
	काष्ठा tegra_xusb_hsic_pad *pad = to_hsic_pad(lane->pad);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	अचिन्हित पूर्णांक index = lane->index;
	u32 value;
	पूर्णांक err;

	err = regulator_enable(pad->supply);
	अगर (err)
		वापस err;

	padctl_ग_लिखोl(padctl, hsic->strobe_trim,
		      XUSB_PADCTL_HSIC_STRB_TRIM_CONTROL);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PADX_CTL1(index));

	अगर (hsic->स्वतः_term)
		value |= XUSB_PADCTL_HSIC_PAD_CTL1_AUTO_TERM_EN;
	अन्यथा
		value &= ~XUSB_PADCTL_HSIC_PAD_CTL1_AUTO_TERM_EN;

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL1(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PADX_CTL0(index));
	value &= ~((XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEN_MASK <<
		    XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEN_SHIFT) |
		   (XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEP_MASK <<
		    XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEP_SHIFT) |
		   (XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWN_MASK <<
		    XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWN_SHIFT) |
		   (XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWP_MASK <<
		    XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWP_SHIFT));
	value |= (hsic->tx_rtune_n <<
		  XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEN_SHIFT) |
		(hsic->tx_rtune_p <<
		  XUSB_PADCTL_HSIC_PAD_CTL0_TX_RTUNEP_SHIFT) |
		(hsic->tx_rslew_n <<
		 XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWN_SHIFT) |
		(hsic->tx_rslew_p <<
		 XUSB_PADCTL_HSIC_PAD_CTL0_TX_RSLEWP_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL0(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PADX_CTL2(index));
	value &= ~((XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_MASK <<
		    XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_SHIFT) |
		   (XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_MASK <<
		    XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_SHIFT));
	value |= (hsic->rx_strobe_trim <<
		  XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_SHIFT) |
		(hsic->rx_data_trim <<
		 XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL2(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PADX_CTL1(index));
	value &= ~(XUSB_PADCTL_HSIC_PAD_CTL1_RPD_STROBE |
		   XUSB_PADCTL_HSIC_PAD_CTL1_RPU_DATA |
		   XUSB_PADCTL_HSIC_PAD_CTL1_PD_RX |
		   XUSB_PADCTL_HSIC_PAD_CTL1_PD_ZI |
		   XUSB_PADCTL_HSIC_PAD_CTL1_PD_TRX |
		   XUSB_PADCTL_HSIC_PAD_CTL1_PD_TX);
	value |= XUSB_PADCTL_HSIC_PAD_CTL1_RPD_DATA |
		 XUSB_PADCTL_HSIC_PAD_CTL1_RPU_STROBE;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL1(index));

	वापस 0;
पूर्ण

अटल पूर्णांक tegra124_hsic_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_hsic_pad *pad = to_hsic_pad(lane->pad);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	अचिन्हित पूर्णांक index = lane->index;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PADX_CTL1(index));
	value |= XUSB_PADCTL_HSIC_PAD_CTL1_PD_RX |
		 XUSB_PADCTL_HSIC_PAD_CTL1_PD_ZI |
		 XUSB_PADCTL_HSIC_PAD_CTL1_PD_TRX |
		 XUSB_PADCTL_HSIC_PAD_CTL1_PD_TX;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL1(index));

	regulator_disable(pad->supply);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops tegra124_hsic_phy_ops = अणु
	.init = tegra124_hsic_phy_init,
	.निकास = tegra124_hsic_phy_निकास,
	.घातer_on = tegra124_hsic_phy_घातer_on,
	.घातer_off = tegra124_hsic_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra124_hsic_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
			स्थिर काष्ठा tegra_xusb_pad_soc *soc,
			काष्ठा device_node *np)
अणु
	काष्ठा tegra_xusb_hsic_pad *hsic;
	काष्ठा tegra_xusb_pad *pad;
	पूर्णांक err;

	hsic = kzalloc(माप(*hsic), GFP_KERNEL);
	अगर (!hsic)
		वापस ERR_PTR(-ENOMEM);

	pad = &hsic->base;
	pad->ops = &tegra124_hsic_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(hsic);
		जाओ out;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &tegra124_hsic_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra124_hsic_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_hsic_pad *hsic = to_hsic_pad(pad);

	kमुक्त(hsic);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra124_hsic_ops = अणु
	.probe = tegra124_hsic_pad_probe,
	.हटाओ = tegra124_hsic_pad_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra124_hsic_pad = अणु
	.name = "hsic",
	.num_lanes = ARRAY_SIZE(tegra124_hsic_lanes),
	.lanes = tegra124_hsic_lanes,
	.ops = &tegra124_hsic_ops,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_pcie_functions[] = अणु
	"pcie",
	"usb3-ss",
	"sata",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra124_pcie_lanes[] = अणु
	TEGRA124_LANE("pcie-0", 0x134, 16, 0x3, pcie),
	TEGRA124_LANE("pcie-1", 0x134, 18, 0x3, pcie),
	TEGRA124_LANE("pcie-2", 0x134, 20, 0x3, pcie),
	TEGRA124_LANE("pcie-3", 0x134, 22, 0x3, pcie),
	TEGRA124_LANE("pcie-4", 0x134, 24, 0x3, pcie),
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra124_pcie_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
			 अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_pcie_lane *pcie;
	पूर्णांक err;

	pcie = kzalloc(माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&pcie->base.list);
	pcie->base.soc = &pad->soc->lanes[index];
	pcie->base.index = index;
	pcie->base.pad = pad;
	pcie->base.np = np;

	err = tegra_xusb_lane_parse_dt(&pcie->base, np);
	अगर (err < 0) अणु
		kमुक्त(pcie);
		वापस ERR_PTR(err);
	पूर्ण

	वापस &pcie->base;
पूर्ण

अटल व्योम tegra124_pcie_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_pcie_lane *pcie = to_pcie_lane(lane);

	kमुक्त(pcie);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra124_pcie_lane_ops = अणु
	.probe = tegra124_pcie_lane_probe,
	.हटाओ = tegra124_pcie_lane_हटाओ,
पूर्ण;

अटल पूर्णांक tegra124_pcie_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_enable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_pcie_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_disable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_pcie_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	अचिन्हित दीर्घ समयout;
	पूर्णांक err = -ETIMEDOUT;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_P0_CTL1_REFCLK_SEL_MASK;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL2);
	value |= XUSB_PADCTL_IOPHY_PLL_P0_CTL2_REFCLKBUF_EN |
		 XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_EN |
		 XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_SEL;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL2);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL_RST;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);

	समयout = jअगरfies + msecs_to_jअगरfies(50);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
		अगर (value & XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL0_LOCKDET) अणु
			err = 0;
			अवरोध;
		पूर्ण

		usleep_range(100, 200);
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value |= XUSB_PADCTL_USB3_PAD_MUX_PCIE_IDDQ_DISABLE(lane->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

	वापस err;
पूर्ण

अटल पूर्णांक tegra124_pcie_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value &= ~XUSB_PADCTL_USB3_PAD_MUX_PCIE_IDDQ_DISABLE(lane->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL_RST;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops tegra124_pcie_phy_ops = अणु
	.init = tegra124_pcie_phy_init,
	.निकास = tegra124_pcie_phy_निकास,
	.घातer_on = tegra124_pcie_phy_घातer_on,
	.घातer_off = tegra124_pcie_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra124_pcie_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
			स्थिर काष्ठा tegra_xusb_pad_soc *soc,
			काष्ठा device_node *np)
अणु
	काष्ठा tegra_xusb_pcie_pad *pcie;
	काष्ठा tegra_xusb_pad *pad;
	पूर्णांक err;

	pcie = kzalloc(माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस ERR_PTR(-ENOMEM);

	pad = &pcie->base;
	pad->ops = &tegra124_pcie_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(pcie);
		जाओ out;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &tegra124_pcie_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra124_pcie_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_pcie_pad *pcie = to_pcie_pad(pad);

	kमुक्त(pcie);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra124_pcie_ops = अणु
	.probe = tegra124_pcie_pad_probe,
	.हटाओ = tegra124_pcie_pad_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra124_pcie_pad = अणु
	.name = "pcie",
	.num_lanes = ARRAY_SIZE(tegra124_pcie_lanes),
	.lanes = tegra124_pcie_lanes,
	.ops = &tegra124_pcie_ops,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra124_sata_lanes[] = अणु
	TEGRA124_LANE("sata-0", 0x134, 26, 0x3, pcie),
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra124_sata_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
			 अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_sata_lane *sata;
	पूर्णांक err;

	sata = kzalloc(माप(*sata), GFP_KERNEL);
	अगर (!sata)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&sata->base.list);
	sata->base.soc = &pad->soc->lanes[index];
	sata->base.index = index;
	sata->base.pad = pad;
	sata->base.np = np;

	err = tegra_xusb_lane_parse_dt(&sata->base, np);
	अगर (err < 0) अणु
		kमुक्त(sata);
		वापस ERR_PTR(err);
	पूर्ण

	वापस &sata->base;
पूर्ण

अटल व्योम tegra124_sata_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_sata_lane *sata = to_sata_lane(lane);

	kमुक्त(sata);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra124_sata_lane_ops = अणु
	.probe = tegra124_sata_lane_probe,
	.हटाओ = tegra124_sata_lane_हटाओ,
पूर्ण;

अटल पूर्णांक tegra124_sata_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_enable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_sata_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra124_xusb_padctl_disable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra124_sata_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	अचिन्हित दीर्घ समयout;
	पूर्णांक err = -ETIMEDOUT;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD;
	value &= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD;
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	समयout = jअगरfies + msecs_to_jअगरfies(50);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
		अगर (value & XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_LOCKDET) अणु
			err = 0;
			अवरोध;
		पूर्ण

		usleep_range(100, 200);
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value |= XUSB_PADCTL_USB3_PAD_MUX_SATA_IDDQ_DISABLE(lane->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

	वापस err;
पूर्ण

अटल पूर्णांक tegra124_sata_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value &= ~XUSB_PADCTL_USB3_PAD_MUX_SATA_IDDQ_DISABLE(lane->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD;
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);
	value |= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD;
	value |= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops tegra124_sata_phy_ops = अणु
	.init = tegra124_sata_phy_init,
	.निकास = tegra124_sata_phy_निकास,
	.घातer_on = tegra124_sata_phy_घातer_on,
	.घातer_off = tegra124_sata_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra124_sata_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
			स्थिर काष्ठा tegra_xusb_pad_soc *soc,
			काष्ठा device_node *np)
अणु
	काष्ठा tegra_xusb_sata_pad *sata;
	काष्ठा tegra_xusb_pad *pad;
	पूर्णांक err;

	sata = kzalloc(माप(*sata), GFP_KERNEL);
	अगर (!sata)
		वापस ERR_PTR(-ENOMEM);

	pad = &sata->base;
	pad->ops = &tegra124_sata_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(sata);
		जाओ out;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &tegra124_sata_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra124_sata_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_sata_pad *sata = to_sata_pad(pad);

	kमुक्त(sata);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra124_sata_ops = अणु
	.probe = tegra124_sata_pad_probe,
	.हटाओ = tegra124_sata_pad_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra124_sata_pad = अणु
	.name = "sata",
	.num_lanes = ARRAY_SIZE(tegra124_sata_lanes),
	.lanes = tegra124_sata_lanes,
	.ops = &tegra124_sata_ops,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc *tegra124_pads[] = अणु
	&tegra124_usb2_pad,
	&tegra124_ulpi_pad,
	&tegra124_hsic_pad,
	&tegra124_pcie_pad,
	&tegra124_sata_pad,
पूर्ण;

अटल पूर्णांक tegra124_usb2_port_enable(काष्ठा tegra_xusb_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra124_usb2_port_disable(काष्ठा tegra_xusb_port *port)
अणु
पूर्ण

अटल काष्ठा tegra_xusb_lane *
tegra124_usb2_port_map(काष्ठा tegra_xusb_port *port)
अणु
	वापस tegra_xusb_find_lane(port->padctl, "usb2", port->index);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_port_ops tegra124_usb2_port_ops = अणु
	.release = tegra_xusb_usb2_port_release,
	.हटाओ = tegra_xusb_usb2_port_हटाओ,
	.enable = tegra124_usb2_port_enable,
	.disable = tegra124_usb2_port_disable,
	.map = tegra124_usb2_port_map,
पूर्ण;

अटल पूर्णांक tegra124_ulpi_port_enable(काष्ठा tegra_xusb_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra124_ulpi_port_disable(काष्ठा tegra_xusb_port *port)
अणु
पूर्ण

अटल काष्ठा tegra_xusb_lane *
tegra124_ulpi_port_map(काष्ठा tegra_xusb_port *port)
अणु
	वापस tegra_xusb_find_lane(port->padctl, "ulpi", port->index);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_port_ops tegra124_ulpi_port_ops = अणु
	.release = tegra_xusb_ulpi_port_release,
	.enable = tegra124_ulpi_port_enable,
	.disable = tegra124_ulpi_port_disable,
	.map = tegra124_ulpi_port_map,
पूर्ण;

अटल पूर्णांक tegra124_hsic_port_enable(काष्ठा tegra_xusb_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra124_hsic_port_disable(काष्ठा tegra_xusb_port *port)
अणु
पूर्ण

अटल काष्ठा tegra_xusb_lane *
tegra124_hsic_port_map(काष्ठा tegra_xusb_port *port)
अणु
	वापस tegra_xusb_find_lane(port->padctl, "hsic", port->index);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_port_ops tegra124_hsic_port_ops = अणु
	.release = tegra_xusb_hsic_port_release,
	.enable = tegra124_hsic_port_enable,
	.disable = tegra124_hsic_port_disable,
	.map = tegra124_hsic_port_map,
पूर्ण;

अटल पूर्णांक tegra124_usb3_port_enable(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_usb3_port *usb3 = to_usb3_port(port);
	काष्ठा tegra_xusb_padctl *padctl = port->padctl;
	काष्ठा tegra_xusb_lane *lane = usb3->base.lane;
	अचिन्हित पूर्णांक index = port->index, offset;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_SS_PORT_MAP);

	अगर (!usb3->पूर्णांकernal)
		value &= ~XUSB_PADCTL_SS_PORT_MAP_PORTX_INTERNAL(index);
	अन्यथा
		value |= XUSB_PADCTL_SS_PORT_MAP_PORTX_INTERNAL(index);

	value &= ~XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP_MASK(index);
	value |= XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP(index, usb3->port);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_SS_PORT_MAP);

	/*
	 * TODO: move this code पूर्णांकo the PCIe/SATA PHY ->घातer_on() callbacks
	 * and conditionalize based on mux function? This seems to work, but
	 * might not be the exact proper sequence.
	 */
	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_USB3_PADX_CTL2(index));
	value &= ~((XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_WANDER_MASK <<
		    XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_WANDER_SHIFT) |
		   (XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_MASK <<
		    XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_SHIFT) |
		   (XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_CDR_CNTL_MASK <<
		    XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_CDR_CNTL_SHIFT));
	value |= (XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_WANDER_VAL <<
		  XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_WANDER_SHIFT) |
		 (XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_CDR_CNTL_VAL <<
		  XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_CDR_CNTL_SHIFT) |
		 (XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_VAL <<
		  XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_SHIFT);

	अगर (usb3->context_saved) अणु
		value &= ~((XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_G_MASK <<
			    XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_G_SHIFT) |
			   (XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_Z_MASK <<
			    XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_Z_SHIFT));
		value |= (usb3->ctle_g <<
			  XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_G_SHIFT) |
			 (usb3->ctle_z <<
			  XUSB_PADCTL_IOPHY_USB3_PAD_CTL2_RX_EQ_Z_SHIFT);
	पूर्ण

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_USB3_PADX_CTL2(index));

	value = XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_VAL;

	अगर (usb3->context_saved) अणु
		value &= ~((XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_TAP_MASK <<
			    XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_TAP_SHIFT) |
			   (XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_AMP_MASK <<
			    XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_AMP_SHIFT));
		value |= (usb3->tap1 <<
			  XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_TAP_SHIFT) |
			 (usb3->amp <<
			  XUSB_PADCTL_IOPHY_USB3_PAD_CTL4_DFE_CNTL_AMP_SHIFT);
	पूर्ण

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_USB3_PADX_CTL4(index));

	अगर (lane->pad == padctl->pcie)
		offset = XUSB_PADCTL_IOPHY_MISC_PAD_PX_CTL2(lane->index);
	अन्यथा
		offset = XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL2;

	value = padctl_पढ़ोl(padctl, offset);
	value &= ~(XUSB_PADCTL_IOPHY_MISC_PAD_CTL2_SPARE_IN_MASK <<
		   XUSB_PADCTL_IOPHY_MISC_PAD_CTL2_SPARE_IN_SHIFT);
	value |= XUSB_PADCTL_IOPHY_MISC_PAD_CTL2_SPARE_IN_VAL <<
		XUSB_PADCTL_IOPHY_MISC_PAD_CTL2_SPARE_IN_SHIFT;
	padctl_ग_लिखोl(padctl, value, offset);

	अगर (lane->pad == padctl->pcie)
		offset = XUSB_PADCTL_IOPHY_MISC_PAD_PX_CTL5(lane->index);
	अन्यथा
		offset = XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL5;

	value = padctl_पढ़ोl(padctl, offset);
	value |= XUSB_PADCTL_IOPHY_MISC_PAD_CTL5_RX_QEYE_EN;
	padctl_ग_लिखोl(padctl, value, offset);

	/* Enable SATA PHY when SATA lane is used */
	अगर (lane->pad == padctl->sata) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
		value &= ~(XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL0_REFCLK_NDIV_MASK <<
			   XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL0_REFCLK_NDIV_SHIFT);
		value |= 0x2 <<
			XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL0_REFCLK_NDIV_SHIFT;
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL2);
		value &= ~((XUSB_PADCTL_IOPHY_PLL_S0_CTL2_XDIGCLK_SEL_MASK <<
			    XUSB_PADCTL_IOPHY_PLL_S0_CTL2_XDIGCLK_SEL_SHIFT) |
			   (XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL1_CP_CNTL_MASK <<
			    XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL1_CP_CNTL_SHIFT) |
			   (XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL0_CP_CNTL_MASK <<
			    XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL0_CP_CNTL_SHIFT) |
			   XUSB_PADCTL_IOPHY_PLL_S0_CTL2_TCLKOUT_EN);
		value |= (0x7 <<
			  XUSB_PADCTL_IOPHY_PLL_S0_CTL2_XDIGCLK_SEL_SHIFT) |
			 (0x8 <<
			  XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL1_CP_CNTL_SHIFT) |
			 (0x8 <<
			  XUSB_PADCTL_IOPHY_PLL_S0_CTL2_PLL0_CP_CNTL_SHIFT) |
			 XUSB_PADCTL_IOPHY_PLL_S0_CTL2_TXCLKREF_SEL;
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL2);

		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL3);
		value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL3_RCAL_BYPASS;
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL3);
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_SSPX_ELPG_VCORE_DOWN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_SSPX_ELPG_CLAMP_EN_EARLY(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_SSPX_ELPG_CLAMP_EN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	वापस 0;
पूर्ण

अटल व्योम tegra124_usb3_port_disable(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_padctl *padctl = port->padctl;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value |= XUSB_PADCTL_ELPG_PROGRAM_SSPX_ELPG_CLAMP_EN_EARLY(port->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value |= XUSB_PADCTL_ELPG_PROGRAM_SSPX_ELPG_CLAMP_EN(port->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(250, 350);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value |= XUSB_PADCTL_ELPG_PROGRAM_SSPX_ELPG_VCORE_DOWN(port->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_SS_PORT_MAP);
	value &= ~XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP_MASK(port->index);
	value |= XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP(port->index, 0x7);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_SS_PORT_MAP);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_map tegra124_usb3_map[] = अणु
	अणु 0, "pcie", 0 पूर्ण,
	अणु 1, "pcie", 1 पूर्ण,
	अणु 1, "sata", 0 पूर्ण,
	अणु 0, शून्य,   0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra124_usb3_port_map(काष्ठा tegra_xusb_port *port)
अणु
	वापस tegra_xusb_port_find_lane(port, tegra124_usb3_map, "usb3-ss");
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_port_ops tegra124_usb3_port_ops = अणु
	.release = tegra_xusb_usb3_port_release,
	.हटाओ = tegra_xusb_usb3_port_हटाओ,
	.enable = tegra124_usb3_port_enable,
	.disable = tegra124_usb3_port_disable,
	.map = tegra124_usb3_port_map,
पूर्ण;

अटल पूर्णांक
tegra124_xusb_पढ़ो_fuse_calibration(काष्ठा tegra124_xusb_fuse_calibration *fuse)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	u32 value;

	err = tegra_fuse_पढ़ोl(TEGRA_FUSE_SKU_CALIB_0, &value);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(fuse->hs_curr_level); i++) अणु
		fuse->hs_curr_level[i] =
			(value >> FUSE_SKU_CALIB_HS_CURR_LEVEL_PADX_SHIFT(i)) &
			FUSE_SKU_CALIB_HS_CURR_LEVEL_PAD_MASK;
	पूर्ण
	fuse->hs_iref_cap =
		(value >> FUSE_SKU_CALIB_HS_IREF_CAP_SHIFT) &
		FUSE_SKU_CALIB_HS_IREF_CAP_MASK;
	fuse->hs_term_range_adj =
		(value >> FUSE_SKU_CALIB_HS_TERM_RANGE_ADJ_SHIFT) &
		FUSE_SKU_CALIB_HS_TERM_RANGE_ADJ_MASK;
	fuse->hs_squelch_level =
		(value >> FUSE_SKU_CALIB_HS_SQUELCH_LEVEL_SHIFT) &
		FUSE_SKU_CALIB_HS_SQUELCH_LEVEL_MASK;

	वापस 0;
पूर्ण

अटल काष्ठा tegra_xusb_padctl *
tegra124_xusb_padctl_probe(काष्ठा device *dev,
			   स्थिर काष्ठा tegra_xusb_padctl_soc *soc)
अणु
	काष्ठा tegra124_xusb_padctl *padctl;
	पूर्णांक err;

	padctl = devm_kzalloc(dev, माप(*padctl), GFP_KERNEL);
	अगर (!padctl)
		वापस ERR_PTR(-ENOMEM);

	padctl->base.dev = dev;
	padctl->base.soc = soc;

	err = tegra124_xusb_पढ़ो_fuse_calibration(&padctl->fuse);
	अगर (err < 0)
		वापस ERR_PTR(err);

	वापस &padctl->base;
पूर्ण

अटल व्योम tegra124_xusb_padctl_हटाओ(काष्ठा tegra_xusb_padctl *padctl)
अणु
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_padctl_ops tegra124_xusb_padctl_ops = अणु
	.probe = tegra124_xusb_padctl_probe,
	.हटाओ = tegra124_xusb_padctl_हटाओ,
	.usb3_save_context = tegra124_usb3_save_context,
	.hsic_set_idle = tegra124_hsic_set_idle,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_xusb_padctl_supply_names[] = अणु
	"avdd-pll-utmip",
	"avdd-pll-erefe",
	"avdd-pex-pll",
	"hvdd-pex-pll-e",
पूर्ण;

स्थिर काष्ठा tegra_xusb_padctl_soc tegra124_xusb_padctl_soc = अणु
	.num_pads = ARRAY_SIZE(tegra124_pads),
	.pads = tegra124_pads,
	.ports = अणु
		.usb2 = अणु
			.ops = &tegra124_usb2_port_ops,
			.count = 3,
		पूर्ण,
		.ulpi = अणु
			.ops = &tegra124_ulpi_port_ops,
			.count = 1,
		पूर्ण,
		.hsic = अणु
			.ops = &tegra124_hsic_port_ops,
			.count = 2,
		पूर्ण,
		.usb3 = अणु
			.ops = &tegra124_usb3_port_ops,
			.count = 2,
		पूर्ण,
	पूर्ण,
	.ops = &tegra124_xusb_padctl_ops,
	.supply_names = tegra124_xusb_padctl_supply_names,
	.num_supplies = ARRAY_SIZE(tegra124_xusb_padctl_supply_names),
पूर्ण;
EXPORT_SYMBOL_GPL(tegra124_xusb_padctl_soc);

MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra 124 XUSB Pad Controller driver");
MODULE_LICENSE("GPL v2");
