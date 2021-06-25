<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMFS (as used by RIO Karma) file operations.
 * Copyright (C) 2005 Bob Copeland <me@bobcopeland.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mpage.h>
#समावेश "omfs.h"

अटल u32 omfs_max_extents(काष्ठा omfs_sb_info *sbi, पूर्णांक offset)
अणु
	वापस (sbi->s_sys_blocksize - offset -
		माप(काष्ठा omfs_extent)) /
		माप(काष्ठा omfs_extent_entry) + 1;
पूर्ण

व्योम omfs_make_empty_table(काष्ठा buffer_head *bh, पूर्णांक offset)
अणु
	काष्ठा omfs_extent *oe = (काष्ठा omfs_extent *) &bh->b_data[offset];

	oe->e_next = ~cpu_to_be64(0ULL);
	oe->e_extent_count = cpu_to_be32(1),
	oe->e_fill = cpu_to_be32(0x22),
	oe->e_entry.e_cluster = ~cpu_to_be64(0ULL);
	oe->e_entry.e_blocks = ~cpu_to_be64(0ULL);
पूर्ण

पूर्णांक omfs_shrink_inode(काष्ठा inode *inode)
अणु
	काष्ठा omfs_sb_info *sbi = OMFS_SB(inode->i_sb);
	काष्ठा omfs_extent *oe;
	काष्ठा omfs_extent_entry *entry;
	काष्ठा buffer_head *bh;
	u64 next, last;
	u32 extent_count;
	u32 max_extents;
	पूर्णांक ret;

	/* traverse extent table, मुक्तing each entry that is greater
	 * than inode->i_size;
	 */
	next = inode->i_ino;

	/* only support truncate -> 0 क्रम now */
	ret = -EIO;
	अगर (inode->i_size != 0)
		जाओ out;

	bh = omfs_bपढ़ो(inode->i_sb, next);
	अगर (!bh)
		जाओ out;

	oe = (काष्ठा omfs_extent *)(&bh->b_data[OMFS_EXTENT_START]);
	max_extents = omfs_max_extents(sbi, OMFS_EXTENT_START);

	क्रम (;;) अणु

		अगर (omfs_is_bad(sbi, (काष्ठा omfs_header *) bh->b_data, next))
			जाओ out_brअन्यथा;

		extent_count = be32_to_cpu(oe->e_extent_count);

		अगर (extent_count > max_extents)
			जाओ out_brअन्यथा;

		last = next;
		next = be64_to_cpu(oe->e_next);
		entry = &oe->e_entry;

		/* ignore last entry as it is the terminator */
		क्रम (; extent_count > 1; extent_count--) अणु
			u64 start, count;
			start = be64_to_cpu(entry->e_cluster);
			count = be64_to_cpu(entry->e_blocks);

			omfs_clear_range(inode->i_sb, start, (पूर्णांक) count);
			entry++;
		पूर्ण
		omfs_make_empty_table(bh, (अक्षर *) oe - bh->b_data);
		mark_buffer_dirty(bh);
		brअन्यथा(bh);

		अगर (last != inode->i_ino)
			omfs_clear_range(inode->i_sb, last, sbi->s_mirrors);

		अगर (next == ~0)
			अवरोध;

		bh = omfs_bपढ़ो(inode->i_sb, next);
		अगर (!bh)
			जाओ out;
		oe = (काष्ठा omfs_extent *) (&bh->b_data[OMFS_EXTENT_CONT]);
		max_extents = omfs_max_extents(sbi, OMFS_EXTENT_CONT);
	पूर्ण
	ret = 0;
out:
	वापस ret;
out_brअन्यथा:
	brअन्यथा(bh);
	वापस ret;
पूर्ण

अटल व्योम omfs_truncate(काष्ठा inode *inode)
अणु
	omfs_shrink_inode(inode);
	mark_inode_dirty(inode);
पूर्ण

/*
 * Add new blocks to the current extent, or create new entries/continuations
 * as necessary.
 */
अटल पूर्णांक omfs_grow_extent(काष्ठा inode *inode, काष्ठा omfs_extent *oe,
			u64 *ret_block)
