<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IIO rescale driver
 *
 * Copyright (C) 2018 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

#समावेश <linux/err.h>
#समावेश <linux/gcd.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

काष्ठा rescale;

काष्ठा rescale_cfg अणु
	क्रमागत iio_chan_type type;
	पूर्णांक (*props)(काष्ठा device *dev, काष्ठा rescale *rescale);
पूर्ण;

काष्ठा rescale अणु
	स्थिर काष्ठा rescale_cfg *cfg;
	काष्ठा iio_channel *source;
	काष्ठा iio_chan_spec chan;
	काष्ठा iio_chan_spec_ext_info *ext_info;
	s32 numerator;
	s32 denominator;
पूर्ण;

अटल पूर्णांक rescale_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा rescale *rescale = iio_priv(indio_dev);
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस iio_पढ़ो_channel_raw(rescale->source, val);

	हाल IIO_CHAN_INFO_SCALE:
		ret = iio_पढ़ो_channel_scale(rescale->source, val, val2);
		चयन (ret) अणु
		हाल IIO_VAL_FRACTIONAL:
			*val *= rescale->numerator;
			*val2 *= rescale->denominator;
			वापस ret;
		हाल IIO_VAL_INT:
			*val *= rescale->numerator;
			अगर (rescale->denominator == 1)
				वापस ret;
			*val2 = rescale->denominator;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_VAL_FRACTIONAL_LOG2:
			पंचांगp = *val * 1000000000LL;
			करो_भाग(पंचांगp, rescale->denominator);
			पंचांगp *= rescale->numerator;
			करो_भाग(पंचांगp, 1000000000LL);
			*val = पंचांगp;
			वापस ret;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक rescale_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			      दीर्घ mask)
अणु
	काष्ठा rescale *rescale = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*type = IIO_VAL_INT;
		वापस iio_पढ़ो_avail_channel_raw(rescale->source,
						  vals, length);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info rescale_info = अणु
	.पढ़ो_raw = rescale_पढ़ो_raw,
	.पढ़ो_avail = rescale_पढ़ो_avail,
पूर्ण;

अटल sमाप_प्रकार rescale_पढ़ो_ext_info(काष्ठा iio_dev *indio_dev,
				     uपूर्णांकptr_t निजी,
				     काष्ठा iio_chan_spec स्थिर *chan,
				     अक्षर *buf)
अणु
	काष्ठा rescale *rescale = iio_priv(indio_dev);

	वापस iio_पढ़ो_channel_ext_info(rescale->source,
					 rescale->ext_info[निजी].name,
					 buf);
पूर्ण

अटल sमाप_प्रकार rescale_ग_लिखो_ext_info(काष्ठा iio_dev *indio_dev,
				      uपूर्णांकptr_t निजी,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा rescale *rescale = iio_priv(indio_dev);

	वापस iio_ग_लिखो_channel_ext_info(rescale->source,
					  rescale->ext_info[निजी].name,
					  buf, len);
पूर्ण

अटल पूर्णांक rescale_configure_channel(काष्ठा device *dev,
				     काष्ठा rescale *rescale)
अणु
	काष्ठा iio_chan_spec *chan = &rescale->chan;
	काष्ठा iio_chan_spec स्थिर *schan = rescale->source->channel;

	chan->indexed = 1;
	chan->output = schan->output;
	chan->ext_info = rescale->ext_info;
	chan->type = rescale->cfg->type;

	अगर (!iio_channel_has_info(schan, IIO_CHAN_INFO_RAW) ||
	    !iio_channel_has_info(schan, IIO_CHAN_INFO_SCALE)) अणु
		dev_err(dev, "source channel does not support raw/scale\n");
		वापस -EINVAL;
	पूर्ण

	chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_SCALE);

	अगर (iio_channel_has_available(schan, IIO_CHAN_INFO_RAW))
		chan->info_mask_separate_available |= BIT(IIO_CHAN_INFO_RAW);

	वापस 0;
पूर्ण

अटल पूर्णांक rescale_current_sense_amplअगरier_props(काष्ठा device *dev,
						 काष्ठा rescale *rescale)
अणु
	u32 sense;
	u32 gain_mult = 1;
	u32 gain_भाग = 1;
	u32 factor;
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, "sense-resistor-micro-ohms",
				       &sense);
	अगर (ret) अणु
		dev_err(dev, "failed to read the sense resistance: %d\n", ret);
		वापस ret;
	पूर्ण

	device_property_पढ़ो_u32(dev, "sense-gain-mult", &gain_mult);
	device_property_पढ़ो_u32(dev, "sense-gain-div", &gain_भाग);

	/*
	 * Calculate the scaling factor, 1 / (gain * sense), or
	 * gain_भाग / (gain_mult * sense), जबतक trying to keep the
	 * numerator/denominator from overflowing.
	 */
	factor = gcd(sense, 1000000);
	rescale->numerator = 1000000 / factor;
	rescale->denominator = sense / factor;

	factor = gcd(rescale->numerator, gain_mult);
	rescale->numerator /= factor;
	rescale->denominator *= gain_mult / factor;

	factor = gcd(rescale->denominator, gain_भाग);
	rescale->numerator *= gain_भाग / factor;
	rescale->denominator /= factor;

	वापस 0;
पूर्ण

