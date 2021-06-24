<शैली गुरु>
/*
 * PCI Stub Driver - Grअसल devices in backend to be exported later
 *
 * Ryan Wilson <hap9@epoch.ncsc.mil>
 * Chris Bookholt <hap10@epoch.ncsc.mil>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#घोषणा dev_fmt pr_fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kref.h>
#समावेश <linux/pci.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/atomic.h>
#समावेश <xen/events.h>
#समावेश <यंत्र/xen/pci.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/पूर्णांकerface/physdev.h>
#समावेश "pciback.h"
#समावेश "conf_space.h"
#समावेश "conf_space_quirks.h"

#घोषणा PCISTUB_DRIVER_NAME "pciback"

अटल अक्षर *pci_devs_to_hide;
रुको_queue_head_t xen_pcibk_aer_रुको_queue;
/*Add sem क्रम sync AER handling and xen_pcibk हटाओ/reconfigue ops,
* We want to aव्योम in middle of AER ops, xen_pcibk devices is being हटाओd
*/
अटल DECLARE_RWSEM(pcistub_sem);
module_param_named(hide, pci_devs_to_hide, अक्षरp, 0444);

काष्ठा pcistub_device_id अणु
	काष्ठा list_head slot_list;
	पूर्णांक करोमुख्य;
	अचिन्हित अक्षर bus;
	अचिन्हित पूर्णांक devfn;
पूर्ण;
अटल LIST_HEAD(pcistub_device_ids);
अटल DEFINE_SPINLOCK(device_ids_lock);

काष्ठा pcistub_device अणु
	काष्ठा kref kref;
	काष्ठा list_head dev_list;
	spinlock_t lock;

	काष्ठा pci_dev *dev;
	काष्ठा xen_pcibk_device *pdev;/* non-शून्य अगर काष्ठा pci_dev is in use */
पूर्ण;

/* Access to pcistub_devices & seized_devices lists and the initialize_devices
 * flag must be locked with pcistub_devices_lock
 */
अटल DEFINE_SPINLOCK(pcistub_devices_lock);
अटल LIST_HEAD(pcistub_devices);

/* रुको क्रम device_initcall beक्रमe initializing our devices
 * (see pcistub_init_devices_late)
 */
अटल पूर्णांक initialize_devices;
अटल LIST_HEAD(seized_devices);

अटल काष्ठा pcistub_device *pcistub_device_alloc(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcistub_device *psdev;

	dev_dbg(&dev->dev, "pcistub_device_alloc\n");

	psdev = kzalloc(माप(*psdev), GFP_KERNEL);
	अगर (!psdev)
		वापस शून्य;

	psdev->dev = pci_dev_get(dev);
	अगर (!psdev->dev) अणु
		kमुक्त(psdev);
		वापस शून्य;
	पूर्ण

	kref_init(&psdev->kref);
	spin_lock_init(&psdev->lock);

	वापस psdev;
पूर्ण

/* Don't call this directly as it's called by pcistub_device_put */
अटल व्योम pcistub_device_release(काष्ठा kref *kref)
अणु
	काष्ठा pcistub_device *psdev;
	काष्ठा pci_dev *dev;
	काष्ठा xen_pcibk_dev_data *dev_data;

	psdev = container_of(kref, काष्ठा pcistub_device, kref);
	dev = psdev->dev;
	dev_data = pci_get_drvdata(dev);

	dev_dbg(&dev->dev, "pcistub_device_release\n");

	xen_unरेजिस्टर_device_करोमुख्य_owner(dev);

	/* Call the reset function which करोes not take lock as this
	 * is called from "unbind" which takes a device_lock mutex.
	 */
	__pci_reset_function_locked(dev);
	अगर (dev_data &&
	    pci_load_and_मुक्त_saved_state(dev, &dev_data->pci_saved_state))
		dev_info(&dev->dev, "Could not reload PCI state\n");
	अन्यथा
		pci_restore_state(dev);

	अगर (dev->msix_cap) अणु
		काष्ठा physdev_pci_device ppdev = अणु
			.seg = pci_करोमुख्य_nr(dev->bus),
			.bus = dev->bus->number,
			.devfn = dev->devfn
		पूर्ण;
		पूर्णांक err = HYPERVISOR_physdev_op(PHYSDEVOP_release_msix,
						&ppdev);

		अगर (err && err != -ENOSYS)
			dev_warn(&dev->dev, "MSI-X release failed (%d)\n",
				 err);
	पूर्ण

	/* Disable the device */
	xen_pcibk_reset_device(dev);

	kमुक्त(dev_data);
	pci_set_drvdata(dev, शून्य);

	/* Clean-up the device */
	xen_pcibk_config_मुक्त_dyn_fields(dev);
	xen_pcibk_config_मुक्त_dev(dev);

	pci_clear_dev_asचिन्हित(dev);
	pci_dev_put(dev);

	kमुक्त(psdev);
पूर्ण

अटल अंतरभूत व्योम pcistub_device_get(काष्ठा pcistub_device *psdev)
अणु
	kref_get(&psdev->kref);
पूर्ण

अटल अंतरभूत व्योम pcistub_device_put(काष्ठा pcistub_device *psdev)
अणु
	kref_put(&psdev->kref, pcistub_device_release);
पूर्ण

अटल काष्ठा pcistub_device *pcistub_device_find_locked(पूर्णांक करोमुख्य, पूर्णांक bus,
							 पूर्णांक slot, पूर्णांक func)
अणु
	काष्ठा pcistub_device *psdev;

	list_क्रम_each_entry(psdev, &pcistub_devices, dev_list) अणु
		अगर (psdev->dev != शून्य
		    && करोमुख्य == pci_करोमुख्य_nr(psdev->dev->bus)
		    && bus == psdev->dev->bus->number
		    && slot == PCI_SLOT(psdev->dev->devfn)
		    && func == PCI_FUNC(psdev->dev->devfn)) अणु
			वापस psdev;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा pcistub_device *pcistub_device_find(पूर्णांक करोमुख्य, पूर्णांक bus,
						  पूर्णांक slot, पूर्णांक func)
अणु
	काष्ठा pcistub_device *psdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pcistub_devices_lock, flags);

	psdev = pcistub_device_find_locked(करोमुख्य, bus, slot, func);
	अगर (psdev)
		pcistub_device_get(psdev);

	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	वापस psdev;
पूर्ण

अटल काष्ठा pci_dev *pcistub_device_get_pci_dev(काष्ठा xen_pcibk_device *pdev,
						  काष्ठा pcistub_device *psdev)
अणु
	काष्ठा pci_dev *pci_dev = शून्य;
	अचिन्हित दीर्घ flags;

	pcistub_device_get(psdev);

	spin_lock_irqsave(&psdev->lock, flags);
	अगर (!psdev->pdev) अणु
		psdev->pdev = pdev;
		pci_dev = psdev->dev;
	पूर्ण
	spin_unlock_irqrestore(&psdev->lock, flags);

	अगर (!pci_dev)
		pcistub_device_put(psdev);

	वापस pci_dev;
पूर्ण

काष्ठा pci_dev *pcistub_get_pci_dev_by_slot(काष्ठा xen_pcibk_device *pdev,
					    पूर्णांक करोमुख्य, पूर्णांक bus,
					    पूर्णांक slot, पूर्णांक func)
