<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_VOLUMES_H
#घोषणा BTRFS_VOLUMES_H

#समावेश <linux/bपन.स>
#समावेश <linux/sort.h>
#समावेश <linux/btrfs.h>
#समावेश "async-thread.h"

#घोषणा BTRFS_MAX_DATA_CHUNK_SIZE	(10ULL * SZ_1G)

बाह्य काष्ठा mutex uuid_mutex;

#घोषणा BTRFS_STRIPE_LEN	SZ_64K

काष्ठा btrfs_io_geometry अणु
	/* reमुख्यing bytes beक्रमe crossing a stripe */
	u64 len;
	/* offset of logical address in chunk */
	u64 offset;
	/* length of single IO stripe */
	u64 stripe_len;
	/* number of stripe where address falls */
	u64 stripe_nr;
	/* offset of address in stripe */
	u64 stripe_offset;
	/* offset of raid56 stripe पूर्णांकo the chunk */
	u64 raid56_stripe_offset;
पूर्ण;

/*
 * Use sequence counter to get consistent device stat data on
 * 32-bit processors.
 */
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
#समावेश <linux/seqlock.h>
#घोषणा __BTRFS_NEED_DEVICE_DATA_ORDERED
#घोषणा btrfs_device_data_ordered_init(device)	\
	seqcount_init(&device->data_seqcount)
#अन्यथा
#घोषणा btrfs_device_data_ordered_init(device) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा BTRFS_DEV_STATE_WRITEABLE	(0)
#घोषणा BTRFS_DEV_STATE_IN_FS_METADATA	(1)
#घोषणा BTRFS_DEV_STATE_MISSING		(2)
#घोषणा BTRFS_DEV_STATE_REPLACE_TGT	(3)
#घोषणा BTRFS_DEV_STATE_FLUSH_SENT	(4)
#घोषणा BTRFS_DEV_STATE_NO_READA	(5)

काष्ठा btrfs_zoned_device_info;

काष्ठा btrfs_device अणु
	काष्ठा list_head dev_list; /* device_list_mutex */
	काष्ठा list_head dev_alloc_list; /* chunk mutex */
	काष्ठा list_head post_commit_list; /* chunk mutex */
	काष्ठा btrfs_fs_devices *fs_devices;
	काष्ठा btrfs_fs_info *fs_info;

	काष्ठा rcu_string __rcu *name;

	u64 generation;

	काष्ठा block_device *bdev;

	काष्ठा btrfs_zoned_device_info *zone_info;

	/* the mode sent to blkdev_get */
	भ_शेषe_t mode;

	अचिन्हित दीर्घ dev_state;
	blk_status_t last_flush_error;

#अगर_घोषित __BTRFS_NEED_DEVICE_DATA_ORDERED
	seqcount_t data_seqcount;
#पूर्ण_अगर

	/* the पूर्णांकernal btrfs device id */
	u64 devid;

	/* size of the device in memory */
	u64 total_bytes;

	/* size of the device on disk */
	u64 disk_total_bytes;

	/* bytes used */
	u64 bytes_used;

	/* optimal io alignment क्रम this device */
	u32 io_align;

	/* optimal io width क्रम this device */
	u32 io_width;
	/* type and info about this device */
	u64 type;

	/* minimal io size क्रम this device */
	u32 sector_size;

	/* physical drive uuid (or lvm uuid) */
	u8 uuid[BTRFS_UUID_SIZE];

	/*
	 * size of the device on the current transaction
	 *
	 * This variant is update when committing the transaction,
	 * and रक्षित by chunk mutex
	 */
	u64 commit_total_bytes;

	/* bytes used on the current transaction */
	u64 commit_bytes_used;

	/* क्रम sending करोwn flush barriers */
	काष्ठा bio *flush_bio;
	काष्ठा completion flush_रुको;

	/* per-device scrub inक्रमmation */
	काष्ठा scrub_ctx *scrub_ctx;

	/* पढ़ोahead state */
	atomic_t पढ़ोa_in_flight;
	u64 पढ़ोa_next;
	काष्ठा पढ़ोa_zone *पढ़ोa_curr_zone;
	काष्ठा radix_tree_root पढ़ोa_zones;
	काष्ठा radix_tree_root पढ़ोa_extents;

	/* disk I/O failure stats. For detailed description refer to
	 * क्रमागत btrfs_dev_stat_values in ioctl.h */
	पूर्णांक dev_stats_valid;

	/* Counter to record the change of device stats */
	atomic_t dev_stats_ccnt;
	atomic_t dev_stat_values[BTRFS_DEV_STAT_VALUES_MAX];

	काष्ठा extent_io_tree alloc_state;

	काष्ठा completion kobj_unरेजिस्टर;
	/* For sysfs/FSID/devinfo/devid/ */
	काष्ठा kobject devid_kobj;
