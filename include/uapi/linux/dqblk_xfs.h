<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * Copyright (c) 1995-2001,2004 Silicon Graphics, Inc.  All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesset General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software Foundation,
 * Inc.,  51 Franklin St, Fअगरth Floor, Boston, MA  02110-1301  USA
 */
#अगर_अघोषित _LINUX_DQBLK_XFS_H
#घोषणा _LINUX_DQBLK_XFS_H

#समावेश <linux/types.h>

/*
 * Disk quota - quotactl(2) commands क्रम the XFS Quota Manager (XQM).
 */

#घोषणा XQM_CMD(x)	(('X'<<8)+(x))	/* note: क्रमms first QCMD argument */
#घोषणा XQM_COMMAND(x)	(((x) & (0xff<<8)) == ('X'<<8))	/* test अगर क्रम XFS */

#घोषणा XQM_USRQUOTA	0	/* प्रणाली call user quota type */
#घोषणा XQM_GRPQUOTA	1	/* प्रणाली call group quota type */
#घोषणा XQM_PRJQUOTA	2	/* प्रणाली call project quota type */
#घोषणा XQM_MAXQUOTAS	3

#घोषणा Q_XQUOTAON	XQM_CMD(1)	/* enable accounting/enक्रमcement */
#घोषणा Q_XQUOTAOFF	XQM_CMD(2)	/* disable accounting/enक्रमcement */
#घोषणा Q_XGETQUOTA	XQM_CMD(3)	/* get disk limits and usage */
#घोषणा Q_XSETQLIM	XQM_CMD(4)	/* set disk limits */
#घोषणा Q_XGETQSTAT	XQM_CMD(5)	/* get quota subप्रणाली status */
#घोषणा Q_XQUOTARM	XQM_CMD(6)	/* मुक्त disk space used by dquots */
#घोषणा Q_XQUOTASYNC	XQM_CMD(7)	/* delalloc flush, updates dquots */
#घोषणा Q_XGETQSTATV	XQM_CMD(8)	/* newer version of get quota */
#घोषणा Q_XGETNEXTQUOTA	XQM_CMD(9)	/* get disk limits and usage >= ID */

/*
 * fs_disk_quota काष्ठाure:
 *
 * This contains the current quota inक्रमmation regarding a user/proj/group.
 * It is 64-bit aligned, and all the blk units are in BBs (Basic Blocks) of
 * 512 bytes.
 */
#घोषणा FS_DQUOT_VERSION	1	/* fs_disk_quota.d_version */
प्रकार काष्ठा fs_disk_quota अणु
	__s8		d_version;	/* version of this काष्ठाure */
	__s8		d_flags;	/* FS_अणुUSER,PROJ,GROUPपूर्ण_QUOTA */
	__u16		d_fieldmask;	/* field specअगरier */
	__u32		d_id;		/* user, project, or group ID */
	__u64		d_blk_hardlimit;/* असलolute limit on disk blks */
	__u64		d_blk_softlimit;/* preferred limit on disk blks */
	__u64		d_ino_hardlimit;/* maximum # allocated inodes */
	__u64		d_ino_softlimit;/* preferred inode limit */
	__u64		d_bcount;	/* # disk blocks owned by the user */
	__u64		d_icount;	/* # inodes owned by the user */
	__s32		d_iसमयr;	/* Zero अगर within inode limits. If
					 * not, we refuse service at this समय
					 * (in seconds since Unix epoch) */
	__s32		d_bसमयr;	/* similar to above; क्रम disk blocks */
	__u16	  	d_iwarns;       /* # warnings issued wrt num inodes */
	__u16	  	d_bwarns;       /* # warnings issued wrt disk blocks */
	__s8		d_iसमयr_hi;	/* upper 8 bits of समयr values */
	__s8		d_bसमयr_hi;
	__s8		d_rtbसमयr_hi;
	__s8		d_padding2;	/* padding2 - क्रम future use */
	__u64		d_rtb_hardlimit;/* असलolute limit on realसमय blks */
	__u64		d_rtb_softlimit;/* preferred limit on RT disk blks */
	__u64		d_rtbcount;	/* # realसमय blocks owned */
	__s32		d_rtbसमयr;	/* similar to above; क्रम RT disk blks */
	__u16	  	d_rtbwarns;     /* # warnings issued wrt RT disk blks */
	__s16		d_padding3;	/* padding3 - क्रम future use */	
	अक्षर		d_padding4[8];	/* yet more padding */
