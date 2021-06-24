<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * the_nilfs.h - the_nilfs shared काष्ठाure.
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 *
 */

#अगर_अघोषित _THE_NILFS_H
#घोषणा _THE_NILFS_H

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/slab.h>
#समावेश <linux/refcount.h>

काष्ठा nilfs_sc_info;
काष्ठा nilfs_sysfs_dev_subgroups;

/* the_nilfs काष्ठा */
क्रमागत अणु
	THE_NILFS_INIT = 0,     /* Inक्रमmation from super_block is set */
	THE_NILFS_DISCONTINUED,	/* 'next' poपूर्णांकer chain has broken */
	THE_NILFS_GC_RUNNING,	/* gc process is running */
	THE_NILFS_SB_सूचीTY,	/* super block is dirty */
पूर्ण;

/**
 * काष्ठा the_nilfs - काष्ठा to supervise multiple nilfs mount poपूर्णांकs
 * @ns_flags: flags
 * @ns_flushed_device: flag indicating अगर all अस्थिर data was flushed
 * @ns_sb: back poपूर्णांकer to super block instance
 * @ns_bdev: block device
 * @ns_sem: semaphore क्रम shared states
 * @ns_snapshot_mount_mutex: mutex to protect snapshot mounts
 * @ns_sbh: buffer heads of on-disk super blocks
 * @ns_sbp: poपूर्णांकers to super block data
 * @ns_sbwसमय: previous ग_लिखो समय of super block
 * @ns_sbwcount: ग_लिखो count of super block
 * @ns_sbsize: size of valid data in super block
 * @ns_mount_state: file प्रणाली state
 * @ns_sb_update_freq: पूर्णांकerval of periodical update of superblocks (in seconds)
 * @ns_seg_seq: segment sequence counter
 * @ns_segnum: index number of the latest full segment.
 * @ns_nextnum: index number of the full segment index to be used next
 * @ns_pseg_offset: offset of next partial segment in the current full segment
 * @ns_cno: next checkpoपूर्णांक number
 * @ns_स_समय: ग_लिखो समय of the last segment
 * @ns_nongc_स_समय: ग_लिखो समय of the last segment not क्रम cleaner operation
 * @ns_ndirtyblks: Number of dirty data blocks
 * @ns_last_segment_lock: lock protecting fields क्रम the latest segment
 * @ns_last_pseg: start block number of the latest segment
 * @ns_last_seq: sequence value of the latest segment
 * @ns_last_cno: checkpoपूर्णांक number of the latest segment
 * @ns_prot_seq: least sequence number of segments which must not be reclaimed
 * @ns_prev_seq: base sequence number used to decide अगर advance log cursor
 * @ns_ग_लिखोr: log ग_लिखोr
 * @ns_segctor_sem: semaphore protecting log ग_लिखो
 * @ns_dat: DAT file inode
 * @ns_cpfile: checkpoपूर्णांक file inode
 * @ns_sufile: segusage file inode
 * @ns_cptree: rb-tree of all mounted checkpoपूर्णांकs (nilfs_root)
 * @ns_cptree_lock: lock protecting @ns_cptree
 * @ns_dirty_files: list of dirty files
 * @ns_inode_lock: lock protecting @ns_dirty_files
 * @ns_gc_inodes: dummy inodes to keep live blocks
 * @ns_next_generation: next generation number क्रम inodes
 * @ns_next_gen_lock: lock protecting @ns_next_generation
 * @ns_mount_opt: mount options
 * @ns_resuid: uid क्रम reserved blocks
 * @ns_resgid: gid क्रम reserved blocks
 * @ns_पूर्णांकerval: checkpoपूर्णांक creation पूर्णांकerval
 * @ns_watermark: watermark क्रम the number of dirty buffers
 * @ns_blocksize_bits: bit length of block size
 * @ns_blocksize: block size
 * @ns_nsegments: number of segments in fileप्रणाली
 * @ns_blocks_per_segment: number of blocks per segment
 * @ns_r_segments_percentage: reserved segments percentage
 * @ns_nrsvsegs: number of reserved segments
 * @ns_first_data_block: block number of first data block
 * @ns_inode_size: size of on-disk inode
 * @ns_first_ino: first not-special inode number
 * @ns_crc_seed: seed value of CRC32 calculation
 * @ns_dev_kobj: /sys/fs/<nilfs>/<device>
 * @ns_dev_kobj_unरेजिस्टर: completion state
 * @ns_dev_subgroups: <device> subgroups poपूर्णांकer
 */
