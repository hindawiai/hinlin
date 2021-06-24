<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions क्रम working with device tree overlays
 *
 * Copyright (C) 2012 Pantelis Antoniou <panto@antoniou-consulting.com>
 * Copyright (C) 2012 Texas Instruments Inc.
 */

#घोषणा pr_fmt(fmt)	"OF: overlay: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/err.h>
#समावेश <linux/idr.h>

#समावेश "of_private.h"

/**
 * काष्ठा target - info about current target node as recursing through overlay
 * @np:			node where current level of overlay will be applied
 * @in_livetree:	@np is a node in the live devicetree
 *
 * Used in the algorithm to create the portion of a changeset that describes
 * an overlay fragment, which is a devicetree subtree.  Initially @np is a node
 * in the live devicetree where the overlay subtree is targeted to be grafted
 * पूर्णांकo.  When recursing to the next level of the overlay subtree, the target
 * also recurses to the next level of the live devicetree, as दीर्घ as overlay
 * subtree node also exists in the live devicetree.  When a node in the overlay
 * subtree करोes not exist at the same level in the live devicetree, target->np
 * poपूर्णांकs to a newly allocated node, and all subsequent tarमाला_लो in the subtree
 * will be newly allocated nodes.
 */
काष्ठा target अणु
	काष्ठा device_node *np;
	bool in_livetree;
पूर्ण;

/**
 * काष्ठा fragment - info about fragment nodes in overlay expanded device tree
 * @target:	target of the overlay operation
 * @overlay:	poपूर्णांकer to the __overlay__ node
 */
काष्ठा fragment अणु
	काष्ठा device_node *overlay;
	काष्ठा device_node *target;
पूर्ण;

/**
 * काष्ठा overlay_changeset
 * @id:			changeset identअगरier
 * @ovcs_list:		list on which we are located
 * @fdt:		base of memory allocated to hold aligned FDT that was unflattened to create @overlay_tree
 * @overlay_tree:	expanded device tree that contains the fragment nodes
 * @count:		count of fragment काष्ठाures
 * @fragments:		fragment nodes in the overlay expanded device tree
 * @symbols_fragment:	last element of @fragments[] is the  __symbols__ node
 * @cset:		changeset to apply fragments to live device tree
 */
काष्ठा overlay_changeset अणु
	पूर्णांक id;
	काष्ठा list_head ovcs_list;
	स्थिर व्योम *fdt;
	काष्ठा device_node *overlay_tree;
	पूर्णांक count;
	काष्ठा fragment *fragments;
	bool symbols_fragment;
	काष्ठा of_changeset cset;
पूर्ण;

/* flags are sticky - once set, करो not reset */
अटल पूर्णांक devicetree_state_flags;
#घोषणा DTSF_APPLY_FAIL		0x01
#घोषणा DTSF_REVERT_FAIL	0x02

/*
 * If a changeset apply or revert encounters an error, an attempt will
 * be made to unकरो partial changes, but may fail.  If the unकरो fails
 * we करो not know the state of the devicetree.
 */
अटल पूर्णांक devicetree_corrupt(व्योम)
अणु
	वापस devicetree_state_flags &
		(DTSF_APPLY_FAIL | DTSF_REVERT_FAIL);
पूर्ण

अटल पूर्णांक build_changeset_next_level(काष्ठा overlay_changeset *ovcs,
		काष्ठा target *target, स्थिर काष्ठा device_node *overlay_node);

/*
 * of_resolve_phandles() finds the largest phandle in the live tree.
 * of_overlay_apply() may add a larger phandle to the live tree.
 * Do not allow race between two overlays being applied simultaneously:
 *    mutex_lock(&of_overlay_phandle_mutex)
 *    of_resolve_phandles()
 *    of_overlay_apply()
 *    mutex_unlock(&of_overlay_phandle_mutex)
 */
अटल DEFINE_MUTEX(of_overlay_phandle_mutex);

व्योम of_overlay_mutex_lock(व्योम)
अणु
	mutex_lock(&of_overlay_phandle_mutex);
पूर्ण

व्योम of_overlay_mutex_unlock(व्योम)
अणु
	mutex_unlock(&of_overlay_phandle_mutex);
पूर्ण


अटल LIST_HEAD(ovcs_list);
अटल DEFINE_IDR(ovcs_idr);

अटल BLOCKING_NOTIFIER_HEAD(overlay_notअगरy_chain);

/**
 * of_overlay_notअगरier_रेजिस्टर() - Register notअगरier क्रम overlay operations
 * @nb:		Notअगरier block to रेजिस्टर
 *
 * Register क्रम notअगरication on overlay operations on device tree nodes. The
 * reported actions definied by @of_reconfig_change. The notअगरier callback
 * furthermore receives a poपूर्णांकer to the affected device tree node.
 *
 * Note that a notअगरier callback is not supposed to store poपूर्णांकers to a device
 * tree node or its content beyond @OF_OVERLAY_POST_REMOVE corresponding to the
 * respective node it received.
 */
पूर्णांक of_overlay_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&overlay_notअगरy_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(of_overlay_notअगरier_रेजिस्टर);

/**
 * of_overlay_notअगरier_unरेजिस्टर() - Unरेजिस्टर notअगरier क्रम overlay operations
 * @nb:		Notअगरier block to unरेजिस्टर
 */
पूर्णांक of_overlay_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&overlay_notअगरy_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(of_overlay_notअगरier_unरेजिस्टर);

अटल अक्षर *of_overlay_action_name[] = अणु
	"pre-apply",
	"post-apply",
	"pre-remove",
	"post-remove",
पूर्ण;

