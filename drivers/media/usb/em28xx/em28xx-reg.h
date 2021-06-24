<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * em28xx-reg.h - Register definitions क्रम em28xx driver
 */

#घोषणा EM_GPIO_0  ((अचिन्हित अक्षर)BIT(0))
#घोषणा EM_GPIO_1  ((अचिन्हित अक्षर)BIT(1))
#घोषणा EM_GPIO_2  ((अचिन्हित अक्षर)BIT(2))
#घोषणा EM_GPIO_3  ((अचिन्हित अक्षर)BIT(3))
#घोषणा EM_GPIO_4  ((अचिन्हित अक्षर)BIT(4))
#घोषणा EM_GPIO_5  ((अचिन्हित अक्षर)BIT(5))
#घोषणा EM_GPIO_6  ((अचिन्हित अक्षर)BIT(6))
#घोषणा EM_GPIO_7  ((अचिन्हित अक्षर)BIT(7))

#घोषणा EM_GPO_0   ((अचिन्हित अक्षर)BIT(0))
#घोषणा EM_GPO_1   ((अचिन्हित अक्षर)BIT(1))
#घोषणा EM_GPO_2   ((अचिन्हित अक्षर)BIT(2))
#घोषणा EM_GPO_3   ((अचिन्हित अक्षर)BIT(3))

/* em28xx endpoपूर्णांकs */
/* 0x82:   (always ?) analog */
#घोषणा EM28XX_EP_AUDIO		0x83
/* 0x84:   digital or analog */

/* em2800 रेजिस्टरs */
#घोषणा EM2800_R08_AUDIOSRC 0x08

/* em28xx रेजिस्टरs */

#घोषणा EM28XX_R00_CHIPCFG	0x00

/* em28xx Chip Configuration 0x00 */
#घोषणा EM2860_CHIPCFG_VENDOR_AUDIO		0x80
#घोषणा EM2860_CHIPCFG_I2S_VOLUME_CAPABLE	0x40
#घोषणा EM2820_CHIPCFG_I2S_3_SAMPRATES		0x30
#घोषणा EM2860_CHIPCFG_I2S_5_SAMPRATES		0x30
#घोषणा EM2820_CHIPCFG_I2S_1_SAMPRATE		0x20
#घोषणा EM2860_CHIPCFG_I2S_3_SAMPRATES		0x20
#घोषणा EM28XX_CHIPCFG_AC97			0x10
#घोषणा EM28XX_CHIPCFG_AUDIOMASK		0x30

#घोषणा EM28XX_R01_CHIPCFG2	0x01

/* em28xx Chip Configuration 2 0x01 */
#घोषणा EM28XX_CHIPCFG2_TS_PRESENT		0x10
#घोषणा EM28XX_CHIPCFG2_TS_REQ_INTERVAL_MASK	0x0c /* bits 3-2 */
#घोषणा EM28XX_CHIPCFG2_TS_REQ_INTERVAL_1MF	0x00
#घोषणा EM28XX_CHIPCFG2_TS_REQ_INTERVAL_2MF	0x04
#घोषणा EM28XX_CHIPCFG2_TS_REQ_INTERVAL_4MF	0x08
#घोषणा EM28XX_CHIPCFG2_TS_REQ_INTERVAL_8MF	0x0c
#घोषणा EM28XX_CHIPCFG2_TS_PACKETSIZE_MASK	0x03 /* bits 0-1 */
#घोषणा EM28XX_CHIPCFG2_TS_PACKETSIZE_188	0x00
#घोषणा EM28XX_CHIPCFG2_TS_PACKETSIZE_376	0x01
#घोषणा EM28XX_CHIPCFG2_TS_PACKETSIZE_564	0x02
#घोषणा EM28XX_CHIPCFG2_TS_PACKETSIZE_752	0x03

/* GPIO/GPO रेजिस्टरs */
#घोषणा EM2880_R04_GPO		0x04    /* em2880-em2883 only */
#घोषणा EM2820_R08_GPIO_CTRL	0x08	/* em2820-em2873/83 only */
#घोषणा EM2820_R09_GPIO_STATE	0x09	/* em2820-em2873/83 only */

#घोषणा EM28XX_R06_I2C_CLK	0x06

