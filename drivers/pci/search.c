<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI searching functions
 *
 * Copyright (C) 1993 -- 1997 Drew Eckhardt, Frederic Potter,
 *					David Mosberger-Tang
 * Copyright (C) 1997 -- 2000 Martin Mares <mj@ucw.cz>
 * Copyright (C) 2003 -- 2004 Greg Kroah-Harपंचांगan <greg@kroah.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "pci.h"

DECLARE_RWSEM(pci_bus_sem);

/*
 * pci_क्रम_each_dma_alias - Iterate over DMA aliases क्रम a device
 * @pdev: starting करोwnstream device
 * @fn: function to call क्रम each alias
 * @data: opaque data to pass to @fn
 *
 * Starting @pdev, walk up the bus calling @fn क्रम each possible alias
 * of @pdev at the root bus.
 */
पूर्णांक pci_क्रम_each_dma_alias(काष्ठा pci_dev *pdev,
			   पूर्णांक (*fn)(काष्ठा pci_dev *pdev,
				     u16 alias, व्योम *data), व्योम *data)
अणु
	काष्ठा pci_bus *bus;
	पूर्णांक ret;

	/*
	 * The device may have an explicit alias requester ID क्रम DMA where the
	 * requester is on another PCI bus.
	 */
	pdev = pci_real_dma_dev(pdev);

	ret = fn(pdev, pci_dev_id(pdev), data);
	अगर (ret)
		वापस ret;

	/*
	 * If the device is broken and uses an alias requester ID क्रम
	 * DMA, iterate over that too.
	 */
	अगर (unlikely(pdev->dma_alias_mask)) अणु
		अचिन्हित पूर्णांक devfn;

		क्रम_each_set_bit(devfn, pdev->dma_alias_mask, MAX_NR_DEVFNS) अणु
			ret = fn(pdev, PCI_DEVID(pdev->bus->number, devfn),
				 data);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	क्रम (bus = pdev->bus; !pci_is_root_bus(bus); bus = bus->parent) अणु
		काष्ठा pci_dev *पंचांगp;

		/* Skip भव buses */
		अगर (!bus->self)
			जारी;

		पंचांगp = bus->self;

		/* stop at bridge where translation unit is associated */
		अगर (पंचांगp->dev_flags & PCI_DEV_FLAGS_BRIDGE_XLATE_ROOT)
			वापस ret;

		/*
		 * PCIe-to-PCI/X bridges alias transactions from करोwnstream
		 * devices using the subordinate bus number (PCI Express to
		 * PCI/PCI-X Bridge Spec, rev 1.0, sec 2.3).  For all हालs
		 * where the upstream bus is PCI/X we alias to the bridge
		 * (there are various conditions in the previous reference
		 * where the bridge may take ownership of transactions, even
		 * when the secondary पूर्णांकerface is PCI-X).
		 */
		अगर (pci_is_pcie(पंचांगp)) अणु
			चयन (pci_pcie_type(पंचांगp)) अणु
			हाल PCI_EXP_TYPE_ROOT_PORT:
			हाल PCI_EXP_TYPE_UPSTREAM:
			हाल PCI_EXP_TYPE_DOWNSTREAM:
				जारी;
			हाल PCI_EXP_TYPE_PCI_BRIDGE:
				ret = fn(पंचांगp,
					 PCI_DEVID(पंचांगp->subordinate->number,
						   PCI_DEVFN(0, 0)), data);
				अगर (ret)
					वापस ret;
				जारी;
			हाल PCI_EXP_TYPE_PCIE_BRIDGE:
				ret = fn(पंचांगp, pci_dev_id(पंचांगp), data);
				अगर (ret)
					वापस ret;
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (पंचांगp->dev_flags & PCI_DEV_FLAG_PCIE_BRIDGE_ALIAS)
				ret = fn(पंचांगp,
					 PCI_DEVID(पंचांगp->subordinate->number,
						   PCI_DEVFN(0, 0)), data);
			अन्यथा
				ret = fn(पंचांगp, pci_dev_id(पंचांगp), data);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा pci_bus *pci_करो_find_bus(काष्ठा pci_bus *bus, अचिन्हित अक्षर busnr)
