<शैली गुरु>
/*
 *  linux/fs/hfs/extent.c
 *
 * Copyright (C) 1995-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * This file contains the functions related to the extents B-tree.
 */

#समावेश <linux/pagemap.h>

#समावेश "hfs_fs.h"
#समावेश "btree.h"

/*================ File-local functions ================*/

/*
 * build_key
 */
अटल व्योम hfs_ext_build_key(hfs_btree_key *key, u32 cnid, u16 block, u8 type)
अणु
	key->key_len = 7;
	key->ext.FkType = type;
	key->ext.FNum = cpu_to_be32(cnid);
	key->ext.FABN = cpu_to_be16(block);
पूर्ण

/*
 * hfs_ext_compare()
 *
 * Description:
 *   This is the comparison function used क्रम the extents B-tree.  In
 *   comparing extent B-tree entries, the file id is the most
 *   signअगरicant field (compared as अचिन्हित पूर्णांकs); the विभाजन type is
 *   the second most signअगरicant field (compared as अचिन्हित अक्षरs);
 *   and the allocation block number field is the least signअगरicant
 *   (compared as अचिन्हित पूर्णांकs).
 * Input Variable(s):
 *   काष्ठा hfs_ext_key *key1: poपूर्णांकer to the first key to compare
 *   काष्ठा hfs_ext_key *key2: poपूर्णांकer to the second key to compare
 * Output Variable(s):
 *   NONE
 * Returns:
 *   पूर्णांक: negative अगर key1<key2, positive अगर key1>key2, and 0 अगर key1==key2
 * Preconditions:
 *   key1 and key2 poपूर्णांक to "valid" (काष्ठा hfs_ext_key)s.
 * Postconditions:
 *   This function has no side-effects */
पूर्णांक hfs_ext_keycmp(स्थिर btree_key *key1, स्थिर btree_key *key2)
अणु
	__be32 fnum1, fnum2;
	__be16 block1, block2;

	fnum1 = key1->ext.FNum;
	fnum2 = key2->ext.FNum;
	अगर (fnum1 != fnum2)
		वापस be32_to_cpu(fnum1) < be32_to_cpu(fnum2) ? -1 : 1;
	अगर (key1->ext.FkType != key2->ext.FkType)
		वापस key1->ext.FkType < key2->ext.FkType ? -1 : 1;

	block1 = key1->ext.FABN;
	block2 = key2->ext.FABN;
	अगर (block1 == block2)
		वापस 0;
	वापस be16_to_cpu(block1) < be16_to_cpu(block2) ? -1 : 1;
पूर्ण

/*
 * hfs_ext_find_block
 *
 * Find a block within an extent record
 */
अटल u16 hfs_ext_find_block(काष्ठा hfs_extent *ext, u16 off)
अणु
	पूर्णांक i;
	u16 count;

	क्रम (i = 0; i < 3; ext++, i++) अणु
		count = be16_to_cpu(ext->count);
		अगर (off < count)
			वापस be16_to_cpu(ext->block) + off;
		off -= count;
	पूर्ण
	/* panic? */
	वापस 0;
पूर्ण

अटल पूर्णांक hfs_ext_block_count(काष्ठा hfs_extent *ext)
अणु
	पूर्णांक i;
	u16 count = 0;

	क्रम (i = 0; i < 3; ext++, i++)
		count += be16_to_cpu(ext->count);
	वापस count;
पूर्ण

अटल u16 hfs_ext_lastblock(काष्ठा hfs_extent *ext)
अणु
	पूर्णांक i;

	ext += 2;
	क्रम (i = 0; i < 2; ext--, i++)
		अगर (ext->count)
			अवरोध;
	वापस be16_to_cpu(ext->block) + be16_to_cpu(ext->count);
पूर्ण

