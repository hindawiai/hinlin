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

#अगर_अघोषित STV06XX_VV6410_H_
#घोषणा STV06XX_VV6410_H_

#समावेश "stv06xx_sensor.h"

#घोषणा VV6410_COLS			416
#घोषणा VV6410_ROWS			320

/* Status रेजिस्टरs */
/* Chip identअगरication number including revision indicator */
#घोषणा VV6410_DEVICEH			0x00
#घोषणा VV6410_DEVICEL			0x01

/* User can determine whether समयd I2C data
   has been consumed by पूर्णांकerrogating flag states */
#घोषणा VV6410_STATUS0			0x02

/* Current line counter value */
#घोषणा VV6410_LINECOUNTH		0x03
#घोषणा VV6410_LINECOUNTL		0x04

/* End x coordinate of image size */
#घोषणा VV6410_XENDH			0x05
#घोषणा VV6410_XENDL			0x06

/* End y coordinate of image size */
#घोषणा VV6410_YENDH			0x07
#घोषणा VV6410_YENDL			0x08

/* This is the average pixel value वापसed from the
   dark line offset cancellation algorithm */
#घोषणा VV6410_DARKAVGH			0x09
#घोषणा VV6410_DARKAVGL			0x0a

/* This is the average pixel value वापसed from the
   black line offset cancellation algorithm  */
#घोषणा VV6410_BLACKAVGH		0x0b
#घोषणा VV6410_BLACKAVGL		0x0c

/* Flags to indicate whether the x or y image coordinates have been clipped */
#घोषणा VV6410_STATUS1			0x0d

/* Setup रेजिस्टरs */

/* Low-घातer/sleep modes & video timing */
#घोषणा VV6410_SETUP0			0x10

/* Various parameters */
#घोषणा VV6410_SETUP1			0x11

/* Contains pixel counter reset value used by बाह्यal sync */
#घोषणा VV6410_SYNCVALUE		0x12

/* Frame grabbing modes (FST, LST and QCK) */
#घोषणा VV6410_FGMODES			0x14

/* FST and QCK mapping modes. */
#घोषणा VV6410_PINMAPPING		0x15

/* Data resolution */
#घोषणा VV6410_DATAFORMAT		0x16

/* Output coding क्रमmats */
#घोषणा VV6410_OPFORMAT			0x17

/* Various mode select bits */
#घोषणा VV6410_MODESELECT		0x18

/* Exposure रेजिस्टरs */
/* Fine exposure. */
#घोषणा VV6410_FINEH			0x20
#घोषणा VV6410_FINEL			0x21

/* Coarse exposure */
#घोषणा VV6410_COARSEH			0x22
#घोषणा VV6410_COARSEL			0x23

/* Analog gain setting */
#घोषणा VV6410_ANALOGGAIN		0x24

/* Clock भागision */
#घोषणा VV6410_CLKDIV			0x25

/* Dark line offset cancellation value */
#घोषणा VV6410_DARKOFFSETH		0x2c
#घोषणा VV6410_DARKOFFSETL		0x2d

/* Dark line offset cancellation enable */
#घोषणा VV6410_DARKOFFSETSETUP		0x2e

/* Video timing रेजिस्टरs */
/* Line Length (Pixel Clocks) */
#घोषणा VV6410_LINELENGTHH		0x52
#घोषणा VV6410_LINELENGTHL		0x53

/* X-co-ordinate of top left corner of region of पूर्णांकerest (x-offset) */
#घोषणा VV6410_XOFFSETH			0x57
#घोषणा VV6410_XOFFSETL			0x58

/* Y-coordinate of top left corner of region of पूर्णांकerest (y-offset) */
#घोषणा VV6410_YOFFSETH			0x59
#घोषणा VV6410_YOFFSETL			0x5a

/* Field length (Lines) */
#घोषणा VV6410_FIELDLENGTHH		0x61
#घोषणा VV6410_FIELDLENGTHL		0x62

/* System रेजिस्टरs */
/* Black offset cancellation शेष value */
#घोषणा VV6410_BLACKOFFSETH		0x70
#घोषणा VV6410_BLACKOFFSETL		0x71

/* Black offset cancellation setup */
#घोषणा VV6410_BLACKOFFSETSETUP		0x72

/* Analog Control Register 0 */
#घोषणा VV6410_CR0			0x75

/* Analog Control Register 1 */
#घोषणा VV6410_CR1			0x76

/* ADC Setup Register */
#घोषणा VV6410_AS0			0x77

/* Analog Test Register */
#घोषणा VV6410_AT0			0x78

/* Audio Amplअगरier Setup Register */
#घोषणा VV6410_AT1			0x79

#घोषणा VV6410_HFLIP			(1 << 3)
#घोषणा VV6410_VFLIP			(1 << 4)

