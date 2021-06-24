<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *    Copyright (C) 2006 Benjamin Herrenschmidt, IBM Corp.
 *			 <benh@kernel.crashing.org>
 *    and		 Arnd Bergmann, IBM Corp.
 *    Merged from घातerpc/kernel/of_platक्रमm.c and
 *    sparcअणु,64पूर्ण/kernel/of_device.c by Stephen Rothwell
 */

#घोषणा pr_fmt(fmt)	"OF: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

स्थिर काष्ठा of_device_id of_शेष_bus_match_table[] = अणु
	अणु .compatible = "simple-bus", पूर्ण,
	अणु .compatible = "simple-mfd", पूर्ण,
	अणु .compatible = "isa", पूर्ण,
#अगर_घोषित CONFIG_ARM_AMBA
	अणु .compatible = "arm,amba-bus", पूर्ण,
#पूर्ण_अगर /* CONFIG_ARM_AMBA */
	अणुपूर्ण /* Empty terminated list */
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_skipped_node_table[] = अणु
	अणु .compatible = "operating-points-v2", पूर्ण,
	अणुपूर्ण /* Empty terminated list */
पूर्ण;

/**
 * of_find_device_by_node - Find the platक्रमm_device associated with a node
 * @np: Poपूर्णांकer to device tree node
 *
 * Takes a reference to the embedded काष्ठा device which needs to be dropped
 * after use.
 *
 * Return: platक्रमm_device poपूर्णांकer, or शून्य अगर not found
 */