अटल पूर्णांक overlay_notअगरy(काष्ठा overlay_changeset *ovcs,
		क्रमागत of_overlay_notअगरy_action action)
अणु
	काष्ठा of_overlay_notअगरy_data nd;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ovcs->count; i++) अणु
		काष्ठा fragment *fragment = &ovcs->fragments[i];

		nd.target = fragment->target;
		nd.overlay = fragment->overlay;

		ret = blocking_notअगरier_call_chain(&overlay_notअगरy_chain,
						   action, &nd);
		अगर (ret == NOTIFY_OK || ret == NOTIFY_STOP)
			वापस 0;
		अगर (ret) अणु
			ret = notअगरier_to_त्रुटि_सं(ret);
			pr_err("overlay changeset %s notifier error %d, target: %pOF\n",
			       of_overlay_action_name[action], ret, nd.target);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The values of properties in the "/__symbols__" node are paths in
 * the ovcs->overlay_tree.  When duplicating the properties, the paths
 * need to be adjusted to be the correct path क्रम the live device tree.
 *
 * The paths refer to a node in the subtree of a fragment node's "__overlay__"
 * node, क्रम example "/fragment@0/__overlay__/symbol_path_tail",
 * where symbol_path_tail can be a single node or it may be a multi-node path.
 *
 * The duplicated property value will be modअगरied by replacing the
 * "/fragment_name/__overlay/" portion of the value  with the target
 * path from the fragment node.
 */
अटल काष्ठा property *dup_and_fixup_symbol_prop(
		काष्ठा overlay_changeset *ovcs, स्थिर काष्ठा property *prop)
अणु
	काष्ठा fragment *fragment;
	काष्ठा property *new_prop;
	काष्ठा device_node *fragment_node;
	काष्ठा device_node *overlay_node;
	स्थिर अक्षर *path;
	स्थिर अक्षर *path_tail;
	स्थिर अक्षर *target_path;
	पूर्णांक k;
	पूर्णांक overlay_name_len;
	पूर्णांक path_len;
	पूर्णांक path_tail_len;
	पूर्णांक target_path_len;

	अगर (!prop->value)
		वापस शून्य;
	अगर (strnlen(prop->value, prop->length) >= prop->length)
		वापस शून्य;
	path = prop->value;
	path_len = म_माप(path);

	अगर (path_len < 1)
		वापस शून्य;
	fragment_node = __of_find_node_by_path(ovcs->overlay_tree, path + 1);
	overlay_node = __of_find_node_by_path(fragment_node, "__overlay__/");
	of_node_put(fragment_node);
	of_node_put(overlay_node);

	क्रम (k = 0; k < ovcs->count; k++) अणु
		fragment = &ovcs->fragments[k];
		अगर (fragment->overlay == overlay_node)
			अवरोध;
	पूर्ण
	अगर (k >= ovcs->count)
		वापस शून्य;

	overlay_name_len = snम_लिखो(शून्य, 0, "%pOF", fragment->overlay);

	अगर (overlay_name_len > path_len)
		वापस शून्य;
	path_tail = path + overlay_name_len;
	path_tail_len = म_माप(path_tail);

	target_path = kaप्र_लिखो(GFP_KERNEL, "%pOF", fragment->target);
	अगर (!target_path)
		वापस शून्य;
	target_path_len = म_माप(target_path);

	new_prop = kzalloc(माप(*new_prop), GFP_KERNEL);
	अगर (!new_prop)
		जाओ err_मुक्त_target_path;

	new_prop->name = kstrdup(prop->name, GFP_KERNEL);
	new_prop->length = target_path_len + path_tail_len + 1;
	new_prop->value = kzalloc(new_prop->length, GFP_KERNEL);
	अगर (!new_prop->name || !new_prop->value)
		जाओ err_मुक्त_new_prop;

	म_नकल(new_prop->value, target_path);
	म_नकल(new_prop->value + target_path_len, path_tail);

	of_property_set_flag(new_prop, OF_DYNAMIC);

	kमुक्त(target_path);

	वापस new_prop;

err_मुक्त_new_prop:
	kमुक्त(new_prop->name);
	kमुक्त(new_prop->value);
	kमुक्त(new_prop);
err_मुक्त_target_path:
	kमुक्त(target_path);

	वापस शून्य;
पूर्ण

/**
 * add_changeset_property() - add @overlay_prop to overlay changeset
 * @ovcs:		overlay changeset
 * @target:		where @overlay_prop will be placed
 * @overlay_prop:	property to add or update, from overlay tree
 * @is_symbols_prop:	1 अगर @overlay_prop is from node "/__symbols__"
 *
 * If @overlay_prop करोes not alपढ़ोy exist in live devicetree, add changeset
 * entry to add @overlay_prop in @target, अन्यथा add changeset entry to update
 * value of @overlay_prop.
 *
 * @target may be either in the live devicetree or in a new subtree that
 * is contained in the changeset.
 *
 * Some special properties are not added or updated (no error वापसed):
 * "name", "phandle", "linux,phandle".
 *
 * Properties "#address-cells" and "#size-cells" are not updated अगर they
 * are alपढ़ोy in the live tree, but अगर present in the live tree, the values
 * in the overlay must match the values in the live tree.
 *
 * Update of property in symbols node is not allowed.
 *
 * Return: 0 on success, -ENOMEM अगर memory allocation failure, or -EINVAL अगर
 * invalid @overlay.
 */
अटल पूर्णांक add_changeset_property(काष्ठा overlay_changeset *ovcs,
		काष्ठा target *target, काष्ठा property *overlay_prop,
		bool is_symbols_prop)
