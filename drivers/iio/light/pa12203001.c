<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Driver क्रम TXC PA12203001 Proximity and Ambient Light Sensor.
 *
 * To करो: Interrupt support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#घोषणा PA12203001_DRIVER_NAME	"pa12203001"

#घोषणा PA12203001_REG_CFG0		0x00
#घोषणा PA12203001_REG_CFG1		0x01
#घोषणा PA12203001_REG_CFG2		0x02
#घोषणा PA12203001_REG_CFG3		0x03

#घोषणा PA12203001_REG_ADL		0x0b
#घोषणा PA12203001_REG_PDH		0x0e

#घोषणा PA12203001_REG_POFS		0x10
#घोषणा PA12203001_REG_PSET		0x11

#घोषणा PA12203001_ALS_EN_MASK		BIT(0)
#घोषणा PA12203001_PX_EN_MASK		BIT(1)
#घोषणा PA12203001_PX_NORMAL_MODE_MASK		GENMASK(7, 6)
#घोषणा PA12203001_AFSR_MASK		GENMASK(5, 4)
#घोषणा PA12203001_AFSR_SHIFT		4

#घोषणा PA12203001_PSCAN			0x03

/* als range 31000, ps, als disabled */
#घोषणा PA12203001_REG_CFG0_DEFAULT		0x30

/* led current: 100 mA */
#घोषणा PA12203001_REG_CFG1_DEFAULT		0x20

/* ps mode: normal, पूर्णांकerrupts not active */
#घोषणा PA12203001_REG_CFG2_DEFAULT		0xcc

#घोषणा PA12203001_REG_CFG3_DEFAULT		0x00

#घोषणा PA12203001_SLEEP_DELAY_MS		3000

#घोषणा PA12203001_CHIP_ENABLE		0xff
#घोषणा PA12203001_CHIP_DISABLE		0x00

/* available scales: corresponding to [500, 4000, 7000, 31000]  lux */
अटल स्थिर पूर्णांक pa12203001_scales[] = अणु 7629, 61036, 106813, 473029पूर्ण;

काष्ठा pa12203001_data अणु
	काष्ठा i2c_client *client;

	/* protect device states */
	काष्ठा mutex lock;

	bool als_enabled;
	bool px_enabled;
	bool als_needs_enable;
	bool px_needs_enable;

	काष्ठा regmap *map;
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8 reg;
	u8 val;
पूर्ण regvals[] = अणु
	अणुPA12203001_REG_CFG0, PA12203001_REG_CFG0_DEFAULTपूर्ण,
	अणुPA12203001_REG_CFG1, PA12203001_REG_CFG1_DEFAULTपूर्ण,
	अणुPA12203001_REG_CFG2, PA12203001_REG_CFG2_DEFAULTपूर्ण,
	अणुPA12203001_REG_CFG3, PA12203001_REG_CFG3_DEFAULTपूर्ण,
	अणुPA12203001_REG_PSET, PA12203001_PSCANपूर्ण,
पूर्ण;

अटल IIO_CONST_ATTR(in_illuminance_scale_available,
		      "0.007629 0.061036 0.106813 0.473029");

अटल काष्ठा attribute *pa12203001_attrs[] = अणु
	&iio_स्थिर_attr_in_illuminance_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pa12203001_attr_group = अणु
	.attrs = pa12203001_attrs,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec pa12203001_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_range pa12203001_अस्थिर_regs_ranges[] = अणु
	regmap_reg_range(PA12203001_REG_ADL, PA12203001_REG_ADL + 1),
	regmap_reg_range(PA12203001_REG_PDH, PA12203001_REG_PDH),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table pa12203001_अस्थिर_regs = अणु
	.yes_ranges = pa12203001_अस्थिर_regs_ranges,
	.n_yes_ranges = ARRAY_SIZE(pa12203001_अस्थिर_regs_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config pa12203001_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = PA12203001_REG_PSET,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_table = &pa12203001_अस्थिर_regs,
पूर्ण;

अटल अंतरभूत पूर्णांक pa12203001_als_enable(काष्ठा pa12203001_data *data, u8 enable)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->map, PA12203001_REG_CFG0,
				 PA12203001_ALS_EN_MASK, enable);
	अगर (ret < 0)
		वापस ret;

	data->als_enabled = !!enable;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pa12203001_px_enable(काष्ठा pa12203001_data *data, u8 enable)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->map, PA12203001_REG_CFG0,
				 PA12203001_PX_EN_MASK, enable);
	अगर (ret < 0)
		वापस ret;

	data->px_enabled = !!enable;

	वापस 0;
