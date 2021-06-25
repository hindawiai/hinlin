<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम Vishay VCNL3020 proximity sensor on i2c bus.
 * Based on Vishay VCNL4000 driver code.
 *
 * TODO: पूर्णांकerrupts.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा VCNL3020_PROD_ID	0x21

#घोषणा VCNL_COMMAND		0x80 /* Command रेजिस्टर */
#घोषणा VCNL_PROD_REV		0x81 /* Product ID and Revision ID */
#घोषणा VCNL_PROXIMITY_RATE	0x82 /* Rate of Proximity Measurement */
#घोषणा VCNL_LED_CURRENT	0x83 /* IR LED current क्रम proximity mode */
#घोषणा VCNL_PS_RESULT_HI	0x87 /* Proximity result रेजिस्टर, MSB */
#घोषणा VCNL_PS_RESULT_LO	0x88 /* Proximity result रेजिस्टर, LSB */
#घोषणा VCNL_PS_ICR		0x89 /* Interrupt Control Register */
#घोषणा VCNL_PS_LO_THR_HI	0x8a /* High byte of low threshold value */
#घोषणा VCNL_PS_LO_THR_LO	0x8b /* Low byte of low threshold value */
#घोषणा VCNL_PS_HI_THR_HI	0x8c /* High byte of high threshold value */
#घोषणा VCNL_PS_HI_THR_LO	0x8d /* Low byte of high threshold value */
#घोषणा VCNL_ISR		0x8e /* Interrupt Status Register */
#घोषणा VCNL_PS_MOD_ADJ		0x8f /* Proximity Modulator Timing Adjusपंचांगent */

/* Bit masks क्रम COMMAND रेजिस्टर */
#घोषणा VCNL_PS_RDY		BIT(5) /* proximity data पढ़ोy? */
#घोषणा VCNL_PS_OD		BIT(3) /* start on-demand proximity
					* measurement
					*/

#घोषणा VCNL_ON_DEMAND_TIMEOUT_US	100000
#घोषणा VCNL_POLL_US			20000

अटल स्थिर पूर्णांक vcnl3020_prox_sampling_frequency[][2] = अणु
	अणु1, 950000पूर्ण,
	अणु3, 906250पूर्ण,
	अणु7, 812500पूर्ण,
	अणु16, 625000पूर्ण,
	अणु31, 250000पूर्ण,
	अणु62, 500000पूर्ण,
	अणु125, 0पूर्ण,
	अणु250, 0पूर्ण,
पूर्ण;

/**
 * काष्ठा vcnl3020_data - vcnl3020 specअगरic data.
 * @regmap:	device रेजिस्टर map.
 * @dev:	vcnl3020 device.
 * @rev:	revision id.
 * @lock:	lock क्रम protecting access to device hardware रेजिस्टरs.
 */
काष्ठा vcnl3020_data अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	u8 rev;
	काष्ठा mutex lock;
पूर्ण;

/**
 * काष्ठा vcnl3020_property - vcnl3020 property.
 * @name:	property name.
 * @reg:	i2c रेजिस्टर offset.
 * @conversion_func:	conversion function.
 */
काष्ठा vcnl3020_property अणु
	स्थिर अक्षर *name;
	u32 reg;
	u32 (*conversion_func)(u32 *val);
पूर्ण;

अटल u32 microamp_to_reg(u32 *val)
अणु
	/*
	 * An example of conversion from uA to reg val:
	 * 200000 uA == 200 mA == 20
	 */
	वापस *val /= 10000;
पूर्ण;

अटल काष्ठा vcnl3020_property vcnl3020_led_current_property = अणु
	.name = "vishay,led-current-microamp",
	.reg = VCNL_LED_CURRENT,
	.conversion_func = microamp_to_reg,
पूर्ण;

अटल पूर्णांक vcnl3020_get_and_apply_property(काष्ठा vcnl3020_data *data,
					   काष्ठा vcnl3020_property prop)
अणु
	पूर्णांक rc;
	u32 val;

	rc = device_property_पढ़ो_u32(data->dev, prop.name, &val);
	अगर (rc)
		वापस 0;

	अगर (prop.conversion_func)
		prop.conversion_func(&val);

	rc = regmap_ग_लिखो(data->regmap, prop.reg, val);
	अगर (rc) अणु
		dev_err(data->dev, "Error (%d) setting property (%s)\n",
			rc, prop.name);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक vcnl3020_init(काष्ठा vcnl3020_data *data)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक reg;

	rc = regmap_पढ़ो(data->regmap, VCNL_PROD_REV, &reg);
	अगर (rc) अणु
		dev_err(data->dev,
			"Error (%d) reading product revision\n", rc);
		वापस rc;
	पूर्ण

	अगर (reg != VCNL3020_PROD_ID) अणु
		dev_err(data->dev,
			"Product id (%x) did not match vcnl3020 (%x)\n", reg,
			VCNL3020_PROD_ID);
		वापस -ENODEV;
	पूर्ण

	data->rev = reg;
	mutex_init(&data->lock);

	वापस vcnl3020_get_and_apply_property(data,
					       vcnl3020_led_current_property);
पूर्ण;

