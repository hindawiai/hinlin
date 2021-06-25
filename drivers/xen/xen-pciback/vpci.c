<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Backend - Provides a Virtual PCI bus (with real devices)
 *               to the frontend
 *
 *   Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#घोषणा dev_fmt pr_fmt

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>
#समावेश "pciback.h"

#घोषणा PCI_SLOT_MAX 32

काष्ठा vpci_dev_data अणु
	/* Access to dev_list must be रक्षित by lock */
	काष्ठा list_head dev_list[PCI_SLOT_MAX];
	काष्ठा mutex lock;
पूर्ण;

अटल अंतरभूत काष्ठा list_head *list_first(काष्ठा list_head *head)
अणु
	वापस head->next;
पूर्ण

अटल काष्ठा pci_dev *__xen_pcibk_get_pci_dev(काष्ठा xen_pcibk_device *pdev,
					       अचिन्हित पूर्णांक करोमुख्य,
					       अचिन्हित पूर्णांक bus,
					       अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा pci_dev_entry *entry;
	काष्ठा pci_dev *dev = शून्य;
	काष्ठा vpci_dev_data *vpci_dev = pdev->pci_dev_data;

	अगर (करोमुख्य != 0 || bus != 0)
		वापस शून्य;

	अगर (PCI_SLOT(devfn) < PCI_SLOT_MAX) अणु
		mutex_lock(&vpci_dev->lock);

		list_क्रम_each_entry(entry,
				    &vpci_dev->dev_list[PCI_SLOT(devfn)],
				    list) अणु
			अगर (PCI_FUNC(entry->dev->devfn) == PCI_FUNC(devfn)) अणु
				dev = entry->dev;
				अवरोध;
			पूर्ण
		पूर्ण

		mutex_unlock(&vpci_dev->lock);
	पूर्ण
	वापस dev;
पूर्ण

अटल अंतरभूत पूर्णांक match_slot(काष्ठा pci_dev *l, काष्ठा pci_dev *r)
अणु
	अगर (pci_करोमुख्य_nr(l->bus) == pci_करोमुख्य_nr(r->bus)
	    && l->bus == r->bus && PCI_SLOT(l->devfn) == PCI_SLOT(r->devfn))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक __xen_pcibk_add_pci_dev(काष्ठा xen_pcibk_device *pdev,
				   काष्ठा pci_dev *dev, पूर्णांक devid,
				   publish_pci_dev_cb publish_cb)
अणु
	पूर्णांक err = 0, slot, func = PCI_FUNC(dev->devfn);
	काष्ठा pci_dev_entry *t, *dev_entry;
	काष्ठा vpci_dev_data *vpci_dev = pdev->pci_dev_data;

	अगर ((dev->class >> 24) == PCI_BASE_CLASS_BRIDGE) अणु
		err = -EFAULT;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Can't export bridges on the virtual PCI bus");
		जाओ out;
	पूर्ण

	dev_entry = kदो_स्मृति(माप(*dev_entry), GFP_KERNEL);
	अगर (!dev_entry) अणु
		err = -ENOMEM;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error adding entry to virtual PCI bus");
		जाओ out;
	पूर्ण

	dev_entry->dev = dev;

	mutex_lock(&vpci_dev->lock);

	/*
	 * Keep multi-function devices together on the भव PCI bus, except
	 * that we want to keep भव functions at func 0 on their own. They
	 * aren't multi-function devices and hence their presence at func 0
	 * may cause guests to not scan the other functions.
	 */
	अगर (!dev->is_virtfn || func) अणु
		क्रम (slot = 0; slot < PCI_SLOT_MAX; slot++) अणु
			अगर (list_empty(&vpci_dev->dev_list[slot]))
				जारी;

			t = list_entry(list_first(&vpci_dev->dev_list[slot]),
				       काष्ठा pci_dev_entry, list);
			अगर (t->dev->is_virtfn && !PCI_FUNC(t->dev->devfn))
				जारी;

			अगर (match_slot(dev, t->dev)) अणु
				dev_info(&dev->dev, "vpci: assign to virtual slot %d func %d\n",
					 slot, func);
				list_add_tail(&dev_entry->list,
					      &vpci_dev->dev_list[slot]);
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Assign to a new slot on the भव PCI bus */
	क्रम (slot = 0; slot < PCI_SLOT_MAX; slot++) अणु
		अगर (list_empty(&vpci_dev->dev_list[slot])) अणु
			dev_info(&dev->dev, "vpci: assign to virtual slot %d\n",
				 slot);
			list_add_tail(&dev_entry->list,
				      &vpci_dev->dev_list[slot]);
			जाओ unlock;
		पूर्ण
	पूर्ण

	err = -ENOMEM;
	xenbus_dev_fatal(pdev->xdev, err,
			 "No more space on root virtual PCI bus");

unlock:
	mutex_unlock(&vpci_dev->lock);

	/* Publish this device. */
	अगर (!err)
		err = publish_cb(pdev, 0, 0, PCI_DEVFN(slot, func), devid);
	अन्यथा
		kमुक्त(dev_entry);

out:
	वापस err;
पूर्ण

अटल व्योम __xen_pcibk_release_pci_dev(काष्ठा xen_pcibk_device *pdev,
					काष्ठा pci_dev *dev, bool lock)
अणु
	पूर्णांक slot;
	काष्ठा vpci_dev_data *vpci_dev = pdev->pci_dev_data;
	काष्ठा pci_dev *found_dev = शून्य;

	mutex_lock(&vpci_dev->lock);

	क्रम (slot = 0; slot < PCI_SLOT_MAX; slot++) अणु
		काष्ठा pci_dev_entry *e;

		list_क्रम_each_entry(e, &vpci_dev->dev_list[slot], list) अणु
			अगर (e->dev == dev) अणु
				list_del(&e->list);
				found_dev = e->dev;
				kमुक्त(e);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&vpci_dev->lock);

	अगर (found_dev) अणु
		अगर (lock)
			device_lock(&found_dev->dev);
		pcistub_put_pci_dev(found_dev);
		अगर (lock)
			device_unlock(&found_dev->dev);
	पूर्ण
