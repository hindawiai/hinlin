<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ov2640 Camera Driver
 *
 * Copyright (C) 2010 Alberto Panizzo <maramaopercheseimorto@gmail.com>
 *
 * Based on ov772x, ov9640 drivers and previous non merged implementations.
 *
 * Copyright 2005-2009 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2006, OmniVision
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-image-sizes.h>

#घोषणा VAL_SET(x, mask, rshअगरt, lshअगरt)  \
		((((x) >> rshअगरt) & mask) << lshअगरt)
/*
 * DSP रेजिस्टरs
 * रेजिस्टर offset क्रम BANK_SEL == BANK_SEL_DSP
 */
#घोषणा R_BYPASS    0x05 /* Bypass DSP */
#घोषणा   R_BYPASS_DSP_BYPAS    0x01 /* Bypass DSP, sensor out directly */
#घोषणा   R_BYPASS_USE_DSP      0x00 /* Use the पूर्णांकernal DSP */
#घोषणा QS          0x44 /* Quantization Scale Factor */
#घोषणा CTRLI       0x50
#घोषणा   CTRLI_LP_DP           0x80
#घोषणा   CTRLI_ROUND           0x40
#घोषणा   CTRLI_V_DIV_SET(x)    VAL_SET(x, 0x3, 0, 3)
#घोषणा   CTRLI_H_DIV_SET(x)    VAL_SET(x, 0x3, 0, 0)
#घोषणा HSIZE       0x51 /* H_SIZE[7:0] (real/4) */
#घोषणा   HSIZE_SET(x)          VAL_SET(x, 0xFF, 2, 0)
#घोषणा VSIZE       0x52 /* V_SIZE[7:0] (real/4) */
#घोषणा   VSIZE_SET(x)          VAL_SET(x, 0xFF, 2, 0)
#घोषणा XOFFL       0x53 /* OFFSET_X[7:0] */
#घोषणा   XOFFL_SET(x)          VAL_SET(x, 0xFF, 0, 0)
#घोषणा YOFFL       0x54 /* OFFSET_Y[7:0] */
#घोषणा   YOFFL_SET(x)          VAL_SET(x, 0xFF, 0, 0)
#घोषणा VHYX        0x55 /* Offset and size completion */
#घोषणा   VHYX_VSIZE_SET(x)     VAL_SET(x, 0x1, (8+2), 7)
#घोषणा   VHYX_HSIZE_SET(x)     VAL_SET(x, 0x1, (8+2), 3)
#घोषणा   VHYX_YOFF_SET(x)      VAL_SET(x, 0x3, 8, 4)
#घोषणा   VHYX_XOFF_SET(x)      VAL_SET(x, 0x3, 8, 0)
#घोषणा DPRP        0x56
#घोषणा TEST        0x57 /* Horizontal size completion */
#घोषणा   TEST_HSIZE_SET(x)     VAL_SET(x, 0x1, (9+2), 7)
#घोषणा ZMOW        0x5A /* Zoom: Out Width  OUTW[7:0] (real/4) */
#घोषणा   ZMOW_OUTW_SET(x)      VAL_SET(x, 0xFF, 2, 0)
#घोषणा ZMOH        0x5B /* Zoom: Out Height OUTH[7:0] (real/4) */
#घोषणा   ZMOH_OUTH_SET(x)      VAL_SET(x, 0xFF, 2, 0)
#घोषणा ZMHH        0x5C /* Zoom: Speed and H&W completion */
#घोषणा   ZMHH_ZSPEED_SET(x)    VAL_SET(x, 0x0F, 0, 4)
#घोषणा   ZMHH_OUTH_SET(x)      VAL_SET(x, 0x1, (8+2), 2)
#घोषणा   ZMHH_OUTW_SET(x)      VAL_SET(x, 0x3, (8+2), 0)
#घोषणा BPADDR      0x7C /* SDE Indirect Register Access: Address */
#घोषणा BPDATA      0x7D /* SDE Indirect Register Access: Data */
#घोषणा CTRL2       0x86 /* DSP Module enable 2 */
#घोषणा   CTRL2_DCW_EN          0x20
#घोषणा   CTRL2_SDE_EN          0x10
#घोषणा   CTRL2_UV_ADJ_EN       0x08
#घोषणा   CTRL2_UV_AVG_EN       0x04
#घोषणा   CTRL2_CMX_EN          0x01
#घोषणा CTRL3       0x87 /* DSP Module enable 3 */
#घोषणा   CTRL3_BPC_EN          0x80
#घोषणा   CTRL3_WPC_EN          0x40
#घोषणा SIZEL       0x8C /* Image Size Completion */
#घोषणा   SIZEL_HSIZE8_11_SET(x) VAL_SET(x, 0x1, 11, 6)
#घोषणा   SIZEL_HSIZE8_SET(x)    VAL_SET(x, 0x7, 0, 3)
#घोषणा   SIZEL_VSIZE8_SET(x)    VAL_SET(x, 0x7, 0, 0)
#घोषणा HSIZE8      0xC0 /* Image Horizontal Size HSIZE[10:3] */
#घोषणा   HSIZE8_SET(x)         VAL_SET(x, 0xFF, 3, 0)
#घोषणा VSIZE8      0xC1 /* Image Vertical Size VSIZE[10:3] */
#घोषणा   VSIZE8_SET(x)         VAL_SET(x, 0xFF, 3, 0)
#घोषणा CTRL0       0xC2 /* DSP Module enable 0 */
#घोषणा   CTRL0_AEC_EN       0x80
#घोषणा   CTRL0_AEC_SEL      0x40
#घोषणा   CTRL0_STAT_SEL     0x20
#घोषणा   CTRL0_VFIRST       0x10
#घोषणा   CTRL0_YUV422       0x08
#घोषणा   CTRL0_YUV_EN       0x04
#घोषणा   CTRL0_RGB_EN       0x02
#घोषणा   CTRL0_RAW_EN       0x01
#घोषणा CTRL1       0xC3 /* DSP Module enable 1 */
#घोषणा   CTRL1_CIP          0x80
#घोषणा   CTRL1_DMY          0x40
#घोषणा   CTRL1_RAW_GMA      0x20
#घोषणा   CTRL1_DG           0x10
#घोषणा   CTRL1_AWB          0x08
#घोषणा   CTRL1_AWB_GAIN     0x04
#घोषणा   CTRL1_LENC         0x02
#घोषणा   CTRL1_PRE          0x01
/*      REG 0xC7 (unknown name): affects Auto White Balance (AWB)
 *	  AWB_OFF            0x40
 *	  AWB_SIMPLE         0x10
 *	  AWB_ON             0x00	(Advanced AWB ?) */
#घोषणा R_DVP_SP    0xD3 /* DVP output speed control */
#घोषणा   R_DVP_SP_AUTO_MODE 0x80
#घोषणा   R_DVP_SP_DVP_MASK  0x3F /* DVP PCLK = sysclk (48)/[6:0] (YUV0);
				   *          = sysclk (48)/(2*[6:0]) (RAW);*/
#घोषणा IMAGE_MODE  0xDA /* Image Output Format Select */
#घोषणा   IMAGE_MODE_Y8_DVP_EN   0x40
#घोषणा   IMAGE_MODE_JPEG_EN     0x10
#घोषणा   IMAGE_MODE_YUV422      0x00
#घोषणा   IMAGE_MODE_RAW10       0x04 /* (DVP) */
#घोषणा   IMAGE_MODE_RGB565      0x08
#घोषणा   IMAGE_MODE_HREF_VSYNC  0x02 /* HREF timing select in DVP JPEG output
				       * mode (0 क्रम HREF is same as sensor) */
