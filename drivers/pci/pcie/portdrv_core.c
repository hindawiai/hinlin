<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Purpose:	PCI Express Port Bus Driver's Core Functions
 *
 * Copyright (C) 2004 Intel
 * Copyright (C) Tom Long Nguyen (tom.l.nguyen@पूर्णांकel.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/aer.h>

#समावेश "../pci.h"
#समावेश "portdrv.h"

काष्ठा portdrv_service_data अणु
	काष्ठा pcie_port_service_driver *drv;
	काष्ठा device *dev;
	u32 service;
पूर्ण;

/**
 * release_pcie_device - मुक्त PCI Express port service device काष्ठाure
 * @dev: Port service device to release
 *
 * Invoked स्वतःmatically when device is being हटाओd in response to
 * device_unरेजिस्टर(dev).  Release all resources being claimed.
 */
अटल व्योम release_pcie_device(काष्ठा device *dev)
अणु
	kमुक्त(to_pcie_device(dev));
पूर्ण

/*
 * Fill in *pme, *aer, *dpc with the relevant Interrupt Message Numbers अगर
 * services are enabled in "mask".  Return the number of MSI/MSI-X vectors
 * required to accommodate the largest Message Number.
 */
अटल पूर्णांक pcie_message_numbers(काष्ठा pci_dev *dev, पूर्णांक mask,
				u32 *pme, u32 *aer, u32 *dpc)
अणु
	u32 nvec = 0, pos;
	u16 reg16;

	/*
	 * The Interrupt Message Number indicates which vector is used, i.e.,
	 * the MSI-X table entry or the MSI offset between the base Message
	 * Data and the generated पूर्णांकerrupt message.  See PCIe r3.1, sec
	 * 7.8.2, 7.10.10, 7.31.2.
	 */

	अगर (mask & (PCIE_PORT_SERVICE_PME | PCIE_PORT_SERVICE_HP |
		    PCIE_PORT_SERVICE_BWNOTIF)) अणु
		pcie_capability_पढ़ो_word(dev, PCI_EXP_FLAGS, &reg16);
		*pme = (reg16 & PCI_EXP_FLAGS_IRQ) >> 9;
		nvec = *pme + 1;
	पूर्ण

#अगर_घोषित CONFIG_PCIEAER
	अगर (mask & PCIE_PORT_SERVICE_AER) अणु
		u32 reg32;

		pos = dev->aer_cap;
		अगर (pos) अणु
			pci_पढ़ो_config_dword(dev, pos + PCI_ERR_ROOT_STATUS,
					      &reg32);
			*aer = (reg32 & PCI_ERR_ROOT_AER_IRQ) >> 27;
			nvec = max(nvec, *aer + 1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (mask & PCIE_PORT_SERVICE_DPC) अणु
		pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_DPC);
		अगर (pos) अणु
			pci_पढ़ो_config_word(dev, pos + PCI_EXP_DPC_CAP,
					     &reg16);
			*dpc = reg16 & PCI_EXP_DPC_IRQ;
			nvec = max(nvec, *dpc + 1);
		पूर्ण
	पूर्ण

	वापस nvec;
पूर्ण

/**
 * pcie_port_enable_irq_vec - try to set up MSI-X or MSI as पूर्णांकerrupt mode
 * क्रम given port
 * @dev: PCI Express port to handle
 * @irqs: Array of पूर्णांकerrupt vectors to populate
 * @mask: Biपंचांगask of port capabilities वापसed by get_port_device_capability()
 *
 * Return value: 0 on success, error code on failure
 */
अटल पूर्णांक pcie_port_enable_irq_vec(काष्ठा pci_dev *dev, पूर्णांक *irqs, पूर्णांक mask)
अणु
	पूर्णांक nr_entries, nvec, pcie_irq;
	u32 pme = 0, aer = 0, dpc = 0;

	/* Allocate the maximum possible number of MSI/MSI-X vectors */
	nr_entries = pci_alloc_irq_vectors(dev, 1, PCIE_PORT_MAX_MSI_ENTRIES,
			PCI_IRQ_MSIX | PCI_IRQ_MSI);
	अगर (nr_entries < 0)
		वापस nr_entries;

	/* See how many and which Interrupt Message Numbers we actually use */
	nvec = pcie_message_numbers(dev, mask, &pme, &aer, &dpc);
	अगर (nvec > nr_entries) अणु
		pci_मुक्त_irq_vectors(dev);
		वापस -EIO;
	पूर्ण

	/*
	 * If we allocated more than we need, मुक्त them and पुनः_स्मृतिate fewer.
	 *
	 * Reallocating may change the specअगरic vectors we get, so
	 * pci_irq_vector() must be करोne *after* the पुनः_स्मृतिation.
	 *
	 * If we're using MSI, hardware is *allowed* to change the Interrupt
	 * Message Numbers when we मुक्त and पुनः_स्मृतिate the vectors, but we
	 * assume it won't because we allocate enough vectors क्रम the
	 * biggest Message Number we found.
	 */
	अगर (nvec != nr_entries) अणु
		pci_मुक्त_irq_vectors(dev);

		nr_entries = pci_alloc_irq_vectors(dev, nvec, nvec,
				PCI_IRQ_MSIX | PCI_IRQ_MSI);
		अगर (nr_entries < 0)
			वापस nr_entries;
	पूर्ण

	/* PME, hotplug and bandwidth notअगरication share an MSI/MSI-X vector */
	अगर (mask & (PCIE_PORT_SERVICE_PME | PCIE_PORT_SERVICE_HP |
		    PCIE_PORT_SERVICE_BWNOTIF)) अणु
		pcie_irq = pci_irq_vector(dev, pme);
		irqs[PCIE_PORT_SERVICE_PME_SHIFT] = pcie_irq;
		irqs[PCIE_PORT_SERVICE_HP_SHIFT] = pcie_irq;
		irqs[PCIE_PORT_SERVICE_BWNOTIF_SHIFT] = pcie_irq;
	पूर्ण

	अगर (mask & PCIE_PORT_SERVICE_AER)
		irqs[PCIE_PORT_SERVICE_AER_SHIFT] = pci_irq_vector(dev, aer);

	अगर (mask & PCIE_PORT_SERVICE_DPC)
		irqs[PCIE_PORT_SERVICE_DPC_SHIFT] = pci_irq_vector(dev, dpc);

	वापस 0;
पूर्ण

/**
 * pcie_init_service_irqs - initialize irqs क्रम PCI Express port services
 * @dev: PCI Express port to handle
 * @irqs: Array of irqs to populate
 * @mask: Biपंचांगask of port capabilities वापसed by get_port_device_capability()
 *
 * Return value: Interrupt mode associated with the port
 */
अटल पूर्णांक pcie_init_service_irqs(काष्ठा pci_dev *dev, पूर्णांक *irqs, पूर्णांक mask)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < PCIE_PORT_DEVICE_MAXSERVICES; i++)
		irqs[i] = -1;

	/*
	 * If we support PME but can't use MSI/MSI-X क्रम it, we have to
	 * fall back to INTx or other पूर्णांकerrupts, e.g., a प्रणाली shared
	 * पूर्णांकerrupt.
	 */
	अगर ((mask & PCIE_PORT_SERVICE_PME) && pcie_pme_no_msi())
		जाओ legacy_irq;

	/* Try to use MSI-X or MSI अगर supported */
	अगर (pcie_port_enable_irq_vec(dev, irqs, mask) == 0)
		वापस 0;

