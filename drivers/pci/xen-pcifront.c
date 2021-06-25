<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xen PCI Frontend
 *
 * Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/events.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/page.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <xen/पूर्णांकerface/io/pciअगर.h>
#समावेश <यंत्र/xen/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/atomic.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <linux/समय.स>
#समावेश <linux/kसमय.स>
#समावेश <linux/swiotlb.h>
#समावेश <xen/platक्रमm_pci.h>

#समावेश <यंत्र/xen/swiotlb-xen.h>

#घोषणा INVALID_EVTCHN    (-1)

काष्ठा pci_bus_entry अणु
	काष्ठा list_head list;
	काष्ठा pci_bus *bus;
पूर्ण;

#घोषणा _PDEVB_op_active		(0)
#घोषणा PDEVB_op_active			(1 << (_PDEVB_op_active))

काष्ठा pcअगरront_device अणु
	काष्ठा xenbus_device *xdev;
	काष्ठा list_head root_buses;

	पूर्णांक evtchn;
	grant_ref_t gnt_ref;

	पूर्णांक irq;

	/* Lock this when करोing any operations in sh_info */
	spinlock_t sh_info_lock;
	काष्ठा xen_pci_sharedinfo *sh_info;
	काष्ठा work_काष्ठा op_work;
	अचिन्हित दीर्घ flags;

पूर्ण;

काष्ठा pcअगरront_sd अणु
	काष्ठा pci_sysdata sd;
	काष्ठा pcअगरront_device *pdev;
पूर्ण;

अटल अंतरभूत काष्ठा pcअगरront_device *
pcअगरront_get_pdev(काष्ठा pcअगरront_sd *sd)
अणु
	वापस sd->pdev;
पूर्ण

अटल अंतरभूत व्योम pcअगरront_init_sd(काष्ठा pcअगरront_sd *sd,
				    अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus,
				    काष्ठा pcअगरront_device *pdev)
अणु
	/* Because we करो not expose that inक्रमmation via XenBus. */
	sd->sd.node = first_online_node;
	sd->sd.करोमुख्य = करोमुख्य;
	sd->pdev = pdev;
पूर्ण

अटल DEFINE_SPINLOCK(pcअगरront_dev_lock);
अटल काष्ठा pcअगरront_device *pcअगरront_dev;

अटल पूर्णांक त्रुटि_सं_to_pcibios_err(पूर्णांक त्रुटि_सं)
अणु
	चयन (त्रुटि_सं) अणु
	हाल XEN_PCI_ERR_success:
		वापस PCIBIOS_SUCCESSFUL;

	हाल XEN_PCI_ERR_dev_not_found:
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	हाल XEN_PCI_ERR_invalid_offset:
	हाल XEN_PCI_ERR_op_failed:
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	हाल XEN_PCI_ERR_not_implemented:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;

	हाल XEN_PCI_ERR_access_denied:
		वापस PCIBIOS_SET_FAILED;
	पूर्ण
	वापस त्रुटि_सं;
पूर्ण

अटल अंतरभूत व्योम schedule_pcअगरront_aer_op(काष्ठा pcअगरront_device *pdev)
अणु
	अगर (test_bit(_XEN_PCIB_active, (अचिन्हित दीर्घ *)&pdev->sh_info->flags)
		&& !test_and_set_bit(_PDEVB_op_active, &pdev->flags)) अणु
		dev_dbg(&pdev->xdev->dev, "schedule aer frontend job\n");
		schedule_work(&pdev->op_work);
	पूर्ण
पूर्ण

अटल पूर्णांक करो_pci_op(काष्ठा pcअगरront_device *pdev, काष्ठा xen_pci_op *op)
अणु
	पूर्णांक err = 0;
	काष्ठा xen_pci_op *active_op = &pdev->sh_info->op;
	अचिन्हित दीर्घ irq_flags;
	evtchn_port_t port = pdev->evtchn;
	अचिन्हित irq = pdev->irq;
	s64 ns, ns_समयout;

	spin_lock_irqsave(&pdev->sh_info_lock, irq_flags);

	स_नकल(active_op, op, माप(काष्ठा xen_pci_op));

	/* Go */
	wmb();
	set_bit(_XEN_PCIF_active, (अचिन्हित दीर्घ *)&pdev->sh_info->flags);
	notअगरy_remote_via_evtchn(port);

	/*
	 * We set a poll समयout of 3 seconds but give up on वापस after
	 * 2 seconds. It is better to समय out too late rather than too early
	 * (in the latter हाल we end up continually re-executing poll() with a
	 * समयout in the past). 1s dअगरference gives plenty of slack क्रम error.
	 */
	ns_समयout = kसमय_get_ns() + 2 * (s64)NSEC_PER_SEC;

	xen_clear_irq_pending(irq);

	जबतक (test_bit(_XEN_PCIF_active,
			(अचिन्हित दीर्घ *)&pdev->sh_info->flags)) अणु
		xen_poll_irq_समयout(irq, jअगरfies + 3*HZ);
		xen_clear_irq_pending(irq);
		ns = kसमय_get_ns();
		अगर (ns > ns_समयout) अणु
			dev_err(&pdev->xdev->dev,
				"pciback not responding!!!\n");
			clear_bit(_XEN_PCIF_active,
				  (अचिन्हित दीर्घ *)&pdev->sh_info->flags);
			err = XEN_PCI_ERR_dev_not_found;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	* We might lose backend service request since we
	* reuse same evtchn with pci_conf backend response. So re-schedule
	* aer pcअगरront service.
	*/
	अगर (test_bit(_XEN_PCIB_active,
			(अचिन्हित दीर्घ *)&pdev->sh_info->flags)) अणु
		dev_err(&pdev->xdev->dev,
			"schedule aer pcifront service\n");
		schedule_pcअगरront_aer_op(pdev);
	पूर्ण

	स_नकल(op, active_op, माप(काष्ठा xen_pci_op));

	err = op->err;
