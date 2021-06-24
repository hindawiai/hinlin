<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ti-dac5571.c - Texas Instruments 8/10/12-bit 1/4-channel DAC driver
 *
 * Copyright (C) 2018 Prevas A/S
 *
 * https://www.ti.com/lit/ds/symlink/dac5571.pdf
 * https://www.ti.com/lit/ds/symlink/dac6571.pdf
 * https://www.ti.com/lit/ds/symlink/dac7571.pdf
 * https://www.ti.com/lit/ds/symlink/dac5574.pdf
 * https://www.ti.com/lit/ds/symlink/dac6574.pdf
 * https://www.ti.com/lit/ds/symlink/dac7574.pdf
 * https://www.ti.com/lit/ds/symlink/dac5573.pdf
 * https://www.ti.com/lit/ds/symlink/dac6573.pdf
 * https://www.ti.com/lit/ds/symlink/dac7573.pdf
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/regulator/consumer.h>

क्रमागत chip_id अणु
	single_8bit, single_10bit, single_12bit,
	quad_8bit, quad_10bit, quad_12bit
पूर्ण;

काष्ठा dac5571_spec अणु
	u8 num_channels;
	u8 resolution;
पूर्ण;

अटल स्थिर काष्ठा dac5571_spec dac5571_spec[] = अणु
	[single_8bit]  = अणु.num_channels = 1, .resolution =  8पूर्ण,
	[single_10bit] = अणु.num_channels = 1, .resolution = 10पूर्ण,
	[single_12bit] = अणु.num_channels = 1, .resolution = 12पूर्ण,
	[quad_8bit]    = अणु.num_channels = 4, .resolution =  8पूर्ण,
	[quad_10bit]   = अणु.num_channels = 4, .resolution = 10पूर्ण,
	[quad_12bit]   = अणु.num_channels = 4, .resolution = 12पूर्ण,
पूर्ण;

काष्ठा dac5571_data अणु
	काष्ठा i2c_client *client;
	पूर्णांक id;
	काष्ठा mutex lock;
	काष्ठा regulator *vref;
	u16 val[4];
	bool घातerकरोwn[4];
	u8 घातerकरोwn_mode[4];
	काष्ठा dac5571_spec स्थिर *spec;
	पूर्णांक (*dac5571_cmd)(काष्ठा dac5571_data *data, पूर्णांक channel, u16 val);
	पूर्णांक (*dac5571_pwrdwn)(काष्ठा dac5571_data *data, पूर्णांक channel, u8 pwrdwn);
	u8 buf[3] ____cacheline_aligned;
पूर्ण;

#घोषणा DAC5571_POWERDOWN(mode)		((mode) + 1)
#घोषणा DAC5571_POWERDOWN_FLAG		BIT(0)
#घोषणा DAC5571_CHANNEL_SELECT		1
#घोषणा DAC5571_LOADMODE_सूचीECT		BIT(4)
#घोषणा DAC5571_SINGLE_PWRDWN_BITS	4
#घोषणा DAC5571_QUAD_PWRDWN_BITS	6

अटल पूर्णांक dac5571_cmd_single(काष्ठा dac5571_data *data, पूर्णांक channel, u16 val)
अणु
	अचिन्हित पूर्णांक shअगरt;

	shअगरt = 12 - data->spec->resolution;
	data->buf[1] = val << shअगरt;
	data->buf[0] = val >> (8 - shअगरt);

	अगर (i2c_master_send(data->client, data->buf, 2) != 2)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक dac5571_cmd_quad(काष्ठा dac5571_data *data, पूर्णांक channel, u16 val)
अणु
	अचिन्हित पूर्णांक shअगरt;

	shअगरt = 16 - data->spec->resolution;
	data->buf[2] = val << shअगरt;
	data->buf[1] = (val >> (8 - shअगरt));
	data->buf[0] = (channel << DAC5571_CHANNEL_SELECT) |
		       DAC5571_LOADMODE_सूचीECT;

	अगर (i2c_master_send(data->client, data->buf, 3) != 3)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक dac5571_pwrdwn_single(काष्ठा dac5571_data *data, पूर्णांक channel, u8 pwrdwn)
