<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/verity.c: fs-verity support क्रम f2fs
 *
 * Copyright 2019 Google LLC
 */

/*
 * Implementation of fsverity_operations क्रम f2fs.
 *
 * Like ext4, f2fs stores the verity metadata (Merkle tree and
 * fsverity_descriptor) past the end of the file, starting at the first 64K
 * boundary beyond i_size.  This approach works because (a) verity files are
 * पढ़ोonly, and (b) pages fully beyond i_size aren't visible to userspace but
 * can be पढ़ो/written पूर्णांकernally by f2fs with only some relatively small
 * changes to f2fs.  Extended attributes cannot be used because (a) f2fs limits
 * the total size of an inode's xattr entries to 4096 bytes, which wouldn't be
 * enough क्रम even a single Merkle tree block, and (b) f2fs encryption करोesn't
 * encrypt xattrs, yet the verity metadata *must* be encrypted when the file is
 * because it contains hashes of the plaपूर्णांकext data.
 *
 * Using a 64K boundary rather than a 4K one keeps things पढ़ोy क्रम
 * architectures with 64K pages, and it करोesn't necessarily waste space on-disk
 * since there can be a hole between i_size and the start of the Merkle tree.
 */

#समावेश <linux/f2fs_fs.h>

#समावेश "f2fs.h"
#समावेश "xattr.h"

#घोषणा F2FS_VERIFY_VER	(1)

अटल अंतरभूत loff_t f2fs_verity_metadata_pos(स्थिर काष्ठा inode *inode)
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
		व्योम *addr;

		page = पढ़ो_mapping_page(inode->i_mapping, pos >> PAGE_SHIFT,
					 शून्य);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		addr = kmap_atomic(page);
		स_नकल(buf, addr + offset_in_page(pos), n);
		kunmap_atomic(addr);

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
		व्योम *addr;
		पूर्णांक res;

		res = pagecache_ग_लिखो_begin(शून्य, inode->i_mapping, pos, n, 0,
					    &page, &fsdata);
		अगर (res)
			वापस res;

		addr = kmap_atomic(page);
		स_नकल(addr + offset_in_page(pos), buf, n);
		kunmap_atomic(addr);

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

/*
 * Format of f2fs verity xattr.  This poपूर्णांकs to the location of the verity
 * descriptor within the file data rather than containing it directly because
 * the verity descriptor *must* be encrypted when f2fs encryption is used.  But,
 * f2fs encryption करोes not encrypt xattrs.
 */
काष्ठा fsverity_descriptor_location अणु
	__le32 version;
	__le32 size;
	__le64 pos;
पूर्ण;