out:
	spin_unlock_irqrestore(&pdev->sh_info_lock, irq_flags);
	वापस err;
पूर्ण

/* Access to this function is spinlocked in drivers/pci/access.c */
अटल पूर्णांक pcअगरront_bus_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	पूर्णांक err = 0;
	काष्ठा xen_pci_op op = अणु
		.cmd    = XEN_PCI_OP_conf_पढ़ो,
		.करोमुख्य = pci_करोमुख्य_nr(bus),
		.bus    = bus->number,
		.devfn  = devfn,
		.offset = where,
		.size   = size,
	पूर्ण;
	काष्ठा pcअगरront_sd *sd = bus->sysdata;
	काष्ठा pcअगरront_device *pdev = pcअगरront_get_pdev(sd);

	dev_dbg(&pdev->xdev->dev,
		"read dev=%04x:%02x:%02x.%d - offset %x size %d\n",
		pci_करोमुख्य_nr(bus), bus->number, PCI_SLOT(devfn),
		PCI_FUNC(devfn), where, size);

	err = करो_pci_op(pdev, &op);

	अगर (likely(!err)) अणु
		dev_dbg(&pdev->xdev->dev, "read got back value %x\n",
			op.value);

		*val = op.value;
	पूर्ण अन्यथा अगर (err == -ENODEV) अणु
		/* No device here, pretend that it just वापसed 0 */
		err = 0;
		*val = 0;
	पूर्ण

	वापस त्रुटि_सं_to_pcibios_err(err);
पूर्ण

/* Access to this function is spinlocked in drivers/pci/access.c */
अटल पूर्णांक pcअगरront_bus_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा xen_pci_op op = अणु
		.cmd    = XEN_PCI_OP_conf_ग_लिखो,
		.करोमुख्य = pci_करोमुख्य_nr(bus),
		.bus    = bus->number,
		.devfn  = devfn,
		.offset = where,
		.size   = size,
		.value  = val,
	पूर्ण;
	काष्ठा pcअगरront_sd *sd = bus->sysdata;
	काष्ठा pcअगरront_device *pdev = pcअगरront_get_pdev(sd);

	dev_dbg(&pdev->xdev->dev,
		"write dev=%04x:%02x:%02x.%d - offset %x size %d val %x\n",
		pci_करोमुख्य_nr(bus), bus->number,
		PCI_SLOT(devfn), PCI_FUNC(devfn), where, size, val);

	वापस त्रुटि_सं_to_pcibios_err(करो_pci_op(pdev, &op));
पूर्ण

अटल काष्ठा pci_ops pcअगरront_bus_ops = अणु
	.पढ़ो = pcअगरront_bus_पढ़ो,
	.ग_लिखो = pcअगरront_bus_ग_लिखो,
पूर्ण;

#अगर_घोषित CONFIG_PCI_MSI
अटल पूर्णांक pci_frontend_enable_msix(काष्ठा pci_dev *dev,
				    पूर्णांक vector[], पूर्णांक nvec)
