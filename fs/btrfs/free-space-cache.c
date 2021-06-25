<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Red Hat.  All rights reserved.
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/math64.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/error-injection.h>
#समावेश <linux/sched/mm.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "free-space-cache.h"
#समावेश "transaction.h"
#समावेश "disk-io.h"
#समावेश "extent_io.h"
#समावेश "volumes.h"
#समावेश "space-info.h"
#समावेश "delalloc-space.h"
#समावेश "block-group.h"
#समावेश "discard.h"

#घोषणा BITS_PER_BITMAP		(PAGE_SIZE * 8UL)
#घोषणा MAX_CACHE_BYTES_PER_GIG	SZ_64K
#घोषणा FORCE_EXTENT_THRESHOLD	SZ_1M

काष्ठा btrfs_trim_range अणु
	u64 start;
	u64 bytes;
	काष्ठा list_head list;
पूर्ण;

अटल पूर्णांक link_मुक्त_space(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			   काष्ठा btrfs_मुक्त_space *info);
अटल व्योम unlink_मुक्त_space(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			      काष्ठा btrfs_मुक्त_space *info);
अटल पूर्णांक search_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			 काष्ठा btrfs_मुक्त_space *biपंचांगap_info, u64 *offset,
			 u64 *bytes, bool क्रम_alloc);
अटल व्योम मुक्त_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			काष्ठा btrfs_मुक्त_space *biपंचांगap_info);
अटल व्योम biपंचांगap_clear_bits(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			      काष्ठा btrfs_मुक्त_space *info, u64 offset,
			      u64 bytes);

अटल काष्ठा inode *__lookup_मुक्त_space_inode(काष्ठा btrfs_root *root,
					       काष्ठा btrfs_path *path,
					       u64 offset)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key location;
	काष्ठा btrfs_disk_key disk_key;
	काष्ठा btrfs_मुक्त_space_header *header;
	काष्ठा extent_buffer *leaf;
	काष्ठा inode *inode = शून्य;
	अचिन्हित nofs_flag;
	पूर्णांक ret;

	key.objectid = BTRFS_FREE_SPACE_OBJECTID;
	key.offset = offset;
	key.type = 0;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस ERR_PTR(ret);
	अगर (ret > 0) अणु
		btrfs_release_path(path);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	leaf = path->nodes[0];
	header = btrfs_item_ptr(leaf, path->slots[0],
				काष्ठा btrfs_मुक्त_space_header);
	btrfs_मुक्त_space_key(leaf, header, &disk_key);
	btrfs_disk_key_to_cpu(&location, &disk_key);
	btrfs_release_path(path);

	/*
	 * We are often under a trans handle at this poपूर्णांक, so we need to make
	 * sure NOFS is set to keep us from deadlocking.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	inode = btrfs_iget_path(fs_info->sb, location.objectid, root, path);
	btrfs_release_path(path);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (IS_ERR(inode))
		वापस inode;

	mapping_set_gfp_mask(inode->i_mapping,
			mapping_gfp_स्थिरraपूर्णांक(inode->i_mapping,
			~(__GFP_FS | __GFP_HIGHMEM)));

	वापस inode;
पूर्ण

काष्ठा inode *lookup_मुक्त_space_inode(काष्ठा btrfs_block_group *block_group,
		काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा inode *inode = शून्य;
	u32 flags = BTRFS_INODE_NODATASUM | BTRFS_INODE_NODATACOW;

	spin_lock(&block_group->lock);
	अगर (block_group->inode)
		inode = igrab(block_group->inode);
	spin_unlock(&block_group->lock);
	अगर (inode)
		वापस inode;

	inode = __lookup_मुक्त_space_inode(fs_info->tree_root, path,
					  block_group->start);
	अगर (IS_ERR(inode))
		वापस inode;

	spin_lock(&block_group->lock);
	अगर (!((BTRFS_I(inode)->flags & flags) == flags)) अणु
		btrfs_info(fs_info, "Old style space inode found, converting.");
		BTRFS_I(inode)->flags |= BTRFS_INODE_NODATASUM |
			BTRFS_INODE_NODATACOW;
		block_group->disk_cache_state = BTRFS_DC_CLEAR;
	पूर्ण

	अगर (!block_group->iref) अणु
		block_group->inode = igrab(inode);
		block_group->iref = 1;
	पूर्ण
	spin_unlock(&block_group->lock);

	वापस inode;
पूर्ण

अटल पूर्णांक __create_मुक्त_space_inode(काष्ठा btrfs_root *root,
				     काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_path *path,
				     u64 ino, u64 offset)
अणु
	काष्ठा btrfs_key key;
	काष्ठा btrfs_disk_key disk_key;
	काष्ठा btrfs_मुक्त_space_header *header;
	काष्ठा btrfs_inode_item *inode_item;
	काष्ठा extent_buffer *leaf;
	/* We अंतरभूत CRCs क्रम the मुक्त disk space cache */
	स्थिर u64 flags = BTRFS_INODE_NOCOMPRESS | BTRFS_INODE_PREALLOC |
			  BTRFS_INODE_NODATASUM | BTRFS_INODE_NODATACOW;
	पूर्णांक ret;

	ret = btrfs_insert_empty_inode(trans, root, path, ino);
	अगर (ret)
		वापस ret;

	leaf = path->nodes[0];
	inode_item = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_inode_item);
	btrfs_item_key(leaf, &disk_key, path->slots[0]);
	memzero_extent_buffer(leaf, (अचिन्हित दीर्घ)inode_item,
			     माप(*inode_item));
	btrfs_set_inode_generation(leaf, inode_item, trans->transid);
	btrfs_set_inode_size(leaf, inode_item, 0);
	btrfs_set_inode_nbytes(leaf, inode_item, 0);
	btrfs_set_inode_uid(leaf, inode_item, 0);
	btrfs_set_inode_gid(leaf, inode_item, 0);
	btrfs_set_inode_mode(leaf, inode_item, S_IFREG | 0600);
	btrfs_set_inode_flags(leaf, inode_item, flags);
	btrfs_set_inode_nlink(leaf, inode_item, 1);
	btrfs_set_inode_transid(leaf, inode_item, trans->transid);
	btrfs_set_inode_block_group(leaf, inode_item, offset);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	key.objectid = BTRFS_FREE_SPACE_OBJECTID;
	key.offset = offset;
	key.type = 0;
	ret = btrfs_insert_empty_item(trans, root, path, &key,
				      माप(काष्ठा btrfs_मुक्त_space_header));
	अगर (ret < 0) अणु
		btrfs_release_path(path);
		वापस ret;
	पूर्ण

	leaf = path->nodes[0];
	header = btrfs_item_ptr(leaf, path->slots[0],
				काष्ठा btrfs_मुक्त_space_header);
	memzero_extent_buffer(leaf, (अचिन्हित दीर्घ)header, माप(*header));
	btrfs_set_मुक्त_space_key(leaf, header, &disk_key);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	वापस 0;
पूर्ण

पूर्णांक create_मुक्त_space_inode(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_block_group *block_group,
			    काष्ठा btrfs_path *path)
अणु
	पूर्णांक ret;
	u64 ino;

	ret = btrfs_get_मुक्त_objectid(trans->fs_info->tree_root, &ino);
	अगर (ret < 0)
		वापस ret;

	वापस __create_मुक्त_space_inode(trans->fs_info->tree_root, trans, path,
					 ino, block_group->start);
पूर्ण

/*
 * inode is an optional sink: अगर it is शून्य, btrfs_हटाओ_मुक्त_space_inode
 * handles lookup, otherwise it takes ownership and iमाला_दो the inode.
 * Don't reuse an inode poपूर्णांकer after passing it पूर्णांकo this function.
 */
पूर्णांक btrfs_हटाओ_मुक्त_space_inode(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा inode *inode,
				  काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	पूर्णांक ret = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	अगर (!inode)
		inode = lookup_मुक्त_space_inode(block_group, path);
	अगर (IS_ERR(inode)) अणु
		अगर (PTR_ERR(inode) != -ENOENT)
			ret = PTR_ERR(inode);
		जाओ out;
	पूर्ण
	ret = btrfs_orphan_add(trans, BTRFS_I(inode));
	अगर (ret) अणु
		btrfs_add_delayed_iput(inode);
		जाओ out;
	पूर्ण
	clear_nlink(inode);
	/* One क्रम the block groups ref */
	spin_lock(&block_group->lock);
	अगर (block_group->iref) अणु
		block_group->iref = 0;
		block_group->inode = शून्य;
		spin_unlock(&block_group->lock);
		iput(inode);
	पूर्ण अन्यथा अणु
		spin_unlock(&block_group->lock);
	पूर्ण
	/* One क्रम the lookup ref */
	btrfs_add_delayed_iput(inode);

	key.objectid = BTRFS_FREE_SPACE_OBJECTID;
	key.type = 0;
	key.offset = block_group->start;
	ret = btrfs_search_slot(trans, trans->fs_info->tree_root, &key, path,
				-1, 1);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = 0;
		जाओ out;
	पूर्ण
	ret = btrfs_del_item(trans, trans->fs_info->tree_root, path);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_check_trunc_cache_मुक्त_space(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा btrfs_block_rsv *rsv)
अणु
	u64 needed_bytes;
	पूर्णांक ret;

	/* 1 क्रम slack space, 1 क्रम updating the inode */
	needed_bytes = btrfs_calc_insert_metadata_size(fs_info, 1) +
		btrfs_calc_metadata_size(fs_info, 1);

	spin_lock(&rsv->lock);
	अगर (rsv->reserved < needed_bytes)
		ret = -ENOSPC;
	अन्यथा
		ret = 0;
	spin_unlock(&rsv->lock);
	वापस ret;
पूर्ण

पूर्णांक btrfs_truncate_मुक्त_space_cache(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_block_group *block_group,
				    काष्ठा inode *inode)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	पूर्णांक ret = 0;
	bool locked = false;

	अगर (block_group) अणु
		काष्ठा btrfs_path *path = btrfs_alloc_path();

		अगर (!path) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
		locked = true;
		mutex_lock(&trans->transaction->cache_ग_लिखो_mutex);
		अगर (!list_empty(&block_group->io_list)) अणु
			list_del_init(&block_group->io_list);

			btrfs_रुको_cache_io(trans, block_group, path);
			btrfs_put_block_group(block_group);
		पूर्ण

		/*
		 * now that we've truncated the cache away, its no दीर्घer
		 * setup or written
		 */
		spin_lock(&block_group->lock);
		block_group->disk_cache_state = BTRFS_DC_CLEAR;
		spin_unlock(&block_group->lock);
		btrfs_मुक्त_path(path);
	पूर्ण

	btrfs_i_size_ग_लिखो(BTRFS_I(inode), 0);
	truncate_pagecache(inode, 0);

	/*
	 * We skip the throttling logic क्रम मुक्त space cache inodes, so we करोn't
	 * need to check क्रम -EAGAIN.
	 */
	ret = btrfs_truncate_inode_items(trans, root, BTRFS_I(inode),
					 0, BTRFS_EXTENT_DATA_KEY);
	अगर (ret)
		जाओ fail;

	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));

fail:
	अगर (locked)
		mutex_unlock(&trans->transaction->cache_ग_लिखो_mutex);
	अगर (ret)
		btrfs_पात_transaction(trans, ret);

	वापस ret;
पूर्ण

अटल व्योम पढ़ोahead_cache(काष्ठा inode *inode)
अणु
	काष्ठा file_ra_state *ra;
	अचिन्हित दीर्घ last_index;

	ra = kzalloc(माप(*ra), GFP_NOFS);
	अगर (!ra)
		वापस;

	file_ra_state_init(ra, inode->i_mapping);
	last_index = (i_size_पढ़ो(inode) - 1) >> PAGE_SHIFT;

	page_cache_sync_पढ़ोahead(inode->i_mapping, ra, शून्य, 0, last_index);

	kमुक्त(ra);
पूर्ण

अटल पूर्णांक io_ctl_init(काष्ठा btrfs_io_ctl *io_ctl, काष्ठा inode *inode,
		       पूर्णांक ग_लिखो)
अणु
	पूर्णांक num_pages;

	num_pages = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);

	/* Make sure we can fit our crcs and generation पूर्णांकo the first page */
	अगर (ग_लिखो && (num_pages * माप(u32) + माप(u64)) > PAGE_SIZE)
		वापस -ENOSPC;

	स_रखो(io_ctl, 0, माप(काष्ठा btrfs_io_ctl));

	io_ctl->pages = kसुस्मृति(num_pages, माप(काष्ठा page *), GFP_NOFS);
	अगर (!io_ctl->pages)
		वापस -ENOMEM;

	io_ctl->num_pages = num_pages;
	io_ctl->fs_info = btrfs_sb(inode->i_sb);
	io_ctl->inode = inode;

	वापस 0;
पूर्ण
ALLOW_ERROR_INJECTION(io_ctl_init, ERRNO);

अटल व्योम io_ctl_मुक्त(काष्ठा btrfs_io_ctl *io_ctl)
अणु
	kमुक्त(io_ctl->pages);
	io_ctl->pages = शून्य;
पूर्ण

अटल व्योम io_ctl_unmap_page(काष्ठा btrfs_io_ctl *io_ctl)
अणु
	अगर (io_ctl->cur) अणु
		io_ctl->cur = शून्य;
		io_ctl->orig = शून्य;
	पूर्ण
पूर्ण

अटल व्योम io_ctl_map_page(काष्ठा btrfs_io_ctl *io_ctl, पूर्णांक clear)
अणु
	ASSERT(io_ctl->index < io_ctl->num_pages);
	io_ctl->page = io_ctl->pages[io_ctl->index++];
	io_ctl->cur = page_address(io_ctl->page);
	io_ctl->orig = io_ctl->cur;
	io_ctl->size = PAGE_SIZE;
	अगर (clear)
		clear_page(io_ctl->cur);
पूर्ण

