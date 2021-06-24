<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched/mm.h>
#समावेश <crypto/hash.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "volumes.h"
#समावेश "print-tree.h"
#समावेश "compression.h"

#घोषणा __MAX_CSUM_ITEMS(r, size) ((अचिन्हित दीर्घ)(((BTRFS_LEAF_DATA_SIZE(r) - \
				   माप(काष्ठा btrfs_item) * 2) / \
				  size) - 1))

#घोषणा MAX_CSUM_ITEMS(r, size) (min_t(u32, __MAX_CSUM_ITEMS(r, size), \
				       PAGE_SIZE))

/**
 * Set inode's size according to fileप्रणाली options
 *
 * @inode:      inode we want to update the disk_i_size क्रम
 * @new_i_size: i_size we want to set to, 0 अगर we use i_size
 *
 * With NO_HOLES set this simply sets the disk_is_size to whatever i_size_पढ़ो()
 * वापसs as it is perfectly fine with a file that has holes without hole file
 * extent items.
 *
 * However without NO_HOLES we need to only वापस the area that is contiguous
 * from the 0 offset of the file.  Otherwise we could end up adjust i_size up
 * to an extent that has a gap in between.
 *
 * Finally new_i_size should only be set in the हाल of truncate where we're not
 * पढ़ोy to use i_size_पढ़ो() as the limiter yet.
 */
व्योम btrfs_inode_safe_disk_i_size_ग_लिखो(काष्ठा btrfs_inode *inode, u64 new_i_size)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	u64 start, end, i_size;
	पूर्णांक ret;

	i_size = new_i_size ?: i_size_पढ़ो(&inode->vfs_inode);
	अगर (btrfs_fs_incompat(fs_info, NO_HOLES)) अणु
		inode->disk_i_size = i_size;
		वापस;
	पूर्ण

	spin_lock(&inode->lock);
	ret = find_contiguous_extent_bit(&inode->file_extent_tree, 0, &start,
					 &end, EXTENT_सूचीTY);
	अगर (!ret && start == 0)
		i_size = min(i_size, end + 1);
	अन्यथा
		i_size = 0;
	inode->disk_i_size = i_size;
	spin_unlock(&inode->lock);
पूर्ण

/**
 * Mark range within a file as having a new extent inserted
 *
 * @inode: inode being modअगरied
 * @start: start file offset of the file extent we've inserted
 * @len:   logical length of the file extent item
 *
 * Call when we are inserting a new file extent where there was none beक्रमe.
 * Does not need to call this in the हाल where we're replacing an existing file
 * extent, however अगर not sure it's fine to call this multiple बार.
 *
 * The start and len must match the file extent item, so thus must be sectorsize
 * aligned.
 */
पूर्णांक btrfs_inode_set_file_extent_range(काष्ठा btrfs_inode *inode, u64 start,
				      u64 len)
अणु
	अगर (len == 0)
		वापस 0;

	ASSERT(IS_ALIGNED(start + len, inode->root->fs_info->sectorsize));

	अगर (btrfs_fs_incompat(inode->root->fs_info, NO_HOLES))
		वापस 0;
	वापस set_extent_bits(&inode->file_extent_tree, start, start + len - 1,
			       EXTENT_सूचीTY);
पूर्ण

/**
 * Marks an inode range as not having a backing extent
 *
 * @inode: inode being modअगरied
 * @start: start file offset of the file extent we've inserted
 * @len:   logical length of the file extent item
 *
 * Called when we drop a file extent, क्रम example when we truncate.  Doesn't
 * need to be called क्रम हालs where we're replacing a file extent, like when
 * we've COWed a file extent.
 *
 * The start and len must match the file extent item, so thus must be sectorsize
 * aligned.
 */
पूर्णांक btrfs_inode_clear_file_extent_range(काष्ठा btrfs_inode *inode, u64 start,
					u64 len)
अणु
	अगर (len == 0)
		वापस 0;

	ASSERT(IS_ALIGNED(start + len, inode->root->fs_info->sectorsize) ||
	       len == (u64)-1);

	अगर (btrfs_fs_incompat(inode->root->fs_info, NO_HOLES))
		वापस 0;
	वापस clear_extent_bit(&inode->file_extent_tree, start,
				start + len - 1, EXTENT_सूचीTY, 0, 0, शून्य);
पूर्ण

अटल अंतरभूत u32 max_ordered_sum_bytes(काष्ठा btrfs_fs_info *fs_info,
					u16 csum_size)
अणु
	u32 ncsums = (PAGE_SIZE - माप(काष्ठा btrfs_ordered_sum)) / csum_size;

	वापस ncsums * fs_info->sectorsize;
पूर्ण

पूर्णांक btrfs_insert_file_extent(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     u64 objectid, u64 pos,
			     u64 disk_offset, u64 disk_num_bytes,
			     u64 num_bytes, u64 offset, u64 ram_bytes,
			     u8 compression, u8 encryption, u16 other_encoding)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_file_extent_item *item;
	काष्ठा btrfs_key file_key;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	file_key.objectid = objectid;
	file_key.offset = pos;
	file_key.type = BTRFS_EXTENT_DATA_KEY;

	ret = btrfs_insert_empty_item(trans, root, path, &file_key,
				      माप(*item));
	अगर (ret < 0)
		जाओ out;
	BUG_ON(ret); /* Can't happen */
	leaf = path->nodes[0];
	item = btrfs_item_ptr(leaf, path->slots[0],
			      काष्ठा btrfs_file_extent_item);
	btrfs_set_file_extent_disk_bytenr(leaf, item, disk_offset);
	btrfs_set_file_extent_disk_num_bytes(leaf, item, disk_num_bytes);
	btrfs_set_file_extent_offset(leaf, item, offset);
	btrfs_set_file_extent_num_bytes(leaf, item, num_bytes);
	btrfs_set_file_extent_ram_bytes(leaf, item, ram_bytes);
	btrfs_set_file_extent_generation(leaf, item, trans->transid);
	btrfs_set_file_extent_type(leaf, item, BTRFS_खाता_EXTENT_REG);
	btrfs_set_file_extent_compression(leaf, item, compression);
	btrfs_set_file_extent_encryption(leaf, item, encryption);
	btrfs_set_file_extent_other_encoding(leaf, item, other_encoding);

	btrfs_mark_buffer_dirty(leaf);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल काष्ठा btrfs_csum_item *
