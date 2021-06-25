<शैली गुरु>
/*
 * Copyright (C) 2010-2011 Neil Brown
 * Copyright (C) 2010-2018 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "md.h"
#समावेश "raid1.h"
#समावेश "raid5.h"
#समावेश "raid10.h"
#समावेश "md-bitmap.h"

#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "raid"
#घोषणा	MAX_RAID_DEVICES	253 /* md-raid kernel limit */

/*
 * Minimum sectors of मुक्त reshape space per raid device
 */
#घोषणा	MIN_FREE_RESHAPE_SPACE to_sector(4*4096)

/*
 * Minimum journal space 4 MiB in sectors.
 */
#घोषणा	MIN_RAID456_JOURNAL_SPACE (4*2048)

अटल bool devices_handle_discard_safely = false;

/*
 * The following flags are used by dm-raid.c to set up the array state.
 * They must be cleared beक्रमe md_run is called.
 */
#घोषणा FirstUse 10		/* rdev flag */

काष्ठा raid_dev अणु
	/*
	 * Two DM devices, one to hold metadata and one to hold the
	 * actual data/parity.	The reason क्रम this is to not confuse
	 * ti->len and give more flexibility in altering size and
	 * अक्षरacteristics.
	 *
	 * While it is possible क्रम this device to be associated
	 * with a dअगरferent physical device than the data_dev, it
	 * is पूर्णांकended क्रम it to be the same.
	 *    |--------- Physical Device ---------|
	 *    |- meta_dev -|------ data_dev ------|
	 */
	काष्ठा dm_dev *meta_dev;
	काष्ठा dm_dev *data_dev;
	काष्ठा md_rdev rdev;
पूर्ण;

/*
 * Bits क्रम establishing rs->ctr_flags
 *
 * 1 = no flag value
 * 2 = flag with value
 */
#घोषणा __CTR_FLAG_SYNC			0  /* 1 */ /* Not with raid0! */
#घोषणा __CTR_FLAG_NOSYNC		1  /* 1 */ /* Not with raid0! */
#घोषणा __CTR_FLAG_REBUILD		2  /* 2 */ /* Not with raid0! */
#घोषणा __CTR_FLAG_DAEMON_SLEEP		3  /* 2 */ /* Not with raid0! */
#घोषणा __CTR_FLAG_MIN_RECOVERY_RATE	4  /* 2 */ /* Not with raid0! */
#घोषणा __CTR_FLAG_MAX_RECOVERY_RATE	5  /* 2 */ /* Not with raid0! */
#घोषणा __CTR_FLAG_MAX_WRITE_BEHIND	6  /* 2 */ /* Only with raid1! */
#घोषणा __CTR_FLAG_WRITE_MOSTLY		7  /* 2 */ /* Only with raid1! */
#घोषणा __CTR_FLAG_STRIPE_CACHE		8  /* 2 */ /* Only with raid4/5/6! */
#घोषणा __CTR_FLAG_REGION_SIZE		9  /* 2 */ /* Not with raid0! */
#घोषणा __CTR_FLAG_RAID10_COPIES	10 /* 2 */ /* Only with raid10 */
#घोषणा __CTR_FLAG_RAID10_FORMAT	11 /* 2 */ /* Only with raid10 */
/* New क्रम v1.9.0 */
#घोषणा __CTR_FLAG_DELTA_DISKS		12 /* 2 */ /* Only with reshapable raid1/4/5/6/10! */
#घोषणा __CTR_FLAG_DATA_OFFSET		13 /* 2 */ /* Only with reshapable raid4/5/6/10! */
#घोषणा __CTR_FLAG_RAID10_USE_NEAR_SETS 14 /* 2 */ /* Only with raid10! */

/* New क्रम v1.10.0 */
#घोषणा __CTR_FLAG_JOURNAL_DEV		15 /* 2 */ /* Only with raid4/5/6 (journal device)! */

/* New क्रम v1.11.1 */
#घोषणा __CTR_FLAG_JOURNAL_MODE		16 /* 2 */ /* Only with raid4/5/6 (journal mode)! */

/*
 * Flags क्रम rs->ctr_flags field.
 */
#घोषणा CTR_FLAG_SYNC			(1 << __CTR_FLAG_SYNC)
#घोषणा CTR_FLAG_NOSYNC			(1 << __CTR_FLAG_NOSYNC)
#घोषणा CTR_FLAG_REBUILD		(1 << __CTR_FLAG_REBUILD)
#घोषणा CTR_FLAG_DAEMON_SLEEP		(1 << __CTR_FLAG_DAEMON_SLEEP)
#घोषणा CTR_FLAG_MIN_RECOVERY_RATE	(1 << __CTR_FLAG_MIN_RECOVERY_RATE)
#घोषणा CTR_FLAG_MAX_RECOVERY_RATE	(1 << __CTR_FLAG_MAX_RECOVERY_RATE)
#घोषणा CTR_FLAG_MAX_WRITE_BEHIND	(1 << __CTR_FLAG_MAX_WRITE_BEHIND)
#घोषणा CTR_FLAG_WRITE_MOSTLY		(1 << __CTR_FLAG_WRITE_MOSTLY)
#घोषणा CTR_FLAG_STRIPE_CACHE		(1 << __CTR_FLAG_STRIPE_CACHE)
#घोषणा CTR_FLAG_REGION_SIZE		(1 << __CTR_FLAG_REGION_SIZE)
#घोषणा CTR_FLAG_RAID10_COPIES		(1 << __CTR_FLAG_RAID10_COPIES)
#घोषणा CTR_FLAG_RAID10_FORMAT		(1 << __CTR_FLAG_RAID10_FORMAT)
#घोषणा CTR_FLAG_DELTA_DISKS		(1 << __CTR_FLAG_DELTA_DISKS)
#घोषणा CTR_FLAG_DATA_OFFSET		(1 << __CTR_FLAG_DATA_OFFSET)
#घोषणा CTR_FLAG_RAID10_USE_NEAR_SETS	(1 << __CTR_FLAG_RAID10_USE_NEAR_SETS)
#घोषणा CTR_FLAG_JOURNAL_DEV		(1 << __CTR_FLAG_JOURNAL_DEV)
#घोषणा CTR_FLAG_JOURNAL_MODE		(1 << __CTR_FLAG_JOURNAL_MODE)

/*
 * Definitions of various स्थिरructor flags to
 * be used in checks of valid / invalid flags
 * per raid level.
 */
/* Define all any sync flags */
#घोषणा	CTR_FLAGS_ANY_SYNC		(CTR_FLAG_SYNC | CTR_FLAG_NOSYNC)

/* Define flags क्रम options without argument (e.g. 'nosync') */
#घोषणा	CTR_FLAG_OPTIONS_NO_ARGS	(CTR_FLAGS_ANY_SYNC | \
					 CTR_FLAG_RAID10_USE_NEAR_SETS)

/* Define flags क्रम options with one argument (e.g. 'delta_disks +2') */
#घोषणा CTR_FLAG_OPTIONS_ONE_ARG (CTR_FLAG_REBUILD | \
				  CTR_FLAG_WRITE_MOSTLY | \
				  CTR_FLAG_DAEMON_SLEEP | \
				  CTR_FLAG_MIN_RECOVERY_RATE | \
				  CTR_FLAG_MAX_RECOVERY_RATE | \
				  CTR_FLAG_MAX_WRITE_BEHIND | \
				  CTR_FLAG_STRIPE_CACHE | \
				  CTR_FLAG_REGION_SIZE | \
				  CTR_FLAG_RAID10_COPIES | \
				  CTR_FLAG_RAID10_FORMAT | \
				  CTR_FLAG_DELTA_DISKS | \
				  CTR_FLAG_DATA_OFFSET | \
				  CTR_FLAG_JOURNAL_DEV | \
				  CTR_FLAG_JOURNAL_MODE)

/* Valid options definitions per raid level... */

/* "raid0" करोes only accept data offset */
#घोषणा RAID0_VALID_FLAGS	(CTR_FLAG_DATA_OFFSET)

/* "raid1" करोes not accept stripe cache, data offset, delta_disks or any raid10 options */
#घोषणा RAID1_VALID_FLAGS	(CTR_FLAGS_ANY_SYNC | \
				 CTR_FLAG_REBUILD | \
				 CTR_FLAG_WRITE_MOSTLY | \
				 CTR_FLAG_DAEMON_SLEEP | \
				 CTR_FLAG_MIN_RECOVERY_RATE | \
				 CTR_FLAG_MAX_RECOVERY_RATE | \
				 CTR_FLAG_MAX_WRITE_BEHIND | \
				 CTR_FLAG_REGION_SIZE | \
				 CTR_FLAG_DELTA_DISKS | \
				 CTR_FLAG_DATA_OFFSET)

/* "raid10" करोes not accept any raid1 or stripe cache options */
#घोषणा RAID10_VALID_FLAGS	(CTR_FLAGS_ANY_SYNC | \
				 CTR_FLAG_REBUILD | \
				 CTR_FLAG_DAEMON_SLEEP | \
				 CTR_FLAG_MIN_RECOVERY_RATE | \
				 CTR_FLAG_MAX_RECOVERY_RATE | \
				 CTR_FLAG_REGION_SIZE | \
				 CTR_FLAG_RAID10_COPIES | \
				 CTR_FLAG_RAID10_FORMAT | \
				 CTR_FLAG_DELTA_DISKS | \
				 CTR_FLAG_DATA_OFFSET | \
				 CTR_FLAG_RAID10_USE_NEAR_SETS)

/*
 * "raid4/5/6" करो not accept any raid1 or raid10 specअगरic options
 *
 * "raid6" करोes not accept "nosync", because it is not guaranteed
 * that both parity and q-syndrome are being written properly with
 * any ग_लिखोs
 */
#घोषणा RAID45_VALID_FLAGS	(CTR_FLAGS_ANY_SYNC | \
				 CTR_FLAG_REBUILD | \
				 CTR_FLAG_DAEMON_SLEEP | \
				 CTR_FLAG_MIN_RECOVERY_RATE | \
				 CTR_FLAG_MAX_RECOVERY_RATE | \
				 CTR_FLAG_STRIPE_CACHE | \
				 CTR_FLAG_REGION_SIZE | \
				 CTR_FLAG_DELTA_DISKS | \
				 CTR_FLAG_DATA_OFFSET | \
				 CTR_FLAG_JOURNAL_DEV | \
				 CTR_FLAG_JOURNAL_MODE)

#घोषणा RAID6_VALID_FLAGS	(CTR_FLAG_SYNC | \
				 CTR_FLAG_REBUILD | \
				 CTR_FLAG_DAEMON_SLEEP | \
				 CTR_FLAG_MIN_RECOVERY_RATE | \
				 CTR_FLAG_MAX_RECOVERY_RATE | \
				 CTR_FLAG_STRIPE_CACHE | \
				 CTR_FLAG_REGION_SIZE | \
				 CTR_FLAG_DELTA_DISKS | \
				 CTR_FLAG_DATA_OFFSET | \
				 CTR_FLAG_JOURNAL_DEV | \
				 CTR_FLAG_JOURNAL_MODE)
/* ...valid options definitions per raid level */

/*
 * Flags क्रम rs->runसमय_flags field
 * (RT_FLAG prefix meaning "runtime flag")
 *
 * These are all पूर्णांकernal and used to define runसमय state,
 * e.g. to prevent another resume from preresume processing
 * the raid set all over again.
 */
#घोषणा RT_FLAG_RS_PRERESUMED		0
#घोषणा RT_FLAG_RS_RESUMED		1
#घोषणा RT_FLAG_RS_BITMAP_LOADED	2
#घोषणा RT_FLAG_UPDATE_SBS		3
#घोषणा RT_FLAG_RESHAPE_RS		4
#घोषणा RT_FLAG_RS_SUSPENDED		5
#घोषणा RT_FLAG_RS_IN_SYNC		6
#घोषणा RT_FLAG_RS_RESYNCING		7
#घोषणा RT_FLAG_RS_GROW			8

/* Array elements of 64 bit needed क्रम rebuild/failed disk bits */
#घोषणा DISKS_ARRAY_ELEMS ((MAX_RAID_DEVICES + (माप(uपूर्णांक64_t) * 8 - 1)) / माप(uपूर्णांक64_t) / 8)

/*
 * raid set level, layout and chunk sectors backup/restore
 */
काष्ठा rs_layout अणु
	पूर्णांक new_level;
	पूर्णांक new_layout;
	पूर्णांक new_chunk_sectors;
पूर्ण;

काष्ठा raid_set अणु
	काष्ठा dm_target *ti;

	uपूर्णांक32_t stripe_cache_entries;
	अचिन्हित दीर्घ ctr_flags;
	अचिन्हित दीर्घ runसमय_flags;

	uपूर्णांक64_t rebuild_disks[DISKS_ARRAY_ELEMS];

	पूर्णांक raid_disks;
	पूर्णांक delta_disks;
	पूर्णांक data_offset;
	पूर्णांक raid10_copies;
	पूर्णांक requested_biपंचांगap_chunk_sectors;

	काष्ठा mddev md;
	काष्ठा raid_type *raid_type;

	sector_t array_sectors;
	sector_t dev_sectors;

	/* Optional raid4/5/6 journal device */
	काष्ठा journal_dev अणु
		काष्ठा dm_dev *dev;
		काष्ठा md_rdev rdev;
		पूर्णांक mode;
	पूर्ण journal_dev;

	काष्ठा raid_dev dev[];
पूर्ण;

अटल व्योम rs_config_backup(काष्ठा raid_set *rs, काष्ठा rs_layout *l)
अणु
	काष्ठा mddev *mddev = &rs->md;

	l->new_level = mddev->new_level;
	l->new_layout = mddev->new_layout;
	l->new_chunk_sectors = mddev->new_chunk_sectors;
पूर्ण

अटल व्योम rs_config_restore(काष्ठा raid_set *rs, काष्ठा rs_layout *l)
अणु
	काष्ठा mddev *mddev = &rs->md;

	mddev->new_level = l->new_level;
	mddev->new_layout = l->new_layout;
	mddev->new_chunk_sectors = l->new_chunk_sectors;
पूर्ण

/* raid10 algorithms (i.e. क्रमmats) */
#घोषणा	ALGORITHM_RAID10_DEFAULT	0
#घोषणा	ALGORITHM_RAID10_NEAR		1
#घोषणा	ALGORITHM_RAID10_OFFSET		2
#घोषणा	ALGORITHM_RAID10_FAR		3

/* Supported raid types and properties. */
अटल काष्ठा raid_type अणु
	स्थिर अक्षर *name;		/* RAID algorithm. */
	स्थिर अक्षर *descr;		/* Descriptor text क्रम logging. */
	स्थिर अचिन्हित पूर्णांक parity_devs;	/* # of parity devices. */
	स्थिर अचिन्हित पूर्णांक minimal_devs;/* minimal # of devices in set. */
	स्थिर अचिन्हित पूर्णांक level;	/* RAID level. */
	स्थिर अचिन्हित पूर्णांक algorithm;	/* RAID algorithm. */
पूर्ण raid_types[] = अणु
	अणु"raid0",	  "raid0 (striping)",			    0, 2, 0,  0 /* NONE */पूर्ण,
	अणु"raid1",	  "raid1 (mirroring)",			    0, 2, 1,  0 /* NONE */पूर्ण,
	अणु"raid10_far",	  "raid10 far (striped mirrors)",	    0, 2, 10, ALGORITHM_RAID10_FARपूर्ण,
	अणु"raid10_offset", "raid10 offset (striped mirrors)",	    0, 2, 10, ALGORITHM_RAID10_OFFSETपूर्ण,
	अणु"raid10_near",	  "raid10 near (striped mirrors)",	    0, 2, 10, ALGORITHM_RAID10_NEARपूर्ण,
	अणु"raid10",	  "raid10 (striped mirrors)",		    0, 2, 10, ALGORITHM_RAID10_DEFAULTपूर्ण,
	अणु"raid4",	  "raid4 (dedicated first parity disk)",    1, 2, 5,  ALGORITHM_PARITY_0पूर्ण, /* raid4 layout = raid5_0 */
	अणु"raid5_n",	  "raid5 (dedicated last parity disk)",	    1, 2, 5,  ALGORITHM_PARITY_Nपूर्ण,
	अणु"raid5_ls",	  "raid5 (left symmetric)",		    1, 2, 5,  ALGORITHM_LEFT_SYMMETRICपूर्ण,
	अणु"raid5_rs",	  "raid5 (right symmetric)",		    1, 2, 5,  ALGORITHM_RIGHT_SYMMETRICपूर्ण,
	अणु"raid5_la",	  "raid5 (left asymmetric)",		    1, 2, 5,  ALGORITHM_LEFT_ASYMMETRICपूर्ण,
	अणु"raid5_ra",	  "raid5 (right asymmetric)",		    1, 2, 5,  ALGORITHM_RIGHT_ASYMMETRICपूर्ण,
	अणु"raid6_zr",	  "raid6 (zero restart)",		    2, 4, 6,  ALGORITHM_ROTATING_ZERO_RESTARTपूर्ण,
	अणु"raid6_nr",	  "raid6 (N restart)",			    2, 4, 6,  ALGORITHM_ROTATING_N_RESTARTपूर्ण,
	अणु"raid6_nc",	  "raid6 (N continue)",			    2, 4, 6,  ALGORITHM_ROTATING_N_CONTINUEपूर्ण,
	अणु"raid6_n_6",	  "raid6 (dedicated parity/Q n/6)",	    2, 4, 6,  ALGORITHM_PARITY_N_6पूर्ण,
	अणु"raid6_ls_6",	  "raid6 (left symmetric dedicated Q 6)",   2, 4, 6,  ALGORITHM_LEFT_SYMMETRIC_6पूर्ण,
	अणु"raid6_rs_6",	  "raid6 (right symmetric dedicated Q 6)",  2, 4, 6,  ALGORITHM_RIGHT_SYMMETRIC_6पूर्ण,
	अणु"raid6_la_6",	  "raid6 (left asymmetric dedicated Q 6)",  2, 4, 6,  ALGORITHM_LEFT_ASYMMETRIC_6पूर्ण,
	अणु"raid6_ra_6",	  "raid6 (right asymmetric dedicated Q 6)", 2, 4, 6,  ALGORITHM_RIGHT_ASYMMETRIC_6पूर्ण
पूर्ण;

/* True, अगर @v is in inclusive range [@min, @max] */
अटल bool __within_range(दीर्घ v, दीर्घ min, दीर्घ max)
अणु
	वापस v >= min && v <= max;
पूर्ण

/* All table line arguments are defined here */
अटल काष्ठा arg_name_flag अणु
	स्थिर अचिन्हित दीर्घ flag;
	स्थिर अक्षर *name;
पूर्ण __arg_name_flags[] = अणु
	अणु CTR_FLAG_SYNC, "sync"पूर्ण,
	अणु CTR_FLAG_NOSYNC, "nosync"पूर्ण,
	अणु CTR_FLAG_REBUILD, "rebuild"पूर्ण,
	अणु CTR_FLAG_DAEMON_SLEEP, "daemon_sleep"पूर्ण,
	अणु CTR_FLAG_MIN_RECOVERY_RATE, "min_recovery_rate"पूर्ण,
	अणु CTR_FLAG_MAX_RECOVERY_RATE, "max_recovery_rate"पूर्ण,
	अणु CTR_FLAG_MAX_WRITE_BEHIND, "max_write_behind"पूर्ण,
	अणु CTR_FLAG_WRITE_MOSTLY, "write_mostly"पूर्ण,
	अणु CTR_FLAG_STRIPE_CACHE, "stripe_cache"पूर्ण,
	अणु CTR_FLAG_REGION_SIZE, "region_size"पूर्ण,
	अणु CTR_FLAG_RAID10_COPIES, "raid10_copies"पूर्ण,
	अणु CTR_FLAG_RAID10_FORMAT, "raid10_format"पूर्ण,
	अणु CTR_FLAG_DATA_OFFSET, "data_offset"पूर्ण,
	अणु CTR_FLAG_DELTA_DISKS, "delta_disks"पूर्ण,
	अणु CTR_FLAG_RAID10_USE_NEAR_SETS, "raid10_use_near_sets"पूर्ण,
	अणु CTR_FLAG_JOURNAL_DEV, "journal_dev" पूर्ण,
	अणु CTR_FLAG_JOURNAL_MODE, "journal_mode" पूर्ण,
पूर्ण;

/* Return argument name string क्रम given @flag */
अटल स्थिर अक्षर *dm_raid_arg_name_by_flag(स्थिर uपूर्णांक32_t flag)
अणु
	अगर (hweight32(flag) == 1) अणु
		काष्ठा arg_name_flag *anf = __arg_name_flags + ARRAY_SIZE(__arg_name_flags);

		जबतक (anf-- > __arg_name_flags)
			अगर (flag & anf->flag)
				वापस anf->name;

	पूर्ण अन्यथा
		DMERR("%s called with more than one flag!", __func__);

	वापस शून्य;