अटल पूर्णांक f2fs_begin_enable_verity(काष्ठा file *filp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक err;

	अगर (f2fs_verity_in_progress(inode))
		वापस -EBUSY;

	अगर (f2fs_is_atomic_file(inode) || f2fs_is_अस्थिर_file(inode))
		वापस -EOPNOTSUPP;

	/*
	 * Since the file was खोलोed पढ़ोonly, we have to initialize the quotas
	 * here and not rely on ->खोलो() करोing it.  This must be करोne beक्रमe
	 * evicting the अंतरभूत data.
	 */
	err = dquot_initialize(inode);
	अगर (err)
		वापस err;

	err = f2fs_convert_अंतरभूत_inode(inode);
	अगर (err)
		वापस err;

	set_inode_flag(inode, FI_VERITY_IN_PROGRESS);
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_end_enable_verity(काष्ठा file *filp, स्थिर व्योम *desc,
				  माप_प्रकार desc_size, u64 merkle_tree_size)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	u64 desc_pos = f2fs_verity_metadata_pos(inode) + merkle_tree_size;
	काष्ठा fsverity_descriptor_location dloc = अणु
		.version = cpu_to_le32(F2FS_VERIFY_VER),
		.size = cpu_to_le32(desc_size),
		.pos = cpu_to_le64(desc_pos),
	पूर्ण;
	पूर्णांक err = 0, err2 = 0;

	/*
	 * If an error alपढ़ोy occurred (which fs/verity/ संकेतs by passing
	 * desc == शून्य), then only clean-up is needed.
	 */
	अगर (desc == शून्य)
		जाओ cleanup;

	/* Append the verity descriptor. */
	err = pagecache_ग_लिखो(inode, desc, desc_size, desc_pos);
	अगर (err)
		जाओ cleanup;

	/*
	 * Write all pages (both data and verity metadata).  Note that this must
	 * happen beक्रमe clearing FI_VERITY_IN_PROGRESS; otherwise pages beyond
	 * i_size won't be written properly.  For crash consistency, this also
	 * must happen beक्रमe the verity inode flag माला_लो persisted.
	 */
	err = filemap_ग_लिखो_and_रुको(inode->i_mapping);
	अगर (err)
		जाओ cleanup;

	/* Set the verity xattr. */
	err = f2fs_setxattr(inode, F2FS_XATTR_INDEX_VERITY,
			    F2FS_XATTR_NAME_VERITY, &dloc, माप(dloc),
			    शून्य, XATTR_CREATE);
	अगर (err)
		जाओ cleanup;

	/* Finally, set the verity inode flag. */
	file_set_verity(inode);
	f2fs_set_inode_flags(inode);
	f2fs_mark_inode_dirty_sync(inode, true);

	clear_inode_flag(inode, FI_VERITY_IN_PROGRESS);
	वापस 0;

cleanup:
	/*
	 * Verity failed to be enabled, so clean up by truncating any verity
	 * metadata that was written beyond i_size (both from cache and from
	 * disk) and clearing FI_VERITY_IN_PROGRESS.
	 *
	 * Taking i_gc_rwsem[WRITE] is needed to stop f2fs garbage collection
	 * from re-instantiating cached pages we are truncating (since unlike
	 * normal file accesses, garbage collection isn't limited by i_size).
	 */
	करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	truncate_inode_pages(inode->i_mapping, inode->i_size);
	err2 = f2fs_truncate(inode);
	अगर (err2) अणु
		f2fs_err(sbi, "Truncating verity metadata failed (errno=%d)",
			 err2);
		set_sbi_flag(sbi, SBI_NEED_FSCK);
	पूर्ण
	up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	clear_inode_flag(inode, FI_VERITY_IN_PROGRESS);
	वापस err ?: err2;
पूर्ण

अटल पूर्णांक f2fs_get_verity_descriptor(काष्ठा inode *inode, व्योम *buf,
				      माप_प्रकार buf_size)
अणु
	काष्ठा fsverity_descriptor_location dloc;
	पूर्णांक res;
	u32 size;
	u64 pos;

	/* Get the descriptor location */
	res = f2fs_getxattr(inode, F2FS_XATTR_INDEX_VERITY,
			    F2FS_XATTR_NAME_VERITY, &dloc, माप(dloc), शून्य);
	अगर (res < 0 && res != -दुस्फल)
		वापस res;
	अगर (res != माप(dloc) || dloc.version != cpu_to_le32(F2FS_VERIFY_VER)) अणु
		f2fs_warn(F2FS_I_SB(inode), "unknown verity xattr format");
		वापस -EINVAL;
	पूर्ण
	size = le32_to_cpu(dloc.size);
	pos = le64_to_cpu(dloc.pos);

	/* Get the descriptor */
	अगर (pos + size < pos || pos + size > inode->i_sb->s_maxbytes ||
	    pos < f2fs_verity_metadata_pos(inode) || size > पूर्णांक_उच्च) अणु
		f2fs_warn(F2FS_I_SB(inode), "invalid verity xattr");
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर (buf_size) अणु
		अगर (size > buf_size)
			वापस -दुस्फल;
		res = pagecache_पढ़ो(inode, buf, size, pos);
		अगर (res)
			वापस res;
	पूर्ण
	वापस size;
पूर्ण

अटल काष्ठा page *f2fs_पढ़ो_merkle_tree_page(काष्ठा inode *inode,
					       pgoff_t index,
					       अचिन्हित दीर्घ num_ra_pages)
अणु
	DEFINE_READAHEAD(ractl, शून्य, शून्य, inode->i_mapping, index);
	काष्ठा page *page;

	index += f2fs_verity_metadata_pos(inode) >> PAGE_SHIFT;

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

अटल पूर्णांक f2fs_ग_लिखो_merkle_tree_block(काष्ठा inode *inode, स्थिर व्योम *buf,
					u64 index, पूर्णांक log_blocksize)
अणु
	loff_t pos = f2fs_verity_metadata_pos(inode) + (index << log_blocksize);

	वापस pagecache_ग_लिखो(inode, buf, 1 << log_blocksize, pos);
पूर्ण

स्थिर काष्ठा fsverity_operations f2fs_verityops = अणु
	.begin_enable_verity	= f2fs_begin_enable_verity,
	.end_enable_verity	= f2fs_end_enable_verity,
	.get_verity_descriptor	= f2fs_get_verity_descriptor,
	.पढ़ो_merkle_tree_page	= f2fs_पढ़ो_merkle_tree_page,
	.ग_लिखो_merkle_tree_block = f2fs_ग_लिखो_merkle_tree_block,
पूर्ण;
