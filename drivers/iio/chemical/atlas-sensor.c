<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * atlas-sensor.c - Support क्रम Atlas Scientअगरic OEM SM sensors
 *
 * Copyright (C) 2015-2019 Konsulko Group
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा ATLAS_REGMAP_NAME	"atlas_regmap"
#घोषणा ATLAS_DRV_NAME		"atlas"

#घोषणा ATLAS_REG_DEV_TYPE		0x00
#घोषणा ATLAS_REG_DEV_VERSION		0x01

#घोषणा ATLAS_REG_INT_CONTROL		0x04
#घोषणा ATLAS_REG_INT_CONTROL_EN	BIT(3)

#घोषणा ATLAS_REG_PWR_CONTROL		0x06

#घोषणा ATLAS_REG_PH_CALIB_STATUS	0x0d
#घोषणा ATLAS_REG_PH_CALIB_STATUS_MASK	0x07
#घोषणा ATLAS_REG_PH_CALIB_STATUS_LOW	BIT(0)
#घोषणा ATLAS_REG_PH_CALIB_STATUS_MID	BIT(1)
#घोषणा ATLAS_REG_PH_CALIB_STATUS_HIGH	BIT(2)

#घोषणा ATLAS_REG_EC_CALIB_STATUS		0x0f
#घोषणा ATLAS_REG_EC_CALIB_STATUS_MASK		0x0f
#घोषणा ATLAS_REG_EC_CALIB_STATUS_DRY		BIT(0)
#घोषणा ATLAS_REG_EC_CALIB_STATUS_SINGLE	BIT(1)
#घोषणा ATLAS_REG_EC_CALIB_STATUS_LOW		BIT(2)
#घोषणा ATLAS_REG_EC_CALIB_STATUS_HIGH		BIT(3)

#घोषणा ATLAS_REG_DO_CALIB_STATUS		0x09
#घोषणा ATLAS_REG_DO_CALIB_STATUS_MASK		0x03
#घोषणा ATLAS_REG_DO_CALIB_STATUS_PRESSURE	BIT(0)
#घोषणा ATLAS_REG_DO_CALIB_STATUS_DO		BIT(1)

#घोषणा ATLAS_REG_RTD_DATA		0x0e

#घोषणा ATLAS_REG_PH_TEMP_DATA		0x0e
#घोषणा ATLAS_REG_PH_DATA		0x16

#घोषणा ATLAS_REG_EC_PROBE		0x08
#घोषणा ATLAS_REG_EC_TEMP_DATA		0x10
#घोषणा ATLAS_REG_EC_DATA		0x18
#घोषणा ATLAS_REG_TDS_DATA		0x1c
#घोषणा ATLAS_REG_PSS_DATA		0x20

#घोषणा ATLAS_REG_ORP_CALIB_STATUS	0x0d
#घोषणा ATLAS_REG_ORP_DATA		0x0e

#घोषणा ATLAS_REG_DO_TEMP_DATA		0x12
#घोषणा ATLAS_REG_DO_DATA		0x22

#घोषणा ATLAS_PH_INT_TIME_IN_MS		450
#घोषणा ATLAS_EC_INT_TIME_IN_MS		650
#घोषणा ATLAS_ORP_INT_TIME_IN_MS	450
#घोषणा ATLAS_DO_INT_TIME_IN_MS		450
#घोषणा ATLAS_RTD_INT_TIME_IN_MS	450

क्रमागत अणु
	ATLAS_PH_SM,
	ATLAS_EC_SM,
	ATLAS_ORP_SM,
	ATLAS_DO_SM,
	ATLAS_RTD_SM,
पूर्ण;

काष्ठा atlas_data अणु
	काष्ठा i2c_client *client;
	काष्ठा iio_trigger *trig;
	काष्ठा atlas_device *chip;
	काष्ठा regmap *regmap;
	काष्ठा irq_work work;
	अचिन्हित पूर्णांक पूर्णांकerrupt_enabled;

	__be32 buffer[6]; /* 96-bit data + 32-bit pad + 64-bit बारtamp */
पूर्ण;

