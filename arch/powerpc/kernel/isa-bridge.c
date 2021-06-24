<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Routines क्रम tracking a legacy ISA bridge
 *
 * Copyrigh 2007 Benjamin Herrenschmidt <benh@kernel.crashing.org>, IBM Corp.
 *
 * Some bits and pieces moved over from pci_64.c
 *
 * Copyrigh 2003 Anton Blanअक्षरd <anton@au.ibm.com>, IBM Corp.
 */

#घोषणा DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/isa-bridge.h>

अचिन्हित दीर्घ isa_io_base;	/* शून्य अगर no ISA bus */
EXPORT_SYMBOL(isa_io_base);

/* Cached ISA bridge dev. */
अटल काष्ठा device_node *isa_bridge_devnode;
काष्ठा pci_dev *isa_bridge_pcidev;
EXPORT_SYMBOL_GPL(isa_bridge_pcidev);

#घोषणा ISA_SPACE_MASK 0x1
#घोषणा ISA_SPACE_IO 0x1

अटल व्योम remap_isa_base(phys_addr_t pa, अचिन्हित दीर्घ size)
अणु
	WARN_ON_ONCE(ISA_IO_BASE & ~PAGE_MASK);
	WARN_ON_ONCE(pa & ~PAGE_MASK);
	WARN_ON_ONCE(size & ~PAGE_MASK);

	अगर (slab_is_available()) अणु
		अगर (ioremap_page_range(ISA_IO_BASE, ISA_IO_BASE + size, pa,
				pgprot_noncached(PAGE_KERNEL)))
			vunmap_range(ISA_IO_BASE, ISA_IO_BASE + size);
	पूर्ण अन्यथा अणु
		early_ioremap_range(ISA_IO_BASE, pa, size,
				pgprot_noncached(PAGE_KERNEL));
	पूर्ण
पूर्ण

अटल व्योम pci_process_ISA_OF_ranges(काष्ठा device_node *isa_node,
				      अचिन्हित दीर्घ phb_io_base_phys)
अणु
	/* We should get some saner parsing here and हटाओ these काष्ठाs */
	काष्ठा pci_address अणु
		u32 a_hi;
		u32 a_mid;
		u32 a_lo;
	पूर्ण;

	काष्ठा isa_address अणु
		u32 a_hi;
		u32 a_lo;
	पूर्ण;

	काष्ठा isa_range अणु
		काष्ठा isa_address isa_addr;
		काष्ठा pci_address pci_addr;
		अचिन्हित पूर्णांक size;
	पूर्ण;

	स्थिर काष्ठा isa_range *range;
	अचिन्हित दीर्घ pci_addr;
	अचिन्हित पूर्णांक isa_addr;
	अचिन्हित पूर्णांक size;
	पूर्णांक rlen = 0;

	range = of_get_property(isa_node, "ranges", &rlen);
	अगर (range == शून्य || (rlen < माप(काष्ठा isa_range)))
		जाओ inval_range;

	/* From "ISA Binding to 1275"
	 * The ranges property is laid out as an array of elements,
	 * each of which comprises:
	 *   cells 0 - 1:	an ISA address
	 *   cells 2 - 4:	a PCI address
	 *			(size depending on dev->n_addr_cells)
	 *   cell 5:		the size of the range
	 */
	अगर ((range->isa_addr.a_hi & ISA_SPACE_MASK) != ISA_SPACE_IO) अणु
		range++;
		rlen -= माप(काष्ठा isa_range);
		अगर (rlen < माप(काष्ठा isa_range))
			जाओ inval_range;
	पूर्ण
	अगर ((range->isa_addr.a_hi & ISA_SPACE_MASK) != ISA_SPACE_IO)
		जाओ inval_range;

	isa_addr = range->isa_addr.a_lo;
	pci_addr = (अचिन्हित दीर्घ) range->pci_addr.a_mid << 32 |
		range->pci_addr.a_lo;

	/* Assume these are both zero. Note: We could fix that and
	 * करो a proper parsing instead ... oh well, that will करो क्रम
	 * now as nobody uses fancy mappings क्रम ISA bridges
	 */
	अगर ((pci_addr != 0) || (isa_addr != 0)) अणु
		prपूर्णांकk(KERN_ERR "unexpected isa to pci mapping: %s\n",
		       __func__);
		वापस;
	पूर्ण

	/* Align size and make sure it's cropped to 64K */
	size = PAGE_ALIGN(range->size);
	अगर (size > 0x10000)
		size = 0x10000;

	remap_isa_base(phb_io_base_phys, size);
	वापस;

