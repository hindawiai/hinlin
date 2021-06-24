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
#अगर_अघोषित _LINUX_QUOTA_
#घोषणा _LINUX_QUOTA_

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/percpu_counter.h>

#समावेश <linux/dqblk_xfs.h>
#समावेश <linux/dqblk_v1.h>
#समावेश <linux/dqblk_v2.h>

#समावेश <linux/atomic.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/projid.h>
#समावेश <uapi/linux/quota.h>

#अघोषित USRQUOTA
#अघोषित GRPQUOTA
#अघोषित PRJQUOTA
क्रमागत quota_type अणु
	USRQUOTA = 0,		/* element used क्रम user quotas */
	GRPQUOTA = 1,		/* element used क्रम group quotas */
	PRJQUOTA = 2,		/* element used क्रम project quotas */
पूर्ण;

/* Masks क्रम quota types when used as a biपंचांगask */
#घोषणा QTYPE_MASK_USR (1 << USRQUOTA)
#घोषणा QTYPE_MASK_GRP (1 << GRPQUOTA)
#घोषणा QTYPE_MASK_PRJ (1 << PRJQUOTA)

प्रकार __kernel_uid32_t qid_t; /* Type in which we store ids in memory */
प्रकार दीर्घ दीर्घ qमाप_प्रकार;	/* Type in which we store sizes */

काष्ठा kqid अणु			/* Type in which we store the quota identअगरier */
	जोड़ अणु
		kuid_t uid;
		kgid_t gid;
		kprojid_t projid;
	पूर्ण;
	क्रमागत quota_type type;  /* USRQUOTA (uid) or GRPQUOTA (gid) or PRJQUOTA (projid) */
पूर्ण;

बाह्य bool qid_eq(काष्ठा kqid left, काष्ठा kqid right);
बाह्य bool qid_lt(काष्ठा kqid left, काष्ठा kqid right);
बाह्य qid_t from_kqid(काष्ठा user_namespace *to, काष्ठा kqid qid);
बाह्य qid_t from_kqid_munged(काष्ठा user_namespace *to, काष्ठा kqid qid);
बाह्य bool qid_valid(काष्ठा kqid qid);

/**
 *	make_kqid - Map a user-namespace, type, qid tuple पूर्णांकo a kqid.
 *	@from: User namespace that the qid is in
 *	@type: The type of quota
 *	@qid: Quota identअगरier
 *
 *	Maps a user-namespace, type qid tuple पूर्णांकo a kernel पूर्णांकernal
 *	kqid, and वापसs that kqid.
 *
 *	When there is no mapping defined क्रम the user-namespace, type,
 *	qid tuple an invalid kqid is वापसed.  Callers are expected to
 *	test क्रम and handle handle invalid kqids being वापसed.
 *	Invalid kqids may be tested क्रम using qid_valid().
 */
अटल अंतरभूत काष्ठा kqid make_kqid(काष्ठा user_namespace *from,
				    क्रमागत quota_type type, qid_t qid)
अणु
	काष्ठा kqid kqid;

	kqid.type = type;
	चयन (type) अणु
	हाल USRQUOTA:
		kqid.uid = make_kuid(from, qid);
		अवरोध;
	हाल GRPQUOTA:
		kqid.gid = make_kgid(from, qid);
		अवरोध;
	हाल PRJQUOTA:
		kqid.projid = make_kprojid(from, qid);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस kqid;
पूर्ण

/**
 *	make_kqid_invalid - Explicitly make an invalid kqid
 *	@type: The type of quota identअगरier
 *
 *	Returns an invalid kqid with the specअगरied type.
 */
अटल अंतरभूत काष्ठा kqid make_kqid_invalid(क्रमागत quota_type type)
अणु
	काष्ठा kqid kqid;

	kqid.type = type;
	चयन (type) अणु
	हाल USRQUOTA:
		kqid.uid = INVALID_UID;
		अवरोध;
	हाल GRPQUOTA:
		kqid.gid = INVALID_GID;
		अवरोध;
	हाल PRJQUOTA:
		kqid.projid = INVALID_PROJID;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस kqid;