अणु
	काष्ठा pcistub_device *psdev;
	काष्ठा pci_dev *found_dev = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pcistub_devices_lock, flags);

	psdev = pcistub_device_find_locked(करोमुख्य, bus, slot, func);
	अगर (psdev)
		found_dev = pcistub_device_get_pci_dev(pdev, psdev);

	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	वापस found_dev;
पूर्ण

काष्ठा pci_dev *pcistub_get_pci_dev(काष्ठा xen_pcibk_device *pdev,
				    काष्ठा pci_dev *dev)
अणु
	काष्ठा pcistub_device *psdev;
	काष्ठा pci_dev *found_dev = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pcistub_devices_lock, flags);

	list_क्रम_each_entry(psdev, &pcistub_devices, dev_list) अणु
		अगर (psdev->dev == dev) अणु
			found_dev = pcistub_device_get_pci_dev(pdev, psdev);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	वापस found_dev;
पूर्ण

/*
 * Called when:
 *  - XenBus state has been reconfigure (pci unplug). See xen_pcibk_हटाओ_device
 *  - XenBus state has been disconnected (guest shutकरोwn). See xen_pcibk_xenbus_हटाओ
 *  - 'echo BDF > unbind' on pciback module with no guest attached. See pcistub_हटाओ
 *  - 'echo BDF > unbind' with a guest still using it. See pcistub_हटाओ
 *
 *  As such we have to be careful.
 *
 *  To make this easier, the caller has to hold the device lock.
 */
