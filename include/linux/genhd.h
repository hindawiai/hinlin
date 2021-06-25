<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_GENHD_H
#घोषणा _LINUX_GENHD_H

/*
 * 	genhd.h Copyright (C) 1992 Drew Eckhardt
 *	Generic hard disk header file by  
 * 		Drew Eckhardt
 *
 *		<drew@coloraकरो.edu>
 */

#समावेश <linux/types.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/uuid.h>
#समावेश <linux/blk_types.h>
#समावेश <यंत्र/local.h>

बाह्य स्थिर काष्ठा device_type disk_type;
बाह्य काष्ठा device_type part_type;
बाह्य काष्ठा class block_class;

#घोषणा DISK_MAX_PARTS			256
#घोषणा DISK_NAME_LEN			32

#समावेश <linux/major.h>
#समावेश <linux/device.h>
#समावेश <linux/smp.h>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/xarray.h>

#घोषणा PARTITION_META_INFO_VOLNAMELTH	64
/*
 * Enough क्रम the string representation of any kind of UUID plus शून्य.
 * EFI UUID is 36 अक्षरacters. MSDOS UUID is 11 अक्षरacters.
 */
#घोषणा PARTITION_META_INFO_UUIDLTH	(UUID_STRING_LEN + 1)

काष्ठा partition_meta_info अणु
	अक्षर uuid[PARTITION_META_INFO_UUIDLTH];
	u8 volname[PARTITION_META_INFO_VOLNAMELTH];
पूर्ण;

/**
 * DOC: genhd capability flags
 *
 * ``GENHD_FL_REMOVABLE`` (0x0001): indicates that the block device
 * gives access to removable media.
 * When set, the device reमुख्यs present even when media is not
 * inserted.
 * Must not be set क्रम devices which are हटाओd entirely when the
 * media is हटाओd.
 *
 * ``GENHD_FL_CD`` (0x0008): the block device is a CD-ROM-style
 * device.
 * Affects responses to the ``CDROM_GET_CAPABILITY`` ioctl.
 *
 * ``GENHD_FL_UP`` (0x0010): indicates that the block device is "up",
 * with a similar meaning to network पूर्णांकerfaces.
 *
 * ``GENHD_FL_SUPPRESS_PARTITION_INFO`` (0x0020): करोn't include
 * partition inक्रमmation in ``/proc/partitions`` or in the output of
 * prपूर्णांकk_all_partitions().
 * Used क्रम the null block device and some MMC devices.
 *
 * ``GENHD_FL_EXT_DEVT`` (0x0040): the driver supports extended
 * dynamic ``dev_t``, i.e. it wants extended device numbers
 * (``BLOCK_EXT_MAJOR``).
 * This affects the maximum number of partitions.
 *
 * ``GENHD_FL_NATIVE_CAPACITY`` (0x0080): based on inक्रमmation in the
 * partition table, the device's capacity has been extended to its
 * native capacity; i.e. the device has hidden capacity used by one
 * of the partitions (this is a flag used so that native capacity is
 * only ever unlocked once).
 *
 * ``GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE`` (0x0100): event polling is
 * blocked whenever a ग_लिखोr holds an exclusive lock.
 *
 * ``GENHD_FL_NO_PART_SCAN`` (0x0200): partition scanning is disabled.
 * Used क्रम loop devices in their शेष settings and some MMC
 * devices.
 *
 * ``GENHD_FL_HIDDEN`` (0x0400): the block device is hidden; it
 * करोesn't produce events, doesn't appear in sysfs, and doesn't have
 * an associated ``bdev``.
 * Implies ``GENHD_FL_SUPPRESS_PARTITION_INFO`` and
 * ``GENHD_FL_NO_PART_SCAN``.
 * Used क्रम multipath devices.
 */
#घोषणा GENHD_FL_REMOVABLE			0x0001
/* 2 is unused (used to be GENHD_FL_DRIVERFS) */
/* 4 is unused (used to be GENHD_FL_MEDIA_CHANGE_NOTIFY) */
#घोषणा GENHD_FL_CD				0x0008
#घोषणा GENHD_FL_UP				0x0010
#घोषणा GENHD_FL_SUPPRESS_PARTITION_INFO	0x0020
#घोषणा GENHD_FL_EXT_DEVT			0x0040
#घोषणा GENHD_FL_NATIVE_CAPACITY		0x0080
#घोषणा GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE	0x0100
#घोषणा GENHD_FL_NO_PART_SCAN			0x0200
#घोषणा GENHD_FL_HIDDEN				0x0400

क्रमागत अणु
	DISK_EVENT_MEDIA_CHANGE			= 1 << 0, /* media changed */
	DISK_EVENT_EJECT_REQUEST		= 1 << 1, /* eject requested */
पूर्ण;

क्रमागत अणु
	/* Poll even अगर events_poll_msecs is unset */
	DISK_EVENT_FLAG_POLL			= 1 << 0,
	/* Forward events to udev */
	DISK_EVENT_FLAG_UEVENT			= 1 << 1,
पूर्ण;

काष्ठा disk_events;
काष्ठा badblocks;

काष्ठा blk_पूर्णांकegrity अणु
	स्थिर काष्ठा blk_पूर्णांकegrity_profile	*profile;
	अचिन्हित अक्षर				flags;
	अचिन्हित अक्षर				tuple_size;
	अचिन्हित अक्षर				पूर्णांकerval_exp;
	अचिन्हित अक्षर				tag_size;
पूर्ण;

काष्ठा gendisk अणु
	/* major, first_minor and minors are input parameters only,
	 * करोn't use directly.  Use disk_devt() and disk_max_parts().
	 */
	पूर्णांक major;			/* major number of driver */
	पूर्णांक first_minor;
	पूर्णांक minors;                     /* maximum number of minors, =1 क्रम
                                         * disks that can't be partitioned. */

	अक्षर disk_name[DISK_NAME_LEN];	/* name of major driver */

	अचिन्हित लघु events;		/* supported events */
	अचिन्हित लघु event_flags;	/* flags related to event processing */

	काष्ठा xarray part_tbl;
	काष्ठा block_device *part0;

	स्थिर काष्ठा block_device_operations *fops;
	काष्ठा request_queue *queue;
	व्योम *निजी_data;

	पूर्णांक flags;
	अचिन्हित दीर्घ state;
#घोषणा GD_NEED_PART_SCAN		0
#घोषणा GD_READ_ONLY			1
	काष्ठा kobject *slave_dir;

	काष्ठा समयr_अक्रम_state *अक्रमom;
	atomic_t sync_io;		/* RAID */
	काष्ठा disk_events *ev;
#अगर_घोषित  CONFIG_BLK_DEV_INTEGRITY
	काष्ठा kobject पूर्णांकegrity_kobj;
#पूर्ण_अगर	/* CONFIG_BLK_DEV_INTEGRITY */
#अगर IS_ENABLED(CONFIG_CDROM)
	काष्ठा cdrom_device_info *cdi;
#पूर्ण_अगर
	पूर्णांक node_id;
	काष्ठा badblocks *bb;
	काष्ठा lockdep_map lockdep_map;
पूर्ण;

/*
 * The gendisk is refcounted by the part0 block_device, and the bd_device
 * therein is also used क्रम device model presentation in sysfs.
 */
#घोषणा dev_to_disk(device) \
	(dev_to_bdev(device)->bd_disk)
#घोषणा disk_to_dev(disk) \
	(&((disk)->part0->bd_device))

#अगर IS_REACHABLE(CONFIG_CDROM)
#घोषणा disk_to_cdi(disk)	((disk)->cdi)
#अन्यथा
#घोषणा disk_to_cdi(disk)	शून्य
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक disk_max_parts(काष्ठा gendisk *disk)
अणु
	अगर (disk->flags & GENHD_FL_EXT_DEVT)
		वापस DISK_MAX_PARTS;
	वापस disk->minors;
पूर्ण

अटल अंतरभूत bool disk_part_scan_enabled(काष्ठा gendisk *disk)
अणु
	वापस disk_max_parts(disk) > 1 &&
		!(disk->flags & GENHD_FL_NO_PART_SCAN);
पूर्ण

अटल अंतरभूत dev_t disk_devt(काष्ठा gendisk *disk)
अणु
	वापस MKDEV(disk->major, disk->first_minor);
पूर्ण

व्योम disk_uevent(काष्ठा gendisk *disk, क्रमागत kobject_action action);

/* block/genhd.c */
बाह्य व्योम device_add_disk(काष्ठा device *parent, काष्ठा gendisk *disk,
			    स्थिर काष्ठा attribute_group **groups);
अटल अंतरभूत व्योम add_disk(काष्ठा gendisk *disk)
अणु
	device_add_disk(शून्य, disk, शून्य);
पूर्ण
बाह्य व्योम device_add_disk_no_queue_reg(काष्ठा device *parent, काष्ठा gendisk *disk);
अटल अंतरभूत व्योम add_disk_no_queue_reg(काष्ठा gendisk *disk)
अणु
	device_add_disk_no_queue_reg(शून्य, disk);
पूर्ण

बाह्य व्योम del_gendisk(काष्ठा gendisk *gp);
बाह्य काष्ठा block_device *bdget_disk(काष्ठा gendisk *disk, पूर्णांक partno);

व्योम set_disk_ro(काष्ठा gendisk *disk, bool पढ़ो_only);

अटल अंतरभूत पूर्णांक get_disk_ro(काष्ठा gendisk *disk)
अणु
	वापस disk->part0->bd_पढ़ो_only ||
		test_bit(GD_READ_ONLY, &disk->state);
पूर्ण

बाह्य व्योम disk_block_events(काष्ठा gendisk *disk);
बाह्य व्योम disk_unblock_events(काष्ठा gendisk *disk);
बाह्य व्योम disk_flush_events(काष्ठा gendisk *disk, अचिन्हित पूर्णांक mask);
bool set_capacity_and_notअगरy(काष्ठा gendisk *disk, sector_t size);

/* drivers/अक्षर/अक्रमom.c */
बाह्य व्योम add_disk_अक्रमomness(काष्ठा gendisk *disk) __latent_entropy;
बाह्य व्योम अक्रम_initialize_disk(काष्ठा gendisk *disk);

अटल अंतरभूत sector_t get_start_sect(काष्ठा block_device *bdev)
अणु
	वापस bdev->bd_start_sect;
पूर्ण

अटल अंतरभूत sector_t bdev_nr_sectors(काष्ठा block_device *bdev)
अणु
	वापस i_size_पढ़ो(bdev->bd_inode) >> 9;
पूर्ण

अटल अंतरभूत sector_t get_capacity(काष्ठा gendisk *disk)
अणु
	वापस bdev_nr_sectors(disk->part0);
पूर्ण

पूर्णांक bdev_disk_changed(काष्ठा block_device *bdev, bool invalidate);
पूर्णांक blk_add_partitions(काष्ठा gendisk *disk, काष्ठा block_device *bdev);
व्योम blk_drop_partitions(काष्ठा gendisk *disk);

बाह्य काष्ठा gendisk *__alloc_disk_node(पूर्णांक minors, पूर्णांक node_id);
बाह्य व्योम put_disk(काष्ठा gendisk *disk);

#घोषणा alloc_disk_node(minors, node_id)				\
(अणु									\
	अटल काष्ठा lock_class_key __key;				\
	स्थिर अक्षर *__name;						\
	काष्ठा gendisk *__disk;						\
									\
	__name = "(gendisk_completion)"#minors"("#node_id")";		\
									\
	__disk = __alloc_disk_node(minors, node_id);			\
									\
	अगर (__disk)							\
		lockdep_init_map(&__disk->lockdep_map, __name, &__key, 0); \
									\
	__disk;								\
पूर्ण)

#घोषणा alloc_disk(minors) alloc_disk_node(minors, NUMA_NO_NODE)

पूर्णांक __रेजिस्टर_blkdev(अचिन्हित पूर्णांक major, स्थिर अक्षर *name,
		व्योम (*probe)(dev_t devt));
#घोषणा रेजिस्टर_blkdev(major, name) \
	__रेजिस्टर_blkdev(major, name, शून्य)
व्योम unरेजिस्टर_blkdev(अचिन्हित पूर्णांक major, स्थिर अक्षर *name);

bool bdev_check_media_change(काष्ठा block_device *bdev);
पूर्णांक __invalidate_device(काष्ठा block_device *bdev, bool समाप्त_dirty);
व्योम set_capacity(काष्ठा gendisk *disk, sector_t size);

/* क्रम drivers/अक्षर/raw.c: */
पूर्णांक blkdev_ioctl(काष्ठा block_device *, भ_शेषe_t, अचिन्हित, अचिन्हित दीर्घ);
दीर्घ compat_blkdev_ioctl(काष्ठा file *, अचिन्हित, अचिन्हित दीर्घ);

#अगर_घोषित CONFIG_SYSFS
पूर्णांक bd_link_disk_holder(काष्ठा block_device *bdev, काष्ठा gendisk *disk);
व्योम bd_unlink_disk_holder(काष्ठा block_device *bdev, काष्ठा gendisk *disk);
#अन्यथा
अटल अंतरभूत पूर्णांक bd_link_disk_holder(काष्ठा block_device *bdev,
				      काष्ठा gendisk *disk)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम bd_unlink_disk_holder(काष्ठा block_device *bdev,
					 काष्ठा gendisk *disk)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSFS */

dev_t blk_lookup_devt(स्थिर अक्षर *name, पूर्णांक partno);
व्योम blk_request_module(dev_t devt);
#अगर_घोषित CONFIG_BLOCK
व्योम prपूर्णांकk_all_partitions(व्योम);
#अन्यथा /* CONFIG_BLOCK */
अटल अंतरभूत व्योम prपूर्णांकk_all_partitions(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BLOCK */

#पूर्ण_अगर /* _LINUX_GENHD_H */