#घोषणा   IMAGE_MODE_LBYTE_FIRST 0x01 /* Byte swap enable क्रम DVP
				       *    1: Low byte first UYVY (C2[4] =0)
				       *        VYUY (C2[4] =1)
				       *    0: High byte first YUYV (C2[4]=0)
				       *        YVYU (C2[4] = 1) */
#घोषणा RESET       0xE0 /* Reset */
#घोषणा   RESET_MICROC       0x40
#घोषणा   RESET_SCCB         0x20
#घोषणा   RESET_JPEG         0x10
#घोषणा   RESET_DVP          0x04
#घोषणा   RESET_IPU          0x02
#घोषणा   RESET_CIF          0x01
#घोषणा REGED       0xED /* Register ED */
#घोषणा   REGED_CLK_OUT_DIS  0x10
#घोषणा MS_SP       0xF0 /* SCCB Master Speed */
#घोषणा SS_ID       0xF7 /* SCCB Slave ID */
#घोषणा SS_CTRL     0xF8 /* SCCB Slave Control */
#घोषणा   SS_CTRL_ADD_AUTO_INC  0x20
#घोषणा   SS_CTRL_EN            0x08
#घोषणा   SS_CTRL_DELAY_CLK     0x04
#घोषणा   SS_CTRL_ACC_EN        0x02
#घोषणा   SS_CTRL_SEN_PASS_THR  0x01
#घोषणा MC_BIST     0xF9 /* Microcontroller misc रेजिस्टर */
#घोषणा   MC_BIST_RESET           0x80 /* Microcontroller Reset */
#घोषणा   MC_BIST_BOOT_ROM_SEL    0x40
#घोषणा   MC_BIST_12KB_SEL        0x20
#घोषणा   MC_BIST_12KB_MASK       0x30
#घोषणा   MC_BIST_512KB_SEL       0x08
#घोषणा   MC_BIST_512KB_MASK      0x0C
#घोषणा   MC_BIST_BUSY_BIT_R      0x02
#घोषणा   MC_BIST_MC_RES_ONE_SH_W 0x02
#घोषणा   MC_BIST_LAUNCH          0x01
#घोषणा BANK_SEL    0xFF /* Register Bank Select */
#घोषणा   BANK_SEL_DSP     0x00
#घोषणा   BANK_SEL_SENS    0x01

/*
 * Sensor रेजिस्टरs
 * रेजिस्टर offset क्रम BANK_SEL == BANK_SEL_SENS
 */
#घोषणा GAIN        0x00 /* AGC - Gain control gain setting */
#घोषणा COM1        0x03 /* Common control 1 */
#घोषणा   COM1_1_DUMMY_FR          0x40
#घोषणा   COM1_3_DUMMY_FR          0x80
#घोषणा   COM1_7_DUMMY_FR          0xC0
#घोषणा   COM1_VWIN_LSB_UXGA       0x0F
#घोषणा   COM1_VWIN_LSB_SVGA       0x0A
#घोषणा   COM1_VWIN_LSB_CIF        0x06
#घोषणा REG04       0x04 /* Register 04 */
#घोषणा   REG04_DEF             0x20 /* Always set */
#घोषणा   REG04_HFLIP_IMG       0x80 /* Horizontal mirror image ON/OFF */
#घोषणा   REG04_VFLIP_IMG       0x40 /* Vertical flip image ON/OFF */
#घोषणा   REG04_VREF_EN         0x10
#घोषणा   REG04_HREF_EN         0x08
#घोषणा   REG04_AEC_SET(x)      VAL_SET(x, 0x3, 0, 0)
#घोषणा REG08       0x08 /* Frame Exposure One-pin Control Pre-अक्षरge Row Num */
#घोषणा COM2        0x09 /* Common control 2 */
#घोषणा   COM2_SOFT_SLEEP_MODE  0x10 /* Soft sleep mode */
				     /* Output drive capability */
#घोषणा   COM2_OCAP_Nx_SET(N)   (((N) - 1) & 0x03) /* N = [1x .. 4x] */
#घोषणा PID         0x0A /* Product ID Number MSB */
#घोषणा VER         0x0B /* Product ID Number LSB */
#घोषणा COM3        0x0C /* Common control 3 */
#घोषणा   COM3_BAND_50H        0x04 /* 0 For Banding at 60H */
#घोषणा   COM3_BAND_AUTO       0x02 /* Auto Banding */
#घोषणा   COM3_SING_FR_SNAPSH  0x01 /* 0 For enable live video output after the
				     * snapshot sequence*/
#घोषणा AEC         0x10 /* AEC[9:2] Exposure Value */
#घोषणा CLKRC       0x11 /* Internal घड़ी */
#घोषणा   CLKRC_EN             0x80
#घोषणा   CLKRC_DIV_SET(x)     (((x) - 1) & 0x1F) /* CLK = XVCLK/(x) */
#घोषणा COM7        0x12 /* Common control 7 */
#घोषणा   COM7_SRST            0x80 /* Initiates प्रणाली reset. All रेजिस्टरs are
				     * set to factory शेष values after which
				     * the chip resumes normal operation */
#घोषणा   COM7_RES_UXGA        0x00 /* Resolution selectors क्रम UXGA */
#घोषणा   COM7_RES_SVGA        0x40 /* SVGA */
#घोषणा   COM7_RES_CIF         0x20 /* CIF */
#घोषणा   COM7_ZOOM_EN         0x04 /* Enable Zoom mode */
#घोषणा   COM7_COLOR_BAR_TEST  0x02 /* Enable Color Bar Test Pattern */
#घोषणा COM8        0x13 /* Common control 8 */
#घोषणा   COM8_DEF             0xC0
#घोषणा   COM8_BNDF_EN         0x20 /* Banding filter ON/OFF */
#घोषणा   COM8_AGC_EN          0x04 /* AGC Auto/Manual control selection */
#घोषणा   COM8_AEC_EN          0x01 /* Auto/Manual Exposure control */
#घोषणा COM9        0x14 /* Common control 9
			  * Automatic gain उच्चमानing - maximum AGC value [7:5]*/
#घोषणा   COM9_AGC_GAIN_2x     0x00 /* 000 :   2x */
#घोषणा   COM9_AGC_GAIN_4x     0x20 /* 001 :   4x */
#घोषणा   COM9_AGC_GAIN_8x     0x40 /* 010 :   8x */
#घोषणा   COM9_AGC_GAIN_16x    0x60 /* 011 :  16x */
#घोषणा   COM9_AGC_GAIN_32x    0x80 /* 100 :  32x */
#घोषणा   COM9_AGC_GAIN_64x    0xA0 /* 101 :  64x */
#घोषणा   COM9_AGC_GAIN_128x   0xC0 /* 110 : 128x */
#घोषणा COM10       0x15 /* Common control 10 */
#घोषणा   COM10_PCLK_HREF      0x20 /* PCLK output qualअगरied by HREF */
#घोषणा   COM10_PCLK_RISE      0x10 /* Data is updated at the rising edge of
				     * PCLK (user can latch data at the next
				     * falling edge of PCLK).
				     * 0 otherwise. */