पूर्ण;

/*
 * If we पढ़ो those variants at the context of their own lock, we needn't
 * use the following helpers, पढ़ोing them directly is safe.
 */
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
#घोषणा BTRFS_DEVICE_GETSET_FUNCS(name)					\
अटल अंतरभूत u64							\
btrfs_device_get_##name(स्थिर काष्ठा btrfs_device *dev)			\
अणु									\
	u64 size;							\
	अचिन्हित पूर्णांक seq;						\
									\
	करो अणु								\
		seq = पढ़ो_seqcount_begin(&dev->data_seqcount);		\
		size = dev->name;					\
	पूर्ण जबतक (पढ़ो_seqcount_retry(&dev->data_seqcount, seq));	\
	वापस size;							\
पूर्ण									\
									\
अटल अंतरभूत व्योम							\
btrfs_device_set_##name(काष्ठा btrfs_device *dev, u64 size)		\
अणु									\
	preempt_disable();						\
	ग_लिखो_seqcount_begin(&dev->data_seqcount);			\
	dev->name = size;						\
	ग_लिखो_seqcount_end(&dev->data_seqcount);			\
	preempt_enable();						\
पूर्ण
#या_अगर BITS_PER_LONG==32 && defined(CONFIG_PREEMPTION)
#घोषणा BTRFS_DEVICE_GETSET_FUNCS(name)					\
अटल अंतरभूत u64							\
btrfs_device_get_##name(स्थिर काष्ठा btrfs_device *dev)			\
अणु									\
	u64 size;							\
									\
	preempt_disable();						\
	size = dev->name;						\
	preempt_enable();						\
	वापस size;							\
पूर्ण									\
									\
अटल अंतरभूत व्योम							\
btrfs_device_set_##name(काष्ठा btrfs_device *dev, u64 size)		\
अणु									\
	preempt_disable();						\
	dev->name = size;						\
	preempt_enable();						\
पूर्ण
#अन्यथा
#घोषणा BTRFS_DEVICE_GETSET_FUNCS(name)					\
अटल अंतरभूत u64							\
btrfs_device_get_##name(स्थिर काष्ठा btrfs_device *dev)			\
अणु									\
	वापस dev->name;						\
पूर्ण									\
									\
अटल अंतरभूत व्योम							\
btrfs_device_set_##name(काष्ठा btrfs_device *dev, u64 size)		\
अणु									\
	dev->name = size;						\
पूर्ण
#पूर्ण_अगर

BTRFS_DEVICE_GETSET_FUNCS(total_bytes);
BTRFS_DEVICE_GETSET_FUNCS(disk_total_bytes);
BTRFS_DEVICE_GETSET_FUNCS(bytes_used);

क्रमागत btrfs_chunk_allocation_policy अणु
	BTRFS_CHUNK_ALLOC_REGULAR,
	BTRFS_CHUNK_ALLOC_ZONED,
पूर्ण;

/*
 * Read policies क्रम mirrored block group profiles, पढ़ो picks the stripe based
 * on these policies.
 */
क्रमागत btrfs_पढ़ो_policy अणु
	/* Use process PID to choose the stripe */
	BTRFS_READ_POLICY_PID,
	BTRFS_NR_READ_POLICY,
पूर्ण;

