<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Purpose:	PCI Express Port Bus Driver
 * Author:	Tom Nguyen <tom.l.nguyen@पूर्णांकel.com>
 *
 * Copyright (C) 2004 Intel
 * Copyright (C) Tom Long Nguyen (tom.l.nguyen@पूर्णांकel.com)
 */

#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/init.h>
#समावेश <linux/aer.h>
#समावेश <linux/dmi.h>

#समावेश "../pci.h"
#समावेश "portdrv.h"

/* If this चयन is set, PCIe port native services should not be enabled. */
bool pcie_ports_disabled;

/*
 * If the user specअगरied "pcie_ports=native", use the PCIe services regardless
 * of whether the platक्रमm has given us permission.  On ACPI प्रणालीs, this
 * means we ignore _OSC.
 */
bool pcie_ports_native;

/*
 * If the user specअगरied "pcie_ports=dpc-native", use the Linux DPC PCIe
 * service even अगर the platक्रमm hasn't given us permission.
 */
bool pcie_ports_dpc_native;

अटल पूर्णांक __init pcie_port_setup(अक्षर *str)
अणु
	अगर (!म_भेदन(str, "compat", 6))
		pcie_ports_disabled = true;
	अन्यथा अगर (!म_भेदन(str, "native", 6))
		pcie_ports_native = true;
	अन्यथा अगर (!म_भेदन(str, "dpc-native", 10))
		pcie_ports_dpc_native = true;

	वापस 1;
पूर्ण
__setup("pcie_ports=", pcie_port_setup);

/* global data */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pcie_port_runसमय_suspend(काष्ठा device *dev)
अणु
	अगर (!to_pci_dev(dev)->bridge_d3)
		वापस -EBUSY;

	वापस pcie_port_device_runसमय_suspend(dev);
पूर्ण

अटल पूर्णांक pcie_port_runसमय_idle(काष्ठा device *dev)
अणु
	/*
	 * Assume the PCI core has set bridge_d3 whenever it thinks the port
	 * should be good to go to D3.  Everything अन्यथा, including moving
	 * the port to D3, is handled by the PCI core.
	 */
	वापस to_pci_dev(dev)->bridge_d3 ? 0 : -EBUSY;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pcie_portdrv_pm_ops = अणु
	.suspend	= pcie_port_device_suspend,
	.resume_noirq	= pcie_port_device_resume_noirq,
	.resume		= pcie_port_device_resume,
	.मुक्तze		= pcie_port_device_suspend,
	.thaw		= pcie_port_device_resume,
	.घातeroff	= pcie_port_device_suspend,
	.restore_noirq	= pcie_port_device_resume_noirq,
	.restore	= pcie_port_device_resume,
	.runसमय_suspend = pcie_port_runसमय_suspend,
	.runसमय_resume	= pcie_port_device_runसमय_resume,
	.runसमय_idle	= pcie_port_runसमय_idle,
पूर्ण;

#घोषणा PCIE_PORTDRV_PM_OPS	(&pcie_portdrv_pm_ops)

#अन्यथा /* !PM */

#घोषणा PCIE_PORTDRV_PM_OPS	शून्य
#पूर्ण_अगर /* !PM */

/*
 * pcie_portdrv_probe - Probe PCI-Express port devices
 * @dev: PCI-Express port device being probed
 *
 * If detected invokes the pcie_port_device_रेजिस्टर() method क्रम
 * this port device.
 *
 */