पूर्ण

/**
 *	make_kqid_uid - Make a kqid from a kuid
 *	@uid: The kuid to make the quota identअगरier from
 */
अटल अंतरभूत काष्ठा kqid make_kqid_uid(kuid_t uid)
अणु
	काष्ठा kqid kqid;
	kqid.type = USRQUOTA;
	kqid.uid = uid;
	वापस kqid;
पूर्ण

/**
 *	make_kqid_gid - Make a kqid from a kgid
 *	@gid: The kgid to make the quota identअगरier from
 */
अटल अंतरभूत काष्ठा kqid make_kqid_gid(kgid_t gid)
अणु
	काष्ठा kqid kqid;
	kqid.type = GRPQUOTA;
	kqid.gid = gid;
	वापस kqid;
पूर्ण

/**
 *	make_kqid_projid - Make a kqid from a projid
 *	@projid: The kprojid to make the quota identअगरier from
 */
अटल अंतरभूत काष्ठा kqid make_kqid_projid(kprojid_t projid)
अणु
	काष्ठा kqid kqid;
	kqid.type = PRJQUOTA;
	kqid.projid = projid;
	वापस kqid;
पूर्ण

/**
 *	qid_has_mapping - Report अगर a qid maps पूर्णांकo a user namespace.
 *	@ns:  The user namespace to see अगर a value maps पूर्णांकo.
 *	@qid: The kernel पूर्णांकernal quota identअगरier to test.
 */
अटल अंतरभूत bool qid_has_mapping(काष्ठा user_namespace *ns, काष्ठा kqid qid)
अणु
	वापस from_kqid(ns, qid) != (qid_t) -1;
पूर्ण


बाह्य spinlock_t dq_data_lock;

/* Maximal numbers of ग_लिखोs क्रम quota operation (insert/delete/update)
 * (over VFS all क्रमmats) */
#घोषणा DQUOT_INIT_ALLOC max(V1_INIT_ALLOC, V2_INIT_ALLOC)
#घोषणा DQUOT_INIT_REWRITE max(V1_INIT_REWRITE, V2_INIT_REWRITE)
#घोषणा DQUOT_DEL_ALLOC max(V1_DEL_ALLOC, V2_DEL_ALLOC)
#घोषणा DQUOT_DEL_REWRITE max(V1_DEL_REWRITE, V2_DEL_REWRITE)

/*
 * Data क्रम one user/group kept in memory
 */
काष्ठा mem_dqblk अणु
	qमाप_प्रकार dqb_bhardlimit;	/* असलolute limit on disk blks alloc */
	qमाप_प्रकार dqb_bsoftlimit;	/* preferred limit on disk blks */
	qमाप_प्रकार dqb_curspace;	/* current used space */
	qमाप_प्रकार dqb_rsvspace;   /* current reserved space क्रम delalloc*/
	qमाप_प्रकार dqb_ihardlimit;	/* असलolute limit on allocated inodes */
	qमाप_प्रकार dqb_isoftlimit;	/* preferred inode limit */
	qमाप_प्रकार dqb_curinodes;	/* current # allocated inodes */
	समय64_t dqb_bसमय;	/* समय limit क्रम excessive disk use */
	समय64_t dqb_iसमय;	/* समय limit क्रम excessive inode use */
पूर्ण;

/*
 * Data क्रम one quotafile kept in memory
 */
काष्ठा quota_क्रमmat_type;

काष्ठा mem_dqinfo अणु
	काष्ठा quota_क्रमmat_type *dqi_क्रमmat;
	पूर्णांक dqi_fmt_id;		/* Id of the dqi_क्रमmat - used when turning
				 * quotas on after remount RW */
	काष्ठा list_head dqi_dirty_list;	/* List of dirty dquots [dq_list_lock] */
	अचिन्हित दीर्घ dqi_flags;	/* DFQ_ flags [dq_data_lock] */
	अचिन्हित पूर्णांक dqi_bgrace;	/* Space grace समय [dq_data_lock] */
	अचिन्हित पूर्णांक dqi_igrace;	/* Inode grace समय [dq_data_lock] */
	qमाप_प्रकार dqi_max_spc_limit;	/* Maximum space limit [अटल] */
	qमाप_प्रकार dqi_max_ino_limit;	/* Maximum inode limit [अटल] */
	व्योम *dqi_priv;
