<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register definitions क्रम the Aपंचांगel Image Sensor Interface.
 *
 * Copyright (C) 2011 Aपंचांगel Corporation
 * Josh Wu, <josh.wu@aपंचांगel.com>
 *
 * Based on previous work by Lars Haring, <lars.haring@aपंचांगel.com>
 * and Sedji Gaouaou
 */
#अगर_अघोषित __ATMEL_ISI_H__
#घोषणा __ATMEL_ISI_H__

#समावेश <linux/types.h>

/* ISI_V2 रेजिस्टर offsets */
#घोषणा ISI_CFG1				0x0000
#घोषणा ISI_CFG2				0x0004
#घोषणा ISI_PSIZE				0x0008
#घोषणा ISI_PDECF				0x000c
#घोषणा ISI_Y2R_SET0				0x0010
#घोषणा ISI_Y2R_SET1				0x0014
#घोषणा ISI_R2Y_SET0				0x0018
#घोषणा ISI_R2Y_SET1				0x001C
#घोषणा ISI_R2Y_SET2				0x0020
#घोषणा ISI_CTRL				0x0024
#घोषणा ISI_STATUS				0x0028
#घोषणा ISI_INTEN				0x002C
#घोषणा ISI_INTDIS				0x0030
#घोषणा ISI_INTMASK				0x0034
#घोषणा ISI_DMA_CHER				0x0038
#घोषणा ISI_DMA_CHDR				0x003C
#घोषणा ISI_DMA_CHSR				0x0040
#घोषणा ISI_DMA_P_ADDR				0x0044
#घोषणा ISI_DMA_P_CTRL				0x0048
#घोषणा ISI_DMA_P_DSCR				0x004C
#घोषणा ISI_DMA_C_ADDR				0x0050
#घोषणा ISI_DMA_C_CTRL				0x0054
#घोषणा ISI_DMA_C_DSCR				0x0058

/* Bitfields in CFG1 */
#घोषणा ISI_CFG1_HSYNC_POL_ACTIVE_LOW		(1 << 2)
#घोषणा ISI_CFG1_VSYNC_POL_ACTIVE_LOW		(1 << 3)
#घोषणा ISI_CFG1_PIXCLK_POL_ACTIVE_FALLING	(1 << 4)
#घोषणा ISI_CFG1_EMB_SYNC			(1 << 6)
#घोषणा ISI_CFG1_CRC_SYNC			(1 << 7)
/* Constants क्रम FRATE(ISI_V2) */
#घोषणा		ISI_CFG1_FRATE_CAPTURE_ALL	(0 << 8)
#घोषणा		ISI_CFG1_FRATE_DIV_2		(1 << 8)
#घोषणा		ISI_CFG1_FRATE_DIV_3		(2 << 8)
#घोषणा		ISI_CFG1_FRATE_DIV_4		(3 << 8)
#घोषणा		ISI_CFG1_FRATE_DIV_5		(4 << 8)
#घोषणा		ISI_CFG1_FRATE_DIV_6		(5 << 8)
#घोषणा		ISI_CFG1_FRATE_DIV_7		(6 << 8)
#घोषणा		ISI_CFG1_FRATE_DIV_8		(7 << 8)
#घोषणा		ISI_CFG1_FRATE_DIV_MASK		(7 << 8)
#घोषणा ISI_CFG1_DISCR				(1 << 11)
#घोषणा ISI_CFG1_FULL_MODE			(1 << 12)
/* Definition क्रम THMASK(ISI_V2) */
#घोषणा		ISI_CFG1_THMASK_BEATS_4		(0 << 13)
#घोषणा		ISI_CFG1_THMASK_BEATS_8		(1 << 13)
#घोषणा		ISI_CFG1_THMASK_BEATS_16	(2 << 13)

