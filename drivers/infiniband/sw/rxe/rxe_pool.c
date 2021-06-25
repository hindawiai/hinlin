<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश "rxe.h"
#समावेश "rxe_loc.h"

/* info about object pools
 */
काष्ठा rxe_type_info rxe_type_info[RXE_NUM_TYPES] = अणु
	[RXE_TYPE_UC] = अणु
		.name		= "rxe-uc",
		.size		= माप(काष्ठा rxe_ucontext),
		.elem_offset	= दुरत्व(काष्ठा rxe_ucontext, pelem),
		.flags          = RXE_POOL_NO_ALLOC,
	पूर्ण,
	[RXE_TYPE_PD] = अणु
		.name		= "rxe-pd",
		.size		= माप(काष्ठा rxe_pd),
		.elem_offset	= दुरत्व(काष्ठा rxe_pd, pelem),
		.flags		= RXE_POOL_NO_ALLOC,
	पूर्ण,
	[RXE_TYPE_AH] = अणु
		.name		= "rxe-ah",
		.size		= माप(काष्ठा rxe_ah),
		.elem_offset	= दुरत्व(काष्ठा rxe_ah, pelem),
		.flags		= RXE_POOL_NO_ALLOC,
	पूर्ण,
	[RXE_TYPE_SRQ] = अणु
		.name		= "rxe-srq",
		.size		= माप(काष्ठा rxe_srq),
		.elem_offset	= दुरत्व(काष्ठा rxe_srq, pelem),
		.flags		= RXE_POOL_INDEX | RXE_POOL_NO_ALLOC,
		.min_index	= RXE_MIN_SRQ_INDEX,
		.max_index	= RXE_MAX_SRQ_INDEX,
	पूर्ण,
	[RXE_TYPE_QP] = अणु
		.name		= "rxe-qp",
		.size		= माप(काष्ठा rxe_qp),
		.elem_offset	= दुरत्व(काष्ठा rxe_qp, pelem),
		.cleanup	= rxe_qp_cleanup,
		.flags		= RXE_POOL_INDEX,
		.min_index	= RXE_MIN_QP_INDEX,
		.max_index	= RXE_MAX_QP_INDEX,
	पूर्ण,
	[RXE_TYPE_CQ] = अणु
		.name		= "rxe-cq",
		.size		= माप(काष्ठा rxe_cq),
		.elem_offset	= दुरत्व(काष्ठा rxe_cq, pelem),
		.flags          = RXE_POOL_NO_ALLOC,
		.cleanup	= rxe_cq_cleanup,
	पूर्ण,
	[RXE_TYPE_MR] = अणु
		.name		= "rxe-mr",
		.size		= माप(काष्ठा rxe_mr),
		.elem_offset	= दुरत्व(काष्ठा rxe_mr, pelem),
		.cleanup	= rxe_mr_cleanup,
		.flags		= RXE_POOL_INDEX,
		.max_index	= RXE_MAX_MR_INDEX,
		.min_index	= RXE_MIN_MR_INDEX,
	पूर्ण,
	[RXE_TYPE_MW] = अणु
		.name		= "rxe-mw",
		.size		= माप(काष्ठा rxe_mw),
		.elem_offset	= दुरत्व(काष्ठा rxe_mw, pelem),
		.flags		= RXE_POOL_INDEX | RXE_POOL_NO_ALLOC,
		.max_index	= RXE_MAX_MW_INDEX,
		.min_index	= RXE_MIN_MW_INDEX,
	पूर्ण,
	[RXE_TYPE_MC_GRP] = अणु
		.name		= "rxe-mc_grp",
		.size		= माप(काष्ठा rxe_mc_grp),
		.elem_offset	= दुरत्व(काष्ठा rxe_mc_grp, pelem),
		.cleanup	= rxe_mc_cleanup,
		.flags		= RXE_POOL_KEY,
		.key_offset	= दुरत्व(काष्ठा rxe_mc_grp, mgid),
		.key_size	= माप(जोड़ ib_gid),
	पूर्ण,
	[RXE_TYPE_MC_ELEM] = अणु
		.name		= "rxe-mc_elem",
		.size		= माप(काष्ठा rxe_mc_elem),
		.elem_offset	= दुरत्व(काष्ठा rxe_mc_elem, pelem),
	पूर्ण,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *pool_name(काष्ठा rxe_pool *pool)