अटल व्योम io_ctl_drop_pages(काष्ठा btrfs_io_ctl *io_ctl)
अणु
	पूर्णांक i;

	io_ctl_unmap_page(io_ctl);

	क्रम (i = 0; i < io_ctl->num_pages; i++) अणु
		अगर (io_ctl->pages[i]) अणु
			ClearPageChecked(io_ctl->pages[i]);
			unlock_page(io_ctl->pages[i]);
			put_page(io_ctl->pages[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक io_ctl_prepare_pages(काष्ठा btrfs_io_ctl *io_ctl, bool uptodate)
अणु
	काष्ठा page *page;
	काष्ठा inode *inode = io_ctl->inode;
	gfp_t mask = btrfs_alloc_ग_लिखो_mask(inode->i_mapping);
	पूर्णांक i;

	क्रम (i = 0; i < io_ctl->num_pages; i++) अणु
		पूर्णांक ret;

		page = find_or_create_page(inode->i_mapping, i, mask);
		अगर (!page) अणु
			io_ctl_drop_pages(io_ctl);
			वापस -ENOMEM;
		पूर्ण

		ret = set_page_extent_mapped(page);
		अगर (ret < 0) अणु
			unlock_page(page);
			put_page(page);
			io_ctl_drop_pages(io_ctl);
			वापस ret;
		पूर्ण

		io_ctl->pages[i] = page;
		अगर (uptodate && !PageUptodate(page)) अणु
			btrfs_पढ़ोpage(शून्य, page);
			lock_page(page);
			अगर (page->mapping != inode->i_mapping) अणु
				btrfs_err(BTRFS_I(inode)->root->fs_info,
					  "free space cache page truncated");
				io_ctl_drop_pages(io_ctl);
				वापस -EIO;
			पूर्ण
			अगर (!PageUptodate(page)) अणु
				btrfs_err(BTRFS_I(inode)->root->fs_info,
					   "error reading free space cache");
				io_ctl_drop_pages(io_ctl);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < io_ctl->num_pages; i++)
		clear_page_dirty_क्रम_io(io_ctl->pages[i]);

	वापस 0;
पूर्ण

अटल व्योम io_ctl_set_generation(काष्ठा btrfs_io_ctl *io_ctl, u64 generation)
अणु
	io_ctl_map_page(io_ctl, 1);

	/*
	 * Skip the csum areas.  If we करोn't check crcs then we just have a
	 * 64bit chunk at the front of the first page.
	 */
	io_ctl->cur += (माप(u32) * io_ctl->num_pages);
	io_ctl->size -= माप(u64) + (माप(u32) * io_ctl->num_pages);

	put_unaligned_le64(generation, io_ctl->cur);
	io_ctl->cur += माप(u64);
पूर्ण

अटल पूर्णांक io_ctl_check_generation(काष्ठा btrfs_io_ctl *io_ctl, u64 generation)
अणु
	u64 cache_gen;

	/*
	 * Skip the crc area.  If we करोn't check crcs then we just have a 64bit
	 * chunk at the front of the first page.
	 */
	io_ctl->cur += माप(u32) * io_ctl->num_pages;
	io_ctl->size -= माप(u64) + (माप(u32) * io_ctl->num_pages);

	cache_gen = get_unaligned_le64(io_ctl->cur);
	अगर (cache_gen != generation) अणु
		btrfs_err_rl(io_ctl->fs_info,
			"space cache generation (%llu) does not match inode (%llu)",
				cache_gen, generation);
		io_ctl_unmap_page(io_ctl);
		वापस -EIO;
	पूर्ण
	io_ctl->cur += माप(u64);
	वापस 0;
पूर्ण

अटल व्योम io_ctl_set_crc(काष्ठा btrfs_io_ctl *io_ctl, पूर्णांक index)
अणु
	u32 *पंचांगp;
	u32 crc = ~(u32)0;
	अचिन्हित offset = 0;

	अगर (index == 0)
		offset = माप(u32) * io_ctl->num_pages;

	crc = btrfs_crc32c(crc, io_ctl->orig + offset, PAGE_SIZE - offset);
	btrfs_crc32c_final(crc, (u8 *)&crc);
	io_ctl_unmap_page(io_ctl);
	पंचांगp = page_address(io_ctl->pages[0]);
	पंचांगp += index;
	*पंचांगp = crc;
पूर्ण

अटल पूर्णांक io_ctl_check_crc(काष्ठा btrfs_io_ctl *io_ctl, पूर्णांक index)
अणु
	u32 *पंचांगp, val;
	u32 crc = ~(u32)0;
	अचिन्हित offset = 0;

	अगर (index == 0)
		offset = माप(u32) * io_ctl->num_pages;

	पंचांगp = page_address(io_ctl->pages[0]);
	पंचांगp += index;
	val = *पंचांगp;

	io_ctl_map_page(io_ctl, 0);
	crc = btrfs_crc32c(crc, io_ctl->orig + offset, PAGE_SIZE - offset);
	btrfs_crc32c_final(crc, (u8 *)&crc);
	अगर (val != crc) अणु
		btrfs_err_rl(io_ctl->fs_info,
			"csum mismatch on free space cache");
		io_ctl_unmap_page(io_ctl);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक io_ctl_add_entry(काष्ठा btrfs_io_ctl *io_ctl, u64 offset, u64 bytes,
			    व्योम *biपंचांगap)
अणु
	काष्ठा btrfs_मुक्त_space_entry *entry;

	अगर (!io_ctl->cur)
		वापस -ENOSPC;

	entry = io_ctl->cur;
	put_unaligned_le64(offset, &entry->offset);
	put_unaligned_le64(bytes, &entry->bytes);
	entry->type = (biपंचांगap) ? BTRFS_FREE_SPACE_BITMAP :
		BTRFS_FREE_SPACE_EXTENT;
	io_ctl->cur += माप(काष्ठा btrfs_मुक्त_space_entry);
	io_ctl->size -= माप(काष्ठा btrfs_मुक्त_space_entry);

	अगर (io_ctl->size >= माप(काष्ठा btrfs_मुक्त_space_entry))
		वापस 0;

	io_ctl_set_crc(io_ctl, io_ctl->index - 1);

	/* No more pages to map */
	अगर (io_ctl->index >= io_ctl->num_pages)
		वापस 0;

	/* map the next page */
	io_ctl_map_page(io_ctl, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक io_ctl_add_biपंचांगap(काष्ठा btrfs_io_ctl *io_ctl, व्योम *biपंचांगap)
अणु
	अगर (!io_ctl->cur)
		वापस -ENOSPC;

	/*
	 * If we aren't at the start of the current page, unmap this one and
	 * map the next one अगर there is any left.
	 */
	अगर (io_ctl->cur != io_ctl->orig) अणु
		io_ctl_set_crc(io_ctl, io_ctl->index - 1);
		अगर (io_ctl->index >= io_ctl->num_pages)
			वापस -ENOSPC;
		io_ctl_map_page(io_ctl, 0);
	पूर्ण

	copy_page(io_ctl->cur, biपंचांगap);
	io_ctl_set_crc(io_ctl, io_ctl->index - 1);
	अगर (io_ctl->index < io_ctl->num_pages)
		io_ctl_map_page(io_ctl, 0);
	वापस 0;
पूर्ण

अटल व्योम io_ctl_zero_reमुख्यing_pages(काष्ठा btrfs_io_ctl *io_ctl)
अणु
	/*
	 * If we're not on the boundary we know we've modअगरied the page and we
	 * need to crc the page.
	 */
	अगर (io_ctl->cur != io_ctl->orig)
		io_ctl_set_crc(io_ctl, io_ctl->index - 1);
	अन्यथा
		io_ctl_unmap_page(io_ctl);

	जबतक (io_ctl->index < io_ctl->num_pages) अणु
		io_ctl_map_page(io_ctl, 1);
		io_ctl_set_crc(io_ctl, io_ctl->index - 1);
	पूर्ण
पूर्ण

अटल पूर्णांक io_ctl_पढ़ो_entry(काष्ठा btrfs_io_ctl *io_ctl,
			    काष्ठा btrfs_मुक्त_space *entry, u8 *type)
अणु
	काष्ठा btrfs_मुक्त_space_entry *e;
	पूर्णांक ret;

	अगर (!io_ctl->cur) अणु
		ret = io_ctl_check_crc(io_ctl, io_ctl->index);
		अगर (ret)
			वापस ret;
	पूर्ण

	e = io_ctl->cur;
	entry->offset = get_unaligned_le64(&e->offset);
	entry->bytes = get_unaligned_le64(&e->bytes);
	*type = e->type;
	io_ctl->cur += माप(काष्ठा btrfs_मुक्त_space_entry);
	io_ctl->size -= माप(काष्ठा btrfs_मुक्त_space_entry);

	अगर (io_ctl->size >= माप(काष्ठा btrfs_मुक्त_space_entry))
		वापस 0;

	io_ctl_unmap_page(io_ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक io_ctl_पढ़ो_biपंचांगap(काष्ठा btrfs_io_ctl *io_ctl,
			      काष्ठा btrfs_मुक्त_space *entry)
अणु
	पूर्णांक ret;

	ret = io_ctl_check_crc(io_ctl, io_ctl->index);
	अगर (ret)
		वापस ret;

	copy_page(entry->biपंचांगap, io_ctl->cur);
	io_ctl_unmap_page(io_ctl);

	वापस 0;
पूर्ण

अटल व्योम recalculate_thresholds(काष्ठा btrfs_मुक्त_space_ctl *ctl)
अणु
	काष्ठा btrfs_block_group *block_group = ctl->निजी;
	u64 max_bytes;
	u64 biपंचांगap_bytes;
	u64 extent_bytes;
	u64 size = block_group->length;
	u64 bytes_per_bg = BITS_PER_BITMAP * ctl->unit;
	u64 max_biपंचांगaps = भाग64_u64(size + bytes_per_bg - 1, bytes_per_bg);

	max_biपंचांगaps = max_t(u64, max_biपंचांगaps, 1);

	ASSERT(ctl->total_biपंचांगaps <= max_biपंचांगaps);

	/*
	 * We are trying to keep the total amount of memory used per 1GiB of
	 * space to be MAX_CACHE_BYTES_PER_GIG.  However, with a reclamation
	 * mechanism of pulling extents >= FORCE_EXTENT_THRESHOLD out of
	 * biपंचांगaps, we may end up using more memory than this.
	 */
	अगर (size < SZ_1G)
		max_bytes = MAX_CACHE_BYTES_PER_GIG;
	अन्यथा
		max_bytes = MAX_CACHE_BYTES_PER_GIG * भाग_u64(size, SZ_1G);

	biपंचांगap_bytes = ctl->total_biपंचांगaps * ctl->unit;

	/*
	 * we want the extent entry threshold to always be at most 1/2 the max
	 * bytes we can have, or whatever is less than that.
	 */
	extent_bytes = max_bytes - biपंचांगap_bytes;
	extent_bytes = min_t(u64, extent_bytes, max_bytes >> 1);

	ctl->extents_thresh =
		भाग_u64(extent_bytes, माप(काष्ठा btrfs_मुक्त_space));
पूर्ण

अटल पूर्णांक __load_मुक्त_space_cache(काष्ठा btrfs_root *root, काष्ठा inode *inode,
				   काष्ठा btrfs_मुक्त_space_ctl *ctl,
				   काष्ठा btrfs_path *path, u64 offset)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_मुक्त_space_header *header;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_io_ctl io_ctl;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_मुक्त_space *e, *n;
	LIST_HEAD(biपंचांगaps);
	u64 num_entries;
	u64 num_biपंचांगaps;
	u64 generation;
	u8 type;
	पूर्णांक ret = 0;

	/* Nothing in the space cache, goodbye */
	अगर (!i_size_पढ़ो(inode))
		वापस 0;

	key.objectid = BTRFS_FREE_SPACE_OBJECTID;
	key.offset = offset;
	key.type = 0;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस 0;
	अन्यथा अगर (ret > 0) अणु
		btrfs_release_path(path);
		वापस 0;
	पूर्ण

	ret = -1;

	leaf = path->nodes[0];
	header = btrfs_item_ptr(leaf, path->slots[0],
				काष्ठा btrfs_मुक्त_space_header);
	num_entries = btrfs_मुक्त_space_entries(leaf, header);
	num_biपंचांगaps = btrfs_मुक्त_space_biपंचांगaps(leaf, header);
	generation = btrfs_मुक्त_space_generation(leaf, header);
	btrfs_release_path(path);

	अगर (!BTRFS_I(inode)->generation) अणु
		btrfs_info(fs_info,
			   "the free space cache file (%llu) is invalid, skip it",
			   offset);
		वापस 0;
	पूर्ण

	अगर (BTRFS_I(inode)->generation != generation) अणु
		btrfs_err(fs_info,
			  "free space inode generation (%llu) did not match free space cache generation (%llu)",
			  BTRFS_I(inode)->generation, generation);
		वापस 0;
	पूर्ण

	अगर (!num_entries)
		वापस 0;

	ret = io_ctl_init(&io_ctl, inode, 0);
	अगर (ret)
		वापस ret;

	पढ़ोahead_cache(inode);

	ret = io_ctl_prepare_pages(&io_ctl, true);
	अगर (ret)
		जाओ out;

	ret = io_ctl_check_crc(&io_ctl, 0);
	अगर (ret)
		जाओ मुक्त_cache;

	ret = io_ctl_check_generation(&io_ctl, generation);
	अगर (ret)
		जाओ मुक्त_cache;

	जबतक (num_entries) अणु
		e = kmem_cache_zalloc(btrfs_मुक्त_space_cachep,
				      GFP_NOFS);
		अगर (!e) अणु
			ret = -ENOMEM;
			जाओ मुक्त_cache;
		पूर्ण

		ret = io_ctl_पढ़ो_entry(&io_ctl, e, &type);
		अगर (ret) अणु
			kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, e);
			जाओ मुक्त_cache;
		पूर्ण

		अगर (!e->bytes) अणु
			ret = -1;
			kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, e);
			जाओ मुक्त_cache;
		पूर्ण

		अगर (type == BTRFS_FREE_SPACE_EXTENT) अणु
			spin_lock(&ctl->tree_lock);
			ret = link_मुक्त_space(ctl, e);
			spin_unlock(&ctl->tree_lock);
			अगर (ret) अणु
				btrfs_err(fs_info,
					"Duplicate entries in free space cache, dumping");
				kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, e);
				जाओ मुक्त_cache;
			पूर्ण
		पूर्ण अन्यथा अणु
			ASSERT(num_biपंचांगaps);
			num_biपंचांगaps--;
			e->biपंचांगap = kmem_cache_zalloc(
					btrfs_मुक्त_space_biपंचांगap_cachep, GFP_NOFS);
			अगर (!e->biपंचांगap) अणु
				ret = -ENOMEM;
				kmem_cache_मुक्त(
					btrfs_मुक्त_space_cachep, e);
				जाओ मुक्त_cache;
			पूर्ण
			spin_lock(&ctl->tree_lock);
			ret = link_मुक्त_space(ctl, e);
			ctl->total_biपंचांगaps++;
			recalculate_thresholds(ctl);
			spin_unlock(&ctl->tree_lock);
			अगर (ret) अणु
				btrfs_err(fs_info,
					"Duplicate entries in free space cache, dumping");
				kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, e);
				जाओ मुक्त_cache;
			पूर्ण
			list_add_tail(&e->list, &biपंचांगaps);
		पूर्ण

		num_entries--;
	पूर्ण

	io_ctl_unmap_page(&io_ctl);

	/*
	 * We add the biपंचांगaps at the end of the entries in order that
	 * the biपंचांगap entries are added to the cache.
	 */
	list_क्रम_each_entry_safe(e, n, &biपंचांगaps, list) अणु
		list_del_init(&e->list);
		ret = io_ctl_पढ़ो_biपंचांगap(&io_ctl, e);
		अगर (ret)
			जाओ मुक्त_cache;
	पूर्ण

	io_ctl_drop_pages(&io_ctl);
	ret = 1;
out:
	io_ctl_मुक्त(&io_ctl);
	वापस ret;
मुक्त_cache:
	io_ctl_drop_pages(&io_ctl);
	__btrfs_हटाओ_मुक्त_space_cache(ctl);
	जाओ out;
पूर्ण

अटल पूर्णांक copy_मुक्त_space_cache(काष्ठा btrfs_block_group *block_group,
				 काष्ठा btrfs_मुक्त_space_ctl *ctl)
अणु
	काष्ठा btrfs_मुक्त_space *info;
	काष्ठा rb_node *n;
	पूर्णांक ret = 0;

	जबतक (!ret && (n = rb_first(&ctl->मुक्त_space_offset)) != शून्य) अणु
		info = rb_entry(n, काष्ठा btrfs_मुक्त_space, offset_index);
		अगर (!info->biपंचांगap) अणु
			unlink_मुक्त_space(ctl, info);
			ret = btrfs_add_मुक्त_space(block_group, info->offset,
						   info->bytes);
			kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, info);
		पूर्ण अन्यथा अणु
			u64 offset = info->offset;
			u64 bytes = ctl->unit;

			जबतक (search_biपंचांगap(ctl, info, &offset, &bytes,
					     false) == 0) अणु
				ret = btrfs_add_मुक्त_space(block_group, offset,
							   bytes);
				अगर (ret)
					अवरोध;
				biपंचांगap_clear_bits(ctl, info, offset, bytes);
				offset = info->offset;
				bytes = ctl->unit;
			पूर्ण
			मुक्त_biपंचांगap(ctl, info);
		पूर्ण
		cond_resched();
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक load_मुक्त_space_cache(काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space_ctl पंचांगp_ctl = अणुपूर्ण;
	काष्ठा inode *inode;
	काष्ठा btrfs_path *path;
	पूर्णांक ret = 0;
	bool matched;
	u64 used = block_group->used;

	/*
	 * Because we could potentially discard our loaded मुक्त space, we want
	 * to load everything पूर्णांकo a temporary काष्ठाure first, and then अगर it's
	 * valid copy it all पूर्णांकo the actual मुक्त space ctl.
	 */
	btrfs_init_मुक्त_space_ctl(block_group, &पंचांगp_ctl);

	/*
	 * If this block group has been marked to be cleared क्रम one reason or
	 * another then we can't trust the on disk cache, so just वापस.
	 */
	spin_lock(&block_group->lock);
	अगर (block_group->disk_cache_state != BTRFS_DC_WRITTEN) अणु
		spin_unlock(&block_group->lock);
		वापस 0;
	पूर्ण
	spin_unlock(&block_group->lock);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस 0;
	path->search_commit_root = 1;
	path->skip_locking = 1;

	/*
	 * We must pass a path with search_commit_root set to btrfs_iget in
	 * order to aव्योम a deadlock when allocating extents क्रम the tree root.
	 *
	 * When we are COWing an extent buffer from the tree root, when looking
	 * क्रम a मुक्त extent, at extent-tree.c:find_मुक्त_extent(), we can find
	 * block group without its मुक्त space cache loaded. When we find one
	 * we must load its space cache which requires पढ़ोing its मुक्त space
	 * cache's inode item from the root tree. If this inode item is located
	 * in the same leaf that we started COWing beक्रमe, then we end up in
	 * deadlock on the extent buffer (trying to पढ़ो lock it when we
	 * previously ग_लिखो locked it).
	 *
	 * It's safe to पढ़ो the inode item using the commit root because
	 * block groups, once loaded, stay in memory क्रमever (until they are
	 * हटाओd) as well as their space caches once loaded. New block groups
	 * once created get their ->cached field set to BTRFS_CACHE_FINISHED so
	 * we will never try to पढ़ो their inode item जबतक the fs is mounted.
	 */
	inode = lookup_मुक्त_space_inode(block_group, path);
	अगर (IS_ERR(inode)) अणु
		btrfs_मुक्त_path(path);
		वापस 0;
	पूर्ण

	/* We may have converted the inode and made the cache invalid. */
	spin_lock(&block_group->lock);
	अगर (block_group->disk_cache_state != BTRFS_DC_WRITTEN) अणु
		spin_unlock(&block_group->lock);
		btrfs_मुक्त_path(path);
		जाओ out;
	पूर्ण
	spin_unlock(&block_group->lock);

	ret = __load_मुक्त_space_cache(fs_info->tree_root, inode, &पंचांगp_ctl,
				      path, block_group->start);
	btrfs_मुक्त_path(path);
	अगर (ret <= 0)
		जाओ out;

	matched = (पंचांगp_ctl.मुक्त_space == (block_group->length - used -
					  block_group->bytes_super));

	अगर (matched) अणु
		ret = copy_मुक्त_space_cache(block_group, &पंचांगp_ctl);
		/*
		 * ret == 1 means we successfully loaded the मुक्त space cache,
		 * so we need to re-set it here.
		 */
		अगर (ret == 0)
			ret = 1;
	पूर्ण अन्यथा अणु
		__btrfs_हटाओ_मुक्त_space_cache(&पंचांगp_ctl);
		btrfs_warn(fs_info,
			   "block group %llu has wrong amount of free space",
			   block_group->start);
		ret = -1;
	पूर्ण
out:
	अगर (ret < 0) अणु
		/* This cache is bogus, make sure it माला_लो cleared */
		spin_lock(&block_group->lock);
		block_group->disk_cache_state = BTRFS_DC_CLEAR;
		spin_unlock(&block_group->lock);
		ret = 0;

		btrfs_warn(fs_info,
			   "failed to load free space cache for block group %llu, rebuilding it now",
			   block_group->start);
	पूर्ण

	spin_lock(&ctl->tree_lock);
	btrfs_discard_update_discardable(block_group);
	spin_unlock(&ctl->tree_lock);
	iput(inode);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक ग_लिखो_cache_extent_entries(काष्ठा btrfs_io_ctl *io_ctl,
			      काष्ठा btrfs_मुक्त_space_ctl *ctl,
			      काष्ठा btrfs_block_group *block_group,
			      पूर्णांक *entries, पूर्णांक *biपंचांगaps,
			      काष्ठा list_head *biपंचांगap_list)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_मुक्त_cluster *cluster = शून्य;
	काष्ठा btrfs_मुक्त_cluster *cluster_locked = शून्य;
	काष्ठा rb_node *node = rb_first(&ctl->मुक्त_space_offset);
	काष्ठा btrfs_trim_range *trim_entry;

	/* Get the cluster क्रम this block_group अगर it exists */
	अगर (block_group && !list_empty(&block_group->cluster_list)) अणु
		cluster = list_entry(block_group->cluster_list.next,
				     काष्ठा btrfs_मुक्त_cluster,
				     block_group_list);
	पूर्ण

	अगर (!node && cluster) अणु
		cluster_locked = cluster;
		spin_lock(&cluster_locked->lock);
		node = rb_first(&cluster->root);
		cluster = शून्य;
	पूर्ण

	/* Write out the extent entries */
	जबतक (node) अणु
		काष्ठा btrfs_मुक्त_space *e;

		e = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);
		*entries += 1;

		ret = io_ctl_add_entry(io_ctl, e->offset, e->bytes,
				       e->biपंचांगap);
		अगर (ret)
			जाओ fail;

		अगर (e->biपंचांगap) अणु
			list_add_tail(&e->list, biपंचांगap_list);
			*biपंचांगaps += 1;
		पूर्ण
		node = rb_next(node);
		अगर (!node && cluster) अणु
			node = rb_first(&cluster->root);
			cluster_locked = cluster;
			spin_lock(&cluster_locked->lock);
			cluster = शून्य;
		पूर्ण
	पूर्ण
	अगर (cluster_locked) अणु
		spin_unlock(&cluster_locked->lock);
		cluster_locked = शून्य;
	पूर्ण

	/*
	 * Make sure we करोn't miss any range that was हटाओd from our rbtree
	 * because trimming is running. Otherwise after a umount+mount (or crash
	 * after committing the transaction) we would leak मुक्त space and get
	 * an inconsistent मुक्त space cache report from fsck.
	 */
	list_क्रम_each_entry(trim_entry, &ctl->trimming_ranges, list) अणु
		ret = io_ctl_add_entry(io_ctl, trim_entry->start,
				       trim_entry->bytes, शून्य);
		अगर (ret)
			जाओ fail;
		*entries += 1;
	पूर्ण

	वापस 0;
