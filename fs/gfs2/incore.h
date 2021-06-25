<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __INCORE_DOT_H__
#घोषणा __INCORE_DOT_H__

#समावेश <linux/fs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/dlm.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rculist_bl.h>
#समावेश <linux/completion.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/percpu.h>
#समावेश <linux/lockref.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/mutex.h>

#घोषणा DIO_WAIT	0x00000010
#घोषणा DIO_METADATA	0x00000020

काष्ठा gfs2_log_operations;
काष्ठा gfs2_bufdata;
काष्ठा gfs2_holder;
काष्ठा gfs2_glock;
काष्ठा gfs2_quota_data;
काष्ठा gfs2_trans;
काष्ठा gfs2_jdesc;
काष्ठा gfs2_sbd;
काष्ठा lm_lockops;

प्रकार व्योम (*gfs2_glop_bh_t) (काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक ret);

काष्ठा gfs2_log_header_host अणु
	u64 lh_sequence;	/* Sequence number of this transaction */
	u32 lh_flags;		/* GFS2_LOG_HEAD_... */
	u32 lh_tail;		/* Block number of log tail */
	u32 lh_blkno;

	s64 lh_local_total;
	s64 lh_local_मुक्त;
	s64 lh_local_dinodes;
पूर्ण;

/*
 * Structure of operations that are associated with each
 * type of element in the log.
 */

काष्ठा gfs2_log_operations अणु
	व्योम (*lo_beक्रमe_commit) (काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr);
	व्योम (*lo_after_commit) (काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr);
	व्योम (*lo_beक्रमe_scan) (काष्ठा gfs2_jdesc *jd,
				काष्ठा gfs2_log_header_host *head, पूर्णांक pass);
	पूर्णांक (*lo_scan_elements) (काष्ठा gfs2_jdesc *jd, अचिन्हित पूर्णांक start,
				 काष्ठा gfs2_log_descriptor *ld, __be64 *ptr,
				 पूर्णांक pass);
	व्योम (*lo_after_scan) (काष्ठा gfs2_jdesc *jd, पूर्णांक error, पूर्णांक pass);
	स्थिर अक्षर *lo_name;
पूर्ण;

#घोषणा GBF_FULL 1

/**
 * Clone biपंचांगaps (bi_clone):
 *
 * - When a block is मुक्तd, we remember the previous state of the block in the
 *   clone biपंचांगap, and only mark the block as मुक्त in the real biपंचांगap.
 *
 * - When looking क्रम a block to allocate, we check क्रम a मुक्त block in the
 *   clone biपंचांगap, and अगर no clone biपंचांगap exists, in the real biपंचांगap.
 *
 * - For allocating a block, we mark it as allocated in the real biपंचांगap, and अगर
 *   a clone biपंचांगap exists, also in the clone biपंचांगap.
 *
 * - At the end of a log_flush, we copy the real biपंचांगap पूर्णांकo the clone biपंचांगap
 *   to make the clone biपंचांगap reflect the current allocation state.
 *   (Alternatively, we could हटाओ the clone biपंचांगap.)
 *
 * The clone biपंचांगaps are in-core only, and is never written to disk.
 *
 * These steps ensure that blocks which have been मुक्तd in a transaction cannot
 * be पुनः_स्मृतिated in that same transaction.
 */
काष्ठा gfs2_biपंचांगap अणु
	काष्ठा buffer_head *bi_bh;
	अक्षर *bi_clone;
	अचिन्हित दीर्घ bi_flags;
	u32 bi_offset;
	u32 bi_start;
	u32 bi_bytes;
	u32 bi_blocks;
पूर्ण;

काष्ठा gfs2_rgrpd अणु
	काष्ठा rb_node rd_node;		/* Link with superblock */
	काष्ठा gfs2_glock *rd_gl;	/* Glock क्रम this rgrp */
	u64 rd_addr;			/* grp block disk address */
	u64 rd_data0;			/* first data location */
	u32 rd_length;			/* length of rgrp header in fs blocks */
	u32 rd_data;			/* num of data blocks in rgrp */
	u32 rd_bitbytes;		/* number of bytes in data biपंचांगaps */
	u32 rd_मुक्त;
	u32 rd_requested;		/* number of blocks in rd_rstree */
	u32 rd_reserved;		/* number of reserved blocks */
	u32 rd_मुक्त_clone;
	u32 rd_dinodes;
	u64 rd_igeneration;
	काष्ठा gfs2_biपंचांगap *rd_bits;
	काष्ठा gfs2_sbd *rd_sbd;
	काष्ठा gfs2_rgrp_lvb *rd_rgl;
	u32 rd_last_alloc;
	u32 rd_flags;
	u32 rd_extfail_pt;		/* extent failure poपूर्णांक */
