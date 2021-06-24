<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/blkdev.h>
#समावेश <linux/iversion.h>
#समावेश "compression.h"
#समावेश "ctree.h"
#समावेश "delalloc-space.h"
#समावेश "reflink.h"
#समावेश "transaction.h"

#घोषणा BTRFS_MAX_DEDUPE_LEN	SZ_16M

अटल पूर्णांक clone_finish_inode_update(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा inode *inode,
				     u64 enकरोff,
				     स्थिर u64 destoff,
				     स्थिर u64 olen,
				     पूर्णांक no_समय_update)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	पूर्णांक ret;

	inode_inc_iversion(inode);
	अगर (!no_समय_update)
		inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	/*
	 * We round up to the block size at eof when determining which
	 * extents to clone above, but shouldn't round up the file size.
	 */
	अगर (enकरोff > destoff + olen)
		enकरोff = destoff + olen;
	अगर (enकरोff > inode->i_size) अणु
		i_size_ग_लिखो(inode, enकरोff);
		btrfs_inode_safe_disk_i_size_ग_लिखो(BTRFS_I(inode), 0);
	पूर्ण

	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		btrfs_end_transaction(trans);
		जाओ out;
	पूर्ण
	ret = btrfs_end_transaction(trans);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक copy_अंतरभूत_to_page(काष्ठा btrfs_inode *inode,
			       स्थिर u64 file_offset,
			       अक्षर *अंतरभूत_data,
			       स्थिर u64 size,
			       स्थिर u64 datal,
			       स्थिर u8 comp_type)
अणु
	स्थिर u64 block_size = btrfs_inode_sectorsize(inode);
	स्थिर u64 range_end = file_offset + block_size - 1;
	स्थिर माप_प्रकार अंतरभूत_size = size - btrfs_file_extent_calc_अंतरभूत_size(0);
	अक्षर *data_start = अंतरभूत_data + btrfs_file_extent_calc_अंतरभूत_size(0);
	काष्ठा extent_changeset *data_reserved = शून्य;
	काष्ठा page *page = शून्य;
	काष्ठा address_space *mapping = inode->vfs_inode.i_mapping;
	पूर्णांक ret;

	ASSERT(IS_ALIGNED(file_offset, block_size));

	/*
	 * We have flushed and locked the ranges of the source and destination
	 * inodes, we also have locked the inodes, so we are safe to करो a
	 * reservation here. Also we must not करो the reservation जबतक holding
	 * a transaction खोलो, otherwise we would deadlock.
	 */
	ret = btrfs_delalloc_reserve_space(inode, &data_reserved, file_offset,
					   block_size);
	अगर (ret)
		जाओ out;

	page = find_or_create_page(mapping, file_offset >> PAGE_SHIFT,
				   btrfs_alloc_ग_लिखो_mask(mapping));
	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	ret = set_page_extent_mapped(page);
	अगर (ret < 0)
		जाओ out_unlock;

	clear_extent_bit(&inode->io_tree, file_offset, range_end,
			 EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING | EXTENT_DEFRAG,
			 0, 0, शून्य);
	ret = btrfs_set_extent_delalloc(inode, file_offset, range_end, 0, शून्य);
	अगर (ret)
		जाओ out_unlock;

	/*
	 * After dirtying the page our caller will need to start a transaction,
	 * and अगर we are low on metadata मुक्त space, that can cause flushing of
	 * delalloc क्रम all inodes in order to get metadata space released.
	 * However we are holding the range locked क्रम the whole duration of
	 * the clone/dedupe operation, so we may deadlock अगर that happens and no
	 * other task releases enough space. So mark this inode as not being
	 * possible to flush to aव्योम such deadlock. We will clear that flag
	 * when we finish cloning all extents, since a transaction is started
	 * after finding each extent to clone.
	 */
	set_bit(BTRFS_INODE_NO_DELALLOC_FLUSH, &inode->runसमय_flags);

	अगर (comp_type == BTRFS_COMPRESS_NONE) अणु
		स_नकल_to_page(page, 0, data_start, datal);
		flush_dcache_page(page);
	पूर्ण अन्यथा अणु
		ret = btrfs_decompress(comp_type, data_start, page, 0,
				       अंतरभूत_size, datal);
		अगर (ret)
			जाओ out_unlock;
		flush_dcache_page(page);
	पूर्ण

	/*
	 * If our अंतरभूत data is smaller then the block/page size, then the
	 * reमुख्यing of the block/page is equivalent to zeroes. We had something
	 * like the following करोne:
	 *
	 * $ xfs_io -f -c "pwrite -S 0xab 0 500" file
	 * $ sync  # (or fsync)
	 * $ xfs_io -c "falloc 0 4K" file
	 * $ xfs_io -c "pwrite -S 0xcd 4K 4K"
	 *
	 * So what's in the range [500, 4095] corresponds to zeroes.
	 */
	अगर (datal < block_size) अणु
		memzero_page(page, datal, block_size - datal);
		flush_dcache_page(page);
	पूर्ण

	SetPageUptodate(page);
	ClearPageChecked(page);
	set_page_dirty(page);