अणु
	काष्ठा omfs_extent_entry *terminator;
	काष्ठा omfs_extent_entry *entry = &oe->e_entry;
	काष्ठा omfs_sb_info *sbi = OMFS_SB(inode->i_sb);
	u32 extent_count = be32_to_cpu(oe->e_extent_count);
	u64 new_block = 0;
	u32 max_count;
	पूर्णांक new_count;
	पूर्णांक ret = 0;

	/* reached the end of the extent table with no blocks mapped.
	 * there are three possibilities क्रम adding: grow last extent,
	 * add a new extent to the current extent table, and add a
	 * continuation inode.  in last two हालs need an allocator क्रम
	 * sbi->s_cluster_size
	 */

	/* TODO: handle holes */

	/* should always have a terminator */
	अगर (extent_count < 1)
		वापस -EIO;

	/* trivially grow current extent, अगर next block is not taken */
	terminator = entry + extent_count - 1;
	अगर (extent_count > 1) अणु
		entry = terminator-1;
		new_block = be64_to_cpu(entry->e_cluster) +
			be64_to_cpu(entry->e_blocks);

		अगर (omfs_allocate_block(inode->i_sb, new_block)) अणु
			be64_add_cpu(&entry->e_blocks, 1);
			terminator->e_blocks = ~(cpu_to_be64(
				be64_to_cpu(~terminator->e_blocks) + 1));
			जाओ out;
		पूर्ण
	पूर्ण
	max_count = omfs_max_extents(sbi, OMFS_EXTENT_START);

	/* TODO: add a continuation block here */
	अगर (be32_to_cpu(oe->e_extent_count) > max_count-1)
		वापस -EIO;

	/* try to allocate a new cluster */
	ret = omfs_allocate_range(inode->i_sb, 1, sbi->s_clustersize,
		&new_block, &new_count);
	अगर (ret)
		जाओ out_fail;

	/* copy terminator करोwn an entry */
	entry = terminator;
	terminator++;
	स_नकल(terminator, entry, माप(काष्ठा omfs_extent_entry));

	entry->e_cluster = cpu_to_be64(new_block);
	entry->e_blocks = cpu_to_be64((u64) new_count);

	terminator->e_blocks = ~(cpu_to_be64(
		be64_to_cpu(~terminator->e_blocks) + (u64) new_count));

	/* ग_लिखो in new entry */
	be32_add_cpu(&oe->e_extent_count, 1);

out:
	*ret_block = new_block;
out_fail:
	वापस ret;
पूर्ण

/*
 * Scans across the directory table क्रम a given file block number.
 * If block not found, वापस 0.
 */
अटल sector_t find_block(काष्ठा inode *inode, काष्ठा omfs_extent_entry *ent,
			sector_t block, पूर्णांक count, पूर्णांक *left)