#घोषणा   COM10_HREF_INV       0x08 /* Invert HREF polarity:
				     * HREF negative क्रम valid data*/
#घोषणा   COM10_VSINC_INV      0x02 /* Invert VSYNC polarity */
#घोषणा HSTART      0x17 /* Horizontal Winकरोw start MSB 8 bit */
#घोषणा HEND        0x18 /* Horizontal Winकरोw end MSB 8 bit */
#घोषणा VSTART      0x19 /* Vertical Winकरोw start MSB 8 bit */
#घोषणा VEND        0x1A /* Vertical Winकरोw end MSB 8 bit */
#घोषणा MIDH        0x1C /* Manufacturer ID byte - high */
#घोषणा MIDL        0x1D /* Manufacturer ID byte - low  */
#घोषणा AEW         0x24 /* AGC/AEC - Stable operating region (upper limit) */
#घोषणा AEB         0x25 /* AGC/AEC - Stable operating region (lower limit) */
#घोषणा VV          0x26 /* AGC/AEC Fast mode operating region */
#घोषणा   VV_HIGH_TH_SET(x)      VAL_SET(x, 0xF, 0, 4)
#घोषणा   VV_LOW_TH_SET(x)       VAL_SET(x, 0xF, 0, 0)
#घोषणा REG2A       0x2A /* Dummy pixel insert MSB */
#घोषणा FRARL       0x2B /* Dummy pixel insert LSB */
#घोषणा ADDVFL      0x2D /* LSB of insert dummy lines in Vertical direction */
#घोषणा ADDVFH      0x2E /* MSB of insert dummy lines in Vertical direction */
#घोषणा YAVG        0x2F /* Y/G Channel Average value */
#घोषणा REG32       0x32 /* Common Control 32 */
#घोषणा   REG32_PCLK_DIV_2    0x80 /* PCLK freq भागided by 2 */
#घोषणा   REG32_PCLK_DIV_4    0xC0 /* PCLK freq भागided by 4 */
#घोषणा ARCOM2      0x34 /* Zoom: Horizontal start poपूर्णांक */
#घोषणा REG45       0x45 /* Register 45 */
#घोषणा FLL         0x46 /* Frame Length Adjusपंचांगent LSBs */
#घोषणा FLH         0x47 /* Frame Length Adjusपंचांगent MSBs */
#घोषणा COM19       0x48 /* Zoom: Vertical start poपूर्णांक */
#घोषणा ZOOMS       0x49 /* Zoom: Vertical start poपूर्णांक */
#घोषणा COM22       0x4B /* Flash light control */
#घोषणा COM25       0x4E /* For Banding operations */
#घोषणा   COM25_50HZ_BANDING_AEC_MSBS_MASK      0xC0 /* 50Hz Bd. AEC 2 MSBs */
#घोषणा   COM25_60HZ_BANDING_AEC_MSBS_MASK      0x30 /* 60Hz Bd. AEC 2 MSBs */
#घोषणा   COM25_50HZ_BANDING_AEC_MSBS_SET(x)    VAL_SET(x, 0x3, 8, 6)
#घोषणा   COM25_60HZ_BANDING_AEC_MSBS_SET(x)    VAL_SET(x, 0x3, 8, 4)
#घोषणा BD50        0x4F /* 50Hz Banding AEC 8 LSBs */
#घोषणा   BD50_50HZ_BANDING_AEC_LSBS_SET(x)     VAL_SET(x, 0xFF, 0, 0)
#घोषणा BD60        0x50 /* 60Hz Banding AEC 8 LSBs */
#घोषणा   BD60_60HZ_BANDING_AEC_LSBS_SET(x)     VAL_SET(x, 0xFF, 0, 0)
#घोषणा REG5A       0x5A /* 50/60Hz Banding Maximum AEC Step */
#घोषणा   BD50_MAX_AEC_STEP_MASK         0xF0 /* 50Hz Banding Max. AEC Step */
#घोषणा   BD60_MAX_AEC_STEP_MASK         0x0F /* 60Hz Banding Max. AEC Step */
#घोषणा   BD50_MAX_AEC_STEP_SET(x)       VAL_SET((x - 1), 0x0F, 0, 4)
#घोषणा   BD60_MAX_AEC_STEP_SET(x)       VAL_SET((x - 1), 0x0F, 0, 0)
#घोषणा REG5D       0x5D /* AVGsel[7:0],   16-zone average weight option */
#घोषणा REG5E       0x5E /* AVGsel[15:8],  16-zone average weight option */
#घोषणा REG5F       0x5F /* AVGsel[23:16], 16-zone average weight option */
#घोषणा REG60       0x60 /* AVGsel[31:24], 16-zone average weight option */
#घोषणा HISTO_LOW   0x61 /* Histogram Algorithm Low Level */
#घोषणा HISTO_HIGH  0x62 /* Histogram Algorithm High Level */

/*
 * ID
 */
#घोषणा MANUFACTURER_ID	0x7FA2
#घोषणा PID_OV2640	0x2642
#घोषणा VERSION(pid, ver) ((pid << 8) | (ver & 0xFF))

/*
 * Struct
 */
काष्ठा regval_list अणु
	u8 reg_num;
	u8 value;
पूर्ण;

काष्ठा ov2640_win_size अणु
	अक्षर				*name;
	u32				width;
	u32				height;
	स्थिर काष्ठा regval_list	*regs;
पूर्ण;


काष्ठा ov2640_priv अणु
	काष्ठा v4l2_subdev		subdev;
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_pad pad;
#पूर्ण_अगर
	काष्ठा v4l2_ctrl_handler	hdl;
	u32	cfmt_code;
	काष्ठा clk			*clk;
	स्थिर काष्ठा ov2640_win_size	*win;

	काष्ठा gpio_desc *resetb_gpio;
	काष्ठा gpio_desc *pwdn_gpio;

	काष्ठा mutex lock; /* lock to protect streaming and घातer_count */
	bool streaming;
	पूर्णांक घातer_count;
पूर्ण;

/*
 * Registers settings
 */

#घोषणा ENDMARKER अणु 0xff, 0xff पूर्ण

