<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/init.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/leon_amba.h>

#समावेश "of_device_common.h"
#समावेश "irq.h"

/*
 * PCI bus specअगरic translator
 */

अटल पूर्णांक of_bus_pci_match(काष्ठा device_node *np)
अणु
	अगर (of_node_is_type(np, "pci") || of_node_is_type(np, "pciex")) अणु
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
	अगर ((addr[0] ^ range[0]) & 0x03000000)
		वापस -EINVAL;

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

अटल अचिन्हित दीर्घ of_bus_sbus_get_flags(स्थिर u32 *addr, अचिन्हित दीर्घ flags)
अणु
	वापस IORESOURCE_MEM;
पूर्ण

 /*
 * AMBAPP bus specअगरic translator
 */

अटल पूर्णांक of_bus_ambapp_match(काष्ठा device_node *np)
अणु
	वापस of_node_is_type(np, "ambapp");
पूर्ण

अटल व्योम of_bus_ambapp_count_cells(काष्ठा device_node *child,
				      पूर्णांक *addrc, पूर्णांक *sizec)
अणु
	अगर (addrc)
		*addrc = 1;
	अगर (sizec)
		*sizec = 1;
पूर्ण

अटल पूर्णांक of_bus_ambapp_map(u32 *addr, स्थिर u32 *range,
			     पूर्णांक na, पूर्णांक ns, पूर्णांक pna)
अणु
	वापस of_bus_शेष_map(addr, range, na, ns, pna);
पूर्ण

अटल अचिन्हित दीर्घ of_bus_ambapp_get_flags(स्थिर u32 *addr,
					     अचिन्हित दीर्घ flags)
अणु
	वापस IORESOURCE_MEM;
पूर्ण

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
	/* SBUS */
	अणु
		.name = "sbus",
		.addr_prop_name = "reg",
		.match = of_bus_sbus_match,
		.count_cells = of_bus_sbus_count_cells,
		.map = of_bus_शेष_map,
		.get_flags = of_bus_sbus_get_flags,
	पूर्ण,
	/* AMBA */
	अणु
		.name = "ambapp",
		.addr_prop_name = "reg",
		.match = of_bus_ambapp_match,
		.count_cells = of_bus_ambapp_count_cells,
		.map = of_bus_ambapp_map,
		.get_flags = of_bus_ambapp_get_flags,
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
	अचिन्हित पूर्णांक rlen;
	पूर्णांक rone;

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

	वापस 1;
पूर्ण

अटल पूर्णांक __init use_1to1_mapping(काष्ठा device_node *pp)
अणु
	/* If we have a ranges property in the parent, use it.  */
	अगर (of_find_property(pp, "ranges", शून्य) != शून्य)
		वापस 0;

	/* Some SBUS devices use पूर्णांकermediate nodes to express
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

	/* Conver to num-entries.  */
	num_reg /= na + ns;

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

		flags = bus->get_flags(reg, 0);

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
			r->start = result & 0xffffffff;
			r->end = result + size - 1;
			r->flags = flags | ((result >> 32ULL) & 0xffUL);
		पूर्ण
		r->name = op->dev.of_node->full_name;
	पूर्ण
पूर्ण

अटल काष्ठा platक्रमm_device * __init scan_one_device(काष्ठा device_node *dp,
						 काष्ठा device *parent)
अणु
	काष्ठा platक्रमm_device *op = kzalloc(माप(*op), GFP_KERNEL);
	स्थिर काष्ठा linux_prom_irqs *पूर्णांकr;
	काष्ठा dev_archdata *sd;
	पूर्णांक len, i;

	अगर (!op)
		वापस शून्य;

	sd = &op->dev.archdata;
	sd->op = op;

	op->dev.of_node = dp;

	पूर्णांकr = of_get_property(dp, "intr", &len);
	अगर (पूर्णांकr) अणु
		op->archdata.num_irqs = len / माप(काष्ठा linux_prom_irqs);
		क्रम (i = 0; i < op->archdata.num_irqs; i++)
			op->archdata.irqs[i] =
			    sparc_config.build_device_irq(op, पूर्णांकr[i].pri);
	पूर्ण अन्यथा अणु
		स्थिर अचिन्हित पूर्णांक *irq =
			of_get_property(dp, "interrupts", &len);

		अगर (irq) अणु
			op->archdata.num_irqs = len / माप(अचिन्हित पूर्णांक);
			क्रम (i = 0; i < op->archdata.num_irqs; i++)
				op->archdata.irqs[i] =
				    sparc_config.build_device_irq(op, irq[i]);
		पूर्ण अन्यथा अणु
			op->archdata.num_irqs = 0;
		पूर्ण
	पूर्ण

	build_device_resources(op, parent);

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
	वापस 1;
पूर्ण

__setup("of_debug=", of_debug);
