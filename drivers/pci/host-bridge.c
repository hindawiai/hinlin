<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Host bridge related code
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>

#समावेश "pci.h"

अटल काष्ठा pci_bus *find_pci_root_bus(काष्ठा pci_bus *bus)
अणु
	जबतक (bus->parent)
		bus = bus->parent;

	वापस bus;
पूर्ण

काष्ठा pci_host_bridge *pci_find_host_bridge(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *root_bus = find_pci_root_bus(bus);

	वापस to_pci_host_bridge(root_bus->bridge);
पूर्ण

काष्ठा device *pci_get_host_bridge_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *root_bus = find_pci_root_bus(dev->bus);
	काष्ठा device *bridge = root_bus->bridge;

	kobject_get(&bridge->kobj);
	वापस bridge;
पूर्ण

व्योम  pci_put_host_bridge_device(काष्ठा device *dev)
अणु
	kobject_put(&dev->kobj);
पूर्ण

व्योम pci_set_host_bridge_release(काष्ठा pci_host_bridge *bridge,
				 व्योम (*release_fn)(काष्ठा pci_host_bridge *),
				 व्योम *release_data)
अणु
	bridge->release_fn = release_fn;
	bridge->release_data = release_data;
पूर्ण
EXPORT_SYMBOL_GPL(pci_set_host_bridge_release);

व्योम pcibios_resource_to_bus(काष्ठा pci_bus *bus, काष्ठा pci_bus_region *region,
			     काष्ठा resource *res)
अणु
	काष्ठा pci_host_bridge *bridge = pci_find_host_bridge(bus);
	काष्ठा resource_entry *winकरोw;
	resource_माप_प्रकार offset = 0;

	resource_list_क्रम_each_entry(winकरोw, &bridge->winकरोws) अणु
		अगर (resource_contains(winकरोw->res, res)) अणु
			offset = winकरोw->offset;
			अवरोध;
		पूर्ण
	पूर्ण

	region->start = res->start - offset;
	region->end = res->end - offset;
पूर्ण
EXPORT_SYMBOL(pcibios_resource_to_bus);

अटल bool region_contains(काष्ठा pci_bus_region *region1,
			    काष्ठा pci_bus_region *region2)
अणु
	वापस region1->start <= region2->start && region1->end >= region2->end;
पूर्ण

व्योम pcibios_bus_to_resource(काष्ठा pci_bus *bus, काष्ठा resource *res,
			     काष्ठा pci_bus_region *region)
अणु
	काष्ठा pci_host_bridge *bridge = pci_find_host_bridge(bus);
	काष्ठा resource_entry *winकरोw;
	resource_माप_प्रकार offset = 0;

	resource_list_क्रम_each_entry(winकरोw, &bridge->winकरोws) अणु
		काष्ठा pci_bus_region bus_region;

		अगर (resource_type(res) != resource_type(winकरोw->res))
			जारी;

		bus_region.start = winकरोw->res->start - winकरोw->offset;
		bus_region.end = winकरोw->res->end - winकरोw->offset;

		अगर (region_contains(&bus_region, region)) अणु
			offset = winकरोw->offset;
			अवरोध;
		पूर्ण
	पूर्ण

	res->start = region->start + offset;
	res->end = region->end + offset;
पूर्ण
EXPORT_SYMBOL(pcibios_bus_to_resource);