अटल पूर्णांक vcnl3020_measure_proximity(काष्ठा vcnl3020_data *data, पूर्णांक *val)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक reg;
	__be16 res;

	mutex_lock(&data->lock);

	rc = regmap_ग_लिखो(data->regmap, VCNL_COMMAND, VCNL_PS_OD);
	अगर (rc)
		जाओ err_unlock;

	/* रुको क्रम data to become पढ़ोy */
	rc = regmap_पढ़ो_poll_समयout(data->regmap, VCNL_COMMAND, reg,
				      reg & VCNL_PS_RDY, VCNL_POLL_US,
				      VCNL_ON_DEMAND_TIMEOUT_US);
	अगर (rc) अणु
		dev_err(data->dev,
			"Error (%d) reading vcnl3020 command register\n", rc);
		जाओ err_unlock;
	पूर्ण

	/* high & low result bytes पढ़ो */
	rc = regmap_bulk_पढ़ो(data->regmap, VCNL_PS_RESULT_HI, &res,
			      माप(res));
	अगर (rc)
		जाओ err_unlock;

	*val = be16_to_cpu(res);

err_unlock:
	mutex_unlock(&data->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक vcnl3020_पढ़ो_proxy_samp_freq(काष्ठा vcnl3020_data *data, पूर्णांक *val,
					 पूर्णांक *val2)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक prox_rate;

	rc = regmap_पढ़ो(data->regmap, VCNL_PROXIMITY_RATE, &prox_rate);
	अगर (rc)
		वापस rc;

	अगर (prox_rate >= ARRAY_SIZE(vcnl3020_prox_sampling_frequency))
		वापस -EINVAL;

	*val = vcnl3020_prox_sampling_frequency[prox_rate][0];
	*val2 = vcnl3020_prox_sampling_frequency[prox_rate][1];

	वापस 0;
पूर्ण

अटल पूर्णांक vcnl3020_ग_लिखो_proxy_samp_freq(काष्ठा vcnl3020_data *data, पूर्णांक val,
					  पूर्णांक val2)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक index = -1;

	क्रम (i = 0; i < ARRAY_SIZE(vcnl3020_prox_sampling_frequency); i++) अणु
		अगर (val == vcnl3020_prox_sampling_frequency[i][0] &&
		    val2 == vcnl3020_prox_sampling_frequency[i][1]) अणु
			index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (index < 0)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(data->regmap, VCNL_PROXIMITY_RATE, index);
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec vcnl3020_channels[] = अणु
	अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.info_mask_separate_available = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
पूर्ण;

अटल पूर्णांक vcnl3020_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक rc;
	काष्ठा vcnl3020_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		rc = vcnl3020_measure_proximity(data, val);
		अगर (rc)
			वापस rc;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		rc = vcnl3020_पढ़ो_proxy_samp_freq(data, val, val2);
		अगर (rc < 0)
			वापस rc;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vcnl3020_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक rc;
	काष्ठा vcnl3020_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		rc = iio_device_claim_direct_mode(indio_dev);
		अगर (rc)
			वापस rc;
		rc = vcnl3020_ग_लिखो_proxy_samp_freq(data, val, val2);
		iio_device_release_direct_mode(indio_dev);
		वापस rc;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vcnl3020_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			       दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*vals = (पूर्णांक *)vcnl3020_prox_sampling_frequency;
		*type = IIO_VAL_INT_PLUS_MICRO;
		*length = 2 * ARRAY_SIZE(vcnl3020_prox_sampling_frequency);
		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info vcnl3020_info = अणु
	.पढ़ो_raw = vcnl3020_पढ़ो_raw,
	.ग_लिखो_raw = vcnl3020_ग_लिखो_raw,
	.पढ़ो_avail = vcnl3020_पढ़ो_avail,
पूर्ण;

अटल स्थिर काष्ठा regmap_config vcnl3020_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= VCNL_PS_MOD_ADJ,
पूर्ण;

अटल पूर्णांक vcnl3020_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा vcnl3020_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	पूर्णांक rc;

	regmap = devm_regmap_init_i2c(client, &vcnl3020_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "regmap_init failed\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->regmap = regmap;
	data->dev = &client->dev;

	rc = vcnl3020_init(data);
	अगर (rc)
		वापस rc;

	indio_dev->info = &vcnl3020_info;
	indio_dev->channels = vcnl3020_channels;
	indio_dev->num_channels = ARRAY_SIZE(vcnl3020_channels);
	indio_dev->name = "vcnl3020";
	indio_dev->modes = INDIO_सूचीECT_MODE;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id vcnl3020_of_match[] = अणु
	अणु
		.compatible = "vishay,vcnl3020",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vcnl3020_of_match);

अटल काष्ठा i2c_driver vcnl3020_driver = अणु
	.driver = अणु
		.name   = "vcnl3020",
		.of_match_table = vcnl3020_of_match,
	पूर्ण,
	.probe_new  = vcnl3020_probe,
पूर्ण;
module_i2c_driver(vcnl3020_driver);

MODULE_AUTHOR("Ivan Mikhaylov <i.mikhaylov@yadro.com>");
MODULE_DESCRIPTION("Vishay VCNL3020 proximity sensor driver");
MODULE_LICENSE("GPL");
