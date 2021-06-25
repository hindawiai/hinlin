<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt)	"OF: " fmt

#समावेश <linux/device.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/logic_pपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/dma-direct.h> /* क्रम bus_dma_region */

#समावेश "of_private.h"

/* Max address size we deal with */
#घोषणा OF_MAX_ADDR_CELLS	4
#घोषणा OF_CHECK_ADDR_COUNT(na)	((na) > 0 && (na) <= OF_MAX_ADDR_CELLS)
#घोषणा OF_CHECK_COUNTS(na, ns)	(OF_CHECK_ADDR_COUNT(na) && (ns) > 0)

अटल काष्ठा of_bus *of_match_bus(काष्ठा device_node *np);
अटल पूर्णांक __of_address_to_resource(काष्ठा device_node *dev,
		स्थिर __be32 *addrp, u64 size, अचिन्हित पूर्णांक flags,
		स्थिर अक्षर *name, काष्ठा resource *r);
अटल bool of_mmio_is_nonposted(काष्ठा device_node *np);

/* Debug utility */
#अगर_घोषित DEBUG
अटल व्योम of_dump_addr(स्थिर अक्षर *s, स्थिर __be32 *addr, पूर्णांक na)
अणु
	pr_debug("%s", s);
	जबतक (na--)
		pr_cont(" %08x", be32_to_cpu(*(addr++)));
	pr_cont("\n");
पूर्ण
#अन्यथा
अटल व्योम of_dump_addr(स्थिर अक्षर *s, स्थिर __be32 *addr, पूर्णांक na) अणु पूर्ण
#पूर्ण_अगर

/* Callbacks क्रम bus specअगरic translators */
काष्ठा of_bus अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*addresses;
	पूर्णांक		(*match)(काष्ठा device_node *parent);
	व्योम		(*count_cells)(काष्ठा device_node *child,
				       पूर्णांक *addrc, पूर्णांक *sizec);
	u64		(*map)(__be32 *addr, स्थिर __be32 *range,
				पूर्णांक na, पूर्णांक ns, पूर्णांक pna);
	पूर्णांक		(*translate)(__be32 *addr, u64 offset, पूर्णांक na);
	bool	has_flags;
	अचिन्हित पूर्णांक	(*get_flags)(स्थिर __be32 *addr);
पूर्ण;

/*
 * Default translator (generic bus)
 */

अटल व्योम of_bus_शेष_count_cells(काष्ठा device_node *dev,
				       पूर्णांक *addrc, पूर्णांक *sizec)
अणु
	अगर (addrc)
		*addrc = of_n_addr_cells(dev);
	अगर (sizec)
		*sizec = of_n_size_cells(dev);
पूर्ण

अटल u64 of_bus_शेष_map(__be32 *addr, स्थिर __be32 *range,
		पूर्णांक na, पूर्णांक ns, पूर्णांक pna)
अणु
	u64 cp, s, da;

	cp = of_पढ़ो_number(range, na);
	s  = of_पढ़ो_number(range + na + pna, ns);
	da = of_पढ़ो_number(addr, na);

	pr_debug("default map, cp=%llx, s=%llx, da=%llx\n",
		 (अचिन्हित दीर्घ दीर्घ)cp, (अचिन्हित दीर्घ दीर्घ)s,
		 (अचिन्हित दीर्घ दीर्घ)da);

	अगर (da < cp || da >= (cp + s))
		वापस OF_BAD_ADDR;
	वापस da - cp;
पूर्ण

अटल पूर्णांक of_bus_शेष_translate(__be32 *addr, u64 offset, पूर्णांक na)
अणु
	u64 a = of_पढ़ो_number(addr, na);
	स_रखो(addr, 0, na * 4);
	a += offset;
	अगर (na > 1)
		addr[na - 2] = cpu_to_be32(a >> 32);
	addr[na - 1] = cpu_to_be32(a & 0xffffffffu);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक of_bus_शेष_get_flags(स्थिर __be32 *addr)
अणु
	वापस IORESOURCE_MEM;
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल अचिन्हित पूर्णांक of_bus_pci_get_flags(स्थिर __be32 *addr)
अणु
	अचिन्हित पूर्णांक flags = 0;
	u32 w = be32_to_cpup(addr);

	अगर (!IS_ENABLED(CONFIG_PCI))
		वापस 0;

	चयन((w >> 24) & 0x03) अणु
	हाल 0x01:
		flags |= IORESOURCE_IO;
		अवरोध;
	हाल 0x02: /* 32 bits */
		flags |= IORESOURCE_MEM;
		अवरोध;

	हाल 0x03: /* 64 bits */
		flags |= IORESOURCE_MEM | IORESOURCE_MEM_64;
		अवरोध;
	पूर्ण
	अगर (w & 0x40000000)
		flags |= IORESOURCE_PREFETCH;
	वापस flags;
पूर्ण

/*
 * PCI bus specअगरic translator
 */

अटल bool of_node_is_pcie(काष्ठा device_node *np)
अणु
	bool is_pcie = of_node_name_eq(np, "pcie");

	अगर (is_pcie)
		pr_warn_once("%pOF: Missing device_type\n", np);

	वापस is_pcie;
