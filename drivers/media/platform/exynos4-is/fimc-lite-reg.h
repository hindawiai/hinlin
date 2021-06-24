<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित FIMC_LITE_REG_H_
#घोषणा FIMC_LITE_REG_H_

#समावेश <linux/bitops.h>

#समावेश "fimc-lite.h"

/* Camera Source size */
#घोषणा FLITE_REG_CISRCSIZE			0x00
#घोषणा FLITE_REG_CISRCSIZE_ORDER422_IN_YCBYCR	(0 << 14)
#घोषणा FLITE_REG_CISRCSIZE_ORDER422_IN_YCRYCB	(1 << 14)
#घोषणा FLITE_REG_CISRCSIZE_ORDER422_IN_CBYCRY	(2 << 14)
#घोषणा FLITE_REG_CISRCSIZE_ORDER422_IN_CRYCBY	(3 << 14)
#घोषणा FLITE_REG_CISRCSIZE_ORDER422_MASK	(0x3 << 14)
#घोषणा FLITE_REG_CISRCSIZE_SIZE_CAM_MASK	(0x3fff << 16 | 0x3fff)

/* Global control */
#घोषणा FLITE_REG_CIGCTRL			0x04
#घोषणा FLITE_REG_CIGCTRL_YUV422_1P		(0x1e << 24)
#घोषणा FLITE_REG_CIGCTRL_RAW8			(0x2a << 24)
#घोषणा FLITE_REG_CIGCTRL_RAW10			(0x2b << 24)
#घोषणा FLITE_REG_CIGCTRL_RAW12			(0x2c << 24)
#घोषणा FLITE_REG_CIGCTRL_RAW14			(0x2d << 24)
/* User defined क्रमmats. x = 0...15 */
#घोषणा FLITE_REG_CIGCTRL_USER(x)		((0x30 + x - 1) << 24)
#घोषणा FLITE_REG_CIGCTRL_FMT_MASK		(0x3f << 24)
#घोषणा FLITE_REG_CIGCTRL_SHADOWMASK_DISABLE	BIT(21)
#घोषणा FLITE_REG_CIGCTRL_ODMA_DISABLE		BIT(20)
#घोषणा FLITE_REG_CIGCTRL_SWRST_REQ		BIT(19)
#घोषणा FLITE_REG_CIGCTRL_SWRST_RDY		BIT(18)
#घोषणा FLITE_REG_CIGCTRL_SWRST			BIT(17)
#घोषणा FLITE_REG_CIGCTRL_TEST_PATTERN_COLORBAR	BIT(15)
#घोषणा FLITE_REG_CIGCTRL_INVPOLPCLK		BIT(14)
#घोषणा FLITE_REG_CIGCTRL_INVPOLVSYNC		BIT(13)
#घोषणा FLITE_REG_CIGCTRL_INVPOLHREF		BIT(12)
/* Interrupts mask bits (1 disables an पूर्णांकerrupt) */
#घोषणा FLITE_REG_CIGCTRL_IRQ_LASTEN		BIT(8)
#घोषणा FLITE_REG_CIGCTRL_IRQ_ENDEN		BIT(7)
#घोषणा FLITE_REG_CIGCTRL_IRQ_STARTEN		BIT(6)
#घोषणा FLITE_REG_CIGCTRL_IRQ_OVFEN		BIT(5)
#घोषणा FLITE_REG_CIGCTRL_IRQ_DISABLE_MASK	(0xf << 5)
#घोषणा FLITE_REG_CIGCTRL_SELCAM_MIPI		BIT(3)

/* Image Capture Enable */
#घोषणा FLITE_REG_CIIMGCPT			0x08
#घोषणा FLITE_REG_CIIMGCPT_IMGCPTEN		BIT(31)
#घोषणा FLITE_REG_CIIMGCPT_CPT_FREN		BIT(25)
#घोषणा FLITE_REG_CIIMGCPT_CPT_MOD_FRCNT	(1 << 18)
#घोषणा FLITE_REG_CIIMGCPT_CPT_MOD_FREN		(0 << 18)

/* Capture Sequence */
#घोषणा FLITE_REG_CICPTSEQ			0x0c

/* Camera Winकरोw Offset */
#घोषणा FLITE_REG_CIWDOFST			0x10
#घोषणा FLITE_REG_CIWDOFST_WINOFSEN		BIT(31)
#घोषणा FLITE_REG_CIWDOFST_CLROVIY		BIT(31)
#घोषणा FLITE_REG_CIWDOFST_CLROVFICB		BIT(15)
#घोषणा FLITE_REG_CIWDOFST_CLROVFICR		BIT(14)
#घोषणा FLITE_REG_CIWDOFST_OFST_MASK		((0x1fff << 16) | 0x1fff)

/* Camera Winकरोw Offset2 */
#घोषणा FLITE_REG_CIWDOFST2			0x14

/* Camera Output DMA Format */
#घोषणा FLITE_REG_CIODMAFMT			0x18
#घोषणा FLITE_REG_CIODMAFMT_RAW_CON		BIT(15)
#घोषणा FLITE_REG_CIODMAFMT_PACK12		BIT(14)
#घोषणा FLITE_REG_CIODMAFMT_YCBYCR		(0 << 4)
#घोषणा FLITE_REG_CIODMAFMT_YCRYCB		(1 << 4)
#घोषणा FLITE_REG_CIODMAFMT_CBYCRY		(2 << 4)
#घोषणा FLITE_REG_CIODMAFMT_CRYCBY		(3 << 4)
#घोषणा FLITE_REG_CIODMAFMT_YCBCR_ORDER_MASK	(0x3 << 4)

