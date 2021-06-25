<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe Native PME support
 *
 * Copyright (C) 2007 - 2009 Intel Corp
 * Copyright (C) 2007 - 2009 Shaohua Li <shaohua.li@पूर्णांकel.com>
 * Copyright (C) 2009 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 */

#घोषणा dev_fmt(fmt) "PME: " fmt

#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "../pci.h"
#समावेश "portdrv.h"

/*
 * If this चयन is set, MSI will not be used क्रम PCIe PME संकेतing.  This
 * causes the PCIe port driver to use INTx पूर्णांकerrupts only, but it turns out
 * that using MSI क्रम PCIe PME संकेतing करोesn't play well with PCIe PME-based
 * wake-up from प्रणाली sleep states.
 */
bool pcie_pme_msi_disabled;

अटल पूर्णांक __init pcie_pme_setup(अक्षर *str)
अणु
	अगर (!म_भेदन(str, "nomsi", 5))
		pcie_pme_msi_disabled = true;

	वापस 1;
पूर्ण
__setup("pcie_pme=", pcie_pme_setup);

काष्ठा pcie_pme_service_data अणु
	spinlock_t lock;
	काष्ठा pcie_device *srv;
	काष्ठा work_काष्ठा work;
	bool noirq; /* If set, keep the PME पूर्णांकerrupt disabled. */
पूर्ण;

/**
 * pcie_pme_पूर्णांकerrupt_enable - Enable/disable PCIe PME पूर्णांकerrupt generation.
 * @dev: PCIe root port or event collector.
 * @enable: Enable or disable the पूर्णांकerrupt.
 */
व्योम pcie_pme_पूर्णांकerrupt_enable(काष्ठा pci_dev *dev, bool enable)
अणु
	अगर (enable)
		pcie_capability_set_word(dev, PCI_EXP_RTCTL,
					 PCI_EXP_RTCTL_PMEIE);
	अन्यथा
		pcie_capability_clear_word(dev, PCI_EXP_RTCTL,
					   PCI_EXP_RTCTL_PMEIE);
पूर्ण

/**
 * pcie_pme_walk_bus - Scan a PCI bus क्रम devices निश्चितing PME#.
 * @bus: PCI bus to scan.
 *
 * Scan given PCI bus and all buses under it क्रम devices निश्चितing PME#.
 */
अटल bool pcie_pme_walk_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;
	bool ret = false;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		/* Skip PCIe devices in हाल we started from a root port. */
		अगर (!pci_is_pcie(dev) && pci_check_pme_status(dev)) अणु
			अगर (dev->pme_poll)
				dev->pme_poll = false;

			pci_wakeup_event(dev);
			pm_request_resume(&dev->dev);
			ret = true;
		पूर्ण

		अगर (dev->subordinate && pcie_pme_walk_bus(dev->subordinate))
			ret = true;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * pcie_pme_from_pci_bridge - Check अगर PCIe-PCI bridge generated a PME.
 * @bus: Secondary bus of the bridge.
 * @devfn: Device/function number to check.
 *
 * PME from PCI devices under a PCIe-PCI bridge may be converted to an in-band
 * PCIe PME message.  In such that हाल the bridge should use the Requester ID
 * of device/function number 0 on its secondary bus.
 */
अटल bool pcie_pme_from_pci_bridge(काष्ठा pci_bus *bus, u8 devfn)
अणु
	काष्ठा pci_dev *dev;
	bool found = false;

	अगर (devfn)
		वापस false;

	dev = pci_dev_get(bus->self);
	अगर (!dev)
		वापस false;

	अगर (pci_is_pcie(dev) && pci_pcie_type(dev) == PCI_EXP_TYPE_PCI_BRIDGE) अणु
		करोwn_पढ़ो(&pci_bus_sem);
		अगर (pcie_pme_walk_bus(bus))
			found = true;
		up_पढ़ो(&pci_bus_sem);
	पूर्ण

	pci_dev_put(dev);
	वापस found;
पूर्ण

