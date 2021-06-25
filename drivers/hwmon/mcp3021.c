<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mcp3021.c - driver क्रम Microchip MCP3021 and MCP3221
 *
 * Copyright (C) 2008-2009, 2012 Freescale Semiconductor, Inc.
 * Author: Mingkai Hu <Mingkai.hu@मुक्तscale.com>
 * Reworked by Sven Schuchmann <schuchmann@schleissheimer.de>
 * DT support added by Clemens Gruber <clemens.gruber@pqgruber.com>
 *
 * This driver export the value of analog input voltage to sysfs, the
 * voltage unit is mV. Through the sysfs पूर्णांकerface, lm-sensors tool
 * can also display the input voltage.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

/* Vdd / reference voltage in millivolt */
#घोषणा MCP3021_VDD_REF_MAX	5500
#घोषणा MCP3021_VDD_REF_MIN	2700
#घोषणा MCP3021_VDD_REF_DEFAULT	3300

/* output क्रमmat */
#घोषणा MCP3021_SAR_SHIFT	2
#घोषणा MCP3021_SAR_MASK	0x3ff
#घोषणा MCP3021_OUTPUT_RES	10	/* 10-bit resolution */

#घोषणा MCP3221_SAR_SHIFT	0
#घोषणा MCP3221_SAR_MASK	0xfff
#घोषणा MCP3221_OUTPUT_RES	12	/* 12-bit resolution */

क्रमागत chips अणु
	mcp3021,
	mcp3221
पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */
काष्ठा mcp3021_data अणु
	काष्ठा device *hwmon_dev;
	u32 vdd;        /* supply and reference voltage in millivolt */
	u16 sar_shअगरt;
	u16 sar_mask;
	u8 output_res;
पूर्ण;

अटल पूर्णांक mcp3021_पढ़ो16(काष्ठा i2c_client *client)
अणु
	काष्ठा mcp3021_data *data = i2c_get_clientdata(client);
	पूर्णांक ret;
	u16 reg;
	__be16 buf;

	ret = i2c_master_recv(client, (अक्षर *)&buf, 2);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 2)
		वापस -EIO;

	/* The output code of the MCP3021 is transmitted with MSB first. */
	reg = be16_to_cpu(buf);

	/*
	 * The ten-bit output code is composed of the lower 4-bit of the
	 * first byte and the upper 6-bit of the second byte.
	 */
	reg = (reg >> data->sar_shअगरt) & data->sar_mask;

	वापस reg;
पूर्ण

अटल अंतरभूत u16 volts_from_reg(काष्ठा mcp3021_data *data, u16 val)
अणु
	वापस DIV_ROUND_CLOSEST(data->vdd * val, 1 << data->output_res);
पूर्ण

अटल sमाप_प्रकार in0_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mcp3021_data *data = i2c_get_clientdata(client);
	पूर्णांक reg, in_input;

	reg = mcp3021_पढ़ो16(client);
	अगर (reg < 0)
		वापस reg;

	in_input = volts_from_reg(data, reg);

	वापस प्र_लिखो(buf, "%d\n", in_input);
पूर्ण

अटल DEVICE_ATTR_RO(in0_input);

अटल स्थिर काष्ठा i2c_device_id mcp3021_id[];

अटल पूर्णांक mcp3021_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक err;
	काष्ठा mcp3021_data *data = शून्य;
	काष्ठा device_node *np = client->dev.of_node;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	data = devm_kzalloc(&client->dev, माप(काष्ठा mcp3021_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);

	अगर (np) अणु
		अगर (!of_property_पढ़ो_u32(np, "reference-voltage-microvolt",
					  &data->vdd))
			data->vdd /= 1000;
		अन्यथा
			data->vdd = MCP3021_VDD_REF_DEFAULT;
	पूर्ण अन्यथा अणु
		u32 *pdata = dev_get_platdata(&client->dev);

		अगर (pdata)
			data->vdd = *pdata;
		अन्यथा
			data->vdd = MCP3021_VDD_REF_DEFAULT;
	पूर्ण

	चयन (i2c_match_id(mcp3021_id, client)->driver_data) अणु
	हाल mcp3021:
		data->sar_shअगरt = MCP3021_SAR_SHIFT;
		data->sar_mask = MCP3021_SAR_MASK;
		data->output_res = MCP3021_OUTPUT_RES;
		अवरोध;

	हाल mcp3221:
		data->sar_shअगरt = MCP3221_SAR_SHIFT;
		data->sar_mask = MCP3221_SAR_MASK;
		data->output_res = MCP3221_OUTPUT_RES;
		अवरोध;
	पूर्ण

	अगर (data->vdd > MCP3021_VDD_REF_MAX || data->vdd < MCP3021_VDD_REF_MIN)
		वापस -EINVAL;

	err = sysfs_create_file(&client->dev.kobj, &dev_attr_in0_input.attr);
	अगर (err)
		वापस err;

	data->hwmon_dev = hwmon_device_रेजिस्टर(&client->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ;
	पूर्ण

	वापस 0;

निकास_हटाओ:
	sysfs_हटाओ_file(&client->dev.kobj, &dev_attr_in0_input.attr);
	वापस err;
पूर्ण

अटल पूर्णांक mcp3021_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mcp3021_data *data = i2c_get_clientdata(client);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_file(&client->dev.kobj, &dev_attr_in0_input.attr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mcp3021_id[] = अणु
	अणु "mcp3021", mcp3021 पूर्ण,
	अणु "mcp3221", mcp3221 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcp3021_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_mcp3021_match[] = अणु
	अणु .compatible = "microchip,mcp3021", .data = (व्योम *)mcp3021 पूर्ण,
	अणु .compatible = "microchip,mcp3221", .data = (व्योम *)mcp3221 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_mcp3021_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver mcp3021_driver = अणु
	.driver = अणु
		.name = "mcp3021",
		.of_match_table = of_match_ptr(of_mcp3021_match),
	पूर्ण,
	.probe_new = mcp3021_probe,
	.हटाओ = mcp3021_हटाओ,
	.id_table = mcp3021_id,
पूर्ण;

module_i2c_driver(mcp3021_driver);

MODULE_AUTHOR("Mingkai Hu <Mingkai.hu@freescale.com>");
MODULE_DESCRIPTION("Microchip MCP3021/MCP3221 driver");
MODULE_LICENSE("GPL");
