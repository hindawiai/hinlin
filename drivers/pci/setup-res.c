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
 * Fixed क्रम multiple PCI buses, 1999 Andrea Arcangeli <andrea@suse.de>
 *
 * Nov 2000, Ivan Kokshaysky <ink@jurassic.park.msu.ru>
 *	     Resource sorting
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/cache.h>
#समावेश <linux/slab.h>
#समावेश "pci.h"

अटल व्योम pci_std_update_resource(काष्ठा pci_dev *dev, पूर्णांक resno)
अणु
	काष्ठा pci_bus_region region;
	bool disable;
	u16 cmd;
	u32 new, check, mask;
	पूर्णांक reg;
	काष्ठा resource *res = dev->resource + resno;

	/* Per SR-IOV spec 3.4.1.11, VF BARs are RO zero */
	अगर (dev->is_virtfn)
		वापस;

	/*
	 * Ignore resources क्रम unimplemented BARs and unused resource slots
	 * क्रम 64 bit BARs.
	 */
	अगर (!res->flags)
		वापस;

	अगर (res->flags & IORESOURCE_UNSET)
		वापस;

	/*
	 * Ignore non-moveable resources.  This might be legacy resources क्रम
	 * which no functional BAR रेजिस्टर exists or another important
	 * प्रणाली resource we shouldn't move around.
	 */
	अगर (res->flags & IORESOURCE_PCI_FIXED)
		वापस;

	pcibios_resource_to_bus(dev->bus, &region, res);
	new = region.start;

	अगर (res->flags & IORESOURCE_IO) अणु
		mask = (u32)PCI_BASE_ADDRESS_IO_MASK;
		new |= res->flags & ~PCI_BASE_ADDRESS_IO_MASK;
	पूर्ण अन्यथा अगर (resno == PCI_ROM_RESOURCE) अणु
		mask = PCI_ROM_ADDRESS_MASK;
	पूर्ण अन्यथा अणु
		mask = (u32)PCI_BASE_ADDRESS_MEM_MASK;
		new |= res->flags & ~PCI_BASE_ADDRESS_MEM_MASK;
	पूर्ण

	अगर (resno < PCI_ROM_RESOURCE) अणु
		reg = PCI_BASE_ADDRESS_0 + 4 * resno;
	पूर्ण अन्यथा अगर (resno == PCI_ROM_RESOURCE) अणु

		/*
		 * Apparently some Matrox devices have ROM BARs that पढ़ो
		 * as zero when disabled, so करोn't update ROM BARs unless
		 * they're enabled.  See
		 * https://lore.kernel.org/r/43147B3D.1030309@vc.cvut.cz/
		 */
		अगर (!(res->flags & IORESOURCE_ROM_ENABLE))
			वापस;

		reg = dev->rom_base_reg;
		new |= PCI_ROM_ADDRESS_ENABLE;
	पूर्ण अन्यथा
		वापस;

	/*
	 * We can't update a 64-bit BAR atomically, so when possible,
	 * disable decoding so that a half-updated BAR won't conflict
	 * with another device.
	 */
	disable = (res->flags & IORESOURCE_MEM_64) && !dev->mmio_always_on;
	अगर (disable) अणु
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
		pci_ग_लिखो_config_word(dev, PCI_COMMAND,
				      cmd & ~PCI_COMMAND_MEMORY);
	पूर्ण

	pci_ग_लिखो_config_dword(dev, reg, new);
	pci_पढ़ो_config_dword(dev, reg, &check);

	अगर ((new ^ check) & mask) अणु
		pci_err(dev, "BAR %d: error updating (%#08x != %#08x)\n",
			resno, new, check);
	पूर्ण

	अगर (res->flags & IORESOURCE_MEM_64) अणु
		new = region.start >> 16 >> 16;
		pci_ग_लिखो_config_dword(dev, reg + 4, new);
		pci_पढ़ो_config_dword(dev, reg + 4, &check);
		अगर (check != new) अणु
			pci_err(dev, "BAR %d: error updating (high %#08x != %#08x)\n",
				resno, new, check);
		पूर्ण
	पूर्ण

	अगर (disable)
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
पूर्ण

व्योम pci_update_resource(काष्ठा pci_dev *dev, पूर्णांक resno)
अणु
	अगर (resno <= PCI_ROM_RESOURCE)
		pci_std_update_resource(dev, resno);
#अगर_घोषित CONFIG_PCI_IOV
	अन्यथा अगर (resno >= PCI_IOV_RESOURCES && resno <= PCI_IOV_RESOURCE_END)
		pci_iov_update_resource(dev, resno);