out_unlock:
	अगर (page) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण
	अगर (ret)
		btrfs_delalloc_release_space(inode, data_reserved, file_offset,
					     block_size, true);
	btrfs_delalloc_release_extents(inode, block_size);
out:
	extent_changeset_मुक्त(data_reserved);

	वापस ret;
पूर्ण

/*
 * Deal with cloning of अंतरभूत extents. We try to copy the अंतरभूत extent from
 * the source inode to destination inode when possible. When not possible we
 * copy the अंतरभूत extent's data पूर्णांकo the respective page of the inode.
 */
अटल पूर्णांक clone_copy_अंतरभूत_extent(काष्ठा inode *dst,
				    काष्ठा btrfs_path *path,
				    काष्ठा btrfs_key *new_key,
				    स्थिर u64 drop_start,
				    स्थिर u64 datal,
				    स्थिर u64 size,
				    स्थिर u8 comp_type,
				    अक्षर *अंतरभूत_data,
				    काष्ठा btrfs_trans_handle **trans_out)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dst->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(dst)->root;
	स्थिर u64 aligned_end = ALIGN(new_key->offset + datal,
				      fs_info->sectorsize);
	काष्ठा btrfs_trans_handle *trans = शून्य;
	काष्ठा btrfs_drop_extents_args drop_args = अणु 0 पूर्ण;
	पूर्णांक ret;
	काष्ठा btrfs_key key;

	अगर (new_key->offset > 0) अणु
		ret = copy_अंतरभूत_to_page(BTRFS_I(dst), new_key->offset,
					  अंतरभूत_data, size, datal, comp_type);
		जाओ out;
	पूर्ण

	key.objectid = btrfs_ino(BTRFS_I(dst));
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0) अणु
		वापस ret;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		अगर (path->slots[0] >= btrfs_header_nritems(path->nodes[0])) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				वापस ret;
			अन्यथा अगर (ret > 0)
				जाओ copy_अंतरभूत_extent;
		पूर्ण
		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
		अगर (key.objectid == btrfs_ino(BTRFS_I(dst)) &&
		    key.type == BTRFS_EXTENT_DATA_KEY) अणु
			/*
			 * There's an implicit hole at file offset 0, copy the
			 * अंतरभूत extent's data to the page.
			 */
			ASSERT(key.offset > 0);
			जाओ copy_to_page;
		पूर्ण
	पूर्ण अन्यथा अगर (i_size_पढ़ो(dst) <= datal) अणु
		काष्ठा btrfs_file_extent_item *ei;

		ei = btrfs_item_ptr(path->nodes[0], path->slots[0],
				    काष्ठा btrfs_file_extent_item);
		/*
		 * If it's an अंतरभूत extent replace it with the source अंतरभूत
		 * extent, otherwise copy the source अंतरभूत extent data पूर्णांकo
		 * the respective page at the destination inode.
		 */
		अगर (btrfs_file_extent_type(path->nodes[0], ei) ==
		    BTRFS_खाता_EXTENT_INLINE)
			जाओ copy_अंतरभूत_extent;

		जाओ copy_to_page;
	पूर्ण

