<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/ialloc.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  BSD ufs-inspired inode and directory allocation by
 *  Stephen Tweedie (sct@redhat.com), 1993
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/quotaops.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/bitops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/cred.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "ext4.h"
#समावेश "ext4_jbd2.h"
#समावेश "xattr.h"
#समावेश "acl.h"

#समावेश <trace/events/ext4.h>

/*
 * ialloc.c contains the inodes allocation and deallocation routines
 */

/*
 * The मुक्त inodes are managed by biपंचांगaps.  A file प्रणाली contains several
 * blocks groups.  Each group contains 1 biपंचांगap block क्रम blocks, 1 biपंचांगap
 * block क्रम inodes, N blocks क्रम the inode table and data blocks.
 *
 * The file प्रणाली contains group descriptors which are located after the
 * super block.  Each descriptor contains the number of the biपंचांगap block and
 * the मुक्त blocks count in the block.
 */

/*
 * To aव्योम calling the atomic setbit hundreds or thousands of बार, we only
 * need to use it within a single byte (to ensure we get endianness right).
 * We can use स_रखो क्रम the rest of the biपंचांगap as there are no other users.
 */
व्योम ext4_mark_biपंचांगap_end(पूर्णांक start_bit, पूर्णांक end_bit, अक्षर *biपंचांगap)
अणु
	पूर्णांक i;

	अगर (start_bit >= end_bit)
		वापस;

	ext4_debug("mark end bits +%d through +%d used\n", start_bit, end_bit);
	क्रम (i = start_bit; i < ((start_bit + 7) & ~7UL); i++)
		ext4_set_bit(i, biपंचांगap);
	अगर (i < end_bit)
		स_रखो(biपंचांगap + (i >> 3), 0xff, (end_bit - i) >> 3);
पूर्ण

