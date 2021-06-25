<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic sigma delta modulator driver
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author: Arnaud Pouliquen <arnaud.pouliquen@st.com>.
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

अटल स्थिर काष्ठा iio_info iio_sd_mod_iio_info;

अटल स्थिर काष्ठा iio_chan_spec iio_sd_mod_ch = अणु
	.type = IIO_VOLTAGE,
	.indexed = 1,
	.scan_type = अणु
		.sign = 'u',
		.realbits = 1,
		.shअगरt = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक iio_sd_mod_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *iio;

	iio = devm_iio_device_alloc(dev, 0);
	अगर (!iio)
		वापस -ENOMEM;

	iio->name = dev_name(dev);
	iio->info = &iio_sd_mod_iio_info;
	iio->modes = INDIO_BUFFER_HARDWARE;

	iio->num_channels = 1;
	iio->channels = &iio_sd_mod_ch;

	platक्रमm_set_drvdata(pdev, iio);

	वापस devm_iio_device_रेजिस्टर(&pdev->dev, iio);
पूर्ण

अटल स्थिर काष्ठा of_device_id sd_adc_of_match[] = अणु
	अणु .compatible = "sd-modulator" पूर्ण,
	अणु .compatible = "ads1201" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sd_adc_of_match);

अटल काष्ठा platक्रमm_driver iio_sd_mod_adc = अणु
	.driver = अणु
		.name = "iio_sd_adc_mod",
		.of_match_table = sd_adc_of_match,
	पूर्ण,
	.probe = iio_sd_mod_probe,
पूर्ण;

module_platक्रमm_driver(iio_sd_mod_adc);

MODULE_DESCRIPTION("Basic sigma delta modulator");
MODULE_AUTHOR("Arnaud Pouliquen <arnaud.pouliquen@st.com>");
MODULE_LICENSE("GPL v2");