legacy_irq:
	/* fall back to legacy IRQ */
	ret = pci_alloc_irq_vectors(dev, 1, 1, PCI_IRQ_LEGACY);
	अगर (ret < 0)
		वापस -ENODEV;

	क्रम (i = 0; i < PCIE_PORT_DEVICE_MAXSERVICES; i++)
		irqs[i] = pci_irq_vector(dev, 0);

	वापस 0;
पूर्ण

/**
 * get_port_device_capability - discover capabilities of a PCI Express port
 * @dev: PCI Express port to examine
 *
 * The capabilities are पढ़ो from the port's PCI Express configuration रेजिस्टरs
 * as described in PCI Express Base Specअगरication 1.0a sections 7.8.2, 7.8.9 and
 * 7.9 - 7.11.
 *
 * Return value: Biपंचांगask of discovered port capabilities
 */
अटल पूर्णांक get_port_device_capability(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_host_bridge *host = pci_find_host_bridge(dev->bus);
	पूर्णांक services = 0;

	अगर (dev->is_hotplug_bridge &&
	    (pcie_ports_native || host->native_pcie_hotplug)) अणु
		services |= PCIE_PORT_SERVICE_HP;

		/*
		 * Disable hot-plug पूर्णांकerrupts in हाल they have been enabled
		 * by the BIOS and the hot-plug service driver is not loaded.
		 */
		pcie_capability_clear_word(dev, PCI_EXP_SLTCTL,
			  PCI_EXP_SLTCTL_CCIE | PCI_EXP_SLTCTL_HPIE);
	पूर्ण

#अगर_घोषित CONFIG_PCIEAER
	अगर (dev->aer_cap && pci_aer_available() &&
	    (pcie_ports_native || host->native_aer)) अणु
		services |= PCIE_PORT_SERVICE_AER;

		/*
		 * Disable AER on this port in हाल it's been enabled by the
		 * BIOS (the AER service driver will enable it when necessary).
		 */
		pci_disable_pcie_error_reporting(dev);
	पूर्ण
#पूर्ण_अगर

	/* Root Ports and Root Complex Event Collectors may generate PMEs */
	अगर ((pci_pcie_type(dev) == PCI_EXP_TYPE_ROOT_PORT ||
	     pci_pcie_type(dev) == PCI_EXP_TYPE_RC_EC) &&
	    (pcie_ports_native || host->native_pme)) अणु
		services |= PCIE_PORT_SERVICE_PME;

		/*
		 * Disable PME पूर्णांकerrupt on this port in हाल it's been enabled
		 * by the BIOS (the PME service driver will enable it when
		 * necessary).
		 */
		pcie_pme_पूर्णांकerrupt_enable(dev, false);
	पूर्ण

	/*
	 * With dpc-native, allow Linux to use DPC even अगर it करोesn't have
	 * permission to use AER.
	 */
	अगर (pci_find_ext_capability(dev, PCI_EXT_CAP_ID_DPC) &&
	    pci_aer_available() &&
	    (pcie_ports_dpc_native || (services & PCIE_PORT_SERVICE_AER)))
		services |= PCIE_PORT_SERVICE_DPC;

	अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_DOWNSTREAM ||
	    pci_pcie_type(dev) == PCI_EXP_TYPE_ROOT_PORT)
		services |= PCIE_PORT_SERVICE_BWNOTIF;

	वापस services;