अटल पूर्णांक rescale_current_sense_shunt_props(काष्ठा device *dev,
					     काष्ठा rescale *rescale)
अणु
	u32 shunt;
	u32 factor;
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, "shunt-resistor-micro-ohms",
				       &shunt);
	अगर (ret) अणु
		dev_err(dev, "failed to read the shunt resistance: %d\n", ret);
		वापस ret;
	पूर्ण

	factor = gcd(shunt, 1000000);
	rescale->numerator = 1000000 / factor;
	rescale->denominator = shunt / factor;

	वापस 0;
पूर्ण

अटल पूर्णांक rescale_voltage_भागider_props(काष्ठा device *dev,
					 काष्ठा rescale *rescale)
अणु
	पूर्णांक ret;
	u32 factor;

	ret = device_property_पढ़ो_u32(dev, "output-ohms",
				       &rescale->denominator);
	अगर (ret) अणु
		dev_err(dev, "failed to read output-ohms: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "full-ohms",
				       &rescale->numerator);
	अगर (ret) अणु
		dev_err(dev, "failed to read full-ohms: %d\n", ret);
		वापस ret;
	पूर्ण

	factor = gcd(rescale->numerator, rescale->denominator);
	rescale->numerator /= factor;
	rescale->denominator /= factor;

	वापस 0;
पूर्ण

क्रमागत rescale_variant अणु
	CURRENT_SENSE_AMPLIFIER,
	CURRENT_SENSE_SHUNT,
	VOLTAGE_DIVIDER,
पूर्ण;

अटल स्थिर काष्ठा rescale_cfg rescale_cfg[] = अणु
	[CURRENT_SENSE_AMPLIFIER] = अणु
		.type = IIO_CURRENT,
		.props = rescale_current_sense_amplअगरier_props,
	पूर्ण,
	[CURRENT_SENSE_SHUNT] = अणु
		.type = IIO_CURRENT,
		.props = rescale_current_sense_shunt_props,
	पूर्ण,
	[VOLTAGE_DIVIDER] = अणु
		.type = IIO_VOLTAGE,
		.props = rescale_voltage_भागider_props,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rescale_match[] = अणु
	अणु .compatible = "current-sense-amplifier",
	  .data = &rescale_cfg[CURRENT_SENSE_AMPLIFIER], पूर्ण,
	अणु .compatible = "current-sense-shunt",
	  .data = &rescale_cfg[CURRENT_SENSE_SHUNT], पूर्ण,
	अणु .compatible = "voltage-divider",
	  .data = &rescale_cfg[VOLTAGE_DIVIDER], पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rescale_match);

अटल पूर्णांक rescale_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा iio_channel *source;
	काष्ठा rescale *rescale;
	पूर्णांक माप_ext_info;
	पूर्णांक माप_priv;
	पूर्णांक i;
	पूर्णांक ret;

	source = devm_iio_channel_get(dev, शून्य);
	अगर (IS_ERR(source))
		वापस dev_err_probe(dev, PTR_ERR(source),
				     "failed to get source channel\n");

	माप_ext_info = iio_get_channel_ext_info_count(source);
	अगर (माप_ext_info) अणु
		माप_ext_info += 1; /* one extra entry क्रम the sentinel */
		माप_ext_info *= माप(*rescale->ext_info);
	पूर्ण

	माप_priv = माप(*rescale) + माप_ext_info;

	indio_dev = devm_iio_device_alloc(dev, माप_priv);
	अगर (!indio_dev)
		वापस -ENOMEM;

	rescale = iio_priv(indio_dev);

	rescale->cfg = of_device_get_match_data(dev);
	rescale->numerator = 1;
	rescale->denominator = 1;

	ret = rescale->cfg->props(dev, rescale);
	अगर (ret)
		वापस ret;

	अगर (!rescale->numerator || !rescale->denominator) अणु
		dev_err(dev, "invalid scaling factor.\n");
		वापस -EINVAL;
	पूर्ण

	platक्रमm_set_drvdata(pdev, indio_dev);

	rescale->source = source;

	indio_dev->name = dev_name(dev);
	indio_dev->info = &rescale_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = &rescale->chan;
	indio_dev->num_channels = 1;
	अगर (माप_ext_info) अणु
		rescale->ext_info = devm_kmemdup(dev,
						 source->channel->ext_info,
						 माप_ext_info, GFP_KERNEL);
		अगर (!rescale->ext_info)
			वापस -ENOMEM;

		क्रम (i = 0; rescale->ext_info[i].name; ++i) अणु
			काष्ठा iio_chan_spec_ext_info *ext_info =
				&rescale->ext_info[i];

			अगर (source->channel->ext_info[i].पढ़ो)
				ext_info->पढ़ो = rescale_पढ़ो_ext_info;
			अगर (source->channel->ext_info[i].ग_लिखो)
				ext_info->ग_लिखो = rescale_ग_लिखो_ext_info;
			ext_info->निजी = i;
		पूर्ण
	पूर्ण

	ret = rescale_configure_channel(dev, rescale);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver rescale_driver = अणु
	.probe = rescale_probe,
	.driver = अणु
		.name = "iio-rescale",
		.of_match_table = rescale_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rescale_driver);

MODULE_DESCRIPTION("IIO rescale driver");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL v2");
