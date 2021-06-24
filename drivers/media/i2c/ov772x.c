<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ov772x Camera Driver
 *
 * Copyright (C) 2017 Jacopo Mondi <jacopo+renesas@jmondi.org>
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 * Based on ov7670 and soc_camera_platक्रमm driver,
 *
 * Copyright 2006-7 Jonathan Corbet <corbet@lwn.net>
 * Copyright (C) 2008 Magnus Damm
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/videodev2.h>

#समावेश <media/i2c/ov772x.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-subdev.h>

/*
 * रेजिस्टर offset
 */
#घोषणा GAIN        0x00 /* AGC - Gain control gain setting */
#घोषणा BLUE        0x01 /* AWB - Blue channel gain setting */
#घोषणा RED         0x02 /* AWB - Red   channel gain setting */
#घोषणा GREEN       0x03 /* AWB - Green channel gain setting */
#घोषणा COM1        0x04 /* Common control 1 */
#घोषणा BAVG        0x05 /* U/B Average Level */
#घोषणा GAVG        0x06 /* Y/Gb Average Level */
#घोषणा RAVG        0x07 /* V/R Average Level */
#घोषणा AECH        0x08 /* Exposure Value - AEC MSBs */
#घोषणा COM2        0x09 /* Common control 2 */
#घोषणा PID         0x0A /* Product ID Number MSB */
#घोषणा VER         0x0B /* Product ID Number LSB */
#घोषणा COM3        0x0C /* Common control 3 */
#घोषणा COM4        0x0D /* Common control 4 */
#घोषणा COM5        0x0E /* Common control 5 */
#घोषणा COM6        0x0F /* Common control 6 */
#घोषणा AEC         0x10 /* Exposure Value */
#घोषणा CLKRC       0x11 /* Internal घड़ी */
#घोषणा COM7        0x12 /* Common control 7 */
#घोषणा COM8        0x13 /* Common control 8 */
#घोषणा COM9        0x14 /* Common control 9 */
#घोषणा COM10       0x15 /* Common control 10 */
#घोषणा REG16       0x16 /* Register 16 */
#घोषणा HSTART      0x17 /* Horizontal sensor size */
#घोषणा HSIZE       0x18 /* Horizontal frame (HREF column) end high 8-bit */
#घोषणा VSTART      0x19 /* Vertical frame (row) start high 8-bit */
#घोषणा VSIZE       0x1A /* Vertical sensor size */
#घोषणा PSHFT       0x1B /* Data क्रमmat - pixel delay select */
#घोषणा MIDH        0x1C /* Manufacturer ID byte - high */
#घोषणा MIDL        0x1D /* Manufacturer ID byte - low  */
#घोषणा LAEC        0x1F /* Fine AEC value */
#घोषणा COM11       0x20 /* Common control 11 */
#घोषणा BDBASE      0x22 /* Banding filter Minimum AEC value */
#घोषणा DBSTEP      0x23 /* Banding filter Maximum Setp */
#घोषणा AEW         0x24 /* AGC/AEC - Stable operating region (upper limit) */
#घोषणा AEB         0x25 /* AGC/AEC - Stable operating region (lower limit) */
#घोषणा VPT         0x26 /* AGC/AEC Fast mode operating region */
#घोषणा REG28       0x28 /* Register 28 */
#घोषणा HOUTSIZE    0x29 /* Horizontal data output size MSBs */
#घोषणा EXHCH       0x2A /* Dummy pixel insert MSB */
#घोषणा EXHCL       0x2B /* Dummy pixel insert LSB */
#घोषणा VOUTSIZE    0x2C /* Vertical data output size MSBs */
#घोषणा ADVFL       0x2D /* LSB of insert dummy lines in Vertical direction */
#घोषणा ADVFH       0x2E /* MSG of insert dummy lines in Vertical direction */
#घोषणा YAVE        0x2F /* Y/G Channel Average value */
#घोषणा LUMHTH      0x30 /* Histogram AEC/AGC Luminance high level threshold */
#घोषणा LUMLTH      0x31 /* Histogram AEC/AGC Luminance low  level threshold */
#घोषणा HREF        0x32 /* Image start and size control */
#घोषणा DM_LNL      0x33 /* Dummy line low  8 bits */
#घोषणा DM_LNH      0x34 /* Dummy line high 8 bits */
#घोषणा ADOFF_B     0x35 /* AD offset compensation value क्रम B  channel */
#घोषणा ADOFF_R     0x36 /* AD offset compensation value क्रम R  channel */
#घोषणा ADOFF_GB    0x37 /* AD offset compensation value क्रम Gb channel */
#घोषणा ADOFF_GR    0x38 /* AD offset compensation value क्रम Gr channel */
#घोषणा OFF_B       0x39 /* Analog process B  channel offset value */
#घोषणा OFF_R       0x3A /* Analog process R  channel offset value */
#घोषणा OFF_GB      0x3B /* Analog process Gb channel offset value */
#घोषणा OFF_GR      0x3C /* Analog process Gr channel offset value */
#घोषणा COM12       0x3D /* Common control 12 */
#घोषणा COM13       0x3E /* Common control 13 */
#घोषणा COM14       0x3F /* Common control 14 */
#घोषणा COM15       0x40 /* Common control 15*/
#घोषणा COM16       0x41 /* Common control 16 */
#घोषणा TGT_B       0x42 /* BLC blue channel target value */
#घोषणा TGT_R       0x43 /* BLC red  channel target value */
#घोषणा TGT_GB      0x44 /* BLC Gb   channel target value */
#घोषणा TGT_GR      0x45 /* BLC Gr   channel target value */
/* क्रम ov7720 */
#घोषणा LCC0        0x46 /* Lens correction control 0 */
#घोषणा LCC1        0x47 /* Lens correction option 1 - X coordinate */
#घोषणा LCC2        0x48 /* Lens correction option 2 - Y coordinate */
#घोषणा LCC3        0x49 /* Lens correction option 3 */
#घोषणा LCC4        0x4A /* Lens correction option 4 - radius of the circular */
#घोषणा LCC5        0x4B /* Lens correction option 5 */
#घोषणा LCC6        0x4C /* Lens correction option 6 */
/* क्रम ov7725 */
#घोषणा LC_CTR      0x46 /* Lens correction control */
#घोषणा LC_XC       0x47 /* X coordinate of lens correction center relative */
#घोषणा LC_YC       0x48 /* Y coordinate of lens correction center relative */
#घोषणा LC_COEF     0x49 /* Lens correction coefficient */
#घोषणा LC_RADI     0x4A /* Lens correction radius */
#घोषणा LC_COEFB    0x4B /* Lens B channel compensation coefficient */
#घोषणा LC_COEFR    0x4C /* Lens R channel compensation coefficient */

