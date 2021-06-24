<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Z-Star/Vimicro zc301/zc302p/vc30x driver
 *
 * Copyright (C) 2009-2012 Jean-Francois Moine <http://moinejf.मुक्त.fr>
 * Copyright (C) 2004 2005 2006 Michel Xhaard mxhaard@magic.fr
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/input.h>
#समावेश "gspca.h"
#समावेश "jpeg.h"

MODULE_AUTHOR("Jean-Francois Moine <http://moinejf.free.fr>, Serge A. Suchkov <Serge.A.S@tochka.ru>");
MODULE_DESCRIPTION("GSPCA ZC03xx/VC3xx USB Camera Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक क्रमce_sensor = -1;

#घोषणा REG08_DEF 3		/* शेष JPEG compression (75%) */
#समावेश "zc3xx-reg.h"

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	काष्ठा अणु /* gamma/brightness/contrast control cluster */
		काष्ठा v4l2_ctrl *gamma;
		काष्ठा v4l2_ctrl *brightness;
		काष्ठा v4l2_ctrl *contrast;
	पूर्ण;
	काष्ठा अणु /* स्वतःgain/exposure control cluster */
		काष्ठा v4l2_ctrl *स्वतःgain;
		काष्ठा v4l2_ctrl *exposure;
	पूर्ण;
	काष्ठा v4l2_ctrl *plfreq;
	काष्ठा v4l2_ctrl *sharpness;
	काष्ठा v4l2_ctrl *jpegqual;

	काष्ठा work_काष्ठा work;

	u8 reg08;		/* webcam compression quality */

	u8 bridge;
	u8 sensor;		/* Type of image sensor chip */
	u16 chip_revision;

	u8 jpeg_hdr[JPEG_HDR_SZ];
पूर्ण;
क्रमागत bridges अणु
	BRIDGE_ZC301,
	BRIDGE_ZC303,
पूर्ण;
क्रमागत sensors अणु
	SENSOR_ADCM2700,
	SENSOR_CS2102,
	SENSOR_CS2102K,
	SENSOR_GC0303,
	SENSOR_GC0305,
	SENSOR_HDCS2020,
	SENSOR_HV7131B,
	SENSOR_HV7131R,
	SENSOR_ICM105A,
	SENSOR_MC501CB,
	SENSOR_MT9V111_1,	/* (mi360soc) zc301 */
	SENSOR_MT9V111_3,	/* (mi360soc) zc303 */
	SENSOR_OV7620,		/* OV7648 - same values */
	SENSOR_OV7630C,
	SENSOR_PAS106,
	SENSOR_PAS202B,
	SENSOR_PB0330,
	SENSOR_PO2030,
	SENSOR_TAS5130C,
	SENSOR_MAX
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat broken_vga_mode[] = अणु
	अणु320, 232, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 232 * 4 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु640, 472, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 472 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat sअगर_mode[] = अणु
	अणु176, 144, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

/*
 * Bridge reg08 bits 1-2 -> JPEG quality conversion table. Note the highest
 * quality setting is not usable as USB 1 करोes not have enough bandwidth.
 */
अटल u8 jpeg_qual[] = अणु50, 75, 87, /* 94 */पूर्ण;

/* usb exchanges */
काष्ठा usb_action अणु
	u8	req;
	u8	val;
	u16	idx;
पूर्ण;

अटल स्थिर काष्ठा usb_action adcm2700_Initial[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,		/* 00,00,01,cc */
	अणु0xa0, 0x04, ZC3XX_R002_CLOCKSELECTपूर्ण,		/* 00,02,04,cc */
	अणु0xa0, 0x00, ZC3XX_R008_CLOCKSETTINGपूर्ण,		/* 00,08,03,cc */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xa0, 0xd3, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,		/* 00,8b,d3,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,	/* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,		/* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,	/* 00,05,01,cc */
	अणु0xa0, 0xd8, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,	/* 00,06,d8,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,	/* 00,01,01,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,01,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,05,cc */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,		/* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,		/* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,		/* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,		/* 01,1c,00,cc */
	अणु0xa0, 0xde, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,		/* 00,9c,de,cc */
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण,		/* 00,9e,86,cc */
	अणु0xbb, 0x00, 0x0400पूर्ण,				/* 04,00,00,bb */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xbb, 0x0f, 0x140fपूर्ण,				/* 14,0f,0f,bb */
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,	/* 01,01,37,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,		/* 01,00,0d,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,		/* 01,89,06,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,		/* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,		/* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,	/* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,		/* 03,01,08,cc */
	अणु0xa0, 0x58, ZC3XX_R116_RGAINपूर्ण,			/* 01,16,58,cc */
	अणु0xa0, 0x5a, ZC3XX_R118_BGAINपूर्ण,			/* 01,18,5a,cc */
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,02,cc */
	अणु0xa0, 0xd3, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,		/* 00,8b,d3,cc */
	अणु0xbb, 0x00, 0x0408पूर्ण,				/* 04,00,08,bb */
	अणु0xdd, 0x00, 0x0200पूर्ण,				/* 00,02,00,dd */
	अणु0xbb, 0x00, 0x0400पूर्ण,				/* 04,00,00,bb */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xbb, 0x0f, 0x140fपूर्ण,				/* 14,0f,0f,bb */
	अणु0xbb, 0xe0, 0x0c2eपूर्ण,				/* 0c,e0,2e,bb */
	अणु0xbb, 0x01, 0x2000पूर्ण,				/* 20,01,00,bb */
	अणु0xbb, 0x96, 0x2400पूर्ण,				/* 24,96,00,bb */
	अणु0xbb, 0x06, 0x1006पूर्ण,				/* 10,06,06,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xaa, 0xfe, 0x0002पूर्ण,				/* 00,fe,02,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xbb, 0x5f, 0x2090पूर्ण,				/* 20,5f,90,bb */
	अणु0xbb, 0x01, 0x8000पूर्ण,				/* 80,01,00,bb */
	अणु0xbb, 0x09, 0x8400पूर्ण,				/* 84,09,00,bb */
	अणु0xbb, 0x86, 0x0002पूर्ण,				/* 00,86,02,bb */
	अणु0xbb, 0xe6, 0x0401पूर्ण,				/* 04,e6,01,bb */
	अणु0xbb, 0x86, 0x0802पूर्ण,				/* 08,86,02,bb */
	अणु0xbb, 0xe6, 0x0c01पूर्ण,				/* 0c,e6,01,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xaa, 0xfe, 0x0000पूर्ण,				/* 00,fe,00,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0020पूर्ण,				/* 00,fe,20,aa */
/*mswin+*/
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xaa, 0xfe, 0x0002पूर्ण,
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xaa, 0xb4, 0xcd37पूर्ण,
	अणु0xaa, 0xa4, 0x0004पूर्ण,
	अणु0xaa, 0xa8, 0x0007पूर्ण,
	अणु0xaa, 0xac, 0x0004पूर्ण,
/*mswin-*/
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xaa, 0xfe, 0x0000पूर्ण,				/* 00,fe,00,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xbb, 0x04, 0x0400पूर्ण,				/* 04,04,00,bb */
	अणु0xdd, 0x00, 0x0100पूर्ण,				/* 00,01,00,dd */
	अणु0xbb, 0x01, 0x0400पूर्ण,				/* 04,01,00,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0002पूर्ण,				/* 00,fe,02,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xbb, 0x41, 0x2803पूर्ण,				/* 28,41,03,bb */
	अणु0xbb, 0x40, 0x2c03पूर्ण,				/* 2c,40,03,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0010पूर्ण,				/* 00,fe,10,aa */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action adcm2700_InitialScale[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,		/* 00,00,01,cc */
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,		/* 00,02,10,cc */
	अणु0xa0, 0x00, ZC3XX_R008_CLOCKSETTINGपूर्ण,		/* 00,08,03,cc */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xa0, 0xd3, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,		/* 00,8b,d3,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,	/* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,		/* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,	/* 00,05,01,cc */
	अणु0xa0, 0xd0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,	/* 00,06,d0,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,	/* 00,01,01,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,01,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,05,cc */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,		/* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,		/* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,		/* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,		/* 01,1c,00,cc */
	अणु0xa0, 0xd8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,		/* 00,9c,d8,cc */
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,		/* 00,9e,88,cc */
	अणु0xbb, 0x00, 0x0400पूर्ण,				/* 04,00,00,bb */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xbb, 0x0f, 0x140fपूर्ण,				/* 14,0f,0f,bb */
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,	/* 01,01,37,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,		/* 01,00,0d,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,		/* 01,89,06,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,		/* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,		/* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,	/* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,		/* 03,01,08,cc */
	अणु0xa0, 0x58, ZC3XX_R116_RGAINपूर्ण,			/* 01,16,58,cc */
	अणु0xa0, 0x5a, ZC3XX_R118_BGAINपूर्ण,			/* 01,18,5a,cc */
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,02,cc */
	अणु0xa0, 0xd3, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,		/* 00,8b,d3,cc */
	अणु0xbb, 0x00, 0x0408पूर्ण,				/* 04,00,08,bb */
	अणु0xdd, 0x00, 0x0200पूर्ण,				/* 00,02,00,dd */
	अणु0xbb, 0x00, 0x0400पूर्ण,				/* 04,00,00,bb */
	अणु0xdd, 0x00, 0x0050पूर्ण,				/* 00,00,50,dd */
	अणु0xbb, 0x0f, 0x140fपूर्ण,				/* 14,0f,0f,bb */
	अणु0xbb, 0xe0, 0x0c2eपूर्ण,				/* 0c,e0,2e,bb */
	अणु0xbb, 0x01, 0x2000पूर्ण,				/* 20,01,00,bb */
	अणु0xbb, 0x96, 0x2400पूर्ण,				/* 24,96,00,bb */
	अणु0xbb, 0x06, 0x1006पूर्ण,				/* 10,06,06,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xaa, 0xfe, 0x0002पूर्ण,				/* 00,fe,02,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xbb, 0x5f, 0x2090पूर्ण,				/* 20,5f,90,bb */
	अणु0xbb, 0x01, 0x8000पूर्ण,				/* 80,01,00,bb */
	अणु0xbb, 0x09, 0x8400पूर्ण,				/* 84,09,00,bb */
	अणु0xbb, 0x86, 0x0002पूर्ण,				/* 00,88,02,bb */
	अणु0xbb, 0xe6, 0x0401पूर्ण,				/* 04,e6,01,bb */
	अणु0xbb, 0x86, 0x0802पूर्ण,				/* 08,88,02,bb */
	अणु0xbb, 0xe6, 0x0c01पूर्ण,				/* 0c,e6,01,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xaa, 0xfe, 0x0000पूर्ण,				/* 00,fe,00,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0020पूर्ण,				/* 00,fe,20,aa */
	/*******/
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xaa, 0xfe, 0x0000पूर्ण,				/* 00,fe,00,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xdd, 0x00, 0x0010पूर्ण,				/* 00,00,10,dd */
	अणु0xbb, 0x04, 0x0400पूर्ण,				/* 04,04,00,bb */
	अणु0xdd, 0x00, 0x0100पूर्ण,				/* 00,01,00,dd */
	अणु0xbb, 0x01, 0x0400पूर्ण,				/* 04,01,00,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0002पूर्ण,				/* 00,fe,02,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xbb, 0x41, 0x2803पूर्ण,				/* 28,41,03,bb */
	अणु0xbb, 0x40, 0x2c03पूर्ण,				/* 2c,40,03,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0010पूर्ण,				/* 00,fe,10,aa */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action adcm2700_50HZ[] = अणु
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0002पूर्ण,				/* 00,fe,02,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xbb, 0x05, 0x8400पूर्ण,				/* 84,05,00,bb */
	अणु0xbb, 0xd0, 0xb007पूर्ण,				/* b0,d0,07,bb */
	अणु0xbb, 0xa0, 0xb80fपूर्ण,				/* b8,a0,0f,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0010पूर्ण,				/* 00,fe,10,aa */
	अणु0xaa, 0x26, 0x00d0पूर्ण,				/* 00,26,d0,aa */
	अणु0xaa, 0x28, 0x0002पूर्ण,				/* 00,28,02,aa */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action adcm2700_60HZ[] = अणु
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0002पूर्ण,				/* 00,fe,02,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xbb, 0x07, 0x8400पूर्ण,				/* 84,07,00,bb */
	अणु0xbb, 0x82, 0xb006पूर्ण,				/* b0,82,06,bb */
	अणु0xbb, 0x04, 0xb80dपूर्ण,				/* b8,04,0d,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0010पूर्ण,				/* 00,fe,10,aa */
	अणु0xaa, 0x26, 0x0057पूर्ण,				/* 00,26,57,aa */
	अणु0xaa, 0x28, 0x0002पूर्ण,				/* 00,28,02,aa */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action adcm2700_NoFliker[] = अणु
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0002पूर्ण,				/* 00,fe,02,aa */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0a,cc */
	अणु0xbb, 0x07, 0x8400पूर्ण,				/* 84,07,00,bb */
	अणु0xbb, 0x05, 0xb000पूर्ण,				/* b0,05,00,bb */
	अणु0xbb, 0xa0, 0xb801पूर्ण,				/* b8,a0,01,bb */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xaa, 0xfe, 0x0010पूर्ण,				/* 00,fe,10,aa */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action cs2102_InitialScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R080_HBLANKHIGHपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R081_HBLANKLOWपूर्ण,
	अणु0xa0, 0x30, ZC3XX_R083_RGAINADDRपूर्ण,
	अणु0xa0, 0x31, ZC3XX_R084_GGAINADDRपूर्ण,
	अणु0xa0, 0x32, ZC3XX_R085_BGAINADDRपूर्ण,
	अणु0xa0, 0x23, ZC3XX_R086_EXPTIMEHIGHपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x25, ZC3XX_R088_EXPTIMELOWपूर्ण,
	अणु0xa0, 0xb3, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* 00 */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xaa, 0x02, 0x0008पूर्ण,
	अणु0xaa, 0x03, 0x0000पूर्ण,
	अणु0xaa, 0x11, 0x0000पूर्ण,
	अणु0xaa, 0x12, 0x0089पूर्ण,
	अणु0xaa, 0x13, 0x0000पूर्ण,
	अणु0xaa, 0x14, 0x00e9पूर्ण,
	अणु0xaa, 0x20, 0x0000पूर्ण,
	अणु0xaa, 0x22, 0x0000पूर्ण,
	अणु0xaa, 0x0b, 0x0004पूर्ण,
	अणु0xaa, 0x30, 0x0030पूर्ण,
	अणु0xaa, 0x31, 0x0030पूर्ण,
	अणु0xaa, 0x32, 0x0030पूर्ण,
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x10, 0x01aeपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x68, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action cs2102_Initial[] = अणु	/* 640x480 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R080_HBLANKHIGHपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R081_HBLANKLOWपूर्ण,
	अणु0xa0, 0x30, ZC3XX_R083_RGAINADDRपूर्ण,
	अणु0xa0, 0x31, ZC3XX_R084_GGAINADDRपूर्ण,
	अणु0xa0, 0x32, ZC3XX_R085_BGAINADDRपूर्ण,
	अणु0xa0, 0x23, ZC3XX_R086_EXPTIMEHIGHपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x25, ZC3XX_R088_EXPTIMELOWपूर्ण,
	अणु0xa0, 0xb3, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* 00 */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xaa, 0x02, 0x0008पूर्ण,
	अणु0xaa, 0x03, 0x0000पूर्ण,
	अणु0xaa, 0x11, 0x0001पूर्ण,
	अणु0xaa, 0x12, 0x0087पूर्ण,
	अणु0xaa, 0x13, 0x0001पूर्ण,
	अणु0xaa, 0x14, 0x00e7पूर्ण,
	अणु0xaa, 0x20, 0x0000पूर्ण,
	अणु0xaa, 0x22, 0x0000पूर्ण,
	अणु0xaa, 0x0b, 0x0004पूर्ण,
	अणु0xaa, 0x30, 0x0030पूर्ण,
	अणु0xaa, 0x31, 0x0030पूर्ण,
	अणु0xaa, 0x32, 0x0030पूर्ण,
	अणु0xa0, 0x77, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x15, 0x01aeपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x68, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action cs2102_50HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x23, 0x0001पूर्ण,
	अणु0xaa, 0x24, 0x005fपूर्ण,
	अणु0xaa, 0x25, 0x0090पूर्ण,
	अणु0xaa, 0x21, 0x00ddपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0xbf, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x3a, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x98, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xdd, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xe4, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action cs2102_50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x23, 0x0000पूर्ण,
	अणु0xaa, 0x24, 0x00afपूर्ण,
	अणु0xaa, 0x25, 0x00c8पूर्ण,
	अणु0xaa, 0x21, 0x0068पूर्ण,
	अणु0xa0, 0x01, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x5f, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x90, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x1d, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x4c, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x68, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xe3, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action cs2102_60HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x23, 0x0001पूर्ण,
	अणु0xaa, 0x24, 0x0055पूर्ण,
	अणु0xaa, 0x25, 0x00ccपूर्ण,
	अणु0xaa, 0x21, 0x003fपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0xab, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x98, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x30, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0xd4, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x39, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x70, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xb0, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action cs2102_60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x23, 0x0000पूर्ण,
	अणु0xaa, 0x24, 0x00aaपूर्ण,
	अणु0xaa, 0x25, 0x00e6पूर्ण,
	अणु0xaa, 0x21, 0x003fपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x55, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xcc, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x6a, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x3f, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xa5, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action cs2102_NoFlikerScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x23, 0x0001पूर्ण,
	अणु0xaa, 0x24, 0x005fपूर्ण,
	अणु0xaa, 0x25, 0x0000पूर्ण,
	अणु0xaa, 0x21, 0x0001पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0xbf, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x40, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xa0, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action cs2102_NoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x23, 0x0000पूर्ण,
	अणु0xaa, 0x24, 0x00afपूर्ण,
	अणु0xaa, 0x25, 0x0080पूर्ण,
	अणु0xaa, 0x21, 0x0001पूर्ण,
	अणु0xa0, 0x01, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x5f, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x40, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xa0, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;

/* CS2102_KOCOM */
अटल स्थिर काष्ठा usb_action cs2102K_InitialScale[] = अणु
	अणु0xa0, 0x11, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xa0, 0x55, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0a, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0b, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x7c, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0xa3, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0xfb, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x09, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x11, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x12, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x15, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x16, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x17, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x78, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x20, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R088_EXPTIMELOWपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0x01, 0x01b1पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x4c, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* घड़ी ? */
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,	/* sharpness+ */
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* sharpness- */
	अणु0xa0, 0x13, ZC3XX_R120_GAMMA00पूर्ण,	/* gamma 4 */
	अणु0xa0, 0x38, ZC3XX_R121_GAMMA01पूर्ण,
	अणु0xa0, 0x59, ZC3XX_R122_GAMMA02पूर्ण,
	अणु0xa0, 0x79, ZC3XX_R123_GAMMA03पूर्ण,
	अणु0xa0, 0x92, ZC3XX_R124_GAMMA04पूर्ण,
	अणु0xa0, 0xa7, ZC3XX_R125_GAMMA05पूर्ण,
	अणु0xa0, 0xb9, ZC3XX_R126_GAMMA06पूर्ण,
	अणु0xa0, 0xc8, ZC3XX_R127_GAMMA07पूर्ण,
	अणु0xa0, 0xd4, ZC3XX_R128_GAMMA08पूर्ण,
	अणु0xa0, 0xdf, ZC3XX_R129_GAMMA09पूर्ण,
	अणु0xa0, 0xe7, ZC3XX_R12A_GAMMA0Aपूर्ण,
	अणु0xa0, 0xee, ZC3XX_R12B_GAMMA0Bपूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R12C_GAMMA0Cपूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R12D_GAMMA0Dपूर्ण,
	अणु0xa0, 0xfc, ZC3XX_R12E_GAMMA0Eपूर्ण,
	अणु0xa0, 0xff, ZC3XX_R12F_GAMMA0Fपूर्ण,
	अणु0xa0, 0x26, ZC3XX_R130_GAMMA10पूर्ण,
	अणु0xa0, 0x22, ZC3XX_R131_GAMMA11पूर्ण,
	अणु0xa0, 0x20, ZC3XX_R132_GAMMA12पूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R133_GAMMA13पूर्ण,
	अणु0xa0, 0x16, ZC3XX_R134_GAMMA14पूर्ण,
	अणु0xa0, 0x13, ZC3XX_R135_GAMMA15पूर्ण,
	अणु0xa0, 0x10, ZC3XX_R136_GAMMA16पूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R137_GAMMA17पूर्ण,
	अणु0xa0, 0x0b, ZC3XX_R138_GAMMA18पूर्ण,
	अणु0xa0, 0x09, ZC3XX_R139_GAMMA19पूर्ण,
	अणु0xa0, 0x07, ZC3XX_R13A_GAMMA1Aपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R13B_GAMMA1Bपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R13C_GAMMA1Cपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R13D_GAMMA1Dपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R13E_GAMMA1Eपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R13F_GAMMA1Fपूर्ण,
	अणु0xa0, 0x58, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xf4, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x58, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x58, ZC3XX_R112_RGB22पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x22, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x22, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण,
	अणु0xa0, 0x22, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xee, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x3a, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x28, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x19, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x1f, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x4c, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x5c, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x5c, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x96, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x96, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action cs2102K_Initial[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
/*fixme: next sequence = i2c exchanges*/
	अणु0xa0, 0x55, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0a, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0b, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x7b, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0xa3, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0xfb, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x09, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x11, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x12, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x15, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x16, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x17, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x78, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x20, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R088_EXPTIMELOWपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0x01, 0x01b1पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x4c, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* घड़ी ? */
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,	/* sharpness+ */
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* sharpness- */
	अणु0xa0, 0x13, ZC3XX_R120_GAMMA00पूर्ण,	/* gamma 4 */
	अणु0xa0, 0x38, ZC3XX_R121_GAMMA01पूर्ण,
	अणु0xa0, 0x59, ZC3XX_R122_GAMMA02पूर्ण,
	अणु0xa0, 0x79, ZC3XX_R123_GAMMA03पूर्ण,
	अणु0xa0, 0x92, ZC3XX_R124_GAMMA04पूर्ण,
	अणु0xa0, 0xa7, ZC3XX_R125_GAMMA05पूर्ण,
	अणु0xa0, 0xb9, ZC3XX_R126_GAMMA06पूर्ण,
	अणु0xa0, 0xc8, ZC3XX_R127_GAMMA07पूर्ण,
	अणु0xa0, 0xd4, ZC3XX_R128_GAMMA08पूर्ण,
	अणु0xa0, 0xdf, ZC3XX_R129_GAMMA09पूर्ण,
	अणु0xa0, 0xe7, ZC3XX_R12A_GAMMA0Aपूर्ण,
	अणु0xa0, 0xee, ZC3XX_R12B_GAMMA0Bपूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R12C_GAMMA0Cपूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R12D_GAMMA0Dपूर्ण,
	अणु0xa0, 0xfc, ZC3XX_R12E_GAMMA0Eपूर्ण,
	अणु0xa0, 0xff, ZC3XX_R12F_GAMMA0Fपूर्ण,
	अणु0xa0, 0x26, ZC3XX_R130_GAMMA10पूर्ण,
	अणु0xa0, 0x22, ZC3XX_R131_GAMMA11पूर्ण,
	अणु0xa0, 0x20, ZC3XX_R132_GAMMA12पूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R133_GAMMA13पूर्ण,
	अणु0xa0, 0x16, ZC3XX_R134_GAMMA14पूर्ण,
	अणु0xa0, 0x13, ZC3XX_R135_GAMMA15पूर्ण,
	अणु0xa0, 0x10, ZC3XX_R136_GAMMA16पूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R137_GAMMA17पूर्ण,
	अणु0xa0, 0x0b, ZC3XX_R138_GAMMA18पूर्ण,
	अणु0xa0, 0x09, ZC3XX_R139_GAMMA19पूर्ण,
	अणु0xa0, 0x07, ZC3XX_R13A_GAMMA1Aपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R13B_GAMMA1Bपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R13C_GAMMA1Cपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R13D_GAMMA1Dपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R13E_GAMMA1Eपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R13F_GAMMA1Fपूर्ण,
	अणु0xa0, 0x58, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xf4, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x58, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x58, ZC3XX_R112_RGB22पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x22, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x22, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण,
	अणु0xa0, 0x22, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xee, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x3a, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x28, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x19, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x1f, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x4c, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x5c, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x5c, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x96, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x96, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
/*fixme:what करोes the next sequence?*/
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x0a, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x0a, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x44, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x44, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x21, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x7e, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x7e, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R094_I2CWRITEACKपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action gc0305_Initial[] = अणु	/* 640x480 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,	/* 00,00,01,cc */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* 00,08,03,cc */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xa0, 0x04, ZC3XX_R002_CLOCKSELECTपूर्ण,	/* 00,02,04,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,	/* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,	/* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,	/* 00,05,01,cc */
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,	/* 00,06,e0,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,	/* 00,01,01,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,01,cc */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,	/* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,	/* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,	/* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,	/* 01,1c,00,cc */
	अणु0xa0, 0xe6, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,	/* 00,9c,e6,cc */
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण,	/* 00,9e,86,cc */
	अणु0xa0, 0x98, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,	/* 00,8b,98,cc */
	अणु0xaa, 0x13, 0x0002पूर्ण,	/* 00,13,02,aa */
	अणु0xaa, 0x15, 0x0003पूर्ण,	/* 00,15,03,aa */
	अणु0xaa, 0x01, 0x0000पूर्ण,	/* 00,01,00,aa */
	अणु0xaa, 0x02, 0x0000पूर्ण,	/* 00,02,00,aa */
	अणु0xaa, 0x1a, 0x0000पूर्ण,	/* 00,1a,00,aa */
	अणु0xaa, 0x1c, 0x0017पूर्ण,	/* 00,1c,17,aa */
	अणु0xaa, 0x1d, 0x0080पूर्ण,	/* 00,1d,80,aa */
	अणु0xaa, 0x1f, 0x0008पूर्ण,	/* 00,1f,08,aa */
	अणु0xaa, 0x21, 0x0012पूर्ण,	/* 00,21,12,aa */
	अणु0xa0, 0x82, ZC3XX_R086_EXPTIMEHIGHपूर्ण,	/* 00,86,82,cc */
	अणु0xa0, 0x83, ZC3XX_R087_EXPTIMEMIDपूर्ण,	/* 00,87,83,cc */
	अणु0xa0, 0x84, ZC3XX_R088_EXPTIMELOWपूर्ण,	/* 00,88,84,cc */
	अणु0xaa, 0x05, 0x0000पूर्ण,	/* 00,05,00,aa */
	अणु0xaa, 0x0a, 0x0000पूर्ण,	/* 00,0a,00,aa */
	अणु0xaa, 0x0b, 0x00b0पूर्ण,	/* 00,0b,b0,aa */
	अणु0xaa, 0x0c, 0x0000पूर्ण,	/* 00,0c,00,aa */
	अणु0xaa, 0x0d, 0x00b0पूर्ण,	/* 00,0d,b0,aa */
	अणु0xaa, 0x0e, 0x0000पूर्ण,	/* 00,0e,00,aa */
	अणु0xaa, 0x0f, 0x00b0पूर्ण,	/* 00,0f,b0,aa */
	अणु0xaa, 0x10, 0x0000पूर्ण,	/* 00,10,00,aa */
	अणु0xaa, 0x11, 0x00b0पूर्ण,	/* 00,11,b0,aa */
	अणु0xaa, 0x16, 0x0001पूर्ण,	/* 00,16,01,aa */
	अणु0xaa, 0x17, 0x00e6पूर्ण,	/* 00,17,e6,aa */
	अणु0xaa, 0x18, 0x0002पूर्ण,	/* 00,18,02,aa */
	अणु0xaa, 0x19, 0x0086पूर्ण,	/* 00,19,86,aa */
	अणु0xaa, 0x20, 0x0000पूर्ण,	/* 00,20,00,aa */
	अणु0xaa, 0x1b, 0x0020पूर्ण,	/* 00,1b,20,aa */
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,	/* 01,01,b7,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,05,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,	/* 01,00,0d,cc */
	अणु0xa0, 0x76, ZC3XX_R189_AWBSTATUSपूर्ण,	/* 01,89,76,cc */
	अणु0xa0, 0x09, 0x01adपूर्ण,	/* 01,ad,09,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,	/* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,	/* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,	/* 03,01,08,cc */
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,	/* 01,a8,60,cc */
	अणु0xa0, 0x85, ZC3XX_R18D_YTARGETपूर्ण,	/* 01,8d,85,cc */
	अणु0xa0, 0x00, 0x011eपूर्ण,	/* 01,1e,00,cc */
	अणु0xa0, 0x52, ZC3XX_R116_RGAINपूर्ण,	/* 01,16,52,cc */
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,	/* 01,17,40,cc */
	अणु0xa0, 0x52, ZC3XX_R118_BGAINपूर्ण,	/* 01,18,52,cc */
	अणु0xa0, 0x03, ZC3XX_R113_RGB03पूर्ण,	/* 01,13,03,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action gc0305_InitialScale[] = अणु /* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,	/* 00,00,01,cc */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* 00,08,03,cc */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc */
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,	/* 00,02,10,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,	/* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,	/* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,	/* 00,05,01,cc */
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,	/* 00,06,e0,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,	/* 00,01,01,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,01,cc */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,	/* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,	/* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,	/* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,	/* 01,1c,00,cc */
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,	/* 00,9c,e8,cc */
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,	/* 00,9e,88,cc */
	अणु0xa0, 0x98, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,	/* 00,8b,98,cc */
	अणु0xaa, 0x13, 0x0000पूर्ण,	/* 00,13,00,aa */
	अणु0xaa, 0x15, 0x0001पूर्ण,	/* 00,15,01,aa */
	अणु0xaa, 0x01, 0x0000पूर्ण,	/* 00,01,00,aa */
	अणु0xaa, 0x02, 0x0000पूर्ण,	/* 00,02,00,aa */
	अणु0xaa, 0x1a, 0x0000पूर्ण,	/* 00,1a,00,aa */
	अणु0xaa, 0x1c, 0x0017पूर्ण,	/* 00,1c,17,aa */
	अणु0xaa, 0x1d, 0x0080पूर्ण,	/* 00,1d,80,aa */
	अणु0xaa, 0x1f, 0x0008पूर्ण,	/* 00,1f,08,aa */
	अणु0xaa, 0x21, 0x0012पूर्ण,	/* 00,21,12,aa */
	अणु0xa0, 0x82, ZC3XX_R086_EXPTIMEHIGHपूर्ण,	/* 00,86,82,cc */
	अणु0xa0, 0x83, ZC3XX_R087_EXPTIMEMIDपूर्ण,	/* 00,87,83,cc */
	अणु0xa0, 0x84, ZC3XX_R088_EXPTIMELOWपूर्ण,	/* 00,88,84,cc */
	अणु0xaa, 0x05, 0x0000पूर्ण,	/* 00,05,00,aa */
	अणु0xaa, 0x0a, 0x0000पूर्ण,	/* 00,0a,00,aa */
	अणु0xaa, 0x0b, 0x00b0पूर्ण,	/* 00,0b,b0,aa */
	अणु0xaa, 0x0c, 0x0000पूर्ण,	/* 00,0c,00,aa */
	अणु0xaa, 0x0d, 0x00b0पूर्ण,	/* 00,0d,b0,aa */
	अणु0xaa, 0x0e, 0x0000पूर्ण,	/* 00,0e,00,aa */
	अणु0xaa, 0x0f, 0x00b0पूर्ण,	/* 00,0f,b0,aa */
	अणु0xaa, 0x10, 0x0000पूर्ण,	/* 00,10,00,aa */
	अणु0xaa, 0x11, 0x00b0पूर्ण,	/* 00,11,b0,aa */
	अणु0xaa, 0x16, 0x0001पूर्ण,	/* 00,16,01,aa */
	अणु0xaa, 0x17, 0x00e8पूर्ण,	/* 00,17,e8,aa */
	अणु0xaa, 0x18, 0x0002पूर्ण,	/* 00,18,02,aa */
	अणु0xaa, 0x19, 0x0088पूर्ण,	/* 00,19,88,aa */
	अणु0xaa, 0x20, 0x0000पूर्ण,	/* 00,20,00,aa */
	अणु0xaa, 0x1b, 0x0020पूर्ण,	/* 00,1b,20,aa */
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,	/* 01,01,b7,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,05,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,	/* 01,00,0d,cc */
	अणु0xa0, 0x76, ZC3XX_R189_AWBSTATUSपूर्ण,	/* 01,89,76,cc */
	अणु0xa0, 0x09, 0x01adपूर्ण,	/* 01,ad,09,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,	/* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,	/* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,	/* 03,01,08,cc */
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,	/* 01,a8,60,cc */
	अणु0xa0, 0x00, 0x011eपूर्ण,	/* 01,1e,00,cc */
	अणु0xa0, 0x52, ZC3XX_R116_RGAINपूर्ण,	/* 01,16,52,cc */
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,	/* 01,17,40,cc */
	अणु0xa0, 0x52, ZC3XX_R118_BGAINपूर्ण,	/* 01,18,52,cc */
	अणु0xa0, 0x03, ZC3XX_R113_RGB03पूर्ण,	/* 01,13,03,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action gc0305_50HZ[] = अणु
	अणु0xaa, 0x82, 0x0000पूर्ण,	/* 00,82,00,aa */
	अणु0xaa, 0x83, 0x0002पूर्ण,	/* 00,83,02,aa */
	अणु0xaa, 0x84, 0x0038पूर्ण,	/* 00,84,38,aa */	/* win: 00,84,ec */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x0b, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,0b,cc */
	अणु0xa0, 0x18, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,18,cc */
							/* win: 01,92,10 */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0x8e, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,8e,cc */
							/* win: 01,97,ec */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,0e,cc */
	अणु0xa0, 0x15, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,15,cc */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,10,cc */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,	/* 00,1d,62,cc */
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,	/* 00,1e,90,cc */
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,	/* 00,1f,c8,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,	/* 00,20,ff,cc */
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,	/* 01,1d,60,cc */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,42,cc */
/*	अणु0xa0, 0x85, ZC3XX_R18D_YTARGETपूर्ण,	 * 01,8d,85,cc *
						 * अगर 640x480 */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action gc0305_60HZ[] = अणु
	अणु0xaa, 0x82, 0x0000पूर्ण,	/* 00,82,00,aa */
	अणु0xaa, 0x83, 0x0000पूर्ण,	/* 00,83,00,aa */
	अणु0xaa, 0x84, 0x00ecपूर्ण,	/* 00,84,ec,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x0b, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,0b,cc */
	अणु0xa0, 0x10, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,10,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0xec, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,ec,cc */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,0e,cc */
	अणु0xa0, 0x15, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,15,cc */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,10,cc */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,	/* 00,1d,62,cc */
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,	/* 00,1e,90,cc */
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,	/* 00,1f,c8,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,	/* 00,20,ff,cc */
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,	/* 01,1d,60,cc */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,42,cc */
	अणु0xa0, 0x80, ZC3XX_R18D_YTARGETपूर्ण,	/* 01,8d,80,cc */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action gc0305_NoFliker[] = अणु
	अणु0xa0, 0x0c, ZC3XX_R100_OPERATIONMODEपूर्ण,	/* 01,00,0c,cc */
	अणु0xaa, 0x82, 0x0000पूर्ण,	/* 00,82,00,aa */
	अणु0xaa, 0x83, 0x0000पूर्ण,	/* 00,83,00,aa */
	अणु0xaa, 0x84, 0x0020पूर्ण,	/* 00,84,20,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x00, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,00,cc */
	अणु0xa0, 0x48, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,48,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0x10, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,10,cc */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,0e,cc */
	अणु0xa0, 0x15, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,15,cc */
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,	/* 00,1d,62,cc */
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,	/* 00,1e,90,cc */
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,	/* 00,1f,c8,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,	/* 00,20,ff,cc */
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,	/* 01,1d,60,cc */
	अणु0xa0, 0x03, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,03,cc */
	अणु0xa0, 0x80, ZC3XX_R18D_YTARGETपूर्ण,	/* 01,8d,80,cc */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action hdcs2020_InitialScale[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x11, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* qtable 0x05 */
	अणु0xa0, 0x08, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xaa, 0x1c, 0x0000पूर्ण,
	अणु0xaa, 0x0a, 0x0001पूर्ण,
	अणु0xaa, 0x0b, 0x0006पूर्ण,
	अणु0xaa, 0x0c, 0x007bपूर्ण,
	अणु0xaa, 0x0d, 0x00a7पूर्ण,
	अणु0xaa, 0x03, 0x00fbपूर्ण,
	अणु0xaa, 0x05, 0x0000पूर्ण,
	अणु0xaa, 0x06, 0x0003पूर्ण,
	अणु0xaa, 0x09, 0x0008पूर्ण,

	अणु0xaa, 0x0f, 0x0018पूर्ण,	/* set sensor gain */
	अणु0xaa, 0x10, 0x0018पूर्ण,
	अणु0xaa, 0x11, 0x0018पूर्ण,
	अणु0xaa, 0x12, 0x0018पूर्ण,

	अणु0xaa, 0x15, 0x004eपूर्ण,
	अणु0xaa, 0x1c, 0x0004पूर्ण,
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x70, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa1, 0x01, 0x0002पूर्ण,
	अणु0xa1, 0x01, 0x0008पूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa1, 0x01, 0x0008पूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* घड़ी ? */
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,	/* sharpness+ */
	अणु0xa1, 0x01, 0x01c8पूर्ण,
	अणु0xa1, 0x01, 0x01c9पूर्ण,
	अणु0xa1, 0x01, 0x01caपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* sharpness- */
	अणु0xa0, 0x13, ZC3XX_R120_GAMMA00पूर्ण,	/* gamma 4 */
	अणु0xa0, 0x38, ZC3XX_R121_GAMMA01पूर्ण,
	अणु0xa0, 0x59, ZC3XX_R122_GAMMA02पूर्ण,
	अणु0xa0, 0x79, ZC3XX_R123_GAMMA03पूर्ण,
	अणु0xa0, 0x92, ZC3XX_R124_GAMMA04पूर्ण,
	अणु0xa0, 0xa7, ZC3XX_R125_GAMMA05पूर्ण,
	अणु0xa0, 0xb9, ZC3XX_R126_GAMMA06पूर्ण,
	अणु0xa0, 0xc8, ZC3XX_R127_GAMMA07पूर्ण,
	अणु0xa0, 0xd4, ZC3XX_R128_GAMMA08पूर्ण,
	अणु0xa0, 0xdf, ZC3XX_R129_GAMMA09पूर्ण,
	अणु0xa0, 0xe7, ZC3XX_R12A_GAMMA0Aपूर्ण,
	अणु0xa0, 0xee, ZC3XX_R12B_GAMMA0Bपूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R12C_GAMMA0Cपूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R12D_GAMMA0Dपूर्ण,
	अणु0xa0, 0xfc, ZC3XX_R12E_GAMMA0Eपूर्ण,
	अणु0xa0, 0xff, ZC3XX_R12F_GAMMA0Fपूर्ण,
	अणु0xa0, 0x26, ZC3XX_R130_GAMMA10पूर्ण,
	अणु0xa0, 0x22, ZC3XX_R131_GAMMA11पूर्ण,
	अणु0xa0, 0x20, ZC3XX_R132_GAMMA12पूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R133_GAMMA13पूर्ण,
	अणु0xa0, 0x16, ZC3XX_R134_GAMMA14पूर्ण,
	अणु0xa0, 0x13, ZC3XX_R135_GAMMA15पूर्ण,
	अणु0xa0, 0x10, ZC3XX_R136_GAMMA16पूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R137_GAMMA17पूर्ण,
	अणु0xa0, 0x0b, ZC3XX_R138_GAMMA18पूर्ण,
	अणु0xa0, 0x09, ZC3XX_R139_GAMMA19पूर्ण,
	अणु0xa0, 0x07, ZC3XX_R13A_GAMMA1Aपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R13B_GAMMA1Bपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R13C_GAMMA1Cपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R13D_GAMMA1Dपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R13E_GAMMA1Eपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R13F_GAMMA1Fपूर्ण,

	अणु0xa0, 0x66, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xed, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x66, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x66, ZC3XX_R112_RGB22पूर्ण,

	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x13, 0x0031पूर्ण,
	अणु0xaa, 0x14, 0x0001पूर्ण,
	अणु0xaa, 0x0e, 0x0004पूर्ण,
	अणु0xaa, 0x19, 0x00cdपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x62, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x3d, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,

	अणु0xa0, 0x0c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 0x14 */
	अणु0xa0, 0x28, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x18, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x2c, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x41, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hdcs2020_Initial[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xaa, 0x1c, 0x0000पूर्ण,
	अणु0xaa, 0x0a, 0x0001पूर्ण,
	अणु0xaa, 0x0b, 0x0006पूर्ण,
	अणु0xaa, 0x0c, 0x007aपूर्ण,
	अणु0xaa, 0x0d, 0x00a7पूर्ण,
	अणु0xaa, 0x03, 0x00fbपूर्ण,
	अणु0xaa, 0x05, 0x0000पूर्ण,
	अणु0xaa, 0x06, 0x0003पूर्ण,
	अणु0xaa, 0x09, 0x0008पूर्ण,
	अणु0xaa, 0x0f, 0x0018पूर्ण,	/* original setting */
	अणु0xaa, 0x10, 0x0018पूर्ण,
	अणु0xaa, 0x11, 0x0018पूर्ण,
	अणु0xaa, 0x12, 0x0018पूर्ण,
	अणु0xaa, 0x15, 0x004eपूर्ण,
	अणु0xaa, 0x1c, 0x0004पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x70, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa1, 0x01, 0x0002पूर्ण,
	अणु0xa1, 0x01, 0x0008पूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa1, 0x01, 0x0008पूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* घड़ी ? */
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,	/* sharpness+ */
	अणु0xa1, 0x01, 0x01c8पूर्ण,
	अणु0xa1, 0x01, 0x01c9पूर्ण,
	अणु0xa1, 0x01, 0x01caपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* sharpness- */
	अणु0xa0, 0x13, ZC3XX_R120_GAMMA00पूर्ण,	/* gamma 4 */
	अणु0xa0, 0x38, ZC3XX_R121_GAMMA01पूर्ण,
	अणु0xa0, 0x59, ZC3XX_R122_GAMMA02पूर्ण,
	अणु0xa0, 0x79, ZC3XX_R123_GAMMA03पूर्ण,
	अणु0xa0, 0x92, ZC3XX_R124_GAMMA04पूर्ण,
	अणु0xa0, 0xa7, ZC3XX_R125_GAMMA05पूर्ण,
	अणु0xa0, 0xb9, ZC3XX_R126_GAMMA06पूर्ण,
	अणु0xa0, 0xc8, ZC3XX_R127_GAMMA07पूर्ण,
	अणु0xa0, 0xd4, ZC3XX_R128_GAMMA08पूर्ण,
	अणु0xa0, 0xdf, ZC3XX_R129_GAMMA09पूर्ण,
	अणु0xa0, 0xe7, ZC3XX_R12A_GAMMA0Aपूर्ण,
	अणु0xa0, 0xee, ZC3XX_R12B_GAMMA0Bपूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R12C_GAMMA0Cपूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R12D_GAMMA0Dपूर्ण,
	अणु0xa0, 0xfc, ZC3XX_R12E_GAMMA0Eपूर्ण,
	अणु0xa0, 0xff, ZC3XX_R12F_GAMMA0Fपूर्ण,
	अणु0xa0, 0x26, ZC3XX_R130_GAMMA10पूर्ण,
	अणु0xa0, 0x22, ZC3XX_R131_GAMMA11पूर्ण,
	अणु0xa0, 0x20, ZC3XX_R132_GAMMA12पूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R133_GAMMA13पूर्ण,
	अणु0xa0, 0x16, ZC3XX_R134_GAMMA14पूर्ण,
	अणु0xa0, 0x13, ZC3XX_R135_GAMMA15पूर्ण,
	अणु0xa0, 0x10, ZC3XX_R136_GAMMA16पूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R137_GAMMA17पूर्ण,
	अणु0xa0, 0x0b, ZC3XX_R138_GAMMA18पूर्ण,
	अणु0xa0, 0x09, ZC3XX_R139_GAMMA19पूर्ण,
	अणु0xa0, 0x07, ZC3XX_R13A_GAMMA1Aपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R13B_GAMMA1Bपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R13C_GAMMA1Cपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R13D_GAMMA1Dपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R13E_GAMMA1Eपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R13F_GAMMA1Fपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xed, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x66, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xed, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x66, ZC3XX_R112_RGB22पूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
 /**** set exposure ***/
	अणु0xaa, 0x13, 0x0031पूर्ण,
	अणु0xaa, 0x14, 0x0001पूर्ण,
	अणु0xaa, 0x0e, 0x0004पूर्ण,
	अणु0xaa, 0x19, 0x00cdपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x62, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x3d, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x28, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x18, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x2c, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x41, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hdcs2020_50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0x13, 0x0018पूर्ण,			/* 00,13,18,aa */
	अणु0xaa, 0x14, 0x0001पूर्ण,			/* 00,14,01,aa */
	अणु0xaa, 0x0e, 0x0005पूर्ण,			/* 00,0e,05,aa */
	अणु0xaa, 0x19, 0x001fपूर्ण,			/* 00,19,1f,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x02, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,02,cc */
	अणु0xa0, 0x76, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,76,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x46, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,46,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,20,cc */
	अणु0xa0, 0x0c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,0c,cc */
	अणु0xa0, 0x28, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,28,cc */
	अणु0xa0, 0x05, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,05,cc */
	अणु0xa0, 0x1a, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,1a,cc */
	अणु0xa0, 0x2f, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,2f,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hdcs2020_60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0x13, 0x0031पूर्ण,			/* 00,13,31,aa */
	अणु0xaa, 0x14, 0x0001पूर्ण,			/* 00,14,01,aa */
	अणु0xaa, 0x0e, 0x0004पूर्ण,			/* 00,0e,04,aa */
	अणु0xaa, 0x19, 0x00cdपूर्ण,			/* 00,19,cd,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x02, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,02,cc */
	अणु0xa0, 0x62, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,62,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x3d, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,3d,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,20,cc */
	अणु0xa0, 0x0c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,0c,cc */
	अणु0xa0, 0x28, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,28,cc */
	अणु0xa0, 0x04, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,04,cc */
	अणु0xa0, 0x18, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,18,cc */
	अणु0xa0, 0x2c, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,2c,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hdcs2020_NoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0x13, 0x0010पूर्ण,			/* 00,13,10,aa */
	अणु0xaa, 0x14, 0x0001पूर्ण,			/* 00,14,01,aa */
	अणु0xaa, 0x0e, 0x0004पूर्ण,			/* 00,0e,04,aa */
	अणु0xaa, 0x19, 0x0000पूर्ण,			/* 00,19,00,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x02, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,02,cc */
	अणु0xa0, 0x70, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,70,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x10, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,10,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,20,cc */
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,00,cc */
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,00,cc */
	अणु0xa0, 0x04, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,04,cc */
	अणु0xa0, 0x17, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,17,cc */
	अणु0xa0, 0x2a, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,2a,cc */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action hv7131b_InitialScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x77, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* 00 */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xaa, 0x30, 0x002dपूर्ण,
	अणु0xaa, 0x01, 0x0005पूर्ण,
	अणु0xaa, 0x11, 0x0000पूर्ण,
	अणु0xaa, 0x13, 0x0001पूर्ण,	/* अणु0xaa, 0x13, 0x0000पूर्ण, */
	अणु0xaa, 0x14, 0x0001पूर्ण,
	अणु0xaa, 0x15, 0x00e8पूर्ण,
	अणु0xaa, 0x16, 0x0002पूर्ण,
	अणु0xaa, 0x17, 0x0086पूर्ण,		/* 00,17,88,aa */
	अणु0xaa, 0x31, 0x0038पूर्ण,
	अणु0xaa, 0x32, 0x0038पूर्ण,
	अणु0xaa, 0x33, 0x0038पूर्ण,
	अणु0xaa, 0x5b, 0x0001पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x68, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0xc0, 0x019bपूर्ण,
	अणु0xa0, 0xa0, 0x019cपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R188_MINGAINपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xaa, 0x02, 0x0090पूर्ण,			/* 00,02,80,aa */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action hv7131b_Initial[] = अणु	/* 640x480*/
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* 00 */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xaa, 0x30, 0x002dपूर्ण,
	अणु0xaa, 0x01, 0x0005पूर्ण,
	अणु0xaa, 0x11, 0x0001पूर्ण,
	अणु0xaa, 0x13, 0x0000पूर्ण,	/* अणु0xaa, 0x13, 0x0001पूर्ण; */
	अणु0xaa, 0x14, 0x0001पूर्ण,
	अणु0xaa, 0x15, 0x00e6पूर्ण,
	अणु0xaa, 0x16, 0x0002पूर्ण,
	अणु0xaa, 0x17, 0x0086पूर्ण,
	अणु0xaa, 0x31, 0x0038पूर्ण,
	अणु0xaa, 0x32, 0x0038पूर्ण,
	अणु0xaa, 0x33, 0x0038पूर्ण,
	अणु0xaa, 0x5b, 0x0001पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x70, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0xc0, 0x019bपूर्ण,
	अणु0xa0, 0xa0, 0x019cपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R188_MINGAINपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xaa, 0x02, 0x0090पूर्ण,	/* अणु0xaa, 0x02, 0x0080पूर्ण, */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131b_50HZ[] = अणु	/* 640x480*/
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,	/* 00,19,00,cc */
	अणु0xaa, 0x25, 0x0007पूर्ण,			/* 00,25,07,aa */
	अणु0xaa, 0x26, 0x0053पूर्ण,			/* 00,26,53,aa */
	अणु0xaa, 0x27, 0x0000पूर्ण,			/* 00,27,00,aa */
	अणु0xaa, 0x20, 0x0000पूर्ण,			/* 00,20,00,aa */
	अणु0xaa, 0x21, 0x0050पूर्ण,			/* 00,21,50,aa */
	अणु0xaa, 0x22, 0x001bपूर्ण,			/* 00,22,1b,aa */
	अणु0xaa, 0x23, 0x00fcपूर्ण,			/* 00,23,fc,aa */
	अणु0xa0, 0x2f, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,2f,cc */
	अणु0xa0, 0x9b, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,9b,cc */
	अणु0xa0, 0x80, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,80,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0xea, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,ea,cc */
	अणु0xa0, 0x60, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,60,cc */
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,0c,cc */
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,18,cc */
	अणु0xa0, 0x18, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,18,cc */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,	/* 00,1d,00,cc */
	अणु0xa0, 0x50, ZC3XX_R01E_HSYNC_1पूर्ण,	/* 00,1e,50,cc */
	अणु0xa0, 0x1b, ZC3XX_R01F_HSYNC_2पूर्ण,	/* 00,1f,1b,cc */
	अणु0xa0, 0xfc, ZC3XX_R020_HSYNC_3पूर्ण,	/* 00,20,fc,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131b_50HZScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,	/* 00,19,00,cc */
	अणु0xaa, 0x25, 0x0007पूर्ण,			/* 00,25,07,aa */
	अणु0xaa, 0x26, 0x0053पूर्ण,			/* 00,26,53,aa */
	अणु0xaa, 0x27, 0x0000पूर्ण,			/* 00,27,00,aa */
	अणु0xaa, 0x20, 0x0000पूर्ण,			/* 00,20,00,aa */
	अणु0xaa, 0x21, 0x0050पूर्ण,			/* 00,21,50,aa */
	अणु0xaa, 0x22, 0x0012पूर्ण,			/* 00,22,12,aa */
	अणु0xaa, 0x23, 0x0080पूर्ण,			/* 00,23,80,aa */
	अणु0xa0, 0x2f, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,2f,cc */
	अणु0xa0, 0x9b, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,9b,cc */
	अणु0xa0, 0x80, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,80,cc */
	अणु0xa0, 0x01, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,01,cc */
	अणु0xa0, 0xd4, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,d4,cc */
	अणु0xa0, 0xc0, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,c0,cc */
	अणु0xa0, 0x07, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,07,cc */
	अणु0xa0, 0x0f, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,0f,cc */
	अणु0xa0, 0x18, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,18,cc */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,	/* 00,1d,00,cc */
	अणु0xa0, 0x50, ZC3XX_R01E_HSYNC_1पूर्ण,	/* 00,1e,50,cc */
	अणु0xa0, 0x12, ZC3XX_R01F_HSYNC_2पूर्ण,	/* 00,1f,12,cc */
	अणु0xa0, 0x80, ZC3XX_R020_HSYNC_3पूर्ण,	/* 00,20,80,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131b_60HZ[] = अणु	/* 640x480*/
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,	/* 00,19,00,cc */
	अणु0xaa, 0x25, 0x0007पूर्ण,			/* 00,25,07,aa */
	अणु0xaa, 0x26, 0x00a1पूर्ण,			/* 00,26,a1,aa */
	अणु0xaa, 0x27, 0x0020पूर्ण,			/* 00,27,20,aa */
	अणु0xaa, 0x20, 0x0000पूर्ण,			/* 00,20,00,aa */
	अणु0xaa, 0x21, 0x0040पूर्ण,			/* 00,21,40,aa */
	अणु0xaa, 0x22, 0x0013पूर्ण,			/* 00,22,13,aa */
	अणु0xaa, 0x23, 0x004cपूर्ण,			/* 00,23,4c,aa */
	अणु0xa0, 0x2f, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,2f,cc */
	अणु0xa0, 0x4d, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,4d,cc */
	अणु0xa0, 0x60, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,60,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0xc3, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,c3,cc */
	अणु0xa0, 0x50, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,50,cc */
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,0c,cc */
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,18,cc */
	अणु0xa0, 0x18, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,18,cc */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,	/* 00,1d,00,cc */
	अणु0xa0, 0x40, ZC3XX_R01E_HSYNC_1पूर्ण,	/* 00,1e,40,cc */
	अणु0xa0, 0x13, ZC3XX_R01F_HSYNC_2पूर्ण,	/* 00,1f,13,cc */
	अणु0xa0, 0x4c, ZC3XX_R020_HSYNC_3पूर्ण,	/* 00,20,4c,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131b_60HZScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,	/* 00,19,00,cc */
	अणु0xaa, 0x25, 0x0007पूर्ण,			/* 00,25,07,aa */
	अणु0xaa, 0x26, 0x00a1पूर्ण,			/* 00,26,a1,aa */
	अणु0xaa, 0x27, 0x0020पूर्ण,			/* 00,27,20,aa */
	अणु0xaa, 0x20, 0x0000पूर्ण,			/* 00,20,00,aa */
	अणु0xaa, 0x21, 0x00a0पूर्ण,			/* 00,21,a0,aa */
	अणु0xaa, 0x22, 0x0016पूर्ण,			/* 00,22,16,aa */
	अणु0xaa, 0x23, 0x0040पूर्ण,			/* 00,23,40,aa */
	अणु0xa0, 0x2f, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,2f,cc */
	अणु0xa0, 0x4d, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,4d,cc */
	अणु0xa0, 0x60, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,60,cc */
	अणु0xa0, 0x01, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,01,cc */
	अणु0xa0, 0x86, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,86,cc */
	अणु0xa0, 0xa0, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,a0,cc */
	अणु0xa0, 0x07, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,07,cc */
	अणु0xa0, 0x0f, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,0f,cc */
	अणु0xa0, 0x18, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,18,cc */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,	/* 00,1d,00,cc */
	अणु0xa0, 0xa0, ZC3XX_R01E_HSYNC_1पूर्ण,	/* 00,1e,a0,cc */
	अणु0xa0, 0x16, ZC3XX_R01F_HSYNC_2पूर्ण,	/* 00,1f,16,cc */
	अणु0xa0, 0x40, ZC3XX_R020_HSYNC_3पूर्ण,	/* 00,20,40,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131b_NoFliker[] = अणु	/* 640x480*/
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,	/* 00,19,00,cc */
	अणु0xaa, 0x25, 0x0003पूर्ण,			/* 00,25,03,aa */
	अणु0xaa, 0x26, 0x0000पूर्ण,			/* 00,26,00,aa */
	अणु0xaa, 0x27, 0x0000पूर्ण,			/* 00,27,00,aa */
	अणु0xaa, 0x20, 0x0000पूर्ण,			/* 00,20,00,aa */
	अणु0xaa, 0x21, 0x0010पूर्ण,			/* 00,21,10,aa */
	अणु0xaa, 0x22, 0x0000पूर्ण,			/* 00,22,00,aa */
	अणु0xaa, 0x23, 0x0003पूर्ण,			/* 00,23,03,aa */
	अणु0xa0, 0x2f, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,2f,cc */
	अणु0xa0, 0xf8, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,f8,cc */
	अणु0xa0, 0x00, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,00,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x02, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,02,cc */
	अणु0xa0, 0x00, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,00,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,20,cc */
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,00,cc */
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,00,cc */
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,	/* 00,1d,00,cc */
	अणु0xa0, 0x10, ZC3XX_R01E_HSYNC_1पूर्ण,	/* 00,1e,10,cc */
	अणु0xa0, 0x00, ZC3XX_R01F_HSYNC_2पूर्ण,	/* 00,1f,00,cc */
	अणु0xa0, 0x03, ZC3XX_R020_HSYNC_3पूर्ण,	/* 00,20,03,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131b_NoFlikerScale[] = अणु /* 320x240 */
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,	/* 00,19,00,cc */
	अणु0xaa, 0x25, 0x0003पूर्ण,			/* 00,25,03,aa */
	अणु0xaa, 0x26, 0x0000पूर्ण,			/* 00,26,00,aa */
	अणु0xaa, 0x27, 0x0000पूर्ण,			/* 00,27,00,aa */
	अणु0xaa, 0x20, 0x0000पूर्ण,			/* 00,20,00,aa */
	अणु0xaa, 0x21, 0x00a0पूर्ण,			/* 00,21,a0,aa */
	अणु0xaa, 0x22, 0x0016पूर्ण,			/* 00,22,16,aa */
	अणु0xaa, 0x23, 0x0040पूर्ण,			/* 00,23,40,aa */
	अणु0xa0, 0x2f, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,2f,cc */
	अणु0xa0, 0xf8, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,f8,cc */
	अणु0xa0, 0x00, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,00,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x02, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,02,cc */
	अणु0xa0, 0x00, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,00,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,20,cc */
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,00,cc */
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,00,cc */
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,	/* 00,1d,00,cc */
	अणु0xa0, 0xa0, ZC3XX_R01E_HSYNC_1पूर्ण,	/* 00,1e,a0,cc */
	अणु0xa0, 0x16, ZC3XX_R01F_HSYNC_2पूर्ण,	/* 00,1f,16,cc */
	अणु0xa0, 0x40, ZC3XX_R020_HSYNC_3पूर्ण,	/* 00,20,40,cc */
	अणुपूर्ण
पूर्ण;

/* from lPEPI264v.inf (hv7131b!) */
अटल स्थिर काष्ठा usb_action hv7131r_InitialScale[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x77, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R09B_WINHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण,
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xdd, 0x00, 0x0200पूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xaa, 0x01, 0x000cपूर्ण,
	अणु0xaa, 0x11, 0x0000पूर्ण,
	अणु0xaa, 0x13, 0x0000पूर्ण,
	अणु0xaa, 0x14, 0x0001पूर्ण,
	अणु0xaa, 0x15, 0x00e8पूर्ण,
	अणु0xaa, 0x16, 0x0002पूर्ण,
	अणु0xaa, 0x17, 0x0088पूर्ण,
	अणु0xaa, 0x30, 0x000bपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x78, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0xc0, 0x019bपूर्ण,
	अणु0xa0, 0xa0, 0x019cपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131r_Initial[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x77, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R09B_WINHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe6, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण,
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xdd, 0x00, 0x0200पूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xaa, 0x01, 0x000cपूर्ण,
	अणु0xaa, 0x11, 0x0000पूर्ण,
	अणु0xaa, 0x13, 0x0000पूर्ण,
	अणु0xaa, 0x14, 0x0001पूर्ण,
	अणु0xaa, 0x15, 0x00e6पूर्ण,
	अणु0xaa, 0x16, 0x0002पूर्ण,
	अणु0xaa, 0x17, 0x0086पूर्ण,
	अणु0xaa, 0x30, 0x000bपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x78, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0xc0, 0x019bपूर्ण,
	अणु0xa0, 0xa0, 0x019cपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131r_50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x68, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xa0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0xea, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131r_50HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0xd1, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0xd4, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0xc0, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131r_60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x1a, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0xc3, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131r_60HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x35, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x86, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0xa0, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131r_NoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x2f, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x58, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action hv7131r_NoFlikerScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xa0, 0x2f, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0xb0, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action icm105a_InitialScale[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0xa1, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R097_WINYSTARTHIGHपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R099_WINXSTARTHIGHपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R09B_WINHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण,
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xaa, 0x01, 0x0010पूर्ण,
	अणु0xaa, 0x03, 0x0000पूर्ण,
	अणु0xaa, 0x04, 0x0001पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0001पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0001पूर्ण,
	अणु0xaa, 0x04, 0x0011पूर्ण,
	अणु0xaa, 0x05, 0x00a0पूर्ण,
	अणु0xaa, 0x06, 0x0001पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0002पूर्ण,
	अणु0xaa, 0x04, 0x0013पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0001पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0003पूर्ण,
	अणु0xaa, 0x04, 0x0015पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0004पूर्ण,
	अणु0xaa, 0x04, 0x0017पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x000dपूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0005पूर्ण,
	अणु0xaa, 0x04, 0x0019पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0006पूर्ण,
	अणु0xaa, 0x04, 0x0017पूर्ण,
	अणु0xaa, 0x05, 0x0026पूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0007पूर्ण,
	अणु0xaa, 0x04, 0x0019पूर्ण,
	अणु0xaa, 0x05, 0x0022पूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0008पूर्ण,
	अणु0xaa, 0x04, 0x0021पूर्ण,
	अणु0xaa, 0x05, 0x00aaपूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0009पूर्ण,
	अणु0xaa, 0x04, 0x0023पूर्ण,
	अणु0xaa, 0x05, 0x00aaपूर्ण,
	अणु0xaa, 0x06, 0x000dपूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x000aपूर्ण,
	अणु0xaa, 0x04, 0x0025पूर्ण,
	अणु0xaa, 0x05, 0x00aaपूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x000bपूर्ण,
	अणु0xaa, 0x04, 0x00ecपूर्ण,
	अणु0xaa, 0x05, 0x002eपूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x000cपूर्ण,
	अणु0xaa, 0x04, 0x00faपूर्ण,
	अणु0xaa, 0x05, 0x002aपूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x07, 0x000dपूर्ण,
	अणु0xaa, 0x01, 0x0005पूर्ण,
	अणु0xaa, 0x94, 0x0002पूर्ण,
	अणु0xaa, 0x90, 0x0000पूर्ण,
	अणु0xaa, 0x91, 0x001fपूर्ण,
	अणु0xaa, 0x10, 0x0064पूर्ण,
	अणु0xaa, 0x9b, 0x00f0पूर्ण,
	अणु0xaa, 0x9c, 0x0002पूर्ण,
	अणु0xaa, 0x14, 0x001aपूर्ण,
	अणु0xaa, 0x20, 0x0080पूर्ण,
	अणु0xaa, 0x22, 0x0080पूर्ण,
	अणु0xaa, 0x24, 0x0080पूर्ण,
	अणु0xaa, 0x26, 0x0080पूर्ण,
	अणु0xaa, 0x00, 0x0084पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xaa, 0xa8, 0x00c0पूर्ण,
	अणु0xa1, 0x01, 0x0002पूर्ण,
	अणु0xa1, 0x01, 0x0008पूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa1, 0x01, 0x0008पूर्ण,

	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* घड़ी ? */
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,	/* sharpness+ */
	अणु0xa1, 0x01, 0x01c8पूर्ण,
	अणु0xa1, 0x01, 0x01c9पूर्ण,
	अणु0xa1, 0x01, 0x01caपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* sharpness- */
	अणु0xa0, 0x52, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xf7, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x52, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x52, ZC3XX_R112_RGB22पूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x0d, 0x0003पूर्ण,
	अणु0xaa, 0x0c, 0x008cपूर्ण,
	अणु0xaa, 0x0e, 0x0095पूर्ण,
	अणु0xaa, 0x0f, 0x0002पूर्ण,
	अणु0xaa, 0x1c, 0x0094पूर्ण,
	अणु0xaa, 0x1d, 0x0002पूर्ण,
	अणु0xaa, 0x20, 0x0080पूर्ण,
	अणु0xaa, 0x22, 0x0080पूर्ण,
	अणु0xaa, 0x24, 0x0080पूर्ण,
	अणु0xaa, 0x26, 0x0080पूर्ण,
	अणु0xaa, 0x00, 0x0084पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण,
	अणु0xa0, 0x94, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x84, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x12, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xe3, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xec, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf5, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0xc0, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0xc0, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action icm105a_Initial[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0xa1, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R097_WINYSTARTHIGHपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R099_WINXSTARTHIGHपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R09B_WINHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe6, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण,
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xa0, 0x77, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xaa, 0x01, 0x0010पूर्ण,
	अणु0xaa, 0x03, 0x0000पूर्ण,
	अणु0xaa, 0x04, 0x0001पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0001पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0001पूर्ण,
	अणु0xaa, 0x04, 0x0011पूर्ण,
	अणु0xaa, 0x05, 0x00a0पूर्ण,
	अणु0xaa, 0x06, 0x0001पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0002पूर्ण,
	अणु0xaa, 0x04, 0x0013पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0001पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0003पूर्ण,
	अणु0xaa, 0x04, 0x0015पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0004पूर्ण,
	अणु0xaa, 0x04, 0x0017पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x000dपूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0005पूर्ण,
	अणु0xa0, 0x04, ZC3XX_R092_I2CADDRESSSELECTपूर्ण,
	अणु0xa0, 0x19, ZC3XX_R093_I2CSETVALUEपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R090_I2CCOMMANDपूर्ण,
	अणु0xa1, 0x01, 0x0091पूर्ण,
	अणु0xaa, 0x05, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0006पूर्ण,
	अणु0xaa, 0x04, 0x0017पूर्ण,
	अणु0xaa, 0x05, 0x0026पूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0007पूर्ण,
	अणु0xaa, 0x04, 0x0019पूर्ण,
	अणु0xaa, 0x05, 0x0022पूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0008पूर्ण,
	अणु0xaa, 0x04, 0x0021पूर्ण,
	अणु0xaa, 0x05, 0x00aaपूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x0009पूर्ण,
	अणु0xaa, 0x04, 0x0023पूर्ण,
	अणु0xaa, 0x05, 0x00aaपूर्ण,
	अणु0xaa, 0x06, 0x000dपूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x000aपूर्ण,
	अणु0xaa, 0x04, 0x0025पूर्ण,
	अणु0xaa, 0x05, 0x00aaपूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x000bपूर्ण,
	अणु0xaa, 0x04, 0x00ecपूर्ण,
	अणु0xaa, 0x05, 0x002eपूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x03, 0x000cपूर्ण,
	अणु0xaa, 0x04, 0x00faपूर्ण,
	अणु0xaa, 0x05, 0x002aपूर्ण,
	अणु0xaa, 0x06, 0x0005पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x07, 0x000dपूर्ण,
	अणु0xaa, 0x01, 0x0005पूर्ण,
	अणु0xaa, 0x94, 0x0002पूर्ण,
	अणु0xaa, 0x90, 0x0000पूर्ण,
	अणु0xaa, 0x91, 0x0010पूर्ण,
	अणु0xaa, 0x10, 0x0064पूर्ण,
	अणु0xaa, 0x9b, 0x00f0पूर्ण,
	अणु0xaa, 0x9c, 0x0002पूर्ण,
	अणु0xaa, 0x14, 0x001aपूर्ण,
	अणु0xaa, 0x20, 0x0080पूर्ण,
	अणु0xaa, 0x22, 0x0080पूर्ण,
	अणु0xaa, 0x24, 0x0080पूर्ण,
	अणु0xaa, 0x26, 0x0080पूर्ण,
	अणु0xaa, 0x00, 0x0084पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xaa, 0xa8, 0x0080पूर्ण,
	अणु0xa0, 0x78, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa1, 0x01, 0x0002पूर्ण,
	अणु0xa1, 0x01, 0x0008पूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa1, 0x01, 0x0008पूर्ण,

	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* घड़ी ? */
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,	/* sharpness+ */
	अणु0xa1, 0x01, 0x01c8पूर्ण,
	अणु0xa1, 0x01, 0x01c9पूर्ण,
	अणु0xa1, 0x01, 0x01caपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* sharpness- */

	अणु0xa0, 0x52, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xf7, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x52, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x52, ZC3XX_R112_RGB22पूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x0d, 0x0003पूर्ण,
	अणु0xaa, 0x0c, 0x0020पूर्ण,
	अणु0xaa, 0x0e, 0x000eपूर्ण,
	अणु0xaa, 0x0f, 0x0002पूर्ण,
	अणु0xaa, 0x1c, 0x000dपूर्ण,
	अणु0xaa, 0x1d, 0x0002पूर्ण,
	अणु0xaa, 0x20, 0x0080पूर्ण,
	अणु0xaa, 0x22, 0x0080पूर्ण,
	अणु0xaa, 0x24, 0x0080पूर्ण,
	अणु0xaa, 0x26, 0x0080पूर्ण,
	अणु0xaa, 0x00, 0x0084पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x1a, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x4b, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x12, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xc8, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xd8, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xea, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action icm105a_50HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0x0d, 0x0003पूर्ण, /* 00,0d,03,aa */
	अणु0xaa, 0x0c, 0x0020पूर्ण, /* 00,0c,20,aa */
	अणु0xaa, 0x0e, 0x000eपूर्ण, /* 00,0e,0e,aa */
	अणु0xaa, 0x0f, 0x0002पूर्ण, /* 00,0f,02,aa */
	अणु0xaa, 0x1c, 0x000dपूर्ण, /* 00,1c,0d,aa */
	अणु0xaa, 0x1d, 0x0002पूर्ण, /* 00,1d,02,aa */
	अणु0xaa, 0x20, 0x0080पूर्ण, /* 00,20,80,aa */
	अणु0xaa, 0x22, 0x0080पूर्ण, /* 00,22,80,aa */
	अणु0xaa, 0x24, 0x0080पूर्ण, /* 00,24,80,aa */
	अणु0xaa, 0x26, 0x0080पूर्ण, /* 00,26,80,aa */
	अणु0xaa, 0x00, 0x0084पूर्ण, /* 00,00,84,aa */
	अणु0xa0, 0x02, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,02,cc */
	अणु0xa0, 0x0d, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,0d,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,04,cc */
	अणु0xa0, 0x1a, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,1a,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x4b, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,4b,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,20,cc */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,10,cc */
	अणु0xa0, 0x12, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,12,cc */
	अणु0xa0, 0xc8, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,c8,cc */
	अणु0xa0, 0xd8, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,d8,cc */
	अणु0xa0, 0xea, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,ea,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action icm105a_50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0x0d, 0x0003पूर्ण, /* 00,0d,03,aa */
	अणु0xaa, 0x0c, 0x008cपूर्ण, /* 00,0c,8c,aa */
	अणु0xaa, 0x0e, 0x0095पूर्ण, /* 00,0e,95,aa */
	अणु0xaa, 0x0f, 0x0002पूर्ण, /* 00,0f,02,aa */
	अणु0xaa, 0x1c, 0x0094पूर्ण, /* 00,1c,94,aa */
	अणु0xaa, 0x1d, 0x0002पूर्ण, /* 00,1d,02,aa */
	अणु0xaa, 0x20, 0x0080पूर्ण, /* 00,20,80,aa */
	अणु0xaa, 0x22, 0x0080पूर्ण, /* 00,22,80,aa */
	अणु0xaa, 0x24, 0x0080पूर्ण, /* 00,24,80,aa */
	अणु0xaa, 0x26, 0x0080पूर्ण, /* 00,26,80,aa */
	अणु0xaa, 0x00, 0x0084पूर्ण, /* 00,00,84,aa */
	अणु0xa0, 0x02, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,02,cc */
	अणु0xa0, 0x94, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,94,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,04,cc */
	अणु0xa0, 0x20, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,20,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x84, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,84,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,20,cc */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,10,cc */
	अणु0xa0, 0x12, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,12,cc */
	अणु0xa0, 0xe3, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,e3,cc */
	अणु0xa0, 0xec, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,ec,cc */
	अणु0xa0, 0xf5, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,f5,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण, /* 01,a7,00,cc */
	अणु0xa0, 0xc0, ZC3XX_R1A8_DIGITALGAINपूर्ण, /* 01,a8,c0,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action icm105a_60HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0x0d, 0x0003पूर्ण, /* 00,0d,03,aa */
	अणु0xaa, 0x0c, 0x0004पूर्ण, /* 00,0c,04,aa */
	अणु0xaa, 0x0e, 0x000dपूर्ण, /* 00,0e,0d,aa */
	अणु0xaa, 0x0f, 0x0002पूर्ण, /* 00,0f,02,aa */
	अणु0xaa, 0x1c, 0x0008पूर्ण, /* 00,1c,08,aa */
	अणु0xaa, 0x1d, 0x0002पूर्ण, /* 00,1d,02,aa */
	अणु0xaa, 0x20, 0x0080पूर्ण, /* 00,20,80,aa */
	अणु0xaa, 0x22, 0x0080पूर्ण, /* 00,22,80,aa */
	अणु0xaa, 0x24, 0x0080पूर्ण, /* 00,24,80,aa */
	अणु0xaa, 0x26, 0x0080पूर्ण, /* 00,26,80,aa */
	अणु0xaa, 0x00, 0x0084पूर्ण, /* 00,00,84,aa */
	अणु0xa0, 0x02, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,02,cc */
	अणु0xa0, 0x08, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,08,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,04,cc */
	अणु0xa0, 0x10, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,10,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x41, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,41,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,20,cc */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,10,cc */
	अणु0xa0, 0x12, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,12,cc */
	अणु0xa0, 0xc1, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,c1,cc */
	अणु0xa0, 0xd4, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,d4,cc */
	अणु0xa0, 0xe8, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,e8,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action icm105a_60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0x0d, 0x0003पूर्ण, /* 00,0d,03,aa */
	अणु0xaa, 0x0c, 0x0008पूर्ण, /* 00,0c,08,aa */
	अणु0xaa, 0x0e, 0x0086पूर्ण, /* 00,0e,86,aa */
	अणु0xaa, 0x0f, 0x0002पूर्ण, /* 00,0f,02,aa */
	अणु0xaa, 0x1c, 0x0085पूर्ण, /* 00,1c,85,aa */
	अणु0xaa, 0x1d, 0x0002पूर्ण, /* 00,1d,02,aa */
	अणु0xaa, 0x20, 0x0080पूर्ण, /* 00,20,80,aa */
	अणु0xaa, 0x22, 0x0080पूर्ण, /* 00,22,80,aa */
	अणु0xaa, 0x24, 0x0080पूर्ण, /* 00,24,80,aa */
	अणु0xaa, 0x26, 0x0080पूर्ण, /* 00,26,80,aa */
	अणु0xaa, 0x00, 0x0084पूर्ण, /* 00,00,84,aa */
	अणु0xa0, 0x02, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,02,cc */
	अणु0xa0, 0x85, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,85,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,04,cc */
	अणु0xa0, 0x08, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,08,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x81, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,81,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,20,cc */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,10,cc */
	अणु0xa0, 0x12, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,12,cc */
	अणु0xa0, 0xc2, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,c2,cc */
	अणु0xa0, 0xd6, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,d6,cc */
	अणु0xa0, 0xea, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,ea,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण, /* 01,a7,00,cc */
	अणु0xa0, 0xc0, ZC3XX_R1A8_DIGITALGAINपूर्ण, /* 01,a8,c0,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action icm105a_NoFlikerScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0x0d, 0x0003पूर्ण, /* 00,0d,03,aa */
	अणु0xaa, 0x0c, 0x0004पूर्ण, /* 00,0c,04,aa */
	अणु0xaa, 0x0e, 0x000dपूर्ण, /* 00,0e,0d,aa */
	अणु0xaa, 0x0f, 0x0002पूर्ण, /* 00,0f,02,aa */
	अणु0xaa, 0x1c, 0x0000पूर्ण, /* 00,1c,00,aa */
	अणु0xaa, 0x1d, 0x0002पूर्ण, /* 00,1d,02,aa */
	अणु0xaa, 0x20, 0x0080पूर्ण, /* 00,20,80,aa */
	अणु0xaa, 0x22, 0x0080पूर्ण, /* 00,22,80,aa */
	अणु0xaa, 0x24, 0x0080पूर्ण, /* 00,24,80,aa */
	अणु0xaa, 0x26, 0x0080पूर्ण, /* 00,26,80,aa */
	अणु0xaa, 0x00, 0x0084पूर्ण, /* 00,00,84,aa */
	अणु0xa0, 0x02, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,02,cc */
	अणु0xa0, 0x00, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,00,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,04,cc */
	अणु0xa0, 0x20, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,20,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x10, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,10,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,20,cc */
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,00,cc */
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,00,cc */
	अणु0xa0, 0xc1, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,c1,cc */
	अणु0xa0, 0xd4, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,d4,cc */
	अणु0xa0, 0xe8, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,e8,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action icm105a_NoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0x0d, 0x0003पूर्ण, /* 00,0d,03,aa */
	अणु0xaa, 0x0c, 0x0004पूर्ण, /* 00,0c,04,aa */
	अणु0xaa, 0x0e, 0x0081पूर्ण, /* 00,0e,81,aa */
	अणु0xaa, 0x0f, 0x0002पूर्ण, /* 00,0f,02,aa */
	अणु0xaa, 0x1c, 0x0080पूर्ण, /* 00,1c,80,aa */
	अणु0xaa, 0x1d, 0x0002पूर्ण, /* 00,1d,02,aa */
	अणु0xaa, 0x20, 0x0080पूर्ण, /* 00,20,80,aa */
	अणु0xaa, 0x22, 0x0080पूर्ण, /* 00,22,80,aa */
	अणु0xaa, 0x24, 0x0080पूर्ण, /* 00,24,80,aa */
	अणु0xaa, 0x26, 0x0080पूर्ण, /* 00,26,80,aa */
	अणु0xaa, 0x00, 0x0084पूर्ण, /* 00,00,84,aa */
	अणु0xa0, 0x02, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,02,cc */
	अणु0xa0, 0x80, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,80,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,04,cc */
	अणु0xa0, 0x20, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,20,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x10, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,10,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,20,cc */
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,00,cc */
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,00,cc */
	अणु0xa0, 0xc1, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,c1,cc */
	अणु0xa0, 0xd4, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,d4,cc */
	अणु0xa0, 0xe8, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,e8,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणु0xa0, 0x00, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण, /* 01,a7,00,cc */
	अणु0xa0, 0xc0, ZC3XX_R1A8_DIGITALGAINपूर्ण, /* 01,a8,c0,cc */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action mc501cb_Initial[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण, /* 00,00,01,cc */
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण, /* 00,02,00,cc */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण, /* 00,10,01,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण, /* 00,01,01,cc */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण, /* 00,08,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,01,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,05,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण, /* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण, /* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण, /* 00,05,01,cc */
	अणु0xa0, 0xd8, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण, /* 00,06,d8,cc */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण, /* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण, /* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण, /* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण, /* 01,1c,00,cc */
	अणु0xa0, 0x01, ZC3XX_R09B_WINHEIGHTHIGHपूर्ण, /* 00,9b,01,cc */
	अणु0xa0, 0xde, ZC3XX_R09C_WINHEIGHTLOWपूर्ण, /* 00,9c,de,cc */
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण, /* 00,9d,02,cc */
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण, /* 00,9e,86,cc */
	अणु0xa0, 0x33, ZC3XX_R086_EXPTIMEHIGHपूर्ण, /* 00,86,33,cc */
	अणु0xa0, 0x34, ZC3XX_R087_EXPTIMEMIDपूर्ण, /* 00,87,34,cc */
	अणु0xa0, 0x35, ZC3XX_R088_EXPTIMELOWपूर्ण, /* 00,88,35,cc */
	अणु0xa0, 0xb0, ZC3XX_R08B_I2CDEVICEADDRपूर्ण, /* 00,8b,b0,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,05,cc */
	अणु0xaa, 0x01, 0x0001पूर्ण, /* 00,01,01,aa */
	अणु0xaa, 0x01, 0x0003पूर्ण, /* 00,01,03,aa */
	अणु0xaa, 0x01, 0x0001पूर्ण, /* 00,01,01,aa */
	अणु0xaa, 0x03, 0x0000पूर्ण, /* 00,03,00,aa */
	अणु0xaa, 0x10, 0x0000पूर्ण, /* 00,10,00,aa */
	अणु0xaa, 0x11, 0x0080पूर्ण, /* 00,11,80,aa */
	अणु0xaa, 0x12, 0x0000पूर्ण, /* 00,12,00,aa */
	अणु0xaa, 0x13, 0x0000पूर्ण, /* 00,13,00,aa */
	अणु0xaa, 0x14, 0x0000पूर्ण, /* 00,14,00,aa */
	अणु0xaa, 0x15, 0x0000पूर्ण, /* 00,15,00,aa */
	अणु0xaa, 0x16, 0x0000पूर्ण, /* 00,16,00,aa */
	अणु0xaa, 0x17, 0x0001पूर्ण, /* 00,17,01,aa */
	अणु0xaa, 0x18, 0x00deपूर्ण, /* 00,18,de,aa */
	अणु0xaa, 0x19, 0x0002पूर्ण, /* 00,19,02,aa */
	अणु0xaa, 0x1a, 0x0086पूर्ण, /* 00,1a,86,aa */
	अणु0xaa, 0x20, 0x00a8पूर्ण, /* 00,20,a8,aa */
	अणु0xaa, 0x22, 0x0000पूर्ण, /* 00,22,00,aa */
	अणु0xaa, 0x23, 0x0000पूर्ण, /* 00,23,00,aa */
	अणु0xaa, 0x24, 0x0000पूर्ण, /* 00,24,00,aa */
	अणु0xaa, 0x40, 0x0033पूर्ण, /* 00,40,33,aa */
	अणु0xaa, 0x41, 0x0077पूर्ण, /* 00,41,77,aa */
	अणु0xaa, 0x42, 0x0053पूर्ण, /* 00,42,53,aa */
	अणु0xaa, 0x43, 0x00b0पूर्ण, /* 00,43,b0,aa */
	अणु0xaa, 0x4b, 0x0001पूर्ण, /* 00,4b,01,aa */
	अणु0xaa, 0x72, 0x0020पूर्ण, /* 00,72,20,aa */
	अणु0xaa, 0x73, 0x0000पूर्ण, /* 00,73,00,aa */
	अणु0xaa, 0x80, 0x0000पूर्ण, /* 00,80,00,aa */
	अणु0xaa, 0x85, 0x0050पूर्ण, /* 00,85,50,aa */
	अणु0xaa, 0x91, 0x0070पूर्ण, /* 00,91,70,aa */
	अणु0xaa, 0x92, 0x0072पूर्ण, /* 00,92,72,aa */
	अणु0xaa, 0x03, 0x0001पूर्ण, /* 00,03,01,aa */
	अणु0xaa, 0x10, 0x00a0पूर्ण, /* 00,10,a0,aa */
	अणु0xaa, 0x11, 0x0001पूर्ण, /* 00,11,01,aa */
	अणु0xaa, 0x30, 0x0000पूर्ण, /* 00,30,00,aa */
	अणु0xaa, 0x60, 0x0000पूर्ण, /* 00,60,00,aa */
	अणु0xaa, 0xa0, 0x001aपूर्ण, /* 00,a0,1a,aa */
	अणु0xaa, 0xa1, 0x0000पूर्ण, /* 00,a1,00,aa */
	अणु0xaa, 0xa2, 0x003fपूर्ण, /* 00,a2,3f,aa */
	अणु0xaa, 0xa3, 0x0028पूर्ण, /* 00,a3,28,aa */
	अणु0xaa, 0xa4, 0x0010पूर्ण, /* 00,a4,10,aa */
	अणु0xaa, 0xa5, 0x0020पूर्ण, /* 00,a5,20,aa */
	अणु0xaa, 0xb1, 0x0044पूर्ण, /* 00,b1,44,aa */
	अणु0xaa, 0xd0, 0x0001पूर्ण, /* 00,d0,01,aa */
	अणु0xaa, 0xd1, 0x0085पूर्ण, /* 00,d1,85,aa */
	अणु0xaa, 0xd2, 0x0080पूर्ण, /* 00,d2,80,aa */
	अणु0xaa, 0xd3, 0x0080पूर्ण, /* 00,d3,80,aa */
	अणु0xaa, 0xd4, 0x0080पूर्ण, /* 00,d4,80,aa */
	अणु0xaa, 0xd5, 0x0080पूर्ण, /* 00,d5,80,aa */
	अणु0xaa, 0xc0, 0x00c3पूर्ण, /* 00,c0,c3,aa */
	अणु0xaa, 0xc2, 0x0044पूर्ण, /* 00,c2,44,aa */
	अणु0xaa, 0xc4, 0x0040पूर्ण, /* 00,c4,40,aa */
	अणु0xaa, 0xc5, 0x0020पूर्ण, /* 00,c5,20,aa */
	अणु0xaa, 0xc6, 0x0008पूर्ण, /* 00,c6,08,aa */
	अणु0xaa, 0x03, 0x0004पूर्ण, /* 00,03,04,aa */
	अणु0xaa, 0x10, 0x0000पूर्ण, /* 00,10,00,aa */
	अणु0xaa, 0x40, 0x0030पूर्ण, /* 00,40,30,aa */
	अणु0xaa, 0x41, 0x0020पूर्ण, /* 00,41,20,aa */
	अणु0xaa, 0x42, 0x002dपूर्ण, /* 00,42,2d,aa */
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x1c, 0x0050पूर्ण, /* 00,1C,50,aa */
	अणु0xaa, 0x11, 0x0081पूर्ण, /* 00,11,81,aa */
	अणु0xaa, 0x3b, 0x001dपूर्ण, /* 00,3b,1D,aa */
	अणु0xaa, 0x3c, 0x004cपूर्ण, /* 00,3c,4C,aa */
	अणु0xaa, 0x3d, 0x0018पूर्ण, /* 00,3d,18,aa */
	अणु0xaa, 0x3e, 0x006aपूर्ण, /* 00,3e,6A,aa */
	अणु0xaa, 0x01, 0x0000पूर्ण, /* 00,01,00,aa */
	अणु0xaa, 0x52, 0x00ffपूर्ण, /* 00,52,FF,aa */
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण, /* 01,00,0d,cc */
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण, /* 01,01,37,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण, /* 01,89,06,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण, /* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण, /* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण, /* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण, /* 03,01,08,cc */
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण, /* 01,80,02,cc */
	अणु0xaa, 0x03, 0x0002पूर्ण, /* 00,03,02,aa */
	अणु0xaa, 0x51, 0x0027पूर्ण, /* 00,51,27,aa */
	अणु0xaa, 0x52, 0x0020पूर्ण, /* 00,52,20,aa */
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x50, 0x0010पूर्ण, /* 00,50,10,aa */
	अणु0xaa, 0x51, 0x0010पूर्ण, /* 00,51,10,aa */
	अणु0xaa, 0x54, 0x0010पूर्ण, /* 00,54,10,aa */
	अणु0xaa, 0x55, 0x0010पूर्ण, /* 00,55,10,aa */
	अणु0xa0, 0xf0, 0x0199पूर्ण, /* 01,99,F0,cc */
	अणु0xa0, 0x80, 0x019aपूर्ण, /* 01,9A,80,cc */

	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x10, 0x00fcपूर्ण, /* 00,10,fc,aa */
	अणु0xaa, 0x36, 0x001dपूर्ण, /* 00,36,1D,aa */
	अणु0xaa, 0x37, 0x004cपूर्ण, /* 00,37,4C,aa */
	अणु0xaa, 0x3b, 0x001dपूर्ण, /* 00,3B,1D,aa */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action mc501cb_InitialScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण, /* 00,00,01,cc */
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण, /* 00,02,10,cc */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण, /* 00,10,01,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण, /* 00,01,01,cc */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण, /* 00,08,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,01,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,05,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण, /* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण, /* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण, /* 00,05,01,cc */
	अणु0xa0, 0xd0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण, /* 00,06,d0,cc */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण, /* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण, /* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण, /* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण, /* 01,1c,00,cc */
	अणु0xa0, 0x01, ZC3XX_R09B_WINHEIGHTHIGHपूर्ण, /* 00,9b,01,cc */
	अणु0xa0, 0xd8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण, /* 00,9c,d8,cc */
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण, /* 00,9d,02,cc */
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण, /* 00,9e,88,cc */
	अणु0xa0, 0x33, ZC3XX_R086_EXPTIMEHIGHपूर्ण, /* 00,86,33,cc */
	अणु0xa0, 0x34, ZC3XX_R087_EXPTIMEMIDपूर्ण, /* 00,87,34,cc */
	अणु0xa0, 0x35, ZC3XX_R088_EXPTIMELOWपूर्ण, /* 00,88,35,cc */
	अणु0xa0, 0xb0, ZC3XX_R08B_I2CDEVICEADDRपूर्ण, /* 00,8b,b0,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,05,cc */
	अणु0xaa, 0x01, 0x0001पूर्ण, /* 00,01,01,aa */
	अणु0xaa, 0x01, 0x0003पूर्ण, /* 00,01,03,aa */
	अणु0xaa, 0x01, 0x0001पूर्ण, /* 00,01,01,aa */
	अणु0xaa, 0x03, 0x0000पूर्ण, /* 00,03,00,aa */
	अणु0xaa, 0x10, 0x0000पूर्ण, /* 00,10,00,aa */
	अणु0xaa, 0x11, 0x0080पूर्ण, /* 00,11,80,aa */
	अणु0xaa, 0x12, 0x0000पूर्ण, /* 00,12,00,aa */
	अणु0xaa, 0x13, 0x0000पूर्ण, /* 00,13,00,aa */
	अणु0xaa, 0x14, 0x0000पूर्ण, /* 00,14,00,aa */
	अणु0xaa, 0x15, 0x0000पूर्ण, /* 00,15,00,aa */
	अणु0xaa, 0x16, 0x0000पूर्ण, /* 00,16,00,aa */
	अणु0xaa, 0x17, 0x0001पूर्ण, /* 00,17,01,aa */
	अणु0xaa, 0x18, 0x00d8पूर्ण, /* 00,18,d8,aa */
	अणु0xaa, 0x19, 0x0002पूर्ण, /* 00,19,02,aa */
	अणु0xaa, 0x1a, 0x0088पूर्ण, /* 00,1a,88,aa */
	अणु0xaa, 0x20, 0x00a8पूर्ण, /* 00,20,a8,aa */
	अणु0xaa, 0x22, 0x0000पूर्ण, /* 00,22,00,aa */
	अणु0xaa, 0x23, 0x0000पूर्ण, /* 00,23,00,aa */
	अणु0xaa, 0x24, 0x0000पूर्ण, /* 00,24,00,aa */
	अणु0xaa, 0x40, 0x0033पूर्ण, /* 00,40,33,aa */
	अणु0xaa, 0x41, 0x0077पूर्ण, /* 00,41,77,aa */
	अणु0xaa, 0x42, 0x0053पूर्ण, /* 00,42,53,aa */
	अणु0xaa, 0x43, 0x00b0पूर्ण, /* 00,43,b0,aa */
	अणु0xaa, 0x4b, 0x0001पूर्ण, /* 00,4b,01,aa */
	अणु0xaa, 0x72, 0x0020पूर्ण, /* 00,72,20,aa */
	अणु0xaa, 0x73, 0x0000पूर्ण, /* 00,73,00,aa */
	अणु0xaa, 0x80, 0x0000पूर्ण, /* 00,80,00,aa */
	अणु0xaa, 0x85, 0x0050पूर्ण, /* 00,85,50,aa */
	अणु0xaa, 0x91, 0x0070पूर्ण, /* 00,91,70,aa */
	अणु0xaa, 0x92, 0x0072पूर्ण, /* 00,92,72,aa */
	अणु0xaa, 0x03, 0x0001पूर्ण, /* 00,03,01,aa */
	अणु0xaa, 0x10, 0x00a0पूर्ण, /* 00,10,a0,aa */
	अणु0xaa, 0x11, 0x0001पूर्ण, /* 00,11,01,aa */
	अणु0xaa, 0x30, 0x0000पूर्ण, /* 00,30,00,aa */
	अणु0xaa, 0x60, 0x0000पूर्ण, /* 00,60,00,aa */
	अणु0xaa, 0xa0, 0x001aपूर्ण, /* 00,a0,1a,aa */
	अणु0xaa, 0xa1, 0x0000पूर्ण, /* 00,a1,00,aa */
	अणु0xaa, 0xa2, 0x003fपूर्ण, /* 00,a2,3f,aa */
	अणु0xaa, 0xa3, 0x0028पूर्ण, /* 00,a3,28,aa */
	अणु0xaa, 0xa4, 0x0010पूर्ण, /* 00,a4,10,aa */
	अणु0xaa, 0xa5, 0x0020पूर्ण, /* 00,a5,20,aa */
	अणु0xaa, 0xb1, 0x0044पूर्ण, /* 00,b1,44,aa */
	अणु0xaa, 0xd0, 0x0001पूर्ण, /* 00,d0,01,aa */
	अणु0xaa, 0xd1, 0x0085पूर्ण, /* 00,d1,85,aa */
	अणु0xaa, 0xd2, 0x0080पूर्ण, /* 00,d2,80,aa */
	अणु0xaa, 0xd3, 0x0080पूर्ण, /* 00,d3,80,aa */
	अणु0xaa, 0xd4, 0x0080पूर्ण, /* 00,d4,80,aa */
	अणु0xaa, 0xd5, 0x0080पूर्ण, /* 00,d5,80,aa */
	अणु0xaa, 0xc0, 0x00c3पूर्ण, /* 00,c0,c3,aa */
	अणु0xaa, 0xc2, 0x0044पूर्ण, /* 00,c2,44,aa */
	अणु0xaa, 0xc4, 0x0040पूर्ण, /* 00,c4,40,aa */
	अणु0xaa, 0xc5, 0x0020पूर्ण, /* 00,c5,20,aa */
	अणु0xaa, 0xc6, 0x0008पूर्ण, /* 00,c6,08,aa */
	अणु0xaa, 0x03, 0x0004पूर्ण, /* 00,03,04,aa */
	अणु0xaa, 0x10, 0x0000पूर्ण, /* 00,10,00,aa */
	अणु0xaa, 0x40, 0x0030पूर्ण, /* 00,40,30,aa */
	अणु0xaa, 0x41, 0x0020पूर्ण, /* 00,41,20,aa */
	अणु0xaa, 0x42, 0x002dपूर्ण, /* 00,42,2d,aa */
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x1c, 0x0050पूर्ण, /* 00,1c,50,aa */
	अणु0xaa, 0x11, 0x0081पूर्ण, /* 00,11,81,aa */
	अणु0xaa, 0x3b, 0x003aपूर्ण, /* 00,3b,3A,aa */
	अणु0xaa, 0x3c, 0x0098पूर्ण, /* 00,3c,98,aa */
	अणु0xaa, 0x3d, 0x0030पूर्ण, /* 00,3d,30,aa */
	अणु0xaa, 0x3e, 0x00d4पूर्ण, /* 00,3E,D4,aa */
	अणु0xaa, 0x01, 0x0000पूर्ण, /* 00,01,00,aa */
	अणु0xaa, 0x52, 0x00ffपूर्ण, /* 00,52,FF,aa */
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण, /* 01,00,0d,cc */
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण, /* 01,01,37,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण, /* 01,89,06,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण, /* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण, /* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण, /* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण, /* 03,01,08,cc */
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण, /* 01,80,02,cc */
	अणु0xaa, 0x03, 0x0002पूर्ण, /* 00,03,02,aa */
	अणु0xaa, 0x51, 0x004eपूर्ण, /* 00,51,4E,aa */
	अणु0xaa, 0x52, 0x0041पूर्ण, /* 00,52,41,aa */
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x50, 0x0010पूर्ण, /* 00,50,10,aa */
	अणु0xaa, 0x51, 0x0010पूर्ण, /* 00,51,10,aa */
	अणु0xaa, 0x54, 0x0010पूर्ण, /* 00,54,10,aa */
	अणु0xaa, 0x55, 0x0010पूर्ण, /* 00,55,10,aa */
	अणु0xa0, 0xf0, 0x0199पूर्ण, /* 01,99,F0,cc */
	अणु0xa0, 0x80, 0x019aपूर्ण, /* 01,9A,80,cc */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action mc501cb_50HZ[] = अणु
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x10, 0x00fcपूर्ण, /* 00,10,fc,aa */
	अणु0xaa, 0x36, 0x001dपूर्ण, /* 00,36,1D,aa */
	अणु0xaa, 0x37, 0x004cपूर्ण, /* 00,37,4C,aa */
	अणु0xaa, 0x3b, 0x001dपूर्ण, /* 00,3B,1D,aa */
	अणु0xaa, 0x3c, 0x004cपूर्ण, /* 00,3C,4C,aa */
	अणु0xaa, 0x3d, 0x001dपूर्ण, /* 00,3D,1D,aa */
	अणु0xaa, 0x3e, 0x004cपूर्ण, /* 00,3E,4C,aa */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action mc501cb_50HZScale[] = अणु
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x10, 0x00fcपूर्ण, /* 00,10,fc,aa */
	अणु0xaa, 0x36, 0x003aपूर्ण, /* 00,36,3A,aa */
	अणु0xaa, 0x37, 0x0098पूर्ण, /* 00,37,98,aa */
	अणु0xaa, 0x3b, 0x003aपूर्ण, /* 00,3B,3A,aa */
	अणु0xaa, 0x3c, 0x0098पूर्ण, /* 00,3C,98,aa */
	अणु0xaa, 0x3d, 0x003aपूर्ण, /* 00,3D,3A,aa */
	अणु0xaa, 0x3e, 0x0098पूर्ण, /* 00,3E,98,aa */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action mc501cb_60HZ[] = अणु
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x10, 0x00fcपूर्ण, /* 00,10,fc,aa */
	अणु0xaa, 0x36, 0x0018पूर्ण, /* 00,36,18,aa */
	अणु0xaa, 0x37, 0x006aपूर्ण, /* 00,37,6A,aa */
	अणु0xaa, 0x3d, 0x0018पूर्ण, /* 00,3D,18,aa */
	अणु0xaa, 0x3e, 0x006aपूर्ण, /* 00,3E,6A,aa */
	अणु0xaa, 0x3b, 0x0018पूर्ण, /* 00,3B,18,aa */
	अणु0xaa, 0x3c, 0x006aपूर्ण, /* 00,3C,6A,aa */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action mc501cb_60HZScale[] = अणु
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x10, 0x00fcपूर्ण, /* 00,10,fc,aa */
	अणु0xaa, 0x36, 0x0030पूर्ण, /* 00,36,30,aa */
	अणु0xaa, 0x37, 0x00d4पूर्ण, /* 00,37,D4,aa */
	अणु0xaa, 0x3d, 0x0030पूर्ण, /* 00,3D,30,aa */
	अणु0xaa, 0x3e, 0x00d4पूर्ण, /* 00,3E,D4,aa */
	अणु0xaa, 0x3b, 0x0030पूर्ण, /* 00,3B,30,aa */
	अणु0xaa, 0x3c, 0x00d4पूर्ण, /* 00,3C,D4,aa */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action mc501cb_NoFliker[] = अणु
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x10, 0x00fcपूर्ण, /* 00,10,fc,aa */
	अणु0xaa, 0x36, 0x0018पूर्ण, /* 00,36,18,aa */
	अणु0xaa, 0x37, 0x006aपूर्ण, /* 00,37,6A,aa */
	अणु0xaa, 0x3d, 0x0018पूर्ण, /* 00,3D,18,aa */
	अणु0xaa, 0x3e, 0x006aपूर्ण, /* 00,3E,6A,aa */
	अणु0xaa, 0x3b, 0x0018पूर्ण, /* 00,3B,18,aa */
	अणु0xaa, 0x3c, 0x006aपूर्ण, /* 00,3C,6A,aa */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action mc501cb_NoFlikerScale[] = अणु
	अणु0xaa, 0x03, 0x0003पूर्ण, /* 00,03,03,aa */
	अणु0xaa, 0x10, 0x00fcपूर्ण, /* 00,10,fc,aa */
	अणु0xaa, 0x36, 0x0030पूर्ण, /* 00,36,30,aa */
	अणु0xaa, 0x37, 0x00d4पूर्ण, /* 00,37,D4,aa */
	अणु0xaa, 0x3d, 0x0030पूर्ण, /* 00,3D,30,aa */
	अणु0xaa, 0x3e, 0x00d4पूर्ण, /* 00,3E,D4,aa */
	अणु0xaa, 0x3b, 0x0030पूर्ण, /* 00,3B,30,aa */
	अणु0xaa, 0x3c, 0x00d4पूर्ण, /* 00,3C,D4,aa */
	अणुपूर्ण
पूर्ण;

/* from zs211.inf */
अटल स्थिर काष्ठा usb_action ov7620_Initial[] = अणु	/* 640x480 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण, /* 00,00,01,cc */
	अणु0xa0, 0x40, ZC3XX_R002_CLOCKSELECTपूर्ण, /* 00,02,40,cc */
	अणु0xa0, 0x00, ZC3XX_R008_CLOCKSETTINGपूर्ण, /* 00,08,00,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण, /* 00,01,01,cc */
	अणु0xa0, 0x06, ZC3XX_R010_CMOSSENSORSELECTपूर्ण, /* 00,10,06,cc */
	अणु0xa0, 0x02, ZC3XX_R083_RGAINADDRपूर्ण, /* 00,83,02,cc */
	अणु0xa0, 0x01, ZC3XX_R085_BGAINADDRपूर्ण, /* 00,85,01,cc */
	अणु0xa0, 0x80, ZC3XX_R086_EXPTIMEHIGHपूर्ण, /* 00,86,80,cc */
	अणु0xa0, 0x81, ZC3XX_R087_EXPTIMEMIDपूर्ण, /* 00,87,81,cc */
	अणु0xa0, 0x10, ZC3XX_R088_EXPTIMELOWपूर्ण, /* 00,88,10,cc */
	अणु0xa0, 0xa1, ZC3XX_R08B_I2CDEVICEADDRपूर्ण, /* 00,8b,a1,cc */
	अणु0xa0, 0x08, ZC3XX_R08D_COMPABILITYMODEपूर्ण, /* 00,8d,08,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण, /* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण, /* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण, /* 00,05,01,cc */
	अणु0xa0, 0xd8, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण, /* 00,06,d8,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,01,cc */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण, /* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण, /* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण, /* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण, /* 01,1c,00,cc */
	अणु0xa0, 0xde, ZC3XX_R09C_WINHEIGHTLOWपूर्ण, /* 00,9c,de,cc */
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण, /* 00,9e,86,cc */
	अणु0xaa, 0x12, 0x0088पूर्ण, /* 00,12,88,aa */
	अणु0xaa, 0x12, 0x0048पूर्ण, /* 00,12,48,aa */
	अणु0xaa, 0x75, 0x008aपूर्ण, /* 00,75,8a,aa */
	अणु0xaa, 0x13, 0x00a3पूर्ण, /* 00,13,a3,aa */
	अणु0xaa, 0x04, 0x0000पूर्ण, /* 00,04,00,aa */
	अणु0xaa, 0x05, 0x0000पूर्ण, /* 00,05,00,aa */
	अणु0xaa, 0x14, 0x0000पूर्ण, /* 00,14,00,aa */
	अणु0xaa, 0x15, 0x0004पूर्ण, /* 00,15,04,aa */
	अणु0xaa, 0x17, 0x0018पूर्ण, /* 00,17,18,aa */
	अणु0xaa, 0x18, 0x00baपूर्ण, /* 00,18,ba,aa */
	अणु0xaa, 0x19, 0x0002पूर्ण, /* 00,19,02,aa */
	अणु0xaa, 0x1a, 0x00f1पूर्ण, /* 00,1a,f1,aa */
	अणु0xaa, 0x20, 0x0040पूर्ण, /* 00,20,40,aa */
	अणु0xaa, 0x24, 0x0088पूर्ण, /* 00,24,88,aa */
	अणु0xaa, 0x25, 0x0078पूर्ण, /* 00,25,78,aa */
	अणु0xaa, 0x27, 0x00f6पूर्ण, /* 00,27,f6,aa */
	अणु0xaa, 0x28, 0x00a0पूर्ण, /* 00,28,a0,aa */
	अणु0xaa, 0x21, 0x0000पूर्ण, /* 00,21,00,aa */
	अणु0xaa, 0x2a, 0x0083पूर्ण, /* 00,2a,83,aa */
	अणु0xaa, 0x2b, 0x0096पूर्ण, /* 00,2b,96,aa */
	अणु0xaa, 0x2d, 0x0005पूर्ण, /* 00,2d,05,aa */
	अणु0xaa, 0x74, 0x0020पूर्ण, /* 00,74,20,aa */
	अणु0xaa, 0x61, 0x0068पूर्ण, /* 00,61,68,aa */
	अणु0xaa, 0x64, 0x0088पूर्ण, /* 00,64,88,aa */
	अणु0xaa, 0x00, 0x0000पूर्ण, /* 00,00,00,aa */
	अणु0xaa, 0x06, 0x0080पूर्ण, /* 00,06,80,aa */
	अणु0xaa, 0x01, 0x0090पूर्ण, /* 00,01,90,aa */
	अणु0xaa, 0x02, 0x0030पूर्ण, /* 00,02,30,aa */
	अणु0xa0, 0x77, ZC3XX_R101_SENSORCORRECTIONपूर्ण, /* 01,01,77,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,05,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण, /* 01,00,0d,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण, /* 01,89,06,cc */
	अणु0xa0, 0x00, 0x01adपूर्ण, /* 01,ad,00,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण, /* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण, /* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण, /* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण, /* 03,01,08,cc */
	अणु0xa0, 0x68, ZC3XX_R116_RGAINपूर्ण, /* 01,16,68,cc */
	अणु0xa0, 0x52, ZC3XX_R118_BGAINपूर्ण, /* 01,18,52,cc */
	अणु0xa0, 0x40, ZC3XX_R11D_GLOBALGAINपूर्ण, /* 01,1d,40,cc */
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण, /* 01,80,02,cc */
	अणु0xa0, 0x50, ZC3XX_R1A8_DIGITALGAINपूर्ण, /* 01,a8,50,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action ov7620_InitialScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण, /* 00,00,01,cc */
	अणु0xa0, 0x50, ZC3XX_R002_CLOCKSELECTपूर्ण,	/* 00,02,50,cc */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* 00,08,00,cc */
						/* mx change? */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण, /* 00,01,01,cc */
	अणु0xa0, 0x06, ZC3XX_R010_CMOSSENSORSELECTपूर्ण, /* 00,10,06,cc */
	अणु0xa0, 0x02, ZC3XX_R083_RGAINADDRपूर्ण,	/* 00,83,02,cc */
	अणु0xa0, 0x01, ZC3XX_R085_BGAINADDRपूर्ण,	/* 00,85,01,cc */
	अणु0xa0, 0x80, ZC3XX_R086_EXPTIMEHIGHपूर्ण,	/* 00,86,80,cc */
	अणु0xa0, 0x81, ZC3XX_R087_EXPTIMEMIDपूर्ण,	/* 00,87,81,cc */
	अणु0xa0, 0x10, ZC3XX_R088_EXPTIMELOWपूर्ण,	/* 00,88,10,cc */
	अणु0xa0, 0xa1, ZC3XX_R08B_I2CDEVICEADDRपूर्ण, /* 00,8b,a1,cc */
	अणु0xa0, 0x08, ZC3XX_R08D_COMPABILITYMODEपूर्ण, /* 00,8d,08,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण, /* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण, /* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण, /* 00,05,01,cc */
	अणु0xa0, 0xd0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण, /* 00,06,d0,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,01,cc */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,	/* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,	/* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,	/* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,	/* 01,1c,00,cc */
	अणु0xa0, 0xd6, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,	/* 00,9c,d6,cc */
						/* OV7648 00,9c,d8,cc */
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,	/* 00,9e,88,cc */
	अणु0xaa, 0x12, 0x0088पूर्ण, /* 00,12,88,aa */
	अणु0xaa, 0x12, 0x0048पूर्ण, /* 00,12,48,aa */
	अणु0xaa, 0x75, 0x008aपूर्ण, /* 00,75,8a,aa */
	अणु0xaa, 0x13, 0x00a3पूर्ण, /* 00,13,a3,aa */
	अणु0xaa, 0x04, 0x0000पूर्ण, /* 00,04,00,aa */
	अणु0xaa, 0x05, 0x0000पूर्ण, /* 00,05,00,aa */
	अणु0xaa, 0x14, 0x0000पूर्ण, /* 00,14,00,aa */
	अणु0xaa, 0x15, 0x0004पूर्ण, /* 00,15,04,aa */
	अणु0xaa, 0x24, 0x0088पूर्ण, /* 00,24,88,aa */
	अणु0xaa, 0x25, 0x0078पूर्ण, /* 00,25,78,aa */
	अणु0xaa, 0x17, 0x0018पूर्ण, /* 00,17,18,aa */
	अणु0xaa, 0x18, 0x00baपूर्ण, /* 00,18,ba,aa */
	अणु0xaa, 0x19, 0x0002पूर्ण, /* 00,19,02,aa */
	अणु0xaa, 0x1a, 0x00f2पूर्ण, /* 00,1a,f2,aa */
	अणु0xaa, 0x20, 0x0040पूर्ण, /* 00,20,40,aa */
	अणु0xaa, 0x27, 0x00f6पूर्ण, /* 00,27,f6,aa */
	अणु0xaa, 0x28, 0x00a0पूर्ण, /* 00,28,a0,aa */
	अणु0xaa, 0x21, 0x0000पूर्ण, /* 00,21,00,aa */
	अणु0xaa, 0x2a, 0x0083पूर्ण, /* 00,2a,83,aa */
	अणु0xaa, 0x2b, 0x0096पूर्ण, /* 00,2b,96,aa */
	अणु0xaa, 0x2d, 0x0005पूर्ण, /* 00,2d,05,aa */
	अणु0xaa, 0x74, 0x0020पूर्ण, /* 00,74,20,aa */
	अणु0xaa, 0x61, 0x0068पूर्ण, /* 00,61,68,aa */
	अणु0xaa, 0x64, 0x0088पूर्ण, /* 00,64,88,aa */
	अणु0xaa, 0x00, 0x0000पूर्ण, /* 00,00,00,aa */
	अणु0xaa, 0x06, 0x0080पूर्ण, /* 00,06,80,aa */
	अणु0xaa, 0x01, 0x0090पूर्ण, /* 00,01,90,aa */
	अणु0xaa, 0x02, 0x0030पूर्ण, /* 00,02,30,aa */
	अणु0xa0, 0x77, ZC3XX_R101_SENSORCORRECTIONपूर्ण, /* 01,01,77,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,05,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण, /* 01,00,0d,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,	/* 01,89,06,cc */
	अणु0xa0, 0x00, 0x01adपूर्ण,			/* 01,ad,00,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण, /* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण, /* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,	/* 03,01,08,cc */
	अणु0xa0, 0x68, ZC3XX_R116_RGAINपूर्ण,		/* 01,16,68,cc */
	अणु0xa0, 0x52, ZC3XX_R118_BGAINपूर्ण,		/* 01,18,52,cc */
	अणु0xa0, 0x50, ZC3XX_R11D_GLOBALGAINपूर्ण,	/* 01,1d,50,cc */
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण, /* 01,80,02,cc */
	अणु0xa0, 0x50, ZC3XX_R1A8_DIGITALGAINपूर्ण,	/* 01,a8,50,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action ov7620_50HZ[] = अणु
	अणु0xdd, 0x00, 0x0100पूर्ण,	/* 00,01,00,dd */
	अणु0xaa, 0x2b, 0x0096पूर्ण,	/* 00,2b,96,aa */
	/* enable 1/120s & 1/100s exposures क्रम banding filter */
	अणु0xaa, 0x75, 0x008eपूर्ण,
	अणु0xaa, 0x2d, 0x0005पूर्ण,	/* 00,2d,05,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,04,cc */
	अणु0xa0, 0x18, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,18,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0x83, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,83,cc */
	अणु0xaa, 0x76, 0x0003पूर्ण,				/* 00,76,03,aa */
/*	अणु0xa0, 0x40, ZC3XX_R002_CLOCKSELECTपूर्ण,		 * 00,02,40,cc
							 * अगर mode0 (640x480) */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action ov7620_60HZ[] = अणु
	अणु0xdd, 0x00, 0x0100पूर्ण,			/* 00,01,00,dd */
	अणु0xaa, 0x2b, 0x0000पूर्ण,			/* 00,2b,00,aa */
	/* enable 1/120s & 1/100s exposures क्रम banding filter */
	अणु0xaa, 0x75, 0x008eपूर्ण,
	अणु0xaa, 0x2d, 0x0005पूर्ण,			/* 00,2d,05,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,04,cc */
	अणु0xa0, 0x18, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,18,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x83, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,83,cc */
	अणु0xaa, 0x76, 0x0003पूर्ण,			/* 00,76,03,aa */
/*	अणु0xa0, 0x40, ZC3XX_R002_CLOCKSELECTपूर्ण,	 * 00,02,40,cc
						 * अगर mode0 (640x480) */
/* ?? in gspca v1, it was
	अणु0xa0, 0x00, 0x0039पूर्ण,  * 00,00,00,dd *
	अणु0xa1, 0x01, 0x0037पूर्ण,		*/
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action ov7620_NoFliker[] = अणु
	अणु0xdd, 0x00, 0x0100पूर्ण,			/* 00,01,00,dd */
	अणु0xaa, 0x2b, 0x0000पूर्ण,			/* 00,2b,00,aa */
	/* disable 1/120s & 1/100s exposures क्रम banding filter */
	अणु0xaa, 0x75, 0x008aपूर्ण,
	अणु0xaa, 0x2d, 0x0001पूर्ण,			/* 00,2d,01,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,04,cc */
	अणु0xa0, 0x18, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,18,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x01, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,01,cc */
/*	अणु0xa0, 0x44, ZC3XX_R002_CLOCKSELECTपूर्ण,	 * 00,02,44,cc
						 * अगर mode1 (320x240) */
/* ?? was
	अणु0xa0, 0x00, 0x0039पूर्ण,  * 00,00,00,dd *
	अणु0xa1, 0x01, 0x0037पूर्ण,		*/
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action ov7630c_InitialScale[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0xa1, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R08D_COMPABILITYMODEपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xaa, 0x12, 0x0080पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R083_RGAINADDRपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R085_BGAINADDRपूर्ण,
	अणु0xa0, 0x90, ZC3XX_R086_EXPTIMEHIGHपूर्ण,
	अणु0xa0, 0x91, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R088_EXPTIMELOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xd8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xaa, 0x12, 0x0069पूर्ण,
	अणु0xaa, 0x04, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0050पूर्ण,
	अणु0xaa, 0x13, 0x0083पूर्ण,
	अणु0xaa, 0x14, 0x0000पूर्ण,
	अणु0xaa, 0x15, 0x0024पूर्ण,
	अणु0xaa, 0x17, 0x0018पूर्ण,
	अणु0xaa, 0x18, 0x00baपूर्ण,
	अणु0xaa, 0x19, 0x0002पूर्ण,
	अणु0xaa, 0x1a, 0x00f6पूर्ण,
	अणु0xaa, 0x1b, 0x0002पूर्ण,
	अणु0xaa, 0x20, 0x00c2पूर्ण,
	अणु0xaa, 0x24, 0x0060पूर्ण,
	अणु0xaa, 0x25, 0x0040पूर्ण,
	अणु0xaa, 0x26, 0x0030पूर्ण,
	अणु0xaa, 0x27, 0x00eaपूर्ण,
	अणु0xaa, 0x28, 0x00a0पूर्ण,
	अणु0xaa, 0x21, 0x0000पूर्ण,
	अणु0xaa, 0x2a, 0x0081पूर्ण,
	अणु0xaa, 0x2b, 0x0096पूर्ण,
	अणु0xaa, 0x2d, 0x0094पूर्ण,
	अणु0xaa, 0x2f, 0x003dपूर्ण,
	अणु0xaa, 0x30, 0x0024पूर्ण,
	अणु0xaa, 0x60, 0x0000पूर्ण,
	अणु0xaa, 0x61, 0x0040पूर्ण,
	अणु0xaa, 0x68, 0x007cपूर्ण,
	अणु0xaa, 0x6f, 0x0015पूर्ण,
	अणु0xaa, 0x75, 0x0088पूर्ण,
	अणु0xaa, 0x77, 0x00b5पूर्ण,
	अणु0xaa, 0x01, 0x0060पूर्ण,
	अणु0xaa, 0x02, 0x0060पूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x77, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x46, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R113_RGB03पूर्ण,
/* 0x10, */
	अणु0xa1, 0x01, 0x0002पूर्ण,
	अणु0xa0, 0x50, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xf8, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x50, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x50, ZC3XX_R112_RGB22पूर्ण,
	अणु0xa1, 0x01, 0x0008पूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* घड़ी ? */
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,	/* sharpness+ */
	अणु0xa1, 0x01, 0x01c8पूर्ण,
	अणु0xa1, 0x01, 0x01c9पूर्ण,
	अणु0xa1, 0x01, 0x01caपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* sharpness- */
	अणु0xa0, 0x01, ZC3XX_R120_GAMMA00पूर्ण,	/* gamma 2 ?*/
	अणु0xa0, 0x0c, ZC3XX_R121_GAMMA01पूर्ण,
	अणु0xa0, 0x1f, ZC3XX_R122_GAMMA02पूर्ण,
	अणु0xa0, 0x3a, ZC3XX_R123_GAMMA03पूर्ण,
	अणु0xa0, 0x53, ZC3XX_R124_GAMMA04पूर्ण,
	अणु0xa0, 0x6d, ZC3XX_R125_GAMMA05पूर्ण,
	अणु0xa0, 0x85, ZC3XX_R126_GAMMA06पूर्ण,
	अणु0xa0, 0x9c, ZC3XX_R127_GAMMA07पूर्ण,
	अणु0xa0, 0xb0, ZC3XX_R128_GAMMA08पूर्ण,
	अणु0xa0, 0xc2, ZC3XX_R129_GAMMA09पूर्ण,
	अणु0xa0, 0xd1, ZC3XX_R12A_GAMMA0Aपूर्ण,
	अणु0xa0, 0xde, ZC3XX_R12B_GAMMA0Bपूर्ण,
	अणु0xa0, 0xe9, ZC3XX_R12C_GAMMA0Cपूर्ण,
	अणु0xa0, 0xf2, ZC3XX_R12D_GAMMA0Dपूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R12E_GAMMA0Eपूर्ण,
	अणु0xa0, 0xff, ZC3XX_R12F_GAMMA0Fपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R130_GAMMA10पूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R131_GAMMA11पूर्ण,
	अणु0xa0, 0x16, ZC3XX_R132_GAMMA12पूर्ण,
	अणु0xa0, 0x1a, ZC3XX_R133_GAMMA13पूर्ण,
	अणु0xa0, 0x19, ZC3XX_R134_GAMMA14पूर्ण,
	अणु0xa0, 0x19, ZC3XX_R135_GAMMA15पूर्ण,
	अणु0xa0, 0x17, ZC3XX_R136_GAMMA16पूर्ण,
	अणु0xa0, 0x15, ZC3XX_R137_GAMMA17पूर्ण,
	अणु0xa0, 0x12, ZC3XX_R138_GAMMA18पूर्ण,
	अणु0xa0, 0x10, ZC3XX_R139_GAMMA19पूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R13A_GAMMA1Aपूर्ण,
	अणु0xa0, 0x0b, ZC3XX_R13B_GAMMA1Bपूर्ण,
	अणु0xa0, 0x09, ZC3XX_R13C_GAMMA1Cपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R13D_GAMMA1Dपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R13E_GAMMA1Eपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R13F_GAMMA1Fपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xf8, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x50, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x50, ZC3XX_R112_RGB22पूर्ण,

	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xaa, 0x10, 0x001bपूर्ण,
	अणु0xaa, 0x76, 0x0002पूर्ण,
	अणु0xaa, 0x2a, 0x0081पूर्ण,
	अणु0xaa, 0x2b, 0x0000पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xb8, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x37, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x26, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xaa, 0x13, 0x0083पूर्ण,	/* 40 */
	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action ov7630c_Initial[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0xa1, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R08D_COMPABILITYMODEपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,

	अणु0xaa, 0x12, 0x0080पूर्ण,
	अणु0xa0, 0x02, ZC3XX_R083_RGAINADDRपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R085_BGAINADDRपूर्ण,
	अणु0xa0, 0x90, ZC3XX_R086_EXPTIMEHIGHपूर्ण,
	अणु0xa0, 0x91, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R088_EXPTIMELOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xe6, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xaa, 0x12, 0x0069पूर्ण,	/* i2c */
	अणु0xaa, 0x04, 0x0020पूर्ण,
	अणु0xaa, 0x06, 0x0050पूर्ण,
	अणु0xaa, 0x13, 0x00c3पूर्ण,
	अणु0xaa, 0x14, 0x0000पूर्ण,
	अणु0xaa, 0x15, 0x0024पूर्ण,
	अणु0xaa, 0x19, 0x0003पूर्ण,
	अणु0xaa, 0x1a, 0x00f6पूर्ण,
	अणु0xaa, 0x1b, 0x0002पूर्ण,
	अणु0xaa, 0x20, 0x00c2पूर्ण,
	अणु0xaa, 0x24, 0x0060पूर्ण,
	अणु0xaa, 0x25, 0x0040पूर्ण,
	अणु0xaa, 0x26, 0x0030पूर्ण,
	अणु0xaa, 0x27, 0x00eaपूर्ण,
	अणु0xaa, 0x28, 0x00a0पूर्ण,
	अणु0xaa, 0x21, 0x0000पूर्ण,
	अणु0xaa, 0x2a, 0x0081पूर्ण,
	अणु0xaa, 0x2b, 0x0096पूर्ण,
	अणु0xaa, 0x2d, 0x0084पूर्ण,
	अणु0xaa, 0x2f, 0x003dपूर्ण,
	अणु0xaa, 0x30, 0x0024पूर्ण,
	अणु0xaa, 0x60, 0x0000पूर्ण,
	अणु0xaa, 0x61, 0x0040पूर्ण,
	अणु0xaa, 0x68, 0x007cपूर्ण,
	अणु0xaa, 0x6f, 0x0015पूर्ण,
	अणु0xaa, 0x75, 0x0088पूर्ण,
	अणु0xaa, 0x77, 0x00b5पूर्ण,
	अणु0xaa, 0x01, 0x0060पूर्ण,
	अणु0xaa, 0x02, 0x0060पूर्ण,
	अणु0xaa, 0x17, 0x0018पूर्ण,
	अणु0xaa, 0x18, 0x00baपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x77, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R1A7_CALCGLOBALMEANपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x46, ZC3XX_R118_BGAINपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R113_RGB03पूर्ण,

	अणु0xa1, 0x01, 0x0002पूर्ण,
	अणु0xa0, 0x4e, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xfe, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x4d, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xfc, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf6, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x4a, ZC3XX_R112_RGB22पूर्ण,

	अणु0xa1, 0x01, 0x0008पूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* घड़ी ? */
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,	/* sharpness+ */
	अणु0xa1, 0x01, 0x01c8पूर्ण,
	अणु0xa1, 0x01, 0x01c9पूर्ण,
	अणु0xa1, 0x01, 0x01caपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,	/* sharpness- */
	अणु0xa0, 0x16, ZC3XX_R120_GAMMA00पूर्ण,	/* gamma ~4 */
	अणु0xa0, 0x3a, ZC3XX_R121_GAMMA01पूर्ण,
	अणु0xa0, 0x5b, ZC3XX_R122_GAMMA02पूर्ण,
	अणु0xa0, 0x7c, ZC3XX_R123_GAMMA03पूर्ण,
	अणु0xa0, 0x94, ZC3XX_R124_GAMMA04पूर्ण,
	अणु0xa0, 0xa9, ZC3XX_R125_GAMMA05पूर्ण,
	अणु0xa0, 0xbb, ZC3XX_R126_GAMMA06पूर्ण,
	अणु0xa0, 0xca, ZC3XX_R127_GAMMA07पूर्ण,
	अणु0xa0, 0xd7, ZC3XX_R128_GAMMA08पूर्ण,
	अणु0xa0, 0xe1, ZC3XX_R129_GAMMA09पूर्ण,
	अणु0xa0, 0xea, ZC3XX_R12A_GAMMA0Aपूर्ण,
	अणु0xa0, 0xf1, ZC3XX_R12B_GAMMA0Bपूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R12C_GAMMA0Cपूर्ण,
	अणु0xa0, 0xfc, ZC3XX_R12D_GAMMA0Dपूर्ण,
	अणु0xa0, 0xff, ZC3XX_R12E_GAMMA0Eपूर्ण,
	अणु0xa0, 0xff, ZC3XX_R12F_GAMMA0Fपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R130_GAMMA10पूर्ण,
	अणु0xa0, 0x22, ZC3XX_R131_GAMMA11पूर्ण,
	अणु0xa0, 0x20, ZC3XX_R132_GAMMA12पूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R133_GAMMA13पूर्ण,
	अणु0xa0, 0x16, ZC3XX_R134_GAMMA14पूर्ण,
	अणु0xa0, 0x13, ZC3XX_R135_GAMMA15पूर्ण,
	अणु0xa0, 0x10, ZC3XX_R136_GAMMA16पूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R137_GAMMA17पूर्ण,
	अणु0xa0, 0x0b, ZC3XX_R138_GAMMA18पूर्ण,
	अणु0xa0, 0x09, ZC3XX_R139_GAMMA19पूर्ण,
	अणु0xa0, 0x07, ZC3XX_R13A_GAMMA1Aपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R13B_GAMMA1Bपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R13C_GAMMA1Cपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R13D_GAMMA1Dपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R13E_GAMMA1Eपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R13F_GAMMA1Fपूर्ण,
	अणु0xa0, 0x4e, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xfe, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x4d, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xfc, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf6, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x4a, ZC3XX_R112_RGB22पूर्ण,

	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xaa, 0x10, 0x000dपूर्ण,
	अणु0xaa, 0x76, 0x0002पूर्ण,
	अणु0xaa, 0x2a, 0x0081पूर्ण,
	अणु0xaa, 0x2b, 0x0000पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xd8, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x1b, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x26, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xaa, 0x13, 0x00c3पूर्ण,

	अणु0xa1, 0x01, 0x0180पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action pas106b_Initial_com[] = अणु
/* Sream and Sensor specअगरic */
	अणु0xa1, 0x01, 0x0010पूर्ण,	/* CMOSSensorSelect */
/* System */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,	/* SystemControl */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,	/* SystemControl */
/* Picture size */
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,	/* ClockSelect */
	अणु0xa0, 0x03, 0x003aपूर्ण,
	अणु0xa0, 0x0c, 0x003bपूर्ण,
	अणु0xa0, 0x04, 0x0038पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action pas106b_InitialScale[] = अणु	/* 176x144 */
/* JPEG control */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
/* Sream and Sensor specअगरic */
	अणु0xa0, 0x0f, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
/* Picture size */
	अणु0xa0, 0x00, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0xb0, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0x90, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
/* System */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
/* Sream and Sensor specअगरic */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
/* Sensor Interface */
	अणु0xa0, 0x08, ZC3XX_R08D_COMPABILITYMODEपूर्ण,
/* Winकरोw inside sensor array */
	अणु0xa0, 0x03, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0x28, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x68, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
/* Init the sensor */
	अणु0xaa, 0x02, 0x0004पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x09, 0x0005पूर्ण,
	अणु0xaa, 0x0a, 0x0002पूर्ण,
	अणु0xaa, 0x0b, 0x0002पूर्ण,
	अणु0xaa, 0x0c, 0x0005पूर्ण,
	अणु0xaa, 0x0d, 0x0000पूर्ण,
	अणु0xaa, 0x0e, 0x0002पूर्ण,
	अणु0xaa, 0x14, 0x0081पूर्ण,
/* Other रेजिस्टरs */
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
/* Frame retrieving */
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
/* Gains */
	अणु0xa0, 0xa0, ZC3XX_R1A8_DIGITALGAINपूर्ण,
/* Unknown */
	अणु0xa0, 0x00, 0x01adपूर्ण,
/* Sharpness */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
/* Other रेजिस्टरs */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
/* Auto exposure and white balance */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
/*Dead pixels */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
/* EEPROM */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
/* JPEG control */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,
/* Other रेजिस्टरs */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
/* Auto exposure and white balance */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
/*Dead pixels */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
/* EEPROM */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
/* JPEG control */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,

	अणु0xa0, 0x58, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xf4, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x58, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x58, ZC3XX_R112_RGB22पूर्ण,
/* Auto correction */
	अणु0xa0, 0x03, ZC3XX_R181_WINXSTARTपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R182_WINXWIDTHपूर्ण,
	अणु0xa0, 0x16, ZC3XX_R183_WINXCENTERपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R184_WINYSTARTपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R185_WINYWIDTHपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R186_WINYCENTERपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
/* Auto exposure and white balance */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xb1, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x87, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,
/* sensor on */
	अणु0xaa, 0x07, 0x00b1पूर्ण,
	अणु0xaa, 0x05, 0x0003पूर्ण,
	अणु0xaa, 0x04, 0x0001पूर्ण,
	अणु0xaa, 0x03, 0x003bपूर्ण,
/* Gains */
	अणु0xa0, 0x20, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x26, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xa0, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
/* Auto correction */
	अणु0xa0, 0x40, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,				/* AutoCorrectEnable */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
/* Gains */
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action pas106b_Initial[] = अणु	/* 352x288 */
/* JPEG control */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
/* Sream and Sensor specअगरic */
	अणु0xa0, 0x0f, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
/* Picture size */
	अणु0xa0, 0x01, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
/* System */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
/* Sream and Sensor specअगरic */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
/* Sensor Interface */
	अणु0xa0, 0x08, ZC3XX_R08D_COMPABILITYMODEपूर्ण,
/* Winकरोw inside sensor array */
	अणु0xa0, 0x03, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0x28, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x68, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
/* Init the sensor */
	अणु0xaa, 0x02, 0x0004पूर्ण,
	अणु0xaa, 0x08, 0x0000पूर्ण,
	अणु0xaa, 0x09, 0x0005पूर्ण,
	अणु0xaa, 0x0a, 0x0002पूर्ण,
	अणु0xaa, 0x0b, 0x0002पूर्ण,
	अणु0xaa, 0x0c, 0x0005पूर्ण,
	अणु0xaa, 0x0d, 0x0000पूर्ण,
	अणु0xaa, 0x0e, 0x0002पूर्ण,
	अणु0xaa, 0x14, 0x0081पूर्ण,
/* Other रेजिस्टरs */
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
/* Frame retrieving */
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
/* Gains */
	अणु0xa0, 0xa0, ZC3XX_R1A8_DIGITALGAINपूर्ण,
/* Unknown */
	अणु0xa0, 0x00, 0x01adपूर्ण,
/* Sharpness */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
/* Other रेजिस्टरs */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
/* Auto exposure and white balance */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R18D_YTARGETपूर्ण,
/*Dead pixels */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
/* EEPROM */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
/* JPEG control */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,
/* Other रेजिस्टरs */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
/* Auto exposure and white balance */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
/*Dead pixels */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
/* EEPROM */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
/* JPEG control */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R1C6_SHARPNESS00पूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R1CB_SHARPNESS05पूर्ण,

	अणु0xa0, 0x58, ZC3XX_R10A_RGB00पूर्ण,	/* matrix */
	अणु0xa0, 0xf4, ZC3XX_R10B_RGB01पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10C_RGB02पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10D_RGB10पूर्ण,
	अणु0xa0, 0x58, ZC3XX_R10E_RGB11पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R10F_RGB12पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R110_RGB20पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R111_RGB21पूर्ण,
	अणु0xa0, 0x58, ZC3XX_R112_RGB22पूर्ण,
/* Auto correction */
	अणु0xa0, 0x03, ZC3XX_R181_WINXSTARTपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R182_WINXWIDTHपूर्ण,
	अणु0xa0, 0x16, ZC3XX_R183_WINXCENTERपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R184_WINYSTARTपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R185_WINYWIDTHपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R186_WINYCENTERपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,

/* Auto exposure and white balance */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xb1, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,

	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x87, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,

	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
/* sensor on */
	अणु0xaa, 0x07, 0x00b1पूर्ण,
	अणु0xaa, 0x05, 0x0003पूर्ण,
	अणु0xaa, 0x04, 0x0001पूर्ण,
	अणु0xaa, 0x03, 0x003bपूर्ण,
/* Gains */
	अणु0xa0, 0x20, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x26, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
/* Auto correction */
	अणु0xa0, 0x40, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa1, 0x01, 0x0180पूर्ण,				/* AutoCorrectEnable */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
/* Gains */
	अणु0xa0, 0x40, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R117_GGAINपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R118_BGAINपूर्ण,

	अणु0xa0, 0x00, 0x0007पूर्ण,			/* AutoCorrectEnable */
	अणु0xa0, 0xff, ZC3XX_R018_FRAMELOSTपूर्ण,	/* Frame adjust */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas106b_50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x06, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,06,cc */
	अणु0xa0, 0x54, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,54,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x87, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,87,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,10,cc */
	अणु0xa0, 0x30, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,30,cc */
	अणु0xaa, 0x03, 0x0021पूर्ण,			/* 00,03,21,aa */
	अणु0xaa, 0x04, 0x000cपूर्ण,			/* 00,04,0c,aa */
	अणु0xaa, 0x05, 0x0002पूर्ण,			/* 00,05,02,aa */
	अणु0xaa, 0x07, 0x001cपूर्ण,			/* 00,07,1c,aa */
	अणु0xa0, 0x04, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,04,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas106b_60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x06, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,06,cc */
	अणु0xa0, 0x2e, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,2e,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x71, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,71,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,10,cc */
	अणु0xa0, 0x30, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,30,cc */
	अणु0xaa, 0x03, 0x001cपूर्ण,			/* 00,03,1c,aa */
	अणु0xaa, 0x04, 0x0004पूर्ण,			/* 00,04,04,aa */
	अणु0xaa, 0x05, 0x0001पूर्ण,			/* 00,05,01,aa */
	अणु0xaa, 0x07, 0x00c4पूर्ण,			/* 00,07,c4,aa */
	अणु0xa0, 0x04, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,04,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas106b_NoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x06, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,06,cc */
	अणु0xa0, 0x50, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,50,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x10, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,10,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,	/* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,	/* 01,8f,20,cc */
	अणु0xaa, 0x03, 0x0013पूर्ण,			/* 00,03,13,aa */
	अणु0xaa, 0x04, 0x0000पूर्ण,			/* 00,04,00,aa */
	अणु0xaa, 0x05, 0x0001पूर्ण,			/* 00,05,01,aa */
	अणु0xaa, 0x07, 0x0030पूर्ण,			/* 00,07,30,aa */
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,00,cc */
	अणुपूर्ण
पूर्ण;

/* from lvWIMv.inf 046d:08a2/:08aa 2007/06/03 */
अटल स्थिर काष्ठा usb_action pas202b_Initial[] = अणु	/* 640x480 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,		/* 00,00,01,cc */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0e,cc */
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,		/* 00,02,00,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,	/* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,		/* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,	/* 00,05,01,cc */
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,	/* 00,06,e0,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,	/* 00,01,01,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,01,cc */
	अणु0xa0, 0x08, ZC3XX_R08D_COMPABILITYMODEपूर्ण,	/* 00,8d,08,cc */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,		/* 00,98,00,cc */
	अणु0xa0, 0x03, ZC3XX_R09A_WINXSTARTLOWपूर्ण,		/* 00,9a,03,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,		/* 01,1a,00,cc */
	अणु0xa0, 0x03, ZC3XX_R11C_FIRSTXLOWपूर्ण,		/* 01,1c,03,cc */
	अणु0xa0, 0x01, ZC3XX_R09B_WINHEIGHTHIGHपूर्ण,		/* 00,9b,01,cc */
	अणु0xa0, 0xe6, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,		/* 00,9c,e6,cc */
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण,		/* 00,9d,02,cc */
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण,		/* 00,9e,86,cc */
	अणु0xaa, 0x02, 0x0002पूर्ण,			/* 00,02,04,aa --> 02 */
	अणु0xaa, 0x07, 0x0006पूर्ण,				/* 00,07,06,aa */
	अणु0xaa, 0x08, 0x0002पूर्ण,				/* 00,08,02,aa */
	अणु0xaa, 0x09, 0x0006पूर्ण,				/* 00,09,06,aa */
	अणु0xaa, 0x0a, 0x0001पूर्ण,				/* 00,0a,01,aa */
	अणु0xaa, 0x0b, 0x0001पूर्ण,				/* 00,0b,01,aa */
	अणु0xaa, 0x0c, 0x0006पूर्ण,
	अणु0xaa, 0x0d, 0x0000पूर्ण,				/* 00,0d,00,aa */
	अणु0xaa, 0x10, 0x0000पूर्ण,				/* 00,10,00,aa */
	अणु0xaa, 0x12, 0x0005पूर्ण,				/* 00,12,05,aa */
	अणु0xaa, 0x13, 0x0063पूर्ण,				/* 00,13,63,aa */
	अणु0xaa, 0x15, 0x0070पूर्ण,				/* 00,15,70,aa */
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,	/* 01,01,b7,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,		/* 01,00,0d,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,		/* 01,89,06,cc */
	अणु0xa0, 0x00, 0x01adपूर्ण,				/* 01,ad,00,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,		/* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,		/* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,	/* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,		/* 03,01,08,cc */
	अणु0xa0, 0x70, ZC3XX_R18D_YTARGETपूर्ण,		/* 01,8d,70,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas202b_InitialScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,		/* 00,00,01,cc */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,0e,cc */
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,		/* 00,02,10,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,	/* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,		/* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,	/* 00,05,01,cc */
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,	/* 00,01,01,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,01,cc */
	अणु0xa0, 0x08, ZC3XX_R08D_COMPABILITYMODEपूर्ण,	/* 00,8d,08,cc */
	अणु0xa0, 0x08, ZC3XX_R098_WINYSTARTLOWपूर्ण,		/* 00,98,08,cc */
	अणु0xa0, 0x02, ZC3XX_R09A_WINXSTARTLOWपूर्ण,		/* 00,9a,02,cc */
	अणु0xa0, 0x08, ZC3XX_R11A_FIRSTYLOWपूर्ण,		/* 01,1a,08,cc */
	अणु0xa0, 0x02, ZC3XX_R11C_FIRSTXLOWपूर्ण,		/* 01,1c,02,cc */
	अणु0xa0, 0x01, ZC3XX_R09B_WINHEIGHTHIGHपूर्ण,		/* 00,9b,01,cc */
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण,		/* 00,9d,02,cc */
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,		/* 00,9e,88,cc */
	अणु0xaa, 0x02, 0x0002पूर्ण,				/* 00,02,02,aa */
	अणु0xaa, 0x07, 0x0006पूर्ण,				/* 00,07,06,aa */
	अणु0xaa, 0x08, 0x0002पूर्ण,				/* 00,08,02,aa */
	अणु0xaa, 0x09, 0x0006पूर्ण,				/* 00,09,06,aa */
	अणु0xaa, 0x0a, 0x0001पूर्ण,				/* 00,0a,01,aa */
	अणु0xaa, 0x0b, 0x0001पूर्ण,				/* 00,0b,01,aa */
	अणु0xaa, 0x0c, 0x0006पूर्ण,
	अणु0xaa, 0x0d, 0x0000पूर्ण,				/* 00,0d,00,aa */
	अणु0xaa, 0x10, 0x0000पूर्ण,				/* 00,10,00,aa */
	अणु0xaa, 0x12, 0x0005पूर्ण,				/* 00,12,05,aa */
	अणु0xaa, 0x13, 0x0063पूर्ण,				/* 00,13,63,aa */
	अणु0xaa, 0x15, 0x0070पूर्ण,				/* 00,15,70,aa */
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,	/* 01,01,37,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,		/* 01,00,0d,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,		/* 01,89,06,cc */
	अणु0xa0, 0x00, 0x01adपूर्ण,				/* 01,ad,00,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,		/* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,		/* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,	/* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,		/* 03,01,08,cc */
	अणु0xa0, 0x70, ZC3XX_R18D_YTARGETपूर्ण,		/* 01,8d,70,cc */
	अणु0xa0, 0xff, ZC3XX_R097_WINYSTARTHIGHपूर्ण,
	अणु0xa0, 0xfe, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas202b_50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,		/* 00,19,00,cc */
	अणु0xa0, 0x20, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,20,cc */
	अणु0xa0, 0x21, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,21,cc */
	अणु0xaa, 0x20, 0x0002पूर्ण,				/* 00,20,02,aa */
	अणु0xaa, 0x21, 0x001bपूर्ण,
	अणु0xaa, 0x03, 0x0044पूर्ण,				/* 00,03,44,aa */
	अणु0xaa, 0x04, 0x0008पूर्ण,
	अणु0xaa, 0x05, 0x001bपूर्ण,
	अणु0xaa, 0x0e, 0x0001पूर्ण,				/* 00,0e,01,aa */
	अणु0xaa, 0x0f, 0x0000पूर्ण,				/* 00,0f,00,aa */
	अणु0xa0, 0x1c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x02, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x1b, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0x4d, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,4d,cc */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1b, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x44, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,44,cc */
	अणु0xa0, 0x6f, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,6f,cc */
	अणु0xa0, 0xad, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,ad,cc */
	अणु0xa0, 0xeb, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,eb,cc */
	अणु0xa0, 0x0f, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,0f,cc */
	अणु0xa0, 0x0e, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,0e,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas202b_50HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,		/* 00,19,00,cc */
	अणु0xa0, 0x20, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,20,cc */
	अणु0xa0, 0x21, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,21,cc */
	अणु0xaa, 0x20, 0x0004पूर्ण,
	अणु0xaa, 0x21, 0x003dपूर्ण,
	अणु0xaa, 0x03, 0x0041पूर्ण,				/* 00,03,41,aa */
	अणु0xaa, 0x04, 0x0010पूर्ण,
	अणु0xaa, 0x05, 0x003dपूर्ण,
	अणु0xaa, 0x0e, 0x0001पूर्ण,				/* 00,0e,01,aa */
	अणु0xaa, 0x0f, 0x0000पूर्ण,				/* 00,0f,00,aa */
	अणु0xa0, 0x1c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x3d, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0x9b, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,9b,cc */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1b, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x41, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,41,cc */
	अणु0xa0, 0x6f, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,6f,cc */
	अणु0xa0, 0xad, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,ad,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,ff,cc */
	अणु0xa0, 0x0f, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,0f,cc */
	अणु0xa0, 0x0e, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,0e,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas202b_60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,		/* 00,19,00,cc */
	अणु0xa0, 0x20, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,20,cc */
	अणु0xa0, 0x21, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,21,cc */
	अणु0xaa, 0x20, 0x0002पूर्ण,				/* 00,20,02,aa */
	अणु0xaa, 0x21, 0x0000पूर्ण,				/* 00,21,00,aa */
	अणु0xaa, 0x03, 0x0045पूर्ण,				/* 00,03,45,aa */
	अणु0xaa, 0x04, 0x0008पूर्ण,				/* 00,04,08,aa */
	अणु0xaa, 0x05, 0x0000पूर्ण,				/* 00,05,00,aa */
	अणु0xaa, 0x0e, 0x0001पूर्ण,				/* 00,0e,01,aa */
	अणु0xaa, 0x0f, 0x0000पूर्ण,				/* 00,0f,00,aa */
	अणु0xa0, 0x1c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x02, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0x40, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,40,cc */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1b, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x45, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,45,cc */
	अणु0xa0, 0x8e, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,8e,cc */
	अणु0xa0, 0xc1, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,c1,cc */
	अणु0xa0, 0xf5, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,f5,cc */
	अणु0xa0, 0x0f, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,0f,cc */
	अणु0xa0, 0x0e, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,0e,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas202b_60HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,		/* 00,19,00,cc */
	अणु0xa0, 0x20, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,20,cc */
	अणु0xa0, 0x21, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,21,cc */
	अणु0xaa, 0x20, 0x0004पूर्ण,
	अणु0xaa, 0x21, 0x0008पूर्ण,
	अणु0xaa, 0x03, 0x0042पूर्ण,				/* 00,03,42,aa */
	अणु0xaa, 0x04, 0x0010पूर्ण,
	अणु0xaa, 0x05, 0x0008पूर्ण,
	अणु0xaa, 0x0e, 0x0001पूर्ण,				/* 00,0e,01,aa */
	अणु0xaa, 0x0f, 0x0000पूर्ण,				/* 00,0f,00,aa */
	अणु0xa0, 0x1c, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0x81, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,81,cc */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1b, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,42,cc */
	अणु0xa0, 0x6f, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,6f,cc */
	अणु0xa0, 0xaf, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,af,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,ff,cc */
	अणु0xa0, 0x0f, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,0f,cc */
	अणु0xa0, 0x0e, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,0e,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas202b_NoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,		/* 00,19,00,cc */
	अणु0xa0, 0x20, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,20,cc */
	अणु0xa0, 0x21, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,21,cc */
	अणु0xaa, 0x20, 0x0002पूर्ण,				/* 00,20,02,aa */
	अणु0xaa, 0x21, 0x0006पूर्ण,
	अणु0xaa, 0x03, 0x0040पूर्ण,				/* 00,03,40,aa */
	अणु0xaa, 0x04, 0x0008पूर्ण,				/* 00,04,08,aa */
	अणु0xaa, 0x05, 0x0006पूर्ण,
	अणु0xaa, 0x0e, 0x0001पूर्ण,				/* 00,0e,01,aa */
	अणु0xaa, 0x0f, 0x0000पूर्ण,				/* 00,0f,00,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x02, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0x01, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,		/* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,		/* 01,8f,20,cc */
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,00,cc */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,40,cc */
	अणु0xa0, 0x60, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,60,cc */
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,90,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,ff,cc */
	अणु0xa0, 0x0f, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,0f,cc */
	अणु0xa0, 0x0e, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,0e,cc */
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pas202b_NoFlikerScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,		/* 00,19,00,cc */
	अणु0xa0, 0x20, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,20,cc */
	अणु0xa0, 0x21, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,21,cc */
	अणु0xaa, 0x20, 0x0004पूर्ण,
	अणु0xaa, 0x21, 0x000cपूर्ण,
	अणु0xaa, 0x03, 0x0040पूर्ण,				/* 00,03,40,aa */
	अणु0xaa, 0x04, 0x0010पूर्ण,
	अणु0xaa, 0x05, 0x000cपूर्ण,
	अणु0xaa, 0x0e, 0x0001पूर्ण,				/* 00,0e,01,aa */
	अणु0xaa, 0x0f, 0x0000पूर्ण,				/* 00,0f,00,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc */
	अणु0xa0, 0x02, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,02,cc */
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,		/* 01,8c,10,cc */
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,		/* 01,8f,20,cc */
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,00,cc */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,40,cc */
	अणु0xa0, 0x60, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,60,cc */
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,90,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,ff,cc */
	अणु0xa0, 0x0f, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,0f,cc */
	अणु0xa0, 0x0e, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,0e,cc */
	अणुपूर्ण
पूर्ण;

/* mt9v111 (mi0360soc) and pb0330 from vm30x.inf 0ac8:301b 07/02/13 */
अटल स्थिर काष्ठा usb_action mt9v111_1_Initial[] = अणु	/* 640x480 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0xdc, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xdc, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xdd, 0x00, 0x0200पूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xaa, 0x01, 0x0001पूर्ण,
	अणु0xaa, 0x06, 0x0000पूर्ण,
	अणु0xaa, 0x08, 0x0483पूर्ण,
	अणु0xaa, 0x01, 0x0004पूर्ण,
	अणु0xaa, 0x08, 0x0006पूर्ण,
	अणु0xaa, 0x02, 0x0011पूर्ण,
	अणु0xaa, 0x03, 0x01e5पूर्ण,			/*jfm: was 01e7*/
	अणु0xaa, 0x04, 0x0285पूर्ण,			/*jfm: was 0287*/
	अणु0xaa, 0x07, 0x3002पूर्ण,
	अणु0xaa, 0x20, 0x5100पूर्ण,
	अणु0xaa, 0x35, 0x507fपूर्ण,
	अणु0xaa, 0x30, 0x0005पूर्ण,
	अणु0xaa, 0x31, 0x0000पूर्ण,
	अणु0xaa, 0x58, 0x0078पूर्ण,
	अणु0xaa, 0x62, 0x0411पूर्ण,
	अणु0xaa, 0x2b, 0x007fपूर्ण,
	अणु0xaa, 0x2c, 0x007fपूर्ण,			/*jfm: was 0030*/
	अणु0xaa, 0x2d, 0x007fपूर्ण,			/*jfm: was 0030*/
	अणु0xaa, 0x2e, 0x007fपूर्ण,			/*jfm: was 0030*/
	अणु0xa0, 0x10, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x09, 0x01adपूर्ण,			/*jfm: was 00*/
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x6c, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x61, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x65, ZC3XX_R118_BGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_1_InitialScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0xdc, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xdc, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xdd, 0x00, 0x0200पूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xaa, 0x01, 0x0001पूर्ण,
	अणु0xaa, 0x06, 0x0000पूर्ण,
	अणु0xaa, 0x08, 0x0483पूर्ण,
	अणु0xaa, 0x01, 0x0004पूर्ण,
	अणु0xaa, 0x08, 0x0006पूर्ण,
	अणु0xaa, 0x02, 0x0011पूर्ण,
	अणु0xaa, 0x03, 0x01e7पूर्ण,
	अणु0xaa, 0x04, 0x0287पूर्ण,
	अणु0xaa, 0x07, 0x3002पूर्ण,
	अणु0xaa, 0x20, 0x5100पूर्ण,
	अणु0xaa, 0x35, 0x007fपूर्ण,			/*jfm: was 0050*/
	अणु0xaa, 0x30, 0x0005पूर्ण,
	अणु0xaa, 0x31, 0x0000पूर्ण,
	अणु0xaa, 0x58, 0x0078पूर्ण,
	अणु0xaa, 0x62, 0x0411पूर्ण,
	अणु0xaa, 0x2b, 0x007fपूर्ण,			/*jfm: was 28*/
	अणु0xaa, 0x2c, 0x007fपूर्ण,			/*jfm: was 30*/
	अणु0xaa, 0x2d, 0x007fपूर्ण,			/*jfm: was 30*/
	अणु0xaa, 0x2e, 0x007fपूर्ण,			/*jfm: was 28*/
	अणु0xa0, 0x10, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x09, 0x01adपूर्ण,			/*jfm: was 00*/
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x6c, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x61, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x65, ZC3XX_R118_BGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_1_AE50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0562पूर्ण,
	अणु0xbb, 0x01, 0x09aaपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x9b, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x47, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_1_AE50HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0509पूर्ण,
	अणु0xbb, 0x01, 0x0934पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xd2, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x9a, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xd7, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_1_AE60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x05, 0x003dपूर्ण,
	अणु0xaa, 0x09, 0x016eपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xdd, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x3d, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_1_AE60HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0509पूर्ण,
	अणु0xbb, 0x01, 0x0983पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x8f, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x81, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xd7, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_1_AENoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0509पूर्ण,
	अणु0xbb, 0x01, 0x0960पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x09, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x40, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_1_AENoFlikerScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0534पूर्ण,
	अणु0xbb, 0x02, 0x0960पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x34, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
/* from usbvm303.inf 0ac8:303b 07/03/25 (3 - tas5130c) */
अटल स्थिर काष्ठा usb_action mt9v111_3_Initial[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0xdc, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xdc, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xdd, 0x00, 0x0200पूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xaa, 0x01, 0x0001पूर्ण,		/* select IFP/SOC रेजिस्टरs */
	अणु0xaa, 0x06, 0x0000पूर्ण,		/* operating mode control */
	अणु0xaa, 0x08, 0x0483पूर्ण,		/* output क्रमmat control */
					/* H red first, V red or blue first,
					 * raw Bayer, स्वतः flicker */
	अणु0xaa, 0x01, 0x0004पूर्ण,		/* select sensor core रेजिस्टरs */
	अणु0xaa, 0x08, 0x0006पूर्ण,		/* row start */
	अणु0xaa, 0x02, 0x0011पूर्ण,		/* column start */
	अणु0xaa, 0x03, 0x01e5पूर्ण,		/* winकरोw height - 1 */
	अणु0xaa, 0x04, 0x0285पूर्ण,		/* winकरोw width - 1 */
	अणु0xaa, 0x07, 0x3002पूर्ण,		/* output control */
	अणु0xaa, 0x20, 0x1100पूर्ण,		/* पढ़ो mode: bits 8 & 12 (?) */
	अणु0xaa, 0x35, 0x007fपूर्ण,		/* global gain */
	अणु0xaa, 0x30, 0x0005पूर्ण,
	अणु0xaa, 0x31, 0x0000पूर्ण,
	अणु0xaa, 0x58, 0x0078पूर्ण,
	अणु0xaa, 0x62, 0x0411पूर्ण,
	अणु0xaa, 0x2b, 0x007fपूर्ण,		/* green1 gain */
	अणु0xaa, 0x2c, 0x007fपूर्ण,		/* blue gain */
	अणु0xaa, 0x2d, 0x007fपूर्ण,		/* red gain */
	अणु0xaa, 0x2e, 0x007fपूर्ण,		/* green2 gain */
	अणु0xa0, 0x10, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x61, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x65, ZC3XX_R118_BGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_3_InitialScale[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0xdc, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xdc, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,
	अणु0xdd, 0x00, 0x0200पूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xaa, 0x01, 0x0001पूर्ण,
	अणु0xaa, 0x06, 0x0000पूर्ण,
	अणु0xaa, 0x08, 0x0483पूर्ण,
	अणु0xaa, 0x01, 0x0004पूर्ण,
	अणु0xaa, 0x08, 0x0006पूर्ण,
	अणु0xaa, 0x02, 0x0011पूर्ण,
	अणु0xaa, 0x03, 0x01e7पूर्ण,
	अणु0xaa, 0x04, 0x0287पूर्ण,
	अणु0xaa, 0x07, 0x3002पूर्ण,
	अणु0xaa, 0x20, 0x1100पूर्ण,
	अणु0xaa, 0x35, 0x007fपूर्ण,
	अणु0xaa, 0x30, 0x0005पूर्ण,
	अणु0xaa, 0x31, 0x0000पूर्ण,
	अणु0xaa, 0x58, 0x0078पूर्ण,
	अणु0xaa, 0x62, 0x0411पूर्ण,
	अणु0xaa, 0x2b, 0x007fपूर्ण,
	अणु0xaa, 0x2c, 0x007fपूर्ण,
	अणु0xaa, 0x2d, 0x007fपूर्ण,
	अणु0xaa, 0x2e, 0x007fपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x61, ZC3XX_R116_RGAINपूर्ण,
	अणु0xa0, 0x65, ZC3XX_R118_BGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_3_AE50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x05, 0x0009पूर्ण,		/* horizontal blanking */
	अणु0xaa, 0x09, 0x01ceपूर्ण,		/* shutter width */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xd2, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x9a, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xd7, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_3_AE50HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x05, 0x0009पूर्ण,
	अणु0xaa, 0x09, 0x01ceपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xd2, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x9a, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xd7, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_3_AE60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x05, 0x0009पूर्ण,
	अणु0xaa, 0x09, 0x0083पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x8f, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x81, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xd7, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_3_AE60HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x05, 0x0009पूर्ण,
	अणु0xaa, 0x09, 0x0083पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x8f, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x81, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xd7, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xf4, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf9, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_3_AENoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x05, 0x0034पूर्ण,
	अणु0xaa, 0x09, 0x0260पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x34, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action mt9v111_3_AENoFlikerScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xaa, 0x05, 0x0034पूर्ण,
	अणु0xaa, 0x09, 0x0260पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1c, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x34, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R020_HSYNC_3पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action pb0330_Initial[] = अणु	/* 640x480 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* 00 */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xdd, 0x00, 0x0200पूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xaa, 0x01, 0x0006पूर्ण,
	अणु0xaa, 0x02, 0x0011पूर्ण,
	अणु0xaa, 0x03, 0x01e5पूर्ण,			/*jfm: was 1e7*/
	अणु0xaa, 0x04, 0x0285पूर्ण,			/*jfm: was 0287*/
	अणु0xaa, 0x06, 0x0003पूर्ण,
	अणु0xaa, 0x07, 0x3002पूर्ण,
	अणु0xaa, 0x20, 0x1100पूर्ण,
	अणु0xaa, 0x2f, 0xf7b0पूर्ण,
	अणु0xaa, 0x30, 0x0005पूर्ण,
	अणु0xaa, 0x31, 0x0000पूर्ण,
	अणु0xaa, 0x34, 0x0100पूर्ण,
	अणु0xaa, 0x35, 0x0060पूर्ण,
	अणु0xaa, 0x3d, 0x068fपूर्ण,
	अणु0xaa, 0x40, 0x01e0पूर्ण,
	अणु0xaa, 0x58, 0x0078पूर्ण,
	अणु0xaa, 0x62, 0x0411पूर्ण,
	अणु0xa0, 0x10, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x09, 0x01adपूर्ण,			/*jfm: was 00 */
	अणु0xa0, 0x15, 0x01aeपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x78, ZC3XX_R18D_YTARGETपूर्ण,	/*jfm: was 6c*/
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pb0330_InitialScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,	/* 00 */
	अणु0xa0, 0x0a, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xdd, 0x00, 0x0200पूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xaa, 0x01, 0x0006पूर्ण,
	अणु0xaa, 0x02, 0x0011पूर्ण,
	अणु0xaa, 0x03, 0x01e7पूर्ण,
	अणु0xaa, 0x04, 0x0287पूर्ण,
	अणु0xaa, 0x06, 0x0003पूर्ण,
	अणु0xaa, 0x07, 0x3002पूर्ण,
	अणु0xaa, 0x20, 0x1100पूर्ण,
	अणु0xaa, 0x2f, 0xf7b0पूर्ण,
	अणु0xaa, 0x30, 0x0005पूर्ण,
	अणु0xaa, 0x31, 0x0000पूर्ण,
	अणु0xaa, 0x34, 0x0100पूर्ण,
	अणु0xaa, 0x35, 0x0060पूर्ण,
	अणु0xaa, 0x3d, 0x068fपूर्ण,
	अणु0xaa, 0x40, 0x01e0पूर्ण,
	अणु0xaa, 0x58, 0x0078पूर्ण,
	अणु0xaa, 0x62, 0x0411पूर्ण,
	अणु0xa0, 0x10, ZC3XX_R087_EXPTIMEMIDपूर्ण,
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x09, 0x01adपूर्ण,
	अणु0xa0, 0x15, 0x01aeपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x78, ZC3XX_R18D_YTARGETपूर्ण,	/*jfm: was 6c*/
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pb0330_50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x055cपूर्ण,
	अणु0xbb, 0x01, 0x09aaपूर्ण,
	अणु0xbb, 0x00, 0x1001पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xc4, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x47, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1a, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x5c, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pb0330_50HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0566पूर्ण,
	अणु0xbb, 0x02, 0x09b2पूर्ण,
	अणु0xbb, 0x00, 0x1002पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x8c, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x8a, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1a, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xd7, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0xf8, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pb0330_60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0535पूर्ण,
	अणु0xbb, 0x01, 0x0974पूर्ण,
	अणु0xbb, 0x00, 0x1001पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xfe, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x3e, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1a, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x35, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x50, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pb0330_60HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0535पूर्ण,
	अणु0xbb, 0x02, 0x096cपूर्ण,
	अणु0xbb, 0x00, 0x1002पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xc0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x7c, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x1a, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x14, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x66, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x35, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x50, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pb0330_NoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0509पूर्ण,
	अणु0xbb, 0x02, 0x0940पूर्ण,
	अणु0xbb, 0x00, 0x1002पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x09, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x40, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action pb0330_NoFlikerScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण,
	अणु0xbb, 0x00, 0x0535पूर्ण,
	अणु0xbb, 0x01, 0x0980पूर्ण,
	अणु0xbb, 0x00, 0x1001पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x10, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x20, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x35, ZC3XX_R01D_HSYNC_0पूर्ण,
	अणु0xa0, 0x60, ZC3XX_R01E_HSYNC_1पूर्ण,
	अणु0xa0, 0x90, ZC3XX_R01F_HSYNC_2पूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R020_HSYNC_3पूर्ण,
	अणुपूर्ण
पूर्ण;

/* from oem9.inf */
अटल स्थिर काष्ठा usb_action po2030_Initial[] = अणु	/* 640x480 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण, /* 00,00,01,cc */
	अणु0xa0, 0x04, ZC3XX_R002_CLOCKSELECTपूर्ण,	/* 00,02,04,cc */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण, /* 00,10,01,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण, /* 00,01,01,cc */
	अणु0xa0, 0x04, ZC3XX_R080_HBLANKHIGHपूर्ण, /* 00,80,04,cc */
	अणु0xa0, 0x05, ZC3XX_R081_HBLANKLOWपूर्ण, /* 00,81,05,cc */
	अणु0xa0, 0x16, ZC3XX_R083_RGAINADDRपूर्ण, /* 00,83,16,cc */
	अणु0xa0, 0x18, ZC3XX_R085_BGAINADDRपूर्ण, /* 00,85,18,cc */
	अणु0xa0, 0x1a, ZC3XX_R086_EXPTIMEHIGHपूर्ण, /* 00,86,1a,cc */
	अणु0xa0, 0x1b, ZC3XX_R087_EXPTIMEMIDपूर्ण, /* 00,87,1b,cc */
	अणु0xa0, 0x1c, ZC3XX_R088_EXPTIMELOWपूर्ण, /* 00,88,1c,cc */
	अणु0xa0, 0xee, ZC3XX_R08B_I2CDEVICEADDRपूर्ण, /* 00,8b,ee,cc */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण, /* 00,08,03,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,01,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण, /* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण, /* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण, /* 00,05,01,cc */
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण, /* 00,06,e0,cc */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण, /* 01,80,42,cc */
	अणु0xaa, 0x8d, 0x0008पूर्ण,			/* 00,8d,08,aa */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,	/* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,	/* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,	/* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,	/* 01,1c,00,cc */
	अणु0xa0, 0xe6, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,	/* 00,9c,e6,cc */
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण,	/* 00,9e,86,cc */
	अणु0xaa, 0x09, 0x00ceपूर्ण, /* 00,09,ce,aa */
	अणु0xaa, 0x0b, 0x0005पूर्ण, /* 00,0b,05,aa */
	अणु0xaa, 0x0d, 0x0054पूर्ण, /* 00,0d,54,aa */
	अणु0xaa, 0x0f, 0x00ebपूर्ण, /* 00,0f,eb,aa */
	अणु0xaa, 0x87, 0x0000पूर्ण, /* 00,87,00,aa */
	अणु0xaa, 0x88, 0x0004पूर्ण, /* 00,88,04,aa */
	अणु0xaa, 0x89, 0x0000पूर्ण, /* 00,89,00,aa */
	अणु0xaa, 0x8a, 0x0005पूर्ण, /* 00,8a,05,aa */
	अणु0xaa, 0x13, 0x0003पूर्ण, /* 00,13,03,aa */
	अणु0xaa, 0x16, 0x0040पूर्ण, /* 00,16,40,aa */
	अणु0xaa, 0x18, 0x0040पूर्ण, /* 00,18,40,aa */
	अणु0xaa, 0x1d, 0x0002पूर्ण, /* 00,1d,02,aa */
	अणु0xaa, 0x29, 0x00e8पूर्ण, /* 00,29,e8,aa */
	अणु0xaa, 0x45, 0x0045पूर्ण, /* 00,45,45,aa */
	अणु0xaa, 0x50, 0x00edपूर्ण, /* 00,50,ed,aa */
	अणु0xaa, 0x51, 0x0025पूर्ण, /* 00,51,25,aa */
	अणु0xaa, 0x52, 0x0042पूर्ण, /* 00,52,42,aa */
	अणु0xaa, 0x53, 0x002fपूर्ण, /* 00,53,2f,aa */
	अणु0xaa, 0x79, 0x0025पूर्ण, /* 00,79,25,aa */
	अणु0xaa, 0x7b, 0x0000पूर्ण, /* 00,7b,00,aa */
	अणु0xaa, 0x7e, 0x0025पूर्ण, /* 00,7e,25,aa */
	अणु0xaa, 0x7f, 0x0025पूर्ण, /* 00,7f,25,aa */
	अणु0xaa, 0x21, 0x0000पूर्ण, /* 00,21,00,aa */
	अणु0xaa, 0x33, 0x0036पूर्ण, /* 00,33,36,aa */
	अणु0xaa, 0x36, 0x0060पूर्ण, /* 00,36,60,aa */
	अणु0xaa, 0x37, 0x0008पूर्ण, /* 00,37,08,aa */
	अणु0xaa, 0x3b, 0x0031पूर्ण, /* 00,3b,31,aa */
	अणु0xaa, 0x44, 0x000fपूर्ण, /* 00,44,0f,aa */
	अणु0xaa, 0x58, 0x0002पूर्ण, /* 00,58,02,aa */
	अणु0xaa, 0x66, 0x00c0पूर्ण, /* 00,66,c0,aa */
	अणु0xaa, 0x67, 0x0044पूर्ण, /* 00,67,44,aa */
	अणु0xaa, 0x6b, 0x00a0पूर्ण, /* 00,6b,a0,aa */
	अणु0xaa, 0x6c, 0x0054पूर्ण, /* 00,6c,54,aa */
	अणु0xaa, 0xd6, 0x0007पूर्ण, /* 00,d6,07,aa */
	अणु0xa0, 0xf7, ZC3XX_R101_SENSORCORRECTIONपूर्ण, /* 01,01,f7,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,05,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण, /* 01,00,0d,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण, /* 01,89,06,cc */
	अणु0xa0, 0x00, 0x01adपूर्ण, /* 01,ad,00,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण, /* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण, /* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण, /* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण, /* 03,01,08,cc */
	अणु0xa0, 0x7a, ZC3XX_R116_RGAINपूर्ण, /* 01,16,7a,cc */
	अणु0xa0, 0x4a, ZC3XX_R118_BGAINपूर्ण, /* 01,18,4a,cc */
	अणुपूर्ण
पूर्ण;

/* from oem9.inf */
अटल स्थिर काष्ठा usb_action po2030_InitialScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण, /* 00,00,01,cc */
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण, /* 00,02,10,cc */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण, /* 00,10,01,cc */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण, /* 00,01,01,cc */
	अणु0xa0, 0x04, ZC3XX_R080_HBLANKHIGHपूर्ण, /* 00,80,04,cc */
	अणु0xa0, 0x05, ZC3XX_R081_HBLANKLOWपूर्ण, /* 00,81,05,cc */
	अणु0xa0, 0x16, ZC3XX_R083_RGAINADDRपूर्ण, /* 00,83,16,cc */
	अणु0xa0, 0x18, ZC3XX_R085_BGAINADDRपूर्ण, /* 00,85,18,cc */
	अणु0xa0, 0x1a, ZC3XX_R086_EXPTIMEHIGHपूर्ण, /* 00,86,1a,cc */
	अणु0xa0, 0x1b, ZC3XX_R087_EXPTIMEMIDपूर्ण, /* 00,87,1b,cc */
	अणु0xa0, 0x1c, ZC3XX_R088_EXPTIMELOWपूर्ण, /* 00,88,1c,cc */
	अणु0xa0, 0xee, ZC3XX_R08B_I2CDEVICEADDRपूर्ण, /* 00,8b,ee,cc */
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण, /* 00,08,03,cc */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,03,cc */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,01,cc */
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण, /* 00,03,02,cc */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण, /* 00,04,80,cc */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण, /* 00,05,01,cc */
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण, /* 00,06,e0,cc */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण, /* 01,80,42,cc */
	अणु0xaa, 0x8d, 0x0008पूर्ण,			/* 00,8d,08,aa */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण, /* 00,98,00,cc */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण, /* 00,9a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण, /* 01,1a,00,cc */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण, /* 01,1c,00,cc */
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण, /* 00,9c,e8,cc */
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण, /* 00,9e,88,cc */
	अणु0xaa, 0x09, 0x00ccपूर्ण, /* 00,09,cc,aa */
	अणु0xaa, 0x0b, 0x0005पूर्ण, /* 00,0b,05,aa */
	अणु0xaa, 0x0d, 0x0058पूर्ण, /* 00,0d,58,aa */
	अणु0xaa, 0x0f, 0x00edपूर्ण, /* 00,0f,ed,aa */
	अणु0xaa, 0x87, 0x0000पूर्ण, /* 00,87,00,aa */
	अणु0xaa, 0x88, 0x0004पूर्ण, /* 00,88,04,aa */
	अणु0xaa, 0x89, 0x0000पूर्ण, /* 00,89,00,aa */
	अणु0xaa, 0x8a, 0x0005पूर्ण, /* 00,8a,05,aa */
	अणु0xaa, 0x13, 0x0003पूर्ण, /* 00,13,03,aa */
	अणु0xaa, 0x16, 0x0040पूर्ण, /* 00,16,40,aa */
	अणु0xaa, 0x18, 0x0040पूर्ण, /* 00,18,40,aa */
	अणु0xaa, 0x1d, 0x0002पूर्ण, /* 00,1d,02,aa */
	अणु0xaa, 0x29, 0x00e8पूर्ण, /* 00,29,e8,aa */
	अणु0xaa, 0x45, 0x0045पूर्ण, /* 00,45,45,aa */
	अणु0xaa, 0x50, 0x00edपूर्ण, /* 00,50,ed,aa */
	अणु0xaa, 0x51, 0x0025पूर्ण, /* 00,51,25,aa */
	अणु0xaa, 0x52, 0x0042पूर्ण, /* 00,52,42,aa */
	अणु0xaa, 0x53, 0x002fपूर्ण, /* 00,53,2f,aa */
	अणु0xaa, 0x79, 0x0025पूर्ण, /* 00,79,25,aa */
	अणु0xaa, 0x7b, 0x0000पूर्ण, /* 00,7b,00,aa */
	अणु0xaa, 0x7e, 0x0025पूर्ण, /* 00,7e,25,aa */
	अणु0xaa, 0x7f, 0x0025पूर्ण, /* 00,7f,25,aa */
	अणु0xaa, 0x21, 0x0000पूर्ण, /* 00,21,00,aa */
	अणु0xaa, 0x33, 0x0036पूर्ण, /* 00,33,36,aa */
	अणु0xaa, 0x36, 0x0060पूर्ण, /* 00,36,60,aa */
	अणु0xaa, 0x37, 0x0008पूर्ण, /* 00,37,08,aa */
	अणु0xaa, 0x3b, 0x0031पूर्ण, /* 00,3b,31,aa */
	अणु0xaa, 0x44, 0x000fपूर्ण, /* 00,44,0f,aa */
	अणु0xaa, 0x58, 0x0002पूर्ण, /* 00,58,02,aa */
	अणु0xaa, 0x66, 0x00c0पूर्ण, /* 00,66,c0,aa */
	अणु0xaa, 0x67, 0x0044पूर्ण, /* 00,67,44,aa */
	अणु0xaa, 0x6b, 0x00a0पूर्ण, /* 00,6b,a0,aa */
	अणु0xaa, 0x6c, 0x0054पूर्ण, /* 00,6c,54,aa */
	अणु0xaa, 0xd6, 0x0007पूर्ण, /* 00,d6,07,aa */
	अणु0xa0, 0xf7, ZC3XX_R101_SENSORCORRECTIONपूर्ण, /* 01,01,f7,cc */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण, /* 00,12,05,cc */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण, /* 01,00,0d,cc */
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण, /* 01,89,06,cc */
	अणु0xa0, 0x00, 0x01adपूर्ण, /* 01,ad,00,cc */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण, /* 01,c5,03,cc */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण, /* 01,cb,13,cc */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण, /* 02,50,08,cc */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण, /* 03,01,08,cc */
	अणु0xa0, 0x7a, ZC3XX_R116_RGAINपूर्ण, /* 01,16,7a,cc */
	अणु0xa0, 0x4a, ZC3XX_R118_BGAINपूर्ण, /* 01,18,4a,cc */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action po2030_50HZ[] = अणु
	अणु0xaa, 0x8d, 0x0008पूर्ण, /* 00,8d,08,aa */
	अणु0xaa, 0x1a, 0x0001पूर्ण, /* 00,1a,01,aa */
	अणु0xaa, 0x1b, 0x000aपूर्ण, /* 00,1b,0a,aa */
	अणु0xaa, 0x1c, 0x00b0पूर्ण, /* 00,1c,b0,aa */
	अणु0xa0, 0x05, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,05,cc */
	अणु0xa0, 0x35, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,35,cc */
	अणु0xa0, 0x70, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,70,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x85, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,85,cc */
	अणु0xa0, 0x58, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,58,cc */
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,0c,cc */
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,18,cc */
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण, /* 01,a8,60,cc */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,10,cc */
	अणु0xa0, 0x22, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,22,cc */
	अणु0xa0, 0x88, ZC3XX_R18D_YTARGETपूर्ण, /* 01,8d,88,cc */
	अणु0xa0, 0x58, ZC3XX_R11D_GLOBALGAINपूर्ण, /* 01,1d,58,cc */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण, /* 01,80,42,cc */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action po2030_60HZ[] = अणु
	अणु0xaa, 0x8d, 0x0008पूर्ण, /* 00,8d,08,aa */
	अणु0xaa, 0x1a, 0x0000पूर्ण, /* 00,1a,00,aa */
	अणु0xaa, 0x1b, 0x00deपूर्ण, /* 00,1b,de,aa */
	अणु0xaa, 0x1c, 0x0040पूर्ण, /* 00,1c,40,aa */
	अणु0xa0, 0x08, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,08,cc */
	अणु0xa0, 0xae, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण, /* 01,91,ae,cc */
	अणु0xa0, 0x80, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण, /* 01,92,80,cc */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x6f, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,6f,cc */
	अणु0xa0, 0x20, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,20,cc */
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण, /* 01,8c,0c,cc */
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण, /* 01,8f,18,cc */
	अणु0xa0, 0x60, ZC3XX_R1A8_DIGITALGAINपूर्ण, /* 01,a8,60,cc */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,10,cc */
	अणु0xa0, 0x22, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,22,cc */
	अणु0xa0, 0x88, ZC3XX_R18D_YTARGETपूर्ण,		/* 01,8d,88,cc */
							/* win: 01,8d,80 */
	अणु0xa0, 0x58, ZC3XX_R11D_GLOBALGAINपूर्ण,		/* 01,1d,58,cc */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,42,cc */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action po2030_NoFliker[] = अणु
	अणु0xa0, 0x02, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण, /* 01,80,02,cc */
	अणु0xaa, 0x8d, 0x000dपूर्ण, /* 00,8d,0d,aa */
	अणु0xaa, 0x1a, 0x0000पूर्ण, /* 00,1a,00,aa */
	अणु0xaa, 0x1b, 0x0002पूर्ण, /* 00,1b,02,aa */
	अणु0xaa, 0x1c, 0x0078पूर्ण, /* 00,1c,78,aa */
	अणु0xaa, 0x46, 0x0000पूर्ण, /* 00,46,00,aa */
	अणु0xaa, 0x15, 0x0000पूर्ण, /* 00,15,00,aa */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action tas5130c_InitialScale[] = अणु	/* 320x240 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,

	अणु0xa0, 0x04, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण,
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R08D_COMPABILITYMODEपूर्ण,
	अणु0xa0, 0xf7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x70, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R0A5_EXPOSUREGAINपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R0A6_EXPOSUREBLACKLVLपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action tas5130c_Initial[] = अणु	/* 640x480 */
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,
	अणु0xa0, 0x40, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R008_CLOCKSETTINGपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R098_WINYSTARTLOWपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R09A_WINXSTARTLOWपूर्ण,
	अणु0xa0, 0x05, ZC3XX_R11A_FIRSTYLOWपूर्ण,
	अणु0xa0, 0x0f, ZC3XX_R11C_FIRSTXLOWपूर्ण,
	अणु0xa0, 0xe6, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R09D_WINWIDTHHIGHपूर्ण,
	अणु0xa0, 0x86, ZC3XX_R09E_WINWIDTHLOWपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R08D_COMPABILITYMODEपूर्ण,
	अणु0xa0, 0x37, ZC3XX_R101_SENSORCORRECTIONपूर्ण,
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,
	अणु0xa0, 0x06, ZC3XX_R189_AWBSTATUSपूर्ण,
	अणु0xa0, 0x70, ZC3XX_R18D_YTARGETपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x00, 0x01adपूर्ण,
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,
	अणु0xa0, 0x07, ZC3XX_R0A5_EXPOSUREGAINपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R0A6_EXPOSUREBLACKLVLपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action tas5130c_50HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0xa3, 0x0001पूर्ण, /* 00,a3,01,aa */
	अणु0xaa, 0xa4, 0x0063पूर्ण, /* 00,a4,63,aa */
	अणु0xa0, 0x01, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,01,cc */
	अणु0xa0, 0x63, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,63,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x04, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xfe, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x47, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,47,cc */
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xd3, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,d3,cc */
	अणु0xa0, 0xda, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,da,cc */
	अणु0xa0, 0xea, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,ea,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणु0xa0, 0x03, ZC3XX_R09F_MAXXHIGHपूर्ण, /* 00,9f,03,cc */
	अणु0xa0, 0x4c, ZC3XX_R0A0_MAXXLOWपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action tas5130c_50HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0xa3, 0x0001पूर्ण, /* 00,a3,01,aa */
	अणु0xaa, 0xa4, 0x0077पूर्ण, /* 00,a4,77,aa */
	अणु0xa0, 0x01, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,01,cc */
	अणु0xa0, 0x77, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,77,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x07, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xd0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x7d, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,7d,cc */
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xf0, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,f0,cc */
	अणु0xa0, 0xf4, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,f4,cc */
	अणु0xa0, 0xf8, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,f8,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणु0xa0, 0x03, ZC3XX_R09F_MAXXHIGHपूर्ण, /* 00,9f,03,cc */
	अणु0xa0, 0xc0, ZC3XX_R0A0_MAXXLOWपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action tas5130c_60HZ[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0xa3, 0x0001पूर्ण, /* 00,a3,01,aa */
	अणु0xaa, 0xa4, 0x0036पूर्ण, /* 00,a4,36,aa */
	अणु0xa0, 0x01, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,01,cc */
	अणु0xa0, 0x36, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,36,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x05, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x54, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x3e, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,3e,cc */
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xca, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,ca,cc */
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,d0,cc */
	अणु0xa0, 0xe0, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,e0,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणु0xa0, 0x03, ZC3XX_R09F_MAXXHIGHपूर्ण, /* 00,9f,03,cc */
	अणु0xa0, 0x28, ZC3XX_R0A0_MAXXLOWपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action tas5130c_60HZScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0xa3, 0x0001पूर्ण, /* 00,a3,01,aa */
	अणु0xaa, 0xa4, 0x0077पूर्ण, /* 00,a4,77,aa */
	अणु0xa0, 0x01, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,01,cc */
	अणु0xa0, 0x77, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,77,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x09, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x47, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण, /* 01,95,00,cc */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण, /* 01,96,00,cc */
	अणु0xa0, 0x7d, ZC3XX_R197_ANTIFLICKERLOWपूर्ण, /* 01,97,7d,cc */
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x08, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0xc8, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,c8,cc */
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,d0,cc */
	अणु0xa0, 0xe0, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,e0,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणु0xa0, 0x03, ZC3XX_R09F_MAXXHIGHपूर्ण, /* 00,9f,03,cc */
	अणु0xa0, 0x20, ZC3XX_R0A0_MAXXLOWपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action tas5130c_NoFliker[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0xa3, 0x0001पूर्ण, /* 00,a3,01,aa */
	अणु0xaa, 0xa4, 0x0040पूर्ण, /* 00,a4,40,aa */
	अणु0xa0, 0x01, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,01,cc */
	अणु0xa0, 0x40, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,40,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x05, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0xa0, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,00,cc */
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,00,cc */
	अणु0xa0, 0xbc, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,bc,cc */
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,d0,cc */
	अणु0xa0, 0xe0, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,e0,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणु0xa0, 0x02, ZC3XX_R09F_MAXXHIGHपूर्ण, /* 00,9f,02,cc */
	अणु0xa0, 0xf0, ZC3XX_R0A0_MAXXLOWपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action tas5130c_NoFlikerScale[] = अणु
	अणु0xa0, 0x00, ZC3XX_R019_AUTOADJUSTFPSपूर्ण, /* 00,19,00,cc */
	अणु0xaa, 0xa3, 0x0001पूर्ण, /* 00,a3,01,aa */
	अणु0xaa, 0xa4, 0x0090पूर्ण, /* 00,a4,90,aa */
	अणु0xa0, 0x01, ZC3XX_R0A3_EXPOSURETIMEHIGHपूर्ण, /* 00,a3,01,cc */
	अणु0xa0, 0x90, ZC3XX_R0A4_EXPOSURETIMELOWपूर्ण, /* 00,a4,90,cc */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण, /* 01,90,00,cc */
	अणु0xa0, 0x0a, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,
	अणु0xa0, 0x04, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,
	अणु0xa0, 0x0c, ZC3XX_R18C_AEFREEZEपूर्ण,
	अणु0xa0, 0x18, ZC3XX_R18F_AEUNFREEZEपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण, /* 01,a9,00,cc */
	अणु0xa0, 0x00, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण, /* 01,aa,00,cc */
	अणु0xa0, 0xbc, ZC3XX_R01D_HSYNC_0पूर्ण, /* 00,1d,bc,cc */
	अणु0xa0, 0xd0, ZC3XX_R01E_HSYNC_1पूर्ण, /* 00,1e,d0,cc */
	अणु0xa0, 0xe0, ZC3XX_R01F_HSYNC_2पूर्ण, /* 00,1f,e0,cc */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण, /* 00,20,ff,cc */
	अणु0xa0, 0x02, ZC3XX_R09F_MAXXHIGHपूर्ण, /* 00,9f,02,cc */
	अणु0xa0, 0xf0, ZC3XX_R0A0_MAXXLOWपूर्ण,
	अणु0xa0, 0x50, ZC3XX_R11D_GLOBALGAINपूर्ण,
	अणुपूर्ण
पूर्ण;

/* from usbvm305.inf 0ac8:305b 07/06/15 (3 - tas5130c) */
अटल स्थिर काष्ठा usb_action gc0303_Initial[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,		/* 00,00,01,cc, */
	अणु0xa0, 0x02, ZC3XX_R008_CLOCKSETTINGपूर्ण,		/* 00,08,02,cc, */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc, */
	अणु0xa0, 0x00, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,	/* 00,03,02,cc, */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,		/* 00,04,80,cc, */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,	/* 00,05,01,cc, */
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,	/* 00,06,e0,cc, */
	अणु0xa0, 0x98, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,		/* 00,8b,98,cc, */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,	/* 00,01,01,cc, */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,03,cc, */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,01,cc, */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,		/* 00,98,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,		/* 00,9a,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,		/* 01,1a,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,		/* 01,1c,00,cc, */
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,		/* 00,9c,e6,cc,
							 * 6<->8 */
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,		/* 00,9e,86,cc,
							 * 6<->8 */
	अणु0xa0, 0x10, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,10,cc, */
	अणु0xa0, 0x98, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,		/* 00,8b,98,cc, */
	अणु0xaa, 0x01, 0x0000पूर्ण,
	अणु0xaa, 0x1a, 0x0000पूर्ण,		/* 00,1a,00,aa, */
	अणु0xaa, 0x1c, 0x0017पूर्ण,		/* 00,1c,17,aa, */
	अणु0xaa, 0x1b, 0x0000पूर्ण,
	अणु0xa0, 0x82, ZC3XX_R086_EXPTIMEHIGHपूर्ण,		/* 00,86,82,cc, */
	अणु0xa0, 0x83, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,83,cc, */
	अणु0xa0, 0x84, ZC3XX_R088_EXPTIMELOWपूर्ण,		/* 00,88,84,cc, */
	अणु0xaa, 0x05, 0x0010पूर्ण,		/* 00,05,10,aa, */
	अणु0xaa, 0x0a, 0x0002पूर्ण,
	अणु0xaa, 0x0b, 0x0000पूर्ण,
	अणु0xaa, 0x0c, 0x0002पूर्ण,
	अणु0xaa, 0x0d, 0x0000पूर्ण,
	अणु0xaa, 0x0e, 0x0002पूर्ण,
	अणु0xaa, 0x0f, 0x0000पूर्ण,
	अणु0xaa, 0x10, 0x0002पूर्ण,
	अणु0xaa, 0x11, 0x0000पूर्ण,
	अणु0xaa, 0x16, 0x0001पूर्ण,		/* 00,16,01,aa, */
	अणु0xaa, 0x17, 0x00e8पूर्ण,		/* 00,17,e6,aa, (e6 -> e8) */
	अणु0xaa, 0x18, 0x0002पूर्ण,		/* 00,18,02,aa, */
	अणु0xaa, 0x19, 0x0088पूर्ण,		/* 00,19,86,aa, */
	अणु0xaa, 0x20, 0x0020पूर्ण,		/* 00,20,20,aa, */
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,	/* 01,01,b7,cc, */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,05,cc, */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,		/* 01,00,0d,cc, */
	अणु0xa0, 0x76, ZC3XX_R189_AWBSTATUSपूर्ण,		/* 01,89,76,cc, */
	अणु0xa0, 0x09, 0x01adपूर्ण,				/* 01,ad,09,cc, */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,		/* 01,c5,03,cc, */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,		/* 01,cb,13,cc, */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,	/* 02,50,08,cc, */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,		/* 03,01,08,cc, */
	अणु0xa0, 0x58, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x61, ZC3XX_R116_RGAINपूर्ण,			/* 01,16,61,cc, */
	अणु0xa0, 0x65, ZC3XX_R118_BGAINपूर्ण,			/* 01,18,65,cc */
	अणु0xaa, 0x1b, 0x0000पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action gc0303_InitialScale[] = अणु
	अणु0xa0, 0x01, ZC3XX_R000_SYSTEMCONTROLपूर्ण,		/* 00,00,01,cc, */
	अणु0xa0, 0x02, ZC3XX_R008_CLOCKSETTINGपूर्ण,		/* 00,08,02,cc, */
	अणु0xa0, 0x01, ZC3XX_R010_CMOSSENSORSELECTपूर्ण,	/* 00,10,01,cc, */
	अणु0xa0, 0x10, ZC3XX_R002_CLOCKSELECTपूर्ण,
	अणु0xa0, 0x02, ZC3XX_R003_FRAMEWIDTHHIGHपूर्ण,	/* 00,03,02,cc, */
	अणु0xa0, 0x80, ZC3XX_R004_FRAMEWIDTHLOWपूर्ण,		/* 00,04,80,cc, */
	अणु0xa0, 0x01, ZC3XX_R005_FRAMEHEIGHTHIGHपूर्ण,	/* 00,05,01,cc, */
	अणु0xa0, 0xe0, ZC3XX_R006_FRAMEHEIGHTLOWपूर्ण,	/* 00,06,e0,cc, */
	अणु0xa0, 0x98, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,		/* 00,8b,98,cc, */
	अणु0xa0, 0x01, ZC3XX_R001_SYSTEMOPERATINGपूर्ण,	/* 00,01,01,cc, */
	अणु0xa0, 0x03, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,03,cc, */
	अणु0xa0, 0x01, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,01,cc, */
	अणु0xa0, 0x00, ZC3XX_R098_WINYSTARTLOWपूर्ण,		/* 00,98,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R09A_WINXSTARTLOWपूर्ण,		/* 00,9a,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R11A_FIRSTYLOWपूर्ण,		/* 01,1a,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R11C_FIRSTXLOWपूर्ण,		/* 01,1c,00,cc, */
	अणु0xa0, 0xe8, ZC3XX_R09C_WINHEIGHTLOWपूर्ण,		/* 00,9c,e8,cc,
							 * 8<->6 */
	अणु0xa0, 0x88, ZC3XX_R09E_WINWIDTHLOWपूर्ण,		/* 00,9e,88,cc,
							 * 8<->6 */
	अणु0xa0, 0x10, ZC3XX_R087_EXPTIMEMIDपूर्ण,		/* 00,87,10,cc, */
	अणु0xa0, 0x98, ZC3XX_R08B_I2CDEVICEADDRपूर्ण,		/* 00,8b,98,cc, */
	अणु0xaa, 0x01, 0x0000पूर्ण,
	अणु0xaa, 0x1a, 0x0000पूर्ण,		/* 00,1a,00,aa, */
	अणु0xaa, 0x1c, 0x0017पूर्ण,		/* 00,1c,17,aa, */
	अणु0xaa, 0x1b, 0x0000पूर्ण,
	अणु0xa0, 0x82, ZC3XX_R086_EXPTIMEHIGHपूर्ण,	/* 00,86,82,cc, */
	अणु0xa0, 0x83, ZC3XX_R087_EXPTIMEMIDपूर्ण,	/* 00,87,83,cc, */
	अणु0xa0, 0x84, ZC3XX_R088_EXPTIMELOWपूर्ण,	/* 00,88,84,cc, */
	अणु0xaa, 0x05, 0x0010पूर्ण,		/* 00,05,10,aa, */
	अणु0xaa, 0x0a, 0x0001पूर्ण,
	अणु0xaa, 0x0b, 0x0000पूर्ण,
	अणु0xaa, 0x0c, 0x0001पूर्ण,
	अणु0xaa, 0x0d, 0x0000पूर्ण,
	अणु0xaa, 0x0e, 0x0001पूर्ण,
	अणु0xaa, 0x0f, 0x0000पूर्ण,
	अणु0xaa, 0x10, 0x0001पूर्ण,
	अणु0xaa, 0x11, 0x0000पूर्ण,
	अणु0xaa, 0x16, 0x0001पूर्ण,		/* 00,16,01,aa, */
	अणु0xaa, 0x17, 0x00e8पूर्ण,		/* 00,17,e6,aa (e6 -> e8) */
	अणु0xaa, 0x18, 0x0002पूर्ण,		/* 00,18,02,aa, */
	अणु0xaa, 0x19, 0x0088पूर्ण,		/* 00,19,88,aa, */
	अणु0xa0, 0xb7, ZC3XX_R101_SENSORCORRECTIONपूर्ण,	/* 01,01,b7,cc, */
	अणु0xa0, 0x05, ZC3XX_R012_VIDEOCONTROLFUNCपूर्ण,	/* 00,12,05,cc, */
	अणु0xa0, 0x0d, ZC3XX_R100_OPERATIONMODEपूर्ण,		/* 01,00,0d,cc, */
	अणु0xa0, 0x76, ZC3XX_R189_AWBSTATUSपूर्ण,		/* 01,89,76,cc, */
	अणु0xa0, 0x09, 0x01adपूर्ण,				/* 01,ad,09,cc, */
	अणु0xa0, 0x03, ZC3XX_R1C5_SHARPNESSMODEपूर्ण,		/* 01,c5,03,cc, */
	अणु0xa0, 0x13, ZC3XX_R1CB_SHARPNESS05पूर्ण,		/* 01,cb,13,cc, */
	अणु0xa0, 0x08, ZC3XX_R250_DEADPIXELSMODEपूर्ण,	/* 02,50,08,cc, */
	अणु0xa0, 0x08, ZC3XX_R301_EEPROMACCESSपूर्ण,		/* 03,01,08,cc, */
	अणु0xa0, 0x58, ZC3XX_R1A8_DIGITALGAINपूर्ण,
	अणु0xa0, 0x61, ZC3XX_R116_RGAINपूर्ण,		/* 01,16,61,cc, */
	अणु0xa0, 0x65, ZC3XX_R118_BGAINपूर्ण,		/* 01,18,65,cc */
	अणु0xaa, 0x1b, 0x0000पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल स्थिर काष्ठा usb_action gc0303_50HZ[] = अणु
	अणु0xaa, 0x82, 0x0000पूर्ण,		/* 00,82,00,aa */
	अणु0xaa, 0x83, 0x0001पूर्ण,		/* 00,83,01,aa */
	अणु0xaa, 0x84, 0x0063पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc, */
	अणु0xa0, 0x06, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,0d,cc, */
	अणु0xa0, 0xa8, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,50,cc, */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc, */
	अणु0xa0, 0x47, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,47,cc, */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,		/* 01,8c,0e,cc, */
	अणु0xa0, 0x15, ZC3XX_R18F_AEUNFREEZEपूर्ण,		/* 01,8f,15,cc, */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,10,cc, */
	अणु0xa0, 0x48, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,62,cc, */
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,90,cc, */
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,c8,cc, */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,ff,cc, */
	अणु0xa0, 0x58, ZC3XX_R11D_GLOBALGAINपूर्ण,		/* 01,1d,58,cc, */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,42,cc, */
	अणु0xa0, 0x7f, ZC3XX_R18D_YTARGETपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action gc0303_50HZScale[] = अणु
	अणु0xaa, 0x82, 0x0000पूर्ण,		/* 00,82,00,aa */
	अणु0xaa, 0x83, 0x0003पूर्ण,		/* 00,83,03,aa */
	अणु0xaa, 0x84, 0x0054पूर्ण,		/* 00,84,54,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc, */
	अणु0xa0, 0x0d, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,0d,cc, */
	अणु0xa0, 0x50, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,50,cc, */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc, */
	अणु0xa0, 0x8e, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,8e,cc, */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,		/* 01,8c,0e,cc, */
	अणु0xa0, 0x15, ZC3XX_R18F_AEUNFREEZEपूर्ण,		/* 01,8f,15,cc, */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,10,cc, */
	अणु0xa0, 0x48, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc, */
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,62,cc, */
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,90,cc, */
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,c8,cc, */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,ff,cc, */
	अणु0xa0, 0x58, ZC3XX_R11D_GLOBALGAINपूर्ण,		/* 01,1d,58,cc, */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,42,cc, */
	अणु0xa0, 0x7f, ZC3XX_R18D_YTARGETपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action gc0303_60HZ[] = अणु
	अणु0xaa, 0x82, 0x0000पूर्ण,		/* 00,82,00,aa */
	अणु0xaa, 0x83, 0x0000पूर्ण,
	अणु0xaa, 0x84, 0x003bपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc, */
	अणु0xa0, 0x05, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,91,05,cc, */
	अणु0xa0, 0x88, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,92,88,cc, */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc, */
	अणु0xa0, 0x3b, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,3b,cc, */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,		/* 01,8c,0e,cc, */
	अणु0xa0, 0x15, ZC3XX_R18F_AEUNFREEZEपूर्ण,		/* 01,8f,15,cc, */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,a9,10,cc, */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,aa,24,cc, */
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,62,cc, */
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,90,cc, */
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,c8,cc, */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,ff,cc, */
	अणु0xa0, 0x58, ZC3XX_R11D_GLOBALGAINपूर्ण,		/* 01,1d,58,cc, */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,42,cc, */
	अणु0xa0, 0x80, ZC3XX_R18D_YTARGETपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action gc0303_60HZScale[] = अणु
	अणु0xaa, 0x82, 0x0000पूर्ण,		/* 00,82,00,aa */
	अणु0xaa, 0x83, 0x0000पूर्ण,
	अणु0xaa, 0x84, 0x0076पूर्ण,
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc, */
	अणु0xa0, 0x0b, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,	/* 01,1,0b,cc, */
	अणु0xa0, 0x10, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,	/* 01,2,10,cc, */
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,5,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,6,00,cc, */
	अणु0xa0, 0x76, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,7,76,cc, */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,		/* 01,c,0e,cc, */
	अणु0xa0, 0x15, ZC3XX_R18F_AEUNFREEZEपूर्ण,		/* 01,f,15,cc, */
	अणु0xa0, 0x10, ZC3XX_R1A9_DIGITALLIMITDIFFपूर्ण,	/* 01,9,10,cc, */
	अणु0xa0, 0x24, ZC3XX_R1AA_DIGITALGAINSTEPपूर्ण,	/* 01,a,24,cc, */
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,d,62,cc, */
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,e,90,cc, */
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,f,c8,cc, */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,0,ff,cc, */
	अणु0xa0, 0x58, ZC3XX_R11D_GLOBALGAINपूर्ण,		/* 01,d,58,cc, */
	अणु0xa0, 0x42, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,42,cc, */
	अणु0xa0, 0x80, ZC3XX_R18D_YTARGETपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action gc0303_NoFliker[] = अणु
	अणु0xa0, 0x0c, ZC3XX_R100_OPERATIONMODEपूर्ण,		/* 01,00,0c,cc, */
	अणु0xaa, 0x82, 0x0000पूर्ण,		/* 00,82,00,aa */
	अणु0xaa, 0x83, 0x0000पूर्ण,		/* 00,83,00,aa */
	अणु0xaa, 0x84, 0x0020पूर्ण,		/* 00,84,20,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,0,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x48, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc, */
	अणु0xa0, 0x10, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,10,cc, */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,		/* 01,8c,0e,cc, */
	अणु0xa0, 0x15, ZC3XX_R18F_AEUNFREEZEपूर्ण,		/* 01,8f,15,cc, */
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,62,cc, */
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,90,cc, */
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,c8,cc, */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,ff,cc, */
	अणु0xa0, 0x58, ZC3XX_R11D_GLOBALGAINपूर्ण,		/* 01,1d,58,cc, */
	अणु0xa0, 0x03, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,03,cc */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_action gc0303_NoFlikerScale[] = अणु
	अणु0xa0, 0x0c, ZC3XX_R100_OPERATIONMODEपूर्ण,		/* 01,00,0c,cc, */
	अणु0xaa, 0x82, 0x0000पूर्ण,		/* 00,82,00,aa */
	अणु0xaa, 0x83, 0x0000पूर्ण,		/* 00,83,00,aa */
	अणु0xaa, 0x84, 0x0020पूर्ण,		/* 00,84,20,aa */
	अणु0xa0, 0x00, ZC3XX_R190_EXPOSURELIMITHIGHपूर्ण,	/* 01,90,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R191_EXPOSURELIMITMIDपूर्ण,
	अणु0xa0, 0x48, ZC3XX_R192_EXPOSURELIMITLOWपूर्ण,
	अणु0xa0, 0x00, ZC3XX_R195_ANTIFLICKERHIGHपूर्ण,	/* 01,95,00,cc, */
	अणु0xa0, 0x00, ZC3XX_R196_ANTIFLICKERMIDपूर्ण,	/* 01,96,00,cc, */
	अणु0xa0, 0x10, ZC3XX_R197_ANTIFLICKERLOWपूर्ण,	/* 01,97,10,cc, */
	अणु0xa0, 0x0e, ZC3XX_R18C_AEFREEZEपूर्ण,		/* 01,8c,0e,cc, */
	अणु0xa0, 0x15, ZC3XX_R18F_AEUNFREEZEपूर्ण,		/* 01,8f,15,cc, */
	अणु0xa0, 0x62, ZC3XX_R01D_HSYNC_0पूर्ण,		/* 00,1d,62,cc, */
	अणु0xa0, 0x90, ZC3XX_R01E_HSYNC_1पूर्ण,		/* 00,1e,90,cc, */
	अणु0xa0, 0xc8, ZC3XX_R01F_HSYNC_2पूर्ण,		/* 00,1f,c8,cc, */
	अणु0xa0, 0xff, ZC3XX_R020_HSYNC_3पूर्ण,		/* 00,20,ff,cc, */
	अणु0xa0, 0x58, ZC3XX_R11D_GLOBALGAINपूर्ण,		/* 01,1d,58,cc, */
	अणु0xa0, 0x03, ZC3XX_R180_AUTOCORRECTENABLEपूर्ण,	/* 01,80,03,cc */
	अणुपूर्ण
पूर्ण;

अटल u8 reg_r(काष्ठा gspca_dev *gspca_dev,
		u16 index)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस 0;
	ret = usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			0xa1,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x01,			/* value */
			index, gspca_dev->usb_buf, 1,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_r err %d\n", ret);
		gspca_dev->usb_err = ret;
		वापस 0;
	पूर्ण
	वापस gspca_dev->usb_buf[0];
पूर्ण

अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev,
			u8 value,
			u16 index)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0xa0,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, शून्य, 0,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_w_i err %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल u16 i2c_पढ़ो(काष्ठा gspca_dev *gspca_dev,
			u8 reg)
अणु
	u8 retbyte;
	u16 retval;

	अगर (gspca_dev->usb_err < 0)
		वापस 0;
	reg_w(gspca_dev, reg, 0x0092);
	reg_w(gspca_dev, 0x02, 0x0090);			/* <- पढ़ो command */
	msleep(20);
	retbyte = reg_r(gspca_dev, 0x0091);		/* पढ़ो status */
	अगर (retbyte != 0x00)
		pr_err("i2c_r status error %02x\n", retbyte);
	retval = reg_r(gspca_dev, 0x0095);		/* पढ़ो Lowbyte */
	retval |= reg_r(gspca_dev, 0x0096) << 8;	/* पढ़ो Hightbyte */
	वापस retval;
पूर्ण

अटल u8 i2c_ग_लिखो(काष्ठा gspca_dev *gspca_dev,
			u8 reg,
			u8 valL,
			u8 valH)
अणु
	u8 retbyte;

	अगर (gspca_dev->usb_err < 0)
		वापस 0;
	reg_w(gspca_dev, reg, 0x92);
	reg_w(gspca_dev, valL, 0x93);
	reg_w(gspca_dev, valH, 0x94);
	reg_w(gspca_dev, 0x01, 0x90);		/* <- ग_लिखो command */
	msleep(1);
	retbyte = reg_r(gspca_dev, 0x0091);		/* पढ़ो status */
	अगर (retbyte != 0x00)
		pr_err("i2c_w status error %02x\n", retbyte);
	वापस retbyte;
पूर्ण

अटल व्योम usb_exchange(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_action *action)
अणु
	जबतक (action->req) अणु
		चयन (action->req) अणु
		हाल 0xa0:	/* ग_लिखो रेजिस्टर */
			reg_w(gspca_dev, action->val, action->idx);
			अवरोध;
		हाल 0xa1:	/* पढ़ो status */
			reg_r(gspca_dev, action->idx);
			अवरोध;
		हाल 0xaa:
			i2c_ग_लिखो(gspca_dev,
				  action->val,			/* reg */
				  action->idx & 0xff,		/* valL */
				  action->idx >> 8);		/* valH */
			अवरोध;
		हाल 0xbb:
			i2c_ग_लिखो(gspca_dev,
				  action->idx >> 8,		/* reg */
				  action->idx & 0xff,		/* valL */
				  action->val);			/* valH */
			अवरोध;
		शेष:
/*		हाल 0xdd:	 * delay */
			msleep(action->idx);
			अवरोध;
		पूर्ण
		action++;
		msleep(1);
	पूर्ण
पूर्ण

अटल व्योम seपंचांगatrix(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i;
	स्थिर u8 *matrix;
	अटल स्थिर u8 adcm2700_matrix[9] =
/*		अणु0x66, 0xed, 0xed, 0xed, 0x66, 0xed, 0xed, 0xed, 0x66पूर्ण; */
/*ms-win*/
		अणु0x74, 0xed, 0xed, 0xed, 0x74, 0xed, 0xed, 0xed, 0x74पूर्ण;
	अटल स्थिर u8 gc0305_matrix[9] =
		अणु0x50, 0xf8, 0xf8, 0xf8, 0x50, 0xf8, 0xf8, 0xf8, 0x50पूर्ण;
	अटल स्थिर u8 ov7620_matrix[9] =
		अणु0x58, 0xf4, 0xf4, 0xf4, 0x58, 0xf4, 0xf4, 0xf4, 0x58पूर्ण;
	अटल स्थिर u8 pas202b_matrix[9] =
		अणु0x4c, 0xf5, 0xff, 0xf9, 0x51, 0xf5, 0xfb, 0xed, 0x5fपूर्ण;
	अटल स्थिर u8 po2030_matrix[9] =
		अणु0x60, 0xf0, 0xf0, 0xf0, 0x60, 0xf0, 0xf0, 0xf0, 0x60पूर्ण;
	अटल स्थिर u8 tas5130c_matrix[9] =
		अणु0x68, 0xec, 0xec, 0xec, 0x68, 0xec, 0xec, 0xec, 0x68पूर्ण;
	अटल स्थिर u8 gc0303_matrix[9] =
		अणु0x6c, 0xea, 0xea, 0xea, 0x6c, 0xea, 0xea, 0xea, 0x6cपूर्ण;
	अटल स्थिर u8 *matrix_tb[SENSOR_MAX] = अणु
		[SENSOR_ADCM2700] =	adcm2700_matrix,
		[SENSOR_CS2102] =	ov7620_matrix,
		[SENSOR_CS2102K] =	शून्य,
		[SENSOR_GC0303] =	gc0303_matrix,
		[SENSOR_GC0305] =	gc0305_matrix,
		[SENSOR_HDCS2020] =	शून्य,
		[SENSOR_HV7131B] =	शून्य,
		[SENSOR_HV7131R] =	po2030_matrix,
		[SENSOR_ICM105A] =	po2030_matrix,
		[SENSOR_MC501CB] =	शून्य,
		[SENSOR_MT9V111_1] =	gc0305_matrix,
		[SENSOR_MT9V111_3] =	gc0305_matrix,
		[SENSOR_OV7620] =	ov7620_matrix,
		[SENSOR_OV7630C] =	शून्य,
		[SENSOR_PAS106] =	शून्य,
		[SENSOR_PAS202B] =	pas202b_matrix,
		[SENSOR_PB0330] =	gc0305_matrix,
		[SENSOR_PO2030] =	po2030_matrix,
		[SENSOR_TAS5130C] =	tas5130c_matrix,
	पूर्ण;

	matrix = matrix_tb[sd->sensor];
	अगर (matrix == शून्य)
		वापस;		/* matrix alपढ़ोy loaded */
	क्रम (i = 0; i < ARRAY_SIZE(ov7620_matrix); i++)
		reg_w(gspca_dev, matrix[i], 0x010a + i);
पूर्ण

अटल व्योम setsharpness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	अटल स्थिर u8 sharpness_tb[][2] = अणु
		अणु0x02, 0x03पूर्ण,
		अणु0x04, 0x07पूर्ण,
		अणु0x08, 0x0fपूर्ण,
		अणु0x10, 0x1eपूर्ण
	पूर्ण;

	reg_w(gspca_dev, sharpness_tb[val][0], 0x01c6);
	reg_r(gspca_dev, 0x01c8);
	reg_r(gspca_dev, 0x01c9);
	reg_r(gspca_dev, 0x01ca);
	reg_w(gspca_dev, sharpness_tb[val][1], 0x01cb);
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev,
		s32 gamma, s32 brightness, s32 contrast)
अणु
	स्थिर u8 *Tgamma;
	पूर्णांक g, i, adj, gp1, gp2;
	u8 gr[16];
	अटल स्थिर u8 delta_b[16] =		/* delta क्रम brightness */
		अणु0x50, 0x38, 0x2d, 0x28, 0x24, 0x21, 0x1e, 0x1d,
		 0x1d, 0x1b, 0x1b, 0x1b, 0x19, 0x18, 0x18, 0x18पूर्ण;
	अटल स्थिर u8 delta_c[16] =		/* delta क्रम contrast */
		अणु0x2c, 0x1a, 0x12, 0x0c, 0x0a, 0x06, 0x06, 0x06,
		 0x04, 0x06, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02पूर्ण;
	अटल स्थिर u8 gamma_tb[6][16] = अणु
		अणु0x00, 0x00, 0x03, 0x0d, 0x1b, 0x2e, 0x45, 0x5f,
		 0x79, 0x93, 0xab, 0xc1, 0xd4, 0xe5, 0xf3, 0xffपूर्ण,
		अणु0x01, 0x0c, 0x1f, 0x3a, 0x53, 0x6d, 0x85, 0x9c,
		 0xb0, 0xc2, 0xd1, 0xde, 0xe9, 0xf2, 0xf9, 0xffपूर्ण,
		अणु0x04, 0x16, 0x30, 0x4e, 0x68, 0x81, 0x98, 0xac,
		 0xbe, 0xcd, 0xda, 0xe4, 0xed, 0xf5, 0xfb, 0xffपूर्ण,
		अणु0x13, 0x38, 0x59, 0x79, 0x92, 0xa7, 0xb9, 0xc8,
		 0xd4, 0xdf, 0xe7, 0xee, 0xf4, 0xf9, 0xfc, 0xffपूर्ण,
		अणु0x20, 0x4b, 0x6e, 0x8d, 0xa3, 0xb5, 0xc5, 0xd2,
		 0xdc, 0xe5, 0xec, 0xf2, 0xf6, 0xfa, 0xfd, 0xffपूर्ण,
		अणु0x24, 0x44, 0x64, 0x84, 0x9d, 0xb2, 0xc4, 0xd3,
		 0xe0, 0xeb, 0xf4, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण,
	पूर्ण;

	Tgamma = gamma_tb[gamma - 1];

	contrast -= 128; /* -128 / 127 */
	brightness -= 128; /* -128 / 92 */
	adj = 0;
	gp1 = gp2 = 0;
	क्रम (i = 0; i < 16; i++) अणु
		g = Tgamma[i] + delta_b[i] * brightness / 256
				- delta_c[i] * contrast / 256 - adj / 2;
		अगर (g > 0xff)
			g = 0xff;
		अन्यथा अगर (g < 0)
			g = 0;
		reg_w(gspca_dev, g, 0x0120 + i);	/* gamma */
		अगर (contrast > 0)
			adj--;
		अन्यथा अगर (contrast < 0)
			adj++;
		अगर (i > 1)
			gr[i - 1] = (g - gp2) / 2;
		अन्यथा अगर (i != 0)
			gr[0] = gp1 == 0 ? 0 : (g - gp1);
		gp2 = gp1;
		gp1 = g;
	पूर्ण
	gr[15] = (0xff - gp2) / 2;
	क्रम (i = 0; i < 16; i++)
		reg_w(gspca_dev, gr[i], 0x0130 + i);	/* gradient */
पूर्ण

अटल s32 getexposure(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->sensor) अणु
	हाल SENSOR_HV7131R:
		वापस (i2c_पढ़ो(gspca_dev, 0x25) << 9)
			| (i2c_पढ़ो(gspca_dev, 0x26) << 1)
			| (i2c_पढ़ो(gspca_dev, 0x27) >> 7);
	हाल SENSOR_OV7620:
		वापस i2c_पढ़ो(gspca_dev, 0x10);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->sensor) अणु
	हाल SENSOR_HV7131R:
		i2c_ग_लिखो(gspca_dev, 0x25, val >> 9, 0x00);
		i2c_ग_लिखो(gspca_dev, 0x26, val >> 1, 0x00);
		i2c_ग_लिखो(gspca_dev, 0x27, val << 7, 0x00);
		अवरोध;
	हाल SENSOR_OV7620:
		i2c_ग_लिखो(gspca_dev, 0x10, val, 0x00);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम setquality(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	jpeg_set_qual(sd->jpeg_hdr, jpeg_qual[sd->reg08 >> 1]);
	reg_w(gspca_dev, sd->reg08, ZC3XX_R008_CLOCKSETTING);
पूर्ण

/* Matches the sensor's पूर्णांकernal frame rate to the lighting frequency.
 * Valid frequencies are:
 *	50Hz, क्रम European and Asian lighting (शेष)
 *	60Hz, क्रम American lighting
 *	0 = No Fliker (क्रम outकरोore usage)
 */
अटल व्योम setlightfreq(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i, mode;
	स्थिर काष्ठा usb_action *zc3_freq;
	अटल स्थिर काष्ठा usb_action *freq_tb[SENSOR_MAX][6] = अणु
	[SENSOR_ADCM2700] =
		अणुadcm2700_NoFliker, adcm2700_NoFliker,
		 adcm2700_50HZ, adcm2700_50HZ,
		 adcm2700_60HZ, adcm2700_60HZपूर्ण,
	[SENSOR_CS2102] =
		अणुcs2102_NoFliker, cs2102_NoFlikerScale,
		 cs2102_50HZ, cs2102_50HZScale,
		 cs2102_60HZ, cs2102_60HZScaleपूर्ण,
	[SENSOR_CS2102K] =
		अणुcs2102_NoFliker, cs2102_NoFlikerScale,
		 शून्य, शून्य, /* currently disabled */
		 शून्य, शून्यपूर्ण,
	[SENSOR_GC0303] =
		अणुgc0303_NoFliker, gc0303_NoFlikerScale,
		 gc0303_50HZ, gc0303_50HZScale,
		 gc0303_60HZ, gc0303_60HZScaleपूर्ण,
	[SENSOR_GC0305] =
		अणुgc0305_NoFliker, gc0305_NoFliker,
		 gc0305_50HZ, gc0305_50HZ,
		 gc0305_60HZ, gc0305_60HZपूर्ण,
	[SENSOR_HDCS2020] =
		अणुhdcs2020_NoFliker, hdcs2020_NoFliker,
		 hdcs2020_50HZ, hdcs2020_50HZ,
		 hdcs2020_60HZ, hdcs2020_60HZपूर्ण,
	[SENSOR_HV7131B] =
		अणुhv7131b_NoFliker, hv7131b_NoFlikerScale,
		 hv7131b_50HZ, hv7131b_50HZScale,
		 hv7131b_60HZ, hv7131b_60HZScaleपूर्ण,
	[SENSOR_HV7131R] =
		अणुhv7131r_NoFliker, hv7131r_NoFlikerScale,
		 hv7131r_50HZ, hv7131r_50HZScale,
		 hv7131r_60HZ, hv7131r_60HZScaleपूर्ण,
	[SENSOR_ICM105A] =
		अणुicm105a_NoFliker, icm105a_NoFlikerScale,
		 icm105a_50HZ, icm105a_50HZScale,
		 icm105a_60HZ, icm105a_60HZScaleपूर्ण,
	[SENSOR_MC501CB] =
		अणुmc501cb_NoFliker, mc501cb_NoFlikerScale,
		 mc501cb_50HZ, mc501cb_50HZScale,
		 mc501cb_60HZ, mc501cb_60HZScaleपूर्ण,
	[SENSOR_MT9V111_1] =
		अणुmt9v111_1_AENoFliker, mt9v111_1_AENoFlikerScale,
		 mt9v111_1_AE50HZ, mt9v111_1_AE50HZScale,
		 mt9v111_1_AE60HZ, mt9v111_1_AE60HZScaleपूर्ण,
	[SENSOR_MT9V111_3] =
		अणुmt9v111_3_AENoFliker, mt9v111_3_AENoFlikerScale,
		 mt9v111_3_AE50HZ, mt9v111_3_AE50HZScale,
		 mt9v111_3_AE60HZ, mt9v111_3_AE60HZScaleपूर्ण,
	[SENSOR_OV7620] =
		अणुov7620_NoFliker, ov7620_NoFliker,
		 ov7620_50HZ, ov7620_50HZ,
		 ov7620_60HZ, ov7620_60HZपूर्ण,
	[SENSOR_OV7630C] =
		अणुशून्य, शून्य,
		 शून्य, शून्य,
		 शून्य, शून्यपूर्ण,
	[SENSOR_PAS106] =
		अणुpas106b_NoFliker, pas106b_NoFliker,
		 pas106b_50HZ, pas106b_50HZ,
		 pas106b_60HZ, pas106b_60HZपूर्ण,
	[SENSOR_PAS202B] =
		अणुpas202b_NoFliker, pas202b_NoFlikerScale,
		 pas202b_50HZ, pas202b_50HZScale,
		 pas202b_60HZ, pas202b_60HZScaleपूर्ण,
	[SENSOR_PB0330] =
		अणुpb0330_NoFliker, pb0330_NoFlikerScale,
		 pb0330_50HZ, pb0330_50HZScale,
		 pb0330_60HZ, pb0330_60HZScaleपूर्ण,
	[SENSOR_PO2030] =
		अणुpo2030_NoFliker, po2030_NoFliker,
		 po2030_50HZ, po2030_50HZ,
		 po2030_60HZ, po2030_60HZपूर्ण,
	[SENSOR_TAS5130C] =
		अणुtas5130c_NoFliker, tas5130c_NoFlikerScale,
		 tas5130c_50HZ, tas5130c_50HZScale,
		 tas5130c_60HZ, tas5130c_60HZScaleपूर्ण,
	पूर्ण;

	i = val * 2;
	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	अगर (mode)
		i++;			/* 320x240 */
	zc3_freq = freq_tb[sd->sensor][i];
	अगर (zc3_freq == शून्य)
		वापस;
	usb_exchange(gspca_dev, zc3_freq);
	चयन (sd->sensor) अणु
	हाल SENSOR_GC0305:
		अगर (mode		/* अगर 320x240 */
		    && val == 1)	/* and 50Hz */
			reg_w(gspca_dev, 0x85, 0x018d);
					/* win: 0x80, 0x018d */
		अवरोध;
	हाल SENSOR_OV7620:
		अगर (!mode) अणु		/* अगर 640x480 */
			अगर (val != 0)	/* and filter */
				reg_w(gspca_dev, 0x40, 0x0002);
			अन्यथा
				reg_w(gspca_dev, 0x44, 0x0002);
		पूर्ण
		अवरोध;
	हाल SENSOR_PAS202B:
		reg_w(gspca_dev, 0x00, 0x01a7);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम setस्वतःgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_OV7620)
		i2c_ग_लिखो(gspca_dev, 0x13, val ? 0xa3 : 0x80, 0x00);
	अन्यथा
		reg_w(gspca_dev, val ? 0x42 : 0x02, 0x0180);
पूर्ण

/*
 * Update the transfer parameters.
 * This function is executed from a work queue.
 */
अटल व्योम transfer_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sd *sd = container_of(work, काष्ठा sd, work);
	काष्ठा gspca_dev *gspca_dev = &sd->gspca_dev;
	पूर्णांक change, good;
	u8 reg07, reg11;

	/* reg07 माला_लो set to 0 by sd_start beक्रमe starting us */
	reg07 = 0;

	good = 0;
	जबतक (1) अणु
		msleep(100);

		/* To protect gspca_dev->usb_buf and gspca_dev->usb_err */
		mutex_lock(&gspca_dev->usb_lock);
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			अवरोध;
#पूर्ण_अगर
		अगर (!gspca_dev->present || !gspca_dev->streaming)
			अवरोध;

		/* Bit 0 of रेजिस्टर 11 indicates FIFO overflow */
		gspca_dev->usb_err = 0;
		reg11 = reg_r(gspca_dev, 0x0011);
		अगर (gspca_dev->usb_err)
			अवरोध;

		change = reg11 & 0x01;
		अगर (change) अणु				/* overflow */
			good = 0;

			अगर (reg07 == 0) /* Bit Rate Control not enabled? */
				reg07 = 0x32; /* Allow 98 bytes / unit */
			अन्यथा अगर (reg07 > 2)
				reg07 -= 2; /* Decrease allowed bytes / unit */
			अन्यथा
				change = 0;
		पूर्ण अन्यथा अणु				/* no overflow */
			good++;
			अगर (good >= 10) अणु
				good = 0;
				अगर (reg07) अणु /* BRC enabled? */
					change = 1;
					अगर (reg07 < 0x32)
						reg07 += 2;
					अन्यथा
						reg07 = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (change) अणु
			gspca_dev->usb_err = 0;
			reg_w(gspca_dev, reg07, 0x0007);
			अगर (gspca_dev->usb_err)
				अवरोध;
		पूर्ण
		mutex_unlock(&gspca_dev->usb_lock);
	पूर्ण

	/* Something went wrong. Unlock and वापस */
	mutex_unlock(&gspca_dev->usb_lock);
पूर्ण

अटल व्योम send_unknown(काष्ठा gspca_dev *gspca_dev, पूर्णांक sensor)
अणु
	reg_w(gspca_dev, 0x01, 0x0000);		/* bridge reset */
	चयन (sensor) अणु
	हाल SENSOR_PAS106:
		reg_w(gspca_dev, 0x03, 0x003a);
		reg_w(gspca_dev, 0x0c, 0x003b);
		reg_w(gspca_dev, 0x08, 0x0038);
		अवरोध;
	हाल SENSOR_ADCM2700:
	हाल SENSOR_GC0305:
	हाल SENSOR_OV7620:
	हाल SENSOR_MT9V111_1:
	हाल SENSOR_MT9V111_3:
	हाल SENSOR_PB0330:
	हाल SENSOR_PO2030:
		reg_w(gspca_dev, 0x0d, 0x003a);
		reg_w(gspca_dev, 0x02, 0x003b);
		reg_w(gspca_dev, 0x00, 0x0038);
		अवरोध;
	हाल SENSOR_HV7131R:
	हाल SENSOR_PAS202B:
		reg_w(gspca_dev, 0x03, 0x003b);
		reg_w(gspca_dev, 0x0c, 0x003a);
		reg_w(gspca_dev, 0x0b, 0x0039);
		अगर (sensor == SENSOR_PAS202B)
			reg_w(gspca_dev, 0x0b, 0x0038);
		अवरोध;
	पूर्ण
पूर्ण

/* start probe 2 wires */
अटल व्योम start_2wr_probe(काष्ठा gspca_dev *gspca_dev, पूर्णांक sensor)
अणु
	reg_w(gspca_dev, 0x01, 0x0000);
	reg_w(gspca_dev, sensor, 0x0010);
	reg_w(gspca_dev, 0x01, 0x0001);
	reg_w(gspca_dev, 0x03, 0x0012);
	reg_w(gspca_dev, 0x01, 0x0012);
/*	msleep(2); */
पूर्ण

अटल पूर्णांक sअगर_probe(काष्ठा gspca_dev *gspca_dev)
अणु
	u16 checkword;

	start_2wr_probe(gspca_dev, 0x0f);		/* PAS106 */
	reg_w(gspca_dev, 0x08, 0x008d);
	msleep(150);
	checkword = ((i2c_पढ़ो(gspca_dev, 0x00) & 0x0f) << 4)
			| ((i2c_पढ़ो(gspca_dev, 0x01) & 0xf0) >> 4);
	gspca_dbg(gspca_dev, D_PROBE, "probe sif 0x%04x\n", checkword);
	अगर (checkword == 0x0007) अणु
		send_unknown(gspca_dev, SENSOR_PAS106);
		वापस 0x0f;			/* PAS106 */
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक vga_2wr_probe(काष्ठा gspca_dev *gspca_dev)
अणु
	u16 retword;

	start_2wr_probe(gspca_dev, 0x00);	/* HV7131B */
	i2c_ग_लिखो(gspca_dev, 0x01, 0xaa, 0x00);
	retword = i2c_पढ़ो(gspca_dev, 0x01);
	अगर (retword != 0)
		वापस 0x00;			/* HV7131B */

	start_2wr_probe(gspca_dev, 0x04);	/* CS2102 */
	i2c_ग_लिखो(gspca_dev, 0x01, 0xaa, 0x00);
	retword = i2c_पढ़ो(gspca_dev, 0x01);
	अगर (retword != 0)
		वापस 0x04;			/* CS2102 */

	start_2wr_probe(gspca_dev, 0x06);	/* OmniVision */
	reg_w(gspca_dev, 0x08, 0x008d);
	i2c_ग_लिखो(gspca_dev, 0x11, 0xaa, 0x00);
	retword = i2c_पढ़ो(gspca_dev, 0x11);
	अगर (retword != 0) अणु
		/* (should have वापसed 0xaa) --> Omnivision? */
		/* reg_r 0x10 -> 0x06 -->  */
		जाओ ov_check;
	पूर्ण

	start_2wr_probe(gspca_dev, 0x08);	/* HDCS2020 */
	i2c_ग_लिखो(gspca_dev, 0x1c, 0x00, 0x00);
	i2c_ग_लिखो(gspca_dev, 0x15, 0xaa, 0x00);
	retword = i2c_पढ़ो(gspca_dev, 0x15);
	अगर (retword != 0)
		वापस 0x08;			/* HDCS2020 */

	start_2wr_probe(gspca_dev, 0x0a);	/* PB0330 */
	i2c_ग_लिखो(gspca_dev, 0x07, 0xaa, 0xaa);
	retword = i2c_पढ़ो(gspca_dev, 0x07);
	अगर (retword != 0)
		वापस 0x0a;			/* PB0330 */
	retword = i2c_पढ़ो(gspca_dev, 0x03);
	अगर (retword != 0)
		वापस 0x0a;			/* PB0330 ?? */
	retword = i2c_पढ़ो(gspca_dev, 0x04);
	अगर (retword != 0)
		वापस 0x0a;			/* PB0330 ?? */

	start_2wr_probe(gspca_dev, 0x0c);	/* ICM105A */
	i2c_ग_लिखो(gspca_dev, 0x01, 0x11, 0x00);
	retword = i2c_पढ़ो(gspca_dev, 0x01);
	अगर (retword != 0)
		वापस 0x0c;			/* ICM105A */

	start_2wr_probe(gspca_dev, 0x0e);	/* PAS202BCB */
	reg_w(gspca_dev, 0x08, 0x008d);
	i2c_ग_लिखो(gspca_dev, 0x03, 0xaa, 0x00);
	msleep(50);
	retword = i2c_पढ़ो(gspca_dev, 0x03);
	अगर (retword != 0) अणु
		send_unknown(gspca_dev, SENSOR_PAS202B);
		वापस 0x0e;			/* PAS202BCB */
	पूर्ण

	start_2wr_probe(gspca_dev, 0x02);	/* TAS5130C */
	i2c_ग_लिखो(gspca_dev, 0x01, 0xaa, 0x00);
	retword = i2c_पढ़ो(gspca_dev, 0x01);
	अगर (retword != 0)
		वापस 0x02;			/* TAS5130C */
ov_check:
	reg_r(gspca_dev, 0x0010);		/* ?? */
	reg_r(gspca_dev, 0x0010);

	reg_w(gspca_dev, 0x01, 0x0000);
	reg_w(gspca_dev, 0x01, 0x0001);
	reg_w(gspca_dev, 0x06, 0x0010);		/* OmniVision */
	reg_w(gspca_dev, 0xa1, 0x008b);
	reg_w(gspca_dev, 0x08, 0x008d);
	msleep(500);
	reg_w(gspca_dev, 0x01, 0x0012);
	i2c_ग_लिखो(gspca_dev, 0x12, 0x80, 0x00);	/* sensor reset */
	retword = i2c_पढ़ो(gspca_dev, 0x0a) << 8;
	retword |= i2c_पढ़ो(gspca_dev, 0x0b);
	gspca_dbg(gspca_dev, D_PROBE, "probe 2wr ov vga 0x%04x\n", retword);
	चयन (retword) अणु
	हाल 0x7631:				/* OV7630C */
		reg_w(gspca_dev, 0x06, 0x0010);
		अवरोध;
	हाल 0x7620:				/* OV7620 */
	हाल 0x7648:				/* OV7648 */
		अवरोध;
	शेष:
		वापस -1;			/* not OmniVision */
	पूर्ण
	वापस retword;
पूर्ण

काष्ठा sensor_by_chipset_revision अणु
	u16 revision;
	u8 पूर्णांकernal_sensor_id;
पूर्ण;
अटल स्थिर काष्ठा sensor_by_chipset_revision chipset_revision_sensor[] = अणु
	अणु0xc000, 0x12पूर्ण,		/* TAS5130C */
	अणु0xc001, 0x13पूर्ण,		/* MT9V111 */
	अणु0xe001, 0x13पूर्ण,
	अणु0x8001, 0x13पूर्ण,
	अणु0x8000, 0x14पूर्ण,		/* CS2102K */
	अणु0x8400, 0x15पूर्ण,		/* MT9V111 */
	अणु0xe400, 0x15पूर्ण,
पूर्ण;

अटल पूर्णांक vga_3wr_probe(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i;
	u16 retword;

/*fixme: lack of 8b=b3 (11,12)-> 10, 8b=e0 (14,15,16)-> 12 found in gspcav1*/
	reg_w(gspca_dev, 0x02, 0x0010);
	reg_r(gspca_dev, 0x0010);
	reg_w(gspca_dev, 0x01, 0x0000);
	reg_w(gspca_dev, 0x00, 0x0010);
	reg_w(gspca_dev, 0x01, 0x0001);
	reg_w(gspca_dev, 0x91, 0x008b);
	reg_w(gspca_dev, 0x03, 0x0012);
	reg_w(gspca_dev, 0x01, 0x0012);
	reg_w(gspca_dev, 0x05, 0x0012);
	retword = i2c_पढ़ो(gspca_dev, 0x14);
	अगर (retword != 0)
		वापस 0x11;			/* HV7131R */
	retword = i2c_पढ़ो(gspca_dev, 0x15);
	अगर (retword != 0)
		वापस 0x11;			/* HV7131R */
	retword = i2c_पढ़ो(gspca_dev, 0x16);
	अगर (retword != 0)
		वापस 0x11;			/* HV7131R */

	reg_w(gspca_dev, 0x02, 0x0010);
	retword = reg_r(gspca_dev, 0x000b) << 8;
	retword |= reg_r(gspca_dev, 0x000a);
	gspca_dbg(gspca_dev, D_PROBE, "probe 3wr vga 1 0x%04x\n", retword);
	reg_r(gspca_dev, 0x0010);
	अगर ((retword & 0xff00) == 0x6400)
		वापस 0x02;		/* TAS5130C */
	क्रम (i = 0; i < ARRAY_SIZE(chipset_revision_sensor); i++) अणु
		अगर (chipset_revision_sensor[i].revision == retword) अणु
			sd->chip_revision = retword;
			send_unknown(gspca_dev, SENSOR_PB0330);
			वापस chipset_revision_sensor[i].पूर्णांकernal_sensor_id;
		पूर्ण
	पूर्ण

	reg_w(gspca_dev, 0x01, 0x0000);	/* check PB0330 */
	reg_w(gspca_dev, 0x01, 0x0001);
	reg_w(gspca_dev, 0xdd, 0x008b);
	reg_w(gspca_dev, 0x0a, 0x0010);
	reg_w(gspca_dev, 0x03, 0x0012);
	reg_w(gspca_dev, 0x01, 0x0012);
	retword = i2c_पढ़ो(gspca_dev, 0x00);
	अगर (retword != 0) अणु
		gspca_dbg(gspca_dev, D_PROBE, "probe 3wr vga type 0a\n");
		वापस 0x0a;			/* PB0330 */
	पूर्ण

	/* probe gc0303 / gc0305 */
	reg_w(gspca_dev, 0x01, 0x0000);
	reg_w(gspca_dev, 0x01, 0x0001);
	reg_w(gspca_dev, 0x98, 0x008b);
	reg_w(gspca_dev, 0x01, 0x0010);
	reg_w(gspca_dev, 0x03, 0x0012);
	msleep(2);
	reg_w(gspca_dev, 0x01, 0x0012);
	retword = i2c_पढ़ो(gspca_dev, 0x00);
	अगर (retword != 0) अणु
		gspca_dbg(gspca_dev, D_PROBE, "probe 3wr vga type %02x\n",
			  retword);
		अगर (retword == 0x0011)			/* gc0303 */
			वापस 0x0303;
		अगर (retword == 0x0029)			/* gc0305 */
			send_unknown(gspca_dev, SENSOR_GC0305);
		वापस retword;
	पूर्ण

	reg_w(gspca_dev, 0x01, 0x0000);	/* check OmniVision */
	reg_w(gspca_dev, 0x01, 0x0001);
	reg_w(gspca_dev, 0xa1, 0x008b);
	reg_w(gspca_dev, 0x08, 0x008d);
	reg_w(gspca_dev, 0x06, 0x0010);
	reg_w(gspca_dev, 0x01, 0x0012);
	reg_w(gspca_dev, 0x05, 0x0012);
	अगर (i2c_पढ़ो(gspca_dev, 0x1c) == 0x007f	/* OV7610 - manufacturer ID */
	    && i2c_पढ़ो(gspca_dev, 0x1d) == 0x00a2) अणु
		send_unknown(gspca_dev, SENSOR_OV7620);
		वापस 0x06;		/* OmniVision confirm ? */
	पूर्ण

	reg_w(gspca_dev, 0x01, 0x0000);
	reg_w(gspca_dev, 0x00, 0x0002);
	reg_w(gspca_dev, 0x01, 0x0010);
	reg_w(gspca_dev, 0x01, 0x0001);
	reg_w(gspca_dev, 0xee, 0x008b);
	reg_w(gspca_dev, 0x03, 0x0012);
	reg_w(gspca_dev, 0x01, 0x0012);
	reg_w(gspca_dev, 0x05, 0x0012);
	retword = i2c_पढ़ो(gspca_dev, 0x00) << 8;	/* ID 0 */
	retword |= i2c_पढ़ो(gspca_dev, 0x01);		/* ID 1 */
	gspca_dbg(gspca_dev, D_PROBE, "probe 3wr vga 2 0x%04x\n", retword);
	अगर (retword == 0x2030) अणु
		u8 retbyte;

		retbyte = i2c_पढ़ो(gspca_dev, 0x02);	/* revision number */
		gspca_dbg(gspca_dev, D_PROBE, "sensor PO2030 rev 0x%02x\n",
			  retbyte);

		send_unknown(gspca_dev, SENSOR_PO2030);
		वापस retword;
	पूर्ण

	reg_w(gspca_dev, 0x01, 0x0000);
	reg_w(gspca_dev, 0x0a, 0x0010);
	reg_w(gspca_dev, 0xd3, 0x008b);
	reg_w(gspca_dev, 0x01, 0x0001);
	reg_w(gspca_dev, 0x03, 0x0012);
	reg_w(gspca_dev, 0x01, 0x0012);
	reg_w(gspca_dev, 0x05, 0x0012);
	reg_w(gspca_dev, 0xd3, 0x008b);
	retword = i2c_पढ़ो(gspca_dev, 0x01);
	अगर (retword != 0) अणु
		gspca_dbg(gspca_dev, D_PROBE, "probe 3wr vga type 0a ? ret: %04x\n",
			  retword);
		वापस 0x16;			/* adcm2700 (6100/6200) */
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक zcxx_probeSensor(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक sensor;

	चयन (sd->sensor) अणु
	हाल SENSOR_MC501CB:
		वापस -1;		/* करोn't probe */
	हाल SENSOR_GC0303:
			/* may probe but with no ग_लिखो in reg 0x0010 */
		वापस -1;		/* करोn't probe */
	हाल SENSOR_PAS106:
		sensor =  sअगर_probe(gspca_dev);
		अगर (sensor >= 0)
			वापस sensor;
		अवरोध;
	पूर्ण
	sensor = vga_2wr_probe(gspca_dev);
	अगर (sensor >= 0)
		वापस sensor;
	वापस vga_3wr_probe(gspca_dev);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (id->idProduct == 0x301b)
		sd->bridge = BRIDGE_ZC301;
	अन्यथा
		sd->bridge = BRIDGE_ZC303;

	/* define some sensors from the venकरोr/product */
	sd->sensor = id->driver_info;

	sd->reg08 = REG08_DEF;

	INIT_WORK(&sd->work, transfer_update);

	वापस 0;
पूर्ण

अटल पूर्णांक zcxx_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		gspca_dev->usb_err = 0;
		अगर (ctrl->val && sd->exposure && gspca_dev->streaming)
			sd->exposure->val = getexposure(gspca_dev);
		वापस gspca_dev->usb_err;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक zcxx_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	पूर्णांक i, qual;

	gspca_dev->usb_err = 0;

	अगर (ctrl->id == V4L2_CID_JPEG_COMPRESSION_QUALITY) अणु
		qual = sd->reg08 >> 1;

		क्रम (i = 0; i < ARRAY_SIZE(jpeg_qual); i++) अणु
			अगर (ctrl->val <= jpeg_qual[i])
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(jpeg_qual) || (i > 0 && i == qual && ctrl->val < jpeg_qual[i]))
			i--;

		/* With high quality settings we need max bandwidth */
		अगर (i >= 2 && gspca_dev->streaming &&
		    !gspca_dev->cam.needs_full_bandwidth)
			वापस -EBUSY;

		sd->reg08 = (i << 1) | 1;
		ctrl->val = jpeg_qual[i];
	पूर्ण

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	/* gamma/brightness/contrast cluster */
	हाल V4L2_CID_GAMMA:
		setcontrast(gspca_dev, sd->gamma->val,
				sd->brightness->val, sd->contrast->val);
		अवरोध;
	/* स्वतःgain/exposure cluster */
	हाल V4L2_CID_AUTOGAIN:
		setस्वतःgain(gspca_dev, ctrl->val);
		अगर (!gspca_dev->usb_err && !ctrl->val && sd->exposure)
			setexposure(gspca_dev, sd->exposure->val);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		setlightfreq(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		setquality(gspca_dev);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops zcxx_ctrl_ops = अणु
	.g_अस्थिर_ctrl = zcxx_g_अस्थिर_ctrl,
	.s_ctrl = zcxx_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	अटल स्थिर u8 gamma[SENSOR_MAX] = अणु
		[SENSOR_ADCM2700] =	4,
		[SENSOR_CS2102] =	4,
		[SENSOR_CS2102K] =	5,
		[SENSOR_GC0303] =	3,
		[SENSOR_GC0305] =	4,
		[SENSOR_HDCS2020] =	4,
		[SENSOR_HV7131B] =	4,
		[SENSOR_HV7131R] =	4,
		[SENSOR_ICM105A] =	4,
		[SENSOR_MC501CB] =	4,
		[SENSOR_MT9V111_1] =	4,
		[SENSOR_MT9V111_3] =	4,
		[SENSOR_OV7620] =	3,
		[SENSOR_OV7630C] =	4,
		[SENSOR_PAS106] =	4,
		[SENSOR_PAS202B] =	4,
		[SENSOR_PB0330] =	4,
		[SENSOR_PO2030] =	4,
		[SENSOR_TAS5130C] =	3,
	पूर्ण;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 8);
	sd->brightness = v4l2_ctrl_new_std(hdl, &zcxx_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	sd->contrast = v4l2_ctrl_new_std(hdl, &zcxx_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 128);
	sd->gamma = v4l2_ctrl_new_std(hdl, &zcxx_ctrl_ops,
			V4L2_CID_GAMMA, 1, 6, 1, gamma[sd->sensor]);
	अगर (sd->sensor == SENSOR_HV7131R)
		sd->exposure = v4l2_ctrl_new_std(hdl, &zcxx_ctrl_ops,
			V4L2_CID_EXPOSURE, 0x30d, 0x493e, 1, 0x927);
	अन्यथा अगर (sd->sensor == SENSOR_OV7620)
		sd->exposure = v4l2_ctrl_new_std(hdl, &zcxx_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 255, 1, 0x41);
	sd->स्वतःgain = v4l2_ctrl_new_std(hdl, &zcxx_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	अगर (sd->sensor != SENSOR_OV7630C)
		sd->plfreq = v4l2_ctrl_new_std_menu(hdl, &zcxx_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 0,
			V4L2_CID_POWER_LINE_FREQUENCY_DISABLED);
	sd->sharpness = v4l2_ctrl_new_std(hdl, &zcxx_ctrl_ops,
			V4L2_CID_SHARPNESS, 0, 3, 1,
			sd->sensor == SENSOR_PO2030 ? 0 : 2);
	sd->jpegqual = v4l2_ctrl_new_std(hdl, &zcxx_ctrl_ops,
			V4L2_CID_JPEG_COMPRESSION_QUALITY,
			jpeg_qual[0], jpeg_qual[ARRAY_SIZE(jpeg_qual) - 1], 1,
			jpeg_qual[REG08_DEF >> 1]);
	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	v4l2_ctrl_cluster(3, &sd->gamma);
	अगर (sd->sensor == SENSOR_HV7131R || sd->sensor == SENSOR_OV7620)
		v4l2_ctrl_स्वतः_cluster(2, &sd->स्वतःgain, 0, true);
	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;
	पूर्णांक sensor;
	अटल स्थिर u8 mode_tb[SENSOR_MAX] = अणु
		[SENSOR_ADCM2700] =	2,
		[SENSOR_CS2102] =	1,
		[SENSOR_CS2102K] =	1,
		[SENSOR_GC0303] =	1,
		[SENSOR_GC0305] =	1,
		[SENSOR_HDCS2020] =	1,
		[SENSOR_HV7131B] =	1,
		[SENSOR_HV7131R] =	1,
		[SENSOR_ICM105A] =	1,
		[SENSOR_MC501CB] =	2,
		[SENSOR_MT9V111_1] =	1,
		[SENSOR_MT9V111_3] =	1,
		[SENSOR_OV7620] =	2,
		[SENSOR_OV7630C] =	1,
		[SENSOR_PAS106] =	0,
		[SENSOR_PAS202B] =	1,
		[SENSOR_PB0330] =	1,
		[SENSOR_PO2030] =	1,
		[SENSOR_TAS5130C] =	1,
	पूर्ण;

	sensor = zcxx_probeSensor(gspca_dev);
	अगर (sensor >= 0)
		gspca_dbg(gspca_dev, D_PROBE, "probe sensor -> %04x\n", sensor);
	अगर ((अचिन्हित) क्रमce_sensor < SENSOR_MAX) अणु
		sd->sensor = क्रमce_sensor;
		gspca_dbg(gspca_dev, D_PROBE, "sensor forced to %d\n",
			  क्रमce_sensor);
	पूर्ण अन्यथा अणु
		चयन (sensor) अणु
		हाल -1:
			चयन (sd->sensor) अणु
			हाल SENSOR_MC501CB:
				gspca_dbg(gspca_dev, D_PROBE, "Sensor MC501CB\n");
				अवरोध;
			हाल SENSOR_GC0303:
				gspca_dbg(gspca_dev, D_PROBE, "Sensor GC0303\n");
				अवरोध;
			शेष:
				pr_warn("Unknown sensor - set to TAS5130C\n");
				sd->sensor = SENSOR_TAS5130C;
			पूर्ण
			अवरोध;
		हाल 0:
			/* check the sensor type */
			sensor = i2c_पढ़ो(gspca_dev, 0x00);
			gspca_dbg(gspca_dev, D_PROBE, "Sensor hv7131 type %d\n",
				  sensor);
			चयन (sensor) अणु
			हाल 0:			/* hv7131b */
			हाल 1:			/* hv7131e */
				gspca_dbg(gspca_dev, D_PROBE, "Find Sensor HV7131B\n");
				sd->sensor = SENSOR_HV7131B;
				अवरोध;
			शेष:
/*			हाल 2:			 * hv7131r */
				gspca_dbg(gspca_dev, D_PROBE, "Find Sensor HV7131R\n");
				sd->sensor = SENSOR_HV7131R;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x02:
			gspca_dbg(gspca_dev, D_PROBE, "Sensor TAS5130C\n");
			sd->sensor = SENSOR_TAS5130C;
			अवरोध;
		हाल 0x04:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor CS2102\n");
			sd->sensor = SENSOR_CS2102;
			अवरोध;
		हाल 0x08:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor HDCS2020\n");
			sd->sensor = SENSOR_HDCS2020;
			अवरोध;
		हाल 0x0a:
			gspca_dbg(gspca_dev, D_PROBE,
				  "Find Sensor PB0330. Chip revision %x\n",
				  sd->chip_revision);
			sd->sensor = SENSOR_PB0330;
			अवरोध;
		हाल 0x0c:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor ICM105A\n");
			sd->sensor = SENSOR_ICM105A;
			अवरोध;
		हाल 0x0e:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor PAS202B\n");
			sd->sensor = SENSOR_PAS202B;
			अवरोध;
		हाल 0x0f:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor PAS106\n");
			sd->sensor = SENSOR_PAS106;
			अवरोध;
		हाल 0x10:
		हाल 0x12:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor TAS5130C\n");
			sd->sensor = SENSOR_TAS5130C;
			अवरोध;
		हाल 0x11:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor HV7131R\n");
			sd->sensor = SENSOR_HV7131R;
			अवरोध;
		हाल 0x13:
		हाल 0x15:
			gspca_dbg(gspca_dev, D_PROBE,
				  "Sensor MT9V111. Chip revision %04x\n",
				  sd->chip_revision);
			sd->sensor = sd->bridge == BRIDGE_ZC301
					? SENSOR_MT9V111_1
					: SENSOR_MT9V111_3;
			अवरोध;
		हाल 0x14:
			gspca_dbg(gspca_dev, D_PROBE,
				  "Find Sensor CS2102K?. Chip revision %x\n",
				  sd->chip_revision);
			sd->sensor = SENSOR_CS2102K;
			अवरोध;
		हाल 0x16:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor ADCM2700\n");
			sd->sensor = SENSOR_ADCM2700;
			अवरोध;
		हाल 0x29:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor GC0305\n");
			sd->sensor = SENSOR_GC0305;
			अवरोध;
		हाल 0x0303:
			gspca_dbg(gspca_dev, D_PROBE, "Sensor GC0303\n");
			sd->sensor =  SENSOR_GC0303;
			अवरोध;
		हाल 0x2030:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor PO2030\n");
			sd->sensor = SENSOR_PO2030;
			अवरोध;
		हाल 0x7620:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor OV7620\n");
			sd->sensor = SENSOR_OV7620;
			अवरोध;
		हाल 0x7631:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor OV7630C\n");
			sd->sensor = SENSOR_OV7630C;
			अवरोध;
		हाल 0x7648:
			gspca_dbg(gspca_dev, D_PROBE, "Find Sensor OV7648\n");
			sd->sensor = SENSOR_OV7620;	/* same sensor (?) */
			अवरोध;
		शेष:
			pr_err("Unknown sensor %04x\n", sensor);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (sensor < 0x20) अणु
		अगर (sensor == -1 || sensor == 0x10 || sensor == 0x12)
			reg_w(gspca_dev, 0x02, 0x0010);
		reg_r(gspca_dev, 0x0010);
	पूर्ण

	cam = &gspca_dev->cam;
	चयन (mode_tb[sd->sensor]) अणु
	हाल 0:
		cam->cam_mode = sअगर_mode;
		cam->nmodes = ARRAY_SIZE(sअगर_mode);
		अवरोध;
	हाल 1:
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
		अवरोध;
	शेष:
/*	हाल 2: */
		cam->cam_mode = broken_vga_mode;
		cam->nmodes = ARRAY_SIZE(broken_vga_mode);
		अवरोध;
	पूर्ण

	/* चयन off the led */
	reg_w(gspca_dev, 0x01, 0x0000);
	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक sd_pre_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	gspca_dev->cam.needs_full_bandwidth = (sd->reg08 >= 4) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक mode;
	अटल स्थिर काष्ठा usb_action *init_tb[SENSOR_MAX][2] = अणु
	[SENSOR_ADCM2700] =
			अणुadcm2700_Initial, adcm2700_InitialScaleपूर्ण,
	[SENSOR_CS2102]	=
			अणुcs2102_Initial, cs2102_InitialScaleपूर्ण,
	[SENSOR_CS2102K] =
			अणुcs2102K_Initial, cs2102K_InitialScaleपूर्ण,
	[SENSOR_GC0303] =
		अणुgc0303_Initial, gc0303_InitialScaleपूर्ण,
	[SENSOR_GC0305] =
			अणुgc0305_Initial, gc0305_InitialScaleपूर्ण,
	[SENSOR_HDCS2020] =
			अणुhdcs2020_Initial, hdcs2020_InitialScaleपूर्ण,
	[SENSOR_HV7131B] =
			अणुhv7131b_Initial, hv7131b_InitialScaleपूर्ण,
	[SENSOR_HV7131R] =
			अणुhv7131r_Initial, hv7131r_InitialScaleपूर्ण,
	[SENSOR_ICM105A] =
			अणुicm105a_Initial, icm105a_InitialScaleपूर्ण,
	[SENSOR_MC501CB] =
			अणुmc501cb_Initial, mc501cb_InitialScaleपूर्ण,
	[SENSOR_MT9V111_1] =
			अणुmt9v111_1_Initial, mt9v111_1_InitialScaleपूर्ण,
	[SENSOR_MT9V111_3] =
			अणुmt9v111_3_Initial, mt9v111_3_InitialScaleपूर्ण,
	[SENSOR_OV7620] =
			अणुov7620_Initial, ov7620_InitialScaleपूर्ण,
	[SENSOR_OV7630C] =
			अणुov7630c_Initial, ov7630c_InitialScaleपूर्ण,
	[SENSOR_PAS106] =
			अणुpas106b_Initial, pas106b_InitialScaleपूर्ण,
	[SENSOR_PAS202B] =
			अणुpas202b_Initial, pas202b_InitialScaleपूर्ण,
	[SENSOR_PB0330] =
			अणुpb0330_Initial, pb0330_InitialScaleपूर्ण,
	[SENSOR_PO2030] =
			अणुpo2030_Initial, po2030_InitialScaleपूर्ण,
	[SENSOR_TAS5130C] =
			अणुtas5130c_Initial, tas5130c_InitialScaleपूर्ण,
	पूर्ण;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x21);		/* JPEG 422 */

	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	चयन (sd->sensor) अणु
	हाल SENSOR_HV7131R:
		zcxx_probeSensor(gspca_dev);
		अवरोध;
	हाल SENSOR_PAS106:
		usb_exchange(gspca_dev, pas106b_Initial_com);
		अवरोध;
	पूर्ण
	usb_exchange(gspca_dev, init_tb[sd->sensor][mode]);

	चयन (sd->sensor) अणु
	हाल SENSOR_ADCM2700:
	हाल SENSOR_GC0305:
	हाल SENSOR_OV7620:
	हाल SENSOR_PO2030:
	हाल SENSOR_TAS5130C:
	हाल SENSOR_GC0303:
/*		msleep(100);			 * ?? */
		reg_r(gspca_dev, 0x0002);	/* --> 0x40 */
		reg_w(gspca_dev, 0x09, 0x01ad);	/* (from win traces) */
		reg_w(gspca_dev, 0x15, 0x01ae);
		अगर (sd->sensor == SENSOR_TAS5130C)
			अवरोध;
		reg_w(gspca_dev, 0x0d, 0x003a);
		reg_w(gspca_dev, 0x02, 0x003b);
		reg_w(gspca_dev, 0x00, 0x0038);
		अवरोध;
	हाल SENSOR_HV7131R:
	हाल SENSOR_PAS202B:
		reg_w(gspca_dev, 0x03, 0x003b);
		reg_w(gspca_dev, 0x0c, 0x003a);
		reg_w(gspca_dev, 0x0b, 0x0039);
		अगर (sd->sensor == SENSOR_HV7131R)
			reg_w(gspca_dev, 0x50, ZC3XX_R11D_GLOBALGAIN);
		अवरोध;
	पूर्ण

	seपंचांगatrix(gspca_dev);
	चयन (sd->sensor) अणु
	हाल SENSOR_ADCM2700:
	हाल SENSOR_OV7620:
		reg_r(gspca_dev, 0x0008);
		reg_w(gspca_dev, 0x00, 0x0008);
		अवरोध;
	हाल SENSOR_PAS202B:
	हाल SENSOR_GC0305:
	हाल SENSOR_HV7131R:
	हाल SENSOR_TAS5130C:
		reg_r(gspca_dev, 0x0008);
		fallthrough;
	हाल SENSOR_PO2030:
		reg_w(gspca_dev, 0x03, 0x0008);
		अवरोध;
	पूर्ण
	setsharpness(gspca_dev, v4l2_ctrl_g_ctrl(sd->sharpness));

	/* set the gamma tables when not set */
	चयन (sd->sensor) अणु
	हाल SENSOR_CS2102K:		/* gamma set in xxx_Initial */
	हाल SENSOR_HDCS2020:
	हाल SENSOR_OV7630C:
		अवरोध;
	शेष:
		setcontrast(gspca_dev, v4l2_ctrl_g_ctrl(sd->gamma),
				v4l2_ctrl_g_ctrl(sd->brightness),
				v4l2_ctrl_g_ctrl(sd->contrast));
		अवरोध;
	पूर्ण
	seपंचांगatrix(gspca_dev);			/* one more समय? */
	चयन (sd->sensor) अणु
	हाल SENSOR_OV7620:
	हाल SENSOR_PAS202B:
		reg_r(gspca_dev, 0x0180);	/* from win */
		reg_w(gspca_dev, 0x00, 0x0180);
		अवरोध;
	पूर्ण
	setquality(gspca_dev);
	/* Start with BRC disabled, transfer_update will enable it अगर needed */
	reg_w(gspca_dev, 0x00, 0x0007);
	अगर (sd->plfreq)
		setlightfreq(gspca_dev, v4l2_ctrl_g_ctrl(sd->plfreq));

	चयन (sd->sensor) अणु
	हाल SENSOR_ADCM2700:
		reg_w(gspca_dev, 0x09, 0x01ad);	/* (from win traces) */
		reg_w(gspca_dev, 0x15, 0x01ae);
		reg_w(gspca_dev, 0x02, 0x0180);
						/* ms-win + */
		reg_w(gspca_dev, 0x40, 0x0117);
		अवरोध;
	हाल SENSOR_HV7131R:
		setexposure(gspca_dev, v4l2_ctrl_g_ctrl(sd->exposure));
		reg_w(gspca_dev, 0x00, ZC3XX_R1A7_CALCGLOBALMEAN);
		अवरोध;
	हाल SENSOR_GC0305:
	हाल SENSOR_TAS5130C:
		reg_w(gspca_dev, 0x09, 0x01ad);	/* (from win traces) */
		reg_w(gspca_dev, 0x15, 0x01ae);
		fallthrough;
	हाल SENSOR_PAS202B:
	हाल SENSOR_PO2030:
/*		reg_w(gspca_dev, 0x40, ZC3XX_R117_GGAIN); in win traces */
		reg_r(gspca_dev, 0x0180);
		अवरोध;
	हाल SENSOR_OV7620:
		reg_w(gspca_dev, 0x09, 0x01ad);
		reg_w(gspca_dev, 0x15, 0x01ae);
		i2c_पढ़ो(gspca_dev, 0x13);	/*fixme: वापसs 0xa3 */
		i2c_ग_लिखो(gspca_dev, 0x13, 0xa3, 0x00);
					/*fixme: वापसed value to send? */
		reg_w(gspca_dev, 0x40, 0x0117);
		reg_r(gspca_dev, 0x0180);
		अवरोध;
	पूर्ण

	setस्वतःgain(gspca_dev, v4l2_ctrl_g_ctrl(sd->स्वतःgain));

	अगर (gspca_dev->usb_err < 0)
		वापस gspca_dev->usb_err;

	/* Start the transfer parameters update thपढ़ो */
	schedule_work(&sd->work);

	वापस 0;
पूर्ण

/* called on streamoff with alt==0 and on disconnect */
/* the usb_lock is held at entry - restore on निकास */
अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	mutex_unlock(&gspca_dev->usb_lock);
	flush_work(&sd->work);
	mutex_lock(&gspca_dev->usb_lock);
	अगर (!gspca_dev->present)
		वापस;
	send_unknown(gspca_dev, sd->sensor);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,
			पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* check the JPEG end of frame */
	अगर (len >= 3
	 && data[len - 3] == 0xff && data[len - 2] == 0xd9) अणु
/*fixme: what करोes the last byte mean?*/
		gspca_frame_add(gspca_dev, LAST_PACKET,
					data, len - 1);
		वापस;
	पूर्ण

	/* check the JPEG start of a frame */
	अगर (data[0] == 0xff && data[1] == 0xd8) अणु
		/* put the JPEG header in the new frame */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sd->jpeg_hdr, JPEG_HDR_SZ);

		/* हटाओ the webcam's header:
		 * ff d8 ff fe 00 0e 00 00 ss ss 00 01 ww ww hh hh pp pp
		 *	- 'ss ss' is the frame sequence number (BE)
		 *	- 'ww ww' and 'hh hh' are the winकरोw dimensions (BE)
		 *	- 'pp pp' is the packet sequence number (BE)
		 */
		data += 18;
		len -= 18;
	पूर्ण
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

अटल पूर्णांक sd_set_jcomp(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा v4l2_jpegcompression *jcomp)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	वापस v4l2_ctrl_s_ctrl(sd->jpegqual, jcomp->quality);
पूर्ण

अटल पूर्णांक sd_get_jcomp(काष्ठा gspca_dev *gspca_dev,
			काष्ठा v4l2_jpegcompression *jcomp)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	स_रखो(jcomp, 0, माप *jcomp);
	jcomp->quality = v4l2_ctrl_g_ctrl(sd->jpegqual);
	jcomp->jpeg_markers = V4L2_JPEG_MARKER_DHT
			| V4L2_JPEG_MARKER_DQT;
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_INPUT)
अटल पूर्णांक sd_पूर्णांक_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,		/* पूर्णांकerrupt packet data */
			पूर्णांक len)		/* पूर्णांकerrupt packet length */
अणु
	अगर (len == 8 && data[4] == 1) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 1);
		input_sync(gspca_dev->input_dev);
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = KBUILD_MODNAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.isoc_init = sd_pre_start,
	.start = sd_start,
	.stop0 = sd_stop0,
	.pkt_scan = sd_pkt_scan,
	.get_jcomp = sd_get_jcomp,
	.set_jcomp = sd_set_jcomp,
#अगर IS_ENABLED(CONFIG_INPUT)
	.पूर्णांक_pkt_scan = sd_पूर्णांक_pkt_scan,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x03f0, 0x1b07)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x041e)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4017)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x401c), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x401e)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x401f)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4022)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4029)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4034), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4035), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4036)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x403a)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4051), .driver_info = SENSOR_GC0303पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4053), .driver_info = SENSOR_GC0303पूर्ण,
	अणुUSB_DEVICE(0x0458, 0x7007)पूर्ण,
	अणुUSB_DEVICE(0x0458, 0x700c)पूर्ण,
	अणुUSB_DEVICE(0x0458, 0x700f)पूर्ण,
	अणुUSB_DEVICE(0x0461, 0x0a00)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x089d), .driver_info = SENSOR_MC501CBपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08a0)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08a1)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08a2)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08a3)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08a6)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08a7)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08a9)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08aa)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08ac)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08ad)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08ae)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08af)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08b9)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08d7)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08d8)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08d9)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08da)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x08dd), .driver_info = SENSOR_MC501CBपूर्ण,
	अणुUSB_DEVICE(0x0471, 0x0325), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x0471, 0x0326), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x0471, 0x032d), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x0471, 0x032e), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc005)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xd003)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xd004)पूर्ण,
	अणुUSB_DEVICE(0x0698, 0x2003)पूर्ण,
	अणुUSB_DEVICE(0x0ac8, 0x0301), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x0ac8, 0x0302), .driver_info = SENSOR_PAS106पूर्ण,
	अणुUSB_DEVICE(0x0ac8, 0x301b)पूर्ण,
	अणुUSB_DEVICE(0x0ac8, 0x303b)पूर्ण,
	अणुUSB_DEVICE(0x0ac8, 0x305b)पूर्ण,
	अणुUSB_DEVICE(0x0ac8, 0x307b)पूर्ण,
	अणुUSB_DEVICE(0x10fd, 0x0128)पूर्ण,
	अणुUSB_DEVICE(0x10fd, 0x804d)पूर्ण,
	अणुUSB_DEVICE(0x10fd, 0x8050)पूर्ण,
	अणुपूर्ण			/* end of entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
				THIS_MODULE);
पूर्ण

/* USB driver */
अटल काष्ठा usb_driver sd_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = device_table,
	.probe = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);

module_param(क्रमce_sensor, पूर्णांक, 0644);
MODULE_PARM_DESC(क्रमce_sensor,
	"Force sensor. Only for experts!!!");
