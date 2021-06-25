<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext2/ialloc.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  BSD ufs-inspired inode and directory allocation by 
 *  Stephen Tweedie (sct@dcs.ed.ac.uk), 1993
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#समावेश <linux/quotaops.h>
#समावेश <linux/sched.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/अक्रमom.h>
#समावेश "ext2.h"
#समावेश "xattr.h"
#समावेश "acl.h"

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
 * Read the inode allocation biपंचांगap क्रम a given block_group, पढ़ोing
 * पूर्णांकo the specअगरied slot in the superblock's biपंचांगap cache.
 *
 * Return buffer_head of biपंचांगap on success or शून्य.
 */
अटल काष्ठा buffer_head *
पढ़ो_inode_biपंचांगap(काष्ठा super_block * sb, अचिन्हित दीर्घ block_group)
अणु
	काष्ठा ext2_group_desc *desc;
	काष्ठा buffer_head *bh = शून्य;

	desc = ext2_get_group_desc(sb, block_group, शून्य);
	अगर (!desc)
		जाओ error_out;

	bh = sb_bपढ़ो(sb, le32_to_cpu(desc->bg_inode_biपंचांगap));
	अगर (!bh)
		ext2_error(sb, "read_inode_bitmap",
			    "Cannot read inode bitmap - "
			    "block_group = %lu, inode_bitmap = %u",
			    block_group, le32_to_cpu(desc->bg_inode_biपंचांगap));
error_out:
	वापस bh;
पूर्ण

अटल व्योम ext2_release_inode(काष्ठा super_block *sb, पूर्णांक group, पूर्णांक dir)
अणु
	काष्ठा ext2_group_desc * desc;
	काष्ठा buffer_head *bh;

	desc = ext2_get_group_desc(sb, group, &bh);
	अगर (!desc) अणु
		ext2_error(sb, "ext2_release_inode",
			"can't get descriptor for group %d", group);
		वापस;
	पूर्ण

	spin_lock(sb_bgl_lock(EXT2_SB(sb), group));
	le16_add_cpu(&desc->bg_मुक्त_inodes_count, 1);
	अगर (dir)
		le16_add_cpu(&desc->bg_used_dirs_count, -1);
	spin_unlock(sb_bgl_lock(EXT2_SB(sb), group));
	percpu_counter_inc(&EXT2_SB(sb)->s_मुक्तinodes_counter);
	अगर (dir)
		percpu_counter_dec(&EXT2_SB(sb)->s_dirs_counter);
	mark_buffer_dirty(bh);
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
व्योम ext2_मुक्त_inode (काष्ठा inode * inode)
अणु
	काष्ठा super_block * sb = inode->i_sb;
	पूर्णांक is_directory;
	अचिन्हित दीर्घ ino;
	काष्ठा buffer_head *biपंचांगap_bh;
	अचिन्हित दीर्घ block_group;
	अचिन्हित दीर्घ bit;
	काष्ठा ext2_super_block * es;

	ino = inode->i_ino;
	ext2_debug ("freeing inode %lu\n", ino);

	/*
	 * Note: we must मुक्त any quota beक्रमe locking the superblock,
	 * as writing the quota to disk may need the lock as well.
	 */
	/* Quota is alपढ़ोy initialized in iput() */
	dquot_मुक्त_inode(inode);
	dquot_drop(inode);

	es = EXT2_SB(sb)->s_es;
	is_directory = S_ISसूची(inode->i_mode);

	अगर (ino < EXT2_FIRST_INO(sb) ||
	    ino > le32_to_cpu(es->s_inodes_count)) अणु
		ext2_error (sb, "ext2_free_inode",
			    "reserved or nonexistent inode %lu", ino);
		वापस;
	पूर्ण
	block_group = (ino - 1) / EXT2_INODES_PER_GROUP(sb);
	bit = (ino - 1) % EXT2_INODES_PER_GROUP(sb);
	biपंचांगap_bh = पढ़ो_inode_biपंचांगap(sb, block_group);
	अगर (!biपंचांगap_bh)
		वापस;

	/* Ok, now we can actually update the inode biपंचांगaps.. */
	अगर (!ext2_clear_bit_atomic(sb_bgl_lock(EXT2_SB(sb), block_group),
				bit, (व्योम *) biपंचांगap_bh->b_data))
		ext2_error (sb, "ext2_free_inode",
			      "bit already cleared for inode %lu", ino);
	अन्यथा
		ext2_release_inode(sb, block_group, is_directory);
	mark_buffer_dirty(biपंचांगap_bh);
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		sync_dirty_buffer(biपंचांगap_bh);

	brअन्यथा(biपंचांगap_bh);
