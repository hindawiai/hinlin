<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Derived from arch/i386/kernel/irq.c
 *    Copyright (C) 1992 Linus Torvalds
 *  Adapted from arch/i386 by Gary Thomas
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *  Updated and modअगरied by Cort Dougan <cort@fsmद_असल.com>
 *    Copyright (C) 1996-2001 Cort Dougan
 *  Adapted क्रम Power Macपूर्णांकosh by Paul Mackerras
 *    Copyright (C) 1996 Paul Mackerras (paulus@cs.anu.edu.au)
 *
 * This file contains the code used to make IRQ descriptions in the
 * device tree to actual irq numbers on an पूर्णांकerrupt controller
 * driver.
 */

#घोषणा pr_fmt(fmt)	"OF: " fmt

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

/**
 * irq_of_parse_and_map - Parse and map an पूर्णांकerrupt पूर्णांकo linux virq space
 * @dev: Device node of the device whose पूर्णांकerrupt is to be mapped
 * @index: Index of the पूर्णांकerrupt to map
 *
 * This function is a wrapper that chains of_irq_parse_one() and
 * irq_create_of_mapping() to make things easier to callers
 */
अचिन्हित पूर्णांक irq_of_parse_and_map(काष्ठा device_node *dev, पूर्णांक index)
अणु
	काष्ठा of_phandle_args oirq;

	अगर (of_irq_parse_one(dev, index, &oirq))
		वापस 0;

	वापस irq_create_of_mapping(&oirq);
पूर्ण
EXPORT_SYMBOL_GPL(irq_of_parse_and_map);

/**
 * of_irq_find_parent - Given a device node, find its पूर्णांकerrupt parent node
 * @child: poपूर्णांकer to device node
 *
 * Return: A poपूर्णांकer to the पूर्णांकerrupt parent node, or शून्य अगर the पूर्णांकerrupt
 * parent could not be determined.
 */
काष्ठा device_node *of_irq_find_parent(काष्ठा device_node *child)
अणु
	काष्ठा device_node *p;
	phandle parent;

	अगर (!of_node_get(child))
		वापस शून्य;

	करो अणु
		अगर (of_property_पढ़ो_u32(child, "interrupt-parent", &parent)) अणु
			p = of_get_parent(child);
		पूर्ण अन्यथा	अणु
			अगर (of_irq_workarounds & OF_IMAP_NO_PHANDLE)
				p = of_node_get(of_irq_dflt_pic);
			अन्यथा
				p = of_find_node_by_phandle(parent);
		पूर्ण
		of_node_put(child);
		child = p;
	पूर्ण जबतक (p && of_get_property(p, "#interrupt-cells", शून्य) == शून्य);

	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(of_irq_find_parent);

/**
 * of_irq_parse_raw - Low level पूर्णांकerrupt tree parsing
 * @addr:	address specअगरier (start of "reg" property of the device) in be32 क्रमmat
 * @out_irq:	काष्ठाure of_phandle_args updated by this function
 *
 * This function is a low-level पूर्णांकerrupt tree walking function. It
 * can be used to करो a partial walk with synthetized reg and पूर्णांकerrupts
 * properties, क्रम example when resolving PCI पूर्णांकerrupts when no device
 * node exist क्रम the parent. It takes an पूर्णांकerrupt specअगरier काष्ठाure as
 * input, walks the tree looking क्रम any पूर्णांकerrupt-map properties, translates
 * the specअगरier क्रम each map, and then वापसs the translated map.
 *
 * Return: 0 on success and a negative number on error
 */
पूर्णांक of_irq_parse_raw(स्थिर __be32 *addr, काष्ठा of_phandle_args *out_irq)
अणु
	काष्ठा device_node *ipar, *tnode, *old = शून्य, *newpar = शून्य;
	__be32 initial_match_array[MAX_PHANDLE_ARGS];
	स्थिर __be32 *match_array = initial_match_array;
	स्थिर __be32 *पंचांगp, *imap, *imask, dummy_imask[] = अणु [0 ... MAX_PHANDLE_ARGS] = cpu_to_be32(~0) पूर्ण;
	u32 पूर्णांकsize = 1, addrsize, newपूर्णांकsize = 0, newaddrsize = 0;
	पूर्णांक imaplen, match, i, rc = -EINVAL;

#अगर_घोषित DEBUG
	of_prपूर्णांक_phandle_args("of_irq_parse_raw: ", out_irq);
