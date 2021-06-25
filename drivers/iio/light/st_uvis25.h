<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics uvis25 sensor driver
 *
 * Copyright 2017 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#अगर_अघोषित ST_UVIS25_H
#घोषणा ST_UVIS25_H

#घोषणा ST_UVIS25_DEV_NAME		"uvis25"

#समावेश <linux/iio/iपन.स>

/**
 * काष्ठा st_uvis25_hw - ST UVIS25 sensor instance
 * @regmap: Register map of the device.
 * @trig: The trigger in use by the driver.
 * @enabled: Status of the sensor (false->off, true->on).
 * @irq: Device पूर्णांकerrupt line (I2C or SPI).
 */
काष्ठा st_uvis25_hw अणु
	काष्ठा regmap *regmap;

	काष्ठा iio_trigger *trig;
	bool enabled;
	पूर्णांक irq;
	/* Ensure बारtamp is naturally aligned */
	काष्ठा अणु
		u8 chan;
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

बाह्य स्थिर काष्ठा dev_pm_ops st_uvis25_pm_ops;

पूर्णांक st_uvis25_probe(काष्ठा device *dev, पूर्णांक irq, काष्ठा regmap *regmap);

#पूर्ण_अगर /* ST_UVIS25_H */
