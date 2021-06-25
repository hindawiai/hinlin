<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Facebook.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/mm.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "locking.h"
#समावेश "free-space-tree.h"
#समावेश "transaction.h"
#समावेश "block-group.h"

अटल पूर्णांक __add_block_group_मुक्त_space(काष्ठा btrfs_trans_handle *trans,
					काष्ठा btrfs_block_group *block_group,
					काष्ठा btrfs_path *path);

व्योम set_मुक्त_space_tree_thresholds(काष्ठा btrfs_block_group *cache)
अणु
	u32 biपंचांगap_range;
	माप_प्रकार biपंचांगap_size;
	u64 num_biपंचांगaps, total_biपंचांगap_size;

	अगर (WARN_ON(cache->length == 0))
		btrfs_warn(cache->fs_info, "block group %llu length is zero",
			   cache->start);

	/*
	 * We convert to biपंचांगaps when the disk space required क्रम using extents
	 * exceeds that required क्रम using biपंचांगaps.
	 */
	biपंचांगap_range = cache->fs_info->sectorsize * BTRFS_FREE_SPACE_BITMAP_BITS;
	num_biपंचांगaps = भाग_u64(cache->length + biपंचांगap_range - 1, biपंचांगap_range);
	biपंचांगap_size = माप(काष्ठा btrfs_item) + BTRFS_FREE_SPACE_BITMAP_SIZE;
	total_biपंचांगap_size = num_biपंचांगaps * biपंचांगap_size;
	cache->biपंचांगap_high_thresh = भाग_u64(total_biपंचांगap_size,
					    माप(काष्ठा btrfs_item));

	/*
	 * We allow क्रम a small buffer between the high threshold and low
	 * threshold to aव्योम thrashing back and क्रमth between the two क्रमmats.
	 */
	अगर (cache->biपंचांगap_high_thresh > 100)
		cache->biपंचांगap_low_thresh = cache->biपंचांगap_high_thresh - 100;
	अन्यथा
		cache->biपंचांगap_low_thresh = 0;
पूर्ण

अटल पूर्णांक add_new_मुक्त_space_info(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_block_group *block_group,
				   काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_root *root = trans->fs_info->मुक्त_space_root;
	काष्ठा btrfs_मुक्त_space_info *info;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf;
	पूर्णांक ret;

	key.objectid = block_group->start;
	key.type = BTRFS_FREE_SPACE_INFO_KEY;
	key.offset = block_group->length;

	ret = btrfs_insert_empty_item(trans, root, path, &key, माप(*info));
	अगर (ret)
		जाओ out;

	leaf = path->nodes[0];
	info = btrfs_item_ptr(leaf, path->slots[0],
			      काष्ठा btrfs_मुक्त_space_info);
	btrfs_set_मुक्त_space_extent_count(leaf, info, 0);
	btrfs_set_मुक्त_space_flags(leaf, info, 0);
	btrfs_mark_buffer_dirty(leaf);

	ret = 0;
out:
	btrfs_release_path(path);
	वापस ret;
पूर्ण

EXPORT_FOR_TESTS
काष्ठा btrfs_मुक्त_space_info *search_मुक्त_space_info(
		काष्ठा btrfs_trans_handle *trans,
		काष्ठा btrfs_block_group *block_group,
		काष्ठा btrfs_path *path, पूर्णांक cow)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा btrfs_root *root = fs_info->मुक्त_space_root;
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	key.objectid = block_group->start;
	key.type = BTRFS_FREE_SPACE_INFO_KEY;
	key.offset = block_group->length;

	ret = btrfs_search_slot(trans, root, &key, path, 0, cow);
	अगर (ret < 0)
		वापस ERR_PTR(ret);
	अगर (ret != 0) अणु
		btrfs_warn(fs_info, "missing free space info for %llu",
			   block_group->start);
		ASSERT(0);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	वापस btrfs_item_ptr(path->nodes[0], path->slots[0],
			      काष्ठा btrfs_मुक्त_space_info);
पूर्ण

/*
 * btrfs_search_slot() but we're looking क्रम the greatest key less than the
 * passed key.
 */
अटल पूर्णांक btrfs_search_prev_slot(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_root *root,
				  काष्ठा btrfs_key *key, काष्ठा btrfs_path *p,
				  पूर्णांक ins_len, पूर्णांक cow)
अणु
	पूर्णांक ret;

	ret = btrfs_search_slot(trans, root, key, p, ins_len, cow);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0) अणु
		ASSERT(0);
		वापस -EIO;
	पूर्ण

	अगर (p->slots[0] == 0) अणु
		ASSERT(0);
		वापस -EIO;
	पूर्ण
	p->slots[0]--;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 मुक्त_space_biपंचांगap_size(स्थिर काष्ठा btrfs_fs_info *fs_info,
					 u64 size)
अणु
	वापस DIV_ROUND_UP(size >> fs_info->sectorsize_bits, BITS_PER_BYTE);
पूर्ण

