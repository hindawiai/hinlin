<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/export.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/module.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/fs_parser.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "bmap.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "inode.h"
#समावेश "recovery.h"
#समावेश "rgrp.h"
#समावेश "super.h"
#समावेश "sys.h"
#समावेश "util.h"
#समावेश "log.h"
#समावेश "quota.h"
#समावेश "dir.h"
#समावेश "meta_io.h"
#समावेश "trace_gfs2.h"
#समावेश "lops.h"

#घोषणा DO 0
#घोषणा UNDO 1

/**
 * gfs2_tune_init - Fill a gfs2_tune काष्ठाure with शेष values
 * @gt: tune
 *
 */

अटल व्योम gfs2_tune_init(काष्ठा gfs2_tune *gt)
अणु
	spin_lock_init(&gt->gt_spin);

	gt->gt_quota_warn_period = 10;
	gt->gt_quota_scale_num = 1;
	gt->gt_quota_scale_den = 1;
	gt->gt_new_files_jdata = 0;
	gt->gt_max_पढ़ोahead = BIT(18);
	gt->gt_complain_secs = 10;
पूर्ण

व्योम मुक्त_sbd(काष्ठा gfs2_sbd *sdp)
अणु
	अगर (sdp->sd_lkstats)
		मुक्त_percpu(sdp->sd_lkstats);
	kमुक्त(sdp);
पूर्ण

अटल काष्ठा gfs2_sbd *init_sbd(काष्ठा super_block *sb)
अणु
	काष्ठा gfs2_sbd *sdp;
	काष्ठा address_space *mapping;

	sdp = kzalloc(माप(काष्ठा gfs2_sbd), GFP_KERNEL);
	अगर (!sdp)
		वापस शून्य;

	sdp->sd_vfs = sb;
	sdp->sd_lkstats = alloc_percpu(काष्ठा gfs2_pcpu_lkstats);
	अगर (!sdp->sd_lkstats)
		जाओ fail;
	sb->s_fs_info = sdp;

	set_bit(SDF_NOJOURNALID, &sdp->sd_flags);
	gfs2_tune_init(&sdp->sd_tune);

	init_रुकोqueue_head(&sdp->sd_glock_रुको);
	init_रुकोqueue_head(&sdp->sd_async_glock_रुको);
	atomic_set(&sdp->sd_glock_disposal, 0);
	init_completion(&sdp->sd_locking_init);
	init_completion(&sdp->sd_wdack);
	spin_lock_init(&sdp->sd_statfs_spin);

	spin_lock_init(&sdp->sd_rindex_spin);
	sdp->sd_rindex_tree.rb_node = शून्य;

	INIT_LIST_HEAD(&sdp->sd_jindex_list);
	spin_lock_init(&sdp->sd_jindex_spin);
	mutex_init(&sdp->sd_jindex_mutex);
	init_completion(&sdp->sd_journal_पढ़ोy);

	INIT_LIST_HEAD(&sdp->sd_quota_list);
	mutex_init(&sdp->sd_quota_mutex);
	mutex_init(&sdp->sd_quota_sync_mutex);
	init_रुकोqueue_head(&sdp->sd_quota_रुको);
	INIT_LIST_HEAD(&sdp->sd_trunc_list);
	spin_lock_init(&sdp->sd_trunc_lock);
	spin_lock_init(&sdp->sd_biपंचांगap_lock);

	INIT_LIST_HEAD(&sdp->sd_sc_inodes_list);

	mapping = &sdp->sd_aspace;

	address_space_init_once(mapping);
	mapping->a_ops = &gfs2_rgrp_aops;
	mapping->host = sb->s_bdev->bd_inode;
	mapping->flags = 0;
	mapping_set_gfp_mask(mapping, GFP_NOFS);
	mapping->निजी_data = शून्य;
	mapping->ग_लिखोback_index = 0;

	spin_lock_init(&sdp->sd_log_lock);
	atomic_set(&sdp->sd_log_pinned, 0);
	INIT_LIST_HEAD(&sdp->sd_log_revokes);
	INIT_LIST_HEAD(&sdp->sd_log_ordered);
	spin_lock_init(&sdp->sd_ordered_lock);

	init_रुकोqueue_head(&sdp->sd_log_रुकोq);
	init_रुकोqueue_head(&sdp->sd_logd_रुकोq);
	spin_lock_init(&sdp->sd_ail_lock);
	INIT_LIST_HEAD(&sdp->sd_ail1_list);
	INIT_LIST_HEAD(&sdp->sd_ail2_list);

	init_rwsem(&sdp->sd_log_flush_lock);
	atomic_set(&sdp->sd_log_in_flight, 0);
	init_रुकोqueue_head(&sdp->sd_log_flush_रुको);
	atomic_set(&sdp->sd_मुक्तze_state, SFS_UNFROZEN);
	mutex_init(&sdp->sd_मुक्तze_mutex);

	वापस sdp;

fail:
	मुक्त_sbd(sdp);
	वापस शून्य;
पूर्ण

/**
 * gfs2_check_sb - Check superblock
 * @sdp: the fileप्रणाली
 * @silent: Don't prपूर्णांक a message अगर the check fails
 *
 * Checks the version code of the FS is one that we understand how to
 * पढ़ो and that the sizes of the various on-disk काष्ठाures have not
 * changed.
 */

