<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi_pcmcia.c
 * Comedi PCMCIA driver specअगरic functions.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश "comedi_pcmcia.h"

/**
 * comedi_to_pcmcia_dev() - Return PCMCIA device attached to COMEDI device
 * @dev: COMEDI device.
 *
 * Assuming @dev->hw_dev is non-%शून्य, it is assumed to be poपूर्णांकing to a
 * a &काष्ठा device embedded in a &काष्ठा pcmcia_device.
 *
 * Return: Attached PCMCIA device अगर @dev->hw_dev is non-%शून्य.
 * Return %शून्य अगर @dev->hw_dev is %शून्य.
 */
काष्ठा pcmcia_device *comedi_to_pcmcia_dev(काष्ठा comedi_device *dev)
अणु
	वापस dev->hw_dev ? to_pcmcia_dev(dev->hw_dev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_to_pcmcia_dev);

अटल पूर्णांक comedi_pcmcia_conf_check(काष्ठा pcmcia_device *link,
				    व्योम *priv_data)
अणु
	अगर (link->config_index == 0)
		वापस -EINVAL;

	वापस pcmcia_request_io(link);
पूर्ण

/**
 * comedi_pcmcia_enable() - Request the regions and enable the PCMCIA device
 * @dev: COMEDI device.
 * @conf_check: Optional callback to check each configuration option of the
 *	PCMCIA device and request I/O regions.
 *
 * Assuming @dev->hw_dev is non-%शून्य, it is assumed to be poपूर्णांकing to a a
 * &काष्ठा device embedded in a &काष्ठा pcmcia_device.  The comedi PCMCIA
 * driver needs to set the 'config_flags' member in the &काष्ठा pcmcia_device,
 * as appropriate क्रम that driver, beक्रमe calling this function in order to
 * allow pcmcia_loop_config() to करो its पूर्णांकernal स्वतःconfiguration.
 *
 * If @conf_check is %शून्य it is set to a शेष function.  If is
 * passed to pcmcia_loop_config() and should वापस %0 अगर the configuration
 * is valid and I/O regions requested successfully, otherwise it should वापस
 * a negative error value.  The शेष function वापसs -%EINVAL अगर the
 * 'config_index' member is %0, otherwise it calls pcmcia_request_io() and
 * वापसs the result.
 *
 * If the above configuration check passes, pcmcia_enable_device() is called
 * to set up and activate the PCMCIA device.
 *
 * If this function वापसs an error, comedi_pcmcia_disable() should be called
 * to release requested resources.
 *
 * Return:
 *	0 on success,
 *	-%ENODEV id @dev->hw_dev is %शून्य,
 *	a negative error number from pcmcia_loop_config() अगर it fails,
 *	or a negative error number from pcmcia_enable_device() अगर it fails.
 */
पूर्णांक comedi_pcmcia_enable(काष्ठा comedi_device *dev,
			 पूर्णांक (*conf_check)(काष्ठा pcmcia_device *p_dev,
					   व्योम *priv_data))
अणु
	काष्ठा pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	पूर्णांक ret;

	अगर (!link)
		वापस -ENODEV;

	अगर (!conf_check)
		conf_check = comedi_pcmcia_conf_check;

	ret = pcmcia_loop_config(link, conf_check, शून्य);
	अगर (ret)
		वापस ret;

	वापस pcmcia_enable_device(link);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pcmcia_enable);

/**
 * comedi_pcmcia_disable() - Disable the PCMCIA device and release the regions
 * @dev: COMEDI device.
 *
 * Assuming @dev->hw_dev is non-%शून्य, it is assumed to be poपूर्णांकing to a
 * a &काष्ठा device embedded in a &काष्ठा pcmcia_device.  Call
 * pcmcia_disable_device() to disable and clean up the PCMCIA device.
 */
व्योम comedi_pcmcia_disable(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcmcia_device *link = comedi_to_pcmcia_dev(dev);

	अगर (link)
		pcmcia_disable_device(link);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pcmcia_disable);

