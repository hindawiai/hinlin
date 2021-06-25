<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions क्रम dealing with DT resolution
 *
 * Copyright (C) 2012 Pantelis Antoniou <panto@antoniou-consulting.com>
 * Copyright (C) 2012 Texas Instruments Inc.
 */

#घोषणा pr_fmt(fmt)	"OF: resolver: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश "of_private.h"

अटल phandle live_tree_max_phandle(व्योम)
अणु
	काष्ठा device_node *node;
	phandle phandle;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	phandle = 0;
	क्रम_each_of_allnodes(node) अणु
		अगर (node->phandle != OF_PHANDLE_ILLEGAL &&
				node->phandle > phandle)
			phandle = node->phandle;
	पूर्ण
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	वापस phandle;
पूर्ण

अटल व्योम adjust_overlay_phandles(काष्ठा device_node *overlay,
		पूर्णांक phandle_delta)
अणु
	काष्ठा device_node *child;
	काष्ठा property *prop;
	phandle phandle;

	/* adjust node's phandle in node */
	अगर (overlay->phandle != 0 && overlay->phandle != OF_PHANDLE_ILLEGAL)
		overlay->phandle += phandle_delta;

	/* copy adjusted phandle पूर्णांकo *phandle properties */
	क्रम_each_property_of_node(overlay, prop) अणु

		अगर (of_prop_cmp(prop->name, "phandle") &&
		    of_prop_cmp(prop->name, "linux,phandle"))
			जारी;

		अगर (prop->length < 4)
			जारी;

		phandle = be32_to_cpup(prop->value);
		अगर (phandle == OF_PHANDLE_ILLEGAL)
			जारी;

		*(__be32 *)prop->value = cpu_to_be32(overlay->phandle);
	पूर्ण

	क्रम_each_child_of_node(overlay, child)
		adjust_overlay_phandles(child, phandle_delta);
पूर्ण

अटल पूर्णांक update_usages_of_a_phandle_reference(काष्ठा device_node *overlay,
		काष्ठा property *prop_fixup, phandle phandle)
अणु
	काष्ठा device_node *refnode;
	काष्ठा property *prop;
	अक्षर *value, *cur, *end, *node_path, *prop_name, *s;
	पूर्णांक offset, len;
	पूर्णांक err = 0;

	value = kmemdup(prop_fixup->value, prop_fixup->length, GFP_KERNEL);
	अगर (!value)
		वापस -ENOMEM;

	/* prop_fixup contains a list of tuples of path:property_name:offset */
	end = value + prop_fixup->length;
	क्रम (cur = value; cur < end; cur += len + 1) अणु
		len = म_माप(cur);

		node_path = cur;
		s = म_अक्षर(cur, ':');
		अगर (!s) अणु
			err = -EINVAL;
			जाओ err_fail;
		पूर्ण
		*s++ = '\0';

		prop_name = s;
		s = म_अक्षर(s, ':');
		अगर (!s) अणु
			err = -EINVAL;
			जाओ err_fail;
		पूर्ण
		*s++ = '\0';

		err = kstrtoपूर्णांक(s, 10, &offset);
		अगर (err)
			जाओ err_fail;

		refnode = __of_find_node_by_full_path(of_node_get(overlay), node_path);
		अगर (!refnode)
			जारी;

		क्रम_each_property_of_node(refnode, prop) अणु
			अगर (!of_prop_cmp(prop->name, prop_name))
				अवरोध;
		पूर्ण
		of_node_put(refnode);

		अगर (!prop) अणु
			err = -ENOENT;
			जाओ err_fail;
		पूर्ण

		अगर (offset < 0 || offset + माप(__be32) > prop->length) अणु
			err = -EINVAL;
			जाओ err_fail;
		पूर्ण

		*(__be32 *)(prop->value + offset) = cpu_to_be32(phandle);
	पूर्ण

err_fail:
	kमुक्त(value);
	वापस err;
पूर्ण

/* compare nodes taking पूर्णांकo account that 'name' strips out the @ part */
अटल पूर्णांक node_name_cmp(स्थिर काष्ठा device_node *dn1,
		स्थिर काष्ठा device_node *dn2)
अणु
	स्थिर अक्षर *n1 = kbasename(dn1->full_name);
	स्थिर अक्षर *n2 = kbasename(dn2->full_name);

	वापस of_node_cmp(n1, n2);
पूर्ण

/*
 * Adjust the local phandle references by the given phandle delta.
 *
 * Subtree @local_fixups, which is overlay node __local_fixups__,
 * mirrors the fragment node काष्ठाure at the root of the overlay.
 *
 * For each property in the fragments that contains a phandle reference,
 * @local_fixups has a property of the same name that contains a list
 * of offsets of the phandle reference(s) within the respective property
 * value(s).  The values at these offsets will be fixed up.
 */
अटल पूर्णांक adjust_local_phandle_references(काष्ठा device_node *local_fixups,
		काष्ठा device_node *overlay, पूर्णांक phandle_delta)