btrfs_lookup_csum(काष्ठा btrfs_trans_handle *trans,
		  काष्ठा btrfs_root *root,
		  काष्ठा btrfs_path *path,
		  u64 bytenr, पूर्णांक cow)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret;
	काष्ठा btrfs_key file_key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_csum_item *item;
	काष्ठा extent_buffer *leaf;
	u64 csum_offset = 0;
	स्थिर u32 csum_size = fs_info->csum_size;
	पूर्णांक csums_in_item;

	file_key.objectid = BTRFS_EXTENT_CSUM_OBJECTID;
	file_key.offset = bytenr;
	file_key.type = BTRFS_EXTENT_CSUM_KEY;
	ret = btrfs_search_slot(trans, root, &file_key, path, 0, cow);
	अगर (ret < 0)
		जाओ fail;
	leaf = path->nodes[0];
	अगर (ret > 0) अणु
		ret = 1;
		अगर (path->slots[0] == 0)
			जाओ fail;
		path->slots[0]--;
		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
		अगर (found_key.type != BTRFS_EXTENT_CSUM_KEY)
			जाओ fail;

		csum_offset = (bytenr - found_key.offset) >>
				fs_info->sectorsize_bits;
		csums_in_item = btrfs_item_size_nr(leaf, path->slots[0]);
		csums_in_item /= csum_size;

		अगर (csum_offset == csums_in_item) अणु
			ret = -EFBIG;
			जाओ fail;
		पूर्ण अन्यथा अगर (csum_offset > csums_in_item) अणु
			जाओ fail;
		पूर्ण
	पूर्ण
	item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_csum_item);
	item = (काष्ठा btrfs_csum_item *)((अचिन्हित अक्षर *)item +
					  csum_offset * csum_size);
	वापस item;
fail:
	अगर (ret > 0)
		ret = -ENOENT;
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक btrfs_lookup_file_extent(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     काष्ठा btrfs_path *path, u64 objectid,
			     u64 offset, पूर्णांक mod)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key file_key;
	पूर्णांक ins_len = mod < 0 ? -1 : 0;
	पूर्णांक cow = mod != 0;

	file_key.objectid = objectid;
	file_key.offset = offset;
	file_key.type = BTRFS_EXTENT_DATA_KEY;
	ret = btrfs_search_slot(trans, root, &file_key, path, ins_len, cow);
	वापस ret;
पूर्ण

/*
 * Find checksums क्रम logical bytenr range [disk_bytenr, disk_bytenr + len) and
 * estore the result to @dst.
 *
 * Return >0 क्रम the number of sectors we found.
 * Return 0 क्रम the range [disk_bytenr, disk_bytenr + sectorsize) has no csum
 * क्रम it. Caller may want to try next sector until one range is hit.
 * Return <0 क्रम fatal error.
 */
अटल पूर्णांक search_csum_tree(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_path *path, u64 disk_bytenr,
			    u64 len, u8 *dst)
अणु
	काष्ठा btrfs_csum_item *item = शून्य;
	काष्ठा btrfs_key key;
	स्थिर u32 sectorsize = fs_info->sectorsize;
	स्थिर u32 csum_size = fs_info->csum_size;
	u32 itemsize;
	पूर्णांक ret;
	u64 csum_start;
	u64 csum_len;

	ASSERT(IS_ALIGNED(disk_bytenr, sectorsize) &&
	       IS_ALIGNED(len, sectorsize));

	/* Check अगर the current csum item covers disk_bytenr */
	अगर (path->nodes[0]) अणु
		item = btrfs_item_ptr(path->nodes[0], path->slots[0],
				      काष्ठा btrfs_csum_item);
		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
		itemsize = btrfs_item_size_nr(path->nodes[0], path->slots[0]);

		csum_start = key.offset;
		csum_len = (itemsize / csum_size) * sectorsize;

		अगर (in_range(disk_bytenr, csum_start, csum_len))
			जाओ found;
	पूर्ण

	/* Current item करोesn't contain the desired range, search again */
	btrfs_release_path(path);
	item = btrfs_lookup_csum(शून्य, fs_info->csum_root, path, disk_bytenr, 0);
	अगर (IS_ERR(item)) अणु
		ret = PTR_ERR(item);
		जाओ out;
	पूर्ण
	btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
	itemsize = btrfs_item_size_nr(path->nodes[0], path->slots[0]);

	csum_start = key.offset;
	csum_len = (itemsize / csum_size) * sectorsize;
	ASSERT(in_range(disk_bytenr, csum_start, csum_len));

found:
	ret = (min(csum_start + csum_len, disk_bytenr + len) -
		   disk_bytenr) >> fs_info->sectorsize_bits;
	पढ़ो_extent_buffer(path->nodes[0], dst, (अचिन्हित दीर्घ)item,
			ret * csum_size);
out:
	अगर (ret == -ENOENT)
		ret = 0;
	वापस ret;
पूर्ण

/*
 * Locate the file_offset of @cur_disk_bytenr of a @bio.
 *
 * Bio of btrfs represents पढ़ो range of
 * [bi_sector << 9, bi_sector << 9 + bi_size).
 * Knowing this, we can iterate through each bvec to locate the page beदीर्घ to
 * @cur_disk_bytenr and get the file offset.
 *
 * @inode is used to determine अगर the bvec page really beदीर्घs to @inode.
 *
 * Return 0 अगर we can't find the file offset
 * Return >0 अगर we find the file offset and restore it to @file_offset_ret
 */
