<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sched/xacct.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/file.h>
#समावेश <linux/uपन.स>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/security.h>
#समावेश <linux/export.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/splice.h>
#समावेश <linux/compat.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs.h>
#समावेश "internal.h"

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>

/*
 * Perक्रमms necessary checks beक्रमe करोing a clone.
 *
 * Can adjust amount of bytes to clone via @req_count argument.
 * Returns appropriate error code that caller should वापस or
 * zero in हाल the clone should be allowed.
 */
अटल पूर्णांक generic_remap_checks(काष्ठा file *file_in, loff_t pos_in,
				काष्ठा file *file_out, loff_t pos_out,
				loff_t *req_count, अचिन्हित पूर्णांक remap_flags)
अणु
	काष्ठा inode *inode_in = file_in->f_mapping->host;
	काष्ठा inode *inode_out = file_out->f_mapping->host;
	uपूर्णांक64_t count = *req_count;
	uपूर्णांक64_t bcount;
	loff_t size_in, size_out;
	loff_t bs = inode_out->i_sb->s_blocksize;
	पूर्णांक ret;

	/* The start of both ranges must be aligned to an fs block. */
	अगर (!IS_ALIGNED(pos_in, bs) || !IS_ALIGNED(pos_out, bs))
		वापस -EINVAL;

	/* Ensure offsets करोn't wrap. */
	अगर (pos_in + count < pos_in || pos_out + count < pos_out)
		वापस -EINVAL;

	size_in = i_size_पढ़ो(inode_in);
	size_out = i_size_पढ़ो(inode_out);

	/* Dedupe requires both ranges to be within खातापूर्ण. */
	अगर ((remap_flags & REMAP_खाता_DEDUP) &&
	    (pos_in >= size_in || pos_in + count > size_in ||
	     pos_out >= size_out || pos_out + count > size_out))
		वापस -EINVAL;

	/* Ensure the infile range is within the infile. */
	अगर (pos_in >= size_in)
		वापस -EINVAL;
	count = min(count, size_in - (uपूर्णांक64_t)pos_in);

	ret = generic_ग_लिखो_check_limits(file_out, pos_out, &count);
	अगर (ret)
		वापस ret;

	/*
	 * If the user wanted us to link to the infile's खातापूर्ण, round up to the
	 * next block boundary क्रम this check.
	 *
	 * Otherwise, make sure the count is also block-aligned, having
	 * alपढ़ोy confirmed the starting offsets' block alignment.
	 */
	अगर (pos_in + count == size_in) अणु
		bcount = ALIGN(size_in, bs) - pos_in;
	पूर्ण अन्यथा अणु
		अगर (!IS_ALIGNED(count, bs))
			count = ALIGN_DOWN(count, bs);
		bcount = count;
	पूर्ण

	/* Don't allow overlapped cloning within the same file. */
	अगर (inode_in == inode_out &&
	    pos_out + bcount > pos_in &&
	    pos_out < pos_in + bcount)
		वापस -EINVAL;

	/*
	 * We लघुened the request but the caller can't deal with that, so
	 * bounce the request back to userspace.
	 */
	अगर (*req_count != count && !(remap_flags & REMAP_खाता_CAN_SHORTEN))
		वापस -EINVAL;

	*req_count = count;
	वापस 0;
पूर्ण

अटल पूर्णांक remap_verअगरy_area(काष्ठा file *file, loff_t pos, loff_t len,
			     bool ग_लिखो)
अणु
	काष्ठा inode *inode = file_inode(file);

	अगर (unlikely(pos < 0 || len < 0))
		वापस -EINVAL;

	अगर (unlikely((loff_t) (pos + len) < 0))
		वापस -EINVAL;

	अगर (unlikely(inode->i_flctx && mandatory_lock(inode))) अणु
		loff_t end = len ? pos + len - 1 : OFFSET_MAX;
		पूर्णांक retval;

		retval = locks_mandatory_area(inode, file, pos, end,
				ग_लिखो ? F_WRLCK : F_RDLCK);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	वापस security_file_permission(file, ग_लिखो ? MAY_WRITE : MAY_READ);