/* em28xx I2C Clock Register (0x06) */
#घोषणा EM28XX_I2C_CLK_ACK_LAST_READ	0x80
#घोषणा EM28XX_I2C_CLK_WAIT_ENABLE	0x40
#घोषणा EM28XX_I2C_EEPROM_ON_BOARD	0x08
#घोषणा EM28XX_I2C_EEPROM_KEY_VALID	0x04
#घोषणा EM2874_I2C_SECONDARY_BUS_SELECT	0x04 /* em2874 has two i2c buses */
#घोषणा EM28XX_I2C_FREQ_1_5_MHZ		0x03 /* bus frequency (bits [1-0]) */
#घोषणा EM28XX_I2C_FREQ_25_KHZ		0x02
#घोषणा EM28XX_I2C_FREQ_400_KHZ		0x01
#घोषणा EM28XX_I2C_FREQ_100_KHZ		0x00

#घोषणा EM28XX_R0A_CHIPID	0x0a
#घोषणा EM28XX_R0C_USBSUSP	0x0c
#घोषणा   EM28XX_R0C_USBSUSP_SNAPSHOT	0x20 /* 1=button pressed, needs reset */

#घोषणा EM28XX_R0E_AUDIOSRC	0x0e
#घोषणा EM28XX_R0F_XCLK	0x0f

/* em28xx XCLK Register (0x0f) */
#घोषणा EM28XX_XCLK_AUDIO_UNMUTE	0x80 /* otherwise audio muted */
#घोषणा EM28XX_XCLK_I2S_MSB_TIMING	0x40 /* otherwise standard timing */
#घोषणा EM28XX_XCLK_IR_RC5_MODE		0x20 /* otherwise NEC mode */
#घोषणा EM28XX_XCLK_IR_NEC_CHK_PARITY	0x10
#घोषणा EM28XX_XCLK_FREQUENCY_30MHZ	0x00 /* Freq. select (bits [3-0]) */
#घोषणा EM28XX_XCLK_FREQUENCY_15MHZ	0x01
#घोषणा EM28XX_XCLK_FREQUENCY_10MHZ	0x02
#घोषणा EM28XX_XCLK_FREQUENCY_7_5MHZ	0x03
#घोषणा EM28XX_XCLK_FREQUENCY_6MHZ	0x04
#घोषणा EM28XX_XCLK_FREQUENCY_5MHZ	0x05
#घोषणा EM28XX_XCLK_FREQUENCY_4_3MHZ	0x06
#घोषणा EM28XX_XCLK_FREQUENCY_12MHZ	0x07
#घोषणा EM28XX_XCLK_FREQUENCY_20MHZ	0x08
#घोषणा EM28XX_XCLK_FREQUENCY_20MHZ_2	0x09
#घोषणा EM28XX_XCLK_FREQUENCY_48MHZ	0x0a
#घोषणा EM28XX_XCLK_FREQUENCY_24MHZ	0x0b

#घोषणा EM28XX_R10_VINMODE	0x10
	  /* used by all non-camera devices: */
#घोषणा   EM28XX_VINMODE_YUV422_CbYCrY  0x10
	  /* used by camera devices: */
#घोषणा   EM28XX_VINMODE_YUV422_YUYV    0x08
#घोषणा   EM28XX_VINMODE_YUV422_YVYU    0x09
#घोषणा   EM28XX_VINMODE_YUV422_UYVY    0x0a
#घोषणा   EM28XX_VINMODE_YUV422_VYUY    0x0b
#घोषणा   EM28XX_VINMODE_RGB8_BGGR      0x0c
#घोषणा   EM28XX_VINMODE_RGB8_GRBG      0x0d
#घोषणा   EM28XX_VINMODE_RGB8_GBRG      0x0e
#घोषणा   EM28XX_VINMODE_RGB8_RGGB      0x0f
	  /*
	   * apparently:
	   *   bit 0: swap component 1+2 with 3+4
	   *                 => e.g.: YUYV => YVYU, BGGR => GRBG
	   *   bit 1: swap component 1 with 2 and 3 with 4
	   *                 => e.g.: YUYV => UYVY, BGGR => GBRG
	   */

#घोषणा EM28XX_R11_VINCTRL	0x11

/* em28xx Video Input Control Register 0x11 */
#घोषणा EM28XX_VINCTRL_VBI_SLICED	0x80
#घोषणा EM28XX_VINCTRL_VBI_RAW		0x40
#घोषणा EM28XX_VINCTRL_VOUT_MODE_IN	0x20 /* HREF,VREF,VACT in output */
#घोषणा EM28XX_VINCTRL_CCIR656_ENABLE	0x10
#घोषणा EM28XX_VINCTRL_VBI_16BIT_RAW	0x08 /* otherwise 8-bit raw */
#घोषणा EM28XX_VINCTRL_FID_ON_HREF	0x04
#घोषणा EM28XX_VINCTRL_DUAL_EDGE_STROBE	0x02
#घोषणा EM28XX_VINCTRL_INTERLACED	0x01

