<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * From setup-res.c, by:
 *	Dave Rusling (david.rusling@reo.mts.dec.com)
 *	David Mosberger (davidm@cs.arizona.edu)
 *	David Miller (davem@redhat.com)
 *	Ivan Kokshaysky (ink@jurassic.park.msu.ru)
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>

#समावेश "pci.h"

व्योम pci_add_resource_offset(काष्ठा list_head *resources, काष्ठा resource *res,
			     resource_माप_प्रकार offset)
अणु
	काष्ठा resource_entry *entry;

	entry = resource_list_create_entry(res, 0);
	अगर (!entry) अणु
		pr_err("PCI: can't add host bridge window %pR\n", res);
		वापस;
	पूर्ण

	entry->offset = offset;
	resource_list_add_tail(entry, resources);
पूर्ण
EXPORT_SYMBOL(pci_add_resource_offset);

व्योम pci_add_resource(काष्ठा list_head *resources, काष्ठा resource *res)
अणु
	pci_add_resource_offset(resources, res, 0);
पूर्ण
EXPORT_SYMBOL(pci_add_resource);

व्योम pci_मुक्त_resource_list(काष्ठा list_head *resources)
अणु
	resource_list_मुक्त(resources);
पूर्ण
EXPORT_SYMBOL(pci_मुक्त_resource_list);

व्योम pci_bus_add_resource(काष्ठा pci_bus *bus, काष्ठा resource *res,
			  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pci_bus_resource *bus_res;

	bus_res = kzalloc(माप(काष्ठा pci_bus_resource), GFP_KERNEL);
	अगर (!bus_res) अणु
		dev_err(&bus->dev, "can't add %pR resource\n", res);
		वापस;
	पूर्ण

	bus_res->res = res;
	bus_res->flags = flags;
	list_add_tail(&bus_res->list, &bus->resources);
पूर्ण

काष्ठा resource *pci_bus_resource_n(स्थिर काष्ठा pci_bus *bus, पूर्णांक n)
अणु
	काष्ठा pci_bus_resource *bus_res;

	अगर (n < PCI_BRIDGE_RESOURCE_NUM)
		वापस bus->resource[n];

	n -= PCI_BRIDGE_RESOURCE_NUM;
	list_क्रम_each_entry(bus_res, &bus->resources, list) अणु
		अगर (n-- == 0)
			वापस bus_res->res;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pci_bus_resource_n);

व्योम pci_bus_हटाओ_resources(काष्ठा pci_bus *bus)
अणु
	पूर्णांक i;
	काष्ठा pci_bus_resource *bus_res, *पंचांगp;

	क्रम (i = 0; i < PCI_BRIDGE_RESOURCE_NUM; i++)
		bus->resource[i] = शून्य;

	list_क्रम_each_entry_safe(bus_res, पंचांगp, &bus->resources, list) अणु
		list_del(&bus_res->list);
		kमुक्त(bus_res);
	पूर्ण
पूर्ण

पूर्णांक devm_request_pci_bus_resources(काष्ठा device *dev,
				   काष्ठा list_head *resources)
अणु
	काष्ठा resource_entry *win;
	काष्ठा resource *parent, *res;
	पूर्णांक err;

	resource_list_क्रम_each_entry(win, resources) अणु
		res = win->res;
		चयन (resource_type(res)) अणु
		हाल IORESOURCE_IO:
			parent = &ioport_resource;
			अवरोध;
		हाल IORESOURCE_MEM:
			parent = &iomem_resource;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		err = devm_request_resource(dev, parent, res);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_request_pci_bus_resources);

अटल काष्ठा pci_bus_region pci_32_bit = अणु0, 0xffffffffULLपूर्ण;
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
अटल काष्ठा pci_bus_region pci_64_bit = अणु0,
				(pci_bus_addr_t) 0xffffffffffffffffULLपूर्ण;
अटल काष्ठा pci_bus_region pci_high = अणु(pci_bus_addr_t) 0x100000000ULL,
				(pci_bus_addr_t) 0xffffffffffffffffULLपूर्ण;
#पूर्ण_अगर

/*
 * @res contains CPU addresses.  Clip it so the corresponding bus addresses
 * on @bus are entirely within @region.  This is used to control the bus
 * addresses of resources we allocate, e.g., we may need a resource that
 * can be mapped by a 32-bit BAR.
 */
अटल व्योम pci_clip_resource_to_region(काष्ठा pci_bus *bus,
					काष्ठा resource *res,
					काष्ठा pci_bus_region *region)
अणु
	काष्ठा pci_bus_region r;

	pcibios_resource_to_bus(bus, &r, res);
	अगर (r.start < region->start)
		r.start = region->start;
	अगर (r.end > region->end)
		r.end = region->end;

	अगर (r.end < r.start)
		res->end = res->start - 1;
	अन्यथा
		pcibios_bus_to_resource(bus, res, &r);
पूर्ण

अटल पूर्णांक pci_bus_alloc_from_region(काष्ठा pci_bus *bus, काष्ठा resource *res,
		resource_माप_प्रकार size, resource_माप_प्रकार align,
		resource_माप_प्रकार min, अचिन्हित दीर्घ type_mask,
		resource_माप_प्रकार (*alignf)(व्योम *,
					  स्थिर काष्ठा resource *,
					  resource_माप_प्रकार,
					  resource_माप_प्रकार),
		व्योम *alignf_data,
		काष्ठा pci_bus_region *region)
अणु
	पूर्णांक i, ret;
	काष्ठा resource *r, avail;
	resource_माप_प्रकार max;

	type_mask |= IORESOURCE_TYPE_BITS;

	pci_bus_क्रम_each_resource(bus, r, i) अणु
		resource_माप_प्रकार min_used = min;

		अगर (!r)
			जारी;

		/* type_mask must match */
		अगर ((res->flags ^ r->flags) & type_mask)
			जारी;

		/* We cannot allocate a non-prefetching resource
		   from a pre-fetching area */
		अगर ((r->flags & IORESOURCE_PREFETCH) &&
		    !(res->flags & IORESOURCE_PREFETCH))
			जारी;

		avail = *r;
		pci_clip_resource_to_region(bus, &avail, region);

		/*
		 * "min" is typically PCIBIOS_MIN_IO or PCIBIOS_MIN_MEM to
		 * protect badly करोcumented motherboard resources, but अगर
		 * this is an alपढ़ोy-configured bridge winकरोw, its start
		 * overrides "min".
		 */
		अगर (avail.start)
			min_used = avail.start;

		max = avail.end;

		/* Ok, try it out.. */
		ret = allocate_resource(r, res, size, min_used, max,
					align, alignf, alignf_data);
		अगर (ret == 0)
			वापस 0;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/**
 * pci_bus_alloc_resource - allocate a resource from a parent bus
 * @bus: PCI bus
 * @res: resource to allocate
 * @size: size of resource to allocate
 * @align: alignment of resource to allocate
 * @min: minimum /proc/iomem address to allocate
 * @type_mask: IORESOURCE_* type flags
 * @alignf: resource alignment function
 * @alignf_data: data argument क्रम resource alignment function
 *
 * Given the PCI bus a device resides on, the size, minimum address,
 * alignment and type, try to find an acceptable resource allocation
 * क्रम a specअगरic device resource.
 */
पूर्णांक pci_bus_alloc_resource(काष्ठा pci_bus *bus, काष्ठा resource *res,
		resource_माप_प्रकार size, resource_माप_प्रकार align,
		resource_माप_प्रकार min, अचिन्हित दीर्घ type_mask,
		resource_माप_प्रकार (*alignf)(व्योम *,
					  स्थिर काष्ठा resource *,
					  resource_माप_प्रकार,
					  resource_माप_प्रकार),
		व्योम *alignf_data)
अणु
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	पूर्णांक rc;

	अगर (res->flags & IORESOURCE_MEM_64) अणु
		rc = pci_bus_alloc_from_region(bus, res, size, align, min,
					       type_mask, alignf, alignf_data,
					       &pci_high);
		अगर (rc == 0)
			वापस 0;

		वापस pci_bus_alloc_from_region(bus, res, size, align, min,
						 type_mask, alignf, alignf_data,
						 &pci_64_bit);
	पूर्ण
#पूर्ण_अगर

	वापस pci_bus_alloc_from_region(bus, res, size, align, min,
					 type_mask, alignf, alignf_data,
					 &pci_32_bit);
पूर्ण
EXPORT_SYMBOL(pci_bus_alloc_resource);

/*
 * The @idx resource of @dev should be a PCI-PCI bridge winकरोw.  If this
 * resource fits inside a winकरोw of an upstream bridge, करो nothing.  If it
 * overlaps an upstream winकरोw but extends outside it, clip the resource so
 * it fits completely inside.
 */