#घोषणा GFS2_RDF_CHECK		0x10000000 /* check क्रम unlinked inodes */
#घोषणा GFS2_RDF_UPTODATE	0x20000000 /* rg is up to date */
#घोषणा GFS2_RDF_ERROR		0x40000000 /* error in rg */
#घोषणा GFS2_RDF_PREFERRED	0x80000000 /* This rgrp is preferred */
#घोषणा GFS2_RDF_MASK		0xf0000000 /* mask क्रम पूर्णांकernal flags */
	spinlock_t rd_rsspin;           /* protects reservation related vars */
	काष्ठा mutex rd_mutex;
	काष्ठा rb_root rd_rstree;       /* multi-block reservation tree */
पूर्ण;

क्रमागत gfs2_state_bits अणु
	BH_Pinned = BH_PrivateStart,
	BH_Escaped = BH_PrivateStart + 1,
पूर्ण;

BUFFER_FNS(Pinned, pinned)
TAS_BUFFER_FNS(Pinned, pinned)
BUFFER_FNS(Escaped, escaped)
TAS_BUFFER_FNS(Escaped, escaped)

काष्ठा gfs2_bufdata अणु
	काष्ठा buffer_head *bd_bh;
	काष्ठा gfs2_glock *bd_gl;
	u64 bd_blkno;

	काष्ठा list_head bd_list;

	काष्ठा gfs2_trans *bd_tr;
	काष्ठा list_head bd_ail_st_list;
	काष्ठा list_head bd_ail_gl_list;
पूर्ण;

/*
 * Internally, we prefix things with gdlm_ and GDLM_ (क्रम gfs-dlm) since a
 * prefix of lock_dlm_ माला_लो awkward.
 */

#घोषणा GDLM_STRNAME_BYTES	25
#घोषणा GDLM_LVB_SIZE		32

/*
 * ls_recover_flags:
 *
 * DFL_BLOCK_LOCKS: dlm is in recovery and will grant locks that had been
 * held by failed nodes whose journals need recovery.  Those locks should
 * only be used क्रम journal recovery until the journal recovery is करोne.
 * This is set by the dlm recover_prep callback and cleared by the
 * gfs2_control thपढ़ो when journal recovery is complete.  To aव्योम
 * races between recover_prep setting and gfs2_control clearing, recover_spin
 * is held जबतक changing this bit and पढ़ोing/writing recover_block
 * and recover_start.
 *
 * DFL_NO_DLM_OPS: dlm lockspace ops/callbacks are not being used.
 *
 * DFL_FIRST_MOUNT: this node is the first to mount this fs and is करोing
 * recovery of all journals beक्रमe allowing other nodes to mount the fs.
 * This is cleared when FIRST_MOUNT_DONE is set.
 *
 * DFL_FIRST_MOUNT_DONE: this node was the first mounter, and has finished
 * recovery of all journals, and now allows other nodes to mount the fs.
 *
 * DFL_MOUNT_DONE: gdlm_mount has completed successfully and cleared
 * BLOCK_LOCKS क्रम the first समय.  The gfs2_control thपढ़ो should now
 * control clearing BLOCK_LOCKS क्रम further recoveries.
 *
 * DFL_UNMOUNT: gdlm_unmount sets to keep sdp off gfs2_control_wq.
 *
 * DFL_DLM_RECOVERY: set जबतक dlm is in recovery, between recover_prep()
 * and recover_करोne(), i.e. set जबतक recover_block == recover_start.
 */

क्रमागत अणु
	DFL_BLOCK_LOCKS		= 0,
	DFL_NO_DLM_OPS		= 1,
	DFL_FIRST_MOUNT		= 2,
	DFL_FIRST_MOUNT_DONE	= 3,
	DFL_MOUNT_DONE		= 4,
	DFL_UNMOUNT		= 5,
	DFL_DLM_RECOVERY	= 6,
पूर्ण;

/*
 * We are using काष्ठा lm_lockname as an rhashtable key.  Aव्योम holes within
 * the काष्ठा; padding at the end is fine.
 */
काष्ठा lm_lockname अणु
	u64 ln_number;
	काष्ठा gfs2_sbd *ln_sbd;
	अचिन्हित पूर्णांक ln_type;
पूर्ण;

#घोषणा lm_name_equal(name1, name2) \
        (((name1)->ln_number == (name2)->ln_number) &&	\
	 ((name1)->ln_type == (name2)->ln_type) &&	\
	 ((name1)->ln_sbd == (name2)->ln_sbd))


काष्ठा gfs2_glock_operations अणु
	पूर्णांक (*go_sync) (काष्ठा gfs2_glock *gl);
	पूर्णांक (*go_xmote_bh)(काष्ठा gfs2_glock *gl);
	व्योम (*go_inval) (काष्ठा gfs2_glock *gl, पूर्णांक flags);
	पूर्णांक (*go_demote_ok) (स्थिर काष्ठा gfs2_glock *gl);
	पूर्णांक (*go_lock) (काष्ठा gfs2_holder *gh);
	व्योम (*go_dump)(काष्ठा seq_file *seq, काष्ठा gfs2_glock *gl,
			स्थिर अक्षर *fs_id_buf);
	व्योम (*go_callback)(काष्ठा gfs2_glock *gl, bool remote);
	व्योम (*go_मुक्त)(काष्ठा gfs2_glock *gl);
	स्थिर पूर्णांक go_subclass;
	स्थिर पूर्णांक go_type;
	स्थिर अचिन्हित दीर्घ go_flags;
