<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm.h"
#समावेश "dm-bio-prison-v1.h"
#समावेश "dm-bio-prison-v2.h"

#समावेश <linux/spinlock.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

/*----------------------------------------------------------------*/

#घोषणा MIN_CELLS 1024

काष्ठा dm_bio_prison अणु
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
काष्ठा dm_bio_prison *dm_bio_prison_create(व्योम)
अणु
	काष्ठा dm_bio_prison *prison = kzalloc(माप(*prison), GFP_KERNEL);
	पूर्णांक ret;

	अगर (!prison)
		वापस शून्य;

	spin_lock_init(&prison->lock);

	ret = mempool_init_slab_pool(&prison->cell_pool, MIN_CELLS, _cell_cache);
	अगर (ret) अणु
		kमुक्त(prison);
		वापस शून्य;
	पूर्ण

	prison->cells = RB_ROOT;

	वापस prison;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_prison_create);

व्योम dm_bio_prison_destroy(काष्ठा dm_bio_prison *prison)
अणु
	mempool_निकास(&prison->cell_pool);
	kमुक्त(prison);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_prison_destroy);

काष्ठा dm_bio_prison_cell *dm_bio_prison_alloc_cell(काष्ठा dm_bio_prison *prison, gfp_t gfp)
अणु
	वापस mempool_alloc(&prison->cell_pool, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_prison_alloc_cell);

व्योम dm_bio_prison_मुक्त_cell(काष्ठा dm_bio_prison *prison,
			     काष्ठा dm_bio_prison_cell *cell)
अणु
	mempool_मुक्त(cell, &prison->cell_pool);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_prison_मुक्त_cell);

अटल व्योम __setup_new_cell(काष्ठा dm_cell_key *key,
			     काष्ठा bio *holder,
			     काष्ठा dm_bio_prison_cell *cell)
अणु
       स_नकल(&cell->key, key, माप(cell->key));
       cell->holder = holder;
       bio_list_init(&cell->bios);
पूर्ण

अटल पूर्णांक cmp_keys(काष्ठा dm_cell_key *lhs,
		    काष्ठा dm_cell_key *rhs)
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

अटल पूर्णांक __bio_detain(काष्ठा dm_bio_prison *prison,
			काष्ठा dm_cell_key *key,
			काष्ठा bio *inmate,
			काष्ठा dm_bio_prison_cell *cell_pपुनः_स्मृति,
			काष्ठा dm_bio_prison_cell **cell_result)
अणु
	पूर्णांक r;
	काष्ठा rb_node **new = &prison->cells.rb_node, *parent = शून्य;

	जबतक (*new) अणु
		काष्ठा dm_bio_prison_cell *cell =
			rb_entry(*new, काष्ठा dm_bio_prison_cell, node);

		r = cmp_keys(key, &cell->key);

		parent = *new;
		अगर (r < 0)
			new = &((*new)->rb_left);
		अन्यथा अगर (r > 0)
			new = &((*new)->rb_right);
		अन्यथा अणु
			अगर (inmate)
				bio_list_add(&cell->bios, inmate);
			*cell_result = cell;
			वापस 1;
		पूर्ण
	पूर्ण

	__setup_new_cell(key, inmate, cell_pपुनः_स्मृति);
	*cell_result = cell_pपुनः_स्मृति;

	rb_link_node(&cell_pपुनः_स्मृति->node, parent, new);
	rb_insert_color(&cell_pपुनः_स्मृति->node, &prison->cells);

	वापस 0;
पूर्ण

अटल पूर्णांक bio_detain(काष्ठा dm_bio_prison *prison,
		      काष्ठा dm_cell_key *key,
		      काष्ठा bio *inmate,
		      काष्ठा dm_bio_prison_cell *cell_pपुनः_स्मृति,
		      काष्ठा dm_bio_prison_cell **cell_result)
अणु
	पूर्णांक r;

	spin_lock_irq(&prison->lock);
	r = __bio_detain(prison, key, inmate, cell_pपुनः_स्मृति, cell_result);
	spin_unlock_irq(&prison->lock);

	वापस r;
पूर्ण

पूर्णांक dm_bio_detain(काष्ठा dm_bio_prison *prison,
		  काष्ठा dm_cell_key *key,
		  काष्ठा bio *inmate,
		  काष्ठा dm_bio_prison_cell *cell_pपुनः_स्मृति,
		  काष्ठा dm_bio_prison_cell **cell_result)
अणु
	वापस bio_detain(prison, key, inmate, cell_pपुनः_स्मृति, cell_result);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_detain);