पूर्ण;

काष्ठा super_block;

/* Mask क्रम flags passed to userspace */
#घोषणा DQF_GETINFO_MASK (DQF_ROOT_SQUASH | DQF_SYS_खाता)
/* Mask क्रम flags modअगरiable from userspace */
#घोषणा DQF_SETINFO_MASK DQF_ROOT_SQUASH

क्रमागत अणु
	DQF_INFO_सूचीTY_B = DQF_PRIVATE,
पूर्ण;
#घोषणा DQF_INFO_सूचीTY (1 << DQF_INFO_सूचीTY_B)	/* Is info dirty? */

बाह्य व्योम mark_info_dirty(काष्ठा super_block *sb, पूर्णांक type);
अटल अंतरभूत पूर्णांक info_dirty(काष्ठा mem_dqinfo *info)
अणु
	वापस test_bit(DQF_INFO_सूचीTY_B, &info->dqi_flags);
पूर्ण

क्रमागत अणु
	DQST_LOOKUPS,
	DQST_DROPS,
	DQST_READS,
	DQST_WRITES,
	DQST_CACHE_HITS,
	DQST_ALLOC_DQUOTS,
	DQST_FREE_DQUOTS,
	DQST_SYNCS,
	_DQST_DQSTAT_LAST
पूर्ण;

काष्ठा dqstats अणु
	अचिन्हित दीर्घ stat[_DQST_DQSTAT_LAST];
	काष्ठा percpu_counter counter[_DQST_DQSTAT_LAST];
पूर्ण;

बाह्य काष्ठा dqstats dqstats;

अटल अंतरभूत व्योम dqstats_inc(अचिन्हित पूर्णांक type)
अणु
	percpu_counter_inc(&dqstats.counter[type]);
पूर्ण

अटल अंतरभूत व्योम dqstats_dec(अचिन्हित पूर्णांक type)
अणु
	percpu_counter_dec(&dqstats.counter[type]);
पूर्ण

#घोषणा DQ_MOD_B	0	/* dquot modअगरied since पढ़ो */
#घोषणा DQ_BLKS_B	1	/* uid/gid has been warned about blk limit */
#घोषणा DQ_INODES_B	2	/* uid/gid has been warned about inode limit */
#घोषणा DQ_FAKE_B	3	/* no limits only usage */
#घोषणा DQ_READ_B	4	/* dquot was पढ़ो पूर्णांकo memory */
#घोषणा DQ_ACTIVE_B	5	/* dquot is active (dquot_release not called) */
#घोषणा DQ_LASTSET_B	6	/* Following 6 bits (see QIF_) are reserved\
				 * क्रम the mask of entries set via SETQUOTA\
				 * quotactl. They are set under dq_data_lock\
				 * and the quota क्रमmat handling dquot can\
				 * clear them when it sees fit. */

काष्ठा dquot अणु
	काष्ठा hlist_node dq_hash;	/* Hash list in memory [dq_list_lock] */
	काष्ठा list_head dq_inuse;	/* List of all quotas [dq_list_lock] */
	काष्ठा list_head dq_मुक्त;	/* Free list element [dq_list_lock] */
	काष्ठा list_head dq_dirty;	/* List of dirty dquots [dq_list_lock] */
	काष्ठा mutex dq_lock;		/* dquot IO lock */
	spinlock_t dq_dqb_lock;		/* Lock protecting dq_dqb changes */
	atomic_t dq_count;		/* Use count */
	काष्ठा super_block *dq_sb;	/* superblock this applies to */
	काष्ठा kqid dq_id;		/* ID this applies to (uid, gid, projid) */
	loff_t dq_off;			/* Offset of dquot on disk [dq_lock, stable once set] */
	अचिन्हित दीर्घ dq_flags;		/* See DQ_* */
	काष्ठा mem_dqblk dq_dqb;	/* Diskquota usage [dq_dqb_lock] */
