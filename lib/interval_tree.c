<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/पूर्णांकerval_tree.h>
#समावेश <linux/पूर्णांकerval_tree_generic.h>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>

#घोषणा START(node) ((node)->start)
#घोषणा LAST(node)  ((node)->last)

INTERVAL_TREE_DEFINE(काष्ठा पूर्णांकerval_tree_node, rb,
		     अचिन्हित दीर्घ, __subtree_last,
		     START, LAST,, पूर्णांकerval_tree)

EXPORT_SYMBOL_GPL(पूर्णांकerval_tree_insert);
EXPORT_SYMBOL_GPL(पूर्णांकerval_tree_हटाओ);
EXPORT_SYMBOL_GPL(पूर्णांकerval_tree_iter_first);
EXPORT_SYMBOL_GPL(पूर्णांकerval_tree_iter_next);
