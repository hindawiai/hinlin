<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2001 Jean-Fredric Clere, Nikolas Zimmermann, Georg Acher
 *		      Mark Cave-Ayland, Carlo E Prelz, Dick Streefland
 * Copyright (c) 2002, 2003 Tuukka Toivonen
 * Copyright (c) 2008 Erik Andrथऊn
 * Copyright (c) 2008 Chia-I Wu
 *
 * P/N 861037:      Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensor Photobit PB100  ASIC STV0600-1 - QuickCam Express
 * P/N 861055:      Sensor ST VV6410       ASIC STV0610   - LEGO cam
 * P/N 861075-0040: Sensor HDCS1000        ASIC
 * P/N 961179-0700: Sensor ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensor ST VV6410       ASIC STV0610   - QuickCam Web
 */

#अगर_अघोषित STV06XX_HDCS_H_
#घोषणा STV06XX_HDCS_H_

#समावेश "stv06xx_sensor.h"

#घोषणा HDCS_REG_CONFIG(sd)	(IS_1020(sd) ? HDCS20_CONFIG : HDCS00_CONFIG)
#घोषणा HDCS_REG_CONTROL(sd)	(IS_1020(sd) ? HDCS20_CONTROL : HDCS00_CONTROL)

#घोषणा HDCS_1X00_DEF_WIDTH	360
#घोषणा HDCS_1X00_DEF_HEIGHT	296

#घोषणा HDCS_1020_DEF_WIDTH	352
#घोषणा HDCS_1020_DEF_HEIGHT	292

#घोषणा HDCS_1020_BOTTOM_Y_SKIP	4

#घोषणा HDCS_CLK_FREQ_MHZ	25

#घोषणा HDCS_ADC_START_SIG_DUR	3

/* LSB bit of I2C or रेजिस्टर address signअगरies ग_लिखो (0) or पढ़ो (1) */
/* I2C Registers common क्रम both HDCS-1000/1100 and HDCS-1020 */
/* Identअगरications Register */
#घोषणा HDCS_IDENT		(0x00 << 1)
/* Status Register */
#घोषणा HDCS_STATUS		(0x01 << 1)
/* Interrupt Mask Register */
#घोषणा HDCS_IMASK		(0x02 << 1)
/* Pad Control Register */
#घोषणा HDCS_PCTRL		(0x03 << 1)
/* Pad Drive Control Register */
#घोषणा HDCS_PDRV		(0x04 << 1)
/* Interface Control Register */
#घोषणा HDCS_ICTRL		(0x05 << 1)
/* Interface Timing Register */
#घोषणा HDCS_ITMG		(0x06 << 1)
/* Baud Fraction Register */
#घोषणा HDCS_BFRAC		(0x07 << 1)
/* Baud Rate Register */
#घोषणा HDCS_BRATE		(0x08 << 1)
/* ADC Control Register */
#घोषणा HDCS_ADCCTRL		(0x09 << 1)
/* First Winकरोw Row Register */
#घोषणा HDCS_FWROW		(0x0a << 1)
/* First Winकरोw Column Register */
#घोषणा HDCS_FWCOL		(0x0b << 1)
/* Last Winकरोw Row Register */
#घोषणा HDCS_LWROW		(0x0c << 1)
/* Last Winकरोw Column Register */
#घोषणा HDCS_LWCOL		(0x0d << 1)
/* Timing Control Register */
#घोषणा HDCS_TCTRL		(0x0e << 1)
/* PGA Gain Register: Even Row, Even Column */
#घोषणा HDCS_ERECPGA		(0x0f << 1)
/* PGA Gain Register: Even Row, Odd Column */
#घोषणा HDCS_EROCPGA		(0x10 << 1)
/* PGA Gain Register: Odd Row, Even Column */
#घोषणा HDCS_ORECPGA		(0x11 << 1)
/* PGA Gain Register: Odd Row, Odd Column */
#घोषणा HDCS_OROCPGA		(0x12 << 1)
/* Row Exposure Low Register */
#घोषणा HDCS_ROWEXPL		(0x13 << 1)
/* Row Exposure High Register */
#घोषणा HDCS_ROWEXPH		(0x14 << 1)

/* I2C Registers only क्रम HDCS-1000/1100 */
/* Sub-Row Exposure Low Register */
#घोषणा HDCS00_SROWEXPL		(0x15 << 1)
/* Sub-Row Exposure High Register */
#घोषणा HDCS00_SROWEXPH		(0x16 << 1)
/* Configuration Register */
#घोषणा HDCS00_CONFIG		(0x17 << 1)
/* Control Register */
#घोषणा HDCS00_CONTROL		(0x18 << 1)