पूर्ण;

/* Operations which must be implemented by each quota क्रमmat */
काष्ठा quota_क्रमmat_ops अणु
	पूर्णांक (*check_quota_file)(काष्ठा super_block *sb, पूर्णांक type);	/* Detect whether file is in our क्रमmat */
	पूर्णांक (*पढ़ो_file_info)(काष्ठा super_block *sb, पूर्णांक type);	/* Read मुख्य info about file - called on quotaon() */
	पूर्णांक (*ग_लिखो_file_info)(काष्ठा super_block *sb, पूर्णांक type);	/* Write मुख्य info about file */
	पूर्णांक (*मुक्त_file_info)(काष्ठा super_block *sb, पूर्णांक type);	/* Called on quotaoff() */
	पूर्णांक (*पढ़ो_dqblk)(काष्ठा dquot *dquot);		/* Read काष्ठाure क्रम one user */
	पूर्णांक (*commit_dqblk)(काष्ठा dquot *dquot);	/* Write काष्ठाure क्रम one user */
	पूर्णांक (*release_dqblk)(काष्ठा dquot *dquot);	/* Called when last reference to dquot is being dropped */
	पूर्णांक (*get_next_id)(काष्ठा super_block *sb, काष्ठा kqid *qid);	/* Get next ID with existing काष्ठाure in the quota file */
पूर्ण;

/* Operations working with dquots */
काष्ठा dquot_operations अणु
	पूर्णांक (*ग_लिखो_dquot) (काष्ठा dquot *);		/* Ordinary dquot ग_लिखो */
	काष्ठा dquot *(*alloc_dquot)(काष्ठा super_block *, पूर्णांक);	/* Allocate memory क्रम new dquot */
	व्योम (*destroy_dquot)(काष्ठा dquot *);		/* Free memory क्रम dquot */
	पूर्णांक (*acquire_dquot) (काष्ठा dquot *);		/* Quota is going to be created on disk */
	पूर्णांक (*release_dquot) (काष्ठा dquot *);		/* Quota is going to be deleted from disk */
	पूर्णांक (*mark_dirty) (काष्ठा dquot *);		/* Dquot is marked dirty */
	पूर्णांक (*ग_लिखो_info) (काष्ठा super_block *, पूर्णांक);	/* Write of quota "superblock" */
	/* get reserved quota क्रम delayed alloc, value वापसed is managed by
	 * quota code only */
	qमाप_प्रकार *(*get_reserved_space) (काष्ठा inode *);
	पूर्णांक (*get_projid) (काष्ठा inode *, kprojid_t *);/* Get project ID */
	/* Get number of inodes that were अक्षरged क्रम a given inode */
	पूर्णांक (*get_inode_usage) (काष्ठा inode *, qमाप_प्रकार *);
	/* Get next ID with active quota काष्ठाure */
	पूर्णांक (*get_next_id) (काष्ठा super_block *sb, काष्ठा kqid *qid);
पूर्ण;

काष्ठा path;

/* Structure क्रम communicating via ->get_dqblk() & ->set_dqblk() */
काष्ठा qc_dqblk अणु
	पूर्णांक d_fieldmask;	/* mask of fields to change in ->set_dqblk() */
	u64 d_spc_hardlimit;	/* असलolute limit on used space */
	u64 d_spc_softlimit;	/* preferred limit on used space */
	u64 d_ino_hardlimit;	/* maximum # allocated inodes */
	u64 d_ino_softlimit;	/* preferred inode limit */
	u64 d_space;		/* Space owned by the user */
	u64 d_ino_count;	/* # inodes owned by the user */
	s64 d_ino_समयr;	/* zero अगर within inode limits */
				/* अगर not, we refuse service */
	s64 d_spc_समयr;	/* similar to above; क्रम space */
	पूर्णांक d_ino_warns;	/* # warnings issued wrt num inodes */
	पूर्णांक d_spc_warns;	/* # warnings issued wrt used space */
	u64 d_rt_spc_hardlimit;	/* असलolute limit on realसमय space */
	u64 d_rt_spc_softlimit;	/* preferred limit on RT space */
	u64 d_rt_space;		/* realसमय space owned */
	s64 d_rt_spc_समयr;	/* similar to above; क्रम RT space */
	पूर्णांक d_rt_spc_warns;	/* # warnings issued wrt RT space */
