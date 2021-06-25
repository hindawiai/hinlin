<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  पूर्णांकernal.h - declarations पूर्णांकernal to debugfs
 *
 *  Copyright (C) 2016 Nicolai Stange <nicstange@gmail.com>
 */

#अगर_अघोषित _DEBUGFS_INTERNAL_H_
#घोषणा _DEBUGFS_INTERNAL_H_

काष्ठा file_operations;

/* declared over in file.c */
बाह्य स्थिर काष्ठा file_operations debugfs_noop_file_operations;
बाह्य स्थिर काष्ठा file_operations debugfs_खोलो_proxy_file_operations;
बाह्य स्थिर काष्ठा file_operations debugfs_full_proxy_file_operations;

काष्ठा debugfs_fsdata अणु
	स्थिर काष्ठा file_operations *real_fops;
	refcount_t active_users;
	काष्ठा completion active_users_drained;
पूर्ण;

/*
 * A dentry's ->d_fsdata either poपूर्णांकs to the real fops or to a
 * dynamically allocated debugfs_fsdata instance.
 * In order to distinguish between these two हालs, a real fops
 * poपूर्णांकer माला_लो its lowest bit set.
 */
#घोषणा DEBUGFS_FSDATA_IS_REAL_FOPS_BIT BIT(0)

/* Access BITS */
#घोषणा DEBUGFS_ALLOW_API	BIT(0)
#घोषणा DEBUGFS_ALLOW_MOUNT	BIT(1)

#अगर_घोषित CONFIG_DEBUG_FS_ALLOW_ALL
#घोषणा DEFAULT_DEBUGFS_ALLOW_BITS (DEBUGFS_ALLOW_MOUNT | DEBUGFS_ALLOW_API)
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_FS_DISALLOW_MOUNT
#घोषणा DEFAULT_DEBUGFS_ALLOW_BITS (DEBUGFS_ALLOW_API)
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_FS_ALLOW_NONE
#घोषणा DEFAULT_DEBUGFS_ALLOW_BITS (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _DEBUGFS_INTERNAL_H_ */