/**
 * pcie_pme_handle_request - Find device that generated PME and handle it.
 * @port: Root port or event collector that generated the PME पूर्णांकerrupt.
 * @req_id: PCIe Requester ID of the device that generated the PME.
 */
अटल व्योम pcie_pme_handle_request(काष्ठा pci_dev *port, u16 req_id)
अणु
	u8 busnr = req_id >> 8, devfn = req_id & 0xff;
	काष्ठा pci_bus *bus;
	काष्ठा pci_dev *dev;
	bool found = false;

	/* First, check अगर the PME is from the root port itself. */
	अगर (port->devfn == devfn && port->bus->number == busnr) अणु
		अगर (port->pme_poll)
			port->pme_poll = false;

		अगर (pci_check_pme_status(port)) अणु
			pm_request_resume(&port->dev);
			found = true;
		पूर्ण अन्यथा अणु
			/*
			 * Apparently, the root port generated the PME on behalf
			 * of a non-PCIe device करोwnstream.  If this is करोne by
			 * a root port, the Requester ID field in its status
			 * रेजिस्टर may contain either the root port's, or the
			 * source device's inक्रमmation (PCI Express Base
			 * Specअगरication, Rev. 2.0, Section 6.1.9).
			 */
			करोwn_पढ़ो(&pci_bus_sem);
			found = pcie_pme_walk_bus(port->subordinate);
			up_पढ़ो(&pci_bus_sem);
		पूर्ण
		जाओ out;
	पूर्ण

	/* Second, find the bus the source device is on. */
	bus = pci_find_bus(pci_करोमुख्य_nr(port->bus), busnr);
	अगर (!bus)
		जाओ out;

	/* Next, check अगर the PME is from a PCIe-PCI bridge. */
	found = pcie_pme_from_pci_bridge(bus, devfn);
	अगर (found)
		जाओ out;

	/* Finally, try to find the PME source on the bus. */
	करोwn_पढ़ो(&pci_bus_sem);
	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		pci_dev_get(dev);
		अगर (dev->devfn == devfn) अणु
			found = true;
			अवरोध;
		पूर्ण
		pci_dev_put(dev);
	पूर्ण
	up_पढ़ो(&pci_bus_sem);

	अगर (found) अणु
		/* The device is there, but we have to check its PME status. */
		found = pci_check_pme_status(dev);
		अगर (found) अणु
			अगर (dev->pme_poll)
				dev->pme_poll = false;

			pci_wakeup_event(dev);
			pm_request_resume(&dev->dev);
		पूर्ण
		pci_dev_put(dev);
	पूर्ण अन्यथा अगर (devfn) अणु
		/*
		 * The device is not there, but we can still try to recover by
		 * assuming that the PME was reported by a PCIe-PCI bridge that
		 * used devfn dअगरferent from zero.
		 */
		pci_info(port, "interrupt generated for non-existent device %02x:%02x.%d\n",
			 busnr, PCI_SLOT(devfn), PCI_FUNC(devfn));
		found = pcie_pme_from_pci_bridge(bus, 0);
	पूर्ण

 out:
	अगर (!found)
		pci_info(port, "Spurious native interrupt!\n");
पूर्ण

/**
 * pcie_pme_work_fn - Work handler क्रम PCIe PME पूर्णांकerrupt.
 * @work: Work काष्ठाure giving access to service data.
 */
अटल व्योम pcie_pme_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pcie_pme_service_data *data =
			container_of(work, काष्ठा pcie_pme_service_data, work);
	काष्ठा pci_dev *port = data->srv->port;
	u32 rtsta;

	spin_lock_irq(&data->lock);

	क्रम (;;) अणु
		अगर (data->noirq)
			अवरोध;

		pcie_capability_पढ़ो_dword(port, PCI_EXP_RTSTA, &rtsta);
		अगर (rtsta == (u32) ~0)
			अवरोध;

		अगर (rtsta & PCI_EXP_RTSTA_PME) अणु
			/*
			 * Clear PME status of the port.  If there are other
			 * pending PMEs, the status will be set again.
			 */
			pcie_clear_root_pme_status(port);

			spin_unlock_irq(&data->lock);
			pcie_pme_handle_request(port, rtsta & 0xffff);
			spin_lock_irq(&data->lock);

			जारी;
		पूर्ण

		/* No need to loop अगर there are no more PMEs pending. */
		अगर (!(rtsta & PCI_EXP_RTSTA_PENDING))
			अवरोध;

		spin_unlock_irq(&data->lock);
		cpu_relax();
		spin_lock_irq(&data->lock);
	पूर्ण

	अगर (!data->noirq)
		pcie_pme_पूर्णांकerrupt_enable(port, true);

	spin_unlock_irq(&data->lock);
