<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 * Copyright (C) 2015 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/tegra.h>
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

#घोषणा FUSE_SKU_CALIB_HS_CURR_LEVEL_PADX_SHIFT(x) \
					((x) ? (11 + ((x) - 1) * 6) : 0)
#घोषणा FUSE_SKU_CALIB_HS_CURR_LEVEL_PAD_MASK 0x3f
#घोषणा FUSE_SKU_CALIB_HS_TERM_RANGE_ADJ_SHIFT 7
#घोषणा FUSE_SKU_CALIB_HS_TERM_RANGE_ADJ_MASK 0xf

#घोषणा FUSE_USB_CALIB_EXT_RPD_CTRL_SHIFT 0
#घोषणा FUSE_USB_CALIB_EXT_RPD_CTRL_MASK 0x1f

#घोषणा XUSB_PADCTL_USB2_PAD_MUX 0x004
#घोषणा XUSB_PADCTL_USB2_PAD_MUX_HSIC_PAD_TRK_SHIFT 16
#घोषणा XUSB_PADCTL_USB2_PAD_MUX_HSIC_PAD_TRK_MASK 0x3
#घोषणा XUSB_PADCTL_USB2_PAD_MUX_HSIC_PAD_TRK_XUSB 0x1
#घोषणा XUSB_PADCTL_USB2_PAD_MUX_USB2_BIAS_PAD_SHIFT 18
#घोषणा XUSB_PADCTL_USB2_PAD_MUX_USB2_BIAS_PAD_MASK 0x3
#घोषणा XUSB_PADCTL_USB2_PAD_MUX_USB2_BIAS_PAD_XUSB 0x1

#घोषणा XUSB_PADCTL_USB2_PORT_CAP 0x008
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_DISABLED(x) (0x0 << ((x) * 4))
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_HOST(x) (0x1 << ((x) * 4))
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_DEVICE(x) (0x2 << ((x) * 4))
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_OTG(x) (0x3 << ((x) * 4))
#घोषणा XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_MASK(x) (0x3 << ((x) * 4))

#घोषणा XUSB_PADCTL_SS_PORT_MAP 0x014
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORTX_INTERNAL(x) (1 << (((x) * 5) + 4))
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP_SHIFT(x) ((x) * 5)
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP_MASK(x) (0x7 << ((x) * 5))
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP(x, v) (((v) & 0x7) << ((x) * 5))
#घोषणा XUSB_PADCTL_SS_PORT_MAP_PORT_DISABLED 0x7

#घोषणा XUSB_PADCTL_ELPG_PROGRAM1 0x024
#घोषणा XUSB_PADCTL_ELPG_PROGRAM1_AUX_MUX_LP0_VCORE_DOWN (1 << 31)
#घोषणा XUSB_PADCTL_ELPG_PROGRAM1_AUX_MUX_LP0_CLAMP_EN_EARLY (1 << 30)
#घोषणा XUSB_PADCTL_ELPG_PROGRAM1_AUX_MUX_LP0_CLAMP_EN (1 << 29)
#घोषणा XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_VCORE_DOWN(x) (1 << (2 + (x) * 3))
#घोषणा XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN_EARLY(x) \
							(1 << (1 + (x) * 3))
#घोषणा XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN(x) (1 << ((x) * 3))

#घोषणा XUSB_PADCTL_USB3_PAD_MUX 0x028
#घोषणा XUSB_PADCTL_USB3_PAD_MUX_PCIE_IDDQ_DISABLE(x) (1 << (1 + (x)))
#घोषणा XUSB_PADCTL_USB3_PAD_MUX_SATA_IDDQ_DISABLE(x) (1 << (8 + (x)))

#घोषणा XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPADX_CTL0(x) (0x080 + (x) * 0x40)
#घोषणा XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL0_ZIP (1 << 18)
#घोषणा XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL0_ZIN (1 << 22)

#घोषणा XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPADX_CTL1(x) (0x084 + (x) * 0x40)
#घोषणा XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL1_VREG_LEV_SHIFT 7
#घोषणा XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL1_VREG_LEV_MASK 0x3
#घोषणा XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL1_VREG_LEV_VAL 0x1
#घोषणा XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL1_VREG_FIX18 (1 << 6)

#घोषणा XUSB_PADCTL_USB2_OTG_PADX_CTL0(x) (0x088 + (x) * 0x40)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD_ZI (1 << 29)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD2 (1 << 27)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD (1 << 26)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_SHIFT 0
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_MASK 0x3f

#घोषणा XUSB_PADCTL_USB2_OTG_PADX_CTL1(x) (0x08c + (x) * 0x40)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_RPD_CTRL_SHIFT 26
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_RPD_CTRL_MASK 0x1f
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_SHIFT 3
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_MASK 0xf
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DR (1 << 2)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DISC_OVRD (1 << 1)
#घोषणा XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_CHRP_OVRD (1 << 0)

#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0 0x284
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD (1 << 11)
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_SHIFT 3
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_MASK 0x7
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_VAL 0x7
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_SHIFT 0
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_MASK 0x7
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_VAL 0x2

#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL1 0x288
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL1_PD_TRK (1 << 26)
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_DONE_RESET_TIMER_SHIFT 19
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_DONE_RESET_TIMER_MASK 0x7f
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_DONE_RESET_TIMER_VAL 0x0a
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_START_TIMER_SHIFT 12
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_START_TIMER_MASK 0x7f
#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_START_TIMER_VAL 0x1e

#घोषणा XUSB_PADCTL_HSIC_PADX_CTL0(x) (0x300 + (x) * 0x20)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_RPU_STROBE (1 << 18)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA1 (1 << 17)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA0 (1 << 16)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_RPD_STROBE (1 << 15)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA1 (1 << 14)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA0 (1 << 13)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_STROBE (1 << 9)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA1 (1 << 8)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA0 (1 << 7)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_STROBE (1 << 6)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA1 (1 << 5)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA0 (1 << 4)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_STROBE (1 << 3)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA1 (1 << 2)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA0 (1 << 1)

#घोषणा XUSB_PADCTL_HSIC_PADX_CTL1(x) (0x304 + (x) * 0x20)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_SHIFT 0
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_MASK 0xf

#घोषणा XUSB_PADCTL_HSIC_PADX_CTL2(x) (0x308 + (x) * 0x20)
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_SHIFT 8
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_MASK 0xf
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_SHIFT 0
#घोषणा XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_MASK 0xff

#घोषणा XUSB_PADCTL_HSIC_PAD_TRK_CTL 0x340
#घोषणा XUSB_PADCTL_HSIC_PAD_TRK_CTL_PD_TRK (1 << 19)
#घोषणा XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_SHIFT 12
#घोषणा XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_MASK 0x7f
#घोषणा XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_VAL 0x0a
#घोषणा XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_SHIFT 5
#घोषणा XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_MASK 0x7f
#घोषणा XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_VAL 0x1e

#घोषणा XUSB_PADCTL_HSIC_STRB_TRIM_CONTROL 0x344

#घोषणा XUSB_PADCTL_UPHY_PLL_P0_CTL1 0x360
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_SHIFT 20
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_MASK 0xff
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_USB_VAL 0x19
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_SATA_VAL 0x1e
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_MDIV_SHIFT 16
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_MDIV_MASK 0x3
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_LOCKDET_STATUS (1 << 15)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_PWR_OVRD (1 << 4)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_ENABLE (1 << 3)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_SLEEP_SHIFT 1
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_SLEEP_MASK 0x3
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL1_IDDQ (1 << 0)