व्योम pcistub_put_pci_dev(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcistub_device *psdev, *found_psdev = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा xen_pcibk_dev_data *dev_data;
	पूर्णांक ret;

	spin_lock_irqsave(&pcistub_devices_lock, flags);

	list_क्रम_each_entry(psdev, &pcistub_devices, dev_list) अणु
		अगर (psdev->dev == dev) अणु
			found_psdev = psdev;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	अगर (WARN_ON(!found_psdev))
		वापस;

	/*hold this lock क्रम aव्योमing अवरोधing link between
	* pcistub and xen_pcibk when AER is in processing
	*/
	करोwn_ग_लिखो(&pcistub_sem);
	/* Cleanup our device
	 * (so it's पढ़ोy क्रम the next करोमुख्य)
	 */
	device_lock_निश्चित(&dev->dev);
	__pci_reset_function_locked(dev);

	dev_data = pci_get_drvdata(dev);
	ret = pci_load_saved_state(dev, dev_data->pci_saved_state);
	अगर (!ret) अणु
		/*
		 * The usual sequence is pci_save_state & pci_restore_state
		 * but the guest might have messed the configuration space up.
		 * Use the initial version (when device was bound to us).
		 */
		pci_restore_state(dev);
	पूर्ण अन्यथा
		dev_info(&dev->dev, "Could not reload PCI state\n");
	/* This disables the device. */
	xen_pcibk_reset_device(dev);

	/* And cleanup up our emulated fields. */
	xen_pcibk_config_reset_dev(dev);
	xen_pcibk_config_मुक्त_dyn_fields(dev);

	dev_data->allow_पूर्णांकerrupt_control = 0;

	xen_unरेजिस्टर_device_करोमुख्य_owner(dev);

	spin_lock_irqsave(&found_psdev->lock, flags);
	found_psdev->pdev = शून्य;
	spin_unlock_irqrestore(&found_psdev->lock, flags);

	pcistub_device_put(found_psdev);
	up_ग_लिखो(&pcistub_sem);
पूर्ण

अटल पूर्णांक pcistub_match_one(काष्ठा pci_dev *dev,
			     काष्ठा pcistub_device_id *pdev_id)
अणु
	/* Match the specअगरied device by करोमुख्य, bus, slot, func and also अगर
	 * any of the device's parent bridges match.
	 */
	क्रम (; dev != शून्य; dev = dev->bus->self) अणु
		अगर (pci_करोमुख्य_nr(dev->bus) == pdev_id->करोमुख्य
		    && dev->bus->number == pdev_id->bus
		    && dev->devfn == pdev_id->devfn)
			वापस 1;

		/* Someबार topmost bridge links to itself. */
		अगर (dev == dev->bus->self)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcistub_match(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcistub_device_id *pdev_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक found = 0;

	spin_lock_irqsave(&device_ids_lock, flags);
	list_क्रम_each_entry(pdev_id, &pcistub_device_ids, slot_list) अणु
		अगर (pcistub_match_one(dev, pdev_id)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&device_ids_lock, flags);

	वापस found;
पूर्ण

अटल पूर्णांक pcistub_init_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_pcibk_dev_data *dev_data;
	पूर्णांक err = 0;

	dev_dbg(&dev->dev, "initializing...\n");

	/* The PCI backend is not पूर्णांकended to be a module (or to work with
	 * removable PCI devices (yet). If it were, xen_pcibk_config_मुक्त()
	 * would need to be called somewhere to मुक्त the memory allocated
	 * here and then to call kमुक्त(pci_get_drvdata(psdev->dev)).
	 */
	dev_data = kzalloc(माप(*dev_data) +  म_माप(DRV_NAME "[]")
				+ म_माप(pci_name(dev)) + 1, GFP_KERNEL);
	अगर (!dev_data) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	pci_set_drvdata(dev, dev_data);

	/*
	 * Setup name क्रम fake IRQ handler. It will only be enabled
	 * once the device is turned on by the guest.
	 */
	प्र_लिखो(dev_data->irq_name, DRV_NAME "[%s]", pci_name(dev));

	dev_dbg(&dev->dev, "initializing config\n");

	init_रुकोqueue_head(&xen_pcibk_aer_रुको_queue);
	err = xen_pcibk_config_init_dev(dev);
	अगर (err)
		जाओ out;

	/* HACK: Force device (& ACPI) to determine what IRQ it's on - we
	 * must करो this here because pcibios_enable_device may specअगरy
	 * the pci device's true irq (and possibly its other resources)
	 * अगर they dअगरfer from what's in the configuration space.
	 * This makes the assumption that the device's resources won't
	 * change after this poपूर्णांक (otherwise this code may अवरोध!)
	 */
	dev_dbg(&dev->dev, "enabling device\n");
	err = pci_enable_device(dev);
	अगर (err)
		जाओ config_release;

	अगर (dev->msix_cap) अणु
		काष्ठा physdev_pci_device ppdev = अणु
			.seg = pci_करोमुख्य_nr(dev->bus),
			.bus = dev->bus->number,
			.devfn = dev->devfn
		पूर्ण;

		err = HYPERVISOR_physdev_op(PHYSDEVOP_prepare_msix, &ppdev);
		अगर (err && err != -ENOSYS)
			dev_err(&dev->dev, "MSI-X preparation failed (%d)\n",
				err);
	पूर्ण

	/* We need the device active to save the state. */
	dev_dbg(&dev->dev, "save state of device\n");
	pci_save_state(dev);
	dev_data->pci_saved_state = pci_store_saved_state(dev);
	अगर (!dev_data->pci_saved_state)
		dev_err(&dev->dev, "Could not store PCI conf saved state!\n");
	अन्यथा अणु
		dev_dbg(&dev->dev, "resetting (FLR, D3, etc) the device\n");
		__pci_reset_function_locked(dev);
		pci_restore_state(dev);
	पूर्ण
	/* Now disable the device (this also ensures some निजी device
	 * data is setup beक्रमe we export)
	 */
	dev_dbg(&dev->dev, "reset device\n");
	xen_pcibk_reset_device(dev);

	pci_set_dev_asचिन्हित(dev);
	वापस 0;

config_release:
	xen_pcibk_config_मुक्त_dev(dev);

out:
	pci_set_drvdata(dev, शून्य);
	kमुक्त(dev_data);
	वापस err;
पूर्ण

/*
 * Because some initialization still happens on
 * devices during fs_initcall, we need to defer
 * full initialization of our devices until
 * device_initcall.
 */
अटल पूर्णांक __init pcistub_init_devices_late(व्योम)
अणु
	काष्ठा pcistub_device *psdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	spin_lock_irqsave(&pcistub_devices_lock, flags);

	जबतक (!list_empty(&seized_devices)) अणु
		psdev = container_of(seized_devices.next,
				     काष्ठा pcistub_device, dev_list);
		list_del(&psdev->dev_list);

		spin_unlock_irqrestore(&pcistub_devices_lock, flags);

		err = pcistub_init_device(psdev->dev);
		अगर (err) अणु
			dev_err(&psdev->dev->dev,
				"error %d initializing device\n", err);
			kमुक्त(psdev);
			psdev = शून्य;
		पूर्ण

		spin_lock_irqsave(&pcistub_devices_lock, flags);

		अगर (psdev)
			list_add_tail(&psdev->dev_list, &pcistub_devices);
	पूर्ण

	initialize_devices = 1;

	spin_unlock_irqrestore(&pcistub_devices_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम pcistub_device_id_add_list(काष्ठा pcistub_device_id *new,
				       पूर्णांक करोमुख्य, पूर्णांक bus, अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा pcistub_device_id *pci_dev_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक found = 0;

	spin_lock_irqsave(&device_ids_lock, flags);

	list_क्रम_each_entry(pci_dev_id, &pcistub_device_ids, slot_list) अणु
		अगर (pci_dev_id->करोमुख्य == करोमुख्य && pci_dev_id->bus == bus &&
		    pci_dev_id->devfn == devfn) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		new->करोमुख्य = करोमुख्य;
		new->bus = bus;
		new->devfn = devfn;
		list_add_tail(&new->slot_list, &pcistub_device_ids);
	पूर्ण

	spin_unlock_irqrestore(&device_ids_lock, flags);

	अगर (found)
		kमुक्त(new);
पूर्ण

अटल पूर्णांक pcistub_seize(काष्ठा pci_dev *dev,
			 काष्ठा pcistub_device_id *pci_dev_id)
अणु
	काष्ठा pcistub_device *psdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	psdev = pcistub_device_alloc(dev);
	अगर (!psdev) अणु
		kमुक्त(pci_dev_id);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&pcistub_devices_lock, flags);

	अगर (initialize_devices) अणु
		spin_unlock_irqrestore(&pcistub_devices_lock, flags);

		/* करोn't want irqs disabled when calling pcistub_init_device */
		err = pcistub_init_device(psdev->dev);

		spin_lock_irqsave(&pcistub_devices_lock, flags);

		अगर (!err)
			list_add(&psdev->dev_list, &pcistub_devices);
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->dev, "deferring initialization\n");
		list_add(&psdev->dev_list, &seized_devices);
	पूर्ण

	spin_unlock_irqrestore(&pcistub_devices_lock, flags);

	अगर (err) अणु
		kमुक्त(pci_dev_id);
		pcistub_device_put(psdev);
	पूर्ण अन्यथा अगर (pci_dev_id)
		pcistub_device_id_add_list(pci_dev_id, pci_करोमुख्य_nr(dev->bus),
					   dev->bus->number, dev->devfn);

	वापस err;
पूर्ण

/* Called when 'bind'. This means we must _NOT_ call pci_reset_function or
 * other functions that take the sysfs lock. */
अटल पूर्णांक pcistub_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err = 0, match;
	काष्ठा pcistub_device_id *pci_dev_id = शून्य;

	dev_dbg(&dev->dev, "probing...\n");

	match = pcistub_match(dev);

	अगर ((dev->driver_override &&
	     !म_भेद(dev->driver_override, PCISTUB_DRIVER_NAME)) ||
	    match) अणु

		अगर (dev->hdr_type != PCI_HEADER_TYPE_NORMAL
		    && dev->hdr_type != PCI_HEADER_TYPE_BRIDGE) अणु
			dev_err(&dev->dev, "can't export pci devices that "
				"don't have a normal (0) or bridge (1) "
				"header type!\n");
			err = -ENODEV;
			जाओ out;
		पूर्ण

		अगर (!match) अणु
			pci_dev_id = kदो_स्मृति(माप(*pci_dev_id), GFP_KERNEL);
			अगर (!pci_dev_id) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण

		dev_info(&dev->dev, "seizing device\n");
		err = pcistub_seize(dev, pci_dev_id);
	पूर्ण अन्यथा
		/* Didn't find the device */
		err = -ENODEV;

out:
	वापस err;
पूर्ण

/* Called when 'unbind'. This means we must _NOT_ call pci_reset_function or
 * other functions that take the sysfs lock. */
अटल व्योम pcistub_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcistub_device *psdev, *found_psdev = शून्य;
	अचिन्हित दीर्घ flags;

	dev_dbg(&dev->dev, "removing\n");

	spin_lock_irqsave(&pcistub_devices_lock, flags);

	xen_pcibk_config_quirk_release(dev);

	list_क्रम_each_entry(psdev, &pcistub_devices, dev_list) अणु
		अगर (psdev->dev == dev) अणु
			found_psdev = psdev;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pcistub_devices_lock, flags);

	अगर (found_psdev) अणु
		dev_dbg(&dev->dev, "found device to remove %s\n",
			found_psdev->pdev ? "- in-use" : "");

		अगर (found_psdev->pdev) अणु
			पूर्णांक करोmid = xen_find_device_करोमुख्य_owner(dev);

			dev_warn(&dev->dev, "****** removing device %s while still in-use by domain %d! ******\n",
			       pci_name(found_psdev->dev), करोmid);
			dev_warn(&dev->dev, "****** driver domain may still access this device's i/o resources!\n");
			dev_warn(&dev->dev, "****** shutdown driver domain before binding device\n");
			dev_warn(&dev->dev, "****** to other drivers or domains\n");

			/* N.B. This ends up calling pcistub_put_pci_dev which ends up
			 * करोing the FLR. */
			xen_pcibk_release_pci_dev(found_psdev->pdev,
						found_psdev->dev,
						false /* caller holds the lock. */);
		पूर्ण

		spin_lock_irqsave(&pcistub_devices_lock, flags);
		list_del(&found_psdev->dev_list);
		spin_unlock_irqrestore(&pcistub_devices_lock, flags);

		/* the final put क्रम releasing from the list */
		pcistub_device_put(found_psdev);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id pcistub_ids[] = अणु
	अणु
	 .venकरोr = PCI_ANY_ID,
	 .device = PCI_ANY_ID,
	 .subvenकरोr = PCI_ANY_ID,
	 .subdevice = PCI_ANY_ID,
	 पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

#घोषणा PCI_NODENAME_MAX 40
अटल व्योम समाप्त_करोमुख्य_by_device(काष्ठा pcistub_device *psdev)
अणु
	काष्ठा xenbus_transaction xbt;
	पूर्णांक err;
	अक्षर nodename[PCI_NODENAME_MAX];

	BUG_ON(!psdev);
	snम_लिखो(nodename, PCI_NODENAME_MAX, "/local/domain/0/backend/pci/%d/0",
		psdev->pdev->xdev->otherend_id);

again:
	err = xenbus_transaction_start(&xbt);
	अगर (err) अणु
		dev_err(&psdev->dev->dev,
			"error %d when start xenbus transaction\n", err);
		वापस;
	पूर्ण
	/*PV AER handlers will set this flag*/
	xenbus_म_लिखो(xbt, nodename, "aerState" , "aerfail");
	err = xenbus_transaction_end(xbt, 0);
	अगर (err) अणु
		अगर (err == -EAGAIN)
			जाओ again;
		dev_err(&psdev->dev->dev,
			"error %d when end xenbus transaction\n", err);
		वापस;
	पूर्ण
पूर्ण

/* For each aer recovery step error_detected, mmio_enabled, etc, front_end and
 * backend need to have cooperation. In xen_pcibk, those steps will करो similar
 * jobs: send service request and रुकोing क्रम front_end response.
*/
अटल pci_ers_result_t common_process(काष्ठा pcistub_device *psdev,
				       pci_channel_state_t state, पूर्णांक aer_cmd,
				       pci_ers_result_t result)
अणु
	pci_ers_result_t res = result;
	काष्ठा xen_pcie_aer_op *aer_op;
	काष्ठा xen_pcibk_device *pdev = psdev->pdev;
	काष्ठा xen_pci_sharedinfo *sh_info = pdev->sh_info;
	पूर्णांक ret;

	/*with PV AER drivers*/
	aer_op = &(sh_info->aer_op);
	aer_op->cmd = aer_cmd ;
	/*useful क्रम error_detected callback*/
	aer_op->err = state;
	/*pcअगरront_end BDF*/
	ret = xen_pcibk_get_pcअगरront_dev(psdev->dev, psdev->pdev,
		&aer_op->करोमुख्य, &aer_op->bus, &aer_op->devfn);
	अगर (!ret) अणु
		dev_err(&psdev->dev->dev, "failed to get pcifront device\n");
		वापस PCI_ERS_RESULT_NONE;
	पूर्ण
	wmb();

	dev_dbg(&psdev->dev->dev, "aer_op %x dom %x bus %x devfn %x\n",
			aer_cmd, aer_op->करोमुख्य, aer_op->bus, aer_op->devfn);
	/*local flag to mark there's aer request, xen_pcibk callback will use
	* this flag to judge whether we need to check pci-front give aer
	* service ack संकेत
	*/
	set_bit(_PCIB_op_pending, (अचिन्हित दीर्घ *)&pdev->flags);

	/*It is possible that a pcअगरront conf_पढ़ो_ग_लिखो ops request invokes
	* the callback which cause the spurious execution of wake_up.
	* Yet it is harmless and better than a spinlock here
	*/
	set_bit(_XEN_PCIB_active,
		(अचिन्हित दीर्घ *)&sh_info->flags);
	wmb();
	notअगरy_remote_via_irq(pdev->evtchn_irq);

	/* Enable IRQ to संकेत "request done". */
	xen_pcibk_lateeoi(pdev, 0);

	ret = रुको_event_समयout(xen_pcibk_aer_रुको_queue,
				 !(test_bit(_XEN_PCIB_active, (अचिन्हित दीर्घ *)
				 &sh_info->flags)), 300*HZ);

	/* Enable IRQ क्रम pcअगरront request अगर not alपढ़ोy active. */
	अगर (!test_bit(_PDEVF_op_active, &pdev->flags))
		xen_pcibk_lateeoi(pdev, 0);

	अगर (!ret) अणु
		अगर (test_bit(_XEN_PCIB_active,
			(अचिन्हित दीर्घ *)&sh_info->flags)) अणु
			dev_err(&psdev->dev->dev,
				"pcifront aer process not responding!\n");
			clear_bit(_XEN_PCIB_active,
			  (अचिन्हित दीर्घ *)&sh_info->flags);
			aer_op->err = PCI_ERS_RESULT_NONE;
			वापस res;
		पूर्ण
	पूर्ण
	clear_bit(_PCIB_op_pending, (अचिन्हित दीर्घ *)&pdev->flags);

	res = (pci_ers_result_t)aer_op->err;
	वापस res;
पूर्ण

/*
* xen_pcibk_slot_reset: it will send the slot_reset request to  pcअगरront in हाल
* of the device driver could provide this service, and then रुको क्रम pcअगरront
* ack.
* @dev: poपूर्णांकer to PCI devices
* वापस value is used by aer_core करो_recovery policy
*/
अटल pci_ers_result_t xen_pcibk_slot_reset(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcistub_device *psdev;
	pci_ers_result_t result;

	result = PCI_ERS_RESULT_RECOVERED;
	dev_dbg(&dev->dev, "xen_pcibk_slot_reset(bus:%x,devfn:%x)\n",
		dev->bus->number, dev->devfn);

	करोwn_ग_लिखो(&pcistub_sem);
	psdev = pcistub_device_find(pci_करोमुख्य_nr(dev->bus),
				dev->bus->number,
				PCI_SLOT(dev->devfn),
				PCI_FUNC(dev->devfn));

	अगर (!psdev || !psdev->pdev) अणु
		dev_err(&dev->dev, "device is not found/assigned\n");
		जाओ end;
	पूर्ण

	अगर (!psdev->pdev->sh_info) अणु
		dev_err(&dev->dev, "device is not connected or owned"
			" by HVM, kill it\n");
		समाप्त_करोमुख्य_by_device(psdev);
		जाओ end;
	पूर्ण

	अगर (!test_bit(_XEN_PCIB_AERHANDLER,
		(अचिन्हित दीर्घ *)&psdev->pdev->sh_info->flags)) अणु
		dev_err(&dev->dev,
			"guest with no AER driver should have been killed\n");
		जाओ end;
	पूर्ण
	result = common_process(psdev, pci_channel_io_normal, XEN_PCI_OP_aer_slotreset, result);

	अगर (result == PCI_ERS_RESULT_NONE ||
		result == PCI_ERS_RESULT_DISCONNECT) अणु
		dev_dbg(&dev->dev,
			"No AER slot_reset service or disconnected!\n");
		समाप्त_करोमुख्य_by_device(psdev);
	पूर्ण
end:
	अगर (psdev)
		pcistub_device_put(psdev);
	up_ग_लिखो(&pcistub_sem);
	वापस result;

पूर्ण


/*xen_pcibk_mmio_enabled: it will send the mmio_enabled request to  pcअगरront
* in हाल of the device driver could provide this service, and then रुको
* क्रम pcअगरront ack
* @dev: poपूर्णांकer to PCI devices
* वापस value is used by aer_core करो_recovery policy
*/

अटल pci_ers_result_t xen_pcibk_mmio_enabled(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcistub_device *psdev;
	pci_ers_result_t result;

	result = PCI_ERS_RESULT_RECOVERED;
	dev_dbg(&dev->dev, "xen_pcibk_mmio_enabled(bus:%x,devfn:%x)\n",
		dev->bus->number, dev->devfn);

	करोwn_ग_लिखो(&pcistub_sem);
	psdev = pcistub_device_find(pci_करोमुख्य_nr(dev->bus),
				dev->bus->number,
				PCI_SLOT(dev->devfn),
				PCI_FUNC(dev->devfn));

	अगर (!psdev || !psdev->pdev) अणु
		dev_err(&dev->dev, "device is not found/assigned\n");
		जाओ end;
	पूर्ण

	अगर (!psdev->pdev->sh_info) अणु
		dev_err(&dev->dev, "device is not connected or owned"
			" by HVM, kill it\n");
		समाप्त_करोमुख्य_by_device(psdev);
		जाओ end;
	पूर्ण

	अगर (!test_bit(_XEN_PCIB_AERHANDLER,
		(अचिन्हित दीर्घ *)&psdev->pdev->sh_info->flags)) अणु
		dev_err(&dev->dev,
			"guest with no AER driver should have been killed\n");
		जाओ end;
	पूर्ण
	result = common_process(psdev, pci_channel_io_normal, XEN_PCI_OP_aer_mmio, result);

	अगर (result == PCI_ERS_RESULT_NONE ||
		result == PCI_ERS_RESULT_DISCONNECT) अणु
		dev_dbg(&dev->dev,
			"No AER mmio_enabled service or disconnected!\n");
		समाप्त_करोमुख्य_by_device(psdev);
	पूर्ण
end:
	अगर (psdev)
		pcistub_device_put(psdev);
	up_ग_लिखो(&pcistub_sem);
	वापस result;
पूर्ण

/*xen_pcibk_error_detected: it will send the error_detected request to  pcअगरront
* in हाल of the device driver could provide this service, and then रुको
* क्रम pcअगरront ack.
* @dev: poपूर्णांकer to PCI devices
* @error: the current PCI connection state
* वापस value is used by aer_core करो_recovery policy
*/

अटल pci_ers_result_t xen_pcibk_error_detected(काष्ठा pci_dev *dev,
	pci_channel_state_t error)
अणु
	काष्ठा pcistub_device *psdev;
	pci_ers_result_t result;

	result = PCI_ERS_RESULT_CAN_RECOVER;
	dev_dbg(&dev->dev, "xen_pcibk_error_detected(bus:%x,devfn:%x)\n",
		dev->bus->number, dev->devfn);

	करोwn_ग_लिखो(&pcistub_sem);
	psdev = pcistub_device_find(pci_करोमुख्य_nr(dev->bus),
				dev->bus->number,
				PCI_SLOT(dev->devfn),
				PCI_FUNC(dev->devfn));

	अगर (!psdev || !psdev->pdev) अणु
		dev_err(&dev->dev, "device is not found/assigned\n");
		जाओ end;
	पूर्ण

	अगर (!psdev->pdev->sh_info) अणु
		dev_err(&dev->dev, "device is not connected or owned"
			" by HVM, kill it\n");
		समाप्त_करोमुख्य_by_device(psdev);
		जाओ end;
	पूर्ण

	/*Guest owns the device yet no aer handler regiested, समाप्त guest*/
	अगर (!test_bit(_XEN_PCIB_AERHANDLER,
		(अचिन्हित दीर्घ *)&psdev->pdev->sh_info->flags)) अणु
		dev_dbg(&dev->dev, "guest may have no aer driver, kill it\n");
		समाप्त_करोमुख्य_by_device(psdev);
		जाओ end;
	पूर्ण
	result = common_process(psdev, error, XEN_PCI_OP_aer_detected, result);

	अगर (result == PCI_ERS_RESULT_NONE ||
		result == PCI_ERS_RESULT_DISCONNECT) अणु
		dev_dbg(&dev->dev,
			"No AER error_detected service or disconnected!\n");
		समाप्त_करोमुख्य_by_device(psdev);
	पूर्ण
end:
	अगर (psdev)
		pcistub_device_put(psdev);
	up_ग_लिखो(&pcistub_sem);
	वापस result;
पूर्ण

/*xen_pcibk_error_resume: it will send the error_resume request to  pcअगरront
* in हाल of the device driver could provide this service, and then रुको
* क्रम pcअगरront ack.
* @dev: poपूर्णांकer to PCI devices
*/

अटल व्योम xen_pcibk_error_resume(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcistub_device *psdev;

	dev_dbg(&dev->dev, "xen_pcibk_error_resume(bus:%x,devfn:%x)\n",
		dev->bus->number, dev->devfn);

	करोwn_ग_लिखो(&pcistub_sem);
	psdev = pcistub_device_find(pci_करोमुख्य_nr(dev->bus),
				dev->bus->number,
				PCI_SLOT(dev->devfn),
				PCI_FUNC(dev->devfn));

	अगर (!psdev || !psdev->pdev) अणु
		dev_err(&dev->dev, "device is not found/assigned\n");
		जाओ end;
	पूर्ण

	अगर (!psdev->pdev->sh_info) अणु
		dev_err(&dev->dev, "device is not connected or owned"
			" by HVM, kill it\n");
		समाप्त_करोमुख्य_by_device(psdev);
		जाओ end;
	पूर्ण

	अगर (!test_bit(_XEN_PCIB_AERHANDLER,
		(अचिन्हित दीर्घ *)&psdev->pdev->sh_info->flags)) अणु
		dev_err(&dev->dev,
			"guest with no AER driver should have been killed\n");
		समाप्त_करोमुख्य_by_device(psdev);
		जाओ end;
	पूर्ण
	common_process(psdev, pci_channel_io_normal, XEN_PCI_OP_aer_resume,
		       PCI_ERS_RESULT_RECOVERED);
end:
	अगर (psdev)
		pcistub_device_put(psdev);
	up_ग_लिखो(&pcistub_sem);
	वापस;
पूर्ण

/*add xen_pcibk AER handling*/
अटल स्थिर काष्ठा pci_error_handlers xen_pcibk_error_handler = अणु
	.error_detected = xen_pcibk_error_detected,
	.mmio_enabled = xen_pcibk_mmio_enabled,
	.slot_reset = xen_pcibk_slot_reset,
	.resume = xen_pcibk_error_resume,
पूर्ण;

/*
 * Note: There is no MODULE_DEVICE_TABLE entry here because this isn't
 * क्रम a normal device. I करोn't want it to be loaded स्वतःmatically.
 */

अटल काष्ठा pci_driver xen_pcibk_pci_driver = अणु
	/* The name should be xen_pciback, but until the tools are updated
	 * we will keep it as pciback. */
	.name = PCISTUB_DRIVER_NAME,
	.id_table = pcistub_ids,
	.probe = pcistub_probe,
	.हटाओ = pcistub_हटाओ,
	.err_handler = &xen_pcibk_error_handler,
पूर्ण;

अटल अंतरभूत पूर्णांक str_to_slot(स्थिर अक्षर *buf, पूर्णांक *करोमुख्य, पूर्णांक *bus,
			      पूर्णांक *slot, पूर्णांक *func)
अणु
	पूर्णांक parsed = 0;

	चयन (माला_पूछो(buf, " %x:%x:%x.%x %n", करोमुख्य, bus, slot, func,
		       &parsed)) अणु
	हाल 3:
		*func = -1;
		माला_पूछो(buf, " %x:%x:%x.* %n", करोमुख्य, bus, slot, &parsed);
		अवरोध;
	हाल 2:
		*slot = *func = -1;
		माला_पूछो(buf, " %x:%x:*.* %n", करोमुख्य, bus, &parsed);
		अवरोध;
	पूर्ण
	अगर (parsed && !buf[parsed])
		वापस 0;

	/* try again without करोमुख्य */
	*करोमुख्य = 0;
	चयन (माला_पूछो(buf, " %x:%x.%x %n", bus, slot, func, &parsed)) अणु
	हाल 2:
		*func = -1;
		माला_पूछो(buf, " %x:%x.* %n", bus, slot, &parsed);
		अवरोध;
	हाल 1:
		*slot = *func = -1;
		माला_पूछो(buf, " %x:*.* %n", bus, &parsed);
		अवरोध;
	पूर्ण
	अगर (parsed && !buf[parsed])
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक str_to_quirk(स्थिर अक्षर *buf, पूर्णांक *करोमुख्य, पूर्णांक *bus, पूर्णांक
			       *slot, पूर्णांक *func, पूर्णांक *reg, पूर्णांक *size, पूर्णांक *mask)
अणु
	पूर्णांक parsed = 0;

	माला_पूछो(buf, " %x:%x:%x.%x-%x:%x:%x %n", करोमुख्य, bus, slot, func,
	       reg, size, mask, &parsed);
	अगर (parsed && !buf[parsed])
		वापस 0;

	/* try again without करोमुख्य */
	*करोमुख्य = 0;
	माला_पूछो(buf, " %x:%x.%x-%x:%x:%x %n", bus, slot, func, reg, size,
	       mask, &parsed);
	अगर (parsed && !buf[parsed])
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pcistub_device_id_add(पूर्णांक करोमुख्य, पूर्णांक bus, पूर्णांक slot, पूर्णांक func)
अणु
	काष्ठा pcistub_device_id *pci_dev_id;
	पूर्णांक rc = 0, devfn = PCI_DEVFN(slot, func);

	अगर (slot < 0) अणु
		क्रम (slot = 0; !rc && slot < 32; ++slot)
			rc = pcistub_device_id_add(करोमुख्य, bus, slot, func);
		वापस rc;
	पूर्ण

	अगर (func < 0) अणु
		क्रम (func = 0; !rc && func < 8; ++func)
			rc = pcistub_device_id_add(करोमुख्य, bus, slot, func);
		वापस rc;
	पूर्ण

	अगर ((
#अगर !defined(MODULE) /* pci_करोमुख्यs_supported is not being exported */ \
    || !defined(CONFIG_PCI_DOMAINS)
	     !pci_करोमुख्यs_supported ? करोमुख्य :
#पूर्ण_अगर
	     करोमुख्य < 0 || करोमुख्य > 0xffff)
	    || bus < 0 || bus > 0xff
	    || PCI_SLOT(devfn) != slot
	    || PCI_FUNC(devfn) != func)
		वापस -EINVAL;

	pci_dev_id = kदो_स्मृति(माप(*pci_dev_id), GFP_KERNEL);
	अगर (!pci_dev_id)
		वापस -ENOMEM;

	pr_debug("wants to seize %04x:%02x:%02x.%d\n",
		 करोमुख्य, bus, slot, func);

	pcistub_device_id_add_list(pci_dev_id, करोमुख्य, bus, devfn);

	वापस 0;
पूर्ण

अटल पूर्णांक pcistub_device_id_हटाओ(पूर्णांक करोमुख्य, पूर्णांक bus, पूर्णांक slot, पूर्णांक func)
अणु
	काष्ठा pcistub_device_id *pci_dev_id, *t;
	पूर्णांक err = -ENOENT;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device_ids_lock, flags);
	list_क्रम_each_entry_safe(pci_dev_id, t, &pcistub_device_ids,
				 slot_list) अणु
		अगर (pci_dev_id->करोमुख्य == करोमुख्य && pci_dev_id->bus == bus
		    && (slot < 0 || PCI_SLOT(pci_dev_id->devfn) == slot)
		    && (func < 0 || PCI_FUNC(pci_dev_id->devfn) == func)) अणु
			/* Don't break; here because it's possible the same
			 * slot could be in the list more than once
			 */
			list_del(&pci_dev_id->slot_list);
			kमुक्त(pci_dev_id);

			err = 0;

			pr_debug("removed %04x:%02x:%02x.%d from seize list\n",
				 करोमुख्य, bus, slot, func);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&device_ids_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक pcistub_reg_add(पूर्णांक करोमुख्य, पूर्णांक bus, पूर्णांक slot, पूर्णांक func,
			   अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक size,
			   अचिन्हित पूर्णांक mask)
अणु
	पूर्णांक err = 0;
	काष्ठा pcistub_device *psdev;
	काष्ठा pci_dev *dev;
	काष्ठा config_field *field;

	अगर (reg > 0xfff || (size < 4 && (mask >> (size * 8))))
		वापस -EINVAL;

	psdev = pcistub_device_find(करोमुख्य, bus, slot, func);
	अगर (!psdev) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण
	dev = psdev->dev;

	field = kzalloc(माप(*field), GFP_KERNEL);
	अगर (!field) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	field->offset = reg;
	field->size = size;
	field->mask = mask;
	field->init = शून्य;
	field->reset = शून्य;
	field->release = शून्य;
	field->clean = xen_pcibk_config_field_मुक्त;

	err = xen_pcibk_config_quirks_add_field(dev, field);
	अगर (err)
		kमुक्त(field);
out:
	अगर (psdev)
		pcistub_device_put(psdev);
	वापस err;
पूर्ण

अटल sमाप_प्रकार new_slot_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक करोमुख्य, bus, slot, func;
	पूर्णांक err;

	err = str_to_slot(buf, &करोमुख्य, &bus, &slot, &func);
	अगर (err)
		जाओ out;

	err = pcistub_device_id_add(करोमुख्य, bus, slot, func);

out:
	अगर (!err)
		err = count;
	वापस err;
पूर्ण
अटल DRIVER_ATTR_WO(new_slot);

अटल sमाप_प्रकार हटाओ_slot_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	पूर्णांक करोमुख्य, bus, slot, func;
	पूर्णांक err;

	err = str_to_slot(buf, &करोमुख्य, &bus, &slot, &func);
	अगर (err)
		जाओ out;

	err = pcistub_device_id_हटाओ(करोमुख्य, bus, slot, func);

out:
	अगर (!err)
		err = count;
	वापस err;
पूर्ण
अटल DRIVER_ATTR_WO(हटाओ_slot);

अटल sमाप_प्रकार slots_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	काष्ठा pcistub_device_id *pci_dev_id;
	माप_प्रकार count = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device_ids_lock, flags);
	list_क्रम_each_entry(pci_dev_id, &pcistub_device_ids, slot_list) अणु
		अगर (count >= PAGE_SIZE)
			अवरोध;

		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "%04x:%02x:%02x.%d\n",
				   pci_dev_id->करोमुख्य, pci_dev_id->bus,
				   PCI_SLOT(pci_dev_id->devfn),
				   PCI_FUNC(pci_dev_id->devfn));
	पूर्ण
	spin_unlock_irqrestore(&device_ids_lock, flags);

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RO(slots);

अटल sमाप_प्रकार irq_handlers_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	काष्ठा pcistub_device *psdev;
	काष्ठा xen_pcibk_dev_data *dev_data;
	माप_प्रकार count = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pcistub_devices_lock, flags);
	list_क्रम_each_entry(psdev, &pcistub_devices, dev_list) अणु
		अगर (count >= PAGE_SIZE)
			अवरोध;
		अगर (!psdev->dev)
			जारी;
		dev_data = pci_get_drvdata(psdev->dev);
		अगर (!dev_data)
			जारी;
		count +=
		    scnम_लिखो(buf + count, PAGE_SIZE - count,
			      "%s:%s:%sing:%ld\n",
			      pci_name(psdev->dev),
			      dev_data->isr_on ? "on" : "off",
			      dev_data->ack_पूर्णांकr ? "ack" : "not ack",
			      dev_data->handled);
	पूर्ण
	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RO(irq_handlers);

