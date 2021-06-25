<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung camera host पूर्णांकerface (FIMC) रेजिस्टरs definition
 *
 * Copyright (C) 2010 - 2012 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित FIMC_REG_H_
#घोषणा FIMC_REG_H_

#समावेश <linux/bitops.h>

#समावेश "fimc-core.h"

/* Input source क्रमmat */
#घोषणा FIMC_REG_CISRCFMT			0x00
#घोषणा FIMC_REG_CISRCFMT_ITU601_8BIT		BIT(31)
#घोषणा FIMC_REG_CISRCFMT_ITU601_16BIT		BIT(29)
#घोषणा FIMC_REG_CISRCFMT_ORDER422_YCBYCR	(0 << 14)
#घोषणा FIMC_REG_CISRCFMT_ORDER422_YCRYCB	(1 << 14)
#घोषणा FIMC_REG_CISRCFMT_ORDER422_CBYCRY	(2 << 14)
#घोषणा FIMC_REG_CISRCFMT_ORDER422_CRYCBY	(3 << 14)

/* Winकरोw offset */
#घोषणा FIMC_REG_CIWDOFST			0x04
#घोषणा FIMC_REG_CIWDOFST_OFF_EN		BIT(31)
#घोषणा FIMC_REG_CIWDOFST_CLROVFIY		BIT(30)
#घोषणा FIMC_REG_CIWDOFST_CLROVRLB		BIT(29)
#घोषणा FIMC_REG_CIWDOFST_HOROFF_MASK		(0x7ff << 16)
#घोषणा FIMC_REG_CIWDOFST_CLROVFICB		BIT(15)
#घोषणा FIMC_REG_CIWDOFST_CLROVFICR		BIT(14)
#घोषणा FIMC_REG_CIWDOFST_VEROFF_MASK		(0xfff << 0)

/* Global control */
#घोषणा FIMC_REG_CIGCTRL			0x08
#घोषणा FIMC_REG_CIGCTRL_SWRST			BIT(31)
#घोषणा FIMC_REG_CIGCTRL_CAMRST_A		BIT(30)
#घोषणा FIMC_REG_CIGCTRL_SELCAM_ITU_A		BIT(29)
#घोषणा FIMC_REG_CIGCTRL_TESTPAT_NORMAL		(0 << 27)
#घोषणा FIMC_REG_CIGCTRL_TESTPAT_COLOR_BAR	(1 << 27)
#घोषणा FIMC_REG_CIGCTRL_TESTPAT_HOR_INC	(2 << 27)
#घोषणा FIMC_REG_CIGCTRL_TESTPAT_VER_INC	(3 << 27)
#घोषणा FIMC_REG_CIGCTRL_TESTPAT_MASK		(3 << 27)
#घोषणा FIMC_REG_CIGCTRL_TESTPAT_SHIFT		27
#घोषणा FIMC_REG_CIGCTRL_INVPOLPCLK		BIT(26)
#घोषणा FIMC_REG_CIGCTRL_INVPOLVSYNC		BIT(25)
#घोषणा FIMC_REG_CIGCTRL_INVPOLHREF		BIT(24)
#घोषणा FIMC_REG_CIGCTRL_IRQ_OVFEN		BIT(22)
#घोषणा FIMC_REG_CIGCTRL_HREF_MASK		BIT(21)
#घोषणा FIMC_REG_CIGCTRL_IRQ_LEVEL		BIT(20)
#घोषणा FIMC_REG_CIGCTRL_IRQ_CLR		BIT(19)
#घोषणा FIMC_REG_CIGCTRL_IRQ_ENABLE		BIT(16)
#घोषणा FIMC_REG_CIGCTRL_SHDW_DISABLE		BIT(12)
/* 0 - selects Writeback A (LCD), 1 - selects Writeback B (LCD/ISP) */
#घोषणा FIMC_REG_CIGCTRL_SELWB_A		BIT(10)
#घोषणा FIMC_REG_CIGCTRL_CAM_JPEG		BIT(8)
#घोषणा FIMC_REG_CIGCTRL_SELCAM_MIPI_A		BIT(7)
#घोषणा FIMC_REG_CIGCTRL_CAMIF_SELWB		BIT(6)
/* 0 - ITU601; 1 - ITU709 */
#घोषणा FIMC_REG_CIGCTRL_CSC_ITU601_709		BIT(5)
#घोषणा FIMC_REG_CIGCTRL_INVPOLHSYNC		BIT(4)
#घोषणा FIMC_REG_CIGCTRL_SELCAM_MIPI		BIT(3)
#घोषणा FIMC_REG_CIGCTRL_INVPOLFIELD		BIT(1)
#घोषणा FIMC_REG_CIGCTRL_INTERLACE		BIT(0)

