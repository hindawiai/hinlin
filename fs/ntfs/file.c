<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * file.c - NTFS kernel file operations.  Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2015 Anton Altaparmakov and Tuxera Inc.
 */

#समावेश <linux/backing-dev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/swap.h>
#समावेश <linux/uपन.स>
#समावेश <linux/ग_लिखोback.h>

#समावेश <यंत्र/page.h>
#समावेश <linux/uaccess.h>

#समावेश "attrib.h"
#समावेश "bitmap.h"
#समावेश "inode.h"
#समावेश "debug.h"
#समावेश "lcnalloc.h"
#समावेश "malloc.h"
#समावेश "mft.h"
#समावेश "ntfs.h"

/**
 * ntfs_file_खोलो - called when an inode is about to be खोलोed
 * @vi:		inode to be खोलोed
 * @filp:	file काष्ठाure describing the inode
 *
 * Limit file size to the page cache limit on architectures where अचिन्हित दीर्घ
 * is 32-bits. This is the most we can करो क्रम now without overflowing the page
 * cache page index. Doing it this way means we करोn't run पूर्णांकo problems because
 * of existing too large files. It would be better to allow the user to पढ़ो
 * the beginning of the file but I करोubt very much anyone is going to hit this
 * check on a 32-bit architecture, so there is no poपूर्णांक in adding the extra
 * complनिकासy required to support this.
 *
 * On 64-bit architectures, the check is hopefully optimized away by the
 * compiler.
 *
 * After the check passes, just call generic_file_खोलो() to करो its work.
 */
अटल पूर्णांक ntfs_file_खोलो(काष्ठा inode *vi, काष्ठा file *filp)
अणु
	अगर (माप(अचिन्हित दीर्घ) < 8) अणु
		अगर (i_size_पढ़ो(vi) > MAX_LFS_खाताSIZE)
			वापस -EOVERFLOW;
	पूर्ण
	वापस generic_file_खोलो(vi, filp);
पूर्ण

#अगर_घोषित NTFS_RW

/**
 * ntfs_attr_extend_initialized - extend the initialized size of an attribute
 * @ni:			ntfs inode of the attribute to extend
 * @new_init_size:	requested new initialized size in bytes
 *
 * Extend the initialized size of an attribute described by the ntfs inode @ni
 * to @new_init_size bytes.  This involves zeroing any non-sparse space between
 * the old initialized size and @new_init_size both in the page cache and on
 * disk (अगर relevant complete pages are alपढ़ोy uptodate in the page cache then
 * these are simply marked dirty).
 *
 * As a side-effect, the file size (vfs inode->i_size) may be incremented as,
 * in the resident attribute हाल, it is tied to the initialized size and, in
 * the non-resident attribute हाल, it may not fall below the initialized size.
 *
 * Note that अगर the attribute is resident, we करो not need to touch the page
 * cache at all.  This is because अगर the page cache page is not uptodate we
 * bring it uptodate later, when करोing the ग_लिखो to the mft record since we
 * then alपढ़ोy have the page mapped.  And अगर the page is uptodate, the
 * non-initialized region will alपढ़ोy have been zeroed when the page was
 * brought uptodate and the region may in fact alपढ़ोy have been overwritten
 * with new data via mmap() based ग_लिखोs, so we cannot just zero it.  And since
 * POSIX specअगरies that the behaviour of resizing a file whilst it is mmap()ped
 * is unspecअगरied, we choose not to करो zeroing and thus we करो not need to touch
 * the page at all.  For a more detailed explanation see ntfs_truncate() in
 * fs/ntfs/inode.c.
 *
 * Return 0 on success and -त्रुटि_सं on error.  In the हाल that an error is
 * encountered it is possible that the initialized size will alपढ़ोy have been
 * incremented some way towards @new_init_size but it is guaranteed that अगर
 * this is the हाल, the necessary zeroing will also have happened and that all
 * metadata is self-consistent.
 *
 * Locking: i_mutex on the vfs inode corrseponsind to the ntfs inode @ni must be
 *	    held by the caller.
 */
अटल पूर्णांक ntfs_attr_extend_initialized(ntfs_inode *ni, स्थिर s64 new_init_size)
अणु
	s64 old_init_size;
	loff_t old_i_size;
	pgoff_t index, end_index;
	अचिन्हित दीर्घ flags;
	काष्ठा inode *vi = VFS_I(ni);
	ntfs_inode *base_ni;
	MFT_RECORD *m = शून्य;
	ATTR_RECORD *a;
	ntfs_attr_search_ctx *ctx = शून्य;
	काष्ठा address_space *mapping;
	काष्ठा page *page = शून्य;
	u8 *kattr;
	पूर्णांक err;
	u32 attr_len;

	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	old_init_size = ni->initialized_size;
	old_i_size = i_size_पढ़ो(vi);
	BUG_ON(new_init_size > ni->allocated_size);
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	ntfs_debug("Entering for i_ino 0x%lx, attribute type 0x%x, "
			"old_initialized_size 0x%llx, "
			"new_initialized_size 0x%llx, i_size 0x%llx.",
			vi->i_ino, (अचिन्हित)le32_to_cpu(ni->type),
			(अचिन्हित दीर्घ दीर्घ)old_init_size,
			(अचिन्हित दीर्घ दीर्घ)new_init_size, old_i_size);
	अगर (!NInoAttr(ni))
		base_ni = ni;
	अन्यथा
		base_ni = ni->ext.base_ntfs_ino;
	/* Use जाओ to reduce indentation and we need the label below anyway. */
	अगर (NInoNonResident(ni))
		जाओ करो_non_resident_extend;
	BUG_ON(old_init_size != old_i_size);
	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		m = शून्य;
		जाओ err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT)
			err = -EIO;
		जाओ err_out;
	पूर्ण
	m = ctx->mrec;
	a = ctx->attr;
	BUG_ON(a->non_resident);
	/* The total length of the attribute value. */
	attr_len = le32_to_cpu(a->data.resident.value_length);
	BUG_ON(old_i_size != (loff_t)attr_len);
	/*
	 * Do the zeroing in the mft record and update the attribute size in
	 * the mft record.
	 */
	kattr = (u8*)a + le16_to_cpu(a->data.resident.value_offset);
	स_रखो(kattr + attr_len, 0, new_init_size - attr_len);
	a->data.resident.value_length = cpu_to_le32((u32)new_init_size);
	/* Finally, update the sizes in the vfs and ntfs inodes. */
	ग_लिखो_lock_irqsave(&ni->size_lock, flags);
	i_size_ग_लिखो(vi, new_init_size);
	ni->initialized_size = new_init_size;
	ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
	जाओ करोne;
करो_non_resident_extend:
	/*
	 * If the new initialized size @new_init_size exceeds the current file
	 * size (vfs inode->i_size), we need to extend the file size to the
	 * new initialized size.
	 */
	अगर (new_init_size > old_i_size) अणु
		m = map_mft_record(base_ni);
		अगर (IS_ERR(m)) अणु
			err = PTR_ERR(m);
			m = शून्य;
			जाओ err_out;
		पूर्ण
		ctx = ntfs_attr_get_search_ctx(base_ni, m);
		अगर (unlikely(!ctx)) अणु
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण
		err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
				CASE_SENSITIVE, 0, शून्य, 0, ctx);
		अगर (unlikely(err)) अणु
			अगर (err == -ENOENT)
				err = -EIO;
			जाओ err_out;
		पूर्ण
		m = ctx->mrec;
		a = ctx->attr;
		BUG_ON(!a->non_resident);
		BUG_ON(old_i_size != (loff_t)
				sle64_to_cpu(a->data.non_resident.data_size));
		a->data.non_resident.data_size = cpu_to_sle64(new_init_size);
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		mark_mft_record_dirty(ctx->ntfs_ino);
		/* Update the file size in the vfs inode. */
		i_size_ग_लिखो(vi, new_init_size);
		ntfs_attr_put_search_ctx(ctx);
		ctx = शून्य;
		unmap_mft_record(base_ni);
		m = शून्य;
	पूर्ण
	mapping = vi->i_mapping;
	index = old_init_size >> PAGE_SHIFT;
	end_index = (new_init_size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	करो अणु
		/*
		 * Read the page.  If the page is not present, this will zero
		 * the uninitialized regions क्रम us.
		 */
		page = पढ़ो_mapping_page(mapping, index, शून्य);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			जाओ init_err_out;
		पूर्ण
		अगर (unlikely(PageError(page))) अणु
			put_page(page);
			err = -EIO;
			जाओ init_err_out;
		पूर्ण
		/*
		 * Update the initialized size in the ntfs inode.  This is
		 * enough to make ntfs_ग_लिखोpage() work.
		 */
		ग_लिखो_lock_irqsave(&ni->size_lock, flags);
		ni->initialized_size = (s64)(index + 1) << PAGE_SHIFT;
		अगर (ni->initialized_size > new_init_size)
			ni->initialized_size = new_init_size;
		ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
		/* Set the page dirty so it माला_लो written out. */
		set_page_dirty(page);
		put_page(page);
		/*
		 * Play nice with the vm and the rest of the प्रणाली.  This is
		 * very much needed as we can potentially be modअगरying the
		 * initialised size from a very small value to a really huge
		 * value, e.g.
		 *	f = खोलो(somefile, O_TRUNC);
		 *	truncate(f, 10GiB);
		 *	seek(f, 10GiB);
		 *	ग_लिखो(f, 1);
		 * And this would mean we would be marking dirty hundreds of
		 * thousands of pages or as in the above example more than
		 * two and a half million pages!
		 *
		 * TODO: For sparse pages could optimize this workload by using
		 * the FsMisc / MiscFs page bit as a "PageIsSparse" bit.  This
		 * would be set in पढ़ोpage क्रम sparse pages and here we would
		 * not need to mark dirty any pages which have this bit set.
		 * The only caveat is that we have to clear the bit everywhere
		 * where we allocate any clusters that lie in the page or that
		 * contain the page.
		 *
		 * TODO: An even greater optimization would be क्रम us to only
		 * call पढ़ोpage() on pages which are not in sparse regions as
		 * determined from the runlist.  This would greatly reduce the
		 * number of pages we पढ़ो and make dirty in the हाल of sparse
		 * files.
		 */
		balance_dirty_pages_ratelimited(mapping);
		cond_resched();
	पूर्ण जबतक (++index < end_index);
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	BUG_ON(ni->initialized_size != new_init_size);
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	/* Now bring in sync the initialized_size in the mft record. */
	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		m = शून्य;
		जाओ init_err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ init_err_out;
	पूर्ण
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT)
			err = -EIO;
		जाओ init_err_out;
	पूर्ण
	m = ctx->mrec;
	a = ctx->attr;
	BUG_ON(!a->non_resident);
	a->data.non_resident.initialized_size = cpu_to_sle64(new_init_size);