#घोषणा EM28XX_R12_VINENABLE	0x12	/* */

#घोषणा EM28XX_R14_GAMMA	0x14
#घोषणा EM28XX_R15_RGAIN	0x15
#घोषणा EM28XX_R16_GGAIN	0x16
#घोषणा EM28XX_R17_BGAIN	0x17
#घोषणा EM28XX_R18_ROFFSET	0x18
#घोषणा EM28XX_R19_GOFFSET	0x19
#घोषणा EM28XX_R1A_BOFFSET	0x1a

#घोषणा EM28XX_R1B_OFLOW	0x1b
#घोषणा EM28XX_R1C_HSTART	0x1c
#घोषणा EM28XX_R1D_VSTART	0x1d
#घोषणा EM28XX_R1E_CWIDTH	0x1e
#घोषणा EM28XX_R1F_CHEIGHT	0x1f

#घोषणा EM28XX_R20_YGAIN	0x20 /* contrast [0:4]   */
#घोषणा   CONTRAST_DEFAULT	0x10

#घोषणा EM28XX_R21_YOFFSET	0x21 /* brightness       */	/* चिन्हित */
#घोषणा   BRIGHTNESS_DEFAULT	0x00

#घोषणा EM28XX_R22_UVGAIN	0x22 /* saturation [0:4] */
#घोषणा   SATURATION_DEFAULT	0x10

#घोषणा EM28XX_R23_UOFFSET	0x23 /* blue balance     */	/* चिन्हित */
#घोषणा   BLUE_BALANCE_DEFAULT	0x00

#घोषणा EM28XX_R24_VOFFSET	0x24 /* red balance      */	/* चिन्हित */
#घोषणा   RED_BALANCE_DEFAULT	0x00

#घोषणा EM28XX_R25_SHARPNESS	0x25 /* sharpness [0:4]  */
#घोषणा   SHARPNESS_DEFAULT	0x00

#घोषणा EM28XX_R26_COMPR	0x26
#घोषणा EM28XX_R27_OUTFMT	0x27

/* em28xx Output Format Register (0x27) */
#घोषणा EM28XX_OUTFMT_RGB_8_RGRG	0x00
#घोषणा EM28XX_OUTFMT_RGB_8_GRGR	0x01
#घोषणा EM28XX_OUTFMT_RGB_8_GBGB	0x02
#घोषणा EM28XX_OUTFMT_RGB_8_BGBG	0x03
#घोषणा EM28XX_OUTFMT_RGB_16_656	0x04
#घोषणा EM28XX_OUTFMT_RGB_8_BAYER	0x08 /* Pattern in Reg 0x10[1-0] */
#घोषणा EM28XX_OUTFMT_YUV211		0x10
#घोषणा EM28XX_OUTFMT_YUV422_Y0UY1V	0x14
#घोषणा EM28XX_OUTFMT_YUV422_Y1UY0V	0x15
#घोषणा EM28XX_OUTFMT_YUV411		0x18

#घोषणा EM28XX_R28_XMIN	0x28
#घोषणा EM28XX_R29_XMAX	0x29
#घोषणा EM28XX_R2A_YMIN	0x2a
#घोषणा EM28XX_R2B_YMAX	0x2b

#घोषणा EM28XX_R30_HSCALELOW	0x30
#घोषणा EM28XX_R31_HSCALEHIGH	0x31
#घोषणा EM28XX_R32_VSCALELOW	0x32
#घोषणा EM28XX_R33_VSCALEHIGH	0x33
#घोषणा   EM28XX_HVSCALE_MAX	0x3fff /* => 20% */

#घोषणा EM28XX_R34_VBI_START_H	0x34
#घोषणा EM28XX_R35_VBI_START_V	0x35
/*
 * NOTE: the EM276x (and EM25xx, EM277x/8x ?) (camera bridges) use these
 * रेजिस्टरs क्रम a dअगरferent unknown purpose.
 *   => रेजिस्टर 0x34 is set to capture width / 16
 *   => रेजिस्टर 0x35 is set to capture height / 16
 */

#घोषणा EM28XX_R36_VBI_WIDTH	0x36
#घोषणा EM28XX_R37_VBI_HEIGHT	0x37

#घोषणा EM28XX_R40_AC97LSB	0x40
#घोषणा EM28XX_R41_AC97MSB	0x41
#घोषणा EM28XX_R42_AC97ADDR	0x42
#घोषणा EM28XX_R43_AC97BUSY	0x43

#घोषणा EM28XX_R45_IR		0x45
	/*
	 * 0x45  bit 7    - parity bit
	 *	 bits 6-0 - count
	 * 0x46  IR bअक्रम
	 *  0x47  IR data
	 */