पूर्ण

/*
 * We perक्रमm asynchronous preपढ़ोing of the new inode's inode block when
 * we create the inode, in the expectation that the inode will be written
 * back soon.  There are two reasons:
 *
 * - When creating a large number of files, the async preपढ़ोs will be
 *   nicely merged पूर्णांकo large पढ़ोs
 * - When writing out a large number of inodes, we करोn't need to keep on
 *   stalling the ग_लिखोs जबतक we पढ़ो the inode block.
 *
 * FIXME: ext2_get_group_desc() needs to be simplअगरied.
 */
अटल व्योम ext2_preपढ़ो_inode(काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ block_group;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ block;
	काष्ठा ext2_group_desc * gdp;
	काष्ठा backing_dev_info *bdi;

	bdi = inode_to_bdi(inode);
	अगर (bdi_rw_congested(bdi))
		वापस;

	block_group = (inode->i_ino - 1) / EXT2_INODES_PER_GROUP(inode->i_sb);
	gdp = ext2_get_group_desc(inode->i_sb, block_group, शून्य);
	अगर (gdp == शून्य)
		वापस;

	/*
	 * Figure out the offset within the block group inode table
	 */
	offset = ((inode->i_ino - 1) % EXT2_INODES_PER_GROUP(inode->i_sb)) *
				EXT2_INODE_SIZE(inode->i_sb);
	block = le32_to_cpu(gdp->bg_inode_table) +
				(offset >> EXT2_BLOCK_SIZE_BITS(inode->i_sb));
	sb_bपढ़ोahead(inode->i_sb, block);
पूर्ण

/*
 * There are two policies क्रम allocating an inode.  If the new inode is
 * a directory, then a क्रमward search is made क्रम a block group with both
 * मुक्त space and a low directory-to-inode ratio; अगर that fails, then of
 * the groups with above-average मुक्त space, that group with the fewest
 * directories alपढ़ोy is chosen.
 *
 * For other inodes, search क्रमward from the parent directory\'s block
 * group to find a मुक्त inode.
 */
अटल पूर्णांक find_group_dir(काष्ठा super_block *sb, काष्ठा inode *parent)
अणु
	पूर्णांक ngroups = EXT2_SB(sb)->s_groups_count;
	पूर्णांक aveमुक्तi = ext2_count_मुक्त_inodes(sb) / ngroups;
	काष्ठा ext2_group_desc *desc, *best_desc = शून्य;
	पूर्णांक group, best_group = -1;

	क्रम (group = 0; group < ngroups; group++) अणु
		desc = ext2_get_group_desc (sb, group, शून्य);
		अगर (!desc || !desc->bg_मुक्त_inodes_count)
			जारी;
		अगर (le16_to_cpu(desc->bg_मुक्त_inodes_count) < aveमुक्तi)
			जारी;
		अगर (!best_desc || 
		    (le16_to_cpu(desc->bg_मुक्त_blocks_count) >
		     le16_to_cpu(best_desc->bg_मुक्त_blocks_count))) अणु
			best_group = group;
			best_desc = desc;
		पूर्ण
	पूर्ण

	वापस best_group;
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
 * it's alपढ़ोy running too large debt (max_debt). 
 * Parent's group is preferred, if it doesn't satisfy these 
 * conditions we search cyclically through the rest. If none 
 * of the groups look good we just look क्रम a group with more 
 * मुक्त inodes than average (starting at parent's group). 
 * 
 * Debt is incremented each समय we allocate a directory and decremented 
 * when we allocate an inode, within 0--255. 
 */ 

#घोषणा INODE_COST 64
#घोषणा BLOCK_COST 256

अटल पूर्णांक find_group_orlov(काष्ठा super_block *sb, काष्ठा inode *parent)
अणु
	पूर्णांक parent_group = EXT2_I(parent)->i_block_group;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);
	काष्ठा ext2_super_block *es = sbi->s_es;
	पूर्णांक ngroups = sbi->s_groups_count;
	पूर्णांक inodes_per_group = EXT2_INODES_PER_GROUP(sb);
	पूर्णांक मुक्तi;
	पूर्णांक aveमुक्तi;
	पूर्णांक मुक्त_blocks;
	पूर्णांक aveमुक्तb;
	पूर्णांक blocks_per_dir;
	पूर्णांक ndirs;
	पूर्णांक max_debt, max_dirs, min_blocks, min_inodes;
	पूर्णांक group = -1, i;
	काष्ठा ext2_group_desc *desc;

	मुक्तi = percpu_counter_पढ़ो_positive(&sbi->s_मुक्तinodes_counter);
	aveमुक्तi = मुक्तi / ngroups;
	मुक्त_blocks = percpu_counter_पढ़ो_positive(&sbi->s_मुक्तblocks_counter);
	aveमुक्तb = मुक्त_blocks / ngroups;
	ndirs = percpu_counter_पढ़ो_positive(&sbi->s_dirs_counter);

	अगर ((parent == d_inode(sb->s_root)) ||
	    (EXT2_I(parent)->i_flags & EXT2_TOPसूची_FL)) अणु
		काष्ठा ext2_group_desc *best_desc = शून्य;
		पूर्णांक best_ndir = inodes_per_group;
		पूर्णांक best_group = -1;

		group = pअक्रमom_u32();
		parent_group = (अचिन्हित)group % ngroups;
		क्रम (i = 0; i < ngroups; i++) अणु
			group = (parent_group + i) % ngroups;
			desc = ext2_get_group_desc (sb, group, शून्य);
			अगर (!desc || !desc->bg_मुक्त_inodes_count)
				जारी;
			अगर (le16_to_cpu(desc->bg_used_dirs_count) >= best_ndir)
				जारी;
			अगर (le16_to_cpu(desc->bg_मुक्त_inodes_count) < aveमुक्तi)
				जारी;
			अगर (le16_to_cpu(desc->bg_मुक्त_blocks_count) < aveमुक्तb)
				जारी;
			best_group = group;
			best_ndir = le16_to_cpu(desc->bg_used_dirs_count);
			best_desc = desc;
		पूर्ण
		अगर (best_group >= 0) अणु
			desc = best_desc;
			group = best_group;
			जाओ found;
		पूर्ण
		जाओ fallback;
	पूर्ण

	अगर (ndirs == 0)
		ndirs = 1;	/* percpu_counters are approximate... */

	blocks_per_dir = (le32_to_cpu(es->s_blocks_count)-मुक्त_blocks) / ndirs;

	max_dirs = ndirs / ngroups + inodes_per_group / 16;
	min_inodes = aveमुक्तi - inodes_per_group / 4;
	min_blocks = aveमुक्तb - EXT2_BLOCKS_PER_GROUP(sb) / 4;

	max_debt = EXT2_BLOCKS_PER_GROUP(sb) / max(blocks_per_dir, BLOCK_COST);
	अगर (max_debt * INODE_COST > inodes_per_group)
		max_debt = inodes_per_group / INODE_COST;
	अगर (max_debt > 255)
		max_debt = 255;
	अगर (max_debt == 0)
		max_debt = 1;

	क्रम (i = 0; i < ngroups; i++) अणु
		group = (parent_group + i) % ngroups;
		desc = ext2_get_group_desc (sb, group, शून्य);
		अगर (!desc || !desc->bg_मुक्त_inodes_count)
			जारी;
		अगर (sbi->s_debts[group] >= max_debt)
			जारी;
		अगर (le16_to_cpu(desc->bg_used_dirs_count) >= max_dirs)
			जारी;
		अगर (le16_to_cpu(desc->bg_मुक्त_inodes_count) < min_inodes)
			जारी;
		अगर (le16_to_cpu(desc->bg_मुक्त_blocks_count) < min_blocks)
			जारी;
		जाओ found;
	पूर्ण

fallback:
	क्रम (i = 0; i < ngroups; i++) अणु
		group = (parent_group + i) % ngroups;
		desc = ext2_get_group_desc (sb, group, शून्य);
		अगर (!desc || !desc->bg_मुक्त_inodes_count)
			जारी;
		अगर (le16_to_cpu(desc->bg_मुक्त_inodes_count) >= aveमुक्तi)
			जाओ found;
	पूर्ण

	अगर (aveमुक्तi) अणु
		/*
		 * The मुक्त-inodes counter is approximate, and क्रम really small
		 * fileप्रणालीs the above test can fail to find any blockgroups
		 */
		aveमुक्तi = 0;
		जाओ fallback;
	पूर्ण

	वापस -1;

found:
	वापस group;
पूर्ण

अटल पूर्णांक find_group_other(काष्ठा super_block *sb, काष्ठा inode *parent)
अणु
	पूर्णांक parent_group = EXT2_I(parent)->i_block_group;
	पूर्णांक ngroups = EXT2_SB(sb)->s_groups_count;
	काष्ठा ext2_group_desc *desc;
	पूर्णांक group, i;

	/*
	 * Try to place the inode in its parent directory
	 */
	group = parent_group;
	desc = ext2_get_group_desc (sb, group, शून्य);
	अगर (desc && le16_to_cpu(desc->bg_मुक्त_inodes_count) &&
			le16_to_cpu(desc->bg_मुक्त_blocks_count))
		जाओ found;

	/*
	 * We're going to place this inode in a dअगरferent blockgroup from its
	 * parent.  We want to cause files in a common directory to all land in
	 * the same blockgroup.  But we want files which are in a dअगरferent
	 * directory which shares a blockgroup with our parent to land in a
	 * dअगरferent blockgroup.
	 *
	 * So add our directory's i_ino पूर्णांकo the starting poपूर्णांक क्रम the hash.
	 */
	group = (group + parent->i_ino) % ngroups;

	/*
	 * Use a quadratic hash to find a group with a मुक्त inode and some
	 * मुक्त blocks.
	 */
	क्रम (i = 1; i < ngroups; i <<= 1) अणु
		group += i;
		अगर (group >= ngroups)
			group -= ngroups;
		desc = ext2_get_group_desc (sb, group, शून्य);
		अगर (desc && le16_to_cpu(desc->bg_मुक्त_inodes_count) &&
				le16_to_cpu(desc->bg_मुक्त_blocks_count))
			जाओ found;
	पूर्ण

	/*
	 * That failed: try linear search क्रम a मुक्त inode, even अगर that group
	 * has no मुक्त blocks.
	 */
	group = parent_group;
	क्रम (i = 0; i < ngroups; i++) अणु
		अगर (++group >= ngroups)
			group = 0;
		desc = ext2_get_group_desc (sb, group, शून्य);
		अगर (desc && le16_to_cpu(desc->bg_मुक्त_inodes_count))
			जाओ found;
	पूर्ण

	वापस -1;

found:
	वापस group;
पूर्ण

काष्ठा inode *ext2_new_inode(काष्ठा inode *dir, umode_t mode,
			     स्थिर काष्ठा qstr *qstr)
अणु
	काष्ठा super_block *sb;
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा buffer_head *bh2;
	पूर्णांक group, i;
	ino_t ino = 0;
	काष्ठा inode * inode;
	काष्ठा ext2_group_desc *gdp;
	काष्ठा ext2_super_block *es;
	काष्ठा ext2_inode_info *ei;
	काष्ठा ext2_sb_info *sbi;
	पूर्णांक err;

	sb = dir->i_sb;
	inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	ei = EXT2_I(inode);
	sbi = EXT2_SB(sb);
	es = sbi->s_es;
	अगर (S_ISसूची(mode)) अणु
		अगर (test_opt(sb, OLDALLOC))
			group = find_group_dir(sb, dir);
		अन्यथा
			group = find_group_orlov(sb, dir);
	पूर्ण अन्यथा 
		group = find_group_other(sb, dir);

	अगर (group == -1) अणु
		err = -ENOSPC;
		जाओ fail;
	पूर्ण

	क्रम (i = 0; i < sbi->s_groups_count; i++) अणु
		gdp = ext2_get_group_desc(sb, group, &bh2);
		अगर (!gdp) अणु
			अगर (++group == sbi->s_groups_count)
				group = 0;
			जारी;
		पूर्ण
		brअन्यथा(biपंचांगap_bh);
		biपंचांगap_bh = पढ़ो_inode_biपंचांगap(sb, group);
		अगर (!biपंचांगap_bh) अणु
			err = -EIO;
			जाओ fail;
		पूर्ण
		ino = 0;

repeat_in_this_group:
		ino = ext2_find_next_zero_bit((अचिन्हित दीर्घ *)biपंचांगap_bh->b_data,
					      EXT2_INODES_PER_GROUP(sb), ino);
		अगर (ino >= EXT2_INODES_PER_GROUP(sb)) अणु
			/*
			 * Rare race: find_group_xx() decided that there were
			 * मुक्त inodes in this group, but by the समय we tried
			 * to allocate one, they're all gone.  This can also
			 * occur because the counters which find_group_orlov()
			 * uses are approximate.  So just go and search the
			 * next block group.
			 */
			अगर (++group == sbi->s_groups_count)
				group = 0;
			जारी;
		पूर्ण
		अगर (ext2_set_bit_atomic(sb_bgl_lock(sbi, group),
						ino, biपंचांगap_bh->b_data)) अणु
			/* we lost this inode */
			अगर (++ino >= EXT2_INODES_PER_GROUP(sb)) अणु
				/* this group is exhausted, try next group */
				अगर (++group == sbi->s_groups_count)
					group = 0;
				जारी;
			पूर्ण
			/* try to find मुक्त inode in the same group */
			जाओ repeat_in_this_group;
		पूर्ण
		जाओ got;
	पूर्ण

	/*
	 * Scanned all blockgroups.
	 */
	brअन्यथा(biपंचांगap_bh);
	err = -ENOSPC;
	जाओ fail;
got:
	mark_buffer_dirty(biपंचांगap_bh);
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		sync_dirty_buffer(biपंचांगap_bh);
	brअन्यथा(biपंचांगap_bh);

	ino += group * EXT2_INODES_PER_GROUP(sb) + 1;
	अगर (ino < EXT2_FIRST_INO(sb) || ino > le32_to_cpu(es->s_inodes_count)) अणु
		ext2_error (sb, "ext2_new_inode",
			    "reserved inode or inode > inodes count - "
			    "block_group = %d,inode=%lu", group,
			    (अचिन्हित दीर्घ) ino);
		err = -EIO;
		जाओ fail;
	पूर्ण

	percpu_counter_dec(&sbi->s_मुक्तinodes_counter);
	अगर (S_ISसूची(mode))
		percpu_counter_inc(&sbi->s_dirs_counter);

	spin_lock(sb_bgl_lock(sbi, group));
	le16_add_cpu(&gdp->bg_मुक्त_inodes_count, -1);
	अगर (S_ISसूची(mode)) अणु
		अगर (sbi->s_debts[group] < 255)
			sbi->s_debts[group]++;
		le16_add_cpu(&gdp->bg_used_dirs_count, 1);
	पूर्ण अन्यथा अणु
		अगर (sbi->s_debts[group])
			sbi->s_debts[group]--;
	पूर्ण
	spin_unlock(sb_bgl_lock(sbi, group));

	mark_buffer_dirty(bh2);
	अगर (test_opt(sb, GRPID)) अणु
		inode->i_mode = mode;
		inode->i_uid = current_fsuid();
		inode->i_gid = dir->i_gid;
	पूर्ण अन्यथा
		inode_init_owner(&init_user_ns, inode, dir, mode);

	inode->i_ino = ino;
	inode->i_blocks = 0;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	स_रखो(ei->i_data, 0, माप(ei->i_data));
	ei->i_flags =
		ext2_mask_flags(mode, EXT2_I(dir)->i_flags & EXT2_FL_INHERITED);
	ei->i_faddr = 0;
	ei->i_frag_no = 0;
	ei->i_frag_size = 0;
	ei->i_file_acl = 0;
	ei->i_dir_acl = 0;
	ei->i_dसमय = 0;
	ei->i_block_alloc_info = शून्य;
	ei->i_block_group = group;
	ei->i_dir_start_lookup = 0;
	ei->i_state = EXT2_STATE_NEW;
	ext2_set_inode_flags(inode);
	spin_lock(&sbi->s_next_gen_lock);
	inode->i_generation = sbi->s_next_generation++;
	spin_unlock(&sbi->s_next_gen_lock);
	अगर (insert_inode_locked(inode) < 0) अणु
		ext2_error(sb, "ext2_new_inode",
			   "inode number already in use - inode=%lu",
			   (अचिन्हित दीर्घ) ino);
		err = -EIO;
		जाओ fail;
	पूर्ण

	err = dquot_initialize(inode);
	अगर (err)
		जाओ fail_drop;

	err = dquot_alloc_inode(inode);
	अगर (err)
		जाओ fail_drop;

	err = ext2_init_acl(inode, dir);
	अगर (err)
		जाओ fail_मुक्त_drop;

	err = ext2_init_security(inode, dir, qstr);
	अगर (err)
		जाओ fail_मुक्त_drop;

	mark_inode_dirty(inode);
	ext2_debug("allocating inode %lu\n", inode->i_ino);
	ext2_preपढ़ो_inode(inode);
	वापस inode;

fail_मुक्त_drop:
	dquot_मुक्त_inode(inode);

fail_drop:
	dquot_drop(inode);
	inode->i_flags |= S_NOQUOTA;
	clear_nlink(inode);
	discard_new_inode(inode);
	वापस ERR_PTR(err);

fail:
	make_bad_inode(inode);
	iput(inode);
	वापस ERR_PTR(err);
पूर्ण

अचिन्हित दीर्घ ext2_count_मुक्त_inodes (काष्ठा super_block * sb)
अणु
	काष्ठा ext2_group_desc *desc;
	अचिन्हित दीर्घ desc_count = 0;
	पूर्णांक i;	

#अगर_घोषित EXT2FS_DEBUG
	काष्ठा ext2_super_block *es;
	अचिन्हित दीर्घ biपंचांगap_count = 0;
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;

	es = EXT2_SB(sb)->s_es;
	क्रम (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) अणु
		अचिन्हित x;

		desc = ext2_get_group_desc (sb, i, शून्य);
		अगर (!desc)
			जारी;
		desc_count += le16_to_cpu(desc->bg_मुक्त_inodes_count);
		brअन्यथा(biपंचांगap_bh);
		biपंचांगap_bh = पढ़ो_inode_biपंचांगap(sb, i);
		अगर (!biपंचांगap_bh)
			जारी;

		x = ext2_count_मुक्त(biपंचांगap_bh, EXT2_INODES_PER_GROUP(sb) / 8);
		prपूर्णांकk("group %d: stored = %d, counted = %u\n",
			i, le16_to_cpu(desc->bg_मुक्त_inodes_count), x);
		biपंचांगap_count += x;
	पूर्ण
	brअन्यथा(biपंचांगap_bh);
	prपूर्णांकk("ext2_count_free_inodes: stored = %lu, computed = %lu, %lu\n",
		(अचिन्हित दीर्घ)
		percpu_counter_पढ़ो(&EXT2_SB(sb)->s_मुक्तinodes_counter),
		desc_count, biपंचांगap_count);
	वापस desc_count;
#अन्यथा
	क्रम (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) अणु
		desc = ext2_get_group_desc (sb, i, शून्य);
		अगर (!desc)
			जारी;
		desc_count += le16_to_cpu(desc->bg_मुक्त_inodes_count);
	पूर्ण
	वापस desc_count;
#पूर्ण_अगर
पूर्ण

/* Called at mount-समय, super-block is locked */
अचिन्हित दीर्घ ext2_count_dirs (काष्ठा super_block * sb)
अणु
	अचिन्हित दीर्घ count = 0;
	पूर्णांक i;

	क्रम (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) अणु
		काष्ठा ext2_group_desc *gdp = ext2_get_group_desc (sb, i, शून्य);
		अगर (!gdp)
			जारी;
		count += le16_to_cpu(gdp->bg_used_dirs_count);
	पूर्ण
	वापस count;
पूर्ण