काष्ठा btrfs_fs_devices अणु
	u8 fsid[BTRFS_FSID_SIZE]; /* FS specअगरic uuid */
	u8 metadata_uuid[BTRFS_FSID_SIZE];
	bool fsid_change;
	काष्ठा list_head fs_list;

	u64 num_devices;
	u64 खोलो_devices;
	u64 rw_devices;
	u64 missing_devices;
	u64 total_rw_bytes;
	u64 total_devices;

	/* Highest generation number of seen devices */
	u64 latest_generation;

	काष्ठा block_device *latest_bdev;

	/* all of the devices in the FS, रक्षित by a mutex
	 * so we can safely walk it to ग_लिखो out the supers without
	 * worrying about add/हटाओ by the multi-device code.
	 * Scrubbing super can kick off supers writing by holding
	 * this mutex lock.
	 */
	काष्ठा mutex device_list_mutex;

	/* List of all devices, रक्षित by device_list_mutex */
	काष्ठा list_head devices;

	/*
	 * Devices which can satisfy space allocation. Protected by
	 * chunk_mutex
	 */
	काष्ठा list_head alloc_list;

	काष्ठा list_head seed_list;
	bool seeding;

	पूर्णांक खोलोed;

	/* set when we find or add a device that करोesn't have the
	 * nonrot flag set
	 */
	bool rotating;

	काष्ठा btrfs_fs_info *fs_info;
	/* sysfs kobjects */
	काष्ठा kobject fsid_kobj;
	काष्ठा kobject *devices_kobj;
	काष्ठा kobject *devinfo_kobj;
	काष्ठा completion kobj_unरेजिस्टर;

	क्रमागत btrfs_chunk_allocation_policy chunk_alloc_policy;

	/* Policy used to पढ़ो the mirrored stripes */
	क्रमागत btrfs_पढ़ो_policy पढ़ो_policy;
पूर्ण;

#घोषणा BTRFS_BIO_INLINE_CSUM_SIZE	64

#घोषणा BTRFS_MAX_DEVS(info) ((BTRFS_MAX_ITEM_SIZE(info)	\
			- माप(काष्ठा btrfs_chunk))		\
			/ माप(काष्ठा btrfs_stripe) + 1)

#घोषणा BTRFS_MAX_DEVS_SYS_CHUNK ((BTRFS_SYSTEM_CHUNK_ARRAY_SIZE	\
				- 2 * माप(काष्ठा btrfs_disk_key)	\
				- 2 * माप(काष्ठा btrfs_chunk))	\
				/ माप(काष्ठा btrfs_stripe) + 1)

/*
 * we need the mirror number and stripe index to be passed around
 * the call chain जबतक we are processing end_io (especially errors).
 * Really, what we need is a btrfs_bio काष्ठाure that has this info
 * and is properly sized with its stripe array, but we're not there
 * quite yet.  We have our own btrfs bioset, and all of the bios
 * we allocate are actually btrfs_io_bios.  We'll cram as much of
 * काष्ठा btrfs_bio as we can पूर्णांकo this over समय.
 */
काष्ठा btrfs_io_bio अणु
	अचिन्हित पूर्णांक mirror_num;
	काष्ठा btrfs_device *device;
	u64 logical;
	u8 *csum;
	u8 csum_अंतरभूत[BTRFS_BIO_INLINE_CSUM_SIZE];
	काष्ठा bvec_iter iter;
	/*
	 * This member must come last, bio_alloc_bioset will allocate enough
	 * bytes क्रम entire btrfs_io_bio but relies on bio being last.
	 */
	काष्ठा bio bio;
पूर्ण;

अटल अंतरभूत काष्ठा btrfs_io_bio *btrfs_io_bio(काष्ठा bio *bio)
अणु
	वापस container_of(bio, काष्ठा btrfs_io_bio, bio);
पूर्ण

अटल अंतरभूत व्योम btrfs_io_bio_मुक्त_csum(काष्ठा btrfs_io_bio *io_bio)
अणु
	अगर (io_bio->csum != io_bio->csum_अंतरभूत) अणु
		kमुक्त(io_bio->csum);
		io_bio->csum = शून्य;
	पूर्ण
पूर्ण

काष्ठा btrfs_bio_stripe अणु
	काष्ठा btrfs_device *dev;
	u64 physical;
	u64 length; /* only used क्रम discard mappings */
पूर्ण;

काष्ठा btrfs_bio अणु
	refcount_t refs;
	atomic_t stripes_pending;
	काष्ठा btrfs_fs_info *fs_info;
	u64 map_type; /* get from map_lookup->type */
	bio_end_io_t *end_io;
	काष्ठा bio *orig_bio;
	व्योम *निजी;
	atomic_t error;
	पूर्णांक max_errors;
	पूर्णांक num_stripes;
	पूर्णांक mirror_num;
	पूर्णांक num_tgtdevs;
	पूर्णांक *tgtdev_map;
	/*
	 * logical block numbers क्रम the start of each stripe
	 * The last one or two are p/q.  These are sorted,
	 * so raid_map[0] is the start of our full stripe
	 */
	u64 *raid_map;
	काष्ठा btrfs_bio_stripe stripes[];
