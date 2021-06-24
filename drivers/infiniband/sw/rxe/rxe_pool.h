<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#अगर_अघोषित RXE_POOL_H
#घोषणा RXE_POOL_H

#घोषणा RXE_POOL_ALIGN		(16)
#घोषणा RXE_POOL_CACHE_FLAGS	(0)

क्रमागत rxe_pool_flags अणु
	RXE_POOL_INDEX		= BIT(1),
	RXE_POOL_KEY		= BIT(2),
	RXE_POOL_NO_ALLOC	= BIT(4),
पूर्ण;

क्रमागत rxe_elem_type अणु
	RXE_TYPE_UC,
	RXE_TYPE_PD,
	RXE_TYPE_AH,
	RXE_TYPE_SRQ,
	RXE_TYPE_QP,
	RXE_TYPE_CQ,
	RXE_TYPE_MR,
	RXE_TYPE_MW,
	RXE_TYPE_MC_GRP,
	RXE_TYPE_MC_ELEM,
	RXE_NUM_TYPES,		/* keep me last */
पूर्ण;

काष्ठा rxe_pool_entry;

काष्ठा rxe_type_info अणु
	स्थिर अक्षर		*name;
	माप_प्रकार			size;
	माप_प्रकार			elem_offset;
	व्योम			(*cleanup)(काष्ठा rxe_pool_entry *obj);
	क्रमागत rxe_pool_flags	flags;
	u32			max_index;
	u32			min_index;
	माप_प्रकार			key_offset;
	माप_प्रकार			key_size;
पूर्ण;

बाह्य काष्ठा rxe_type_info rxe_type_info[];

काष्ठा rxe_pool_entry अणु
	काष्ठा rxe_pool		*pool;
	काष्ठा kref		ref_cnt;
	काष्ठा list_head	list;

	/* only used अगर keyed */
	काष्ठा rb_node		key_node;

	/* only used अगर indexed */
	काष्ठा rb_node		index_node;
	u32			index;
पूर्ण;

काष्ठा rxe_pool अणु
	काष्ठा rxe_dev		*rxe;
	rwlock_t		pool_lock; /* protects pool add/del/search */
	माप_प्रकार			elem_size;
	व्योम			(*cleanup)(काष्ठा rxe_pool_entry *obj);
	क्रमागत rxe_pool_flags	flags;
	क्रमागत rxe_elem_type	type;

	अचिन्हित पूर्णांक		max_elem;
	atomic_t		num_elem;

	/* only used अगर indexed */
	काष्ठा अणु
		काष्ठा rb_root		tree;
		अचिन्हित दीर्घ		*table;
		माप_प्रकार			table_size;
		u32			last;
		u32			max_index;
		u32			min_index;
	पूर्ण index;

	/* only used अगर keyed */
	काष्ठा अणु
		काष्ठा rb_root		tree;
		माप_प्रकार			key_offset;
		माप_प्रकार			key_size;
	पूर्ण key;
पूर्ण;

/* initialize a pool of objects with given limit on
 * number of elements. माला_लो parameters from rxe_type_info
 * pool elements will be allocated out of a slab cache
 */
पूर्णांक rxe_pool_init(काष्ठा rxe_dev *rxe, काष्ठा rxe_pool *pool,
		  क्रमागत rxe_elem_type type, u32 max_elem);

/* मुक्त resources from object pool */
व्योम rxe_pool_cleanup(काष्ठा rxe_pool *pool);

/* allocate an object from pool holding and not holding the pool lock */
व्योम *rxe_alloc_locked(काष्ठा rxe_pool *pool);

व्योम *rxe_alloc(काष्ठा rxe_pool *pool);

/* connect alपढ़ोy allocated object to pool */
पूर्णांक __rxe_add_to_pool(काष्ठा rxe_pool *pool, काष्ठा rxe_pool_entry *elem);

#घोषणा rxe_add_to_pool(pool, obj) __rxe_add_to_pool(pool, &(obj)->pelem)

/* assign an index to an indexed object and insert object पूर्णांकo
 *  pool's rb tree holding and not holding the pool_lock
 */
व्योम __rxe_add_index_locked(काष्ठा rxe_pool_entry *elem);

#घोषणा rxe_add_index_locked(obj) __rxe_add_index_locked(&(obj)->pelem)

व्योम __rxe_add_index(काष्ठा rxe_pool_entry *elem);

#घोषणा rxe_add_index(obj) __rxe_add_index(&(obj)->pelem)

/* drop an index and हटाओ object from rb tree
 * holding and not holding the pool_lock
 */
व्योम __rxe_drop_index_locked(काष्ठा rxe_pool_entry *elem);

#घोषणा rxe_drop_index_locked(obj) __rxe_drop_index_locked(&(obj)->pelem)

व्योम __rxe_drop_index(काष्ठा rxe_pool_entry *elem);

#घोषणा rxe_drop_index(obj) __rxe_drop_index(&(obj)->pelem)

/* assign a key to a keyed object and insert object पूर्णांकo
 * pool's rb tree holding and not holding pool_lock
 */
व्योम __rxe_add_key_locked(काष्ठा rxe_pool_entry *elem, व्योम *key);

#घोषणा rxe_add_key_locked(obj, key) __rxe_add_key_locked(&(obj)->pelem, key)

व्योम __rxe_add_key(काष्ठा rxe_pool_entry *elem, व्योम *key);

#घोषणा rxe_add_key(obj, key) __rxe_add_key(&(obj)->pelem, key)

/* हटाओ elem from rb tree holding and not holding the pool_lock */
व्योम __rxe_drop_key_locked(काष्ठा rxe_pool_entry *elem);

#घोषणा rxe_drop_key_locked(obj) __rxe_drop_key_locked(&(obj)->pelem)

व्योम __rxe_drop_key(काष्ठा rxe_pool_entry *elem);

#घोषणा rxe_drop_key(obj) __rxe_drop_key(&(obj)->pelem)

/* lookup an indexed object from index holding and not holding the pool_lock.
 * takes a reference on object
 */
व्योम *rxe_pool_get_index_locked(काष्ठा rxe_pool *pool, u32 index);

व्योम *rxe_pool_get_index(काष्ठा rxe_pool *pool, u32 index);

/* lookup keyed object from key holding and not holding the pool_lock.
 * takes a reference on the objecti
 */
व्योम *rxe_pool_get_key_locked(काष्ठा rxe_pool *pool, व्योम *key);

व्योम *rxe_pool_get_key(काष्ठा rxe_pool *pool, व्योम *key);

/* cleanup an object when all references are dropped */
व्योम rxe_elem_release(काष्ठा kref *kref);

/* take a reference on an object */
#घोषणा rxe_add_ref(elem) kref_get(&(elem)->pelem.ref_cnt)

/* drop a reference on an object */
#घोषणा rxe_drop_ref(elem) kref_put(&(elem)->pelem.ref_cnt, rxe_elem_release)

#पूर्ण_अगर /* RXE_POOL_H */