अणु
	काष्ठा property *new_prop = शून्य, *prop;
	पूर्णांक ret = 0;

	अगर (target->in_livetree)
		अगर (!of_prop_cmp(overlay_prop->name, "name") ||
		    !of_prop_cmp(overlay_prop->name, "phandle") ||
		    !of_prop_cmp(overlay_prop->name, "linux,phandle"))
			वापस 0;

	अगर (target->in_livetree)
		prop = of_find_property(target->np, overlay_prop->name, शून्य);
	अन्यथा
		prop = शून्य;

	अगर (prop) अणु
		अगर (!of_prop_cmp(prop->name, "#address-cells")) अणु
			अगर (!of_prop_val_eq(prop, overlay_prop)) अणु
				pr_err("ERROR: changing value of #address-cells is not allowed in %pOF\n",
				       target->np);
				ret = -EINVAL;
			पूर्ण
			वापस ret;

		पूर्ण अन्यथा अगर (!of_prop_cmp(prop->name, "#size-cells")) अणु
			अगर (!of_prop_val_eq(prop, overlay_prop)) अणु
				pr_err("ERROR: changing value of #size-cells is not allowed in %pOF\n",
				       target->np);
				ret = -EINVAL;
			पूर्ण
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (is_symbols_prop) अणु
		अगर (prop)
			वापस -EINVAL;
		new_prop = dup_and_fixup_symbol_prop(ovcs, overlay_prop);
	पूर्ण अन्यथा अणु
		new_prop = __of_prop_dup(overlay_prop, GFP_KERNEL);
	पूर्ण

	अगर (!new_prop)
		वापस -ENOMEM;

	अगर (!prop) अणु
		अगर (!target->in_livetree) अणु
			new_prop->next = target->np->deadprops;
			target->np->deadprops = new_prop;
		पूर्ण
		ret = of_changeset_add_property(&ovcs->cset, target->np,
						new_prop);
	पूर्ण अन्यथा अणु
		ret = of_changeset_update_property(&ovcs->cset, target->np,
						   new_prop);
	पूर्ण

	अगर (!of_node_check_flag(target->np, OF_OVERLAY))
		pr_err("WARNING: memory leak will occur if overlay removed, property: %pOF/%s\n",
		       target->np, new_prop->name);

	अगर (ret) अणु
		kमुक्त(new_prop->name);
		kमुक्त(new_prop->value);
		kमुक्त(new_prop);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * add_changeset_node() - add @node (and children) to overlay changeset
 * @ovcs:	overlay changeset
 * @target:	where @node will be placed in live tree or changeset
 * @node:	node from within overlay device tree fragment
 *
 * If @node करोes not alपढ़ोy exist in @target, add changeset entry
 * to add @node in @target.
 *
 * If @node alपढ़ोy exists in @target, and the existing node has
 * a phandle, the overlay node is not allowed to have a phandle.
 *
 * If @node has child nodes, add the children recursively via
 * build_changeset_next_level().
 *
 * NOTE_1: A live devicetree created from a flattened device tree (FDT) will
 *       not contain the full path in node->full_name.  Thus an overlay
 *       created from an FDT also will not contain the full path in
 *       node->full_name.  However, a live devicetree created from Open
 *       Firmware may have the full path in node->full_name.
 *
 *       add_changeset_node() follows the FDT convention and करोes not include
 *       the full path in node->full_name.  Even though it expects the overlay
 *       to not contain the full path, it uses kbasename() to हटाओ the
 *       full path should it exist.  It also uses kbasename() in comparisons
 *       to nodes in the live devicetree so that it can apply an overlay to
 *       a live devicetree created from Open Firmware.
 *
 * NOTE_2: Multiple mods of created nodes not supported.
 *
 * Return: 0 on success, -ENOMEM अगर memory allocation failure, or -EINVAL अगर
 * invalid @overlay.
 */
अटल पूर्णांक add_changeset_node(काष्ठा overlay_changeset *ovcs,
		काष्ठा target *target, काष्ठा device_node *node)
अणु
	स्थिर अक्षर *node_kbasename;
	स्थिर __be32 *phandle;
	काष्ठा device_node *tchild;
	काष्ठा target target_child;
	पूर्णांक ret = 0, size;

	node_kbasename = kbasename(node->full_name);

	क्रम_each_child_of_node(target->np, tchild)
		अगर (!of_node_cmp(node_kbasename, kbasename(tchild->full_name)))
			अवरोध;

	अगर (!tchild) अणु
		tchild = __of_node_dup(शून्य, node_kbasename);
		अगर (!tchild)
			वापस -ENOMEM;

		tchild->parent = target->np;
		tchild->name = __of_get_property(node, "name", शून्य);

		अगर (!tchild->name)
			tchild->name = "<NULL>";

		/* ignore obsolete "linux,phandle" */
		phandle = __of_get_property(node, "phandle", &size);
		अगर (phandle && (size == 4))
			tchild->phandle = be32_to_cpup(phandle);

		of_node_set_flag(tchild, OF_OVERLAY);

		ret = of_changeset_attach_node(&ovcs->cset, tchild);
		अगर (ret)
			वापस ret;

		target_child.np = tchild;
		target_child.in_livetree = false;

		ret = build_changeset_next_level(ovcs, &target_child, node);
		of_node_put(tchild);
		वापस ret;
	पूर्ण

	अगर (node->phandle && tchild->phandle) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		target_child.np = tchild;
		target_child.in_livetree = target->in_livetree;
		ret = build_changeset_next_level(ovcs, &target_child, node);
	पूर्ण
	of_node_put(tchild);

	वापस ret;
पूर्ण

