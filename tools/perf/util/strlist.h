<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_STRLIST_H
#घोषणा __PERF_STRLIST_H

#समावेश <linux/rbtree.h>
#समावेश <stdbool.h>

#समावेश "rblist.h"

काष्ठा str_node अणु
	काष्ठा rb_node rb_node;
	स्थिर अक्षर     *s;
पूर्ण;

काष्ठा strlist अणु
	काष्ठा rblist rblist;
	bool	      dupstr;
	bool	      file_only;
पूर्ण;

/*
 * @file_only: When स_नाम is present, only consider entries as filenames,
 *             that should not be added to the list अगर स_नाम/entry is not
 *             found
 */
काष्ठा strlist_config अणु
	bool करोnt_dupstr;
	bool file_only;
	स्थिर अक्षर *स_नाम;
पूर्ण;

काष्ठा strlist *strlist__new(स्थिर अक्षर *slist, स्थिर काष्ठा strlist_config *config);
व्योम strlist__delete(काष्ठा strlist *slist);

व्योम strlist__हटाओ(काष्ठा strlist *slist, काष्ठा str_node *sn);
पूर्णांक strlist__load(काष्ठा strlist *slist, स्थिर अक्षर *filename);
पूर्णांक strlist__add(काष्ठा strlist *slist, स्थिर अक्षर *str);

काष्ठा str_node *strlist__entry(स्थिर काष्ठा strlist *slist, अचिन्हित पूर्णांक idx);
काष्ठा str_node *strlist__find(काष्ठा strlist *slist, स्थिर अक्षर *entry);

अटल अंतरभूत bool strlist__has_entry(काष्ठा strlist *slist, स्थिर अक्षर *entry)
अणु
	वापस strlist__find(slist, entry) != शून्य;
पूर्ण

अटल अंतरभूत bool strlist__empty(स्थिर काष्ठा strlist *slist)
अणु
	वापस rblist__empty(&slist->rblist);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक strlist__nr_entries(स्थिर काष्ठा strlist *slist)
अणु
	वापस rblist__nr_entries(&slist->rblist);
पूर्ण

/* For strlist iteration */
अटल अंतरभूत काष्ठा str_node *strlist__first(काष्ठा strlist *slist)
अणु
	काष्ठा rb_node *rn = rb_first_cached(&slist->rblist.entries);
	वापस rn ? rb_entry(rn, काष्ठा str_node, rb_node) : शून्य;
पूर्ण
अटल अंतरभूत काष्ठा str_node *strlist__next(काष्ठा str_node *sn)
अणु
	काष्ठा rb_node *rn;
	अगर (!sn)
		वापस शून्य;
	rn = rb_next(&sn->rb_node);
	वापस rn ? rb_entry(rn, काष्ठा str_node, rb_node) : शून्य;
पूर्ण

/**
 * strlist_क्रम_each      - iterate over a strlist
 * @pos:	the &काष्ठा str_node to use as a loop cursor.
 * @slist:	the &काष्ठा strlist क्रम loop.
 */
#घोषणा strlist__क्रम_each_entry(pos, slist)	\
	क्रम (pos = strlist__first(slist); pos; pos = strlist__next(pos))

/**
 * strlist_क्रम_each_safe - iterate over a strlist safe against removal of
 *                         str_node
 * @pos:	the &काष्ठा str_node to use as a loop cursor.
 * @n:		another &काष्ठा str_node to use as temporary storage.
 * @slist:	the &काष्ठा strlist क्रम loop.
 */
#घोषणा strlist__क्रम_each_entry_safe(pos, n, slist)	\
	क्रम (pos = strlist__first(slist), n = strlist__next(pos); pos;\
	     pos = n, n = strlist__next(n))
#पूर्ण_अगर /* __PERF_STRLIST_H */