पूर्ण

अटल पूर्णांक pa12203001_set_घातer_state(काष्ठा pa12203001_data *data, bool on,
				      u8 mask)
अणु
#अगर_घोषित CONFIG_PM
	पूर्णांक ret;

	अगर (on && (mask & PA12203001_ALS_EN_MASK)) अणु
		mutex_lock(&data->lock);
		अगर (data->px_enabled) अणु
			ret = pa12203001_als_enable(data,
						    PA12203001_ALS_EN_MASK);
			अगर (ret < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			data->als_needs_enable = true;
		पूर्ण
		mutex_unlock(&data->lock);
	पूर्ण

	अगर (on && (mask & PA12203001_PX_EN_MASK)) अणु
		mutex_lock(&data->lock);
		अगर (data->als_enabled) अणु
			ret = pa12203001_px_enable(data, PA12203001_PX_EN_MASK);
			अगर (ret < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			data->px_needs_enable = true;
		पूर्ण
		mutex_unlock(&data->lock);
	पूर्ण

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&data->client->dev);
		अगर (ret < 0)
			pm_runसमय_put_noidle(&data->client->dev);

	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(&data->client->dev);
		ret = pm_runसमय_put_स्वतःsuspend(&data->client->dev);
	पूर्ण

	वापस ret;

err:
	mutex_unlock(&data->lock);
	वापस ret;

#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक pa12203001_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			       पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा pa12203001_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 dev_mask;
	अचिन्हित पूर्णांक reg_byte;
	__le16 reg_word;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			dev_mask = PA12203001_ALS_EN_MASK;
			ret = pa12203001_set_घातer_state(data, true, dev_mask);
			अगर (ret < 0)
				वापस ret;
			/*
			 * ALS ADC value is stored in रेजिस्टरs
			 * PA12203001_REG_ADL and in PA12203001_REG_ADL + 1.
			 */
			ret = regmap_bulk_पढ़ो(data->map, PA12203001_REG_ADL,
					       &reg_word, 2);
			अगर (ret < 0)
				जाओ reg_err;

			*val = le16_to_cpu(reg_word);
			ret = pa12203001_set_घातer_state(data, false, dev_mask);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		हाल IIO_PROXIMITY:
			dev_mask = PA12203001_PX_EN_MASK;
			ret = pa12203001_set_घातer_state(data, true, dev_mask);
			अगर (ret < 0)
				वापस ret;
			ret = regmap_पढ़ो(data->map, PA12203001_REG_PDH,
					  &reg_byte);
			अगर (ret < 0)
				जाओ reg_err;

			*val = reg_byte;
			ret = pa12203001_set_घातer_state(data, false, dev_mask);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = regmap_पढ़ो(data->map, PA12203001_REG_CFG0, &reg_byte);
		अगर (ret < 0)
			वापस ret;
		*val = 0;
		reg_byte = (reg_byte & PA12203001_AFSR_MASK);
		*val2 = pa12203001_scales[reg_byte >> 4];
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण

reg_err:
	pa12203001_set_घातer_state(data, false, dev_mask);
	वापस ret;
पूर्ण

अटल पूर्णांक pa12203001_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
				पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा pa12203001_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret, new_val;
	अचिन्हित पूर्णांक reg_byte;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		ret = regmap_पढ़ो(data->map, PA12203001_REG_CFG0, &reg_byte);
		अगर (val != 0 || ret < 0)
			वापस -EINVAL;
		क्रम (i = 0; i < ARRAY_SIZE(pa12203001_scales); i++) अणु
			अगर (val2 == pa12203001_scales[i]) अणु
				new_val = i << PA12203001_AFSR_SHIFT;
				वापस regmap_update_bits(data->map,
							  PA12203001_REG_CFG0,
							  PA12203001_AFSR_MASK,
							  new_val);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info pa12203001_info = अणु
	.पढ़ो_raw = pa12203001_पढ़ो_raw,
	.ग_लिखो_raw = pa12203001_ग_लिखो_raw,
	.attrs = &pa12203001_attr_group,
पूर्ण;

अटल पूर्णांक pa12203001_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा pa12203001_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(regvals); i++) अणु
		ret = regmap_ग_लिखो(data->map, regvals[i].reg, regvals[i].val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pa12203001_घातer_chip(काष्ठा iio_dev *indio_dev, u8 state)
अणु
	काष्ठा pa12203001_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = pa12203001_als_enable(data, state);
	अगर (ret < 0)
		जाओ out;

	ret = pa12203001_px_enable(data, state);

out:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pa12203001_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pa12203001_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev,
					  माप(काष्ठा pa12203001_data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	data->map = devm_regmap_init_i2c(client, &pa12203001_regmap_config);
	अगर (IS_ERR(data->map))
		वापस PTR_ERR(data->map);

	mutex_init(&data->lock);

	indio_dev->info = &pa12203001_info;
	indio_dev->name = PA12203001_DRIVER_NAME;
	indio_dev->channels = pa12203001_channels;
	indio_dev->num_channels = ARRAY_SIZE(pa12203001_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = pa12203001_init(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = pa12203001_घातer_chip(indio_dev, PA12203001_CHIP_ENABLE);
	अगर (ret < 0)
		वापस ret;

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret < 0)
		जाओ out_err;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev,
					 PA12203001_SLEEP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ out_err;

	वापस 0;

out_err:
	pa12203001_घातer_chip(indio_dev, PA12203001_CHIP_DISABLE);
	वापस ret;
पूर्ण

अटल पूर्णांक pa12203001_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस pa12203001_घातer_chip(indio_dev, PA12203001_CHIP_DISABLE);
पूर्ण

#अगर defined(CONFIG_PM_SLEEP) || defined(CONFIG_PM)
अटल पूर्णांक pa12203001_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));

	वापस pa12203001_घातer_chip(indio_dev, PA12203001_CHIP_DISABLE);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pa12203001_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));

	वापस pa12203001_घातer_chip(indio_dev, PA12203001_CHIP_ENABLE);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pa12203001_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pa12203001_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	mutex_lock(&data->lock);
	अगर (data->als_needs_enable) अणु
		pa12203001_als_enable(data, PA12203001_ALS_EN_MASK);
		data->als_needs_enable = false;
	पूर्ण
	अगर (data->px_needs_enable) अणु
		pa12203001_px_enable(data, PA12203001_PX_EN_MASK);
		data->px_needs_enable = false;
	पूर्ण
	mutex_unlock(&data->lock);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops pa12203001_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pa12203001_suspend, pa12203001_resume)
	SET_RUNTIME_PM_OPS(pa12203001_suspend, pa12203001_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id pa12203001_acpi_match[] = अणु
	अणु "TXCPA122", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, pa12203001_acpi_match);

अटल स्थिर काष्ठा i2c_device_id pa12203001_id[] = अणु
		अणु"txcpa122", 0पूर्ण,
		अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, pa12203001_id);

अटल काष्ठा i2c_driver pa12203001_driver = अणु
	.driver = अणु
		.name = PA12203001_DRIVER_NAME,
		.pm = &pa12203001_pm_ops,
		.acpi_match_table = ACPI_PTR(pa12203001_acpi_match),
	पूर्ण,
	.probe = pa12203001_probe,
	.हटाओ = pa12203001_हटाओ,
	.id_table = pa12203001_id,

पूर्ण;
module_i2c_driver(pa12203001_driver);

MODULE_AUTHOR("Adriana Reus <adriana.reus@intel.com>");
MODULE_DESCRIPTION("Driver for TXC PA12203001 Proximity and Light Sensor");
MODULE_LICENSE("GPL v2");