अटल sमाप_प्रकार irq_handler_state_store(काष्ठा device_driver *drv,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcistub_device *psdev;
	काष्ठा xen_pcibk_dev_data *dev_data;
	पूर्णांक करोमुख्य, bus, slot, func;
	पूर्णांक err;

	err = str_to_slot(buf, &करोमुख्य, &bus, &slot, &func);
	अगर (err)
		वापस err;

	psdev = pcistub_device_find(करोमुख्य, bus, slot, func);
	अगर (!psdev) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	dev_data = pci_get_drvdata(psdev->dev);
	अगर (!dev_data) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	dev_dbg(&psdev->dev->dev, "%s fake irq handler: %d->%d\n",
		dev_data->irq_name, dev_data->isr_on,
		!dev_data->isr_on);

	dev_data->isr_on = !(dev_data->isr_on);
	अगर (dev_data->isr_on)
		dev_data->ack_पूर्णांकr = 1;
out:
	अगर (psdev)
		pcistub_device_put(psdev);
	अगर (!err)
		err = count;
	वापस err;
पूर्ण
अटल DRIVER_ATTR_WO(irq_handler_state);

अटल sमाप_प्रकार quirks_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक करोमुख्य, bus, slot, func, reg, size, mask;
	पूर्णांक err;

	err = str_to_quirk(buf, &करोमुख्य, &bus, &slot, &func, &reg, &size,
			   &mask);
	अगर (err)
		जाओ out;

	err = pcistub_reg_add(करोमुख्य, bus, slot, func, reg, size, mask);

out:
	अगर (!err)
		err = count;
	वापस err;
पूर्ण

अटल sमाप_प्रकार quirks_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा xen_pcibk_config_quirk *quirk;
	काष्ठा xen_pcibk_dev_data *dev_data;
	स्थिर काष्ठा config_field *field;
	स्थिर काष्ठा config_field_entry *cfg_entry;

	spin_lock_irqsave(&device_ids_lock, flags);
	list_क्रम_each_entry(quirk, &xen_pcibk_quirks, quirks_list) अणु
		अगर (count >= PAGE_SIZE)
			जाओ out;

		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "%02x:%02x.%01x\n\t%04x:%04x:%04x:%04x\n",
				   quirk->pdev->bus->number,
				   PCI_SLOT(quirk->pdev->devfn),
				   PCI_FUNC(quirk->pdev->devfn),
				   quirk->devid.venकरोr, quirk->devid.device,
				   quirk->devid.subvenकरोr,
				   quirk->devid.subdevice);

		dev_data = pci_get_drvdata(quirk->pdev);

		list_क्रम_each_entry(cfg_entry, &dev_data->config_fields, list) अणु
			field = cfg_entry->field;
			अगर (count >= PAGE_SIZE)
				जाओ out;

			count += scnम_लिखो(buf + count, PAGE_SIZE - count,
					   "\t\t%08x:%01x:%08x\n",
					   cfg_entry->base_offset +
					   field->offset, field->size,
					   field->mask);
		पूर्ण
	पूर्ण