पूर्ण

अटल पूर्णांक __xen_pcibk_init_devices(काष्ठा xen_pcibk_device *pdev)
अणु
	पूर्णांक slot;
	काष्ठा vpci_dev_data *vpci_dev;

	vpci_dev = kदो_स्मृति(माप(*vpci_dev), GFP_KERNEL);
	अगर (!vpci_dev)
		वापस -ENOMEM;

	mutex_init(&vpci_dev->lock);

	क्रम (slot = 0; slot < PCI_SLOT_MAX; slot++)
		INIT_LIST_HEAD(&vpci_dev->dev_list[slot]);

	pdev->pci_dev_data = vpci_dev;

	वापस 0;
पूर्ण

अटल पूर्णांक __xen_pcibk_publish_pci_roots(काष्ठा xen_pcibk_device *pdev,
					 publish_pci_root_cb publish_cb)
अणु
	/* The Virtual PCI bus has only one root */
	वापस publish_cb(pdev, 0, 0);
पूर्ण

अटल व्योम __xen_pcibk_release_devices(काष्ठा xen_pcibk_device *pdev)
अणु
	पूर्णांक slot;
	काष्ठा vpci_dev_data *vpci_dev = pdev->pci_dev_data;

	क्रम (slot = 0; slot < PCI_SLOT_MAX; slot++) अणु
		काष्ठा pci_dev_entry *e, *पंचांगp;
		list_क्रम_each_entry_safe(e, पंचांगp, &vpci_dev->dev_list[slot],
					 list) अणु
			काष्ठा pci_dev *dev = e->dev;
			list_del(&e->list);
			device_lock(&dev->dev);
			pcistub_put_pci_dev(dev);
			device_unlock(&dev->dev);
			kमुक्त(e);
		पूर्ण
	पूर्ण

	kमुक्त(vpci_dev);
	pdev->pci_dev_data = शून्य;
पूर्ण

अटल पूर्णांक __xen_pcibk_get_pcअगरront_dev(काष्ठा pci_dev *pcidev,
					काष्ठा xen_pcibk_device *pdev,
					अचिन्हित पूर्णांक *करोमुख्य, अचिन्हित पूर्णांक *bus,
					अचिन्हित पूर्णांक *devfn)
अणु
	काष्ठा pci_dev_entry *entry;
	काष्ठा vpci_dev_data *vpci_dev = pdev->pci_dev_data;
	पूर्णांक found = 0, slot;

	mutex_lock(&vpci_dev->lock);
	क्रम (slot = 0; slot < PCI_SLOT_MAX; slot++) अणु
		list_क्रम_each_entry(entry,
			    &vpci_dev->dev_list[slot],
			    list) अणु
			अगर (entry->dev == pcidev) अणु
				found = 1;
				*करोमुख्य = 0;
				*bus = 0;
				*devfn = PCI_DEVFN(slot,
					 PCI_FUNC(pcidev->devfn));
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&vpci_dev->lock);
	वापस found;
पूर्ण

स्थिर काष्ठा xen_pcibk_backend xen_pcibk_vpci_backend = अणु
	.name		= "vpci",
	.init		= __xen_pcibk_init_devices,
	.मुक्त		= __xen_pcibk_release_devices,
	.find		= __xen_pcibk_get_pcअगरront_dev,
	.publish	= __xen_pcibk_publish_pci_roots,
	.release	= __xen_pcibk_release_pci_dev,
	.add		= __xen_pcibk_add_pci_dev,
	.get		= __xen_pcibk_get_pci_dev,
पूर्ण;
