<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * segment.h - NILFS Segment स्थिरructor prototypes and definitions
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 *
 */
#अगर_अघोषित _NILFS_SEGMENT_H
#घोषणा _NILFS_SEGMENT_H

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/workqueue.h>
#समावेश "nilfs.h"

काष्ठा nilfs_root;

/**
 * काष्ठा nilfs_recovery_info - Recovery inक्रमmation
 * @ri_need_recovery: Recovery status
 * @ri_super_root: Block number of the last super root
 * @ri_ri_cno: Number of the last checkpoपूर्णांक
 * @ri_lsegs_start: Region क्रम roll-क्रमwarding (start block number)
 * @ri_lsegs_end: Region क्रम roll-क्रमwarding (end block number)
 * @ri_lseg_start_seq: Sequence value of the segment at ri_lsegs_start
 * @ri_used_segments: List of segments to be mark active
 * @ri_pseg_start: Block number of the last partial segment
 * @ri_seq: Sequence number on the last partial segment
 * @ri_segnum: Segment number on the last partial segment
 * @ri_nextnum: Next segment number on the last partial segment
 */
काष्ठा nilfs_recovery_info अणु
	पूर्णांक			ri_need_recovery;
	sector_t		ri_super_root;
	__u64			ri_cno;

	sector_t		ri_lsegs_start;
	sector_t		ri_lsegs_end;
	u64			ri_lsegs_start_seq;
	काष्ठा list_head	ri_used_segments;
	sector_t		ri_pseg_start;
	u64			ri_seq;
	__u64			ri_segnum;
	__u64			ri_nextnum;
पूर्ण;

/* ri_need_recovery */
#घोषणा NILFS_RECOVERY_SR_UPDATED	 1  /* The super root was updated */
#घोषणा NILFS_RECOVERY_ROLLFORWARD_DONE	 2  /* Rollक्रमward was carried out */

/**
 * काष्ठा nilfs_cstage - Context of collection stage
 * @scnt: Stage count, must be accessed via wrappers:
 *        nilfs_sc_cstage_inc(), nilfs_sc_cstage_set(), nilfs_sc_cstage_get()
 * @flags: State flags
 * @dirty_file_ptr: Poपूर्णांकer on dirty_files list, or inode of a target file
 * @gc_inode_ptr: Poपूर्णांकer on the list of gc-inodes
 */
काष्ठा nilfs_cstage अणु
	पूर्णांक			scnt;
	अचिन्हित पूर्णांक		flags;
	काष्ठा nilfs_inode_info *dirty_file_ptr;
	काष्ठा nilfs_inode_info *gc_inode_ptr;
पूर्ण;

काष्ठा nilfs_segment_buffer;

काष्ठा nilfs_segsum_poपूर्णांकer अणु
	काष्ठा buffer_head     *bh;
	अचिन्हित पूर्णांक		offset; /* offset in bytes */
पूर्ण;

/**
 * काष्ठा nilfs_sc_info - Segment स्थिरructor inक्रमmation
 * @sc_super: Back poपूर्णांकer to super_block काष्ठा
 * @sc_root: root object of the current fileप्रणाली tree
 * @sc_nblk_inc: Block count of current generation
 * @sc_dirty_files: List of files to be written
 * @sc_gc_inodes: List of GC inodes having blocks to be written
 * @sc_iput_queue: list of inodes क्रम which iput should be करोne
 * @sc_iput_work: work काष्ठा to defer iput call
 * @sc_मुक्तsegs: array of segment numbers to be मुक्तd
 * @sc_nमुक्तsegs: number of segments on @sc_मुक्तsegs
 * @sc_dsync_inode: inode whose data pages are written क्रम a sync operation
 * @sc_dsync_start: start byte offset of data pages
 * @sc_dsync_end: end byte offset of data pages (inclusive)
 * @sc_segbufs: List of segment buffers
 * @sc_ग_लिखो_logs: List of segment buffers to hold logs under writing
 * @sc_segbuf_nblocks: Number of available blocks in segment buffers.
 * @sc_curseg: Current segment buffer
 * @sc_stage: Collection stage
 * @sc_finfo_ptr: poपूर्णांकer to the current finfo काष्ठा in the segment summary
 * @sc_binfo_ptr: poपूर्णांकer to the current binfo काष्ठा in the segment summary
 * @sc_blk_cnt:	Block count of a file
 * @sc_datablk_cnt: Data block count of a file
 * @sc_nblk_this_inc: Number of blocks included in the current logical segment
 * @sc_seg_स_समय: Creation समय
 * @sc_cno: checkpoपूर्णांक number of current log
 * @sc_flags: Internal flags
 * @sc_state_lock: spinlock क्रम sc_state and so on
 * @sc_state: Segctord state flags
 * @sc_flush_request: inode biपंचांगap of metadata files to be flushed
 * @sc_रुको_request: Client request queue
 * @sc_रुको_daemon: Daemon रुको queue
 * @sc_रुको_task: Start/end रुको queue to control segctord task
 * @sc_seq_request: Request counter
 * @sc_seq_accept: Accepted request count
 * @sc_seq_करोne: Completion counter
 * @sc_sync: Request of explicit sync operation
 * @sc_पूर्णांकerval: Timeout value of background स्थिरruction
 * @sc_mjcp_freq: Frequency of creating checkpoपूर्णांकs
 * @sc_lseg_sसमय: Start समय of the latest logical segment
 * @sc_watermark: Watermark क्रम the number of dirty buffers
 * @sc_समयr: Timer क्रम segctord
 * @sc_task: current thपढ़ो of segctord
 */