out:
	spin_unlock_irqrestore(&device_ids_lock, flags);

	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(quirks);

अटल sमाप_प्रकार permissive_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	पूर्णांक करोमुख्य, bus, slot, func;
	पूर्णांक err;
	काष्ठा pcistub_device *psdev;
	काष्ठा xen_pcibk_dev_data *dev_data;

	err = str_to_slot(buf, &करोमुख्य, &bus, &slot, &func);
	अगर (err)
		जाओ out;

	psdev = pcistub_device_find(करोमुख्य, bus, slot, func);
	अगर (!psdev) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	dev_data = pci_get_drvdata(psdev->dev);
	/* the driver data क्रम a device should never be null at this poपूर्णांक */
	अगर (!dev_data) अणु
		err = -ENXIO;
		जाओ release;
	पूर्ण
	अगर (!dev_data->permissive) अणु
		dev_data->permissive = 1;
		/* Let user know that what they're करोing could be unsafe */
		dev_warn(&psdev->dev->dev, "enabling permissive mode "
			 "configuration space accesses!\n");
		dev_warn(&psdev->dev->dev,
			 "permissive mode is potentially unsafe!\n");
	पूर्ण
release:
	pcistub_device_put(psdev);
out:
	अगर (!err)
		err = count;
	वापस err;
