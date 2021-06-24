<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/nfs/file.c
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  Changes Copyright (C) 1994 by Florian La Roche
 *   - Do not copy data too often around in the kernel.
 *   - In nfs_file_पढ़ो the वापस value of kदो_स्मृति wasn't checked.
 *   - Put in a better version of पढ़ो look-ahead buffering. Original idea
 *     and implementation by Wai S Kok elekokws@ee.nus.sg.
 *
 *  Expire cache on ग_लिखो to a file by Wai S Kok (Oct 1994).
 *
 *  Total reग_लिखो of पढ़ो side क्रम new NFS buffer cache.. Linus.
 *
 *  nfs regular file handling functions
 */

#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/gfp.h>
#समावेश <linux/swap.h>

#समावेश <linux/uaccess.h>

#समावेश "delegation.h"
#समावेश "internal.h"
#समावेश "iostat.h"
#समावेश "fscache.h"
#समावेश "pnfs.h"

#समावेश "nfstrace.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_खाता

अटल स्थिर काष्ठा vm_operations_काष्ठा nfs_file_vm_ops;

/* Hack क्रम future NFS swap support */
#अगर_अघोषित IS_SWAPखाता
# define IS_SWAPखाता(inode)	(0)
#पूर्ण_अगर

पूर्णांक nfs_check_flags(पूर्णांक flags)
अणु
	अगर ((flags & (O_APPEND | O_सूचीECT)) == (O_APPEND | O_सूचीECT))
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_check_flags);

/*
 * Open file
 */
अटल पूर्णांक
nfs_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक res;

	dprपूर्णांकk("NFS: open file(%pD2)\n", filp);

	nfs_inc_stats(inode, NFSIOS_VFSOPEN);
	res = nfs_check_flags(filp->f_flags);
	अगर (res)
		वापस res;

	res = nfs_खोलो(inode, filp);
	वापस res;
पूर्ण

पूर्णांक
nfs_file_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	dprपूर्णांकk("NFS: release(%pD2)\n", filp);

	nfs_inc_stats(inode, NFSIOS_VFSRELEASE);
	nfs_file_clear_खोलो_context(filp);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_file_release);

/**
 * nfs_revalidate_file_size - Revalidate the file size
 * @inode: poपूर्णांकer to inode काष्ठा
 * @filp: poपूर्णांकer to काष्ठा file
 *
 * Revalidates the file length. This is basically a wrapper around
 * nfs_revalidate_inode() that takes पूर्णांकo account the fact that we may
 * have cached ग_लिखोs (in which हाल we करोn't care about the server's
 * idea of what the file length is), or O_सूचीECT (in which हाल we
 * shouldn't trust the cache).
 */
अटल पूर्णांक nfs_revalidate_file_size(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);

	अगर (filp->f_flags & O_सूचीECT)
		जाओ क्रमce_reval;
	अगर (nfs_check_cache_invalid(inode, NFS_INO_INVALID_SIZE))
		जाओ क्रमce_reval;
	वापस 0;
क्रमce_reval:
	वापस __nfs_revalidate_inode(server, inode);
पूर्ण

loff_t nfs_file_llseek(काष्ठा file *filp, loff_t offset, पूर्णांक whence)
अणु
	dprपूर्णांकk("NFS: llseek file(%pD2, %lld, %d)\n",
			filp, offset, whence);

	/*
	 * whence == अंत_से || SEEK_DATA || SEEK_HOLE => we must revalidate
	 * the cached file length
	 */
	अगर (whence != शुरू_से && whence != प्रस्तुत_से) अणु
		काष्ठा inode *inode = filp->f_mapping->host;

		पूर्णांक retval = nfs_revalidate_file_size(inode, filp);
		अगर (retval < 0)
			वापस (loff_t)retval;
	पूर्ण

	वापस generic_file_llseek(filp, offset, whence);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_file_llseek);

/*
 * Flush all dirty pages, and check क्रम ग_लिखो errors.
 */
अटल पूर्णांक
nfs_file_flush(काष्ठा file *file, fl_owner_t id)
अणु
	काष्ठा inode	*inode = file_inode(file);
	errseq_t since;

	dprपूर्णांकk("NFS: flush(%pD2)\n", file);

	nfs_inc_stats(inode, NFSIOS_VFSFLUSH);
	अगर ((file->f_mode & FMODE_WRITE) == 0)
		वापस 0;

	/* Flush ग_लिखोs to the server and वापस any errors */
	since = filemap_sample_wb_err(file->f_mapping);
	nfs_wb_all(inode);
	वापस filemap_check_wb_err(file->f_mapping, since);