पूर्ण

/* Define correlation of raid456 journal cache modes and dm-raid target line parameters */
अटल काष्ठा अणु
	स्थिर पूर्णांक mode;
	स्थिर अक्षर *param;
पूर्ण _raid456_journal_mode[] = अणु
	अणु R5C_JOURNAL_MODE_WRITE_THROUGH , "writethrough" पूर्ण,
	अणु R5C_JOURNAL_MODE_WRITE_BACK    , "writeback" पूर्ण
पूर्ण;

/* Return MD raid4/5/6 journal mode क्रम dm @journal_mode one */
अटल पूर्णांक dm_raid_journal_mode_to_md(स्थिर अक्षर *mode)
अणु
	पूर्णांक m = ARRAY_SIZE(_raid456_journal_mode);

	जबतक (m--)
		अगर (!strहालcmp(mode, _raid456_journal_mode[m].param))
			वापस _raid456_journal_mode[m].mode;

	वापस -EINVAL;
पूर्ण

/* Return dm-raid raid4/5/6 journal mode string क्रम @mode */
अटल स्थिर अक्षर *md_journal_mode_to_dm_raid(स्थिर पूर्णांक mode)
अणु
	पूर्णांक m = ARRAY_SIZE(_raid456_journal_mode);

	जबतक (m--)
		अगर (mode == _raid456_journal_mode[m].mode)
			वापस _raid456_journal_mode[m].param;

	वापस "unknown";
पूर्ण

/*
 * Bool helpers to test क्रम various raid levels of a raid set.
 * It's level as reported by the superblock rather than
 * the requested raid_type passed to the स्थिरructor.
 */
/* Return true, अगर raid set in @rs is raid0 */
अटल bool rs_is_raid0(काष्ठा raid_set *rs)
अणु
	वापस !rs->md.level;
पूर्ण

/* Return true, अगर raid set in @rs is raid1 */
अटल bool rs_is_raid1(काष्ठा raid_set *rs)
अणु
	वापस rs->md.level == 1;
पूर्ण

/* Return true, अगर raid set in @rs is raid10 */
अटल bool rs_is_raid10(काष्ठा raid_set *rs)
अणु
	वापस rs->md.level == 10;
पूर्ण

/* Return true, अगर raid set in @rs is level 6 */
अटल bool rs_is_raid6(काष्ठा raid_set *rs)
अणु
	वापस rs->md.level == 6;
पूर्ण

/* Return true, अगर raid set in @rs is level 4, 5 or 6 */
अटल bool rs_is_raid456(काष्ठा raid_set *rs)
अणु
	वापस __within_range(rs->md.level, 4, 6);
पूर्ण

/* Return true, अगर raid set in @rs is reshapable */
अटल bool __is_raid10_far(पूर्णांक layout);
अटल bool rs_is_reshapable(काष्ठा raid_set *rs)
अणु
	वापस rs_is_raid456(rs) ||
	       (rs_is_raid10(rs) && !__is_raid10_far(rs->md.new_layout));
पूर्ण

/* Return true, अगर raid set in @rs is recovering */
अटल bool rs_is_recovering(काष्ठा raid_set *rs)
अणु
	वापस rs->md.recovery_cp < rs->md.dev_sectors;
पूर्ण

/* Return true, अगर raid set in @rs is reshaping */
अटल bool rs_is_reshaping(काष्ठा raid_set *rs)
अणु
	वापस rs->md.reshape_position != MaxSector;
पूर्ण

/*
 * bool helpers to test क्रम various raid levels of a raid type @rt
 */

/* Return true, अगर raid type in @rt is raid0 */
अटल bool rt_is_raid0(काष्ठा raid_type *rt)
अणु
	वापस !rt->level;
पूर्ण

/* Return true, अगर raid type in @rt is raid1 */
अटल bool rt_is_raid1(काष्ठा raid_type *rt)
अणु
	वापस rt->level == 1;
पूर्ण

/* Return true, अगर raid type in @rt is raid10 */
अटल bool rt_is_raid10(काष्ठा raid_type *rt)
अणु
	वापस rt->level == 10;
पूर्ण

/* Return true, अगर raid type in @rt is raid4/5 */
अटल bool rt_is_raid45(काष्ठा raid_type *rt)
अणु
	वापस __within_range(rt->level, 4, 5);
पूर्ण

/* Return true, अगर raid type in @rt is raid6 */
अटल bool rt_is_raid6(काष्ठा raid_type *rt)
अणु
	वापस rt->level == 6;
पूर्ण

/* Return true, अगर raid type in @rt is raid4/5/6 */
अटल bool rt_is_raid456(काष्ठा raid_type *rt)
अणु
	वापस __within_range(rt->level, 4, 6);
पूर्ण
/* END: raid level bools */

/* Return valid ctr flags क्रम the raid level of @rs */
अटल अचिन्हित दीर्घ __valid_flags(काष्ठा raid_set *rs)
अणु
	अगर (rt_is_raid0(rs->raid_type))
		वापस RAID0_VALID_FLAGS;
	अन्यथा अगर (rt_is_raid1(rs->raid_type))
		वापस RAID1_VALID_FLAGS;
	अन्यथा अगर (rt_is_raid10(rs->raid_type))
		वापस RAID10_VALID_FLAGS;
	अन्यथा अगर (rt_is_raid45(rs->raid_type))
		वापस RAID45_VALID_FLAGS;
	अन्यथा अगर (rt_is_raid6(rs->raid_type))
		वापस RAID6_VALID_FLAGS;

	वापस 0;
पूर्ण

/*
 * Check क्रम valid flags set on @rs
 *
 * Has to be called after parsing of the ctr flags!
 */
अटल पूर्णांक rs_check_क्रम_valid_flags(काष्ठा raid_set *rs)
अणु
	अगर (rs->ctr_flags & ~__valid_flags(rs)) अणु
		rs->ti->error = "Invalid flags combination";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* MD raid10 bit definitions and helpers */
#घोषणा RAID10_OFFSET			(1 << 16) /* stripes with data copies area adjacent on devices */
#घोषणा RAID10_BROCKEN_USE_FAR_SETS	(1 << 17) /* Broken in raid10.c: use sets instead of whole stripe rotation */
#घोषणा RAID10_USE_FAR_SETS		(1 << 18) /* Use sets instead of whole stripe rotation */
#घोषणा RAID10_FAR_COPIES_SHIFT		8	  /* raid10 # far copies shअगरt (2nd byte of layout) */

/* Return md raid10 near copies क्रम @layout */
अटल अचिन्हित पूर्णांक __raid10_near_copies(पूर्णांक layout)
अणु
	वापस layout & 0xFF;
पूर्ण

/* Return md raid10 far copies क्रम @layout */
अटल अचिन्हित पूर्णांक __raid10_far_copies(पूर्णांक layout)
अणु
	वापस __raid10_near_copies(layout >> RAID10_FAR_COPIES_SHIFT);
पूर्ण

/* Return true अगर md raid10 offset क्रम @layout */
अटल bool __is_raid10_offset(पूर्णांक layout)
अणु
	वापस !!(layout & RAID10_OFFSET);
पूर्ण

/* Return true अगर md raid10 near क्रम @layout */
अटल bool __is_raid10_near(पूर्णांक layout)
अणु
	वापस !__is_raid10_offset(layout) && __raid10_near_copies(layout) > 1;
पूर्ण

/* Return true अगर md raid10 far क्रम @layout */
अटल bool __is_raid10_far(पूर्णांक layout)
अणु
	वापस !__is_raid10_offset(layout) && __raid10_far_copies(layout) > 1;
पूर्ण

/* Return md raid10 layout string क्रम @layout */
अटल स्थिर अक्षर *raid10_md_layout_to_क्रमmat(पूर्णांक layout)
अणु
	/*
	 * Bit 16 stands क्रम "offset"
	 * (i.e. adjacent stripes hold copies)
	 *
	 * Refer to MD's raid10.c क्रम details
	 */
	अगर (__is_raid10_offset(layout))
		वापस "offset";

	अगर (__raid10_near_copies(layout) > 1)
		वापस "near";

	अगर (__raid10_far_copies(layout) > 1)
		वापस "far";

	वापस "unknown";
पूर्ण

/* Return md raid10 algorithm क्रम @name */
अटल पूर्णांक raid10_name_to_क्रमmat(स्थिर अक्षर *name)
अणु
	अगर (!strहालcmp(name, "near"))
		वापस ALGORITHM_RAID10_NEAR;
	अन्यथा अगर (!strहालcmp(name, "offset"))
		वापस ALGORITHM_RAID10_OFFSET;
	अन्यथा अगर (!strहालcmp(name, "far"))
		वापस ALGORITHM_RAID10_FAR;

	वापस -EINVAL;
पूर्ण

/* Return md raid10 copies क्रम @layout */
अटल अचिन्हित पूर्णांक raid10_md_layout_to_copies(पूर्णांक layout)
अणु
	वापस max(__raid10_near_copies(layout), __raid10_far_copies(layout));
पूर्ण

/* Return md raid10 क्रमmat id क्रम @क्रमmat string */
अटल पूर्णांक raid10_क्रमmat_to_md_layout(काष्ठा raid_set *rs,
				      अचिन्हित पूर्णांक algorithm,
				      अचिन्हित पूर्णांक copies)
अणु
	अचिन्हित पूर्णांक n = 1, f = 1, r = 0;

	/*
	 * MD resilienece flaw:
	 *
	 * enabling use_far_sets क्रम far/offset क्रमmats causes copies
	 * to be colocated on the same devs together with their origins!
	 *
	 * -> disable it क्रम now in the definition above
	 */
	अगर (algorithm == ALGORITHM_RAID10_DEFAULT ||
	    algorithm == ALGORITHM_RAID10_NEAR)
		n = copies;

	अन्यथा अगर (algorithm == ALGORITHM_RAID10_OFFSET) अणु
		f = copies;
		r = RAID10_OFFSET;
		अगर (!test_bit(__CTR_FLAG_RAID10_USE_NEAR_SETS, &rs->ctr_flags))
			r |= RAID10_USE_FAR_SETS;

	पूर्ण अन्यथा अगर (algorithm == ALGORITHM_RAID10_FAR) अणु
		f = copies;
		अगर (!test_bit(__CTR_FLAG_RAID10_USE_NEAR_SETS, &rs->ctr_flags))
			r |= RAID10_USE_FAR_SETS;

	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस r | (f << RAID10_FAR_COPIES_SHIFT) | n;
पूर्ण
/* END: MD raid10 bit definitions and helpers */

/* Check क्रम any of the raid10 algorithms */
अटल bool __got_raid10(काष्ठा raid_type *rtp, स्थिर पूर्णांक layout)
अणु
	अगर (rtp->level == 10) अणु
		चयन (rtp->algorithm) अणु
		हाल ALGORITHM_RAID10_DEFAULT:
		हाल ALGORITHM_RAID10_NEAR:
			वापस __is_raid10_near(layout);
		हाल ALGORITHM_RAID10_OFFSET:
			वापस __is_raid10_offset(layout);
		हाल ALGORITHM_RAID10_FAR:
			वापस __is_raid10_far(layout);
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/* Return raid_type क्रम @name */
अटल काष्ठा raid_type *get_raid_type(स्थिर अक्षर *name)
अणु
	काष्ठा raid_type *rtp = raid_types + ARRAY_SIZE(raid_types);

	जबतक (rtp-- > raid_types)
		अगर (!strहालcmp(rtp->name, name))
			वापस rtp;

	वापस शून्य;
पूर्ण

/* Return raid_type क्रम @name based derived from @level and @layout */
अटल काष्ठा raid_type *get_raid_type_by_ll(स्थिर पूर्णांक level, स्थिर पूर्णांक layout)
अणु
	काष्ठा raid_type *rtp = raid_types + ARRAY_SIZE(raid_types);

	जबतक (rtp-- > raid_types) अणु
		/* RAID10 special checks based on @layout flags/properties */
		अगर (rtp->level == level &&
		    (__got_raid10(rtp, layout) || rtp->algorithm == layout))
			वापस rtp;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Adjust rdev sectors */
अटल व्योम rs_set_rdev_sectors(काष्ठा raid_set *rs)
अणु
	काष्ठा mddev *mddev = &rs->md;
	काष्ठा md_rdev *rdev;

	/*
	 * raid10 sets rdev->sector to the device size, which
	 * is unपूर्णांकended in हाल of out-of-place reshaping
	 */
	rdev_क्रम_each(rdev, mddev)
		अगर (!test_bit(Journal, &rdev->flags))
			rdev->sectors = mddev->dev_sectors;
पूर्ण

/*
 * Change bdev capacity of @rs in हाल of a disk add/हटाओ reshape
 */
अटल व्योम rs_set_capacity(काष्ठा raid_set *rs)
अणु
	काष्ठा gendisk *gendisk = dm_disk(dm_table_get_md(rs->ti->table));

	set_capacity_and_notअगरy(gendisk, rs->md.array_sectors);
पूर्ण

/*
 * Set the mddev properties in @rs to the current
 * ones retrieved from the freshest superblock
 */
अटल व्योम rs_set_cur(काष्ठा raid_set *rs)
अणु
	काष्ठा mddev *mddev = &rs->md;

	mddev->new_level = mddev->level;
	mddev->new_layout = mddev->layout;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
पूर्ण

/*
 * Set the mddev properties in @rs to the new
 * ones requested by the ctr
 */
अटल व्योम rs_set_new(काष्ठा raid_set *rs)
अणु
	काष्ठा mddev *mddev = &rs->md;

	mddev->level = mddev->new_level;
	mddev->layout = mddev->new_layout;
	mddev->chunk_sectors = mddev->new_chunk_sectors;
	mddev->raid_disks = rs->raid_disks;
	mddev->delta_disks = 0;
पूर्ण

अटल काष्ठा raid_set *raid_set_alloc(काष्ठा dm_target *ti, काष्ठा raid_type *raid_type,
				       अचिन्हित पूर्णांक raid_devs)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा raid_set *rs;

	अगर (raid_devs <= raid_type->parity_devs) अणु
		ti->error = "Insufficient number of devices";
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	rs = kzalloc(काष्ठा_size(rs, dev, raid_devs), GFP_KERNEL);
	अगर (!rs) अणु
		ti->error = "Cannot allocate raid context";
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	mddev_init(&rs->md);

	rs->raid_disks = raid_devs;
	rs->delta_disks = 0;

	rs->ti = ti;
	rs->raid_type = raid_type;
	rs->stripe_cache_entries = 256;
	rs->md.raid_disks = raid_devs;
	rs->md.level = raid_type->level;
	rs->md.new_level = rs->md.level;
	rs->md.layout = raid_type->algorithm;
	rs->md.new_layout = rs->md.layout;
	rs->md.delta_disks = 0;
	rs->md.recovery_cp = MaxSector;

	क्रम (i = 0; i < raid_devs; i++)
		md_rdev_init(&rs->dev[i].rdev);

	/*
	 * Reमुख्यing items to be initialized by further RAID params:
	 *  rs->md.persistent
	 *  rs->md.बाह्यal
	 *  rs->md.chunk_sectors
	 *  rs->md.new_chunk_sectors
	 *  rs->md.dev_sectors
	 */

	वापस rs;
पूर्ण

/* Free all @rs allocations */
अटल व्योम raid_set_मुक्त(काष्ठा raid_set *rs)
अणु
	पूर्णांक i;

	अगर (rs->journal_dev.dev) अणु
		md_rdev_clear(&rs->journal_dev.rdev);
		dm_put_device(rs->ti, rs->journal_dev.dev);
	पूर्ण

	क्रम (i = 0; i < rs->raid_disks; i++) अणु
		अगर (rs->dev[i].meta_dev)
			dm_put_device(rs->ti, rs->dev[i].meta_dev);
		md_rdev_clear(&rs->dev[i].rdev);
		अगर (rs->dev[i].data_dev)
			dm_put_device(rs->ti, rs->dev[i].data_dev);
	पूर्ण

	kमुक्त(rs);
पूर्ण

/*
 * For every device we have two words
 *  <meta_dev>: meta device name or '-' अगर missing
 *  <data_dev>: data device name or '-' अगर missing
 *
 * The following are permitted:
 *    - -
 *    - <data_dev>
 *    <meta_dev> <data_dev>
 *
 * The following is not allowed:
 *    <meta_dev> -
 *
 * This code parses those words.  If there is a failure,
 * the caller must use raid_set_मुक्त() to unwind the operations.
 */
अटल पूर्णांक parse_dev_params(काष्ठा raid_set *rs, काष्ठा dm_arg_set *as)
अणु
	पूर्णांक i;
	पूर्णांक rebuild = 0;
	पूर्णांक metadata_available = 0;
	पूर्णांक r = 0;
	स्थिर अक्षर *arg;

	/* Put off the number of raid devices argument to get to dev pairs */
	arg = dm_shअगरt_arg(as);
	अगर (!arg)
		वापस -EINVAL;

	क्रम (i = 0; i < rs->raid_disks; i++) अणु
		rs->dev[i].rdev.raid_disk = i;

		rs->dev[i].meta_dev = शून्य;
		rs->dev[i].data_dev = शून्य;

		/*
		 * There are no offsets initially.
		 * Out of place reshape will set them accordingly.
		 */
		rs->dev[i].rdev.data_offset = 0;
		rs->dev[i].rdev.new_data_offset = 0;
		rs->dev[i].rdev.mddev = &rs->md;

		arg = dm_shअगरt_arg(as);
		अगर (!arg)
			वापस -EINVAL;

		अगर (म_भेद(arg, "-")) अणु
			r = dm_get_device(rs->ti, arg, dm_table_get_mode(rs->ti->table),
					  &rs->dev[i].meta_dev);
			अगर (r) अणु
				rs->ti->error = "RAID metadata device lookup failure";
				वापस r;
			पूर्ण

			rs->dev[i].rdev.sb_page = alloc_page(GFP_KERNEL);
			अगर (!rs->dev[i].rdev.sb_page) अणु
				rs->ti->error = "Failed to allocate superblock page";
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		arg = dm_shअगरt_arg(as);
		अगर (!arg)
			वापस -EINVAL;

		अगर (!म_भेद(arg, "-")) अणु
			अगर (!test_bit(In_sync, &rs->dev[i].rdev.flags) &&
			    (!rs->dev[i].rdev.recovery_offset)) अणु
				rs->ti->error = "Drive designated for rebuild not specified";
				वापस -EINVAL;
			पूर्ण

			अगर (rs->dev[i].meta_dev) अणु
				rs->ti->error = "No data device supplied with metadata device";
				वापस -EINVAL;
			पूर्ण

			जारी;
		पूर्ण

		r = dm_get_device(rs->ti, arg, dm_table_get_mode(rs->ti->table),
				  &rs->dev[i].data_dev);
		अगर (r) अणु
			rs->ti->error = "RAID device lookup failure";
			वापस r;
		पूर्ण

		अगर (rs->dev[i].meta_dev) अणु
			metadata_available = 1;
			rs->dev[i].rdev.meta_bdev = rs->dev[i].meta_dev->bdev;
		पूर्ण
		rs->dev[i].rdev.bdev = rs->dev[i].data_dev->bdev;
		list_add_tail(&rs->dev[i].rdev.same_set, &rs->md.disks);
		अगर (!test_bit(In_sync, &rs->dev[i].rdev.flags))
			rebuild++;
	पूर्ण

	अगर (rs->journal_dev.dev)
		list_add_tail(&rs->journal_dev.rdev.same_set, &rs->md.disks);

	अगर (metadata_available) अणु
		rs->md.बाह्यal = 0;
		rs->md.persistent = 1;
		rs->md.major_version = 2;
	पूर्ण अन्यथा अगर (rebuild && !rs->md.recovery_cp) अणु
		/*
		 * Without metadata, we will not be able to tell अगर the array
		 * is in-sync or not - we must assume it is not.  Thereक्रमe,
		 * it is impossible to rebuild a drive.
		 *
		 * Even अगर there is metadata, the on-disk inक्रमmation may
		 * indicate that the array is not in-sync and it will then
		 * fail at that समय.
		 *
		 * User could specअगरy 'nosync' option अगर desperate.
		 */
		rs->ti->error = "Unable to rebuild drive while array is not in-sync";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * validate_region_size
 * @rs
 * @region_size:  region size in sectors.  If 0, pick a size (4MiB शेष).
 *
 * Set rs->md.biपंचांगap_info.chunksize (which really refers to 'region size').
 * Ensure that (ti->len/region_size < 2^21) - required by MD biपंचांगap.
 *
 * Returns: 0 on success, -EINVAL on failure.
 */