अटल पूर्णांक gfs2_check_sb(काष्ठा gfs2_sbd *sdp, पूर्णांक silent)
अणु
	काष्ठा gfs2_sb_host *sb = &sdp->sd_sb;

	अगर (sb->sb_magic != GFS2_MAGIC ||
	    sb->sb_type != GFS2_METATYPE_SB) अणु
		अगर (!silent)
			pr_warn("not a GFS2 filesystem\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sb->sb_fs_क्रमmat < GFS2_FS_FORMAT_MIN ||
	    sb->sb_fs_क्रमmat > GFS2_FS_FORMAT_MAX ||
	    sb->sb_multihost_क्रमmat != GFS2_FORMAT_MULTI) अणु
		fs_warn(sdp, "Unknown on-disk format, unable to mount\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sb->sb_bsize < 512 || sb->sb_bsize > PAGE_SIZE ||
	    (sb->sb_bsize & (sb->sb_bsize - 1))) अणु
		pr_warn("Invalid block size\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम end_bio_io_page(काष्ठा bio *bio)
अणु
	काष्ठा page *page = bio->bi_निजी;

	अगर (!bio->bi_status)
		SetPageUptodate(page);
	अन्यथा
		pr_warn("error %d reading superblock\n", bio->bi_status);
	unlock_page(page);
पूर्ण

अटल व्योम gfs2_sb_in(काष्ठा gfs2_sbd *sdp, स्थिर व्योम *buf)
अणु
	काष्ठा gfs2_sb_host *sb = &sdp->sd_sb;
	काष्ठा super_block *s = sdp->sd_vfs;
	स्थिर काष्ठा gfs2_sb *str = buf;

	sb->sb_magic = be32_to_cpu(str->sb_header.mh_magic);
	sb->sb_type = be32_to_cpu(str->sb_header.mh_type);
	sb->sb_fs_क्रमmat = be32_to_cpu(str->sb_fs_क्रमmat);
	sb->sb_multihost_क्रमmat = be32_to_cpu(str->sb_multihost_क्रमmat);
	sb->sb_bsize = be32_to_cpu(str->sb_bsize);
	sb->sb_bsize_shअगरt = be32_to_cpu(str->sb_bsize_shअगरt);
	sb->sb_master_dir.no_addr = be64_to_cpu(str->sb_master_dir.no_addr);
	sb->sb_master_dir.no_क्रमmal_ino = be64_to_cpu(str->sb_master_dir.no_क्रमmal_ino);
	sb->sb_root_dir.no_addr = be64_to_cpu(str->sb_root_dir.no_addr);
	sb->sb_root_dir.no_क्रमmal_ino = be64_to_cpu(str->sb_root_dir.no_क्रमmal_ino);

	स_नकल(sb->sb_lockproto, str->sb_lockproto, GFS2_LOCKNAME_LEN);
	स_नकल(sb->sb_locktable, str->sb_locktable, GFS2_LOCKNAME_LEN);
	स_नकल(&s->s_uuid, str->sb_uuid, 16);
पूर्ण

/**
 * gfs2_पढ़ो_super - Read the gfs2 super block from disk
 * @sdp: The GFS2 super block
 * @sector: The location of the super block
 * @silent: Don't prपूर्णांक a message अगर the check fails
 *
 * This uses the bio functions to पढ़ो the super block from disk
 * because we want to be 100% sure that we never पढ़ो cached data.
 * A super block is पढ़ो twice only during each GFS2 mount and is
 * never written to by the fileप्रणाली. The first समय its पढ़ो no
 * locks are held, and the only details which are looked at are those
 * relating to the locking protocol. Once locking is up and working,
 * the sb is पढ़ो again under the lock to establish the location of
 * the master directory (contains poपूर्णांकers to journals etc) and the
 * root directory.
 *
 * Returns: 0 on success or error
 */

अटल पूर्णांक gfs2_पढ़ो_super(काष्ठा gfs2_sbd *sdp, sector_t sector, पूर्णांक silent)
अणु
	काष्ठा super_block *sb = sdp->sd_vfs;
	काष्ठा gfs2_sb *p;
	काष्ठा page *page;
	काष्ठा bio *bio;

	page = alloc_page(GFP_NOFS);
	अगर (unlikely(!page))
		वापस -ENOMEM;

	ClearPageUptodate(page);
	ClearPageDirty(page);
	lock_page(page);

	bio = bio_alloc(GFP_NOFS, 1);
	bio->bi_iter.bi_sector = sector * (sb->s_blocksize >> 9);
	bio_set_dev(bio, sb->s_bdev);
	bio_add_page(bio, page, PAGE_SIZE, 0);

	bio->bi_end_io = end_bio_io_page;
	bio->bi_निजी = page;
	bio_set_op_attrs(bio, REQ_OP_READ, REQ_META);
	submit_bio(bio);
	रुको_on_page_locked(page);
	bio_put(bio);
	अगर (!PageUptodate(page)) अणु
		__मुक्त_page(page);
		वापस -EIO;
	पूर्ण
	p = kmap(page);
	gfs2_sb_in(sdp, p);
	kunmap(page);
	__मुक्त_page(page);
	वापस gfs2_check_sb(sdp, silent);
पूर्ण

/**
 * gfs2_पढ़ो_sb - Read super block
 * @sdp: The GFS2 superblock
 * @silent: Don't prपूर्णांक message अगर mount fails
 *
 */

अटल पूर्णांक gfs2_पढ़ो_sb(काष्ठा gfs2_sbd *sdp, पूर्णांक silent)
अणु
	u32 hash_blocks, ind_blocks, leaf_blocks;
	u32 पंचांगp_blocks;
	अचिन्हित पूर्णांक x;
	पूर्णांक error;

	error = gfs2_पढ़ो_super(sdp, GFS2_SB_ADDR >> sdp->sd_fsb2bb_shअगरt, silent);
	अगर (error) अणु
		अगर (!silent)
			fs_err(sdp, "can't read superblock\n");
		वापस error;
	पूर्ण

	sdp->sd_fsb2bb_shअगरt = sdp->sd_sb.sb_bsize_shअगरt -
			       GFS2_BASIC_BLOCK_SHIFT;
	sdp->sd_fsb2bb = BIT(sdp->sd_fsb2bb_shअगरt);
	sdp->sd_diptrs = (sdp->sd_sb.sb_bsize -
			  माप(काष्ठा gfs2_dinode)) / माप(u64);
	sdp->sd_inptrs = (sdp->sd_sb.sb_bsize -
			  माप(काष्ठा gfs2_meta_header)) / माप(u64);
	sdp->sd_ldptrs = (sdp->sd_sb.sb_bsize -
			  माप(काष्ठा gfs2_log_descriptor)) / माप(u64);
	sdp->sd_jbsize = sdp->sd_sb.sb_bsize - माप(काष्ठा gfs2_meta_header);
	sdp->sd_hash_bsize = sdp->sd_sb.sb_bsize / 2;
	sdp->sd_hash_bsize_shअगरt = sdp->sd_sb.sb_bsize_shअगरt - 1;
	sdp->sd_hash_ptrs = sdp->sd_hash_bsize / माप(u64);
	sdp->sd_qc_per_block = (sdp->sd_sb.sb_bsize -
				माप(काष्ठा gfs2_meta_header)) /
			        माप(काष्ठा gfs2_quota_change);
	sdp->sd_blocks_per_biपंचांगap = (sdp->sd_sb.sb_bsize -
				     माप(काष्ठा gfs2_meta_header))
		* GFS2_NBBY; /* not the rgrp biपंचांगap, subsequent biपंचांगaps only */

	/*
	 * We always keep at least one block reserved क्रम revokes in
	 * transactions.  This greatly simplअगरies allocating additional
	 * revoke blocks.
	 */
	atomic_set(&sdp->sd_log_revokes_available, sdp->sd_ldptrs);

	/* Compute maximum reservation required to add a entry to a directory */

	hash_blocks = DIV_ROUND_UP(माप(u64) * BIT(GFS2_सूची_MAX_DEPTH),
			     sdp->sd_jbsize);

	ind_blocks = 0;
	क्रम (पंचांगp_blocks = hash_blocks; पंचांगp_blocks > sdp->sd_diptrs;) अणु
		पंचांगp_blocks = DIV_ROUND_UP(पंचांगp_blocks, sdp->sd_inptrs);
		ind_blocks += पंचांगp_blocks;
	पूर्ण

	leaf_blocks = 2 + GFS2_सूची_MAX_DEPTH;

	sdp->sd_max_dirres = hash_blocks + ind_blocks + leaf_blocks;

	sdp->sd_heightsize[0] = sdp->sd_sb.sb_bsize -
				माप(काष्ठा gfs2_dinode);
	sdp->sd_heightsize[1] = sdp->sd_sb.sb_bsize * sdp->sd_diptrs;
	क्रम (x = 2;; x++) अणु
		u64 space, d;
		u32 m;

		space = sdp->sd_heightsize[x - 1] * sdp->sd_inptrs;
		d = space;
		m = करो_भाग(d, sdp->sd_inptrs);

		अगर (d != sdp->sd_heightsize[x - 1] || m)
			अवरोध;
		sdp->sd_heightsize[x] = space;
	पूर्ण
	sdp->sd_max_height = x;
	sdp->sd_heightsize[x] = ~0;
	gfs2_निश्चित(sdp, sdp->sd_max_height <= GFS2_MAX_META_HEIGHT);

	sdp->sd_max_dents_per_leaf = (sdp->sd_sb.sb_bsize -
				      माप(काष्ठा gfs2_leaf)) /
				     GFS2_MIN_सूचीENT_SIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक init_names(काष्ठा gfs2_sbd *sdp, पूर्णांक silent)
अणु
	अक्षर *proto, *table;
	पूर्णांक error = 0;

	proto = sdp->sd_args.ar_lockproto;
	table = sdp->sd_args.ar_locktable;

	/*  Try to स्वतःdetect  */

	अगर (!proto[0] || !table[0]) अणु
		error = gfs2_पढ़ो_super(sdp, GFS2_SB_ADDR >> sdp->sd_fsb2bb_shअगरt, silent);
		अगर (error)
			वापस error;

		अगर (!proto[0])
			proto = sdp->sd_sb.sb_lockproto;
		अगर (!table[0])
			table = sdp->sd_sb.sb_locktable;
	पूर्ण

	अगर (!table[0])
		table = sdp->sd_vfs->s_id;

	strlcpy(sdp->sd_proto_name, proto, GFS2_FSNAME_LEN);
	strlcpy(sdp->sd_table_name, table, GFS2_FSNAME_LEN);

	table = sdp->sd_table_name;
	जबतक ((table = म_अक्षर(table, '/')))
		*table = '_';

	वापस error;
पूर्ण

अटल पूर्णांक init_locking(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_holder *mount_gh,
			पूर्णांक unकरो)
अणु
	पूर्णांक error = 0;

	अगर (unकरो)
		जाओ fail_trans;

	error = gfs2_glock_nq_num(sdp,
				  GFS2_MOUNT_LOCK, &gfs2_nondisk_glops,
				  LM_ST_EXCLUSIVE, LM_FLAG_NOEXP | GL_NOCACHE,
				  mount_gh);
	अगर (error) अणु
		fs_err(sdp, "can't acquire mount glock: %d\n", error);
		जाओ fail;
	पूर्ण

	error = gfs2_glock_nq_num(sdp,
				  GFS2_LIVE_LOCK, &gfs2_nondisk_glops,
				  LM_ST_SHARED,
				  LM_FLAG_NOEXP | GL_EXACT,
				  &sdp->sd_live_gh);
	अगर (error) अणु
		fs_err(sdp, "can't acquire live glock: %d\n", error);
		जाओ fail_mount;
	पूर्ण

	error = gfs2_glock_get(sdp, GFS2_RENAME_LOCK, &gfs2_nondisk_glops,
			       CREATE, &sdp->sd_नाम_gl);
	अगर (error) अणु
		fs_err(sdp, "can't create rename glock: %d\n", error);
		जाओ fail_live;
	पूर्ण

	error = gfs2_glock_get(sdp, GFS2_FREEZE_LOCK, &gfs2_मुक्तze_glops,
			       CREATE, &sdp->sd_मुक्तze_gl);
	अगर (error) अणु
		fs_err(sdp, "can't create transaction glock: %d\n", error);
		जाओ fail_नाम;
	पूर्ण

	वापस 0;

fail_trans:
	gfs2_glock_put(sdp->sd_मुक्तze_gl);
fail_नाम:
	gfs2_glock_put(sdp->sd_नाम_gl);
fail_live:
	gfs2_glock_dq_uninit(&sdp->sd_live_gh);
fail_mount:
	gfs2_glock_dq_uninit(mount_gh);
fail:
	वापस error;
पूर्ण

अटल पूर्णांक gfs2_lookup_root(काष्ठा super_block *sb, काष्ठा dentry **dptr,
			    u64 no_addr, स्थिर अक्षर *name)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;

	inode = gfs2_inode_lookup(sb, DT_सूची, no_addr, 0,
				  GFS2_BLKST_FREE /* ignore */);
	अगर (IS_ERR(inode)) अणु
		fs_err(sdp, "can't read in %s inode: %ld\n", name, PTR_ERR(inode));
		वापस PTR_ERR(inode);
	पूर्ण
	dentry = d_make_root(inode);
	अगर (!dentry) अणु
		fs_err(sdp, "can't alloc %s dentry\n", name);
		वापस -ENOMEM;
	पूर्ण
	*dptr = dentry;
	वापस 0;
पूर्ण

अटल पूर्णांक init_sb(काष्ठा gfs2_sbd *sdp, पूर्णांक silent)
अणु
	काष्ठा super_block *sb = sdp->sd_vfs;
	काष्ठा gfs2_holder sb_gh;
	u64 no_addr;
	पूर्णांक ret;

	ret = gfs2_glock_nq_num(sdp, GFS2_SB_LOCK, &gfs2_meta_glops,
				LM_ST_SHARED, 0, &sb_gh);
	अगर (ret) अणु
		fs_err(sdp, "can't acquire superblock glock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = gfs2_पढ़ो_sb(sdp, silent);
	अगर (ret) अणु
		fs_err(sdp, "can't read superblock: %d\n", ret);
		जाओ out;
	पूर्ण

	चयन(sdp->sd_sb.sb_fs_क्रमmat) अणु
	हाल GFS2_FS_FORMAT_MAX:
		sb->s_xattr = gfs2_xattr_handlers_max;
		अवरोध;

	हाल GFS2_FS_FORMAT_MIN:
		sb->s_xattr = gfs2_xattr_handlers_min;
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	/* Set up the buffer cache and SB क्रम real */
	अगर (sdp->sd_sb.sb_bsize < bdev_logical_block_size(sb->s_bdev)) अणु
		ret = -EINVAL;
		fs_err(sdp, "FS block size (%u) is too small for device "
		       "block size (%u)\n",
		       sdp->sd_sb.sb_bsize, bdev_logical_block_size(sb->s_bdev));
		जाओ out;
	पूर्ण
	अगर (sdp->sd_sb.sb_bsize > PAGE_SIZE) अणु
		ret = -EINVAL;
		fs_err(sdp, "FS block size (%u) is too big for machine "
		       "page size (%u)\n",
		       sdp->sd_sb.sb_bsize, (अचिन्हित पूर्णांक)PAGE_SIZE);
		जाओ out;
	पूर्ण
	sb_set_blocksize(sb, sdp->sd_sb.sb_bsize);

	/* Get the root inode */
	no_addr = sdp->sd_sb.sb_root_dir.no_addr;
	ret = gfs2_lookup_root(sb, &sdp->sd_root_dir, no_addr, "root");
	अगर (ret)
		जाओ out;

	/* Get the master inode */
	no_addr = sdp->sd_sb.sb_master_dir.no_addr;
	ret = gfs2_lookup_root(sb, &sdp->sd_master_dir, no_addr, "master");
	अगर (ret) अणु
		dput(sdp->sd_root_dir);
		जाओ out;
	पूर्ण
	sb->s_root = dget(sdp->sd_args.ar_meta ? sdp->sd_master_dir : sdp->sd_root_dir);
out:
	gfs2_glock_dq_uninit(&sb_gh);
	वापस ret;
पूर्ण

अटल व्योम gfs2_others_may_mount(काष्ठा gfs2_sbd *sdp)
अणु
	अक्षर *message = "FIRSTMOUNT=Done";
	अक्षर *envp[] = अणु message, शून्य पूर्ण;

	fs_info(sdp, "first mount done, others may mount\n");

	अगर (sdp->sd_lockकाष्ठा.ls_ops->lm_first_करोne)
		sdp->sd_lockकाष्ठा.ls_ops->lm_first_करोne(sdp);

	kobject_uevent_env(&sdp->sd_kobj, KOBJ_CHANGE, envp);
पूर्ण

/**
 * gfs2_jindex_hold - Grab a lock on the jindex
 * @sdp: The GFS2 superblock
 * @ji_gh: the holder क्रम the jindex glock
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_jindex_hold(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_holder *ji_gh)
अणु
	काष्ठा gfs2_inode *dip = GFS2_I(sdp->sd_jindex);
	काष्ठा qstr name;
	अक्षर buf[20];
	काष्ठा gfs2_jdesc *jd;
	पूर्णांक error;

	name.name = buf;

	mutex_lock(&sdp->sd_jindex_mutex);

	क्रम (;;) अणु
		काष्ठा gfs2_inode *jip;

		error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, ji_gh);
		अगर (error)
			अवरोध;

		name.len = प्र_लिखो(buf, "journal%u", sdp->sd_journals);
		name.hash = gfs2_disk_hash(name.name, name.len);

		error = gfs2_dir_check(sdp->sd_jindex, &name, शून्य);
		अगर (error == -ENOENT) अणु
			error = 0;
			अवरोध;
		पूर्ण

		gfs2_glock_dq_uninit(ji_gh);

		अगर (error)
			अवरोध;

		error = -ENOMEM;
		jd = kzalloc(माप(काष्ठा gfs2_jdesc), GFP_KERNEL);
		अगर (!jd)
			अवरोध;

		INIT_LIST_HEAD(&jd->extent_list);
		INIT_LIST_HEAD(&jd->jd_revoke_list);

		INIT_WORK(&jd->jd_work, gfs2_recover_func);
		jd->jd_inode = gfs2_lookupi(sdp->sd_jindex, &name, 1);
		अगर (IS_ERR_OR_शून्य(jd->jd_inode)) अणु
			अगर (!jd->jd_inode)
				error = -ENOENT;
			अन्यथा
				error = PTR_ERR(jd->jd_inode);
			kमुक्त(jd);
			अवरोध;
		पूर्ण

		spin_lock(&sdp->sd_jindex_spin);
		jd->jd_jid = sdp->sd_journals++;
		jip = GFS2_I(jd->jd_inode);
		jd->jd_no_addr = jip->i_no_addr;
		list_add_tail(&jd->jd_list, &sdp->sd_jindex_list);
		spin_unlock(&sdp->sd_jindex_spin);
	पूर्ण

	mutex_unlock(&sdp->sd_jindex_mutex);

	वापस error;
पूर्ण

/**
 * init_statfs - look up and initialize master and local (per node) statfs inodes
 * @sdp: The GFS2 superblock
 *
 * This should be called after the jindex is initialized in init_journal() and
 * beक्रमe gfs2_journal_recovery() is called because we need to be able to ग_लिखो
 * to these inodes during recovery.
 *
 * Returns: त्रुटि_सं
 */
अटल पूर्णांक init_statfs(काष्ठा gfs2_sbd *sdp)
अणु
	पूर्णांक error = 0;
	काष्ठा inode *master = d_inode(sdp->sd_master_dir);
	काष्ठा inode *pn = शून्य;
	अक्षर buf[30];
	काष्ठा gfs2_jdesc *jd;
	काष्ठा gfs2_inode *ip;

	sdp->sd_statfs_inode = gfs2_lookup_simple(master, "statfs");
	अगर (IS_ERR(sdp->sd_statfs_inode)) अणु
		error = PTR_ERR(sdp->sd_statfs_inode);
		fs_err(sdp, "can't read in statfs inode: %d\n", error);
		जाओ out;
	पूर्ण
	अगर (sdp->sd_args.ar_spectator)
		जाओ out;

	pn = gfs2_lookup_simple(master, "per_node");
	अगर (IS_ERR(pn)) अणु
		error = PTR_ERR(pn);
		fs_err(sdp, "can't find per_node directory: %d\n", error);
		जाओ put_statfs;
	पूर्ण

	/* For each jid, lookup the corresponding local statfs inode in the
	 * per_node metafs directory and save it in the sdp->sd_sc_inodes_list. */
	list_क्रम_each_entry(jd, &sdp->sd_jindex_list, jd_list) अणु
		काष्ठा local_statfs_inode *lsi =
			kदो_स्मृति(माप(काष्ठा local_statfs_inode), GFP_NOFS);
		अगर (!lsi) अणु
			error = -ENOMEM;
			जाओ मुक्त_local;
		पूर्ण
		प्र_लिखो(buf, "statfs_change%u", jd->jd_jid);
		lsi->si_sc_inode = gfs2_lookup_simple(pn, buf);
		अगर (IS_ERR(lsi->si_sc_inode)) अणु
			error = PTR_ERR(lsi->si_sc_inode);
			fs_err(sdp, "can't find local \"sc\" file#%u: %d\n",
			       jd->jd_jid, error);
			जाओ मुक्त_local;
		पूर्ण
		lsi->si_jid = jd->jd_jid;
		अगर (jd->jd_jid == sdp->sd_jdesc->jd_jid)
			sdp->sd_sc_inode = lsi->si_sc_inode;

		list_add_tail(&lsi->si_list, &sdp->sd_sc_inodes_list);
	पूर्ण

	iput(pn);
	ip = GFS2_I(sdp->sd_sc_inode);
	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0,
				   &sdp->sd_sc_gh);
	अगर (error) अणु
		fs_err(sdp, "can't lock local \"sc\" file: %d\n", error);
		जाओ मुक्त_local;
	पूर्ण
	वापस 0;

मुक्त_local:
	मुक्त_local_statfs_inodes(sdp);
	iput(pn);
put_statfs:
	iput(sdp->sd_statfs_inode);
out:
	वापस error;
पूर्ण

/* Uninitialize and मुक्त up memory used by the list of statfs inodes */
अटल व्योम uninit_statfs(काष्ठा gfs2_sbd *sdp)
अणु
	अगर (!sdp->sd_args.ar_spectator) अणु
		gfs2_glock_dq_uninit(&sdp->sd_sc_gh);
		मुक्त_local_statfs_inodes(sdp);
	पूर्ण
	iput(sdp->sd_statfs_inode);
पूर्ण

अटल पूर्णांक init_journal(काष्ठा gfs2_sbd *sdp, पूर्णांक unकरो)
अणु
	काष्ठा inode *master = d_inode(sdp->sd_master_dir);
	काष्ठा gfs2_holder ji_gh;
	काष्ठा gfs2_inode *ip;
	पूर्णांक jindex = 1;
	पूर्णांक error = 0;

	अगर (unकरो) अणु
		jindex = 0;
		जाओ fail_statfs;
	पूर्ण

	sdp->sd_jindex = gfs2_lookup_simple(master, "jindex");
	अगर (IS_ERR(sdp->sd_jindex)) अणु
		fs_err(sdp, "can't lookup journal index: %d\n", error);
		वापस PTR_ERR(sdp->sd_jindex);
	पूर्ण

	/* Load in the journal index special file */

	error = gfs2_jindex_hold(sdp, &ji_gh);
	अगर (error) अणु
		fs_err(sdp, "can't read journal index: %d\n", error);
		जाओ fail;
	पूर्ण

	error = -EUSERS;
	अगर (!gfs2_jindex_size(sdp)) अणु
		fs_err(sdp, "no journals!\n");
		जाओ fail_jindex;
	पूर्ण

	atomic_set(&sdp->sd_log_blks_needed, 0);
	अगर (sdp->sd_args.ar_spectator) अणु
		sdp->sd_jdesc = gfs2_jdesc_find(sdp, 0);
		atomic_set(&sdp->sd_log_blks_मुक्त, sdp->sd_jdesc->jd_blocks);
		atomic_set(&sdp->sd_log_thresh1, 2*sdp->sd_jdesc->jd_blocks/5);
		atomic_set(&sdp->sd_log_thresh2, 4*sdp->sd_jdesc->jd_blocks/5);
	पूर्ण अन्यथा अणु
		अगर (sdp->sd_lockकाष्ठा.ls_jid >= gfs2_jindex_size(sdp)) अणु
			fs_err(sdp, "can't mount journal #%u\n",
			       sdp->sd_lockकाष्ठा.ls_jid);
			fs_err(sdp, "there are only %u journals (0 - %u)\n",
			       gfs2_jindex_size(sdp),
			       gfs2_jindex_size(sdp) - 1);
			जाओ fail_jindex;
		पूर्ण
		sdp->sd_jdesc = gfs2_jdesc_find(sdp, sdp->sd_lockकाष्ठा.ls_jid);

		error = gfs2_glock_nq_num(sdp, sdp->sd_lockकाष्ठा.ls_jid,
					  &gfs2_journal_glops,
					  LM_ST_EXCLUSIVE,
					  LM_FLAG_NOEXP | GL_NOCACHE,
					  &sdp->sd_journal_gh);
		अगर (error) अणु
			fs_err(sdp, "can't acquire journal glock: %d\n", error);
			जाओ fail_jindex;
		पूर्ण

		ip = GFS2_I(sdp->sd_jdesc->jd_inode);
		sdp->sd_jinode_gl = ip->i_gl;
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED,
					   LM_FLAG_NOEXP | GL_EXACT | GL_NOCACHE,
					   &sdp->sd_jinode_gh);
		अगर (error) अणु
			fs_err(sdp, "can't acquire journal inode glock: %d\n",
			       error);
			जाओ fail_journal_gh;
		पूर्ण

		error = gfs2_jdesc_check(sdp->sd_jdesc);
		अगर (error) अणु
			fs_err(sdp, "my journal (%u) is bad: %d\n",
			       sdp->sd_jdesc->jd_jid, error);
			जाओ fail_jinode_gh;
		पूर्ण
		atomic_set(&sdp->sd_log_blks_मुक्त, sdp->sd_jdesc->jd_blocks);
		atomic_set(&sdp->sd_log_thresh1, 2*sdp->sd_jdesc->jd_blocks/5);
		atomic_set(&sdp->sd_log_thresh2, 4*sdp->sd_jdesc->jd_blocks/5);

		/* Map the extents क्रम this journal's blocks */
		gfs2_map_journal_extents(sdp, sdp->sd_jdesc);
	पूर्ण
	trace_gfs2_log_blocks(sdp, atomic_पढ़ो(&sdp->sd_log_blks_मुक्त));

	/* Lookup statfs inodes here so journal recovery can use them. */
	error = init_statfs(sdp);
	अगर (error)
		जाओ fail_jinode_gh;

	अगर (sdp->sd_lockकाष्ठा.ls_first) अणु
		अचिन्हित पूर्णांक x;
		क्रम (x = 0; x < sdp->sd_journals; x++) अणु
			काष्ठा gfs2_jdesc *jd = gfs2_jdesc_find(sdp, x);

			अगर (sdp->sd_args.ar_spectator) अणु
				error = check_journal_clean(sdp, jd, true);
				अगर (error)
					जाओ fail_statfs;
				जारी;
			पूर्ण
			error = gfs2_recover_journal(jd, true);
			अगर (error) अणु
				fs_err(sdp, "error recovering journal %u: %d\n",
				       x, error);
				जाओ fail_statfs;
			पूर्ण
		पूर्ण

		gfs2_others_may_mount(sdp);
	पूर्ण अन्यथा अगर (!sdp->sd_args.ar_spectator) अणु
		error = gfs2_recover_journal(sdp->sd_jdesc, true);
		अगर (error) अणु
			fs_err(sdp, "error recovering my journal: %d\n", error);
			जाओ fail_statfs;
		पूर्ण
	पूर्ण

	sdp->sd_log_idle = 1;
	set_bit(SDF_JOURNAL_CHECKED, &sdp->sd_flags);
	gfs2_glock_dq_uninit(&ji_gh);
	jindex = 0;
	INIT_WORK(&sdp->sd_मुक्तze_work, gfs2_मुक्तze_func);
	वापस 0;