fail:
	अगर (cluster_locked)
		spin_unlock(&cluster_locked->lock);
	वापस -ENOSPC;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
update_cache_item(काष्ठा btrfs_trans_handle *trans,
		  काष्ठा btrfs_root *root,
		  काष्ठा inode *inode,
		  काष्ठा btrfs_path *path, u64 offset,
		  पूर्णांक entries, पूर्णांक biपंचांगaps)
अणु
	काष्ठा btrfs_key key;
	काष्ठा btrfs_मुक्त_space_header *header;
	काष्ठा extent_buffer *leaf;
	पूर्णांक ret;

	key.objectid = BTRFS_FREE_SPACE_OBJECTID;
	key.offset = offset;
	key.type = 0;

	ret = btrfs_search_slot(trans, root, &key, path, 0, 1);
	अगर (ret < 0) अणु
		clear_extent_bit(&BTRFS_I(inode)->io_tree, 0, inode->i_size - 1,
				 EXTENT_DELALLOC, 0, 0, शून्य);
		जाओ fail;
	पूर्ण
	leaf = path->nodes[0];
	अगर (ret > 0) अणु
		काष्ठा btrfs_key found_key;
		ASSERT(path->slots[0]);
		path->slots[0]--;
		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
		अगर (found_key.objectid != BTRFS_FREE_SPACE_OBJECTID ||
		    found_key.offset != offset) अणु
			clear_extent_bit(&BTRFS_I(inode)->io_tree, 0,
					 inode->i_size - 1, EXTENT_DELALLOC, 0,
					 0, शून्य);
			btrfs_release_path(path);
			जाओ fail;
		पूर्ण
	पूर्ण

	BTRFS_I(inode)->generation = trans->transid;
	header = btrfs_item_ptr(leaf, path->slots[0],
				काष्ठा btrfs_मुक्त_space_header);
	btrfs_set_मुक्त_space_entries(leaf, header, entries);
	btrfs_set_मुक्त_space_biपंचांगaps(leaf, header, biपंचांगaps);
	btrfs_set_मुक्त_space_generation(leaf, header, trans->transid);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	वापस 0;

fail:
	वापस -1;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ग_लिखो_pinned_extent_entries(
			    काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_block_group *block_group,
			    काष्ठा btrfs_io_ctl *io_ctl,
			    पूर्णांक *entries)
अणु
	u64 start, extent_start, extent_end, len;
	काष्ठा extent_io_tree *unpin = शून्य;
	पूर्णांक ret;

	अगर (!block_group)
		वापस 0;

	/*
	 * We want to add any pinned extents to our मुक्त space cache
	 * so we करोn't leak the space
	 *
	 * We shouldn't have चयनed the pinned extents yet so this is the
	 * right one
	 */
	unpin = &trans->transaction->pinned_extents;

	start = block_group->start;

	जबतक (start < block_group->start + block_group->length) अणु
		ret = find_first_extent_bit(unpin, start,
					    &extent_start, &extent_end,
					    EXTENT_सूचीTY, शून्य);
		अगर (ret)
			वापस 0;

		/* This pinned extent is out of our range */
		अगर (extent_start >= block_group->start + block_group->length)
			वापस 0;

		extent_start = max(extent_start, start);
		extent_end = min(block_group->start + block_group->length,
				 extent_end + 1);
		len = extent_end - extent_start;

		*entries += 1;
		ret = io_ctl_add_entry(io_ctl, extent_start, len, शून्य);
		अगर (ret)
			वापस -ENOSPC;

		start = extent_end;
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ग_लिखो_biपंचांगap_entries(काष्ठा btrfs_io_ctl *io_ctl, काष्ठा list_head *biपंचांगap_list)
अणु
	काष्ठा btrfs_मुक्त_space *entry, *next;
	पूर्णांक ret;

	/* Write out the biपंचांगaps */
	list_क्रम_each_entry_safe(entry, next, biपंचांगap_list, list) अणु
		ret = io_ctl_add_biपंचांगap(io_ctl, entry->biपंचांगap);
		अगर (ret)
			वापस -ENOSPC;
		list_del_init(&entry->list);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक flush_dirty_cache(काष्ठा inode *inode)
अणु
	पूर्णांक ret;

	ret = btrfs_रुको_ordered_range(inode, 0, (u64)-1);
	अगर (ret)
		clear_extent_bit(&BTRFS_I(inode)->io_tree, 0, inode->i_size - 1,
				 EXTENT_DELALLOC, 0, 0, शून्य);

	वापस ret;
पूर्ण

अटल व्योम noअंतरभूत_क्रम_stack
cleanup_biपंचांगap_list(काष्ठा list_head *biपंचांगap_list)
अणु
	काष्ठा btrfs_मुक्त_space *entry, *next;

	list_क्रम_each_entry_safe(entry, next, biपंचांगap_list, list)
		list_del_init(&entry->list);
पूर्ण

अटल व्योम noअंतरभूत_क्रम_stack
cleanup_ग_लिखो_cache_enospc(काष्ठा inode *inode,
			   काष्ठा btrfs_io_ctl *io_ctl,
			   काष्ठा extent_state **cached_state)
अणु
	io_ctl_drop_pages(io_ctl);
	unlock_extent_cached(&BTRFS_I(inode)->io_tree, 0,
			     i_size_पढ़ो(inode) - 1, cached_state);
पूर्ण

अटल पूर्णांक __btrfs_रुको_cache_io(काष्ठा btrfs_root *root,
				 काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_block_group *block_group,
				 काष्ठा btrfs_io_ctl *io_ctl,
				 काष्ठा btrfs_path *path, u64 offset)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode = io_ctl->inode;

	अगर (!inode)
		वापस 0;

	/* Flush the dirty pages in the cache file. */
	ret = flush_dirty_cache(inode);
	अगर (ret)
		जाओ out;

	/* Update the cache item to tell everyone this cache file is valid. */
	ret = update_cache_item(trans, root, inode, path, offset,
				io_ctl->entries, io_ctl->biपंचांगaps);
out:
	अगर (ret) अणु
		invalidate_inode_pages2(inode->i_mapping);
		BTRFS_I(inode)->generation = 0;
		अगर (block_group)
			btrfs_debug(root->fs_info,
	  "failed to write free space cache for block group %llu error %d",
				  block_group->start, ret);
	पूर्ण
	btrfs_update_inode(trans, root, BTRFS_I(inode));

	अगर (block_group) अणु
		/* the dirty list is रक्षित by the dirty_bgs_lock */
		spin_lock(&trans->transaction->dirty_bgs_lock);

		/* the disk_cache_state is रक्षित by the block group lock */
		spin_lock(&block_group->lock);

		/*
		 * only mark this as written अगर we didn't get put back on
		 * the dirty list जबतक रुकोing क्रम IO.   Otherwise our
		 * cache state won't be right, and we won't get written again
		 */
		अगर (!ret && list_empty(&block_group->dirty_list))
			block_group->disk_cache_state = BTRFS_DC_WRITTEN;
		अन्यथा अगर (ret)
			block_group->disk_cache_state = BTRFS_DC_ERROR;

		spin_unlock(&block_group->lock);
		spin_unlock(&trans->transaction->dirty_bgs_lock);
		io_ctl->inode = शून्य;
		iput(inode);
	पूर्ण

	वापस ret;

पूर्ण

पूर्णांक btrfs_रुको_cache_io(काष्ठा btrfs_trans_handle *trans,
			काष्ठा btrfs_block_group *block_group,
			काष्ठा btrfs_path *path)
अणु
	वापस __btrfs_रुको_cache_io(block_group->fs_info->tree_root, trans,
				     block_group, &block_group->io_ctl,
				     path, block_group->start);
पूर्ण

/**
 * Write out cached info to an inode
 *
 * @root:        root the inode beदीर्घs to
 * @inode:       मुक्तspace inode we are writing out
 * @ctl:         मुक्त space cache we are going to ग_लिखो out
 * @block_group: block_group क्रम this cache अगर it beदीर्घs to a block_group
 * @io_ctl:      holds context क्रम the io
 * @trans:       the trans handle
 *
 * This function ग_लिखोs out a मुक्त space cache काष्ठा to disk क्रम quick recovery
 * on mount.  This will वापस 0 अगर it was successful in writing the cache out,
 * or an त्रुटि_सं अगर it was not.
 */
अटल पूर्णांक __btrfs_ग_लिखो_out_cache(काष्ठा btrfs_root *root, काष्ठा inode *inode,
				   काष्ठा btrfs_मुक्त_space_ctl *ctl,
				   काष्ठा btrfs_block_group *block_group,
				   काष्ठा btrfs_io_ctl *io_ctl,
				   काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा extent_state *cached_state = शून्य;
	LIST_HEAD(biपंचांगap_list);
	पूर्णांक entries = 0;
	पूर्णांक biपंचांगaps = 0;
	पूर्णांक ret;
	पूर्णांक must_iput = 0;

	अगर (!i_size_पढ़ो(inode))
		वापस -EIO;

	WARN_ON(io_ctl->pages);
	ret = io_ctl_init(io_ctl, inode, 1);
	अगर (ret)
		वापस ret;

	अगर (block_group && (block_group->flags & BTRFS_BLOCK_GROUP_DATA)) अणु
		करोwn_ग_लिखो(&block_group->data_rwsem);
		spin_lock(&block_group->lock);
		अगर (block_group->delalloc_bytes) अणु
			block_group->disk_cache_state = BTRFS_DC_WRITTEN;
			spin_unlock(&block_group->lock);
			up_ग_लिखो(&block_group->data_rwsem);
			BTRFS_I(inode)->generation = 0;
			ret = 0;
			must_iput = 1;
			जाओ out;
		पूर्ण
		spin_unlock(&block_group->lock);
	पूर्ण

	/* Lock all pages first so we can lock the extent safely. */
	ret = io_ctl_prepare_pages(io_ctl, false);
	अगर (ret)
		जाओ out_unlock;

	lock_extent_bits(&BTRFS_I(inode)->io_tree, 0, i_size_पढ़ो(inode) - 1,
			 &cached_state);

	io_ctl_set_generation(io_ctl, trans->transid);

	mutex_lock(&ctl->cache_ग_लिखोout_mutex);
	/* Write out the extent entries in the मुक्त space cache */
	spin_lock(&ctl->tree_lock);
	ret = ग_लिखो_cache_extent_entries(io_ctl, ctl,
					 block_group, &entries, &biपंचांगaps,
					 &biपंचांगap_list);
	अगर (ret)
		जाओ out_nospc_locked;

	/*
	 * Some spaces that are मुक्तd in the current transaction are pinned,
	 * they will be added पूर्णांकo मुक्त space cache after the transaction is
	 * committed, we shouldn't lose them.
	 *
	 * If this changes जबतक we are working we'll get added back to
	 * the dirty list and reकरो it.  No locking needed
	 */
	ret = ग_लिखो_pinned_extent_entries(trans, block_group, io_ctl, &entries);
	अगर (ret)
		जाओ out_nospc_locked;

	/*
	 * At last, we ग_लिखो out all the biपंचांगaps and keep cache_ग_लिखोout_mutex
	 * locked जबतक करोing it because a concurrent trim can be manipulating
	 * or मुक्तing the biपंचांगap.
	 */
	ret = ग_लिखो_biपंचांगap_entries(io_ctl, &biपंचांगap_list);
	spin_unlock(&ctl->tree_lock);
	mutex_unlock(&ctl->cache_ग_लिखोout_mutex);
	अगर (ret)
		जाओ out_nospc;

	/* Zero out the rest of the pages just to make sure */
	io_ctl_zero_reमुख्यing_pages(io_ctl);

	/* Everything is written out, now we dirty the pages in the file. */
	ret = btrfs_dirty_pages(BTRFS_I(inode), io_ctl->pages,
				io_ctl->num_pages, 0, i_size_पढ़ो(inode),
				&cached_state, false);
	अगर (ret)
		जाओ out_nospc;

	अगर (block_group && (block_group->flags & BTRFS_BLOCK_GROUP_DATA))
		up_ग_लिखो(&block_group->data_rwsem);
	/*
	 * Release the pages and unlock the extent, we will flush
	 * them out later
	 */
	io_ctl_drop_pages(io_ctl);
	io_ctl_मुक्त(io_ctl);

	unlock_extent_cached(&BTRFS_I(inode)->io_tree, 0,
			     i_size_पढ़ो(inode) - 1, &cached_state);

	/*
	 * at this poपूर्णांक the pages are under IO and we're happy,
	 * The caller is responsible क्रम रुकोing on them and updating
	 * the cache and the inode
	 */
	io_ctl->entries = entries;
	io_ctl->biपंचांगaps = biपंचांगaps;

	ret = btrfs_fdataग_लिखो_range(inode, 0, (u64)-1);
	अगर (ret)
		जाओ out;

	वापस 0;

out_nospc_locked:
	cleanup_biपंचांगap_list(&biपंचांगap_list);
	spin_unlock(&ctl->tree_lock);
	mutex_unlock(&ctl->cache_ग_लिखोout_mutex);

out_nospc:
	cleanup_ग_लिखो_cache_enospc(inode, io_ctl, &cached_state);

out_unlock:
	अगर (block_group && (block_group->flags & BTRFS_BLOCK_GROUP_DATA))
		up_ग_लिखो(&block_group->data_rwsem);

out:
	io_ctl->inode = शून्य;
	io_ctl_मुक्त(io_ctl);
	अगर (ret) अणु
		invalidate_inode_pages2(inode->i_mapping);
		BTRFS_I(inode)->generation = 0;
	पूर्ण
	btrfs_update_inode(trans, root, BTRFS_I(inode));
	अगर (must_iput)
		iput(inode);
	वापस ret;
पूर्ण

पूर्णांक btrfs_ग_लिखो_out_cache(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_block_group *block_group,
			  काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा inode *inode;
	पूर्णांक ret = 0;

	spin_lock(&block_group->lock);
	अगर (block_group->disk_cache_state < BTRFS_DC_SETUP) अणु
		spin_unlock(&block_group->lock);
		वापस 0;
	पूर्ण
	spin_unlock(&block_group->lock);

	inode = lookup_मुक्त_space_inode(block_group, path);
	अगर (IS_ERR(inode))
		वापस 0;

	ret = __btrfs_ग_लिखो_out_cache(fs_info->tree_root, inode, ctl,
				block_group, &block_group->io_ctl, trans);
	अगर (ret) अणु
		btrfs_debug(fs_info,
	  "failed to write free space cache for block group %llu error %d",
			  block_group->start, ret);
		spin_lock(&block_group->lock);
		block_group->disk_cache_state = BTRFS_DC_ERROR;
		spin_unlock(&block_group->lock);

		block_group->io_ctl.inode = शून्य;
		iput(inode);
	पूर्ण

	/*
	 * अगर ret == 0 the caller is expected to call btrfs_रुको_cache_io
	 * to रुको क्रम IO and put the inode
	 */

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ offset_to_bit(u64 biपंचांगap_start, u32 unit,
					  u64 offset)
अणु
	ASSERT(offset >= biपंचांगap_start);
	offset -= biपंचांगap_start;
	वापस (अचिन्हित दीर्घ)(भाग_u64(offset, unit));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ bytes_to_bits(u64 bytes, u32 unit)
अणु
	वापस (अचिन्हित दीर्घ)(भाग_u64(bytes, unit));
पूर्ण

अटल अंतरभूत u64 offset_to_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
				   u64 offset)
अणु
	u64 biपंचांगap_start;
	u64 bytes_per_biपंचांगap;

	bytes_per_biपंचांगap = BITS_PER_BITMAP * ctl->unit;
	biपंचांगap_start = offset - ctl->start;
	biपंचांगap_start = भाग64_u64(biपंचांगap_start, bytes_per_biपंचांगap);
	biपंचांगap_start *= bytes_per_biपंचांगap;
	biपंचांगap_start += ctl->start;

	वापस biपंचांगap_start;
पूर्ण

अटल पूर्णांक tree_insert_offset(काष्ठा rb_root *root, u64 offset,
			      काष्ठा rb_node *node, पूर्णांक biपंचांगap)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा btrfs_मुक्त_space *info;

	जबतक (*p) अणु
		parent = *p;
		info = rb_entry(parent, काष्ठा btrfs_मुक्त_space, offset_index);

		अगर (offset < info->offset) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (offset > info->offset) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			/*
			 * we could have a biपंचांगap entry and an extent entry
			 * share the same offset.  If this is the हाल, we want
			 * the extent entry to always be found first अगर we करो a
			 * linear search through the tree, since we want to have
			 * the quickest allocation समय, and allocating from an
			 * extent is faster than allocating from a biपंचांगap.  So
			 * अगर we're inserting a biपंचांगap and we find an entry at
			 * this offset, we want to go right, or after this entry
			 * logically.  If we are inserting an extent and we've
			 * found a biपंचांगap, we want to go left, or beक्रमe
			 * logically.
			 */
			अगर (biपंचांगap) अणु
				अगर (info->biपंचांगap) अणु
					WARN_ON_ONCE(1);
					वापस -EEXIST;
				पूर्ण
				p = &(*p)->rb_right;
			पूर्ण अन्यथा अणु
				अगर (!info->biपंचांगap) अणु
					WARN_ON_ONCE(1);
					वापस -EEXIST;
				पूर्ण
				p = &(*p)->rb_left;
			पूर्ण
		पूर्ण
	पूर्ण

	rb_link_node(node, parent, p);
	rb_insert_color(node, root);

	वापस 0;
पूर्ण

/*
 * searches the tree क्रम the given offset.
 *
 * fuzzy - If this is set, then we are trying to make an allocation, and we just
 * want a section that has at least bytes size and comes at or after the given
 * offset.
 */
अटल काष्ठा btrfs_मुक्त_space *
tree_search_offset(काष्ठा btrfs_मुक्त_space_ctl *ctl,
		   u64 offset, पूर्णांक biपंचांगap_only, पूर्णांक fuzzy)
अणु
	काष्ठा rb_node *n = ctl->मुक्त_space_offset.rb_node;
	काष्ठा btrfs_मुक्त_space *entry, *prev = शून्य;

	/* find entry that is बंदst to the 'offset' */
	जबतक (1) अणु
		अगर (!n) अणु
			entry = शून्य;
			अवरोध;
		पूर्ण

		entry = rb_entry(n, काष्ठा btrfs_मुक्त_space, offset_index);
		prev = entry;

		अगर (offset < entry->offset)
			n = n->rb_left;
		अन्यथा अगर (offset > entry->offset)
			n = n->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (biपंचांगap_only) अणु
		अगर (!entry)
			वापस शून्य;
		अगर (entry->biपंचांगap)
			वापस entry;

		/*
		 * biपंचांगap entry and extent entry may share same offset,
		 * in that हाल, biपंचांगap entry comes after extent entry.
		 */
		n = rb_next(n);
		अगर (!n)
			वापस शून्य;
		entry = rb_entry(n, काष्ठा btrfs_मुक्त_space, offset_index);
		अगर (entry->offset != offset)
			वापस शून्य;

		WARN_ON(!entry->biपंचांगap);
		वापस entry;
	पूर्ण अन्यथा अगर (entry) अणु
		अगर (entry->biपंचांगap) अणु
			/*
			 * अगर previous extent entry covers the offset,
			 * we should वापस it instead of the biपंचांगap entry
			 */
			n = rb_prev(&entry->offset_index);
			अगर (n) अणु
				prev = rb_entry(n, काष्ठा btrfs_मुक्त_space,
						offset_index);
				अगर (!prev->biपंचांगap &&
				    prev->offset + prev->bytes > offset)
					entry = prev;
			पूर्ण
		पूर्ण
		वापस entry;
	पूर्ण

	अगर (!prev)
		वापस शून्य;

	/* find last entry beक्रमe the 'offset' */
	entry = prev;
	अगर (entry->offset > offset) अणु
		n = rb_prev(&entry->offset_index);
		अगर (n) अणु
			entry = rb_entry(n, काष्ठा btrfs_मुक्त_space,
					offset_index);
			ASSERT(entry->offset <= offset);
		पूर्ण अन्यथा अणु
			अगर (fuzzy)
				वापस entry;
			अन्यथा
				वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (entry->biपंचांगap) अणु
		n = rb_prev(&entry->offset_index);
		अगर (n) अणु
			prev = rb_entry(n, काष्ठा btrfs_मुक्त_space,
					offset_index);
			अगर (!prev->biपंचांगap &&
			    prev->offset + prev->bytes > offset)
				वापस prev;
		पूर्ण
		अगर (entry->offset + BITS_PER_BITMAP * ctl->unit > offset)
			वापस entry;
	पूर्ण अन्यथा अगर (entry->offset + entry->bytes > offset)
		वापस entry;

	अगर (!fuzzy)
		वापस शून्य;

	जबतक (1) अणु
		अगर (entry->biपंचांगap) अणु
			अगर (entry->offset + BITS_PER_BITMAP *
			    ctl->unit > offset)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (entry->offset + entry->bytes > offset)
				अवरोध;
		पूर्ण

		n = rb_next(&entry->offset_index);
		अगर (!n)
			वापस शून्य;
		entry = rb_entry(n, काष्ठा btrfs_मुक्त_space, offset_index);
	पूर्ण
	वापस entry;
पूर्ण

अटल अंतरभूत व्योम
__unlink_मुक्त_space(काष्ठा btrfs_मुक्त_space_ctl *ctl,
		    काष्ठा btrfs_मुक्त_space *info)
अणु
	rb_erase(&info->offset_index, &ctl->मुक्त_space_offset);
	ctl->मुक्त_extents--;

	अगर (!info->biपंचांगap && !btrfs_मुक्त_space_trimmed(info)) अणु
		ctl->discardable_extents[BTRFS_STAT_CURR]--;
		ctl->discardable_bytes[BTRFS_STAT_CURR] -= info->bytes;
	पूर्ण
पूर्ण

अटल व्योम unlink_मुक्त_space(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			      काष्ठा btrfs_मुक्त_space *info)
अणु
	__unlink_मुक्त_space(ctl, info);
	ctl->मुक्त_space -= info->bytes;
पूर्ण

अटल पूर्णांक link_मुक्त_space(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			   काष्ठा btrfs_मुक्त_space *info)
अणु
	पूर्णांक ret = 0;

	ASSERT(info->bytes || info->biपंचांगap);
	ret = tree_insert_offset(&ctl->मुक्त_space_offset, info->offset,
				 &info->offset_index, (info->biपंचांगap != शून्य));
	अगर (ret)
		वापस ret;

	अगर (!info->biपंचांगap && !btrfs_मुक्त_space_trimmed(info)) अणु
		ctl->discardable_extents[BTRFS_STAT_CURR]++;
		ctl->discardable_bytes[BTRFS_STAT_CURR] += info->bytes;
	पूर्ण

	ctl->मुक्त_space += info->bytes;
	ctl->मुक्त_extents++;
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम __biपंचांगap_clear_bits(काष्ठा btrfs_मुक्त_space_ctl *ctl,
				       काष्ठा btrfs_मुक्त_space *info,
				       u64 offset, u64 bytes)
अणु
	अचिन्हित दीर्घ start, count, end;
	पूर्णांक extent_delta = -1;

	start = offset_to_bit(info->offset, ctl->unit, offset);
	count = bytes_to_bits(bytes, ctl->unit);
	end = start + count;
	ASSERT(end <= BITS_PER_BITMAP);

	biपंचांगap_clear(info->biपंचांगap, start, count);

	info->bytes -= bytes;
	अगर (info->max_extent_size > ctl->unit)
		info->max_extent_size = 0;

	अगर (start && test_bit(start - 1, info->biपंचांगap))
		extent_delta++;

	अगर (end < BITS_PER_BITMAP && test_bit(end, info->biपंचांगap))
		extent_delta++;

	info->biपंचांगap_extents += extent_delta;
	अगर (!btrfs_मुक्त_space_trimmed(info)) अणु
		ctl->discardable_extents[BTRFS_STAT_CURR] += extent_delta;
		ctl->discardable_bytes[BTRFS_STAT_CURR] -= bytes;
	पूर्ण
पूर्ण

अटल व्योम biपंचांगap_clear_bits(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			      काष्ठा btrfs_मुक्त_space *info, u64 offset,
			      u64 bytes)
अणु
	__biपंचांगap_clear_bits(ctl, info, offset, bytes);
	ctl->मुक्त_space -= bytes;
पूर्ण

अटल व्योम biपंचांगap_set_bits(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			    काष्ठा btrfs_मुक्त_space *info, u64 offset,
			    u64 bytes)
अणु
	अचिन्हित दीर्घ start, count, end;
	पूर्णांक extent_delta = 1;

	start = offset_to_bit(info->offset, ctl->unit, offset);
	count = bytes_to_bits(bytes, ctl->unit);
	end = start + count;
	ASSERT(end <= BITS_PER_BITMAP);

	biपंचांगap_set(info->biपंचांगap, start, count);

	info->bytes += bytes;
	ctl->मुक्त_space += bytes;

	अगर (start && test_bit(start - 1, info->biपंचांगap))
		extent_delta--;

	अगर (end < BITS_PER_BITMAP && test_bit(end, info->biपंचांगap))
		extent_delta--;

	info->biपंचांगap_extents += extent_delta;
	अगर (!btrfs_मुक्त_space_trimmed(info)) अणु
		ctl->discardable_extents[BTRFS_STAT_CURR] += extent_delta;
		ctl->discardable_bytes[BTRFS_STAT_CURR] += bytes;
	पूर्ण
पूर्ण

/*
 * If we can not find suitable extent, we will use bytes to record
 * the size of the max extent.
 */
अटल पूर्णांक search_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			 काष्ठा btrfs_मुक्त_space *biपंचांगap_info, u64 *offset,
			 u64 *bytes, bool क्रम_alloc)