पूर्णांक dm_get_cell(काष्ठा dm_bio_prison *prison,
		काष्ठा dm_cell_key *key,
		काष्ठा dm_bio_prison_cell *cell_pपुनः_स्मृति,
		काष्ठा dm_bio_prison_cell **cell_result)
अणु
	वापस bio_detain(prison, key, शून्य, cell_pपुनः_स्मृति, cell_result);
पूर्ण
EXPORT_SYMBOL_GPL(dm_get_cell);

/*
 * @inmates must have been initialised prior to this call
 */
अटल व्योम __cell_release(काष्ठा dm_bio_prison *prison,
			   काष्ठा dm_bio_prison_cell *cell,
			   काष्ठा bio_list *inmates)
अणु
	rb_erase(&cell->node, &prison->cells);

	अगर (inmates) अणु
		अगर (cell->holder)
			bio_list_add(inmates, cell->holder);
		bio_list_merge(inmates, &cell->bios);
	पूर्ण
पूर्ण

व्योम dm_cell_release(काष्ठा dm_bio_prison *prison,
		     काष्ठा dm_bio_prison_cell *cell,
		     काष्ठा bio_list *bios)
अणु
	spin_lock_irq(&prison->lock);
	__cell_release(prison, cell, bios);
	spin_unlock_irq(&prison->lock);
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_release);

/*
 * Someबार we करोn't want the holder, just the additional bios.
 */
अटल व्योम __cell_release_no_holder(काष्ठा dm_bio_prison *prison,
				     काष्ठा dm_bio_prison_cell *cell,
				     काष्ठा bio_list *inmates)
अणु
	rb_erase(&cell->node, &prison->cells);
	bio_list_merge(inmates, &cell->bios);
पूर्ण

व्योम dm_cell_release_no_holder(काष्ठा dm_bio_prison *prison,
			       काष्ठा dm_bio_prison_cell *cell,
			       काष्ठा bio_list *inmates)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&prison->lock, flags);
	__cell_release_no_holder(prison, cell, inmates);
	spin_unlock_irqrestore(&prison->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_release_no_holder);

व्योम dm_cell_error(काष्ठा dm_bio_prison *prison,
		   काष्ठा dm_bio_prison_cell *cell, blk_status_t error)
अणु
	काष्ठा bio_list bios;
	काष्ठा bio *bio;

	bio_list_init(&bios);
	dm_cell_release(prison, cell, &bios);

	जबतक ((bio = bio_list_pop(&bios))) अणु
		bio->bi_status = error;
		bio_endio(bio);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_error);

व्योम dm_cell_visit_release(काष्ठा dm_bio_prison *prison,
			   व्योम (*visit_fn)(व्योम *, काष्ठा dm_bio_prison_cell *),
			   व्योम *context,
			   काष्ठा dm_bio_prison_cell *cell)
अणु
	spin_lock_irq(&prison->lock);
	visit_fn(context, cell);
	rb_erase(&cell->node, &prison->cells);
	spin_unlock_irq(&prison->lock);
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_visit_release);

अटल पूर्णांक __promote_or_release(काष्ठा dm_bio_prison *prison,
				काष्ठा dm_bio_prison_cell *cell)
अणु
	अगर (bio_list_empty(&cell->bios)) अणु
		rb_erase(&cell->node, &prison->cells);
		वापस 1;
	पूर्ण

	cell->holder = bio_list_pop(&cell->bios);
	वापस 0;
पूर्ण

पूर्णांक dm_cell_promote_or_release(काष्ठा dm_bio_prison *prison,
			       काष्ठा dm_bio_prison_cell *cell)
अणु
	पूर्णांक r;

	spin_lock_irq(&prison->lock);
	r = __promote_or_release(prison, cell);
	spin_unlock_irq(&prison->lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cell_promote_or_release);

/*----------------------------------------------------------------*/

#घोषणा DEFERRED_SET_SIZE 64

काष्ठा dm_deferred_entry अणु
	काष्ठा dm_deferred_set *ds;
	अचिन्हित count;
	काष्ठा list_head work_items;
पूर्ण;

काष्ठा dm_deferred_set अणु
	spinlock_t lock;
	अचिन्हित current_entry;
	अचिन्हित sweeper;
	काष्ठा dm_deferred_entry entries[DEFERRED_SET_SIZE];
पूर्ण;

काष्ठा dm_deferred_set *dm_deferred_set_create(व्योम)
अणु
	पूर्णांक i;
	काष्ठा dm_deferred_set *ds;

	ds = kदो_स्मृति(माप(*ds), GFP_KERNEL);
	अगर (!ds)
		वापस शून्य;

	spin_lock_init(&ds->lock);
	ds->current_entry = 0;
	ds->sweeper = 0;
	क्रम (i = 0; i < DEFERRED_SET_SIZE; i++) अणु
		ds->entries[i].ds = ds;
		ds->entries[i].count = 0;
		INIT_LIST_HEAD(&ds->entries[i].work_items);
	पूर्ण

	वापस ds;