#घोषणा XUSB_PADCTL_UPHY_PLL_P0_CTL2 0x364
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_SHIFT 4
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_MASK 0xffffff
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_VAL 0x136
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL2_CAL_OVRD (1 << 2)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL2_CAL_DONE (1 << 1)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL2_CAL_EN (1 << 0)

#घोषणा XUSB_PADCTL_UPHY_PLL_P0_CTL4 0x36c
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL4_XDIGCLK_EN (1 << 19)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_EN (1 << 15)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_SHIFT 12
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_MASK 0x3
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_USB_VAL 0x2
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_SATA_VAL 0x0
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL4_REFCLKBUF_EN (1 << 8)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL4_REFCLK_SEL_SHIFT 4
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL4_REFCLK_SEL_MASK 0xf

#घोषणा XUSB_PADCTL_UPHY_PLL_P0_CTL5 0x370
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_SHIFT 16
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_MASK 0xff
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_VAL 0x2a

#घोषणा XUSB_PADCTL_UPHY_PLL_P0_CTL8 0x37c
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_DONE (1 << 31)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_OVRD (1 << 15)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_CLK_EN (1 << 13)
#घोषणा XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_EN (1 << 12)

#घोषणा XUSB_PADCTL_UPHY_MISC_PAD_PX_CTL1(x) (0x460 + (x) * 0x40)
#घोषणा XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_SHIFT 20
#घोषणा XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_MASK 0x3
#घोषणा XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_VAL 0x1
#घोषणा XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_TERM_EN BIT(18)
#घोषणा XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_MODE_OVRD BIT(13)

#घोषणा XUSB_PADCTL_UPHY_PLL_S0_CTL1 0x860

#घोषणा XUSB_PADCTL_UPHY_PLL_S0_CTL2 0x864

#घोषणा XUSB_PADCTL_UPHY_PLL_S0_CTL4 0x86c

#घोषणा XUSB_PADCTL_UPHY_PLL_S0_CTL5 0x870

#घोषणा XUSB_PADCTL_UPHY_PLL_S0_CTL8 0x87c

#घोषणा XUSB_PADCTL_UPHY_MISC_PAD_S0_CTL1 0x960

#घोषणा XUSB_PADCTL_UPHY_USB3_PADX_ECTL1(x) (0xa60 + (x) * 0x40)
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL1_TX_TERM_CTRL_SHIFT 16
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL1_TX_TERM_CTRL_MASK 0x3
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL1_TX_TERM_CTRL_VAL 0x2

#घोषणा XUSB_PADCTL_UPHY_USB3_PADX_ECTL2(x) (0xa64 + (x) * 0x40)
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL2_RX_CTLE_SHIFT 0
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL2_RX_CTLE_MASK 0xffff
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL2_RX_CTLE_VAL 0x00fc

#घोषणा XUSB_PADCTL_UPHY_USB3_PADX_ECTL3(x) (0xa68 + (x) * 0x40)
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL3_RX_DFE_VAL 0xc0077f1f

#घोषणा XUSB_PADCTL_UPHY_USB3_PADX_ECTL4(x) (0xa6c + (x) * 0x40)
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL4_RX_CDR_CTRL_SHIFT 16
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL4_RX_CDR_CTRL_MASK 0xffff
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL4_RX_CDR_CTRL_VAL 0x01c7

#घोषणा XUSB_PADCTL_UPHY_USB3_PADX_ECTL6(x) (0xa74 + (x) * 0x40)
#घोषणा XUSB_PADCTL_UPHY_USB3_PAD_ECTL6_RX_EQ_CTRL_H_VAL 0xfcf01368

#घोषणा XUSB_PADCTL_USB2_VBUS_ID 0xc60
#घोषणा XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_VBUS_ON (1 << 14)
#घोषणा XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_SHIFT 18
#घोषणा XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_MASK 0xf
#घोषणा XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_FLOATING 8
#घोषणा XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_GROUNDED 0

काष्ठा tegra210_xusb_fuse_calibration अणु
	u32 hs_curr_level[4];
	u32 hs_term_range_adj;
	u32 rpd_ctrl;
पूर्ण;

काष्ठा tegra210_xusb_padctl अणु
	काष्ठा tegra_xusb_padctl base;

	काष्ठा tegra210_xusb_fuse_calibration fuse;
पूर्ण;

अटल अंतरभूत काष्ठा tegra210_xusb_padctl *
to_tegra210_xusb_padctl(काष्ठा tegra_xusb_padctl *padctl)
अणु
	वापस container_of(padctl, काष्ठा tegra210_xusb_padctl, base);
पूर्ण

/* must be called under padctl->lock */
अटल पूर्णांक tegra210_pex_uphy_enable(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा tegra_xusb_pcie_pad *pcie = to_pcie_pad(padctl->pcie);
	अचिन्हित दीर्घ समयout;
	u32 value;
	पूर्णांक err;

	अगर (pcie->enable > 0) अणु
		pcie->enable++;
		वापस 0;
	पूर्ण

	err = clk_prepare_enable(pcie->pll);
	अगर (err < 0)
		वापस err;

	err = reset_control_deनिश्चित(pcie->rst);
	अगर (err < 0)
		जाओ disable;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL2);
	value &= ~(XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_MASK <<
		   XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_SHIFT);
	value |= XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_VAL <<
		 XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL2);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL5);
	value &= ~(XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_MASK <<
		   XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_SHIFT);
	value |= XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_VAL <<
		 XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL5);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL1);
	value |= XUSB_PADCTL_UPHY_PLL_CTL1_PWR_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL2);
	value |= XUSB_PADCTL_UPHY_PLL_CTL2_CAL_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL2);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL8);
	value |= XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL8);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL4);
	value &= ~((XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_MASK <<
		    XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_SHIFT) |
		   (XUSB_PADCTL_UPHY_PLL_CTL4_REFCLK_SEL_MASK <<
		    XUSB_PADCTL_UPHY_PLL_CTL4_REFCLK_SEL_SHIFT));
	value |= (XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_USB_VAL <<
		  XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_SHIFT) |
		 XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL4);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL1);
	value &= ~((XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_MDIV_MASK <<
		    XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_MDIV_SHIFT) |
		   (XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_MASK <<
		    XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_SHIFT));
	value |= XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_USB_VAL <<
		 XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL1);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL1_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL1);
	value &= ~(XUSB_PADCTL_UPHY_PLL_CTL1_SLEEP_MASK <<
		   XUSB_PADCTL_UPHY_PLL_CTL1_SLEEP_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL1);

	usleep_range(10, 20);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL4);
	value |= XUSB_PADCTL_UPHY_PLL_CTL4_REFCLKBUF_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL4);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL2);
	value |= XUSB_PADCTL_UPHY_PLL_CTL2_CAL_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL2);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL2);
		अगर (value & XUSB_PADCTL_UPHY_PLL_CTL2_CAL_DONE)
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL2);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL2_CAL_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL2);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL2);
		अगर (!(value & XUSB_PADCTL_UPHY_PLL_CTL2_CAL_DONE))
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL1);
	value |= XUSB_PADCTL_UPHY_PLL_CTL1_ENABLE;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL1);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL1);
		अगर (value & XUSB_PADCTL_UPHY_PLL_CTL1_LOCKDET_STATUS)
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL8);
	value |= XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_EN |
		 XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_CLK_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL8);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL8);
		अगर (value & XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_DONE)
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL8);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL8);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL8);
		अगर (!(value & XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_DONE))
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL8);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_CLK_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL8);

	tegra210_xusb_pll_hw_control_enable();

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL1);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL1_PWR_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL2);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL2_CAL_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL2);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_P0_CTL8);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_P0_CTL8);

	usleep_range(10, 20);

	tegra210_xusb_pll_hw_sequence_start();

	pcie->enable++;

	वापस 0;