काष्ठा platक्रमm_device *of_find_device_by_node(काष्ठा device_node *np)
अणु
	काष्ठा device *dev;

	dev = bus_find_device_by_of_node(&platक्रमm_bus_type, np);
	वापस dev ? to_platक्रमm_device(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL(of_find_device_by_node);

#अगर_घोषित CONFIG_OF_ADDRESS
/*
 * The following routines scan a subtree and रेजिस्टरs a device क्रम
 * each applicable node.
 *
 * Note: sparc करोesn't use these routines because it has a dअगरferent
 * mechanism क्रम creating devices from device tree nodes.
 */

/**
 * of_device_make_bus_id - Use the device node data to assign a unique name
 * @dev: poपूर्णांकer to device काष्ठाure that is linked to a device tree node
 *
 * This routine will first try using the translated bus address to
 * derive a unique name. If it cannot, then it will prepend names from
 * parent nodes until a unique name can be derived.
 */
अटल व्योम of_device_make_bus_id(काष्ठा device *dev)
अणु
	काष्ठा device_node *node = dev->of_node;
	स्थिर __be32 *reg;
	u64 addr;

	/* Conकाष्ठा the name, using parent nodes अगर necessary to ensure uniqueness */
	जबतक (node->parent) अणु
		/*
		 * If the address can be translated, then that is as much
		 * uniqueness as we need. Make it the first component and वापस
		 */
		reg = of_get_property(node, "reg", शून्य);
		अगर (reg && (addr = of_translate_address(node, reg)) != OF_BAD_ADDR) अणु
			dev_set_name(dev, dev_name(dev) ? "%llx.%pOFn:%s" : "%llx.%pOFn",
				     addr, node, dev_name(dev));
			वापस;
		पूर्ण

		/* क्रमmat arguments only used अगर dev_name() resolves to शून्य */
		dev_set_name(dev, dev_name(dev) ? "%s:%s" : "%s",
			     kbasename(node->full_name), dev_name(dev));
		node = node->parent;
	पूर्ण
पूर्ण

/**
 * of_device_alloc - Allocate and initialize an of_device
 * @np: device node to assign to device
 * @bus_id: Name to assign to the device.  May be null to use शेष name.
 * @parent: Parent device.
 */
काष्ठा platक्रमm_device *of_device_alloc(काष्ठा device_node *np,
				  स्थिर अक्षर *bus_id,
				  काष्ठा device *parent)
अणु
	काष्ठा platक्रमm_device *dev;
	पूर्णांक rc, i, num_reg = 0, num_irq;
	काष्ठा resource *res, temp_res;

	dev = platक्रमm_device_alloc("", PLATFORM_DEVID_NONE);
	अगर (!dev)
		वापस शून्य;

	/* count the io and irq resources */
	जबतक (of_address_to_resource(np, num_reg, &temp_res) == 0)
		num_reg++;
	num_irq = of_irq_count(np);

	/* Populate the resource table */
	अगर (num_irq || num_reg) अणु
		res = kसुस्मृति(num_irq + num_reg, माप(*res), GFP_KERNEL);
		अगर (!res) अणु
			platक्रमm_device_put(dev);
			वापस शून्य;
		पूर्ण

		dev->num_resources = num_reg + num_irq;
		dev->resource = res;
		क्रम (i = 0; i < num_reg; i++, res++) अणु
			rc = of_address_to_resource(np, i, res);
			WARN_ON(rc);
		पूर्ण
		अगर (of_irq_to_resource_table(np, res, num_irq) != num_irq)
			pr_debug("not all legacy IRQ resources mapped for %pOFn\n",
				 np);
	पूर्ण

	dev->dev.of_node = of_node_get(np);
	dev->dev.fwnode = &np->fwnode;
	dev->dev.parent = parent ? : &platक्रमm_bus;

	अगर (bus_id)
		dev_set_name(&dev->dev, "%s", bus_id);
	अन्यथा
		of_device_make_bus_id(&dev->dev);

	वापस dev;
पूर्ण
EXPORT_SYMBOL(of_device_alloc);

/**
 * of_platक्रमm_device_create_pdata - Alloc, initialize and रेजिस्टर an of_device
 * @np: poपूर्णांकer to node to create device क्रम
 * @bus_id: name to assign device
 * @platक्रमm_data: poपूर्णांकer to populate platक्रमm_data poपूर्णांकer with
 * @parent: Linux device model parent device.
 *
 * Return: Poपूर्णांकer to created platक्रमm device, or शून्य अगर a device was not
 * रेजिस्टरed.  Unavailable devices will not get रेजिस्टरed.
 */
अटल काष्ठा platक्रमm_device *of_platक्रमm_device_create_pdata(
					काष्ठा device_node *np,
					स्थिर अक्षर *bus_id,
					व्योम *platक्रमm_data,
					काष्ठा device *parent)
अणु
	काष्ठा platक्रमm_device *dev;

	अगर (!of_device_is_available(np) ||
	    of_node_test_and_set_flag(np, OF_POPULATED))
		वापस शून्य;

	dev = of_device_alloc(np, bus_id, parent);
	अगर (!dev)
		जाओ err_clear_flag;

	dev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	अगर (!dev->dev.dma_mask)
		dev->dev.dma_mask = &dev->dev.coherent_dma_mask;
	dev->dev.bus = &platक्रमm_bus_type;
	dev->dev.platक्रमm_data = platक्रमm_data;
	of_msi_configure(&dev->dev, dev->dev.of_node);

	अगर (of_device_add(dev) != 0) अणु
		platक्रमm_device_put(dev);
		जाओ err_clear_flag;
	पूर्ण

	वापस dev;

err_clear_flag:
	of_node_clear_flag(np, OF_POPULATED);
	वापस शून्य;
पूर्ण

/**
 * of_platक्रमm_device_create - Alloc, initialize and रेजिस्टर an of_device
 * @np: poपूर्णांकer to node to create device क्रम
 * @bus_id: name to assign device
 * @parent: Linux device model parent device.
 *
 * Return: Poपूर्णांकer to created platक्रमm device, or शून्य अगर a device was not
 * रेजिस्टरed.  Unavailable devices will not get रेजिस्टरed.
 */
काष्ठा platक्रमm_device *of_platक्रमm_device_create(काष्ठा device_node *np,
					    स्थिर अक्षर *bus_id,
					    काष्ठा device *parent)
अणु
	वापस of_platक्रमm_device_create_pdata(np, bus_id, शून्य, parent);
पूर्ण
EXPORT_SYMBOL(of_platक्रमm_device_create);

#अगर_घोषित CONFIG_ARM_AMBA
अटल काष्ठा amba_device *of_amba_device_create(काष्ठा device_node *node,
						 स्थिर अक्षर *bus_id,
						 व्योम *platक्रमm_data,
						 काष्ठा device *parent)
अणु
	काष्ठा amba_device *dev;
	स्थिर व्योम *prop;
	पूर्णांक i, ret;

	pr_debug("Creating amba device %pOF\n", node);

	अगर (!of_device_is_available(node) ||
	    of_node_test_and_set_flag(node, OF_POPULATED))
		वापस शून्य;

	dev = amba_device_alloc(शून्य, 0, 0);
	अगर (!dev)
		जाओ err_clear_flag;

	/* AMBA devices only support a single DMA mask */
	dev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	dev->dev.dma_mask = &dev->dev.coherent_dma_mask;

	/* setup generic device info */
	dev->dev.of_node = of_node_get(node);
	dev->dev.fwnode = &node->fwnode;
	dev->dev.parent = parent ? : &platक्रमm_bus;
	dev->dev.platक्रमm_data = platक्रमm_data;
	अगर (bus_id)
		dev_set_name(&dev->dev, "%s", bus_id);
	अन्यथा
		of_device_make_bus_id(&dev->dev);

	/* Allow the HW Peripheral ID to be overridden */
	prop = of_get_property(node, "arm,primecell-periphid", शून्य);
	अगर (prop)
		dev->periphid = of_पढ़ो_uदीर्घ(prop, 1);

	/* Decode the IRQs and address ranges */
	क्रम (i = 0; i < AMBA_NR_IRQS; i++)
		dev->irq[i] = irq_of_parse_and_map(node, i);

	ret = of_address_to_resource(node, 0, &dev->res);
	अगर (ret) अणु
		pr_err("amba: of_address_to_resource() failed (%d) for %pOF\n",
		       ret, node);
		जाओ err_मुक्त;
	पूर्ण

	ret = amba_device_add(dev, &iomem_resource);
	अगर (ret) अणु
		pr_err("amba_device_add() failed (%d) for %pOF\n",
		       ret, node);
		जाओ err_मुक्त;
	पूर्ण

	वापस dev;

err_मुक्त:
	amba_device_put(dev);
err_clear_flag:
	of_node_clear_flag(node, OF_POPULATED);
	वापस शून्य;
पूर्ण
#अन्यथा /* CONFIG_ARM_AMBA */
अटल काष्ठा amba_device *of_amba_device_create(काष्ठा device_node *node,
						 स्थिर अक्षर *bus_id,
						 व्योम *platक्रमm_data,
						 काष्ठा device *parent)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM_AMBA */

/*
 * of_dev_lookup() - Given a device node, lookup the preferred Linux name
 */
अटल स्थिर काष्ठा of_dev_auxdata *of_dev_lookup(स्थिर काष्ठा of_dev_auxdata *lookup,
				 काष्ठा device_node *np)
अणु
	स्थिर काष्ठा of_dev_auxdata *auxdata;
	काष्ठा resource res;
	पूर्णांक compatible = 0;

	अगर (!lookup)
		वापस शून्य;

	auxdata = lookup;
	क्रम (; auxdata->compatible; auxdata++) अणु
		अगर (!of_device_is_compatible(np, auxdata->compatible))
			जारी;
		compatible++;
		अगर (!of_address_to_resource(np, 0, &res))
			अगर (res.start != auxdata->phys_addr)
				जारी;
		pr_debug("%pOF: devname=%s\n", np, auxdata->name);
		वापस auxdata;
	पूर्ण

	अगर (!compatible)
		वापस शून्य;

	/* Try compatible match अगर no phys_addr and name are specअगरied */
	auxdata = lookup;
	क्रम (; auxdata->compatible; auxdata++) अणु
		अगर (!of_device_is_compatible(np, auxdata->compatible))
			जारी;
		अगर (!auxdata->phys_addr && !auxdata->name) अणु
			pr_debug("%pOF: compatible match\n", np);
			वापस auxdata;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * of_platक्रमm_bus_create() - Create a device क्रम a node and its children.
 * @bus: device node of the bus to instantiate
 * @matches: match table क्रम bus nodes
 * @lookup: auxdata table क्रम matching id and platक्रमm_data with device nodes
 * @parent: parent क्रम new device, or शून्य क्रम top level.
 * @strict: require compatible property
 *
 * Creates a platक्रमm_device क्रम the provided device_node, and optionally
 * recursively create devices क्रम all the child nodes.
 */
अटल पूर्णांक of_platक्रमm_bus_create(काष्ठा device_node *bus,
				  स्थिर काष्ठा of_device_id *matches,
				  स्थिर काष्ठा of_dev_auxdata *lookup,
				  काष्ठा device *parent, bool strict)
अणु
	स्थिर काष्ठा of_dev_auxdata *auxdata;
	काष्ठा device_node *child;
	काष्ठा platक्रमm_device *dev;
	स्थिर अक्षर *bus_id = शून्य;
	व्योम *platक्रमm_data = शून्य;
	पूर्णांक rc = 0;

	/* Make sure it has a compatible property */
	अगर (strict && (!of_get_property(bus, "compatible", शून्य))) अणु
		pr_debug("%s() - skipping %pOF, no compatible prop\n",
			 __func__, bus);
		वापस 0;
	पूर्ण

	/* Skip nodes क्रम which we करोn't want to create devices */
	अगर (unlikely(of_match_node(of_skipped_node_table, bus))) अणु
		pr_debug("%s() - skipping %pOF node\n", __func__, bus);
		वापस 0;
	पूर्ण

	अगर (of_node_check_flag(bus, OF_POPULATED_BUS)) अणु
		pr_debug("%s() - skipping %pOF, already populated\n",
			__func__, bus);
		वापस 0;
	पूर्ण

	auxdata = of_dev_lookup(lookup, bus);
	अगर (auxdata) अणु
		bus_id = auxdata->name;
		platक्रमm_data = auxdata->platक्रमm_data;
	पूर्ण

	अगर (of_device_is_compatible(bus, "arm,primecell")) अणु
		/*
		 * Don't वापस an error here to keep compatibility with older
		 * device tree files.
		 */
		of_amba_device_create(bus, bus_id, platक्रमm_data, parent);
		वापस 0;
	पूर्ण

	dev = of_platक्रमm_device_create_pdata(bus, bus_id, platक्रमm_data, parent);
	अगर (!dev || !of_match_node(matches, bus))
		वापस 0;

	क्रम_each_child_of_node(bus, child) अणु
		pr_debug("   create child: %pOF\n", child);
		rc = of_platक्रमm_bus_create(child, matches, lookup, &dev->dev, strict);
		अगर (rc) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण
	of_node_set_flag(bus, OF_POPULATED_BUS);
	वापस rc;
पूर्ण

/**
 * of_platक्रमm_bus_probe() - Probe the device-tree क्रम platक्रमm buses
 * @root: parent of the first level to probe or शून्य क्रम the root of the tree
 * @matches: match table क्रम bus nodes
 * @parent: parent to hook devices from, शून्य क्रम toplevel
 *
 * Note that children of the provided root are not instantiated as devices
 * unless the specअगरied root itself matches the bus list and is not शून्य.
 */
पूर्णांक of_platक्रमm_bus_probe(काष्ठा device_node *root,
			  स्थिर काष्ठा of_device_id *matches,
			  काष्ठा device *parent)
अणु
	काष्ठा device_node *child;
	पूर्णांक rc = 0;

	root = root ? of_node_get(root) : of_find_node_by_path("/");
	अगर (!root)
		वापस -EINVAL;

	pr_debug("%s()\n", __func__);
	pr_debug(" starting at: %pOF\n", root);

	/* Do a self check of bus type, अगर there's a match, create children */
	अगर (of_match_node(matches, root)) अणु
		rc = of_platक्रमm_bus_create(root, matches, शून्य, parent, false);
	पूर्ण अन्यथा क्रम_each_child_of_node(root, child) अणु
		अगर (!of_match_node(matches, child))
			जारी;
		rc = of_platक्रमm_bus_create(child, matches, शून्य, parent, false);
		अगर (rc) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(root);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(of_platक्रमm_bus_probe);

/**
 * of_platक्रमm_populate() - Populate platक्रमm_devices from device tree data
 * @root: parent of the first level to probe or शून्य क्रम the root of the tree
 * @matches: match table, शून्य to use the शेष
 * @lookup: auxdata table क्रम matching id and platक्रमm_data with device nodes
 * @parent: parent to hook devices from, शून्य क्रम toplevel
 *
 * Similar to of_platक्रमm_bus_probe(), this function walks the device tree
 * and creates devices from nodes.  It dअगरfers in that it follows the modern
 * convention of requiring all device nodes to have a 'compatible' property,
 * and it is suitable क्रम creating devices which are children of the root
 * node (of_platक्रमm_bus_probe will only create children of the root which
 * are selected by the @matches argument).
 *
 * New board support should be using this function instead of
 * of_platक्रमm_bus_probe().
 *
 * Return: 0 on success, < 0 on failure.
 */
पूर्णांक of_platक्रमm_populate(काष्ठा device_node *root,
			स्थिर काष्ठा of_device_id *matches,
			स्थिर काष्ठा of_dev_auxdata *lookup,
			काष्ठा device *parent)
अणु
	काष्ठा device_node *child;
	पूर्णांक rc = 0;

	root = root ? of_node_get(root) : of_find_node_by_path("/");
	अगर (!root)
		वापस -EINVAL;

	pr_debug("%s()\n", __func__);
	pr_debug(" starting at: %pOF\n", root);

	device_links_supplier_sync_state_छोड़ो();
	क्रम_each_child_of_node(root, child) अणु
		rc = of_platक्रमm_bus_create(child, matches, lookup, parent, true);
		अगर (rc) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण
	device_links_supplier_sync_state_resume();

	of_node_set_flag(root, OF_POPULATED_BUS);

	of_node_put(root);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(of_platक्रमm_populate);

पूर्णांक of_platक्रमm_शेष_populate(काष्ठा device_node *root,
				 स्थिर काष्ठा of_dev_auxdata *lookup,
				 काष्ठा device *parent)
अणु
	वापस of_platक्रमm_populate(root, of_शेष_bus_match_table, lookup,
				    parent);
पूर्ण
EXPORT_SYMBOL_GPL(of_platक्रमm_शेष_populate);

#अगर_अघोषित CONFIG_PPC
अटल स्थिर काष्ठा of_device_id reserved_mem_matches[] = अणु
	अणु .compatible = "qcom,rmtfs-mem" पूर्ण,
	अणु .compatible = "qcom,cmd-db" पूर्ण,
	अणु .compatible = "ramoops" पूर्ण,
	अणु .compatible = "nvmem-rmem" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init of_platक्रमm_शेष_populate_init(व्योम)
अणु
	काष्ठा device_node *node;

	device_links_supplier_sync_state_छोड़ो();

	अगर (!of_have_populated_dt())
		वापस -ENODEV;

	/*
	 * Handle certain compatibles explicitly, since we करोn't want to create
	 * platक्रमm_devices क्रम every node in /reserved-memory with a
	 * "compatible",
	 */
	क्रम_each_matching_node(node, reserved_mem_matches)
		of_platक्रमm_device_create(node, शून्य, शून्य);

	node = of_find_node_by_path("/firmware");
	अगर (node) अणु
		of_platक्रमm_populate(node, शून्य, शून्य, शून्य);
		of_node_put(node);
	पूर्ण

	/* Populate everything अन्यथा. */
	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);

	वापस 0;