अटल पूर्णांक __hfs_ext_ग_लिखो_extent(काष्ठा inode *inode, काष्ठा hfs_find_data *fd)
अणु
	पूर्णांक res;

	hfs_ext_build_key(fd->search_key, inode->i_ino, HFS_I(inode)->cached_start,
			  HFS_IS_RSRC(inode) ?  HFS_FK_RSRC : HFS_FK_DATA);
	res = hfs_brec_find(fd);
	अगर (HFS_I(inode)->flags & HFS_FLG_EXT_NEW) अणु
		अगर (res != -ENOENT)
			वापस res;
		/* Fail early and aव्योम ENOSPC during the btree operation */
		res = hfs_bmap_reserve(fd->tree, fd->tree->depth + 1);
		अगर (res)
			वापस res;
		hfs_brec_insert(fd, HFS_I(inode)->cached_extents, माप(hfs_extent_rec));
		HFS_I(inode)->flags &= ~(HFS_FLG_EXT_सूचीTY|HFS_FLG_EXT_NEW);
	पूर्ण अन्यथा अणु
		अगर (res)
			वापस res;
		hfs_bnode_ग_लिखो(fd->bnode, HFS_I(inode)->cached_extents, fd->entryoffset, fd->entrylength);
		HFS_I(inode)->flags &= ~HFS_FLG_EXT_सूचीTY;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक hfs_ext_ग_लिखो_extent(काष्ठा inode *inode)
अणु
	काष्ठा hfs_find_data fd;
	पूर्णांक res = 0;

	अगर (HFS_I(inode)->flags & HFS_FLG_EXT_सूचीTY) अणु
		res = hfs_find_init(HFS_SB(inode->i_sb)->ext_tree, &fd);
		अगर (res)
			वापस res;
		res = __hfs_ext_ग_लिखो_extent(inode, &fd);
		hfs_find_निकास(&fd);
	पूर्ण
	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक __hfs_ext_पढ़ो_extent(काष्ठा hfs_find_data *fd, काष्ठा hfs_extent *extent,
					u32 cnid, u32 block, u8 type)
अणु
	पूर्णांक res;

	hfs_ext_build_key(fd->search_key, cnid, block, type);
	fd->key->ext.FNum = 0;
	res = hfs_brec_find(fd);
	अगर (res && res != -ENOENT)
		वापस res;
	अगर (fd->key->ext.FNum != fd->search_key->ext.FNum ||
	    fd->key->ext.FkType != fd->search_key->ext.FkType)
		वापस -ENOENT;
	अगर (fd->entrylength != माप(hfs_extent_rec))
		वापस -EIO;
	hfs_bnode_पढ़ो(fd->bnode, extent, fd->entryoffset, माप(hfs_extent_rec));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __hfs_ext_cache_extent(काष्ठा hfs_find_data *fd, काष्ठा inode *inode, u32 block)
अणु
	पूर्णांक res;

	अगर (HFS_I(inode)->flags & HFS_FLG_EXT_सूचीTY) अणु
		res = __hfs_ext_ग_लिखो_extent(inode, fd);
		अगर (res)
			वापस res;
	पूर्ण

	res = __hfs_ext_पढ़ो_extent(fd, HFS_I(inode)->cached_extents, inode->i_ino,
				    block, HFS_IS_RSRC(inode) ? HFS_FK_RSRC : HFS_FK_DATA);
	अगर (!res) अणु
		HFS_I(inode)->cached_start = be16_to_cpu(fd->key->ext.FABN);
		HFS_I(inode)->cached_blocks = hfs_ext_block_count(HFS_I(inode)->cached_extents);
	पूर्ण अन्यथा अणु
		HFS_I(inode)->cached_start = HFS_I(inode)->cached_blocks = 0;
		HFS_I(inode)->flags &= ~(HFS_FLG_EXT_सूचीTY|HFS_FLG_EXT_NEW);
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक hfs_ext_पढ़ो_extent(काष्ठा inode *inode, u16 block)
अणु
	काष्ठा hfs_find_data fd;
	पूर्णांक res;

	अगर (block >= HFS_I(inode)->cached_start &&
	    block < HFS_I(inode)->cached_start + HFS_I(inode)->cached_blocks)
		वापस 0;

	res = hfs_find_init(HFS_SB(inode->i_sb)->ext_tree, &fd);
	अगर (!res) अणु
		res = __hfs_ext_cache_extent(&fd, inode, block);
		hfs_find_निकास(&fd);
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम hfs_dump_extent(काष्ठा hfs_extent *extent)
अणु
	पूर्णांक i;

	hfs_dbg(EXTENT, "   ");
	क्रम (i = 0; i < 3; i++)
		hfs_dbg_cont(EXTENT, " %u:%u",
			     be16_to_cpu(extent[i].block),
			     be16_to_cpu(extent[i].count));
	hfs_dbg_cont(EXTENT, "\n");
पूर्ण

अटल पूर्णांक hfs_add_extent(काष्ठा hfs_extent *extent, u16 offset,
			  u16 alloc_block, u16 block_count)
