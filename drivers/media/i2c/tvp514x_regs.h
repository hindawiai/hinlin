<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/media/i2c/tvp514x_regs.h
 *
 * Copyright (C) 2008 Texas Instruments Inc
 * Author: Vaibhav Hiremath <hvaibhav@ti.com>
 *
 * Contributors:
 *     Sivaraj R <sivaraj@ti.com>
 *     Brijesh R Jadav <brijesh.j@ti.com>
 *     Hardik Shah <hardik.shah@ti.com>
 *     Manjunath Hadli <mrh@ti.com>
 *     Karicheri Muralidharan <m-karicheri2@ti.com>
 */

#अगर_अघोषित _TVP514X_REGS_H
#घोषणा _TVP514X_REGS_H

/*
 * TVP5146/47 रेजिस्टरs
 */
#घोषणा REG_INPUT_SEL			(0x00)
#घोषणा REG_AFE_GAIN_CTRL		(0x01)
#घोषणा REG_VIDEO_STD			(0x02)
#घोषणा REG_OPERATION_MODE		(0x03)
#घोषणा REG_AUTOSWITCH_MASK		(0x04)

#घोषणा REG_COLOR_KILLER		(0x05)
#घोषणा REG_LUMA_CONTROL1		(0x06)
#घोषणा REG_LUMA_CONTROL2		(0x07)
#घोषणा REG_LUMA_CONTROL3		(0x08)

#घोषणा REG_BRIGHTNESS			(0x09)
#घोषणा REG_CONTRAST			(0x0A)
#घोषणा REG_SATURATION			(0x0B)
#घोषणा REG_HUE				(0x0C)

#घोषणा REG_CHROMA_CONTROL1		(0x0D)
#घोषणा REG_CHROMA_CONTROL2		(0x0E)

/* 0x0F Reserved */

#घोषणा REG_COMP_PR_SATURATION		(0x10)
#घोषणा REG_COMP_Y_CONTRAST		(0x11)
#घोषणा REG_COMP_PB_SATURATION		(0x12)

/* 0x13 Reserved */

#घोषणा REG_COMP_Y_BRIGHTNESS		(0x14)

/* 0x15 Reserved */

#घोषणा REG_AVID_START_PIXEL_LSB	(0x16)
#घोषणा REG_AVID_START_PIXEL_MSB	(0x17)
#घोषणा REG_AVID_STOP_PIXEL_LSB		(0x18)
#घोषणा REG_AVID_STOP_PIXEL_MSB		(0x19)

#घोषणा REG_HSYNC_START_PIXEL_LSB	(0x1A)
#घोषणा REG_HSYNC_START_PIXEL_MSB	(0x1B)
#घोषणा REG_HSYNC_STOP_PIXEL_LSB	(0x1C)
#घोषणा REG_HSYNC_STOP_PIXEL_MSB	(0x1D)

#घोषणा REG_VSYNC_START_LINE_LSB	(0x1E)
#घोषणा REG_VSYNC_START_LINE_MSB	(0x1F)
#घोषणा REG_VSYNC_STOP_LINE_LSB		(0x20)
#घोषणा REG_VSYNC_STOP_LINE_MSB		(0x21)

#घोषणा REG_VBLK_START_LINE_LSB		(0x22)
#घोषणा REG_VBLK_START_LINE_MSB		(0x23)
#घोषणा REG_VBLK_STOP_LINE_LSB		(0x24)
#घोषणा REG_VBLK_STOP_LINE_MSB		(0x25)

/* 0x26 - 0x27 Reserved */

#घोषणा REG_FAST_SWTICH_CONTROL		(0x28)

/* 0x29 Reserved */

#घोषणा REG_FAST_SWTICH_SCART_DELAY	(0x2A)

/* 0x2B Reserved */

#घोषणा REG_SCART_DELAY			(0x2C)
#घोषणा REG_CTI_DELAY			(0x2D)
#घोषणा REG_CTI_CONTROL			(0x2E)

/* 0x2F - 0x31 Reserved */

#घोषणा REG_SYNC_CONTROL		(0x32)
#घोषणा REG_OUTPUT_FORMATTER1		(0x33)
#घोषणा REG_OUTPUT_FORMATTER2		(0x34)
#घोषणा REG_OUTPUT_FORMATTER3		(0x35)
#घोषणा REG_OUTPUT_FORMATTER4		(0x36)
#घोषणा REG_OUTPUT_FORMATTER5		(0x37)
#घोषणा REG_OUTPUT_FORMATTER6		(0x38)
#घोषणा REG_CLEAR_LOST_LOCK		(0x39)

#घोषणा REG_STATUS1			(0x3A)
#घोषणा REG_STATUS2			(0x3B)

#घोषणा REG_AGC_GAIN_STATUS_LSB		(0x3C)
#घोषणा REG_AGC_GAIN_STATUS_MSB		(0x3D)

