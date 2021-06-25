<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
 /*
  * iio/dac/max5821.c
  * Copyright (C) 2014 Philippe Reynes
  */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/regulator/consumer.h>

#घोषणा MAX5821_MAX_DAC_CHANNELS		2

/* command bytes */
#घोषणा MAX5821_LOAD_DAC_A_IN_REG_B		0x00
#घोषणा MAX5821_LOAD_DAC_B_IN_REG_A		0x10
#घोषणा MAX5821_EXTENDED_COMMAND_MODE		0xf0
#घोषणा MAX5821_READ_DAC_A_COMMAND		0xf1
#घोषणा MAX5821_READ_DAC_B_COMMAND		0xf2

#घोषणा MAX5821_EXTENDED_POWER_UP		0x00
#घोषणा MAX5821_EXTENDED_POWER_DOWN_MODE0	0x01
#घोषणा MAX5821_EXTENDED_POWER_DOWN_MODE1	0x02
#घोषणा MAX5821_EXTENDED_POWER_DOWN_MODE2	0x03
#घोषणा MAX5821_EXTENDED_DAC_A			0x04
#घोषणा MAX5821_EXTENDED_DAC_B			0x08

क्रमागत max5821_device_ids अणु
	ID_MAX5821,
पूर्ण;

काष्ठा max5821_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा regulator	*vref_reg;
	अचिन्हित लघु		vref_mv;
	bool			घातerकरोwn[MAX5821_MAX_DAC_CHANNELS];
	u8			घातerकरोwn_mode[MAX5821_MAX_DAC_CHANNELS];
	काष्ठा mutex		lock;
पूर्ण;

अटल स्थिर अक्षर * स्थिर max5821_घातerकरोwn_modes[] = अणु
	"three_state",
	"1kohm_to_gnd",
	"100kohm_to_gnd",
पूर्ण;

क्रमागत अणु
	MAX5821_THREE_STATE,
	MAX5821_1KOHM_TO_GND,
	MAX5821_100KOHM_TO_GND
पूर्ण;

अटल पूर्णांक max5821_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा max5821_data *st = iio_priv(indio_dev);

	वापस st->घातerकरोwn_mode[chan->channel];
पूर्ण

अटल पूर्णांक max5821_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      अचिन्हित पूर्णांक mode)
अणु
	काष्ठा max5821_data *st = iio_priv(indio_dev);

	st->घातerकरोwn_mode[chan->channel] = mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत max5821_घातerकरोwn_mode_क्रमागत = अणु
	.items = max5821_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(max5821_घातerकरोwn_modes),
	.get = max5821_get_घातerकरोwn_mode,
	.set = max5821_set_घातerकरोwn_mode,
पूर्ण;

अटल sमाप_प्रकार max5821_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					  uपूर्णांकptr_t निजी,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  अक्षर *buf)
अणु
	काष्ठा max5821_data *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", st->घातerकरोwn[chan->channel]);
पूर्ण

अटल पूर्णांक max5821_sync_घातerकरोwn_mode(काष्ठा max5821_data *data,
				       स्थिर काष्ठा iio_chan_spec *chan)
अणु
	u8 outbuf[2];

	outbuf[0] = MAX5821_EXTENDED_COMMAND_MODE;

	अगर (chan->channel == 0)
		outbuf[1] = MAX5821_EXTENDED_DAC_A;
	अन्यथा
		outbuf[1] = MAX5821_EXTENDED_DAC_B;

	अगर (data->घातerकरोwn[chan->channel])
		outbuf[1] |= data->घातerकरोwn_mode[chan->channel] + 1;
	अन्यथा
		outbuf[1] |= MAX5821_EXTENDED_POWER_UP;

	वापस i2c_master_send(data->client, outbuf, 2);
पूर्ण

अटल sमाप_प्रकार max5821_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					   uपूर्णांकptr_t निजी,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा max5821_data *data = iio_priv(indio_dev);
	bool घातerकरोwn;
	पूर्णांक ret;

	ret = strtobool(buf, &घातerकरोwn);
	अगर (ret)
		वापस ret;

	data->घातerकरोwn[chan->channel] = घातerकरोwn;

	ret = max5821_sync_घातerकरोwn_mode(data, chan);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info max5821_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = max5821_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = max5821_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SEPARATE, &max5821_घातerकरोwn_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("powerdown_mode", &max5821_घातerकरोwn_mode_क्रमागत),
	अणु पूर्ण,
पूर्ण;

#घोषणा MAX5821_CHANNEL(chan) अणु					\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (chan),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SCALE),	\
	.ext_info = max5821_ext_info,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec max5821_channels[] = अणु
	MAX5821_CHANNEL(0),
	MAX5821_CHANNEL(1)
पूर्ण;

अटल स्थिर u8 max5821_पढ़ो_dac_command[] = अणु
	MAX5821_READ_DAC_A_COMMAND,
	MAX5821_READ_DAC_B_COMMAND
पूर्ण;

अटल स्थिर u8 max5821_load_dac_command[] = अणु
	MAX5821_LOAD_DAC_A_IN_REG_B,
	MAX5821_LOAD_DAC_B_IN_REG_A
पूर्ण;

अटल पूर्णांक max5821_get_value(काष्ठा iio_dev *indio_dev,
			     पूर्णांक *val, पूर्णांक channel)