/* em2874 रेजिस्टरs */
#घोषणा EM2874_R50_IR_CONFIG    0x50
#घोषणा EM2874_R51_IR           0x51
#घोषणा EM2874_R5D_TS1_PKT_SIZE 0x5d
#घोषणा EM2874_R5E_TS2_PKT_SIZE 0x5e
	/*
	 * For both TS1 and TS2, In isochronous mode:
	 *  0x01  188 bytes
	 *  0x02  376 bytes
	 *  0x03  564 bytes
	 *  0x04  752 bytes
	 *  0x05  940 bytes
	 * In bulk mode:
	 *  0x01..0xff  total packet count in 188-byte
	 */

#घोषणा EM2874_R5F_TS_ENABLE    0x5f

/* em2874/174/84, em25xx, em276x/7x/8x GPIO रेजिस्टरs */
/*
 * NOTE: not all ports are bonded out;
 * Some ports are multiplexed with special function I/O
 */
#घोषणा EM2874_R80_GPIO_P0_CTRL    0x80
#घोषणा EM2874_R81_GPIO_P1_CTRL    0x81
#घोषणा EM2874_R82_GPIO_P2_CTRL    0x82
#घोषणा EM2874_R83_GPIO_P3_CTRL    0x83
#घोषणा EM2874_R84_GPIO_P0_STATE   0x84
#घोषणा EM2874_R85_GPIO_P1_STATE   0x85
#घोषणा EM2874_R86_GPIO_P2_STATE   0x86
#घोषणा EM2874_R87_GPIO_P3_STATE   0x87

/* em2874 IR config रेजिस्टर (0x50) */
#घोषणा EM2874_IR_NEC           0x00
#घोषणा EM2874_IR_NEC_NO_PARITY 0x01
#घोषणा EM2874_IR_RC5           0x04
#घोषणा EM2874_IR_RC6_MODE_0    0x08
#घोषणा EM2874_IR_RC6_MODE_6A   0x0b

/* em2874 Transport Stream Enable Register (0x5f) */
#घोषणा EM2874_TS1_CAPTURE_ENABLE ((अचिन्हित अक्षर)BIT(0))
#घोषणा EM2874_TS1_FILTER_ENABLE  ((अचिन्हित अक्षर)BIT(1))
#घोषणा EM2874_TS1_शून्य_DISCARD   ((अचिन्हित अक्षर)BIT(2))
#घोषणा EM2874_TS2_CAPTURE_ENABLE ((अचिन्हित अक्षर)BIT(4))
#घोषणा EM2874_TS2_FILTER_ENABLE  ((अचिन्हित अक्षर)BIT(5))
#घोषणा EM2874_TS2_शून्य_DISCARD   ((अचिन्हित अक्षर)BIT(6))

/* रेजिस्टर settings */
#घोषणा EM2800_AUDIO_SRC_TUNER  0x0d
#घोषणा EM2800_AUDIO_SRC_LINE   0x0c
#घोषणा EM28XX_AUDIO_SRC_TUNER	0xc0
#घोषणा EM28XX_AUDIO_SRC_LINE	0x80

/* FIXME: Need to be populated with the other chip ID's */
क्रमागत em28xx_chip_id अणु
	CHIP_ID_EM2800 = 7,
	CHIP_ID_EM2710 = 17,
	CHIP_ID_EM2820 = 18,	/* Also used by some em2710 */
	CHIP_ID_EM2840 = 20,
	CHIP_ID_EM2750 = 33,
	CHIP_ID_EM2860 = 34,
	CHIP_ID_EM2870 = 35,
	CHIP_ID_EM2883 = 36,
	CHIP_ID_EM2765 = 54,
	CHIP_ID_EM2874 = 65,
	CHIP_ID_EM2884 = 68,
	CHIP_ID_EM28174 = 113,
	CHIP_ID_EM28178 = 114,
पूर्ण;

/*
 * Registers used by em202
 */

/* EMP202 venकरोr रेजिस्टरs */
#घोषणा EM202_EXT_MODEM_CTRL     0x3e
#घोषणा EM202_GPIO_CONF          0x4c
#घोषणा EM202_GPIO_POLARITY      0x4e
#घोषणा EM202_GPIO_STICKY        0x50
#घोषणा EM202_GPIO_MASK          0x52
#घोषणा EM202_GPIO_STATUS        0x54
#घोषणा EM202_SPDIF_OUT_SEL      0x6a
#घोषणा EM202_ANTIPOP            0x72
#घोषणा EM202_EAPD_GPIO_ACCESS   0x74