/* 0x3E Reserved */

#घोषणा REG_VIDEO_STD_STATUS		(0x3F)
#घोषणा REG_GPIO_INPUT1			(0x40)
#घोषणा REG_GPIO_INPUT2			(0x41)

/* 0x42 - 0x45 Reserved */

#घोषणा REG_AFE_COARSE_GAIN_CH1		(0x46)
#घोषणा REG_AFE_COARSE_GAIN_CH2		(0x47)
#घोषणा REG_AFE_COARSE_GAIN_CH3		(0x48)
#घोषणा REG_AFE_COARSE_GAIN_CH4		(0x49)

#घोषणा REG_AFE_FINE_GAIN_PB_B_LSB	(0x4A)
#घोषणा REG_AFE_FINE_GAIN_PB_B_MSB	(0x4B)
#घोषणा REG_AFE_FINE_GAIN_Y_G_CHROMA_LSB	(0x4C)
#घोषणा REG_AFE_FINE_GAIN_Y_G_CHROMA_MSB	(0x4D)
#घोषणा REG_AFE_FINE_GAIN_PR_R_LSB	(0x4E)
#घोषणा REG_AFE_FINE_GAIN_PR_R_MSB	(0x4F)
#घोषणा REG_AFE_FINE_GAIN_CVBS_LUMA_LSB	(0x50)
#घोषणा REG_AFE_FINE_GAIN_CVBS_LUMA_MSB	(0x51)

/* 0x52 - 0x68 Reserved */

#घोषणा REG_FBIT_VBIT_CONTROL1		(0x69)

/* 0x6A - 0x6B Reserved */

#घोषणा REG_BACKEND_AGC_CONTROL		(0x6C)

/* 0x6D - 0x6E Reserved */

#घोषणा REG_AGC_DECREMENT_SPEED_CONTROL	(0x6F)
#घोषणा REG_ROM_VERSION			(0x70)

/* 0x71 - 0x73 Reserved */

#घोषणा REG_AGC_WHITE_PEAK_PROCESSING	(0x74)
#घोषणा REG_FBIT_VBIT_CONTROL2		(0x75)
#घोषणा REG_VCR_TRICK_MODE_CONTROL	(0x76)
#घोषणा REG_HORIZONTAL_SHAKE_INCREMENT	(0x77)
#घोषणा REG_AGC_INCREMENT_SPEED		(0x78)
#घोषणा REG_AGC_INCREMENT_DELAY		(0x79)

/* 0x7A - 0x7F Reserved */

#घोषणा REG_CHIP_ID_MSB			(0x80)
#घोषणा REG_CHIP_ID_LSB			(0x81)

/* 0x82 Reserved */

#घोषणा REG_CPLL_SPEED_CONTROL		(0x83)

/* 0x84 - 0x96 Reserved */

#घोषणा REG_STATUS_REQUEST		(0x97)

/* 0x98 - 0x99 Reserved */

#घोषणा REG_VERTICAL_LINE_COUNT_LSB	(0x9A)
#घोषणा REG_VERTICAL_LINE_COUNT_MSB	(0x9B)

/* 0x9C - 0x9D Reserved */

#घोषणा REG_AGC_DECREMENT_DELAY		(0x9E)

/* 0x9F - 0xB0 Reserved */

#घोषणा REG_VDP_TTX_FILTER_1_MASK1	(0xB1)
#घोषणा REG_VDP_TTX_FILTER_1_MASK2	(0xB2)
#घोषणा REG_VDP_TTX_FILTER_1_MASK3	(0xB3)
#घोषणा REG_VDP_TTX_FILTER_1_MASK4	(0xB4)
#घोषणा REG_VDP_TTX_FILTER_1_MASK5	(0xB5)
#घोषणा REG_VDP_TTX_FILTER_2_MASK1	(0xB6)
#घोषणा REG_VDP_TTX_FILTER_2_MASK2	(0xB7)
#घोषणा REG_VDP_TTX_FILTER_2_MASK3	(0xB8)
#घोषणा REG_VDP_TTX_FILTER_2_MASK4	(0xB9)
#घोषणा REG_VDP_TTX_FILTER_2_MASK5	(0xBA)
#घोषणा REG_VDP_TTX_FILTER_CONTROL	(0xBB)
#घोषणा REG_VDP_FIFO_WORD_COUNT		(0xBC)
#घोषणा REG_VDP_FIFO_INTERRUPT_THRLD	(0xBD)

/* 0xBE Reserved */

#घोषणा REG_VDP_FIFO_RESET		(0xBF)
#घोषणा REG_VDP_FIFO_OUTPUT_CONTROL	(0xC0)
#घोषणा REG_VDP_LINE_NUMBER_INTERRUPT	(0xC1)
#घोषणा REG_VDP_PIXEL_ALIGNMENT_LSB	(0xC2)
#घोषणा REG_VDP_PIXEL_ALIGNMENT_MSB	(0xC3)

