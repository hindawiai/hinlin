<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा pr_fmt(fmt)  "irq: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/topology.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/fs.h>

अटल LIST_HEAD(irq_करोमुख्य_list);
अटल DEFINE_MUTEX(irq_करोमुख्य_mutex);

अटल काष्ठा irq_करोमुख्य *irq_शेष_करोमुख्य;

अटल व्योम irq_करोमुख्य_check_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य);

काष्ठा irqchip_fwid अणु
	काष्ठा fwnode_handle	fwnode;
	अचिन्हित पूर्णांक		type;
	अक्षर			*name;
	phys_addr_t		*pa;
पूर्ण;

#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
अटल व्योम debugfs_add_करोमुख्य_dir(काष्ठा irq_करोमुख्य *d);
अटल व्योम debugfs_हटाओ_करोमुख्य_dir(काष्ठा irq_करोमुख्य *d);
#अन्यथा
अटल अंतरभूत व्योम debugfs_add_करोमुख्य_dir(काष्ठा irq_करोमुख्य *d) अणु पूर्ण
अटल अंतरभूत व्योम debugfs_हटाओ_करोमुख्य_dir(काष्ठा irq_करोमुख्य *d) अणु पूर्ण
#पूर्ण_अगर

अटल स्थिर अक्षर *irqchip_fwnode_get_name(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा irqchip_fwid *fwid = container_of(fwnode, काष्ठा irqchip_fwid, fwnode);

	वापस fwid->name;
पूर्ण

स्थिर काष्ठा fwnode_operations irqchip_fwnode_ops = अणु
	.get_name = irqchip_fwnode_get_name,
पूर्ण;
EXPORT_SYMBOL_GPL(irqchip_fwnode_ops);

/**
 * __irq_करोमुख्य_alloc_fwnode - Allocate a fwnode_handle suitable क्रम
 *                           identअगरying an irq करोमुख्य
 * @type:	Type of irqchip_fwnode. See linux/irqकरोमुख्य.h
 * @id:		Optional user provided id अगर name != शून्य
 * @name:	Optional user provided करोमुख्य name
 * @pa:		Optional user-provided physical address
 *
 * Allocate a काष्ठा irqchip_fwid, and वापस a poपूर्णांकer to the embedded
 * fwnode_handle (or शून्य on failure).
 *
 * Note: The types IRQCHIP_FWNODE_NAMED and IRQCHIP_FWNODE_NAMED_ID are
 * solely to transport name inक्रमmation to irqकरोमुख्य creation code. The
 * node is not stored. For other types the poपूर्णांकer is kept in the irq
 * करोमुख्य काष्ठा.
 */
काष्ठा fwnode_handle *__irq_करोमुख्य_alloc_fwnode(अचिन्हित पूर्णांक type, पूर्णांक id,
						स्थिर अक्षर *name,
						phys_addr_t *pa)
अणु
	काष्ठा irqchip_fwid *fwid;
	अक्षर *n;

	fwid = kzalloc(माप(*fwid), GFP_KERNEL);

	चयन (type) अणु
	हाल IRQCHIP_FWNODE_NAMED:
		n = kaप्र_लिखो(GFP_KERNEL, "%s", name);
		अवरोध;
	हाल IRQCHIP_FWNODE_NAMED_ID:
		n = kaप्र_लिखो(GFP_KERNEL, "%s-%d", name, id);
		अवरोध;
	शेष:
		n = kaप्र_लिखो(GFP_KERNEL, "irqchip@%pa", pa);
		अवरोध;
	पूर्ण

	अगर (!fwid || !n) अणु
		kमुक्त(fwid);
		kमुक्त(n);
		वापस शून्य;
	पूर्ण

	fwid->type = type;
	fwid->name = n;
	fwid->pa = pa;
	fwnode_init(&fwid->fwnode, &irqchip_fwnode_ops);
	वापस &fwid->fwnode;
पूर्ण
EXPORT_SYMBOL_GPL(__irq_करोमुख्य_alloc_fwnode);

/**
 * irq_करोमुख्य_मुक्त_fwnode - Free a non-OF-backed fwnode_handle
 *
 * Free a fwnode_handle allocated with irq_करोमुख्य_alloc_fwnode.
 */
व्योम irq_करोमुख्य_मुक्त_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा irqchip_fwid *fwid;

	अगर (WARN_ON(!is_fwnode_irqchip(fwnode)))
		वापस;

	fwid = container_of(fwnode, काष्ठा irqchip_fwid, fwnode);
	kमुक्त(fwid->name);
	kमुक्त(fwid);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_मुक्त_fwnode);

/**
 * __irq_करोमुख्य_add() - Allocate a new irq_करोमुख्य data काष्ठाure
 * @fwnode: firmware node क्रम the पूर्णांकerrupt controller
 * @size: Size of linear map; 0 क्रम radix mapping only
 * @hwirq_max: Maximum number of पूर्णांकerrupts supported by controller
 * @direct_max: Maximum value of direct maps; Use ~0 क्रम no limit; 0 क्रम no
 *              direct mapping
 * @ops: करोमुख्य callbacks
 * @host_data: Controller निजी data poपूर्णांकer
 *
 * Allocates and initializes an irq_करोमुख्य काष्ठाure.
 * Returns poपूर्णांकer to IRQ करोमुख्य, or शून्य on failure.
 */
काष्ठा irq_करोमुख्य *__irq_करोमुख्य_add(काष्ठा fwnode_handle *fwnode, पूर्णांक size,
				    irq_hw_number_t hwirq_max, पूर्णांक direct_max,
				    स्थिर काष्ठा irq_करोमुख्य_ops *ops,
				    व्योम *host_data)
अणु
	काष्ठा irqchip_fwid *fwid;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अटल atomic_t unknown_करोमुख्यs;

	करोमुख्य = kzalloc_node(माप(*करोमुख्य) + (माप(अचिन्हित पूर्णांक) * size),
			      GFP_KERNEL, of_node_to_nid(to_of_node(fwnode)));
	अगर (!करोमुख्य)
		वापस शून्य;

	अगर (is_fwnode_irqchip(fwnode)) अणु
		fwid = container_of(fwnode, काष्ठा irqchip_fwid, fwnode);

		चयन (fwid->type) अणु
		हाल IRQCHIP_FWNODE_NAMED:
		हाल IRQCHIP_FWNODE_NAMED_ID:
			करोमुख्य->fwnode = fwnode;
			करोमुख्य->name = kstrdup(fwid->name, GFP_KERNEL);
			अगर (!करोमुख्य->name) अणु
				kमुक्त(करोमुख्य);
				वापस शून्य;
			पूर्ण
			करोमुख्य->flags |= IRQ_DOMAIN_NAME_ALLOCATED;
			अवरोध;
		शेष:
			करोमुख्य->fwnode = fwnode;
			करोमुख्य->name = fwid->name;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (is_of_node(fwnode) || is_acpi_device_node(fwnode) ||
		   is_software_node(fwnode)) अणु
		अक्षर *name;

		/*
		 * fwnode paths contain '/', which debugfs is legitimately
		 * unhappy about. Replace them with ':', which करोes
		 * the trick and is not as offensive as '\'...
		 */
		name = kaप्र_लिखो(GFP_KERNEL, "%pfw", fwnode);
		अगर (!name) अणु
			kमुक्त(करोमुख्य);
			वापस शून्य;
		पूर्ण

		strreplace(name, '/', ':');

		करोमुख्य->name = name;
		करोमुख्य->fwnode = fwnode;
		करोमुख्य->flags |= IRQ_DOMAIN_NAME_ALLOCATED;
	पूर्ण

	अगर (!करोमुख्य->name) अणु
		अगर (fwnode)
			pr_err("Invalid fwnode type for irqdomain\n");
		करोमुख्य->name = kaप्र_लिखो(GFP_KERNEL, "unknown-%d",
					 atomic_inc_वापस(&unknown_करोमुख्यs));
		अगर (!करोमुख्य->name) अणु
			kमुक्त(करोमुख्य);
			वापस शून्य;
		पूर्ण
		करोमुख्य->flags |= IRQ_DOMAIN_NAME_ALLOCATED;
	पूर्ण

	fwnode_handle_get(fwnode);
	fwnode_dev_initialized(fwnode, true);

	/* Fill काष्ठाure */
	INIT_RADIX_TREE(&करोमुख्य->revmap_tree, GFP_KERNEL);
	mutex_init(&करोमुख्य->revmap_tree_mutex);
	करोमुख्य->ops = ops;
	करोमुख्य->host_data = host_data;
	करोमुख्य->hwirq_max = hwirq_max;
	करोमुख्य->revmap_size = size;
	करोमुख्य->revmap_direct_max_irq = direct_max;
	irq_करोमुख्य_check_hierarchy(करोमुख्य);

	mutex_lock(&irq_करोमुख्य_mutex);
	debugfs_add_करोमुख्य_dir(करोमुख्य);
	list_add(&करोमुख्य->link, &irq_करोमुख्य_list);
	mutex_unlock(&irq_करोमुख्य_mutex);

	pr_debug("Added domain %s\n", करोमुख्य->name);
	वापस करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(__irq_करोमुख्य_add);