/* Winकरोw offset 2 */
#घोषणा FIMC_REG_CIWDOFST2			0x14
#घोषणा FIMC_REG_CIWDOFST2_HOROFF_MASK		(0xfff << 16)
#घोषणा FIMC_REG_CIWDOFST2_VEROFF_MASK		(0xfff << 0)

/* Output DMA Y/Cb/Cr plane start addresses */
#घोषणा FIMC_REG_CIOYSA(n)			(0x18 + (n) * 4)
#घोषणा FIMC_REG_CIOCBSA(n)			(0x28 + (n) * 4)
#घोषणा FIMC_REG_CIOCRSA(n)			(0x38 + (n) * 4)

/* Target image क्रमmat */
#घोषणा FIMC_REG_CITRGFMT			0x48
#घोषणा FIMC_REG_CITRGFMT_INROT90		BIT(31)
#घोषणा FIMC_REG_CITRGFMT_YCBCR420		(0 << 29)
#घोषणा FIMC_REG_CITRGFMT_YCBCR422		(1 << 29)
#घोषणा FIMC_REG_CITRGFMT_YCBCR422_1P		(2 << 29)
#घोषणा FIMC_REG_CITRGFMT_RGB			(3 << 29)
#घोषणा FIMC_REG_CITRGFMT_FMT_MASK		(3 << 29)
#घोषणा FIMC_REG_CITRGFMT_HSIZE_MASK		(0xfff << 16)
#घोषणा FIMC_REG_CITRGFMT_FLIP_SHIFT		14
#घोषणा FIMC_REG_CITRGFMT_FLIP_NORMAL		(0 << 14)
#घोषणा FIMC_REG_CITRGFMT_FLIP_X_MIRROR		(1 << 14)
#घोषणा FIMC_REG_CITRGFMT_FLIP_Y_MIRROR		(2 << 14)
#घोषणा FIMC_REG_CITRGFMT_FLIP_180		(3 << 14)
#घोषणा FIMC_REG_CITRGFMT_FLIP_MASK		(3 << 14)
#घोषणा FIMC_REG_CITRGFMT_OUTROT90		BIT(13)
#घोषणा FIMC_REG_CITRGFMT_VSIZE_MASK		(0xfff << 0)

/* Output DMA control */
#घोषणा FIMC_REG_CIOCTRL			0x4c
#घोषणा FIMC_REG_CIOCTRL_ORDER422_MASK		(3 << 0)
#घोषणा FIMC_REG_CIOCTRL_ORDER422_YCBYCR	(0 << 0)
#घोषणा FIMC_REG_CIOCTRL_ORDER422_YCRYCB	(1 << 0)
#घोषणा FIMC_REG_CIOCTRL_ORDER422_CBYCRY	(2 << 0)
#घोषणा FIMC_REG_CIOCTRL_ORDER422_CRYCBY	(3 << 0)
#घोषणा FIMC_REG_CIOCTRL_LASTIRQ_ENABLE		BIT(2)
#घोषणा FIMC_REG_CIOCTRL_YCBCR_3PLANE		(0 << 3)
#घोषणा FIMC_REG_CIOCTRL_YCBCR_2PLANE		(1 << 3)
#घोषणा FIMC_REG_CIOCTRL_YCBCR_PLANE_MASK	(1 << 3)
#घोषणा FIMC_REG_CIOCTRL_ALPHA_OUT_MASK		(0xff << 4)
#घोषणा FIMC_REG_CIOCTRL_RGB16FMT_MASK		(3 << 16)
#घोषणा FIMC_REG_CIOCTRL_RGB565			(0 << 16)
#घोषणा FIMC_REG_CIOCTRL_ARGB1555		(1 << 16)
#घोषणा FIMC_REG_CIOCTRL_ARGB4444		(2 << 16)
#घोषणा FIMC_REG_CIOCTRL_ORDER2P_SHIFT		24
#घोषणा FIMC_REG_CIOCTRL_ORDER2P_MASK		(3 << 24)
#घोषणा FIMC_REG_CIOCTRL_ORDER422_2P_LSB_CRCB	(0 << 24)