पूर्ण
arch_initcall_sync(of_platक्रमm_शेष_populate_init);

अटल पूर्णांक __init of_platक्रमm_sync_state_init(व्योम)
अणु
	device_links_supplier_sync_state_resume();
	वापस 0;
पूर्ण
late_initcall_sync(of_platक्रमm_sync_state_init);
#पूर्ण_अगर

पूर्णांक of_platक्रमm_device_destroy(काष्ठा device *dev, व्योम *data)
अणु
	/* Do not touch devices not populated from the device tree */
	अगर (!dev->of_node || !of_node_check_flag(dev->of_node, OF_POPULATED))
		वापस 0;

	/* Recurse क्रम any nodes that were treated as busses */
	अगर (of_node_check_flag(dev->of_node, OF_POPULATED_BUS))
		device_क्रम_each_child(dev, शून्य, of_platक्रमm_device_destroy);

	of_node_clear_flag(dev->of_node, OF_POPULATED);
	of_node_clear_flag(dev->of_node, OF_POPULATED_BUS);

	अगर (dev->bus == &platक्रमm_bus_type)
		platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
#अगर_घोषित CONFIG_ARM_AMBA
	अन्यथा अगर (dev->bus == &amba_bustype)
		amba_device_unरेजिस्टर(to_amba_device(dev));
