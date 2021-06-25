<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 * tvp5150 - Texas Instruments TVP5150A/AM1 video decoder रेजिस्टरs
 *
 * Copyright (c) 2005,2006 Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#घोषणा TVP5150_VD_IN_SRC_SEL_1      0x00 /* Video input source selection #1 */
#घोषणा TVP5150_ANAL_CHL_CTL         0x01 /* Analog channel controls */
#घोषणा TVP5150_OP_MODE_CTL          0x02 /* Operation mode controls */
#घोषणा TVP5150_MISC_CTL             0x03 /* Miscellaneous controls */
#घोषणा TVP5150_MISC_CTL_VBLK_GPCL	BIT(7)
#घोषणा TVP5150_MISC_CTL_GPCL		BIT(6)
#घोषणा TVP5150_MISC_CTL_INTREQ_OE	BIT(5)
#घोषणा TVP5150_MISC_CTL_HVLK		BIT(4)
#घोषणा TVP5150_MISC_CTL_YCBCR_OE	BIT(3)
#घोषणा TVP5150_MISC_CTL_SYNC_OE	BIT(2)
#घोषणा TVP5150_MISC_CTL_VBLANK		BIT(1)
#घोषणा TVP5150_MISC_CTL_CLOCK_OE	BIT(0)

#घोषणा TVP5150_AUTOSW_MSK           0x04 /* Autoचयन mask: TVP5150A / TVP5150AM */

/* Reserved 05h */

#घोषणा TVP5150_COLOR_KIL_THSH_CTL   0x06 /* Color समाप्तer threshold control */
#घोषणा TVP5150_LUMA_PROC_CTL_1      0x07 /* Luminance processing control #1 */
#घोषणा TVP5150_LUMA_PROC_CTL_2      0x08 /* Luminance processing control #2 */
#घोषणा TVP5150_BRIGHT_CTL           0x09 /* Brightness control */
#घोषणा TVP5150_SATURATION_CTL       0x0a /* Color saturation control */
#घोषणा TVP5150_HUE_CTL              0x0b /* Hue control */
#घोषणा TVP5150_CONTRAST_CTL         0x0c /* Contrast control */
#घोषणा TVP5150_DATA_RATE_SEL        0x0d /* Outमाला_दो and data rates select */
#घोषणा TVP5150_LUMA_PROC_CTL_3      0x0e /* Luminance processing control #3 */
#घोषणा TVP5150_CONF_SHARED_PIN      0x0f /* Configuration shared pins */

/* Reserved 10h */

#घोषणा TVP5150_ACT_VD_CROP_ST_MSB   0x11 /* Active video cropping start MSB */
#घोषणा TVP5150_ACT_VD_CROP_ST_LSB   0x12 /* Active video cropping start LSB */
#घोषणा TVP5150_ACT_VD_CROP_STP_MSB  0x13 /* Active video cropping stop MSB */
#घोषणा TVP5150_ACT_VD_CROP_STP_LSB  0x14 /* Active video cropping stop LSB */
#घोषणा TVP5150_GENLOCK              0x15 /* Genlock/RTC */
#घोषणा TVP5150_HORIZ_SYNC_START     0x16 /* Horizontal sync start */

/* Reserved 17h */

#घोषणा TVP5150_VERT_BLANKING_START 0x18 /* Vertical blanking start */
#घोषणा TVP5150_VERT_BLANKING_STOP  0x19 /* Vertical blanking stop */
#घोषणा TVP5150_CHROMA_PROC_CTL_1   0x1a /* Chrominance processing control #1 */
#घोषणा TVP5150_CHROMA_PROC_CTL_2   0x1b /* Chrominance processing control #2 */
#घोषणा TVP5150_INT_RESET_REG_B     0x1c /* Interrupt reset रेजिस्टर B */
#घोषणा TVP5150_INT_ENABLE_REG_B    0x1d /* Interrupt enable रेजिस्टर B */
#घोषणा TVP5150_INTT_CONFIG_REG_B   0x1e /* Interrupt configuration रेजिस्टर B */

/* Reserved 1Fh-27h */

#घोषणा VIDEO_STD_MASK			 (0x07 >> 1)
#घोषणा TVP5150_VIDEO_STD                0x28 /* Video standard */
#घोषणा VIDEO_STD_AUTO_SWITCH_BIT	 0x00
#घोषणा VIDEO_STD_NTSC_MJ_BIT		 0x02
#घोषणा VIDEO_STD_PAL_BDGHIN_BIT	 0x04
#घोषणा VIDEO_STD_PAL_M_BIT		 0x06
#घोषणा VIDEO_STD_PAL_COMBINATION_N_BIT	 0x08
#घोषणा VIDEO_STD_NTSC_4_43_BIT		 0x0a
#घोषणा VIDEO_STD_SECAM_BIT		 0x0c

#घोषणा VIDEO_STD_NTSC_MJ_BIT_AS                 0x01
#घोषणा VIDEO_STD_PAL_BDGHIN_BIT_AS              0x03
#घोषणा VIDEO_STD_PAL_M_BIT_AS			 0x05
#घोषणा VIDEO_STD_PAL_COMBINATION_N_BIT_AS	 0x07
#घोषणा VIDEO_STD_NTSC_4_43_BIT_AS		 0x09
#घोषणा VIDEO_STD_SECAM_BIT_AS			 0x0b

/* Reserved 29h-2bh */