अटल पूर्णांक pcie_portdrv_probe(काष्ठा pci_dev *dev,
					स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक type = pci_pcie_type(dev);
	पूर्णांक status;

	अगर (!pci_is_pcie(dev) ||
	    ((type != PCI_EXP_TYPE_ROOT_PORT) &&
	     (type != PCI_EXP_TYPE_UPSTREAM) &&
	     (type != PCI_EXP_TYPE_DOWNSTREAM) &&
	     (type != PCI_EXP_TYPE_RC_EC)))
		वापस -ENODEV;

	अगर (type == PCI_EXP_TYPE_RC_EC)
		pcie_link_rcec(dev);

	status = pcie_port_device_रेजिस्टर(dev);
	अगर (status)
		वापस status;

	pci_save_state(dev);

	dev_pm_set_driver_flags(&dev->dev, DPM_FLAG_NO_सूचीECT_COMPLETE |
					   DPM_FLAG_SMART_SUSPEND);

	अगर (pci_bridge_d3_possible(dev)) अणु
		/*
		 * Keep the port resumed 100ms to make sure things like
		 * config space accesses from userspace (lspci) will not
		 * cause the port to repeatedly suspend and resume.
		 */
		pm_runसमय_set_स्वतःsuspend_delay(&dev->dev, 100);
		pm_runसमय_use_स्वतःsuspend(&dev->dev);
		pm_runसमय_mark_last_busy(&dev->dev);
		pm_runसमय_put_स्वतःsuspend(&dev->dev);
		pm_runसमय_allow(&dev->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pcie_portdrv_हटाओ(काष्ठा pci_dev *dev)
अणु
	अगर (pci_bridge_d3_possible(dev)) अणु
		pm_runसमय_क्रमbid(&dev->dev);
		pm_runसमय_get_noresume(&dev->dev);
		pm_runसमय_करोnt_use_स्वतःsuspend(&dev->dev);
	पूर्ण

	pcie_port_device_हटाओ(dev);
पूर्ण

अटल pci_ers_result_t pcie_portdrv_error_detected(काष्ठा pci_dev *dev,
					pci_channel_state_t error)
अणु
	अगर (error == pci_channel_io_frozen)
		वापस PCI_ERS_RESULT_NEED_RESET;
	वापस PCI_ERS_RESULT_CAN_RECOVER;
पूर्ण

अटल pci_ers_result_t pcie_portdrv_slot_reset(काष्ठा pci_dev *dev)
अणु
	pci_restore_state(dev);
	pci_save_state(dev);
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल pci_ers_result_t pcie_portdrv_mmio_enabled(काष्ठा pci_dev *dev)
अणु
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल पूर्णांक resume_iter(काष्ठा device *device, व्योम *data)
अणु
	काष्ठा pcie_device *pcie_device;
	काष्ठा pcie_port_service_driver *driver;

	अगर (device->bus == &pcie_port_bus_type && device->driver) अणु
		driver = to_service_driver(device->driver);
		अगर (driver && driver->error_resume) अणु
			pcie_device = to_pcie_device(device);

			/* Forward error message to service drivers */
			driver->error_resume(pcie_device->port);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pcie_portdrv_err_resume(काष्ठा pci_dev *dev)
अणु
	device_क्रम_each_child(&dev->dev, शून्य, resume_iter);
पूर्ण

/*
 * LINUX Device Driver Model
 */
अटल स्थिर काष्ठा pci_device_id port_pci_ids[] = अणु
	/* handle any PCI-Express port */
	अणु PCI_DEVICE_CLASS(((PCI_CLASS_BRIDGE_PCI << 8) | 0x00), ~0) पूर्ण,
	/* subtractive decode PCI-to-PCI bridge, class type is 060401h */
	अणु PCI_DEVICE_CLASS(((PCI_CLASS_BRIDGE_PCI << 8) | 0x01), ~0) पूर्ण,
	/* handle any Root Complex Event Collector */
	अणु PCI_DEVICE_CLASS(((PCI_CLASS_SYSTEM_RCEC << 8) | 0x00), ~0) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_error_handlers pcie_portdrv_err_handler = अणु
	.error_detected = pcie_portdrv_error_detected,
	.slot_reset = pcie_portdrv_slot_reset,
	.mmio_enabled = pcie_portdrv_mmio_enabled,
	.resume = pcie_portdrv_err_resume,
पूर्ण;

अटल काष्ठा pci_driver pcie_portdriver = अणु
	.name		= "pcieport",
	.id_table	= &port_pci_ids[0],

	.probe		= pcie_portdrv_probe,
	.हटाओ		= pcie_portdrv_हटाओ,
	.shutकरोwn	= pcie_portdrv_हटाओ,

	.err_handler	= &pcie_portdrv_err_handler,

	.driver.pm	= PCIE_PORTDRV_PM_OPS,
पूर्ण;

अटल पूर्णांक __init dmi_pcie_pme_disable_msi(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	pr_notice("%s detected: will not use MSI for PCIe PME signaling\n",
		  d->ident);
	pcie_pme_disable_msi();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id pcie_portdrv_dmi_table[] __initस्थिर = अणु
	/*
	 * Boxes that should not use MSI क्रम PCIe PME संकेतing.
	 */
	अणु
	 .callback = dmi_pcie_pme_disable_msi,
	 .ident = "MSI Wind U-100",
	 .matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR,
				"MICRO-STAR INTERNATIONAL CO., LTD"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "U-100"),
		     पूर्ण,
	 पूर्ण,
	 अणुपूर्ण
पूर्ण;

अटल व्योम __init pcie_init_services(व्योम)
अणु
	pcie_aer_init();
	pcie_pme_init();
	pcie_dpc_init();
	pcie_hp_init();
पूर्ण

अटल पूर्णांक __init pcie_portdrv_init(व्योम)
अणु
	अगर (pcie_ports_disabled)
		वापस -EACCES;

	pcie_init_services();
	dmi_check_प्रणाली(pcie_portdrv_dmi_table);

	वापस pci_रेजिस्टर_driver(&pcie_portdriver);
पूर्ण
device_initcall(pcie_portdrv_init);