पूर्ण;

काष्ठा btrfs_device_info अणु
	काष्ठा btrfs_device *dev;
	u64 dev_offset;
	u64 max_avail;
	u64 total_avail;
पूर्ण;

काष्ठा btrfs_raid_attr अणु
	u8 sub_stripes;		/* sub_stripes info क्रम map */
	u8 dev_stripes;		/* stripes per dev */
	u8 devs_max;		/* max devs to use */
	u8 devs_min;		/* min devs needed */
	u8 tolerated_failures;	/* max tolerated fail devs */
	u8 devs_increment;	/* ndevs has to be a multiple of this */
	u8 ncopies;		/* how many copies to data has */
	u8 nparity;		/* number of stripes worth of bytes to store
				 * parity inक्रमmation */
	u8 mindev_error;	/* error code अगर min devs requisite is unmet */
	स्थिर अक्षर raid_name[8]; /* name of the raid */
	u64 bg_flag;		/* block group flag of the raid */
पूर्ण;

बाह्य स्थिर काष्ठा btrfs_raid_attr btrfs_raid_array[BTRFS_NR_RAID_TYPES];

काष्ठा map_lookup अणु
	u64 type;
	पूर्णांक io_align;
	पूर्णांक io_width;
	u64 stripe_len;
	पूर्णांक num_stripes;
	पूर्णांक sub_stripes;
	पूर्णांक verअगरied_stripes; /* For mount समय dev extent verअगरication */
	काष्ठा btrfs_bio_stripe stripes[];
पूर्ण;

#घोषणा map_lookup_size(n) (माप(काष्ठा map_lookup) + \
			    (माप(काष्ठा btrfs_bio_stripe) * (n)))

काष्ठा btrfs_balance_args;
काष्ठा btrfs_balance_progress;
काष्ठा btrfs_balance_control अणु
	काष्ठा btrfs_balance_args data;
	काष्ठा btrfs_balance_args meta;
	काष्ठा btrfs_balance_args sys;

	u64 flags;

	काष्ठा btrfs_balance_progress stat;
पूर्ण;

क्रमागत btrfs_map_op अणु
	BTRFS_MAP_READ,
	BTRFS_MAP_WRITE,
	BTRFS_MAP_DISCARD,
	BTRFS_MAP_GET_READ_MIRRORS,
पूर्ण;

अटल अंतरभूत क्रमागत btrfs_map_op btrfs_op(काष्ठा bio *bio)
अणु
	चयन (bio_op(bio)) अणु
	हाल REQ_OP_DISCARD:
		वापस BTRFS_MAP_DISCARD;
	हाल REQ_OP_WRITE:
	हाल REQ_OP_ZONE_APPEND:
		वापस BTRFS_MAP_WRITE;
	शेष:
		WARN_ON_ONCE(1);
		fallthrough;
	हाल REQ_OP_READ:
		वापस BTRFS_MAP_READ;
	पूर्ण
पूर्ण

व्योम btrfs_get_bbio(काष्ठा btrfs_bio *bbio);
व्योम btrfs_put_bbio(काष्ठा btrfs_bio *bbio);
पूर्णांक btrfs_map_block(काष्ठा btrfs_fs_info *fs_info, क्रमागत btrfs_map_op op,
		    u64 logical, u64 *length,
		    काष्ठा btrfs_bio **bbio_ret, पूर्णांक mirror_num);
पूर्णांक btrfs_map_sblock(काष्ठा btrfs_fs_info *fs_info, क्रमागत btrfs_map_op op,
		     u64 logical, u64 *length,
		     काष्ठा btrfs_bio **bbio_ret);
पूर्णांक btrfs_get_io_geometry(काष्ठा btrfs_fs_info *fs_info, काष्ठा extent_map *map,
			  क्रमागत btrfs_map_op op, u64 logical, u64 len,
			  काष्ठा btrfs_io_geometry *io_geom);
पूर्णांक btrfs_पढ़ो_sys_array(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_पढ़ो_chunk_tree(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_alloc_chunk(काष्ठा btrfs_trans_handle *trans, u64 type);
व्योम btrfs_mapping_tree_मुक्त(काष्ठा extent_map_tree *tree);
blk_status_t btrfs_map_bio(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			   पूर्णांक mirror_num);
पूर्णांक btrfs_खोलो_devices(काष्ठा btrfs_fs_devices *fs_devices,
		       भ_शेषe_t flags, व्योम *holder);
काष्ठा btrfs_device *btrfs_scan_one_device(स्थिर अक्षर *path,
					   भ_शेषe_t flags, व्योम *holder);
पूर्णांक btrfs_क्रमget_devices(स्थिर अक्षर *path);
व्योम btrfs_बंद_devices(काष्ठा btrfs_fs_devices *fs_devices);
व्योम btrfs_मुक्त_extra_devids(काष्ठा btrfs_fs_devices *fs_devices);
व्योम btrfs_assign_next_active_device(काष्ठा btrfs_device *device,
				     काष्ठा btrfs_device *this_dev);
काष्ठा btrfs_device *btrfs_find_device_by_devspec(काष्ठा btrfs_fs_info *fs_info,
						  u64 devid,
						  स्थिर अक्षर *devpath);
काष्ठा btrfs_device *btrfs_alloc_device(काष्ठा btrfs_fs_info *fs_info,
					स्थिर u64 *devid,
					स्थिर u8 *uuid);
व्योम btrfs_मुक्त_device(काष्ठा btrfs_device *device);
पूर्णांक btrfs_rm_device(काष्ठा btrfs_fs_info *fs_info,
		    स्थिर अक्षर *device_path, u64 devid);
व्योम __निकास btrfs_cleanup_fs_uuids(व्योम);
पूर्णांक btrfs_num_copies(काष्ठा btrfs_fs_info *fs_info, u64 logical, u64 len);
पूर्णांक btrfs_grow_device(काष्ठा btrfs_trans_handle *trans,
		      काष्ठा btrfs_device *device, u64 new_size);
काष्ठा btrfs_device *btrfs_find_device(काष्ठा btrfs_fs_devices *fs_devices,
				       u64 devid, u8 *uuid, u8 *fsid);
पूर्णांक btrfs_shrink_device(काष्ठा btrfs_device *device, u64 new_size);
पूर्णांक btrfs_init_new_device(काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *path);
पूर्णांक btrfs_balance(काष्ठा btrfs_fs_info *fs_info,
		  काष्ठा btrfs_balance_control *bctl,
		  काष्ठा btrfs_ioctl_balance_args *bargs);
व्योम btrfs_describe_block_groups(u64 flags, अक्षर *buf, u32 size_buf);
पूर्णांक btrfs_resume_balance_async(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_recover_balance(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_छोड़ो_balance(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_relocate_chunk(काष्ठा btrfs_fs_info *fs_info, u64 chunk_offset);
पूर्णांक btrfs_cancel_balance(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_create_uuid_tree(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_uuid_scan_kthपढ़ो(व्योम *data);
पूर्णांक btrfs_chunk_पढ़ोonly(काष्ठा btrfs_fs_info *fs_info, u64 chunk_offset);
पूर्णांक find_मुक्त_dev_extent(काष्ठा btrfs_device *device, u64 num_bytes,
			 u64 *start, u64 *max_avail);
व्योम btrfs_dev_stat_inc_and_prपूर्णांक(काष्ठा btrfs_device *dev, पूर्णांक index);
पूर्णांक btrfs_get_dev_stats(काष्ठा btrfs_fs_info *fs_info,
			काष्ठा btrfs_ioctl_get_dev_stats *stats);
व्योम btrfs_init_devices_late(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_init_dev_stats(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_run_dev_stats(काष्ठा btrfs_trans_handle *trans);
व्योम btrfs_rm_dev_replace_हटाओ_srcdev(काष्ठा btrfs_device *srcdev);
व्योम btrfs_rm_dev_replace_मुक्त_srcdev(काष्ठा btrfs_device *srcdev);
व्योम btrfs_destroy_dev_replace_tgtdev(काष्ठा btrfs_device *tgtdev);
पूर्णांक btrfs_is_parity_mirror(काष्ठा btrfs_fs_info *fs_info,
			   u64 logical, u64 len);
अचिन्हित दीर्घ btrfs_full_stripe_len(काष्ठा btrfs_fs_info *fs_info,
				    u64 logical);
पूर्णांक btrfs_finish_chunk_alloc(काष्ठा btrfs_trans_handle *trans,
			     u64 chunk_offset, u64 chunk_size);
पूर्णांक btrfs_हटाओ_chunk(काष्ठा btrfs_trans_handle *trans, u64 chunk_offset);
काष्ठा extent_map *btrfs_get_chunk_map(काष्ठा btrfs_fs_info *fs_info,
				       u64 logical, u64 length);
व्योम btrfs_release_disk_super(काष्ठा btrfs_super_block *super);

अटल अंतरभूत व्योम btrfs_dev_stat_inc(काष्ठा btrfs_device *dev,
				      पूर्णांक index)
अणु
	atomic_inc(dev->dev_stat_values + index);
	/*
	 * This memory barrier orders stores updating statistics beक्रमe stores
	 * updating dev_stats_ccnt.
	 *
	 * It pairs with smp_rmb() in btrfs_run_dev_stats().
	 */
	smp_mb__beक्रमe_atomic();
	atomic_inc(&dev->dev_stats_ccnt);
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_dev_stat_पढ़ो(काष्ठा btrfs_device *dev,
				      पूर्णांक index)
अणु
	वापस atomic_पढ़ो(dev->dev_stat_values + index);
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_dev_stat_पढ़ो_and_reset(काष्ठा btrfs_device *dev,
						पूर्णांक index)
अणु
	पूर्णांक ret;

	ret = atomic_xchg(dev->dev_stat_values + index, 0);
	/*
	 * atomic_xchg implies a full memory barriers as per atomic_t.txt:
	 * - RMW operations that have a वापस value are fully ordered;
	 *
	 * This implicit memory barriers is paired with the smp_rmb in
	 * btrfs_run_dev_stats
	 */
	atomic_inc(&dev->dev_stats_ccnt);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम btrfs_dev_stat_set(काष्ठा btrfs_device *dev,
				      पूर्णांक index, अचिन्हित दीर्घ val)
अणु
	atomic_set(dev->dev_stat_values + index, val);
	/*
	 * This memory barrier orders stores updating statistics beक्रमe stores
	 * updating dev_stats_ccnt.
	 *
	 * It pairs with smp_rmb() in btrfs_run_dev_stats().
	 */
	smp_mb__beक्रमe_atomic();
	atomic_inc(&dev->dev_stats_ccnt);
पूर्ण

/*
 * Convert block group flags (BTRFS_BLOCK_GROUP_*) to btrfs_raid_types, which
 * can be used as index to access btrfs_raid_array[].
 */
अटल अंतरभूत क्रमागत btrfs_raid_types btrfs_bg_flags_to_raid_index(u64 flags)
अणु
	अगर (flags & BTRFS_BLOCK_GROUP_RAID10)
		वापस BTRFS_RAID_RAID10;
	अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_RAID1)
		वापस BTRFS_RAID_RAID1;
	अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_RAID1C3)
		वापस BTRFS_RAID_RAID1C3;
	अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_RAID1C4)
		वापस BTRFS_RAID_RAID1C4;
	अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_DUP)
		वापस BTRFS_RAID_DUP;
	अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_RAID0)
		वापस BTRFS_RAID_RAID0;
	अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_RAID5)
		वापस BTRFS_RAID_RAID5;
	अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_RAID6)
		वापस BTRFS_RAID_RAID6;

	वापस BTRFS_RAID_SINGLE; /* BTRFS_BLOCK_GROUP_SINGLE */
पूर्ण

व्योम btrfs_commit_device_sizes(काष्ठा btrfs_transaction *trans);

काष्ठा list_head * __attribute_स्थिर__ btrfs_get_fs_uuids(व्योम);
bool btrfs_check_rw_degradable(काष्ठा btrfs_fs_info *fs_info,
					काष्ठा btrfs_device *failing_dev);
व्योम btrfs_scratch_superblocks(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा block_device *bdev,
			       स्थिर अक्षर *device_path);

पूर्णांक btrfs_bg_type_to_factor(u64 flags);
स्थिर अक्षर *btrfs_bg_type_to_raid_name(u64 flags);
पूर्णांक btrfs_verअगरy_dev_extents(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_repair_one_zone(काष्ठा btrfs_fs_info *fs_info, u64 logical);

#पूर्ण_अगर