reset:
	reset_control_निश्चित(pcie->rst);
disable:
	clk_disable_unprepare(pcie->pll);
	वापस err;
पूर्ण

अटल व्योम tegra210_pex_uphy_disable(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा tegra_xusb_pcie_pad *pcie = to_pcie_pad(padctl->pcie);

	mutex_lock(&padctl->lock);

	अगर (WARN_ON(pcie->enable == 0))
		जाओ unlock;

	अगर (--pcie->enable > 0)
		जाओ unlock;

	reset_control_निश्चित(pcie->rst);
	clk_disable_unprepare(pcie->pll);

unlock:
	mutex_unlock(&padctl->lock);
पूर्ण

/* must be called under padctl->lock */
अटल पूर्णांक tegra210_sata_uphy_enable(काष्ठा tegra_xusb_padctl *padctl, bool usb)
अणु
	काष्ठा tegra_xusb_sata_pad *sata = to_sata_pad(padctl->sata);
	अचिन्हित दीर्घ समयout;
	u32 value;
	पूर्णांक err;

	अगर (sata->enable > 0) अणु
		sata->enable++;
		वापस 0;
	पूर्ण

	err = clk_prepare_enable(sata->pll);
	अगर (err < 0)
		वापस err;

	err = reset_control_deनिश्चित(sata->rst);
	अगर (err < 0)
		जाओ disable;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL2);
	value &= ~(XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_MASK <<
		   XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_SHIFT);
	value |= XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_VAL <<
		 XUSB_PADCTL_UPHY_PLL_CTL2_CAL_CTRL_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL2);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL5);
	value &= ~(XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_MASK <<
		   XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_SHIFT);
	value |= XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_VAL <<
		 XUSB_PADCTL_UPHY_PLL_CTL5_DCO_CTRL_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL5);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_UPHY_PLL_CTL1_PWR_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL2);
	value |= XUSB_PADCTL_UPHY_PLL_CTL2_CAL_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL2);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL8);
	value |= XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL8);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL4);
	value &= ~((XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_MASK <<
		    XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_SHIFT) |
		   (XUSB_PADCTL_UPHY_PLL_CTL4_REFCLK_SEL_MASK <<
		    XUSB_PADCTL_UPHY_PLL_CTL4_REFCLK_SEL_SHIFT));
	value |= XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_EN;

	अगर (usb)
		value |= (XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_USB_VAL <<
			  XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_SHIFT);
	अन्यथा
		value |= (XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_SATA_VAL <<
			  XUSB_PADCTL_UPHY_PLL_CTL4_TXCLKREF_SEL_SHIFT);

	value &= ~XUSB_PADCTL_UPHY_PLL_CTL4_XDIGCLK_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL4);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL1);
	value &= ~((XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_MDIV_MASK <<
		    XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_MDIV_SHIFT) |
		   (XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_MASK <<
		    XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_SHIFT));

	अगर (usb)
		value |= XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_USB_VAL <<
			 XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_SHIFT;
	अन्यथा
		value |= XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_SATA_VAL <<
			 XUSB_PADCTL_UPHY_PLL_CTL1_FREQ_NDIV_SHIFT;

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL1_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL1);
	value &= ~(XUSB_PADCTL_UPHY_PLL_CTL1_SLEEP_MASK <<
		   XUSB_PADCTL_UPHY_PLL_CTL1_SLEEP_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL1);

	usleep_range(10, 20);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL4);
	value |= XUSB_PADCTL_UPHY_PLL_CTL4_REFCLKBUF_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL4);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL2);
	value |= XUSB_PADCTL_UPHY_PLL_CTL2_CAL_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL2);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL2);
		अगर (value & XUSB_PADCTL_UPHY_PLL_CTL2_CAL_DONE)
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL2);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL2_CAL_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL2);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL2);
		अगर (!(value & XUSB_PADCTL_UPHY_PLL_CTL2_CAL_DONE))
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_UPHY_PLL_CTL1_ENABLE;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL1);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL1);
		अगर (value & XUSB_PADCTL_UPHY_PLL_CTL1_LOCKDET_STATUS)
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL8);
	value |= XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_EN |
		 XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_CLK_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL8);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL8);
		अगर (value & XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_DONE)
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL8);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL8);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL8);
		अगर (!(value & XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_DONE))
			अवरोध;

		usleep_range(10, 20);
	पूर्ण

	अगर (समय_after_eq(jअगरfies, समयout)) अणु
		err = -ETIMEDOUT;
		जाओ reset;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL8);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_CLK_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL8);

	tegra210_sata_pll_hw_control_enable();

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL1_PWR_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL2);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL2_CAL_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL2);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_PLL_S0_CTL8);
	value &= ~XUSB_PADCTL_UPHY_PLL_CTL8_RCAL_OVRD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_PLL_S0_CTL8);

	usleep_range(10, 20);

	tegra210_sata_pll_hw_sequence_start();

	sata->enable++;

	वापस 0;

reset:
	reset_control_निश्चित(sata->rst);
disable:
	clk_disable_unprepare(sata->pll);
	वापस err;
पूर्ण