पूर्ण

/**
 * pcie_pme_irq - Interrupt handler क्रम PCIe root port PME पूर्णांकerrupt.
 * @irq: Interrupt vector.
 * @context: Interrupt context poपूर्णांकer.
 */
अटल irqवापस_t pcie_pme_irq(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा pci_dev *port;
	काष्ठा pcie_pme_service_data *data;
	u32 rtsta;
	अचिन्हित दीर्घ flags;

	port = ((काष्ठा pcie_device *)context)->port;
	data = get_service_data((काष्ठा pcie_device *)context);

	spin_lock_irqsave(&data->lock, flags);
	pcie_capability_पढ़ो_dword(port, PCI_EXP_RTSTA, &rtsta);

	अगर (rtsta == (u32) ~0 || !(rtsta & PCI_EXP_RTSTA_PME)) अणु
		spin_unlock_irqrestore(&data->lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	pcie_pme_पूर्णांकerrupt_enable(port, false);
	spin_unlock_irqrestore(&data->lock, flags);

	/* We करोn't use pm_wq, because it's मुक्तzable. */
	schedule_work(&data->work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * pcie_pme_can_wakeup - Set the wakeup capability flag.
 * @dev: PCI device to handle.
 * @ign: Ignored.
 */
अटल पूर्णांक pcie_pme_can_wakeup(काष्ठा pci_dev *dev, व्योम *ign)
अणु
	device_set_wakeup_capable(&dev->dev, true);
	वापस 0;
पूर्ण

/**
 * pcie_pme_mark_devices - Set the wakeup flag क्रम devices below a port.
 * @port: PCIe root port or event collector to handle.
 *
 * For each device below given root port, including the port itself (or क्रम each
 * root complex पूर्णांकegrated endpoपूर्णांक अगर @port is a root complex event collector)
 * set the flag indicating that it can संकेत run-समय wake-up events.
 */
अटल व्योम pcie_pme_mark_devices(काष्ठा pci_dev *port)
अणु
	pcie_pme_can_wakeup(port, शून्य);

	अगर (pci_pcie_type(port) == PCI_EXP_TYPE_RC_EC)
		pcie_walk_rcec(port, pcie_pme_can_wakeup, शून्य);
	अन्यथा अगर (port->subordinate)
		pci_walk_bus(port->subordinate, pcie_pme_can_wakeup, शून्य);
पूर्ण

/**
 * pcie_pme_probe - Initialize PCIe PME service क्रम given root port.
 * @srv: PCIe service to initialize.
 */
अटल पूर्णांक pcie_pme_probe(काष्ठा pcie_device *srv)
अणु
	काष्ठा pci_dev *port = srv->port;
	काष्ठा pcie_pme_service_data *data;
	पूर्णांक type = pci_pcie_type(port);
	पूर्णांक ret;

	/* Limit to Root Ports or Root Complex Event Collectors */
	अगर (type != PCI_EXP_TYPE_RC_EC &&
	    type != PCI_EXP_TYPE_ROOT_PORT)
		वापस -ENODEV;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spin_lock_init(&data->lock);
	INIT_WORK(&data->work, pcie_pme_work_fn);
	data->srv = srv;
	set_service_data(srv, data);

	pcie_pme_पूर्णांकerrupt_enable(port, false);
	pcie_clear_root_pme_status(port);

	ret = request_irq(srv->irq, pcie_pme_irq, IRQF_SHARED, "PCIe PME", srv);
	अगर (ret) अणु
		kमुक्त(data);
		वापस ret;
	पूर्ण

	pci_info(port, "Signaling with IRQ %d\n", srv->irq);

	pcie_pme_mark_devices(port);
	pcie_pme_पूर्णांकerrupt_enable(port, true);
	वापस 0;
पूर्ण

अटल bool pcie_pme_check_wakeup(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	अगर (!bus)
		वापस false;

	list_क्रम_each_entry(dev, &bus->devices, bus_list)
		अगर (device_may_wakeup(&dev->dev)
		    || pcie_pme_check_wakeup(dev->subordinate))
			वापस true;

	वापस false;
पूर्ण

अटल व्योम pcie_pme_disable_पूर्णांकerrupt(काष्ठा pci_dev *port,
				       काष्ठा pcie_pme_service_data *data)
अणु
	spin_lock_irq(&data->lock);
	pcie_pme_पूर्णांकerrupt_enable(port, false);
	pcie_clear_root_pme_status(port);
	data->noirq = true;
	spin_unlock_irq(&data->lock);
पूर्ण

/**
 * pcie_pme_suspend - Suspend PCIe PME service device.
 * @srv: PCIe service device to suspend.
 */
अटल पूर्णांक pcie_pme_suspend(काष्ठा pcie_device *srv)
अणु
	काष्ठा pcie_pme_service_data *data = get_service_data(srv);
	काष्ठा pci_dev *port = srv->port;
	bool wakeup;
	पूर्णांक ret;

	अगर (device_may_wakeup(&port->dev)) अणु
		wakeup = true;
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&pci_bus_sem);
		wakeup = pcie_pme_check_wakeup(port->subordinate);
		up_पढ़ो(&pci_bus_sem);
	पूर्ण
	अगर (wakeup) अणु
		ret = enable_irq_wake(srv->irq);
		अगर (!ret)
			वापस 0;
	पूर्ण

	pcie_pme_disable_पूर्णांकerrupt(port, data);

	synchronize_irq(srv->irq);

	वापस 0;
पूर्ण

/**
 * pcie_pme_resume - Resume PCIe PME service device.
 * @srv: PCIe service device to resume.
 */
अटल पूर्णांक pcie_pme_resume(काष्ठा pcie_device *srv)
अणु
	काष्ठा pcie_pme_service_data *data = get_service_data(srv);

	spin_lock_irq(&data->lock);
	अगर (data->noirq) अणु
		काष्ठा pci_dev *port = srv->port;

		pcie_clear_root_pme_status(port);
		pcie_pme_पूर्णांकerrupt_enable(port, true);
		data->noirq = false;
	पूर्ण अन्यथा अणु
		disable_irq_wake(srv->irq);
	पूर्ण
	spin_unlock_irq(&data->lock);

	वापस 0;
पूर्ण

/**
 * pcie_pme_हटाओ - Prepare PCIe PME service device क्रम removal.
 * @srv: PCIe service device to हटाओ.
 */
अटल व्योम pcie_pme_हटाओ(काष्ठा pcie_device *srv)
अणु
	काष्ठा pcie_pme_service_data *data = get_service_data(srv);

	pcie_pme_disable_पूर्णांकerrupt(srv->port, data);
	मुक्त_irq(srv->irq, srv);
	cancel_work_sync(&data->work);
	kमुक्त(data);
पूर्ण

अटल काष्ठा pcie_port_service_driver pcie_pme_driver = अणु
	.name		= "pcie_pme",
	.port_type	= PCIE_ANY_PORT,
	.service	= PCIE_PORT_SERVICE_PME,

	.probe		= pcie_pme_probe,
	.suspend	= pcie_pme_suspend,
	.resume		= pcie_pme_resume,
	.हटाओ		= pcie_pme_हटाओ,
पूर्ण;

/**
 * pcie_pme_init - Register the PCIe PME service driver.
 */
पूर्णांक __init pcie_pme_init(व्योम)
अणु
	वापस pcie_port_service_रेजिस्टर(&pcie_pme_driver);
पूर्ण