copy_अंतरभूत_extent:
	/*
	 * We have no extent items, or we have an extent at offset 0 which may
	 * or may not be अंतरभूतd. All these हालs are dealt the same way.
	 */
	अगर (i_size_पढ़ो(dst) > datal) अणु
		/*
		 * At the destination offset 0 we have either a hole, a regular
		 * extent or an अंतरभूत extent larger then the one we want to
		 * clone. Deal with all these हालs by copying the अंतरभूत extent
		 * data पूर्णांकo the respective page at the destination inode.
		 */
		जाओ copy_to_page;
	पूर्ण

	/*
	 * Release path beक्रमe starting a new transaction so we करोn't hold locks
	 * that would confuse lockdep.
	 */
	btrfs_release_path(path);
	/*
	 * If we end up here it means were copy the अंतरभूत extent पूर्णांकo a leaf
	 * of the destination inode. We know we will drop or adjust at most one
	 * extent item in the destination root.
	 *
	 * 1 unit - adjusting old extent (we may have to split it)
	 * 1 unit - add new extent
	 * 1 unit - inode update
	 */
	trans = btrfs_start_transaction(root, 3);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		trans = शून्य;
		जाओ out;
	पूर्ण
	drop_args.path = path;
	drop_args.start = drop_start;
	drop_args.end = aligned_end;
	drop_args.drop_cache = true;
	ret = btrfs_drop_extents(trans, root, BTRFS_I(dst), &drop_args);
	अगर (ret)
		जाओ out;
	ret = btrfs_insert_empty_item(trans, root, path, new_key, size);
	अगर (ret)
		जाओ out;

	ग_लिखो_extent_buffer(path->nodes[0], अंतरभूत_data,
			    btrfs_item_ptr_offset(path->nodes[0],
						  path->slots[0]),
			    size);
	btrfs_update_inode_bytes(BTRFS_I(dst), datal, drop_args.bytes_found);
	set_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &BTRFS_I(dst)->runसमय_flags);
	ret = btrfs_inode_set_file_extent_range(BTRFS_I(dst), 0, aligned_end);
out:
	अगर (!ret && !trans) अणु
		/*
		 * No transaction here means we copied the अंतरभूत extent पूर्णांकo a
		 * page of the destination inode.
		 *
		 * 1 unit to update inode item
		 */
		trans = btrfs_start_transaction(root, 1);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			trans = शून्य;
		पूर्ण
	पूर्ण
	अगर (ret && trans) अणु
		btrfs_पात_transaction(trans, ret);
		btrfs_end_transaction(trans);
	पूर्ण
	अगर (!ret)
		*trans_out = trans;

	वापस ret;

copy_to_page:
	/*
	 * Release our path because we करोn't need it anymore and also because
	 * copy_अंतरभूत_to_page() needs to reserve data and metadata, which may
	 * need to flush delalloc when we are low on available space and
	 * thereक्रमe cause a deadlock अगर ग_लिखोback of an अंतरभूत extent needs to
	 * ग_लिखो to the same leaf or an ordered extent completion needs to ग_लिखो
	 * to the same leaf.
	 */
	btrfs_release_path(path);

	ret = copy_अंतरभूत_to_page(BTRFS_I(dst), new_key->offset,
				  अंतरभूत_data, size, datal, comp_type);
	जाओ out;
पूर्ण

/**
 * btrfs_clone() - clone a range from inode file to another
 *
 * @src: Inode to clone from
 * @inode: Inode to clone to
 * @off: Offset within source to start clone from
 * @olen: Original length, passed by user, of range to clone
 * @olen_aligned: Block-aligned value of olen
 * @destoff: Offset within @inode to start clone
 * @no_समय_update: Whether to update mसमय/स_समय on the target inode
 */
अटल पूर्णांक btrfs_clone(काष्ठा inode *src, काष्ठा inode *inode,
		       स्थिर u64 off, स्थिर u64 olen, स्थिर u64 olen_aligned,
		       स्थिर u64 destoff, पूर्णांक no_समय_update)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_trans_handle *trans;
	अक्षर *buf = शून्य;
	काष्ठा btrfs_key key;
	u32 nritems;
	पूर्णांक slot;
	पूर्णांक ret;
	स्थिर u64 len = olen_aligned;
	u64 last_dest_end = destoff;

	ret = -ENOMEM;
	buf = kvदो_स्मृति(fs_info->nodesize, GFP_KERNEL);
	अगर (!buf)
		वापस ret;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		kvमुक्त(buf);
		वापस ret;
	पूर्ण

	path->पढ़ोa = READA_FORWARD;
	/* Clone data */
	key.objectid = btrfs_ino(BTRFS_I(src));
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = off;

	जबतक (1) अणु
		u64 next_key_min_offset = key.offset + 1;
		काष्ठा btrfs_file_extent_item *extent;
		u64 extent_gen;
		पूर्णांक type;
		u32 size;
		काष्ठा btrfs_key new_key;
		u64 disko = 0, diskl = 0;
		u64 datao = 0, datal = 0;
		u8 comp;
		u64 drop_start;

		/* Note the key will change type as we walk through the tree */
		ret = btrfs_search_slot(शून्य, BTRFS_I(src)->root, &key, path,
				0, 0);
		अगर (ret < 0)
			जाओ out;
		/*
		 * First search, अगर no extent item that starts at offset off was
		 * found but the previous item is an extent item, it's possible
		 * it might overlap our target range, thereक्रमe process it.
		 */
		अगर (key.offset == off && ret > 0 && path->slots[0] > 0) अणु
			btrfs_item_key_to_cpu(path->nodes[0], &key,
					      path->slots[0] - 1);
			अगर (key.type == BTRFS_EXTENT_DATA_KEY)
				path->slots[0]--;
		पूर्ण

		nritems = btrfs_header_nritems(path->nodes[0]);