/* I2C Registers only क्रम HDCS-1020 */
/* Sub-Row Exposure Register */
#घोषणा HDCS20_SROWEXP		(0x15 << 1)
/* Error Control Register */
#घोषणा HDCS20_ERROR		(0x16 << 1)
/* Interface Timing 2 Register */
#घोषणा HDCS20_ITMG2		(0x17 << 1)
/* Interface Control 2 Register	*/
#घोषणा HDCS20_ICTRL2		(0x18 << 1)
/* Horizontal Blank Register */
#घोषणा HDCS20_HBLANK		(0x19 << 1)
/* Vertical Blank Register */
#घोषणा HDCS20_VBLANK		(0x1a << 1)
/* Configuration Register */
#घोषणा HDCS20_CONFIG		(0x1b << 1)
/* Control Register */
#घोषणा HDCS20_CONTROL		(0x1c << 1)

#घोषणा HDCS_RUN_ENABLE		(1 << 2)
#घोषणा HDCS_SLEEP_MODE		(1 << 1)

#घोषणा HDCS_DEFAULT_EXPOSURE	48
#घोषणा HDCS_DEFAULT_GAIN	50

अटल पूर्णांक hdcs_probe_1x00(काष्ठा sd *sd);
अटल पूर्णांक hdcs_probe_1020(काष्ठा sd *sd);
अटल पूर्णांक hdcs_start(काष्ठा sd *sd);
अटल पूर्णांक hdcs_init(काष्ठा sd *sd);
अटल पूर्णांक hdcs_init_controls(काष्ठा sd *sd);
अटल पूर्णांक hdcs_stop(काष्ठा sd *sd);
अटल पूर्णांक hdcs_dump(काष्ठा sd *sd);

अटल पूर्णांक hdcs_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val);
अटल पूर्णांक hdcs_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val);

स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_hdcs1x00 = अणु
	.name = "HP HDCS-1000/1100",
	.i2c_flush = 0,
	.i2c_addr = (0x55 << 1),
	.i2c_len = 1,

	/* FIXME (see अगर we can lower min_packet_size, needs testing, and also
	   adjusting framerate when the bandwidth माला_लो lower) */
	.min_packet_size = अणु 847 पूर्ण,
	.max_packet_size = अणु 847 पूर्ण,

	.init = hdcs_init,
	.init_controls = hdcs_init_controls,
	.probe = hdcs_probe_1x00,
	.start = hdcs_start,
	.stop = hdcs_stop,
	.dump = hdcs_dump,
पूर्ण;

स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_hdcs1020 = अणु
	.name = "HDCS-1020",
	.i2c_flush = 0,
	.i2c_addr = (0x55 << 1),
	.i2c_len = 1,

	/* FIXME (see अगर we can lower min_packet_size, needs testing, and also
	   adjusting framerate when the bandwidthm माला_लो lower) */
	.min_packet_size = अणु 847 पूर्ण,
	.max_packet_size = अणु 847 पूर्ण,

	.init = hdcs_init,
	.init_controls = hdcs_init_controls,
	.probe = hdcs_probe_1020,
	.start = hdcs_start,
	.stop = hdcs_stop,
	.dump = hdcs_dump,
पूर्ण;

अटल स्थिर u16 stv_bridge_init[][2] = अणु
	अणुSTV_ISO_ENABLE, 0पूर्ण,
	अणुSTV_REG23, 0पूर्ण,
	अणुSTV_REG00, 0x1dपूर्ण,
	अणुSTV_REG01, 0xb5पूर्ण,
	अणुSTV_REG02, 0xa8पूर्ण,
	अणुSTV_REG03, 0x95पूर्ण,
	अणुSTV_REG04, 0x07पूर्ण,

	अणुSTV_SCAN_RATE, 0x20पूर्ण,
	अणुSTV_Y_CTRL, 0x01पूर्ण,
	अणुSTV_X_CTRL, 0x0aपूर्ण
पूर्ण;

अटल स्थिर u8 stv_sensor_init[][2] = अणु
	/* Clear status (writing 1 will clear the corresponding status bit) */
	अणुHDCS_STATUS, BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1)पूर्ण,
	/* Disable all पूर्णांकerrupts */
	अणुHDCS_IMASK, 0x00पूर्ण,
	अणुHDCS_PCTRL, BIT(6) | BIT(5) | BIT(1) | BIT(0)पूर्ण,
	अणुHDCS_PDRV,  0x00पूर्ण,
	अणुHDCS_ICTRL, BIT(5)पूर्ण,
	अणुHDCS_ITMG,  BIT(4) | BIT(1)पूर्ण,
	/* ADC output resolution to 10 bits */
	अणुHDCS_ADCCTRL, 10पूर्ण
पूर्ण;

#पूर्ण_अगर
