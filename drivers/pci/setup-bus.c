<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support routines क्रम initializing a PCI subप्रणाली
 *
 * Extruded from code written by
 *      Dave Rusling (david.rusling@reo.mts.dec.com)
 *      David Mosberger (davidm@cs.arizona.edu)
 *	David Miller (davem@redhat.com)
 *
 * Nov 2000, Ivan Kokshaysky <ink@jurassic.park.msu.ru>
 *	     PCI-PCI bridges cleanup, sorted resource allocation.
 * Feb 2002, Ivan Kokshaysky <ink@jurassic.park.msu.ru>
 *	     Converted to allocation in 3 passes, which gives
 *	     tighter packing. Prefetchable range support.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/cache.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश "pci.h"

अचिन्हित पूर्णांक pci_flags;
EXPORT_SYMBOL_GPL(pci_flags);

काष्ठा pci_dev_resource अणु
	काष्ठा list_head list;
	काष्ठा resource *res;
	काष्ठा pci_dev *dev;
	resource_माप_प्रकार start;
	resource_माप_प्रकार end;
	resource_माप_प्रकार add_size;
	resource_माप_प्रकार min_align;
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल व्योम मुक्त_list(काष्ठा list_head *head)
अणु
	काष्ठा pci_dev_resource *dev_res, *पंचांगp;

	list_क्रम_each_entry_safe(dev_res, पंचांगp, head, list) अणु
		list_del(&dev_res->list);
		kमुक्त(dev_res);
	पूर्ण
पूर्ण

/**
 * add_to_list() - Add a new resource tracker to the list
 * @head:	Head of the list
 * @dev:	Device to which the resource beदीर्घs
 * @res:	Resource to be tracked
 * @add_size:	Additional size to be optionally added to the resource
 * @min_align:	Minimum memory winकरोw alignment
 */
अटल पूर्णांक add_to_list(काष्ठा list_head *head, काष्ठा pci_dev *dev,
		       काष्ठा resource *res, resource_माप_प्रकार add_size,
		       resource_माप_प्रकार min_align)
अणु
	काष्ठा pci_dev_resource *पंचांगp;

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	पंचांगp->res = res;
	पंचांगp->dev = dev;
	पंचांगp->start = res->start;
	पंचांगp->end = res->end;
	पंचांगp->flags = res->flags;
	पंचांगp->add_size = add_size;
	पंचांगp->min_align = min_align;

	list_add(&पंचांगp->list, head);

	वापस 0;
पूर्ण

अटल व्योम हटाओ_from_list(काष्ठा list_head *head, काष्ठा resource *res)
अणु
	काष्ठा pci_dev_resource *dev_res, *पंचांगp;

	list_क्रम_each_entry_safe(dev_res, पंचांगp, head, list) अणु
		अगर (dev_res->res == res) अणु
			list_del(&dev_res->list);
			kमुक्त(dev_res);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा pci_dev_resource *res_to_dev_res(काष्ठा list_head *head,
					       काष्ठा resource *res)
अणु
	काष्ठा pci_dev_resource *dev_res;

	list_क्रम_each_entry(dev_res, head, list) अणु
		अगर (dev_res->res == res)
			वापस dev_res;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल resource_माप_प्रकार get_res_add_size(काष्ठा list_head *head,
					काष्ठा resource *res)
अणु
	काष्ठा pci_dev_resource *dev_res;

	dev_res = res_to_dev_res(head, res);
	वापस dev_res ? dev_res->add_size : 0;
पूर्ण

अटल resource_माप_प्रकार get_res_add_align(काष्ठा list_head *head,
					 काष्ठा resource *res)
अणु
	काष्ठा pci_dev_resource *dev_res;

	dev_res = res_to_dev_res(head, res);
	वापस dev_res ? dev_res->min_align : 0;
पूर्ण


/* Sort resources by alignment */
अटल व्योम pdev_sort_resources(काष्ठा pci_dev *dev, काष्ठा list_head *head)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
		काष्ठा resource *r;
		काष्ठा pci_dev_resource *dev_res, *पंचांगp;
		resource_माप_प्रकार r_align;
		काष्ठा list_head *n;

		r = &dev->resource[i];

		अगर (r->flags & IORESOURCE_PCI_FIXED)
			जारी;

		अगर (!(r->flags) || r->parent)
			जारी;

		r_align = pci_resource_alignment(dev, r);
		अगर (!r_align) अणु
			pci_warn(dev, "BAR %d: %pR has bogus alignment\n",
				 i, r);
			जारी;
		पूर्ण

		पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
		अगर (!पंचांगp)
			panic("%s: kzalloc() failed!\n", __func__);
		पंचांगp->res = r;
		पंचांगp->dev = dev;

		/* Fallback is smallest one or list is empty */
		n = head;
		list_क्रम_each_entry(dev_res, head, list) अणु
			resource_माप_प्रकार align;

			align = pci_resource_alignment(dev_res->dev,
							 dev_res->res);

			अगर (r_align > align) अणु
				n = &dev_res->list;
				अवरोध;
			पूर्ण
		पूर्ण
		/* Insert it just beक्रमe n */
		list_add_tail(&पंचांगp->list, n);
	पूर्ण
पूर्ण

अटल व्योम __dev_sort_resources(काष्ठा pci_dev *dev, काष्ठा list_head *head)
अणु
	u16 class = dev->class >> 8;

	/* Don't touch classless devices or host bridges or IOAPICs */
	अगर (class == PCI_CLASS_NOT_DEFINED || class == PCI_CLASS_BRIDGE_HOST)
		वापस;

	/* Don't touch IOAPIC devices alपढ़ोy enabled by firmware */
	अगर (class == PCI_CLASS_SYSTEM_PIC) अणु
		u16 command;
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);
		अगर (command & (PCI_COMMAND_IO | PCI_COMMAND_MEMORY))
			वापस;
	पूर्ण

	pdev_sort_resources(dev, head);
पूर्ण

अटल अंतरभूत व्योम reset_resource(काष्ठा resource *res)
अणु
	res->start = 0;
	res->end = 0;
	res->flags = 0;
पूर्ण

/**
 * reassign_resources_sorted() - Satisfy any additional resource requests
 *
 * @पुनः_स्मृति_head:	Head of the list tracking requests requiring
 *			additional resources
 * @head:		Head of the list tracking requests with allocated
 *			resources
 *
 * Walk through each element of the पुनः_स्मृति_head and try to procure additional
 * resources क्रम the element, provided the element is in the head list.
 */
अटल व्योम reassign_resources_sorted(काष्ठा list_head *पुनः_स्मृति_head,
				      काष्ठा list_head *head)
अणु
	काष्ठा resource *res;
	काष्ठा pci_dev_resource *add_res, *पंचांगp;
	काष्ठा pci_dev_resource *dev_res;
	resource_माप_प्रकार add_size, align;
	पूर्णांक idx;

	list_क्रम_each_entry_safe(add_res, पंचांगp, पुनः_स्मृति_head, list) अणु
		bool found_match = false;

		res = add_res->res;
		/* Skip resource that has been reset */
		अगर (!res->flags)
			जाओ out;

		/* Skip this resource अगर not found in head list */
		list_क्रम_each_entry(dev_res, head, list) अणु
			अगर (dev_res->res == res) अणु
				found_match = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found_match) /* Just skip */
			जारी;

		idx = res - &add_res->dev->resource[0];
		add_size = add_res->add_size;
		align = add_res->min_align;
		अगर (!resource_size(res)) अणु
			res->start = align;
			res->end = res->start + add_size - 1;
			अगर (pci_assign_resource(add_res->dev, idx))
				reset_resource(res);
		पूर्ण अन्यथा अणु
			res->flags |= add_res->flags &
				 (IORESOURCE_STARTALIGN|IORESOURCE_SIZEALIGN);
			अगर (pci_reassign_resource(add_res->dev, idx,
						  add_size, align))
				pci_info(add_res->dev, "failed to add %llx res[%d]=%pR\n",
					 (अचिन्हित दीर्घ दीर्घ) add_size, idx,
					 res);
		पूर्ण
out:
		list_del(&add_res->list);
		kमुक्त(add_res);
	पूर्ण
पूर्ण

/**
 * assign_requested_resources_sorted() - Satisfy resource requests
 *
 * @head:	Head of the list tracking requests क्रम resources
 * @fail_head:	Head of the list tracking requests that could not be
 *		allocated
 *
 * Satisfy resource requests of each element in the list.  Add requests that
 * could not be satisfied to the failed_list.
 */
अटल व्योम assign_requested_resources_sorted(काष्ठा list_head *head,
				 काष्ठा list_head *fail_head)
अणु
	काष्ठा resource *res;
	काष्ठा pci_dev_resource *dev_res;
	पूर्णांक idx;

	list_क्रम_each_entry(dev_res, head, list) अणु
		res = dev_res->res;
		idx = res - &dev_res->dev->resource[0];
		अगर (resource_size(res) &&
		    pci_assign_resource(dev_res->dev, idx)) अणु
			अगर (fail_head) अणु
				/*
				 * If the failed resource is a ROM BAR and
				 * it will be enabled later, करोn't add it
				 * to the list.
				 */
				अगर (!((idx == PCI_ROM_RESOURCE) &&
				      (!(res->flags & IORESOURCE_ROM_ENABLE))))
					add_to_list(fail_head,
						    dev_res->dev, res,
						    0 /* करोn't care */,
						    0 /* करोn't care */);
			पूर्ण
			reset_resource(res);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ pci_fail_res_type_mask(काष्ठा list_head *fail_head)
अणु
	काष्ठा pci_dev_resource *fail_res;
	अचिन्हित दीर्घ mask = 0;

	/* Check failed type */
	list_क्रम_each_entry(fail_res, fail_head, list)
		mask |= fail_res->flags;

	/*
	 * One pref failed resource will set IORESOURCE_MEM, as we can
	 * allocate pref in non-pref range.  Will release all asचिन्हित
	 * non-pref sibling resources according to that bit.
	 */
	वापस mask & (IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_PREFETCH);
पूर्ण