अटल अचिन्हित दीर्घ *alloc_biपंचांगap(u32 biपंचांगap_size)
अणु
	अचिन्हित दीर्घ *ret;
	अचिन्हित पूर्णांक nofs_flag;
	u32 biपंचांगap_rounded_size = round_up(biपंचांगap_size, माप(अचिन्हित दीर्घ));

	/*
	 * GFP_NOFS करोesn't work with kvmalloc(), but we really can't recurse
	 * पूर्णांकo the fileप्रणाली as the मुक्त space biपंचांगap can be modअगरied in the
	 * critical section of a transaction commit.
	 *
	 * TODO: push the meदो_स्मृति_nofs_अणुsave,restoreपूर्ण() to the caller where we
	 * know that recursion is unsafe.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	ret = kvzalloc(biपंचांगap_rounded_size, GFP_KERNEL);
	meदो_स्मृति_nofs_restore(nofs_flag);
	वापस ret;
पूर्ण

अटल व्योम le_biपंचांगap_set(अचिन्हित दीर्घ *map, अचिन्हित पूर्णांक start, पूर्णांक len)
अणु
	u8 *p = ((u8 *)map) + BIT_BYTE(start);
	स्थिर अचिन्हित पूर्णांक size = start + len;
	पूर्णांक bits_to_set = BITS_PER_BYTE - (start % BITS_PER_BYTE);
	u8 mask_to_set = BITMAP_FIRST_BYTE_MASK(start);

	जबतक (len - bits_to_set >= 0) अणु
		*p |= mask_to_set;
		len -= bits_to_set;
		bits_to_set = BITS_PER_BYTE;
		mask_to_set = ~0;
		p++;
	पूर्ण
	अगर (len) अणु
		mask_to_set &= BITMAP_LAST_BYTE_MASK(size);
		*p |= mask_to_set;
	पूर्ण
पूर्ण

EXPORT_FOR_TESTS
पूर्णांक convert_मुक्त_space_to_biपंचांगaps(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_block_group *block_group,
				  काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root = fs_info->मुक्त_space_root;
	काष्ठा btrfs_मुक्त_space_info *info;
	काष्ठा btrfs_key key, found_key;
	काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ *biपंचांगap;
	अक्षर *biपंचांगap_cursor;
	u64 start, end;
	u64 biपंचांगap_range, i;
	u32 biपंचांगap_size, flags, expected_extent_count;
	u32 extent_count = 0;
	पूर्णांक करोne = 0, nr;
	पूर्णांक ret;

	biपंचांगap_size = मुक्त_space_biपंचांगap_size(fs_info, block_group->length);
	biपंचांगap = alloc_biपंचांगap(biपंचांगap_size);
	अगर (!biपंचांगap) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	start = block_group->start;
	end = block_group->start + block_group->length;

	key.objectid = end - 1;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	जबतक (!करोne) अणु
		ret = btrfs_search_prev_slot(trans, root, &key, path, -1, 1);
		अगर (ret)
			जाओ out;

		leaf = path->nodes[0];
		nr = 0;
		path->slots[0]++;
		जबतक (path->slots[0] > 0) अणु
			btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0] - 1);

			अगर (found_key.type == BTRFS_FREE_SPACE_INFO_KEY) अणु
				ASSERT(found_key.objectid == block_group->start);
				ASSERT(found_key.offset == block_group->length);
				करोne = 1;
				अवरोध;
			पूर्ण अन्यथा अगर (found_key.type == BTRFS_FREE_SPACE_EXTENT_KEY) अणु
				u64 first, last;

				ASSERT(found_key.objectid >= start);
				ASSERT(found_key.objectid < end);
				ASSERT(found_key.objectid + found_key.offset <= end);

				first = भाग_u64(found_key.objectid - start,
						fs_info->sectorsize);
				last = भाग_u64(found_key.objectid + found_key.offset - start,
					       fs_info->sectorsize);
				le_biपंचांगap_set(biपंचांगap, first, last - first);

				extent_count++;
				nr++;
				path->slots[0]--;
			पूर्ण अन्यथा अणु
				ASSERT(0);
			पूर्ण
		पूर्ण

		ret = btrfs_del_items(trans, root, path, path->slots[0], nr);
		अगर (ret)
			जाओ out;
		btrfs_release_path(path);
	पूर्ण

	info = search_मुक्त_space_info(trans, block_group, path, 1);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ out;
	पूर्ण
	leaf = path->nodes[0];
	flags = btrfs_मुक्त_space_flags(leaf, info);
	flags |= BTRFS_FREE_SPACE_USING_BITMAPS;
	btrfs_set_मुक्त_space_flags(leaf, info, flags);
	expected_extent_count = btrfs_मुक्त_space_extent_count(leaf, info);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	अगर (extent_count != expected_extent_count) अणु
		btrfs_err(fs_info,
			  "incorrect extent count for %llu; counted %u, expected %u",
			  block_group->start, extent_count,
			  expected_extent_count);
		ASSERT(0);
		ret = -EIO;
		जाओ out;
	पूर्ण

	biपंचांगap_cursor = (अक्षर *)biपंचांगap;
	biपंचांगap_range = fs_info->sectorsize * BTRFS_FREE_SPACE_BITMAP_BITS;
	i = start;
	जबतक (i < end) अणु
		अचिन्हित दीर्घ ptr;
		u64 extent_size;
		u32 data_size;

		extent_size = min(end - i, biपंचांगap_range);
		data_size = मुक्त_space_biपंचांगap_size(fs_info, extent_size);

		key.objectid = i;
		key.type = BTRFS_FREE_SPACE_BITMAP_KEY;
		key.offset = extent_size;

		ret = btrfs_insert_empty_item(trans, root, path, &key,
					      data_size);
		अगर (ret)
			जाओ out;

		leaf = path->nodes[0];
		ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
		ग_लिखो_extent_buffer(leaf, biपंचांगap_cursor, ptr,
				    data_size);
		btrfs_mark_buffer_dirty(leaf);
		btrfs_release_path(path);

		i += extent_size;
		biपंचांगap_cursor += data_size;
	पूर्ण

	ret = 0;
out:
	kvमुक्त(biपंचांगap);
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
	वापस ret;
पूर्ण

EXPORT_FOR_TESTS
पूर्णांक convert_मुक्त_space_to_extents(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_block_group *block_group,
				  काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root = fs_info->मुक्त_space_root;
	काष्ठा btrfs_मुक्त_space_info *info;
	काष्ठा btrfs_key key, found_key;
	काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ *biपंचांगap;
	u64 start, end;
	u32 biपंचांगap_size, flags, expected_extent_count;
	अचिन्हित दीर्घ nrbits, start_bit, end_bit;
	u32 extent_count = 0;
	पूर्णांक करोne = 0, nr;
	पूर्णांक ret;

	biपंचांगap_size = मुक्त_space_biपंचांगap_size(fs_info, block_group->length);
	biपंचांगap = alloc_biपंचांगap(biपंचांगap_size);
	अगर (!biपंचांगap) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	start = block_group->start;
	end = block_group->start + block_group->length;

	key.objectid = end - 1;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	जबतक (!करोne) अणु
		ret = btrfs_search_prev_slot(trans, root, &key, path, -1, 1);
		अगर (ret)
			जाओ out;

		leaf = path->nodes[0];
		nr = 0;
		path->slots[0]++;
		जबतक (path->slots[0] > 0) अणु
			btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0] - 1);

			अगर (found_key.type == BTRFS_FREE_SPACE_INFO_KEY) अणु
				ASSERT(found_key.objectid == block_group->start);
				ASSERT(found_key.offset == block_group->length);
				करोne = 1;
				अवरोध;
			पूर्ण अन्यथा अगर (found_key.type == BTRFS_FREE_SPACE_BITMAP_KEY) अणु
				अचिन्हित दीर्घ ptr;
				अक्षर *biपंचांगap_cursor;
				u32 biपंचांगap_pos, data_size;

				ASSERT(found_key.objectid >= start);
				ASSERT(found_key.objectid < end);
				ASSERT(found_key.objectid + found_key.offset <= end);

				biपंचांगap_pos = भाग_u64(found_key.objectid - start,
						     fs_info->sectorsize *
						     BITS_PER_BYTE);
				biपंचांगap_cursor = ((अक्षर *)biपंचांगap) + biपंचांगap_pos;
				data_size = मुक्त_space_biपंचांगap_size(fs_info,
								found_key.offset);

				ptr = btrfs_item_ptr_offset(leaf, path->slots[0] - 1);
				पढ़ो_extent_buffer(leaf, biपंचांगap_cursor, ptr,
						   data_size);

				nr++;
				path->slots[0]--;
			पूर्ण अन्यथा अणु
				ASSERT(0);
			पूर्ण
		पूर्ण

		ret = btrfs_del_items(trans, root, path, path->slots[0], nr);
		अगर (ret)
			जाओ out;
		btrfs_release_path(path);
	पूर्ण

	info = search_मुक्त_space_info(trans, block_group, path, 1);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ out;
	पूर्ण
	leaf = path->nodes[0];
	flags = btrfs_मुक्त_space_flags(leaf, info);
	flags &= ~BTRFS_FREE_SPACE_USING_BITMAPS;
	btrfs_set_मुक्त_space_flags(leaf, info, flags);
	expected_extent_count = btrfs_मुक्त_space_extent_count(leaf, info);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	nrbits = block_group->length >> block_group->fs_info->sectorsize_bits;
	start_bit = find_next_bit_le(biपंचांगap, nrbits, 0);

	जबतक (start_bit < nrbits) अणु
		end_bit = find_next_zero_bit_le(biपंचांगap, nrbits, start_bit);
		ASSERT(start_bit < end_bit);

		key.objectid = start + start_bit * block_group->fs_info->sectorsize;
		key.type = BTRFS_FREE_SPACE_EXTENT_KEY;
		key.offset = (end_bit - start_bit) * block_group->fs_info->sectorsize;

		ret = btrfs_insert_empty_item(trans, root, path, &key, 0);
		अगर (ret)
			जाओ out;
		btrfs_release_path(path);

		extent_count++;

		start_bit = find_next_bit_le(biपंचांगap, nrbits, end_bit);
	पूर्ण

	अगर (extent_count != expected_extent_count) अणु
		btrfs_err(fs_info,
			  "incorrect extent count for %llu; counted %u, expected %u",
			  block_group->start, extent_count,
			  expected_extent_count);
		ASSERT(0);
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = 0;
out:
	kvमुक्त(biपंचांगap);
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक update_मुक्त_space_extent_count(काष्ठा btrfs_trans_handle *trans,
					  काष्ठा btrfs_block_group *block_group,
					  काष्ठा btrfs_path *path,
					  पूर्णांक new_extents)
अणु
	काष्ठा btrfs_मुक्त_space_info *info;
	u32 flags;
	u32 extent_count;
	पूर्णांक ret = 0;

	अगर (new_extents == 0)
		वापस 0;

	info = search_मुक्त_space_info(trans, block_group, path, 1);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ out;
	पूर्ण
	flags = btrfs_मुक्त_space_flags(path->nodes[0], info);
	extent_count = btrfs_मुक्त_space_extent_count(path->nodes[0], info);

	extent_count += new_extents;
	btrfs_set_मुक्त_space_extent_count(path->nodes[0], info, extent_count);
	btrfs_mark_buffer_dirty(path->nodes[0]);
	btrfs_release_path(path);

	अगर (!(flags & BTRFS_FREE_SPACE_USING_BITMAPS) &&
	    extent_count > block_group->biपंचांगap_high_thresh) अणु
		ret = convert_मुक्त_space_to_biपंचांगaps(trans, block_group, path);
	पूर्ण अन्यथा अगर ((flags & BTRFS_FREE_SPACE_USING_BITMAPS) &&
		   extent_count < block_group->biपंचांगap_low_thresh) अणु
		ret = convert_मुक्त_space_to_extents(trans, block_group, path);
	पूर्ण

out:
	वापस ret;
पूर्ण

EXPORT_FOR_TESTS
पूर्णांक मुक्त_space_test_bit(काष्ठा btrfs_block_group *block_group,
			काष्ठा btrfs_path *path, u64 offset)
अणु
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	u64 found_start, found_end;
	अचिन्हित दीर्घ ptr, i;

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
	ASSERT(key.type == BTRFS_FREE_SPACE_BITMAP_KEY);

	found_start = key.objectid;
	found_end = key.objectid + key.offset;
	ASSERT(offset >= found_start && offset < found_end);

	ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
	i = भाग_u64(offset - found_start,
		    block_group->fs_info->sectorsize);
	वापस !!extent_buffer_test_bit(leaf, ptr, i);
पूर्ण

अटल व्योम मुक्त_space_set_bits(काष्ठा btrfs_block_group *block_group,
				काष्ठा btrfs_path *path, u64 *start, u64 *size,
				पूर्णांक bit)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	u64 end = *start + *size;
	u64 found_start, found_end;
	अचिन्हित दीर्घ ptr, first, last;

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
	ASSERT(key.type == BTRFS_FREE_SPACE_BITMAP_KEY);

	found_start = key.objectid;
	found_end = key.objectid + key.offset;
	ASSERT(*start >= found_start && *start < found_end);
	ASSERT(end > found_start);

	अगर (end > found_end)
		end = found_end;

	ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
	first = (*start - found_start) >> fs_info->sectorsize_bits;
	last = (end - found_start) >> fs_info->sectorsize_bits;
	अगर (bit)
		extent_buffer_biपंचांगap_set(leaf, ptr, first, last - first);
	अन्यथा
		extent_buffer_biपंचांगap_clear(leaf, ptr, first, last - first);
	btrfs_mark_buffer_dirty(leaf);

	*size -= end - *start;
	*start = end;
पूर्ण

/*
 * We can't use btrfs_next_item() in modअगरy_मुक्त_space_biपंचांगap() because
 * btrfs_next_leaf() करोesn't get the path क्रम writing. We can क्रमgo the fancy
 * tree walking in btrfs_next_leaf() anyways because we know exactly what we're
 * looking क्रम.
 */
