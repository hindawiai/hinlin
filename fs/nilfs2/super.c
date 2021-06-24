<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * super.c - NILFS module and super block management.
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 */
/*
 *  linux/fs/ext2/super.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/inode.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/parser.h>
#समावेश <linux/crc32.h>
#समावेश <linux/vfs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mount.h>
#समावेश "nilfs.h"
#समावेश "export.h"
#समावेश "mdt.h"
#समावेश "alloc.h"
#समावेश "btree.h"
#समावेश "btnode.h"
#समावेश "page.h"
#समावेश "cpfile.h"
#समावेश "sufile.h" /* nilfs_sufile_resize(), nilfs_sufile_set_alloc_range() */
#समावेश "ifile.h"
#समावेश "dat.h"
#समावेश "segment.h"
#समावेश "segbuf.h"

MODULE_AUTHOR("NTT Corp.");
MODULE_DESCRIPTION("A New Implementation of the Log-structured Filesystem "
		   "(NILFS)");
MODULE_LICENSE("GPL");

अटल काष्ठा kmem_cache *nilfs_inode_cachep;
काष्ठा kmem_cache *nilfs_transaction_cachep;
काष्ठा kmem_cache *nilfs_segbuf_cachep;
काष्ठा kmem_cache *nilfs_btree_path_cache;

अटल पूर्णांक nilfs_setup_super(काष्ठा super_block *sb, पूर्णांक is_mount);
अटल पूर्णांक nilfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data);