अणु
	पूर्णांक err;
	पूर्णांक i;
	काष्ठा xen_pci_op op = अणु
		.cmd    = XEN_PCI_OP_enable_msix,
		.करोमुख्य = pci_करोमुख्य_nr(dev->bus),
		.bus = dev->bus->number,
		.devfn = dev->devfn,
		.value = nvec,
	पूर्ण;
	काष्ठा pcअगरront_sd *sd = dev->bus->sysdata;
	काष्ठा pcअगरront_device *pdev = pcअगरront_get_pdev(sd);
	काष्ठा msi_desc *entry;

	अगर (nvec > SH_INFO_MAX_VEC) अणु
		pci_err(dev, "too many vectors (0x%x) for PCI frontend:"
				   " Increase SH_INFO_MAX_VEC\n", nvec);
		वापस -EINVAL;
	पूर्ण

	i = 0;
	क्रम_each_pci_msi_entry(entry, dev) अणु
		op.msix_entries[i].entry = entry->msi_attrib.entry_nr;
		/* Vector is useless at this poपूर्णांक. */
		op.msix_entries[i].vector = -1;
		i++;
	पूर्ण

	err = करो_pci_op(pdev, &op);

	अगर (likely(!err)) अणु
		अगर (likely(!op.value)) अणु
			/* we get the result */
			क्रम (i = 0; i < nvec; i++) अणु
				अगर (op.msix_entries[i].vector <= 0) अणु
					pci_warn(dev, "MSI-X entry %d is invalid: %d!\n",
						i, op.msix_entries[i].vector);
					err = -EINVAL;
					vector[i] = -1;
					जारी;
				पूर्ण
				vector[i] = op.msix_entries[i].vector;
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_info("enable msix get value %x\n", op.value);
			err = op.value;
		पूर्ण
	पूर्ण अन्यथा अणु
		pci_err(dev, "enable msix get err %x\n", err);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम pci_frontend_disable_msix(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err;
	काष्ठा xen_pci_op op = अणु
		.cmd    = XEN_PCI_OP_disable_msix,
		.करोमुख्य = pci_करोमुख्य_nr(dev->bus),
		.bus = dev->bus->number,
		.devfn = dev->devfn,
	पूर्ण;
	काष्ठा pcअगरront_sd *sd = dev->bus->sysdata;
	काष्ठा pcअगरront_device *pdev = pcअगरront_get_pdev(sd);

	err = करो_pci_op(pdev, &op);

	/* What should करो क्रम error ? */
	अगर (err)
		pci_err(dev, "pci_disable_msix get err %x\n", err);
पूर्ण

अटल पूर्णांक pci_frontend_enable_msi(काष्ठा pci_dev *dev, पूर्णांक vector[])
अणु
	पूर्णांक err;
	काष्ठा xen_pci_op op = अणु
		.cmd    = XEN_PCI_OP_enable_msi,
		.करोमुख्य = pci_करोमुख्य_nr(dev->bus),
		.bus = dev->bus->number,
		.devfn = dev->devfn,
	पूर्ण;
	काष्ठा pcअगरront_sd *sd = dev->bus->sysdata;
	काष्ठा pcअगरront_device *pdev = pcअगरront_get_pdev(sd);

	err = करो_pci_op(pdev, &op);
	अगर (likely(!err)) अणु
		vector[0] = op.value;
		अगर (op.value <= 0) अणु
			pci_warn(dev, "MSI entry is invalid: %d!\n",
				op.value);
			err = -EINVAL;
			vector[0] = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		pci_err(dev, "pci frontend enable msi failed for dev "
				    "%x:%x\n", op.bus, op.devfn);
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम pci_frontend_disable_msi(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err;
	काष्ठा xen_pci_op op = अणु
		.cmd    = XEN_PCI_OP_disable_msi,
		.करोमुख्य = pci_करोमुख्य_nr(dev->bus),
		.bus = dev->bus->number,
		.devfn = dev->devfn,
	पूर्ण;
	काष्ठा pcअगरront_sd *sd = dev->bus->sysdata;
	काष्ठा pcअगरront_device *pdev = pcअगरront_get_pdev(sd);

	err = करो_pci_op(pdev, &op);
	अगर (err == XEN_PCI_ERR_dev_not_found) अणु
		/* XXX No response from backend, what shall we करो? */
		pr_info("get no response from backend for disable MSI\n");
		वापस;
	पूर्ण
	अगर (err)
		/* how can pciback notअगरy us fail? */
		pr_info("get fake response from backend\n");
पूर्ण

अटल काष्ठा xen_pci_frontend_ops pci_frontend_ops = अणु
	.enable_msi = pci_frontend_enable_msi,
	.disable_msi = pci_frontend_disable_msi,
	.enable_msix = pci_frontend_enable_msix,
	.disable_msix = pci_frontend_disable_msix,
पूर्ण;

अटल व्योम pci_frontend_registrar(पूर्णांक enable)
अणु
	अगर (enable)
		xen_pci_frontend = &pci_frontend_ops;
	अन्यथा
		xen_pci_frontend = शून्य;
पूर्ण;
#अन्यथा
अटल अंतरभूत व्योम pci_frontend_registrar(पूर्णांक enable) अणु पूर्ण;
#पूर्ण_अगर /* CONFIG_PCI_MSI */

/* Claim resources क्रम the PCI frontend as-is, backend won't allow changes */
अटल पूर्णांक pcअगरront_claim_resource(काष्ठा pci_dev *dev, व्योम *data)
अणु
	काष्ठा pcअगरront_device *pdev = data;
	पूर्णांक i;
	काष्ठा resource *r;

	क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
		r = &dev->resource[i];

		अगर (!r->parent && r->start && r->flags) अणु
			dev_info(&pdev->xdev->dev, "claiming resource %s/%d\n",
				pci_name(dev), i);
			अगर (pci_claim_resource(dev, i)) अणु
				dev_err(&pdev->xdev->dev, "Could not claim resource %s/%d! "
					"Device offline. Try using e820_host=1 in the guest config.\n",
					pci_name(dev), i);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcअगरront_scan_bus(काष्ठा pcअगरront_device *pdev,
				अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus,
				काष्ठा pci_bus *b)
अणु
	काष्ठा pci_dev *d;
	अचिन्हित पूर्णांक devfn;

	/* Scan the bus क्रम functions and add.
	 * We omit handling of PCI bridge attachment because pciback prevents
	 * bridges from being exported.
	 */
	क्रम (devfn = 0; devfn < 0x100; devfn++) अणु
		d = pci_get_slot(b, devfn);
		अगर (d) अणु
			/* Device is alपढ़ोy known. */
			pci_dev_put(d);
			जारी;
		पूर्ण

		d = pci_scan_single_device(b, devfn);
		अगर (d)
			dev_info(&pdev->xdev->dev, "New device on "
				 "%04x:%02x:%02x.%d found.\n", करोमुख्य, bus,
				 PCI_SLOT(devfn), PCI_FUNC(devfn));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcअगरront_scan_root(काष्ठा pcअगरront_device *pdev,
				 अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus)
अणु
	काष्ठा pci_bus *b;
	LIST_HEAD(resources);
	काष्ठा pcअगरront_sd *sd = शून्य;
	काष्ठा pci_bus_entry *bus_entry = शून्य;
	पूर्णांक err = 0;
	अटल काष्ठा resource busn_res = अणु
		.start = 0,
		.end = 255,
		.flags = IORESOURCE_BUS,
	पूर्ण;

#अगर_अघोषित CONFIG_PCI_DOMAINS
	अगर (करोमुख्य != 0) अणु
		dev_err(&pdev->xdev->dev,
			"PCI Root in non-zero PCI Domain! domain=%d\n", करोमुख्य);
		dev_err(&pdev->xdev->dev,
			"Please compile with CONFIG_PCI_DOMAINS\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण
#पूर्ण_अगर

	dev_info(&pdev->xdev->dev, "Creating PCI Frontend Bus %04x:%02x\n",
		 करोमुख्य, bus);

	bus_entry = kzalloc(माप(*bus_entry), GFP_KERNEL);
	sd = kzalloc(माप(*sd), GFP_KERNEL);
	अगर (!bus_entry || !sd) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	pci_add_resource(&resources, &ioport_resource);
	pci_add_resource(&resources, &iomem_resource);
	pci_add_resource(&resources, &busn_res);
	pcअगरront_init_sd(sd, करोमुख्य, bus, pdev);

	pci_lock_rescan_हटाओ();

	b = pci_scan_root_bus(&pdev->xdev->dev, bus,
				  &pcअगरront_bus_ops, sd, &resources);
	अगर (!b) अणु
		dev_err(&pdev->xdev->dev,
			"Error creating PCI Frontend Bus!\n");
		err = -ENOMEM;
		pci_unlock_rescan_हटाओ();
		pci_मुक्त_resource_list(&resources);
		जाओ err_out;
	पूर्ण

	bus_entry->bus = b;

	list_add(&bus_entry->list, &pdev->root_buses);

	/* pci_scan_root_bus skips devices which करो not have a
	* devfn==0. The pcअगरront_scan_bus क्रमागतerates all devfn. */
	err = pcअगरront_scan_bus(pdev, करोमुख्य, bus, b);

	/* Claim resources beक्रमe going "live" with our devices */
	pci_walk_bus(b, pcअगरront_claim_resource, pdev);

	/* Create SysFS and notअगरy udev of the devices. Aka: "going live" */
	pci_bus_add_devices(b);

	pci_unlock_rescan_हटाओ();
	वापस err;

err_out:
	kमुक्त(bus_entry);
	kमुक्त(sd);

	वापस err;
पूर्ण

अटल पूर्णांक pcअगरront_rescan_root(काष्ठा pcअगरront_device *pdev,
				   अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus)
अणु
	पूर्णांक err;
	काष्ठा pci_bus *b;

#अगर_अघोषित CONFIG_PCI_DOMAINS
	अगर (करोमुख्य != 0) अणु
		dev_err(&pdev->xdev->dev,
			"PCI Root in non-zero PCI Domain! domain=%d\n", करोमुख्य);
		dev_err(&pdev->xdev->dev,
			"Please compile with CONFIG_PCI_DOMAINS\n");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	dev_info(&pdev->xdev->dev, "Rescanning PCI Frontend Bus %04x:%02x\n",
		 करोमुख्य, bus);

	b = pci_find_bus(करोमुख्य, bus);
	अगर (!b)
		/* If the bus is unknown, create it. */
		वापस pcअगरront_scan_root(pdev, करोमुख्य, bus);

	err = pcअगरront_scan_bus(pdev, करोमुख्य, bus, b);

	/* Claim resources beक्रमe going "live" with our devices */
	pci_walk_bus(b, pcअगरront_claim_resource, pdev);

	/* Create SysFS and notअगरy udev of the devices. Aka: "going live" */
	pci_bus_add_devices(b);

	वापस err;
पूर्ण

अटल व्योम मुक्त_root_bus_devs(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	जबतक (!list_empty(&bus->devices)) अणु
		dev = container_of(bus->devices.next, काष्ठा pci_dev,
				   bus_list);
		pci_dbg(dev, "removing device\n");
		pci_stop_and_हटाओ_bus_device(dev);
	पूर्ण
पूर्ण

अटल व्योम pcअगरront_मुक्त_roots(काष्ठा pcअगरront_device *pdev)
अणु
	काष्ठा pci_bus_entry *bus_entry, *t;

	dev_dbg(&pdev->xdev->dev, "cleaning up root buses\n");

	pci_lock_rescan_हटाओ();
	list_क्रम_each_entry_safe(bus_entry, t, &pdev->root_buses, list) अणु
		list_del(&bus_entry->list);

		मुक्त_root_bus_devs(bus_entry->bus);

		kमुक्त(bus_entry->bus->sysdata);

		device_unरेजिस्टर(bus_entry->bus->bridge);
		pci_हटाओ_bus(bus_entry->bus);

		kमुक्त(bus_entry);
	पूर्ण
	pci_unlock_rescan_हटाओ();
पूर्ण

अटल pci_ers_result_t pcअगरront_common_process(पूर्णांक cmd,
						काष्ठा pcअगरront_device *pdev,
						pci_channel_state_t state)
अणु
	pci_ers_result_t result;
	काष्ठा pci_driver *pdrv;
	पूर्णांक bus = pdev->sh_info->aer_op.bus;
	पूर्णांक devfn = pdev->sh_info->aer_op.devfn;
	पूर्णांक करोमुख्य = pdev->sh_info->aer_op.करोमुख्य;
	काष्ठा pci_dev *pcidev;
	पूर्णांक flag = 0;

	dev_dbg(&pdev->xdev->dev,
		"pcifront AER process: cmd %x (bus:%x, devfn%x)",
		cmd, bus, devfn);
	result = PCI_ERS_RESULT_NONE;

	pcidev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, bus, devfn);
	अगर (!pcidev || !pcidev->driver) अणु
		dev_err(&pdev->xdev->dev, "device or AER driver is NULL\n");
		pci_dev_put(pcidev);
		वापस result;
	पूर्ण
	pdrv = pcidev->driver;

	अगर (pdrv) अणु
		अगर (pdrv->err_handler && pdrv->err_handler->error_detected) अणु
			pci_dbg(pcidev, "trying to call AER service\n");
			अगर (pcidev) अणु
				flag = 1;
				चयन (cmd) अणु
				हाल XEN_PCI_OP_aer_detected:
					result = pdrv->err_handler->
						 error_detected(pcidev, state);
					अवरोध;
				हाल XEN_PCI_OP_aer_mmio:
					result = pdrv->err_handler->
						 mmio_enabled(pcidev);
					अवरोध;
				हाल XEN_PCI_OP_aer_slotreset:
					result = pdrv->err_handler->
						 slot_reset(pcidev);
					अवरोध;
				हाल XEN_PCI_OP_aer_resume:
					pdrv->err_handler->resume(pcidev);
					अवरोध;
				शेष:
					dev_err(&pdev->xdev->dev,
						"bad request in aer recovery "
						"operation!\n");

				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!flag)
		result = PCI_ERS_RESULT_NONE;

	वापस result;
पूर्ण


अटल व्योम pcअगरront_करो_aer(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा pcअगरront_device *pdev =
		container_of(data, काष्ठा pcअगरront_device, op_work);
	पूर्णांक cmd = pdev->sh_info->aer_op.cmd;
	pci_channel_state_t state =
		(pci_channel_state_t)pdev->sh_info->aer_op.err;

	/*If a pci_conf op is in progress,
		we have to रुको until it is करोne beक्रमe service aer op*/
	dev_dbg(&pdev->xdev->dev,
		"pcifront service aer bus %x devfn %x\n",
		pdev->sh_info->aer_op.bus, pdev->sh_info->aer_op.devfn);

	pdev->sh_info->aer_op.err = pcअगरront_common_process(cmd, pdev, state);

	/* Post the operation to the guest. */
	wmb();
	clear_bit(_XEN_PCIB_active, (अचिन्हित दीर्घ *)&pdev->sh_info->flags);
	notअगरy_remote_via_evtchn(pdev->evtchn);

	/*in हाल of we lost an aer request in four lines समय_winकरोw*/
	smp_mb__beक्रमe_atomic();
	clear_bit(_PDEVB_op_active, &pdev->flags);
	smp_mb__after_atomic();

	schedule_pcअगरront_aer_op(pdev);

पूर्ण

अटल irqवापस_t pcअगरront_handler_aer(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा pcअगरront_device *pdev = dev;
	schedule_pcअगरront_aer_op(pdev);
	वापस IRQ_HANDLED;
पूर्ण
अटल पूर्णांक pcअगरront_connect_and_init_dma(काष्ठा pcअगरront_device *pdev)
अणु
	पूर्णांक err = 0;

	spin_lock(&pcअगरront_dev_lock);

	अगर (!pcअगरront_dev) अणु
		dev_info(&pdev->xdev->dev, "Installing PCI frontend\n");
		pcअगरront_dev = pdev;
	पूर्ण अन्यथा
		err = -EEXIST;

	spin_unlock(&pcअगरront_dev_lock);

	अगर (!err && !is_swiotlb_active()) अणु
		err = pci_xen_swiotlb_init_late();
		अगर (err)
			dev_err(&pdev->xdev->dev, "Could not setup SWIOTLB!\n");
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम pcअगरront_disconnect(काष्ठा pcअगरront_device *pdev)
अणु
	spin_lock(&pcअगरront_dev_lock);

	अगर (pdev == pcअगरront_dev) अणु
		dev_info(&pdev->xdev->dev,
			 "Disconnecting PCI Frontend Buses\n");
		pcअगरront_dev = शून्य;
	पूर्ण

	spin_unlock(&pcअगरront_dev_lock);
पूर्ण
अटल काष्ठा pcअगरront_device *alloc_pdev(काष्ठा xenbus_device *xdev)
अणु
	काष्ठा pcअगरront_device *pdev;

	pdev = kzalloc(माप(काष्ठा pcअगरront_device), GFP_KERNEL);
	अगर (pdev == शून्य)
		जाओ out;

	pdev->sh_info =
	    (काष्ठा xen_pci_sharedinfo *)__get_मुक्त_page(GFP_KERNEL);
	अगर (pdev->sh_info == शून्य) अणु
		kमुक्त(pdev);
		pdev = शून्य;
		जाओ out;
	पूर्ण
	pdev->sh_info->flags = 0;

	/*Flag क्रम रेजिस्टरing PV AER handler*/
	set_bit(_XEN_PCIB_AERHANDLER, (व्योम *)&pdev->sh_info->flags);

	dev_set_drvdata(&xdev->dev, pdev);
	pdev->xdev = xdev;

	INIT_LIST_HEAD(&pdev->root_buses);

	spin_lock_init(&pdev->sh_info_lock);

	pdev->evtchn = INVALID_EVTCHN;
	pdev->gnt_ref = INVALID_GRANT_REF;
	pdev->irq = -1;

	INIT_WORK(&pdev->op_work, pcअगरront_करो_aer);

	dev_dbg(&xdev->dev, "Allocated pdev @ 0x%p pdev->sh_info @ 0x%p\n",
		pdev, pdev->sh_info);
out:
	वापस pdev;
पूर्ण

अटल व्योम मुक्त_pdev(काष्ठा pcअगरront_device *pdev)
अणु
	dev_dbg(&pdev->xdev->dev, "freeing pdev @ 0x%p\n", pdev);

	pcअगरront_मुक्त_roots(pdev);

	cancel_work_sync(&pdev->op_work);

	अगर (pdev->irq >= 0)
		unbind_from_irqhandler(pdev->irq, pdev);

	अगर (pdev->evtchn != INVALID_EVTCHN)
		xenbus_मुक्त_evtchn(pdev->xdev, pdev->evtchn);

	अगर (pdev->gnt_ref != INVALID_GRANT_REF)
		gnttab_end_क्रमeign_access(pdev->gnt_ref, 0 /* r/w page */,
					  (अचिन्हित दीर्घ)pdev->sh_info);
	अन्यथा
		मुक्त_page((अचिन्हित दीर्घ)pdev->sh_info);

	dev_set_drvdata(&pdev->xdev->dev, शून्य);

	kमुक्त(pdev);
पूर्ण

अटल पूर्णांक pcअगरront_publish_info(काष्ठा pcअगरront_device *pdev)
अणु
	पूर्णांक err = 0;
	काष्ठा xenbus_transaction trans;
	grant_ref_t gref;

	err = xenbus_grant_ring(pdev->xdev, pdev->sh_info, 1, &gref);
	अगर (err < 0)
		जाओ out;

	pdev->gnt_ref = gref;

	err = xenbus_alloc_evtchn(pdev->xdev, &pdev->evtchn);
	अगर (err)
		जाओ out;

	err = bind_evtchn_to_irqhandler(pdev->evtchn, pcअगरront_handler_aer,
		0, "pcifront", pdev);

	अगर (err < 0)
		वापस err;

	pdev->irq = err;

करो_publish:
	err = xenbus_transaction_start(&trans);
	अगर (err) अणु
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error writing configuration for backend "
				 "(start transaction)");
		जाओ out;
	पूर्ण

	err = xenbus_म_लिखो(trans, pdev->xdev->nodename,
			    "pci-op-ref", "%u", pdev->gnt_ref);
	अगर (!err)
		err = xenbus_म_लिखो(trans, pdev->xdev->nodename,
				    "event-channel", "%u", pdev->evtchn);
	अगर (!err)
		err = xenbus_म_लिखो(trans, pdev->xdev->nodename,
				    "magic", XEN_PCI_MAGIC);

	अगर (err) अणु
		xenbus_transaction_end(trans, 1);
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error writing configuration for backend");
		जाओ out;
	पूर्ण अन्यथा अणु
		err = xenbus_transaction_end(trans, 0);
		अगर (err == -EAGAIN)
			जाओ करो_publish;
		अन्यथा अगर (err) अणु
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error completing transaction "
					 "for backend");
			जाओ out;
		पूर्ण
	पूर्ण

	xenbus_चयन_state(pdev->xdev, XenbusStateInitialised);

	dev_dbg(&pdev->xdev->dev, "publishing successful!\n");

out:
	वापस err;
पूर्ण

अटल पूर्णांक pcअगरront_try_connect(काष्ठा pcअगरront_device *pdev)
अणु
	पूर्णांक err = -EFAULT;
	पूर्णांक i, num_roots, len;
	अक्षर str[64];
	अचिन्हित पूर्णांक करोमुख्य, bus;


	/* Only connect once */
	अगर (xenbus_पढ़ो_driver_state(pdev->xdev->nodename) !=
	    XenbusStateInitialised)
		जाओ out;

	err = pcअगरront_connect_and_init_dma(pdev);
	अगर (err && err != -EEXIST) अणु
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error setting up PCI Frontend");
		जाओ out;
	पूर्ण

	err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->otherend,
			   "root_num", "%d", &num_roots);
	अगर (err == -ENOENT) अणु
		xenbus_dev_error(pdev->xdev, err,
				 "No PCI Roots found, trying 0000:00");
		err = pcअगरront_scan_root(pdev, 0, 0);
		अगर (err) अणु
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error scanning PCI root 0000:00");
			जाओ out;
		पूर्ण
		num_roots = 0;
	पूर्ण अन्यथा अगर (err != 1) अणु
		अगर (err == 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading number of PCI roots");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_roots; i++) अणु
		len = snम_लिखो(str, माप(str), "root-%d", i);
		अगर (unlikely(len >= (माप(str) - 1))) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->otherend, str,
				   "%x:%x", &करोमुख्य, &bus);
		अगर (err != 2) अणु
			अगर (err >= 0)
				err = -EINVAL;
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error reading PCI root %d", i);
			जाओ out;
		पूर्ण

		err = pcअगरront_scan_root(pdev, करोमुख्य, bus);
		अगर (err) अणु
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error scanning PCI root %04x:%02x",
					 करोमुख्य, bus);
			जाओ out;
		पूर्ण
	पूर्ण

	err = xenbus_चयन_state(pdev->xdev, XenbusStateConnected);

