<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compat.h>

काष्ठा compat_अगर_dqblk अणु
	compat_u64			dqb_bhardlimit;
	compat_u64			dqb_bsoftlimit;
	compat_u64			dqb_curspace;
	compat_u64			dqb_ihardlimit;
	compat_u64			dqb_isoftlimit;
	compat_u64			dqb_curinodes;
	compat_u64			dqb_bसमय;
	compat_u64			dqb_iसमय;
	compat_uपूर्णांक_t			dqb_valid;
पूर्ण;

काष्ठा compat_fs_qfilestat अणु
	compat_u64			dqb_bhardlimit;
	compat_u64			qfs_nblks;
	compat_uपूर्णांक_t			qfs_nextents;
पूर्ण;

काष्ठा compat_fs_quota_stat अणु
	__s8				qs_version;
	__u16				qs_flags;
	__s8				qs_pad;
	काष्ठा compat_fs_qfilestat	qs_uquota;
	काष्ठा compat_fs_qfilestat	qs_gquota;
	compat_uपूर्णांक_t			qs_incoredqs;
	compat_पूर्णांक_t			qs_bसमयlimit;
	compat_पूर्णांक_t			qs_iसमयlimit;
	compat_पूर्णांक_t			qs_rtbसमयlimit;
	__u16				qs_bwarnlimit;
	__u16				qs_iwarnlimit;
पूर्ण;
