<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) Copyright 2002-2004, 2007 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * (C) Copyright 2007 Novell Inc.
 */

#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/suspend.h>
#समावेश <linux/kexec.h>
#समावेश <linux/of_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dma-map-ops.h>
#समावेश "pci.h"
#समावेश "pcie/portdrv.h"

काष्ठा pci_dynid अणु
	काष्ठा list_head node;
	काष्ठा pci_device_id id;
पूर्ण;

/**
 * pci_add_dynid - add a new PCI device ID to this driver and re-probe devices
 * @drv: target pci driver
 * @venकरोr: PCI venकरोr ID
 * @device: PCI device ID
 * @subvenकरोr: PCI subvenकरोr ID
 * @subdevice: PCI subdevice ID
 * @class: PCI class
 * @class_mask: PCI class mask
 * @driver_data: निजी driver data
 *
 * Adds a new dynamic pci device ID to this driver and causes the
 * driver to probe क्रम all devices again.  @drv must have been
 * रेजिस्टरed prior to calling this function.
 *
 * CONTEXT:
 * Does GFP_KERNEL allocation.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक pci_add_dynid(काष्ठा pci_driver *drv,
		  अचिन्हित पूर्णांक venकरोr, अचिन्हित पूर्णांक device,
		  अचिन्हित पूर्णांक subvenकरोr, अचिन्हित पूर्णांक subdevice,
		  अचिन्हित पूर्णांक class, अचिन्हित पूर्णांक class_mask,
		  अचिन्हित दीर्घ driver_data)
अणु
	काष्ठा pci_dynid *dynid;

	dynid = kzalloc(माप(*dynid), GFP_KERNEL);
	अगर (!dynid)
		वापस -ENOMEM;

	dynid->id.venकरोr = venकरोr;
	dynid->id.device = device;
	dynid->id.subvenकरोr = subvenकरोr;
	dynid->id.subdevice = subdevice;
	dynid->id.class = class;
	dynid->id.class_mask = class_mask;
	dynid->id.driver_data = driver_data;

	spin_lock(&drv->dynids.lock);
	list_add_tail(&dynid->node, &drv->dynids.list);
	spin_unlock(&drv->dynids.lock);

	वापस driver_attach(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(pci_add_dynid);

अटल व्योम pci_मुक्त_dynids(काष्ठा pci_driver *drv)
अणु
	काष्ठा pci_dynid *dynid, *n;

	spin_lock(&drv->dynids.lock);
	list_क्रम_each_entry_safe(dynid, n, &drv->dynids.list, node) अणु
		list_del(&dynid->node);
		kमुक्त(dynid);
	पूर्ण
	spin_unlock(&drv->dynids.lock);
पूर्ण

/**
 * pci_match_id - See अगर a PCI device matches a given pci_id table
 * @ids: array of PCI device ID काष्ठाures to search in
 * @dev: the PCI device काष्ठाure to match against.
 *
 * Used by a driver to check whether a PCI device is in its list of
 * supported devices.  Returns the matching pci_device_id काष्ठाure or
 * %शून्य अगर there is no match.
 *
 * Deprecated; करोn't use this as it will not catch any dynamic IDs
 * that a driver might want to check क्रम.
 */
स्थिर काष्ठा pci_device_id *pci_match_id(स्थिर काष्ठा pci_device_id *ids,
					 काष्ठा pci_dev *dev)
अणु
	अगर (ids) अणु
		जबतक (ids->venकरोr || ids->subvenकरोr || ids->class_mask) अणु
			अगर (pci_match_one_device(ids, dev))
				वापस ids;
			ids++;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(pci_match_id);

अटल स्थिर काष्ठा pci_device_id pci_device_id_any = अणु
	.venकरोr = PCI_ANY_ID,
	.device = PCI_ANY_ID,
	.subvenकरोr = PCI_ANY_ID,
	.subdevice = PCI_ANY_ID,
पूर्ण;

/**
 * pci_match_device - See अगर a device matches a driver's list of IDs
 * @drv: the PCI driver to match against
 * @dev: the PCI device काष्ठाure to match against
 *
 * Used by a driver to check whether a PCI device is in its list of
 * supported devices or in the dynids list, which may have been augmented
 * via the sysfs "new_id" file.  Returns the matching pci_device_id
 * काष्ठाure or %शून्य अगर there is no match.
 */
अटल स्थिर काष्ठा pci_device_id *pci_match_device(काष्ठा pci_driver *drv,
						    काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dynid *dynid;
	स्थिर काष्ठा pci_device_id *found_id = शून्य;

	/* When driver_override is set, only bind to the matching driver */
	अगर (dev->driver_override && म_भेद(dev->driver_override, drv->name))
		वापस शून्य;

	/* Look at the dynamic ids first, beक्रमe the अटल ones */
	spin_lock(&drv->dynids.lock);
	list_क्रम_each_entry(dynid, &drv->dynids.list, node) अणु
		अगर (pci_match_one_device(&dynid->id, dev)) अणु
			found_id = &dynid->id;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&drv->dynids.lock);

	अगर (!found_id)
		found_id = pci_match_id(drv->id_table, dev);

	/* driver_override will always match, send a dummy id */
	अगर (!found_id && dev->driver_override)
		found_id = &pci_device_id_any;

	वापस found_id;
पूर्ण

/**
 * new_id_store - sysfs frontend to pci_add_dynid()
 * @driver: target device driver
 * @buf: buffer क्रम scanning device ID data
 * @count: input size
 *
 * Allow PCI IDs to be added to an existing driver via sysfs.
 */
