<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Backend - Provides restricted access to the real PCI bus topology
 *               to the frontend
 *
 *   Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */

#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>
#समावेश "pciback.h"

काष्ठा passthrough_dev_data अणु
	/* Access to dev_list must be रक्षित by lock */
	काष्ठा list_head dev_list;
	काष्ठा mutex lock;
पूर्ण;

अटल काष्ठा pci_dev *__xen_pcibk_get_pci_dev(काष्ठा xen_pcibk_device *pdev,
					       अचिन्हित पूर्णांक करोमुख्य,
					       अचिन्हित पूर्णांक bus,
					       अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा passthrough_dev_data *dev_data = pdev->pci_dev_data;
	काष्ठा pci_dev_entry *dev_entry;
	काष्ठा pci_dev *dev = शून्य;

	mutex_lock(&dev_data->lock);

	list_क्रम_each_entry(dev_entry, &dev_data->dev_list, list) अणु
		अगर (करोमुख्य == (अचिन्हित पूर्णांक)pci_करोमुख्य_nr(dev_entry->dev->bus)
		    && bus == (अचिन्हित पूर्णांक)dev_entry->dev->bus->number
		    && devfn == dev_entry->dev->devfn) अणु
			dev = dev_entry->dev;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&dev_data->lock);

	वापस dev;
पूर्ण

अटल पूर्णांक __xen_pcibk_add_pci_dev(काष्ठा xen_pcibk_device *pdev,
				   काष्ठा pci_dev *dev,
				   पूर्णांक devid, publish_pci_dev_cb publish_cb)
अणु
	काष्ठा passthrough_dev_data *dev_data = pdev->pci_dev_data;
	काष्ठा pci_dev_entry *dev_entry;
	अचिन्हित पूर्णांक करोमुख्य, bus, devfn;
	पूर्णांक err;

	dev_entry = kदो_स्मृति(माप(*dev_entry), GFP_KERNEL);
	अगर (!dev_entry)
		वापस -ENOMEM;
	dev_entry->dev = dev;

	mutex_lock(&dev_data->lock);
	list_add_tail(&dev_entry->list, &dev_data->dev_list);
	mutex_unlock(&dev_data->lock);

	/* Publish this device. */
	करोमुख्य = (अचिन्हित पूर्णांक)pci_करोमुख्य_nr(dev->bus);
	bus = (अचिन्हित पूर्णांक)dev->bus->number;
	devfn = dev->devfn;
	err = publish_cb(pdev, करोमुख्य, bus, devfn, devid);

	वापस err;
पूर्ण

अटल व्योम __xen_pcibk_release_pci_dev(काष्ठा xen_pcibk_device *pdev,
					काष्ठा pci_dev *dev, bool lock)
अणु
	काष्ठा passthrough_dev_data *dev_data = pdev->pci_dev_data;
	काष्ठा pci_dev_entry *dev_entry, *t;
	काष्ठा pci_dev *found_dev = शून्य;

	mutex_lock(&dev_data->lock);

	list_क्रम_each_entry_safe(dev_entry, t, &dev_data->dev_list, list) अणु
		अगर (dev_entry->dev == dev) अणु
			list_del(&dev_entry->list);
			found_dev = dev_entry->dev;
			kमुक्त(dev_entry);
		पूर्ण
	पूर्ण

	mutex_unlock(&dev_data->lock);

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
	काष्ठा passthrough_dev_data *dev_data;

	dev_data = kदो_स्मृति(माप(*dev_data), GFP_KERNEL);
	अगर (!dev_data)
		वापस -ENOMEM;

	mutex_init(&dev_data->lock);

	INIT_LIST_HEAD(&dev_data->dev_list);

	pdev->pci_dev_data = dev_data;

	वापस 0;
पूर्ण

अटल पूर्णांक __xen_pcibk_publish_pci_roots(काष्ठा xen_pcibk_device *pdev,
					 publish_pci_root_cb publish_root_cb)
अणु
	पूर्णांक err = 0;
	काष्ठा passthrough_dev_data *dev_data = pdev->pci_dev_data;
	काष्ठा pci_dev_entry *dev_entry, *e;
	काष्ठा pci_dev *dev;
	पूर्णांक found;
	अचिन्हित पूर्णांक करोमुख्य, bus;

	mutex_lock(&dev_data->lock);

	list_क्रम_each_entry(dev_entry, &dev_data->dev_list, list) अणु
		/* Only publish this device as a root अगर none of its
		 * parent bridges are exported
		 */
		found = 0;
		dev = dev_entry->dev->bus->self;
		क्रम (; !found && dev != शून्य; dev = dev->bus->self) अणु
			list_क्रम_each_entry(e, &dev_data->dev_list, list) अणु
				अगर (dev == e->dev) अणु
					found = 1;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		करोमुख्य = (अचिन्हित पूर्णांक)pci_करोमुख्य_nr(dev_entry->dev->bus);
		bus = (अचिन्हित पूर्णांक)dev_entry->dev->bus->number;

		अगर (!found) अणु
			err = publish_root_cb(pdev, करोमुख्य, bus);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&dev_data->lock);

	वापस err;
पूर्ण

अटल व्योम __xen_pcibk_release_devices(काष्ठा xen_pcibk_device *pdev)
अणु
	काष्ठा passthrough_dev_data *dev_data = pdev->pci_dev_data;
	काष्ठा pci_dev_entry *dev_entry, *t;

	list_क्रम_each_entry_safe(dev_entry, t, &dev_data->dev_list, list) अणु
		काष्ठा pci_dev *dev = dev_entry->dev;
		list_del(&dev_entry->list);
		device_lock(&dev->dev);
		pcistub_put_pci_dev(dev);
		device_unlock(&dev->dev);
		kमुक्त(dev_entry);
	पूर्ण

	kमुक्त(dev_data);
	pdev->pci_dev_data = शून्य;
पूर्ण

अटल पूर्णांक __xen_pcibk_get_pcअगरront_dev(काष्ठा pci_dev *pcidev,
					काष्ठा xen_pcibk_device *pdev,
					अचिन्हित पूर्णांक *करोमुख्य, अचिन्हित पूर्णांक *bus,
					अचिन्हित पूर्णांक *devfn)
अणु
	*करोमुख्य = pci_करोमुख्य_nr(pcidev->bus);
	*bus = pcidev->bus->number;
	*devfn = pcidev->devfn;
	वापस 1;
पूर्ण

स्थिर काष्ठा xen_pcibk_backend xen_pcibk_passthrough_backend = अणु
	.name           = "passthrough",
	.init           = __xen_pcibk_init_devices,
	.मुक्त		= __xen_pcibk_release_devices,
	.find           = __xen_pcibk_get_pcअगरront_dev,
	.publish        = __xen_pcibk_publish_pci_roots,
	.release        = __xen_pcibk_release_pci_dev,
	.add            = __xen_pcibk_add_pci_dev,
	.get            = __xen_pcibk_get_pci_dev,
पूर्ण;
