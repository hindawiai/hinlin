<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mcp4725.c - Support क्रम Microchip MCP4725/6
 *
 * Copyright (C) 2012 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * Based on max517 by Roland Stigge <stigge@antcom.de>
 *
 * driver क्रम the Microchip I2C 12-bit digital-to-analog converter (DAC)
 * (7-bit I2C slave address 0x60, the three LSBs can be configured in
 * hardware)
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश <linux/iio/dac/mcp4725.h>

#घोषणा MCP4725_DRV_NAME "mcp4725"

#घोषणा MCP472X_REF_VDD			0x00
#घोषणा MCP472X_REF_VREF_UNBUFFERED	0x02
#घोषणा MCP472X_REF_VREF_BUFFERED	0x03

काष्ठा mcp4725_data अणु
	काष्ठा i2c_client *client;
	पूर्णांक id;
	अचिन्हित ref_mode;
	bool vref_buffered;
	u16 dac_value;
	bool घातerकरोwn;
	अचिन्हित घातerकरोwn_mode;
	काष्ठा regulator *vdd_reg;
	काष्ठा regulator *vref_reg;
पूर्ण;

अटल पूर्णांक __maybe_unused mcp4725_suspend(काष्ठा device *dev)
अणु
	काष्ठा mcp4725_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	u8 outbuf[2];

	outbuf[0] = (data->घातerकरोwn_mode + 1) << 4;
	outbuf[1] = 0;
	data->घातerकरोwn = true;

	वापस i2c_master_send(data->client, outbuf, 2);
पूर्ण

अटल पूर्णांक __maybe_unused mcp4725_resume(काष्ठा device *dev)
अणु
	काष्ठा mcp4725_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	u8 outbuf[2];

	/* restore previous DAC value */
	outbuf[0] = (data->dac_value >> 8) & 0xf;
	outbuf[1] = data->dac_value & 0xff;
	data->घातerकरोwn = false;

	वापस i2c_master_send(data->client, outbuf, 2);
पूर्ण
अटल SIMPLE_DEV_PM_OPS(mcp4725_pm_ops, mcp4725_suspend, mcp4725_resume);

अटल sमाप_प्रकार mcp4725_store_eeprom(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);
	पूर्णांक tries = 20;
	u8 inoutbuf[3];
	bool state;
	पूर्णांक ret;

	ret = strtobool(buf, &state);
	अगर (ret < 0)
		वापस ret;

	अगर (!state)
		वापस 0;

	inoutbuf[0] = 0x60; /* ग_लिखो EEPROM */
	inoutbuf[0] |= data->ref_mode << 3;
	inoutbuf[0] |= data->घातerकरोwn ? ((data->घातerकरोwn_mode + 1) << 1) : 0;
	inoutbuf[1] = data->dac_value >> 4;
	inoutbuf[2] = (data->dac_value & 0xf) << 4;

	ret = i2c_master_send(data->client, inoutbuf, 3);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != 3)
		वापस -EIO;

	/* रुको क्रम ग_लिखो complete, takes up to 50ms */
	जबतक (tries--) अणु
		msleep(20);
		ret = i2c_master_recv(data->client, inoutbuf, 3);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret != 3)
			वापस -EIO;

		अगर (inoutbuf[0] & 0x80)
			अवरोध;
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(&data->client->dev,
			"mcp4725_store_eeprom() failed, incomplete\n");
		वापस -EIO;
	पूर्ण

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(store_eeprom, S_IWUSR, शून्य, mcp4725_store_eeprom, 0);

अटल काष्ठा attribute *mcp4725_attributes[] = अणु
	&iio_dev_attr_store_eeprom.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mcp4725_attribute_group = अणु
	.attrs = mcp4725_attributes,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mcp4725_घातerकरोwn_modes[] = अणु
	"1kohm_to_gnd",
	"100kohm_to_gnd",
	"500kohm_to_gnd"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mcp4726_घातerकरोwn_modes[] = अणु
	"1kohm_to_gnd",
	"125kohm_to_gnd",
	"640kohm_to_gnd"
पूर्ण;

अटल पूर्णांक mcp4725_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);

	वापस data->घातerकरोwn_mode;
पूर्ण

अटल पूर्णांक mcp4725_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित mode)
अणु
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);

	data->घातerकरोwn_mode = mode;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mcp4725_पढ़ो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", data->घातerकरोwn);
पूर्ण

