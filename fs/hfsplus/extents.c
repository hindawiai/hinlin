<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/extents.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Handling of Extents both in catalog and extents overflow trees
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>

#समावेश "hfsplus_fs.h"
#समावेश "hfsplus_raw.h"

/* Compare two extents keys, वापसs 0 on same, pos/neg क्रम dअगरference */
पूर्णांक hfsplus_ext_cmp_key(स्थिर hfsplus_btree_key *k1,
			स्थिर hfsplus_btree_key *k2)
अणु
	__be32 k1id, k2id;
	__be32 k1s, k2s;

	k1id = k1->ext.cnid;
	k2id = k2->ext.cnid;
	अगर (k1id != k2id)
		वापस be32_to_cpu(k1id) < be32_to_cpu(k2id) ? -1 : 1;

	अगर (k1->ext.विभाजन_type != k2->ext.विभाजन_type)
		वापस k1->ext.विभाजन_type < k2->ext.विभाजन_type ? -1 : 1;

	k1s = k1->ext.start_block;
	k2s = k2->ext.start_block;
	अगर (k1s == k2s)
		वापस 0;
	वापस be32_to_cpu(k1s) < be32_to_cpu(k2s) ? -1 : 1;
पूर्ण

अटल व्योम hfsplus_ext_build_key(hfsplus_btree_key *key, u32 cnid,
				  u32 block, u8 type)
अणु
	key->key_len = cpu_to_be16(HFSPLUS_EXT_KEYLEN - 2);
	key->ext.cnid = cpu_to_be32(cnid);
	key->ext.start_block = cpu_to_be32(block);
	key->ext.विभाजन_type = type;
	key->ext.pad = 0;
पूर्ण

अटल u32 hfsplus_ext_find_block(काष्ठा hfsplus_extent *ext, u32 off)
अणु
	पूर्णांक i;
	u32 count;

	क्रम (i = 0; i < 8; ext++, i++) अणु
		count = be32_to_cpu(ext->block_count);
		अगर (off < count)
			वापस be32_to_cpu(ext->start_block) + off;
		off -= count;
	पूर्ण
	/* panic? */
	वापस 0;
पूर्ण

अटल पूर्णांक hfsplus_ext_block_count(काष्ठा hfsplus_extent *ext)
अणु
	पूर्णांक i;
	u32 count = 0;

	क्रम (i = 0; i < 8; ext++, i++)
		count += be32_to_cpu(ext->block_count);
	वापस count;
पूर्ण

अटल u32 hfsplus_ext_lastblock(काष्ठा hfsplus_extent *ext)
अणु
	पूर्णांक i;

	ext += 7;
	क्रम (i = 0; i < 7; ext--, i++)
		अगर (ext->block_count)
			अवरोध;
	वापस be32_to_cpu(ext->start_block) + be32_to_cpu(ext->block_count);
पूर्ण

अटल पूर्णांक __hfsplus_ext_ग_लिखो_extent(काष्ठा inode *inode,
		काष्ठा hfs_find_data *fd)
