<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/export.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>

#समावेश "of_device_common.h"

अचिन्हित पूर्णांक irq_of_parse_and_map(काष्ठा device_node *node, पूर्णांक index)
अणु
	काष्ठा platक्रमm_device *op = of_find_device_by_node(node);

	अगर (!op || index >= op->archdata.num_irqs)
		वापस 0;

	वापस op->archdata.irqs[index];
पूर्ण
EXPORT_SYMBOL(irq_of_parse_and_map);

पूर्णांक of_address_to_resource(काष्ठा device_node *node, पूर्णांक index,
			   काष्ठा resource *r)
अणु
	काष्ठा platक्रमm_device *op = of_find_device_by_node(node);

	अगर (!op || index >= op->num_resources)
		वापस -EINVAL;

	स_नकल(r, &op->archdata.resource[index], माप(*r));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_address_to_resource);

व्योम __iomem *of_iomap(काष्ठा device_node *node, पूर्णांक index)
अणु
	काष्ठा platक्रमm_device *op = of_find_device_by_node(node);
	काष्ठा resource *r;

	अगर (!op || index >= op->num_resources)
		वापस शून्य;

	r = &op->archdata.resource[index];

	वापस of_ioremap(r, 0, resource_size(r), (अक्षर *) r->name);
पूर्ण
EXPORT_SYMBOL(of_iomap);

/* Take the archdata values क्रम IOMMU, STC, and HOSTDATA found in
 * BUS and propagate to all child platक्रमm_device objects.
 */
व्योम of_propagate_archdata(काष्ठा platक्रमm_device *bus)
अणु
	काष्ठा dev_archdata *bus_sd = &bus->dev.archdata;
	काष्ठा device_node *bus_dp = bus->dev.of_node;
	काष्ठा device_node *dp;

	क्रम (dp = bus_dp->child; dp; dp = dp->sibling) अणु
		काष्ठा platक्रमm_device *op = of_find_device_by_node(dp);

		op->dev.archdata.iommu = bus_sd->iommu;
		op->dev.archdata.stc = bus_sd->stc;
		op->dev.archdata.host_controller = bus_sd->host_controller;
		op->dev.archdata.numa_node = bus_sd->numa_node;
		op->dev.dma_ops = bus->dev.dma_ops;

		अगर (dp->child)
			of_propagate_archdata(op);
	पूर्ण
पूर्ण

अटल व्योम get_cells(काष्ठा device_node *dp, पूर्णांक *addrc, पूर्णांक *sizec)
अणु
	अगर (addrc)
		*addrc = of_n_addr_cells(dp);
	अगर (sizec)
		*sizec = of_n_size_cells(dp);
पूर्ण

/*
 * Default translator (generic bus)
 */

व्योम of_bus_शेष_count_cells(काष्ठा device_node *dev, पूर्णांक *addrc, पूर्णांक *sizec)
अणु
	get_cells(dev, addrc, sizec);
पूर्ण

/* Make sure the least signअगरicant 64-bits are in-range.  Even
 * क्रम 3 or 4 cell values it is a good enough approximation.
 */
पूर्णांक of_out_of_range(स्थिर u32 *addr, स्थिर u32 *base,
		    स्थिर u32 *size, पूर्णांक na, पूर्णांक ns)
अणु
	u64 a = of_पढ़ो_addr(addr, na);
	u64 b = of_पढ़ो_addr(base, na);

	अगर (a < b)
		वापस 1;

	b += of_पढ़ो_addr(size, ns);
	अगर (a >= b)
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक of_bus_शेष_map(u32 *addr, स्थिर u32 *range, पूर्णांक na, पूर्णांक ns, पूर्णांक pna)
अणु
	u32 result[OF_MAX_ADDR_CELLS];
	पूर्णांक i;

	अगर (ns > 2) अणु
		prपूर्णांकk("of_device: Cannot handle size cells (%d) > 2.", ns);
		वापस -EINVAL;
	पूर्ण

	अगर (of_out_of_range(addr, range, range + na + pna, na, ns))
		वापस -EINVAL;

	/* Start with the parent range base.  */
	स_नकल(result, range + na, pna * 4);

	/* Add in the child address offset.  */
	क्रम (i = 0; i < na; i++)
		result[pna - 1 - i] +=
			(addr[na - 1 - i] -
			 range[na - 1 - i]);

	स_नकल(addr, result, pna * 4);

	वापस 0;
पूर्ण

अचिन्हित दीर्घ of_bus_शेष_get_flags(स्थिर u32 *addr, अचिन्हित दीर्घ flags)
अणु
	अगर (flags)
		वापस flags;
	वापस IORESOURCE_MEM;
पूर्ण

/*
 * SBUS bus specअगरic translator
 */

पूर्णांक of_bus_sbus_match(काष्ठा device_node *np)
अणु
	काष्ठा device_node *dp = np;

	जबतक (dp) अणु
		अगर (of_node_name_eq(dp, "sbus") ||
		    of_node_name_eq(dp, "sbi"))
			वापस 1;

		/* Have a look at use_1to1_mapping().  We're trying
		 * to match SBUS अगर that's the top-level bus and we
		 * करोn't have some पूर्णांकervening real bus that provides
		 * ranges based translations.
		 */
		अगर (of_find_property(dp, "ranges", शून्य) != शून्य)
			अवरोध;

		dp = dp->parent;
	पूर्ण

	वापस 0;
पूर्ण

व्योम of_bus_sbus_count_cells(काष्ठा device_node *child, पूर्णांक *addrc, पूर्णांक *sizec)
अणु
	अगर (addrc)
		*addrc = 2;
	अगर (sizec)
		*sizec = 1;
पूर्ण
