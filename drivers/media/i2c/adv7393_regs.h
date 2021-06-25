<शैली गुरु>
/*
 * ADV7393 encoder related काष्ठाure and रेजिस्टर definitions
 *
 * Copyright (C) 2010-2012 ADVANSEE - http://www.advansee.com/
 * Benoथऍt Thथऊbaudeau <benoit.thebaudeau@advansee.com>
 *
 * Based on ADV7343 driver,
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित ADV7393_REGS_H
#घोषणा ADV7393_REGS_H

काष्ठा adv7393_std_info अणु
	u32 standard_val3;
	u32 fsc_val;
	v4l2_std_id stdid;
पूर्ण;

/* Register offset macros */
#घोषणा ADV7393_POWER_MODE_REG		(0x00)
#घोषणा ADV7393_MODE_SELECT_REG		(0x01)
#घोषणा ADV7393_MODE_REG0		(0x02)

#घोषणा ADV7393_DAC123_OUTPUT_LEVEL	(0x0B)

#घोषणा ADV7393_SOFT_RESET		(0x17)

#घोषणा ADV7393_HD_MODE_REG1		(0x30)
#घोषणा ADV7393_HD_MODE_REG2		(0x31)
#घोषणा ADV7393_HD_MODE_REG3		(0x32)
#घोषणा ADV7393_HD_MODE_REG4		(0x33)
#घोषणा ADV7393_HD_MODE_REG5		(0x34)
#घोषणा ADV7393_HD_MODE_REG6		(0x35)

#घोषणा ADV7393_HD_MODE_REG7		(0x39)

#घोषणा ADV7393_SD_MODE_REG1		(0x80)
#घोषणा ADV7393_SD_MODE_REG2		(0x82)
#घोषणा ADV7393_SD_MODE_REG3		(0x83)
#घोषणा ADV7393_SD_MODE_REG4		(0x84)
#घोषणा ADV7393_SD_MODE_REG5		(0x86)
#घोषणा ADV7393_SD_MODE_REG6		(0x87)
#घोषणा ADV7393_SD_MODE_REG7		(0x88)
#घोषणा ADV7393_SD_MODE_REG8		(0x89)

#घोषणा ADV7393_SD_TIMING_REG0		(0x8A)

#घोषणा ADV7393_FSC_REG0		(0x8C)
#घोषणा ADV7393_FSC_REG1		(0x8D)
#घोषणा ADV7393_FSC_REG2		(0x8E)
#घोषणा ADV7393_FSC_REG3		(0x8F)

#घोषणा ADV7393_SD_CGMS_WSS0		(0x99)

#घोषणा ADV7393_SD_HUE_ADJUST		(0xA0)
#घोषणा ADV7393_SD_BRIGHTNESS_WSS	(0xA1)

/* Default values क्रम the रेजिस्टरs */
#घोषणा ADV7393_POWER_MODE_REG_DEFAULT		(0x10)
#घोषणा ADV7393_HD_MODE_REG1_DEFAULT		(0x3C)	/* Changed Default
							   720p EAV/SAV code*/
#घोषणा ADV7393_HD_MODE_REG2_DEFAULT		(0x01)	/* Changed Pixel data
							   valid */
#घोषणा ADV7393_HD_MODE_REG3_DEFAULT		(0x00)	/* Color delay 0 clks */
#घोषणा ADV7393_HD_MODE_REG4_DEFAULT		(0xEC)	/* Changed */
#घोषणा ADV7393_HD_MODE_REG5_DEFAULT		(0x08)
#घोषणा ADV7393_HD_MODE_REG6_DEFAULT		(0x00)
#घोषणा ADV7393_HD_MODE_REG7_DEFAULT		(0x00)
#घोषणा ADV7393_SOFT_RESET_DEFAULT		(0x02)
#घोषणा ADV7393_COMPOSITE_POWER_VALUE		(0x10)
#घोषणा ADV7393_COMPONENT_POWER_VALUE		(0x1C)
#घोषणा ADV7393_SVIDEO_POWER_VALUE		(0x0C)
#घोषणा ADV7393_SD_HUE_ADJUST_DEFAULT		(0x80)
#घोषणा ADV7393_SD_BRIGHTNESS_WSS_DEFAULT	(0x00)

#घोषणा ADV7393_SD_CGMS_WSS0_DEFAULT		(0x10)

#घोषणा ADV7393_SD_MODE_REG1_DEFAULT		(0x10)
#घोषणा ADV7393_SD_MODE_REG2_DEFAULT		(0xC9)
#घोषणा ADV7393_SD_MODE_REG3_DEFAULT		(0x00)
#घोषणा ADV7393_SD_MODE_REG4_DEFAULT		(0x00)
#घोषणा ADV7393_SD_MODE_REG5_DEFAULT		(0x02)
#घोषणा ADV7393_SD_MODE_REG6_DEFAULT		(0x8C)
#घोषणा ADV7393_SD_MODE_REG7_DEFAULT		(0x14)
#घोषणा ADV7393_SD_MODE_REG8_DEFAULT		(0x00)

#घोषणा ADV7393_SD_TIMING_REG0_DEFAULT		(0x0C)