/* Bitfields in CFG2 */
#घोषणा ISI_CFG2_GS_MODE_2_PIXEL		(0 << 11)
#घोषणा ISI_CFG2_GS_MODE_1_PIXEL		(1 << 11)
#घोषणा ISI_CFG2_GRAYSCALE			(1 << 13)
#घोषणा ISI_CFG2_COL_SPACE_YCbCr		(0 << 15)
#घोषणा ISI_CFG2_COL_SPACE_RGB			(1 << 15)
/* Constants क्रम YCC_SWAP(ISI_V2) */
#घोषणा		ISI_CFG2_YCC_SWAP_DEFAULT	(0 << 28)
#घोषणा		ISI_CFG2_YCC_SWAP_MODE_1	(1 << 28)
#घोषणा		ISI_CFG2_YCC_SWAP_MODE_2	(2 << 28)
#घोषणा		ISI_CFG2_YCC_SWAP_MODE_3	(3 << 28)
#घोषणा		ISI_CFG2_YCC_SWAP_MODE_MASK	(3 << 28)
#घोषणा ISI_CFG2_IM_VSIZE_OFFSET		0
#घोषणा ISI_CFG2_IM_HSIZE_OFFSET		16
#घोषणा ISI_CFG2_IM_VSIZE_MASK		(0x7FF << ISI_CFG2_IM_VSIZE_OFFSET)
#घोषणा ISI_CFG2_IM_HSIZE_MASK		(0x7FF << ISI_CFG2_IM_HSIZE_OFFSET)

/* Bitfields in PSIZE */
#घोषणा ISI_PSIZE_PREV_VSIZE_OFFSET	0
#घोषणा ISI_PSIZE_PREV_HSIZE_OFFSET	16
#घोषणा ISI_PSIZE_PREV_VSIZE_MASK	(0x3FF << ISI_PSIZE_PREV_VSIZE_OFFSET)
#घोषणा ISI_PSIZE_PREV_HSIZE_MASK	(0x3FF << ISI_PSIZE_PREV_HSIZE_OFFSET)

/* Bitfields in PDECF */
#घोषणा ISI_PDECF_DEC_FACTOR_MASK	(0xFF << 0)
#घोषणा	ISI_PDECF_NO_SAMPLING		(16)

/* Bitfields in CTRL */
/* Also using in SR(ISI_V2) */
#घोषणा ISI_CTRL_EN				(1 << 0)
#घोषणा ISI_CTRL_CDC				(1 << 8)
/* Also using in SR/IER/IDR/IMR(ISI_V2) */
#घोषणा ISI_CTRL_DIS				(1 << 1)
#घोषणा ISI_CTRL_SRST				(1 << 2)

/* Bitfields in SR */
#घोषणा ISI_SR_SIP				(1 << 19)
/* Also using in SR/IER/IDR/IMR */
#घोषणा ISI_SR_VSYNC				(1 << 10)
#घोषणा ISI_SR_PXFR_DONE			(1 << 16)
#घोषणा ISI_SR_CXFR_DONE			(1 << 17)
#घोषणा ISI_SR_P_OVR				(1 << 24)
#घोषणा ISI_SR_C_OVR				(1 << 25)
#घोषणा ISI_SR_CRC_ERR				(1 << 26)
#घोषणा ISI_SR_FR_OVR				(1 << 27)

/* Bitfields in DMA_C_CTRL & in DMA_P_CTRL */
#घोषणा ISI_DMA_CTRL_FETCH			(1 << 0)
#घोषणा ISI_DMA_CTRL_WB				(1 << 1)
#घोषणा ISI_DMA_CTRL_IEN			(1 << 2)
#घोषणा ISI_DMA_CTRL_DONE			(1 << 3)

/* Bitfields in DMA_CHSR/CHER/CHDR */
#घोषणा ISI_DMA_CHSR_P_CH			(1 << 0)
#घोषणा ISI_DMA_CHSR_C_CH			(1 << 1)

/* Definition क्रम isi_platक्रमm_data */
#घोषणा ISI_DATAWIDTH_8				0x01
#घोषणा ISI_DATAWIDTH_10			0x02

काष्ठा v4l2_async_subdev;

काष्ठा isi_platक्रमm_data अणु
	u8 has_emb_sync;
	u8 hsync_act_low;
	u8 vsync_act_low;
	u8 pclk_act_falling;
	u8 full_mode;
	u32 data_width_flags;
	/* Using क्रम ISI_CFG1 */
	u32 frate;
पूर्ण;

#पूर्ण_अगर /* __ATMEL_ISI_H__ */
