<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * lmp91000.c - Support क्रम Texas Instruments digital potentiostats
 *
 * Copyright (C) 2016, 2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 *
 * TODO: bias voltage + polarity control, and multiple chip support
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा LMP91000_REG_LOCK		0x01
#घोषणा LMP91000_REG_TIACN		0x10
#घोषणा LMP91000_REG_TIACN_GAIN_SHIFT	2

#घोषणा LMP91000_REG_REFCN		0x11
#घोषणा LMP91000_REG_REFCN_EXT_REF	0x20
#घोषणा LMP91000_REG_REFCN_50_ZERO	0x80

#घोषणा LMP91000_REG_MODECN		0x12
#घोषणा LMP91000_REG_MODECN_3LEAD	0x03
#घोषणा LMP91000_REG_MODECN_TEMP	0x07

#घोषणा LMP91000_DRV_NAME	"lmp91000"

अटल स्थिर पूर्णांक lmp91000_tia_gain[] = अणु 0, 2750, 3500, 7000, 14000, 35000,
					 120000, 350000 पूर्ण;

अटल स्थिर पूर्णांक lmp91000_rload[] = अणु 10, 33, 50, 100 पूर्ण;

#घोषणा LMP91000_TEMP_BASE	-40

अटल स्थिर u16 lmp91000_temp_lut[] = अणु
	1875, 1867, 1860, 1852, 1844, 1836, 1828, 1821, 1813, 1805,
	1797, 1789, 1782, 1774, 1766, 1758, 1750, 1742, 1734, 1727,
	1719, 1711, 1703, 1695, 1687, 1679, 1671, 1663, 1656, 1648,
	1640, 1632, 1624, 1616, 1608, 1600, 1592, 1584, 1576, 1568,
	1560, 1552, 1544, 1536, 1528, 1520, 1512, 1504, 1496, 1488,
	1480, 1472, 1464, 1456, 1448, 1440, 1432, 1424, 1415, 1407,
	1399, 1391, 1383, 1375, 1367, 1359, 1351, 1342, 1334, 1326,
	1318, 1310, 1302, 1293, 1285, 1277, 1269, 1261, 1253, 1244,
	1236, 1228, 1220, 1212, 1203, 1195, 1187, 1179, 1170, 1162,
	1154, 1146, 1137, 1129, 1121, 1112, 1104, 1096, 1087, 1079,
	1071, 1063, 1054, 1046, 1038, 1029, 1021, 1012, 1004,  996,
	 987,  979,  971,  962,  954,  945,  937,  929,  920,  912,
	 903,  895,  886,  878,  870,  861 पूर्ण;

अटल स्थिर काष्ठा regmap_config lmp91000_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

काष्ठा lmp91000_data अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;

	काष्ठा iio_trigger *trig;
	काष्ठा iio_cb_buffer *cb_buffer;
	काष्ठा iio_channel *adc_chan;

	काष्ठा completion completion;
	u8 chan_select;

	u32 buffer[4]; /* 64-bit data + 64-bit बारtamp */
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec lmp91000_channels[] = अणु
	अणु /* chemical channel mV */
		.type = IIO_VOLTAGE,
		.channel = 0,
		.address = LMP91000_REG_MODECN_3LEAD,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_OFFSET) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 32,
			.storagebits = 32,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
	अणु /* temperature channel mV */
		.type = IIO_TEMP,
		.channel = 1,
		.address = LMP91000_REG_MODECN_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.scan_index = -1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक lmp91000_पढ़ो(काष्ठा lmp91000_data *data, पूर्णांक channel, पूर्णांक *val)
अणु
	पूर्णांक state, ret;

	ret = regmap_पढ़ो(data->regmap, LMP91000_REG_MODECN, &state);
	अगर (ret)
		वापस -EINVAL;

	ret = regmap_ग_लिखो(data->regmap, LMP91000_REG_MODECN, channel);
	अगर (ret)
		वापस -EINVAL;

	/* delay till first temperature पढ़ोing is complete */
	अगर (state != channel && channel == LMP91000_REG_MODECN_TEMP)
		usleep_range(3000, 4000);

	data->chan_select = channel != LMP91000_REG_MODECN_3LEAD;

	iio_trigger_poll_chained(data->trig);

	ret = रुको_क्रम_completion_समयout(&data->completion, HZ);
	reinit_completion(&data->completion);

	अगर (!ret)
		वापस -ETIMEDOUT;

	*val = data->buffer[data->chan_select];

	वापस 0;