inval_range:
	prपूर्णांकk(KERN_ERR "no ISA IO ranges or unexpected isa range, "
	       "mapping 64k\n");
	remap_isa_base(phb_io_base_phys, 0x10000);
पूर्ण


/**
 * isa_bridge_find_early - Find and map the ISA IO space early beक्रमe
 *                         मुख्य PCI discovery. This is optionally called by
 *                         the arch code when adding PCI PHBs to get early
 *                         access to ISA IO ports
 */
व्योम __init isa_bridge_find_early(काष्ठा pci_controller *hose)
अणु
	काष्ठा device_node *np, *parent = शून्य, *पंचांगp;

	/* If we alपढ़ोy have an ISA bridge, bail off */
	अगर (isa_bridge_devnode != शून्य)
		वापस;

	/* For each "isa" node in the प्रणाली. Note : we करो a search by
	 * type and not by name. It might be better to करो by name but that's
	 * what the code used to करो and I करोn't want to अवरोध too much at
	 * once. We can look पूर्णांकo changing that separately
	 */
	क्रम_each_node_by_type(np, "isa") अणु
		/* Look क्रम our hose being a parent */
		क्रम (parent = of_get_parent(np); parent;) अणु
			अगर (parent == hose->dn) अणु
				of_node_put(parent);
				अवरोध;
			पूर्ण
			पंचांगp = parent;
			parent = of_get_parent(parent);
			of_node_put(पंचांगp);
		पूर्ण
		अगर (parent != शून्य)
			अवरोध;
	पूर्ण
	अगर (np == शून्य)
		वापस;
	isa_bridge_devnode = np;

	/* Now parse the "ranges" property and setup the ISA mapping */
	pci_process_ISA_OF_ranges(np, hose->io_base_phys);

	/* Set the global ISA io base to indicate we have an ISA bridge */
	isa_io_base = ISA_IO_BASE;

	pr_debug("ISA bridge (early) is %pOF\n", np);
पूर्ण

/**
 * isa_bridge_find_early - Find and map the ISA IO space early beक्रमe
 *                         मुख्य PCI discovery. This is optionally called by
 *                         the arch code when adding PCI PHBs to get early
 *                         access to ISA IO ports
 */
व्योम __init isa_bridge_init_non_pci(काष्ठा device_node *np)
अणु
	स्थिर __be32 *ranges, *pbasep = शून्य;
	पूर्णांक rlen, i, rs;
	u32 na, ns, pna;
	u64 cbase, pbase, size = 0;

	/* If we alपढ़ोy have an ISA bridge, bail off */
	अगर (isa_bridge_devnode != शून्य)
		वापस;

	pna = of_n_addr_cells(np);
	अगर (of_property_पढ़ो_u32(np, "#address-cells", &na) ||
	    of_property_पढ़ो_u32(np, "#size-cells", &ns)) अणु
		pr_warn("ISA: Non-PCI bridge %pOF is missing address format\n",
			np);
		वापस;
	पूर्ण

	/* Check it's a supported address क्रमmat */
	अगर (na != 2 || ns != 1) अणु
		pr_warn("ISA: Non-PCI bridge %pOF has unsupported address format\n",
			np);
		वापस;
	पूर्ण
	rs = na + ns + pna;

	/* Grab the ranges property */
	ranges = of_get_property(np, "ranges", &rlen);
	अगर (ranges == शून्य || rlen < rs) अणु
		pr_warn("ISA: Non-PCI bridge %pOF has absent or invalid ranges\n",
			np);
		वापस;
	पूर्ण

	/* Parse it. We are only looking क्रम IO space */
	क्रम (i = 0; (i + rs - 1) < rlen; i += rs) अणु
		अगर (be32_to_cpup(ranges + i) != 1)
			जारी;
		cbase = be32_to_cpup(ranges + i + 1);
		size = of_पढ़ो_number(ranges + i + na + pna, ns);
		pbasep = ranges + i + na;
		अवरोध;
	पूर्ण

	/* Got something ? */
	अगर (!size || !pbasep) अणु
		pr_warn("ISA: Non-PCI bridge %pOF has no usable IO range\n",
			np);
		वापस;
	पूर्ण

	/* Align size and make sure it's cropped to 64K */
	size = PAGE_ALIGN(size);
	अगर (size > 0x10000)
		size = 0x10000;

	/* Map pbase */
	pbase = of_translate_address(np, pbasep);
	अगर (pbase == OF_BAD_ADDR) अणु
		pr_warn("ISA: Non-PCI bridge %pOF failed to translate IO base\n",
			np);
		वापस;
	पूर्ण

	/* We need page alignment */
	अगर ((cbase & ~PAGE_MASK) || (pbase & ~PAGE_MASK)) अणु
		pr_warn("ISA: Non-PCI bridge %pOF has non aligned IO range\n",
			np);
		वापस;
	पूर्ण

	/* Got it */
	isa_bridge_devnode = np;

	/* Set the global ISA io base to indicate we have an ISA bridge
	 * and map it
	 */
	isa_io_base = ISA_IO_BASE;
	remap_isa_base(pbase, size);

	pr_debug("ISA: Non-PCI bridge is %pOF\n", np);