पूर्ण

/**
 * pcie_device_init - allocate and initialize PCI Express port service device
 * @pdev: PCI Express port to associate the service device with
 * @service: Type of service to associate with the service device
 * @irq: Interrupt vector to associate with the service device
 */
अटल पूर्णांक pcie_device_init(काष्ठा pci_dev *pdev, पूर्णांक service, पूर्णांक irq)
अणु
	पूर्णांक retval;
	काष्ठा pcie_device *pcie;
	काष्ठा device *device;

	pcie = kzalloc(माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस -ENOMEM;
	pcie->port = pdev;
	pcie->irq = irq;
	pcie->service = service;

	/* Initialize generic device पूर्णांकerface */
	device = &pcie->device;
	device->bus = &pcie_port_bus_type;
	device->release = release_pcie_device;	/* callback to मुक्त pcie dev */
	dev_set_name(device, "%s:pcie%03x",
		     pci_name(pdev),
		     get_descriptor_id(pci_pcie_type(pdev), service));
	device->parent = &pdev->dev;
	device_enable_async_suspend(device);

	retval = device_रेजिस्टर(device);
	अगर (retval) अणु
		put_device(device);
		वापस retval;
	पूर्ण

	pm_runसमय_no_callbacks(device);

	वापस 0;
पूर्ण

/**
 * pcie_port_device_रेजिस्टर - रेजिस्टर PCI Express port
 * @dev: PCI Express port to रेजिस्टर
 *
 * Allocate the port extension काष्ठाure and रेजिस्टर services associated with
 * the port.
 */
पूर्णांक pcie_port_device_रेजिस्टर(काष्ठा pci_dev *dev)
अणु
	पूर्णांक status, capabilities, i, nr_service;
	पूर्णांक irqs[PCIE_PORT_DEVICE_MAXSERVICES];

	/* Enable PCI Express port device */
	status = pci_enable_device(dev);
	अगर (status)
		वापस status;

	/* Get and check PCI Express port services */
	capabilities = get_port_device_capability(dev);
	अगर (!capabilities)
		वापस 0;

	pci_set_master(dev);
	/*
	 * Initialize service irqs. Don't use service devices that
	 * require पूर्णांकerrupts अगर there is no way to generate them.
	 * However, some drivers may have a polling mode (e.g. pciehp_poll_mode)
	 * that can be used in the असलence of irqs.  Allow them to determine
	 * अगर that is to be used.
	 */
	status = pcie_init_service_irqs(dev, irqs, capabilities);
	अगर (status) अणु
		capabilities &= PCIE_PORT_SERVICE_HP;
		अगर (!capabilities)
			जाओ error_disable;
	पूर्ण

	/* Allocate child services अगर any */
	status = -ENODEV;
	nr_service = 0;
	क्रम (i = 0; i < PCIE_PORT_DEVICE_MAXSERVICES; i++) अणु
		पूर्णांक service = 1 << i;
		अगर (!(capabilities & service))
			जारी;
		अगर (!pcie_device_init(dev, service, irqs[i]))
			nr_service++;
	पूर्ण
	अगर (!nr_service)
		जाओ error_cleanup_irqs;

	वापस 0;

error_cleanup_irqs:
	pci_मुक्त_irq_vectors(dev);
error_disable:
	pci_disable_device(dev);
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_PM
प्रकार पूर्णांक (*pcie_pm_callback_t)(काष्ठा pcie_device *);

अटल पूर्णांक pm_iter(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा pcie_port_service_driver *service_driver;
	माप_प्रकार offset = *(माप_प्रकार *)data;
	pcie_pm_callback_t cb;

	अगर ((dev->bus == &pcie_port_bus_type) && dev->driver) अणु
		service_driver = to_service_driver(dev->driver);
		cb = *(pcie_pm_callback_t *)((व्योम *)service_driver + offset);
		अगर (cb)
			वापस cb(to_pcie_device(dev));
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pcie_port_device_suspend - suspend port services associated with a PCIe port
 * @dev: PCI Express port to handle
 */
पूर्णांक pcie_port_device_suspend(काष्ठा device *dev)
अणु
	माप_प्रकार off = दुरत्व(काष्ठा pcie_port_service_driver, suspend);
	वापस device_क्रम_each_child(dev, &off, pm_iter);
पूर्ण

पूर्णांक pcie_port_device_resume_noirq(काष्ठा device *dev)
अणु
	माप_प्रकार off = दुरत्व(काष्ठा pcie_port_service_driver, resume_noirq);
	वापस device_क्रम_each_child(dev, &off, pm_iter);
पूर्ण

/**
 * pcie_port_device_resume - resume port services associated with a PCIe port
 * @dev: PCI Express port to handle
 */
पूर्णांक pcie_port_device_resume(काष्ठा device *dev)
अणु
	माप_प्रकार off = दुरत्व(काष्ठा pcie_port_service_driver, resume);
	वापस device_क्रम_each_child(dev, &off, pm_iter);
पूर्ण

/**
 * pcie_port_device_runसमय_suspend - runसमय suspend port services
 * @dev: PCI Express port to handle
 */
पूर्णांक pcie_port_device_runसमय_suspend(काष्ठा device *dev)
अणु
	माप_प्रकार off = दुरत्व(काष्ठा pcie_port_service_driver, runसमय_suspend);
	वापस device_क्रम_each_child(dev, &off, pm_iter);
पूर्ण

/**
 * pcie_port_device_runसमय_resume - runसमय resume port services
 * @dev: PCI Express port to handle
 */
पूर्णांक pcie_port_device_runसमय_resume(काष्ठा device *dev)
अणु
	माप_प्रकार off = दुरत्व(काष्ठा pcie_port_service_driver, runसमय_resume);
	वापस device_क्रम_each_child(dev, &off, pm_iter);
पूर्ण
#पूर्ण_अगर /* PM */

अटल पूर्णांक हटाओ_iter(काष्ठा device *dev, व्योम *data)
अणु
	अगर (dev->bus == &pcie_port_bus_type)
		device_unरेजिस्टर(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक find_service_iter(काष्ठा device *device, व्योम *data)
अणु
	काष्ठा pcie_port_service_driver *service_driver;
	काष्ठा portdrv_service_data *pdrvs;
	u32 service;

	pdrvs = (काष्ठा portdrv_service_data *) data;
	service = pdrvs->service;

	अगर (device->bus == &pcie_port_bus_type && device->driver) अणु
		service_driver = to_service_driver(device->driver);
		अगर (service_driver->service == service) अणु
			pdrvs->drv = service_driver;
			pdrvs->dev = device;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pcie_port_find_device - find the काष्ठा device
 * @dev: PCI Express port the service is associated with
 * @service: For the service to find
 *
 * Find the काष्ठा device associated with given service on a pci_dev
 */
काष्ठा device *pcie_port_find_device(काष्ठा pci_dev *dev,
				      u32 service)
अणु
	काष्ठा device *device;
	काष्ठा portdrv_service_data pdrvs;

	pdrvs.dev = शून्य;
	pdrvs.service = service;
	device_क्रम_each_child(&dev->dev, &pdrvs, find_service_iter);

	device = pdrvs.dev;
	वापस device;
पूर्ण
EXPORT_SYMBOL_GPL(pcie_port_find_device);

/**
 * pcie_port_device_हटाओ - unरेजिस्टर PCI Express port service devices
 * @dev: PCI Express port the service devices to unरेजिस्टर are associated with
 *
 * Remove PCI Express port service devices associated with given port and
 * disable MSI-X or MSI क्रम the port.
 */
व्योम pcie_port_device_हटाओ(काष्ठा pci_dev *dev)
अणु
	device_क्रम_each_child(&dev->dev, शून्य, हटाओ_iter);
	pci_मुक्त_irq_vectors(dev);
	pci_disable_device(dev);
पूर्ण

/**
 * pcie_port_probe_service - probe driver क्रम given PCI Express port service
 * @dev: PCI Express port service device to probe against
 *
 * If PCI Express port service driver is रेजिस्टरed with
 * pcie_port_service_रेजिस्टर(), this function will be called by the driver core
 * whenever match is found between the driver and a port service device.
 */
अटल पूर्णांक pcie_port_probe_service(काष्ठा device *dev)
अणु
	काष्ठा pcie_device *pciedev;
	काष्ठा pcie_port_service_driver *driver;
	पूर्णांक status;

	अगर (!dev || !dev->driver)
		वापस -ENODEV;

	driver = to_service_driver(dev->driver);
	अगर (!driver || !driver->probe)
		वापस -ENODEV;

	pciedev = to_pcie_device(dev);
	status = driver->probe(pciedev);
	अगर (status)
		वापस status;

	get_device(dev);
	वापस 0;
पूर्ण

/**
 * pcie_port_हटाओ_service - detach driver from given PCI Express port service
 * @dev: PCI Express port service device to handle
 *
 * If PCI Express port service driver is रेजिस्टरed with
 * pcie_port_service_रेजिस्टर(), this function will be called by the driver core
 * when device_unरेजिस्टर() is called क्रम the port service device associated
 * with the driver.
 */
अटल पूर्णांक pcie_port_हटाओ_service(काष्ठा device *dev)
अणु
	काष्ठा pcie_device *pciedev;
	काष्ठा pcie_port_service_driver *driver;

	अगर (!dev || !dev->driver)
		वापस 0;

	pciedev = to_pcie_device(dev);
	driver = to_service_driver(dev->driver);
	अगर (driver && driver->हटाओ) अणु
		driver->हटाओ(pciedev);
		put_device(dev);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pcie_port_shutकरोwn_service - shut करोwn given PCI Express port service
 * @dev: PCI Express port service device to handle
 *
 * If PCI Express port service driver is रेजिस्टरed with
 * pcie_port_service_रेजिस्टर(), this function will be called by the driver core
 * when device_shutकरोwn() is called क्रम the port service device associated
 * with the driver.
 */
अटल व्योम pcie_port_shutकरोwn_service(काष्ठा device *dev) अणुपूर्ण

/**
 * pcie_port_service_रेजिस्टर - रेजिस्टर PCI Express port service driver
 * @new: PCI Express port service driver to रेजिस्टर
 */
पूर्णांक pcie_port_service_रेजिस्टर(काष्ठा pcie_port_service_driver *new)
अणु
	अगर (pcie_ports_disabled)
		वापस -ENODEV;

	new->driver.name = new->name;
	new->driver.bus = &pcie_port_bus_type;
	new->driver.probe = pcie_port_probe_service;
	new->driver.हटाओ = pcie_port_हटाओ_service;
	new->driver.shutकरोwn = pcie_port_shutकरोwn_service;

	वापस driver_रेजिस्टर(&new->driver);
पूर्ण
EXPORT_SYMBOL(pcie_port_service_रेजिस्टर);

/**
 * pcie_port_service_unरेजिस्टर - unरेजिस्टर PCI Express port service driver
 * @drv: PCI Express port service driver to unरेजिस्टर
 */
व्योम pcie_port_service_unरेजिस्टर(काष्ठा pcie_port_service_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(pcie_port_service_unरेजिस्टर);
