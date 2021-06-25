<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Eurobraille/Iris घातer off support.
 *
 * Eurobraille's Iris machine is a PC with no APM or ACPI support.
 * It is shutकरोwn by a special I/O sequence which this module provides.
 *
 *  Copyright (C) Shथऊrab <Sebastien.Hinderer@ens-lyon.org>
 */

#समावेश <linux/moduleparam.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <यंत्र/पन.स>

#घोषणा IRIS_GIO_BASE		0x340
#घोषणा IRIS_GIO_INPUT		IRIS_GIO_BASE
#घोषणा IRIS_GIO_OUTPUT		(IRIS_GIO_BASE + 1)
#घोषणा IRIS_GIO_PULSE		0x80 /* First byte to send */
#घोषणा IRIS_GIO_REST		0x00 /* Second byte to send */
#घोषणा IRIS_GIO_NODEV		0xff /* Likely not an Iris */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sथऊbastien Hinderer <Sebastien.Hinderer@ens-lyon.org>");
MODULE_DESCRIPTION("A power_off handler for Iris devices from EuroBraille");

अटल bool क्रमce;

module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Set to one to force poweroff handler installation.");

अटल व्योम (*old_pm_घातer_off)(व्योम);

अटल व्योम iris_घातer_off(व्योम)
अणु
	outb(IRIS_GIO_PULSE, IRIS_GIO_OUTPUT);
	msleep(850);
	outb(IRIS_GIO_REST, IRIS_GIO_OUTPUT);
पूर्ण

/*
 * Beक्रमe installing the घातer_off handler, try to make sure the OS is
 * running on an Iris.  Since Iris करोes not support DMI, this is करोne
 * by पढ़ोing its input port and seeing whether the पढ़ो value is
 * meaningful.
 */
अटल पूर्णांक iris_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित अक्षर status = inb(IRIS_GIO_INPUT);
	अगर (status == IRIS_GIO_NODEV) अणु
		prपूर्णांकk(KERN_ERR "This machine does not seem to be an Iris. "
			"Power off handler not installed.\n");
		वापस -ENODEV;
	पूर्ण
	old_pm_घातer_off = pm_घातer_off;
	pm_घातer_off = &iris_घातer_off;
	prपूर्णांकk(KERN_INFO "Iris power_off handler installed.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक iris_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_घातer_off = old_pm_घातer_off;
	prपूर्णांकk(KERN_INFO "Iris power_off handler uninstalled.\n");
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver iris_driver = अणु
	.driver		= अणु
		.name   = "iris",
	पूर्ण,
	.probe          = iris_probe,
	.हटाओ         = iris_हटाओ,
पूर्ण;

अटल काष्ठा resource iris_resources[] = अणु
	अणु
		.start  = IRIS_GIO_BASE,
		.end    = IRIS_GIO_OUTPUT,
		.flags  = IORESOURCE_IO,
		.name   = "address"
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *iris_device;

अटल पूर्णांक iris_init(व्योम)
अणु
	पूर्णांक ret;
	अगर (क्रमce != 1) अणु
		prपूर्णांकk(KERN_ERR "The force parameter has not been set to 1."
			" The Iris poweroff handler will not be installed.\n");
		वापस -ENODEV;
	पूर्ण
	ret = platक्रमm_driver_रेजिस्टर(&iris_driver);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register iris platform driver: %d\n",
			ret);
		वापस ret;
	पूर्ण
	iris_device = platक्रमm_device_रेजिस्टर_simple("iris", (-1),
				iris_resources, ARRAY_SIZE(iris_resources));
	अगर (IS_ERR(iris_device)) अणु
		prपूर्णांकk(KERN_ERR "Failed to register iris platform device\n");
		platक्रमm_driver_unरेजिस्टर(&iris_driver);
		वापस PTR_ERR(iris_device);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम iris_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(iris_device);
	platक्रमm_driver_unरेजिस्टर(&iris_driver);
पूर्ण

module_init(iris_init);
module_निकास(iris_निकास);
