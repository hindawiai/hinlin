<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_INTERVAL_TREE_H
#घोषणा _LINUX_INTERVAL_TREE_H

#समावेश <linux/rbtree.h>

काष्ठा पूर्णांकerval_tree_node अणु
	काष्ठा rb_node rb;
	अचिन्हित दीर्घ start;	/* Start of पूर्णांकerval */
	अचिन्हित दीर्घ last;	/* Last location _in_ पूर्णांकerval */
	अचिन्हित दीर्घ __subtree_last;
पूर्ण;

बाह्य व्योम
पूर्णांकerval_tree_insert(काष्ठा पूर्णांकerval_tree_node *node,
		     काष्ठा rb_root_cached *root);

बाह्य व्योम
पूर्णांकerval_tree_हटाओ(काष्ठा पूर्णांकerval_tree_node *node,
		     काष्ठा rb_root_cached *root);

बाह्य काष्ठा पूर्णांकerval_tree_node *
पूर्णांकerval_tree_iter_first(काष्ठा rb_root_cached *root,
			 अचिन्हित दीर्घ start, अचिन्हित दीर्घ last);

बाह्य काष्ठा पूर्णांकerval_tree_node *
पूर्णांकerval_tree_iter_next(काष्ठा पूर्णांकerval_tree_node *node,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ last);

#पूर्ण_अगर	/* _LINUX_INTERVAL_TREE_H */