पूर्ण;

/*
 * Field specअगरiers क्रम ->set_dqblk() in काष्ठा qc_dqblk and also क्रम
 * ->set_info() in काष्ठा qc_info
 */
#घोषणा	QC_INO_SOFT	(1<<0)
#घोषणा	QC_INO_HARD	(1<<1)
#घोषणा	QC_SPC_SOFT	(1<<2)
#घोषणा	QC_SPC_HARD	(1<<3)
#घोषणा	QC_RT_SPC_SOFT	(1<<4)
#घोषणा	QC_RT_SPC_HARD	(1<<5)
#घोषणा QC_LIMIT_MASK (QC_INO_SOFT | QC_INO_HARD | QC_SPC_SOFT | QC_SPC_HARD | \
		       QC_RT_SPC_SOFT | QC_RT_SPC_HARD)
#घोषणा	QC_SPC_TIMER	(1<<6)
#घोषणा	QC_INO_TIMER	(1<<7)
#घोषणा	QC_RT_SPC_TIMER	(1<<8)
#घोषणा QC_TIMER_MASK (QC_SPC_TIMER | QC_INO_TIMER | QC_RT_SPC_TIMER)
#घोषणा	QC_SPC_WARNS	(1<<9)
#घोषणा	QC_INO_WARNS	(1<<10)
#घोषणा	QC_RT_SPC_WARNS	(1<<11)
#घोषणा QC_WARNS_MASK (QC_SPC_WARNS | QC_INO_WARNS | QC_RT_SPC_WARNS)
#घोषणा	QC_SPACE	(1<<12)
#घोषणा	QC_INO_COUNT	(1<<13)
#घोषणा	QC_RT_SPACE	(1<<14)
#घोषणा QC_ACCT_MASK (QC_SPACE | QC_INO_COUNT | QC_RT_SPACE)
#घोषणा QC_FLAGS	(1<<15)

#घोषणा QCI_SYSखाता		(1 << 0)	/* Quota file is hidden from userspace */
#घोषणा QCI_ROOT_SQUASH		(1 << 1)	/* Root squash turned on */
#घोषणा QCI_ACCT_ENABLED	(1 << 2)	/* Quota accounting enabled */
#घोषणा QCI_LIMITS_ENFORCED	(1 << 3)	/* Quota limits enक्रमced */

/* Structures क्रम communicating via ->get_state */
काष्ठा qc_type_state अणु
	अचिन्हित पूर्णांक flags;		/* Flags QCI_* */
	अचिन्हित पूर्णांक spc_समयlimit;	/* Time after which space softlimit is
					 * enक्रमced */
	अचिन्हित पूर्णांक ino_समयlimit;	/* Ditto क्रम inode softlimit */
	अचिन्हित पूर्णांक rt_spc_समयlimit;	/* Ditto क्रम real-समय space */
	अचिन्हित पूर्णांक spc_warnlimit;	/* Limit क्रम number of space warnings */
	अचिन्हित पूर्णांक ino_warnlimit;	/* Ditto क्रम inodes */
	अचिन्हित पूर्णांक rt_spc_warnlimit;	/* Ditto क्रम real-समय space */
	अचिन्हित दीर्घ दीर्घ ino;		/* Inode number of quota file */
	blkcnt_t blocks;		/* Number of 512-byte blocks in the file */
	blkcnt_t nextents;		/* Number of extents in the file */
पूर्ण;

काष्ठा qc_state अणु
	अचिन्हित पूर्णांक s_incoredqs;	/* Number of dquots in core */
	काष्ठा qc_type_state s_state[MAXQUOTAS];  /* Per quota type inक्रमmation */
