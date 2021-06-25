<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright 2020 Google LLC.

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

काष्ठा cros_ec_regulator_data अणु
	काष्ठा regulator_desc desc;
	काष्ठा regulator_dev *dev;
	काष्ठा cros_ec_device *ec_dev;

	u32 index;

	u16 *voltages_mV;
	u16 num_voltages;
पूर्ण;

अटल पूर्णांक cros_ec_cmd(काष्ठा cros_ec_device *ec, u32 version, u32 command,
		       व्योम *outdata, u32 outsize, व्योम *indata, u32 insize)
अणु
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = kzalloc(माप(*msg) + max(outsize, insize), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->version = version;
	msg->command = command;
	msg->outsize = outsize;
	msg->insize = insize;

	अगर (outdata && outsize > 0)
		स_नकल(msg->data, outdata, outsize);

	ret = cros_ec_cmd_xfer_status(ec, msg);
	अगर (ret < 0)
		जाओ cleanup;

	अगर (insize)
		स_नकल(indata, msg->data, insize);

cleanup:
	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_regulator_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा cros_ec_regulator_data *data = rdev_get_drvdata(dev);
	काष्ठा ec_params_regulator_enable cmd = अणु
		.index = data->index,
		.enable = 1,
	पूर्ण;

	वापस cros_ec_cmd(data->ec_dev, 0, EC_CMD_REGULATOR_ENABLE, &cmd,
			  माप(cmd), शून्य, 0);
पूर्ण

अटल पूर्णांक cros_ec_regulator_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा cros_ec_regulator_data *data = rdev_get_drvdata(dev);
	काष्ठा ec_params_regulator_enable cmd = अणु
		.index = data->index,
		.enable = 0,
	पूर्ण;

	वापस cros_ec_cmd(data->ec_dev, 0, EC_CMD_REGULATOR_ENABLE, &cmd,
			  माप(cmd), शून्य, 0);
पूर्ण

अटल पूर्णांक cros_ec_regulator_is_enabled(काष्ठा regulator_dev *dev)
अणु
	काष्ठा cros_ec_regulator_data *data = rdev_get_drvdata(dev);
	काष्ठा ec_params_regulator_is_enabled cmd = अणु
		.index = data->index,
	पूर्ण;
	काष्ठा ec_response_regulator_is_enabled resp;
	पूर्णांक ret;

	ret = cros_ec_cmd(data->ec_dev, 0, EC_CMD_REGULATOR_IS_ENABLED, &cmd,
			  माप(cmd), &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;
	वापस resp.enabled;
पूर्ण

अटल पूर्णांक cros_ec_regulator_list_voltage(काष्ठा regulator_dev *dev,
					  अचिन्हित पूर्णांक selector)
अणु
	काष्ठा cros_ec_regulator_data *data = rdev_get_drvdata(dev);

	अगर (selector >= data->num_voltages)
		वापस -EINVAL;

	वापस data->voltages_mV[selector] * 1000;
पूर्ण

अटल पूर्णांक cros_ec_regulator_get_voltage(काष्ठा regulator_dev *dev)
अणु
	काष्ठा cros_ec_regulator_data *data = rdev_get_drvdata(dev);
	काष्ठा ec_params_regulator_get_voltage cmd = अणु
		.index = data->index,
	पूर्ण;
	काष्ठा ec_response_regulator_get_voltage resp;
	पूर्णांक ret;

	ret = cros_ec_cmd(data->ec_dev, 0, EC_CMD_REGULATOR_GET_VOLTAGE, &cmd,
			  माप(cmd), &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;
	वापस resp.voltage_mv * 1000;
पूर्ण

अटल पूर्णांक cros_ec_regulator_set_voltage(काष्ठा regulator_dev *dev, पूर्णांक min_uV,
					 पूर्णांक max_uV, अचिन्हित पूर्णांक *selector)
अणु
	काष्ठा cros_ec_regulator_data *data = rdev_get_drvdata(dev);
	पूर्णांक min_mV = DIV_ROUND_UP(min_uV, 1000);
	पूर्णांक max_mV = max_uV / 1000;
	काष्ठा ec_params_regulator_set_voltage cmd = अणु
		.index = data->index,
		.min_mv = min_mV,
		.max_mv = max_mV,
	पूर्ण;

	/*
	 * This can happen when the given range [min_uV, max_uV] करोesn't
	 * contain any voltage that can be represented exactly in mV.
	 */
	अगर (min_mV > max_mV)
		वापस -EINVAL;

	वापस cros_ec_cmd(data->ec_dev, 0, EC_CMD_REGULATOR_SET_VOLTAGE, &cmd,
			   माप(cmd), शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा regulator_ops cros_ec_regulator_voltage_ops = अणु
	.enable = cros_ec_regulator_enable,
	.disable = cros_ec_regulator_disable,
	.is_enabled = cros_ec_regulator_is_enabled,
	.list_voltage = cros_ec_regulator_list_voltage,
	.get_voltage = cros_ec_regulator_get_voltage,
	.set_voltage = cros_ec_regulator_set_voltage,
पूर्ण;

अटल पूर्णांक cros_ec_regulator_init_info(काष्ठा device *dev,
				       काष्ठा cros_ec_regulator_data *data)
अणु
	काष्ठा ec_params_regulator_get_info cmd = अणु
		.index = data->index,
	पूर्ण;
	काष्ठा ec_response_regulator_get_info resp;
	पूर्णांक ret;

	ret = cros_ec_cmd(data->ec_dev, 0, EC_CMD_REGULATOR_GET_INFO, &cmd,
			   माप(cmd), &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	data->num_voltages =
		min_t(u16, ARRAY_SIZE(resp.voltages_mv), resp.num_voltages);
	data->voltages_mV =
		devm_kmemdup(dev, resp.voltages_mv,
			     माप(u16) * data->num_voltages, GFP_KERNEL);
	अगर (!data->voltages_mV)
		वापस -ENOMEM;

	data->desc.n_voltages = data->num_voltages;

	/* Make sure the वापसed name is always a valid string */
	resp.name[ARRAY_SIZE(resp.name) - 1] = '\0';
	data->desc.name = devm_kstrdup(dev, resp.name, GFP_KERNEL);
	अगर (!data->desc.name)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा cros_ec_regulator_data *drvdata;
	काष्ठा regulator_init_data *init_data;
	काष्ठा regulator_config cfg = अणुपूर्ण;
	काष्ठा regulator_desc *desc;
	पूर्णांक ret;

	drvdata = devm_kzalloc(
		&pdev->dev, माप(काष्ठा cros_ec_regulator_data), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->ec_dev = dev_get_drvdata(dev->parent);
	desc = &drvdata->desc;

	init_data = of_get_regulator_init_data(dev, np, desc);
	अगर (!init_data)
		वापस -EINVAL;

	ret = of_property_पढ़ो_u32(np, "reg", &drvdata->index);
	अगर (ret < 0)
		वापस ret;

	desc->owner = THIS_MODULE;
	desc->type = REGULATOR_VOLTAGE;
	desc->ops = &cros_ec_regulator_voltage_ops;

	ret = cros_ec_regulator_init_info(dev, drvdata);
	अगर (ret < 0)
		वापस ret;

	cfg.dev = &pdev->dev;
	cfg.init_data = init_data;
	cfg.driver_data = drvdata;
	cfg.of_node = np;

	drvdata->dev = devm_regulator_रेजिस्टर(dev, &drvdata->desc, &cfg);
	अगर (IS_ERR(drvdata->dev)) अणु
		ret = PTR_ERR(drvdata->dev);
		dev_err(&pdev->dev, "Failed to register regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, drvdata);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id regulator_cros_ec_of_match[] = अणु
	अणु .compatible = "google,cros-ec-regulator", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, regulator_cros_ec_of_match);

अटल काष्ठा platक्रमm_driver cros_ec_regulator_driver = अणु
	.probe		= cros_ec_regulator_probe,
	.driver		= अणु
		.name		= "cros-ec-regulator",
		.of_match_table = regulator_cros_ec_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cros_ec_regulator_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChromeOS EC controlled regulator");
MODULE_AUTHOR("Pi-Hsun Shih <pihsun@chromium.org>");
