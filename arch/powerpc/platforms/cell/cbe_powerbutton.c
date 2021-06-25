<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * driver क्रम घातerbutton on IBM cell blades
 *
 * (C) Copyright IBM Corp. 2005-2008
 *
 * Author: Christian Krafft <krafft@de.ibm.com>
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/pmi.h>
#समावेश <यंत्र/prom.h>

अटल काष्ठा input_dev *button_dev;
अटल काष्ठा platक्रमm_device *button_pdev;

अटल व्योम cbe_घातerbutton_handle_pmi(pmi_message_t pmi_msg)
अणु
	BUG_ON(pmi_msg.type != PMI_TYPE_POWER_BUTTON);

	input_report_key(button_dev, KEY_POWER, 1);
	input_sync(button_dev);
	input_report_key(button_dev, KEY_POWER, 0);
	input_sync(button_dev);
पूर्ण

अटल काष्ठा pmi_handler cbe_pmi_handler = अणु
	.type			= PMI_TYPE_POWER_BUTTON,
	.handle_pmi_message	= cbe_घातerbutton_handle_pmi,
पूर्ण;

अटल पूर्णांक __init cbe_घातerbutton_init(व्योम)
अणु
	पूर्णांक ret = 0;
	काष्ठा input_dev *dev;

	अगर (!of_machine_is_compatible("IBM,CBPLUS-1.0")) अणु
		prपूर्णांकk(KERN_ERR "%s: Not a cell blade.\n", __func__);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	dev = input_allocate_device();
	अगर (!dev) अणु
		ret = -ENOMEM;
		prपूर्णांकk(KERN_ERR "%s: Not enough memory.\n", __func__);
		जाओ out;
	पूर्ण

	set_bit(EV_KEY, dev->evbit);
	set_bit(KEY_POWER, dev->keybit);

	dev->name = "Power Button";
	dev->id.bustype = BUS_HOST;

	/* this makes the button look like an acpi घातer button
	 * no clue whether anyone relies on that though */
	dev->id.product = 0x02;
	dev->phys = "LNXPWRBN/button/input0";

	button_pdev = platक्रमm_device_रेजिस्टर_simple("power_button", 0, शून्य, 0);
	अगर (IS_ERR(button_pdev)) अणु
		ret = PTR_ERR(button_pdev);
		जाओ out_मुक्त_input;
	पूर्ण

	dev->dev.parent = &button_pdev->dev;
	ret = input_रेजिस्टर_device(dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to register device\n", __func__);
		जाओ out_मुक्त_pdev;
	पूर्ण

	button_dev = dev;

	ret = pmi_रेजिस्टर_handler(&cbe_pmi_handler);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to register with pmi.\n", __func__);
		जाओ out_मुक्त_pdev;
	पूर्ण

	जाओ out;

out_मुक्त_pdev:
	platक्रमm_device_unरेजिस्टर(button_pdev);
out_मुक्त_input:
	input_मुक्त_device(dev);
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास cbe_घातerbutton_निकास(व्योम)
अणु
	pmi_unरेजिस्टर_handler(&cbe_pmi_handler);
	platक्रमm_device_unरेजिस्टर(button_pdev);
	input_मुक्त_device(button_dev);
पूर्ण

module_init(cbe_घातerbutton_init);
module_निकास(cbe_घातerbutton_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Krafft <krafft@de.ibm.com>");
