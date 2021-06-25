<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * the_nilfs.c - the_nilfs shared काष्ठाure.
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 *
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/crc32.h>
#समावेश "nilfs.h"
#समावेश "segment.h"
#समावेश "alloc.h"
#समावेश "cpfile.h"
#समावेश "sufile.h"
#समावेश "dat.h"
#समावेश "segbuf.h"


अटल पूर्णांक nilfs_valid_sb(काष्ठा nilfs_super_block *sbp);

व्योम nilfs_set_last_segment(काष्ठा the_nilfs *nilfs,
			    sector_t start_blocknr, u64 seq, __u64 cno)
अणु
	spin_lock(&nilfs->ns_last_segment_lock);
	nilfs->ns_last_pseg = start_blocknr;
	nilfs->ns_last_seq = seq;
	nilfs->ns_last_cno = cno;

	अगर (!nilfs_sb_dirty(nilfs)) अणु
		अगर (nilfs->ns_prev_seq == nilfs->ns_last_seq)
			जाओ stay_cursor;

		set_nilfs_sb_dirty(nilfs);
	पूर्ण
	nilfs->ns_prev_seq = nilfs->ns_last_seq;

 stay_cursor:
	spin_unlock(&nilfs->ns_last_segment_lock);
पूर्ण

/**
 * alloc_nilfs - allocate a nilfs object
 * @sb: super block instance
 *
 * Return Value: On success, poपूर्णांकer to the_nilfs is वापसed.
 * On error, शून्य is वापसed.
 */