#घोषणा FIXGAIN     0x4D /* Analog fix gain amplअगरer */
#घोषणा AREF0       0x4E /* Sensor reference control */
#घोषणा AREF1       0x4F /* Sensor reference current control */
#घोषणा AREF2       0x50 /* Analog reference control */
#घोषणा AREF3       0x51 /* ADC    reference control */
#घोषणा AREF4       0x52 /* ADC    reference control */
#घोषणा AREF5       0x53 /* ADC    reference control */
#घोषणा AREF6       0x54 /* Analog reference control */
#घोषणा AREF7       0x55 /* Analog reference control */
#घोषणा UFIX        0x60 /* U channel fixed value output */
#घोषणा VFIX        0x61 /* V channel fixed value output */
#घोषणा AWBB_BLK    0x62 /* AWB option क्रम advanced AWB */
#घोषणा AWB_CTRL0   0x63 /* AWB control byte 0 */
#घोषणा DSP_CTRL1   0x64 /* DSP control byte 1 */
#घोषणा DSP_CTRL2   0x65 /* DSP control byte 2 */
#घोषणा DSP_CTRL3   0x66 /* DSP control byte 3 */
#घोषणा DSP_CTRL4   0x67 /* DSP control byte 4 */
#घोषणा AWB_BIAS    0x68 /* AWB BLC level clip */
#घोषणा AWB_CTRL1   0x69 /* AWB control  1 */
#घोषणा AWB_CTRL2   0x6A /* AWB control  2 */
#घोषणा AWB_CTRL3   0x6B /* AWB control  3 */
#घोषणा AWB_CTRL4   0x6C /* AWB control  4 */
#घोषणा AWB_CTRL5   0x6D /* AWB control  5 */
#घोषणा AWB_CTRL6   0x6E /* AWB control  6 */
#घोषणा AWB_CTRL7   0x6F /* AWB control  7 */
#घोषणा AWB_CTRL8   0x70 /* AWB control  8 */
#घोषणा AWB_CTRL9   0x71 /* AWB control  9 */
#घोषणा AWB_CTRL10  0x72 /* AWB control 10 */
#घोषणा AWB_CTRL11  0x73 /* AWB control 11 */
#घोषणा AWB_CTRL12  0x74 /* AWB control 12 */
#घोषणा AWB_CTRL13  0x75 /* AWB control 13 */
#घोषणा AWB_CTRL14  0x76 /* AWB control 14 */
#घोषणा AWB_CTRL15  0x77 /* AWB control 15 */
#घोषणा AWB_CTRL16  0x78 /* AWB control 16 */
#घोषणा AWB_CTRL17  0x79 /* AWB control 17 */
#घोषणा AWB_CTRL18  0x7A /* AWB control 18 */
#घोषणा AWB_CTRL19  0x7B /* AWB control 19 */
#घोषणा AWB_CTRL20  0x7C /* AWB control 20 */
#घोषणा AWB_CTRL21  0x7D /* AWB control 21 */
#घोषणा GAM1        0x7E /* Gamma Curve  1st segment input end poपूर्णांक */
#घोषणा GAM2        0x7F /* Gamma Curve  2nd segment input end poपूर्णांक */
#घोषणा GAM3        0x80 /* Gamma Curve  3rd segment input end poपूर्णांक */
#घोषणा GAM4        0x81 /* Gamma Curve  4th segment input end poपूर्णांक */
#घोषणा GAM5        0x82 /* Gamma Curve  5th segment input end poपूर्णांक */
#घोषणा GAM6        0x83 /* Gamma Curve  6th segment input end poपूर्णांक */
#घोषणा GAM7        0x84 /* Gamma Curve  7th segment input end poपूर्णांक */
#घोषणा GAM8        0x85 /* Gamma Curve  8th segment input end poपूर्णांक */
#घोषणा GAM9        0x86 /* Gamma Curve  9th segment input end poपूर्णांक */
#घोषणा GAM10       0x87 /* Gamma Curve 10th segment input end poपूर्णांक */
#घोषणा GAM11       0x88 /* Gamma Curve 11th segment input end poपूर्णांक */
#घोषणा GAM12       0x89 /* Gamma Curve 12th segment input end poपूर्णांक */
#घोषणा GAM13       0x8A /* Gamma Curve 13th segment input end poपूर्णांक */
#घोषणा GAM14       0x8B /* Gamma Curve 14th segment input end poपूर्णांक */
#घोषणा GAM15       0x8C /* Gamma Curve 15th segment input end poपूर्णांक */
#घोषणा SLOP        0x8D /* Gamma curve highest segment slope */
#घोषणा DNSTH       0x8E /* De-noise threshold */
#घोषणा EDGE_STRNGT 0x8F /* Edge strength  control when manual mode */
#घोषणा EDGE_TRSHLD 0x90 /* Edge threshold control when manual mode */
#घोषणा DNSOFF      0x91 /* Auto De-noise threshold control */
#घोषणा EDGE_UPPER  0x92 /* Edge strength upper limit when Auto mode */
#घोषणा EDGE_LOWER  0x93 /* Edge strength lower limit when Auto mode */
#घोषणा MTX1        0x94 /* Matrix coefficient 1 */
#घोषणा MTX2        0x95 /* Matrix coefficient 2 */
#घोषणा MTX3        0x96 /* Matrix coefficient 3 */
#घोषणा MTX4        0x97 /* Matrix coefficient 4 */
#घोषणा MTX5        0x98 /* Matrix coefficient 5 */
#घोषणा MTX6        0x99 /* Matrix coefficient 6 */
#घोषणा MTX_CTRL    0x9A /* Matrix control */
#घोषणा BRIGHT      0x9B /* Brightness control */
#घोषणा CNTRST      0x9C /* Contrast contrast */
#घोषणा CNTRST_CTRL 0x9D /* Contrast contrast center */
#घोषणा UVAD_J0     0x9E /* Auto UV adjust contrast 0 */
#घोषणा UVAD_J1     0x9F /* Auto UV adjust contrast 1 */
#घोषणा SCAL0       0xA0 /* Scaling control 0 */
#घोषणा SCAL1       0xA1 /* Scaling control 1 */
#घोषणा SCAL2       0xA2 /* Scaling control 2 */
#घोषणा FIFODLYM    0xA3 /* FIFO manual mode delay control */
#घोषणा FIFODLYA    0xA4 /* FIFO स्वतः   mode delay control */
#घोषणा SDE         0xA6 /* Special digital effect control */
#घोषणा USAT        0xA7 /* U component saturation control */
#घोषणा VSAT        0xA8 /* V component saturation control */
/* क्रम ov7720 */
#घोषणा HUE0        0xA9 /* Hue control 0 */
#घोषणा HUE1        0xAA /* Hue control 1 */
/* क्रम ov7725 */
#घोषणा HUECOS      0xA9 /* Cosine value */
#घोषणा HUESIN      0xAA /* Sine value */

#घोषणा SIGN        0xAB /* Sign bit क्रम Hue and contrast */
#घोषणा DSPAUTO     0xAC /* DSP स्वतः function ON/OFF control */

/*
 * रेजिस्टर detail
 */

/* COM2 */
#घोषणा SOFT_SLEEP_MODE 0x10	/* Soft sleep mode */
				/* Output drive capability */
#घोषणा OCAP_1x         0x00	/* 1x */
#घोषणा OCAP_2x         0x01	/* 2x */
#घोषणा OCAP_3x         0x02	/* 3x */
#घोषणा OCAP_4x         0x03	/* 4x */

/* COM3 */
#घोषणा SWAP_MASK       (SWAP_RGB | SWAP_YUV | SWAP_ML)
#घोषणा IMG_MASK        (VFLIP_IMG | HFLIP_IMG | SCOLOR_TEST)

#घोषणा VFLIP_IMG       0x80	/* Vertical flip image ON/OFF selection */
#घोषणा HFLIP_IMG       0x40	/* Horizontal mirror image ON/OFF selection */
#घोषणा SWAP_RGB        0x20	/* Swap B/R  output sequence in RGB mode */
#घोषणा SWAP_YUV        0x10	/* Swap Y/UV output sequence in YUV mode */
#घोषणा SWAP_ML         0x08	/* Swap output MSB/LSB */
				/* Tri-state option क्रम output घड़ी */
