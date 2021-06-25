<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम dynamic device trees.
 *
 * On some platक्रमms, the device tree can be manipulated at runसमय.
 * The routines in this section support adding, removing and changing
 * device tree nodes.
 */

#घोषणा pr_fmt(fmt)	"OF: " fmt

#समावेश <linux/of.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/proc_fs.h>

#समावेश "of_private.h"

अटल काष्ठा device_node *kobj_to_device_node(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा device_node, kobj);
पूर्ण

/**
 * of_node_get() - Increment refcount of a node
 * @node:	Node to inc refcount, शून्य is supported to simplअगरy writing of
 *		callers
 *
 * Return: The node with refcount incremented.
 */
काष्ठा device_node *of_node_get(काष्ठा device_node *node)
अणु
	अगर (node)
		kobject_get(&node->kobj);
	वापस node;
पूर्ण
EXPORT_SYMBOL(of_node_get);

/**
 * of_node_put() - Decrement refcount of a node
 * @node:	Node to dec refcount, शून्य is supported to simplअगरy writing of
 *		callers
 */
व्योम of_node_put(काष्ठा device_node *node)
अणु
	अगर (node)
		kobject_put(&node->kobj);
पूर्ण
EXPORT_SYMBOL(of_node_put);

अटल BLOCKING_NOTIFIER_HEAD(of_reconfig_chain);

पूर्णांक of_reconfig_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&of_reconfig_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(of_reconfig_notअगरier_रेजिस्टर);

पूर्णांक of_reconfig_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&of_reconfig_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(of_reconfig_notअगरier_unरेजिस्टर);

#अगर_घोषित DEBUG
स्थिर अक्षर *action_names[] = अणु
	[OF_RECONFIG_ATTACH_NODE] = "ATTACH_NODE",
	[OF_RECONFIG_DETACH_NODE] = "DETACH_NODE",
	[OF_RECONFIG_ADD_PROPERTY] = "ADD_PROPERTY",
	[OF_RECONFIG_REMOVE_PROPERTY] = "REMOVE_PROPERTY",
	[OF_RECONFIG_UPDATE_PROPERTY] = "UPDATE_PROPERTY",
पूर्ण;
#पूर्ण_अगर

पूर्णांक of_reconfig_notअगरy(अचिन्हित दीर्घ action, काष्ठा of_reconfig_data *p)
अणु
	पूर्णांक rc;
