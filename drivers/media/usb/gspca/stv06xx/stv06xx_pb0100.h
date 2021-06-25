<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2001 Jean-Fredric Clere, Nikolas Zimmermann, Georg Acher
 *		      Mark Cave-Ayland, Carlo E Prelz, Dick Streefland
 * Copyright (c) 2002, 2003 Tuukka Toivonen
 * Copyright (c) 2008 Erik Andrथऊn
 *
 * P/N 861037:      Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensor Photobit PB100  ASIC STV0600-1 - QuickCam Express
 * P/N 861055:      Sensor ST VV6410       ASIC STV0610   - LEGO cam
 * P/N 861075-0040: Sensor HDCS1000        ASIC
 * P/N 961179-0700: Sensor ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensor ST VV6410       ASIC STV0610   - QuickCam Web
 */

#अगर_अघोषित STV06XX_PB0100_H_
#घोषणा STV06XX_PB0100_H_

#समावेश "stv06xx_sensor.h"

/* mode priv field flags */
#घोषणा PB0100_CROP_TO_VGA	0x01
#घोषणा PB0100_SUBSAMPLE	0x02

/* I2C Registers */
#घोषणा PB_IDENT		0x00	/* Chip Version */
#घोषणा PB_RSTART		0x01	/* Row Winकरोw Start */
#घोषणा PB_CSTART		0x02	/* Column Winकरोw Start */
#घोषणा PB_RWSIZE		0x03	/* Row Winकरोw Size */
#घोषणा PB_CWSIZE		0x04	/* Column  Winकरोw Size */
#घोषणा PB_CFILLIN		0x05	/* Column Fill-In */
#घोषणा PB_VBL			0x06	/* Vertical Blank Count */
#घोषणा PB_CONTROL		0x07	/* Control Mode */
#घोषणा PB_FINTTIME		0x08	/* Integration Time/Frame Unit Count */
#घोषणा PB_RINTTIME		0x09	/* Integration Time/Row Unit Count */
#घोषणा PB_ROWSPEED		0x0a	/* Row Speed Control */
#घोषणा PB_ABORTFRAME		0x0b	/* Abort Frame */
#घोषणा PB_R12			0x0c	/* Reserved */
#घोषणा PB_RESET		0x0d	/* Reset */
#घोषणा PB_EXPGAIN		0x0e	/* Exposure Gain Command */
#घोषणा PB_R15			0x0f	/* Expose0 */
#घोषणा PB_R16			0x10	/* Expose1 */
#घोषणा PB_R17			0x11	/* Expose2 */
#घोषणा PB_R18			0x12	/* Low0_DAC */
#घोषणा PB_R19			0x13	/* Low1_DAC */
#घोषणा PB_R20			0x14	/* Low2_DAC */
#घोषणा PB_R21			0x15	/* Threshold11 */
#घोषणा PB_R22			0x16	/* Threshold0x */
#घोषणा PB_UPDATEINT		0x17	/* Update Interval */
#घोषणा PB_R24			0x18	/* High_DAC */
#घोषणा PB_R25			0x19	/* Trans0H */
#घोषणा PB_R26			0x1a	/* Trans1L */
#घोषणा PB_R27			0x1b	/* Trans1H */
#घोषणा PB_R28			0x1c	/* Trans2L */
#घोषणा PB_R29			0x1d	/* Reserved */
#घोषणा PB_R30			0x1e	/* Reserved */
#घोषणा PB_R31			0x1f	/* Wait to Read */
#घोषणा PB_PREADCTRL		0x20	/* Pixel Read Control Mode */
#घोषणा PB_R33			0x21	/* IREF_VLN */
#घोषणा PB_R34			0x22	/* IREF_VLP */
#घोषणा PB_R35			0x23	/* IREF_VLN_INTEG */
#घोषणा PB_R36			0x24	/* IREF_MASTER */
#घोषणा PB_R37			0x25	/* IDACP */
#घोषणा PB_R38			0x26	/* IDACN */
#घोषणा PB_R39			0x27	/* DAC_Control_Reg */
#घोषणा PB_R40			0x28	/* VCL */
#घोषणा PB_R41			0x29	/* IREF_VLN_ADCIN */
#घोषणा PB_R42			0x2a	/* Reserved */
#घोषणा PB_G1GAIN		0x2b	/* Green 1 Gain */
#घोषणा PB_BGAIN		0x2c	/* Blue Gain */
#घोषणा PB_RGAIN		0x2d	/* Red Gain */
#घोषणा PB_G2GAIN		0x2e	/* Green 2 Gain */
#घोषणा PB_R47			0x2f	/* Dark Row Address */
#घोषणा PB_R48			0x30	/* Dark Row Options */
#घोषणा PB_R49			0x31	/* Reserved */
#घोषणा PB_R50			0x32	/* Image Test Data */
#घोषणा PB_ADCMAXGAIN		0x33	/* Maximum Gain */
#घोषणा PB_ADCMINGAIN		0x34	/* Minimum Gain */
#घोषणा PB_ADCGLOBALGAIN	0x35	/* Global Gain */
#घोषणा PB_R54			0x36	/* Maximum Frame */
#घोषणा PB_R55			0x37	/* Minimum Frame */
#घोषणा PB_R56			0x38	/* Reserved */
#घोषणा PB_VOFFSET		0x39	/* VOFFSET */
#घोषणा PB_R58			0x3a	/* Snap-Shot Sequence Trigger */
#घोषणा PB_ADCGAINH		0x3b	/* VREF_HI */
#घोषणा PB_ADCGAINL		0x3c	/* VREF_LO */
#घोषणा PB_R61			0x3d	/* Reserved */
#घोषणा PB_R62			0x3e	/* Reserved */
#घोषणा PB_R63			0x3f	/* Reserved */
#घोषणा PB_R64			0x40	/* Red/Blue Gain */
#घोषणा PB_R65			0x41	/* Green 2/Green 1 Gain */
#घोषणा PB_R66			0x42	/* VREF_HI/LO */
#घोषणा PB_R67			0x43	/* Integration Time/Row Unit Count */
#घोषणा PB_R240			0xf0	/* ADC Test */
#घोषणा PB_R241			0xf1    /* Chip Enable */
#घोषणा PB_R242			0xf2	/* Reserved */