अटल स्थिर काष्ठा regmap_config atlas_regmap_config = अणु
	.name = ATLAS_REGMAP_NAME,
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक atlas_buffer_num_channels(स्थिर काष्ठा iio_chan_spec *spec)
अणु
	पूर्णांक idx = 0;

	क्रम (; spec->type != IIO_TIMESTAMP; spec++)
		idx++;

	वापस idx;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec atlas_ph_channels[] = अणु
	अणु
		.type = IIO_PH,
		.address = ATLAS_REG_PH_DATA,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
	अणु
		.type = IIO_TEMP,
		.address = ATLAS_REG_PH_TEMP_DATA,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.output = 1,
		.scan_index = -1
	पूर्ण,
पूर्ण;

#घोषणा ATLAS_CONCENTRATION_CHANNEL(_idx, _addr) \
	अणु\
		.type = IIO_CONCENTRATION, \
		.indexed = 1, \
		.channel = _idx, \
		.address = _addr, \
		.info_mask_separate = \
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE), \
		.scan_index = _idx + 1, \
		.scan_type = अणु \
			.sign = 'u', \
			.realbits = 32, \
			.storagebits = 32, \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec atlas_ec_channels[] = अणु
	अणु
		.type = IIO_ELECTRICALCONDUCTIVITY,
		.address = ATLAS_REG_EC_DATA,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	ATLAS_CONCENTRATION_CHANNEL(0, ATLAS_REG_TDS_DATA),
	ATLAS_CONCENTRATION_CHANNEL(1, ATLAS_REG_PSS_DATA),
	IIO_CHAN_SOFT_TIMESTAMP(3),
	अणु
		.type = IIO_TEMP,
		.address = ATLAS_REG_EC_TEMP_DATA,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.output = 1,
		.scan_index = -1
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec atlas_orp_channels[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.address = ATLAS_REG_ORP_DATA,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec atlas_करो_channels[] = अणु
	अणु
		.type = IIO_CONCENTRATION,
		.address = ATLAS_REG_DO_DATA,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
	अणु
		.type = IIO_TEMP,
		.address = ATLAS_REG_DO_TEMP_DATA,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.output = 1,
		.scan_index = -1
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec atlas_rtd_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.address = ATLAS_REG_RTD_DATA,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल पूर्णांक atlas_check_ph_calibration(काष्ठा atlas_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(data->regmap, ATLAS_REG_PH_CALIB_STATUS, &val);
	अगर (ret)
		वापस ret;

	अगर (!(val & ATLAS_REG_PH_CALIB_STATUS_MASK)) अणु
		dev_warn(dev, "device has not been calibrated\n");
		वापस 0;
	पूर्ण

	अगर (!(val & ATLAS_REG_PH_CALIB_STATUS_LOW))
		dev_warn(dev, "device missing low point calibration\n");

	अगर (!(val & ATLAS_REG_PH_CALIB_STATUS_MID))
		dev_warn(dev, "device missing mid point calibration\n");

	अगर (!(val & ATLAS_REG_PH_CALIB_STATUS_HIGH))
		dev_warn(dev, "device missing high point calibration\n");

	वापस 0;
पूर्ण

अटल पूर्णांक atlas_check_ec_calibration(काष्ठा atlas_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	__be16	rval;

	ret = regmap_bulk_पढ़ो(data->regmap, ATLAS_REG_EC_PROBE, &rval, 2);
	अगर (ret)
		वापस ret;

	val = be16_to_cpu(rval);
	dev_info(dev, "probe set to K = %d.%.2d", val / 100, val % 100);

	ret = regmap_पढ़ो(data->regmap, ATLAS_REG_EC_CALIB_STATUS, &val);
	अगर (ret)
		वापस ret;

	अगर (!(val & ATLAS_REG_EC_CALIB_STATUS_MASK)) अणु
		dev_warn(dev, "device has not been calibrated\n");
		वापस 0;
	पूर्ण

	अगर (!(val & ATLAS_REG_EC_CALIB_STATUS_DRY))
		dev_warn(dev, "device missing dry point calibration\n");

	अगर (val & ATLAS_REG_EC_CALIB_STATUS_SINGLE) अणु
		dev_warn(dev, "device using single point calibration\n");
	पूर्ण अन्यथा अणु
		अगर (!(val & ATLAS_REG_EC_CALIB_STATUS_LOW))
			dev_warn(dev, "device missing low point calibration\n");

		अगर (!(val & ATLAS_REG_EC_CALIB_STATUS_HIGH))
			dev_warn(dev, "device missing high point calibration\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atlas_check_orp_calibration(काष्ठा atlas_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(data->regmap, ATLAS_REG_ORP_CALIB_STATUS, &val);
	अगर (ret)
		वापस ret;

	अगर (!val)
		dev_warn(dev, "device has not been calibrated\n");

	वापस 0;
पूर्ण

अटल पूर्णांक atlas_check_करो_calibration(काष्ठा atlas_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(data->regmap, ATLAS_REG_DO_CALIB_STATUS, &val);
	अगर (ret)
		वापस ret;

	अगर (!(val & ATLAS_REG_DO_CALIB_STATUS_MASK)) अणु
		dev_warn(dev, "device has not been calibrated\n");
		वापस 0;
	पूर्ण

	अगर (!(val & ATLAS_REG_DO_CALIB_STATUS_PRESSURE))
		dev_warn(dev, "device missing atmospheric pressure calibration\n");

	अगर (!(val & ATLAS_REG_DO_CALIB_STATUS_DO))
		dev_warn(dev, "device missing dissolved oxygen calibration\n");

	वापस 0;
पूर्ण

काष्ठा atlas_device अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	पूर्णांक num_channels;
	पूर्णांक data_reg;

	पूर्णांक (*calibration)(काष्ठा atlas_data *data);
	पूर्णांक delay;
पूर्ण;

अटल काष्ठा atlas_device atlas_devices[] = अणु
	[ATLAS_PH_SM] = अणु
				.channels = atlas_ph_channels,
				.num_channels = 3,
				.data_reg = ATLAS_REG_PH_DATA,
				.calibration = &atlas_check_ph_calibration,
				.delay = ATLAS_PH_INT_TIME_IN_MS,
	पूर्ण,
	[ATLAS_EC_SM] = अणु
				.channels = atlas_ec_channels,
				.num_channels = 5,
				.data_reg = ATLAS_REG_EC_DATA,
				.calibration = &atlas_check_ec_calibration,
				.delay = ATLAS_EC_INT_TIME_IN_MS,
	पूर्ण,
	[ATLAS_ORP_SM] = अणु
				.channels = atlas_orp_channels,
				.num_channels = 2,
				.data_reg = ATLAS_REG_ORP_DATA,
				.calibration = &atlas_check_orp_calibration,
				.delay = ATLAS_ORP_INT_TIME_IN_MS,
	पूर्ण,
	[ATLAS_DO_SM] = अणु
				.channels = atlas_करो_channels,
				.num_channels = 3,
				.data_reg = ATLAS_REG_DO_DATA,
				.calibration = &atlas_check_करो_calibration,
				.delay = ATLAS_DO_INT_TIME_IN_MS,
	पूर्ण,
	[ATLAS_RTD_SM] = अणु
				.channels = atlas_rtd_channels,
				.num_channels = 2,
				.data_reg = ATLAS_REG_RTD_DATA,
				.delay = ATLAS_RTD_INT_TIME_IN_MS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक atlas_set_घातermode(काष्ठा atlas_data *data, पूर्णांक on)
अणु
	वापस regmap_ग_लिखो(data->regmap, ATLAS_REG_PWR_CONTROL, on);
पूर्ण

अटल पूर्णांक atlas_set_पूर्णांकerrupt(काष्ठा atlas_data *data, bool state)
अणु
	अगर (!data->पूर्णांकerrupt_enabled)
		वापस 0;

	वापस regmap_update_bits(data->regmap, ATLAS_REG_INT_CONTROL,
				  ATLAS_REG_INT_CONTROL_EN,
				  state ? ATLAS_REG_INT_CONTROL_EN : 0);
पूर्ण

अटल पूर्णांक atlas_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा atlas_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&data->client->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&data->client->dev);
		वापस ret;
	पूर्ण

	वापस atlas_set_पूर्णांकerrupt(data, true);
पूर्ण

अटल पूर्णांक atlas_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा atlas_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = atlas_set_पूर्णांकerrupt(data, false);
	अगर (ret)
		वापस ret;

	pm_runसमय_mark_last_busy(&data->client->dev);
	ret = pm_runसमय_put_स्वतःsuspend(&data->client->dev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops atlas_पूर्णांकerrupt_trigger_ops = अणु
पूर्ण;

अटल स्थिर काष्ठा iio_buffer_setup_ops atlas_buffer_setup_ops = अणु
	.postenable = atlas_buffer_postenable,
	.predisable = atlas_buffer_predisable,
पूर्ण;

अटल व्योम atlas_work_handler(काष्ठा irq_work *work)
अणु
	काष्ठा atlas_data *data = container_of(work, काष्ठा atlas_data, work);

	iio_trigger_poll(data->trig);
पूर्ण

अटल irqवापस_t atlas_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा atlas_data *data = iio_priv(indio_dev);
	पूर्णांक channels = atlas_buffer_num_channels(data->chip->channels);
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(data->regmap, data->chip->data_reg,
			      &data->buffer, माप(__be32) * channels);

	अगर (!ret)
		iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
				iio_get_समय_ns(indio_dev));

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t atlas_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा atlas_data *data = iio_priv(indio_dev);

	irq_work_queue(&data->work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक atlas_पढ़ो_measurement(काष्ठा atlas_data *data, पूर्णांक reg, __be32 *val)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक suspended = pm_runसमय_suspended(dev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	अगर (suspended)
		msleep(data->chip->delay);

	ret = regmap_bulk_पढ़ो(data->regmap, reg, val, माप(*val));

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक atlas_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा atlas_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
	हाल IIO_CHAN_INFO_RAW: अणु
		पूर्णांक ret;
		__be32 reg;

		चयन (chan->type) अणु
		हाल IIO_TEMP:
			ret = regmap_bulk_पढ़ो(data->regmap, chan->address,
					       &reg, माप(reg));
			अवरोध;
		हाल IIO_PH:
		हाल IIO_CONCENTRATION:
		हाल IIO_ELECTRICALCONDUCTIVITY:
		हाल IIO_VOLTAGE:
			ret = iio_device_claim_direct_mode(indio_dev);
			अगर (ret)
				वापस ret;

			ret = atlas_पढ़ो_measurement(data, chan->address, &reg);

			iio_device_release_direct_mode(indio_dev);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण

		अगर (!ret) अणु
			*val = be32_to_cpu(reg);
			ret = IIO_VAL_INT;
		पूर्ण
		वापस ret;
	पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = 10;
			वापस IIO_VAL_INT;
		हाल IIO_PH:
			*val = 1; /* 0.001 */
			*val2 = 1000;
			अवरोध;
		हाल IIO_ELECTRICALCONDUCTIVITY:
			*val = 1; /* 0.00001 */
			*val2 = 100000;
			अवरोध;
		हाल IIO_CONCENTRATION:
			*val = 0; /* 0.000000001 */
			*val2 = 1000;
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		हाल IIO_VOLTAGE:
			*val = 1; /* 0.1 */
			*val2 = 10;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक atlas_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा atlas_data *data = iio_priv(indio_dev);
	__be32 reg = cpu_to_be32(val / 10);

	अगर (val2 != 0 || val < 0 || val > 20000)
		वापस -EINVAL;

	अगर (mask != IIO_CHAN_INFO_RAW || chan->type != IIO_TEMP)
		वापस -EINVAL;

	वापस regmap_bulk_ग_लिखो(data->regmap, chan->address,
				 &reg, माप(reg));
पूर्ण

अटल स्थिर काष्ठा iio_info atlas_info = अणु
	.पढ़ो_raw = atlas_पढ़ो_raw,
	.ग_लिखो_raw = atlas_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id atlas_id[] = अणु
	अणु "atlas-ph-sm", ATLAS_PH_SMपूर्ण,
	अणु "atlas-ec-sm", ATLAS_EC_SMपूर्ण,
	अणु "atlas-orp-sm", ATLAS_ORP_SMपूर्ण,
	अणु "atlas-do-sm", ATLAS_DO_SMपूर्ण,
	अणु "atlas-rtd-sm", ATLAS_RTD_SMपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, atlas_id);

अटल स्थिर काष्ठा of_device_id atlas_dt_ids[] = अणु
	अणु .compatible = "atlas,ph-sm", .data = (व्योम *)ATLAS_PH_SM, पूर्ण,
	अणु .compatible = "atlas,ec-sm", .data = (व्योम *)ATLAS_EC_SM, पूर्ण,
	अणु .compatible = "atlas,orp-sm", .data = (व्योम *)ATLAS_ORP_SM, पूर्ण,
	अणु .compatible = "atlas,do-sm", .data = (व्योम *)ATLAS_DO_SM, पूर्ण,
	अणु .compatible = "atlas,rtd-sm", .data = (व्योम *)ATLAS_RTD_SM, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, atlas_dt_ids);

अटल पूर्णांक atlas_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा atlas_data *data;
	काष्ठा atlas_device *chip;
	काष्ठा iio_trigger *trig;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	अगर (!dev_fwnode(&client->dev))
		chip = &atlas_devices[id->driver_data];
	अन्यथा
		chip = &atlas_devices[(अचिन्हित दीर्घ)device_get_match_data(&client->dev)];

	indio_dev->info = &atlas_info;
	indio_dev->name = ATLAS_DRV_NAME;
	indio_dev->channels = chip->channels;
	indio_dev->num_channels = chip->num_channels;
	indio_dev->modes = INDIO_BUFFER_SOFTWARE | INDIO_सूचीECT_MODE;

	trig = devm_iio_trigger_alloc(&client->dev, "%s-dev%d",
				      indio_dev->name, indio_dev->id);

	अगर (!trig)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	data->trig = trig;
	data->chip = chip;
	trig->ops = &atlas_पूर्णांकerrupt_trigger_ops;
	iio_trigger_set_drvdata(trig, indio_dev);

	i2c_set_clientdata(client, indio_dev);

	data->regmap = devm_regmap_init_i2c(client, &atlas_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "regmap initialization failed\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret)
		वापस ret;

	ret = chip->calibration(data);
	अगर (ret)
		वापस ret;

	ret = iio_trigger_रेजिस्टर(trig);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to register trigger\n");
		वापस ret;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_समय,
		&atlas_trigger_handler, &atlas_buffer_setup_ops);
	अगर (ret) अणु
		dev_err(&client->dev, "cannot setup iio trigger\n");
		जाओ unरेजिस्टर_trigger;
	पूर्ण

	init_irq_work(&data->work, atlas_work_handler);

	अगर (client->irq > 0) अणु
		/* पूर्णांकerrupt pin toggles on new conversion */
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
				शून्य, atlas_पूर्णांकerrupt_handler,
				IRQF_TRIGGER_RISING |
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"atlas_irq",
				indio_dev);

		अगर (ret)
			dev_warn(&client->dev,
				"request irq (%d) failed\n", client->irq);
		अन्यथा
			data->पूर्णांकerrupt_enabled = 1;
	पूर्ण

	ret = atlas_set_घातermode(data, 1);
	अगर (ret) अणु
		dev_err(&client->dev, "cannot power device on");
		जाओ unरेजिस्टर_buffer;
	पूर्ण

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 2500);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "unable to register device\n");
		जाओ unरेजिस्टर_pm;
	पूर्ण

	वापस 0;

unरेजिस्टर_pm:
	pm_runसमय_disable(&client->dev);
	atlas_set_घातermode(data, 0);

unरेजिस्टर_buffer:
	iio_triggered_buffer_cleanup(indio_dev);

unरेजिस्टर_trigger:
	iio_trigger_unरेजिस्टर(data->trig);

	वापस ret;
पूर्ण

अटल पूर्णांक atlas_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा atlas_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	iio_trigger_unरेजिस्टर(data->trig);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	वापस atlas_set_घातermode(data, 0);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक atlas_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा atlas_data *data =
		     iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस atlas_set_घातermode(data, 0);
पूर्ण

अटल पूर्णांक atlas_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा atlas_data *data =
		     iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस atlas_set_घातermode(data, 1);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops atlas_pm_ops = अणु
	SET_RUNTIME_PM_OPS(atlas_runसमय_suspend,
			   atlas_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver atlas_driver = अणु
	.driver = अणु
		.name	= ATLAS_DRV_NAME,
		.of_match_table	= atlas_dt_ids,
		.pm	= &atlas_pm_ops,
	पूर्ण,
	.probe		= atlas_probe,
	.हटाओ		= atlas_हटाओ,
	.id_table	= atlas_id,
पूर्ण;
module_i2c_driver(atlas_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("Atlas Scientific SM sensors");
MODULE_LICENSE("GPL");