पूर्ण

/*
 * Ensure that we करोn't remap a partial खातापूर्ण block in the middle of something
 * अन्यथा.  Assume that the offsets have alपढ़ोy been checked क्रम block
 * alignment.
 *
 * For clone we only link a partial खातापूर्ण block above or at the destination file's
 * खातापूर्ण.  For deduplication we accept a partial खातापूर्ण block only अगर it ends at the
 * destination file's खातापूर्ण (can not link it पूर्णांकo the middle of a file).
 *
 * Shorten the request अगर possible.
 */
अटल पूर्णांक generic_remap_check_len(काष्ठा inode *inode_in,
				   काष्ठा inode *inode_out,
				   loff_t pos_out,
				   loff_t *len,
				   अचिन्हित पूर्णांक remap_flags)
अणु
	u64 blkmask = i_blocksize(inode_in) - 1;
	loff_t new_len = *len;

	अगर ((*len & blkmask) == 0)
		वापस 0;

	अगर (pos_out + *len < i_size_पढ़ो(inode_out))
		new_len &= ~blkmask;

	अगर (new_len == *len)
		वापस 0;

	अगर (remap_flags & REMAP_खाता_CAN_SHORTEN) अणु
		*len = new_len;
		वापस 0;
	पूर्ण

	वापस (remap_flags & REMAP_खाता_DEDUP) ? -EBADE : -EINVAL;
पूर्ण

/* Read a page's worth of file data पूर्णांकo the page cache. */
अटल काष्ठा page *vfs_dedupe_get_page(काष्ठा inode *inode, loff_t offset)
अणु
	काष्ठा page *page;

	page = पढ़ो_mapping_page(inode->i_mapping, offset >> PAGE_SHIFT, शून्य);
	अगर (IS_ERR(page))
		वापस page;
	अगर (!PageUptodate(page)) अणु
		put_page(page);
		वापस ERR_PTR(-EIO);
	पूर्ण
	वापस page;
पूर्ण

/*
 * Lock two pages, ensuring that we lock in offset order अगर the pages are from
 * the same file.
 */
अटल व्योम vfs_lock_two_pages(काष्ठा page *page1, काष्ठा page *page2)
अणु
	/* Always lock in order of increasing index. */
	अगर (page1->index > page2->index)
		swap(page1, page2);

	lock_page(page1);
	अगर (page1 != page2)
		lock_page(page2);
पूर्ण

/* Unlock two pages, being careful not to unlock the same page twice. */
अटल व्योम vfs_unlock_two_pages(काष्ठा page *page1, काष्ठा page *page2)
अणु
	unlock_page(page1);
	अगर (page1 != page2)
		unlock_page(page2);
पूर्ण

/*
 * Compare extents of two files to see अगर they are the same.
 * Caller must have locked both inodes to prevent ग_लिखो races.
 */
अटल पूर्णांक vfs_dedupe_file_range_compare(काष्ठा inode *src, loff_t srcoff,
					 काष्ठा inode *dest, loff_t destoff,
					 loff_t len, bool *is_same)