पूर्ण

/**
 * isa_bridge_find_late - Find and map the ISA IO space upon discovery of
 *                        a new ISA bridge
 */
अटल व्योम isa_bridge_find_late(काष्ठा pci_dev *pdev,
				 काष्ठा device_node *devnode)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(pdev->bus);

	/* Store ISA device node and PCI device */
	isa_bridge_devnode = of_node_get(devnode);
	isa_bridge_pcidev = pdev;

	/* Now parse the "ranges" property and setup the ISA mapping */
	pci_process_ISA_OF_ranges(devnode, hose->io_base_phys);

	/* Set the global ISA io base to indicate we have an ISA bridge */
	isa_io_base = ISA_IO_BASE;

	pr_debug("ISA bridge (late) is %pOF on %s\n",
		 devnode, pci_name(pdev));
पूर्ण

/**
 * isa_bridge_हटाओ - Remove/unmap an ISA bridge
 */
अटल व्योम isa_bridge_हटाओ(व्योम)
अणु
	pr_debug("ISA bridge removed !\n");

	/* Clear the global ISA io base to indicate that we have no more
	 * ISA bridge. Note that drivers करोn't quite handle that, though
	 * we should probably करो something about it. But करो we ever really
	 * have ISA bridges being हटाओd on machines using legacy devices ?
	 */
	isa_io_base = ISA_IO_BASE;

	/* Clear references to the bridge */
	of_node_put(isa_bridge_devnode);
	isa_bridge_devnode = शून्य;
	isa_bridge_pcidev = शून्य;

	/* Unmap the ISA area */
	vunmap_range(ISA_IO_BASE, ISA_IO_BASE + 0x10000);
पूर्ण

/**
 * isa_bridge_notअगरy - Get notअगरied of PCI devices addition/removal
 */
अटल पूर्णांक isa_bridge_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			     व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा device_node *devnode = pci_device_to_OF_node(pdev);

	चयन(action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		/* Check अगर we have an early ISA device, without PCI dev */
		अगर (isa_bridge_devnode && isa_bridge_devnode == devnode &&
		    !isa_bridge_pcidev) अणु
			pr_debug("ISA bridge PCI attached: %s\n",
				 pci_name(pdev));
			isa_bridge_pcidev = pdev;
		पूर्ण

		/* Check अगर we have no ISA device, and this happens to be one,
		 * रेजिस्टर it as such अगर it has an OF device
		 */
		अगर (!isa_bridge_devnode && of_node_is_type(devnode, "isa"))
			isa_bridge_find_late(pdev, devnode);

		वापस 0;
	हाल BUS_NOTIFY_DEL_DEVICE:
		/* Check अगर this our existing ISA device */
		अगर (pdev == isa_bridge_pcidev ||
		    (devnode && devnode == isa_bridge_devnode))
			isa_bridge_हटाओ();
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block isa_bridge_notअगरier = अणु
	.notअगरier_call = isa_bridge_notअगरy
पूर्ण;

/**
 * isa_bridge_init - रेजिस्टर to be notअगरied of ISA bridge addition/removal
 *
 */
अटल पूर्णांक __init isa_bridge_init(व्योम)
अणु
	bus_रेजिस्टर_notअगरier(&pci_bus_type, &isa_bridge_notअगरier);
	वापस 0;
पूर्ण
arch_initcall(isa_bridge_init);