#पूर्ण_अगर
पूर्ण

पूर्णांक pci_claim_resource(काष्ठा pci_dev *dev, पूर्णांक resource)
अणु
	काष्ठा resource *res = &dev->resource[resource];
	काष्ठा resource *root, *conflict;

	अगर (res->flags & IORESOURCE_UNSET) अणु
		pci_info(dev, "can't claim BAR %d %pR: no address assigned\n",
			 resource, res);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If we have a shaकरोw copy in RAM, the PCI device करोesn't respond
	 * to the shaकरोw range, so we करोn't need to claim it, and upstream
	 * bridges करोn't need to route the range to the device.
	 */
	अगर (res->flags & IORESOURCE_ROM_SHADOW)
		वापस 0;

	root = pci_find_parent_resource(dev, res);
	अगर (!root) अणु
		pci_info(dev, "can't claim BAR %d %pR: no compatible bridge window\n",
			 resource, res);
		res->flags |= IORESOURCE_UNSET;
		वापस -EINVAL;
	पूर्ण

	conflict = request_resource_conflict(root, res);
	अगर (conflict) अणु
		pci_info(dev, "can't claim BAR %d %pR: address conflict with %s %pR\n",
			 resource, res, conflict->name, conflict);
		res->flags |= IORESOURCE_UNSET;
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pci_claim_resource);

व्योम pci_disable_bridge_winकरोw(काष्ठा pci_dev *dev)
अणु
	/* MMIO Base/Limit */
	pci_ग_लिखो_config_dword(dev, PCI_MEMORY_BASE, 0x0000fff0);

	/* Prefetchable MMIO Base/Limit */
	pci_ग_लिखो_config_dword(dev, PCI_PREF_LIMIT_UPPER32, 0);
	pci_ग_लिखो_config_dword(dev, PCI_PREF_MEMORY_BASE, 0x0000fff0);
	pci_ग_लिखो_config_dword(dev, PCI_PREF_BASE_UPPER32, 0xffffffff);
पूर्ण

/*
 * Generic function that वापसs a value indicating that the device's
 * original BIOS BAR address was not saved and so is not available क्रम
 * reinstatement.
 *
 * Can be over-ridden by architecture specअगरic code that implements
 * reinstatement functionality rather than leaving it disabled when
 * normal allocation attempts fail.
 */
resource_माप_प्रकार __weak pcibios_retrieve_fw_addr(काष्ठा pci_dev *dev, पूर्णांक idx)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pci_revert_fw_address(काष्ठा resource *res, काष्ठा pci_dev *dev,
		पूर्णांक resno, resource_माप_प्रकार size)
अणु
	काष्ठा resource *root, *conflict;
	resource_माप_प्रकार fw_addr, start, end;

	fw_addr = pcibios_retrieve_fw_addr(dev, resno);
	अगर (!fw_addr)
		वापस -ENOMEM;

	start = res->start;
	end = res->end;
	res->start = fw_addr;
	res->end = res->start + size - 1;
	res->flags &= ~IORESOURCE_UNSET;

	root = pci_find_parent_resource(dev, res);
	अगर (!root) अणु
		अगर (res->flags & IORESOURCE_IO)
			root = &ioport_resource;
		अन्यथा
			root = &iomem_resource;
	पूर्ण

	pci_info(dev, "BAR %d: trying firmware assignment %pR\n",
		 resno, res);
	conflict = request_resource_conflict(root, res);
	अगर (conflict) अणु
		pci_info(dev, "BAR %d: %pR conflicts with %s %pR\n",
			 resno, res, conflict->name, conflict);
		res->start = start;
		res->end = end;
		res->flags |= IORESOURCE_UNSET;
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * We करोn't have to worry about legacy ISA devices, so nothing to करो here.
 * This is marked as __weak because multiple architectures define it; it should
 * eventually go away.
 */
resource_माप_प्रकार __weak pcibios_align_resource(व्योम *data,
					      स्थिर काष्ठा resource *res,
					      resource_माप_प्रकार size,
					      resource_माप_प्रकार align)
अणु
       वापस res->start;
पूर्ण

