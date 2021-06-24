<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018-2020 NXP.
 */

#समावेश <dt-bindings/firmware/imx/rsrc.h>
#समावेश <linux/err.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_core.h"
#समावेश "thermal_hwmon.h"

#घोषणा IMX_SC_MISC_FUNC_GET_TEMP	13

अटल काष्ठा imx_sc_ipc *thermal_ipc_handle;

काष्ठा imx_sc_sensor अणु
	काष्ठा thermal_zone_device *tzd;
	u32 resource_id;
पूर्ण;

काष्ठा req_get_temp अणु
	u16 resource_id;
	u8 type;
पूर्ण __packed __aligned(4);

काष्ठा resp_get_temp अणु
	s16 celsius;
	s8 tenths;
पूर्ण __packed __aligned(4);

काष्ठा imx_sc_msg_misc_get_temp अणु
	काष्ठा imx_sc_rpc_msg hdr;
	जोड़ अणु
		काष्ठा req_get_temp req;
		काष्ठा resp_get_temp resp;
	पूर्ण data;
पूर्ण __packed __aligned(4);

अटल पूर्णांक imx_sc_thermal_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा imx_sc_msg_misc_get_temp msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	काष्ठा imx_sc_sensor *sensor = data;
	पूर्णांक ret;

	msg.data.req.resource_id = sensor->resource_id;
	msg.data.req.type = IMX_SC_C_TEMP;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_MISC;
	hdr->func = IMX_SC_MISC_FUNC_GET_TEMP;
	hdr->size = 2;

	ret = imx_scu_call_rpc(thermal_ipc_handle, &msg, true);
	अगर (ret) अणु
		dev_err(&sensor->tzd->device, "read temp sensor %d failed, ret %d\n",
			sensor->resource_id, ret);
		वापस ret;
	पूर्ण

	*temp = msg.data.resp.celsius * 1000 + msg.data.resp.tenths * 100;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops imx_sc_thermal_ops = अणु
	.get_temp = imx_sc_thermal_get_temp,
पूर्ण;

अटल पूर्णांक imx_sc_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np, *child, *sensor_np;
	काष्ठा imx_sc_sensor *sensor;
	पूर्णांक ret;

	ret = imx_scu_get_handle(&thermal_ipc_handle);
	अगर (ret)
		वापस ret;

	np = of_find_node_by_name(शून्य, "thermal-zones");
	अगर (!np)
		वापस -ENODEV;

	sensor_np = of_node_get(pdev->dev.of_node);

	क्रम_each_available_child_of_node(np, child) अणु
		sensor = devm_kzalloc(&pdev->dev, माप(*sensor), GFP_KERNEL);
		अगर (!sensor) अणु
			of_node_put(sensor_np);
			वापस -ENOMEM;
		पूर्ण

		ret = thermal_zone_of_get_sensor_id(child,
						    sensor_np,
						    &sensor->resource_id);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev,
				"failed to get valid sensor resource id: %d\n",
				ret);
			अवरोध;
		पूर्ण

		sensor->tzd = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev,
								   sensor->resource_id,
								   sensor,
								   &imx_sc_thermal_ops);
		अगर (IS_ERR(sensor->tzd)) अणु
			dev_err(&pdev->dev, "failed to register thermal zone\n");
			ret = PTR_ERR(sensor->tzd);
			अवरोध;
		पूर्ण

		अगर (devm_thermal_add_hwmon_sysfs(sensor->tzd))
			dev_warn(&pdev->dev, "failed to add hwmon sysfs attributes\n");
	पूर्ण

	of_node_put(sensor_np);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_sc_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_sc_thermal_table[] = अणु
	अणु .compatible = "fsl,imx-sc-thermal", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_sc_thermal_table);

अटल काष्ठा platक्रमm_driver imx_sc_thermal_driver = अणु
		.probe = imx_sc_thermal_probe,
		.हटाओ	= imx_sc_thermal_हटाओ,
		.driver = अणु
			.name = "imx-sc-thermal",
			.of_match_table = imx_sc_thermal_table,
		पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_sc_thermal_driver);

MODULE_AUTHOR("Anson Huang <Anson.Huang@nxp.com>");
MODULE_DESCRIPTION("Thermal driver for NXP i.MX SoCs with system controller");
MODULE_LICENSE("GPL v2");