अणु
	अचिन्हित दीर्घ found_bits = 0;
	अचिन्हित दीर्घ max_bits = 0;
	अचिन्हित दीर्घ bits, i;
	अचिन्हित दीर्घ next_zero;
	अचिन्हित दीर्घ extent_bits;

	/*
	 * Skip searching the biपंचांगap अगर we करोn't have a contiguous section that
	 * is large enough क्रम this allocation.
	 */
	अगर (क्रम_alloc &&
	    biपंचांगap_info->max_extent_size &&
	    biपंचांगap_info->max_extent_size < *bytes) अणु
		*bytes = biपंचांगap_info->max_extent_size;
		वापस -1;
	पूर्ण

	i = offset_to_bit(biपंचांगap_info->offset, ctl->unit,
			  max_t(u64, *offset, biपंचांगap_info->offset));
	bits = bytes_to_bits(*bytes, ctl->unit);

	क्रम_each_set_bit_from(i, biपंचांगap_info->biपंचांगap, BITS_PER_BITMAP) अणु
		अगर (क्रम_alloc && bits == 1) अणु
			found_bits = 1;
			अवरोध;
		पूर्ण
		next_zero = find_next_zero_bit(biपंचांगap_info->biपंचांगap,
					       BITS_PER_BITMAP, i);
		extent_bits = next_zero - i;
		अगर (extent_bits >= bits) अणु
			found_bits = extent_bits;
			अवरोध;
		पूर्ण अन्यथा अगर (extent_bits > max_bits) अणु
			max_bits = extent_bits;
		पूर्ण
		i = next_zero;
	पूर्ण

	अगर (found_bits) अणु
		*offset = (u64)(i * ctl->unit) + biपंचांगap_info->offset;
		*bytes = (u64)(found_bits) * ctl->unit;
		वापस 0;
	पूर्ण

	*bytes = (u64)(max_bits) * ctl->unit;
	biपंचांगap_info->max_extent_size = *bytes;
	वापस -1;
पूर्ण

अटल अंतरभूत u64 get_max_extent_size(काष्ठा btrfs_मुक्त_space *entry)
अणु
	अगर (entry->biपंचांगap)
		वापस entry->max_extent_size;
	वापस entry->bytes;
पूर्ण

/* Cache the size of the max extent in bytes */
अटल काष्ठा btrfs_मुक्त_space *
find_मुक्त_space(काष्ठा btrfs_मुक्त_space_ctl *ctl, u64 *offset, u64 *bytes,
		अचिन्हित दीर्घ align, u64 *max_extent_size)
अणु
	काष्ठा btrfs_मुक्त_space *entry;
	काष्ठा rb_node *node;
	u64 पंचांगp;
	u64 align_off;
	पूर्णांक ret;

	अगर (!ctl->मुक्त_space_offset.rb_node)
		जाओ out;

	entry = tree_search_offset(ctl, offset_to_biपंचांगap(ctl, *offset), 0, 1);
	अगर (!entry)
		जाओ out;

	क्रम (node = &entry->offset_index; node; node = rb_next(node)) अणु
		entry = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);
		अगर (entry->bytes < *bytes) अणु
			*max_extent_size = max(get_max_extent_size(entry),
					       *max_extent_size);
			जारी;
		पूर्ण

		/* make sure the space वापसed is big enough
		 * to match our requested alignment
		 */
		अगर (*bytes >= align) अणु
			पंचांगp = entry->offset - ctl->start + align - 1;
			पंचांगp = भाग64_u64(पंचांगp, align);
			पंचांगp = पंचांगp * align + ctl->start;
			align_off = पंचांगp - entry->offset;
		पूर्ण अन्यथा अणु
			align_off = 0;
			पंचांगp = entry->offset;
		पूर्ण

		अगर (entry->bytes < *bytes + align_off) अणु
			*max_extent_size = max(get_max_extent_size(entry),
					       *max_extent_size);
			जारी;
		पूर्ण

		अगर (entry->biपंचांगap) अणु
			u64 size = *bytes;

			ret = search_biपंचांगap(ctl, entry, &पंचांगp, &size, true);
			अगर (!ret) अणु
				*offset = पंचांगp;
				*bytes = size;
				वापस entry;
			पूर्ण अन्यथा अणु
				*max_extent_size =
					max(get_max_extent_size(entry),
					    *max_extent_size);
			पूर्ण
			जारी;
		पूर्ण

		*offset = पंचांगp;
		*bytes = entry->bytes - align_off;
		वापस entry;
	पूर्ण
out:
	वापस शून्य;
पूर्ण

अटल व्योम add_new_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			   काष्ठा btrfs_मुक्त_space *info, u64 offset)
अणु
	info->offset = offset_to_biपंचांगap(ctl, offset);
	info->bytes = 0;
	info->biपंचांगap_extents = 0;
	INIT_LIST_HEAD(&info->list);
	link_मुक्त_space(ctl, info);
	ctl->total_biपंचांगaps++;
	recalculate_thresholds(ctl);
पूर्ण

अटल व्योम मुक्त_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			काष्ठा btrfs_मुक्त_space *biपंचांगap_info)
अणु
	/*
	 * Normally when this is called, the biपंचांगap is completely empty. However,
	 * अगर we are blowing up the मुक्त space cache क्रम one reason or another
	 * via __btrfs_हटाओ_मुक्त_space_cache(), then it may not be मुक्तd and
	 * we may leave stats on the table.
	 */
	अगर (biपंचांगap_info->bytes && !btrfs_मुक्त_space_trimmed(biपंचांगap_info)) अणु
		ctl->discardable_extents[BTRFS_STAT_CURR] -=
			biपंचांगap_info->biपंचांगap_extents;
		ctl->discardable_bytes[BTRFS_STAT_CURR] -= biपंचांगap_info->bytes;

	पूर्ण
	unlink_मुक्त_space(ctl, biपंचांगap_info);
	kmem_cache_मुक्त(btrfs_मुक्त_space_biपंचांगap_cachep, biपंचांगap_info->biपंचांगap);
	kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, biपंचांगap_info);
	ctl->total_biपंचांगaps--;
	recalculate_thresholds(ctl);
पूर्ण

अटल noअंतरभूत पूर्णांक हटाओ_from_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			      काष्ठा btrfs_मुक्त_space *biपंचांगap_info,
			      u64 *offset, u64 *bytes)
अणु
	u64 end;
	u64 search_start, search_bytes;
	पूर्णांक ret;

again:
	end = biपंचांगap_info->offset + (u64)(BITS_PER_BITMAP * ctl->unit) - 1;

	/*
	 * We need to search क्रम bits in this biपंचांगap.  We could only cover some
	 * of the extent in this biपंचांगap thanks to how we add space, so we need
	 * to search क्रम as much as it as we can and clear that amount, and then
	 * go searching क्रम the next bit.
	 */
	search_start = *offset;
	search_bytes = ctl->unit;
	search_bytes = min(search_bytes, end - search_start + 1);
	ret = search_biपंचांगap(ctl, biपंचांगap_info, &search_start, &search_bytes,
			    false);
	अगर (ret < 0 || search_start != *offset)
		वापस -EINVAL;

	/* We may have found more bits than what we need */
	search_bytes = min(search_bytes, *bytes);

	/* Cannot clear past the end of the biपंचांगap */
	search_bytes = min(search_bytes, end - search_start + 1);

	biपंचांगap_clear_bits(ctl, biपंचांगap_info, search_start, search_bytes);
	*offset += search_bytes;
	*bytes -= search_bytes;

	अगर (*bytes) अणु
		काष्ठा rb_node *next = rb_next(&biपंचांगap_info->offset_index);
		अगर (!biपंचांगap_info->bytes)
			मुक्त_biपंचांगap(ctl, biपंचांगap_info);

		/*
		 * no entry after this biपंचांगap, but we still have bytes to
		 * हटाओ, so something has gone wrong.
		 */
		अगर (!next)
			वापस -EINVAL;

		biपंचांगap_info = rb_entry(next, काष्ठा btrfs_मुक्त_space,
				       offset_index);

		/*
		 * अगर the next entry isn't a biपंचांगap we need to वापस to let the
		 * extent stuff करो its work.
		 */
		अगर (!biपंचांगap_info->biपंचांगap)
			वापस -EAGAIN;

		/*
		 * Ok the next item is a biपंचांगap, but it may not actually hold
		 * the inक्रमmation क्रम the rest of this मुक्त space stuff, so
		 * look क्रम it, and अगर we करोn't find it वापस so we can try
		 * everything over again.
		 */
		search_start = *offset;
		search_bytes = ctl->unit;
		ret = search_biपंचांगap(ctl, biपंचांगap_info, &search_start,
				    &search_bytes, false);
		अगर (ret < 0 || search_start != *offset)
			वापस -EAGAIN;

		जाओ again;
	पूर्ण अन्यथा अगर (!biपंचांगap_info->bytes)
		मुक्त_biपंचांगap(ctl, biपंचांगap_info);

	वापस 0;
पूर्ण

अटल u64 add_bytes_to_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			       काष्ठा btrfs_मुक्त_space *info, u64 offset,
			       u64 bytes, क्रमागत btrfs_trim_state trim_state)
अणु
	u64 bytes_to_set = 0;
	u64 end;

	/*
	 * This is a tradeoff to make biपंचांगap trim state minimal.  We mark the
	 * whole biपंचांगap untrimmed अगर at any poपूर्णांक we add untrimmed regions.
	 */
	अगर (trim_state == BTRFS_TRIM_STATE_UNTRIMMED) अणु
		अगर (btrfs_मुक्त_space_trimmed(info)) अणु
			ctl->discardable_extents[BTRFS_STAT_CURR] +=
				info->biपंचांगap_extents;
			ctl->discardable_bytes[BTRFS_STAT_CURR] += info->bytes;
		पूर्ण
		info->trim_state = BTRFS_TRIM_STATE_UNTRIMMED;
	पूर्ण

	end = info->offset + (u64)(BITS_PER_BITMAP * ctl->unit);

	bytes_to_set = min(end - offset, bytes);

	biपंचांगap_set_bits(ctl, info, offset, bytes_to_set);

	/*
	 * We set some bytes, we have no idea what the max extent size is
	 * anymore.
	 */
	info->max_extent_size = 0;

	वापस bytes_to_set;