अणु
	वापस rxe_type_info[pool->type].name;
पूर्ण

अटल पूर्णांक rxe_pool_init_index(काष्ठा rxe_pool *pool, u32 max, u32 min)
अणु
	पूर्णांक err = 0;
	माप_प्रकार size;

	अगर ((max - min + 1) < pool->max_elem) अणु
		pr_warn("not enough indices for max_elem\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	pool->index.max_index = max;
	pool->index.min_index = min;

	size = BITS_TO_LONGS(max - min + 1) * माप(दीर्घ);
	pool->index.table = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!pool->index.table) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	pool->index.table_size = size;
	biपंचांगap_zero(pool->index.table, max - min + 1);

out:
	वापस err;
पूर्ण

पूर्णांक rxe_pool_init(
	काष्ठा rxe_dev		*rxe,
	काष्ठा rxe_pool		*pool,
	क्रमागत rxe_elem_type	type,
	अचिन्हित पूर्णांक		max_elem)
अणु
	पूर्णांक			err = 0;
	माप_प्रकार			size = rxe_type_info[type].size;

	स_रखो(pool, 0, माप(*pool));

	pool->rxe		= rxe;
	pool->type		= type;
	pool->max_elem		= max_elem;
	pool->elem_size		= ALIGN(size, RXE_POOL_ALIGN);
	pool->flags		= rxe_type_info[type].flags;
	pool->index.tree	= RB_ROOT;
	pool->key.tree		= RB_ROOT;
	pool->cleanup		= rxe_type_info[type].cleanup;

	atomic_set(&pool->num_elem, 0);

	rwlock_init(&pool->pool_lock);

	अगर (rxe_type_info[type].flags & RXE_POOL_INDEX) अणु
		err = rxe_pool_init_index(pool,
					  rxe_type_info[type].max_index,
					  rxe_type_info[type].min_index);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (rxe_type_info[type].flags & RXE_POOL_KEY) अणु
		pool->key.key_offset = rxe_type_info[type].key_offset;
		pool->key.key_size = rxe_type_info[type].key_size;
	पूर्ण

out:
	वापस err;
पूर्ण

व्योम rxe_pool_cleanup(काष्ठा rxe_pool *pool)
अणु
	अगर (atomic_पढ़ो(&pool->num_elem) > 0)
		pr_warn("%s pool destroyed with unfree'd elem\n",
			pool_name(pool));

	kमुक्त(pool->index.table);
पूर्ण

अटल u32 alloc_index(काष्ठा rxe_pool *pool)
अणु
	u32 index;
	u32 range = pool->index.max_index - pool->index.min_index + 1;

	index = find_next_zero_bit(pool->index.table, range, pool->index.last);
	अगर (index >= range)
		index = find_first_zero_bit(pool->index.table, range);

	WARN_ON_ONCE(index >= range);
	set_bit(index, pool->index.table);
	pool->index.last = index;
	वापस index + pool->index.min_index;
पूर्ण

अटल व्योम insert_index(काष्ठा rxe_pool *pool, काष्ठा rxe_pool_entry *new)
अणु
	काष्ठा rb_node **link = &pool->index.tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rxe_pool_entry *elem;

	जबतक (*link) अणु
		parent = *link;
		elem = rb_entry(parent, काष्ठा rxe_pool_entry, index_node);

		अगर (elem->index == new->index) अणु
			pr_warn("element already exists!\n");
			जाओ out;
		पूर्ण

		अगर (elem->index > new->index)
			link = &(*link)->rb_left;
		अन्यथा
			link = &(*link)->rb_right;
	पूर्ण

	rb_link_node(&new->index_node, parent, link);
	rb_insert_color(&new->index_node, &pool->index.tree);
out:
	वापस;
पूर्ण

अटल व्योम insert_key(काष्ठा rxe_pool *pool, काष्ठा rxe_pool_entry *new)
अणु
	काष्ठा rb_node **link = &pool->key.tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rxe_pool_entry *elem;
	पूर्णांक cmp;

	जबतक (*link) अणु
		parent = *link;
		elem = rb_entry(parent, काष्ठा rxe_pool_entry, key_node);

		cmp = स_भेद((u8 *)elem + pool->key.key_offset,
			     (u8 *)new + pool->key.key_offset, pool->key.key_size);

		अगर (cmp == 0) अणु
			pr_warn("key already exists!\n");
			जाओ out;
		पूर्ण

		अगर (cmp > 0)
			link = &(*link)->rb_left;
		अन्यथा
			link = &(*link)->rb_right;
	पूर्ण

	rb_link_node(&new->key_node, parent, link);
	rb_insert_color(&new->key_node, &pool->key.tree);
out:
	वापस;
पूर्ण

व्योम __rxe_add_key_locked(काष्ठा rxe_pool_entry *elem, व्योम *key)
अणु
	काष्ठा rxe_pool *pool = elem->pool;

	स_नकल((u8 *)elem + pool->key.key_offset, key, pool->key.key_size);
	insert_key(pool, elem);
पूर्ण

व्योम __rxe_add_key(काष्ठा rxe_pool_entry *elem, व्योम *key)
अणु
	काष्ठा rxe_pool *pool = elem->pool;
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&pool->pool_lock, flags);
	__rxe_add_key_locked(elem, key);
	ग_लिखो_unlock_irqrestore(&pool->pool_lock, flags);
पूर्ण

व्योम __rxe_drop_key_locked(काष्ठा rxe_pool_entry *elem)
अणु
	काष्ठा rxe_pool *pool = elem->pool;

	rb_erase(&elem->key_node, &pool->key.tree);
पूर्ण

व्योम __rxe_drop_key(काष्ठा rxe_pool_entry *elem)
अणु
	काष्ठा rxe_pool *pool = elem->pool;
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&pool->pool_lock, flags);
	__rxe_drop_key_locked(elem);
	ग_लिखो_unlock_irqrestore(&pool->pool_lock, flags);
पूर्ण

व्योम __rxe_add_index_locked(काष्ठा rxe_pool_entry *elem)
अणु
	काष्ठा rxe_pool *pool = elem->pool;

	elem->index = alloc_index(pool);
	insert_index(pool, elem);
पूर्ण

व्योम __rxe_add_index(काष्ठा rxe_pool_entry *elem)
अणु
	काष्ठा rxe_pool *pool = elem->pool;
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&pool->pool_lock, flags);
	__rxe_add_index_locked(elem);
	ग_लिखो_unlock_irqrestore(&pool->pool_lock, flags);
पूर्ण

व्योम __rxe_drop_index_locked(काष्ठा rxe_pool_entry *elem)
अणु
	काष्ठा rxe_pool *pool = elem->pool;

	clear_bit(elem->index - pool->index.min_index, pool->index.table);
	rb_erase(&elem->index_node, &pool->index.tree);
पूर्ण

व्योम __rxe_drop_index(काष्ठा rxe_pool_entry *elem)
अणु
	काष्ठा rxe_pool *pool = elem->pool;
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&pool->pool_lock, flags);
	__rxe_drop_index_locked(elem);
	ग_लिखो_unlock_irqrestore(&pool->pool_lock, flags);
पूर्ण

व्योम *rxe_alloc_locked(काष्ठा rxe_pool *pool)
अणु
	काष्ठा rxe_type_info *info = &rxe_type_info[pool->type];
	काष्ठा rxe_pool_entry *elem;
	u8 *obj;

	अगर (atomic_inc_वापस(&pool->num_elem) > pool->max_elem)
		जाओ out_cnt;

	obj = kzalloc(info->size, GFP_ATOMIC);
	अगर (!obj)
		जाओ out_cnt;

	elem = (काष्ठा rxe_pool_entry *)(obj + info->elem_offset);

	elem->pool = pool;
	kref_init(&elem->ref_cnt);

	वापस obj;

out_cnt:
	atomic_dec(&pool->num_elem);
	वापस शून्य;
पूर्ण

व्योम *rxe_alloc(काष्ठा rxe_pool *pool)
अणु
	काष्ठा rxe_type_info *info = &rxe_type_info[pool->type];
	काष्ठा rxe_pool_entry *elem;
	u8 *obj;

	अगर (atomic_inc_वापस(&pool->num_elem) > pool->max_elem)
		जाओ out_cnt;

	obj = kzalloc(info->size, GFP_KERNEL);
	अगर (!obj)
		जाओ out_cnt;

	elem = (काष्ठा rxe_pool_entry *)(obj + info->elem_offset);

	elem->pool = pool;
	kref_init(&elem->ref_cnt);

	वापस obj;

out_cnt:
	atomic_dec(&pool->num_elem);
	वापस शून्य;
पूर्ण

पूर्णांक __rxe_add_to_pool(काष्ठा rxe_pool *pool, काष्ठा rxe_pool_entry *elem)
अणु
	अगर (atomic_inc_वापस(&pool->num_elem) > pool->max_elem)
		जाओ out_cnt;

	elem->pool = pool;
	kref_init(&elem->ref_cnt);

	वापस 0;

out_cnt:
	atomic_dec(&pool->num_elem);
	वापस -EINVAL;
पूर्ण

व्योम rxe_elem_release(काष्ठा kref *kref)
अणु
	काष्ठा rxe_pool_entry *elem =
		container_of(kref, काष्ठा rxe_pool_entry, ref_cnt);
	काष्ठा rxe_pool *pool = elem->pool;
	काष्ठा rxe_type_info *info = &rxe_type_info[pool->type];
	u8 *obj;

	अगर (pool->cleanup)
		pool->cleanup(elem);

	अगर (!(pool->flags & RXE_POOL_NO_ALLOC)) अणु
		obj = (u8 *)elem - info->elem_offset;
		kमुक्त(obj);
	पूर्ण

	atomic_dec(&pool->num_elem);
पूर्ण

व्योम *rxe_pool_get_index_locked(काष्ठा rxe_pool *pool, u32 index)
अणु
	काष्ठा rxe_type_info *info = &rxe_type_info[pool->type];
	काष्ठा rb_node *node;
	काष्ठा rxe_pool_entry *elem;
	u8 *obj;

	node = pool->index.tree.rb_node;

	जबतक (node) अणु
		elem = rb_entry(node, काष्ठा rxe_pool_entry, index_node);

		अगर (elem->index > index)
			node = node->rb_left;
		अन्यथा अगर (elem->index < index)
			node = node->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (node) अणु
		kref_get(&elem->ref_cnt);
		obj = (u8 *)elem - info->elem_offset;
	पूर्ण अन्यथा अणु
		obj = शून्य;
	पूर्ण

	वापस obj;
पूर्ण

व्योम *rxe_pool_get_index(काष्ठा rxe_pool *pool, u32 index)
अणु
	u8 *obj;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&pool->pool_lock, flags);
	obj = rxe_pool_get_index_locked(pool, index);
	पढ़ो_unlock_irqrestore(&pool->pool_lock, flags);

	वापस obj;
पूर्ण

व्योम *rxe_pool_get_key_locked(काष्ठा rxe_pool *pool, व्योम *key)
अणु
	काष्ठा rxe_type_info *info = &rxe_type_info[pool->type];
	काष्ठा rb_node *node;
	काष्ठा rxe_pool_entry *elem;
	u8 *obj;
	पूर्णांक cmp;

	node = pool->key.tree.rb_node;

	जबतक (node) अणु
		elem = rb_entry(node, काष्ठा rxe_pool_entry, key_node);

		cmp = स_भेद((u8 *)elem + pool->key.key_offset,
			     key, pool->key.key_size);

		अगर (cmp > 0)
			node = node->rb_left;
		अन्यथा अगर (cmp < 0)
			node = node->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (node) अणु
		kref_get(&elem->ref_cnt);
		obj = (u8 *)elem - info->elem_offset;
	पूर्ण अन्यथा अणु
		obj = शून्य;
	पूर्ण

	वापस obj;
पूर्ण

व्योम *rxe_pool_get_key(काष्ठा rxe_pool *pool, व्योम *key)
अणु
	u8 *obj;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&pool->pool_lock, flags);
	obj = rxe_pool_get_key_locked(pool, key);
	पढ़ो_unlock_irqrestore(&pool->pool_lock, flags);

	वापस obj;
पूर्ण