process_slot:
		अगर (path->slots[0] >= nritems) अणु
			ret = btrfs_next_leaf(BTRFS_I(src)->root, path);
			अगर (ret < 0)
				जाओ out;
			अगर (ret > 0)
				अवरोध;
			nritems = btrfs_header_nritems(path->nodes[0]);
		पूर्ण
		leaf = path->nodes[0];
		slot = path->slots[0];

		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.type > BTRFS_EXTENT_DATA_KEY ||
		    key.objectid != btrfs_ino(BTRFS_I(src)))
			अवरोध;

		ASSERT(key.type == BTRFS_EXTENT_DATA_KEY);

		extent = btrfs_item_ptr(leaf, slot,
					काष्ठा btrfs_file_extent_item);
		extent_gen = btrfs_file_extent_generation(leaf, extent);
		comp = btrfs_file_extent_compression(leaf, extent);
		type = btrfs_file_extent_type(leaf, extent);
		अगर (type == BTRFS_खाता_EXTENT_REG ||
		    type == BTRFS_खाता_EXTENT_PREALLOC) अणु
			disko = btrfs_file_extent_disk_bytenr(leaf, extent);
			diskl = btrfs_file_extent_disk_num_bytes(leaf, extent);
			datao = btrfs_file_extent_offset(leaf, extent);
			datal = btrfs_file_extent_num_bytes(leaf, extent);
		पूर्ण अन्यथा अगर (type == BTRFS_खाता_EXTENT_INLINE) अणु
			/* Take upper bound, may be compressed */
			datal = btrfs_file_extent_ram_bytes(leaf, extent);
		पूर्ण

		/*
		 * The first search might have left us at an extent item that
		 * ends beक्रमe our target range's start, can happen अगर we have
		 * holes and NO_HOLES feature enabled.
		 */
		अगर (key.offset + datal <= off) अणु
			path->slots[0]++;
			जाओ process_slot;
		पूर्ण अन्यथा अगर (key.offset >= off + len) अणु
			अवरोध;
		पूर्ण
		next_key_min_offset = key.offset + datal;
		size = btrfs_item_size_nr(leaf, slot);
		पढ़ो_extent_buffer(leaf, buf, btrfs_item_ptr_offset(leaf, slot),
				   size);

		btrfs_release_path(path);

		स_नकल(&new_key, &key, माप(new_key));
		new_key.objectid = btrfs_ino(BTRFS_I(inode));
		अगर (off <= key.offset)
			new_key.offset = key.offset + destoff - off;
		अन्यथा
			new_key.offset = destoff;

		/*
		 * Deal with a hole that करोesn't have an extent item that
		 * represents it (NO_HOLES feature enabled).
		 * This hole is either in the middle of the cloning range or at
		 * the beginning (fully overlaps it or partially overlaps it).
		 */
		अगर (new_key.offset != last_dest_end)
			drop_start = last_dest_end;
		अन्यथा
			drop_start = new_key.offset;

		अगर (type == BTRFS_खाता_EXTENT_REG ||
		    type == BTRFS_खाता_EXTENT_PREALLOC) अणु
			काष्ठा btrfs_replace_extent_info clone_info;

			/*
			 *    a  | --- range to clone ---|  b
			 * | ------------- extent ------------- |
			 */

			/* Subtract range b */
			अगर (key.offset + datal > off + len)
				datal = off + len - key.offset;

			/* Subtract range a */
			अगर (off > key.offset) अणु
				datao += off - key.offset;
				datal -= off - key.offset;
			पूर्ण

			clone_info.disk_offset = disko;
			clone_info.disk_len = diskl;
			clone_info.data_offset = datao;
			clone_info.data_len = datal;
			clone_info.file_offset = new_key.offset;
			clone_info.extent_buf = buf;
			clone_info.is_new_extent = false;
			ret = btrfs_replace_file_extents(BTRFS_I(inode), path,
					drop_start, new_key.offset + datal - 1,
					&clone_info, &trans);
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अगर (type == BTRFS_खाता_EXTENT_INLINE) अणु
			/*
			 * Inline extents always have to start at file offset 0
			 * and can never be bigger then the sector size. We can
			 * never clone only parts of an अंतरभूत extent, since all
			 * reflink operations must start at a sector size aligned
			 * offset, and the length must be aligned too or end at
			 * the i_size (which implies the whole अंतरभूतd data).
			 */
			ASSERT(key.offset == 0);
			ASSERT(datal <= fs_info->sectorsize);
			अगर (key.offset != 0 || datal > fs_info->sectorsize)
				वापस -EUCLEAN;

			ret = clone_copy_अंतरभूत_extent(inode, path, &new_key,
						       drop_start, datal, size,
						       comp, buf, &trans);
			अगर (ret)
				जाओ out;
		पूर्ण

		btrfs_release_path(path);

		/*
		 * If this is a new extent update the last_reflink_trans of both
		 * inodes. This is used by fsync to make sure it करोes not log
		 * multiple checksum items with overlapping ranges. For older
		 * extents we करोn't need to करो it since inode logging skips the
		 * checksums क्रम older extents. Also ignore holes and अंतरभूत
		 * extents because they करोn't have checksums in the csum tree.
		 */
		अगर (extent_gen == trans->transid && disko > 0) अणु
			BTRFS_I(src)->last_reflink_trans = trans->transid;
			BTRFS_I(inode)->last_reflink_trans = trans->transid;
		पूर्ण

		last_dest_end = ALIGN(new_key.offset + datal,
				      fs_info->sectorsize);
		ret = clone_finish_inode_update(trans, inode, last_dest_end,
						destoff, olen, no_समय_update);
		अगर (ret)
			जाओ out;
		अगर (new_key.offset + datal >= destoff + len)
			अवरोध;

		btrfs_release_path(path);
		key.offset = next_key_min_offset;

		अगर (fatal_संकेत_pending(current)) अणु
			ret = -EINTR;
			जाओ out;
		पूर्ण

		cond_resched();
	पूर्ण
	ret = 0;

	अगर (last_dest_end < destoff + len) अणु
		/*
		 * We have an implicit hole that fully or partially overlaps our
		 * cloning range at its end. This means that we either have the
		 * NO_HOLES feature enabled or the implicit hole happened due to
		 * mixing buffered and direct IO ग_लिखोs against this file.
		 */
		btrfs_release_path(path);

		/*
		 * When using NO_HOLES and we are cloning a range that covers
		 * only a hole (no extents) पूर्णांकo a range beyond the current
		 * i_size, punching a hole in the target range will not create
		 * an extent map defining a hole, because the range starts at or
		 * beyond current i_size. If the file previously had an i_size
		 * greater than the new i_size set by this clone operation, we
		 * need to make sure the next fsync is a full fsync, so that it
		 * detects and logs a hole covering a range from the current
		 * i_size to the new i_size. If the clone range covers extents,
		 * besides a hole, then we know the full sync flag was alपढ़ोy
		 * set by previous calls to btrfs_replace_file_extents() that
		 * replaced file extent items.
		 */
		अगर (last_dest_end >= i_size_पढ़ो(inode))
			set_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
				&BTRFS_I(inode)->runसमय_flags);

		ret = btrfs_replace_file_extents(BTRFS_I(inode), path,
				last_dest_end, destoff + len - 1, शून्य, &trans);
		अगर (ret)
			जाओ out;

		ret = clone_finish_inode_update(trans, inode, destoff + len,
						destoff, olen, no_समय_update);
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	kvमुक्त(buf);
	clear_bit(BTRFS_INODE_NO_DELALLOC_FLUSH, &BTRFS_I(inode)->runसमय_flags);

	वापस ret;