पूर्ण

अटल पूर्णांक of_bus_pci_match(काष्ठा device_node *np)
अणु
	/*
 	 * "pciex" is PCI Express
	 * "vci" is क्रम the /chaos bridge on 1st-gen PCI घातermacs
	 * "ht" is hypertransport
	 *
	 * If none of the device_type match, and that the node name is
	 * "pcie", accept the device as PCI (with a warning).
	 */
	वापस of_node_is_type(np, "pci") || of_node_is_type(np, "pciex") ||
		of_node_is_type(np, "vci") || of_node_is_type(np, "ht") ||
		of_node_is_pcie(np);
पूर्ण

अटल व्योम of_bus_pci_count_cells(काष्ठा device_node *np,
				   पूर्णांक *addrc, पूर्णांक *sizec)
अणु
	अगर (addrc)
		*addrc = 3;
	अगर (sizec)
		*sizec = 2;
पूर्ण

अटल u64 of_bus_pci_map(__be32 *addr, स्थिर __be32 *range, पूर्णांक na, पूर्णांक ns,
		पूर्णांक pna)
अणु
	u64 cp, s, da;
	अचिन्हित पूर्णांक af, rf;

	af = of_bus_pci_get_flags(addr);
	rf = of_bus_pci_get_flags(range);

	/* Check address type match */
	अगर ((af ^ rf) & (IORESOURCE_MEM | IORESOURCE_IO))
		वापस OF_BAD_ADDR;

	/* Read address values, skipping high cell */
	cp = of_पढ़ो_number(range + 1, na - 1);
	s  = of_पढ़ो_number(range + na + pna, ns);
	da = of_पढ़ो_number(addr + 1, na - 1);

	pr_debug("PCI map, cp=%llx, s=%llx, da=%llx\n",
		 (अचिन्हित दीर्घ दीर्घ)cp, (अचिन्हित दीर्घ दीर्घ)s,
		 (अचिन्हित दीर्घ दीर्घ)da);

	अगर (da < cp || da >= (cp + s))
		वापस OF_BAD_ADDR;
	वापस da - cp;
पूर्ण

अटल पूर्णांक of_bus_pci_translate(__be32 *addr, u64 offset, पूर्णांक na)
अणु
	वापस of_bus_शेष_translate(addr + 1, offset, na - 1);
पूर्ण

स्थिर __be32 *of_get_pci_address(काष्ठा device_node *dev, पूर्णांक bar_no, u64 *size,
			अचिन्हित पूर्णांक *flags)
अणु
	स्थिर __be32 *prop;
	अचिन्हित पूर्णांक psize;
	काष्ठा device_node *parent;
	काष्ठा of_bus *bus;
	पूर्णांक onesize, i, na, ns;

	/* Get parent & match bus type */
	parent = of_get_parent(dev);
	अगर (parent == शून्य)
		वापस शून्य;
	bus = of_match_bus(parent);
	अगर (म_भेद(bus->name, "pci")) अणु
		of_node_put(parent);
		वापस शून्य;
	पूर्ण
	bus->count_cells(dev, &na, &ns);
	of_node_put(parent);
	अगर (!OF_CHECK_ADDR_COUNT(na))
		वापस शून्य;

	/* Get "reg" or "assigned-addresses" property */
	prop = of_get_property(dev, bus->addresses, &psize);
	अगर (prop == शून्य)
		वापस शून्य;
	psize /= 4;

	onesize = na + ns;
	क्रम (i = 0; psize >= onesize; psize -= onesize, prop += onesize, i++) अणु
		u32 val = be32_to_cpu(prop[0]);
		अगर ((val & 0xff) == ((bar_no * 4) + PCI_BASE_ADDRESS_0)) अणु
			अगर (size)
				*size = of_पढ़ो_number(prop + na, ns);
			अगर (flags)
				*flags = bus->get_flags(prop);
			वापस prop;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(of_get_pci_address);

पूर्णांक of_pci_address_to_resource(काष्ठा device_node *dev, पूर्णांक bar,
			       काष्ठा resource *r)
अणु
	स्थिर __be32	*addrp;
	u64		size;
	अचिन्हित पूर्णांक	flags;

	addrp = of_get_pci_address(dev, bar, &size, &flags);
	अगर (addrp == शून्य)
		वापस -EINVAL;
	वापस __of_address_to_resource(dev, addrp, size, flags, शून्य, r);
पूर्ण
EXPORT_SYMBOL_GPL(of_pci_address_to_resource);

/*
 * of_pci_range_to_resource - Create a resource from an of_pci_range
 * @range:	the PCI range that describes the resource
 * @np:		device node where the range beदीर्घs to
 * @res:	poपूर्णांकer to a valid resource that will be updated to
 *              reflect the values contained in the range.
 *
 * Returns EINVAL अगर the range cannot be converted to resource.
 *
 * Note that अगर the range is an IO range, the resource will be converted
 * using pci_address_to_pio() which can fail अगर it is called too early or
 * अगर the range cannot be matched to any host bridge IO space (our हाल here).
 * To guard against that we try to रेजिस्टर the IO range first.
 * If that fails we know that pci_address_to_pio() will करो too.
 */