पूर्ण

अटल sमाप_प्रकार permissive_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	काष्ठा pcistub_device *psdev;
	काष्ठा xen_pcibk_dev_data *dev_data;
	माप_प्रकार count = 0;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&pcistub_devices_lock, flags);
	list_क्रम_each_entry(psdev, &pcistub_devices, dev_list) अणु
		अगर (count >= PAGE_SIZE)
			अवरोध;
		अगर (!psdev->dev)
			जारी;
		dev_data = pci_get_drvdata(psdev->dev);
		अगर (!dev_data || !dev_data->permissive)
			जारी;
		count +=
		    scnम_लिखो(buf + count, PAGE_SIZE - count, "%s\n",
			      pci_name(psdev->dev));
	पूर्ण
	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(permissive);

अटल sमाप_प्रकार allow_पूर्णांकerrupt_control_store(काष्ठा device_driver *drv,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक करोमुख्य, bus, slot, func;
	पूर्णांक err;
	काष्ठा pcistub_device *psdev;
	काष्ठा xen_pcibk_dev_data *dev_data;

	err = str_to_slot(buf, &करोमुख्य, &bus, &slot, &func);
	अगर (err)
		जाओ out;

	psdev = pcistub_device_find(करोमुख्य, bus, slot, func);
	अगर (!psdev) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	dev_data = pci_get_drvdata(psdev->dev);
	/* the driver data क्रम a device should never be null at this poपूर्णांक */
	अगर (!dev_data) अणु
		err = -ENXIO;
		जाओ release;
	पूर्ण
	dev_data->allow_पूर्णांकerrupt_control = 1;
release:
	pcistub_device_put(psdev);
out:
	अगर (!err)
		err = count;
	वापस err;
पूर्ण

अटल sमाप_प्रकार allow_पूर्णांकerrupt_control_show(काष्ठा device_driver *drv,
					    अक्षर *buf)
अणु
	काष्ठा pcistub_device *psdev;
	काष्ठा xen_pcibk_dev_data *dev_data;
	माप_प्रकार count = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pcistub_devices_lock, flags);
	list_क्रम_each_entry(psdev, &pcistub_devices, dev_list) अणु
		अगर (count >= PAGE_SIZE)
			अवरोध;
		अगर (!psdev->dev)
			जारी;
		dev_data = pci_get_drvdata(psdev->dev);
		अगर (!dev_data || !dev_data->allow_पूर्णांकerrupt_control)
			जारी;
		count +=
		    scnम_लिखो(buf + count, PAGE_SIZE - count, "%s\n",
			      pci_name(psdev->dev));
	पूर्ण
	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	वापस count;