पूर्ण

अटल bool use_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
		      काष्ठा btrfs_मुक्त_space *info)
अणु
	काष्ठा btrfs_block_group *block_group = ctl->निजी;
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	bool क्रमced = false;

#अगर_घोषित CONFIG_BTRFS_DEBUG
	अगर (btrfs_should_fragment_मुक्त_space(block_group))
		क्रमced = true;
#पूर्ण_अगर

	/* This is a way to reclaim large regions from the biपंचांगaps. */
	अगर (!क्रमced && info->bytes >= FORCE_EXTENT_THRESHOLD)
		वापस false;

	/*
	 * If we are below the extents threshold then we can add this as an
	 * extent, and करोn't have to deal with the biपंचांगap
	 */
	अगर (!क्रमced && ctl->मुक्त_extents < ctl->extents_thresh) अणु
		/*
		 * If this block group has some small extents we करोn't want to
		 * use up all of our मुक्त slots in the cache with them, we want
		 * to reserve them to larger extents, however अगर we have plenty
		 * of cache left then go ahead an dadd them, no sense in adding
		 * the overhead of a biपंचांगap अगर we करोn't have to.
		 */
		अगर (info->bytes <= fs_info->sectorsize * 8) अणु
			अगर (ctl->मुक्त_extents * 3 <= ctl->extents_thresh)
				वापस false;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
	पूर्ण

	/*
	 * The original block groups from mkfs can be really small, like 8
	 * megabytes, so करोn't bother with a biपंचांगap क्रम those entries.  However
	 * some block groups can be smaller than what a biपंचांगap would cover but
	 * are still large enough that they could overflow the 32k memory limit,
	 * so allow those block groups to still be allowed to have a biपंचांगap
	 * entry.
	 */
	अगर (((BITS_PER_BITMAP * ctl->unit) >> 1) > block_group->length)
		वापस false;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा btrfs_मुक्त_space_op मुक्त_space_op = अणु
	.use_biपंचांगap		= use_biपंचांगap,
पूर्ण;

अटल पूर्णांक insert_पूर्णांकo_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			      काष्ठा btrfs_मुक्त_space *info)
अणु
	काष्ठा btrfs_मुक्त_space *biपंचांगap_info;
	काष्ठा btrfs_block_group *block_group = शून्य;
	पूर्णांक added = 0;
	u64 bytes, offset, bytes_added;
	क्रमागत btrfs_trim_state trim_state;
	पूर्णांक ret;

	bytes = info->bytes;
	offset = info->offset;
	trim_state = info->trim_state;

	अगर (!ctl->op->use_biपंचांगap(ctl, info))
		वापस 0;

	अगर (ctl->op == &मुक्त_space_op)
		block_group = ctl->निजी;
again:
	/*
	 * Since we link biपंचांगaps right पूर्णांकo the cluster we need to see अगर we
	 * have a cluster here, and अगर so and it has our biपंचांगap we need to add
	 * the मुक्त space to that biपंचांगap.
	 */
	अगर (block_group && !list_empty(&block_group->cluster_list)) अणु
		काष्ठा btrfs_मुक्त_cluster *cluster;
		काष्ठा rb_node *node;
		काष्ठा btrfs_मुक्त_space *entry;

		cluster = list_entry(block_group->cluster_list.next,
				     काष्ठा btrfs_मुक्त_cluster,
				     block_group_list);
		spin_lock(&cluster->lock);
		node = rb_first(&cluster->root);
		अगर (!node) अणु
			spin_unlock(&cluster->lock);
			जाओ no_cluster_biपंचांगap;
		पूर्ण

		entry = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);
		अगर (!entry->biपंचांगap) अणु
			spin_unlock(&cluster->lock);
			जाओ no_cluster_biपंचांगap;
		पूर्ण

		अगर (entry->offset == offset_to_biपंचांगap(ctl, offset)) अणु
			bytes_added = add_bytes_to_biपंचांगap(ctl, entry, offset,
							  bytes, trim_state);
			bytes -= bytes_added;
			offset += bytes_added;
		पूर्ण
		spin_unlock(&cluster->lock);
		अगर (!bytes) अणु
			ret = 1;
			जाओ out;
		पूर्ण
	पूर्ण

no_cluster_biपंचांगap:
	biपंचांगap_info = tree_search_offset(ctl, offset_to_biपंचांगap(ctl, offset),
					 1, 0);
	अगर (!biपंचांगap_info) अणु
		ASSERT(added == 0);
		जाओ new_biपंचांगap;
	पूर्ण

	bytes_added = add_bytes_to_biपंचांगap(ctl, biपंचांगap_info, offset, bytes,
					  trim_state);
	bytes -= bytes_added;
	offset += bytes_added;
	added = 0;

	अगर (!bytes) अणु
		ret = 1;
		जाओ out;
	पूर्ण अन्यथा
		जाओ again;

new_biपंचांगap:
	अगर (info && info->biपंचांगap) अणु
		add_new_biपंचांगap(ctl, info, offset);
		added = 1;
		info = शून्य;
		जाओ again;
	पूर्ण अन्यथा अणु
		spin_unlock(&ctl->tree_lock);

		/* no pre-allocated info, allocate a new one */
		अगर (!info) अणु
			info = kmem_cache_zalloc(btrfs_मुक्त_space_cachep,
						 GFP_NOFS);
			अगर (!info) अणु
				spin_lock(&ctl->tree_lock);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण

		/* allocate the biपंचांगap */
		info->biपंचांगap = kmem_cache_zalloc(btrfs_मुक्त_space_biपंचांगap_cachep,
						 GFP_NOFS);
		info->trim_state = BTRFS_TRIM_STATE_TRIMMED;
		spin_lock(&ctl->tree_lock);
		अगर (!info->biपंचांगap) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		जाओ again;
	पूर्ण

out:
	अगर (info) अणु
		अगर (info->biपंचांगap)
			kmem_cache_मुक्त(btrfs_मुक्त_space_biपंचांगap_cachep,
					info->biपंचांगap);
		kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, info);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Free space merging rules:
 *  1) Merge trimmed areas together
 *  2) Let untrimmed areas coalesce with trimmed areas
 *  3) Always pull neighboring regions from biपंचांगaps
 *
 * The above rules are क्रम when we merge मुक्त space based on btrfs_trim_state.
 * Rules 2 and 3 are subtle because they are suboptimal, but are करोne क्रम the
 * same reason: to promote larger extent regions which makes lअगरe easier क्रम
 * find_मुक्त_extent().  Rule 2 enables coalescing based on the common path
 * being वापसing मुक्त space from btrfs_finish_extent_commit().  So when मुक्त
 * space is trimmed, it will prevent aggregating trimmed new region and
 * untrimmed regions in the rb_tree.  Rule 3 is purely to obtain larger extents
 * and provide find_मुक्त_extent() with the largest extents possible hoping क्रम
 * the reuse path.
 */
अटल bool try_merge_मुक्त_space(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			  काष्ठा btrfs_मुक्त_space *info, bool update_stat)
अणु
	काष्ठा btrfs_मुक्त_space *left_info = शून्य;
	काष्ठा btrfs_मुक्त_space *right_info;
	bool merged = false;
	u64 offset = info->offset;
	u64 bytes = info->bytes;
	स्थिर bool is_trimmed = btrfs_मुक्त_space_trimmed(info);

	/*
	 * first we want to see अगर there is मुक्त space adjacent to the range we
	 * are adding, अगर there is हटाओ that काष्ठा and add a new one to
	 * cover the entire range
	 */
	right_info = tree_search_offset(ctl, offset + bytes, 0, 0);
	अगर (right_info && rb_prev(&right_info->offset_index))
		left_info = rb_entry(rb_prev(&right_info->offset_index),
				     काष्ठा btrfs_मुक्त_space, offset_index);
	अन्यथा अगर (!right_info)
		left_info = tree_search_offset(ctl, offset - 1, 0, 0);

	/* See try_merge_मुक्त_space() comment. */
	अगर (right_info && !right_info->biपंचांगap &&
	    (!is_trimmed || btrfs_मुक्त_space_trimmed(right_info))) अणु
		अगर (update_stat)
			unlink_मुक्त_space(ctl, right_info);
		अन्यथा
			__unlink_मुक्त_space(ctl, right_info);
		info->bytes += right_info->bytes;
		kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, right_info);
		merged = true;
	पूर्ण

	/* See try_merge_मुक्त_space() comment. */
	अगर (left_info && !left_info->biपंचांगap &&
	    left_info->offset + left_info->bytes == offset &&
	    (!is_trimmed || btrfs_मुक्त_space_trimmed(left_info))) अणु
		अगर (update_stat)
			unlink_मुक्त_space(ctl, left_info);
		अन्यथा
			__unlink_मुक्त_space(ctl, left_info);
		info->offset = left_info->offset;
		info->bytes += left_info->bytes;
		kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, left_info);
		merged = true;
	पूर्ण

	वापस merged;
पूर्ण

अटल bool steal_from_biपंचांगap_to_end(काष्ठा btrfs_मुक्त_space_ctl *ctl,
				     काष्ठा btrfs_मुक्त_space *info,
				     bool update_stat)
अणु
	काष्ठा btrfs_मुक्त_space *biपंचांगap;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ j;
	स्थिर u64 end = info->offset + info->bytes;
	स्थिर u64 biपंचांगap_offset = offset_to_biपंचांगap(ctl, end);
	u64 bytes;

	biपंचांगap = tree_search_offset(ctl, biपंचांगap_offset, 1, 0);
	अगर (!biपंचांगap)
		वापस false;

	i = offset_to_bit(biपंचांगap->offset, ctl->unit, end);
	j = find_next_zero_bit(biपंचांगap->biपंचांगap, BITS_PER_BITMAP, i);
	अगर (j == i)
		वापस false;
	bytes = (j - i) * ctl->unit;
	info->bytes += bytes;

	/* See try_merge_मुक्त_space() comment. */
	अगर (!btrfs_मुक्त_space_trimmed(biपंचांगap))
		info->trim_state = BTRFS_TRIM_STATE_UNTRIMMED;

	अगर (update_stat)
		biपंचांगap_clear_bits(ctl, biपंचांगap, end, bytes);
	अन्यथा
		__biपंचांगap_clear_bits(ctl, biपंचांगap, end, bytes);

	अगर (!biपंचांगap->bytes)
		मुक्त_biपंचांगap(ctl, biपंचांगap);

	वापस true;
पूर्ण

अटल bool steal_from_biपंचांगap_to_front(काष्ठा btrfs_मुक्त_space_ctl *ctl,
				       काष्ठा btrfs_मुक्त_space *info,
				       bool update_stat)
अणु
	काष्ठा btrfs_मुक्त_space *biपंचांगap;
	u64 biपंचांगap_offset;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ j;
	अचिन्हित दीर्घ prev_j;
	u64 bytes;

	biपंचांगap_offset = offset_to_biपंचांगap(ctl, info->offset);
	/* If we're on a boundary, try the previous logical biपंचांगap. */
	अगर (biपंचांगap_offset == info->offset) अणु
		अगर (info->offset == 0)
			वापस false;
		biपंचांगap_offset = offset_to_biपंचांगap(ctl, info->offset - 1);
	पूर्ण

	biपंचांगap = tree_search_offset(ctl, biपंचांगap_offset, 1, 0);
	अगर (!biपंचांगap)
		वापस false;

	i = offset_to_bit(biपंचांगap->offset, ctl->unit, info->offset) - 1;
	j = 0;
	prev_j = (अचिन्हित दीर्घ)-1;
	क्रम_each_clear_bit_from(j, biपंचांगap->biपंचांगap, BITS_PER_BITMAP) अणु
		अगर (j > i)
			अवरोध;
		prev_j = j;
	पूर्ण
	अगर (prev_j == i)
		वापस false;

	अगर (prev_j == (अचिन्हित दीर्घ)-1)
		bytes = (i + 1) * ctl->unit;
	अन्यथा
		bytes = (i - prev_j) * ctl->unit;

	info->offset -= bytes;
	info->bytes += bytes;

	/* See try_merge_मुक्त_space() comment. */
	अगर (!btrfs_मुक्त_space_trimmed(biपंचांगap))
		info->trim_state = BTRFS_TRIM_STATE_UNTRIMMED;

	अगर (update_stat)
		biपंचांगap_clear_bits(ctl, biपंचांगap, info->offset, bytes);
	अन्यथा
		__biपंचांगap_clear_bits(ctl, biपंचांगap, info->offset, bytes);

	अगर (!biपंचांगap->bytes)
		मुक्त_biपंचांगap(ctl, biपंचांगap);

	वापस true;
पूर्ण

/*
 * We prefer always to allocate from extent entries, both क्रम clustered and
 * non-clustered allocation requests. So when attempting to add a new extent
 * entry, try to see अगर there's adjacent मुक्त space in biपंचांगap entries, and अगर
 * there is, migrate that space from the biपंचांगaps to the extent.
 * Like this we get better chances of satisfying space allocation requests
 * because we attempt to satisfy them based on a single cache entry, and never
 * on 2 or more entries - even अगर the entries represent a contiguous मुक्त space
 * region (e.g. 1 extent entry + 1 biपंचांगap entry starting where the extent entry
 * ends).
 */
अटल व्योम steal_from_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			      काष्ठा btrfs_मुक्त_space *info,
			      bool update_stat)
अणु
	/*
	 * Only work with disconnected entries, as we can change their offset,
	 * and must be extent entries.
	 */
	ASSERT(!info->biपंचांगap);
	ASSERT(RB_EMPTY_NODE(&info->offset_index));

	अगर (ctl->total_biपंचांगaps > 0) अणु
		bool stole_end;
		bool stole_front = false;

		stole_end = steal_from_biपंचांगap_to_end(ctl, info, update_stat);
		अगर (ctl->total_biपंचांगaps > 0)
			stole_front = steal_from_biपंचांगap_to_front(ctl, info,
								 update_stat);

		अगर (stole_end || stole_front)
			try_merge_मुक्त_space(ctl, info, update_stat);
	पूर्ण
पूर्ण

पूर्णांक __btrfs_add_मुक्त_space(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_मुक्त_space_ctl *ctl,
			   u64 offset, u64 bytes,
			   क्रमागत btrfs_trim_state trim_state)
अणु
	काष्ठा btrfs_block_group *block_group = ctl->निजी;
	काष्ठा btrfs_मुक्त_space *info;
	पूर्णांक ret = 0;
	u64 filter_bytes = bytes;

	ASSERT(!btrfs_is_zoned(fs_info));

	info = kmem_cache_zalloc(btrfs_मुक्त_space_cachep, GFP_NOFS);
	अगर (!info)
		वापस -ENOMEM;

	info->offset = offset;
	info->bytes = bytes;
	info->trim_state = trim_state;
	RB_CLEAR_NODE(&info->offset_index);

	spin_lock(&ctl->tree_lock);

	अगर (try_merge_मुक्त_space(ctl, info, true))
		जाओ link;

	/*
	 * There was no extent directly to the left or right of this new
	 * extent then we know we're going to have to allocate a new extent, so
	 * beक्रमe we करो that see अगर we need to drop this पूर्णांकo a biपंचांगap
	 */
	ret = insert_पूर्णांकo_biपंचांगap(ctl, info);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (ret) अणु
		ret = 0;
		जाओ out;
	पूर्ण
link:
	/*
	 * Only steal मुक्त space from adjacent biपंचांगaps अगर we're sure we're not
	 * going to add the new मुक्त space to existing biपंचांगap entries - because
	 * that would mean unnecessary work that would be reverted. Thereक्रमe
	 * attempt to steal space from biपंचांगaps अगर we're adding an extent entry.
	 */
	steal_from_biपंचांगap(ctl, info, true);

	filter_bytes = max(filter_bytes, info->bytes);

	ret = link_मुक्त_space(ctl, info);
	अगर (ret)
		kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, info);
out:
	btrfs_discard_update_discardable(block_group);
	spin_unlock(&ctl->tree_lock);

	अगर (ret) अणु
		btrfs_crit(fs_info, "unable to add free space :%d", ret);
		ASSERT(ret != -EEXIST);
	पूर्ण

	अगर (trim_state != BTRFS_TRIM_STATE_TRIMMED) अणु
		btrfs_discard_check_filter(block_group, filter_bytes);
		btrfs_discard_queue_work(&fs_info->discard_ctl, block_group);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __btrfs_add_मुक्त_space_zoned(काष्ठा btrfs_block_group *block_group,
					u64 bytenr, u64 size, bool used)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	u64 offset = bytenr - block_group->start;
	u64 to_मुक्त, to_unusable;

	spin_lock(&ctl->tree_lock);
	अगर (!used)
		to_मुक्त = size;
	अन्यथा अगर (offset >= block_group->alloc_offset)
		to_मुक्त = size;
	अन्यथा अगर (offset + size <= block_group->alloc_offset)
		to_मुक्त = 0;
	अन्यथा
		to_मुक्त = offset + size - block_group->alloc_offset;
	to_unusable = size - to_मुक्त;

	ctl->मुक्त_space += to_मुक्त;
	/*
	 * If the block group is पढ़ो-only, we should account मुक्तd space पूर्णांकo
	 * bytes_पढ़ोonly.
	 */
	अगर (!block_group->ro)
		block_group->zone_unusable += to_unusable;
	spin_unlock(&ctl->tree_lock);
	अगर (!used) अणु
		spin_lock(&block_group->lock);
		block_group->alloc_offset -= size;
		spin_unlock(&block_group->lock);
	पूर्ण

	/* All the region is now unusable. Mark it as unused and reclaim */
	अगर (block_group->zone_unusable == block_group->length) अणु
		btrfs_mark_bg_unused(block_group);
	पूर्ण अन्यथा अगर (block_group->zone_unusable >=
		   भाग_factor_fine(block_group->length,
				   fs_info->bg_reclaim_threshold)) अणु
		btrfs_mark_bg_to_reclaim(block_group);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक btrfs_add_मुक्त_space(काष्ठा btrfs_block_group *block_group,
			 u64 bytenr, u64 size)