पूर्णांक of_pci_range_to_resource(काष्ठा of_pci_range *range,
			     काष्ठा device_node *np, काष्ठा resource *res)
अणु
	पूर्णांक err;
	res->flags = range->flags;
	res->parent = res->child = res->sibling = शून्य;
	res->name = np->full_name;

	अगर (res->flags & IORESOURCE_IO) अणु
		अचिन्हित दीर्घ port;
		err = pci_रेजिस्टर_io_range(&np->fwnode, range->cpu_addr,
				range->size);
		अगर (err)
			जाओ invalid_range;
		port = pci_address_to_pio(range->cpu_addr);
		अगर (port == (अचिन्हित दीर्घ)-1) अणु
			err = -EINVAL;
			जाओ invalid_range;
		पूर्ण
		res->start = port;
	पूर्ण अन्यथा अणु
		अगर ((माप(resource_माप_प्रकार) < 8) &&
		    upper_32_bits(range->cpu_addr)) अणु
			err = -EINVAL;
			जाओ invalid_range;
		पूर्ण

		res->start = range->cpu_addr;
	पूर्ण
	res->end = res->start + range->size - 1;
	वापस 0;

invalid_range:
	res->start = (resource_माप_प्रकार)OF_BAD_ADDR;
	res->end = (resource_माप_प्रकार)OF_BAD_ADDR;
	वापस err;
पूर्ण
EXPORT_SYMBOL(of_pci_range_to_resource);
#पूर्ण_अगर /* CONFIG_PCI */

/*
 * ISA bus specअगरic translator
 */

अटल पूर्णांक of_bus_isa_match(काष्ठा device_node *np)
अणु
	वापस of_node_name_eq(np, "isa");
पूर्ण

अटल व्योम of_bus_isa_count_cells(काष्ठा device_node *child,
				   पूर्णांक *addrc, पूर्णांक *sizec)
अणु
	अगर (addrc)
		*addrc = 2;
	अगर (sizec)
		*sizec = 1;
पूर्ण

अटल u64 of_bus_isa_map(__be32 *addr, स्थिर __be32 *range, पूर्णांक na, पूर्णांक ns,
		पूर्णांक pna)
अणु
	u64 cp, s, da;

	/* Check address type match */
	अगर ((addr[0] ^ range[0]) & cpu_to_be32(1))
		वापस OF_BAD_ADDR;

	/* Read address values, skipping high cell */
	cp = of_पढ़ो_number(range + 1, na - 1);
	s  = of_पढ़ो_number(range + na + pna, ns);
	da = of_पढ़ो_number(addr + 1, na - 1);

	pr_debug("ISA map, cp=%llx, s=%llx, da=%llx\n",
		 (अचिन्हित दीर्घ दीर्घ)cp, (अचिन्हित दीर्घ दीर्घ)s,
		 (अचिन्हित दीर्घ दीर्घ)da);

	अगर (da < cp || da >= (cp + s))
		वापस OF_BAD_ADDR;
	वापस da - cp;
पूर्ण

अटल पूर्णांक of_bus_isa_translate(__be32 *addr, u64 offset, पूर्णांक na)
अणु
	वापस of_bus_शेष_translate(addr + 1, offset, na - 1);
पूर्ण

अटल अचिन्हित पूर्णांक of_bus_isa_get_flags(स्थिर __be32 *addr)
अणु
	अचिन्हित पूर्णांक flags = 0;
	u32 w = be32_to_cpup(addr);

	अगर (w & 1)
		flags |= IORESOURCE_IO;
	अन्यथा
		flags |= IORESOURCE_MEM;
	वापस flags;
पूर्ण

/*
 * Array of bus specअगरic translators
 */

अटल काष्ठा of_bus of_busses[] = अणु
#अगर_घोषित CONFIG_PCI
	/* PCI */
	अणु
		.name = "pci",
		.addresses = "assigned-addresses",
		.match = of_bus_pci_match,
		.count_cells = of_bus_pci_count_cells,
		.map = of_bus_pci_map,
		.translate = of_bus_pci_translate,
		.has_flags = true,
		.get_flags = of_bus_pci_get_flags,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_PCI */
	/* ISA */
	अणु
		.name = "isa",
		.addresses = "reg",
		.match = of_bus_isa_match,
		.count_cells = of_bus_isa_count_cells,
		.map = of_bus_isa_map,
		.translate = of_bus_isa_translate,
		.has_flags = true,
		.get_flags = of_bus_isa_get_flags,
	पूर्ण,
	/* Default */
	अणु
		.name = "default",
		.addresses = "reg",
		.match = शून्य,
		.count_cells = of_bus_शेष_count_cells,
		.map = of_bus_शेष_map,
		.translate = of_bus_शेष_translate,
		.get_flags = of_bus_शेष_get_flags,
	पूर्ण,