#पूर्ण_अगर

	ipar = of_node_get(out_irq->np);

	/* First get the #पूर्णांकerrupt-cells property of the current cursor
	 * that tells us how to पूर्णांकerpret the passed-in पूर्णांकspec. If there
	 * is none, we are nice and just walk up the tree
	 */
	करो अणु
		अगर (!of_property_पढ़ो_u32(ipar, "#interrupt-cells", &पूर्णांकsize))
			अवरोध;
		tnode = ipar;
		ipar = of_irq_find_parent(ipar);
		of_node_put(tnode);
	पूर्ण जबतक (ipar);
	अगर (ipar == शून्य) अणु
		pr_debug(" -> no parent found !\n");
		जाओ fail;
	पूर्ण

	pr_debug("of_irq_parse_raw: ipar=%pOF, size=%d\n", ipar, पूर्णांकsize);

	अगर (out_irq->args_count != पूर्णांकsize)
		जाओ fail;

	/* Look क्रम this #address-cells. We have to implement the old linux
	 * trick of looking क्रम the parent here as some device-trees rely on it
	 */
	old = of_node_get(ipar);
	करो अणु
		पंचांगp = of_get_property(old, "#address-cells", शून्य);
		tnode = of_get_parent(old);
		of_node_put(old);
		old = tnode;
	पूर्ण जबतक (old && पंचांगp == शून्य);
	of_node_put(old);
	old = शून्य;
	addrsize = (पंचांगp == शून्य) ? 2 : be32_to_cpu(*पंचांगp);

	pr_debug(" -> addrsize=%d\n", addrsize);

	/* Range check so that the temporary buffer करोesn't overflow */
	अगर (WARN_ON(addrsize + पूर्णांकsize > MAX_PHANDLE_ARGS)) अणु
		rc = -EFAULT;
		जाओ fail;
	पूर्ण

	/* Precalculate the match array - this simplअगरies match loop */
	क्रम (i = 0; i < addrsize; i++)
		initial_match_array[i] = addr ? addr[i] : 0;
	क्रम (i = 0; i < पूर्णांकsize; i++)
		initial_match_array[addrsize + i] = cpu_to_be32(out_irq->args[i]);

	/* Now start the actual "proper" walk of the पूर्णांकerrupt tree */
	जबतक (ipar != शून्य) अणु
		/* Now check अगर cursor is an पूर्णांकerrupt-controller and अगर it is
		 * then we are करोne
		 */
		अगर (of_property_पढ़ो_bool(ipar, "interrupt-controller")) अणु
			pr_debug(" -> got it !\n");
			वापस 0;
		पूर्ण

		/*
		 * पूर्णांकerrupt-map parsing करोes not work without a reg
		 * property when #address-cells != 0
		 */
		अगर (addrsize && !addr) अणु
			pr_debug(" -> no reg passed in when needed !\n");
			जाओ fail;
		पूर्ण

		/* Now look क्रम an पूर्णांकerrupt-map */
		imap = of_get_property(ipar, "interrupt-map", &imaplen);
		/* No पूर्णांकerrupt map, check क्रम an पूर्णांकerrupt parent */
		अगर (imap == शून्य) अणु
			pr_debug(" -> no map, getting parent\n");
			newpar = of_irq_find_parent(ipar);
			जाओ skiplevel;
		पूर्ण
		imaplen /= माप(u32);

		/* Look क्रम a mask */
		imask = of_get_property(ipar, "interrupt-map-mask", शून्य);
		अगर (!imask)
			imask = dummy_imask;

		/* Parse पूर्णांकerrupt-map */
		match = 0;
		जबतक (imaplen > (addrsize + पूर्णांकsize + 1) && !match) अणु
			/* Compare specअगरiers */
			match = 1;
			क्रम (i = 0; i < (addrsize + पूर्णांकsize); i++, imaplen--)
				match &= !((match_array[i] ^ *imap++) & imask[i]);

			pr_debug(" -> match=%d (imaplen=%d)\n", match, imaplen);

			/* Get the पूर्णांकerrupt parent */
			अगर (of_irq_workarounds & OF_IMAP_NO_PHANDLE)
				newpar = of_node_get(of_irq_dflt_pic);
			अन्यथा
				newpar = of_find_node_by_phandle(be32_to_cpup(imap));
			imap++;
			--imaplen;

			/* Check अगर not found */
			अगर (newpar == शून्य) अणु
				pr_debug(" -> imap parent not found !\n");
				जाओ fail;
			पूर्ण

			अगर (!of_device_is_available(newpar))
				match = 0;

			/* Get #पूर्णांकerrupt-cells and #address-cells of new
			 * parent
			 */
			अगर (of_property_पढ़ो_u32(newpar, "#interrupt-cells",
						 &newपूर्णांकsize)) अणु
				pr_debug(" -> parent lacks #interrupt-cells!\n");
				जाओ fail;
			पूर्ण
			अगर (of_property_पढ़ो_u32(newpar, "#address-cells",
						 &newaddrsize))
				newaddrsize = 0;

			pr_debug(" -> newintsize=%d, newaddrsize=%d\n",
			    newपूर्णांकsize, newaddrsize);

			/* Check क्रम malक्रमmed properties */
			अगर (WARN_ON(newaddrsize + newपूर्णांकsize > MAX_PHANDLE_ARGS)
			    || (imaplen < (newaddrsize + newपूर्णांकsize))) अणु
				rc = -EFAULT;
				जाओ fail;
			पूर्ण

			imap += newaddrsize + newपूर्णांकsize;
			imaplen -= newaddrsize + newपूर्णांकsize;

			pr_debug(" -> imaplen=%d\n", imaplen);
		पूर्ण
		अगर (!match)
			जाओ fail;

		/*
		 * Successfully parsed an पूर्णांकerrrupt-map translation; copy new
		 * पूर्णांकerrupt specअगरier पूर्णांकo the out_irq काष्ठाure
		 */
		match_array = imap - newaddrsize - newपूर्णांकsize;
		क्रम (i = 0; i < newपूर्णांकsize; i++)
			out_irq->args[i] = be32_to_cpup(imap - newपूर्णांकsize + i);
		out_irq->args_count = पूर्णांकsize = newपूर्णांकsize;
		addrsize = newaddrsize;

	skiplevel:
		/* Iterate again with new parent */
		out_irq->np = newpar;
		pr_debug(" -> new parent: %pOF\n", newpar);
		of_node_put(ipar);
		ipar = newpar;
		newpar = शून्य;
	पूर्ण
	rc = -ENOENT; /* No पूर्णांकerrupt-map found */

 fail:
	of_node_put(ipar);
	of_node_put(newpar);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(of_irq_parse_raw);

