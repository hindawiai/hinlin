<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mfd/ucb1x00-assabet.c
 *
 *  Copyright (C) 2001-2003 Russell King, All Rights Reserved.
 *
 *  We handle the machine-specअगरic bits of the UCB1x00 driver here.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mfd/ucb1x00.h>

#घोषणा UCB1X00_ATTR(name,input)\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			   अक्षर *buf)	\
अणु								\
	काष्ठा ucb1x00 *ucb = classdev_to_ucb1x00(dev);		\
	पूर्णांक val;						\
	ucb1x00_adc_enable(ucb);				\
	val = ucb1x00_adc_पढ़ो(ucb, input, UCB_NOSYNC);		\
	ucb1x00_adc_disable(ucb);				\
	वापस प्र_लिखो(buf, "%d\n", val);			\
पूर्ण								\
अटल DEVICE_ATTR(name,0444,name##_show,शून्य)

UCB1X00_ATTR(vbatt, UCB_ADC_INP_AD1);
UCB1X00_ATTR(vअक्षरger, UCB_ADC_INP_AD0);
UCB1X00_ATTR(batt_temp, UCB_ADC_INP_AD2);

अटल पूर्णांक ucb1x00_assabet_add(काष्ठा ucb1x00_dev *dev)
अणु
	काष्ठा ucb1x00 *ucb = dev->ucb;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा gpio_keys_platक्रमm_data keys;
	अटल काष्ठा gpio_keys_button buttons[6];
	अचिन्हित i;

	स_रखो(buttons, 0, माप(buttons));
	स_रखो(&keys, 0, माप(keys));

	क्रम (i = 0; i < ARRAY_SIZE(buttons); i++) अणु
		buttons[i].code = BTN_0 + i;
		buttons[i].gpio = ucb->gpio.base + i;
		buttons[i].type = EV_KEY;
		buttons[i].can_disable = true;
	पूर्ण

	keys.buttons = buttons;
	keys.nbuttons = ARRAY_SIZE(buttons);
	keys.poll_पूर्णांकerval = 50;
	keys.name = "ucb1x00";

	pdev = platक्रमm_device_रेजिस्टर_data(&ucb->dev, "gpio-keys", -1,
		&keys, माप(keys));

	device_create_file(&ucb->dev, &dev_attr_vbatt);
	device_create_file(&ucb->dev, &dev_attr_vअक्षरger);
	device_create_file(&ucb->dev, &dev_attr_batt_temp);

	dev->priv = pdev;
	वापस 0;
पूर्ण

अटल व्योम ucb1x00_assabet_हटाओ(काष्ठा ucb1x00_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->priv;

	अगर (!IS_ERR(pdev))
		platक्रमm_device_unरेजिस्टर(pdev);

	device_हटाओ_file(&dev->ucb->dev, &dev_attr_batt_temp);
	device_हटाओ_file(&dev->ucb->dev, &dev_attr_vअक्षरger);
	device_हटाओ_file(&dev->ucb->dev, &dev_attr_vbatt);
पूर्ण

अटल काष्ठा ucb1x00_driver ucb1x00_assabet_driver = अणु
	.add	= ucb1x00_assabet_add,
	.हटाओ	= ucb1x00_assabet_हटाओ,
पूर्ण;

अटल पूर्णांक __init ucb1x00_assabet_init(व्योम)
अणु
	वापस ucb1x00_रेजिस्टर_driver(&ucb1x00_assabet_driver);
पूर्ण

अटल व्योम __निकास ucb1x00_assabet_निकास(व्योम)
अणु
	ucb1x00_unरेजिस्टर_driver(&ucb1x00_assabet_driver);
पूर्ण

module_init(ucb1x00_assabet_init);
module_निकास(ucb1x00_assabet_निकास);

MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("Assabet noddy testing only example ADC driver");
MODULE_LICENSE("GPL");
