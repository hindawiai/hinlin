<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_SUPER_H__
#घोषणा __XFS_SUPER_H__

#समावेश <linux/exportfs.h>

#अगर_घोषित CONFIG_XFS_QUOTA
बाह्य पूर्णांक xfs_qm_init(व्योम);
बाह्य व्योम xfs_qm_निकास(व्योम);
# define XFS_QUOTA_STRING	"quota, "
#अन्यथा
# define xfs_qm_init()	(0)
# define xfs_qm_निकास()	करो अणु पूर्ण जबतक (0)
# define XFS_QUOTA_STRING
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFS_POSIX_ACL
# define XFS_ACL_STRING		"ACLs, "
# define set_posix_acl_flag(sb)	((sb)->s_flags |= SB_POSIXACL)
#अन्यथा
# define XFS_ACL_STRING
# define set_posix_acl_flag(sb)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा XFS_SECURITY_STRING	"security attributes, "

#अगर_घोषित CONFIG_XFS_RT
# define XFS_REALTIME_STRING	"realtime, "
#अन्यथा
# define XFS_REALTIME_STRING
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFS_ONLINE_SCRUB
# define XFS_SCRUB_STRING	"scrub, "
#अन्यथा
# define XFS_SCRUB_STRING
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFS_ONLINE_REPAIR
# define XFS_REPAIR_STRING	"repair, "
#अन्यथा
# define XFS_REPAIR_STRING
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFS_WARN
# define XFS_WARN_STRING	"verbose warnings, "
#अन्यथा
# define XFS_WARN_STRING
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFS_ASSERT_FATAL
# define XFS_ASSERT_FATAL_STRING	"fatal assert, "
#अन्यथा
# define XFS_ASSERT_FATAL_STRING
#पूर्ण_अगर

#अगर_घोषित DEBUG
# define XFS_DBG_STRING		"debug"
#अन्यथा
# define XFS_DBG_STRING		"no debug"
#पूर्ण_अगर

#घोषणा XFS_VERSION_STRING	"SGI XFS"
#घोषणा XFS_BUILD_OPTIONS	XFS_ACL_STRING \
				XFS_SECURITY_STRING \
				XFS_REALTIME_STRING \
				XFS_SCRUB_STRING \
				XFS_REPAIR_STRING \
				XFS_WARN_STRING \
				XFS_QUOTA_STRING \
				XFS_ASSERT_FATAL_STRING \
				XFS_DBG_STRING /* DBG must be last */

#अगर_घोषित DEBUG
# define XFS_WQFLAGS(wqflags)	(WQ_SYSFS | (wqflags))
#अन्यथा
# define XFS_WQFLAGS(wqflags)	(wqflags)
#पूर्ण_अगर

काष्ठा xfs_inode;
काष्ठा xfs_mount;
काष्ठा xfs_buftarg;
काष्ठा block_device;

बाह्य व्योम xfs_flush_inodes(काष्ठा xfs_mount *mp);
बाह्य व्योम xfs_blkdev_issue_flush(काष्ठा xfs_buftarg *);
बाह्य xfs_agnumber_t xfs_set_inode_alloc(काष्ठा xfs_mount *,
					   xfs_agnumber_t agcount);

बाह्य स्थिर काष्ठा export_operations xfs_export_operations;
बाह्य स्थिर काष्ठा xattr_handler *xfs_xattr_handlers[];
बाह्य स्थिर काष्ठा quotactl_ops xfs_quotactl_operations;

बाह्य व्योम xfs_reinit_percpu_counters(काष्ठा xfs_mount *mp);

बाह्य काष्ठा workqueue_काष्ठा *xfs_discard_wq;

#घोषणा XFS_M(sb)		((काष्ठा xfs_mount *)((sb)->s_fs_info))

#पूर्ण_अगर	/* __XFS_SUPER_H__ */
