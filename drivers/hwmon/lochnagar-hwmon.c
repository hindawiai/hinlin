<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Lochnagar hardware monitoring features
 *
 * Copyright (c) 2016-2019 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 *
 * Author: Lucas Tanure <tanureal@खोलोsource.cirrus.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/math64.h>
#समावेश <linux/mfd/lochnagar.h>
#समावेश <linux/mfd/lochnagar2_regs.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा LN2_MAX_NSAMPLE 1023
#घोषणा LN2_SAMPLE_US   1670

#घोषणा LN2_CURR_UNITS  1000
#घोषणा LN2_VOLT_UNITS  1000
#घोषणा LN2_TEMP_UNITS  1000
#घोषणा LN2_PWR_UNITS   1000000

अटल स्थिर अक्षर * स्थिर lochnagar_chan_names[] = अणु
	"DBVDD1",
	"1V8 DSP",
	"1V8 CDC",
	"VDDCORE DSP",
	"AVDD 1V8",
	"SYSVDD",
	"VDDCORE CDC",
	"MICVDD",
पूर्ण;

काष्ठा lochnagar_hwmon अणु
	काष्ठा regmap *regmap;

	दीर्घ घातer_nsamples[ARRAY_SIZE(lochnagar_chan_names)];

	/* Lock to ensure only a single sensor is पढ़ो at a समय */
	काष्ठा mutex sensor_lock;
पूर्ण;

क्रमागत lochnagar_measure_mode अणु
	LN2_CURR = 0,
	LN2_VOLT,
	LN2_TEMP,
पूर्ण;

/**
 * भग्न_to_दीर्घ - Convert ieee754 पढ़ोing from hardware to an पूर्णांकeger
 *
 * @data: Value पढ़ो from the hardware
 * @precision: Units to multiply up to eg. 1000 = milli, 1000000 = micro
 *
 * Return: Converted पूर्णांकeger पढ़ोing
 *
 * Depending on the measurement type the hardware वापसs an ieee754
 * भग्नing poपूर्णांक value in either volts, amps or celsius. This function
 * will convert that पूर्णांकo an पूर्णांकeger in a smaller unit such as micro-amps
 * or milli-celsius. The hardware करोes not वापस NaN, so consideration of
 * that is not required.
 */
अटल दीर्घ भग्न_to_दीर्घ(u32 data, u32 precision)
अणु
	u64 man = data & 0x007FFFFF;
	पूर्णांक exp = ((data & 0x7F800000) >> 23) - 127 - 23;
	bool negative = data & 0x80000000;
	दीर्घ result;

	man = (man + (1 << 23)) * precision;

	अगर (fls64(man) + exp > (पूर्णांक)माप(दीर्घ) * 8 - 1)
		result = दीर्घ_उच्च;
	अन्यथा अगर (exp < 0)
		result = (man + (1ull << (-exp - 1))) >> -exp;
	अन्यथा
		result = man << exp;

	वापस negative ? -result : result;
पूर्ण

अटल पूर्णांक करो_measurement(काष्ठा regmap *regmap, पूर्णांक chan,
			  क्रमागत lochnagar_measure_mode mode, पूर्णांक nsamples)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	chan = 1 << (chan + LOCHNAGAR2_IMON_MEASURED_CHANNELS_SHIFT);

	ret = regmap_ग_लिखो(regmap, LOCHNAGAR2_IMON_CTRL1,
			   LOCHNAGAR2_IMON_ENA_MASK | chan | mode);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, LOCHNAGAR2_IMON_CTRL2, nsamples);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, LOCHNAGAR2_IMON_CTRL3,
			   LOCHNAGAR2_IMON_CONFIGURE_MASK);
	अगर (ret < 0)
		वापस ret;

	ret =  regmap_पढ़ो_poll_समयout(regmap, LOCHNAGAR2_IMON_CTRL3, val,
					val & LOCHNAGAR2_IMON_DONE_MASK,
					1000, 10000);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, LOCHNAGAR2_IMON_CTRL3,
			   LOCHNAGAR2_IMON_MEASURE_MASK);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Actual measurement समय is ~1.67mS per sample, approximate this
	 * with a 1.5mS per sample msleep and then poll क्रम success up to
	 * ~0.17mS * 1023 (LN2_MAX_NSAMPLES). Normally क्रम smaller values
	 * of nsamples the poll will complete on the first loop due to
	 * other latency in the प्रणाली.
	 */
	msleep((nsamples * 3) / 2);

	ret =  regmap_पढ़ो_poll_समयout(regmap, LOCHNAGAR2_IMON_CTRL3, val,
					val & LOCHNAGAR2_IMON_DONE_MASK,
					5000, 200000);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_ग_लिखो(regmap, LOCHNAGAR2_IMON_CTRL3, 0);