#घोषणा NOTRI_CLOCK     0x04	/*   0: Tri-state    at this period */
				/*   1: No tri-state at this period */
				/* Tri-state option क्रम output data */
#घोषणा NOTRI_DATA      0x02	/*   0: Tri-state    at this period */
				/*   1: No tri-state at this period */
#घोषणा SCOLOR_TEST     0x01	/* Sensor color bar test pattern */

/* COM4 */
				/* PLL frequency control */
#घोषणा PLL_BYPASS      0x00	/*  00: Bypass PLL */
#घोषणा PLL_4x          0x40	/*  01: PLL 4x */
#घोषणा PLL_6x          0x80	/*  10: PLL 6x */
#घोषणा PLL_8x          0xc0	/*  11: PLL 8x */
				/* AEC evaluate winकरोw */
#घोषणा AEC_FULL        0x00	/*  00: Full winकरोw */
#घोषणा AEC_1p2         0x10	/*  01: 1/2  winकरोw */
#घोषणा AEC_1p4         0x20	/*  10: 1/4  winकरोw */
#घोषणा AEC_2p3         0x30	/*  11: Low 2/3 winकरोw */
#घोषणा COM4_RESERVED   0x01	/* Reserved bit */

/* COM5 */
#घोषणा AFR_ON_OFF      0x80	/* Auto frame rate control ON/OFF selection */
#घोषणा AFR_SPPED       0x40	/* Auto frame rate control speed selection */
				/* Auto frame rate max rate control */
#घोषणा AFR_NO_RATE     0x00	/*     No  reduction of frame rate */
#घोषणा AFR_1p2         0x10	/*     Max reduction to 1/2 frame rate */
#घोषणा AFR_1p4         0x20	/*     Max reduction to 1/4 frame rate */
#घोषणा AFR_1p8         0x30	/* Max reduction to 1/8 frame rate */
				/* Auto frame rate active poपूर्णांक control */
#घोषणा AF_2x           0x00	/*     Add frame when AGC reaches  2x gain */
#घोषणा AF_4x           0x04	/*     Add frame when AGC reaches  4x gain */
#घोषणा AF_8x           0x08	/*     Add frame when AGC reaches  8x gain */
#घोषणा AF_16x          0x0c	/* Add frame when AGC reaches 16x gain */
				/* AEC max step control */
#घोषणा AEC_NO_LIMIT    0x01	/*   0 : AEC incease step has limit */
				/*   1 : No limit to AEC increase step */
/* CLKRC */
				/* Input घड़ी भागider रेजिस्टर */
#घोषणा CLKRC_RESERVED  0x80	/* Reserved bit */
#घोषणा CLKRC_DIV(n)    ((n) - 1)

/* COM7 */
				/* SCCB Register Reset */
#घोषणा SCCB_RESET      0x80	/*   0 : No change */
				/*   1 : Resets all रेजिस्टरs to शेष */
				/* Resolution selection */
#घोषणा SLCT_MASK       0x40	/*   Mask of VGA or QVGA */
#घोषणा SLCT_VGA        0x00	/*   0 : VGA */
#घोषणा SLCT_QVGA       0x40	/*   1 : QVGA */
#घोषणा ITU656_ON_OFF   0x20	/* ITU656 protocol ON/OFF selection */
#घोषणा SENSOR_RAW	0x10	/* Sensor RAW */
				/* RGB output क्रमmat control */
#घोषणा FMT_MASK        0x0c	/*      Mask of color क्रमmat */
#घोषणा FMT_GBR422      0x00	/*      00 : GBR 4:2:2 */
#घोषणा FMT_RGB565      0x04	/*      01 : RGB 565 */
#घोषणा FMT_RGB555      0x08	/*      10 : RGB 555 */
#घोषणा FMT_RGB444      0x0c	/* 11 : RGB 444 */
				/* Output क्रमmat control */
#घोषणा OFMT_MASK       0x03    /*      Mask of output क्रमmat */
#घोषणा OFMT_YUV        0x00	/*      00 : YUV */
#घोषणा OFMT_P_BRAW     0x01	/*      01 : Processed Bayer RAW */
#घोषणा OFMT_RGB        0x02	/*      10 : RGB */
#घोषणा OFMT_BRAW       0x03	/* 11 : Bayer RAW */

/* COM8 */
#घोषणा FAST_ALGO       0x80	/* Enable fast AGC/AEC algorithm */
				/* AEC Setp size limit */
#घोषणा UNLMT_STEP      0x40	/*   0 : Step size is limited */
				/*   1 : Unlimited step size */
#घोषणा BNDF_ON_OFF     0x20	/* Banding filter ON/OFF */
#घोषणा AEC_BND         0x10	/* Enable AEC below banding value */
#घोषणा AEC_ON_OFF      0x08	/* Fine AEC ON/OFF control */
#घोषणा AGC_ON          0x04	/* AGC Enable */
#घोषणा AWB_ON          0x02	/* AWB Enable */
#घोषणा AEC_ON          0x01	/* AEC Enable */

/* COM9 */
#घोषणा BASE_AECAGC     0x80	/* Histogram or average based AEC/AGC */
				/* Automatic gain उच्चमानing - maximum AGC value */
#घोषणा GAIN_2x         0x00	/*    000 :   2x */
#घोषणा GAIN_4x         0x10	/*    001 :   4x */
#घोषणा GAIN_8x         0x20	/*    010 :   8x */
#घोषणा GAIN_16x        0x30	/*    011 :  16x */
#घोषणा GAIN_32x        0x40	/*    100 :  32x */
#घोषणा GAIN_64x        0x50	/* 101 :  64x */
#घोषणा GAIN_128x       0x60	/* 110 : 128x */
#घोषणा DROP_VSYNC      0x04	/* Drop VSYNC output of corrupt frame */
#घोषणा DROP_HREF       0x02	/* Drop HREF  output of corrupt frame */

/* COM11 */
#घोषणा SGLF_ON_OFF     0x02	/* Single frame ON/OFF selection */
#घोषणा SGLF_TRIG       0x01	/* Single frame transfer trigger */

/* HREF */
#घोषणा HREF_VSTART_SHIFT	6	/* VSTART LSB */
#घोषणा HREF_HSTART_SHIFT	4	/* HSTART 2 LSBs */
#घोषणा HREF_VSIZE_SHIFT	2	/* VSIZE LSB */
#घोषणा HREF_HSIZE_SHIFT	0	/* HSIZE 2 LSBs */

/* EXHCH */
#घोषणा EXHCH_VSIZE_SHIFT	2	/* VOUTSIZE LSB */
#घोषणा EXHCH_HSIZE_SHIFT	0	/* HOUTSIZE 2 LSBs */

/* DSP_CTRL1 */
#घोषणा FIFO_ON         0x80	/* FIFO enable/disable selection */
#घोषणा UV_ON_OFF       0x40	/* UV adjust function ON/OFF selection */
#घोषणा YUV444_2_422    0x20	/* YUV444 to 422 UV channel option selection */
#घोषणा CLR_MTRX_ON_OFF 0x10	/* Color matrix ON/OFF selection */
#घोषणा INTPLT_ON_OFF   0x08	/* Interpolation ON/OFF selection */
#घोषणा GMM_ON_OFF      0x04	/* Gamma function ON/OFF selection */
#घोषणा AUTO_BLK_ON_OFF 0x02	/* Black defect स्वतः correction ON/OFF */
#घोषणा AUTO_WHT_ON_OFF 0x01	/* White define स्वतः correction ON/OFF */