/**
 * irq_करोमुख्य_हटाओ() - Remove an irq करोमुख्य.
 * @करोमुख्य: करोमुख्य to हटाओ
 *
 * This routine is used to हटाओ an irq करोमुख्य. The caller must ensure
 * that all mappings within the करोमुख्य have been disposed of prior to
 * use, depending on the revmap type.
 */
व्योम irq_करोमुख्य_हटाओ(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	mutex_lock(&irq_करोमुख्य_mutex);
	debugfs_हटाओ_करोमुख्य_dir(करोमुख्य);

	WARN_ON(!radix_tree_empty(&करोमुख्य->revmap_tree));

	list_del(&करोमुख्य->link);

	/*
	 * If the going away करोमुख्य is the शेष one, reset it.
	 */
	अगर (unlikely(irq_शेष_करोमुख्य == करोमुख्य))
		irq_set_शेष_host(शून्य);

	mutex_unlock(&irq_करोमुख्य_mutex);

	pr_debug("Removed domain %s\n", करोमुख्य->name);

	fwnode_dev_initialized(करोमुख्य->fwnode, false);
	fwnode_handle_put(करोमुख्य->fwnode);
	अगर (करोमुख्य->flags & IRQ_DOMAIN_NAME_ALLOCATED)
		kमुक्त(करोमुख्य->name);
	kमुक्त(करोमुख्य);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_हटाओ);

व्योम irq_करोमुख्य_update_bus_token(काष्ठा irq_करोमुख्य *करोमुख्य,
				 क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	अक्षर *name;

	अगर (करोमुख्य->bus_token == bus_token)
		वापस;

	mutex_lock(&irq_करोमुख्य_mutex);

	करोमुख्य->bus_token = bus_token;

	name = kaप्र_लिखो(GFP_KERNEL, "%s-%d", करोमुख्य->name, bus_token);
	अगर (!name) अणु
		mutex_unlock(&irq_करोमुख्य_mutex);
		वापस;
	पूर्ण

	debugfs_हटाओ_करोमुख्य_dir(करोमुख्य);

	अगर (करोमुख्य->flags & IRQ_DOMAIN_NAME_ALLOCATED)
		kमुक्त(करोमुख्य->name);
	अन्यथा
		करोमुख्य->flags |= IRQ_DOMAIN_NAME_ALLOCATED;

	करोमुख्य->name = name;
	debugfs_add_करोमुख्य_dir(करोमुख्य);

	mutex_unlock(&irq_करोमुख्य_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_update_bus_token);

/**
 * irq_करोमुख्य_create_simple() - Register an irq_करोमुख्य and optionally map a range of irqs
 * @fwnode: firmware node क्रम the पूर्णांकerrupt controller
 * @size: total number of irqs in mapping
 * @first_irq: first number of irq block asचिन्हित to the करोमुख्य,
 *	pass zero to assign irqs on-the-fly. If first_irq is non-zero, then
 *	pre-map all of the irqs in the करोमुख्य to virqs starting at first_irq.
 * @ops: करोमुख्य callbacks
 * @host_data: Controller निजी data poपूर्णांकer
 *
 * Allocates an irq_करोमुख्य, and optionally अगर first_irq is positive then also
 * allocate irq_descs and map all of the hwirqs to virqs starting at first_irq.
 *
 * This is पूर्णांकended to implement the expected behaviour क्रम most
 * पूर्णांकerrupt controllers. If device tree is used, then first_irq will be 0 and
 * irqs get mapped dynamically on the fly. However, अगर the controller requires
 * अटल virq assignments (non-DT boot) then it will set that up correctly.
 */
काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_simple(काष्ठा fwnode_handle *fwnode,
					    अचिन्हित पूर्णांक size,
					    अचिन्हित पूर्णांक first_irq,
					    स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					    व्योम *host_data)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	करोमुख्य = __irq_करोमुख्य_add(fwnode, size, size, 0, ops, host_data);
	अगर (!करोमुख्य)
		वापस शून्य;

	अगर (first_irq > 0) अणु
		अगर (IS_ENABLED(CONFIG_SPARSE_IRQ)) अणु
			/* attempt to allocated irq_descs */
			पूर्णांक rc = irq_alloc_descs(first_irq, first_irq, size,
						 of_node_to_nid(to_of_node(fwnode)));
			अगर (rc < 0)
				pr_info("Cannot allocate irq_descs @ IRQ%d, assuming pre-allocated\n",
					first_irq);
		पूर्ण
		irq_करोमुख्य_associate_many(करोमुख्य, first_irq, 0, size);
	पूर्ण

	वापस करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_create_simple);

/**
 * irq_करोमुख्य_add_legacy() - Allocate and रेजिस्टर a legacy revmap irq_करोमुख्य.
 * @of_node: poपूर्णांकer to पूर्णांकerrupt controller's device tree node.
 * @size: total number of irqs in legacy mapping
 * @first_irq: first number of irq block asचिन्हित to the करोमुख्य
 * @first_hwirq: first hwirq number to use क्रम the translation. Should normally
 *               be '0', but a positive पूर्णांकeger can be used अगर the effective
 *               hwirqs numbering करोes not begin at zero.
 * @ops: map/unmap करोमुख्य callbacks
 * @host_data: Controller निजी data poपूर्णांकer
 *
 * Note: the map() callback will be called beक्रमe this function वापसs
 * क्रम all legacy पूर्णांकerrupts except 0 (which is always the invalid irq क्रम
 * a legacy controller).
 */
काष्ठा irq_करोमुख्य *irq_करोमुख्य_add_legacy(काष्ठा device_node *of_node,
					 अचिन्हित पूर्णांक size,
					 अचिन्हित पूर्णांक first_irq,
					 irq_hw_number_t first_hwirq,
					 स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					 व्योम *host_data)
अणु
	वापस irq_करोमुख्य_create_legacy(of_node_to_fwnode(of_node), size,
					first_irq, first_hwirq, ops, host_data);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_add_legacy);

काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_legacy(काष्ठा fwnode_handle *fwnode,
					 अचिन्हित पूर्णांक size,
					 अचिन्हित पूर्णांक first_irq,
					 irq_hw_number_t first_hwirq,
					 स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					 व्योम *host_data)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	करोमुख्य = __irq_करोमुख्य_add(fwnode, first_hwirq + size, first_hwirq + size, 0, ops, host_data);
	अगर (करोमुख्य)
		irq_करोमुख्य_associate_many(करोमुख्य, first_irq, first_hwirq, size);

	वापस करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_create_legacy);

/**
 * irq_find_matching_fwspec() - Locates a करोमुख्य क्रम a given fwspec
 * @fwspec: FW specअगरier क्रम an पूर्णांकerrupt
 * @bus_token: करोमुख्य-specअगरic data
 */
काष्ठा irq_करोमुख्य *irq_find_matching_fwspec(काष्ठा irq_fwspec *fwspec,
					    क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	काष्ठा irq_करोमुख्य *h, *found = शून्य;
	काष्ठा fwnode_handle *fwnode = fwspec->fwnode;
	पूर्णांक rc;

	/* We might want to match the legacy controller last since
	 * it might potentially be set to match all पूर्णांकerrupts in
	 * the असलence of a device node. This isn't a problem so far
	 * yet though...
	 *
	 * bus_token == DOMAIN_BUS_ANY matches any करोमुख्य, any other
	 * values must generate an exact match क्रम the करोमुख्य to be
	 * selected.
	 */
	mutex_lock(&irq_करोमुख्य_mutex);
	list_क्रम_each_entry(h, &irq_करोमुख्य_list, link) अणु
		अगर (h->ops->select && fwspec->param_count)
			rc = h->ops->select(h, fwspec, bus_token);
		अन्यथा अगर (h->ops->match)
			rc = h->ops->match(h, to_of_node(fwnode), bus_token);
		अन्यथा
			rc = ((fwnode != शून्य) && (h->fwnode == fwnode) &&
			      ((bus_token == DOMAIN_BUS_ANY) ||
			       (h->bus_token == bus_token)));

		अगर (rc) अणु
			found = h;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&irq_करोमुख्य_mutex);
	वापस found;
पूर्ण
EXPORT_SYMBOL_GPL(irq_find_matching_fwspec);

/**
 * irq_करोमुख्य_check_msi_remap - Check whether all MSI irq करोमुख्यs implement
 * IRQ remapping
 *
 * Return: false अगर any MSI irq करोमुख्य करोes not support IRQ remapping,
 * true otherwise (including अगर there is no MSI irq करोमुख्य)
 */
bool irq_करोमुख्य_check_msi_remap(व्योम)
अणु
	काष्ठा irq_करोमुख्य *h;
	bool ret = true;

	mutex_lock(&irq_करोमुख्य_mutex);
	list_क्रम_each_entry(h, &irq_करोमुख्य_list, link) अणु
		अगर (irq_करोमुख्य_is_msi(h) &&
		    !irq_करोमुख्य_hierarchical_is_msi_remap(h)) अणु
			ret = false;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&irq_करोमुख्य_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_check_msi_remap);

/**
 * irq_set_शेष_host() - Set a "default" irq करोमुख्य
 * @करोमुख्य: शेष करोमुख्य poपूर्णांकer
 *
 * For convenience, it's possible to set a "default" करोमुख्य that will be used
 * whenever शून्य is passed to irq_create_mapping(). It makes lअगरe easier क्रम
 * platक्रमms that want to manipulate a few hard coded पूर्णांकerrupt numbers that
 * aren't properly represented in the device-tree.
 */