पूर्ण

अटल व्योम btrfs_द्विगुन_extent_unlock(काष्ठा inode *inode1, u64 loff1,
				       काष्ठा inode *inode2, u64 loff2, u64 len)
अणु
	unlock_extent(&BTRFS_I(inode1)->io_tree, loff1, loff1 + len - 1);
	unlock_extent(&BTRFS_I(inode2)->io_tree, loff2, loff2 + len - 1);
पूर्ण

अटल व्योम btrfs_द्विगुन_extent_lock(काष्ठा inode *inode1, u64 loff1,
				     काष्ठा inode *inode2, u64 loff2, u64 len)
अणु
	अगर (inode1 < inode2) अणु
		swap(inode1, inode2);
		swap(loff1, loff2);
	पूर्ण अन्यथा अगर (inode1 == inode2 && loff2 < loff1) अणु
		swap(loff1, loff2);
	पूर्ण
	lock_extent(&BTRFS_I(inode1)->io_tree, loff1, loff1 + len - 1);
	lock_extent(&BTRFS_I(inode2)->io_tree, loff2, loff2 + len - 1);
पूर्ण

अटल व्योम btrfs_द्विगुन_mmap_lock(काष्ठा inode *inode1, काष्ठा inode *inode2)
अणु
	अगर (inode1 < inode2)
		swap(inode1, inode2);
	करोwn_ग_लिखो(&BTRFS_I(inode1)->i_mmap_lock);
	करोwn_ग_लिखो_nested(&BTRFS_I(inode2)->i_mmap_lock, SINGLE_DEPTH_NESTING);