अणु
	क्रमागत btrfs_trim_state trim_state = BTRFS_TRIM_STATE_UNTRIMMED;

	अगर (btrfs_is_zoned(block_group->fs_info))
		वापस __btrfs_add_मुक्त_space_zoned(block_group, bytenr, size,
						    true);

	अगर (btrfs_test_opt(block_group->fs_info, DISCARD_SYNC))
		trim_state = BTRFS_TRIM_STATE_TRIMMED;

	वापस __btrfs_add_मुक्त_space(block_group->fs_info,
				      block_group->मुक्त_space_ctl,
				      bytenr, size, trim_state);
पूर्ण

पूर्णांक btrfs_add_मुक्त_space_unused(काष्ठा btrfs_block_group *block_group,
				u64 bytenr, u64 size)
अणु
	अगर (btrfs_is_zoned(block_group->fs_info))
		वापस __btrfs_add_मुक्त_space_zoned(block_group, bytenr, size,
						    false);

	वापस btrfs_add_मुक्त_space(block_group, bytenr, size);
पूर्ण

/*
 * This is a subtle distinction because when adding मुक्त space back in general,
 * we want it to be added as untrimmed क्रम async. But in the हाल where we add
 * it on loading of a block group, we want to consider it trimmed.
 */
पूर्णांक btrfs_add_मुक्त_space_async_trimmed(काष्ठा btrfs_block_group *block_group,
				       u64 bytenr, u64 size)
अणु
	क्रमागत btrfs_trim_state trim_state = BTRFS_TRIM_STATE_UNTRIMMED;

	अगर (btrfs_is_zoned(block_group->fs_info))
		वापस __btrfs_add_मुक्त_space_zoned(block_group, bytenr, size,
						    true);

	अगर (btrfs_test_opt(block_group->fs_info, DISCARD_SYNC) ||
	    btrfs_test_opt(block_group->fs_info, DISCARD_ASYNC))
		trim_state = BTRFS_TRIM_STATE_TRIMMED;

	वापस __btrfs_add_मुक्त_space(block_group->fs_info,
				      block_group->मुक्त_space_ctl,
				      bytenr, size, trim_state);
पूर्ण

पूर्णांक btrfs_हटाओ_मुक्त_space(काष्ठा btrfs_block_group *block_group,
			    u64 offset, u64 bytes)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *info;
	पूर्णांक ret;
	bool re_search = false;

	अगर (btrfs_is_zoned(block_group->fs_info)) अणु
		/*
		 * This can happen with conventional zones when replaying log.
		 * Since the allocation info of tree-log nodes are not recorded
		 * to the extent-tree, calculate_alloc_poपूर्णांकer() failed to
		 * advance the allocation poपूर्णांकer after last allocated tree log
		 * node blocks.
		 *
		 * This function is called from
		 * btrfs_pin_extent_क्रम_log_replay() when replaying the log.
		 * Advance the poपूर्णांकer not to overग_लिखो the tree-log nodes.
		 */
		अगर (block_group->alloc_offset < offset + bytes)
			block_group->alloc_offset = offset + bytes;
		वापस 0;
	पूर्ण

	spin_lock(&ctl->tree_lock);

again:
	ret = 0;
	अगर (!bytes)
		जाओ out_lock;

	info = tree_search_offset(ctl, offset, 0, 0);
	अगर (!info) अणु
		/*
		 * oops didn't find an extent that matched the space we wanted
		 * to हटाओ, look क्रम a biपंचांगap instead
		 */
		info = tree_search_offset(ctl, offset_to_biपंचांगap(ctl, offset),
					  1, 0);
		अगर (!info) अणु
			/*
			 * If we found a partial bit of our मुक्त space in a
			 * biपंचांगap but then couldn't find the other part this may
			 * be a problem, so WARN about it.
			 */
			WARN_ON(re_search);
			जाओ out_lock;
		पूर्ण
	पूर्ण

	re_search = false;
	अगर (!info->biपंचांगap) अणु
		unlink_मुक्त_space(ctl, info);
		अगर (offset == info->offset) अणु
			u64 to_मुक्त = min(bytes, info->bytes);

			info->bytes -= to_मुक्त;
			info->offset += to_मुक्त;
			अगर (info->bytes) अणु
				ret = link_मुक्त_space(ctl, info);
				WARN_ON(ret);
			पूर्ण अन्यथा अणु
				kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, info);
			पूर्ण

			offset += to_मुक्त;
			bytes -= to_मुक्त;
			जाओ again;
		पूर्ण अन्यथा अणु
			u64 old_end = info->bytes + info->offset;

			info->bytes = offset - info->offset;
			ret = link_मुक्त_space(ctl, info);
			WARN_ON(ret);
			अगर (ret)
				जाओ out_lock;

			/* Not enough bytes in this entry to satisfy us */
			अगर (old_end < offset + bytes) अणु
				bytes -= old_end - offset;
				offset = old_end;
				जाओ again;
			पूर्ण अन्यथा अगर (old_end == offset + bytes) अणु
				/* all करोne */
				जाओ out_lock;
			पूर्ण
			spin_unlock(&ctl->tree_lock);

			ret = __btrfs_add_मुक्त_space(block_group->fs_info, ctl,
						     offset + bytes,
						     old_end - (offset + bytes),
						     info->trim_state);
			WARN_ON(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = हटाओ_from_biपंचांगap(ctl, info, &offset, &bytes);
	अगर (ret == -EAGAIN) अणु
		re_search = true;
		जाओ again;
	पूर्ण
out_lock:
	btrfs_discard_update_discardable(block_group);
	spin_unlock(&ctl->tree_lock);
out:
	वापस ret;
पूर्ण

व्योम btrfs_dump_मुक्त_space(काष्ठा btrfs_block_group *block_group,
			   u64 bytes)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *info;
	काष्ठा rb_node *n;
	पूर्णांक count = 0;

	/*
	 * Zoned btrfs करोes not use मुक्त space tree and cluster. Just prपूर्णांक
	 * out the मुक्त space after the allocation offset.
	 */
	अगर (btrfs_is_zoned(fs_info)) अणु
		btrfs_info(fs_info, "free space %llu",
			   block_group->length - block_group->alloc_offset);
		वापस;
	पूर्ण

	spin_lock(&ctl->tree_lock);
	क्रम (n = rb_first(&ctl->मुक्त_space_offset); n; n = rb_next(n)) अणु
		info = rb_entry(n, काष्ठा btrfs_मुक्त_space, offset_index);
		अगर (info->bytes >= bytes && !block_group->ro)
			count++;
		btrfs_crit(fs_info, "entry offset %llu, bytes %llu, bitmap %s",
			   info->offset, info->bytes,
		       (info->biपंचांगap) ? "yes" : "no");
	पूर्ण
	spin_unlock(&ctl->tree_lock);
	btrfs_info(fs_info, "block group has cluster?: %s",
	       list_empty(&block_group->cluster_list) ? "no" : "yes");
	btrfs_info(fs_info,
		   "%d blocks of free space at or bigger than bytes is", count);
पूर्ण

व्योम btrfs_init_मुक्त_space_ctl(काष्ठा btrfs_block_group *block_group,
			       काष्ठा btrfs_मुक्त_space_ctl *ctl)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;

	spin_lock_init(&ctl->tree_lock);
	ctl->unit = fs_info->sectorsize;
	ctl->start = block_group->start;
	ctl->निजी = block_group;
	ctl->op = &मुक्त_space_op;
	INIT_LIST_HEAD(&ctl->trimming_ranges);
	mutex_init(&ctl->cache_ग_लिखोout_mutex);

	/*
	 * we only want to have 32k of ram per block group क्रम keeping
	 * track of मुक्त space, and अगर we pass 1/2 of that we want to
	 * start converting things over to using biपंचांगaps
	 */
	ctl->extents_thresh = (SZ_32K / 2) / माप(काष्ठा btrfs_मुक्त_space);
पूर्ण

/*
 * क्रम a given cluster, put all of its extents back पूर्णांकo the मुक्त
 * space cache.  If the block group passed करोesn't match the block group
 * poपूर्णांकed to by the cluster, someone अन्यथा raced in and मुक्तd the
 * cluster alपढ़ोy.  In that हाल, we just वापस without changing anything
 */
अटल व्योम __btrfs_वापस_cluster_to_मुक्त_space(
			     काष्ठा btrfs_block_group *block_group,
			     काष्ठा btrfs_मुक्त_cluster *cluster)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *entry;
	काष्ठा rb_node *node;

	spin_lock(&cluster->lock);
	अगर (cluster->block_group != block_group) अणु
		spin_unlock(&cluster->lock);
		वापस;
	पूर्ण

	cluster->block_group = शून्य;
	cluster->winकरोw_start = 0;
	list_del_init(&cluster->block_group_list);

	node = rb_first(&cluster->root);
	जबतक (node) अणु
		bool biपंचांगap;

		entry = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);
		node = rb_next(&entry->offset_index);
		rb_erase(&entry->offset_index, &cluster->root);
		RB_CLEAR_NODE(&entry->offset_index);

		biपंचांगap = (entry->biपंचांगap != शून्य);
		अगर (!biपंचांगap) अणु
			/* Merging treats extents as अगर they were new */
			अगर (!btrfs_मुक्त_space_trimmed(entry)) अणु
				ctl->discardable_extents[BTRFS_STAT_CURR]--;
				ctl->discardable_bytes[BTRFS_STAT_CURR] -=
					entry->bytes;
			पूर्ण

			try_merge_मुक्त_space(ctl, entry, false);
			steal_from_biपंचांगap(ctl, entry, false);

			/* As we insert directly, update these statistics */
			अगर (!btrfs_मुक्त_space_trimmed(entry)) अणु
				ctl->discardable_extents[BTRFS_STAT_CURR]++;
				ctl->discardable_bytes[BTRFS_STAT_CURR] +=
					entry->bytes;
			पूर्ण
		पूर्ण
		tree_insert_offset(&ctl->मुक्त_space_offset,
				   entry->offset, &entry->offset_index, biपंचांगap);
	पूर्ण
	cluster->root = RB_ROOT;
	spin_unlock(&cluster->lock);
	btrfs_put_block_group(block_group);
पूर्ण

अटल व्योम __btrfs_हटाओ_मुक्त_space_cache_locked(
				काष्ठा btrfs_मुक्त_space_ctl *ctl)
अणु
	काष्ठा btrfs_मुक्त_space *info;
	काष्ठा rb_node *node;

	जबतक ((node = rb_last(&ctl->मुक्त_space_offset)) != शून्य) अणु
		info = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);
		अगर (!info->biपंचांगap) अणु
			unlink_मुक्त_space(ctl, info);
			kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, info);
		पूर्ण अन्यथा अणु
			मुक्त_biपंचांगap(ctl, info);
		पूर्ण

		cond_resched_lock(&ctl->tree_lock);
	पूर्ण
पूर्ण

व्योम __btrfs_हटाओ_मुक्त_space_cache(काष्ठा btrfs_मुक्त_space_ctl *ctl)
अणु
	spin_lock(&ctl->tree_lock);
	__btrfs_हटाओ_मुक्त_space_cache_locked(ctl);
	अगर (ctl->निजी)
		btrfs_discard_update_discardable(ctl->निजी);
	spin_unlock(&ctl->tree_lock);
पूर्ण

व्योम btrfs_हटाओ_मुक्त_space_cache(काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_cluster *cluster;
	काष्ठा list_head *head;

	spin_lock(&ctl->tree_lock);
	जबतक ((head = block_group->cluster_list.next) !=
	       &block_group->cluster_list) अणु
		cluster = list_entry(head, काष्ठा btrfs_मुक्त_cluster,
				     block_group_list);

		WARN_ON(cluster->block_group != block_group);
		__btrfs_वापस_cluster_to_मुक्त_space(block_group, cluster);

		cond_resched_lock(&ctl->tree_lock);
	पूर्ण
	__btrfs_हटाओ_मुक्त_space_cache_locked(ctl);
	btrfs_discard_update_discardable(block_group);
	spin_unlock(&ctl->tree_lock);

पूर्ण

/**
 * btrfs_is_मुक्त_space_trimmed - see अगर everything is trimmed
 * @block_group: block_group of पूर्णांकerest
 *
 * Walk @block_group's मुक्त space rb_tree to determine अगर everything is trimmed.
 */
bool btrfs_is_मुक्त_space_trimmed(काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *info;
	काष्ठा rb_node *node;
	bool ret = true;

	spin_lock(&ctl->tree_lock);
	node = rb_first(&ctl->मुक्त_space_offset);

	जबतक (node) अणु
		info = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);

		अगर (!btrfs_मुक्त_space_trimmed(info)) अणु
			ret = false;
			अवरोध;
		पूर्ण

		node = rb_next(node);
	पूर्ण

	spin_unlock(&ctl->tree_lock);
	वापस ret;
पूर्ण

u64 btrfs_find_space_क्रम_alloc(काष्ठा btrfs_block_group *block_group,
			       u64 offset, u64 bytes, u64 empty_size,
			       u64 *max_extent_size)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_discard_ctl *discard_ctl =
					&block_group->fs_info->discard_ctl;
	काष्ठा btrfs_मुक्त_space *entry = शून्य;
	u64 bytes_search = bytes + empty_size;
	u64 ret = 0;
	u64 align_gap = 0;
	u64 align_gap_len = 0;
	क्रमागत btrfs_trim_state align_gap_trim_state = BTRFS_TRIM_STATE_UNTRIMMED;

	ASSERT(!btrfs_is_zoned(block_group->fs_info));

	spin_lock(&ctl->tree_lock);
	entry = find_मुक्त_space(ctl, &offset, &bytes_search,
				block_group->full_stripe_len, max_extent_size);
	अगर (!entry)
		जाओ out;

	ret = offset;
	अगर (entry->biपंचांगap) अणु
		biपंचांगap_clear_bits(ctl, entry, offset, bytes);

		अगर (!btrfs_मुक्त_space_trimmed(entry))
			atomic64_add(bytes, &discard_ctl->discard_bytes_saved);

		अगर (!entry->bytes)
			मुक्त_biपंचांगap(ctl, entry);
	पूर्ण अन्यथा अणु
		unlink_मुक्त_space(ctl, entry);
		align_gap_len = offset - entry->offset;
		align_gap = entry->offset;
		align_gap_trim_state = entry->trim_state;

		अगर (!btrfs_मुक्त_space_trimmed(entry))
			atomic64_add(bytes, &discard_ctl->discard_bytes_saved);

		entry->offset = offset + bytes;
		WARN_ON(entry->bytes < bytes + align_gap_len);

		entry->bytes -= bytes + align_gap_len;
		अगर (!entry->bytes)
			kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, entry);
		अन्यथा
			link_मुक्त_space(ctl, entry);
	पूर्ण
out:
	btrfs_discard_update_discardable(block_group);
	spin_unlock(&ctl->tree_lock);

	अगर (align_gap_len)
		__btrfs_add_मुक्त_space(block_group->fs_info, ctl,
				       align_gap, align_gap_len,
				       align_gap_trim_state);
	वापस ret;
पूर्ण

/*
 * given a cluster, put all of its extents back पूर्णांकo the मुक्त space
 * cache.  If a block group is passed, this function will only मुक्त
 * a cluster that beदीर्घs to the passed block group.
 *
 * Otherwise, it'll get a reference on the block group poपूर्णांकed to by the
 * cluster and हटाओ the cluster from it.
 */
व्योम btrfs_वापस_cluster_to_मुक्त_space(
			       काष्ठा btrfs_block_group *block_group,
			       काष्ठा btrfs_मुक्त_cluster *cluster)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl;

	/* first, get a safe poपूर्णांकer to the block group */
	spin_lock(&cluster->lock);
	अगर (!block_group) अणु
		block_group = cluster->block_group;
		अगर (!block_group) अणु
			spin_unlock(&cluster->lock);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (cluster->block_group != block_group) अणु
		/* someone अन्यथा has alपढ़ोy मुक्तd it करोn't reकरो their work */
		spin_unlock(&cluster->lock);
		वापस;
	पूर्ण
	btrfs_get_block_group(block_group);
	spin_unlock(&cluster->lock);

	ctl = block_group->मुक्त_space_ctl;

	/* now वापस any extents the cluster had on it */
	spin_lock(&ctl->tree_lock);
	__btrfs_वापस_cluster_to_मुक्त_space(block_group, cluster);
	spin_unlock(&ctl->tree_lock);

	btrfs_discard_queue_work(&block_group->fs_info->discard_ctl, block_group);

	/* finally drop our ref */
	btrfs_put_block_group(block_group);
पूर्ण

अटल u64 btrfs_alloc_from_biपंचांगap(काष्ठा btrfs_block_group *block_group,
				   काष्ठा btrfs_मुक्त_cluster *cluster,
				   काष्ठा btrfs_मुक्त_space *entry,
				   u64 bytes, u64 min_start,
				   u64 *max_extent_size)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	पूर्णांक err;
	u64 search_start = cluster->winकरोw_start;
	u64 search_bytes = bytes;
	u64 ret = 0;

	search_start = min_start;
	search_bytes = bytes;

	err = search_biपंचांगap(ctl, entry, &search_start, &search_bytes, true);
	अगर (err) अणु
		*max_extent_size = max(get_max_extent_size(entry),
				       *max_extent_size);
		वापस 0;
	पूर्ण

	ret = search_start;
	__biपंचांगap_clear_bits(ctl, entry, ret, bytes);

	वापस ret;
पूर्ण

/*
 * given a cluster, try to allocate 'bytes' from it, वापसs 0
 * अगर it couldn't find anything suitably large, or a logical disk offset
 * अगर things worked out
 */