#घोषणा GLOF_ASPACE 1 /* address space attached */
#घोषणा GLOF_LVB    2 /* Lock Value Block attached */
#घोषणा GLOF_LRU    4 /* LRU managed */
#घोषणा GLOF_NONDISK   8 /* not I/O related */
पूर्ण;

क्रमागत अणु
	GFS2_LKS_SRTT = 0,	/* Non blocking smoothed round trip समय */
	GFS2_LKS_SRTTVAR = 1,	/* Non blocking smoothed variance */
	GFS2_LKS_SRTTB = 2,	/* Blocking smoothed round trip समय */
	GFS2_LKS_SRTTVARB = 3,	/* Blocking smoothed variance */
	GFS2_LKS_SIRT = 4,	/* Smoothed Inter-request समय */
	GFS2_LKS_SIRTVAR = 5,	/* Smoothed Inter-request variance */
	GFS2_LKS_DCOUNT = 6,	/* Count of dlm requests */
	GFS2_LKS_QCOUNT = 7,	/* Count of gfs2_holder queues */
	GFS2_NR_LKSTATS
पूर्ण;

काष्ठा gfs2_lkstats अणु
	u64 stats[GFS2_NR_LKSTATS];
पूर्ण;

क्रमागत अणु
	/* States */
	HIF_HOLDER		= 6,  /* Set क्रम gh that "holds" the glock */
	HIF_FIRST		= 7,
	HIF_WAIT		= 10,
पूर्ण;

काष्ठा gfs2_holder अणु
	काष्ठा list_head gh_list;

	काष्ठा gfs2_glock *gh_gl;
	काष्ठा pid *gh_owner_pid;
	u16 gh_flags;
	u16 gh_state;

	पूर्णांक gh_error;
	अचिन्हित दीर्घ gh_अगरlags; /* HIF_... */
	अचिन्हित दीर्घ gh_ip;
पूर्ण;

/* Number of quota types we support */
#घोषणा GFS2_MAXQUOTAS 2

काष्ठा gfs2_qadata अणु /* quota allocation data */
	/* Quota stuff */
	काष्ठा gfs2_quota_data *qa_qd[2 * GFS2_MAXQUOTAS];
	काष्ठा gfs2_holder qa_qd_ghs[2 * GFS2_MAXQUOTAS];
	अचिन्हित पूर्णांक qa_qd_num;
	पूर्णांक qa_ref;
पूर्ण;

/* Resource group multi-block reservation, in order of appearance:

   Step 1. Function prepares to ग_लिखो, allocates a mb, sets the size hपूर्णांक.
   Step 2. User calls inplace_reserve to target an rgrp, sets the rgrp info
   Step 3. Function get_local_rgrp locks the rgrp, determines which bits to use
   Step 4. Bits are asचिन्हित from the rgrp based on either the reservation
           or wherever it can.
*/

काष्ठा gfs2_blkreserv अणु
	काष्ठा rb_node rs_node;       /* node within rd_rstree */
	काष्ठा gfs2_rgrpd *rs_rgd;
	u64 rs_start;
	u32 rs_requested;
	u32 rs_reserved;              /* number of reserved blocks */
पूर्ण;

/*
 * Allocation parameters
 * @target: The number of blocks we'd ideally like to allocate
 * @aflags: The flags (e.g. Orlov flag)
 *
 * The पूर्णांकent is to gradually expand this काष्ठाure over समय in
 * order to give more inक्रमmation, e.g. alignment, min extent size
 * to the allocation code.
 */
काष्ठा gfs2_alloc_parms अणु
	u64 target;
	u32 min_target;
	u32 aflags;
	u64 allowed;
पूर्ण;

क्रमागत अणु
	GLF_LOCK			= 1,
	GLF_DEMOTE			= 3,
	GLF_PENDING_DEMOTE		= 4,
	GLF_DEMOTE_IN_PROGRESS		= 5,
	GLF_सूचीTY			= 6,
	GLF_LFLUSH			= 7,
	GLF_INVALIDATE_IN_PROGRESS	= 8,
	GLF_REPLY_PENDING		= 9,
	GLF_INITIAL			= 10,
	GLF_FROZEN			= 11,
	GLF_LRU				= 13,
	GLF_OBJECT			= 14, /* Used only क्रम tracing */
	GLF_BLOCKING			= 15,
	GLF_PENDING_DELETE		= 17,
	GLF_FREEING			= 18, /* Wait क्रम glock to be मुक्तd */