/* Bit masks क्रम Mode Select Register */
#घोषणा INPUT_MODE_MASK			(0x70)
#घोषणा SD_INPUT_MODE			(0x00)
#घोषणा HD_720P_INPUT_MODE		(0x10)
#घोषणा HD_1080I_INPUT_MODE		(0x10)

/* Bit masks क्रम Mode Register 0 */
#घोषणा TEST_PATTERN_BLACK_BAR_EN	(0x04)
#घोषणा YUV_OUTPUT_SELECT		(0x20)
#घोषणा RGB_OUTPUT_SELECT		(0xDF)

/* Bit masks क्रम SD brightness/WSS */
#घोषणा SD_BRIGHTNESS_VALUE_MASK	(0x7F)
#घोषणा SD_BLANK_WSS_DATA_MASK		(0x80)

/* Bit masks क्रम soft reset रेजिस्टर */
#घोषणा SOFT_RESET			(0x02)

/* Bit masks क्रम HD Mode Register 1 */
#घोषणा OUTPUT_STD_MASK		(0x03)
#घोषणा OUTPUT_STD_SHIFT	(0)
#घोषणा OUTPUT_STD_EIA0_2	(0x00)
#घोषणा OUTPUT_STD_EIA0_1	(0x01)
#घोषणा OUTPUT_STD_FULL		(0x02)
#घोषणा EMBEDDED_SYNC		(0x04)
#घोषणा EXTERNAL_SYNC		(0xFB)
#घोषणा STD_MODE_MASK		(0x1F)
#घोषणा STD_MODE_SHIFT		(3)
#घोषणा STD_MODE_720P		(0x05)
#घोषणा STD_MODE_720P_25	(0x08)
#घोषणा STD_MODE_720P_30	(0x07)
#घोषणा STD_MODE_720P_50	(0x06)
#घोषणा STD_MODE_1080I		(0x0D)
#घोषणा STD_MODE_1080I_25	(0x0E)
#घोषणा STD_MODE_1080P_24	(0x11)
#घोषणा STD_MODE_1080P_25	(0x10)
#घोषणा STD_MODE_1080P_30	(0x0F)
#घोषणा STD_MODE_525P		(0x00)
#घोषणा STD_MODE_625P		(0x03)

/* Bit masks क्रम SD Mode Register 1 */
#घोषणा SD_STD_MASK		(0x03)
#घोषणा SD_STD_NTSC		(0x00)
#घोषणा SD_STD_PAL_BDGHI	(0x01)
#घोषणा SD_STD_PAL_M		(0x02)
#घोषणा SD_STD_PAL_N		(0x03)
#घोषणा SD_LUMA_FLTR_MASK	(0x07)
#घोषणा SD_LUMA_FLTR_SHIFT	(2)
#घोषणा SD_CHROMA_FLTR_MASK	(0x07)
#घोषणा SD_CHROMA_FLTR_SHIFT	(5)

/* Bit masks क्रम SD Mode Register 2 */
#घोषणा SD_PRPB_SSAF_EN		(0x01)
#घोषणा SD_PRPB_SSAF_DI		(0xFE)
#घोषणा SD_DAC_OUT1_EN		(0x02)
#घोषणा SD_DAC_OUT1_DI		(0xFD)
#घोषणा SD_PEDESTAL_EN		(0x08)
#घोषणा SD_PEDESTAL_DI		(0xF7)
#घोषणा SD_SQUARE_PIXEL_EN	(0x10)
#घोषणा SD_SQUARE_PIXEL_DI	(0xEF)
#घोषणा SD_PIXEL_DATA_VALID	(0x40)
#घोषणा SD_ACTIVE_EDGE_EN	(0x80)
#घोषणा SD_ACTIVE_EDGE_DI	(0x7F)

/* Bit masks क्रम HD Mode Register 6 */
#घोषणा HD_PRPB_SYNC_EN		(0x04)
#घोषणा HD_PRPB_SYNC_DI		(0xFB)
#घोषणा HD_DAC_SWAP_EN		(0x08)
#घोषणा HD_DAC_SWAP_DI		(0xF7)
#घोषणा HD_GAMMA_CURVE_A	(0xEF)
#घोषणा HD_GAMMA_CURVE_B	(0x10)
#घोषणा HD_GAMMA_EN		(0x20)
#घोषणा HD_GAMMA_DI		(0xDF)
#घोषणा HD_ADPT_FLTR_MODEA	(0xBF)
#घोषणा HD_ADPT_FLTR_MODEB	(0x40)
#घोषणा HD_ADPT_FLTR_EN		(0x80)
#घोषणा HD_ADPT_FLTR_DI		(0x7F)

#घोषणा ADV7393_BRIGHTNESS_MAX	(63)
#घोषणा ADV7393_BRIGHTNESS_MIN	(-64)
#घोषणा ADV7393_BRIGHTNESS_DEF	(0)
#घोषणा ADV7393_HUE_MAX		(127)
#घोषणा ADV7393_HUE_MIN		(-128)
#घोषणा ADV7393_HUE_DEF		(0)
#घोषणा ADV7393_GAIN_MAX	(64)
#घोषणा ADV7393_GAIN_MIN	(-64)
#घोषणा ADV7393_GAIN_DEF	(0)

#पूर्ण_अगर