/* Camera Output Canvas */
#घोषणा FLITE_REG_CIOCAN			0x20
#घोषणा FLITE_REG_CIOCAN_MASK			((0x3fff << 16) | 0x3fff)

/* Camera Output DMA Offset */
#घोषणा FLITE_REG_CIOOFF			0x24
#घोषणा FLITE_REG_CIOOFF_MASK			((0x3fff << 16) | 0x3fff)

/* Camera Output DMA Start Address */
#घोषणा FLITE_REG_CIOSA				0x30

/* Camera Status */
#घोषणा FLITE_REG_CISTATUS			0x40
#घोषणा FLITE_REG_CISTATUS_MIPI_VVALID		BIT(22)
#घोषणा FLITE_REG_CISTATUS_MIPI_HVALID		BIT(21)
#घोषणा FLITE_REG_CISTATUS_MIPI_DVALID		BIT(20)
#घोषणा FLITE_REG_CISTATUS_ITU_VSYNC		BIT(14)
#घोषणा FLITE_REG_CISTATUS_ITU_HREFF		BIT(13)
#घोषणा FLITE_REG_CISTATUS_OVFIY		BIT(10)
#घोषणा FLITE_REG_CISTATUS_OVFICB		BIT(9)
#घोषणा FLITE_REG_CISTATUS_OVFICR		BIT(8)
#घोषणा FLITE_REG_CISTATUS_IRQ_SRC_OVERFLOW	BIT(7)
#घोषणा FLITE_REG_CISTATUS_IRQ_SRC_LASTCAPEND	BIT(6)
#घोषणा FLITE_REG_CISTATUS_IRQ_SRC_FRMSTART	BIT(5)
#घोषणा FLITE_REG_CISTATUS_IRQ_SRC_FRMEND	BIT(4)
#घोषणा FLITE_REG_CISTATUS_IRQ_CAM		BIT(0)
#घोषणा FLITE_REG_CISTATUS_IRQ_MASK		(0xf << 4)

/* Camera Status2 */
#घोषणा FLITE_REG_CISTATUS2			0x44
#घोषणा FLITE_REG_CISTATUS2_LASTCAPEND		BIT(1)
#घोषणा FLITE_REG_CISTATUS2_FRMEND		BIT(0)

/* Qos Threshold */
#घोषणा FLITE_REG_CITHOLD			0xf0
#घोषणा FLITE_REG_CITHOLD_W_QOS_EN		BIT(30)

/* Camera General Purpose */
#घोषणा FLITE_REG_CIGENERAL			0xfc
/* b0: 1 - camera B, 0 - camera A */
#घोषणा FLITE_REG_CIGENERAL_CAM_B		BIT(0)

#घोषणा FLITE_REG_CIFCNTSEQ			0x100
#घोषणा FLITE_REG_CIOSAN(x)			(0x200 + (4 * (x)))

/* ----------------------------------------------------------------------------
 * Function declarations
 */
व्योम flite_hw_reset(काष्ठा fimc_lite *dev);
व्योम flite_hw_clear_pending_irq(काष्ठा fimc_lite *dev);
u32 flite_hw_get_पूर्णांकerrupt_source(काष्ठा fimc_lite *dev);
व्योम flite_hw_clear_last_capture_end(काष्ठा fimc_lite *dev);
व्योम flite_hw_set_पूर्णांकerrupt_mask(काष्ठा fimc_lite *dev);
व्योम flite_hw_capture_start(काष्ठा fimc_lite *dev);
व्योम flite_hw_capture_stop(काष्ठा fimc_lite *dev);
व्योम flite_hw_set_camera_bus(काष्ठा fimc_lite *dev,
			     काष्ठा fimc_source_info *s_info);
व्योम flite_hw_set_camera_polarity(काष्ठा fimc_lite *dev,
				  काष्ठा fimc_source_info *cam);
व्योम flite_hw_set_winकरोw_offset(काष्ठा fimc_lite *dev, काष्ठा flite_frame *f);
व्योम flite_hw_set_source_क्रमmat(काष्ठा fimc_lite *dev, काष्ठा flite_frame *f);

व्योम flite_hw_set_output_dma(काष्ठा fimc_lite *dev, काष्ठा flite_frame *f,
			     bool enable);
व्योम flite_hw_set_dma_winकरोw(काष्ठा fimc_lite *dev, काष्ठा flite_frame *f);
व्योम flite_hw_set_test_pattern(काष्ठा fimc_lite *dev, bool on);
व्योम flite_hw_dump_regs(काष्ठा fimc_lite *dev, स्थिर अक्षर *label);
व्योम flite_hw_set_dma_buffer(काष्ठा fimc_lite *dev, काष्ठा flite_buffer *buf);
व्योम flite_hw_mask_dma_buffer(काष्ठा fimc_lite *dev, u32 index);

अटल अंतरभूत व्योम flite_hw_set_dma_buf_mask(काष्ठा fimc_lite *dev, u32 mask)
अणु
	ग_लिखोl(mask, dev->regs + FLITE_REG_CIFCNTSEQ);
पूर्ण

#पूर्ण_अगर /* FIMC_LITE_REG_H */