पूर्ण;

काष्ठा gfs2_glock अणु
	अचिन्हित दीर्घ gl_flags;		/* GLF_... */
	काष्ठा lm_lockname gl_name;

	काष्ठा lockref gl_lockref;

	/* State fields रक्षित by gl_lockref.lock */
	अचिन्हित पूर्णांक gl_state:2,	/* Current state */
		     gl_target:2,	/* Target state */
		     gl_demote_state:2,	/* State requested by remote node */
		     gl_req:2,		/* State in last dlm request */
		     gl_reply:8;	/* Last reply from the dlm */

	अचिन्हित दीर्घ gl_demote_समय; /* समय of first demote request */
	दीर्घ gl_hold_समय;
	काष्ठा list_head gl_holders;

	स्थिर काष्ठा gfs2_glock_operations *gl_ops;
	kसमय_प्रकार gl_dstamp;
	काष्ठा gfs2_lkstats gl_stats;
	काष्ठा dlm_lksb gl_lksb;
	अचिन्हित दीर्घ gl_tchange;
	व्योम *gl_object;

	काष्ठा list_head gl_lru;
	काष्ठा list_head gl_ail_list;
	atomic_t gl_ail_count;
	atomic_t gl_revokes;
	काष्ठा delayed_work gl_work;
	/* For iखोलो glocks only */
	काष्ठा अणु
		काष्ठा delayed_work gl_delete;
		u64 gl_no_क्रमmal_ino;
	पूर्ण;
	काष्ठा rcu_head gl_rcu;
	काष्ठा rhash_head gl_node;
पूर्ण;

क्रमागत अणु
	GIF_INVALID		= 0,
	GIF_QD_LOCKED		= 1,
	GIF_ALLOC_FAILED	= 2,
	GIF_SW_PAGED		= 3,
	GIF_FREE_VFS_INODE      = 5,
	GIF_GLOP_PENDING	= 6,
	GIF_DEFERRED_DELETE	= 7,
पूर्ण;

काष्ठा gfs2_inode अणु
	काष्ठा inode i_inode;
	u64 i_no_addr;
	u64 i_no_क्रमmal_ino;
	u64 i_generation;
	u64 i_eattr;
	अचिन्हित दीर्घ i_flags;		/* GIF_... */
	काष्ठा gfs2_glock *i_gl; /* Move पूर्णांकo i_gh? */
	काष्ठा gfs2_holder i_iखोलो_gh;
	काष्ठा gfs2_holder i_gh; /* क्रम prepare/commit_ग_लिखो only */
	काष्ठा gfs2_qadata *i_qadata; /* quota allocation data */
	काष्ठा gfs2_holder i_rgd_gh;
	काष्ठा gfs2_blkreserv i_res; /* rgrp multi-block reservation */
	u64 i_goal;	/* goal block क्रम allocations */
	atomic_t i_sizehपूर्णांक;  /* hपूर्णांक of the ग_लिखो size */
	काष्ठा rw_semaphore i_rw_mutex;
	काष्ठा list_head i_ordered;
	काष्ठा list_head i_trunc_list;
	__be64 *i_hash_cache;
	u32 i_entries;
	u32 i_diskflags;
	u8 i_height;
	u8 i_depth;
	u16 i_rahead;
पूर्ण;

/*
 * Since i_inode is the first element of काष्ठा gfs2_inode,
 * this is effectively a cast.
 */
अटल अंतरभूत काष्ठा gfs2_inode *GFS2_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा gfs2_inode, i_inode);
पूर्ण

अटल अंतरभूत काष्ठा gfs2_sbd *GFS2_SB(स्थिर काष्ठा inode *inode)
अणु
	वापस inode->i_sb->s_fs_info;
पूर्ण

काष्ठा gfs2_file अणु
	काष्ठा mutex f_fl_mutex;
	काष्ठा gfs2_holder f_fl_gh;
पूर्ण;

काष्ठा gfs2_revoke_replay अणु
	काष्ठा list_head rr_list;
	u64 rr_blkno;
	अचिन्हित पूर्णांक rr_where;
पूर्ण;

क्रमागत अणु
	QDF_CHANGE		= 1,
	QDF_LOCKED		= 2,
	QDF_REFRESH		= 3,
	QDF_QMSG_QUIET          = 4,
पूर्ण;

काष्ठा gfs2_quota_data अणु
	काष्ठा hlist_bl_node qd_hlist;
	काष्ठा list_head qd_list;
	काष्ठा kqid qd_id;
	काष्ठा gfs2_sbd *qd_sbd;
	काष्ठा lockref qd_lockref;
	काष्ठा list_head qd_lru;
	अचिन्हित qd_hash;

	अचिन्हित दीर्घ qd_flags;		/* QDF_... */

	s64 qd_change;
	s64 qd_change_sync;

	अचिन्हित पूर्णांक qd_slot;
	अचिन्हित पूर्णांक qd_slot_count;

	काष्ठा buffer_head *qd_bh;
	काष्ठा gfs2_quota_change *qd_bh_qc;
	अचिन्हित पूर्णांक qd_bh_count;

	काष्ठा gfs2_glock *qd_gl;
	काष्ठा gfs2_quota_lvb qd_qb;

	u64 qd_sync_gen;
	अचिन्हित दीर्घ qd_last_warn;
	काष्ठा rcu_head qd_rcu;