व्योम irq_set_शेष_host(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	pr_debug("Default domain set to @0x%p\n", करोमुख्य);

	irq_शेष_करोमुख्य = करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(irq_set_शेष_host);

/**
 * irq_get_शेष_host() - Retrieve the "default" irq करोमुख्य
 *
 * Returns: the शेष करोमुख्य, अगर any.
 *
 * Modern code should never use this. This should only be used on
 * प्रणालीs that cannot implement a firmware->fwnode mapping (which
 * both DT and ACPI provide).
 */
काष्ठा irq_करोमुख्य *irq_get_शेष_host(व्योम)
अणु
	वापस irq_शेष_करोमुख्य;
पूर्ण

अटल व्योम irq_करोमुख्य_clear_mapping(काष्ठा irq_करोमुख्य *करोमुख्य,
				     irq_hw_number_t hwirq)
अणु
	अगर (hwirq < करोमुख्य->revmap_size) अणु
		करोमुख्य->linear_revmap[hwirq] = 0;
	पूर्ण अन्यथा अणु
		mutex_lock(&करोमुख्य->revmap_tree_mutex);
		radix_tree_delete(&करोमुख्य->revmap_tree, hwirq);
		mutex_unlock(&करोमुख्य->revmap_tree_mutex);
	पूर्ण
पूर्ण

अटल व्योम irq_करोमुख्य_set_mapping(काष्ठा irq_करोमुख्य *करोमुख्य,
				   irq_hw_number_t hwirq,
				   काष्ठा irq_data *irq_data)
अणु
	अगर (hwirq < करोमुख्य->revmap_size) अणु
		करोमुख्य->linear_revmap[hwirq] = irq_data->irq;
	पूर्ण अन्यथा अणु
		mutex_lock(&करोमुख्य->revmap_tree_mutex);
		radix_tree_insert(&करोमुख्य->revmap_tree, hwirq, irq_data);
		mutex_unlock(&करोमुख्य->revmap_tree_mutex);
	पूर्ण
पूर्ण

अटल व्योम irq_करोमुख्य_disassociate(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_data *irq_data = irq_get_irq_data(irq);
	irq_hw_number_t hwirq;

	अगर (WARN(!irq_data || irq_data->करोमुख्य != करोमुख्य,
		 "virq%i doesn't exist; cannot disassociate\n", irq))
		वापस;

	hwirq = irq_data->hwirq;
	irq_set_status_flags(irq, IRQ_NOREQUEST);

	/* हटाओ chip and handler */
	irq_set_chip_and_handler(irq, शून्य, शून्य);

	/* Make sure it's completed */
	synchronize_irq(irq);

	/* Tell the PIC about it */
	अगर (करोमुख्य->ops->unmap)
		करोमुख्य->ops->unmap(करोमुख्य, irq);
	smp_mb();

	irq_data->करोमुख्य = शून्य;
	irq_data->hwirq = 0;
	करोमुख्य->mapcount--;

	/* Clear reverse map क्रम this hwirq */
	irq_करोमुख्य_clear_mapping(करोमुख्य, hwirq);
पूर्ण

पूर्णांक irq_करोमुख्य_associate(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hwirq)
अणु
	काष्ठा irq_data *irq_data = irq_get_irq_data(virq);
	पूर्णांक ret;

	अगर (WARN(hwirq >= करोमुख्य->hwirq_max,
		 "error: hwirq 0x%x is too large for %s\n", (पूर्णांक)hwirq, करोमुख्य->name))
		वापस -EINVAL;
	अगर (WARN(!irq_data, "error: virq%i is not allocated", virq))
		वापस -EINVAL;
	अगर (WARN(irq_data->करोमुख्य, "error: virq%i is already associated", virq))
		वापस -EINVAL;

	mutex_lock(&irq_करोमुख्य_mutex);
	irq_data->hwirq = hwirq;
	irq_data->करोमुख्य = करोमुख्य;
	अगर (करोमुख्य->ops->map) अणु
		ret = करोमुख्य->ops->map(करोमुख्य, virq, hwirq);
		अगर (ret != 0) अणु
			/*
			 * If map() वापसs -EPERM, this पूर्णांकerrupt is रक्षित
			 * by the firmware or some other service and shall not
			 * be mapped. Don't bother telling the user about it.
			 */
			अगर (ret != -EPERM) अणु
				pr_info("%s didn't like hwirq-0x%lx to VIRQ%i mapping (rc=%d)\n",
				       करोमुख्य->name, hwirq, virq, ret);
			पूर्ण
			irq_data->करोमुख्य = शून्य;
			irq_data->hwirq = 0;
			mutex_unlock(&irq_करोमुख्य_mutex);
			वापस ret;
		पूर्ण

		/* If not alपढ़ोy asचिन्हित, give the करोमुख्य the chip's name */
		अगर (!करोमुख्य->name && irq_data->chip)
			करोमुख्य->name = irq_data->chip->name;
	पूर्ण

	करोमुख्य->mapcount++;
	irq_करोमुख्य_set_mapping(करोमुख्य, hwirq, irq_data);
	mutex_unlock(&irq_करोमुख्य_mutex);

	irq_clear_status_flags(virq, IRQ_NOREQUEST);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_associate);

व्योम irq_करोमुख्य_associate_many(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq_base,
			       irq_hw_number_t hwirq_base, पूर्णांक count)
अणु
	काष्ठा device_node *of_node;
	पूर्णांक i;

	of_node = irq_करोमुख्य_get_of_node(करोमुख्य);
	pr_debug("%s(%s, irqbase=%i, hwbase=%i, count=%i)\n", __func__,
		of_node_full_name(of_node), irq_base, (पूर्णांक)hwirq_base, count);

	क्रम (i = 0; i < count; i++) अणु
		irq_करोमुख्य_associate(करोमुख्य, irq_base + i, hwirq_base + i);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_associate_many);

/**
 * irq_create_direct_mapping() - Allocate an irq क्रम direct mapping
 * @करोमुख्य: करोमुख्य to allocate the irq क्रम or शून्य क्रम शेष करोमुख्य
 *
 * This routine is used क्रम irq controllers which can choose the hardware
 * पूर्णांकerrupt numbers they generate. In such a हाल it's simplest to use
 * the linux irq as the hardware पूर्णांकerrupt number. It still uses the linear
 * or radix tree to store the mapping, but the irq controller can optimize
 * the revmap path by using the hwirq directly.
 */
अचिन्हित पूर्णांक irq_create_direct_mapping(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा device_node *of_node;
	अचिन्हित पूर्णांक virq;

	अगर (करोमुख्य == शून्य)
		करोमुख्य = irq_शेष_करोमुख्य;

	of_node = irq_करोमुख्य_get_of_node(करोमुख्य);
	virq = irq_alloc_desc_from(1, of_node_to_nid(of_node));
	अगर (!virq) अणु
		pr_debug("create_direct virq allocation failed\n");
		वापस 0;
	पूर्ण
	अगर (virq >= करोमुख्य->revmap_direct_max_irq) अणु
		pr_err("ERROR: no free irqs available below %i maximum\n",
			करोमुख्य->revmap_direct_max_irq);
		irq_मुक्त_desc(virq);
		वापस 0;
	पूर्ण
	pr_debug("create_direct obtained virq %d\n", virq);

	अगर (irq_करोमुख्य_associate(करोमुख्य, virq, virq)) अणु
		irq_मुक्त_desc(virq);
		वापस 0;
	पूर्ण

	वापस virq;
पूर्ण
EXPORT_SYMBOL_GPL(irq_create_direct_mapping);

/**
 * irq_create_mapping_affinity() - Map a hardware पूर्णांकerrupt पूर्णांकo linux irq space
 * @करोमुख्य: करोमुख्य owning this hardware पूर्णांकerrupt or शून्य क्रम शेष करोमुख्य
 * @hwirq: hardware irq number in that करोमुख्य space
 * @affinity: irq affinity
 *
 * Only one mapping per hardware पूर्णांकerrupt is permitted. Returns a linux
 * irq number.
 * If the sense/trigger is to be specअगरied, set_irq_type() should be called
 * on the number वापसed from that call.
 */
अचिन्हित पूर्णांक irq_create_mapping_affinity(काष्ठा irq_करोमुख्य *करोमुख्य,
				       irq_hw_number_t hwirq,
				       स्थिर काष्ठा irq_affinity_desc *affinity)
अणु
	काष्ठा device_node *of_node;
	पूर्णांक virq;

	pr_debug("irq_create_mapping(0x%p, 0x%lx)\n", करोमुख्य, hwirq);

	/* Look क्रम शेष करोमुख्य अगर necessary */
	अगर (करोमुख्य == शून्य)
		करोमुख्य = irq_शेष_करोमुख्य;
	अगर (करोमुख्य == शून्य) अणु
		WARN(1, "%s(, %lx) called with NULL domain\n", __func__, hwirq);
		वापस 0;
	पूर्ण
	pr_debug("-> using domain @%p\n", करोमुख्य);

	of_node = irq_करोमुख्य_get_of_node(करोमुख्य);

	/* Check अगर mapping alपढ़ोy exists */
	virq = irq_find_mapping(करोमुख्य, hwirq);
	अगर (virq) अणु
		pr_debug("-> existing mapping on virq %d\n", virq);
		वापस virq;
	पूर्ण

	/* Allocate a भव पूर्णांकerrupt number */
	virq = irq_करोमुख्य_alloc_descs(-1, 1, hwirq, of_node_to_nid(of_node),
				      affinity);
	अगर (virq <= 0) अणु
		pr_debug("-> virq allocation failed\n");
		वापस 0;
	पूर्ण

	अगर (irq_करोमुख्य_associate(करोमुख्य, virq, hwirq)) अणु
		irq_मुक्त_desc(virq);
		वापस 0;
	पूर्ण

	pr_debug("irq %lu on domain %s mapped to virtual irq %u\n",
		hwirq, of_node_full_name(of_node), virq);

	वापस virq;
पूर्ण
EXPORT_SYMBOL_GPL(irq_create_mapping_affinity);

अटल पूर्णांक irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				काष्ठा irq_fwspec *fwspec,
				irq_hw_number_t *hwirq, अचिन्हित पूर्णांक *type)