अटल स्थिर काष्ठा regval_list ov2640_init_regs[] = अणु
	अणु BANK_SEL, BANK_SEL_DSP पूर्ण,
	अणु 0x2c,   0xff पूर्ण,
	अणु 0x2e,   0xdf पूर्ण,
	अणु BANK_SEL, BANK_SEL_SENS पूर्ण,
	अणु 0x3c,   0x32 पूर्ण,
	अणु CLKRC,  CLKRC_DIV_SET(1) पूर्ण,
	अणु COM2,   COM2_OCAP_Nx_SET(3) पूर्ण,
	अणु REG04,  REG04_DEF | REG04_HREF_EN पूर्ण,
	अणु COM8,   COM8_DEF | COM8_BNDF_EN | COM8_AGC_EN | COM8_AEC_EN पूर्ण,
	अणु COM9,   COM9_AGC_GAIN_8x | 0x08पूर्ण,
	अणु 0x2c,   0x0c पूर्ण,
	अणु 0x33,   0x78 पूर्ण,
	अणु 0x3a,   0x33 पूर्ण,
	अणु 0x3b,   0xfb पूर्ण,
	अणु 0x3e,   0x00 पूर्ण,
	अणु 0x43,   0x11 पूर्ण,
	अणु 0x16,   0x10 पूर्ण,
	अणु 0x39,   0x02 पूर्ण,
	अणु 0x35,   0x88 पूर्ण,
	अणु 0x22,   0x0a पूर्ण,
	अणु 0x37,   0x40 पूर्ण,
	अणु 0x23,   0x00 पूर्ण,
	अणु ARCOM2, 0xa0 पूर्ण,
	अणु 0x06,   0x02 पूर्ण,
	अणु 0x06,   0x88 पूर्ण,
	अणु 0x07,   0xc0 पूर्ण,
	अणु 0x0d,   0xb7 पूर्ण,
	अणु 0x0e,   0x01 पूर्ण,
	अणु 0x4c,   0x00 पूर्ण,
	अणु 0x4a,   0x81 पूर्ण,
	अणु 0x21,   0x99 पूर्ण,
	अणु AEW,    0x40 पूर्ण,
	अणु AEB,    0x38 पूर्ण,
	अणु VV,     VV_HIGH_TH_SET(0x08) | VV_LOW_TH_SET(0x02) पूर्ण,
	अणु 0x5c,   0x00 पूर्ण,
	अणु 0x63,   0x00 पूर्ण,
	अणु FLL,    0x22 पूर्ण,
	अणु COM3,   0x38 | COM3_BAND_AUTO पूर्ण,
	अणु REG5D,  0x55 पूर्ण,
	अणु REG5E,  0x7d पूर्ण,
	अणु REG5F,  0x7d पूर्ण,
	अणु REG60,  0x55 पूर्ण,
	अणु HISTO_LOW,   0x70 पूर्ण,
	अणु HISTO_HIGH,  0x80 पूर्ण,
	अणु 0x7c,   0x05 पूर्ण,
	अणु 0x20,   0x80 पूर्ण,
	अणु 0x28,   0x30 पूर्ण,
	अणु 0x6c,   0x00 पूर्ण,
	अणु 0x6d,   0x80 पूर्ण,
	अणु 0x6e,   0x00 पूर्ण,
	अणु 0x70,   0x02 पूर्ण,
	अणु 0x71,   0x94 पूर्ण,
	अणु 0x73,   0xc1 पूर्ण,
	अणु 0x3d,   0x34 पूर्ण,
	अणु COM7,   COM7_RES_UXGA | COM7_ZOOM_EN पूर्ण,
	अणु REG5A,  BD50_MAX_AEC_STEP_SET(6)
		   | BD60_MAX_AEC_STEP_SET(8) पूर्ण,		/* 0x57 */
	अणु COM25,  COM25_50HZ_BANDING_AEC_MSBS_SET(0x0bb)
		   | COM25_60HZ_BANDING_AEC_MSBS_SET(0x09c) पूर्ण,	/* 0x00 */
	अणु BD50,   BD50_50HZ_BANDING_AEC_LSBS_SET(0x0bb) पूर्ण,	/* 0xbb */
	अणु BD60,   BD60_60HZ_BANDING_AEC_LSBS_SET(0x09c) पूर्ण,	/* 0x9c */
	अणु BANK_SEL,  BANK_SEL_DSP पूर्ण,
	अणु 0xe5,   0x7f पूर्ण,
	अणु MC_BIST,  MC_BIST_RESET | MC_BIST_BOOT_ROM_SEL पूर्ण,
	अणु 0x41,   0x24 पूर्ण,
	अणु RESET,  RESET_JPEG | RESET_DVP पूर्ण,
	अणु 0x76,   0xff पूर्ण,
	अणु 0x33,   0xa0 पूर्ण,
	अणु 0x42,   0x20 पूर्ण,
	अणु 0x43,   0x18 पूर्ण,
	अणु 0x4c,   0x00 पूर्ण,
	अणु CTRL3,  CTRL3_BPC_EN | CTRL3_WPC_EN | 0x10 पूर्ण,
	अणु 0x88,   0x3f पूर्ण,
	अणु 0xd7,   0x03 पूर्ण,
	अणु 0xd9,   0x10 पूर्ण,
	अणु R_DVP_SP,  R_DVP_SP_AUTO_MODE | 0x2 पूर्ण,
	अणु 0xc8,   0x08 पूर्ण,
	अणु 0xc9,   0x80 पूर्ण,
	अणु BPADDR, 0x00 पूर्ण,
	अणु BPDATA, 0x00 पूर्ण,
	अणु BPADDR, 0x03 पूर्ण,
	अणु BPDATA, 0x48 पूर्ण,
	अणु BPDATA, 0x48 पूर्ण,
	अणु BPADDR, 0x08 पूर्ण,
	अणु BPDATA, 0x20 पूर्ण,
	अणु BPDATA, 0x10 पूर्ण,
	अणु BPDATA, 0x0e पूर्ण,
	अणु 0x90,   0x00 पूर्ण,
	अणु 0x91,   0x0e पूर्ण,
	अणु 0x91,   0x1a पूर्ण,
	अणु 0x91,   0x31 पूर्ण,
	अणु 0x91,   0x5a पूर्ण,
	अणु 0x91,   0x69 पूर्ण,
	अणु 0x91,   0x75 पूर्ण,
	अणु 0x91,   0x7e पूर्ण,
	अणु 0x91,   0x88 पूर्ण,
	अणु 0x91,   0x8f पूर्ण,
	अणु 0x91,   0x96 पूर्ण,
	अणु 0x91,   0xa3 पूर्ण,
	अणु 0x91,   0xaf पूर्ण,
	अणु 0x91,   0xc4 पूर्ण,
	अणु 0x91,   0xd7 पूर्ण,
	अणु 0x91,   0xe8 पूर्ण,
	अणु 0x91,   0x20 पूर्ण,
	अणु 0x92,   0x00 पूर्ण,
	अणु 0x93,   0x06 पूर्ण,
	अणु 0x93,   0xe3 पूर्ण,
	अणु 0x93,   0x03 पूर्ण,
	अणु 0x93,   0x03 पूर्ण,
	अणु 0x93,   0x00 पूर्ण,
	अणु 0x93,   0x02 पूर्ण,
	अणु 0x93,   0x00 पूर्ण,
	अणु 0x93,   0x00 पूर्ण,
	अणु 0x93,   0x00 पूर्ण,
	अणु 0x93,   0x00 पूर्ण,
	अणु 0x93,   0x00 पूर्ण,
	अणु 0x93,   0x00 पूर्ण,
	अणु 0x93,   0x00 पूर्ण,
	अणु 0x96,   0x00 पूर्ण,
	अणु 0x97,   0x08 पूर्ण,
	अणु 0x97,   0x19 पूर्ण,
	अणु 0x97,   0x02 पूर्ण,
	अणु 0x97,   0x0c पूर्ण,
	अणु 0x97,   0x24 पूर्ण,
	अणु 0x97,   0x30 पूर्ण,
	अणु 0x97,   0x28 पूर्ण,
	अणु 0x97,   0x26 पूर्ण,
	अणु 0x97,   0x02 पूर्ण,
	अणु 0x97,   0x98 पूर्ण,
	अणु 0x97,   0x80 पूर्ण,
	अणु 0x97,   0x00 पूर्ण,
	अणु 0x97,   0x00 पूर्ण,
	अणु 0xa4,   0x00 पूर्ण,
	अणु 0xa8,   0x00 पूर्ण,
	अणु 0xc5,   0x11 पूर्ण,
	अणु 0xc6,   0x51 पूर्ण,
	अणु 0xbf,   0x80 पूर्ण,
	अणु 0xc7,   0x10 पूर्ण,	/* simple AWB */
	अणु 0xb6,   0x66 पूर्ण,
	अणु 0xb8,   0xA5 पूर्ण,
	अणु 0xb7,   0x64 पूर्ण,
	अणु 0xb9,   0x7C पूर्ण,
	अणु 0xb3,   0xaf पूर्ण,
	अणु 0xb4,   0x97 पूर्ण,
	अणु 0xb5,   0xFF पूर्ण,
	अणु 0xb0,   0xC5 पूर्ण,
	अणु 0xb1,   0x94 पूर्ण,
	अणु 0xb2,   0x0f पूर्ण,
	अणु 0xc4,   0x5c पूर्ण,
	अणु 0xa6,   0x00 पूर्ण,
	अणु 0xa7,   0x20 पूर्ण,
	अणु 0xa7,   0xd8 पूर्ण,
	अणु 0xa7,   0x1b पूर्ण,
	अणु 0xa7,   0x31 पूर्ण,
	अणु 0xa7,   0x00 पूर्ण,
	अणु 0xa7,   0x18 पूर्ण,
	अणु 0xa7,   0x20 पूर्ण,
	अणु 0xa7,   0xd8 पूर्ण,
	अणु 0xa7,   0x19 पूर्ण,
	अणु 0xa7,   0x31 पूर्ण,
	अणु 0xa7,   0x00 पूर्ण,
	अणु 0xa7,   0x18 पूर्ण,
	अणु 0xa7,   0x20 पूर्ण,
	अणु 0xa7,   0xd8 पूर्ण,
	अणु 0xa7,   0x19 पूर्ण,
	अणु 0xa7,   0x31 पूर्ण,
	अणु 0xa7,   0x00 पूर्ण,
	अणु 0xa7,   0x18 पूर्ण,
	अणु 0x7f,   0x00 पूर्ण,
	अणु 0xe5,   0x1f पूर्ण,
	अणु 0xe1,   0x77 पूर्ण,
	अणु 0xdd,   0x7f पूर्ण,
	अणु CTRL0,  CTRL0_YUV422 | CTRL0_YUV_EN | CTRL0_RGB_EN पूर्ण,
	ENDMARKER,