करोne:
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(base_ni);
	ntfs_debug("Done, initialized_size 0x%llx, i_size 0x%llx.",
			(अचिन्हित दीर्घ दीर्घ)new_init_size, i_size_पढ़ो(vi));
	वापस 0;
init_err_out:
	ग_लिखो_lock_irqsave(&ni->size_lock, flags);
	ni->initialized_size = old_init_size;
	ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
err_out:
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(base_ni);
	ntfs_debug("Failed.  Returning error code %i.", err);
	वापस err;
पूर्ण

अटल sमाप_प्रकार ntfs_prepare_file_क्रम_ग_लिखो(काष्ठा kiocb *iocb,
		काष्ठा iov_iter *from)
अणु
	loff_t pos;
	s64 end, ll;
	sमाप_प्रकार err;
	अचिन्हित दीर्घ flags;
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *vi = file_inode(file);
	ntfs_inode *ni = NTFS_I(vi);
	ntfs_volume *vol = ni->vol;

	ntfs_debug("Entering for i_ino 0x%lx, attribute type 0x%x, pos "
			"0x%llx, count 0x%zx.", vi->i_ino,
			(अचिन्हित)le32_to_cpu(ni->type),
			(अचिन्हित दीर्घ दीर्घ)iocb->ki_pos,
			iov_iter_count(from));
	err = generic_ग_लिखो_checks(iocb, from);
	अगर (unlikely(err <= 0))
		जाओ out;
	/*
	 * All checks have passed.  Beक्रमe we start करोing any writing we want
	 * to पात any totally illegal ग_लिखोs.
	 */
	BUG_ON(NInoMstProtected(ni));
	BUG_ON(ni->type != AT_DATA);
	/* If file is encrypted, deny access, just like NT4. */
	अगर (NInoEncrypted(ni)) अणु
		/* Only $DATA attributes can be encrypted. */
		/*
		 * Reminder क्रम later: Encrypted files are _always_
		 * non-resident so that the content can always be encrypted.
		 */
		ntfs_debug("Denying write access to encrypted file.");
		err = -EACCES;
		जाओ out;
	पूर्ण
	अगर (NInoCompressed(ni)) अणु
		/* Only unnamed $DATA attribute can be compressed. */
		BUG_ON(ni->name_len);
		/*
		 * Reminder क्रम later: If resident, the data is not actually
		 * compressed.  Only on the चयन to non-resident करोes
		 * compression kick in.  This is in contrast to encrypted files
		 * (see above).
		 */
		ntfs_error(vi->i_sb, "Writing to compressed files is not "
				"implemented yet.  Sorry.");
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	err = file_हटाओ_privs(file);
	अगर (unlikely(err))
		जाओ out;
	/*
	 * Our ->update_समय method always succeeds thus file_update_समय()
	 * cannot fail either so there is no need to check the वापस code.
	 */
	file_update_समय(file);
	pos = iocb->ki_pos;
	/* The first byte after the last cluster being written to. */
	end = (pos + iov_iter_count(from) + vol->cluster_size_mask) &
			~(u64)vol->cluster_size_mask;
	/*
	 * If the ग_लिखो goes beyond the allocated size, extend the allocation
	 * to cover the whole of the ग_लिखो, rounded up to the nearest cluster.
	 */
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	ll = ni->allocated_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	अगर (end > ll) अणु
		/*
		 * Extend the allocation without changing the data size.
		 *
		 * Note we ensure the allocation is big enough to at least
		 * ग_लिखो some data but we करो not require the allocation to be
		 * complete, i.e. it may be partial.
		 */
		ll = ntfs_attr_extend_allocation(ni, end, -1, pos);
		अगर (likely(ll >= 0)) अणु
			BUG_ON(pos >= ll);
			/* If the extension was partial truncate the ग_लिखो. */
			अगर (end > ll) अणु
				ntfs_debug("Truncating write to inode 0x%lx, "
						"attribute type 0x%x, because "
						"the allocation was only "
						"partially extended.",
						vi->i_ino, (अचिन्हित)
						le32_to_cpu(ni->type));
				iov_iter_truncate(from, ll - pos);
			पूर्ण
		पूर्ण अन्यथा अणु
			err = ll;
			पढ़ो_lock_irqsave(&ni->size_lock, flags);
			ll = ni->allocated_size;
			पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
			/* Perक्रमm a partial ग_लिखो अगर possible or fail. */
			अगर (pos < ll) अणु
				ntfs_debug("Truncating write to inode 0x%lx "
						"attribute type 0x%x, because "
						"extending the allocation "
						"failed (error %d).",
						vi->i_ino, (अचिन्हित)
						le32_to_cpu(ni->type),
						(पूर्णांक)-err);
				iov_iter_truncate(from, ll - pos);
			पूर्ण अन्यथा अणु
				अगर (err != -ENOSPC)
					ntfs_error(vi->i_sb, "Cannot perform "
							"write to inode "
							"0x%lx, attribute "
							"type 0x%x, because "
							"extending the "
							"allocation failed "
							"(error %ld).",
							vi->i_ino, (अचिन्हित)
							le32_to_cpu(ni->type),
							(दीर्घ)-err);
				अन्यथा
					ntfs_debug("Cannot perform write to "
							"inode 0x%lx, "
							"attribute type 0x%x, "
							"because there is not "
							"space left.",
							vi->i_ino, (अचिन्हित)
							le32_to_cpu(ni->type));
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * If the ग_लिखो starts beyond the initialized size, extend it up to the
	 * beginning of the ग_लिखो and initialize all non-sparse space between
	 * the old initialized size and the new one.  This स्वतःmatically also
	 * increments the vfs inode->i_size to keep it above or equal to the
	 * initialized_size.
	 */
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	ll = ni->initialized_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	अगर (pos > ll) अणु
		/*
		 * Wait क्रम ongoing direct i/o to complete beक्रमe proceeding.
		 * New direct i/o cannot start as we hold i_mutex.
		 */
		inode_dio_रुको(vi);
		err = ntfs_attr_extend_initialized(ni, pos);
		अगर (unlikely(err < 0))
			ntfs_error(vi->i_sb, "Cannot perform write to inode "
					"0x%lx, attribute type 0x%x, because "
					"extending the initialized size "
					"failed (error %d).", vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type),
					(पूर्णांक)-err);
	पूर्ण
out:
	वापस err;
पूर्ण

/**
 * __ntfs_grab_cache_pages - obtain a number of locked pages
 * @mapping:	address space mapping from which to obtain page cache pages
 * @index:	starting index in @mapping at which to begin obtaining pages
 * @nr_pages:	number of page cache pages to obtain
 * @pages:	array of pages in which to वापस the obtained page cache pages
 * @cached_page: allocated but as yet unused page
 *
 * Obtain @nr_pages locked page cache pages from the mapping @mapping and
 * starting at index @index.
 *
 * If a page is newly created, add it to lru list
 *
 * Note, the page locks are obtained in ascending page index order.
 */
अटल अंतरभूत पूर्णांक __ntfs_grab_cache_pages(काष्ठा address_space *mapping,
		pgoff_t index, स्थिर अचिन्हित nr_pages, काष्ठा page **pages,
		काष्ठा page **cached_page)
अणु
	पूर्णांक err, nr;

	BUG_ON(!nr_pages);
	err = nr = 0;
	करो अणु
		pages[nr] = find_get_page_flags(mapping, index, FGP_LOCK |
				FGP_ACCESSED);
		अगर (!pages[nr]) अणु
			अगर (!*cached_page) अणु
				*cached_page = page_cache_alloc(mapping);
				अगर (unlikely(!*cached_page)) अणु
					err = -ENOMEM;
					जाओ err_out;
				पूर्ण
			पूर्ण
			err = add_to_page_cache_lru(*cached_page, mapping,
				   index,
				   mapping_gfp_स्थिरraपूर्णांक(mapping, GFP_KERNEL));
			अगर (unlikely(err)) अणु
				अगर (err == -EEXIST)
					जारी;
				जाओ err_out;
			पूर्ण
			pages[nr] = *cached_page;
			*cached_page = शून्य;
		पूर्ण
		index++;
		nr++;
	पूर्ण जबतक (nr < nr_pages);
out:
	वापस err;
err_out:
	जबतक (nr > 0) अणु
		unlock_page(pages[--nr]);
		put_page(pages[nr]);
	पूर्ण
	जाओ out;
