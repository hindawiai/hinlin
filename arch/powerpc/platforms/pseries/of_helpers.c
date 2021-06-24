<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/माला.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/prom.h>

#समावेश "of_helpers.h"

/**
 * pseries_of_derive_parent - basically like स_नाम(1)
 * @path:  the full_name of a node to be added to the tree
 *
 * Returns the node which should be the parent of the node
 * described by path.  E.g., क्रम path = "/foo/bar", वापसs
 * the node with full_name = "/foo".
 */
काष्ठा device_node *pseries_of_derive_parent(स्थिर अक्षर *path)
अणु
	काष्ठा device_node *parent;
	अक्षर *parent_path = "/";
	स्थिर अक्षर *tail;

	/* We करो not want the trailing '/' अक्षरacter */
	tail = kbasename(path) - 1;

	/* reject अगर path is "/" */
	अगर (!म_भेद(path, "/"))
		वापस ERR_PTR(-EINVAL);

	अगर (tail > path) अणु
		parent_path = kstrndup(path, tail - path, GFP_KERNEL);
		अगर (!parent_path)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण
	parent = of_find_node_by_path(parent_path);
	अगर (म_भेद(parent_path, "/"))
		kमुक्त(parent_path);
	वापस parent ? parent : ERR_PTR(-EINVAL);
पूर्ण


/* Helper Routines to convert between drc_index to cpu numbers */

पूर्णांक of_पढ़ो_drc_info_cell(काष्ठा property **prop, स्थिर __be32 **curval,
			काष्ठा of_drc_info *data)
अणु
	स्थिर अक्षर *p = (अक्षर *)(*curval);
	स्थिर __be32 *p2;

	अगर (!data)
		वापस -EINVAL;

	/* Get drc-type:encode-string */
	data->drc_type = (अक्षर *)p;
	p = of_prop_next_string(*prop, p);
	अगर (!p)
		वापस -EINVAL;

	/* Get drc-name-prefix:encode-string */
	data->drc_name_prefix = (अक्षर *)p;
	p = of_prop_next_string(*prop, p);
	अगर (!p)
		वापस -EINVAL;

	/* Get drc-index-start:encode-पूर्णांक */
	p2 = (स्थिर __be32 *)p;
	data->drc_index_start = be32_to_cpu(*p2);

	/* Get drc-name-suffix-start:encode-पूर्णांक */
	p2 = of_prop_next_u32(*prop, p2, &data->drc_name_suffix_start);
	अगर (!p2)
		वापस -EINVAL;

	/* Get number-sequential-elements:encode-पूर्णांक */
	p2 = of_prop_next_u32(*prop, p2, &data->num_sequential_elems);
	अगर (!p2)
		वापस -EINVAL;

	/* Get sequential-increment:encode-पूर्णांक */
	p2 = of_prop_next_u32(*prop, p2, &data->sequential_inc);
	अगर (!p2)
		वापस -EINVAL;

	/* Get drc-घातer-करोमुख्य:encode-पूर्णांक */
	p2 = of_prop_next_u32(*prop, p2, &data->drc_घातer_करोमुख्य);
	अगर (!p2)
		वापस -EINVAL;

	/* Should now know end of current entry */
	(*curval) = (व्योम *)(++p2);
	data->last_drc_index = data->drc_index_start +
		((data->num_sequential_elems - 1) * data->sequential_inc);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(of_पढ़ो_drc_info_cell);