काष्ठा the_nilfs अणु
	अचिन्हित दीर्घ		ns_flags;
	पूर्णांक			ns_flushed_device;

	काष्ठा super_block     *ns_sb;
	काष्ठा block_device    *ns_bdev;
	काष्ठा rw_semaphore	ns_sem;
	काष्ठा mutex		ns_snapshot_mount_mutex;

	/*
	 * used क्रम
	 * - loading the latest checkpoपूर्णांक exclusively.
	 * - allocating a new full segment.
	 */
	काष्ठा buffer_head     *ns_sbh[2];
	काष्ठा nilfs_super_block *ns_sbp[2];
	समय64_t		ns_sbwसमय;
	अचिन्हित पूर्णांक		ns_sbwcount;
	अचिन्हित पूर्णांक		ns_sbsize;
	अचिन्हित पूर्णांक		ns_mount_state;
	अचिन्हित पूर्णांक		ns_sb_update_freq;

	/*
	 * The following fields are updated by a writable FS-instance.
	 * These fields are रक्षित by ns_segctor_sem outside load_nilfs().
	 */
	u64			ns_seg_seq;
	__u64			ns_segnum;
	__u64			ns_nextnum;
	अचिन्हित दीर्घ		ns_pseg_offset;
	__u64			ns_cno;
	समय64_t		ns_स_समय;
	समय64_t		ns_nongc_स_समय;
	atomic_t		ns_ndirtyblks;

	/*
	 * The following fields hold inक्रमmation on the latest partial segment
	 * written to disk with a super root.  These fields are रक्षित by
	 * ns_last_segment_lock.
	 */
	spinlock_t		ns_last_segment_lock;
	sector_t		ns_last_pseg;
	u64			ns_last_seq;
	__u64			ns_last_cno;
	u64			ns_prot_seq;
	u64			ns_prev_seq;

	काष्ठा nilfs_sc_info   *ns_ग_लिखोr;
	काष्ठा rw_semaphore	ns_segctor_sem;

	/*
	 * Following fields are lock मुक्त except क्रम the period beक्रमe
	 * the_nilfs is initialized.
	 */
	काष्ठा inode	       *ns_dat;
	काष्ठा inode	       *ns_cpfile;
	काष्ठा inode	       *ns_sufile;

	/* Checkpoपूर्णांक tree */
	काष्ठा rb_root		ns_cptree;
	spinlock_t		ns_cptree_lock;

	/* Dirty inode list */
	काष्ठा list_head	ns_dirty_files;
	spinlock_t		ns_inode_lock;

	/* GC inode list */
	काष्ठा list_head	ns_gc_inodes;

	/* Inode allocator */
	u32			ns_next_generation;
	spinlock_t		ns_next_gen_lock;

	/* Mount options */
	अचिन्हित दीर्घ		ns_mount_opt;

	uid_t			ns_resuid;
	gid_t			ns_resgid;
	अचिन्हित दीर्घ		ns_पूर्णांकerval;
	अचिन्हित दीर्घ		ns_watermark;

	/* Disk layout inक्रमmation (अटल) */
	अचिन्हित पूर्णांक		ns_blocksize_bits;
	अचिन्हित पूर्णांक		ns_blocksize;
	अचिन्हित दीर्घ		ns_nsegments;
	अचिन्हित दीर्घ		ns_blocks_per_segment;
	अचिन्हित दीर्घ		ns_r_segments_percentage;
	अचिन्हित दीर्घ		ns_nrsvsegs;
	अचिन्हित दीर्घ		ns_first_data_block;
	पूर्णांक			ns_inode_size;
	पूर्णांक			ns_first_ino;
	u32			ns_crc_seed;

	/* /sys/fs/<nilfs>/<device> */
	काष्ठा kobject ns_dev_kobj;
	काष्ठा completion ns_dev_kobj_unरेजिस्टर;
	काष्ठा nilfs_sysfs_dev_subgroups *ns_dev_subgroups;
पूर्ण;