/**
 * of_irq_parse_one - Resolve an पूर्णांकerrupt क्रम a device
 * @device: the device whose पूर्णांकerrupt is to be resolved
 * @index: index of the पूर्णांकerrupt to resolve
 * @out_irq: काष्ठाure of_phandle_args filled by this function
 *
 * This function resolves an पूर्णांकerrupt क्रम a node by walking the पूर्णांकerrupt tree,
 * finding which पूर्णांकerrupt controller node it is attached to, and वापसing the
 * पूर्णांकerrupt specअगरier that can be used to retrieve a Linux IRQ number.
 */
पूर्णांक of_irq_parse_one(काष्ठा device_node *device, पूर्णांक index, काष्ठा of_phandle_args *out_irq)
अणु
	काष्ठा device_node *p;
	स्थिर __be32 *addr;
	u32 पूर्णांकsize;
	पूर्णांक i, res;

	pr_debug("of_irq_parse_one: dev=%pOF, index=%d\n", device, index);

	/* OldWorld mac stuff is "special", handle out of line */
	अगर (of_irq_workarounds & OF_IMAP_OLDWORLD_MAC)
		वापस of_irq_parse_oldworld(device, index, out_irq);

	/* Get the reg property (अगर any) */
	addr = of_get_property(device, "reg", शून्य);

	/* Try the new-style पूर्णांकerrupts-extended first */
	res = of_parse_phandle_with_args(device, "interrupts-extended",
					"#interrupt-cells", index, out_irq);
	अगर (!res)
		वापस of_irq_parse_raw(addr, out_irq);

	/* Look क्रम the पूर्णांकerrupt parent. */
	p = of_irq_find_parent(device);
	अगर (p == शून्य)
		वापस -EINVAL;

	/* Get size of पूर्णांकerrupt specअगरier */
	अगर (of_property_पढ़ो_u32(p, "#interrupt-cells", &पूर्णांकsize)) अणु
		res = -EINVAL;
		जाओ out;
	पूर्ण

	pr_debug(" parent=%pOF, intsize=%d\n", p, पूर्णांकsize);

	/* Copy पूर्णांकspec पूर्णांकo irq काष्ठाure */
	out_irq->np = p;
	out_irq->args_count = पूर्णांकsize;
	क्रम (i = 0; i < पूर्णांकsize; i++) अणु
		res = of_property_पढ़ो_u32_index(device, "interrupts",
						 (index * पूर्णांकsize) + i,
						 out_irq->args + i);
		अगर (res)
			जाओ out;
	पूर्ण

	pr_debug(" intspec=%d\n", *out_irq->args);


	/* Check अगर there are any पूर्णांकerrupt-map translations to process */
	res = of_irq_parse_raw(addr, out_irq);
 out:
	of_node_put(p);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(of_irq_parse_one);

