<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Statically sized hash table implementation
 * (C) 2012  Sasha Levin <levinsasha928@gmail.com>
 */

#अगर_अघोषित _LINUX_HASHTABLE_H
#घोषणा _LINUX_HASHTABLE_H

#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hash.h>
#समावेश <linux/rculist.h>

#घोषणा DEFINE_HASHTABLE(name, bits)						\
	काष्ठा hlist_head name[1 << (bits)] =					\
			अणु [0 ... ((1 << (bits)) - 1)] = HLIST_HEAD_INIT पूर्ण

#घोषणा DEFINE_READ_MOSTLY_HASHTABLE(name, bits)				\
	काष्ठा hlist_head name[1 << (bits)] __पढ़ो_mostly =			\
			अणु [0 ... ((1 << (bits)) - 1)] = HLIST_HEAD_INIT पूर्ण

#घोषणा DECLARE_HASHTABLE(name, bits)                                   	\
	काष्ठा hlist_head name[1 << (bits)]

#घोषणा HASH_SIZE(name) (ARRAY_SIZE(name))
#घोषणा HASH_BITS(name) ilog2(HASH_SIZE(name))

/* Use hash_32 when possible to allow क्रम fast 32bit hashing in 64bit kernels. */
#घोषणा hash_min(val, bits)							\
	(माप(val) <= 4 ? hash_32(val, bits) : hash_दीर्घ(val, bits))

अटल अंतरभूत व्योम __hash_init(काष्ठा hlist_head *ht, अचिन्हित पूर्णांक sz)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sz; i++)
		INIT_HLIST_HEAD(&ht[i]);
पूर्ण

/**
 * hash_init - initialize a hash table
 * @hashtable: hashtable to be initialized
 *
 * Calculates the size of the hashtable from the given parameter, otherwise
 * same as hash_init_size.
 *
 * This has to be a macro since HASH_BITS() will not work on poपूर्णांकers since
 * it calculates the size during preprocessing.
 */
#घोषणा hash_init(hashtable) __hash_init(hashtable, HASH_SIZE(hashtable))

/**
 * hash_add - add an object to a hashtable
 * @hashtable: hashtable to add to
 * @node: the &काष्ठा hlist_node of the object to be added
 * @key: the key of the object to be added
 */
#घोषणा hash_add(hashtable, node, key)						\
	hlist_add_head(node, &hashtable[hash_min(key, HASH_BITS(hashtable))])

/**
 * hash_add_rcu - add an object to a rcu enabled hashtable
 * @hashtable: hashtable to add to
 * @node: the &काष्ठा hlist_node of the object to be added
 * @key: the key of the object to be added
 */
#घोषणा hash_add_rcu(hashtable, node, key)					\
	hlist_add_head_rcu(node, &hashtable[hash_min(key, HASH_BITS(hashtable))])

/**
 * hash_hashed - check whether an object is in any hashtable
 * @node: the &काष्ठा hlist_node of the object to be checked
 */
अटल अंतरभूत bool hash_hashed(काष्ठा hlist_node *node)
अणु
	वापस !hlist_unhashed(node);
पूर्ण

अटल अंतरभूत bool __hash_empty(काष्ठा hlist_head *ht, अचिन्हित पूर्णांक sz)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sz; i++)
		अगर (!hlist_empty(&ht[i]))
			वापस false;

	वापस true;
पूर्ण

/**
 * hash_empty - check whether a hashtable is empty
 * @hashtable: hashtable to check
 *
 * This has to be a macro since HASH_BITS() will not work on poपूर्णांकers since
 * it calculates the size during preprocessing.
 */
#घोषणा hash_empty(hashtable) __hash_empty(hashtable, HASH_SIZE(hashtable))

/**
 * hash_del - हटाओ an object from a hashtable
 * @node: &काष्ठा hlist_node of the object to हटाओ
 */
अटल अंतरभूत व्योम hash_del(काष्ठा hlist_node *node)
अणु
	hlist_del_init(node);
पूर्ण

/**
 * hash_del_rcu - हटाओ an object from a rcu enabled hashtable
 * @node: &काष्ठा hlist_node of the object to हटाओ
 */
अटल अंतरभूत व्योम hash_del_rcu(काष्ठा hlist_node *node)
अणु
	hlist_del_init_rcu(node);
पूर्ण