पूर्ण

अटल व्योम btrfs_द्विगुन_mmap_unlock(काष्ठा inode *inode1, काष्ठा inode *inode2)
अणु
	up_ग_लिखो(&BTRFS_I(inode1)->i_mmap_lock);
	up_ग_लिखो(&BTRFS_I(inode2)->i_mmap_lock);
पूर्ण

अटल पूर्णांक btrfs_extent_same_range(काष्ठा inode *src, u64 loff, u64 len,
				   काष्ठा inode *dst, u64 dst_loff)
अणु
	स्थिर u64 bs = BTRFS_I(src)->root->fs_info->sb->s_blocksize;
	पूर्णांक ret;

	/*
	 * Lock destination range to serialize with concurrent पढ़ोpages() and
	 * source range to serialize with relocation.
	 */
	btrfs_द्विगुन_extent_lock(src, loff, dst, dst_loff, len);
	ret = btrfs_clone(src, dst, loff, len, ALIGN(len, bs), dst_loff, 1);
	btrfs_द्विगुन_extent_unlock(src, loff, dst, dst_loff, len);

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_extent_same(काष्ठा inode *src, u64 loff, u64 olen,
			     काष्ठा inode *dst, u64 dst_loff)
अणु
	पूर्णांक ret;
	u64 i, tail_len, chunk_count;
	काष्ठा btrfs_root *root_dst = BTRFS_I(dst)->root;

	spin_lock(&root_dst->root_item_lock);
	अगर (root_dst->send_in_progress) अणु
		btrfs_warn_rl(root_dst->fs_info,
"cannot deduplicate to root %llu while send operations are using it (%d in progress)",
			      root_dst->root_key.objectid,
			      root_dst->send_in_progress);
		spin_unlock(&root_dst->root_item_lock);
		वापस -EAGAIN;
	पूर्ण
	root_dst->dedupe_in_progress++;
	spin_unlock(&root_dst->root_item_lock);

	tail_len = olen % BTRFS_MAX_DEDUPE_LEN;
	chunk_count = भाग_u64(olen, BTRFS_MAX_DEDUPE_LEN);

	क्रम (i = 0; i < chunk_count; i++) अणु
		ret = btrfs_extent_same_range(src, loff, BTRFS_MAX_DEDUPE_LEN,
					      dst, dst_loff);
		अगर (ret)
			जाओ out;

		loff += BTRFS_MAX_DEDUPE_LEN;
		dst_loff += BTRFS_MAX_DEDUPE_LEN;
	पूर्ण

	अगर (tail_len > 0)
		ret = btrfs_extent_same_range(src, loff, tail_len, dst, dst_loff);