अटल sमाप_प्रकार new_id_store(काष्ठा device_driver *driver, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा pci_driver *pdrv = to_pci_driver(driver);
	स्थिर काष्ठा pci_device_id *ids = pdrv->id_table;
	u32 venकरोr, device, subvenकरोr = PCI_ANY_ID,
		subdevice = PCI_ANY_ID, class = 0, class_mask = 0;
	अचिन्हित दीर्घ driver_data = 0;
	पूर्णांक fields = 0;
	पूर्णांक retval = 0;

	fields = माला_पूछो(buf, "%x %x %x %x %x %x %lx",
			&venकरोr, &device, &subvenकरोr, &subdevice,
			&class, &class_mask, &driver_data);
	अगर (fields < 2)
		वापस -EINVAL;

	अगर (fields != 7) अणु
		काष्ठा pci_dev *pdev = kzalloc(माप(*pdev), GFP_KERNEL);
		अगर (!pdev)
			वापस -ENOMEM;

		pdev->venकरोr = venकरोr;
		pdev->device = device;
		pdev->subप्रणाली_venकरोr = subvenकरोr;
		pdev->subप्रणाली_device = subdevice;
		pdev->class = class;

		अगर (pci_match_device(pdrv, pdev))
			retval = -EEXIST;

		kमुक्त(pdev);

		अगर (retval)
			वापस retval;
	पूर्ण

	/* Only accept driver_data values that match an existing id_table
	   entry */
	अगर (ids) अणु
		retval = -EINVAL;
		जबतक (ids->venकरोr || ids->subvenकरोr || ids->class_mask) अणु
			अगर (driver_data == ids->driver_data) अणु
				retval = 0;
				अवरोध;
			पूर्ण
			ids++;
		पूर्ण
		अगर (retval)	/* No match */
			वापस retval;
	पूर्ण

	retval = pci_add_dynid(pdrv, venकरोr, device, subvenकरोr, subdevice,
			       class, class_mask, driver_data);
	अगर (retval)
		वापस retval;
	वापस count;
पूर्ण
अटल DRIVER_ATTR_WO(new_id);

/**
 * हटाओ_id_store - हटाओ a PCI device ID from this driver
 * @driver: target device driver
 * @buf: buffer क्रम scanning device ID data
 * @count: input size
 *
 * Removes a dynamic pci device ID to this driver.
 */
अटल sमाप_प्रकार हटाओ_id_store(काष्ठा device_driver *driver, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा pci_dynid *dynid, *n;
	काष्ठा pci_driver *pdrv = to_pci_driver(driver);
	u32 venकरोr, device, subvenकरोr = PCI_ANY_ID,
		subdevice = PCI_ANY_ID, class = 0, class_mask = 0;
	पूर्णांक fields = 0;
	माप_प्रकार retval = -ENODEV;

	fields = माला_पूछो(buf, "%x %x %x %x %x %x",
			&venकरोr, &device, &subvenकरोr, &subdevice,
			&class, &class_mask);
	अगर (fields < 2)
		वापस -EINVAL;

	spin_lock(&pdrv->dynids.lock);
	list_क्रम_each_entry_safe(dynid, n, &pdrv->dynids.list, node) अणु
		काष्ठा pci_device_id *id = &dynid->id;
		अगर ((id->venकरोr == venकरोr) &&
		    (id->device == device) &&
		    (subvenकरोr == PCI_ANY_ID || id->subvenकरोr == subvenकरोr) &&
		    (subdevice == PCI_ANY_ID || id->subdevice == subdevice) &&
		    !((id->class ^ class) & class_mask)) अणु
			list_del(&dynid->node);
			kमुक्त(dynid);
			retval = count;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&pdrv->dynids.lock);

	वापस retval;
पूर्ण
अटल DRIVER_ATTR_WO(हटाओ_id);

अटल काष्ठा attribute *pci_drv_attrs[] = अणु
	&driver_attr_new_id.attr,
	&driver_attr_हटाओ_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(pci_drv);

काष्ठा drv_dev_and_id अणु
	काष्ठा pci_driver *drv;
	काष्ठा pci_dev *dev;
	स्थिर काष्ठा pci_device_id *id;
पूर्ण;

अटल दीर्घ local_pci_probe(व्योम *_ddi)
अणु
	काष्ठा drv_dev_and_id *ddi = _ddi;
	काष्ठा pci_dev *pci_dev = ddi->dev;
	काष्ठा pci_driver *pci_drv = ddi->drv;
	काष्ठा device *dev = &pci_dev->dev;
	पूर्णांक rc;

	/*
	 * Unbound PCI devices are always put in D0, regardless of
	 * runसमय PM status.  During probe, the device is set to
	 * active and the usage count is incremented.  If the driver
	 * supports runसमय PM, it should call pm_runसमय_put_noidle(),
	 * or any other runसमय PM helper function decrementing the usage
	 * count, in its probe routine and pm_runसमय_get_noresume() in
	 * its हटाओ routine.
	 */
	pm_runसमय_get_sync(dev);
	pci_dev->driver = pci_drv;
	rc = pci_drv->probe(pci_dev, ddi->id);
	अगर (!rc)
		वापस rc;
	अगर (rc < 0) अणु
		pci_dev->driver = शून्य;
		pm_runसमय_put_sync(dev);
		वापस rc;
	पूर्ण
	/*
	 * Probe function should वापस < 0 क्रम failure, 0 क्रम success
	 * Treat values > 0 as success, but warn.
	 */
	pci_warn(pci_dev, "Driver probe function unexpectedly returned %d\n",
		 rc);
	वापस 0;
पूर्ण

अटल bool pci_physfn_is_probed(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	वापस dev->is_virtfn && dev->physfn->is_probed;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक pci_call_probe(काष्ठा pci_driver *drv, काष्ठा pci_dev *dev,
			  स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक error, node, cpu;
	पूर्णांक hk_flags = HK_FLAG_DOMAIN | HK_FLAG_WQ;
	काष्ठा drv_dev_and_id ddi = अणु drv, dev, id पूर्ण;

	/*
	 * Execute driver initialization on node where the device is
	 * attached.  This way the driver likely allocates its local memory
	 * on the right node.
	 */
	node = dev_to_node(&dev->dev);
	dev->is_probed = 1;

	cpu_hotplug_disable();

	/*
	 * Prevent nesting work_on_cpu() क्रम the हाल where a Virtual Function
	 * device is probed from work_on_cpu() of the Physical device.
	 */
	अगर (node < 0 || node >= MAX_NUMNODES || !node_online(node) ||
	    pci_physfn_is_probed(dev))
		cpu = nr_cpu_ids;
	अन्यथा
		cpu = cpumask_any_and(cpumask_of_node(node),
				      housekeeping_cpumask(hk_flags));

	अगर (cpu < nr_cpu_ids)
		error = work_on_cpu(cpu, local_pci_probe, &ddi);
	अन्यथा
		error = local_pci_probe(&ddi);

	dev->is_probed = 0;
	cpu_hotplug_enable();
	वापस error;
पूर्ण

/**
 * __pci_device_probe - check अगर a driver wants to claim a specअगरic PCI device
 * @drv: driver to call to check अगर it wants the PCI device
 * @pci_dev: PCI device being probed
 *
 * वापसs 0 on success, अन्यथा error.
 * side-effect: pci_dev->driver is set to drv when drv claims pci_dev.
 */
अटल पूर्णांक __pci_device_probe(काष्ठा pci_driver *drv, काष्ठा pci_dev *pci_dev)
अणु
	स्थिर काष्ठा pci_device_id *id;
	पूर्णांक error = 0;

	अगर (!pci_dev->driver && drv->probe) अणु
		error = -ENODEV;

		id = pci_match_device(drv, pci_dev);
		अगर (id)
			error = pci_call_probe(drv, pci_dev, id);
	पूर्ण
	वापस error;
पूर्ण

पूर्णांक __weak pcibios_alloc_irq(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

व्योम __weak pcibios_मुक्त_irq(काष्ठा pci_dev *dev)
अणु
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
अटल अंतरभूत bool pci_device_can_probe(काष्ठा pci_dev *pdev)
अणु
	वापस (!pdev->is_virtfn || pdev->physfn->sriov->drivers_स्वतःprobe ||
		pdev->driver_override);
पूर्ण
#अन्यथा
अटल अंतरभूत bool pci_device_can_probe(काष्ठा pci_dev *pdev)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pci_device_probe(काष्ठा device *dev)
अणु
	पूर्णांक error;
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा pci_driver *drv = to_pci_driver(dev->driver);

	अगर (!pci_device_can_probe(pci_dev))
		वापस -ENODEV;

	pci_assign_irq(pci_dev);

	error = pcibios_alloc_irq(pci_dev);
	अगर (error < 0)
		वापस error;

	pci_dev_get(pci_dev);
	error = __pci_device_probe(drv, pci_dev);
	अगर (error) अणु
		pcibios_मुक्त_irq(pci_dev);
		pci_dev_put(pci_dev);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक pci_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा pci_driver *drv = pci_dev->driver;

	अगर (drv) अणु
		अगर (drv->हटाओ) अणु
			pm_runसमय_get_sync(dev);
			drv->हटाओ(pci_dev);
			pm_runसमय_put_noidle(dev);
		पूर्ण
		pcibios_मुक्त_irq(pci_dev);
		pci_dev->driver = शून्य;
		pci_iov_हटाओ(pci_dev);
	पूर्ण

	/* Unकरो the runसमय PM settings in local_pci_probe() */
	pm_runसमय_put_sync(dev);

	/*
	 * If the device is still on, set the घातer state as "unknown",
	 * since it might change by the next समय we load the driver.
	 */
	अगर (pci_dev->current_state == PCI_D0)
		pci_dev->current_state = PCI_UNKNOWN;

	/*
	 * We would love to complain here अगर pci_dev->is_enabled is set, that
	 * the driver should have called pci_disable_device(), but the
	 * unक्रमtunate fact is there are too many odd BIOS and bridge setups
	 * that करोn't like drivers करोing that all of the समय.
	 * Oh well, we can dream of sane hardware when we sleep, no matter how
	 * horrible the crap we have to deal with is when we are awake...
	 */

	pci_dev_put(pci_dev);
	वापस 0;
पूर्ण

अटल व्योम pci_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा pci_driver *drv = pci_dev->driver;

	pm_runसमय_resume(dev);

	अगर (drv && drv->shutकरोwn)
		drv->shutकरोwn(pci_dev);

	/*
	 * If this is a kexec reboot, turn off Bus Master bit on the
	 * device to tell it to not जारी to करो DMA. Don't touch
	 * devices in D3cold or unknown states.
	 * If it is not a kexec reboot, firmware will hit the PCI
	 * devices with big hammer and stop their DMA any way.
	 */
	अगर (kexec_in_progress && (pci_dev->current_state <= PCI_D3hot))
		pci_clear_master(pci_dev);
पूर्ण

#अगर_घोषित CONFIG_PM

/* Auxiliary functions used क्रम प्रणाली resume and run-समय resume. */

/**
 * pci_restore_standard_config - restore standard config रेजिस्टरs of PCI device
 * @pci_dev: PCI device to handle
 */
अटल पूर्णांक pci_restore_standard_config(काष्ठा pci_dev *pci_dev)
अणु
	pci_update_current_state(pci_dev, PCI_UNKNOWN);

	अगर (pci_dev->current_state != PCI_D0) अणु
		पूर्णांक error = pci_set_घातer_state(pci_dev, PCI_D0);
		अगर (error)
			वापस error;
	पूर्ण

	pci_restore_state(pci_dev);
	pci_pme_restore(pci_dev);
	वापस 0;
पूर्ण

अटल व्योम pci_pm_शेष_resume(काष्ठा pci_dev *pci_dev)
अणु
	pci_fixup_device(pci_fixup_resume, pci_dev);
	pci_enable_wake(pci_dev, PCI_D0, false);
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP

अटल व्योम pci_pm_शेष_resume_early(काष्ठा pci_dev *pci_dev)
अणु
	pci_घातer_up(pci_dev);
	pci_update_current_state(pci_dev, PCI_D0);
	pci_restore_state(pci_dev);
	pci_pme_restore(pci_dev);
पूर्ण

/*
 * Default "suspend" method क्रम devices that have no driver provided suspend,
 * or not even a driver at all (second part).
 */
अटल व्योम pci_pm_set_unknown_state(काष्ठा pci_dev *pci_dev)
अणु
	/*
	 * mark its घातer state as "unknown", since we करोn't know अगर
	 * e.g. the BIOS will change its device state when we suspend.
	 */
	अगर (pci_dev->current_state == PCI_D0)
		pci_dev->current_state = PCI_UNKNOWN;
पूर्ण

/*
 * Default "resume" method क्रम devices that have no driver provided resume,
 * or not even a driver at all (second part).
 */
अटल पूर्णांक pci_pm_reenable_device(काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक retval;

	/* अगर the device was enabled beक्रमe suspend, reenable */
	retval = pci_reenable_device(pci_dev);
	/*
	 * अगर the device was busmaster beक्रमe the suspend, make it busmaster
	 * again
	 */
	अगर (pci_dev->is_busmaster)
		pci_set_master(pci_dev);

	वापस retval;
पूर्ण

अटल पूर्णांक pci_legacy_suspend(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा pci_driver *drv = pci_dev->driver;

	अगर (drv && drv->suspend) अणु
		pci_घातer_t prev = pci_dev->current_state;
		पूर्णांक error;

		error = drv->suspend(pci_dev, state);
		suspend_report_result(drv->suspend, error);
		अगर (error)
			वापस error;

		अगर (!pci_dev->state_saved && pci_dev->current_state != PCI_D0
		    && pci_dev->current_state != PCI_UNKNOWN) अणु
			pci_WARN_ONCE(pci_dev, pci_dev->current_state != prev,
				      "PCI PM: Device state not saved by %pS\n",
				      drv->suspend);
		पूर्ण
	पूर्ण

	pci_fixup_device(pci_fixup_suspend, pci_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_legacy_suspend_late(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);

	अगर (!pci_dev->state_saved)
		pci_save_state(pci_dev);

	pci_pm_set_unknown_state(pci_dev);

	pci_fixup_device(pci_fixup_suspend_late, pci_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_legacy_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा pci_driver *drv = pci_dev->driver;

	pci_fixup_device(pci_fixup_resume, pci_dev);

	वापस drv && drv->resume ?
			drv->resume(pci_dev) : pci_pm_reenable_device(pci_dev);
पूर्ण

/* Auxiliary functions used by the new घातer management framework */

अटल व्योम pci_pm_शेष_suspend(काष्ठा pci_dev *pci_dev)
अणु
	/* Disable non-bridge devices without PM support */
	अगर (!pci_has_subordinate(pci_dev))
		pci_disable_enabled_device(pci_dev);
पूर्ण

अटल bool pci_has_legacy_pm_support(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा pci_driver *drv = pci_dev->driver;
	bool ret = drv && (drv->suspend || drv->resume);

	/*
	 * Legacy PM support is used by शेष, so warn अगर the new framework is
	 * supported as well.  Drivers are supposed to support either the
	 * क्रमmer, or the latter, but not both at the same समय.
	 */
	pci_WARN(pci_dev, ret && drv->driver.pm, "device %04x:%04x\n",
		 pci_dev->venकरोr, pci_dev->device);

	वापस ret;
पूर्ण

/* New घातer management framework */

अटल पूर्णांक pci_pm_prepare(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	अगर (pm && pm->prepare) अणु
		पूर्णांक error = pm->prepare(dev);
		अगर (error < 0)
			वापस error;

		अगर (!error && dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_PREPARE))
			वापस 0;
	पूर्ण
	अगर (pci_dev_need_resume(pci_dev))
		वापस 0;

	/*
	 * The PME setting needs to be adjusted here in हाल the direct-complete
	 * optimization is used with respect to this device.
	 */
	pci_dev_adjust_pme(pci_dev);
	वापस 1;
पूर्ण

अटल व्योम pci_pm_complete(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);

	pci_dev_complete_resume(pci_dev);
	pm_generic_complete(dev);

	/* Resume device अगर platक्रमm firmware has put it in reset-घातer-on */
	अगर (pm_runसमय_suspended(dev) && pm_resume_via_firmware()) अणु
		pci_घातer_t pre_sleep_state = pci_dev->current_state;

		pci_refresh_घातer_state(pci_dev);
		/*
		 * On platक्रमms with ACPI this check may also trigger क्रम
		 * devices sharing घातer resources अगर one of those घातer
		 * resources has been activated as a result of a change of the
		 * घातer state of another device sharing it.  However, in that
		 * हाल it is also better to resume the device, in general.
		 */
		अगर (pci_dev->current_state < pre_sleep_state)
			pm_request_resume(dev);
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_PM_SLEEP */

#घोषणा pci_pm_prepare	शून्य
#घोषणा pci_pm_complete	शून्य

#पूर्ण_अगर /* !CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_SUSPEND
अटल व्योम pcie_pme_root_status_cleanup(काष्ठा pci_dev *pci_dev)
अणु
	/*
	 * Some BIOSes क्रमget to clear Root PME Status bits after प्रणाली
	 * wakeup, which अवरोधs ACPI-based runसमय wakeup on PCI Express.
	 * Clear those bits now just in हाल (shouldn't hurt).
	 */
	अगर (pci_is_pcie(pci_dev) &&
	    (pci_pcie_type(pci_dev) == PCI_EXP_TYPE_ROOT_PORT ||
	     pci_pcie_type(pci_dev) == PCI_EXP_TYPE_RC_EC))
		pcie_clear_root_pme_status(pci_dev);
पूर्ण

अटल पूर्णांक pci_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	pci_dev->skip_bus_pm = false;

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस pci_legacy_suspend(dev, PMSG_SUSPEND);

	अगर (!pm) अणु
		pci_pm_शेष_suspend(pci_dev);
		वापस 0;
	पूर्ण

	/*
	 * PCI devices suspended at run समय may need to be resumed at this
	 * poपूर्णांक, because in general it may be necessary to reconfigure them क्रम
	 * प्रणाली suspend.  Namely, अगर the device is expected to wake up the
	 * प्रणाली from the sleep state, it may have to be reconfigured क्रम this
	 * purpose, or अगर the device is not expected to wake up the प्रणाली from
	 * the sleep state, it should be prevented from संकेतing wakeup events
	 * going क्रमward.
	 *
	 * Also अगर the driver of the device करोes not indicate that its प्रणाली
	 * suspend callbacks can cope with runसमय-suspended devices, it is
	 * better to resume the device from runसमय suspend here.
	 */
	अगर (!dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_SUSPEND) ||
	    pci_dev_need_resume(pci_dev)) अणु
		pm_runसमय_resume(dev);
		pci_dev->state_saved = false;
	पूर्ण अन्यथा अणु
		pci_dev_adjust_pme(pci_dev);
	पूर्ण

	अगर (pm->suspend) अणु
		pci_घातer_t prev = pci_dev->current_state;
		पूर्णांक error;

		error = pm->suspend(dev);
		suspend_report_result(pm->suspend, error);
		अगर (error)
			वापस error;

		अगर (!pci_dev->state_saved && pci_dev->current_state != PCI_D0
		    && pci_dev->current_state != PCI_UNKNOWN) अणु
			pci_WARN_ONCE(pci_dev, pci_dev->current_state != prev,
				      "PCI PM: State of device not saved by %pS\n",
				      pm->suspend);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_suspend_late(काष्ठा device *dev)
अणु
	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	pci_fixup_device(pci_fixup_suspend, to_pci_dev(dev));

	वापस pm_generic_suspend_late(dev);
पूर्ण

अटल पूर्णांक pci_pm_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस pci_legacy_suspend_late(dev, PMSG_SUSPEND);

	अगर (!pm) अणु
		pci_save_state(pci_dev);
		जाओ Fixup;
	पूर्ण

	अगर (pm->suspend_noirq) अणु
		pci_घातer_t prev = pci_dev->current_state;
		पूर्णांक error;

		error = pm->suspend_noirq(dev);
		suspend_report_result(pm->suspend_noirq, error);
		अगर (error)
			वापस error;

		अगर (!pci_dev->state_saved && pci_dev->current_state != PCI_D0
		    && pci_dev->current_state != PCI_UNKNOWN) अणु
			pci_WARN_ONCE(pci_dev, pci_dev->current_state != prev,
				      "PCI PM: State of device not saved by %pS\n",
				      pm->suspend_noirq);
			जाओ Fixup;
		पूर्ण
	पूर्ण

	अगर (pci_dev->skip_bus_pm) अणु
		/*
		 * Either the device is a bridge with a child in D0 below it, or
		 * the function is running क्रम the second समय in a row without
		 * going through full resume, which is possible only during
		 * suspend-to-idle in a spurious wakeup हाल.  The device should
		 * be in D0 at this poपूर्णांक, but अगर it is a bridge, it may be
		 * necessary to save its state.
		 */
		अगर (!pci_dev->state_saved)
			pci_save_state(pci_dev);
	पूर्ण अन्यथा अगर (!pci_dev->state_saved) अणु
		pci_save_state(pci_dev);
		अगर (pci_घातer_manageable(pci_dev))
			pci_prepare_to_sleep(pci_dev);
	पूर्ण

	pci_dbg(pci_dev, "PCI PM: Suspend power state: %s\n",
		pci_घातer_name(pci_dev->current_state));

	अगर (pci_dev->current_state == PCI_D0) अणु
		pci_dev->skip_bus_pm = true;
		/*
		 * Per PCI PM r1.2, table 6-1, a bridge must be in D0 अगर any
		 * करोwnstream device is in D0, so aव्योम changing the घातer state
		 * of the parent bridge by setting the skip_bus_pm flag क्रम it.
		 */
		अगर (pci_dev->bus->self)
			pci_dev->bus->self->skip_bus_pm = true;
	पूर्ण

	अगर (pci_dev->skip_bus_pm && pm_suspend_no_platक्रमm()) अणु
		pci_dbg(pci_dev, "PCI PM: Skipped\n");
		जाओ Fixup;
	पूर्ण

	pci_pm_set_unknown_state(pci_dev);

	/*
	 * Some BIOSes from ASUS have a bug: If a USB EHCI host controller's
	 * PCI COMMAND रेजिस्टर isn't 0, the BIOS assumes that the controller
	 * hasn't been quiesced and tries to turn it off.  If the controller
	 * is alपढ़ोy in D3, this can hang or cause memory corruption.
	 *
	 * Since the value of the COMMAND रेजिस्टर करोesn't matter once the
	 * device has been suspended, we can safely set it to 0 here.
	 */
	अगर (pci_dev->class == PCI_CLASS_SERIAL_USB_EHCI)
		pci_ग_लिखो_config_word(pci_dev, PCI_COMMAND, 0);

Fixup:
	pci_fixup_device(pci_fixup_suspend_late, pci_dev);

	/*
	 * If the target प्रणाली sleep state is suspend-to-idle, it is sufficient
	 * to check whether or not the device's wakeup settings are good क्रम
	 * runसमय PM.  Otherwise, the pm_resume_via_firmware() check will cause
	 * pci_pm_complete() to take care of fixing up the device's state
	 * anyway, अगर need be.
	 */
	अगर (device_can_wakeup(dev) && !device_may_wakeup(dev))
		dev->घातer.may_skip_resume = false;

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	pci_घातer_t prev_state = pci_dev->current_state;
	bool skip_bus_pm = pci_dev->skip_bus_pm;

	अगर (dev_pm_skip_resume(dev))
		वापस 0;

	/*
	 * In the suspend-to-idle हाल, devices left in D0 during suspend will
	 * stay in D0, so it is not necessary to restore or update their
	 * configuration here and attempting to put them पूर्णांकo D0 again is
	 * poपूर्णांकless, so aव्योम करोing that.
	 */
	अगर (!(skip_bus_pm && pm_suspend_no_platक्रमm()))
		pci_pm_शेष_resume_early(pci_dev);

	pci_fixup_device(pci_fixup_resume_early, pci_dev);
	pcie_pme_root_status_cleanup(pci_dev);

	अगर (!skip_bus_pm && prev_state == PCI_D3cold)
		pci_bridge_रुको_क्रम_secondary_bus(pci_dev);

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस 0;

	अगर (pm && pm->resume_noirq)
		वापस pm->resume_noirq(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_resume_early(काष्ठा device *dev)
अणु
	अगर (dev_pm_skip_resume(dev))
		वापस 0;

	वापस pm_generic_resume_early(dev);
पूर्ण

अटल पूर्णांक pci_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	/*
	 * This is necessary क्रम the suspend error path in which resume is
	 * called without restoring the standard config रेजिस्टरs of the device.
	 */
	अगर (pci_dev->state_saved)
		pci_restore_standard_config(pci_dev);

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस pci_legacy_resume(dev);

	pci_pm_शेष_resume(pci_dev);

	अगर (pm) अणु
		अगर (pm->resume)
			वापस pm->resume(dev);
	पूर्ण अन्यथा अणु
		pci_pm_reenable_device(pci_dev);
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_SUSPEND */

#घोषणा pci_pm_suspend		शून्य
#घोषणा pci_pm_suspend_late	शून्य
#घोषणा pci_pm_suspend_noirq	शून्य
#घोषणा pci_pm_resume		शून्य
#घोषणा pci_pm_resume_early	शून्य
#घोषणा pci_pm_resume_noirq	शून्य

#पूर्ण_अगर /* !CONFIG_SUSPEND */

#अगर_घोषित CONFIG_HIBERNATE_CALLBACKS

अटल पूर्णांक pci_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस pci_legacy_suspend(dev, PMSG_FREEZE);

	अगर (!pm) अणु
		pci_pm_शेष_suspend(pci_dev);
		वापस 0;
	पूर्ण

	/*
	 * Resume all runसमय-suspended devices beक्रमe creating a snapshot
	 * image of प्रणाली memory, because the restore kernel generally cannot
	 * be expected to always handle them consistently and they need to be
	 * put पूर्णांकo the runसमय-active metastate during प्रणाली resume anyway,
	 * so it is better to ensure that the state saved in the image will be
	 * always consistent with that.
	 */
	pm_runसमय_resume(dev);
	pci_dev->state_saved = false;

	अगर (pm->मुक्तze) अणु
		पूर्णांक error;

		error = pm->मुक्तze(dev);
		suspend_report_result(pm->मुक्तze, error);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_मुक्तze_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस pci_legacy_suspend_late(dev, PMSG_FREEZE);

	अगर (pm && pm->मुक्तze_noirq) अणु
		पूर्णांक error;

		error = pm->मुक्तze_noirq(dev);
		suspend_report_result(pm->मुक्तze_noirq, error);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (!pci_dev->state_saved)
		pci_save_state(pci_dev);

	pci_pm_set_unknown_state(pci_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_thaw_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	/*
	 * The pm->thaw_noirq() callback assumes the device has been
	 * वापसed to D0 and its config state has been restored.
	 *
	 * In addition, pci_restore_state() restores MSI-X state in MMIO
	 * space, which requires the device to be in D0, so वापस it to D0
	 * in हाल the driver's "freeze" callbacks put it पूर्णांकo a low-घातer
	 * state.
	 */
	pci_set_घातer_state(pci_dev, PCI_D0);
	pci_restore_state(pci_dev);

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस 0;

	अगर (pm && pm->thaw_noirq)
		वापस pm->thaw_noirq(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_thaw(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	पूर्णांक error = 0;

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस pci_legacy_resume(dev);

	अगर (pm) अणु
		अगर (pm->thaw)
			error = pm->thaw(dev);
	पूर्ण अन्यथा अणु
		pci_pm_reenable_device(pci_dev);
	पूर्ण

	pci_dev->state_saved = false;

	वापस error;
पूर्ण

अटल पूर्णांक pci_pm_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस pci_legacy_suspend(dev, PMSG_HIBERNATE);

	अगर (!pm) अणु
		pci_pm_शेष_suspend(pci_dev);
		वापस 0;
	पूर्ण

	/* The reason to करो that is the same as in pci_pm_suspend(). */
	अगर (!dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_SUSPEND) ||
	    pci_dev_need_resume(pci_dev)) अणु
		pm_runसमय_resume(dev);
		pci_dev->state_saved = false;
	पूर्ण अन्यथा अणु
		pci_dev_adjust_pme(pci_dev);
	पूर्ण

	अगर (pm->घातeroff) अणु
		पूर्णांक error;

		error = pm->घातeroff(dev);
		suspend_report_result(pm->घातeroff, error);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_घातeroff_late(काष्ठा device *dev)
अणु
	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	pci_fixup_device(pci_fixup_suspend, to_pci_dev(dev));

	वापस pm_generic_घातeroff_late(dev);
पूर्ण

अटल पूर्णांक pci_pm_घातeroff_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस pci_legacy_suspend_late(dev, PMSG_HIBERNATE);

	अगर (!pm) अणु
		pci_fixup_device(pci_fixup_suspend_late, pci_dev);
		वापस 0;
	पूर्ण

	अगर (pm->घातeroff_noirq) अणु
		पूर्णांक error;

		error = pm->घातeroff_noirq(dev);
		suspend_report_result(pm->घातeroff_noirq, error);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (!pci_dev->state_saved && !pci_has_subordinate(pci_dev))
		pci_prepare_to_sleep(pci_dev);

	/*
	 * The reason क्रम करोing this here is the same as क्रम the analogous code
	 * in pci_pm_suspend_noirq().
	 */
	अगर (pci_dev->class == PCI_CLASS_SERIAL_USB_EHCI)
		pci_ग_लिखो_config_word(pci_dev, PCI_COMMAND, 0);

	pci_fixup_device(pci_fixup_suspend_late, pci_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_restore_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	pci_pm_शेष_resume_early(pci_dev);
	pci_fixup_device(pci_fixup_resume_early, pci_dev);

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस 0;

	अगर (pm && pm->restore_noirq)
		वापस pm->restore_noirq(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_restore(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	/*
	 * This is necessary क्रम the hibernation error path in which restore is
	 * called without restoring the standard config रेजिस्टरs of the device.
	 */
	अगर (pci_dev->state_saved)
		pci_restore_standard_config(pci_dev);

	अगर (pci_has_legacy_pm_support(pci_dev))
		वापस pci_legacy_resume(dev);

	pci_pm_शेष_resume(pci_dev);

	अगर (pm) अणु
		अगर (pm->restore)
			वापस pm->restore(dev);
	पूर्ण अन्यथा अणु
		pci_pm_reenable_device(pci_dev);
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_HIBERNATE_CALLBACKS */

#घोषणा pci_pm_मुक्तze		शून्य
#घोषणा pci_pm_मुक्तze_noirq	शून्य
#घोषणा pci_pm_thaw		शून्य
#घोषणा pci_pm_thaw_noirq	शून्य
#घोषणा pci_pm_घातeroff		शून्य
#घोषणा pci_pm_घातeroff_late	शून्य
#घोषणा pci_pm_घातeroff_noirq	शून्य
#घोषणा pci_pm_restore		शून्य
#घोषणा pci_pm_restore_noirq	शून्य

#पूर्ण_अगर /* !CONFIG_HIBERNATE_CALLBACKS */

#अगर_घोषित CONFIG_PM

अटल पूर्णांक pci_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	pci_घातer_t prev = pci_dev->current_state;
	पूर्णांक error;

	/*
	 * If pci_dev->driver is not set (unbound), we leave the device in D0,
	 * but it may go to D3cold when the bridge above it runसमय suspends.
	 * Save its config space in हाल that happens.
	 */
	अगर (!pci_dev->driver) अणु
		pci_save_state(pci_dev);
		वापस 0;
	पूर्ण

	pci_dev->state_saved = false;
	अगर (pm && pm->runसमय_suspend) अणु
		error = pm->runसमय_suspend(dev);
		/*
		 * -EBUSY and -EAGAIN is used to request the runसमय PM core
		 * to schedule a new suspend, so log the event only with debug
		 * log level.
		 */
		अगर (error == -EBUSY || error == -EAGAIN) अणु
			pci_dbg(pci_dev, "can't suspend now (%ps returned %d)\n",
				pm->runसमय_suspend, error);
			वापस error;
		पूर्ण अन्यथा अगर (error) अणु
			pci_err(pci_dev, "can't suspend (%ps returned %d)\n",
				pm->runसमय_suspend, error);
			वापस error;
		पूर्ण
	पूर्ण

	pci_fixup_device(pci_fixup_suspend, pci_dev);

	अगर (pm && pm->runसमय_suspend
	    && !pci_dev->state_saved && pci_dev->current_state != PCI_D0
	    && pci_dev->current_state != PCI_UNKNOWN) अणु
		pci_WARN_ONCE(pci_dev, pci_dev->current_state != prev,
			      "PCI PM: State of device not saved by %pS\n",
			      pm->runसमय_suspend);
		वापस 0;
	पूर्ण

	अगर (!pci_dev->state_saved) अणु
		pci_save_state(pci_dev);
		pci_finish_runसमय_suspend(pci_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	pci_घातer_t prev_state = pci_dev->current_state;
	पूर्णांक error = 0;

	/*
	 * Restoring config space is necessary even अगर the device is not bound
	 * to a driver because although we left it in D0, it may have gone to
	 * D3cold when the bridge above it runसमय suspended.
	 */
	pci_restore_standard_config(pci_dev);

	अगर (!pci_dev->driver)
		वापस 0;

	pci_fixup_device(pci_fixup_resume_early, pci_dev);
	pci_pm_शेष_resume(pci_dev);

	अगर (prev_state == PCI_D3cold)
		pci_bridge_रुको_क्रम_secondary_bus(pci_dev);

	अगर (pm && pm->runसमय_resume)
		error = pm->runसमय_resume(dev);

	pci_dev->runसमय_d3cold = false;

	वापस error;
पूर्ण

अटल पूर्णांक pci_pm_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	/*
	 * If pci_dev->driver is not set (unbound), the device should
	 * always reमुख्य in D0 regardless of the runसमय PM status
	 */
	अगर (!pci_dev->driver)
		वापस 0;

	अगर (!pm)
		वापस -ENOSYS;

	अगर (pm->runसमय_idle)
		वापस pm->runसमय_idle(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pci_dev_pm_ops = अणु
	.prepare = pci_pm_prepare,
	.complete = pci_pm_complete,
	.suspend = pci_pm_suspend,
	.suspend_late = pci_pm_suspend_late,
	.resume = pci_pm_resume,
	.resume_early = pci_pm_resume_early,
	.मुक्तze = pci_pm_मुक्तze,
	.thaw = pci_pm_thaw,
	.घातeroff = pci_pm_घातeroff,
	.घातeroff_late = pci_pm_घातeroff_late,
	.restore = pci_pm_restore,
	.suspend_noirq = pci_pm_suspend_noirq,
	.resume_noirq = pci_pm_resume_noirq,
	.मुक्तze_noirq = pci_pm_मुक्तze_noirq,
	.thaw_noirq = pci_pm_thaw_noirq,
	.घातeroff_noirq = pci_pm_घातeroff_noirq,
	.restore_noirq = pci_pm_restore_noirq,
	.runसमय_suspend = pci_pm_runसमय_suspend,
	.runसमय_resume = pci_pm_runसमय_resume,
	.runसमय_idle = pci_pm_runसमय_idle,
पूर्ण;

#घोषणा PCI_PM_OPS_PTR	(&pci_dev_pm_ops)

#अन्यथा /* !CONFIG_PM */

#घोषणा pci_pm_runसमय_suspend	शून्य
#घोषणा pci_pm_runसमय_resume	शून्य
#घोषणा pci_pm_runसमय_idle	शून्य

#घोषणा PCI_PM_OPS_PTR	शून्य

#पूर्ण_अगर /* !CONFIG_PM */

/**
 * __pci_रेजिस्टर_driver - रेजिस्टर a new pci driver
 * @drv: the driver काष्ठाure to रेजिस्टर
 * @owner: owner module of drv
 * @mod_name: module name string
 *
 * Adds the driver काष्ठाure to the list of रेजिस्टरed drivers.
 * Returns a negative value on error, otherwise 0.
 * If no error occurred, the driver reमुख्यs रेजिस्टरed even अगर
 * no device was claimed during registration.
 */
पूर्णांक __pci_रेजिस्टर_driver(काष्ठा pci_driver *drv, काष्ठा module *owner,
			  स्थिर अक्षर *mod_name)
अणु
	/* initialize common driver fields */
	drv->driver.name = drv->name;
	drv->driver.bus = &pci_bus_type;
	drv->driver.owner = owner;
	drv->driver.mod_name = mod_name;
	drv->driver.groups = drv->groups;

	spin_lock_init(&drv->dynids.lock);
	INIT_LIST_HEAD(&drv->dynids.list);

	/* रेजिस्टर with core */
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(__pci_रेजिस्टर_driver);

/**
 * pci_unरेजिस्टर_driver - unरेजिस्टर a pci driver
 * @drv: the driver काष्ठाure to unरेजिस्टर
 *
 * Deletes the driver काष्ठाure from the list of रेजिस्टरed PCI drivers,
 * gives it a chance to clean up by calling its हटाओ() function क्रम
 * each device it was responsible क्रम, and marks those devices as
 * driverless.
 */

व्योम pci_unरेजिस्टर_driver(काष्ठा pci_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
	pci_मुक्त_dynids(drv);
पूर्ण
EXPORT_SYMBOL(pci_unरेजिस्टर_driver);

अटल काष्ठा pci_driver pci_compat_driver = अणु
	.name = "compat"
पूर्ण;

/**
 * pci_dev_driver - get the pci_driver of a device
 * @dev: the device to query
 *
 * Returns the appropriate pci_driver काष्ठाure or %शून्य अगर there is no
 * रेजिस्टरed driver क्रम the device.
 */
काष्ठा pci_driver *pci_dev_driver(स्थिर काष्ठा pci_dev *dev)
अणु
	अगर (dev->driver)
		वापस dev->driver;
	अन्यथा अणु
		पूर्णांक i;
		क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++)
			अगर (dev->resource[i].flags & IORESOURCE_BUSY)
				वापस &pci_compat_driver;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(pci_dev_driver);

/**
 * pci_bus_match - Tell अगर a PCI device काष्ठाure has a matching PCI device id काष्ठाure
 * @dev: the PCI device काष्ठाure to match against
 * @drv: the device driver to search क्रम matching PCI device id काष्ठाures
 *
 * Used by a driver to check whether a PCI device present in the
 * प्रणाली is in its list of supported devices. Returns the matching
 * pci_device_id काष्ठाure or %शून्य अगर there is no match.
 */
अटल पूर्णांक pci_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा pci_driver *pci_drv;
	स्थिर काष्ठा pci_device_id *found_id;

	अगर (!pci_dev->match_driver)
		वापस 0;

	pci_drv = to_pci_driver(drv);
	found_id = pci_match_device(pci_drv, pci_dev);
	अगर (found_id)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * pci_dev_get - increments the reference count of the pci device काष्ठाure
 * @dev: the device being referenced
 *
 * Each live reference to a device should be refcounted.
 *
 * Drivers क्रम PCI devices should normally record such references in
 * their probe() methods, when they bind to a device, and release
 * them by calling pci_dev_put(), in their disconnect() methods.
 *
 * A poपूर्णांकer to the device with the incremented reference counter is वापसed.
 */
काष्ठा pci_dev *pci_dev_get(काष्ठा pci_dev *dev)
अणु
	अगर (dev)
		get_device(&dev->dev);
	वापस dev;
पूर्ण
EXPORT_SYMBOL(pci_dev_get);

/**
 * pci_dev_put - release a use of the pci device काष्ठाure
 * @dev: device that's been disconnected
 *
 * Must be called when a user of a device is finished with it.  When the last
 * user of the device calls this function, the memory of the device is मुक्तd.
 */
व्योम pci_dev_put(काष्ठा pci_dev *dev)
अणु
	अगर (dev)
		put_device(&dev->dev);
पूर्ण
EXPORT_SYMBOL(pci_dev_put);

अटल पूर्णांक pci_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा pci_dev *pdev;

	अगर (!dev)
		वापस -ENODEV;

	pdev = to_pci_dev(dev);

	अगर (add_uevent_var(env, "PCI_CLASS=%04X", pdev->class))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "PCI_ID=%04X:%04X", pdev->venकरोr, pdev->device))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "PCI_SUBSYS_ID=%04X:%04X", pdev->subप्रणाली_venकरोr,
			   pdev->subप्रणाली_device))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "PCI_SLOT_NAME=%s", pci_name(pdev)))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "MODALIAS=pci:v%08Xd%08Xsv%08Xsd%08Xbc%02Xsc%02Xi%02X",
			   pdev->venकरोr, pdev->device,
			   pdev->subप्रणाली_venकरोr, pdev->subप्रणाली_device,
			   (u8)(pdev->class >> 16), (u8)(pdev->class >> 8),
			   (u8)(pdev->class)))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

#अगर defined(CONFIG_PCIEPORTBUS) || defined(CONFIG_EEH)
/**
 * pci_uevent_ers - emit a uevent during recovery path of PCI device
 * @pdev: PCI device undergoing error recovery
 * @err_type: type of error event
 */
व्योम pci_uevent_ers(काष्ठा pci_dev *pdev, क्रमागत pci_ers_result err_type)
अणु
	पूर्णांक idx = 0;
	अक्षर *envp[3];

	चयन (err_type) अणु
	हाल PCI_ERS_RESULT_NONE:
	हाल PCI_ERS_RESULT_CAN_RECOVER:
		envp[idx++] = "ERROR_EVENT=BEGIN_RECOVERY";
		envp[idx++] = "DEVICE_ONLINE=0";
		अवरोध;
	हाल PCI_ERS_RESULT_RECOVERED:
		envp[idx++] = "ERROR_EVENT=SUCCESSFUL_RECOVERY";
		envp[idx++] = "DEVICE_ONLINE=1";
		अवरोध;
	हाल PCI_ERS_RESULT_DISCONNECT:
		envp[idx++] = "ERROR_EVENT=FAILED_RECOVERY";
		envp[idx++] = "DEVICE_ONLINE=0";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (idx > 0) अणु
		envp[idx++] = शून्य;
		kobject_uevent_env(&pdev->dev.kobj, KOBJ_CHANGE, envp);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pci_bus_num_vf(काष्ठा device *dev)
अणु
	वापस pci_num_vf(to_pci_dev(dev));
पूर्ण

/**
 * pci_dma_configure - Setup DMA configuration
 * @dev: ptr to dev काष्ठाure
 *
 * Function to update PCI devices's DMA configuration using the same
 * info from the OF node or ACPI node of host bridge's parent (अगर any).
 */
अटल पूर्णांक pci_dma_configure(काष्ठा device *dev)
अणु
	काष्ठा device *bridge;
	पूर्णांक ret = 0;

	bridge = pci_get_host_bridge_device(to_pci_dev(dev));

	अगर (IS_ENABLED(CONFIG_OF) && bridge->parent &&
	    bridge->parent->of_node) अणु
		ret = of_dma_configure(dev, bridge->parent->of_node, true);
	पूर्ण अन्यथा अगर (has_acpi_companion(bridge)) अणु
		काष्ठा acpi_device *adev = to_acpi_device_node(bridge->fwnode);

		ret = acpi_dma_configure(dev, acpi_get_dma_attr(adev));
	पूर्ण

	pci_put_host_bridge_device(bridge);
	वापस ret;
पूर्ण

काष्ठा bus_type pci_bus_type = अणु
	.name		= "pci",
	.match		= pci_bus_match,
	.uevent		= pci_uevent,
	.probe		= pci_device_probe,
	.हटाओ		= pci_device_हटाओ,
	.shutकरोwn	= pci_device_shutकरोwn,
	.dev_groups	= pci_dev_groups,
	.bus_groups	= pci_bus_groups,
	.drv_groups	= pci_drv_groups,
	.pm		= PCI_PM_OPS_PTR,
	.num_vf		= pci_bus_num_vf,
	.dma_configure	= pci_dma_configure,
पूर्ण;
EXPORT_SYMBOL(pci_bus_type);

#अगर_घोषित CONFIG_PCIEPORTBUS
अटल पूर्णांक pcie_port_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा pcie_device *pciedev;
	काष्ठा pcie_port_service_driver *driver;

	अगर (drv->bus != &pcie_port_bus_type || dev->bus != &pcie_port_bus_type)
		वापस 0;

	pciedev = to_pcie_device(dev);
	driver = to_service_driver(drv);

	अगर (driver->service != pciedev->service)
		वापस 0;

	अगर (driver->port_type != PCIE_ANY_PORT &&
	    driver->port_type != pci_pcie_type(pciedev->port))
		वापस 0;

	वापस 1;
पूर्ण

काष्ठा bus_type pcie_port_bus_type = अणु
	.name		= "pci_express",
	.match		= pcie_port_bus_match,
पूर्ण;
EXPORT_SYMBOL_GPL(pcie_port_bus_type);
#पूर्ण_अगर

अटल पूर्णांक __init pci_driver_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&pci_bus_type);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_PCIEPORTBUS
	ret = bus_रेजिस्टर(&pcie_port_bus_type);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर
	dma_debug_add_bus(&pci_bus_type);
	वापस 0;
पूर्ण
postcore_initcall(pci_driver_init);
