<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * AD7091RX Analog to Digital converter driver
 *
 * Copyright 2014-2019 Analog Devices Inc.
 */

#अगर_अघोषित __DRIVERS_IIO_ADC_AD7091R_BASE_H__
#घोषणा __DRIVERS_IIO_ADC_AD7091R_BASE_H__

काष्ठा device;
काष्ठा ad7091r_state;

काष्ठा ad7091r_chip_info अणु
	अचिन्हित पूर्णांक num_channels;
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक vref_mV;
पूर्ण;

बाह्य स्थिर काष्ठा regmap_config ad7091r_regmap_config;

पूर्णांक ad7091r_probe(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर काष्ठा ad7091r_chip_info *chip_info,
		काष्ठा regmap *map, पूर्णांक irq);

#पूर्ण_अगर /* __DRIVERS_IIO_ADC_AD7091R_BASE_H__ */