अणु
	/* count > 1 because of terminator */
	sector_t searched = 0;
	क्रम (; count > 1; count--) अणु
		पूर्णांक numblocks = clus_to_blk(OMFS_SB(inode->i_sb),
			be64_to_cpu(ent->e_blocks));

		अगर (block >= searched  &&
		    block < searched + numblocks) अणु
			/*
			 * found it at cluster + (block - searched)
			 * numblocks - (block - searched) is reमुख्यder
			 */
			*left = numblocks - (block - searched);
			वापस clus_to_blk(OMFS_SB(inode->i_sb),
				be64_to_cpu(ent->e_cluster)) +
				block - searched;
		पूर्ण
		searched += numblocks;
		ent++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक omfs_get_block(काष्ठा inode *inode, sector_t block,
			  काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा buffer_head *bh;
	sector_t next, offset;
	पूर्णांक ret;
	u64 new_block;
	u32 max_extents;
	पूर्णांक extent_count;
	काष्ठा omfs_extent *oe;
	काष्ठा omfs_extent_entry *entry;
	काष्ठा omfs_sb_info *sbi = OMFS_SB(inode->i_sb);
	पूर्णांक max_blocks = bh_result->b_size >> inode->i_blkbits;
	पूर्णांक reमुख्य;

	ret = -EIO;
	bh = omfs_bपढ़ो(inode->i_sb, inode->i_ino);
	अगर (!bh)
		जाओ out;

	oe = (काष्ठा omfs_extent *)(&bh->b_data[OMFS_EXTENT_START]);
	max_extents = omfs_max_extents(sbi, OMFS_EXTENT_START);
	next = inode->i_ino;

	क्रम (;;) अणु

		अगर (omfs_is_bad(sbi, (काष्ठा omfs_header *) bh->b_data, next))
			जाओ out_brअन्यथा;

		extent_count = be32_to_cpu(oe->e_extent_count);
		next = be64_to_cpu(oe->e_next);
		entry = &oe->e_entry;

		अगर (extent_count > max_extents)
			जाओ out_brअन्यथा;

		offset = find_block(inode, entry, block, extent_count, &reमुख्य);
		अगर (offset > 0) अणु
			ret = 0;
			map_bh(bh_result, inode->i_sb, offset);
			अगर (reमुख्य > max_blocks)
				reमुख्य = max_blocks;
			bh_result->b_size = (reमुख्य << inode->i_blkbits);
			जाओ out_brअन्यथा;
		पूर्ण
		अगर (next == ~0)
			अवरोध;

		brअन्यथा(bh);
		bh = omfs_bपढ़ो(inode->i_sb, next);
		अगर (!bh)
			जाओ out;
		oe = (काष्ठा omfs_extent *) (&bh->b_data[OMFS_EXTENT_CONT]);
		max_extents = omfs_max_extents(sbi, OMFS_EXTENT_CONT);
	पूर्ण
	अगर (create) अणु
		ret = omfs_grow_extent(inode, oe, &new_block);
		अगर (ret == 0) अणु
			mark_buffer_dirty(bh);
			mark_inode_dirty(inode);
			map_bh(bh_result, inode->i_sb,
					clus_to_blk(sbi, new_block));
		पूर्ण
	पूर्ण
out_brअन्यथा:
	brअन्यथा(bh);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक omfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page, omfs_get_block);
पूर्ण

अटल व्योम omfs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, omfs_get_block);
पूर्ण

अटल पूर्णांक omfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, omfs_get_block, wbc);
पूर्ण

अटल पूर्णांक
omfs_ग_लिखोpages(काष्ठा address_space *mapping, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस mpage_ग_लिखोpages(mapping, wbc, omfs_get_block);
पूर्ण

अटल व्योम omfs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		omfs_truncate(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक omfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	ret = block_ग_लिखो_begin(mapping, pos, len, flags, pagep,
				omfs_get_block);
	अगर (unlikely(ret))
		omfs_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल sector_t omfs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, omfs_get_block);
पूर्ण

स्थिर काष्ठा file_operations omfs_file_operations = अणु
	.llseek = generic_file_llseek,
	.पढ़ो_iter = generic_file_पढ़ो_iter,
	.ग_लिखो_iter = generic_file_ग_लिखो_iter,
	.mmap = generic_file_mmap,
	.fsync = generic_file_fsync,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
पूर्ण;

अटल पूर्णांक omfs_setattr(काष्ठा user_namespace *mnt_userns,
			काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_पढ़ो(inode)) अणु
		error = inode_newsize_ok(inode, attr->ia_size);
		अगर (error)
			वापस error;
		truncate_setsize(inode, attr->ia_size);
		omfs_truncate(inode);
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations omfs_file_inops = अणु
	.setattr = omfs_setattr,
पूर्ण;

स्थिर काष्ठा address_space_operations omfs_aops = अणु
	.पढ़ोpage = omfs_पढ़ोpage,
	.पढ़ोahead = omfs_पढ़ोahead,
	.ग_लिखोpage = omfs_ग_लिखोpage,
	.ग_लिखोpages = omfs_ग_लिखोpages,
	.ग_लिखो_begin = omfs_ग_लिखो_begin,
	.ग_लिखो_end = generic_ग_लिखो_end,
	.bmap = omfs_bmap,
पूर्ण;