पूर्ण;

अटल काष्ठा of_bus *of_match_bus(काष्ठा device_node *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(of_busses); i++)
		अगर (!of_busses[i].match || of_busses[i].match(np))
			वापस &of_busses[i];
	BUG();
	वापस शून्य;
पूर्ण

अटल पूर्णांक of_empty_ranges_quirk(काष्ठा device_node *np)
अणु
	अगर (IS_ENABLED(CONFIG_PPC)) अणु
		/* To save cycles, we cache the result क्रम global "Mac" setting */
		अटल पूर्णांक quirk_state = -1;

		/* PA-SEMI sdc DT bug */
		अगर (of_device_is_compatible(np, "1682m-sdc"))
			वापस true;

		/* Make quirk cached */
		अगर (quirk_state < 0)
			quirk_state =
				of_machine_is_compatible("Power Macintosh") ||
				of_machine_is_compatible("MacRISC");
		वापस quirk_state;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक of_translate_one(काष्ठा device_node *parent, काष्ठा of_bus *bus,
			    काष्ठा of_bus *pbus, __be32 *addr,
			    पूर्णांक na, पूर्णांक ns, पूर्णांक pna, स्थिर अक्षर *rprop)
अणु
	स्थिर __be32 *ranges;
	अचिन्हित पूर्णांक rlen;
	पूर्णांक rone;
	u64 offset = OF_BAD_ADDR;

	/*
	 * Normally, an असलence of a "ranges" property means we are
	 * crossing a non-translatable boundary, and thus the addresses
	 * below the current cannot be converted to CPU physical ones.
	 * Unक्रमtunately, जबतक this is very clear in the spec, it's not
	 * what Apple understood, and they करो have things like /uni-n or
	 * /ht nodes with no "ranges" property and a lot of perfectly
	 * useable mapped devices below them. Thus we treat the असलence of
	 * "ranges" as equivalent to an empty "ranges" property which means
	 * a 1:1 translation at that level. It's up to the caller not to try
	 * to translate addresses that aren't supposed to be translated in
	 * the first place. --BenH.
	 *
	 * As far as we know, this damage only exists on Apple machines, so
	 * This code is only enabled on घातerpc. --gcl
	 *
	 * This quirk also applies क्रम 'dma-ranges' which frequently exist in
	 * child nodes without 'dma-ranges' in the parent nodes. --RobH
	 */
	ranges = of_get_property(parent, rprop, &rlen);
	अगर (ranges == शून्य && !of_empty_ranges_quirk(parent) &&
	    म_भेद(rprop, "dma-ranges")) अणु
		pr_debug("no ranges; cannot translate\n");
		वापस 1;
	पूर्ण
	अगर (ranges == शून्य || rlen == 0) अणु
		offset = of_पढ़ो_number(addr, na);
		स_रखो(addr, 0, pna * 4);
		pr_debug("empty ranges; 1:1 translation\n");
		जाओ finish;
	पूर्ण

	pr_debug("walking ranges...\n");

	/* Now walk through the ranges */
	rlen /= 4;
	rone = na + pna + ns;
	क्रम (; rlen >= rone; rlen -= rone, ranges += rone) अणु
		offset = bus->map(addr, ranges, na, ns, pna);
		अगर (offset != OF_BAD_ADDR)
			अवरोध;
	पूर्ण
	अगर (offset == OF_BAD_ADDR) अणु
		pr_debug("not found !\n");
		वापस 1;
	पूर्ण
	स_नकल(addr, ranges + na, 4 * pna);

 finish:
	of_dump_addr("parent translation for:", addr, pna);
	pr_debug("with offset: %llx\n", (अचिन्हित दीर्घ दीर्घ)offset);

	/* Translate it पूर्णांकo parent bus space */
	वापस pbus->translate(addr, offset, pna);
पूर्ण

/*
 * Translate an address from the device-tree पूर्णांकo a CPU physical address,
 * this walks up the tree and applies the various bus mappings on the
 * way.
 *
 * Note: We consider that crossing any level with #size-cells == 0 to mean
 * that translation is impossible (that is we are not dealing with a value
 * that can be mapped to a cpu physical address). This is not really specअगरied
 * that way, but this is traditionally the way IBM at least करो things
 *
 * Whenever the translation fails, the *host poपूर्णांकer will be set to the
 * device that had रेजिस्टरed logical PIO mapping, and the वापस code is
 * relative to that node.
 */
अटल u64 __of_translate_address(काष्ठा device_node *dev,
				  काष्ठा device_node *(*get_parent)(स्थिर काष्ठा device_node *),
				  स्थिर __be32 *in_addr, स्थिर अक्षर *rprop,
				  काष्ठा device_node **host)