अणु
#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
	अगर (d->ops->translate)
		वापस d->ops->translate(d, fwspec, hwirq, type);
#पूर्ण_अगर
	अगर (d->ops->xlate)
		वापस d->ops->xlate(d, to_of_node(fwspec->fwnode),
				     fwspec->param, fwspec->param_count,
				     hwirq, type);

	/* If करोमुख्य has no translation, then we assume पूर्णांकerrupt line */
	*hwirq = fwspec->param[0];
	वापस 0;
पूर्ण

अटल व्योम of_phandle_args_to_fwspec(काष्ठा device_node *np, स्थिर u32 *args,
				      अचिन्हित पूर्णांक count,
				      काष्ठा irq_fwspec *fwspec)
अणु
	पूर्णांक i;

	fwspec->fwnode = of_node_to_fwnode(np);
	fwspec->param_count = count;

	क्रम (i = 0; i < count; i++)
		fwspec->param[i] = args[i];
पूर्ण

अचिन्हित पूर्णांक irq_create_fwspec_mapping(काष्ठा irq_fwspec *fwspec)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_data *irq_data;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type = IRQ_TYPE_NONE;
	पूर्णांक virq;

	अगर (fwspec->fwnode) अणु
		करोमुख्य = irq_find_matching_fwspec(fwspec, DOMAIN_BUS_WIRED);
		अगर (!करोमुख्य)
			करोमुख्य = irq_find_matching_fwspec(fwspec, DOMAIN_BUS_ANY);
	पूर्ण अन्यथा अणु
		करोमुख्य = irq_शेष_करोमुख्य;
	पूर्ण

	अगर (!करोमुख्य) अणु
		pr_warn("no irq domain found for %s !\n",
			of_node_full_name(to_of_node(fwspec->fwnode)));
		वापस 0;
	पूर्ण

	अगर (irq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type))
		वापस 0;

	/*
	 * WARN अगर the irqchip वापसs a type with bits
	 * outside the sense mask set and clear these bits.
	 */
	अगर (WARN_ON(type & ~IRQ_TYPE_SENSE_MASK))
		type &= IRQ_TYPE_SENSE_MASK;

	/*
	 * If we've alपढ़ोy configured this पूर्णांकerrupt,
	 * करोn't करो it again, or hell will अवरोध loose.
	 */
	virq = irq_find_mapping(करोमुख्य, hwirq);
	अगर (virq) अणु
		/*
		 * If the trigger type is not specअगरied or matches the
		 * current trigger type then we are करोne so वापस the
		 * पूर्णांकerrupt number.
		 */
		अगर (type == IRQ_TYPE_NONE || type == irq_get_trigger_type(virq))
			वापस virq;

		/*
		 * If the trigger type has not been set yet, then set
		 * it now and वापस the पूर्णांकerrupt number.
		 */
		अगर (irq_get_trigger_type(virq) == IRQ_TYPE_NONE) अणु
			irq_data = irq_get_irq_data(virq);
			अगर (!irq_data)
				वापस 0;

			irqd_set_trigger_type(irq_data, type);
			वापस virq;
		पूर्ण

		pr_warn("type mismatch, failed to map hwirq-%lu for %s!\n",
			hwirq, of_node_full_name(to_of_node(fwspec->fwnode)));
		वापस 0;
	पूर्ण

	अगर (irq_करोमुख्य_is_hierarchy(करोमुख्य)) अणु
		virq = irq_करोमुख्य_alloc_irqs(करोमुख्य, 1, NUMA_NO_NODE, fwspec);
		अगर (virq <= 0)
			वापस 0;
	पूर्ण अन्यथा अणु
		/* Create mapping */
		virq = irq_create_mapping(करोमुख्य, hwirq);
		अगर (!virq)
			वापस virq;
	पूर्ण

	irq_data = irq_get_irq_data(virq);
	अगर (!irq_data) अणु
		अगर (irq_करोमुख्य_is_hierarchy(करोमुख्य))
			irq_करोमुख्य_मुक्त_irqs(virq, 1);
		अन्यथा
			irq_dispose_mapping(virq);
		वापस 0;
	पूर्ण

	/* Store trigger type */
	irqd_set_trigger_type(irq_data, type);

	वापस virq;
पूर्ण
EXPORT_SYMBOL_GPL(irq_create_fwspec_mapping);

अचिन्हित पूर्णांक irq_create_of_mapping(काष्ठा of_phandle_args *irq_data)
अणु
	काष्ठा irq_fwspec fwspec;

	of_phandle_args_to_fwspec(irq_data->np, irq_data->args,
				  irq_data->args_count, &fwspec);

	वापस irq_create_fwspec_mapping(&fwspec);
पूर्ण
EXPORT_SYMBOL_GPL(irq_create_of_mapping);

/**
 * irq_dispose_mapping() - Unmap an पूर्णांकerrupt
 * @virq: linux irq number of the पूर्णांकerrupt to unmap
 */
व्योम irq_dispose_mapping(अचिन्हित पूर्णांक virq)
अणु
	काष्ठा irq_data *irq_data = irq_get_irq_data(virq);
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (!virq || !irq_data)
		वापस;

	करोमुख्य = irq_data->करोमुख्य;
	अगर (WARN_ON(करोमुख्य == शून्य))
		वापस;

	अगर (irq_करोमुख्य_is_hierarchy(करोमुख्य)) अणु
		irq_करोमुख्य_मुक्त_irqs(virq, 1);
	पूर्ण अन्यथा अणु
		irq_करोमुख्य_disassociate(करोमुख्य, virq);
		irq_मुक्त_desc(virq);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(irq_dispose_mapping);

/**
 * irq_find_mapping() - Find a linux irq from a hw irq number.
 * @करोमुख्य: करोमुख्य owning this hardware पूर्णांकerrupt
 * @hwirq: hardware irq number in that करोमुख्य space
 */
अचिन्हित पूर्णांक irq_find_mapping(काष्ठा irq_करोमुख्य *करोमुख्य,
			      irq_hw_number_t hwirq)
अणु
	काष्ठा irq_data *data;

	/* Look क्रम शेष करोमुख्य अगर necessary */
	अगर (करोमुख्य == शून्य)
		करोमुख्य = irq_शेष_करोमुख्य;
	अगर (करोमुख्य == शून्य)
		वापस 0;

	अगर (hwirq < करोमुख्य->revmap_direct_max_irq) अणु
		data = irq_करोमुख्य_get_irq_data(करोमुख्य, hwirq);
		अगर (data && data->hwirq == hwirq)
			वापस hwirq;
	पूर्ण

	/* Check अगर the hwirq is in the linear revmap. */
	अगर (hwirq < करोमुख्य->revmap_size)
		वापस करोमुख्य->linear_revmap[hwirq];

	rcu_पढ़ो_lock();
	data = radix_tree_lookup(&करोमुख्य->revmap_tree, hwirq);
	rcu_पढ़ो_unlock();
	वापस data ? data->irq : 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_find_mapping);

/**
 * irq_करोमुख्य_xlate_onecell() - Generic xlate क्रम direct one cell bindings
 *
 * Device Tree IRQ specअगरier translation function which works with one cell
 * bindings where the cell value maps directly to the hwirq number.
 */
पूर्णांक irq_करोमुख्य_xlate_onecell(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
			     स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			     अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(पूर्णांकsize < 1))
		वापस -EINVAL;
	*out_hwirq = पूर्णांकspec[0];
	*out_type = IRQ_TYPE_NONE;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_xlate_onecell);

/**
 * irq_करोमुख्य_xlate_twocell() - Generic xlate क्रम direct two cell bindings
 *
 * Device Tree IRQ specअगरier translation function which works with two cell
 * bindings where the cell values map directly to the hwirq number
 * and linux irq flags.
 */
पूर्णांक irq_करोमुख्य_xlate_twocell(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
			स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा irq_fwspec fwspec;

	of_phandle_args_to_fwspec(ctrlr, पूर्णांकspec, पूर्णांकsize, &fwspec);
	वापस irq_करोमुख्य_translate_twocell(d, &fwspec, out_hwirq, out_type);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_xlate_twocell);

/**
 * irq_करोमुख्य_xlate_onetwocell() - Generic xlate क्रम one or two cell bindings
 *
 * Device Tree IRQ specअगरier translation function which works with either one
 * or two cell bindings where the cell values map directly to the hwirq number
 * and linux irq flags.
 *
 * Note: करोn't use this function unless your पूर्णांकerrupt controller explicitly
 * supports both one and two cell bindings.  For the majority of controllers
 * the _onecell() or _twocell() variants above should be used.
 */