#पूर्ण_अगर

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_platक्रमm_device_destroy);

/**
 * of_platक्रमm_depopulate() - Remove devices populated from device tree
 * @parent: device which children will be हटाओd
 *
 * Complementary to of_platक्रमm_populate(), this function हटाओs children
 * of the given device (and, recurrently, their children) that have been
 * created from their respective device tree nodes (and only those,
 * leaving others - eg. manually created - unharmed).
 */
व्योम of_platक्रमm_depopulate(काष्ठा device *parent)
अणु
	अगर (parent->of_node && of_node_check_flag(parent->of_node, OF_POPULATED_BUS)) अणु
		device_क्रम_each_child_reverse(parent, शून्य, of_platक्रमm_device_destroy);
		of_node_clear_flag(parent->of_node, OF_POPULATED_BUS);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(of_platक्रमm_depopulate);

अटल व्योम devm_of_platक्रमm_populate_release(काष्ठा device *dev, व्योम *res)
अणु
	of_platक्रमm_depopulate(*(काष्ठा device **)res);
पूर्ण

/**
 * devm_of_platक्रमm_populate() - Populate platक्रमm_devices from device tree data
 * @dev: device that requested to populate from device tree data
 *
 * Similar to of_platक्रमm_populate(), but will स्वतःmatically call
 * of_platक्रमm_depopulate() when the device is unbound from the bus.
 *
 * Return: 0 on success, < 0 on failure.
 */