अटल bool pci_need_to_release(अचिन्हित दीर्घ mask, काष्ठा resource *res)
अणु
	अगर (res->flags & IORESOURCE_IO)
		वापस !!(mask & IORESOURCE_IO);

	/* Check pref at first */
	अगर (res->flags & IORESOURCE_PREFETCH) अणु
		अगर (mask & IORESOURCE_PREFETCH)
			वापस true;
		/* Count pref अगर its parent is non-pref */
		अन्यथा अगर ((mask & IORESOURCE_MEM) &&
			 !(res->parent->flags & IORESOURCE_PREFETCH))
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण

	अगर (res->flags & IORESOURCE_MEM)
		वापस !!(mask & IORESOURCE_MEM);

	वापस false;	/* Should not get here */
पूर्ण

अटल व्योम __assign_resources_sorted(काष्ठा list_head *head,
				      काष्ठा list_head *पुनः_स्मृति_head,
				      काष्ठा list_head *fail_head)
अणु
	/*
	 * Should not assign requested resources at first.  They could be
	 * adjacent, so later reassign can not पुनः_स्मृतिate them one by one in
	 * parent resource winकरोw.
	 *
	 * Try to assign requested + add_size at beginning.  If could करो that,
	 * could get out early.  If could not करो that, we still try to assign
	 * requested at first, then try to reassign add_size क्रम some resources.
	 *
	 * Separate three resource type checking अगर we need to release
	 * asचिन्हित resource after requested + add_size try.
	 *
	 *	1. If IO port assignment fails, will release asचिन्हित IO
	 *	   port.
	 *	2. If pref MMIO assignment fails, release asचिन्हित pref
	 *	   MMIO.  If asचिन्हित pref MMIO's parent is non-pref MMIO
	 *	   and non-pref MMIO assignment fails, will release that
	 *	   asचिन्हित pref MMIO.
	 *	3. If non-pref MMIO assignment fails or pref MMIO
	 *	   assignment fails, will release asचिन्हित non-pref MMIO.
	 */
	LIST_HEAD(save_head);
	LIST_HEAD(local_fail_head);
	काष्ठा pci_dev_resource *save_res;
	काष्ठा pci_dev_resource *dev_res, *पंचांगp_res, *dev_res2;
	अचिन्हित दीर्घ fail_type;
	resource_माप_प्रकार add_align, align;

	/* Check अगर optional add_size is there */
	अगर (!पुनः_स्मृति_head || list_empty(पुनः_स्मृति_head))
		जाओ requested_and_reassign;

	/* Save original start, end, flags etc at first */
	list_क्रम_each_entry(dev_res, head, list) अणु
		अगर (add_to_list(&save_head, dev_res->dev, dev_res->res, 0, 0)) अणु
			मुक्त_list(&save_head);
			जाओ requested_and_reassign;
		पूर्ण
	पूर्ण

	/* Update res in head list with add_size in पुनः_स्मृति_head list */
	list_क्रम_each_entry_safe(dev_res, पंचांगp_res, head, list) अणु
		dev_res->res->end += get_res_add_size(पुनः_स्मृति_head,
							dev_res->res);

		/*
		 * There are two kinds of additional resources in the list:
		 * 1. bridge resource  -- IORESOURCE_STARTALIGN
		 * 2. SR-IOV resource  -- IORESOURCE_SIZEALIGN
		 * Here just fix the additional alignment क्रम bridge
		 */
		अगर (!(dev_res->res->flags & IORESOURCE_STARTALIGN))
			जारी;

		add_align = get_res_add_align(पुनः_स्मृति_head, dev_res->res);

		/*
		 * The "head" list is sorted by alignment so resources with
		 * bigger alignment will be asचिन्हित first.  After we
		 * change the alignment of a dev_res in "head" list, we
		 * need to reorder the list by alignment to make it
		 * consistent.
		 */
		अगर (add_align > dev_res->res->start) अणु
			resource_माप_प्रकार r_size = resource_size(dev_res->res);

			dev_res->res->start = add_align;
			dev_res->res->end = add_align + r_size - 1;

			list_क्रम_each_entry(dev_res2, head, list) अणु
				align = pci_resource_alignment(dev_res2->dev,
							       dev_res2->res);
				अगर (add_align > align) अणु
					list_move_tail(&dev_res->list,
						       &dev_res2->list);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

	पूर्ण

	/* Try updated head list with add_size added */
	assign_requested_resources_sorted(head, &local_fail_head);

	/* All asचिन्हित with add_size? */
	अगर (list_empty(&local_fail_head)) अणु
		/* Remove head list from पुनः_स्मृति_head list */
		list_क्रम_each_entry(dev_res, head, list)
			हटाओ_from_list(पुनः_स्मृति_head, dev_res->res);
		मुक्त_list(&save_head);
		मुक्त_list(head);
		वापस;
	पूर्ण

	/* Check failed type */
	fail_type = pci_fail_res_type_mask(&local_fail_head);
	/* Remove not need to be released asचिन्हित res from head list etc */
	list_क्रम_each_entry_safe(dev_res, पंचांगp_res, head, list)
		अगर (dev_res->res->parent &&
		    !pci_need_to_release(fail_type, dev_res->res)) अणु
			/* Remove it from पुनः_स्मृति_head list */
			हटाओ_from_list(पुनः_स्मृति_head, dev_res->res);
			हटाओ_from_list(&save_head, dev_res->res);
			list_del(&dev_res->list);
			kमुक्त(dev_res);
		पूर्ण

	मुक्त_list(&local_fail_head);
	/* Release asचिन्हित resource */
	list_क्रम_each_entry(dev_res, head, list)
		अगर (dev_res->res->parent)
			release_resource(dev_res->res);
	/* Restore start/end/flags from saved list */
	list_क्रम_each_entry(save_res, &save_head, list) अणु
		काष्ठा resource *res = save_res->res;

		res->start = save_res->start;
		res->end = save_res->end;
		res->flags = save_res->flags;
	पूर्ण
	मुक्त_list(&save_head);

requested_and_reassign:
	/* Satisfy the must-have resource requests */
	assign_requested_resources_sorted(head, fail_head);

	/* Try to satisfy any additional optional resource requests */
	अगर (पुनः_स्मृति_head)
		reassign_resources_sorted(पुनः_स्मृति_head, head);
	मुक्त_list(head);
पूर्ण

अटल व्योम pdev_assign_resources_sorted(काष्ठा pci_dev *dev,
					 काष्ठा list_head *add_head,
					 काष्ठा list_head *fail_head)
अणु
	LIST_HEAD(head);

	__dev_sort_resources(dev, &head);
	__assign_resources_sorted(&head, add_head, fail_head);

पूर्ण

अटल व्योम pbus_assign_resources_sorted(स्थिर काष्ठा pci_bus *bus,
					 काष्ठा list_head *पुनः_स्मृति_head,
					 काष्ठा list_head *fail_head)
अणु
	काष्ठा pci_dev *dev;
	LIST_HEAD(head);

	list_क्रम_each_entry(dev, &bus->devices, bus_list)
		__dev_sort_resources(dev, &head);

	__assign_resources_sorted(&head, पुनः_स्मृति_head, fail_head);
पूर्ण

व्योम pci_setup_cardbus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *bridge = bus->self;
	काष्ठा resource *res;
	काष्ठा pci_bus_region region;

	pci_info(bridge, "CardBus bridge to %pR\n",
		 &bus->busn_res);

	res = bus->resource[0];
	pcibios_resource_to_bus(bridge->bus, &region, res);
	अगर (res->flags & IORESOURCE_IO) अणु
		/*
		 * The IO resource is allocated a range twice as large as it
		 * would normally need.  This allows us to set both IO regs.
		 */
		pci_info(bridge, "  bridge window %pR\n", res);
		pci_ग_लिखो_config_dword(bridge, PCI_CB_IO_BASE_0,
					region.start);
		pci_ग_लिखो_config_dword(bridge, PCI_CB_IO_LIMIT_0,
					region.end);
	पूर्ण

	res = bus->resource[1];
	pcibios_resource_to_bus(bridge->bus, &region, res);
	अगर (res->flags & IORESOURCE_IO) अणु
		pci_info(bridge, "  bridge window %pR\n", res);
		pci_ग_लिखो_config_dword(bridge, PCI_CB_IO_BASE_1,
					region.start);
		pci_ग_लिखो_config_dword(bridge, PCI_CB_IO_LIMIT_1,
					region.end);
	पूर्ण

	res = bus->resource[2];
	pcibios_resource_to_bus(bridge->bus, &region, res);
	अगर (res->flags & IORESOURCE_MEM) अणु
		pci_info(bridge, "  bridge window %pR\n", res);
		pci_ग_लिखो_config_dword(bridge, PCI_CB_MEMORY_BASE_0,
					region.start);
		pci_ग_लिखो_config_dword(bridge, PCI_CB_MEMORY_LIMIT_0,
					region.end);
	पूर्ण

	res = bus->resource[3];
	pcibios_resource_to_bus(bridge->bus, &region, res);
	अगर (res->flags & IORESOURCE_MEM) अणु
		pci_info(bridge, "  bridge window %pR\n", res);
		pci_ग_लिखो_config_dword(bridge, PCI_CB_MEMORY_BASE_1,
					region.start);
		pci_ग_लिखो_config_dword(bridge, PCI_CB_MEMORY_LIMIT_1,
					region.end);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pci_setup_cardbus);

/*
 * Initialize bridges with base/limit values we have collected.  PCI-to-PCI
 * Bridge Architecture Specअगरication rev. 1.1 (1998) requires that अगर there
 * are no I/O ports or memory behind the bridge, the corresponding range
 * must be turned off by writing base value greater than limit to the
 * bridge's base/limit रेजिस्टरs.
 *
 * Note: care must be taken when updating I/O base/limit रेजिस्टरs of
 * bridges which support 32-bit I/O.  This update requires two config space
 * ग_लिखोs, so it's quite possible that an I/O winकरोw of the bridge will
 * have some undesirable address (e.g. 0) after the first ग_लिखो.  Ditto
 * 64-bit prefetchable MMIO.
 */