काष्ठा nilfs_sc_info अणु
	काष्ठा super_block     *sc_super;
	काष्ठा nilfs_root      *sc_root;

	अचिन्हित दीर्घ		sc_nblk_inc;

	काष्ठा list_head	sc_dirty_files;
	काष्ठा list_head	sc_gc_inodes;
	काष्ठा list_head	sc_iput_queue;
	काष्ठा work_काष्ठा	sc_iput_work;

	__u64		       *sc_मुक्तsegs;
	माप_प्रकार			sc_nमुक्तsegs;

	काष्ठा nilfs_inode_info *sc_dsync_inode;
	loff_t			sc_dsync_start;
	loff_t			sc_dsync_end;

	/* Segment buffers */
	काष्ठा list_head	sc_segbufs;
	काष्ठा list_head	sc_ग_लिखो_logs;
	अचिन्हित दीर्घ		sc_segbuf_nblocks;
	काष्ठा nilfs_segment_buffer *sc_curseg;

	काष्ठा nilfs_cstage	sc_stage;

	काष्ठा nilfs_segsum_poपूर्णांकer sc_finfo_ptr;
	काष्ठा nilfs_segsum_poपूर्णांकer sc_binfo_ptr;
	अचिन्हित दीर्घ		sc_blk_cnt;
	अचिन्हित दीर्घ		sc_datablk_cnt;
	अचिन्हित दीर्घ		sc_nblk_this_inc;
	समय64_t		sc_seg_स_समय;
	__u64			sc_cno;
	अचिन्हित दीर्घ		sc_flags;

	spinlock_t		sc_state_lock;
	अचिन्हित दीर्घ		sc_state;
	अचिन्हित दीर्घ		sc_flush_request;

	रुको_queue_head_t	sc_रुको_request;
	रुको_queue_head_t	sc_रुको_daemon;
	रुको_queue_head_t	sc_रुको_task;

	__u32			sc_seq_request;
	__u32			sc_seq_accepted;
	__u32			sc_seq_करोne;

	पूर्णांक			sc_sync;
	अचिन्हित दीर्घ		sc_पूर्णांकerval;
	अचिन्हित दीर्घ		sc_mjcp_freq;
	अचिन्हित दीर्घ		sc_lseg_sसमय;	/* in 1/HZ seconds */
	अचिन्हित दीर्घ		sc_watermark;

	काष्ठा समयr_list	sc_समयr;
	काष्ठा task_काष्ठा     *sc_समयr_task;
	काष्ठा task_काष्ठा     *sc_task;
पूर्ण;

/* sc_flags */
क्रमागत अणु
	NILFS_SC_सूचीTY,		/* One or more dirty meta-data blocks exist */
	NILFS_SC_UNCLOSED,	/* Logical segment is not बंदd */
	NILFS_SC_SUPER_ROOT,	/* The latest segment has a super root */
	NILFS_SC_PRIOR_FLUSH,	/*
				 * Requesting immediate flush without making a
				 * checkpoपूर्णांक
				 */
	NILFS_SC_HAVE_DELTA,	/*
				 * Next checkpoपूर्णांक will have update of files
				 * other than DAT, cpfile, sufile, or files
				 * moved by GC.
				 */
पूर्ण;

/* sc_state */
#घोषणा NILFS_SEGCTOR_QUIT	    0x0001  /* segctord is being destroyed */
#घोषणा NILFS_SEGCTOR_COMMIT	    0x0004  /* committed transaction exists */

/*
 * Constant parameters
 */
#घोषणा NILFS_SC_CLEANUP_RETRY	    3  /*
					* Retry count of स्थिरruction when
					* destroying segctord
					*/

/*
 * Default values of समयout, in seconds.
 */
#घोषणा NILFS_SC_DEFAULT_TIMEOUT    5   /*
					 * Timeout value of dirty blocks.
					 * It triggers स्थिरruction of a
					 * logical segment with a super root.
					 */
#घोषणा NILFS_SC_DEFAULT_SR_FREQ    30  /*
					 * Maximum frequency of super root
					 * creation
					 */

/*
 * The शेष threshold amount of data, in block counts.
 */
#घोषणा NILFS_SC_DEFAULT_WATERMARK  3600

/* super.c */
बाह्य काष्ठा kmem_cache *nilfs_transaction_cachep;

/* segment.c */
बाह्य व्योम nilfs_relax_pressure_in_lock(काष्ठा super_block *);

बाह्य पूर्णांक nilfs_स्थिरruct_segment(काष्ठा super_block *);
बाह्य पूर्णांक nilfs_स्थिरruct_dsync_segment(काष्ठा super_block *, काष्ठा inode *,
					 loff_t, loff_t);
बाह्य व्योम nilfs_flush_segment(काष्ठा super_block *, ino_t);
बाह्य पूर्णांक nilfs_clean_segments(काष्ठा super_block *, काष्ठा nilfs_argv *,
				व्योम **);

पूर्णांक nilfs_attach_log_ग_लिखोr(काष्ठा super_block *sb, काष्ठा nilfs_root *root);
व्योम nilfs_detach_log_ग_लिखोr(काष्ठा super_block *sb);

/* recovery.c */
बाह्य पूर्णांक nilfs_पढ़ो_super_root_block(काष्ठा the_nilfs *, sector_t,
				       काष्ठा buffer_head **, पूर्णांक);
बाह्य पूर्णांक nilfs_search_super_root(काष्ठा the_nilfs *,
				   काष्ठा nilfs_recovery_info *);
पूर्णांक nilfs_salvage_orphan_logs(काष्ठा the_nilfs *nilfs, काष्ठा super_block *sb,
			      काष्ठा nilfs_recovery_info *ri);
बाह्य व्योम nilfs_dispose_segment_list(काष्ठा list_head *);

#पूर्ण_अगर /* _NILFS_SEGMENT_H */
