<शैली गुरु>
/*
 * Copyright (C) 2011-2017 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_BIO_PRISON_V2_H
#घोषणा DM_BIO_PRISON_V2_H

#समावेश "persistent-data/dm-block-manager.h" /* FIXME: क्रम dm_block_t */
#समावेश "dm-thin-metadata.h" /* FIXME: क्रम dm_thin_id */

#समावेश <linux/bपन.स>
#समावेश <linux/rbtree.h>
#समावेश <linux/workqueue.h>

/*----------------------------------------------------------------*/

पूर्णांक dm_bio_prison_init_v2(व्योम);
व्योम dm_bio_prison_निकास_v2(व्योम);

/*
 * Someबार we can't deal with a bio straight away.  We put them in prison
 * where they can't cause any mischief.  Bios are put in a cell identअगरied
 * by a key, multiple bios can be in the same cell.  When the cell is
 * subsequently unlocked the bios become available.
 */
काष्ठा dm_bio_prison_v2;

/*
 * Keys define a range of blocks within either a भव or physical
 * device.
 */
काष्ठा dm_cell_key_v2 अणु
	पूर्णांक भव;
	dm_thin_id dev;
	dm_block_t block_begin, block_end;
पूर्ण;

/*
 * Treat this as opaque, only in header so callers can manage allocation
 * themselves.
 */
काष्ठा dm_bio_prison_cell_v2 अणु
	// FIXME: pack these
	bool exclusive_lock;
	अचिन्हित exclusive_level;
	अचिन्हित shared_count;
	काष्ठा work_काष्ठा *quiesce_continuation;

	काष्ठा rb_node node;
	काष्ठा dm_cell_key_v2 key;
	काष्ठा bio_list bios;
पूर्ण;

काष्ठा dm_bio_prison_v2 *dm_bio_prison_create_v2(काष्ठा workqueue_काष्ठा *wq);
व्योम dm_bio_prison_destroy_v2(काष्ठा dm_bio_prison_v2 *prison);

/*
 * These two functions just wrap a mempool.  This is a transitory step:
 * Eventually all bio prison clients should manage their own cell memory.
 *
 * Like mempool_alloc(), dm_bio_prison_alloc_cell_v2() can only fail अगर called
 * in पूर्णांकerrupt context or passed GFP_NOWAIT.
 */
काष्ठा dm_bio_prison_cell_v2 *dm_bio_prison_alloc_cell_v2(काष्ठा dm_bio_prison_v2 *prison,
						    gfp_t gfp);
व्योम dm_bio_prison_मुक्त_cell_v2(काष्ठा dm_bio_prison_v2 *prison,
				काष्ठा dm_bio_prison_cell_v2 *cell);

/*
 * Shared locks have a bio associated with them.
 *
 * If the lock is granted the caller can जारी to use the bio, and must
 * call dm_cell_put_v2() to drop the reference count when finished using it.
 *
 * If the lock cannot be granted then the bio will be tracked within the
 * cell, and later given to the holder of the exclusive lock.
 *
 * See dm_cell_lock_v2() क्रम discussion of the lock_level parameter.
 *
 * Compare *cell_result with cell_pपुनः_स्मृति to see अगर the pपुनः_स्मृति was used.
 * If cell_pपुनः_स्मृति was used then inmate wasn't added to it.
 *
 * Returns true अगर the lock is granted.
 */
bool dm_cell_get_v2(काष्ठा dm_bio_prison_v2 *prison,
		    काष्ठा dm_cell_key_v2 *key,
		    अचिन्हित lock_level,
		    काष्ठा bio *inmate,
		    काष्ठा dm_bio_prison_cell_v2 *cell_pपुनः_स्मृति,
		    काष्ठा dm_bio_prison_cell_v2 **cell_result);

/*
 * Decrement the shared reference count क्रम the lock.  Returns true अगर
 * वापसing ownership of the cell (ie. you should मुक्त it).
 */
bool dm_cell_put_v2(काष्ठा dm_bio_prison_v2 *prison,
		    काष्ठा dm_bio_prison_cell_v2 *cell);

/*
 * Locks a cell.  No associated bio.  Exclusive locks get priority.  These
 * locks स्थिरrain whether the io locks are granted according to level.
 *
 * Shared locks will still be granted अगर the lock_level is > (not = to) the
 * exclusive lock level.
 *
 * If an _exclusive_ lock is alपढ़ोy held then -EBUSY is वापसed.
 *
 * Return values:
 *  < 0 - error
 *  0   - locked; no quiescing needed
 *  1   - locked; quiescing needed
 */
पूर्णांक dm_cell_lock_v2(काष्ठा dm_bio_prison_v2 *prison,
		    काष्ठा dm_cell_key_v2 *key,
		    अचिन्हित lock_level,
		    काष्ठा dm_bio_prison_cell_v2 *cell_pपुनः_स्मृति,
		    काष्ठा dm_bio_prison_cell_v2 **cell_result);

व्योम dm_cell_quiesce_v2(काष्ठा dm_bio_prison_v2 *prison,
			काष्ठा dm_bio_prison_cell_v2 *cell,
			काष्ठा work_काष्ठा *continuation);

/*
 * Promotes an _exclusive_ lock to a higher lock level.
 *
 * Return values:
 *  < 0 - error
 *  0   - promoted; no quiescing needed
 *  1   - promoted; quiescing needed
 */
पूर्णांक dm_cell_lock_promote_v2(काष्ठा dm_bio_prison_v2 *prison,
			    काष्ठा dm_bio_prison_cell_v2 *cell,
			    अचिन्हित new_lock_level);

/*
 * Adds any held bios to the bio list.
 *
 * There may be shared locks still held at this poपूर्णांक even अगर you quiesced
 * (ie. dअगरferent lock levels).
 *
 * Returns true अगर वापसing ownership of the cell (ie. you should मुक्त
 * it).
 */
bool dm_cell_unlock_v2(काष्ठा dm_bio_prison_v2 *prison,
		       काष्ठा dm_bio_prison_cell_v2 *cell,
		       काष्ठा bio_list *bios);

/*----------------------------------------------------------------*/

#पूर्ण_अगर