अटल पूर्णांक मुक्त_space_next_biपंचांगap(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_root *root, काष्ठा btrfs_path *p)
अणु
	काष्ठा btrfs_key key;

	अगर (p->slots[0] + 1 < btrfs_header_nritems(p->nodes[0])) अणु
		p->slots[0]++;
		वापस 0;
	पूर्ण

	btrfs_item_key_to_cpu(p->nodes[0], &key, p->slots[0]);
	btrfs_release_path(p);

	key.objectid += key.offset;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	वापस btrfs_search_prev_slot(trans, root, &key, p, 0, 1);
पूर्ण

/*
 * If हटाओ is 1, then we are removing मुक्त space, thus clearing bits in the
 * biपंचांगap. If हटाओ is 0, then we are adding मुक्त space, thus setting bits in
 * the biपंचांगap.
 */
अटल पूर्णांक modअगरy_मुक्त_space_biपंचांगap(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_block_group *block_group,
				    काष्ठा btrfs_path *path,
				    u64 start, u64 size, पूर्णांक हटाओ)
अणु
	काष्ठा btrfs_root *root = block_group->fs_info->मुक्त_space_root;
	काष्ठा btrfs_key key;
	u64 end = start + size;
	u64 cur_start, cur_size;
	पूर्णांक prev_bit, next_bit;
	पूर्णांक new_extents;
	पूर्णांक ret;

	/*
	 * Read the bit क्रम the block immediately beक्रमe the extent of space अगर
	 * that block is within the block group.
	 */
	अगर (start > block_group->start) अणु
		u64 prev_block = start - block_group->fs_info->sectorsize;

		key.objectid = prev_block;
		key.type = (u8)-1;
		key.offset = (u64)-1;

		ret = btrfs_search_prev_slot(trans, root, &key, path, 0, 1);
		अगर (ret)
			जाओ out;

		prev_bit = मुक्त_space_test_bit(block_group, path, prev_block);

		/* The previous block may have been in the previous biपंचांगap. */
		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
		अगर (start >= key.objectid + key.offset) अणु
			ret = मुक्त_space_next_biपंचांगap(trans, root, path);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		key.objectid = start;
		key.type = (u8)-1;
		key.offset = (u64)-1;

		ret = btrfs_search_prev_slot(trans, root, &key, path, 0, 1);
		अगर (ret)
			जाओ out;

		prev_bit = -1;
	पूर्ण

	/*
	 * Iterate over all of the biपंचांगaps overlapped by the extent of space,
	 * clearing/setting bits as required.
	 */
	cur_start = start;
	cur_size = size;
	जबतक (1) अणु
		मुक्त_space_set_bits(block_group, path, &cur_start, &cur_size,
				    !हटाओ);
		अगर (cur_size == 0)
			अवरोध;
		ret = मुक्त_space_next_biपंचांगap(trans, root, path);
		अगर (ret)
			जाओ out;
	पूर्ण

	/*
	 * Read the bit क्रम the block immediately after the extent of space अगर
	 * that block is within the block group.
	 */
	अगर (end < block_group->start + block_group->length) अणु
		/* The next block may be in the next biपंचांगap. */
		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
		अगर (end >= key.objectid + key.offset) अणु
			ret = मुक्त_space_next_biपंचांगap(trans, root, path);
			अगर (ret)
				जाओ out;
		पूर्ण

		next_bit = मुक्त_space_test_bit(block_group, path, end);
	पूर्ण अन्यथा अणु
		next_bit = -1;
	पूर्ण

	अगर (हटाओ) अणु
		new_extents = -1;
		अगर (prev_bit == 1) अणु
			/* Leftover on the left. */
			new_extents++;
		पूर्ण
		अगर (next_bit == 1) अणु
			/* Leftover on the right. */
			new_extents++;
		पूर्ण
	पूर्ण अन्यथा अणु
		new_extents = 1;
		अगर (prev_bit == 1) अणु
			/* Merging with neighbor on the left. */
			new_extents--;
		पूर्ण
		अगर (next_bit == 1) अणु
			/* Merging with neighbor on the right. */
			new_extents--;
		पूर्ण
	पूर्ण

	btrfs_release_path(path);
	ret = update_मुक्त_space_extent_count(trans, block_group, path,
					     new_extents);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक हटाओ_मुक्त_space_extent(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_block_group *block_group,
				    काष्ठा btrfs_path *path,
				    u64 start, u64 size)