अणु
	loff_t src_poff;
	loff_t dest_poff;
	व्योम *src_addr;
	व्योम *dest_addr;
	काष्ठा page *src_page;
	काष्ठा page *dest_page;
	loff_t cmp_len;
	bool same;
	पूर्णांक error;

	error = -EINVAL;
	same = true;
	जबतक (len) अणु
		src_poff = srcoff & (PAGE_SIZE - 1);
		dest_poff = destoff & (PAGE_SIZE - 1);
		cmp_len = min(PAGE_SIZE - src_poff,
			      PAGE_SIZE - dest_poff);
		cmp_len = min(cmp_len, len);
		अगर (cmp_len <= 0)
			जाओ out_error;

		src_page = vfs_dedupe_get_page(src, srcoff);
		अगर (IS_ERR(src_page)) अणु
			error = PTR_ERR(src_page);
			जाओ out_error;
		पूर्ण
		dest_page = vfs_dedupe_get_page(dest, destoff);
		अगर (IS_ERR(dest_page)) अणु
			error = PTR_ERR(dest_page);
			put_page(src_page);
			जाओ out_error;
		पूर्ण

		vfs_lock_two_pages(src_page, dest_page);

		/*
		 * Now that we've locked both pages, make sure they're still
		 * mapped to the file data we're पूर्णांकerested in.  If not,
		 * someone is invalidating pages on us and we lose.
		 */
		अगर (!PageUptodate(src_page) || !PageUptodate(dest_page) ||
		    src_page->mapping != src->i_mapping ||
		    dest_page->mapping != dest->i_mapping) अणु
			same = false;
			जाओ unlock;
		पूर्ण

		src_addr = kmap_atomic(src_page);
		dest_addr = kmap_atomic(dest_page);

		flush_dcache_page(src_page);
		flush_dcache_page(dest_page);

		अगर (स_भेद(src_addr + src_poff, dest_addr + dest_poff, cmp_len))
			same = false;

		kunmap_atomic(dest_addr);
		kunmap_atomic(src_addr);
unlock:
		vfs_unlock_two_pages(src_page, dest_page);
		put_page(dest_page);
		put_page(src_page);

		अगर (!same)
			अवरोध;

		srcoff += cmp_len;
		destoff += cmp_len;
		len -= cmp_len;
	पूर्ण

	*is_same = same;
	वापस 0;

out_error:
	वापस error;
पूर्ण

/*
 * Check that the two inodes are eligible क्रम cloning, the ranges make
 * sense, and then flush all dirty data.  Caller must ensure that the
 * inodes have been locked against any other modअगरications.
 *
 * If there's an error, then the usual negative error code is वापसed.
 * Otherwise वापसs 0 with *len set to the request length.
 */
पूर्णांक generic_remap_file_range_prep(काष्ठा file *file_in, loff_t pos_in,
				  काष्ठा file *file_out, loff_t pos_out,
				  loff_t *len, अचिन्हित पूर्णांक remap_flags)
अणु
	काष्ठा inode *inode_in = file_inode(file_in);
	काष्ठा inode *inode_out = file_inode(file_out);
	bool same_inode = (inode_in == inode_out);
	पूर्णांक ret;

	/* Don't touch certain kinds of inodes */
	अगर (IS_IMMUTABLE(inode_out))
		वापस -EPERM;

	अगर (IS_SWAPखाता(inode_in) || IS_SWAPखाता(inode_out))
		वापस -ETXTBSY;

	/* Don't reflink dirs, pipes, sockets... */
	अगर (S_ISसूची(inode_in->i_mode) || S_ISसूची(inode_out->i_mode))
		वापस -EISसूची;
	अगर (!S_ISREG(inode_in->i_mode) || !S_ISREG(inode_out->i_mode))
		वापस -EINVAL;

	/* Zero length dedupe निकासs immediately; reflink goes to खातापूर्ण. */
	अगर (*len == 0) अणु
		loff_t isize = i_size_पढ़ो(inode_in);

		अगर ((remap_flags & REMAP_खाता_DEDUP) || pos_in == isize)
			वापस 0;
		अगर (pos_in > isize)
			वापस -EINVAL;
		*len = isize - pos_in;
		अगर (*len == 0)
			वापस 0;
	पूर्ण

	/* Check that we करोn't violate प्रणाली file offset limits. */
	ret = generic_remap_checks(file_in, pos_in, file_out, pos_out, len,
			remap_flags);
	अगर (ret)
		वापस ret;

	/* Wait क्रम the completion of any pending IOs on both files */
	inode_dio_रुको(inode_in);
	अगर (!same_inode)
		inode_dio_रुको(inode_out);

	ret = filemap_ग_लिखो_and_रुको_range(inode_in->i_mapping,
			pos_in, pos_in + *len - 1);
	अगर (ret)
		वापस ret;

	ret = filemap_ग_लिखो_and_रुको_range(inode_out->i_mapping,
			pos_out, pos_out + *len - 1);
	अगर (ret)
		वापस ret;

	/*
	 * Check that the extents are the same.
	 */
	अगर (remap_flags & REMAP_खाता_DEDUP) अणु
		bool		is_same = false;

		ret = vfs_dedupe_file_range_compare(inode_in, pos_in,
				inode_out, pos_out, *len, &is_same);
		अगर (ret)
			वापस ret;
		अगर (!is_same)
			वापस -EBADE;
	पूर्ण

	ret = generic_remap_check_len(inode_in, inode_out, pos_out, len,
			remap_flags);
	अगर (ret)
		वापस ret;

	/* If can't alter the file contents, we're करोne. */
	अगर (!(remap_flags & REMAP_खाता_DEDUP))
		ret = file_modअगरied(file_out);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(generic_remap_file_range_prep);

