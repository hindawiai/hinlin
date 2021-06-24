<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mediatek GNSS receiver driver
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

काष्ठा mtk_data अणु
	काष्ठा regulator *vbackup;
	काष्ठा regulator *vcc;
पूर्ण;

अटल पूर्णांक mtk_set_active(काष्ठा gnss_serial *gserial)
अणु
	काष्ठा mtk_data *data = gnss_serial_get_drvdata(gserial);
	पूर्णांक ret;

	ret = regulator_enable(data->vcc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_set_standby(काष्ठा gnss_serial *gserial)
अणु
	काष्ठा mtk_data *data = gnss_serial_get_drvdata(gserial);
	पूर्णांक ret;

	ret = regulator_disable(data->vcc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_set_घातer(काष्ठा gnss_serial *gserial,
			 क्रमागत gnss_serial_pm_state state)
अणु
	चयन (state) अणु
	हाल GNSS_SERIAL_ACTIVE:
		वापस mtk_set_active(gserial);
	हाल GNSS_SERIAL_OFF:
	हाल GNSS_SERIAL_STANDBY:
		वापस mtk_set_standby(gserial);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा gnss_serial_ops mtk_gserial_ops = अणु
	.set_घातer = mtk_set_घातer,
पूर्ण;

अटल पूर्णांक mtk_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा gnss_serial *gserial;
	काष्ठा mtk_data *data;
	पूर्णांक ret;

	gserial = gnss_serial_allocate(serdev, माप(*data));
	अगर (IS_ERR(gserial)) अणु
		ret = PTR_ERR(gserial);
		वापस ret;
	पूर्ण

	gserial->ops = &mtk_gserial_ops;

	gserial->gdev->type = GNSS_TYPE_MTK;

	data = gnss_serial_get_drvdata(gserial);

	data->vcc = devm_regulator_get(&serdev->dev, "vcc");
	अगर (IS_ERR(data->vcc)) अणु
		ret = PTR_ERR(data->vcc);
		जाओ err_मुक्त_gserial;
	पूर्ण

	data->vbackup = devm_regulator_get_optional(&serdev->dev, "vbackup");
	अगर (IS_ERR(data->vbackup)) अणु
		ret = PTR_ERR(data->vbackup);
		अगर (ret == -ENODEV)
			data->vbackup = शून्य;
		अन्यथा
			जाओ err_मुक्त_gserial;
	पूर्ण

	अगर (data->vbackup) अणु
		ret = regulator_enable(data->vbackup);
		अगर (ret)
			जाओ err_मुक्त_gserial;
	पूर्ण

	ret = gnss_serial_रेजिस्टर(gserial);
	अगर (ret)
		जाओ err_disable_vbackup;

	वापस 0;

err_disable_vbackup:
	अगर (data->vbackup)
		regulator_disable(data->vbackup);
err_मुक्त_gserial:
	gnss_serial_मुक्त(gserial);

	वापस ret;
पूर्ण

अटल व्योम mtk_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा gnss_serial *gserial = serdev_device_get_drvdata(serdev);
	काष्ठा mtk_data *data = gnss_serial_get_drvdata(gserial);

	gnss_serial_deरेजिस्टर(gserial);
	अगर (data->vbackup)
		regulator_disable(data->vbackup);
	gnss_serial_मुक्त(gserial);
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mtk_of_match[] = अणु
	अणु .compatible = "globaltop,pa6h" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_of_match);
#पूर्ण_अगर

अटल काष्ठा serdev_device_driver mtk_driver = अणु
	.driver	= अणु
		.name		= "gnss-mtk",
		.of_match_table	= of_match_ptr(mtk_of_match),
		.pm		= &gnss_serial_pm_ops,
	पूर्ण,
	.probe	= mtk_probe,
	.हटाओ	= mtk_हटाओ,
पूर्ण;
module_serdev_device_driver(mtk_driver);

MODULE_AUTHOR("Loys Ollivier <lollivier@baylibre.com>");
MODULE_DESCRIPTION("Mediatek GNSS receiver driver");
MODULE_LICENSE("GPL v2");