/* DSP_CTRL3 */
#घोषणा UV_MASK         0x80	/* UV output sequence option */
#घोषणा UV_ON           0x80	/*   ON */
#घोषणा UV_OFF          0x00	/*   OFF */
#घोषणा CBAR_MASK       0x20	/* DSP Color bar mask */
#घोषणा CBAR_ON         0x20	/*   ON */
#घोषणा CBAR_OFF        0x00	/*   OFF */

/* DSP_CTRL4 */
#घोषणा DSP_OFMT_YUV	0x00
#घोषणा DSP_OFMT_RGB	0x00
#घोषणा DSP_OFMT_RAW8	0x02
#घोषणा DSP_OFMT_RAW10	0x03

/* DSPAUTO (DSP Auto Function ON/OFF Control) */
#घोषणा AWB_ACTRL       0x80 /* AWB स्वतः threshold control */
#घोषणा DENOISE_ACTRL   0x40 /* De-noise स्वतः threshold control */
#घोषणा EDGE_ACTRL      0x20 /* Edge enhancement स्वतः strength control */
#घोषणा UV_ACTRL        0x10 /* UV adjust स्वतः slope control */
#घोषणा SCAL0_ACTRL     0x08 /* Auto scaling factor control */
#घोषणा SCAL1_2_ACTRL   0x04 /* Auto scaling factor control */

#घोषणा OV772X_MAX_WIDTH	VGA_WIDTH
#घोषणा OV772X_MAX_HEIGHT	VGA_HEIGHT

/*
 * ID
 */
#घोषणा OV7720  0x7720
#घोषणा OV7725  0x7721
#घोषणा VERSION(pid, ver) ((pid << 8) | (ver & 0xFF))

/*
 * PLL multipliers
 */
अटल काष्ठा अणु
	अचिन्हित पूर्णांक mult;
	u8 com4;
पूर्ण ov772x_pll[] = अणु
	अणु 1, PLL_BYPASS, पूर्ण,
	अणु 4, PLL_4x, पूर्ण,
	अणु 6, PLL_6x, पूर्ण,
	अणु 8, PLL_8x, पूर्ण,
पूर्ण;

/*
 * काष्ठा
 */

काष्ठा ov772x_color_क्रमmat अणु
	u32 code;
	क्रमागत v4l2_colorspace colorspace;
	u8 dsp3;
	u8 dsp4;
	u8 com3;
	u8 com7;
पूर्ण;

काष्ठा ov772x_win_size अणु
	अक्षर                     *name;
	अचिन्हित अक्षर             com7_bit;
	अचिन्हित पूर्णांक		  sizeimage;
	काष्ठा v4l2_rect	  rect;
पूर्ण;

काष्ठा ov772x_priv अणु
	काष्ठा v4l2_subdev                subdev;
	काष्ठा v4l2_ctrl_handler	  hdl;
	काष्ठा clk			 *clk;
	काष्ठा regmap			 *regmap;
	काष्ठा ov772x_camera_info        *info;
	काष्ठा gpio_desc		 *pwdn_gpio;
	काष्ठा gpio_desc		 *rstb_gpio;
	स्थिर काष्ठा ov772x_color_क्रमmat *cfmt;
	स्थिर काष्ठा ov772x_win_size     *win;
	काष्ठा v4l2_ctrl		 *vflip_ctrl;
	काष्ठा v4l2_ctrl		 *hflip_ctrl;
	अचिन्हित पूर्णांक			  test_pattern;
	/* band_filter = COM8[5] ? 256 - BDBASE : 0 */
	काष्ठा v4l2_ctrl		 *band_filter_ctrl;
	अचिन्हित पूर्णांक			  fps;
	/* lock to protect घातer_count and streaming */
	काष्ठा mutex			  lock;
	पूर्णांक				  घातer_count;
	पूर्णांक				  streaming;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_pad pad;
#पूर्ण_अगर
	क्रमागत v4l2_mbus_type		  bus_type;
पूर्ण;

/*
 * supported color क्रमmat list
 */
अटल स्थिर काष्ठा ov772x_color_क्रमmat ov772x_cfmts[] = अणु
	अणु
		.code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.dsp3		= 0x0,
		.dsp4		= DSP_OFMT_YUV,
		.com3		= SWAP_YUV,
		.com7		= OFMT_YUV,
	पूर्ण,
	अणु
		.code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.dsp3		= UV_ON,
		.dsp4		= DSP_OFMT_YUV,
		.com3		= SWAP_YUV,
		.com7		= OFMT_YUV,
	पूर्ण,
	अणु
		.code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.dsp3		= 0x0,
		.dsp4		= DSP_OFMT_YUV,
		.com3		= 0x0,
		.com7		= OFMT_YUV,
	पूर्ण,
	अणु
		.code		= MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.dsp3		= 0x0,
		.dsp4		= DSP_OFMT_YUV,
		.com3		= SWAP_RGB,
		.com7		= FMT_RGB555 | OFMT_RGB,
	पूर्ण,
	अणु
		.code		= MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.dsp3		= 0x0,
		.dsp4		= DSP_OFMT_YUV,
		.com3		= 0x0,
		.com7		= FMT_RGB555 | OFMT_RGB,
	पूर्ण,
	अणु
		.code		= MEDIA_BUS_FMT_RGB565_2X8_LE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.dsp3		= 0x0,
		.dsp4		= DSP_OFMT_YUV,
		.com3		= SWAP_RGB,
		.com7		= FMT_RGB565 | OFMT_RGB,
	पूर्ण,
	अणु
		.code		= MEDIA_BUS_FMT_RGB565_2X8_BE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.dsp3		= 0x0,
		.dsp4		= DSP_OFMT_YUV,
		.com3		= 0x0,
		.com7		= FMT_RGB565 | OFMT_RGB,
	पूर्ण,
	अणु
		/* Setting DSP4 to DSP_OFMT_RAW8 still gives 10-bit output,
		 * regardless of the COM7 value. We can thus only support 10-bit
		 * Bayer until someone figures it out.
		 */
		.code		= MEDIA_BUS_FMT_SBGGR10_1X10,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.dsp3		= 0x0,
		.dsp4		= DSP_OFMT_RAW10,
		.com3		= 0x0,
		.com7		= SENSOR_RAW | OFMT_BRAW,
	पूर्ण,
पूर्ण;

/*
 * winकरोw size list
 */

अटल स्थिर काष्ठा ov772x_win_size ov772x_win_sizes[] = अणु
	अणु
		.name		= "VGA",
		.com7_bit	= SLCT_VGA,
		.sizeimage	= 510 * 748,
		.rect = अणु
			.left	= 140,
			.top	= 14,
			.width	= VGA_WIDTH,
			.height	= VGA_HEIGHT,
		पूर्ण,
	पूर्ण, अणु
		.name		= "QVGA",
		.com7_bit	= SLCT_QVGA,
		.sizeimage	= 278 * 576,
		.rect = अणु
			.left	= 252,
			.top	= 6,
			.width	= QVGA_WIDTH,
			.height	= QVGA_HEIGHT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov772x_test_pattern_menu[] = अणु
	"Disabled",
	"Vertical Color Bar Type 1",
पूर्ण;

/*
 * frame rate settings lists
 */
अटल स्थिर अचिन्हित पूर्णांक ov772x_frame_पूर्णांकervals[] = अणु 5, 10, 15, 20, 30, 60 पूर्ण;

/*
 * general function
 */

अटल काष्ठा ov772x_priv *to_ov772x(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov772x_priv, subdev);
पूर्ण

