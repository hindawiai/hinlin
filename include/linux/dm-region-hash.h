<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software Limited.
 * Copyright (C) 2004-2008 Red Hat, Inc. All rights reserved.
 *
 * Device-Mapper dirty region hash पूर्णांकerface.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_REGION_HASH_H
#घोषणा DM_REGION_HASH_H

#समावेश <linux/dm-dirty-log.h>

/*-----------------------------------------------------------------
 * Region hash
 *----------------------------------------------------------------*/
काष्ठा dm_region_hash;
काष्ठा dm_region;

/*
 * States a region can have.
 */
क्रमागत dm_rh_region_states अणु
	DM_RH_CLEAN	 = 0x01,	/* No ग_लिखोs in flight. */
	DM_RH_सूचीTY	 = 0x02,	/* Writes in flight. */
	DM_RH_NOSYNC	 = 0x04,	/* Out of sync. */
	DM_RH_RECOVERING = 0x08,	/* Under resynchronization. */
पूर्ण;

/*
 * Region hash create/destroy.
 */
काष्ठा bio_list;
काष्ठा dm_region_hash *dm_region_hash_create(
		व्योम *context, व्योम (*dispatch_bios)(व्योम *context,
						     काष्ठा bio_list *bios),
		व्योम (*wakeup_workers)(व्योम *context),
		व्योम (*wakeup_all_recovery_रुकोers)(व्योम *context),
		sector_t target_begin, अचिन्हित max_recovery,
		काष्ठा dm_dirty_log *log, uपूर्णांक32_t region_size,
		region_t nr_regions);
व्योम dm_region_hash_destroy(काष्ठा dm_region_hash *rh);

काष्ठा dm_dirty_log *dm_rh_dirty_log(काष्ठा dm_region_hash *rh);

/*
 * Conversion functions.
 */
region_t dm_rh_bio_to_region(काष्ठा dm_region_hash *rh, काष्ठा bio *bio);
sector_t dm_rh_region_to_sector(काष्ठा dm_region_hash *rh, region_t region);
व्योम *dm_rh_region_context(काष्ठा dm_region *reg);

/*
 * Get region size and key (ie. number of the region).
 */
sector_t dm_rh_get_region_size(काष्ठा dm_region_hash *rh);
region_t dm_rh_get_region_key(काष्ठा dm_region *reg);

/*
 * Get/set/update region state (and dirty log).
 *
 */
पूर्णांक dm_rh_get_state(काष्ठा dm_region_hash *rh, region_t region, पूर्णांक may_block);
व्योम dm_rh_set_state(काष्ठा dm_region_hash *rh, region_t region,
		     क्रमागत dm_rh_region_states state, पूर्णांक may_block);

/* Non-zero errors_handled leaves the state of the region NOSYNC */
व्योम dm_rh_update_states(काष्ठा dm_region_hash *rh, पूर्णांक errors_handled);

/* Flush the region hash and dirty log. */
पूर्णांक dm_rh_flush(काष्ठा dm_region_hash *rh);

/* Inc/dec pending count on regions. */
व्योम dm_rh_inc_pending(काष्ठा dm_region_hash *rh, काष्ठा bio_list *bios);
व्योम dm_rh_dec(काष्ठा dm_region_hash *rh, region_t region);

/* Delay bios on regions. */
व्योम dm_rh_delay(काष्ठा dm_region_hash *rh, काष्ठा bio *bio);

व्योम dm_rh_mark_nosync(काष्ठा dm_region_hash *rh, काष्ठा bio *bio);

/*
 * Region recovery control.
 */

/* Prepare some regions क्रम recovery by starting to quiesce them. */
व्योम dm_rh_recovery_prepare(काष्ठा dm_region_hash *rh);

/* Try fetching a quiesced region क्रम recovery. */
काष्ठा dm_region *dm_rh_recovery_start(काष्ठा dm_region_hash *rh);

/* Report recovery end on a region. */
व्योम dm_rh_recovery_end(काष्ठा dm_region *reg, पूर्णांक error);

/* Returns number of regions with recovery work outstanding. */
पूर्णांक dm_rh_recovery_in_flight(काष्ठा dm_region_hash *rh);

/* Start/stop recovery. */
व्योम dm_rh_start_recovery(काष्ठा dm_region_hash *rh);
व्योम dm_rh_stop_recovery(काष्ठा dm_region_hash *rh);

#पूर्ण_अगर /* DM_REGION_HASH_H */