अणु
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	पूर्णांक res;

	WARN_ON(!mutex_is_locked(&hip->extents_lock));

	hfsplus_ext_build_key(fd->search_key, inode->i_ino, hip->cached_start,
			      HFSPLUS_IS_RSRC(inode) ?
				HFSPLUS_TYPE_RSRC : HFSPLUS_TYPE_DATA);

	res = hfs_brec_find(fd, hfs_find_rec_by_key);
	अगर (hip->extent_state & HFSPLUS_EXT_NEW) अणु
		अगर (res != -ENOENT)
			वापस res;
		/* Fail early and aव्योम ENOSPC during the btree operation */
		res = hfs_bmap_reserve(fd->tree, fd->tree->depth + 1);
		अगर (res)
			वापस res;
		hfs_brec_insert(fd, hip->cached_extents,
				माप(hfsplus_extent_rec));
		hip->extent_state &= ~(HFSPLUS_EXT_सूचीTY | HFSPLUS_EXT_NEW);
	पूर्ण अन्यथा अणु
		अगर (res)
			वापस res;
		hfs_bnode_ग_लिखो(fd->bnode, hip->cached_extents,
				fd->entryoffset, fd->entrylength);
		hip->extent_state &= ~HFSPLUS_EXT_सूचीTY;
	पूर्ण

	/*
	 * We can't just use hfsplus_mark_inode_dirty here, because we
	 * also get called from hfsplus_ग_लिखो_inode, which should not
	 * redirty the inode.  Instead the callers have to be careful
	 * to explicily mark the inode dirty, too.
	 */
	set_bit(HFSPLUS_I_EXT_सूचीTY, &hip->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक hfsplus_ext_ग_लिखो_extent_locked(काष्ठा inode *inode)
अणु
	पूर्णांक res = 0;

	अगर (HFSPLUS_I(inode)->extent_state & HFSPLUS_EXT_सूचीTY) अणु
		काष्ठा hfs_find_data fd;

		res = hfs_find_init(HFSPLUS_SB(inode->i_sb)->ext_tree, &fd);
		अगर (res)
			वापस res;
		res = __hfsplus_ext_ग_लिखो_extent(inode, &fd);
		hfs_find_निकास(&fd);
	पूर्ण
	वापस res;
पूर्ण

पूर्णांक hfsplus_ext_ग_लिखो_extent(काष्ठा inode *inode)
अणु
	पूर्णांक res;

	mutex_lock(&HFSPLUS_I(inode)->extents_lock);
	res = hfsplus_ext_ग_लिखो_extent_locked(inode);
	mutex_unlock(&HFSPLUS_I(inode)->extents_lock);

	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक __hfsplus_ext_पढ़ो_extent(काष्ठा hfs_find_data *fd,
					    काष्ठा hfsplus_extent *extent,
					    u32 cnid, u32 block, u8 type)
अणु
	पूर्णांक res;

	hfsplus_ext_build_key(fd->search_key, cnid, block, type);
	fd->key->ext.cnid = 0;
	res = hfs_brec_find(fd, hfs_find_rec_by_key);
	अगर (res && res != -ENOENT)
		वापस res;
	अगर (fd->key->ext.cnid != fd->search_key->ext.cnid ||
	    fd->key->ext.विभाजन_type != fd->search_key->ext.विभाजन_type)
		वापस -ENOENT;
	अगर (fd->entrylength != माप(hfsplus_extent_rec))
		वापस -EIO;
	hfs_bnode_पढ़ो(fd->bnode, extent, fd->entryoffset,
		माप(hfsplus_extent_rec));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __hfsplus_ext_cache_extent(काष्ठा hfs_find_data *fd,
		काष्ठा inode *inode, u32 block)
अणु
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	पूर्णांक res;

	WARN_ON(!mutex_is_locked(&hip->extents_lock));

	अगर (hip->extent_state & HFSPLUS_EXT_सूचीTY) अणु
		res = __hfsplus_ext_ग_लिखो_extent(inode, fd);
		अगर (res)
			वापस res;
	पूर्ण

	res = __hfsplus_ext_पढ़ो_extent(fd, hip->cached_extents, inode->i_ino,
					block, HFSPLUS_IS_RSRC(inode) ?
						HFSPLUS_TYPE_RSRC :
						HFSPLUS_TYPE_DATA);
	अगर (!res) अणु
		hip->cached_start = be32_to_cpu(fd->key->ext.start_block);
		hip->cached_blocks =
			hfsplus_ext_block_count(hip->cached_extents);
	पूर्ण अन्यथा अणु
		hip->cached_start = hip->cached_blocks = 0;
		hip->extent_state &= ~(HFSPLUS_EXT_सूचीTY | HFSPLUS_EXT_NEW);
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक hfsplus_ext_पढ़ो_extent(काष्ठा inode *inode, u32 block)
अणु
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	काष्ठा hfs_find_data fd;
	पूर्णांक res;

	अगर (block >= hip->cached_start &&
	    block < hip->cached_start + hip->cached_blocks)
		वापस 0;

	res = hfs_find_init(HFSPLUS_SB(inode->i_sb)->ext_tree, &fd);
	अगर (!res) अणु
		res = __hfsplus_ext_cache_extent(&fd, inode, block);
		hfs_find_निकास(&fd);
	पूर्ण
	वापस res;
पूर्ण

/* Get a block at iblock क्रम inode, possibly allocating अगर create */
पूर्णांक hfsplus_get_block(काष्ठा inode *inode, sector_t iblock,
		      काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	पूर्णांक res = -EIO;
	u32 ablock, dblock, mask;
	sector_t sector;
	पूर्णांक was_dirty = 0;

	/* Convert inode block to disk allocation block */
	ablock = iblock >> sbi->fs_shअगरt;

	अगर (iblock >= hip->fs_blocks) अणु
		अगर (!create)
			वापस 0;
		अगर (iblock > hip->fs_blocks)
			वापस -EIO;
		अगर (ablock >= hip->alloc_blocks) अणु
			res = hfsplus_file_extend(inode, false);
			अगर (res)
				वापस res;
		पूर्ण
	पूर्ण अन्यथा
		create = 0;

	अगर (ablock < hip->first_blocks) अणु
		dblock = hfsplus_ext_find_block(hip->first_extents, ablock);
		जाओ करोne;
	पूर्ण

	अगर (inode->i_ino == HFSPLUS_EXT_CNID)
		वापस -EIO;

	mutex_lock(&hip->extents_lock);

	/*
	 * hfsplus_ext_पढ़ो_extent will ग_लिखो out a cached extent पूर्णांकo
	 * the extents btree.  In that हाल we may have to mark the inode
	 * dirty even क्रम a pure पढ़ो of an extent here.
	 */
	was_dirty = (hip->extent_state & HFSPLUS_EXT_सूचीTY);
	res = hfsplus_ext_पढ़ो_extent(inode, ablock);
	अगर (res) अणु
		mutex_unlock(&hip->extents_lock);
		वापस -EIO;
	पूर्ण
	dblock = hfsplus_ext_find_block(hip->cached_extents,
					ablock - hip->cached_start);
	mutex_unlock(&hip->extents_lock);

करोne:
	hfs_dbg(EXTENT, "get_block(%lu): %llu - %u\n",
		inode->i_ino, (दीर्घ दीर्घ)iblock, dblock);

	mask = (1 << sbi->fs_shअगरt) - 1;
	sector = ((sector_t)dblock << sbi->fs_shअगरt) +
		  sbi->blockoffset + (iblock & mask);
	map_bh(bh_result, sb, sector);

	अगर (create) अणु
		set_buffer_new(bh_result);
		hip->phys_size += sb->s_blocksize;
		hip->fs_blocks++;
		inode_add_bytes(inode, sb->s_blocksize);
	पूर्ण
	अगर (create || was_dirty)
		mark_inode_dirty(inode);
	वापस 0;
पूर्ण

अटल व्योम hfsplus_dump_extent(काष्ठा hfsplus_extent *extent)
अणु
	पूर्णांक i;

	hfs_dbg(EXTENT, "   ");
	क्रम (i = 0; i < 8; i++)
		hfs_dbg_cont(EXTENT, " %u:%u",
			     be32_to_cpu(extent[i].start_block),
			     be32_to_cpu(extent[i].block_count));
	hfs_dbg_cont(EXTENT, "\n");
पूर्ण

अटल पूर्णांक hfsplus_add_extent(काष्ठा hfsplus_extent *extent, u32 offset,
			      u32 alloc_block, u32 block_count)
अणु
	u32 count, start;
	पूर्णांक i;

	hfsplus_dump_extent(extent);
	क्रम (i = 0; i < 8; extent++, i++) अणु
		count = be32_to_cpu(extent->block_count);
		अगर (offset == count) अणु
			start = be32_to_cpu(extent->start_block);
			अगर (alloc_block != start + count) अणु
				अगर (++i >= 8)
					वापस -ENOSPC;
				extent++;
				extent->start_block = cpu_to_be32(alloc_block);
			पूर्ण अन्यथा
				block_count += count;
			extent->block_count = cpu_to_be32(block_count);
			वापस 0;
		पूर्ण अन्यथा अगर (offset < count)
			अवरोध;
		offset -= count;
	पूर्ण
	/* panic? */
	वापस -EIO;
पूर्ण

अटल पूर्णांक hfsplus_मुक्त_extents(काष्ठा super_block *sb,
				काष्ठा hfsplus_extent *extent,
				u32 offset, u32 block_nr)
अणु
	u32 count, start;
	पूर्णांक i;
	पूर्णांक err = 0;

	/* Mapping the allocation file may lock the extent tree */
	WARN_ON(mutex_is_locked(&HFSPLUS_SB(sb)->ext_tree->tree_lock));

	hfsplus_dump_extent(extent);
	क्रम (i = 0; i < 8; extent++, i++) अणु
		count = be32_to_cpu(extent->block_count);
		अगर (offset == count)
			जाओ found;
		अन्यथा अगर (offset < count)
			अवरोध;
		offset -= count;
	पूर्ण
	/* panic? */
	वापस -EIO;
found:
	क्रम (;;) अणु
		start = be32_to_cpu(extent->start_block);
		अगर (count <= block_nr) अणु
			err = hfsplus_block_मुक्त(sb, start, count);
			अगर (err) अणु
				pr_err("can't free extent\n");
				hfs_dbg(EXTENT, " start: %u count: %u\n",
					start, count);
			पूर्ण
			extent->block_count = 0;
			extent->start_block = 0;
			block_nr -= count;
		पूर्ण अन्यथा अणु
			count -= block_nr;
			err = hfsplus_block_मुक्त(sb, start + count, block_nr);
			अगर (err) अणु
				pr_err("can't free extent\n");
				hfs_dbg(EXTENT, " start: %u count: %u\n",
					start, count);
			पूर्ण
			extent->block_count = cpu_to_be32(count);
			block_nr = 0;
		पूर्ण
		अगर (!block_nr || !i) अणु
			/*
			 * Try to मुक्त all extents and
			 * वापस only last error
			 */
			वापस err;
		पूर्ण
		i--;
		extent--;
		count = be32_to_cpu(extent->block_count);
	पूर्ण
पूर्ण

पूर्णांक hfsplus_मुक्त_विभाजन(काष्ठा super_block *sb, u32 cnid,
		काष्ठा hfsplus_विभाजन_raw *विभाजन, पूर्णांक type)
अणु
	काष्ठा hfs_find_data fd;
	hfsplus_extent_rec ext_entry;
	u32 total_blocks, blocks, start;
	पूर्णांक res, i;

	total_blocks = be32_to_cpu(विभाजन->total_blocks);
	अगर (!total_blocks)
		वापस 0;

	blocks = 0;
	क्रम (i = 0; i < 8; i++)
		blocks += be32_to_cpu(विभाजन->extents[i].block_count);

	res = hfsplus_मुक्त_extents(sb, विभाजन->extents, blocks, blocks);
	अगर (res)
		वापस res;
	अगर (total_blocks == blocks)
		वापस 0;

	res = hfs_find_init(HFSPLUS_SB(sb)->ext_tree, &fd);
	अगर (res)
		वापस res;
	करो अणु
		res = __hfsplus_ext_पढ़ो_extent(&fd, ext_entry, cnid,
						total_blocks, type);
		अगर (res)
			अवरोध;
		start = be32_to_cpu(fd.key->ext.start_block);
		hfs_brec_हटाओ(&fd);

		mutex_unlock(&fd.tree->tree_lock);
		hfsplus_मुक्त_extents(sb, ext_entry, total_blocks - start,
				     total_blocks);
		total_blocks = start;
		mutex_lock(&fd.tree->tree_lock);
	पूर्ण जबतक (total_blocks > blocks);
	hfs_find_निकास(&fd);

	वापस res;
पूर्ण

पूर्णांक hfsplus_file_extend(काष्ठा inode *inode, bool zeroout)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	u32 start, len, goal;
	पूर्णांक res;

	अगर (sbi->alloc_file->i_size * 8 <
	    sbi->total_blocks - sbi->मुक्त_blocks + 8) अणु
		/* extend alloc file */
		pr_err("extend alloc file! (%llu,%u,%u)\n",
		       sbi->alloc_file->i_size * 8,
		       sbi->total_blocks, sbi->मुक्त_blocks);
		वापस -ENOSPC;
	पूर्ण

	mutex_lock(&hip->extents_lock);
	अगर (hip->alloc_blocks == hip->first_blocks)
		goal = hfsplus_ext_lastblock(hip->first_extents);
	अन्यथा अणु
		res = hfsplus_ext_पढ़ो_extent(inode, hip->alloc_blocks);
		अगर (res)
			जाओ out;
		goal = hfsplus_ext_lastblock(hip->cached_extents);
	पूर्ण

	len = hip->clump_blocks;
	start = hfsplus_block_allocate(sb, sbi->total_blocks, goal, &len);
	अगर (start >= sbi->total_blocks) अणु
		start = hfsplus_block_allocate(sb, goal, 0, &len);
		अगर (start >= goal) अणु
			res = -ENOSPC;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (zeroout) अणु
		res = sb_issue_zeroout(sb, start, len, GFP_NOFS);
		अगर (res)
			जाओ out;
	पूर्ण

	hfs_dbg(EXTENT, "extend %lu: %u,%u\n", inode->i_ino, start, len);

	अगर (hip->alloc_blocks <= hip->first_blocks) अणु
		अगर (!hip->first_blocks) अणु
			hfs_dbg(EXTENT, "first extents\n");
			/* no extents yet */
			hip->first_extents[0].start_block = cpu_to_be32(start);
			hip->first_extents[0].block_count = cpu_to_be32(len);
			res = 0;
		पूर्ण अन्यथा अणु
			/* try to append to extents in inode */
			res = hfsplus_add_extent(hip->first_extents,
						 hip->alloc_blocks,
						 start, len);
			अगर (res == -ENOSPC)
				जाओ insert_extent;
		पूर्ण
		अगर (!res) अणु
			hfsplus_dump_extent(hip->first_extents);
			hip->first_blocks += len;
		पूर्ण
	पूर्ण अन्यथा अणु
		res = hfsplus_add_extent(hip->cached_extents,
					 hip->alloc_blocks - hip->cached_start,
					 start, len);
		अगर (!res) अणु
			hfsplus_dump_extent(hip->cached_extents);
			hip->extent_state |= HFSPLUS_EXT_सूचीTY;
			hip->cached_blocks += len;
		पूर्ण अन्यथा अगर (res == -ENOSPC)
			जाओ insert_extent;
	पूर्ण
out:
	अगर (!res) अणु
		hip->alloc_blocks += len;
		mutex_unlock(&hip->extents_lock);
		hfsplus_mark_inode_dirty(inode, HFSPLUS_I_ALLOC_सूचीTY);
		वापस 0;
	पूर्ण
	mutex_unlock(&hip->extents_lock);
	वापस res;

insert_extent:
	hfs_dbg(EXTENT, "insert new extent\n");
	res = hfsplus_ext_ग_लिखो_extent_locked(inode);
	अगर (res)
		जाओ out;

	स_रखो(hip->cached_extents, 0, माप(hfsplus_extent_rec));
	hip->cached_extents[0].start_block = cpu_to_be32(start);
	hip->cached_extents[0].block_count = cpu_to_be32(len);
	hfsplus_dump_extent(hip->cached_extents);
	hip->extent_state |= HFSPLUS_EXT_सूचीTY | HFSPLUS_EXT_NEW;
	hip->cached_start = hip->alloc_blocks;
	hip->cached_blocks = len;

	res = 0;
	जाओ out;
पूर्ण

व्योम hfsplus_file_truncate(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	काष्ठा hfs_find_data fd;
	u32 alloc_cnt, blk_cnt, start;
	पूर्णांक res;

	hfs_dbg(INODE, "truncate: %lu, %llu -> %llu\n",
		inode->i_ino, (दीर्घ दीर्घ)hip->phys_size, inode->i_size);

	अगर (inode->i_size > hip->phys_size) अणु
		काष्ठा address_space *mapping = inode->i_mapping;
		काष्ठा page *page;
		व्योम *fsdata;
		loff_t size = inode->i_size;

		res = pagecache_ग_लिखो_begin(शून्य, mapping, size, 0, 0,
					    &page, &fsdata);
		अगर (res)
			वापस;
		res = pagecache_ग_लिखो_end(शून्य, mapping, size,
			0, 0, page, fsdata);
		अगर (res < 0)
			वापस;
		mark_inode_dirty(inode);
		वापस;
	पूर्ण अन्यथा अगर (inode->i_size == hip->phys_size)
		वापस;

	blk_cnt = (inode->i_size + HFSPLUS_SB(sb)->alloc_blksz - 1) >>
			HFSPLUS_SB(sb)->alloc_blksz_shअगरt;

	mutex_lock(&hip->extents_lock);

	alloc_cnt = hip->alloc_blocks;
	अगर (blk_cnt == alloc_cnt)
		जाओ out_unlock;

	res = hfs_find_init(HFSPLUS_SB(sb)->ext_tree, &fd);
	अगर (res) अणु
		mutex_unlock(&hip->extents_lock);
		/* XXX: We lack error handling of hfsplus_file_truncate() */
		वापस;
	पूर्ण
	जबतक (1) अणु
		अगर (alloc_cnt == hip->first_blocks) अणु
			mutex_unlock(&fd.tree->tree_lock);
			hfsplus_मुक्त_extents(sb, hip->first_extents,
					     alloc_cnt, alloc_cnt - blk_cnt);
			hfsplus_dump_extent(hip->first_extents);
			hip->first_blocks = blk_cnt;
			mutex_lock(&fd.tree->tree_lock);
			अवरोध;
		पूर्ण
		res = __hfsplus_ext_cache_extent(&fd, inode, alloc_cnt);
		अगर (res)
			अवरोध;

		start = hip->cached_start;
		अगर (blk_cnt <= start)
			hfs_brec_हटाओ(&fd);
		mutex_unlock(&fd.tree->tree_lock);
		hfsplus_मुक्त_extents(sb, hip->cached_extents,
				     alloc_cnt - start, alloc_cnt - blk_cnt);
		hfsplus_dump_extent(hip->cached_extents);
		mutex_lock(&fd.tree->tree_lock);
		अगर (blk_cnt > start) अणु
			hip->extent_state |= HFSPLUS_EXT_सूचीTY;
			अवरोध;
		पूर्ण
		alloc_cnt = start;
		hip->cached_start = hip->cached_blocks = 0;
		hip->extent_state &= ~(HFSPLUS_EXT_सूचीTY | HFSPLUS_EXT_NEW);
	पूर्ण
	hfs_find_निकास(&fd);

	hip->alloc_blocks = blk_cnt;
out_unlock:
	mutex_unlock(&hip->extents_lock);
	hip->phys_size = inode->i_size;
	hip->fs_blocks = (inode->i_size + sb->s_blocksize - 1) >>
		sb->s_blocksize_bits;
	inode_set_bytes(inode, hip->fs_blocks << sb->s_blocksize_bits);
	hfsplus_mark_inode_dirty(inode, HFSPLUS_I_ALLOC_सूचीTY);
पूर्ण