व्योम ext4_end_biपंचांगap_पढ़ो(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	अगर (uptodate) अणु
		set_buffer_uptodate(bh);
		set_biपंचांगap_uptodate(bh);
	पूर्ण
	unlock_buffer(bh);
	put_bh(bh);
पूर्ण

अटल पूर्णांक ext4_validate_inode_biपंचांगap(काष्ठा super_block *sb,
				      काष्ठा ext4_group_desc *desc,
				      ext4_group_t block_group,
				      काष्ठा buffer_head *bh)
अणु
	ext4_fsblk_t	blk;
	काष्ठा ext4_group_info *grp;

	अगर (EXT4_SB(sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस 0;

	grp = ext4_get_group_info(sb, block_group);

	अगर (buffer_verअगरied(bh))
		वापस 0;
	अगर (EXT4_MB_GRP_IBITMAP_CORRUPT(grp))
		वापस -EFSCORRUPTED;

	ext4_lock_group(sb, block_group);
	अगर (buffer_verअगरied(bh))
		जाओ verअगरied;
	blk = ext4_inode_biपंचांगap(sb, desc);
	अगर (!ext4_inode_biपंचांगap_csum_verअगरy(sb, block_group, desc, bh,
					   EXT4_INODES_PER_GROUP(sb) / 8) ||
	    ext4_simulate_fail(sb, EXT4_SIM_IBITMAP_CRC)) अणु
		ext4_unlock_group(sb, block_group);
		ext4_error(sb, "Corrupt inode bitmap - block_group = %u, "
			   "inode_bitmap = %llu", block_group, blk);
		ext4_mark_group_biपंचांगap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_IBITMAP_CORRUPT);
		वापस -EFSBADCRC;
	पूर्ण
	set_buffer_verअगरied(bh);
verअगरied:
	ext4_unlock_group(sb, block_group);
	वापस 0;
पूर्ण

/*
 * Read the inode allocation biपंचांगap क्रम a given block_group, पढ़ोing
 * पूर्णांकo the specअगरied slot in the superblock's biपंचांगap cache.
 *
 * Return buffer_head of biपंचांगap on success, or an ERR_PTR on error.
 */
अटल काष्ठा buffer_head *
ext4_पढ़ो_inode_biपंचांगap(काष्ठा super_block *sb, ext4_group_t block_group)
अणु
	काष्ठा ext4_group_desc *desc;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा buffer_head *bh = शून्य;
	ext4_fsblk_t biपंचांगap_blk;
	पूर्णांक err;

	desc = ext4_get_group_desc(sb, block_group, शून्य);
	अगर (!desc)
		वापस ERR_PTR(-EFSCORRUPTED);

	biपंचांगap_blk = ext4_inode_biपंचांगap(sb, desc);
	अगर ((biपंचांगap_blk <= le32_to_cpu(sbi->s_es->s_first_data_block)) ||
	    (biपंचांगap_blk >= ext4_blocks_count(sbi->s_es))) अणु
		ext4_error(sb, "Invalid inode bitmap blk %llu in "
			   "block_group %u", biपंचांगap_blk, block_group);
		ext4_mark_group_biपंचांगap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_IBITMAP_CORRUPT);
		वापस ERR_PTR(-EFSCORRUPTED);
	पूर्ण
	bh = sb_getblk(sb, biपंचांगap_blk);
	अगर (unlikely(!bh)) अणु
		ext4_warning(sb, "Cannot read inode bitmap - "
			     "block_group = %u, inode_bitmap = %llu",
			     block_group, biपंचांगap_blk);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	अगर (biपंचांगap_uptodate(bh))
		जाओ verअगरy;

	lock_buffer(bh);
	अगर (biपंचांगap_uptodate(bh)) अणु
		unlock_buffer(bh);
		जाओ verअगरy;
	पूर्ण

	ext4_lock_group(sb, block_group);
	अगर (ext4_has_group_desc_csum(sb) &&
	    (desc->bg_flags & cpu_to_le16(EXT4_BG_INODE_UNINIT))) अणु
		अगर (block_group == 0) अणु
			ext4_unlock_group(sb, block_group);
			unlock_buffer(bh);
			ext4_error(sb, "Inode bitmap for bg 0 marked "
				   "uninitialized");
			err = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		स_रखो(bh->b_data, 0, (EXT4_INODES_PER_GROUP(sb) + 7) / 8);
		ext4_mark_biपंचांगap_end(EXT4_INODES_PER_GROUP(sb),
				     sb->s_blocksize * 8, bh->b_data);
		set_biपंचांगap_uptodate(bh);
		set_buffer_uptodate(bh);
		set_buffer_verअगरied(bh);
		ext4_unlock_group(sb, block_group);
		unlock_buffer(bh);
		वापस bh;
	पूर्ण
	ext4_unlock_group(sb, block_group);

	अगर (buffer_uptodate(bh)) अणु
		/*
		 * अगर not uninit अगर bh is uptodate,
		 * biपंचांगap is also uptodate
		 */
		set_biपंचांगap_uptodate(bh);
		unlock_buffer(bh);
		जाओ verअगरy;
	पूर्ण
	/*
	 * submit the buffer_head क्रम पढ़ोing
	 */
	trace_ext4_load_inode_biपंचांगap(sb, block_group);
	ext4_पढ़ो_bh(bh, REQ_META | REQ_PRIO, ext4_end_biपंचांगap_पढ़ो);
	ext4_simulate_fail_bh(sb, bh, EXT4_SIM_IBITMAP_EIO);
	अगर (!buffer_uptodate(bh)) अणु
		put_bh(bh);
		ext4_error_err(sb, EIO, "Cannot read inode bitmap - "
			       "block_group = %u, inode_bitmap = %llu",
			       block_group, biपंचांगap_blk);
		ext4_mark_group_biपंचांगap_corrupted(sb, block_group,
				EXT4_GROUP_INFO_IBITMAP_CORRUPT);
		वापस ERR_PTR(-EIO);
	पूर्ण

verअगरy:
	err = ext4_validate_inode_biपंचांगap(sb, desc, block_group, bh);
	अगर (err)
		जाओ out;
	वापस bh;
out:
	put_bh(bh);
	वापस ERR_PTR(err);
पूर्ण

/*
 * NOTE! When we get the inode, we're the only people
 * that have access to it, and as such there are no
 * race conditions we have to worry about. The inode
 * is not on the hash-lists, and it cannot be reached
 * through the fileप्रणाली because the directory entry
 * has been deleted earlier.
 *
 * HOWEVER: we must make sure that we get no aliases,
 * which means that we have to call "clear_inode()"
 * _beक्रमe_ we mark the inode not in use in the inode
 * biपंचांगaps. Otherwise a newly created file might use
 * the same inode number (not actually the same poपूर्णांकer
 * though), and then we'd have two inodes sharing the
 * same inode number and space on the harddisk.
 */
व्योम ext4_मुक्त_inode(handle_t *handle, काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक is_directory;
	अचिन्हित दीर्घ ino;
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा buffer_head *bh2;
	ext4_group_t block_group;
	अचिन्हित दीर्घ bit;
	काष्ठा ext4_group_desc *gdp;
	काष्ठा ext4_super_block *es;
	काष्ठा ext4_sb_info *sbi;
	पूर्णांक fatal = 0, err, count, cleared;
	काष्ठा ext4_group_info *grp;

	अगर (!sb) अणु
		prपूर्णांकk(KERN_ERR "EXT4-fs: %s:%d: inode on "
		       "nonexistent device\n", __func__, __LINE__);
		वापस;
	पूर्ण
	अगर (atomic_पढ़ो(&inode->i_count) > 1) अणु
		ext4_msg(sb, KERN_ERR, "%s:%d: inode #%lu: count=%d",
			 __func__, __LINE__, inode->i_ino,
			 atomic_पढ़ो(&inode->i_count));
		वापस;
	पूर्ण
	अगर (inode->i_nlink) अणु
		ext4_msg(sb, KERN_ERR, "%s:%d: inode #%lu: nlink=%d\n",
			 __func__, __LINE__, inode->i_ino, inode->i_nlink);
		वापस;
	पूर्ण
	sbi = EXT4_SB(sb);

	ino = inode->i_ino;
	ext4_debug("freeing inode %lu\n", ino);
	trace_ext4_मुक्त_inode(inode);

	dquot_initialize(inode);
	dquot_मुक्त_inode(inode);

	is_directory = S_ISसूची(inode->i_mode);

	/* Do this BEFORE marking the inode not in use or वापसing an error */
	ext4_clear_inode(inode);

	es = sbi->s_es;
	अगर (ino < EXT4_FIRST_INO(sb) || ino > le32_to_cpu(es->s_inodes_count)) अणु
		ext4_error(sb, "reserved or nonexistent inode %lu", ino);
		जाओ error_वापस;
	पूर्ण
	block_group = (ino - 1) / EXT4_INODES_PER_GROUP(sb);
	bit = (ino - 1) % EXT4_INODES_PER_GROUP(sb);
	biपंचांगap_bh = ext4_पढ़ो_inode_biपंचांगap(sb, block_group);
	/* Don't bother अगर the inode biपंचांगap is corrupt. */
	अगर (IS_ERR(biपंचांगap_bh)) अणु
		fatal = PTR_ERR(biपंचांगap_bh);
		biपंचांगap_bh = शून्य;
		जाओ error_वापस;
	पूर्ण
	अगर (!(sbi->s_mount_state & EXT4_FC_REPLAY)) अणु
		grp = ext4_get_group_info(sb, block_group);
		अगर (unlikely(EXT4_MB_GRP_IBITMAP_CORRUPT(grp))) अणु
			fatal = -EFSCORRUPTED;
			जाओ error_वापस;
		पूर्ण
	पूर्ण

	BUFFER_TRACE(biपंचांगap_bh, "get_write_access");
	fatal = ext4_journal_get_ग_लिखो_access(handle, biपंचांगap_bh);
	अगर (fatal)
		जाओ error_वापस;

	fatal = -ESRCH;
	gdp = ext4_get_group_desc(sb, block_group, &bh2);
	अगर (gdp) अणु
		BUFFER_TRACE(bh2, "get_write_access");
		fatal = ext4_journal_get_ग_लिखो_access(handle, bh2);
	पूर्ण
	ext4_lock_group(sb, block_group);
	cleared = ext4_test_and_clear_bit(bit, biपंचांगap_bh->b_data);
	अगर (fatal || !cleared) अणु
		ext4_unlock_group(sb, block_group);
		जाओ out;
	पूर्ण

	count = ext4_मुक्त_inodes_count(sb, gdp) + 1;
	ext4_मुक्त_inodes_set(sb, gdp, count);
	अगर (is_directory) अणु
		count = ext4_used_dirs_count(sb, gdp) - 1;
		ext4_used_dirs_set(sb, gdp, count);
		अगर (percpu_counter_initialized(&sbi->s_dirs_counter))
			percpu_counter_dec(&sbi->s_dirs_counter);
	पूर्ण
	ext4_inode_biपंचांगap_csum_set(sb, block_group, gdp, biपंचांगap_bh,
				   EXT4_INODES_PER_GROUP(sb) / 8);
	ext4_group_desc_csum_set(sb, block_group, gdp);
	ext4_unlock_group(sb, block_group);

	अगर (percpu_counter_initialized(&sbi->s_मुक्तinodes_counter))
		percpu_counter_inc(&sbi->s_मुक्तinodes_counter);
	अगर (sbi->s_log_groups_per_flex) अणु
		काष्ठा flex_groups *fg;

		fg = sbi_array_rcu_deref(sbi, s_flex_groups,
					 ext4_flex_group(sbi, block_group));
		atomic_inc(&fg->मुक्त_inodes);
		अगर (is_directory)
			atomic_dec(&fg->used_dirs);
	पूर्ण
	BUFFER_TRACE(bh2, "call ext4_handle_dirty_metadata");
	fatal = ext4_handle_dirty_metadata(handle, शून्य, bh2);
out:
	अगर (cleared) अणु
		BUFFER_TRACE(biपंचांगap_bh, "call ext4_handle_dirty_metadata");
		err = ext4_handle_dirty_metadata(handle, शून्य, biपंचांगap_bh);
		अगर (!fatal)
			fatal = err;
	पूर्ण अन्यथा अणु
		ext4_error(sb, "bit already cleared for inode %lu", ino);
		ext4_mark_group_biपंचांगap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_IBITMAP_CORRUPT);
	पूर्ण

error_वापस:
	brअन्यथा(biपंचांगap_bh);
	ext4_std_error(sb, fatal);
पूर्ण

काष्ठा orlov_stats अणु
	__u64 मुक्त_clusters;
	__u32 मुक्त_inodes;
	__u32 used_dirs;
पूर्ण;

/*
 * Helper function क्रम Orlov's allocator; वापसs critical inक्रमmation
 * क्रम a particular block group or flex_bg.  If flex_size is 1, then g
 * is a block group number; otherwise it is flex_bg number.
 */
अटल व्योम get_orlov_stats(काष्ठा super_block *sb, ext4_group_t g,
			    पूर्णांक flex_size, काष्ठा orlov_stats *stats)
अणु
	काष्ठा ext4_group_desc *desc;

	अगर (flex_size > 1) अणु
		काष्ठा flex_groups *fg = sbi_array_rcu_deref(EXT4_SB(sb),
							     s_flex_groups, g);
		stats->मुक्त_inodes = atomic_पढ़ो(&fg->मुक्त_inodes);
		stats->मुक्त_clusters = atomic64_पढ़ो(&fg->मुक्त_clusters);
		stats->used_dirs = atomic_पढ़ो(&fg->used_dirs);
		वापस;
	पूर्ण

	desc = ext4_get_group_desc(sb, g, शून्य);
	अगर (desc) अणु
		stats->मुक्त_inodes = ext4_मुक्त_inodes_count(sb, desc);
		stats->मुक्त_clusters = ext4_मुक्त_group_clusters(sb, desc);
		stats->used_dirs = ext4_used_dirs_count(sb, desc);
	पूर्ण अन्यथा अणु
		stats->मुक्त_inodes = 0;
		stats->मुक्त_clusters = 0;
		stats->used_dirs = 0;
	पूर्ण
पूर्ण

/*
 * Orlov's allocator क्रम directories.
 *
 * We always try to spपढ़ो first-level directories.
 *
 * If there are blockgroups with both मुक्त inodes and मुक्त blocks counts
 * not worse than average we वापस one with smallest directory count.
 * Otherwise we simply वापस a अक्रमom group.
 *
 * For the rest rules look so:
 *
 * It's OK to put directory पूर्णांकo a group unless
 * it has too many directories alपढ़ोy (max_dirs) or
 * it has too few मुक्त inodes left (min_inodes) or
 * it has too few मुक्त blocks left (min_blocks) or
 * Parent's group is preferred, if it doesn't satisfy these
 * conditions we search cyclically through the rest. If none
 * of the groups look good we just look क्रम a group with more
 * मुक्त inodes than average (starting at parent's group).
 */

अटल पूर्णांक find_group_orlov(काष्ठा super_block *sb, काष्ठा inode *parent,
			    ext4_group_t *group, umode_t mode,
			    स्थिर काष्ठा qstr *qstr)
अणु
	ext4_group_t parent_group = EXT4_I(parent)->i_block_group;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_group_t real_ngroups = ext4_get_groups_count(sb);
	पूर्णांक inodes_per_group = EXT4_INODES_PER_GROUP(sb);
	अचिन्हित पूर्णांक मुक्तi, aveमुक्तi, grp_मुक्त;
	ext4_fsblk_t मुक्तb, aveमुक्तc;
	अचिन्हित पूर्णांक ndirs;
	पूर्णांक max_dirs, min_inodes;
	ext4_grpblk_t min_clusters;
	ext4_group_t i, grp, g, ngroups;
	काष्ठा ext4_group_desc *desc;
	काष्ठा orlov_stats stats;
	पूर्णांक flex_size = ext4_flex_bg_size(sbi);
	काष्ठा dx_hash_info hinfo;

	ngroups = real_ngroups;
	अगर (flex_size > 1) अणु
		ngroups = (real_ngroups + flex_size - 1) >>
			sbi->s_log_groups_per_flex;
		parent_group >>= sbi->s_log_groups_per_flex;
	पूर्ण

	मुक्तi = percpu_counter_पढ़ो_positive(&sbi->s_मुक्तinodes_counter);
	aveमुक्तi = मुक्तi / ngroups;
	मुक्तb = EXT4_C2B(sbi,
		percpu_counter_पढ़ो_positive(&sbi->s_मुक्तclusters_counter));
	aveमुक्तc = मुक्तb;
	करो_भाग(aveमुक्तc, ngroups);
	ndirs = percpu_counter_पढ़ो_positive(&sbi->s_dirs_counter);

	अगर (S_ISसूची(mode) &&
	    ((parent == d_inode(sb->s_root)) ||
	     (ext4_test_inode_flag(parent, EXT4_INODE_TOPसूची)))) अणु
		पूर्णांक best_ndir = inodes_per_group;
		पूर्णांक ret = -1;

		अगर (qstr) अणु
			hinfo.hash_version = DX_HASH_HALF_MD4;
			hinfo.seed = sbi->s_hash_seed;
			ext4fs_dirhash(parent, qstr->name, qstr->len, &hinfo);
			grp = hinfo.hash;
		पूर्ण अन्यथा
			grp = pअक्रमom_u32();
		parent_group = (अचिन्हित)grp % ngroups;
		क्रम (i = 0; i < ngroups; i++) अणु
			g = (parent_group + i) % ngroups;
			get_orlov_stats(sb, g, flex_size, &stats);
			अगर (!stats.मुक्त_inodes)
				जारी;
			अगर (stats.used_dirs >= best_ndir)
				जारी;
			अगर (stats.मुक्त_inodes < aveमुक्तi)
				जारी;
			अगर (stats.मुक्त_clusters < aveमुक्तc)
				जारी;
			grp = g;
			ret = 0;
			best_ndir = stats.used_dirs;
		पूर्ण
		अगर (ret)
			जाओ fallback;
	found_flex_bg:
		अगर (flex_size == 1) अणु
			*group = grp;
			वापस 0;
		पूर्ण

		/*
		 * We pack inodes at the beginning of the flexgroup's
		 * inode tables.  Block allocation decisions will करो
		 * something similar, although regular files will
		 * start at 2nd block group of the flexgroup.  See
		 * ext4_ext_find_goal() and ext4_find_near().
		 */
		grp *= flex_size;
		क्रम (i = 0; i < flex_size; i++) अणु
			अगर (grp+i >= real_ngroups)
				अवरोध;
			desc = ext4_get_group_desc(sb, grp+i, शून्य);
			अगर (desc && ext4_मुक्त_inodes_count(sb, desc)) अणु
				*group = grp+i;
				वापस 0;
			पूर्ण
		पूर्ण
		जाओ fallback;
	पूर्ण

	max_dirs = ndirs / ngroups + inodes_per_group / 16;
	min_inodes = aveमुक्तi - inodes_per_group*flex_size / 4;
	अगर (min_inodes < 1)
		min_inodes = 1;
	min_clusters = aveमुक्तc - EXT4_CLUSTERS_PER_GROUP(sb)*flex_size / 4;

	/*
	 * Start looking in the flex group where we last allocated an
	 * inode क्रम this parent directory
	 */
	अगर (EXT4_I(parent)->i_last_alloc_group != ~0) अणु
		parent_group = EXT4_I(parent)->i_last_alloc_group;
		अगर (flex_size > 1)
			parent_group >>= sbi->s_log_groups_per_flex;
	पूर्ण

	क्रम (i = 0; i < ngroups; i++) अणु
		grp = (parent_group + i) % ngroups;
		get_orlov_stats(sb, grp, flex_size, &stats);
		अगर (stats.used_dirs >= max_dirs)
			जारी;
		अगर (stats.मुक्त_inodes < min_inodes)
			जारी;
		अगर (stats.मुक्त_clusters < min_clusters)
			जारी;
		जाओ found_flex_bg;
	पूर्ण

fallback:
	ngroups = real_ngroups;
	aveमुक्तi = मुक्तi / ngroups;
fallback_retry:
	parent_group = EXT4_I(parent)->i_block_group;
	क्रम (i = 0; i < ngroups; i++) अणु
		grp = (parent_group + i) % ngroups;
		desc = ext4_get_group_desc(sb, grp, शून्य);
		अगर (desc) अणु
			grp_मुक्त = ext4_मुक्त_inodes_count(sb, desc);
			अगर (grp_मुक्त && grp_मुक्त >= aveमुक्तi) अणु
				*group = grp;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (aveमुक्तi) अणु
		/*
		 * The मुक्त-inodes counter is approximate, and क्रम really small
		 * fileप्रणालीs the above test can fail to find any blockgroups
		 */
		aveमुक्तi = 0;
		जाओ fallback_retry;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक find_group_other(काष्ठा super_block *sb, काष्ठा inode *parent,
			    ext4_group_t *group, umode_t mode)
अणु
	ext4_group_t parent_group = EXT4_I(parent)->i_block_group;
	ext4_group_t i, last, ngroups = ext4_get_groups_count(sb);
	काष्ठा ext4_group_desc *desc;
	पूर्णांक flex_size = ext4_flex_bg_size(EXT4_SB(sb));

	/*
	 * Try to place the inode is the same flex group as its
	 * parent.  If we can't find space, use the Orlov algorithm to
	 * find another flex group, and store that inक्रमmation in the
	 * parent directory's inode inक्रमmation so that use that flex
	 * group क्रम future allocations.
	 */
	अगर (flex_size > 1) अणु
		पूर्णांक retry = 0;

	try_again:
		parent_group &= ~(flex_size-1);
		last = parent_group + flex_size;
		अगर (last > ngroups)
			last = ngroups;
		क्रम  (i = parent_group; i < last; i++) अणु
			desc = ext4_get_group_desc(sb, i, शून्य);
			अगर (desc && ext4_मुक्त_inodes_count(sb, desc)) अणु
				*group = i;
				वापस 0;
			पूर्ण
		पूर्ण
		अगर (!retry && EXT4_I(parent)->i_last_alloc_group != ~0) अणु
			retry = 1;
			parent_group = EXT4_I(parent)->i_last_alloc_group;
			जाओ try_again;
		पूर्ण
		/*
		 * If this didn't work, use the Orlov search algorithm
		 * to find a new flex group; we pass in the mode to
		 * aव्योम the topdir algorithms.
		 */
		*group = parent_group + flex_size;
		अगर (*group > ngroups)
			*group = 0;
		वापस find_group_orlov(sb, parent, group, mode, शून्य);
	पूर्ण

	/*
	 * Try to place the inode in its parent directory
	 */
	*group = parent_group;
	desc = ext4_get_group_desc(sb, *group, शून्य);
	अगर (desc && ext4_मुक्त_inodes_count(sb, desc) &&
	    ext4_मुक्त_group_clusters(sb, desc))
		वापस 0;

	/*
	 * We're going to place this inode in a dअगरferent blockgroup from its
	 * parent.  We want to cause files in a common directory to all land in
	 * the same blockgroup.  But we want files which are in a dअगरferent
	 * directory which shares a blockgroup with our parent to land in a
	 * dअगरferent blockgroup.
	 *
	 * So add our directory's i_ino पूर्णांकo the starting poपूर्णांक क्रम the hash.
	 */
	*group = (*group + parent->i_ino) % ngroups;

	/*
	 * Use a quadratic hash to find a group with a मुक्त inode and some मुक्त
	 * blocks.
	 */
	क्रम (i = 1; i < ngroups; i <<= 1) अणु
		*group += i;
		अगर (*group >= ngroups)
			*group -= ngroups;
		desc = ext4_get_group_desc(sb, *group, शून्य);
		अगर (desc && ext4_मुक्त_inodes_count(sb, desc) &&
		    ext4_मुक्त_group_clusters(sb, desc))
			वापस 0;
	पूर्ण

	/*
	 * That failed: try linear search क्रम a मुक्त inode, even अगर that group
	 * has no मुक्त blocks.
	 */
	*group = parent_group;
	क्रम (i = 0; i < ngroups; i++) अणु
		अगर (++*group >= ngroups)
			*group = 0;
		desc = ext4_get_group_desc(sb, *group, शून्य);
		अगर (desc && ext4_मुक्त_inodes_count(sb, desc))
			वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

/*
 * In no journal mode, अगर an inode has recently been deleted, we want
 * to aव्योम reusing it until we're reasonably sure the inode table
 * block has been written back to disk.  (Yes, these values are
 * somewhat arbitrary...)
 */
#घोषणा RECENTCY_MIN	60
#घोषणा RECENTCY_सूचीTY	300

अटल पूर्णांक recently_deleted(काष्ठा super_block *sb, ext4_group_t group, पूर्णांक ino)
अणु
	काष्ठा ext4_group_desc	*gdp;
	काष्ठा ext4_inode	*raw_inode;
	काष्ठा buffer_head	*bh;
	पूर्णांक inodes_per_block = EXT4_SB(sb)->s_inodes_per_block;
	पूर्णांक offset, ret = 0;
	पूर्णांक recentcy = RECENTCY_MIN;
	u32 dसमय, now;

	gdp = ext4_get_group_desc(sb, group, शून्य);
	अगर (unlikely(!gdp))
		वापस 0;

	bh = sb_find_get_block(sb, ext4_inode_table(sb, gdp) +
		       (ino / inodes_per_block));
	अगर (!bh || !buffer_uptodate(bh))
		/*
		 * If the block is not in the buffer cache, then it
		 * must have been written out.
		 */
		जाओ out;

	offset = (ino % inodes_per_block) * EXT4_INODE_SIZE(sb);
	raw_inode = (काष्ठा ext4_inode *) (bh->b_data + offset);

	/* i_dसमय is only 32 bits on disk, but we only care about relative
	 * बार in the range of a few minutes (i.e. दीर्घ enough to sync a
	 * recently-deleted inode to disk), so using the low 32 bits of the
	 * घड़ी (a 68 year range) is enough, see समय_beक्रमe32() */
	dसमय = le32_to_cpu(raw_inode->i_dसमय);
	now = kसमय_get_real_seconds();
	अगर (buffer_dirty(bh))
		recentcy += RECENTCY_सूचीTY;

	अगर (dसमय && समय_beक्रमe32(dसमय, now) &&
	    समय_beक्रमe32(now, dसमय + recentcy))
		ret = 1;
out:
	brअन्यथा(bh);
	वापस ret;
पूर्ण

अटल पूर्णांक find_inode_bit(काष्ठा super_block *sb, ext4_group_t group,
			  काष्ठा buffer_head *biपंचांगap, अचिन्हित दीर्घ *ino)
अणु
	bool check_recently_deleted = EXT4_SB(sb)->s_journal == शून्य;
	अचिन्हित दीर्घ recently_deleted_ino = EXT4_INODES_PER_GROUP(sb);

next:
	*ino = ext4_find_next_zero_bit((अचिन्हित दीर्घ *)
				       biपंचांगap->b_data,
				       EXT4_INODES_PER_GROUP(sb), *ino);
	अगर (*ino >= EXT4_INODES_PER_GROUP(sb))
		जाओ not_found;

	अगर (check_recently_deleted && recently_deleted(sb, group, *ino)) अणु
		recently_deleted_ino = *ino;
		*ino = *ino + 1;
		अगर (*ino < EXT4_INODES_PER_GROUP(sb))
			जाओ next;
		जाओ not_found;
	पूर्ण
	वापस 1;
not_found:
	अगर (recently_deleted_ino >= EXT4_INODES_PER_GROUP(sb))
		वापस 0;
	/*
	 * Not reusing recently deleted inodes is mostly a preference. We करोn't
	 * want to report ENOSPC or skew allocation patterns because of that.
	 * So वापस even recently deleted inode अगर we could find better in the
	 * given range.
	 */
	*ino = recently_deleted_ino;
	वापस 1;
पूर्ण

पूर्णांक ext4_mark_inode_used(काष्ठा super_block *sb, पूर्णांक ino)
अणु
	अचिन्हित दीर्घ max_ino = le32_to_cpu(EXT4_SB(sb)->s_es->s_inodes_count);
	काष्ठा buffer_head *inode_biपंचांगap_bh = शून्य, *group_desc_bh = शून्य;
	काष्ठा ext4_group_desc *gdp;
	ext4_group_t group;
	पूर्णांक bit;
	पूर्णांक err = -EFSCORRUPTED;

	अगर (ino < EXT4_FIRST_INO(sb) || ino > max_ino)
		जाओ out;

	group = (ino - 1) / EXT4_INODES_PER_GROUP(sb);
	bit = (ino - 1) % EXT4_INODES_PER_GROUP(sb);
	inode_biपंचांगap_bh = ext4_पढ़ो_inode_biपंचांगap(sb, group);
	अगर (IS_ERR(inode_biपंचांगap_bh))
		वापस PTR_ERR(inode_biपंचांगap_bh);

	अगर (ext4_test_bit(bit, inode_biपंचांगap_bh->b_data)) अणु
		err = 0;
		जाओ out;
	पूर्ण

	gdp = ext4_get_group_desc(sb, group, &group_desc_bh);
	अगर (!gdp || !group_desc_bh) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	ext4_set_bit(bit, inode_biपंचांगap_bh->b_data);

	BUFFER_TRACE(inode_biपंचांगap_bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_metadata(शून्य, शून्य, inode_biपंचांगap_bh);
	अगर (err) अणु
		ext4_std_error(sb, err);
		जाओ out;
	पूर्ण
	err = sync_dirty_buffer(inode_biपंचांगap_bh);
	अगर (err) अणु
		ext4_std_error(sb, err);
		जाओ out;
	पूर्ण

	/* We may have to initialize the block biपंचांगap अगर it isn't alपढ़ोy */
	अगर (ext4_has_group_desc_csum(sb) &&
	    gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) अणु
		काष्ठा buffer_head *block_biपंचांगap_bh;

		block_biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, group);
		अगर (IS_ERR(block_biपंचांगap_bh)) अणु
			err = PTR_ERR(block_biपंचांगap_bh);
			जाओ out;
		पूर्ण

		BUFFER_TRACE(block_biपंचांगap_bh, "dirty block bitmap");
		err = ext4_handle_dirty_metadata(शून्य, शून्य, block_biपंचांगap_bh);
		sync_dirty_buffer(block_biपंचांगap_bh);

		/* recheck and clear flag under lock अगर we still need to */
		ext4_lock_group(sb, group);
		अगर (ext4_has_group_desc_csum(sb) &&
		    (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) अणु
			gdp->bg_flags &= cpu_to_le16(~EXT4_BG_BLOCK_UNINIT);
			ext4_मुक्त_group_clusters_set(sb, gdp,
				ext4_मुक्त_clusters_after_init(sb, group, gdp));
			ext4_block_biपंचांगap_csum_set(sb, group, gdp,
						   block_biपंचांगap_bh);
			ext4_group_desc_csum_set(sb, group, gdp);
		पूर्ण
		ext4_unlock_group(sb, group);
		brअन्यथा(block_biपंचांगap_bh);

		अगर (err) अणु
			ext4_std_error(sb, err);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Update the relevant bg descriptor fields */
	अगर (ext4_has_group_desc_csum(sb)) अणु
		पूर्णांक मुक्त;

		ext4_lock_group(sb, group); /* जबतक we modअगरy the bg desc */
		मुक्त = EXT4_INODES_PER_GROUP(sb) -
			ext4_itable_unused_count(sb, gdp);
		अगर (gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_UNINIT)) अणु
			gdp->bg_flags &= cpu_to_le16(~EXT4_BG_INODE_UNINIT);
			मुक्त = 0;
		पूर्ण

		/*
		 * Check the relative inode number against the last used
		 * relative inode number in this group. अगर it is greater
		 * we need to update the bg_itable_unused count
		 */
		अगर (bit >= मुक्त)
			ext4_itable_unused_set(sb, gdp,
					(EXT4_INODES_PER_GROUP(sb) - bit - 1));
	पूर्ण अन्यथा अणु
		ext4_lock_group(sb, group);
	पूर्ण

	ext4_मुक्त_inodes_set(sb, gdp, ext4_मुक्त_inodes_count(sb, gdp) - 1);
	अगर (ext4_has_group_desc_csum(sb)) अणु
		ext4_inode_biपंचांगap_csum_set(sb, group, gdp, inode_biपंचांगap_bh,
					   EXT4_INODES_PER_GROUP(sb) / 8);
		ext4_group_desc_csum_set(sb, group, gdp);
	पूर्ण

	ext4_unlock_group(sb, group);
	err = ext4_handle_dirty_metadata(शून्य, शून्य, group_desc_bh);
	sync_dirty_buffer(group_desc_bh);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ext4_xattr_credits_क्रम_new_inode(काष्ठा inode *dir, mode_t mode,
					    bool encrypt)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	पूर्णांक nblocks = 0;
#अगर_घोषित CONFIG_EXT4_FS_POSIX_ACL
	काष्ठा posix_acl *p = get_acl(dir, ACL_TYPE_DEFAULT);

	अगर (IS_ERR(p))
		वापस PTR_ERR(p);
	अगर (p) अणु
		पूर्णांक acl_size = p->a_count * माप(ext4_acl_entry);

		nblocks += (S_ISसूची(mode) ? 2 : 1) *
			__ext4_xattr_set_credits(sb, शून्य /* inode */,
						 शून्य /* block_bh */, acl_size,
						 true /* is_create */);
		posix_acl_release(p);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY
	अणु
		पूर्णांक num_security_xattrs = 1;

#अगर_घोषित CONFIG_INTEGRITY
		num_security_xattrs++;
#पूर्ण_अगर
		/*
		 * We assume that security xattrs are never more than 1k.
		 * In practice they are under 128 bytes.
		 */
		nblocks += num_security_xattrs *
			__ext4_xattr_set_credits(sb, शून्य /* inode */,
						 शून्य /* block_bh */, 1024,
						 true /* is_create */);
	पूर्ण
#पूर्ण_अगर
	अगर (encrypt)
		nblocks += __ext4_xattr_set_credits(sb,
						    शून्य /* inode */,
						    शून्य /* block_bh */,
						    FSCRYPT_SET_CONTEXT_MAX_SIZE,
						    true /* is_create */);
	वापस nblocks;
पूर्ण

/*
 * There are two policies क्रम allocating an inode.  If the new inode is
 * a directory, then a क्रमward search is made क्रम a block group with both
 * मुक्त space and a low directory-to-inode ratio; अगर that fails, then of
 * the groups with above-average मुक्त space, that group with the fewest
 * directories alपढ़ोy is chosen.
 *
 * For other inodes, search क्रमward from the parent directory's block
 * group to find a मुक्त inode.
 */
काष्ठा inode *__ext4_new_inode(काष्ठा user_namespace *mnt_userns,
			       handle_t *handle, काष्ठा inode *dir,
			       umode_t mode, स्थिर काष्ठा qstr *qstr,
			       __u32 goal, uid_t *owner, __u32 i_flags,
			       पूर्णांक handle_type, अचिन्हित पूर्णांक line_no,
			       पूर्णांक nblocks)
अणु
	काष्ठा super_block *sb;
	काष्ठा buffer_head *inode_biपंचांगap_bh = शून्य;
	काष्ठा buffer_head *group_desc_bh;
	ext4_group_t ngroups, group = 0;
	अचिन्हित दीर्घ ino = 0;
	काष्ठा inode *inode;
	काष्ठा ext4_group_desc *gdp = शून्य;
	काष्ठा ext4_inode_info *ei;
	काष्ठा ext4_sb_info *sbi;
	पूर्णांक ret2, err;
	काष्ठा inode *ret;
	ext4_group_t i;
	ext4_group_t flex_group;
	काष्ठा ext4_group_info *grp = शून्य;
	bool encrypt = false;

	/* Cannot create files in a deleted directory */
	अगर (!dir || !dir->i_nlink)
		वापस ERR_PTR(-EPERM);

	sb = dir->i_sb;
	sbi = EXT4_SB(sb);

	अगर (unlikely(ext4_क्रमced_shutकरोwn(sbi)))
		वापस ERR_PTR(-EIO);

	ngroups = ext4_get_groups_count(sb);
	trace_ext4_request_inode(dir, mode);
	inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	ei = EXT4_I(inode);

	/*
	 * Initialize owners and quota early so that we करोn't have to account
	 * क्रम quota initialization worst हाल in standard inode creating
	 * transaction
	 */
	अगर (owner) अणु
		inode->i_mode = mode;
		i_uid_ग_लिखो(inode, owner[0]);
		i_gid_ग_लिखो(inode, owner[1]);
	पूर्ण अन्यथा अगर (test_opt(sb, GRPID)) अणु
		inode->i_mode = mode;
		inode_fsuid_set(inode, mnt_userns);
		inode->i_gid = dir->i_gid;
	पूर्ण अन्यथा
		inode_init_owner(mnt_userns, inode, dir, mode);

	अगर (ext4_has_feature_project(sb) &&
	    ext4_test_inode_flag(dir, EXT4_INODE_PROJINHERIT))
		ei->i_projid = EXT4_I(dir)->i_projid;
	अन्यथा
		ei->i_projid = make_kprojid(&init_user_ns, EXT4_DEF_PROJID);

	अगर (!(i_flags & EXT4_EA_INODE_FL)) अणु
		err = fscrypt_prepare_new_inode(dir, inode, &encrypt);
		अगर (err)
			जाओ out;
	पूर्ण

	err = dquot_initialize(inode);
	अगर (err)
		जाओ out;

	अगर (!handle && sbi->s_journal && !(i_flags & EXT4_EA_INODE_FL)) अणु
		ret2 = ext4_xattr_credits_क्रम_new_inode(dir, mode, encrypt);
		अगर (ret2 < 0) अणु
			err = ret2;
			जाओ out;
		पूर्ण
		nblocks += ret2;
	पूर्ण

	अगर (!goal)
		goal = sbi->s_inode_goal;

	अगर (goal && goal <= le32_to_cpu(sbi->s_es->s_inodes_count)) अणु
		group = (goal - 1) / EXT4_INODES_PER_GROUP(sb);
		ino = (goal - 1) % EXT4_INODES_PER_GROUP(sb);
		ret2 = 0;
		जाओ got_group;
	पूर्ण

	अगर (S_ISसूची(mode))
		ret2 = find_group_orlov(sb, dir, &group, mode, qstr);
	अन्यथा
		ret2 = find_group_other(sb, dir, &group, mode);

got_group:
	EXT4_I(dir)->i_last_alloc_group = group;
	err = -ENOSPC;
	अगर (ret2 == -1)
		जाओ out;

	/*
	 * Normally we will only go through one pass of this loop,
	 * unless we get unlucky and it turns out the group we selected
	 * had its last inode grabbed by someone अन्यथा.
	 */
	क्रम (i = 0; i < ngroups; i++, ino = 0) अणु
		err = -EIO;

		gdp = ext4_get_group_desc(sb, group, &group_desc_bh);
		अगर (!gdp)
			जाओ out;

		/*
		 * Check मुक्त inodes count beक्रमe loading biपंचांगap.
		 */
		अगर (ext4_मुक्त_inodes_count(sb, gdp) == 0)
			जाओ next_group;

		अगर (!(sbi->s_mount_state & EXT4_FC_REPLAY)) अणु
			grp = ext4_get_group_info(sb, group);
			/*
			 * Skip groups with alपढ़ोy-known suspicious inode
			 * tables
			 */
			अगर (EXT4_MB_GRP_IBITMAP_CORRUPT(grp))
				जाओ next_group;
		पूर्ण

		brअन्यथा(inode_biपंचांगap_bh);
		inode_biपंचांगap_bh = ext4_पढ़ो_inode_biपंचांगap(sb, group);
		/* Skip groups with suspicious inode tables */
		अगर (((!(sbi->s_mount_state & EXT4_FC_REPLAY))
		     && EXT4_MB_GRP_IBITMAP_CORRUPT(grp)) ||
		    IS_ERR(inode_biपंचांगap_bh)) अणु
			inode_biपंचांगap_bh = शून्य;
			जाओ next_group;
		पूर्ण

repeat_in_this_group:
		ret2 = find_inode_bit(sb, group, inode_biपंचांगap_bh, &ino);
		अगर (!ret2)
			जाओ next_group;

		अगर (group == 0 && (ino + 1) < EXT4_FIRST_INO(sb)) अणु
			ext4_error(sb, "reserved inode found cleared - "
				   "inode=%lu", ino + 1);
			ext4_mark_group_biपंचांगap_corrupted(sb, group,
					EXT4_GROUP_INFO_IBITMAP_CORRUPT);
			जाओ next_group;
		पूर्ण

		अगर ((!(sbi->s_mount_state & EXT4_FC_REPLAY)) && !handle) अणु
			BUG_ON(nblocks <= 0);
			handle = __ext4_journal_start_sb(dir->i_sb, line_no,
				 handle_type, nblocks, 0,
				 ext4_trans_शेष_revoke_credits(sb));
			अगर (IS_ERR(handle)) अणु
				err = PTR_ERR(handle);
				ext4_std_error(sb, err);
				जाओ out;
			पूर्ण
		पूर्ण
		BUFFER_TRACE(inode_biपंचांगap_bh, "get_write_access");
		err = ext4_journal_get_ग_लिखो_access(handle, inode_biपंचांगap_bh);
		अगर (err) अणु
			ext4_std_error(sb, err);
			जाओ out;
		पूर्ण
		ext4_lock_group(sb, group);
		ret2 = ext4_test_and_set_bit(ino, inode_biपंचांगap_bh->b_data);
		अगर (ret2) अणु
			/* Someone alपढ़ोy took the bit. Repeat the search
			 * with lock held.
			 */
			ret2 = find_inode_bit(sb, group, inode_biपंचांगap_bh, &ino);
			अगर (ret2) अणु
				ext4_set_bit(ino, inode_biपंचांगap_bh->b_data);
				ret2 = 0;
			पूर्ण अन्यथा अणु
				ret2 = 1; /* we didn't grab the inode */
			पूर्ण
		पूर्ण
		ext4_unlock_group(sb, group);
		ino++;		/* the inode biपंचांगap is zero-based */
		अगर (!ret2)
			जाओ got; /* we grabbed the inode! */

		अगर (ino < EXT4_INODES_PER_GROUP(sb))
			जाओ repeat_in_this_group;
next_group:
		अगर (++group == ngroups)
			group = 0;
	पूर्ण
	err = -ENOSPC;
	जाओ out;

got:
	BUFFER_TRACE(inode_biपंचांगap_bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_metadata(handle, शून्य, inode_biपंचांगap_bh);
	अगर (err) अणु
		ext4_std_error(sb, err);
		जाओ out;
	पूर्ण

	BUFFER_TRACE(group_desc_bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, group_desc_bh);
	अगर (err) अणु
		ext4_std_error(sb, err);
		जाओ out;
	पूर्ण

	/* We may have to initialize the block biपंचांगap अगर it isn't alपढ़ोy */
	अगर (ext4_has_group_desc_csum(sb) &&
	    gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) अणु
		काष्ठा buffer_head *block_biपंचांगap_bh;

		block_biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, group);
		अगर (IS_ERR(block_biपंचांगap_bh)) अणु
			err = PTR_ERR(block_biपंचांगap_bh);
			जाओ out;
		पूर्ण
		BUFFER_TRACE(block_biपंचांगap_bh, "get block bitmap access");
		err = ext4_journal_get_ग_लिखो_access(handle, block_biपंचांगap_bh);
		अगर (err) अणु
			brअन्यथा(block_biपंचांगap_bh);
			ext4_std_error(sb, err);
			जाओ out;
		पूर्ण

		BUFFER_TRACE(block_biपंचांगap_bh, "dirty block bitmap");
		err = ext4_handle_dirty_metadata(handle, शून्य, block_biपंचांगap_bh);

		/* recheck and clear flag under lock अगर we still need to */
		ext4_lock_group(sb, group);
		अगर (ext4_has_group_desc_csum(sb) &&
		    (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) अणु
			gdp->bg_flags &= cpu_to_le16(~EXT4_BG_BLOCK_UNINIT);
			ext4_मुक्त_group_clusters_set(sb, gdp,
				ext4_मुक्त_clusters_after_init(sb, group, gdp));
			ext4_block_biपंचांगap_csum_set(sb, group, gdp,
						   block_biपंचांगap_bh);
			ext4_group_desc_csum_set(sb, group, gdp);
		पूर्ण
		ext4_unlock_group(sb, group);
		brअन्यथा(block_biपंचांगap_bh);

		अगर (err) अणु
			ext4_std_error(sb, err);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Update the relevant bg descriptor fields */
	अगर (ext4_has_group_desc_csum(sb)) अणु
		पूर्णांक मुक्त;
		काष्ठा ext4_group_info *grp = शून्य;

		अगर (!(sbi->s_mount_state & EXT4_FC_REPLAY)) अणु
			grp = ext4_get_group_info(sb, group);
			करोwn_पढ़ो(&grp->alloc_sem); /*
						     * protect vs itable
						     * lazyinit
						     */
		पूर्ण
		ext4_lock_group(sb, group); /* जबतक we modअगरy the bg desc */
		मुक्त = EXT4_INODES_PER_GROUP(sb) -
			ext4_itable_unused_count(sb, gdp);
		अगर (gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_UNINIT)) अणु
			gdp->bg_flags &= cpu_to_le16(~EXT4_BG_INODE_UNINIT);
			मुक्त = 0;
		पूर्ण
		/*
		 * Check the relative inode number against the last used
		 * relative inode number in this group. अगर it is greater
		 * we need to update the bg_itable_unused count
		 */
		अगर (ino > मुक्त)
			ext4_itable_unused_set(sb, gdp,
					(EXT4_INODES_PER_GROUP(sb) - ino));
		अगर (!(sbi->s_mount_state & EXT4_FC_REPLAY))
			up_पढ़ो(&grp->alloc_sem);
	पूर्ण अन्यथा अणु
		ext4_lock_group(sb, group);
	पूर्ण

	ext4_मुक्त_inodes_set(sb, gdp, ext4_मुक्त_inodes_count(sb, gdp) - 1);
	अगर (S_ISसूची(mode)) अणु
		ext4_used_dirs_set(sb, gdp, ext4_used_dirs_count(sb, gdp) + 1);
		अगर (sbi->s_log_groups_per_flex) अणु
			ext4_group_t f = ext4_flex_group(sbi, group);

			atomic_inc(&sbi_array_rcu_deref(sbi, s_flex_groups,
							f)->used_dirs);
		पूर्ण
	पूर्ण
	अगर (ext4_has_group_desc_csum(sb)) अणु
		ext4_inode_biपंचांगap_csum_set(sb, group, gdp, inode_biपंचांगap_bh,
					   EXT4_INODES_PER_GROUP(sb) / 8);
		ext4_group_desc_csum_set(sb, group, gdp);
	पूर्ण
	ext4_unlock_group(sb, group);

	BUFFER_TRACE(group_desc_bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_metadata(handle, शून्य, group_desc_bh);
	अगर (err) अणु
		ext4_std_error(sb, err);
		जाओ out;
	पूर्ण

	percpu_counter_dec(&sbi->s_मुक्तinodes_counter);
	अगर (S_ISसूची(mode))
		percpu_counter_inc(&sbi->s_dirs_counter);

	अगर (sbi->s_log_groups_per_flex) अणु
		flex_group = ext4_flex_group(sbi, group);
		atomic_dec(&sbi_array_rcu_deref(sbi, s_flex_groups,
						flex_group)->मुक्त_inodes);
	पूर्ण

	inode->i_ino = ino + group * EXT4_INODES_PER_GROUP(sb);
	/* This is the optimal IO size (क्रम stat), not the fs block size */
	inode->i_blocks = 0;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	ei->i_crसमय = inode->i_mसमय;

	स_रखो(ei->i_data, 0, माप(ei->i_data));
	ei->i_dir_start_lookup = 0;
	ei->i_disksize = 0;

	/* Don't inherit extent flag from directory, amongst others. */
	ei->i_flags =
		ext4_mask_flags(mode, EXT4_I(dir)->i_flags & EXT4_FL_INHERITED);
	ei->i_flags |= i_flags;
	ei->i_file_acl = 0;
	ei->i_dसमय = 0;
	ei->i_block_group = group;
	ei->i_last_alloc_group = ~0;

	ext4_set_inode_flags(inode, true);
	अगर (IS_सूचीSYNC(inode))
		ext4_handle_sync(handle);
	अगर (insert_inode_locked(inode) < 0) अणु
		/*
		 * Likely a biपंचांगap corruption causing inode to be allocated
		 * twice.
		 */
		err = -EIO;
		ext4_error(sb, "failed to insert inode %lu: doubly allocated?",
			   inode->i_ino);
		ext4_mark_group_biपंचांगap_corrupted(sb, group,
					EXT4_GROUP_INFO_IBITMAP_CORRUPT);
		जाओ out;
	पूर्ण
	inode->i_generation = pअक्रमom_u32();

	/* Precompute checksum seed क्रम inode metadata */
	अगर (ext4_has_metadata_csum(sb)) अणु
		__u32 csum;
		__le32 inum = cpu_to_le32(inode->i_ino);
		__le32 gen = cpu_to_le32(inode->i_generation);
		csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&inum,
				   माप(inum));
		ei->i_csum_seed = ext4_chksum(sbi, csum, (__u8 *)&gen,
					      माप(gen));
	पूर्ण

	ext4_clear_state_flags(ei); /* Only relevant on 32-bit archs */
	ext4_set_inode_state(inode, EXT4_STATE_NEW);

	ei->i_extra_isize = sbi->s_want_extra_isize;
	ei->i_अंतरभूत_off = 0;
	अगर (ext4_has_feature_अंतरभूत_data(sb) &&
	    (!(ei->i_flags & EXT4_DAX_FL) || S_ISसूची(mode)))
		ext4_set_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
	ret = inode;
	err = dquot_alloc_inode(inode);
	अगर (err)
		जाओ fail_drop;

	/*
	 * Since the encryption xattr will always be unique, create it first so
	 * that it's less likely to end up in an बाह्यal xattr block and
	 * prevent its deduplication.
	 */
	अगर (encrypt) अणु
		err = fscrypt_set_context(inode, handle);
		अगर (err)
			जाओ fail_मुक्त_drop;
	पूर्ण

	अगर (!(ei->i_flags & EXT4_EA_INODE_FL)) अणु
		err = ext4_init_acl(handle, inode, dir);
		अगर (err)
			जाओ fail_मुक्त_drop;

		err = ext4_init_security(handle, inode, dir, qstr);
		अगर (err)
			जाओ fail_मुक्त_drop;
	पूर्ण

	अगर (ext4_has_feature_extents(sb)) अणु
		/* set extent flag only क्रम directory, file and normal symlink*/
		अगर (S_ISसूची(mode) || S_ISREG(mode) || S_ISLNK(mode)) अणु
			ext4_set_inode_flag(inode, EXT4_INODE_EXTENTS);
			ext4_ext_tree_init(handle, inode);
		पूर्ण
	पूर्ण

	अगर (ext4_handle_valid(handle)) अणु
		ei->i_sync_tid = handle->h_transaction->t_tid;
		ei->i_datasync_tid = handle->h_transaction->t_tid;
	पूर्ण

	err = ext4_mark_inode_dirty(handle, inode);
	अगर (err) अणु
		ext4_std_error(sb, err);
		जाओ fail_मुक्त_drop;
	पूर्ण

	ext4_debug("allocating inode %lu\n", inode->i_ino);
	trace_ext4_allocate_inode(inode, dir, mode);
	brअन्यथा(inode_biपंचांगap_bh);
	वापस ret;

fail_मुक्त_drop:
	dquot_मुक्त_inode(inode);
fail_drop:
	clear_nlink(inode);
	unlock_new_inode(inode);
out:
	dquot_drop(inode);
	inode->i_flags |= S_NOQUOTA;
	iput(inode);
	brअन्यथा(inode_biपंचांगap_bh);
	वापस ERR_PTR(err);
पूर्ण

/* Verअगरy that we are loading a valid orphan from disk */
काष्ठा inode *ext4_orphan_get(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	अचिन्हित दीर्घ max_ino = le32_to_cpu(EXT4_SB(sb)->s_es->s_inodes_count);
	ext4_group_t block_group;
	पूर्णांक bit;
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा inode *inode = शून्य;
	पूर्णांक err = -EFSCORRUPTED;

	अगर (ino < EXT4_FIRST_INO(sb) || ino > max_ino)
		जाओ bad_orphan;

	block_group = (ino - 1) / EXT4_INODES_PER_GROUP(sb);
	bit = (ino - 1) % EXT4_INODES_PER_GROUP(sb);
	biपंचांगap_bh = ext4_पढ़ो_inode_biपंचांगap(sb, block_group);
	अगर (IS_ERR(biपंचांगap_bh))
		वापस ERR_CAST(biपंचांगap_bh);

	/* Having the inode bit set should be a 100% indicator that this
	 * is a valid orphan (no e2fsck run on fs).  Orphans also include
	 * inodes that were being truncated, so we can't check i_nlink==0.
	 */
	अगर (!ext4_test_bit(bit, biपंचांगap_bh->b_data))
		जाओ bad_orphan;

	inode = ext4_iget(sb, ino, EXT4_IGET_NORMAL);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		ext4_error_err(sb, -err,
			       "couldn't read orphan inode %lu (err %d)",
			       ino, err);
		brअन्यथा(biपंचांगap_bh);
		वापस inode;
	पूर्ण

	/*
	 * If the orphans has i_nlinks > 0 then it should be able to
	 * be truncated, otherwise it won't be हटाओd from the orphan
	 * list during processing and an infinite loop will result.
	 * Similarly, it must not be a bad inode.
	 */
	अगर ((inode->i_nlink && !ext4_can_truncate(inode)) ||
	    is_bad_inode(inode))
		जाओ bad_orphan;

	अगर (NEXT_ORPHAN(inode) > max_ino)
		जाओ bad_orphan;
	brअन्यथा(biपंचांगap_bh);
	वापस inode;

bad_orphan:
	ext4_error(sb, "bad orphan inode %lu", ino);
	अगर (biपंचांगap_bh)
		prपूर्णांकk(KERN_ERR "ext4_test_bit(bit=%d, block=%llu) = %d\n",
		       bit, (अचिन्हित दीर्घ दीर्घ)biपंचांगap_bh->b_blocknr,
		       ext4_test_bit(bit, biपंचांगap_bh->b_data));
	अगर (inode) अणु
		prपूर्णांकk(KERN_ERR "is_bad_inode(inode)=%d\n",
		       is_bad_inode(inode));
		prपूर्णांकk(KERN_ERR "NEXT_ORPHAN(inode)=%u\n",
		       NEXT_ORPHAN(inode));
		prपूर्णांकk(KERN_ERR "max_ino=%lu\n", max_ino);
		prपूर्णांकk(KERN_ERR "i_nlink=%u\n", inode->i_nlink);
		/* Aव्योम मुक्तing blocks अगर we got a bad deleted inode */
		अगर (inode->i_nlink == 0)
			inode->i_blocks = 0;
		iput(inode);
	पूर्ण
	brअन्यथा(biपंचांगap_bh);
	वापस ERR_PTR(err);
पूर्ण

अचिन्हित दीर्घ ext4_count_मुक्त_inodes(काष्ठा super_block *sb)
अणु
	अचिन्हित दीर्घ desc_count;
	काष्ठा ext4_group_desc *gdp;
	ext4_group_t i, ngroups = ext4_get_groups_count(sb);
#अगर_घोषित EXT4FS_DEBUG
	काष्ठा ext4_super_block *es;
	अचिन्हित दीर्घ biपंचांगap_count, x;
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;

	es = EXT4_SB(sb)->s_es;
	desc_count = 0;
	biपंचांगap_count = 0;
	gdp = शून्य;
	क्रम (i = 0; i < ngroups; i++) अणु
		gdp = ext4_get_group_desc(sb, i, शून्य);
		अगर (!gdp)
			जारी;
		desc_count += ext4_मुक्त_inodes_count(sb, gdp);
		brअन्यथा(biपंचांगap_bh);
		biपंचांगap_bh = ext4_पढ़ो_inode_biपंचांगap(sb, i);
		अगर (IS_ERR(biपंचांगap_bh)) अणु
			biपंचांगap_bh = शून्य;
			जारी;
		पूर्ण

		x = ext4_count_मुक्त(biपंचांगap_bh->b_data,
				    EXT4_INODES_PER_GROUP(sb) / 8);
		prपूर्णांकk(KERN_DEBUG "group %lu: stored = %d, counted = %lu\n",
			(अचिन्हित दीर्घ) i, ext4_मुक्त_inodes_count(sb, gdp), x);
		biपंचांगap_count += x;
	पूर्ण
	brअन्यथा(biपंचांगap_bh);
	prपूर्णांकk(KERN_DEBUG "ext4_count_free_inodes: "
	       "stored = %u, computed = %lu, %lu\n",
	       le32_to_cpu(es->s_मुक्त_inodes_count), desc_count, biपंचांगap_count);
	वापस desc_count;
#अन्यथा
	desc_count = 0;
	क्रम (i = 0; i < ngroups; i++) अणु
		gdp = ext4_get_group_desc(sb, i, शून्य);
		अगर (!gdp)
			जारी;
		desc_count += ext4_मुक्त_inodes_count(sb, gdp);
		cond_resched();
	पूर्ण
	वापस desc_count;
#पूर्ण_अगर
पूर्ण

/* Called at mount-समय, super-block is locked */
अचिन्हित दीर्घ ext4_count_dirs(काष्ठा super_block * sb)
अणु
	अचिन्हित दीर्घ count = 0;
	ext4_group_t i, ngroups = ext4_get_groups_count(sb);

	क्रम (i = 0; i < ngroups; i++) अणु
		काष्ठा ext4_group_desc *gdp = ext4_get_group_desc(sb, i, शून्य);
		अगर (!gdp)
			जारी;
		count += ext4_used_dirs_count(sb, gdp);
	पूर्ण
	वापस count;
पूर्ण

/*
 * Zeroes not yet zeroed inode table - just ग_लिखो zeroes through the whole
 * inode table. Must be called without any spinlock held. The only place
 * where it is called from on active part of fileप्रणाली is ext4lazyinit
 * thपढ़ो, so we करो not need any special locks, however we have to prevent
 * inode allocation from the current group, so we take alloc_sem lock, to
 * block ext4_new_inode() until we are finished.
 */
पूर्णांक ext4_init_inode_table(काष्ठा super_block *sb, ext4_group_t group,
				 पूर्णांक barrier)
अणु
	काष्ठा ext4_group_info *grp = ext4_get_group_info(sb, group);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_group_desc *gdp = शून्य;
	काष्ठा buffer_head *group_desc_bh;
	handle_t *handle;
	ext4_fsblk_t blk;
	पूर्णांक num, ret = 0, used_blks = 0;
	अचिन्हित दीर्घ used_inos = 0;

	/* This should not happen, but just to be sure check this */
	अगर (sb_rकरोnly(sb)) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	gdp = ext4_get_group_desc(sb, group, &group_desc_bh);
	अगर (!gdp)
		जाओ out;

	/*
	 * We करो not need to lock this, because we are the only one
	 * handling this flag.
	 */
	अगर (gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_ZEROED))
		जाओ out;

	handle = ext4_journal_start_sb(sb, EXT4_HT_MISC, 1);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		जाओ out;
	पूर्ण

	करोwn_ग_लिखो(&grp->alloc_sem);
	/*
	 * If inode biपंचांगap was alपढ़ोy initialized there may be some
	 * used inodes so we need to skip blocks with used inodes in
	 * inode table.
	 */
	अगर (!(gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_UNINIT))) अणु
		used_inos = EXT4_INODES_PER_GROUP(sb) -
			    ext4_itable_unused_count(sb, gdp);
		used_blks = DIV_ROUND_UP(used_inos, sbi->s_inodes_per_block);

		/* Bogus inode unused count? */
		अगर (used_blks < 0 || used_blks > sbi->s_itb_per_group) अणु
			ext4_error(sb, "Something is wrong with group %u: "
				   "used itable blocks: %d; "
				   "itable unused count: %u",
				   group, used_blks,
				   ext4_itable_unused_count(sb, gdp));
			ret = 1;
			जाओ err_out;
		पूर्ण

		used_inos += group * EXT4_INODES_PER_GROUP(sb);
		/*
		 * Are there some uninitialized inodes in the inode table
		 * beक्रमe the first normal inode?
		 */
		अगर ((used_blks != sbi->s_itb_per_group) &&
		     (used_inos < EXT4_FIRST_INO(sb))) अणु
			ext4_error(sb, "Something is wrong with group %u: "
				   "itable unused count: %u; "
				   "itables initialized count: %ld",
				   group, ext4_itable_unused_count(sb, gdp),
				   used_inos);
			ret = 1;
			जाओ err_out;
		पूर्ण
	पूर्ण

	blk = ext4_inode_table(sb, gdp) + used_blks;
	num = sbi->s_itb_per_group - used_blks;

	BUFFER_TRACE(group_desc_bh, "get_write_access");
	ret = ext4_journal_get_ग_लिखो_access(handle,
					    group_desc_bh);
	अगर (ret)
		जाओ err_out;

	/*
	 * Skip zeroout अगर the inode table is full. But we set the ZEROED
	 * flag anyway, because obviously, when it is full it करोes not need
	 * further zeroing.
	 */
	अगर (unlikely(num == 0))
		जाओ skip_zeroout;

	ext4_debug("going to zero out inode table in group %d\n",
		   group);
	ret = sb_issue_zeroout(sb, blk, num, GFP_NOFS);
	अगर (ret < 0)
		जाओ err_out;
	अगर (barrier)
		blkdev_issue_flush(sb->s_bdev);

skip_zeroout:
	ext4_lock_group(sb, group);
	gdp->bg_flags |= cpu_to_le16(EXT4_BG_INODE_ZEROED);
	ext4_group_desc_csum_set(sb, group, gdp);
	ext4_unlock_group(sb, group);

	BUFFER_TRACE(group_desc_bh,
		     "call ext4_handle_dirty_metadata");
	ret = ext4_handle_dirty_metadata(handle, शून्य,
					 group_desc_bh);

err_out:
	up_ग_लिखो(&grp->alloc_sem);
	ext4_journal_stop(handle);
out:
	वापस ret;
पूर्ण
