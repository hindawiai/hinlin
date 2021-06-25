<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Karol Kosik <karo9@पूर्णांकeria.eu>
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>

#समावेश "vudc.h"

अटल अचिन्हित पूर्णांक vudc_number = 1;

module_param_named(num, vudc_number, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(num, "number of emulated controllers");

अटल काष्ठा platक्रमm_driver vudc_driver = अणु
	.probe		= vudc_probe,
	.हटाओ		= vudc_हटाओ,
	.driver		= अणु
		.name	= GADGET_NAME,
		.dev_groups = vudc_groups,
	पूर्ण,
पूर्ण;

अटल काष्ठा list_head vudc_devices = LIST_HEAD_INIT(vudc_devices);

अटल पूर्णांक __init init(व्योम)
अणु
	पूर्णांक retval = -ENOMEM;
	पूर्णांक i;
	काष्ठा vudc_device *udc_dev = शून्य, *udc_dev2 = शून्य;

	अगर (usb_disabled())
		वापस -ENODEV;

	अगर (vudc_number < 1) अणु
		pr_err("Number of emulated UDC must be no less than 1");
		वापस -EINVAL;
	पूर्ण

	retval = platक्रमm_driver_रेजिस्टर(&vudc_driver);
	अगर (retval < 0)
		जाओ out;

	क्रम (i = 0; i < vudc_number; i++) अणु
		udc_dev = alloc_vudc_device(i);
		अगर (!udc_dev) अणु
			retval = -ENOMEM;
			जाओ cleanup;
		पूर्ण

		retval = platक्रमm_device_add(udc_dev->pdev);
		अगर (retval < 0) अणु
			put_vudc_device(udc_dev);
			जाओ cleanup;
		पूर्ण

		list_add_tail(&udc_dev->dev_entry, &vudc_devices);
		अगर (!platक्रमm_get_drvdata(udc_dev->pdev)) अणु
			/*
			 * The udc was added successfully but its probe
			 * function failed क्रम some reason.
			 */
			retval = -EINVAL;
			जाओ cleanup;
		पूर्ण
	पूर्ण
	जाओ out;

cleanup:
	list_क्रम_each_entry_safe(udc_dev, udc_dev2, &vudc_devices, dev_entry) अणु
		list_del(&udc_dev->dev_entry);
		/*
		 * Just करो platक्रमm_device_del() here, put_vudc_device()
		 * calls the platक्रमm_device_put()
		 */
		platक्रमm_device_del(udc_dev->pdev);
		put_vudc_device(udc_dev);
	पूर्ण

	platक्रमm_driver_unरेजिस्टर(&vudc_driver);
out:
	वापस retval;
पूर्ण
module_init(init);

अटल व्योम __निकास cleanup(व्योम)
अणु
	काष्ठा vudc_device *udc_dev = शून्य, *udc_dev2 = शून्य;

	list_क्रम_each_entry_safe(udc_dev, udc_dev2, &vudc_devices, dev_entry) अणु
		list_del(&udc_dev->dev_entry);
		/*
		 * Just करो platक्रमm_device_del() here, put_vudc_device()
		 * calls the platक्रमm_device_put()
		 */
		platक्रमm_device_del(udc_dev->pdev);
		put_vudc_device(udc_dev);
	पूर्ण
	platक्रमm_driver_unरेजिस्टर(&vudc_driver);
पूर्ण
module_निकास(cleanup);

MODULE_DESCRIPTION("USB over IP Device Controller");
MODULE_AUTHOR("Krzysztof Opasiak, Karol Kosik, Igor Kotrasinski");
MODULE_LICENSE("GPL");