अटल पूर्णांक ov772x_reset(काष्ठा ov772x_priv *priv)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(priv->regmap, COM7, SCCB_RESET);
	अगर (ret < 0)
		वापस ret;

	usleep_range(1000, 5000);

	वापस regmap_update_bits(priv->regmap, COM2, SOFT_SLEEP_MODE,
				  SOFT_SLEEP_MODE);
पूर्ण

/*
 * subdev ops
 */

अटल पूर्णांक ov772x_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov772x_priv *priv = to_ov772x(sd);
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	अगर (priv->streaming == enable)
		जाओ करोne;

	अगर (priv->bus_type == V4L2_MBUS_BT656) अणु
		ret = regmap_update_bits(priv->regmap, COM7, ITU656_ON_OFF,
					 enable ?
					 ITU656_ON_OFF : ~ITU656_ON_OFF);
		अगर (ret)
			जाओ करोne;
	पूर्ण

	ret = regmap_update_bits(priv->regmap, COM2, SOFT_SLEEP_MODE,
				 enable ? 0 : SOFT_SLEEP_MODE);
	अगर (ret)
		जाओ करोne;

	अगर (enable) अणु
		dev_dbg(&client->dev, "format %d, win %s\n",
			priv->cfmt->code, priv->win->name);
	पूर्ण
	priv->streaming = enable;

करोne:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक ov772x_select_fps(काष्ठा ov772x_priv *priv,
				      काष्ठा v4l2_fract *tpf)
अणु
	अचिन्हित पूर्णांक fps = tpf->numerator ?
			   tpf->denominator / tpf->numerator :
			   tpf->denominator;
	अचिन्हित पूर्णांक best_dअगरf;
	अचिन्हित पूर्णांक dअगरf;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक i;

	/* Approximate to the बंदst supported frame पूर्णांकerval. */
	best_dअगरf = ~0L;
	क्रम (i = 0, idx = 0; i < ARRAY_SIZE(ov772x_frame_पूर्णांकervals); i++) अणु
		dअगरf = असल(fps - ov772x_frame_पूर्णांकervals[i]);
		अगर (dअगरf < best_dअगरf) अणु
			idx = i;
			best_dअगरf = dअगरf;
		पूर्ण
	पूर्ण

	वापस ov772x_frame_पूर्णांकervals[idx];
पूर्ण

अटल पूर्णांक ov772x_set_frame_rate(काष्ठा ov772x_priv *priv,
				 अचिन्हित पूर्णांक fps,
				 स्थिर काष्ठा ov772x_color_क्रमmat *cfmt,
				 स्थिर काष्ठा ov772x_win_size *win)
अणु
	अचिन्हित दीर्घ fin = clk_get_rate(priv->clk);
	अचिन्हित पूर्णांक best_dअगरf;
	अचिन्हित पूर्णांक fsize;
	अचिन्हित पूर्णांक pclk;
	अचिन्हित पूर्णांक dअगरf;
	अचिन्हित पूर्णांक i;
	u8 clkrc = 0;
	u8 com4 = 0;
	पूर्णांक ret;

	/* Use image size (with blankings) to calculate desired pixel घड़ी. */
	चयन (cfmt->com7 & OFMT_MASK) अणु
	हाल OFMT_BRAW:
		fsize = win->sizeimage;
		अवरोध;
	हाल OFMT_RGB:
	हाल OFMT_YUV:
	शेष:
		fsize = win->sizeimage * 2;
		अवरोध;
	पूर्ण

	pclk = fps * fsize;

	/*
	 * Pixel घड़ी generation circuit is pretty simple:
	 *
	 * Fin -> [ / CLKRC_भाग] -> [ * PLL_mult] -> pclk
	 *
	 * Try to approximate the desired pixel घड़ी testing all available
	 * PLL multipliers (1x, 4x, 6x, 8x) and calculate corresponding
	 * भागisor with:
	 *
	 * भाग = PLL_mult * Fin / pclk
	 *
	 * and re-calculate the pixel घड़ी using it:
	 *
	 * pclk = Fin * PLL_mult / CLKRC_भाग
	 *
	 * Choose the PLL_mult and CLKRC_भाग pair that gives a pixel घड़ी
	 * बंदr to the desired one.
	 *
	 * The desired pixel घड़ी is calculated using a known frame size
	 * (blanking included) and FPS.
	 */
	best_dअगरf = ~0L;
	क्रम (i = 0; i < ARRAY_SIZE(ov772x_pll); i++) अणु
		अचिन्हित पूर्णांक pll_mult = ov772x_pll[i].mult;
		अचिन्हित पूर्णांक pll_out = pll_mult * fin;
		अचिन्हित पूर्णांक t_pclk;
		अचिन्हित पूर्णांक भाग;

		अगर (pll_out < pclk)
			जारी;

		भाग = DIV_ROUND_CLOSEST(pll_out, pclk);
		t_pclk = DIV_ROUND_CLOSEST(fin * pll_mult, भाग);
		dअगरf = असल(pclk - t_pclk);
		अगर (dअगरf < best_dअगरf) अणु
			best_dअगरf = dअगरf;
			clkrc = CLKRC_DIV(भाग);
			com4 = ov772x_pll[i].com4;
		पूर्ण
	पूर्ण

	ret = regmap_ग_लिखो(priv->regmap, COM4, com4 | COM4_RESERVED);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(priv->regmap, CLKRC, clkrc | CLKRC_RESERVED);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ov772x_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा ov772x_priv *priv = to_ov772x(sd);
	काष्ठा v4l2_fract *tpf = &ival->पूर्णांकerval;

	tpf->numerator = 1;
	tpf->denominator = priv->fps;

	वापस 0;
पूर्ण

अटल पूर्णांक ov772x_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा ov772x_priv *priv = to_ov772x(sd);
	काष्ठा v4l2_fract *tpf = &ival->पूर्णांकerval;
	अचिन्हित पूर्णांक fps;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	अगर (priv->streaming) अणु
		ret = -EBUSY;
		जाओ error;
	पूर्ण

	fps = ov772x_select_fps(priv, tpf);

	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any changes to H/W at this समय. Instead
	 * the frame rate will be restored right after घातer-up.
	 */
	अगर (priv->घातer_count > 0) अणु
		ret = ov772x_set_frame_rate(priv, fps, priv->cfmt, priv->win);
		अगर (ret)
			जाओ error;
	पूर्ण

	tpf->numerator = 1;
	tpf->denominator = fps;
	priv->fps = fps;

error:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov772x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov772x_priv *priv = container_of(ctrl->handler,
						काष्ठा ov772x_priv, hdl);
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret = 0;
	u8 val;

	/* v4l2_ctrl_lock() locks our own mutex */

	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any controls to H/W at this समय. Instead
	 * the controls will be restored right after घातer-up.
	 */
	अगर (priv->घातer_count == 0)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		val = ctrl->val ? VFLIP_IMG : 0x00;
		अगर (priv->info && (priv->info->flags & OV772X_FLAG_VFLIP))
			val ^= VFLIP_IMG;
		वापस regmap_update_bits(regmap, COM3, VFLIP_IMG, val);
	हाल V4L2_CID_HFLIP:
		val = ctrl->val ? HFLIP_IMG : 0x00;
		अगर (priv->info && (priv->info->flags & OV772X_FLAG_HFLIP))
			val ^= HFLIP_IMG;
		वापस regmap_update_bits(regmap, COM3, HFLIP_IMG, val);
	हाल V4L2_CID_BAND_STOP_FILTER:
		अगर (!ctrl->val) अणु
			/* Switch the filter off, it is on now */
			ret = regmap_update_bits(regmap, BDBASE, 0xff, 0xff);
			अगर (!ret)
				ret = regmap_update_bits(regmap, COM8,
							 BNDF_ON_OFF, 0);
		पूर्ण अन्यथा अणु
			/* Switch the filter on, set AEC low limit */
			val = 256 - ctrl->val;
			ret = regmap_update_bits(regmap, COM8,
						 BNDF_ON_OFF, BNDF_ON_OFF);
			अगर (!ret)
				ret = regmap_update_bits(regmap, BDBASE,
							 0xff, val);
		पूर्ण

		वापस ret;
	हाल V4L2_CID_TEST_PATTERN:
		priv->test_pattern = ctrl->val;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ov772x_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा ov772x_priv *priv = to_ov772x(sd);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	reg->size = 1;
	अगर (reg->reg > 0xff)
		वापस -EINVAL;

	ret = regmap_पढ़ो(priv->regmap, reg->reg, &val);
	अगर (ret < 0)
		वापस ret;

	reg->val = (__u64)val;

	वापस 0;
पूर्ण

अटल पूर्णांक ov772x_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा ov772x_priv *priv = to_ov772x(sd);

	अगर (reg->reg > 0xff ||
	    reg->val > 0xff)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(priv->regmap, reg->reg, reg->val);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ov772x_घातer_on(काष्ठा ov772x_priv *priv)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&priv->subdev);
	पूर्णांक ret;

	अगर (priv->clk) अणु
		ret = clk_prepare_enable(priv->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (priv->pwdn_gpio) अणु
		gpiod_set_value(priv->pwdn_gpio, 1);
		usleep_range(500, 1000);
	पूर्ण

	/*
	 * FIXME: The reset संकेत is connected to a shared GPIO on some
	 * platक्रमms (namely the SuperH Migo-R). Until a framework becomes
	 * available to handle this cleanly, request the GPIO temporarily
	 * to aव्योम conflicts.
	 */
	priv->rstb_gpio = gpiod_get_optional(&client->dev, "reset",
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->rstb_gpio)) अणु
		dev_info(&client->dev, "Unable to get GPIO \"reset\"");
		clk_disable_unprepare(priv->clk);
		वापस PTR_ERR(priv->rstb_gpio);
	पूर्ण

	अगर (priv->rstb_gpio) अणु
		gpiod_set_value(priv->rstb_gpio, 1);
		usleep_range(500, 1000);
		gpiod_set_value(priv->rstb_gpio, 0);
		usleep_range(500, 1000);

		gpiod_put(priv->rstb_gpio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov772x_घातer_off(काष्ठा ov772x_priv *priv)
अणु
	clk_disable_unprepare(priv->clk);

	अगर (priv->pwdn_gpio) अणु
		gpiod_set_value(priv->pwdn_gpio, 0);
		usleep_range(500, 1000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov772x_set_params(काष्ठा ov772x_priv *priv,
			     स्थिर काष्ठा ov772x_color_क्रमmat *cfmt,
			     स्थिर काष्ठा ov772x_win_size *win);

अटल पूर्णांक ov772x_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov772x_priv *priv = to_ov772x(sd);
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	/* If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (priv->घातer_count == !on) अणु
		अगर (on) अणु
			ret = ov772x_घातer_on(priv);
			/*
			 * Restore the क्रमmat, the frame rate, and
			 * the controls
			 */
			अगर (!ret)
				ret = ov772x_set_params(priv, priv->cfmt,
							priv->win);
		पूर्ण अन्यथा अणु
			ret = ov772x_घातer_off(priv);
		पूर्ण
	पूर्ण

	अगर (!ret) अणु
		/* Update the घातer count. */
		priv->घातer_count += on ? 1 : -1;
		WARN(priv->घातer_count < 0, "Unbalanced power count\n");
		WARN(priv->घातer_count > 1, "Duplicated s_power call\n");
	पूर्ण

	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ov772x_win_size *ov772x_select_win(u32 width, u32 height)
अणु
	स्थिर काष्ठा ov772x_win_size *win = &ov772x_win_sizes[0];
	u32 best_dअगरf = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ov772x_win_sizes); ++i) अणु
		u32 dअगरf = असल(width - ov772x_win_sizes[i].rect.width)
			 + असल(height - ov772x_win_sizes[i].rect.height);
		अगर (dअगरf < best_dअगरf) अणु
			best_dअगरf = dअगरf;
			win = &ov772x_win_sizes[i];
		पूर्ण
	पूर्ण

	वापस win;
पूर्ण

अटल व्योम ov772x_select_params(स्थिर काष्ठा v4l2_mbus_framefmt *mf,
				 स्थिर काष्ठा ov772x_color_क्रमmat **cfmt,
				 स्थिर काष्ठा ov772x_win_size **win)