fail_statfs:
	uninit_statfs(sdp);
fail_jinode_gh:
	/* A withdraw may have करोne dq/uninit so now we need to check it */
	अगर (!sdp->sd_args.ar_spectator &&
	    gfs2_holder_initialized(&sdp->sd_jinode_gh))
		gfs2_glock_dq_uninit(&sdp->sd_jinode_gh);
fail_journal_gh:
	अगर (!sdp->sd_args.ar_spectator &&
	    gfs2_holder_initialized(&sdp->sd_journal_gh))
		gfs2_glock_dq_uninit(&sdp->sd_journal_gh);
fail_jindex:
	gfs2_jindex_मुक्त(sdp);
	अगर (jindex)
		gfs2_glock_dq_uninit(&ji_gh);
fail:
	iput(sdp->sd_jindex);
	वापस error;
पूर्ण

अटल काष्ठा lock_class_key gfs2_quota_imutex_key;

अटल पूर्णांक init_inodes(काष्ठा gfs2_sbd *sdp, पूर्णांक unकरो)
अणु
	पूर्णांक error = 0;
	काष्ठा inode *master = d_inode(sdp->sd_master_dir);

	अगर (unकरो)
		जाओ fail_qinode;

	error = init_journal(sdp, unकरो);
	complete_all(&sdp->sd_journal_पढ़ोy);
	अगर (error)
		जाओ fail;

	/* Read in the resource index inode */
	sdp->sd_rindex = gfs2_lookup_simple(master, "rindex");
	अगर (IS_ERR(sdp->sd_rindex)) अणु
		error = PTR_ERR(sdp->sd_rindex);
		fs_err(sdp, "can't get resource index inode: %d\n", error);
		जाओ fail_journal;
	पूर्ण
	sdp->sd_rindex_uptodate = 0;

	/* Read in the quota inode */
	sdp->sd_quota_inode = gfs2_lookup_simple(master, "quota");
	अगर (IS_ERR(sdp->sd_quota_inode)) अणु
		error = PTR_ERR(sdp->sd_quota_inode);
		fs_err(sdp, "can't get quota file inode: %d\n", error);
		जाओ fail_rindex;
	पूर्ण
	/*
	 * i_rwsem on quota files is special. Since this inode is hidden प्रणाली
	 * file, we are safe to define locking ourselves.
	 */
	lockdep_set_class(&sdp->sd_quota_inode->i_rwsem,
			  &gfs2_quota_imutex_key);

	error = gfs2_rindex_update(sdp);
	अगर (error)
		जाओ fail_qinode;

	वापस 0;

