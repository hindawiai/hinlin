<शैली गुरु>
/*
 * Copyright (c) 1982, 1986 Regents of the University of Calअगरornia.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Robert Elz at The University of Melbourne.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#अगर_अघोषित _UAPI_LINUX_QUOTA_
#घोषणा _UAPI_LINUX_QUOTA_

#समावेश <linux/types.h>

#घोषणा __DQUOT_VERSION__	"dquot_6.6.0"

#घोषणा MAXQUOTAS 3
#घोषणा USRQUOTA  0		/* element used क्रम user quotas */
#घोषणा GRPQUOTA  1		/* element used क्रम group quotas */
#घोषणा PRJQUOTA  2		/* element used क्रम project quotas */

/*
 * Definitions क्रम the शेष names of the quotas files.
 */
#घोषणा INITQFNAMES अणु \
	"user",    /* USRQUOTA */ \
	"group",   /* GRPQUOTA */ \
	"project", /* PRJQUOTA */ \
	"undefined", \
पूर्ण;

/*
 * Command definitions क्रम the 'quotactl' प्रणाली call.
 * The commands are broken पूर्णांकo a मुख्य command defined below
 * and a subcommand that is used to convey the type of
 * quota that is being manipulated (see above).
 */
#घोषणा SUBCMDMASK  0x00ff
#घोषणा SUBCMDSHIFT 8
#घोषणा QCMD(cmd, type)  (((cmd) << SUBCMDSHIFT) | ((type) & SUBCMDMASK))

#घोषणा Q_SYNC     0x800001	/* sync disk copy of a fileप्रणालीs quotas */
#घोषणा Q_QUOTAON  0x800002	/* turn quotas on */
#घोषणा Q_QUOTAOFF 0x800003	/* turn quotas off */
#घोषणा Q_GETFMT   0x800004	/* get quota क्रमmat used on given fileप्रणाली */
#घोषणा Q_GETINFO  0x800005	/* get inक्रमmation about quota files */
#घोषणा Q_SETINFO  0x800006	/* set inक्रमmation about quota files */
#घोषणा Q_GETQUOTA 0x800007	/* get user quota काष्ठाure */
#घोषणा Q_SETQUOTA 0x800008	/* set user quota काष्ठाure */
#घोषणा Q_GETNEXTQUOTA 0x800009	/* get disk limits and usage >= ID */

/* Quota क्रमmat type IDs */
#घोषणा	QFMT_VFS_OLD 1
#घोषणा	QFMT_VFS_V0 2
#घोषणा QFMT_OCFS2 3
#घोषणा	QFMT_VFS_V1 4

/* Size of block in which space limits are passed through the quota
 * पूर्णांकerface */
#घोषणा QIF_DQBLKSIZE_BITS 10
#घोषणा QIF_DQBLKSIZE (1 << QIF_DQBLKSIZE_BITS)

/*
 * Quota काष्ठाure used क्रम communication with userspace via quotactl
 * Following flags are used to specअगरy which fields are valid
 */
क्रमागत अणु
	QIF_BLIMITS_B = 0,
	QIF_SPACE_B,
	QIF_ILIMITS_B,
	QIF_INODES_B,
	QIF_BTIME_B,
	QIF_ITIME_B,
पूर्ण;

#घोषणा QIF_BLIMITS	(1 << QIF_BLIMITS_B)
#घोषणा QIF_SPACE	(1 << QIF_SPACE_B)
#घोषणा QIF_ILIMITS	(1 << QIF_ILIMITS_B)
#घोषणा QIF_INODES	(1 << QIF_INODES_B)
#घोषणा QIF_BTIME	(1 << QIF_BTIME_B)
#घोषणा QIF_ITIME	(1 << QIF_ITIME_B)
#घोषणा QIF_LIMITS	(QIF_BLIMITS | QIF_ILIMITS)
#घोषणा QIF_USAGE	(QIF_SPACE | QIF_INODES)
#घोषणा QIF_TIMES	(QIF_BTIME | QIF_ITIME)
#घोषणा QIF_ALL		(QIF_LIMITS | QIF_USAGE | QIF_TIMES)