पूर्ण fs_disk_quota_t;

/*
 * These fields are sent to Q_XSETQLIM to specअगरy fields that need to change.
 */
#घोषणा FS_DQ_ISOFT	(1<<0)
#घोषणा FS_DQ_IHARD	(1<<1)
#घोषणा FS_DQ_BSOFT	(1<<2)
#घोषणा FS_DQ_BHARD 	(1<<3)
#घोषणा FS_DQ_RTBSOFT	(1<<4)
#घोषणा FS_DQ_RTBHARD	(1<<5)
#घोषणा FS_DQ_LIMIT_MASK	(FS_DQ_ISOFT | FS_DQ_IHARD | FS_DQ_BSOFT | \
				 FS_DQ_BHARD | FS_DQ_RTBSOFT | FS_DQ_RTBHARD)
/*
 * These समयrs can only be set in super user's dquot. For others, समयrs are
 * स्वतःmatically started and stopped. Superusers समयr values set the limits
 * क्रम the rest.  In हाल these values are zero, the DQ_अणुF,Bपूर्णTIMELIMIT values
 * defined below are used. 
 * These values also apply only to the d_fieldmask field क्रम Q_XSETQLIM.
 */
#घोषणा FS_DQ_BTIMER	(1<<6)
#घोषणा FS_DQ_ITIMER	(1<<7)
#घोषणा FS_DQ_RTBTIMER 	(1<<8)
#घोषणा FS_DQ_TIMER_MASK	(FS_DQ_BTIMER | FS_DQ_ITIMER | FS_DQ_RTBTIMER)

/*
 * Warning counts are set in both super user's dquot and others. For others,
 * warnings are set/cleared by the administrators (or स्वतःmatically by going
 * below the soft limit).  Superusers warning values set the warning limits
 * क्रम the rest.  In हाल these values are zero, the DQ_अणुF,Bपूर्णWARNLIMIT values
 * defined below are used. 
 * These values also apply only to the d_fieldmask field क्रम Q_XSETQLIM.
 */
#घोषणा FS_DQ_BWARNS	(1<<9)
#घोषणा FS_DQ_IWARNS	(1<<10)
#घोषणा FS_DQ_RTBWARNS	(1<<11)
#घोषणा FS_DQ_WARNS_MASK	(FS_DQ_BWARNS | FS_DQ_IWARNS | FS_DQ_RTBWARNS)

/*
 * Accounting values.  These can only be set क्रम fileप्रणाली with
 * non-transactional quotas that require quotacheck(8) in userspace.
 */
#घोषणा FS_DQ_BCOUNT		(1<<12)
#घोषणा FS_DQ_ICOUNT		(1<<13)
#घोषणा FS_DQ_RTBCOUNT		(1<<14)
#घोषणा FS_DQ_ACCT_MASK		(FS_DQ_BCOUNT | FS_DQ_ICOUNT | FS_DQ_RTBCOUNT)

/*
 * Quota expiration बारtamps are 40-bit चिन्हित पूर्णांकegers, with the upper 8
 * bits encoded in the _hi fields.
 */
#घोषणा FS_DQ_BIGTIME		(1<<15)

/*
 * Various flags related to quotactl(2).
 */
#घोषणा FS_QUOTA_UDQ_ACCT	(1<<0)  /* user quota accounting */
#घोषणा FS_QUOTA_UDQ_ENFD	(1<<1)  /* user quota limits enक्रमcement */
#घोषणा FS_QUOTA_GDQ_ACCT	(1<<2)  /* group quota accounting */
#घोषणा FS_QUOTA_GDQ_ENFD	(1<<3)  /* group quota limits enक्रमcement */
#घोषणा FS_QUOTA_PDQ_ACCT	(1<<4)  /* project quota accounting */
#घोषणा FS_QUOTA_PDQ_ENFD	(1<<5)  /* project quota limits enक्रमcement */

#घोषणा FS_USER_QUOTA		(1<<0)	/* user quota type */
#घोषणा FS_PROJ_QUOTA		(1<<1)	/* project quota type */
#घोषणा FS_GROUP_QUOTA		(1<<2)	/* group quota type */