पूर्णांक devm_of_platक्रमm_populate(काष्ठा device *dev)
अणु
	काष्ठा device **ptr;
	पूर्णांक ret;

	अगर (!dev)
		वापस -EINVAL;

	ptr = devres_alloc(devm_of_platक्रमm_populate_release,
			   माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);
	अगर (ret) अणु
		devres_मुक्त(ptr);
	पूर्ण अन्यथा अणु
		*ptr = dev;
		devres_add(dev, ptr);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_platक्रमm_populate);

अटल पूर्णांक devm_of_platक्रमm_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा device **ptr = res;

	अगर (!ptr) अणु
		WARN_ON(!ptr);
		वापस 0;
	पूर्ण

	वापस *ptr == data;
पूर्ण

/**
 * devm_of_platक्रमm_depopulate() - Remove devices populated from device tree
 * @dev: device that requested to depopulate from device tree data
 *
 * Complementary to devm_of_platक्रमm_populate(), this function हटाओs children
 * of the given device (and, recurrently, their children) that have been
 * created from their respective device tree nodes (and only those,
 * leaving others - eg. manually created - unharmed).
 */
व्योम devm_of_platक्रमm_depopulate(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = devres_release(dev, devm_of_platक्रमm_populate_release,
			     devm_of_platक्रमm_match, dev);

	WARN_ON(ret);
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_platक्रमm_depopulate);

