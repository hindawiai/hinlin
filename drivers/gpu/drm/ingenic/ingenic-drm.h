<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
//
// Ingenic JZ47xx KMS driver - Register definitions and निजी API
//
// Copyright (C) 2020, Paul Cercueil <paul@crapouillou.net>

#अगर_अघोषित DRIVERS_GPU_DRM_INGENIC_INGENIC_DRM_H
#घोषणा DRIVERS_GPU_DRM_INGENIC_INGENIC_DRM_H

#समावेश <linux/bitops.h>
#समावेश <linux/types.h>

#घोषणा JZ_REG_LCD_CFG				0x00
#घोषणा JZ_REG_LCD_VSYNC			0x04
#घोषणा JZ_REG_LCD_HSYNC			0x08
#घोषणा JZ_REG_LCD_VAT				0x0C
#घोषणा JZ_REG_LCD_DAH				0x10
#घोषणा JZ_REG_LCD_DAV				0x14
#घोषणा JZ_REG_LCD_PS				0x18
#घोषणा JZ_REG_LCD_CLS				0x1C
#घोषणा JZ_REG_LCD_SPL				0x20
#घोषणा JZ_REG_LCD_REV				0x24
#घोषणा JZ_REG_LCD_CTRL				0x30
#घोषणा JZ_REG_LCD_STATE			0x34
#घोषणा JZ_REG_LCD_IID				0x38
#घोषणा JZ_REG_LCD_DA0				0x40
#घोषणा JZ_REG_LCD_SA0				0x44
#घोषणा JZ_REG_LCD_FID0				0x48
#घोषणा JZ_REG_LCD_CMD0				0x4C
#घोषणा JZ_REG_LCD_DA1				0x50
#घोषणा JZ_REG_LCD_SA1				0x54
#घोषणा JZ_REG_LCD_FID1				0x58
#घोषणा JZ_REG_LCD_CMD1				0x5C
#घोषणा JZ_REG_LCD_RGBC				0x90
#घोषणा JZ_REG_LCD_OSDC				0x100
#घोषणा JZ_REG_LCD_OSDCTRL			0x104
#घोषणा JZ_REG_LCD_OSDS				0x108
#घोषणा JZ_REG_LCD_BGC				0x10c
#घोषणा JZ_REG_LCD_KEY0				0x110
#घोषणा JZ_REG_LCD_KEY1				0x114
#घोषणा JZ_REG_LCD_ALPHA			0x118
#घोषणा JZ_REG_LCD_IPUR				0x11c
#घोषणा JZ_REG_LCD_XYP0				0x120
#घोषणा JZ_REG_LCD_XYP1				0x124
#घोषणा JZ_REG_LCD_SIZE0			0x128
#घोषणा JZ_REG_LCD_SIZE1			0x12c

#घोषणा JZ_LCD_CFG_SLCD				BIT(31)
#घोषणा JZ_LCD_CFG_PS_DISABLE			BIT(23)
#घोषणा JZ_LCD_CFG_CLS_DISABLE			BIT(22)
#घोषणा JZ_LCD_CFG_SPL_DISABLE			BIT(21)
#घोषणा JZ_LCD_CFG_REV_DISABLE			BIT(20)
#घोषणा JZ_LCD_CFG_HSYNCM			BIT(19)
#घोषणा JZ_LCD_CFG_PCLKM			BIT(18)
#घोषणा JZ_LCD_CFG_INV				BIT(17)
#घोषणा JZ_LCD_CFG_SYNC_सूची			BIT(16)
#घोषणा JZ_LCD_CFG_PS_POLARITY			BIT(15)
#घोषणा JZ_LCD_CFG_CLS_POLARITY			BIT(14)
#घोषणा JZ_LCD_CFG_SPL_POLARITY			BIT(13)
#घोषणा JZ_LCD_CFG_REV_POLARITY			BIT(12)
#घोषणा JZ_LCD_CFG_HSYNC_ACTIVE_LOW		BIT(11)
#घोषणा JZ_LCD_CFG_PCLK_FALLING_EDGE		BIT(10)
#घोषणा JZ_LCD_CFG_DE_ACTIVE_LOW		BIT(9)
#घोषणा JZ_LCD_CFG_VSYNC_ACTIVE_LOW		BIT(8)
#घोषणा JZ_LCD_CFG_18_BIT			BIT(7)
#घोषणा JZ_LCD_CFG_PDW				(BIT(5) | BIT(4))