/*
 * fs_quota_stat is the काष्ठा वापसed in Q_XGETQSTAT क्रम a given file प्रणाली.
 * Provides a centralized way to get meta inक्रमmation about the quota subप्रणाली.
 * eg. space taken up क्रम user and group quotas, number of dquots currently
 * incore.
 */
#घोषणा FS_QSTAT_VERSION	1	/* fs_quota_stat.qs_version */

/*
 * Some basic inक्रमmation about 'quota files'.
 */
प्रकार काष्ठा fs_qfilestat अणु
	__u64		qfs_ino;	/* inode number */
	__u64		qfs_nblks;	/* number of BBs 512-byte-blks */
	__u32		qfs_nextents;	/* number of extents */
पूर्ण fs_qfilestat_t;

प्रकार काष्ठा fs_quota_stat अणु
	__s8		qs_version;	/* version number क्रम future changes */
	__u16		qs_flags;	/* FS_QUOTA_अणुU,P,Gपूर्णDQ_अणुACCT,ENFDपूर्ण */
	__s8		qs_pad;		/* unused */
	fs_qfilestat_t	qs_uquota;	/* user quota storage inक्रमmation */
	fs_qfilestat_t	qs_gquota;	/* group quota storage inक्रमmation */
	__u32		qs_incoredqs;	/* number of dquots incore */
	__s32		qs_bसमयlimit;  /* limit क्रम blks समयr */	
	__s32		qs_iसमयlimit;  /* limit क्रम inodes समयr */	
	__s32		qs_rtbसमयlimit;/* limit क्रम rt blks समयr */	
	__u16		qs_bwarnlimit;	/* limit क्रम num warnings */
	__u16		qs_iwarnlimit;	/* limit क्रम num warnings */
पूर्ण fs_quota_stat_t;

/*
 * fs_quota_statv is used by Q_XGETQSTATV क्रम a given file प्रणाली. It provides
 * a centralized way to get meta inक्रमmation about the quota subप्रणाली. eg.
 * space taken up क्रम user, group, and project quotas, number of dquots
 * currently incore.
 *
 * This version has proper versioning support with appropriate padding क्रम
 * future expansions, and ability to expand क्रम future without creating any
 * backward compatibility issues.
 *
 * Q_XGETQSTATV uses the passed in value of the requested version via
 * fs_quota_statv.qs_version to determine the वापस data layout of
 * fs_quota_statv.  The kernel will fill the data fields relevant to that
 * version.
 *
 * If kernel करोes not support user space caller specअगरied version, EINVAL will
 * be वापसed. User space caller can then reduce the version number and retry
 * the same command.
 */
#घोषणा FS_QSTATV_VERSION1	1	/* fs_quota_statv.qs_version */
/*
 * Some basic inक्रमmation about 'quota files' क्रम Q_XGETQSTATV command
 */
काष्ठा fs_qfilestatv अणु
	__u64		qfs_ino;	/* inode number */
	__u64		qfs_nblks;	/* number of BBs 512-byte-blks */
	__u32		qfs_nextents;	/* number of extents */
	__u32		qfs_pad;	/* pad क्रम 8-byte alignment */
पूर्ण;

काष्ठा fs_quota_statv अणु
	__s8			qs_version;	/* version क्रम future changes */
	__u8			qs_pad1;	/* pad क्रम 16bit alignment */
	__u16			qs_flags;	/* FS_QUOTA_.* flags */
	__u32			qs_incoredqs;	/* number of dquots incore */
	काष्ठा fs_qfilestatv	qs_uquota;	/* user quota inक्रमmation */
	काष्ठा fs_qfilestatv	qs_gquota;	/* group quota inक्रमmation */
	काष्ठा fs_qfilestatv	qs_pquota;	/* project quota inक्रमmation */
	__s32			qs_bसमयlimit;  /* limit क्रम blks समयr */
	__s32			qs_iसमयlimit;  /* limit क्रम inodes समयr */
	__s32			qs_rtbसमयlimit;/* limit क्रम rt blks समयr */
	__u16			qs_bwarnlimit;	/* limit क्रम num warnings */
	__u16			qs_iwarnlimit;	/* limit क्रम num warnings */
	__u16			qs_rtbwarnlimit;/* limit क्रम rt blks warnings */
	__u16			qs_pad3;
	__u32			qs_pad4;
	__u64			qs_pad2[7];	/* क्रम future proofing */
पूर्ण;

#पूर्ण_अगर	/* _LINUX_DQBLK_XFS_H */