पूर्ण

अटल irqवापस_t lmp91000_buffer_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा lmp91000_data *data = iio_priv(indio_dev);
	पूर्णांक ret, val;

	स_रखो(data->buffer, 0, माप(data->buffer));

	ret = lmp91000_पढ़ो(data, LMP91000_REG_MODECN_3LEAD, &val);
	अगर (!ret) अणु
		data->buffer[0] = val;
		iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
						   iio_get_समय_ns(indio_dev));
	पूर्ण

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lmp91000_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा lmp91000_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED: अणु
		पूर्णांक ret = iio_channel_start_all_cb(data->cb_buffer);

		अगर (ret)
			वापस ret;

		ret = lmp91000_पढ़ो(data, chan->address, val);

		iio_channel_stop_all_cb(data->cb_buffer);

		अगर (ret)
			वापस ret;

		अगर (mask == IIO_CHAN_INFO_PROCESSED) अणु
			पूर्णांक पंचांगp, i;

			ret = iio_convert_raw_to_processed(data->adc_chan,
							   *val, &पंचांगp, 1);
			अगर (ret)
				वापस ret;

			क्रम (i = 0; i < ARRAY_SIZE(lmp91000_temp_lut); i++)
				अगर (lmp91000_temp_lut[i] < पंचांगp)
					अवरोध;

			*val = (LMP91000_TEMP_BASE + i) * 1000;
		पूर्ण
		वापस IIO_VAL_INT;
	पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		वापस iio_पढ़ो_channel_offset(data->adc_chan, val, val2);
	हाल IIO_CHAN_INFO_SCALE:
		वापस iio_पढ़ो_channel_scale(data->adc_chan, val, val2);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info lmp91000_info = अणु
	.पढ़ो_raw = lmp91000_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक lmp91000_पढ़ो_config(काष्ठा lmp91000_data *data)
