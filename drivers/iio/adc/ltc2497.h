<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#घोषणा LTC2497_ENABLE			0xA0
#घोषणा LTC2497_CONFIG_DEFAULT		LTC2497_ENABLE
#घोषणा LTC2497_CONVERSION_TIME_MS	150ULL

काष्ठा ltc2497core_driverdata अणु
	काष्ठा regulator *ref;
	kसमय_प्रकार	समय_prev;
	u8 addr_prev;
	पूर्णांक (*result_and_measure)(काष्ठा ltc2497core_driverdata *ddata,
				  u8 address, पूर्णांक *val);
पूर्ण;

पूर्णांक ltc2497core_probe(काष्ठा device *dev, काष्ठा iio_dev *indio_dev);
व्योम ltc2497core_हटाओ(काष्ठा iio_dev *indio_dev);

MODULE_IMPORT_NS(LTC2497);