अटल व्योम tegra210_sata_uphy_disable(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा tegra_xusb_sata_pad *sata = to_sata_pad(padctl->sata);

	mutex_lock(&padctl->lock);

	अगर (WARN_ON(sata->enable == 0))
		जाओ unlock;

	अगर (--sata->enable > 0)
		जाओ unlock;

	reset_control_निश्चित(sata->rst);
	clk_disable_unprepare(sata->pll);

unlock:
	mutex_unlock(&padctl->lock);
पूर्ण

अटल पूर्णांक tegra210_xusb_padctl_enable(काष्ठा tegra_xusb_padctl *padctl)
अणु
	u32 value;

	mutex_lock(&padctl->lock);

	अगर (padctl->enable++ > 0)
		जाओ out;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM1_AUX_MUX_LP0_CLAMP_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM1_AUX_MUX_LP0_CLAMP_EN_EARLY;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM1_AUX_MUX_LP0_VCORE_DOWN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

out:
	mutex_unlock(&padctl->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_xusb_padctl_disable(काष्ठा tegra_xusb_padctl *padctl)
अणु
	u32 value;

	mutex_lock(&padctl->lock);

	अगर (WARN_ON(padctl->enable == 0))
		जाओ out;

	अगर (--padctl->enable > 0)
		जाओ out;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value |= XUSB_PADCTL_ELPG_PROGRAM1_AUX_MUX_LP0_VCORE_DOWN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value |= XUSB_PADCTL_ELPG_PROGRAM1_AUX_MUX_LP0_CLAMP_EN_EARLY;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value |= XUSB_PADCTL_ELPG_PROGRAM1_AUX_MUX_LP0_CLAMP_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

out:
	mutex_unlock(&padctl->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_hsic_set_idle(काष्ठा tegra_xusb_padctl *padctl,
				  अचिन्हित पूर्णांक index, bool idle)
अणु
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PADX_CTL0(index));

	value &= ~(XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_RPD_STROBE);

	अगर (idle)
		value |= XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA0 |
			 XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA1 |
			 XUSB_PADCTL_HSIC_PAD_CTL0_RPU_STROBE;
	अन्यथा
		value &= ~(XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA0 |
			   XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA1 |
			   XUSB_PADCTL_HSIC_PAD_CTL0_RPU_STROBE);

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL0(index));

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_usb3_set_lfps_detect(काष्ठा tegra_xusb_padctl *padctl,
					 अचिन्हित पूर्णांक index, bool enable)
अणु
	काष्ठा tegra_xusb_port *port;
	काष्ठा tegra_xusb_lane *lane;
	u32 value, offset;

	port = tegra_xusb_find_port(padctl, "usb3", index);
	अगर (!port)
		वापस -ENODEV;

	lane = port->lane;

	अगर (lane->pad == padctl->pcie)
		offset = XUSB_PADCTL_UPHY_MISC_PAD_PX_CTL1(lane->index);
	अन्यथा
		offset = XUSB_PADCTL_UPHY_MISC_PAD_S0_CTL1;

	value = padctl_पढ़ोl(padctl, offset);

	value &= ~((XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_MASK <<
		    XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_SHIFT) |
		   XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_TERM_EN |
		   XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_MODE_OVRD);

	अगर (!enable) अणु
		value |= (XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_VAL <<
			  XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_IDLE_MODE_SHIFT) |
			 XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_TERM_EN |
			 XUSB_PADCTL_UPHY_MISC_PAD_CTL1_AUX_RX_MODE_OVRD;
	पूर्ण

	padctl_ग_लिखोl(padctl, value, offset);

	वापस 0;
पूर्ण

#घोषणा TEGRA210_LANE(_name, _offset, _shअगरt, _mask, _type)		\
	अणु								\
		.name = _name,						\
		.offset = _offset,					\
		.shअगरt = _shअगरt,					\
		.mask = _mask,						\
		.num_funcs = ARRAY_SIZE(tegra210_##_type##_functions),	\
		.funcs = tegra210_##_type##_functions,			\
	पूर्ण

अटल स्थिर अक्षर *tegra210_usb2_functions[] = अणु
	"snps",
	"xusb",
	"uart"
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra210_usb2_lanes[] = अणु
	TEGRA210_LANE("usb2-0", 0x004,  0, 0x3, usb2),
	TEGRA210_LANE("usb2-1", 0x004,  2, 0x3, usb2),
	TEGRA210_LANE("usb2-2", 0x004,  4, 0x3, usb2),
	TEGRA210_LANE("usb2-3", 0x004,  6, 0x3, usb2),
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra210_usb2_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
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

अटल व्योम tegra210_usb2_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_usb2_lane *usb2 = to_usb2_lane(lane);

	kमुक्त(usb2);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra210_usb2_lane_ops = अणु
	.probe = tegra210_usb2_lane_probe,
	.हटाओ = tegra210_usb2_lane_हटाओ,
पूर्ण;

अटल पूर्णांक tegra210_usb2_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_PAD_MUX);
	value &= ~(XUSB_PADCTL_USB2_PAD_MUX_USB2_BIAS_PAD_MASK <<
		   XUSB_PADCTL_USB2_PAD_MUX_USB2_BIAS_PAD_SHIFT);
	value |= XUSB_PADCTL_USB2_PAD_MUX_USB2_BIAS_PAD_XUSB <<
		 XUSB_PADCTL_USB2_PAD_MUX_USB2_BIAS_PAD_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_PAD_MUX);

	वापस tegra210_xusb_padctl_enable(padctl);
पूर्ण

अटल पूर्णांक tegra210_usb2_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra210_xusb_padctl_disable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra210_xusb_padctl_vbus_override(काष्ठा tegra_xusb_padctl *padctl,
					      bool status)
अणु
	u32 value;

	dev_dbg(padctl->dev, "%s vbus override\n", status ? "set" : "clear");

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_VBUS_ID);

	अगर (status) अणु
		value |= XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_VBUS_ON;
		value &= ~(XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_MASK <<
			   XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_SHIFT);
		value |= XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_FLOATING <<
			 XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_SHIFT;
	पूर्ण अन्यथा अणु
		value &= ~XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_VBUS_ON;
	पूर्ण

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_VBUS_ID);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_xusb_padctl_id_override(काष्ठा tegra_xusb_padctl *padctl,
					    bool status)
अणु
	u32 value;

	dev_dbg(padctl->dev, "%s id override\n", status ? "set" : "clear");

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_VBUS_ID);

	अगर (status) अणु
		अगर (value & XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_VBUS_ON) अणु
			value &= ~XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_VBUS_ON;
			padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_VBUS_ID);
			usleep_range(1000, 2000);

			value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_VBUS_ID);
		पूर्ण

		value &= ~(XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_MASK <<
			   XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_SHIFT);
		value |= XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_GROUNDED <<
			 XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_SHIFT;
	पूर्ण अन्यथा अणु
		value &= ~(XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_MASK <<
			   XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_SHIFT);
		value |= XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_FLOATING <<
			 XUSB_PADCTL_USB2_VBUS_ID_OVERRIDE_SHIFT;
	पूर्ण

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_VBUS_ID);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_usb2_phy_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode,
				      पूर्णांक submode)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra_xusb_usb2_port *port = tegra_xusb_find_usb2_port(padctl,
								lane->index);
	पूर्णांक err = 0;

	mutex_lock(&padctl->lock);

	dev_dbg(&port->base.dev, "%s: mode %d", __func__, mode);

	अगर (mode == PHY_MODE_USB_OTG) अणु
		अगर (submode == USB_ROLE_HOST) अणु
			tegra210_xusb_padctl_id_override(padctl, true);

			err = regulator_enable(port->supply);
		पूर्ण अन्यथा अगर (submode == USB_ROLE_DEVICE) अणु
			tegra210_xusb_padctl_vbus_override(padctl, true);
		पूर्ण अन्यथा अगर (submode == USB_ROLE_NONE) अणु
			/*
			 * When port is peripheral only or role transitions to
			 * USB_ROLE_NONE from USB_ROLE_DEVICE, regulator is not
			 * be enabled.
			 */
			अगर (regulator_is_enabled(port->supply))
				regulator_disable(port->supply);

			tegra210_xusb_padctl_id_override(padctl, false);
			tegra210_xusb_padctl_vbus_override(padctl, false);
		पूर्ण
	पूर्ण

	mutex_unlock(&padctl->lock);

	वापस err;
पूर्ण