पूर्ण

sमाप_प्रकार
nfs_file_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	sमाप_प्रकार result;

	अगर (iocb->ki_flags & IOCB_सूचीECT)
		वापस nfs_file_direct_पढ़ो(iocb, to);

	dprपूर्णांकk("NFS: read(%pD2, %zu@%lu)\n",
		iocb->ki_filp,
		iov_iter_count(to), (अचिन्हित दीर्घ) iocb->ki_pos);

	nfs_start_io_पढ़ो(inode);
	result = nfs_revalidate_mapping(inode, iocb->ki_filp->f_mapping);
	अगर (!result) अणु
		result = generic_file_पढ़ो_iter(iocb, to);
		अगर (result > 0)
			nfs_add_stats(inode, NFSIOS_NORMALREADBYTES, result);
	पूर्ण
	nfs_end_io_पढ़ो(inode);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_file_पढ़ो);

पूर्णांक
nfs_file_mmap(काष्ठा file * file, काष्ठा vm_area_काष्ठा * vma)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक	status;

	dprपूर्णांकk("NFS: mmap(%pD2)\n", file);

	/* Note: generic_file_mmap() वापसs ENOSYS on nommu प्रणालीs
	 *       so we call that beक्रमe revalidating the mapping
	 */
	status = generic_file_mmap(file, vma);
	अगर (!status) अणु
		vma->vm_ops = &nfs_file_vm_ops;
		status = nfs_revalidate_mapping(inode, file->f_mapping);
	पूर्ण
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_file_mmap);

/*
 * Flush any dirty pages क्रम this process, and check क्रम ग_लिखो errors.
 * The वापस status from this call provides a reliable indication of
 * whether any ग_लिखो errors occurred क्रम this process.
 */