अणु
	काष्ठा btrfs_root *root = trans->fs_info->मुक्त_space_root;
	काष्ठा btrfs_key key;
	u64 found_start, found_end;
	u64 end = start + size;
	पूर्णांक new_extents = -1;
	पूर्णांक ret;

	key.objectid = start;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	ret = btrfs_search_prev_slot(trans, root, &key, path, -1, 1);
	अगर (ret)
		जाओ out;

	btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);

	ASSERT(key.type == BTRFS_FREE_SPACE_EXTENT_KEY);

	found_start = key.objectid;
	found_end = key.objectid + key.offset;
	ASSERT(start >= found_start && end <= found_end);

	/*
	 * Okay, now that we've found the मुक्त space extent which contains the
	 * मुक्त space that we are removing, there are four हालs:
	 *
	 * 1. We're using the whole extent: delete the key we found and
	 * decrement the मुक्त space extent count.
	 * 2. We are using part of the extent starting at the beginning: delete
	 * the key we found and insert a new key representing the leftover at
	 * the end. There is no net change in the number of extents.
	 * 3. We are using part of the extent ending at the end: delete the key
	 * we found and insert a new key representing the leftover at the
	 * beginning. There is no net change in the number of extents.
	 * 4. We are using part of the extent in the middle: delete the key we
	 * found and insert two new keys representing the leftovers on each
	 * side. Where we used to have one extent, we now have two, so increment
	 * the extent count. We may need to convert the block group to biपंचांगaps
	 * as a result.
	 */

	/* Delete the existing key (हालs 1-4). */
	ret = btrfs_del_item(trans, root, path);
	अगर (ret)
		जाओ out;

	/* Add a key क्रम leftovers at the beginning (हालs 3 and 4). */
	अगर (start > found_start) अणु
		key.objectid = found_start;
		key.type = BTRFS_FREE_SPACE_EXTENT_KEY;
		key.offset = start - found_start;

		btrfs_release_path(path);
		ret = btrfs_insert_empty_item(trans, root, path, &key, 0);
		अगर (ret)
			जाओ out;
		new_extents++;
	पूर्ण

	/* Add a key क्रम leftovers at the end (हालs 2 and 4). */
	अगर (end < found_end) अणु
		key.objectid = end;
		key.type = BTRFS_FREE_SPACE_EXTENT_KEY;
		key.offset = found_end - end;

		btrfs_release_path(path);
		ret = btrfs_insert_empty_item(trans, root, path, &key, 0);
		अगर (ret)
			जाओ out;
		new_extents++;
	पूर्ण

	btrfs_release_path(path);
	ret = update_मुक्त_space_extent_count(trans, block_group, path,
					     new_extents);

