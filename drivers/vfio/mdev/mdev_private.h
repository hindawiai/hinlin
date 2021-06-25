<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Mediated device पूर्णांकernal definitions
 *
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *     Author: Neo Jia <cjia@nvidia.com>
 *             Kirti Wankhede <kwankhede@nvidia.com>
 */

#अगर_अघोषित MDEV_PRIVATE_H
#घोषणा MDEV_PRIVATE_H

पूर्णांक  mdev_bus_रेजिस्टर(व्योम);
व्योम mdev_bus_unरेजिस्टर(व्योम);

काष्ठा mdev_parent अणु
	काष्ठा device *dev;
	स्थिर काष्ठा mdev_parent_ops *ops;
	काष्ठा kref ref;
	काष्ठा list_head next;
	काष्ठा kset *mdev_types_kset;
	काष्ठा list_head type_list;
	/* Synchronize device creation/removal with parent unregistration */
	काष्ठा rw_semaphore unreg_sem;
पूर्ण;

काष्ठा mdev_type अणु
	काष्ठा kobject kobj;
	काष्ठा kobject *devices_kobj;
	काष्ठा mdev_parent *parent;
	काष्ठा list_head next;
	अचिन्हित पूर्णांक type_group_id;
पूर्ण;

#घोषणा to_mdev_type_attr(_attr)	\
	container_of(_attr, काष्ठा mdev_type_attribute, attr)
#घोषणा to_mdev_type(_kobj)		\
	container_of(_kobj, काष्ठा mdev_type, kobj)

पूर्णांक  parent_create_sysfs_files(काष्ठा mdev_parent *parent);
व्योम parent_हटाओ_sysfs_files(काष्ठा mdev_parent *parent);

पूर्णांक  mdev_create_sysfs_files(काष्ठा mdev_device *mdev);
व्योम mdev_हटाओ_sysfs_files(काष्ठा mdev_device *mdev);

पूर्णांक mdev_device_create(काष्ठा mdev_type *kobj, स्थिर guid_t *uuid);
पूर्णांक  mdev_device_हटाओ(काष्ठा mdev_device *dev);

व्योम mdev_release_parent(काष्ठा kref *kref);

अटल अंतरभूत व्योम mdev_get_parent(काष्ठा mdev_parent *parent)
अणु
	kref_get(&parent->ref);
पूर्ण

अटल अंतरभूत व्योम mdev_put_parent(काष्ठा mdev_parent *parent)
अणु
	kref_put(&parent->ref, mdev_release_parent);
पूर्ण

#पूर्ण_अगर /* MDEV_PRIVATE_H */