अणु
	काष्ठा pci_bus *child;
	काष्ठा pci_bus *पंचांगp;

	अगर (bus->number == busnr)
		वापस bus;

	list_क्रम_each_entry(पंचांगp, &bus->children, node) अणु
		child = pci_करो_find_bus(पंचांगp, busnr);
		अगर (child)
			वापस child;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * pci_find_bus - locate PCI bus from a given करोमुख्य and bus number
 * @करोमुख्य: number of PCI करोमुख्य to search
 * @busnr: number of desired PCI bus
 *
 * Given a PCI bus number and करोमुख्य number, the desired PCI bus is located
 * in the global list of PCI buses.  If the bus is found, a poपूर्णांकer to its
 * data काष्ठाure is वापसed.  If no bus is found, %शून्य is वापसed.
 */
काष्ठा pci_bus *pci_find_bus(पूर्णांक करोमुख्य, पूर्णांक busnr)
अणु
	काष्ठा pci_bus *bus = शून्य;
	काष्ठा pci_bus *पंचांगp_bus;

	जबतक ((bus = pci_find_next_bus(bus)) != शून्य)  अणु
		अगर (pci_करोमुख्य_nr(bus) != करोमुख्य)
			जारी;
		पंचांगp_bus = pci_करो_find_bus(bus, busnr);
		अगर (पंचांगp_bus)
			वापस पंचांगp_bus;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(pci_find_bus);

/**
 * pci_find_next_bus - begin or जारी searching क्रम a PCI bus
 * @from: Previous PCI bus found, or %शून्य क्रम new search.
 *
 * Iterates through the list of known PCI buses.  A new search is
 * initiated by passing %शून्य as the @from argument.  Otherwise अगर
 * @from is not %शून्य, searches जारी from next device on the
 * global list.
 */
काष्ठा pci_bus *pci_find_next_bus(स्थिर काष्ठा pci_bus *from)
अणु
	काष्ठा list_head *n;
	काष्ठा pci_bus *b = शून्य;

	करोwn_पढ़ो(&pci_bus_sem);
	n = from ? from->node.next : pci_root_buses.next;
	अगर (n != &pci_root_buses)
		b = list_entry(n, काष्ठा pci_bus, node);
	up_पढ़ो(&pci_bus_sem);
	वापस b;
पूर्ण
EXPORT_SYMBOL(pci_find_next_bus);

/**
 * pci_get_slot - locate PCI device क्रम a given PCI slot
 * @bus: PCI bus on which desired PCI device resides
 * @devfn: encodes number of PCI slot in which the desired PCI
 * device resides and the logical device number within that slot
 * in हाल of multi-function devices.
 *
 * Given a PCI bus and slot/function number, the desired PCI device
 * is located in the list of PCI devices.
 * If the device is found, its reference count is increased and this
 * function वापसs a poपूर्णांकer to its data काष्ठाure.  The caller must
 * decrement the reference count by calling pci_dev_put().
 * If no device is found, %शून्य is वापसed.
 */