/**
 * comedi_pcmcia_स्वतः_config() - Configure/probe a PCMCIA COMEDI device
 * @link: PCMCIA device.
 * @driver: Registered COMEDI driver.
 *
 * Typically called from the pcmcia_driver (*probe) function.  Auto-configure
 * a COMEDI device, using a poपूर्णांकer to the &काष्ठा device embedded in *@link
 * as the hardware device.  The @driver's "auto_attach" handler may call
 * comedi_to_pcmcia_dev() on the passed in COMEDI device to recover @link.
 *
 * Return: The result of calling comedi_स्वतः_config() (0 on success, or a
 * negative error number on failure).
 */
पूर्णांक comedi_pcmcia_स्वतः_config(काष्ठा pcmcia_device *link,
			      काष्ठा comedi_driver *driver)
अणु
	वापस comedi_स्वतः_config(&link->dev, driver, 0);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pcmcia_स्वतः_config);

/**
 * comedi_pcmcia_स्वतः_unconfig() - Unconfigure/हटाओ a PCMCIA COMEDI device
 * @link: PCMCIA device.
 *
 * Typically called from the pcmcia_driver (*हटाओ) function.
 * Auto-unconfigure a COMEDI device attached to this PCMCIA device, using a
 * poपूर्णांकer to the &काष्ठा device embedded in *@link as the hardware device.
 * The COMEDI driver's "detach" handler will be called during unconfiguration
 * of the COMEDI device.
 *
 * Note that the COMEDI device may have alपढ़ोy been unconfigured using the
 * %COMEDI_DEVCONFIG ioctl, in which हाल this attempt to unconfigure it
 * again should be ignored.
 */
व्योम comedi_pcmcia_स्वतः_unconfig(काष्ठा pcmcia_device *link)
अणु
	comedi_स्वतः_unconfig(&link->dev);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pcmcia_स्वतः_unconfig);

/**
 * comedi_pcmcia_driver_रेजिस्टर() - Register a PCMCIA COMEDI driver
 * @comedi_driver: COMEDI driver to be रेजिस्टरed.
 * @pcmcia_driver: PCMCIA driver to be रेजिस्टरed.
 *
 * This function is used क्रम the module_init() of PCMCIA COMEDI driver modules
 * to रेजिस्टर the COMEDI driver and the PCMCIA driver.  Do not call it
 * directly, use the module_comedi_pcmcia_driver() helper macro instead.
 *
 * Return: 0 on success, or a negative error number on failure.
 */
पूर्णांक comedi_pcmcia_driver_रेजिस्टर(काष्ठा comedi_driver *comedi_driver,
				  काष्ठा pcmcia_driver *pcmcia_driver)
अणु
	पूर्णांक ret;

	ret = comedi_driver_रेजिस्टर(comedi_driver);
	अगर (ret < 0)
		वापस ret;

	ret = pcmcia_रेजिस्टर_driver(pcmcia_driver);
	अगर (ret < 0) अणु
		comedi_driver_unरेजिस्टर(comedi_driver);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pcmcia_driver_रेजिस्टर);

/**
 * comedi_pcmcia_driver_unरेजिस्टर() - Unरेजिस्टर a PCMCIA COMEDI driver
 * @comedi_driver: COMEDI driver to be रेजिस्टरed.
 * @pcmcia_driver: PCMCIA driver to be रेजिस्टरed.
 *
 * This function is called from the module_निकास() of PCMCIA COMEDI driver
 * modules to unरेजिस्टर the PCMCIA driver and the COMEDI driver.  Do not call
 * it directly, use the module_comedi_pcmcia_driver() helper macro instead.
 */
व्योम comedi_pcmcia_driver_unरेजिस्टर(काष्ठा comedi_driver *comedi_driver,
				     काष्ठा pcmcia_driver *pcmcia_driver)
अणु
	pcmcia_unरेजिस्टर_driver(pcmcia_driver);
	comedi_driver_unरेजिस्टर(comedi_driver);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pcmcia_driver_unरेजिस्टर);

अटल पूर्णांक __init comedi_pcmcia_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(comedi_pcmcia_init);

अटल व्योम __निकास comedi_pcmcia_निकास(व्योम)
अणु
पूर्ण
module_निकास(comedi_pcmcia_निकास);

MODULE_AUTHOR("https://www.comedi.org");
MODULE_DESCRIPTION("Comedi PCMCIA interface module");
MODULE_LICENSE("GPL");