#घोषणा TVP5150_CB_GAIN_FACT        0x2c /* Cb gain factor */
#घोषणा TVP5150_CR_GAIN_FACTOR      0x2d /* Cr gain factor */
#घोषणा TVP5150_MACROVISION_ON_CTR  0x2e /* Macrovision on counter */
#घोषणा TVP5150_MACROVISION_OFF_CTR 0x2f /* Macrovision off counter */
#घोषणा TVP5150_REV_SELECT          0x30 /* revision select (TVP5150AM1 only) */

/* Reserved	31h-7Fh */

#घोषणा TVP5150_MSB_DEV_ID          0x80 /* MSB of device ID */
#घोषणा TVP5150_LSB_DEV_ID          0x81 /* LSB of device ID */
#घोषणा TVP5150_ROM_MAJOR_VER       0x82 /* ROM major version */
#घोषणा TVP5150_ROM_MINOR_VER       0x83 /* ROM minor version */
#घोषणा TVP5150_VERT_LN_COUNT_MSB   0x84 /* Vertical line count MSB */
#घोषणा TVP5150_VERT_LN_COUNT_LSB   0x85 /* Vertical line count LSB */
#घोषणा TVP5150_INT_STATUS_REG_B    0x86 /* Interrupt status रेजिस्टर B */
#घोषणा TVP5150_INT_ACTIVE_REG_B    0x87 /* Interrupt active रेजिस्टर B */
#घोषणा TVP5150_STATUS_REG_1        0x88 /* Status रेजिस्टर #1 */
#घोषणा TVP5150_STATUS_REG_2        0x89 /* Status रेजिस्टर #2 */
#घोषणा TVP5150_STATUS_REG_3        0x8a /* Status रेजिस्टर #3 */
#घोषणा TVP5150_STATUS_REG_4        0x8b /* Status रेजिस्टर #4 */
#घोषणा TVP5150_STATUS_REG_5        0x8c /* Status रेजिस्टर #5 */
/* Reserved	8Dh-8Fh */
 /* Closed caption data रेजिस्टरs */
#घोषणा TVP5150_CC_DATA_INI         0x90
#घोषणा TVP5150_CC_DATA_END         0x93

 /* WSS data रेजिस्टरs */
#घोषणा TVP5150_WSS_DATA_INI        0x94
#घोषणा TVP5150_WSS_DATA_END        0x99

/* VPS data रेजिस्टरs */
#घोषणा TVP5150_VPS_DATA_INI        0x9a
#घोषणा TVP5150_VPS_DATA_END        0xa6

/* VITC data रेजिस्टरs */
#घोषणा TVP5150_VITC_DATA_INI       0xa7
#घोषणा TVP5150_VITC_DATA_END       0xaf

#घोषणा TVP5150_VBI_FIFO_READ_DATA  0xb0 /* VBI FIFO पढ़ो data */

/* Teletext filter 1 */
#घोषणा TVP5150_TELETEXT_FIL1_INI  0xb1
#घोषणा TVP5150_TELETEXT_FIL1_END  0xb5

/* Teletext filter 2 */
#घोषणा TVP5150_TELETEXT_FIL2_INI  0xb6
#घोषणा TVP5150_TELETEXT_FIL2_END  0xba

#घोषणा TVP5150_TELETEXT_FIL_ENA    0xbb /* Teletext filter enable */
/* Reserved	BCh-BFh */
#घोषणा TVP5150_INT_STATUS_REG_A    0xc0 /* Interrupt status रेजिस्टर A */
#घोषणा   TVP5150_INT_A_LOCK_STATUS BIT(7)
#घोषणा   TVP5150_INT_A_LOCK        BIT(6)
#घोषणा TVP5150_INT_ENABLE_REG_A    0xc1 /* Interrupt enable रेजिस्टर A */
#घोषणा TVP5150_INT_CONF            0xc2 /* Interrupt configuration */
#घोषणा   TVP5150_VDPOE             BIT(2)
#घोषणा TVP5150_VDP_CONF_RAM_DATA   0xc3 /* VDP configuration RAM data */
#घोषणा TVP5150_CONF_RAM_ADDR_LOW   0xc4 /* Configuration RAM address low byte */
#घोषणा TVP5150_CONF_RAM_ADDR_HIGH  0xc5 /* Configuration RAM address high byte */
#घोषणा TVP5150_VDP_STATUS_REG      0xc6 /* VDP status रेजिस्टर */
#घोषणा TVP5150_FIFO_WORD_COUNT     0xc7 /* FIFO word count */
#घोषणा TVP5150_FIFO_INT_THRESHOLD  0xc8 /* FIFO पूर्णांकerrupt threshold */
#घोषणा TVP5150_FIFO_RESET          0xc9 /* FIFO reset */
#घोषणा TVP5150_LINE_NUMBER_INT     0xca /* Line number पूर्णांकerrupt */
#घोषणा TVP5150_PIX_ALIGN_REG_LOW   0xcb /* Pixel alignment रेजिस्टर low byte */
#घोषणा TVP5150_PIX_ALIGN_REG_HIGH  0xcc /* Pixel alignment रेजिस्टर high byte */
#घोषणा TVP5150_FIFO_OUT_CTRL       0xcd /* FIFO output control */
/* Reserved	CEh */
#घोषणा TVP5150_FULL_FIELD_ENA      0xcf /* Full field enable 1 */

/* Line mode रेजिस्टरs */
#घोषणा TVP5150_LINE_MODE_INI       0xd0
#घोषणा TVP5150_LINE_MODE_END       0xfb

#घोषणा TVP5150_FULL_FIELD_MODE_REG 0xfc /* Full field mode रेजिस्टर */
/* Reserved	FDh-FFh */