अटल पूर्णांक validate_region_size(काष्ठा raid_set *rs, अचिन्हित दीर्घ region_size)
अणु
	अचिन्हित दीर्घ min_region_size = rs->ti->len / (1 << 21);

	अगर (rs_is_raid0(rs))
		वापस 0;

	अगर (!region_size) अणु
		/*
		 * Choose a reasonable शेष.	 All figures in sectors.
		 */
		अगर (min_region_size > (1 << 13)) अणु
			/* If not a घातer of 2, make it the next घातer of 2 */
			region_size = roundup_घात_of_two(min_region_size);
			DMINFO("Choosing default region size of %lu sectors",
			       region_size);
		पूर्ण अन्यथा अणु
			DMINFO("Choosing default region size of 4MiB");
			region_size = 1 << 13; /* sectors */
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Validate user-supplied value.
		 */
		अगर (region_size > rs->ti->len) अणु
			rs->ti->error = "Supplied region size is too large";
			वापस -EINVAL;
		पूर्ण

		अगर (region_size < min_region_size) अणु
			DMERR("Supplied region_size (%lu sectors) below minimum (%lu)",
			      region_size, min_region_size);
			rs->ti->error = "Supplied region size is too small";
			वापस -EINVAL;
		पूर्ण

		अगर (!is_घातer_of_2(region_size)) अणु
			rs->ti->error = "Region size is not a power of 2";
			वापस -EINVAL;
		पूर्ण

		अगर (region_size < rs->md.chunk_sectors) अणु
			rs->ti->error = "Region size is smaller than the chunk size";
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Convert sectors to bytes.
	 */
	rs->md.biपंचांगap_info.chunksize = to_bytes(region_size);

	वापस 0;
पूर्ण

/*
 * validate_raid_redundancy
 * @rs
 *
 * Determine अगर there are enough devices in the array that haven't
 * failed (or are being rebuilt) to क्रमm a usable array.
 *
 * Returns: 0 on success, -EINVAL on failure.
 */
अटल पूर्णांक validate_raid_redundancy(काष्ठा raid_set *rs)
अणु
	अचिन्हित पूर्णांक i, rebuild_cnt = 0;
	अचिन्हित पूर्णांक rebuilds_per_group = 0, copies;
	अचिन्हित पूर्णांक group_size, last_group_start;

	क्रम (i = 0; i < rs->md.raid_disks; i++)
		अगर (!test_bit(In_sync, &rs->dev[i].rdev.flags) ||
		    !rs->dev[i].rdev.sb_page)
			rebuild_cnt++;

	चयन (rs->md.level) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		अगर (rebuild_cnt >= rs->md.raid_disks)
			जाओ too_many;
		अवरोध;
	हाल 4:
	हाल 5:
	हाल 6:
		अगर (rebuild_cnt > rs->raid_type->parity_devs)
			जाओ too_many;
		अवरोध;
	हाल 10:
		copies = raid10_md_layout_to_copies(rs->md.new_layout);
		अगर (copies < 2) अणु
			DMERR("Bogus raid10 data copies < 2!");
			वापस -EINVAL;
		पूर्ण

		अगर (rebuild_cnt < copies)
			अवरोध;

		/*
		 * It is possible to have a higher rebuild count क्रम RAID10,
		 * as दीर्घ as the failed devices occur in dअगरferent mirror
		 * groups (i.e. dअगरferent stripes).
		 *
		 * When checking "near" क्रमmat, make sure no adjacent devices
		 * have failed beyond what can be handled.  In addition to the
		 * simple हाल where the number of devices is a multiple of the
		 * number of copies, we must also handle हालs where the number
		 * of devices is not a multiple of the number of copies.
		 * E.g.	   dev1 dev2 dev3 dev4 dev5
		 *	    A	 A    B	   B	C
		 *	    C	 D    D	   E	E
		 */
		अगर (__is_raid10_near(rs->md.new_layout)) अणु
			क्रम (i = 0; i < rs->md.raid_disks; i++) अणु
				अगर (!(i % copies))
					rebuilds_per_group = 0;
				अगर ((!rs->dev[i].rdev.sb_page ||
				    !test_bit(In_sync, &rs->dev[i].rdev.flags)) &&
				    (++rebuilds_per_group >= copies))
					जाओ too_many;
			पूर्ण
			अवरोध;
		पूर्ण

		/*
		 * When checking "far" and "offset" क्रमmats, we need to ensure
		 * that the device that holds its copy is not also dead or
		 * being rebuilt.  (Note that "far" and "offset" क्रमmats only
		 * support two copies right now.  These क्रमmats also only ever
		 * use the 'use_far_sets' variant.)
		 *
		 * This check is somewhat complicated by the need to account
		 * क्रम arrays that are not a multiple of (far) copies.	This
		 * results in the need to treat the last (potentially larger)
		 * set dअगरferently.
		 */
		group_size = (rs->md.raid_disks / copies);
		last_group_start = (rs->md.raid_disks / group_size) - 1;
		last_group_start *= group_size;
		क्रम (i = 0; i < rs->md.raid_disks; i++) अणु
			अगर (!(i % copies) && !(i > last_group_start))
				rebuilds_per_group = 0;
			अगर ((!rs->dev[i].rdev.sb_page ||
			     !test_bit(In_sync, &rs->dev[i].rdev.flags)) &&
			    (++rebuilds_per_group >= copies))
					जाओ too_many;
		पूर्ण
		अवरोध;
	शेष:
		अगर (rebuild_cnt)
			वापस -EINVAL;
	पूर्ण

	वापस 0;

too_many:
	वापस -EINVAL;
पूर्ण

/*
 * Possible arguments are...
 *	<chunk_size> [optional_args]
 *
 * Argument definitions
 *    <chunk_size>			The number of sectors per disk that
 *					will क्रमm the "stripe"
 *    [[no]sync]			Force or prevent recovery of the
 *					entire array
 *    [rebuild <idx>]			Rebuild the drive indicated by the index
 *    [daemon_sleep <ms>]		Time between biपंचांगap daemon work to
 *					clear bits
 *    [min_recovery_rate <kB/sec/disk>]	Throttle RAID initialization
 *    [max_recovery_rate <kB/sec/disk>]	Throttle RAID initialization
 *    [ग_लिखो_mostly <idx>]		Indicate a ग_लिखो mostly drive via index
 *    [max_ग_लिखो_behind <sectors>]	See '-write-behind=' (man mdadm)
 *    [stripe_cache <sectors>]		Stripe cache size क्रम higher RAIDs
 *    [region_size <sectors>]		Defines granularity of biपंचांगap
 *    [journal_dev <dev>]		raid4/5/6 journaling deviice
 *    					(i.e. ग_लिखो hole closing log)
 *
 * RAID10-only options:
 *    [raid10_copies <# copies>]	Number of copies.  (Default: 2)
 *    [raid10_क्रमmat <near|far|offset>] Layout algorithm.  (Default: near)
 */
अटल पूर्णांक parse_raid_params(काष्ठा raid_set *rs, काष्ठा dm_arg_set *as,
			     अचिन्हित पूर्णांक num_raid_params)
अणु
	पूर्णांक value, raid10_क्रमmat = ALGORITHM_RAID10_DEFAULT;
	अचिन्हित पूर्णांक raid10_copies = 2;
	अचिन्हित पूर्णांक i, ग_लिखो_mostly = 0;
	अचिन्हित पूर्णांक region_size = 0;
	sector_t max_io_len;
	स्थिर अक्षर *arg, *key;
	काष्ठा raid_dev *rd;
	काष्ठा raid_type *rt = rs->raid_type;

	arg = dm_shअगरt_arg(as);
	num_raid_params--; /* Account क्रम chunk_size argument */

	अगर (kstrtoपूर्णांक(arg, 10, &value) < 0) अणु
		rs->ti->error = "Bad numerical argument given for chunk_size";
		वापस -EINVAL;
	पूर्ण

	/*
	 * First, parse the in-order required arguments
	 * "chunk_size" is the only argument of this type.
	 */
	अगर (rt_is_raid1(rt)) अणु
		अगर (value)
			DMERR("Ignoring chunk size parameter for RAID 1");
		value = 0;
	पूर्ण अन्यथा अगर (!is_घातer_of_2(value)) अणु
		rs->ti->error = "Chunk size must be a power of 2";
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (value < 8) अणु
		rs->ti->error = "Chunk size value is too small";
		वापस -EINVAL;
	पूर्ण

	rs->md.new_chunk_sectors = rs->md.chunk_sectors = value;

	/*
	 * We set each inभागidual device as In_sync with a completed
	 * 'recovery_offset'.  If there has been a device failure or
	 * replacement then one of the following हालs applies:
	 *
	 *   1) User specअगरies 'rebuild'.
	 *	- Device is reset when param is पढ़ो.
	 *   2) A new device is supplied.
	 *	- No matching superblock found, resets device.
	 *   3) Device failure was transient and वापसs on reload.
	 *	- Failure noticed, resets device क्रम biपंचांगap replay.
	 *   4) Device hadn't completed recovery after previous failure.
	 *	- Superblock is पढ़ो and overrides recovery_offset.
	 *
	 * What is found in the superblocks of the devices is always
	 * authoritative, unless 'rebuild' or '[no]sync' was specअगरied.
	 */
	क्रम (i = 0; i < rs->raid_disks; i++) अणु
		set_bit(In_sync, &rs->dev[i].rdev.flags);
		rs->dev[i].rdev.recovery_offset = MaxSector;
	पूर्ण

	/*
	 * Second, parse the unordered optional arguments
	 */
	क्रम (i = 0; i < num_raid_params; i++) अणु
		key = dm_shअगरt_arg(as);
		अगर (!key) अणु
			rs->ti->error = "Not enough raid parameters given";
			वापस -EINVAL;
		पूर्ण

		अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_NOSYNC))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_NOSYNC, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one 'nosync' argument allowed";
				वापस -EINVAL;
			पूर्ण
			जारी;
		पूर्ण
		अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_SYNC))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_SYNC, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one 'sync' argument allowed";
				वापस -EINVAL;
			पूर्ण
			जारी;
		पूर्ण
		अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_RAID10_USE_NEAR_SETS))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_RAID10_USE_NEAR_SETS, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one 'raid10_use_new_sets' argument allowed";
				वापस -EINVAL;
			पूर्ण
			जारी;
		पूर्ण

		arg = dm_shअगरt_arg(as);
		i++; /* Account क्रम the argument pairs */
		अगर (!arg) अणु
			rs->ti->error = "Wrong number of raid parameters given";
			वापस -EINVAL;
		पूर्ण

		/*
		 * Parameters that take a string value are checked here.
		 */
		/* "raid10_क्रमmat अणुnear|offset|farपूर्ण */
		अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_RAID10_FORMAT))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_RAID10_FORMAT, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one 'raid10_format' argument pair allowed";
				वापस -EINVAL;
			पूर्ण
			अगर (!rt_is_raid10(rt)) अणु
				rs->ti->error = "'raid10_format' is an invalid parameter for this RAID type";
				वापस -EINVAL;
			पूर्ण
			raid10_क्रमmat = raid10_name_to_क्रमmat(arg);
			अगर (raid10_क्रमmat < 0) अणु
				rs->ti->error = "Invalid 'raid10_format' value given";
				वापस raid10_क्रमmat;
			पूर्ण
			जारी;
		पूर्ण

		/* "journal_dev <dev>" */
		अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_JOURNAL_DEV))) अणु
			पूर्णांक r;
			काष्ठा md_rdev *jdev;

			अगर (test_and_set_bit(__CTR_FLAG_JOURNAL_DEV, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one raid4/5/6 set journaling device allowed";
				वापस -EINVAL;
			पूर्ण
			अगर (!rt_is_raid456(rt)) अणु
				rs->ti->error = "'journal_dev' is an invalid parameter for this RAID type";
				वापस -EINVAL;
			पूर्ण
			r = dm_get_device(rs->ti, arg, dm_table_get_mode(rs->ti->table),
					  &rs->journal_dev.dev);
			अगर (r) अणु
				rs->ti->error = "raid4/5/6 journal device lookup failure";
				वापस r;
			पूर्ण
			jdev = &rs->journal_dev.rdev;
			md_rdev_init(jdev);
			jdev->mddev = &rs->md;
			jdev->bdev = rs->journal_dev.dev->bdev;
			jdev->sectors = to_sector(i_size_पढ़ो(jdev->bdev->bd_inode));
			अगर (jdev->sectors < MIN_RAID456_JOURNAL_SPACE) अणु
				rs->ti->error = "No space for raid4/5/6 journal";
				वापस -ENOSPC;
			पूर्ण
			rs->journal_dev.mode = R5C_JOURNAL_MODE_WRITE_THROUGH;
			set_bit(Journal, &jdev->flags);
			जारी;
		पूर्ण

		/* "journal_mode <mode>" ("journal_dev" mandatory!) */
		अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_JOURNAL_MODE))) अणु
			पूर्णांक r;

			अगर (!test_bit(__CTR_FLAG_JOURNAL_DEV, &rs->ctr_flags)) अणु
				rs->ti->error = "raid4/5/6 'journal_mode' is invalid without 'journal_dev'";
				वापस -EINVAL;
			पूर्ण
			अगर (test_and_set_bit(__CTR_FLAG_JOURNAL_MODE, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one raid4/5/6 'journal_mode' argument allowed";
				वापस -EINVAL;
			पूर्ण
			r = dm_raid_journal_mode_to_md(arg);
			अगर (r < 0) अणु
				rs->ti->error = "Invalid 'journal_mode' argument";
				वापस r;
			पूर्ण
			rs->journal_dev.mode = r;
			जारी;
		पूर्ण

		/*
		 * Parameters with number values from here on.
		 */
		अगर (kstrtoपूर्णांक(arg, 10, &value) < 0) अणु
			rs->ti->error = "Bad numerical argument given in raid params";
			वापस -EINVAL;
		पूर्ण

		अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_REBUILD))) अणु
			/*
			 * "rebuild" is being passed in by userspace to provide
			 * indexes of replaced devices and to set up additional
			 * devices on raid level takeover.
			 */
			अगर (!__within_range(value, 0, rs->raid_disks - 1)) अणु
				rs->ti->error = "Invalid rebuild index given";
				वापस -EINVAL;
			पूर्ण

			अगर (test_and_set_bit(value, (व्योम *) rs->rebuild_disks)) अणु
				rs->ti->error = "rebuild for this index already given";
				वापस -EINVAL;
			पूर्ण

			rd = rs->dev + value;
			clear_bit(In_sync, &rd->rdev.flags);
			clear_bit(Faulty, &rd->rdev.flags);
			rd->rdev.recovery_offset = 0;
			set_bit(__CTR_FLAG_REBUILD, &rs->ctr_flags);
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_WRITE_MOSTLY))) अणु
			अगर (!rt_is_raid1(rt)) अणु
				rs->ti->error = "write_mostly option is only valid for RAID1";
				वापस -EINVAL;
			पूर्ण

			अगर (!__within_range(value, 0, rs->md.raid_disks - 1)) अणु
				rs->ti->error = "Invalid write_mostly index given";
				वापस -EINVAL;
			पूर्ण

			ग_लिखो_mostly++;
			set_bit(WriteMostly, &rs->dev[value].rdev.flags);
			set_bit(__CTR_FLAG_WRITE_MOSTLY, &rs->ctr_flags);
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_MAX_WRITE_BEHIND))) अणु
			अगर (!rt_is_raid1(rt)) अणु
				rs->ti->error = "max_write_behind option is only valid for RAID1";
				वापस -EINVAL;
			पूर्ण

			अगर (test_and_set_bit(__CTR_FLAG_MAX_WRITE_BEHIND, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one max_write_behind argument pair allowed";
				वापस -EINVAL;
			पूर्ण

			/*
			 * In device-mapper, we specअगरy things in sectors, but
			 * MD records this value in kB
			 */
			अगर (value < 0 || value / 2 > COUNTER_MAX) अणु
				rs->ti->error = "Max write-behind limit out of range";
				वापस -EINVAL;
			पूर्ण

			rs->md.biपंचांगap_info.max_ग_लिखो_behind = value / 2;
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_DAEMON_SLEEP))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_DAEMON_SLEEP, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one daemon_sleep argument pair allowed";
				वापस -EINVAL;
			पूर्ण
			अगर (value < 0) अणु
				rs->ti->error = "daemon sleep period out of range";
				वापस -EINVAL;
			पूर्ण
			rs->md.biपंचांगap_info.daemon_sleep = value;
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_DATA_OFFSET))) अणु
			/* Userspace passes new data_offset after having extended the the data image LV */
			अगर (test_and_set_bit(__CTR_FLAG_DATA_OFFSET, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one data_offset argument pair allowed";
				वापस -EINVAL;
			पूर्ण
			/* Ensure sensible data offset */
			अगर (value < 0 ||
			    (value && (value < MIN_FREE_RESHAPE_SPACE || value % to_sector(PAGE_SIZE)))) अणु
				rs->ti->error = "Bogus data_offset value";
				वापस -EINVAL;
			पूर्ण
			rs->data_offset = value;
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_DELTA_DISKS))) अणु
			/* Define the +/-# of disks to add to/हटाओ from the given raid set */
			अगर (test_and_set_bit(__CTR_FLAG_DELTA_DISKS, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one delta_disks argument pair allowed";
				वापस -EINVAL;
			पूर्ण
			/* Ensure MAX_RAID_DEVICES and raid type minimal_devs! */
			अगर (!__within_range(असल(value), 1, MAX_RAID_DEVICES - rt->minimal_devs)) अणु
				rs->ti->error = "Too many delta_disk requested";
				वापस -EINVAL;
			पूर्ण

			rs->delta_disks = value;
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_STRIPE_CACHE))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_STRIPE_CACHE, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one stripe_cache argument pair allowed";
				वापस -EINVAL;
			पूर्ण

			अगर (!rt_is_raid456(rt)) अणु
				rs->ti->error = "Inappropriate argument: stripe_cache";
				वापस -EINVAL;
			पूर्ण

			अगर (value < 0) अणु
				rs->ti->error = "Bogus stripe cache entries value";
				वापस -EINVAL;
			पूर्ण
			rs->stripe_cache_entries = value;
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_MIN_RECOVERY_RATE))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_MIN_RECOVERY_RATE, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one min_recovery_rate argument pair allowed";
				वापस -EINVAL;
			पूर्ण

			अगर (value < 0) अणु
				rs->ti->error = "min_recovery_rate out of range";
				वापस -EINVAL;
			पूर्ण
			rs->md.sync_speed_min = value;
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_MAX_RECOVERY_RATE))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_MAX_RECOVERY_RATE, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one max_recovery_rate argument pair allowed";
				वापस -EINVAL;
			पूर्ण

			अगर (value < 0) अणु
				rs->ti->error = "max_recovery_rate out of range";
				वापस -EINVAL;
			पूर्ण
			rs->md.sync_speed_max = value;
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_REGION_SIZE))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_REGION_SIZE, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one region_size argument pair allowed";
				वापस -EINVAL;
			पूर्ण

			region_size = value;
			rs->requested_biपंचांगap_chunk_sectors = value;
		पूर्ण अन्यथा अगर (!strहालcmp(key, dm_raid_arg_name_by_flag(CTR_FLAG_RAID10_COPIES))) अणु
			अगर (test_and_set_bit(__CTR_FLAG_RAID10_COPIES, &rs->ctr_flags)) अणु
				rs->ti->error = "Only one raid10_copies argument pair allowed";
				वापस -EINVAL;
			पूर्ण

			अगर (!__within_range(value, 2, rs->md.raid_disks)) अणु
				rs->ti->error = "Bad value for 'raid10_copies'";
				वापस -EINVAL;
			पूर्ण

			raid10_copies = value;
		पूर्ण अन्यथा अणु
			DMERR("Unable to parse RAID parameter: %s", key);
			rs->ti->error = "Unable to parse RAID parameter";
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (test_bit(__CTR_FLAG_SYNC, &rs->ctr_flags) &&
	    test_bit(__CTR_FLAG_NOSYNC, &rs->ctr_flags)) अणु
		rs->ti->error = "sync and nosync are mutually exclusive";
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(__CTR_FLAG_REBUILD, &rs->ctr_flags) &&
	    (test_bit(__CTR_FLAG_SYNC, &rs->ctr_flags) ||
	     test_bit(__CTR_FLAG_NOSYNC, &rs->ctr_flags))) अणु
		rs->ti->error = "sync/nosync and rebuild are mutually exclusive";
		वापस -EINVAL;
	पूर्ण

	अगर (ग_लिखो_mostly >= rs->md.raid_disks) अणु
		rs->ti->error = "Can't set all raid1 devices to write_mostly";
		वापस -EINVAL;
	पूर्ण

	अगर (rs->md.sync_speed_max &&
	    rs->md.sync_speed_min > rs->md.sync_speed_max) अणु
		rs->ti->error = "Bogus recovery rates";
		वापस -EINVAL;
	पूर्ण

	अगर (validate_region_size(rs, region_size))
		वापस -EINVAL;

	अगर (rs->md.chunk_sectors)
		max_io_len = rs->md.chunk_sectors;
	अन्यथा
		max_io_len = region_size;

	अगर (dm_set_target_max_io_len(rs->ti, max_io_len))
		वापस -EINVAL;

	अगर (rt_is_raid10(rt)) अणु
		अगर (raid10_copies > rs->md.raid_disks) अणु
			rs->ti->error = "Not enough devices to satisfy specification";
			वापस -EINVAL;
		पूर्ण

		rs->md.new_layout = raid10_क्रमmat_to_md_layout(rs, raid10_क्रमmat, raid10_copies);
		अगर (rs->md.new_layout < 0) अणु
			rs->ti->error = "Error getting raid10 format";
			वापस rs->md.new_layout;
		पूर्ण

		rt = get_raid_type_by_ll(10, rs->md.new_layout);
		अगर (!rt) अणु
			rs->ti->error = "Failed to recognize new raid10 layout";
			वापस -EINVAL;
		पूर्ण

		अगर ((rt->algorithm == ALGORITHM_RAID10_DEFAULT ||
		     rt->algorithm == ALGORITHM_RAID10_NEAR) &&
		    test_bit(__CTR_FLAG_RAID10_USE_NEAR_SETS, &rs->ctr_flags)) अणु
			rs->ti->error = "RAID10 format 'near' and 'raid10_use_near_sets' are incompatible";
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	rs->raid10_copies = raid10_copies;

	/* Assume there are no metadata devices until the drives are parsed */
	rs->md.persistent = 0;
	rs->md.बाह्यal = 1;

	/* Check, अगर any invalid ctr arguments have been passed in क्रम the raid level */
	वापस rs_check_क्रम_valid_flags(rs);
