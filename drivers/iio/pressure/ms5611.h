<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MS5611 pressure and temperature sensor driver
 *
 * Copyright (c) Tomasz Duszynski <tduszyns@gmail.com>
 *
 */

#अगर_अघोषित _MS5611_H
#घोषणा _MS5611_H

#समावेश <linux/device.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/mutex.h>

काष्ठा regulator;

#घोषणा MS5611_RESET			0x1e
#घोषणा MS5611_READ_ADC			0x00
#घोषणा MS5611_READ_PROM_WORD		0xA0
#घोषणा MS5611_PROM_WORDS_NB		8

क्रमागत अणु
	MS5611,
	MS5607,
पूर्ण;

काष्ठा ms5611_chip_info अणु
	u16 prom[MS5611_PROM_WORDS_NB];

	पूर्णांक (*temp_and_pressure_compensate)(काष्ठा ms5611_chip_info *chip_info,
					    s32 *temp, s32 *pressure);
पूर्ण;

/*
 * OverSampling Rate descriptor.
 * Warning: cmd MUST be kept aligned on a word boundary (see
 * m5611_spi_पढ़ो_adc_temp_and_pressure in ms5611_spi.c).
 */
काष्ठा ms5611_osr अणु
	अचिन्हित दीर्घ conv_usec;
	u8 cmd;
	अचिन्हित लघु rate;
पूर्ण;

काष्ठा ms5611_state अणु
	व्योम *client;
	काष्ठा mutex lock;

	स्थिर काष्ठा ms5611_osr *pressure_osr;
	स्थिर काष्ठा ms5611_osr *temp_osr;

	पूर्णांक (*reset)(काष्ठा device *dev);
	पूर्णांक (*पढ़ो_prom_word)(काष्ठा device *dev, पूर्णांक index, u16 *word);
	पूर्णांक (*पढ़ो_adc_temp_and_pressure)(काष्ठा device *dev,
					  s32 *temp, s32 *pressure);

	काष्ठा ms5611_chip_info *chip_info;
	काष्ठा regulator *vdd;
पूर्ण;

पूर्णांक ms5611_probe(काष्ठा iio_dev *indio_dev, काष्ठा device *dev,
		 स्थिर अक्षर *name, पूर्णांक type);
पूर्णांक ms5611_हटाओ(काष्ठा iio_dev *indio_dev);

#पूर्ण_अगर /* _MS5611_H */