पूर्ण

अटल अंतरभूत पूर्णांक ntfs_submit_bh_क्रम_पढ़ो(काष्ठा buffer_head *bh)
अणु
	lock_buffer(bh);
	get_bh(bh);
	bh->b_end_io = end_buffer_पढ़ो_sync;
	वापस submit_bh(REQ_OP_READ, 0, bh);
पूर्ण

/**
 * ntfs_prepare_pages_क्रम_non_resident_ग_लिखो - prepare pages क्रम receiving data
 * @pages:	array of destination pages
 * @nr_pages:	number of pages in @pages
 * @pos:	byte position in file at which the ग_लिखो begins
 * @bytes:	number of bytes to be written
 *
 * This is called क्रम non-resident attributes from ntfs_file_buffered_ग_लिखो()
 * with i_mutex held on the inode (@pages[0]->mapping->host).  There are
 * @nr_pages pages in @pages which are locked but not kmap()ped.  The source
 * data has not yet been copied पूर्णांकo the @pages.
 * 
 * Need to fill any holes with actual clusters, allocate buffers अगर necessary,
 * ensure all the buffers are mapped, and bring uptodate any buffers that are
 * only partially being written to.
 *
 * If @nr_pages is greater than one, we are guaranteed that the cluster size is
 * greater than PAGE_SIZE, that all pages in @pages are entirely inside
 * the same cluster and that they are the entirety of that cluster, and that
 * the cluster is sparse, i.e. we need to allocate a cluster to fill the hole.
 *
 * i_size is not to be modअगरied yet.
 *
 * Return 0 on success or -त्रुटि_सं on error.
 */
अटल पूर्णांक ntfs_prepare_pages_क्रम_non_resident_ग_लिखो(काष्ठा page **pages,
		अचिन्हित nr_pages, s64 pos, माप_प्रकार bytes)
अणु
	VCN vcn, highest_vcn = 0, cpos, cend, bh_cpos, bh_cend;
	LCN lcn;
	s64 bh_pos, vcn_len, end, initialized_size;
	sector_t lcn_block;
	काष्ठा page *page;
	काष्ठा inode *vi;
	ntfs_inode *ni, *base_ni = शून्य;
	ntfs_volume *vol;
	runlist_element *rl, *rl2;
	काष्ठा buffer_head *bh, *head, *रुको[2], **रुको_bh = रुको;
	ntfs_attr_search_ctx *ctx = शून्य;
	MFT_RECORD *m = शून्य;
	ATTR_RECORD *a = शून्य;
	अचिन्हित दीर्घ flags;
	u32 attr_rec_len = 0;
	अचिन्हित blocksize, u;
	पूर्णांक err, mp_size;
	bool rl_ग_लिखो_locked, was_hole, is_retry;
	अचिन्हित अक्षर blocksize_bits;
	काष्ठा अणु
		u8 runlist_merged:1;
		u8 mft_attr_mapped:1;
		u8 mp_rebuilt:1;
		u8 attr_चयनed:1;
	पूर्ण status = अणु 0, 0, 0, 0 पूर्ण;

	BUG_ON(!nr_pages);
	BUG_ON(!pages);
	BUG_ON(!*pages);
	vi = pages[0]->mapping->host;
	ni = NTFS_I(vi);
	vol = ni->vol;
	ntfs_debug("Entering for inode 0x%lx, attribute type 0x%x, start page "
			"index 0x%lx, nr_pages 0x%x, pos 0x%llx, bytes 0x%zx.",
			vi->i_ino, ni->type, pages[0]->index, nr_pages,
			(दीर्घ दीर्घ)pos, bytes);
	blocksize = vol->sb->s_blocksize;
	blocksize_bits = vol->sb->s_blocksize_bits;
	u = 0;
	करो अणु
		page = pages[u];
		BUG_ON(!page);
		/*
		 * create_empty_buffers() will create uptodate/dirty buffers अगर
		 * the page is uptodate/dirty.
		 */
		अगर (!page_has_buffers(page)) अणु
			create_empty_buffers(page, blocksize, 0);
			अगर (unlikely(!page_has_buffers(page)))
				वापस -ENOMEM;
		पूर्ण
	पूर्ण जबतक (++u < nr_pages);
	rl_ग_लिखो_locked = false;
	rl = शून्य;
	err = 0;
	vcn = lcn = -1;
	vcn_len = 0;
	lcn_block = -1;
	was_hole = false;
	cpos = pos >> vol->cluster_size_bits;
	end = pos + bytes;
	cend = (end + vol->cluster_size - 1) >> vol->cluster_size_bits;
	/*
	 * Loop over each page and क्रम each page over each buffer.  Use जाओ to
	 * reduce indentation.
	 */
	u = 0;
करो_next_page:
	page = pages[u];
	bh_pos = (s64)page->index << PAGE_SHIFT;
	bh = head = page_buffers(page);
	करो अणु
		VCN cdelta;
		s64 bh_end;
		अचिन्हित bh_cofs;

		/* Clear buffer_new on all buffers to reinitialise state. */
		अगर (buffer_new(bh))
			clear_buffer_new(bh);
		bh_end = bh_pos + blocksize;
		bh_cpos = bh_pos >> vol->cluster_size_bits;
		bh_cofs = bh_pos & vol->cluster_size_mask;
		अगर (buffer_mapped(bh)) अणु
			/*
			 * The buffer is alपढ़ोy mapped.  If it is uptodate,
			 * ignore it.
			 */
			अगर (buffer_uptodate(bh))
				जारी;
			/*
			 * The buffer is not uptodate.  If the page is uptodate
			 * set the buffer uptodate and otherwise ignore it.
			 */
			अगर (PageUptodate(page)) अणु
				set_buffer_uptodate(bh);
				जारी;
			पूर्ण
			/*
			 * Neither the page nor the buffer are uptodate.  If
			 * the buffer is only partially being written to, we
			 * need to पढ़ो it in beक्रमe the ग_लिखो, i.e. now.
			 */
			अगर ((bh_pos < pos && bh_end > pos) ||
					(bh_pos < end && bh_end > end)) अणु
				/*
				 * If the buffer is fully or partially within
				 * the initialized size, करो an actual पढ़ो.
				 * Otherwise, simply zero the buffer.
				 */
				पढ़ो_lock_irqsave(&ni->size_lock, flags);
				initialized_size = ni->initialized_size;
				पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
				अगर (bh_pos < initialized_size) अणु
					ntfs_submit_bh_क्रम_पढ़ो(bh);
					*रुको_bh++ = bh;
				पूर्ण अन्यथा अणु
					zero_user(page, bh_offset(bh),
							blocksize);
					set_buffer_uptodate(bh);
				पूर्ण
			पूर्ण
			जारी;
		पूर्ण
		/* Unmapped buffer.  Need to map it. */
		bh->b_bdev = vol->sb->s_bdev;
		/*
		 * If the current buffer is in the same clusters as the map
		 * cache, there is no need to check the runlist again.  The
		 * map cache is made up of @vcn, which is the first cached file
		 * cluster, @vcn_len which is the number of cached file
		 * clusters, @lcn is the device cluster corresponding to @vcn,
		 * and @lcn_block is the block number corresponding to @lcn.
		 */
		cdelta = bh_cpos - vcn;
		अगर (likely(!cdelta || (cdelta > 0 && cdelta < vcn_len))) अणु