काष्ठा अगर_dqblk अणु
	__u64 dqb_bhardlimit;
	__u64 dqb_bsoftlimit;
	__u64 dqb_curspace;
	__u64 dqb_ihardlimit;
	__u64 dqb_isoftlimit;
	__u64 dqb_curinodes;
	__u64 dqb_bसमय;
	__u64 dqb_iसमय;
	__u32 dqb_valid;
पूर्ण;

काष्ठा अगर_nextdqblk अणु
	__u64 dqb_bhardlimit;
	__u64 dqb_bsoftlimit;
	__u64 dqb_curspace;
	__u64 dqb_ihardlimit;
	__u64 dqb_isoftlimit;
	__u64 dqb_curinodes;
	__u64 dqb_bसमय;
	__u64 dqb_iसमय;
	__u32 dqb_valid;
	__u32 dqb_id;
पूर्ण;

/*
 * Structure used क्रम setting quota inक्रमmation about file via quotactl
 * Following flags are used to specअगरy which fields are valid
 */
#घोषणा IIF_BGRACE	1
#घोषणा IIF_IGRACE	2
#घोषणा IIF_FLAGS	4
#घोषणा IIF_ALL		(IIF_BGRACE | IIF_IGRACE | IIF_FLAGS)

क्रमागत अणु
	DQF_ROOT_SQUASH_B = 0,
	DQF_SYS_खाता_B = 16,
	/* Kernel पूर्णांकernal flags invisible to userspace */
	DQF_PRIVATE
पूर्ण;

/* Root squash enabled (क्रम v1 quota क्रमmat) */
#घोषणा DQF_ROOT_SQUASH	(1 << DQF_ROOT_SQUASH_B)
/* Quota stored in a प्रणाली file */
#घोषणा DQF_SYS_खाता	(1 << DQF_SYS_खाता_B)

काष्ठा अगर_dqinfo अणु
	__u64 dqi_bgrace;
	__u64 dqi_igrace;
	__u32 dqi_flags;	/* DFQ_* */
	__u32 dqi_valid;
पूर्ण;

/*
 * Definitions क्रम quota netlink पूर्णांकerface
 */
#घोषणा QUOTA_NL_NOWARN 0
#घोषणा QUOTA_NL_IHARDWARN 1		/* Inode hardlimit reached */
#घोषणा QUOTA_NL_ISOFTLONGWARN 2 	/* Inode grace समय expired */
#घोषणा QUOTA_NL_ISOFTWARN 3		/* Inode softlimit reached */
#घोषणा QUOTA_NL_BHARDWARN 4		/* Block hardlimit reached */
#घोषणा QUOTA_NL_BSOFTLONGWARN 5	/* Block grace समय expired */
#घोषणा QUOTA_NL_BSOFTWARN 6		/* Block softlimit reached */
#घोषणा QUOTA_NL_IHARDBELOW 7		/* Usage got below inode hardlimit */
#घोषणा QUOTA_NL_ISOFTBELOW 8		/* Usage got below inode softlimit */
#घोषणा QUOTA_NL_BHARDBELOW 9		/* Usage got below block hardlimit */
#घोषणा QUOTA_NL_BSOFTBELOW 10		/* Usage got below block softlimit */

क्रमागत अणु
	QUOTA_NL_C_UNSPEC,
	QUOTA_NL_C_WARNING,
	__QUOTA_NL_C_MAX,
पूर्ण;
#घोषणा QUOTA_NL_C_MAX (__QUOTA_NL_C_MAX - 1)

क्रमागत अणु
	QUOTA_NL_A_UNSPEC,
	QUOTA_NL_A_QTYPE,
	QUOTA_NL_A_EXCESS_ID,
	QUOTA_NL_A_WARNING,
	QUOTA_NL_A_DEV_MAJOR,
	QUOTA_NL_A_DEV_MINOR,
	QUOTA_NL_A_CAUSED_ID,
	QUOTA_NL_A_PAD,
	__QUOTA_NL_A_MAX,
पूर्ण;
#घोषणा QUOTA_NL_A_MAX (__QUOTA_NL_A_MAX - 1)


#पूर्ण_अगर /* _UAPI_LINUX_QUOTA_ */