अटल पूर्णांक __pci_assign_resource(काष्ठा pci_bus *bus, काष्ठा pci_dev *dev,
		पूर्णांक resno, resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा resource *res = dev->resource + resno;
	resource_माप_प्रकार min;
	पूर्णांक ret;

	min = (res->flags & IORESOURCE_IO) ? PCIBIOS_MIN_IO : PCIBIOS_MIN_MEM;

	/*
	 * First, try exact prefetching match.  Even अगर a 64-bit
	 * prefetchable bridge winकरोw is below 4GB, we can't put a 32-bit
	 * prefetchable resource in it because pbus_size_mem() assumes a
	 * 64-bit winकरोw will contain no 32-bit resources.  If we assign
	 * things dअगरferently than they were sized, not everything will fit.
	 */
	ret = pci_bus_alloc_resource(bus, res, size, align, min,
				     IORESOURCE_PREFETCH | IORESOURCE_MEM_64,
				     pcibios_align_resource, dev);
	अगर (ret == 0)
		वापस 0;

	/*
	 * If the prefetchable winकरोw is only 32 bits wide, we can put
	 * 64-bit prefetchable resources in it.
	 */
	अगर ((res->flags & (IORESOURCE_PREFETCH | IORESOURCE_MEM_64)) ==
	     (IORESOURCE_PREFETCH | IORESOURCE_MEM_64)) अणु
		ret = pci_bus_alloc_resource(bus, res, size, align, min,
					     IORESOURCE_PREFETCH,
					     pcibios_align_resource, dev);
		अगर (ret == 0)
			वापस 0;
	पूर्ण

	/*
	 * If we didn't find a better match, we can put any memory resource
	 * in a non-prefetchable winकरोw.  If this resource is 32 bits and
	 * non-prefetchable, the first call alपढ़ोy tried the only possibility
	 * so we करोn't need to try again.
	 */
	अगर (res->flags & (IORESOURCE_PREFETCH | IORESOURCE_MEM_64))
		ret = pci_bus_alloc_resource(bus, res, size, align, min, 0,
					     pcibios_align_resource, dev);

	वापस ret;
पूर्ण

अटल पूर्णांक _pci_assign_resource(काष्ठा pci_dev *dev, पूर्णांक resno,
				resource_माप_प्रकार size, resource_माप_प्रकार min_align)
अणु
	काष्ठा pci_bus *bus;
	पूर्णांक ret;

	bus = dev->bus;
	जबतक ((ret = __pci_assign_resource(bus, dev, resno, size, min_align))) अणु
		अगर (!bus->parent || !bus->self->transparent)
			अवरोध;
		bus = bus->parent;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक pci_assign_resource(काष्ठा pci_dev *dev, पूर्णांक resno)
अणु
	काष्ठा resource *res = dev->resource + resno;
	resource_माप_प्रकार align, size;
	पूर्णांक ret;

	अगर (res->flags & IORESOURCE_PCI_FIXED)
		वापस 0;

	res->flags |= IORESOURCE_UNSET;
	align = pci_resource_alignment(dev, res);
	अगर (!align) अणु
		pci_info(dev, "BAR %d: can't assign %pR (bogus alignment)\n",
			 resno, res);
		वापस -EINVAL;
	पूर्ण

	size = resource_size(res);
	ret = _pci_assign_resource(dev, resno, size, align);

	/*
	 * If we failed to assign anything, let's try the address
	 * where firmware left it.  That at least has a chance of
	 * working, which is better than just leaving it disabled.
	 */
	अगर (ret < 0) अणु
		pci_info(dev, "BAR %d: no space for %pR\n", resno, res);
		ret = pci_revert_fw_address(res, dev, resno, size);
	पूर्ण

	अगर (ret < 0) अणु
		pci_info(dev, "BAR %d: failed to assign %pR\n", resno, res);
		वापस ret;
	पूर्ण

	res->flags &= ~IORESOURCE_UNSET;
	res->flags &= ~IORESOURCE_STARTALIGN;
	pci_info(dev, "BAR %d: assigned %pR\n", resno, res);
	अगर (resno < PCI_BRIDGE_RESOURCES)
		pci_update_resource(dev, resno);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pci_assign_resource);

पूर्णांक pci_reassign_resource(काष्ठा pci_dev *dev, पूर्णांक resno, resource_माप_प्रकार addsize,
			resource_माप_प्रकार min_align)