u64 btrfs_alloc_from_cluster(काष्ठा btrfs_block_group *block_group,
			     काष्ठा btrfs_मुक्त_cluster *cluster, u64 bytes,
			     u64 min_start, u64 *max_extent_size)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_discard_ctl *discard_ctl =
					&block_group->fs_info->discard_ctl;
	काष्ठा btrfs_मुक्त_space *entry = शून्य;
	काष्ठा rb_node *node;
	u64 ret = 0;

	ASSERT(!btrfs_is_zoned(block_group->fs_info));

	spin_lock(&cluster->lock);
	अगर (bytes > cluster->max_size)
		जाओ out;

	अगर (cluster->block_group != block_group)
		जाओ out;

	node = rb_first(&cluster->root);
	अगर (!node)
		जाओ out;

	entry = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);
	जबतक (1) अणु
		अगर (entry->bytes < bytes)
			*max_extent_size = max(get_max_extent_size(entry),
					       *max_extent_size);

		अगर (entry->bytes < bytes ||
		    (!entry->biपंचांगap && entry->offset < min_start)) अणु
			node = rb_next(&entry->offset_index);
			अगर (!node)
				अवरोध;
			entry = rb_entry(node, काष्ठा btrfs_मुक्त_space,
					 offset_index);
			जारी;
		पूर्ण

		अगर (entry->biपंचांगap) अणु
			ret = btrfs_alloc_from_biपंचांगap(block_group,
						      cluster, entry, bytes,
						      cluster->winकरोw_start,
						      max_extent_size);
			अगर (ret == 0) अणु
				node = rb_next(&entry->offset_index);
				अगर (!node)
					अवरोध;
				entry = rb_entry(node, काष्ठा btrfs_मुक्त_space,
						 offset_index);
				जारी;
			पूर्ण
			cluster->winकरोw_start += bytes;
		पूर्ण अन्यथा अणु
			ret = entry->offset;

			entry->offset += bytes;
			entry->bytes -= bytes;
		पूर्ण

		अवरोध;
	पूर्ण
out:
	spin_unlock(&cluster->lock);

	अगर (!ret)
		वापस 0;

	spin_lock(&ctl->tree_lock);

	अगर (!btrfs_मुक्त_space_trimmed(entry))
		atomic64_add(bytes, &discard_ctl->discard_bytes_saved);

	ctl->मुक्त_space -= bytes;
	अगर (!entry->biपंचांगap && !btrfs_मुक्त_space_trimmed(entry))
		ctl->discardable_bytes[BTRFS_STAT_CURR] -= bytes;

	spin_lock(&cluster->lock);
	अगर (entry->bytes == 0) अणु
		rb_erase(&entry->offset_index, &cluster->root);
		ctl->मुक्त_extents--;
		अगर (entry->biपंचांगap) अणु
			kmem_cache_मुक्त(btrfs_मुक्त_space_biपंचांगap_cachep,
					entry->biपंचांगap);
			ctl->total_biपंचांगaps--;
			recalculate_thresholds(ctl);
		पूर्ण अन्यथा अगर (!btrfs_मुक्त_space_trimmed(entry)) अणु
			ctl->discardable_extents[BTRFS_STAT_CURR]--;
		पूर्ण
		kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, entry);
	पूर्ण

	spin_unlock(&cluster->lock);
	spin_unlock(&ctl->tree_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_biपंचांगap_cluster(काष्ठा btrfs_block_group *block_group,
				काष्ठा btrfs_मुक्त_space *entry,
				काष्ठा btrfs_मुक्त_cluster *cluster,
				u64 offset, u64 bytes,
				u64 cont1_bytes, u64 min_bytes)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	अचिन्हित दीर्घ next_zero;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ want_bits;
	अचिन्हित दीर्घ min_bits;
	अचिन्हित दीर्घ found_bits;
	अचिन्हित दीर्घ max_bits = 0;
	अचिन्हित दीर्घ start = 0;
	अचिन्हित दीर्घ total_found = 0;
	पूर्णांक ret;

	i = offset_to_bit(entry->offset, ctl->unit,
			  max_t(u64, offset, entry->offset));
	want_bits = bytes_to_bits(bytes, ctl->unit);
	min_bits = bytes_to_bits(min_bytes, ctl->unit);

	/*
	 * Don't bother looking for a cluster in this bitmap if it's heavily
	 * fragmented.
	 */
	अगर (entry->max_extent_size &&
	    entry->max_extent_size < cont1_bytes)
		वापस -ENOSPC;
again:
	found_bits = 0;
	क्रम_each_set_bit_from(i, entry->biपंचांगap, BITS_PER_BITMAP) अणु
		next_zero = find_next_zero_bit(entry->biपंचांगap,
					       BITS_PER_BITMAP, i);
		अगर (next_zero - i >= min_bits) अणु
			found_bits = next_zero - i;
			अगर (found_bits > max_bits)
				max_bits = found_bits;
			अवरोध;
		पूर्ण
		अगर (next_zero - i > max_bits)
			max_bits = next_zero - i;
		i = next_zero;
	पूर्ण

	अगर (!found_bits) अणु
		entry->max_extent_size = (u64)max_bits * ctl->unit;
		वापस -ENOSPC;
	पूर्ण

	अगर (!total_found) अणु
		start = i;
		cluster->max_size = 0;
	पूर्ण

	total_found += found_bits;

	अगर (cluster->max_size < found_bits * ctl->unit)
		cluster->max_size = found_bits * ctl->unit;

	अगर (total_found < want_bits || cluster->max_size < cont1_bytes) अणु
		i = next_zero + 1;
		जाओ again;
	पूर्ण

	cluster->winकरोw_start = start * ctl->unit + entry->offset;
	rb_erase(&entry->offset_index, &ctl->मुक्त_space_offset);
	ret = tree_insert_offset(&cluster->root, entry->offset,
				 &entry->offset_index, 1);
	ASSERT(!ret); /* -EEXIST; Logic error */

	trace_btrfs_setup_cluster(block_group, cluster,
				  total_found * ctl->unit, 1);
	वापस 0;
पूर्ण

/*
 * This searches the block group क्रम just extents to fill the cluster with.
 * Try to find a cluster with at least bytes total bytes, at least one
 * extent of cont1_bytes, and other clusters of at least min_bytes.
 */
अटल noअंतरभूत पूर्णांक
setup_cluster_no_biपंचांगap(काष्ठा btrfs_block_group *block_group,
			काष्ठा btrfs_मुक्त_cluster *cluster,
			काष्ठा list_head *biपंचांगaps, u64 offset, u64 bytes,
			u64 cont1_bytes, u64 min_bytes)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *first = शून्य;
	काष्ठा btrfs_मुक्त_space *entry = शून्य;
	काष्ठा btrfs_मुक्त_space *last;
	काष्ठा rb_node *node;
	u64 winकरोw_मुक्त;
	u64 max_extent;
	u64 total_size = 0;

	entry = tree_search_offset(ctl, offset, 0, 1);
	अगर (!entry)
		वापस -ENOSPC;

	/*
	 * We करोn't want biपंचांगaps, so just move aदीर्घ until we find a normal
	 * extent entry.
	 */
	जबतक (entry->biपंचांगap || entry->bytes < min_bytes) अणु
		अगर (entry->biपंचांगap && list_empty(&entry->list))
			list_add_tail(&entry->list, biपंचांगaps);
		node = rb_next(&entry->offset_index);
		अगर (!node)
			वापस -ENOSPC;
		entry = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);
	पूर्ण

	winकरोw_मुक्त = entry->bytes;
	max_extent = entry->bytes;
	first = entry;
	last = entry;

	क्रम (node = rb_next(&entry->offset_index); node;
	     node = rb_next(&entry->offset_index)) अणु
		entry = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);

		अगर (entry->biपंचांगap) अणु
			अगर (list_empty(&entry->list))
				list_add_tail(&entry->list, biपंचांगaps);
			जारी;
		पूर्ण

		अगर (entry->bytes < min_bytes)
			जारी;

		last = entry;
		winकरोw_मुक्त += entry->bytes;
		अगर (entry->bytes > max_extent)
			max_extent = entry->bytes;
	पूर्ण

	अगर (winकरोw_मुक्त < bytes || max_extent < cont1_bytes)
		वापस -ENOSPC;

	cluster->winकरोw_start = first->offset;

	node = &first->offset_index;

	/*
	 * now we've found our entries, pull them out of the मुक्त space
	 * cache and put them पूर्णांकo the cluster rbtree
	 */
	करो अणु
		पूर्णांक ret;

		entry = rb_entry(node, काष्ठा btrfs_मुक्त_space, offset_index);
		node = rb_next(&entry->offset_index);
		अगर (entry->biपंचांगap || entry->bytes < min_bytes)
			जारी;

		rb_erase(&entry->offset_index, &ctl->मुक्त_space_offset);
		ret = tree_insert_offset(&cluster->root, entry->offset,
					 &entry->offset_index, 0);
		total_size += entry->bytes;
		ASSERT(!ret); /* -EEXIST; Logic error */
	पूर्ण जबतक (node && entry != last);

	cluster->max_size = max_extent;
	trace_btrfs_setup_cluster(block_group, cluster, total_size, 0);
	वापस 0;
पूर्ण

/*
 * This specअगरically looks क्रम biपंचांगaps that may work in the cluster, we assume
 * that we have alपढ़ोy failed to find extents that will work.
 */
अटल noअंतरभूत पूर्णांक
setup_cluster_biपंचांगap(काष्ठा btrfs_block_group *block_group,
		     काष्ठा btrfs_मुक्त_cluster *cluster,
		     काष्ठा list_head *biपंचांगaps, u64 offset, u64 bytes,
		     u64 cont1_bytes, u64 min_bytes)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *entry = शून्य;
	पूर्णांक ret = -ENOSPC;
	u64 biपंचांगap_offset = offset_to_biपंचांगap(ctl, offset);

	अगर (ctl->total_biपंचांगaps == 0)
		वापस -ENOSPC;

	/*
	 * The biपंचांगap that covers offset won't be in the list unless offset
	 * is just its start offset.
	 */
	अगर (!list_empty(biपंचांगaps))
		entry = list_first_entry(biपंचांगaps, काष्ठा btrfs_मुक्त_space, list);

	अगर (!entry || entry->offset != biपंचांगap_offset) अणु
		entry = tree_search_offset(ctl, biपंचांगap_offset, 1, 0);
		अगर (entry && list_empty(&entry->list))
			list_add(&entry->list, biपंचांगaps);
	पूर्ण

	list_क्रम_each_entry(entry, biपंचांगaps, list) अणु
		अगर (entry->bytes < bytes)
			जारी;
		ret = btrfs_biपंचांगap_cluster(block_group, entry, cluster, offset,
					   bytes, cont1_bytes, min_bytes);
		अगर (!ret)
			वापस 0;
	पूर्ण

	/*
	 * The biपंचांगaps list has all the biपंचांगaps that record मुक्त space
	 * starting after offset, so no more search is required.
	 */
	वापस -ENOSPC;
पूर्ण

/*
 * here we try to find a cluster of blocks in a block group.  The goal
 * is to find at least bytes+empty_size.
 * We might not find them all in one contiguous area.
 *
 * वापसs zero and sets up cluster अगर things worked out, otherwise
 * it वापसs -enospc
 */
पूर्णांक btrfs_find_space_cluster(काष्ठा btrfs_block_group *block_group,
			     काष्ठा btrfs_मुक्त_cluster *cluster,
			     u64 offset, u64 bytes, u64 empty_size)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *entry, *पंचांगp;
	LIST_HEAD(biपंचांगaps);
	u64 min_bytes;
	u64 cont1_bytes;
	पूर्णांक ret;

	/*
	 * Choose the minimum extent size we'll require क्रम this
	 * cluster.  For SSD_SPREAD, करोn't allow any fragmentation.
	 * For metadata, allow allocates with smaller extents.  For
	 * data, keep it dense.
	 */
	अगर (btrfs_test_opt(fs_info, SSD_SPREAD)) अणु
		cont1_bytes = min_bytes = bytes + empty_size;
	पूर्ण अन्यथा अगर (block_group->flags & BTRFS_BLOCK_GROUP_METADATA) अणु
		cont1_bytes = bytes;
		min_bytes = fs_info->sectorsize;
	पूर्ण अन्यथा अणु
		cont1_bytes = max(bytes, (bytes + empty_size) >> 2);
		min_bytes = fs_info->sectorsize;
	पूर्ण

	spin_lock(&ctl->tree_lock);

	/*
	 * If we know we करोn't have enough space to make a cluster don't even
	 * bother करोing all the work to try and find one.
	 */
	अगर (ctl->मुक्त_space < bytes) अणु
		spin_unlock(&ctl->tree_lock);
		वापस -ENOSPC;
	पूर्ण

	spin_lock(&cluster->lock);

	/* someone alपढ़ोy found a cluster, hooray */
	अगर (cluster->block_group) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	trace_btrfs_find_cluster(block_group, offset, bytes, empty_size,
				 min_bytes);

	ret = setup_cluster_no_biपंचांगap(block_group, cluster, &biपंचांगaps, offset,
				      bytes + empty_size,
				      cont1_bytes, min_bytes);
	अगर (ret)
		ret = setup_cluster_biपंचांगap(block_group, cluster, &biपंचांगaps,
					   offset, bytes + empty_size,
					   cont1_bytes, min_bytes);

	/* Clear our temporary list */
	list_क्रम_each_entry_safe(entry, पंचांगp, &biपंचांगaps, list)
		list_del_init(&entry->list);

	अगर (!ret) अणु
		btrfs_get_block_group(block_group);
		list_add_tail(&cluster->block_group_list,
			      &block_group->cluster_list);
		cluster->block_group = block_group;
	पूर्ण अन्यथा अणु
		trace_btrfs_failed_cluster_setup(block_group);
	पूर्ण
out:
	spin_unlock(&cluster->lock);
	spin_unlock(&ctl->tree_lock);

	वापस ret;
पूर्ण

/*
 * simple code to zero out a cluster
 */
व्योम btrfs_init_मुक्त_cluster(काष्ठा btrfs_मुक्त_cluster *cluster)
अणु
	spin_lock_init(&cluster->lock);
	spin_lock_init(&cluster->refill_lock);
	cluster->root = RB_ROOT;
	cluster->max_size = 0;
	cluster->fragmented = false;
	INIT_LIST_HEAD(&cluster->block_group_list);
	cluster->block_group = शून्य;
पूर्ण

अटल पूर्णांक करो_trimming(काष्ठा btrfs_block_group *block_group,
		       u64 *total_trimmed, u64 start, u64 bytes,
		       u64 reserved_start, u64 reserved_bytes,
		       क्रमागत btrfs_trim_state reserved_trim_state,
		       काष्ठा btrfs_trim_range *trim_entry)
अणु
	काष्ठा btrfs_space_info *space_info = block_group->space_info;
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	पूर्णांक ret;
	पूर्णांक update = 0;
	स्थिर u64 end = start + bytes;
	स्थिर u64 reserved_end = reserved_start + reserved_bytes;
	क्रमागत btrfs_trim_state trim_state = BTRFS_TRIM_STATE_UNTRIMMED;
	u64 trimmed = 0;

	spin_lock(&space_info->lock);
	spin_lock(&block_group->lock);
	अगर (!block_group->ro) अणु
		block_group->reserved += reserved_bytes;
		space_info->bytes_reserved += reserved_bytes;
		update = 1;
	पूर्ण
	spin_unlock(&block_group->lock);
	spin_unlock(&space_info->lock);

	ret = btrfs_discard_extent(fs_info, start, bytes, &trimmed);
	अगर (!ret) अणु
		*total_trimmed += trimmed;
		trim_state = BTRFS_TRIM_STATE_TRIMMED;
	पूर्ण

	mutex_lock(&ctl->cache_ग_लिखोout_mutex);
	अगर (reserved_start < start)
		__btrfs_add_मुक्त_space(fs_info, ctl, reserved_start,
				       start - reserved_start,
				       reserved_trim_state);
	अगर (start + bytes < reserved_start + reserved_bytes)
		__btrfs_add_मुक्त_space(fs_info, ctl, end, reserved_end - end,
				       reserved_trim_state);
	__btrfs_add_मुक्त_space(fs_info, ctl, start, bytes, trim_state);
	list_del(&trim_entry->list);
	mutex_unlock(&ctl->cache_ग_लिखोout_mutex);

	अगर (update) अणु
		spin_lock(&space_info->lock);
		spin_lock(&block_group->lock);
		अगर (block_group->ro)
			space_info->bytes_पढ़ोonly += reserved_bytes;
		block_group->reserved -= reserved_bytes;
		space_info->bytes_reserved -= reserved_bytes;
		spin_unlock(&block_group->lock);
		spin_unlock(&space_info->lock);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * If @async is set, then we will trim 1 region and वापस.
 */
अटल पूर्णांक trim_no_biपंचांगap(काष्ठा btrfs_block_group *block_group,
			  u64 *total_trimmed, u64 start, u64 end, u64 minlen,
			  bool async)
अणु
	काष्ठा btrfs_discard_ctl *discard_ctl =
					&block_group->fs_info->discard_ctl;
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *entry;
	काष्ठा rb_node *node;
	पूर्णांक ret = 0;
	u64 extent_start;
	u64 extent_bytes;
	क्रमागत btrfs_trim_state extent_trim_state;
	u64 bytes;
	स्थिर u64 max_discard_size = READ_ONCE(discard_ctl->max_discard_size);

	जबतक (start < end) अणु
		काष्ठा btrfs_trim_range trim_entry;

		mutex_lock(&ctl->cache_ग_लिखोout_mutex);
		spin_lock(&ctl->tree_lock);

		अगर (ctl->मुक्त_space < minlen)
			जाओ out_unlock;

		entry = tree_search_offset(ctl, start, 0, 1);
		अगर (!entry)
			जाओ out_unlock;

		/* Skip biपंचांगaps and अगर async, alपढ़ोy trimmed entries */
		जबतक (entry->biपंचांगap ||
		       (async && btrfs_मुक्त_space_trimmed(entry))) अणु
			node = rb_next(&entry->offset_index);
			अगर (!node)
				जाओ out_unlock;
			entry = rb_entry(node, काष्ठा btrfs_मुक्त_space,
					 offset_index);
		पूर्ण

		अगर (entry->offset >= end)
			जाओ out_unlock;

		extent_start = entry->offset;
		extent_bytes = entry->bytes;
		extent_trim_state = entry->trim_state;
		अगर (async) अणु
			start = entry->offset;
			bytes = entry->bytes;
			अगर (bytes < minlen) अणु
				spin_unlock(&ctl->tree_lock);
				mutex_unlock(&ctl->cache_ग_लिखोout_mutex);
				जाओ next;
			पूर्ण
			unlink_मुक्त_space(ctl, entry);
			/*
			 * Let bytes = BTRFS_MAX_DISCARD_SIZE + X.
			 * If X < BTRFS_ASYNC_DISCARD_MIN_FILTER, we won't trim
			 * X when we come back around.  So trim it now.
			 */
			अगर (max_discard_size &&
			    bytes >= (max_discard_size +
				      BTRFS_ASYNC_DISCARD_MIN_FILTER)) अणु
				bytes = max_discard_size;
				extent_bytes = max_discard_size;
				entry->offset += max_discard_size;
				entry->bytes -= max_discard_size;
				link_मुक्त_space(ctl, entry);
			पूर्ण अन्यथा अणु
				kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, entry);
			पूर्ण
		पूर्ण अन्यथा अणु
			start = max(start, extent_start);
			bytes = min(extent_start + extent_bytes, end) - start;
			अगर (bytes < minlen) अणु
				spin_unlock(&ctl->tree_lock);
				mutex_unlock(&ctl->cache_ग_लिखोout_mutex);
				जाओ next;
			पूर्ण

			unlink_मुक्त_space(ctl, entry);
			kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, entry);
		पूर्ण

		spin_unlock(&ctl->tree_lock);
		trim_entry.start = extent_start;
		trim_entry.bytes = extent_bytes;
		list_add_tail(&trim_entry.list, &ctl->trimming_ranges);
		mutex_unlock(&ctl->cache_ग_लिखोout_mutex);

		ret = करो_trimming(block_group, total_trimmed, start, bytes,
				  extent_start, extent_bytes, extent_trim_state,
				  &trim_entry);
		अगर (ret) अणु
			block_group->discard_cursor = start + bytes;
			अवरोध;
		पूर्ण