अणु
	data->buf[1] = 0;
	data->buf[0] = pwrdwn << DAC5571_SINGLE_PWRDWN_BITS;

	अगर (i2c_master_send(data->client, data->buf, 2) != 2)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक dac5571_pwrdwn_quad(काष्ठा dac5571_data *data, पूर्णांक channel, u8 pwrdwn)
अणु
	data->buf[2] = 0;
	data->buf[1] = pwrdwn << DAC5571_QUAD_PWRDWN_BITS;
	data->buf[0] = (channel << DAC5571_CHANNEL_SELECT) |
		       DAC5571_LOADMODE_सूचीECT | DAC5571_POWERDOWN_FLAG;

	अगर (i2c_master_send(data->client, data->buf, 3) != 3)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *स्थिर dac5571_घातerकरोwn_modes[] = अणु
	"1kohm_to_gnd", "100kohm_to_gnd", "three_state",
पूर्ण;

अटल पूर्णांक dac5571_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा dac5571_data *data = iio_priv(indio_dev);

	वापस data->घातerकरोwn_mode[chan->channel];
पूर्ण

अटल पूर्णांक dac5571_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      अचिन्हित पूर्णांक mode)
अणु
	काष्ठा dac5571_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	अगर (data->घातerकरोwn_mode[chan->channel] == mode)
		वापस 0;

	mutex_lock(&data->lock);
	अगर (data->घातerकरोwn[chan->channel]) अणु
		ret = data->dac5571_pwrdwn(data, chan->channel,
					   DAC5571_POWERDOWN(mode));
		अगर (ret)
			जाओ out;
	पूर्ण
	data->घातerकरोwn_mode[chan->channel] = mode;

 out:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत dac5571_घातerकरोwn_mode = अणु
	.items = dac5571_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(dac5571_घातerकरोwn_modes),
	.get = dac5571_get_घातerकरोwn_mode,
	.set = dac5571_set_घातerकरोwn_mode,
पूर्ण;

अटल sमाप_प्रकार dac5571_पढ़ो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
				      uपूर्णांकptr_t निजी,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      अक्षर *buf)
अणु
	काष्ठा dac5571_data *data = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", data->घातerकरोwn[chan->channel]);
पूर्ण

अटल sमाप_प्रकार dac5571_ग_लिखो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
				       uपूर्णांकptr_t निजी,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा dac5571_data *data = iio_priv(indio_dev);
	bool घातerकरोwn;
	पूर्णांक ret;

	ret = strtobool(buf, &घातerकरोwn);
	अगर (ret)
		वापस ret;

	अगर (data->घातerकरोwn[chan->channel] == घातerकरोwn)
		वापस len;

	mutex_lock(&data->lock);
	अगर (घातerकरोwn)
		ret = data->dac5571_pwrdwn(data, chan->channel,
			    DAC5571_POWERDOWN(data->घातerकरोwn_mode[chan->channel]));
	अन्यथा
		ret = data->dac5571_cmd(data, chan->channel,
				data->val[chan->channel]);
	अगर (ret)
		जाओ out;

	data->घातerकरोwn[chan->channel] = घातerकरोwn;

 out:
	mutex_unlock(&data->lock);

	वापस ret ? ret : len;
पूर्ण


अटल स्थिर काष्ठा iio_chan_spec_ext_info dac5571_ext_info[] = अणु
	अणु
		.name	   = "powerdown",
		.पढ़ो	   = dac5571_पढ़ो_घातerकरोwn,
		.ग_लिखो	   = dac5571_ग_लिखो_घातerकरोwn,
		.shared	   = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SEPARATE, &dac5571_घातerकरोwn_mode),
	IIO_ENUM_AVAILABLE("powerdown_mode", &dac5571_घातerकरोwn_mode),
	अणुपूर्ण,
पूर्ण;

#घोषणा dac5571_CHANNEL(chan, name) अणु				\
	.type = IIO_VOLTAGE,					\
	.channel = (chan),					\
	.address = (chan),					\
	.indexed = true,					\
	.output = true,						\
	.datasheet_name = name,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.ext_info = dac5571_ext_info,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec dac5571_channels[] = अणु
	dac5571_CHANNEL(0, "A"),
	dac5571_CHANNEL(1, "B"),
	dac5571_CHANNEL(2, "C"),
	dac5571_CHANNEL(3, "D"),