map_buffer_cached:
			BUG_ON(lcn < 0);
			bh->b_blocknr = lcn_block +
					(cdelta << (vol->cluster_size_bits -
					blocksize_bits)) +
					(bh_cofs >> blocksize_bits);
			set_buffer_mapped(bh);
			/*
			 * If the page is uptodate so is the buffer.  If the
			 * buffer is fully outside the ग_लिखो, we ignore it अगर
			 * it was alपढ़ोy allocated and we mark it dirty so it
			 * माला_लो written out अगर we allocated it.  On the other
			 * hand, अगर we allocated the buffer but we are not
			 * marking it dirty we set buffer_new so we can करो
			 * error recovery.
			 */
			अगर (PageUptodate(page)) अणु
				अगर (!buffer_uptodate(bh))
					set_buffer_uptodate(bh);
				अगर (unlikely(was_hole)) अणु
					/* We allocated the buffer. */
					clean_bdev_bh_alias(bh);
					अगर (bh_end <= pos || bh_pos >= end)
						mark_buffer_dirty(bh);
					अन्यथा
						set_buffer_new(bh);
				पूर्ण
				जारी;
			पूर्ण
			/* Page is _not_ uptodate. */
			अगर (likely(!was_hole)) अणु
				/*
				 * Buffer was alपढ़ोy allocated.  If it is not
				 * uptodate and is only partially being written
				 * to, we need to पढ़ो it in beक्रमe the ग_लिखो,
				 * i.e. now.
				 */
				अगर (!buffer_uptodate(bh) && bh_pos < end &&
						bh_end > pos &&
						(bh_pos < pos ||
						bh_end > end)) अणु
					/*
					 * If the buffer is fully or partially
					 * within the initialized size, करो an
					 * actual पढ़ो.  Otherwise, simply zero
					 * the buffer.
					 */
					पढ़ो_lock_irqsave(&ni->size_lock,
							flags);
					initialized_size = ni->initialized_size;
					पढ़ो_unlock_irqrestore(&ni->size_lock,
							flags);
					अगर (bh_pos < initialized_size) अणु
						ntfs_submit_bh_क्रम_पढ़ो(bh);
						*रुको_bh++ = bh;
					पूर्ण अन्यथा अणु
						zero_user(page, bh_offset(bh),
								blocksize);
						set_buffer_uptodate(bh);
					पूर्ण
				पूर्ण
				जारी;
			पूर्ण
			/* We allocated the buffer. */
			clean_bdev_bh_alias(bh);
			/*
			 * If the buffer is fully outside the ग_लिखो, zero it,
			 * set it uptodate, and mark it dirty so it माला_लो
			 * written out.  If it is partially being written to,
			 * zero region surrounding the ग_लिखो but leave it to
			 * commit ग_लिखो to करो anything अन्यथा.  Finally, अगर the
			 * buffer is fully being overwritten, करो nothing.
			 */
			अगर (bh_end <= pos || bh_pos >= end) अणु
				अगर (!buffer_uptodate(bh)) अणु
					zero_user(page, bh_offset(bh),
							blocksize);
					set_buffer_uptodate(bh);
				पूर्ण
				mark_buffer_dirty(bh);
				जारी;
			पूर्ण
			set_buffer_new(bh);
			अगर (!buffer_uptodate(bh) &&
					(bh_pos < pos || bh_end > end)) अणु
				u8 *kaddr;
				अचिन्हित pofs;
					
				kaddr = kmap_atomic(page);
				अगर (bh_pos < pos) अणु
					pofs = bh_pos & ~PAGE_MASK;
					स_रखो(kaddr + pofs, 0, pos - bh_pos);
				पूर्ण
				अगर (bh_end > end) अणु
					pofs = end & ~PAGE_MASK;
					स_रखो(kaddr + pofs, 0, bh_end - end);
				पूर्ण
				kunmap_atomic(kaddr);
				flush_dcache_page(page);
			पूर्ण
			जारी;
		पूर्ण
		/*
		 * Slow path: this is the first buffer in the cluster.  If it
		 * is outside allocated size and is not uptodate, zero it and
		 * set it uptodate.
		 */
		पढ़ो_lock_irqsave(&ni->size_lock, flags);
		initialized_size = ni->allocated_size;
		पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
		अगर (bh_pos > initialized_size) अणु
			अगर (PageUptodate(page)) अणु
				अगर (!buffer_uptodate(bh))
					set_buffer_uptodate(bh);
			पूर्ण अन्यथा अगर (!buffer_uptodate(bh)) अणु
				zero_user(page, bh_offset(bh), blocksize);
				set_buffer_uptodate(bh);
			पूर्ण
			जारी;
		पूर्ण
		is_retry = false;
		अगर (!rl) अणु
			करोwn_पढ़ो(&ni->runlist.lock);
retry_remap:
			rl = ni->runlist.rl;
		पूर्ण
		अगर (likely(rl != शून्य)) अणु
			/* Seek to element containing target cluster. */
			जबतक (rl->length && rl[1].vcn <= bh_cpos)
				rl++;
			lcn = ntfs_rl_vcn_to_lcn(rl, bh_cpos);
			अगर (likely(lcn >= 0)) अणु
				/*
				 * Successful remap, setup the map cache and
				 * use that to deal with the buffer.
				 */
				was_hole = false;
				vcn = bh_cpos;
				vcn_len = rl[1].vcn - vcn;
				lcn_block = lcn << (vol->cluster_size_bits -
						blocksize_bits);
				cdelta = 0;
				/*
				 * If the number of reमुख्यing clusters touched
				 * by the ग_लिखो is smaller or equal to the
				 * number of cached clusters, unlock the
				 * runlist as the map cache will be used from
				 * now on.
				 */
				अगर (likely(vcn + vcn_len >= cend)) अणु
					अगर (rl_ग_लिखो_locked) अणु
						up_ग_लिखो(&ni->runlist.lock);
						rl_ग_लिखो_locked = false;
					पूर्ण अन्यथा
						up_पढ़ो(&ni->runlist.lock);
					rl = शून्य;
				पूर्ण
				जाओ map_buffer_cached;
			पूर्ण
		पूर्ण अन्यथा
			lcn = LCN_RL_NOT_MAPPED;
		/*
		 * If it is not a hole and not out of bounds, the runlist is
		 * probably unmapped so try to map it now.
		 */
		अगर (unlikely(lcn != LCN_HOLE && lcn != LCN_ENOENT)) अणु
			अगर (likely(!is_retry && lcn == LCN_RL_NOT_MAPPED)) अणु
				/* Attempt to map runlist. */
				अगर (!rl_ग_लिखो_locked) अणु
					/*
					 * We need the runlist locked क्रम
					 * writing, so अगर it is locked क्रम
					 * पढ़ोing relock it now and retry in
					 * हाल it changed whilst we dropped
					 * the lock.
					 */
					up_पढ़ो(&ni->runlist.lock);
					करोwn_ग_लिखो(&ni->runlist.lock);
					rl_ग_लिखो_locked = true;
					जाओ retry_remap;
				पूर्ण
				err = ntfs_map_runlist_nolock(ni, bh_cpos,
						शून्य);
				अगर (likely(!err)) अणु
					is_retry = true;
					जाओ retry_remap;
				पूर्ण
				/*
				 * If @vcn is out of bounds, pretend @lcn is
				 * LCN_ENOENT.  As दीर्घ as the buffer is out
				 * of bounds this will work fine.
				 */
				अगर (err == -ENOENT) अणु
					lcn = LCN_ENOENT;
					err = 0;
					जाओ rl_not_mapped_enoent;
				पूर्ण
			पूर्ण अन्यथा
				err = -EIO;
			/* Failed to map the buffer, even after retrying. */
			bh->b_blocknr = -1;
			ntfs_error(vol->sb, "Failed to write to inode 0x%lx, "
					"attribute type 0x%x, vcn 0x%llx, "
					"vcn offset 0x%x, because its "
					"location on disk could not be "
					"determined%s (error code %i).",
					ni->mft_no, ni->type,
					(अचिन्हित दीर्घ दीर्घ)bh_cpos,
					(अचिन्हित)bh_pos &
					vol->cluster_size_mask,
					is_retry ? " even after retrying" : "",
					err);
			अवरोध;
		पूर्ण
