<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FDT Address translation based on u-boot fdt_support.c which in turn was
 * based on the kernel unflattened DT address translation code.
 *
 * (C) Copyright 2007
 * Gerald Van Baren, Custom IDEAS, vanbaren@cideas.com
 *
 * Copyright 2010-2011 Freescale Semiconductor, Inc.
 */

#घोषणा pr_fmt(fmt)	"OF: fdt: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/sizes.h>

/* Max address size we deal with */
#घोषणा OF_MAX_ADDR_CELLS	4
#घोषणा OF_CHECK_COUNTS(na, ns)	((na) > 0 && (na) <= OF_MAX_ADDR_CELLS && \
			(ns) > 0)

/* Debug utility */
#अगर_घोषित DEBUG
अटल व्योम __init of_dump_addr(स्थिर अक्षर *s, स्थिर __be32 *addr, पूर्णांक na)
अणु
	pr_debug("%s", s);
	जबतक(na--)
		pr_cont(" %08x", *(addr++));
	pr_cont("\n");
पूर्ण
#अन्यथा
अटल व्योम __init of_dump_addr(स्थिर अक्षर *s, स्थिर __be32 *addr, पूर्णांक na) अणु पूर्ण
#पूर्ण_अगर

/* Callbacks क्रम bus specअगरic translators */
काष्ठा of_bus अणु
	व्योम		(*count_cells)(स्थिर व्योम *blob, पूर्णांक parentoffset,
				पूर्णांक *addrc, पूर्णांक *sizec);
	u64		(*map)(__be32 *addr, स्थिर __be32 *range,
				पूर्णांक na, पूर्णांक ns, पूर्णांक pna);
	पूर्णांक		(*translate)(__be32 *addr, u64 offset, पूर्णांक na);
पूर्ण;

/* Default translator (generic bus) */
अटल व्योम __init fdt_bus_शेष_count_cells(स्थिर व्योम *blob, पूर्णांक parentoffset,
					       पूर्णांक *addrc, पूर्णांक *sizec)
अणु
	स्थिर __be32 *prop;

	अगर (addrc) अणु
		prop = fdt_getprop(blob, parentoffset, "#address-cells", शून्य);
		अगर (prop)
			*addrc = be32_to_cpup(prop);
		अन्यथा
			*addrc = dt_root_addr_cells;
	पूर्ण

	अगर (sizec) अणु
		prop = fdt_getprop(blob, parentoffset, "#size-cells", शून्य);
		अगर (prop)
			*sizec = be32_to_cpup(prop);
		अन्यथा
			*sizec = dt_root_size_cells;
	पूर्ण
पूर्ण

अटल u64 __init fdt_bus_शेष_map(__be32 *addr, स्थिर __be32 *range,
				      पूर्णांक na, पूर्णांक ns, पूर्णांक pna)
अणु
	u64 cp, s, da;

	cp = of_पढ़ो_number(range, na);
	s  = of_पढ़ो_number(range + na + pna, ns);
	da = of_पढ़ो_number(addr, na);

	pr_debug("default map, cp=%llx, s=%llx, da=%llx\n",
	    cp, s, da);

	अगर (da < cp || da >= (cp + s))
		वापस OF_BAD_ADDR;
	वापस da - cp;
पूर्ण

अटल पूर्णांक __init fdt_bus_शेष_translate(__be32 *addr, u64 offset, पूर्णांक na)
अणु
	u64 a = of_पढ़ो_number(addr, na);
	स_रखो(addr, 0, na * 4);
	a += offset;
	अगर (na > 1)
		addr[na - 2] = cpu_to_fdt32(a >> 32);
	addr[na - 1] = cpu_to_fdt32(a & 0xffffffffu);

	वापस 0;
पूर्ण