पूर्ण;

अटल पूर्णांक dac5571_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा dac5571_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = data->val[chan->channel];
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(data->vref);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000;
		*val2 = data->spec->resolution;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dac5571_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा dac5571_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (data->val[chan->channel] == val)
			वापस 0;

		अगर (val >= (1 << data->spec->resolution) || val < 0)
			वापस -EINVAL;

		अगर (data->घातerकरोwn[chan->channel])
			वापस -EBUSY;

		mutex_lock(&data->lock);
		ret = data->dac5571_cmd(data, chan->channel, val);
		अगर (ret == 0)
			data->val[chan->channel] = val;
		mutex_unlock(&data->lock);
		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dac5571_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *chan,
				     दीर्घ mask)
अणु
	वापस IIO_VAL_INT;
पूर्ण

अटल स्थिर काष्ठा iio_info dac5571_info = अणु
	.पढ़ो_raw = dac5571_पढ़ो_raw,
	.ग_लिखो_raw = dac5571_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = dac5571_ग_लिखो_raw_get_fmt,
पूर्ण;

अटल पूर्णांक dac5571_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा dac5571_spec *spec;
	काष्ठा dac5571_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret, i;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->info = &dac5571_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = dac5571_channels;

	spec = &dac5571_spec[id->driver_data];
	indio_dev->num_channels = spec->num_channels;
	data->spec = spec;

	data->vref = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(data->vref))
		वापस PTR_ERR(data->vref);

	ret = regulator_enable(data->vref);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&data->lock);

	चयन (spec->num_channels) अणु
	हाल 1:
		data->dac5571_cmd = dac5571_cmd_single;
		data->dac5571_pwrdwn = dac5571_pwrdwn_single;
		अवरोध;
	हाल 4:
		data->dac5571_cmd = dac5571_cmd_quad;
		data->dac5571_pwrdwn = dac5571_pwrdwn_quad;
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < spec->num_channels; i++) अणु
		ret = data->dac5571_cmd(data, i, 0);
		अगर (ret) अणु
			dev_err(dev, "failed to initialize channel %d to 0\n", i);
			जाओ err;
		पूर्ण
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err;

	वापस 0;

 err:
	regulator_disable(data->vref);
	वापस ret;
पूर्ण

अटल पूर्णांक dac5571_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(i2c);
	काष्ठा dac5571_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(data->vref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dac5571_of_id[] = अणु
	अणु.compatible = "ti,dac5571"पूर्ण,
	अणु.compatible = "ti,dac6571"पूर्ण,
	अणु.compatible = "ti,dac7571"पूर्ण,
	अणु.compatible = "ti,dac5574"पूर्ण,
	अणु.compatible = "ti,dac6574"पूर्ण,
	अणु.compatible = "ti,dac7574"पूर्ण,
	अणु.compatible = "ti,dac5573"पूर्ण,
	अणु.compatible = "ti,dac6573"पूर्ण,
	अणु.compatible = "ti,dac7573"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dac5571_of_id);

अटल स्थिर काष्ठा i2c_device_id dac5571_id[] = अणु
	अणु"dac5571", single_8bitपूर्ण,
	अणु"dac6571", single_10bitपूर्ण,
	अणु"dac7571", single_12bitपूर्ण,
	अणु"dac5574", quad_8bitपूर्ण,
	अणु"dac6574", quad_10bitपूर्ण,
	अणु"dac7574", quad_12bitपूर्ण,
	अणु"dac5573", quad_8bitपूर्ण,
	अणु"dac6573", quad_10bitपूर्ण,
	अणु"dac7573", quad_12bitपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dac5571_id);

अटल काष्ठा i2c_driver dac5571_driver = अणु
	.driver = अणु
		   .name = "ti-dac5571",
		   .of_match_table = dac5571_of_id,
	पूर्ण,
	.probe	  = dac5571_probe,
	.हटाओ   = dac5571_हटाओ,
	.id_table = dac5571_id,
पूर्ण;
module_i2c_driver(dac5571_driver);

MODULE_AUTHOR("Sean Nyekjaer <sean@geanix.dk>");
MODULE_DESCRIPTION("Texas Instruments 8/10/12-bit 1/4-channel DAC driver");
MODULE_LICENSE("GPL v2");
