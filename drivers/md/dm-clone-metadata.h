<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2019 Arrikto, Inc. All Rights Reserved.
 */

#अगर_अघोषित DM_CLONE_METADATA_H
#घोषणा DM_CLONE_METADATA_H

#समावेश "persistent-data/dm-block-manager.h"
#समावेश "persistent-data/dm-space-map-metadata.h"

#घोषणा DM_CLONE_METADATA_BLOCK_SIZE DM_SM_METADATA_BLOCK_SIZE

/*
 * The metadata device is currently limited in size.
 */
#घोषणा DM_CLONE_METADATA_MAX_SECTORS DM_SM_METADATA_MAX_SECTORS

/*
 * A metadata device larger than 16GB triggers a warning.
 */
#घोषणा DM_CLONE_METADATA_MAX_SECTORS_WARNING (16 * (1024 * 1024 * 1024 >> SECTOR_SHIFT))

#घोषणा SPACE_MAP_ROOT_SIZE 128

/* dm-clone metadata */
काष्ठा dm_clone_metadata;

/*
 * Set region status to hydrated.
 *
 * @cmd: The dm-clone metadata
 * @region_nr: The region number
 *
 * This function करोesn't block, so it's safe to call it from पूर्णांकerrupt context.
 */
पूर्णांक dm_clone_set_region_hydrated(काष्ठा dm_clone_metadata *cmd, अचिन्हित दीर्घ region_nr);

/*
 * Set status of all regions in the provided range to hydrated, अगर not alपढ़ोy
 * hydrated.
 *
 * @cmd: The dm-clone metadata
 * @start: Starting region number
 * @nr_regions: Number of regions in the range
 *
 * This function करोesn't block, but since it uses spin_lock_irq()/spin_unlock_irq()
 * it's NOT safe to call it from any context where पूर्णांकerrupts are disabled, e.g.,
 * from पूर्णांकerrupt context.
 */
पूर्णांक dm_clone_cond_set_range(काष्ठा dm_clone_metadata *cmd, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ nr_regions);

/*
 * Read existing or create fresh metadata.
 *
 * @bdev: The device storing the metadata
 * @target_size: The target size
 * @region_size: The region size
 *
 * @वापसs: The dm-clone metadata
 *
 * This function पढ़ोs the superblock of @bdev and checks अगर it's all zeroes.
 * If it is, it क्रमmats @bdev and creates fresh metadata. If it isn't, it
 * validates the metadata stored in @bdev.
 */
काष्ठा dm_clone_metadata *dm_clone_metadata_खोलो(काष्ठा block_device *bdev,
						 sector_t target_size,
						 sector_t region_size);

/*
 * Free the resources related to metadata management.
 */
व्योम dm_clone_metadata_बंद(काष्ठा dm_clone_metadata *cmd);

/*
 * Commit dm-clone metadata to disk.
 *
 * We use a two phase commit:
 *
 * 1. dm_clone_metadata_pre_commit(): Prepare the current transaction क्रम
 *    committing. After this is called, all subsequent metadata updates, करोne
 *    through either dm_clone_set_region_hydrated() or
 *    dm_clone_cond_set_range(), will be part of the **next** transaction.
 *
 * 2. dm_clone_metadata_commit(): Actually commit the current transaction to
 *    disk and start a new transaction.
 *
 * This allows dm-clone to flush the destination device after step (1) to
 * ensure that all freshly hydrated regions, क्रम which we are updating the
 * metadata, are properly written to non-अस्थिर storage and won't be lost in
 * हाल of a crash.
 */
पूर्णांक dm_clone_metadata_pre_commit(काष्ठा dm_clone_metadata *cmd);
पूर्णांक dm_clone_metadata_commit(काष्ठा dm_clone_metadata *cmd);

/*
 * Reload the in core copy of the on-disk biपंचांगap.
 *
 * This should be used after पातing a metadata transaction and setting the
 * metadata to पढ़ो-only, to invalidate the in-core cache and make it match the
 * on-disk metadata.
 *
 * WARNING: It must not be called concurrently with either
 * dm_clone_set_region_hydrated() or dm_clone_cond_set_range(), as it updates
 * the region biपंचांगap without taking the relevant spinlock. We करोn't take the
 * spinlock because dm_clone_reload_in_core_bitset() करोes I/O, so it may block.
 *
 * But, it's safe to use it after calling dm_clone_metadata_set_पढ़ो_only(),
 * because the latter sets the metadata to पढ़ो-only mode. Both
 * dm_clone_set_region_hydrated() and dm_clone_cond_set_range() refuse to touch
 * the region biपंचांगap, after calling dm_clone_metadata_set_पढ़ो_only().
 */
पूर्णांक dm_clone_reload_in_core_bitset(काष्ठा dm_clone_metadata *cmd);

/*
 * Check whether dm-clone's metadata changed this transaction.
 */
bool dm_clone_changed_this_transaction(काष्ठा dm_clone_metadata *cmd);

/*
 * Abort current metadata transaction and rollback metadata to the last
 * committed transaction.
 */
पूर्णांक dm_clone_metadata_पात(काष्ठा dm_clone_metadata *cmd);

/*
 * Switches metadata to a पढ़ो only mode. Once पढ़ो-only mode has been entered
 * the following functions will वापस -EPERM:
 *
 *   dm_clone_metadata_pre_commit()
 *   dm_clone_metadata_commit()
 *   dm_clone_set_region_hydrated()
 *   dm_clone_cond_set_range()
 *   dm_clone_metadata_पात()
 */
व्योम dm_clone_metadata_set_पढ़ो_only(काष्ठा dm_clone_metadata *cmd);
व्योम dm_clone_metadata_set_पढ़ो_ग_लिखो(काष्ठा dm_clone_metadata *cmd);

/*
 * Returns true अगर the hydration of the destination device is finished.
 */
bool dm_clone_is_hydration_करोne(काष्ठा dm_clone_metadata *cmd);

/*
 * Returns true अगर region @region_nr is hydrated.
 */
bool dm_clone_is_region_hydrated(काष्ठा dm_clone_metadata *cmd, अचिन्हित दीर्घ region_nr);

/*
 * Returns true अगर all the regions in the range are hydrated.
 */
bool dm_clone_is_range_hydrated(काष्ठा dm_clone_metadata *cmd,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_regions);

/*
 * Returns the number of hydrated regions.
 */
अचिन्हित पूर्णांक dm_clone_nr_of_hydrated_regions(काष्ठा dm_clone_metadata *cmd);

/*
 * Returns the first unhydrated region with region_nr >= @start
 */
अचिन्हित दीर्घ dm_clone_find_next_unhydrated_region(काष्ठा dm_clone_metadata *cmd,
						   अचिन्हित दीर्घ start);

/*
 * Get the number of मुक्त metadata blocks.
 */
पूर्णांक dm_clone_get_मुक्त_metadata_block_count(काष्ठा dm_clone_metadata *cmd, dm_block_t *result);

/*
 * Get the total number of metadata blocks.
 */
पूर्णांक dm_clone_get_metadata_dev_size(काष्ठा dm_clone_metadata *cmd, dm_block_t *result);

#पूर्ण_अगर /* DM_CLONE_METADATA_H */