out:
	वापस err;
पूर्ण

अटल पूर्णांक pcअगरront_try_disconnect(काष्ठा pcअगरront_device *pdev)
अणु
	पूर्णांक err = 0;
	क्रमागत xenbus_state prev_state;


	prev_state = xenbus_पढ़ो_driver_state(pdev->xdev->nodename);

	अगर (prev_state >= XenbusStateClosing)
		जाओ out;

	अगर (prev_state == XenbusStateConnected) अणु
		pcअगरront_मुक्त_roots(pdev);
		pcअगरront_disconnect(pdev);
	पूर्ण

	err = xenbus_चयन_state(pdev->xdev, XenbusStateClosed);

out:

	वापस err;
पूर्ण

अटल पूर्णांक pcअगरront_attach_devices(काष्ठा pcअगरront_device *pdev)
अणु
	पूर्णांक err = -EFAULT;
	पूर्णांक i, num_roots, len;
	अचिन्हित पूर्णांक करोमुख्य, bus;
	अक्षर str[64];

	अगर (xenbus_पढ़ो_driver_state(pdev->xdev->nodename) !=
	    XenbusStateReconfiguring)
		जाओ out;

	err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->otherend,
			   "root_num", "%d", &num_roots);
	अगर (err == -ENOENT) अणु
		xenbus_dev_error(pdev->xdev, err,
				 "No PCI Roots found, trying 0000:00");
		err = pcअगरront_rescan_root(pdev, 0, 0);
		अगर (err) अणु
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error scanning PCI root 0000:00");
			जाओ out;
		पूर्ण
		num_roots = 0;
	पूर्ण अन्यथा अगर (err != 1) अणु
		अगर (err == 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading number of PCI roots");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_roots; i++) अणु
		len = snम_लिखो(str, माप(str), "root-%d", i);
		अगर (unlikely(len >= (माप(str) - 1))) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->otherend, str,
				   "%x:%x", &करोमुख्य, &bus);
		अगर (err != 2) अणु
			अगर (err >= 0)
				err = -EINVAL;
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error reading PCI root %d", i);
			जाओ out;
		पूर्ण

		err = pcअगरront_rescan_root(pdev, करोमुख्य, bus);
		अगर (err) अणु
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error scanning PCI root %04x:%02x",
					 करोमुख्य, bus);
			जाओ out;
		पूर्ण
	पूर्ण

	xenbus_चयन_state(pdev->xdev, XenbusStateConnected);

