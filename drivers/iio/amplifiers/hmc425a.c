<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * HMC425A and similar Gain Amplअगरiers
 *
 * Copyright 2020 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sysfs.h>

क्रमागत hmc425a_type अणु
	ID_HMC425A,
पूर्ण;

काष्ठा hmc425a_chip_info अणु
	स्थिर अक्षर			*name;
	स्थिर काष्ठा iio_chan_spec	*channels;
	अचिन्हित पूर्णांक			num_channels;
	अचिन्हित पूर्णांक			num_gpios;
	पूर्णांक				gain_min;
	पूर्णांक				gain_max;
	पूर्णांक				शेष_gain;
पूर्ण;

काष्ठा hmc425a_state अणु
	काष्ठा	regulator *reg;
	काष्ठा	mutex lock; /* protect sensor state */
	काष्ठा	hmc425a_chip_info *chip_info;
	काष्ठा	gpio_descs *gpios;
	क्रमागत	hmc425a_type type;
	u32	gain;
पूर्ण;

अटल पूर्णांक hmc425a_ग_लिखो(काष्ठा iio_dev *indio_dev, u32 value)
अणु
	काष्ठा hmc425a_state *st = iio_priv(indio_dev);
	DECLARE_BITMAP(values, BITS_PER_TYPE(value));

	values[0] = value;

	gpiod_set_array_value_cansleep(st->gpios->ndescs, st->gpios->desc,
				       शून्य, values);
	वापस 0;
पूर्ण

अटल पूर्णांक hmc425a_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा hmc425a_state *st = iio_priv(indio_dev);
	पूर्णांक code, gain = 0;
	पूर्णांक ret;

	mutex_lock(&st->lock);
	चयन (m) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		code = st->gain;

		चयन (st->type) अणु
		हाल ID_HMC425A:
			gain = ~code * -500;
			अवरोध;
		पूर्ण

		*val = gain / 1000;
		*val2 = (gain % 1000) * 1000;

		ret = IIO_VAL_INT_PLUS_MICRO_DB;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण;

अटल पूर्णांक hmc425a_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			     पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा hmc425a_state *st = iio_priv(indio_dev);
	काष्ठा hmc425a_chip_info *inf = st->chip_info;
	पूर्णांक code = 0, gain;
	पूर्णांक ret;

	अगर (val < 0)
		gain = (val * 1000) - (val2 / 1000);
	अन्यथा
		gain = (val * 1000) + (val2 / 1000);

	अगर (gain > inf->gain_max || gain < inf->gain_min)
		वापस -EINVAL;

	चयन (st->type) अणु
	हाल ID_HMC425A:
		code = ~((असल(gain) / 500) & 0x3F);
		अवरोध;
	पूर्ण

	mutex_lock(&st->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		st->gain = code;

		ret = hmc425a_ग_लिखो(indio_dev, st->gain);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hmc425a_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *chan,
				     दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		वापस IIO_VAL_INT_PLUS_MICRO_DB;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info hmc425a_info = अणु
	.पढ़ो_raw = &hmc425a_पढ़ो_raw,
	.ग_लिखो_raw = &hmc425a_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = &hmc425a_ग_लिखो_raw_get_fmt,
पूर्ण;

#घोषणा HMC425A_CHAN(_channel)						\
अणु									\
	.type = IIO_VOLTAGE,						\
	.output = 1,							\
	.indexed = 1,							\
	.channel = _channel,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_HARDWAREGAIN),		\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec hmc425a_channels[] = अणु
	HMC425A_CHAN(0),
पूर्ण;

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id hmc425a_of_match[] = अणु
	अणु .compatible = "adi,hmc425a", .data = (व्योम *)ID_HMC425A पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hmc425a_of_match);

अटल व्योम hmc425a_reg_disable(व्योम *data)
अणु
	काष्ठा hmc425a_state *st = data;

	regulator_disable(st->reg);
पूर्ण

अटल काष्ठा hmc425a_chip_info hmc425a_chip_info_tbl[] = अणु
	[ID_HMC425A] = अणु
		.name = "hmc425a",
		.channels = hmc425a_channels,
		.num_channels = ARRAY_SIZE(hmc425a_channels),
		.num_gpios = 6,
		.gain_min = -31500,
		.gain_max = 0,
		.शेष_gain = -0x40, /* set शेष gain -31.5db*/
	पूर्ण,
पूर्ण;

अटल पूर्णांक hmc425a_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा hmc425a_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	st->type = (क्रमागत hmc425a_type)of_device_get_match_data(&pdev->dev);

	st->chip_info = &hmc425a_chip_info_tbl[st->type];
	indio_dev->num_channels = st->chip_info->num_channels;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->name = st->chip_info->name;
	st->gain = st->chip_info->शेष_gain;

	st->gpios = devm_gpiod_get_array(&pdev->dev, "ctrl", GPIOD_OUT_LOW);
	अगर (IS_ERR(st->gpios))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(st->gpios),
				     "failed to get gpios\n");

	अगर (st->gpios->ndescs != st->chip_info->num_gpios) अणु
		dev_err(&pdev->dev, "%d GPIOs needed to operate\n",
			st->chip_info->num_gpios);
		वापस -ENODEV;
	पूर्ण

	st->reg = devm_regulator_get(&pdev->dev, "vcc-supply");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	अगर (ret)
		वापस ret;
	ret = devm_add_action_or_reset(&pdev->dev, hmc425a_reg_disable, st);
	अगर (ret)
		वापस ret;

	mutex_init(&st->lock);

	indio_dev->info = &hmc425a_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	वापस devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver hmc425a_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = hmc425a_of_match,
	पूर्ण,
	.probe = hmc425a_probe,
पूर्ण;
module_platक्रमm_driver(hmc425a_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices HMC425A and similar GPIO control Gain Amplifiers");
MODULE_LICENSE("GPL v2");
