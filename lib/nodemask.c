<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/nodemask.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>

पूर्णांक __next_node_in(पूर्णांक node, स्थिर nodemask_t *srcp)
अणु
	पूर्णांक ret = __next_node(node, srcp);

	अगर (ret == MAX_NUMNODES)
		ret = __first_node(srcp);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__next_node_in);

#अगर_घोषित CONFIG_NUMA
/*
 * Return the bit number of a अक्रमom bit set in the nodemask.
 * (वापसs NUMA_NO_NODE अगर nodemask is empty)
 */
पूर्णांक node_अक्रमom(स्थिर nodemask_t *maskp)
अणु
	पूर्णांक w, bit = NUMA_NO_NODE;

	w = nodes_weight(*maskp);
	अगर (w)
		bit = biपंचांगap_ord_to_pos(maskp->bits,
			get_अक्रमom_पूर्णांक() % w, MAX_NUMNODES);
	वापस bit;
पूर्ण
#पूर्ण_अगर