अणु
	काष्ठा device *dev = data->dev;
	अचिन्हित पूर्णांक reg, val;
	पूर्णांक i, ret;

	ret = device_property_पढ़ो_u32(dev, "ti,tia-gain-ohm", &val);
	अगर (ret) अणु
		अगर (!device_property_पढ़ो_bool(dev, "ti,external-tia-resistor")) अणु
			dev_err(dev, "no ti,tia-gain-ohm defined and external resistor not specified\n");
			वापस ret;
		पूर्ण
		val = 0;
	पूर्ण

	ret = -EINVAL;
	क्रम (i = 0; i < ARRAY_SIZE(lmp91000_tia_gain); i++) अणु
		अगर (lmp91000_tia_gain[i] == val) अणु
			reg = i << LMP91000_REG_TIACN_GAIN_SHIFT;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		dev_err(dev, "invalid ti,tia-gain-ohm %d\n", val);
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "ti,rload-ohm", &val);
	अगर (ret) अणु
		val = 100;
		dev_info(dev, "no ti,rload-ohm defined, default to %d\n", val);
	पूर्ण

	ret = -EINVAL;
	क्रम (i = 0; i < ARRAY_SIZE(lmp91000_rload); i++) अणु
		अगर (lmp91000_rload[i] == val) अणु
			reg |= i;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		dev_err(dev, "invalid ti,rload-ohm %d\n", val);
		वापस ret;
	पूर्ण

	regmap_ग_लिखो(data->regmap, LMP91000_REG_LOCK, 0);
	regmap_ग_लिखो(data->regmap, LMP91000_REG_TIACN, reg);
	regmap_ग_लिखो(data->regmap, LMP91000_REG_REFCN,
		     LMP91000_REG_REFCN_EXT_REF | LMP91000_REG_REFCN_50_ZERO);
	regmap_ग_लिखो(data->regmap, LMP91000_REG_LOCK, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक lmp91000_buffer_cb(स्थिर व्योम *val, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा lmp91000_data *data = iio_priv(indio_dev);

	data->buffer[data->chan_select] = *((पूर्णांक *)val);
	complete_all(&data->completion);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops lmp91000_trigger_ops = अणु
पूर्ण;

अटल पूर्णांक lmp91000_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा lmp91000_data *data = iio_priv(indio_dev);

	वापस iio_channel_start_all_cb(data->cb_buffer);
पूर्ण

अटल पूर्णांक lmp91000_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा lmp91000_data *data = iio_priv(indio_dev);

	iio_channel_stop_all_cb(data->cb_buffer);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops lmp91000_buffer_setup_ops = अणु
	.postenable = lmp91000_buffer_postenable,
	.predisable = lmp91000_buffer_predisable,
पूर्ण;

अटल पूर्णांक lmp91000_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा lmp91000_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->info = &lmp91000_info;
	indio_dev->channels = lmp91000_channels;
	indio_dev->num_channels = ARRAY_SIZE(lmp91000_channels);
	indio_dev->name = LMP91000_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	i2c_set_clientdata(client, indio_dev);

	data = iio_priv(indio_dev);
	data->dev = dev;
	data->regmap = devm_regmap_init_i2c(client, &lmp91000_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(dev, "regmap initialization failed.\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	data->trig = devm_iio_trigger_alloc(dev, "%s-mux%d",
					    indio_dev->name, indio_dev->id);
	अगर (!data->trig) अणु
		dev_err(dev, "cannot allocate iio trigger.\n");
		वापस -ENOMEM;
	पूर्ण

	data->trig->ops = &lmp91000_trigger_ops;
	init_completion(&data->completion);

	ret = lmp91000_पढ़ो_config(data);
	अगर (ret)
		वापस ret;

	ret = iio_trigger_set_immutable(iio_channel_cb_get_iio_dev(data->cb_buffer),
					data->trig);
	अगर (ret) अणु
		dev_err(dev, "cannot set immutable trigger.\n");
		वापस ret;
	पूर्ण

	ret = iio_trigger_रेजिस्टर(data->trig);
	अगर (ret) अणु
		dev_err(dev, "cannot register iio trigger.\n");
		वापस ret;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 &lmp91000_buffer_handler,
					 &lmp91000_buffer_setup_ops);
	अगर (ret)
		जाओ error_unreg_trigger;

	data->cb_buffer = iio_channel_get_all_cb(dev, &lmp91000_buffer_cb,
						 indio_dev);

	अगर (IS_ERR(data->cb_buffer)) अणु
		अगर (PTR_ERR(data->cb_buffer) == -ENODEV)
			ret = -EPROBE_DEFER;
		अन्यथा
			ret = PTR_ERR(data->cb_buffer);

		जाओ error_unreg_buffer;
	पूर्ण

	data->adc_chan = iio_channel_cb_get_channels(data->cb_buffer);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_unreg_cb_buffer;

	वापस 0;

error_unreg_cb_buffer:
	iio_channel_release_all_cb(data->cb_buffer);

error_unreg_buffer:
	iio_triggered_buffer_cleanup(indio_dev);

error_unreg_trigger:
	iio_trigger_unरेजिस्टर(data->trig);

	वापस ret;
पूर्ण

अटल पूर्णांक lmp91000_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा lmp91000_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	iio_channel_stop_all_cb(data->cb_buffer);
	iio_channel_release_all_cb(data->cb_buffer);

	iio_triggered_buffer_cleanup(indio_dev);
	iio_trigger_unरेजिस्टर(data->trig);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lmp91000_of_match[] = अणु
	अणु .compatible = "ti,lmp91000", पूर्ण,
	अणु .compatible = "ti,lmp91002", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lmp91000_of_match);

अटल स्थिर काष्ठा i2c_device_id lmp91000_id[] = अणु
	अणु "lmp91000", 0 पूर्ण,
	अणु "lmp91002", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lmp91000_id);

अटल काष्ठा i2c_driver lmp91000_driver = अणु
	.driver = अणु
		.name = LMP91000_DRV_NAME,
		.of_match_table = lmp91000_of_match,
	पूर्ण,
	.probe = lmp91000_probe,
	.हटाओ = lmp91000_हटाओ,
	.id_table = lmp91000_id,
पूर्ण;
module_i2c_driver(lmp91000_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("LMP91000 digital potentiostat");
MODULE_LICENSE("GPL");
