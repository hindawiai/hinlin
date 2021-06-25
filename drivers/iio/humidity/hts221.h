<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics hts221 sensor driver
 *
 * Copyright 2016 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi@st.com>
 */

#अगर_अघोषित HTS221_H
#घोषणा HTS221_H

#घोषणा HTS221_DEV_NAME		"hts221"

#समावेश <linux/iio/iपन.स>
#समावेश <linux/regulator/consumer.h>

क्रमागत hts221_sensor_type अणु
	HTS221_SENSOR_H,
	HTS221_SENSOR_T,
	HTS221_SENSOR_MAX,
पूर्ण;

काष्ठा hts221_sensor अणु
	u8 cur_avg_idx;
	पूर्णांक slope, b_gen;
पूर्ण;

काष्ठा hts221_hw अणु
	स्थिर अक्षर *name;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator *vdd;

	काष्ठा iio_trigger *trig;
	पूर्णांक irq;

	काष्ठा hts221_sensor sensors[HTS221_SENSOR_MAX];

	bool enabled;
	u8 odr;
	/* Ensure natural alignment of बारtamp */
	काष्ठा अणु
		__le16 channels[2];
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

बाह्य स्थिर काष्ठा dev_pm_ops hts221_pm_ops;

पूर्णांक hts221_probe(काष्ठा device *dev, पूर्णांक irq, स्थिर अक्षर *name,
		 काष्ठा regmap *regmap);
पूर्णांक hts221_set_enable(काष्ठा hts221_hw *hw, bool enable);
पूर्णांक hts221_allocate_buffers(काष्ठा iio_dev *iio_dev);
पूर्णांक hts221_allocate_trigger(काष्ठा iio_dev *iio_dev);

#पूर्ण_अगर /* HTS221_H */