#घोषणा JZ_LCD_CFG_MODE_GENERIC_16BIT		0
#घोषणा JZ_LCD_CFG_MODE_GENERIC_18BIT		BIT(7)
#घोषणा JZ_LCD_CFG_MODE_GENERIC_24BIT		BIT(6)

#घोषणा JZ_LCD_CFG_MODE_SPECIAL_TFT_1		1
#घोषणा JZ_LCD_CFG_MODE_SPECIAL_TFT_2		2
#घोषणा JZ_LCD_CFG_MODE_SPECIAL_TFT_3		3

#घोषणा JZ_LCD_CFG_MODE_TV_OUT_P		4
#घोषणा JZ_LCD_CFG_MODE_TV_OUT_I		6

#घोषणा JZ_LCD_CFG_MODE_SINGLE_COLOR_STN	8
#घोषणा JZ_LCD_CFG_MODE_SINGLE_MONOCHROME_STN	9
#घोषणा JZ_LCD_CFG_MODE_DUAL_COLOR_STN		10
#घोषणा JZ_LCD_CFG_MODE_DUAL_MONOCHROME_STN	11

#घोषणा JZ_LCD_CFG_MODE_8BIT_SERIAL		12
#घोषणा JZ_LCD_CFG_MODE_LCM			13

#घोषणा JZ_LCD_VSYNC_VPS_OFFSET			16
#घोषणा JZ_LCD_VSYNC_VPE_OFFSET			0

#घोषणा JZ_LCD_HSYNC_HPS_OFFSET			16
#घोषणा JZ_LCD_HSYNC_HPE_OFFSET			0

#घोषणा JZ_LCD_VAT_HT_OFFSET			16
#घोषणा JZ_LCD_VAT_VT_OFFSET			0

#घोषणा JZ_LCD_DAH_HDS_OFFSET			16
#घोषणा JZ_LCD_DAH_HDE_OFFSET			0

#घोषणा JZ_LCD_DAV_VDS_OFFSET			16
#घोषणा JZ_LCD_DAV_VDE_OFFSET			0

#घोषणा JZ_LCD_CTRL_BURST_4			(0x0 << 28)
#घोषणा JZ_LCD_CTRL_BURST_8			(0x1 << 28)
#घोषणा JZ_LCD_CTRL_BURST_16			(0x2 << 28)
#घोषणा JZ_LCD_CTRL_RGB555			BIT(27)
#घोषणा JZ_LCD_CTRL_OFUP			BIT(26)
#घोषणा JZ_LCD_CTRL_FRC_GRAYSCALE_16		(0x0 << 24)
#घोषणा JZ_LCD_CTRL_FRC_GRAYSCALE_4		(0x1 << 24)
#घोषणा JZ_LCD_CTRL_FRC_GRAYSCALE_2		(0x2 << 24)
#घोषणा JZ_LCD_CTRL_PDD_MASK			(0xff << 16)
#घोषणा JZ_LCD_CTRL_खातापूर्ण_IRQ			BIT(13)
#घोषणा JZ_LCD_CTRL_SOF_IRQ			BIT(12)
#घोषणा JZ_LCD_CTRL_OFU_IRQ			BIT(11)
#घोषणा JZ_LCD_CTRL_IFU0_IRQ			BIT(10)
#घोषणा JZ_LCD_CTRL_IFU1_IRQ			BIT(9)
#घोषणा JZ_LCD_CTRL_DD_IRQ			BIT(8)
#घोषणा JZ_LCD_CTRL_QDD_IRQ			BIT(7)
#घोषणा JZ_LCD_CTRL_REVERSE_ENDIAN		BIT(6)
#घोषणा JZ_LCD_CTRL_LSB_FISRT			BIT(5)
#घोषणा JZ_LCD_CTRL_DISABLE			BIT(4)
#घोषणा JZ_LCD_CTRL_ENABLE			BIT(3)
#घोषणा JZ_LCD_CTRL_BPP_1			0x0
#घोषणा JZ_LCD_CTRL_BPP_2			0x1
#घोषणा JZ_LCD_CTRL_BPP_4			0x2
#घोषणा JZ_LCD_CTRL_BPP_8			0x3
#घोषणा JZ_LCD_CTRL_BPP_15_16			0x4
#घोषणा JZ_LCD_CTRL_BPP_18_24			0x5
#घोषणा JZ_LCD_CTRL_BPP_24_COMP			0x6
#घोषणा JZ_LCD_CTRL_BPP_30			0x7
#घोषणा JZ_LCD_CTRL_BPP_MASK			(JZ_LCD_CTRL_RGB555 | 0x7)