पूर्ण
अटल DRIVER_ATTR_RW(allow_पूर्णांकerrupt_control);

अटल व्योम pcistub_निकास(व्योम)
अणु
	driver_हटाओ_file(&xen_pcibk_pci_driver.driver, &driver_attr_new_slot);
	driver_हटाओ_file(&xen_pcibk_pci_driver.driver,
			   &driver_attr_हटाओ_slot);
	driver_हटाओ_file(&xen_pcibk_pci_driver.driver, &driver_attr_slots);
	driver_हटाओ_file(&xen_pcibk_pci_driver.driver, &driver_attr_quirks);
	driver_हटाओ_file(&xen_pcibk_pci_driver.driver,
			   &driver_attr_permissive);
	driver_हटाओ_file(&xen_pcibk_pci_driver.driver,
			   &driver_attr_allow_पूर्णांकerrupt_control);
	driver_हटाओ_file(&xen_pcibk_pci_driver.driver,
			   &driver_attr_irq_handlers);
	driver_हटाओ_file(&xen_pcibk_pci_driver.driver,
			   &driver_attr_irq_handler_state);
	pci_unरेजिस्टर_driver(&xen_pcibk_pci_driver);
पूर्ण

अटल पूर्णांक __init pcistub_init(व्योम)
अणु
	पूर्णांक pos = 0;
	पूर्णांक err = 0;
	पूर्णांक करोमुख्य, bus, slot, func;
	पूर्णांक parsed;

	अगर (pci_devs_to_hide && *pci_devs_to_hide) अणु
		करो अणु
			parsed = 0;

			err = माला_पूछो(pci_devs_to_hide + pos,
				     " (%x:%x:%x.%x) %n",
				     &करोमुख्य, &bus, &slot, &func, &parsed);
			चयन (err) अणु
			हाल 3:
				func = -1;
				माला_पूछो(pci_devs_to_hide + pos,
				       " (%x:%x:%x.*) %n",
				       &करोमुख्य, &bus, &slot, &parsed);
				अवरोध;
			हाल 2:
				slot = func = -1;
				माला_पूछो(pci_devs_to_hide + pos,
				       " (%x:%x:*.*) %n",
				       &करोमुख्य, &bus, &parsed);
				अवरोध;
			पूर्ण

			अगर (!parsed) अणु
				करोमुख्य = 0;
				err = माला_पूछो(pci_devs_to_hide + pos,
					     " (%x:%x.%x) %n",
					     &bus, &slot, &func, &parsed);
				चयन (err) अणु
				हाल 2:
					func = -1;
					माला_पूछो(pci_devs_to_hide + pos,
					       " (%x:%x.*) %n",
					       &bus, &slot, &parsed);
					अवरोध;
				हाल 1:
					slot = func = -1;
					माला_पूछो(pci_devs_to_hide + pos,
					       " (%x:*.*) %n",
					       &bus, &parsed);
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (parsed <= 0)
				जाओ parse_error;

			err = pcistub_device_id_add(करोमुख्य, bus, slot, func);
			अगर (err)
				जाओ out;

			pos += parsed;
		पूर्ण जबतक (pci_devs_to_hide[pos]);
	पूर्ण

	/* If we're the first PCI Device Driver to register, we're the
	 * first one to get offered PCI devices as they become
	 * available (and thus we can be the first to grab them)
	 */
	err = pci_रेजिस्टर_driver(&xen_pcibk_pci_driver);
	अगर (err < 0)
		जाओ out;

	err = driver_create_file(&xen_pcibk_pci_driver.driver,
				 &driver_attr_new_slot);
	अगर (!err)
		err = driver_create_file(&xen_pcibk_pci_driver.driver,
					 &driver_attr_हटाओ_slot);
	अगर (!err)
		err = driver_create_file(&xen_pcibk_pci_driver.driver,
					 &driver_attr_slots);
	अगर (!err)
		err = driver_create_file(&xen_pcibk_pci_driver.driver,
					 &driver_attr_quirks);
	अगर (!err)
		err = driver_create_file(&xen_pcibk_pci_driver.driver,
					 &driver_attr_permissive);
	अगर (!err)
		err = driver_create_file(&xen_pcibk_pci_driver.driver,
					 &driver_attr_allow_पूर्णांकerrupt_control);

	अगर (!err)
		err = driver_create_file(&xen_pcibk_pci_driver.driver,
					 &driver_attr_irq_handlers);
	अगर (!err)
		err = driver_create_file(&xen_pcibk_pci_driver.driver,
					&driver_attr_irq_handler_state);
	अगर (err)
		pcistub_निकास();