out:
	वापस ret;
पूर्ण

EXPORT_FOR_TESTS
पूर्णांक __हटाओ_from_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_block_group *block_group,
				  काष्ठा btrfs_path *path, u64 start, u64 size)
अणु
	काष्ठा btrfs_मुक्त_space_info *info;
	u32 flags;
	पूर्णांक ret;

	अगर (block_group->needs_मुक्त_space) अणु
		ret = __add_block_group_मुक्त_space(trans, block_group, path);
		अगर (ret)
			वापस ret;
	पूर्ण

	info = search_मुक्त_space_info(शून्य, block_group, path, 0);
	अगर (IS_ERR(info))
		वापस PTR_ERR(info);
	flags = btrfs_मुक्त_space_flags(path->nodes[0], info);
	btrfs_release_path(path);

	अगर (flags & BTRFS_FREE_SPACE_USING_BITMAPS) अणु
		वापस modअगरy_मुक्त_space_biपंचांगap(trans, block_group, path,
						start, size, 1);
	पूर्ण अन्यथा अणु
		वापस हटाओ_मुक्त_space_extent(trans, block_group, path,
						start, size);
	पूर्ण
पूर्ण

पूर्णांक हटाओ_from_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
				u64 start, u64 size)
अणु
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_path *path;
	पूर्णांक ret;

	अगर (!btrfs_fs_compat_ro(trans->fs_info, FREE_SPACE_TREE))
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	block_group = btrfs_lookup_block_group(trans->fs_info, start);
	अगर (!block_group) अणु
		ASSERT(0);
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	mutex_lock(&block_group->मुक्त_space_lock);
	ret = __हटाओ_from_मुक्त_space_tree(trans, block_group, path, start,
					    size);
	mutex_unlock(&block_group->मुक्त_space_lock);

	btrfs_put_block_group(block_group);
out:
	btrfs_मुक्त_path(path);
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक add_मुक्त_space_extent(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_block_group *block_group,
				 काष्ठा btrfs_path *path,
				 u64 start, u64 size)
अणु
	काष्ठा btrfs_root *root = trans->fs_info->मुक्त_space_root;
	काष्ठा btrfs_key key, new_key;
	u64 found_start, found_end;
	u64 end = start + size;
	पूर्णांक new_extents = 1;
	पूर्णांक ret;

	/*
	 * We are adding a new extent of मुक्त space, but we need to merge
	 * extents. There are four हालs here:
	 *
	 * 1. The new extent करोes not have any immediate neighbors to merge
	 * with: add the new key and increment the मुक्त space extent count. We
	 * may need to convert the block group to biपंचांगaps as a result.
	 * 2. The new extent has an immediate neighbor beक्रमe it: हटाओ the
	 * previous key and insert a new key combining both of them. There is no
	 * net change in the number of extents.
	 * 3. The new extent has an immediate neighbor after it: हटाओ the next
	 * key and insert a new key combining both of them. There is no net
	 * change in the number of extents.
	 * 4. The new extent has immediate neighbors on both sides: हटाओ both
	 * of the keys and insert a new key combining all of them. Where we used
	 * to have two extents, we now have one, so decrement the extent count.
	 */

	new_key.objectid = start;
	new_key.type = BTRFS_FREE_SPACE_EXTENT_KEY;
	new_key.offset = size;

	/* Search क्रम a neighbor on the left. */
	अगर (start == block_group->start)
		जाओ right;
	key.objectid = start - 1;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	ret = btrfs_search_prev_slot(trans, root, &key, path, -1, 1);
	अगर (ret)
		जाओ out;

	btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);

	अगर (key.type != BTRFS_FREE_SPACE_EXTENT_KEY) अणु
		ASSERT(key.type == BTRFS_FREE_SPACE_INFO_KEY);
		btrfs_release_path(path);
		जाओ right;
	पूर्ण

	found_start = key.objectid;
	found_end = key.objectid + key.offset;
	ASSERT(found_start >= block_group->start &&
	       found_end > block_group->start);
	ASSERT(found_start < start && found_end <= start);

	/*
	 * Delete the neighbor on the left and असलorb it पूर्णांकo the new key (हालs
	 * 2 and 4).
	 */
	अगर (found_end == start) अणु
		ret = btrfs_del_item(trans, root, path);
		अगर (ret)
			जाओ out;
		new_key.objectid = found_start;
		new_key.offset += key.offset;
		new_extents--;
	पूर्ण
	btrfs_release_path(path);