अणु
	काष्ठा device_node *parent = शून्य;
	काष्ठा of_bus *bus, *pbus;
	__be32 addr[OF_MAX_ADDR_CELLS];
	पूर्णांक na, ns, pna, pns;
	u64 result = OF_BAD_ADDR;

	pr_debug("** translation for device %pOF **\n", dev);

	/* Increase refcount at current level */
	of_node_get(dev);

	*host = शून्य;
	/* Get parent & match bus type */
	parent = get_parent(dev);
	अगर (parent == शून्य)
		जाओ bail;
	bus = of_match_bus(parent);

	/* Count address cells & copy address locally */
	bus->count_cells(dev, &na, &ns);
	अगर (!OF_CHECK_COUNTS(na, ns)) अणु
		pr_debug("Bad cell count for %pOF\n", dev);
		जाओ bail;
	पूर्ण
	स_नकल(addr, in_addr, na * 4);

	pr_debug("bus is %s (na=%d, ns=%d) on %pOF\n",
	    bus->name, na, ns, parent);
	of_dump_addr("translating address:", addr, na);

	/* Translate */
	क्रम (;;) अणु
		काष्ठा logic_pio_hwaddr *iorange;

		/* Switch to parent bus */
		of_node_put(dev);
		dev = parent;
		parent = get_parent(dev);

		/* If root, we have finished */
		अगर (parent == शून्य) अणु
			pr_debug("reached root node\n");
			result = of_पढ़ो_number(addr, na);
			अवरोध;
		पूर्ण

		/*
		 * For indirectIO device which has no ranges property, get
		 * the address from reg directly.
		 */
		iorange = find_io_range_by_fwnode(&dev->fwnode);
		अगर (iorange && (iorange->flags != LOGIC_PIO_CPU_MMIO)) अणु
			result = of_पढ़ो_number(addr + 1, na - 1);
			pr_debug("indirectIO matched(%pOF) 0x%llx\n",
				 dev, result);
			*host = of_node_get(dev);
			अवरोध;
		पूर्ण

		/* Get new parent bus and counts */
		pbus = of_match_bus(parent);
		pbus->count_cells(dev, &pna, &pns);
		अगर (!OF_CHECK_COUNTS(pna, pns)) अणु
			pr_err("Bad cell count for %pOF\n", dev);
			अवरोध;
		पूर्ण

		pr_debug("parent bus is %s (na=%d, ns=%d) on %pOF\n",
		    pbus->name, pna, pns, parent);

		/* Apply bus translation */
		अगर (of_translate_one(dev, bus, pbus, addr, na, ns, pna, rprop))
			अवरोध;

		/* Complete the move up one level */
		na = pna;
		ns = pns;
		bus = pbus;

		of_dump_addr("one level translation:", addr, na);
	पूर्ण
 bail:
	of_node_put(parent);
	of_node_put(dev);

	वापस result;
पूर्ण

u64 of_translate_address(काष्ठा device_node *dev, स्थिर __be32 *in_addr)
अणु
	काष्ठा device_node *host;
	u64 ret;

	ret = __of_translate_address(dev, of_get_parent,
				     in_addr, "ranges", &host);
	अगर (host) अणु
		of_node_put(host);
		वापस OF_BAD_ADDR;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(of_translate_address);

अटल काष्ठा device_node *__of_get_dma_parent(स्थिर काष्ठा device_node *np)
अणु
	काष्ठा of_phandle_args args;
	पूर्णांक ret, index;

	index = of_property_match_string(np, "interconnect-names", "dma-mem");
	अगर (index < 0)
		वापस of_get_parent(np);

	ret = of_parse_phandle_with_args(np, "interconnects",
					 "#interconnect-cells",
					 index, &args);
	अगर (ret < 0)
		वापस of_get_parent(np);

	वापस of_node_get(args.np);
पूर्ण