/* Array of bus specअगरic translators */
अटल स्थिर काष्ठा of_bus of_busses[] __initस्थिर = अणु
	/* Default */
	अणु
		.count_cells = fdt_bus_शेष_count_cells,
		.map = fdt_bus_शेष_map,
		.translate = fdt_bus_शेष_translate,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init fdt_translate_one(स्थिर व्योम *blob, पूर्णांक parent,
				    स्थिर काष्ठा of_bus *bus,
				    स्थिर काष्ठा of_bus *pbus, __be32 *addr,
				    पूर्णांक na, पूर्णांक ns, पूर्णांक pna, स्थिर अक्षर *rprop)
अणु
	स्थिर __be32 *ranges;
	पूर्णांक rlen;
	पूर्णांक rone;
	u64 offset = OF_BAD_ADDR;

	ranges = fdt_getprop(blob, parent, rprop, &rlen);
	अगर (!ranges)
		वापस 1;
	अगर (rlen == 0) अणु
		offset = of_पढ़ो_number(addr, na);
		स_रखो(addr, 0, pna * 4);
		pr_debug("empty ranges, 1:1 translation\n");
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
	pr_debug("with offset: %llx\n", offset);

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
 */
अटल u64 __init fdt_translate_address(स्थिर व्योम *blob, पूर्णांक node_offset)
अणु
	पूर्णांक parent, len;
	स्थिर काष्ठा of_bus *bus, *pbus;
	स्थिर __be32 *reg;
	__be32 addr[OF_MAX_ADDR_CELLS];
	पूर्णांक na, ns, pna, pns;
	u64 result = OF_BAD_ADDR;

	pr_debug("** translation for device %s **\n",
		 fdt_get_name(blob, node_offset, शून्य));

	reg = fdt_getprop(blob, node_offset, "reg", &len);
	अगर (!reg) अणु
		pr_err("warning: device tree node '%s' has no address.\n",
			fdt_get_name(blob, node_offset, शून्य));
		जाओ bail;
	पूर्ण

	/* Get parent & match bus type */
	parent = fdt_parent_offset(blob, node_offset);
	अगर (parent < 0)
		जाओ bail;
	bus = &of_busses[0];

	/* Cound address cells & copy address locally */
	bus->count_cells(blob, parent, &na, &ns);
	अगर (!OF_CHECK_COUNTS(na, ns)) अणु
		pr_err("Bad cell count for %s\n",
		       fdt_get_name(blob, node_offset, शून्य));
		जाओ bail;
	पूर्ण
	स_नकल(addr, reg, na * 4);

	pr_debug("bus (na=%d, ns=%d) on %s\n",
		 na, ns, fdt_get_name(blob, parent, शून्य));
	of_dump_addr("translating address:", addr, na);

	/* Translate */
	क्रम (;;) अणु
		/* Switch to parent bus */
		node_offset = parent;
		parent = fdt_parent_offset(blob, node_offset);

		/* If root, we have finished */
		अगर (parent < 0) अणु
			pr_debug("reached root node\n");
			result = of_पढ़ो_number(addr, na);
			अवरोध;
		पूर्ण

		/* Get new parent bus and counts */
		pbus = &of_busses[0];
		pbus->count_cells(blob, parent, &pna, &pns);
		अगर (!OF_CHECK_COUNTS(pna, pns)) अणु
			pr_err("Bad cell count for %s\n",
				fdt_get_name(blob, node_offset, शून्य));
			अवरोध;
		पूर्ण

		pr_debug("parent bus (na=%d, ns=%d) on %s\n",
			 pna, pns, fdt_get_name(blob, parent, शून्य));

		/* Apply bus translation */
		अगर (fdt_translate_one(blob, node_offset, bus, pbus,
					addr, na, ns, pna, "ranges"))
			अवरोध;

		/* Complete the move up one level */
		na = pna;
		ns = pns;
		bus = pbus;

		of_dump_addr("one level translation:", addr, na);
	पूर्ण
 bail:
	वापस result;
पूर्ण

/**
 * of_flat_dt_translate_address - translate DT addr पूर्णांकo CPU phys addr
 * @node: node in the flat blob
 */
u64 __init of_flat_dt_translate_address(अचिन्हित दीर्घ node)
अणु
	वापस fdt_translate_address(initial_boot_params, node);
पूर्ण