rl_not_mapped_enoent:
		/*
		 * The buffer is in a hole or out of bounds.  We need to fill
		 * the hole, unless the buffer is in a cluster which is not
		 * touched by the ग_लिखो, in which हाल we just leave the buffer
		 * unmapped.  This can only happen when the cluster size is
		 * less than the page cache size.
		 */
		अगर (unlikely(vol->cluster_size < PAGE_SIZE)) अणु
			bh_cend = (bh_end + vol->cluster_size - 1) >>
					vol->cluster_size_bits;
			अगर ((bh_cend <= cpos || bh_cpos >= cend)) अणु
				bh->b_blocknr = -1;
				/*
				 * If the buffer is uptodate we skip it.  If it
				 * is not but the page is uptodate, we can set
				 * the buffer uptodate.  If the page is not
				 * uptodate, we can clear the buffer and set it
				 * uptodate.  Whether this is worthजबतक is
				 * debatable and this could be हटाओd.
				 */
				अगर (PageUptodate(page)) अणु
					अगर (!buffer_uptodate(bh))
						set_buffer_uptodate(bh);
				पूर्ण अन्यथा अगर (!buffer_uptodate(bh)) अणु
					zero_user(page, bh_offset(bh),
						blocksize);
					set_buffer_uptodate(bh);
				पूर्ण
				जारी;
			पूर्ण
		पूर्ण
		/*
		 * Out of bounds buffer is invalid अगर it was not really out of
		 * bounds.
		 */
		BUG_ON(lcn != LCN_HOLE);
		/*
		 * We need the runlist locked क्रम writing, so अगर it is locked
		 * क्रम पढ़ोing relock it now and retry in हाल it changed
		 * whilst we dropped the lock.
		 */
		BUG_ON(!rl);
		अगर (!rl_ग_लिखो_locked) अणु
			up_पढ़ो(&ni->runlist.lock);
			करोwn_ग_लिखो(&ni->runlist.lock);
			rl_ग_लिखो_locked = true;
			जाओ retry_remap;
		पूर्ण
		/* Find the previous last allocated cluster. */
		BUG_ON(rl->lcn != LCN_HOLE);
		lcn = -1;
		rl2 = rl;
		जबतक (--rl2 >= ni->runlist.rl) अणु
			अगर (rl2->lcn >= 0) अणु
				lcn = rl2->lcn + rl2->length;
				अवरोध;
			पूर्ण
		पूर्ण
		rl2 = ntfs_cluster_alloc(vol, bh_cpos, 1, lcn, DATA_ZONE,
				false);
		अगर (IS_ERR(rl2)) अणु
			err = PTR_ERR(rl2);
			ntfs_debug("Failed to allocate cluster, error code %i.",
					err);
			अवरोध;
		पूर्ण
		lcn = rl2->lcn;
		rl = ntfs_runlists_merge(ni->runlist.rl, rl2);
		अगर (IS_ERR(rl)) अणु
			err = PTR_ERR(rl);
			अगर (err != -ENOMEM)
				err = -EIO;
			अगर (ntfs_cluster_मुक्त_from_rl(vol, rl2)) अणु
				ntfs_error(vol->sb, "Failed to release "
						"allocated cluster in error "
						"code path.  Run chkdsk to "
						"recover the lost cluster.");
				NVolSetErrors(vol);
			पूर्ण
			ntfs_मुक्त(rl2);
			अवरोध;
		पूर्ण
		ni->runlist.rl = rl;
		status.runlist_merged = 1;
		ntfs_debug("Allocated cluster, lcn 0x%llx.",
				(अचिन्हित दीर्घ दीर्घ)lcn);
		/* Map and lock the mft record and get the attribute record. */
		अगर (!NInoAttr(ni))
			base_ni = ni;
		अन्यथा
			base_ni = ni->ext.base_ntfs_ino;
		m = map_mft_record(base_ni);
		अगर (IS_ERR(m)) अणु
			err = PTR_ERR(m);
			अवरोध;
		पूर्ण
		ctx = ntfs_attr_get_search_ctx(base_ni, m);
		अगर (unlikely(!ctx)) अणु
			err = -ENOMEM;
			unmap_mft_record(base_ni);
			अवरोध;
		पूर्ण
		status.mft_attr_mapped = 1;
		err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
				CASE_SENSITIVE, bh_cpos, शून्य, 0, ctx);
		अगर (unlikely(err)) अणु
			अगर (err == -ENOENT)
				err = -EIO;
			अवरोध;
		पूर्ण
		m = ctx->mrec;
		a = ctx->attr;
		/*
		 * Find the runlist element with which the attribute extent
		 * starts.  Note, we cannot use the _attr_ version because we
		 * have mapped the mft record.  That is ok because we know the
		 * runlist fragment must be mapped alपढ़ोy to have ever gotten
		 * here, so we can just use the _rl_ version.
		 */
		vcn = sle64_to_cpu(a->data.non_resident.lowest_vcn);
		rl2 = ntfs_rl_find_vcn_nolock(rl, vcn);
		BUG_ON(!rl2);
		BUG_ON(!rl2->length);
		BUG_ON(rl2->lcn < LCN_HOLE);
		highest_vcn = sle64_to_cpu(a->data.non_resident.highest_vcn);
		/*
		 * If @highest_vcn is zero, calculate the real highest_vcn
		 * (which can really be zero).
		 */
		अगर (!highest_vcn)
			highest_vcn = (sle64_to_cpu(
					a->data.non_resident.allocated_size) >>
					vol->cluster_size_bits) - 1;
		/*
		 * Determine the size of the mapping pairs array क्रम the new
		 * extent, i.e. the old extent with the hole filled.
		 */
		mp_size = ntfs_get_size_क्रम_mapping_pairs(vol, rl2, vcn,
				highest_vcn);
		अगर (unlikely(mp_size <= 0)) अणु
			अगर (!(err = mp_size))
				err = -EIO;
			ntfs_debug("Failed to get size for mapping pairs "
					"array, error code %i.", err);
			अवरोध;
		पूर्ण
		/*
		 * Resize the attribute record to fit the new mapping pairs
		 * array.
		 */
		attr_rec_len = le32_to_cpu(a->length);
		err = ntfs_attr_record_resize(m, a, mp_size + le16_to_cpu(
				a->data.non_resident.mapping_pairs_offset));
		अगर (unlikely(err)) अणु
			BUG_ON(err != -ENOSPC);
			// TODO: Deal with this by using the current attribute
			// and fill it with as much of the mapping pairs
			// array as possible.  Then loop over each attribute
			// extent rewriting the mapping pairs arrays as we go
			// aदीर्घ and अगर when we reach the end we have not
			// enough space, try to resize the last attribute
			// extent and अगर even that fails, add a new attribute
			// extent.
			// We could also try to resize at each step in the hope
			// that we will not need to reग_लिखो every single extent.
			// Note, we may need to decompress some extents to fill
			// the runlist as we are walking the extents...
			ntfs_error(vol->sb, "Not enough space in the mft "
					"record for the extended attribute "
					"record.  This case is not "
					"implemented yet.");
			err = -EOPNOTSUPP;
			अवरोध ;
		पूर्ण
		status.mp_rebuilt = 1;
		/*
		 * Generate the mapping pairs array directly पूर्णांकo the attribute
		 * record.
		 */
		err = ntfs_mapping_pairs_build(vol, (u8*)a + le16_to_cpu(
				a->data.non_resident.mapping_pairs_offset),
				mp_size, rl2, vcn, highest_vcn, शून्य);
		अगर (unlikely(err)) अणु
			ntfs_error(vol->sb, "Cannot fill hole in inode 0x%lx, "
					"attribute type 0x%x, because building "
					"the mapping pairs failed with error "
					"code %i.", vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type), err);
			err = -EIO;
			अवरोध;
		पूर्ण
		/* Update the highest_vcn but only अगर it was not set. */
		अगर (unlikely(!a->data.non_resident.highest_vcn))
			a->data.non_resident.highest_vcn =
					cpu_to_sle64(highest_vcn);
		/*
		 * If the attribute is sparse/compressed, update the compressed
		 * size in the ntfs_inode काष्ठाure and the attribute record.
		 */
		अगर (likely(NInoSparse(ni) || NInoCompressed(ni))) अणु
			/*
			 * If we are not in the first attribute extent, चयन
			 * to it, but first ensure the changes will make it to
			 * disk later.
			 */
			अगर (a->data.non_resident.lowest_vcn) अणु
				flush_dcache_mft_record_page(ctx->ntfs_ino);
				mark_mft_record_dirty(ctx->ntfs_ino);
				ntfs_attr_reinit_search_ctx(ctx);
				err = ntfs_attr_lookup(ni->type, ni->name,
						ni->name_len, CASE_SENSITIVE,
						0, शून्य, 0, ctx);
				अगर (unlikely(err)) अणु
					status.attr_चयनed = 1;
					अवरोध;
				पूर्ण
				/* @m is not used any more so करो not set it. */
				a = ctx->attr;
			पूर्ण
			ग_लिखो_lock_irqsave(&ni->size_lock, flags);
			ni->itype.compressed.size += vol->cluster_size;
			a->data.non_resident.compressed_size =
					cpu_to_sle64(ni->itype.compressed.size);
			ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
		पूर्ण
		/* Ensure the changes make it to disk. */
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		mark_mft_record_dirty(ctx->ntfs_ino);
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(base_ni);
		/* Successfully filled the hole. */
		status.runlist_merged = 0;
		status.mft_attr_mapped = 0;
		status.mp_rebuilt = 0;
		/* Setup the map cache and use that to deal with the buffer. */
		was_hole = true;
		vcn = bh_cpos;
		vcn_len = 1;
		lcn_block = lcn << (vol->cluster_size_bits - blocksize_bits);
		cdelta = 0;
		/*
		 * If the number of reमुख्यing clusters in the @pages is smaller
		 * or equal to the number of cached clusters, unlock the
		 * runlist as the map cache will be used from now on.
		 */
		अगर (likely(vcn + vcn_len >= cend)) अणु
			up_ग_लिखो(&ni->runlist.lock);
			rl_ग_लिखो_locked = false;
			rl = शून्य;
		पूर्ण
		जाओ map_buffer_cached;
	पूर्ण जबतक (bh_pos += blocksize, (bh = bh->b_this_page) != head);
	/* If there are no errors, करो the next page. */
	अगर (likely(!err && ++u < nr_pages))
		जाओ करो_next_page;
	/* If there are no errors, release the runlist lock अगर we took it. */
	अगर (likely(!err)) अणु
		अगर (unlikely(rl_ग_लिखो_locked)) अणु
			up_ग_लिखो(&ni->runlist.lock);
			rl_ग_लिखो_locked = false;
		पूर्ण अन्यथा अगर (unlikely(rl))
			up_पढ़ो(&ni->runlist.lock);
		rl = शून्य;
	पूर्ण
	/* If we issued पढ़ो requests, let them complete. */
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	initialized_size = ni->initialized_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	जबतक (रुको_bh > रुको) अणु
		bh = *--रुको_bh;
		रुको_on_buffer(bh);
		अगर (likely(buffer_uptodate(bh))) अणु
			page = bh->b_page;
			bh_pos = ((s64)page->index << PAGE_SHIFT) +
					bh_offset(bh);
			/*
			 * If the buffer overflows the initialized size, need
			 * to zero the overflowing region.
			 */
			अगर (unlikely(bh_pos + blocksize > initialized_size)) अणु
				पूर्णांक ofs = 0;

				अगर (likely(bh_pos < initialized_size))
					ofs = initialized_size - bh_pos;
				zero_user_segment(page, bh_offset(bh) + ofs,
						blocksize);
			पूर्ण
		पूर्ण अन्यथा /* अगर (unlikely(!buffer_uptodate(bh))) */
			err = -EIO;
	पूर्ण
	अगर (likely(!err)) अणु
		/* Clear buffer_new on all buffers. */
		u = 0;
		करो अणु
			bh = head = page_buffers(pages[u]);
			करो अणु
				अगर (buffer_new(bh))
					clear_buffer_new(bh);
			पूर्ण जबतक ((bh = bh->b_this_page) != head);
		पूर्ण जबतक (++u < nr_pages);
		ntfs_debug("Done.");
		वापस err;
	पूर्ण
	अगर (status.attr_चयनed) अणु
		/* Get back to the attribute extent we modअगरied. */
		ntfs_attr_reinit_search_ctx(ctx);
		अगर (ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
				CASE_SENSITIVE, bh_cpos, शून्य, 0, ctx)) अणु
			ntfs_error(vol->sb, "Failed to find required "
					"attribute extent of attribute in "
					"error code path.  Run chkdsk to "
					"recover.");
			ग_लिखो_lock_irqsave(&ni->size_lock, flags);
			ni->itype.compressed.size += vol->cluster_size;
			ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
			flush_dcache_mft_record_page(ctx->ntfs_ino);
			mark_mft_record_dirty(ctx->ntfs_ino);
			/*
			 * The only thing that is now wrong is the compressed
			 * size of the base attribute extent which chkdsk
			 * should be able to fix.
			 */
			NVolSetErrors(vol);
		पूर्ण अन्यथा अणु
			m = ctx->mrec;
			a = ctx->attr;
			status.attr_चयनed = 0;
		पूर्ण
	पूर्ण
	/*
	 * If the runlist has been modअगरied, need to restore it by punching a
	 * hole पूर्णांकo it and we then need to deallocate the on-disk cluster as
	 * well.  Note, we only modअगरy the runlist अगर we are able to generate a
	 * new mapping pairs array, i.e. only when the mapped attribute extent
	 * is not चयनed.
	 */
	अगर (status.runlist_merged && !status.attr_चयनed) अणु
		BUG_ON(!rl_ग_लिखो_locked);
		/* Make the file cluster we allocated sparse in the runlist. */
		अगर (ntfs_rl_punch_nolock(vol, &ni->runlist, bh_cpos, 1)) अणु
			ntfs_error(vol->sb, "Failed to punch hole into "
					"attribute runlist in error code "
					"path.  Run chkdsk to recover the "
					"lost cluster.");
			NVolSetErrors(vol);
		पूर्ण अन्यथा /* अगर (success) */ अणु
			status.runlist_merged = 0;
			/*
			 * Deallocate the on-disk cluster we allocated but only
			 * अगर we succeeded in punching its vcn out of the
			 * runlist.
			 */
			करोwn_ग_लिखो(&vol->lcnbmp_lock);
			अगर (ntfs_biपंचांगap_clear_bit(vol->lcnbmp_ino, lcn)) अणु
				ntfs_error(vol->sb, "Failed to release "
						"allocated cluster in error "
						"code path.  Run chkdsk to "
						"recover the lost cluster.");
				NVolSetErrors(vol);
			पूर्ण
			up_ग_लिखो(&vol->lcnbmp_lock);
		पूर्ण
	पूर्ण
	/*
	 * Resize the attribute record to its old size and rebuild the mapping
	 * pairs array.  Note, we only can करो this अगर the runlist has been
	 * restored to its old state which also implies that the mapped
	 * attribute extent is not चयनed.
	 */
	अगर (status.mp_rebuilt && !status.runlist_merged) अणु
		अगर (ntfs_attr_record_resize(m, a, attr_rec_len)) अणु
			ntfs_error(vol->sb, "Failed to restore attribute "
					"record in error code path.  Run "
					"chkdsk to recover.");
			NVolSetErrors(vol);
		पूर्ण अन्यथा /* अगर (success) */ अणु
			अगर (ntfs_mapping_pairs_build(vol, (u8*)a +
					le16_to_cpu(a->data.non_resident.
					mapping_pairs_offset), attr_rec_len -
					le16_to_cpu(a->data.non_resident.
					mapping_pairs_offset), ni->runlist.rl,
					vcn, highest_vcn, शून्य)) अणु
				ntfs_error(vol->sb, "Failed to restore "
						"mapping pairs array in error "
						"code path.  Run chkdsk to "
						"recover.");
				NVolSetErrors(vol);
			पूर्ण
			flush_dcache_mft_record_page(ctx->ntfs_ino);
			mark_mft_record_dirty(ctx->ntfs_ino);
		पूर्ण
	पूर्ण
	/* Release the mft record and the attribute. */
	अगर (status.mft_attr_mapped) अणु
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(base_ni);
	पूर्ण
	/* Release the runlist lock. */
	अगर (rl_ग_लिखो_locked)
		up_ग_लिखो(&ni->runlist.lock);
	अन्यथा अगर (rl)
		up_पढ़ो(&ni->runlist.lock);
	/*
	 * Zero out any newly allocated blocks to aव्योम exposing stale data.
	 * If BH_New is set, we know that the block was newly allocated above
	 * and that it has not been fully zeroed and marked dirty yet.
	 */
	nr_pages = u;
	u = 0;
	end = bh_cpos << vol->cluster_size_bits;
	करो अणु
		page = pages[u];
		bh = head = page_buffers(page);
		करो अणु
			अगर (u == nr_pages &&
					((s64)page->index << PAGE_SHIFT) +
					bh_offset(bh) >= end)
				अवरोध;
			अगर (!buffer_new(bh))
				जारी;
			clear_buffer_new(bh);
			अगर (!buffer_uptodate(bh)) अणु
				अगर (PageUptodate(page))
					set_buffer_uptodate(bh);
				अन्यथा अणु
					zero_user(page, bh_offset(bh),
							blocksize);
					set_buffer_uptodate(bh);
				पूर्ण
			पूर्ण
			mark_buffer_dirty(bh);
		पूर्ण जबतक ((bh = bh->b_this_page) != head);
	पूर्ण जबतक (++u <= nr_pages);
	ntfs_error(vol->sb, "Failed.  Returning error code %i.", err);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम ntfs_flush_dcache_pages(काष्ठा page **pages,
		अचिन्हित nr_pages)
