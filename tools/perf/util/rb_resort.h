<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_RESORT_RB_H_
#घोषणा _PERF_RESORT_RB_H_
/*
 * Template क्रम creating a class to resort an existing rb_tree according to
 * a new sort criteria, that must be present in the entries of the source
 * rb_tree.
 *
 * (c) 2016 Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Quick example, resorting thपढ़ोs by its लघुname:
 *
 * First define the prefix (thपढ़ोs) to be used क्रम the functions and data
 * काष्ठाures created, and provide an expression क्रम the sorting, then the
 * fields to be present in each of the entries in the new, sorted, rb_tree.
 *
 * The body of the init function should collect the fields, maybe
 * pre-calculating them from multiple entries in the original 'entry' from
 * the rb_tree used as a source क्रम the entries to be sorted:

DEFINE_RB_RESORT_RB(thपढ़ोs, म_भेद(a->thपढ़ो->लघुname,
				    b->thपढ़ो->लघुname) < 0,
	काष्ठा thपढ़ो *thपढ़ो;
)
अणु
	entry->thपढ़ो = rb_entry(nd, काष्ठा thपढ़ो, rb_node);
पूर्ण

 * After this it is just a matter of instantiating it and iterating it,
 * क्रम a few data काष्ठाures with existing rb_trees, such as 'struct machine',
 * helpers are available to get the rb_root and the nr_entries:

	DECLARE_RESORT_RB_MACHINE_THREADS(thपढ़ोs, machine_ptr);

 * This will instantiate the new rb_tree and a cursor क्रम it, that can be used as:

	काष्ठा rb_node *nd;

	resort_rb__क्रम_each_entry(nd, thपढ़ोs) अणु
		काष्ठा thपढ़ो *t = thपढ़ोs_entry;
		म_लिखो("%s: %d\n", t->लघुname, t->tid);
	पूर्ण

 * Then delete it:

	resort_rb__delete(thपढ़ोs);

 * The name of the data काष्ठाures and functions will have a _sorted suffix
 * right beक्रमe the method names, i.e. will look like:
 *
 * 	काष्ठा thपढ़ोs_sorted_entry अणुपूर्ण
 * 	thपढ़ोs_sorted__insert()
 */

#घोषणा DEFINE_RESORT_RB(__name, __comp, ...)					\
काष्ठा __name##_sorted_entry अणु							\
	काष्ठा rb_node	rb_node;						\
	__VA_ARGS__								\
पूर्ण;										\
अटल व्योम __name##_sorted__init_entry(काष्ठा rb_node *nd,			\
					काष्ठा __name##_sorted_entry *entry);	\
										\
अटल पूर्णांक __name##_sorted__cmp(काष्ठा rb_node *nda, काष्ठा rb_node *ndb)	\
अणु										\
	काष्ठा __name##_sorted_entry *a, *b;					\
	a = rb_entry(nda, काष्ठा __name##_sorted_entry, rb_node);		\
	b = rb_entry(ndb, काष्ठा __name##_sorted_entry, rb_node);		\
	वापस __comp;								\
पूर्ण										\
										\
काष्ठा __name##_sorted अणु							\
       काष्ठा rb_root		    entries;					\
       काष्ठा __name##_sorted_entry nd[0];					\
पूर्ण;										\
										\
अटल व्योम __name##_sorted__insert(काष्ठा __name##_sorted *sorted,		\
				      काष्ठा rb_node *sorted_nd)		\
अणु										\
	काष्ठा rb_node **p = &sorted->entries.rb_node, *parent = शून्य;		\
	जबतक (*p != शून्य) अणु							\
		parent = *p;							\
		अगर (__name##_sorted__cmp(sorted_nd, parent))			\
			p = &(*p)->rb_left;					\
		अन्यथा								\
			p = &(*p)->rb_right;					\
	पूर्ण									\
	rb_link_node(sorted_nd, parent, p);					\
	rb_insert_color(sorted_nd, &sorted->entries);				\
पूर्ण										\
										\
अटल व्योम __name##_sorted__sort(काष्ठा __name##_sorted *sorted,		\
				    काष्ठा rb_root *entries)			\
अणु										\
	काष्ठा rb_node *nd;							\
	अचिन्हित पूर्णांक i = 0;							\
	क्रम (nd = rb_first(entries); nd; nd = rb_next(nd)) अणु			\
		काष्ठा __name##_sorted_entry *snd = &sorted->nd[i++];		\
		__name##_sorted__init_entry(nd, snd);				\
		__name##_sorted__insert(sorted, &snd->rb_node);			\
	पूर्ण									\
पूर्ण										\
										\
अटल काष्ठा __name##_sorted *__name##_sorted__new(काष्ठा rb_root *entries,	\
						    पूर्णांक nr_entries)		\
अणु										\
	काष्ठा __name##_sorted *sorted;						\
	sorted = दो_स्मृति(माप(*sorted) + माप(sorted->nd[0]) * nr_entries);	\
	अगर (sorted) अणु								\
		sorted->entries = RB_ROOT;					\
		__name##_sorted__sort(sorted, entries);				\
	पूर्ण									\
	वापस sorted;								\
पूर्ण										\
										\
अटल व्योम __name##_sorted__delete(काष्ठा __name##_sorted *sorted)		\
अणु										\
	मुक्त(sorted);								\
पूर्ण										\
										\
अटल व्योम __name##_sorted__init_entry(काष्ठा rb_node *nd,			\
					काष्ठा __name##_sorted_entry *entry)

#घोषणा DECLARE_RESORT_RB(__name)						\
काष्ठा __name##_sorted_entry *__name##_entry;					\
काष्ठा __name##_sorted *__name = __name##_sorted__new

#घोषणा resort_rb__क्रम_each_entry(__nd, __name)					\
	क्रम (__nd = rb_first(&__name->entries);					\
	     __name##_entry = rb_entry(__nd, काष्ठा __name##_sorted_entry,	\
				       rb_node), __nd;				\
	     __nd = rb_next(__nd))

#घोषणा resort_rb__delete(__name)						\
	__name##_sorted__delete(__name), __name = शून्य

/*
 * Helpers क्रम other classes that contains both an rbtree and the
 * number of entries in it:
 */

/* For 'struct intlist' */
#घोषणा DECLARE_RESORT_RB_INTLIST(__name, __ilist)				\
	DECLARE_RESORT_RB(__name)(&__ilist->rblist.entries.rb_root,		\
				  __ilist->rblist.nr_entries)

/* For 'struct machine->threads' */
#घोषणा DECLARE_RESORT_RB_MACHINE_THREADS(__name, __machine, hash_bucket)    \
 DECLARE_RESORT_RB(__name)(&__machine->thपढ़ोs[hash_bucket].entries.rb_root, \
			   __machine->thपढ़ोs[hash_bucket].nr)

#पूर्ण_अगर /* _PERF_RESORT_RB_H_ */
