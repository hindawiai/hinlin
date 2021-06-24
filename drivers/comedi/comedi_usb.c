<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi_usb.c
 * Comedi USB driver specअगरic functions.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 */

#समावेश <linux/module.h>

#समावेश "comedi_usb.h"

/**
 * comedi_to_usb_पूर्णांकerface() - Return USB पूर्णांकerface attached to COMEDI device
 * @dev: COMEDI device.
 *
 * Assuming @dev->hw_dev is non-%शून्य, it is assumed to be poपूर्णांकing to a
 * a &काष्ठा device embedded in a &काष्ठा usb_पूर्णांकerface.
 *
 * Return: Attached USB पूर्णांकerface अगर @dev->hw_dev is non-%शून्य.
 * Return %शून्य अगर @dev->hw_dev is %शून्य.
 */
काष्ठा usb_पूर्णांकerface *comedi_to_usb_पूर्णांकerface(काष्ठा comedi_device *dev)
अणु
	वापस dev->hw_dev ? to_usb_पूर्णांकerface(dev->hw_dev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_to_usb_पूर्णांकerface);

/**
 * comedi_to_usb_dev() - Return USB device attached to COMEDI device
 * @dev: COMEDI device.
 *
 * Assuming @dev->hw_dev is non-%शून्य, it is assumed to be poपूर्णांकing to a
 * a &काष्ठा device embedded in a &काष्ठा usb_पूर्णांकerface.
 *
 * Return: USB device to which the USB पूर्णांकerface beदीर्घs अगर @dev->hw_dev is
 * non-%शून्य.  Return %शून्य अगर @dev->hw_dev is %शून्य.
 */
काष्ठा usb_device *comedi_to_usb_dev(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);

	वापस पूर्णांकf ? पूर्णांकerface_to_usbdev(पूर्णांकf) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_to_usb_dev);

/**
 * comedi_usb_स्वतः_config() - Configure/probe a USB COMEDI driver
 * @पूर्णांकf: USB पूर्णांकerface.
 * @driver: Registered COMEDI driver.
 * @context: Driver specअगरic data, passed to comedi_स्वतः_config().
 *
 * Typically called from the usb_driver (*probe) function.  Auto-configure a
 * COMEDI device, using a poपूर्णांकer to the &काष्ठा device embedded in *@पूर्णांकf as
 * the hardware device.  The @context value माला_लो passed through to @driver's
 * "auto_attach" handler.  The "auto_attach" handler may call
 * comedi_to_usb_पूर्णांकerface() on the passed in COMEDI device to recover @पूर्णांकf.
 *
 * Return: The result of calling comedi_स्वतः_config() (%0 on success, or
 * a negative error number on failure).
 */
पूर्णांक comedi_usb_स्वतः_config(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   काष्ठा comedi_driver *driver,
			   अचिन्हित दीर्घ context)
अणु
	वापस comedi_स्वतः_config(&पूर्णांकf->dev, driver, context);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_usb_स्वतः_config);

/**
 * comedi_usb_स्वतः_unconfig() - Unconfigure/disconnect a USB COMEDI device
 * @पूर्णांकf: USB पूर्णांकerface.
 *
 * Typically called from the usb_driver (*disconnect) function.
 * Auto-unconfigure a COMEDI device attached to this USB पूर्णांकerface, using a
 * poपूर्णांकer to the &काष्ठा device embedded in *@पूर्णांकf as the hardware device.
 * The COMEDI driver's "detach" handler will be called during unconfiguration
 * of the COMEDI device.
 *
 * Note that the COMEDI device may have alपढ़ोy been unconfigured using the
 * %COMEDI_DEVCONFIG ioctl, in which हाल this attempt to unconfigure it
 * again should be ignored.
 */
व्योम comedi_usb_स्वतः_unconfig(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	comedi_स्वतः_unconfig(&पूर्णांकf->dev);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_usb_स्वतः_unconfig);

/**
 * comedi_usb_driver_रेजिस्टर() - Register a USB COMEDI driver
 * @comedi_driver: COMEDI driver to be रेजिस्टरed.
 * @usb_driver: USB driver to be रेजिस्टरed.
 *
 * This function is called from the module_init() of USB COMEDI driver modules
 * to रेजिस्टर the COMEDI driver and the USB driver.  Do not call it directly,
 * use the module_comedi_usb_driver() helper macro instead.
 *
 * Return: %0 on success, or a negative error number on failure.
 */
पूर्णांक comedi_usb_driver_रेजिस्टर(काष्ठा comedi_driver *comedi_driver,
			       काष्ठा usb_driver *usb_driver)
अणु
	पूर्णांक ret;

	ret = comedi_driver_रेजिस्टर(comedi_driver);
	अगर (ret < 0)
		वापस ret;

	ret = usb_रेजिस्टर(usb_driver);
	अगर (ret < 0) अणु
		comedi_driver_unरेजिस्टर(comedi_driver);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_usb_driver_रेजिस्टर);

/**
 * comedi_usb_driver_unरेजिस्टर() - Unरेजिस्टर a USB COMEDI driver
 * @comedi_driver: COMEDI driver to be रेजिस्टरed.
 * @usb_driver: USB driver to be रेजिस्टरed.
 *
 * This function is called from the module_निकास() of USB COMEDI driver modules
 * to unरेजिस्टर the USB driver and the COMEDI driver.  Do not call it
 * directly, use the module_comedi_usb_driver() helper macro instead.
 */
व्योम comedi_usb_driver_unरेजिस्टर(काष्ठा comedi_driver *comedi_driver,
				  काष्ठा usb_driver *usb_driver)
अणु
	usb_deरेजिस्टर(usb_driver);
	comedi_driver_unरेजिस्टर(comedi_driver);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_usb_driver_unरेजिस्टर);

अटल पूर्णांक __init comedi_usb_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(comedi_usb_init);

अटल व्योम __निकास comedi_usb_निकास(व्योम)
अणु
पूर्ण
module_निकास(comedi_usb_निकास);

MODULE_AUTHOR("https://www.comedi.org");
MODULE_DESCRIPTION("Comedi USB interface module");
MODULE_LICENSE("GPL");