पूर्ण;

/*
 * Register settings क्रम winकरोw size
 * The preamble, setup the पूर्णांकernal DSP to input an UXGA (1600x1200) image.
 * Then the dअगरferent zooming configurations will setup the output image size.
 */
अटल स्थिर काष्ठा regval_list ov2640_size_change_preamble_regs[] = अणु
	अणु BANK_SEL, BANK_SEL_DSP पूर्ण,
	अणु RESET, RESET_DVP पूर्ण,
	अणु SIZEL, SIZEL_HSIZE8_11_SET(UXGA_WIDTH) |
		 SIZEL_HSIZE8_SET(UXGA_WIDTH) |
		 SIZEL_VSIZE8_SET(UXGA_HEIGHT) पूर्ण,
	अणु HSIZE8, HSIZE8_SET(UXGA_WIDTH) पूर्ण,
	अणु VSIZE8, VSIZE8_SET(UXGA_HEIGHT) पूर्ण,
	अणु CTRL2, CTRL2_DCW_EN | CTRL2_SDE_EN |
		 CTRL2_UV_AVG_EN | CTRL2_CMX_EN | CTRL2_UV_ADJ_EN पूर्ण,
	अणु HSIZE, HSIZE_SET(UXGA_WIDTH) पूर्ण,
	अणु VSIZE, VSIZE_SET(UXGA_HEIGHT) पूर्ण,
	अणु XOFFL, XOFFL_SET(0) पूर्ण,
	अणु YOFFL, YOFFL_SET(0) पूर्ण,
	अणु VHYX, VHYX_HSIZE_SET(UXGA_WIDTH) | VHYX_VSIZE_SET(UXGA_HEIGHT) |
		VHYX_XOFF_SET(0) | VHYX_YOFF_SET(0)पूर्ण,
	अणु TEST, TEST_HSIZE_SET(UXGA_WIDTH) पूर्ण,
	ENDMARKER,
पूर्ण;

#घोषणा PER_SIZE_REG_SEQ(x, y, v_भाग, h_भाग, pclk_भाग)	\
	अणु CTRLI, CTRLI_LP_DP | CTRLI_V_DIV_SET(v_भाग) |	\
		 CTRLI_H_DIV_SET(h_भाग)पूर्ण,		\
	अणु ZMOW, ZMOW_OUTW_SET(x) पूर्ण,			\
	अणु ZMOH, ZMOH_OUTH_SET(y) पूर्ण,			\
	अणु ZMHH, ZMHH_OUTW_SET(x) | ZMHH_OUTH_SET(y) पूर्ण,	\
	अणु R_DVP_SP, pclk_भाग पूर्ण,				\
	अणु RESET, 0x00पूर्ण

अटल स्थिर काष्ठा regval_list ov2640_qcअगर_regs[] = अणु
	PER_SIZE_REG_SEQ(QCIF_WIDTH, QCIF_HEIGHT, 3, 3, 4),
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_qvga_regs[] = अणु
	PER_SIZE_REG_SEQ(QVGA_WIDTH, QVGA_HEIGHT, 2, 2, 4),
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_cअगर_regs[] = अणु
	PER_SIZE_REG_SEQ(CIF_WIDTH, CIF_HEIGHT, 2, 2, 8),
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_vga_regs[] = अणु
	PER_SIZE_REG_SEQ(VGA_WIDTH, VGA_HEIGHT, 0, 0, 2),
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_svga_regs[] = अणु
	PER_SIZE_REG_SEQ(SVGA_WIDTH, SVGA_HEIGHT, 1, 1, 2),
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_xga_regs[] = अणु
	PER_SIZE_REG_SEQ(XGA_WIDTH, XGA_HEIGHT, 0, 0, 2),
	अणु CTRLI,    0x00पूर्ण,
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_sxga_regs[] = अणु
	PER_SIZE_REG_SEQ(SXGA_WIDTH, SXGA_HEIGHT, 0, 0, 2),
	अणु CTRLI,    0x00पूर्ण,
	अणु R_DVP_SP, 2 | R_DVP_SP_AUTO_MODE पूर्ण,
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_uxga_regs[] = अणु
	PER_SIZE_REG_SEQ(UXGA_WIDTH, UXGA_HEIGHT, 0, 0, 0),
	अणु CTRLI,    0x00पूर्ण,
	अणु R_DVP_SP, 0 | R_DVP_SP_AUTO_MODE पूर्ण,
	ENDMARKER,
पूर्ण;

#घोषणा OV2640_SIZE(n, w, h, r) \
	अणु.name = n, .width = w , .height = h, .regs = r पूर्ण