अणु
	u16 count, start;
	पूर्णांक i;

	hfs_dump_extent(extent);
	क्रम (i = 0; i < 3; extent++, i++) अणु
		count = be16_to_cpu(extent->count);
		अगर (offset == count) अणु
			start = be16_to_cpu(extent->block);
			अगर (alloc_block != start + count) अणु
				अगर (++i >= 3)
					वापस -ENOSPC;
				extent++;
				extent->block = cpu_to_be16(alloc_block);
			पूर्ण अन्यथा
				block_count += count;
			extent->count = cpu_to_be16(block_count);
			वापस 0;
		पूर्ण अन्यथा अगर (offset < count)
			अवरोध;
		offset -= count;
	पूर्ण
	/* panic? */
	वापस -EIO;
पूर्ण

अटल पूर्णांक hfs_मुक्त_extents(काष्ठा super_block *sb, काष्ठा hfs_extent *extent,
			    u16 offset, u16 block_nr)
अणु
	u16 count, start;
	पूर्णांक i;

	hfs_dump_extent(extent);
	क्रम (i = 0; i < 3; extent++, i++) अणु
		count = be16_to_cpu(extent->count);
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
		start = be16_to_cpu(extent->block);
		अगर (count <= block_nr) अणु
			hfs_clear_vbm_bits(sb, start, count);
			extent->block = 0;
			extent->count = 0;
			block_nr -= count;
		पूर्ण अन्यथा अणु
			count -= block_nr;
			hfs_clear_vbm_bits(sb, start + count, block_nr);
			extent->count = cpu_to_be16(count);
			block_nr = 0;
		पूर्ण
		अगर (!block_nr || !i)
			वापस 0;
		i--;
		extent--;
		count = be16_to_cpu(extent->count);
	पूर्ण
पूर्ण

पूर्णांक hfs_मुक्त_विभाजन(काष्ठा super_block *sb, काष्ठा hfs_cat_file *file, पूर्णांक type)
अणु
	काष्ठा hfs_find_data fd;
	u32 total_blocks, blocks, start;
	u32 cnid = be32_to_cpu(file->FlNum);
	काष्ठा hfs_extent *extent;
	पूर्णांक res, i;

	अगर (type == HFS_FK_DATA) अणु
		total_blocks = be32_to_cpu(file->PyLen);
		extent = file->ExtRec;
	पूर्ण अन्यथा अणु
		total_blocks = be32_to_cpu(file->RPyLen);
		extent = file->RExtRec;
	पूर्ण
	total_blocks /= HFS_SB(sb)->alloc_blksz;
	अगर (!total_blocks)
		वापस 0;

	blocks = 0;
	क्रम (i = 0; i < 3; i++)
		blocks += be16_to_cpu(extent[i].count);

	res = hfs_मुक्त_extents(sb, extent, blocks, blocks);
	अगर (res)
		वापस res;
	अगर (total_blocks == blocks)
		वापस 0;

	res = hfs_find_init(HFS_SB(sb)->ext_tree, &fd);
	अगर (res)
		वापस res;
	करो अणु
		res = __hfs_ext_पढ़ो_extent(&fd, extent, cnid, total_blocks, type);
		अगर (res)
			अवरोध;
		start = be16_to_cpu(fd.key->ext.FABN);
		hfs_मुक्त_extents(sb, extent, total_blocks - start, total_blocks);
		hfs_brec_हटाओ(&fd);
		total_blocks = start;
	पूर्ण जबतक (total_blocks > blocks);
	hfs_find_निकास(&fd);

	वापस res;
पूर्ण

/*
 * hfs_get_block
 */
