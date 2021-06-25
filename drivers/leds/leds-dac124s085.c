<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2008
 * Guennadi Liakhovetski, DENX Software Engineering, <lg@denx.de>
 *
 * LED driver क्रम the DAC124S085 SPI DAC
 */

#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

काष्ठा dac124s085_led अणु
	काष्ठा led_classdev	ldev;
	काष्ठा spi_device	*spi;
	पूर्णांक			id;
	अक्षर			name[माप("dac124s085-3")];

	काष्ठा mutex		mutex;
पूर्ण;

काष्ठा dac124s085 अणु
	काष्ठा dac124s085_led leds[4];
पूर्ण;

#घोषणा REG_WRITE		(0 << 12)
#घोषणा REG_WRITE_UPDATE	(1 << 12)
#घोषणा ALL_WRITE_UPDATE	(2 << 12)
#घोषणा POWER_DOWN_OUTPUT	(3 << 12)

अटल पूर्णांक dac124s085_set_brightness(काष्ठा led_classdev *ldev,
				      क्रमागत led_brightness brightness)
अणु
	काष्ठा dac124s085_led *led = container_of(ldev, काष्ठा dac124s085_led,
						  ldev);
	u16 word;
	पूर्णांक ret;

	mutex_lock(&led->mutex);
	word = cpu_to_le16(((led->id) << 14) | REG_WRITE_UPDATE |
			   (brightness & 0xfff));
	ret = spi_ग_लिखो(led->spi, (स्थिर u8 *)&word, माप(word));
	mutex_unlock(&led->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक dac124s085_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा dac124s085	*dac;
	काष्ठा dac124s085_led	*led;
	पूर्णांक i, ret;

	dac = devm_kzalloc(&spi->dev, माप(*dac), GFP_KERNEL);
	अगर (!dac)
		वापस -ENOMEM;

	spi->bits_per_word = 16;

	क्रम (i = 0; i < ARRAY_SIZE(dac->leds); i++) अणु
		led		= dac->leds + i;
		led->id		= i;
		led->spi	= spi;
		snम_लिखो(led->name, माप(led->name), "dac124s085-%d", i);
		mutex_init(&led->mutex);
		led->ldev.name = led->name;
		led->ldev.brightness = LED_OFF;
		led->ldev.max_brightness = 0xfff;
		led->ldev.brightness_set_blocking = dac124s085_set_brightness;
		ret = led_classdev_रेजिस्टर(&spi->dev, &led->ldev);
		अगर (ret < 0)
			जाओ eledcr;
	पूर्ण

	spi_set_drvdata(spi, dac);

	वापस 0;

eledcr:
	जबतक (i--)
		led_classdev_unरेजिस्टर(&dac->leds[i].ldev);

	वापस ret;
पूर्ण

अटल पूर्णांक dac124s085_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा dac124s085	*dac = spi_get_drvdata(spi);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dac->leds); i++)
		led_classdev_unरेजिस्टर(&dac->leds[i].ldev);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver dac124s085_driver = अणु
	.probe		= dac124s085_probe,
	.हटाओ		= dac124s085_हटाओ,
	.driver = अणु
		.name	= "dac124s085",
	पूर्ण,
पूर्ण;

module_spi_driver(dac124s085_driver);

MODULE_AUTHOR("Guennadi Liakhovetski <lg@denx.de>");
MODULE_DESCRIPTION("DAC124S085 LED driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:dac124s085");