fail_qinode:
	iput(sdp->sd_quota_inode);
fail_rindex:
	gfs2_clear_rgrpd(sdp);
	iput(sdp->sd_rindex);
fail_journal:
	init_journal(sdp, UNDO);
fail:
	वापस error;
पूर्ण

अटल पूर्णांक init_per_node(काष्ठा gfs2_sbd *sdp, पूर्णांक unकरो)
अणु
	काष्ठा inode *pn = शून्य;
	अक्षर buf[30];
	पूर्णांक error = 0;
	काष्ठा gfs2_inode *ip;
	काष्ठा inode *master = d_inode(sdp->sd_master_dir);

	अगर (sdp->sd_args.ar_spectator)
		वापस 0;

	अगर (unकरो)
		जाओ fail_qc_gh;

	pn = gfs2_lookup_simple(master, "per_node");
	अगर (IS_ERR(pn)) अणु
		error = PTR_ERR(pn);
		fs_err(sdp, "can't find per_node directory: %d\n", error);
		वापस error;
	पूर्ण

	प्र_लिखो(buf, "quota_change%u", sdp->sd_jdesc->jd_jid);
	sdp->sd_qc_inode = gfs2_lookup_simple(pn, buf);
	अगर (IS_ERR(sdp->sd_qc_inode)) अणु
		error = PTR_ERR(sdp->sd_qc_inode);
		fs_err(sdp, "can't find local \"qc\" file: %d\n", error);
		जाओ fail_ut_i;
	पूर्ण

	iput(pn);
	pn = शून्य;

	ip = GFS2_I(sdp->sd_qc_inode);
	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0,
				   &sdp->sd_qc_gh);
	अगर (error) अणु
		fs_err(sdp, "can't lock local \"qc\" file: %d\n", error);
		जाओ fail_qc_i;
	पूर्ण

	वापस 0;

