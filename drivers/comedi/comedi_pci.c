<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi_pci.c
 * Comedi PCI driver specअगरic functions.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "comedi_pci.h"

/**
 * comedi_to_pci_dev() - Return PCI device attached to COMEDI device
 * @dev: COMEDI device.
 *
 * Assuming @dev->hw_dev is non-%शून्य, it is assumed to be poपूर्णांकing to a
 * a &काष्ठा device embedded in a &काष्ठा pci_dev.
 *
 * Return: Attached PCI device अगर @dev->hw_dev is non-%शून्य.
 * Return %शून्य अगर @dev->hw_dev is %शून्य.
 */
काष्ठा pci_dev *comedi_to_pci_dev(काष्ठा comedi_device *dev)
अणु
	वापस dev->hw_dev ? to_pci_dev(dev->hw_dev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_to_pci_dev);

/**
 * comedi_pci_enable() - Enable the PCI device and request the regions
 * @dev: COMEDI device.
 *
 * Assuming @dev->hw_dev is non-%शून्य, it is assumed to be poपूर्णांकing to a
 * a &काष्ठा device embedded in a &काष्ठा pci_dev.  Enable the PCI device
 * and request its regions.  Set @dev->ioenabled to %true अगर successful,
 * otherwise unकरो what was करोne.
 *
 * Calls to comedi_pci_enable() and comedi_pci_disable() cannot be nested.
 *
 * Return:
 *	0 on success,
 *	-%ENODEV अगर @dev->hw_dev is %शून्य,
 *	-%EBUSY अगर regions busy,
 *	or some negative error number अगर failed to enable PCI device.
 *
 */
पूर्णांक comedi_pci_enable(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	पूर्णांक rc;

	अगर (!pcidev)
		वापस -ENODEV;

	rc = pci_enable_device(pcidev);
	अगर (rc < 0)
		वापस rc;

	rc = pci_request_regions(pcidev, dev->board_name);
	अगर (rc < 0)
		pci_disable_device(pcidev);
	अन्यथा
		dev->ioenabled = true;

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pci_enable);

/**
 * comedi_pci_disable() - Release the regions and disable the PCI device
 * @dev: COMEDI device.
 *
 * Assuming @dev->hw_dev is non-%शून्य, it is assumed to be poपूर्णांकing to a
 * a &काष्ठा device embedded in a &काष्ठा pci_dev.  If the earlier call
 * to comedi_pci_enable() was successful, release the PCI device's regions
 * and disable it.  Reset @dev->ioenabled back to %false.
 */
व्योम comedi_pci_disable(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);

	अगर (pcidev && dev->ioenabled) अणु
		pci_release_regions(pcidev);
		pci_disable_device(pcidev);
	पूर्ण
	dev->ioenabled = false;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pci_disable);

/**
 * comedi_pci_detach() - A generic "detach" handler क्रम PCI COMEDI drivers
 * @dev: COMEDI device.
 *
 * COMEDI drivers क्रम PCI devices that need no special clean-up of निजी data
 * and have no ioremapped regions other than that poपूर्णांकed to by @dev->mmio may
 * use this function as its "detach" handler called by the COMEDI core when a
 * COMEDI device is being detached from the low-level driver.  It may be also
 * called from a more specअगरic "detach" handler that करोes additional clean-up.
 *
 * Free the IRQ अगर @dev->irq is non-zero, iounmap @dev->mmio अगर it is
 * non-%शून्य, and call comedi_pci_disable() to release the PCI device's regions
 * and disable it.
 */
व्योम comedi_pci_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);

	अगर (!pcidev || !dev->ioenabled)
		वापस;

	अगर (dev->irq) अणु
		मुक्त_irq(dev->irq, dev);
		dev->irq = 0;
	पूर्ण
	अगर (dev->mmio) अणु
		iounmap(dev->mmio);
		dev->mmio = शून्य;
	पूर्ण
	comedi_pci_disable(dev);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pci_detach);

