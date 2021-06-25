<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV sensor code
 *
 * Copyright (C) 2013 IBM
 */

#समावेश <linux/delay.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/machdep.h>

/*
 * This will वापस sensor inक्रमmation to driver based on the requested sensor
 * handle. A handle is an opaque id क्रम the घातernv, पढ़ो by the driver from the
 * device tree..
 */
पूर्णांक opal_get_sensor_data(u32 sensor_hndl, u32 *sensor_data)
अणु
	पूर्णांक ret, token;
	काष्ठा opal_msg msg;
	__be32 data;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0)
		वापस token;

	ret = opal_sensor_पढ़ो(sensor_hndl, token, &data);
	चयन (ret) अणु
	हाल OPAL_ASYNC_COMPLETION:
		ret = opal_async_रुको_response(token, &msg);
		अगर (ret) अणु
			pr_err("%s: Failed to wait for the async response, %d\n",
			       __func__, ret);
			जाओ out;
		पूर्ण

		ret = opal_error_code(opal_get_async_rc(msg));
		*sensor_data = be32_to_cpu(data);
		अवरोध;

	हाल OPAL_SUCCESS:
		ret = 0;
		*sensor_data = be32_to_cpu(data);
		अवरोध;

	हाल OPAL_WRONG_STATE:
		ret = -EIO;
		अवरोध;

	शेष:
		ret = opal_error_code(ret);
		अवरोध;
	पूर्ण

out:
	opal_async_release_token(token);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(opal_get_sensor_data);

पूर्णांक opal_get_sensor_data_u64(u32 sensor_hndl, u64 *sensor_data)
अणु
	पूर्णांक ret, token;
	काष्ठा opal_msg msg;
	__be64 data;

	अगर (!opal_check_token(OPAL_SENSOR_READ_U64)) अणु
		u32 sdata;

		ret = opal_get_sensor_data(sensor_hndl, &sdata);
		अगर (!ret)
			*sensor_data = sdata;
		वापस ret;
	पूर्ण

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0)
		वापस token;

	ret = opal_sensor_पढ़ो_u64(sensor_hndl, token, &data);
	चयन (ret) अणु
	हाल OPAL_ASYNC_COMPLETION:
		ret = opal_async_रुको_response(token, &msg);
		अगर (ret) अणु
			pr_err("%s: Failed to wait for the async response, %d\n",
			       __func__, ret);
			जाओ out_token;
		पूर्ण

		ret = opal_error_code(opal_get_async_rc(msg));
		*sensor_data = be64_to_cpu(data);
		अवरोध;

	हाल OPAL_SUCCESS:
		ret = 0;
		*sensor_data = be64_to_cpu(data);
		अवरोध;

	हाल OPAL_WRONG_STATE:
		ret = -EIO;
		अवरोध;

	शेष:
		ret = opal_error_code(ret);
		अवरोध;
	पूर्ण

out_token:
	opal_async_release_token(token);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(opal_get_sensor_data_u64);

पूर्णांक __init opal_sensor_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *sensor;

	sensor = of_find_node_by_path("/ibm,opal/sensors");
	अगर (!sensor) अणु
		pr_err("Opal node 'sensors' not found\n");
		वापस -ENODEV;
	पूर्ण

	pdev = of_platक्रमm_device_create(sensor, "opal-sensor", शून्य);
	of_node_put(sensor);

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण
