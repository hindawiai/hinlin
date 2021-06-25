<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * sysfs.h - sysfs support declarations.
 *
 * Copyright (C) 2005-2014 Nippon Telegraph and Telephone Corporation.
 * Copyright (C) 2014 HGST, Inc., a Western Digital Company.
 *
 * Written by Vyacheslav Dubeyko <Vyacheslav.Dubeyko@hgst.com>
 */

#अगर_अघोषित _NILFS_SYSFS_H
#घोषणा _NILFS_SYSFS_H

#समावेश <linux/sysfs.h>

#घोषणा NILFS_ROOT_GROUP_NAME	"nilfs2"

/*
 * काष्ठा nilfs_sysfs_dev_subgroups - device subgroup kernel objects
 * @sg_superblock_kobj: /sys/fs/<nilfs>/<device>/superblock
 * @sg_superblock_kobj_unरेजिस्टर: completion state
 * @sg_segctor_kobj: /sys/fs/<nilfs>/<device>/segctor
 * @sg_segctor_kobj_unरेजिस्टर: completion state
 * @sg_mounted_snapshots_kobj: /sys/fs/<nilfs>/<device>/mounted_snapshots
 * @sg_mounted_snapshots_kobj_unरेजिस्टर: completion state
 * @sg_checkpoपूर्णांकs_kobj: /sys/fs/<nilfs>/<device>/checkpoपूर्णांकs
 * @sg_checkpoपूर्णांकs_kobj_unरेजिस्टर: completion state
 * @sg_segments_kobj: /sys/fs/<nilfs>/<device>/segments
 * @sg_segments_kobj_unरेजिस्टर: completion state
 */
काष्ठा nilfs_sysfs_dev_subgroups अणु
	/* /sys/fs/<nilfs>/<device>/superblock */
	काष्ठा kobject sg_superblock_kobj;
	काष्ठा completion sg_superblock_kobj_unरेजिस्टर;

	/* /sys/fs/<nilfs>/<device>/segctor */
	काष्ठा kobject sg_segctor_kobj;
	काष्ठा completion sg_segctor_kobj_unरेजिस्टर;

	/* /sys/fs/<nilfs>/<device>/mounted_snapshots */
	काष्ठा kobject sg_mounted_snapshots_kobj;
	काष्ठा completion sg_mounted_snapshots_kobj_unरेजिस्टर;

	/* /sys/fs/<nilfs>/<device>/checkpoपूर्णांकs */
	काष्ठा kobject sg_checkpoपूर्णांकs_kobj;
	काष्ठा completion sg_checkpoपूर्णांकs_kobj_unरेजिस्टर;

	/* /sys/fs/<nilfs>/<device>/segments */
	काष्ठा kobject sg_segments_kobj;
	काष्ठा completion sg_segments_kobj_unरेजिस्टर;
पूर्ण;

#घोषणा NILFS_COMMON_ATTR_STRUCT(name) \
काष्ठा nilfs_##name##_attr अणु \
	काष्ठा attribute attr; \
	sमाप_प्रकार (*show)(काष्ठा kobject *, काष्ठा attribute *, \
			अक्षर *); \
	sमाप_प्रकार (*store)(काष्ठा kobject *, काष्ठा attribute *, \
			 स्थिर अक्षर *, माप_प्रकार); \
पूर्ण

NILFS_COMMON_ATTR_STRUCT(feature);

#घोषणा NILFS_DEV_ATTR_STRUCT(name) \
काष्ठा nilfs_##name##_attr अणु \
	काष्ठा attribute attr; \
	sमाप_प्रकार (*show)(काष्ठा nilfs_##name##_attr *, काष्ठा the_nilfs *, \
			अक्षर *); \
	sमाप_प्रकार (*store)(काष्ठा nilfs_##name##_attr *, काष्ठा the_nilfs *, \
			 स्थिर अक्षर *, माप_प्रकार); \
पूर्ण

NILFS_DEV_ATTR_STRUCT(dev);
NILFS_DEV_ATTR_STRUCT(segments);
NILFS_DEV_ATTR_STRUCT(mounted_snapshots);
NILFS_DEV_ATTR_STRUCT(checkpoपूर्णांकs);
NILFS_DEV_ATTR_STRUCT(superblock);
NILFS_DEV_ATTR_STRUCT(segctor);

#घोषणा NILFS_CP_ATTR_STRUCT(name) \
काष्ठा nilfs_##name##_attr अणु \
	काष्ठा attribute attr; \
	sमाप_प्रकार (*show)(काष्ठा nilfs_##name##_attr *, काष्ठा nilfs_root *, \
			अक्षर *); \
	sमाप_प्रकार (*store)(काष्ठा nilfs_##name##_attr *, काष्ठा nilfs_root *, \
			 स्थिर अक्षर *, माप_प्रकार); \
पूर्ण

NILFS_CP_ATTR_STRUCT(snapshot);

#घोषणा NILFS_ATTR(type, name, mode, show, store) \
	अटल काष्ठा nilfs_##type##_attr nilfs_##type##_attr_##name = \
		__ATTR(name, mode, show, store)

#घोषणा NILFS_INFO_ATTR(type, name) \
	NILFS_ATTR(type, name, 0444, शून्य, शून्य)
#घोषणा NILFS_RO_ATTR(type, name) \
	NILFS_ATTR(type, name, 0444, nilfs_##type##_##name##_show, शून्य)
#घोषणा NILFS_RW_ATTR(type, name) \
	NILFS_ATTR(type, name, 0644, \
		    nilfs_##type##_##name##_show, \
		    nilfs_##type##_##name##_store)

#घोषणा NILFS_FEATURE_INFO_ATTR(name) \
	NILFS_INFO_ATTR(feature, name)
#घोषणा NILFS_FEATURE_RO_ATTR(name) \
	NILFS_RO_ATTR(feature, name)
#घोषणा NILFS_FEATURE_RW_ATTR(name) \
	NILFS_RW_ATTR(feature, name)

#घोषणा NILFS_DEV_INFO_ATTR(name) \
	NILFS_INFO_ATTR(dev, name)
#घोषणा NILFS_DEV_RO_ATTR(name) \
	NILFS_RO_ATTR(dev, name)
#घोषणा NILFS_DEV_RW_ATTR(name) \
	NILFS_RW_ATTR(dev, name)

#घोषणा NILFS_SEGMENTS_RO_ATTR(name) \
	NILFS_RO_ATTR(segments, name)
#घोषणा NILFS_SEGMENTS_RW_ATTR(name) \
	NILFS_RW_ATTR(segs_info, name)

#घोषणा NILFS_MOUNTED_SNAPSHOTS_RO_ATTR(name) \
	NILFS_RO_ATTR(mounted_snapshots, name)

#घोषणा NILFS_CHECKPOINTS_RO_ATTR(name) \
	NILFS_RO_ATTR(checkpoपूर्णांकs, name)
#घोषणा NILFS_CHECKPOINTS_RW_ATTR(name) \
	NILFS_RW_ATTR(checkpoपूर्णांकs, name)

#घोषणा NILFS_SNAPSHOT_INFO_ATTR(name) \
	NILFS_INFO_ATTR(snapshot, name)
#घोषणा NILFS_SNAPSHOT_RO_ATTR(name) \
	NILFS_RO_ATTR(snapshot, name)
#घोषणा NILFS_SNAPSHOT_RW_ATTR(name) \
	NILFS_RW_ATTR(snapshot, name)

#घोषणा NILFS_SUPERBLOCK_RO_ATTR(name) \
	NILFS_RO_ATTR(superblock, name)
#घोषणा NILFS_SUPERBLOCK_RW_ATTR(name) \
	NILFS_RW_ATTR(superblock, name)

#घोषणा NILFS_SEGCTOR_INFO_ATTR(name) \
	NILFS_INFO_ATTR(segctor, name)
#घोषणा NILFS_SEGCTOR_RO_ATTR(name) \
	NILFS_RO_ATTR(segctor, name)
#घोषणा NILFS_SEGCTOR_RW_ATTR(name) \
	NILFS_RW_ATTR(segctor, name)

#घोषणा NILFS_FEATURE_ATTR_LIST(name) \
	(&nilfs_feature_attr_##name.attr)
#घोषणा NILFS_DEV_ATTR_LIST(name) \
	(&nilfs_dev_attr_##name.attr)
#घोषणा NILFS_SEGMENTS_ATTR_LIST(name) \
	(&nilfs_segments_attr_##name.attr)
#घोषणा NILFS_MOUNTED_SNAPSHOTS_ATTR_LIST(name) \
	(&nilfs_mounted_snapshots_attr_##name.attr)
#घोषणा NILFS_CHECKPOINTS_ATTR_LIST(name) \
	(&nilfs_checkpoपूर्णांकs_attr_##name.attr)
#घोषणा NILFS_SNAPSHOT_ATTR_LIST(name) \
	(&nilfs_snapshot_attr_##name.attr)
#घोषणा NILFS_SUPERBLOCK_ATTR_LIST(name) \
	(&nilfs_superblock_attr_##name.attr)
#घोषणा NILFS_SEGCTOR_ATTR_LIST(name) \
	(&nilfs_segctor_attr_##name.attr)

#पूर्ण_अगर /* _NILFS_SYSFS_H */
