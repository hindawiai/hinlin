<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * u-blox GNSS receiver driver
 *
 * Copyright (C) 2018 Johan Hovold <johan@kernel.org>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gnss.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/serdev.h>

#समावेश "serial.h"

काष्ठा ubx_data अणु
	काष्ठा regulator *v_bckp;
	काष्ठा regulator *vcc;
पूर्ण;

अटल पूर्णांक ubx_set_active(काष्ठा gnss_serial *gserial)
अणु
	काष्ठा ubx_data *data = gnss_serial_get_drvdata(gserial);
	पूर्णांक ret;

	ret = regulator_enable(data->vcc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ubx_set_standby(काष्ठा gnss_serial *gserial)
अणु
	काष्ठा ubx_data *data = gnss_serial_get_drvdata(gserial);
	पूर्णांक ret;

	ret = regulator_disable(data->vcc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ubx_set_घातer(काष्ठा gnss_serial *gserial,
				क्रमागत gnss_serial_pm_state state)
अणु
	चयन (state) अणु
	हाल GNSS_SERIAL_ACTIVE:
		वापस ubx_set_active(gserial);
	हाल GNSS_SERIAL_OFF:
	हाल GNSS_SERIAL_STANDBY:
		वापस ubx_set_standby(gserial);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा gnss_serial_ops ubx_gserial_ops = अणु
	.set_घातer = ubx_set_घातer,
पूर्ण;

अटल पूर्णांक ubx_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा gnss_serial *gserial;
	काष्ठा ubx_data *data;
	पूर्णांक ret;

	gserial = gnss_serial_allocate(serdev, माप(*data));
	अगर (IS_ERR(gserial)) अणु
		ret = PTR_ERR(gserial);
		वापस ret;
	पूर्ण

	gserial->ops = &ubx_gserial_ops;

	gserial->gdev->type = GNSS_TYPE_UBX;

	data = gnss_serial_get_drvdata(gserial);

	data->vcc = devm_regulator_get(&serdev->dev, "vcc");
	अगर (IS_ERR(data->vcc)) अणु
		ret = PTR_ERR(data->vcc);
		जाओ err_मुक्त_gserial;
	पूर्ण

	data->v_bckp = devm_regulator_get_optional(&serdev->dev, "v-bckp");
	अगर (IS_ERR(data->v_bckp)) अणु
		ret = PTR_ERR(data->v_bckp);
		अगर (ret == -ENODEV)
			data->v_bckp = शून्य;
		अन्यथा
			जाओ err_मुक्त_gserial;
	पूर्ण

	अगर (data->v_bckp) अणु
		ret = regulator_enable(data->v_bckp);
		अगर (ret)
			जाओ err_मुक्त_gserial;
	पूर्ण

	ret = gnss_serial_रेजिस्टर(gserial);
	अगर (ret)
		जाओ err_disable_v_bckp;

	वापस 0;

err_disable_v_bckp:
	अगर (data->v_bckp)
		regulator_disable(data->v_bckp);
err_मुक्त_gserial:
	gnss_serial_मुक्त(gserial);

	वापस ret;
पूर्ण

अटल व्योम ubx_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा gnss_serial *gserial = serdev_device_get_drvdata(serdev);
	काष्ठा ubx_data *data = gnss_serial_get_drvdata(gserial);

	gnss_serial_deरेजिस्टर(gserial);
	अगर (data->v_bckp)
		regulator_disable(data->v_bckp);
	gnss_serial_मुक्त(gserial);
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ubx_of_match[] = अणु
	अणु .compatible = "u-blox,neo-6m" पूर्ण,
	अणु .compatible = "u-blox,neo-8" पूर्ण,
	अणु .compatible = "u-blox,neo-m8" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ubx_of_match);
#पूर्ण_अगर

अटल काष्ठा serdev_device_driver ubx_driver = अणु
	.driver	= अणु
		.name		= "gnss-ubx",
		.of_match_table	= of_match_ptr(ubx_of_match),
		.pm		= &gnss_serial_pm_ops,
	पूर्ण,
	.probe	= ubx_probe,
	.हटाओ	= ubx_हटाओ,
पूर्ण;
module_serdev_device_driver(ubx_driver);

MODULE_AUTHOR("Johan Hovold <johan@kernel.org>");
MODULE_DESCRIPTION("u-blox GNSS receiver driver");
MODULE_LICENSE("GPL v2");
