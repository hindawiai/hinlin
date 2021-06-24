<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/range.h>

#समावेश "bus_numa.h"

LIST_HEAD(pci_root_infos);

अटल काष्ठा pci_root_info *x86_find_pci_root_info(पूर्णांक bus)
अणु
	काष्ठा pci_root_info *info;

	list_क्रम_each_entry(info, &pci_root_infos, list)
		अगर (info->busn.start == bus)
			वापस info;

	वापस शून्य;
पूर्ण

पूर्णांक x86_pci_root_bus_node(पूर्णांक bus)
अणु
	काष्ठा pci_root_info *info = x86_find_pci_root_info(bus);

	अगर (!info)
		वापस NUMA_NO_NODE;

	वापस info->node;
पूर्ण

व्योम x86_pci_root_bus_resources(पूर्णांक bus, काष्ठा list_head *resources)
अणु
	काष्ठा pci_root_info *info = x86_find_pci_root_info(bus);
	काष्ठा pci_root_res *root_res;
	काष्ठा resource_entry *winकरोw;
	bool found = false;

	अगर (!info)
		जाओ शेष_resources;

	prपूर्णांकk(KERN_DEBUG "PCI: root bus %02x: hardware-probed resources\n",
	       bus);

	/* alपढ़ोy added by acpi ? */
	resource_list_क्रम_each_entry(winकरोw, resources)
		अगर (winकरोw->res->flags & IORESOURCE_BUS) अणु
			found = true;
			अवरोध;
		पूर्ण

	अगर (!found)
		pci_add_resource(resources, &info->busn);

	list_क्रम_each_entry(root_res, &info->resources, list)
		pci_add_resource(resources, &root_res->res);

	वापस;

शेष_resources:
	/*
	 * We करोn't have any host bridge aperture inक्रमmation from the
	 * "native host bridge drivers," e.g., amd_bus or broadcom_bus,
	 * so fall back to the शेषs historically used by pci_create_bus().
	 */
	prपूर्णांकk(KERN_DEBUG "PCI: root bus %02x: using default resources\n", bus);
	pci_add_resource(resources, &ioport_resource);
	pci_add_resource(resources, &iomem_resource);
पूर्ण

काष्ठा pci_root_info __init *alloc_pci_root_info(पूर्णांक bus_min, पूर्णांक bus_max,
						 पूर्णांक node, पूर्णांक link)
अणु
	काष्ठा pci_root_info *info;

	info = kzalloc(माप(*info), GFP_KERNEL);

	अगर (!info)
		वापस info;

	प्र_लिखो(info->name, "PCI Bus #%02x", bus_min);

	INIT_LIST_HEAD(&info->resources);
	info->busn.name  = info->name;
	info->busn.start = bus_min;
	info->busn.end   = bus_max;
	info->busn.flags = IORESOURCE_BUS;
	info->node = node;
	info->link = link;

	list_add_tail(&info->list, &pci_root_infos);

	वापस info;
पूर्ण

व्योम update_res(काष्ठा pci_root_info *info, resource_माप_प्रकार start,
		resource_माप_प्रकार end, अचिन्हित दीर्घ flags, पूर्णांक merge)
अणु
	काष्ठा resource *res;
	काष्ठा pci_root_res *root_res;

	अगर (start > end)
		वापस;

	अगर (start == MAX_RESOURCE)
		वापस;

	अगर (!merge)
		जाओ addit;

	/* try to merge it with old one */
	list_क्रम_each_entry(root_res, &info->resources, list) अणु
		resource_माप_प्रकार final_start, final_end;
		resource_माप_प्रकार common_start, common_end;

		res = &root_res->res;
		अगर (res->flags != flags)
			जारी;

		common_start = max(res->start, start);
		common_end = min(res->end, end);
		अगर (common_start > common_end + 1)
			जारी;

		final_start = min(res->start, start);
		final_end = max(res->end, end);

		res->start = final_start;
		res->end = final_end;
		वापस;
	पूर्ण

addit:

	/* need to add that */
	root_res = kzalloc(माप(*root_res), GFP_KERNEL);
	अगर (!root_res)
		वापस;

	res = &root_res->res;
	res->name = info->name;
	res->flags = flags;
	res->start = start;
	res->end = end;

	list_add_tail(&root_res->list, &info->resources);
पूर्ण