पूर्ण;

/* Structure क्रम communicating via ->set_info */
काष्ठा qc_info अणु
	पूर्णांक i_fieldmask;	/* mask of fields to change in ->set_info() */
	अचिन्हित पूर्णांक i_flags;		/* Flags QCI_* */
	अचिन्हित पूर्णांक i_spc_समयlimit;	/* Time after which space softlimit is
					 * enक्रमced */
	अचिन्हित पूर्णांक i_ino_समयlimit;	/* Ditto क्रम inode softlimit */
	अचिन्हित पूर्णांक i_rt_spc_समयlimit;/* Ditto क्रम real-समय space */
	अचिन्हित पूर्णांक i_spc_warnlimit;	/* Limit क्रम number of space warnings */
	अचिन्हित पूर्णांक i_ino_warnlimit;	/* Limit क्रम number of inode warnings */
	अचिन्हित पूर्णांक i_rt_spc_warnlimit;	/* Ditto क्रम real-समय space */
पूर्ण;

/* Operations handling requests from userspace */
काष्ठा quotactl_ops अणु
	पूर्णांक (*quota_on)(काष्ठा super_block *, पूर्णांक, पूर्णांक, स्थिर काष्ठा path *);
	पूर्णांक (*quota_off)(काष्ठा super_block *, पूर्णांक);
	पूर्णांक (*quota_enable)(काष्ठा super_block *, अचिन्हित पूर्णांक);
	पूर्णांक (*quota_disable)(काष्ठा super_block *, अचिन्हित पूर्णांक);
	पूर्णांक (*quota_sync)(काष्ठा super_block *, पूर्णांक);
	पूर्णांक (*set_info)(काष्ठा super_block *, पूर्णांक, काष्ठा qc_info *);
	पूर्णांक (*get_dqblk)(काष्ठा super_block *, काष्ठा kqid, काष्ठा qc_dqblk *);
	पूर्णांक (*get_nextdqblk)(काष्ठा super_block *, काष्ठा kqid *,
			     काष्ठा qc_dqblk *);
	पूर्णांक (*set_dqblk)(काष्ठा super_block *, काष्ठा kqid, काष्ठा qc_dqblk *);
	पूर्णांक (*get_state)(काष्ठा super_block *, काष्ठा qc_state *);
	पूर्णांक (*rm_xquota)(काष्ठा super_block *, अचिन्हित पूर्णांक);
पूर्ण;

काष्ठा quota_क्रमmat_type अणु
	पूर्णांक qf_fmt_id;	/* Quota क्रमmat id */
	स्थिर काष्ठा quota_क्रमmat_ops *qf_ops;	/* Operations of क्रमmat */
	काष्ठा module *qf_owner;		/* Module implementing quota क्रमmat */
	काष्ठा quota_क्रमmat_type *qf_next;
पूर्ण;

/**
 * Quota state flags - they come in three flavors - क्रम users, groups and projects.
 *
 * Actual typed flags layout:
 *				USRQUOTA	GRPQUOTA	PRJQUOTA
 *  DQUOT_USAGE_ENABLED		0x0001		0x0002		0x0004
 *  DQUOT_LIMITS_ENABLED	0x0008		0x0010		0x0020
 *  DQUOT_SUSPENDED		0x0040		0x0080		0x0100
 *
 * Following bits are used क्रम non-typed flags:
 *  DQUOT_QUOTA_SYS_खाता	0x0200
 *  DQUOT_NEGATIVE_USAGE	0x0400
 *  DQUOT_NOLIST_सूचीTY		0x0800
 */
क्रमागत अणु
	_DQUOT_USAGE_ENABLED = 0,		/* Track disk usage क्रम users */
	_DQUOT_LIMITS_ENABLED,			/* Enक्रमce quota limits क्रम users */
	_DQUOT_SUSPENDED,			/* User diskquotas are off, but
						 * we have necessary info in
						 * memory to turn them on */
	_DQUOT_STATE_FLAGS