अटल स्थिर काष्ठा ov2640_win_size ov2640_supported_win_sizes[] = अणु
	OV2640_SIZE("QCIF", QCIF_WIDTH, QCIF_HEIGHT, ov2640_qcअगर_regs),
	OV2640_SIZE("QVGA", QVGA_WIDTH, QVGA_HEIGHT, ov2640_qvga_regs),
	OV2640_SIZE("CIF", CIF_WIDTH, CIF_HEIGHT, ov2640_cअगर_regs),
	OV2640_SIZE("VGA", VGA_WIDTH, VGA_HEIGHT, ov2640_vga_regs),
	OV2640_SIZE("SVGA", SVGA_WIDTH, SVGA_HEIGHT, ov2640_svga_regs),
	OV2640_SIZE("XGA", XGA_WIDTH, XGA_HEIGHT, ov2640_xga_regs),
	OV2640_SIZE("SXGA", SXGA_WIDTH, SXGA_HEIGHT, ov2640_sxga_regs),
	OV2640_SIZE("UXGA", UXGA_WIDTH, UXGA_HEIGHT, ov2640_uxga_regs),
पूर्ण;

/*
 * Register settings क्रम pixel क्रमmats
 */
अटल स्थिर काष्ठा regval_list ov2640_क्रमmat_change_preamble_regs[] = अणु
	अणु BANK_SEL, BANK_SEL_DSP पूर्ण,
	अणु R_BYPASS, R_BYPASS_USE_DSP पूर्ण,
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_yuyv_regs[] = अणु
	अणु IMAGE_MODE, IMAGE_MODE_YUV422 पूर्ण,
	अणु 0xd7, 0x03 पूर्ण,
	अणु 0x33, 0xa0 पूर्ण,
	अणु 0xe5, 0x1f पूर्ण,
	अणु 0xe1, 0x67 पूर्ण,
	अणु RESET,  0x00 पूर्ण,
	अणु R_BYPASS, R_BYPASS_USE_DSP पूर्ण,
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_uyvy_regs[] = अणु
	अणु IMAGE_MODE, IMAGE_MODE_LBYTE_FIRST | IMAGE_MODE_YUV422 पूर्ण,
	अणु 0xd7, 0x01 पूर्ण,
	अणु 0x33, 0xa0 पूर्ण,
	अणु 0xe1, 0x67 पूर्ण,
	अणु RESET,  0x00 पूर्ण,
	अणु R_BYPASS, R_BYPASS_USE_DSP पूर्ण,
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_rgb565_be_regs[] = अणु
	अणु IMAGE_MODE, IMAGE_MODE_RGB565 पूर्ण,
	अणु 0xd7, 0x03 पूर्ण,
	अणु RESET,  0x00 पूर्ण,
	अणु R_BYPASS, R_BYPASS_USE_DSP पूर्ण,
	ENDMARKER,
पूर्ण;

अटल स्थिर काष्ठा regval_list ov2640_rgb565_le_regs[] = अणु
	अणु IMAGE_MODE, IMAGE_MODE_LBYTE_FIRST | IMAGE_MODE_RGB565 पूर्ण,
	अणु 0xd7, 0x03 पूर्ण,
	अणु RESET,  0x00 पूर्ण,
	अणु R_BYPASS, R_BYPASS_USE_DSP पूर्ण,
	ENDMARKER,
पूर्ण;

अटल u32 ov2640_codes[] = अणु
	MEDIA_BUS_FMT_YUYV8_2X8,
	MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_YVYU8_2X8,
	MEDIA_BUS_FMT_VYUY8_2X8,
	MEDIA_BUS_FMT_RGB565_2X8_BE,
	MEDIA_BUS_FMT_RGB565_2X8_LE,
पूर्ण;

/*
 * General functions
 */
अटल काष्ठा ov2640_priv *to_ov2640(स्थिर काष्ठा i2c_client *client)
अणु
	वापस container_of(i2c_get_clientdata(client), काष्ठा ov2640_priv,
			    subdev);
पूर्ण

अटल पूर्णांक ov2640_ग_लिखो_array(काष्ठा i2c_client *client,
			      स्थिर काष्ठा regval_list *vals)
अणु
	पूर्णांक ret;

	जबतक ((vals->reg_num != 0xff) || (vals->value != 0xff)) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client,
						vals->reg_num, vals->value);
		dev_vdbg(&client->dev, "array: 0x%02x, 0x%02x",
			 vals->reg_num, vals->value);

		अगर (ret < 0)
			वापस ret;
		vals++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ov2640_mask_set(काष्ठा i2c_client *client,
			   u8  reg, u8  mask, u8  set)
अणु
	s32 val = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (val < 0)
		वापस val;

	val &= ~mask;
	val |= set & mask;

	dev_vdbg(&client->dev, "masks: 0x%02x, 0x%02x", reg, val);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल पूर्णांक ov2640_reset(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	अटल स्थिर काष्ठा regval_list reset_seq[] = अणु
		अणुBANK_SEL, BANK_SEL_SENSपूर्ण,
		अणुCOM7, COM7_SRSTपूर्ण,
		ENDMARKER,
	पूर्ण;

	ret = ov2640_ग_लिखो_array(client, reset_seq);
	अगर (ret)
		जाओ err;

	msleep(5);
err:
	dev_dbg(&client->dev, "%s: (ret %d)", __func__, ret);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर ov2640_test_pattern_menu[] = अणु
	"Disabled",
	"Eight Vertical Colour Bars",
पूर्ण;

/*
 * functions
 */
अटल पूर्णांक ov2640_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd =
		&container_of(ctrl->handler, काष्ठा ov2640_priv, hdl)->subdev;
	काष्ठा i2c_client  *client = v4l2_get_subdevdata(sd);
	काष्ठा ov2640_priv *priv = to_ov2640(client);
	u8 val;
	पूर्णांक ret;

	/* v4l2_ctrl_lock() locks our own mutex */

	/*
	 * If the device is not घातered up by the host driver, करो not apply any
	 * controls to H/W at this समय. Instead the controls will be restored
	 * when the streaming is started.
	 */
	अगर (!priv->घातer_count)
		वापस 0;

	ret = i2c_smbus_ग_लिखो_byte_data(client, BANK_SEL, BANK_SEL_SENS);
	अगर (ret < 0)
		वापस ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		val = ctrl->val ? REG04_VFLIP_IMG | REG04_VREF_EN : 0x00;
		वापस ov2640_mask_set(client, REG04,
				       REG04_VFLIP_IMG | REG04_VREF_EN, val);
		/* NOTE: REG04_VREF_EN: 1 line shअगरt / even/odd line swap */
	हाल V4L2_CID_HFLIP:
		val = ctrl->val ? REG04_HFLIP_IMG : 0x00;
		वापस ov2640_mask_set(client, REG04, REG04_HFLIP_IMG, val);
	हाल V4L2_CID_TEST_PATTERN:
		val = ctrl->val ? COM7_COLOR_BAR_TEST : 0x00;
		वापस ov2640_mask_set(client, COM7, COM7_COLOR_BAR_TEST, val);
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ov2640_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	reg->size = 1;
	अगर (reg->reg > 0xff)
		वापस -EINVAL;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg->reg);
	अगर (ret < 0)
		वापस ret;

	reg->val = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2640_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg > 0xff ||
	    reg->val > 0xff)
		वापस -EINVAL;

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg->reg, reg->val);
पूर्ण
#पूर्ण_अगर