अणु
	काष्ठा resource *res = dev->resource + resno;
	अचिन्हित दीर्घ flags;
	resource_माप_प्रकार new_size;
	पूर्णांक ret;

	अगर (res->flags & IORESOURCE_PCI_FIXED)
		वापस 0;

	flags = res->flags;
	res->flags |= IORESOURCE_UNSET;
	अगर (!res->parent) अणु
		pci_info(dev, "BAR %d: can't reassign an unassigned resource %pR\n",
			 resno, res);
		वापस -EINVAL;
	पूर्ण

	/* alपढ़ोy aligned with min_align */
	new_size = resource_size(res) + addsize;
	ret = _pci_assign_resource(dev, resno, new_size, min_align);
	अगर (ret) अणु
		res->flags = flags;
		pci_info(dev, "BAR %d: %pR (failed to expand by %#llx)\n",
			 resno, res, (अचिन्हित दीर्घ दीर्घ) addsize);
		वापस ret;
	पूर्ण

	res->flags &= ~IORESOURCE_UNSET;
	res->flags &= ~IORESOURCE_STARTALIGN;
	pci_info(dev, "BAR %d: reassigned %pR (expanded by %#llx)\n",
		 resno, res, (अचिन्हित दीर्घ दीर्घ) addsize);
	अगर (resno < PCI_BRIDGE_RESOURCES)
		pci_update_resource(dev, resno);

	वापस 0;
पूर्ण

व्योम pci_release_resource(काष्ठा pci_dev *dev, पूर्णांक resno)
अणु
	काष्ठा resource *res = dev->resource + resno;

	pci_info(dev, "BAR %d: releasing %pR\n", resno, res);

	अगर (!res->parent)
		वापस;

	release_resource(res);
	res->end = resource_size(res) - 1;
	res->start = 0;
	res->flags |= IORESOURCE_UNSET;
पूर्ण
EXPORT_SYMBOL(pci_release_resource);

पूर्णांक pci_resize_resource(काष्ठा pci_dev *dev, पूर्णांक resno, पूर्णांक size)
अणु
	काष्ठा resource *res = dev->resource + resno;
	काष्ठा pci_host_bridge *host;
	पूर्णांक old, ret;
	u32 sizes;
	u16 cmd;

	/* Check अगर we must preserve the firmware's resource assignment */
	host = pci_find_host_bridge(dev->bus);
	अगर (host->preserve_config)
		वापस -ENOTSUPP;

	/* Make sure the resource isn't asचिन्हित beक्रमe resizing it. */
	अगर (!(res->flags & IORESOURCE_UNSET))
		वापस -EBUSY;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	अगर (cmd & PCI_COMMAND_MEMORY)
		वापस -EBUSY;

	sizes = pci_rebar_get_possible_sizes(dev, resno);
	अगर (!sizes)
		वापस -ENOTSUPP;

	अगर (!(sizes & BIT(size)))
		वापस -EINVAL;

	old = pci_rebar_get_current_size(dev, resno);
	अगर (old < 0)
		वापस old;

	ret = pci_rebar_set_size(dev, resno, size);
	अगर (ret)
		वापस ret;

	res->end = res->start + pci_rebar_माप_प्रकारo_bytes(size) - 1;

	/* Check अगर the new config works by trying to assign everything. */
	अगर (dev->bus->self) अणु
		ret = pci_reassign_bridge_resources(dev->bus->self, res->flags);
		अगर (ret)
			जाओ error_resize;
	पूर्ण
	वापस 0;

error_resize:
	pci_rebar_set_size(dev, resno, old);
	res->end = res->start + pci_rebar_माप_प्रकारo_bytes(old) - 1;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pci_resize_resource);

पूर्णांक pci_enable_resources(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	u16 cmd, old_cmd;
	पूर्णांक i;
	काष्ठा resource *r;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	old_cmd = cmd;

	क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
		अगर (!(mask & (1 << i)))
			जारी;

		r = &dev->resource[i];

		अगर (!(r->flags & (IORESOURCE_IO | IORESOURCE_MEM)))
			जारी;
		अगर ((i == PCI_ROM_RESOURCE) &&
				(!(r->flags & IORESOURCE_ROM_ENABLE)))
			जारी;

		अगर (r->flags & IORESOURCE_UNSET) अणु
			pci_err(dev, "can't enable device: BAR %d %pR not assigned\n",
				i, r);
			वापस -EINVAL;
		पूर्ण

		अगर (!r->parent) अणु
			pci_err(dev, "can't enable device: BAR %d %pR not claimed\n",
				i, r);
			वापस -EINVAL;
		पूर्ण

		अगर (r->flags & IORESOURCE_IO)
			cmd |= PCI_COMMAND_IO;
		अगर (r->flags & IORESOURCE_MEM)
			cmd |= PCI_COMMAND_MEMORY;
	पूर्ण

	अगर (cmd != old_cmd) अणु
		pci_info(dev, "enabling device (%04x -> %04x)\n", old_cmd, cmd);
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
	वापस 0;
पूर्ण
