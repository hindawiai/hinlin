<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat. All rights reserved.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_CACHE_POLICY_H
#घोषणा DM_CACHE_POLICY_H

#समावेश "dm-cache-block-types.h"

#समावेश <linux/device-mapper.h>

/*----------------------------------------------------------------*/

/*
 * The cache policy makes the important decisions about which blocks get to
 * live on the faster cache device.
 */
क्रमागत policy_operation अणु
	POLICY_PROMOTE,
	POLICY_DEMOTE,
	POLICY_WRITEBACK
पूर्ण;

/*
 * This is the inकाष्ठाion passed back to the core target.
 */
काष्ठा policy_work अणु
	क्रमागत policy_operation op;
	dm_oblock_t oblock;
	dm_cblock_t cblock;
पूर्ण;

/*
 * The cache policy object.  It is envisaged that this काष्ठाure will be
 * embedded in a bigger, policy specअगरic काष्ठाure (ie. use container_of()).
 */
काष्ठा dm_cache_policy अणु
	/*
	 * Destroys this object.
	 */
	व्योम (*destroy)(काष्ठा dm_cache_policy *p);

	/*
	 * Find the location of a block.
	 *
	 * Must not block.
	 *
	 * Returns 0 अगर in cache (cblock will be set), -ENOENT अगर not, < 0 क्रम
	 * other errors (-EWOULDBLOCK would be typical).  data_dir should be
	 * READ or WRITE. fast_copy should be set अगर migrating this block would
	 * be 'cheap' somehow (eg, discarded data). background_queued will be set
	 * अगर a migration has just been queued.
	 */
	पूर्णांक (*lookup)(काष्ठा dm_cache_policy *p, dm_oblock_t oblock, dm_cblock_t *cblock,
		      पूर्णांक data_dir, bool fast_copy, bool *background_queued);

	/*
	 * Someबार the core target can optimise a migration, eg, the
	 * block may be discarded, or the bio may cover an entire block.
	 * In order to optimise it needs the migration immediately though
	 * so it knows to करो something dअगरferent with the bio.
	 *
	 * This method is optional (policy-पूर्णांकernal will fallback to using
	 * lookup).
	 */
	पूर्णांक (*lookup_with_work)(काष्ठा dm_cache_policy *p,
				dm_oblock_t oblock, dm_cblock_t *cblock,
				पूर्णांक data_dir, bool fast_copy,
				काष्ठा policy_work **work);

	/*
	 * Retrieves background work.  Returns -ENODATA when there's no
	 * background work.
	 */
	पूर्णांक (*get_background_work)(काष्ठा dm_cache_policy *p, bool idle,
			           काष्ठा policy_work **result);

	/*
	 * You must pass in the same work poपूर्णांकer that you were given, not
	 * a copy.
	 */
	व्योम (*complete_background_work)(काष्ठा dm_cache_policy *p,
					 काष्ठा policy_work *work,
					 bool success);

	व्योम (*set_dirty)(काष्ठा dm_cache_policy *p, dm_cblock_t cblock);
	व्योम (*clear_dirty)(काष्ठा dm_cache_policy *p, dm_cblock_t cblock);

	/*
	 * Called when a cache target is first created.  Used to load a
	 * mapping from the metadata device पूर्णांकo the policy.
	 */
	पूर्णांक (*load_mapping)(काष्ठा dm_cache_policy *p, dm_oblock_t oblock,
			    dm_cblock_t cblock, bool dirty,
			    uपूर्णांक32_t hपूर्णांक, bool hपूर्णांक_valid);

	/*
	 * Drops the mapping, irrespective of whether it's clean or dirty.
	 * Returns -ENODATA अगर cblock is not mapped.
	 */
	पूर्णांक (*invalidate_mapping)(काष्ठा dm_cache_policy *p, dm_cblock_t cblock);

	/*
	 * Gets the hपूर्णांक क्रम a given cblock.  Called in a single thपढ़ोed
	 * context.  So no locking required.
	 */
	uपूर्णांक32_t (*get_hपूर्णांक)(काष्ठा dm_cache_policy *p, dm_cblock_t cblock);

	/*
	 * How full is the cache?
	 */
	dm_cblock_t (*residency)(काष्ठा dm_cache_policy *p);

	/*
	 * Because of where we sit in the block layer, we can be asked to
	 * map a lot of little bios that are all in the same block (no
	 * queue merging has occurred).  To stop the policy being fooled by
	 * these, the core target sends regular tick() calls to the policy.
	 * The policy should only count an entry as hit once per tick.
	 *
	 * This method is optional.
	 */
	व्योम (*tick)(काष्ठा dm_cache_policy *p, bool can_block);

	/*
	 * Configuration.
	 */
	पूर्णांक (*emit_config_values)(काष्ठा dm_cache_policy *p, अक्षर *result,
				  अचिन्हित maxlen, sमाप_प्रकार *sz_ptr);
	पूर्णांक (*set_config_value)(काष्ठा dm_cache_policy *p,
				स्थिर अक्षर *key, स्थिर अक्षर *value);

	व्योम (*allow_migrations)(काष्ठा dm_cache_policy *p, bool allow);

	/*
	 * Book keeping ptr क्रम the policy रेजिस्टर, not क्रम general use.
	 */
	व्योम *निजी;
पूर्ण;

/*----------------------------------------------------------------*/

/*
 * We मुख्यtain a little रेजिस्टर of the dअगरferent policy types.
 */
#घोषणा CACHE_POLICY_NAME_SIZE 16
#घोषणा CACHE_POLICY_VERSION_SIZE 3

काष्ठा dm_cache_policy_type अणु
	/* For use by the रेजिस्टर code only. */
	काष्ठा list_head list;

	/*
	 * Policy ग_लिखोrs should fill in these fields.  The name field is
	 * what माला_लो passed on the target line to select your policy.
	 */
	अक्षर name[CACHE_POLICY_NAME_SIZE];
	अचिन्हित version[CACHE_POLICY_VERSION_SIZE];

	/*
	 * For use by an alias dm_cache_policy_type to poपूर्णांक to the
	 * real dm_cache_policy_type.
	 */
	काष्ठा dm_cache_policy_type *real;

	/*
	 * Policies may store a hपूर्णांक क्रम each each cache block.
	 * Currently the size of this hपूर्णांक must be 0 or 4 bytes but we
	 * expect to relax this in future.
	 */
	माप_प्रकार hपूर्णांक_size;

	काष्ठा module *owner;
	काष्ठा dm_cache_policy *(*create)(dm_cblock_t cache_size,
					  sector_t origin_size,
					  sector_t block_size);
पूर्ण;

पूर्णांक dm_cache_policy_रेजिस्टर(काष्ठा dm_cache_policy_type *type);
व्योम dm_cache_policy_unरेजिस्टर(काष्ठा dm_cache_policy_type *type);

/*----------------------------------------------------------------*/

#पूर्ण_अगर	/* DM_CACHE_POLICY_H */