/**
 * comedi_pci_स्वतः_config() - Configure/probe a PCI COMEDI device
 * @pcidev: PCI device.
 * @driver: Registered COMEDI driver.
 * @context: Driver specअगरic data, passed to comedi_स्वतः_config().
 *
 * Typically called from the pci_driver (*probe) function.  Auto-configure
 * a COMEDI device, using the &काष्ठा device embedded in *@pcidev as the
 * hardware device.  The @context value माला_लो passed through to @driver's
 * "auto_attach" handler.  The "auto_attach" handler may call
 * comedi_to_pci_dev() on the passed in COMEDI device to recover @pcidev.
 *
 * Return: The result of calling comedi_स्वतः_config() (0 on success, or
 * a negative error number on failure).
 */
पूर्णांक comedi_pci_स्वतः_config(काष्ठा pci_dev *pcidev,
			   काष्ठा comedi_driver *driver,
			   अचिन्हित दीर्घ context)
अणु
	वापस comedi_स्वतः_config(&pcidev->dev, driver, context);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pci_स्वतः_config);

/**
 * comedi_pci_स्वतः_unconfig() - Unconfigure/हटाओ a PCI COMEDI device
 * @pcidev: PCI device.
 *
 * Typically called from the pci_driver (*हटाओ) function.  Auto-unconfigure
 * a COMEDI device attached to this PCI device, using a poपूर्णांकer to the
 * &काष्ठा device embedded in *@pcidev as the hardware device.  The COMEDI
 * driver's "detach" handler will be called during unconfiguration of the
 * COMEDI device.
 *
 * Note that the COMEDI device may have alपढ़ोy been unconfigured using the
 * %COMEDI_DEVCONFIG ioctl, in which हाल this attempt to unconfigure it
 * again should be ignored.
 */
व्योम comedi_pci_स्वतः_unconfig(काष्ठा pci_dev *pcidev)
अणु
	comedi_स्वतः_unconfig(&pcidev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pci_स्वतः_unconfig);

/**
 * comedi_pci_driver_रेजिस्टर() - Register a PCI COMEDI driver
 * @comedi_driver: COMEDI driver to be रेजिस्टरed.
 * @pci_driver: PCI driver to be रेजिस्टरed.
 *
 * This function is called from the module_init() of PCI COMEDI driver modules
 * to रेजिस्टर the COMEDI driver and the PCI driver.  Do not call it directly,
 * use the module_comedi_pci_driver() helper macro instead.
 *
 * Return: 0 on success, or a negative error number on failure.
 */
पूर्णांक comedi_pci_driver_रेजिस्टर(काष्ठा comedi_driver *comedi_driver,
			       काष्ठा pci_driver *pci_driver)
अणु
	पूर्णांक ret;

	ret = comedi_driver_रेजिस्टर(comedi_driver);
	अगर (ret < 0)
		वापस ret;

	ret = pci_रेजिस्टर_driver(pci_driver);
	अगर (ret < 0) अणु
		comedi_driver_unरेजिस्टर(comedi_driver);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pci_driver_रेजिस्टर);

/**
 * comedi_pci_driver_unरेजिस्टर() - Unरेजिस्टर a PCI COMEDI driver
 * @comedi_driver: COMEDI driver to be unरेजिस्टरed.
 * @pci_driver: PCI driver to be unरेजिस्टरed.
 *
 * This function is called from the module_निकास() of PCI COMEDI driver modules
 * to unरेजिस्टर the PCI driver and the COMEDI driver.  Do not call it
 * directly, use the module_comedi_pci_driver() helper macro instead.
 */
व्योम comedi_pci_driver_unरेजिस्टर(काष्ठा comedi_driver *comedi_driver,
				  काष्ठा pci_driver *pci_driver)
अणु
	pci_unरेजिस्टर_driver(pci_driver);
	comedi_driver_unरेजिस्टर(comedi_driver);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_pci_driver_unरेजिस्टर);

अटल पूर्णांक __init comedi_pci_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(comedi_pci_init);

अटल व्योम __निकास comedi_pci_निकास(व्योम)
अणु
पूर्ण
module_निकास(comedi_pci_निकास);

MODULE_AUTHOR("https://www.comedi.org");
MODULE_DESCRIPTION("Comedi PCI interface module");
MODULE_LICENSE("GPL");