काष्ठा the_nilfs *alloc_nilfs(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs;

	nilfs = kzalloc(माप(*nilfs), GFP_KERNEL);
	अगर (!nilfs)
		वापस शून्य;

	nilfs->ns_sb = sb;
	nilfs->ns_bdev = sb->s_bdev;
	atomic_set(&nilfs->ns_ndirtyblks, 0);
	init_rwsem(&nilfs->ns_sem);
	mutex_init(&nilfs->ns_snapshot_mount_mutex);
	INIT_LIST_HEAD(&nilfs->ns_dirty_files);
	INIT_LIST_HEAD(&nilfs->ns_gc_inodes);
	spin_lock_init(&nilfs->ns_inode_lock);
	spin_lock_init(&nilfs->ns_next_gen_lock);
	spin_lock_init(&nilfs->ns_last_segment_lock);
	nilfs->ns_cptree = RB_ROOT;
	spin_lock_init(&nilfs->ns_cptree_lock);
	init_rwsem(&nilfs->ns_segctor_sem);
	nilfs->ns_sb_update_freq = NILFS_SB_FREQ;

	वापस nilfs;
पूर्ण

/**
 * destroy_nilfs - destroy nilfs object
 * @nilfs: nilfs object to be released
 */
व्योम destroy_nilfs(काष्ठा the_nilfs *nilfs)
अणु
	might_sleep();
	अगर (nilfs_init(nilfs)) अणु
		nilfs_sysfs_delete_device_group(nilfs);
		brअन्यथा(nilfs->ns_sbh[0]);
		brअन्यथा(nilfs->ns_sbh[1]);
	पूर्ण
	kमुक्त(nilfs);
पूर्ण

अटल पूर्णांक nilfs_load_super_root(काष्ठा the_nilfs *nilfs,
				 काष्ठा super_block *sb, sector_t sr_block)
अणु
	काष्ठा buffer_head *bh_sr;
	काष्ठा nilfs_super_root *raw_sr;
	काष्ठा nilfs_super_block **sbp = nilfs->ns_sbp;
	काष्ठा nilfs_inode *rawi;
	अचिन्हित पूर्णांक dat_entry_size, segment_usage_size, checkpoपूर्णांक_size;
	अचिन्हित पूर्णांक inode_size;
	पूर्णांक err;

	err = nilfs_पढ़ो_super_root_block(nilfs, sr_block, &bh_sr, 1);
	अगर (unlikely(err))
		वापस err;

	करोwn_पढ़ो(&nilfs->ns_sem);
	dat_entry_size = le16_to_cpu(sbp[0]->s_dat_entry_size);
	checkpoपूर्णांक_size = le16_to_cpu(sbp[0]->s_checkpoपूर्णांक_size);
	segment_usage_size = le16_to_cpu(sbp[0]->s_segment_usage_size);
	up_पढ़ो(&nilfs->ns_sem);

	inode_size = nilfs->ns_inode_size;

	rawi = (व्योम *)bh_sr->b_data + NILFS_SR_DAT_OFFSET(inode_size);
	err = nilfs_dat_पढ़ो(sb, dat_entry_size, rawi, &nilfs->ns_dat);
	अगर (err)
		जाओ failed;

	rawi = (व्योम *)bh_sr->b_data + NILFS_SR_CPखाता_OFFSET(inode_size);
	err = nilfs_cpfile_पढ़ो(sb, checkpoपूर्णांक_size, rawi, &nilfs->ns_cpfile);
	अगर (err)
		जाओ failed_dat;

	rawi = (व्योम *)bh_sr->b_data + NILFS_SR_SUखाता_OFFSET(inode_size);
	err = nilfs_sufile_पढ़ो(sb, segment_usage_size, rawi,
				&nilfs->ns_sufile);
	अगर (err)
		जाओ failed_cpfile;

	raw_sr = (काष्ठा nilfs_super_root *)bh_sr->b_data;
	nilfs->ns_nongc_स_समय = le64_to_cpu(raw_sr->sr_nongc_स_समय);

 failed:
	brअन्यथा(bh_sr);
	वापस err;

 failed_cpfile:
	iput(nilfs->ns_cpfile);

 failed_dat:
	iput(nilfs->ns_dat);
	जाओ failed;
पूर्ण

अटल व्योम nilfs_init_recovery_info(काष्ठा nilfs_recovery_info *ri)
अणु
	स_रखो(ri, 0, माप(*ri));
	INIT_LIST_HEAD(&ri->ri_used_segments);
पूर्ण

अटल व्योम nilfs_clear_recovery_info(काष्ठा nilfs_recovery_info *ri)
अणु
	nilfs_dispose_segment_list(&ri->ri_used_segments);
पूर्ण

/**
 * nilfs_store_log_cursor - load log cursor from a super block
 * @nilfs: nilfs object
 * @sbp: buffer storing super block to be पढ़ो
 *
 * nilfs_store_log_cursor() पढ़ोs the last position of the log
 * containing a super root from a given super block, and initializes
 * relevant inक्रमmation on the nilfs object preparatory क्रम log
 * scanning and recovery.
 */
अटल पूर्णांक nilfs_store_log_cursor(काष्ठा the_nilfs *nilfs,
				  काष्ठा nilfs_super_block *sbp)
अणु
	पूर्णांक ret = 0;

	nilfs->ns_last_pseg = le64_to_cpu(sbp->s_last_pseg);
	nilfs->ns_last_cno = le64_to_cpu(sbp->s_last_cno);
	nilfs->ns_last_seq = le64_to_cpu(sbp->s_last_seq);

	nilfs->ns_prev_seq = nilfs->ns_last_seq;
	nilfs->ns_seg_seq = nilfs->ns_last_seq;
	nilfs->ns_segnum =
		nilfs_get_segnum_of_block(nilfs, nilfs->ns_last_pseg);
	nilfs->ns_cno = nilfs->ns_last_cno + 1;
	अगर (nilfs->ns_segnum >= nilfs->ns_nsegments) अणु
		nilfs_err(nilfs->ns_sb,
			  "pointed segment number is out of range: segnum=%llu, nsegments=%lu",
			  (अचिन्हित दीर्घ दीर्घ)nilfs->ns_segnum,
			  nilfs->ns_nsegments);
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * load_nilfs - load and recover the nilfs
 * @nilfs: the_nilfs काष्ठाure to be released
 * @sb: super block instance used to recover past segment
 *
 * load_nilfs() searches and load the latest super root,
 * attaches the last segment, and करोes recovery अगर needed.
 * The caller must call this exclusively क्रम simultaneous mounts.
 */
पूर्णांक load_nilfs(काष्ठा the_nilfs *nilfs, काष्ठा super_block *sb)
अणु
	काष्ठा nilfs_recovery_info ri;
	अचिन्हित पूर्णांक s_flags = sb->s_flags;
	पूर्णांक really_पढ़ो_only = bdev_पढ़ो_only(nilfs->ns_bdev);
	पूर्णांक valid_fs = nilfs_valid_fs(nilfs);
	पूर्णांक err;

	अगर (!valid_fs) अणु
		nilfs_warn(sb, "mounting unchecked fs");
		अगर (s_flags & SB_RDONLY) अणु
			nilfs_info(sb,
				   "recovery required for readonly filesystem");
			nilfs_info(sb,
				   "write access will be enabled during recovery");
		पूर्ण
	पूर्ण

	nilfs_init_recovery_info(&ri);

	err = nilfs_search_super_root(nilfs, &ri);
	अगर (unlikely(err)) अणु
		काष्ठा nilfs_super_block **sbp = nilfs->ns_sbp;
		पूर्णांक blocksize;

		अगर (err != -EINVAL)
			जाओ scan_error;

		अगर (!nilfs_valid_sb(sbp[1])) अणु
			nilfs_warn(sb,
				   "unable to fall back to spare super block");
			जाओ scan_error;
		पूर्ण
		nilfs_info(sb, "trying rollback from an earlier position");

		/*
		 * restore super block with its spare and reconfigure
		 * relevant states of the nilfs object.
		 */
		स_नकल(sbp[0], sbp[1], nilfs->ns_sbsize);
		nilfs->ns_crc_seed = le32_to_cpu(sbp[0]->s_crc_seed);
		nilfs->ns_sbwसमय = le64_to_cpu(sbp[0]->s_wसमय);

		/* verअगरy consistency between two super blocks */
		blocksize = BLOCK_SIZE << le32_to_cpu(sbp[0]->s_log_block_size);
		अगर (blocksize != nilfs->ns_blocksize) अणु
			nilfs_warn(sb,
				   "blocksize differs between two super blocks (%d != %d)",
				   blocksize, nilfs->ns_blocksize);
			जाओ scan_error;
		पूर्ण

		err = nilfs_store_log_cursor(nilfs, sbp[0]);
		अगर (err)
			जाओ scan_error;

		/* drop clean flag to allow roll-क्रमward and recovery */
		nilfs->ns_mount_state &= ~NILFS_VALID_FS;
		valid_fs = 0;

		err = nilfs_search_super_root(nilfs, &ri);
		अगर (err)
			जाओ scan_error;
	पूर्ण

	err = nilfs_load_super_root(nilfs, sb, ri.ri_super_root);
	अगर (unlikely(err)) अणु
		nilfs_err(sb, "error %d while loading super root", err);
		जाओ failed;
	पूर्ण

	अगर (valid_fs)
		जाओ skip_recovery;

	अगर (s_flags & SB_RDONLY) अणु
		__u64 features;

		अगर (nilfs_test_opt(nilfs, NORECOVERY)) अणु
			nilfs_info(sb,
				   "norecovery option specified, skipping roll-forward recovery");
			जाओ skip_recovery;
		पूर्ण
		features = le64_to_cpu(nilfs->ns_sbp[0]->s_feature_compat_ro) &
			~NILFS_FEATURE_COMPAT_RO_SUPP;
		अगर (features) अणु
			nilfs_err(sb,
				  "couldn't proceed with recovery because of unsupported optional features (%llx)",
				  (अचिन्हित दीर्घ दीर्घ)features);
			err = -EROFS;
			जाओ failed_unload;
		पूर्ण
		अगर (really_पढ़ो_only) अणु
			nilfs_err(sb,
				  "write access unavailable, cannot proceed");
			err = -EROFS;
			जाओ failed_unload;
		पूर्ण
		sb->s_flags &= ~SB_RDONLY;
	पूर्ण अन्यथा अगर (nilfs_test_opt(nilfs, NORECOVERY)) अणु
		nilfs_err(sb,
			  "recovery cancelled because norecovery option was specified for a read/write mount");
		err = -EINVAL;
		जाओ failed_unload;
	पूर्ण

	err = nilfs_salvage_orphan_logs(nilfs, sb, &ri);
	अगर (err)
		जाओ failed_unload;

	करोwn_ग_लिखो(&nilfs->ns_sem);
	nilfs->ns_mount_state |= NILFS_VALID_FS; /* set "clean" flag */
	err = nilfs_cleanup_super(sb);
	up_ग_लिखो(&nilfs->ns_sem);

	अगर (err) अणु
		nilfs_err(sb,
			  "error %d updating super block. recovery unfinished.",
			  err);
		जाओ failed_unload;
	पूर्ण
	nilfs_info(sb, "recovery complete");

 skip_recovery:
	nilfs_clear_recovery_info(&ri);
	sb->s_flags = s_flags;
	वापस 0;

 scan_error:
	nilfs_err(sb, "error %d while searching super root", err);
	जाओ failed;

 failed_unload:
	iput(nilfs->ns_cpfile);
	iput(nilfs->ns_sufile);
	iput(nilfs->ns_dat);

 failed:
	nilfs_clear_recovery_info(&ri);
	sb->s_flags = s_flags;
	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ nilfs_max_size(अचिन्हित पूर्णांक blkbits)
अणु
	अचिन्हित पूर्णांक max_bits;
	अचिन्हित दीर्घ दीर्घ res = MAX_LFS_खाताSIZE; /* page cache limit */

	max_bits = blkbits + NILFS_BMAP_KEY_BIT; /* bmap size limit */
	अगर (max_bits < 64)
		res = min_t(अचिन्हित दीर्घ दीर्घ, res, (1ULL << max_bits) - 1);
	वापस res;
पूर्ण

/**
 * nilfs_nrsvsegs - calculate the number of reserved segments
 * @nilfs: nilfs object
 * @nsegs: total number of segments
 */
अचिन्हित दीर्घ nilfs_nrsvsegs(काष्ठा the_nilfs *nilfs, अचिन्हित दीर्घ nsegs)
अणु
	वापस max_t(अचिन्हित दीर्घ, NILFS_MIN_NRSVSEGS,
		     DIV_ROUND_UP(nsegs * nilfs->ns_r_segments_percentage,
				  100));
पूर्ण

व्योम nilfs_set_nsegments(काष्ठा the_nilfs *nilfs, अचिन्हित दीर्घ nsegs)
अणु
	nilfs->ns_nsegments = nsegs;
	nilfs->ns_nrsvsegs = nilfs_nrsvsegs(nilfs, nsegs);
पूर्ण

अटल पूर्णांक nilfs_store_disk_layout(काष्ठा the_nilfs *nilfs,
				   काष्ठा nilfs_super_block *sbp)
अणु
	अगर (le32_to_cpu(sbp->s_rev_level) < NILFS_MIN_SUPP_REV) अणु
		nilfs_err(nilfs->ns_sb,
			  "unsupported revision (superblock rev.=%d.%d, current rev.=%d.%d). Please check the version of mkfs.nilfs(2).",
			  le32_to_cpu(sbp->s_rev_level),
			  le16_to_cpu(sbp->s_minor_rev_level),
			  NILFS_CURRENT_REV, NILFS_MINOR_REV);
		वापस -EINVAL;
	पूर्ण
	nilfs->ns_sbsize = le16_to_cpu(sbp->s_bytes);
	अगर (nilfs->ns_sbsize > BLOCK_SIZE)
		वापस -EINVAL;

	nilfs->ns_inode_size = le16_to_cpu(sbp->s_inode_size);
	अगर (nilfs->ns_inode_size > nilfs->ns_blocksize) अणु
		nilfs_err(nilfs->ns_sb, "too large inode size: %d bytes",
			  nilfs->ns_inode_size);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (nilfs->ns_inode_size < NILFS_MIN_INODE_SIZE) अणु
		nilfs_err(nilfs->ns_sb, "too small inode size: %d bytes",
			  nilfs->ns_inode_size);
		वापस -EINVAL;
	पूर्ण

	nilfs->ns_first_ino = le32_to_cpu(sbp->s_first_ino);

	nilfs->ns_blocks_per_segment = le32_to_cpu(sbp->s_blocks_per_segment);
	अगर (nilfs->ns_blocks_per_segment < NILFS_SEG_MIN_BLOCKS) अणु
		nilfs_err(nilfs->ns_sb, "too short segment: %lu blocks",
			  nilfs->ns_blocks_per_segment);
		वापस -EINVAL;
	पूर्ण

	nilfs->ns_first_data_block = le64_to_cpu(sbp->s_first_data_block);
	nilfs->ns_r_segments_percentage =
		le32_to_cpu(sbp->s_r_segments_percentage);
	अगर (nilfs->ns_r_segments_percentage < 1 ||
	    nilfs->ns_r_segments_percentage > 99) अणु
		nilfs_err(nilfs->ns_sb,
			  "invalid reserved segments percentage: %lu",
			  nilfs->ns_r_segments_percentage);
		वापस -EINVAL;
	पूर्ण

	nilfs_set_nsegments(nilfs, le64_to_cpu(sbp->s_nsegments));
	nilfs->ns_crc_seed = le32_to_cpu(sbp->s_crc_seed);
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_valid_sb(काष्ठा nilfs_super_block *sbp)
अणु
	अटल अचिन्हित अक्षर sum[4];
	स्थिर पूर्णांक sumoff = दुरत्व(काष्ठा nilfs_super_block, s_sum);
	माप_प्रकार bytes;
	u32 crc;

	अगर (!sbp || le16_to_cpu(sbp->s_magic) != NILFS_SUPER_MAGIC)
		वापस 0;
	bytes = le16_to_cpu(sbp->s_bytes);
	अगर (bytes < sumoff + 4 || bytes > BLOCK_SIZE)
		वापस 0;
	crc = crc32_le(le32_to_cpu(sbp->s_crc_seed), (अचिन्हित अक्षर *)sbp,
		       sumoff);
	crc = crc32_le(crc, sum, 4);
	crc = crc32_le(crc, (अचिन्हित अक्षर *)sbp + sumoff + 4,
		       bytes - sumoff - 4);
	वापस crc == le32_to_cpu(sbp->s_sum);
पूर्ण

अटल पूर्णांक nilfs_sb2_bad_offset(काष्ठा nilfs_super_block *sbp, u64 offset)
अणु
	वापस offset < ((le64_to_cpu(sbp->s_nsegments) *
			  le32_to_cpu(sbp->s_blocks_per_segment)) <<
			 (le32_to_cpu(sbp->s_log_block_size) + 10));
पूर्ण

अटल व्योम nilfs_release_super_block(काष्ठा the_nilfs *nilfs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (nilfs->ns_sbp[i]) अणु
			brअन्यथा(nilfs->ns_sbh[i]);
			nilfs->ns_sbh[i] = शून्य;
			nilfs->ns_sbp[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम nilfs_fall_back_super_block(काष्ठा the_nilfs *nilfs)
अणु
	brअन्यथा(nilfs->ns_sbh[0]);
	nilfs->ns_sbh[0] = nilfs->ns_sbh[1];
	nilfs->ns_sbp[0] = nilfs->ns_sbp[1];
	nilfs->ns_sbh[1] = शून्य;
	nilfs->ns_sbp[1] = शून्य;
पूर्ण

व्योम nilfs_swap_super_block(काष्ठा the_nilfs *nilfs)
अणु
	काष्ठा buffer_head *tsbh = nilfs->ns_sbh[0];
	काष्ठा nilfs_super_block *tsbp = nilfs->ns_sbp[0];

	nilfs->ns_sbh[0] = nilfs->ns_sbh[1];
	nilfs->ns_sbp[0] = nilfs->ns_sbp[1];
	nilfs->ns_sbh[1] = tsbh;
	nilfs->ns_sbp[1] = tsbp;
पूर्ण

अटल पूर्णांक nilfs_load_super_block(काष्ठा the_nilfs *nilfs,
				  काष्ठा super_block *sb, पूर्णांक blocksize,
				  काष्ठा nilfs_super_block **sbpp)
अणु
	काष्ठा nilfs_super_block **sbp = nilfs->ns_sbp;
	काष्ठा buffer_head **sbh = nilfs->ns_sbh;
	u64 sb2off = NILFS_SB2_OFFSET_BYTES(nilfs->ns_bdev->bd_inode->i_size);
	पूर्णांक valid[2], swp = 0;

	sbp[0] = nilfs_पढ़ो_super_block(sb, NILFS_SB_OFFSET_BYTES, blocksize,
					&sbh[0]);
	sbp[1] = nilfs_पढ़ो_super_block(sb, sb2off, blocksize, &sbh[1]);

	अगर (!sbp[0]) अणु
		अगर (!sbp[1]) अणु
			nilfs_err(sb, "unable to read superblock");
			वापस -EIO;
		पूर्ण
		nilfs_warn(sb,
			   "unable to read primary superblock (blocksize = %d)",
			   blocksize);
	पूर्ण अन्यथा अगर (!sbp[1]) अणु
		nilfs_warn(sb,
			   "unable to read secondary superblock (blocksize = %d)",
			   blocksize);
	पूर्ण

	/*
	 * Compare two super blocks and set 1 in swp अगर the secondary
	 * super block is valid and newer.  Otherwise, set 0 in swp.
	 */
	valid[0] = nilfs_valid_sb(sbp[0]);
	valid[1] = nilfs_valid_sb(sbp[1]);
	swp = valid[1] && (!valid[0] ||
			   le64_to_cpu(sbp[1]->s_last_cno) >
			   le64_to_cpu(sbp[0]->s_last_cno));

	अगर (valid[swp] && nilfs_sb2_bad_offset(sbp[swp], sb2off)) अणु
		brअन्यथा(sbh[1]);
		sbh[1] = शून्य;
		sbp[1] = शून्य;
		valid[1] = 0;
		swp = 0;
	पूर्ण
	अगर (!valid[swp]) अणु
		nilfs_release_super_block(nilfs);
		nilfs_err(sb, "couldn't find nilfs on the device");
		वापस -EINVAL;
	पूर्ण

	अगर (!valid[!swp])
		nilfs_warn(sb,
			   "broken superblock, retrying with spare superblock (blocksize = %d)",
			   blocksize);
	अगर (swp)
		nilfs_swap_super_block(nilfs);

	nilfs->ns_sbwcount = 0;
	nilfs->ns_sbwसमय = le64_to_cpu(sbp[0]->s_wसमय);
	nilfs->ns_prot_seq = le64_to_cpu(sbp[valid[1] & !swp]->s_last_seq);
	*sbpp = sbp[0];
	वापस 0;
पूर्ण

/**
 * init_nilfs - initialize a NILFS instance.
 * @nilfs: the_nilfs काष्ठाure
 * @sb: super block
 * @data: mount options
 *
 * init_nilfs() perक्रमms common initialization per block device (e.g.
 * पढ़ोing the super block, getting disk layout inक्रमmation, initializing
 * shared fields in the_nilfs).
 *
 * Return Value: On success, 0 is वापसed. On error, a negative error
 * code is वापसed.
 */
पूर्णांक init_nilfs(काष्ठा the_nilfs *nilfs, काष्ठा super_block *sb, अक्षर *data)
अणु
	काष्ठा nilfs_super_block *sbp;
	पूर्णांक blocksize;
	पूर्णांक err;

	करोwn_ग_लिखो(&nilfs->ns_sem);

	blocksize = sb_min_blocksize(sb, NILFS_MIN_BLOCK_SIZE);
	अगर (!blocksize) अणु
		nilfs_err(sb, "unable to set blocksize");
		err = -EINVAL;
		जाओ out;
	पूर्ण
	err = nilfs_load_super_block(nilfs, sb, blocksize, &sbp);
	अगर (err)
		जाओ out;

	err = nilfs_store_magic_and_option(sb, sbp, data);
	अगर (err)
		जाओ failed_sbh;

	err = nilfs_check_feature_compatibility(sb, sbp);
	अगर (err)
		जाओ failed_sbh;

	blocksize = BLOCK_SIZE << le32_to_cpu(sbp->s_log_block_size);
	अगर (blocksize < NILFS_MIN_BLOCK_SIZE ||
	    blocksize > NILFS_MAX_BLOCK_SIZE) अणु
		nilfs_err(sb,
			  "couldn't mount because of unsupported filesystem blocksize %d",
			  blocksize);
		err = -EINVAL;
		जाओ failed_sbh;
	पूर्ण
	अगर (sb->s_blocksize != blocksize) अणु
		पूर्णांक hw_blocksize = bdev_logical_block_size(sb->s_bdev);

		अगर (blocksize < hw_blocksize) अणु
			nilfs_err(sb,
				  "blocksize %d too small for device (sector-size = %d)",
				  blocksize, hw_blocksize);
			err = -EINVAL;
			जाओ failed_sbh;
		पूर्ण
		nilfs_release_super_block(nilfs);
		sb_set_blocksize(sb, blocksize);

		err = nilfs_load_super_block(nilfs, sb, blocksize, &sbp);
		अगर (err)
			जाओ out;
			/*
			 * Not to failed_sbh; sbh is released स्वतःmatically
			 * when reloading fails.
			 */
	पूर्ण
	nilfs->ns_blocksize_bits = sb->s_blocksize_bits;
	nilfs->ns_blocksize = blocksize;

	get_अक्रमom_bytes(&nilfs->ns_next_generation,
			 माप(nilfs->ns_next_generation));

	err = nilfs_store_disk_layout(nilfs, sbp);
	अगर (err)
		जाओ failed_sbh;

	sb->s_maxbytes = nilfs_max_size(sb->s_blocksize_bits);

	nilfs->ns_mount_state = le16_to_cpu(sbp->s_state);

	err = nilfs_store_log_cursor(nilfs, sbp);
	अगर (err)
		जाओ failed_sbh;

	err = nilfs_sysfs_create_device_group(sb);
	अगर (err)
		जाओ failed_sbh;

	set_nilfs_init(nilfs);
	err = 0;
 out:
	up_ग_लिखो(&nilfs->ns_sem);
	वापस err;

 failed_sbh:
	nilfs_release_super_block(nilfs);
	जाओ out;
पूर्ण

पूर्णांक nilfs_discard_segments(काष्ठा the_nilfs *nilfs, __u64 *segnump,
			    माप_प्रकार nsegs)
अणु
	sector_t seg_start, seg_end;
	sector_t start = 0, nblocks = 0;
	अचिन्हित पूर्णांक sects_per_block;
	__u64 *sn;
	पूर्णांक ret = 0;

	sects_per_block = (1 << nilfs->ns_blocksize_bits) /
		bdev_logical_block_size(nilfs->ns_bdev);
	क्रम (sn = segnump; sn < segnump + nsegs; sn++) अणु
		nilfs_get_segment_range(nilfs, *sn, &seg_start, &seg_end);

		अगर (!nblocks) अणु
			start = seg_start;
			nblocks = seg_end - seg_start + 1;
		पूर्ण अन्यथा अगर (start + nblocks == seg_start) अणु
			nblocks += seg_end - seg_start + 1;
		पूर्ण अन्यथा अणु
			ret = blkdev_issue_discard(nilfs->ns_bdev,
						   start * sects_per_block,
						   nblocks * sects_per_block,
						   GFP_NOFS, 0);
			अगर (ret < 0)
				वापस ret;
			nblocks = 0;
		पूर्ण
	पूर्ण
	अगर (nblocks)
		ret = blkdev_issue_discard(nilfs->ns_bdev,
					   start * sects_per_block,
					   nblocks * sects_per_block,
					   GFP_NOFS, 0);
	वापस ret;
पूर्ण

पूर्णांक nilfs_count_मुक्त_blocks(काष्ठा the_nilfs *nilfs, sector_t *nblocks)
अणु
	अचिन्हित दीर्घ ncleansegs;

	करोwn_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	ncleansegs = nilfs_sufile_get_ncleansegs(nilfs->ns_sufile);
	up_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	*nblocks = (sector_t)ncleansegs * nilfs->ns_blocks_per_segment;
	वापस 0;
पूर्ण

पूर्णांक nilfs_near_disk_full(काष्ठा the_nilfs *nilfs)
अणु
	अचिन्हित दीर्घ ncleansegs, nincsegs;

	ncleansegs = nilfs_sufile_get_ncleansegs(nilfs->ns_sufile);
	nincsegs = atomic_पढ़ो(&nilfs->ns_ndirtyblks) /
		nilfs->ns_blocks_per_segment + 1;

	वापस ncleansegs <= nilfs->ns_nrsvsegs + nincsegs;
पूर्ण

काष्ठा nilfs_root *nilfs_lookup_root(काष्ठा the_nilfs *nilfs, __u64 cno)
अणु
	काष्ठा rb_node *n;
	काष्ठा nilfs_root *root;

	spin_lock(&nilfs->ns_cptree_lock);
	n = nilfs->ns_cptree.rb_node;
	जबतक (n) अणु
		root = rb_entry(n, काष्ठा nilfs_root, rb_node);

		अगर (cno < root->cno) अणु
			n = n->rb_left;
		पूर्ण अन्यथा अगर (cno > root->cno) अणु
			n = n->rb_right;
		पूर्ण अन्यथा अणु
			refcount_inc(&root->count);
			spin_unlock(&nilfs->ns_cptree_lock);
			वापस root;
		पूर्ण
	पूर्ण
	spin_unlock(&nilfs->ns_cptree_lock);

	वापस शून्य;
पूर्ण

काष्ठा nilfs_root *
nilfs_find_or_create_root(काष्ठा the_nilfs *nilfs, __u64 cno)
अणु
	काष्ठा rb_node **p, *parent;
	काष्ठा nilfs_root *root, *new;
	पूर्णांक err;

	root = nilfs_lookup_root(nilfs, cno);
	अगर (root)
		वापस root;

	new = kzalloc(माप(*root), GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	spin_lock(&nilfs->ns_cptree_lock);

	p = &nilfs->ns_cptree.rb_node;
	parent = शून्य;

	जबतक (*p) अणु
		parent = *p;
		root = rb_entry(parent, काष्ठा nilfs_root, rb_node);

		अगर (cno < root->cno) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (cno > root->cno) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			refcount_inc(&root->count);
			spin_unlock(&nilfs->ns_cptree_lock);
			kमुक्त(new);
			वापस root;
		पूर्ण
	पूर्ण

	new->cno = cno;
	new->अगरile = शून्य;
	new->nilfs = nilfs;
	refcount_set(&new->count, 1);
	atomic64_set(&new->inodes_count, 0);
	atomic64_set(&new->blocks_count, 0);

	rb_link_node(&new->rb_node, parent, p);
	rb_insert_color(&new->rb_node, &nilfs->ns_cptree);

	spin_unlock(&nilfs->ns_cptree_lock);

	err = nilfs_sysfs_create_snapshot_group(new);
	अगर (err) अणु
		kमुक्त(new);
		new = शून्य;
	पूर्ण

	वापस new;
पूर्ण

व्योम nilfs_put_root(काष्ठा nilfs_root *root)
अणु
	अगर (refcount_dec_and_test(&root->count)) अणु
		काष्ठा the_nilfs *nilfs = root->nilfs;

		nilfs_sysfs_delete_snapshot_group(root);

		spin_lock(&nilfs->ns_cptree_lock);
		rb_erase(&root->rb_node, &nilfs->ns_cptree);
		spin_unlock(&nilfs->ns_cptree_lock);
		iput(root->अगरile);

		kमुक्त(root);
	पूर्ण
पूर्ण