fail_qc_gh:
	gfs2_glock_dq_uninit(&sdp->sd_qc_gh);
fail_qc_i:
	iput(sdp->sd_qc_inode);
fail_ut_i:
	iput(pn);
	वापस error;
पूर्ण

अटल स्थिर match_table_t nolock_tokens = अणु
	अणु Opt_jid, "jid=%d", पूर्ण,
	अणु Opt_err, शून्य पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lm_lockops nolock_ops = अणु
	.lm_proto_name = "lock_nolock",
	.lm_put_lock = gfs2_glock_मुक्त,
	.lm_tokens = &nolock_tokens,
पूर्ण;

/**
 * gfs2_lm_mount - mount a locking protocol
 * @sdp: the fileप्रणाली
 * @silent: अगर 1, करोn't complain if the FS isn't a GFS2 fs
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_lm_mount(काष्ठा gfs2_sbd *sdp, पूर्णांक silent)
अणु
	स्थिर काष्ठा lm_lockops *lm;
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;
	काष्ठा gfs2_args *args = &sdp->sd_args;
	स्थिर अक्षर *proto = sdp->sd_proto_name;
	स्थिर अक्षर *table = sdp->sd_table_name;
	अक्षर *o, *options;
	पूर्णांक ret;

	अगर (!म_भेद("lock_nolock", proto)) अणु
		lm = &nolock_ops;
		sdp->sd_args.ar_localflocks = 1;
#अगर_घोषित CONFIG_GFS2_FS_LOCKING_DLM
	पूर्ण अन्यथा अगर (!म_भेद("lock_dlm", proto)) अणु
		lm = &gfs2_dlm_ops;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		pr_info("can't find protocol %s\n", proto);
		वापस -ENOENT;
	पूर्ण

	fs_info(sdp, "Trying to join cluster \"%s\", \"%s\"\n", proto, table);

	ls->ls_ops = lm;
	ls->ls_first = 1;

	क्रम (options = args->ar_hostdata; (o = strsep(&options, ":")); ) अणु
		substring_t पंचांगp[MAX_OPT_ARGS];
		पूर्णांक token, option;

		अगर (!o || !*o)
			जारी;

		token = match_token(o, *lm->lm_tokens, पंचांगp);
		चयन (token) अणु
		हाल Opt_jid:
			ret = match_पूर्णांक(&पंचांगp[0], &option);
			अगर (ret || option < 0) 
				जाओ hostdata_error;
			अगर (test_and_clear_bit(SDF_NOJOURNALID, &sdp->sd_flags))
				ls->ls_jid = option;
			अवरोध;
		हाल Opt_id:
		हाल Opt_nodir:
			/* Obsolete, but left क्रम backward compat purposes */
			अवरोध;
		हाल Opt_first:
			ret = match_पूर्णांक(&पंचांगp[0], &option);
			अगर (ret || (option != 0 && option != 1))
				जाओ hostdata_error;
			ls->ls_first = option;
			अवरोध;
		हाल Opt_err:
		शेष:
hostdata_error:
			fs_info(sdp, "unknown hostdata (%s)\n", o);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (lm->lm_mount == शून्य) अणु
		fs_info(sdp, "Now mounting FS (format %u)...\n", sdp->sd_sb.sb_fs_क्रमmat);
		complete_all(&sdp->sd_locking_init);
		वापस 0;
	पूर्ण
	ret = lm->lm_mount(sdp, table);
	अगर (ret == 0)
		fs_info(sdp, "Joined cluster. Now mounting FS (format %u)...\n",
		        sdp->sd_sb.sb_fs_क्रमmat);
	complete_all(&sdp->sd_locking_init);
	वापस ret;