bool pci_bus_clip_resource(काष्ठा pci_dev *dev, पूर्णांक idx)
अणु
	काष्ठा pci_bus *bus = dev->bus;
	काष्ठा resource *res = &dev->resource[idx];
	काष्ठा resource orig_res = *res;
	काष्ठा resource *r;
	पूर्णांक i;

	pci_bus_क्रम_each_resource(bus, r, i) अणु
		resource_माप_प्रकार start, end;

		अगर (!r)
			जारी;

		अगर (resource_type(res) != resource_type(r))
			जारी;

		start = max(r->start, res->start);
		end = min(r->end, res->end);

		अगर (start > end)
			जारी;	/* no overlap */

		अगर (res->start == start && res->end == end)
			वापस false;	/* no change */

		res->start = start;
		res->end = end;
		res->flags &= ~IORESOURCE_UNSET;
		orig_res.flags &= ~IORESOURCE_UNSET;
		pci_info(dev, "%pR clipped to %pR\n", &orig_res, res);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम __weak pcibios_resource_survey_bus(काष्ठा pci_bus *bus) अणु पूर्ण

व्योम __weak pcibios_bus_add_device(काष्ठा pci_dev *pdev) अणु पूर्ण

/**
 * pci_bus_add_device - start driver क्रम a single device
 * @dev: device to add
 *
 * This adds add sysfs entries and start device drivers
 */
व्योम pci_bus_add_device(काष्ठा pci_dev *dev)
अणु
	पूर्णांक retval;

	/*
	 * Can not put in pci_device_add yet because resources
	 * are not asचिन्हित yet क्रम some devices.
	 */
	pcibios_bus_add_device(dev);
	pci_fixup_device(pci_fixup_final, dev);
	pci_create_sysfs_dev_files(dev);
	pci_proc_attach_device(dev);
	pci_bridge_d3_update(dev);

	dev->match_driver = true;
	retval = device_attach(&dev->dev);
	अगर (retval < 0 && retval != -EPROBE_DEFER)
		pci_warn(dev, "device attach failed (%d)\n", retval);

	pci_dev_assign_added(dev, true);
पूर्ण
EXPORT_SYMBOL_GPL(pci_bus_add_device);

/**
 * pci_bus_add_devices - start driver क्रम PCI devices
 * @bus: bus to check क्रम new devices
 *
 * Start driver क्रम PCI devices and add some sysfs entries.
 */
व्योम pci_bus_add_devices(स्थिर काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *child;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		/* Skip alपढ़ोy-added devices */
		अगर (pci_dev_is_added(dev))
			जारी;
		pci_bus_add_device(dev);
	पूर्ण

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		/* Skip अगर device attach failed */
		अगर (!pci_dev_is_added(dev))
			जारी;
		child = dev->subordinate;
		अगर (child)
			pci_bus_add_devices(child);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pci_bus_add_devices);

/** pci_walk_bus - walk devices on/under bus, calling callback.
 *  @top      bus whose devices should be walked
 *  @cb       callback to be called क्रम each device found
 *  @userdata arbitrary poपूर्णांकer to be passed to callback.
 *
 *  Walk the given bus, including any bridged devices
 *  on buses under this bus.  Call the provided callback
 *  on each device found.
 *
 *  We check the वापस of @cb each समय. If it वापसs anything
 *  other than 0, we अवरोध out.
 *
 */
व्योम pci_walk_bus(काष्ठा pci_bus *top, पूर्णांक (*cb)(काष्ठा pci_dev *, व्योम *),
		  व्योम *userdata)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *bus;
	काष्ठा list_head *next;
	पूर्णांक retval;

	bus = top;
	करोwn_पढ़ो(&pci_bus_sem);
	next = top->devices.next;
	क्रम (;;) अणु
		अगर (next == &bus->devices) अणु
			/* end of this bus, go up or finish */
			अगर (bus == top)
				अवरोध;
			next = bus->self->bus_list.next;
			bus = bus->self->bus;
			जारी;
		पूर्ण
		dev = list_entry(next, काष्ठा pci_dev, bus_list);
		अगर (dev->subordinate) अणु
			/* this is a pci-pci bridge, करो its devices next */
			next = dev->subordinate->devices.next;
			bus = dev->subordinate;
		पूर्ण अन्यथा
			next = dev->bus_list.next;

		retval = cb(dev, userdata);
		अगर (retval)
			अवरोध;
	पूर्ण
	up_पढ़ो(&pci_bus_sem);
पूर्ण
EXPORT_SYMBOL_GPL(pci_walk_bus);

काष्ठा pci_bus *pci_bus_get(काष्ठा pci_bus *bus)
अणु
	अगर (bus)
		get_device(&bus->dev);
	वापस bus;
पूर्ण

व्योम pci_bus_put(काष्ठा pci_bus *bus)
अणु
	अगर (bus)
		put_device(&bus->dev);
पूर्ण
