<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/spitfire.h>

#समावेश "of_device_common.h"

व्योम __iomem *of_ioremap(काष्ठा resource *res, अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size, अक्षर *name)
अणु
	अचिन्हित दीर्घ ret = res->start + offset;
	काष्ठा resource *r;

	अगर (res->flags & IORESOURCE_MEM)
		r = request_mem_region(ret, size, name);
	अन्यथा
		r = request_region(ret, size, name);
	अगर (!r)
		ret = 0;

	वापस (व्योम __iomem *) ret;
पूर्ण
EXPORT_SYMBOL(of_ioremap);

व्योम of_iounmap(काष्ठा resource *res, व्योम __iomem *base, अचिन्हित दीर्घ size)
अणु
	अगर (res->flags & IORESOURCE_MEM)
		release_mem_region((अचिन्हित दीर्घ) base, size);
	अन्यथा
		release_region((अचिन्हित दीर्घ) base, size);
पूर्ण
EXPORT_SYMBOL(of_iounmap);

/*
 * PCI bus specअगरic translator
 */

अटल पूर्णांक of_bus_pci_match(काष्ठा device_node *np)
अणु
	अगर (of_node_name_eq(np, "pci")) अणु
		स्थिर अक्षर *model = of_get_property(np, "model", शून्य);

		अगर (model && !म_भेद(model, "SUNW,simba"))
			वापस 0;

		/* Do not करो PCI specअगरic frobbing अगर the
		 * PCI bridge lacks a ranges property.  We
		 * want to pass it through up to the next
		 * parent as-is, not with the PCI translate
		 * method which chops off the top address cell.
		 */
		अगर (!of_find_property(np, "ranges", शून्य))
			वापस 0;

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक of_bus_simba_match(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *model = of_get_property(np, "model", शून्य);

	अगर (model && !म_भेद(model, "SUNW,simba"))
		वापस 1;

	/* Treat PCI busses lacking ranges property just like
	 * simba.
	 */
	अगर (of_node_name_eq(np, "pci")) अणु
		अगर (!of_find_property(np, "ranges", शून्य))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक of_bus_simba_map(u32 *addr, स्थिर u32 *range,
			    पूर्णांक na, पूर्णांक ns, पूर्णांक pna)
अणु
	वापस 0;
पूर्ण

अटल व्योम of_bus_pci_count_cells(काष्ठा device_node *np,
				   पूर्णांक *addrc, पूर्णांक *sizec)
अणु
	अगर (addrc)
		*addrc = 3;
	अगर (sizec)
		*sizec = 2;
पूर्ण

अटल पूर्णांक of_bus_pci_map(u32 *addr, स्थिर u32 *range,
			  पूर्णांक na, पूर्णांक ns, पूर्णांक pna)
अणु
	u32 result[OF_MAX_ADDR_CELLS];
	पूर्णांक i;

	/* Check address type match */
	अगर (!((addr[0] ^ range[0]) & 0x03000000))
		जाओ type_match;

	/* Special exception, we can map a 64-bit address पूर्णांकo
	 * a 32-bit range.
	 */
	अगर ((addr[0] & 0x03000000) == 0x03000000 &&
	    (range[0] & 0x03000000) == 0x02000000)
		जाओ type_match;

	वापस -EINVAL;

type_match:
	अगर (of_out_of_range(addr + 1, range + 1, range + na + pna,
			    na - 1, ns))
		वापस -EINVAL;

	/* Start with the parent range base.  */
	स_नकल(result, range + na, pna * 4);

	/* Add in the child address offset, skipping high cell.  */
	क्रम (i = 0; i < na - 1; i++)
		result[pna - 1 - i] +=
			(addr[na - 1 - i] -
			 range[na - 1 - i]);

	स_नकल(addr, result, pna * 4);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ of_bus_pci_get_flags(स्थिर u32 *addr, अचिन्हित दीर्घ flags)
अणु
	u32 w = addr[0];

	/* For PCI, we override whatever child busses may have used.  */
	flags = 0;
	चयन((w >> 24) & 0x03) अणु
	हाल 0x01:
		flags |= IORESOURCE_IO;
		अवरोध;

	हाल 0x02: /* 32 bits */
	हाल 0x03: /* 64 bits */
		flags |= IORESOURCE_MEM;
		अवरोध;
	पूर्ण
	अगर (w & 0x40000000)
		flags |= IORESOURCE_PREFETCH;
	वापस flags;
पूर्ण

/*
 * FHC/Central bus specअगरic translator.
 *
 * This is just needed to hard-code the address and size cell
 * counts.  'fhc' and 'central' nodes lack the #address-cells and
 * #size-cells properties, and अगर you walk to the root on such
 * Enterprise boxes all you'll get is a #size-cells of 2 which is
 * not what we want to use.
 */
अटल पूर्णांक of_bus_fhc_match(काष्ठा device_node *np)
अणु
	वापस of_node_name_eq(np, "fhc") ||
		of_node_name_eq(np, "central");
पूर्ण

#घोषणा of_bus_fhc_count_cells of_bus_sbus_count_cells

/*
 * Array of bus specअगरic translators
 */

अटल काष्ठा of_bus of_busses[] = अणु
	/* PCI */
	अणु
		.name = "pci",
		.addr_prop_name = "assigned-addresses",
		.match = of_bus_pci_match,
		.count_cells = of_bus_pci_count_cells,
		.map = of_bus_pci_map,
		.get_flags = of_bus_pci_get_flags,
	पूर्ण,
	/* SIMBA */
	अणु
		.name = "simba",
		.addr_prop_name = "assigned-addresses",
		.match = of_bus_simba_match,
		.count_cells = of_bus_pci_count_cells,
		.map = of_bus_simba_map,
		.get_flags = of_bus_pci_get_flags,
	पूर्ण,
	/* SBUS */
	अणु
		.name = "sbus",
		.addr_prop_name = "reg",
		.match = of_bus_sbus_match,
		.count_cells = of_bus_sbus_count_cells,
		.map = of_bus_शेष_map,
		.get_flags = of_bus_शेष_get_flags,
	पूर्ण,
	/* FHC */
	अणु
		.name = "fhc",
		.addr_prop_name = "reg",
		.match = of_bus_fhc_match,
		.count_cells = of_bus_fhc_count_cells,
		.map = of_bus_शेष_map,
		.get_flags = of_bus_शेष_get_flags,
	पूर्ण,
	/* Default */
	अणु
		.name = "default",
		.addr_prop_name = "reg",
		.match = शून्य,
		.count_cells = of_bus_शेष_count_cells,
		.map = of_bus_शेष_map,
		.get_flags = of_bus_शेष_get_flags,
	पूर्ण,
पूर्ण;

अटल काष्ठा of_bus *of_match_bus(काष्ठा device_node *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(of_busses); i ++)
		अगर (!of_busses[i].match || of_busses[i].match(np))
			वापस &of_busses[i];
	BUG();
	वापस शून्य;
पूर्ण

अटल पूर्णांक __init build_one_resource(काष्ठा device_node *parent,
				     काष्ठा of_bus *bus,
				     काष्ठा of_bus *pbus,
				     u32 *addr,
				     पूर्णांक na, पूर्णांक ns, पूर्णांक pna)
अणु
	स्थिर u32 *ranges;
	पूर्णांक rone, rlen;

	ranges = of_get_property(parent, "ranges", &rlen);
	अगर (ranges == शून्य || rlen == 0) अणु
		u32 result[OF_MAX_ADDR_CELLS];
		पूर्णांक i;

		स_रखो(result, 0, pna * 4);
		क्रम (i = 0; i < na; i++)
			result[pna - 1 - i] =
				addr[na - 1 - i];

		स_नकल(addr, result, pna * 4);
		वापस 0;
	पूर्ण

	/* Now walk through the ranges */
	rlen /= 4;
	rone = na + pna + ns;
	क्रम (; rlen >= rone; rlen -= rone, ranges += rone) अणु
		अगर (!bus->map(addr, ranges, na, ns, pna))
			वापस 0;
	पूर्ण

	/* When we miss an I/O space match on PCI, just pass it up
	 * to the next PCI bridge and/or controller.
	 */
	अगर (!म_भेद(bus->name, "pci") &&
	    (addr[0] & 0x03000000) == 0x01000000)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक __init use_1to1_mapping(काष्ठा device_node *pp)
अणु
	/* If we have a ranges property in the parent, use it.  */
	अगर (of_find_property(pp, "ranges", शून्य) != शून्य)
		वापस 0;

	/* If the parent is the dma node of an ISA bus, pass
	 * the translation up to the root.
	 *
	 * Some SBUS devices use पूर्णांकermediate nodes to express
	 * hierarchy within the device itself.  These aren't
	 * real bus nodes, and करोn't have a 'ranges' property.
	 * But, we should still pass the translation work up
	 * to the SBUS itself.
	 */
	अगर (of_node_name_eq(pp, "dma") ||
	    of_node_name_eq(pp, "espdma") ||
	    of_node_name_eq(pp, "ledma") ||
	    of_node_name_eq(pp, "lebuffer"))
		वापस 0;

	/* Similarly क्रम all PCI bridges, अगर we get this far
	 * it lacks a ranges property, and this will include
	 * हालs like Simba.
	 */
	अगर (of_node_name_eq(pp, "pci"))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक of_resource_verbose;

अटल व्योम __init build_device_resources(काष्ठा platक्रमm_device *op,
					  काष्ठा device *parent)
अणु
	काष्ठा platक्रमm_device *p_op;
	काष्ठा of_bus *bus;
	पूर्णांक na, ns;
	पूर्णांक index, num_reg;
	स्थिर व्योम *preg;

	अगर (!parent)
		वापस;

	p_op = to_platक्रमm_device(parent);
	bus = of_match_bus(p_op->dev.of_node);
	bus->count_cells(op->dev.of_node, &na, &ns);

	preg = of_get_property(op->dev.of_node, bus->addr_prop_name, &num_reg);
	अगर (!preg || num_reg == 0)
		वापस;

	/* Convert to num-cells.  */
	num_reg /= 4;

	/* Convert to num-entries.  */
	num_reg /= na + ns;

	/* Prevent overrunning the op->resources[] array.  */
	अगर (num_reg > PROMREG_MAX) अणु
		prपूर्णांकk(KERN_WARNING "%pOF: Too many regs (%d), "
		       "limiting to %d.\n",
		       op->dev.of_node, num_reg, PROMREG_MAX);
		num_reg = PROMREG_MAX;
	पूर्ण

	op->resource = op->archdata.resource;
	op->num_resources = num_reg;
	क्रम (index = 0; index < num_reg; index++) अणु
		काष्ठा resource *r = &op->resource[index];
		u32 addr[OF_MAX_ADDR_CELLS];
		स्थिर u32 *reg = (preg + (index * ((na + ns) * 4)));
		काष्ठा device_node *dp = op->dev.of_node;
		काष्ठा device_node *pp = p_op->dev.of_node;
		काष्ठा of_bus *pbus, *dbus;
		u64 size, result = OF_BAD_ADDR;
		अचिन्हित दीर्घ flags;
		पूर्णांक dna, dns;
		पूर्णांक pna, pns;

		size = of_पढ़ो_addr(reg + na, ns);
		स_नकल(addr, reg, na * 4);

		flags = bus->get_flags(addr, 0);

		अगर (use_1to1_mapping(pp)) अणु
			result = of_पढ़ो_addr(addr, na);
			जाओ build_res;
		पूर्ण

		dna = na;
		dns = ns;
		dbus = bus;

		जबतक (1) अणु
			dp = pp;
			pp = dp->parent;
			अगर (!pp) अणु
				result = of_पढ़ो_addr(addr, dna);
				अवरोध;
			पूर्ण

			pbus = of_match_bus(pp);
			pbus->count_cells(dp, &pna, &pns);

			अगर (build_one_resource(dp, dbus, pbus, addr,
					       dna, dns, pna))
				अवरोध;

			flags = pbus->get_flags(addr, flags);

			dna = pna;
			dns = pns;
			dbus = pbus;
		पूर्ण

	build_res:
		स_रखो(r, 0, माप(*r));

		अगर (of_resource_verbose)
			prपूर्णांकk("%pOF reg[%d] -> %llx\n",
			       op->dev.of_node, index,
			       result);

		अगर (result != OF_BAD_ADDR) अणु
			अगर (tlb_type == hypervisor)
				result &= 0x0fffffffffffffffUL;

			r->start = result;
			r->end = result + size - 1;
			r->flags = flags;
		पूर्ण
		r->name = op->dev.of_node->full_name;
	पूर्ण
पूर्ण

अटल काष्ठा device_node * __init
apply_पूर्णांकerrupt_map(काष्ठा device_node *dp, काष्ठा device_node *pp,
		    स्थिर u32 *imap, पूर्णांक imlen, स्थिर u32 *imask,
		    अचिन्हित पूर्णांक *irq_p)
अणु
	काष्ठा device_node *cp;
	अचिन्हित पूर्णांक irq = *irq_p;
	काष्ठा of_bus *bus;
	phandle handle;
	स्थिर u32 *reg;
	पूर्णांक na, num_reg, i;

	bus = of_match_bus(pp);
	bus->count_cells(dp, &na, शून्य);

	reg = of_get_property(dp, "reg", &num_reg);
	अगर (!reg || !num_reg)
		वापस शून्य;

	imlen /= ((na + 3) * 4);
	handle = 0;
	क्रम (i = 0; i < imlen; i++) अणु
		पूर्णांक j;

		क्रम (j = 0; j < na; j++) अणु
			अगर ((reg[j] & imask[j]) != imap[j])
				जाओ next;
		पूर्ण
		अगर (imap[na] == irq) अणु
			handle = imap[na + 1];
			irq = imap[na + 2];
			अवरोध;
		पूर्ण

	next:
		imap += (na + 3);
	पूर्ण
	अगर (i == imlen) अणु
		/* Psycho and Sabre PCI controllers can have 'interrupt-map'
		 * properties that करो not include the on-board device
		 * पूर्णांकerrupts.  Instead, the device's 'interrupts' property
		 * is alपढ़ोy a fully specअगरied INO value.
		 *
		 * Handle this by deciding that, अगर we didn't get a
		 * match in the parent's 'interrupt-map', and the
		 * parent is an IRQ translator, then use the parent as
		 * our IRQ controller.
		 */
		अगर (pp->irq_trans)
			वापस pp;

		वापस शून्य;
	पूर्ण

	*irq_p = irq;
	cp = of_find_node_by_phandle(handle);

	वापस cp;
पूर्ण

अटल अचिन्हित पूर्णांक __init pci_irq_swizzle(काष्ठा device_node *dp,
					   काष्ठा device_node *pp,
					   अचिन्हित पूर्णांक irq)
अणु
	स्थिर काष्ठा linux_prom_pci_रेजिस्टरs *regs;
	अचिन्हित पूर्णांक bus, devfn, slot, ret;

	अगर (irq < 1 || irq > 4)
		वापस irq;

	regs = of_get_property(dp, "reg", शून्य);
	अगर (!regs)
		वापस irq;

	bus = (regs->phys_hi >> 16) & 0xff;
	devfn = (regs->phys_hi >> 8) & 0xff;
	slot = (devfn >> 3) & 0x1f;

	अगर (pp->irq_trans) अणु
		/* Derived from Table 8-3, U2P User's Manual.  This branch
		 * is handling a PCI controller that lacks a proper set of
		 * पूर्णांकerrupt-map and पूर्णांकerrupt-map-mask properties.  The
		 * Ultra-E450 is one example.
		 *
		 * The bit layout is BSSLL, where:
		 * B: 0 on bus A, 1 on bus B
		 * D: 2-bit slot number, derived from PCI device number as
		 *    (dev - 1) क्रम bus A, or (dev - 2) क्रम bus B
		 * L: 2-bit line number
		 */
		अगर (bus & 0x80) अणु
			/* PBM-A */
			bus  = 0x00;
			slot = (slot - 1) << 2;
		पूर्ण अन्यथा अणु
			/* PBM-B */
			bus  = 0x10;
			slot = (slot - 2) << 2;
		पूर्ण
		irq -= 1;

		ret = (bus | slot | irq);
	पूर्ण अन्यथा अणु
		/* Going through a PCI-PCI bridge that lacks a set of
		 * पूर्णांकerrupt-map and पूर्णांकerrupt-map-mask properties.
		 */
		ret = ((irq - 1 + (slot & 3)) & 3) + 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक of_irq_verbose;

अटल अचिन्हित पूर्णांक __init build_one_device_irq(काष्ठा platक्रमm_device *op,
						काष्ठा device *parent,
						अचिन्हित पूर्णांक irq)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा device_node *pp, *ip;
	अचिन्हित पूर्णांक orig_irq = irq;
	पूर्णांक nid;

	अगर (irq == 0xffffffff)
		वापस irq;

	अगर (dp->irq_trans) अणु
		irq = dp->irq_trans->irq_build(dp, irq,
					       dp->irq_trans->data);

		अगर (of_irq_verbose)
			prपूर्णांकk("%pOF: direct translate %x --> %x\n",
			       dp, orig_irq, irq);

		जाओ out;
	पूर्ण

	/* Something more complicated.  Walk up to the root, applying
	 * पूर्णांकerrupt-map or bus specअगरic translations, until we hit
	 * an IRQ translator.
	 *
	 * If we hit a bus type or situation we cannot handle, we
	 * stop and assume that the original IRQ number was in a
	 * क्रमmat which has special meaning to it's immediate parent.
	 */
	pp = dp->parent;
	ip = शून्य;
	जबतक (pp) अणु
		स्थिर व्योम *imap, *imsk;
		पूर्णांक imlen;

		imap = of_get_property(pp, "interrupt-map", &imlen);
		imsk = of_get_property(pp, "interrupt-map-mask", शून्य);
		अगर (imap && imsk) अणु
			काष्ठा device_node *iret;
			पूर्णांक this_orig_irq = irq;

			iret = apply_पूर्णांकerrupt_map(dp, pp,
						   imap, imlen, imsk,
						   &irq);

			अगर (of_irq_verbose)
				prपूर्णांकk("%pOF: Apply [%pOF:%x] imap --> [%pOF:%x]\n",
				       op->dev.of_node,
				       pp, this_orig_irq, iret, irq);

			अगर (!iret)
				अवरोध;

			अगर (iret->irq_trans) अणु
				ip = iret;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (of_node_name_eq(pp, "pci")) अणु
				अचिन्हित पूर्णांक this_orig_irq = irq;

				irq = pci_irq_swizzle(dp, pp, irq);
				अगर (of_irq_verbose)
					prपूर्णांकk("%pOF: PCI swizzle [%pOF] "
					       "%x --> %x\n",
					       op->dev.of_node,
					       pp, this_orig_irq,
					       irq);

			पूर्ण

			अगर (pp->irq_trans) अणु
				ip = pp;
				अवरोध;
			पूर्ण
		पूर्ण
		dp = pp;
		pp = pp->parent;
	पूर्ण
	अगर (!ip)
		वापस orig_irq;

	irq = ip->irq_trans->irq_build(op->dev.of_node, irq,
				       ip->irq_trans->data);
	अगर (of_irq_verbose)
		prपूर्णांकk("%pOF: Apply IRQ trans [%pOF] %x --> %x\n",
		      op->dev.of_node, ip, orig_irq, irq);

out:
	nid = of_node_to_nid(dp);
	अगर (nid != -1) अणु
		cpumask_t numa_mask;

		cpumask_copy(&numa_mask, cpumask_of_node(nid));
		irq_set_affinity(irq, &numa_mask);
	पूर्ण

	वापस irq;
पूर्ण

अटल काष्ठा platक्रमm_device * __init scan_one_device(काष्ठा device_node *dp,
						 काष्ठा device *parent)
अणु
	काष्ठा platक्रमm_device *op = kzalloc(माप(*op), GFP_KERNEL);
	स्थिर अचिन्हित पूर्णांक *irq;
	काष्ठा dev_archdata *sd;
	पूर्णांक len, i;

	अगर (!op)
		वापस शून्य;

	sd = &op->dev.archdata;
	sd->op = op;

	op->dev.of_node = dp;

	irq = of_get_property(dp, "interrupts", &len);
	अगर (irq) अणु
		op->archdata.num_irqs = len / 4;

		/* Prevent overrunning the op->irqs[] array.  */
		अगर (op->archdata.num_irqs > PROMINTR_MAX) अणु
			prपूर्णांकk(KERN_WARNING "%pOF: Too many irqs (%d), "
			       "limiting to %d.\n",
			       dp, op->archdata.num_irqs, PROMINTR_MAX);
			op->archdata.num_irqs = PROMINTR_MAX;
		पूर्ण
		स_नकल(op->archdata.irqs, irq, op->archdata.num_irqs * 4);
	पूर्ण अन्यथा अणु
		op->archdata.num_irqs = 0;
	पूर्ण

	build_device_resources(op, parent);
	क्रम (i = 0; i < op->archdata.num_irqs; i++)
		op->archdata.irqs[i] = build_one_device_irq(op, parent, op->archdata.irqs[i]);

	op->dev.parent = parent;
	op->dev.bus = &platक्रमm_bus_type;
	अगर (!parent)
		dev_set_name(&op->dev, "root");
	अन्यथा
		dev_set_name(&op->dev, "%08x", dp->phandle);
	op->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	op->dev.dma_mask = &op->dev.coherent_dma_mask;

	अगर (of_device_रेजिस्टर(op)) अणु
		prपूर्णांकk("%pOF: Could not register of device.\n", dp);
		kमुक्त(op);
		op = शून्य;
	पूर्ण

	वापस op;
पूर्ण

अटल व्योम __init scan_tree(काष्ठा device_node *dp, काष्ठा device *parent)
अणु
	जबतक (dp) अणु
		काष्ठा platक्रमm_device *op = scan_one_device(dp, parent);

		अगर (op)
			scan_tree(dp->child, &op->dev);

		dp = dp->sibling;
	पूर्ण
पूर्ण

अटल पूर्णांक __init scan_of_devices(व्योम)
अणु
	काष्ठा device_node *root = of_find_node_by_path("/");
	काष्ठा platक्रमm_device *parent;

	parent = scan_one_device(root, शून्य);
	अगर (!parent)
		वापस 0;

	scan_tree(root->child, &parent->dev);
	वापस 0;
पूर्ण
postcore_initcall(scan_of_devices);

अटल पूर्णांक __init of_debug(अक्षर *str)
अणु
	पूर्णांक val = 0;

	get_option(&str, &val);
	अगर (val & 1)
		of_resource_verbose = 1;
	अगर (val & 2)
		of_irq_verbose = 1;
	वापस 1;
पूर्ण

__setup("of_debug=", of_debug);