काष्ठा pci_dev *pci_get_slot(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा pci_dev *dev;

	करोwn_पढ़ो(&pci_bus_sem);

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		अगर (dev->devfn == devfn)
			जाओ out;
	पूर्ण

	dev = शून्य;
 out:
	pci_dev_get(dev);
	up_पढ़ो(&pci_bus_sem);
	वापस dev;
पूर्ण
EXPORT_SYMBOL(pci_get_slot);

/**
 * pci_get_करोमुख्य_bus_and_slot - locate PCI device क्रम a given PCI करोमुख्य (segment), bus, and slot
 * @करोमुख्य: PCI करोमुख्य/segment on which the PCI device resides.
 * @bus: PCI bus on which desired PCI device resides
 * @devfn: encodes number of PCI slot in which the desired PCI device
 * resides and the logical device number within that slot in हाल of
 * multi-function devices.
 *
 * Given a PCI करोमुख्य, bus, and slot/function number, the desired PCI
 * device is located in the list of PCI devices. If the device is
 * found, its reference count is increased and this function वापसs a
 * poपूर्णांकer to its data काष्ठाure.  The caller must decrement the
 * reference count by calling pci_dev_put().  If no device is found,
 * %शून्य is वापसed.
 */
काष्ठा pci_dev *pci_get_करोमुख्य_bus_and_slot(पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus,
					    अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा pci_dev *dev = शून्य;

	क्रम_each_pci_dev(dev) अणु
		अगर (pci_करोमुख्य_nr(dev->bus) == करोमुख्य &&
		    (dev->bus->number == bus && dev->devfn == devfn))
			वापस dev;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(pci_get_करोमुख्य_bus_and_slot);

अटल पूर्णांक match_pci_dev_by_id(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	स्थिर काष्ठा pci_device_id *id = data;

	अगर (pci_match_one_device(id, pdev))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * pci_get_dev_by_id - begin or जारी searching क्रम a PCI device by id
 * @id: poपूर्णांकer to काष्ठा pci_device_id to match क्रम the device
 * @from: Previous PCI device found in search, or %शून्य क्रम new search.
 *
 * Iterates through the list of known PCI devices.  If a PCI device is found
 * with a matching id a poपूर्णांकer to its device काष्ठाure is वापसed, and the
 * reference count to the device is incremented.  Otherwise, %शून्य is वापसed.
 * A new search is initiated by passing %शून्य as the @from argument.  Otherwise
 * अगर @from is not %शून्य, searches जारी from next device on the global
 * list.  The reference count क्रम @from is always decremented अगर it is not
 * %शून्य.
 *
 * This is an पूर्णांकernal function क्रम use by the other search functions in
 * this file.
 */
अटल काष्ठा pci_dev *pci_get_dev_by_id(स्थिर काष्ठा pci_device_id *id,
					 काष्ठा pci_dev *from)
अणु
	काष्ठा device *dev;
	काष्ठा device *dev_start = शून्य;
	काष्ठा pci_dev *pdev = शून्य;

	अगर (from)
		dev_start = &from->dev;
	dev = bus_find_device(&pci_bus_type, dev_start, (व्योम *)id,
			      match_pci_dev_by_id);
	अगर (dev)
		pdev = to_pci_dev(dev);
	pci_dev_put(from);
	वापस pdev;
पूर्ण

/**
 * pci_get_subsys - begin or जारी searching क्रम a PCI device by venकरोr/subvenकरोr/device/subdevice id
 * @venकरोr: PCI venकरोr id to match, or %PCI_ANY_ID to match all venकरोr ids
 * @device: PCI device id to match, or %PCI_ANY_ID to match all device ids
 * @ss_venकरोr: PCI subप्रणाली venकरोr id to match, or %PCI_ANY_ID to match all venकरोr ids
 * @ss_device: PCI subप्रणाली device id to match, or %PCI_ANY_ID to match all device ids
 * @from: Previous PCI device found in search, or %शून्य क्रम new search.
 *
 * Iterates through the list of known PCI devices.  If a PCI device is found
 * with a matching @venकरोr, @device, @ss_venकरोr and @ss_device, a poपूर्णांकer to its
 * device काष्ठाure is वापसed, and the reference count to the device is
 * incremented.  Otherwise, %शून्य is वापसed.  A new search is initiated by
 * passing %शून्य as the @from argument.  Otherwise अगर @from is not %शून्य,
 * searches जारी from next device on the global list.
 * The reference count क्रम @from is always decremented अगर it is not %शून्य.
 */
काष्ठा pci_dev *pci_get_subsys(अचिन्हित पूर्णांक venकरोr, अचिन्हित पूर्णांक device,
			       अचिन्हित पूर्णांक ss_venकरोr, अचिन्हित पूर्णांक ss_device,
			       काष्ठा pci_dev *from)
अणु
	काष्ठा pci_device_id id = अणु
		.venकरोr = venकरोr,
		.device = device,
		.subvenकरोr = ss_venकरोr,
		.subdevice = ss_device,
	पूर्ण;

	वापस pci_get_dev_by_id(&id, from);
पूर्ण
EXPORT_SYMBOL(pci_get_subsys);

/**
 * pci_get_device - begin or जारी searching क्रम a PCI device by venकरोr/device id
 * @venकरोr: PCI venकरोr id to match, or %PCI_ANY_ID to match all venकरोr ids
 * @device: PCI device id to match, or %PCI_ANY_ID to match all device ids
 * @from: Previous PCI device found in search, or %शून्य क्रम new search.
 *
 * Iterates through the list of known PCI devices.  If a PCI device is
 * found with a matching @venकरोr and @device, the reference count to the
 * device is incremented and a poपूर्णांकer to its device काष्ठाure is वापसed.
 * Otherwise, %शून्य is वापसed.  A new search is initiated by passing %शून्य
 * as the @from argument.  Otherwise अगर @from is not %शून्य, searches जारी
 * from next device on the global list.  The reference count क्रम @from is
 * always decremented अगर it is not %शून्य.
 */
काष्ठा pci_dev *pci_get_device(अचिन्हित पूर्णांक venकरोr, अचिन्हित पूर्णांक device,
			       काष्ठा pci_dev *from)
अणु
	वापस pci_get_subsys(venकरोr, device, PCI_ANY_ID, PCI_ANY_ID, from);
पूर्ण
EXPORT_SYMBOL(pci_get_device);

/**
 * pci_get_class - begin or जारी searching क्रम a PCI device by class
 * @class: search क्रम a PCI device with this class designation
 * @from: Previous PCI device found in search, or %शून्य क्रम new search.
 *
 * Iterates through the list of known PCI devices.  If a PCI device is
 * found with a matching @class, the reference count to the device is
 * incremented and a poपूर्णांकer to its device काष्ठाure is वापसed.
 * Otherwise, %शून्य is वापसed.
 * A new search is initiated by passing %शून्य as the @from argument.
 * Otherwise अगर @from is not %शून्य, searches जारी from next device
 * on the global list.  The reference count क्रम @from is always decremented
 * अगर it is not %शून्य.
 */
काष्ठा pci_dev *pci_get_class(अचिन्हित पूर्णांक class, काष्ठा pci_dev *from)
अणु
	काष्ठा pci_device_id id = अणु
		.venकरोr = PCI_ANY_ID,
		.device = PCI_ANY_ID,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
		.class_mask = PCI_ANY_ID,
		.class = class,
	पूर्ण;

	वापस pci_get_dev_by_id(&id, from);
पूर्ण
EXPORT_SYMBOL(pci_get_class);

/**
 * pci_dev_present - Returns 1 अगर device matching the device list is present, 0 अगर not.
 * @ids: A poपूर्णांकer to a null terminated list of काष्ठा pci_device_id काष्ठाures
 * that describe the type of PCI device the caller is trying to find.
 *
 * Obvious fact: You करो not have a reference to any device that might be found
 * by this function, so अगर that device is हटाओd from the प्रणाली right after
 * this function is finished, the value will be stale.  Use this function to
 * find devices that are usually built पूर्णांकo a प्रणाली, or क्रम a general hपूर्णांक as
 * to अगर another device happens to be present at this specअगरic moment in समय.
 */
पूर्णांक pci_dev_present(स्थिर काष्ठा pci_device_id *ids)
अणु
	काष्ठा pci_dev *found = शून्य;

	जबतक (ids->venकरोr || ids->subvenकरोr || ids->class_mask) अणु
		found = pci_get_dev_by_id(ids, शून्य);
		अगर (found) अणु
			pci_dev_put(found);
			वापस 1;
		पूर्ण
		ids++;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pci_dev_present);