/* Pre-scaler control 1 */
#घोषणा FIMC_REG_CISCPRERATIO			0x50

#घोषणा FIMC_REG_CISCPREDST			0x54

/* Main scaler control */
#घोषणा FIMC_REG_CISCCTRL			0x58
#घोषणा FIMC_REG_CISCCTRL_SCALERBYPASS		BIT(31)
#घोषणा FIMC_REG_CISCCTRL_SCALEUP_H		BIT(30)
#घोषणा FIMC_REG_CISCCTRL_SCALEUP_V		BIT(29)
#घोषणा FIMC_REG_CISCCTRL_CSCR2Y_WIDE		BIT(28)
#घोषणा FIMC_REG_CISCCTRL_CSCY2R_WIDE		BIT(27)
#घोषणा FIMC_REG_CISCCTRL_LCDPATHEN_FIFO	BIT(26)
#घोषणा FIMC_REG_CISCCTRL_INTERLACE		BIT(25)
#घोषणा FIMC_REG_CISCCTRL_SCALERSTART		BIT(15)
#घोषणा FIMC_REG_CISCCTRL_INRGB_FMT_RGB565	(0 << 13)
#घोषणा FIMC_REG_CISCCTRL_INRGB_FMT_RGB666	(1 << 13)
#घोषणा FIMC_REG_CISCCTRL_INRGB_FMT_RGB888	(2 << 13)
#घोषणा FIMC_REG_CISCCTRL_INRGB_FMT_MASK	(3 << 13)
#घोषणा FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB565	(0 << 11)
#घोषणा FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB666	(1 << 11)
#घोषणा FIMC_REG_CISCCTRL_OUTRGB_FMT_RGB888	(2 << 11)
#घोषणा FIMC_REG_CISCCTRL_OUTRGB_FMT_MASK	(3 << 11)
#घोषणा FIMC_REG_CISCCTRL_RGB_EXT		BIT(10)
#घोषणा FIMC_REG_CISCCTRL_ONE2ONE		BIT(9)
#घोषणा FIMC_REG_CISCCTRL_MHRATIO(x)		((x) << 16)
#घोषणा FIMC_REG_CISCCTRL_MVRATIO(x)		((x) << 0)
#घोषणा FIMC_REG_CISCCTRL_MHRATIO_MASK		(0x1ff << 16)
#घोषणा FIMC_REG_CISCCTRL_MVRATIO_MASK		(0x1ff << 0)
#घोषणा FIMC_REG_CISCCTRL_MHRATIO_EXT(x)	(((x) >> 6) << 16)
#घोषणा FIMC_REG_CISCCTRL_MVRATIO_EXT(x)	(((x) >> 6) << 0)

/* Target area */
#घोषणा FIMC_REG_CITAREA			0x5c
#घोषणा FIMC_REG_CITAREA_MASK			0x0fffffff

/* General status */
#घोषणा FIMC_REG_CISTATUS			0x64
#घोषणा FIMC_REG_CISTATUS_OVFIY			BIT(31)
#घोषणा FIMC_REG_CISTATUS_OVFICB		BIT(30)
#घोषणा FIMC_REG_CISTATUS_OVFICR		BIT(29)
#घोषणा FIMC_REG_CISTATUS_VSYNC			BIT(28)
#घोषणा FIMC_REG_CISTATUS_FRAMECNT_MASK		(3 << 26)
#घोषणा FIMC_REG_CISTATUS_FRAMECNT_SHIFT	26
#घोषणा FIMC_REG_CISTATUS_WINOFF_EN		BIT(25)
#घोषणा FIMC_REG_CISTATUS_IMGCPT_EN		BIT(22)
#घोषणा FIMC_REG_CISTATUS_IMGCPT_SCEN		BIT(21)
#घोषणा FIMC_REG_CISTATUS_VSYNC_A		BIT(20)
#घोषणा FIMC_REG_CISTATUS_VSYNC_B		BIT(19)
#घोषणा FIMC_REG_CISTATUS_OVRLB			BIT(18)
#घोषणा FIMC_REG_CISTATUS_FRAME_END		BIT(17)
#घोषणा FIMC_REG_CISTATUS_LASTCAPT_END		BIT(16)
#घोषणा FIMC_REG_CISTATUS_VVALID_A		BIT(15)
#घोषणा FIMC_REG_CISTATUS_VVALID_B		BIT(14)

