<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BMI160_H_
#घोषणा BMI160_H_

#समावेश <linux/iio/iपन.स>
#समावेश <linux/regulator/consumer.h>

काष्ठा bmi160_data अणु
	काष्ठा regmap *regmap;
	काष्ठा iio_trigger *trig;
	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा iio_mount_matrix orientation;
	/*
	 * Ensure natural alignment क्रम बारtamp अगर present.
	 * Max length needed: 2 * 3 channels + 4 bytes padding + 8 byte ts.
	 * If fewer channels are enabled, less space may be needed, as
	 * दीर्घ as the बारtamp is still aligned to 8 bytes.
	 */
	__le16 buf[12] __aligned(8);
पूर्ण;

बाह्य स्थिर काष्ठा regmap_config bmi160_regmap_config;

पूर्णांक bmi160_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		      स्थिर अक्षर *name, bool use_spi);

पूर्णांक bmi160_enable_irq(काष्ठा regmap *regmap, bool enable);

पूर्णांक bmi160_probe_trigger(काष्ठा iio_dev *indio_dev, पूर्णांक irq, u32 irq_type);

#पूर्ण_अगर  /* BMI160_H_ */