/**
 * of_irq_to_resource - Decode a node's IRQ and वापस it as a resource
 * @dev: poपूर्णांकer to device tree node
 * @index: zero-based index of the irq
 * @r: poपूर्णांकer to resource काष्ठाure to वापस result पूर्णांकo.
 */
पूर्णांक of_irq_to_resource(काष्ठा device_node *dev, पूर्णांक index, काष्ठा resource *r)
अणु
	पूर्णांक irq = of_irq_get(dev, index);

	अगर (irq < 0)
		वापस irq;

	/* Only dereference the resource अगर both the
	 * resource and the irq are valid. */
	अगर (r && irq) अणु
		स्थिर अक्षर *name = शून्य;

		स_रखो(r, 0, माप(*r));
		/*
		 * Get optional "interrupt-names" property to add a name
		 * to the resource.
		 */
		of_property_पढ़ो_string_index(dev, "interrupt-names", index,
					      &name);

		r->start = r->end = irq;
		r->flags = IORESOURCE_IRQ | irqd_get_trigger_type(irq_get_irq_data(irq));
		r->name = name ? name : of_node_full_name(dev);
	पूर्ण

	वापस irq;
पूर्ण
EXPORT_SYMBOL_GPL(of_irq_to_resource);

/**
 * of_irq_get - Decode a node's IRQ and वापस it as a Linux IRQ number
 * @dev: poपूर्णांकer to device tree node
 * @index: zero-based index of the IRQ
 *
 * Return: Linux IRQ number on success, or 0 on the IRQ mapping failure, or
 * -EPROBE_DEFER अगर the IRQ करोमुख्य is not yet created, or error code in हाल
 * of any other failure.
 */
पूर्णांक of_irq_get(काष्ठा device_node *dev, पूर्णांक index)
अणु
	पूर्णांक rc;
	काष्ठा of_phandle_args oirq;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	rc = of_irq_parse_one(dev, index, &oirq);
	अगर (rc)
		वापस rc;

	करोमुख्य = irq_find_host(oirq.np);
	अगर (!करोमुख्य)
		वापस -EPROBE_DEFER;

	वापस irq_create_of_mapping(&oirq);
पूर्ण
EXPORT_SYMBOL_GPL(of_irq_get);

/**
 * of_irq_get_byname - Decode a node's IRQ and वापस it as a Linux IRQ number
 * @dev: poपूर्णांकer to device tree node
 * @name: IRQ name
 *
 * Return: Linux IRQ number on success, or 0 on the IRQ mapping failure, or
 * -EPROBE_DEFER अगर the IRQ करोमुख्य is not yet created, or error code in हाल
 * of any other failure.
 */
पूर्णांक of_irq_get_byname(काष्ठा device_node *dev, स्थिर अक्षर *name)
अणु
	पूर्णांक index;

	अगर (unlikely(!name))
		वापस -EINVAL;

	index = of_property_match_string(dev, "interrupt-names", name);
	अगर (index < 0)
		वापस index;

	वापस of_irq_get(dev, index);
पूर्ण
EXPORT_SYMBOL_GPL(of_irq_get_byname);

/**
 * of_irq_count - Count the number of IRQs a node uses
 * @dev: poपूर्णांकer to device tree node
 */
पूर्णांक of_irq_count(काष्ठा device_node *dev)
अणु
	काष्ठा of_phandle_args irq;
	पूर्णांक nr = 0;

	जबतक (of_irq_parse_one(dev, nr, &irq) == 0)
		nr++;

	वापस nr;
पूर्ण

/**
 * of_irq_to_resource_table - Fill in resource table with node's IRQ info
 * @dev: poपूर्णांकer to device tree node
 * @res: array of resources to fill in
 * @nr_irqs: the number of IRQs (and upper bound क्रम num of @res elements)
 *
 * Return: The size of the filled in table (up to @nr_irqs).
 */