#घोषणा THE_NILFS_FNS(bit, name)					\
अटल अंतरभूत व्योम set_nilfs_##name(काष्ठा the_nilfs *nilfs)		\
अणु									\
	set_bit(THE_NILFS_##bit, &(nilfs)->ns_flags);			\
पूर्ण									\
अटल अंतरभूत व्योम clear_nilfs_##name(काष्ठा the_nilfs *nilfs)		\
अणु									\
	clear_bit(THE_NILFS_##bit, &(nilfs)->ns_flags);			\
पूर्ण									\
अटल अंतरभूत पूर्णांक nilfs_##name(काष्ठा the_nilfs *nilfs)			\
अणु									\
	वापस test_bit(THE_NILFS_##bit, &(nilfs)->ns_flags);		\
पूर्ण

THE_NILFS_FNS(INIT, init)
THE_NILFS_FNS(DISCONTINUED, disजारीd)
THE_NILFS_FNS(GC_RUNNING, gc_running)
THE_NILFS_FNS(SB_सूचीTY, sb_dirty)

/*
 * Mount option operations
 */
#घोषणा nilfs_clear_opt(nilfs, opt)  \
	((nilfs)->ns_mount_opt &= ~NILFS_MOUNT_##opt)
#घोषणा nilfs_set_opt(nilfs, opt)  \
	((nilfs)->ns_mount_opt |= NILFS_MOUNT_##opt)
#घोषणा nilfs_test_opt(nilfs, opt) ((nilfs)->ns_mount_opt & NILFS_MOUNT_##opt)
#घोषणा nilfs_ग_लिखो_opt(nilfs, mask, opt)				\
	((nilfs)->ns_mount_opt =					\
		(((nilfs)->ns_mount_opt & ~NILFS_MOUNT_##mask) |	\
		 NILFS_MOUNT_##opt))					\

/**
 * काष्ठा nilfs_root - nilfs root object
 * @cno: checkpoपूर्णांक number
 * @rb_node: red-black tree node
 * @count: refcount of this काष्ठाure
 * @nilfs: nilfs object
 * @अगरile: inode file
 * @inodes_count: number of inodes
 * @blocks_count: number of blocks
 * @snapshot_kobj: /sys/fs/<nilfs>/<device>/mounted_snapshots/<snapshot>
 * @snapshot_kobj_unरेजिस्टर: completion state क्रम kernel object
 */
काष्ठा nilfs_root अणु
	__u64 cno;
	काष्ठा rb_node rb_node;

	refcount_t count;
	काष्ठा the_nilfs *nilfs;
	काष्ठा inode *अगरile;

	atomic64_t inodes_count;
	atomic64_t blocks_count;

	/* /sys/fs/<nilfs>/<device>/mounted_snapshots/<snapshot> */
	काष्ठा kobject snapshot_kobj;
	काष्ठा completion snapshot_kobj_unरेजिस्टर;
पूर्ण;

/* Special checkpoपूर्णांक number */
#घोषणा NILFS_CPTREE_CURRENT_CNO	0

/* Minimum पूर्णांकerval of periodical update of superblocks (in seconds) */
#घोषणा NILFS_SB_FREQ		10

अटल अंतरभूत पूर्णांक nilfs_sb_need_update(काष्ठा the_nilfs *nilfs)
अणु
	u64 t = kसमय_get_real_seconds();

	वापस t < nilfs->ns_sbwसमय ||
		t > nilfs->ns_sbwसमय + nilfs->ns_sb_update_freq;
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_sb_will_flip(काष्ठा the_nilfs *nilfs)
अणु
	पूर्णांक flip_bits = nilfs->ns_sbwcount & 0x0FL;

	वापस (flip_bits != 0x08 && flip_bits != 0x0F);
पूर्ण

व्योम nilfs_set_last_segment(काष्ठा the_nilfs *, sector_t, u64, __u64);
काष्ठा the_nilfs *alloc_nilfs(काष्ठा super_block *sb);
व्योम destroy_nilfs(काष्ठा the_nilfs *nilfs);
पूर्णांक init_nilfs(काष्ठा the_nilfs *nilfs, काष्ठा super_block *sb, अक्षर *data);
पूर्णांक load_nilfs(काष्ठा the_nilfs *nilfs, काष्ठा super_block *sb);
अचिन्हित दीर्घ nilfs_nrsvsegs(काष्ठा the_nilfs *nilfs, अचिन्हित दीर्घ nsegs);
व्योम nilfs_set_nsegments(काष्ठा the_nilfs *nilfs, अचिन्हित दीर्घ nsegs);
पूर्णांक nilfs_discard_segments(काष्ठा the_nilfs *, __u64 *, माप_प्रकार);
पूर्णांक nilfs_count_मुक्त_blocks(काष्ठा the_nilfs *, sector_t *);
काष्ठा nilfs_root *nilfs_lookup_root(काष्ठा the_nilfs *nilfs, __u64 cno);
काष्ठा nilfs_root *nilfs_find_or_create_root(काष्ठा the_nilfs *nilfs,
					     __u64 cno);
व्योम nilfs_put_root(काष्ठा nilfs_root *root);
पूर्णांक nilfs_near_disk_full(काष्ठा the_nilfs *);
व्योम nilfs_fall_back_super_block(काष्ठा the_nilfs *);
व्योम nilfs_swap_super_block(काष्ठा the_nilfs *);


अटल अंतरभूत व्योम nilfs_get_root(काष्ठा nilfs_root *root)
अणु
	refcount_inc(&root->count);
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_valid_fs(काष्ठा the_nilfs *nilfs)
अणु
	अचिन्हित पूर्णांक valid_fs;

	करोwn_पढ़ो(&nilfs->ns_sem);
	valid_fs = (nilfs->ns_mount_state & NILFS_VALID_FS);
	up_पढ़ो(&nilfs->ns_sem);
	वापस valid_fs;
पूर्ण

अटल अंतरभूत व्योम
nilfs_get_segment_range(काष्ठा the_nilfs *nilfs, __u64 segnum,
			sector_t *seg_start, sector_t *seg_end)
अणु
	*seg_start = (sector_t)nilfs->ns_blocks_per_segment * segnum;
	*seg_end = *seg_start + nilfs->ns_blocks_per_segment - 1;
	अगर (segnum == 0)
		*seg_start = nilfs->ns_first_data_block;
पूर्ण

अटल अंतरभूत sector_t
nilfs_get_segment_start_blocknr(काष्ठा the_nilfs *nilfs, __u64 segnum)
अणु
	वापस (segnum == 0) ? nilfs->ns_first_data_block :
		(sector_t)nilfs->ns_blocks_per_segment * segnum;
पूर्ण

अटल अंतरभूत __u64
nilfs_get_segnum_of_block(काष्ठा the_nilfs *nilfs, sector_t blocknr)
अणु
	sector_t segnum = blocknr;

	sector_भाग(segnum, nilfs->ns_blocks_per_segment);
	वापस segnum;
पूर्ण

अटल अंतरभूत व्योम
nilfs_terminate_segment(काष्ठा the_nilfs *nilfs, sector_t seg_start,
			sector_t seg_end)
अणु
	/* terminate the current full segment (used in हाल of I/O-error) */
	nilfs->ns_pseg_offset = seg_end - seg_start + 1;
पूर्ण

अटल अंतरभूत व्योम nilfs_shअगरt_to_next_segment(काष्ठा the_nilfs *nilfs)
अणु
	/* move क्रमward with a full segment */
	nilfs->ns_segnum = nilfs->ns_nextnum;
	nilfs->ns_pseg_offset = 0;
	nilfs->ns_seg_seq++;
पूर्ण

अटल अंतरभूत __u64 nilfs_last_cno(काष्ठा the_nilfs *nilfs)
अणु
	__u64 cno;

	spin_lock(&nilfs->ns_last_segment_lock);
	cno = nilfs->ns_last_cno;
	spin_unlock(&nilfs->ns_last_segment_lock);
	वापस cno;
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_segment_is_active(काष्ठा the_nilfs *nilfs, __u64 n)
अणु
	वापस n == nilfs->ns_segnum || n == nilfs->ns_nextnum;
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_flush_device(काष्ठा the_nilfs *nilfs)
अणु
	पूर्णांक err;

	अगर (!nilfs_test_opt(nilfs, BARRIER) || nilfs->ns_flushed_device)
		वापस 0;

	nilfs->ns_flushed_device = 1;
	/*
	 * the store to ns_flushed_device must not be reordered after
	 * blkdev_issue_flush().
	 */
	smp_wmb();

	err = blkdev_issue_flush(nilfs->ns_bdev);
	अगर (err != -EIO)
		err = 0;
	वापस err;
पूर्ण

#पूर्ण_अगर /* _THE_NILFS_H */