पूर्ण

/* Set raid4/5/6 cache size */
अटल पूर्णांक rs_set_raid456_stripe_cache(काष्ठा raid_set *rs)
अणु
	पूर्णांक r;
	काष्ठा r5conf *conf;
	काष्ठा mddev *mddev = &rs->md;
	uपूर्णांक32_t min_stripes = max(mddev->chunk_sectors, mddev->new_chunk_sectors) / 2;
	uपूर्णांक32_t nr_stripes = rs->stripe_cache_entries;

	अगर (!rt_is_raid456(rs->raid_type)) अणु
		rs->ti->error = "Inappropriate raid level; cannot change stripe_cache size";
		वापस -EINVAL;
	पूर्ण

	अगर (nr_stripes < min_stripes) अणु
		DMINFO("Adjusting requested %u stripe cache entries to %u to suit stripe size",
		       nr_stripes, min_stripes);
		nr_stripes = min_stripes;
	पूर्ण

	conf = mddev->निजी;
	अगर (!conf) अणु
		rs->ti->error = "Cannot change stripe_cache size on inactive RAID set";
		वापस -EINVAL;
	पूर्ण

	/* Try setting number of stripes in raid456 stripe cache */
	अगर (conf->min_nr_stripes != nr_stripes) अणु
		r = raid5_set_cache_size(mddev, nr_stripes);
		अगर (r) अणु
			rs->ti->error = "Failed to set raid4/5/6 stripe cache size";
			वापस r;
		पूर्ण

		DMINFO("%u stripe cache entries", nr_stripes);
	पूर्ण

	वापस 0;
पूर्ण

/* Return # of data stripes as kept in mddev as of @rs (i.e. as of superblock) */
अटल अचिन्हित पूर्णांक mddev_data_stripes(काष्ठा raid_set *rs)
अणु
	वापस rs->md.raid_disks - rs->raid_type->parity_devs;
पूर्ण

/* Return # of data stripes of @rs (i.e. as of ctr) */
अटल अचिन्हित पूर्णांक rs_data_stripes(काष्ठा raid_set *rs)
अणु
	वापस rs->raid_disks - rs->raid_type->parity_devs;
पूर्ण

/*
 * Retrieve rdev->sectors from any valid raid device of @rs
 * to allow userpace to pass in arbitray "- -" device tupples.
 */
