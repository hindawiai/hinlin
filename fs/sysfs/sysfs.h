<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs/sysfs/sysfs.h - sysfs पूर्णांकernal header file
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007 Tejun Heo <teheo@suse.de>
 */

#अगर_अघोषित __SYSFS_INTERNAL_H
#घोषणा __SYSFS_INTERNAL_H

#समावेश <linux/sysfs.h>

/*
 * mount.c
 */
बाह्य काष्ठा kernfs_node *sysfs_root_kn;

/*
 * dir.c
 */
बाह्य spinlock_t sysfs_symlink_target_lock;

व्योम sysfs_warn_dup(काष्ठा kernfs_node *parent, स्थिर अक्षर *name);

/*
 * file.c
 */
पूर्णांक sysfs_add_file_mode_ns(काष्ठा kernfs_node *parent,
			   स्थिर काष्ठा attribute *attr, bool is_bin,
			   umode_t amode, kuid_t uid, kgid_t gid,
			   स्थिर व्योम *ns);

/*
 * symlink.c
 */
पूर्णांक sysfs_create_link_sd(काष्ठा kernfs_node *kn, काष्ठा kobject *target,
			 स्थिर अक्षर *name);

#पूर्ण_अगर	/* __SYSFS_INTERNAL_H */