/* 0xC4 - 0xD5 Reserved */

#घोषणा REG_VDP_LINE_START		(0xD6)
#घोषणा REG_VDP_LINE_STOP		(0xD7)
#घोषणा REG_VDP_GLOBAL_LINE_MODE	(0xD8)
#घोषणा REG_VDP_FULL_FIELD_ENABLE	(0xD9)
#घोषणा REG_VDP_FULL_FIELD_MODE		(0xDA)

/* 0xDB - 0xDF Reserved */

#घोषणा REG_VBUS_DATA_ACCESS_NO_VBUS_ADDR_INCR	(0xE0)
#घोषणा REG_VBUS_DATA_ACCESS_VBUS_ADDR_INCR	(0xE1)
#घोषणा REG_FIFO_READ_DATA			(0xE2)

/* 0xE3 - 0xE7 Reserved */

#घोषणा REG_VBUS_ADDRESS_ACCESS1	(0xE8)
#घोषणा REG_VBUS_ADDRESS_ACCESS2	(0xE9)
#घोषणा REG_VBUS_ADDRESS_ACCESS3	(0xEA)

/* 0xEB - 0xEF Reserved */

#घोषणा REG_INTERRUPT_RAW_STATUS0	(0xF0)
#घोषणा REG_INTERRUPT_RAW_STATUS1	(0xF1)
#घोषणा REG_INTERRUPT_STATUS0		(0xF2)
#घोषणा REG_INTERRUPT_STATUS1		(0xF3)
#घोषणा REG_INTERRUPT_MASK0		(0xF4)
#घोषणा REG_INTERRUPT_MASK1		(0xF5)
#घोषणा REG_INTERRUPT_CLEAR0		(0xF6)
#घोषणा REG_INTERRUPT_CLEAR1		(0xF7)

/* 0xF8 - 0xFF Reserved */

/*
 * Mask and bit definitions of TVP5146/47 रेजिस्टरs
 */
/* The ID values we are looking क्रम */
#घोषणा TVP514X_CHIP_ID_MSB		(0x51)
#घोषणा TVP5146_CHIP_ID_LSB		(0x46)
#घोषणा TVP5147_CHIP_ID_LSB		(0x47)

#घोषणा VIDEO_STD_MASK			(0x07)
#घोषणा VIDEO_STD_AUTO_SWITCH_BIT	(0x00)
#घोषणा VIDEO_STD_NTSC_MJ_BIT		(0x01)
#घोषणा VIDEO_STD_PAL_BDGHIN_BIT	(0x02)
#घोषणा VIDEO_STD_PAL_M_BIT		(0x03)
#घोषणा VIDEO_STD_PAL_COMBINATION_N_BIT	(0x04)
#घोषणा VIDEO_STD_NTSC_4_43_BIT		(0x05)
#घोषणा VIDEO_STD_SECAM_BIT		(0x06)
#घोषणा VIDEO_STD_PAL_60_BIT		(0x07)

/*
 * Status bit
 */
#घोषणा STATUS_TV_VCR_BIT		(1<<0)
#घोषणा STATUS_HORZ_SYNC_LOCK_BIT	(1<<1)
#घोषणा STATUS_VIRT_SYNC_LOCK_BIT	(1<<2)
#घोषणा STATUS_CLR_SUBCAR_LOCK_BIT	(1<<3)
#घोषणा STATUS_LOST_LOCK_DETECT_BIT	(1<<4)
#घोषणा STATUS_FEILD_RATE_BIT		(1<<5)
#घोषणा STATUS_LINE_ALTERNATING_BIT	(1<<6)
#घोषणा STATUS_PEAK_WHITE_DETECT_BIT	(1<<7)

/* Tokens क्रम रेजिस्टर ग_लिखो */
#घोषणा TOK_WRITE                       (0)     /* token क्रम ग_लिखो operation */
#घोषणा TOK_TERM                        (1)     /* terminating token */
#घोषणा TOK_DELAY                       (2)     /* delay token क्रम reg list */
#घोषणा TOK_SKIP                        (3)     /* token to skip a रेजिस्टर */
/**
 * काष्ठा tvp514x_reg - Structure क्रम TVP5146/47 रेजिस्टर initialization values
 * @token: Token: TOK_WRITE, TOK_TERM etc..
 * @reg: Register offset
 * @val: Register Value क्रम TOK_WRITE or delay in ms क्रम TOK_DELAY
 */
काष्ठा tvp514x_reg अणु
	u8 token;
	u8 reg;
	u32 val;
पूर्ण;

#पूर्ण_अगर				/* अगरndef _TVP514X_REGS_H */