अटल पूर्णांक tegra210_usb2_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_usb2_lane *usb2 = to_usb2_lane(lane);
	काष्ठा tegra_xusb_usb2_pad *pad = to_usb2_pad(lane->pad);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra210_xusb_padctl *priv;
	काष्ठा tegra_xusb_usb2_port *port;
	अचिन्हित पूर्णांक index = lane->index;
	u32 value;
	पूर्णांक err;

	port = tegra_xusb_find_usb2_port(padctl, index);
	अगर (!port) अणु
		dev_err(&phy->dev, "no port found for USB2 lane %u\n", index);
		वापस -ENODEV;
	पूर्ण

	priv = to_tegra210_xusb_padctl(padctl);

	अगर (port->usb3_port_fake != -1) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_SS_PORT_MAP);
		value &= ~XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP_MASK(
					port->usb3_port_fake);
		value |= XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP(
					port->usb3_port_fake, index);
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_SS_PORT_MAP);

		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
		value &= ~XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_VCORE_DOWN(
					port->usb3_port_fake);
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

		usleep_range(100, 200);

		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
		value &= ~XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN_EARLY(
					port->usb3_port_fake);
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

		usleep_range(100, 200);

		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
		value &= ~XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN(
					port->usb3_port_fake);
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value &= ~((XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_MASK <<
		    XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_SHIFT) |
		   (XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_MASK <<
		    XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_SHIFT));
	value |= (XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_VAL <<
		  XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_SHIFT);

	अगर (tegra_sku_info.revision < TEGRA_REVISION_A02)
		value |=
			(XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_VAL <<
			XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_SHIFT);

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_PORT_CAP);
	value &= ~XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_MASK(index);
	अगर (port->mode == USB_DR_MODE_UNKNOWN)
		value |= XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_DISABLED(index);
	अन्यथा अगर (port->mode == USB_DR_MODE_PERIPHERAL)
		value |= XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_DEVICE(index);
	अन्यथा अगर (port->mode == USB_DR_MODE_HOST)
		value |= XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_HOST(index);
	अन्यथा अगर (port->mode == USB_DR_MODE_OTG)
		value |= XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_OTG(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_PORT_CAP);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));
	value &= ~((XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_SHIFT) |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD2 |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD_ZI);
	value |= (priv->fuse.hs_curr_level[index] +
		  usb2->hs_curr_level_offset) <<
		 XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));
	value &= ~((XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_SHIFT) |
		   (XUSB_PADCTL_USB2_OTG_PAD_CTL1_RPD_CTRL_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL1_RPD_CTRL_SHIFT) |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DR |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_CHRP_OVRD |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DISC_OVRD);
	value |= (priv->fuse.hs_term_range_adj <<
		  XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_SHIFT) |
		 (priv->fuse.rpd_ctrl <<
		  XUSB_PADCTL_USB2_OTG_PAD_CTL1_RPD_CTRL_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));

	value = padctl_पढ़ोl(padctl,
			     XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPADX_CTL1(index));
	value &= ~(XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL1_VREG_LEV_MASK <<
		   XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL1_VREG_LEV_SHIFT);
	अगर (port->mode == USB_DR_MODE_HOST)
		value |= XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL1_VREG_FIX18;
	अन्यथा
		value |=
		      XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL1_VREG_LEV_VAL <<
		      XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL1_VREG_LEV_SHIFT;
	padctl_ग_लिखोl(padctl, value,
		      XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPADX_CTL1(index));

	अगर (port->supply && port->mode == USB_DR_MODE_HOST) अणु
		err = regulator_enable(port->supply);
		अगर (err)
			वापस err;
	पूर्ण

	mutex_lock(&padctl->lock);

	अगर (pad->enable > 0) अणु
		pad->enable++;
		mutex_unlock(&padctl->lock);
		वापस 0;
	पूर्ण

	err = clk_prepare_enable(pad->clk);
	अगर (err)
		जाओ disable_regulator;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);
	value &= ~((XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_START_TIMER_MASK <<
		    XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_START_TIMER_SHIFT) |
		   (XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_DONE_RESET_TIMER_MASK <<
		    XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_DONE_RESET_TIMER_SHIFT));
	value |= (XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_START_TIMER_VAL <<
		  XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_START_TIMER_SHIFT) |
		 (XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_DONE_RESET_TIMER_VAL <<
		  XUSB_PADCTL_USB2_BIAS_PAD_CTL1_TRK_DONE_RESET_TIMER_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value &= ~XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

	udelay(1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);
	value &= ~XUSB_PADCTL_USB2_BIAS_PAD_CTL1_PD_TRK;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);

	udelay(50);

	clk_disable_unprepare(pad->clk);

	pad->enable++;
	mutex_unlock(&padctl->lock);

	वापस 0;

disable_regulator:
	regulator_disable(port->supply);
	mutex_unlock(&padctl->lock);
	वापस err;
पूर्ण

अटल पूर्णांक tegra210_usb2_phy_घातer_off(काष्ठा phy *phy)
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

	mutex_lock(&padctl->lock);

	अगर (port->usb3_port_fake != -1) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
		value |= XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN_EARLY(
					port->usb3_port_fake);
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

		usleep_range(100, 200);

		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
		value |= XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN(
					port->usb3_port_fake);
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

		usleep_range(250, 350);

		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
		value |= XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_VCORE_DOWN(
					port->usb3_port_fake);
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_SS_PORT_MAP);
		value |= XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP(port->usb3_port_fake,
					XUSB_PADCTL_SS_PORT_MAP_PORT_DISABLED);
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_SS_PORT_MAP);
	पूर्ण

	अगर (WARN_ON(pad->enable == 0))
		जाओ out;

	अगर (--pad->enable > 0)
		जाओ out;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value |= XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

out:
	regulator_disable(port->supply);
	mutex_unlock(&padctl->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops tegra210_usb2_phy_ops = अणु
	.init = tegra210_usb2_phy_init,
	.निकास = tegra210_usb2_phy_निकास,
	.घातer_on = tegra210_usb2_phy_घातer_on,
	.घातer_off = tegra210_usb2_phy_घातer_off,
	.set_mode = tegra210_usb2_phy_set_mode,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra210_usb2_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
			स्थिर काष्ठा tegra_xusb_pad_soc *soc,
			काष्ठा device_node *np)
अणु
	काष्ठा tegra_xusb_usb2_pad *usb2;
	काष्ठा tegra_xusb_pad *pad;
	पूर्णांक err;

	usb2 = kzalloc(माप(*usb2), GFP_KERNEL);
	अगर (!usb2)
		वापस ERR_PTR(-ENOMEM);

	pad = &usb2->base;
	pad->ops = &tegra210_usb2_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(usb2);
		जाओ out;
	पूर्ण

	usb2->clk = devm_clk_get(&pad->dev, "trk");
	अगर (IS_ERR(usb2->clk)) अणु
		err = PTR_ERR(usb2->clk);
		dev_err(&pad->dev, "failed to get trk clock: %d\n", err);
		जाओ unरेजिस्टर;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &tegra210_usb2_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra210_usb2_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_usb2_pad *usb2 = to_usb2_pad(pad);

	kमुक्त(usb2);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra210_usb2_ops = अणु
	.probe = tegra210_usb2_pad_probe,
	.हटाओ = tegra210_usb2_pad_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra210_usb2_pad = अणु
	.name = "usb2",
	.num_lanes = ARRAY_SIZE(tegra210_usb2_lanes),
	.lanes = tegra210_usb2_lanes,
	.ops = &tegra210_usb2_ops,
पूर्ण;