अटल व्योम pci_setup_bridge_io(काष्ठा pci_dev *bridge)
अणु
	काष्ठा resource *res;
	काष्ठा pci_bus_region region;
	अचिन्हित दीर्घ io_mask;
	u8 io_base_lo, io_limit_lo;
	u16 l;
	u32 io_upper16;

	io_mask = PCI_IO_RANGE_MASK;
	अगर (bridge->io_winकरोw_1k)
		io_mask = PCI_IO_1K_RANGE_MASK;

	/* Set up the top and bottom of the PCI I/O segment क्रम this bus */
	res = &bridge->resource[PCI_BRIDGE_IO_WINDOW];
	pcibios_resource_to_bus(bridge->bus, &region, res);
	अगर (res->flags & IORESOURCE_IO) अणु
		pci_पढ़ो_config_word(bridge, PCI_IO_BASE, &l);
		io_base_lo = (region.start >> 8) & io_mask;
		io_limit_lo = (region.end >> 8) & io_mask;
		l = ((u16) io_limit_lo << 8) | io_base_lo;
		/* Set up upper 16 bits of I/O base/limit */
		io_upper16 = (region.end & 0xffff0000) | (region.start >> 16);
		pci_info(bridge, "  bridge window %pR\n", res);
	पूर्ण अन्यथा अणु
		/* Clear upper 16 bits of I/O base/limit */
		io_upper16 = 0;
		l = 0x00f0;
	पूर्ण
	/* Temporarily disable the I/O range beक्रमe updating PCI_IO_BASE */
	pci_ग_लिखो_config_dword(bridge, PCI_IO_BASE_UPPER16, 0x0000ffff);
	/* Update lower 16 bits of I/O base/limit */
	pci_ग_लिखो_config_word(bridge, PCI_IO_BASE, l);
	/* Update upper 16 bits of I/O base/limit */
	pci_ग_लिखो_config_dword(bridge, PCI_IO_BASE_UPPER16, io_upper16);
पूर्ण

अटल व्योम pci_setup_bridge_mmio(काष्ठा pci_dev *bridge)
अणु
	काष्ठा resource *res;
	काष्ठा pci_bus_region region;
	u32 l;

	/* Set up the top and bottom of the PCI Memory segment क्रम this bus */
	res = &bridge->resource[PCI_BRIDGE_MEM_WINDOW];
	pcibios_resource_to_bus(bridge->bus, &region, res);
	अगर (res->flags & IORESOURCE_MEM) अणु
		l = (region.start >> 16) & 0xfff0;
		l |= region.end & 0xfff00000;
		pci_info(bridge, "  bridge window %pR\n", res);
	पूर्ण अन्यथा अणु
		l = 0x0000fff0;
	पूर्ण
	pci_ग_लिखो_config_dword(bridge, PCI_MEMORY_BASE, l);
पूर्ण

अटल व्योम pci_setup_bridge_mmio_pref(काष्ठा pci_dev *bridge)
अणु
	काष्ठा resource *res;
	काष्ठा pci_bus_region region;
	u32 l, bu, lu;

	/*
	 * Clear out the upper 32 bits of PREF limit.  If
	 * PCI_PREF_BASE_UPPER32 was non-zero, this temporarily disables
	 * PREF range, which is ok.
	 */
	pci_ग_लिखो_config_dword(bridge, PCI_PREF_LIMIT_UPPER32, 0);

	/* Set up PREF base/limit */
	bu = lu = 0;
	res = &bridge->resource[PCI_BRIDGE_PREF_MEM_WINDOW];
	pcibios_resource_to_bus(bridge->bus, &region, res);
	अगर (res->flags & IORESOURCE_PREFETCH) अणु
		l = (region.start >> 16) & 0xfff0;
		l |= region.end & 0xfff00000;
		अगर (res->flags & IORESOURCE_MEM_64) अणु
			bu = upper_32_bits(region.start);
			lu = upper_32_bits(region.end);
		पूर्ण
		pci_info(bridge, "  bridge window %pR\n", res);
	पूर्ण अन्यथा अणु
		l = 0x0000fff0;
	पूर्ण
	pci_ग_लिखो_config_dword(bridge, PCI_PREF_MEMORY_BASE, l);

	/* Set the upper 32 bits of PREF base & limit */
	pci_ग_लिखो_config_dword(bridge, PCI_PREF_BASE_UPPER32, bu);
	pci_ग_लिखो_config_dword(bridge, PCI_PREF_LIMIT_UPPER32, lu);
पूर्ण

अटल व्योम __pci_setup_bridge(काष्ठा pci_bus *bus, अचिन्हित दीर्घ type)
अणु
	काष्ठा pci_dev *bridge = bus->self;

	pci_info(bridge, "PCI bridge to %pR\n",
		 &bus->busn_res);

	अगर (type & IORESOURCE_IO)
		pci_setup_bridge_io(bridge);

	अगर (type & IORESOURCE_MEM)
		pci_setup_bridge_mmio(bridge);

	अगर (type & IORESOURCE_PREFETCH)
		pci_setup_bridge_mmio_pref(bridge);

	pci_ग_लिखो_config_word(bridge, PCI_BRIDGE_CONTROL, bus->bridge_ctl);
पूर्ण

व्योम __weak pcibios_setup_bridge(काष्ठा pci_bus *bus, अचिन्हित दीर्घ type)
अणु
पूर्ण

व्योम pci_setup_bridge(काष्ठा pci_bus *bus)
अणु
	अचिन्हित दीर्घ type = IORESOURCE_IO | IORESOURCE_MEM |
				  IORESOURCE_PREFETCH;

	pcibios_setup_bridge(bus, type);
	__pci_setup_bridge(bus, type);
पूर्ण


पूर्णांक pci_claim_bridge_resource(काष्ठा pci_dev *bridge, पूर्णांक i)
अणु
	अगर (i < PCI_BRIDGE_RESOURCES || i > PCI_BRIDGE_RESOURCE_END)
		वापस 0;

	अगर (pci_claim_resource(bridge, i) == 0)
		वापस 0;	/* Claimed the winकरोw */

	अगर ((bridge->class >> 8) != PCI_CLASS_BRIDGE_PCI)
		वापस 0;

	अगर (!pci_bus_clip_resource(bridge, i))
		वापस -EINVAL;	/* Clipping didn't change anything */

	चयन (i) अणु
	हाल PCI_BRIDGE_IO_WINDOW:
		pci_setup_bridge_io(bridge);
		अवरोध;
	हाल PCI_BRIDGE_MEM_WINDOW:
		pci_setup_bridge_mmio(bridge);
		अवरोध;
	हाल PCI_BRIDGE_PREF_MEM_WINDOW:
		pci_setup_bridge_mmio_pref(bridge);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (pci_claim_resource(bridge, i) == 0)
		वापस 0;	/* Claimed a smaller winकरोw */

	वापस -EINVAL;
पूर्ण

/*
 * Check whether the bridge supports optional I/O and prefetchable memory
 * ranges.  If not, the respective base/limit रेजिस्टरs must be पढ़ो-only
 * and पढ़ो as 0.
 */