right:
	/* Search क्रम a neighbor on the right. */
	अगर (end == block_group->start + block_group->length)
		जाओ insert;
	key.objectid = end;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	ret = btrfs_search_prev_slot(trans, root, &key, path, -1, 1);
	अगर (ret)
		जाओ out;

	btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);

	अगर (key.type != BTRFS_FREE_SPACE_EXTENT_KEY) अणु
		ASSERT(key.type == BTRFS_FREE_SPACE_INFO_KEY);
		btrfs_release_path(path);
		जाओ insert;
	पूर्ण

	found_start = key.objectid;
	found_end = key.objectid + key.offset;
	ASSERT(found_start >= block_group->start &&
	       found_end > block_group->start);
	ASSERT((found_start < start && found_end <= start) ||
	       (found_start >= end && found_end > end));

	/*
	 * Delete the neighbor on the right and असलorb it पूर्णांकo the new key
	 * (हालs 3 and 4).
	 */
	अगर (found_start == end) अणु
		ret = btrfs_del_item(trans, root, path);
		अगर (ret)
			जाओ out;
		new_key.offset += key.offset;
		new_extents--;
	पूर्ण
	btrfs_release_path(path);

insert:
	/* Insert the new key (हालs 1-4). */
	ret = btrfs_insert_empty_item(trans, root, path, &new_key, 0);
	अगर (ret)
		जाओ out;

	btrfs_release_path(path);
	ret = update_मुक्त_space_extent_count(trans, block_group, path,
					     new_extents);

out:
	वापस ret;
पूर्ण

EXPORT_FOR_TESTS
पूर्णांक __add_to_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_block_group *block_group,
			     काष्ठा btrfs_path *path, u64 start, u64 size)
अणु
	काष्ठा btrfs_मुक्त_space_info *info;
	u32 flags;
	पूर्णांक ret;

	अगर (block_group->needs_मुक्त_space) अणु
		ret = __add_block_group_मुक्त_space(trans, block_group, path);
		अगर (ret)
			वापस ret;
	पूर्ण

	info = search_मुक्त_space_info(शून्य, block_group, path, 0);
	अगर (IS_ERR(info))
		वापस PTR_ERR(info);
	flags = btrfs_मुक्त_space_flags(path->nodes[0], info);
	btrfs_release_path(path);

	अगर (flags & BTRFS_FREE_SPACE_USING_BITMAPS) अणु
		वापस modअगरy_मुक्त_space_biपंचांगap(trans, block_group, path,
						start, size, 0);
	पूर्ण अन्यथा अणु
		वापस add_मुक्त_space_extent(trans, block_group, path, start,
					     size);
	पूर्ण
पूर्ण

पूर्णांक add_to_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
			   u64 start, u64 size)
अणु
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_path *path;
	पूर्णांक ret;

	अगर (!btrfs_fs_compat_ro(trans->fs_info, FREE_SPACE_TREE))
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	block_group = btrfs_lookup_block_group(trans->fs_info, start);
	अगर (!block_group) अणु
		ASSERT(0);
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	mutex_lock(&block_group->मुक्त_space_lock);
	ret = __add_to_मुक्त_space_tree(trans, block_group, path, start, size);
	mutex_unlock(&block_group->मुक्त_space_lock);

	btrfs_put_block_group(block_group);
out:
	btrfs_मुक्त_path(path);
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
	वापस ret;
पूर्ण

/*
 * Populate the मुक्त space tree by walking the extent tree. Operations on the
 * extent tree that happen as a result of ग_लिखोs to the मुक्त space tree will go
 * through the normal add/हटाओ hooks.
 */
अटल पूर्णांक populate_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_root *extent_root = trans->fs_info->extent_root;
	काष्ठा btrfs_path *path, *path2;
	काष्ठा btrfs_key key;
	u64 start, end;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	path->पढ़ोa = READA_FORWARD;

	path2 = btrfs_alloc_path();
	अगर (!path2) अणु
		btrfs_मुक्त_path(path);
		वापस -ENOMEM;
	पूर्ण

	ret = add_new_मुक्त_space_info(trans, block_group, path2);
	अगर (ret)
		जाओ out;

	mutex_lock(&block_group->मुक्त_space_lock);

	/*
	 * Iterate through all of the extent and metadata items in this block
	 * group, adding the मुक्त space between them and the मुक्त space at the
	 * end. Note that EXTENT_ITEM and METADATA_ITEM are less than
	 * BLOCK_GROUP_ITEM, so an extent may precede the block group that it's
	 * contained in.
	 */
	key.objectid = block_group->start;
	key.type = BTRFS_EXTENT_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_search_slot_क्रम_पढ़ो(extent_root, &key, path, 1, 0);
	अगर (ret < 0)
		जाओ out_locked;
	ASSERT(ret == 0);

	start = block_group->start;
	end = block_group->start + block_group->length;
	जबतक (1) अणु
		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);

		अगर (key.type == BTRFS_EXTENT_ITEM_KEY ||
		    key.type == BTRFS_METADATA_ITEM_KEY) अणु
			अगर (key.objectid >= end)
				अवरोध;

			अगर (start < key.objectid) अणु
				ret = __add_to_मुक्त_space_tree(trans,
							       block_group,
							       path2, start,
							       key.objectid -
							       start);
				अगर (ret)
					जाओ out_locked;
			पूर्ण
			start = key.objectid;
			अगर (key.type == BTRFS_METADATA_ITEM_KEY)
				start += trans->fs_info->nodesize;
			अन्यथा
				start += key.offset;
		पूर्ण अन्यथा अगर (key.type == BTRFS_BLOCK_GROUP_ITEM_KEY) अणु
			अगर (key.objectid != block_group->start)
				अवरोध;
		पूर्ण

		ret = btrfs_next_item(extent_root, path);
		अगर (ret < 0)
			जाओ out_locked;
		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (start < end) अणु
		ret = __add_to_मुक्त_space_tree(trans, block_group, path2,
					       start, end - start);
		अगर (ret)
			जाओ out_locked;
	पूर्ण

	ret = 0;
out_locked:
	mutex_unlock(&block_group->मुक्त_space_lock);