अणु
	अचिन्हित पूर्णांक i;

	/* Select a क्रमmat. */
	*cfmt = &ov772x_cfmts[0];

	क्रम (i = 0; i < ARRAY_SIZE(ov772x_cfmts); i++) अणु
		अगर (mf->code == ov772x_cfmts[i].code) अणु
			*cfmt = &ov772x_cfmts[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/* Select a winकरोw size. */
	*win = ov772x_select_win(mf->width, mf->height);
पूर्ण

अटल पूर्णांक ov772x_edgectrl(काष्ठा ov772x_priv *priv)
अणु
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret;

	अगर (!priv->info)
		वापस 0;

	अगर (priv->info->edgectrl.strength & OV772X_MANUAL_EDGE_CTRL) अणु
		/*
		 * Manual Edge Control Mode.
		 *
		 * Edge स्वतः strength bit is set by शेष.
		 * Remove it when manual mode.
		 */

		ret = regmap_update_bits(regmap, DSPAUTO, EDGE_ACTRL, 0x00);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(regmap, EDGE_TRSHLD,
					 OV772X_EDGE_THRESHOLD_MASK,
					 priv->info->edgectrl.threshold);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(regmap, EDGE_STRNGT,
					 OV772X_EDGE_STRENGTH_MASK,
					 priv->info->edgectrl.strength);
		अगर (ret < 0)
			वापस ret;

	पूर्ण अन्यथा अगर (priv->info->edgectrl.upper > priv->info->edgectrl.lower) अणु
		/*
		 * Auto Edge Control Mode.
		 *
		 * Set upper and lower limit.
		 */
		ret = regmap_update_bits(regmap, EDGE_UPPER,
					 OV772X_EDGE_UPPER_MASK,
					 priv->info->edgectrl.upper);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(regmap, EDGE_LOWER,
					 OV772X_EDGE_LOWER_MASK,
					 priv->info->edgectrl.lower);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov772x_set_params(काष्ठा ov772x_priv *priv,
			     स्थिर काष्ठा ov772x_color_क्रमmat *cfmt,
			     स्थिर काष्ठा ov772x_win_size *win)
अणु
	पूर्णांक ret;
	u8  val;

	/* Reset hardware. */
	ov772x_reset(priv);

	/* Edge Ctrl. */
	ret = ov772x_edgectrl(priv);
	अगर (ret < 0)
		वापस ret;

	/* Format and winकरोw size. */
	ret = regmap_ग_लिखो(priv->regmap, HSTART, win->rect.left >> 2);
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;
	ret = regmap_ग_लिखो(priv->regmap, HSIZE, win->rect.width >> 2);
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;
	ret = regmap_ग_लिखो(priv->regmap, VSTART, win->rect.top >> 1);
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;
	ret = regmap_ग_लिखो(priv->regmap, VSIZE, win->rect.height >> 1);
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;
	ret = regmap_ग_लिखो(priv->regmap, HOUTSIZE, win->rect.width >> 2);
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;
	ret = regmap_ग_लिखो(priv->regmap, VOUTSIZE, win->rect.height >> 1);
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;
	ret = regmap_ग_लिखो(priv->regmap, HREF,
			   ((win->rect.top & 1) << HREF_VSTART_SHIFT) |
			   ((win->rect.left & 3) << HREF_HSTART_SHIFT) |
			   ((win->rect.height & 1) << HREF_VSIZE_SHIFT) |
			   ((win->rect.width & 3) << HREF_HSIZE_SHIFT));
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;
	ret = regmap_ग_लिखो(priv->regmap, EXHCH,
			   ((win->rect.height & 1) << EXHCH_VSIZE_SHIFT) |
			   ((win->rect.width & 3) << EXHCH_HSIZE_SHIFT));
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;

	/* Set DSP_CTRL3. */
	val = cfmt->dsp3;
	अगर (val) अणु
		ret = regmap_update_bits(priv->regmap, DSP_CTRL3, UV_MASK, val);
		अगर (ret < 0)
			जाओ ov772x_set_fmt_error;
	पूर्ण

	/* DSP_CTRL4: AEC reference poपूर्णांक and DSP output क्रमmat. */
	अगर (cfmt->dsp4) अणु
		ret = regmap_ग_लिखो(priv->regmap, DSP_CTRL4, cfmt->dsp4);
		अगर (ret < 0)
			जाओ ov772x_set_fmt_error;
	पूर्ण

	/* Set COM3. */
	val = cfmt->com3;
	अगर (priv->info && (priv->info->flags & OV772X_FLAG_VFLIP))
		val |= VFLIP_IMG;
	अगर (priv->info && (priv->info->flags & OV772X_FLAG_HFLIP))
		val |= HFLIP_IMG;
	अगर (priv->vflip_ctrl->val)
		val ^= VFLIP_IMG;
	अगर (priv->hflip_ctrl->val)
		val ^= HFLIP_IMG;
	अगर (priv->test_pattern)
		val |= SCOLOR_TEST;

	ret = regmap_update_bits(priv->regmap, COM3, SWAP_MASK | IMG_MASK, val);
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;

	/* COM7: Sensor resolution and output क्रमmat control. */
	ret = regmap_ग_लिखो(priv->regmap, COM7, win->com7_bit | cfmt->com7);
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;

	/* COM4, CLKRC: Set pixel घड़ी and framerate. */
	ret = ov772x_set_frame_rate(priv, priv->fps, cfmt, win);
	अगर (ret < 0)
		जाओ ov772x_set_fmt_error;

	/* Set COM8. */
	अगर (priv->band_filter_ctrl->val) अणु
		अचिन्हित लघु band_filter = priv->band_filter_ctrl->val;

		ret = regmap_update_bits(priv->regmap, COM8,
					 BNDF_ON_OFF, BNDF_ON_OFF);
		अगर (!ret)
			ret = regmap_update_bits(priv->regmap, BDBASE,
						 0xff, 256 - band_filter);
		अगर (ret < 0)
			जाओ ov772x_set_fmt_error;
	पूर्ण

	वापस ret;

ov772x_set_fmt_error:

	ov772x_reset(priv);

	वापस ret;
पूर्ण

अटल पूर्णांक ov772x_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा ov772x_priv *priv = to_ov772x(sd);

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	sel->r.left = 0;
	sel->r.top = 0;
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP:
		sel->r.width = priv->win->rect.width;
		sel->r.height = priv->win->rect.height;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ov772x_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा ov772x_priv *priv = to_ov772x(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	mf->width	= priv->win->rect.width;
	mf->height	= priv->win->rect.height;
	mf->code	= priv->cfmt->code;
	mf->colorspace	= priv->cfmt->colorspace;
	mf->field	= V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक ov772x_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov772x_priv *priv = to_ov772x(sd);
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	स्थिर काष्ठा ov772x_color_क्रमmat *cfmt;
	स्थिर काष्ठा ov772x_win_size *win;
	पूर्णांक ret = 0;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	ov772x_select_params(mf, &cfmt, &win);

	mf->code = cfmt->code;
	mf->width = win->rect.width;
	mf->height = win->rect.height;
	mf->field = V4L2_FIELD_NONE;
	mf->colorspace = cfmt->colorspace;
	mf->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	mf->quantization = V4L2_QUANTIZATION_DEFAULT;
	mf->xfer_func = V4L2_XFER_FUNC_DEFAULT;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cfg->try_fmt = *mf;
		वापस 0;
	पूर्ण

	mutex_lock(&priv->lock);

	अगर (priv->streaming) अणु
		ret = -EBUSY;
		जाओ error;
	पूर्ण

	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any changes to H/W at this समय. Instead
	 * the क्रमmat will be restored right after घातer-up.
	 */
	अगर (priv->घातer_count > 0) अणु
		ret = ov772x_set_params(priv, cfmt, win);
		अगर (ret < 0)
			जाओ error;
	पूर्ण
	priv->win = win;
	priv->cfmt = cfmt;

error:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov772x_video_probe(काष्ठा ov772x_priv *priv)
अणु
	काष्ठा i2c_client  *client = v4l2_get_subdevdata(&priv->subdev);
	पूर्णांक		    pid, ver, midh, midl;
	स्थिर अक्षर         *devname;
	पूर्णांक		    ret;

	ret = ov772x_घातer_on(priv);
	अगर (ret < 0)
		वापस ret;

	/* Check and show product ID and manufacturer ID. */
	ret = regmap_पढ़ो(priv->regmap, PID, &pid);
	अगर (ret < 0)
		वापस ret;
	ret = regmap_पढ़ो(priv->regmap, VER, &ver);
	अगर (ret < 0)
		वापस ret;

	चयन (VERSION(pid, ver)) अणु
	हाल OV7720:
		devname     = "ov7720";
		अवरोध;
	हाल OV7725:
		devname     = "ov7725";
		अवरोध;
	शेष:
		dev_err(&client->dev,
			"Product ID error %x:%x\n", pid, ver);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	ret = regmap_पढ़ो(priv->regmap, MIDH, &midh);
	अगर (ret < 0)
		वापस ret;
	ret = regmap_पढ़ो(priv->regmap, MIDL, &midl);
	अगर (ret < 0)
		वापस ret;

	dev_info(&client->dev,
		 "%s Product ID %0x:%0x Manufacturer ID %x:%x\n",
		 devname, pid, ver, midh, midl);

	ret = v4l2_ctrl_handler_setup(&priv->hdl);

करोne:
	ov772x_घातer_off(priv);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov772x_ctrl_ops = अणु
	.s_ctrl = ov772x_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov772x_subdev_core_ops = अणु
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर	= ov772x_g_रेजिस्टर,
	.s_रेजिस्टर	= ov772x_s_रेजिस्टर,
#पूर्ण_अगर
	.s_घातer	= ov772x_s_घातer,
पूर्ण;

अटल पूर्णांक ov772x_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	अगर (fie->pad || fie->index >= ARRAY_SIZE(ov772x_frame_पूर्णांकervals))
		वापस -EINVAL;

	अगर (fie->width != VGA_WIDTH && fie->width != QVGA_WIDTH)
		वापस -EINVAL;
	अगर (fie->height != VGA_HEIGHT && fie->height != QVGA_HEIGHT)
		वापस -EINVAL;

	fie->पूर्णांकerval.numerator = 1;
	fie->पूर्णांकerval.denominator = ov772x_frame_पूर्णांकervals[fie->index];

	वापस 0;
पूर्ण

अटल पूर्णांक ov772x_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= ARRAY_SIZE(ov772x_cfmts))
		वापस -EINVAL;

	code->code = ov772x_cfmts[code->index].code;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov772x_subdev_video_ops = अणु
	.s_stream		= ov772x_s_stream,
	.s_frame_पूर्णांकerval	= ov772x_s_frame_पूर्णांकerval,
	.g_frame_पूर्णांकerval	= ov772x_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov772x_subdev_pad_ops = अणु
	.क्रमागत_frame_पूर्णांकerval	= ov772x_क्रमागत_frame_पूर्णांकerval,
	.क्रमागत_mbus_code		= ov772x_क्रमागत_mbus_code,
	.get_selection		= ov772x_get_selection,
	.get_fmt		= ov772x_get_fmt,
	.set_fmt		= ov772x_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov772x_subdev_ops = अणु
	.core	= &ov772x_subdev_core_ops,
	.video	= &ov772x_subdev_video_ops,
	.pad	= &ov772x_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक ov772x_parse_dt(काष्ठा i2c_client *client,
			   काष्ठा ov772x_priv *priv)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_PARALLEL
	पूर्ण;
	काष्ठा fwnode_handle *ep;
	पूर्णांक ret;

	ep = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(&client->dev), शून्य);
	अगर (!ep) अणु
		dev_err(&client->dev, "Endpoint node not found\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * For backward compatibility with older DTS where the
	 * bus-type property was not mandatory, assume
	 * V4L2_MBUS_PARALLEL as it was the only supported bus at the
	 * समय. v4l2_fwnode_endpoपूर्णांक_alloc_parse() will not fail अगर
	 * 'bus-type' is not specअगरied.
	 */
	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(ep, &bus_cfg);
	अगर (ret) अणु
		bus_cfg = (काष्ठा v4l2_fwnode_endpoपूर्णांक)
			  अणु .bus_type = V4L2_MBUS_BT656 पूर्ण;
		ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(ep, &bus_cfg);
		अगर (ret)
			जाओ error_fwnode_put;
	पूर्ण

	priv->bus_type = bus_cfg.bus_type;
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);