/* Indexes to the last and the currently processed buffer. */
#घोषणा FIMC_REG_CISTATUS2			0x68

/* Image capture control */
#घोषणा FIMC_REG_CIIMGCPT			0xc0
#घोषणा FIMC_REG_CIIMGCPT_IMGCPTEN		BIT(31)
#घोषणा FIMC_REG_CIIMGCPT_IMGCPTEN_SC		BIT(30)
#घोषणा FIMC_REG_CIIMGCPT_CPT_FREN_ENABLE	BIT(25)
#घोषणा FIMC_REG_CIIMGCPT_CPT_FRMOD_CNT		BIT(18)

/* Frame capture sequence */
#घोषणा FIMC_REG_CICPTSEQ			0xc4

/* Image effect */
#घोषणा FIMC_REG_CIIMGEFF			0xd0
#घोषणा FIMC_REG_CIIMGEFF_IE_ENABLE		BIT(30)
#घोषणा FIMC_REG_CIIMGEFF_IE_SC_BEFORE		(0 << 29)
#घोषणा FIMC_REG_CIIMGEFF_IE_SC_AFTER		(1 << 29)
#घोषणा FIMC_REG_CIIMGEFF_FIN_BYPASS		(0 << 26)
#घोषणा FIMC_REG_CIIMGEFF_FIN_ARBITRARY		(1 << 26)
#घोषणा FIMC_REG_CIIMGEFF_FIN_NEGATIVE		(2 << 26)
#घोषणा FIMC_REG_CIIMGEFF_FIN_ARTFREEZE		(3 << 26)
#घोषणा FIMC_REG_CIIMGEFF_FIN_EMBOSSING		(4 << 26)
#घोषणा FIMC_REG_CIIMGEFF_FIN_SILHOUETTE	(5 << 26)
#घोषणा FIMC_REG_CIIMGEFF_FIN_MASK		(7 << 26)
#घोषणा FIMC_REG_CIIMGEFF_PAT_CBCR_MASK		((0xff << 13) | 0xff)

/* Input DMA Y/Cb/Cr plane start address 0/1 */
#घोषणा FIMC_REG_CIIYSA(n)			(0xd4 + (n) * 0x70)
#घोषणा FIMC_REG_CIICBSA(n)			(0xd8 + (n) * 0x70)
#घोषणा FIMC_REG_CIICRSA(n)			(0xdc + (n) * 0x70)

/* Real input DMA image size */
#घोषणा FIMC_REG_CIREAL_ISIZE			0xf8
#घोषणा FIMC_REG_CIREAL_ISIZE_AUTOLOAD_EN	BIT(31)
#घोषणा FIMC_REG_CIREAL_ISIZE_ADDR_CH_DIS	BIT(30)