पूर्ण

अटल पूर्णांक request_data(काष्ठा regmap *regmap, पूर्णांक chan, u32 *data)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(regmap, LOCHNAGAR2_IMON_CTRL4,
			   LOCHNAGAR2_IMON_DATA_REQ_MASK |
			   chan << LOCHNAGAR2_IMON_CH_SEL_SHIFT);
	अगर (ret < 0)
		वापस ret;

	ret =  regmap_पढ़ो_poll_समयout(regmap, LOCHNAGAR2_IMON_CTRL4, val,
					val & LOCHNAGAR2_IMON_DATA_RDY_MASK,
					1000, 10000);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, LOCHNAGAR2_IMON_DATA1, &val);
	अगर (ret < 0)
		वापस ret;

	*data = val << 16;

	ret = regmap_पढ़ो(regmap, LOCHNAGAR2_IMON_DATA2, &val);
	अगर (ret < 0)
		वापस ret;

	*data |= val;

	वापस regmap_ग_लिखो(regmap, LOCHNAGAR2_IMON_CTRL4, 0);
पूर्ण

अटल पूर्णांक पढ़ो_sensor(काष्ठा device *dev, पूर्णांक chan,
		       क्रमागत lochnagar_measure_mode mode, पूर्णांक nsamples,
		       अचिन्हित पूर्णांक precision, दीर्घ *val)
अणु
	काष्ठा lochnagar_hwmon *priv = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = priv->regmap;
	u32 data;
	पूर्णांक ret;

	mutex_lock(&priv->sensor_lock);

	ret = करो_measurement(regmap, chan, mode, nsamples);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to perform measurement: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = request_data(regmap, chan, &data);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read measurement: %d\n", ret);
		जाओ error;
	पूर्ण

	*val = भग्न_to_दीर्घ(data, precision);