out:
	btrfs_मुक्त_path(path2);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_create_मुक्त_space_tree(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	काष्ठा btrfs_root *मुक्त_space_root;
	काष्ठा btrfs_block_group *block_group;
	काष्ठा rb_node *node;
	पूर्णांक ret;

	trans = btrfs_start_transaction(tree_root, 0);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	set_bit(BTRFS_FS_CREATING_FREE_SPACE_TREE, &fs_info->flags);
	set_bit(BTRFS_FS_FREE_SPACE_TREE_UNTRUSTED, &fs_info->flags);
	मुक्त_space_root = btrfs_create_tree(trans,
					    BTRFS_FREE_SPACE_TREE_OBJECTID);
	अगर (IS_ERR(मुक्त_space_root)) अणु
		ret = PTR_ERR(मुक्त_space_root);
		जाओ पात;
	पूर्ण
	fs_info->मुक्त_space_root = मुक्त_space_root;

	node = rb_first(&fs_info->block_group_cache_tree);
	जबतक (node) अणु
		block_group = rb_entry(node, काष्ठा btrfs_block_group,
				       cache_node);
		ret = populate_मुक्त_space_tree(trans, block_group);
		अगर (ret)
			जाओ पात;
		node = rb_next(node);
	पूर्ण

	btrfs_set_fs_compat_ro(fs_info, FREE_SPACE_TREE);
	btrfs_set_fs_compat_ro(fs_info, FREE_SPACE_TREE_VALID);
	clear_bit(BTRFS_FS_CREATING_FREE_SPACE_TREE, &fs_info->flags);
	ret = btrfs_commit_transaction(trans);

	/*
	 * Now that we've committed the transaction any पढ़ोing of our commit
	 * root will be safe, so we can cache from the मुक्त space tree now.
	 */
	clear_bit(BTRFS_FS_FREE_SPACE_TREE_UNTRUSTED, &fs_info->flags);
	वापस ret;

पात:
	clear_bit(BTRFS_FS_CREATING_FREE_SPACE_TREE, &fs_info->flags);
	clear_bit(BTRFS_FS_FREE_SPACE_TREE_UNTRUSTED, &fs_info->flags);
	btrfs_पात_transaction(trans, ret);
	btrfs_end_transaction(trans);
	वापस ret;
पूर्ण

अटल पूर्णांक clear_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	पूर्णांक nr;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = 0;
	key.type = 0;
	key.offset = 0;

	जबतक (1) अणु
		ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
		अगर (ret < 0)
			जाओ out;

		nr = btrfs_header_nritems(path->nodes[0]);
		अगर (!nr)
			अवरोध;

		path->slots[0] = 0;
		ret = btrfs_del_items(trans, root, path, 0, nr);
		अगर (ret)
			जाओ out;

		btrfs_release_path(path);
	पूर्ण

	ret = 0;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_clear_मुक्त_space_tree(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	काष्ठा btrfs_root *मुक्त_space_root = fs_info->मुक्त_space_root;
	पूर्णांक ret;

	trans = btrfs_start_transaction(tree_root, 0);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	btrfs_clear_fs_compat_ro(fs_info, FREE_SPACE_TREE);
	btrfs_clear_fs_compat_ro(fs_info, FREE_SPACE_TREE_VALID);
	fs_info->मुक्त_space_root = शून्य;

	ret = clear_मुक्त_space_tree(trans, मुक्त_space_root);
	अगर (ret)
		जाओ पात;

	ret = btrfs_del_root(trans, &मुक्त_space_root->root_key);
	अगर (ret)
		जाओ पात;

	list_del(&मुक्त_space_root->dirty_list);

	btrfs_tree_lock(मुक्त_space_root->node);
	btrfs_clean_tree_block(मुक्त_space_root->node);
	btrfs_tree_unlock(मुक्त_space_root->node);
	btrfs_मुक्त_tree_block(trans, मुक्त_space_root, मुक्त_space_root->node,
			      0, 1);

	btrfs_put_root(मुक्त_space_root);

	वापस btrfs_commit_transaction(trans);

पात:
	btrfs_पात_transaction(trans, ret);
	btrfs_end_transaction(trans);
	वापस ret;
पूर्ण

अटल पूर्णांक __add_block_group_मुक्त_space(काष्ठा btrfs_trans_handle *trans,
					काष्ठा btrfs_block_group *block_group,
					काष्ठा btrfs_path *path)
अणु
	पूर्णांक ret;

	block_group->needs_मुक्त_space = 0;

	ret = add_new_मुक्त_space_info(trans, block_group, path);
	अगर (ret)
		वापस ret;

	वापस __add_to_मुक्त_space_tree(trans, block_group, path,
					block_group->start,
					block_group->length);
पूर्ण

पूर्णांक add_block_group_मुक्त_space(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_path *path = शून्य;
	पूर्णांक ret = 0;

	अगर (!btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE))
		वापस 0;

	mutex_lock(&block_group->मुक्त_space_lock);
	अगर (!block_group->needs_मुक्त_space)
		जाओ out;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = __add_block_group_मुक्त_space(trans, block_group, path);

out:
	btrfs_मुक्त_path(path);
	mutex_unlock(&block_group->मुक्त_space_lock);
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
	वापस ret;
पूर्ण

पूर्णांक हटाओ_block_group_मुक्त_space(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_root *root = trans->fs_info->मुक्त_space_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key, found_key;
	काष्ठा extent_buffer *leaf;
	u64 start, end;
	पूर्णांक करोne = 0, nr;
	पूर्णांक ret;

	अगर (!btrfs_fs_compat_ro(trans->fs_info, FREE_SPACE_TREE))
		वापस 0;

	अगर (block_group->needs_मुक्त_space) अणु
		/* We never added this block group to the मुक्त space tree. */
		वापस 0;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	start = block_group->start;
	end = block_group->start + block_group->length;

	key.objectid = end - 1;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	जबतक (!करोne) अणु
		ret = btrfs_search_prev_slot(trans, root, &key, path, -1, 1);
		अगर (ret)
			जाओ out;

		leaf = path->nodes[0];
		nr = 0;
		path->slots[0]++;
		जबतक (path->slots[0] > 0) अणु
			btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0] - 1);

			अगर (found_key.type == BTRFS_FREE_SPACE_INFO_KEY) अणु
				ASSERT(found_key.objectid == block_group->start);
				ASSERT(found_key.offset == block_group->length);
				करोne = 1;
				nr++;
				path->slots[0]--;
				अवरोध;
			पूर्ण अन्यथा अगर (found_key.type == BTRFS_FREE_SPACE_EXTENT_KEY ||
				   found_key.type == BTRFS_FREE_SPACE_BITMAP_KEY) अणु
				ASSERT(found_key.objectid >= start);
				ASSERT(found_key.objectid < end);
				ASSERT(found_key.objectid + found_key.offset <= end);
				nr++;
				path->slots[0]--;
			पूर्ण अन्यथा अणु
				ASSERT(0);
			पूर्ण
		पूर्ण

		ret = btrfs_del_items(trans, root, path, path->slots[0], nr);
		अगर (ret)
			जाओ out;
		btrfs_release_path(path);
	पूर्ण

	ret = 0;
out:
	btrfs_मुक्त_path(path);
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक load_मुक्त_space_biपंचांगaps(काष्ठा btrfs_caching_control *caching_ctl,
				   काष्ठा btrfs_path *path,
				   u32 expected_extent_count)
अणु
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_key key;
	पूर्णांक prev_bit = 0, bit;
	/* Initialize to silence GCC. */
	u64 extent_start = 0;
	u64 end, offset;
	u64 total_found = 0;
	u32 extent_count = 0;
	पूर्णांक ret;

	block_group = caching_ctl->block_group;
	fs_info = block_group->fs_info;
	root = fs_info->मुक्त_space_root;

	end = block_group->start + block_group->length;

	जबतक (1) अणु
		ret = btrfs_next_item(root, path);
		अगर (ret < 0)
			जाओ out;
		अगर (ret)
			अवरोध;

		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);

		अगर (key.type == BTRFS_FREE_SPACE_INFO_KEY)
			अवरोध;

		ASSERT(key.type == BTRFS_FREE_SPACE_BITMAP_KEY);
		ASSERT(key.objectid < end && key.objectid + key.offset <= end);

		caching_ctl->progress = key.objectid;

		offset = key.objectid;
		जबतक (offset < key.objectid + key.offset) अणु
			bit = मुक्त_space_test_bit(block_group, path, offset);
			अगर (prev_bit == 0 && bit == 1) अणु
				extent_start = offset;
			पूर्ण अन्यथा अगर (prev_bit == 1 && bit == 0) अणु
				total_found += add_new_मुक्त_space(block_group,
								  extent_start,
								  offset);
				अगर (total_found > CACHING_CTL_WAKE_UP) अणु
					total_found = 0;
					wake_up(&caching_ctl->रुको);
				पूर्ण
				extent_count++;
			पूर्ण
			prev_bit = bit;
			offset += fs_info->sectorsize;
		पूर्ण
	पूर्ण
	अगर (prev_bit == 1) अणु
		total_found += add_new_मुक्त_space(block_group, extent_start,
						  end);
		extent_count++;
	पूर्ण

	अगर (extent_count != expected_extent_count) अणु
		btrfs_err(fs_info,
			  "incorrect extent count for %llu; counted %u, expected %u",
			  block_group->start, extent_count,
			  expected_extent_count);
		ASSERT(0);
		ret = -EIO;
		जाओ out;
	पूर्ण

	caching_ctl->progress = (u64)-1;

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक load_मुक्त_space_extents(काष्ठा btrfs_caching_control *caching_ctl,
				   काष्ठा btrfs_path *path,
				   u32 expected_extent_count)