अणु
	काष्ठा device_node *child, *overlay_child;
	काष्ठा property *prop_fix, *prop;
	पूर्णांक err, i, count;
	अचिन्हित पूर्णांक off;

	अगर (!local_fixups)
		वापस 0;

	क्रम_each_property_of_node(local_fixups, prop_fix) अणु

		/* skip properties added स्वतःmatically */
		अगर (!of_prop_cmp(prop_fix->name, "name") ||
		    !of_prop_cmp(prop_fix->name, "phandle") ||
		    !of_prop_cmp(prop_fix->name, "linux,phandle"))
			जारी;

		अगर ((prop_fix->length % 4) != 0 || prop_fix->length == 0)
			वापस -EINVAL;
		count = prop_fix->length / माप(__be32);

		क्रम_each_property_of_node(overlay, prop) अणु
			अगर (!of_prop_cmp(prop->name, prop_fix->name))
				अवरोध;
		पूर्ण

		अगर (!prop)
			वापस -EINVAL;

		क्रम (i = 0; i < count; i++) अणु
			off = be32_to_cpu(((__be32 *)prop_fix->value)[i]);
			अगर ((off + 4) > prop->length)
				वापस -EINVAL;

			be32_add_cpu(prop->value + off, phandle_delta);
		पूर्ण
	पूर्ण

	/*
	 * These nested loops recurse करोwn two subtrees in parallel, where the
	 * node names in the two subtrees match.
	 *
	 * The roots of the subtrees are the overlay's __local_fixups__ node
	 * and the overlay's root node.
	 */
	क्रम_each_child_of_node(local_fixups, child) अणु

		क्रम_each_child_of_node(overlay, overlay_child)
			अगर (!node_name_cmp(child, overlay_child)) अणु
				of_node_put(overlay_child);
				अवरोध;
			पूर्ण

		अगर (!overlay_child) अणु
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण

		err = adjust_local_phandle_references(child, overlay_child,
				phandle_delta);
		अगर (err) अणु
			of_node_put(child);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * of_resolve_phandles - Relocate and resolve overlay against live tree
 *
 * @overlay:	Poपूर्णांकer to devicetree overlay to relocate and resolve
 *
 * Modअगरy (relocate) values of local phandles in @overlay to a range that
 * करोes not conflict with the live expanded devicetree.  Update references
 * to the local phandles in @overlay.  Update (resolve) phandle references
 * in @overlay that refer to the live expanded devicetree.
 *
 * Phandle values in the live tree are in the range of
 * 1 .. live_tree_max_phandle().  The range of phandle values in the overlay
 * also begin with at 1.  Adjust the phandle values in the overlay to begin
 * at live_tree_max_phandle() + 1.  Update references to the phandles to
 * the adjusted phandle values.
 *
 * The name of each property in the "__fixups__" node in the overlay matches
 * the name of a symbol (a label) in the live tree.  The values of each
 * property in the "__fixups__" node is a list of the property values in the
 * overlay that need to be updated to contain the phandle reference
 * corresponding to that symbol in the live tree.  Update the references in
 * the overlay with the phandle values in the live tree.
 *
 * @overlay must be detached.
 *
 * Resolving and applying @overlay to the live expanded devicetree must be
 * रक्षित by a mechanism to ensure that multiple overlays are processed
 * in a single thपढ़ोed manner so that multiple overlays will not relocate
 * phandles to overlapping ranges.  The mechanism to enक्रमce this is not
 * yet implemented.
 *
 * Return: %0 on success or a negative error value on error.
 */
पूर्णांक of_resolve_phandles(काष्ठा device_node *overlay)
अणु
	काष्ठा device_node *child, *local_fixups, *refnode;
	काष्ठा device_node *tree_symbols, *overlay_fixups;
	काष्ठा property *prop;
	स्थिर अक्षर *refpath;
	phandle phandle, phandle_delta;
	पूर्णांक err;

	tree_symbols = शून्य;

	अगर (!overlay) अणु
		pr_err("null overlay\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!of_node_check_flag(overlay, OF_DETACHED)) अणु
		pr_err("overlay not detached\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	phandle_delta = live_tree_max_phandle() + 1;
	adjust_overlay_phandles(overlay, phandle_delta);

	क्रम_each_child_of_node(overlay, local_fixups)
		अगर (of_node_name_eq(local_fixups, "__local_fixups__"))
			अवरोध;

	err = adjust_local_phandle_references(local_fixups, overlay, phandle_delta);
	अगर (err)
		जाओ out;

	overlay_fixups = शून्य;

	क्रम_each_child_of_node(overlay, child) अणु
		अगर (of_node_name_eq(child, "__fixups__"))
			overlay_fixups = child;
	पूर्ण

	अगर (!overlay_fixups) अणु
		err = 0;
		जाओ out;
	पूर्ण

	tree_symbols = of_find_node_by_path("/__symbols__");
	अगर (!tree_symbols) अणु
		pr_err("no symbols in root of device tree.\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम_each_property_of_node(overlay_fixups, prop) अणु

		/* skip properties added स्वतःmatically */
		अगर (!of_prop_cmp(prop->name, "name"))
			जारी;

		err = of_property_पढ़ो_string(tree_symbols,
				prop->name, &refpath);
		अगर (err) अणु
			pr_err("node label '%s' not found in live devicetree symbols table\n",
			       prop->name);
			जाओ out;
		पूर्ण

		refnode = of_find_node_by_path(refpath);
		अगर (!refnode) अणु
			err = -ENOENT;
			जाओ out;
		पूर्ण

		phandle = refnode->phandle;
		of_node_put(refnode);

		err = update_usages_of_a_phandle_reference(overlay, prop, phandle);
		अगर (err)
			अवरोध;
	पूर्ण

out:
	अगर (err)
		pr_err("overlay phandle fixup failed: %d\n", err);
	of_node_put(tree_symbols);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(of_resolve_phandles);
