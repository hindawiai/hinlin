<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <crypto/hash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bपन.स>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/compat.h>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/slab.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/btrfs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/uपन.स>
#समावेश <linux/magic.h>
#समावेश <linux/iversion.h>
#समावेश <linux/swap.h>
#समावेश <linux/migrate.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/iomap.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "btrfs_inode.h"
#समावेश "print-tree.h"
#समावेश "ordered-data.h"
#समावेश "xattr.h"
#समावेश "tree-log.h"
#समावेश "volumes.h"
#समावेश "compression.h"
#समावेश "locking.h"
#समावेश "free-space-cache.h"
#समावेश "props.h"
#समावेश "qgroup.h"
#समावेश "delalloc-space.h"
#समावेश "block-group.h"
#समावेश "space-info.h"
#समावेश "zoned.h"

काष्ठा btrfs_iget_args अणु
	u64 ino;
	काष्ठा btrfs_root *root;
पूर्ण;

काष्ठा btrfs_dio_data अणु
	u64 reserve;
	loff_t length;
	sमाप_प्रकार submitted;
	काष्ठा extent_changeset *data_reserved;
पूर्ण;

अटल स्थिर काष्ठा inode_operations btrfs_dir_inode_operations;
अटल स्थिर काष्ठा inode_operations btrfs_symlink_inode_operations;
अटल स्थिर काष्ठा inode_operations btrfs_special_inode_operations;
अटल स्थिर काष्ठा inode_operations btrfs_file_inode_operations;
अटल स्थिर काष्ठा address_space_operations btrfs_aops;
अटल स्थिर काष्ठा file_operations btrfs_dir_file_operations;

अटल काष्ठा kmem_cache *btrfs_inode_cachep;
काष्ठा kmem_cache *btrfs_trans_handle_cachep;
काष्ठा kmem_cache *btrfs_path_cachep;
काष्ठा kmem_cache *btrfs_मुक्त_space_cachep;
काष्ठा kmem_cache *btrfs_मुक्त_space_biपंचांगap_cachep;

अटल पूर्णांक btrfs_setsize(काष्ठा inode *inode, काष्ठा iattr *attr);
अटल पूर्णांक btrfs_truncate(काष्ठा inode *inode, bool skip_ग_लिखोback);
अटल पूर्णांक btrfs_finish_ordered_io(काष्ठा btrfs_ordered_extent *ordered_extent);
अटल noअंतरभूत पूर्णांक cow_file_range(काष्ठा btrfs_inode *inode,
				   काष्ठा page *locked_page,
				   u64 start, u64 end, पूर्णांक *page_started,
				   अचिन्हित दीर्घ *nr_written, पूर्णांक unlock);
अटल काष्ठा extent_map *create_io_em(काष्ठा btrfs_inode *inode, u64 start,
				       u64 len, u64 orig_start, u64 block_start,
				       u64 block_len, u64 orig_block_len,
				       u64 ram_bytes, पूर्णांक compress_type,
				       पूर्णांक type);

अटल व्योम __endio_ग_लिखो_update_ordered(काष्ठा btrfs_inode *inode,
					 स्थिर u64 offset, स्थिर u64 bytes,
					 स्थिर bool uptodate);

/*
 * btrfs_inode_lock - lock inode i_rwsem based on arguments passed
 *
 * ilock_flags can have the following bit set:
 *
 * BTRFS_ILOCK_SHARED - acquire a shared lock on the inode
 * BTRFS_ILOCK_TRY - try to acquire the lock, अगर fails on first attempt
 *		     वापस -EAGAIN
 * BTRFS_ILOCK_MMAP - acquire a ग_लिखो lock on the i_mmap_lock
 */
पूर्णांक btrfs_inode_lock(काष्ठा inode *inode, अचिन्हित पूर्णांक ilock_flags)
अणु
	अगर (ilock_flags & BTRFS_ILOCK_SHARED) अणु
		अगर (ilock_flags & BTRFS_ILOCK_TRY) अणु
			अगर (!inode_trylock_shared(inode))
				वापस -EAGAIN;
			अन्यथा
				वापस 0;
		पूर्ण
		inode_lock_shared(inode);
	पूर्ण अन्यथा अणु
		अगर (ilock_flags & BTRFS_ILOCK_TRY) अणु
			अगर (!inode_trylock(inode))
				वापस -EAGAIN;
			अन्यथा
				वापस 0;
		पूर्ण
		inode_lock(inode);
	पूर्ण
	अगर (ilock_flags & BTRFS_ILOCK_MMAP)
		करोwn_ग_लिखो(&BTRFS_I(inode)->i_mmap_lock);
	वापस 0;
पूर्ण

/*
 * btrfs_inode_unlock - unock inode i_rwsem
 *
 * ilock_flags should contain the same bits set as passed to btrfs_inode_lock()
 * to decide whether the lock acquired is shared or exclusive.
 */
व्योम btrfs_inode_unlock(काष्ठा inode *inode, अचिन्हित पूर्णांक ilock_flags)
अणु
	अगर (ilock_flags & BTRFS_ILOCK_MMAP)
		up_ग_लिखो(&BTRFS_I(inode)->i_mmap_lock);
	अगर (ilock_flags & BTRFS_ILOCK_SHARED)
		inode_unlock_shared(inode);
	अन्यथा
		inode_unlock(inode);
पूर्ण

/*
 * Cleanup all submitted ordered extents in specअगरied range to handle errors
 * from the btrfs_run_delalloc_range() callback.
 *
 * NOTE: caller must ensure that when an error happens, it can not call
 * extent_clear_unlock_delalloc() to clear both the bits EXTENT_DO_ACCOUNTING
 * and EXTENT_DELALLOC simultaneously, because that causes the reserved metadata
 * to be released, which we want to happen only when finishing the ordered
 * extent (btrfs_finish_ordered_io()).
 */
अटल अंतरभूत व्योम btrfs_cleanup_ordered_extents(काष्ठा btrfs_inode *inode,
						 काष्ठा page *locked_page,
						 u64 offset, u64 bytes)
अणु
	अचिन्हित दीर्घ index = offset >> PAGE_SHIFT;
	अचिन्हित दीर्घ end_index = (offset + bytes - 1) >> PAGE_SHIFT;
	u64 page_start = page_offset(locked_page);
	u64 page_end = page_start + PAGE_SIZE - 1;

	काष्ठा page *page;

	जबतक (index <= end_index) अणु
		page = find_get_page(inode->vfs_inode.i_mapping, index);
		index++;
		अगर (!page)
			जारी;
		ClearPagePrivate2(page);
		put_page(page);
	पूर्ण

	/*
	 * In हाल this page beदीर्घs to the delalloc range being instantiated
	 * then skip it, since the first page of a range is going to be
	 * properly cleaned up by the caller of run_delalloc_range
	 */
	अगर (page_start >= offset && page_end <= (offset + bytes - 1)) अणु
		offset += PAGE_SIZE;
		bytes -= PAGE_SIZE;
	पूर्ण

	वापस __endio_ग_लिखो_update_ordered(inode, offset, bytes, false);
पूर्ण

अटल पूर्णांक btrfs_dirty_inode(काष्ठा inode *inode);

अटल पूर्णांक btrfs_init_inode_security(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा inode *inode,  काष्ठा inode *dir,
				     स्थिर काष्ठा qstr *qstr)
अणु
	पूर्णांक err;

	err = btrfs_init_acl(trans, inode, dir);
	अगर (!err)
		err = btrfs_xattr_security_init(trans, inode, dir, qstr);
	वापस err;
पूर्ण

/*
 * this करोes all the hard work क्रम inserting an अंतरभूत extent पूर्णांकo
 * the btree.  The caller should have करोne a btrfs_drop_extents so that
 * no overlapping अंतरभूत items exist in the btree
 */
अटल पूर्णांक insert_अंतरभूत_extent(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_path *path, bool extent_inserted,
				काष्ठा btrfs_root *root, काष्ठा inode *inode,
				u64 start, माप_प्रकार size, माप_प्रकार compressed_size,
				पूर्णांक compress_type,
				काष्ठा page **compressed_pages)
अणु
	काष्ठा extent_buffer *leaf;
	काष्ठा page *page = शून्य;
	अक्षर *kaddr;
	अचिन्हित दीर्घ ptr;
	काष्ठा btrfs_file_extent_item *ei;
	पूर्णांक ret;
	माप_प्रकार cur_size = size;
	अचिन्हित दीर्घ offset;

	ASSERT((compressed_size > 0 && compressed_pages) ||
	       (compressed_size == 0 && !compressed_pages));

	अगर (compressed_size && compressed_pages)
		cur_size = compressed_size;

	अगर (!extent_inserted) अणु
		काष्ठा btrfs_key key;
		माप_प्रकार datasize;

		key.objectid = btrfs_ino(BTRFS_I(inode));
		key.offset = start;
		key.type = BTRFS_EXTENT_DATA_KEY;

		datasize = btrfs_file_extent_calc_अंतरभूत_size(cur_size);
		ret = btrfs_insert_empty_item(trans, root, path, &key,
					      datasize);
		अगर (ret)
			जाओ fail;
	पूर्ण
	leaf = path->nodes[0];
	ei = btrfs_item_ptr(leaf, path->slots[0],
			    काष्ठा btrfs_file_extent_item);
	btrfs_set_file_extent_generation(leaf, ei, trans->transid);
	btrfs_set_file_extent_type(leaf, ei, BTRFS_खाता_EXTENT_INLINE);
	btrfs_set_file_extent_encryption(leaf, ei, 0);
	btrfs_set_file_extent_other_encoding(leaf, ei, 0);
	btrfs_set_file_extent_ram_bytes(leaf, ei, size);
	ptr = btrfs_file_extent_अंतरभूत_start(ei);

	अगर (compress_type != BTRFS_COMPRESS_NONE) अणु
		काष्ठा page *cpage;
		पूर्णांक i = 0;
		जबतक (compressed_size > 0) अणु
			cpage = compressed_pages[i];
			cur_size = min_t(अचिन्हित दीर्घ, compressed_size,
				       PAGE_SIZE);

			kaddr = kmap_atomic(cpage);
			ग_लिखो_extent_buffer(leaf, kaddr, ptr, cur_size);
			kunmap_atomic(kaddr);

			i++;
			ptr += cur_size;
			compressed_size -= cur_size;
		पूर्ण
		btrfs_set_file_extent_compression(leaf, ei,
						  compress_type);
	पूर्ण अन्यथा अणु
		page = find_get_page(inode->i_mapping,
				     start >> PAGE_SHIFT);
		btrfs_set_file_extent_compression(leaf, ei, 0);
		kaddr = kmap_atomic(page);
		offset = offset_in_page(start);
		ग_लिखो_extent_buffer(leaf, kaddr + offset, ptr, size);
		kunmap_atomic(kaddr);
		put_page(page);
	पूर्ण
	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	/*
	 * We align size to sectorsize क्रम अंतरभूत extents just क्रम simplicity
	 * sake.
	 */
	size = ALIGN(size, root->fs_info->sectorsize);
	ret = btrfs_inode_set_file_extent_range(BTRFS_I(inode), start, size);
	अगर (ret)
		जाओ fail;

	/*
	 * we're an अंतरभूत extent, so nobody can
	 * extend the file past i_size without locking
	 * a page we alपढ़ोy have locked.
	 *
	 * We must करो any isize and inode updates
	 * beक्रमe we unlock the pages.  Otherwise we
	 * could end up racing with unlink.
	 */
	BTRFS_I(inode)->disk_i_size = inode->i_size;
fail:
	वापस ret;
पूर्ण


/*
 * conditionally insert an अंतरभूत extent पूर्णांकo the file.  This
 * करोes the checks required to make sure the data is small enough
 * to fit as an अंतरभूत extent.
 */
अटल noअंतरभूत पूर्णांक cow_file_range_अंतरभूत(काष्ठा btrfs_inode *inode, u64 start,
					  u64 end, माप_प्रकार compressed_size,
					  पूर्णांक compress_type,
					  काष्ठा page **compressed_pages)
अणु
	काष्ठा btrfs_drop_extents_args drop_args = अणु 0 पूर्ण;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_trans_handle *trans;
	u64 isize = i_size_पढ़ो(&inode->vfs_inode);
	u64 actual_end = min(end + 1, isize);
	u64 अंतरभूत_len = actual_end - start;
	u64 aligned_end = ALIGN(end, fs_info->sectorsize);
	u64 data_len = अंतरभूत_len;
	पूर्णांक ret;
	काष्ठा btrfs_path *path;

	अगर (compressed_size)
		data_len = compressed_size;

	अगर (start > 0 ||
	    actual_end > fs_info->sectorsize ||
	    data_len > BTRFS_MAX_INLINE_DATA_SIZE(fs_info) ||
	    (!compressed_size &&
	    (actual_end & (fs_info->sectorsize - 1)) == 0) ||
	    end + 1 < isize ||
	    data_len > fs_info->max_अंतरभूत) अणु
		वापस 1;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans)) अणु
		btrfs_मुक्त_path(path);
		वापस PTR_ERR(trans);
	पूर्ण
	trans->block_rsv = &inode->block_rsv;

	drop_args.path = path;
	drop_args.start = start;
	drop_args.end = aligned_end;
	drop_args.drop_cache = true;
	drop_args.replace_extent = true;

	अगर (compressed_size && compressed_pages)
		drop_args.extent_item_size = btrfs_file_extent_calc_अंतरभूत_size(
		   compressed_size);
	अन्यथा
		drop_args.extent_item_size = btrfs_file_extent_calc_अंतरभूत_size(
		    अंतरभूत_len);

	ret = btrfs_drop_extents(trans, root, inode, &drop_args);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	अगर (isize > actual_end)
		अंतरभूत_len = min_t(u64, isize, actual_end);
	ret = insert_अंतरभूत_extent(trans, path, drop_args.extent_inserted,
				   root, &inode->vfs_inode, start,
				   अंतरभूत_len, compressed_size,
				   compress_type, compressed_pages);
	अगर (ret && ret != -ENOSPC) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण अन्यथा अगर (ret == -ENOSPC) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	btrfs_update_inode_bytes(inode, अंतरभूत_len, drop_args.bytes_found);
	ret = btrfs_update_inode(trans, root, inode);
	अगर (ret && ret != -ENOSPC) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण अन्यथा अगर (ret == -ENOSPC) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	set_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &inode->runसमय_flags);
out:
	/*
	 * Don't क्रमget to मुक्त the reserved space, as क्रम अंतरभूतd extent
	 * it won't count as data extent, मुक्त them directly here.
	 * And at reserve समय, it's always aligned to page size, so
	 * just मुक्त one page here.
	 */
	btrfs_qgroup_मुक्त_data(inode, शून्य, 0, PAGE_SIZE);
	btrfs_मुक्त_path(path);
	btrfs_end_transaction(trans);
	वापस ret;
पूर्ण

काष्ठा async_extent अणु
	u64 start;
	u64 ram_size;
	u64 compressed_size;
	काष्ठा page **pages;
	अचिन्हित दीर्घ nr_pages;
	पूर्णांक compress_type;
	काष्ठा list_head list;
पूर्ण;

काष्ठा async_chunk अणु
	काष्ठा inode *inode;
	काष्ठा page *locked_page;
	u64 start;
	u64 end;
	अचिन्हित पूर्णांक ग_लिखो_flags;
	काष्ठा list_head extents;
	काष्ठा cgroup_subsys_state *blkcg_css;
	काष्ठा btrfs_work work;
	atomic_t *pending;
पूर्ण;

काष्ठा async_cow अणु
	/* Number of chunks in flight; must be first in the काष्ठाure */
	atomic_t num_chunks;
	काष्ठा async_chunk chunks[];
पूर्ण;

अटल noअंतरभूत पूर्णांक add_async_extent(काष्ठा async_chunk *cow,
				     u64 start, u64 ram_size,
				     u64 compressed_size,
				     काष्ठा page **pages,
				     अचिन्हित दीर्घ nr_pages,
				     पूर्णांक compress_type)
अणु
	काष्ठा async_extent *async_extent;

	async_extent = kदो_स्मृति(माप(*async_extent), GFP_NOFS);
	BUG_ON(!async_extent); /* -ENOMEM */
	async_extent->start = start;
	async_extent->ram_size = ram_size;
	async_extent->compressed_size = compressed_size;
	async_extent->pages = pages;
	async_extent->nr_pages = nr_pages;
	async_extent->compress_type = compress_type;
	list_add_tail(&async_extent->list, &cow->extents);
	वापस 0;
पूर्ण

/*
 * Check अगर the inode has flags compatible with compression
 */
अटल अंतरभूत bool inode_can_compress(काष्ठा btrfs_inode *inode)
अणु
	अगर (inode->flags & BTRFS_INODE_NODATACOW ||
	    inode->flags & BTRFS_INODE_NODATASUM)
		वापस false;
	वापस true;
पूर्ण

/*
 * Check अगर the inode needs to be submitted to compression, based on mount
 * options, defragmentation, properties or heuristics.
 */
अटल अंतरभूत पूर्णांक inode_need_compress(काष्ठा btrfs_inode *inode, u64 start,
				      u64 end)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;

	अगर (!inode_can_compress(inode)) अणु
		WARN(IS_ENABLED(CONFIG_BTRFS_DEBUG),
			KERN_ERR "BTRFS: unexpected compression for ino %llu\n",
			btrfs_ino(inode));
		वापस 0;
	पूर्ण
	/* क्रमce compress */
	अगर (btrfs_test_opt(fs_info, FORCE_COMPRESS))
		वापस 1;
	/* defrag ioctl */
	अगर (inode->defrag_compress)
		वापस 1;
	/* bad compression ratios */
	अगर (inode->flags & BTRFS_INODE_NOCOMPRESS)
		वापस 0;
	अगर (btrfs_test_opt(fs_info, COMPRESS) ||
	    inode->flags & BTRFS_INODE_COMPRESS ||
	    inode->prop_compress)
		वापस btrfs_compress_heuristic(&inode->vfs_inode, start, end);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम inode_should_defrag(काष्ठा btrfs_inode *inode,
		u64 start, u64 end, u64 num_bytes, u64 small_ग_लिखो)
अणु
	/* If this is a small ग_लिखो inside eof, kick off a defrag */
	अगर (num_bytes < small_ग_लिखो &&
	    (start > 0 || end + 1 < inode->disk_i_size))
		btrfs_add_inode_defrag(शून्य, inode);
पूर्ण

/*
 * we create compressed extents in two phases.  The first
 * phase compresses a range of pages that have alपढ़ोy been
 * locked (both pages and state bits are locked).
 *
 * This is करोne inside an ordered work queue, and the compression
 * is spपढ़ो across many cpus.  The actual IO submission is step
 * two, and the ordered work queue takes care of making sure that
 * happens in the same order things were put onto the queue by
 * ग_लिखोpages and मित्रs.
 *
 * If this code finds it can't get good compression, it माला_दो an
 * entry onto the work queue to ग_लिखो the uncompressed bytes.  This
 * makes sure that both compressed inodes and uncompressed inodes
 * are written in the same order that the flusher thपढ़ो sent them
 * करोwn.
 */
अटल noअंतरभूत पूर्णांक compress_file_range(काष्ठा async_chunk *async_chunk)
अणु
	काष्ठा inode *inode = async_chunk->inode;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	u64 blocksize = fs_info->sectorsize;
	u64 start = async_chunk->start;
	u64 end = async_chunk->end;
	u64 actual_end;
	u64 i_size;
	पूर्णांक ret = 0;
	काष्ठा page **pages = शून्य;
	अचिन्हित दीर्घ nr_pages;
	अचिन्हित दीर्घ total_compressed = 0;
	अचिन्हित दीर्घ total_in = 0;
	पूर्णांक i;
	पूर्णांक will_compress;
	पूर्णांक compress_type = fs_info->compress_type;
	पूर्णांक compressed_extents = 0;
	पूर्णांक redirty = 0;

	inode_should_defrag(BTRFS_I(inode), start, end, end - start + 1,
			SZ_16K);

	/*
	 * We need to save i_size beक्रमe now because it could change in between
	 * us evaluating the size and assigning it.  This is because we lock and
	 * unlock the page in truncate and fallocate, and then modअगरy the i_size
	 * later on.
	 *
	 * The barriers are to emulate READ_ONCE, हटाओ that once i_size_पढ़ो
	 * करोes that क्रम us.
	 */
	barrier();
	i_size = i_size_पढ़ो(inode);
	barrier();
	actual_end = min_t(u64, i_size, end + 1);
again:
	will_compress = 0;
	nr_pages = (end >> PAGE_SHIFT) - (start >> PAGE_SHIFT) + 1;
	BUILD_BUG_ON((BTRFS_MAX_COMPRESSED % PAGE_SIZE) != 0);
	nr_pages = min_t(अचिन्हित दीर्घ, nr_pages,
			BTRFS_MAX_COMPRESSED / PAGE_SIZE);

	/*
	 * we करोn't want to send crud past the end of i_size through
	 * compression, that's just a waste of CPU समय.  So, अगर the
	 * end of the file is beक्रमe the start of our current
	 * requested range of bytes, we bail out to the uncompressed
	 * cleanup code that can deal with all of this.
	 *
	 * It isn't really the fastest way to fix things, but this is a
	 * very uncommon corner.
	 */
	अगर (actual_end <= start)
		जाओ cleanup_and_bail_uncompressed;

	total_compressed = actual_end - start;

	/*
	 * skip compression क्रम a small file range(<=blocksize) that
	 * isn't an inline extent, since it doesn't save disk space at all.
	 */
	अगर (total_compressed <= blocksize &&
	   (start > 0 || end + 1 < BTRFS_I(inode)->disk_i_size))
		जाओ cleanup_and_bail_uncompressed;

	total_compressed = min_t(अचिन्हित दीर्घ, total_compressed,
			BTRFS_MAX_UNCOMPRESSED);
	total_in = 0;
	ret = 0;

	/*
	 * we करो compression क्रम mount -o compress and when the
	 * inode has not been flagged as nocompress.  This flag can
	 * change at any समय अगर we discover bad compression ratios.
	 */
	अगर (inode_need_compress(BTRFS_I(inode), start, end)) अणु
		WARN_ON(pages);
		pages = kसुस्मृति(nr_pages, माप(काष्ठा page *), GFP_NOFS);
		अगर (!pages) अणु
			/* just bail out to the uncompressed code */
			nr_pages = 0;
			जाओ cont;
		पूर्ण

		अगर (BTRFS_I(inode)->defrag_compress)
			compress_type = BTRFS_I(inode)->defrag_compress;
		अन्यथा अगर (BTRFS_I(inode)->prop_compress)
			compress_type = BTRFS_I(inode)->prop_compress;

		/*
		 * we need to call clear_page_dirty_क्रम_io on each
		 * page in the range.  Otherwise applications with the file
		 * mmap'd can wander in and change the page contents जबतक
		 * we are compressing them.
		 *
		 * If the compression fails क्रम any reason, we set the pages
		 * dirty again later on.
		 *
		 * Note that the reमुख्यing part is redirtied, the start poपूर्णांकer
		 * has moved, the end is the original one.
		 */
		अगर (!redirty) अणु
			extent_range_clear_dirty_क्रम_io(inode, start, end);
			redirty = 1;
		पूर्ण

		/* Compression level is applied here and only here */
		ret = btrfs_compress_pages(
			compress_type | (fs_info->compress_level << 4),
					   inode->i_mapping, start,
					   pages,
					   &nr_pages,
					   &total_in,
					   &total_compressed);

		अगर (!ret) अणु
			अचिन्हित दीर्घ offset = offset_in_page(total_compressed);
			काष्ठा page *page = pages[nr_pages - 1];

			/* zero the tail end of the last page, we might be
			 * sending it करोwn to disk
			 */
			अगर (offset)
				memzero_page(page, offset, PAGE_SIZE - offset);
			will_compress = 1;
		पूर्ण
	पूर्ण
cont:
	अगर (start == 0) अणु
		/* lets try to make an अंतरभूत extent */
		अगर (ret || total_in < actual_end) अणु
			/* we didn't compress the entire range, try
			 * to make an uncompressed अंतरभूत extent.
			 */
			ret = cow_file_range_अंतरभूत(BTRFS_I(inode), start, end,
						    0, BTRFS_COMPRESS_NONE,
						    शून्य);
		पूर्ण अन्यथा अणु
			/* try making a compressed अंतरभूत extent */
			ret = cow_file_range_अंतरभूत(BTRFS_I(inode), start, end,
						    total_compressed,
						    compress_type, pages);
		पूर्ण
		अगर (ret <= 0) अणु
			अचिन्हित दीर्घ clear_flags = EXTENT_DELALLOC |
				EXTENT_DELALLOC_NEW | EXTENT_DEFRAG |
				EXTENT_DO_ACCOUNTING;
			अचिन्हित दीर्घ page_error_op;

			page_error_op = ret < 0 ? PAGE_SET_ERROR : 0;

			/*
			 * अंतरभूत extent creation worked or वापसed error,
			 * we करोn't need to create any more async work items.
			 * Unlock and मुक्त up our temp pages.
			 *
			 * We use DO_ACCOUNTING here because we need the
			 * delalloc_release_metadata to be करोne _after_ we drop
			 * our outstanding extent क्रम clearing delalloc क्रम this
			 * range.
			 */
			extent_clear_unlock_delalloc(BTRFS_I(inode), start, end,
						     शून्य,
						     clear_flags,
						     PAGE_UNLOCK |
						     PAGE_START_WRITEBACK |
						     page_error_op |
						     PAGE_END_WRITEBACK);

			/*
			 * Ensure we only मुक्त the compressed pages अगर we have
			 * them allocated, as we can still reach here with
			 * inode_need_compress() == false.
			 */
			अगर (pages) अणु
				क्रम (i = 0; i < nr_pages; i++) अणु
					WARN_ON(pages[i]->mapping);
					put_page(pages[i]);
				पूर्ण
				kमुक्त(pages);
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (will_compress) अणु
		/*
		 * we aren't करोing an अंतरभूत extent round the compressed size
		 * up to a block size boundary so the allocator करोes sane
		 * things
		 */
		total_compressed = ALIGN(total_compressed, blocksize);

		/*
		 * one last check to make sure the compression is really a
		 * win, compare the page count पढ़ो with the blocks on disk,
		 * compression must मुक्त at least one sector size
		 */
		total_in = ALIGN(total_in, PAGE_SIZE);
		अगर (total_compressed + blocksize <= total_in) अणु
			compressed_extents++;

			/*
			 * The async work queues will take care of करोing actual
			 * allocation on disk क्रम these compressed pages, and
			 * will submit them to the elevator.
			 */
			add_async_extent(async_chunk, start, total_in,
					total_compressed, pages, nr_pages,
					compress_type);

			अगर (start + total_in < end) अणु
				start += total_in;
				pages = शून्य;
				cond_resched();
				जाओ again;
			पूर्ण
			वापस compressed_extents;
		पूर्ण
	पूर्ण
	अगर (pages) अणु
		/*
		 * the compression code ran but failed to make things smaller,
		 * मुक्त any pages it allocated and our page poपूर्णांकer array
		 */
		क्रम (i = 0; i < nr_pages; i++) अणु
			WARN_ON(pages[i]->mapping);
			put_page(pages[i]);
		पूर्ण
		kमुक्त(pages);
		pages = शून्य;
		total_compressed = 0;
		nr_pages = 0;

		/* flag the file so we करोn't compress in the future */
		अगर (!btrfs_test_opt(fs_info, FORCE_COMPRESS) &&
		    !(BTRFS_I(inode)->prop_compress)) अणु
			BTRFS_I(inode)->flags |= BTRFS_INODE_NOCOMPRESS;
		पूर्ण
	पूर्ण
cleanup_and_bail_uncompressed:
	/*
	 * No compression, but we still need to ग_लिखो the pages in the file
	 * we've been given so far.  redirty the locked page अगर it corresponds
	 * to our extent and set things up क्रम the async work queue to run
	 * cow_file_range to करो the normal delalloc dance.
	 */
	अगर (async_chunk->locked_page &&
	    (page_offset(async_chunk->locked_page) >= start &&
	     page_offset(async_chunk->locked_page)) <= end) अणु
		__set_page_dirty_nobuffers(async_chunk->locked_page);
		/* unlocked later on in the async handlers */
	पूर्ण

	अगर (redirty)
		extent_range_redirty_क्रम_io(inode, start, end);
	add_async_extent(async_chunk, start, end - start + 1, 0, शून्य, 0,
			 BTRFS_COMPRESS_NONE);
	compressed_extents++;

	वापस compressed_extents;
पूर्ण

अटल व्योम मुक्त_async_extent_pages(काष्ठा async_extent *async_extent)
अणु
	पूर्णांक i;

	अगर (!async_extent->pages)
		वापस;

	क्रम (i = 0; i < async_extent->nr_pages; i++) अणु
		WARN_ON(async_extent->pages[i]->mapping);
		put_page(async_extent->pages[i]);
	पूर्ण
	kमुक्त(async_extent->pages);
	async_extent->nr_pages = 0;
	async_extent->pages = शून्य;
पूर्ण

/*
 * phase two of compressed ग_लिखोback.  This is the ordered portion
 * of the code, which only माला_लो called in the order the work was
 * queued.  We walk all the async extents created by compress_file_range
 * and send them करोwn to the disk.
 */
अटल noअंतरभूत व्योम submit_compressed_extents(काष्ठा async_chunk *async_chunk)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(async_chunk->inode);
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा async_extent *async_extent;
	u64 alloc_hपूर्णांक = 0;
	काष्ठा btrfs_key ins;
	काष्ठा extent_map *em;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा extent_io_tree *io_tree = &inode->io_tree;
	पूर्णांक ret = 0;

again:
	जबतक (!list_empty(&async_chunk->extents)) अणु
		async_extent = list_entry(async_chunk->extents.next,
					  काष्ठा async_extent, list);
		list_del(&async_extent->list);

retry:
		lock_extent(io_tree, async_extent->start,
			    async_extent->start + async_extent->ram_size - 1);
		/* did the compression code fall back to uncompressed IO? */
		अगर (!async_extent->pages) अणु
			पूर्णांक page_started = 0;
			अचिन्हित दीर्घ nr_written = 0;

			/* allocate blocks */
			ret = cow_file_range(inode, async_chunk->locked_page,
					     async_extent->start,
					     async_extent->start +
					     async_extent->ram_size - 1,
					     &page_started, &nr_written, 0);

			/* JDM XXX */

			/*
			 * अगर page_started, cow_file_range inserted an
			 * अंतरभूत extent and took care of all the unlocking
			 * and IO क्रम us.  Otherwise, we need to submit
			 * all those pages करोwn to the drive.
			 */
			अगर (!page_started && !ret)
				extent_ग_लिखो_locked_range(&inode->vfs_inode,
						  async_extent->start,
						  async_extent->start +
						  async_extent->ram_size - 1,
						  WB_SYNC_ALL);
			अन्यथा अगर (ret && async_chunk->locked_page)
				unlock_page(async_chunk->locked_page);
			kमुक्त(async_extent);
			cond_resched();
			जारी;
		पूर्ण

		ret = btrfs_reserve_extent(root, async_extent->ram_size,
					   async_extent->compressed_size,
					   async_extent->compressed_size,
					   0, alloc_hपूर्णांक, &ins, 1, 1);
		अगर (ret) अणु
			मुक्त_async_extent_pages(async_extent);

			अगर (ret == -ENOSPC) अणु
				unlock_extent(io_tree, async_extent->start,
					      async_extent->start +
					      async_extent->ram_size - 1);

				/*
				 * we need to redirty the pages अगर we decide to
				 * fallback to uncompressed IO, otherwise we
				 * will not submit these pages करोwn to lower
				 * layers.
				 */
				extent_range_redirty_क्रम_io(&inode->vfs_inode,
						async_extent->start,
						async_extent->start +
						async_extent->ram_size - 1);

				जाओ retry;
			पूर्ण
			जाओ out_मुक्त;
		पूर्ण
		/*
		 * here we're करोing allocation and ग_लिखोback of the
		 * compressed pages
		 */
		em = create_io_em(inode, async_extent->start,
				  async_extent->ram_size, /* len */
				  async_extent->start, /* orig_start */
				  ins.objectid, /* block_start */
				  ins.offset, /* block_len */
				  ins.offset, /* orig_block_len */
				  async_extent->ram_size, /* ram_bytes */
				  async_extent->compress_type,
				  BTRFS_ORDERED_COMPRESSED);
		अगर (IS_ERR(em))
			/* ret value is not necessary due to व्योम function */
			जाओ out_मुक्त_reserve;
		मुक्त_extent_map(em);

		ret = btrfs_add_ordered_extent_compress(inode,
						async_extent->start,
						ins.objectid,
						async_extent->ram_size,
						ins.offset,
						async_extent->compress_type);
		अगर (ret) अणु
			btrfs_drop_extent_cache(inode, async_extent->start,
						async_extent->start +
						async_extent->ram_size - 1, 0);
			जाओ out_मुक्त_reserve;
		पूर्ण
		btrfs_dec_block_group_reservations(fs_info, ins.objectid);

		/*
		 * clear dirty, set ग_लिखोback and unlock the pages.
		 */
		extent_clear_unlock_delalloc(inode, async_extent->start,
				async_extent->start +
				async_extent->ram_size - 1,
				शून्य, EXTENT_LOCKED | EXTENT_DELALLOC,
				PAGE_UNLOCK | PAGE_START_WRITEBACK);
		अगर (btrfs_submit_compressed_ग_लिखो(inode, async_extent->start,
				    async_extent->ram_size,
				    ins.objectid,
				    ins.offset, async_extent->pages,
				    async_extent->nr_pages,
				    async_chunk->ग_लिखो_flags,
				    async_chunk->blkcg_css)) अणु
			काष्ठा page *p = async_extent->pages[0];
			स्थिर u64 start = async_extent->start;
			स्थिर u64 end = start + async_extent->ram_size - 1;

			p->mapping = inode->vfs_inode.i_mapping;
			btrfs_ग_लिखोpage_endio_finish_ordered(p, start, end, 0);

			p->mapping = शून्य;
			extent_clear_unlock_delalloc(inode, start, end, शून्य, 0,
						     PAGE_END_WRITEBACK |
						     PAGE_SET_ERROR);
			मुक्त_async_extent_pages(async_extent);
		पूर्ण
		alloc_hपूर्णांक = ins.objectid + ins.offset;
		kमुक्त(async_extent);
		cond_resched();
	पूर्ण
	वापस;
out_मुक्त_reserve:
	btrfs_dec_block_group_reservations(fs_info, ins.objectid);
	btrfs_मुक्त_reserved_extent(fs_info, ins.objectid, ins.offset, 1);
out_मुक्त:
	extent_clear_unlock_delalloc(inode, async_extent->start,
				     async_extent->start +
				     async_extent->ram_size - 1,
				     शून्य, EXTENT_LOCKED | EXTENT_DELALLOC |
				     EXTENT_DELALLOC_NEW |
				     EXTENT_DEFRAG | EXTENT_DO_ACCOUNTING,
				     PAGE_UNLOCK | PAGE_START_WRITEBACK |
				     PAGE_END_WRITEBACK | PAGE_SET_ERROR);
	मुक्त_async_extent_pages(async_extent);
	kमुक्त(async_extent);
	जाओ again;
पूर्ण

अटल u64 get_extent_allocation_hपूर्णांक(काष्ठा btrfs_inode *inode, u64 start,
				      u64 num_bytes)
अणु
	काष्ठा extent_map_tree *em_tree = &inode->extent_tree;
	काष्ठा extent_map *em;
	u64 alloc_hपूर्णांक = 0;

	पढ़ो_lock(&em_tree->lock);
	em = search_extent_mapping(em_tree, start, num_bytes);
	अगर (em) अणु
		/*
		 * अगर block start isn't an actual block number then find the
		 * first block in this inode and use that as a hपूर्णांक.  If that
		 * block is also bogus then just करोn't worry about it.
		 */
		अगर (em->block_start >= EXTENT_MAP_LAST_BYTE) अणु
			मुक्त_extent_map(em);
			em = search_extent_mapping(em_tree, 0, 0);
			अगर (em && em->block_start < EXTENT_MAP_LAST_BYTE)
				alloc_hपूर्णांक = em->block_start;
			अगर (em)
				मुक्त_extent_map(em);
		पूर्ण अन्यथा अणु
			alloc_hपूर्णांक = em->block_start;
			मुक्त_extent_map(em);
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&em_tree->lock);

	वापस alloc_hपूर्णांक;
पूर्ण

/*
 * when extent_io.c finds a delayed allocation range in the file,
 * the call backs end up in this code.  The basic idea is to
 * allocate extents on disk क्रम the range, and create ordered data काष्ठाs
 * in ram to track those extents.
 *
 * locked_page is the page that ग_लिखोpage had locked alपढ़ोy.  We use
 * it to make sure we करोn't करो extra locks or unlocks.
 *
 * *page_started is set to one अगर we unlock locked_page and करो everything
 * required to start IO on it.  It may be clean and alपढ़ोy करोne with
 * IO when we वापस.
 */
अटल noअंतरभूत पूर्णांक cow_file_range(काष्ठा btrfs_inode *inode,
				   काष्ठा page *locked_page,
				   u64 start, u64 end, पूर्णांक *page_started,
				   अचिन्हित दीर्घ *nr_written, पूर्णांक unlock)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 alloc_hपूर्णांक = 0;
	u64 num_bytes;
	अचिन्हित दीर्घ ram_size;
	u64 cur_alloc_size = 0;
	u64 min_alloc_size;
	u64 blocksize = fs_info->sectorsize;
	काष्ठा btrfs_key ins;
	काष्ठा extent_map *em;
	अचिन्हित clear_bits;
	अचिन्हित दीर्घ page_ops;
	bool extent_reserved = false;
	पूर्णांक ret = 0;

	अगर (btrfs_is_मुक्त_space_inode(inode)) अणु
		WARN_ON_ONCE(1);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	num_bytes = ALIGN(end - start + 1, blocksize);
	num_bytes = max(blocksize,  num_bytes);
	ASSERT(num_bytes <= btrfs_super_total_bytes(fs_info->super_copy));

	inode_should_defrag(inode, start, end, num_bytes, SZ_64K);

	अगर (start == 0) अणु
		/* lets try to make an अंतरभूत extent */
		ret = cow_file_range_अंतरभूत(inode, start, end, 0,
					    BTRFS_COMPRESS_NONE, शून्य);
		अगर (ret == 0) अणु
			/*
			 * We use DO_ACCOUNTING here because we need the
			 * delalloc_release_metadata to be run _after_ we drop
			 * our outstanding extent क्रम clearing delalloc क्रम this
			 * range.
			 */
			extent_clear_unlock_delalloc(inode, start, end, शून्य,
				     EXTENT_LOCKED | EXTENT_DELALLOC |
				     EXTENT_DELALLOC_NEW | EXTENT_DEFRAG |
				     EXTENT_DO_ACCOUNTING, PAGE_UNLOCK |
				     PAGE_START_WRITEBACK | PAGE_END_WRITEBACK);
			*nr_written = *nr_written +
			     (end - start + PAGE_SIZE) / PAGE_SIZE;
			*page_started = 1;
			जाओ out;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	alloc_hपूर्णांक = get_extent_allocation_hपूर्णांक(inode, start, num_bytes);
	btrfs_drop_extent_cache(inode, start, start + num_bytes - 1, 0);

	/*
	 * Relocation relies on the relocated extents to have exactly the same
	 * size as the original extents. Normally ग_लिखोback क्रम relocation data
	 * extents follows a NOCOW path because relocation pपुनः_स्मृतिates the
	 * extents. However, due to an operation such as scrub turning a block
	 * group to RO mode, it may fallback to COW mode, so we must make sure
	 * an extent allocated during COW has exactly the requested size and can
	 * not be split पूर्णांकo smaller extents, otherwise relocation अवरोधs and
	 * fails during the stage where it updates the bytenr of file extent
	 * items.
	 */
	अगर (root->root_key.objectid == BTRFS_DATA_RELOC_TREE_OBJECTID)
		min_alloc_size = num_bytes;
	अन्यथा
		min_alloc_size = fs_info->sectorsize;

	जबतक (num_bytes > 0) अणु
		cur_alloc_size = num_bytes;
		ret = btrfs_reserve_extent(root, cur_alloc_size, cur_alloc_size,
					   min_alloc_size, 0, alloc_hपूर्णांक,
					   &ins, 1, 1);
		अगर (ret < 0)
			जाओ out_unlock;
		cur_alloc_size = ins.offset;
		extent_reserved = true;

		ram_size = ins.offset;
		em = create_io_em(inode, start, ins.offset, /* len */
				  start, /* orig_start */
				  ins.objectid, /* block_start */
				  ins.offset, /* block_len */
				  ins.offset, /* orig_block_len */
				  ram_size, /* ram_bytes */
				  BTRFS_COMPRESS_NONE, /* compress_type */
				  BTRFS_ORDERED_REGULAR /* type */);
		अगर (IS_ERR(em)) अणु
			ret = PTR_ERR(em);
			जाओ out_reserve;
		पूर्ण
		मुक्त_extent_map(em);

		ret = btrfs_add_ordered_extent(inode, start, ins.objectid,
					       ram_size, cur_alloc_size,
					       BTRFS_ORDERED_REGULAR);
		अगर (ret)
			जाओ out_drop_extent_cache;

		अगर (root->root_key.objectid ==
		    BTRFS_DATA_RELOC_TREE_OBJECTID) अणु
			ret = btrfs_reloc_clone_csums(inode, start,
						      cur_alloc_size);
			/*
			 * Only drop cache here, and process as normal.
			 *
			 * We must not allow extent_clear_unlock_delalloc()
			 * at out_unlock label to मुक्त meta of this ordered
			 * extent, as its meta should be मुक्तd by
			 * btrfs_finish_ordered_io().
			 *
			 * So we must जारी until @start is increased to
			 * skip current ordered extent.
			 */
			अगर (ret)
				btrfs_drop_extent_cache(inode, start,
						start + ram_size - 1, 0);
		पूर्ण

		btrfs_dec_block_group_reservations(fs_info, ins.objectid);

		/* we're not doing compressed IO, don't unlock the first
		 * page (which the caller expects to stay locked), करोn't
		 * clear any dirty bits and करोn't set any ग_लिखोback bits
		 *
		 * Do set the Private2 bit so we know this page was properly
		 * setup क्रम ग_लिखोpage
		 */
		page_ops = unlock ? PAGE_UNLOCK : 0;
		page_ops |= PAGE_SET_PRIVATE2;

		extent_clear_unlock_delalloc(inode, start, start + ram_size - 1,
					     locked_page,
					     EXTENT_LOCKED | EXTENT_DELALLOC,
					     page_ops);
		अगर (num_bytes < cur_alloc_size)
			num_bytes = 0;
		अन्यथा
			num_bytes -= cur_alloc_size;
		alloc_hपूर्णांक = ins.objectid + ins.offset;
		start += cur_alloc_size;
		extent_reserved = false;

		/*
		 * btrfs_reloc_clone_csums() error, since start is increased
		 * extent_clear_unlock_delalloc() at out_unlock label won't
		 * मुक्त metadata of current ordered extent, we're OK to निकास.
		 */
		अगर (ret)
			जाओ out_unlock;
	पूर्ण
out:
	वापस ret;

out_drop_extent_cache:
	btrfs_drop_extent_cache(inode, start, start + ram_size - 1, 0);
out_reserve:
	btrfs_dec_block_group_reservations(fs_info, ins.objectid);
	btrfs_मुक्त_reserved_extent(fs_info, ins.objectid, ins.offset, 1);
out_unlock:
	clear_bits = EXTENT_LOCKED | EXTENT_DELALLOC | EXTENT_DELALLOC_NEW |
		EXTENT_DEFRAG | EXTENT_CLEAR_META_RESV;
	page_ops = PAGE_UNLOCK | PAGE_START_WRITEBACK | PAGE_END_WRITEBACK;
	/*
	 * If we reserved an extent क्रम our delalloc range (or a subrange) and
	 * failed to create the respective ordered extent, then it means that
	 * when we reserved the extent we decremented the extent's size from
	 * the data space_info's bytes_may_use counter and incremented the
	 * space_info's bytes_reserved counter by the same amount. We must make
	 * sure extent_clear_unlock_delalloc() करोes not try to decrement again
	 * the data space_info's bytes_may_use counter, thereक्रमe we करो not pass
	 * it the flag EXTENT_CLEAR_DATA_RESV.
	 */
	अगर (extent_reserved) अणु
		extent_clear_unlock_delalloc(inode, start,
					     start + cur_alloc_size - 1,
					     locked_page,
					     clear_bits,
					     page_ops);
		start += cur_alloc_size;
		अगर (start >= end)
			जाओ out;
	पूर्ण
	extent_clear_unlock_delalloc(inode, start, end, locked_page,
				     clear_bits | EXTENT_CLEAR_DATA_RESV,
				     page_ops);
	जाओ out;
पूर्ण

/*
 * work queue call back to started compression on a file and pages
 */
अटल noअंतरभूत व्योम async_cow_start(काष्ठा btrfs_work *work)
अणु
	काष्ठा async_chunk *async_chunk;
	पूर्णांक compressed_extents;

	async_chunk = container_of(work, काष्ठा async_chunk, work);

	compressed_extents = compress_file_range(async_chunk);
	अगर (compressed_extents == 0) अणु
		btrfs_add_delayed_iput(async_chunk->inode);
		async_chunk->inode = शून्य;
	पूर्ण
पूर्ण

/*
 * work queue call back to submit previously compressed pages
 */
अटल noअंतरभूत व्योम async_cow_submit(काष्ठा btrfs_work *work)
अणु
	काष्ठा async_chunk *async_chunk = container_of(work, काष्ठा async_chunk,
						     work);
	काष्ठा btrfs_fs_info *fs_info = btrfs_work_owner(work);
	अचिन्हित दीर्घ nr_pages;

	nr_pages = (async_chunk->end - async_chunk->start + PAGE_SIZE) >>
		PAGE_SHIFT;

	/* atomic_sub_वापस implies a barrier */
	अगर (atomic_sub_वापस(nr_pages, &fs_info->async_delalloc_pages) <
	    5 * SZ_1M)
		cond_wake_up_nomb(&fs_info->async_submit_रुको);

	/*
	 * ->inode could be शून्य अगर async_chunk_start has failed to compress,
	 * in which हाल we करोn't have anything to submit, yet we need to
	 * always adjust ->async_delalloc_pages as its paired with the init
	 * happening in cow_file_range_async
	 */
	अगर (async_chunk->inode)
		submit_compressed_extents(async_chunk);
पूर्ण

अटल noअंतरभूत व्योम async_cow_मुक्त(काष्ठा btrfs_work *work)
अणु
	काष्ठा async_chunk *async_chunk;

	async_chunk = container_of(work, काष्ठा async_chunk, work);
	अगर (async_chunk->inode)
		btrfs_add_delayed_iput(async_chunk->inode);
	अगर (async_chunk->blkcg_css)
		css_put(async_chunk->blkcg_css);
	/*
	 * Since the poपूर्णांकer to 'pending' is at the beginning of the array of
	 * async_chunk's, मुक्तing it ensures the whole array has been मुक्तd.
	 */
	अगर (atomic_dec_and_test(async_chunk->pending))
		kvमुक्त(async_chunk->pending);
पूर्ण

अटल पूर्णांक cow_file_range_async(काष्ठा btrfs_inode *inode,
				काष्ठा ग_लिखोback_control *wbc,
				काष्ठा page *locked_page,
				u64 start, u64 end, पूर्णांक *page_started,
				अचिन्हित दीर्घ *nr_written)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा cgroup_subsys_state *blkcg_css = wbc_blkcg_css(wbc);
	काष्ठा async_cow *ctx;
	काष्ठा async_chunk *async_chunk;
	अचिन्हित दीर्घ nr_pages;
	u64 cur_end;
	u64 num_chunks = DIV_ROUND_UP(end - start, SZ_512K);
	पूर्णांक i;
	bool should_compress;
	अचिन्हित nofs_flag;
	स्थिर अचिन्हित पूर्णांक ग_लिखो_flags = wbc_to_ग_लिखो_flags(wbc);

	unlock_extent(&inode->io_tree, start, end);

	अगर (inode->flags & BTRFS_INODE_NOCOMPRESS &&
	    !btrfs_test_opt(fs_info, FORCE_COMPRESS)) अणु
		num_chunks = 1;
		should_compress = false;
	पूर्ण अन्यथा अणु
		should_compress = true;
	पूर्ण

	nofs_flag = meदो_स्मृति_nofs_save();
	ctx = kvदो_स्मृति(काष्ठा_size(ctx, chunks, num_chunks), GFP_KERNEL);
	meदो_स्मृति_nofs_restore(nofs_flag);

	अगर (!ctx) अणु
		अचिन्हित clear_bits = EXTENT_LOCKED | EXTENT_DELALLOC |
			EXTENT_DELALLOC_NEW | EXTENT_DEFRAG |
			EXTENT_DO_ACCOUNTING;
		अचिन्हित दीर्घ page_ops = PAGE_UNLOCK | PAGE_START_WRITEBACK |
					 PAGE_END_WRITEBACK | PAGE_SET_ERROR;

		extent_clear_unlock_delalloc(inode, start, end, locked_page,
					     clear_bits, page_ops);
		वापस -ENOMEM;
	पूर्ण

	async_chunk = ctx->chunks;
	atomic_set(&ctx->num_chunks, num_chunks);

	क्रम (i = 0; i < num_chunks; i++) अणु
		अगर (should_compress)
			cur_end = min(end, start + SZ_512K - 1);
		अन्यथा
			cur_end = end;

		/*
		 * igrab is called higher up in the call chain, take only the
		 * lightweight reference क्रम the callback lअगरeसमय
		 */
		ihold(&inode->vfs_inode);
		async_chunk[i].pending = &ctx->num_chunks;
		async_chunk[i].inode = &inode->vfs_inode;
		async_chunk[i].start = start;
		async_chunk[i].end = cur_end;
		async_chunk[i].ग_लिखो_flags = ग_लिखो_flags;
		INIT_LIST_HEAD(&async_chunk[i].extents);

		/*
		 * The locked_page comes all the way from ग_लिखोpage and its
		 * the original page we were actually given.  As we spपढ़ो
		 * this large delalloc region across multiple async_chunk
		 * काष्ठाs, only the first काष्ठा needs a poपूर्णांकer to locked_page
		 *
		 * This way we करोn't need racey decisions about who is supposed
		 * to unlock it.
		 */
		अगर (locked_page) अणु
			/*
			 * Depending on the compressibility, the pages might or
			 * might not go through async.  We want all of them to
			 * be accounted against wbc once.  Let's करो it here
			 * beक्रमe the paths भागerge.  wbc accounting is used
			 * only क्रम क्रमeign ग_लिखोback detection and करोesn't
			 * need full accuracy.  Just account the whole thing
			 * against the first page.
			 */
			wbc_account_cgroup_owner(wbc, locked_page,
						 cur_end - start);
			async_chunk[i].locked_page = locked_page;
			locked_page = शून्य;
		पूर्ण अन्यथा अणु
			async_chunk[i].locked_page = शून्य;
		पूर्ण

		अगर (blkcg_css != blkcg_root_css) अणु
			css_get(blkcg_css);
			async_chunk[i].blkcg_css = blkcg_css;
		पूर्ण अन्यथा अणु
			async_chunk[i].blkcg_css = शून्य;
		पूर्ण

		btrfs_init_work(&async_chunk[i].work, async_cow_start,
				async_cow_submit, async_cow_मुक्त);

		nr_pages = DIV_ROUND_UP(cur_end - start, PAGE_SIZE);
		atomic_add(nr_pages, &fs_info->async_delalloc_pages);

		btrfs_queue_work(fs_info->delalloc_workers, &async_chunk[i].work);

		*nr_written += nr_pages;
		start = cur_end + 1;
	पूर्ण
	*page_started = 1;
	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक run_delalloc_zoned(काष्ठा btrfs_inode *inode,
				       काष्ठा page *locked_page, u64 start,
				       u64 end, पूर्णांक *page_started,
				       अचिन्हित दीर्घ *nr_written)
अणु
	पूर्णांक ret;

	ret = cow_file_range(inode, locked_page, start, end, page_started,
			     nr_written, 0);
	अगर (ret)
		वापस ret;

	अगर (*page_started)
		वापस 0;

	__set_page_dirty_nobuffers(locked_page);
	account_page_redirty(locked_page);
	extent_ग_लिखो_locked_range(&inode->vfs_inode, start, end, WB_SYNC_ALL);
	*page_started = 1;

	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक csum_exist_in_range(काष्ठा btrfs_fs_info *fs_info,
					u64 bytenr, u64 num_bytes)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_ordered_sum *sums;
	LIST_HEAD(list);

	ret = btrfs_lookup_csums_range(fs_info->csum_root, bytenr,
				       bytenr + num_bytes - 1, &list, 0);
	अगर (ret == 0 && list_empty(&list))
		वापस 0;

	जबतक (!list_empty(&list)) अणु
		sums = list_entry(list.next, काष्ठा btrfs_ordered_sum, list);
		list_del(&sums->list);
		kमुक्त(sums);
	पूर्ण
	अगर (ret < 0)
		वापस ret;
	वापस 1;
पूर्ण

अटल पूर्णांक fallback_to_cow(काष्ठा btrfs_inode *inode, काष्ठा page *locked_page,
			   स्थिर u64 start, स्थिर u64 end,
			   पूर्णांक *page_started, अचिन्हित दीर्घ *nr_written)
अणु
	स्थिर bool is_space_ino = btrfs_is_मुक्त_space_inode(inode);
	स्थिर bool is_reloc_ino = (inode->root->root_key.objectid ==
				   BTRFS_DATA_RELOC_TREE_OBJECTID);
	स्थिर u64 range_bytes = end + 1 - start;
	काष्ठा extent_io_tree *io_tree = &inode->io_tree;
	u64 range_start = start;
	u64 count;

	/*
	 * If EXTENT_NORESERVE is set it means that when the buffered ग_लिखो was
	 * made we had not enough available data space and thereक्रमe we did not
	 * reserve data space क्रम it, since we though we could करो NOCOW क्रम the
	 * respective file range (either there is pपुनः_स्मृति extent or the inode
	 * has the NOCOW bit set).
	 *
	 * However when we need to fallback to COW mode (because क्रम example the
	 * block group क्रम the corresponding extent was turned to RO mode by a
	 * scrub or relocation) we need to करो the following:
	 *
	 * 1) We increment the bytes_may_use counter of the data space info.
	 *    If COW succeeds, it allocates a new data extent and after करोing
	 *    that it decrements the space info's bytes_may_use counter and
	 *    increments its bytes_reserved counter by the same amount (we करो
	 *    this at btrfs_add_reserved_bytes()). So we need to increment the
	 *    bytes_may_use counter to compensate (when space is reserved at
	 *    buffered ग_लिखो समय, the bytes_may_use counter is incremented);
	 *
	 * 2) We clear the EXTENT_NORESERVE bit from the range. We करो this so
	 *    that अगर the COW path fails क्रम any reason, it decrements (through
	 *    extent_clear_unlock_delalloc()) the bytes_may_use counter of the
	 *    data space info, which we incremented in the step above.
	 *
	 * If we need to fallback to cow and the inode corresponds to a मुक्त
	 * space cache inode or an inode of the data relocation tree, we must
	 * also increment bytes_may_use of the data space_info क्रम the same
	 * reason. Space caches and relocated data extents always get a pपुनः_स्मृति
	 * extent क्रम them, however scrub or balance may have set the block
	 * group that contains that extent to RO mode and thereक्रमe क्रमce COW
	 * when starting ग_लिखोback.
	 */
	count = count_range_bits(io_tree, &range_start, end, range_bytes,
				 EXTENT_NORESERVE, 0);
	अगर (count > 0 || is_space_ino || is_reloc_ino) अणु
		u64 bytes = count;
		काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
		काष्ठा btrfs_space_info *sinfo = fs_info->data_sinfo;

		अगर (is_space_ino || is_reloc_ino)
			bytes = range_bytes;

		spin_lock(&sinfo->lock);
		btrfs_space_info_update_bytes_may_use(fs_info, sinfo, bytes);
		spin_unlock(&sinfo->lock);

		अगर (count > 0)
			clear_extent_bit(io_tree, start, end, EXTENT_NORESERVE,
					 0, 0, शून्य);
	पूर्ण

	वापस cow_file_range(inode, locked_page, start, end, page_started,
			      nr_written, 1);
पूर्ण

/*
 * when nowcow ग_लिखोback call back.  This checks क्रम snapshots or COW copies
 * of the extents that exist in the file, and COWs the file as required.
 *
 * If no cow copies or snapshots exist, we ग_लिखो directly to the existing
 * blocks on disk
 */
अटल noअंतरभूत पूर्णांक run_delalloc_nocow(काष्ठा btrfs_inode *inode,
				       काष्ठा page *locked_page,
				       स्थिर u64 start, स्थिर u64 end,
				       पूर्णांक *page_started,
				       अचिन्हित दीर्घ *nr_written)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_path *path;
	u64 cow_start = (u64)-1;
	u64 cur_offset = start;
	पूर्णांक ret;
	bool check_prev = true;
	स्थिर bool मुक्तspace_inode = btrfs_is_मुक्त_space_inode(inode);
	u64 ino = btrfs_ino(inode);
	bool nocow = false;
	u64 disk_bytenr = 0;
	स्थिर bool क्रमce = inode->flags & BTRFS_INODE_NODATACOW;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		extent_clear_unlock_delalloc(inode, start, end, locked_page,
					     EXTENT_LOCKED | EXTENT_DELALLOC |
					     EXTENT_DO_ACCOUNTING |
					     EXTENT_DEFRAG, PAGE_UNLOCK |
					     PAGE_START_WRITEBACK |
					     PAGE_END_WRITEBACK);
		वापस -ENOMEM;
	पूर्ण

	जबतक (1) अणु
		काष्ठा btrfs_key found_key;
		काष्ठा btrfs_file_extent_item *fi;
		काष्ठा extent_buffer *leaf;
		u64 extent_end;
		u64 extent_offset;
		u64 num_bytes = 0;
		u64 disk_num_bytes;
		u64 ram_bytes;
		पूर्णांक extent_type;

		nocow = false;

		ret = btrfs_lookup_file_extent(शून्य, root, path, ino,
					       cur_offset, 0);
		अगर (ret < 0)
			जाओ error;

		/*
		 * If there is no extent क्रम our range when करोing the initial
		 * search, then go back to the previous slot as it will be the
		 * one containing the search offset
		 */
		अगर (ret > 0 && path->slots[0] > 0 && check_prev) अणु
			leaf = path->nodes[0];
			btrfs_item_key_to_cpu(leaf, &found_key,
					      path->slots[0] - 1);
			अगर (found_key.objectid == ino &&
			    found_key.type == BTRFS_EXTENT_DATA_KEY)
				path->slots[0]--;
		पूर्ण
		check_prev = false;
next_slot:
		/* Go to next leaf अगर we have exhausted the current one */
		leaf = path->nodes[0];
		अगर (path->slots[0] >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0) अणु
				अगर (cow_start != (u64)-1)
					cur_offset = cow_start;
				जाओ error;
			पूर्ण
			अगर (ret > 0)
				अवरोध;
			leaf = path->nodes[0];
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);

		/* Didn't find anything क्रम our INO */
		अगर (found_key.objectid > ino)
			अवरोध;
		/*
		 * Keep searching until we find an EXTENT_ITEM or there are no
		 * more extents क्रम this inode
		 */
		अगर (WARN_ON_ONCE(found_key.objectid < ino) ||
		    found_key.type < BTRFS_EXTENT_DATA_KEY) अणु
			path->slots[0]++;
			जाओ next_slot;
		पूर्ण

		/* Found key is not EXTENT_DATA_KEY or starts after req range */
		अगर (found_key.type > BTRFS_EXTENT_DATA_KEY ||
		    found_key.offset > end)
			अवरोध;

		/*
		 * If the found extent starts after requested offset, then
		 * adjust extent_end to be right beक्रमe this extent begins
		 */
		अगर (found_key.offset > cur_offset) अणु
			extent_end = found_key.offset;
			extent_type = 0;
			जाओ out_check;
		पूर्ण

		/*
		 * Found extent which begins beक्रमe our range and potentially
		 * पूर्णांकersect it
		 */
		fi = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_file_extent_item);
		extent_type = btrfs_file_extent_type(leaf, fi);

		ram_bytes = btrfs_file_extent_ram_bytes(leaf, fi);
		अगर (extent_type == BTRFS_खाता_EXTENT_REG ||
		    extent_type == BTRFS_खाता_EXTENT_PREALLOC) अणु
			disk_bytenr = btrfs_file_extent_disk_bytenr(leaf, fi);
			extent_offset = btrfs_file_extent_offset(leaf, fi);
			extent_end = found_key.offset +
				btrfs_file_extent_num_bytes(leaf, fi);
			disk_num_bytes =
				btrfs_file_extent_disk_num_bytes(leaf, fi);
			/*
			 * If the extent we got ends beक्रमe our current offset,
			 * skip to the next extent.
			 */
			अगर (extent_end <= cur_offset) अणु
				path->slots[0]++;
				जाओ next_slot;
			पूर्ण
			/* Skip holes */
			अगर (disk_bytenr == 0)
				जाओ out_check;
			/* Skip compressed/encrypted/encoded extents */
			अगर (btrfs_file_extent_compression(leaf, fi) ||
			    btrfs_file_extent_encryption(leaf, fi) ||
			    btrfs_file_extent_other_encoding(leaf, fi))
				जाओ out_check;
			/*
			 * If extent is created beक्रमe the last volume's snapshot
			 * this implies the extent is shared, hence we can't करो
			 * nocow. This is the same check as in
			 * btrfs_cross_ref_exist but without calling
			 * btrfs_search_slot.
			 */
			अगर (!मुक्तspace_inode &&
			    btrfs_file_extent_generation(leaf, fi) <=
			    btrfs_root_last_snapshot(&root->root_item))
				जाओ out_check;
			अगर (extent_type == BTRFS_खाता_EXTENT_REG && !क्रमce)
				जाओ out_check;

			/*
			 * The following checks can be expensive, as they need to
			 * take other locks and करो btree or rbtree searches, so
			 * release the path to aव्योम blocking other tasks क्रम too
			 * दीर्घ.
			 */
			btrfs_release_path(path);

			ret = btrfs_cross_ref_exist(root, ino,
						    found_key.offset -
						    extent_offset, disk_bytenr, false);
			अगर (ret) अणु
				/*
				 * ret could be -EIO अगर the above fails to पढ़ो
				 * metadata.
				 */
				अगर (ret < 0) अणु
					अगर (cow_start != (u64)-1)
						cur_offset = cow_start;
					जाओ error;
				पूर्ण

				WARN_ON_ONCE(मुक्तspace_inode);
				जाओ out_check;
			पूर्ण
			disk_bytenr += extent_offset;
			disk_bytenr += cur_offset - found_key.offset;
			num_bytes = min(end + 1, extent_end) - cur_offset;
			/*
			 * If there are pending snapshots क्रम this root, we
			 * fall पूर्णांकo common COW way
			 */
			अगर (!मुक्तspace_inode && atomic_पढ़ो(&root->snapshot_क्रमce_cow))
				जाओ out_check;
			/*
			 * क्रमce cow अगर csum exists in the range.
			 * this ensure that csum क्रम a given extent are
			 * either valid or करो not exist.
			 */
			ret = csum_exist_in_range(fs_info, disk_bytenr,
						  num_bytes);
			अगर (ret) अणु
				/*
				 * ret could be -EIO अगर the above fails to पढ़ो
				 * metadata.
				 */
				अगर (ret < 0) अणु
					अगर (cow_start != (u64)-1)
						cur_offset = cow_start;
					जाओ error;
				पूर्ण
				WARN_ON_ONCE(मुक्तspace_inode);
				जाओ out_check;
			पूर्ण
			/* If the extent's block group is RO, we must COW */
			अगर (!btrfs_inc_nocow_ग_लिखोrs(fs_info, disk_bytenr))
				जाओ out_check;
			nocow = true;
		पूर्ण अन्यथा अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
			extent_end = found_key.offset + ram_bytes;
			extent_end = ALIGN(extent_end, fs_info->sectorsize);
			/* Skip extents outside of our requested range */
			अगर (extent_end <= start) अणु
				path->slots[0]++;
				जाओ next_slot;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* If this triggers then we have a memory corruption */
			BUG();
		पूर्ण
out_check:
		/*
		 * If nocow is false then record the beginning of the range
		 * that needs to be COWed
		 */
		अगर (!nocow) अणु
			अगर (cow_start == (u64)-1)
				cow_start = cur_offset;
			cur_offset = extent_end;
			अगर (cur_offset > end)
				अवरोध;
			अगर (!path->nodes[0])
				जारी;
			path->slots[0]++;
			जाओ next_slot;
		पूर्ण

		/*
		 * COW range from cow_start to found_key.offset - 1. As the key
		 * will contain the beginning of the first extent that can be
		 * NOCOW, following one which needs to be COW'ed
		 */
		अगर (cow_start != (u64)-1) अणु
			ret = fallback_to_cow(inode, locked_page,
					      cow_start, found_key.offset - 1,
					      page_started, nr_written);
			अगर (ret)
				जाओ error;
			cow_start = (u64)-1;
		पूर्ण

		अगर (extent_type == BTRFS_खाता_EXTENT_PREALLOC) अणु
			u64 orig_start = found_key.offset - extent_offset;
			काष्ठा extent_map *em;

			em = create_io_em(inode, cur_offset, num_bytes,
					  orig_start,
					  disk_bytenr, /* block_start */
					  num_bytes, /* block_len */
					  disk_num_bytes, /* orig_block_len */
					  ram_bytes, BTRFS_COMPRESS_NONE,
					  BTRFS_ORDERED_PREALLOC);
			अगर (IS_ERR(em)) अणु
				ret = PTR_ERR(em);
				जाओ error;
			पूर्ण
			मुक्त_extent_map(em);
			ret = btrfs_add_ordered_extent(inode, cur_offset,
						       disk_bytenr, num_bytes,
						       num_bytes,
						       BTRFS_ORDERED_PREALLOC);
			अगर (ret) अणु
				btrfs_drop_extent_cache(inode, cur_offset,
							cur_offset + num_bytes - 1,
							0);
				जाओ error;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = btrfs_add_ordered_extent(inode, cur_offset,
						       disk_bytenr, num_bytes,
						       num_bytes,
						       BTRFS_ORDERED_NOCOW);
			अगर (ret)
				जाओ error;
		पूर्ण

		अगर (nocow)
			btrfs_dec_nocow_ग_लिखोrs(fs_info, disk_bytenr);
		nocow = false;

		अगर (root->root_key.objectid ==
		    BTRFS_DATA_RELOC_TREE_OBJECTID)
			/*
			 * Error handled later, as we must prevent
			 * extent_clear_unlock_delalloc() in error handler
			 * from मुक्तing metadata of created ordered extent.
			 */
			ret = btrfs_reloc_clone_csums(inode, cur_offset,
						      num_bytes);

		extent_clear_unlock_delalloc(inode, cur_offset,
					     cur_offset + num_bytes - 1,
					     locked_page, EXTENT_LOCKED |
					     EXTENT_DELALLOC |
					     EXTENT_CLEAR_DATA_RESV,
					     PAGE_UNLOCK | PAGE_SET_PRIVATE2);

		cur_offset = extent_end;

		/*
		 * btrfs_reloc_clone_csums() error, now we're OK to call error
		 * handler, as metadata क्रम created ordered extent will only
		 * be मुक्तd by btrfs_finish_ordered_io().
		 */
		अगर (ret)
			जाओ error;
		अगर (cur_offset > end)
			अवरोध;
	पूर्ण
	btrfs_release_path(path);

	अगर (cur_offset <= end && cow_start == (u64)-1)
		cow_start = cur_offset;

	अगर (cow_start != (u64)-1) अणु
		cur_offset = end;
		ret = fallback_to_cow(inode, locked_page, cow_start, end,
				      page_started, nr_written);
		अगर (ret)
			जाओ error;
	पूर्ण

error:
	अगर (nocow)
		btrfs_dec_nocow_ग_लिखोrs(fs_info, disk_bytenr);

	अगर (ret && cur_offset < end)
		extent_clear_unlock_delalloc(inode, cur_offset, end,
					     locked_page, EXTENT_LOCKED |
					     EXTENT_DELALLOC | EXTENT_DEFRAG |
					     EXTENT_DO_ACCOUNTING, PAGE_UNLOCK |
					     PAGE_START_WRITEBACK |
					     PAGE_END_WRITEBACK);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल bool should_nocow(काष्ठा btrfs_inode *inode, u64 start, u64 end)
अणु
	अगर (inode->flags & (BTRFS_INODE_NODATACOW | BTRFS_INODE_PREALLOC)) अणु
		अगर (inode->defrag_bytes &&
		    test_range_bit(&inode->io_tree, start, end, EXTENT_DEFRAG,
				   0, शून्य))
			वापस false;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Function to process delayed allocation (create CoW) क्रम ranges which are
 * being touched क्रम the first समय.
 */
पूर्णांक btrfs_run_delalloc_range(काष्ठा btrfs_inode *inode, काष्ठा page *locked_page,
		u64 start, u64 end, पूर्णांक *page_started, अचिन्हित दीर्घ *nr_written,
		काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;
	स्थिर bool zoned = btrfs_is_zoned(inode->root->fs_info);

	अगर (should_nocow(inode, start, end)) अणु
		ASSERT(!zoned);
		ret = run_delalloc_nocow(inode, locked_page, start, end,
					 page_started, nr_written);
	पूर्ण अन्यथा अगर (!inode_can_compress(inode) ||
		   !inode_need_compress(inode, start, end)) अणु
		अगर (zoned)
			ret = run_delalloc_zoned(inode, locked_page, start, end,
						 page_started, nr_written);
		अन्यथा
			ret = cow_file_range(inode, locked_page, start, end,
					     page_started, nr_written, 1);
	पूर्ण अन्यथा अणु
		set_bit(BTRFS_INODE_HAS_ASYNC_EXTENT, &inode->runसमय_flags);
		ret = cow_file_range_async(inode, wbc, locked_page, start, end,
					   page_started, nr_written);
	पूर्ण
	अगर (ret)
		btrfs_cleanup_ordered_extents(inode, locked_page, start,
					      end - start + 1);
	वापस ret;
पूर्ण

व्योम btrfs_split_delalloc_extent(काष्ठा inode *inode,
				 काष्ठा extent_state *orig, u64 split)
अणु
	u64 size;

	/* not delalloc, ignore it */
	अगर (!(orig->state & EXTENT_DELALLOC))
		वापस;

	size = orig->end - orig->start + 1;
	अगर (size > BTRFS_MAX_EXTENT_SIZE) अणु
		u32 num_extents;
		u64 new_size;

		/*
		 * See the explanation in btrfs_merge_delalloc_extent, the same
		 * applies here, just in reverse.
		 */
		new_size = orig->end - split + 1;
		num_extents = count_max_extents(new_size);
		new_size = split - orig->start;
		num_extents += count_max_extents(new_size);
		अगर (count_max_extents(size) >= num_extents)
			वापस;
	पूर्ण

	spin_lock(&BTRFS_I(inode)->lock);
	btrfs_mod_outstanding_extents(BTRFS_I(inode), 1);
	spin_unlock(&BTRFS_I(inode)->lock);
पूर्ण

/*
 * Handle merged delayed allocation extents so we can keep track of new extents
 * that are just merged onto old extents, such as when we are करोing sequential
 * ग_लिखोs, so we can properly account क्रम the metadata space we'll need.
 */
व्योम btrfs_merge_delalloc_extent(काष्ठा inode *inode, काष्ठा extent_state *new,
				 काष्ठा extent_state *other)
अणु
	u64 new_size, old_size;
	u32 num_extents;

	/* not delalloc, ignore it */
	अगर (!(other->state & EXTENT_DELALLOC))
		वापस;

	अगर (new->start > other->start)
		new_size = new->end - other->start + 1;
	अन्यथा
		new_size = other->end - new->start + 1;

	/* we're not bigger than the max, unreserve the space and go */
	अगर (new_size <= BTRFS_MAX_EXTENT_SIZE) अणु
		spin_lock(&BTRFS_I(inode)->lock);
		btrfs_mod_outstanding_extents(BTRFS_I(inode), -1);
		spin_unlock(&BTRFS_I(inode)->lock);
		वापस;
	पूर्ण

	/*
	 * We have to add up either side to figure out how many extents were
	 * accounted क्रम beक्रमe we merged पूर्णांकo one big extent.  If the number of
	 * extents we accounted क्रम is <= the amount we need क्रम the new range
	 * then we can वापस, otherwise drop.  Think of it like this
	 *
	 * [ 4k][MAX_SIZE]
	 *
	 * So we've grown the extent by a MAX_SIZE extent, this would mean we
	 * need 2 outstanding extents, on one side we have 1 and the other side
	 * we have 1 so they are == and we can वापस.  But in this हाल
	 *
	 * [MAX_SIZE+4k][MAX_SIZE+4k]
	 *
	 * Each range on their own accounts क्रम 2 extents, but merged together
	 * they are only 3 extents worth of accounting, so we need to drop in
	 * this हाल.
	 */
	old_size = other->end - other->start + 1;
	num_extents = count_max_extents(old_size);
	old_size = new->end - new->start + 1;
	num_extents += count_max_extents(old_size);
	अगर (count_max_extents(new_size) >= num_extents)
		वापस;

	spin_lock(&BTRFS_I(inode)->lock);
	btrfs_mod_outstanding_extents(BTRFS_I(inode), -1);
	spin_unlock(&BTRFS_I(inode)->lock);
पूर्ण

अटल व्योम btrfs_add_delalloc_inodes(काष्ठा btrfs_root *root,
				      काष्ठा inode *inode)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);

	spin_lock(&root->delalloc_lock);
	अगर (list_empty(&BTRFS_I(inode)->delalloc_inodes)) अणु
		list_add_tail(&BTRFS_I(inode)->delalloc_inodes,
			      &root->delalloc_inodes);
		set_bit(BTRFS_INODE_IN_DELALLOC_LIST,
			&BTRFS_I(inode)->runसमय_flags);
		root->nr_delalloc_inodes++;
		अगर (root->nr_delalloc_inodes == 1) अणु
			spin_lock(&fs_info->delalloc_root_lock);
			BUG_ON(!list_empty(&root->delalloc_root));
			list_add_tail(&root->delalloc_root,
				      &fs_info->delalloc_roots);
			spin_unlock(&fs_info->delalloc_root_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&root->delalloc_lock);
पूर्ण


व्योम __btrfs_del_delalloc_inode(काष्ठा btrfs_root *root,
				काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	अगर (!list_empty(&inode->delalloc_inodes)) अणु
		list_del_init(&inode->delalloc_inodes);
		clear_bit(BTRFS_INODE_IN_DELALLOC_LIST,
			  &inode->runसमय_flags);
		root->nr_delalloc_inodes--;
		अगर (!root->nr_delalloc_inodes) अणु
			ASSERT(list_empty(&root->delalloc_inodes));
			spin_lock(&fs_info->delalloc_root_lock);
			BUG_ON(list_empty(&root->delalloc_root));
			list_del_init(&root->delalloc_root);
			spin_unlock(&fs_info->delalloc_root_lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btrfs_del_delalloc_inode(काष्ठा btrfs_root *root,
				     काष्ठा btrfs_inode *inode)
अणु
	spin_lock(&root->delalloc_lock);
	__btrfs_del_delalloc_inode(root, inode);
	spin_unlock(&root->delalloc_lock);
पूर्ण

/*
 * Properly track delayed allocation bytes in the inode and to मुख्यtain the
 * list of inodes that have pending delalloc work to be करोne.
 */
व्योम btrfs_set_delalloc_extent(काष्ठा inode *inode, काष्ठा extent_state *state,
			       अचिन्हित *bits)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);

	अगर ((*bits & EXTENT_DEFRAG) && !(*bits & EXTENT_DELALLOC))
		WARN_ON(1);
	/*
	 * set_bit and clear bit hooks normally require _irqsave/restore
	 * but in this हाल, we are only testing क्रम the DELALLOC
	 * bit, which is only set or cleared with irqs on
	 */
	अगर (!(state->state & EXTENT_DELALLOC) && (*bits & EXTENT_DELALLOC)) अणु
		काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
		u64 len = state->end + 1 - state->start;
		u32 num_extents = count_max_extents(len);
		bool करो_list = !btrfs_is_मुक्त_space_inode(BTRFS_I(inode));

		spin_lock(&BTRFS_I(inode)->lock);
		btrfs_mod_outstanding_extents(BTRFS_I(inode), num_extents);
		spin_unlock(&BTRFS_I(inode)->lock);

		/* For sanity tests */
		अगर (btrfs_is_testing(fs_info))
			वापस;

		percpu_counter_add_batch(&fs_info->delalloc_bytes, len,
					 fs_info->delalloc_batch);
		spin_lock(&BTRFS_I(inode)->lock);
		BTRFS_I(inode)->delalloc_bytes += len;
		अगर (*bits & EXTENT_DEFRAG)
			BTRFS_I(inode)->defrag_bytes += len;
		अगर (करो_list && !test_bit(BTRFS_INODE_IN_DELALLOC_LIST,
					 &BTRFS_I(inode)->runसमय_flags))
			btrfs_add_delalloc_inodes(root, inode);
		spin_unlock(&BTRFS_I(inode)->lock);
	पूर्ण

	अगर (!(state->state & EXTENT_DELALLOC_NEW) &&
	    (*bits & EXTENT_DELALLOC_NEW)) अणु
		spin_lock(&BTRFS_I(inode)->lock);
		BTRFS_I(inode)->new_delalloc_bytes += state->end + 1 -
			state->start;
		spin_unlock(&BTRFS_I(inode)->lock);
	पूर्ण
पूर्ण

/*
 * Once a range is no दीर्घer delalloc this function ensures that proper
 * accounting happens.
 */
व्योम btrfs_clear_delalloc_extent(काष्ठा inode *vfs_inode,
				 काष्ठा extent_state *state, अचिन्हित *bits)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(vfs_inode);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(vfs_inode->i_sb);
	u64 len = state->end + 1 - state->start;
	u32 num_extents = count_max_extents(len);

	अगर ((state->state & EXTENT_DEFRAG) && (*bits & EXTENT_DEFRAG)) अणु
		spin_lock(&inode->lock);
		inode->defrag_bytes -= len;
		spin_unlock(&inode->lock);
	पूर्ण

	/*
	 * set_bit and clear bit hooks normally require _irqsave/restore
	 * but in this हाल, we are only testing क्रम the DELALLOC
	 * bit, which is only set or cleared with irqs on
	 */
	अगर ((state->state & EXTENT_DELALLOC) && (*bits & EXTENT_DELALLOC)) अणु
		काष्ठा btrfs_root *root = inode->root;
		bool करो_list = !btrfs_is_मुक्त_space_inode(inode);

		spin_lock(&inode->lock);
		btrfs_mod_outstanding_extents(inode, -num_extents);
		spin_unlock(&inode->lock);

		/*
		 * We करोn't reserve metadata space क्रम space cache inodes so we
		 * करोn't need to call delalloc_release_metadata अगर there is an
		 * error.
		 */
		अगर (*bits & EXTENT_CLEAR_META_RESV &&
		    root != fs_info->tree_root)
			btrfs_delalloc_release_metadata(inode, len, false);

		/* For sanity tests. */
		अगर (btrfs_is_testing(fs_info))
			वापस;

		अगर (root->root_key.objectid != BTRFS_DATA_RELOC_TREE_OBJECTID &&
		    करो_list && !(state->state & EXTENT_NORESERVE) &&
		    (*bits & EXTENT_CLEAR_DATA_RESV))
			btrfs_मुक्त_reserved_data_space_noquota(fs_info, len);

		percpu_counter_add_batch(&fs_info->delalloc_bytes, -len,
					 fs_info->delalloc_batch);
		spin_lock(&inode->lock);
		inode->delalloc_bytes -= len;
		अगर (करो_list && inode->delalloc_bytes == 0 &&
		    test_bit(BTRFS_INODE_IN_DELALLOC_LIST,
					&inode->runसमय_flags))
			btrfs_del_delalloc_inode(root, inode);
		spin_unlock(&inode->lock);
	पूर्ण

	अगर ((state->state & EXTENT_DELALLOC_NEW) &&
	    (*bits & EXTENT_DELALLOC_NEW)) अणु
		spin_lock(&inode->lock);
		ASSERT(inode->new_delalloc_bytes >= len);
		inode->new_delalloc_bytes -= len;
		अगर (*bits & EXTENT_ADD_INODE_BYTES)
			inode_add_bytes(&inode->vfs_inode, len);
		spin_unlock(&inode->lock);
	पूर्ण
पूर्ण

/*
 * btrfs_bio_fits_in_stripe - Checks whether the size of the given bio will fit
 * in a chunk's stripe. This function ensures that bios करो not span a
 * stripe/chunk
 *
 * @page - The page we are about to add to the bio
 * @size - size we want to add to the bio
 * @bio - bio we want to ensure is smaller than a stripe
 * @bio_flags - flags of the bio
 *
 * वापस 1 अगर page cannot be added to the bio
 * वापस 0 अगर page can be added to the bio
 * वापस error otherwise
 */
पूर्णांक btrfs_bio_fits_in_stripe(काष्ठा page *page, माप_प्रकार size, काष्ठा bio *bio,
			     अचिन्हित दीर्घ bio_flags)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	u64 logical = bio->bi_iter.bi_sector << 9;
	काष्ठा extent_map *em;
	u64 length = 0;
	u64 map_length;
	पूर्णांक ret = 0;
	काष्ठा btrfs_io_geometry geom;

	अगर (bio_flags & EXTENT_BIO_COMPRESSED)
		वापस 0;

	length = bio->bi_iter.bi_size;
	map_length = length;
	em = btrfs_get_chunk_map(fs_info, logical, map_length);
	अगर (IS_ERR(em))
		वापस PTR_ERR(em);
	ret = btrfs_get_io_geometry(fs_info, em, btrfs_op(bio), logical,
				    map_length, &geom);
	अगर (ret < 0)
		जाओ out;

	अगर (geom.len < length + size)
		ret = 1;
out:
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

/*
 * in order to insert checksums पूर्णांकo the metadata in large chunks,
 * we रुको until bio submission समय.   All the pages in the bio are
 * checksummed and sums are attached onto the ordered extent record.
 *
 * At IO completion समय the cums attached on the ordered extent record
 * are inserted पूर्णांकo the btree
 */
अटल blk_status_t btrfs_submit_bio_start(काष्ठा inode *inode, काष्ठा bio *bio,
					   u64 dio_file_offset)
अणु
	वापस btrfs_csum_one_bio(BTRFS_I(inode), bio, 0, 0);
पूर्ण

bool btrfs_bio_fits_in_ordered_extent(काष्ठा page *page, काष्ठा bio *bio,
				      अचिन्हित पूर्णांक size)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(page->mapping->host);
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_ordered_extent *ordered;
	u64 len = bio->bi_iter.bi_size + size;
	bool ret = true;

	ASSERT(btrfs_is_zoned(fs_info));
	ASSERT(fs_info->max_zone_append_size > 0);
	ASSERT(bio_op(bio) == REQ_OP_ZONE_APPEND);

	/* Ordered extent not yet created, so we're good */
	ordered = btrfs_lookup_ordered_extent(inode, page_offset(page));
	अगर (!ordered)
		वापस ret;

	अगर ((bio->bi_iter.bi_sector << SECTOR_SHIFT) + len >
	    ordered->disk_bytenr + ordered->disk_num_bytes)
		ret = false;

	btrfs_put_ordered_extent(ordered);

	वापस ret;
पूर्ण

अटल blk_status_t extract_ordered_extent(काष्ठा btrfs_inode *inode,
					   काष्ठा bio *bio, loff_t file_offset)
अणु
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा extent_map *em = शून्य, *em_new = शून्य;
	काष्ठा extent_map_tree *em_tree = &inode->extent_tree;
	u64 start = (u64)bio->bi_iter.bi_sector << SECTOR_SHIFT;
	u64 len = bio->bi_iter.bi_size;
	u64 end = start + len;
	u64 ordered_end;
	u64 pre, post;
	पूर्णांक ret = 0;

	ordered = btrfs_lookup_ordered_extent(inode, file_offset);
	अगर (WARN_ON_ONCE(!ordered))
		वापस BLK_STS_IOERR;

	/* No need to split */
	अगर (ordered->disk_num_bytes == len)
		जाओ out;

	/* We cannot split once end_bio'd ordered extent */
	अगर (WARN_ON_ONCE(ordered->bytes_left != ordered->disk_num_bytes)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* We cannot split a compressed ordered extent */
	अगर (WARN_ON_ONCE(ordered->disk_num_bytes != ordered->num_bytes)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ordered_end = ordered->disk_bytenr + ordered->disk_num_bytes;
	/* bio must be in one ordered extent */
	अगर (WARN_ON_ONCE(start < ordered->disk_bytenr || end > ordered_end)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Checksum list should be empty */
	अगर (WARN_ON_ONCE(!list_empty(&ordered->list))) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	pre = start - ordered->disk_bytenr;
	post = ordered_end - end;

	ret = btrfs_split_ordered_extent(ordered, pre, post);
	अगर (ret)
		जाओ out;

	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, ordered->file_offset, len);
	अगर (!em) अणु
		पढ़ो_unlock(&em_tree->lock);
		ret = -EIO;
		जाओ out;
	पूर्ण
	पढ़ो_unlock(&em_tree->lock);

	ASSERT(!test_bit(EXTENT_FLAG_COMPRESSED, &em->flags));
	/*
	 * We cannot reuse em_new here but have to create a new one, as
	 * unpin_extent_cache() expects the start of the extent map to be the
	 * logical offset of the file, which करोes not hold true anymore after
	 * splitting.
	 */
	em_new = create_io_em(inode, em->start + pre, len,
			      em->start + pre, em->block_start + pre, len,
			      len, len, BTRFS_COMPRESS_NONE,
			      BTRFS_ORDERED_REGULAR);
	अगर (IS_ERR(em_new)) अणु
		ret = PTR_ERR(em_new);
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em_new);

out:
	मुक्त_extent_map(em);
	btrfs_put_ordered_extent(ordered);

	वापस त्रुटि_सं_to_blk_status(ret);
पूर्ण

/*
 * extent_io.c submission hook. This करोes the right thing क्रम csum calculation
 * on ग_लिखो, or पढ़ोing the csums from the tree beक्रमe a पढ़ो.
 *
 * Rules about async/sync submit,
 * a) पढ़ो:				sync submit
 *
 * b) ग_लिखो without checksum:		sync submit
 *
 * c) ग_लिखो with checksum:
 *    c-1) अगर bio is issued by fsync:	sync submit
 *         (sync_ग_लिखोrs != 0)
 *
 *    c-2) अगर root is reloc root:	sync submit
 *         (only in हाल of buffered IO)
 *
 *    c-3) otherwise:			async submit
 */
blk_status_t btrfs_submit_data_bio(काष्ठा inode *inode, काष्ठा bio *bio,
				   पूर्णांक mirror_num, अचिन्हित दीर्घ bio_flags)

अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	क्रमागत btrfs_wq_endio_type metadata = BTRFS_WQ_ENDIO_DATA;
	blk_status_t ret = 0;
	पूर्णांक skip_sum;
	पूर्णांक async = !atomic_पढ़ो(&BTRFS_I(inode)->sync_ग_लिखोrs);

	skip_sum = (BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM) ||
		   !fs_info->csum_root;

	अगर (btrfs_is_मुक्त_space_inode(BTRFS_I(inode)))
		metadata = BTRFS_WQ_ENDIO_FREE_SPACE;

	अगर (bio_op(bio) == REQ_OP_ZONE_APPEND) अणु
		काष्ठा page *page = bio_first_bvec_all(bio)->bv_page;
		loff_t file_offset = page_offset(page);

		ret = extract_ordered_extent(BTRFS_I(inode), bio, file_offset);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (btrfs_op(bio) != BTRFS_MAP_WRITE) अणु
		ret = btrfs_bio_wq_end_io(fs_info, bio, metadata);
		अगर (ret)
			जाओ out;

		अगर (bio_flags & EXTENT_BIO_COMPRESSED) अणु
			ret = btrfs_submit_compressed_पढ़ो(inode, bio,
							   mirror_num,
							   bio_flags);
			जाओ out;
		पूर्ण अन्यथा अणु
			/*
			 * Lookup bio sums करोes extra checks around whether we
			 * need to csum or not, which is why we ignore skip_sum
			 * here.
			 */
			ret = btrfs_lookup_bio_sums(inode, bio, शून्य);
			अगर (ret)
				जाओ out;
		पूर्ण
		जाओ mapit;
	पूर्ण अन्यथा अगर (async && !skip_sum) अणु
		/* csum items have alपढ़ोy been cloned */
		अगर (root->root_key.objectid == BTRFS_DATA_RELOC_TREE_OBJECTID)
			जाओ mapit;
		/* we're करोing a ग_लिखो, करो the async checksumming */
		ret = btrfs_wq_submit_bio(inode, bio, mirror_num, bio_flags,
					  0, btrfs_submit_bio_start);
		जाओ out;
	पूर्ण अन्यथा अगर (!skip_sum) अणु
		ret = btrfs_csum_one_bio(BTRFS_I(inode), bio, 0, 0);
		अगर (ret)
			जाओ out;
	पूर्ण

mapit:
	ret = btrfs_map_bio(fs_info, bio, mirror_num);

out:
	अगर (ret) अणु
		bio->bi_status = ret;
		bio_endio(bio);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * given a list of ordered sums record them in the inode.  This happens
 * at IO completion समय based on sums calculated at bio submission समय.
 */
अटल पूर्णांक add_pending_csums(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा list_head *list)
अणु
	काष्ठा btrfs_ordered_sum *sum;
	पूर्णांक ret;

	list_क्रम_each_entry(sum, list, list) अणु
		trans->adding_csums = true;
		ret = btrfs_csum_file_blocks(trans, trans->fs_info->csum_root, sum);
		trans->adding_csums = false;
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_find_new_delalloc_bytes(काष्ठा btrfs_inode *inode,
					 स्थिर u64 start,
					 स्थिर u64 len,
					 काष्ठा extent_state **cached_state)
अणु
	u64 search_start = start;
	स्थिर u64 end = start + len - 1;

	जबतक (search_start < end) अणु
		स्थिर u64 search_len = end - search_start + 1;
		काष्ठा extent_map *em;
		u64 em_len;
		पूर्णांक ret = 0;

		em = btrfs_get_extent(inode, शून्य, 0, search_start, search_len);
		अगर (IS_ERR(em))
			वापस PTR_ERR(em);

		अगर (em->block_start != EXTENT_MAP_HOLE)
			जाओ next;

		em_len = em->len;
		अगर (em->start < search_start)
			em_len -= search_start - em->start;
		अगर (em_len > search_len)
			em_len = search_len;

		ret = set_extent_bit(&inode->io_tree, search_start,
				     search_start + em_len - 1,
				     EXTENT_DELALLOC_NEW, 0, शून्य, cached_state,
				     GFP_NOFS, शून्य);
next:
		search_start = extent_map_end(em);
		मुक्त_extent_map(em);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक btrfs_set_extent_delalloc(काष्ठा btrfs_inode *inode, u64 start, u64 end,
			      अचिन्हित पूर्णांक extra_bits,
			      काष्ठा extent_state **cached_state)
अणु
	WARN_ON(PAGE_ALIGNED(end));

	अगर (start >= i_size_पढ़ो(&inode->vfs_inode) &&
	    !(inode->flags & BTRFS_INODE_PREALLOC)) अणु
		/*
		 * There can't be any extents following eof in this हाल so just
		 * set the delalloc new bit क्रम the range directly.
		 */
		extra_bits |= EXTENT_DELALLOC_NEW;
	पूर्ण अन्यथा अणु
		पूर्णांक ret;

		ret = btrfs_find_new_delalloc_bytes(inode, start,
						    end + 1 - start,
						    cached_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस set_extent_delalloc(&inode->io_tree, start, end, extra_bits,
				   cached_state);
पूर्ण

/* see btrfs_ग_लिखोpage_start_hook क्रम details on why this is required */
काष्ठा btrfs_ग_लिखोpage_fixup अणु
	काष्ठा page *page;
	काष्ठा inode *inode;
	काष्ठा btrfs_work work;
पूर्ण;

अटल व्योम btrfs_ग_लिखोpage_fixup_worker(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_ग_लिखोpage_fixup *fixup;
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा extent_changeset *data_reserved = शून्य;
	काष्ठा page *page;
	काष्ठा btrfs_inode *inode;
	u64 page_start;
	u64 page_end;
	पूर्णांक ret = 0;
	bool मुक्त_delalloc_space = true;

	fixup = container_of(work, काष्ठा btrfs_ग_लिखोpage_fixup, work);
	page = fixup->page;
	inode = BTRFS_I(fixup->inode);
	page_start = page_offset(page);
	page_end = page_offset(page) + PAGE_SIZE - 1;

	/*
	 * This is similar to page_mkग_लिखो, we need to reserve the space beक्रमe
	 * we take the page lock.
	 */
	ret = btrfs_delalloc_reserve_space(inode, &data_reserved, page_start,
					   PAGE_SIZE);
again:
	lock_page(page);

	/*
	 * Beक्रमe we queued this fixup, we took a reference on the page.
	 * page->mapping may go शून्य, but it shouldn't be moved to a dअगरferent
	 * address space.
	 */
	अगर (!page->mapping || !PageDirty(page) || !PageChecked(page)) अणु
		/*
		 * Unक्रमtunately this is a little tricky, either
		 *
		 * 1) We got here and our page had alपढ़ोy been dealt with and
		 *    we reserved our space, thus ret == 0, so we need to just
		 *    drop our space reservation and bail.  This can happen the
		 *    first समय we come पूर्णांकo the fixup worker, or could happen
		 *    जबतक रुकोing क्रम the ordered extent.
		 * 2) Our page was alपढ़ोy dealt with, but we happened to get an
		 *    ENOSPC above from the btrfs_delalloc_reserve_space.  In
		 *    this हाल we obviously करोn't have anything to release, but
		 *    because the page was alपढ़ोy dealt with we करोn't want to
		 *    mark the page with an error, so make sure we're resetting
		 *    ret to 0.  This is why we have this check _beक्रमe_ the ret
		 *    check, because we करो not want to have a surprise ENOSPC
		 *    when the page was alपढ़ोy properly dealt with.
		 */
		अगर (!ret) अणु
			btrfs_delalloc_release_extents(inode, PAGE_SIZE);
			btrfs_delalloc_release_space(inode, data_reserved,
						     page_start, PAGE_SIZE,
						     true);
		पूर्ण
		ret = 0;
		जाओ out_page;
	पूर्ण

	/*
	 * We can't mess with the page state unless it is locked, so now that
	 * it is locked bail अगर we failed to make our space reservation.
	 */
	अगर (ret)
		जाओ out_page;

	lock_extent_bits(&inode->io_tree, page_start, page_end, &cached_state);

	/* alपढ़ोy ordered? We're करोne */
	अगर (PagePrivate2(page))
		जाओ out_reserved;

	ordered = btrfs_lookup_ordered_range(inode, page_start, PAGE_SIZE);
	अगर (ordered) अणु
		unlock_extent_cached(&inode->io_tree, page_start, page_end,
				     &cached_state);
		unlock_page(page);
		btrfs_start_ordered_extent(ordered, 1);
		btrfs_put_ordered_extent(ordered);
		जाओ again;
	पूर्ण

	ret = btrfs_set_extent_delalloc(inode, page_start, page_end, 0,
					&cached_state);
	अगर (ret)
		जाओ out_reserved;

	/*
	 * Everything went as planned, we're now the owner of a dirty page with
	 * delayed allocation bits set and space reserved क्रम our COW
	 * destination.
	 *
	 * The page was dirty when we started, nothing should have cleaned it.
	 */
	BUG_ON(!PageDirty(page));
	मुक्त_delalloc_space = false;
out_reserved:
	btrfs_delalloc_release_extents(inode, PAGE_SIZE);
	अगर (मुक्त_delalloc_space)
		btrfs_delalloc_release_space(inode, data_reserved, page_start,
					     PAGE_SIZE, true);
	unlock_extent_cached(&inode->io_tree, page_start, page_end,
			     &cached_state);
out_page:
	अगर (ret) अणु
		/*
		 * We hit ENOSPC or other errors.  Update the mapping and page
		 * to reflect the errors and clean the page.
		 */
		mapping_set_error(page->mapping, ret);
		end_extent_ग_लिखोpage(page, ret, page_start, page_end);
		clear_page_dirty_क्रम_io(page);
		SetPageError(page);
	पूर्ण
	ClearPageChecked(page);
	unlock_page(page);
	put_page(page);
	kमुक्त(fixup);
	extent_changeset_मुक्त(data_reserved);
	/*
	 * As a precaution, करो a delayed iput in हाल it would be the last iput
	 * that could need flushing space. Recursing back to fixup worker would
	 * deadlock.
	 */
	btrfs_add_delayed_iput(&inode->vfs_inode);
पूर्ण

/*
 * There are a few paths in the higher layers of the kernel that directly
 * set the page dirty bit without asking the fileप्रणाली अगर it is a
 * good idea.  This causes problems because we want to make sure COW
 * properly happens and the data=ordered rules are followed.
 *
 * In our हाल any range that करोesn't have the ORDERED bit set
 * hasn't been properly setup क्रम IO.  We kick off an async process
 * to fix it up.  The async helper will रुको क्रम ordered extents, set
 * the delalloc bit and make it safe to ग_लिखो the page.
 */
पूर्णांक btrfs_ग_लिखोpage_cow_fixup(काष्ठा page *page, u64 start, u64 end)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_ग_लिखोpage_fixup *fixup;

	/* this page is properly in the ordered list */
	अगर (TestClearPagePrivate2(page))
		वापस 0;

	/*
	 * PageChecked is set below when we create a fixup worker क्रम this page,
	 * करोn't try to create another one if we're alपढ़ोy PageChecked()
	 *
	 * The extent_io ग_लिखोpage code will redirty the page अगर we send back
	 * EAGAIN.
	 */
	अगर (PageChecked(page))
		वापस -EAGAIN;

	fixup = kzalloc(माप(*fixup), GFP_NOFS);
	अगर (!fixup)
		वापस -EAGAIN;

	/*
	 * We are alपढ़ोy holding a reference to this inode from
	 * ग_लिखो_cache_pages.  We need to hold it because the space reservation
	 * takes place outside of the page lock, and we can't trust
	 * page->mapping outside of the page lock.
	 */
	ihold(inode);
	SetPageChecked(page);
	get_page(page);
	btrfs_init_work(&fixup->work, btrfs_ग_लिखोpage_fixup_worker, शून्य, शून्य);
	fixup->page = page;
	fixup->inode = inode;
	btrfs_queue_work(fs_info->fixup_workers, &fixup->work);

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक insert_reserved_file_extent(काष्ठा btrfs_trans_handle *trans,
				       काष्ठा btrfs_inode *inode, u64 file_pos,
				       काष्ठा btrfs_file_extent_item *stack_fi,
				       स्थिर bool update_inode_bytes,
				       u64 qgroup_reserved)
अणु
	काष्ठा btrfs_root *root = inode->root;
	स्थिर u64 sectorsize = root->fs_info->sectorsize;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key ins;
	u64 disk_num_bytes = btrfs_stack_file_extent_disk_num_bytes(stack_fi);
	u64 disk_bytenr = btrfs_stack_file_extent_disk_bytenr(stack_fi);
	u64 num_bytes = btrfs_stack_file_extent_num_bytes(stack_fi);
	u64 ram_bytes = btrfs_stack_file_extent_ram_bytes(stack_fi);
	काष्ठा btrfs_drop_extents_args drop_args = अणु 0 पूर्ण;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/*
	 * we may be replacing one extent in the tree with another.
	 * The new extent is pinned in the extent map, and we करोn't want
	 * to drop it from the cache until it is completely in the btree.
	 *
	 * So, tell btrfs_drop_extents to leave this extent in the cache.
	 * the caller is expected to unpin it and allow it to be merged
	 * with the others.
	 */
	drop_args.path = path;
	drop_args.start = file_pos;
	drop_args.end = file_pos + num_bytes;
	drop_args.replace_extent = true;
	drop_args.extent_item_size = माप(*stack_fi);
	ret = btrfs_drop_extents(trans, root, inode, &drop_args);
	अगर (ret)
		जाओ out;

	अगर (!drop_args.extent_inserted) अणु
		ins.objectid = btrfs_ino(inode);
		ins.offset = file_pos;
		ins.type = BTRFS_EXTENT_DATA_KEY;

		ret = btrfs_insert_empty_item(trans, root, path, &ins,
					      माप(*stack_fi));
		अगर (ret)
			जाओ out;
	पूर्ण
	leaf = path->nodes[0];
	btrfs_set_stack_file_extent_generation(stack_fi, trans->transid);
	ग_लिखो_extent_buffer(leaf, stack_fi,
			btrfs_item_ptr_offset(leaf, path->slots[0]),
			माप(काष्ठा btrfs_file_extent_item));

	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	/*
	 * If we dropped an अंतरभूत extent here, we know the range where it is
	 * was not marked with the EXTENT_DELALLOC_NEW bit, so we update the
	 * number of bytes only क्रम that range contaning the अंतरभूत extent.
	 * The reमुख्यing of the range will be processed when clearning the
	 * EXTENT_DELALLOC_BIT bit through the ordered extent completion.
	 */
	अगर (file_pos == 0 && !IS_ALIGNED(drop_args.bytes_found, sectorsize)) अणु
		u64 अंतरभूत_size = round_करोwn(drop_args.bytes_found, sectorsize);

		अंतरभूत_size = drop_args.bytes_found - अंतरभूत_size;
		btrfs_update_inode_bytes(inode, sectorsize, अंतरभूत_size);
		drop_args.bytes_found -= अंतरभूत_size;
		num_bytes -= sectorsize;
	पूर्ण

	अगर (update_inode_bytes)
		btrfs_update_inode_bytes(inode, num_bytes, drop_args.bytes_found);

	ins.objectid = disk_bytenr;
	ins.offset = disk_num_bytes;
	ins.type = BTRFS_EXTENT_ITEM_KEY;

	ret = btrfs_inode_set_file_extent_range(inode, file_pos, ram_bytes);
	अगर (ret)
		जाओ out;

	ret = btrfs_alloc_reserved_file_extent(trans, root, btrfs_ino(inode),
					       file_pos, qgroup_reserved, &ins);
out:
	btrfs_मुक्त_path(path);

	वापस ret;
पूर्ण

अटल व्योम btrfs_release_delalloc_bytes(काष्ठा btrfs_fs_info *fs_info,
					 u64 start, u64 len)
अणु
	काष्ठा btrfs_block_group *cache;

	cache = btrfs_lookup_block_group(fs_info, start);
	ASSERT(cache);

	spin_lock(&cache->lock);
	cache->delalloc_bytes -= len;
	spin_unlock(&cache->lock);

	btrfs_put_block_group(cache);
पूर्ण

अटल पूर्णांक insert_ordered_extent_file_extent(काष्ठा btrfs_trans_handle *trans,
					     काष्ठा btrfs_ordered_extent *oe)
अणु
	काष्ठा btrfs_file_extent_item stack_fi;
	u64 logical_len;
	bool update_inode_bytes;

	स_रखो(&stack_fi, 0, माप(stack_fi));
	btrfs_set_stack_file_extent_type(&stack_fi, BTRFS_खाता_EXTENT_REG);
	btrfs_set_stack_file_extent_disk_bytenr(&stack_fi, oe->disk_bytenr);
	btrfs_set_stack_file_extent_disk_num_bytes(&stack_fi,
						   oe->disk_num_bytes);
	अगर (test_bit(BTRFS_ORDERED_TRUNCATED, &oe->flags))
		logical_len = oe->truncated_len;
	अन्यथा
		logical_len = oe->num_bytes;
	btrfs_set_stack_file_extent_num_bytes(&stack_fi, logical_len);
	btrfs_set_stack_file_extent_ram_bytes(&stack_fi, logical_len);
	btrfs_set_stack_file_extent_compression(&stack_fi, oe->compress_type);
	/* Encryption and other encoding is reserved and all 0 */

	/*
	 * For delalloc, when completing an ordered extent we update the inode's
	 * bytes when clearing the range in the inode's io tree, so pass false
	 * as the argument 'update_inode_bytes' to insert_reserved_file_extent(),
	 * except अगर the ordered extent was truncated.
	 */
	update_inode_bytes = test_bit(BTRFS_ORDERED_सूचीECT, &oe->flags) ||
			     test_bit(BTRFS_ORDERED_TRUNCATED, &oe->flags);

	वापस insert_reserved_file_extent(trans, BTRFS_I(oe->inode),
					   oe->file_offset, &stack_fi,
					   update_inode_bytes, oe->qgroup_rsv);
पूर्ण

/*
 * As ordered data IO finishes, this माला_लो called so we can finish
 * an ordered extent अगर the range of bytes in the file it covers are
 * fully written.
 */
अटल पूर्णांक btrfs_finish_ordered_io(काष्ठा btrfs_ordered_extent *ordered_extent)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(ordered_extent->inode);
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_trans_handle *trans = शून्य;
	काष्ठा extent_io_tree *io_tree = &inode->io_tree;
	काष्ठा extent_state *cached_state = शून्य;
	u64 start, end;
	पूर्णांक compress_type = 0;
	पूर्णांक ret = 0;
	u64 logical_len = ordered_extent->num_bytes;
	bool मुक्तspace_inode;
	bool truncated = false;
	bool clear_reserved_extent = true;
	अचिन्हित पूर्णांक clear_bits = EXTENT_DEFRAG;

	start = ordered_extent->file_offset;
	end = start + ordered_extent->num_bytes - 1;

	अगर (!test_bit(BTRFS_ORDERED_NOCOW, &ordered_extent->flags) &&
	    !test_bit(BTRFS_ORDERED_PREALLOC, &ordered_extent->flags) &&
	    !test_bit(BTRFS_ORDERED_सूचीECT, &ordered_extent->flags))
		clear_bits |= EXTENT_DELALLOC_NEW;

	मुक्तspace_inode = btrfs_is_मुक्त_space_inode(inode);

	अगर (test_bit(BTRFS_ORDERED_IOERR, &ordered_extent->flags)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (ordered_extent->disk)
		btrfs_reग_लिखो_logical_zoned(ordered_extent);

	btrfs_मुक्त_io_failure_record(inode, start, end);

	अगर (test_bit(BTRFS_ORDERED_TRUNCATED, &ordered_extent->flags)) अणु
		truncated = true;
		logical_len = ordered_extent->truncated_len;
		/* Truncated the entire extent, करोn't bother adding */
		अगर (!logical_len)
			जाओ out;
	पूर्ण

	अगर (test_bit(BTRFS_ORDERED_NOCOW, &ordered_extent->flags)) अणु
		BUG_ON(!list_empty(&ordered_extent->list)); /* Logic error */

		btrfs_inode_safe_disk_i_size_ग_लिखो(inode, 0);
		अगर (मुक्तspace_inode)
			trans = btrfs_join_transaction_spacecache(root);
		अन्यथा
			trans = btrfs_join_transaction(root);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			trans = शून्य;
			जाओ out;
		पूर्ण
		trans->block_rsv = &inode->block_rsv;
		ret = btrfs_update_inode_fallback(trans, root, inode);
		अगर (ret) /* -ENOMEM or corruption */
			btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	clear_bits |= EXTENT_LOCKED;
	lock_extent_bits(io_tree, start, end, &cached_state);

	अगर (मुक्तspace_inode)
		trans = btrfs_join_transaction_spacecache(root);
	अन्यथा
		trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		trans = शून्य;
		जाओ out;
	पूर्ण

	trans->block_rsv = &inode->block_rsv;

	अगर (test_bit(BTRFS_ORDERED_COMPRESSED, &ordered_extent->flags))
		compress_type = ordered_extent->compress_type;
	अगर (test_bit(BTRFS_ORDERED_PREALLOC, &ordered_extent->flags)) अणु
		BUG_ON(compress_type);
		ret = btrfs_mark_extent_written(trans, inode,
						ordered_extent->file_offset,
						ordered_extent->file_offset +
						logical_len);
	पूर्ण अन्यथा अणु
		BUG_ON(root == fs_info->tree_root);
		ret = insert_ordered_extent_file_extent(trans, ordered_extent);
		अगर (!ret) अणु
			clear_reserved_extent = false;
			btrfs_release_delalloc_bytes(fs_info,
						ordered_extent->disk_bytenr,
						ordered_extent->disk_num_bytes);
		पूर्ण
	पूर्ण
	unpin_extent_cache(&inode->extent_tree, ordered_extent->file_offset,
			   ordered_extent->num_bytes, trans->transid);
	अगर (ret < 0) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	ret = add_pending_csums(trans, &ordered_extent->list);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	/*
	 * If this is a new delalloc range, clear its new delalloc flag to
	 * update the inode's number of bytes. This needs to be करोne first
	 * beक्रमe updating the inode item.
	 */
	अगर ((clear_bits & EXTENT_DELALLOC_NEW) &&
	    !test_bit(BTRFS_ORDERED_TRUNCATED, &ordered_extent->flags))
		clear_extent_bit(&inode->io_tree, start, end,
				 EXTENT_DELALLOC_NEW | EXTENT_ADD_INODE_BYTES,
				 0, 0, &cached_state);

	btrfs_inode_safe_disk_i_size_ग_लिखो(inode, 0);
	ret = btrfs_update_inode_fallback(trans, root, inode);
	अगर (ret) अणु /* -ENOMEM or corruption */
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण
	ret = 0;
out:
	clear_extent_bit(&inode->io_tree, start, end, clear_bits,
			 (clear_bits & EXTENT_LOCKED) ? 1 : 0, 0,
			 &cached_state);

	अगर (trans)
		btrfs_end_transaction(trans);

	अगर (ret || truncated) अणु
		u64 unwritten_start = start;

		/*
		 * If we failed to finish this ordered extent क्रम any reason we
		 * need to make sure BTRFS_ORDERED_IOERR is set on the ordered
		 * extent, and mark the inode with the error अगर it wasn't
		 * alपढ़ोy set.  Any error during ग_लिखोback would have alपढ़ोy
		 * set the mapping error, so we need to set it अगर we're the ones
		 * marking this ordered extent as failed.
		 */
		अगर (ret && !test_and_set_bit(BTRFS_ORDERED_IOERR,
					     &ordered_extent->flags))
			mapping_set_error(ordered_extent->inode->i_mapping, -EIO);

		अगर (truncated)
			unwritten_start += logical_len;
		clear_extent_uptodate(io_tree, unwritten_start, end, शून्य);

		/* Drop the cache क्रम the part of the extent we didn't ग_लिखो. */
		btrfs_drop_extent_cache(inode, unwritten_start, end, 0);

		/*
		 * If the ordered extent had an IOERR or something अन्यथा went
		 * wrong we need to वापस the space क्रम this ordered extent
		 * back to the allocator.  We only मुक्त the extent in the
		 * truncated हाल अगर we didn't ग_लिखो out the extent at all.
		 *
		 * If we made it past insert_reserved_file_extent beक्रमe we
		 * errored out then we करोn't need to करो this as the accounting
		 * has alपढ़ोy been करोne.
		 */
		अगर ((ret || !logical_len) &&
		    clear_reserved_extent &&
		    !test_bit(BTRFS_ORDERED_NOCOW, &ordered_extent->flags) &&
		    !test_bit(BTRFS_ORDERED_PREALLOC, &ordered_extent->flags)) अणु
			/*
			 * Discard the range beक्रमe वापसing it back to the
			 * मुक्त space pool
			 */
			अगर (ret && btrfs_test_opt(fs_info, DISCARD_SYNC))
				btrfs_discard_extent(fs_info,
						ordered_extent->disk_bytenr,
						ordered_extent->disk_num_bytes,
						शून्य);
			btrfs_मुक्त_reserved_extent(fs_info,
					ordered_extent->disk_bytenr,
					ordered_extent->disk_num_bytes, 1);
		पूर्ण
	पूर्ण

	/*
	 * This needs to be करोne to make sure anybody रुकोing knows we are करोne
	 * updating everything क्रम this ordered extent.
	 */
	btrfs_हटाओ_ordered_extent(inode, ordered_extent);

	/* once क्रम us */
	btrfs_put_ordered_extent(ordered_extent);
	/* once क्रम the tree */
	btrfs_put_ordered_extent(ordered_extent);

	वापस ret;
पूर्ण

अटल व्योम finish_ordered_fn(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_ordered_extent *ordered_extent;
	ordered_extent = container_of(work, काष्ठा btrfs_ordered_extent, work);
	btrfs_finish_ordered_io(ordered_extent);
पूर्ण

व्योम btrfs_ग_लिखोpage_endio_finish_ordered(काष्ठा page *page, u64 start,
					  u64 end, पूर्णांक uptodate)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(page->mapping->host);
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_ordered_extent *ordered_extent = शून्य;
	काष्ठा btrfs_workqueue *wq;

	trace_btrfs_ग_लिखोpage_end_io_hook(page, start, end, uptodate);

	ClearPagePrivate2(page);
	अगर (!btrfs_dec_test_ordered_pending(inode, &ordered_extent, start,
					    end - start + 1, uptodate))
		वापस;

	अगर (btrfs_is_मुक्त_space_inode(inode))
		wq = fs_info->endio_मुक्तspace_worker;
	अन्यथा
		wq = fs_info->endio_ग_लिखो_workers;

	btrfs_init_work(&ordered_extent->work, finish_ordered_fn, शून्य, शून्य);
	btrfs_queue_work(wq, &ordered_extent->work);
पूर्ण

/*
 * check_data_csum - verअगरy checksum of one sector of uncompressed data
 * @inode:	inode
 * @io_bio:	btrfs_io_bio which contains the csum
 * @bio_offset:	offset to the beginning of the bio (in bytes)
 * @page:	page where is the data to be verअगरied
 * @pgoff:	offset inside the page
 * @start:	logical offset in the file
 *
 * The length of such check is always one sector size.
 */
अटल पूर्णांक check_data_csum(काष्ठा inode *inode, काष्ठा btrfs_io_bio *io_bio,
			   u32 bio_offset, काष्ठा page *page, u32 pgoff,
			   u64 start)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	अक्षर *kaddr;
	u32 len = fs_info->sectorsize;
	स्थिर u32 csum_size = fs_info->csum_size;
	अचिन्हित पूर्णांक offset_sectors;
	u8 *csum_expected;
	u8 csum[BTRFS_CSUM_SIZE];

	ASSERT(pgoff + len <= PAGE_SIZE);

	offset_sectors = bio_offset >> fs_info->sectorsize_bits;
	csum_expected = ((u8 *)io_bio->csum) + offset_sectors * csum_size;

	kaddr = kmap_atomic(page);
	shash->tfm = fs_info->csum_shash;

	crypto_shash_digest(shash, kaddr + pgoff, len, csum);

	अगर (स_भेद(csum, csum_expected, csum_size))
		जाओ zeroit;

	kunmap_atomic(kaddr);
	वापस 0;
zeroit:
	btrfs_prपूर्णांक_data_csum_error(BTRFS_I(inode), start, csum, csum_expected,
				    io_bio->mirror_num);
	अगर (io_bio->device)
		btrfs_dev_stat_inc_and_prपूर्णांक(io_bio->device,
					     BTRFS_DEV_STAT_CORRUPTION_ERRS);
	स_रखो(kaddr + pgoff, 1, len);
	flush_dcache_page(page);
	kunmap_atomic(kaddr);
	वापस -EIO;
पूर्ण

/*
 * When पढ़ोs are करोne, we need to check csums to verअगरy the data is correct.
 * अगर there's a match, we allow the bio to finish.  If not, the code in
 * extent_io.c will try to find good copies क्रम us.
 *
 * @bio_offset:	offset to the beginning of the bio (in bytes)
 * @start:	file offset of the range start
 * @end:	file offset of the range end (inclusive)
 */
पूर्णांक btrfs_verअगरy_data_csum(काष्ठा btrfs_io_bio *io_bio, u32 bio_offset,
			   काष्ठा page *page, u64 start, u64 end)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	स्थिर u32 sectorsize = root->fs_info->sectorsize;
	u32 pg_off;

	अगर (PageChecked(page)) अणु
		ClearPageChecked(page);
		वापस 0;
	पूर्ण

	अगर (BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM)
		वापस 0;

	अगर (!root->fs_info->csum_root)
		वापस 0;

	अगर (root->root_key.objectid == BTRFS_DATA_RELOC_TREE_OBJECTID &&
	    test_range_bit(io_tree, start, end, EXTENT_NODATASUM, 1, शून्य)) अणु
		clear_extent_bits(io_tree, start, end, EXTENT_NODATASUM);
		वापस 0;
	पूर्ण

	ASSERT(page_offset(page) <= start &&
	       end <= page_offset(page) + PAGE_SIZE - 1);
	क्रम (pg_off = offset_in_page(start);
	     pg_off < offset_in_page(end);
	     pg_off += sectorsize, bio_offset += sectorsize) अणु
		पूर्णांक ret;

		ret = check_data_csum(inode, io_bio, bio_offset, page, pg_off,
				      page_offset(page) + pg_off);
		अगर (ret < 0)
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * btrfs_add_delayed_iput - perक्रमm a delayed iput on @inode
 *
 * @inode: The inode we want to perक्रमm iput on
 *
 * This function uses the generic vfs_inode::i_count to track whether we should
 * just decrement it (in हाल it's > 1) or अगर this is the last iput then link
 * the inode to the delayed iput machinery. Delayed iमाला_दो are processed at
 * transaction commit समय/superblock commit/cleaner kthपढ़ो.
 */
व्योम btrfs_add_delayed_iput(काष्ठा inode *inode)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_inode *binode = BTRFS_I(inode);

	अगर (atomic_add_unless(&inode->i_count, -1, 1))
		वापस;

	atomic_inc(&fs_info->nr_delayed_iमाला_दो);
	spin_lock(&fs_info->delayed_iput_lock);
	ASSERT(list_empty(&binode->delayed_iput));
	list_add_tail(&binode->delayed_iput, &fs_info->delayed_iमाला_दो);
	spin_unlock(&fs_info->delayed_iput_lock);
	अगर (!test_bit(BTRFS_FS_CLEANER_RUNNING, &fs_info->flags))
		wake_up_process(fs_info->cleaner_kthपढ़ो);
पूर्ण

अटल व्योम run_delayed_iput_locked(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_inode *inode)
अणु
	list_del_init(&inode->delayed_iput);
	spin_unlock(&fs_info->delayed_iput_lock);
	iput(&inode->vfs_inode);
	अगर (atomic_dec_and_test(&fs_info->nr_delayed_iमाला_दो))
		wake_up(&fs_info->delayed_iमाला_दो_रुको);
	spin_lock(&fs_info->delayed_iput_lock);
पूर्ण

अटल व्योम btrfs_run_delayed_iput(काष्ठा btrfs_fs_info *fs_info,
				   काष्ठा btrfs_inode *inode)
अणु
	अगर (!list_empty(&inode->delayed_iput)) अणु
		spin_lock(&fs_info->delayed_iput_lock);
		अगर (!list_empty(&inode->delayed_iput))
			run_delayed_iput_locked(fs_info, inode);
		spin_unlock(&fs_info->delayed_iput_lock);
	पूर्ण
पूर्ण

व्योम btrfs_run_delayed_iमाला_दो(काष्ठा btrfs_fs_info *fs_info)
अणु

	spin_lock(&fs_info->delayed_iput_lock);
	जबतक (!list_empty(&fs_info->delayed_iमाला_दो)) अणु
		काष्ठा btrfs_inode *inode;

		inode = list_first_entry(&fs_info->delayed_iमाला_दो,
				काष्ठा btrfs_inode, delayed_iput);
		run_delayed_iput_locked(fs_info, inode);
		cond_resched_lock(&fs_info->delayed_iput_lock);
	पूर्ण
	spin_unlock(&fs_info->delayed_iput_lock);
पूर्ण

/**
 * Wait क्रम flushing all delayed iमाला_दो
 *
 * @fs_info:  the fileप्रणाली
 *
 * This will रुको on any delayed iमाला_दो that are currently running with KILLABLE
 * set.  Once they are all करोne running we will वापस, unless we are समाप्तed in
 * which हाल we वापस EINTR. This helps in user operations like fallocate etc
 * that might get blocked on the iमाला_दो.
 *
 * Return EINTR अगर we were समाप्तed, 0 अगर nothing's pending
 */
पूर्णांक btrfs_रुको_on_delayed_iमाला_दो(काष्ठा btrfs_fs_info *fs_info)
अणु
	पूर्णांक ret = रुको_event_समाप्तable(fs_info->delayed_iमाला_दो_रुको,
			atomic_पढ़ो(&fs_info->nr_delayed_iमाला_दो) == 0);
	अगर (ret)
		वापस -EINTR;
	वापस 0;
पूर्ण

/*
 * This creates an orphan entry क्रम the given inode in हाल something goes wrong
 * in the middle of an unlink.
 */
पूर्णांक btrfs_orphan_add(काष्ठा btrfs_trans_handle *trans,
		     काष्ठा btrfs_inode *inode)
अणु
	पूर्णांक ret;

	ret = btrfs_insert_orphan_item(trans, inode->root, btrfs_ino(inode));
	अगर (ret && ret != -EEXIST) अणु
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We have करोne the delete so we can go ahead and हटाओ the orphan item क्रम
 * this particular inode.
 */
अटल पूर्णांक btrfs_orphan_del(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_inode *inode)
अणु
	वापस btrfs_del_orphan_item(trans, inode->root, btrfs_ino(inode));
पूर्ण

/*
 * this cleans up any orphans that may be left on the list from the last use
 * of this root.
 */
पूर्णांक btrfs_orphan_cleanup(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key, found_key;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा inode *inode;
	u64 last_objectid = 0;
	पूर्णांक ret = 0, nr_unlink = 0;

	अगर (cmpxchg(&root->orphan_cleanup_state, 0, ORPHAN_CLEANUP_STARTED))
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	path->पढ़ोa = READA_BACK;

	key.objectid = BTRFS_ORPHAN_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = (u64)-1;

	जबतक (1) अणु
		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		अगर (ret < 0)
			जाओ out;

		/*
		 * अगर ret == 0 means we found what we were searching क्रम, which
		 * is weird, but possible, so only screw with path अगर we didn't
		 * find the key and see अगर we have stuff that matches
		 */
		अगर (ret > 0) अणु
			ret = 0;
			अगर (path->slots[0] == 0)
				अवरोध;
			path->slots[0]--;
		पूर्ण

		/* pull out the item */
		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);

		/* make sure the item matches what we want */
		अगर (found_key.objectid != BTRFS_ORPHAN_OBJECTID)
			अवरोध;
		अगर (found_key.type != BTRFS_ORPHAN_ITEM_KEY)
			अवरोध;

		/* release the path since we're करोne with it */
		btrfs_release_path(path);

		/*
		 * this is where we are basically btrfs_lookup, without the
		 * crossing root thing.  we store the inode number in the
		 * offset of the orphan item.
		 */

		अगर (found_key.offset == last_objectid) अणु
			btrfs_err(fs_info,
				  "Error removing orphan entry, stopping orphan cleanup");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		last_objectid = found_key.offset;

		found_key.objectid = found_key.offset;
		found_key.type = BTRFS_INODE_ITEM_KEY;
		found_key.offset = 0;
		inode = btrfs_iget(fs_info->sb, last_objectid, root);
		ret = PTR_ERR_OR_ZERO(inode);
		अगर (ret && ret != -ENOENT)
			जाओ out;

		अगर (ret == -ENOENT && root == fs_info->tree_root) अणु
			काष्ठा btrfs_root *dead_root;
			पूर्णांक is_dead_root = 0;

			/*
			 * This is an orphan in the tree root. Currently these
			 * could come from 2 sources:
			 *  a) a root (snapshot/subvolume) deletion in progress
			 *  b) a मुक्त space cache inode
			 * We need to distinguish those two, as the orphan item
			 * क्रम a root must not get deleted beक्रमe the deletion
			 * of the snapshot/subvolume's tree completes.
			 *
			 * btrfs_find_orphan_roots() ran beक्रमe us, which has
			 * found all deleted roots and loaded them पूर्णांकo
			 * fs_info->fs_roots_radix. So here we can find अगर an
			 * orphan item corresponds to a deleted root by looking
			 * up the root from that radix tree.
			 */

			spin_lock(&fs_info->fs_roots_radix_lock);
			dead_root = radix_tree_lookup(&fs_info->fs_roots_radix,
							 (अचिन्हित दीर्घ)found_key.objectid);
			अगर (dead_root && btrfs_root_refs(&dead_root->root_item) == 0)
				is_dead_root = 1;
			spin_unlock(&fs_info->fs_roots_radix_lock);

			अगर (is_dead_root) अणु
				/* prevent this orphan from being found again */
				key.offset = found_key.objectid - 1;
				जारी;
			पूर्ण

		पूर्ण

		/*
		 * If we have an inode with links, there are a couple of
		 * possibilities. Old kernels (beक्रमe v3.12) used to create an
		 * orphan item क्रम truncate indicating that there were possibly
		 * extent items past i_size that needed to be deleted. In v3.12,
		 * truncate was changed to update i_size in sync with the extent
		 * items, but the (useless) orphan item was still created. Since
		 * v4.18, we करोn't create the orphan item क्रम truncate at all.
		 *
		 * So, this item could mean that we need to करो a truncate, but
		 * only अगर this fileप्रणाली was last used on a pre-v3.12 kernel
		 * and was not cleanly unmounted. The odds of that are quite
		 * slim, and it's a pain to करो the truncate now, so just delete
		 * the orphan item.
		 *
		 * It's also possible that this orphan item was supposed to be
		 * deleted but wasn't. The inode number may have been reused,
		 * but either way, we can delete the orphan item.
		 */
		अगर (ret == -ENOENT || inode->i_nlink) अणु
			अगर (!ret)
				iput(inode);
			trans = btrfs_start_transaction(root, 1);
			अगर (IS_ERR(trans)) अणु
				ret = PTR_ERR(trans);
				जाओ out;
			पूर्ण
			btrfs_debug(fs_info, "auto deleting %Lu",
				    found_key.objectid);
			ret = btrfs_del_orphan_item(trans, root,
						    found_key.objectid);
			btrfs_end_transaction(trans);
			अगर (ret)
				जाओ out;
			जारी;
		पूर्ण

		nr_unlink++;

		/* this will करो delete_inode and everything क्रम us */
		iput(inode);
	पूर्ण
	/* release the path since we're करोne with it */
	btrfs_release_path(path);

	root->orphan_cleanup_state = ORPHAN_CLEANUP_DONE;

	अगर (test_bit(BTRFS_ROOT_ORPHAN_ITEM_INSERTED, &root->state)) अणु
		trans = btrfs_join_transaction(root);
		अगर (!IS_ERR(trans))
			btrfs_end_transaction(trans);
	पूर्ण

	अगर (nr_unlink)
		btrfs_debug(fs_info, "unlinked %d orphans", nr_unlink);

out:
	अगर (ret)
		btrfs_err(fs_info, "could not do orphan cleanup %d", ret);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * very simple check to peek ahead in the leaf looking क्रम xattrs.  If we
 * करोn't find any xattrs, we know there can't be any acls.
 *
 * slot is the slot the inode is in, objectid is the objectid of the inode
 */
अटल noअंतरभूत पूर्णांक acls_after_inode_item(काष्ठा extent_buffer *leaf,
					  पूर्णांक slot, u64 objectid,
					  पूर्णांक *first_xattr_slot)
अणु
	u32 nritems = btrfs_header_nritems(leaf);
	काष्ठा btrfs_key found_key;
	अटल u64 xattr_access = 0;
	अटल u64 xattr_शेष = 0;
	पूर्णांक scanned = 0;

	अगर (!xattr_access) अणु
		xattr_access = btrfs_name_hash(XATTR_NAME_POSIX_ACL_ACCESS,
					म_माप(XATTR_NAME_POSIX_ACL_ACCESS));
		xattr_शेष = btrfs_name_hash(XATTR_NAME_POSIX_ACL_DEFAULT,
					म_माप(XATTR_NAME_POSIX_ACL_DEFAULT));
	पूर्ण

	slot++;
	*first_xattr_slot = -1;
	जबतक (slot < nritems) अणु
		btrfs_item_key_to_cpu(leaf, &found_key, slot);

		/* we found a dअगरferent objectid, there must not be acls */
		अगर (found_key.objectid != objectid)
			वापस 0;

		/* we found an xattr, assume we've got an acl */
		अगर (found_key.type == BTRFS_XATTR_ITEM_KEY) अणु
			अगर (*first_xattr_slot == -1)
				*first_xattr_slot = slot;
			अगर (found_key.offset == xattr_access ||
			    found_key.offset == xattr_शेष)
				वापस 1;
		पूर्ण

		/*
		 * we found a key greater than an xattr key, there can't
		 * be any acls later on
		 */
		अगर (found_key.type > BTRFS_XATTR_ITEM_KEY)
			वापस 0;

		slot++;
		scanned++;

		/*
		 * it goes inode, inode backrefs, xattrs, extents,
		 * so अगर there are a ton of hard links to an inode there can
		 * be a lot of backrefs.  Don't waste समय searching too hard,
		 * this is just an optimization
		 */
		अगर (scanned >= 8)
			अवरोध;
	पूर्ण
	/* we hit the end of the leaf beक्रमe we found an xattr or
	 * something larger than an xattr.  We have to assume the inode
	 * has acls
	 */
	अगर (*first_xattr_slot == -1)
		*first_xattr_slot = slot;
	वापस 1;
पूर्ण

/*
 * पढ़ो an inode from the btree पूर्णांकo the in-memory inode
 */
अटल पूर्णांक btrfs_पढ़ो_locked_inode(काष्ठा inode *inode,
				   काष्ठा btrfs_path *in_path)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_path *path = in_path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_inode_item *inode_item;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_key location;
	अचिन्हित दीर्घ ptr;
	पूर्णांक maybe_acls;
	u32 rdev;
	पूर्णांक ret;
	bool filled = false;
	पूर्णांक first_xattr_slot;

	ret = btrfs_fill_inode(inode, &rdev);
	अगर (!ret)
		filled = true;

	अगर (!path) अणु
		path = btrfs_alloc_path();
		अगर (!path)
			वापस -ENOMEM;
	पूर्ण

	स_नकल(&location, &BTRFS_I(inode)->location, माप(location));

	ret = btrfs_lookup_inode(शून्य, root, path, &location, 0);
	अगर (ret) अणु
		अगर (path != in_path)
			btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण

	leaf = path->nodes[0];

	अगर (filled)
		जाओ cache_index;

	inode_item = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_inode_item);
	inode->i_mode = btrfs_inode_mode(leaf, inode_item);
	set_nlink(inode, btrfs_inode_nlink(leaf, inode_item));
	i_uid_ग_लिखो(inode, btrfs_inode_uid(leaf, inode_item));
	i_gid_ग_लिखो(inode, btrfs_inode_gid(leaf, inode_item));
	btrfs_i_size_ग_लिखो(BTRFS_I(inode), btrfs_inode_size(leaf, inode_item));
	btrfs_inode_set_file_extent_range(BTRFS_I(inode), 0,
			round_up(i_size_पढ़ो(inode), fs_info->sectorsize));

	inode->i_aसमय.tv_sec = btrfs_बारpec_sec(leaf, &inode_item->aसमय);
	inode->i_aसमय.tv_nsec = btrfs_बारpec_nsec(leaf, &inode_item->aसमय);

	inode->i_mसमय.tv_sec = btrfs_बारpec_sec(leaf, &inode_item->mसमय);
	inode->i_mसमय.tv_nsec = btrfs_बारpec_nsec(leaf, &inode_item->mसमय);

	inode->i_स_समय.tv_sec = btrfs_बारpec_sec(leaf, &inode_item->स_समय);
	inode->i_स_समय.tv_nsec = btrfs_बारpec_nsec(leaf, &inode_item->स_समय);

	BTRFS_I(inode)->i_oसमय.tv_sec =
		btrfs_बारpec_sec(leaf, &inode_item->oसमय);
	BTRFS_I(inode)->i_oसमय.tv_nsec =
		btrfs_बारpec_nsec(leaf, &inode_item->oसमय);

	inode_set_bytes(inode, btrfs_inode_nbytes(leaf, inode_item));
	BTRFS_I(inode)->generation = btrfs_inode_generation(leaf, inode_item);
	BTRFS_I(inode)->last_trans = btrfs_inode_transid(leaf, inode_item);

	inode_set_iversion_queried(inode,
				   btrfs_inode_sequence(leaf, inode_item));
	inode->i_generation = BTRFS_I(inode)->generation;
	inode->i_rdev = 0;
	rdev = btrfs_inode_rdev(leaf, inode_item);

	BTRFS_I(inode)->index_cnt = (u64)-1;
	BTRFS_I(inode)->flags = btrfs_inode_flags(leaf, inode_item);

cache_index:
	/*
	 * If we were modअगरied in the current generation and evicted from memory
	 * and then re-पढ़ो we need to करो a full sync since we करोn't have any
	 * idea about which extents were modअगरied beक्रमe we were evicted from
	 * cache.
	 *
	 * This is required क्रम both inode re-पढ़ो from disk and delayed inode
	 * in delayed_nodes_tree.
	 */
	अगर (BTRFS_I(inode)->last_trans == fs_info->generation)
		set_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
			&BTRFS_I(inode)->runसमय_flags);

	/*
	 * We करोn't persist the id of the transaction where an unlink operation
	 * against the inode was last made. So here we assume the inode might
	 * have been evicted, and thereक्रमe the exact value of last_unlink_trans
	 * lost, and set it to last_trans to aव्योम metadata inconsistencies
	 * between the inode and its parent अगर the inode is fsync'ed and the log
	 * replayed. For example, in the scenario:
	 *
	 * touch mydir/foo
	 * ln mydir/foo mydir/bar
	 * sync
	 * unlink mydir/bar
	 * echo 2 > /proc/sys/vm/drop_caches   # evicts inode
	 * xfs_io -c fsync mydir/foo
	 * <घातer failure>
	 * mount fs, triggers fsync log replay
	 *
	 * We must make sure that when we fsync our inode foo we also log its
	 * parent inode, otherwise after log replay the parent still has the
	 * dentry with the "bar" name but our inode foo has a link count of 1
	 * and करोesn't have an inode ref with the name "bar" anymore.
	 *
	 * Setting last_unlink_trans to last_trans is a pessimistic approach,
	 * but it guarantees correctness at the expense of occasional full
	 * transaction commits on fsync अगर our inode is a directory, or अगर our
	 * inode is not a directory, logging its parent unnecessarily.
	 */
	BTRFS_I(inode)->last_unlink_trans = BTRFS_I(inode)->last_trans;

	/*
	 * Same logic as क्रम last_unlink_trans. We करोn't persist the generation
	 * of the last transaction where this inode was used क्रम a reflink
	 * operation, so after eviction and reloading the inode we must be
	 * pessimistic and assume the last transaction that modअगरied the inode.
	 */
	BTRFS_I(inode)->last_reflink_trans = BTRFS_I(inode)->last_trans;

	path->slots[0]++;
	अगर (inode->i_nlink != 1 ||
	    path->slots[0] >= btrfs_header_nritems(leaf))
		जाओ cache_acl;

	btrfs_item_key_to_cpu(leaf, &location, path->slots[0]);
	अगर (location.objectid != btrfs_ino(BTRFS_I(inode)))
		जाओ cache_acl;

	ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
	अगर (location.type == BTRFS_INODE_REF_KEY) अणु
		काष्ठा btrfs_inode_ref *ref;

		ref = (काष्ठा btrfs_inode_ref *)ptr;
		BTRFS_I(inode)->dir_index = btrfs_inode_ref_index(leaf, ref);
	पूर्ण अन्यथा अगर (location.type == BTRFS_INODE_EXTREF_KEY) अणु
		काष्ठा btrfs_inode_extref *extref;

		extref = (काष्ठा btrfs_inode_extref *)ptr;
		BTRFS_I(inode)->dir_index = btrfs_inode_extref_index(leaf,
								     extref);
	पूर्ण
cache_acl:
	/*
	 * try to precache a शून्य acl entry क्रम files that करोn't have
	 * any xattrs or acls
	 */
	maybe_acls = acls_after_inode_item(leaf, path->slots[0],
			btrfs_ino(BTRFS_I(inode)), &first_xattr_slot);
	अगर (first_xattr_slot != -1) अणु
		path->slots[0] = first_xattr_slot;
		ret = btrfs_load_inode_props(inode, path);
		अगर (ret)
			btrfs_err(fs_info,
				  "error loading props for ino %llu (root %llu): %d",
				  btrfs_ino(BTRFS_I(inode)),
				  root->root_key.objectid, ret);
	पूर्ण
	अगर (path != in_path)
		btrfs_मुक्त_path(path);

	अगर (!maybe_acls)
		cache_no_acl(inode);

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFREG:
		inode->i_mapping->a_ops = &btrfs_aops;
		inode->i_fop = &btrfs_file_operations;
		inode->i_op = &btrfs_file_inode_operations;
		अवरोध;
	हाल S_IFसूची:
		inode->i_fop = &btrfs_dir_file_operations;
		inode->i_op = &btrfs_dir_inode_operations;
		अवरोध;
	हाल S_IFLNK:
		inode->i_op = &btrfs_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &btrfs_aops;
		अवरोध;
	शेष:
		inode->i_op = &btrfs_special_inode_operations;
		init_special_inode(inode, inode->i_mode, rdev);
		अवरोध;
	पूर्ण

	btrfs_sync_inode_flags_to_i_flags(inode);
	वापस 0;
पूर्ण

/*
 * given a leaf and an inode, copy the inode fields पूर्णांकo the leaf
 */
अटल व्योम fill_inode_item(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा extent_buffer *leaf,
			    काष्ठा btrfs_inode_item *item,
			    काष्ठा inode *inode)
अणु
	काष्ठा btrfs_map_token token;

	btrfs_init_map_token(&token, leaf);

	btrfs_set_token_inode_uid(&token, item, i_uid_पढ़ो(inode));
	btrfs_set_token_inode_gid(&token, item, i_gid_पढ़ो(inode));
	btrfs_set_token_inode_size(&token, item, BTRFS_I(inode)->disk_i_size);
	btrfs_set_token_inode_mode(&token, item, inode->i_mode);
	btrfs_set_token_inode_nlink(&token, item, inode->i_nlink);

	btrfs_set_token_बारpec_sec(&token, &item->aसमय,
				     inode->i_aसमय.tv_sec);
	btrfs_set_token_बारpec_nsec(&token, &item->aसमय,
				      inode->i_aसमय.tv_nsec);

	btrfs_set_token_बारpec_sec(&token, &item->mसमय,
				     inode->i_mसमय.tv_sec);
	btrfs_set_token_बारpec_nsec(&token, &item->mसमय,
				      inode->i_mसमय.tv_nsec);

	btrfs_set_token_बारpec_sec(&token, &item->स_समय,
				     inode->i_स_समय.tv_sec);
	btrfs_set_token_बारpec_nsec(&token, &item->स_समय,
				      inode->i_स_समय.tv_nsec);

	btrfs_set_token_बारpec_sec(&token, &item->oसमय,
				     BTRFS_I(inode)->i_oसमय.tv_sec);
	btrfs_set_token_बारpec_nsec(&token, &item->oसमय,
				      BTRFS_I(inode)->i_oसमय.tv_nsec);

	btrfs_set_token_inode_nbytes(&token, item, inode_get_bytes(inode));
	btrfs_set_token_inode_generation(&token, item,
					 BTRFS_I(inode)->generation);
	btrfs_set_token_inode_sequence(&token, item, inode_peek_iversion(inode));
	btrfs_set_token_inode_transid(&token, item, trans->transid);
	btrfs_set_token_inode_rdev(&token, item, inode->i_rdev);
	btrfs_set_token_inode_flags(&token, item, BTRFS_I(inode)->flags);
	btrfs_set_token_inode_block_group(&token, item, 0);
पूर्ण

/*
 * copy everything in the in-memory inode पूर्णांकo the btree.
 */
अटल noअंतरभूत पूर्णांक btrfs_update_inode_item(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_root *root,
				काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_inode_item *inode_item;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_lookup_inode(trans, root, path, &inode->location, 1);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = -ENOENT;
		जाओ failed;
	पूर्ण

	leaf = path->nodes[0];
	inode_item = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_inode_item);

	fill_inode_item(trans, leaf, inode_item, &inode->vfs_inode);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_set_inode_last_trans(trans, inode);
	ret = 0;
failed:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * copy everything in the in-memory inode पूर्णांकo the btree.
 */
noअंतरभूत पूर्णांक btrfs_update_inode(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_root *root,
				काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret;

	/*
	 * If the inode is a मुक्त space inode, we can deadlock during commit
	 * अगर we put it पूर्णांकo the delayed code.
	 *
	 * The data relocation inode should also be directly updated
	 * without delay
	 */
	अगर (!btrfs_is_मुक्त_space_inode(inode)
	    && root->root_key.objectid != BTRFS_DATA_RELOC_TREE_OBJECTID
	    && !test_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags)) अणु
		btrfs_update_root_बार(trans, root);

		ret = btrfs_delayed_update_inode(trans, root, inode);
		अगर (!ret)
			btrfs_set_inode_last_trans(trans, inode);
		वापस ret;
	पूर्ण

	वापस btrfs_update_inode_item(trans, root, inode);
पूर्ण

पूर्णांक btrfs_update_inode_fallback(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode)
अणु
	पूर्णांक ret;

	ret = btrfs_update_inode(trans, root, inode);
	अगर (ret == -ENOSPC)
		वापस btrfs_update_inode_item(trans, root, inode);
	वापस ret;
पूर्ण

/*
 * unlink helper that माला_लो used here in inode.c and in the tree logging
 * recovery code.  It हटाओ a link in a directory with a given name, and
 * also drops the back refs in the inode to the directory
 */
अटल पूर्णांक __btrfs_unlink_inode(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_root *root,
				काष्ठा btrfs_inode *dir,
				काष्ठा btrfs_inode *inode,
				स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_path *path;
	पूर्णांक ret = 0;
	काष्ठा btrfs_dir_item *di;
	u64 index;
	u64 ino = btrfs_ino(inode);
	u64 dir_ino = btrfs_ino(dir);

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	di = btrfs_lookup_dir_item(trans, root, path, dir_ino,
				    name, name_len, -1);
	अगर (IS_ERR_OR_शून्य(di)) अणु
		ret = di ? PTR_ERR(di) : -ENOENT;
		जाओ err;
	पूर्ण
	ret = btrfs_delete_one_dir_name(trans, root, path, di);
	अगर (ret)
		जाओ err;
	btrfs_release_path(path);

	/*
	 * If we करोn't have dir index, we have to get it by looking up
	 * the inode ref, since we get the inode ref, हटाओ it directly,
	 * it is unnecessary to करो delayed deletion.
	 *
	 * But अगर we have dir index, needn't search inode ref to get it.
	 * Since the inode ref is बंद to the inode item, it is better
	 * that we delay to delete it, and just करो this deletion when
	 * we update the inode item.
	 */
	अगर (inode->dir_index) अणु
		ret = btrfs_delayed_delete_inode_ref(inode);
		अगर (!ret) अणु
			index = inode->dir_index;
			जाओ skip_backref;
		पूर्ण
	पूर्ण

	ret = btrfs_del_inode_ref(trans, root, name, name_len, ino,
				  dir_ino, &index);
	अगर (ret) अणु
		btrfs_info(fs_info,
			"failed to delete reference to %.*s, inode %llu parent %llu",
			name_len, name, ino, dir_ino);
		btrfs_पात_transaction(trans, ret);
		जाओ err;
	पूर्ण
skip_backref:
	ret = btrfs_delete_delayed_dir_index(trans, dir, index);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ err;
	पूर्ण

	ret = btrfs_del_inode_ref_in_log(trans, root, name, name_len, inode,
			dir_ino);
	अगर (ret != 0 && ret != -ENOENT) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ err;
	पूर्ण

	ret = btrfs_del_dir_entries_in_log(trans, root, name, name_len, dir,
			index);
	अगर (ret == -ENOENT)
		ret = 0;
	अन्यथा अगर (ret)
		btrfs_पात_transaction(trans, ret);

	/*
	 * If we have a pending delayed iput we could end up with the final iput
	 * being run in btrfs-cleaner context.  If we have enough of these built
	 * up we can end up burning a lot of समय in btrfs-cleaner without any
	 * way to throttle the unlinks.  Since we're currently holding a ref on
	 * the inode we can run the delayed iput here without any issues as the
	 * final iput won't be done until after we drop the ref we're currently
	 * holding.
	 */
	btrfs_run_delayed_iput(fs_info, inode);
err:
	btrfs_मुक्त_path(path);
	अगर (ret)
		जाओ out;

	btrfs_i_size_ग_लिखो(dir, dir->vfs_inode.i_size - name_len * 2);
	inode_inc_iversion(&inode->vfs_inode);
	inode_inc_iversion(&dir->vfs_inode);
	inode->vfs_inode.i_स_समय = dir->vfs_inode.i_mसमय =
		dir->vfs_inode.i_स_समय = current_समय(&inode->vfs_inode);
	ret = btrfs_update_inode(trans, root, dir);
out:
	वापस ret;
पूर्ण

पूर्णांक btrfs_unlink_inode(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root,
		       काष्ठा btrfs_inode *dir, काष्ठा btrfs_inode *inode,
		       स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	पूर्णांक ret;
	ret = __btrfs_unlink_inode(trans, root, dir, inode, name, name_len);
	अगर (!ret) अणु
		drop_nlink(&inode->vfs_inode);
		ret = btrfs_update_inode(trans, root, inode);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * helper to start transaction क्रम unlink and सूची_हटाओ.
 *
 * unlink and सूची_हटाओ are special in btrfs, they करो not always मुक्त space, so
 * अगर we cannot make our reservations the normal way try and see अगर there is
 * plenty of slack room in the global reserve to migrate, otherwise we cannot
 * allow the unlink to occur.
 */
अटल काष्ठा btrfs_trans_handle *__unlink_start_trans(काष्ठा inode *dir)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;

	/*
	 * 1 क्रम the possible orphan item
	 * 1 क्रम the dir item
	 * 1 क्रम the dir index
	 * 1 क्रम the inode ref
	 * 1 क्रम the inode
	 */
	वापस btrfs_start_transaction_fallback_global_rsv(root, 5);
पूर्ण

अटल पूर्णांक btrfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक ret;

	trans = __unlink_start_trans(dir);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	btrfs_record_unlink_dir(trans, BTRFS_I(dir), BTRFS_I(d_inode(dentry)),
			0);

	ret = btrfs_unlink_inode(trans, root, BTRFS_I(dir),
			BTRFS_I(d_inode(dentry)), dentry->d_name.name,
			dentry->d_name.len);
	अगर (ret)
		जाओ out;

	अगर (inode->i_nlink == 0) अणु
		ret = btrfs_orphan_add(trans, BTRFS_I(inode));
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	btrfs_end_transaction(trans);
	btrfs_btree_balance_dirty(root->fs_info);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_unlink_subvol(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा btrfs_inode *inode = BTRFS_I(d_inode(dentry));
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_key key;
	स्थिर अक्षर *name = dentry->d_name.name;
	पूर्णांक name_len = dentry->d_name.len;
	u64 index;
	पूर्णांक ret;
	u64 objectid;
	u64 dir_ino = btrfs_ino(BTRFS_I(dir));

	अगर (btrfs_ino(inode) == BTRFS_FIRST_FREE_OBJECTID) अणु
		objectid = inode->root->root_key.objectid;
	पूर्ण अन्यथा अगर (btrfs_ino(inode) == BTRFS_EMPTY_SUBVOL_सूची_OBJECTID) अणु
		objectid = inode->location.objectid;
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	di = btrfs_lookup_dir_item(trans, root, path, dir_ino,
				   name, name_len, -1);
	अगर (IS_ERR_OR_शून्य(di)) अणु
		ret = di ? PTR_ERR(di) : -ENOENT;
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	btrfs_dir_item_key_to_cpu(leaf, di, &key);
	WARN_ON(key.type != BTRFS_ROOT_ITEM_KEY || key.objectid != objectid);
	ret = btrfs_delete_one_dir_name(trans, root, path, di);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण
	btrfs_release_path(path);

	/*
	 * This is a placeholder inode क्रम a subvolume we didn't have a
	 * reference to at the समय of the snapshot creation.  In the meanसमय
	 * we could have नामd the real subvol link पूर्णांकo our snapshot, so
	 * depending on btrfs_del_root_ref to वापस -ENOENT here is incorret.
	 * Instead simply lookup the dir_index_item क्रम this entry so we can
	 * हटाओ it.  Otherwise we know we have a ref to the root and we can
	 * call btrfs_del_root_ref, and it _shouldn't_ fail.
	 */
	अगर (btrfs_ino(inode) == BTRFS_EMPTY_SUBVOL_सूची_OBJECTID) अणु
		di = btrfs_search_dir_index_item(root, path, dir_ino,
						 name, name_len);
		अगर (IS_ERR_OR_शून्य(di)) अणु
			अगर (!di)
				ret = -ENOENT;
			अन्यथा
				ret = PTR_ERR(di);
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण

		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		index = key.offset;
		btrfs_release_path(path);
	पूर्ण अन्यथा अणु
		ret = btrfs_del_root_ref(trans, objectid,
					 root->root_key.objectid, dir_ino,
					 &index, name, name_len);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = btrfs_delete_delayed_dir_index(trans, BTRFS_I(dir), index);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	btrfs_i_size_ग_लिखो(BTRFS_I(dir), dir->i_size - name_len * 2);
	inode_inc_iversion(dir);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	ret = btrfs_update_inode_fallback(trans, root, BTRFS_I(dir));
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Helper to check अगर the subvolume references other subvolumes or अगर it's
 * शेष.
 */
अटल noअंतरभूत पूर्णांक may_destroy_subvol(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_key key;
	u64 dir_id;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/* Make sure this root isn't set as the शेष subvol */
	dir_id = btrfs_super_root_dir(fs_info->super_copy);
	di = btrfs_lookup_dir_item(शून्य, fs_info->tree_root, path,
				   dir_id, "default", 7, 0);
	अगर (di && !IS_ERR(di)) अणु
		btrfs_dir_item_key_to_cpu(path->nodes[0], di, &key);
		अगर (key.objectid == root->root_key.objectid) अणु
			ret = -EPERM;
			btrfs_err(fs_info,
				  "deleting default subvolume %llu is not allowed",
				  key.objectid);
			जाओ out;
		पूर्ण
		btrfs_release_path(path);
	पूर्ण

	key.objectid = root->root_key.objectid;
	key.type = BTRFS_ROOT_REF_KEY;
	key.offset = (u64)-1;

	ret = btrfs_search_slot(शून्य, fs_info->tree_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	BUG_ON(ret == 0);

	ret = 0;
	अगर (path->slots[0] > 0) अणु
		path->slots[0]--;
		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
		अगर (key.objectid == root->root_key.objectid &&
		    key.type == BTRFS_ROOT_REF_KEY)
			ret = -ENOTEMPTY;
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/* Delete all dentries क्रम inodes beदीर्घing to the root */
अटल व्योम btrfs_prune_dentries(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा rb_node *node;
	काष्ठा rb_node *prev;
	काष्ठा btrfs_inode *entry;
	काष्ठा inode *inode;
	u64 objectid = 0;

	अगर (!test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state))
		WARN_ON(btrfs_root_refs(&root->root_item) != 0);

	spin_lock(&root->inode_lock);
again:
	node = root->inode_tree.rb_node;
	prev = शून्य;
	जबतक (node) अणु
		prev = node;
		entry = rb_entry(node, काष्ठा btrfs_inode, rb_node);

		अगर (objectid < btrfs_ino(entry))
			node = node->rb_left;
		अन्यथा अगर (objectid > btrfs_ino(entry))
			node = node->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (!node) अणु
		जबतक (prev) अणु
			entry = rb_entry(prev, काष्ठा btrfs_inode, rb_node);
			अगर (objectid <= btrfs_ino(entry)) अणु
				node = prev;
				अवरोध;
			पूर्ण
			prev = rb_next(prev);
		पूर्ण
	पूर्ण
	जबतक (node) अणु
		entry = rb_entry(node, काष्ठा btrfs_inode, rb_node);
		objectid = btrfs_ino(entry) + 1;
		inode = igrab(&entry->vfs_inode);
		अगर (inode) अणु
			spin_unlock(&root->inode_lock);
			अगर (atomic_पढ़ो(&inode->i_count) > 1)
				d_prune_aliases(inode);
			/*
			 * btrfs_drop_inode will have it हटाओd from the inode
			 * cache when its usage count hits zero.
			 */
			iput(inode);
			cond_resched();
			spin_lock(&root->inode_lock);
			जाओ again;
		पूर्ण

		अगर (cond_resched_lock(&root->inode_lock))
			जाओ again;

		node = rb_next(node);
	पूर्ण
	spin_unlock(&root->inode_lock);
पूर्ण

पूर्णांक btrfs_delete_subvolume(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dentry->d_sb);
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा btrfs_root *dest = BTRFS_I(inode)->root;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_block_rsv block_rsv;
	u64 root_flags;
	पूर्णांक ret;

	/*
	 * Don't allow to delete a subvolume with send in progress. This is
	 * inside the inode lock so the error handling that has to drop the bit
	 * again is not run concurrently.
	 */
	spin_lock(&dest->root_item_lock);
	अगर (dest->send_in_progress) अणु
		spin_unlock(&dest->root_item_lock);
		btrfs_warn(fs_info,
			   "attempt to delete subvolume %llu during send",
			   dest->root_key.objectid);
		वापस -EPERM;
	पूर्ण
	root_flags = btrfs_root_flags(&dest->root_item);
	btrfs_set_root_flags(&dest->root_item,
			     root_flags | BTRFS_ROOT_SUBVOL_DEAD);
	spin_unlock(&dest->root_item_lock);

	करोwn_ग_लिखो(&fs_info->subvol_sem);

	ret = may_destroy_subvol(dest);
	अगर (ret)
		जाओ out_up_ग_लिखो;

	btrfs_init_block_rsv(&block_rsv, BTRFS_BLOCK_RSV_TEMP);
	/*
	 * One क्रम dir inode,
	 * two क्रम dir entries,
	 * two क्रम root ref/backref.
	 */
	ret = btrfs_subvolume_reserve_metadata(root, &block_rsv, 5, true);
	अगर (ret)
		जाओ out_up_ग_लिखो;

	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out_release;
	पूर्ण
	trans->block_rsv = &block_rsv;
	trans->bytes_reserved = block_rsv.size;

	btrfs_record_snapshot_destroy(trans, BTRFS_I(dir));

	ret = btrfs_unlink_subvol(trans, dir, dentry);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_end_trans;
	पूर्ण

	ret = btrfs_record_root_in_trans(trans, dest);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_end_trans;
	पूर्ण

	स_रखो(&dest->root_item.drop_progress, 0,
		माप(dest->root_item.drop_progress));
	btrfs_set_root_drop_level(&dest->root_item, 0);
	btrfs_set_root_refs(&dest->root_item, 0);

	अगर (!test_and_set_bit(BTRFS_ROOT_ORPHAN_ITEM_INSERTED, &dest->state)) अणु
		ret = btrfs_insert_orphan_item(trans,
					fs_info->tree_root,
					dest->root_key.objectid);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out_end_trans;
		पूर्ण
	पूर्ण

	ret = btrfs_uuid_tree_हटाओ(trans, dest->root_item.uuid,
				  BTRFS_UUID_KEY_SUBVOL,
				  dest->root_key.objectid);
	अगर (ret && ret != -ENOENT) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_end_trans;
	पूर्ण
	अगर (!btrfs_is_empty_uuid(dest->root_item.received_uuid)) अणु
		ret = btrfs_uuid_tree_हटाओ(trans,
					  dest->root_item.received_uuid,
					  BTRFS_UUID_KEY_RECEIVED_SUBVOL,
					  dest->root_key.objectid);
		अगर (ret && ret != -ENOENT) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out_end_trans;
		पूर्ण
	पूर्ण

	मुक्त_anon_bdev(dest->anon_dev);
	dest->anon_dev = 0;
out_end_trans:
	trans->block_rsv = शून्य;
	trans->bytes_reserved = 0;
	ret = btrfs_end_transaction(trans);
	inode->i_flags |= S_DEAD;
out_release:
	btrfs_subvolume_release_metadata(root, &block_rsv);
out_up_ग_लिखो:
	up_ग_लिखो(&fs_info->subvol_sem);
	अगर (ret) अणु
		spin_lock(&dest->root_item_lock);
		root_flags = btrfs_root_flags(&dest->root_item);
		btrfs_set_root_flags(&dest->root_item,
				root_flags & ~BTRFS_ROOT_SUBVOL_DEAD);
		spin_unlock(&dest->root_item_lock);
	पूर्ण अन्यथा अणु
		d_invalidate(dentry);
		btrfs_prune_dentries(dest);
		ASSERT(dest->send_in_progress == 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक err = 0;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा btrfs_trans_handle *trans;
	u64 last_unlink_trans;

	अगर (inode->i_size > BTRFS_EMPTY_सूची_SIZE)
		वापस -ENOTEMPTY;
	अगर (btrfs_ino(BTRFS_I(inode)) == BTRFS_FIRST_FREE_OBJECTID)
		वापस btrfs_delete_subvolume(dir, dentry);

	trans = __unlink_start_trans(dir);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	अगर (unlikely(btrfs_ino(BTRFS_I(inode)) == BTRFS_EMPTY_SUBVOL_सूची_OBJECTID)) अणु
		err = btrfs_unlink_subvol(trans, dir, dentry);
		जाओ out;
	पूर्ण

	err = btrfs_orphan_add(trans, BTRFS_I(inode));
	अगर (err)
		जाओ out;

	last_unlink_trans = BTRFS_I(inode)->last_unlink_trans;

	/* now the directory is empty */
	err = btrfs_unlink_inode(trans, root, BTRFS_I(dir),
			BTRFS_I(d_inode(dentry)), dentry->d_name.name,
			dentry->d_name.len);
	अगर (!err) अणु
		btrfs_i_size_ग_लिखो(BTRFS_I(inode), 0);
		/*
		 * Propagate the last_unlink_trans value of the deleted dir to
		 * its parent directory. This is to prevent an unrecoverable
		 * log tree in the हाल we करो something like this:
		 * 1) create dir foo
		 * 2) create snapshot under dir foo
		 * 3) delete the snapshot
		 * 4) सूची_हटाओ foo
		 * 5) सूची_गढ़ो foo
		 * 6) fsync foo or some file inside foo
		 */
		अगर (last_unlink_trans >= trans->transid)
			BTRFS_I(dir)->last_unlink_trans = last_unlink_trans;
	पूर्ण
out:
	btrfs_end_transaction(trans);
	btrfs_btree_balance_dirty(root->fs_info);

	वापस err;
पूर्ण

/*
 * Return this अगर we need to call truncate_block क्रम the last bit of the
 * truncate.
 */
#घोषणा NEED_TRUNCATE_BLOCK 1

/*
 * this can truncate away extent items, csum items and directory items.
 * It starts at a high offset and हटाओs keys until it can't find
 * any higher than new_size
 *
 * csum items that cross the new i_size are truncated to the new size
 * as well.
 *
 * min_type is the minimum key type to truncate करोwn to.  If set to 0, this
 * will समाप्त all the items on this inode, including the INODE_ITEM_KEY.
 */
पूर्णांक btrfs_truncate_inode_items(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       काष्ठा btrfs_inode *inode,
			       u64 new_size, u32 min_type)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	u64 extent_start = 0;
	u64 extent_num_bytes = 0;
	u64 extent_offset = 0;
	u64 item_end = 0;
	u64 last_size = new_size;
	u32 found_type = (u8)-1;
	पूर्णांक found_extent;
	पूर्णांक del_item;
	पूर्णांक pending_del_nr = 0;
	पूर्णांक pending_del_slot = 0;
	पूर्णांक extent_type = -1;
	पूर्णांक ret;
	u64 ino = btrfs_ino(inode);
	u64 bytes_deleted = 0;
	bool be_nice = false;
	bool should_throttle = false;
	स्थिर u64 lock_start = ALIGN_DOWN(new_size, fs_info->sectorsize);
	काष्ठा extent_state *cached_state = शून्य;

	BUG_ON(new_size > 0 && min_type != BTRFS_EXTENT_DATA_KEY);

	/*
	 * For non-मुक्त space inodes and non-shareable roots, we want to back
	 * off from समय to समय.  This means all inodes in subvolume roots,
	 * reloc roots, and data reloc roots.
	 */
	अगर (!btrfs_is_मुक्त_space_inode(inode) &&
	    test_bit(BTRFS_ROOT_SHAREABLE, &root->state))
		be_nice = true;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	path->पढ़ोa = READA_BACK;

	अगर (root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID) अणु
		lock_extent_bits(&inode->io_tree, lock_start, (u64)-1,
				 &cached_state);

		/*
		 * We want to drop from the next block क्रमward in हाल this
		 * new size is not block aligned since we will be keeping the
		 * last block of the extent just the way it is.
		 */
		btrfs_drop_extent_cache(inode, ALIGN(new_size,
					fs_info->sectorsize),
					(u64)-1, 0);
	पूर्ण

	/*
	 * This function is also used to drop the items in the log tree beक्रमe
	 * we relog the inode, so अगर root != BTRFS_I(inode)->root, it means
	 * it is used to drop the logged items. So we shouldn't समाप्त the delayed
	 * items.
	 */
	अगर (min_type == 0 && root == inode->root)
		btrfs_समाप्त_delayed_inode_items(inode);

	key.objectid = ino;
	key.offset = (u64)-1;
	key.type = (u8)-1;

search_again:
	/*
	 * with a 16K leaf size and 128MB extents, you can actually queue
	 * up a huge file in a single leaf.  Most of the समय that
	 * bytes_deleted is > 0, it will be huge by the समय we get here
	 */
	अगर (be_nice && bytes_deleted > SZ_32M &&
	    btrfs_should_end_transaction(trans)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret < 0)
		जाओ out;

	अगर (ret > 0) अणु
		ret = 0;
		/* there are no items in the tree क्रम us to truncate, we're
		 * करोne
		 */
		अगर (path->slots[0] == 0)
			जाओ out;
		path->slots[0]--;
	पूर्ण

	जबतक (1) अणु
		u64 clear_start = 0, clear_len = 0;

		fi = शून्य;
		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
		found_type = found_key.type;

		अगर (found_key.objectid != ino)
			अवरोध;

		अगर (found_type < min_type)
			अवरोध;

		item_end = found_key.offset;
		अगर (found_type == BTRFS_EXTENT_DATA_KEY) अणु
			fi = btrfs_item_ptr(leaf, path->slots[0],
					    काष्ठा btrfs_file_extent_item);
			extent_type = btrfs_file_extent_type(leaf, fi);
			अगर (extent_type != BTRFS_खाता_EXTENT_INLINE) अणु
				item_end +=
				    btrfs_file_extent_num_bytes(leaf, fi);

				trace_btrfs_truncate_show_fi_regular(
					inode, leaf, fi, found_key.offset);
			पूर्ण अन्यथा अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
				item_end += btrfs_file_extent_ram_bytes(leaf,
									fi);

				trace_btrfs_truncate_show_fi_अंतरभूत(
					inode, leaf, fi, path->slots[0],
					found_key.offset);
			पूर्ण
			item_end--;
		पूर्ण
		अगर (found_type > min_type) अणु
			del_item = 1;
		पूर्ण अन्यथा अणु
			अगर (item_end < new_size)
				अवरोध;
			अगर (found_key.offset >= new_size)
				del_item = 1;
			अन्यथा
				del_item = 0;
		पूर्ण
		found_extent = 0;
		/* FIXME, shrink the extent अगर the ref count is only 1 */
		अगर (found_type != BTRFS_EXTENT_DATA_KEY)
			जाओ delete;

		अगर (extent_type != BTRFS_खाता_EXTENT_INLINE) अणु
			u64 num_dec;

			clear_start = found_key.offset;
			extent_start = btrfs_file_extent_disk_bytenr(leaf, fi);
			अगर (!del_item) अणु
				u64 orig_num_bytes =
					btrfs_file_extent_num_bytes(leaf, fi);
				extent_num_bytes = ALIGN(new_size -
						found_key.offset,
						fs_info->sectorsize);
				clear_start = ALIGN(new_size, fs_info->sectorsize);
				btrfs_set_file_extent_num_bytes(leaf, fi,
							 extent_num_bytes);
				num_dec = (orig_num_bytes -
					   extent_num_bytes);
				अगर (test_bit(BTRFS_ROOT_SHAREABLE,
					     &root->state) &&
				    extent_start != 0)
					inode_sub_bytes(&inode->vfs_inode,
							num_dec);
				btrfs_mark_buffer_dirty(leaf);
			पूर्ण अन्यथा अणु
				extent_num_bytes =
					btrfs_file_extent_disk_num_bytes(leaf,
									 fi);
				extent_offset = found_key.offset -
					btrfs_file_extent_offset(leaf, fi);

				/* FIXME blocksize != 4096 */
				num_dec = btrfs_file_extent_num_bytes(leaf, fi);
				अगर (extent_start != 0) अणु
					found_extent = 1;
					अगर (test_bit(BTRFS_ROOT_SHAREABLE,
						     &root->state))
						inode_sub_bytes(&inode->vfs_inode,
								num_dec);
				पूर्ण
			पूर्ण
			clear_len = num_dec;
		पूर्ण अन्यथा अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
			/*
			 * we can't truncate अंतरभूत items that have had
			 * special encodings
			 */
			अगर (!del_item &&
			    btrfs_file_extent_encryption(leaf, fi) == 0 &&
			    btrfs_file_extent_other_encoding(leaf, fi) == 0 &&
			    btrfs_file_extent_compression(leaf, fi) == 0) अणु
				u32 size = (u32)(new_size - found_key.offset);

				btrfs_set_file_extent_ram_bytes(leaf, fi, size);
				size = btrfs_file_extent_calc_अंतरभूत_size(size);
				btrfs_truncate_item(path, size, 1);
			पूर्ण अन्यथा अगर (!del_item) अणु
				/*
				 * We have to bail so the last_size is set to
				 * just beक्रमe this extent.
				 */
				ret = NEED_TRUNCATE_BLOCK;
				अवरोध;
			पूर्ण अन्यथा अणु
				/*
				 * Inline extents are special, we just treat
				 * them as a full sector worth in the file
				 * extent tree just क्रम simplicity sake.
				 */
				clear_len = fs_info->sectorsize;
			पूर्ण

			अगर (test_bit(BTRFS_ROOT_SHAREABLE, &root->state))
				inode_sub_bytes(&inode->vfs_inode,
						item_end + 1 - new_size);
		पूर्ण
delete:
		/*
		 * We use btrfs_truncate_inode_items() to clean up log trees क्रम
		 * multiple fsyncs, and in this हाल we करोn't want to clear the
		 * file extent range because it's just the log.
		 */
		अगर (root == inode->root) अणु
			ret = btrfs_inode_clear_file_extent_range(inode,
						  clear_start, clear_len);
			अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (del_item)
			last_size = found_key.offset;
		अन्यथा
			last_size = new_size;
		अगर (del_item) अणु
			अगर (!pending_del_nr) अणु
				/* no pending yet, add ourselves */
				pending_del_slot = path->slots[0];
				pending_del_nr = 1;
			पूर्ण अन्यथा अगर (pending_del_nr &&
				   path->slots[0] + 1 == pending_del_slot) अणु
				/* hop on the pending chunk */
				pending_del_nr++;
				pending_del_slot = path->slots[0];
			पूर्ण अन्यथा अणु
				BUG();
			पूर्ण
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
		should_throttle = false;

		अगर (found_extent &&
		    root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID) अणु
			काष्ठा btrfs_ref ref = अणु 0 पूर्ण;

			bytes_deleted += extent_num_bytes;

			btrfs_init_generic_ref(&ref, BTRFS_DROP_DELAYED_REF,
					extent_start, extent_num_bytes, 0);
			ref.real_root = root->root_key.objectid;
			btrfs_init_data_ref(&ref, btrfs_header_owner(leaf),
					ino, extent_offset);
			ret = btrfs_मुक्त_extent(trans, &ref);
			अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
				अवरोध;
			पूर्ण
			अगर (be_nice) अणु
				अगर (btrfs_should_throttle_delayed_refs(trans))
					should_throttle = true;
			पूर्ण
		पूर्ण

		अगर (found_type == BTRFS_INODE_ITEM_KEY)
			अवरोध;

		अगर (path->slots[0] == 0 ||
		    path->slots[0] != pending_del_slot ||
		    should_throttle) अणु
			अगर (pending_del_nr) अणु
				ret = btrfs_del_items(trans, root, path,
						pending_del_slot,
						pending_del_nr);
				अगर (ret) अणु
					btrfs_पात_transaction(trans, ret);
					अवरोध;
				पूर्ण
				pending_del_nr = 0;
			पूर्ण
			btrfs_release_path(path);

			/*
			 * We can generate a lot of delayed refs, so we need to
			 * throttle every once and a जबतक and make sure we're
			 * adding enough space to keep up with the work we are
			 * generating.  Since we hold a transaction here we
			 * can't flush, and we don't want to FLUSH_LIMIT because
			 * we could have generated too many delayed refs to
			 * actually allocate, so just bail अगर we're लघु and
			 * let the normal reservation dance happen higher up.
			 */
			अगर (should_throttle) अणु
				ret = btrfs_delayed_refs_rsv_refill(fs_info,
							BTRFS_RESERVE_NO_FLUSH);
				अगर (ret) अणु
					ret = -EAGAIN;
					अवरोध;
				पूर्ण
			पूर्ण
			जाओ search_again;
		पूर्ण अन्यथा अणु
			path->slots[0]--;
		पूर्ण
	पूर्ण
out:
	अगर (ret >= 0 && pending_del_nr) अणु
		पूर्णांक err;

		err = btrfs_del_items(trans, root, path, pending_del_slot,
				      pending_del_nr);
		अगर (err) अणु
			btrfs_पात_transaction(trans, err);
			ret = err;
		पूर्ण
	पूर्ण
	अगर (root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID) अणु
		ASSERT(last_size >= new_size);
		अगर (!ret && last_size > new_size)
			last_size = new_size;
		btrfs_inode_safe_disk_i_size_ग_लिखो(inode, last_size);
		unlock_extent_cached(&inode->io_tree, lock_start, (u64)-1,
				     &cached_state);
	पूर्ण

	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * btrfs_truncate_block - पढ़ो, zero a chunk and ग_लिखो a block
 * @inode - inode that we're zeroing
 * @from - the offset to start zeroing
 * @len - the length to zero, 0 to zero the entire range respective to the
 *	offset
 * @front - zero up to the offset instead of from the offset on
 *
 * This will find the block क्रम the "from" offset and cow the block and zero the
 * part we want to zero.  This is used with truncate and hole punching.
 */
पूर्णांक btrfs_truncate_block(काष्ठा btrfs_inode *inode, loff_t from, loff_t len,
			 पूर्णांक front)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा address_space *mapping = inode->vfs_inode.i_mapping;
	काष्ठा extent_io_tree *io_tree = &inode->io_tree;
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा extent_changeset *data_reserved = शून्य;
	bool only_release_metadata = false;
	u32 blocksize = fs_info->sectorsize;
	pgoff_t index = from >> PAGE_SHIFT;
	अचिन्हित offset = from & (blocksize - 1);
	काष्ठा page *page;
	gfp_t mask = btrfs_alloc_ग_लिखो_mask(mapping);
	माप_प्रकार ग_लिखो_bytes = blocksize;
	पूर्णांक ret = 0;
	u64 block_start;
	u64 block_end;

	अगर (IS_ALIGNED(offset, blocksize) &&
	    (!len || IS_ALIGNED(len, blocksize)))
		जाओ out;

	block_start = round_करोwn(from, blocksize);
	block_end = block_start + blocksize - 1;

	ret = btrfs_check_data_मुक्त_space(inode, &data_reserved, block_start,
					  blocksize);
	अगर (ret < 0) अणु
		अगर (btrfs_check_nocow_lock(inode, block_start, &ग_लिखो_bytes) > 0) अणु
			/* For nocow हाल, no need to reserve data space */
			only_release_metadata = true;
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण
	पूर्ण
	ret = btrfs_delalloc_reserve_metadata(inode, blocksize);
	अगर (ret < 0) अणु
		अगर (!only_release_metadata)
			btrfs_मुक्त_reserved_data_space(inode, data_reserved,
						       block_start, blocksize);
		जाओ out;
	पूर्ण
again:
	page = find_or_create_page(mapping, index, mask);
	अगर (!page) अणु
		btrfs_delalloc_release_space(inode, data_reserved, block_start,
					     blocksize, true);
		btrfs_delalloc_release_extents(inode, blocksize);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ret = set_page_extent_mapped(page);
	अगर (ret < 0)
		जाओ out_unlock;

	अगर (!PageUptodate(page)) अणु
		ret = btrfs_पढ़ोpage(शून्य, page);
		lock_page(page);
		अगर (page->mapping != mapping) अणु
			unlock_page(page);
			put_page(page);
			जाओ again;
		पूर्ण
		अगर (!PageUptodate(page)) अणु
			ret = -EIO;
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	रुको_on_page_ग_लिखोback(page);

	lock_extent_bits(io_tree, block_start, block_end, &cached_state);

	ordered = btrfs_lookup_ordered_extent(inode, block_start);
	अगर (ordered) अणु
		unlock_extent_cached(io_tree, block_start, block_end,
				     &cached_state);
		unlock_page(page);
		put_page(page);
		btrfs_start_ordered_extent(ordered, 1);
		btrfs_put_ordered_extent(ordered);
		जाओ again;
	पूर्ण

	clear_extent_bit(&inode->io_tree, block_start, block_end,
			 EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING | EXTENT_DEFRAG,
			 0, 0, &cached_state);

	ret = btrfs_set_extent_delalloc(inode, block_start, block_end, 0,
					&cached_state);
	अगर (ret) अणु
		unlock_extent_cached(io_tree, block_start, block_end,
				     &cached_state);
		जाओ out_unlock;
	पूर्ण

	अगर (offset != blocksize) अणु
		अगर (!len)
			len = blocksize - offset;
		अगर (front)
			memzero_page(page, (block_start - page_offset(page)),
				     offset);
		अन्यथा
			memzero_page(page, (block_start - page_offset(page)) + offset,
				     len);
		flush_dcache_page(page);
	पूर्ण
	ClearPageChecked(page);
	set_page_dirty(page);
	unlock_extent_cached(io_tree, block_start, block_end, &cached_state);

	अगर (only_release_metadata)
		set_extent_bit(&inode->io_tree, block_start, block_end,
			       EXTENT_NORESERVE, 0, शून्य, शून्य, GFP_NOFS, शून्य);

out_unlock:
	अगर (ret) अणु
		अगर (only_release_metadata)
			btrfs_delalloc_release_metadata(inode, blocksize, true);
		अन्यथा
			btrfs_delalloc_release_space(inode, data_reserved,
					block_start, blocksize, true);
	पूर्ण
	btrfs_delalloc_release_extents(inode, blocksize);
	unlock_page(page);
	put_page(page);
out:
	अगर (only_release_metadata)
		btrfs_check_nocow_unlock(inode);
	extent_changeset_मुक्त(data_reserved);
	वापस ret;
पूर्ण

अटल पूर्णांक maybe_insert_hole(काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode,
			     u64 offset, u64 len)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_drop_extents_args drop_args = अणु 0 पूर्ण;
	पूर्णांक ret;

	/*
	 * Still need to make sure the inode looks like it's been updated so
	 * that any holes get logged अगर we fsync.
	 */
	अगर (btrfs_fs_incompat(fs_info, NO_HOLES)) अणु
		inode->last_trans = fs_info->generation;
		inode->last_sub_trans = root->log_transid;
		inode->last_log_commit = root->last_log_commit;
		वापस 0;
	पूर्ण

	/*
	 * 1 - क्रम the one we're dropping
	 * 1 - क्रम the one we're adding
	 * 1 - क्रम updating the inode.
	 */
	trans = btrfs_start_transaction(root, 3);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	drop_args.start = offset;
	drop_args.end = offset + len;
	drop_args.drop_cache = true;

	ret = btrfs_drop_extents(trans, root, inode, &drop_args);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		btrfs_end_transaction(trans);
		वापस ret;
	पूर्ण

	ret = btrfs_insert_file_extent(trans, root, btrfs_ino(inode),
			offset, 0, 0, len, 0, len, 0, 0, 0);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
	पूर्ण अन्यथा अणु
		btrfs_update_inode_bytes(inode, 0, drop_args.bytes_found);
		btrfs_update_inode(trans, root, inode);
	पूर्ण
	btrfs_end_transaction(trans);
	वापस ret;
पूर्ण

/*
 * This function माला_दो in dummy file extents क्रम the area we're creating a hole
 * क्रम.  So अगर we are truncating this file to a larger size we need to insert
 * these file extents so that btrfs_get_extent will वापस a EXTENT_MAP_HOLE क्रम
 * the range between oldsize and size
 */
पूर्णांक btrfs_cont_expand(काष्ठा btrfs_inode *inode, loff_t oldsize, loff_t size)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_io_tree *io_tree = &inode->io_tree;
	काष्ठा extent_map *em = शून्य;
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा extent_map_tree *em_tree = &inode->extent_tree;
	u64 hole_start = ALIGN(oldsize, fs_info->sectorsize);
	u64 block_end = ALIGN(size, fs_info->sectorsize);
	u64 last_byte;
	u64 cur_offset;
	u64 hole_size;
	पूर्णांक err = 0;

	/*
	 * If our size started in the middle of a block we need to zero out the
	 * rest of the block beक्रमe we expand the i_size, otherwise we could
	 * expose stale data.
	 */
	err = btrfs_truncate_block(inode, oldsize, 0, 0);
	अगर (err)
		वापस err;

	अगर (size <= hole_start)
		वापस 0;

	btrfs_lock_and_flush_ordered_range(inode, hole_start, block_end - 1,
					   &cached_state);
	cur_offset = hole_start;
	जबतक (1) अणु
		em = btrfs_get_extent(inode, शून्य, 0, cur_offset,
				      block_end - cur_offset);
		अगर (IS_ERR(em)) अणु
			err = PTR_ERR(em);
			em = शून्य;
			अवरोध;
		पूर्ण
		last_byte = min(extent_map_end(em), block_end);
		last_byte = ALIGN(last_byte, fs_info->sectorsize);
		hole_size = last_byte - cur_offset;

		अगर (!test_bit(EXTENT_FLAG_PREALLOC, &em->flags)) अणु
			काष्ठा extent_map *hole_em;

			err = maybe_insert_hole(root, inode, cur_offset,
						hole_size);
			अगर (err)
				अवरोध;

			err = btrfs_inode_set_file_extent_range(inode,
							cur_offset, hole_size);
			अगर (err)
				अवरोध;

			btrfs_drop_extent_cache(inode, cur_offset,
						cur_offset + hole_size - 1, 0);
			hole_em = alloc_extent_map();
			अगर (!hole_em) अणु
				set_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
					&inode->runसमय_flags);
				जाओ next;
			पूर्ण
			hole_em->start = cur_offset;
			hole_em->len = hole_size;
			hole_em->orig_start = cur_offset;

			hole_em->block_start = EXTENT_MAP_HOLE;
			hole_em->block_len = 0;
			hole_em->orig_block_len = 0;
			hole_em->ram_bytes = hole_size;
			hole_em->compress_type = BTRFS_COMPRESS_NONE;
			hole_em->generation = fs_info->generation;

			जबतक (1) अणु
				ग_लिखो_lock(&em_tree->lock);
				err = add_extent_mapping(em_tree, hole_em, 1);
				ग_लिखो_unlock(&em_tree->lock);
				अगर (err != -EEXIST)
					अवरोध;
				btrfs_drop_extent_cache(inode, cur_offset,
							cur_offset +
							hole_size - 1, 0);
			पूर्ण
			मुक्त_extent_map(hole_em);
		पूर्ण अन्यथा अणु
			err = btrfs_inode_set_file_extent_range(inode,
							cur_offset, hole_size);
			अगर (err)
				अवरोध;
		पूर्ण
next:
		मुक्त_extent_map(em);
		em = शून्य;
		cur_offset = last_byte;
		अगर (cur_offset >= block_end)
			अवरोध;
	पूर्ण
	मुक्त_extent_map(em);
	unlock_extent_cached(io_tree, hole_start, block_end - 1, &cached_state);
	वापस err;
पूर्ण

अटल पूर्णांक btrfs_setsize(काष्ठा inode *inode, काष्ठा iattr *attr)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_trans_handle *trans;
	loff_t oldsize = i_size_पढ़ो(inode);
	loff_t newsize = attr->ia_size;
	पूर्णांक mask = attr->ia_valid;
	पूर्णांक ret;

	/*
	 * The regular truncate() हाल without ATTR_CTIME and ATTR_MTIME is a
	 * special हाल where we need to update the बार despite not having
	 * these flags set.  For all other operations the VFS set these flags
	 * explicitly अगर it wants a बारtamp update.
	 */
	अगर (newsize != oldsize) अणु
		inode_inc_iversion(inode);
		अगर (!(mask & (ATTR_CTIME | ATTR_MTIME)))
			inode->i_स_समय = inode->i_mसमय =
				current_समय(inode);
	पूर्ण

	अगर (newsize > oldsize) अणु
		/*
		 * Don't करो an expanding truncate जबतक snapshotting is ongoing.
		 * This is to ensure the snapshot captures a fully consistent
		 * state of this file - अगर the snapshot captures this expanding
		 * truncation, it must capture all ग_लिखोs that happened beक्रमe
		 * this truncation.
		 */
		btrfs_drew_ग_लिखो_lock(&root->snapshot_lock);
		ret = btrfs_cont_expand(BTRFS_I(inode), oldsize, newsize);
		अगर (ret) अणु
			btrfs_drew_ग_लिखो_unlock(&root->snapshot_lock);
			वापस ret;
		पूर्ण

		trans = btrfs_start_transaction(root, 1);
		अगर (IS_ERR(trans)) अणु
			btrfs_drew_ग_लिखो_unlock(&root->snapshot_lock);
			वापस PTR_ERR(trans);
		पूर्ण

		i_size_ग_लिखो(inode, newsize);
		btrfs_inode_safe_disk_i_size_ग_लिखो(BTRFS_I(inode), 0);
		pagecache_isize_extended(inode, oldsize, newsize);
		ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
		btrfs_drew_ग_लिखो_unlock(&root->snapshot_lock);
		btrfs_end_transaction(trans);
	पूर्ण अन्यथा अणु
		काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);

		अगर (btrfs_is_zoned(fs_info)) अणु
			ret = btrfs_रुको_ordered_range(inode,
					ALIGN(newsize, fs_info->sectorsize),
					(u64)-1);
			अगर (ret)
				वापस ret;
		पूर्ण

		/*
		 * We're truncating a file that used to have good data करोwn to
		 * zero. Make sure any new ग_लिखोs to the file get on disk
		 * on बंद.
		 */
		अगर (newsize == 0)
			set_bit(BTRFS_INODE_FLUSH_ON_CLOSE,
				&BTRFS_I(inode)->runसमय_flags);

		truncate_setsize(inode, newsize);

		inode_dio_रुको(inode);

		ret = btrfs_truncate(inode, newsize == oldsize);
		अगर (ret && inode->i_nlink) अणु
			पूर्णांक err;

			/*
			 * Truncate failed, so fix up the in-memory size. We
			 * adjusted disk_i_size करोwn as we हटाओd extents, so
			 * रुको क्रम disk_i_size to be stable and then update the
			 * in-memory size to match.
			 */
			err = btrfs_रुको_ordered_range(inode, 0, (u64)-1);
			अगर (err)
				वापस err;
			i_size_ग_लिखो(inode, BTRFS_I(inode)->disk_i_size);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
			 काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	पूर्णांक err;

	अगर (btrfs_root_पढ़ोonly(root))
		वापस -EROFS;

	err = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (err)
		वापस err;

	अगर (S_ISREG(inode->i_mode) && (attr->ia_valid & ATTR_SIZE)) अणु
		err = btrfs_setsize(inode, attr);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (attr->ia_valid) अणु
		setattr_copy(&init_user_ns, inode, attr);
		inode_inc_iversion(inode);
		err = btrfs_dirty_inode(inode);

		अगर (!err && attr->ia_valid & ATTR_MODE)
			err = posix_acl_chmod(&init_user_ns, inode,
					      inode->i_mode);
	पूर्ण

	वापस err;
पूर्ण

/*
 * While truncating the inode pages during eviction, we get the VFS calling
 * btrfs_invalidatepage() against each page of the inode. This is slow because
 * the calls to btrfs_invalidatepage() result in a huge amount of calls to
 * lock_extent_bits() and clear_extent_bit(), which keep merging and splitting
 * extent_state काष्ठाures over and over, wasting lots of समय.
 *
 * Thereक्रमe अगर the inode is being evicted, let btrfs_invalidatepage() skip all
 * those expensive operations on a per page basis and करो only the ordered io
 * finishing, जबतक we release here the extent_map and extent_state काष्ठाures,
 * without the excessive merging and splitting.
 */
अटल व्योम evict_inode_truncate_pages(काष्ठा inode *inode)
अणु
	काष्ठा extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	काष्ठा extent_map_tree *map_tree = &BTRFS_I(inode)->extent_tree;
	काष्ठा rb_node *node;

	ASSERT(inode->i_state & I_FREEING);
	truncate_inode_pages_final(&inode->i_data);

	ग_लिखो_lock(&map_tree->lock);
	जबतक (!RB_EMPTY_ROOT(&map_tree->map.rb_root)) अणु
		काष्ठा extent_map *em;

		node = rb_first_cached(&map_tree->map);
		em = rb_entry(node, काष्ठा extent_map, rb_node);
		clear_bit(EXTENT_FLAG_PINNED, &em->flags);
		clear_bit(EXTENT_FLAG_LOGGING, &em->flags);
		हटाओ_extent_mapping(map_tree, em);
		मुक्त_extent_map(em);
		अगर (need_resched()) अणु
			ग_लिखो_unlock(&map_tree->lock);
			cond_resched();
			ग_लिखो_lock(&map_tree->lock);
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&map_tree->lock);

	/*
	 * Keep looping until we have no more ranges in the io tree.
	 * We can have ongoing bios started by पढ़ोahead that have
	 * their endio callback (extent_io.c:end_bio_extent_पढ़ोpage)
	 * still in progress (unlocked the pages in the bio but did not yet
	 * unlocked the ranges in the io tree). Thereक्रमe this means some
	 * ranges can still be locked and eviction started because beक्रमe
	 * submitting those bios, which are executed by a separate task (work
	 * queue kthपढ़ो), inode references (inode->i_count) were not taken
	 * (which would be dropped in the end io callback of each bio).
	 * Thereक्रमe here we effectively end up रुकोing क्रम those bios and
	 * anyone अन्यथा holding locked ranges without having bumped the inode's
	 * reference count - अगर we करोn't do it, when they access the inode's
	 * io_tree to unlock a range it may be too late, leading to an
	 * use-after-मुक्त issue.
	 */
	spin_lock(&io_tree->lock);
	जबतक (!RB_EMPTY_ROOT(&io_tree->state)) अणु
		काष्ठा extent_state *state;
		काष्ठा extent_state *cached_state = शून्य;
		u64 start;
		u64 end;
		अचिन्हित state_flags;

		node = rb_first(&io_tree->state);
		state = rb_entry(node, काष्ठा extent_state, rb_node);
		start = state->start;
		end = state->end;
		state_flags = state->state;
		spin_unlock(&io_tree->lock);

		lock_extent_bits(io_tree, start, end, &cached_state);

		/*
		 * If still has DELALLOC flag, the extent didn't reach disk,
		 * and its reserved space won't be मुक्तd by delayed_ref.
		 * So we need to मुक्त its reserved space here.
		 * (Refer to comment in btrfs_invalidatepage, हाल 2)
		 *
		 * Note, end is the bytenr of last byte, so we need + 1 here.
		 */
		अगर (state_flags & EXTENT_DELALLOC)
			btrfs_qgroup_मुक्त_data(BTRFS_I(inode), शून्य, start,
					       end - start + 1);

		clear_extent_bit(io_tree, start, end,
				 EXTENT_LOCKED | EXTENT_DELALLOC |
				 EXTENT_DO_ACCOUNTING | EXTENT_DEFRAG, 1, 1,
				 &cached_state);

		cond_resched();
		spin_lock(&io_tree->lock);
	पूर्ण
	spin_unlock(&io_tree->lock);
पूर्ण

अटल काष्ठा btrfs_trans_handle *evict_refill_and_join(काष्ठा btrfs_root *root,
							काष्ठा btrfs_block_rsv *rsv)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	काष्ठा btrfs_trans_handle *trans;
	u64 delayed_refs_extra = btrfs_calc_insert_metadata_size(fs_info, 1);
	पूर्णांक ret;

	/*
	 * Eviction should be taking place at some place safe because of our
	 * delayed iमाला_दो.  However the normal flushing code will run delayed
	 * iमाला_दो, so we cannot use FLUSH_ALL otherwise we'll deadlock.
	 *
	 * We reserve the delayed_refs_extra here again because we can't use
	 * btrfs_start_transaction(root, 0) क्रम the same deadlocky reason as
	 * above.  We reserve our extra bit here because we generate a ton of
	 * delayed refs activity by truncating.
	 *
	 * If we cannot make our reservation we'll attempt to steal from the
	 * global reserve, because we really want to be able to मुक्त up space.
	 */
	ret = btrfs_block_rsv_refill(root, rsv, rsv->size + delayed_refs_extra,
				     BTRFS_RESERVE_FLUSH_EVICT);
	अगर (ret) अणु
		/*
		 * Try to steal from the global reserve अगर there is space क्रम
		 * it.
		 */
		अगर (btrfs_check_space_क्रम_delayed_refs(fs_info) ||
		    btrfs_block_rsv_migrate(global_rsv, rsv, rsv->size, 0)) अणु
			btrfs_warn(fs_info,
				   "could not allocate space for delete; will truncate on mount");
			वापस ERR_PTR(-ENOSPC);
		पूर्ण
		delayed_refs_extra = 0;
	पूर्ण

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans))
		वापस trans;

	अगर (delayed_refs_extra) अणु
		trans->block_rsv = &fs_info->trans_block_rsv;
		trans->bytes_reserved = delayed_refs_extra;
		btrfs_block_rsv_migrate(rsv, trans->block_rsv,
					delayed_refs_extra, 1);
	पूर्ण
	वापस trans;
पूर्ण

व्योम btrfs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_block_rsv *rsv;
	पूर्णांक ret;

	trace_btrfs_inode_evict(inode);

	अगर (!root) अणु
		clear_inode(inode);
		वापस;
	पूर्ण

	evict_inode_truncate_pages(inode);

	अगर (inode->i_nlink &&
	    ((btrfs_root_refs(&root->root_item) != 0 &&
	      root->root_key.objectid != BTRFS_ROOT_TREE_OBJECTID) ||
	     btrfs_is_मुक्त_space_inode(BTRFS_I(inode))))
		जाओ no_delete;

	अगर (is_bad_inode(inode))
		जाओ no_delete;

	btrfs_मुक्त_io_failure_record(BTRFS_I(inode), 0, (u64)-1);

	अगर (test_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags))
		जाओ no_delete;

	अगर (inode->i_nlink > 0) अणु
		BUG_ON(btrfs_root_refs(&root->root_item) != 0 &&
		       root->root_key.objectid != BTRFS_ROOT_TREE_OBJECTID);
		जाओ no_delete;
	पूर्ण

	ret = btrfs_commit_inode_delayed_inode(BTRFS_I(inode));
	अगर (ret)
		जाओ no_delete;

	rsv = btrfs_alloc_block_rsv(fs_info, BTRFS_BLOCK_RSV_TEMP);
	अगर (!rsv)
		जाओ no_delete;
	rsv->size = btrfs_calc_metadata_size(fs_info, 1);
	rsv->failfast = 1;

	btrfs_i_size_ग_लिखो(BTRFS_I(inode), 0);

	जबतक (1) अणु
		trans = evict_refill_and_join(root, rsv);
		अगर (IS_ERR(trans))
			जाओ मुक्त_rsv;

		trans->block_rsv = rsv;

		ret = btrfs_truncate_inode_items(trans, root, BTRFS_I(inode),
						 0, 0);
		trans->block_rsv = &fs_info->trans_block_rsv;
		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty(fs_info);
		अगर (ret && ret != -ENOSPC && ret != -EAGAIN)
			जाओ मुक्त_rsv;
		अन्यथा अगर (!ret)
			अवरोध;
	पूर्ण

	/*
	 * Errors here aren't a big deal, it just means we leave orphan items in
	 * the tree. They will be cleaned up on the next mount. If the inode
	 * number माला_लो reused, cleanup deletes the orphan item without करोing
	 * anything, and unlink reuses the existing orphan item.
	 *
	 * If it turns out that we are dropping too many of these, we might want
	 * to add a mechanism क्रम retrying these after a commit.
	 */
	trans = evict_refill_and_join(root, rsv);
	अगर (!IS_ERR(trans)) अणु
		trans->block_rsv = rsv;
		btrfs_orphan_del(trans, BTRFS_I(inode));
		trans->block_rsv = &fs_info->trans_block_rsv;
		btrfs_end_transaction(trans);
	पूर्ण

मुक्त_rsv:
	btrfs_मुक्त_block_rsv(fs_info, rsv);
no_delete:
	/*
	 * If we didn't successfully delete, the orphan item will still be in
	 * the tree and we'll retry on the next mount. Again, we might also want
	 * to retry these periodically in the future.
	 */
	btrfs_हटाओ_delayed_node(BTRFS_I(inode));
	clear_inode(inode);
पूर्ण

/*
 * Return the key found in the dir entry in the location poपूर्णांकer, fill @type
 * with BTRFS_FT_*, and वापस 0.
 *
 * If no dir entries were found, वापसs -ENOENT.
 * If found a corrupted location in dir entry, वापसs -EUCLEAN.
 */
अटल पूर्णांक btrfs_inode_by_name(काष्ठा inode *dir, काष्ठा dentry *dentry,
			       काष्ठा btrfs_key *location, u8 *type)
अणु
	स्थिर अक्षर *name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	पूर्णांक ret = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	di = btrfs_lookup_dir_item(शून्य, root, path, btrfs_ino(BTRFS_I(dir)),
			name, namelen, 0);
	अगर (IS_ERR_OR_शून्य(di)) अणु
		ret = di ? PTR_ERR(di) : -ENOENT;
		जाओ out;
	पूर्ण

	btrfs_dir_item_key_to_cpu(path->nodes[0], di, location);
	अगर (location->type != BTRFS_INODE_ITEM_KEY &&
	    location->type != BTRFS_ROOT_ITEM_KEY) अणु
		ret = -EUCLEAN;
		btrfs_warn(root->fs_info,
"%s gets something invalid in DIR_ITEM (name %s, directory ino %llu, location(%llu %u %llu))",
			   __func__, name, btrfs_ino(BTRFS_I(dir)),
			   location->objectid, location->type, location->offset);
	पूर्ण
	अगर (!ret)
		*type = btrfs_dir_type(path->nodes[0], di);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * when we hit a tree root in a directory, the btrfs part of the inode
 * needs to be changed to reflect the root directory of the tree root.  This
 * is kind of like crossing a mount poपूर्णांक.
 */
अटल पूर्णांक fixup_tree_root_location(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा inode *dir,
				    काष्ठा dentry *dentry,
				    काष्ठा btrfs_key *location,
				    काष्ठा btrfs_root **sub_root)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *new_root;
	काष्ठा btrfs_root_ref *ref;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	पूर्णांक ret;
	पूर्णांक err = 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = -ENOENT;
	key.objectid = BTRFS_I(dir)->root->root_key.objectid;
	key.type = BTRFS_ROOT_REF_KEY;
	key.offset = location->objectid;

	ret = btrfs_search_slot(शून्य, fs_info->tree_root, &key, path, 0, 0);
	अगर (ret) अणु
		अगर (ret < 0)
			err = ret;
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	ref = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_root_ref);
	अगर (btrfs_root_ref_dirid(leaf, ref) != btrfs_ino(BTRFS_I(dir)) ||
	    btrfs_root_ref_name_len(leaf, ref) != dentry->d_name.len)
		जाओ out;

	ret = स_भेद_extent_buffer(leaf, dentry->d_name.name,
				   (अचिन्हित दीर्घ)(ref + 1),
				   dentry->d_name.len);
	अगर (ret)
		जाओ out;

	btrfs_release_path(path);

	new_root = btrfs_get_fs_root(fs_info, location->objectid, true);
	अगर (IS_ERR(new_root)) अणु
		err = PTR_ERR(new_root);
		जाओ out;
	पूर्ण

	*sub_root = new_root;
	location->objectid = btrfs_root_dirid(&new_root->root_item);
	location->type = BTRFS_INODE_ITEM_KEY;
	location->offset = 0;
	err = 0;
out:
	btrfs_मुक्त_path(path);
	वापस err;
पूर्ण

अटल व्योम inode_tree_add(काष्ठा inode *inode)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_inode *entry;
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent;
	काष्ठा rb_node *new = &BTRFS_I(inode)->rb_node;
	u64 ino = btrfs_ino(BTRFS_I(inode));

	अगर (inode_unhashed(inode))
		वापस;
	parent = शून्य;
	spin_lock(&root->inode_lock);
	p = &root->inode_tree.rb_node;
	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा btrfs_inode, rb_node);

		अगर (ino < btrfs_ino(entry))
			p = &parent->rb_left;
		अन्यथा अगर (ino > btrfs_ino(entry))
			p = &parent->rb_right;
		अन्यथा अणु
			WARN_ON(!(entry->vfs_inode.i_state &
				  (I_WILL_FREE | I_FREEING)));
			rb_replace_node(parent, new, &root->inode_tree);
			RB_CLEAR_NODE(parent);
			spin_unlock(&root->inode_lock);
			वापस;
		पूर्ण
	पूर्ण
	rb_link_node(new, parent, p);
	rb_insert_color(new, &root->inode_tree);
	spin_unlock(&root->inode_lock);
पूर्ण

अटल व्योम inode_tree_del(काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_root *root = inode->root;
	पूर्णांक empty = 0;

	spin_lock(&root->inode_lock);
	अगर (!RB_EMPTY_NODE(&inode->rb_node)) अणु
		rb_erase(&inode->rb_node, &root->inode_tree);
		RB_CLEAR_NODE(&inode->rb_node);
		empty = RB_EMPTY_ROOT(&root->inode_tree);
	पूर्ण
	spin_unlock(&root->inode_lock);

	अगर (empty && btrfs_root_refs(&root->root_item) == 0) अणु
		spin_lock(&root->inode_lock);
		empty = RB_EMPTY_ROOT(&root->inode_tree);
		spin_unlock(&root->inode_lock);
		अगर (empty)
			btrfs_add_dead_root(root);
	पूर्ण
पूर्ण


अटल पूर्णांक btrfs_init_locked_inode(काष्ठा inode *inode, व्योम *p)
अणु
	काष्ठा btrfs_iget_args *args = p;

	inode->i_ino = args->ino;
	BTRFS_I(inode)->location.objectid = args->ino;
	BTRFS_I(inode)->location.type = BTRFS_INODE_ITEM_KEY;
	BTRFS_I(inode)->location.offset = 0;
	BTRFS_I(inode)->root = btrfs_grab_root(args->root);
	BUG_ON(args->root && !BTRFS_I(inode)->root);
	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_find_actor(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा btrfs_iget_args *args = opaque;

	वापस args->ino == BTRFS_I(inode)->location.objectid &&
		args->root == BTRFS_I(inode)->root;
पूर्ण

अटल काष्ठा inode *btrfs_iget_locked(काष्ठा super_block *s, u64 ino,
				       काष्ठा btrfs_root *root)
अणु
	काष्ठा inode *inode;
	काष्ठा btrfs_iget_args args;
	अचिन्हित दीर्घ hashval = btrfs_inode_hash(ino, root);

	args.ino = ino;
	args.root = root;

	inode = iget5_locked(s, hashval, btrfs_find_actor,
			     btrfs_init_locked_inode,
			     (व्योम *)&args);
	वापस inode;
पूर्ण

/*
 * Get an inode object given its inode number and corresponding root.
 * Path can be pपुनः_स्मृतिated to prevent recursing back to iget through
 * allocator. शून्य is also valid but may require an additional allocation
 * later.
 */
काष्ठा inode *btrfs_iget_path(काष्ठा super_block *s, u64 ino,
			      काष्ठा btrfs_root *root, काष्ठा btrfs_path *path)
अणु
	काष्ठा inode *inode;

	inode = btrfs_iget_locked(s, ino, root);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	अगर (inode->i_state & I_NEW) अणु
		पूर्णांक ret;

		ret = btrfs_पढ़ो_locked_inode(inode, path);
		अगर (!ret) अणु
			inode_tree_add(inode);
			unlock_new_inode(inode);
		पूर्ण अन्यथा अणु
			iget_failed(inode);
			/*
			 * ret > 0 can come from btrfs_search_slot called by
			 * btrfs_पढ़ो_locked_inode, this means the inode item
			 * was not found.
			 */
			अगर (ret > 0)
				ret = -ENOENT;
			inode = ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस inode;
पूर्ण

काष्ठा inode *btrfs_iget(काष्ठा super_block *s, u64 ino, काष्ठा btrfs_root *root)
अणु
	वापस btrfs_iget_path(s, ino, root, शून्य);
पूर्ण

अटल काष्ठा inode *new_simple_dir(काष्ठा super_block *s,
				    काष्ठा btrfs_key *key,
				    काष्ठा btrfs_root *root)
अणु
	काष्ठा inode *inode = new_inode(s);

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	BTRFS_I(inode)->root = btrfs_grab_root(root);
	स_नकल(&BTRFS_I(inode)->location, key, माप(*key));
	set_bit(BTRFS_INODE_DUMMY, &BTRFS_I(inode)->runसमय_flags);

	inode->i_ino = BTRFS_EMPTY_SUBVOL_सूची_OBJECTID;
	/*
	 * We only need lookup, the rest is पढ़ो-only and there's no inode
	 * associated with the dentry
	 */
	inode->i_op = &simple_dir_inode_operations;
	inode->i_opflags &= ~IOP_XATTR;
	inode->i_fop = &simple_dir_operations;
	inode->i_mode = S_IFसूची | S_IRUGO | S_IWUSR | S_IXUGO;
	inode->i_mसमय = current_समय(inode);
	inode->i_aसमय = inode->i_mसमय;
	inode->i_स_समय = inode->i_mसमय;
	BTRFS_I(inode)->i_oसमय = inode->i_mसमय;

	वापस inode;
पूर्ण

अटल अंतरभूत u8 btrfs_inode_type(काष्ठा inode *inode)
अणु
	/*
	 * Compile-समय निश्चितs that generic FT_* types still match
	 * BTRFS_FT_* types
	 */
	BUILD_BUG_ON(BTRFS_FT_UNKNOWN != FT_UNKNOWN);
	BUILD_BUG_ON(BTRFS_FT_REG_खाता != FT_REG_खाता);
	BUILD_BUG_ON(BTRFS_FT_सूची != FT_सूची);
	BUILD_BUG_ON(BTRFS_FT_CHRDEV != FT_CHRDEV);
	BUILD_BUG_ON(BTRFS_FT_BLKDEV != FT_BLKDEV);
	BUILD_BUG_ON(BTRFS_FT_FIFO != FT_FIFO);
	BUILD_BUG_ON(BTRFS_FT_SOCK != FT_SOCK);
	BUILD_BUG_ON(BTRFS_FT_SYMLINK != FT_SYMLINK);

	वापस fs_umode_to_ftype(inode->i_mode);
पूर्ण

काष्ठा inode *btrfs_lookup_dentry(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा inode *inode;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा btrfs_root *sub_root = root;
	काष्ठा btrfs_key location;
	u8 di_type = 0;
	पूर्णांक ret = 0;

	अगर (dentry->d_name.len > BTRFS_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	ret = btrfs_inode_by_name(dir, dentry, &location, &di_type);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	अगर (location.type == BTRFS_INODE_ITEM_KEY) अणु
		inode = btrfs_iget(dir->i_sb, location.objectid, root);
		अगर (IS_ERR(inode))
			वापस inode;

		/* Do extra check against inode mode with di_type */
		अगर (btrfs_inode_type(inode) != di_type) अणु
			btrfs_crit(fs_info,
"inode mode mismatch with dir: inode mode=0%o btrfs type=%u dir type=%u",
				  inode->i_mode, btrfs_inode_type(inode),
				  di_type);
			iput(inode);
			वापस ERR_PTR(-EUCLEAN);
		पूर्ण
		वापस inode;
	पूर्ण

	ret = fixup_tree_root_location(fs_info, dir, dentry,
				       &location, &sub_root);
	अगर (ret < 0) अणु
		अगर (ret != -ENOENT)
			inode = ERR_PTR(ret);
		अन्यथा
			inode = new_simple_dir(dir->i_sb, &location, sub_root);
	पूर्ण अन्यथा अणु
		inode = btrfs_iget(dir->i_sb, location.objectid, sub_root);
	पूर्ण
	अगर (root != sub_root)
		btrfs_put_root(sub_root);

	अगर (!IS_ERR(inode) && root != sub_root) अणु
		करोwn_पढ़ो(&fs_info->cleanup_work_sem);
		अगर (!sb_rकरोnly(inode->i_sb))
			ret = btrfs_orphan_cleanup(sub_root);
		up_पढ़ो(&fs_info->cleanup_work_sem);
		अगर (ret) अणु
			iput(inode);
			inode = ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस inode;
पूर्ण

अटल पूर्णांक btrfs_dentry_delete(स्थिर काष्ठा dentry *dentry)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा inode *inode = d_inode(dentry);

	अगर (!inode && !IS_ROOT(dentry))
		inode = d_inode(dentry->d_parent);

	अगर (inode) अणु
		root = BTRFS_I(inode)->root;
		अगर (btrfs_root_refs(&root->root_item) == 0)
			वापस 1;

		अगर (btrfs_ino(BTRFS_I(inode)) == BTRFS_EMPTY_SUBVOL_सूची_OBJECTID)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा dentry *btrfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = btrfs_lookup_dentry(dir, dentry);

	अगर (inode == ERR_PTR(-ENOENT))
		inode = शून्य;
	वापस d_splice_alias(inode, dentry);
पूर्ण

/*
 * All this infraकाष्ठाure exists because dir_emit can fault, and we are holding
 * the tree lock when करोing सूची_पढ़ो.  For now just allocate a buffer and copy
 * our inक्रमmation पूर्णांकo that, and then dir_emit from the buffer.  This is
 * similar to what NFS करोes, only we करोn't keep the buffer around in pagecache
 * because I'm afraid I'll mess that up.  Long term we need to make filldir करो
 * copy_to_user_inatomic so we करोn't have to worry about page faulting under the
 * tree lock.
 */
अटल पूर्णांक btrfs_सूची_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा btrfs_file_निजी *निजी;

	निजी = kzalloc(माप(काष्ठा btrfs_file_निजी), GFP_KERNEL);
	अगर (!निजी)
		वापस -ENOMEM;
	निजी->filldir_buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!निजी->filldir_buf) अणु
		kमुक्त(निजी);
		वापस -ENOMEM;
	पूर्ण
	file->निजी_data = निजी;
	वापस 0;
पूर्ण

काष्ठा dir_entry अणु
	u64 ino;
	u64 offset;
	अचिन्हित type;
	पूर्णांक name_len;
पूर्ण;

अटल पूर्णांक btrfs_filldir(व्योम *addr, पूर्णांक entries, काष्ठा dir_context *ctx)
अणु
	जबतक (entries--) अणु
		काष्ठा dir_entry *entry = addr;
		अक्षर *name = (अक्षर *)(entry + 1);

		ctx->pos = get_unaligned(&entry->offset);
		अगर (!dir_emit(ctx, name, get_unaligned(&entry->name_len),
					 get_unaligned(&entry->ino),
					 get_unaligned(&entry->type)))
			वापस 1;
		addr += माप(काष्ठा dir_entry) +
			get_unaligned(&entry->name_len);
		ctx->pos++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_real_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_file_निजी *निजी = file->निजी_data;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_path *path;
	व्योम *addr;
	काष्ठा list_head ins_list;
	काष्ठा list_head del_list;
	पूर्णांक ret;
	काष्ठा extent_buffer *leaf;
	पूर्णांक slot;
	अक्षर *name_ptr;
	पूर्णांक name_len;
	पूर्णांक entries = 0;
	पूर्णांक total_len = 0;
	bool put = false;
	काष्ठा btrfs_key location;

	अगर (!dir_emit_करोts(file, ctx))
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	addr = निजी->filldir_buf;
	path->पढ़ोa = READA_FORWARD;

	INIT_LIST_HEAD(&ins_list);
	INIT_LIST_HEAD(&del_list);
	put = btrfs_सूची_पढ़ो_get_delayed_items(inode, &ins_list, &del_list);

again:
	key.type = BTRFS_सूची_INDEX_KEY;
	key.offset = ctx->pos;
	key.objectid = btrfs_ino(BTRFS_I(inode));

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ err;

	जबतक (1) अणु
		काष्ठा dir_entry *entry;

		leaf = path->nodes[0];
		slot = path->slots[0];
		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ err;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &found_key, slot);

		अगर (found_key.objectid != key.objectid)
			अवरोध;
		अगर (found_key.type != BTRFS_सूची_INDEX_KEY)
			अवरोध;
		अगर (found_key.offset < ctx->pos)
			जाओ next;
		अगर (btrfs_should_delete_dir_index(&del_list, found_key.offset))
			जाओ next;
		di = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_dir_item);
		name_len = btrfs_dir_name_len(leaf, di);
		अगर ((total_len + माप(काष्ठा dir_entry) + name_len) >=
		    PAGE_SIZE) अणु
			btrfs_release_path(path);
			ret = btrfs_filldir(निजी->filldir_buf, entries, ctx);
			अगर (ret)
				जाओ nopos;
			addr = निजी->filldir_buf;
			entries = 0;
			total_len = 0;
			जाओ again;
		पूर्ण

		entry = addr;
		put_unaligned(name_len, &entry->name_len);
		name_ptr = (अक्षर *)(entry + 1);
		पढ़ो_extent_buffer(leaf, name_ptr, (अचिन्हित दीर्घ)(di + 1),
				   name_len);
		put_unaligned(fs_ftype_to_dtype(btrfs_dir_type(leaf, di)),
				&entry->type);
		btrfs_dir_item_key_to_cpu(leaf, di, &location);
		put_unaligned(location.objectid, &entry->ino);
		put_unaligned(found_key.offset, &entry->offset);
		entries++;
		addr += माप(काष्ठा dir_entry) + name_len;
		total_len += माप(काष्ठा dir_entry) + name_len;
next:
		path->slots[0]++;
	पूर्ण
	btrfs_release_path(path);

	ret = btrfs_filldir(निजी->filldir_buf, entries, ctx);
	अगर (ret)
		जाओ nopos;

	ret = btrfs_सूची_पढ़ो_delayed_dir_index(ctx, &ins_list);
	अगर (ret)
		जाओ nopos;

	/*
	 * Stop new entries from being वापसed after we वापस the last
	 * entry.
	 *
	 * New directory entries are asचिन्हित a strictly increasing
	 * offset.  This means that new entries created during सूची_पढ़ो
	 * are *guaranteed* to be seen in the future by that सूची_पढ़ो.
	 * This has broken buggy programs which operate on names as
	 * they're वापसed by सूची_पढ़ो.  Until we re-use मुक्तd offsets
	 * we have this hack to stop new entries from being वापसed
	 * under the assumption that they'll never reach this huge
	 * offset.
	 *
	 * This is being careful not to overflow 32bit loff_t unless the
	 * last entry requires it because करोing so has broken 32bit apps
	 * in the past.
	 */
	अगर (ctx->pos >= पूर्णांक_उच्च)
		ctx->pos = Lदीर्घ_उच्च;
	अन्यथा
		ctx->pos = पूर्णांक_उच्च;
nopos:
	ret = 0;
err:
	अगर (put)
		btrfs_सूची_पढ़ो_put_delayed_items(inode, &ins_list, &del_list);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * This is somewhat expensive, updating the tree every समय the
 * inode changes.  But, it is most likely to find the inode in cache.
 * FIXME, needs more benchmarking...there are no reasons other than perक्रमmance
 * to keep or drop this code.
 */
अटल पूर्णांक btrfs_dirty_inode(काष्ठा inode *inode)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;

	अगर (test_bit(BTRFS_INODE_DUMMY, &BTRFS_I(inode)->runसमय_flags))
		वापस 0;

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
	अगर (ret && (ret == -ENOSPC || ret == -EDQUOT)) अणु
		/* whoops, lets try again with the full transaction */
		btrfs_end_transaction(trans);
		trans = btrfs_start_transaction(root, 1);
		अगर (IS_ERR(trans))
			वापस PTR_ERR(trans);

		ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
	पूर्ण
	btrfs_end_transaction(trans);
	अगर (BTRFS_I(inode)->delayed_node)
		btrfs_balance_delayed_items(fs_info);

	वापस ret;
पूर्ण

/*
 * This is a copy of file_update_समय.  We need this so we can वापस error on
 * ENOSPC क्रम updating the inode in the हाल of file ग_लिखो and mmap ग_लिखोs.
 */
अटल पूर्णांक btrfs_update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *now,
			     पूर्णांक flags)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	bool dirty = flags & ~S_VERSION;

	अगर (btrfs_root_पढ़ोonly(root))
		वापस -EROFS;

	अगर (flags & S_VERSION)
		dirty |= inode_maybe_inc_iversion(inode, dirty);
	अगर (flags & S_CTIME)
		inode->i_स_समय = *now;
	अगर (flags & S_MTIME)
		inode->i_mसमय = *now;
	अगर (flags & S_ATIME)
		inode->i_aसमय = *now;
	वापस dirty ? btrfs_dirty_inode(inode) : 0;
पूर्ण

/*
 * find the highest existing sequence number in a directory
 * and then set the in-memory index_cnt variable to reflect
 * मुक्त sequence numbers
 */
अटल पूर्णांक btrfs_set_inode_index_count(काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_key key, found_key;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	पूर्णांक ret;

	key.objectid = btrfs_ino(inode);
	key.type = BTRFS_सूची_INDEX_KEY;
	key.offset = (u64)-1;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	/* FIXME: we should be able to handle this */
	अगर (ret == 0)
		जाओ out;
	ret = 0;

	/*
	 * MAGIC NUMBER EXPLANATION:
	 * since we search a directory based on f_pos we have to start at 2
	 * since '.' and '..' have f_pos of 0 and 1 respectively, so everybody
	 * अन्यथा has to start at 2
	 */
	अगर (path->slots[0] == 0) अणु
		inode->index_cnt = 2;
		जाओ out;
	पूर्ण

	path->slots[0]--;

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);

	अगर (found_key.objectid != btrfs_ino(inode) ||
	    found_key.type != BTRFS_सूची_INDEX_KEY) अणु
		inode->index_cnt = 2;
		जाओ out;
	पूर्ण

	inode->index_cnt = found_key.offset + 1;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * helper to find a मुक्त sequence number in a given directory.  This current
 * code is very simple, later versions will करो smarter things in the btree
 */
पूर्णांक btrfs_set_inode_index(काष्ठा btrfs_inode *dir, u64 *index)
अणु
	पूर्णांक ret = 0;

	अगर (dir->index_cnt == (u64)-1) अणु
		ret = btrfs_inode_delayed_dir_index_count(dir);
		अगर (ret) अणु
			ret = btrfs_set_inode_index_count(dir);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	*index = dir->index_cnt;
	dir->index_cnt++;

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_insert_inode_locked(काष्ठा inode *inode)
अणु
	काष्ठा btrfs_iget_args args;

	args.ino = BTRFS_I(inode)->location.objectid;
	args.root = BTRFS_I(inode)->root;

	वापस insert_inode_locked4(inode,
		   btrfs_inode_hash(inode->i_ino, BTRFS_I(inode)->root),
		   btrfs_find_actor, &args);
पूर्ण

/*
 * Inherit flags from the parent inode.
 *
 * Currently only the compression flags and the cow flags are inherited.
 */
अटल व्योम btrfs_inherit_अगरlags(काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	अचिन्हित पूर्णांक flags;

	अगर (!dir)
		वापस;

	flags = BTRFS_I(dir)->flags;

	अगर (flags & BTRFS_INODE_NOCOMPRESS) अणु
		BTRFS_I(inode)->flags &= ~BTRFS_INODE_COMPRESS;
		BTRFS_I(inode)->flags |= BTRFS_INODE_NOCOMPRESS;
	पूर्ण अन्यथा अगर (flags & BTRFS_INODE_COMPRESS) अणु
		BTRFS_I(inode)->flags &= ~BTRFS_INODE_NOCOMPRESS;
		BTRFS_I(inode)->flags |= BTRFS_INODE_COMPRESS;
	पूर्ण

	अगर (flags & BTRFS_INODE_NODATACOW) अणु
		BTRFS_I(inode)->flags |= BTRFS_INODE_NODATACOW;
		अगर (S_ISREG(inode->i_mode))
			BTRFS_I(inode)->flags |= BTRFS_INODE_NODATASUM;
	पूर्ण

	btrfs_sync_inode_flags_to_i_flags(inode);
पूर्ण

अटल काष्ठा inode *btrfs_new_inode(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_root *root,
				     काष्ठा inode *dir,
				     स्थिर अक्षर *name, पूर्णांक name_len,
				     u64 ref_objectid, u64 objectid,
				     umode_t mode, u64 *index)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा inode *inode;
	काष्ठा btrfs_inode_item *inode_item;
	काष्ठा btrfs_key *location;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_inode_ref *ref;
	काष्ठा btrfs_key key[2];
	u32 sizes[2];
	पूर्णांक nitems = name ? 2 : 1;
	अचिन्हित दीर्घ ptr;
	अचिन्हित पूर्णांक nofs_flag;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस ERR_PTR(-ENOMEM);

	nofs_flag = meदो_स्मृति_nofs_save();
	inode = new_inode(fs_info->sb);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (!inode) अणु
		btrfs_मुक्त_path(path);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/*
	 * O_TMPखाता, set link count to 0, so that after this poपूर्णांक,
	 * we fill in an inode item with the correct link count.
	 */
	अगर (!name)
		set_nlink(inode, 0);

	/*
	 * we have to initialize this early, so we can reclaim the inode
	 * number अगर we fail afterwards in this function.
	 */
	inode->i_ino = objectid;

	अगर (dir && name) अणु
		trace_btrfs_inode_request(dir);

		ret = btrfs_set_inode_index(BTRFS_I(dir), index);
		अगर (ret) अणु
			btrfs_मुक्त_path(path);
			iput(inode);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण अन्यथा अगर (dir) अणु
		*index = 0;
	पूर्ण
	/*
	 * index_cnt is ignored क्रम everything but a dir,
	 * btrfs_set_inode_index_count has an explanation क्रम the magic
	 * number
	 */
	BTRFS_I(inode)->index_cnt = 2;
	BTRFS_I(inode)->dir_index = *index;
	BTRFS_I(inode)->root = btrfs_grab_root(root);
	BTRFS_I(inode)->generation = trans->transid;
	inode->i_generation = BTRFS_I(inode)->generation;

	/*
	 * We could have gotten an inode number from somebody who was fsynced
	 * and then हटाओd in this same transaction, so let's just set full
	 * sync since it will be a full sync anyway and this will blow away the
	 * old info in the log.
	 */
	set_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &BTRFS_I(inode)->runसमय_flags);

	key[0].objectid = objectid;
	key[0].type = BTRFS_INODE_ITEM_KEY;
	key[0].offset = 0;

	sizes[0] = माप(काष्ठा btrfs_inode_item);

	अगर (name) अणु
		/*
		 * Start new inodes with an inode_ref. This is slightly more
		 * efficient क्रम small numbers of hard links since they will
		 * be packed पूर्णांकo one item. Extended refs will kick in अगर we
		 * add more hard links than can fit in the ref item.
		 */
		key[1].objectid = objectid;
		key[1].type = BTRFS_INODE_REF_KEY;
		key[1].offset = ref_objectid;

		sizes[1] = name_len + माप(*ref);
	पूर्ण

	location = &BTRFS_I(inode)->location;
	location->objectid = objectid;
	location->offset = 0;
	location->type = BTRFS_INODE_ITEM_KEY;

	ret = btrfs_insert_inode_locked(inode);
	अगर (ret < 0) अणु
		iput(inode);
		जाओ fail;
	पूर्ण

	ret = btrfs_insert_empty_items(trans, root, path, key, sizes, nitems);
	अगर (ret != 0)
		जाओ fail_unlock;

	inode_init_owner(&init_user_ns, inode, dir, mode);
	inode_set_bytes(inode, 0);

	inode->i_mसमय = current_समय(inode);
	inode->i_aसमय = inode->i_mसमय;
	inode->i_स_समय = inode->i_mसमय;
	BTRFS_I(inode)->i_oसमय = inode->i_mसमय;

	inode_item = btrfs_item_ptr(path->nodes[0], path->slots[0],
				  काष्ठा btrfs_inode_item);
	memzero_extent_buffer(path->nodes[0], (अचिन्हित दीर्घ)inode_item,
			     माप(*inode_item));
	fill_inode_item(trans, path->nodes[0], inode_item, inode);

	अगर (name) अणु
		ref = btrfs_item_ptr(path->nodes[0], path->slots[0] + 1,
				     काष्ठा btrfs_inode_ref);
		btrfs_set_inode_ref_name_len(path->nodes[0], ref, name_len);
		btrfs_set_inode_ref_index(path->nodes[0], ref, *index);
		ptr = (अचिन्हित दीर्घ)(ref + 1);
		ग_लिखो_extent_buffer(path->nodes[0], name, ptr, name_len);
	पूर्ण

	btrfs_mark_buffer_dirty(path->nodes[0]);
	btrfs_मुक्त_path(path);

	btrfs_inherit_अगरlags(inode, dir);

	अगर (S_ISREG(mode)) अणु
		अगर (btrfs_test_opt(fs_info, NODATASUM))
			BTRFS_I(inode)->flags |= BTRFS_INODE_NODATASUM;
		अगर (btrfs_test_opt(fs_info, NODATACOW))
			BTRFS_I(inode)->flags |= BTRFS_INODE_NODATACOW |
				BTRFS_INODE_NODATASUM;
	पूर्ण

	inode_tree_add(inode);

	trace_btrfs_inode_new(inode);
	btrfs_set_inode_last_trans(trans, BTRFS_I(inode));

	btrfs_update_root_बार(trans, root);

	ret = btrfs_inode_inherit_props(trans, inode, dir);
	अगर (ret)
		btrfs_err(fs_info,
			  "error inheriting props for ino %llu (root %llu): %d",
			btrfs_ino(BTRFS_I(inode)), root->root_key.objectid, ret);

	वापस inode;

fail_unlock:
	discard_new_inode(inode);
fail:
	अगर (dir && name)
		BTRFS_I(dir)->index_cnt--;
	btrfs_मुक्त_path(path);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * utility function to add 'inode' into 'parent_inode' with
 * a give name and a given sequence number.
 * अगर 'add_backref' is true, also insert a backref from the
 * inode to the parent directory.
 */
पूर्णांक btrfs_add_link(काष्ठा btrfs_trans_handle *trans,
		   काष्ठा btrfs_inode *parent_inode, काष्ठा btrfs_inode *inode,
		   स्थिर अक्षर *name, पूर्णांक name_len, पूर्णांक add_backref, u64 index)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root *root = parent_inode->root;
	u64 ino = btrfs_ino(inode);
	u64 parent_ino = btrfs_ino(parent_inode);

	अगर (unlikely(ino == BTRFS_FIRST_FREE_OBJECTID)) अणु
		स_नकल(&key, &inode->root->root_key, माप(key));
	पूर्ण अन्यथा अणु
		key.objectid = ino;
		key.type = BTRFS_INODE_ITEM_KEY;
		key.offset = 0;
	पूर्ण

	अगर (unlikely(ino == BTRFS_FIRST_FREE_OBJECTID)) अणु
		ret = btrfs_add_root_ref(trans, key.objectid,
					 root->root_key.objectid, parent_ino,
					 index, name, name_len);
	पूर्ण अन्यथा अगर (add_backref) अणु
		ret = btrfs_insert_inode_ref(trans, root, name, name_len, ino,
					     parent_ino, index);
	पूर्ण

	/* Nothing to clean up yet */
	अगर (ret)
		वापस ret;

	ret = btrfs_insert_dir_item(trans, name, name_len, parent_inode, &key,
				    btrfs_inode_type(&inode->vfs_inode), index);
	अगर (ret == -EEXIST || ret == -EOVERFLOW)
		जाओ fail_dir_item;
	अन्यथा अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण

	btrfs_i_size_ग_लिखो(parent_inode, parent_inode->vfs_inode.i_size +
			   name_len * 2);
	inode_inc_iversion(&parent_inode->vfs_inode);
	/*
	 * If we are replaying a log tree, we करो not want to update the mसमय
	 * and स_समय of the parent directory with the current समय, since the
	 * log replay procedure is responsible क्रम setting them to their correct
	 * values (the ones it had when the fsync was करोne).
	 */
	अगर (!test_bit(BTRFS_FS_LOG_RECOVERING, &root->fs_info->flags)) अणु
		काष्ठा बारpec64 now = current_समय(&parent_inode->vfs_inode);

		parent_inode->vfs_inode.i_mसमय = now;
		parent_inode->vfs_inode.i_स_समय = now;
	पूर्ण
	ret = btrfs_update_inode(trans, root, parent_inode);
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
	वापस ret;

fail_dir_item:
	अगर (unlikely(ino == BTRFS_FIRST_FREE_OBJECTID)) अणु
		u64 local_index;
		पूर्णांक err;
		err = btrfs_del_root_ref(trans, key.objectid,
					 root->root_key.objectid, parent_ino,
					 &local_index, name, name_len);
		अगर (err)
			btrfs_पात_transaction(trans, err);
	पूर्ण अन्यथा अगर (add_backref) अणु
		u64 local_index;
		पूर्णांक err;

		err = btrfs_del_inode_ref(trans, root, name, name_len,
					  ino, parent_ino, &local_index);
		अगर (err)
			btrfs_पात_transaction(trans, err);
	पूर्ण

	/* Return the original error code */
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_add_nondir(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_inode *dir, काष्ठा dentry *dentry,
			    काष्ठा btrfs_inode *inode, पूर्णांक backref, u64 index)
अणु
	पूर्णांक err = btrfs_add_link(trans, dir, inode,
				 dentry->d_name.name, dentry->d_name.len,
				 backref, index);
	अगर (err > 0)
		err = -EEXIST;
	वापस err;
पूर्ण

अटल पूर्णांक btrfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा inode *inode = शून्य;
	पूर्णांक err;
	u64 objectid;
	u64 index = 0;

	/*
	 * 2 क्रम inode item and ref
	 * 2 क्रम dir items
	 * 1 क्रम xattr अगर selinux is on
	 */
	trans = btrfs_start_transaction(root, 5);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	err = btrfs_get_मुक्त_objectid(root, &objectid);
	अगर (err)
		जाओ out_unlock;

	inode = btrfs_new_inode(trans, root, dir, dentry->d_name.name,
			dentry->d_name.len, btrfs_ino(BTRFS_I(dir)), objectid,
			mode, &index);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		inode = शून्य;
		जाओ out_unlock;
	पूर्ण

	/*
	* If the active LSM wants to access the inode during
	* d_instantiate it needs these. Smack checks to see
	* अगर the fileप्रणाली supports xattrs by looking at the
	* ops vector.
	*/
	inode->i_op = &btrfs_special_inode_operations;
	init_special_inode(inode, inode->i_mode, rdev);

	err = btrfs_init_inode_security(trans, inode, dir, &dentry->d_name);
	अगर (err)
		जाओ out_unlock;

	err = btrfs_add_nondir(trans, BTRFS_I(dir), dentry, BTRFS_I(inode),
			0, index);
	अगर (err)
		जाओ out_unlock;

	btrfs_update_inode(trans, root, BTRFS_I(inode));
	d_instantiate_new(dentry, inode);

out_unlock:
	btrfs_end_transaction(trans);
	btrfs_btree_balance_dirty(fs_info);
	अगर (err && inode) अणु
		inode_dec_link_count(inode);
		discard_new_inode(inode);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक btrfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा inode *inode = शून्य;
	पूर्णांक err;
	u64 objectid;
	u64 index = 0;

	/*
	 * 2 क्रम inode item and ref
	 * 2 क्रम dir items
	 * 1 क्रम xattr अगर selinux is on
	 */
	trans = btrfs_start_transaction(root, 5);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	err = btrfs_get_मुक्त_objectid(root, &objectid);
	अगर (err)
		जाओ out_unlock;

	inode = btrfs_new_inode(trans, root, dir, dentry->d_name.name,
			dentry->d_name.len, btrfs_ino(BTRFS_I(dir)), objectid,
			mode, &index);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		inode = शून्य;
		जाओ out_unlock;
	पूर्ण
	/*
	* If the active LSM wants to access the inode during
	* d_instantiate it needs these. Smack checks to see
	* अगर the fileप्रणाली supports xattrs by looking at the
	* ops vector.
	*/
	inode->i_fop = &btrfs_file_operations;
	inode->i_op = &btrfs_file_inode_operations;
	inode->i_mapping->a_ops = &btrfs_aops;

	err = btrfs_init_inode_security(trans, inode, dir, &dentry->d_name);
	अगर (err)
		जाओ out_unlock;

	err = btrfs_update_inode(trans, root, BTRFS_I(inode));
	अगर (err)
		जाओ out_unlock;

	err = btrfs_add_nondir(trans, BTRFS_I(dir), dentry, BTRFS_I(inode),
			0, index);
	अगर (err)
		जाओ out_unlock;

	d_instantiate_new(dentry, inode);

out_unlock:
	btrfs_end_transaction(trans);
	अगर (err && inode) अणु
		inode_dec_link_count(inode);
		discard_new_inode(inode);
	पूर्ण
	btrfs_btree_balance_dirty(fs_info);
	वापस err;
पूर्ण

अटल पूर्णांक btrfs_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
		      काष्ठा dentry *dentry)
अणु
	काष्ठा btrfs_trans_handle *trans = शून्य;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा inode *inode = d_inode(old_dentry);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	u64 index;
	पूर्णांक err;
	पूर्णांक drop_inode = 0;

	/* करो not allow sys_link's with other subvols of the same device */
	अगर (root->root_key.objectid != BTRFS_I(inode)->root->root_key.objectid)
		वापस -EXDEV;

	अगर (inode->i_nlink >= BTRFS_LINK_MAX)
		वापस -EMLINK;

	err = btrfs_set_inode_index(BTRFS_I(dir), &index);
	अगर (err)
		जाओ fail;

	/*
	 * 2 items क्रम inode and inode ref
	 * 2 items क्रम dir items
	 * 1 item क्रम parent inode
	 * 1 item क्रम orphan item deletion अगर O_TMPखाता
	 */
	trans = btrfs_start_transaction(root, inode->i_nlink ? 5 : 6);
	अगर (IS_ERR(trans)) अणु
		err = PTR_ERR(trans);
		trans = शून्य;
		जाओ fail;
	पूर्ण

	/* There are several dir indexes क्रम this inode, clear the cache. */
	BTRFS_I(inode)->dir_index = 0ULL;
	inc_nlink(inode);
	inode_inc_iversion(inode);
	inode->i_स_समय = current_समय(inode);
	ihold(inode);
	set_bit(BTRFS_INODE_COPY_EVERYTHING, &BTRFS_I(inode)->runसमय_flags);

	err = btrfs_add_nondir(trans, BTRFS_I(dir), dentry, BTRFS_I(inode),
			1, index);

	अगर (err) अणु
		drop_inode = 1;
	पूर्ण अन्यथा अणु
		काष्ठा dentry *parent = dentry->d_parent;

		err = btrfs_update_inode(trans, root, BTRFS_I(inode));
		अगर (err)
			जाओ fail;
		अगर (inode->i_nlink == 1) अणु
			/*
			 * If new hard link count is 1, it's a file created
			 * with खोलो(2) O_TMPखाता flag.
			 */
			err = btrfs_orphan_del(trans, BTRFS_I(inode));
			अगर (err)
				जाओ fail;
		पूर्ण
		d_instantiate(dentry, inode);
		btrfs_log_new_name(trans, BTRFS_I(inode), शून्य, parent);
	पूर्ण

fail:
	अगर (trans)
		btrfs_end_transaction(trans);
	अगर (drop_inode) अणु
		inode_dec_link_count(inode);
		iput(inode);
	पूर्ण
	btrfs_btree_balance_dirty(fs_info);
	वापस err;
पूर्ण

अटल पूर्णांक btrfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा inode *inode = शून्य;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	पूर्णांक err = 0;
	u64 objectid = 0;
	u64 index = 0;

	/*
	 * 2 items क्रम inode and ref
	 * 2 items क्रम dir items
	 * 1 क्रम xattr अगर selinux is on
	 */
	trans = btrfs_start_transaction(root, 5);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	err = btrfs_get_मुक्त_objectid(root, &objectid);
	अगर (err)
		जाओ out_fail;

	inode = btrfs_new_inode(trans, root, dir, dentry->d_name.name,
			dentry->d_name.len, btrfs_ino(BTRFS_I(dir)), objectid,
			S_IFसूची | mode, &index);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		inode = शून्य;
		जाओ out_fail;
	पूर्ण

	/* these must be set beक्रमe we unlock the inode */
	inode->i_op = &btrfs_dir_inode_operations;
	inode->i_fop = &btrfs_dir_file_operations;

	err = btrfs_init_inode_security(trans, inode, dir, &dentry->d_name);
	अगर (err)
		जाओ out_fail;

	btrfs_i_size_ग_लिखो(BTRFS_I(inode), 0);
	err = btrfs_update_inode(trans, root, BTRFS_I(inode));
	अगर (err)
		जाओ out_fail;

	err = btrfs_add_link(trans, BTRFS_I(dir), BTRFS_I(inode),
			dentry->d_name.name,
			dentry->d_name.len, 0, index);
	अगर (err)
		जाओ out_fail;

	d_instantiate_new(dentry, inode);

out_fail:
	btrfs_end_transaction(trans);
	अगर (err && inode) अणु
		inode_dec_link_count(inode);
		discard_new_inode(inode);
	पूर्ण
	btrfs_btree_balance_dirty(fs_info);
	वापस err;
पूर्ण

अटल noअंतरभूत पूर्णांक uncompress_अंतरभूत(काष्ठा btrfs_path *path,
				      काष्ठा page *page,
				      माप_प्रकार pg_offset, u64 extent_offset,
				      काष्ठा btrfs_file_extent_item *item)
अणु
	पूर्णांक ret;
	काष्ठा extent_buffer *leaf = path->nodes[0];
	अक्षर *पंचांगp;
	माप_प्रकार max_size;
	अचिन्हित दीर्घ अंतरभूत_size;
	अचिन्हित दीर्घ ptr;
	पूर्णांक compress_type;

	WARN_ON(pg_offset != 0);
	compress_type = btrfs_file_extent_compression(leaf, item);
	max_size = btrfs_file_extent_ram_bytes(leaf, item);
	अंतरभूत_size = btrfs_file_extent_अंतरभूत_item_len(leaf,
					btrfs_item_nr(path->slots[0]));
	पंचांगp = kदो_स्मृति(अंतरभूत_size, GFP_NOFS);
	अगर (!पंचांगp)
		वापस -ENOMEM;
	ptr = btrfs_file_extent_अंतरभूत_start(item);

	पढ़ो_extent_buffer(leaf, पंचांगp, ptr, अंतरभूत_size);

	max_size = min_t(अचिन्हित दीर्घ, PAGE_SIZE, max_size);
	ret = btrfs_decompress(compress_type, पंचांगp, page,
			       extent_offset, अंतरभूत_size, max_size);

	/*
	 * decompression code contains a स_रखो to fill in any space between the end
	 * of the uncompressed data and the end of max_size in हाल the decompressed
	 * data ends up लघुer than ram_bytes.  That करोesn't cover the hole between
	 * the end of an अंतरभूत extent and the beginning of the next block, so we
	 * cover that region here.
	 */

	अगर (max_size + pg_offset < PAGE_SIZE)
		memzero_page(page,  pg_offset + max_size,
			     PAGE_SIZE - max_size - pg_offset);
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

/**
 * btrfs_get_extent - Lookup the first extent overlapping a range in a file.
 * @inode:	file to search in
 * @page:	page to पढ़ो extent data पूर्णांकo अगर the extent is अंतरभूत
 * @pg_offset:	offset पूर्णांकo @page to copy to
 * @start:	file offset
 * @len:	length of range starting at @start
 *
 * This वापसs the first &काष्ठा extent_map which overlaps with the given
 * range, पढ़ोing it from the B-tree and caching it अगर necessary. Note that
 * there may be more extents which overlap the given range after the वापसed
 * extent_map.
 *
 * If @page is not शून्य and the extent is अंतरभूत, this also पढ़ोs the extent
 * data directly पूर्णांकo the page and marks the extent up to date in the io_tree.
 *
 * Return: ERR_PTR on error, non-शून्य extent_map on success.
 */
काष्ठा extent_map *btrfs_get_extent(काष्ठा btrfs_inode *inode,
				    काष्ठा page *page, माप_प्रकार pg_offset,
				    u64 start, u64 len)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	पूर्णांक ret = 0;
	u64 extent_start = 0;
	u64 extent_end = 0;
	u64 objectid = btrfs_ino(inode);
	पूर्णांक extent_type = -1;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_file_extent_item *item;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key found_key;
	काष्ठा extent_map *em = शून्य;
	काष्ठा extent_map_tree *em_tree = &inode->extent_tree;
	काष्ठा extent_io_tree *io_tree = &inode->io_tree;

	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, start, len);
	पढ़ो_unlock(&em_tree->lock);

	अगर (em) अणु
		अगर (em->start > start || em->start + em->len <= start)
			मुक्त_extent_map(em);
		अन्यथा अगर (em->block_start == EXTENT_MAP_INLINE && page)
			मुक्त_extent_map(em);
		अन्यथा
			जाओ out;
	पूर्ण
	em = alloc_extent_map();
	अगर (!em) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	em->start = EXTENT_MAP_HOLE;
	em->orig_start = EXTENT_MAP_HOLE;
	em->len = (u64)-1;
	em->block_len = (u64)-1;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Chances are we'll be called again, so go ahead and करो पढ़ोahead */
	path->पढ़ोa = READA_FORWARD;

	/*
	 * The same explanation in load_मुक्त_space_cache applies here as well,
	 * we only पढ़ो when we're loading the मुक्त space cache, and at that
	 * poपूर्णांक the commit_root has everything we need.
	 */
	अगर (btrfs_is_मुक्त_space_inode(inode)) अणु
		path->search_commit_root = 1;
		path->skip_locking = 1;
	पूर्ण

	ret = btrfs_lookup_file_extent(शून्य, root, path, objectid, start, 0);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		अगर (path->slots[0] == 0)
			जाओ not_found;
		path->slots[0]--;
		ret = 0;
	पूर्ण

	leaf = path->nodes[0];
	item = btrfs_item_ptr(leaf, path->slots[0],
			      काष्ठा btrfs_file_extent_item);
	btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
	अगर (found_key.objectid != objectid ||
	    found_key.type != BTRFS_EXTENT_DATA_KEY) अणु
		/*
		 * If we backup past the first extent we want to move क्रमward
		 * and see अगर there is an extent in front of us, otherwise we'll
		 * say there is a hole क्रम our whole search range which can
		 * cause problems.
		 */
		extent_end = start;
		जाओ next;
	पूर्ण

	extent_type = btrfs_file_extent_type(leaf, item);
	extent_start = found_key.offset;
	extent_end = btrfs_file_extent_end(path);
	अगर (extent_type == BTRFS_खाता_EXTENT_REG ||
	    extent_type == BTRFS_खाता_EXTENT_PREALLOC) अणु
		/* Only regular file could have regular/pपुनः_स्मृति extent */
		अगर (!S_ISREG(inode->vfs_inode.i_mode)) अणु
			ret = -EUCLEAN;
			btrfs_crit(fs_info,
		"regular/prealloc extent found for non-regular inode %llu",
				   btrfs_ino(inode));
			जाओ out;
		पूर्ण
		trace_btrfs_get_extent_show_fi_regular(inode, leaf, item,
						       extent_start);
	पूर्ण अन्यथा अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
		trace_btrfs_get_extent_show_fi_अंतरभूत(inode, leaf, item,
						      path->slots[0],
						      extent_start);
	पूर्ण
next:
	अगर (start >= extent_end) अणु
		path->slots[0]++;
		अगर (path->slots[0] >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0)
				जाओ not_found;

			leaf = path->nodes[0];
		पूर्ण
		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
		अगर (found_key.objectid != objectid ||
		    found_key.type != BTRFS_EXTENT_DATA_KEY)
			जाओ not_found;
		अगर (start + len <= found_key.offset)
			जाओ not_found;
		अगर (start > found_key.offset)
			जाओ next;

		/* New extent overlaps with existing one */
		em->start = start;
		em->orig_start = start;
		em->len = found_key.offset - start;
		em->block_start = EXTENT_MAP_HOLE;
		जाओ insert;
	पूर्ण

	btrfs_extent_item_to_extent_map(inode, path, item, !page, em);

	अगर (extent_type == BTRFS_खाता_EXTENT_REG ||
	    extent_type == BTRFS_खाता_EXTENT_PREALLOC) अणु
		जाओ insert;
	पूर्ण अन्यथा अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
		अचिन्हित दीर्घ ptr;
		अक्षर *map;
		माप_प्रकार size;
		माप_प्रकार extent_offset;
		माप_प्रकार copy_size;

		अगर (!page)
			जाओ out;

		size = btrfs_file_extent_ram_bytes(leaf, item);
		extent_offset = page_offset(page) + pg_offset - extent_start;
		copy_size = min_t(u64, PAGE_SIZE - pg_offset,
				  size - extent_offset);
		em->start = extent_start + extent_offset;
		em->len = ALIGN(copy_size, fs_info->sectorsize);
		em->orig_block_len = em->len;
		em->orig_start = em->start;
		ptr = btrfs_file_extent_अंतरभूत_start(item) + extent_offset;

		अगर (!PageUptodate(page)) अणु
			अगर (btrfs_file_extent_compression(leaf, item) !=
			    BTRFS_COMPRESS_NONE) अणु
				ret = uncompress_अंतरभूत(path, page, pg_offset,
							extent_offset, item);
				अगर (ret)
					जाओ out;
			पूर्ण अन्यथा अणु
				map = kmap_local_page(page);
				पढ़ो_extent_buffer(leaf, map + pg_offset, ptr,
						   copy_size);
				अगर (pg_offset + copy_size < PAGE_SIZE) अणु
					स_रखो(map + pg_offset + copy_size, 0,
					       PAGE_SIZE - pg_offset -
					       copy_size);
				पूर्ण
				kunmap_local(map);
			पूर्ण
			flush_dcache_page(page);
		पूर्ण
		set_extent_uptodate(io_tree, em->start,
				    extent_map_end(em) - 1, शून्य, GFP_NOFS);
		जाओ insert;
	पूर्ण
not_found:
	em->start = start;
	em->orig_start = start;
	em->len = len;
	em->block_start = EXTENT_MAP_HOLE;
insert:
	ret = 0;
	btrfs_release_path(path);
	अगर (em->start > start || extent_map_end(em) <= start) अणु
		btrfs_err(fs_info,
			  "bad extent! em: [%llu %llu] passed [%llu %llu]",
			  em->start, em->len, start, len);
		ret = -EIO;
		जाओ out;
	पूर्ण

	ग_लिखो_lock(&em_tree->lock);
	ret = btrfs_add_extent_mapping(fs_info, em_tree, &em, start, len);
	ग_लिखो_unlock(&em_tree->lock);
out:
	btrfs_मुक्त_path(path);

	trace_btrfs_get_extent(root, inode, em);

	अगर (ret) अणु
		मुक्त_extent_map(em);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस em;
पूर्ण

काष्ठा extent_map *btrfs_get_extent_fiemap(काष्ठा btrfs_inode *inode,
					   u64 start, u64 len)
अणु
	काष्ठा extent_map *em;
	काष्ठा extent_map *hole_em = शून्य;
	u64 delalloc_start = start;
	u64 end;
	u64 delalloc_len;
	u64 delalloc_end;
	पूर्णांक err = 0;

	em = btrfs_get_extent(inode, शून्य, 0, start, len);
	अगर (IS_ERR(em))
		वापस em;
	/*
	 * If our em maps to:
	 * - a hole or
	 * - a pre-alloc extent,
	 * there might actually be delalloc bytes behind it.
	 */
	अगर (em->block_start != EXTENT_MAP_HOLE &&
	    !test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
		वापस em;
	अन्यथा
		hole_em = em;

	/* check to see अगर we've wrapped (len == -1 or similar) */
	end = start + len;
	अगर (end < start)
		end = (u64)-1;
	अन्यथा
		end -= 1;

	em = शून्य;

	/* ok, we didn't find anything, lets look क्रम delalloc */
	delalloc_len = count_range_bits(&inode->io_tree, &delalloc_start,
				 end, len, EXTENT_DELALLOC, 1);
	delalloc_end = delalloc_start + delalloc_len;
	अगर (delalloc_end < delalloc_start)
		delalloc_end = (u64)-1;

	/*
	 * We didn't find anything useful, वापस the original results from
	 * get_extent()
	 */
	अगर (delalloc_start > end || delalloc_end <= start) अणु
		em = hole_em;
		hole_em = शून्य;
		जाओ out;
	पूर्ण

	/*
	 * Adjust the delalloc_start to make sure it करोesn't go backwards from
	 * the start they passed in
	 */
	delalloc_start = max(start, delalloc_start);
	delalloc_len = delalloc_end - delalloc_start;

	अगर (delalloc_len > 0) अणु
		u64 hole_start;
		u64 hole_len;
		स्थिर u64 hole_end = extent_map_end(hole_em);

		em = alloc_extent_map();
		अगर (!em) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		ASSERT(hole_em);
		/*
		 * When btrfs_get_extent can't find anything it वापसs one
		 * huge hole
		 *
		 * Make sure what it found really fits our range, and adjust to
		 * make sure it is based on the start from the caller
		 */
		अगर (hole_end <= start || hole_em->start > end) अणु
		       मुक्त_extent_map(hole_em);
		       hole_em = शून्य;
		पूर्ण अन्यथा अणु
		       hole_start = max(hole_em->start, start);
		       hole_len = hole_end - hole_start;
		पूर्ण

		अगर (hole_em && delalloc_start > hole_start) अणु
			/*
			 * Our hole starts beक्रमe our delalloc, so we have to
			 * वापस just the parts of the hole that go until the
			 * delalloc starts
			 */
			em->len = min(hole_len, delalloc_start - hole_start);
			em->start = hole_start;
			em->orig_start = hole_start;
			/*
			 * Don't adjust block start at all, it is fixed at
			 * EXTENT_MAP_HOLE
			 */
			em->block_start = hole_em->block_start;
			em->block_len = hole_len;
			अगर (test_bit(EXTENT_FLAG_PREALLOC, &hole_em->flags))
				set_bit(EXTENT_FLAG_PREALLOC, &em->flags);
		पूर्ण अन्यथा अणु
			/*
			 * Hole is out of passed range or it starts after
			 * delalloc range
			 */
			em->start = delalloc_start;
			em->len = delalloc_len;
			em->orig_start = delalloc_start;
			em->block_start = EXTENT_MAP_DELALLOC;
			em->block_len = delalloc_len;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस hole_em;
	पूर्ण
out:

	मुक्त_extent_map(hole_em);
	अगर (err) अणु
		मुक्त_extent_map(em);
		वापस ERR_PTR(err);
	पूर्ण
	वापस em;
पूर्ण

अटल काष्ठा extent_map *btrfs_create_dio_extent(काष्ठा btrfs_inode *inode,
						  स्थिर u64 start,
						  स्थिर u64 len,
						  स्थिर u64 orig_start,
						  स्थिर u64 block_start,
						  स्थिर u64 block_len,
						  स्थिर u64 orig_block_len,
						  स्थिर u64 ram_bytes,
						  स्थिर पूर्णांक type)
अणु
	काष्ठा extent_map *em = शून्य;
	पूर्णांक ret;

	अगर (type != BTRFS_ORDERED_NOCOW) अणु
		em = create_io_em(inode, start, len, orig_start, block_start,
				  block_len, orig_block_len, ram_bytes,
				  BTRFS_COMPRESS_NONE, /* compress_type */
				  type);
		अगर (IS_ERR(em))
			जाओ out;
	पूर्ण
	ret = btrfs_add_ordered_extent_dio(inode, start, block_start, len,
					   block_len, type);
	अगर (ret) अणु
		अगर (em) अणु
			मुक्त_extent_map(em);
			btrfs_drop_extent_cache(inode, start, start + len - 1, 0);
		पूर्ण
		em = ERR_PTR(ret);
	पूर्ण
 out:

	वापस em;
पूर्ण

अटल काष्ठा extent_map *btrfs_new_extent_direct(काष्ठा btrfs_inode *inode,
						  u64 start, u64 len)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_map *em;
	काष्ठा btrfs_key ins;
	u64 alloc_hपूर्णांक;
	पूर्णांक ret;

	alloc_hपूर्णांक = get_extent_allocation_hपूर्णांक(inode, start, len);
	ret = btrfs_reserve_extent(root, len, len, fs_info->sectorsize,
				   0, alloc_hपूर्णांक, &ins, 1, 1);
	अगर (ret)
		वापस ERR_PTR(ret);

	em = btrfs_create_dio_extent(inode, start, ins.offset, start,
				     ins.objectid, ins.offset, ins.offset,
				     ins.offset, BTRFS_ORDERED_REGULAR);
	btrfs_dec_block_group_reservations(fs_info, ins.objectid);
	अगर (IS_ERR(em))
		btrfs_मुक्त_reserved_extent(fs_info, ins.objectid, ins.offset,
					   1);

	वापस em;
पूर्ण

अटल bool btrfs_extent_पढ़ोonly(काष्ठा btrfs_fs_info *fs_info, u64 bytenr)
अणु
	काष्ठा btrfs_block_group *block_group;
	bool पढ़ोonly = false;

	block_group = btrfs_lookup_block_group(fs_info, bytenr);
	अगर (!block_group || block_group->ro)
		पढ़ोonly = true;
	अगर (block_group)
		btrfs_put_block_group(block_group);
	वापस पढ़ोonly;
पूर्ण

/*
 * Check अगर we can करो nocow ग_लिखो पूर्णांकo the range [@offset, @offset + @len)
 *
 * @offset:	File offset
 * @len:	The length to ग_लिखो, will be updated to the nocow ग_लिखोable
 *		range
 * @orig_start:	(optional) Return the original file offset of the file extent
 * @orig_len:	(optional) Return the original on-disk length of the file extent
 * @ram_bytes:	(optional) Return the ram_bytes of the file extent
 * @strict:	अगर true, omit optimizations that might क्रमce us पूर्णांकo unnecessary
 *		cow. e.g., करोn't trust generation number.
 *
 * Return:
 * >0	and update @len अगर we can करो nocow ग_लिखो
 *  0	अगर we can't करो nocow ग_लिखो
 * <0	अगर error happened
 *
 * NOTE: This only checks the file extents, caller is responsible to रुको क्रम
 *	 any ordered extents.
 */
noअंतरभूत पूर्णांक can_nocow_extent(काष्ठा inode *inode, u64 offset, u64 *len,
			      u64 *orig_start, u64 *orig_block_len,
			      u64 *ram_bytes, bool strict)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_path *path;
	पूर्णांक ret;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा btrfs_key key;
	u64 disk_bytenr;
	u64 backref_offset;
	u64 extent_end;
	u64 num_bytes;
	पूर्णांक slot;
	पूर्णांक found_type;
	bool nocow = (BTRFS_I(inode)->flags & BTRFS_INODE_NODATACOW);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_lookup_file_extent(शून्य, root, path,
			btrfs_ino(BTRFS_I(inode)), offset, 0);
	अगर (ret < 0)
		जाओ out;

	slot = path->slots[0];
	अगर (ret == 1) अणु
		अगर (slot == 0) अणु
			/* can't find the item, must cow */
			ret = 0;
			जाओ out;
		पूर्ण
		slot--;
	पूर्ण
	ret = 0;
	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, slot);
	अगर (key.objectid != btrfs_ino(BTRFS_I(inode)) ||
	    key.type != BTRFS_EXTENT_DATA_KEY) अणु
		/* not our file or wrong item type, must cow */
		जाओ out;
	पूर्ण

	अगर (key.offset > offset) अणु
		/* Wrong offset, must cow */
		जाओ out;
	पूर्ण

	fi = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);
	found_type = btrfs_file_extent_type(leaf, fi);
	अगर (found_type != BTRFS_खाता_EXTENT_REG &&
	    found_type != BTRFS_खाता_EXTENT_PREALLOC) अणु
		/* not a regular extent, must cow */
		जाओ out;
	पूर्ण

	अगर (!nocow && found_type == BTRFS_खाता_EXTENT_REG)
		जाओ out;

	extent_end = key.offset + btrfs_file_extent_num_bytes(leaf, fi);
	अगर (extent_end <= offset)
		जाओ out;

	disk_bytenr = btrfs_file_extent_disk_bytenr(leaf, fi);
	अगर (disk_bytenr == 0)
		जाओ out;

	अगर (btrfs_file_extent_compression(leaf, fi) ||
	    btrfs_file_extent_encryption(leaf, fi) ||
	    btrfs_file_extent_other_encoding(leaf, fi))
		जाओ out;

	/*
	 * Do the same check as in btrfs_cross_ref_exist but without the
	 * unnecessary search.
	 */
	अगर (!strict &&
	    (btrfs_file_extent_generation(leaf, fi) <=
	     btrfs_root_last_snapshot(&root->root_item)))
		जाओ out;

	backref_offset = btrfs_file_extent_offset(leaf, fi);

	अगर (orig_start) अणु
		*orig_start = key.offset - backref_offset;
		*orig_block_len = btrfs_file_extent_disk_num_bytes(leaf, fi);
		*ram_bytes = btrfs_file_extent_ram_bytes(leaf, fi);
	पूर्ण

	अगर (btrfs_extent_पढ़ोonly(fs_info, disk_bytenr))
		जाओ out;

	num_bytes = min(offset + *len, extent_end) - offset;
	अगर (!nocow && found_type == BTRFS_खाता_EXTENT_PREALLOC) अणु
		u64 range_end;

		range_end = round_up(offset + num_bytes,
				     root->fs_info->sectorsize) - 1;
		ret = test_range_bit(io_tree, offset, range_end,
				     EXTENT_DELALLOC, 0, शून्य);
		अगर (ret) अणु
			ret = -EAGAIN;
			जाओ out;
		पूर्ण
	पूर्ण

	btrfs_release_path(path);

	/*
	 * look क्रम other files referencing this extent, अगर we
	 * find any we must cow
	 */

	ret = btrfs_cross_ref_exist(root, btrfs_ino(BTRFS_I(inode)),
				    key.offset - backref_offset, disk_bytenr,
				    strict);
	अगर (ret) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/*
	 * adjust disk_bytenr and num_bytes to cover just the bytes
	 * in this extent we are about to ग_लिखो.  If there
	 * are any csums in that range we have to cow in order
	 * to keep the csums correct
	 */
	disk_bytenr += backref_offset;
	disk_bytenr += offset - key.offset;
	अगर (csum_exist_in_range(fs_info, disk_bytenr, num_bytes))
		जाओ out;
	/*
	 * all of the above have passed, it is safe to overग_लिखो this extent
	 * without cow
	 */
	*len = num_bytes;
	ret = 1;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक lock_extent_direct(काष्ठा inode *inode, u64 lockstart, u64 lockend,
			      काष्ठा extent_state **cached_state, bool writing)
अणु
	काष्ठा btrfs_ordered_extent *ordered;
	पूर्णांक ret = 0;

	जबतक (1) अणु
		lock_extent_bits(&BTRFS_I(inode)->io_tree, lockstart, lockend,
				 cached_state);
		/*
		 * We're concerned with the entire range that we're going to be
		 * करोing DIO to, so we need to make sure there's no ordered
		 * extents in this range.
		 */
		ordered = btrfs_lookup_ordered_range(BTRFS_I(inode), lockstart,
						     lockend - lockstart + 1);

		/*
		 * We need to make sure there are no buffered pages in this
		 * range either, we could have raced between the invalidate in
		 * generic_file_direct_ग_लिखो and locking the extent.  The
		 * invalidate needs to happen so that पढ़ोs after a ग_लिखो करो not
		 * get stale data.
		 */
		अगर (!ordered &&
		    (!writing || !filemap_range_has_page(inode->i_mapping,
							 lockstart, lockend)))
			अवरोध;

		unlock_extent_cached(&BTRFS_I(inode)->io_tree, lockstart, lockend,
				     cached_state);

		अगर (ordered) अणु
			/*
			 * If we are करोing a DIO पढ़ो and the ordered extent we
			 * found is क्रम a buffered ग_लिखो, we can not रुको क्रम it
			 * to complete and retry, because अगर we करो so we can
			 * deadlock with concurrent buffered ग_लिखोs on page
			 * locks. This happens only अगर our DIO पढ़ो covers more
			 * than one extent map, अगर at this poपूर्णांक has alपढ़ोy
			 * created an ordered extent क्रम a previous extent map
			 * and locked its range in the inode's io tree, and a
			 * concurrent ग_लिखो against that previous extent map's
			 * range and this range started (we unlock the ranges
			 * in the io tree only when the bios complete and
			 * buffered ग_लिखोs always lock pages beक्रमe attempting
			 * to lock range in the io tree).
			 */
			अगर (writing ||
			    test_bit(BTRFS_ORDERED_सूचीECT, &ordered->flags))
				btrfs_start_ordered_extent(ordered, 1);
			अन्यथा
				ret = -ENOTBLK;
			btrfs_put_ordered_extent(ordered);
		पूर्ण अन्यथा अणु
			/*
			 * We could trigger ग_लिखोback क्रम this range (and रुको
			 * क्रम it to complete) and then invalidate the pages क्रम
			 * this range (through invalidate_inode_pages2_range()),
			 * but that can lead us to a deadlock with a concurrent
			 * call to पढ़ोahead (a buffered पढ़ो or a defrag call
			 * triggered a पढ़ोahead) on a page lock due to an
			 * ordered dio extent we created beक्रमe but did not have
			 * yet a corresponding bio submitted (whence it can not
			 * complete), which makes पढ़ोahead रुको क्रम that
			 * ordered extent to complete जबतक holding a lock on
			 * that page.
			 */
			ret = -ENOTBLK;
		पूर्ण

		अगर (ret)
			अवरोध;

		cond_resched();
	पूर्ण

	वापस ret;
पूर्ण

/* The callers of this must take lock_extent() */
अटल काष्ठा extent_map *create_io_em(काष्ठा btrfs_inode *inode, u64 start,
				       u64 len, u64 orig_start, u64 block_start,
				       u64 block_len, u64 orig_block_len,
				       u64 ram_bytes, पूर्णांक compress_type,
				       पूर्णांक type)
अणु
	काष्ठा extent_map_tree *em_tree;
	काष्ठा extent_map *em;
	पूर्णांक ret;

	ASSERT(type == BTRFS_ORDERED_PREALLOC ||
	       type == BTRFS_ORDERED_COMPRESSED ||
	       type == BTRFS_ORDERED_NOCOW ||
	       type == BTRFS_ORDERED_REGULAR);

	em_tree = &inode->extent_tree;
	em = alloc_extent_map();
	अगर (!em)
		वापस ERR_PTR(-ENOMEM);

	em->start = start;
	em->orig_start = orig_start;
	em->len = len;
	em->block_len = block_len;
	em->block_start = block_start;
	em->orig_block_len = orig_block_len;
	em->ram_bytes = ram_bytes;
	em->generation = -1;
	set_bit(EXTENT_FLAG_PINNED, &em->flags);
	अगर (type == BTRFS_ORDERED_PREALLOC) अणु
		set_bit(EXTENT_FLAG_FILLING, &em->flags);
	पूर्ण अन्यथा अगर (type == BTRFS_ORDERED_COMPRESSED) अणु
		set_bit(EXTENT_FLAG_COMPRESSED, &em->flags);
		em->compress_type = compress_type;
	पूर्ण

	करो अणु
		btrfs_drop_extent_cache(inode, em->start,
					em->start + em->len - 1, 0);
		ग_लिखो_lock(&em_tree->lock);
		ret = add_extent_mapping(em_tree, em, 1);
		ग_लिखो_unlock(&em_tree->lock);
		/*
		 * The caller has taken lock_extent(), who could race with us
		 * to add em?
		 */
	पूर्ण जबतक (ret == -EEXIST);

	अगर (ret) अणु
		मुक्त_extent_map(em);
		वापस ERR_PTR(ret);
	पूर्ण

	/* em got 2 refs now, callers needs to करो मुक्त_extent_map once. */
	वापस em;
पूर्ण


अटल पूर्णांक btrfs_get_blocks_direct_ग_लिखो(काष्ठा extent_map **map,
					 काष्ठा inode *inode,
					 काष्ठा btrfs_dio_data *dio_data,
					 u64 start, u64 len)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा extent_map *em = *map;
	पूर्णांक ret = 0;

	/*
	 * We करोn't allocate a new extent in the following हालs
	 *
	 * 1) The inode is marked as NODATACOW. In this हाल we'll just use the
	 * existing extent.
	 * 2) The extent is marked as PREALLOC. We're good to go here and can
	 * just use the extent.
	 *
	 */
	अगर (test_bit(EXTENT_FLAG_PREALLOC, &em->flags) ||
	    ((BTRFS_I(inode)->flags & BTRFS_INODE_NODATACOW) &&
	     em->block_start != EXTENT_MAP_HOLE)) अणु
		पूर्णांक type;
		u64 block_start, orig_start, orig_block_len, ram_bytes;

		अगर (test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
			type = BTRFS_ORDERED_PREALLOC;
		अन्यथा
			type = BTRFS_ORDERED_NOCOW;
		len = min(len, em->len - (start - em->start));
		block_start = em->block_start + (start - em->start);

		अगर (can_nocow_extent(inode, start, &len, &orig_start,
				     &orig_block_len, &ram_bytes, false) == 1 &&
		    btrfs_inc_nocow_ग_लिखोrs(fs_info, block_start)) अणु
			काष्ठा extent_map *em2;

			em2 = btrfs_create_dio_extent(BTRFS_I(inode), start, len,
						      orig_start, block_start,
						      len, orig_block_len,
						      ram_bytes, type);
			btrfs_dec_nocow_ग_लिखोrs(fs_info, block_start);
			अगर (type == BTRFS_ORDERED_PREALLOC) अणु
				मुक्त_extent_map(em);
				*map = em = em2;
			पूर्ण

			अगर (em2 && IS_ERR(em2)) अणु
				ret = PTR_ERR(em2);
				जाओ out;
			पूर्ण
			/*
			 * For inode marked NODATACOW or extent marked PREALLOC,
			 * use the existing or pपुनः_स्मृतिated extent, so करोes not
			 * need to adjust btrfs_space_info's bytes_may_use.
			 */
			btrfs_मुक्त_reserved_data_space_noquota(fs_info, len);
			जाओ skip_cow;
		पूर्ण
	पूर्ण

	/* this will cow the extent */
	मुक्त_extent_map(em);
	*map = em = btrfs_new_extent_direct(BTRFS_I(inode), start, len);
	अगर (IS_ERR(em)) अणु
		ret = PTR_ERR(em);
		जाओ out;
	पूर्ण

	len = min(len, em->len - (start - em->start));

skip_cow:
	/*
	 * Need to update the i_size under the extent lock so buffered
	 * पढ़ोers will get the updated i_size when we unlock.
	 */
	अगर (start + len > i_size_पढ़ो(inode))
		i_size_ग_लिखो(inode, start + len);

	dio_data->reserve -= len;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_dio_iomap_begin(काष्ठा inode *inode, loff_t start,
		loff_t length, अचिन्हित पूर्णांक flags, काष्ठा iomap *iomap,
		काष्ठा iomap *srcmap)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा extent_map *em;
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा btrfs_dio_data *dio_data = शून्य;
	u64 lockstart, lockend;
	स्थिर bool ग_लिखो = !!(flags & IOMAP_WRITE);
	पूर्णांक ret = 0;
	u64 len = length;
	bool unlock_extents = false;

	अगर (!ग_लिखो)
		len = min_t(u64, len, fs_info->sectorsize);

	lockstart = start;
	lockend = start + len - 1;

	/*
	 * The generic stuff only करोes filemap_ग_लिखो_and_रुको_range, which
	 * isn't enough if we've written compressed pages to this area, so we
	 * need to flush the dirty pages again to make असलolutely sure that any
	 * outstanding dirty pages are on disk.
	 */
	अगर (test_bit(BTRFS_INODE_HAS_ASYNC_EXTENT,
		     &BTRFS_I(inode)->runसमय_flags)) अणु
		ret = filemap_fdataग_लिखो_range(inode->i_mapping, start,
					       start + length - 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	dio_data = kzalloc(माप(*dio_data), GFP_NOFS);
	अगर (!dio_data)
		वापस -ENOMEM;

	dio_data->length = length;
	अगर (ग_लिखो) अणु
		dio_data->reserve = round_up(length, fs_info->sectorsize);
		ret = btrfs_delalloc_reserve_space(BTRFS_I(inode),
				&dio_data->data_reserved,
				start, dio_data->reserve);
		अगर (ret) अणु
			extent_changeset_मुक्त(dio_data->data_reserved);
			kमुक्त(dio_data);
			वापस ret;
		पूर्ण
	पूर्ण
	iomap->निजी = dio_data;


	/*
	 * If this errors out it's because we couldn't invalidate pagecache क्रम
	 * this range and we need to fallback to buffered.
	 */
	अगर (lock_extent_direct(inode, lockstart, lockend, &cached_state, ग_लिखो)) अणु
		ret = -ENOTBLK;
		जाओ err;
	पूर्ण

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, start, len);
	अगर (IS_ERR(em)) अणु
		ret = PTR_ERR(em);
		जाओ unlock_err;
	पूर्ण

	/*
	 * Ok क्रम INLINE and COMPRESSED extents we need to fallback on buffered
	 * io.  INLINE is special, and we could probably kludge it in here, but
	 * it's still buffered so क्रम safety lets just fall back to the generic
	 * buffered path.
	 *
	 * For COMPRESSED we _have_ to पढ़ो the entire extent in so we can
	 * decompress it, so there will be buffering required no matter what we
	 * करो, so go ahead and fallback to buffered.
	 *
	 * We वापस -ENOTBLK because that's what makes DIO go ahead and go back
	 * to buffered IO.  Don't blame me, this is the price we pay क्रम using
	 * the generic code.
	 */
	अगर (test_bit(EXTENT_FLAG_COMPRESSED, &em->flags) ||
	    em->block_start == EXTENT_MAP_INLINE) अणु
		मुक्त_extent_map(em);
		ret = -ENOTBLK;
		जाओ unlock_err;
	पूर्ण

	len = min(len, em->len - (start - em->start));
	अगर (ग_लिखो) अणु
		ret = btrfs_get_blocks_direct_ग_लिखो(&em, inode, dio_data,
						    start, len);
		अगर (ret < 0)
			जाओ unlock_err;
		unlock_extents = true;
		/* Recalc len in हाल the new em is smaller than requested */
		len = min(len, em->len - (start - em->start));
	पूर्ण अन्यथा अणु
		/*
		 * We need to unlock only the end area that we aren't using.
		 * The rest is going to be unlocked by the endio routine.
		 */
		lockstart = start + len;
		अगर (lockstart < lockend)
			unlock_extents = true;
	पूर्ण

	अगर (unlock_extents)
		unlock_extent_cached(&BTRFS_I(inode)->io_tree,
				     lockstart, lockend, &cached_state);
	अन्यथा
		मुक्त_extent_state(cached_state);

	/*
	 * Translate extent map inक्रमmation to iomap.
	 * We trim the extents (and move the addr) even though iomap code करोes
	 * that, since we have locked only the parts we are perक्रमming I/O in.
	 */
	अगर ((em->block_start == EXTENT_MAP_HOLE) ||
	    (test_bit(EXTENT_FLAG_PREALLOC, &em->flags) && !ग_लिखो)) अणु
		iomap->addr = IOMAP_शून्य_ADDR;
		iomap->type = IOMAP_HOLE;
	पूर्ण अन्यथा अणु
		iomap->addr = em->block_start + (start - em->start);
		iomap->type = IOMAP_MAPPED;
	पूर्ण
	iomap->offset = start;
	iomap->bdev = fs_info->fs_devices->latest_bdev;
	iomap->length = len;

	अगर (ग_लिखो && btrfs_use_zone_append(BTRFS_I(inode), em->block_start))
		iomap->flags |= IOMAP_F_ZONE_APPEND;

	मुक्त_extent_map(em);

	वापस 0;

unlock_err:
	unlock_extent_cached(&BTRFS_I(inode)->io_tree, lockstart, lockend,
			     &cached_state);
err:
	अगर (dio_data) अणु
		btrfs_delalloc_release_space(BTRFS_I(inode),
				dio_data->data_reserved, start,
				dio_data->reserve, true);
		btrfs_delalloc_release_extents(BTRFS_I(inode), dio_data->reserve);
		extent_changeset_मुक्त(dio_data->data_reserved);
		kमुक्त(dio_data);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_dio_iomap_end(काष्ठा inode *inode, loff_t pos, loff_t length,
		sमाप_प्रकार written, अचिन्हित पूर्णांक flags, काष्ठा iomap *iomap)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_dio_data *dio_data = iomap->निजी;
	माप_प्रकार submitted = dio_data->submitted;
	स्थिर bool ग_लिखो = !!(flags & IOMAP_WRITE);

	अगर (!ग_लिखो && (iomap->type == IOMAP_HOLE)) अणु
		/* If पढ़ोing from a hole, unlock and वापस */
		unlock_extent(&BTRFS_I(inode)->io_tree, pos, pos + length - 1);
		जाओ out;
	पूर्ण

	अगर (submitted < length) अणु
		pos += submitted;
		length -= submitted;
		अगर (ग_लिखो)
			__endio_ग_लिखो_update_ordered(BTRFS_I(inode), pos,
					length, false);
		अन्यथा
			unlock_extent(&BTRFS_I(inode)->io_tree, pos,
				      pos + length - 1);
		ret = -ENOTBLK;
	पूर्ण

	अगर (ग_लिखो) अणु
		अगर (dio_data->reserve)
			btrfs_delalloc_release_space(BTRFS_I(inode),
					dio_data->data_reserved, pos,
					dio_data->reserve, true);
		btrfs_delalloc_release_extents(BTRFS_I(inode), dio_data->length);
		extent_changeset_मुक्त(dio_data->data_reserved);
	पूर्ण
out:
	kमुक्त(dio_data);
	iomap->निजी = शून्य;

	वापस ret;
पूर्ण

अटल व्योम btrfs_dio_निजी_put(काष्ठा btrfs_dio_निजी *dip)
अणु
	/*
	 * This implies a barrier so that stores to dio_bio->bi_status beक्रमe
	 * this and loads of dio_bio->bi_status after this are fully ordered.
	 */
	अगर (!refcount_dec_and_test(&dip->refs))
		वापस;

	अगर (btrfs_op(dip->dio_bio) == BTRFS_MAP_WRITE) अणु
		__endio_ग_लिखो_update_ordered(BTRFS_I(dip->inode),
					     dip->logical_offset,
					     dip->bytes,
					     !dip->dio_bio->bi_status);
	पूर्ण अन्यथा अणु
		unlock_extent(&BTRFS_I(dip->inode)->io_tree,
			      dip->logical_offset,
			      dip->logical_offset + dip->bytes - 1);
	पूर्ण

	bio_endio(dip->dio_bio);
	kमुक्त(dip);
पूर्ण

अटल blk_status_t submit_dio_repair_bio(काष्ठा inode *inode, काष्ठा bio *bio,
					  पूर्णांक mirror_num,
					  अचिन्हित दीर्घ bio_flags)
अणु
	काष्ठा btrfs_dio_निजी *dip = bio->bi_निजी;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	blk_status_t ret;

	BUG_ON(bio_op(bio) == REQ_OP_WRITE);

	ret = btrfs_bio_wq_end_io(fs_info, bio, BTRFS_WQ_ENDIO_DATA);
	अगर (ret)
		वापस ret;

	refcount_inc(&dip->refs);
	ret = btrfs_map_bio(fs_info, bio, mirror_num);
	अगर (ret)
		refcount_dec(&dip->refs);
	वापस ret;
पूर्ण

अटल blk_status_t btrfs_check_पढ़ो_dio_bio(काष्ठा inode *inode,
					     काष्ठा btrfs_io_bio *io_bio,
					     स्थिर bool uptodate)
अणु
	काष्ठा btrfs_fs_info *fs_info = BTRFS_I(inode)->root->fs_info;
	स्थिर u32 sectorsize = fs_info->sectorsize;
	काष्ठा extent_io_tree *failure_tree = &BTRFS_I(inode)->io_failure_tree;
	काष्ठा extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	स्थिर bool csum = !(BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM);
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	u64 start = io_bio->logical;
	u32 bio_offset = 0;
	blk_status_t err = BLK_STS_OK;

	__bio_क्रम_each_segment(bvec, &io_bio->bio, iter, io_bio->iter) अणु
		अचिन्हित पूर्णांक i, nr_sectors, pgoff;

		nr_sectors = BTRFS_BYTES_TO_BLKS(fs_info, bvec.bv_len);
		pgoff = bvec.bv_offset;
		क्रम (i = 0; i < nr_sectors; i++) अणु
			ASSERT(pgoff < PAGE_SIZE);
			अगर (uptodate &&
			    (!csum || !check_data_csum(inode, io_bio,
						       bio_offset, bvec.bv_page,
						       pgoff, start))) अणु
				clean_io_failure(fs_info, failure_tree, io_tree,
						 start, bvec.bv_page,
						 btrfs_ino(BTRFS_I(inode)),
						 pgoff);
			पूर्ण अन्यथा अणु
				blk_status_t status;

				ASSERT((start - io_bio->logical) < अच_पूर्णांक_उच्च);
				status = btrfs_submit_पढ़ो_repair(inode,
							&io_bio->bio,
							start - io_bio->logical,
							bvec.bv_page, pgoff,
							start,
							start + sectorsize - 1,
							io_bio->mirror_num,
							submit_dio_repair_bio);
				अगर (status)
					err = status;
			पूर्ण
			start += sectorsize;
			ASSERT(bio_offset + sectorsize > bio_offset);
			bio_offset += sectorsize;
			pgoff += sectorsize;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम __endio_ग_लिखो_update_ordered(काष्ठा btrfs_inode *inode,
					 स्थिर u64 offset, स्थिर u64 bytes,
					 स्थिर bool uptodate)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_ordered_extent *ordered = शून्य;
	काष्ठा btrfs_workqueue *wq;
	u64 ordered_offset = offset;
	u64 ordered_bytes = bytes;
	u64 last_offset;

	अगर (btrfs_is_मुक्त_space_inode(inode))
		wq = fs_info->endio_मुक्तspace_worker;
	अन्यथा
		wq = fs_info->endio_ग_लिखो_workers;

	जबतक (ordered_offset < offset + bytes) अणु
		last_offset = ordered_offset;
		अगर (btrfs_dec_test_first_ordered_pending(inode, &ordered,
							 &ordered_offset,
							 ordered_bytes,
							 uptodate)) अणु
			btrfs_init_work(&ordered->work, finish_ordered_fn, शून्य,
					शून्य);
			btrfs_queue_work(wq, &ordered->work);
		पूर्ण

		/* No ordered extent found in the range, निकास */
		अगर (ordered_offset == last_offset)
			वापस;
		/*
		 * Our bio might span multiple ordered extents. In this हाल
		 * we keep going until we have accounted the whole dio.
		 */
		अगर (ordered_offset < offset + bytes) अणु
			ordered_bytes = offset + bytes - ordered_offset;
			ordered = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल blk_status_t btrfs_submit_bio_start_direct_io(काष्ठा inode *inode,
						     काष्ठा bio *bio,
						     u64 dio_file_offset)
अणु
	वापस btrfs_csum_one_bio(BTRFS_I(inode), bio, dio_file_offset, 1);
पूर्ण

अटल व्योम btrfs_end_dio_bio(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_dio_निजी *dip = bio->bi_निजी;
	blk_status_t err = bio->bi_status;

	अगर (err)
		btrfs_warn(BTRFS_I(dip->inode)->root->fs_info,
			   "direct IO failed ino %llu rw %d,%u sector %#Lx len %u err no %d",
			   btrfs_ino(BTRFS_I(dip->inode)), bio_op(bio),
			   bio->bi_opf, bio->bi_iter.bi_sector,
			   bio->bi_iter.bi_size, err);

	अगर (bio_op(bio) == REQ_OP_READ) अणु
		err = btrfs_check_पढ़ो_dio_bio(dip->inode, btrfs_io_bio(bio),
					       !err);
	पूर्ण

	अगर (err)
		dip->dio_bio->bi_status = err;

	btrfs_record_physical_zoned(dip->inode, dip->logical_offset, bio);

	bio_put(bio);
	btrfs_dio_निजी_put(dip);
पूर्ण

अटल अंतरभूत blk_status_t btrfs_submit_dio_bio(काष्ठा bio *bio,
		काष्ठा inode *inode, u64 file_offset, पूर्णांक async_submit)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_dio_निजी *dip = bio->bi_निजी;
	bool ग_लिखो = btrfs_op(bio) == BTRFS_MAP_WRITE;
	blk_status_t ret;

	/* Check btrfs_submit_bio_hook() क्रम rules about async submit. */
	अगर (async_submit)
		async_submit = !atomic_पढ़ो(&BTRFS_I(inode)->sync_ग_लिखोrs);

	अगर (!ग_लिखो) अणु
		ret = btrfs_bio_wq_end_io(fs_info, bio, BTRFS_WQ_ENDIO_DATA);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM)
		जाओ map;

	अगर (ग_लिखो && async_submit) अणु
		ret = btrfs_wq_submit_bio(inode, bio, 0, 0, file_offset,
					  btrfs_submit_bio_start_direct_io);
		जाओ err;
	पूर्ण अन्यथा अगर (ग_लिखो) अणु
		/*
		 * If we aren't करोing async submit, calculate the csum of the
		 * bio now.
		 */
		ret = btrfs_csum_one_bio(BTRFS_I(inode), bio, file_offset, 1);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु
		u64 csum_offset;

		csum_offset = file_offset - dip->logical_offset;
		csum_offset >>= fs_info->sectorsize_bits;
		csum_offset *= fs_info->csum_size;
		btrfs_io_bio(bio)->csum = dip->csums + csum_offset;
	पूर्ण
map:
	ret = btrfs_map_bio(fs_info, bio, 0);
err:
	वापस ret;
पूर्ण

/*
 * If this succeeds, the btrfs_dio_निजी is responsible क्रम cleaning up locked
 * or ordered extents whether or not we submit any bios.
 */
अटल काष्ठा btrfs_dio_निजी *btrfs_create_dio_निजी(काष्ठा bio *dio_bio,
							  काष्ठा inode *inode,
							  loff_t file_offset)
अणु
	स्थिर bool ग_लिखो = (btrfs_op(dio_bio) == BTRFS_MAP_WRITE);
	स्थिर bool csum = !(BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM);
	माप_प्रकार dip_size;
	काष्ठा btrfs_dio_निजी *dip;

	dip_size = माप(*dip);
	अगर (!ग_लिखो && csum) अणु
		काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
		माप_प्रकार nblocks;

		nblocks = dio_bio->bi_iter.bi_size >> fs_info->sectorsize_bits;
		dip_size += fs_info->csum_size * nblocks;
	पूर्ण

	dip = kzalloc(dip_size, GFP_NOFS);
	अगर (!dip)
		वापस शून्य;

	dip->inode = inode;
	dip->logical_offset = file_offset;
	dip->bytes = dio_bio->bi_iter.bi_size;
	dip->disk_bytenr = dio_bio->bi_iter.bi_sector << 9;
	dip->dio_bio = dio_bio;
	refcount_set(&dip->refs, 1);
	वापस dip;
पूर्ण

अटल blk_qc_t btrfs_submit_direct(काष्ठा inode *inode, काष्ठा iomap *iomap,
		काष्ठा bio *dio_bio, loff_t file_offset)
अणु
	स्थिर bool ग_लिखो = (btrfs_op(dio_bio) == BTRFS_MAP_WRITE);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	स्थिर bool raid56 = (btrfs_data_alloc_profile(fs_info) &
			     BTRFS_BLOCK_GROUP_RAID56_MASK);
	काष्ठा btrfs_dio_निजी *dip;
	काष्ठा bio *bio;
	u64 start_sector;
	पूर्णांक async_submit = 0;
	u64 submit_len;
	पूर्णांक clone_offset = 0;
	पूर्णांक clone_len;
	u64 logical;
	पूर्णांक ret;
	blk_status_t status;
	काष्ठा btrfs_io_geometry geom;
	काष्ठा btrfs_dio_data *dio_data = iomap->निजी;
	काष्ठा extent_map *em = शून्य;

	dip = btrfs_create_dio_निजी(dio_bio, inode, file_offset);
	अगर (!dip) अणु
		अगर (!ग_लिखो) अणु
			unlock_extent(&BTRFS_I(inode)->io_tree, file_offset,
				file_offset + dio_bio->bi_iter.bi_size - 1);
		पूर्ण
		dio_bio->bi_status = BLK_STS_RESOURCE;
		bio_endio(dio_bio);
		वापस BLK_QC_T_NONE;
	पूर्ण

	अगर (!ग_लिखो) अणु
		/*
		 * Load the csums up front to reduce csum tree searches and
		 * contention when submitting bios.
		 *
		 * If we have csums disabled this will करो nothing.
		 */
		status = btrfs_lookup_bio_sums(inode, dio_bio, dip->csums);
		अगर (status != BLK_STS_OK)
			जाओ out_err;
	पूर्ण

	start_sector = dio_bio->bi_iter.bi_sector;
	submit_len = dio_bio->bi_iter.bi_size;

	करो अणु
		logical = start_sector << 9;
		em = btrfs_get_chunk_map(fs_info, logical, submit_len);
		अगर (IS_ERR(em)) अणु
			status = त्रुटि_सं_to_blk_status(PTR_ERR(em));
			em = शून्य;
			जाओ out_err_em;
		पूर्ण
		ret = btrfs_get_io_geometry(fs_info, em, btrfs_op(dio_bio),
					    logical, submit_len, &geom);
		अगर (ret) अणु
			status = त्रुटि_सं_to_blk_status(ret);
			जाओ out_err_em;
		पूर्ण
		ASSERT(geom.len <= पूर्णांक_उच्च);

		clone_len = min_t(पूर्णांक, submit_len, geom.len);

		/*
		 * This will never fail as it's passing GPF_NOFS and
		 * the allocation is backed by btrfs_bioset.
		 */
		bio = btrfs_bio_clone_partial(dio_bio, clone_offset, clone_len);
		bio->bi_निजी = dip;
		bio->bi_end_io = btrfs_end_dio_bio;
		btrfs_io_bio(bio)->logical = file_offset;

		अगर (bio_op(bio) == REQ_OP_ZONE_APPEND) अणु
			status = extract_ordered_extent(BTRFS_I(inode), bio,
							file_offset);
			अगर (status) अणु
				bio_put(bio);
				जाओ out_err;
			पूर्ण
		पूर्ण

		ASSERT(submit_len >= clone_len);
		submit_len -= clone_len;

		/*
		 * Increase the count beक्रमe we submit the bio so we know
		 * the end IO handler won't happen beक्रमe we increase the
		 * count. Otherwise, the dip might get मुक्तd beक्रमe we're
		 * करोne setting it up.
		 *
		 * We transfer the initial reference to the last bio, so we
		 * करोn't need to increment the reference count क्रम the last one.
		 */
		अगर (submit_len > 0) अणु
			refcount_inc(&dip->refs);
			/*
			 * If we are submitting more than one bio, submit them
			 * all asynchronously. The exception is RAID 5 or 6, as
			 * asynchronous checksums make it dअगरficult to collect
			 * full stripe ग_लिखोs.
			 */
			अगर (!raid56)
				async_submit = 1;
		पूर्ण

		status = btrfs_submit_dio_bio(bio, inode, file_offset,
						async_submit);
		अगर (status) अणु
			bio_put(bio);
			अगर (submit_len > 0)
				refcount_dec(&dip->refs);
			जाओ out_err_em;
		पूर्ण

		dio_data->submitted += clone_len;
		clone_offset += clone_len;
		start_sector += clone_len >> 9;
		file_offset += clone_len;

		मुक्त_extent_map(em);
	पूर्ण जबतक (submit_len > 0);
	वापस BLK_QC_T_NONE;

out_err_em:
	मुक्त_extent_map(em);
out_err:
	dip->dio_bio->bi_status = status;
	btrfs_dio_निजी_put(dip);

	वापस BLK_QC_T_NONE;
पूर्ण

स्थिर काष्ठा iomap_ops btrfs_dio_iomap_ops = अणु
	.iomap_begin            = btrfs_dio_iomap_begin,
	.iomap_end              = btrfs_dio_iomap_end,
पूर्ण;

स्थिर काष्ठा iomap_dio_ops btrfs_dio_ops = अणु
	.submit_io		= btrfs_submit_direct,
पूर्ण;

अटल पूर्णांक btrfs_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
			u64 start, u64 len)
अणु
	पूर्णांक	ret;

	ret = fiemap_prep(inode, fieinfo, start, &len, 0);
	अगर (ret)
		वापस ret;

	वापस extent_fiemap(BTRFS_I(inode), fieinfo, start, len);
पूर्ण

पूर्णांक btrfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(page->mapping->host);
	u64 start = page_offset(page);
	u64 end = start + PAGE_SIZE - 1;
	अचिन्हित दीर्घ bio_flags = 0;
	काष्ठा bio *bio = शून्य;
	पूर्णांक ret;

	btrfs_lock_and_flush_ordered_range(inode, start, end, शून्य);

	ret = btrfs_करो_पढ़ोpage(page, शून्य, &bio, &bio_flags, 0, शून्य);
	अगर (bio)
		ret = submit_one_bio(bio, 0, bio_flags);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	पूर्णांक ret;

	अगर (current->flags & PF_MEMALLOC) अणु
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		unlock_page(page);
		वापस 0;
	पूर्ण

	/*
	 * If we are under memory pressure we will call this directly from the
	 * VM, we need to make sure we have the inode referenced क्रम the ordered
	 * extent.  If not just वापस like we didn't करो anything.
	 */
	अगर (!igrab(inode)) अणु
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		वापस AOP_WRITEPAGE_ACTIVATE;
	पूर्ण
	ret = extent_ग_लिखो_full_page(page, wbc);
	btrfs_add_delayed_iput(inode);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_ग_लिखोpages(काष्ठा address_space *mapping,
			    काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस extent_ग_लिखोpages(mapping, wbc);
पूर्ण

अटल व्योम btrfs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	extent_पढ़ोahead(rac);
पूर्ण

अटल पूर्णांक __btrfs_releasepage(काष्ठा page *page, gfp_t gfp_flags)
अणु
	पूर्णांक ret = try_release_extent_mapping(page, gfp_flags);
	अगर (ret == 1)
		clear_page_extent_mapped(page);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_releasepage(काष्ठा page *page, gfp_t gfp_flags)
अणु
	अगर (PageWriteback(page) || PageDirty(page))
		वापस 0;
	वापस __btrfs_releasepage(page, gfp_flags);
पूर्ण

#अगर_घोषित CONFIG_MIGRATION
अटल पूर्णांक btrfs_migratepage(काष्ठा address_space *mapping,
			     काष्ठा page *newpage, काष्ठा page *page,
			     क्रमागत migrate_mode mode)
अणु
	पूर्णांक ret;

	ret = migrate_page_move_mapping(mapping, newpage, page, 0);
	अगर (ret != MIGRATEPAGE_SUCCESS)
		वापस ret;

	अगर (page_has_निजी(page))
		attach_page_निजी(newpage, detach_page_निजी(page));

	अगर (PagePrivate2(page)) अणु
		ClearPagePrivate2(page);
		SetPagePrivate2(newpage);
	पूर्ण

	अगर (mode != MIGRATE_SYNC_NO_COPY)
		migrate_page_copy(newpage, page);
	अन्यथा
		migrate_page_states(newpage, page);
	वापस MIGRATEPAGE_SUCCESS;
पूर्ण
#पूर्ण_अगर

अटल व्योम btrfs_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				 अचिन्हित पूर्णांक length)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(page->mapping->host);
	काष्ठा extent_io_tree *tree = &inode->io_tree;
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा extent_state *cached_state = शून्य;
	u64 page_start = page_offset(page);
	u64 page_end = page_start + PAGE_SIZE - 1;
	u64 start;
	u64 end;
	पूर्णांक inode_evicting = inode->vfs_inode.i_state & I_FREEING;
	bool found_ordered = false;
	bool completed_ordered = false;

	/*
	 * we have the page locked, so new ग_लिखोback can't start,
	 * and the dirty bit won't be cleared जबतक we are here.
	 *
	 * Wait क्रम IO on this page so that we can safely clear
	 * the PagePrivate2 bit and करो ordered accounting
	 */
	रुको_on_page_ग_लिखोback(page);

	अगर (offset) अणु
		btrfs_releasepage(page, GFP_NOFS);
		वापस;
	पूर्ण

	अगर (!inode_evicting)
		lock_extent_bits(tree, page_start, page_end, &cached_state);

	start = page_start;
again:
	ordered = btrfs_lookup_ordered_range(inode, start, page_end - start + 1);
	अगर (ordered) अणु
		found_ordered = true;
		end = min(page_end,
			  ordered->file_offset + ordered->num_bytes - 1);
		/*
		 * IO on this page will never be started, so we need to account
		 * क्रम any ordered extents now. Don't clear EXTENT_DELALLOC_NEW
		 * here, must leave that up क्रम the ordered extent completion.
		 */
		अगर (!inode_evicting)
			clear_extent_bit(tree, start, end,
					 EXTENT_DELALLOC |
					 EXTENT_LOCKED | EXTENT_DO_ACCOUNTING |
					 EXTENT_DEFRAG, 1, 0, &cached_state);
		/*
		 * whoever cleared the निजी bit is responsible
		 * क्रम the finish_ordered_io
		 */
		अगर (TestClearPagePrivate2(page)) अणु
			spin_lock_irq(&inode->ordered_tree.lock);
			set_bit(BTRFS_ORDERED_TRUNCATED, &ordered->flags);
			ordered->truncated_len = min(ordered->truncated_len,
						     start - ordered->file_offset);
			spin_unlock_irq(&inode->ordered_tree.lock);

			अगर (btrfs_dec_test_ordered_pending(inode, &ordered,
							   start,
							   end - start + 1, 1)) अणु
				btrfs_finish_ordered_io(ordered);
				completed_ordered = true;
			पूर्ण
		पूर्ण
		btrfs_put_ordered_extent(ordered);
		अगर (!inode_evicting) अणु
			cached_state = शून्य;
			lock_extent_bits(tree, start, end,
					 &cached_state);
		पूर्ण

		start = end + 1;
		अगर (start < page_end)
			जाओ again;
	पूर्ण

	/*
	 * Qgroup reserved space handler
	 * Page here will be either
	 * 1) Alपढ़ोy written to disk or ordered extent alपढ़ोy submitted
	 *    Then its QGROUP_RESERVED bit in io_tree is alपढ़ोy cleaned.
	 *    Qgroup will be handled by its qgroup_record then.
	 *    btrfs_qgroup_मुक्त_data() call will करो nothing here.
	 *
	 * 2) Not written to disk yet
	 *    Then btrfs_qgroup_मुक्त_data() call will clear the QGROUP_RESERVED
	 *    bit of its io_tree, and मुक्त the qgroup reserved data space.
	 *    Since the IO will never happen क्रम this page.
	 */
	btrfs_qgroup_मुक्त_data(inode, शून्य, page_start, PAGE_SIZE);
	अगर (!inode_evicting) अणु
		bool delete = true;

		/*
		 * If there's an ordered extent क्रम this range and we have not
		 * finished it ourselves, we must leave EXTENT_DELALLOC_NEW set
		 * in the range क्रम the ordered extent completion. We must also
		 * not delete the range, otherwise we would lose that bit (and
		 * any other bits set in the range). Make sure EXTENT_UPTODATE
		 * is cleared अगर we करोn't delete, otherwise it can lead to
		 * corruptions अगर the i_size is extented later.
		 */
		अगर (found_ordered && !completed_ordered)
			delete = false;
		clear_extent_bit(tree, page_start, page_end, EXTENT_LOCKED |
				 EXTENT_DELALLOC | EXTENT_UPTODATE |
				 EXTENT_DO_ACCOUNTING | EXTENT_DEFRAG, 1,
				 delete, &cached_state);

		__btrfs_releasepage(page, GFP_NOFS);
	पूर्ण

	ClearPageChecked(page);
	clear_page_extent_mapped(page);
पूर्ण

/*
 * btrfs_page_mkग_लिखो() is not allowed to change the file size as it माला_लो
 * called from a page fault handler when a page is first dirtied. Hence we must
 * be careful to check क्रम खातापूर्ण conditions here. We set the page up correctly
 * क्रम a written page which means we get ENOSPC checking when writing पूर्णांकo
 * holes and correct delalloc and unwritten extent mapping on fileप्रणालीs that
 * support these features.
 *
 * We are not allowed to take the i_mutex here so we have to play games to
 * protect against truncate races as the page could now be beyond खातापूर्ण.  Because
 * truncate_setsize() ग_लिखोs the inode size beक्रमe removing pages, once we have
 * the page lock we can determine safely अगर the page is beyond खातापूर्ण. If it is not
 * beyond खातापूर्ण, then the page is guaranteed safe against truncation until we
 * unlock the page.
 */
vm_fault_t btrfs_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा extent_changeset *data_reserved = शून्य;
	अचिन्हित दीर्घ zero_start;
	loff_t size;
	vm_fault_t ret;
	पूर्णांक ret2;
	पूर्णांक reserved = 0;
	u64 reserved_space;
	u64 page_start;
	u64 page_end;
	u64 end;

	reserved_space = PAGE_SIZE;

	sb_start_pagefault(inode->i_sb);
	page_start = page_offset(page);
	page_end = page_start + PAGE_SIZE - 1;
	end = page_end;

	/*
	 * Reserving delalloc space after obtaining the page lock can lead to
	 * deadlock. For example, अगर a dirty page is locked by this function
	 * and the call to btrfs_delalloc_reserve_space() ends up triggering
	 * dirty page ग_लिखो out, then the btrfs_ग_लिखोpage() function could
	 * end up रुकोing indefinitely to get a lock on the page currently
	 * being processed by btrfs_page_mkग_लिखो() function.
	 */
	ret2 = btrfs_delalloc_reserve_space(BTRFS_I(inode), &data_reserved,
					    page_start, reserved_space);
	अगर (!ret2) अणु
		ret2 = file_update_समय(vmf->vma->vm_file);
		reserved = 1;
	पूर्ण
	अगर (ret2) अणु
		ret = vmf_error(ret2);
		अगर (reserved)
			जाओ out;
		जाओ out_noreserve;
	पूर्ण

	ret = VM_FAULT_NOPAGE; /* make the VM retry the fault */
again:
	करोwn_पढ़ो(&BTRFS_I(inode)->i_mmap_lock);
	lock_page(page);
	size = i_size_पढ़ो(inode);

	अगर ((page->mapping != inode->i_mapping) ||
	    (page_start >= size)) अणु
		/* page got truncated out from underneath us */
		जाओ out_unlock;
	पूर्ण
	रुको_on_page_ग_लिखोback(page);

	lock_extent_bits(io_tree, page_start, page_end, &cached_state);
	ret2 = set_page_extent_mapped(page);
	अगर (ret2 < 0) अणु
		ret = vmf_error(ret2);
		unlock_extent_cached(io_tree, page_start, page_end, &cached_state);
		जाओ out_unlock;
	पूर्ण

	/*
	 * we can't set the delalloc bits अगर there are pending ordered
	 * extents.  Drop our locks and रुको क्रम them to finish
	 */
	ordered = btrfs_lookup_ordered_range(BTRFS_I(inode), page_start,
			PAGE_SIZE);
	अगर (ordered) अणु
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state);
		unlock_page(page);
		up_पढ़ो(&BTRFS_I(inode)->i_mmap_lock);
		btrfs_start_ordered_extent(ordered, 1);
		btrfs_put_ordered_extent(ordered);
		जाओ again;
	पूर्ण

	अगर (page->index == ((size - 1) >> PAGE_SHIFT)) अणु
		reserved_space = round_up(size - page_start,
					  fs_info->sectorsize);
		अगर (reserved_space < PAGE_SIZE) अणु
			end = page_start + reserved_space - 1;
			btrfs_delalloc_release_space(BTRFS_I(inode),
					data_reserved, page_start,
					PAGE_SIZE - reserved_space, true);
		पूर्ण
	पूर्ण

	/*
	 * page_mkग_लिखो माला_लो called when the page is firstly dirtied after it's
	 * faulted in, but ग_लिखो(2) could also dirty a page and set delalloc
	 * bits, thus in this हाल क्रम space account reason, we still need to
	 * clear any delalloc bits within this page range since we have to
	 * reserve data&meta space beक्रमe lock_page() (see above comments).
	 */
	clear_extent_bit(&BTRFS_I(inode)->io_tree, page_start, end,
			  EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING |
			  EXTENT_DEFRAG, 0, 0, &cached_state);

	ret2 = btrfs_set_extent_delalloc(BTRFS_I(inode), page_start, end, 0,
					&cached_state);
	अगर (ret2) अणु
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state);
		ret = VM_FAULT_SIGBUS;
		जाओ out_unlock;
	पूर्ण

	/* page is wholly or partially inside खातापूर्ण */
	अगर (page_start + PAGE_SIZE > size)
		zero_start = offset_in_page(size);
	अन्यथा
		zero_start = PAGE_SIZE;

	अगर (zero_start != PAGE_SIZE) अणु
		memzero_page(page, zero_start, PAGE_SIZE - zero_start);
		flush_dcache_page(page);
	पूर्ण
	ClearPageChecked(page);
	set_page_dirty(page);
	SetPageUptodate(page);

	btrfs_set_inode_last_sub_trans(BTRFS_I(inode));

	unlock_extent_cached(io_tree, page_start, page_end, &cached_state);
	up_पढ़ो(&BTRFS_I(inode)->i_mmap_lock);

	btrfs_delalloc_release_extents(BTRFS_I(inode), PAGE_SIZE);
	sb_end_pagefault(inode->i_sb);
	extent_changeset_मुक्त(data_reserved);
	वापस VM_FAULT_LOCKED;

out_unlock:
	unlock_page(page);
	up_पढ़ो(&BTRFS_I(inode)->i_mmap_lock);
out:
	btrfs_delalloc_release_extents(BTRFS_I(inode), PAGE_SIZE);
	btrfs_delalloc_release_space(BTRFS_I(inode), data_reserved, page_start,
				     reserved_space, (ret != 0));
out_noreserve:
	sb_end_pagefault(inode->i_sb);
	extent_changeset_मुक्त(data_reserved);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_truncate(काष्ठा inode *inode, bool skip_ग_लिखोback)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_block_rsv *rsv;
	पूर्णांक ret;
	काष्ठा btrfs_trans_handle *trans;
	u64 mask = fs_info->sectorsize - 1;
	u64 min_size = btrfs_calc_metadata_size(fs_info, 1);

	अगर (!skip_ग_लिखोback) अणु
		ret = btrfs_रुको_ordered_range(inode, inode->i_size & (~mask),
					       (u64)-1);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Yes ladies and gentlemen, this is indeed ugly.  We have a couple of
	 * things going on here:
	 *
	 * 1) We need to reserve space to update our inode.
	 *
	 * 2) We need to have something to cache all the space that is going to
	 * be मुक्त'd up by the truncate operation, but also have some slack
	 * space reserved in हाल it uses space during the truncate (thank you
	 * very much snapshotting).
	 *
	 * And we need these to be separate.  The fact is we can use a lot of
	 * space करोing the truncate, and we have no earthly idea how much space
	 * we will use, so we need the truncate reservation to be separate so it
	 * करोesn't end up using space reserved क्रम updating the inode.  We also
	 * need to be able to stop the transaction and start a new one, which
	 * means we need to be able to update the inode several बार, and we
	 * have no idea of knowing how many बार that will be, so we can't just
	 * reserve 1 item क्रम the entirety of the operation, so that has to be
	 * करोne separately as well.
	 *
	 * So that leaves us with
	 *
	 * 1) rsv - क्रम the truncate reservation, which we will steal from the
	 * transaction reservation.
	 * 2) fs_info->trans_block_rsv - this will have 1 items worth left क्रम
	 * updating the inode.
	 */
	rsv = btrfs_alloc_block_rsv(fs_info, BTRFS_BLOCK_RSV_TEMP);
	अगर (!rsv)
		वापस -ENOMEM;
	rsv->size = min_size;
	rsv->failfast = 1;

	/*
	 * 1 क्रम the truncate slack space
	 * 1 क्रम updating the inode.
	 */
	trans = btrfs_start_transaction(root, 2);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out;
	पूर्ण

	/* Migrate the slack space क्रम the truncate to our reserve */
	ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv, rsv,
				      min_size, false);
	BUG_ON(ret);

	/*
	 * So अगर we truncate and then ग_लिखो and fsync we normally would just
	 * ग_लिखो the extents that changed, which is a problem अगर we need to
	 * first truncate that entire inode.  So set this flag so we ग_लिखो out
	 * all of the extents in the inode to the sync log so we're completely
	 * safe.
	 */
	set_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &BTRFS_I(inode)->runसमय_flags);
	trans->block_rsv = rsv;

	जबतक (1) अणु
		ret = btrfs_truncate_inode_items(trans, root, BTRFS_I(inode),
						 inode->i_size,
						 BTRFS_EXTENT_DATA_KEY);
		trans->block_rsv = &fs_info->trans_block_rsv;
		अगर (ret != -ENOSPC && ret != -EAGAIN)
			अवरोध;

		ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
		अगर (ret)
			अवरोध;

		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty(fs_info);

		trans = btrfs_start_transaction(root, 2);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			trans = शून्य;
			अवरोध;
		पूर्ण

		btrfs_block_rsv_release(fs_info, rsv, -1, शून्य);
		ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv,
					      rsv, min_size, false);
		BUG_ON(ret);	/* shouldn't happen */
		trans->block_rsv = rsv;
	पूर्ण

	/*
	 * We can't call btrfs_truncate_block inside a trans handle as we could
	 * deadlock with मुक्तze, अगर we got NEED_TRUNCATE_BLOCK then we know
	 * we've truncated everything except the last little bit, and can करो
	 * btrfs_truncate_block and then update the disk_i_size.
	 */
	अगर (ret == NEED_TRUNCATE_BLOCK) अणु
		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty(fs_info);

		ret = btrfs_truncate_block(BTRFS_I(inode), inode->i_size, 0, 0);
		अगर (ret)
			जाओ out;
		trans = btrfs_start_transaction(root, 1);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			जाओ out;
		पूर्ण
		btrfs_inode_safe_disk_i_size_ग_लिखो(BTRFS_I(inode), 0);
	पूर्ण

	अगर (trans) अणु
		पूर्णांक ret2;

		trans->block_rsv = &fs_info->trans_block_rsv;
		ret2 = btrfs_update_inode(trans, root, BTRFS_I(inode));
		अगर (ret2 && !ret)
			ret = ret2;

		ret2 = btrfs_end_transaction(trans);
		अगर (ret2 && !ret)
			ret = ret2;
		btrfs_btree_balance_dirty(fs_info);
	पूर्ण
out:
	btrfs_मुक्त_block_rsv(fs_info, rsv);

	वापस ret;
पूर्ण

/*
 * create a new subvolume directory/inode (helper क्रम the ioctl).
 */
पूर्णांक btrfs_create_subvol_root(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *new_root,
			     काष्ठा btrfs_root *parent_root)
अणु
	काष्ठा inode *inode;
	पूर्णांक err;
	u64 index = 0;
	u64 ino;

	err = btrfs_get_मुक्त_objectid(new_root, &ino);
	अगर (err < 0)
		वापस err;

	inode = btrfs_new_inode(trans, new_root, शून्य, "..", 2, ino, ino,
				S_IFसूची | (~current_umask() & S_IRWXUGO),
				&index);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);
	inode->i_op = &btrfs_dir_inode_operations;
	inode->i_fop = &btrfs_dir_file_operations;

	set_nlink(inode, 1);
	btrfs_i_size_ग_लिखो(BTRFS_I(inode), 0);
	unlock_new_inode(inode);

	err = btrfs_subvol_inherit_props(trans, new_root, parent_root);
	अगर (err)
		btrfs_err(new_root->fs_info,
			  "error inheriting subvolume %llu properties: %d",
			  new_root->root_key.objectid, err);

	err = btrfs_update_inode(trans, new_root, BTRFS_I(inode));

	iput(inode);
	वापस err;
पूर्ण

काष्ठा inode *btrfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(sb);
	काष्ठा btrfs_inode *ei;
	काष्ठा inode *inode;

	ei = kmem_cache_alloc(btrfs_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;

	ei->root = शून्य;
	ei->generation = 0;
	ei->last_trans = 0;
	ei->last_sub_trans = 0;
	ei->logged_trans = 0;
	ei->delalloc_bytes = 0;
	ei->new_delalloc_bytes = 0;
	ei->defrag_bytes = 0;
	ei->disk_i_size = 0;
	ei->flags = 0;
	ei->csum_bytes = 0;
	ei->index_cnt = (u64)-1;
	ei->dir_index = 0;
	ei->last_unlink_trans = 0;
	ei->last_reflink_trans = 0;
	ei->last_log_commit = 0;

	spin_lock_init(&ei->lock);
	ei->outstanding_extents = 0;
	अगर (sb->s_magic != BTRFS_TEST_MAGIC)
		btrfs_init_metadata_block_rsv(fs_info, &ei->block_rsv,
					      BTRFS_BLOCK_RSV_DELALLOC);
	ei->runसमय_flags = 0;
	ei->prop_compress = BTRFS_COMPRESS_NONE;
	ei->defrag_compress = BTRFS_COMPRESS_NONE;

	ei->delayed_node = शून्य;

	ei->i_oसमय.tv_sec = 0;
	ei->i_oसमय.tv_nsec = 0;

	inode = &ei->vfs_inode;
	extent_map_tree_init(&ei->extent_tree);
	extent_io_tree_init(fs_info, &ei->io_tree, IO_TREE_INODE_IO, inode);
	extent_io_tree_init(fs_info, &ei->io_failure_tree,
			    IO_TREE_INODE_IO_FAILURE, inode);
	extent_io_tree_init(fs_info, &ei->file_extent_tree,
			    IO_TREE_INODE_खाता_EXTENT, inode);
	ei->io_tree.track_uptodate = true;
	ei->io_failure_tree.track_uptodate = true;
	atomic_set(&ei->sync_ग_लिखोrs, 0);
	mutex_init(&ei->log_mutex);
	btrfs_ordered_inode_tree_init(&ei->ordered_tree);
	INIT_LIST_HEAD(&ei->delalloc_inodes);
	INIT_LIST_HEAD(&ei->delayed_iput);
	RB_CLEAR_NODE(&ei->rb_node);
	init_rwsem(&ei->i_mmap_lock);

	वापस inode;
पूर्ण

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
व्योम btrfs_test_destroy_inode(काष्ठा inode *inode)
अणु
	btrfs_drop_extent_cache(BTRFS_I(inode), 0, (u64)-1, 0);
	kmem_cache_मुक्त(btrfs_inode_cachep, BTRFS_I(inode));
पूर्ण
#पूर्ण_अगर

व्योम btrfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(btrfs_inode_cachep, BTRFS_I(inode));
पूर्ण

व्योम btrfs_destroy_inode(काष्ठा inode *vfs_inode)
अणु
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा btrfs_inode *inode = BTRFS_I(vfs_inode);
	काष्ठा btrfs_root *root = inode->root;

	WARN_ON(!hlist_empty(&vfs_inode->i_dentry));
	WARN_ON(vfs_inode->i_data.nrpages);
	WARN_ON(inode->block_rsv.reserved);
	WARN_ON(inode->block_rsv.size);
	WARN_ON(inode->outstanding_extents);
	WARN_ON(inode->delalloc_bytes);
	WARN_ON(inode->new_delalloc_bytes);
	WARN_ON(inode->csum_bytes);
	WARN_ON(inode->defrag_bytes);

	/*
	 * This can happen where we create an inode, but somebody अन्यथा also
	 * created the same inode and we need to destroy the one we alपढ़ोy
	 * created.
	 */
	अगर (!root)
		वापस;

	जबतक (1) अणु
		ordered = btrfs_lookup_first_ordered_extent(inode, (u64)-1);
		अगर (!ordered)
			अवरोध;
		अन्यथा अणु
			btrfs_err(root->fs_info,
				  "found ordered extent %llu %llu on inode cleanup",
				  ordered->file_offset, ordered->num_bytes);
			btrfs_हटाओ_ordered_extent(inode, ordered);
			btrfs_put_ordered_extent(ordered);
			btrfs_put_ordered_extent(ordered);
		पूर्ण
	पूर्ण
	btrfs_qgroup_check_reserved_leak(inode);
	inode_tree_del(inode);
	btrfs_drop_extent_cache(inode, 0, (u64)-1, 0);
	btrfs_inode_clear_file_extent_range(inode, 0, (u64)-1);
	btrfs_put_root(inode->root);
पूर्ण

पूर्णांक btrfs_drop_inode(काष्ठा inode *inode)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;

	अगर (root == शून्य)
		वापस 1;

	/* the snap/subvol tree is on deleting */
	अगर (btrfs_root_refs(&root->root_item) == 0)
		वापस 1;
	अन्यथा
		वापस generic_drop_inode(inode);
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा btrfs_inode *ei = (काष्ठा btrfs_inode *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

व्योम __cold btrfs_destroy_cachep(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(btrfs_inode_cachep);
	kmem_cache_destroy(btrfs_trans_handle_cachep);
	kmem_cache_destroy(btrfs_path_cachep);
	kmem_cache_destroy(btrfs_मुक्त_space_cachep);
	kmem_cache_destroy(btrfs_मुक्त_space_biपंचांगap_cachep);
पूर्ण

पूर्णांक __init btrfs_init_cachep(व्योम)
अणु
	btrfs_inode_cachep = kmem_cache_create("btrfs_inode",
			माप(काष्ठा btrfs_inode), 0,
			SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD | SLAB_ACCOUNT,
			init_once);
	अगर (!btrfs_inode_cachep)
		जाओ fail;

	btrfs_trans_handle_cachep = kmem_cache_create("btrfs_trans_handle",
			माप(काष्ठा btrfs_trans_handle), 0,
			SLAB_TEMPORARY | SLAB_MEM_SPREAD, शून्य);
	अगर (!btrfs_trans_handle_cachep)
		जाओ fail;

	btrfs_path_cachep = kmem_cache_create("btrfs_path",
			माप(काष्ठा btrfs_path), 0,
			SLAB_MEM_SPREAD, शून्य);
	अगर (!btrfs_path_cachep)
		जाओ fail;

	btrfs_मुक्त_space_cachep = kmem_cache_create("btrfs_free_space",
			माप(काष्ठा btrfs_मुक्त_space), 0,
			SLAB_MEM_SPREAD, शून्य);
	अगर (!btrfs_मुक्त_space_cachep)
		जाओ fail;

	btrfs_मुक्त_space_biपंचांगap_cachep = kmem_cache_create("btrfs_free_space_bitmap",
							PAGE_SIZE, PAGE_SIZE,
							SLAB_MEM_SPREAD, शून्य);
	अगर (!btrfs_मुक्त_space_biपंचांगap_cachep)
		जाओ fail;

	वापस 0;
fail:
	btrfs_destroy_cachep();
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक btrfs_getattr(काष्ठा user_namespace *mnt_userns,
			 स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			 u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	u64 delalloc_bytes;
	u64 inode_bytes;
	काष्ठा inode *inode = d_inode(path->dentry);
	u32 blocksize = inode->i_sb->s_blocksize;
	u32 bi_flags = BTRFS_I(inode)->flags;

	stat->result_mask |= STATX_BTIME;
	stat->bसमय.tv_sec = BTRFS_I(inode)->i_oसमय.tv_sec;
	stat->bसमय.tv_nsec = BTRFS_I(inode)->i_oसमय.tv_nsec;
	अगर (bi_flags & BTRFS_INODE_APPEND)
		stat->attributes |= STATX_ATTR_APPEND;
	अगर (bi_flags & BTRFS_INODE_COMPRESS)
		stat->attributes |= STATX_ATTR_COMPRESSED;
	अगर (bi_flags & BTRFS_INODE_IMMUTABLE)
		stat->attributes |= STATX_ATTR_IMMUTABLE;
	अगर (bi_flags & BTRFS_INODE_NODUMP)
		stat->attributes |= STATX_ATTR_NODUMP;

	stat->attributes_mask |= (STATX_ATTR_APPEND |
				  STATX_ATTR_COMPRESSED |
				  STATX_ATTR_IMMUTABLE |
				  STATX_ATTR_NODUMP);

	generic_fillattr(&init_user_ns, inode, stat);
	stat->dev = BTRFS_I(inode)->root->anon_dev;

	spin_lock(&BTRFS_I(inode)->lock);
	delalloc_bytes = BTRFS_I(inode)->new_delalloc_bytes;
	inode_bytes = inode_get_bytes(inode);
	spin_unlock(&BTRFS_I(inode)->lock);
	stat->blocks = (ALIGN(inode_bytes, blocksize) +
			ALIGN(delalloc_bytes, blocksize)) >> 9;
	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_नाम_exchange(काष्ठा inode *old_dir,
			      काष्ठा dentry *old_dentry,
			      काष्ठा inode *new_dir,
			      काष्ठा dentry *new_dentry)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(old_dir->i_sb);
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = BTRFS_I(old_dir)->root;
	काष्ठा btrfs_root *dest = BTRFS_I(new_dir)->root;
	काष्ठा inode *new_inode = new_dentry->d_inode;
	काष्ठा inode *old_inode = old_dentry->d_inode;
	काष्ठा बारpec64 स_समय = current_समय(old_inode);
	u64 old_ino = btrfs_ino(BTRFS_I(old_inode));
	u64 new_ino = btrfs_ino(BTRFS_I(new_inode));
	u64 old_idx = 0;
	u64 new_idx = 0;
	पूर्णांक ret;
	पूर्णांक ret2;
	bool root_log_pinned = false;
	bool dest_log_pinned = false;
	bool need_पात = false;

	/* we only allow नाम subvolume link between subvolumes */
	अगर (old_ino != BTRFS_FIRST_FREE_OBJECTID && root != dest)
		वापस -EXDEV;

	/* बंद the race winकरोw with snapshot create/destroy ioctl */
	अगर (old_ino == BTRFS_FIRST_FREE_OBJECTID ||
	    new_ino == BTRFS_FIRST_FREE_OBJECTID)
		करोwn_पढ़ो(&fs_info->subvol_sem);

	/*
	 * We want to reserve the असलolute worst हाल amount of items.  So अगर
	 * both inodes are subvols and we need to unlink them then that would
	 * require 4 item modअगरications, but अगर they are both normal inodes it
	 * would require 5 item modअगरications, so we'll assume their normal
	 * inodes.  So 5 * 2 is 10, plus 2 क्रम the new links, so 12 total items
	 * should cover the worst हाल number of items we'll modअगरy.
	 */
	trans = btrfs_start_transaction(root, 12);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out_notrans;
	पूर्ण

	अगर (dest != root) अणु
		ret = btrfs_record_root_in_trans(trans, dest);
		अगर (ret)
			जाओ out_fail;
	पूर्ण

	/*
	 * We need to find a मुक्त sequence number both in the source and
	 * in the destination directory क्रम the exchange.
	 */
	ret = btrfs_set_inode_index(BTRFS_I(new_dir), &old_idx);
	अगर (ret)
		जाओ out_fail;
	ret = btrfs_set_inode_index(BTRFS_I(old_dir), &new_idx);
	अगर (ret)
		जाओ out_fail;

	BTRFS_I(old_inode)->dir_index = 0ULL;
	BTRFS_I(new_inode)->dir_index = 0ULL;

	/* Reference क्रम the source. */
	अगर (old_ino == BTRFS_FIRST_FREE_OBJECTID) अणु
		/* क्रमce full log commit अगर subvolume involved. */
		btrfs_set_log_full_commit(trans);
	पूर्ण अन्यथा अणु
		btrfs_pin_log_trans(root);
		root_log_pinned = true;
		ret = btrfs_insert_inode_ref(trans, dest,
					     new_dentry->d_name.name,
					     new_dentry->d_name.len,
					     old_ino,
					     btrfs_ino(BTRFS_I(new_dir)),
					     old_idx);
		अगर (ret)
			जाओ out_fail;
		need_पात = true;
	पूर्ण

	/* And now क्रम the dest. */
	अगर (new_ino == BTRFS_FIRST_FREE_OBJECTID) अणु
		/* क्रमce full log commit अगर subvolume involved. */
		btrfs_set_log_full_commit(trans);
	पूर्ण अन्यथा अणु
		btrfs_pin_log_trans(dest);
		dest_log_pinned = true;
		ret = btrfs_insert_inode_ref(trans, root,
					     old_dentry->d_name.name,
					     old_dentry->d_name.len,
					     new_ino,
					     btrfs_ino(BTRFS_I(old_dir)),
					     new_idx);
		अगर (ret) अणु
			अगर (need_पात)
				btrfs_पात_transaction(trans, ret);
			जाओ out_fail;
		पूर्ण
	पूर्ण

	/* Update inode version and स_समय/mसमय. */
	inode_inc_iversion(old_dir);
	inode_inc_iversion(new_dir);
	inode_inc_iversion(old_inode);
	inode_inc_iversion(new_inode);
	old_dir->i_स_समय = old_dir->i_mसमय = स_समय;
	new_dir->i_स_समय = new_dir->i_mसमय = स_समय;
	old_inode->i_स_समय = स_समय;
	new_inode->i_स_समय = स_समय;

	अगर (old_dentry->d_parent != new_dentry->d_parent) अणु
		btrfs_record_unlink_dir(trans, BTRFS_I(old_dir),
				BTRFS_I(old_inode), 1);
		btrfs_record_unlink_dir(trans, BTRFS_I(new_dir),
				BTRFS_I(new_inode), 1);
	पूर्ण

	/* src is a subvolume */
	अगर (old_ino == BTRFS_FIRST_FREE_OBJECTID) अणु
		ret = btrfs_unlink_subvol(trans, old_dir, old_dentry);
	पूर्ण अन्यथा अणु /* src is an inode */
		ret = __btrfs_unlink_inode(trans, root, BTRFS_I(old_dir),
					   BTRFS_I(old_dentry->d_inode),
					   old_dentry->d_name.name,
					   old_dentry->d_name.len);
		अगर (!ret)
			ret = btrfs_update_inode(trans, root, BTRFS_I(old_inode));
	पूर्ण
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_fail;
	पूर्ण

	/* dest is a subvolume */
	अगर (new_ino == BTRFS_FIRST_FREE_OBJECTID) अणु
		ret = btrfs_unlink_subvol(trans, new_dir, new_dentry);
	पूर्ण अन्यथा अणु /* dest is an inode */
		ret = __btrfs_unlink_inode(trans, dest, BTRFS_I(new_dir),
					   BTRFS_I(new_dentry->d_inode),
					   new_dentry->d_name.name,
					   new_dentry->d_name.len);
		अगर (!ret)
			ret = btrfs_update_inode(trans, dest, BTRFS_I(new_inode));
	पूर्ण
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_fail;
	पूर्ण

	ret = btrfs_add_link(trans, BTRFS_I(new_dir), BTRFS_I(old_inode),
			     new_dentry->d_name.name,
			     new_dentry->d_name.len, 0, old_idx);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_fail;
	पूर्ण

	ret = btrfs_add_link(trans, BTRFS_I(old_dir), BTRFS_I(new_inode),
			     old_dentry->d_name.name,
			     old_dentry->d_name.len, 0, new_idx);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_fail;
	पूर्ण

	अगर (old_inode->i_nlink == 1)
		BTRFS_I(old_inode)->dir_index = old_idx;
	अगर (new_inode->i_nlink == 1)
		BTRFS_I(new_inode)->dir_index = new_idx;

	अगर (root_log_pinned) अणु
		btrfs_log_new_name(trans, BTRFS_I(old_inode), BTRFS_I(old_dir),
				   new_dentry->d_parent);
		btrfs_end_log_trans(root);
		root_log_pinned = false;
	पूर्ण
	अगर (dest_log_pinned) अणु
		btrfs_log_new_name(trans, BTRFS_I(new_inode), BTRFS_I(new_dir),
				   old_dentry->d_parent);
		btrfs_end_log_trans(dest);
		dest_log_pinned = false;
	पूर्ण
out_fail:
	/*
	 * If we have pinned a log and an error happened, we unpin tasks
	 * trying to sync the log and क्रमce them to fallback to a transaction
	 * commit अगर the log currently contains any of the inodes involved in
	 * this नाम operation (to ensure we करो not persist a log with an
	 * inconsistent state क्रम any of these inodes or leading to any
	 * inconsistencies when replayed). If the transaction was पातed, the
	 * पातion reason is propagated to userspace when attempting to commit
	 * the transaction. If the log करोes not contain any of these inodes, we
	 * allow the tasks to sync it.
	 */
	अगर (ret && (root_log_pinned || dest_log_pinned)) अणु
		अगर (btrfs_inode_in_log(BTRFS_I(old_dir), fs_info->generation) ||
		    btrfs_inode_in_log(BTRFS_I(new_dir), fs_info->generation) ||
		    btrfs_inode_in_log(BTRFS_I(old_inode), fs_info->generation) ||
		    (new_inode &&
		     btrfs_inode_in_log(BTRFS_I(new_inode), fs_info->generation)))
			btrfs_set_log_full_commit(trans);

		अगर (root_log_pinned) अणु
			btrfs_end_log_trans(root);
			root_log_pinned = false;
		पूर्ण
		अगर (dest_log_pinned) अणु
			btrfs_end_log_trans(dest);
			dest_log_pinned = false;
		पूर्ण
	पूर्ण
	ret2 = btrfs_end_transaction(trans);
	ret = ret ? ret : ret2;
out_notrans:
	अगर (new_ino == BTRFS_FIRST_FREE_OBJECTID ||
	    old_ino == BTRFS_FIRST_FREE_OBJECTID)
		up_पढ़ो(&fs_info->subvol_sem);

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_whiteout_क्रम_नाम(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_root *root,
				     काष्ठा inode *dir,
				     काष्ठा dentry *dentry)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode;
	u64 objectid;
	u64 index;

	ret = btrfs_get_मुक्त_objectid(root, &objectid);
	अगर (ret)
		वापस ret;

	inode = btrfs_new_inode(trans, root, dir,
				dentry->d_name.name,
				dentry->d_name.len,
				btrfs_ino(BTRFS_I(dir)),
				objectid,
				S_IFCHR | WHITEOUT_MODE,
				&index);

	अगर (IS_ERR(inode)) अणु
		ret = PTR_ERR(inode);
		वापस ret;
	पूर्ण

	inode->i_op = &btrfs_special_inode_operations;
	init_special_inode(inode, inode->i_mode,
		WHITEOUT_DEV);

	ret = btrfs_init_inode_security(trans, inode, dir,
				&dentry->d_name);
	अगर (ret)
		जाओ out;

	ret = btrfs_add_nondir(trans, BTRFS_I(dir), dentry,
				BTRFS_I(inode), 0, index);
	अगर (ret)
		जाओ out;

	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
out:
	unlock_new_inode(inode);
	अगर (ret)
		inode_dec_link_count(inode);
	iput(inode);

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_नाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			   काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(old_dir->i_sb);
	काष्ठा btrfs_trans_handle *trans;
	अचिन्हित पूर्णांक trans_num_items;
	काष्ठा btrfs_root *root = BTRFS_I(old_dir)->root;
	काष्ठा btrfs_root *dest = BTRFS_I(new_dir)->root;
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा inode *old_inode = d_inode(old_dentry);
	u64 index = 0;
	पूर्णांक ret;
	पूर्णांक ret2;
	u64 old_ino = btrfs_ino(BTRFS_I(old_inode));
	bool log_pinned = false;

	अगर (btrfs_ino(BTRFS_I(new_dir)) == BTRFS_EMPTY_SUBVOL_सूची_OBJECTID)
		वापस -EPERM;

	/* we only allow नाम subvolume link between subvolumes */
	अगर (old_ino != BTRFS_FIRST_FREE_OBJECTID && root != dest)
		वापस -EXDEV;

	अगर (old_ino == BTRFS_EMPTY_SUBVOL_सूची_OBJECTID ||
	    (new_inode && btrfs_ino(BTRFS_I(new_inode)) == BTRFS_FIRST_FREE_OBJECTID))
		वापस -ENOTEMPTY;

	अगर (S_ISसूची(old_inode->i_mode) && new_inode &&
	    new_inode->i_size > BTRFS_EMPTY_सूची_SIZE)
		वापस -ENOTEMPTY;


	/* check क्रम collisions, even अगर the  name isn't there */
	ret = btrfs_check_dir_item_collision(dest, new_dir->i_ino,
			     new_dentry->d_name.name,
			     new_dentry->d_name.len);

	अगर (ret) अणु
		अगर (ret == -EEXIST) अणु
			/* we shouldn't get
			 * eexist without a new_inode */
			अगर (WARN_ON(!new_inode)) अणु
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* maybe -EOVERFLOW */
			वापस ret;
		पूर्ण
	पूर्ण
	ret = 0;

	/*
	 * we're using नाम to replace one file with another.  Start IO on it
	 * now so  we करोn't add too much work to the end of the transaction
	 */
	अगर (new_inode && S_ISREG(old_inode->i_mode) && new_inode->i_size)
		filemap_flush(old_inode->i_mapping);

	/* बंद the racy winकरोw with snapshot create/destroy ioctl */
	अगर (old_ino == BTRFS_FIRST_FREE_OBJECTID)
		करोwn_पढ़ो(&fs_info->subvol_sem);
	/*
	 * We want to reserve the असलolute worst हाल amount of items.  So अगर
	 * both inodes are subvols and we need to unlink them then that would
	 * require 4 item modअगरications, but अगर they are both normal inodes it
	 * would require 5 item modअगरications, so we'll assume they are normal
	 * inodes.  So 5 * 2 is 10, plus 1 क्रम the new link, so 11 total items
	 * should cover the worst हाल number of items we'll modअगरy.
	 * If our नाम has the whiteout flag, we need more 5 units क्रम the
	 * new inode (1 inode item, 1 inode ref, 2 dir items and 1 xattr item
	 * when selinux is enabled).
	 */
	trans_num_items = 11;
	अगर (flags & RENAME_WHITEOUT)
		trans_num_items += 5;
	trans = btrfs_start_transaction(root, trans_num_items);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out_notrans;
	पूर्ण

	अगर (dest != root) अणु
		ret = btrfs_record_root_in_trans(trans, dest);
		अगर (ret)
			जाओ out_fail;
	पूर्ण

	ret = btrfs_set_inode_index(BTRFS_I(new_dir), &index);
	अगर (ret)
		जाओ out_fail;

	BTRFS_I(old_inode)->dir_index = 0ULL;
	अगर (unlikely(old_ino == BTRFS_FIRST_FREE_OBJECTID)) अणु
		/* क्रमce full log commit अगर subvolume involved. */
		btrfs_set_log_full_commit(trans);
	पूर्ण अन्यथा अणु
		btrfs_pin_log_trans(root);
		log_pinned = true;
		ret = btrfs_insert_inode_ref(trans, dest,
					     new_dentry->d_name.name,
					     new_dentry->d_name.len,
					     old_ino,
					     btrfs_ino(BTRFS_I(new_dir)), index);
		अगर (ret)
			जाओ out_fail;
	पूर्ण

	inode_inc_iversion(old_dir);
	inode_inc_iversion(new_dir);
	inode_inc_iversion(old_inode);
	old_dir->i_स_समय = old_dir->i_mसमय =
	new_dir->i_स_समय = new_dir->i_mसमय =
	old_inode->i_स_समय = current_समय(old_dir);

	अगर (old_dentry->d_parent != new_dentry->d_parent)
		btrfs_record_unlink_dir(trans, BTRFS_I(old_dir),
				BTRFS_I(old_inode), 1);

	अगर (unlikely(old_ino == BTRFS_FIRST_FREE_OBJECTID)) अणु
		ret = btrfs_unlink_subvol(trans, old_dir, old_dentry);
	पूर्ण अन्यथा अणु
		ret = __btrfs_unlink_inode(trans, root, BTRFS_I(old_dir),
					BTRFS_I(d_inode(old_dentry)),
					old_dentry->d_name.name,
					old_dentry->d_name.len);
		अगर (!ret)
			ret = btrfs_update_inode(trans, root, BTRFS_I(old_inode));
	पूर्ण
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_fail;
	पूर्ण

	अगर (new_inode) अणु
		inode_inc_iversion(new_inode);
		new_inode->i_स_समय = current_समय(new_inode);
		अगर (unlikely(btrfs_ino(BTRFS_I(new_inode)) ==
			     BTRFS_EMPTY_SUBVOL_सूची_OBJECTID)) अणु
			ret = btrfs_unlink_subvol(trans, new_dir, new_dentry);
			BUG_ON(new_inode->i_nlink == 0);
		पूर्ण अन्यथा अणु
			ret = btrfs_unlink_inode(trans, dest, BTRFS_I(new_dir),
						 BTRFS_I(d_inode(new_dentry)),
						 new_dentry->d_name.name,
						 new_dentry->d_name.len);
		पूर्ण
		अगर (!ret && new_inode->i_nlink == 0)
			ret = btrfs_orphan_add(trans,
					BTRFS_I(d_inode(new_dentry)));
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out_fail;
		पूर्ण
	पूर्ण

	ret = btrfs_add_link(trans, BTRFS_I(new_dir), BTRFS_I(old_inode),
			     new_dentry->d_name.name,
			     new_dentry->d_name.len, 0, index);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out_fail;
	पूर्ण

	अगर (old_inode->i_nlink == 1)
		BTRFS_I(old_inode)->dir_index = index;

	अगर (log_pinned) अणु
		btrfs_log_new_name(trans, BTRFS_I(old_inode), BTRFS_I(old_dir),
				   new_dentry->d_parent);
		btrfs_end_log_trans(root);
		log_pinned = false;
	पूर्ण

	अगर (flags & RENAME_WHITEOUT) अणु
		ret = btrfs_whiteout_क्रम_नाम(trans, root, old_dir,
						old_dentry);

		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out_fail;
		पूर्ण
	पूर्ण
out_fail:
	/*
	 * If we have pinned the log and an error happened, we unpin tasks
	 * trying to sync the log and क्रमce them to fallback to a transaction
	 * commit अगर the log currently contains any of the inodes involved in
	 * this नाम operation (to ensure we करो not persist a log with an
	 * inconsistent state क्रम any of these inodes or leading to any
	 * inconsistencies when replayed). If the transaction was पातed, the
	 * पातion reason is propagated to userspace when attempting to commit
	 * the transaction. If the log करोes not contain any of these inodes, we
	 * allow the tasks to sync it.
	 */
	अगर (ret && log_pinned) अणु
		अगर (btrfs_inode_in_log(BTRFS_I(old_dir), fs_info->generation) ||
		    btrfs_inode_in_log(BTRFS_I(new_dir), fs_info->generation) ||
		    btrfs_inode_in_log(BTRFS_I(old_inode), fs_info->generation) ||
		    (new_inode &&
		     btrfs_inode_in_log(BTRFS_I(new_inode), fs_info->generation)))
			btrfs_set_log_full_commit(trans);

		btrfs_end_log_trans(root);
		log_pinned = false;
	पूर्ण
	ret2 = btrfs_end_transaction(trans);
	ret = ret ? ret : ret2;
out_notrans:
	अगर (old_ino == BTRFS_FIRST_FREE_OBJECTID)
		up_पढ़ो(&fs_info->subvol_sem);

	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_नाम2(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
			 काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
			 काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE | RENAME_WHITEOUT))
		वापस -EINVAL;

	अगर (flags & RENAME_EXCHANGE)
		वापस btrfs_नाम_exchange(old_dir, old_dentry, new_dir,
					  new_dentry);

	वापस btrfs_नाम(old_dir, old_dentry, new_dir, new_dentry, flags);
पूर्ण

काष्ठा btrfs_delalloc_work अणु
	काष्ठा inode *inode;
	काष्ठा completion completion;
	काष्ठा list_head list;
	काष्ठा btrfs_work work;
पूर्ण;

अटल व्योम btrfs_run_delalloc_work(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_delalloc_work *delalloc_work;
	काष्ठा inode *inode;

	delalloc_work = container_of(work, काष्ठा btrfs_delalloc_work,
				     work);
	inode = delalloc_work->inode;
	filemap_flush(inode->i_mapping);
	अगर (test_bit(BTRFS_INODE_HAS_ASYNC_EXTENT,
				&BTRFS_I(inode)->runसमय_flags))
		filemap_flush(inode->i_mapping);

	iput(inode);
	complete(&delalloc_work->completion);
पूर्ण

अटल काष्ठा btrfs_delalloc_work *btrfs_alloc_delalloc_work(काष्ठा inode *inode)
अणु
	काष्ठा btrfs_delalloc_work *work;

	work = kदो_स्मृति(माप(*work), GFP_NOFS);
	अगर (!work)
		वापस शून्य;

	init_completion(&work->completion);
	INIT_LIST_HEAD(&work->list);
	work->inode = inode;
	btrfs_init_work(&work->work, btrfs_run_delalloc_work, शून्य, शून्य);

	वापस work;
पूर्ण

/*
 * some fairly slow code that needs optimization. This walks the list
 * of all the inodes with pending delalloc and क्रमces them to disk.
 */
अटल पूर्णांक start_delalloc_inodes(काष्ठा btrfs_root *root,
				 काष्ठा ग_लिखोback_control *wbc, bool snapshot,
				 bool in_reclaim_context)
अणु
	काष्ठा btrfs_inode *binode;
	काष्ठा inode *inode;
	काष्ठा btrfs_delalloc_work *work, *next;
	काष्ठा list_head works;
	काष्ठा list_head splice;
	पूर्णांक ret = 0;
	bool full_flush = wbc->nr_to_ग_लिखो == दीर्घ_उच्च;

	INIT_LIST_HEAD(&works);
	INIT_LIST_HEAD(&splice);

	mutex_lock(&root->delalloc_mutex);
	spin_lock(&root->delalloc_lock);
	list_splice_init(&root->delalloc_inodes, &splice);
	जबतक (!list_empty(&splice)) अणु
		binode = list_entry(splice.next, काष्ठा btrfs_inode,
				    delalloc_inodes);

		list_move_tail(&binode->delalloc_inodes,
			       &root->delalloc_inodes);

		अगर (in_reclaim_context &&
		    test_bit(BTRFS_INODE_NO_DELALLOC_FLUSH, &binode->runसमय_flags))
			जारी;

		inode = igrab(&binode->vfs_inode);
		अगर (!inode) अणु
			cond_resched_lock(&root->delalloc_lock);
			जारी;
		पूर्ण
		spin_unlock(&root->delalloc_lock);

		अगर (snapshot)
			set_bit(BTRFS_INODE_SNAPSHOT_FLUSH,
				&binode->runसमय_flags);
		अगर (full_flush) अणु
			work = btrfs_alloc_delalloc_work(inode);
			अगर (!work) अणु
				iput(inode);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			list_add_tail(&work->list, &works);
			btrfs_queue_work(root->fs_info->flush_workers,
					 &work->work);
		पूर्ण अन्यथा अणु
			ret = sync_inode(inode, wbc);
			अगर (!ret &&
			    test_bit(BTRFS_INODE_HAS_ASYNC_EXTENT,
				     &BTRFS_I(inode)->runसमय_flags))
				ret = sync_inode(inode, wbc);
			btrfs_add_delayed_iput(inode);
			अगर (ret || wbc->nr_to_ग_लिखो <= 0)
				जाओ out;
		पूर्ण
		cond_resched();
		spin_lock(&root->delalloc_lock);
	पूर्ण
	spin_unlock(&root->delalloc_lock);

out:
	list_क्रम_each_entry_safe(work, next, &works, list) अणु
		list_del_init(&work->list);
		रुको_क्रम_completion(&work->completion);
		kमुक्त(work);
	पूर्ण

	अगर (!list_empty(&splice)) अणु
		spin_lock(&root->delalloc_lock);
		list_splice_tail(&splice, &root->delalloc_inodes);
		spin_unlock(&root->delalloc_lock);
	पूर्ण
	mutex_unlock(&root->delalloc_mutex);
	वापस ret;
पूर्ण

पूर्णांक btrfs_start_delalloc_snapshot(काष्ठा btrfs_root *root, bool in_reclaim_context)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.nr_to_ग_लिखो = दीर्घ_उच्च,
		.sync_mode = WB_SYNC_NONE,
		.range_start = 0,
		.range_end = Lदीर्घ_उच्च,
	पूर्ण;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state))
		वापस -EROFS;

	वापस start_delalloc_inodes(root, &wbc, true, in_reclaim_context);
पूर्ण

पूर्णांक btrfs_start_delalloc_roots(काष्ठा btrfs_fs_info *fs_info, दीर्घ nr,
			       bool in_reclaim_context)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.nr_to_ग_लिखो = nr,
		.sync_mode = WB_SYNC_NONE,
		.range_start = 0,
		.range_end = Lदीर्घ_उच्च,
	पूर्ण;
	काष्ठा btrfs_root *root;
	काष्ठा list_head splice;
	पूर्णांक ret;

	अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state))
		वापस -EROFS;

	INIT_LIST_HEAD(&splice);

	mutex_lock(&fs_info->delalloc_root_mutex);
	spin_lock(&fs_info->delalloc_root_lock);
	list_splice_init(&fs_info->delalloc_roots, &splice);
	जबतक (!list_empty(&splice)) अणु
		/*
		 * Reset nr_to_ग_लिखो here so we know that we're करोing a full
		 * flush.
		 */
		अगर (nr == दीर्घ_उच्च)
			wbc.nr_to_ग_लिखो = दीर्घ_उच्च;

		root = list_first_entry(&splice, काष्ठा btrfs_root,
					delalloc_root);
		root = btrfs_grab_root(root);
		BUG_ON(!root);
		list_move_tail(&root->delalloc_root,
			       &fs_info->delalloc_roots);
		spin_unlock(&fs_info->delalloc_root_lock);

		ret = start_delalloc_inodes(root, &wbc, false, in_reclaim_context);
		btrfs_put_root(root);
		अगर (ret < 0 || wbc.nr_to_ग_लिखो <= 0)
			जाओ out;
		spin_lock(&fs_info->delalloc_root_lock);
	पूर्ण
	spin_unlock(&fs_info->delalloc_root_lock);

	ret = 0;
out:
	अगर (!list_empty(&splice)) अणु
		spin_lock(&fs_info->delalloc_root_lock);
		list_splice_tail(&splice, &fs_info->delalloc_roots);
		spin_unlock(&fs_info->delalloc_root_lock);
	पूर्ण
	mutex_unlock(&fs_info->delalloc_root_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा inode *inode = शून्य;
	पूर्णांक err;
	u64 objectid;
	u64 index = 0;
	पूर्णांक name_len;
	पूर्णांक datasize;
	अचिन्हित दीर्घ ptr;
	काष्ठा btrfs_file_extent_item *ei;
	काष्ठा extent_buffer *leaf;

	name_len = म_माप(symname);
	अगर (name_len > BTRFS_MAX_INLINE_DATA_SIZE(fs_info))
		वापस -ENAMETOOLONG;

	/*
	 * 2 items क्रम inode item and ref
	 * 2 items क्रम dir items
	 * 1 item क्रम updating parent inode item
	 * 1 item क्रम the अंतरभूत extent item
	 * 1 item क्रम xattr अगर selinux is on
	 */
	trans = btrfs_start_transaction(root, 7);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	err = btrfs_get_मुक्त_objectid(root, &objectid);
	अगर (err)
		जाओ out_unlock;

	inode = btrfs_new_inode(trans, root, dir, dentry->d_name.name,
				dentry->d_name.len, btrfs_ino(BTRFS_I(dir)),
				objectid, S_IFLNK|S_IRWXUGO, &index);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		inode = शून्य;
		जाओ out_unlock;
	पूर्ण

	/*
	* If the active LSM wants to access the inode during
	* d_instantiate it needs these. Smack checks to see
	* अगर the fileप्रणाली supports xattrs by looking at the
	* ops vector.
	*/
	inode->i_fop = &btrfs_file_operations;
	inode->i_op = &btrfs_file_inode_operations;
	inode->i_mapping->a_ops = &btrfs_aops;

	err = btrfs_init_inode_security(trans, inode, dir, &dentry->d_name);
	अगर (err)
		जाओ out_unlock;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण
	key.objectid = btrfs_ino(BTRFS_I(inode));
	key.offset = 0;
	key.type = BTRFS_EXTENT_DATA_KEY;
	datasize = btrfs_file_extent_calc_अंतरभूत_size(name_len);
	err = btrfs_insert_empty_item(trans, root, path, &key,
				      datasize);
	अगर (err) अणु
		btrfs_मुक्त_path(path);
		जाओ out_unlock;
	पूर्ण
	leaf = path->nodes[0];
	ei = btrfs_item_ptr(leaf, path->slots[0],
			    काष्ठा btrfs_file_extent_item);
	btrfs_set_file_extent_generation(leaf, ei, trans->transid);
	btrfs_set_file_extent_type(leaf, ei,
				   BTRFS_खाता_EXTENT_INLINE);
	btrfs_set_file_extent_encryption(leaf, ei, 0);
	btrfs_set_file_extent_compression(leaf, ei, 0);
	btrfs_set_file_extent_other_encoding(leaf, ei, 0);
	btrfs_set_file_extent_ram_bytes(leaf, ei, name_len);

	ptr = btrfs_file_extent_अंतरभूत_start(ei);
	ग_लिखो_extent_buffer(leaf, symname, ptr, name_len);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_मुक्त_path(path);

	inode->i_op = &btrfs_symlink_inode_operations;
	inode_nohighmem(inode);
	inode_set_bytes(inode, name_len);
	btrfs_i_size_ग_लिखो(BTRFS_I(inode), name_len);
	err = btrfs_update_inode(trans, root, BTRFS_I(inode));
	/*
	 * Last step, add directory indexes क्रम our symlink inode. This is the
	 * last step to aव्योम extra cleanup of these indexes अगर an error happens
	 * अन्यथाwhere above.
	 */
	अगर (!err)
		err = btrfs_add_nondir(trans, BTRFS_I(dir), dentry,
				BTRFS_I(inode), 0, index);
	अगर (err)
		जाओ out_unlock;

	d_instantiate_new(dentry, inode);

out_unlock:
	btrfs_end_transaction(trans);
	अगर (err && inode) अणु
		inode_dec_link_count(inode);
		discard_new_inode(inode);
	पूर्ण
	btrfs_btree_balance_dirty(fs_info);
	वापस err;
पूर्ण

अटल काष्ठा btrfs_trans_handle *insert_pपुनः_स्मृति_file_extent(
				       काष्ठा btrfs_trans_handle *trans_in,
				       काष्ठा btrfs_inode *inode,
				       काष्ठा btrfs_key *ins,
				       u64 file_offset)
अणु
	काष्ठा btrfs_file_extent_item stack_fi;
	काष्ठा btrfs_replace_extent_info extent_info;
	काष्ठा btrfs_trans_handle *trans = trans_in;
	काष्ठा btrfs_path *path;
	u64 start = ins->objectid;
	u64 len = ins->offset;
	पूर्णांक qgroup_released;
	पूर्णांक ret;

	स_रखो(&stack_fi, 0, माप(stack_fi));

	btrfs_set_stack_file_extent_type(&stack_fi, BTRFS_खाता_EXTENT_PREALLOC);
	btrfs_set_stack_file_extent_disk_bytenr(&stack_fi, start);
	btrfs_set_stack_file_extent_disk_num_bytes(&stack_fi, len);
	btrfs_set_stack_file_extent_num_bytes(&stack_fi, len);
	btrfs_set_stack_file_extent_ram_bytes(&stack_fi, len);
	btrfs_set_stack_file_extent_compression(&stack_fi, BTRFS_COMPRESS_NONE);
	/* Encryption and other encoding is reserved and all 0 */

	qgroup_released = btrfs_qgroup_release_data(inode, file_offset, len);
	अगर (qgroup_released < 0)
		वापस ERR_PTR(qgroup_released);

	अगर (trans) अणु
		ret = insert_reserved_file_extent(trans, inode,
						  file_offset, &stack_fi,
						  true, qgroup_released);
		अगर (ret)
			जाओ मुक्त_qgroup;
		वापस trans;
	पूर्ण

	extent_info.disk_offset = start;
	extent_info.disk_len = len;
	extent_info.data_offset = 0;
	extent_info.data_len = len;
	extent_info.file_offset = file_offset;
	extent_info.extent_buf = (अक्षर *)&stack_fi;
	extent_info.is_new_extent = true;
	extent_info.qgroup_reserved = qgroup_released;
	extent_info.insertions = 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ मुक्त_qgroup;
	पूर्ण

	ret = btrfs_replace_file_extents(inode, path, file_offset,
				     file_offset + len - 1, &extent_info,
				     &trans);
	btrfs_मुक्त_path(path);
	अगर (ret)
		जाओ मुक्त_qgroup;
	वापस trans;

मुक्त_qgroup:
	/*
	 * We have released qgroup data range at the beginning of the function,
	 * and normally qgroup_released bytes will be मुक्तd when committing
	 * transaction.
	 * But अगर we error out early, we have to मुक्त what we have released
	 * or we leak qgroup data reservation.
	 */
	btrfs_qgroup_मुक्त_refroot(inode->root->fs_info,
			inode->root->root_key.objectid, qgroup_released,
			BTRFS_QGROUP_RSV_DATA);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक __btrfs_pपुनः_स्मृति_file_range(काष्ठा inode *inode, पूर्णांक mode,
				       u64 start, u64 num_bytes, u64 min_size,
				       loff_t actual_len, u64 *alloc_hपूर्णांक,
				       काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा extent_map_tree *em_tree = &BTRFS_I(inode)->extent_tree;
	काष्ठा extent_map *em;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_key ins;
	u64 cur_offset = start;
	u64 clear_offset = start;
	u64 i_size;
	u64 cur_bytes;
	u64 last_alloc = (u64)-1;
	पूर्णांक ret = 0;
	bool own_trans = true;
	u64 end = start + num_bytes - 1;

	अगर (trans)
		own_trans = false;
	जबतक (num_bytes > 0) अणु
		cur_bytes = min_t(u64, num_bytes, SZ_256M);
		cur_bytes = max(cur_bytes, min_size);
		/*
		 * If we are severely fragmented we could end up with really
		 * small allocations, so अगर the allocator is वापसing small
		 * chunks lets make its job easier by only searching क्रम those
		 * sized chunks.
		 */
		cur_bytes = min(cur_bytes, last_alloc);
		ret = btrfs_reserve_extent(root, cur_bytes, cur_bytes,
				min_size, 0, *alloc_hपूर्णांक, &ins, 1, 0);
		अगर (ret)
			अवरोध;

		/*
		 * We've reserved this space, and thus converted it from
		 * ->bytes_may_use to ->bytes_reserved.  Any error that happens
		 * from here on out we will only need to clear our reservation
		 * क्रम the reमुख्यing unreserved area, so advance our
		 * clear_offset by our extent size.
		 */
		clear_offset += ins.offset;

		last_alloc = ins.offset;
		trans = insert_pपुनः_स्मृति_file_extent(trans, BTRFS_I(inode),
						    &ins, cur_offset);
		/*
		 * Now that we inserted the pपुनः_स्मृति extent we can finally
		 * decrement the number of reservations in the block group.
		 * If we did it beक्रमe, we could race with relocation and have
		 * relocation miss the reserved extent, making it fail later.
		 */
		btrfs_dec_block_group_reservations(fs_info, ins.objectid);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			btrfs_मुक्त_reserved_extent(fs_info, ins.objectid,
						   ins.offset, 0);
			अवरोध;
		पूर्ण

		btrfs_drop_extent_cache(BTRFS_I(inode), cur_offset,
					cur_offset + ins.offset -1, 0);

		em = alloc_extent_map();
		अगर (!em) अणु
			set_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
				&BTRFS_I(inode)->runसमय_flags);
			जाओ next;
		पूर्ण

		em->start = cur_offset;
		em->orig_start = cur_offset;
		em->len = ins.offset;
		em->block_start = ins.objectid;
		em->block_len = ins.offset;
		em->orig_block_len = ins.offset;
		em->ram_bytes = ins.offset;
		set_bit(EXTENT_FLAG_PREALLOC, &em->flags);
		em->generation = trans->transid;

		जबतक (1) अणु
			ग_लिखो_lock(&em_tree->lock);
			ret = add_extent_mapping(em_tree, em, 1);
			ग_लिखो_unlock(&em_tree->lock);
			अगर (ret != -EEXIST)
				अवरोध;
			btrfs_drop_extent_cache(BTRFS_I(inode), cur_offset,
						cur_offset + ins.offset - 1,
						0);
		पूर्ण
		मुक्त_extent_map(em);
next:
		num_bytes -= ins.offset;
		cur_offset += ins.offset;
		*alloc_hपूर्णांक = ins.objectid + ins.offset;

		inode_inc_iversion(inode);
		inode->i_स_समय = current_समय(inode);
		BTRFS_I(inode)->flags |= BTRFS_INODE_PREALLOC;
		अगर (!(mode & FALLOC_FL_KEEP_SIZE) &&
		    (actual_len > inode->i_size) &&
		    (cur_offset > inode->i_size)) अणु
			अगर (cur_offset > actual_len)
				i_size = actual_len;
			अन्यथा
				i_size = cur_offset;
			i_size_ग_लिखो(inode, i_size);
			btrfs_inode_safe_disk_i_size_ग_लिखो(BTRFS_I(inode), 0);
		पूर्ण

		ret = btrfs_update_inode(trans, root, BTRFS_I(inode));

		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			अगर (own_trans)
				btrfs_end_transaction(trans);
			अवरोध;
		पूर्ण

		अगर (own_trans) अणु
			btrfs_end_transaction(trans);
			trans = शून्य;
		पूर्ण
	पूर्ण
	अगर (clear_offset < end)
		btrfs_मुक्त_reserved_data_space(BTRFS_I(inode), शून्य, clear_offset,
			end - clear_offset + 1);
	वापस ret;
पूर्ण

पूर्णांक btrfs_pपुनः_स्मृति_file_range(काष्ठा inode *inode, पूर्णांक mode,
			      u64 start, u64 num_bytes, u64 min_size,
			      loff_t actual_len, u64 *alloc_hपूर्णांक)
अणु
	वापस __btrfs_pपुनः_स्मृति_file_range(inode, mode, start, num_bytes,
					   min_size, actual_len, alloc_hपूर्णांक,
					   शून्य);
पूर्ण

पूर्णांक btrfs_pपुनः_स्मृति_file_range_trans(काष्ठा inode *inode,
				    काष्ठा btrfs_trans_handle *trans, पूर्णांक mode,
				    u64 start, u64 num_bytes, u64 min_size,
				    loff_t actual_len, u64 *alloc_hपूर्णांक)
अणु
	वापस __btrfs_pपुनः_स्मृति_file_range(inode, mode, start, num_bytes,
					   min_size, actual_len, alloc_hपूर्णांक, trans);
पूर्ण

अटल पूर्णांक btrfs_set_page_dirty(काष्ठा page *page)
अणु
	वापस __set_page_dirty_nobuffers(page);
पूर्ण

अटल पूर्णांक btrfs_permission(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	umode_t mode = inode->i_mode;

	अगर (mask & MAY_WRITE &&
	    (S_ISREG(mode) || S_ISसूची(mode) || S_ISLNK(mode))) अणु
		अगर (btrfs_root_पढ़ोonly(root))
			वापस -EROFS;
		अगर (BTRFS_I(inode)->flags & BTRFS_INODE_READONLY)
			वापस -EACCES;
	पूर्ण
	वापस generic_permission(&init_user_ns, inode, mask);
पूर्ण

अटल पूर्णांक btrfs_क्षणिक_ख(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = BTRFS_I(dir)->root;
	काष्ठा inode *inode = शून्य;
	u64 objectid;
	u64 index;
	पूर्णांक ret = 0;

	/*
	 * 5 units required क्रम adding orphan entry
	 */
	trans = btrfs_start_transaction(root, 5);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	ret = btrfs_get_मुक्त_objectid(root, &objectid);
	अगर (ret)
		जाओ out;

	inode = btrfs_new_inode(trans, root, dir, शून्य, 0,
			btrfs_ino(BTRFS_I(dir)), objectid, mode, &index);
	अगर (IS_ERR(inode)) अणु
		ret = PTR_ERR(inode);
		inode = शून्य;
		जाओ out;
	पूर्ण

	inode->i_fop = &btrfs_file_operations;
	inode->i_op = &btrfs_file_inode_operations;

	inode->i_mapping->a_ops = &btrfs_aops;

	ret = btrfs_init_inode_security(trans, inode, dir, शून्य);
	अगर (ret)
		जाओ out;

	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
	अगर (ret)
		जाओ out;
	ret = btrfs_orphan_add(trans, BTRFS_I(inode));
	अगर (ret)
		जाओ out;

	/*
	 * We set number of links to 0 in btrfs_new_inode(), and here we set
	 * it to 1 because d_क्षणिक_ख() will issue a warning अगर the count is 0,
	 * through:
	 *
	 *    d_क्षणिक_ख() -> inode_dec_link_count() -> drop_nlink()
	 */
	set_nlink(inode, 1);
	d_क्षणिक_ख(dentry, inode);
	unlock_new_inode(inode);
	mark_inode_dirty(inode);
out:
	btrfs_end_transaction(trans);
	अगर (ret && inode)
		discard_new_inode(inode);
	btrfs_btree_balance_dirty(fs_info);
	वापस ret;
पूर्ण

व्योम btrfs_set_range_ग_लिखोback(काष्ठा extent_io_tree *tree, u64 start, u64 end)
अणु
	काष्ठा inode *inode = tree->निजी_data;
	अचिन्हित दीर्घ index = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ end_index = end >> PAGE_SHIFT;
	काष्ठा page *page;

	जबतक (index <= end_index) अणु
		page = find_get_page(inode->i_mapping, index);
		ASSERT(page); /* Pages should be in the extent_io_tree */
		set_page_ग_लिखोback(page);
		put_page(page);
		index++;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SWAP
/*
 * Add an entry indicating a block group or device which is pinned by a
 * swapfile. Returns 0 on success, 1 अगर there is alपढ़ोy an entry क्रम it, or a
 * negative त्रुटि_सं on failure.
 */
अटल पूर्णांक btrfs_add_swapfile_pin(काष्ठा inode *inode, व्योम *ptr,
				  bool is_block_group)
अणु
	काष्ठा btrfs_fs_info *fs_info = BTRFS_I(inode)->root->fs_info;
	काष्ठा btrfs_swapfile_pin *sp, *entry;
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;

	sp = kदो_स्मृति(माप(*sp), GFP_NOFS);
	अगर (!sp)
		वापस -ENOMEM;
	sp->ptr = ptr;
	sp->inode = inode;
	sp->is_block_group = is_block_group;
	sp->bg_extent_count = 1;

	spin_lock(&fs_info->swapfile_pins_lock);
	p = &fs_info->swapfile_pins.rb_node;
	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा btrfs_swapfile_pin, node);
		अगर (sp->ptr < entry->ptr ||
		    (sp->ptr == entry->ptr && sp->inode < entry->inode)) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (sp->ptr > entry->ptr ||
			   (sp->ptr == entry->ptr && sp->inode > entry->inode)) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			अगर (is_block_group)
				entry->bg_extent_count++;
			spin_unlock(&fs_info->swapfile_pins_lock);
			kमुक्त(sp);
			वापस 1;
		पूर्ण
	पूर्ण
	rb_link_node(&sp->node, parent, p);
	rb_insert_color(&sp->node, &fs_info->swapfile_pins);
	spin_unlock(&fs_info->swapfile_pins_lock);
	वापस 0;
पूर्ण

/* Free all of the entries pinned by this swapfile. */
अटल व्योम btrfs_मुक्त_swapfile_pins(काष्ठा inode *inode)
अणु
	काष्ठा btrfs_fs_info *fs_info = BTRFS_I(inode)->root->fs_info;
	काष्ठा btrfs_swapfile_pin *sp;
	काष्ठा rb_node *node, *next;

	spin_lock(&fs_info->swapfile_pins_lock);
	node = rb_first(&fs_info->swapfile_pins);
	जबतक (node) अणु
		next = rb_next(node);
		sp = rb_entry(node, काष्ठा btrfs_swapfile_pin, node);
		अगर (sp->inode == inode) अणु
			rb_erase(&sp->node, &fs_info->swapfile_pins);
			अगर (sp->is_block_group) अणु
				btrfs_dec_block_group_swap_extents(sp->ptr,
							   sp->bg_extent_count);
				btrfs_put_block_group(sp->ptr);
			पूर्ण
			kमुक्त(sp);
		पूर्ण
		node = next;
	पूर्ण
	spin_unlock(&fs_info->swapfile_pins_lock);
पूर्ण

काष्ठा btrfs_swap_info अणु
	u64 start;
	u64 block_start;
	u64 block_len;
	u64 lowest_ppage;
	u64 highest_ppage;
	अचिन्हित दीर्घ nr_pages;
	पूर्णांक nr_extents;
पूर्ण;

अटल पूर्णांक btrfs_add_swap_extent(काष्ठा swap_info_काष्ठा *sis,
				 काष्ठा btrfs_swap_info *bsi)
अणु
	अचिन्हित दीर्घ nr_pages;
	u64 first_ppage, first_ppage_reported, next_ppage;
	पूर्णांक ret;

	first_ppage = ALIGN(bsi->block_start, PAGE_SIZE) >> PAGE_SHIFT;
	next_ppage = ALIGN_DOWN(bsi->block_start + bsi->block_len,
				PAGE_SIZE) >> PAGE_SHIFT;

	अगर (first_ppage >= next_ppage)
		वापस 0;
	nr_pages = next_ppage - first_ppage;

	first_ppage_reported = first_ppage;
	अगर (bsi->start == 0)
		first_ppage_reported++;
	अगर (bsi->lowest_ppage > first_ppage_reported)
		bsi->lowest_ppage = first_ppage_reported;
	अगर (bsi->highest_ppage < (next_ppage - 1))
		bsi->highest_ppage = next_ppage - 1;

	ret = add_swap_extent(sis, bsi->nr_pages, nr_pages, first_ppage);
	अगर (ret < 0)
		वापस ret;
	bsi->nr_extents += ret;
	bsi->nr_pages += nr_pages;
	वापस 0;
पूर्ण

अटल व्योम btrfs_swap_deactivate(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);

	btrfs_मुक्त_swapfile_pins(inode);
	atomic_dec(&BTRFS_I(inode)->root->nr_swapfiles);
पूर्ण

अटल पूर्णांक btrfs_swap_activate(काष्ठा swap_info_काष्ठा *sis, काष्ठा file *file,
			       sector_t *span)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा extent_map *em = शून्य;
	काष्ठा btrfs_device *device = शून्य;
	काष्ठा btrfs_swap_info bsi = अणु
		.lowest_ppage = (sector_t)-1ULL,
	पूर्ण;
	पूर्णांक ret = 0;
	u64 isize;
	u64 start;

	/*
	 * If the swap file was just created, make sure delalloc is करोne. If the
	 * file changes again after this, the user is करोing something stupid and
	 * we करोn't really care.
	 */
	ret = btrfs_रुको_ordered_range(inode, 0, (u64)-1);
	अगर (ret)
		वापस ret;

	/*
	 * The inode is locked, so these flags won't change after we check them.
	 */
	अगर (BTRFS_I(inode)->flags & BTRFS_INODE_COMPRESS) अणु
		btrfs_warn(fs_info, "swapfile must not be compressed");
		वापस -EINVAL;
	पूर्ण
	अगर (!(BTRFS_I(inode)->flags & BTRFS_INODE_NODATACOW)) अणु
		btrfs_warn(fs_info, "swapfile must not be copy-on-write");
		वापस -EINVAL;
	पूर्ण
	अगर (!(BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM)) अणु
		btrfs_warn(fs_info, "swapfile must not be checksummed");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Balance or device हटाओ/replace/resize can move stuff around from
	 * under us. The exclop protection makes sure they aren't running/won't
	 * run concurrently जबतक we are mapping the swap extents, and
	 * fs_info->swapfile_pins prevents them from running जबतक the swap
	 * file is active and moving the extents. Note that this also prevents
	 * a concurrent device add which isn't actually necessary, but it's not
	 * really worth the trouble to allow it.
	 */
	अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_SWAP_ACTIVATE)) अणु
		btrfs_warn(fs_info,
	   "cannot activate swapfile while exclusive operation is running");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Prevent snapshot creation जबतक we are activating the swap file.
	 * We करो not want to race with snapshot creation. If snapshot creation
	 * alपढ़ोy started beक्रमe we bumped nr_swapfiles from 0 to 1 and
	 * completes beक्रमe the first ग_लिखो पूर्णांकo the swap file after it is
	 * activated, than that ग_लिखो would fallback to COW.
	 */
	अगर (!btrfs_drew_try_ग_लिखो_lock(&root->snapshot_lock)) अणु
		btrfs_exclop_finish(fs_info);
		btrfs_warn(fs_info,
	   "cannot activate swapfile because snapshot creation is in progress");
		वापस -EINVAL;
	पूर्ण
	/*
	 * Snapshots can create extents which require COW even अगर NODATACOW is
	 * set. We use this counter to prevent snapshots. We must increment it
	 * beक्रमe walking the extents because we करोn't want a concurrent
	 * snapshot to run after we've alपढ़ोy checked the extents.
	 */
	atomic_inc(&root->nr_swapfiles);

	isize = ALIGN_DOWN(inode->i_size, fs_info->sectorsize);

	lock_extent_bits(io_tree, 0, isize - 1, &cached_state);
	start = 0;
	जबतक (start < isize) अणु
		u64 logical_block_start, physical_block_start;
		काष्ठा btrfs_block_group *bg;
		u64 len = isize - start;

		em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, start, len);
		अगर (IS_ERR(em)) अणु
			ret = PTR_ERR(em);
			जाओ out;
		पूर्ण

		अगर (em->block_start == EXTENT_MAP_HOLE) अणु
			btrfs_warn(fs_info, "swapfile must not have holes");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (em->block_start == EXTENT_MAP_INLINE) अणु
			/*
			 * It's unlikely we'll ever actually find ourselves
			 * here, as a file small enough to fit अंतरभूत won't be
			 * big enough to store more than the swap header, but in
			 * हाल something changes in the future, let's catch it
			 * here rather than later.
			 */
			btrfs_warn(fs_info, "swapfile must not be inline");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (test_bit(EXTENT_FLAG_COMPRESSED, &em->flags)) अणु
			btrfs_warn(fs_info, "swapfile must not be compressed");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		logical_block_start = em->block_start + (start - em->start);
		len = min(len, em->len - (start - em->start));
		मुक्त_extent_map(em);
		em = शून्य;

		ret = can_nocow_extent(inode, start, &len, शून्य, शून्य, शून्य, true);
		अगर (ret < 0) अणु
			जाओ out;
		पूर्ण अन्यथा अगर (ret) अणु
			ret = 0;
		पूर्ण अन्यथा अणु
			btrfs_warn(fs_info,
				   "swapfile must not be copy-on-write");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		em = btrfs_get_chunk_map(fs_info, logical_block_start, len);
		अगर (IS_ERR(em)) अणु
			ret = PTR_ERR(em);
			जाओ out;
		पूर्ण

		अगर (em->map_lookup->type & BTRFS_BLOCK_GROUP_PROखाता_MASK) अणु
			btrfs_warn(fs_info,
				   "swapfile must have single data profile");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (device == शून्य) अणु
			device = em->map_lookup->stripes[0].dev;
			ret = btrfs_add_swapfile_pin(inode, device, false);
			अगर (ret == 1)
				ret = 0;
			अन्यथा अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अगर (device != em->map_lookup->stripes[0].dev) अणु
			btrfs_warn(fs_info, "swapfile must be on one device");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		physical_block_start = (em->map_lookup->stripes[0].physical +
					(logical_block_start - em->start));
		len = min(len, em->len - (logical_block_start - em->start));
		मुक्त_extent_map(em);
		em = शून्य;

		bg = btrfs_lookup_block_group(fs_info, logical_block_start);
		अगर (!bg) अणु
			btrfs_warn(fs_info,
			   "could not find block group containing swapfile");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!btrfs_inc_block_group_swap_extents(bg)) अणु
			btrfs_warn(fs_info,
			   "block group for swapfile at %llu is read-only%s",
			   bg->start,
			   atomic_पढ़ो(&fs_info->scrubs_running) ?
				       " (scrub running)" : "");
			btrfs_put_block_group(bg);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		ret = btrfs_add_swapfile_pin(inode, bg, true);
		अगर (ret) अणु
			btrfs_put_block_group(bg);
			अगर (ret == 1)
				ret = 0;
			अन्यथा
				जाओ out;
		पूर्ण

		अगर (bsi.block_len &&
		    bsi.block_start + bsi.block_len == physical_block_start) अणु
			bsi.block_len += len;
		पूर्ण अन्यथा अणु
			अगर (bsi.block_len) अणु
				ret = btrfs_add_swap_extent(sis, &bsi);
				अगर (ret)
					जाओ out;
			पूर्ण
			bsi.start = start;
			bsi.block_start = physical_block_start;
			bsi.block_len = len;
		पूर्ण

		start += len;
	पूर्ण

	अगर (bsi.block_len)
		ret = btrfs_add_swap_extent(sis, &bsi);

out:
	अगर (!IS_ERR_OR_शून्य(em))
		मुक्त_extent_map(em);

	unlock_extent_cached(io_tree, 0, isize - 1, &cached_state);

	अगर (ret)
		btrfs_swap_deactivate(file);

	btrfs_drew_ग_लिखो_unlock(&root->snapshot_lock);

	btrfs_exclop_finish(fs_info);

	अगर (ret)
		वापस ret;

	अगर (device)
		sis->bdev = device->bdev;
	*span = bsi.highest_ppage - bsi.lowest_ppage + 1;
	sis->max = bsi.nr_pages;
	sis->pages = bsi.nr_pages - 1;
	sis->highest_bit = bsi.nr_pages - 1;
	वापस bsi.nr_extents;
पूर्ण
#अन्यथा
अटल व्योम btrfs_swap_deactivate(काष्ठा file *file)
अणु
पूर्ण

अटल पूर्णांक btrfs_swap_activate(काष्ठा swap_info_काष्ठा *sis, काष्ठा file *file,
			       sector_t *span)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

/*
 * Update the number of bytes used in the VFS' inode. When we replace extents in
 * a range (clone, dedupe, fallocate's zero range), we must update the number of
 * bytes used by the inode in an atomic manner, so that concurrent stat(2) calls
 * always get a correct value.
 */
व्योम btrfs_update_inode_bytes(काष्ठा btrfs_inode *inode,
			      स्थिर u64 add_bytes,
			      स्थिर u64 del_bytes)
अणु
	अगर (add_bytes == del_bytes)
		वापस;

	spin_lock(&inode->lock);
	अगर (del_bytes > 0)
		inode_sub_bytes(&inode->vfs_inode, del_bytes);
	अगर (add_bytes > 0)
		inode_add_bytes(&inode->vfs_inode, add_bytes);
	spin_unlock(&inode->lock);
पूर्ण

अटल स्थिर काष्ठा inode_operations btrfs_dir_inode_operations = अणु
	.getattr	= btrfs_getattr,
	.lookup		= btrfs_lookup,
	.create		= btrfs_create,
	.unlink		= btrfs_unlink,
	.link		= btrfs_link,
	.सूची_गढ़ो		= btrfs_सूची_गढ़ो,
	.सूची_हटाओ		= btrfs_सूची_हटाओ,
	.नाम		= btrfs_नाम2,
	.symlink	= btrfs_symlink,
	.setattr	= btrfs_setattr,
	.mknod		= btrfs_mknod,
	.listxattr	= btrfs_listxattr,
	.permission	= btrfs_permission,
	.get_acl	= btrfs_get_acl,
	.set_acl	= btrfs_set_acl,
	.update_समय	= btrfs_update_समय,
	.क्षणिक_ख        = btrfs_क्षणिक_ख,
	.fileattr_get	= btrfs_fileattr_get,
	.fileattr_set	= btrfs_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा file_operations btrfs_dir_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= btrfs_real_सूची_पढ़ो,
	.खोलो		= btrfs_सूची_खोलो,
	.unlocked_ioctl	= btrfs_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= btrfs_compat_ioctl,
#पूर्ण_अगर
	.release        = btrfs_release_file,
	.fsync		= btrfs_sync_file,
पूर्ण;

/*
 * btrfs करोesn't support the bmap operation because swapfiles
 * use bmap to make a mapping of extents in the file.  They assume
 * these extents won't change over the lअगरe of the file and they
 * use the bmap result to करो IO directly to the drive.
 *
 * the btrfs bmap call would वापस logical addresses that aren't
 * suitable क्रम IO and they also will change frequently as COW
 * operations happen.  So, swapfile + btrfs == corruption.
 *
 * For now we're aव्योमing this by dropping bmap.
 */
अटल स्थिर काष्ठा address_space_operations btrfs_aops = अणु
	.पढ़ोpage	= btrfs_पढ़ोpage,
	.ग_लिखोpage	= btrfs_ग_लिखोpage,
	.ग_लिखोpages	= btrfs_ग_लिखोpages,
	.पढ़ोahead	= btrfs_पढ़ोahead,
	.direct_IO	= noop_direct_IO,
	.invalidatepage = btrfs_invalidatepage,
	.releasepage	= btrfs_releasepage,
#अगर_घोषित CONFIG_MIGRATION
	.migratepage	= btrfs_migratepage,
#पूर्ण_अगर
	.set_page_dirty	= btrfs_set_page_dirty,
	.error_हटाओ_page = generic_error_हटाओ_page,
	.swap_activate	= btrfs_swap_activate,
	.swap_deactivate = btrfs_swap_deactivate,
पूर्ण;

अटल स्थिर काष्ठा inode_operations btrfs_file_inode_operations = अणु
	.getattr	= btrfs_getattr,
	.setattr	= btrfs_setattr,
	.listxattr      = btrfs_listxattr,
	.permission	= btrfs_permission,
	.fiemap		= btrfs_fiemap,
	.get_acl	= btrfs_get_acl,
	.set_acl	= btrfs_set_acl,
	.update_समय	= btrfs_update_समय,
	.fileattr_get	= btrfs_fileattr_get,
	.fileattr_set	= btrfs_fileattr_set,
पूर्ण;
अटल स्थिर काष्ठा inode_operations btrfs_special_inode_operations = अणु
	.getattr	= btrfs_getattr,
	.setattr	= btrfs_setattr,
	.permission	= btrfs_permission,
	.listxattr	= btrfs_listxattr,
	.get_acl	= btrfs_get_acl,
	.set_acl	= btrfs_set_acl,
	.update_समय	= btrfs_update_समय,
पूर्ण;
अटल स्थिर काष्ठा inode_operations btrfs_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.getattr	= btrfs_getattr,
	.setattr	= btrfs_setattr,
	.permission	= btrfs_permission,
	.listxattr	= btrfs_listxattr,
	.update_समय	= btrfs_update_समय,
पूर्ण;

स्थिर काष्ठा dentry_operations btrfs_dentry_operations = अणु
	.d_delete	= btrfs_dentry_delete,
पूर्ण;