पूर्णांक irq_करोमुख्य_xlate_onetwocell(काष्ठा irq_करोमुख्य *d,
				काष्ठा device_node *ctrlr,
				स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(पूर्णांकsize < 1))
		वापस -EINVAL;
	*out_hwirq = पूर्णांकspec[0];
	अगर (पूर्णांकsize > 1)
		*out_type = पूर्णांकspec[1] & IRQ_TYPE_SENSE_MASK;
	अन्यथा
		*out_type = IRQ_TYPE_NONE;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_xlate_onetwocell);

स्थिर काष्ठा irq_करोमुख्य_ops irq_करोमुख्य_simple_ops = अणु
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;
EXPORT_SYMBOL_GPL(irq_करोमुख्य_simple_ops);

/**
 * irq_करोमुख्य_translate_onecell() - Generic translate क्रम direct one cell
 * bindings
 */
पूर्णांक irq_करोमुख्य_translate_onecell(काष्ठा irq_करोमुख्य *d,
				 काष्ठा irq_fwspec *fwspec,
				 अचिन्हित दीर्घ *out_hwirq,
				 अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(fwspec->param_count < 1))
		वापस -EINVAL;
	*out_hwirq = fwspec->param[0];
	*out_type = IRQ_TYPE_NONE;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_translate_onecell);

/**
 * irq_करोमुख्य_translate_twocell() - Generic translate क्रम direct two cell
 * bindings
 *
 * Device Tree IRQ specअगरier translation function which works with two cell
 * bindings where the cell values map directly to the hwirq number
 * and linux irq flags.
 */
पूर्णांक irq_करोमुख्य_translate_twocell(काष्ठा irq_करोमुख्य *d,
				 काष्ठा irq_fwspec *fwspec,
				 अचिन्हित दीर्घ *out_hwirq,
				 अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(fwspec->param_count < 2))
		वापस -EINVAL;
	*out_hwirq = fwspec->param[0];
	*out_type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_translate_twocell);

पूर्णांक irq_करोमुख्य_alloc_descs(पूर्णांक virq, अचिन्हित पूर्णांक cnt, irq_hw_number_t hwirq,
			   पूर्णांक node, स्थिर काष्ठा irq_affinity_desc *affinity)
अणु
	अचिन्हित पूर्णांक hपूर्णांक;

	अगर (virq >= 0) अणु
		virq = __irq_alloc_descs(virq, virq, cnt, node, THIS_MODULE,
					 affinity);
	पूर्ण अन्यथा अणु
		hपूर्णांक = hwirq % nr_irqs;
		अगर (hपूर्णांक == 0)
			hपूर्णांक++;
		virq = __irq_alloc_descs(-1, hपूर्णांक, cnt, node, THIS_MODULE,
					 affinity);
		अगर (virq <= 0 && hपूर्णांक > 1) अणु
			virq = __irq_alloc_descs(-1, 1, cnt, node, THIS_MODULE,
						 affinity);
		पूर्ण
	पूर्ण

	वापस virq;
पूर्ण

/**
 * irq_करोमुख्य_reset_irq_data - Clear hwirq, chip and chip_data in @irq_data
 * @irq_data:	The poपूर्णांकer to irq_data
 */
व्योम irq_करोमुख्य_reset_irq_data(काष्ठा irq_data *irq_data)
अणु
	irq_data->hwirq = 0;
	irq_data->chip = &no_irq_chip;
	irq_data->chip_data = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_reset_irq_data);

#अगर_घोषित	CONFIG_IRQ_DOMAIN_HIERARCHY
/**
 * irq_करोमुख्य_create_hierarchy - Add a irqकरोमुख्य पूर्णांकo the hierarchy
 * @parent:	Parent irq करोमुख्य to associate with the new करोमुख्य
 * @flags:	Irq करोमुख्य flags associated to the करोमुख्य
 * @size:	Size of the करोमुख्य. See below
 * @fwnode:	Optional fwnode of the पूर्णांकerrupt controller
 * @ops:	Poपूर्णांकer to the पूर्णांकerrupt करोमुख्य callbacks
 * @host_data:	Controller निजी data poपूर्णांकer
 *
 * If @size is 0 a tree करोमुख्य is created, otherwise a linear करोमुख्य.
 *
 * If successful the parent is associated to the new करोमुख्य and the
 * करोमुख्य flags are set.
 * Returns poपूर्णांकer to IRQ करोमुख्य, or शून्य on failure.
 */
काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_hierarchy(काष्ठा irq_करोमुख्य *parent,
					    अचिन्हित पूर्णांक flags,
					    अचिन्हित पूर्णांक size,
					    काष्ठा fwnode_handle *fwnode,
					    स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					    व्योम *host_data)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (size)
		करोमुख्य = irq_करोमुख्य_create_linear(fwnode, size, ops, host_data);
	अन्यथा
		करोमुख्य = irq_करोमुख्य_create_tree(fwnode, ops, host_data);
	अगर (करोमुख्य) अणु
		करोमुख्य->parent = parent;
		करोमुख्य->flags |= flags;
	पूर्ण

	वापस करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_create_hierarchy);

अटल व्योम irq_करोमुख्य_insert_irq(पूर्णांक virq)
अणु
	काष्ठा irq_data *data;

	क्रम (data = irq_get_irq_data(virq); data; data = data->parent_data) अणु
		काष्ठा irq_करोमुख्य *करोमुख्य = data->करोमुख्य;

		करोमुख्य->mapcount++;
		irq_करोमुख्य_set_mapping(करोमुख्य, data->hwirq, data);

		/* If not alपढ़ोy asचिन्हित, give the करोमुख्य the chip's name */
		अगर (!करोमुख्य->name && data->chip)
			करोमुख्य->name = data->chip->name;
	पूर्ण

	irq_clear_status_flags(virq, IRQ_NOREQUEST);
पूर्ण

अटल व्योम irq_करोमुख्य_हटाओ_irq(पूर्णांक virq)
अणु
	काष्ठा irq_data *data;

	irq_set_status_flags(virq, IRQ_NOREQUEST);
	irq_set_chip_and_handler(virq, शून्य, शून्य);
	synchronize_irq(virq);
	smp_mb();

	क्रम (data = irq_get_irq_data(virq); data; data = data->parent_data) अणु
		काष्ठा irq_करोमुख्य *करोमुख्य = data->करोमुख्य;
		irq_hw_number_t hwirq = data->hwirq;

		करोमुख्य->mapcount--;
		irq_करोमुख्य_clear_mapping(करोमुख्य, hwirq);
	पूर्ण
पूर्ण

अटल काष्ठा irq_data *irq_करोमुख्य_insert_irq_data(काष्ठा irq_करोमुख्य *करोमुख्य,
						   काष्ठा irq_data *child)
अणु
	काष्ठा irq_data *irq_data;

	irq_data = kzalloc_node(माप(*irq_data), GFP_KERNEL,
				irq_data_get_node(child));
	अगर (irq_data) अणु
		child->parent_data = irq_data;
		irq_data->irq = child->irq;
		irq_data->common = child->common;
		irq_data->करोमुख्य = करोमुख्य;
	पूर्ण

	वापस irq_data;
पूर्ण

अटल व्योम __irq_करोमुख्य_मुक्त_hierarchy(काष्ठा irq_data *irq_data)
अणु
	काष्ठा irq_data *पंचांगp;

	जबतक (irq_data) अणु
		पंचांगp = irq_data;
		irq_data = irq_data->parent_data;
		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम irq_करोमुख्य_मुक्त_irq_data(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irq_data, *पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_data = irq_get_irq_data(virq + i);
		पंचांगp = irq_data->parent_data;
		irq_data->parent_data = शून्य;
		irq_data->करोमुख्य = शून्य;

		__irq_करोमुख्य_मुक्त_hierarchy(पंचांगp);
	पूर्ण
पूर्ण

/**
 * irq_करोमुख्य_disconnect_hierarchy - Mark the first unused level of a hierarchy
 * @करोमुख्य:	IRQ करोमुख्य from which the hierarchy is to be disconnected
 * @virq:	IRQ number where the hierarchy is to be trimmed
 *
 * Marks the @virq level beदीर्घing to @करोमुख्य as disconnected.
 * Returns -EINVAL अगर @virq करोesn't have a valid irq_data poपूर्णांकing
 * to @करोमुख्य.
 *
 * Its only use is to be able to trim levels of hierarchy that करो not
 * have any real meaning क्रम this पूर्णांकerrupt, and that the driver marks
 * as such from its .alloc() callback.
 */
पूर्णांक irq_करोमुख्य_disconnect_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक virq)
अणु
	काष्ठा irq_data *irqd;

	irqd = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	अगर (!irqd)
		वापस -EINVAL;

	irqd->chip = ERR_PTR(-ENOTCONN);
	वापस 0;
पूर्ण