#अगर_घोषित CONFIG_OF_DYNAMIC
अटल पूर्णांक of_platक्रमm_notअगरy(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ action, व्योम *arg)
अणु
	काष्ठा of_reconfig_data *rd = arg;
	काष्ठा platक्रमm_device *pdev_parent, *pdev;
	bool children_left;

	चयन (of_reconfig_get_state_change(action, rd)) अणु
	हाल OF_RECONFIG_CHANGE_ADD:
		/* verअगरy that the parent is a bus */
		अगर (!of_node_check_flag(rd->dn->parent, OF_POPULATED_BUS))
			वापस NOTIFY_OK;	/* not क्रम us */

		/* alपढ़ोy populated? (driver using of_populate manually) */
		अगर (of_node_check_flag(rd->dn, OF_POPULATED))
			वापस NOTIFY_OK;

		/* pdev_parent may be शून्य when no bus platक्रमm device */
		pdev_parent = of_find_device_by_node(rd->dn->parent);
		pdev = of_platक्रमm_device_create(rd->dn, शून्य,
				pdev_parent ? &pdev_parent->dev : शून्य);
		platक्रमm_device_put(pdev_parent);

		अगर (pdev == शून्य) अणु
			pr_err("%s: failed to create for '%pOF'\n",
					__func__, rd->dn);
			/* of_platक्रमm_device_create tosses the error code */
			वापस notअगरier_from_त्रुटि_सं(-EINVAL);
		पूर्ण
		अवरोध;

	हाल OF_RECONFIG_CHANGE_REMOVE:

		/* alपढ़ोy depopulated? */
		अगर (!of_node_check_flag(rd->dn, OF_POPULATED))
			वापस NOTIFY_OK;

		/* find our device by node */
		pdev = of_find_device_by_node(rd->dn);
		अगर (pdev == शून्य)
			वापस NOTIFY_OK;	/* no? not meant क्रम us */

		/* unरेजिस्टर takes one ref away */
		of_platक्रमm_device_destroy(&pdev->dev, &children_left);

		/* and put the reference of the find */
		platक्रमm_device_put(pdev);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block platक्रमm_of_notअगरier = अणु
	.notअगरier_call = of_platक्रमm_notअगरy,
पूर्ण;

व्योम of_platक्रमm_रेजिस्टर_reconfig_notअगरier(व्योम)
अणु
	WARN_ON(of_reconfig_notअगरier_रेजिस्टर(&platक्रमm_of_notअगरier));
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_DYNAMIC */

#पूर्ण_अगर /* CONFIG_OF_ADDRESS */