पूर्ण;

क्रमागत अणु
	TR_TOUCHED = 1,
	TR_ATTACHED = 2,
	TR_ONSTACK = 3,
पूर्ण;

काष्ठा gfs2_trans अणु
	अचिन्हित दीर्घ tr_ip;

	अचिन्हित पूर्णांक tr_blocks;
	अचिन्हित पूर्णांक tr_revokes;
	अचिन्हित पूर्णांक tr_reserved;
	अचिन्हित दीर्घ tr_flags;

	अचिन्हित पूर्णांक tr_num_buf_new;
	अचिन्हित पूर्णांक tr_num_databuf_new;
	अचिन्हित पूर्णांक tr_num_buf_rm;
	अचिन्हित पूर्णांक tr_num_databuf_rm;
	अचिन्हित पूर्णांक tr_num_revoke;

	काष्ठा list_head tr_list;
	काष्ठा list_head tr_databuf;
	काष्ठा list_head tr_buf;

	अचिन्हित पूर्णांक tr_first;
	काष्ठा list_head tr_ail1_list;
	काष्ठा list_head tr_ail2_list;
पूर्ण;

काष्ठा gfs2_journal_extent अणु
	काष्ठा list_head list;

	अचिन्हित पूर्णांक lblock; /* First logical block */
	u64 dblock; /* First disk block */
	u64 blocks;
पूर्ण;

काष्ठा gfs2_jdesc अणु
	काष्ठा list_head jd_list;
	काष्ठा list_head extent_list;
	अचिन्हित पूर्णांक nr_extents;
	काष्ठा work_काष्ठा jd_work;
	काष्ठा inode *jd_inode;
	काष्ठा bio *jd_log_bio;
	अचिन्हित दीर्घ jd_flags;
#घोषणा JDF_RECOVERY 1
	अचिन्हित पूर्णांक jd_jid;
	u32 jd_blocks;
	पूर्णांक jd_recover_error;
	/* Replay stuff */

	अचिन्हित पूर्णांक jd_found_blocks;
	अचिन्हित पूर्णांक jd_found_revokes;
	अचिन्हित पूर्णांक jd_replayed_blocks;

	काष्ठा list_head jd_revoke_list;
	अचिन्हित पूर्णांक jd_replay_tail;

	u64 jd_no_addr;
पूर्ण;

काष्ठा gfs2_statfs_change_host अणु
	s64 sc_total;
	s64 sc_मुक्त;
	s64 sc_dinodes;
पूर्ण;

#घोषणा GFS2_QUOTA_DEFAULT	GFS2_QUOTA_OFF
#घोषणा GFS2_QUOTA_OFF		0
#घोषणा GFS2_QUOTA_ACCOUNT	1
#घोषणा GFS2_QUOTA_ON		2

#घोषणा GFS2_DATA_DEFAULT	GFS2_DATA_ORDERED
#घोषणा GFS2_DATA_WRITEBACK	1
#घोषणा GFS2_DATA_ORDERED	2

#घोषणा GFS2_ERRORS_DEFAULT     GFS2_ERRORS_WITHDRAW
#घोषणा GFS2_ERRORS_WITHDRAW    0
#घोषणा GFS2_ERRORS_CONTINUE    1 /* place holder क्रम future feature */
#घोषणा GFS2_ERRORS_RO          2 /* place holder क्रम future feature */
#घोषणा GFS2_ERRORS_PANIC       3

