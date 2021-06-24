<शैली गुरु>
/*
 * Copyright (C) 2001-2002 Sistina Software (UK) Limited.
 * Copyright (C) 2008 Red Hat, Inc. All rights reserved.
 *
 * Device-mapper snapshot exception store.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित _LINUX_DM_EXCEPTION_STORE
#घोषणा _LINUX_DM_EXCEPTION_STORE

#समावेश <linux/blkdev.h>
#समावेश <linux/list_bl.h>
#समावेश <linux/device-mapper.h>

/*
 * The snapshot code deals with largish chunks of the disk at a
 * समय. Typically 32k - 512k.
 */
प्रकार sector_t chunk_t;

/*
 * An exception is used where an old chunk of data has been
 * replaced by a new one.
 * If chunk_t is 64 bits in size, the top 8 bits of new_chunk hold the number
 * of chunks that follow contiguously.  Reमुख्यing bits hold the number of the
 * chunk within the device.
 */
काष्ठा dm_exception अणु
	काष्ठा hlist_bl_node hash_list;

	chunk_t old_chunk;
	chunk_t new_chunk;
पूर्ण;

/*
 * Abstraction to handle the meta/layout of exception stores (the
 * COW device).
 */
काष्ठा dm_exception_store;
काष्ठा dm_exception_store_type अणु
	स्थिर अक्षर *name;
	काष्ठा module *module;

	पूर्णांक (*ctr) (काष्ठा dm_exception_store *store, अक्षर *options);

	/*
	 * Destroys this object when you've finished with it.
	 */
	व्योम (*dtr) (काष्ठा dm_exception_store *store);

	/*
	 * The target shouldn't पढ़ो the COW device until this is
	 * called.  As exceptions are पढ़ो from the COW, they are
	 * reported back via the callback.
	 */
	पूर्णांक (*पढ़ो_metadata) (काष्ठा dm_exception_store *store,
			      पूर्णांक (*callback)(व्योम *callback_context,
					      chunk_t old, chunk_t new),
			      व्योम *callback_context);

	/*
	 * Find somewhere to store the next exception.
	 */
	पूर्णांक (*prepare_exception) (काष्ठा dm_exception_store *store,
				  काष्ठा dm_exception *e);

	/*
	 * Update the metadata with this exception.
	 */
	व्योम (*commit_exception) (काष्ठा dm_exception_store *store,
				  काष्ठा dm_exception *e, पूर्णांक valid,
				  व्योम (*callback) (व्योम *, पूर्णांक success),
				  व्योम *callback_context);

	/*
	 * Returns 0 अगर the exception store is empty.
	 *
	 * If there are exceptions still to be merged, sets
	 * *last_old_chunk and *last_new_chunk to the most recent
	 * still-to-be-merged chunk and वापसs the number of
	 * consecutive previous ones.
	 */
	पूर्णांक (*prepare_merge) (काष्ठा dm_exception_store *store,
			      chunk_t *last_old_chunk, chunk_t *last_new_chunk);

	/*
	 * Clear the last n exceptions.
	 * nr_merged must be <= the value वापसed by prepare_merge.
	 */
	पूर्णांक (*commit_merge) (काष्ठा dm_exception_store *store, पूर्णांक nr_merged);

	/*
	 * The snapshot is invalid, note this in the metadata.
	 */
	व्योम (*drop_snapshot) (काष्ठा dm_exception_store *store);

	अचिन्हित (*status) (काष्ठा dm_exception_store *store,
			    status_type_t status, अक्षर *result,
			    अचिन्हित maxlen);

	/*
	 * Return how full the snapshot is.
	 */
	व्योम (*usage) (काष्ठा dm_exception_store *store,
		       sector_t *total_sectors, sector_t *sectors_allocated,
		       sector_t *metadata_sectors);

	/* For पूर्णांकernal device-mapper use only. */
	काष्ठा list_head list;
पूर्ण;

काष्ठा dm_snapshot;

काष्ठा dm_exception_store अणु
	काष्ठा dm_exception_store_type *type;
	काष्ठा dm_snapshot *snap;

	/* Size of data blocks saved - must be a घातer of 2 */
	अचिन्हित chunk_size;
	अचिन्हित chunk_mask;
	अचिन्हित chunk_shअगरt;

	व्योम *context;

	bool userspace_supports_overflow;
पूर्ण;

/*
 * Obtain the origin or cow device used by a given snapshot.
 */
काष्ठा dm_dev *dm_snap_origin(काष्ठा dm_snapshot *snap);
काष्ठा dm_dev *dm_snap_cow(काष्ठा dm_snapshot *snap);

/*
 * Funtions to manipulate consecutive chunks
 */
#घोषणा DM_CHUNK_CONSECUTIVE_BITS 8
#घोषणा DM_CHUNK_NUMBER_BITS 56

अटल अंतरभूत chunk_t dm_chunk_number(chunk_t chunk)
अणु
	वापस chunk & (chunk_t)((1ULL << DM_CHUNK_NUMBER_BITS) - 1ULL);
पूर्ण

अटल अंतरभूत अचिन्हित dm_consecutive_chunk_count(काष्ठा dm_exception *e)
अणु
	वापस e->new_chunk >> DM_CHUNK_NUMBER_BITS;
पूर्ण

अटल अंतरभूत व्योम dm_consecutive_chunk_count_inc(काष्ठा dm_exception *e)
अणु
	e->new_chunk += (1ULL << DM_CHUNK_NUMBER_BITS);

	BUG_ON(!dm_consecutive_chunk_count(e));
पूर्ण

अटल अंतरभूत व्योम dm_consecutive_chunk_count_dec(काष्ठा dm_exception *e)
अणु
	BUG_ON(!dm_consecutive_chunk_count(e));

	e->new_chunk -= (1ULL << DM_CHUNK_NUMBER_BITS);
पूर्ण

/*
 * Return the number of sectors in the device.
 */
अटल अंतरभूत sector_t get_dev_size(काष्ठा block_device *bdev)
अणु
	वापस i_size_पढ़ो(bdev->bd_inode) >> SECTOR_SHIFT;
पूर्ण

अटल अंतरभूत chunk_t sector_to_chunk(काष्ठा dm_exception_store *store,
				      sector_t sector)
अणु
	वापस sector >> store->chunk_shअगरt;
पूर्ण

पूर्णांक dm_exception_store_type_रेजिस्टर(काष्ठा dm_exception_store_type *type);
पूर्णांक dm_exception_store_type_unरेजिस्टर(काष्ठा dm_exception_store_type *type);

पूर्णांक dm_exception_store_set_chunk_size(काष्ठा dm_exception_store *store,
				      अचिन्हित chunk_size,
				      अक्षर **error);

पूर्णांक dm_exception_store_create(काष्ठा dm_target *ti, पूर्णांक argc, अक्षर **argv,
			      काष्ठा dm_snapshot *snap,
			      अचिन्हित *args_used,
			      काष्ठा dm_exception_store **store);
व्योम dm_exception_store_destroy(काष्ठा dm_exception_store *store);

पूर्णांक dm_exception_store_init(व्योम);
व्योम dm_exception_store_निकास(व्योम);

/*
 * Two exception store implementations.
 */
पूर्णांक dm_persistent_snapshot_init(व्योम);
व्योम dm_persistent_snapshot_निकास(व्योम);

पूर्णांक dm_transient_snapshot_init(व्योम);
व्योम dm_transient_snapshot_निकास(व्योम);

#पूर्ण_अगर /* _LINUX_DM_EXCEPTION_STORE */