out:
	spin_lock(&root_dst->root_item_lock);
	root_dst->dedupe_in_progress--;
	spin_unlock(&root_dst->root_item_lock);

	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_clone_files(काष्ठा file *file, काष्ठा file *file_src,
					u64 off, u64 olen, u64 destoff)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा inode *src = file_inode(file_src);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	पूर्णांक ret;
	पूर्णांक wb_ret;
	u64 len = olen;
	u64 bs = fs_info->sb->s_blocksize;

	/*
	 * VFS's generic_remap_file_range_prep() protects us from cloning the
	 * eof block पूर्णांकo the middle of a file, which would result in corruption
	 * अगर the file size is not blocksize aligned. So we करोn't need to check
	 * क्रम that हाल here.
	 */
	अगर (off + len == src->i_size)
		len = ALIGN(src->i_size, bs) - off;

	अगर (destoff > inode->i_size) अणु
		स्थिर u64 wb_start = ALIGN_DOWN(inode->i_size, bs);

		ret = btrfs_cont_expand(BTRFS_I(inode), inode->i_size, destoff);
		अगर (ret)
			वापस ret;
		/*
		 * We may have truncated the last block अगर the inode's size is
		 * not sector size aligned, so we need to रुको क्रम ग_लिखोback to
		 * complete beक्रमe proceeding further, otherwise we can race
		 * with cloning and attempt to increment a reference to an
		 * extent that no दीर्घer exists (ग_लिखोback completed right after
		 * we found the previous extent covering eof and beक्रमe we
		 * attempted to increment its reference count).
		 */
		ret = btrfs_रुको_ordered_range(inode, wb_start,
					       destoff - wb_start);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Lock destination range to serialize with concurrent पढ़ोpages() and
	 * source range to serialize with relocation.
	 */
	btrfs_द्विगुन_extent_lock(src, off, inode, destoff, len);
	ret = btrfs_clone(src, inode, off, olen, len, destoff, 0);
	btrfs_द्विगुन_extent_unlock(src, off, inode, destoff, len);

	/*
	 * We may have copied an अंतरभूत extent पूर्णांकo a page of the destination
	 * range, so रुको क्रम ग_लिखोback to complete beक्रमe truncating pages
	 * from the page cache. This is a rare हाल.
	 */
	wb_ret = btrfs_रुको_ordered_range(inode, destoff, len);
	ret = ret ? ret : wb_ret;
	/*
	 * Truncate page cache pages so that future पढ़ोs will see the cloned
	 * data immediately and not the previous data.
	 */
	truncate_inode_pages_range(&inode->i_data,
				round_करोwn(destoff, PAGE_SIZE),
				round_up(destoff + len, PAGE_SIZE) - 1);

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_remap_file_range_prep(काष्ठा file *file_in, loff_t pos_in,
				       काष्ठा file *file_out, loff_t pos_out,
				       loff_t *len, अचिन्हित पूर्णांक remap_flags)
अणु
	काष्ठा inode *inode_in = file_inode(file_in);
	काष्ठा inode *inode_out = file_inode(file_out);
	u64 bs = BTRFS_I(inode_out)->root->fs_info->sb->s_blocksize;
	bool same_inode = inode_out == inode_in;
	u64 wb_len;
	पूर्णांक ret;

	अगर (!(remap_flags & REMAP_खाता_DEDUP)) अणु
		काष्ठा btrfs_root *root_out = BTRFS_I(inode_out)->root;

		अगर (btrfs_root_पढ़ोonly(root_out))
			वापस -EROFS;

		अगर (file_in->f_path.mnt != file_out->f_path.mnt ||
		    inode_in->i_sb != inode_out->i_sb)
			वापस -EXDEV;
	पूर्ण

	/* Don't make the dst file partly checksummed */
	अगर ((BTRFS_I(inode_in)->flags & BTRFS_INODE_NODATASUM) !=
	    (BTRFS_I(inode_out)->flags & BTRFS_INODE_NODATASUM)) अणु
		वापस -EINVAL;
	पूर्ण

	/*
	 * Now that the inodes are locked, we need to start ग_लिखोback ourselves
	 * and can not rely on the ग_लिखोback from the VFS's generic helper
	 * generic_remap_file_range_prep() because:
	 *
	 * 1) For compression we must call filemap_fdataग_लिखो_range() range
	 *    twice (btrfs_fdataग_लिखो_range() करोes it क्रम us), and the generic
	 *    helper only calls it once;
	 *
	 * 2) filemap_fdataग_लिखो_range(), called by the generic helper only
	 *    रुकोs क्रम the ग_लिखोback to complete, i.e. क्रम IO to be करोne, and
	 *    not क्रम the ordered extents to complete. We need to रुको क्रम them
	 *    to complete so that new file extent items are in the fs tree.
	 */
	अगर (*len == 0 && !(remap_flags & REMAP_खाता_DEDUP))
		wb_len = ALIGN(inode_in->i_size, bs) - ALIGN_DOWN(pos_in, bs);
	अन्यथा
		wb_len = ALIGN(*len, bs);

	/*
	 * Since we करोn't lock ranges, रुको क्रम ongoing lockless dio ग_लिखोs (as
	 * any in progress could create its ordered extents after we रुको क्रम
	 * existing ordered extents below).
	 */
	inode_dio_रुको(inode_in);
	अगर (!same_inode)
		inode_dio_रुको(inode_out);

	/*
	 * Workaround to make sure NOCOW buffered ग_लिखो reach disk as NOCOW.
	 *
	 * Btrfs' back references करो not have a block level granularity, they
	 * work at the whole extent level.
	 * NOCOW buffered ग_लिखो without data space reserved may not be able
	 * to fall back to CoW due to lack of data space, thus could cause
	 * data loss.
	 *
	 * Here we take a लघुcut by flushing the whole inode, so that all
	 * nocow ग_लिखो should reach disk as nocow beक्रमe we increase the
	 * reference of the extent. We could करो better by only flushing NOCOW
	 * data, but that needs extra accounting.
	 *
	 * Also we करोn't need to check ASYNC_EXTENT, as async extent will be
	 * CoWed anyway, not affecting nocow part.
	 */
	ret = filemap_flush(inode_in->i_mapping);
	अगर (ret < 0)
		वापस ret;

	ret = btrfs_रुको_ordered_range(inode_in, ALIGN_DOWN(pos_in, bs),
				       wb_len);
	अगर (ret < 0)
		वापस ret;
	ret = btrfs_रुको_ordered_range(inode_out, ALIGN_DOWN(pos_out, bs),
				       wb_len);
	अगर (ret < 0)
		वापस ret;

	वापस generic_remap_file_range_prep(file_in, pos_in, file_out, pos_out,
					    len, remap_flags);