out:
	वापस err;

parse_error:
	pr_err("Error parsing pci_devs_to_hide at \"%s\"\n",
	       pci_devs_to_hide + pos);
	वापस -EINVAL;
पूर्ण

#अगर_अघोषित MODULE
/*
 * fs_initcall happens beक्रमe device_initcall
 * so xen_pcibk *should* get called first (b/c we
 * want to suck up any device beक्रमe other drivers
 * get a chance by being the first pci device
 * driver to रेजिस्टर)
 */
fs_initcall(pcistub_init);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_IOV
अटल काष्ठा pcistub_device *find_vfs(स्थिर काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcistub_device *psdev = शून्य;
	अचिन्हित दीर्घ flags;
	bool found = false;

	spin_lock_irqsave(&pcistub_devices_lock, flags);
	list_क्रम_each_entry(psdev, &pcistub_devices, dev_list) अणु
		अगर (!psdev->pdev && psdev->dev != pdev
		    && pci_physfn(psdev->dev) == pdev) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	अगर (found)
		वापस psdev;
	वापस शून्य;
पूर्ण

अटल पूर्णांक pci_stub_notअगरier(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;
	स्थिर काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (action != BUS_NOTIFY_UNBIND_DRIVER)
		वापस NOTIFY_DONE;

	अगर (!pdev->is_physfn)
		वापस NOTIFY_DONE;

	क्रम (;;) अणु
		काष्ठा pcistub_device *psdev = find_vfs(pdev);
		अगर (!psdev)
			अवरोध;
		device_release_driver(&psdev->dev->dev);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block pci_stub_nb = अणु
	.notअगरier_call = pci_stub_notअगरier,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init xen_pcibk_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!xen_initial_करोमुख्य())
		वापस -ENODEV;

	err = xen_pcibk_config_init();
	अगर (err)
		वापस err;

#अगर_घोषित MODULE
	err = pcistub_init();
	अगर (err < 0)
		वापस err;
#पूर्ण_अगर

	pcistub_init_devices_late();
	err = xen_pcibk_xenbus_रेजिस्टर();
	अगर (err)
		pcistub_निकास();
#अगर_घोषित CONFIG_PCI_IOV
	अन्यथा
		bus_रेजिस्टर_notअगरier(&pci_bus_type, &pci_stub_nb);
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल व्योम __निकास xen_pcibk_cleanup(व्योम)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	bus_unरेजिस्टर_notअगरier(&pci_bus_type, &pci_stub_nb);
#पूर्ण_अगर
	xen_pcibk_xenbus_unरेजिस्टर();
	pcistub_निकास();
पूर्ण

module_init(xen_pcibk_init);
module_निकास(xen_pcibk_cleanup);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("xen-backend:pci");