व्योम __nilfs_msg(काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	पूर्णांक level;

	बहु_शुरू(args, fmt);

	level = prपूर्णांकk_get_level(fmt);
	vaf.fmt = prपूर्णांकk_skip_level(fmt);
	vaf.va = &args;

	अगर (sb)
		prपूर्णांकk("%c%cNILFS (%s): %pV\n",
		       KERN_SOH_ASCII, level, sb->s_id, &vaf);
	अन्यथा
		prपूर्णांकk("%c%cNILFS: %pV\n",
		       KERN_SOH_ASCII, level, &vaf);

	बहु_पूर्ण(args);
पूर्ण

अटल व्योम nilfs_set_error(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_super_block **sbp;

	करोwn_ग_लिखो(&nilfs->ns_sem);
	अगर (!(nilfs->ns_mount_state & NILFS_ERROR_FS)) अणु
		nilfs->ns_mount_state |= NILFS_ERROR_FS;
		sbp = nilfs_prepare_super(sb, 0);
		अगर (likely(sbp)) अणु
			sbp[0]->s_state |= cpu_to_le16(NILFS_ERROR_FS);
			अगर (sbp[1])
				sbp[1]->s_state |= cpu_to_le16(NILFS_ERROR_FS);
			nilfs_commit_super(sb, NILFS_SB_COMMIT_ALL);
		पूर्ण
	पूर्ण
	up_ग_लिखो(&nilfs->ns_sem);
पूर्ण

/**
 * __nilfs_error() - report failure condition on a fileप्रणाली
 *
 * __nilfs_error() sets an ERROR_FS flag on the superblock as well as
 * reporting an error message.  This function should be called when
 * NILFS detects incoherences or defects of meta data on disk.
 *
 * This implements the body of nilfs_error() macro.  Normally,
 * nilfs_error() should be used.  As क्रम sustainable errors such as a
 * single-shot I/O error, nilfs_err() should be used instead.
 *
 * Callers should not add a trailing newline since this will करो it.
 */
व्योम __nilfs_error(काष्ठा super_block *sb, स्थिर अक्षर *function,
		   स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_CRIT "NILFS error (device %s): %s: %pV\n",
	       sb->s_id, function, &vaf);

	बहु_पूर्ण(args);

	अगर (!sb_rकरोnly(sb)) अणु
		nilfs_set_error(sb);

		अगर (nilfs_test_opt(nilfs, ERRORS_RO)) अणु
			prपूर्णांकk(KERN_CRIT "Remounting filesystem read-only\n");
			sb->s_flags |= SB_RDONLY;
		पूर्ण
	पूर्ण

	अगर (nilfs_test_opt(nilfs, ERRORS_PANIC))
		panic("NILFS (device %s): panic forced after error\n",
		      sb->s_id);
पूर्ण

काष्ठा inode *nilfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा nilfs_inode_info *ii;

	ii = kmem_cache_alloc(nilfs_inode_cachep, GFP_NOFS);
	अगर (!ii)
		वापस शून्य;
	ii->i_bh = शून्य;
	ii->i_state = 0;
	ii->i_cno = 0;
	nilfs_mapping_init(&ii->i_btnode_cache, &ii->vfs_inode);
	वापस &ii->vfs_inode;
पूर्ण

अटल व्योम nilfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	अगर (nilfs_is_metadata_file_inode(inode))
		nilfs_mdt_destroy(inode);

	kmem_cache_मुक्त(nilfs_inode_cachep, NILFS_I(inode));
पूर्ण

अटल पूर्णांक nilfs_sync_super(काष्ठा super_block *sb, पूर्णांक flag)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	पूर्णांक err;

 retry:
	set_buffer_dirty(nilfs->ns_sbh[0]);
	अगर (nilfs_test_opt(nilfs, BARRIER)) अणु
		err = __sync_dirty_buffer(nilfs->ns_sbh[0],
					  REQ_SYNC | REQ_PREFLUSH | REQ_FUA);
	पूर्ण अन्यथा अणु
		err = sync_dirty_buffer(nilfs->ns_sbh[0]);
	पूर्ण

	अगर (unlikely(err)) अणु
		nilfs_err(sb, "unable to write superblock: err=%d", err);
		अगर (err == -EIO && nilfs->ns_sbh[1]) अणु
			/*
			 * sbp[0] poपूर्णांकs to newer log than sbp[1],
			 * so copy sbp[0] to sbp[1] to take over sbp[0].
			 */
			स_नकल(nilfs->ns_sbp[1], nilfs->ns_sbp[0],
			       nilfs->ns_sbsize);
			nilfs_fall_back_super_block(nilfs);
			जाओ retry;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा nilfs_super_block *sbp = nilfs->ns_sbp[0];

		nilfs->ns_sbwcount++;

		/*
		 * The latest segment becomes trailable from the position
		 * written in superblock.
		 */
		clear_nilfs_disजारीd(nilfs);

		/* update GC protection क्रम recent segments */
		अगर (nilfs->ns_sbh[1]) अणु
			अगर (flag == NILFS_SB_COMMIT_ALL) अणु
				set_buffer_dirty(nilfs->ns_sbh[1]);
				अगर (sync_dirty_buffer(nilfs->ns_sbh[1]) < 0)
					जाओ out;
			पूर्ण
			अगर (le64_to_cpu(nilfs->ns_sbp[1]->s_last_cno) <
			    le64_to_cpu(nilfs->ns_sbp[0]->s_last_cno))
				sbp = nilfs->ns_sbp[1];
		पूर्ण

		spin_lock(&nilfs->ns_last_segment_lock);
		nilfs->ns_prot_seq = le64_to_cpu(sbp->s_last_seq);
		spin_unlock(&nilfs->ns_last_segment_lock);
	पूर्ण
 out:
	वापस err;
पूर्ण

व्योम nilfs_set_log_cursor(काष्ठा nilfs_super_block *sbp,
			  काष्ठा the_nilfs *nilfs)
अणु
	sector_t nमुक्तblocks;

	/* nilfs->ns_sem must be locked by the caller. */
	nilfs_count_मुक्त_blocks(nilfs, &nमुक्तblocks);
	sbp->s_मुक्त_blocks_count = cpu_to_le64(nमुक्तblocks);

	spin_lock(&nilfs->ns_last_segment_lock);
	sbp->s_last_seq = cpu_to_le64(nilfs->ns_last_seq);
	sbp->s_last_pseg = cpu_to_le64(nilfs->ns_last_pseg);
	sbp->s_last_cno = cpu_to_le64(nilfs->ns_last_cno);
	spin_unlock(&nilfs->ns_last_segment_lock);
पूर्ण

काष्ठा nilfs_super_block **nilfs_prepare_super(काष्ठा super_block *sb,
					       पूर्णांक flip)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_super_block **sbp = nilfs->ns_sbp;

	/* nilfs->ns_sem must be locked by the caller. */
	अगर (sbp[0]->s_magic != cpu_to_le16(NILFS_SUPER_MAGIC)) अणु
		अगर (sbp[1] &&
		    sbp[1]->s_magic == cpu_to_le16(NILFS_SUPER_MAGIC)) अणु
			स_नकल(sbp[0], sbp[1], nilfs->ns_sbsize);
		पूर्ण अन्यथा अणु
			nilfs_crit(sb, "superblock broke");
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (sbp[1] &&
		   sbp[1]->s_magic != cpu_to_le16(NILFS_SUPER_MAGIC)) अणु
		स_नकल(sbp[1], sbp[0], nilfs->ns_sbsize);
	पूर्ण

	अगर (flip && sbp[1])
		nilfs_swap_super_block(nilfs);

	वापस sbp;
पूर्ण

पूर्णांक nilfs_commit_super(काष्ठा super_block *sb, पूर्णांक flag)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_super_block **sbp = nilfs->ns_sbp;
	समय64_t t;

	/* nilfs->ns_sem must be locked by the caller. */
	t = kसमय_get_real_seconds();
	nilfs->ns_sbwसमय = t;
	sbp[0]->s_wसमय = cpu_to_le64(t);
	sbp[0]->s_sum = 0;
	sbp[0]->s_sum = cpu_to_le32(crc32_le(nilfs->ns_crc_seed,
					     (अचिन्हित अक्षर *)sbp[0],
					     nilfs->ns_sbsize));
	अगर (flag == NILFS_SB_COMMIT_ALL && sbp[1]) अणु
		sbp[1]->s_wसमय = sbp[0]->s_wसमय;
		sbp[1]->s_sum = 0;
		sbp[1]->s_sum = cpu_to_le32(crc32_le(nilfs->ns_crc_seed,
					    (अचिन्हित अक्षर *)sbp[1],
					    nilfs->ns_sbsize));
	पूर्ण
	clear_nilfs_sb_dirty(nilfs);
	nilfs->ns_flushed_device = 1;
	/* make sure store to ns_flushed_device cannot be reordered */
	smp_wmb();
	वापस nilfs_sync_super(sb, flag);
पूर्ण

/**
 * nilfs_cleanup_super() - ग_लिखो fileप्रणाली state क्रम cleanup
 * @sb: super block instance to be unmounted or degraded to पढ़ो-only
 *
 * This function restores state flags in the on-disk super block.
 * This will set "clean" flag (i.e. NILFS_VALID_FS) unless the
 * fileप्रणाली was not clean previously.
 */
पूर्णांक nilfs_cleanup_super(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_super_block **sbp;
	पूर्णांक flag = NILFS_SB_COMMIT;
	पूर्णांक ret = -EIO;

	sbp = nilfs_prepare_super(sb, 0);
	अगर (sbp) अणु
		sbp[0]->s_state = cpu_to_le16(nilfs->ns_mount_state);
		nilfs_set_log_cursor(sbp[0], nilfs);
		अगर (sbp[1] && sbp[0]->s_last_cno == sbp[1]->s_last_cno) अणु
			/*
			 * make the "clean" flag also to the opposite
			 * super block अगर both super blocks poपूर्णांक to
			 * the same checkpoपूर्णांक.
			 */
			sbp[1]->s_state = sbp[0]->s_state;
			flag = NILFS_SB_COMMIT_ALL;
		पूर्ण
		ret = nilfs_commit_super(sb, flag);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nilfs_move_2nd_super - relocate secondary super block
 * @sb: super block instance
 * @sb2off: new offset of the secondary super block (in bytes)
 */
अटल पूर्णांक nilfs_move_2nd_super(काष्ठा super_block *sb, loff_t sb2off)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा buffer_head *nsbh;
	काष्ठा nilfs_super_block *nsbp;
	sector_t blocknr, newblocknr;
	अचिन्हित दीर्घ offset;
	पूर्णांक sb2i;  /* array index of the secondary superblock */
	पूर्णांक ret = 0;

	/* nilfs->ns_sem must be locked by the caller. */
	अगर (nilfs->ns_sbh[1] &&
	    nilfs->ns_sbh[1]->b_blocknr > nilfs->ns_first_data_block) अणु
		sb2i = 1;
		blocknr = nilfs->ns_sbh[1]->b_blocknr;
	पूर्ण अन्यथा अगर (nilfs->ns_sbh[0]->b_blocknr > nilfs->ns_first_data_block) अणु
		sb2i = 0;
		blocknr = nilfs->ns_sbh[0]->b_blocknr;
	पूर्ण अन्यथा अणु
		sb2i = -1;
		blocknr = 0;
	पूर्ण
	अगर (sb2i >= 0 && (u64)blocknr << nilfs->ns_blocksize_bits == sb2off)
		जाओ out;  /* super block location is unchanged */

	/* Get new super block buffer */
	newblocknr = sb2off >> nilfs->ns_blocksize_bits;
	offset = sb2off & (nilfs->ns_blocksize - 1);
	nsbh = sb_getblk(sb, newblocknr);
	अगर (!nsbh) अणु
		nilfs_warn(sb,
			   "unable to move secondary superblock to block %llu",
			   (अचिन्हित दीर्घ दीर्घ)newblocknr);
		ret = -EIO;
		जाओ out;
	पूर्ण
	nsbp = (व्योम *)nsbh->b_data + offset;
	स_रखो(nsbp, 0, nilfs->ns_blocksize);

	अगर (sb2i >= 0) अणु
		स_नकल(nsbp, nilfs->ns_sbp[sb2i], nilfs->ns_sbsize);
		brअन्यथा(nilfs->ns_sbh[sb2i]);
		nilfs->ns_sbh[sb2i] = nsbh;
		nilfs->ns_sbp[sb2i] = nsbp;
	पूर्ण अन्यथा अगर (nilfs->ns_sbh[0]->b_blocknr < nilfs->ns_first_data_block) अणु
		/* secondary super block will be restored to index 1 */
		nilfs->ns_sbh[1] = nsbh;
		nilfs->ns_sbp[1] = nsbp;
	पूर्ण अन्यथा अणु
		brअन्यथा(nsbh);
	पूर्ण
out:
	वापस ret;
पूर्ण

/**
 * nilfs_resize_fs - resize the fileप्रणाली
 * @sb: super block instance
 * @newsize: new size of the fileप्रणाली (in bytes)
 */
पूर्णांक nilfs_resize_fs(काष्ठा super_block *sb, __u64 newsize)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_super_block **sbp;
	__u64 devsize, newnsegs;
	loff_t sb2off;
	पूर्णांक ret;

	ret = -दुस्फल;
	devsize = i_size_पढ़ो(sb->s_bdev->bd_inode);
	अगर (newsize > devsize)
		जाओ out;

	/*
	 * Write lock is required to protect some functions depending
	 * on the number of segments, the number of reserved segments,
	 * and so क्रमth.
	 */
	करोwn_ग_लिखो(&nilfs->ns_segctor_sem);

	sb2off = NILFS_SB2_OFFSET_BYTES(newsize);
	newnsegs = sb2off >> nilfs->ns_blocksize_bits;
	करो_भाग(newnsegs, nilfs->ns_blocks_per_segment);

	ret = nilfs_sufile_resize(nilfs->ns_sufile, newnsegs);
	up_ग_लिखो(&nilfs->ns_segctor_sem);
	अगर (ret < 0)
		जाओ out;

	ret = nilfs_स्थिरruct_segment(sb);
	अगर (ret < 0)
		जाओ out;

	करोwn_ग_लिखो(&nilfs->ns_sem);
	nilfs_move_2nd_super(sb, sb2off);
	ret = -EIO;
	sbp = nilfs_prepare_super(sb, 0);
	अगर (likely(sbp)) अणु
		nilfs_set_log_cursor(sbp[0], nilfs);
		/*
		 * Drop NILFS_RESIZE_FS flag क्रम compatibility with
		 * mount-समय resize which may be implemented in a
		 * future release.
		 */
		sbp[0]->s_state = cpu_to_le16(le16_to_cpu(sbp[0]->s_state) &
					      ~NILFS_RESIZE_FS);
		sbp[0]->s_dev_size = cpu_to_le64(newsize);
		sbp[0]->s_nsegments = cpu_to_le64(nilfs->ns_nsegments);
		अगर (sbp[1])
			स_नकल(sbp[1], sbp[0], nilfs->ns_sbsize);
		ret = nilfs_commit_super(sb, NILFS_SB_COMMIT_ALL);
	पूर्ण
	up_ग_लिखो(&nilfs->ns_sem);

	/*
	 * Reset the range of allocatable segments last.  This order
	 * is important in the हाल of expansion because the secondary
	 * superblock must be रक्षित from log ग_लिखो until migration
	 * completes.
	 */
	अगर (!ret)
		nilfs_sufile_set_alloc_range(nilfs->ns_sufile, 0, newnsegs - 1);
out:
	वापस ret;
पूर्ण

अटल व्योम nilfs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;

	nilfs_detach_log_ग_लिखोr(sb);

	अगर (!sb_rकरोnly(sb)) अणु
		करोwn_ग_लिखो(&nilfs->ns_sem);
		nilfs_cleanup_super(sb);
		up_ग_लिखो(&nilfs->ns_sem);
	पूर्ण

	iput(nilfs->ns_sufile);
	iput(nilfs->ns_cpfile);
	iput(nilfs->ns_dat);

	destroy_nilfs(nilfs);
	sb->s_fs_info = शून्य;
पूर्ण

अटल पूर्णांक nilfs_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_super_block **sbp;
	पूर्णांक err = 0;

	/* This function is called when super block should be written back */
	अगर (रुको)
		err = nilfs_स्थिरruct_segment(sb);

	करोwn_ग_लिखो(&nilfs->ns_sem);
	अगर (nilfs_sb_dirty(nilfs)) अणु
		sbp = nilfs_prepare_super(sb, nilfs_sb_will_flip(nilfs));
		अगर (likely(sbp)) अणु
			nilfs_set_log_cursor(sbp[0], nilfs);
			nilfs_commit_super(sb, NILFS_SB_COMMIT);
		पूर्ण
	पूर्ण
	up_ग_लिखो(&nilfs->ns_sem);

	अगर (!err)
		err = nilfs_flush_device(nilfs);

	वापस err;
पूर्ण

पूर्णांक nilfs_attach_checkpoपूर्णांक(काष्ठा super_block *sb, __u64 cno, पूर्णांक curr_mnt,
			    काष्ठा nilfs_root **rootp)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_root *root;
	काष्ठा nilfs_checkpoपूर्णांक *raw_cp;
	काष्ठा buffer_head *bh_cp;
	पूर्णांक err = -ENOMEM;

	root = nilfs_find_or_create_root(
		nilfs, curr_mnt ? NILFS_CPTREE_CURRENT_CNO : cno);
	अगर (!root)
		वापस err;

	अगर (root->अगरile)
		जाओ reuse; /* alपढ़ोy attached checkpoपूर्णांक */

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	err = nilfs_cpfile_get_checkpoपूर्णांक(nilfs->ns_cpfile, cno, 0, &raw_cp,
					  &bh_cp);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT || err == -EINVAL) अणु
			nilfs_err(sb,
				  "Invalid checkpoint (checkpoint number=%llu)",
				  (अचिन्हित दीर्घ दीर्घ)cno);
			err = -EINVAL;
		पूर्ण
		जाओ failed;
	पूर्ण

	err = nilfs_अगरile_पढ़ो(sb, root, nilfs->ns_inode_size,
			       &raw_cp->cp_अगरile_inode, &root->अगरile);
	अगर (err)
		जाओ failed_bh;

	atomic64_set(&root->inodes_count,
			le64_to_cpu(raw_cp->cp_inodes_count));
	atomic64_set(&root->blocks_count,
			le64_to_cpu(raw_cp->cp_blocks_count));

	nilfs_cpfile_put_checkpoपूर्णांक(nilfs->ns_cpfile, cno, bh_cp);

 reuse:
	*rootp = root;
	वापस 0;

 failed_bh:
	nilfs_cpfile_put_checkpoपूर्णांक(nilfs->ns_cpfile, cno, bh_cp);
 failed:
	nilfs_put_root(root);

	वापस err;
पूर्ण

अटल पूर्णांक nilfs_मुक्तze(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	पूर्णांक err;

	अगर (sb_rकरोnly(sb))
		वापस 0;

	/* Mark super block clean */
	करोwn_ग_लिखो(&nilfs->ns_sem);
	err = nilfs_cleanup_super(sb);
	up_ग_लिखो(&nilfs->ns_sem);
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_unमुक्तze(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;

	अगर (sb_rकरोnly(sb))
		वापस 0;

	करोwn_ग_लिखो(&nilfs->ns_sem);
	nilfs_setup_super(sb, false);
	up_ग_लिखो(&nilfs->ns_sem);
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा nilfs_root *root = NILFS_I(d_inode(dentry))->i_root;
	काष्ठा the_nilfs *nilfs = root->nilfs;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);
	अचिन्हित दीर्घ दीर्घ blocks;
	अचिन्हित दीर्घ overhead;
	अचिन्हित दीर्घ nrsvblocks;
	sector_t nमुक्तblocks;
	u64 nmaxinodes, nमुक्तinodes;
	पूर्णांक err;

	/*
	 * Compute all of the segment blocks
	 *
	 * The blocks beक्रमe first segment and after last segment
	 * are excluded.
	 */
	blocks = nilfs->ns_blocks_per_segment * nilfs->ns_nsegments
		- nilfs->ns_first_data_block;
	nrsvblocks = nilfs->ns_nrsvsegs * nilfs->ns_blocks_per_segment;

	/*
	 * Compute the overhead
	 *
	 * When distributing meta data blocks outside segment काष्ठाure,
	 * We must count them as the overhead.
	 */
	overhead = 0;

	err = nilfs_count_मुक्त_blocks(nilfs, &nमुक्तblocks);
	अगर (unlikely(err))
		वापस err;

	err = nilfs_अगरile_count_मुक्त_inodes(root->अगरile,
					    &nmaxinodes, &nमुक्तinodes);
	अगर (unlikely(err)) अणु
		nilfs_warn(sb, "failed to count free inodes: err=%d", err);
		अगर (err == -दुस्फल) अणु
			/*
			 * If nilfs_palloc_count_max_entries() वापसs
			 * -दुस्फल error code then we simply treat
			 * curent inodes count as maximum possible and
			 * zero as मुक्त inodes value.
			 */
			nmaxinodes = atomic64_पढ़ो(&root->inodes_count);
			nमुक्तinodes = 0;
			err = 0;
		पूर्ण अन्यथा
			वापस err;
	पूर्ण

	buf->f_type = NILFS_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = blocks - overhead;
	buf->f_bमुक्त = nमुक्तblocks;
	buf->f_bavail = (buf->f_bमुक्त >= nrsvblocks) ?
		(buf->f_bमुक्त - nrsvblocks) : 0;
	buf->f_files = nmaxinodes;
	buf->f_fमुक्त = nमुक्तinodes;
	buf->f_namelen = NILFS_NAME_LEN;
	buf->f_fsid = u64_to_fsid(id);

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *dentry)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_root *root = NILFS_I(d_inode(dentry))->i_root;

	अगर (!nilfs_test_opt(nilfs, BARRIER))
		seq_माला_दो(seq, ",nobarrier");
	अगर (root->cno != NILFS_CPTREE_CURRENT_CNO)
		seq_म_लिखो(seq, ",cp=%llu", (अचिन्हित दीर्घ दीर्घ)root->cno);
	अगर (nilfs_test_opt(nilfs, ERRORS_PANIC))
		seq_माला_दो(seq, ",errors=panic");
	अगर (nilfs_test_opt(nilfs, ERRORS_CONT))
		seq_माला_दो(seq, ",errors=continue");
	अगर (nilfs_test_opt(nilfs, STRICT_ORDER))
		seq_माला_दो(seq, ",order=strict");
	अगर (nilfs_test_opt(nilfs, NORECOVERY))
		seq_माला_दो(seq, ",norecovery");
	अगर (nilfs_test_opt(nilfs, DISCARD))
		seq_माला_दो(seq, ",discard");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations nilfs_sops = अणु
	.alloc_inode    = nilfs_alloc_inode,
	.मुक्त_inode     = nilfs_मुक्त_inode,
	.dirty_inode    = nilfs_dirty_inode,
	.evict_inode    = nilfs_evict_inode,
	.put_super      = nilfs_put_super,
	.sync_fs        = nilfs_sync_fs,
	.मुक्तze_fs	= nilfs_मुक्तze,
	.unमुक्तze_fs	= nilfs_unमुक्तze,
	.statfs         = nilfs_statfs,
	.remount_fs     = nilfs_remount,
	.show_options = nilfs_show_options
पूर्ण;

क्रमागत अणु
	Opt_err_cont, Opt_err_panic, Opt_err_ro,
	Opt_barrier, Opt_nobarrier, Opt_snapshot, Opt_order, Opt_norecovery,
	Opt_discard, Opt_nodiscard, Opt_err,
पूर्ण;

अटल match_table_t tokens = अणु
	अणुOpt_err_cont, "errors=continue"पूर्ण,
	अणुOpt_err_panic, "errors=panic"पूर्ण,
	अणुOpt_err_ro, "errors=remount-ro"पूर्ण,
	अणुOpt_barrier, "barrier"पूर्ण,
	अणुOpt_nobarrier, "nobarrier"पूर्ण,
	अणुOpt_snapshot, "cp=%u"पूर्ण,
	अणुOpt_order, "order=%s"पूर्ण,
	अणुOpt_norecovery, "norecovery"पूर्ण,
	अणुOpt_discard, "discard"पूर्ण,
	अणुOpt_nodiscard, "nodiscard"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक parse_options(अक्षर *options, काष्ठा super_block *sb, पूर्णांक is_remount)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;

		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_barrier:
			nilfs_set_opt(nilfs, BARRIER);
			अवरोध;
		हाल Opt_nobarrier:
			nilfs_clear_opt(nilfs, BARRIER);
			अवरोध;
		हाल Opt_order:
			अगर (म_भेद(args[0].from, "relaxed") == 0)
				/* Ordered data semantics */
				nilfs_clear_opt(nilfs, STRICT_ORDER);
			अन्यथा अगर (म_भेद(args[0].from, "strict") == 0)
				/* Strict in-order semantics */
				nilfs_set_opt(nilfs, STRICT_ORDER);
			अन्यथा
				वापस 0;
			अवरोध;
		हाल Opt_err_panic:
			nilfs_ग_लिखो_opt(nilfs, ERROR_MODE, ERRORS_PANIC);
			अवरोध;
		हाल Opt_err_ro:
			nilfs_ग_लिखो_opt(nilfs, ERROR_MODE, ERRORS_RO);
			अवरोध;
		हाल Opt_err_cont:
			nilfs_ग_लिखो_opt(nilfs, ERROR_MODE, ERRORS_CONT);
			अवरोध;
		हाल Opt_snapshot:
			अगर (is_remount) अणु
				nilfs_err(sb,
					  "\"%s\" option is invalid for remount",
					  p);
				वापस 0;
			पूर्ण
			अवरोध;
		हाल Opt_norecovery:
			nilfs_set_opt(nilfs, NORECOVERY);
			अवरोध;
		हाल Opt_discard:
			nilfs_set_opt(nilfs, DISCARD);
			अवरोध;
		हाल Opt_nodiscard:
			nilfs_clear_opt(nilfs, DISCARD);
			अवरोध;
		शेष:
			nilfs_err(sb, "unrecognized mount option \"%s\"", p);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम
nilfs_set_शेष_options(काष्ठा super_block *sb,
			  काष्ठा nilfs_super_block *sbp)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;

	nilfs->ns_mount_opt =
		NILFS_MOUNT_ERRORS_RO | NILFS_MOUNT_BARRIER;
पूर्ण

अटल पूर्णांक nilfs_setup_super(काष्ठा super_block *sb, पूर्णांक is_mount)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_super_block **sbp;
	पूर्णांक max_mnt_count;
	पूर्णांक mnt_count;

	/* nilfs->ns_sem must be locked by the caller. */
	sbp = nilfs_prepare_super(sb, 0);
	अगर (!sbp)
		वापस -EIO;

	अगर (!is_mount)
		जाओ skip_mount_setup;

	max_mnt_count = le16_to_cpu(sbp[0]->s_max_mnt_count);
	mnt_count = le16_to_cpu(sbp[0]->s_mnt_count);

	अगर (nilfs->ns_mount_state & NILFS_ERROR_FS) अणु
		nilfs_warn(sb, "mounting fs with errors");
#अगर 0
	पूर्ण अन्यथा अगर (max_mnt_count >= 0 && mnt_count >= max_mnt_count) अणु
		nilfs_warn(sb, "maximal mount count reached");
#पूर्ण_अगर
	पूर्ण
	अगर (!max_mnt_count)
		sbp[0]->s_max_mnt_count = cpu_to_le16(NILFS_DFL_MAX_MNT_COUNT);

	sbp[0]->s_mnt_count = cpu_to_le16(mnt_count + 1);
	sbp[0]->s_mसमय = cpu_to_le64(kसमय_get_real_seconds());

skip_mount_setup:
	sbp[0]->s_state =
		cpu_to_le16(le16_to_cpu(sbp[0]->s_state) & ~NILFS_VALID_FS);
	/* synchronize sbp[1] with sbp[0] */
	अगर (sbp[1])
		स_नकल(sbp[1], sbp[0], nilfs->ns_sbsize);
	वापस nilfs_commit_super(sb, NILFS_SB_COMMIT_ALL);
पूर्ण

काष्ठा nilfs_super_block *nilfs_पढ़ो_super_block(काष्ठा super_block *sb,
						 u64 pos, पूर्णांक blocksize,
						 काष्ठा buffer_head **pbh)
अणु
	अचिन्हित दीर्घ दीर्घ sb_index = pos;
	अचिन्हित दीर्घ offset;

	offset = करो_भाग(sb_index, blocksize);
	*pbh = sb_bपढ़ो(sb, sb_index);
	अगर (!*pbh)
		वापस शून्य;
	वापस (काष्ठा nilfs_super_block *)((अक्षर *)(*pbh)->b_data + offset);
पूर्ण

पूर्णांक nilfs_store_magic_and_option(काष्ठा super_block *sb,
				 काष्ठा nilfs_super_block *sbp,
				 अक्षर *data)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;

	sb->s_magic = le16_to_cpu(sbp->s_magic);

	/* FS independent flags */
#अगर_घोषित NILFS_ATIME_DISABLE
	sb->s_flags |= SB_NOATIME;
#पूर्ण_अगर

	nilfs_set_शेष_options(sb, sbp);

	nilfs->ns_resuid = le16_to_cpu(sbp->s_def_resuid);
	nilfs->ns_resgid = le16_to_cpu(sbp->s_def_resgid);
	nilfs->ns_पूर्णांकerval = le32_to_cpu(sbp->s_c_पूर्णांकerval);
	nilfs->ns_watermark = le32_to_cpu(sbp->s_c_block_max);

	वापस !parse_options(data, sb, 0) ? -EINVAL : 0;
पूर्ण

पूर्णांक nilfs_check_feature_compatibility(काष्ठा super_block *sb,
				      काष्ठा nilfs_super_block *sbp)
अणु
	__u64 features;

	features = le64_to_cpu(sbp->s_feature_incompat) &
		~NILFS_FEATURE_INCOMPAT_SUPP;
	अगर (features) अणु
		nilfs_err(sb,
			  "couldn't mount because of unsupported optional features (%llx)",
			  (अचिन्हित दीर्घ दीर्घ)features);
		वापस -EINVAL;
	पूर्ण
	features = le64_to_cpu(sbp->s_feature_compat_ro) &
		~NILFS_FEATURE_COMPAT_RO_SUPP;
	अगर (!sb_rकरोnly(sb) && features) अणु
		nilfs_err(sb,
			  "couldn't mount RDWR because of unsupported optional features (%llx)",
			  (अचिन्हित दीर्घ दीर्घ)features);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_get_root_dentry(काष्ठा super_block *sb,
				 काष्ठा nilfs_root *root,
				 काष्ठा dentry **root_dentry)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry *dentry;
	पूर्णांक ret = 0;

	inode = nilfs_iget(sb, root, NILFS_ROOT_INO);
	अगर (IS_ERR(inode)) अणु
		ret = PTR_ERR(inode);
		nilfs_err(sb, "error %d getting root inode", ret);
		जाओ out;
	पूर्ण
	अगर (!S_ISसूची(inode->i_mode) || !inode->i_blocks || !inode->i_size) अणु
		iput(inode);
		nilfs_err(sb, "corrupt root inode");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (root->cno == NILFS_CPTREE_CURRENT_CNO) अणु
		dentry = d_find_alias(inode);
		अगर (!dentry) अणु
			dentry = d_make_root(inode);
			अगर (!dentry) अणु
				ret = -ENOMEM;
				जाओ failed_dentry;
			पूर्ण
		पूर्ण अन्यथा अणु
			iput(inode);
		पूर्ण
	पूर्ण अन्यथा अणु
		dentry = d_obtain_root(inode);
		अगर (IS_ERR(dentry)) अणु
			ret = PTR_ERR(dentry);
			जाओ failed_dentry;
		पूर्ण
	पूर्ण
	*root_dentry = dentry;
 out:
	वापस ret;

 failed_dentry:
	nilfs_err(sb, "error %d getting root dentry", ret);
	जाओ out;
पूर्ण

अटल पूर्णांक nilfs_attach_snapshot(काष्ठा super_block *s, __u64 cno,
				 काष्ठा dentry **root_dentry)
अणु
	काष्ठा the_nilfs *nilfs = s->s_fs_info;
	काष्ठा nilfs_root *root;
	पूर्णांक ret;

	mutex_lock(&nilfs->ns_snapshot_mount_mutex);

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	ret = nilfs_cpfile_is_snapshot(nilfs->ns_cpfile, cno);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	अगर (ret < 0) अणु
		ret = (ret == -ENOENT) ? -EINVAL : ret;
		जाओ out;
	पूर्ण अन्यथा अगर (!ret) अणु
		nilfs_err(s,
			  "The specified checkpoint is not a snapshot (checkpoint number=%llu)",
			  (अचिन्हित दीर्घ दीर्घ)cno);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = nilfs_attach_checkpoपूर्णांक(s, cno, false, &root);
	अगर (ret) अणु
		nilfs_err(s,
			  "error %d while loading snapshot (checkpoint number=%llu)",
			  ret, (अचिन्हित दीर्घ दीर्घ)cno);
		जाओ out;
	पूर्ण
	ret = nilfs_get_root_dentry(s, root, root_dentry);
	nilfs_put_root(root);
 out:
	mutex_unlock(&nilfs->ns_snapshot_mount_mutex);
	वापस ret;
पूर्ण

/**
 * nilfs_tree_is_busy() - try to shrink dentries of a checkpoपूर्णांक
 * @root_dentry: root dentry of the tree to be shrunk
 *
 * This function वापसs true अगर the tree was in-use.
 */
अटल bool nilfs_tree_is_busy(काष्ठा dentry *root_dentry)
अणु
	shrink_dcache_parent(root_dentry);
	वापस d_count(root_dentry) > 1;
पूर्ण

पूर्णांक nilfs_checkpoपूर्णांक_is_mounted(काष्ठा super_block *sb, __u64 cno)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_root *root;
	काष्ठा inode *inode;
	काष्ठा dentry *dentry;
	पूर्णांक ret;

	अगर (cno > nilfs->ns_cno)
		वापस false;

	अगर (cno >= nilfs_last_cno(nilfs))
		वापस true;	/* protect recent checkpoपूर्णांकs */

	ret = false;
	root = nilfs_lookup_root(nilfs, cno);
	अगर (root) अणु
		inode = nilfs_ilookup(sb, root, NILFS_ROOT_INO);
		अगर (inode) अणु
			dentry = d_find_alias(inode);
			अगर (dentry) अणु
				ret = nilfs_tree_is_busy(dentry);
				dput(dentry);
			पूर्ण
			iput(inode);
		पूर्ण
		nilfs_put_root(root);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nilfs_fill_super() - initialize a super block instance
 * @sb: super_block
 * @data: mount options
 * @silent: silent mode flag
 *
 * This function is called exclusively by nilfs->ns_mount_mutex.
 * So, the recovery process is रक्षित from other simultaneous mounts.
 */
अटल पूर्णांक
nilfs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा the_nilfs *nilfs;
	काष्ठा nilfs_root *fsroot;
	__u64 cno;
	पूर्णांक err;

	nilfs = alloc_nilfs(sb);
	अगर (!nilfs)
		वापस -ENOMEM;

	sb->s_fs_info = nilfs;

	err = init_nilfs(nilfs, sb, (अक्षर *)data);
	अगर (err)
		जाओ failed_nilfs;

	sb->s_op = &nilfs_sops;
	sb->s_export_op = &nilfs_export_ops;
	sb->s_root = शून्य;
	sb->s_समय_gran = 1;
	sb->s_max_links = NILFS_LINK_MAX;

	sb->s_bdi = bdi_get(sb->s_bdev->bd_bdi);

	err = load_nilfs(nilfs, sb);
	अगर (err)
		जाओ failed_nilfs;

	cno = nilfs_last_cno(nilfs);
	err = nilfs_attach_checkpoपूर्णांक(sb, cno, true, &fsroot);
	अगर (err) अणु
		nilfs_err(sb,
			  "error %d while loading last checkpoint (checkpoint number=%llu)",
			  err, (अचिन्हित दीर्घ दीर्घ)cno);
		जाओ failed_unload;
	पूर्ण

	अगर (!sb_rकरोnly(sb)) अणु
		err = nilfs_attach_log_ग_लिखोr(sb, fsroot);
		अगर (err)
			जाओ failed_checkpoपूर्णांक;
	पूर्ण

	err = nilfs_get_root_dentry(sb, fsroot, &sb->s_root);
	अगर (err)
		जाओ failed_segctor;

	nilfs_put_root(fsroot);

	अगर (!sb_rकरोnly(sb)) अणु
		करोwn_ग_लिखो(&nilfs->ns_sem);
		nilfs_setup_super(sb, true);
		up_ग_लिखो(&nilfs->ns_sem);
	पूर्ण

	वापस 0;

 failed_segctor:
	nilfs_detach_log_ग_लिखोr(sb);

 failed_checkpoपूर्णांक:
	nilfs_put_root(fsroot);

 failed_unload:
	iput(nilfs->ns_sufile);
	iput(nilfs->ns_cpfile);
	iput(nilfs->ns_dat);

 failed_nilfs:
	destroy_nilfs(nilfs);
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	अचिन्हित दीर्घ old_sb_flags;
	अचिन्हित दीर्घ old_mount_opt;
	पूर्णांक err;

	sync_fileप्रणाली(sb);
	old_sb_flags = sb->s_flags;
	old_mount_opt = nilfs->ns_mount_opt;

	अगर (!parse_options(data, sb, 1)) अणु
		err = -EINVAL;
		जाओ restore_opts;
	पूर्ण
	sb->s_flags = (sb->s_flags & ~SB_POSIXACL);

	err = -EINVAL;

	अगर (!nilfs_valid_fs(nilfs)) अणु
		nilfs_warn(sb,
			   "couldn't remount because the filesystem is in an incomplete recovery state");
		जाओ restore_opts;
	पूर्ण

	अगर ((bool)(*flags & SB_RDONLY) == sb_rकरोnly(sb))
		जाओ out;
	अगर (*flags & SB_RDONLY) अणु
		/* Shutting करोwn log ग_लिखोr */
		nilfs_detach_log_ग_लिखोr(sb);
		sb->s_flags |= SB_RDONLY;

		/*
		 * Remounting a valid RW partition RDONLY, so set
		 * the RDONLY flag and then mark the partition as valid again.
		 */
		करोwn_ग_लिखो(&nilfs->ns_sem);
		nilfs_cleanup_super(sb);
		up_ग_लिखो(&nilfs->ns_sem);
	पूर्ण अन्यथा अणु
		__u64 features;
		काष्ठा nilfs_root *root;

		/*
		 * Mounting a RDONLY partition पढ़ो-ग_लिखो, so reपढ़ो and
		 * store the current valid flag.  (It may have been changed
		 * by fsck since we originally mounted the partition.)
		 */
		करोwn_पढ़ो(&nilfs->ns_sem);
		features = le64_to_cpu(nilfs->ns_sbp[0]->s_feature_compat_ro) &
			~NILFS_FEATURE_COMPAT_RO_SUPP;
		up_पढ़ो(&nilfs->ns_sem);
		अगर (features) अणु
			nilfs_warn(sb,
				   "couldn't remount RDWR because of unsupported optional features (%llx)",
				   (अचिन्हित दीर्घ दीर्घ)features);
			err = -EROFS;
			जाओ restore_opts;
		पूर्ण

		sb->s_flags &= ~SB_RDONLY;

		root = NILFS_I(d_inode(sb->s_root))->i_root;
		err = nilfs_attach_log_ग_लिखोr(sb, root);
		अगर (err)
			जाओ restore_opts;

		करोwn_ग_लिखो(&nilfs->ns_sem);
		nilfs_setup_super(sb, true);
		up_ग_लिखो(&nilfs->ns_sem);
	पूर्ण
 out:
	वापस 0;

 restore_opts:
	sb->s_flags = old_sb_flags;
	nilfs->ns_mount_opt = old_mount_opt;
	वापस err;
पूर्ण

काष्ठा nilfs_super_data अणु
	काष्ठा block_device *bdev;
	__u64 cno;
	पूर्णांक flags;
पूर्ण;

अटल पूर्णांक nilfs_parse_snapshot_option(स्थिर अक्षर *option,
				       स्थिर substring_t *arg,
				       काष्ठा nilfs_super_data *sd)
अणु
	अचिन्हित दीर्घ दीर्घ val;
	स्थिर अक्षर *msg = शून्य;
	पूर्णांक err;

	अगर (!(sd->flags & SB_RDONLY)) अणु
		msg = "read-only option is not specified";
		जाओ parse_error;
	पूर्ण

	err = kम_से_अदीर्घl(arg->from, 0, &val);
	अगर (err) अणु
		अगर (err == -दुस्फल)
			msg = "too large checkpoint number";
		अन्यथा
			msg = "malformed argument";
		जाओ parse_error;
	पूर्ण अन्यथा अगर (val == 0) अणु
		msg = "invalid checkpoint number 0";
		जाओ parse_error;
	पूर्ण
	sd->cno = val;
	वापस 0;

parse_error:
	nilfs_err(शून्य, "invalid option \"%s\": %s", option, msg);
	वापस 1;
पूर्ण

/**
 * nilfs_identअगरy - pre-पढ़ो mount options needed to identअगरy mount instance
 * @data: mount options
 * @sd: nilfs_super_data
 */
अटल पूर्णांक nilfs_identअगरy(अक्षर *data, काष्ठा nilfs_super_data *sd)
अणु
	अक्षर *p, *options = data;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक token;
	पूर्णांक ret = 0;

	करो अणु
		p = strsep(&options, ",");
		अगर (p != शून्य && *p) अणु
			token = match_token(p, tokens, args);
			अगर (token == Opt_snapshot)
				ret = nilfs_parse_snapshot_option(p, &args[0],
								  sd);
		पूर्ण
		अगर (!options)
			अवरोध;
		BUG_ON(options == data);
		*(options - 1) = ',';
	पूर्ण जबतक (!ret);
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_set_bdev_super(काष्ठा super_block *s, व्योम *data)
अणु
	s->s_bdev = data;
	s->s_dev = s->s_bdev->bd_dev;
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_test_bdev_super(काष्ठा super_block *s, व्योम *data)
अणु
	वापस (व्योम *)s->s_bdev == data;
पूर्ण

अटल काष्ठा dentry *
nilfs_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags,
	     स्थिर अक्षर *dev_name, व्योम *data)
अणु
	काष्ठा nilfs_super_data sd;
	काष्ठा super_block *s;
	भ_शेषe_t mode = FMODE_READ | FMODE_EXCL;
	काष्ठा dentry *root_dentry;
	पूर्णांक err, s_new = false;

	अगर (!(flags & SB_RDONLY))
		mode |= FMODE_WRITE;

	sd.bdev = blkdev_get_by_path(dev_name, mode, fs_type);
	अगर (IS_ERR(sd.bdev))
		वापस ERR_CAST(sd.bdev);

	sd.cno = 0;
	sd.flags = flags;
	अगर (nilfs_identअगरy((अक्षर *)data, &sd)) अणु
		err = -EINVAL;
		जाओ failed;
	पूर्ण

	/*
	 * once the super is inserted पूर्णांकo the list by sget, s_umount
	 * will protect the lockfs code from trying to start a snapshot
	 * जबतक we are mounting
	 */
	mutex_lock(&sd.bdev->bd_fsमुक्तze_mutex);
	अगर (sd.bdev->bd_fsमुक्तze_count > 0) अणु
		mutex_unlock(&sd.bdev->bd_fsमुक्तze_mutex);
		err = -EBUSY;
		जाओ failed;
	पूर्ण
	s = sget(fs_type, nilfs_test_bdev_super, nilfs_set_bdev_super, flags,
		 sd.bdev);
	mutex_unlock(&sd.bdev->bd_fsमुक्तze_mutex);
	अगर (IS_ERR(s)) अणु
		err = PTR_ERR(s);
		जाओ failed;
	पूर्ण

	अगर (!s->s_root) अणु
		s_new = true;

		/* New superblock instance created */
		s->s_mode = mode;
		snम_लिखो(s->s_id, माप(s->s_id), "%pg", sd.bdev);
		sb_set_blocksize(s, block_size(sd.bdev));

		err = nilfs_fill_super(s, data, flags & SB_SILENT ? 1 : 0);
		अगर (err)
			जाओ failed_super;

		s->s_flags |= SB_ACTIVE;
	पूर्ण अन्यथा अगर (!sd.cno) अणु
		अगर (nilfs_tree_is_busy(s->s_root)) अणु
			अगर ((flags ^ s->s_flags) & SB_RDONLY) अणु
				nilfs_err(s,
					  "the device already has a %s mount.",
					  sb_rकरोnly(s) ? "read-only" : "read/write");
				err = -EBUSY;
				जाओ failed_super;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Try remount to setup mount states अगर the current
			 * tree is not mounted and only snapshots use this sb.
			 */
			err = nilfs_remount(s, &flags, data);
			अगर (err)
				जाओ failed_super;
		पूर्ण
	पूर्ण

	अगर (sd.cno) अणु
		err = nilfs_attach_snapshot(s, sd.cno, &root_dentry);
		अगर (err)
			जाओ failed_super;
	पूर्ण अन्यथा अणु
		root_dentry = dget(s->s_root);
	पूर्ण

	अगर (!s_new)
		blkdev_put(sd.bdev, mode);

	वापस root_dentry;

 failed_super:
	deactivate_locked_super(s);

 failed:
	अगर (!s_new)
		blkdev_put(sd.bdev, mode);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा file_प्रणाली_type nilfs_fs_type = अणु
	.owner    = THIS_MODULE,
	.name     = "nilfs2",
	.mount    = nilfs_mount,
	.समाप्त_sb  = समाप्त_block_super,
	.fs_flags = FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("nilfs2");

अटल व्योम nilfs_inode_init_once(व्योम *obj)
अणु
	काष्ठा nilfs_inode_info *ii = obj;

	INIT_LIST_HEAD(&ii->i_dirty);
#अगर_घोषित CONFIG_NILFS_XATTR
	init_rwsem(&ii->xattr_sem);
#पूर्ण_अगर
	address_space_init_once(&ii->i_btnode_cache);
	ii->i_bmap = &ii->i_bmap_data;
	inode_init_once(&ii->vfs_inode);
पूर्ण

अटल व्योम nilfs_segbuf_init_once(व्योम *obj)
अणु
	स_रखो(obj, 0, माप(काष्ठा nilfs_segment_buffer));
पूर्ण

अटल व्योम nilfs_destroy_cachep(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();

	kmem_cache_destroy(nilfs_inode_cachep);
	kmem_cache_destroy(nilfs_transaction_cachep);
	kmem_cache_destroy(nilfs_segbuf_cachep);
	kmem_cache_destroy(nilfs_btree_path_cache);
पूर्ण

अटल पूर्णांक __init nilfs_init_cachep(व्योम)
अणु
	nilfs_inode_cachep = kmem_cache_create("nilfs2_inode_cache",
			माप(काष्ठा nilfs_inode_info), 0,
			SLAB_RECLAIM_ACCOUNT|SLAB_ACCOUNT,
			nilfs_inode_init_once);
	अगर (!nilfs_inode_cachep)
		जाओ fail;

	nilfs_transaction_cachep = kmem_cache_create("nilfs2_transaction_cache",
			माप(काष्ठा nilfs_transaction_info), 0,
			SLAB_RECLAIM_ACCOUNT, शून्य);
	अगर (!nilfs_transaction_cachep)
		जाओ fail;

	nilfs_segbuf_cachep = kmem_cache_create("nilfs2_segbuf_cache",
			माप(काष्ठा nilfs_segment_buffer), 0,
			SLAB_RECLAIM_ACCOUNT, nilfs_segbuf_init_once);
	अगर (!nilfs_segbuf_cachep)
		जाओ fail;

	nilfs_btree_path_cache = kmem_cache_create("nilfs2_btree_path_cache",
			माप(काष्ठा nilfs_btree_path) * NILFS_BTREE_LEVEL_MAX,
			0, 0, शून्य);
	अगर (!nilfs_btree_path_cache)
		जाओ fail;

	वापस 0;

fail:
	nilfs_destroy_cachep();
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __init init_nilfs_fs(व्योम)
अणु
	पूर्णांक err;

	err = nilfs_init_cachep();
	अगर (err)
		जाओ fail;

	err = nilfs_sysfs_init();
	अगर (err)
		जाओ मुक्त_cachep;

	err = रेजिस्टर_fileप्रणाली(&nilfs_fs_type);
	अगर (err)
		जाओ deinit_sysfs_entry;

	prपूर्णांकk(KERN_INFO "NILFS version 2 loaded\n");
	वापस 0;

deinit_sysfs_entry:
	nilfs_sysfs_निकास();
मुक्त_cachep:
	nilfs_destroy_cachep();
fail:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_nilfs_fs(व्योम)
अणु
	nilfs_destroy_cachep();
	nilfs_sysfs_निकास();
	unरेजिस्टर_fileप्रणाली(&nilfs_fs_type);
पूर्ण

module_init(init_nilfs_fs)
module_निकास(निकास_nilfs_fs)