अटल पूर्णांक irq_करोमुख्य_trim_hierarchy(अचिन्हित पूर्णांक virq)
अणु
	काष्ठा irq_data *tail, *irqd, *irq_data;

	irq_data = irq_get_irq_data(virq);
	tail = शून्य;

	/* The first entry must have a valid irqchip */
	अगर (!irq_data->chip || IS_ERR(irq_data->chip))
		वापस -EINVAL;

	/*
	 * Validate that the irq_data chain is sane in the presence of
	 * a hierarchy trimming marker.
	 */
	क्रम (irqd = irq_data->parent_data; irqd; irq_data = irqd, irqd = irqd->parent_data) अणु
		/* Can't have a valid irqchip after a trim marker */
		अगर (irqd->chip && tail)
			वापस -EINVAL;

		/* Can't have an empty irqchip beक्रमe a trim marker */
		अगर (!irqd->chip && !tail)
			वापस -EINVAL;

		अगर (IS_ERR(irqd->chip)) अणु
			/* Only -ENOTCONN is a valid trim marker */
			अगर (PTR_ERR(irqd->chip) != -ENOTCONN)
				वापस -EINVAL;

			tail = irq_data;
		पूर्ण
	पूर्ण

	/* No trim marker, nothing to करो */
	अगर (!tail)
		वापस 0;

	pr_info("IRQ%d: trimming hierarchy from %s\n",
		virq, tail->parent_data->करोमुख्य->name);

	/* Sever the inner part of the hierarchy...  */
	irqd = tail;
	tail = tail->parent_data;
	irqd->parent_data = शून्य;
	__irq_करोमुख्य_मुक्त_hierarchy(tail);

	वापस 0;
पूर्ण

अटल पूर्णांक irq_करोमुख्य_alloc_irq_data(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irq_data;
	काष्ठा irq_करोमुख्य *parent;
	पूर्णांक i;

	/* The outermost irq_data is embedded in काष्ठा irq_desc */
	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_data = irq_get_irq_data(virq + i);
		irq_data->करोमुख्य = करोमुख्य;

		क्रम (parent = करोमुख्य->parent; parent; parent = parent->parent) अणु
			irq_data = irq_करोमुख्य_insert_irq_data(parent, irq_data);
			अगर (!irq_data) अणु
				irq_करोमुख्य_मुक्त_irq_data(virq, i + 1);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * irq_करोमुख्य_get_irq_data - Get irq_data associated with @virq and @करोमुख्य
 * @करोमुख्य:	करोमुख्य to match
 * @virq:	IRQ number to get irq_data
 */
काष्ठा irq_data *irq_करोमुख्य_get_irq_data(काष्ठा irq_करोमुख्य *करोमुख्य,
					 अचिन्हित पूर्णांक virq)
अणु
	काष्ठा irq_data *irq_data;

	क्रम (irq_data = irq_get_irq_data(virq); irq_data;
	     irq_data = irq_data->parent_data)
		अगर (irq_data->करोमुख्य == करोमुख्य)
			वापस irq_data;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_get_irq_data);

/**
 * irq_करोमुख्य_set_hwirq_and_chip - Set hwirq and irqchip of @virq at @करोमुख्य
 * @करोमुख्य:	Interrupt करोमुख्य to match
 * @virq:	IRQ number
 * @hwirq:	The hwirq number
 * @chip:	The associated पूर्णांकerrupt chip
 * @chip_data:	The associated chip data
 */
पूर्णांक irq_करोमुख्य_set_hwirq_and_chip(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  irq_hw_number_t hwirq, काष्ठा irq_chip *chip,
				  व्योम *chip_data)
अणु
	काष्ठा irq_data *irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	अगर (!irq_data)
		वापस -ENOENT;

	irq_data->hwirq = hwirq;
	irq_data->chip = chip ? chip : &no_irq_chip;
	irq_data->chip_data = chip_data;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_set_hwirq_and_chip);

/**
 * irq_करोमुख्य_set_info - Set the complete data क्रम a @virq in @करोमुख्य
 * @करोमुख्य:		Interrupt करोमुख्य to match
 * @virq:		IRQ number
 * @hwirq:		The hardware पूर्णांकerrupt number
 * @chip:		The associated पूर्णांकerrupt chip
 * @chip_data:		The associated पूर्णांकerrupt chip data
 * @handler:		The पूर्णांकerrupt flow handler
 * @handler_data:	The पूर्णांकerrupt flow handler data
 * @handler_name:	The पूर्णांकerrupt handler name
 */
व्योम irq_करोमुख्य_set_info(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hwirq, काष्ठा irq_chip *chip,
			 व्योम *chip_data, irq_flow_handler_t handler,
			 व्योम *handler_data, स्थिर अक्षर *handler_name)
अणु
	irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq, chip, chip_data);
	__irq_set_handler(virq, handler, 0, handler_name);
	irq_set_handler_data(virq, handler_data);
पूर्ण
EXPORT_SYMBOL(irq_करोमुख्य_set_info);

/**
 * irq_करोमुख्य_मुक्त_irqs_common - Clear irq_data and मुक्त the parent
 * @करोमुख्य:	Interrupt करोमुख्य to match
 * @virq:	IRQ number to start with
 * @nr_irqs:	The number of irqs to मुक्त
 */
व्योम irq_करोमुख्य_मुक्त_irqs_common(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irq_data;
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);
		अगर (irq_data)
			irq_करोमुख्य_reset_irq_data(irq_data);
	पूर्ण
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_मुक्त_irqs_common);

/**
 * irq_करोमुख्य_मुक्त_irqs_top - Clear handler and handler data, clear irqdata and मुक्त parent
 * @करोमुख्य:	Interrupt करोमुख्य to match
 * @virq:	IRQ number to start with
 * @nr_irqs:	The number of irqs to मुक्त
 */
व्योम irq_करोमुख्य_मुक्त_irqs_top(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_set_handler_data(virq + i, शून्य);
		irq_set_handler(virq + i, शून्य);
	पूर्ण
	irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल व्योम irq_करोमुख्य_मुक्त_irqs_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य,
					   अचिन्हित पूर्णांक irq_base,
					   अचिन्हित पूर्णांक nr_irqs)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!करोमुख्य->ops->मुक्त)
		वापस;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		अगर (irq_करोमुख्य_get_irq_data(करोमुख्य, irq_base + i))
			करोमुख्य->ops->मुक्त(करोमुख्य, irq_base + i, 1);
	पूर्ण
पूर्ण

पूर्णांक irq_करोमुख्य_alloc_irqs_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक irq_base,
				    अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	अगर (!करोमुख्य->ops->alloc) अणु
		pr_debug("domain->ops->alloc() is NULL\n");
		वापस -ENOSYS;
	पूर्ण

	वापस करोमुख्य->ops->alloc(करोमुख्य, irq_base, nr_irqs, arg);
पूर्ण

/**
 * __irq_करोमुख्य_alloc_irqs - Allocate IRQs from करोमुख्य
 * @करोमुख्य:	करोमुख्य to allocate from
 * @irq_base:	allocate specअगरied IRQ number अगर irq_base >= 0
 * @nr_irqs:	number of IRQs to allocate
 * @node:	NUMA node id क्रम memory allocation
 * @arg:	करोमुख्य specअगरic argument
 * @पुनः_स्मृति:	IRQ descriptors have alपढ़ोy been allocated अगर true
 * @affinity:	Optional irq affinity mask क्रम multiqueue devices
 *
 * Allocate IRQ numbers and initialized all data काष्ठाures to support
 * hierarchy IRQ करोमुख्यs.
 * Parameter @पुनः_स्मृति is मुख्यly to support legacy IRQs.
 * Returns error code or allocated IRQ number
 *
 * The whole process to setup an IRQ has been split पूर्णांकo two steps.
 * The first step, __irq_करोमुख्य_alloc_irqs(), is to allocate IRQ
 * descriptor and required hardware resources. The second step,
 * irq_करोमुख्य_activate_irq(), is to program the hardware with pपुनः_स्मृतिated
 * resources. In this way, it's easier to rollback when failing to
 * allocate resources.
 */
पूर्णांक __irq_करोमुख्य_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, पूर्णांक irq_base,
			    अचिन्हित पूर्णांक nr_irqs, पूर्णांक node, व्योम *arg,
			    bool पुनः_स्मृति, स्थिर काष्ठा irq_affinity_desc *affinity)
अणु
	पूर्णांक i, ret, virq;

	अगर (करोमुख्य == शून्य) अणु
		करोमुख्य = irq_शेष_करोमुख्य;
		अगर (WARN(!करोमुख्य, "domain is NULL; cannot allocate IRQ\n"))
			वापस -EINVAL;
	पूर्ण

	अगर (पुनः_स्मृति && irq_base >= 0) अणु
		virq = irq_base;
	पूर्ण अन्यथा अणु
		virq = irq_करोमुख्य_alloc_descs(irq_base, nr_irqs, 0, node,
					      affinity);
		अगर (virq < 0) अणु
			pr_debug("cannot allocate IRQ(base %d, count %d)\n",
				 irq_base, nr_irqs);
			वापस virq;
		पूर्ण
	पूर्ण

	अगर (irq_करोमुख्य_alloc_irq_data(करोमुख्य, virq, nr_irqs)) अणु
		pr_debug("cannot allocate memory for IRQ%d\n", virq);
		ret = -ENOMEM;
		जाओ out_मुक्त_desc;
	पूर्ण

	mutex_lock(&irq_करोमुख्य_mutex);
	ret = irq_करोमुख्य_alloc_irqs_hierarchy(करोमुख्य, virq, nr_irqs, arg);
	अगर (ret < 0) अणु
		mutex_unlock(&irq_करोमुख्य_mutex);
		जाओ out_मुक्त_irq_data;
	पूर्ण

	क्रम (i = 0; i < nr_irqs; i++) अणु
		ret = irq_करोमुख्य_trim_hierarchy(virq + i);
		अगर (ret) अणु
			mutex_unlock(&irq_करोमुख्य_mutex);
			जाओ out_मुक्त_irq_data;
		पूर्ण
	पूर्ण
	
	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_insert_irq(virq + i);
	mutex_unlock(&irq_करोमुख्य_mutex);

	वापस virq;