अटल पूर्णांक pb0100_probe(काष्ठा sd *sd);
अटल पूर्णांक pb0100_start(काष्ठा sd *sd);
अटल पूर्णांक pb0100_init(काष्ठा sd *sd);
अटल पूर्णांक pb0100_init_controls(काष्ठा sd *sd);
अटल पूर्णांक pb0100_stop(काष्ठा sd *sd);
अटल पूर्णांक pb0100_dump(काष्ठा sd *sd);

/* V4L2 controls supported by the driver */
अटल पूर्णांक pb0100_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val);
अटल पूर्णांक pb0100_set_red_balance(काष्ठा gspca_dev *gspca_dev, __s32 val);
अटल पूर्णांक pb0100_set_blue_balance(काष्ठा gspca_dev *gspca_dev, __s32 val);
अटल पूर्णांक pb0100_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val);
अटल पूर्णांक pb0100_set_स्वतःgain(काष्ठा gspca_dev *gspca_dev, __s32 val);
अटल पूर्णांक pb0100_set_स्वतःgain_target(काष्ठा gspca_dev *gspca_dev, __s32 val);

स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_pb0100 = अणु
	.name = "PB-0100",
	.i2c_flush = 1,
	.i2c_addr = 0xba,
	.i2c_len = 2,

	.min_packet_size = अणु 635, 847 पूर्ण,
	.max_packet_size = अणु 847, 923 पूर्ण,

	.init = pb0100_init,
	.init_controls = pb0100_init_controls,
	.probe = pb0100_probe,
	.start = pb0100_start,
	.stop = pb0100_stop,
	.dump = pb0100_dump,
पूर्ण;

#पूर्ण_अगर