पूर्णांक of_irq_to_resource_table(काष्ठा device_node *dev, काष्ठा resource *res,
		पूर्णांक nr_irqs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++, res++)
		अगर (of_irq_to_resource(dev, i, res) <= 0)
			अवरोध;

	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(of_irq_to_resource_table);

काष्ठा of_पूर्णांकc_desc अणु
	काष्ठा list_head	list;
	of_irq_init_cb_t	irq_init_cb;
	काष्ठा device_node	*dev;
	काष्ठा device_node	*पूर्णांकerrupt_parent;
पूर्ण;

/**
 * of_irq_init - Scan and init matching पूर्णांकerrupt controllers in DT
 * @matches: 0 terminated array of nodes to match and init function to call
 *
 * This function scans the device tree क्रम matching पूर्णांकerrupt controller nodes,
 * and calls their initialization functions in order with parents first.
 */
व्योम __init of_irq_init(स्थिर काष्ठा of_device_id *matches)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np, *parent = शून्य;
	काष्ठा of_पूर्णांकc_desc *desc, *temp_desc;
	काष्ठा list_head पूर्णांकc_desc_list, पूर्णांकc_parent_list;

	INIT_LIST_HEAD(&पूर्णांकc_desc_list);
	INIT_LIST_HEAD(&पूर्णांकc_parent_list);

	क्रम_each_matching_node_and_match(np, matches, &match) अणु
		अगर (!of_property_पढ़ो_bool(np, "interrupt-controller") ||
				!of_device_is_available(np))
			जारी;

		अगर (WARN(!match->data, "of_irq_init: no init function for %s\n",
			 match->compatible))
			जारी;

		/*
		 * Here, we allocate and populate an of_पूर्णांकc_desc with the node
		 * poपूर्णांकer, पूर्णांकerrupt-parent device_node etc.
		 */
		desc = kzalloc(माप(*desc), GFP_KERNEL);
		अगर (!desc) अणु
			of_node_put(np);
			जाओ err;
		पूर्ण

		desc->irq_init_cb = match->data;
		desc->dev = of_node_get(np);
		desc->पूर्णांकerrupt_parent = of_irq_find_parent(np);
		अगर (desc->पूर्णांकerrupt_parent == np)
			desc->पूर्णांकerrupt_parent = शून्य;
		list_add_tail(&desc->list, &पूर्णांकc_desc_list);
	पूर्ण

	/*
	 * The root irq controller is the one without an पूर्णांकerrupt-parent.
	 * That one goes first, followed by the controllers that reference it,
	 * followed by the ones that reference the 2nd level controllers, etc.
	 */
	जबतक (!list_empty(&पूर्णांकc_desc_list)) अणु
		/*
		 * Process all controllers with the current 'parent'.
		 * First pass will be looking क्रम शून्य as the parent.
		 * The assumption is that शून्य parent means a root controller.
		 */
		list_क्रम_each_entry_safe(desc, temp_desc, &पूर्णांकc_desc_list, list) अणु
			पूर्णांक ret;

			अगर (desc->पूर्णांकerrupt_parent != parent)
				जारी;

			list_del(&desc->list);

			of_node_set_flag(desc->dev, OF_POPULATED);

			pr_debug("of_irq_init: init %pOF (%p), parent %p\n",
				 desc->dev,
				 desc->dev, desc->पूर्णांकerrupt_parent);
			ret = desc->irq_init_cb(desc->dev,
						desc->पूर्णांकerrupt_parent);
			अगर (ret) अणु
				of_node_clear_flag(desc->dev, OF_POPULATED);
				kमुक्त(desc);
				जारी;
			पूर्ण

			/*
			 * This one is now set up; add it to the parent list so
			 * its children can get processed in a subsequent pass.
			 */
			list_add_tail(&desc->list, &पूर्णांकc_parent_list);
		पूर्ण

		/* Get the next pending parent that might have children */
		desc = list_first_entry_or_null(&पूर्णांकc_parent_list,
						typeof(*desc), list);
		अगर (!desc) अणु
			pr_err("of_irq_init: children remain, but no parents\n");
			अवरोध;
		पूर्ण
		list_del(&desc->list);
		parent = desc->dev;
		kमुक्त(desc);
	पूर्ण

	list_क्रम_each_entry_safe(desc, temp_desc, &पूर्णांकc_parent_list, list) अणु
		list_del(&desc->list);
		kमुक्त(desc);
	पूर्ण