पूर्ण

अटल bool file_sync_ग_लिखो(स्थिर काष्ठा file *file)
अणु
	अगर (file->f_flags & (__O_SYNC | O_DSYNC))
		वापस true;
	अगर (IS_SYNC(file_inode(file)))
		वापस true;

	वापस false;
पूर्ण

loff_t btrfs_remap_file_range(काष्ठा file *src_file, loff_t off,
		काष्ठा file *dst_file, loff_t destoff, loff_t len,
		अचिन्हित पूर्णांक remap_flags)
अणु
	काष्ठा inode *src_inode = file_inode(src_file);
	काष्ठा inode *dst_inode = file_inode(dst_file);
	bool same_inode = dst_inode == src_inode;
	पूर्णांक ret;

	अगर (remap_flags & ~(REMAP_खाता_DEDUP | REMAP_खाता_ADVISORY))
		वापस -EINVAL;

	अगर (same_inode) अणु
		btrfs_inode_lock(src_inode, BTRFS_ILOCK_MMAP);
	पूर्ण अन्यथा अणु
		lock_two_nondirectories(src_inode, dst_inode);
		btrfs_द्विगुन_mmap_lock(src_inode, dst_inode);
	पूर्ण

	ret = btrfs_remap_file_range_prep(src_file, off, dst_file, destoff,
					  &len, remap_flags);
	अगर (ret < 0 || len == 0)
		जाओ out_unlock;

	अगर (remap_flags & REMAP_खाता_DEDUP)
		ret = btrfs_extent_same(src_inode, off, len, dst_inode, destoff);
	अन्यथा
		ret = btrfs_clone_files(dst_file, src_file, off, len, destoff);

out_unlock:
	अगर (same_inode) अणु
		btrfs_inode_unlock(src_inode, BTRFS_ILOCK_MMAP);
	पूर्ण अन्यथा अणु
		btrfs_द्विगुन_mmap_unlock(src_inode, dst_inode);
		unlock_two_nondirectories(src_inode, dst_inode);
	पूर्ण

	/*
	 * If either the source or the destination file was खोलोed with O_SYNC,
	 * O_DSYNC or has the S_SYNC attribute, fsync both the destination and
	 * source files/ranges, so that after a successful वापस (0) followed
	 * by a घातer failure results in the reflinked data to be पढ़ोable from
	 * both files/ranges.
	 */
	अगर (ret == 0 && len > 0 &&
	    (file_sync_ग_लिखो(src_file) || file_sync_ग_लिखो(dst_file))) अणु
		ret = btrfs_sync_file(src_file, off, off + len - 1, 0);
		अगर (ret == 0)
			ret = btrfs_sync_file(dst_file, destoff,
					      destoff + len - 1, 0);
	पूर्ण

	वापस ret < 0 ? ret : len;
पूर्ण
