<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Bluetooth built-in chip control
 *
 * Copyright (c) 2008 Dmitry Baryshkov
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/rfसमाप्त.h>

#समावेश "tosa_bt.h"

अटल व्योम tosa_bt_on(काष्ठा tosa_bt_data *data)
अणु
	gpio_set_value(data->gpio_reset, 0);
	gpio_set_value(data->gpio_pwr, 1);
	gpio_set_value(data->gpio_reset, 1);
	mdelay(20);
	gpio_set_value(data->gpio_reset, 0);
पूर्ण

अटल व्योम tosa_bt_off(काष्ठा tosa_bt_data *data)
अणु
	gpio_set_value(data->gpio_reset, 1);
	mdelay(10);
	gpio_set_value(data->gpio_pwr, 0);
	gpio_set_value(data->gpio_reset, 0);
पूर्ण

अटल पूर्णांक tosa_bt_set_block(व्योम *data, bool blocked)
अणु
	pr_info("BT_RADIO going: %s\n", blocked ? "off" : "on");

	अगर (!blocked) अणु
		pr_info("TOSA_BT: going ON\n");
		tosa_bt_on(data);
	पूर्ण अन्यथा अणु
		pr_info("TOSA_BT: going OFF\n");
		tosa_bt_off(data);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops tosa_bt_rfसमाप्त_ops = अणु
	.set_block = tosa_bt_set_block,
पूर्ण;

अटल पूर्णांक tosa_bt_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक rc;
	काष्ठा rfसमाप्त *rfk;

	काष्ठा tosa_bt_data *data = dev->dev.platक्रमm_data;

	rc = gpio_request(data->gpio_reset, "Bluetooth reset");
	अगर (rc)
		जाओ err_reset;
	rc = gpio_direction_output(data->gpio_reset, 0);
	अगर (rc)
		जाओ err_reset_dir;
	rc = gpio_request(data->gpio_pwr, "Bluetooth power");
	अगर (rc)
		जाओ err_pwr;
	rc = gpio_direction_output(data->gpio_pwr, 0);
	अगर (rc)
		जाओ err_pwr_dir;

	rfk = rfसमाप्त_alloc("tosa-bt", &dev->dev, RFKILL_TYPE_BLUETOOTH,
			   &tosa_bt_rfसमाप्त_ops, data);
	अगर (!rfk) अणु
		rc = -ENOMEM;
		जाओ err_rfk_alloc;
	पूर्ण

	rc = rfसमाप्त_रेजिस्टर(rfk);
	अगर (rc)
		जाओ err_rfसमाप्त;

	platक्रमm_set_drvdata(dev, rfk);

	वापस 0;

err_rfसमाप्त:
	rfसमाप्त_destroy(rfk);
err_rfk_alloc:
	tosa_bt_off(data);
err_pwr_dir:
	gpio_मुक्त(data->gpio_pwr);
err_pwr:
err_reset_dir:
	gpio_मुक्त(data->gpio_reset);
err_reset:
	वापस rc;
पूर्ण

अटल पूर्णांक tosa_bt_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tosa_bt_data *data = dev->dev.platक्रमm_data;
	काष्ठा rfसमाप्त *rfk = platक्रमm_get_drvdata(dev);

	platक्रमm_set_drvdata(dev, शून्य);

	अगर (rfk) अणु
		rfसमाप्त_unरेजिस्टर(rfk);
		rfसमाप्त_destroy(rfk);
	पूर्ण
	rfk = शून्य;

	tosa_bt_off(data);

	gpio_मुक्त(data->gpio_pwr);
	gpio_मुक्त(data->gpio_reset);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tosa_bt_driver = अणु
	.probe = tosa_bt_probe,
	.हटाओ = tosa_bt_हटाओ,

	.driver = अणु
		.name = "tosa-bt",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tosa_bt_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dmitry Baryshkov");
MODULE_DESCRIPTION("Bluetooth built-in chip control");