out_मुक्त_irq_data:
	irq_करोमुख्य_मुक्त_irq_data(virq, nr_irqs);
out_मुक्त_desc:
	irq_मुक्त_descs(virq, nr_irqs);
	वापस ret;
पूर्ण

/* The irq_data was moved, fix the revmap to refer to the new location */
अटल व्योम irq_करोमुख्य_fix_revmap(काष्ठा irq_data *d)
अणु
	व्योम __rcu **slot;

	अगर (d->hwirq < d->करोमुख्य->revmap_size)
		वापस; /* Not using radix tree. */

	/* Fix up the revmap. */
	mutex_lock(&d->करोमुख्य->revmap_tree_mutex);
	slot = radix_tree_lookup_slot(&d->करोमुख्य->revmap_tree, d->hwirq);
	अगर (slot)
		radix_tree_replace_slot(&d->करोमुख्य->revmap_tree, slot, d);
	mutex_unlock(&d->करोमुख्य->revmap_tree_mutex);
पूर्ण

/**
 * irq_करोमुख्य_push_irq() - Push a करोमुख्य in to the top of a hierarchy.
 * @करोमुख्य:	Doमुख्य to push.
 * @virq:	Irq to push the करोमुख्य in to.
 * @arg:	Passed to the irq_करोमुख्य_ops alloc() function.
 *
 * For an alपढ़ोy existing irqकरोमुख्य hierarchy, as might be obtained
 * via a call to pci_enable_msix(), add an additional करोमुख्य to the
 * head of the processing chain.  Must be called beक्रमe request_irq()
 * has been called.
 */
पूर्णांक irq_करोमुख्य_push_irq(काष्ठा irq_करोमुख्य *करोमुख्य, पूर्णांक virq, व्योम *arg)
अणु
	काष्ठा irq_data *child_irq_data;
	काष्ठा irq_data *root_irq_data = irq_get_irq_data(virq);
	काष्ठा irq_desc *desc;
	पूर्णांक rv = 0;

	/*
	 * Check that no action has been set, which indicates the virq
	 * is in a state where this function करोesn't have to deal with
	 * races between पूर्णांकerrupt handling and मुख्यtaining the
	 * hierarchy.  This will catch gross misuse.  Attempting to
	 * make the check race मुक्त would require holding locks across
	 * calls to काष्ठा irq_करोमुख्य_ops->alloc(), which could lead
	 * to deadlock, so we just करो a simple check beक्रमe starting.
	 */
	desc = irq_to_desc(virq);
	अगर (!desc)
		वापस -EINVAL;
	अगर (WARN_ON(desc->action))
		वापस -EBUSY;

	अगर (करोमुख्य == शून्य)
		वापस -EINVAL;

	अगर (WARN_ON(!irq_करोमुख्य_is_hierarchy(करोमुख्य)))
		वापस -EINVAL;

	अगर (!root_irq_data)
		वापस -EINVAL;

	अगर (करोमुख्य->parent != root_irq_data->करोमुख्य)
		वापस -EINVAL;

	child_irq_data = kzalloc_node(माप(*child_irq_data), GFP_KERNEL,
				      irq_data_get_node(root_irq_data));
	अगर (!child_irq_data)
		वापस -ENOMEM;

	mutex_lock(&irq_करोमुख्य_mutex);

	/* Copy the original irq_data. */
	*child_irq_data = *root_irq_data;

	/*
	 * Overग_लिखो the root_irq_data, which is embedded in काष्ठा
	 * irq_desc, with values क्रम this करोमुख्य.
	 */
	root_irq_data->parent_data = child_irq_data;
	root_irq_data->करोमुख्य = करोमुख्य;
	root_irq_data->mask = 0;
	root_irq_data->hwirq = 0;
	root_irq_data->chip = शून्य;
	root_irq_data->chip_data = शून्य;

	/* May (probably करोes) set hwirq, chip, etc. */
	rv = irq_करोमुख्य_alloc_irqs_hierarchy(करोमुख्य, virq, 1, arg);
	अगर (rv) अणु
		/* Restore the original irq_data. */
		*root_irq_data = *child_irq_data;
		kमुक्त(child_irq_data);
		जाओ error;
	पूर्ण

	irq_करोमुख्य_fix_revmap(child_irq_data);
	irq_करोमुख्य_set_mapping(करोमुख्य, root_irq_data->hwirq, root_irq_data);

error:
	mutex_unlock(&irq_करोमुख्य_mutex);

	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_push_irq);

/**
 * irq_करोमुख्य_pop_irq() - Remove a करोमुख्य from the top of a hierarchy.
 * @करोमुख्य:	Doमुख्य to हटाओ.
 * @virq:	Irq to हटाओ the करोमुख्य from.
 *
 * Unकरो the effects of a call to irq_करोमुख्य_push_irq().  Must be
 * called either beक्रमe request_irq() or after मुक्त_irq().
 */
पूर्णांक irq_करोमुख्य_pop_irq(काष्ठा irq_करोमुख्य *करोमुख्य, पूर्णांक virq)
अणु
	काष्ठा irq_data *root_irq_data = irq_get_irq_data(virq);
	काष्ठा irq_data *child_irq_data;
	काष्ठा irq_data *पंचांगp_irq_data;
	काष्ठा irq_desc *desc;

	/*
	 * Check that no action is set, which indicates the virq is in
	 * a state where this function करोesn't have to deal with races
	 * between पूर्णांकerrupt handling and मुख्यtaining the hierarchy.
	 * This will catch gross misuse.  Attempting to make the check
	 * race मुक्त would require holding locks across calls to
	 * काष्ठा irq_करोमुख्य_ops->मुक्त(), which could lead to
	 * deadlock, so we just करो a simple check beक्रमe starting.
	 */
	desc = irq_to_desc(virq);
	अगर (!desc)
		वापस -EINVAL;
	अगर (WARN_ON(desc->action))
		वापस -EBUSY;

	अगर (करोमुख्य == शून्य)
		वापस -EINVAL;

	अगर (!root_irq_data)
		वापस -EINVAL;

	पंचांगp_irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	/* We can only "pop" अगर this करोमुख्य is at the top of the list */
	अगर (WARN_ON(root_irq_data != पंचांगp_irq_data))
		वापस -EINVAL;

	अगर (WARN_ON(root_irq_data->करोमुख्य != करोमुख्य))
		वापस -EINVAL;

	child_irq_data = root_irq_data->parent_data;
	अगर (WARN_ON(!child_irq_data))
		वापस -EINVAL;

	mutex_lock(&irq_करोमुख्य_mutex);

	root_irq_data->parent_data = शून्य;

	irq_करोमुख्य_clear_mapping(करोमुख्य, root_irq_data->hwirq);
	irq_करोमुख्य_मुक्त_irqs_hierarchy(करोमुख्य, virq, 1);

	/* Restore the original irq_data. */
	*root_irq_data = *child_irq_data;

	irq_करोमुख्य_fix_revmap(root_irq_data);

	mutex_unlock(&irq_करोमुख्य_mutex);

	kमुक्त(child_irq_data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_pop_irq);

/**
 * irq_करोमुख्य_मुक्त_irqs - Free IRQ number and associated data काष्ठाures
 * @virq:	base IRQ number
 * @nr_irqs:	number of IRQs to मुक्त
 */
व्योम irq_करोमुख्य_मुक्त_irqs(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *data = irq_get_irq_data(virq);
	पूर्णांक i;

	अगर (WARN(!data || !data->करोमुख्य || !data->करोमुख्य->ops->मुक्त,
		 "NULL pointer, cannot free irq\n"))
		वापस;

	mutex_lock(&irq_करोमुख्य_mutex);
	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_हटाओ_irq(virq + i);
	irq_करोमुख्य_मुक्त_irqs_hierarchy(data->करोमुख्य, virq, nr_irqs);
	mutex_unlock(&irq_करोमुख्य_mutex);

	irq_करोमुख्य_मुक्त_irq_data(virq, nr_irqs);
	irq_मुक्त_descs(virq, nr_irqs);
पूर्ण

/**
 * irq_करोमुख्य_alloc_irqs_parent - Allocate पूर्णांकerrupts from parent करोमुख्य
 * @करोमुख्य:	Doमुख्य below which पूर्णांकerrupts must be allocated
 * @irq_base:	Base IRQ number
 * @nr_irqs:	Number of IRQs to allocate
 * @arg:	Allocation data (arch/करोमुख्य specअगरic)
 */
पूर्णांक irq_करोमुख्य_alloc_irqs_parent(काष्ठा irq_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक irq_base, अचिन्हित पूर्णांक nr_irqs,
				 व्योम *arg)
अणु
	अगर (!करोमुख्य->parent)
		वापस -ENOSYS;

	वापस irq_करोमुख्य_alloc_irqs_hierarchy(करोमुख्य->parent, irq_base,
					       nr_irqs, arg);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_alloc_irqs_parent);

