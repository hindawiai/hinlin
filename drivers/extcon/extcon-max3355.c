<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Maxim Integrated MAX3355 USB OTG chip extcon driver
 *
 * Copyright (C)  2014-2015 Cogent Embedded, Inc.
 * Author: Sergei Shtylyov <sergei.shtylyov@cogentembedded.com>
 */

#समावेश <linux/extcon-provider.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा max3355_data अणु
	काष्ठा extcon_dev *edev;
	काष्ठा gpio_desc *id_gpiod;
	काष्ठा gpio_desc *shdn_gpiod;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max3355_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल irqवापस_t max3355_id_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा max3355_data *data = dev_id;
	पूर्णांक id = gpiod_get_value_cansleep(data->id_gpiod);

	अगर (id) अणु
		/*
		 * ID = 1 means USB HOST cable detached.
		 * As we करोn't have event क्रम USB peripheral cable attached,
		 * we simulate USB peripheral attach here.
		 */
		extcon_set_state_sync(data->edev, EXTCON_USB_HOST, false);
		extcon_set_state_sync(data->edev, EXTCON_USB, true);
	पूर्ण अन्यथा अणु
		/*
		 * ID = 0 means USB HOST cable attached.
		 * As we करोn't have event क्रम USB peripheral cable detached,
		 * we simulate USB peripheral detach here.
		 */
		extcon_set_state_sync(data->edev, EXTCON_USB, false);
		extcon_set_state_sync(data->edev, EXTCON_USB_HOST, true);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max3355_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max3355_data *data;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक irq, err;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा max3355_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	gpiod = devm_gpiod_get(&pdev->dev, "id", GPIOD_IN);
	अगर (IS_ERR(gpiod)) अणु
		dev_err(&pdev->dev, "failed to get ID_OUT GPIO\n");
		वापस PTR_ERR(gpiod);
	पूर्ण
	data->id_gpiod = gpiod;

	gpiod = devm_gpiod_get(&pdev->dev, "maxim,shdn", GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpiod)) अणु
		dev_err(&pdev->dev, "failed to get SHDN# GPIO\n");
		वापस PTR_ERR(gpiod);
	पूर्ण
	data->shdn_gpiod = gpiod;

	data->edev = devm_extcon_dev_allocate(&pdev->dev, max3355_cable);
	अगर (IS_ERR(data->edev)) अणु
		dev_err(&pdev->dev, "failed to allocate extcon device\n");
		वापस PTR_ERR(data->edev);
	पूर्ण

	err = devm_extcon_dev_रेजिस्टर(&pdev->dev, data->edev);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register extcon device\n");
		वापस err;
	पूर्ण

	irq = gpiod_to_irq(data->id_gpiod);
	अगर (irq < 0) अणु
		dev_err(&pdev->dev, "failed to translate ID_OUT GPIO to IRQ\n");
		वापस irq;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य, max3355_id_irq,
					IRQF_ONESHOT | IRQF_NO_SUSPEND |
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING,
					pdev->name, data);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to request ID_OUT IRQ\n");
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	/* Perक्रमm initial detection */
	max3355_id_irq(irq, data);

	वापस 0;
पूर्ण

अटल पूर्णांक max3355_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max3355_data *data = platक्रमm_get_drvdata(pdev);

	gpiod_set_value_cansleep(data->shdn_gpiod, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id max3355_match_table[] = अणु
	अणु .compatible = "maxim,max3355", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max3355_match_table);

अटल काष्ठा platक्रमm_driver max3355_driver = अणु
	.probe		= max3355_probe,
	.हटाओ		= max3355_हटाओ,
	.driver		= अणु
		.name	= "extcon-max3355",
		.of_match_table = max3355_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(max3355_driver);

MODULE_AUTHOR("Sergei Shtylyov <sergei.shtylyov@cogentembedded.com>");
MODULE_DESCRIPTION("Maxim MAX3355 extcon driver");
MODULE_LICENSE("GPL v2");