अटल पूर्णांक search_file_offset_in_bio(काष्ठा bio *bio, काष्ठा inode *inode,
				     u64 disk_bytenr, u64 *file_offset_ret)
अणु
	काष्ठा bvec_iter iter;
	काष्ठा bio_vec bvec;
	u64 cur = bio->bi_iter.bi_sector << SECTOR_SHIFT;
	पूर्णांक ret = 0;

	bio_क्रम_each_segment(bvec, bio, iter) अणु
		काष्ठा page *page = bvec.bv_page;

		अगर (cur > disk_bytenr)
			अवरोध;
		अगर (cur + bvec.bv_len <= disk_bytenr) अणु
			cur += bvec.bv_len;
			जारी;
		पूर्ण
		ASSERT(in_range(disk_bytenr, cur, bvec.bv_len));
		अगर (page->mapping && page->mapping->host &&
		    page->mapping->host == inode) अणु
			ret = 1;
			*file_offset_ret = page_offset(page) + bvec.bv_offset +
					   disk_bytenr - cur;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * Lookup the checksum क्रम the पढ़ो bio in csum tree.
 *
 * @inode: inode that the bio is क्रम.
 * @bio: bio to look up.
 * @dst: Buffer of size nblocks * btrfs_super_csum_size() used to वापस
 *       checksum (nblocks = bio->bi_iter.bi_size / fs_info->sectorsize). If
 *       शून्य, the checksum buffer is allocated and वापसed in
 *       btrfs_io_bio(bio)->csum instead.
 *
 * Return: BLK_STS_RESOURCE अगर allocating memory fails, BLK_STS_OK otherwise.
 */
blk_status_t btrfs_lookup_bio_sums(काष्ठा inode *inode, काष्ठा bio *bio, u8 *dst)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	काष्ठा btrfs_path *path;
	स्थिर u32 sectorsize = fs_info->sectorsize;
	स्थिर u32 csum_size = fs_info->csum_size;
	u32 orig_len = bio->bi_iter.bi_size;
	u64 orig_disk_bytenr = bio->bi_iter.bi_sector << SECTOR_SHIFT;
	u64 cur_disk_bytenr;
	u8 *csum;
	स्थिर अचिन्हित पूर्णांक nblocks = orig_len >> fs_info->sectorsize_bits;
	पूर्णांक count = 0;

	अगर (!fs_info->csum_root || (BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM))
		वापस BLK_STS_OK;

	/*
	 * This function is only called क्रम पढ़ो bio.
	 *
	 * This means two things:
	 * - All our csums should only be in csum tree
	 *   No ordered extents csums, as ordered extents are only क्रम ग_लिखो
	 *   path.
	 * - No need to bother any other info from bvec
	 *   Since we're looking up csums, the only important info is the
	 *   disk_bytenr and the length, which can be extracted from bi_iter
	 *   directly.
	 */
	ASSERT(bio_op(bio) == REQ_OP_READ);
	path = btrfs_alloc_path();
	अगर (!path)
		वापस BLK_STS_RESOURCE;

	अगर (!dst) अणु
		काष्ठा btrfs_io_bio *btrfs_bio = btrfs_io_bio(bio);

		अगर (nblocks * csum_size > BTRFS_BIO_INLINE_CSUM_SIZE) अणु
			btrfs_bio->csum = kदो_स्मृति_array(nblocks, csum_size,
							GFP_NOFS);
			अगर (!btrfs_bio->csum) अणु
				btrfs_मुक्त_path(path);
				वापस BLK_STS_RESOURCE;
			पूर्ण
		पूर्ण अन्यथा अणु
			btrfs_bio->csum = btrfs_bio->csum_अंतरभूत;
		पूर्ण
		csum = btrfs_bio->csum;
	पूर्ण अन्यथा अणु
		csum = dst;
	पूर्ण

	/*
	 * If requested number of sectors is larger than one leaf can contain,
	 * kick the पढ़ोahead क्रम csum tree.
	 */
	अगर (nblocks > fs_info->csums_per_leaf)
		path->पढ़ोa = READA_FORWARD;

	/*
	 * the मुक्त space stuff is only पढ़ो when it hasn't been
	 * updated in the current transaction.  So, we can safely
	 * पढ़ो from the commit root and sidestep a nasty deadlock
	 * between पढ़ोing the मुक्त space cache and updating the csum tree.
	 */
	अगर (btrfs_is_मुक्त_space_inode(BTRFS_I(inode))) अणु
		path->search_commit_root = 1;
		path->skip_locking = 1;
	पूर्ण

	क्रम (cur_disk_bytenr = orig_disk_bytenr;
	     cur_disk_bytenr < orig_disk_bytenr + orig_len;
	     cur_disk_bytenr += (count * sectorsize)) अणु
		u64 search_len = orig_disk_bytenr + orig_len - cur_disk_bytenr;
		अचिन्हित पूर्णांक sector_offset;
		u8 *csum_dst;

		/*
		 * Although both cur_disk_bytenr and orig_disk_bytenr is u64,
		 * we're calculating the offset to the bio start.
		 *
		 * Bio size is limited to अच_पूर्णांक_उच्च, thus अचिन्हित पूर्णांक is large
		 * enough to contain the raw result, not to mention the right
		 * shअगरted result.
		 */
		ASSERT(cur_disk_bytenr - orig_disk_bytenr < अच_पूर्णांक_उच्च);
		sector_offset = (cur_disk_bytenr - orig_disk_bytenr) >>
				fs_info->sectorsize_bits;
		csum_dst = csum + sector_offset * csum_size;

		count = search_csum_tree(fs_info, path, cur_disk_bytenr,
					 search_len, csum_dst);
		अगर (count <= 0) अणु
			/*
			 * Either we hit a critical error or we didn't find
			 * the csum.
			 * Either way, we put zero पूर्णांकo the csums dst, and skip
			 * to the next sector.
			 */
			स_रखो(csum_dst, 0, csum_size);
			count = 1;

			/*
			 * For data reloc inode, we need to mark the range
			 * NODATASUM so that balance won't report false csum
			 * error.
			 */
			अगर (BTRFS_I(inode)->root->root_key.objectid ==
			    BTRFS_DATA_RELOC_TREE_OBJECTID) अणु
				u64 file_offset;
				पूर्णांक ret;

				ret = search_file_offset_in_bio(bio, inode,
						cur_disk_bytenr, &file_offset);
				अगर (ret)
					set_extent_bits(io_tree, file_offset,
						file_offset + sectorsize - 1,
						EXTENT_NODATASUM);
			पूर्ण अन्यथा अणु
				btrfs_warn_rl(fs_info,
			"csum hole found for disk bytenr range [%llu, %llu)",
				cur_disk_bytenr, cur_disk_bytenr + sectorsize);
			पूर्ण
		पूर्ण
	पूर्ण

	btrfs_मुक्त_path(path);
	वापस BLK_STS_OK;
