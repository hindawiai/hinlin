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

#अगर_अघोषित STV06XX_SENSOR_H_
#घोषणा STV06XX_SENSOR_H_

#समावेश "stv06xx.h"

#घोषणा IS_1020(sd)	((sd)->sensor == &stv06xx_sensor_hdcs1020)

बाह्य स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_vv6410;
बाह्य स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_hdcs1x00;
बाह्य स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_hdcs1020;
बाह्य स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_pb0100;
बाह्य स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_st6422;

काष्ठा stv06xx_sensor अणु
	/* Defines the name of a sensor */
	अक्षर name[32];

	/* Sensor i2c address */
	u8 i2c_addr;

	/* Flush value*/
	u8 i2c_flush;

	/* length of an i2c word */
	u8 i2c_len;

	/* Isoc packet size (per mode) */
	पूर्णांक min_packet_size[4];
	पूर्णांक max_packet_size[4];

	/* Probes अगर the sensor is connected */
	पूर्णांक (*probe)(काष्ठा sd *sd);

	/* Perक्रमms a initialization sequence */
	पूर्णांक (*init)(काष्ठा sd *sd);

	/* Initializes the controls */
	पूर्णांक (*init_controls)(काष्ठा sd *sd);

	/* Reads a sensor रेजिस्टर */
	पूर्णांक (*पढ़ो_sensor)(काष्ठा sd *sd, स्थिर u8 address,
	      u8 *i2c_data, स्थिर u8 len);

	/* Writes to a sensor रेजिस्टर */
	पूर्णांक (*ग_लिखो_sensor)(काष्ठा sd *sd, स्थिर u8 address,
	      u8 *i2c_data, स्थिर u8 len);

	/* Inकाष्ठाs the sensor to start streaming */
	पूर्णांक (*start)(काष्ठा sd *sd);

	/* Inकाष्ठाs the sensor to stop streaming */
	पूर्णांक (*stop)(काष्ठा sd *sd);

	/* Inकाष्ठाs the sensor to dump all its contents */
	पूर्णांक (*dump)(काष्ठा sd *sd);
पूर्ण;

#पूर्ण_अगर