out:
	वापस err;
पूर्ण

अटल पूर्णांक pcअगरront_detach_devices(काष्ठा pcअगरront_device *pdev)
अणु
	पूर्णांक err = 0;
	पूर्णांक i, num_devs;
	अचिन्हित पूर्णांक करोमुख्य, bus, slot, func;
	काष्ठा pci_dev *pci_dev;
	अक्षर str[64];

	अगर (xenbus_पढ़ो_driver_state(pdev->xdev->nodename) !=
	    XenbusStateConnected)
		जाओ out;

	err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->otherend, "num_devs", "%d",
			   &num_devs);
	अगर (err != 1) अणु
		अगर (err >= 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading number of PCI devices");
		जाओ out;
	पूर्ण

	/* Find devices being detached and हटाओ them. */
	क्रम (i = 0; i < num_devs; i++) अणु
		पूर्णांक l, state;
		l = snम_लिखो(str, माप(str), "state-%d", i);
		अगर (unlikely(l >= (माप(str) - 1))) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		state = xenbus_पढ़ो_अचिन्हित(pdev->xdev->otherend, str,
					     XenbusStateUnknown);

		अगर (state != XenbusStateClosing)
			जारी;

		/* Remove device. */
		l = snम_लिखो(str, माप(str), "vdev-%d", i);
		अगर (unlikely(l >= (माप(str) - 1))) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->otherend, str,
				   "%x:%x:%x.%x", &करोमुख्य, &bus, &slot, &func);
		अगर (err != 4) अणु
			अगर (err >= 0)
				err = -EINVAL;
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error reading PCI device %d", i);
			जाओ out;
		पूर्ण

		pci_dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, bus,
				PCI_DEVFN(slot, func));
		अगर (!pci_dev) अणु
			dev_dbg(&pdev->xdev->dev,
				"Cannot get PCI device %04x:%02x:%02x.%d\n",
				करोमुख्य, bus, slot, func);
			जारी;
		पूर्ण
		pci_lock_rescan_हटाओ();
		pci_stop_and_हटाओ_bus_device(pci_dev);
		pci_dev_put(pci_dev);
		pci_unlock_rescan_हटाओ();

		dev_dbg(&pdev->xdev->dev,
			"PCI device %04x:%02x:%02x.%d removed.\n",
			करोमुख्य, bus, slot, func);
	पूर्ण

	err = xenbus_चयन_state(pdev->xdev, XenbusStateReconfiguring);