अणु
	BUG_ON(!nr_pages);
	/*
	 * Warning: Do not करो the decrement at the same समय as the call to
	 * flush_dcache_page() because it is a शून्य macro on i386 and hence the
	 * decrement never happens so the loop never terminates.
	 */
	करो अणु
		--nr_pages;
		flush_dcache_page(pages[nr_pages]);
	पूर्ण जबतक (nr_pages > 0);
पूर्ण

/**
 * ntfs_commit_pages_after_non_resident_ग_लिखो - commit the received data
 * @pages:	array of destination pages
 * @nr_pages:	number of pages in @pages
 * @pos:	byte position in file at which the ग_लिखो begins
 * @bytes:	number of bytes to be written
 *
 * See description of ntfs_commit_pages_after_ग_लिखो(), below.
 */
अटल अंतरभूत पूर्णांक ntfs_commit_pages_after_non_resident_ग_लिखो(
		काष्ठा page **pages, स्थिर अचिन्हित nr_pages,
		s64 pos, माप_प्रकार bytes)
अणु
	s64 end, initialized_size;
	काष्ठा inode *vi;
	ntfs_inode *ni, *base_ni;
	काष्ठा buffer_head *bh, *head;
	ntfs_attr_search_ctx *ctx;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	अचिन्हित दीर्घ flags;
	अचिन्हित blocksize, u;
	पूर्णांक err;

	vi = pages[0]->mapping->host;
	ni = NTFS_I(vi);
	blocksize = vi->i_sb->s_blocksize;
	end = pos + bytes;
	u = 0;
	करो अणु
		s64 bh_pos;
		काष्ठा page *page;
		bool partial;

		page = pages[u];
		bh_pos = (s64)page->index << PAGE_SHIFT;
		bh = head = page_buffers(page);
		partial = false;
		करो अणु
			s64 bh_end;

			bh_end = bh_pos + blocksize;
			अगर (bh_end <= pos || bh_pos >= end) अणु
				अगर (!buffer_uptodate(bh))
					partial = true;
			पूर्ण अन्यथा अणु
				set_buffer_uptodate(bh);
				mark_buffer_dirty(bh);
			पूर्ण
		पूर्ण जबतक (bh_pos += blocksize, (bh = bh->b_this_page) != head);
		/*
		 * If all buffers are now uptodate but the page is not, set the
		 * page uptodate.
		 */
		अगर (!partial && !PageUptodate(page))
			SetPageUptodate(page);
	पूर्ण जबतक (++u < nr_pages);
	/*
	 * Finally, अगर we करो not need to update initialized_size or i_size we
	 * are finished.
	 */
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	initialized_size = ni->initialized_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	अगर (end <= initialized_size) अणु
		ntfs_debug("Done.");
		वापस 0;
	पूर्ण
	/*
	 * Update initialized_size/i_size as appropriate, both in the inode and
	 * the mft record.
	 */
	अगर (!NInoAttr(ni))
		base_ni = ni;
	अन्यथा
		base_ni = ni->ext.base_ntfs_ino;
	/* Map, pin, and lock the mft record. */
	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		m = शून्य;
		ctx = शून्य;
		जाओ err_out;
	पूर्ण
	BUG_ON(!NInoNonResident(ni));
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT)
			err = -EIO;
		जाओ err_out;
	पूर्ण
	a = ctx->attr;
	BUG_ON(!a->non_resident);
	ग_लिखो_lock_irqsave(&ni->size_lock, flags);
	BUG_ON(end > ni->allocated_size);
	ni->initialized_size = end;
	a->data.non_resident.initialized_size = cpu_to_sle64(end);
	अगर (end > i_size_पढ़ो(vi)) अणु
		i_size_ग_लिखो(vi, end);
		a->data.non_resident.data_size =
				a->data.non_resident.initialized_size;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
	/* Mark the mft record dirty, so it माला_लो written back. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
	ntfs_debug("Done.");
	वापस 0;
err_out:
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(base_ni);
	ntfs_error(vi->i_sb, "Failed to update initialized_size/i_size (error "
			"code %i).", err);
	अगर (err != -ENOMEM)
		NVolSetErrors(ni->vol);
	वापस err;
पूर्ण

/**
 * ntfs_commit_pages_after_ग_लिखो - commit the received data
 * @pages:	array of destination pages
 * @nr_pages:	number of pages in @pages
 * @pos:	byte position in file at which the ग_लिखो begins
 * @bytes:	number of bytes to be written
 *
 * This is called from ntfs_file_buffered_ग_लिखो() with i_mutex held on the inode
 * (@pages[0]->mapping->host).  There are @nr_pages pages in @pages which are
 * locked but not kmap()ped.  The source data has alपढ़ोy been copied पूर्णांकo the
 * @page.  ntfs_prepare_pages_क्रम_non_resident_ग_लिखो() has been called beक्रमe
 * the data was copied (क्रम non-resident attributes only) and it वापसed
 * success.
 *
 * Need to set uptodate and mark dirty all buffers within the boundary of the
 * ग_लिखो.  If all buffers in a page are uptodate we set the page uptodate, too.
 *
 * Setting the buffers dirty ensures that they get written out later when
 * ntfs_ग_लिखोpage() is invoked by the VM.
 *
 * Finally, we need to update i_size and initialized_size as appropriate both
 * in the inode and the mft record.
 *
 * This is modelled after fs/buffer.c::generic_commit_ग_लिखो(), which marks
 * buffers uptodate and dirty, sets the page uptodate अगर all buffers in the
 * page are uptodate, and updates i_size अगर the end of io is beyond i_size.  In
 * that हाल, it also marks the inode dirty.
 *
 * If things have gone as outlined in
 * ntfs_prepare_pages_क्रम_non_resident_ग_लिखो(), we करो not need to करो any page
 * content modअगरications here क्रम non-resident attributes.  For resident
 * attributes we need to करो the uptodate bringing here which we combine with
 * the copying पूर्णांकo the mft record which means we save one atomic kmap.
 *
 * Return 0 on success or -त्रुटि_सं on error.
 */