#घोषणा JZ_LCD_CMD_SOF_IRQ			BIT(31)
#घोषणा JZ_LCD_CMD_खातापूर्ण_IRQ			BIT(30)
#घोषणा JZ_LCD_CMD_ENABLE_PAL			BIT(28)

#घोषणा JZ_LCD_SYNC_MASK			0x3ff

#घोषणा JZ_LCD_STATE_खातापूर्ण_IRQ			BIT(5)
#घोषणा JZ_LCD_STATE_SOF_IRQ			BIT(4)
#घोषणा JZ_LCD_STATE_DISABLED			BIT(0)

#घोषणा JZ_LCD_RGBC_ODD_RGB			(0x0 << 4)
#घोषणा JZ_LCD_RGBC_ODD_RBG			(0x1 << 4)
#घोषणा JZ_LCD_RGBC_ODD_GRB			(0x2 << 4)
#घोषणा JZ_LCD_RGBC_ODD_GBR			(0x3 << 4)
#घोषणा JZ_LCD_RGBC_ODD_BRG			(0x4 << 4)
#घोषणा JZ_LCD_RGBC_ODD_BGR			(0x5 << 4)
#घोषणा JZ_LCD_RGBC_EVEN_RGB			(0x0 << 0)
#घोषणा JZ_LCD_RGBC_EVEN_RBG			(0x1 << 0)
#घोषणा JZ_LCD_RGBC_EVEN_GRB			(0x2 << 0)
#घोषणा JZ_LCD_RGBC_EVEN_GBR			(0x3 << 0)
#घोषणा JZ_LCD_RGBC_EVEN_BRG			(0x4 << 0)
#घोषणा JZ_LCD_RGBC_EVEN_BGR			(0x5 << 0)

#घोषणा JZ_LCD_OSDC_OSDEN			BIT(0)
#घोषणा JZ_LCD_OSDC_F0EN			BIT(3)
#घोषणा JZ_LCD_OSDC_F1EN			BIT(4)

#घोषणा JZ_LCD_OSDCTRL_IPU			BIT(15)
#घोषणा JZ_LCD_OSDCTRL_RGB555			BIT(4)
#घोषणा JZ_LCD_OSDCTRL_CHANGE			BIT(3)
#घोषणा JZ_LCD_OSDCTRL_BPP_15_16		0x4
#घोषणा JZ_LCD_OSDCTRL_BPP_18_24		0x5
#घोषणा JZ_LCD_OSDCTRL_BPP_24_COMP		0x6
#घोषणा JZ_LCD_OSDCTRL_BPP_30			0x7
#घोषणा JZ_LCD_OSDCTRL_BPP_MASK			(JZ_LCD_OSDCTRL_RGB555 | 0x7)

#घोषणा JZ_LCD_OSDS_READY			BIT(0)

#घोषणा JZ_LCD_IPUR_IPUREN			BIT(31)
#घोषणा JZ_LCD_IPUR_IPUR_LSB			0

#घोषणा JZ_LCD_XYP01_XPOS_LSB			0
#घोषणा JZ_LCD_XYP01_YPOS_LSB			16

#घोषणा JZ_LCD_SIZE01_WIDTH_LSB			0
#घोषणा JZ_LCD_SIZE01_HEIGHT_LSB		16

काष्ठा device;
काष्ठा drm_plane;
काष्ठा drm_plane_state;
काष्ठा platक्रमm_driver;

व्योम ingenic_drm_plane_config(काष्ठा device *dev,
			      काष्ठा drm_plane *plane, u32 fourcc);
व्योम ingenic_drm_plane_disable(काष्ठा device *dev, काष्ठा drm_plane *plane);

बाह्य काष्ठा platक्रमm_driver *ingenic_ipu_driver_ptr;

#पूर्ण_अगर /* DRIVERS_GPU_DRM_INGENIC_INGENIC_DRM_H */