अटल काष्ठा device_node *of_get_next_dma_parent(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent;

	parent = __of_get_dma_parent(np);
	of_node_put(np);

	वापस parent;
पूर्ण

u64 of_translate_dma_address(काष्ठा device_node *dev, स्थिर __be32 *in_addr)
अणु
	काष्ठा device_node *host;
	u64 ret;

	ret = __of_translate_address(dev, __of_get_dma_parent,
				     in_addr, "dma-ranges", &host);

	अगर (host) अणु
		of_node_put(host);
		वापस OF_BAD_ADDR;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(of_translate_dma_address);

स्थिर __be32 *of_get_address(काष्ठा device_node *dev, पूर्णांक index, u64 *size,
		    अचिन्हित पूर्णांक *flags)
अणु
	स्थिर __be32 *prop;
	अचिन्हित पूर्णांक psize;
	काष्ठा device_node *parent;
	काष्ठा of_bus *bus;
	पूर्णांक onesize, i, na, ns;

	/* Get parent & match bus type */
	parent = of_get_parent(dev);
	अगर (parent == शून्य)
		वापस शून्य;
	bus = of_match_bus(parent);
	bus->count_cells(dev, &na, &ns);
	of_node_put(parent);
	अगर (!OF_CHECK_ADDR_COUNT(na))
		वापस शून्य;

	/* Get "reg" or "assigned-addresses" property */
	prop = of_get_property(dev, bus->addresses, &psize);
	अगर (prop == शून्य)
		वापस शून्य;
	psize /= 4;

	onesize = na + ns;
	क्रम (i = 0; psize >= onesize; psize -= onesize, prop += onesize, i++)
		अगर (i == index) अणु
			अगर (size)
				*size = of_पढ़ो_number(prop + na, ns);
			अगर (flags)
				*flags = bus->get_flags(prop);
			वापस prop;
		पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(of_get_address);

अटल पूर्णांक parser_init(काष्ठा of_pci_range_parser *parser,
			काष्ठा device_node *node, स्थिर अक्षर *name)
अणु
	पूर्णांक rlen;

	parser->node = node;
	parser->pna = of_n_addr_cells(node);
	parser->na = of_bus_n_addr_cells(node);
	parser->ns = of_bus_n_size_cells(node);
	parser->dma = !म_भेद(name, "dma-ranges");
	parser->bus = of_match_bus(node);

	parser->range = of_get_property(node, name, &rlen);
	अगर (parser->range == शून्य)
		वापस -ENOENT;

	parser->end = parser->range + rlen / माप(__be32);

	वापस 0;
पूर्ण

पूर्णांक of_pci_range_parser_init(काष्ठा of_pci_range_parser *parser,
				काष्ठा device_node *node)
अणु
	वापस parser_init(parser, node, "ranges");
पूर्ण
EXPORT_SYMBOL_GPL(of_pci_range_parser_init);

पूर्णांक of_pci_dma_range_parser_init(काष्ठा of_pci_range_parser *parser,
				काष्ठा device_node *node)
अणु
	वापस parser_init(parser, node, "dma-ranges");
पूर्ण
EXPORT_SYMBOL_GPL(of_pci_dma_range_parser_init);
#घोषणा of_dma_range_parser_init of_pci_dma_range_parser_init

काष्ठा of_pci_range *of_pci_range_parser_one(काष्ठा of_pci_range_parser *parser,
						काष्ठा of_pci_range *range)
अणु
	पूर्णांक na = parser->na;
	पूर्णांक ns = parser->ns;
	पूर्णांक np = parser->pna + na + ns;
	पूर्णांक busflag_na = 0;

	अगर (!range)
		वापस शून्य;

	अगर (!parser->range || parser->range + np > parser->end)
		वापस शून्य;

	range->flags = parser->bus->get_flags(parser->range);

	/* A extra cell क्रम resource flags */
	अगर (parser->bus->has_flags)
		busflag_na = 1;

	range->bus_addr = of_पढ़ो_number(parser->range + busflag_na, na - busflag_na);

	अगर (parser->dma)
		range->cpu_addr = of_translate_dma_address(parser->node,
				parser->range + na);
	अन्यथा
		range->cpu_addr = of_translate_address(parser->node,
				parser->range + na);
	range->size = of_पढ़ो_number(parser->range + parser->pna + na, ns);

	parser->range += np;

	/* Now consume following elements जबतक they are contiguous */
	जबतक (parser->range + np <= parser->end) अणु
		u32 flags = 0;
		u64 bus_addr, cpu_addr, size;

		flags = parser->bus->get_flags(parser->range);
		bus_addr = of_पढ़ो_number(parser->range + busflag_na, na - busflag_na);
		अगर (parser->dma)
			cpu_addr = of_translate_dma_address(parser->node,
					parser->range + na);
		अन्यथा
			cpu_addr = of_translate_address(parser->node,
					parser->range + na);
		size = of_पढ़ो_number(parser->range + parser->pna + na, ns);

		अगर (flags != range->flags)
			अवरोध;
		अगर (bus_addr != range->bus_addr + range->size ||
		    cpu_addr != range->cpu_addr + range->size)
			अवरोध;

		range->size += size;
		parser->range += np;
	पूर्ण

	वापस range;
पूर्ण
EXPORT_SYMBOL_GPL(of_pci_range_parser_one);

अटल u64 of_translate_ioport(काष्ठा device_node *dev, स्थिर __be32 *in_addr,
			u64 size)
अणु
	u64 taddr;
	अचिन्हित दीर्घ port;
	काष्ठा device_node *host;

	taddr = __of_translate_address(dev, of_get_parent,
				       in_addr, "ranges", &host);
	अगर (host) अणु
		/* host-specअगरic port access */
		port = logic_pio_trans_hwaddr(&host->fwnode, taddr, size);
		of_node_put(host);
	पूर्ण अन्यथा अणु
		/* memory-mapped I/O range */
		port = pci_address_to_pio(taddr);
	पूर्ण

	अगर (port == (अचिन्हित दीर्घ)-1)
		वापस OF_BAD_ADDR;

	वापस port;
पूर्ण

अटल पूर्णांक __of_address_to_resource(काष्ठा device_node *dev,
		स्थिर __be32 *addrp, u64 size, अचिन्हित पूर्णांक flags,
		स्थिर अक्षर *name, काष्ठा resource *r)
अणु
	u64 taddr;

	अगर (flags & IORESOURCE_MEM)
		taddr = of_translate_address(dev, addrp);
	अन्यथा अगर (flags & IORESOURCE_IO)
		taddr = of_translate_ioport(dev, addrp, size);
	अन्यथा
		वापस -EINVAL;

	अगर (taddr == OF_BAD_ADDR)
		वापस -EINVAL;
	स_रखो(r, 0, माप(काष्ठा resource));

	अगर (of_mmio_is_nonposted(dev))
		flags |= IORESOURCE_MEM_NONPOSTED;

	r->start = taddr;
	r->end = taddr + size - 1;
	r->flags = flags;
	r->name = name ? name : dev->full_name;

	वापस 0;
पूर्ण

/**
 * of_address_to_resource - Translate device tree address and वापस as resource
 * @dev:	Caller's Device Node
 * @index:	Index पूर्णांकo the array
 * @r:		Poपूर्णांकer to resource array
 *
 * Note that अगर your address is a PIO address, the conversion will fail अगर
 * the physical address can't be पूर्णांकernally converted to an IO token with
 * pci_address_to_pio(), that is because it's either called too early or it
 * can't be matched to any host bridge IO space
 */
पूर्णांक of_address_to_resource(काष्ठा device_node *dev, पूर्णांक index,
			   काष्ठा resource *r)
अणु
	स्थिर __be32	*addrp;
	u64		size;
	अचिन्हित पूर्णांक	flags;
	स्थिर अक्षर	*name = शून्य;

	addrp = of_get_address(dev, index, &size, &flags);
	अगर (addrp == शून्य)
		वापस -EINVAL;

	/* Get optional "reg-names" property to add a name to a resource */
	of_property_पढ़ो_string_index(dev, "reg-names",	index, &name);

	वापस __of_address_to_resource(dev, addrp, size, flags, name, r);
पूर्ण
EXPORT_SYMBOL_GPL(of_address_to_resource);

/**
 * of_iomap - Maps the memory mapped IO क्रम a given device_node
 * @np:		the device whose io range will be mapped
 * @index:	index of the io range
 *
 * Returns a poपूर्णांकer to the mapped memory
 */
व्योम __iomem *of_iomap(काष्ठा device_node *np, पूर्णांक index)
अणु
	काष्ठा resource res;

	अगर (of_address_to_resource(np, index, &res))
		वापस शून्य;

	अगर (res.flags & IORESOURCE_MEM_NONPOSTED)
		वापस ioremap_np(res.start, resource_size(&res));
	अन्यथा
		वापस ioremap(res.start, resource_size(&res));
पूर्ण
EXPORT_SYMBOL(of_iomap);

/*
 * of_io_request_and_map - Requests a resource and maps the memory mapped IO
 *			   क्रम a given device_node
 * @device:	the device whose io range will be mapped
 * @index:	index of the io range
 * @name:	name "override" क्रम the memory region request or शून्य
 *
 * Returns a poपूर्णांकer to the requested and mapped memory or an ERR_PTR() encoded
 * error code on failure. Usage example:
 *
 *	base = of_io_request_and_map(node, 0, "foo");
 *	अगर (IS_ERR(base))
 *		वापस PTR_ERR(base);
 */
व्योम __iomem *of_io_request_and_map(काष्ठा device_node *np, पूर्णांक index,
				    स्थिर अक्षर *name)
अणु
	काष्ठा resource res;
	व्योम __iomem *mem;

	अगर (of_address_to_resource(np, index, &res))
		वापस IOMEM_ERR_PTR(-EINVAL);

	अगर (!name)
		name = res.name;
	अगर (!request_mem_region(res.start, resource_size(&res), name))
		वापस IOMEM_ERR_PTR(-EBUSY);

	अगर (res.flags & IORESOURCE_MEM_NONPOSTED)
		mem = ioremap_np(res.start, resource_size(&res));
	अन्यथा
		mem = ioremap(res.start, resource_size(&res));

	अगर (!mem) अणु
		release_mem_region(res.start, resource_size(&res));
		वापस IOMEM_ERR_PTR(-ENOMEM);
	पूर्ण

	वापस mem;
पूर्ण
EXPORT_SYMBOL(of_io_request_and_map);

#अगर_घोषित CONFIG_HAS_DMA
/**
 * of_dma_get_range - Get DMA range info and put it पूर्णांकo a map array
 * @np:		device node to get DMA range info
 * @map:	dma range काष्ठाure to वापस
 *
 * Look in bottom up direction क्रम the first "dma-ranges" property
 * and parse it.  Put the inक्रमmation पूर्णांकo a DMA offset map array.
 *
 * dma-ranges क्रमmat:
 *	DMA addr (dma_addr)	: naddr cells
 *	CPU addr (phys_addr_t)	: pna cells
 *	size			: nsize cells
 *
 * It वापसs -ENODEV अगर "dma-ranges" property was not found क्रम this
 * device in the DT.
 */
पूर्णांक of_dma_get_range(काष्ठा device_node *np, स्थिर काष्ठा bus_dma_region **map)
अणु
	काष्ठा device_node *node = of_node_get(np);
	स्थिर __be32 *ranges = शून्य;
	bool found_dma_ranges = false;
	काष्ठा of_range_parser parser;
	काष्ठा of_range range;
	काष्ठा bus_dma_region *r;
	पूर्णांक len, num_ranges = 0;
	पूर्णांक ret = 0;

	जबतक (node) अणु
		ranges = of_get_property(node, "dma-ranges", &len);

		/* Ignore empty ranges, they imply no translation required */
		अगर (ranges && len > 0)
			अवरोध;

		/* Once we find 'dma-ranges', then a missing one is an error */
		अगर (found_dma_ranges && !ranges) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण
		found_dma_ranges = true;

		node = of_get_next_dma_parent(node);
	पूर्ण

	अगर (!node || !ranges) अणु
		pr_debug("no dma-ranges found for node(%pOF)\n", np);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	of_dma_range_parser_init(&parser, node);
	क्रम_each_of_range(&parser, &range)
		num_ranges++;

	r = kसुस्मृति(num_ranges + 1, माप(*r), GFP_KERNEL);
	अगर (!r) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Record all info in the generic DMA ranges array क्रम काष्ठा device.
	 */
	*map = r;
	of_dma_range_parser_init(&parser, node);
	क्रम_each_of_range(&parser, &range) अणु
		pr_debug("dma_addr(%llx) cpu_addr(%llx) size(%llx)\n",
			 range.bus_addr, range.cpu_addr, range.size);
		अगर (range.cpu_addr == OF_BAD_ADDR) अणु
			pr_err("translation of DMA address(%llx) to CPU address failed node(%pOF)\n",
			       range.bus_addr, node);
			जारी;
		पूर्ण
		r->cpu_start = range.cpu_addr;
		r->dma_start = range.bus_addr;
		r->size = range.size;
		r->offset = range.cpu_addr - range.bus_addr;
		r++;
	पूर्ण
out:
	of_node_put(node);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAS_DMA */

/**
 * of_dma_get_max_cpu_address - Gets highest CPU address suitable क्रम DMA
 * @np: The node to start searching from or शून्य to start from the root
 *
 * Gets the highest CPU physical address that is addressable by all DMA masters
 * in the sub-tree poपूर्णांकed by np, or the whole tree अगर शून्य is passed. If no
 * DMA स्थिरrained device is found, it वापसs PHYS_ADDR_MAX.
 */
phys_addr_t __init of_dma_get_max_cpu_address(काष्ठा device_node *np)
अणु
	phys_addr_t max_cpu_addr = PHYS_ADDR_MAX;
	काष्ठा of_range_parser parser;
	phys_addr_t subtree_max_addr;
	काष्ठा device_node *child;
	काष्ठा of_range range;
	स्थिर __be32 *ranges;
	u64 cpu_end = 0;
	पूर्णांक len;

	अगर (!np)
		np = of_root;

	ranges = of_get_property(np, "dma-ranges", &len);
	अगर (ranges && len) अणु
		of_dma_range_parser_init(&parser, np);
		क्रम_each_of_range(&parser, &range)
			अगर (range.cpu_addr + range.size > cpu_end)
				cpu_end = range.cpu_addr + range.size - 1;

		अगर (max_cpu_addr > cpu_end)
			max_cpu_addr = cpu_end;
	पूर्ण

	क्रम_each_available_child_of_node(np, child) अणु
		subtree_max_addr = of_dma_get_max_cpu_address(child);
		अगर (max_cpu_addr > subtree_max_addr)
			max_cpu_addr = subtree_max_addr;
	पूर्ण

	वापस max_cpu_addr;
पूर्ण

/**
 * of_dma_is_coherent - Check अगर device is coherent
 * @np:	device node
 *
 * It वापसs true अगर "dma-coherent" property was found
 * क्रम this device in the DT, or अगर DMA is coherent by
 * शेष क्रम OF devices on the current platक्रमm.
 */
bool of_dma_is_coherent(काष्ठा device_node *np)
अणु
	काष्ठा device_node *node;

	अगर (IS_ENABLED(CONFIG_OF_DMA_DEFAULT_COHERENT))
		वापस true;

	node = of_node_get(np);

	जबतक (node) अणु
		अगर (of_property_पढ़ो_bool(node, "dma-coherent")) अणु
			of_node_put(node);
			वापस true;
		पूर्ण
		node = of_get_next_dma_parent(node);
	पूर्ण
	of_node_put(node);
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(of_dma_is_coherent);

/**
 * of_mmio_is_nonposted - Check अगर device uses non-posted MMIO
 * @np:	device node
 *
 * Returns true अगर the "nonposted-mmio" property was found क्रम
 * the device's bus.
 *
 * This is currently only enabled on builds that support Apple ARM devices, as
 * an optimization.
 */
अटल bool of_mmio_is_nonposted(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent;
	bool nonposted;

	अगर (!IS_ENABLED(CONFIG_ARCH_APPLE))
		वापस false;

	parent = of_get_parent(np);
	अगर (!parent)
		वापस false;

	nonposted = of_property_पढ़ो_bool(parent, "nonposted-mmio");

	of_node_put(parent);
	वापस nonposted;
पूर्ण