अटल sector_t __rdev_sectors(काष्ठा raid_set *rs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rs->md.raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = &rs->dev[i].rdev;

		अगर (!test_bit(Journal, &rdev->flags) &&
		    rdev->bdev && rdev->sectors)
			वापस rdev->sectors;
	पूर्ण

	वापस 0;
पूर्ण

/* Check that calculated dev_sectors fits all component devices. */
अटल पूर्णांक _check_data_dev_sectors(काष्ठा raid_set *rs)
अणु
	sector_t ds = ~0;
	काष्ठा md_rdev *rdev;

	rdev_क्रम_each(rdev, &rs->md)
		अगर (!test_bit(Journal, &rdev->flags) && rdev->bdev) अणु
			ds = min(ds, to_sector(i_size_पढ़ो(rdev->bdev->bd_inode)));
			अगर (ds < rs->md.dev_sectors) अणु
				rs->ti->error = "Component device(s) too small";
				वापस -EINVAL;
			पूर्ण
		पूर्ण

	वापस 0;
पूर्ण

/* Calculate the sectors per device and per array used क्रम @rs */
अटल पूर्णांक rs_set_dev_and_array_sectors(काष्ठा raid_set *rs, sector_t sectors, bool use_mddev)
अणु
	पूर्णांक delta_disks;
	अचिन्हित पूर्णांक data_stripes;
	sector_t array_sectors = sectors, dev_sectors = sectors;
	काष्ठा mddev *mddev = &rs->md;

	अगर (use_mddev) अणु
		delta_disks = mddev->delta_disks;
		data_stripes = mddev_data_stripes(rs);
	पूर्ण अन्यथा अणु
		delta_disks = rs->delta_disks;
		data_stripes = rs_data_stripes(rs);
	पूर्ण

	/* Special raid1 हाल w/o delta_disks support (yet) */
	अगर (rt_is_raid1(rs->raid_type))
		;
	अन्यथा अगर (rt_is_raid10(rs->raid_type)) अणु
		अगर (rs->raid10_copies < 2 ||
		    delta_disks < 0) अणु
			rs->ti->error = "Bogus raid10 data copies or delta disks";
			वापस -EINVAL;
		पूर्ण

		dev_sectors *= rs->raid10_copies;
		अगर (sector_भाग(dev_sectors, data_stripes))
			जाओ bad;

		array_sectors = (data_stripes + delta_disks) * dev_sectors;
		अगर (sector_भाग(array_sectors, rs->raid10_copies))
			जाओ bad;

	पूर्ण अन्यथा अगर (sector_भाग(dev_sectors, data_stripes))
		जाओ bad;

	अन्यथा
		/* Striped layouts */
		array_sectors = (data_stripes + delta_disks) * dev_sectors;

	mddev->array_sectors = array_sectors;
	mddev->dev_sectors = dev_sectors;
	rs_set_rdev_sectors(rs);

	वापस _check_data_dev_sectors(rs);
bad:
	rs->ti->error = "Target length not divisible by number of data devices";
	वापस -EINVAL;
पूर्ण

/* Setup recovery on @rs */
अटल व्योम rs_setup_recovery(काष्ठा raid_set *rs, sector_t dev_sectors)
अणु
	/* raid0 करोes not recover */
	अगर (rs_is_raid0(rs))
		rs->md.recovery_cp = MaxSector;
	/*
	 * A raid6 set has to be recovered either
	 * completely or क्रम the grown part to
	 * ensure proper parity and Q-Syndrome
	 */
	अन्यथा अगर (rs_is_raid6(rs))
		rs->md.recovery_cp = dev_sectors;
	/*
	 * Other raid set types may skip recovery
	 * depending on the 'nosync' flag.
	 */
	अन्यथा
		rs->md.recovery_cp = test_bit(__CTR_FLAG_NOSYNC, &rs->ctr_flags)
				     ? MaxSector : dev_sectors;
पूर्ण

अटल व्योम करो_table_event(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा raid_set *rs = container_of(ws, काष्ठा raid_set, md.event_work);

	smp_rmb(); /* Make sure we access most actual mddev properties */
	अगर (!rs_is_reshaping(rs)) अणु
		अगर (rs_is_raid10(rs))
			rs_set_rdev_sectors(rs);
		rs_set_capacity(rs);
	पूर्ण
	dm_table_event(rs->ti->table);
पूर्ण

/*
 * Make sure a valid takover (level चयन) is being requested on @rs
 *
 * Conversions of raid sets from one MD personality to another
 * have to conक्रमm to restrictions which are enक्रमced here.
 */
अटल पूर्णांक rs_check_takeover(काष्ठा raid_set *rs)
अणु
	काष्ठा mddev *mddev = &rs->md;
	अचिन्हित पूर्णांक near_copies;

	अगर (rs->md.degraded) अणु
		rs->ti->error = "Can't takeover degraded raid set";
		वापस -EPERM;
	पूर्ण

	अगर (rs_is_reshaping(rs)) अणु
		rs->ti->error = "Can't takeover reshaping raid set";
		वापस -EPERM;
	पूर्ण

	चयन (mddev->level) अणु
	हाल 0:
		/* raid0 -> raid1/5 with one disk */
		अगर ((mddev->new_level == 1 || mddev->new_level == 5) &&
		    mddev->raid_disks == 1)
			वापस 0;

		/* raid0 -> raid10 */
		अगर (mddev->new_level == 10 &&
		    !(rs->raid_disks % mddev->raid_disks))
			वापस 0;

		/* raid0 with multiple disks -> raid4/5/6 */
		अगर (__within_range(mddev->new_level, 4, 6) &&
		    mddev->new_layout == ALGORITHM_PARITY_N &&
		    mddev->raid_disks > 1)
			वापस 0;

		अवरोध;

	हाल 10:
		/* Can't takeover raid10_offset! */
		अगर (__is_raid10_offset(mddev->layout))
			अवरोध;

		near_copies = __raid10_near_copies(mddev->layout);

		/* raid10* -> raid0 */
		अगर (mddev->new_level == 0) अणु
			/* Can takeover raid10_near with raid disks भागisable by data copies! */
			अगर (near_copies > 1 &&
			    !(mddev->raid_disks % near_copies)) अणु
				mddev->raid_disks /= near_copies;
				mddev->delta_disks = mddev->raid_disks;
				वापस 0;
			पूर्ण

			/* Can takeover raid10_far */
			अगर (near_copies == 1 &&
			    __raid10_far_copies(mddev->layout) > 1)
				वापस 0;

			अवरोध;
		पूर्ण

		/* raid10_अणुnear,farपूर्ण -> raid1 */
		अगर (mddev->new_level == 1 &&
		    max(near_copies, __raid10_far_copies(mddev->layout)) == mddev->raid_disks)
			वापस 0;

		/* raid10_अणुnear,farपूर्ण with 2 disks -> raid4/5 */
		अगर (__within_range(mddev->new_level, 4, 5) &&
		    mddev->raid_disks == 2)
			वापस 0;
		अवरोध;

	हाल 1:
		/* raid1 with 2 disks -> raid4/5 */
		अगर (__within_range(mddev->new_level, 4, 5) &&
		    mddev->raid_disks == 2) अणु
			mddev->degraded = 1;
			वापस 0;
		पूर्ण

		/* raid1 -> raid0 */
		अगर (mddev->new_level == 0 &&
		    mddev->raid_disks == 1)
			वापस 0;

		/* raid1 -> raid10 */
		अगर (mddev->new_level == 10)
			वापस 0;
		अवरोध;

	हाल 4:
		/* raid4 -> raid0 */
		अगर (mddev->new_level == 0)
			वापस 0;

		/* raid4 -> raid1/5 with 2 disks */
		अगर ((mddev->new_level == 1 || mddev->new_level == 5) &&
		    mddev->raid_disks == 2)
			वापस 0;

		/* raid4 -> raid5/6 with parity N */
		अगर (__within_range(mddev->new_level, 5, 6) &&
		    mddev->layout == ALGORITHM_PARITY_N)
			वापस 0;
		अवरोध;

	हाल 5:
		/* raid5 with parity N -> raid0 */
		अगर (mddev->new_level == 0 &&
		    mddev->layout == ALGORITHM_PARITY_N)
			वापस 0;

		/* raid5 with parity N -> raid4 */
		अगर (mddev->new_level == 4 &&
		    mddev->layout == ALGORITHM_PARITY_N)
			वापस 0;

		/* raid5 with 2 disks -> raid1/4/10 */
		अगर ((mddev->new_level == 1 || mddev->new_level == 4 || mddev->new_level == 10) &&
		    mddev->raid_disks == 2)
			वापस 0;

		/* raid5_* ->  raid6_*_6 with Q-Syndrome N (e.g. raid5_ra -> raid6_ra_6 */
		अगर (mddev->new_level == 6 &&
		    ((mddev->layout == ALGORITHM_PARITY_N && mddev->new_layout == ALGORITHM_PARITY_N) ||
		      __within_range(mddev->new_layout, ALGORITHM_LEFT_ASYMMETRIC_6, ALGORITHM_RIGHT_SYMMETRIC_6)))
			वापस 0;
		अवरोध;

	हाल 6:
		/* raid6 with parity N -> raid0 */
		अगर (mddev->new_level == 0 &&
		    mddev->layout == ALGORITHM_PARITY_N)
			वापस 0;

		/* raid6 with parity N -> raid4 */
		अगर (mddev->new_level == 4 &&
		    mddev->layout == ALGORITHM_PARITY_N)
			वापस 0;

		/* raid6_*_n with Q-Syndrome N -> raid5_* */
		अगर (mddev->new_level == 5 &&
		    ((mddev->layout == ALGORITHM_PARITY_N && mddev->new_layout == ALGORITHM_PARITY_N) ||
		     __within_range(mddev->new_layout, ALGORITHM_LEFT_ASYMMETRIC, ALGORITHM_RIGHT_SYMMETRIC)))
			वापस 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	rs->ti->error = "takeover not possible";
	वापस -EINVAL;
पूर्ण

/* True अगर @rs requested to be taken over */
अटल bool rs_takeover_requested(काष्ठा raid_set *rs)
अणु
	वापस rs->md.new_level != rs->md.level;
पूर्ण

/* True अगर layout is set to reshape. */
अटल bool rs_is_layout_change(काष्ठा raid_set *rs, bool use_mddev)
अणु
	वापस (use_mddev ? rs->md.delta_disks : rs->delta_disks) ||
	       rs->md.new_layout != rs->md.layout ||
	       rs->md.new_chunk_sectors != rs->md.chunk_sectors;
पूर्ण

/* True अगर @rs is requested to reshape by ctr */
अटल bool rs_reshape_requested(काष्ठा raid_set *rs)
अणु
	bool change;
	काष्ठा mddev *mddev = &rs->md;

	अगर (rs_takeover_requested(rs))
		वापस false;

	अगर (rs_is_raid0(rs))
		वापस false;

	change = rs_is_layout_change(rs, false);

	/* Historical हाल to support raid1 reshape without delta disks */
	अगर (rs_is_raid1(rs)) अणु
		अगर (rs->delta_disks)
			वापस !!rs->delta_disks;

		वापस !change &&
		       mddev->raid_disks != rs->raid_disks;
	पूर्ण

	अगर (rs_is_raid10(rs))
		वापस change &&
		       !__is_raid10_far(mddev->new_layout) &&
		       rs->delta_disks >= 0;

	वापस change;
पूर्ण

/*  Features */
#घोषणा	FEATURE_FLAG_SUPPORTS_V190	0x1 /* Supports extended superblock */

/* State flags क्रम sb->flags */
#घोषणा	SB_FLAG_RESHAPE_ACTIVE		0x1
#घोषणा	SB_FLAG_RESHAPE_BACKWARDS	0x2

/*
 * This काष्ठाure is never routinely used by userspace, unlike md superblocks.
 * Devices with this superblock should only ever be accessed via device-mapper.
 */
#घोषणा DM_RAID_MAGIC 0x64526D44
काष्ठा dm_raid_superblock अणु
	__le32 magic;		/* "DmRd" */
	__le32 compat_features;	/* Used to indicate compatible features (like 1.9.0 ondisk metadata extension) */

	__le32 num_devices;	/* Number of devices in this raid set. (Max 64) */
	__le32 array_position;	/* The position of this drive in the raid set */

	__le64 events;		/* Incremented by md when superblock updated */
	__le64 failed_devices;	/* Pre 1.9.0 part of bit field of devices to */
				/* indicate failures (see extension below) */

	/*
	 * This offset tracks the progress of the repair or replacement of
	 * an inभागidual drive.
	 */
	__le64 disk_recovery_offset;

	/*
	 * This offset tracks the progress of the initial raid set
	 * synchronisation/parity calculation.
	 */
	__le64 array_resync_offset;

	/*
	 * raid अक्षरacteristics
	 */
	__le32 level;
	__le32 layout;
	__le32 stripe_sectors;

	/********************************************************************
	 * BELOW FOLLOW V1.9.0 EXTENSIONS TO THE PRISTINE SUPERBLOCK FORMAT!!!
	 *
	 * FEATURE_FLAG_SUPPORTS_V190 in the compat_features member indicates that those exist
	 */

	__le32 flags; /* Flags defining array states क्रम reshaping */

	/*
	 * This offset tracks the progress of a raid
	 * set reshape in order to be able to restart it
	 */
	__le64 reshape_position;

	/*
	 * These define the properties of the array in हाल of an पूर्णांकerrupted reshape
	 */
	__le32 new_level;
	__le32 new_layout;
	__le32 new_stripe_sectors;
	__le32 delta_disks;

	__le64 array_sectors; /* Array size in sectors */

	/*
	 * Sector offsets to data on devices (reshaping).
	 * Needed to support out of place reshaping, thus
	 * not writing over any stripes whilst converting
	 * them from old to new layout
	 */
	__le64 data_offset;
	__le64 new_data_offset;

	__le64 sectors; /* Used device size in sectors */

	/*
	 * Additonal Bit field of devices indicating failures to support
	 * up to 256 devices with the 1.9.0 on-disk metadata क्रमmat
	 */
	__le64 extended_failed_devices[DISKS_ARRAY_ELEMS - 1];

	__le32 incompat_features;	/* Used to indicate any incompatible features */

	/* Always set rest up to logical block size to 0 when writing (see get_metadata_device() below). */
पूर्ण __packed;

/*
 * Check क्रम reshape स्थिरraपूर्णांकs on raid set @rs:
 *
 * - reshape function non-existent
 * - degraded set
 * - ongoing recovery
 * - ongoing reshape
 *
 * Returns 0 अगर none or -EPERM अगर given स्थिरraपूर्णांक
 * and error message reference in @errmsg
 */
अटल पूर्णांक rs_check_reshape(काष्ठा raid_set *rs)
अणु
	काष्ठा mddev *mddev = &rs->md;

	अगर (!mddev->pers || !mddev->pers->check_reshape)
		rs->ti->error = "Reshape not supported";
	अन्यथा अगर (mddev->degraded)
		rs->ti->error = "Can't reshape degraded raid set";
	अन्यथा अगर (rs_is_recovering(rs))
		rs->ti->error = "Convert request on recovering raid set prohibited";
	अन्यथा अगर (rs_is_reshaping(rs))
		rs->ti->error = "raid set already reshaping!";
	अन्यथा अगर (!(rs_is_raid1(rs) || rs_is_raid10(rs) || rs_is_raid456(rs)))
		rs->ti->error = "Reshaping only supported for raid1/4/5/6/10";
	अन्यथा
		वापस 0;

	वापस -EPERM;
पूर्ण

अटल पूर्णांक पढ़ो_disk_sb(काष्ठा md_rdev *rdev, पूर्णांक size, bool क्रमce_reload)
अणु
	BUG_ON(!rdev->sb_page);

	अगर (rdev->sb_loaded && !क्रमce_reload)
		वापस 0;

	rdev->sb_loaded = 0;

	अगर (!sync_page_io(rdev, 0, size, rdev->sb_page, REQ_OP_READ, 0, true)) अणु
		DMERR("Failed to read superblock of device at position %d",
		      rdev->raid_disk);
		md_error(rdev->mddev, rdev);
		set_bit(Faulty, &rdev->flags);
		वापस -EIO;
	पूर्ण

	rdev->sb_loaded = 1;

	वापस 0;
पूर्ण

अटल व्योम sb_retrieve_failed_devices(काष्ठा dm_raid_superblock *sb, uपूर्णांक64_t *failed_devices)
अणु
	failed_devices[0] = le64_to_cpu(sb->failed_devices);
	स_रखो(failed_devices + 1, 0, माप(sb->extended_failed_devices));

	अगर (le32_to_cpu(sb->compat_features) & FEATURE_FLAG_SUPPORTS_V190) अणु
		पूर्णांक i = ARRAY_SIZE(sb->extended_failed_devices);

		जबतक (i--)
			failed_devices[i+1] = le64_to_cpu(sb->extended_failed_devices[i]);
	पूर्ण
पूर्ण

अटल व्योम sb_update_failed_devices(काष्ठा dm_raid_superblock *sb, uपूर्णांक64_t *failed_devices)
अणु
	पूर्णांक i = ARRAY_SIZE(sb->extended_failed_devices);

	sb->failed_devices = cpu_to_le64(failed_devices[0]);
	जबतक (i--)
		sb->extended_failed_devices[i] = cpu_to_le64(failed_devices[i+1]);
पूर्ण

/*
 * Synchronize the superblock members with the raid set properties
 *
 * All superblock data is little endian.
 */
अटल व्योम super_sync(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	bool update_failed_devices = false;
	अचिन्हित पूर्णांक i;
	uपूर्णांक64_t failed_devices[DISKS_ARRAY_ELEMS];
	काष्ठा dm_raid_superblock *sb;
	काष्ठा raid_set *rs = container_of(mddev, काष्ठा raid_set, md);

	/* No metadata device, no superblock */
	अगर (!rdev->meta_bdev)
		वापस;

	BUG_ON(!rdev->sb_page);

	sb = page_address(rdev->sb_page);

	sb_retrieve_failed_devices(sb, failed_devices);

	क्रम (i = 0; i < rs->raid_disks; i++)
		अगर (!rs->dev[i].data_dev || test_bit(Faulty, &rs->dev[i].rdev.flags)) अणु
			update_failed_devices = true;
			set_bit(i, (व्योम *) failed_devices);
		पूर्ण

	अगर (update_failed_devices)
		sb_update_failed_devices(sb, failed_devices);

	sb->magic = cpu_to_le32(DM_RAID_MAGIC);
	sb->compat_features = cpu_to_le32(FEATURE_FLAG_SUPPORTS_V190);

	sb->num_devices = cpu_to_le32(mddev->raid_disks);
	sb->array_position = cpu_to_le32(rdev->raid_disk);

	sb->events = cpu_to_le64(mddev->events);

	sb->disk_recovery_offset = cpu_to_le64(rdev->recovery_offset);
	sb->array_resync_offset = cpu_to_le64(mddev->recovery_cp);

	sb->level = cpu_to_le32(mddev->level);
	sb->layout = cpu_to_le32(mddev->layout);
	sb->stripe_sectors = cpu_to_le32(mddev->chunk_sectors);

	/********************************************************************
	 * BELOW FOLLOW V1.9.0 EXTENSIONS TO THE PRISTINE SUPERBLOCK FORMAT!!!
	 *
	 * FEATURE_FLAG_SUPPORTS_V190 in the compat_features member indicates that those exist
	 */
	sb->new_level = cpu_to_le32(mddev->new_level);
	sb->new_layout = cpu_to_le32(mddev->new_layout);
	sb->new_stripe_sectors = cpu_to_le32(mddev->new_chunk_sectors);

	sb->delta_disks = cpu_to_le32(mddev->delta_disks);

	smp_rmb(); /* Make sure we access most recent reshape position */
	sb->reshape_position = cpu_to_le64(mddev->reshape_position);
	अगर (le64_to_cpu(sb->reshape_position) != MaxSector) अणु
		/* Flag ongoing reshape */
		sb->flags |= cpu_to_le32(SB_FLAG_RESHAPE_ACTIVE);

		अगर (mddev->delta_disks < 0 || mddev->reshape_backwards)
			sb->flags |= cpu_to_le32(SB_FLAG_RESHAPE_BACKWARDS);
	पूर्ण अन्यथा अणु
		/* Clear reshape flags */
		sb->flags &= ~(cpu_to_le32(SB_FLAG_RESHAPE_ACTIVE|SB_FLAG_RESHAPE_BACKWARDS));
	पूर्ण

	sb->array_sectors = cpu_to_le64(mddev->array_sectors);
	sb->data_offset = cpu_to_le64(rdev->data_offset);
	sb->new_data_offset = cpu_to_le64(rdev->new_data_offset);
	sb->sectors = cpu_to_le64(rdev->sectors);
	sb->incompat_features = cpu_to_le32(0);

	/* Zero out the rest of the payload after the size of the superblock */
	स_रखो(sb + 1, 0, rdev->sb_size - माप(*sb));
पूर्ण

/*
 * super_load
 *
 * This function creates a superblock अगर one is not found on the device
 * and will decide which superblock to use अगर there's a choice.
 *
 * Return: 1 अगर use rdev, 0 अगर use refdev, -Exxx otherwise
 */
अटल पूर्णांक super_load(काष्ठा md_rdev *rdev, काष्ठा md_rdev *refdev)
अणु
	पूर्णांक r;
	काष्ठा dm_raid_superblock *sb;
	काष्ठा dm_raid_superblock *refsb;
	uपूर्णांक64_t events_sb, events_refsb;

	r = पढ़ो_disk_sb(rdev, rdev->sb_size, false);
	अगर (r)
		वापस r;

	sb = page_address(rdev->sb_page);

	/*
	 * Two हालs that we want to ग_लिखो new superblocks and rebuild:
	 * 1) New device (no matching magic number)
	 * 2) Device specअगरied क्रम rebuild (!In_sync w/ offset == 0)
	 */
	अगर ((sb->magic != cpu_to_le32(DM_RAID_MAGIC)) ||
	    (!test_bit(In_sync, &rdev->flags) && !rdev->recovery_offset)) अणु
		super_sync(rdev->mddev, rdev);

		set_bit(FirstUse, &rdev->flags);
		sb->compat_features = cpu_to_le32(FEATURE_FLAG_SUPPORTS_V190);

		/* Force writing of superblocks to disk */
		set_bit(MD_SB_CHANGE_DEVS, &rdev->mddev->sb_flags);

		/* Any superblock is better than none, choose that अगर given */
		वापस refdev ? 0 : 1;
	पूर्ण

	अगर (!refdev)
		वापस 1;

	events_sb = le64_to_cpu(sb->events);

	refsb = page_address(refdev->sb_page);
	events_refsb = le64_to_cpu(refsb->events);

	वापस (events_sb > events_refsb) ? 1 : 0;
पूर्ण

अटल पूर्णांक super_init_validation(काष्ठा raid_set *rs, काष्ठा md_rdev *rdev)
अणु
	पूर्णांक role;
	अचिन्हित पूर्णांक d;
	काष्ठा mddev *mddev = &rs->md;
	uपूर्णांक64_t events_sb;
	uपूर्णांक64_t failed_devices[DISKS_ARRAY_ELEMS];
	काष्ठा dm_raid_superblock *sb;
	uपूर्णांक32_t new_devs = 0, rebuild_and_new = 0, rebuilds = 0;
	काष्ठा md_rdev *r;
	काष्ठा dm_raid_superblock *sb2;

	sb = page_address(rdev->sb_page);
	events_sb = le64_to_cpu(sb->events);

	/*
	 * Initialise to 1 अगर this is a new superblock.
	 */
	mddev->events = events_sb ? : 1;

	mddev->reshape_position = MaxSector;

	mddev->raid_disks = le32_to_cpu(sb->num_devices);
	mddev->level = le32_to_cpu(sb->level);
	mddev->layout = le32_to_cpu(sb->layout);
	mddev->chunk_sectors = le32_to_cpu(sb->stripe_sectors);

	/*
	 * Reshaping is supported, e.g. reshape_position is valid
	 * in superblock and superblock content is authoritative.
	 */
	अगर (le32_to_cpu(sb->compat_features) & FEATURE_FLAG_SUPPORTS_V190) अणु
		/* Superblock is authoritative wrt given raid set layout! */
		mddev->new_level = le32_to_cpu(sb->new_level);
		mddev->new_layout = le32_to_cpu(sb->new_layout);
		mddev->new_chunk_sectors = le32_to_cpu(sb->new_stripe_sectors);
		mddev->delta_disks = le32_to_cpu(sb->delta_disks);
		mddev->array_sectors = le64_to_cpu(sb->array_sectors);

		/* raid was reshaping and got पूर्णांकerrupted */
		अगर (le32_to_cpu(sb->flags) & SB_FLAG_RESHAPE_ACTIVE) अणु
			अगर (test_bit(__CTR_FLAG_DELTA_DISKS, &rs->ctr_flags)) अणु
				DMERR("Reshape requested but raid set is still reshaping");
				वापस -EINVAL;
			पूर्ण

			अगर (mddev->delta_disks < 0 ||
			    (!mddev->delta_disks && (le32_to_cpu(sb->flags) & SB_FLAG_RESHAPE_BACKWARDS)))
				mddev->reshape_backwards = 1;
			अन्यथा
				mddev->reshape_backwards = 0;

			mddev->reshape_position = le64_to_cpu(sb->reshape_position);
			rs->raid_type = get_raid_type_by_ll(mddev->level, mddev->layout);
		पूर्ण

	पूर्ण अन्यथा अणु
		/*
		 * No takeover/reshaping, because we करोn't have the extended v1.9.0 metadata
		 */
		काष्ठा raid_type *rt_cur = get_raid_type_by_ll(mddev->level, mddev->layout);
		काष्ठा raid_type *rt_new = get_raid_type_by_ll(mddev->new_level, mddev->new_layout);

		अगर (rs_takeover_requested(rs)) अणु
			अगर (rt_cur && rt_new)
				DMERR("Takeover raid sets from %s to %s not yet supported by metadata. (raid level change)",
				      rt_cur->name, rt_new->name);
			अन्यथा
				DMERR("Takeover raid sets not yet supported by metadata. (raid level change)");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (rs_reshape_requested(rs)) अणु
			DMERR("Reshaping raid sets not yet supported by metadata. (raid layout change keeping level)");
			अगर (mddev->layout != mddev->new_layout) अणु
				अगर (rt_cur && rt_new)
					DMERR("	 current layout %s vs new layout %s",
					      rt_cur->name, rt_new->name);
				अन्यथा
					DMERR("	 current layout 0x%X vs new layout 0x%X",
					      le32_to_cpu(sb->layout), mddev->new_layout);
			पूर्ण
			अगर (mddev->chunk_sectors != mddev->new_chunk_sectors)
				DMERR("	 current stripe sectors %u vs new stripe sectors %u",
				      mddev->chunk_sectors, mddev->new_chunk_sectors);
			अगर (rs->delta_disks)
				DMERR("	 current %u disks vs new %u disks",
				      mddev->raid_disks, mddev->raid_disks + rs->delta_disks);
			अगर (rs_is_raid10(rs)) अणु
				DMERR("	 Old layout: %s w/ %u copies",
				      raid10_md_layout_to_क्रमmat(mddev->layout),
				      raid10_md_layout_to_copies(mddev->layout));
				DMERR("	 New layout: %s w/ %u copies",
				      raid10_md_layout_to_क्रमmat(mddev->new_layout),
				      raid10_md_layout_to_copies(mddev->new_layout));
			पूर्ण
			वापस -EINVAL;
		पूर्ण

		DMINFO("Discovered old metadata format; upgrading to extended metadata format");
	पूर्ण

	अगर (!test_bit(__CTR_FLAG_NOSYNC, &rs->ctr_flags))
		mddev->recovery_cp = le64_to_cpu(sb->array_resync_offset);

	/*
	 * During load, we set FirstUse अगर a new superblock was written.
	 * There are two reasons we might not have a superblock:
	 * 1) The raid set is bअक्रम new - in which हाल, all of the
	 *    devices must have their In_sync bit set.	Also,
	 *    recovery_cp must be 0, unless क्रमced.
	 * 2) This is a new device being added to an old raid set
	 *    and the new device needs to be rebuilt - in which
	 *    हाल the In_sync bit will /not/ be set and
	 *    recovery_cp must be MaxSector.
	 * 3) This is/are a new device(s) being added to an old
	 *    raid set during takeover to a higher raid level
	 *    to provide capacity क्रम redundancy or during reshape
	 *    to add capacity to grow the raid set.
	 */
	d = 0;
	rdev_क्रम_each(r, mddev) अणु
		अगर (test_bit(Journal, &rdev->flags))
			जारी;

		अगर (test_bit(FirstUse, &r->flags))
			new_devs++;

		अगर (!test_bit(In_sync, &r->flags)) अणु
			DMINFO("Device %d specified for rebuild; clearing superblock",
				r->raid_disk);
			rebuilds++;

			अगर (test_bit(FirstUse, &r->flags))
				rebuild_and_new++;
		पूर्ण

		d++;
	पूर्ण

	अगर (new_devs == rs->raid_disks || !rebuilds) अणु
		/* Replace a broken device */
		अगर (new_devs == rs->raid_disks) अणु
			DMINFO("Superblocks created for new raid set");
			set_bit(MD_ARRAY_FIRST_USE, &mddev->flags);
		पूर्ण अन्यथा अगर (new_devs != rebuilds &&
			   new_devs != rs->delta_disks) अणु
			DMERR("New device injected into existing raid set without "
			      "'delta_disks' or 'rebuild' parameter specified");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (new_devs && new_devs != rebuilds) अणु
		DMERR("%u 'rebuild' devices cannot be injected into"
		      " a raid set with %u other first-time devices",
		      rebuilds, new_devs);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (rebuilds) अणु
		अगर (rebuild_and_new && rebuilds != rebuild_and_new) अणु
			DMERR("new device%s provided without 'rebuild'",
			      new_devs > 1 ? "s" : "");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (!test_bit(__CTR_FLAG_REBUILD, &rs->ctr_flags) && rs_is_recovering(rs)) अणु
			DMERR("'rebuild' specified while raid set is not in-sync (recovery_cp=%llu)",
			      (अचिन्हित दीर्घ दीर्घ) mddev->recovery_cp);
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (rs_is_reshaping(rs)) अणु
			DMERR("'rebuild' specified while raid set is being reshaped (reshape_position=%llu)",
			      (अचिन्हित दीर्घ दीर्घ) mddev->reshape_position);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Now we set the Faulty bit क्रम those devices that are
	 * recorded in the superblock as failed.
	 */
	sb_retrieve_failed_devices(sb, failed_devices);
	rdev_क्रम_each(r, mddev) अणु
		अगर (test_bit(Journal, &rdev->flags) ||
		    !r->sb_page)
			जारी;
		sb2 = page_address(r->sb_page);
		sb2->failed_devices = 0;
		स_रखो(sb2->extended_failed_devices, 0, माप(sb2->extended_failed_devices));

		/*
		 * Check क्रम any device re-ordering.
		 */
		अगर (!test_bit(FirstUse, &r->flags) && (r->raid_disk >= 0)) अणु
			role = le32_to_cpu(sb2->array_position);
			अगर (role < 0)
				जारी;

			अगर (role != r->raid_disk) अणु
				अगर (rs_is_raid10(rs) && __is_raid10_near(mddev->layout)) अणु
					अगर (mddev->raid_disks % __raid10_near_copies(mddev->layout) ||
					    rs->raid_disks % rs->raid10_copies) अणु
						rs->ti->error =
							"Cannot change raid10 near set to odd # of devices!";
						वापस -EINVAL;
					पूर्ण

					sb2->array_position = cpu_to_le32(r->raid_disk);

				पूर्ण अन्यथा अगर (!(rs_is_raid10(rs) && rt_is_raid0(rs->raid_type)) &&
					   !(rs_is_raid0(rs) && rt_is_raid10(rs->raid_type)) &&
					   !rt_is_raid1(rs->raid_type)) अणु
					rs->ti->error = "Cannot change device positions in raid set";
					वापस -EINVAL;
				पूर्ण

				DMINFO("raid device #%d now at position #%d", role, r->raid_disk);
			पूर्ण

			/*
			 * Partial recovery is perक्रमmed on
			 * वापसing failed devices.
			 */
			अगर (test_bit(role, (व्योम *) failed_devices))
				set_bit(Faulty, &r->flags);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक super_validate(काष्ठा raid_set *rs, काष्ठा md_rdev *rdev)
अणु
	काष्ठा mddev *mddev = &rs->md;
	काष्ठा dm_raid_superblock *sb;

	अगर (rs_is_raid0(rs) || !rdev->sb_page || rdev->raid_disk < 0)
		वापस 0;

	sb = page_address(rdev->sb_page);

	/*
	 * If mddev->events is not set, we know we have not yet initialized
	 * the array.
	 */
	अगर (!mddev->events && super_init_validation(rs, rdev))
		वापस -EINVAL;

	अगर (le32_to_cpu(sb->compat_features) &&
	    le32_to_cpu(sb->compat_features) != FEATURE_FLAG_SUPPORTS_V190) अणु
		rs->ti->error = "Unable to assemble array: Unknown flag(s) in compatible feature flags";
		वापस -EINVAL;
	पूर्ण

	अगर (sb->incompat_features) अणु
		rs->ti->error = "Unable to assemble array: No incompatible feature flags supported yet";
		वापस -EINVAL;
	पूर्ण

	/* Enable biपंचांगap creation on @rs unless no metadevs or raid0 or journaled raid4/5/6 set. */
	mddev->biपंचांगap_info.offset = (rt_is_raid0(rs->raid_type) || rs->journal_dev.dev) ? 0 : to_sector(4096);
	mddev->biपंचांगap_info.शेष_offset = mddev->biपंचांगap_info.offset;

	अगर (!test_and_clear_bit(FirstUse, &rdev->flags)) अणु
		/*
		 * Retrieve rdev size stored in superblock to be prepared क्रम shrink.
		 * Check extended superblock members are present otherwise the size
		 * will not be set!
		 */
		अगर (le32_to_cpu(sb->compat_features) & FEATURE_FLAG_SUPPORTS_V190)
			rdev->sectors = le64_to_cpu(sb->sectors);

		rdev->recovery_offset = le64_to_cpu(sb->disk_recovery_offset);
		अगर (rdev->recovery_offset == MaxSector)
			set_bit(In_sync, &rdev->flags);
		/*
		 * If no reshape in progress -> we're recovering single
		 * disk(s) and have to set the device(s) to out-of-sync
		 */
		अन्यथा अगर (!rs_is_reshaping(rs))
			clear_bit(In_sync, &rdev->flags); /* Mandatory क्रम recovery */
	पूर्ण

	/*
	 * If a device comes back, set it as not In_sync and no दीर्घer faulty.
	 */
	अगर (test_and_clear_bit(Faulty, &rdev->flags)) अणु
		rdev->recovery_offset = 0;
		clear_bit(In_sync, &rdev->flags);
		rdev->saved_raid_disk = rdev->raid_disk;
	पूर्ण

	/* Reshape support -> restore repective data offsets */
	rdev->data_offset = le64_to_cpu(sb->data_offset);
	rdev->new_data_offset = le64_to_cpu(sb->new_data_offset);

	वापस 0;
पूर्ण

/*
 * Analyse superblocks and select the freshest.
 */
अटल पूर्णांक analyse_superblocks(काष्ठा dm_target *ti, काष्ठा raid_set *rs)
अणु
	पूर्णांक r;
	काष्ठा md_rdev *rdev, *freshest;
	काष्ठा mddev *mddev = &rs->md;

	freshest = शून्य;
	rdev_क्रम_each(rdev, mddev) अणु
		अगर (test_bit(Journal, &rdev->flags))
			जारी;

		अगर (!rdev->meta_bdev)
			जारी;

		/* Set superblock offset/size क्रम metadata device. */
		rdev->sb_start = 0;
		rdev->sb_size = bdev_logical_block_size(rdev->meta_bdev);
		अगर (rdev->sb_size < माप(काष्ठा dm_raid_superblock) || rdev->sb_size > PAGE_SIZE) अणु
			DMERR("superblock size of a logical block is no longer valid");
			वापस -EINVAL;
		पूर्ण

		/*
		 * Skipping super_load due to CTR_FLAG_SYNC will cause
		 * the array to undergo initialization again as
		 * though it were new.	This is the पूर्णांकended effect
		 * of the "sync" directive.
		 *
		 * With reshaping capability added, we must ensure that
		 * that the "sync" directive is disallowed during the reshape.
		 */
		अगर (test_bit(__CTR_FLAG_SYNC, &rs->ctr_flags))
			जारी;

		r = super_load(rdev, freshest);

		चयन (r) अणु
		हाल 1:
			freshest = rdev;
			अवरोध;
		हाल 0:
			अवरोध;
		शेष:
			/* This is a failure to पढ़ो the superblock from the metadata device. */
			/*
			 * We have to keep any raid0 data/metadata device pairs or
			 * the MD raid0 personality will fail to start the array.
			 */
			अगर (rs_is_raid0(rs))
				जारी;

			/*
			 * We keep the dm_devs to be able to emit the device tuple
			 * properly on the table line in raid_status() (rather than
			 * mistakenly acting as अगर '- -' got passed पूर्णांकo the स्थिरructor).
			 *
			 * The rdev has to stay on the same_set list to allow क्रम
			 * the attempt to restore faulty devices on second resume.
			 */
			rdev->raid_disk = rdev->saved_raid_disk = -1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!freshest)
		वापस 0;

	/*
	 * Validation of the freshest device provides the source of
	 * validation क्रम the reमुख्यing devices.
	 */
	rs->ti->error = "Unable to assemble array: Invalid superblocks";
	अगर (super_validate(rs, freshest))
		वापस -EINVAL;

	अगर (validate_raid_redundancy(rs)) अणु
		rs->ti->error = "Insufficient redundancy to activate array";
		वापस -EINVAL;
	पूर्ण

	rdev_क्रम_each(rdev, mddev)
		अगर (!test_bit(Journal, &rdev->flags) &&
		    rdev != freshest &&
		    super_validate(rs, rdev))
			वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Adjust data_offset and new_data_offset on all disk members of @rs
 * क्रम out of place reshaping अगर requested by contructor
 *
 * We need मुक्त space at the beginning of each raid disk क्रम क्रमward
 * and at the end क्रम backward reshapes which userspace has to provide
 * via remapping/reordering of space.
 */
अटल पूर्णांक rs_adjust_data_offsets(काष्ठा raid_set *rs)
अणु
	sector_t data_offset = 0, new_data_offset = 0;
	काष्ठा md_rdev *rdev;

	/* Conकाष्ठाor did not request data offset change */
	अगर (!test_bit(__CTR_FLAG_DATA_OFFSET, &rs->ctr_flags)) अणु
		अगर (!rs_is_reshapable(rs))
			जाओ out;

		वापस 0;
	पूर्ण

	/* HM FIXME: get In_Sync raid_dev? */
	rdev = &rs->dev[0].rdev;

	अगर (rs->delta_disks < 0) अणु
		/*
		 * Removing disks (reshaping backwards):
		 *
		 * - beक्रमe reshape: data is at offset 0 and मुक्त space
		 *		     is at end of each component LV
		 *
		 * - after reshape: data is at offset rs->data_offset != 0 on each component LV
		 */
		data_offset = 0;
		new_data_offset = rs->data_offset;

	पूर्ण अन्यथा अगर (rs->delta_disks > 0) अणु
		/*
		 * Adding disks (reshaping क्रमwards):
		 *
		 * - beक्रमe reshape: data is at offset rs->data_offset != 0 and
		 *		     मुक्त space is at begin of each component LV
		 *
		 * - after reshape: data is at offset 0 on each component LV
		 */
		data_offset = rs->data_offset;
		new_data_offset = 0;

	पूर्ण अन्यथा अणु
		/*
		 * User space passes in 0 क्रम data offset after having हटाओd reshape space
		 *
		 * - or - (data offset != 0)
		 *
		 * Changing RAID layout or chunk size -> toggle offsets
		 *
		 * - beक्रमe reshape: data is at offset rs->data_offset 0 and
		 *		     मुक्त space is at end of each component LV
		 *		     -or-
		 *                   data is at offset rs->data_offset != 0 and
		 *		     मुक्त space is at begin of each component LV
		 *
		 * - after reshape: data is at offset 0 अगर it was at offset != 0
		 *                  or at offset != 0 अगर it was at offset 0
		 *                  on each component LV
		 *
		 */
		data_offset = rs->data_offset ? rdev->data_offset : 0;
		new_data_offset = data_offset ? 0 : rs->data_offset;
		set_bit(RT_FLAG_UPDATE_SBS, &rs->runसमय_flags);
	पूर्ण

	/*
	 * Make sure we got a minimum amount of मुक्त sectors per device
	 */
	अगर (rs->data_offset &&
	    to_sector(i_size_पढ़ो(rdev->bdev->bd_inode)) - rs->md.dev_sectors < MIN_FREE_RESHAPE_SPACE) अणु
		rs->ti->error = data_offset ? "No space for forward reshape" :
					      "No space for backward reshape";
		वापस -ENOSPC;
	पूर्ण
out:
	/*
	 * Raise recovery_cp in हाल data_offset != 0 to
	 * aव्योम false recovery positives in the स्थिरructor.
	 */
	अगर (rs->md.recovery_cp < rs->md.dev_sectors)
		rs->md.recovery_cp += rs->dev[0].rdev.data_offset;

	/* Adjust data offsets on all rdevs but on any raid4/5/6 journal device */
	rdev_क्रम_each(rdev, &rs->md) अणु
		अगर (!test_bit(Journal, &rdev->flags)) अणु
			rdev->data_offset = data_offset;
			rdev->new_data_offset = new_data_offset;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Userpace reordered disks -> adjust raid_disk indexes in @rs */
अटल व्योम __reorder_raid_disk_indexes(काष्ठा raid_set *rs)
अणु
	पूर्णांक i = 0;
	काष्ठा md_rdev *rdev;

	rdev_क्रम_each(rdev, &rs->md) अणु
		अगर (!test_bit(Journal, &rdev->flags)) अणु
			rdev->raid_disk = i++;
			rdev->saved_raid_disk = rdev->new_raid_disk = -1;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Setup @rs क्रम takeover by a dअगरferent raid level
 */
अटल पूर्णांक rs_setup_takeover(काष्ठा raid_set *rs)
अणु
	काष्ठा mddev *mddev = &rs->md;
	काष्ठा md_rdev *rdev;
	अचिन्हित पूर्णांक d = mddev->raid_disks = rs->raid_disks;
	sector_t new_data_offset = rs->dev[0].rdev.data_offset ? 0 : rs->data_offset;

	अगर (rt_is_raid10(rs->raid_type)) अणु
		अगर (rs_is_raid0(rs)) अणु
			/* Userpace reordered disks -> adjust raid_disk indexes */
			__reorder_raid_disk_indexes(rs);

			/* raid0 -> raid10_far layout */
			mddev->layout = raid10_क्रमmat_to_md_layout(rs, ALGORITHM_RAID10_FAR,
								   rs->raid10_copies);
		पूर्ण अन्यथा अगर (rs_is_raid1(rs))
			/* raid1 -> raid10_near layout */
			mddev->layout = raid10_क्रमmat_to_md_layout(rs, ALGORITHM_RAID10_NEAR,
								   rs->raid_disks);
		अन्यथा
			वापस -EINVAL;

	पूर्ण

	clear_bit(MD_ARRAY_FIRST_USE, &mddev->flags);
	mddev->recovery_cp = MaxSector;

	जबतक (d--) अणु
		rdev = &rs->dev[d].rdev;

		अगर (test_bit(d, (व्योम *) rs->rebuild_disks)) अणु
			clear_bit(In_sync, &rdev->flags);
			clear_bit(Faulty, &rdev->flags);
			mddev->recovery_cp = rdev->recovery_offset = 0;
			/* Biपंचांगap has to be created when we करो an "up" takeover */
			set_bit(MD_ARRAY_FIRST_USE, &mddev->flags);
		पूर्ण

		rdev->new_data_offset = new_data_offset;
	पूर्ण

	वापस 0;
पूर्ण

/* Prepare @rs क्रम reshape */
अटल पूर्णांक rs_prepare_reshape(काष्ठा raid_set *rs)
अणु
	bool reshape;
	काष्ठा mddev *mddev = &rs->md;

	अगर (rs_is_raid10(rs)) अणु
		अगर (rs->raid_disks != mddev->raid_disks &&
		    __is_raid10_near(mddev->layout) &&
		    rs->raid10_copies &&
		    rs->raid10_copies != __raid10_near_copies(mddev->layout)) अणु
			/*
			 * raid disk have to be multiple of data copies to allow this conversion,
			 *
			 * This is actually not a reshape it is a
			 * rebuild of any additional mirrors per group
			 */
			अगर (rs->raid_disks % rs->raid10_copies) अणु
				rs->ti->error = "Can't reshape raid10 mirror groups";
				वापस -EINVAL;
			पूर्ण

			/* Userpace reordered disks to add/हटाओ mirrors -> adjust raid_disk indexes */
			__reorder_raid_disk_indexes(rs);
			mddev->layout = raid10_क्रमmat_to_md_layout(rs, ALGORITHM_RAID10_NEAR,
								   rs->raid10_copies);
			mddev->new_layout = mddev->layout;
			reshape = false;
		पूर्ण अन्यथा
			reshape = true;

	पूर्ण अन्यथा अगर (rs_is_raid456(rs))
		reshape = true;

	अन्यथा अगर (rs_is_raid1(rs)) अणु
		अगर (rs->delta_disks) अणु
			/* Process raid1 via delta_disks */
			mddev->degraded = rs->delta_disks < 0 ? -rs->delta_disks : rs->delta_disks;
			reshape = true;
		पूर्ण अन्यथा अणु
			/* Process raid1 without delta_disks */
			mddev->raid_disks = rs->raid_disks;
			reshape = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		rs->ti->error = "Called with bogus raid type";
		वापस -EINVAL;
	पूर्ण

	अगर (reshape) अणु
		set_bit(RT_FLAG_RESHAPE_RS, &rs->runसमय_flags);
		set_bit(RT_FLAG_UPDATE_SBS, &rs->runसमय_flags);
	पूर्ण अन्यथा अगर (mddev->raid_disks < rs->raid_disks)
		/* Create new superblocks and biपंचांगaps, अगर any new disks */
		set_bit(RT_FLAG_UPDATE_SBS, &rs->runसमय_flags);

	वापस 0;
पूर्ण

/* Get reshape sectors from data_offsets or raid set */
अटल sector_t _get_reshape_sectors(काष्ठा raid_set *rs)
अणु
	काष्ठा md_rdev *rdev;
	sector_t reshape_sectors = 0;

	rdev_क्रम_each(rdev, &rs->md)
		अगर (!test_bit(Journal, &rdev->flags)) अणु
			reshape_sectors = (rdev->data_offset > rdev->new_data_offset) ?
					rdev->data_offset - rdev->new_data_offset :
					rdev->new_data_offset - rdev->data_offset;
			अवरोध;
		पूर्ण

	वापस max(reshape_sectors, (sector_t) rs->data_offset);
पूर्ण

/*
 * Reshape:
 * - change raid layout
 * - change chunk size
 * - add disks
 * - हटाओ disks
 */
अटल पूर्णांक rs_setup_reshape(काष्ठा raid_set *rs)
अणु
	पूर्णांक r = 0;
	अचिन्हित पूर्णांक cur_raid_devs, d;
	sector_t reshape_sectors = _get_reshape_sectors(rs);
	काष्ठा mddev *mddev = &rs->md;
	काष्ठा md_rdev *rdev;

	mddev->delta_disks = rs->delta_disks;
	cur_raid_devs = mddev->raid_disks;

	/* Ignore impossible layout change whilst adding/removing disks */
	अगर (mddev->delta_disks &&
	    mddev->layout != mddev->new_layout) अणु
		DMINFO("Ignoring invalid layout change with delta_disks=%d", rs->delta_disks);
		mddev->new_layout = mddev->layout;
	पूर्ण

	/*
	 * Adjust array size:
	 *
	 * - in हाल of adding disk(s), array size has
	 *   to grow after the disk adding reshape,
	 *   which'll hapen in the event handler;
	 *   reshape will happen क्रमward, so space has to
	 *   be available at the beginning of each disk
	 *
	 * - in हाल of removing disk(s), array size
	 *   has to shrink beक्रमe starting the reshape,
	 *   which'll happen here;
	 *   reshape will happen backward, so space has to
	 *   be available at the end of each disk
	 *
	 * - data_offset and new_data_offset are
	 *   adjusted क्रम aक्रमementioned out of place
	 *   reshaping based on userspace passing in
	 *   the "data_offset <sectors>" key/value
	 *   pair via the स्थिरructor
	 */

	/* Add disk(s) */
	अगर (rs->delta_disks > 0) अणु
		/* Prepare disks क्रम check in raid4/5/6/10 अणुcheck|startपूर्ण_reshape */
		क्रम (d = cur_raid_devs; d < rs->raid_disks; d++) अणु
			rdev = &rs->dev[d].rdev;
			clear_bit(In_sync, &rdev->flags);

			/*
			 * save_raid_disk needs to be -1, or recovery_offset will be set to 0
			 * by md, which'll store that erroneously in the superblock on reshape
			 */
			rdev->saved_raid_disk = -1;
			rdev->raid_disk = d;

			rdev->sectors = mddev->dev_sectors;
			rdev->recovery_offset = rs_is_raid1(rs) ? 0 : MaxSector;
		पूर्ण

		mddev->reshape_backwards = 0; /* adding disk(s) -> क्रमward reshape */

	/* Remove disk(s) */
	पूर्ण अन्यथा अगर (rs->delta_disks < 0) अणु
		r = rs_set_dev_and_array_sectors(rs, rs->ti->len, true);
		mddev->reshape_backwards = 1; /* removing disk(s) -> backward reshape */

	/* Change layout and/or chunk size */
	पूर्ण अन्यथा अणु
		/*
		 * Reshape layout (e.g. raid5_ls -> raid5_n) and/or chunk size:
		 *
		 * keeping number of disks and करो layout change ->
		 *
		 * toggle reshape_backward depending on data_offset:
		 *
		 * - मुक्त space upfront -> reshape क्रमward
		 *
		 * - मुक्त space at the end -> reshape backward
		 *
		 *
		 * This utilizes मुक्त reshape space aव्योमing the need
		 * क्रम userspace to move (parts of) LV segments in
		 * हाल of layout/chunksize change  (क्रम disk
		 * adding/removing reshape space has to be at
		 * the proper address (see above with delta_disks):
		 *
		 * add disk(s)   -> begin
		 * हटाओ disk(s)-> end
		 */
		mddev->reshape_backwards = rs->dev[0].rdev.data_offset ? 0 : 1;
	पूर्ण

	/*
	 * Adjust device size क्रम क्रमward reshape
	 * because md_finish_reshape() reduces it.
	 */
	अगर (!mddev->reshape_backwards)
		rdev_क्रम_each(rdev, &rs->md)
			अगर (!test_bit(Journal, &rdev->flags))
				rdev->sectors += reshape_sectors;

	वापस r;
पूर्ण

/*
 * If the md resync thपढ़ो has updated superblock with max reshape position
 * at the end of a reshape but not (yet) reset the layout configuration
 * changes -> reset the latter.
 */
अटल व्योम rs_reset_inconclusive_reshape(काष्ठा raid_set *rs)
अणु
	अगर (!rs_is_reshaping(rs) && rs_is_layout_change(rs, true)) अणु
		rs_set_cur(rs);
		rs->md.delta_disks = 0;
		rs->md.reshape_backwards = 0;
	पूर्ण
पूर्ण

/*
 * Enable/disable discard support on RAID set depending on
 * RAID level and discard properties of underlying RAID members.
 */
अटल व्योम configure_discard_support(काष्ठा raid_set *rs)
अणु
	पूर्णांक i;
	bool raid456;
	काष्ठा dm_target *ti = rs->ti;

	/*
	 * XXX: RAID level 4,5,6 require zeroing क्रम safety.
	 */
	raid456 = rs_is_raid456(rs);

	क्रम (i = 0; i < rs->raid_disks; i++) अणु
		काष्ठा request_queue *q;

		अगर (!rs->dev[i].rdev.bdev)
			जारी;

		q = bdev_get_queue(rs->dev[i].rdev.bdev);
		अगर (!q || !blk_queue_discard(q))
			वापस;

		अगर (raid456) अणु
			अगर (!devices_handle_discard_safely) अणु
				DMERR("raid456 discard support disabled due to discard_zeroes_data uncertainty.");
				DMERR("Set dm-raid.devices_handle_discard_safely=Y to override.");
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	ti->num_discard_bios = 1;
पूर्ण

/*
 * Conकाष्ठा a RAID0/1/10/4/5/6 mapping:
 * Args:
 *	<raid_type> <#raid_params> <raid_params>अणु0,पूर्ण	\
 *	<#raid_devs> [<meta_dev1> <dev1>]अणु1,पूर्ण
 *
 * <raid_params> varies by <raid_type>.	 See 'parse_raid_params' क्रम
 * details on possible <raid_params>.
 *
 * Userspace is मुक्त to initialize the metadata devices, hence the superblocks to
 * enक्रमce recreation based on the passed in table parameters.
 *
 */
अटल पूर्णांक raid_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक r;
	bool resize = false;
	काष्ठा raid_type *rt;
	अचिन्हित पूर्णांक num_raid_params, num_raid_devs;
	sector_t sb_array_sectors, rdev_sectors, reshape_sectors;
	काष्ठा raid_set *rs = शून्य;
	स्थिर अक्षर *arg;
	काष्ठा rs_layout rs_layout;
	काष्ठा dm_arg_set as = अणु argc, argv पूर्ण, as_nrd;
	काष्ठा dm_arg _args[] = अणु
		अणु 0, as.argc, "Cannot understand number of raid parameters" पूर्ण,
		अणु 1, 254, "Cannot understand number of raid devices parameters" पूर्ण
	पूर्ण;

	arg = dm_shअगरt_arg(&as);
	अगर (!arg) अणु
		ti->error = "No arguments";
		वापस -EINVAL;
	पूर्ण

	rt = get_raid_type(arg);
	अगर (!rt) अणु
		ti->error = "Unrecognised raid_type";
		वापस -EINVAL;
	पूर्ण

	/* Must have <#raid_params> */
	अगर (dm_पढ़ो_arg_group(_args, &as, &num_raid_params, &ti->error))
		वापस -EINVAL;

	/* number of raid device tupples <meta_dev data_dev> */
	as_nrd = as;
	dm_consume_args(&as_nrd, num_raid_params);
	_args[1].max = (as_nrd.argc - 1) / 2;
	अगर (dm_पढ़ो_arg(_args + 1, &as_nrd, &num_raid_devs, &ti->error))
		वापस -EINVAL;

	अगर (!__within_range(num_raid_devs, 1, MAX_RAID_DEVICES)) अणु
		ti->error = "Invalid number of supplied raid devices";
		वापस -EINVAL;
	पूर्ण

	rs = raid_set_alloc(ti, rt, num_raid_devs);
	अगर (IS_ERR(rs))
		वापस PTR_ERR(rs);

	r = parse_raid_params(rs, &as, num_raid_params);
	अगर (r)
		जाओ bad;

	r = parse_dev_params(rs, &as);
	अगर (r)
		जाओ bad;

	rs->md.sync_super = super_sync;

	/*
	 * Calculate ctr requested array and device sizes to allow
	 * क्रम superblock analysis needing device sizes defined.
	 *
	 * Any existing superblock will overग_लिखो the array and device sizes
	 */
	r = rs_set_dev_and_array_sectors(rs, rs->ti->len, false);
	अगर (r)
		जाओ bad;

	/* Memorize just calculated, potentially larger sizes to grow the raid set in preresume */
	rs->array_sectors = rs->md.array_sectors;
	rs->dev_sectors = rs->md.dev_sectors;

	/*
	 * Backup any new raid set level, layout, ...
	 * requested to be able to compare to superblock
	 * members क्रम conversion decisions.
	 */
	rs_config_backup(rs, &rs_layout);

	r = analyse_superblocks(ti, rs);
	अगर (r)
		जाओ bad;

	/* All in-core metadata now as of current superblocks after calling analyse_superblocks() */
	sb_array_sectors = rs->md.array_sectors;
	rdev_sectors = __rdev_sectors(rs);
	अगर (!rdev_sectors) अणु
		ti->error = "Invalid rdev size";
		r = -EINVAL;
		जाओ bad;
	पूर्ण


	reshape_sectors = _get_reshape_sectors(rs);
	अगर (rs->dev_sectors != rdev_sectors) अणु
		resize = (rs->dev_sectors != rdev_sectors - reshape_sectors);
		अगर (rs->dev_sectors > rdev_sectors - reshape_sectors)
			set_bit(RT_FLAG_RS_GROW, &rs->runसमय_flags);
	पूर्ण

	INIT_WORK(&rs->md.event_work, करो_table_event);
	ti->निजी = rs;
	ti->num_flush_bios = 1;

	/* Restore any requested new layout क्रम conversion decision */
	rs_config_restore(rs, &rs_layout);

	/*
	 * Now that we have any superblock metadata available,
	 * check क्रम new, recovering, reshaping, to be taken over,
	 * to be reshaped or an existing, unchanged raid set to
	 * run in sequence.
	 */
	अगर (test_bit(MD_ARRAY_FIRST_USE, &rs->md.flags)) अणु
		/* A new raid6 set has to be recovered to ensure proper parity and Q-Syndrome */
		अगर (rs_is_raid6(rs) &&
		    test_bit(__CTR_FLAG_NOSYNC, &rs->ctr_flags)) अणु
			ti->error = "'nosync' not allowed for new raid6 set";
			r = -EINVAL;
			जाओ bad;
		पूर्ण
		rs_setup_recovery(rs, 0);
		set_bit(RT_FLAG_UPDATE_SBS, &rs->runसमय_flags);
		rs_set_new(rs);
	पूर्ण अन्यथा अगर (rs_is_recovering(rs)) अणु
		/* A recovering raid set may be resized */
		जाओ size_check;
	पूर्ण अन्यथा अगर (rs_is_reshaping(rs)) अणु
		/* Have to reject size change request during reshape */
		अगर (resize) अणु
			ti->error = "Can't resize a reshaping raid set";
			r = -EPERM;
			जाओ bad;
		पूर्ण
		/* skip setup rs */
	पूर्ण अन्यथा अगर (rs_takeover_requested(rs)) अणु
		अगर (rs_is_reshaping(rs)) अणु
			ti->error = "Can't takeover a reshaping raid set";
			r = -EPERM;
			जाओ bad;
		पूर्ण

		/* We can't takeover a journaled raid4/5/6 */
		अगर (test_bit(__CTR_FLAG_JOURNAL_DEV, &rs->ctr_flags)) अणु
			ti->error = "Can't takeover a journaled raid4/5/6 set";
			r = -EPERM;
			जाओ bad;
		पूर्ण

		/*
		 * If a takeover is needed, userspace sets any additional
		 * devices to rebuild and we can check क्रम a valid request here.
		 *
		 * If acceptible, set the level to the new requested
		 * one, prohibit requesting recovery, allow the raid
		 * set to run and store superblocks during resume.
		 */
		r = rs_check_takeover(rs);
		अगर (r)
			जाओ bad;

		r = rs_setup_takeover(rs);
		अगर (r)
			जाओ bad;

		set_bit(RT_FLAG_UPDATE_SBS, &rs->runसमय_flags);
		/* Takeover ain't recovery, so disable recovery */
		rs_setup_recovery(rs, MaxSector);
		rs_set_new(rs);
	पूर्ण अन्यथा अगर (rs_reshape_requested(rs)) अणु
		/* Only request grow on raid set size extensions, not on reshapes. */
		clear_bit(RT_FLAG_RS_GROW, &rs->runसमय_flags);

		/*
		 * No need to check क्रम 'ongoing' takeover here, because takeover
		 * is an instant operation as oposed to an ongoing reshape.
		 */

		/* We can't reshape a journaled raid4/5/6 */
		अगर (test_bit(__CTR_FLAG_JOURNAL_DEV, &rs->ctr_flags)) अणु
			ti->error = "Can't reshape a journaled raid4/5/6 set";
			r = -EPERM;
			जाओ bad;
		पूर्ण

		/* Out-of-place space has to be available to allow क्रम a reshape unless raid1! */
		अगर (reshape_sectors || rs_is_raid1(rs)) अणु
			/*
			  * We can only prepare क्रम a reshape here, because the
			  * raid set needs to run to provide the repective reshape
			  * check functions via its MD personality instance.
			  *
			  * So करो the reshape check after md_run() succeeded.
			  */
			r = rs_prepare_reshape(rs);
			अगर (r)
				जाओ bad;

			/* Reshaping ain't recovery, so disable recovery */
			rs_setup_recovery(rs, MaxSector);
		पूर्ण
		rs_set_cur(rs);
	पूर्ण अन्यथा अणु
size_check:
		/* May not set recovery when a device rebuild is requested */
		अगर (test_bit(__CTR_FLAG_REBUILD, &rs->ctr_flags)) अणु
			clear_bit(RT_FLAG_RS_GROW, &rs->runसमय_flags);
			set_bit(RT_FLAG_UPDATE_SBS, &rs->runसमय_flags);
			rs_setup_recovery(rs, MaxSector);
		पूर्ण अन्यथा अगर (test_bit(RT_FLAG_RS_GROW, &rs->runसमय_flags)) अणु
			/*
			 * Set raid set to current size, i.e. size as of
			 * superblocks to grow to larger size in preresume.
			 */
			r = rs_set_dev_and_array_sectors(rs, sb_array_sectors, false);
			अगर (r)
				जाओ bad;

			rs_setup_recovery(rs, rs->md.recovery_cp < rs->md.dev_sectors ? rs->md.recovery_cp : rs->md.dev_sectors);
		पूर्ण अन्यथा अणु
			/* This is no size change or it is shrinking, update size and record in superblocks */
			r = rs_set_dev_and_array_sectors(rs, rs->ti->len, false);
			अगर (r)
				जाओ bad;

			अगर (sb_array_sectors > rs->array_sectors)
				set_bit(RT_FLAG_UPDATE_SBS, &rs->runसमय_flags);
		पूर्ण
		rs_set_cur(rs);
	पूर्ण

	/* If स्थिरructor requested it, change data and new_data offsets */
	r = rs_adjust_data_offsets(rs);
	अगर (r)
		जाओ bad;

	/* Catch any inconclusive reshape superblock content. */
	rs_reset_inconclusive_reshape(rs);

	/* Start raid set पढ़ो-only and assumed clean to change in raid_resume() */
	rs->md.ro = 1;
	rs->md.in_sync = 1;

	/* Keep array frozen until resume. */
	set_bit(MD_RECOVERY_FROZEN, &rs->md.recovery);

	/* Has to be held on running the array */
	mddev_lock_noपूर्णांकr(&rs->md);
	r = md_run(&rs->md);
	rs->md.in_sync = 0; /* Assume alपढ़ोy marked dirty */
	अगर (r) अणु
		ti->error = "Failed to run raid array";
		mddev_unlock(&rs->md);
		जाओ bad;
	पूर्ण

	r = md_start(&rs->md);
	अगर (r) अणु
		ti->error = "Failed to start raid array";
		mddev_unlock(&rs->md);
		जाओ bad_md_start;
	पूर्ण

	/* If raid4/5/6 journal mode explicitly requested (only possible with journal dev) -> set it */
	अगर (test_bit(__CTR_FLAG_JOURNAL_MODE, &rs->ctr_flags)) अणु
		r = r5c_journal_mode_set(&rs->md, rs->journal_dev.mode);
		अगर (r) अणु
			ti->error = "Failed to set raid4/5/6 journal mode";
			mddev_unlock(&rs->md);
			जाओ bad_journal_mode_set;
		पूर्ण
	पूर्ण

	mddev_suspend(&rs->md);
	set_bit(RT_FLAG_RS_SUSPENDED, &rs->runसमय_flags);

	/* Try to adjust the raid4/5/6 stripe cache size to the stripe size */
	अगर (rs_is_raid456(rs)) अणु
		r = rs_set_raid456_stripe_cache(rs);
		अगर (r)
			जाओ bad_stripe_cache;
	पूर्ण

	/* Now करो an early reshape check */
	अगर (test_bit(RT_FLAG_RESHAPE_RS, &rs->runसमय_flags)) अणु
		r = rs_check_reshape(rs);
		अगर (r)
			जाओ bad_check_reshape;

		/* Restore new, ctr requested layout to perक्रमm check */
		rs_config_restore(rs, &rs_layout);

		अगर (rs->md.pers->start_reshape) अणु
			r = rs->md.pers->check_reshape(&rs->md);
			अगर (r) अणु
				ti->error = "Reshape check failed";
				जाओ bad_check_reshape;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Disable/enable discard support on raid set. */
	configure_discard_support(rs);

	mddev_unlock(&rs->md);
	वापस 0;

bad_md_start:
bad_journal_mode_set:
bad_stripe_cache:
bad_check_reshape:
	md_stop(&rs->md);
bad:
	raid_set_मुक्त(rs);

	वापस r;
पूर्ण

अटल व्योम raid_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा raid_set *rs = ti->निजी;

	md_stop(&rs->md);
	raid_set_मुक्त(rs);
पूर्ण

अटल पूर्णांक raid_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा raid_set *rs = ti->निजी;
	काष्ठा mddev *mddev = &rs->md;

	/*
	 * If we're reshaping to add disk(s)), ti->len and
	 * mddev->array_sectors will dअगरfer during the process
	 * (ti->len > mddev->array_sectors), so we have to requeue
	 * bios with addresses > mddev->array_sectors here or
	 * there will occur accesses past EOD of the component
	 * data images thus erroring the raid set.
	 */
	अगर (unlikely(bio_end_sector(bio) > mddev->array_sectors))
		वापस DM_MAPIO_REQUEUE;

	md_handle_request(mddev, bio);

	वापस DM_MAPIO_SUBMITTED;
पूर्ण

/* Return sync state string क्रम @state */
क्रमागत sync_state अणु st_frozen, st_reshape, st_resync, st_check, st_repair, st_recover, st_idle पूर्ण;
अटल स्थिर अक्षर *sync_str(क्रमागत sync_state state)
अणु
	/* Has to be in above sync_state order! */
	अटल स्थिर अक्षर *sync_strs[] = अणु
		"frozen",
		"reshape",
		"resync",
		"check",
		"repair",
		"recover",
		"idle"
	पूर्ण;

	वापस __within_range(state, 0, ARRAY_SIZE(sync_strs) - 1) ? sync_strs[state] : "undef";
पूर्ण;

/* Return क्रमागत sync_state क्रम @mddev derived from @recovery flags */
अटल क्रमागत sync_state decipher_sync_action(काष्ठा mddev *mddev, अचिन्हित दीर्घ recovery)
अणु
	अगर (test_bit(MD_RECOVERY_FROZEN, &recovery))
		वापस st_frozen;

	/* The MD sync thपढ़ो can be करोne with io or be पूर्णांकerrupted but still be running */
	अगर (!test_bit(MD_RECOVERY_DONE, &recovery) &&
	    (test_bit(MD_RECOVERY_RUNNING, &recovery) ||
	     (!mddev->ro && test_bit(MD_RECOVERY_NEEDED, &recovery)))) अणु
		अगर (test_bit(MD_RECOVERY_RESHAPE, &recovery))
			वापस st_reshape;

		अगर (test_bit(MD_RECOVERY_SYNC, &recovery)) अणु
			अगर (!test_bit(MD_RECOVERY_REQUESTED, &recovery))
				वापस st_resync;
			अगर (test_bit(MD_RECOVERY_CHECK, &recovery))
				वापस st_check;
			वापस st_repair;
		पूर्ण

		अगर (test_bit(MD_RECOVERY_RECOVER, &recovery))
			वापस st_recover;

		अगर (mddev->reshape_position != MaxSector)
			वापस st_reshape;
	पूर्ण

	वापस st_idle;
पूर्ण

/*
 * Return status string क्रम @rdev
 *
 * Status अक्षरacters:
 *
 *  'D' = Dead/Failed raid set component or raid4/5/6 journal device
 *  'a' = Alive but not in-sync raid set component _or_ alive raid4/5/6 'write_back' journal device
 *  'A' = Alive and in-sync raid set component _or_ alive raid4/5/6 'write_through' journal device
 *  '-' = Non-existing device (i.e. uspace passed '- -' पूर्णांकo the ctr)
 */
अटल स्थिर अक्षर *__raid_dev_status(काष्ठा raid_set *rs, काष्ठा md_rdev *rdev)
अणु
	अगर (!rdev->bdev)
		वापस "-";
	अन्यथा अगर (test_bit(Faulty, &rdev->flags))
		वापस "D";
	अन्यथा अगर (test_bit(Journal, &rdev->flags))
		वापस (rs->journal_dev.mode == R5C_JOURNAL_MODE_WRITE_THROUGH) ? "A" : "a";
	अन्यथा अगर (test_bit(RT_FLAG_RS_RESYNCING, &rs->runसमय_flags) ||
		 (!test_bit(RT_FLAG_RS_IN_SYNC, &rs->runसमय_flags) &&
		  !test_bit(In_sync, &rdev->flags)))
		वापस "a";
	अन्यथा
		वापस "A";
पूर्ण

/* Helper to वापस resync/reshape progress क्रम @rs and runसमय flags क्रम raid set in sync / resynching */
अटल sector_t rs_get_progress(काष्ठा raid_set *rs, अचिन्हित दीर्घ recovery,
				क्रमागत sync_state state, sector_t resync_max_sectors)
अणु
	sector_t r;
	काष्ठा mddev *mddev = &rs->md;

	clear_bit(RT_FLAG_RS_IN_SYNC, &rs->runसमय_flags);
	clear_bit(RT_FLAG_RS_RESYNCING, &rs->runसमय_flags);

	अगर (rs_is_raid0(rs)) अणु
		r = resync_max_sectors;
		set_bit(RT_FLAG_RS_IN_SYNC, &rs->runसमय_flags);

	पूर्ण अन्यथा अणु
		अगर (state == st_idle && !test_bit(MD_RECOVERY_INTR, &recovery))
			r = mddev->recovery_cp;
		अन्यथा
			r = mddev->curr_resync_completed;

		अगर (state == st_idle && r >= resync_max_sectors) अणु
			/*
			 * Sync complete.
			 */
			/* In हाल we have finished recovering, the array is in sync. */
			अगर (test_bit(MD_RECOVERY_RECOVER, &recovery))
				set_bit(RT_FLAG_RS_IN_SYNC, &rs->runसमय_flags);

		पूर्ण अन्यथा अगर (state == st_recover)
			/*
			 * In हाल we are recovering, the array is not in sync
			 * and health अक्षरs should show the recovering legs.
			 *
			 * Alपढ़ोy retrieved recovery offset from curr_resync_completed above.
			 */
			;

		अन्यथा अगर (state == st_resync || state == st_reshape)
			/*
			 * If "resync/reshape" is occurring, the raid set
			 * is or may be out of sync hence the health
			 * अक्षरacters shall be 'a'.
			 */
			set_bit(RT_FLAG_RS_RESYNCING, &rs->runसमय_flags);

		अन्यथा अगर (state == st_check || state == st_repair)
			/*
			 * If "check" or "repair" is occurring, the raid set has
			 * undergone an initial sync and the health अक्षरacters
			 * should not be 'a' anymore.
			 */
			set_bit(RT_FLAG_RS_IN_SYNC, &rs->runसमय_flags);

		अन्यथा अगर (test_bit(MD_RECOVERY_NEEDED, &recovery))
			/*
			 * We are idle and recovery is needed, prevent 'A' अक्षरs race
			 * caused by components still set to in-sync by स्थिरructor.
			 */
			set_bit(RT_FLAG_RS_RESYNCING, &rs->runसमय_flags);

		अन्यथा अणु
			/*
			 * We are idle and the raid set may be करोing an initial
			 * sync, or it may be rebuilding inभागidual components.
			 * If all the devices are In_sync, then it is the raid set
			 * that is being initialized.
			 */
			काष्ठा md_rdev *rdev;

			set_bit(RT_FLAG_RS_IN_SYNC, &rs->runसमय_flags);
			rdev_क्रम_each(rdev, mddev)
				अगर (!test_bit(Journal, &rdev->flags) &&
				    !test_bit(In_sync, &rdev->flags)) अणु
					clear_bit(RT_FLAG_RS_IN_SYNC, &rs->runसमय_flags);
					अवरोध;
				पूर्ण
		पूर्ण
	पूर्ण

	वापस min(r, resync_max_sectors);
पूर्ण

/* Helper to वापस @dev name or "-" अगर !@dev */
अटल स्थिर अक्षर *__get_dev_name(काष्ठा dm_dev *dev)
अणु
	वापस dev ? dev->name : "-";
पूर्ण

अटल व्योम raid_status(काष्ठा dm_target *ti, status_type_t type,
			अचिन्हित पूर्णांक status_flags, अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	काष्ठा raid_set *rs = ti->निजी;
	काष्ठा mddev *mddev = &rs->md;
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक i, max_nr_stripes = conf ? conf->max_nr_stripes : 0;
	अचिन्हित दीर्घ recovery;
	अचिन्हित पूर्णांक raid_param_cnt = 1; /* at least 1 क्रम chunksize */
	अचिन्हित पूर्णांक sz = 0;
	अचिन्हित पूर्णांक rebuild_ग_लिखोmostly_count = 0;
	sector_t progress, resync_max_sectors, resync_mismatches;
	क्रमागत sync_state state;
	काष्ठा raid_type *rt;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		/* *Should* always succeed */
		rt = get_raid_type_by_ll(mddev->new_level, mddev->new_layout);
		अगर (!rt)
			वापस;

		DMEMIT("%s %d ", rt->name, mddev->raid_disks);

		/* Access most recent mddev properties क्रम status output */
		smp_rmb();
		/* Get sensible max sectors even अगर raid set not yet started */
		resync_max_sectors = test_bit(RT_FLAG_RS_PRERESUMED, &rs->runसमय_flags) ?
				      mddev->resync_max_sectors : mddev->dev_sectors;
		recovery = rs->md.recovery;
		state = decipher_sync_action(mddev, recovery);
		progress = rs_get_progress(rs, recovery, state, resync_max_sectors);
		resync_mismatches = (mddev->last_sync_action && !strहालcmp(mddev->last_sync_action, "check")) ?
				    atomic64_पढ़ो(&mddev->resync_mismatches) : 0;

		/* HM FIXME: करो we want another state अक्षर क्रम raid0? It shows 'D'/'A'/'-' now */
		क्रम (i = 0; i < rs->raid_disks; i++)
			DMEMIT(__raid_dev_status(rs, &rs->dev[i].rdev));

		/*
		 * In-sync/Reshape ratio:
		 *  The in-sync ratio shows the progress of:
		 *   - Initializing the raid set
		 *   - Rebuilding a subset of devices of the raid set
		 *  The user can distinguish between the two by referring
		 *  to the status अक्षरacters.
		 *
		 *  The reshape ratio shows the progress of
		 *  changing the raid layout or the number of
		 *  disks of a raid set
		 */
		DMEMIT(" %llu/%llu", (अचिन्हित दीर्घ दीर्घ) progress,
				     (अचिन्हित दीर्घ दीर्घ) resync_max_sectors);

		/*
		 * v1.5.0+:
		 *
		 * Sync action:
		 *   See Documentation/admin-guide/device-mapper/dm-raid.rst क्रम
		 *   inक्रमmation on each of these states.
		 */
		DMEMIT(" %s", sync_str(state));

		/*
		 * v1.5.0+:
		 *
		 * resync_mismatches/mismatch_cnt
		 *   This field shows the number of discrepancies found when
		 *   perक्रमming a "check" of the raid set.
		 */
		DMEMIT(" %llu", (अचिन्हित दीर्घ दीर्घ) resync_mismatches);

		/*
		 * v1.9.0+:
		 *
		 * data_offset (needed क्रम out of space reshaping)
		 *   This field shows the data offset पूर्णांकo the data
		 *   image LV where the first stripes data starts.
		 *
		 * We keep data_offset equal on all raid disks of the set,
		 * so retrieving it from the first raid disk is sufficient.
		 */
		DMEMIT(" %llu", (अचिन्हित दीर्घ दीर्घ) rs->dev[0].rdev.data_offset);

		/*
		 * v1.10.0+:
		 */
		DMEMIT(" %s", test_bit(__CTR_FLAG_JOURNAL_DEV, &rs->ctr_flags) ?
			      __raid_dev_status(rs, &rs->journal_dev.rdev) : "-");
		अवरोध;

	हाल STATUSTYPE_TABLE:
		/* Report the table line string you would use to स्थिरruct this raid set */

		/*
		 * Count any rebuild or ग_लिखोmostly argument pairs and subtract the
		 * hweight count being added below of any rebuild and ग_लिखोmostly ctr flags.
		 */
		क्रम (i = 0; i < rs->raid_disks; i++) अणु
			rebuild_ग_लिखोmostly_count += (test_bit(i, (व्योम *) rs->rebuild_disks) ? 2 : 0) +
						     (test_bit(WriteMostly, &rs->dev[i].rdev.flags) ? 2 : 0);
		पूर्ण
		rebuild_ग_लिखोmostly_count -= (test_bit(__CTR_FLAG_REBUILD, &rs->ctr_flags) ? 2 : 0) +
					     (test_bit(__CTR_FLAG_WRITE_MOSTLY, &rs->ctr_flags) ? 2 : 0);
		/* Calculate raid parameter count based on ^ rebuild/ग_लिखोmostly argument counts and ctr flags set. */
		raid_param_cnt += rebuild_ग_लिखोmostly_count +
				  hweight32(rs->ctr_flags & CTR_FLAG_OPTIONS_NO_ARGS) +
				  hweight32(rs->ctr_flags & CTR_FLAG_OPTIONS_ONE_ARG) * 2;
		/* Emit table line */
		/* This has to be in the करोcumented order क्रम userspace! */
		DMEMIT("%s %u %u", rs->raid_type->name, raid_param_cnt, mddev->new_chunk_sectors);
		अगर (test_bit(__CTR_FLAG_SYNC, &rs->ctr_flags))
			DMEMIT(" %s", dm_raid_arg_name_by_flag(CTR_FLAG_SYNC));
		अगर (test_bit(__CTR_FLAG_NOSYNC, &rs->ctr_flags))
			DMEMIT(" %s", dm_raid_arg_name_by_flag(CTR_FLAG_NOSYNC));
		अगर (test_bit(__CTR_FLAG_REBUILD, &rs->ctr_flags))
			क्रम (i = 0; i < rs->raid_disks; i++)
				अगर (test_bit(i, (व्योम *) rs->rebuild_disks))
					DMEMIT(" %s %u", dm_raid_arg_name_by_flag(CTR_FLAG_REBUILD), i);
		अगर (test_bit(__CTR_FLAG_DAEMON_SLEEP, &rs->ctr_flags))
			DMEMIT(" %s %lu", dm_raid_arg_name_by_flag(CTR_FLAG_DAEMON_SLEEP),
					  mddev->biपंचांगap_info.daemon_sleep);
		अगर (test_bit(__CTR_FLAG_MIN_RECOVERY_RATE, &rs->ctr_flags))
			DMEMIT(" %s %d", dm_raid_arg_name_by_flag(CTR_FLAG_MIN_RECOVERY_RATE),
					 mddev->sync_speed_min);
		अगर (test_bit(__CTR_FLAG_MAX_RECOVERY_RATE, &rs->ctr_flags))
			DMEMIT(" %s %d", dm_raid_arg_name_by_flag(CTR_FLAG_MAX_RECOVERY_RATE),
					 mddev->sync_speed_max);
		अगर (test_bit(__CTR_FLAG_WRITE_MOSTLY, &rs->ctr_flags))
			क्रम (i = 0; i < rs->raid_disks; i++)
				अगर (test_bit(WriteMostly, &rs->dev[i].rdev.flags))
					DMEMIT(" %s %d", dm_raid_arg_name_by_flag(CTR_FLAG_WRITE_MOSTLY),
					       rs->dev[i].rdev.raid_disk);
		अगर (test_bit(__CTR_FLAG_MAX_WRITE_BEHIND, &rs->ctr_flags))
			DMEMIT(" %s %lu", dm_raid_arg_name_by_flag(CTR_FLAG_MAX_WRITE_BEHIND),
					  mddev->biपंचांगap_info.max_ग_लिखो_behind);
		अगर (test_bit(__CTR_FLAG_STRIPE_CACHE, &rs->ctr_flags))
			DMEMIT(" %s %d", dm_raid_arg_name_by_flag(CTR_FLAG_STRIPE_CACHE),
					 max_nr_stripes);
		अगर (test_bit(__CTR_FLAG_REGION_SIZE, &rs->ctr_flags))
			DMEMIT(" %s %llu", dm_raid_arg_name_by_flag(CTR_FLAG_REGION_SIZE),
					   (अचिन्हित दीर्घ दीर्घ) to_sector(mddev->biपंचांगap_info.chunksize));
		अगर (test_bit(__CTR_FLAG_RAID10_COPIES, &rs->ctr_flags))
			DMEMIT(" %s %d", dm_raid_arg_name_by_flag(CTR_FLAG_RAID10_COPIES),
					 raid10_md_layout_to_copies(mddev->layout));
		अगर (test_bit(__CTR_FLAG_RAID10_FORMAT, &rs->ctr_flags))
			DMEMIT(" %s %s", dm_raid_arg_name_by_flag(CTR_FLAG_RAID10_FORMAT),
					 raid10_md_layout_to_क्रमmat(mddev->layout));
		अगर (test_bit(__CTR_FLAG_DELTA_DISKS, &rs->ctr_flags))
			DMEMIT(" %s %d", dm_raid_arg_name_by_flag(CTR_FLAG_DELTA_DISKS),
					 max(rs->delta_disks, mddev->delta_disks));
		अगर (test_bit(__CTR_FLAG_DATA_OFFSET, &rs->ctr_flags))
			DMEMIT(" %s %llu", dm_raid_arg_name_by_flag(CTR_FLAG_DATA_OFFSET),
					   (अचिन्हित दीर्घ दीर्घ) rs->data_offset);
		अगर (test_bit(__CTR_FLAG_JOURNAL_DEV, &rs->ctr_flags))
			DMEMIT(" %s %s", dm_raid_arg_name_by_flag(CTR_FLAG_JOURNAL_DEV),
					__get_dev_name(rs->journal_dev.dev));
		अगर (test_bit(__CTR_FLAG_JOURNAL_MODE, &rs->ctr_flags))
			DMEMIT(" %s %s", dm_raid_arg_name_by_flag(CTR_FLAG_JOURNAL_MODE),
					 md_journal_mode_to_dm_raid(rs->journal_dev.mode));
		DMEMIT(" %d", rs->raid_disks);
		क्रम (i = 0; i < rs->raid_disks; i++)
			DMEMIT(" %s %s", __get_dev_name(rs->dev[i].meta_dev),
					 __get_dev_name(rs->dev[i].data_dev));
	पूर्ण
पूर्ण

अटल पूर्णांक raid_message(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv,
			अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा raid_set *rs = ti->निजी;
	काष्ठा mddev *mddev = &rs->md;

	अगर (!mddev->pers || !mddev->pers->sync_request)
		वापस -EINVAL;

	अगर (!strहालcmp(argv[0], "frozen"))
		set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
	अन्यथा
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);

	अगर (!strहालcmp(argv[0], "idle") || !strहालcmp(argv[0], "frozen")) अणु
		अगर (mddev->sync_thपढ़ो) अणु
			set_bit(MD_RECOVERY_INTR, &mddev->recovery);
			md_reap_sync_thपढ़ो(mddev);
		पूर्ण
	पूर्ण अन्यथा अगर (decipher_sync_action(mddev, mddev->recovery) != st_idle)
		वापस -EBUSY;
	अन्यथा अगर (!strहालcmp(argv[0], "resync"))
		; /* MD_RECOVERY_NEEDED set below */
	अन्यथा अगर (!strहालcmp(argv[0], "recover"))
		set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	अन्यथा अणु
		अगर (!strहालcmp(argv[0], "check")) अणु
			set_bit(MD_RECOVERY_CHECK, &mddev->recovery);
			set_bit(MD_RECOVERY_REQUESTED, &mddev->recovery);
			set_bit(MD_RECOVERY_SYNC, &mddev->recovery);
		पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "repair")) अणु
			set_bit(MD_RECOVERY_REQUESTED, &mddev->recovery);
			set_bit(MD_RECOVERY_SYNC, &mddev->recovery);
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण
	अगर (mddev->ro == 2) अणु
		/* A ग_लिखो to sync_action is enough to justअगरy
		 * canceling पढ़ो-स्वतः mode
		 */
		mddev->ro = 0;
		अगर (!mddev->suspended && mddev->sync_thपढ़ो)
			md_wakeup_thपढ़ो(mddev->sync_thपढ़ो);
	पूर्ण
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	अगर (!mddev->suspended && mddev->thपढ़ो)
		md_wakeup_thपढ़ो(mddev->thपढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक raid_iterate_devices(काष्ठा dm_target *ti,
				iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा raid_set *rs = ti->निजी;
	अचिन्हित पूर्णांक i;
	पूर्णांक r = 0;

	क्रम (i = 0; !r && i < rs->md.raid_disks; i++)
		अगर (rs->dev[i].data_dev)
			r = fn(ti,
				 rs->dev[i].data_dev,
				 0, /* No offset on data devs */
				 rs->md.dev_sectors,
				 data);

	वापस r;
पूर्ण

अटल व्योम raid_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा raid_set *rs = ti->निजी;
	अचिन्हित पूर्णांक chunk_size_bytes = to_bytes(rs->md.chunk_sectors);

	blk_limits_io_min(limits, chunk_size_bytes);
	blk_limits_io_opt(limits, chunk_size_bytes * mddev_data_stripes(rs));
पूर्ण

अटल व्योम raid_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा raid_set *rs = ti->निजी;

	अगर (!test_and_set_bit(RT_FLAG_RS_SUSPENDED, &rs->runसमय_flags)) अणु
		/* Writes have to be stopped beक्रमe suspending to aव्योम deadlocks. */
		अगर (!test_bit(MD_RECOVERY_FROZEN, &rs->md.recovery))
			md_stop_ग_लिखोs(&rs->md);

		mddev_lock_noपूर्णांकr(&rs->md);
		mddev_suspend(&rs->md);
		mddev_unlock(&rs->md);
	पूर्ण
पूर्ण

अटल व्योम attempt_restore_of_faulty_devices(काष्ठा raid_set *rs)
अणु
	पूर्णांक i;
	uपूर्णांक64_t cleared_failed_devices[DISKS_ARRAY_ELEMS];
	अचिन्हित दीर्घ flags;
	bool cleared = false;
	काष्ठा dm_raid_superblock *sb;
	काष्ठा mddev *mddev = &rs->md;
	काष्ठा md_rdev *r;

	/* RAID personalities have to provide hot add/हटाओ methods or we need to bail out. */
	अगर (!mddev->pers || !mddev->pers->hot_add_disk || !mddev->pers->hot_हटाओ_disk)
		वापस;

	स_रखो(cleared_failed_devices, 0, माप(cleared_failed_devices));

	क्रम (i = 0; i < mddev->raid_disks; i++) अणु
		r = &rs->dev[i].rdev;
		/* HM FIXME: enhance journal device recovery processing */
		अगर (test_bit(Journal, &r->flags))
			जारी;

		अगर (test_bit(Faulty, &r->flags) &&
		    r->meta_bdev && !पढ़ो_disk_sb(r, r->sb_size, true)) अणु
			DMINFO("Faulty %s device #%d has readable super block."
			       "  Attempting to revive it.",
			       rs->raid_type->name, i);

			/*
			 * Faulty bit may be set, but someबार the array can
			 * be suspended beक्रमe the personalities can respond
			 * by removing the device from the array (i.e. calling
			 * 'hot_remove_disk').	If they haven't yet हटाओd
			 * the failed device, its 'raid_disk' number will be
			 * '>= 0' - meaning we must call this function
			 * ourselves.
			 */
			flags = r->flags;
			clear_bit(In_sync, &r->flags); /* Mandatory क्रम hot हटाओ. */
			अगर (r->raid_disk >= 0) अणु
				अगर (mddev->pers->hot_हटाओ_disk(mddev, r)) अणु
					/* Failed to revive this device, try next */
					r->flags = flags;
					जारी;
				पूर्ण
			पूर्ण अन्यथा
				r->raid_disk = r->saved_raid_disk = i;

			clear_bit(Faulty, &r->flags);
			clear_bit(WriteErrorSeen, &r->flags);

			अगर (mddev->pers->hot_add_disk(mddev, r)) अणु
				/* Failed to revive this device, try next */
				r->raid_disk = r->saved_raid_disk = -1;
				r->flags = flags;
			पूर्ण अन्यथा अणु
				clear_bit(In_sync, &r->flags);
				r->recovery_offset = 0;
				set_bit(i, (व्योम *) cleared_failed_devices);
				cleared = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/* If any failed devices could be cleared, update all sbs failed_devices bits */
	अगर (cleared) अणु
		uपूर्णांक64_t failed_devices[DISKS_ARRAY_ELEMS];

		rdev_क्रम_each(r, &rs->md) अणु
			अगर (test_bit(Journal, &r->flags))
				जारी;

			sb = page_address(r->sb_page);
			sb_retrieve_failed_devices(sb, failed_devices);

			क्रम (i = 0; i < DISKS_ARRAY_ELEMS; i++)
				failed_devices[i] &= ~cleared_failed_devices[i];

			sb_update_failed_devices(sb, failed_devices);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __load_dirty_region_biपंचांगap(काष्ठा raid_set *rs)
अणु
	पूर्णांक r = 0;

	/* Try loading the biपंचांगap unless "raid0", which करोes not have one */
	अगर (!rs_is_raid0(rs) &&
	    !test_and_set_bit(RT_FLAG_RS_BITMAP_LOADED, &rs->runसमय_flags)) अणु
		r = md_biपंचांगap_load(&rs->md);
		अगर (r)
			DMERR("Failed to load bitmap");
	पूर्ण

	वापस r;
पूर्ण

/* Enक्रमce updating all superblocks */
अटल व्योम rs_update_sbs(काष्ठा raid_set *rs)
अणु
	काष्ठा mddev *mddev = &rs->md;
	पूर्णांक ro = mddev->ro;

	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	mddev->ro = 0;
	md_update_sb(mddev, 1);
	mddev->ro = ro;
पूर्ण

/*
 * Reshape changes raid algorithm of @rs to new one within personality
 * (e.g. raid6_zr -> raid6_nc), changes stripe size, adds/हटाओs
 * disks from a raid set thus growing/shrinking it or resizes the set
 *
 * Call mddev_lock_noपूर्णांकr() beक्रमe!
 */
अटल पूर्णांक rs_start_reshape(काष्ठा raid_set *rs)
अणु
	पूर्णांक r;
	काष्ठा mddev *mddev = &rs->md;
	काष्ठा md_personality *pers = mddev->pers;

	/* Don't allow the sync thपढ़ो to work until the table माला_लो reloaded. */
	set_bit(MD_RECOVERY_WAIT, &mddev->recovery);

	r = rs_setup_reshape(rs);
	अगर (r)
		वापस r;

	/*
	 * Check any reshape स्थिरraपूर्णांकs enक्रमced by the personalility
	 *
	 * May as well alपढ़ोy kick the reshape off so that * pers->start_reshape() becomes optional.
	 */
	r = pers->check_reshape(mddev);
	अगर (r) अणु
		rs->ti->error = "pers->check_reshape() failed";
		वापस r;
	पूर्ण

	/*
	 * Personality may not provide start reshape method in which
	 * हाल check_reshape above has alपढ़ोy covered everything
	 */
	अगर (pers->start_reshape) अणु
		r = pers->start_reshape(mddev);
		अगर (r) अणु
			rs->ti->error = "pers->start_reshape() failed";
			वापस r;
		पूर्ण
	पूर्ण

	/*
	 * Now reshape got set up, update superblocks to
	 * reflect the fact so that a table reload will
	 * access proper superblock content in the ctr.
	 */
	rs_update_sbs(rs);

	वापस 0;
पूर्ण

अटल पूर्णांक raid_preresume(काष्ठा dm_target *ti)
अणु
	पूर्णांक r;
	काष्ठा raid_set *rs = ti->निजी;
	काष्ठा mddev *mddev = &rs->md;

	/* This is a resume after a suspend of the set -> it's alपढ़ोy started. */
	अगर (test_and_set_bit(RT_FLAG_RS_PRERESUMED, &rs->runसमय_flags))
		वापस 0;

	/*
	 * The superblocks need to be updated on disk अगर the
	 * array is new or new devices got added (thus zeroed
	 * out by userspace) or __load_dirty_region_biपंचांगap
	 * will overग_लिखो them in core with old data or fail.
	 */
	अगर (test_bit(RT_FLAG_UPDATE_SBS, &rs->runसमय_flags))
		rs_update_sbs(rs);

	/* Load the biपंचांगap from disk unless raid0 */
	r = __load_dirty_region_biपंचांगap(rs);
	अगर (r)
		वापस r;

	/* We are extending the raid set size, adjust mddev/md_rdev sizes and set capacity. */
	अगर (test_bit(RT_FLAG_RS_GROW, &rs->runसमय_flags)) अणु
		mddev->array_sectors = rs->array_sectors;
		mddev->dev_sectors = rs->dev_sectors;
		rs_set_rdev_sectors(rs);
		rs_set_capacity(rs);
	पूर्ण

	/* Resize biपंचांगap to adjust to changed region size (aka MD biपंचांगap chunksize) or grown device size */
        अगर (test_bit(RT_FLAG_RS_BITMAP_LOADED, &rs->runसमय_flags) && mddev->biपंचांगap &&
	    (test_bit(RT_FLAG_RS_GROW, &rs->runसमय_flags) ||
	     (rs->requested_biपंचांगap_chunk_sectors &&
	       mddev->biपंचांगap_info.chunksize != to_bytes(rs->requested_biपंचांगap_chunk_sectors)))) अणु
		पूर्णांक chunksize = to_bytes(rs->requested_biपंचांगap_chunk_sectors) ?: mddev->biपंचांगap_info.chunksize;

		r = md_biपंचांगap_resize(mddev->biपंचांगap, mddev->dev_sectors, chunksize, 0);
		अगर (r)
			DMERR("Failed to resize bitmap");
	पूर्ण

	/* Check क्रम any resize/reshape on @rs and adjust/initiate */
	/* Be prepared क्रम mddev_resume() in raid_resume() */
	set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
	अगर (mddev->recovery_cp && mddev->recovery_cp < MaxSector) अणु
		set_bit(MD_RECOVERY_REQUESTED, &mddev->recovery);
		mddev->resync_min = mddev->recovery_cp;
		अगर (test_bit(RT_FLAG_RS_GROW, &rs->runसमय_flags))
			mddev->resync_max_sectors = mddev->dev_sectors;
	पूर्ण

	/* Check क्रम any reshape request unless new raid set */
	अगर (test_bit(RT_FLAG_RESHAPE_RS, &rs->runसमय_flags)) अणु
		/* Initiate a reshape. */
		rs_set_rdev_sectors(rs);
		mddev_lock_noपूर्णांकr(mddev);
		r = rs_start_reshape(rs);
		mddev_unlock(mddev);
		अगर (r)
			DMWARN("Failed to check/start reshape, continuing without change");
		r = 0;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम raid_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा raid_set *rs = ti->निजी;
	काष्ठा mddev *mddev = &rs->md;

	अगर (test_and_set_bit(RT_FLAG_RS_RESUMED, &rs->runसमय_flags)) अणु
		/*
		 * A secondary resume जबतक the device is active.
		 * Take this opportunity to check whether any failed
		 * devices are reachable again.
		 */
		attempt_restore_of_faulty_devices(rs);
	पूर्ण

	अगर (test_and_clear_bit(RT_FLAG_RS_SUSPENDED, &rs->runसमय_flags)) अणु
		/* Only reduce raid set size beक्रमe running a disk removing reshape. */
		अगर (mddev->delta_disks < 0)
			rs_set_capacity(rs);

		mddev_lock_noपूर्णांकr(mddev);
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		mddev->ro = 0;
		mddev->in_sync = 0;
		mddev_resume(mddev);
		mddev_unlock(mddev);
	पूर्ण
पूर्ण

अटल काष्ठा target_type raid_target = अणु
	.name = "raid",
	.version = अणु1, 15, 1पूर्ण,
	.module = THIS_MODULE,
	.ctr = raid_ctr,
	.dtr = raid_dtr,
	.map = raid_map,
	.status = raid_status,
	.message = raid_message,
	.iterate_devices = raid_iterate_devices,
	.io_hपूर्णांकs = raid_io_hपूर्णांकs,
	.postsuspend = raid_postsuspend,
	.preresume = raid_preresume,
	.resume = raid_resume,
पूर्ण;

अटल पूर्णांक __init dm_raid_init(व्योम)
अणु
	DMINFO("Loading target version %u.%u.%u",
	       raid_target.version[0],
	       raid_target.version[1],
	       raid_target.version[2]);
	वापस dm_रेजिस्टर_target(&raid_target);
पूर्ण

अटल व्योम __निकास dm_raid_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&raid_target);
पूर्ण

module_init(dm_raid_init);
module_निकास(dm_raid_निकास);

module_param(devices_handle_discard_safely, bool, 0644);
MODULE_PARM_DESC(devices_handle_discard_safely,
		 "Set to Y if all devices in each array reliably return zeroes on reads from discarded regions");

MODULE_DESCRIPTION(DM_NAME " raid0/1/10/4/5/6 target");
MODULE_ALIAS("dm-raid0");
MODULE_ALIAS("dm-raid1");
MODULE_ALIAS("dm-raid10");
MODULE_ALIAS("dm-raid4");
MODULE_ALIAS("dm-raid5");
MODULE_ALIAS("dm-raid6");
MODULE_AUTHOR("Neil Brown <dm-devel@redhat.com>");
MODULE_AUTHOR("Heinz Mauelshagen <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