अणु
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_key key;
	u64 end;
	u64 total_found = 0;
	u32 extent_count = 0;
	पूर्णांक ret;

	block_group = caching_ctl->block_group;
	fs_info = block_group->fs_info;
	root = fs_info->मुक्त_space_root;

	end = block_group->start + block_group->length;

	जबतक (1) अणु
		ret = btrfs_next_item(root, path);
		अगर (ret < 0)
			जाओ out;
		अगर (ret)
			अवरोध;

		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);

		अगर (key.type == BTRFS_FREE_SPACE_INFO_KEY)
			अवरोध;

		ASSERT(key.type == BTRFS_FREE_SPACE_EXTENT_KEY);
		ASSERT(key.objectid < end && key.objectid + key.offset <= end);

		caching_ctl->progress = key.objectid;

		total_found += add_new_मुक्त_space(block_group, key.objectid,
						  key.objectid + key.offset);
		अगर (total_found > CACHING_CTL_WAKE_UP) अणु
			total_found = 0;
			wake_up(&caching_ctl->रुको);
		पूर्ण
		extent_count++;
	पूर्ण

	अगर (extent_count != expected_extent_count) अणु
		btrfs_err(fs_info,
			  "incorrect extent count for %llu; counted %u, expected %u",
			  block_group->start, extent_count,
			  expected_extent_count);
		ASSERT(0);
		ret = -EIO;
		जाओ out;
	पूर्ण

	caching_ctl->progress = (u64)-1;

	ret = 0;
out:
	वापस ret;
पूर्ण

पूर्णांक load_मुक्त_space_tree(काष्ठा btrfs_caching_control *caching_ctl)
अणु
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_मुक्त_space_info *info;
	काष्ठा btrfs_path *path;
	u32 extent_count, flags;
	पूर्णांक ret;

	block_group = caching_ctl->block_group;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/*
	 * Just like caching_thपढ़ो() करोesn't want to deadlock on the extent
	 * tree, we करोn't want to deadlock on the मुक्त space tree.
	 */
	path->skip_locking = 1;
	path->search_commit_root = 1;
	path->पढ़ोa = READA_FORWARD;

	info = search_मुक्त_space_info(शून्य, block_group, path, 0);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ out;
	पूर्ण
	extent_count = btrfs_मुक्त_space_extent_count(path->nodes[0], info);
	flags = btrfs_मुक्त_space_flags(path->nodes[0], info);

	/*
	 * We left path poपूर्णांकing to the मुक्त space info item, so now
	 * load_मुक्त_space_foo can just iterate through the मुक्त space tree from
	 * there.
	 */
	अगर (flags & BTRFS_FREE_SPACE_USING_BITMAPS)
		ret = load_मुक्त_space_biपंचांगaps(caching_ctl, path, extent_count);
	अन्यथा
		ret = load_मुक्त_space_extents(caching_ctl, path, extent_count);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण
