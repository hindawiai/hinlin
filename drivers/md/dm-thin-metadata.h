<शैली गुरु>
/*
 * Copyright (C) 2010-2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_THIN_METADATA_H
#घोषणा DM_THIN_METADATA_H

#समावेश "persistent-data/dm-block-manager.h"
#समावेश "persistent-data/dm-space-map.h"
#समावेश "persistent-data/dm-space-map-metadata.h"

#घोषणा THIN_METADATA_BLOCK_SIZE DM_SM_METADATA_BLOCK_SIZE

/*
 * The metadata device is currently limited in size.
 */
#घोषणा THIN_METADATA_MAX_SECTORS DM_SM_METADATA_MAX_SECTORS

/*
 * A metadata device larger than 16GB triggers a warning.
 */
#घोषणा THIN_METADATA_MAX_SECTORS_WARNING (16 * (1024 * 1024 * 1024 >> SECTOR_SHIFT))

/*----------------------------------------------------------------*/

/*
 * Thin metadata superblock flags.
 */
#घोषणा THIN_METADATA_NEEDS_CHECK_FLAG (1 << 0)

काष्ठा dm_pool_metadata;
काष्ठा dm_thin_device;

/*
 * Device identअगरier
 */
प्रकार uपूर्णांक64_t dm_thin_id;

/*
 * Reखोलोs or creates a new, empty metadata volume.
 */
काष्ठा dm_pool_metadata *dm_pool_metadata_खोलो(काष्ठा block_device *bdev,
					       sector_t data_block_size,
					       bool क्रमmat_device);

पूर्णांक dm_pool_metadata_बंद(काष्ठा dm_pool_metadata *pmd);

/*
 * Compat feature flags.  Any incompat flags beyond the ones
 * specअगरied below will prevent use of the thin metadata.
 */
#घोषणा THIN_FEATURE_COMPAT_SUPP	  0UL
#घोषणा THIN_FEATURE_COMPAT_RO_SUPP	  0UL
#घोषणा THIN_FEATURE_INCOMPAT_SUPP	  0UL

/*
 * Device creation/deletion.
 */
पूर्णांक dm_pool_create_thin(काष्ठा dm_pool_metadata *pmd, dm_thin_id dev);

/*
 * An पूर्णांकernal snapshot.
 *
 * You can only snapshot a quiesced origin i.e. one that is either
 * suspended or not instanced at all.
 */
पूर्णांक dm_pool_create_snap(काष्ठा dm_pool_metadata *pmd, dm_thin_id dev,
			dm_thin_id origin);

/*
 * Deletes a भव device from the metadata.  It _is_ safe to call this
 * when that device is खोलो.  Operations on that device will just start
 * failing.  You still need to call बंद() on the device.
 */
पूर्णांक dm_pool_delete_thin_device(काष्ठा dm_pool_metadata *pmd,
			       dm_thin_id dev);

/*
 * Commits _all_ metadata changes: device creation, deletion, mapping
 * updates.
 */
पूर्णांक dm_pool_commit_metadata(काष्ठा dm_pool_metadata *pmd);

/*
 * Discards all uncommitted changes.  Reपढ़ोs the superblock, rolling back
 * to the last good transaction.  Thin devices reमुख्य खोलो.
 * dm_thin_पातed_changes() tells you अगर they had uncommitted changes.
 *
 * If this call fails it's only useful to call dm_pool_metadata_बंद().
 * All other methods will fail with -EINVAL.
 */
पूर्णांक dm_pool_पात_metadata(काष्ठा dm_pool_metadata *pmd);

/*
 * Set/get userspace transaction id.
 */
पूर्णांक dm_pool_set_metadata_transaction_id(काष्ठा dm_pool_metadata *pmd,
					uपूर्णांक64_t current_id,
					uपूर्णांक64_t new_id);

पूर्णांक dm_pool_get_metadata_transaction_id(काष्ठा dm_pool_metadata *pmd,
					uपूर्णांक64_t *result);

/*
 * Hold/get root क्रम userspace transaction.
 *
 * The metadata snapshot is a copy of the current superblock (minus the
 * space maps).  Userland can access the data काष्ठाures क्रम READ
 * operations only.  A small perक्रमmance hit is incurred by providing this
 * copy of the metadata to userland due to extra copy-on-ग_लिखो operations
 * on the metadata nodes.  Release this as soon as you finish with it.
 */
पूर्णांक dm_pool_reserve_metadata_snap(काष्ठा dm_pool_metadata *pmd);
पूर्णांक dm_pool_release_metadata_snap(काष्ठा dm_pool_metadata *pmd);

पूर्णांक dm_pool_get_metadata_snap(काष्ठा dm_pool_metadata *pmd,
			      dm_block_t *result);

/*
 * Actions on a single भव device.
 */

/*
 * Opening the same device more than once will fail with -EBUSY.
 */
पूर्णांक dm_pool_खोलो_thin_device(काष्ठा dm_pool_metadata *pmd, dm_thin_id dev,
			     काष्ठा dm_thin_device **td);