error_fwnode_put:
	fwnode_handle_put(ep);

	वापस ret;
पूर्ण

/*
 * i2c_driver function
 */

अटल पूर्णांक ov772x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov772x_priv	*priv;
	पूर्णांक			ret;
	अटल स्थिर काष्ठा regmap_config ov772x_regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = DSPAUTO,
	पूर्ण;

	अगर (!client->dev.of_node && !client->dev.platक्रमm_data) अणु
		dev_err(&client->dev,
			"Missing ov772x platform data for non-DT device\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = devm_regmap_init_sccb(client, &ov772x_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(&client->dev, "Failed to allocate register map\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	priv->info = client->dev.platक्रमm_data;
	mutex_init(&priv->lock);

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov772x_subdev_ops);
	priv->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
			      V4L2_SUBDEV_FL_HAS_EVENTS;
	v4l2_ctrl_handler_init(&priv->hdl, 3);
	/* Use our mutex क्रम the controls */
	priv->hdl.lock = &priv->lock;
	priv->vflip_ctrl = v4l2_ctrl_new_std(&priv->hdl, &ov772x_ctrl_ops,
					     V4L2_CID_VFLIP, 0, 1, 1, 0);
	priv->hflip_ctrl = v4l2_ctrl_new_std(&priv->hdl, &ov772x_ctrl_ops,
					     V4L2_CID_HFLIP, 0, 1, 1, 0);
	priv->band_filter_ctrl = v4l2_ctrl_new_std(&priv->hdl, &ov772x_ctrl_ops,
						   V4L2_CID_BAND_STOP_FILTER,
						   0, 256, 1, 0);
	v4l2_ctrl_new_std_menu_items(&priv->hdl, &ov772x_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov772x_test_pattern_menu) - 1,
				     0, 0, ov772x_test_pattern_menu);
	priv->subdev.ctrl_handler = &priv->hdl;
	अगर (priv->hdl.error) अणु
		ret = priv->hdl.error;
		जाओ error_mutex_destroy;
	पूर्ण

	priv->clk = clk_get(&client->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&client->dev, "Unable to get xclk clock\n");
		ret = PTR_ERR(priv->clk);
		जाओ error_ctrl_मुक्त;
	पूर्ण

	priv->pwdn_gpio = gpiod_get_optional(&client->dev, "powerdown",
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->pwdn_gpio)) अणु
		dev_info(&client->dev, "Unable to get GPIO \"powerdown\"");
		ret = PTR_ERR(priv->pwdn_gpio);
		जाओ error_clk_put;
	पूर्ण

	ret = ov772x_parse_dt(client, priv);
	अगर (ret)
		जाओ error_clk_put;

	ret = ov772x_video_probe(priv);
	अगर (ret < 0)
		जाओ error_gpio_put;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	priv->pad.flags = MEDIA_PAD_FL_SOURCE;
	priv->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&priv->subdev.entity, 1, &priv->pad);
	अगर (ret < 0)
		जाओ error_gpio_put;
#पूर्ण_अगर

	priv->cfmt = &ov772x_cfmts[0];
	priv->win = &ov772x_win_sizes[0];
	priv->fps = 15;

	ret = v4l2_async_रेजिस्टर_subdev(&priv->subdev);
	अगर (ret)
		जाओ error_entity_cleanup;

	वापस 0;

error_entity_cleanup:
	media_entity_cleanup(&priv->subdev.entity);
error_gpio_put:
	अगर (priv->pwdn_gpio)
		gpiod_put(priv->pwdn_gpio);
error_clk_put:
	clk_put(priv->clk);
error_ctrl_मुक्त:
	v4l2_ctrl_handler_मुक्त(&priv->hdl);
error_mutex_destroy:
	mutex_destroy(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov772x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ov772x_priv *priv = to_ov772x(i2c_get_clientdata(client));

	media_entity_cleanup(&priv->subdev.entity);
	clk_put(priv->clk);
	अगर (priv->pwdn_gpio)
		gpiod_put(priv->pwdn_gpio);
	v4l2_async_unरेजिस्टर_subdev(&priv->subdev);
	v4l2_ctrl_handler_मुक्त(&priv->hdl);
	mutex_destroy(&priv->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov772x_id[] = अणु
	अणु "ov772x", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov772x_id);

अटल स्थिर काष्ठा of_device_id ov772x_of_match[] = अणु
	अणु .compatible = "ovti,ov7725", पूर्ण,
	अणु .compatible = "ovti,ov7720", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ov772x_of_match);

अटल काष्ठा i2c_driver ov772x_i2c_driver = अणु
	.driver = अणु
		.name = "ov772x",
		.of_match_table = ov772x_of_match,
	पूर्ण,
	.probe_new = ov772x_probe,
	.हटाओ   = ov772x_हटाओ,
	.id_table = ov772x_id,
पूर्ण;

module_i2c_driver(ov772x_i2c_driver);

MODULE_DESCRIPTION("V4L2 driver for OV772x image sensor");
MODULE_AUTHOR("Kuninori Morimoto");
MODULE_LICENSE("GPL v2");
