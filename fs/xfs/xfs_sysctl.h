<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2001-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_SYSCTL_H__
#घोषणा __XFS_SYSCTL_H__

#समावेश <linux/sysctl.h>

/*
 * Tunable xfs parameters
 */

प्रकार काष्ठा xfs_sysctl_val अणु
	पूर्णांक min;
	पूर्णांक val;
	पूर्णांक max;
पूर्ण xfs_sysctl_val_t;

प्रकार काष्ठा xfs_param अणु
	xfs_sysctl_val_t sgid_inherit;	/* Inherit S_ISGID अगर process' GID is
					 * not a member of parent dir GID. */
	xfs_sysctl_val_t symlink_mode;	/* Link creat mode affected by umask */
	xfs_sysctl_val_t panic_mask;	/* biपंचांगask to cause panic on errors. */
	xfs_sysctl_val_t error_level;	/* Degree of reporting क्रम problems  */
	xfs_sysctl_val_t syncd_समयr;	/* Interval between xfssyncd wakeups */
	xfs_sysctl_val_t stats_clear;	/* Reset all XFS statistics to zero. */
	xfs_sysctl_val_t inherit_sync;	/* Inherit the "sync" inode flag. */
	xfs_sysctl_val_t inherit_nodump;/* Inherit the "nodump" inode flag. */
	xfs_sysctl_val_t inherit_noatim;/* Inherit the "noatime" inode flag. */
	xfs_sysctl_val_t xfs_buf_समयr;	/* Interval between xfsbufd wakeups. */
	xfs_sysctl_val_t xfs_buf_age;	/* Metadata buffer age beक्रमe flush. */
	xfs_sysctl_val_t inherit_nosym;	/* Inherit the "nosymlinks" flag. */
	xfs_sysctl_val_t rotorstep;	/* inode32 AG rotoring control knob */
	xfs_sysctl_val_t inherit_nodfrg;/* Inherit the "nodefrag" inode flag. */
	xfs_sysctl_val_t fstrm_समयr;	/* Filestream dir-AG assoc'n समयout. */
	xfs_sysctl_val_t blockgc_समयr;	/* Interval between blockgc scans */
पूर्ण xfs_param_t;

/*
 * xfs_error_level:
 *
 * How much error reporting will be करोne when पूर्णांकernal problems are
 * encountered.  These problems normally वापस an EFSCORRUPTED to their
 * caller, with no other inक्रमmation reported.
 *
 * 0	No error reports
 * 1	Report EFSCORRUPTED errors that will cause a fileप्रणाली shutकरोwn
 * 5	Report all EFSCORRUPTED errors (all of the above errors, plus any
 *	additional errors that are known to not cause shutकरोwns)
 *
 * xfs_panic_mask bit 0x8 turns the error reports पूर्णांकo panics
 */

क्रमागत अणु
	/* XFS_REFCACHE_SIZE = 1 */
	/* XFS_REFCACHE_PURGE = 2 */
	/* XFS_RESTRICT_CHOWN = 3 */
	XFS_SGID_INHERIT = 4,
	XFS_SYMLINK_MODE = 5,
	XFS_PANIC_MASK = 6,
	XFS_ERRLEVEL = 7,
	XFS_SYNCD_TIMER = 8,
	/* XFS_PROBE_DMAPI = 9 */
	/* XFS_PROBE_IOOPS = 10 */
	/* XFS_PROBE_QUOTA = 11 */
	XFS_STATS_CLEAR = 12,
	XFS_INHERIT_SYNC = 13,
	XFS_INHERIT_NODUMP = 14,
	XFS_INHERIT_NOATIME = 15,
	XFS_BUF_TIMER = 16,
	XFS_BUF_AGE = 17,
	/* XFS_IO_BYPASS = 18 */
	XFS_INHERIT_NOSYM = 19,
	XFS_ROTORSTEP = 20,
	XFS_INHERIT_NODFRG = 21,
	XFS_खाताSTREAM_TIMER = 22,
पूर्ण;

बाह्य xfs_param_t	xfs_params;

काष्ठा xfs_globals अणु
#अगर_घोषित DEBUG
	पूर्णांक	pwork_thपढ़ोs;		/* parallel workqueue thपढ़ोs */
#पूर्ण_अगर
	पूर्णांक	log_recovery_delay;	/* log recovery delay (secs) */
	पूर्णांक	mount_delay;		/* mount setup delay (secs) */
	bool	bug_on_निश्चित;		/* BUG() the kernel on निश्चित failure */
	bool	always_cow;		/* use COW विभाजन क्रम all overग_लिखोs */
पूर्ण;
बाह्य काष्ठा xfs_globals	xfs_globals;

#अगर_घोषित CONFIG_SYSCTL
बाह्य पूर्णांक xfs_sysctl_रेजिस्टर(व्योम);
बाह्य व्योम xfs_sysctl_unरेजिस्टर(व्योम);
#अन्यथा
# define xfs_sysctl_रेजिस्टर()		(0)
# define xfs_sysctl_unरेजिस्टर()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_SYSCTL */

#पूर्ण_अगर /* __XFS_SYSCTL_H__ */
