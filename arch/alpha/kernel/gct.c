<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/gct.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/gct.h>

पूर्णांक
gct6_find_nodes(gct6_node *node, gct6_search_काष्ठा *search)
अणु
	gct6_search_काष्ठा *wanted;
	पूर्णांक status = 0;

	/* First check the magic number.  */
	अगर (node->magic != GCT_NODE_MAGIC) अणु
		prपूर्णांकk(KERN_ERR "GCT Node MAGIC incorrect - GCT invalid\n");
		वापस -EINVAL;
	पूर्ण

	/* Check against the search काष्ठा.  */
	क्रम (wanted = search; 
	     wanted && (wanted->type | wanted->subtype); 
	     wanted++) अणु
		अगर (node->type != wanted->type)
			जारी;
		अगर (node->subtype != wanted->subtype)
			जारी;

		/* Found it -- call out.  */
		अगर (wanted->callout)
			wanted->callout(node);
	पूर्ण

	/* Now walk the tree, siblings first.  */
	अगर (node->next) 
		status |= gct6_find_nodes(GCT_NODE_PTR(node->next), search);

	/* Then the children.  */
	अगर (node->child) 
		status |= gct6_find_nodes(GCT_NODE_PTR(node->child), search);

	वापस status;
पूर्ण
