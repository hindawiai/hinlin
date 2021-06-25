<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_INTLIST_H
#घोषणा __PERF_INTLIST_H

#समावेश <linux/rbtree.h>
#समावेश <stdbool.h>

#समावेश "rblist.h"

काष्ठा पूर्णांक_node अणु
	काष्ठा rb_node rb_node;
	अचिन्हित दीर्घ i;
	व्योम *priv;
पूर्ण;

काष्ठा पूर्णांकlist अणु
	काष्ठा rblist rblist;
पूर्ण;

काष्ठा पूर्णांकlist *पूर्णांकlist__new(स्थिर अक्षर *slist);
व्योम पूर्णांकlist__delete(काष्ठा पूर्णांकlist *ilist);

व्योम पूर्णांकlist__हटाओ(काष्ठा पूर्णांकlist *ilist, काष्ठा पूर्णांक_node *in);
पूर्णांक पूर्णांकlist__add(काष्ठा पूर्णांकlist *ilist, अचिन्हित दीर्घ i);

काष्ठा पूर्णांक_node *पूर्णांकlist__entry(स्थिर काष्ठा पूर्णांकlist *ilist, अचिन्हित पूर्णांक idx);
काष्ठा पूर्णांक_node *पूर्णांकlist__find(काष्ठा पूर्णांकlist *ilist, अचिन्हित दीर्घ i);
काष्ठा पूर्णांक_node *पूर्णांकlist__findnew(काष्ठा पूर्णांकlist *ilist, अचिन्हित दीर्घ i);

अटल अंतरभूत bool पूर्णांकlist__has_entry(काष्ठा पूर्णांकlist *ilist, अचिन्हित दीर्घ i)
अणु
	वापस पूर्णांकlist__find(ilist, i) != शून्य;
पूर्ण

अटल अंतरभूत bool पूर्णांकlist__empty(स्थिर काष्ठा पूर्णांकlist *ilist)
अणु
	वापस rblist__empty(&ilist->rblist);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक पूर्णांकlist__nr_entries(स्थिर काष्ठा पूर्णांकlist *ilist)
अणु
	वापस rblist__nr_entries(&ilist->rblist);
पूर्ण

/* For पूर्णांकlist iteration */
अटल अंतरभूत काष्ठा पूर्णांक_node *पूर्णांकlist__first(काष्ठा पूर्णांकlist *ilist)
अणु
	काष्ठा rb_node *rn = rb_first_cached(&ilist->rblist.entries);
	वापस rn ? rb_entry(rn, काष्ठा पूर्णांक_node, rb_node) : शून्य;
पूर्ण
अटल अंतरभूत काष्ठा पूर्णांक_node *पूर्णांकlist__next(काष्ठा पूर्णांक_node *in)
अणु
	काष्ठा rb_node *rn;
	अगर (!in)
		वापस शून्य;
	rn = rb_next(&in->rb_node);
	वापस rn ? rb_entry(rn, काष्ठा पूर्णांक_node, rb_node) : शून्य;
पूर्ण

/**
 * पूर्णांकlist__क्रम_each_entry      - iterate over a पूर्णांकlist
 * @pos:	the &काष्ठा पूर्णांक_node to use as a loop cursor.
 * @ilist:	the &काष्ठा पूर्णांकlist क्रम loop.
 */
#घोषणा पूर्णांकlist__क्रम_each_entry(pos, ilist)	\
	क्रम (pos = पूर्णांकlist__first(ilist); pos; pos = पूर्णांकlist__next(pos))

/**
 * पूर्णांकlist__क्रम_each_entry_safe - iterate over a पूर्णांकlist safe against removal of
 *                         पूर्णांक_node
 * @pos:	the &काष्ठा पूर्णांक_node to use as a loop cursor.
 * @n:		another &काष्ठा पूर्णांक_node to use as temporary storage.
 * @ilist:	the &काष्ठा पूर्णांकlist क्रम loop.
 */
#घोषणा पूर्णांकlist__क्रम_each_entry_safe(pos, n, ilist)	\
	क्रम (pos = पूर्णांकlist__first(ilist), n = पूर्णांकlist__next(pos); pos;\
	     pos = n, n = पूर्णांकlist__next(n))
#पूर्ण_अगर /* __PERF_INTLIST_H */