अटल व्योम ov2640_set_घातer(काष्ठा ov2640_priv *priv, पूर्णांक on)
अणु
#अगर_घोषित CONFIG_GPIOLIB
	अगर (priv->pwdn_gpio)
		gpiod_direction_output(priv->pwdn_gpio, !on);
	अगर (on && priv->resetb_gpio) अणु
		/* Active the resetb pin to perक्रमm a reset pulse */
		gpiod_direction_output(priv->resetb_gpio, 1);
		usleep_range(3000, 5000);
		gpiod_set_value(priv->resetb_gpio, 0);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ov2640_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov2640_priv *priv = to_ov2640(client);

	mutex_lock(&priv->lock);

	/*
	 * If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (priv->घातer_count == !on)
		ov2640_set_घातer(priv, on);
	priv->घातer_count += on ? 1 : -1;
	WARN_ON(priv->घातer_count < 0);
	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

/* Select the nearest higher resolution क्रम capture */
अटल स्थिर काष्ठा ov2640_win_size *ov2640_select_win(u32 width, u32 height)
अणु
	पूर्णांक i, शेष_size = ARRAY_SIZE(ov2640_supported_win_sizes) - 1;

	क्रम (i = 0; i < ARRAY_SIZE(ov2640_supported_win_sizes); i++) अणु
		अगर (ov2640_supported_win_sizes[i].width  >= width &&
		    ov2640_supported_win_sizes[i].height >= height)
			वापस &ov2640_supported_win_sizes[i];
	पूर्ण

	वापस &ov2640_supported_win_sizes[शेष_size];
पूर्ण

अटल पूर्णांक ov2640_set_params(काष्ठा i2c_client *client,
			     स्थिर काष्ठा ov2640_win_size *win, u32 code)
अणु
	स्थिर काष्ठा regval_list *selected_cfmt_regs;
	u8 val;
	पूर्णांक ret;

	चयन (code) अणु
	हाल MEDIA_BUS_FMT_RGB565_2X8_BE:
		dev_dbg(&client->dev, "%s: Selected cfmt RGB565 BE", __func__);
		selected_cfmt_regs = ov2640_rgb565_be_regs;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
		dev_dbg(&client->dev, "%s: Selected cfmt RGB565 LE", __func__);
		selected_cfmt_regs = ov2640_rgb565_le_regs;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		dev_dbg(&client->dev, "%s: Selected cfmt YUYV (YUV422)", __func__);
		selected_cfmt_regs = ov2640_yuyv_regs;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
	शेष:
		dev_dbg(&client->dev, "%s: Selected cfmt UYVY", __func__);
		selected_cfmt_regs = ov2640_uyvy_regs;
		अवरोध;
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
		dev_dbg(&client->dev, "%s: Selected cfmt YVYU", __func__);
		selected_cfmt_regs = ov2640_yuyv_regs;
		अवरोध;
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
		dev_dbg(&client->dev, "%s: Selected cfmt VYUY", __func__);
		selected_cfmt_regs = ov2640_uyvy_regs;
		अवरोध;
	पूर्ण

	/* reset hardware */
	ov2640_reset(client);

	/* initialize the sensor with शेष data */
	dev_dbg(&client->dev, "%s: Init default", __func__);
	ret = ov2640_ग_लिखो_array(client, ov2640_init_regs);
	अगर (ret < 0)
		जाओ err;

	/* select preamble */
	dev_dbg(&client->dev, "%s: Set size to %s", __func__, win->name);
	ret = ov2640_ग_लिखो_array(client, ov2640_size_change_preamble_regs);
	अगर (ret < 0)
		जाओ err;

	/* set size win */
	ret = ov2640_ग_लिखो_array(client, win->regs);
	अगर (ret < 0)
		जाओ err;

	/* cfmt preamble */
	dev_dbg(&client->dev, "%s: Set cfmt", __func__);
	ret = ov2640_ग_लिखो_array(client, ov2640_क्रमmat_change_preamble_regs);
	अगर (ret < 0)
		जाओ err;

	/* set cfmt */
	ret = ov2640_ग_लिखो_array(client, selected_cfmt_regs);
	अगर (ret < 0)
		जाओ err;
	val = (code == MEDIA_BUS_FMT_YVYU8_2X8)
	      || (code == MEDIA_BUS_FMT_VYUY8_2X8) ? CTRL0_VFIRST : 0x00;
	ret = ov2640_mask_set(client, CTRL0, CTRL0_VFIRST, val);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	dev_err(&client->dev, "%s: Error %d", __func__, ret);
	ov2640_reset(client);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2640_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client  *client = v4l2_get_subdevdata(sd);
	काष्ठा ov2640_priv *priv = to_ov2640(client);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		क्रमmat->क्रमmat = *mf;
		वापस 0;
#अन्यथा
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण

	mf->width	= priv->win->width;
	mf->height	= priv->win->height;
	mf->code	= priv->cfmt_code;
	mf->colorspace	= V4L2_COLORSPACE_SRGB;
	mf->field	= V4L2_FIELD_NONE;
	mf->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	mf->quantization = V4L2_QUANTIZATION_DEFAULT;
	mf->xfer_func	= V4L2_XFER_FUNC_DEFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2640_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov2640_priv *priv = to_ov2640(client);
	स्थिर काष्ठा ov2640_win_size *win;
	पूर्णांक ret = 0;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	/* select suitable win */
	win = ov2640_select_win(mf->width, mf->height);
	mf->width	= win->width;
	mf->height	= win->height;

	mf->field	= V4L2_FIELD_NONE;
	mf->colorspace	= V4L2_COLORSPACE_SRGB;
	mf->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	mf->quantization = V4L2_QUANTIZATION_DEFAULT;
	mf->xfer_func	= V4L2_XFER_FUNC_DEFAULT;

	चयन (mf->code) अणु
	हाल MEDIA_BUS_FMT_RGB565_2X8_BE:
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
		अवरोध;
	शेष:
		mf->code = MEDIA_BUS_FMT_UYVY8_2X8;
		अवरोध;
	पूर्ण

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		काष्ठा ov2640_priv *priv = to_ov2640(client);

		अगर (priv->streaming) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
		/* select win */
		priv->win = win;
		/* select क्रमmat */
		priv->cfmt_code = mf->code;
	पूर्ण अन्यथा अणु
		cfg->try_fmt = *mf;
	पूर्ण
out:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2640_init_cfg(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg)
अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	काष्ठा v4l2_mbus_framefmt *try_fmt =
		v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
	स्थिर काष्ठा ov2640_win_size *win =
		ov2640_select_win(SVGA_WIDTH, SVGA_HEIGHT);

	try_fmt->width = win->width;
	try_fmt->height = win->height;
	try_fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	try_fmt->colorspace = V4L2_COLORSPACE_SRGB;
	try_fmt->field = V4L2_FIELD_NONE;
	try_fmt->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	try_fmt->quantization = V4L2_QUANTIZATION_DEFAULT;
	try_fmt->xfer_func = V4L2_XFER_FUNC_DEFAULT;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक ov2640_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= ARRAY_SIZE(ov2640_codes))
		वापस -EINVAL;

	code->code = ov2640_codes[code->index];
	वापस 0;
पूर्ण