पूर्ण
EXPORT_SYMBOL_GPL(dm_deferred_set_create);

व्योम dm_deferred_set_destroy(काष्ठा dm_deferred_set *ds)
अणु
	kमुक्त(ds);
पूर्ण
EXPORT_SYMBOL_GPL(dm_deferred_set_destroy);

काष्ठा dm_deferred_entry *dm_deferred_entry_inc(काष्ठा dm_deferred_set *ds)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dm_deferred_entry *entry;

	spin_lock_irqsave(&ds->lock, flags);
	entry = ds->entries + ds->current_entry;
	entry->count++;
	spin_unlock_irqrestore(&ds->lock, flags);

	वापस entry;
पूर्ण
EXPORT_SYMBOL_GPL(dm_deferred_entry_inc);

अटल अचिन्हित ds_next(अचिन्हित index)
अणु
	वापस (index + 1) % DEFERRED_SET_SIZE;
पूर्ण

अटल व्योम __sweep(काष्ठा dm_deferred_set *ds, काष्ठा list_head *head)
अणु
	जबतक ((ds->sweeper != ds->current_entry) &&
	       !ds->entries[ds->sweeper].count) अणु
		list_splice_init(&ds->entries[ds->sweeper].work_items, head);
		ds->sweeper = ds_next(ds->sweeper);
	पूर्ण

	अगर ((ds->sweeper == ds->current_entry) && !ds->entries[ds->sweeper].count)
		list_splice_init(&ds->entries[ds->sweeper].work_items, head);
पूर्ण

व्योम dm_deferred_entry_dec(काष्ठा dm_deferred_entry *entry, काष्ठा list_head *head)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&entry->ds->lock, flags);
	BUG_ON(!entry->count);
	--entry->count;
	__sweep(entry->ds, head);
	spin_unlock_irqrestore(&entry->ds->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(dm_deferred_entry_dec);

/*
 * Returns 1 अगर deferred or 0 अगर no pending items to delay job.
 */
पूर्णांक dm_deferred_set_add_work(काष्ठा dm_deferred_set *ds, काष्ठा list_head *work)
अणु
	पूर्णांक r = 1;
	अचिन्हित next_entry;

	spin_lock_irq(&ds->lock);
	अगर ((ds->sweeper == ds->current_entry) &&
	    !ds->entries[ds->current_entry].count)
		r = 0;
	अन्यथा अणु
		list_add(work, &ds->entries[ds->current_entry].work_items);
		next_entry = ds_next(ds->current_entry);
		अगर (!ds->entries[next_entry].count)
			ds->current_entry = next_entry;
	पूर्ण
	spin_unlock_irq(&ds->lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_deferred_set_add_work);

/*----------------------------------------------------------------*/

अटल पूर्णांक __init dm_bio_prison_init_v1(व्योम)
अणु
	_cell_cache = KMEM_CACHE(dm_bio_prison_cell, 0);
	अगर (!_cell_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम dm_bio_prison_निकास_v1(व्योम)
अणु
	kmem_cache_destroy(_cell_cache);
	_cell_cache = शून्य;
पूर्ण

अटल पूर्णांक (*_inits[])(व्योम) __initdata = अणु
	dm_bio_prison_init_v1,
	dm_bio_prison_init_v2,
पूर्ण;

अटल व्योम (*_निकासs[])(व्योम) = अणु
	dm_bio_prison_निकास_v1,
	dm_bio_prison_निकास_v2,
पूर्ण;

अटल पूर्णांक __init dm_bio_prison_init(व्योम)
अणु
	स्थिर पूर्णांक count = ARRAY_SIZE(_inits);

	पूर्णांक r, i;

	क्रम (i = 0; i < count; i++) अणु
		r = _inits[i]();
		अगर (r)
			जाओ bad;
	पूर्ण

	वापस 0;

      bad:
	जबतक (i--)
		_निकासs[i]();

	वापस r;
पूर्ण

अटल व्योम __निकास dm_bio_prison_निकास(व्योम)
अणु
	पूर्णांक i = ARRAY_SIZE(_निकासs);

	जबतक (i--)
		_निकासs[i]();
पूर्ण

/*
 * module hooks
 */
module_init(dm_bio_prison_init);
module_निकास(dm_bio_prison_निकास);

MODULE_DESCRIPTION(DM_NAME " bio prison");
MODULE_AUTHOR("Joe Thornber <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