काष्ठा gfs2_args अणु
	अक्षर ar_lockproto[GFS2_LOCKNAME_LEN];	/* Name of the Lock Protocol */
	अक्षर ar_locktable[GFS2_LOCKNAME_LEN];	/* Name of the Lock Table */
	अक्षर ar_hostdata[GFS2_LOCKNAME_LEN];	/* Host specअगरic data */
	अचिन्हित पूर्णांक ar_spectator:1;		/* Don't get a journal */
	अचिन्हित पूर्णांक ar_localflocks:1;		/* Let the VFS करो flock|fcntl */
	अचिन्हित पूर्णांक ar_debug:1;		/* Oops on errors */
	अचिन्हित पूर्णांक ar_posix_acl:1;		/* Enable posix acls */
	अचिन्हित पूर्णांक ar_quota:2;		/* off/account/on */
	अचिन्हित पूर्णांक ar_suiddir:1;		/* suiddir support */
	अचिन्हित पूर्णांक ar_data:2;			/* ordered/ग_लिखोback */
	अचिन्हित पूर्णांक ar_meta:1;			/* mount metafs */
	अचिन्हित पूर्णांक ar_discard:1;		/* discard requests */
	अचिन्हित पूर्णांक ar_errors:2;               /* errors=withdraw | panic */
	अचिन्हित पूर्णांक ar_nobarrier:1;            /* करो not send barriers */
	अचिन्हित पूर्णांक ar_rgrplvb:1;		/* use lvbs क्रम rgrp info */
	अचिन्हित पूर्णांक ar_got_rgrplvb:1;		/* Was the rgrplvb opt given? */
	अचिन्हित पूर्णांक ar_loccookie:1;		/* use location based सूची_पढ़ो
						   cookies */
	s32 ar_commit;				/* Commit पूर्णांकerval */
	s32 ar_statfs_quantum;			/* The fast statfs पूर्णांकerval */
	s32 ar_quota_quantum;			/* The quota पूर्णांकerval */
	s32 ar_statfs_percent;			/* The % change to क्रमce sync */
पूर्ण;

काष्ठा gfs2_tune अणु
	spinlock_t gt_spin;

	अचिन्हित पूर्णांक gt_logd_secs;

	अचिन्हित पूर्णांक gt_quota_warn_period; /* Secs between quota warn msgs */
	अचिन्हित पूर्णांक gt_quota_scale_num; /* Numerator */
	अचिन्हित पूर्णांक gt_quota_scale_den; /* Denominator */
	अचिन्हित पूर्णांक gt_quota_quantum; /* Secs between syncs to quota file */
	अचिन्हित पूर्णांक gt_new_files_jdata;
	अचिन्हित पूर्णांक gt_max_पढ़ोahead; /* Max bytes to पढ़ो-ahead from disk */
	अचिन्हित पूर्णांक gt_complain_secs;
	अचिन्हित पूर्णांक gt_statfs_quantum;
	अचिन्हित पूर्णांक gt_statfs_slow;
पूर्ण;

क्रमागत अणु
	SDF_JOURNAL_CHECKED	= 0,
	SDF_JOURNAL_LIVE	= 1,
	SDF_WITHDRAWN		= 2,
	SDF_NOBARRIERS		= 3,
	SDF_NORECOVERY		= 4,
	SDF_DEMOTE		= 5,
	SDF_NOJOURNALID		= 6,
	SDF_RORECOVERY		= 7, /* पढ़ो only recovery */
	SDF_SKIP_DLM_UNLOCK	= 8,
	SDF_FORCE_AIL_FLUSH     = 9,
	SDF_FS_FROZEN           = 10,
	SDF_WITHDRAWING		= 11, /* Will withdraw eventually */
	SDF_WITHDRAW_IN_PROG	= 12, /* Withdraw is in progress */
	SDF_REMOTE_WITHDRAW	= 13, /* Perक्रमming remote recovery */
	SDF_WITHDRAW_RECOVERY	= 14, /* Wait क्रम journal recovery when we are
					 withdrawing */
पूर्ण;

क्रमागत gfs2_मुक्तze_state अणु
	SFS_UNFROZEN		= 0,
	SFS_STARTING_FREEZE	= 1,
	SFS_FROZEN		= 2,
पूर्ण;

#घोषणा GFS2_FSNAME_LEN		256

काष्ठा gfs2_inum_host अणु
	u64 no_क्रमmal_ino;
	u64 no_addr;
पूर्ण;

काष्ठा gfs2_sb_host अणु
	u32 sb_magic;
	u32 sb_type;

	u32 sb_fs_क्रमmat;
	u32 sb_multihost_क्रमmat;
	u32 sb_bsize;
	u32 sb_bsize_shअगरt;

	काष्ठा gfs2_inum_host sb_master_dir;
	काष्ठा gfs2_inum_host sb_root_dir;

	अक्षर sb_lockproto[GFS2_LOCKNAME_LEN];
	अक्षर sb_locktable[GFS2_LOCKNAME_LEN];
पूर्ण;

/*
 * lm_mount() वापस values
 *
 * ls_jid - the journal ID this node should use
 * ls_first - this node is the first to mount the file प्रणाली
 * ls_lockspace - lock module's context क्रम this file प्रणाली
 * ls_ops - lock module's functions
 */