अटल पूर्णांक ov2640_get_selection(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_selection *sel)
अणु
	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = UXGA_WIDTH;
		sel->r.height = UXGA_HEIGHT;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ov2640_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov2640_priv *priv = to_ov2640(client);
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);
	अगर (priv->streaming == !on) अणु
		अगर (on) अणु
			ret = ov2640_set_params(client, priv->win,
						priv->cfmt_code);
			अगर (!ret)
				ret = __v4l2_ctrl_handler_setup(&priv->hdl);
		पूर्ण
	पूर्ण
	अगर (!ret)
		priv->streaming = on;
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2640_video_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov2640_priv *priv = to_ov2640(client);
	u8 pid, ver, midh, midl;
	स्थिर अक्षर *devname;
	पूर्णांक ret;

	ret = ov2640_s_घातer(&priv->subdev, 1);
	अगर (ret < 0)
		वापस ret;

	/*
	 * check and show product ID and manufacturer ID
	 */
	i2c_smbus_ग_लिखो_byte_data(client, BANK_SEL, BANK_SEL_SENS);
	pid  = i2c_smbus_पढ़ो_byte_data(client, PID);
	ver  = i2c_smbus_पढ़ो_byte_data(client, VER);
	midh = i2c_smbus_पढ़ो_byte_data(client, MIDH);
	midl = i2c_smbus_पढ़ो_byte_data(client, MIDL);

	चयन (VERSION(pid, ver)) अणु
	हाल PID_OV2640:
		devname     = "ov2640";
		अवरोध;
	शेष:
		dev_err(&client->dev,
			"Product ID error %x:%x\n", pid, ver);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	dev_info(&client->dev,
		 "%s Product ID %0x:%0x Manufacturer ID %x:%x\n",
		 devname, pid, ver, midh, midl);

करोne:
	ov2640_s_घातer(&priv->subdev, 0);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov2640_ctrl_ops = अणु
	.s_ctrl = ov2640_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov2640_subdev_core_ops = अणु
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर	= ov2640_g_रेजिस्टर,
	.s_रेजिस्टर	= ov2640_s_रेजिस्टर,
#पूर्ण_अगर
	.s_घातer	= ov2640_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov2640_subdev_pad_ops = अणु
	.init_cfg	= ov2640_init_cfg,
	.क्रमागत_mbus_code = ov2640_क्रमागत_mbus_code,
	.get_selection	= ov2640_get_selection,
	.get_fmt	= ov2640_get_fmt,
	.set_fmt	= ov2640_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov2640_subdev_video_ops = अणु
	.s_stream = ov2640_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov2640_subdev_ops = अणु
	.core	= &ov2640_subdev_core_ops,
	.pad	= &ov2640_subdev_pad_ops,
	.video	= &ov2640_subdev_video_ops,
पूर्ण;

अटल पूर्णांक ov2640_probe_dt(काष्ठा i2c_client *client,
		काष्ठा ov2640_priv *priv)
अणु
	पूर्णांक ret;

	/* Request the reset GPIO deनिश्चितed */
	priv->resetb_gpio = devm_gpiod_get_optional(&client->dev, "resetb",
			GPIOD_OUT_LOW);

	अगर (!priv->resetb_gpio)
		dev_dbg(&client->dev, "resetb gpio is not assigned!\n");

	ret = PTR_ERR_OR_ZERO(priv->resetb_gpio);
	अगर (ret && ret != -ENOSYS) अणु
		dev_dbg(&client->dev,
			"Error %d while getting resetb gpio\n", ret);
		वापस ret;
	पूर्ण

	/* Request the घातer करोwn GPIO निश्चितed */
	priv->pwdn_gpio = devm_gpiod_get_optional(&client->dev, "pwdn",
			GPIOD_OUT_HIGH);

	अगर (!priv->pwdn_gpio)
		dev_dbg(&client->dev, "pwdn gpio is not assigned!\n");

	ret = PTR_ERR_OR_ZERO(priv->pwdn_gpio);
	अगर (ret && ret != -ENOSYS) अणु
		dev_dbg(&client->dev,
			"Error %d while getting pwdn gpio\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * i2c_driver functions
 */
अटल पूर्णांक ov2640_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov2640_priv	*priv;
	काष्ठा i2c_adapter	*adapter = client->adapter;
	पूर्णांक			ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&adapter->dev,
			"OV2640: I2C-Adapter doesn't support SMBUS\n");
		वापस -EIO;
	पूर्ण

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (client->dev.of_node) अणु
		priv->clk = devm_clk_get(&client->dev, "xvclk");
		अगर (IS_ERR(priv->clk))
			वापस PTR_ERR(priv->clk);
		ret = clk_prepare_enable(priv->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = ov2640_probe_dt(client, priv);
	अगर (ret)
		जाओ err_clk;

	priv->win = ov2640_select_win(SVGA_WIDTH, SVGA_HEIGHT);
	priv->cfmt_code = MEDIA_BUS_FMT_UYVY8_2X8;

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov2640_subdev_ops);
	priv->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
			      V4L2_SUBDEV_FL_HAS_EVENTS;
	mutex_init(&priv->lock);
	v4l2_ctrl_handler_init(&priv->hdl, 3);
	priv->hdl.lock = &priv->lock;
	v4l2_ctrl_new_std(&priv->hdl, &ov2640_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ov2640_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std_menu_items(&priv->hdl, &ov2640_ctrl_ops,
			V4L2_CID_TEST_PATTERN,
			ARRAY_SIZE(ov2640_test_pattern_menu) - 1, 0, 0,
			ov2640_test_pattern_menu);
	priv->subdev.ctrl_handler = &priv->hdl;
	अगर (priv->hdl.error) अणु
		ret = priv->hdl.error;
		जाओ err_hdl;
	पूर्ण
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	priv->pad.flags = MEDIA_PAD_FL_SOURCE;
	priv->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&priv->subdev.entity, 1, &priv->pad);
	अगर (ret < 0)
		जाओ err_hdl;
#पूर्ण_अगर

	ret = ov2640_video_probe(client);
	अगर (ret < 0)
		जाओ err_videoprobe;

	ret = v4l2_async_रेजिस्टर_subdev(&priv->subdev);
	अगर (ret < 0)
		जाओ err_videoprobe;

	dev_info(&adapter->dev, "OV2640 Probed\n");

	वापस 0;

err_videoprobe:
	media_entity_cleanup(&priv->subdev.entity);
err_hdl:
	v4l2_ctrl_handler_मुक्त(&priv->hdl);
	mutex_destroy(&priv->lock);
err_clk:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ov2640_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ov2640_priv       *priv = to_ov2640(client);

	v4l2_async_unरेजिस्टर_subdev(&priv->subdev);
	v4l2_ctrl_handler_मुक्त(&priv->hdl);
	mutex_destroy(&priv->lock);
	media_entity_cleanup(&priv->subdev.entity);
	v4l2_device_unरेजिस्टर_subdev(&priv->subdev);
	clk_disable_unprepare(priv->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov2640_id[] = अणु
	अणु "ov2640", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov2640_id);

अटल स्थिर काष्ठा of_device_id ov2640_of_match[] = अणु
	अणु.compatible = "ovti,ov2640", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ov2640_of_match);

अटल काष्ठा i2c_driver ov2640_i2c_driver = अणु
	.driver = अणु
		.name = "ov2640",
		.of_match_table = of_match_ptr(ov2640_of_match),
	पूर्ण,
	.probe_new = ov2640_probe,
	.हटाओ   = ov2640_हटाओ,
	.id_table = ov2640_id,
पूर्ण;

module_i2c_driver(ov2640_i2c_driver);

MODULE_DESCRIPTION("Driver for Omni Vision 2640 sensor");
MODULE_AUTHOR("Alberto Panizzo");
MODULE_LICENSE("GPL v2");