/* Input DMA control */
#घोषणा FIMC_REG_MSCTRL				0xfc
#घोषणा FIMC_REG_MSCTRL_IN_BURST_COUNT_MASK	(0xf << 24)
#घोषणा FIMC_REG_MSCTRL_2P_IN_ORDER_MASK	(3 << 16)
#घोषणा FIMC_REG_MSCTRL_2P_IN_ORDER_SHIFT	16
#घोषणा FIMC_REG_MSCTRL_C_INT_IN_3PLANE		(0 << 15)
#घोषणा FIMC_REG_MSCTRL_C_INT_IN_2PLANE		(1 << 15)
#घोषणा FIMC_REG_MSCTRL_C_INT_IN_MASK		(1 << 15)
#घोषणा FIMC_REG_MSCTRL_FLIP_SHIFT		13
#घोषणा FIMC_REG_MSCTRL_FLIP_MASK		(3 << 13)
#घोषणा FIMC_REG_MSCTRL_FLIP_NORMAL		(0 << 13)
#घोषणा FIMC_REG_MSCTRL_FLIP_X_MIRROR		(1 << 13)
#घोषणा FIMC_REG_MSCTRL_FLIP_Y_MIRROR		(2 << 13)
#घोषणा FIMC_REG_MSCTRL_FLIP_180		(3 << 13)
#घोषणा FIMC_REG_MSCTRL_FIFO_CTRL_FULL		BIT(12)
#घोषणा FIMC_REG_MSCTRL_ORDER422_SHIFT		4
#घोषणा FIMC_REG_MSCTRL_ORDER422_CRYCBY		(0 << 4)
#घोषणा FIMC_REG_MSCTRL_ORDER422_YCRYCB		(1 << 4)
#घोषणा FIMC_REG_MSCTRL_ORDER422_CBYCRY		(2 << 4)
#घोषणा FIMC_REG_MSCTRL_ORDER422_YCBYCR		(3 << 4)
#घोषणा FIMC_REG_MSCTRL_ORDER422_MASK		(3 << 4)
#घोषणा FIMC_REG_MSCTRL_INPUT_EXTCAM		(0 << 3)
#घोषणा FIMC_REG_MSCTRL_INPUT_MEMORY		BIT(3)
#घोषणा FIMC_REG_MSCTRL_INPUT_MASK		BIT(3)
#घोषणा FIMC_REG_MSCTRL_INFORMAT_YCBCR420	(0 << 1)
#घोषणा FIMC_REG_MSCTRL_INFORMAT_YCBCR422	(1 << 1)
#घोषणा FIMC_REG_MSCTRL_INFORMAT_YCBCR422_1P	(2 << 1)
#घोषणा FIMC_REG_MSCTRL_INFORMAT_RGB		(3 << 1)
#घोषणा FIMC_REG_MSCTRL_INFORMAT_MASK		(3 << 1)
#घोषणा FIMC_REG_MSCTRL_ENVID			BIT(0)
#घोषणा FIMC_REG_MSCTRL_IN_BURST_COUNT(x)	((x) << 24)

/* Output DMA Y/Cb/Cr offset */
#घोषणा FIMC_REG_CIOYOFF			0x168
#घोषणा FIMC_REG_CIOCBOFF			0x16c
#घोषणा FIMC_REG_CIOCROFF			0x170

/* Input DMA Y/Cb/Cr offset */
#घोषणा FIMC_REG_CIIYOFF			0x174
#घोषणा FIMC_REG_CIICBOFF			0x178
#घोषणा FIMC_REG_CIICROFF			0x17c

/* Input DMA original image size */
#घोषणा FIMC_REG_ORGISIZE			0x180

/* Output DMA original image size */
#घोषणा FIMC_REG_ORGOSIZE			0x184

/* Real output DMA image size (extension रेजिस्टर) */
#घोषणा FIMC_REG_CIEXTEN			0x188
#घोषणा FIMC_REG_CIEXTEN_MHRATIO_EXT(x)		(((x) & 0x3f) << 10)
#घोषणा FIMC_REG_CIEXTEN_MVRATIO_EXT(x)		((x) & 0x3f)
#घोषणा FIMC_REG_CIEXTEN_MHRATIO_EXT_MASK	(0x3f << 10)
#घोषणा FIMC_REG_CIEXTEN_MVRATIO_EXT_MASK	0x3f

#घोषणा FIMC_REG_CIDMAPARAM			0x18c
#घोषणा FIMC_REG_CIDMAPARAM_R_LINEAR		(0 << 29)
#घोषणा FIMC_REG_CIDMAPARAM_R_64X32		(3 << 29)
#घोषणा FIMC_REG_CIDMAPARAM_W_LINEAR		(0 << 13)
#घोषणा FIMC_REG_CIDMAPARAM_W_64X32		(3 << 13)
#घोषणा FIMC_REG_CIDMAPARAM_TILE_MASK		((3 << 29) | (3 << 13))