काष्ठा lm_lockकाष्ठा अणु
	पूर्णांक ls_jid;
	अचिन्हित पूर्णांक ls_first;
	स्थिर काष्ठा lm_lockops *ls_ops;
	dlm_lockspace_t *ls_dlm;

	पूर्णांक ls_recover_jid_करोne;   /* These two are deprecated, */
	पूर्णांक ls_recover_jid_status; /* used previously by gfs_controld */

	काष्ठा dlm_lksb ls_mounted_lksb; /* mounted_lock */
	काष्ठा dlm_lksb ls_control_lksb; /* control_lock */
	अक्षर ls_control_lvb[GDLM_LVB_SIZE]; /* control_lock lvb */
	काष्ठा completion ls_sync_रुको; /* अणुcontrol,mountedपूर्ण_अणुlock,unlockपूर्ण */
	अक्षर *ls_lvb_bits;

	spinlock_t ls_recover_spin; /* protects following fields */
	अचिन्हित दीर्घ ls_recover_flags; /* DFL_ */
	uपूर्णांक32_t ls_recover_mount; /* gen in first recover_करोne cb */
	uपूर्णांक32_t ls_recover_start; /* gen in last recover_करोne cb */
	uपूर्णांक32_t ls_recover_block; /* copy recover_start in last recover_prep */
	uपूर्णांक32_t ls_recover_size; /* size of recover_submit, recover_result */
	uपूर्णांक32_t *ls_recover_submit; /* gen in last recover_slot cb per jid */
	uपूर्णांक32_t *ls_recover_result; /* result of last jid recovery */
पूर्ण;

काष्ठा gfs2_pcpu_lkstats अणु
	/* One काष्ठा क्रम each glock type */
	काष्ठा gfs2_lkstats lkstats[10];
पूर्ण;

/* List of local (per node) statfs inodes */
काष्ठा local_statfs_inode अणु
	काष्ठा list_head si_list;
	काष्ठा inode *si_sc_inode;
	अचिन्हित पूर्णांक si_jid; /* journal id this statfs inode corresponds to */
पूर्ण;

