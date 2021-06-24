<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/ext4/verity.c: fs-verity support क्रम ext4
 *
 * Copyright 2019 Google LLC
 */

/*
 * Implementation of fsverity_operations क्रम ext4.
 *
 * ext4 stores the verity metadata (Merkle tree and fsverity_descriptor) past
 * the end of the file, starting at the first 64K boundary beyond i_size.  This
 * approach works because (a) verity files are पढ़ोonly, and (b) pages fully
 * beyond i_size aren't visible to userspace but can be पढ़ो/written पूर्णांकernally
 * by ext4 with only some relatively small changes to ext4.  This approach
 * aव्योमs having to depend on the EA_INODE feature and on rearchitecturing
 * ext4's xattr support to support paging multi-gigabyte xattrs पूर्णांकo memory, and
 * to support encrypting xattrs.  Note that the verity metadata *must* be
 * encrypted when the file is, since it contains hashes of the plaपूर्णांकext data.
 *
 * Using a 64K boundary rather than a 4K one keeps things पढ़ोy क्रम
 * architectures with 64K pages, and it करोesn't necessarily waste space on-disk
 * since there can be a hole between i_size and the start of the Merkle tree.
 */

#समावेश <linux/quotaops.h>

#समावेश "ext4.h"
#समावेश "ext4_extents.h"
#समावेश "ext4_jbd2.h"

अटल अंतरभूत loff_t ext4_verity_metadata_pos(स्थिर काष्ठा inode *inode)
अणु
	वापस round_up(inode->i_size, 65536);
पूर्ण

/*
 * Read some verity metadata from the inode.  __vfs_पढ़ो() can't be used because
 * we need to पढ़ो beyond i_size.
 */
अटल पूर्णांक pagecache_पढ़ो(काष्ठा inode *inode, व्योम *buf, माप_प्रकार count,
			  loff_t pos)
अणु
	जबतक (count) अणु
		माप_प्रकार n = min_t(माप_प्रकार, count,
				 PAGE_SIZE - offset_in_page(pos));
		काष्ठा page *page;

		page = पढ़ो_mapping_page(inode->i_mapping, pos >> PAGE_SHIFT,
					 शून्य);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		स_नकल_from_page(buf, page, offset_in_page(pos), n);

		put_page(page);

		buf += n;
		pos += n;
		count -= n;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Write some verity metadata to the inode क्रम FS_IOC_ENABLE_VERITY.
 * kernel_ग_लिखो() can't be used because the file descriptor is पढ़ोonly.
 */
अटल पूर्णांक pagecache_ग_लिखो(काष्ठा inode *inode, स्थिर व्योम *buf, माप_प्रकार count,
			   loff_t pos)
