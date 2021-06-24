<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IIO DAC emulation driver using a digital potentiometer
 *
 * Copyright (C) 2016 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

/*
 * It is assumed that the dpot is used as a voltage भागider between the
 * current dpot wiper setting and the maximum resistance of the dpot. The
 * भागided voltage is provided by a vref regulator.
 *
 *                   .------.
 *    .-----------.  |      |
 *    | vref      |--'    .---.
 *    | regulator |--.    |   |
 *    '-----------'  |    | d |
 *                   |    | p |
 *                   |    | o |  wiper
 *                   |    | t |<---------+
 *                   |    |   |
 *                   |    '---'       dac output voltage
 *                   |      |
 *                   '------+------------+
 */

#समावेश <linux/err.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

काष्ठा dpot_dac अणु
	काष्ठा regulator *vref;
	काष्ठा iio_channel *dpot;
	u32 max_ohms;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec dpot_dac_iio_channel = अणु
	.type = IIO_VOLTAGE,
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW)
			    | BIT(IIO_CHAN_INFO_SCALE),
	.info_mask_separate_available = BIT(IIO_CHAN_INFO_RAW),
	.output = 1,
	.indexed = 1,
पूर्ण;

अटल पूर्णांक dpot_dac_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा dpot_dac *dac = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित दीर्घ दीर्घ पंचांगp;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस iio_पढ़ो_channel_raw(dac->dpot, val);

	हाल IIO_CHAN_INFO_SCALE:
		ret = iio_पढ़ो_channel_scale(dac->dpot, val, val2);
		चयन (ret) अणु
		हाल IIO_VAL_FRACTIONAL_LOG2:
			पंचांगp = *val * 1000000000LL;
			करो_भाग(पंचांगp, dac->max_ohms);
			पंचांगp *= regulator_get_voltage(dac->vref) / 1000;
			करो_भाग(पंचांगp, 1000000000LL);
			*val = पंचांगp;
			वापस ret;
		हाल IIO_VAL_INT:
			/*
			 * Convert पूर्णांकeger scale to fractional scale by
			 * setting the denominator (val2) to one...
			 */
			*val2 = 1;
			ret = IIO_VAL_FRACTIONAL;
			/* ...and fall through. Say it again क्रम GCC. */
			fallthrough;
		हाल IIO_VAL_FRACTIONAL:
			*val *= regulator_get_voltage(dac->vref) / 1000;
			*val2 *= dac->max_ohms;
			अवरोध;
		पूर्ण

		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dpot_dac_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			       दीर्घ mask)
अणु
	काष्ठा dpot_dac *dac = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*type = IIO_VAL_INT;
		वापस iio_पढ़ो_avail_channel_raw(dac->dpot, vals, length);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dpot_dac_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा dpot_dac *dac = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस iio_ग_लिखो_channel_raw(dac->dpot, val);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info dpot_dac_info = अणु
	.पढ़ो_raw = dpot_dac_पढ़ो_raw,
	.पढ़ो_avail = dpot_dac_पढ़ो_avail,
	.ग_लिखो_raw = dpot_dac_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक dpot_dac_channel_max_ohms(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा device *dev = &indio_dev->dev;
	काष्ठा dpot_dac *dac = iio_priv(indio_dev);
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	पूर्णांक ret;
	पूर्णांक val;
	पूर्णांक val2;
	पूर्णांक max;

	ret = iio_पढ़ो_max_channel_raw(dac->dpot, &max);
	अगर (ret < 0) अणु
		dev_err(dev, "dpot does not indicate its raw maximum value\n");
		वापस ret;
	पूर्ण

	चयन (iio_पढ़ो_channel_scale(dac->dpot, &val, &val2)) अणु
	हाल IIO_VAL_INT:
		वापस max * val;
	हाल IIO_VAL_FRACTIONAL:
		पंचांगp = (अचिन्हित दीर्घ दीर्घ)max * val;
		करो_भाग(पंचांगp, val2);
		वापस पंचांगp;
	हाल IIO_VAL_FRACTIONAL_LOG2:
		पंचांगp = val * 1000000000LL * max >> val2;
		करो_भाग(पंचांगp, 1000000000LL);
		वापस पंचांगp;
	शेष:
		dev_err(dev, "dpot has a scale that is too weird\n");
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dpot_dac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा dpot_dac *dac;
	क्रमागत iio_chan_type type;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*dac));
	अगर (!indio_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);
	dac = iio_priv(indio_dev);

	indio_dev->name = dev_name(dev);
	indio_dev->info = &dpot_dac_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = &dpot_dac_iio_channel;
	indio_dev->num_channels = 1;

	dac->vref = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(dac->vref))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(dac->vref),
				     "failed to get vref regulator\n");

	dac->dpot = devm_iio_channel_get(dev, "dpot");
	अगर (IS_ERR(dac->dpot))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(dac->dpot),
				     "failed to get dpot input channel\n");

	ret = iio_get_channel_type(dac->dpot, &type);
	अगर (ret < 0)
		वापस ret;

	अगर (type != IIO_RESISTANCE) अणु
		dev_err(dev, "dpot is of the wrong type\n");
		वापस -EINVAL;
	पूर्ण

	ret = dpot_dac_channel_max_ohms(indio_dev);
	अगर (ret < 0)
		वापस ret;
	dac->max_ohms = ret;

	ret = regulator_enable(dac->vref);
	अगर (ret) अणु
		dev_err(dev, "failed to enable the vref regulator\n");
		वापस ret;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "failed to register iio device\n");
		जाओ disable_reg;
	पूर्ण

	वापस 0;

disable_reg:
	regulator_disable(dac->vref);
	वापस ret;
पूर्ण

अटल पूर्णांक dpot_dac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा dpot_dac *dac = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(dac->vref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dpot_dac_match[] = अणु
	अणु .compatible = "dpot-dac" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dpot_dac_match);

अटल काष्ठा platक्रमm_driver dpot_dac_driver = अणु
	.probe = dpot_dac_probe,
	.हटाओ = dpot_dac_हटाओ,
	.driver = अणु
		.name = "iio-dpot-dac",
		.of_match_table = dpot_dac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dpot_dac_driver);

MODULE_DESCRIPTION("DAC emulation driver using a digital potentiometer");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL v2");