#घोषणा VV6410_LOW_POWER_MODE		(1 << 0)
#घोषणा VV6410_SOFT_RESET		(1 << 2)
#घोषणा VV6410_PAL_25_FPS		(0 << 3)

#घोषणा VV6410_CLK_DIV_2		(1 << 1)

#घोषणा VV6410_FINE_EXPOSURE		320
#घोषणा VV6410_COARSE_EXPOSURE		192
#घोषणा VV6410_DEFAULT_GAIN		5

#घोषणा VV6410_SUBSAMPLE		0x01
#घोषणा VV6410_CROP_TO_QVGA		0x02

#घोषणा VV6410_CIF_LINELENGTH		415

अटल पूर्णांक vv6410_probe(काष्ठा sd *sd);
अटल पूर्णांक vv6410_start(काष्ठा sd *sd);
अटल पूर्णांक vv6410_init(काष्ठा sd *sd);
अटल पूर्णांक vv6410_init_controls(काष्ठा sd *sd);
अटल पूर्णांक vv6410_stop(काष्ठा sd *sd);
अटल पूर्णांक vv6410_dump(काष्ठा sd *sd);

/* V4L2 controls supported by the driver */
अटल पूर्णांक vv6410_set_hflip(काष्ठा gspca_dev *gspca_dev, __s32 val);
अटल पूर्णांक vv6410_set_vflip(काष्ठा gspca_dev *gspca_dev, __s32 val);
अटल पूर्णांक vv6410_set_analog_gain(काष्ठा gspca_dev *gspca_dev, __s32 val);
अटल पूर्णांक vv6410_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val);

स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_vv6410 = अणु
	.name = "ST VV6410",
	.i2c_flush = 5,
	.i2c_addr = 0x20,
	.i2c_len = 1,
	/* FIXME (see अगर we can lower packet_size-s, needs testing, and also
	   adjusting framerate when the bandwidth माला_लो lower) */
	.min_packet_size = अणु 1023 पूर्ण,
	.max_packet_size = अणु 1023 पूर्ण,
	.init = vv6410_init,
	.init_controls = vv6410_init_controls,
	.probe = vv6410_probe,
	.start = vv6410_start,
	.stop = vv6410_stop,
	.dump = vv6410_dump,
पूर्ण;

/* If शून्य, only single value to ग_लिखो, stored in len */
काष्ठा stv_init अणु
	u16 addr;
	u8 data;
पूर्ण;

अटल स्थिर काष्ठा stv_init stv_bridge_init[] = अणु
	/* This reg is written twice. Some kind of reset? */
	अणुSTV_RESET, 0x80पूर्ण,
	अणुSTV_RESET, 0x00पूर्ण,
	अणुSTV_SCAN_RATE, 0x00पूर्ण,
	अणुSTV_I2C_FLUSH, 0x04पूर्ण,
	अणुSTV_REG00, 0x0bपूर्ण,
	अणुSTV_REG01, 0xa7पूर्ण,
	अणुSTV_REG02, 0xb7पूर्ण,
	अणुSTV_REG03, 0x00पूर्ण,
	अणुSTV_REG04, 0x00पूर्ण,
	अणु0x1536, 0x02पूर्ण,
	अणु0x1537, 0x00पूर्ण,
	अणु0x1538, 0x60पूर्ण,
	अणु0x1539, 0x01पूर्ण,
	अणु0x153a, 0x20पूर्ण,
	अणु0x153b, 0x01पूर्ण,
पूर्ण;

अटल स्थिर u8 vv6410_sensor_init[][2] = अणु
	/* Setup रेजिस्टरs */
	अणुVV6410_SETUP0,	VV6410_SOFT_RESETपूर्ण,
	अणुVV6410_SETUP0,	VV6410_LOW_POWER_MODEपूर्ण,
	/* Use shuffled पढ़ो-out mode */
	अणुVV6410_SETUP1,	BIT(6)पूर्ण,
	/* All modes to 1, FST, Fast QCK, Free running QCK, Free running LST, FST will qualअगरy visible pixels */
	अणुVV6410_FGMODES, BIT(6) | BIT(4) | BIT(2) | BIT(0)पूर्ण,
	अणुVV6410_PINMAPPING, 0x00पूर्ण,
	/* Pre-घड़ी generator भागide off */
	अणुVV6410_DATAFORMAT, BIT(7) | BIT(0)पूर्ण,

	अणुVV6410_CLKDIV,	VV6410_CLK_DIV_2पूर्ण,

	/* System रेजिस्टरs */
	/* Enable voltage द्विगुनr */
	अणुVV6410_AS0, BIT(6) | BIT(4) | BIT(3) | BIT(2) | BIT(1)पूर्ण,
	अणुVV6410_AT0, 0x00पूर्ण,
	/* Power up audio, dअगरferential */
	अणुVV6410_AT1, BIT(4) | BIT(0)पूर्ण,
पूर्ण;

#पूर्ण_अगर