/**
 * build_changeset_next_level() - add level of overlay changeset
 * @ovcs:		overlay changeset
 * @target:		where to place @overlay_node in live tree
 * @overlay_node:	node from within an overlay device tree fragment
 *
 * Add the properties (अगर any) and nodes (अगर any) from @overlay_node to the
 * @ovcs->cset changeset.  If an added node has child nodes, they will
 * be added recursively.
 *
 * Do not allow symbols node to have any children.
 *
 * Return: 0 on success, -ENOMEM अगर memory allocation failure, or -EINVAL अगर
 * invalid @overlay_node.
 */
अटल पूर्णांक build_changeset_next_level(काष्ठा overlay_changeset *ovcs,
		काष्ठा target *target, स्थिर काष्ठा device_node *overlay_node)
अणु
	काष्ठा device_node *child;
	काष्ठा property *prop;
	पूर्णांक ret;

	क्रम_each_property_of_node(overlay_node, prop) अणु
		ret = add_changeset_property(ovcs, target, prop, 0);
		अगर (ret) अणु
			pr_debug("Failed to apply prop @%pOF/%s, err=%d\n",
				 target->np, prop->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम_each_child_of_node(overlay_node, child) अणु
		ret = add_changeset_node(ovcs, target, child);
		अगर (ret) अणु
			pr_debug("Failed to apply node @%pOF/%pOFn, err=%d\n",
				 target->np, child, ret);
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Add the properties from __overlay__ node to the @ovcs->cset changeset.
 */
अटल पूर्णांक build_changeset_symbols_node(काष्ठा overlay_changeset *ovcs,
		काष्ठा target *target,
		स्थिर काष्ठा device_node *overlay_symbols_node)
अणु
	काष्ठा property *prop;
	पूर्णांक ret;

	क्रम_each_property_of_node(overlay_symbols_node, prop) अणु
		ret = add_changeset_property(ovcs, target, prop, 1);
		अगर (ret) अणु
			pr_debug("Failed to apply symbols prop @%pOF/%s, err=%d\n",
				 target->np, prop->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक find_dup_cset_node_entry(काष्ठा overlay_changeset *ovcs,
		काष्ठा of_changeset_entry *ce_1)
अणु
	काष्ठा of_changeset_entry *ce_2;
	अक्षर *fn_1, *fn_2;
	पूर्णांक node_path_match;

	अगर (ce_1->action != OF_RECONFIG_ATTACH_NODE &&
	    ce_1->action != OF_RECONFIG_DETACH_NODE)
		वापस 0;

	ce_2 = ce_1;
	list_क्रम_each_entry_जारी(ce_2, &ovcs->cset.entries, node) अणु
		अगर ((ce_2->action != OF_RECONFIG_ATTACH_NODE &&
		     ce_2->action != OF_RECONFIG_DETACH_NODE) ||
		    of_node_cmp(ce_1->np->full_name, ce_2->np->full_name))
			जारी;

		fn_1 = kaप्र_लिखो(GFP_KERNEL, "%pOF", ce_1->np);
		fn_2 = kaप्र_लिखो(GFP_KERNEL, "%pOF", ce_2->np);
		node_path_match = !म_भेद(fn_1, fn_2);
		kमुक्त(fn_1);
		kमुक्त(fn_2);
		अगर (node_path_match) अणु
			pr_err("ERROR: multiple fragments add and/or delete node %pOF\n",
			       ce_1->np);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक find_dup_cset_prop(काष्ठा overlay_changeset *ovcs,
		काष्ठा of_changeset_entry *ce_1)
अणु
	काष्ठा of_changeset_entry *ce_2;
	अक्षर *fn_1, *fn_2;
	पूर्णांक node_path_match;

	अगर (ce_1->action != OF_RECONFIG_ADD_PROPERTY &&
	    ce_1->action != OF_RECONFIG_REMOVE_PROPERTY &&
	    ce_1->action != OF_RECONFIG_UPDATE_PROPERTY)
		वापस 0;

	ce_2 = ce_1;
	list_क्रम_each_entry_जारी(ce_2, &ovcs->cset.entries, node) अणु
		अगर ((ce_2->action != OF_RECONFIG_ADD_PROPERTY &&
		     ce_2->action != OF_RECONFIG_REMOVE_PROPERTY &&
		     ce_2->action != OF_RECONFIG_UPDATE_PROPERTY) ||
		    of_node_cmp(ce_1->np->full_name, ce_2->np->full_name))
			जारी;

		fn_1 = kaप्र_लिखो(GFP_KERNEL, "%pOF", ce_1->np);
		fn_2 = kaप्र_लिखो(GFP_KERNEL, "%pOF", ce_2->np);
		node_path_match = !म_भेद(fn_1, fn_2);
		kमुक्त(fn_1);
		kमुक्त(fn_2);
		अगर (node_path_match &&
		    !of_prop_cmp(ce_1->prop->name, ce_2->prop->name)) अणु
			pr_err("ERROR: multiple fragments add, update, and/or delete property %pOF/%s\n",
			       ce_1->np, ce_1->prop->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * changeset_dup_entry_check() - check क्रम duplicate entries
 * @ovcs:	Overlay changeset
 *
 * Check changeset @ovcs->cset क्रम multiple अणुadd or deleteपूर्ण node entries क्रम
 * the same node or duplicate अणुadd, delete, or updateपूर्ण properties entries
 * क्रम the same property.
 *
 * Return: 0 on success, or -EINVAL अगर duplicate changeset entry found.
 */
अटल पूर्णांक changeset_dup_entry_check(काष्ठा overlay_changeset *ovcs)
अणु
	काष्ठा of_changeset_entry *ce_1;
	पूर्णांक dup_entry = 0;

	list_क्रम_each_entry(ce_1, &ovcs->cset.entries, node) अणु
		dup_entry |= find_dup_cset_node_entry(ovcs, ce_1);
		dup_entry |= find_dup_cset_prop(ovcs, ce_1);
	पूर्ण

	वापस dup_entry ? -EINVAL : 0;
पूर्ण

/**
 * build_changeset() - populate overlay changeset in @ovcs from @ovcs->fragments
 * @ovcs:	Overlay changeset
 *
 * Create changeset @ovcs->cset to contain the nodes and properties of the
 * overlay device tree fragments in @ovcs->fragments[].  If an error occurs,
 * any portions of the changeset that were successfully created will reमुख्य
 * in @ovcs->cset.
 *
 * Return: 0 on success, -ENOMEM अगर memory allocation failure, or -EINVAL अगर
 * invalid overlay in @ovcs->fragments[].
 */
अटल पूर्णांक build_changeset(काष्ठा overlay_changeset *ovcs)
अणु
	काष्ठा fragment *fragment;
	काष्ठा target target;
	पूर्णांक fragments_count, i, ret;

	/*
	 * अगर there is a symbols fragment in ovcs->fragments[i] it is
	 * the final element in the array
	 */
	अगर (ovcs->symbols_fragment)
		fragments_count = ovcs->count - 1;
	अन्यथा
		fragments_count = ovcs->count;

	क्रम (i = 0; i < fragments_count; i++) अणु
		fragment = &ovcs->fragments[i];

		target.np = fragment->target;
		target.in_livetree = true;
		ret = build_changeset_next_level(ovcs, &target,
						 fragment->overlay);
		अगर (ret) अणु
			pr_debug("fragment apply failed '%pOF'\n",
				 fragment->target);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (ovcs->symbols_fragment) अणु
		fragment = &ovcs->fragments[ovcs->count - 1];

		target.np = fragment->target;
		target.in_livetree = true;
		ret = build_changeset_symbols_node(ovcs, &target,
						   fragment->overlay);
		अगर (ret) अणु
			pr_debug("symbols fragment apply failed '%pOF'\n",
				 fragment->target);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस changeset_dup_entry_check(ovcs);
पूर्ण

/*
 * Find the target node using a number of dअगरferent strategies
 * in order of preference:
 *
 * 1) "target" property containing the phandle of the target
 * 2) "target-path" property containing the path of the target
 */
अटल काष्ठा device_node *find_target(काष्ठा device_node *info_node)
अणु
	काष्ठा device_node *node;
	स्थिर अक्षर *path;
	u32 val;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(info_node, "target", &val);
	अगर (!ret) अणु
		node = of_find_node_by_phandle(val);
		अगर (!node)
			pr_err("find target, node: %pOF, phandle 0x%x not found\n",
			       info_node, val);
		वापस node;
	पूर्ण

	ret = of_property_पढ़ो_string(info_node, "target-path", &path);
	अगर (!ret) अणु
		node =  of_find_node_by_path(path);
		अगर (!node)
			pr_err("find target, node: %pOF, path '%s' not found\n",
			       info_node, path);
		वापस node;
	पूर्ण

	pr_err("find target, node: %pOF, no target property\n", info_node);

	वापस शून्य;
पूर्ण

/**
 * init_overlay_changeset() - initialize overlay changeset from overlay tree
 * @ovcs:	Overlay changeset to build
 * @fdt:	base of memory allocated to hold aligned FDT that was unflattened to create @tree
 * @tree:	Contains the overlay fragments and overlay fixup nodes
 *
 * Initialize @ovcs.  Populate @ovcs->fragments with node inक्रमmation from
 * the top level of @tree.  The relevant top level nodes are the fragment
 * nodes and the __symbols__ node.  Any other top level node will be ignored.
 *
 * Return: 0 on success, -ENOMEM अगर memory allocation failure, -EINVAL अगर error
 * detected in @tree, or -ENOSPC अगर idr_alloc() error.
 */
अटल पूर्णांक init_overlay_changeset(काष्ठा overlay_changeset *ovcs,
		स्थिर व्योम *fdt, काष्ठा device_node *tree)
अणु
	काष्ठा device_node *node, *overlay_node;
	काष्ठा fragment *fragment;
	काष्ठा fragment *fragments;
	पूर्णांक cnt, id, ret;

	/*
	 * Warn क्रम some issues.  Can not वापस -EINVAL क्रम these until
	 * of_unittest_apply_overlay() is fixed to pass these checks.
	 */
	अगर (!of_node_check_flag(tree, OF_DYNAMIC))
		pr_debug("%s() tree is not dynamic\n", __func__);

	अगर (!of_node_check_flag(tree, OF_DETACHED))
		pr_debug("%s() tree is not detached\n", __func__);

	अगर (!of_node_is_root(tree))
		pr_debug("%s() tree is not root\n", __func__);

	ovcs->overlay_tree = tree;
	ovcs->fdt = fdt;

	INIT_LIST_HEAD(&ovcs->ovcs_list);

	of_changeset_init(&ovcs->cset);

	id = idr_alloc(&ovcs_idr, ovcs, 1, 0, GFP_KERNEL);
	अगर (id <= 0)
		वापस id;

	cnt = 0;

	/* fragment nodes */
	क्रम_each_child_of_node(tree, node) अणु
		overlay_node = of_get_child_by_name(node, "__overlay__");
		अगर (overlay_node) अणु
			cnt++;
			of_node_put(overlay_node);
		पूर्ण
	पूर्ण

	node = of_get_child_by_name(tree, "__symbols__");
	अगर (node) अणु
		cnt++;
		of_node_put(node);
	पूर्ण

	fragments = kसुस्मृति(cnt, माप(*fragments), GFP_KERNEL);
	अगर (!fragments) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_idr;
	पूर्ण

	cnt = 0;
	क्रम_each_child_of_node(tree, node) अणु
		overlay_node = of_get_child_by_name(node, "__overlay__");
		अगर (!overlay_node)
			जारी;

		fragment = &fragments[cnt];
		fragment->overlay = overlay_node;
		fragment->target = find_target(node);
		अगर (!fragment->target) अणु
			of_node_put(fragment->overlay);
			ret = -EINVAL;
			of_node_put(node);
			जाओ err_मुक्त_fragments;
		पूर्ण

		cnt++;
	पूर्ण

	/*
	 * अगर there is a symbols fragment in ovcs->fragments[i] it is
	 * the final element in the array
	 */
	node = of_get_child_by_name(tree, "__symbols__");
	अगर (node) अणु
		ovcs->symbols_fragment = 1;
		fragment = &fragments[cnt];
		fragment->overlay = node;
		fragment->target = of_find_node_by_path("/__symbols__");

		अगर (!fragment->target) अणु
			pr_err("symbols in overlay, but not in live tree\n");
			ret = -EINVAL;
			जाओ err_मुक्त_fragments;
		पूर्ण

		cnt++;
	पूर्ण

	अगर (!cnt) अणु
		pr_err("no fragments or symbols in overlay\n");
		ret = -EINVAL;
		जाओ err_मुक्त_fragments;
	पूर्ण

	ovcs->id = id;
	ovcs->count = cnt;
	ovcs->fragments = fragments;

	वापस 0;

err_मुक्त_fragments:
	kमुक्त(fragments);
err_मुक्त_idr:
	idr_हटाओ(&ovcs_idr, id);

	pr_err("%s() failed, ret = %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_overlay_changeset(काष्ठा overlay_changeset *ovcs)
अणु
	पूर्णांक i;

	अगर (ovcs->cset.entries.next)
		of_changeset_destroy(&ovcs->cset);

	अगर (ovcs->id)
		idr_हटाओ(&ovcs_idr, ovcs->id);

	क्रम (i = 0; i < ovcs->count; i++) अणु
		of_node_put(ovcs->fragments[i].target);
		of_node_put(ovcs->fragments[i].overlay);
	पूर्ण
	kमुक्त(ovcs->fragments);
	/*
	 * There should be no live poपूर्णांकers पूर्णांकo ovcs->overlay_tree and
	 * ovcs->fdt due to the policy that overlay notअगरiers are not allowed
	 * to retain poपूर्णांकers पूर्णांकo the overlay devicetree.
	 */
	kमुक्त(ovcs->overlay_tree);
	kमुक्त(ovcs->fdt);
	kमुक्त(ovcs);
पूर्ण

/*
 * पूर्णांकernal करोcumentation
 *
 * of_overlay_apply() - Create and apply an overlay changeset
 * @fdt:	base of memory allocated to hold the aligned FDT
 * @tree:	Expanded overlay device tree
 * @ovcs_id:	Poपूर्णांकer to overlay changeset id
 *
 * Creates and applies an overlay changeset.
 *
 * If an error occurs in a pre-apply notअगरier, then no changes are made
 * to the device tree.
 *

 * A non-zero वापस value will not have created the changeset अगर error is from:
 *   - parameter checks
 *   - building the changeset
 *   - overlay changeset pre-apply notअगरier
 *
 * If an error is वापसed by an overlay changeset pre-apply notअगरier
 * then no further overlay changeset pre-apply notअगरier will be called.
 *
 * A non-zero वापस value will have created the changeset अगर error is from:
 *   - overlay changeset entry notअगरier
 *   - overlay changeset post-apply notअगरier
 *
 * If an error is वापसed by an overlay changeset post-apply notअगरier
 * then no further overlay changeset post-apply notअगरier will be called.
 *
 * If more than one notअगरier वापसs an error, then the last notअगरier
 * error to occur is वापसed.
 *
 * If an error occurred जबतक applying the overlay changeset, then an
 * attempt is made to revert any changes that were made to the
 * device tree.  If there were any errors during the revert attempt
 * then the state of the device tree can not be determined, and any
 * following attempt to apply or हटाओ an overlay changeset will be
 * refused.
 *
 * Returns 0 on success, or a negative error number.  Overlay changeset
 * id is वापसed to *ovcs_id.
 */

अटल पूर्णांक of_overlay_apply(स्थिर व्योम *fdt, काष्ठा device_node *tree,
		पूर्णांक *ovcs_id)
अणु
	काष्ठा overlay_changeset *ovcs;
	पूर्णांक ret = 0, ret_revert, ret_पंचांगp;

	/*
	 * As of this poपूर्णांक, fdt and tree beदीर्घ to the overlay changeset.
	 * overlay changeset code is responsible क्रम मुक्तing them.
	 */

	अगर (devicetree_corrupt()) अणु
		pr_err("devicetree state suspect, refuse to apply overlay\n");
		kमुक्त(fdt);
		kमुक्त(tree);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ovcs = kzalloc(माप(*ovcs), GFP_KERNEL);
	अगर (!ovcs) अणु
		kमुक्त(fdt);
		kमुक्त(tree);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	of_overlay_mutex_lock();
	mutex_lock(&of_mutex);

	ret = of_resolve_phandles(tree);
	अगर (ret)
		जाओ err_मुक्त_tree;

	ret = init_overlay_changeset(ovcs, fdt, tree);
	अगर (ret)
		जाओ err_मुक्त_tree;

	/*
	 * after overlay_notअगरy(), ovcs->overlay_tree related poपूर्णांकers may have
	 * leaked to drivers, so can not kमुक्त() tree, aka ovcs->overlay_tree;
	 * and can not मुक्त memory containing aligned fdt.  The aligned fdt
	 * is contained within the memory at ovcs->fdt, possibly at an offset
	 * from ovcs->fdt.
	 */
	ret = overlay_notअगरy(ovcs, OF_OVERLAY_PRE_APPLY);
	अगर (ret) अणु
		pr_err("overlay changeset pre-apply notify error %d\n", ret);
		जाओ err_मुक्त_overlay_changeset;
	पूर्ण

	ret = build_changeset(ovcs);
	अगर (ret)
		जाओ err_मुक्त_overlay_changeset;

	ret_revert = 0;
	ret = __of_changeset_apply_entries(&ovcs->cset, &ret_revert);
	अगर (ret) अणु
		अगर (ret_revert) अणु
			pr_debug("overlay changeset revert error %d\n",
				 ret_revert);
			devicetree_state_flags |= DTSF_APPLY_FAIL;
		पूर्ण
		जाओ err_मुक्त_overlay_changeset;
	पूर्ण

	ret = __of_changeset_apply_notअगरy(&ovcs->cset);
	अगर (ret)
		pr_err("overlay apply changeset entry notify error %d\n", ret);
	/* notअगरy failure is not fatal, जारी */

	list_add_tail(&ovcs->ovcs_list, &ovcs_list);
	*ovcs_id = ovcs->id;

	ret_पंचांगp = overlay_notअगरy(ovcs, OF_OVERLAY_POST_APPLY);
	अगर (ret_पंचांगp) अणु
		pr_err("overlay changeset post-apply notify error %d\n",
		       ret_पंचांगp);
		अगर (!ret)
			ret = ret_पंचांगp;
	पूर्ण

	जाओ out_unlock;

err_मुक्त_tree:
	kमुक्त(fdt);
	kमुक्त(tree);

err_मुक्त_overlay_changeset:
	मुक्त_overlay_changeset(ovcs);

out_unlock:
	mutex_unlock(&of_mutex);
	of_overlay_mutex_unlock();

out:
	pr_debug("%s() err=%d\n", __func__, ret);

	वापस ret;
पूर्ण

पूर्णांक of_overlay_fdt_apply(स्थिर व्योम *overlay_fdt, u32 overlay_fdt_size,
			 पूर्णांक *ovcs_id)
अणु
	व्योम *new_fdt;
	व्योम *new_fdt_align;
	पूर्णांक ret;
	u32 size;
	काष्ठा device_node *overlay_root = शून्य;

	*ovcs_id = 0;

	अगर (overlay_fdt_size < माप(काष्ठा fdt_header) ||
	    fdt_check_header(overlay_fdt)) अणु
		pr_err("Invalid overlay_fdt header\n");
		वापस -EINVAL;
	पूर्ण

	size = fdt_totalsize(overlay_fdt);
	अगर (overlay_fdt_size < size)
		वापस -EINVAL;

	/*
	 * Must create permanent copy of FDT because of_fdt_unflatten_tree()
	 * will create poपूर्णांकers to the passed in FDT in the unflattened tree.
	 */
	new_fdt = kदो_स्मृति(size + FDT_ALIGN_SIZE, GFP_KERNEL);
	अगर (!new_fdt)
		वापस -ENOMEM;

	new_fdt_align = PTR_ALIGN(new_fdt, FDT_ALIGN_SIZE);
	स_नकल(new_fdt_align, overlay_fdt, size);

	of_fdt_unflatten_tree(new_fdt_align, शून्य, &overlay_root);
	अगर (!overlay_root) अणु
		pr_err("unable to unflatten overlay_fdt\n");
		ret = -EINVAL;
		जाओ out_मुक्त_new_fdt;
	पूर्ण

	ret = of_overlay_apply(new_fdt, overlay_root, ovcs_id);
	अगर (ret < 0) अणु
		/*
		 * new_fdt and overlay_root now beदीर्घ to the overlay
		 * changeset.
		 * overlay changeset code is responsible क्रम मुक्तing them.
		 */
		जाओ out;
	पूर्ण

	वापस 0;


out_मुक्त_new_fdt:
	kमुक्त(new_fdt);

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_overlay_fdt_apply);

/*
 * Find @np in @tree.
 *
 * Returns 1 अगर @np is @tree or is contained in @tree, अन्यथा 0
 */
अटल पूर्णांक find_node(काष्ठा device_node *tree, काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;

	अगर (tree == np)
		वापस 1;

	क्रम_each_child_of_node(tree, child) अणु
		अगर (find_node(child, np)) अणु
			of_node_put(child);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Is @हटाओ_ce_node a child of, a parent of, or the same as any
 * node in an overlay changeset more topmost than @हटाओ_ovcs?
 *
 * Returns 1 अगर found, अन्यथा 0
 */
अटल पूर्णांक node_overlaps_later_cs(काष्ठा overlay_changeset *हटाओ_ovcs,
		काष्ठा device_node *हटाओ_ce_node)
अणु
	काष्ठा overlay_changeset *ovcs;
	काष्ठा of_changeset_entry *ce;

	list_क्रम_each_entry_reverse(ovcs, &ovcs_list, ovcs_list) अणु
		अगर (ovcs == हटाओ_ovcs)
			अवरोध;

		list_क्रम_each_entry(ce, &ovcs->cset.entries, node) अणु
			अगर (find_node(ce->np, हटाओ_ce_node)) अणु
				pr_err("%s: #%d overlaps with #%d @%pOF\n",
					__func__, हटाओ_ovcs->id, ovcs->id,
					हटाओ_ce_node);
				वापस 1;
			पूर्ण
			अगर (find_node(हटाओ_ce_node, ce->np)) अणु
				pr_err("%s: #%d overlaps with #%d @%pOF\n",
					__func__, हटाओ_ovcs->id, ovcs->id,
					हटाओ_ce_node);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We can safely हटाओ the overlay only अगर it's the top-most one.
 * Newly applied overlays are inserted at the tail of the overlay list,
 * so a top most overlay is the one that is बंदst to the tail.
 *
 * The topmost check is करोne by exploiting this property. For each
 * affected device node in the log list we check अगर this overlay is
 * the one बंदst to the tail. If another overlay has affected this
 * device node and is बंदst to the tail, then removal is not permited.
 */
अटल पूर्णांक overlay_removal_is_ok(काष्ठा overlay_changeset *हटाओ_ovcs)
अणु
	काष्ठा of_changeset_entry *हटाओ_ce;

	list_क्रम_each_entry(हटाओ_ce, &हटाओ_ovcs->cset.entries, node) अणु
		अगर (node_overlaps_later_cs(हटाओ_ovcs, हटाओ_ce->np)) अणु
			pr_err("overlay #%d is not topmost\n", हटाओ_ovcs->id);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/**
 * of_overlay_हटाओ() - Revert and मुक्त an overlay changeset
 * @ovcs_id:	Poपूर्णांकer to overlay changeset id
 *
 * Removes an overlay अगर it is permissible.  @ovcs_id was previously वापसed
 * by of_overlay_fdt_apply().
 *
 * If an error occurred जबतक attempting to revert the overlay changeset,
 * then an attempt is made to re-apply any changeset entry that was
 * reverted.  If an error occurs on re-apply then the state of the device
 * tree can not be determined, and any following attempt to apply or हटाओ
 * an overlay changeset will be refused.
 *
 * A non-zero वापस value will not revert the changeset अगर error is from:
 *   - parameter checks
 *   - overlay changeset pre-हटाओ notअगरier
 *   - overlay changeset entry revert
 *
 * If an error is वापसed by an overlay changeset pre-हटाओ notअगरier
 * then no further overlay changeset pre-हटाओ notअगरier will be called.
 *
 * If more than one notअगरier वापसs an error, then the last notअगरier
 * error to occur is वापसed.
 *
 * A non-zero वापस value will revert the changeset अगर error is from:
 *   - overlay changeset entry notअगरier
 *   - overlay changeset post-हटाओ notअगरier
 *
 * If an error is वापसed by an overlay changeset post-हटाओ notअगरier
 * then no further overlay changeset post-हटाओ notअगरier will be called.
 *
 * Return: 0 on success, or a negative error number.  *@ovcs_id is set to
 * zero after reverting the changeset, even अगर a subsequent error occurs.
 */
पूर्णांक of_overlay_हटाओ(पूर्णांक *ovcs_id)
अणु
	काष्ठा overlay_changeset *ovcs;
	पूर्णांक ret, ret_apply, ret_पंचांगp;

	अगर (devicetree_corrupt()) अणु
		pr_err("suspect devicetree state, refuse to remove overlay\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	mutex_lock(&of_mutex);

	ovcs = idr_find(&ovcs_idr, *ovcs_id);
	अगर (!ovcs) अणु
		ret = -ENODEV;
		pr_err("remove: Could not find overlay #%d\n", *ovcs_id);
		जाओ out_unlock;
	पूर्ण

	अगर (!overlay_removal_is_ok(ovcs)) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	ret = overlay_notअगरy(ovcs, OF_OVERLAY_PRE_REMOVE);
	अगर (ret) अणु
		pr_err("overlay changeset pre-remove notify error %d\n", ret);
		जाओ out_unlock;
	पूर्ण

	list_del(&ovcs->ovcs_list);

	ret_apply = 0;
	ret = __of_changeset_revert_entries(&ovcs->cset, &ret_apply);
	अगर (ret) अणु
		अगर (ret_apply)
			devicetree_state_flags |= DTSF_REVERT_FAIL;
		जाओ out_unlock;
	पूर्ण

	ret = __of_changeset_revert_notअगरy(&ovcs->cset);
	अगर (ret)
		pr_err("overlay remove changeset entry notify error %d\n", ret);
	/* notअगरy failure is not fatal, जारी */

	*ovcs_id = 0;

	ret_पंचांगp = overlay_notअगरy(ovcs, OF_OVERLAY_POST_REMOVE);
	अगर (ret_पंचांगp) अणु
		pr_err("overlay changeset post-remove notify error %d\n",
		       ret_पंचांगp);
		अगर (!ret)
			ret = ret_पंचांगp;
	पूर्ण

	मुक्त_overlay_changeset(ovcs);

out_unlock:
	mutex_unlock(&of_mutex);

out:
	pr_debug("%s() err=%d\n", __func__, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_overlay_हटाओ);

/**
 * of_overlay_हटाओ_all() - Reverts and मुक्तs all overlay changesets
 *
 * Removes all overlays from the प्रणाली in the correct order.
 *
 * Return: 0 on success, or a negative error number
 */
पूर्णांक of_overlay_हटाओ_all(व्योम)
अणु
	काष्ठा overlay_changeset *ovcs, *ovcs_n;
	पूर्णांक ret;

	/* the tail of list is guaranteed to be safe to हटाओ */
	list_क्रम_each_entry_safe_reverse(ovcs, ovcs_n, &ovcs_list, ovcs_list) अणु
		ret = of_overlay_हटाओ(&ovcs->id);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_overlay_हटाओ_all);