अणु
	काष्ठा max5821_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;
	u8 outbuf[1];
	u8 inbuf[2];
	पूर्णांक ret;

	अगर ((channel != 0) && (channel != 1))
		वापस -EINVAL;

	outbuf[0] = max5821_पढ़ो_dac_command[channel];

	mutex_lock(&data->lock);

	ret = i2c_master_send(client, outbuf, 1);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण अन्यथा अगर (ret != 1) अणु
		mutex_unlock(&data->lock);
		वापस -EIO;
	पूर्ण

	ret = i2c_master_recv(client, inbuf, 2);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण अन्यथा अगर (ret != 2) अणु
		mutex_unlock(&data->lock);
		वापस -EIO;
	पूर्ण

	mutex_unlock(&data->lock);

	*val = ((inbuf[0] & 0x0f) << 6) | (inbuf[1] >> 2);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक max5821_set_value(काष्ठा iio_dev *indio_dev,
			     पूर्णांक val, पूर्णांक channel)
अणु
	काष्ठा max5821_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;
	u8 outbuf[2];
	पूर्णांक ret;

	अगर ((val < 0) || (val > 1023))
		वापस -EINVAL;

	अगर ((channel != 0) && (channel != 1))
		वापस -EINVAL;

	outbuf[0] = max5821_load_dac_command[channel];
	outbuf[0] |= val >> 6;
	outbuf[1] = (val & 0x3f) << 2;

	ret = i2c_master_send(client, outbuf, 2);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != 2)
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक max5821_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max5821_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस max5821_get_value(indio_dev, val, chan->channel);
	हाल IIO_CHAN_INFO_SCALE:
		*val = data->vref_mv;
		*val2 = 10;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक max5821_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	अगर (val2 != 0)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस max5821_set_value(indio_dev, val, chan->channel);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused max5821_suspend(काष्ठा device *dev)
अणु
	u8 outbuf[2] = अणु MAX5821_EXTENDED_COMMAND_MODE,
			 MAX5821_EXTENDED_DAC_A |
			 MAX5821_EXTENDED_DAC_B |
			 MAX5821_EXTENDED_POWER_DOWN_MODE2 पूर्ण;

	वापस i2c_master_send(to_i2c_client(dev), outbuf, 2);
पूर्ण

अटल पूर्णांक __maybe_unused max5821_resume(काष्ठा device *dev)
अणु
	u8 outbuf[2] = अणु MAX5821_EXTENDED_COMMAND_MODE,
			 MAX5821_EXTENDED_DAC_A |
			 MAX5821_EXTENDED_DAC_B |
			 MAX5821_EXTENDED_POWER_UP पूर्ण;

	वापस i2c_master_send(to_i2c_client(dev), outbuf, 2);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max5821_pm_ops, max5821_suspend, max5821_resume);

अटल स्थिर काष्ठा iio_info max5821_info = अणु
	.पढ़ो_raw = max5821_पढ़ो_raw,
	.ग_लिखो_raw = max5821_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक max5821_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max5821_data *data;
	काष्ठा iio_dev *indio_dev;
	u32 पंचांगp;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;
	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	/* max5821 start in घातerकरोwn mode 100Kohm to ground */
	क्रम (पंचांगp = 0; पंचांगp < MAX5821_MAX_DAC_CHANNELS; पंचांगp++) अणु
		data->घातerकरोwn[पंचांगp] = true;
		data->घातerकरोwn_mode[पंचांगp] = MAX5821_100KOHM_TO_GND;
	पूर्ण

	data->vref_reg = devm_regulator_get(&client->dev, "vref");
	अगर (IS_ERR(data->vref_reg)) अणु
		ret = PTR_ERR(data->vref_reg);
		dev_err(&client->dev,
			"Failed to get vref regulator: %d\n", ret);
		जाओ error_मुक्त_reg;
	पूर्ण

	ret = regulator_enable(data->vref_reg);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Failed to enable vref regulator: %d\n", ret);
		जाओ error_मुक्त_reg;
	पूर्ण

	ret = regulator_get_voltage(data->vref_reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"Failed to get voltage on regulator: %d\n", ret);
		जाओ error_disable_reg;
	पूर्ण

	data->vref_mv = ret / 1000;

	indio_dev->name = id->name;
	indio_dev->num_channels = ARRAY_SIZE(max5821_channels);
	indio_dev->channels = max5821_channels;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &max5821_info;

	वापस iio_device_रेजिस्टर(indio_dev);

error_disable_reg:
	regulator_disable(data->vref_reg);

error_मुक्त_reg:

	वापस ret;
पूर्ण

अटल पूर्णांक max5821_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा max5821_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(data->vref_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max5821_id[] = अणु
	अणु "max5821", ID_MAX5821 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max5821_id);

अटल स्थिर काष्ठा of_device_id max5821_of_match[] = अणु
	अणु .compatible = "maxim,max5821" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max5821_of_match);

अटल काष्ठा i2c_driver max5821_driver = अणु
	.driver = अणु
		.name	= "max5821",
		.of_match_table = max5821_of_match,
		.pm     = &max5821_pm_ops,
	पूर्ण,
	.probe		= max5821_probe,
	.हटाओ		= max5821_हटाओ,
	.id_table	= max5821_id,
पूर्ण;
module_i2c_driver(max5821_driver);

MODULE_AUTHOR("Philippe Reynes <tremyfr@yahoo.fr>");
MODULE_DESCRIPTION("MAX5821 DAC");
MODULE_LICENSE("GPL v2");