अटल पूर्णांक ntfs_commit_pages_after_ग_लिखो(काष्ठा page **pages,
		स्थिर अचिन्हित nr_pages, s64 pos, माप_प्रकार bytes)
अणु
	s64 end, initialized_size;
	loff_t i_size;
	काष्ठा inode *vi;
	ntfs_inode *ni, *base_ni;
	काष्ठा page *page;
	ntfs_attr_search_ctx *ctx;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	अक्षर *kattr, *kaddr;
	अचिन्हित दीर्घ flags;
	u32 attr_len;
	पूर्णांक err;

	BUG_ON(!nr_pages);
	BUG_ON(!pages);
	page = pages[0];
	BUG_ON(!page);
	vi = page->mapping->host;
	ni = NTFS_I(vi);
	ntfs_debug("Entering for inode 0x%lx, attribute type 0x%x, start page "
			"index 0x%lx, nr_pages 0x%x, pos 0x%llx, bytes 0x%zx.",
			vi->i_ino, ni->type, page->index, nr_pages,
			(दीर्घ दीर्घ)pos, bytes);
	अगर (NInoNonResident(ni))
		वापस ntfs_commit_pages_after_non_resident_ग_लिखो(pages,
				nr_pages, pos, bytes);
	BUG_ON(nr_pages > 1);
	/*
	 * Attribute is resident, implying it is not compressed, encrypted, or
	 * sparse.
	 */
	अगर (!NInoAttr(ni))
		base_ni = ni;
	अन्यथा
		base_ni = ni->ext.base_ntfs_ino;
	BUG_ON(NInoNonResident(ni));
	/* Map, pin, and lock the mft record. */
	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		m = शून्य;
		ctx = शून्य;
		जाओ err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT)
			err = -EIO;
		जाओ err_out;
	पूर्ण
	a = ctx->attr;
	BUG_ON(a->non_resident);
	/* The total length of the attribute value. */
	attr_len = le32_to_cpu(a->data.resident.value_length);
	i_size = i_size_पढ़ो(vi);
	BUG_ON(attr_len != i_size);
	BUG_ON(pos > attr_len);
	end = pos + bytes;
	BUG_ON(end > le32_to_cpu(a->length) -
			le16_to_cpu(a->data.resident.value_offset));
	kattr = (u8*)a + le16_to_cpu(a->data.resident.value_offset);
	kaddr = kmap_atomic(page);
	/* Copy the received data from the page to the mft record. */
	स_नकल(kattr + pos, kaddr + pos, bytes);
	/* Update the attribute length अगर necessary. */
	अगर (end > attr_len) अणु
		attr_len = end;
		a->data.resident.value_length = cpu_to_le32(attr_len);
	पूर्ण
	/*
	 * If the page is not uptodate, bring the out of bounds area(s)
	 * uptodate by copying data from the mft record to the page.
	 */
	अगर (!PageUptodate(page)) अणु
		अगर (pos > 0)
			स_नकल(kaddr, kattr, pos);
		अगर (end < attr_len)
			स_नकल(kaddr + end, kattr + end, attr_len - end);
		/* Zero the region outside the end of the attribute value. */
		स_रखो(kaddr + attr_len, 0, PAGE_SIZE - attr_len);
		flush_dcache_page(page);
		SetPageUptodate(page);
	पूर्ण
	kunmap_atomic(kaddr);
	/* Update initialized_size/i_size अगर necessary. */
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	initialized_size = ni->initialized_size;
	BUG_ON(end > ni->allocated_size);
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	BUG_ON(initialized_size != i_size);
	अगर (end > initialized_size) अणु
		ग_लिखो_lock_irqsave(&ni->size_lock, flags);
		ni->initialized_size = end;
		i_size_ग_लिखो(vi, end);
		ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
	पूर्ण
	/* Mark the mft record dirty, so it माला_लो written back. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
	ntfs_debug("Done.");
	वापस 0;
err_out:
	अगर (err == -ENOMEM) अणु
		ntfs_warning(vi->i_sb, "Error allocating memory required to "
				"commit the write.");
		अगर (PageUptodate(page)) अणु
			ntfs_warning(vi->i_sb, "Page is uptodate, setting "
					"dirty so the write will be retried "
					"later on by the VM.");
			/*
			 * Put the page on mapping->dirty_pages, but leave its
			 * buffers' dirty state as-is.
			 */
			__set_page_dirty_nobuffers(page);
			err = 0;
		पूर्ण अन्यथा
			ntfs_error(vi->i_sb, "Page is not uptodate.  Written "
					"data has been lost.");
	पूर्ण अन्यथा अणु
		ntfs_error(vi->i_sb, "Resident attribute commit write failed "
				"with error %i.", err);
		NVolSetErrors(ni->vol);
	पूर्ण
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(base_ni);
	वापस err;
पूर्ण

/*
 * Copy as much as we can पूर्णांकo the pages and वापस the number of bytes which
 * were successfully copied.  If a fault is encountered then clear the pages
 * out to (ofs + bytes) and वापस the number of bytes which were copied.
 */
अटल माप_प्रकार ntfs_copy_from_user_iter(काष्ठा page **pages, अचिन्हित nr_pages,
		अचिन्हित ofs, काष्ठा iov_iter *i, माप_प्रकार bytes)
अणु
	काष्ठा page **last_page = pages + nr_pages;
	माप_प्रकार total = 0;
	काष्ठा iov_iter data = *i;
	अचिन्हित len, copied;

	करो अणु
		len = PAGE_SIZE - ofs;
		अगर (len > bytes)
			len = bytes;
		copied = iov_iter_copy_from_user_atomic(*pages, &data, ofs,
				len);
		total += copied;
		bytes -= copied;
		अगर (!bytes)
			अवरोध;
		iov_iter_advance(&data, copied);
		अगर (copied < len)
			जाओ err;
		ofs = 0;
	पूर्ण जबतक (++pages < last_page);
out:
	वापस total;
err:
	/* Zero the rest of the target like __copy_from_user(). */
	len = PAGE_SIZE - copied;
	करो अणु
		अगर (len > bytes)
			len = bytes;
		zero_user(*pages, copied, len);
		bytes -= len;
		copied = 0;
		len = PAGE_SIZE;
	पूर्ण जबतक (++pages < last_page);
	जाओ out;
पूर्ण

/**
 * ntfs_perक्रमm_ग_लिखो - perक्रमm buffered ग_लिखो to a file
 * @file:	file to ग_लिखो to
 * @i:		iov_iter with data to ग_लिखो
 * @pos:	byte offset in file at which to begin writing to
 */
अटल sमाप_प्रकार ntfs_perक्रमm_ग_लिखो(काष्ठा file *file, काष्ठा iov_iter *i,
		loff_t pos)