पूर्ण;
#घोषणा DQUOT_USAGE_ENABLED	(1 << _DQUOT_USAGE_ENABLED * MAXQUOTAS)
#घोषणा DQUOT_LIMITS_ENABLED	(1 << _DQUOT_LIMITS_ENABLED * MAXQUOTAS)
#घोषणा DQUOT_SUSPENDED		(1 << _DQUOT_SUSPENDED * MAXQUOTAS)
#घोषणा DQUOT_STATE_FLAGS	(DQUOT_USAGE_ENABLED | DQUOT_LIMITS_ENABLED | \
				 DQUOT_SUSPENDED)
/* Other quota flags */
#घोषणा DQUOT_STATE_LAST	(_DQUOT_STATE_FLAGS * MAXQUOTAS)
#घोषणा DQUOT_QUOTA_SYS_खाता	(1 << DQUOT_STATE_LAST)
						/* Quota file is a special
						 * प्रणाली file and user cannot
						 * touch it. Fileप्रणाली is
						 * responsible क्रम setting
						 * S_NOQUOTA, S_NOATIME flags
						 */
#घोषणा DQUOT_NEGATIVE_USAGE	(1 << (DQUOT_STATE_LAST + 1))
					       /* Allow negative quota usage */
/* Do not track dirty dquots in a list */
#घोषणा DQUOT_NOLIST_सूचीTY	(1 << (DQUOT_STATE_LAST + 2))

अटल अंतरभूत अचिन्हित पूर्णांक dquot_state_flag(अचिन्हित पूर्णांक flags, पूर्णांक type)
अणु
	वापस flags << type;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dquot_generic_flag(अचिन्हित पूर्णांक flags, पूर्णांक type)
अणु
	वापस (flags >> type) & DQUOT_STATE_FLAGS;
पूर्ण

/* Biपंचांगap of quota types where flag is set in flags */
अटल __always_अंतरभूत अचिन्हित dquot_state_types(अचिन्हित flags, अचिन्हित flag)
अणु
	BUILD_BUG_ON_NOT_POWER_OF_2(flag);
	वापस (flags / flag) & ((1 << MAXQUOTAS) - 1);
पूर्ण

#अगर_घोषित CONFIG_QUOTA_NETLINK_INTERFACE
बाह्य व्योम quota_send_warning(काष्ठा kqid qid, dev_t dev,
			       स्थिर अक्षर warntype);
#अन्यथा
अटल अंतरभूत व्योम quota_send_warning(काष्ठा kqid qid, dev_t dev,
				      स्थिर अक्षर warntype)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_QUOTA_NETLINK_INTERFACE */

काष्ठा quota_info अणु
	अचिन्हित पूर्णांक flags;			/* Flags क्रम diskquotas on this device */
	काष्ठा rw_semaphore dqio_sem;		/* Lock quota file जबतक I/O in progress */
	काष्ठा inode *files[MAXQUOTAS];		/* inodes of quotafiles */
	काष्ठा mem_dqinfo info[MAXQUOTAS];	/* Inक्रमmation क्रम each quota type */
	स्थिर काष्ठा quota_क्रमmat_ops *ops[MAXQUOTAS];	/* Operations क्रम each type */
पूर्ण;

पूर्णांक रेजिस्टर_quota_क्रमmat(काष्ठा quota_क्रमmat_type *fmt);
व्योम unरेजिस्टर_quota_क्रमmat(काष्ठा quota_क्रमmat_type *fmt);

काष्ठा quota_module_name अणु
	पूर्णांक qm_fmt_id;
	अक्षर *qm_mod_name;
पूर्ण;

#घोषणा INIT_QUOTA_MODULE_NAMES अणु\
	अणुQFMT_VFS_OLD, "quota_v1"पूर्ण,\
	अणुQFMT_VFS_V0, "quota_v2"पूर्ण,\
	अणुQFMT_VFS_V1, "quota_v2"पूर्ण,\
	अणु0, शून्यपूर्णपूर्ण

#पूर्ण_अगर /* _QUOTA_ */