loff_t करो_clone_file_range(काष्ठा file *file_in, loff_t pos_in,
			   काष्ठा file *file_out, loff_t pos_out,
			   loff_t len, अचिन्हित पूर्णांक remap_flags)
अणु
	loff_t ret;

	WARN_ON_ONCE(remap_flags & REMAP_खाता_DEDUP);

	/*
	 * FICLONE/FICLONदुस्फल ioctls enक्रमce that src and dest files are on
	 * the same mount. Practically, they only need to be on the same file
	 * प्रणाली.
	 */
	अगर (file_inode(file_in)->i_sb != file_inode(file_out)->i_sb)
		वापस -EXDEV;

	ret = generic_file_rw_checks(file_in, file_out);
	अगर (ret < 0)
		वापस ret;

	अगर (!file_in->f_op->remap_file_range)
		वापस -EOPNOTSUPP;

	ret = remap_verअगरy_area(file_in, pos_in, len, false);
	अगर (ret)
		वापस ret;

	ret = remap_verअगरy_area(file_out, pos_out, len, true);
	अगर (ret)
		वापस ret;

	ret = file_in->f_op->remap_file_range(file_in, pos_in,
			file_out, pos_out, len, remap_flags);
	अगर (ret < 0)
		वापस ret;

	fsnotअगरy_access(file_in);
	fsnotअगरy_modअगरy(file_out);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(करो_clone_file_range);

loff_t vfs_clone_file_range(काष्ठा file *file_in, loff_t pos_in,
			    काष्ठा file *file_out, loff_t pos_out,
			    loff_t len, अचिन्हित पूर्णांक remap_flags)
अणु
	loff_t ret;

	file_start_ग_लिखो(file_out);
	ret = करो_clone_file_range(file_in, pos_in, file_out, pos_out, len,
				  remap_flags);
	file_end_ग_लिखो(file_out);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfs_clone_file_range);

/* Check whether we are allowed to dedupe the destination file */
अटल bool allow_file_dedupe(काष्ठा file *file)
अणु
	काष्ठा user_namespace *mnt_userns = file_mnt_user_ns(file);
	काष्ठा inode *inode = file_inode(file);

	अगर (capable(CAP_SYS_ADMIN))
		वापस true;
	अगर (file->f_mode & FMODE_WRITE)
		वापस true;
	अगर (uid_eq(current_fsuid(), i_uid_पूर्णांकo_mnt(mnt_userns, inode)))
		वापस true;
	अगर (!inode_permission(mnt_userns, inode, MAY_WRITE))
		वापस true;
	वापस false;
पूर्ण

loff_t vfs_dedupe_file_range_one(काष्ठा file *src_file, loff_t src_pos,
				 काष्ठा file *dst_file, loff_t dst_pos,
				 loff_t len, अचिन्हित पूर्णांक remap_flags)