पूर्ण

व्योम gfs2_lm_unmount(काष्ठा gfs2_sbd *sdp)
अणु
	स्थिर काष्ठा lm_lockops *lm = sdp->sd_lockकाष्ठा.ls_ops;
	अगर (likely(!gfs2_withdrawn(sdp)) && lm->lm_unmount)
		lm->lm_unmount(sdp);
पूर्ण

अटल पूर्णांक रुको_on_journal(काष्ठा gfs2_sbd *sdp)
अणु
	अगर (sdp->sd_lockकाष्ठा.ls_ops->lm_mount == शून्य)
		वापस 0;

	वापस रुको_on_bit(&sdp->sd_flags, SDF_NOJOURNALID, TASK_INTERRUPTIBLE)
		? -EINTR : 0;
पूर्ण

व्योम gfs2_online_uevent(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा super_block *sb = sdp->sd_vfs;
	अक्षर ro[20];
	अक्षर spectator[20];
	अक्षर *envp[] = अणु ro, spectator, शून्य पूर्ण;
	प्र_लिखो(ro, "RDONLY=%d", sb_rकरोnly(sb));
	प्र_लिखो(spectator, "SPECTATOR=%d", sdp->sd_args.ar_spectator ? 1 : 0);
	kobject_uevent_env(&sdp->sd_kobj, KOBJ_ONLINE, envp);
पूर्ण

/**
 * gfs2_fill_super - Read in superblock
 * @sb: The VFS superblock
 * @fc: Mount options and flags
 *
 * Returns: -त्रुटि_सं
 */
अटल पूर्णांक gfs2_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा gfs2_args *args = fc->fs_निजी;
	पूर्णांक silent = fc->sb_flags & SB_SILENT;
	काष्ठा gfs2_sbd *sdp;
	काष्ठा gfs2_holder mount_gh;
	काष्ठा gfs2_holder मुक्तze_gh;
	पूर्णांक error;

	sdp = init_sbd(sb);
	अगर (!sdp) अणु
		pr_warn("can't alloc struct gfs2_sbd\n");
		वापस -ENOMEM;
	पूर्ण
	sdp->sd_args = *args;

	अगर (sdp->sd_args.ar_spectator) अणु
                sb->s_flags |= SB_RDONLY;
		set_bit(SDF_RORECOVERY, &sdp->sd_flags);
	पूर्ण
	अगर (sdp->sd_args.ar_posix_acl)
		sb->s_flags |= SB_POSIXACL;
	अगर (sdp->sd_args.ar_nobarrier)
		set_bit(SDF_NOBARRIERS, &sdp->sd_flags);

	sb->s_flags |= SB_NOSEC;
	sb->s_magic = GFS2_MAGIC;
	sb->s_op = &gfs2_super_ops;
	sb->s_d_op = &gfs2_करोps;
	sb->s_export_op = &gfs2_export_ops;
	sb->s_qcop = &gfs2_quotactl_ops;
	sb->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP;
	sb_dqopt(sb)->flags |= DQUOT_QUOTA_SYS_खाता;
	sb->s_समय_gran = 1;
	sb->s_maxbytes = MAX_LFS_खाताSIZE;

	/* Set up the buffer cache and fill in some fake block size values
	   to allow us to पढ़ो-in the on-disk superblock. */
	sdp->sd_sb.sb_bsize = sb_min_blocksize(sb, GFS2_BASIC_BLOCK);
	sdp->sd_sb.sb_bsize_shअगरt = sb->s_blocksize_bits;
	sdp->sd_fsb2bb_shअगरt = sdp->sd_sb.sb_bsize_shअगरt -
                               GFS2_BASIC_BLOCK_SHIFT;
	sdp->sd_fsb2bb = BIT(sdp->sd_fsb2bb_shअगरt);

	sdp->sd_tune.gt_logd_secs = sdp->sd_args.ar_commit;
	sdp->sd_tune.gt_quota_quantum = sdp->sd_args.ar_quota_quantum;
	अगर (sdp->sd_args.ar_statfs_quantum) अणु
		sdp->sd_tune.gt_statfs_slow = 0;
		sdp->sd_tune.gt_statfs_quantum = sdp->sd_args.ar_statfs_quantum;
	पूर्ण अन्यथा अणु
		sdp->sd_tune.gt_statfs_slow = 1;
		sdp->sd_tune.gt_statfs_quantum = 30;
	पूर्ण

	error = init_names(sdp, silent);
	अगर (error)
		जाओ fail_मुक्त;

	snम_लिखो(sdp->sd_fsname, माप(sdp->sd_fsname), "%s", sdp->sd_table_name);

	error = gfs2_sys_fs_add(sdp);
	अगर (error)
		जाओ fail_मुक्त;

	gfs2_create_debugfs_file(sdp);

	error = gfs2_lm_mount(sdp, silent);
	अगर (error)
		जाओ fail_debug;

	error = init_locking(sdp, &mount_gh, DO);
	अगर (error)
		जाओ fail_lm;

	error = init_sb(sdp, silent);
	अगर (error)
		जाओ fail_locking;

	/* Turn rgrplvb on by शेष अगर fs क्रमmat is recent enough */
	अगर (!sdp->sd_args.ar_got_rgrplvb && sdp->sd_sb.sb_fs_क्रमmat > 1801)
		sdp->sd_args.ar_rgrplvb = 1;

	error = रुको_on_journal(sdp);
	अगर (error)
		जाओ fail_sb;

	/*
	 * If user space has failed to join the cluster or some similar
	 * failure has occurred, then the journal id will contain a
	 * negative (error) number. This will then be वापसed to the
	 * caller (of the mount syscall). We करो this even क्रम spectator
	 * mounts (which just ग_लिखो a jid of 0 to indicate "ok" even though
	 * the jid is unused in the spectator हाल)
	 */
	अगर (sdp->sd_lockकाष्ठा.ls_jid < 0) अणु
		error = sdp->sd_lockकाष्ठा.ls_jid;
		sdp->sd_lockकाष्ठा.ls_jid = 0;
		जाओ fail_sb;
	पूर्ण

	अगर (sdp->sd_args.ar_spectator)
		snम_लिखो(sdp->sd_fsname, माप(sdp->sd_fsname), "%s.s",
			 sdp->sd_table_name);
	अन्यथा
		snम_लिखो(sdp->sd_fsname, माप(sdp->sd_fsname), "%s.%u",
			 sdp->sd_table_name, sdp->sd_lockकाष्ठा.ls_jid);

	error = init_inodes(sdp, DO);
	अगर (error)
		जाओ fail_sb;

	error = init_per_node(sdp, DO);
	अगर (error)
		जाओ fail_inodes;

	error = gfs2_statfs_init(sdp);
	अगर (error) अणु
		fs_err(sdp, "can't initialize statfs subsystem: %d\n", error);
		जाओ fail_per_node;
	पूर्ण

	error = gfs2_मुक्तze_lock(sdp, &मुक्तze_gh, 0);
	अगर (error)
		जाओ fail_per_node;

	अगर (!sb_rकरोnly(sb))
		error = gfs2_make_fs_rw(sdp);

	gfs2_मुक्तze_unlock(&मुक्तze_gh);
	अगर (error) अणु
		fs_err(sdp, "can't make FS RW: %d\n", error);
		जाओ fail_per_node;
	पूर्ण
	gfs2_glock_dq_uninit(&mount_gh);
	gfs2_online_uevent(sdp);
	वापस 0;

fail_per_node:
	init_per_node(sdp, UNDO);
fail_inodes:
	init_inodes(sdp, UNDO);
fail_sb:
	अगर (sdp->sd_root_dir)
		dput(sdp->sd_root_dir);
	अगर (sdp->sd_master_dir)
		dput(sdp->sd_master_dir);
	अगर (sb->s_root)
		dput(sb->s_root);
	sb->s_root = शून्य;
fail_locking:
	init_locking(sdp, &mount_gh, UNDO);
fail_lm:
	complete_all(&sdp->sd_journal_पढ़ोy);
	gfs2_gl_hash_clear(sdp);
	gfs2_lm_unmount(sdp);
fail_debug:
	gfs2_delete_debugfs_file(sdp);
	gfs2_sys_fs_del(sdp);
fail_मुक्त:
	मुक्त_sbd(sdp);
	sb->s_fs_info = शून्य;
	वापस error;
पूर्ण

/**
 * gfs2_get_tree - Get the GFS2 superblock and root directory
 * @fc: The fileप्रणाली context
 *
 * Returns: 0 or -त्रुटि_सं on error
 */
अटल पूर्णांक gfs2_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा gfs2_args *args = fc->fs_निजी;
	काष्ठा gfs2_sbd *sdp;
	पूर्णांक error;

	error = get_tree_bdev(fc, gfs2_fill_super);
	अगर (error)
		वापस error;

	sdp = fc->root->d_sb->s_fs_info;
	dput(fc->root);
	अगर (args->ar_meta)
		fc->root = dget(sdp->sd_master_dir);
	अन्यथा
		fc->root = dget(sdp->sd_root_dir);
	वापस 0;
पूर्ण

अटल व्योम gfs2_fc_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा gfs2_args *args = fc->fs_निजी;

	kमुक्त(args);
पूर्ण

क्रमागत gfs2_param अणु
	Opt_lockproto,
	Opt_locktable,
	Opt_hostdata,
	Opt_spectator,
	Opt_ignore_local_fs,
	Opt_localflocks,
	Opt_localcaching,
	Opt_debug,
	Opt_upgrade,
	Opt_acl,
	Opt_quota,
	Opt_quota_flag,
	Opt_suiddir,
	Opt_data,
	Opt_meta,
	Opt_discard,
	Opt_commit,
	Opt_errors,
	Opt_statfs_quantum,
	Opt_statfs_percent,
	Opt_quota_quantum,
	Opt_barrier,
	Opt_rgrplvb,
	Opt_loccookie,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table gfs2_param_quota[] = अणु
	अणु"off",        GFS2_QUOTA_OFFपूर्ण,
	अणु"account",    GFS2_QUOTA_ACCOUNTपूर्ण,
	अणु"on",         GFS2_QUOTA_ONपूर्ण,
	अणुपूर्ण
पूर्ण;

क्रमागत opt_data अणु
	Opt_data_ग_लिखोback = GFS2_DATA_WRITEBACK,
	Opt_data_ordered   = GFS2_DATA_ORDERED,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table gfs2_param_data[] = अणु
	अणु"writeback",  Opt_data_ग_लिखोback पूर्ण,
	अणु"ordered",    Opt_data_ordered पूर्ण,
	अणुपूर्ण
पूर्ण;

क्रमागत opt_errors अणु
	Opt_errors_withdraw = GFS2_ERRORS_WITHDRAW,
	Opt_errors_panic    = GFS2_ERRORS_PANIC,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table gfs2_param_errors[] = अणु
	अणु"withdraw",   Opt_errors_withdraw पूर्ण,
	अणु"panic",      Opt_errors_panic पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec gfs2_fs_parameters[] = अणु
	fsparam_string ("lockproto",          Opt_lockproto),
	fsparam_string ("locktable",          Opt_locktable),
	fsparam_string ("hostdata",           Opt_hostdata),
	fsparam_flag   ("spectator",          Opt_spectator),
	fsparam_flag   ("norecovery",         Opt_spectator),
	fsparam_flag   ("ignore_local_fs",    Opt_ignore_local_fs),
	fsparam_flag   ("localflocks",        Opt_localflocks),
	fsparam_flag   ("localcaching",       Opt_localcaching),
	fsparam_flag_no("debug",              Opt_debug),
	fsparam_flag   ("upgrade",            Opt_upgrade),
	fsparam_flag_no("acl",                Opt_acl),
	fsparam_flag_no("suiddir",            Opt_suiddir),
	fsparam_क्रमागत   ("data",               Opt_data, gfs2_param_data),
	fsparam_flag   ("meta",               Opt_meta),
	fsparam_flag_no("discard",            Opt_discard),
	fsparam_s32    ("commit",             Opt_commit),
	fsparam_क्रमागत   ("errors",             Opt_errors, gfs2_param_errors),
	fsparam_s32    ("statfs_quantum",     Opt_statfs_quantum),
	fsparam_s32    ("statfs_percent",     Opt_statfs_percent),
	fsparam_s32    ("quota_quantum",      Opt_quota_quantum),
	fsparam_flag_no("barrier",            Opt_barrier),
	fsparam_flag_no("rgrplvb",            Opt_rgrplvb),
	fsparam_flag_no("loccookie",          Opt_loccookie),
	/* quota can be a flag or an क्रमागत so it माला_लो special treaपंचांगent */
	fsparam_flag_no("quota",	      Opt_quota_flag),
	fsparam_क्रमागत("quota",		      Opt_quota, gfs2_param_quota),
	अणुपूर्ण
पूर्ण;

/* Parse a single mount parameter */
अटल पूर्णांक gfs2_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा gfs2_args *args = fc->fs_निजी;
	काष्ठा fs_parse_result result;
	पूर्णांक o;

	o = fs_parse(fc, gfs2_fs_parameters, param, &result);
	अगर (o < 0)
		वापस o;

	चयन (o) अणु
	हाल Opt_lockproto:
		strlcpy(args->ar_lockproto, param->string, GFS2_LOCKNAME_LEN);
		अवरोध;
	हाल Opt_locktable:
		strlcpy(args->ar_locktable, param->string, GFS2_LOCKNAME_LEN);
		अवरोध;
	हाल Opt_hostdata:
		strlcpy(args->ar_hostdata, param->string, GFS2_LOCKNAME_LEN);
		अवरोध;
	हाल Opt_spectator:
		args->ar_spectator = 1;
		अवरोध;
	हाल Opt_ignore_local_fs:
		/* Retained क्रम backwards compat only */
		अवरोध;
	हाल Opt_localflocks:
		args->ar_localflocks = 1;
		अवरोध;
	हाल Opt_localcaching:
		/* Retained क्रम backwards compat only */
		अवरोध;
	हाल Opt_debug:
		अगर (result.boolean && args->ar_errors == GFS2_ERRORS_PANIC)
			वापस invalfc(fc, "-o debug and -o errors=panic are mutually exclusive");
		args->ar_debug = result.boolean;
		अवरोध;
	हाल Opt_upgrade:
		/* Retained क्रम backwards compat only */
		अवरोध;
	हाल Opt_acl:
		args->ar_posix_acl = result.boolean;
		अवरोध;
	हाल Opt_quota_flag:
		args->ar_quota = result.negated ? GFS2_QUOTA_OFF : GFS2_QUOTA_ON;
		अवरोध;
	हाल Opt_quota:
		args->ar_quota = result.पूर्णांक_32;
		अवरोध;
	हाल Opt_suiddir:
		args->ar_suiddir = result.boolean;
		अवरोध;
	हाल Opt_data:
		/* The uपूर्णांक_32 result maps directly to GFS2_DATA_* */
		args->ar_data = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_meta:
		args->ar_meta = 1;
		अवरोध;
	हाल Opt_discard:
		args->ar_discard = result.boolean;
		अवरोध;
	हाल Opt_commit:
		अगर (result.पूर्णांक_32 <= 0)
			वापस invalfc(fc, "commit mount option requires a positive numeric argument");
		args->ar_commit = result.पूर्णांक_32;
		अवरोध;
	हाल Opt_statfs_quantum:
		अगर (result.पूर्णांक_32 < 0)
			वापस invalfc(fc, "statfs_quantum mount option requires a non-negative numeric argument");
		args->ar_statfs_quantum = result.पूर्णांक_32;
		अवरोध;
	हाल Opt_quota_quantum:
		अगर (result.पूर्णांक_32 <= 0)
			वापस invalfc(fc, "quota_quantum mount option requires a positive numeric argument");
		args->ar_quota_quantum = result.पूर्णांक_32;
		अवरोध;
	हाल Opt_statfs_percent:
		अगर (result.पूर्णांक_32 < 0 || result.पूर्णांक_32 > 100)
			वापस invalfc(fc, "statfs_percent mount option requires a numeric argument between 0 and 100");
		args->ar_statfs_percent = result.पूर्णांक_32;
		अवरोध;
	हाल Opt_errors:
		अगर (args->ar_debug && result.uपूर्णांक_32 == GFS2_ERRORS_PANIC)
			वापस invalfc(fc, "-o debug and -o errors=panic are mutually exclusive");
		args->ar_errors = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_barrier:
		args->ar_nobarrier = result.boolean;
		अवरोध;
	हाल Opt_rgrplvb:
		args->ar_rgrplvb = result.boolean;
		args->ar_got_rgrplvb = 1;
		अवरोध;
	हाल Opt_loccookie:
		args->ar_loccookie = result.boolean;
		अवरोध;
	शेष:
		वापस invalfc(fc, "invalid mount option: %s", param->key);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *sb = fc->root->d_sb;
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा gfs2_args *oldargs = &sdp->sd_args;
	काष्ठा gfs2_args *newargs = fc->fs_निजी;
	काष्ठा gfs2_tune *gt = &sdp->sd_tune;
	पूर्णांक error = 0;

	sync_fileप्रणाली(sb);

	spin_lock(&gt->gt_spin);
	oldargs->ar_commit = gt->gt_logd_secs;
	oldargs->ar_quota_quantum = gt->gt_quota_quantum;
	अगर (gt->gt_statfs_slow)
		oldargs->ar_statfs_quantum = 0;
	अन्यथा
		oldargs->ar_statfs_quantum = gt->gt_statfs_quantum;
	spin_unlock(&gt->gt_spin);

	अगर (म_भेद(newargs->ar_lockproto, oldargs->ar_lockproto)) अणु
		errorfc(fc, "reconfiguration of locking protocol not allowed");
		वापस -EINVAL;
	पूर्ण
	अगर (म_भेद(newargs->ar_locktable, oldargs->ar_locktable)) अणु
		errorfc(fc, "reconfiguration of lock table not allowed");
		वापस -EINVAL;
	पूर्ण
	अगर (म_भेद(newargs->ar_hostdata, oldargs->ar_hostdata)) अणु
		errorfc(fc, "reconfiguration of host data not allowed");
		वापस -EINVAL;
	पूर्ण
	अगर (newargs->ar_spectator != oldargs->ar_spectator) अणु
		errorfc(fc, "reconfiguration of spectator mode not allowed");
		वापस -EINVAL;
	पूर्ण
	अगर (newargs->ar_localflocks != oldargs->ar_localflocks) अणु
		errorfc(fc, "reconfiguration of localflocks not allowed");
		वापस -EINVAL;
	पूर्ण
	अगर (newargs->ar_meta != oldargs->ar_meta) अणु
		errorfc(fc, "switching between gfs2 and gfs2meta not allowed");
		वापस -EINVAL;
	पूर्ण
	अगर (oldargs->ar_spectator)
		fc->sb_flags |= SB_RDONLY;

	अगर ((sb->s_flags ^ fc->sb_flags) & SB_RDONLY) अणु
		काष्ठा gfs2_holder मुक्तze_gh;

		error = gfs2_मुक्तze_lock(sdp, &मुक्तze_gh, 0);
		अगर (error)
			वापस -EINVAL;

		अगर (fc->sb_flags & SB_RDONLY) अणु
			gfs2_make_fs_ro(sdp);
		पूर्ण अन्यथा अणु
			error = gfs2_make_fs_rw(sdp);
			अगर (error)
				errorfc(fc, "unable to remount read-write");
		पूर्ण
		gfs2_मुक्तze_unlock(&मुक्तze_gh);
	पूर्ण
	sdp->sd_args = *newargs;

	अगर (sdp->sd_args.ar_posix_acl)
		sb->s_flags |= SB_POSIXACL;
	अन्यथा
		sb->s_flags &= ~SB_POSIXACL;
	अगर (sdp->sd_args.ar_nobarrier)
		set_bit(SDF_NOBARRIERS, &sdp->sd_flags);
	अन्यथा
		clear_bit(SDF_NOBARRIERS, &sdp->sd_flags);
	spin_lock(&gt->gt_spin);
	gt->gt_logd_secs = newargs->ar_commit;
	gt->gt_quota_quantum = newargs->ar_quota_quantum;
	अगर (newargs->ar_statfs_quantum) अणु
		gt->gt_statfs_slow = 0;
		gt->gt_statfs_quantum = newargs->ar_statfs_quantum;
	पूर्ण
	अन्यथा अणु
		gt->gt_statfs_slow = 1;
		gt->gt_statfs_quantum = 30;
	पूर्ण
	spin_unlock(&gt->gt_spin);

	gfs2_online_uevent(sdp);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations gfs2_context_ops = अणु
	.मुक्त        = gfs2_fc_मुक्त,
	.parse_param = gfs2_parse_param,
	.get_tree    = gfs2_get_tree,
	.reconfigure = gfs2_reconfigure,
पूर्ण;

/* Set up the fileप्रणाली mount context */
अटल पूर्णांक gfs2_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा gfs2_args *args;

	args = kदो_स्मृति(माप(*args), GFP_KERNEL);
	अगर (args == शून्य)
		वापस -ENOMEM;

	अगर (fc->purpose == FS_CONTEXT_FOR_RECONFIGURE) अणु
		काष्ठा gfs2_sbd *sdp = fc->root->d_sb->s_fs_info;

		*args = sdp->sd_args;
	पूर्ण अन्यथा अणु
		स_रखो(args, 0, माप(*args));
		args->ar_quota = GFS2_QUOTA_DEFAULT;
		args->ar_data = GFS2_DATA_DEFAULT;
		args->ar_commit = 30;
		args->ar_statfs_quantum = 30;
		args->ar_quota_quantum = 60;
		args->ar_errors = GFS2_ERRORS_DEFAULT;
	पूर्ण
	fc->fs_निजी = args;
	fc->ops = &gfs2_context_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक set_meta_super(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक test_meta_super(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	वापस (fc->sget_key == s->s_bdev);
पूर्ण

अटल पूर्णांक gfs2_meta_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *s;
	काष्ठा gfs2_sbd *sdp;
	काष्ठा path path;
	पूर्णांक error;

	अगर (!fc->source || !*fc->source)
		वापस -EINVAL;

	error = kern_path(fc->source, LOOKUP_FOLLOW, &path);
	अगर (error) अणु
		pr_warn("path_lookup on %s returned error %d\n",
		        fc->source, error);
		वापस error;
	पूर्ण
	fc->fs_type = &gfs2_fs_type;
	fc->sget_key = path.dentry->d_sb->s_bdev;
	s = sget_fc(fc, test_meta_super, set_meta_super);
	path_put(&path);
	अगर (IS_ERR(s)) अणु
		pr_warn("gfs2 mount does not exist\n");
		वापस PTR_ERR(s);
	पूर्ण
	अगर ((fc->sb_flags ^ s->s_flags) & SB_RDONLY) अणु
		deactivate_locked_super(s);
		वापस -EBUSY;
	पूर्ण
	sdp = s->s_fs_info;
	fc->root = dget(sdp->sd_master_dir);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations gfs2_meta_context_ops = अणु
	.मुक्त        = gfs2_fc_मुक्त,
	.get_tree    = gfs2_meta_get_tree,
पूर्ण;

अटल पूर्णांक gfs2_meta_init_fs_context(काष्ठा fs_context *fc)
अणु
	पूर्णांक ret = gfs2_init_fs_context(fc);

	अगर (ret)
		वापस ret;

	fc->ops = &gfs2_meta_context_ops;
	वापस 0;
पूर्ण

अटल व्योम gfs2_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;

	अगर (sdp == शून्य) अणु
		समाप्त_block_super(sb);
		वापस;
	पूर्ण

	gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_SYNC | GFS2_LFC_KILL_SB);
	dput(sdp->sd_root_dir);
	dput(sdp->sd_master_dir);
	sdp->sd_root_dir = शून्य;
	sdp->sd_master_dir = शून्य;
	shrink_dcache_sb(sb);
	समाप्त_block_super(sb);
पूर्ण

काष्ठा file_प्रणाली_type gfs2_fs_type = अणु
	.name = "gfs2",
	.fs_flags = FS_REQUIRES_DEV,
	.init_fs_context = gfs2_init_fs_context,
	.parameters = gfs2_fs_parameters,
	.समाप्त_sb = gfs2_समाप्त_sb,
	.owner = THIS_MODULE,
पूर्ण;
MODULE_ALIAS_FS("gfs2");

काष्ठा file_प्रणाली_type gfs2meta_fs_type = अणु
	.name = "gfs2meta",
	.fs_flags = FS_REQUIRES_DEV,
	.init_fs_context = gfs2_meta_init_fs_context,
	.owner = THIS_MODULE,
पूर्ण;
MODULE_ALIAS_FS("gfs2meta");