/* MIPI CSI image क्रमmat */
#घोषणा FIMC_REG_CSIIMGFMT			0x194
#घोषणा FIMC_REG_CSIIMGFMT_YCBCR422_8BIT	0x1e
#घोषणा FIMC_REG_CSIIMGFMT_RAW8			0x2a
#घोषणा FIMC_REG_CSIIMGFMT_RAW10		0x2b
#घोषणा FIMC_REG_CSIIMGFMT_RAW12		0x2c
/* User defined क्रमmats. x = 0...16. */
#घोषणा FIMC_REG_CSIIMGFMT_USER(x)		(0x30 + x - 1)

/* Output frame buffer sequence mask */
#घोषणा FIMC_REG_CIFCNTSEQ			0x1fc

/* SYSREG ISP Writeback रेजिस्टर address offsets */
#घोषणा SYSREG_ISPBLK				0x020c
#घोषणा SYSREG_ISPBLK_FIFORST_CAM_BLK		BIT(7)

#घोषणा SYSREG_CAMBLK				0x0218
#घोषणा SYSREG_CAMBLK_FIFORST_ISP		BIT(15)
#घोषणा SYSREG_CAMBLK_ISPWB_FULL_EN		(7 << 20)

/*
 * Function declarations
 */
व्योम fimc_hw_reset(काष्ठा fimc_dev *fimc);
व्योम fimc_hw_set_rotation(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_set_target_क्रमmat(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_set_out_dma(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_en_lastirq(काष्ठा fimc_dev *fimc, पूर्णांक enable);
व्योम fimc_hw_en_irq(काष्ठा fimc_dev *fimc, पूर्णांक enable);
व्योम fimc_hw_set_prescaler(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_set_मुख्यscaler(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_enable_capture(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_set_effect(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_set_rgb_alpha(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_set_in_dma(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_set_input_path(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_set_output_path(काष्ठा fimc_ctx *ctx);
व्योम fimc_hw_set_input_addr(काष्ठा fimc_dev *fimc, काष्ठा fimc_addr *addr);
व्योम fimc_hw_set_output_addr(काष्ठा fimc_dev *fimc, काष्ठा fimc_addr *addr,
			     पूर्णांक index);
पूर्णांक fimc_hw_set_camera_source(काष्ठा fimc_dev *fimc,
			      काष्ठा fimc_source_info *cam);
व्योम fimc_hw_set_camera_offset(काष्ठा fimc_dev *fimc, काष्ठा fimc_frame *f);
पूर्णांक fimc_hw_set_camera_polarity(काष्ठा fimc_dev *fimc,
				काष्ठा fimc_source_info *cam);
पूर्णांक fimc_hw_set_camera_type(काष्ठा fimc_dev *fimc,
			    काष्ठा fimc_source_info *cam);
व्योम fimc_hw_clear_irq(काष्ठा fimc_dev *dev);
व्योम fimc_hw_enable_scaler(काष्ठा fimc_dev *dev, bool on);
व्योम fimc_hw_activate_input_dma(काष्ठा fimc_dev *dev, bool on);
व्योम fimc_hw_disable_capture(काष्ठा fimc_dev *dev);
s32 fimc_hw_get_frame_index(काष्ठा fimc_dev *dev);
s32 fimc_hw_get_prev_frame_index(काष्ठा fimc_dev *dev);
पूर्णांक fimc_hw_camblk_cfg_ग_लिखोback(काष्ठा fimc_dev *fimc);
व्योम fimc_activate_capture(काष्ठा fimc_ctx *ctx);
व्योम fimc_deactivate_capture(काष्ठा fimc_dev *fimc);

/**
 * fimc_hw_set_dma_seq - configure output DMA buffer sequence
 * @dev: fimc device
 * @mask: biपंचांगask क्रम the DMA output buffer रेजिस्टरs, set to 0 to skip buffer
 * This function masks output DMA ring buffers, it allows to select which of
 * the 32 available output buffer address रेजिस्टरs will be used by the DMA
 * engine.
 */
अटल अंतरभूत व्योम fimc_hw_set_dma_seq(काष्ठा fimc_dev *dev, u32 mask)
अणु
	ग_लिखोl(mask, dev->regs + FIMC_REG_CIFCNTSEQ);
पूर्ण

#पूर्ण_अगर /* FIMC_REG_H_ */