अटल पूर्णांक
nfs_file_fsync_commit(काष्ठा file *file, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक ret;

	dprपूर्णांकk("NFS: fsync file(%pD2) datasync %d\n", file, datasync);

	nfs_inc_stats(inode, NFSIOS_VFSFSYNC);
	ret = nfs_commit_inode(inode, FLUSH_SYNC);
	अगर (ret < 0)
		वापस ret;
	वापस file_check_and_advance_wb_err(file);
पूर्ण

पूर्णांक
nfs_file_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा nfs_खोलो_context *ctx = nfs_file_खोलो_context(file);
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक ret;

	trace_nfs_fsync_enter(inode);

	क्रम (;;) अणु
		ret = file_ग_लिखो_and_रुको_range(file, start, end);
		अगर (ret != 0)
			अवरोध;
		ret = nfs_file_fsync_commit(file, datasync);
		अगर (ret != 0)
			अवरोध;
		ret = pnfs_sync_inode(inode, !!datasync);
		अगर (ret != 0)
			अवरोध;
		अगर (!test_and_clear_bit(NFS_CONTEXT_RESEND_WRITES, &ctx->flags))
			अवरोध;
		/*
		 * If nfs_file_fsync_commit detected a server reboot, then
		 * resend all dirty pages that might have been covered by
		 * the NFS_CONTEXT_RESEND_WRITES flag
		 */
		start = 0;
		end = Lदीर्घ_उच्च;
	पूर्ण

	trace_nfs_fsync_निकास(inode, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_file_fsync);

/*
 * Decide whether a पढ़ो/modअगरy/ग_लिखो cycle may be more efficient
 * then a modअगरy/ग_लिखो/पढ़ो cycle when writing to a page in the
 * page cache.
 *
 * Some pNFS layout drivers can only पढ़ो/ग_लिखो at a certain block
 * granularity like all block devices and thereक्रमe we must perक्रमm
 * पढ़ो/modअगरy/ग_लिखो whenever a page hasn't पढ़ो yet and the data
 * to be written there is not aligned to a block boundary and/or
 * smaller than the block size.
 *
 * The modअगरy/ग_लिखो/पढ़ो cycle may occur अगर a page is पढ़ो beक्रमe
 * being completely filled by the ग_लिखोr.  In this situation, the
 * page must be completely written to stable storage on the server
 * beक्रमe it can be refilled by पढ़ोing in the page from the server.
 * This can lead to expensive, small, खाता_SYNC mode ग_लिखोs being
 * करोne.
 *
 * It may be more efficient to पढ़ो the page first अगर the file is
 * खोलो क्रम पढ़ोing in addition to writing, the page is not marked
 * as Uptodate, it is not dirty or रुकोing to be committed,
 * indicating that it was previously allocated and then modअगरied,
 * that there were valid bytes of data in that range of the file,
 * and that the new data won't completely replace the old data in
 * that range of the file.
 */
अटल bool nfs_full_page_ग_लिखो(काष्ठा page *page, loff_t pos, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक pglen = nfs_page_length(page);
	अचिन्हित पूर्णांक offset = pos & (PAGE_SIZE - 1);
	अचिन्हित पूर्णांक end = offset + len;

	वापस !pglen || (end >= pglen && !offset);
पूर्ण

अटल bool nfs_want_पढ़ो_modअगरy_ग_लिखो(काष्ठा file *file, काष्ठा page *page,
			loff_t pos, अचिन्हित पूर्णांक len)
अणु
	/*
	 * Up-to-date pages, those with ongoing or full-page ग_लिखो
	 * करोn't need पढ़ो/modअगरy/ग_लिखो
	 */
	अगर (PageUptodate(page) || PagePrivate(page) ||
	    nfs_full_page_ग_लिखो(page, pos, len))
		वापस false;

	अगर (pnfs_ld_पढ़ो_whole_page(file->f_mapping->host))
		वापस true;
	/* Open क्रम पढ़ोing too? */
	अगर (file->f_mode & FMODE_READ)
		वापस true;
	वापस false;
पूर्ण

/*
 * This करोes the "real" work of the ग_लिखो. We must allocate and lock the
 * page to be sent back to the generic routine, which then copies the
 * data from user space.
 *
 * If the ग_लिखोr ends up delaying the ग_लिखो, the ग_लिखोr needs to
 * increment the page use counts until he is करोne with the page.
 */
अटल पूर्णांक nfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;
	pgoff_t index = pos >> PAGE_SHIFT;
	काष्ठा page *page;
	पूर्णांक once_thru = 0;

	dfprपूर्णांकk(PAGECACHE, "NFS: write_begin(%pD2(%lu), %u@%lld)\n",
		file, mapping->host->i_ino, len, (दीर्घ दीर्घ) pos);

start:
	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;
	*pagep = page;

	ret = nfs_flush_incompatible(file, page);
	अगर (ret) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण अन्यथा अगर (!once_thru &&
		   nfs_want_पढ़ो_modअगरy_ग_लिखो(file, page, pos, len)) अणु
		once_thru = 1;
		ret = nfs_पढ़ोpage(file, page);
		put_page(page);
		अगर (!ret)
			जाओ start;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nfs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	अचिन्हित offset = pos & (PAGE_SIZE - 1);
	काष्ठा nfs_खोलो_context *ctx = nfs_file_खोलो_context(file);
	पूर्णांक status;

	dfprपूर्णांकk(PAGECACHE, "NFS: write_end(%pD2(%lu), %u@%lld)\n",
		file, mapping->host->i_ino, len, (दीर्घ दीर्घ) pos);

	/*
	 * Zero any uninitialised parts of the page, and then mark the page
	 * as up to date अगर it turns out that we're extending the file.
	 */
	अगर (!PageUptodate(page)) अणु
		अचिन्हित pglen = nfs_page_length(page);
		अचिन्हित end = offset + copied;

		अगर (pglen == 0) अणु
			zero_user_segments(page, 0, offset,
					end, PAGE_SIZE);
			SetPageUptodate(page);
		पूर्ण अन्यथा अगर (end >= pglen) अणु
			zero_user_segment(page, end, PAGE_SIZE);
			अगर (offset == 0)
				SetPageUptodate(page);
		पूर्ण अन्यथा
			zero_user_segment(page, pglen, PAGE_SIZE);
	पूर्ण

	status = nfs_updatepage(file, page, offset, copied);

	unlock_page(page);
	put_page(page);

	अगर (status < 0)
		वापस status;
	NFS_I(mapping->host)->ग_लिखो_io += copied;

	अगर (nfs_ctx_key_to_expire(ctx, mapping->host)) अणु
		status = nfs_wb_all(mapping->host);
		अगर (status < 0)
			वापस status;
	पूर्ण

	वापस copied;
पूर्ण

/*
 * Partially or wholly invalidate a page
 * - Release the निजी state associated with a page अगर undergoing complete
 *   page invalidation
 * - Called अगर either PG_निजी or PG_fscache is set on the page
 * - Caller holds page lock
 */
अटल व्योम nfs_invalidate_page(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				अचिन्हित पूर्णांक length)
अणु
	dfprपूर्णांकk(PAGECACHE, "NFS: invalidate_page(%p, %u, %u)\n",
		 page, offset, length);

	अगर (offset != 0 || length < PAGE_SIZE)
		वापस;
	/* Cancel any unstarted ग_लिखोs on this page */
	nfs_wb_page_cancel(page_file_mapping(page)->host, page);

	nfs_fscache_invalidate_page(page, page->mapping->host);
पूर्ण

/*
 * Attempt to release the निजी state associated with a page
 * - Called अगर either PG_निजी or PG_fscache is set on the page
 * - Caller holds page lock
 * - Return true (may release page) or false (may not)
 */
अटल पूर्णांक nfs_release_page(काष्ठा page *page, gfp_t gfp)
अणु
	dfprपूर्णांकk(PAGECACHE, "NFS: release_page(%p)\n", page);

	/* If PagePrivate() is set, then the page is not मुक्तable */
	अगर (PagePrivate(page))
		वापस 0;
	वापस nfs_fscache_release_page(page, gfp);
पूर्ण

अटल व्योम nfs_check_dirty_ग_लिखोback(काष्ठा page *page,
				bool *dirty, bool *ग_लिखोback)
अणु
	काष्ठा nfs_inode *nfsi;
	काष्ठा address_space *mapping = page_file_mapping(page);

	अगर (!mapping || PageSwapCache(page))
		वापस;

	/*
	 * Check अगर an unstable page is currently being committed and
	 * अगर so, have the VM treat it as अगर the page is under ग_लिखोback
	 * so it will not block due to pages that will लघुly be मुक्तable.
	 */
	nfsi = NFS_I(mapping->host);
	अगर (atomic_पढ़ो(&nfsi->commit_info.rpcs_out)) अणु
		*ग_लिखोback = true;
		वापस;
	पूर्ण

	/*
	 * If PagePrivate() is set, then the page is not मुक्तable and as the
	 * inode is not being committed, it's not going to be cleaned in the
	 * near future so treat it as dirty
	 */
	अगर (PagePrivate(page))
		*dirty = true;
पूर्ण

/*
 * Attempt to clear the निजी state associated with a page when an error
 * occurs that requires the cached contents of an inode to be written back or
 * destroyed
 * - Called अगर either PG_निजी or fscache is set on the page
 * - Caller holds page lock
 * - Return 0 अगर successful, -error otherwise
 */
अटल पूर्णांक nfs_launder_page(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page_file_mapping(page)->host;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	dfprपूर्णांकk(PAGECACHE, "NFS: launder_page(%ld, %llu)\n",
		inode->i_ino, (दीर्घ दीर्घ)page_offset(page));

	nfs_fscache_रुको_on_page_ग_लिखो(nfsi, page);
	वापस nfs_wb_page(inode, page);
पूर्ण

अटल पूर्णांक nfs_swap_activate(काष्ठा swap_info_काष्ठा *sis, काष्ठा file *file,
						sector_t *span)
अणु
	अचिन्हित दीर्घ blocks;
	दीर्घ दीर्घ isize;
	काष्ठा rpc_clnt *clnt = NFS_CLIENT(file->f_mapping->host);
	काष्ठा inode *inode = file->f_mapping->host;

	spin_lock(&inode->i_lock);
	blocks = inode->i_blocks;
	isize = inode->i_size;
	spin_unlock(&inode->i_lock);
	अगर (blocks*512 < isize) अणु
		pr_warn("swap activate: swapfile has holes\n");
		वापस -EINVAL;
	पूर्ण

	*span = sis->pages;

	वापस rpc_clnt_swap_activate(clnt);
पूर्ण

अटल व्योम nfs_swap_deactivate(काष्ठा file *file)
अणु
	काष्ठा rpc_clnt *clnt = NFS_CLIENT(file->f_mapping->host);

	rpc_clnt_swap_deactivate(clnt);
पूर्ण

स्थिर काष्ठा address_space_operations nfs_file_aops = अणु
	.पढ़ोpage = nfs_पढ़ोpage,
	.पढ़ोpages = nfs_पढ़ोpages,
	.set_page_dirty = __set_page_dirty_nobuffers,
	.ग_लिखोpage = nfs_ग_लिखोpage,
	.ग_लिखोpages = nfs_ग_लिखोpages,
	.ग_लिखो_begin = nfs_ग_लिखो_begin,
	.ग_लिखो_end = nfs_ग_लिखो_end,
	.invalidatepage = nfs_invalidate_page,
	.releasepage = nfs_release_page,
	.direct_IO = nfs_direct_IO,
#अगर_घोषित CONFIG_MIGRATION
	.migratepage = nfs_migrate_page,
#पूर्ण_अगर
	.launder_page = nfs_launder_page,
	.is_dirty_ग_लिखोback = nfs_check_dirty_ग_लिखोback,
	.error_हटाओ_page = generic_error_हटाओ_page,
	.swap_activate = nfs_swap_activate,
	.swap_deactivate = nfs_swap_deactivate,
पूर्ण;

/*
 * Notअगरication that a PTE poपूर्णांकing to an NFS page is about to be made
 * writable, implying that someone is about to modअगरy the page through a
 * shared-writable mapping
 */
अटल vm_fault_t nfs_vm_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा file *filp = vmf->vma->vm_file;
	काष्ठा inode *inode = file_inode(filp);
	अचिन्हित pagelen;
	vm_fault_t ret = VM_FAULT_NOPAGE;
	काष्ठा address_space *mapping;

	dfprपूर्णांकk(PAGECACHE, "NFS: vm_page_mkwrite(%pD2(%lu), offset %lld)\n",
		filp, filp->f_mapping->host->i_ino,
		(दीर्घ दीर्घ)page_offset(page));

	sb_start_pagefault(inode->i_sb);

	/* make sure the cache has finished storing the page */
	nfs_fscache_रुको_on_page_ग_लिखो(NFS_I(inode), page);

	रुको_on_bit_action(&NFS_I(inode)->flags, NFS_INO_INVALIDATING,
			nfs_रुको_bit_समाप्तable, TASK_KILLABLE);

	lock_page(page);
	mapping = page_file_mapping(page);
	अगर (mapping != inode->i_mapping)
		जाओ out_unlock;

	रुको_on_page_ग_लिखोback(page);

	pagelen = nfs_page_length(page);
	अगर (pagelen == 0)
		जाओ out_unlock;

	ret = VM_FAULT_LOCKED;
	अगर (nfs_flush_incompatible(filp, page) == 0 &&
	    nfs_updatepage(filp, page, 0, pagelen) == 0)
		जाओ out;

	ret = VM_FAULT_SIGBUS;
out_unlock:
	unlock_page(page);
out:
	sb_end_pagefault(inode->i_sb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा nfs_file_vm_ops = अणु
	.fault = filemap_fault,
	.map_pages = filemap_map_pages,
	.page_mkग_लिखो = nfs_vm_page_mkग_लिखो,
पूर्ण;

अटल पूर्णांक nfs_need_check_ग_लिखो(काष्ठा file *filp, काष्ठा inode *inode,
				पूर्णांक error)
अणु
	काष्ठा nfs_खोलो_context *ctx;

	ctx = nfs_file_खोलो_context(filp);
	अगर (nfs_error_is_fatal_on_server(error) ||
	    nfs_ctx_key_to_expire(ctx, inode))
		वापस 1;
	वापस 0;
पूर्ण

sमाप_प्रकार nfs_file_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	अचिन्हित पूर्णांक mntflags = NFS_SERVER(inode)->flags;
	sमाप_प्रकार result, written;
	errseq_t since;
	पूर्णांक error;

	result = nfs_key_समयout_notअगरy(file, inode);
	अगर (result)
		वापस result;

	अगर (iocb->ki_flags & IOCB_सूचीECT)
		वापस nfs_file_direct_ग_लिखो(iocb, from);

	dprपूर्णांकk("NFS: write(%pD2, %zu@%Ld)\n",
		file, iov_iter_count(from), (दीर्घ दीर्घ) iocb->ki_pos);

	अगर (IS_SWAPखाता(inode))
		जाओ out_swapfile;
	/*
	 * O_APPEND implies that we must revalidate the file length.
	 */
	अगर (iocb->ki_flags & IOCB_APPEND || iocb->ki_pos > i_size_पढ़ो(inode)) अणु
		result = nfs_revalidate_file_size(inode, file);
		अगर (result)
			जाओ out;
	पूर्ण

	nfs_clear_invalid_mapping(file->f_mapping);

	since = filemap_sample_wb_err(file->f_mapping);
	nfs_start_io_ग_लिखो(inode);
	result = generic_ग_लिखो_checks(iocb, from);
	अगर (result > 0) अणु
		current->backing_dev_info = inode_to_bdi(inode);
		result = generic_perक्रमm_ग_लिखो(file, from, iocb->ki_pos);
		current->backing_dev_info = शून्य;
	पूर्ण
	nfs_end_io_ग_लिखो(inode);
	अगर (result <= 0)
		जाओ out;

	written = result;
	iocb->ki_pos += written;

	अगर (mntflags & NFS_MOUNT_WRITE_EAGER) अणु
		result = filemap_fdataग_लिखो_range(file->f_mapping,
						  iocb->ki_pos - written,
						  iocb->ki_pos - 1);
		अगर (result < 0)
			जाओ out;
	पूर्ण
	अगर (mntflags & NFS_MOUNT_WRITE_WAIT) अणु
		result = filemap_fdataरुको_range(file->f_mapping,
						 iocb->ki_pos - written,
						 iocb->ki_pos - 1);
		अगर (result < 0)
			जाओ out;
	पूर्ण
	result = generic_ग_लिखो_sync(iocb, written);
	अगर (result < 0)
		जाओ out;

	/* Return error values */
	error = filemap_check_wb_err(file->f_mapping, since);
	अगर (nfs_need_check_ग_लिखो(file, inode, error)) अणु
		पूर्णांक err = nfs_wb_all(inode);
		अगर (err < 0)
			result = err;
	पूर्ण
	nfs_add_stats(inode, NFSIOS_NORMALWRITTENBYTES, written);
out:
	वापस result;

out_swapfile:
	prपूर्णांकk(KERN_INFO "NFS: attempt to write to active swap file!\n");
	वापस -ETXTBSY;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_file_ग_लिखो);

अटल पूर्णांक
करो_getlk(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl, पूर्णांक is_local)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक saved_type = fl->fl_type;

	/* Try local locking first */
	posix_test_lock(filp, fl);
	अगर (fl->fl_type != F_UNLCK) अणु
		/* found a conflict */
		जाओ out;
	पूर्ण
	fl->fl_type = saved_type;

	अगर (NFS_PROTO(inode)->have_delegation(inode, FMODE_READ))
		जाओ out_noconflict;

	अगर (is_local)
		जाओ out_noconflict;

	status = NFS_PROTO(inode)->lock(filp, cmd, fl);
out:
	वापस status;
out_noconflict:
	fl->fl_type = F_UNLCK;
	जाओ out;
पूर्ण

अटल पूर्णांक
करो_unlk(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl, पूर्णांक is_local)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	काष्ठा nfs_lock_context *l_ctx;
	पूर्णांक status;

	/*
	 * Flush all pending ग_लिखोs beक्रमe करोing anything
	 * with locks..
	 */
	nfs_wb_all(inode);

	l_ctx = nfs_get_lock_context(nfs_file_खोलो_context(filp));
	अगर (!IS_ERR(l_ctx)) अणु
		status = nfs_iocounter_रुको(l_ctx);
		nfs_put_lock_context(l_ctx);
		/*  NOTE: special हाल
		 * 	If we're संकेतled जबतक cleaning up locks on process निकास, we
		 * 	still need to complete the unlock.
		 */
		अगर (status < 0 && !(fl->fl_flags & FL_CLOSE))
			वापस status;
	पूर्ण

	/*
	 * Use local locking अगर mounted with "-onolock" or with appropriate
	 * "-olocal_lock="
	 */
	अगर (!is_local)
		status = NFS_PROTO(inode)->lock(filp, cmd, fl);
	अन्यथा
		status = locks_lock_file_रुको(filp, fl);
	वापस status;
पूर्ण

अटल पूर्णांक
करो_setlk(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl, पूर्णांक is_local)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक status;

	/*
	 * Flush all pending ग_लिखोs beक्रमe करोing anything
	 * with locks..
	 */
	status = nfs_sync_mapping(filp->f_mapping);
	अगर (status != 0)
		जाओ out;

	/*
	 * Use local locking अगर mounted with "-onolock" or with appropriate
	 * "-olocal_lock="
	 */
	अगर (!is_local)
		status = NFS_PROTO(inode)->lock(filp, cmd, fl);
	अन्यथा
		status = locks_lock_file_रुको(filp, fl);
	अगर (status < 0)
		जाओ out;

	/*
	 * Invalidate cache to prevent missing any changes.  If
	 * the file is mapped, clear the page cache as well so
	 * those mappings will be loaded.
	 *
	 * This makes locking act as a cache coherency poपूर्णांक.
	 */
	nfs_sync_mapping(filp->f_mapping);
	अगर (!NFS_PROTO(inode)->have_delegation(inode, FMODE_READ)) अणु
		nfs_zap_caches(inode);
		अगर (mapping_mapped(filp->f_mapping))
			nfs_revalidate_mapping(inode, filp->f_mapping);
	पूर्ण
out:
	वापस status;
पूर्ण

/*
 * Lock a (portion of) a file
 */
पूर्णांक nfs_lock(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक ret = -ENOLCK;
	पूर्णांक is_local = 0;

	dprपूर्णांकk("NFS: lock(%pD2, t=%x, fl=%x, r=%lld:%lld)\n",
			filp, fl->fl_type, fl->fl_flags,
			(दीर्घ दीर्घ)fl->fl_start, (दीर्घ दीर्घ)fl->fl_end);

	nfs_inc_stats(inode, NFSIOS_VFSLOCK);

	/* No mandatory locks over NFS */
	अगर (__mandatory_lock(inode) && fl->fl_type != F_UNLCK)
		जाओ out_err;

	अगर (NFS_SERVER(inode)->flags & NFS_MOUNT_LOCAL_FCNTL)
		is_local = 1;

	अगर (NFS_PROTO(inode)->lock_check_bounds != शून्य) अणु
		ret = NFS_PROTO(inode)->lock_check_bounds(fl);
		अगर (ret < 0)
			जाओ out_err;
	पूर्ण

	अगर (IS_GETLK(cmd))
		ret = करो_getlk(filp, cmd, fl, is_local);
	अन्यथा अगर (fl->fl_type == F_UNLCK)
		ret = करो_unlk(filp, cmd, fl, is_local);
	अन्यथा
		ret = करो_setlk(filp, cmd, fl, is_local);
out_err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_lock);

/*
 * Lock a (portion of) a file
 */
पूर्णांक nfs_flock(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक is_local = 0;

	dprपूर्णांकk("NFS: flock(%pD2, t=%x, fl=%x)\n",
			filp, fl->fl_type, fl->fl_flags);

	अगर (!(fl->fl_flags & FL_FLOCK))
		वापस -ENOLCK;

	/*
	 * The NFSv4 protocol करोesn't support LOCK_MAND, which is not part of
	 * any standard. In principle we might be able to support LOCK_MAND
	 * on NFSv2/3 since NLMv3/4 support DOS share modes, but क्रम now the
	 * NFS code is not set up क्रम it.
	 */
	अगर (fl->fl_type & LOCK_MAND)
		वापस -EINVAL;

	अगर (NFS_SERVER(inode)->flags & NFS_MOUNT_LOCAL_FLOCK)
		is_local = 1;

	/* We're simulating flock() locks using posix locks on the server */
	अगर (fl->fl_type == F_UNLCK)
		वापस करो_unlk(filp, cmd, fl, is_local);
	वापस करो_setlk(filp, cmd, fl, is_local);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_flock);

स्थिर काष्ठा file_operations nfs_file_operations = अणु
	.llseek		= nfs_file_llseek,
	.पढ़ो_iter	= nfs_file_पढ़ो,
	.ग_लिखो_iter	= nfs_file_ग_लिखो,
	.mmap		= nfs_file_mmap,
	.खोलो		= nfs_file_खोलो,
	.flush		= nfs_file_flush,
	.release	= nfs_file_release,
	.fsync		= nfs_file_fsync,
	.lock		= nfs_lock,
	.flock		= nfs_flock,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.check_flags	= nfs_check_flags,
	.setlease	= simple_nosetlease,
पूर्ण;
EXPORT_SYMBOL_GPL(nfs_file_operations);