अटल व्योम pci_bridge_check_ranges(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *bridge = bus->self;
	काष्ठा resource *b_res;

	b_res = &bridge->resource[PCI_BRIDGE_MEM_WINDOW];
	b_res->flags |= IORESOURCE_MEM;

	अगर (bridge->io_winकरोw) अणु
		b_res = &bridge->resource[PCI_BRIDGE_IO_WINDOW];
		b_res->flags |= IORESOURCE_IO;
	पूर्ण

	अगर (bridge->pref_winकरोw) अणु
		b_res = &bridge->resource[PCI_BRIDGE_PREF_MEM_WINDOW];
		b_res->flags |= IORESOURCE_MEM | IORESOURCE_PREFETCH;
		अगर (bridge->pref_64_winकरोw) अणु
			b_res->flags |= IORESOURCE_MEM_64 |
					PCI_PREF_RANGE_TYPE_64;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Helper function क्रम sizing routines.  Asचिन्हित resources have non-शून्य
 * parent resource.
 *
 * Return first unasचिन्हित resource of the correct type.  If there is none,
 * वापस first asचिन्हित resource of the correct type.  If none of the
 * above, वापस शून्य.
 *
 * Returning an asचिन्हित resource of the correct type allows the caller to
 * distinguish between alपढ़ोy asचिन्हित and no resource of the correct type.
 */
अटल काष्ठा resource *find_bus_resource_of_type(काष्ठा pci_bus *bus,
						  अचिन्हित दीर्घ type_mask,
						  अचिन्हित दीर्घ type)
अणु
	काष्ठा resource *r, *r_asचिन्हित = शून्य;
	पूर्णांक i;

	pci_bus_क्रम_each_resource(bus, r, i) अणु
		अगर (r == &ioport_resource || r == &iomem_resource)
			जारी;
		अगर (r && (r->flags & type_mask) == type && !r->parent)
			वापस r;
		अगर (r && (r->flags & type_mask) == type && !r_asचिन्हित)
			r_asचिन्हित = r;
	पूर्ण
	वापस r_asचिन्हित;
पूर्ण

अटल resource_माप_प्रकार calculate_iosize(resource_माप_प्रकार size,
					resource_माप_प्रकार min_size,
					resource_माप_प्रकार size1,
					resource_माप_प्रकार add_size,
					resource_माप_प्रकार children_add_size,
					resource_माप_प्रकार old_size,
					resource_माप_प्रकार align)
अणु
	अगर (size < min_size)
		size = min_size;
	अगर (old_size == 1)
		old_size = 0;
	/*
	 * To be fixed in 2.5: we should have sort of HAVE_ISA flag in the
	 * काष्ठा pci_bus.
	 */
#अगर defined(CONFIG_ISA) || defined(CONFIG_EISA)
	size = (size & 0xff) + ((size & ~0xffUL) << 2);
#पूर्ण_अगर
	size = size + size1;
	अगर (size < old_size)
		size = old_size;

	size = ALIGN(max(size, add_size) + children_add_size, align);
	वापस size;
पूर्ण

अटल resource_माप_प्रकार calculate_memsize(resource_माप_प्रकार size,
					 resource_माप_प्रकार min_size,
					 resource_माप_प्रकार add_size,
					 resource_माप_प्रकार children_add_size,
					 resource_माप_प्रकार old_size,
					 resource_माप_प्रकार align)
अणु
	अगर (size < min_size)
		size = min_size;
	अगर (old_size == 1)
		old_size = 0;
	अगर (size < old_size)
		size = old_size;

	size = ALIGN(max(size, add_size) + children_add_size, align);
	वापस size;
पूर्ण

resource_माप_प्रकार __weak pcibios_winकरोw_alignment(काष्ठा pci_bus *bus,
						अचिन्हित दीर्घ type)
अणु
	वापस 1;
पूर्ण

#घोषणा PCI_P2P_DEFAULT_MEM_ALIGN	0x100000	/* 1MiB */
#घोषणा PCI_P2P_DEFAULT_IO_ALIGN	0x1000		/* 4KiB */
#घोषणा PCI_P2P_DEFAULT_IO_ALIGN_1K	0x400		/* 1KiB */

अटल resource_माप_प्रकार winकरोw_alignment(काष्ठा pci_bus *bus, अचिन्हित दीर्घ type)
अणु
	resource_माप_प्रकार align = 1, arch_align;

	अगर (type & IORESOURCE_MEM)
		align = PCI_P2P_DEFAULT_MEM_ALIGN;
	अन्यथा अगर (type & IORESOURCE_IO) अणु
		/*
		 * Per spec, I/O winकरोws are 4K-aligned, but some bridges have
		 * an extension to support 1K alignment.
		 */
		अगर (bus->self && bus->self->io_winकरोw_1k)
			align = PCI_P2P_DEFAULT_IO_ALIGN_1K;
		अन्यथा
			align = PCI_P2P_DEFAULT_IO_ALIGN;
	पूर्ण

	arch_align = pcibios_winकरोw_alignment(bus, type);
	वापस max(align, arch_align);
पूर्ण

/**
 * pbus_size_io() - Size the I/O winकरोw of a given bus
 *
 * @bus:		The bus
 * @min_size:		The minimum I/O winकरोw that must be allocated
 * @add_size:		Additional optional I/O winकरोw
 * @पुनः_स्मृति_head:	Track the additional I/O winकरोw on this list
 *
 * Sizing the I/O winकरोws of the PCI-PCI bridge is trivial, since these
 * winकरोws have 1K or 4K granularity and the I/O ranges of non-bridge PCI
 * devices are limited to 256 bytes.  We must be careful with the ISA
 * aliasing though.
 */
अटल व्योम pbus_size_io(काष्ठा pci_bus *bus, resource_माप_प्रकार min_size,
			 resource_माप_प्रकार add_size,
			 काष्ठा list_head *पुनः_स्मृति_head)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा resource *b_res = find_bus_resource_of_type(bus, IORESOURCE_IO,
							   IORESOURCE_IO);
	resource_माप_प्रकार size = 0, size0 = 0, size1 = 0;
	resource_माप_प्रकार children_add_size = 0;
	resource_माप_प्रकार min_align, align;

	अगर (!b_res)
		वापस;

	/* If resource is alपढ़ोy asचिन्हित, nothing more to करो */
	अगर (b_res->parent)
		वापस;

	min_align = winकरोw_alignment(bus, IORESOURCE_IO);
	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
			काष्ठा resource *r = &dev->resource[i];
			अचिन्हित दीर्घ r_size;

			अगर (r->parent || !(r->flags & IORESOURCE_IO))
				जारी;
			r_size = resource_size(r);

			अगर (r_size < 0x400)
				/* Might be re-aligned क्रम ISA */
				size += r_size;
			अन्यथा
				size1 += r_size;

			align = pci_resource_alignment(dev, r);
			अगर (align > min_align)
				min_align = align;

			अगर (पुनः_स्मृति_head)
				children_add_size += get_res_add_size(पुनः_स्मृति_head, r);
		पूर्ण
	पूर्ण

	size0 = calculate_iosize(size, min_size, size1, 0, 0,
			resource_size(b_res), min_align);
	size1 = (!पुनः_स्मृति_head || (पुनः_स्मृति_head && !add_size && !children_add_size)) ? size0 :
		calculate_iosize(size, min_size, size1, add_size, children_add_size,
			resource_size(b_res), min_align);
	अगर (!size0 && !size1) अणु
		अगर (bus->self && (b_res->start || b_res->end))
			pci_info(bus->self, "disabling bridge window %pR to %pR (unused)\n",
				 b_res, &bus->busn_res);
		b_res->flags = 0;
		वापस;
	पूर्ण

	b_res->start = min_align;
	b_res->end = b_res->start + size0 - 1;
	b_res->flags |= IORESOURCE_STARTALIGN;
	अगर (bus->self && size1 > size0 && पुनः_स्मृति_head) अणु
		add_to_list(पुनः_स्मृति_head, bus->self, b_res, size1-size0,
			    min_align);
		pci_info(bus->self, "bridge window %pR to %pR add_size %llx\n",
			 b_res, &bus->busn_res,
			 (अचिन्हित दीर्घ दीर्घ) size1 - size0);
	पूर्ण
पूर्ण

अटल अंतरभूत resource_माप_प्रकार calculate_mem_align(resource_माप_प्रकार *aligns,
						  पूर्णांक max_order)
अणु
	resource_माप_प्रकार align = 0;
	resource_माप_प्रकार min_align = 0;
	पूर्णांक order;

	क्रम (order = 0; order <= max_order; order++) अणु
		resource_माप_प्रकार align1 = 1;

		align1 <<= (order + 20);

		अगर (!align)
			min_align = align1;
		अन्यथा अगर (ALIGN(align + min_align, min_align) < align1)
			min_align = align1 >> 1;
		align += aligns[order];
	पूर्ण

	वापस min_align;
पूर्ण

/**
 * pbus_size_mem() - Size the memory winकरोw of a given bus
 *
 * @bus:		The bus
 * @mask:		Mask the resource flag, then compare it with type
 * @type:		The type of मुक्त resource from bridge
 * @type2:		Second match type
 * @type3:		Third match type
 * @min_size:		The minimum memory winकरोw that must be allocated
 * @add_size:		Additional optional memory winकरोw
 * @पुनः_स्मृति_head:	Track the additional memory winकरोw on this list
 *
 * Calculate the size of the bus and minimal alignment which guarantees
 * that all child resources fit in this size.
 *
 * Return -ENOSPC अगर there's no available bus resource of the desired
 * type.  Otherwise, set the bus resource start/end to indicate the
 * required size, add things to पुनः_स्मृति_head (अगर supplied), and वापस 0.
 */
अटल पूर्णांक pbus_size_mem(काष्ठा pci_bus *bus, अचिन्हित दीर्घ mask,
			 अचिन्हित दीर्घ type, अचिन्हित दीर्घ type2,
			 अचिन्हित दीर्घ type3, resource_माप_प्रकार min_size,
			 resource_माप_प्रकार add_size,
			 काष्ठा list_head *पुनः_स्मृति_head)
अणु
	काष्ठा pci_dev *dev;
	resource_माप_प्रकार min_align, align, size, size0, size1;
	resource_माप_प्रकार aligns[18]; /* Alignments from 1MB to 128GB */
	पूर्णांक order, max_order;
	काष्ठा resource *b_res = find_bus_resource_of_type(bus,
					mask | IORESOURCE_PREFETCH, type);
	resource_माप_प्रकार children_add_size = 0;
	resource_माप_प्रकार children_add_align = 0;
	resource_माप_प्रकार add_align = 0;

	अगर (!b_res)
		वापस -ENOSPC;

	/* If resource is alपढ़ोy asचिन्हित, nothing more to करो */
	अगर (b_res->parent)
		वापस 0;

	स_रखो(aligns, 0, माप(aligns));
	max_order = 0;
	size = 0;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
			काष्ठा resource *r = &dev->resource[i];
			resource_माप_प्रकार r_size;

			अगर (r->parent || (r->flags & IORESOURCE_PCI_FIXED) ||
			    ((r->flags & mask) != type &&
			     (r->flags & mask) != type2 &&
			     (r->flags & mask) != type3))
				जारी;
			r_size = resource_size(r);
#अगर_घोषित CONFIG_PCI_IOV
			/* Put SRIOV requested res to the optional list */
			अगर (पुनः_स्मृति_head && i >= PCI_IOV_RESOURCES &&
					i <= PCI_IOV_RESOURCE_END) अणु
				add_align = max(pci_resource_alignment(dev, r), add_align);
				r->end = r->start - 1;
				add_to_list(पुनः_स्मृति_head, dev, r, r_size, 0 /* Don't care */);
				children_add_size += r_size;
				जारी;
			पूर्ण
#पूर्ण_अगर
			/*
			 * aligns[0] is क्रम 1MB (since bridge memory
			 * winकरोws are always at least 1MB aligned), so
			 * keep "order" from being negative क्रम smaller
			 * resources.
			 */
			align = pci_resource_alignment(dev, r);
			order = __ffs(align) - 20;
			अगर (order < 0)
				order = 0;
			अगर (order >= ARRAY_SIZE(aligns)) अणु
				pci_warn(dev, "disabling BAR %d: %pR (bad alignment %#llx)\n",
					 i, r, (अचिन्हित दीर्घ दीर्घ) align);
				r->flags = 0;
				जारी;
			पूर्ण
			size += max(r_size, align);
			/*
			 * Exclude ranges with size > align from calculation of
			 * the alignment.
			 */
			अगर (r_size <= align)
				aligns[order] += align;
			अगर (order > max_order)
				max_order = order;

			अगर (पुनः_स्मृति_head) अणु
				children_add_size += get_res_add_size(पुनः_स्मृति_head, r);
				children_add_align = get_res_add_align(पुनः_स्मृति_head, r);
				add_align = max(add_align, children_add_align);
			पूर्ण
		पूर्ण
	पूर्ण

	min_align = calculate_mem_align(aligns, max_order);
	min_align = max(min_align, winकरोw_alignment(bus, b_res->flags));
	size0 = calculate_memsize(size, min_size, 0, 0, resource_size(b_res), min_align);
	add_align = max(min_align, add_align);
	size1 = (!पुनः_स्मृति_head || (पुनः_स्मृति_head && !add_size && !children_add_size)) ? size0 :
		calculate_memsize(size, min_size, add_size, children_add_size,
				resource_size(b_res), add_align);
	अगर (!size0 && !size1) अणु
		अगर (bus->self && (b_res->start || b_res->end))
			pci_info(bus->self, "disabling bridge window %pR to %pR (unused)\n",
				 b_res, &bus->busn_res);
		b_res->flags = 0;
		वापस 0;
	पूर्ण
	b_res->start = min_align;
	b_res->end = size0 + min_align - 1;
	b_res->flags |= IORESOURCE_STARTALIGN;
	अगर (bus->self && size1 > size0 && पुनः_स्मृति_head) अणु
		add_to_list(पुनः_स्मृति_head, bus->self, b_res, size1-size0, add_align);
		pci_info(bus->self, "bridge window %pR to %pR add_size %llx add_align %llx\n",
			   b_res, &bus->busn_res,
			   (अचिन्हित दीर्घ दीर्घ) (size1 - size0),
			   (अचिन्हित दीर्घ दीर्घ) add_align);
	पूर्ण
	वापस 0;
पूर्ण

अचिन्हित दीर्घ pci_cardbus_resource_alignment(काष्ठा resource *res)
अणु
	अगर (res->flags & IORESOURCE_IO)
		वापस pci_cardbus_io_size;
	अगर (res->flags & IORESOURCE_MEM)
		वापस pci_cardbus_mem_size;
	वापस 0;
पूर्ण

अटल व्योम pci_bus_size_cardbus(काष्ठा pci_bus *bus,
				 काष्ठा list_head *पुनः_स्मृति_head)
अणु
	काष्ठा pci_dev *bridge = bus->self;
	काष्ठा resource *b_res;
	resource_माप_प्रकार b_res_3_size = pci_cardbus_mem_size * 2;
	u16 ctrl;

	b_res = &bridge->resource[PCI_CB_BRIDGE_IO_0_WINDOW];
	अगर (b_res->parent)
		जाओ handle_b_res_1;
	/*
	 * Reserve some resources क्रम CardBus.  We reserve a fixed amount
	 * of bus space क्रम CardBus bridges.
	 */
	b_res->start = pci_cardbus_io_size;
	b_res->end = b_res->start + pci_cardbus_io_size - 1;
	b_res->flags |= IORESOURCE_IO | IORESOURCE_STARTALIGN;
	अगर (पुनः_स्मृति_head) अणु
		b_res->end -= pci_cardbus_io_size;
		add_to_list(पुनः_स्मृति_head, bridge, b_res, pci_cardbus_io_size,
			    pci_cardbus_io_size);
	पूर्ण

handle_b_res_1:
	b_res = &bridge->resource[PCI_CB_BRIDGE_IO_1_WINDOW];
	अगर (b_res->parent)
		जाओ handle_b_res_2;
	b_res->start = pci_cardbus_io_size;
	b_res->end = b_res->start + pci_cardbus_io_size - 1;
	b_res->flags |= IORESOURCE_IO | IORESOURCE_STARTALIGN;
	अगर (पुनः_स्मृति_head) अणु
		b_res->end -= pci_cardbus_io_size;
		add_to_list(पुनः_स्मृति_head, bridge, b_res, pci_cardbus_io_size,
			    pci_cardbus_io_size);
	पूर्ण

handle_b_res_2:
	/* MEM1 must not be pref MMIO */
	pci_पढ़ो_config_word(bridge, PCI_CB_BRIDGE_CONTROL, &ctrl);
	अगर (ctrl & PCI_CB_BRIDGE_CTL_PREFETCH_MEM1) अणु
		ctrl &= ~PCI_CB_BRIDGE_CTL_PREFETCH_MEM1;
		pci_ग_लिखो_config_word(bridge, PCI_CB_BRIDGE_CONTROL, ctrl);
		pci_पढ़ो_config_word(bridge, PCI_CB_BRIDGE_CONTROL, &ctrl);
	पूर्ण

	/* Check whether prefetchable memory is supported by this bridge. */
	pci_पढ़ो_config_word(bridge, PCI_CB_BRIDGE_CONTROL, &ctrl);
	अगर (!(ctrl & PCI_CB_BRIDGE_CTL_PREFETCH_MEM0)) अणु
		ctrl |= PCI_CB_BRIDGE_CTL_PREFETCH_MEM0;
		pci_ग_लिखो_config_word(bridge, PCI_CB_BRIDGE_CONTROL, ctrl);
		pci_पढ़ो_config_word(bridge, PCI_CB_BRIDGE_CONTROL, &ctrl);
	पूर्ण

	b_res = &bridge->resource[PCI_CB_BRIDGE_MEM_0_WINDOW];
	अगर (b_res->parent)
		जाओ handle_b_res_3;
	/*
	 * If we have prefetchable memory support, allocate two regions.
	 * Otherwise, allocate one region of twice the size.
	 */
	अगर (ctrl & PCI_CB_BRIDGE_CTL_PREFETCH_MEM0) अणु
		b_res->start = pci_cardbus_mem_size;
		b_res->end = b_res->start + pci_cardbus_mem_size - 1;
		b_res->flags |= IORESOURCE_MEM | IORESOURCE_PREFETCH |
				    IORESOURCE_STARTALIGN;
		अगर (पुनः_स्मृति_head) अणु
			b_res->end -= pci_cardbus_mem_size;
			add_to_list(पुनः_स्मृति_head, bridge, b_res,
				    pci_cardbus_mem_size, pci_cardbus_mem_size);
		पूर्ण

		/* Reduce that to half */
		b_res_3_size = pci_cardbus_mem_size;
	पूर्ण

handle_b_res_3:
	b_res = &bridge->resource[PCI_CB_BRIDGE_MEM_1_WINDOW];
	अगर (b_res->parent)
		जाओ handle_करोne;
	b_res->start = pci_cardbus_mem_size;
	b_res->end = b_res->start + b_res_3_size - 1;
	b_res->flags |= IORESOURCE_MEM | IORESOURCE_STARTALIGN;
	अगर (पुनः_स्मृति_head) अणु
		b_res->end -= b_res_3_size;
		add_to_list(पुनः_स्मृति_head, bridge, b_res, b_res_3_size,
			    pci_cardbus_mem_size);
	पूर्ण

handle_करोne:
	;
पूर्ण

व्योम __pci_bus_size_bridges(काष्ठा pci_bus *bus, काष्ठा list_head *पुनः_स्मृति_head)
अणु
	काष्ठा pci_dev *dev;
	अचिन्हित दीर्घ mask, prefmask, type2 = 0, type3 = 0;
	resource_माप_प्रकार additional_io_size = 0, additional_mmio_size = 0,
			additional_mmio_pref_size = 0;
	काष्ठा resource *pref;
	काष्ठा pci_host_bridge *host;
	पूर्णांक hdr_type, i, ret;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		काष्ठा pci_bus *b = dev->subordinate;
		अगर (!b)
			जारी;

		चयन (dev->hdr_type) अणु
		हाल PCI_HEADER_TYPE_CARDBUS:
			pci_bus_size_cardbus(b, पुनः_स्मृति_head);
			अवरोध;

		हाल PCI_HEADER_TYPE_BRIDGE:
		शेष:
			__pci_bus_size_bridges(b, पुनः_स्मृति_head);
			अवरोध;
		पूर्ण
	पूर्ण

	/* The root bus? */
	अगर (pci_is_root_bus(bus)) अणु
		host = to_pci_host_bridge(bus->bridge);
		अगर (!host->size_winकरोws)
			वापस;
		pci_bus_क्रम_each_resource(bus, pref, i)
			अगर (pref && (pref->flags & IORESOURCE_PREFETCH))
				अवरोध;
		hdr_type = -1;	/* Intentionally invalid - not a PCI device. */
	पूर्ण अन्यथा अणु
		pref = &bus->self->resource[PCI_BRIDGE_PREF_MEM_WINDOW];
		hdr_type = bus->self->hdr_type;
	पूर्ण

	चयन (hdr_type) अणु
	हाल PCI_HEADER_TYPE_CARDBUS:
		/* Don't size CardBuses yet */
		अवरोध;

	हाल PCI_HEADER_TYPE_BRIDGE:
		pci_bridge_check_ranges(bus);
		अगर (bus->self->is_hotplug_bridge) अणु
			additional_io_size  = pci_hotplug_io_size;
			additional_mmio_size = pci_hotplug_mmio_size;
			additional_mmio_pref_size = pci_hotplug_mmio_pref_size;
		पूर्ण
		fallthrough;
	शेष:
		pbus_size_io(bus, पुनः_स्मृति_head ? 0 : additional_io_size,
			     additional_io_size, पुनः_स्मृति_head);

		/*
		 * If there's a 64-bit prefetchable MMIO winकरोw, compute
		 * the size required to put all 64-bit prefetchable
		 * resources in it.
		 */
		mask = IORESOURCE_MEM;
		prefmask = IORESOURCE_MEM | IORESOURCE_PREFETCH;
		अगर (pref && (pref->flags & IORESOURCE_MEM_64)) अणु
			prefmask |= IORESOURCE_MEM_64;
			ret = pbus_size_mem(bus, prefmask, prefmask,
				prefmask, prefmask,
				पुनः_स्मृति_head ? 0 : additional_mmio_pref_size,
				additional_mmio_pref_size, पुनः_स्मृति_head);

			/*
			 * If successful, all non-prefetchable resources
			 * and any 32-bit prefetchable resources will go in
			 * the non-prefetchable winकरोw.
			 */
			अगर (ret == 0) अणु
				mask = prefmask;
				type2 = prefmask & ~IORESOURCE_MEM_64;
				type3 = prefmask & ~IORESOURCE_PREFETCH;
			पूर्ण
		पूर्ण

		/*
		 * If there is no 64-bit prefetchable winकरोw, compute the
		 * size required to put all prefetchable resources in the
		 * 32-bit prefetchable winकरोw (अगर there is one).
		 */
		अगर (!type2) अणु
			prefmask &= ~IORESOURCE_MEM_64;
			ret = pbus_size_mem(bus, prefmask, prefmask,
				prefmask, prefmask,
				पुनः_स्मृति_head ? 0 : additional_mmio_pref_size,
				additional_mmio_pref_size, पुनः_स्मृति_head);

			/*
			 * If successful, only non-prefetchable resources
			 * will go in the non-prefetchable winकरोw.
			 */
			अगर (ret == 0)
				mask = prefmask;
			अन्यथा
				additional_mmio_size += additional_mmio_pref_size;

			type2 = type3 = IORESOURCE_MEM;
		पूर्ण

		/*
		 * Compute the size required to put everything अन्यथा in the
		 * non-prefetchable winकरोw. This includes:
		 *
		 *   - all non-prefetchable resources
		 *   - 32-bit prefetchable resources अगर there's a 64-bit
		 *     prefetchable winकरोw or no prefetchable winकरोw at all
		 *   - 64-bit prefetchable resources अगर there's no prefetchable
		 *     winकरोw at all
		 *
		 * Note that the strategy in __pci_assign_resource() must match
		 * that used here. Specअगरically, we cannot put a 32-bit
		 * prefetchable resource in a 64-bit prefetchable winकरोw.
		 */
		pbus_size_mem(bus, mask, IORESOURCE_MEM, type2, type3,
			      पुनः_स्मृति_head ? 0 : additional_mmio_size,
			      additional_mmio_size, पुनः_स्मृति_head);
		अवरोध;
	पूर्ण
पूर्ण

व्योम pci_bus_size_bridges(काष्ठा pci_bus *bus)
अणु
	__pci_bus_size_bridges(bus, शून्य);
पूर्ण
EXPORT_SYMBOL(pci_bus_size_bridges);

अटल व्योम assign_fixed_resource_on_bus(काष्ठा pci_bus *b, काष्ठा resource *r)
अणु
	पूर्णांक i;
	काष्ठा resource *parent_r;
	अचिन्हित दीर्घ mask = IORESOURCE_IO | IORESOURCE_MEM |
			     IORESOURCE_PREFETCH;

	pci_bus_क्रम_each_resource(b, parent_r, i) अणु
		अगर (!parent_r)
			जारी;

		अगर ((r->flags & mask) == (parent_r->flags & mask) &&
		    resource_contains(parent_r, r))
			request_resource(parent_r, r);
	पूर्ण
पूर्ण

/*
 * Try to assign any resources marked as IORESOURCE_PCI_FIXED, as they are
 * skipped by pbus_assign_resources_sorted().
 */
अटल व्योम pdev_assign_fixed_resources(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <  PCI_NUM_RESOURCES; i++) अणु
		काष्ठा pci_bus *b;
		काष्ठा resource *r = &dev->resource[i];

		अगर (r->parent || !(r->flags & IORESOURCE_PCI_FIXED) ||
		    !(r->flags & (IORESOURCE_IO | IORESOURCE_MEM)))
			जारी;

		b = dev->bus;
		जबतक (b && !r->parent) अणु
			assign_fixed_resource_on_bus(b, r);
			b = b->parent;
		पूर्ण
	पूर्ण
पूर्ण

व्योम __pci_bus_assign_resources(स्थिर काष्ठा pci_bus *bus,
				काष्ठा list_head *पुनः_स्मृति_head,
				काष्ठा list_head *fail_head)
अणु
	काष्ठा pci_bus *b;
	काष्ठा pci_dev *dev;

	pbus_assign_resources_sorted(bus, पुनः_स्मृति_head, fail_head);

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		pdev_assign_fixed_resources(dev);

		b = dev->subordinate;
		अगर (!b)
			जारी;

		__pci_bus_assign_resources(b, पुनः_स्मृति_head, fail_head);

		चयन (dev->hdr_type) अणु
		हाल PCI_HEADER_TYPE_BRIDGE:
			अगर (!pci_is_enabled(dev))
				pci_setup_bridge(b);
			अवरोध;

		हाल PCI_HEADER_TYPE_CARDBUS:
			pci_setup_cardbus(b);
			अवरोध;

		शेष:
			pci_info(dev, "not setting up bridge for bus %04x:%02x\n",
				 pci_करोमुख्य_nr(b), b->number);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम pci_bus_assign_resources(स्थिर काष्ठा pci_bus *bus)
अणु
	__pci_bus_assign_resources(bus, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL(pci_bus_assign_resources);

अटल व्योम pci_claim_device_resources(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_BRIDGE_RESOURCES; i++) अणु
		काष्ठा resource *r = &dev->resource[i];

		अगर (!r->flags || r->parent)
			जारी;

		pci_claim_resource(dev, i);
	पूर्ण
पूर्ण

अटल व्योम pci_claim_bridge_resources(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = PCI_BRIDGE_RESOURCES; i < PCI_NUM_RESOURCES; i++) अणु
		काष्ठा resource *r = &dev->resource[i];

		अगर (!r->flags || r->parent)
			जारी;

		pci_claim_bridge_resource(dev, i);
	पूर्ण
पूर्ण

अटल व्योम pci_bus_allocate_dev_resources(काष्ठा pci_bus *b)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *child;

	list_क्रम_each_entry(dev, &b->devices, bus_list) अणु
		pci_claim_device_resources(dev);

		child = dev->subordinate;
		अगर (child)
			pci_bus_allocate_dev_resources(child);
	पूर्ण
पूर्ण

अटल व्योम pci_bus_allocate_resources(काष्ठा pci_bus *b)
अणु
	काष्ठा pci_bus *child;

	/*
	 * Carry out a depth-first search on the PCI bus tree to allocate
	 * bridge apertures.  Read the programmed bridge bases and
	 * recursively claim the respective bridge resources.
	 */
	अगर (b->self) अणु
		pci_पढ़ो_bridge_bases(b);
		pci_claim_bridge_resources(b->self);
	पूर्ण

	list_क्रम_each_entry(child, &b->children, node)
		pci_bus_allocate_resources(child);
पूर्ण

व्योम pci_bus_claim_resources(काष्ठा pci_bus *b)
अणु
	pci_bus_allocate_resources(b);
	pci_bus_allocate_dev_resources(b);
पूर्ण
EXPORT_SYMBOL(pci_bus_claim_resources);

अटल व्योम __pci_bridge_assign_resources(स्थिर काष्ठा pci_dev *bridge,
					  काष्ठा list_head *add_head,
					  काष्ठा list_head *fail_head)
अणु
	काष्ठा pci_bus *b;

	pdev_assign_resources_sorted((काष्ठा pci_dev *)bridge,
					 add_head, fail_head);

	b = bridge->subordinate;
	अगर (!b)
		वापस;

	__pci_bus_assign_resources(b, add_head, fail_head);

	चयन (bridge->class >> 8) अणु
	हाल PCI_CLASS_BRIDGE_PCI:
		pci_setup_bridge(b);
		अवरोध;

	हाल PCI_CLASS_BRIDGE_CARDBUS:
		pci_setup_cardbus(b);
		अवरोध;

	शेष:
		pci_info(bridge, "not setting up bridge for bus %04x:%02x\n",
			 pci_करोमुख्य_nr(b), b->number);
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा PCI_RES_TYPE_MASK \
	(IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_PREFETCH |\
	 IORESOURCE_MEM_64)

अटल व्योम pci_bridge_release_resources(काष्ठा pci_bus *bus,
					 अचिन्हित दीर्घ type)
अणु
	काष्ठा pci_dev *dev = bus->self;
	काष्ठा resource *r;
	अचिन्हित old_flags = 0;
	काष्ठा resource *b_res;
	पूर्णांक idx = 1;

	b_res = &dev->resource[PCI_BRIDGE_RESOURCES];

	/*
	 * 1. If IO port assignment fails, release bridge IO port.
	 * 2. If non pref MMIO assignment fails, release bridge nonpref MMIO.
	 * 3. If 64bit pref MMIO assignment fails, and bridge pref is 64bit,
	 *    release bridge pref MMIO.
	 * 4. If pref MMIO assignment fails, and bridge pref is 32bit,
	 *    release bridge pref MMIO.
	 * 5. If pref MMIO assignment fails, and bridge pref is not
	 *    asचिन्हित, release bridge nonpref MMIO.
	 */
	अगर (type & IORESOURCE_IO)
		idx = 0;
	अन्यथा अगर (!(type & IORESOURCE_PREFETCH))
		idx = 1;
	अन्यथा अगर ((type & IORESOURCE_MEM_64) &&
		 (b_res[2].flags & IORESOURCE_MEM_64))
		idx = 2;
	अन्यथा अगर (!(b_res[2].flags & IORESOURCE_MEM_64) &&
		 (b_res[2].flags & IORESOURCE_PREFETCH))
		idx = 2;
	अन्यथा
		idx = 1;

	r = &b_res[idx];

	अगर (!r->parent)
		वापस;

	/* If there are children, release them all */
	release_child_resources(r);
	अगर (!release_resource(r)) अणु
		type = old_flags = r->flags & PCI_RES_TYPE_MASK;
		pci_info(dev, "resource %d %pR released\n",
			 PCI_BRIDGE_RESOURCES + idx, r);
		/* Keep the old size */
		r->end = resource_size(r) - 1;
		r->start = 0;
		r->flags = 0;

		/* Aव्योमing touch the one without PREF */
		अगर (type & IORESOURCE_PREFETCH)
			type = IORESOURCE_PREFETCH;
		__pci_setup_bridge(bus, type);
		/* For next child res under same bridge */
		r->flags = old_flags;
	पूर्ण
पूर्ण

क्रमागत release_type अणु
	leaf_only,
	whole_subtree,
पूर्ण;

/*
 * Try to release PCI bridge resources from leaf bridge, so we can allocate
 * a larger winकरोw later.
 */
अटल व्योम pci_bus_release_bridge_resources(काष्ठा pci_bus *bus,
					     अचिन्हित दीर्घ type,
					     क्रमागत release_type rel_type)
अणु
	काष्ठा pci_dev *dev;
	bool is_leaf_bridge = true;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		काष्ठा pci_bus *b = dev->subordinate;
		अगर (!b)
			जारी;

		is_leaf_bridge = false;

		अगर ((dev->class >> 8) != PCI_CLASS_BRIDGE_PCI)
			जारी;

		अगर (rel_type == whole_subtree)
			pci_bus_release_bridge_resources(b, type,
						 whole_subtree);
	पूर्ण

	अगर (pci_is_root_bus(bus))
		वापस;

	अगर ((bus->self->class >> 8) != PCI_CLASS_BRIDGE_PCI)
		वापस;

	अगर ((rel_type == whole_subtree) || is_leaf_bridge)
		pci_bridge_release_resources(bus, type);
पूर्ण

अटल व्योम pci_bus_dump_res(काष्ठा pci_bus *bus)
अणु
	काष्ठा resource *res;
	पूर्णांक i;

	pci_bus_क्रम_each_resource(bus, res, i) अणु
		अगर (!res || !res->end || !res->flags)
			जारी;

		dev_info(&bus->dev, "resource %d %pR\n", i, res);
	पूर्ण
पूर्ण

अटल व्योम pci_bus_dump_resources(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *b;
	काष्ठा pci_dev *dev;


	pci_bus_dump_res(bus);

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		b = dev->subordinate;
		अगर (!b)
			जारी;

		pci_bus_dump_resources(b);
	पूर्ण
पूर्ण

अटल पूर्णांक pci_bus_get_depth(काष्ठा pci_bus *bus)
अणु
	पूर्णांक depth = 0;
	काष्ठा pci_bus *child_bus;

	list_क्रम_each_entry(child_bus, &bus->children, node) अणु
		पूर्णांक ret;

		ret = pci_bus_get_depth(child_bus);
		अगर (ret + 1 > depth)
			depth = ret + 1;
	पूर्ण

	वापस depth;
पूर्ण

/*
 * -1: undefined, will स्वतः detect later
 *  0: disabled by user
 *  1: disabled by स्वतः detect
 *  2: enabled by user
 *  3: enabled by स्वतः detect
 */
क्रमागत enable_type अणु
	undefined = -1,
	user_disabled,
	स्वतः_disabled,
	user_enabled,
	स्वतः_enabled,
पूर्ण;

अटल क्रमागत enable_type pci_पुनः_स्मृति_enable = undefined;
व्योम __init pci_पुनः_स्मृति_get_opt(अक्षर *str)
अणु
	अगर (!म_भेदन(str, "off", 3))
		pci_पुनः_स्मृति_enable = user_disabled;
	अन्यथा अगर (!म_भेदन(str, "on", 2))
		pci_पुनः_स्मृति_enable = user_enabled;
पूर्ण
अटल bool pci_पुनः_स्मृति_enabled(क्रमागत enable_type enable)
अणु
	वापस enable >= user_enabled;
पूर्ण

#अगर defined(CONFIG_PCI_IOV) && defined(CONFIG_PCI_REALLOC_ENABLE_AUTO)
अटल पूर्णांक iov_resources_unasचिन्हित(काष्ठा pci_dev *dev, व्योम *data)
अणु
	पूर्णांक i;
	bool *unasचिन्हित = data;

	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		काष्ठा resource *r = &dev->resource[i + PCI_IOV_RESOURCES];
		काष्ठा pci_bus_region region;

		/* Not asचिन्हित or rejected by kernel? */
		अगर (!r->flags)
			जारी;

		pcibios_resource_to_bus(dev->bus, &region, r);
		अगर (!region.start) अणु
			*unasचिन्हित = true;
			वापस 1; /* Return early from pci_walk_bus() */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत enable_type pci_पुनः_स्मृति_detect(काष्ठा pci_bus *bus,
					   क्रमागत enable_type enable_local)
अणु
	bool unasचिन्हित = false;
	काष्ठा pci_host_bridge *host;

	अगर (enable_local != undefined)
		वापस enable_local;

	host = pci_find_host_bridge(bus);
	अगर (host->preserve_config)
		वापस स्वतः_disabled;

	pci_walk_bus(bus, iov_resources_unasचिन्हित, &unasचिन्हित);
	अगर (unasचिन्हित)
		वापस स्वतः_enabled;

	वापस enable_local;
पूर्ण
#अन्यथा
अटल क्रमागत enable_type pci_पुनः_स्मृति_detect(काष्ठा pci_bus *bus,
					   क्रमागत enable_type enable_local)
अणु
	वापस enable_local;
पूर्ण
#पूर्ण_अगर

/*
 * First try will not touch PCI bridge res.
 * Second and later try will clear small leaf bridge res.
 * Will stop till to the max depth अगर can not find good one.
 */
व्योम pci_assign_unasचिन्हित_root_bus_resources(काष्ठा pci_bus *bus)
अणु
	LIST_HEAD(पुनः_स्मृति_head);
	/* List of resources that want additional resources */
	काष्ठा list_head *add_list = शून्य;
	पूर्णांक tried_बार = 0;
	क्रमागत release_type rel_type = leaf_only;
	LIST_HEAD(fail_head);
	काष्ठा pci_dev_resource *fail_res;
	पूर्णांक pci_try_num = 1;
	क्रमागत enable_type enable_local;

	/* Don't पुनः_स्मृति अगर asked to करो so */
	enable_local = pci_पुनः_स्मृति_detect(bus, pci_पुनः_स्मृति_enable);
	अगर (pci_पुनः_स्मृति_enabled(enable_local)) अणु
		पूर्णांक max_depth = pci_bus_get_depth(bus);

		pci_try_num = max_depth + 1;
		dev_info(&bus->dev, "max bus depth: %d pci_try_num: %d\n",
			 max_depth, pci_try_num);
	पूर्ण

again:
	/*
	 * Last try will use add_list, otherwise will try good to have as must
	 * have, so can पुनः_स्मृति parent bridge resource
	 */
	अगर (tried_बार + 1 == pci_try_num)
		add_list = &पुनः_स्मृति_head;
	/*
	 * Depth first, calculate sizes and alignments of all subordinate buses.
	 */
	__pci_bus_size_bridges(bus, add_list);

	/* Depth last, allocate resources and update the hardware. */
	__pci_bus_assign_resources(bus, add_list, &fail_head);
	अगर (add_list)
		BUG_ON(!list_empty(add_list));
	tried_बार++;

	/* Any device complain? */
	अगर (list_empty(&fail_head))
		जाओ dump;

	अगर (tried_बार >= pci_try_num) अणु
		अगर (enable_local == undefined)
			dev_info(&bus->dev, "Some PCI device resources are unassigned, try booting with pci=realloc\n");
		अन्यथा अगर (enable_local == स्वतः_enabled)
			dev_info(&bus->dev, "Automatically enabled pci realloc, if you have problem, try booting with pci=realloc=off\n");

		मुक्त_list(&fail_head);
		जाओ dump;
	पूर्ण

	dev_info(&bus->dev, "No. %d try to assign unassigned res\n",
		 tried_बार + 1);

	/* Third बार and later will not check अगर it is leaf */
	अगर ((tried_बार + 1) > 2)
		rel_type = whole_subtree;

	/*
	 * Try to release leaf bridge's resources that doesn't fit resource of
	 * child device under that bridge.
	 */
	list_क्रम_each_entry(fail_res, &fail_head, list)
		pci_bus_release_bridge_resources(fail_res->dev->bus,
						 fail_res->flags & PCI_RES_TYPE_MASK,
						 rel_type);

	/* Restore size and flags */
	list_क्रम_each_entry(fail_res, &fail_head, list) अणु
		काष्ठा resource *res = fail_res->res;
		पूर्णांक idx;

		res->start = fail_res->start;
		res->end = fail_res->end;
		res->flags = fail_res->flags;

		अगर (pci_is_bridge(fail_res->dev)) अणु
			idx = res - &fail_res->dev->resource[0];
			अगर (idx >= PCI_BRIDGE_RESOURCES &&
			    idx <= PCI_BRIDGE_RESOURCE_END)
				res->flags = 0;
		पूर्ण
	पूर्ण
	मुक्त_list(&fail_head);

	जाओ again;

dump:
	/* Dump the resource on buses */
	pci_bus_dump_resources(bus);
पूर्ण

व्योम __init pci_assign_unasचिन्हित_resources(व्योम)
अणु
	काष्ठा pci_bus *root_bus;

	list_क्रम_each_entry(root_bus, &pci_root_buses, node) अणु
		pci_assign_unasचिन्हित_root_bus_resources(root_bus);

		/* Make sure the root bridge has a companion ACPI device */
		अगर (ACPI_HANDLE(root_bus->bridge))
			acpi_ioapic_add(ACPI_HANDLE(root_bus->bridge));
	पूर्ण
पूर्ण

अटल व्योम adjust_bridge_winकरोw(काष्ठा pci_dev *bridge, काष्ठा resource *res,
				 काष्ठा list_head *add_list,
				 resource_माप_प्रकार new_size)
अणु
	resource_माप_प्रकार add_size, size = resource_size(res);

	अगर (res->parent)
		वापस;

	अगर (!new_size)
		वापस;

	अगर (new_size > size) अणु
		add_size = new_size - size;
		pci_dbg(bridge, "bridge window %pR extended by %pa\n", res,
			&add_size);
	पूर्ण अन्यथा अगर (new_size < size) अणु
		add_size = size - new_size;
		pci_dbg(bridge, "bridge window %pR shrunken by %pa\n", res,
			&add_size);
	पूर्ण

	res->end = res->start + new_size - 1;
	हटाओ_from_list(add_list, res);
पूर्ण

अटल व्योम pci_bus_distribute_available_resources(काष्ठा pci_bus *bus,
					    काष्ठा list_head *add_list,
					    काष्ठा resource io,
					    काष्ठा resource mmio,
					    काष्ठा resource mmio_pref)
अणु
	अचिन्हित पूर्णांक normal_bridges = 0, hotplug_bridges = 0;
	काष्ठा resource *io_res, *mmio_res, *mmio_pref_res;
	काष्ठा pci_dev *dev, *bridge = bus->self;
	resource_माप_प्रकार io_per_hp, mmio_per_hp, mmio_pref_per_hp, align;

	io_res = &bridge->resource[PCI_BRIDGE_IO_WINDOW];
	mmio_res = &bridge->resource[PCI_BRIDGE_MEM_WINDOW];
	mmio_pref_res = &bridge->resource[PCI_BRIDGE_PREF_MEM_WINDOW];

	/*
	 * The alignment of this bridge is yet to be considered, hence it must
	 * be करोne now beक्रमe extending its bridge winकरोw.
	 */
	align = pci_resource_alignment(bridge, io_res);
	अगर (!io_res->parent && align)
		io.start = min(ALIGN(io.start, align), io.end + 1);

	align = pci_resource_alignment(bridge, mmio_res);
	अगर (!mmio_res->parent && align)
		mmio.start = min(ALIGN(mmio.start, align), mmio.end + 1);

	align = pci_resource_alignment(bridge, mmio_pref_res);
	अगर (!mmio_pref_res->parent && align)
		mmio_pref.start = min(ALIGN(mmio_pref.start, align),
			mmio_pref.end + 1);

	/*
	 * Now that we have adjusted क्रम alignment, update the bridge winकरोw
	 * resources to fill as much reमुख्यing resource space as possible.
	 */
	adjust_bridge_winकरोw(bridge, io_res, add_list, resource_size(&io));
	adjust_bridge_winकरोw(bridge, mmio_res, add_list, resource_size(&mmio));
	adjust_bridge_winकरोw(bridge, mmio_pref_res, add_list,
			     resource_size(&mmio_pref));

	/*
	 * Calculate how many hotplug bridges and normal bridges there
	 * are on this bus.  We will distribute the additional available
	 * resources between hotplug bridges.
	 */
	क्रम_each_pci_bridge(dev, bus) अणु
		अगर (dev->is_hotplug_bridge)
			hotplug_bridges++;
		अन्यथा
			normal_bridges++;
	पूर्ण

	/*
	 * There is only one bridge on the bus so it माला_लो all available
	 * resources which it can then distribute to the possible hotplug
	 * bridges below.
	 */
	अगर (hotplug_bridges + normal_bridges == 1) अणु
		dev = list_first_entry(&bus->devices, काष्ठा pci_dev, bus_list);
		अगर (dev->subordinate)
			pci_bus_distribute_available_resources(dev->subordinate,
				add_list, io, mmio, mmio_pref);
		वापस;
	पूर्ण

	अगर (hotplug_bridges == 0)
		वापस;

	/*
	 * Calculate the total amount of extra resource space we can
	 * pass to bridges below this one.  This is basically the
	 * extra space reduced by the minimal required space क्रम the
	 * non-hotplug bridges.
	 */
	क्रम_each_pci_bridge(dev, bus) अणु
		resource_माप_प्रकार used_size;
		काष्ठा resource *res;

		अगर (dev->is_hotplug_bridge)
			जारी;

		/*
		 * Reduce the available resource space by what the
		 * bridge and devices below it occupy.
		 */
		res = &dev->resource[PCI_BRIDGE_IO_WINDOW];
		align = pci_resource_alignment(dev, res);
		align = align ? ALIGN(io.start, align) - io.start : 0;
		used_size = align + resource_size(res);
		अगर (!res->parent)
			io.start = min(io.start + used_size, io.end + 1);

		res = &dev->resource[PCI_BRIDGE_MEM_WINDOW];
		align = pci_resource_alignment(dev, res);
		align = align ? ALIGN(mmio.start, align) - mmio.start : 0;
		used_size = align + resource_size(res);
		अगर (!res->parent)
			mmio.start = min(mmio.start + used_size, mmio.end + 1);

		res = &dev->resource[PCI_BRIDGE_PREF_MEM_WINDOW];
		align = pci_resource_alignment(dev, res);
		align = align ? ALIGN(mmio_pref.start, align) -
			mmio_pref.start : 0;
		used_size = align + resource_size(res);
		अगर (!res->parent)
			mmio_pref.start = min(mmio_pref.start + used_size,
				mmio_pref.end + 1);
	पूर्ण

	io_per_hp = भाग64_ul(resource_size(&io), hotplug_bridges);
	mmio_per_hp = भाग64_ul(resource_size(&mmio), hotplug_bridges);
	mmio_pref_per_hp = भाग64_ul(resource_size(&mmio_pref),
		hotplug_bridges);

	/*
	 * Go over devices on this bus and distribute the reमुख्यing
	 * resource space between hotplug bridges.
	 */
	क्रम_each_pci_bridge(dev, bus) अणु
		काष्ठा pci_bus *b;

		b = dev->subordinate;
		अगर (!b || !dev->is_hotplug_bridge)
			जारी;

		/*
		 * Distribute available extra resources equally between
		 * hotplug-capable करोwnstream ports taking alignment पूर्णांकo
		 * account.
		 */
		io.end = io.start + io_per_hp - 1;
		mmio.end = mmio.start + mmio_per_hp - 1;
		mmio_pref.end = mmio_pref.start + mmio_pref_per_hp - 1;

		pci_bus_distribute_available_resources(b, add_list, io, mmio,
						       mmio_pref);

		io.start += io_per_hp;
		mmio.start += mmio_per_hp;
		mmio_pref.start += mmio_pref_per_hp;
	पूर्ण
पूर्ण

अटल व्योम pci_bridge_distribute_available_resources(काष्ठा pci_dev *bridge,
						     काष्ठा list_head *add_list)
अणु
	काष्ठा resource available_io, available_mmio, available_mmio_pref;

	अगर (!bridge->is_hotplug_bridge)
		वापस;

	/* Take the initial extra resources from the hotplug port */
	available_io = bridge->resource[PCI_BRIDGE_IO_WINDOW];
	available_mmio = bridge->resource[PCI_BRIDGE_MEM_WINDOW];
	available_mmio_pref = bridge->resource[PCI_BRIDGE_PREF_MEM_WINDOW];

	pci_bus_distribute_available_resources(bridge->subordinate,
					       add_list, available_io,
					       available_mmio,
					       available_mmio_pref);
पूर्ण

व्योम pci_assign_unasचिन्हित_bridge_resources(काष्ठा pci_dev *bridge)
अणु
	काष्ठा pci_bus *parent = bridge->subordinate;
	/* List of resources that want additional resources */
	LIST_HEAD(add_list);

	पूर्णांक tried_बार = 0;
	LIST_HEAD(fail_head);
	काष्ठा pci_dev_resource *fail_res;
	पूर्णांक retval;

again:
	__pci_bus_size_bridges(parent, &add_list);

	/*
	 * Distribute reमुख्यing resources (अगर any) equally between hotplug
	 * bridges below.  This makes it possible to extend the hierarchy
	 * later without running out of resources.
	 */
	pci_bridge_distribute_available_resources(bridge, &add_list);

	__pci_bridge_assign_resources(bridge, &add_list, &fail_head);
	BUG_ON(!list_empty(&add_list));
	tried_बार++;

	अगर (list_empty(&fail_head))
		जाओ enable_all;

	अगर (tried_बार >= 2) अणु
		/* Still fail, करोn't need to try more */
		मुक्त_list(&fail_head);
		जाओ enable_all;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "PCI: No. %d try to assign unassigned res\n",
			 tried_बार + 1);

	/*
	 * Try to release leaf bridge's resources that aren't big enough
	 * to contain child device resources.
	 */
	list_क्रम_each_entry(fail_res, &fail_head, list)
		pci_bus_release_bridge_resources(fail_res->dev->bus,
						 fail_res->flags & PCI_RES_TYPE_MASK,
						 whole_subtree);

	/* Restore size and flags */
	list_क्रम_each_entry(fail_res, &fail_head, list) अणु
		काष्ठा resource *res = fail_res->res;
		पूर्णांक idx;

		res->start = fail_res->start;
		res->end = fail_res->end;
		res->flags = fail_res->flags;

		अगर (pci_is_bridge(fail_res->dev)) अणु
			idx = res - &fail_res->dev->resource[0];
			अगर (idx >= PCI_BRIDGE_RESOURCES &&
			    idx <= PCI_BRIDGE_RESOURCE_END)
				res->flags = 0;
		पूर्ण
	पूर्ण
	मुक्त_list(&fail_head);

	जाओ again;

enable_all:
	retval = pci_reenable_device(bridge);
	अगर (retval)
		pci_err(bridge, "Error reenabling bridge (%d)\n", retval);
	pci_set_master(bridge);
पूर्ण
EXPORT_SYMBOL_GPL(pci_assign_unasचिन्हित_bridge_resources);

पूर्णांक pci_reassign_bridge_resources(काष्ठा pci_dev *bridge, अचिन्हित दीर्घ type)
अणु
	काष्ठा pci_dev_resource *dev_res;
	काष्ठा pci_dev *next;
	LIST_HEAD(saved);
	LIST_HEAD(added);
	LIST_HEAD(failed);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	करोwn_पढ़ो(&pci_bus_sem);

	/* Walk to the root hub, releasing bridge BARs when possible */
	next = bridge;
	करो अणु
		bridge = next;
		क्रम (i = PCI_BRIDGE_RESOURCES; i < PCI_BRIDGE_RESOURCE_END;
		     i++) अणु
			काष्ठा resource *res = &bridge->resource[i];

			अगर ((res->flags ^ type) & PCI_RES_TYPE_MASK)
				जारी;

			/* Ignore BARs which are still in use */
			अगर (res->child)
				जारी;

			ret = add_to_list(&saved, bridge, res, 0, 0);
			अगर (ret)
				जाओ cleanup;

			pci_info(bridge, "BAR %d: releasing %pR\n",
				 i, res);

			अगर (res->parent)
				release_resource(res);
			res->start = 0;
			res->end = 0;
			अवरोध;
		पूर्ण
		अगर (i == PCI_BRIDGE_RESOURCE_END)
			अवरोध;

		next = bridge->bus ? bridge->bus->self : शून्य;
	पूर्ण जबतक (next);

	अगर (list_empty(&saved)) अणु
		up_पढ़ो(&pci_bus_sem);
		वापस -ENOENT;
	पूर्ण

	__pci_bus_size_bridges(bridge->subordinate, &added);
	__pci_bridge_assign_resources(bridge, &added, &failed);
	BUG_ON(!list_empty(&added));

	अगर (!list_empty(&failed)) अणु
		ret = -ENOSPC;
		जाओ cleanup;
	पूर्ण

	list_क्रम_each_entry(dev_res, &saved, list) अणु
		/* Skip the bridge we just asचिन्हित resources क्रम */
		अगर (bridge == dev_res->dev)
			जारी;

		bridge = dev_res->dev;
		pci_setup_bridge(bridge->subordinate);
	पूर्ण

	मुक्त_list(&saved);
	up_पढ़ो(&pci_bus_sem);
	वापस 0;

cleanup:
	/* Restore size and flags */
	list_क्रम_each_entry(dev_res, &failed, list) अणु
		काष्ठा resource *res = dev_res->res;

		res->start = dev_res->start;
		res->end = dev_res->end;
		res->flags = dev_res->flags;
	पूर्ण
	मुक्त_list(&failed);

	/* Revert to the old configuration */
	list_क्रम_each_entry(dev_res, &saved, list) अणु
		काष्ठा resource *res = dev_res->res;

		bridge = dev_res->dev;
		i = res - bridge->resource;

		res->start = dev_res->start;
		res->end = dev_res->end;
		res->flags = dev_res->flags;

		pci_claim_resource(bridge, i);
		pci_setup_bridge(bridge->subordinate);
	पूर्ण
	मुक्त_list(&saved);
	up_पढ़ो(&pci_bus_sem);

	वापस ret;
पूर्ण

व्योम pci_assign_unasचिन्हित_bus_resources(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;
	/* List of resources that want additional resources */
	LIST_HEAD(add_list);

	करोwn_पढ़ो(&pci_bus_sem);
	क्रम_each_pci_bridge(dev, bus)
		अगर (pci_has_subordinate(dev))
			__pci_bus_size_bridges(dev->subordinate, &add_list);
	up_पढ़ो(&pci_bus_sem);
	__pci_bus_assign_resources(bus, &add_list, शून्य);
	BUG_ON(!list_empty(&add_list));
पूर्ण
EXPORT_SYMBOL_GPL(pci_assign_unasचिन्हित_bus_resources);
