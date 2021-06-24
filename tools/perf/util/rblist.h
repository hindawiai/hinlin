<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_RBLIST_H
#घोषणा __PERF_RBLIST_H

#समावेश <linux/rbtree.h>
#समावेश <stdbool.h>

/*
 * create node काष्ठाs of the क्रमm:
 * काष्ठा my_node अणु
 *     काष्ठा rb_node rb_node;
 *     ... my data ...
 * पूर्ण;
 *
 * create list काष्ठाs of the क्रमm:
 * काष्ठा mylist अणु
 *     काष्ठा rblist rblist;
 *     ... my data ...
 * पूर्ण;
 */

काष्ठा rblist अणु
	काष्ठा rb_root_cached entries;
	अचिन्हित पूर्णांक   nr_entries;

	पूर्णांक (*node_cmp)(काष्ठा rb_node *rbn, स्थिर व्योम *entry);
	काष्ठा rb_node *(*node_new)(काष्ठा rblist *rlist, स्थिर व्योम *new_entry);
	व्योम (*node_delete)(काष्ठा rblist *rblist, काष्ठा rb_node *rb_node);
पूर्ण;

व्योम rblist__init(काष्ठा rblist *rblist);
व्योम rblist__निकास(काष्ठा rblist *rblist);
व्योम rblist__delete(काष्ठा rblist *rblist);
पूर्णांक rblist__add_node(काष्ठा rblist *rblist, स्थिर व्योम *new_entry);
व्योम rblist__हटाओ_node(काष्ठा rblist *rblist, काष्ठा rb_node *rb_node);
काष्ठा rb_node *rblist__find(काष्ठा rblist *rblist, स्थिर व्योम *entry);
काष्ठा rb_node *rblist__findnew(काष्ठा rblist *rblist, स्थिर व्योम *entry);
काष्ठा rb_node *rblist__entry(स्थिर काष्ठा rblist *rblist, अचिन्हित पूर्णांक idx);

अटल अंतरभूत bool rblist__empty(स्थिर काष्ठा rblist *rblist)
अणु
	वापस rblist->nr_entries == 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rblist__nr_entries(स्थिर काष्ठा rblist *rblist)
अणु
	वापस rblist->nr_entries;
पूर्ण

#पूर्ण_अगर /* __PERF_RBLIST_H */