#अगर_घोषित DEBUG
	काष्ठा of_reconfig_data *pr = p;

	चयन (action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
	हाल OF_RECONFIG_DETACH_NODE:
		pr_debug("notify %-15s %pOF\n", action_names[action],
			pr->dn);
		अवरोध;
	हाल OF_RECONFIG_ADD_PROPERTY:
	हाल OF_RECONFIG_REMOVE_PROPERTY:
	हाल OF_RECONFIG_UPDATE_PROPERTY:
		pr_debug("notify %-15s %pOF:%s\n", action_names[action],
			pr->dn, pr->prop->name);
		अवरोध;

	पूर्ण
#पूर्ण_अगर
	rc = blocking_notअगरier_call_chain(&of_reconfig_chain, action, p);
	वापस notअगरier_to_त्रुटि_सं(rc);
पूर्ण

/*
 * of_reconfig_get_state_change()	- Returns new state of device
 * @action	- action of the of notअगरier
 * @arg		- argument of the of notअगरier
 *
 * Returns the new state of a device based on the notअगरier used.
 *
 * Return: 0 on device going from enabled to disabled, 1 on device
 * going from disabled to enabled and -1 on no change.
 */
पूर्णांक of_reconfig_get_state_change(अचिन्हित दीर्घ action, काष्ठा of_reconfig_data *pr)
अणु
	काष्ठा property *prop, *old_prop = शून्य;
	पूर्णांक is_status, status_state, old_status_state, prev_state, new_state;

	/* figure out अगर a device should be created or destroyed */
	चयन (action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
	हाल OF_RECONFIG_DETACH_NODE:
		prop = of_find_property(pr->dn, "status", शून्य);
		अवरोध;
	हाल OF_RECONFIG_ADD_PROPERTY:
	हाल OF_RECONFIG_REMOVE_PROPERTY:
		prop = pr->prop;
		अवरोध;
	हाल OF_RECONFIG_UPDATE_PROPERTY:
		prop = pr->prop;
		old_prop = pr->old_prop;
		अवरोध;
	शेष:
		वापस OF_RECONFIG_NO_CHANGE;
	पूर्ण

	is_status = 0;
	status_state = -1;
	old_status_state = -1;
	prev_state = -1;
	new_state = -1;

	अगर (prop && !म_भेद(prop->name, "status")) अणु
		is_status = 1;
		status_state = !म_भेद(prop->value, "okay") ||
			       !म_भेद(prop->value, "ok");
		अगर (old_prop)
			old_status_state = !म_भेद(old_prop->value, "okay") ||
					   !म_भेद(old_prop->value, "ok");
	पूर्ण

	चयन (action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
		prev_state = 0;
		/* -1 & 0 status either missing or okay */
		new_state = status_state != 0;
		अवरोध;
	हाल OF_RECONFIG_DETACH_NODE:
		/* -1 & 0 status either missing or okay */
		prev_state = status_state != 0;
		new_state = 0;
		अवरोध;
	हाल OF_RECONFIG_ADD_PROPERTY:
		अगर (is_status) अणु
			/* no status property -> enabled (legacy) */
			prev_state = 1;
			new_state = status_state;
		पूर्ण
		अवरोध;
	हाल OF_RECONFIG_REMOVE_PROPERTY:
		अगर (is_status) अणु
			prev_state = status_state;
			/* no status property -> enabled (legacy) */
			new_state = 1;
		पूर्ण
		अवरोध;
	हाल OF_RECONFIG_UPDATE_PROPERTY:
		अगर (is_status) अणु
			prev_state = old_status_state != 0;
			new_state = status_state != 0;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (prev_state == new_state)
		वापस OF_RECONFIG_NO_CHANGE;

	वापस new_state ? OF_RECONFIG_CHANGE_ADD : OF_RECONFIG_CHANGE_REMOVE;
पूर्ण
EXPORT_SYMBOL_GPL(of_reconfig_get_state_change);

पूर्णांक of_property_notअगरy(पूर्णांक action, काष्ठा device_node *np,
		       काष्ठा property *prop, काष्ठा property *oldprop)
अणु
	काष्ठा of_reconfig_data pr;

	/* only call notअगरiers अगर the node is attached */
	अगर (!of_node_is_attached(np))
		वापस 0;

	pr.dn = np;
	pr.prop = prop;
	pr.old_prop = oldprop;
	वापस of_reconfig_notअगरy(action, &pr);
पूर्ण

अटल व्योम __of_attach_node(काष्ठा device_node *np)
अणु
	स्थिर __be32 *phandle;
	पूर्णांक sz;

	अगर (!of_node_check_flag(np, OF_OVERLAY)) अणु
		np->name = __of_get_property(np, "name", शून्य);
		अगर (!np->name)
			np->name = "<NULL>";

		phandle = __of_get_property(np, "phandle", &sz);
		अगर (!phandle)
			phandle = __of_get_property(np, "linux,phandle", &sz);
		अगर (IS_ENABLED(CONFIG_PPC_PSERIES) && !phandle)
			phandle = __of_get_property(np, "ibm,phandle", &sz);
		अगर (phandle && (sz >= 4))
			np->phandle = be32_to_cpup(phandle);
		अन्यथा
			np->phandle = 0;
	पूर्ण

	np->child = शून्य;
	np->sibling = np->parent->child;
	np->parent->child = np;
	of_node_clear_flag(np, OF_DETACHED);
पूर्ण

/**
 * of_attach_node() - Plug a device node पूर्णांकo the tree and global list.
 * @np:		Poपूर्णांकer to the caller's Device Node
 */
पूर्णांक of_attach_node(काष्ठा device_node *np)
अणु
	काष्ठा of_reconfig_data rd;
	अचिन्हित दीर्घ flags;

	स_रखो(&rd, 0, माप(rd));
	rd.dn = np;

	mutex_lock(&of_mutex);
	raw_spin_lock_irqsave(&devtree_lock, flags);
	__of_attach_node(np);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	__of_attach_node_sysfs(np);
	mutex_unlock(&of_mutex);

	of_reconfig_notअगरy(OF_RECONFIG_ATTACH_NODE, &rd);

	वापस 0;
पूर्ण

व्योम __of_detach_node(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent;

	अगर (WARN_ON(of_node_check_flag(np, OF_DETACHED)))
		वापस;

	parent = np->parent;
	अगर (WARN_ON(!parent))
		वापस;

	अगर (parent->child == np)
		parent->child = np->sibling;
	अन्यथा अणु
		काष्ठा device_node *prevsib;
		क्रम (prevsib = np->parent->child;
		     prevsib->sibling != np;
		     prevsib = prevsib->sibling)
			;
		prevsib->sibling = np->sibling;
	पूर्ण

	of_node_set_flag(np, OF_DETACHED);

	/* race with of_find_node_by_phandle() prevented by devtree_lock */
	__of_phandle_cache_inv_entry(np->phandle);
पूर्ण

/**
 * of_detach_node() - "Unplug" a node from the device tree.
 * @np:		Poपूर्णांकer to the caller's Device Node
 */
पूर्णांक of_detach_node(काष्ठा device_node *np)
अणु
	काष्ठा of_reconfig_data rd;
	अचिन्हित दीर्घ flags;

	स_रखो(&rd, 0, माप(rd));
	rd.dn = np;

	mutex_lock(&of_mutex);
	raw_spin_lock_irqsave(&devtree_lock, flags);
	__of_detach_node(np);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	__of_detach_node_sysfs(np);
	mutex_unlock(&of_mutex);

	of_reconfig_notअगरy(OF_RECONFIG_DETACH_NODE, &rd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_detach_node);

अटल व्योम property_list_मुक्त(काष्ठा property *prop_list)
अणु
	काष्ठा property *prop, *next;

	क्रम (prop = prop_list; prop != शून्य; prop = next) अणु
		next = prop->next;
		kमुक्त(prop->name);
		kमुक्त(prop->value);
		kमुक्त(prop);
	पूर्ण
पूर्ण

/**
 * of_node_release() - release a dynamically allocated node
 * @kobj: kernel object of the node to be released
 *
 * In of_node_put() this function is passed to kref_put() as the deकाष्ठाor.
 */
व्योम of_node_release(काष्ठा kobject *kobj)
अणु
	काष्ठा device_node *node = kobj_to_device_node(kobj);

	/* We should never be releasing nodes that haven't been detached. */
	अगर (!of_node_check_flag(node, OF_DETACHED)) अणु
		pr_err("ERROR: Bad of_node_put() on %pOF\n", node);
		dump_stack();
		वापस;
	पूर्ण
	अगर (!of_node_check_flag(node, OF_DYNAMIC))
		वापस;

	अगर (of_node_check_flag(node, OF_OVERLAY)) अणु

		अगर (!of_node_check_flag(node, OF_OVERLAY_FREE_CSET)) अणु
			/* premature refcount of zero, करो not मुक्त memory */
			pr_err("ERROR: memory leak before free overlay changeset,  %pOF\n",
			       node);
			वापस;
		पूर्ण

		/*
		 * If node->properties non-empty then properties were added
		 * to this node either by dअगरferent overlay that has not
		 * yet been हटाओd, or by a non-overlay mechanism.
		 */
		अगर (node->properties)
			pr_err("ERROR: %s(), unexpected properties in %pOF\n",
			       __func__, node);
	पूर्ण

	property_list_मुक्त(node->properties);
	property_list_मुक्त(node->deadprops);
	fwnode_links_purge(of_fwnode_handle(node));

	kमुक्त(node->full_name);
	kमुक्त(node->data);
	kमुक्त(node);
पूर्ण

/**
 * __of_prop_dup - Copy a property dynamically.
 * @prop:	Property to copy
 * @allocflags:	Allocation flags (typically pass GFP_KERNEL)
 *
 * Copy a property by dynamically allocating the memory of both the
 * property काष्ठाure and the property name & contents. The property's
 * flags have the OF_DYNAMIC bit set so that we can dअगरferentiate between
 * dynamically allocated properties and not.
 *
 * Return: The newly allocated property or शून्य on out of memory error.
 */
काष्ठा property *__of_prop_dup(स्थिर काष्ठा property *prop, gfp_t allocflags)
अणु
	काष्ठा property *new;

	new = kzalloc(माप(*new), allocflags);
	अगर (!new)
		वापस शून्य;

	/*
	 * NOTE: There is no check क्रम zero length value.
	 * In हाल of a boolean property, this will allocate a value
	 * of zero bytes. We करो this to work around the use
	 * of of_get_property() calls on boolean values.
	 */
	new->name = kstrdup(prop->name, allocflags);
	new->value = kmemdup(prop->value, prop->length, allocflags);
	new->length = prop->length;
	अगर (!new->name || !new->value)
		जाओ err_मुक्त;

	/* mark the property as dynamic */
	of_property_set_flag(new, OF_DYNAMIC);

	वापस new;

 err_मुक्त:
	kमुक्त(new->name);
	kमुक्त(new->value);
	kमुक्त(new);
	वापस शून्य;
पूर्ण

/**
 * __of_node_dup() - Duplicate or create an empty device node dynamically.
 * @np:		अगर not शून्य, contains properties to be duplicated in new node
 * @full_name:	string value to be duplicated पूर्णांकo new node's full_name field
 *
 * Create a device tree node, optionally duplicating the properties of
 * another node.  The node data are dynamically allocated and all the node
 * flags have the OF_DYNAMIC & OF_DETACHED bits set.
 *
 * Return: The newly allocated node or शून्य on out of memory error.
 */
काष्ठा device_node *__of_node_dup(स्थिर काष्ठा device_node *np,
				  स्थिर अक्षर *full_name)
अणु
	काष्ठा device_node *node;

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस शून्य;
	node->full_name = kstrdup(full_name, GFP_KERNEL);
	अगर (!node->full_name) अणु
		kमुक्त(node);
		वापस शून्य;
	पूर्ण

	of_node_set_flag(node, OF_DYNAMIC);
	of_node_set_flag(node, OF_DETACHED);
	of_node_init(node);

	/* Iterate over and duplicate all properties */
	अगर (np) अणु
		काष्ठा property *pp, *new_pp;
		क्रम_each_property_of_node(np, pp) अणु
			new_pp = __of_prop_dup(pp, GFP_KERNEL);
			अगर (!new_pp)
				जाओ err_prop;
			अगर (__of_add_property(node, new_pp)) अणु
				kमुक्त(new_pp->name);
				kमुक्त(new_pp->value);
				kमुक्त(new_pp);
				जाओ err_prop;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस node;

 err_prop:
	of_node_put(node); /* Frees the node and properties */
	वापस शून्य;
पूर्ण

अटल व्योम __of_changeset_entry_destroy(काष्ठा of_changeset_entry *ce)
अणु
	अगर (ce->action == OF_RECONFIG_ATTACH_NODE &&
	    of_node_check_flag(ce->np, OF_OVERLAY)) अणु
		अगर (kref_पढ़ो(&ce->np->kobj.kref) > 1) अणु
			pr_err("ERROR: memory leak, expected refcount 1 instead of %d, of_node_get()/of_node_put() unbalanced - destroy cset entry: attach overlay node %pOF\n",
			       kref_पढ़ो(&ce->np->kobj.kref), ce->np);
		पूर्ण अन्यथा अणु
			of_node_set_flag(ce->np, OF_OVERLAY_FREE_CSET);
		पूर्ण
	पूर्ण

	of_node_put(ce->np);
	list_del(&ce->node);
	kमुक्त(ce);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम __of_changeset_entry_dump(काष्ठा of_changeset_entry *ce)
अणु
	चयन (ce->action) अणु
	हाल OF_RECONFIG_ADD_PROPERTY:
	हाल OF_RECONFIG_REMOVE_PROPERTY:
	हाल OF_RECONFIG_UPDATE_PROPERTY:
		pr_debug("cset<%p> %-15s %pOF/%s\n", ce, action_names[ce->action],
			ce->np, ce->prop->name);
		अवरोध;
	हाल OF_RECONFIG_ATTACH_NODE:
	हाल OF_RECONFIG_DETACH_NODE:
		pr_debug("cset<%p> %-15s %pOF\n", ce, action_names[ce->action],
			ce->np);
		अवरोध;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __of_changeset_entry_dump(काष्ठा of_changeset_entry *ce)
अणु
	/* empty */
पूर्ण
#पूर्ण_अगर

अटल व्योम __of_changeset_entry_invert(काष्ठा of_changeset_entry *ce,
					  काष्ठा of_changeset_entry *rce)
अणु
	स_नकल(rce, ce, माप(*rce));

	चयन (ce->action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
		rce->action = OF_RECONFIG_DETACH_NODE;
		अवरोध;
	हाल OF_RECONFIG_DETACH_NODE:
		rce->action = OF_RECONFIG_ATTACH_NODE;
		अवरोध;
	हाल OF_RECONFIG_ADD_PROPERTY:
		rce->action = OF_RECONFIG_REMOVE_PROPERTY;
		अवरोध;
	हाल OF_RECONFIG_REMOVE_PROPERTY:
		rce->action = OF_RECONFIG_ADD_PROPERTY;
		अवरोध;
	हाल OF_RECONFIG_UPDATE_PROPERTY:
		rce->old_prop = ce->prop;
		rce->prop = ce->old_prop;
		/* update was used but original property did not exist */
		अगर (!rce->prop) अणु
			rce->action = OF_RECONFIG_REMOVE_PROPERTY;
			rce->prop = ce->prop;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __of_changeset_entry_notअगरy(काष्ठा of_changeset_entry *ce,
		bool revert)
अणु
	काष्ठा of_reconfig_data rd;
	काष्ठा of_changeset_entry ce_inverted;
	पूर्णांक ret = 0;

	अगर (revert) अणु
		__of_changeset_entry_invert(ce, &ce_inverted);
		ce = &ce_inverted;
	पूर्ण

	चयन (ce->action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
	हाल OF_RECONFIG_DETACH_NODE:
		स_रखो(&rd, 0, माप(rd));
		rd.dn = ce->np;
		ret = of_reconfig_notअगरy(ce->action, &rd);
		अवरोध;
	हाल OF_RECONFIG_ADD_PROPERTY:
	हाल OF_RECONFIG_REMOVE_PROPERTY:
	हाल OF_RECONFIG_UPDATE_PROPERTY:
		ret = of_property_notअगरy(ce->action, ce->np, ce->prop, ce->old_prop);
		अवरोध;
	शेष:
		pr_err("invalid devicetree changeset action: %i\n",
			(पूर्णांक)ce->action);
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		pr_err("changeset notifier error @%pOF\n", ce->np);
	वापस ret;
पूर्ण

अटल पूर्णांक __of_changeset_entry_apply(काष्ठा of_changeset_entry *ce)
अणु
	काष्ठा property *old_prop, **propp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	__of_changeset_entry_dump(ce);

	raw_spin_lock_irqsave(&devtree_lock, flags);
	चयन (ce->action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
		__of_attach_node(ce->np);
		अवरोध;
	हाल OF_RECONFIG_DETACH_NODE:
		__of_detach_node(ce->np);
		अवरोध;
	हाल OF_RECONFIG_ADD_PROPERTY:
		/* If the property is in deadprops then it must be हटाओd */
		क्रम (propp = &ce->np->deadprops; *propp; propp = &(*propp)->next) अणु
			अगर (*propp == ce->prop) अणु
				*propp = ce->prop->next;
				ce->prop->next = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण

		ret = __of_add_property(ce->np, ce->prop);
		अगर (ret) अणु
			pr_err("changeset: add_property failed @%pOF/%s\n",
				ce->np,
				ce->prop->name);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल OF_RECONFIG_REMOVE_PROPERTY:
		ret = __of_हटाओ_property(ce->np, ce->prop);
		अगर (ret) अणु
			pr_err("changeset: remove_property failed @%pOF/%s\n",
				ce->np,
				ce->prop->name);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल OF_RECONFIG_UPDATE_PROPERTY:
		/* If the property is in deadprops then it must be हटाओd */
		क्रम (propp = &ce->np->deadprops; *propp; propp = &(*propp)->next) अणु
			अगर (*propp == ce->prop) अणु
				*propp = ce->prop->next;
				ce->prop->next = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण

		ret = __of_update_property(ce->np, ce->prop, &old_prop);
		अगर (ret) अणु
			pr_err("changeset: update_property failed @%pOF/%s\n",
				ce->np,
				ce->prop->name);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	अगर (ret)
		वापस ret;

	चयन (ce->action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
		__of_attach_node_sysfs(ce->np);
		अवरोध;
	हाल OF_RECONFIG_DETACH_NODE:
		__of_detach_node_sysfs(ce->np);
		अवरोध;
	हाल OF_RECONFIG_ADD_PROPERTY:
		/* ignore duplicate names */
		__of_add_property_sysfs(ce->np, ce->prop);
		अवरोध;
	हाल OF_RECONFIG_REMOVE_PROPERTY:
		__of_हटाओ_property_sysfs(ce->np, ce->prop);
		अवरोध;
	हाल OF_RECONFIG_UPDATE_PROPERTY:
		__of_update_property_sysfs(ce->np, ce->prop, ce->old_prop);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __of_changeset_entry_revert(काष्ठा of_changeset_entry *ce)
अणु
	काष्ठा of_changeset_entry ce_inverted;

	__of_changeset_entry_invert(ce, &ce_inverted);
	वापस __of_changeset_entry_apply(&ce_inverted);
पूर्ण

/**
 * of_changeset_init - Initialize a changeset क्रम use
 *
 * @ocs:	changeset poपूर्णांकer
 *
 * Initialize a changeset काष्ठाure
 */
व्योम of_changeset_init(काष्ठा of_changeset *ocs)
अणु
	स_रखो(ocs, 0, माप(*ocs));
	INIT_LIST_HEAD(&ocs->entries);
पूर्ण
EXPORT_SYMBOL_GPL(of_changeset_init);

/**
 * of_changeset_destroy - Destroy a changeset
 *
 * @ocs:	changeset poपूर्णांकer
 *
 * Destroys a changeset. Note that अगर a changeset is applied,
 * its changes to the tree cannot be reverted.
 */
व्योम of_changeset_destroy(काष्ठा of_changeset *ocs)
अणु
	काष्ठा of_changeset_entry *ce, *cen;

	list_क्रम_each_entry_safe_reverse(ce, cen, &ocs->entries, node)
		__of_changeset_entry_destroy(ce);
पूर्ण
EXPORT_SYMBOL_GPL(of_changeset_destroy);

/*
 * Apply the changeset entries in @ocs.
 * If apply fails, an attempt is made to revert the entries that were
 * successfully applied.
 *
 * If multiple revert errors occur then only the final revert error is reported.
 *
 * Returns 0 on success, a negative error value in हाल of an error.
 * If a revert error occurs, it is वापसed in *ret_revert.
 */
पूर्णांक __of_changeset_apply_entries(काष्ठा of_changeset *ocs, पूर्णांक *ret_revert)
अणु
	काष्ठा of_changeset_entry *ce;
	पूर्णांक ret, ret_पंचांगp;

	pr_debug("changeset: applying...\n");
	list_क्रम_each_entry(ce, &ocs->entries, node) अणु
		ret = __of_changeset_entry_apply(ce);
		अगर (ret) अणु
			pr_err("Error applying changeset (%d)\n", ret);
			list_क्रम_each_entry_जारी_reverse(ce, &ocs->entries,
							     node) अणु
				ret_पंचांगp = __of_changeset_entry_revert(ce);
				अगर (ret_पंचांगp)
					*ret_revert = ret_पंचांगp;
			पूर्ण
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Returns 0 on success, a negative error value in हाल of an error.
 *
 * If multiple changeset entry notअगरication errors occur then only the
 * final notअगरication error is reported.
 */
पूर्णांक __of_changeset_apply_notअगरy(काष्ठा of_changeset *ocs)
अणु
	काष्ठा of_changeset_entry *ce;
	पूर्णांक ret = 0, ret_पंचांगp;

	pr_debug("changeset: emitting notifiers.\n");

	/* drop the global lock जबतक emitting notअगरiers */
	mutex_unlock(&of_mutex);
	list_क्रम_each_entry(ce, &ocs->entries, node) अणु
		ret_पंचांगp = __of_changeset_entry_notअगरy(ce, 0);
		अगर (ret_पंचांगp)
			ret = ret_पंचांगp;
	पूर्ण
	mutex_lock(&of_mutex);
	pr_debug("changeset: notifiers sent.\n");

	वापस ret;
पूर्ण

/*
 * Returns 0 on success, a negative error value in हाल of an error.
 *
 * If a changeset entry apply fails, an attempt is made to revert any
 * previous entries in the changeset.  If any of the reverts fails,
 * that failure is not reported.  Thus the state of the device tree
 * is unknown अगर an apply error occurs.
 */
अटल पूर्णांक __of_changeset_apply(काष्ठा of_changeset *ocs)
अणु
	पूर्णांक ret, ret_revert = 0;

	ret = __of_changeset_apply_entries(ocs, &ret_revert);
	अगर (!ret)
		ret = __of_changeset_apply_notअगरy(ocs);

	वापस ret;
पूर्ण

/**
 * of_changeset_apply - Applies a changeset
 *
 * @ocs:	changeset poपूर्णांकer
 *
 * Applies a changeset to the live tree.
 * Any side-effects of live tree state changes are applied here on
 * success, like creation/deकाष्ठाion of devices and side-effects
 * like creation of sysfs properties and directories.
 *
 * Return: 0 on success, a negative error value in हाल of an error.
 * On error the partially applied effects are reverted.
 */
पूर्णांक of_changeset_apply(काष्ठा of_changeset *ocs)
अणु
	पूर्णांक ret;

	mutex_lock(&of_mutex);
	ret = __of_changeset_apply(ocs);
	mutex_unlock(&of_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_changeset_apply);

/*
 * Revert the changeset entries in @ocs.
 * If revert fails, an attempt is made to re-apply the entries that were
 * successfully हटाओd.
 *
 * If multiple re-apply errors occur then only the final apply error is
 * reported.
 *
 * Returns 0 on success, a negative error value in हाल of an error.
 * If an apply error occurs, it is वापसed in *ret_apply.
 */
पूर्णांक __of_changeset_revert_entries(काष्ठा of_changeset *ocs, पूर्णांक *ret_apply)
अणु
	काष्ठा of_changeset_entry *ce;
	पूर्णांक ret, ret_पंचांगp;

	pr_debug("changeset: reverting...\n");
	list_क्रम_each_entry_reverse(ce, &ocs->entries, node) अणु
		ret = __of_changeset_entry_revert(ce);
		अगर (ret) अणु
			pr_err("Error reverting changeset (%d)\n", ret);
			list_क्रम_each_entry_जारी(ce, &ocs->entries, node) अणु
				ret_पंचांगp = __of_changeset_entry_apply(ce);
				अगर (ret_पंचांगp)
					*ret_apply = ret_पंचांगp;
			पूर्ण
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If multiple changeset entry notअगरication errors occur then only the
 * final notअगरication error is reported.
 */
पूर्णांक __of_changeset_revert_notअगरy(काष्ठा of_changeset *ocs)
अणु
	काष्ठा of_changeset_entry *ce;
	पूर्णांक ret = 0, ret_पंचांगp;

	pr_debug("changeset: emitting notifiers.\n");

	/* drop the global lock जबतक emitting notअगरiers */
	mutex_unlock(&of_mutex);
	list_क्रम_each_entry_reverse(ce, &ocs->entries, node) अणु
		ret_पंचांगp = __of_changeset_entry_notअगरy(ce, 1);
		अगर (ret_पंचांगp)
			ret = ret_पंचांगp;
	पूर्ण
	mutex_lock(&of_mutex);
	pr_debug("changeset: notifiers sent.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक __of_changeset_revert(काष्ठा of_changeset *ocs)
अणु
	पूर्णांक ret, ret_reply;

	ret_reply = 0;
	ret = __of_changeset_revert_entries(ocs, &ret_reply);

	अगर (!ret)
		ret = __of_changeset_revert_notअगरy(ocs);

	वापस ret;
पूर्ण

/**
 * of_changeset_revert - Reverts an applied changeset
 *
 * @ocs:	changeset poपूर्णांकer
 *
 * Reverts a changeset वापसing the state of the tree to what it
 * was beक्रमe the application.
 * Any side-effects like creation/deकाष्ठाion of devices and
 * removal of sysfs properties and directories are applied.
 *
 * Return: 0 on success, a negative error value in हाल of an error.
 */
पूर्णांक of_changeset_revert(काष्ठा of_changeset *ocs)
अणु
	पूर्णांक ret;

	mutex_lock(&of_mutex);
	ret = __of_changeset_revert(ocs);
	mutex_unlock(&of_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_changeset_revert);

/**
 * of_changeset_action - Add an action to the tail of the changeset list
 *
 * @ocs:	changeset poपूर्णांकer
 * @action:	action to perक्रमm
 * @np:		Poपूर्णांकer to device node
 * @prop:	Poपूर्णांकer to property
 *
 * On action being one of:
 * + OF_RECONFIG_ATTACH_NODE
 * + OF_RECONFIG_DETACH_NODE,
 * + OF_RECONFIG_ADD_PROPERTY
 * + OF_RECONFIG_REMOVE_PROPERTY,
 * + OF_RECONFIG_UPDATE_PROPERTY
 *
 * Return: 0 on success, a negative error value in हाल of an error.
 */
पूर्णांक of_changeset_action(काष्ठा of_changeset *ocs, अचिन्हित दीर्घ action,
		काष्ठा device_node *np, काष्ठा property *prop)
अणु
	काष्ठा of_changeset_entry *ce;

	ce = kzalloc(माप(*ce), GFP_KERNEL);
	अगर (!ce)
		वापस -ENOMEM;

	/* get a reference to the node */
	ce->action = action;
	ce->np = of_node_get(np);
	ce->prop = prop;

	अगर (action == OF_RECONFIG_UPDATE_PROPERTY && prop)
		ce->old_prop = of_find_property(np, prop->name, शून्य);

	/* add it to the list */
	list_add_tail(&ce->node, &ocs->entries);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_changeset_action);
