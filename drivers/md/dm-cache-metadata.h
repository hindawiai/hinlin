<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_CACHE_METADATA_H
#घोषणा DM_CACHE_METADATA_H

#समावेश "dm-cache-block-types.h"
#समावेश "dm-cache-policy-internal.h"
#समावेश "persistent-data/dm-space-map-metadata.h"

/*----------------------------------------------------------------*/

#घोषणा DM_CACHE_METADATA_BLOCK_SIZE DM_SM_METADATA_BLOCK_SIZE

/* FIXME: हटाओ this restriction */
/*
 * The metadata device is currently limited in size.
 */
#घोषणा DM_CACHE_METADATA_MAX_SECTORS DM_SM_METADATA_MAX_SECTORS

/*
 * A metadata device larger than 16GB triggers a warning.
 */
#घोषणा DM_CACHE_METADATA_MAX_SECTORS_WARNING (16 * (1024 * 1024 * 1024 >> SECTOR_SHIFT))

/*----------------------------------------------------------------*/

/*
 * Ext[234]-style compat feature flags.
 *
 * A new feature which old metadata will still be compatible with should
 * define a DM_CACHE_FEATURE_COMPAT_* flag (rarely useful).
 *
 * A new feature that is not compatible with old code should define a
 * DM_CACHE_FEATURE_INCOMPAT_* flag and guard the relevant code with
 * that flag.
 *
 * A new feature that is not compatible with old code accessing the
 * metadata RDWR should define a DM_CACHE_FEATURE_RO_COMPAT_* flag and
 * guard the relevant code with that flag.
 *
 * As these various flags are defined they should be added to the
 * following masks.
 */

#घोषणा DM_CACHE_FEATURE_COMPAT_SUPP	  0UL
#घोषणा DM_CACHE_FEATURE_COMPAT_RO_SUPP	  0UL
#घोषणा DM_CACHE_FEATURE_INCOMPAT_SUPP	  0UL

काष्ठा dm_cache_metadata;

/*
 * Reखोलोs or creates a new, empty metadata volume.  Returns an ERR_PTR on
 * failure.  If reखोलोing then features must match.
 */
काष्ठा dm_cache_metadata *dm_cache_metadata_खोलो(काष्ठा block_device *bdev,
						 sector_t data_block_size,
						 bool may_क्रमmat_device,
						 माप_प्रकार policy_hपूर्णांक_size,
						 अचिन्हित metadata_version);

व्योम dm_cache_metadata_बंद(काष्ठा dm_cache_metadata *cmd);

/*
 * The metadata needs to know how many cache blocks there are.  We करोn't
 * care about the origin, assuming the core target is giving us valid
 * origin blocks to map to.
 */
पूर्णांक dm_cache_resize(काष्ठा dm_cache_metadata *cmd, dm_cblock_t new_cache_size);
पूर्णांक dm_cache_size(काष्ठा dm_cache_metadata *cmd, dm_cblock_t *result);

पूर्णांक dm_cache_discard_bitset_resize(काष्ठा dm_cache_metadata *cmd,
				   sector_t discard_block_size,
				   dm_dblock_t new_nr_entries);

प्रकार पूर्णांक (*load_discard_fn)(व्योम *context, sector_t discard_block_size,
			       dm_dblock_t dblock, bool discarded);
पूर्णांक dm_cache_load_discards(काष्ठा dm_cache_metadata *cmd,
			   load_discard_fn fn, व्योम *context);

पूर्णांक dm_cache_set_discard(काष्ठा dm_cache_metadata *cmd, dm_dblock_t dblock, bool discard);

पूर्णांक dm_cache_हटाओ_mapping(काष्ठा dm_cache_metadata *cmd, dm_cblock_t cblock);
पूर्णांक dm_cache_insert_mapping(काष्ठा dm_cache_metadata *cmd, dm_cblock_t cblock, dm_oblock_t oblock);
पूर्णांक dm_cache_changed_this_transaction(काष्ठा dm_cache_metadata *cmd);

प्रकार पूर्णांक (*load_mapping_fn)(व्योम *context, dm_oblock_t oblock,
			       dm_cblock_t cblock, bool dirty,
			       uपूर्णांक32_t hपूर्णांक, bool hपूर्णांक_valid);
पूर्णांक dm_cache_load_mappings(काष्ठा dm_cache_metadata *cmd,
			   काष्ठा dm_cache_policy *policy,
			   load_mapping_fn fn,
			   व्योम *context);

पूर्णांक dm_cache_set_dirty_bits(काष्ठा dm_cache_metadata *cmd,
			    अचिन्हित nr_bits, अचिन्हित दीर्घ *bits);

काष्ठा dm_cache_statistics अणु
	uपूर्णांक32_t पढ़ो_hits;
	uपूर्णांक32_t पढ़ो_misses;
	uपूर्णांक32_t ग_लिखो_hits;
	uपूर्णांक32_t ग_लिखो_misses;
पूर्ण;

व्योम dm_cache_metadata_get_stats(काष्ठा dm_cache_metadata *cmd,
				 काष्ठा dm_cache_statistics *stats);

/*
 * 'void' because it's no big deal अगर it fails.
 */
व्योम dm_cache_metadata_set_stats(काष्ठा dm_cache_metadata *cmd,
				 काष्ठा dm_cache_statistics *stats);

पूर्णांक dm_cache_commit(काष्ठा dm_cache_metadata *cmd, bool clean_shutकरोwn);

पूर्णांक dm_cache_get_मुक्त_metadata_block_count(काष्ठा dm_cache_metadata *cmd,
					   dm_block_t *result);

पूर्णांक dm_cache_get_metadata_dev_size(काष्ठा dm_cache_metadata *cmd,
				   dm_block_t *result);

व्योम dm_cache_dump(काष्ठा dm_cache_metadata *cmd);

/*
 * The policy is invited to save a 32bit hपूर्णांक value क्रम every cblock (eg,
 * क्रम a hit count).  These are stored against the policy name.  If
 * policies are changed, then hपूर्णांकs will be lost.  If the machine crashes,
 * hपूर्णांकs will be lost.
 *
 * The hपूर्णांकs are indexed by the cblock, but many policies will not
 * neccessarily have a fast way of accessing efficiently via cblock.  So
 * rather than querying the policy क्रम each cblock, we let it walk its data
 * काष्ठाures and fill in the hपूर्णांकs in whatever order it wishes.
 */
पूर्णांक dm_cache_ग_लिखो_hपूर्णांकs(काष्ठा dm_cache_metadata *cmd, काष्ठा dm_cache_policy *p);

/*
 * Query method.  Are all the blocks in the cache clean?
 */
पूर्णांक dm_cache_metadata_all_clean(काष्ठा dm_cache_metadata *cmd, bool *result);

पूर्णांक dm_cache_metadata_needs_check(काष्ठा dm_cache_metadata *cmd, bool *result);
पूर्णांक dm_cache_metadata_set_needs_check(काष्ठा dm_cache_metadata *cmd);
व्योम dm_cache_metadata_set_पढ़ो_only(काष्ठा dm_cache_metadata *cmd);
व्योम dm_cache_metadata_set_पढ़ो_ग_लिखो(काष्ठा dm_cache_metadata *cmd);
पूर्णांक dm_cache_metadata_पात(काष्ठा dm_cache_metadata *cmd);

/*----------------------------------------------------------------*/

#पूर्ण_अगर /* DM_CACHE_METADATA_H */
