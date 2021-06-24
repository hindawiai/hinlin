<शैली गुरु>
/*
 * Copyright (C) 2012-2017 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm.h"
#समावेश "dm-bio-prison-v2.h"

#समावेश <linux/spinlock.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/rwsem.h>

/*----------------------------------------------------------------*/

#घोषणा MIN_CELLS 1024

काष्ठा dm_bio_prison_v2 अणु
	काष्ठा workqueue_काष्ठा *wq;

	spinlock_t lock;
	काष्ठा rb_root cells;
	mempool_t cell_pool;
पूर्ण;

अटल काष्ठा kmem_cache *_cell_cache;

/*----------------------------------------------------------------*/

/*
 * @nr_cells should be the number of cells you want in use _concurrently_.
 * Don't confuse it with the number of distinct keys.
 */
काष्ठा dm_bio_prison_v2 *dm_bio_prison_create_v2(काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा dm_bio_prison_v2 *prison = kzalloc(माप(*prison), GFP_KERNEL);
	पूर्णांक ret;

	अगर (!prison)
		वापस शून्य;

	prison->wq = wq;
	spin_lock_init(&prison->lock);

	ret = mempool_init_slab_pool(&prison->cell_pool, MIN_CELLS, _cell_cache);
	अगर (ret) अणु
		kमुक्त(prison);
		वापस शून्य;
	पूर्ण

	prison->cells = RB_ROOT;

	वापस prison;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_prison_create_v2);

व्योम dm_bio_prison_destroy_v2(काष्ठा dm_bio_prison_v2 *prison)
अणु
	mempool_निकास(&prison->cell_pool);
	kमुक्त(prison);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_prison_destroy_v2);

काष्ठा dm_bio_prison_cell_v2 *dm_bio_prison_alloc_cell_v2(काष्ठा dm_bio_prison_v2 *prison, gfp_t gfp)
अणु
	वापस mempool_alloc(&prison->cell_pool, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_prison_alloc_cell_v2);

व्योम dm_bio_prison_मुक्त_cell_v2(काष्ठा dm_bio_prison_v2 *prison,
				काष्ठा dm_bio_prison_cell_v2 *cell)
अणु
	mempool_मुक्त(cell, &prison->cell_pool);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_prison_मुक्त_cell_v2);

अटल व्योम __setup_new_cell(काष्ठा dm_cell_key_v2 *key,
			     काष्ठा dm_bio_prison_cell_v2 *cell)
अणु
	स_रखो(cell, 0, माप(*cell));
	स_नकल(&cell->key, key, माप(cell->key));
	bio_list_init(&cell->bios);
पूर्ण

अटल पूर्णांक cmp_keys(काष्ठा dm_cell_key_v2 *lhs,
		    काष्ठा dm_cell_key_v2 *rhs)
अणु
	अगर (lhs->भव < rhs->भव)
		वापस -1;

	अगर (lhs->भव > rhs->भव)
		वापस 1;

	अगर (lhs->dev < rhs->dev)
		वापस -1;

	अगर (lhs->dev > rhs->dev)
		वापस 1;

	अगर (lhs->block_end <= rhs->block_begin)
		वापस -1;

	अगर (lhs->block_begin >= rhs->block_end)
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Returns true अगर node found, otherwise it inserts a new one.
 */
अटल bool __find_or_insert(काष्ठा dm_bio_prison_v2 *prison,
			     काष्ठा dm_cell_key_v2 *key,
			     काष्ठा dm_bio_prison_cell_v2 *cell_pपुनः_स्मृति,
			     काष्ठा dm_bio_prison_cell_v2 **result)