अटल स्थिर अक्षर *tegra210_hsic_functions[] = अणु
	"snps",
	"xusb",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra210_hsic_lanes[] = अणु
	TEGRA210_LANE("hsic-0", 0x004, 14, 0x1, hsic),
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra210_hsic_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
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

अटल व्योम tegra210_hsic_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_hsic_lane *hsic = to_hsic_lane(lane);

	kमुक्त(hsic);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra210_hsic_lane_ops = अणु
	.probe = tegra210_hsic_lane_probe,
	.हटाओ = tegra210_hsic_lane_हटाओ,
पूर्ण;

अटल पूर्णांक tegra210_hsic_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_PAD_MUX);
	value &= ~(XUSB_PADCTL_USB2_PAD_MUX_HSIC_PAD_TRK_MASK <<
		   XUSB_PADCTL_USB2_PAD_MUX_HSIC_PAD_TRK_SHIFT);
	value |= XUSB_PADCTL_USB2_PAD_MUX_HSIC_PAD_TRK_XUSB <<
		 XUSB_PADCTL_USB2_PAD_MUX_HSIC_PAD_TRK_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_PAD_MUX);

	वापस tegra210_xusb_padctl_enable(padctl);
पूर्ण

अटल पूर्णांक tegra210_hsic_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra210_xusb_padctl_disable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra210_hsic_phy_घातer_on(काष्ठा phy *phy)
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
	value &= ~(XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_MASK <<
		   XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_SHIFT);
	value |= (hsic->tx_rtune_p <<
		  XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL1(index));

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

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PADX_CTL0(index));
	value &= ~(XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_RPU_STROBE |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_STROBE |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_STROBE |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_STROBE);
	value |= XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA0 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA1 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_RPD_STROBE;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL0(index));

	err = clk_prepare_enable(pad->clk);
	अगर (err)
		जाओ disable;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PAD_TRK_CTL);
	value &= ~((XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_MASK <<
		    XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_SHIFT) |
		   (XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_MASK <<
		    XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_SHIFT));
	value |= (XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_VAL <<
		  XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_SHIFT) |
		 (XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_VAL <<
		  XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_SHIFT);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PAD_TRK_CTL);

	udelay(1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PAD_TRK_CTL);
	value &= ~XUSB_PADCTL_HSIC_PAD_TRK_CTL_PD_TRK;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PAD_TRK_CTL);

	udelay(50);

	clk_disable_unprepare(pad->clk);

	वापस 0;

disable:
	regulator_disable(pad->supply);
	वापस err;
पूर्ण

अटल पूर्णांक tegra210_hsic_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_hsic_pad *pad = to_hsic_pad(lane->pad);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	अचिन्हित पूर्णांक index = lane->index;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_HSIC_PADX_CTL0(index));
	value |= XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA0 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA1 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_STROBE |
		 XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA0 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA1 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_STROBE |
		 XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA0 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA1 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_STROBE;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL1(index));

	regulator_disable(pad->supply);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops tegra210_hsic_phy_ops = अणु
	.init = tegra210_hsic_phy_init,
	.निकास = tegra210_hsic_phy_निकास,
	.घातer_on = tegra210_hsic_phy_घातer_on,
	.घातer_off = tegra210_hsic_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra210_hsic_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
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
	pad->ops = &tegra210_hsic_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(hsic);
		जाओ out;
	पूर्ण

	hsic->clk = devm_clk_get(&pad->dev, "trk");
	अगर (IS_ERR(hsic->clk)) अणु
		err = PTR_ERR(hsic->clk);
		dev_err(&pad->dev, "failed to get trk clock: %d\n", err);
		जाओ unरेजिस्टर;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &tegra210_hsic_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra210_hsic_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_hsic_pad *hsic = to_hsic_pad(pad);

	kमुक्त(hsic);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra210_hsic_ops = अणु
	.probe = tegra210_hsic_pad_probe,
	.हटाओ = tegra210_hsic_pad_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra210_hsic_pad = अणु
	.name = "hsic",
	.num_lanes = ARRAY_SIZE(tegra210_hsic_lanes),
	.lanes = tegra210_hsic_lanes,
	.ops = &tegra210_hsic_ops,
पूर्ण;

अटल स्थिर अक्षर *tegra210_pcie_functions[] = अणु
	"pcie-x1",
	"usb3-ss",
	"sata",
	"pcie-x4",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra210_pcie_lanes[] = अणु
	TEGRA210_LANE("pcie-0", 0x028, 12, 0x3, pcie),
	TEGRA210_LANE("pcie-1", 0x028, 14, 0x3, pcie),
	TEGRA210_LANE("pcie-2", 0x028, 16, 0x3, pcie),
	TEGRA210_LANE("pcie-3", 0x028, 18, 0x3, pcie),
	TEGRA210_LANE("pcie-4", 0x028, 20, 0x3, pcie),
	TEGRA210_LANE("pcie-5", 0x028, 22, 0x3, pcie),
	TEGRA210_LANE("pcie-6", 0x028, 24, 0x3, pcie),
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra210_pcie_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
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

अटल व्योम tegra210_pcie_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_pcie_lane *pcie = to_pcie_lane(lane);

	kमुक्त(pcie);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra210_pcie_lane_ops = अणु
	.probe = tegra210_pcie_lane_probe,
	.हटाओ = tegra210_pcie_lane_हटाओ,
पूर्ण;

