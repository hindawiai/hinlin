<शैली गुरु>
/*
 * Copyright (C) 2011-2017 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_BIO_PRISON_H
#घोषणा DM_BIO_PRISON_H

#समावेश "persistent-data/dm-block-manager.h" /* FIXME: क्रम dm_block_t */
#समावेश "dm-thin-metadata.h" /* FIXME: क्रम dm_thin_id */

#समावेश <linux/bपन.स>
#समावेश <linux/rbtree.h>

/*----------------------------------------------------------------*/

/*
 * Someबार we can't deal with a bio straight away.  We put them in prison
 * where they can't cause any mischief.  Bios are put in a cell identअगरied
 * by a key, multiple bios can be in the same cell.  When the cell is
 * subsequently unlocked the bios become available.
 */
काष्ठा dm_bio_prison;

/*
 * Keys define a range of blocks within either a भव or physical
 * device.
 */
काष्ठा dm_cell_key अणु
	पूर्णांक भव;
	dm_thin_id dev;
	dm_block_t block_begin, block_end;
पूर्ण;

/*
 * Treat this as opaque, only in header so callers can manage allocation
 * themselves.
 */
काष्ठा dm_bio_prison_cell अणु
	काष्ठा list_head user_list;	/* क्रम client use */
	काष्ठा rb_node node;

	काष्ठा dm_cell_key key;
	काष्ठा bio *holder;
	काष्ठा bio_list bios;
पूर्ण;

काष्ठा dm_bio_prison *dm_bio_prison_create(व्योम);
व्योम dm_bio_prison_destroy(काष्ठा dm_bio_prison *prison);

/*
 * These two functions just wrap a mempool.  This is a transitory step:
 * Eventually all bio prison clients should manage their own cell memory.
 *
 * Like mempool_alloc(), dm_bio_prison_alloc_cell() can only fail अगर called
 * in पूर्णांकerrupt context or passed GFP_NOWAIT.
 */
काष्ठा dm_bio_prison_cell *dm_bio_prison_alloc_cell(काष्ठा dm_bio_prison *prison,
						    gfp_t gfp);
व्योम dm_bio_prison_मुक्त_cell(काष्ठा dm_bio_prison *prison,
			     काष्ठा dm_bio_prison_cell *cell);

/*
 * Creates, or retrieves a cell that overlaps the given key.
 *
 * Returns 1 अगर pre-existing cell वापसed, zero अगर new cell created using
 * @cell_pपुनः_स्मृति.
 */
पूर्णांक dm_get_cell(काष्ठा dm_bio_prison *prison,
		काष्ठा dm_cell_key *key,
		काष्ठा dm_bio_prison_cell *cell_pपुनः_स्मृति,
		काष्ठा dm_bio_prison_cell **cell_result);

/*
 * An atomic op that combines retrieving or creating a cell, and adding a
 * bio to it.
 *
 * Returns 1 अगर the cell was alपढ़ोy held, 0 अगर @inmate is the new holder.
 */
पूर्णांक dm_bio_detain(काष्ठा dm_bio_prison *prison,
		  काष्ठा dm_cell_key *key,
		  काष्ठा bio *inmate,
		  काष्ठा dm_bio_prison_cell *cell_pपुनः_स्मृति,
		  काष्ठा dm_bio_prison_cell **cell_result);

व्योम dm_cell_release(काष्ठा dm_bio_prison *prison,
		     काष्ठा dm_bio_prison_cell *cell,
		     काष्ठा bio_list *bios);
व्योम dm_cell_release_no_holder(काष्ठा dm_bio_prison *prison,
			       काष्ठा dm_bio_prison_cell *cell,
			       काष्ठा bio_list *inmates);
व्योम dm_cell_error(काष्ठा dm_bio_prison *prison,
		   काष्ठा dm_bio_prison_cell *cell, blk_status_t error);

/*
 * Visits the cell and then releases.  Guarantees no new inmates are
 * inserted between the visit and release.
 */
व्योम dm_cell_visit_release(काष्ठा dm_bio_prison *prison,
			   व्योम (*visit_fn)(व्योम *, काष्ठा dm_bio_prison_cell *),
			   व्योम *context, काष्ठा dm_bio_prison_cell *cell);

/*
 * Rather than always releasing the prisoners in a cell, the client may
 * want to promote one of them to be the new holder.  There is a race here
 * though between releasing an empty cell, and other thपढ़ोs adding new
 * inmates.  So this function makes the decision with its lock held.
 *
 * This function can have two outcomes:
 * i) An inmate is promoted to be the holder of the cell (वापस value of 0).
 * ii) The cell has no inmate क्रम promotion and is released (वापस value of 1).
 */
पूर्णांक dm_cell_promote_or_release(काष्ठा dm_bio_prison *prison,
			       काष्ठा dm_bio_prison_cell *cell);

/*----------------------------------------------------------------*/

/*
 * We use the deferred set to keep track of pending पढ़ोs to shared blocks.
 * We करो this to ensure the new mapping caused by a ग_लिखो isn't perक्रमmed
 * until these prior पढ़ोs have completed.  Otherwise the insertion of the
 * new mapping could मुक्त the old block that the पढ़ो bios are mapped to.
 */

काष्ठा dm_deferred_set;
काष्ठा dm_deferred_entry;

काष्ठा dm_deferred_set *dm_deferred_set_create(व्योम);
व्योम dm_deferred_set_destroy(काष्ठा dm_deferred_set *ds);

काष्ठा dm_deferred_entry *dm_deferred_entry_inc(काष्ठा dm_deferred_set *ds);
व्योम dm_deferred_entry_dec(काष्ठा dm_deferred_entry *entry, काष्ठा list_head *head);
पूर्णांक dm_deferred_set_add_work(काष्ठा dm_deferred_set *ds, काष्ठा list_head *work);

/*----------------------------------------------------------------*/

#पूर्ण_अगर