/**
 * hash_क्रम_each - iterate over a hashtable
 * @name: hashtable to iterate
 * @bkt: पूर्णांकeger to use as bucket loop cursor
 * @obj: the type * to use as a loop cursor क्रम each entry
 * @member: the name of the hlist_node within the काष्ठा
 */
#घोषणा hash_क्रम_each(name, bkt, obj, member)				\
	क्रम ((bkt) = 0, obj = शून्य; obj == शून्य && (bkt) < HASH_SIZE(name);\
			(bkt)++)\
		hlist_क्रम_each_entry(obj, &name[bkt], member)

/**
 * hash_क्रम_each_rcu - iterate over a rcu enabled hashtable
 * @name: hashtable to iterate
 * @bkt: पूर्णांकeger to use as bucket loop cursor
 * @obj: the type * to use as a loop cursor क्रम each entry
 * @member: the name of the hlist_node within the काष्ठा
 */
#घोषणा hash_क्रम_each_rcu(name, bkt, obj, member)			\
	क्रम ((bkt) = 0, obj = शून्य; obj == शून्य && (bkt) < HASH_SIZE(name);\
			(bkt)++)\
		hlist_क्रम_each_entry_rcu(obj, &name[bkt], member)

/**
 * hash_क्रम_each_safe - iterate over a hashtable safe against removal of
 * hash entry
 * @name: hashtable to iterate
 * @bkt: पूर्णांकeger to use as bucket loop cursor
 * @पंचांगp: a &काष्ठा hlist_node used क्रम temporary storage
 * @obj: the type * to use as a loop cursor क्रम each entry
 * @member: the name of the hlist_node within the काष्ठा
 */
#घोषणा hash_क्रम_each_safe(name, bkt, पंचांगp, obj, member)			\
	क्रम ((bkt) = 0, obj = शून्य; obj == शून्य && (bkt) < HASH_SIZE(name);\
			(bkt)++)\
		hlist_क्रम_each_entry_safe(obj, पंचांगp, &name[bkt], member)

/**
 * hash_क्रम_each_possible - iterate over all possible objects hashing to the
 * same bucket
 * @name: hashtable to iterate
 * @obj: the type * to use as a loop cursor क्रम each entry
 * @member: the name of the hlist_node within the काष्ठा
 * @key: the key of the objects to iterate over
 */
#घोषणा hash_क्रम_each_possible(name, obj, member, key)			\
	hlist_क्रम_each_entry(obj, &name[hash_min(key, HASH_BITS(name))], member)

/**
 * hash_क्रम_each_possible_rcu - iterate over all possible objects hashing to the
 * same bucket in an rcu enabled hashtable
 * @name: hashtable to iterate
 * @obj: the type * to use as a loop cursor क्रम each entry
 * @member: the name of the hlist_node within the काष्ठा
 * @key: the key of the objects to iterate over
 */
#घोषणा hash_क्रम_each_possible_rcu(name, obj, member, key, cond...)	\
	hlist_क्रम_each_entry_rcu(obj, &name[hash_min(key, HASH_BITS(name))],\
		member, ## cond)

/**
 * hash_क्रम_each_possible_rcu_notrace - iterate over all possible objects hashing
 * to the same bucket in an rcu enabled hashtable in a rcu enabled hashtable
 * @name: hashtable to iterate
 * @obj: the type * to use as a loop cursor क्रम each entry
 * @member: the name of the hlist_node within the काष्ठा
 * @key: the key of the objects to iterate over
 *
 * This is the same as hash_क्रम_each_possible_rcu() except that it करोes
 * not करो any RCU debugging or tracing.
 */
#घोषणा hash_क्रम_each_possible_rcu_notrace(name, obj, member, key) \
	hlist_क्रम_each_entry_rcu_notrace(obj, \
		&name[hash_min(key, HASH_BITS(name))], member)

/**
 * hash_क्रम_each_possible_safe - iterate over all possible objects hashing to the
 * same bucket safe against removals
 * @name: hashtable to iterate
 * @obj: the type * to use as a loop cursor क्रम each entry
 * @पंचांगp: a &काष्ठा hlist_node used क्रम temporary storage
 * @member: the name of the hlist_node within the काष्ठा
 * @key: the key of the objects to iterate over
 */
#घोषणा hash_क्रम_each_possible_safe(name, obj, पंचांगp, member, key)	\
	hlist_क्रम_each_entry_safe(obj, पंचांगp,\
		&name[hash_min(key, HASH_BITS(name))], member)


#पूर्ण_अगर