पूर्ण

पूर्णांक btrfs_lookup_csums_range(काष्ठा btrfs_root *root, u64 start, u64 end,
			     काष्ठा list_head *list, पूर्णांक search_commit)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_ordered_sum *sums;
	काष्ठा btrfs_csum_item *item;
	LIST_HEAD(पंचांगplist);
	अचिन्हित दीर्घ offset;
	पूर्णांक ret;
	माप_प्रकार size;
	u64 csum_end;
	स्थिर u32 csum_size = fs_info->csum_size;

	ASSERT(IS_ALIGNED(start, fs_info->sectorsize) &&
	       IS_ALIGNED(end + 1, fs_info->sectorsize));

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	अगर (search_commit) अणु
		path->skip_locking = 1;
		path->पढ़ोa = READA_FORWARD;
		path->search_commit_root = 1;
	पूर्ण

	key.objectid = BTRFS_EXTENT_CSUM_OBJECTID;
	key.offset = start;
	key.type = BTRFS_EXTENT_CSUM_KEY;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ fail;
	अगर (ret > 0 && path->slots[0] > 0) अणु
		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &key, path->slots[0] - 1);
		अगर (key.objectid == BTRFS_EXTENT_CSUM_OBJECTID &&
		    key.type == BTRFS_EXTENT_CSUM_KEY) अणु
			offset = (start - key.offset) >> fs_info->sectorsize_bits;
			अगर (offset * csum_size <
			    btrfs_item_size_nr(leaf, path->slots[0] - 1))
				path->slots[0]--;
		पूर्ण
	पूर्ण

	जबतक (start <= end) अणु
		leaf = path->nodes[0];
		अगर (path->slots[0] >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ fail;
			अगर (ret > 0)
				अवरोध;
			leaf = path->nodes[0];
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		अगर (key.objectid != BTRFS_EXTENT_CSUM_OBJECTID ||
		    key.type != BTRFS_EXTENT_CSUM_KEY ||
		    key.offset > end)
			अवरोध;

		अगर (key.offset > start)
			start = key.offset;

		size = btrfs_item_size_nr(leaf, path->slots[0]);
		csum_end = key.offset + (size / csum_size) * fs_info->sectorsize;
		अगर (csum_end <= start) अणु
			path->slots[0]++;
			जारी;
		पूर्ण

		csum_end = min(csum_end, end + 1);
		item = btrfs_item_ptr(path->nodes[0], path->slots[0],
				      काष्ठा btrfs_csum_item);
		जबतक (start < csum_end) अणु
			size = min_t(माप_प्रकार, csum_end - start,
				     max_ordered_sum_bytes(fs_info, csum_size));
			sums = kzalloc(btrfs_ordered_sum_size(fs_info, size),
				       GFP_NOFS);
			अगर (!sums) अणु
				ret = -ENOMEM;
				जाओ fail;
			पूर्ण

			sums->bytenr = start;
			sums->len = (पूर्णांक)size;

			offset = (start - key.offset) >> fs_info->sectorsize_bits;
			offset *= csum_size;
			size >>= fs_info->sectorsize_bits;

			पढ़ो_extent_buffer(path->nodes[0],
					   sums->sums,
					   ((अचिन्हित दीर्घ)item) + offset,
					   csum_size * size);

			start += fs_info->sectorsize * size;
			list_add_tail(&sums->list, &पंचांगplist);
		पूर्ण
		path->slots[0]++;
	पूर्ण
	ret = 0;
fail:
	जबतक (ret < 0 && !list_empty(&पंचांगplist)) अणु
		sums = list_entry(पंचांगplist.next, काष्ठा btrfs_ordered_sum, list);
		list_del(&sums->list);
		kमुक्त(sums);
	पूर्ण
	list_splice_tail(&पंचांगplist, list);

	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * btrfs_csum_one_bio - Calculates checksums of the data contained inside a bio
 * @inode:	 Owner of the data inside the bio
 * @bio:	 Contains the data to be checksummed
 * @file_start:  offset in file this bio begins to describe
 * @contig:	 Boolean. If true/1 means all bio vecs in this bio are
 *		 contiguous and they begin at @file_start in the file. False/0
 *		 means this bio can contains potentially discontigous bio vecs
 *		 so the logical offset of each should be calculated separately.
 */
blk_status_t btrfs_csum_one_bio(काष्ठा btrfs_inode *inode, काष्ठा bio *bio,
		       u64 file_start, पूर्णांक contig)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	काष्ठा btrfs_ordered_sum *sums;
	काष्ठा btrfs_ordered_extent *ordered = शून्य;
	अक्षर *data;
	काष्ठा bvec_iter iter;
	काष्ठा bio_vec bvec;
	पूर्णांक index;
	पूर्णांक nr_sectors;
	अचिन्हित दीर्घ total_bytes = 0;
	अचिन्हित दीर्घ this_sum_bytes = 0;
	पूर्णांक i;
	u64 offset;
	अचिन्हित nofs_flag;

	nofs_flag = meदो_स्मृति_nofs_save();
	sums = kvzalloc(btrfs_ordered_sum_size(fs_info, bio->bi_iter.bi_size),
		       GFP_KERNEL);
	meदो_स्मृति_nofs_restore(nofs_flag);

	अगर (!sums)
		वापस BLK_STS_RESOURCE;

	sums->len = bio->bi_iter.bi_size;
	INIT_LIST_HEAD(&sums->list);

	अगर (contig)
		offset = file_start;
	अन्यथा
		offset = 0; /* shut up gcc */

	sums->bytenr = bio->bi_iter.bi_sector << 9;
	index = 0;

	shash->tfm = fs_info->csum_shash;

	bio_क्रम_each_segment(bvec, bio, iter) अणु
		अगर (!contig)
			offset = page_offset(bvec.bv_page) + bvec.bv_offset;

		अगर (!ordered) अणु
			ordered = btrfs_lookup_ordered_extent(inode, offset);
			BUG_ON(!ordered); /* Logic error */
		पूर्ण

		nr_sectors = BTRFS_BYTES_TO_BLKS(fs_info,
						 bvec.bv_len + fs_info->sectorsize
						 - 1);

		क्रम (i = 0; i < nr_sectors; i++) अणु
			अगर (offset >= ordered->file_offset + ordered->num_bytes ||
			    offset < ordered->file_offset) अणु
				अचिन्हित दीर्घ bytes_left;

				sums->len = this_sum_bytes;
				this_sum_bytes = 0;
				btrfs_add_ordered_sum(ordered, sums);
				btrfs_put_ordered_extent(ordered);

				bytes_left = bio->bi_iter.bi_size - total_bytes;

				nofs_flag = meदो_स्मृति_nofs_save();
				sums = kvzalloc(btrfs_ordered_sum_size(fs_info,
						      bytes_left), GFP_KERNEL);
				meदो_स्मृति_nofs_restore(nofs_flag);
				BUG_ON(!sums); /* -ENOMEM */
				sums->len = bytes_left;
				ordered = btrfs_lookup_ordered_extent(inode,
								offset);
				ASSERT(ordered); /* Logic error */
				sums->bytenr = (bio->bi_iter.bi_sector << 9)
					+ total_bytes;
				index = 0;
			पूर्ण

			data = kmap_atomic(bvec.bv_page);
			crypto_shash_digest(shash, data + bvec.bv_offset
					    + (i * fs_info->sectorsize),
					    fs_info->sectorsize,
					    sums->sums + index);
			kunmap_atomic(data);
			index += fs_info->csum_size;
			offset += fs_info->sectorsize;
			this_sum_bytes += fs_info->sectorsize;
			total_bytes += fs_info->sectorsize;
		पूर्ण

	पूर्ण
	this_sum_bytes = 0;
	btrfs_add_ordered_sum(ordered, sums);
	btrfs_put_ordered_extent(ordered);
	वापस 0;
पूर्ण

/*
 * helper function क्रम csum removal, this expects the
 * key to describe the csum poपूर्णांकed to by the path, and it expects
 * the csum to overlap the range [bytenr, len]
 *
 * The csum should not be entirely contained in the range and the
 * range should not be entirely contained in the csum.
 *
 * This calls btrfs_truncate_item with the correct args based on the
 * overlap, and fixes up the key as required.
 */
अटल noअंतरभूत व्योम truncate_one_csum(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा btrfs_path *path,
				       काष्ठा btrfs_key *key,
				       u64 bytenr, u64 len)
अणु
	काष्ठा extent_buffer *leaf;
	स्थिर u32 csum_size = fs_info->csum_size;
	u64 csum_end;
	u64 end_byte = bytenr + len;
	u32 blocksize_bits = fs_info->sectorsize_bits;

	leaf = path->nodes[0];
	csum_end = btrfs_item_size_nr(leaf, path->slots[0]) / csum_size;
	csum_end <<= blocksize_bits;
	csum_end += key->offset;

	अगर (key->offset < bytenr && csum_end <= end_byte) अणु
		/*
		 *         [ bytenr - len ]
		 *         [   ]
		 *   [csum     ]
		 *   A simple truncate off the end of the item
		 */
		u32 new_size = (bytenr - key->offset) >> blocksize_bits;
		new_size *= csum_size;
		btrfs_truncate_item(path, new_size, 1);
	पूर्ण अन्यथा अगर (key->offset >= bytenr && csum_end > end_byte &&
		   end_byte > key->offset) अणु
		/*
		 *         [ bytenr - len ]
		 *                 [ ]
		 *                 [csum     ]
		 * we need to truncate from the beginning of the csum
		 */
		u32 new_size = (csum_end - end_byte) >> blocksize_bits;
		new_size *= csum_size;

		btrfs_truncate_item(path, new_size, 0);

		key->offset = end_byte;
		btrfs_set_item_key_safe(fs_info, path, key);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
पूर्ण

/*
 * deletes the csum items from the csum tree क्रम a given
 * range of bytes.
 */
पूर्णांक btrfs_del_csums(काष्ठा btrfs_trans_handle *trans,
		    काष्ठा btrfs_root *root, u64 bytenr, u64 len)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	u64 end_byte = bytenr + len;
	u64 csum_end;
	काष्ठा extent_buffer *leaf;
	पूर्णांक ret = 0;
	स्थिर u32 csum_size = fs_info->csum_size;
	u32 blocksize_bits = fs_info->sectorsize_bits;

	ASSERT(root == fs_info->csum_root ||
	       root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	जबतक (1) अणु
		key.objectid = BTRFS_EXTENT_CSUM_OBJECTID;
		key.offset = end_byte - 1;
		key.type = BTRFS_EXTENT_CSUM_KEY;

		ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
		अगर (ret > 0) अणु
			ret = 0;
			अगर (path->slots[0] == 0)
				अवरोध;
			path->slots[0]--;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			अवरोध;
		पूर्ण

		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);

		अगर (key.objectid != BTRFS_EXTENT_CSUM_OBJECTID ||
		    key.type != BTRFS_EXTENT_CSUM_KEY) अणु
			अवरोध;
		पूर्ण

		अगर (key.offset >= end_byte)
			अवरोध;

		csum_end = btrfs_item_size_nr(leaf, path->slots[0]) / csum_size;
		csum_end <<= blocksize_bits;
		csum_end += key.offset;

		/* this csum ends beक्रमe we start, we're करोne */
		अगर (csum_end <= bytenr)
			अवरोध;

		/* delete the entire item, it is inside our range */
		अगर (key.offset >= bytenr && csum_end <= end_byte) अणु
			पूर्णांक del_nr = 1;

			/*
			 * Check how many csum items preceding this one in this
			 * leaf correspond to our range and then delete them all
			 * at once.
			 */
			अगर (key.offset > bytenr && path->slots[0] > 0) अणु
				पूर्णांक slot = path->slots[0] - 1;

				जबतक (slot >= 0) अणु
					काष्ठा btrfs_key pk;

					btrfs_item_key_to_cpu(leaf, &pk, slot);
					अगर (pk.offset < bytenr ||
					    pk.type != BTRFS_EXTENT_CSUM_KEY ||
					    pk.objectid !=
					    BTRFS_EXTENT_CSUM_OBJECTID)
						अवरोध;
					path->slots[0] = slot;
					del_nr++;
					key.offset = pk.offset;
					slot--;
				पूर्ण
			पूर्ण
			ret = btrfs_del_items(trans, root, path,
					      path->slots[0], del_nr);
			अगर (ret)
				अवरोध;
			अगर (key.offset == bytenr)
				अवरोध;
		पूर्ण अन्यथा अगर (key.offset < bytenr && csum_end > end_byte) अणु
			अचिन्हित दीर्घ offset;
			अचिन्हित दीर्घ shअगरt_len;
			अचिन्हित दीर्घ item_offset;
			/*
			 *        [ bytenr - len ]
			 *     [csum                ]
			 *
			 * Our bytes are in the middle of the csum,
			 * we need to split this item and insert a new one.
			 *
			 * But we can't drop the path because the
			 * csum could change, get हटाओd, extended etc.
			 *
			 * The trick here is the max size of a csum item leaves
			 * enough room in the tree block क्रम a single
			 * item header.  So, we split the item in place,
			 * adding a new header poपूर्णांकing to the existing
			 * bytes.  Then we loop around again and we have
			 * a nicely क्रमmed csum item that we can neatly
			 * truncate.
			 */
			offset = (bytenr - key.offset) >> blocksize_bits;
			offset *= csum_size;

			shअगरt_len = (len >> blocksize_bits) * csum_size;

			item_offset = btrfs_item_ptr_offset(leaf,
							    path->slots[0]);

			memzero_extent_buffer(leaf, item_offset + offset,
					     shअगरt_len);
			key.offset = bytenr;

			/*
			 * btrfs_split_item वापसs -EAGAIN when the
			 * item changed size or key
			 */
			ret = btrfs_split_item(trans, root, path, &key, offset);
			अगर (ret && ret != -EAGAIN) अणु
				btrfs_पात_transaction(trans, ret);
				अवरोध;
			पूर्ण
			ret = 0;

			key.offset = end_byte - 1;
		पूर्ण अन्यथा अणु
			truncate_one_csum(fs_info, path, &key, bytenr, len);
			अगर (key.offset < bytenr)
				अवरोध;
		पूर्ण
		btrfs_release_path(path);
	पूर्ण
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक find_next_csum_offset(काष्ठा btrfs_root *root,
				 काष्ठा btrfs_path *path,
				 u64 *next_offset)
अणु
	स्थिर u32 nritems = btrfs_header_nritems(path->nodes[0]);
	काष्ठा btrfs_key found_key;
	पूर्णांक slot = path->slots[0] + 1;
	पूर्णांक ret;

	अगर (nritems == 0 || slot >= nritems) अणु
		ret = btrfs_next_leaf(root, path);
		अगर (ret < 0) अणु
			वापस ret;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			*next_offset = (u64)-1;
			वापस 0;
		पूर्ण
		slot = path->slots[0];
	पूर्ण

	btrfs_item_key_to_cpu(path->nodes[0], &found_key, slot);

	अगर (found_key.objectid != BTRFS_EXTENT_CSUM_OBJECTID ||
	    found_key.type != BTRFS_EXTENT_CSUM_KEY)
		*next_offset = (u64)-1;
	अन्यथा
		*next_offset = found_key.offset;

	वापस 0;
पूर्ण

पूर्णांक btrfs_csum_file_blocks(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   काष्ठा btrfs_ordered_sum *sums)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_key file_key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_csum_item *item;
	काष्ठा btrfs_csum_item *item_end;
	काष्ठा extent_buffer *leaf = शून्य;
	u64 next_offset;
	u64 total_bytes = 0;
	u64 csum_offset;
	u64 bytenr;
	u32 ins_size;
	पूर्णांक index = 0;
	पूर्णांक found_next;
	पूर्णांक ret;
	स्थिर u32 csum_size = fs_info->csum_size;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
again:
	next_offset = (u64)-1;
	found_next = 0;
	bytenr = sums->bytenr + total_bytes;
	file_key.objectid = BTRFS_EXTENT_CSUM_OBJECTID;
	file_key.offset = bytenr;
	file_key.type = BTRFS_EXTENT_CSUM_KEY;

	item = btrfs_lookup_csum(trans, root, path, bytenr, 1);
	अगर (!IS_ERR(item)) अणु
		ret = 0;
		leaf = path->nodes[0];
		item_end = btrfs_item_ptr(leaf, path->slots[0],
					  काष्ठा btrfs_csum_item);
		item_end = (काष्ठा btrfs_csum_item *)((अक्षर *)item_end +
			   btrfs_item_size_nr(leaf, path->slots[0]));
		जाओ found;
	पूर्ण
	ret = PTR_ERR(item);
	अगर (ret != -EFBIG && ret != -ENOENT)
		जाओ out;

	अगर (ret == -EFBIG) अणु
		u32 item_size;
		/* we found one, but it isn't big enough yet */
		leaf = path->nodes[0];
		item_size = btrfs_item_size_nr(leaf, path->slots[0]);
		अगर ((item_size / csum_size) >=
		    MAX_CSUM_ITEMS(fs_info, csum_size)) अणु
			/* alपढ़ोy at max size, make a new one */
			जाओ insert;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We didn't find a csum item, insert one. */
		ret = find_next_csum_offset(root, path, &next_offset);
		अगर (ret < 0)
			जाओ out;
		found_next = 1;
		जाओ insert;
	पूर्ण

	/*
	 * At this poपूर्णांक, we know the tree has a checksum item that ends at an
	 * offset matching the start of the checksum range we want to insert.
	 * We try to extend that item as much as possible and then add as many
	 * checksums to it as they fit.
	 *
	 * First check अगर the leaf has enough मुक्त space क्रम at least one
	 * checksum. If it has go directly to the item extension code, otherwise
	 * release the path and करो a search क्रम insertion beक्रमe the extension.
	 */
	अगर (btrfs_leaf_मुक्त_space(leaf) >= csum_size) अणु
		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
		csum_offset = (bytenr - found_key.offset) >>
			fs_info->sectorsize_bits;
		जाओ extend_csum;
	पूर्ण

	btrfs_release_path(path);
	path->search_क्रम_extension = 1;
	ret = btrfs_search_slot(trans, root, &file_key, path,
				csum_size, 1);
	path->search_क्रम_extension = 0;
	अगर (ret < 0)
		जाओ out;

	अगर (ret > 0) अणु
		अगर (path->slots[0] == 0)
			जाओ insert;
		path->slots[0]--;
	पूर्ण

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
	csum_offset = (bytenr - found_key.offset) >> fs_info->sectorsize_bits;

	अगर (found_key.type != BTRFS_EXTENT_CSUM_KEY ||
	    found_key.objectid != BTRFS_EXTENT_CSUM_OBJECTID ||
	    csum_offset >= MAX_CSUM_ITEMS(fs_info, csum_size)) अणु
		जाओ insert;
	पूर्ण

extend_csum:
	अगर (csum_offset == btrfs_item_size_nr(leaf, path->slots[0]) /
	    csum_size) अणु
		पूर्णांक extend_nr;
		u64 पंचांगp;
		u32 dअगरf;

		पंचांगp = sums->len - total_bytes;
		पंचांगp >>= fs_info->sectorsize_bits;
		WARN_ON(पंचांगp < 1);
		extend_nr = max_t(पूर्णांक, 1, पंचांगp);

		/*
		 * A log tree can alपढ़ोy have checksum items with a subset of
		 * the checksums we are trying to log. This can happen after
		 * करोing a sequence of partial ग_लिखोs पूर्णांकo pपुनः_स्मृति extents and
		 * fsyncs in between, with a full fsync logging a larger subrange
		 * of an extent क्रम which a previous fast fsync logged a smaller
		 * subrange. And this happens in particular due to merging file
		 * extent items when we complete an ordered extent क्रम a range
		 * covered by a pपुनः_स्मृति extent - this is करोne at
		 * btrfs_mark_extent_written().
		 *
		 * So अगर we try to extend the previous checksum item, which has
		 * a range that ends at the start of the range we want to insert,
		 * make sure we करोn't extend beyond the start offset of the next
		 * checksum item. If we are at the last item in the leaf, then
		 * क्रमget the optimization of extending and add a new checksum
		 * item - it is not worth the complनिकासy of releasing the path,
		 * getting the first key क्रम the next leaf, repeat the btree
		 * search, etc, because log trees are temporary anyway and it
		 * would only save a few bytes of leaf space.
		 */
		अगर (root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID) अणु
			अगर (path->slots[0] + 1 >=
			    btrfs_header_nritems(path->nodes[0])) अणु
				ret = find_next_csum_offset(root, path, &next_offset);
				अगर (ret < 0)
					जाओ out;
				found_next = 1;
				जाओ insert;
			पूर्ण

			ret = find_next_csum_offset(root, path, &next_offset);
			अगर (ret < 0)
				जाओ out;

			पंचांगp = (next_offset - bytenr) >> fs_info->sectorsize_bits;
			अगर (पंचांगp <= पूर्णांक_उच्च)
				extend_nr = min_t(पूर्णांक, extend_nr, पंचांगp);
		पूर्ण

		dअगरf = (csum_offset + extend_nr) * csum_size;
		dअगरf = min(dअगरf,
			   MAX_CSUM_ITEMS(fs_info, csum_size) * csum_size);

		dअगरf = dअगरf - btrfs_item_size_nr(leaf, path->slots[0]);
		dअगरf = min_t(u32, btrfs_leaf_मुक्त_space(leaf), dअगरf);
		dअगरf /= csum_size;
		dअगरf *= csum_size;

		btrfs_extend_item(path, dअगरf);
		ret = 0;
		जाओ csum;
	पूर्ण

insert:
	btrfs_release_path(path);
	csum_offset = 0;
	अगर (found_next) अणु
		u64 पंचांगp;

		पंचांगp = sums->len - total_bytes;
		पंचांगp >>= fs_info->sectorsize_bits;
		पंचांगp = min(पंचांगp, (next_offset - file_key.offset) >>
					 fs_info->sectorsize_bits);

		पंचांगp = max_t(u64, 1, पंचांगp);
		पंचांगp = min_t(u64, पंचांगp, MAX_CSUM_ITEMS(fs_info, csum_size));
		ins_size = csum_size * पंचांगp;
	पूर्ण अन्यथा अणु
		ins_size = csum_size;
	पूर्ण
	ret = btrfs_insert_empty_item(trans, root, path, &file_key,
				      ins_size);
	अगर (ret < 0)
		जाओ out;
	अगर (WARN_ON(ret != 0))
		जाओ out;
	leaf = path->nodes[0];
csum:
	item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_csum_item);
	item_end = (काष्ठा btrfs_csum_item *)((अचिन्हित अक्षर *)item +
				      btrfs_item_size_nr(leaf, path->slots[0]));
	item = (काष्ठा btrfs_csum_item *)((अचिन्हित अक्षर *)item +
					  csum_offset * csum_size);
