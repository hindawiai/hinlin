<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics sensors platक्रमm-data driver
 *
 * Copyright 2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#अगर_अघोषित ST_SENSORS_PDATA_H
#घोषणा ST_SENSORS_PDATA_H

/**
 * काष्ठा st_sensors_platक्रमm_data - Platक्रमm data क्रम the ST sensors
 * @drdy_पूर्णांक_pin: Redirect DRDY on pin 1 (1) or pin 2 (2).
 *	Available only क्रम accelerometer and pressure sensors.
 *	Accelerometer DRDY on LSM330 available only on pin 1 (see datasheet).
 * @खोलो_drain: set the पूर्णांकerrupt line to be खोलो drain अगर possible.
 * @spi_3wire: enable spi-3wire mode.
 * @pullups: enable/disable i2c controller pullup resistors.
 * @wakeup_source: enable/disable device as wakeup generator.
 */
काष्ठा st_sensors_platक्रमm_data अणु
	u8 drdy_पूर्णांक_pin;
	bool खोलो_drain;
	bool spi_3wire;
	bool pullups;
	bool wakeup_source;
पूर्ण;

#पूर्ण_अगर /* ST_SENSORS_PDATA_H */