पूर्णांक hfs_get_block(काष्ठा inode *inode, sector_t block,
		  काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा super_block *sb;
	u16 dblock, ablock;
	पूर्णांक res;

	sb = inode->i_sb;
	/* Convert inode block to disk allocation block */
	ablock = (u32)block / HFS_SB(sb)->fs_भाग;

	अगर (block >= HFS_I(inode)->fs_blocks) अणु
		अगर (!create)
			वापस 0;
		अगर (block > HFS_I(inode)->fs_blocks)
			वापस -EIO;
		अगर (ablock >= HFS_I(inode)->alloc_blocks) अणु
			res = hfs_extend_file(inode);
			अगर (res)
				वापस res;
		पूर्ण
	पूर्ण अन्यथा
		create = 0;

	अगर (ablock < HFS_I(inode)->first_blocks) अणु
		dblock = hfs_ext_find_block(HFS_I(inode)->first_extents, ablock);
		जाओ करोne;
	पूर्ण

	mutex_lock(&HFS_I(inode)->extents_lock);
	res = hfs_ext_पढ़ो_extent(inode, ablock);
	अगर (!res)
		dblock = hfs_ext_find_block(HFS_I(inode)->cached_extents,
					    ablock - HFS_I(inode)->cached_start);
	अन्यथा अणु
		mutex_unlock(&HFS_I(inode)->extents_lock);
		वापस -EIO;
	पूर्ण
	mutex_unlock(&HFS_I(inode)->extents_lock);

करोne:
	map_bh(bh_result, sb, HFS_SB(sb)->fs_start +
	       dblock * HFS_SB(sb)->fs_भाग +
	       (u32)block % HFS_SB(sb)->fs_भाग);

	अगर (create) अणु
		set_buffer_new(bh_result);
		HFS_I(inode)->phys_size += sb->s_blocksize;
		HFS_I(inode)->fs_blocks++;
		inode_add_bytes(inode, sb->s_blocksize);
		mark_inode_dirty(inode);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक hfs_extend_file(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	u32 start, len, goal;
	पूर्णांक res;

	mutex_lock(&HFS_I(inode)->extents_lock);
	अगर (HFS_I(inode)->alloc_blocks == HFS_I(inode)->first_blocks)
		goal = hfs_ext_lastblock(HFS_I(inode)->first_extents);
	अन्यथा अणु
		res = hfs_ext_पढ़ो_extent(inode, HFS_I(inode)->alloc_blocks);
		अगर (res)
			जाओ out;
		goal = hfs_ext_lastblock(HFS_I(inode)->cached_extents);
	पूर्ण

	len = HFS_I(inode)->clump_blocks;
	start = hfs_vbm_search_मुक्त(sb, goal, &len);
	अगर (!len) अणु
		res = -ENOSPC;
		जाओ out;
	पूर्ण

	hfs_dbg(EXTENT, "extend %lu: %u,%u\n", inode->i_ino, start, len);
	अगर (HFS_I(inode)->alloc_blocks == HFS_I(inode)->first_blocks) अणु
		अगर (!HFS_I(inode)->first_blocks) अणु
			hfs_dbg(EXTENT, "first extents\n");
			/* no extents yet */
			HFS_I(inode)->first_extents[0].block = cpu_to_be16(start);
			HFS_I(inode)->first_extents[0].count = cpu_to_be16(len);
			res = 0;
		पूर्ण अन्यथा अणु
			/* try to append to extents in inode */
			res = hfs_add_extent(HFS_I(inode)->first_extents,
					     HFS_I(inode)->alloc_blocks,
					     start, len);
			अगर (res == -ENOSPC)
				जाओ insert_extent;
		पूर्ण
		अगर (!res) अणु
			hfs_dump_extent(HFS_I(inode)->first_extents);
			HFS_I(inode)->first_blocks += len;
		पूर्ण
	पूर्ण अन्यथा अणु
		res = hfs_add_extent(HFS_I(inode)->cached_extents,
				     HFS_I(inode)->alloc_blocks -
				     HFS_I(inode)->cached_start,
				     start, len);
		अगर (!res) अणु
			hfs_dump_extent(HFS_I(inode)->cached_extents);
			HFS_I(inode)->flags |= HFS_FLG_EXT_सूचीTY;
			HFS_I(inode)->cached_blocks += len;
		पूर्ण अन्यथा अगर (res == -ENOSPC)
			जाओ insert_extent;
	पूर्ण
out:
	mutex_unlock(&HFS_I(inode)->extents_lock);
	अगर (!res) अणु
		HFS_I(inode)->alloc_blocks += len;
		mark_inode_dirty(inode);
		अगर (inode->i_ino < HFS_FIRSTUSER_CNID)
			set_bit(HFS_FLG_ALT_MDB_सूचीTY, &HFS_SB(sb)->flags);
		set_bit(HFS_FLG_MDB_सूचीTY, &HFS_SB(sb)->flags);
		hfs_mark_mdb_dirty(sb);
	पूर्ण
	वापस res;

insert_extent:
	hfs_dbg(EXTENT, "insert new extent\n");
	res = hfs_ext_ग_लिखो_extent(inode);
	अगर (res)
		जाओ out;

	स_रखो(HFS_I(inode)->cached_extents, 0, माप(hfs_extent_rec));
	HFS_I(inode)->cached_extents[0].block = cpu_to_be16(start);
	HFS_I(inode)->cached_extents[0].count = cpu_to_be16(len);
	hfs_dump_extent(HFS_I(inode)->cached_extents);
	HFS_I(inode)->flags |= HFS_FLG_EXT_सूचीTY|HFS_FLG_EXT_NEW;
	HFS_I(inode)->cached_start = HFS_I(inode)->alloc_blocks;
	HFS_I(inode)->cached_blocks = len;

	res = 0;
	जाओ out;
पूर्ण

व्योम hfs_file_truncate(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfs_find_data fd;
	u16 blk_cnt, alloc_cnt, start;
	u32 size;
	पूर्णांक res;

	hfs_dbg(INODE, "truncate: %lu, %Lu -> %Lu\n",
		inode->i_ino, (दीर्घ दीर्घ)HFS_I(inode)->phys_size,
		inode->i_size);
	अगर (inode->i_size > HFS_I(inode)->phys_size) अणु
		काष्ठा address_space *mapping = inode->i_mapping;
		व्योम *fsdata;
		काष्ठा page *page;

		/* XXX: Can use generic_cont_expand? */
		size = inode->i_size - 1;
		res = pagecache_ग_लिखो_begin(शून्य, mapping, size+1, 0, 0,
					    &page, &fsdata);
		अगर (!res) अणु
			res = pagecache_ग_लिखो_end(शून्य, mapping, size+1, 0, 0,
					page, fsdata);
		पूर्ण
		अगर (res)
			inode->i_size = HFS_I(inode)->phys_size;
		वापस;
	पूर्ण अन्यथा अगर (inode->i_size == HFS_I(inode)->phys_size)
		वापस;
	size = inode->i_size + HFS_SB(sb)->alloc_blksz - 1;
	blk_cnt = size / HFS_SB(sb)->alloc_blksz;
	alloc_cnt = HFS_I(inode)->alloc_blocks;
	अगर (blk_cnt == alloc_cnt)
		जाओ out;

	mutex_lock(&HFS_I(inode)->extents_lock);
	res = hfs_find_init(HFS_SB(sb)->ext_tree, &fd);
	अगर (res) अणु
		mutex_unlock(&HFS_I(inode)->extents_lock);
		/* XXX: We lack error handling of hfs_file_truncate() */
		वापस;
	पूर्ण
	जबतक (1) अणु
		अगर (alloc_cnt == HFS_I(inode)->first_blocks) अणु
			hfs_मुक्त_extents(sb, HFS_I(inode)->first_extents,
					 alloc_cnt, alloc_cnt - blk_cnt);
			hfs_dump_extent(HFS_I(inode)->first_extents);
			HFS_I(inode)->first_blocks = blk_cnt;
			अवरोध;
		पूर्ण
		res = __hfs_ext_cache_extent(&fd, inode, alloc_cnt);
		अगर (res)
			अवरोध;
		start = HFS_I(inode)->cached_start;
		hfs_मुक्त_extents(sb, HFS_I(inode)->cached_extents,
				 alloc_cnt - start, alloc_cnt - blk_cnt);
		hfs_dump_extent(HFS_I(inode)->cached_extents);
		अगर (blk_cnt > start) अणु
			HFS_I(inode)->flags |= HFS_FLG_EXT_सूचीTY;
			अवरोध;
		पूर्ण
		alloc_cnt = start;
		HFS_I(inode)->cached_start = HFS_I(inode)->cached_blocks = 0;
		HFS_I(inode)->flags &= ~(HFS_FLG_EXT_सूचीTY|HFS_FLG_EXT_NEW);
		hfs_brec_हटाओ(&fd);
	पूर्ण
	hfs_find_निकास(&fd);
	mutex_unlock(&HFS_I(inode)->extents_lock);

	HFS_I(inode)->alloc_blocks = blk_cnt;
out:
	HFS_I(inode)->phys_size = inode->i_size;
	HFS_I(inode)->fs_blocks = (inode->i_size + sb->s_blocksize - 1) >> sb->s_blocksize_bits;
	inode_set_bytes(inode, HFS_I(inode)->fs_blocks << sb->s_blocksize_bits);
	mark_inode_dirty(inode);
पूर्ण