err:
	list_क्रम_each_entry_safe(desc, temp_desc, &पूर्णांकc_desc_list, list) अणु
		list_del(&desc->list);
		of_node_put(desc->dev);
		kमुक्त(desc);
	पूर्ण
पूर्ण

अटल u32 __of_msi_map_id(काष्ठा device *dev, काष्ठा device_node **np,
			    u32 id_in)
अणु
	काष्ठा device *parent_dev;
	u32 id_out = id_in;

	/*
	 * Walk up the device parent links looking क्रम one with a
	 * "msi-map" property.
	 */
	क्रम (parent_dev = dev; parent_dev; parent_dev = parent_dev->parent)
		अगर (!of_map_id(parent_dev->of_node, id_in, "msi-map",
				"msi-map-mask", np, &id_out))
			अवरोध;
	वापस id_out;
पूर्ण

/**
 * of_msi_map_id - Map a MSI ID क्रम a device.
 * @dev: device क्रम which the mapping is to be करोne.
 * @msi_np: device node of the expected msi controller.
 * @id_in: unmapped MSI ID क्रम the device.
 *
 * Walk up the device hierarchy looking क्रम devices with a "msi-map"
 * property.  If found, apply the mapping to @id_in.
 *
 * Return: The mapped MSI ID.
 */
u32 of_msi_map_id(काष्ठा device *dev, काष्ठा device_node *msi_np, u32 id_in)
अणु
	वापस __of_msi_map_id(dev, &msi_np, id_in);
पूर्ण

/**
 * of_msi_map_get_device_करोमुख्य - Use msi-map to find the relevant MSI करोमुख्य
 * @dev: device क्रम which the mapping is to be करोne.
 * @id: Device ID.
 * @bus_token: Bus token
 *
 * Walk up the device hierarchy looking क्रम devices with a "msi-map"
 * property.
 *
 * Returns: the MSI करोमुख्य क्रम this device (or शून्य on failure)
 */
काष्ठा irq_करोमुख्य *of_msi_map_get_device_करोमुख्य(काष्ठा device *dev, u32 id,
						u32 bus_token)
अणु
	काष्ठा device_node *np = शून्य;

	__of_msi_map_id(dev, &np, id);
	वापस irq_find_matching_host(np, bus_token);
पूर्ण

/**
 * of_msi_get_करोमुख्य - Use msi-parent to find the relevant MSI करोमुख्य
 * @dev: device क्रम which the करोमुख्य is requested
 * @np: device node क्रम @dev
 * @token: bus type क्रम this करोमुख्य
 *
 * Parse the msi-parent property (both the simple and the complex
 * versions), and वापसs the corresponding MSI करोमुख्य.
 *
 * Returns: the MSI करोमुख्य क्रम this device (or शून्य on failure).
 */
काष्ठा irq_करोमुख्य *of_msi_get_करोमुख्य(काष्ठा device *dev,
				     काष्ठा device_node *np,
				     क्रमागत irq_करोमुख्य_bus_token token)
अणु
	काष्ठा device_node *msi_np;
	काष्ठा irq_करोमुख्य *d;

	/* Check क्रम a single msi-parent property */
	msi_np = of_parse_phandle(np, "msi-parent", 0);
	अगर (msi_np && !of_property_पढ़ो_bool(msi_np, "#msi-cells")) अणु
		d = irq_find_matching_host(msi_np, token);
		अगर (!d)
			of_node_put(msi_np);
		वापस d;
	पूर्ण

	अगर (token == DOMAIN_BUS_PLATFORM_MSI) अणु
		/* Check क्रम the complex msi-parent version */
		काष्ठा of_phandle_args args;
		पूर्णांक index = 0;

		जबतक (!of_parse_phandle_with_args(np, "msi-parent",
						   "#msi-cells",
						   index, &args)) अणु
			d = irq_find_matching_host(args.np, token);
			अगर (d)
				वापस d;

			of_node_put(args.np);
			index++;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * of_msi_configure - Set the msi_करोमुख्य field of a device
 * @dev: device काष्ठाure to associate with an MSI irq करोमुख्य
 * @np: device node क्रम that device
 */
व्योम of_msi_configure(काष्ठा device *dev, काष्ठा device_node *np)
अणु
	dev_set_msi_करोमुख्य(dev,
			   of_msi_get_करोमुख्य(dev, np, DOMAIN_BUS_PLATFORM_MSI));
पूर्ण
EXPORT_SYMBOL_GPL(of_msi_configure);