अटल sमाप_प्रकार mcp4725_ग_लिखो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	 uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan,
	 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);
	bool state;
	पूर्णांक ret;

	ret = strtobool(buf, &state);
	अगर (ret)
		वापस ret;

	अगर (state)
		ret = mcp4725_suspend(&data->client->dev);
	अन्यथा
		ret = mcp4725_resume(&data->client->dev);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

क्रमागत chip_id अणु
	MCP4725,
	MCP4726,
पूर्ण;

अटल स्थिर काष्ठा iio_क्रमागत mcp472x_घातerकरोwn_mode_क्रमागत[] = अणु
	[MCP4725] = अणु
		.items = mcp4725_घातerकरोwn_modes,
		.num_items = ARRAY_SIZE(mcp4725_घातerकरोwn_modes),
		.get = mcp4725_get_घातerकरोwn_mode,
		.set = mcp4725_set_घातerकरोwn_mode,
	पूर्ण,
	[MCP4726] = अणु
		.items = mcp4726_घातerकरोwn_modes,
		.num_items = ARRAY_SIZE(mcp4726_घातerकरोwn_modes),
		.get = mcp4725_get_घातerकरोwn_mode,
		.set = mcp4725_set_घातerकरोwn_mode,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info mcp4725_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = mcp4725_पढ़ो_घातerकरोwn,
		.ग_लिखो = mcp4725_ग_लिखो_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SEPARATE,
			&mcp472x_घातerकरोwn_mode_क्रमागत[MCP4725]),
	IIO_ENUM_AVAILABLE("powerdown_mode",
			&mcp472x_घातerकरोwn_mode_क्रमागत[MCP4725]),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info mcp4726_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = mcp4725_पढ़ो_घातerकरोwn,
		.ग_लिखो = mcp4725_ग_लिखो_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SEPARATE,
			&mcp472x_घातerकरोwn_mode_क्रमागत[MCP4726]),
	IIO_ENUM_AVAILABLE("powerdown_mode",
			&mcp472x_घातerकरोwn_mode_क्रमागत[MCP4726]),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mcp472x_channel[] = अणु
	[MCP4725] = अणु
		.type		= IIO_VOLTAGE,
		.indexed	= 1,
		.output		= 1,
		.channel	= 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.ext_info	= mcp4725_ext_info,
	पूर्ण,
	[MCP4726] = अणु
		.type		= IIO_VOLTAGE,
		.indexed	= 1,
		.output		= 1,
		.channel	= 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.ext_info	= mcp4726_ext_info,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mcp4725_set_value(काष्ठा iio_dev *indio_dev, पूर्णांक val)
अणु
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);
	u8 outbuf[2];
	पूर्णांक ret;

	अगर (val >= (1 << 12) || val < 0)
		वापस -EINVAL;

	outbuf[0] = (val >> 8) & 0xf;
	outbuf[1] = val & 0xff;

	ret = i2c_master_send(data->client, outbuf, 2);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != 2)
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक mcp4726_set_cfg(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);
	u8 outbuf[3];
	पूर्णांक ret;

	outbuf[0] = 0x40;
	outbuf[0] |= data->ref_mode << 3;
	अगर (data->घातerकरोwn)
		outbuf[0] |= data->घातerकरोwn << 1;
	outbuf[1] = data->dac_value >> 4;
	outbuf[2] = (data->dac_value & 0xf) << 4;

	ret = i2c_master_send(data->client, outbuf, 3);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != 3)
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक mcp4725_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = data->dac_value;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (data->ref_mode == MCP472X_REF_VDD)
			ret = regulator_get_voltage(data->vdd_reg);
		अन्यथा
			ret = regulator_get_voltage(data->vref_reg);

		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000;
		*val2 = 12;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mcp4725_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = mcp4725_set_value(indio_dev, val);
		data->dac_value = val;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info mcp4725_info = अणु
	.पढ़ो_raw = mcp4725_पढ़ो_raw,
	.ग_लिखो_raw = mcp4725_ग_लिखो_raw,
	.attrs = &mcp4725_attribute_group,
पूर्ण;

अटल पूर्णांक mcp4725_probe_dt(काष्ठा device *dev,
			    काष्ठा mcp4725_platक्रमm_data *pdata)
अणु
	/* check अगर is the vref-supply defined */
	pdata->use_vref = device_property_पढ़ो_bool(dev, "vref-supply");
	pdata->vref_buffered =
		device_property_पढ़ो_bool(dev, "microchip,vref-buffered");

	वापस 0;
पूर्ण

