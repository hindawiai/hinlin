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

#अगर_अघोषित STV06XX_H_
#घोषणा STV06XX_H_

#समावेश <linux/slab.h>
#समावेश "gspca.h"

#घोषणा MODULE_NAME "STV06xx"

#घोषणा STV_ISOC_ENDPOINT_ADDR		0x81

#घोषणा STV_R                           0x0509

#घोषणा STV_REG23			0x0423

/* Control रेजिस्टरs of the STV0600 ASIC */
#घोषणा STV_I2C_PARTNER			0x1420
#घोषणा STV_I2C_VAL_REG_VAL_PAIRS_MIN1	0x1421
#घोषणा STV_I2C_READ_WRITE_TOGGLE	0x1422
#घोषणा STV_I2C_FLUSH			0x1423
#घोषणा STV_I2C_SUCC_READ_REG_VALS	0x1424

#घोषणा STV_ISO_ENABLE			0x1440
#घोषणा STV_SCAN_RATE			0x1443
#घोषणा STV_LED_CTRL			0x1445
#घोषणा STV_STV0600_EMULATION		0x1446
#घोषणा STV_REG00			0x1500
#घोषणा STV_REG01			0x1501
#घोषणा STV_REG02			0x1502
#घोषणा STV_REG03			0x1503
#घोषणा STV_REG04			0x1504

#घोषणा STV_ISO_SIZE_L			0x15c1
#घोषणा STV_ISO_SIZE_H			0x15c2

/* Refers to the CIF 352x288 and QCIF 176x144 */
/* 1: 288 lines, 2: 144 lines */
#घोषणा STV_Y_CTRL			0x15c3

#घोषणा STV_RESET                       0x1620

/* 0xa: 352 columns, 0x6: 176 columns */
#घोषणा STV_X_CTRL			0x1680

#घोषणा STV06XX_URB_MSG_TIMEOUT		5000

#घोषणा I2C_MAX_BYTES			16
#घोषणा I2C_MAX_WORDS			8

#घोषणा I2C_BUFFER_LENGTH		0x23
#घोषणा I2C_READ_CMD			3
#घोषणा I2C_WRITE_CMD			1

#घोषणा LED_ON				1
#घोषणा LED_OFF				0

/* STV06xx device descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;

	/* A poपूर्णांकer to the currently connected sensor */
	स्थिर काष्ठा stv06xx_sensor *sensor;

	/* Sensor निजी data */
	व्योम *sensor_priv;

	/* The first 4 lines produced by the stv6422 are no good, this keeps
	   track of how many bytes we still need to skip during a frame */
	पूर्णांक to_skip;

	/* Bridge / Camera type */
	u8 bridge;
	#घोषणा BRIDGE_STV600 0
	#घोषणा BRIDGE_STV602 1
	#घोषणा BRIDGE_STV610 2
	#घोषणा BRIDGE_ST6422 3 /* With पूर्णांकegrated sensor */
पूर्ण;

पूर्णांक stv06xx_ग_लिखो_bridge(काष्ठा sd *sd, u16 address, u16 i2c_data);
पूर्णांक stv06xx_पढ़ो_bridge(काष्ठा sd *sd, u16 address, u8 *i2c_data);

पूर्णांक stv06xx_ग_लिखो_sensor_bytes(काष्ठा sd *sd, स्थिर u8 *data, u8 len);
पूर्णांक stv06xx_ग_लिखो_sensor_words(काष्ठा sd *sd, स्थिर u16 *data, u8 len);

पूर्णांक stv06xx_पढ़ो_sensor(काष्ठा sd *sd, स्थिर u8 address, u16 *value);
पूर्णांक stv06xx_ग_लिखो_sensor(काष्ठा sd *sd, u8 address, u16 value);

#पूर्ण_अगर