error:
	mutex_unlock(&priv->sensor_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_घातer(काष्ठा device *dev, पूर्णांक chan, दीर्घ *val)
अणु
	काष्ठा lochnagar_hwmon *priv = dev_get_drvdata(dev);
	पूर्णांक nsamples = priv->घातer_nsamples[chan];
	u64 घातer;
	पूर्णांक ret;

	अगर (!म_भेद("SYSVDD", lochnagar_chan_names[chan])) अणु
		घातer = 5 * LN2_PWR_UNITS;
	पूर्ण अन्यथा अणु
		ret = पढ़ो_sensor(dev, chan, LN2_VOLT, 1, LN2_PWR_UNITS, val);
		अगर (ret < 0)
			वापस ret;

		घातer = असल(*val);
	पूर्ण

	ret = पढ़ो_sensor(dev, chan, LN2_CURR, nsamples, LN2_PWR_UNITS, val);
	अगर (ret < 0)
		वापस ret;

	घातer *= असल(*val);
	घातer = DIV_ROUND_CLOSEST_ULL(घातer, LN2_PWR_UNITS);

	अगर (घातer > दीर्घ_उच्च)
		*val = दीर्घ_उच्च;
	अन्यथा
		*val = घातer;

	वापस 0;
पूर्ण

अटल umode_t lochnagar_is_visible(स्थिर व्योम *drvdata,
				    क्रमागत hwmon_sensor_types type,
				    u32 attr, पूर्णांक chan)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		अगर (!म_भेद("SYSVDD", lochnagar_chan_names[chan]))
			वापस 0;
		अवरोध;
	हाल hwmon_घातer:
		अगर (attr == hwmon_घातer_average_पूर्णांकerval)
			वापस 0644;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0444;
पूर्ण

अटल पूर्णांक lochnagar_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			  u32 attr, पूर्णांक chan, दीर्घ *val)
अणु
	काष्ठा lochnagar_hwmon *priv = dev_get_drvdata(dev);
	पूर्णांक पूर्णांकerval;

	चयन (type) अणु
	हाल hwmon_in:
		वापस पढ़ो_sensor(dev, chan, LN2_VOLT, 1, LN2_VOLT_UNITS, val);
	हाल hwmon_curr:
		वापस पढ़ो_sensor(dev, chan, LN2_CURR, 1, LN2_CURR_UNITS, val);
	हाल hwmon_temp:
		वापस पढ़ो_sensor(dev, chan, LN2_TEMP, 1, LN2_TEMP_UNITS, val);
	हाल hwmon_घातer:
		चयन (attr) अणु
		हाल hwmon_घातer_average:
			वापस पढ़ो_घातer(dev, chan, val);
		हाल hwmon_घातer_average_पूर्णांकerval:
			पूर्णांकerval = priv->घातer_nsamples[chan] * LN2_SAMPLE_US;
			*val = DIV_ROUND_CLOSEST(पूर्णांकerval, 1000);
			वापस 0;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lochnagar_पढ़ो_string(काष्ठा device *dev,
				 क्रमागत hwmon_sensor_types type, u32 attr,
				 पूर्णांक chan, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_in:
	हाल hwmon_curr:
	हाल hwmon_घातer:
		*str = lochnagar_chan_names[chan];
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lochnagar_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			   u32 attr, पूर्णांक chan, दीर्घ val)
अणु
	काष्ठा lochnagar_hwmon *priv = dev_get_drvdata(dev);

	अगर (type != hwmon_घातer || attr != hwmon_घातer_average_पूर्णांकerval)
		वापस -EOPNOTSUPP;

	val = clamp_t(दीर्घ, val, 1, (LN2_MAX_NSAMPLE * LN2_SAMPLE_US) / 1000);
	val = DIV_ROUND_CLOSEST(val * 1000, LN2_SAMPLE_US);

	priv->घातer_nsamples[chan] = val;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops lochnagar_ops = अणु
	.is_visible = lochnagar_is_visible,
	.पढ़ो = lochnagar_पढ़ो,
	.पढ़ो_string = lochnagar_पढ़ो_string,
	.ग_लिखो = lochnagar_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *lochnagar_info[] = अणु
	HWMON_CHANNEL_INFO(temp,  HWMON_T_INPUT),
	HWMON_CHANNEL_INFO(in,    HWMON_I_INPUT | HWMON_I_LABEL,
				  HWMON_I_INPUT | HWMON_I_LABEL,
				  HWMON_I_INPUT | HWMON_I_LABEL,
				  HWMON_I_INPUT | HWMON_I_LABEL,
				  HWMON_I_INPUT | HWMON_I_LABEL,
				  HWMON_I_INPUT | HWMON_I_LABEL,
				  HWMON_I_INPUT | HWMON_I_LABEL,
				  HWMON_I_INPUT | HWMON_I_LABEL),
	HWMON_CHANNEL_INFO(curr,  HWMON_C_INPUT | HWMON_C_LABEL,
				  HWMON_C_INPUT | HWMON_C_LABEL,
				  HWMON_C_INPUT | HWMON_C_LABEL,
				  HWMON_C_INPUT | HWMON_C_LABEL,
				  HWMON_C_INPUT | HWMON_C_LABEL,
				  HWMON_C_INPUT | HWMON_C_LABEL,
				  HWMON_C_INPUT | HWMON_C_LABEL,
				  HWMON_C_INPUT | HWMON_C_LABEL),
	HWMON_CHANNEL_INFO(घातer, HWMON_P_AVERAGE | HWMON_P_AVERAGE_INTERVAL |
				  HWMON_P_LABEL,
				  HWMON_P_AVERAGE | HWMON_P_AVERAGE_INTERVAL |
				  HWMON_P_LABEL,
				  HWMON_P_AVERAGE | HWMON_P_AVERAGE_INTERVAL |
				  HWMON_P_LABEL,
				  HWMON_P_AVERAGE | HWMON_P_AVERAGE_INTERVAL |
				  HWMON_P_LABEL,
				  HWMON_P_AVERAGE | HWMON_P_AVERAGE_INTERVAL |
				  HWMON_P_LABEL,
				  HWMON_P_AVERAGE | HWMON_P_AVERAGE_INTERVAL |
				  HWMON_P_LABEL,
				  HWMON_P_AVERAGE | HWMON_P_AVERAGE_INTERVAL |
				  HWMON_P_LABEL,
				  HWMON_P_AVERAGE | HWMON_P_AVERAGE_INTERVAL |
				  HWMON_P_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info lochnagar_chip_info = अणु
	.ops = &lochnagar_ops,
	.info = lochnagar_info,
पूर्ण;

अटल स्थिर काष्ठा of_device_id lochnagar_of_match[] = अणु
	अणु .compatible = "cirrus,lochnagar2-hwmon" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lochnagar_of_match);

अटल पूर्णांक lochnagar_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा lochnagar_hwmon *priv;
	पूर्णांक i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->sensor_lock);

	priv->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!priv->regmap) अणु
		dev_err(dev, "No register map found\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(priv->घातer_nsamples); i++)
		priv->घातer_nsamples[i] = 96;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, "Lochnagar", priv,
							 &lochnagar_chip_info,
							 शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver lochnagar_hwmon_driver = अणु
	.driver = अणु
		.name = "lochnagar-hwmon",
		.of_match_table = lochnagar_of_match,
	पूर्ण,
	.probe = lochnagar_hwmon_probe,
पूर्ण;
module_platक्रमm_driver(lochnagar_hwmon_driver);

MODULE_AUTHOR("Lucas Tanure <tanureal@opensource.cirrus.com>");
MODULE_DESCRIPTION("Lochnagar hardware monitoring features");
MODULE_LICENSE("GPL");