अणु
	अगर (pos + count > inode->i_sb->s_maxbytes)
		वापस -EFBIG;

	जबतक (count) अणु
		माप_प्रकार n = min_t(माप_प्रकार, count,
				 PAGE_SIZE - offset_in_page(pos));
		काष्ठा page *page;
		व्योम *fsdata;
		पूर्णांक res;

		res = pagecache_ग_लिखो_begin(शून्य, inode->i_mapping, pos, n, 0,
					    &page, &fsdata);
		अगर (res)
			वापस res;

		स_नकल_to_page(page, offset_in_page(pos), buf, n);

		res = pagecache_ग_लिखो_end(शून्य, inode->i_mapping, pos, n, n,
					  page, fsdata);
		अगर (res < 0)
			वापस res;
		अगर (res != n)
			वापस -EIO;

		buf += n;
		pos += n;
		count -= n;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_begin_enable_verity(काष्ठा file *filp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	स्थिर पूर्णांक credits = 2; /* superblock and inode क्रम ext4_orphan_add() */
	handle_t *handle;
	पूर्णांक err;

	अगर (IS_DAX(inode) || ext4_test_inode_flag(inode, EXT4_INODE_DAX))
		वापस -EINVAL;

	अगर (ext4_verity_in_progress(inode))
		वापस -EBUSY;

	/*
	 * Since the file was खोलोed पढ़ोonly, we have to initialize the jbd
	 * inode and quotas here and not rely on ->खोलो() करोing it.  This must
	 * be करोne beक्रमe evicting the अंतरभूत data.
	 */

	err = ext4_inode_attach_jinode(inode);
	अगर (err)
		वापस err;

	err = dquot_initialize(inode);
	अगर (err)
		वापस err;

	err = ext4_convert_अंतरभूत_data(inode);
	अगर (err)
		वापस err;

	अगर (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) अणु
		ext4_warning_inode(inode,
				   "verity is only allowed on extent-based files");
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * ext4 uses the last allocated block to find the verity descriptor, so
	 * we must हटाओ any other blocks past खातापूर्ण which might confuse things.
	 */
	err = ext4_truncate(inode);
	अगर (err)
		वापस err;

	handle = ext4_journal_start(inode, EXT4_HT_INODE, credits);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	err = ext4_orphan_add(handle, inode);
	अगर (err == 0)
		ext4_set_inode_state(inode, EXT4_STATE_VERITY_IN_PROGRESS);

	ext4_journal_stop(handle);
	वापस err;
पूर्ण

/*
 * ext4 stores the verity descriptor beginning on the next fileप्रणाली block
 * boundary after the Merkle tree.  Then, the descriptor size is stored in the
 * last 4 bytes of the last allocated fileप्रणाली block --- which is either the
 * block in which the descriptor ends, or the next block after that अगर there
 * weren't at least 4 bytes reमुख्यing.
 *
 * We can't simply store the descriptor in an xattr because it *must* be
 * encrypted when ext4 encryption is used, but ext4 encryption करोesn't encrypt
 * xattrs.  Also, अगर the descriptor includes a large signature blob it may be
 * too large to store in an xattr without the EA_INODE feature.
 */
अटल पूर्णांक ext4_ग_लिखो_verity_descriptor(काष्ठा inode *inode, स्थिर व्योम *desc,
					माप_प्रकार desc_size, u64 merkle_tree_size)
अणु
	स्थिर u64 desc_pos = round_up(ext4_verity_metadata_pos(inode) +
				      merkle_tree_size, i_blocksize(inode));
	स्थिर u64 desc_end = desc_pos + desc_size;
	स्थिर __le32 desc_size_disk = cpu_to_le32(desc_size);
	स्थिर u64 desc_size_pos = round_up(desc_end + माप(desc_size_disk),
					   i_blocksize(inode)) -
				  माप(desc_size_disk);
	पूर्णांक err;

	err = pagecache_ग_लिखो(inode, desc, desc_size, desc_pos);
	अगर (err)
		वापस err;

	वापस pagecache_ग_लिखो(inode, &desc_size_disk, माप(desc_size_disk),
			       desc_size_pos);
पूर्ण

अटल पूर्णांक ext4_end_enable_verity(काष्ठा file *filp, स्थिर व्योम *desc,
				  माप_प्रकार desc_size, u64 merkle_tree_size)
अणु
	काष्ठा inode *inode = file_inode(filp);
	स्थिर पूर्णांक credits = 2; /* superblock and inode क्रम ext4_orphan_del() */
	handle_t *handle;
	काष्ठा ext4_iloc iloc;
	पूर्णांक err = 0;

	/*
	 * If an error alपढ़ोy occurred (which fs/verity/ संकेतs by passing
	 * desc == शून्य), then only clean-up is needed.
	 */
	अगर (desc == शून्य)
		जाओ cleanup;

	/* Append the verity descriptor. */
	err = ext4_ग_लिखो_verity_descriptor(inode, desc, desc_size,
					   merkle_tree_size);
	अगर (err)
		जाओ cleanup;

	/*
	 * Write all pages (both data and verity metadata).  Note that this must
	 * happen beक्रमe clearing EXT4_STATE_VERITY_IN_PROGRESS; otherwise pages
	 * beyond i_size won't be written properly.  For crash consistency, this
	 * also must happen beक्रमe the verity inode flag माला_लो persisted.
	 */
	err = filemap_ग_लिखो_and_रुको(inode->i_mapping);
	अगर (err)
		जाओ cleanup;

	/*
	 * Finally, set the verity inode flag and हटाओ the inode from the
	 * orphan list (in a single transaction).
	 */

	handle = ext4_journal_start(inode, EXT4_HT_INODE, credits);
	अगर (IS_ERR(handle)) अणु
		err = PTR_ERR(handle);
		जाओ cleanup;
	पूर्ण

	err = ext4_orphan_del(handle, inode);
	अगर (err)
		जाओ stop_and_cleanup;

	err = ext4_reserve_inode_ग_लिखो(handle, inode, &iloc);
	अगर (err)
		जाओ stop_and_cleanup;

	ext4_set_inode_flag(inode, EXT4_INODE_VERITY);
	ext4_set_inode_flags(inode, false);
	err = ext4_mark_iloc_dirty(handle, inode, &iloc);
	अगर (err)
		जाओ stop_and_cleanup;

	ext4_journal_stop(handle);

	ext4_clear_inode_state(inode, EXT4_STATE_VERITY_IN_PROGRESS);
	वापस 0;

stop_and_cleanup:
	ext4_journal_stop(handle);
cleanup:
	/*
	 * Verity failed to be enabled, so clean up by truncating any verity
	 * metadata that was written beyond i_size (both from cache and from
	 * disk), removing the inode from the orphan list (अगर it wasn't करोne
	 * alपढ़ोy), and clearing EXT4_STATE_VERITY_IN_PROGRESS.
	 */
	truncate_inode_pages(inode->i_mapping, inode->i_size);
	ext4_truncate(inode);
	ext4_orphan_del(शून्य, inode);
	ext4_clear_inode_state(inode, EXT4_STATE_VERITY_IN_PROGRESS);
	वापस err;
पूर्ण

अटल पूर्णांक ext4_get_verity_descriptor_location(काष्ठा inode *inode,
					       माप_प्रकार *desc_size_ret,
					       u64 *desc_pos_ret)
अणु
	काष्ठा ext4_ext_path *path;
	काष्ठा ext4_extent *last_extent;
	u32 end_lblk;
	u64 desc_size_pos;
	__le32 desc_size_disk;
	u32 desc_size;
	u64 desc_pos;
	पूर्णांक err;

	/*
	 * Descriptor size is in last 4 bytes of last allocated block.
	 * See ext4_ग_लिखो_verity_descriptor().
	 */

	अगर (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) अणु
		EXT4_ERROR_INODE(inode, "verity file doesn't use extents");
		वापस -EFSCORRUPTED;
	पूर्ण

	path = ext4_find_extent(inode, EXT_MAX_BLOCKS - 1, शून्य, 0);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	last_extent = path[path->p_depth].p_ext;
	अगर (!last_extent) अणु
		EXT4_ERROR_INODE(inode, "verity file has no extents");
		ext4_ext_drop_refs(path);
		kमुक्त(path);
		वापस -EFSCORRUPTED;
	पूर्ण

	end_lblk = le32_to_cpu(last_extent->ee_block) +
		   ext4_ext_get_actual_len(last_extent);
	desc_size_pos = (u64)end_lblk << inode->i_blkbits;
	ext4_ext_drop_refs(path);
	kमुक्त(path);

	अगर (desc_size_pos < माप(desc_size_disk))
		जाओ bad;
	desc_size_pos -= माप(desc_size_disk);

	err = pagecache_पढ़ो(inode, &desc_size_disk, माप(desc_size_disk),
			     desc_size_pos);
	अगर (err)
		वापस err;
	desc_size = le32_to_cpu(desc_size_disk);

	/*
	 * The descriptor is stored just beक्रमe the desc_size_disk, but starting
	 * on a fileप्रणाली block boundary.
	 */

	अगर (desc_size > पूर्णांक_उच्च || desc_size > desc_size_pos)
		जाओ bad;

	desc_pos = round_करोwn(desc_size_pos - desc_size, i_blocksize(inode));
	अगर (desc_pos < ext4_verity_metadata_pos(inode))
		जाओ bad;

	*desc_size_ret = desc_size;
	*desc_pos_ret = desc_pos;
	वापस 0;

bad:
	EXT4_ERROR_INODE(inode, "verity file corrupted; can't find descriptor");
	वापस -EFSCORRUPTED;
पूर्ण

अटल पूर्णांक ext4_get_verity_descriptor(काष्ठा inode *inode, व्योम *buf,
				      माप_प्रकार buf_size)
अणु
	माप_प्रकार desc_size = 0;
	u64 desc_pos = 0;
	पूर्णांक err;

	err = ext4_get_verity_descriptor_location(inode, &desc_size, &desc_pos);
	अगर (err)
		वापस err;

	अगर (buf_size) अणु
		अगर (desc_size > buf_size)
			वापस -दुस्फल;
		err = pagecache_पढ़ो(inode, buf, desc_size, desc_pos);
		अगर (err)
			वापस err;
	पूर्ण
	वापस desc_size;
पूर्ण

अटल काष्ठा page *ext4_पढ़ो_merkle_tree_page(काष्ठा inode *inode,
					       pgoff_t index,
					       अचिन्हित दीर्घ num_ra_pages)
अणु
	DEFINE_READAHEAD(ractl, शून्य, शून्य, inode->i_mapping, index);
	काष्ठा page *page;

	index += ext4_verity_metadata_pos(inode) >> PAGE_SHIFT;

	page = find_get_page_flags(inode->i_mapping, index, FGP_ACCESSED);
	अगर (!page || !PageUptodate(page)) अणु
		अगर (page)
			put_page(page);
		अन्यथा अगर (num_ra_pages > 1)
			page_cache_ra_unbounded(&ractl, num_ra_pages, 0);
		page = पढ़ो_mapping_page(inode->i_mapping, index, शून्य);
	पूर्ण
	वापस page;
पूर्ण

अटल पूर्णांक ext4_ग_लिखो_merkle_tree_block(काष्ठा inode *inode, स्थिर व्योम *buf,
					u64 index, पूर्णांक log_blocksize)
अणु
	loff_t pos = ext4_verity_metadata_pos(inode) + (index << log_blocksize);

	वापस pagecache_ग_लिखो(inode, buf, 1 << log_blocksize, pos);
पूर्ण

स्थिर काष्ठा fsverity_operations ext4_verityops = अणु
	.begin_enable_verity	= ext4_begin_enable_verity,
	.end_enable_verity	= ext4_end_enable_verity,
	.get_verity_descriptor	= ext4_get_verity_descriptor,
	.पढ़ो_merkle_tree_page	= ext4_पढ़ो_merkle_tree_page,
	.ग_लिखो_merkle_tree_block = ext4_ग_लिखो_merkle_tree_block,
पूर्ण;