/**
 * irq_करोमुख्य_मुक्त_irqs_parent - Free पूर्णांकerrupts from parent करोमुख्य
 * @करोमुख्य:	Doमुख्य below which पूर्णांकerrupts must be मुक्तd
 * @irq_base:	Base IRQ number
 * @nr_irqs:	Number of IRQs to मुक्त
 */
व्योम irq_करोमुख्य_मुक्त_irqs_parent(काष्ठा irq_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक irq_base, अचिन्हित पूर्णांक nr_irqs)
अणु
	अगर (!करोमुख्य->parent)
		वापस;

	irq_करोमुख्य_मुक्त_irqs_hierarchy(करोमुख्य->parent, irq_base, nr_irqs);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_मुक्त_irqs_parent);

अटल व्योम __irq_करोमुख्य_deactivate_irq(काष्ठा irq_data *irq_data)
अणु
	अगर (irq_data && irq_data->करोमुख्य) अणु
		काष्ठा irq_करोमुख्य *करोमुख्य = irq_data->करोमुख्य;

		अगर (करोमुख्य->ops->deactivate)
			करोमुख्य->ops->deactivate(करोमुख्य, irq_data);
		अगर (irq_data->parent_data)
			__irq_करोमुख्य_deactivate_irq(irq_data->parent_data);
	पूर्ण
पूर्ण

अटल पूर्णांक __irq_करोमुख्य_activate_irq(काष्ठा irq_data *irqd, bool reserve)
अणु
	पूर्णांक ret = 0;

	अगर (irqd && irqd->करोमुख्य) अणु
		काष्ठा irq_करोमुख्य *करोमुख्य = irqd->करोमुख्य;

		अगर (irqd->parent_data)
			ret = __irq_करोमुख्य_activate_irq(irqd->parent_data,
							reserve);
		अगर (!ret && करोमुख्य->ops->activate) अणु
			ret = करोमुख्य->ops->activate(करोमुख्य, irqd, reserve);
			/* Rollback in हाल of error */
			अगर (ret && irqd->parent_data)
				__irq_करोमुख्य_deactivate_irq(irqd->parent_data);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * irq_करोमुख्य_activate_irq - Call करोमुख्य_ops->activate recursively to activate
 *			     पूर्णांकerrupt
 * @irq_data:	Outermost irq_data associated with पूर्णांकerrupt
 * @reserve:	If set only reserve an पूर्णांकerrupt vector instead of assigning one
 *
 * This is the second step to call करोमुख्य_ops->activate to program पूर्णांकerrupt
 * controllers, so the पूर्णांकerrupt could actually get delivered.
 */
पूर्णांक irq_करोमुख्य_activate_irq(काष्ठा irq_data *irq_data, bool reserve)
अणु
	पूर्णांक ret = 0;

	अगर (!irqd_is_activated(irq_data))
		ret = __irq_करोमुख्य_activate_irq(irq_data, reserve);
	अगर (!ret)
		irqd_set_activated(irq_data);
	वापस ret;
पूर्ण

/**
 * irq_करोमुख्य_deactivate_irq - Call करोमुख्य_ops->deactivate recursively to
 *			       deactivate पूर्णांकerrupt
 * @irq_data: outermost irq_data associated with पूर्णांकerrupt
 *
 * It calls करोमुख्य_ops->deactivate to program पूर्णांकerrupt controllers to disable
 * पूर्णांकerrupt delivery.
 */
व्योम irq_करोमुख्य_deactivate_irq(काष्ठा irq_data *irq_data)
अणु
	अगर (irqd_is_activated(irq_data)) अणु
		__irq_करोमुख्य_deactivate_irq(irq_data);
		irqd_clr_activated(irq_data);
	पूर्ण
पूर्ण

अटल व्योम irq_करोमुख्य_check_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	/* Hierarchy irq_करोमुख्यs must implement callback alloc() */
	अगर (करोमुख्य->ops->alloc)
		करोमुख्य->flags |= IRQ_DOMAIN_FLAG_HIERARCHY;
पूर्ण

/**
 * irq_करोमुख्य_hierarchical_is_msi_remap - Check अगर the करोमुख्य or any
 * parent has MSI remapping support
 * @करोमुख्य: करोमुख्य poपूर्णांकer
 */
bool irq_करोमुख्य_hierarchical_is_msi_remap(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	क्रम (; करोमुख्य; करोमुख्य = करोमुख्य->parent) अणु
		अगर (irq_करोमुख्य_is_msi_remap(करोमुख्य))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
#अन्यथा	/* CONFIG_IRQ_DOMAIN_HIERARCHY */
/**
 * irq_करोमुख्य_get_irq_data - Get irq_data associated with @virq and @करोमुख्य
 * @करोमुख्य:	करोमुख्य to match
 * @virq:	IRQ number to get irq_data
 */
काष्ठा irq_data *irq_करोमुख्य_get_irq_data(काष्ठा irq_करोमुख्य *करोमुख्य,
					 अचिन्हित पूर्णांक virq)
अणु
	काष्ठा irq_data *irq_data = irq_get_irq_data(virq);

	वापस (irq_data && irq_data->करोमुख्य == करोमुख्य) ? irq_data : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_get_irq_data);

/**
 * irq_करोमुख्य_set_info - Set the complete data क्रम a @virq in @करोमुख्य
 * @करोमुख्य:		Interrupt करोमुख्य to match
 * @virq:		IRQ number
 * @hwirq:		The hardware पूर्णांकerrupt number
 * @chip:		The associated पूर्णांकerrupt chip
 * @chip_data:		The associated पूर्णांकerrupt chip data
 * @handler:		The पूर्णांकerrupt flow handler
 * @handler_data:	The पूर्णांकerrupt flow handler data
 * @handler_name:	The पूर्णांकerrupt handler name
 */
व्योम irq_करोमुख्य_set_info(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hwirq, काष्ठा irq_chip *chip,
			 व्योम *chip_data, irq_flow_handler_t handler,
			 व्योम *handler_data, स्थिर अक्षर *handler_name)
अणु
	irq_set_chip_and_handler_name(virq, chip, handler, handler_name);
	irq_set_chip_data(virq, chip_data);
	irq_set_handler_data(virq, handler_data);
पूर्ण

अटल व्योम irq_करोमुख्य_check_hierarchy(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_IRQ_DOMAIN_HIERARCHY */

#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
अटल काष्ठा dentry *करोमुख्य_dir;

अटल व्योम
irq_करोमुख्य_debug_show_one(काष्ठा seq_file *m, काष्ठा irq_करोमुख्य *d, पूर्णांक ind)
अणु
	seq_म_लिखो(m, "%*sname:   %s\n", ind, "", d->name);
	seq_म_लिखो(m, "%*ssize:   %u\n", ind + 1, "",
		   d->revmap_size + d->revmap_direct_max_irq);
	seq_म_लिखो(m, "%*smapped: %u\n", ind + 1, "", d->mapcount);
	seq_म_लिखो(m, "%*sflags:  0x%08x\n", ind +1 , "", d->flags);
	अगर (d->ops && d->ops->debug_show)
		d->ops->debug_show(m, d, शून्य, ind + 1);
#अगर_घोषित	CONFIG_IRQ_DOMAIN_HIERARCHY
	अगर (!d->parent)
		वापस;
	seq_म_लिखो(m, "%*sparent: %s\n", ind + 1, "", d->parent->name);
	irq_करोमुख्य_debug_show_one(m, d->parent, ind + 4);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक irq_करोमुख्य_debug_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा irq_करोमुख्य *d = m->निजी;

	/* Default करोमुख्य? Might be शून्य */
	अगर (!d) अणु
		अगर (!irq_शेष_करोमुख्य)
			वापस 0;
		d = irq_शेष_करोमुख्य;
	पूर्ण
	irq_करोमुख्य_debug_show_one(m, d, 0);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(irq_करोमुख्य_debug);

अटल व्योम debugfs_add_करोमुख्य_dir(काष्ठा irq_करोमुख्य *d)
अणु
	अगर (!d->name || !करोमुख्य_dir)
		वापस;
	debugfs_create_file(d->name, 0444, करोमुख्य_dir, d,
			    &irq_करोमुख्य_debug_fops);
पूर्ण

अटल व्योम debugfs_हटाओ_करोमुख्य_dir(काष्ठा irq_करोमुख्य *d)
अणु
	debugfs_हटाओ(debugfs_lookup(d->name, करोमुख्य_dir));
पूर्ण

व्योम __init irq_करोमुख्य_debugfs_init(काष्ठा dentry *root)
अणु
	काष्ठा irq_करोमुख्य *d;

	करोमुख्य_dir = debugfs_create_dir("domains", root);

	debugfs_create_file("default", 0444, करोमुख्य_dir, शून्य,
			    &irq_करोमुख्य_debug_fops);
	mutex_lock(&irq_करोमुख्य_mutex);
	list_क्रम_each_entry(d, &irq_करोमुख्य_list, link)
		debugfs_add_करोमुख्य_dir(d);
	mutex_unlock(&irq_करोमुख्य_mutex);
पूर्ण
#पूर्ण_अगर