found:
	ins_size = (u32)(sums->len - total_bytes) >> fs_info->sectorsize_bits;
	ins_size *= csum_size;
	ins_size = min_t(u32, (अचिन्हित दीर्घ)item_end - (अचिन्हित दीर्घ)item,
			      ins_size);
	ग_लिखो_extent_buffer(leaf, sums->sums + index, (अचिन्हित दीर्घ)item,
			    ins_size);

	index += ins_size;
	ins_size /= csum_size;
	total_bytes += ins_size * fs_info->sectorsize;

	btrfs_mark_buffer_dirty(path->nodes[0]);
	अगर (total_bytes < sums->len) अणु
		btrfs_release_path(path);
		cond_resched();
		जाओ again;
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

व्योम btrfs_extent_item_to_extent_map(काष्ठा btrfs_inode *inode,
				     स्थिर काष्ठा btrfs_path *path,
				     काष्ठा btrfs_file_extent_item *fi,
				     स्थिर bool new_अंतरभूत,
				     काष्ठा extent_map *em)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा extent_buffer *leaf = path->nodes[0];
	स्थिर पूर्णांक slot = path->slots[0];
	काष्ठा btrfs_key key;
	u64 extent_start, extent_end;
	u64 bytenr;
	u8 type = btrfs_file_extent_type(leaf, fi);
	पूर्णांक compress_type = btrfs_file_extent_compression(leaf, fi);

	btrfs_item_key_to_cpu(leaf, &key, slot);
	extent_start = key.offset;
	extent_end = btrfs_file_extent_end(path);
	em->ram_bytes = btrfs_file_extent_ram_bytes(leaf, fi);
	अगर (type == BTRFS_खाता_EXTENT_REG ||
	    type == BTRFS_खाता_EXTENT_PREALLOC) अणु
		em->start = extent_start;
		em->len = extent_end - extent_start;
		em->orig_start = extent_start -
			btrfs_file_extent_offset(leaf, fi);
		em->orig_block_len = btrfs_file_extent_disk_num_bytes(leaf, fi);
		bytenr = btrfs_file_extent_disk_bytenr(leaf, fi);
		अगर (bytenr == 0) अणु
			em->block_start = EXTENT_MAP_HOLE;
			वापस;
		पूर्ण
		अगर (compress_type != BTRFS_COMPRESS_NONE) अणु
			set_bit(EXTENT_FLAG_COMPRESSED, &em->flags);
			em->compress_type = compress_type;
			em->block_start = bytenr;
			em->block_len = em->orig_block_len;
		पूर्ण अन्यथा अणु
			bytenr += btrfs_file_extent_offset(leaf, fi);
			em->block_start = bytenr;
			em->block_len = em->len;
			अगर (type == BTRFS_खाता_EXTENT_PREALLOC)
				set_bit(EXTENT_FLAG_PREALLOC, &em->flags);
		पूर्ण
	पूर्ण अन्यथा अगर (type == BTRFS_खाता_EXTENT_INLINE) अणु
		em->block_start = EXTENT_MAP_INLINE;
		em->start = extent_start;
		em->len = extent_end - extent_start;
		/*
		 * Initialize orig_start and block_len with the same values
		 * as in inode.c:btrfs_get_extent().
		 */
		em->orig_start = EXTENT_MAP_HOLE;
		em->block_len = (u64)-1;
		अगर (!new_अंतरभूत && compress_type != BTRFS_COMPRESS_NONE) अणु
			set_bit(EXTENT_FLAG_COMPRESSED, &em->flags);
			em->compress_type = compress_type;
		पूर्ण
	पूर्ण अन्यथा अणु
		btrfs_err(fs_info,
			  "unknown file extent item type %d, inode %llu, offset %llu, "
			  "root %llu", type, btrfs_ino(inode), extent_start,
			  root->root_key.objectid);
	पूर्ण
पूर्ण

/*
 * Returns the end offset (non inclusive) of the file extent item the given path
 * poपूर्णांकs to. If it poपूर्णांकs to an अंतरभूत extent, the वापसed offset is rounded
 * up to the sector size.
 */
u64 btrfs_file_extent_end(स्थिर काष्ठा btrfs_path *path)
अणु
	स्थिर काष्ठा extent_buffer *leaf = path->nodes[0];
	स्थिर पूर्णांक slot = path->slots[0];
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा btrfs_key key;
	u64 end;

	btrfs_item_key_to_cpu(leaf, &key, slot);
	ASSERT(key.type == BTRFS_EXTENT_DATA_KEY);
	fi = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);

	अगर (btrfs_file_extent_type(leaf, fi) == BTRFS_खाता_EXTENT_INLINE) अणु
		end = btrfs_file_extent_ram_bytes(leaf, fi);
		end = ALIGN(key.offset + end, leaf->fs_info->sectorsize);
	पूर्ण अन्यथा अणु
		end = key.offset + btrfs_file_extent_num_bytes(leaf, fi);
	पूर्ण

	वापस end;
पूर्ण