next:
		start += bytes;
		block_group->discard_cursor = start;
		अगर (async && *total_trimmed)
			अवरोध;

		अगर (fatal_संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		cond_resched();
	पूर्ण

	वापस ret;

out_unlock:
	block_group->discard_cursor = btrfs_block_group_end(block_group);
	spin_unlock(&ctl->tree_lock);
	mutex_unlock(&ctl->cache_ग_लिखोout_mutex);

	वापस ret;
पूर्ण

/*
 * If we अवरोध out of trimming a biपंचांगap prematurely, we should reset the
 * trimming bit.  In a rather contrieved हाल, it's possible to race here so
 * reset the state to BTRFS_TRIM_STATE_UNTRIMMED.
 *
 * start = start of biपंचांगap
 * end = near end of biपंचांगap
 *
 * Thपढ़ो 1:			Thपढ़ो 2:
 * trim_biपंचांगaps(start)
 *				trim_biपंचांगaps(end)
 *				end_trimming_biपंचांगap()
 * reset_trimming_biपंचांगap()
 */
अटल व्योम reset_trimming_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl, u64 offset)
अणु
	काष्ठा btrfs_मुक्त_space *entry;

	spin_lock(&ctl->tree_lock);
	entry = tree_search_offset(ctl, offset, 1, 0);
	अगर (entry) अणु
		अगर (btrfs_मुक्त_space_trimmed(entry)) अणु
			ctl->discardable_extents[BTRFS_STAT_CURR] +=
				entry->biपंचांगap_extents;
			ctl->discardable_bytes[BTRFS_STAT_CURR] += entry->bytes;
		पूर्ण
		entry->trim_state = BTRFS_TRIM_STATE_UNTRIMMED;
	पूर्ण

	spin_unlock(&ctl->tree_lock);
पूर्ण

अटल व्योम end_trimming_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
				काष्ठा btrfs_मुक्त_space *entry)
अणु
	अगर (btrfs_मुक्त_space_trimming_biपंचांगap(entry)) अणु
		entry->trim_state = BTRFS_TRIM_STATE_TRIMMED;
		ctl->discardable_extents[BTRFS_STAT_CURR] -=
			entry->biपंचांगap_extents;
		ctl->discardable_bytes[BTRFS_STAT_CURR] -= entry->bytes;
	पूर्ण
पूर्ण

/*
 * If @async is set, then we will trim 1 region and वापस.
 */
अटल पूर्णांक trim_biपंचांगaps(काष्ठा btrfs_block_group *block_group,
			u64 *total_trimmed, u64 start, u64 end, u64 minlen,
			u64 maxlen, bool async)
अणु
	काष्ठा btrfs_discard_ctl *discard_ctl =
					&block_group->fs_info->discard_ctl;
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *entry;
	पूर्णांक ret = 0;
	पूर्णांक ret2;
	u64 bytes;
	u64 offset = offset_to_biपंचांगap(ctl, start);
	स्थिर u64 max_discard_size = READ_ONCE(discard_ctl->max_discard_size);

	जबतक (offset < end) अणु
		bool next_biपंचांगap = false;
		काष्ठा btrfs_trim_range trim_entry;

		mutex_lock(&ctl->cache_ग_लिखोout_mutex);
		spin_lock(&ctl->tree_lock);

		अगर (ctl->मुक्त_space < minlen) अणु
			block_group->discard_cursor =
				btrfs_block_group_end(block_group);
			spin_unlock(&ctl->tree_lock);
			mutex_unlock(&ctl->cache_ग_लिखोout_mutex);
			अवरोध;
		पूर्ण

		entry = tree_search_offset(ctl, offset, 1, 0);
		/*
		 * Biपंचांगaps are marked trimmed lossily now to prevent स्थिरant
		 * discarding of the same biपंचांगap (the reason why we are bound
		 * by the filters).  So, retrim the block group biपंचांगaps when we
		 * are preparing to punt to the unused_bgs list.  This uses
		 * @minlen to determine अगर we are in BTRFS_DISCARD_INDEX_UNUSED
		 * which is the only discard index which sets minlen to 0.
		 */
		अगर (!entry || (async && minlen && start == offset &&
			       btrfs_मुक्त_space_trimmed(entry))) अणु
			spin_unlock(&ctl->tree_lock);
			mutex_unlock(&ctl->cache_ग_लिखोout_mutex);
			next_biपंचांगap = true;
			जाओ next;
		पूर्ण

		/*
		 * Async discard biपंचांगap trimming begins at by setting the start
		 * to be key.objectid and the offset_to_biपंचांगap() aligns to the
		 * start of the biपंचांगap.  This lets us know we are fully
		 * scanning the biपंचांगap rather than only some portion of it.
		 */
		अगर (start == offset)
			entry->trim_state = BTRFS_TRIM_STATE_TRIMMING;

		bytes = minlen;
		ret2 = search_biपंचांगap(ctl, entry, &start, &bytes, false);
		अगर (ret2 || start >= end) अणु
			/*
			 * We lossily consider a biपंचांगap trimmed अगर we only skip
			 * over regions <= BTRFS_ASYNC_DISCARD_MIN_FILTER.
			 */
			अगर (ret2 && minlen <= BTRFS_ASYNC_DISCARD_MIN_FILTER)
				end_trimming_biपंचांगap(ctl, entry);
			अन्यथा
				entry->trim_state = BTRFS_TRIM_STATE_UNTRIMMED;
			spin_unlock(&ctl->tree_lock);
			mutex_unlock(&ctl->cache_ग_लिखोout_mutex);
			next_biपंचांगap = true;
			जाओ next;
		पूर्ण

		/*
		 * We alपढ़ोy trimmed a region, but are using the locking above
		 * to reset the trim_state.
		 */
		अगर (async && *total_trimmed) अणु
			spin_unlock(&ctl->tree_lock);
			mutex_unlock(&ctl->cache_ग_लिखोout_mutex);
			जाओ out;
		पूर्ण

		bytes = min(bytes, end - start);
		अगर (bytes < minlen || (async && maxlen && bytes > maxlen)) अणु
			spin_unlock(&ctl->tree_lock);
			mutex_unlock(&ctl->cache_ग_लिखोout_mutex);
			जाओ next;
		पूर्ण

		/*
		 * Let bytes = BTRFS_MAX_DISCARD_SIZE + X.
		 * If X < @minlen, we won't trim X when we come back around.
		 * So trim it now.  We dअगरfer here from trimming extents as we
		 * करोn't keep inभागidual state per bit.
		 */
		अगर (async &&
		    max_discard_size &&
		    bytes > (max_discard_size + minlen))
			bytes = max_discard_size;

		biपंचांगap_clear_bits(ctl, entry, start, bytes);
		अगर (entry->bytes == 0)
			मुक्त_biपंचांगap(ctl, entry);

		spin_unlock(&ctl->tree_lock);
		trim_entry.start = start;
		trim_entry.bytes = bytes;
		list_add_tail(&trim_entry.list, &ctl->trimming_ranges);
		mutex_unlock(&ctl->cache_ग_लिखोout_mutex);

		ret = करो_trimming(block_group, total_trimmed, start, bytes,
				  start, bytes, 0, &trim_entry);
		अगर (ret) अणु
			reset_trimming_biपंचांगap(ctl, offset);
			block_group->discard_cursor =
				btrfs_block_group_end(block_group);
			अवरोध;
		पूर्ण
next:
		अगर (next_biपंचांगap) अणु
			offset += BITS_PER_BITMAP * ctl->unit;
			start = offset;
		पूर्ण अन्यथा अणु
			start += bytes;
		पूर्ण
		block_group->discard_cursor = start;

		अगर (fatal_संकेत_pending(current)) अणु
			अगर (start != offset)
				reset_trimming_biपंचांगap(ctl, offset);
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		cond_resched();
	पूर्ण

	अगर (offset >= end)
		block_group->discard_cursor = end;

out:
	वापस ret;
पूर्ण

पूर्णांक btrfs_trim_block_group(काष्ठा btrfs_block_group *block_group,
			   u64 *trimmed, u64 start, u64 end, u64 minlen)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	पूर्णांक ret;
	u64 rem = 0;

	ASSERT(!btrfs_is_zoned(block_group->fs_info));

	*trimmed = 0;

	spin_lock(&block_group->lock);
	अगर (block_group->हटाओd) अणु
		spin_unlock(&block_group->lock);
		वापस 0;
	पूर्ण
	btrfs_मुक्तze_block_group(block_group);
	spin_unlock(&block_group->lock);

	ret = trim_no_biपंचांगap(block_group, trimmed, start, end, minlen, false);
	अगर (ret)
		जाओ out;

	ret = trim_biपंचांगaps(block_group, trimmed, start, end, minlen, 0, false);
	भाग64_u64_rem(end, BITS_PER_BITMAP * ctl->unit, &rem);
	/* If we ended in the middle of a biपंचांगap, reset the trimming flag */
	अगर (rem)
		reset_trimming_biपंचांगap(ctl, offset_to_biपंचांगap(ctl, end));
out:
	btrfs_unमुक्तze_block_group(block_group);
	वापस ret;
पूर्ण

पूर्णांक btrfs_trim_block_group_extents(काष्ठा btrfs_block_group *block_group,
				   u64 *trimmed, u64 start, u64 end, u64 minlen,
				   bool async)
अणु
	पूर्णांक ret;

	*trimmed = 0;

	spin_lock(&block_group->lock);
	अगर (block_group->हटाओd) अणु
		spin_unlock(&block_group->lock);
		वापस 0;
	पूर्ण
	btrfs_मुक्तze_block_group(block_group);
	spin_unlock(&block_group->lock);

	ret = trim_no_biपंचांगap(block_group, trimmed, start, end, minlen, async);
	btrfs_unमुक्तze_block_group(block_group);

	वापस ret;
पूर्ण

पूर्णांक btrfs_trim_block_group_biपंचांगaps(काष्ठा btrfs_block_group *block_group,
				   u64 *trimmed, u64 start, u64 end, u64 minlen,
				   u64 maxlen, bool async)
अणु
	पूर्णांक ret;

	*trimmed = 0;

	spin_lock(&block_group->lock);
	अगर (block_group->हटाओd) अणु
		spin_unlock(&block_group->lock);
		वापस 0;
	पूर्ण
	btrfs_मुक्तze_block_group(block_group);
	spin_unlock(&block_group->lock);

	ret = trim_biपंचांगaps(block_group, trimmed, start, end, minlen, maxlen,
			   async);

	btrfs_unमुक्तze_block_group(block_group);

	वापस ret;
पूर्ण

bool btrfs_मुक्त_space_cache_v1_active(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस btrfs_super_cache_generation(fs_info->super_copy);
पूर्ण

अटल पूर्णांक cleanup_मुक्त_space_cache_v1(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_block_group *block_group;
	काष्ठा rb_node *node;
	पूर्णांक ret = 0;

	btrfs_info(fs_info, "cleaning free space cache v1");

	node = rb_first(&fs_info->block_group_cache_tree);
	जबतक (node) अणु
		block_group = rb_entry(node, काष्ठा btrfs_block_group, cache_node);
		ret = btrfs_हटाओ_मुक्त_space_inode(trans, शून्य, block_group);
		अगर (ret)
			जाओ out;
		node = rb_next(node);
	पूर्ण
out:
	वापस ret;
पूर्ण

पूर्णांक btrfs_set_मुक्त_space_cache_v1_active(काष्ठा btrfs_fs_info *fs_info, bool active)
अणु
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;

	/*
	 * update_super_roots will appropriately set or unset
	 * super_copy->cache_generation based on SPACE_CACHE and
	 * BTRFS_FS_CLEANUP_SPACE_CACHE_V1. For this reason, we need a
	 * transaction commit whether we are enabling space cache v1 and करोn't
	 * have any other work to करो, or are disabling it and removing मुक्त
	 * space inodes.
	 */
	trans = btrfs_start_transaction(fs_info->tree_root, 0);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	अगर (!active) अणु
		set_bit(BTRFS_FS_CLEANUP_SPACE_CACHE_V1, &fs_info->flags);
		ret = cleanup_मुक्त_space_cache_v1(fs_info, trans);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			btrfs_end_transaction(trans);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = btrfs_commit_transaction(trans);
out:
	clear_bit(BTRFS_FS_CLEANUP_SPACE_CACHE_V1, &fs_info->flags);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
/*
 * Use this अगर you need to make a biपंचांगap or extent entry specअगरically, it
 * करोesn't करो any of the merging that add_मुक्त_space करोes, this acts a lot like
 * how the मुक्त space cache loading stuff works, so you can get really weird
 * configurations.
 */
पूर्णांक test_add_मुक्त_space_entry(काष्ठा btrfs_block_group *cache,
			      u64 offset, u64 bytes, bool biपंचांगap)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = cache->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *info = शून्य, *biपंचांगap_info;
	व्योम *map = शून्य;
	क्रमागत btrfs_trim_state trim_state = BTRFS_TRIM_STATE_TRIMMED;
	u64 bytes_added;
	पूर्णांक ret;

again:
	अगर (!info) अणु
		info = kmem_cache_zalloc(btrfs_मुक्त_space_cachep, GFP_NOFS);
		अगर (!info)
			वापस -ENOMEM;
	पूर्ण

	अगर (!biपंचांगap) अणु
		spin_lock(&ctl->tree_lock);
		info->offset = offset;
		info->bytes = bytes;
		info->max_extent_size = 0;
		ret = link_मुक्त_space(ctl, info);
		spin_unlock(&ctl->tree_lock);
		अगर (ret)
			kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, info);
		वापस ret;
	पूर्ण

	अगर (!map) अणु
		map = kmem_cache_zalloc(btrfs_मुक्त_space_biपंचांगap_cachep, GFP_NOFS);
		अगर (!map) अणु
			kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, info);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	spin_lock(&ctl->tree_lock);
	biपंचांगap_info = tree_search_offset(ctl, offset_to_biपंचांगap(ctl, offset),
					 1, 0);
	अगर (!biपंचांगap_info) अणु
		info->biपंचांगap = map;
		map = शून्य;
		add_new_biपंचांगap(ctl, info, offset);
		biपंचांगap_info = info;
		info = शून्य;
	पूर्ण

	bytes_added = add_bytes_to_biपंचांगap(ctl, biपंचांगap_info, offset, bytes,
					  trim_state);

	bytes -= bytes_added;
	offset += bytes_added;
	spin_unlock(&ctl->tree_lock);

	अगर (bytes)
		जाओ again;

	अगर (info)
		kmem_cache_मुक्त(btrfs_मुक्त_space_cachep, info);
	अगर (map)
		kmem_cache_मुक्त(btrfs_मुक्त_space_biपंचांगap_cachep, map);
	वापस 0;
पूर्ण

/*
 * Checks to see अगर the given range is in the मुक्त space cache.  This is really
 * just used to check the असलence of space, so अगर there is मुक्त space in the
 * range at all we will वापस 1.
 */
पूर्णांक test_check_exists(काष्ठा btrfs_block_group *cache,
		      u64 offset, u64 bytes)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl = cache->मुक्त_space_ctl;
	काष्ठा btrfs_मुक्त_space *info;
	पूर्णांक ret = 0;

	spin_lock(&ctl->tree_lock);
	info = tree_search_offset(ctl, offset, 0, 0);
	अगर (!info) अणु
		info = tree_search_offset(ctl, offset_to_biपंचांगap(ctl, offset),
					  1, 0);
		अगर (!info)
			जाओ out;
	पूर्ण

have_info:
	अगर (info->biपंचांगap) अणु
		u64 bit_off, bit_bytes;
		काष्ठा rb_node *n;
		काष्ठा btrfs_मुक्त_space *पंचांगp;

		bit_off = offset;
		bit_bytes = ctl->unit;
		ret = search_biपंचांगap(ctl, info, &bit_off, &bit_bytes, false);
		अगर (!ret) अणु
			अगर (bit_off == offset) अणु
				ret = 1;
				जाओ out;
			पूर्ण अन्यथा अगर (bit_off > offset &&
				   offset + bytes > bit_off) अणु
				ret = 1;
				जाओ out;
			पूर्ण
		पूर्ण

		n = rb_prev(&info->offset_index);
		जबतक (n) अणु
			पंचांगp = rb_entry(n, काष्ठा btrfs_मुक्त_space,
				       offset_index);
			अगर (पंचांगp->offset + पंचांगp->bytes < offset)
				अवरोध;
			अगर (offset + bytes < पंचांगp->offset) अणु
				n = rb_prev(&पंचांगp->offset_index);
				जारी;
			पूर्ण
			info = पंचांगp;
			जाओ have_info;
		पूर्ण

		n = rb_next(&info->offset_index);
		जबतक (n) अणु
			पंचांगp = rb_entry(n, काष्ठा btrfs_मुक्त_space,
				       offset_index);
			अगर (offset + bytes < पंचांगp->offset)
				अवरोध;
			अगर (पंचांगp->offset + पंचांगp->bytes < offset) अणु
				n = rb_next(&पंचांगp->offset_index);
				जारी;
			पूर्ण
			info = पंचांगp;
			जाओ have_info;
		पूर्ण

		ret = 0;
		जाओ out;
	पूर्ण

	अगर (info->offset == offset) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	अगर (offset > info->offset && offset < info->offset + info->bytes)
		ret = 1;
out:
	spin_unlock(&ctl->tree_lock);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_BTRFS_FS_RUN_SANITY_TESTS */