अणु
	पूर्णांक r;
	काष्ठा rb_node **new = &prison->cells.rb_node, *parent = शून्य;

	जबतक (*new) अणु
		काष्ठा dm_bio_prison_cell_v2 *cell =
			rb_entry(*new, काष्ठा dm_bio_prison_cell_v2, node);

		r = cmp_keys(key, &cell->key);

		parent = *new;
		अगर (r < 0)
			new = &((*new)->rb_left);

		अन्यथा अगर (r > 0)
			new = &((*new)->rb_right);

		अन्यथा अणु
			*result = cell;
			वापस true;
		पूर्ण
	पूर्ण

	__setup_new_cell(key, cell_pपुनः_स्मृति);
	*result = cell_pपुनः_स्मृति;
	rb_link_node(&cell_pपुनः_स्मृति->node, parent, new);
	rb_insert_color(&cell_pपुनः_स्मृति->node, &prison->cells);

	वापस false;
पूर्ण

अटल bool __get(काष्ठा dm_bio_prison_v2 *prison,
		  काष्ठा dm_cell_key_v2 *key,
		  अचिन्हित lock_level,
		  काष्ठा bio *inmate,
		  काष्ठा dm_bio_prison_cell_v2 *cell_pपुनः_स्मृति,
		  काष्ठा dm_bio_prison_cell_v2 **cell)
अणु
	अगर (__find_or_insert(prison, key, cell_pपुनः_स्मृति, cell)) अणु
		अगर ((*cell)->exclusive_lock) अणु
			अगर (lock_level <= (*cell)->exclusive_level) अणु
				bio_list_add(&(*cell)->bios, inmate);
				वापस false;
			पूर्ण
		पूर्ण

		(*cell)->shared_count++;

	पूर्ण अन्यथा
		(*cell)->shared_count = 1;

	वापस true;
पूर्ण

bool dm_cell_get_v2(काष्ठा dm_bio_prison_v2 *prison,
		    काष्ठा dm_cell_key_v2 *key,
		    अचिन्हित lock_level,
		    काष्ठा bio *inmate,
		    काष्ठा dm_bio_prison_cell_v2 *cell_pपुनः_स्मृति,
		    काष्ठा dm_bio_prison_cell_v2 **cell_result)
अणु
	पूर्णांक r;

	spin_lock_irq(&prison->lock);
	r = __get(prison, key, lock_level, inmate, cell_pपुनः_स्मृति, cell_result);
	spin_unlock_irq(&prison->lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_get_v2);

अटल bool __put(काष्ठा dm_bio_prison_v2 *prison,
		  काष्ठा dm_bio_prison_cell_v2 *cell)
अणु
	BUG_ON(!cell->shared_count);
	cell->shared_count--;

	// FIXME: shared locks granted above the lock level could starve this
	अगर (!cell->shared_count) अणु
		अगर (cell->exclusive_lock)अणु
			अगर (cell->quiesce_continuation) अणु
				queue_work(prison->wq, cell->quiesce_continuation);
				cell->quiesce_continuation = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			rb_erase(&cell->node, &prison->cells);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

bool dm_cell_put_v2(काष्ठा dm_bio_prison_v2 *prison,
		    काष्ठा dm_bio_prison_cell_v2 *cell)
अणु
	bool r;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&prison->lock, flags);
	r = __put(prison, cell);
	spin_unlock_irqrestore(&prison->lock, flags);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_put_v2);

अटल पूर्णांक __lock(काष्ठा dm_bio_prison_v2 *prison,
		  काष्ठा dm_cell_key_v2 *key,
		  अचिन्हित lock_level,
		  काष्ठा dm_bio_prison_cell_v2 *cell_pपुनः_स्मृति,
		  काष्ठा dm_bio_prison_cell_v2 **cell_result)
अणु
	काष्ठा dm_bio_prison_cell_v2 *cell;

	अगर (__find_or_insert(prison, key, cell_pपुनः_स्मृति, &cell)) अणु
		अगर (cell->exclusive_lock)
			वापस -EBUSY;

		cell->exclusive_lock = true;
		cell->exclusive_level = lock_level;
		*cell_result = cell;

		// FIXME: we करोn't yet know what level these shared locks
		// were taken at, so have to quiesce them all.
		वापस cell->shared_count > 0;

	पूर्ण अन्यथा अणु
		cell = cell_pपुनः_स्मृति;
		cell->shared_count = 0;
		cell->exclusive_lock = true;
		cell->exclusive_level = lock_level;
		*cell_result = cell;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dm_cell_lock_v2(काष्ठा dm_bio_prison_v2 *prison,
		    काष्ठा dm_cell_key_v2 *key,
		    अचिन्हित lock_level,
		    काष्ठा dm_bio_prison_cell_v2 *cell_pपुनः_स्मृति,
		    काष्ठा dm_bio_prison_cell_v2 **cell_result)
अणु
	पूर्णांक r;

	spin_lock_irq(&prison->lock);
	r = __lock(prison, key, lock_level, cell_pपुनः_स्मृति, cell_result);
	spin_unlock_irq(&prison->lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_lock_v2);

अटल व्योम __quiesce(काष्ठा dm_bio_prison_v2 *prison,
		      काष्ठा dm_bio_prison_cell_v2 *cell,
		      काष्ठा work_काष्ठा *continuation)
अणु
	अगर (!cell->shared_count)
		queue_work(prison->wq, continuation);
	अन्यथा
		cell->quiesce_continuation = continuation;
पूर्ण

व्योम dm_cell_quiesce_v2(काष्ठा dm_bio_prison_v2 *prison,
			काष्ठा dm_bio_prison_cell_v2 *cell,
			काष्ठा work_काष्ठा *continuation)
अणु
	spin_lock_irq(&prison->lock);
	__quiesce(prison, cell, continuation);
	spin_unlock_irq(&prison->lock);
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_quiesce_v2);

अटल पूर्णांक __promote(काष्ठा dm_bio_prison_v2 *prison,
		     काष्ठा dm_bio_prison_cell_v2 *cell,
		     अचिन्हित new_lock_level)
अणु
	अगर (!cell->exclusive_lock)
		वापस -EINVAL;

	cell->exclusive_level = new_lock_level;
	वापस cell->shared_count > 0;
पूर्ण

पूर्णांक dm_cell_lock_promote_v2(काष्ठा dm_bio_prison_v2 *prison,
			    काष्ठा dm_bio_prison_cell_v2 *cell,
			    अचिन्हित new_lock_level)
अणु
	पूर्णांक r;

	spin_lock_irq(&prison->lock);
	r = __promote(prison, cell, new_lock_level);
	spin_unlock_irq(&prison->lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_lock_promote_v2);

अटल bool __unlock(काष्ठा dm_bio_prison_v2 *prison,
		     काष्ठा dm_bio_prison_cell_v2 *cell,
		     काष्ठा bio_list *bios)
अणु
	BUG_ON(!cell->exclusive_lock);

	bio_list_merge(bios, &cell->bios);
	bio_list_init(&cell->bios);

	अगर (cell->shared_count) अणु
		cell->exclusive_lock = false;
		वापस false;
	पूर्ण

	rb_erase(&cell->node, &prison->cells);
	वापस true;
पूर्ण

bool dm_cell_unlock_v2(काष्ठा dm_bio_prison_v2 *prison,
		       काष्ठा dm_bio_prison_cell_v2 *cell,
		       काष्ठा bio_list *bios)
अणु
	bool r;

	spin_lock_irq(&prison->lock);
	r = __unlock(prison, cell, bios);
	spin_unlock_irq(&prison->lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_unlock_v2);

/*----------------------------------------------------------------*/

पूर्णांक __init dm_bio_prison_init_v2(व्योम)
अणु
	_cell_cache = KMEM_CACHE(dm_bio_prison_cell_v2, 0);
	अगर (!_cell_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम dm_bio_prison_निकास_v2(व्योम)
अणु
	kmem_cache_destroy(_cell_cache);
	_cell_cache = शून्य;
पूर्ण