पूर्णांक dm_pool_बंद_thin_device(काष्ठा dm_thin_device *td);

dm_thin_id dm_thin_dev_id(काष्ठा dm_thin_device *td);

काष्ठा dm_thin_lookup_result अणु
	dm_block_t block;
	bool shared:1;
पूर्ण;

/*
 * Returns:
 *   -EWOULDBLOCK अगरf @can_issue_io is set and would issue IO
 *   -ENODATA अगरf that mapping is not present.
 *   0 success
 */
पूर्णांक dm_thin_find_block(काष्ठा dm_thin_device *td, dm_block_t block,
		       पूर्णांक can_issue_io, काष्ठा dm_thin_lookup_result *result);

/*
 * Retrieve the next run of contiguously mapped blocks.  Useful क्रम working
 * out where to अवरोध up IO.  Returns 0 on success, < 0 on error.
 */
पूर्णांक dm_thin_find_mapped_range(काष्ठा dm_thin_device *td,
			      dm_block_t begin, dm_block_t end,
			      dm_block_t *thin_begin, dm_block_t *thin_end,
			      dm_block_t *pool_begin, bool *maybe_shared);

/*
 * Obtain an unused block.
 */
पूर्णांक dm_pool_alloc_data_block(काष्ठा dm_pool_metadata *pmd, dm_block_t *result);

/*
 * Insert or हटाओ block.
 */
पूर्णांक dm_thin_insert_block(काष्ठा dm_thin_device *td, dm_block_t block,
			 dm_block_t data_block);

पूर्णांक dm_thin_हटाओ_block(काष्ठा dm_thin_device *td, dm_block_t block);
पूर्णांक dm_thin_हटाओ_range(काष्ठा dm_thin_device *td,
			 dm_block_t begin, dm_block_t end);

/*
 * Queries.
 */
bool dm_thin_changed_this_transaction(काष्ठा dm_thin_device *td);

bool dm_pool_changed_this_transaction(काष्ठा dm_pool_metadata *pmd);

bool dm_thin_पातed_changes(काष्ठा dm_thin_device *td);

पूर्णांक dm_thin_get_highest_mapped_block(काष्ठा dm_thin_device *td,
				     dm_block_t *highest_mapped);

पूर्णांक dm_thin_get_mapped_count(काष्ठा dm_thin_device *td, dm_block_t *result);

पूर्णांक dm_pool_get_मुक्त_block_count(काष्ठा dm_pool_metadata *pmd,
				 dm_block_t *result);

पूर्णांक dm_pool_get_मुक्त_metadata_block_count(काष्ठा dm_pool_metadata *pmd,
					  dm_block_t *result);

पूर्णांक dm_pool_get_metadata_dev_size(काष्ठा dm_pool_metadata *pmd,
				  dm_block_t *result);

पूर्णांक dm_pool_get_data_dev_size(काष्ठा dm_pool_metadata *pmd, dm_block_t *result);

पूर्णांक dm_pool_block_is_shared(काष्ठा dm_pool_metadata *pmd, dm_block_t b, bool *result);

पूर्णांक dm_pool_inc_data_range(काष्ठा dm_pool_metadata *pmd, dm_block_t b, dm_block_t e);
पूर्णांक dm_pool_dec_data_range(काष्ठा dm_pool_metadata *pmd, dm_block_t b, dm_block_t e);

/*
 * Returns -ENOSPC अगर the new size is too small and alपढ़ोy allocated
 * blocks would be lost.
 */
पूर्णांक dm_pool_resize_data_dev(काष्ठा dm_pool_metadata *pmd, dm_block_t new_size);
पूर्णांक dm_pool_resize_metadata_dev(काष्ठा dm_pool_metadata *pmd, dm_block_t new_size);

/*
 * Flicks the underlying block manager पूर्णांकo पढ़ो only mode, so you know
 * that nothing is changing.
 */
व्योम dm_pool_metadata_पढ़ो_only(काष्ठा dm_pool_metadata *pmd);
व्योम dm_pool_metadata_पढ़ो_ग_लिखो(काष्ठा dm_pool_metadata *pmd);

पूर्णांक dm_pool_रेजिस्टर_metadata_threshold(काष्ठा dm_pool_metadata *pmd,
					dm_block_t threshold,
					dm_sm_threshold_fn fn,
					व्योम *context);

/*
 * Updates the superblock immediately.
 */
पूर्णांक dm_pool_metadata_set_needs_check(काष्ठा dm_pool_metadata *pmd);
bool dm_pool_metadata_needs_check(काष्ठा dm_pool_metadata *pmd);

/*
 * Issue any prefetches that may be useful.
 */
व्योम dm_pool_issue_prefetches(काष्ठा dm_pool_metadata *pmd);

/* Pre-commit callback */
प्रकार पूर्णांक (*dm_pool_pre_commit_fn)(व्योम *context);

व्योम dm_pool_रेजिस्टर_pre_commit_callback(काष्ठा dm_pool_metadata *pmd,
					  dm_pool_pre_commit_fn fn,
					  व्योम *context);

/*----------------------------------------------------------------*/

#पूर्ण_अगर