अटल पूर्णांक mcp4725_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mcp4725_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा mcp4725_platक्रमm_data *pdata, pdata_dt;
	u8 inbuf[4];
	u8 pd;
	u8 ref;
	पूर्णांक err;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;
	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	अगर (dev_fwnode(&client->dev))
		data->id = (क्रमागत chip_id)device_get_match_data(&client->dev);
	अन्यथा
		data->id = id->driver_data;
	pdata = dev_get_platdata(&client->dev);

	अगर (!pdata) अणु
		err = mcp4725_probe_dt(&client->dev, &pdata_dt);
		अगर (err) अणु
			dev_err(&client->dev,
				"invalid platform or devicetree data");
			वापस err;
		पूर्ण
		pdata = &pdata_dt;
	पूर्ण

	अगर (data->id == MCP4725 && pdata->use_vref) अणु
		dev_err(&client->dev,
			"external reference is unavailable on MCP4725");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata->use_vref && pdata->vref_buffered) अणु
		dev_err(&client->dev,
			"buffering is unavailable on the internal reference");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata->use_vref)
		data->ref_mode = MCP472X_REF_VDD;
	अन्यथा
		data->ref_mode = pdata->vref_buffered ?
			MCP472X_REF_VREF_BUFFERED :
			MCP472X_REF_VREF_UNBUFFERED;

	data->vdd_reg = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(data->vdd_reg))
		वापस PTR_ERR(data->vdd_reg);

	err = regulator_enable(data->vdd_reg);
	अगर (err)
		वापस err;

	अगर (pdata->use_vref) अणु
		data->vref_reg = devm_regulator_get(&client->dev, "vref");
		अगर (IS_ERR(data->vref_reg)) अणु
			err = PTR_ERR(data->vref_reg);
			जाओ err_disable_vdd_reg;
		पूर्ण

		err = regulator_enable(data->vref_reg);
		अगर (err)
			जाओ err_disable_vdd_reg;
	पूर्ण

	indio_dev->name = id->name;
	indio_dev->info = &mcp4725_info;
	indio_dev->channels = &mcp472x_channel[id->driver_data];
	indio_dev->num_channels = 1;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	/* पढ़ो current DAC value and settings */
	err = i2c_master_recv(client, inbuf, data->id == MCP4725 ? 3 : 4);

	अगर (err < 0) अणु
		dev_err(&client->dev, "failed to read DAC value");
		जाओ err_disable_vref_reg;
	पूर्ण
	pd = (inbuf[0] >> 1) & 0x3;
	data->घातerकरोwn = pd > 0;
	data->घातerकरोwn_mode = pd ? pd - 1 : 2; /* largest resistor to gnd */
	data->dac_value = (inbuf[1] << 4) | (inbuf[2] >> 4);
	अगर (data->id == MCP4726)
		ref = (inbuf[3] >> 3) & 0x3;

	अगर (data->id == MCP4726 && ref != data->ref_mode) अणु
		dev_info(&client->dev,
			"voltage reference mode differs (conf: %u, eeprom: %u), setting %u",
			data->ref_mode, ref, data->ref_mode);
		err = mcp4726_set_cfg(indio_dev);
		अगर (err < 0)
			जाओ err_disable_vref_reg;
	पूर्ण
 
	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err)
		जाओ err_disable_vref_reg;

	वापस 0;

err_disable_vref_reg:
	अगर (data->vref_reg)
		regulator_disable(data->vref_reg);

err_disable_vdd_reg:
	regulator_disable(data->vdd_reg);

	वापस err;
पूर्ण

अटल पूर्णांक mcp4725_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा mcp4725_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (data->vref_reg)
		regulator_disable(data->vref_reg);
	regulator_disable(data->vdd_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mcp4725_id[] = अणु
	अणु "mcp4725", MCP4725 पूर्ण,
	अणु "mcp4726", MCP4726 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcp4725_id);

अटल स्थिर काष्ठा of_device_id mcp4725_of_match[] = अणु
	अणु
		.compatible = "microchip,mcp4725",
		.data = (व्योम *)MCP4725
	पूर्ण,
	अणु
		.compatible = "microchip,mcp4726",
		.data = (व्योम *)MCP4726
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp4725_of_match);

अटल काष्ठा i2c_driver mcp4725_driver = अणु
	.driver = अणु
		.name	= MCP4725_DRV_NAME,
		.of_match_table = mcp4725_of_match,
		.pm	= &mcp4725_pm_ops,
	पूर्ण,
	.probe		= mcp4725_probe,
	.हटाओ		= mcp4725_हटाओ,
	.id_table	= mcp4725_id,
पूर्ण;
module_i2c_driver(mcp4725_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("MCP4725/6 12-bit DAC");
MODULE_LICENSE("GPL");