out:
	वापस err;
पूर्ण

अटल व्योम __ref pcअगरront_backend_changed(काष्ठा xenbus_device *xdev,
						  क्रमागत xenbus_state be_state)
अणु
	काष्ठा pcअगरront_device *pdev = dev_get_drvdata(&xdev->dev);

	चयन (be_state) अणु
	हाल XenbusStateUnknown:
	हाल XenbusStateInitialising:
	हाल XenbusStateInitWait:
	हाल XenbusStateInitialised:
		अवरोध;

	हाल XenbusStateConnected:
		pcअगरront_try_connect(pdev);
		अवरोध;

	हाल XenbusStateClosed:
		अगर (xdev->state == XenbusStateClosed)
			अवरोध;
		fallthrough;	/* Missed the backend's CLOSING state */
	हाल XenbusStateClosing:
		dev_warn(&xdev->dev, "backend going away!\n");
		pcअगरront_try_disconnect(pdev);
		अवरोध;

	हाल XenbusStateReconfiguring:
		pcअगरront_detach_devices(pdev);
		अवरोध;

	हाल XenbusStateReconfigured:
		pcअगरront_attach_devices(pdev);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pcअगरront_xenbus_probe(काष्ठा xenbus_device *xdev,
				 स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक err = 0;
	काष्ठा pcअगरront_device *pdev = alloc_pdev(xdev);

	अगर (pdev == शून्य) अणु
		err = -ENOMEM;
		xenbus_dev_fatal(xdev, err,
				 "Error allocating pcifront_device struct");
		जाओ out;
	पूर्ण

	err = pcअगरront_publish_info(pdev);
	अगर (err)
		मुक्त_pdev(pdev);

out:
	वापस err;
पूर्ण

अटल पूर्णांक pcअगरront_xenbus_हटाओ(काष्ठा xenbus_device *xdev)
अणु
	काष्ठा pcअगरront_device *pdev = dev_get_drvdata(&xdev->dev);
	अगर (pdev)
		मुक्त_pdev(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id xenpci_ids[] = अणु
	अणु"pci"पूर्ण,
	अणु""पूर्ण,
पूर्ण;

अटल काष्ठा xenbus_driver xenpci_driver = अणु
	.name			= "pcifront",
	.ids			= xenpci_ids,
	.probe			= pcअगरront_xenbus_probe,
	.हटाओ			= pcअगरront_xenbus_हटाओ,
	.otherend_changed	= pcअगरront_backend_changed,
पूर्ण;

अटल पूर्णांक __init pcअगरront_init(व्योम)
अणु
	अगर (!xen_pv_करोमुख्य() || xen_initial_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_has_pv_devices())
		वापस -ENODEV;

	pci_frontend_registrar(1 /* enable */);

	वापस xenbus_रेजिस्टर_frontend(&xenpci_driver);
पूर्ण

अटल व्योम __निकास pcअगरront_cleanup(व्योम)
अणु
	xenbus_unरेजिस्टर_driver(&xenpci_driver);
	pci_frontend_registrar(0 /* disable */);
पूर्ण
module_init(pcअगरront_init);
module_निकास(pcअगरront_cleanup);

MODULE_DESCRIPTION("Xen PCI passthrough frontend.");
MODULE_LICENSE("GPL");
MODULE_ALIAS("xen:pci");