अणु
	loff_t ret;

	WARN_ON_ONCE(remap_flags & ~(REMAP_खाता_DEDUP |
				     REMAP_खाता_CAN_SHORTEN));

	ret = mnt_want_ग_लिखो_file(dst_file);
	अगर (ret)
		वापस ret;

	/*
	 * This is redundant अगर called from vfs_dedupe_file_range(), but other
	 * callers need it and it's not perक्रमmance sesitive...
	 */
	ret = remap_verअगरy_area(src_file, src_pos, len, false);
	अगर (ret)
		जाओ out_drop_ग_लिखो;

	ret = remap_verअगरy_area(dst_file, dst_pos, len, true);
	अगर (ret)
		जाओ out_drop_ग_लिखो;

	ret = -EPERM;
	अगर (!allow_file_dedupe(dst_file))
		जाओ out_drop_ग_लिखो;

	ret = -EXDEV;
	अगर (src_file->f_path.mnt != dst_file->f_path.mnt)
		जाओ out_drop_ग_लिखो;

	ret = -EISसूची;
	अगर (S_ISसूची(file_inode(dst_file)->i_mode))
		जाओ out_drop_ग_लिखो;

	ret = -EINVAL;
	अगर (!dst_file->f_op->remap_file_range)
		जाओ out_drop_ग_लिखो;

	अगर (len == 0) अणु
		ret = 0;
		जाओ out_drop_ग_लिखो;
	पूर्ण

	ret = dst_file->f_op->remap_file_range(src_file, src_pos, dst_file,
			dst_pos, len, remap_flags | REMAP_खाता_DEDUP);
out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(dst_file);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfs_dedupe_file_range_one);

पूर्णांक vfs_dedupe_file_range(काष्ठा file *file, काष्ठा file_dedupe_range *same)
अणु
	काष्ठा file_dedupe_range_info *info;
	काष्ठा inode *src = file_inode(file);
	u64 off;
	u64 len;
	पूर्णांक i;
	पूर्णांक ret;
	u16 count = same->dest_count;
	loff_t deduped;

	अगर (!(file->f_mode & FMODE_READ))
		वापस -EINVAL;

	अगर (same->reserved1 || same->reserved2)
		वापस -EINVAL;

	off = same->src_offset;
	len = same->src_length;

	अगर (S_ISसूची(src->i_mode))
		वापस -EISसूची;

	अगर (!S_ISREG(src->i_mode))
		वापस -EINVAL;

	अगर (!file->f_op->remap_file_range)
		वापस -EOPNOTSUPP;

	ret = remap_verअगरy_area(file, off, len, false);
	अगर (ret < 0)
		वापस ret;
	ret = 0;

	अगर (off + len > i_size_पढ़ो(src))
		वापस -EINVAL;

	/* Arbitrary 1G limit on a single dedupe request, can be उठाओd. */
	len = min_t(u64, len, 1 << 30);

	/* pre-क्रमmat output fields to sane values */
	क्रम (i = 0; i < count; i++) अणु
		same->info[i].bytes_deduped = 0ULL;
		same->info[i].status = खाता_DEDUPE_RANGE_SAME;
	पूर्ण

	क्रम (i = 0, info = same->info; i < count; i++, info++) अणु
		काष्ठा fd dst_fd = fdget(info->dest_fd);
		काष्ठा file *dst_file = dst_fd.file;

		अगर (!dst_file) अणु
			info->status = -EBADF;
			जाओ next_loop;
		पूर्ण

		अगर (info->reserved) अणु
			info->status = -EINVAL;
			जाओ next_fdput;
		पूर्ण

		deduped = vfs_dedupe_file_range_one(file, off, dst_file,
						    info->dest_offset, len,
						    REMAP_खाता_CAN_SHORTEN);
		अगर (deduped == -EBADE)
			info->status = खाता_DEDUPE_RANGE_DIFFERS;
		अन्यथा अगर (deduped < 0)
			info->status = deduped;
		अन्यथा
			info->bytes_deduped = len;

next_fdput:
		fdput(dst_fd);
next_loop:
		अगर (fatal_संकेत_pending(current))
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfs_dedupe_file_range);