अटल पूर्णांक tegra210_pcie_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra210_xusb_padctl_enable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra210_pcie_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra210_xusb_padctl_disable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra210_pcie_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	u32 value;
	पूर्णांक err;

	mutex_lock(&padctl->lock);

	err = tegra210_pex_uphy_enable(padctl);
	अगर (err < 0)
		जाओ unlock;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value |= XUSB_PADCTL_USB3_PAD_MUX_PCIE_IDDQ_DISABLE(lane->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

unlock:
	mutex_unlock(&padctl->lock);
	वापस err;
पूर्ण

अटल पूर्णांक tegra210_pcie_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value &= ~XUSB_PADCTL_USB3_PAD_MUX_PCIE_IDDQ_DISABLE(lane->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

	tegra210_pex_uphy_disable(padctl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops tegra210_pcie_phy_ops = अणु
	.init = tegra210_pcie_phy_init,
	.निकास = tegra210_pcie_phy_निकास,
	.घातer_on = tegra210_pcie_phy_घातer_on,
	.घातer_off = tegra210_pcie_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra210_pcie_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
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
	pad->ops = &tegra210_pcie_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(pcie);
		जाओ out;
	पूर्ण

	pcie->pll = devm_clk_get(&pad->dev, "pll");
	अगर (IS_ERR(pcie->pll)) अणु
		err = PTR_ERR(pcie->pll);
		dev_err(&pad->dev, "failed to get PLL: %d\n", err);
		जाओ unरेजिस्टर;
	पूर्ण

	pcie->rst = devm_reset_control_get(&pad->dev, "phy");
	अगर (IS_ERR(pcie->rst)) अणु
		err = PTR_ERR(pcie->rst);
		dev_err(&pad->dev, "failed to get PCIe pad reset: %d\n", err);
		जाओ unरेजिस्टर;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &tegra210_pcie_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra210_pcie_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_pcie_pad *pcie = to_pcie_pad(pad);

	kमुक्त(pcie);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra210_pcie_ops = अणु
	.probe = tegra210_pcie_pad_probe,
	.हटाओ = tegra210_pcie_pad_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra210_pcie_pad = अणु
	.name = "pcie",
	.num_lanes = ARRAY_SIZE(tegra210_pcie_lanes),
	.lanes = tegra210_pcie_lanes,
	.ops = &tegra210_pcie_ops,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra210_sata_lanes[] = अणु
	TEGRA210_LANE("sata-0", 0x028, 30, 0x3, pcie),
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra210_sata_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
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

अटल व्योम tegra210_sata_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_sata_lane *sata = to_sata_lane(lane);

	kमुक्त(sata);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra210_sata_lane_ops = अणु
	.probe = tegra210_sata_lane_probe,
	.हटाओ = tegra210_sata_lane_हटाओ,
पूर्ण;

अटल पूर्णांक tegra210_sata_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra210_xusb_padctl_enable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra210_sata_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

	वापस tegra210_xusb_padctl_disable(lane->pad->padctl);
पूर्ण

अटल पूर्णांक tegra210_sata_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	u32 value;
	पूर्णांक err;

	mutex_lock(&padctl->lock);

	err = tegra210_sata_uphy_enable(padctl, false);
	अगर (err < 0)
		जाओ unlock;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value |= XUSB_PADCTL_USB3_PAD_MUX_SATA_IDDQ_DISABLE(lane->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

unlock:
	mutex_unlock(&padctl->lock);
	वापस err;
पूर्ण

अटल पूर्णांक tegra210_sata_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value &= ~XUSB_PADCTL_USB3_PAD_MUX_SATA_IDDQ_DISABLE(lane->index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

	tegra210_sata_uphy_disable(lane->pad->padctl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops tegra210_sata_phy_ops = अणु
	.init = tegra210_sata_phy_init,
	.निकास = tegra210_sata_phy_निकास,
	.घातer_on = tegra210_sata_phy_घातer_on,
	.घातer_off = tegra210_sata_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra210_sata_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
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
	pad->ops = &tegra210_sata_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(sata);
		जाओ out;
	पूर्ण

	sata->rst = devm_reset_control_get(&pad->dev, "phy");
	अगर (IS_ERR(sata->rst)) अणु
		err = PTR_ERR(sata->rst);
		dev_err(&pad->dev, "failed to get SATA pad reset: %d\n", err);
		जाओ unरेजिस्टर;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &tegra210_sata_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra210_sata_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_sata_pad *sata = to_sata_pad(pad);

	kमुक्त(sata);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra210_sata_ops = अणु
	.probe = tegra210_sata_pad_probe,
	.हटाओ = tegra210_sata_pad_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra210_sata_pad = अणु
	.name = "sata",
	.num_lanes = ARRAY_SIZE(tegra210_sata_lanes),
	.lanes = tegra210_sata_lanes,
	.ops = &tegra210_sata_ops,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc * स्थिर tegra210_pads[] = अणु
	&tegra210_usb2_pad,
	&tegra210_hsic_pad,
	&tegra210_pcie_pad,
	&tegra210_sata_pad,
पूर्ण;

अटल पूर्णांक tegra210_usb2_port_enable(काष्ठा tegra_xusb_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra210_usb2_port_disable(काष्ठा tegra_xusb_port *port)
अणु
पूर्ण

अटल काष्ठा tegra_xusb_lane *
tegra210_usb2_port_map(काष्ठा tegra_xusb_port *port)
अणु
	वापस tegra_xusb_find_lane(port->padctl, "usb2", port->index);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_port_ops tegra210_usb2_port_ops = अणु
	.release = tegra_xusb_usb2_port_release,
	.हटाओ = tegra_xusb_usb2_port_हटाओ,
	.enable = tegra210_usb2_port_enable,
	.disable = tegra210_usb2_port_disable,
	.map = tegra210_usb2_port_map,
पूर्ण;

अटल पूर्णांक tegra210_hsic_port_enable(काष्ठा tegra_xusb_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra210_hsic_port_disable(काष्ठा tegra_xusb_port *port)
अणु
पूर्ण

अटल काष्ठा tegra_xusb_lane *
tegra210_hsic_port_map(काष्ठा tegra_xusb_port *port)
अणु
	वापस tegra_xusb_find_lane(port->padctl, "hsic", port->index);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_port_ops tegra210_hsic_port_ops = अणु
	.release = tegra_xusb_hsic_port_release,
	.enable = tegra210_hsic_port_enable,
	.disable = tegra210_hsic_port_disable,
	.map = tegra210_hsic_port_map,
पूर्ण;

अटल पूर्णांक tegra210_usb3_port_enable(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_usb3_port *usb3 = to_usb3_port(port);
	काष्ठा tegra_xusb_padctl *padctl = port->padctl;
	काष्ठा tegra_xusb_lane *lane = usb3->base.lane;
	अचिन्हित पूर्णांक index = port->index;
	u32 value;
	पूर्णांक err;

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
	err = regulator_enable(usb3->supply);
	अगर (err < 0)
		वापस err;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_USB3_PADX_ECTL1(index));
	value &= ~(XUSB_PADCTL_UPHY_USB3_PAD_ECTL1_TX_TERM_CTRL_MASK <<
		   XUSB_PADCTL_UPHY_USB3_PAD_ECTL1_TX_TERM_CTRL_SHIFT);
	value |= XUSB_PADCTL_UPHY_USB3_PAD_ECTL1_TX_TERM_CTRL_VAL <<
		 XUSB_PADCTL_UPHY_USB3_PAD_ECTL1_TX_TERM_CTRL_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_USB3_PADX_ECTL1(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_USB3_PADX_ECTL2(index));
	value &= ~(XUSB_PADCTL_UPHY_USB3_PAD_ECTL2_RX_CTLE_MASK <<
		   XUSB_PADCTL_UPHY_USB3_PAD_ECTL2_RX_CTLE_SHIFT);
	value |= XUSB_PADCTL_UPHY_USB3_PAD_ECTL2_RX_CTLE_VAL <<
		 XUSB_PADCTL_UPHY_USB3_PAD_ECTL2_RX_CTLE_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_USB3_PADX_ECTL2(index));

	padctl_ग_लिखोl(padctl, XUSB_PADCTL_UPHY_USB3_PAD_ECTL3_RX_DFE_VAL,
		      XUSB_PADCTL_UPHY_USB3_PADX_ECTL3(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_UPHY_USB3_PADX_ECTL4(index));
	value &= ~(XUSB_PADCTL_UPHY_USB3_PAD_ECTL4_RX_CDR_CTRL_MASK <<
		   XUSB_PADCTL_UPHY_USB3_PAD_ECTL4_RX_CDR_CTRL_SHIFT);
	value |= XUSB_PADCTL_UPHY_USB3_PAD_ECTL4_RX_CDR_CTRL_VAL <<
		 XUSB_PADCTL_UPHY_USB3_PAD_ECTL4_RX_CDR_CTRL_SHIFT;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_UPHY_USB3_PADX_ECTL4(index));

	padctl_ग_लिखोl(padctl, XUSB_PADCTL_UPHY_USB3_PAD_ECTL6_RX_EQ_CTRL_H_VAL,
		      XUSB_PADCTL_UPHY_USB3_PADX_ECTL6(index));

	अगर (lane->pad == padctl->sata)
		err = tegra210_sata_uphy_enable(padctl, true);
	अन्यथा
		err = tegra210_pex_uphy_enable(padctl);

	अगर (err) अणु
		dev_err(&port->dev, "%s: failed to enable UPHY: %d\n",
			__func__, err);
		वापस err;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_VCORE_DOWN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN_EARLY(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	वापस 0;
पूर्ण

अटल व्योम tegra210_usb3_port_disable(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_usb3_port *usb3 = to_usb3_port(port);
	काष्ठा tegra_xusb_padctl *padctl = port->padctl;
	काष्ठा tegra_xusb_lane *lane = port->lane;
	अचिन्हित पूर्णांक index = port->index;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value |= XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN_EARLY(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value |= XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_CLAMP_EN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	usleep_range(250, 350);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM1);
	value |= XUSB_PADCTL_ELPG_PROGRAM1_SSPX_ELPG_VCORE_DOWN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM1);

	अगर (lane->pad == padctl->sata)
		tegra210_sata_uphy_disable(padctl);
	अन्यथा
		tegra210_pex_uphy_disable(padctl);

	regulator_disable(usb3->supply);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_SS_PORT_MAP);
	value &= ~XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP_MASK(index);
	value |= XUSB_PADCTL_SS_PORT_MAP_PORTX_MAP(index, 0x7);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_SS_PORT_MAP);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_map tegra210_usb3_map[] = अणु
	अणु 0, "pcie", 6 पूर्ण,
	अणु 1, "pcie", 5 पूर्ण,
	अणु 2, "pcie", 0 पूर्ण,
	अणु 2, "pcie", 3 पूर्ण,
	अणु 3, "pcie", 4 पूर्ण,
	अणु 3, "pcie", 4 पूर्ण,
	अणु 0, शून्य,   0 पूर्ण
पूर्ण;

अटल काष्ठा tegra_xusb_lane *
tegra210_usb3_port_map(काष्ठा tegra_xusb_port *port)
अणु
	वापस tegra_xusb_port_find_lane(port, tegra210_usb3_map, "usb3-ss");
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_port_ops tegra210_usb3_port_ops = अणु
	.release = tegra_xusb_usb3_port_release,
	.हटाओ = tegra_xusb_usb3_port_हटाओ,
	.enable = tegra210_usb3_port_enable,
	.disable = tegra210_usb3_port_disable,
	.map = tegra210_usb3_port_map,
पूर्ण;

अटल पूर्णांक tegra210_uपंचांगi_port_reset(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_padctl *padctl;
	काष्ठा tegra_xusb_lane *lane;
	u32 value;

	lane = phy_get_drvdata(phy);
	padctl = lane->pad->padctl;

	value = padctl_पढ़ोl(padctl,
		     XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPADX_CTL0(lane->index));

	अगर ((value & XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL0_ZIP) ||
	    (value & XUSB_PADCTL_USB2_BATTERY_CHRG_OTGPAD_CTL0_ZIN)) अणु
		tegra210_xusb_padctl_vbus_override(padctl, false);
		tegra210_xusb_padctl_vbus_override(padctl, true);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
tegra210_xusb_पढ़ो_fuse_calibration(काष्ठा tegra210_xusb_fuse_calibration *fuse)
अणु
	अचिन्हित पूर्णांक i;
	u32 value;
	पूर्णांक err;

	err = tegra_fuse_पढ़ोl(TEGRA_FUSE_SKU_CALIB_0, &value);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(fuse->hs_curr_level); i++) अणु
		fuse->hs_curr_level[i] =
			(value >> FUSE_SKU_CALIB_HS_CURR_LEVEL_PADX_SHIFT(i)) &
			FUSE_SKU_CALIB_HS_CURR_LEVEL_PAD_MASK;
	पूर्ण

	fuse->hs_term_range_adj =
		(value >> FUSE_SKU_CALIB_HS_TERM_RANGE_ADJ_SHIFT) &
		FUSE_SKU_CALIB_HS_TERM_RANGE_ADJ_MASK;

	err = tegra_fuse_पढ़ोl(TEGRA_FUSE_USB_CALIB_EXT_0, &value);
	अगर (err < 0)
		वापस err;

	fuse->rpd_ctrl =
		(value >> FUSE_USB_CALIB_EXT_RPD_CTRL_SHIFT) &
		FUSE_USB_CALIB_EXT_RPD_CTRL_MASK;

	वापस 0;
पूर्ण

अटल काष्ठा tegra_xusb_padctl *
tegra210_xusb_padctl_probe(काष्ठा device *dev,
			   स्थिर काष्ठा tegra_xusb_padctl_soc *soc)
अणु
	काष्ठा tegra210_xusb_padctl *padctl;
	पूर्णांक err;

	padctl = devm_kzalloc(dev, माप(*padctl), GFP_KERNEL);
	अगर (!padctl)
		वापस ERR_PTR(-ENOMEM);

	padctl->base.dev = dev;
	padctl->base.soc = soc;

	err = tegra210_xusb_पढ़ो_fuse_calibration(&padctl->fuse);
	अगर (err < 0)
		वापस ERR_PTR(err);

	वापस &padctl->base;
पूर्ण

अटल व्योम tegra210_xusb_padctl_हटाओ(काष्ठा tegra_xusb_padctl *padctl)
अणु
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_padctl_ops tegra210_xusb_padctl_ops = अणु
	.probe = tegra210_xusb_padctl_probe,
	.हटाओ = tegra210_xusb_padctl_हटाओ,
	.usb3_set_lfps_detect = tegra210_usb3_set_lfps_detect,
	.hsic_set_idle = tegra210_hsic_set_idle,
	.vbus_override = tegra210_xusb_padctl_vbus_override,
	.uपंचांगi_port_reset = tegra210_uपंचांगi_port_reset,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_xusb_padctl_supply_names[] = अणु
	"avdd-pll-utmip",
	"avdd-pll-uerefe",
	"dvdd-pex-pll",
	"hvdd-pex-pll-e",
पूर्ण;

स्थिर काष्ठा tegra_xusb_padctl_soc tegra210_xusb_padctl_soc = अणु
	.num_pads = ARRAY_SIZE(tegra210_pads),
	.pads = tegra210_pads,
	.ports = अणु
		.usb2 = अणु
			.ops = &tegra210_usb2_port_ops,
			.count = 4,
		पूर्ण,
		.hsic = अणु
			.ops = &tegra210_hsic_port_ops,
			.count = 1,
		पूर्ण,
		.usb3 = अणु
			.ops = &tegra210_usb3_port_ops,
			.count = 4,
		पूर्ण,
	पूर्ण,
	.ops = &tegra210_xusb_padctl_ops,
	.supply_names = tegra210_xusb_padctl_supply_names,
	.num_supplies = ARRAY_SIZE(tegra210_xusb_padctl_supply_names),
	.need_fake_usb3_port = true,
पूर्ण;
EXPORT_SYMBOL_GPL(tegra210_xusb_padctl_soc);

MODULE_AUTHOR("Andrew Bresticker <abrestic@chromium.org>");
MODULE_DESCRIPTION("NVIDIA Tegra 210 XUSB Pad Controller driver");
MODULE_LICENSE("GPL v2");