काष्ठा gfs2_sbd अणु
	काष्ठा super_block *sd_vfs;
	काष्ठा gfs2_pcpu_lkstats __percpu *sd_lkstats;
	काष्ठा kobject sd_kobj;
	काष्ठा completion sd_kobj_unरेजिस्टर;
	अचिन्हित दीर्घ sd_flags;	/* SDF_... */
	काष्ठा gfs2_sb_host sd_sb;

	/* Constants computed on mount */

	u32 sd_fsb2bb;
	u32 sd_fsb2bb_shअगरt;
	u32 sd_diptrs;	/* Number of poपूर्णांकers in a dinode */
	u32 sd_inptrs;	/* Number of poपूर्णांकers in a indirect block */
	u32 sd_ldptrs;  /* Number of poपूर्णांकers in a log descriptor block */
	u32 sd_jbsize;	/* Size of a journaled data block */
	u32 sd_hash_bsize;	/* माप(exhash block) */
	u32 sd_hash_bsize_shअगरt;
	u32 sd_hash_ptrs;	/* Number of poपूर्णांकers in a hash block */
	u32 sd_qc_per_block;
	u32 sd_blocks_per_biपंचांगap;
	u32 sd_max_dirres;	/* Max blocks needed to add a directory entry */
	u32 sd_max_height;	/* Max height of a file's metadata tree */
	u64 sd_heightsize[GFS2_MAX_META_HEIGHT + 1];
	u32 sd_max_dents_per_leaf; /* Max number of dirents in a leaf block */

	काष्ठा gfs2_args sd_args;	/* Mount arguments */
	काष्ठा gfs2_tune sd_tune;	/* Fileप्रणाली tuning काष्ठाure */

	/* Lock Stuff */

	काष्ठा lm_lockकाष्ठा sd_lockकाष्ठा;
	काष्ठा gfs2_holder sd_live_gh;
	काष्ठा gfs2_glock *sd_नाम_gl;
	काष्ठा gfs2_glock *sd_मुक्तze_gl;
	काष्ठा work_काष्ठा sd_मुक्तze_work;
	रुको_queue_head_t sd_glock_रुको;
	रुको_queue_head_t sd_async_glock_रुको;
	atomic_t sd_glock_disposal;
	काष्ठा completion sd_locking_init;
	काष्ठा completion sd_wdack;
	काष्ठा delayed_work sd_control_work;

	/* Inode Stuff */

	काष्ठा dentry *sd_master_dir;
	काष्ठा dentry *sd_root_dir;

	काष्ठा inode *sd_jindex;
	काष्ठा inode *sd_statfs_inode;
	काष्ठा inode *sd_sc_inode;
	काष्ठा list_head sd_sc_inodes_list;
	काष्ठा inode *sd_qc_inode;
	काष्ठा inode *sd_rindex;
	काष्ठा inode *sd_quota_inode;

	/* StatFS stuff */

	spinlock_t sd_statfs_spin;
	काष्ठा gfs2_statfs_change_host sd_statfs_master;
	काष्ठा gfs2_statfs_change_host sd_statfs_local;
	पूर्णांक sd_statfs_क्रमce_sync;

	/* Resource group stuff */

	पूर्णांक sd_rindex_uptodate;
	spinlock_t sd_rindex_spin;
	काष्ठा rb_root sd_rindex_tree;
	अचिन्हित पूर्णांक sd_rgrps;
	अचिन्हित पूर्णांक sd_max_rg_data;

	/* Journal index stuff */

	काष्ठा list_head sd_jindex_list;
	spinlock_t sd_jindex_spin;
	काष्ठा mutex sd_jindex_mutex;
	अचिन्हित पूर्णांक sd_journals;

	काष्ठा gfs2_jdesc *sd_jdesc;
	काष्ठा gfs2_holder sd_journal_gh;
	काष्ठा gfs2_holder sd_jinode_gh;
	काष्ठा gfs2_glock *sd_jinode_gl;

	काष्ठा gfs2_holder sd_sc_gh;
	काष्ठा gfs2_holder sd_qc_gh;

	काष्ठा completion sd_journal_पढ़ोy;

	/* Daemon stuff */

	काष्ठा task_काष्ठा *sd_logd_process;
	काष्ठा task_काष्ठा *sd_quotad_process;

	/* Quota stuff */

	काष्ठा list_head sd_quota_list;
	atomic_t sd_quota_count;
	काष्ठा mutex sd_quota_mutex;
	काष्ठा mutex sd_quota_sync_mutex;
	रुको_queue_head_t sd_quota_रुको;
	काष्ठा list_head sd_trunc_list;
	spinlock_t sd_trunc_lock;

	अचिन्हित पूर्णांक sd_quota_slots;
	अचिन्हित दीर्घ *sd_quota_biपंचांगap;
	spinlock_t sd_biपंचांगap_lock;

	u64 sd_quota_sync_gen;

	/* Log stuff */

	काष्ठा address_space sd_aspace;

	spinlock_t sd_log_lock;

	काष्ठा gfs2_trans *sd_log_tr;
	अचिन्हित पूर्णांक sd_log_blks_reserved;

	atomic_t sd_log_pinned;
	अचिन्हित पूर्णांक sd_log_num_revoke;

	काष्ठा list_head sd_log_revokes;
	काष्ठा list_head sd_log_ordered;
	spinlock_t sd_ordered_lock;

	atomic_t sd_log_thresh1;
	atomic_t sd_log_thresh2;
	atomic_t sd_log_blks_मुक्त;
	atomic_t sd_log_blks_needed;
	atomic_t sd_log_revokes_available;
	रुको_queue_head_t sd_log_रुकोq;
	रुको_queue_head_t sd_logd_रुकोq;

	u64 sd_log_sequence;
	पूर्णांक sd_log_idle;

	काष्ठा rw_semaphore sd_log_flush_lock;
	atomic_t sd_log_in_flight;
	रुको_queue_head_t sd_log_flush_रुको;
	पूर्णांक sd_log_error; /* First log error */
	रुको_queue_head_t sd_withdraw_रुको;

	अचिन्हित पूर्णांक sd_log_tail;
	अचिन्हित पूर्णांक sd_log_flush_tail;
	अचिन्हित पूर्णांक sd_log_head;
	अचिन्हित पूर्णांक sd_log_flush_head;

	spinlock_t sd_ail_lock;
	काष्ठा list_head sd_ail1_list;
	काष्ठा list_head sd_ail2_list;

	/* For quiescing the fileप्रणाली */
	काष्ठा gfs2_holder sd_मुक्तze_gh;
	atomic_t sd_मुक्तze_state;
	काष्ठा mutex sd_मुक्तze_mutex;

	अक्षर sd_fsname[GFS2_FSNAME_LEN + 3 * माप(पूर्णांक) + 2];
	अक्षर sd_table_name[GFS2_FSNAME_LEN];
	अक्षर sd_proto_name[GFS2_FSNAME_LEN];

	/* Debugging crud */

	अचिन्हित दीर्घ sd_last_warning;
	काष्ठा dentry *debugfs_dir;    /* debugfs directory */
	अचिन्हित दीर्घ sd_glock_dqs_held;
पूर्ण;

अटल अंतरभूत व्योम gfs2_glstats_inc(काष्ठा gfs2_glock *gl, पूर्णांक which)
अणु
	gl->gl_stats.stats[which]++;
पूर्ण

अटल अंतरभूत व्योम gfs2_sbstats_inc(स्थिर काष्ठा gfs2_glock *gl, पूर्णांक which)
अणु
	स्थिर काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	preempt_disable();
	this_cpu_ptr(sdp->sd_lkstats)->lkstats[gl->gl_name.ln_type].stats[which]++;
	preempt_enable();
पूर्ण

बाह्य काष्ठा gfs2_rgrpd *gfs2_glock2rgrp(काष्ठा gfs2_glock *gl);

अटल अंतरभूत अचिन्हित gfs2_max_stuffed_size(स्थिर काष्ठा gfs2_inode *ip)
अणु
	वापस GFS2_SB(&ip->i_inode)->sd_sb.sb_bsize - माप(काष्ठा gfs2_dinode);
पूर्ण

#पूर्ण_अगर /* __INCORE_DOT_H__ */