अणु
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *vi = mapping->host;
	ntfs_inode *ni = NTFS_I(vi);
	ntfs_volume *vol = ni->vol;
	काष्ठा page *pages[NTFS_MAX_PAGES_PER_CLUSTER];
	काष्ठा page *cached_page = शून्य;
	VCN last_vcn;
	LCN lcn;
	माप_प्रकार bytes;
	sमाप_प्रकार status, written = 0;
	अचिन्हित nr_pages;

	ntfs_debug("Entering for i_ino 0x%lx, attribute type 0x%x, pos "
			"0x%llx, count 0x%lx.", vi->i_ino,
			(अचिन्हित)le32_to_cpu(ni->type),
			(अचिन्हित दीर्घ दीर्घ)pos,
			(अचिन्हित दीर्घ)iov_iter_count(i));
	/*
	 * If a previous ntfs_truncate() failed, repeat it and पात अगर it
	 * fails again.
	 */
	अगर (unlikely(NInoTruncateFailed(ni))) अणु
		पूर्णांक err;

		inode_dio_रुको(vi);
		err = ntfs_truncate(vi);
		अगर (err || NInoTruncateFailed(ni)) अणु
			अगर (!err)
				err = -EIO;
			ntfs_error(vol->sb, "Cannot perform write to inode "
					"0x%lx, attribute type 0x%x, because "
					"ntfs_truncate() failed (error code "
					"%i).", vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type), err);
			वापस err;
		पूर्ण
	पूर्ण
	/*
	 * Determine the number of pages per cluster क्रम non-resident
	 * attributes.
	 */
	nr_pages = 1;
	अगर (vol->cluster_size > PAGE_SIZE && NInoNonResident(ni))
		nr_pages = vol->cluster_size >> PAGE_SHIFT;
	last_vcn = -1;
	करो अणु
		VCN vcn;
		pgoff_t idx, start_idx;
		अचिन्हित ofs, करो_pages, u;
		माप_प्रकार copied;

		start_idx = idx = pos >> PAGE_SHIFT;
		ofs = pos & ~PAGE_MASK;
		bytes = PAGE_SIZE - ofs;
		करो_pages = 1;
		अगर (nr_pages > 1) अणु
			vcn = pos >> vol->cluster_size_bits;
			अगर (vcn != last_vcn) अणु
				last_vcn = vcn;
				/*
				 * Get the lcn of the vcn the ग_लिखो is in.  If
				 * it is a hole, need to lock करोwn all pages in
				 * the cluster.
				 */
				करोwn_पढ़ो(&ni->runlist.lock);
				lcn = ntfs_attr_vcn_to_lcn_nolock(ni, pos >>
						vol->cluster_size_bits, false);
				up_पढ़ो(&ni->runlist.lock);
				अगर (unlikely(lcn < LCN_HOLE)) अणु
					अगर (lcn == LCN_ENOMEM)
						status = -ENOMEM;
					अन्यथा अणु
						status = -EIO;
						ntfs_error(vol->sb, "Cannot "
							"perform write to "
							"inode 0x%lx, "
							"attribute type 0x%x, "
							"because the attribute "
							"is corrupt.",
							vi->i_ino, (अचिन्हित)
							le32_to_cpu(ni->type));
					पूर्ण
					अवरोध;
				पूर्ण
				अगर (lcn == LCN_HOLE) अणु
					start_idx = (pos & ~(s64)
							vol->cluster_size_mask)
							>> PAGE_SHIFT;
					bytes = vol->cluster_size - (pos &
							vol->cluster_size_mask);
					करो_pages = nr_pages;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (bytes > iov_iter_count(i))
			bytes = iov_iter_count(i);
again:
		/*
		 * Bring in the user page(s) that we will copy from _first_.
		 * Otherwise there is a nasty deadlock on copying from the same
		 * page(s) as we are writing to, without it/them being marked
		 * up-to-date.  Note, at present there is nothing to stop the
		 * pages being swapped out between us bringing them पूर्णांकo memory
		 * and करोing the actual copying.
		 */
		अगर (unlikely(iov_iter_fault_in_पढ़ोable(i, bytes))) अणु
			status = -EFAULT;
			अवरोध;
		पूर्ण
		/* Get and lock @करो_pages starting at index @start_idx. */
		status = __ntfs_grab_cache_pages(mapping, start_idx, करो_pages,
				pages, &cached_page);
		अगर (unlikely(status))
			अवरोध;
		/*
		 * For non-resident attributes, we need to fill any holes with
		 * actual clusters and ensure all bufferes are mapped.  We also
		 * need to bring uptodate any buffers that are only partially
		 * being written to.
		 */
		अगर (NInoNonResident(ni)) अणु
			status = ntfs_prepare_pages_क्रम_non_resident_ग_लिखो(
					pages, करो_pages, pos, bytes);
			अगर (unlikely(status)) अणु
				करो अणु
					unlock_page(pages[--करो_pages]);
					put_page(pages[करो_pages]);
				पूर्ण जबतक (करो_pages);
				अवरोध;
			पूर्ण
		पूर्ण
		u = (pos >> PAGE_SHIFT) - pages[0]->index;
		copied = ntfs_copy_from_user_iter(pages + u, करो_pages - u, ofs,
					i, bytes);
		ntfs_flush_dcache_pages(pages + u, करो_pages - u);
		status = 0;
		अगर (likely(copied == bytes)) अणु
			status = ntfs_commit_pages_after_ग_लिखो(pages, करो_pages,
					pos, bytes);
			अगर (!status)
				status = bytes;
		पूर्ण
		करो अणु
			unlock_page(pages[--करो_pages]);
			put_page(pages[करो_pages]);
		पूर्ण जबतक (करो_pages);
		अगर (unlikely(status < 0))
			अवरोध;
		copied = status;
		cond_resched();
		अगर (unlikely(!copied)) अणु
			माप_प्रकार sc;

			/*
			 * We failed to copy anything.  Fall back to single
			 * segment length ग_लिखो.
			 *
			 * This is needed to aव्योम possible livelock in the
			 * हाल that all segments in the iov cannot be copied
			 * at once without a pagefault.
			 */
			sc = iov_iter_single_seg_count(i);
			अगर (bytes > sc)
				bytes = sc;
			जाओ again;
		पूर्ण
		iov_iter_advance(i, copied);
		pos += copied;
		written += copied;
		balance_dirty_pages_ratelimited(mapping);
		अगर (fatal_संकेत_pending(current)) अणु
			status = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (iov_iter_count(i));
	अगर (cached_page)
		put_page(cached_page);
	ntfs_debug("Done.  Returning %s (written 0x%lx, status %li).",
			written ? "written" : "status", (अचिन्हित दीर्घ)written,
			(दीर्घ)status);
	वापस written ? written : status;
पूर्ण

/**
 * ntfs_file_ग_लिखो_iter - simple wrapper क्रम ntfs_file_ग_लिखो_iter_nolock()
 * @iocb:	IO state काष्ठाure
 * @from:	iov_iter with data to ग_लिखो
 *
 * Basically the same as generic_file_ग_लिखो_iter() except that it ends up
 * up calling ntfs_perक्रमm_ग_लिखो() instead of generic_perक्रमm_ग_लिखो() and that
 * O_सूचीECT is not implemented.
 */
अटल sमाप_प्रकार ntfs_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *vi = file_inode(file);
	sमाप_प्रकार written = 0;
	sमाप_प्रकार err;

	inode_lock(vi);
	/* We can ग_लिखो back this queue in page reclaim. */
	current->backing_dev_info = inode_to_bdi(vi);
	err = ntfs_prepare_file_क्रम_ग_लिखो(iocb, from);
	अगर (iov_iter_count(from) && !err)
		written = ntfs_perक्रमm_ग_लिखो(file, from, iocb->ki_pos);
	current->backing_dev_info = शून्य;
	inode_unlock(vi);
	iocb->ki_pos += written;
	अगर (likely(written > 0))
		written = generic_ग_लिखो_sync(iocb, written);
	वापस written ? written : err;
पूर्ण

/**
 * ntfs_file_fsync - sync a file to disk
 * @filp:	file to be synced
 * @datasync:	अगर non-zero only flush user data and not metadata
 *
 * Data पूर्णांकegrity sync of a file to disk.  Used क्रम fsync, fdatasync, and msync
 * प्रणाली calls.  This function is inspired by fs/buffer.c::file_fsync().
 *
 * If @datasync is false, ग_लिखो the mft record and all associated extent mft
 * records as well as the $DATA attribute and then sync the block device.
 *
 * If @datasync is true and the attribute is non-resident, we skip the writing
 * of the mft record and all associated extent mft records (this might still
 * happen due to the ग_लिखो_inode_now() call).
 *
 * Also, अगर @datasync is true, we करो not रुको on the inode to be written out
 * but we always रुको on the page cache pages to be written out.
 *
 * Locking: Caller must hold i_mutex on the inode.
 *
 * TODO: We should probably also ग_लिखो all attribute/index inodes associated
 * with this inode but since we have no simple way of getting to them we ignore
 * this problem क्रम now.
 */
अटल पूर्णांक ntfs_file_fsync(काष्ठा file *filp, loff_t start, loff_t end,
			   पूर्णांक datasync)
अणु
	काष्ठा inode *vi = filp->f_mapping->host;
	पूर्णांक err, ret = 0;

	ntfs_debug("Entering for inode 0x%lx.", vi->i_ino);

	err = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (err)
		वापस err;
	inode_lock(vi);

	BUG_ON(S_ISसूची(vi->i_mode));
	अगर (!datasync || !NInoNonResident(NTFS_I(vi)))
		ret = __ntfs_ग_लिखो_inode(vi, 1);
	ग_लिखो_inode_now(vi, !datasync);
	/*
	 * NOTE: If we were to use mapping->निजी_list (see ext2 and
	 * fs/buffer.c) क्रम dirty blocks then we could optimize the below to be
	 * sync_mapping_buffers(vi->i_mapping).
	 */
	err = sync_blockdev(vi->i_sb->s_bdev);
	अगर (unlikely(err && !ret))
		ret = err;
	अगर (likely(!ret))
		ntfs_debug("Done.");
	अन्यथा
		ntfs_warning(vi->i_sb, "Failed to f%ssync inode 0x%lx.  Error "
				"%u.", datasync ? "data" : "", vi->i_ino, -ret);
	inode_unlock(vi);
	वापस ret;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */

स्थिर काष्ठा file_operations ntfs_file_ops = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
#अगर_घोषित NTFS_RW
	.ग_लिखो_iter	= ntfs_file_ग_लिखो_iter,
	.fsync		= ntfs_file_fsync,
#पूर्ण_अगर /* NTFS_RW */
	.mmap		= generic_file_mmap,
	.खोलो		= ntfs_file_खोलो,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
पूर्ण;

स्थिर काष्ठा inode_operations ntfs_file_inode_ops = अणु
#अगर_घोषित NTFS_RW
	.setattr	= ntfs_setattr,
#पूर्ण_अगर /* NTFS_RW */
पूर्ण;

स्थिर काष्ठा file_operations ntfs_empty_file_ops = अणुपूर्ण;

स्थिर काष्ठा inode_operations ntfs_empty_inode_ops = अणुपूर्ण;
