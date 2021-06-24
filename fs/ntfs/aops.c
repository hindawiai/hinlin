<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * aops.c - NTFS kernel address space operations and page cache handling.
 *
 * Copyright (c) 2001-2014 Anton Altaparmakov and Tuxera Inc.
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/bit_spinlock.h>
#समावेश <linux/bपन.स>

#समावेश "aops.h"
#समावेश "attrib.h"
#समावेश "debug.h"
#समावेश "inode.h"
#समावेश "mft.h"
#समावेश "runlist.h"
#समावेश "types.h"
#समावेश "ntfs.h"

/**
 * ntfs_end_buffer_async_पढ़ो - async io completion क्रम पढ़ोing attributes
 * @bh:		buffer head on which io is completed
 * @uptodate:	whether @bh is now uptodate or not
 *
 * Asynchronous I/O completion handler क्रम पढ़ोing pages beदीर्घing to the
 * attribute address space of an inode.  The inodes can either be files or
 * directories or they can be fake inodes describing some attribute.
 *
 * If NInoMstProtected(), perक्रमm the post पढ़ो mst fixups when all IO on the
 * page has been completed and mark the page uptodate or set the error bit on
 * the page.  To determine the size of the records that need fixing up, we
 * cheat a little bit by setting the index_block_size in ntfs_inode to the ntfs
 * record size, and index_block_size_bits, to the log(base 2) of the ntfs
 * record size.
 */
अटल व्योम ntfs_end_buffer_async_पढ़ो(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा buffer_head *first, *पंचांगp;
	काष्ठा page *page;
	काष्ठा inode *vi;
	ntfs_inode *ni;
	पूर्णांक page_uptodate = 1;

	page = bh->b_page;
	vi = page->mapping->host;
	ni = NTFS_I(vi);

	अगर (likely(uptodate)) अणु
		loff_t i_size;
		s64 file_ofs, init_size;

		set_buffer_uptodate(bh);

		file_ofs = ((s64)page->index << PAGE_SHIFT) +
				bh_offset(bh);
		पढ़ो_lock_irqsave(&ni->size_lock, flags);
		init_size = ni->initialized_size;
		i_size = i_size_पढ़ो(vi);
		पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
		अगर (unlikely(init_size > i_size)) अणु
			/* Race with shrinking truncate. */
			init_size = i_size;
		पूर्ण
		/* Check क्रम the current buffer head overflowing. */
		अगर (unlikely(file_ofs + bh->b_size > init_size)) अणु
			पूर्णांक ofs;
			व्योम *kaddr;

			ofs = 0;
			अगर (file_ofs < init_size)
				ofs = init_size - file_ofs;
			kaddr = kmap_atomic(page);
			स_रखो(kaddr + bh_offset(bh) + ofs, 0,
					bh->b_size - ofs);
			flush_dcache_page(page);
			kunmap_atomic(kaddr);
		पूर्ण
	पूर्ण अन्यथा अणु
		clear_buffer_uptodate(bh);
		SetPageError(page);
		ntfs_error(ni->vol->sb, "Buffer I/O error, logical block "
				"0x%llx.", (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
	पूर्ण
	first = page_buffers(page);
	spin_lock_irqsave(&first->b_uptodate_lock, flags);
	clear_buffer_async_पढ़ो(bh);
	unlock_buffer(bh);
	पंचांगp = bh;
	करो अणु
		अगर (!buffer_uptodate(पंचांगp))
			page_uptodate = 0;
		अगर (buffer_async_पढ़ो(पंचांगp)) अणु
			अगर (likely(buffer_locked(पंचांगp)))
				जाओ still_busy;
			/* Async buffers must be locked. */
			BUG();
		पूर्ण
		पंचांगp = पंचांगp->b_this_page;
	पूर्ण जबतक (पंचांगp != bh);
	spin_unlock_irqrestore(&first->b_uptodate_lock, flags);
	/*
	 * If none of the buffers had errors then we can set the page uptodate,
	 * but we first have to perक्रमm the post पढ़ो mst fixups, अगर the
	 * attribute is mst रक्षित, i.e. अगर NInoMstProteced(ni) is true.
	 * Note we ignore fixup errors as those are detected when
	 * map_mft_record() is called which gives us per record granularity
	 * rather than per page granularity.
	 */
	अगर (!NInoMstProtected(ni)) अणु
		अगर (likely(page_uptodate && !PageError(page)))
			SetPageUptodate(page);
	पूर्ण अन्यथा अणु
		u8 *kaddr;
		अचिन्हित पूर्णांक i, recs;
		u32 rec_size;

		rec_size = ni->itype.index.block_size;
		recs = PAGE_SIZE / rec_size;
		/* Should have been verअगरied beक्रमe we got here... */
		BUG_ON(!recs);
		kaddr = kmap_atomic(page);
		क्रम (i = 0; i < recs; i++)
			post_पढ़ो_mst_fixup((NTFS_RECORD*)(kaddr +
					i * rec_size), rec_size);
		kunmap_atomic(kaddr);
		flush_dcache_page(page);
		अगर (likely(page_uptodate && !PageError(page)))
			SetPageUptodate(page);
	पूर्ण
	unlock_page(page);
	वापस;
still_busy:
	spin_unlock_irqrestore(&first->b_uptodate_lock, flags);
	वापस;
पूर्ण

/**
 * ntfs_पढ़ो_block - fill a @page of an address space with data
 * @page:	page cache page to fill with data
 *
 * Fill the page @page of the address space beदीर्घing to the @page->host inode.
 * We पढ़ो each buffer asynchronously and when all buffers are पढ़ो in, our io
 * completion handler ntfs_end_buffer_पढ़ो_async(), अगर required, स्वतःmatically
 * applies the mst fixups to the page beक्रमe finally marking it uptodate and
 * unlocking it.
 *
 * We only enक्रमce allocated_size limit because i_size is checked क्रम in
 * generic_file_पढ़ो().
 *
 * Return 0 on success and -त्रुटि_सं on error.
 *
 * Contains an adapted version of fs/buffer.c::block_पढ़ो_full_page().
 */
अटल पूर्णांक ntfs_पढ़ो_block(काष्ठा page *page)
अणु
	loff_t i_size;
	VCN vcn;
	LCN lcn;
	s64 init_size;
	काष्ठा inode *vi;
	ntfs_inode *ni;
	ntfs_volume *vol;
	runlist_element *rl;
	काष्ठा buffer_head *bh, *head, *arr[MAX_BUF_PER_PAGE];
	sector_t iblock, lblock, zblock;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक blocksize, vcn_ofs;
	पूर्णांक i, nr;
	अचिन्हित अक्षर blocksize_bits;

	vi = page->mapping->host;
	ni = NTFS_I(vi);
	vol = ni->vol;

	/* $MFT/$DATA must have its complete runlist in memory at all बार. */
	BUG_ON(!ni->runlist.rl && !ni->mft_no && !NInoAttr(ni));

	blocksize = vol->sb->s_blocksize;
	blocksize_bits = vol->sb->s_blocksize_bits;

	अगर (!page_has_buffers(page)) अणु
		create_empty_buffers(page, blocksize, 0);
		अगर (unlikely(!page_has_buffers(page))) अणु
			unlock_page(page);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	bh = head = page_buffers(page);
	BUG_ON(!bh);

	/*
	 * We may be racing with truncate.  To aव्योम some of the problems we
	 * now take a snapshot of the various sizes and use those क्रम the whole
	 * of the function.  In हाल of an extending truncate it just means we
	 * may leave some buffers unmapped which are now allocated.  This is
	 * not a problem since these buffers will just get mapped when a ग_लिखो
	 * occurs.  In हाल of a shrinking truncate, we will detect this later
	 * on due to the runlist being incomplete and अगर the page is being
	 * fully truncated, truncate will throw it away as soon as we unlock
	 * it so no need to worry what we करो with it.
	 */
	iblock = (s64)page->index << (PAGE_SHIFT - blocksize_bits);
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	lblock = (ni->allocated_size + blocksize - 1) >> blocksize_bits;
	init_size = ni->initialized_size;
	i_size = i_size_पढ़ो(vi);
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	अगर (unlikely(init_size > i_size)) अणु
		/* Race with shrinking truncate. */
		init_size = i_size;
	पूर्ण
	zblock = (init_size + blocksize - 1) >> blocksize_bits;

	/* Loop through all the buffers in the page. */
	rl = शून्य;
	nr = i = 0;
	करो अणु
		पूर्णांक err = 0;

		अगर (unlikely(buffer_uptodate(bh)))
			जारी;
		अगर (unlikely(buffer_mapped(bh))) अणु
			arr[nr++] = bh;
			जारी;
		पूर्ण
		bh->b_bdev = vol->sb->s_bdev;
		/* Is the block within the allowed limits? */
		अगर (iblock < lblock) अणु
			bool is_retry = false;

			/* Convert iblock पूर्णांकo corresponding vcn and offset. */
			vcn = (VCN)iblock << blocksize_bits >>
					vol->cluster_size_bits;
			vcn_ofs = ((VCN)iblock << blocksize_bits) &
					vol->cluster_size_mask;
			अगर (!rl) अणु
lock_retry_remap:
				करोwn_पढ़ो(&ni->runlist.lock);
				rl = ni->runlist.rl;
			पूर्ण
			अगर (likely(rl != शून्य)) अणु
				/* Seek to element containing target vcn. */
				जबतक (rl->length && rl[1].vcn <= vcn)
					rl++;
				lcn = ntfs_rl_vcn_to_lcn(rl, vcn);
			पूर्ण अन्यथा
				lcn = LCN_RL_NOT_MAPPED;
			/* Successful remap. */
			अगर (lcn >= 0) अणु
				/* Setup buffer head to correct block. */
				bh->b_blocknr = ((lcn << vol->cluster_size_bits)
						+ vcn_ofs) >> blocksize_bits;
				set_buffer_mapped(bh);
				/* Only पढ़ो initialized data blocks. */
				अगर (iblock < zblock) अणु
					arr[nr++] = bh;
					जारी;
				पूर्ण
				/* Fully non-initialized data block, zero it. */
				जाओ handle_zblock;
			पूर्ण
			/* It is a hole, need to zero it. */
			अगर (lcn == LCN_HOLE)
				जाओ handle_hole;
			/* If first try and runlist unmapped, map and retry. */
			अगर (!is_retry && lcn == LCN_RL_NOT_MAPPED) अणु
				is_retry = true;
				/*
				 * Attempt to map runlist, dropping lock क्रम
				 * the duration.
				 */
				up_पढ़ो(&ni->runlist.lock);
				err = ntfs_map_runlist(ni, vcn);
				अगर (likely(!err))
					जाओ lock_retry_remap;
				rl = शून्य;
			पूर्ण अन्यथा अगर (!rl)
				up_पढ़ो(&ni->runlist.lock);
			/*
			 * If buffer is outside the runlist, treat it as a
			 * hole.  This can happen due to concurrent truncate
			 * क्रम example.
			 */
			अगर (err == -ENOENT || lcn == LCN_ENOENT) अणु
				err = 0;
				जाओ handle_hole;
			पूर्ण
			/* Hard error, zero out region. */
			अगर (!err)
				err = -EIO;
			bh->b_blocknr = -1;
			SetPageError(page);
			ntfs_error(vol->sb, "Failed to read from inode 0x%lx, "
					"attribute type 0x%x, vcn 0x%llx, "
					"offset 0x%x because its location on "
					"disk could not be determined%s "
					"(error code %i).", ni->mft_no,
					ni->type, (अचिन्हित दीर्घ दीर्घ)vcn,
					vcn_ofs, is_retry ? " even after "
					"retrying" : "", err);
		पूर्ण
		/*
		 * Either iblock was outside lblock limits or
		 * ntfs_rl_vcn_to_lcn() वापसed error.  Just zero that portion
		 * of the page and set the buffer uptodate.
		 */
handle_hole:
		bh->b_blocknr = -1UL;
		clear_buffer_mapped(bh);
handle_zblock:
		zero_user(page, i * blocksize, blocksize);
		अगर (likely(!err))
			set_buffer_uptodate(bh);
	पूर्ण जबतक (i++, iblock++, (bh = bh->b_this_page) != head);

	/* Release the lock अगर we took it. */
	अगर (rl)
		up_पढ़ो(&ni->runlist.lock);

	/* Check we have at least one buffer पढ़ोy क्रम i/o. */
	अगर (nr) अणु
		काष्ठा buffer_head *tbh;

		/* Lock the buffers. */
		क्रम (i = 0; i < nr; i++) अणु
			tbh = arr[i];
			lock_buffer(tbh);
			tbh->b_end_io = ntfs_end_buffer_async_पढ़ो;
			set_buffer_async_पढ़ो(tbh);
		पूर्ण
		/* Finally, start i/o on the buffers. */
		क्रम (i = 0; i < nr; i++) अणु
			tbh = arr[i];
			अगर (likely(!buffer_uptodate(tbh)))
				submit_bh(REQ_OP_READ, 0, tbh);
			अन्यथा
				ntfs_end_buffer_async_पढ़ो(tbh, 1);
		पूर्ण
		वापस 0;
	पूर्ण
	/* No i/o was scheduled on any of the buffers. */
	अगर (likely(!PageError(page)))
		SetPageUptodate(page);
	अन्यथा /* Signal synchronous i/o error. */
		nr = -EIO;
	unlock_page(page);
	वापस nr;
पूर्ण

/**
 * ntfs_पढ़ोpage - fill a @page of a @file with data from the device
 * @file:	खोलो file to which the page @page beदीर्घs or शून्य
 * @page:	page cache page to fill with data
 *
 * For non-resident attributes, ntfs_पढ़ोpage() fills the @page of the खोलो
 * file @file by calling the ntfs version of the generic block_पढ़ो_full_page()
 * function, ntfs_पढ़ो_block(), which in turn creates and पढ़ोs in the buffers
 * associated with the page asynchronously.
 *
 * For resident attributes, OTOH, ntfs_पढ़ोpage() fills @page by copying the
 * data from the mft record (which at this stage is most likely in memory) and
 * fills the reमुख्यder with zeroes. Thus, in this हाल, I/O is synchronous, as
 * even अगर the mft record is not cached at this poपूर्णांक in समय, we need to रुको
 * क्रम it to be पढ़ो in beक्रमe we can करो the copy.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल पूर्णांक ntfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	loff_t i_size;
	काष्ठा inode *vi;
	ntfs_inode *ni, *base_ni;
	u8 *addr;
	ntfs_attr_search_ctx *ctx;
	MFT_RECORD *mrec;
	अचिन्हित दीर्घ flags;
	u32 attr_len;
	पूर्णांक err = 0;

retry_पढ़ोpage:
	BUG_ON(!PageLocked(page));
	vi = page->mapping->host;
	i_size = i_size_पढ़ो(vi);
	/* Is the page fully outside i_size? (truncate in progress) */
	अगर (unlikely(page->index >= (i_size + PAGE_SIZE - 1) >>
			PAGE_SHIFT)) अणु
		zero_user(page, 0, PAGE_SIZE);
		ntfs_debug("Read outside i_size - truncated?");
		जाओ करोne;
	पूर्ण
	/*
	 * This can potentially happen because we clear PageUptodate() during
	 * ntfs_ग_लिखोpage() of MstProtected() attributes.
	 */
	अगर (PageUptodate(page)) अणु
		unlock_page(page);
		वापस 0;
	पूर्ण
	ni = NTFS_I(vi);
	/*
	 * Only $DATA attributes can be encrypted and only unnamed $DATA
	 * attributes can be compressed.  Index root can have the flags set but
	 * this means to create compressed/encrypted files, not that the
	 * attribute is compressed/encrypted.  Note we need to check क्रम
	 * AT_INDEX_ALLOCATION since this is the type of both directory and
	 * index inodes.
	 */
	अगर (ni->type != AT_INDEX_ALLOCATION) अणु
		/* If attribute is encrypted, deny access, just like NT4. */
		अगर (NInoEncrypted(ni)) अणु
			BUG_ON(ni->type != AT_DATA);
			err = -EACCES;
			जाओ err_out;
		पूर्ण
		/* Compressed data streams are handled in compress.c. */
		अगर (NInoNonResident(ni) && NInoCompressed(ni)) अणु
			BUG_ON(ni->type != AT_DATA);
			BUG_ON(ni->name_len);
			वापस ntfs_पढ़ो_compressed_block(page);
		पूर्ण
	पूर्ण
	/* NInoNonResident() == NInoIndexAllocPresent() */
	अगर (NInoNonResident(ni)) अणु
		/* Normal, non-resident data stream. */
		वापस ntfs_पढ़ो_block(page);
	पूर्ण
	/*
	 * Attribute is resident, implying it is not compressed or encrypted.
	 * This also means the attribute is smaller than an mft record and
	 * hence smaller than a page, so can simply zero out any pages with
	 * index above 0.  Note the attribute can actually be marked compressed
	 * but अगर it is resident the actual data is not compressed so we are
	 * ok to ignore the compressed flag here.
	 */
	अगर (unlikely(page->index > 0)) अणु
		zero_user(page, 0, PAGE_SIZE);
		जाओ करोne;
	पूर्ण
	अगर (!NInoAttr(ni))
		base_ni = ni;
	अन्यथा
		base_ni = ni->ext.base_ntfs_ino;
	/* Map, pin, and lock the mft record. */
	mrec = map_mft_record(base_ni);
	अगर (IS_ERR(mrec)) अणु
		err = PTR_ERR(mrec);
		जाओ err_out;
	पूर्ण
	/*
	 * If a parallel ग_लिखो made the attribute non-resident, drop the mft
	 * record and retry the पढ़ोpage.
	 */
	अगर (unlikely(NInoNonResident(ni))) अणु
		unmap_mft_record(base_ni);
		जाओ retry_पढ़ोpage;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, mrec);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ unm_err_out;
	पूर्ण
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err))
		जाओ put_unm_err_out;
	attr_len = le32_to_cpu(ctx->attr->data.resident.value_length);
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	अगर (unlikely(attr_len > ni->initialized_size))
		attr_len = ni->initialized_size;
	i_size = i_size_पढ़ो(vi);
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	अगर (unlikely(attr_len > i_size)) अणु
		/* Race with shrinking truncate. */
		attr_len = i_size;
	पूर्ण
	addr = kmap_atomic(page);
	/* Copy the data to the page. */
	स_नकल(addr, (u8*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset),
			attr_len);
	/* Zero the reमुख्यder of the page. */
	स_रखो(addr + attr_len, 0, PAGE_SIZE - attr_len);
	flush_dcache_page(page);
	kunmap_atomic(addr);
put_unm_err_out:
	ntfs_attr_put_search_ctx(ctx);
unm_err_out:
	unmap_mft_record(base_ni);
करोne:
	SetPageUptodate(page);
err_out:
	unlock_page(page);
	वापस err;
पूर्ण

#अगर_घोषित NTFS_RW

/**
 * ntfs_ग_लिखो_block - ग_लिखो a @page to the backing store
 * @page:	page cache page to ग_लिखो out
 * @wbc:	ग_लिखोback control काष्ठाure
 *
 * This function is क्रम writing pages beदीर्घing to non-resident, non-mst
 * रक्षित attributes to their backing store.
 *
 * For a page with buffers, map and ग_लिखो the dirty buffers asynchronously
 * under page ग_लिखोback. For a page without buffers, create buffers क्रम the
 * page, then proceed as above.
 *
 * If a page करोesn't have buffers the page dirty state is definitive. If a page
 * करोes have buffers, the page dirty state is just a hपूर्णांक, and the buffer dirty
 * state is definitive. (A hपूर्णांक which has rules: dirty buffers against a clean
 * page is illegal. Other combinations are legal and need to be handled. In
 * particular a dirty page containing clean buffers क्रम example.)
 *
 * Return 0 on success and -त्रुटि_सं on error.
 *
 * Based on ntfs_पढ़ो_block() and __block_ग_लिखो_full_page().
 */
अटल पूर्णांक ntfs_ग_लिखो_block(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	VCN vcn;
	LCN lcn;
	s64 initialized_size;
	loff_t i_size;
	sector_t block, dblock, iblock;
	काष्ठा inode *vi;
	ntfs_inode *ni;
	ntfs_volume *vol;
	runlist_element *rl;
	काष्ठा buffer_head *bh, *head;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक blocksize, vcn_ofs;
	पूर्णांक err;
	bool need_end_ग_लिखोback;
	अचिन्हित अक्षर blocksize_bits;

	vi = page->mapping->host;
	ni = NTFS_I(vi);
	vol = ni->vol;

	ntfs_debug("Entering for inode 0x%lx, attribute type 0x%x, page index "
			"0x%lx.", ni->mft_no, ni->type, page->index);

	BUG_ON(!NInoNonResident(ni));
	BUG_ON(NInoMstProtected(ni));
	blocksize = vol->sb->s_blocksize;
	blocksize_bits = vol->sb->s_blocksize_bits;
	अगर (!page_has_buffers(page)) अणु
		BUG_ON(!PageUptodate(page));
		create_empty_buffers(page, blocksize,
				(1 << BH_Uptodate) | (1 << BH_Dirty));
		अगर (unlikely(!page_has_buffers(page))) अणु
			ntfs_warning(vol->sb, "Error allocating page "
					"buffers.  Redirtying page so we try "
					"again later.");
			/*
			 * Put the page back on mapping->dirty_pages, but leave
			 * its buffers' dirty state as-is.
			 */
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			unlock_page(page);
			वापस 0;
		पूर्ण
	पूर्ण
	bh = head = page_buffers(page);
	BUG_ON(!bh);

	/* NOTE: Dअगरferent naming scheme to ntfs_पढ़ो_block()! */

	/* The first block in the page. */
	block = (s64)page->index << (PAGE_SHIFT - blocksize_bits);

	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	i_size = i_size_पढ़ो(vi);
	initialized_size = ni->initialized_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);

	/* The first out of bounds block क्रम the data size. */
	dblock = (i_size + blocksize - 1) >> blocksize_bits;

	/* The last (fully or partially) initialized block. */
	iblock = initialized_size >> blocksize_bits;

	/*
	 * Be very careful.  We have no exclusion from __set_page_dirty_buffers
	 * here, and the (potentially unmapped) buffers may become dirty at
	 * any समय.  If a buffer becomes dirty here after we've inspected it
	 * then we just miss that fact, and the page stays dirty.
	 *
	 * Buffers outside i_size may be dirtied by __set_page_dirty_buffers;
	 * handle that here by just cleaning them.
	 */

	/*
	 * Loop through all the buffers in the page, mapping all the dirty
	 * buffers to disk addresses and handling any aliases from the
	 * underlying block device's mapping.
	 */
	rl = शून्य;
	err = 0;
	करो अणु
		bool is_retry = false;

		अगर (unlikely(block >= dblock)) अणु
			/*
			 * Mapped buffers outside i_size will occur, because
			 * this page can be outside i_size when there is a
			 * truncate in progress. The contents of such buffers
			 * were zeroed by ntfs_ग_लिखोpage().
			 *
			 * FIXME: What about the small race winकरोw where
			 * ntfs_ग_लिखोpage() has not करोne any clearing because
			 * the page was within i_size but beक्रमe we get here,
			 * vmtruncate() modअगरies i_size?
			 */
			clear_buffer_dirty(bh);
			set_buffer_uptodate(bh);
			जारी;
		पूर्ण

		/* Clean buffers are not written out, so no need to map them. */
		अगर (!buffer_dirty(bh))
			जारी;

		/* Make sure we have enough initialized size. */
		अगर (unlikely((block >= iblock) &&
				(initialized_size < i_size))) अणु
			/*
			 * If this page is fully outside initialized size, zero
			 * out all pages between the current initialized size
			 * and the current page. Just use ntfs_पढ़ोpage() to करो
			 * the zeroing transparently.
			 */
			अगर (block > iblock) अणु
				// TODO:
				// For each page करो:
				// - पढ़ो_cache_page()
				// Again क्रम each page करो:
				// - रुको_on_page_locked()
				// - Check (PageUptodate(page) &&
				//			!PageError(page))
				// Update initialized size in the attribute and
				// in the inode.
				// Again, क्रम each page करो:
				//	__set_page_dirty_buffers();
				// put_page()
				// We करोn't need to रुको on the ग_लिखोs.
				// Update iblock.
			पूर्ण
			/*
			 * The current page straddles initialized size. Zero
			 * all non-uptodate buffers and set them uptodate (and
			 * dirty?). Note, there aren't any non-uptodate buffers
			 * अगर the page is uptodate.
			 * FIXME: For an uptodate page, the buffers may need to
			 * be written out because they were not initialized on
			 * disk beक्रमe.
			 */
			अगर (!PageUptodate(page)) अणु
				// TODO:
				// Zero any non-uptodate buffers up to i_size.
				// Set them uptodate and dirty.
			पूर्ण
			// TODO:
			// Update initialized size in the attribute and in the
			// inode (up to i_size).
			// Update iblock.
			// FIXME: This is inefficient. Try to batch the two
			// size changes to happen in one go.
			ntfs_error(vol->sb, "Writing beyond initialized size "
					"is not supported yet. Sorry.");
			err = -EOPNOTSUPP;
			अवरोध;
			// Do NOT set_buffer_new() BUT DO clear buffer range
			// outside ग_लिखो request range.
			// set_buffer_uptodate() on complete buffers as well as
			// set_buffer_dirty().
		पूर्ण

		/* No need to map buffers that are alपढ़ोy mapped. */
		अगर (buffer_mapped(bh))
			जारी;

		/* Unmapped, dirty buffer. Need to map it. */
		bh->b_bdev = vol->sb->s_bdev;

		/* Convert block पूर्णांकo corresponding vcn and offset. */
		vcn = (VCN)block << blocksize_bits;
		vcn_ofs = vcn & vol->cluster_size_mask;
		vcn >>= vol->cluster_size_bits;
		अगर (!rl) अणु
lock_retry_remap:
			करोwn_पढ़ो(&ni->runlist.lock);
			rl = ni->runlist.rl;
		पूर्ण
		अगर (likely(rl != शून्य)) अणु
			/* Seek to element containing target vcn. */
			जबतक (rl->length && rl[1].vcn <= vcn)
				rl++;
			lcn = ntfs_rl_vcn_to_lcn(rl, vcn);
		पूर्ण अन्यथा
			lcn = LCN_RL_NOT_MAPPED;
		/* Successful remap. */
		अगर (lcn >= 0) अणु
			/* Setup buffer head to poपूर्णांक to correct block. */
			bh->b_blocknr = ((lcn << vol->cluster_size_bits) +
					vcn_ofs) >> blocksize_bits;
			set_buffer_mapped(bh);
			जारी;
		पूर्ण
		/* It is a hole, need to instantiate it. */
		अगर (lcn == LCN_HOLE) अणु
			u8 *kaddr;
			अचिन्हित दीर्घ *bpos, *bend;

			/* Check अगर the buffer is zero. */
			kaddr = kmap_atomic(page);
			bpos = (अचिन्हित दीर्घ *)(kaddr + bh_offset(bh));
			bend = (अचिन्हित दीर्घ *)((u8*)bpos + blocksize);
			करो अणु
				अगर (unlikely(*bpos))
					अवरोध;
			पूर्ण जबतक (likely(++bpos < bend));
			kunmap_atomic(kaddr);
			अगर (bpos == bend) अणु
				/*
				 * Buffer is zero and sparse, no need to ग_लिखो
				 * it.
				 */
				bh->b_blocknr = -1;
				clear_buffer_dirty(bh);
				जारी;
			पूर्ण
			// TODO: Instantiate the hole.
			// clear_buffer_new(bh);
			// clean_bdev_bh_alias(bh);
			ntfs_error(vol->sb, "Writing into sparse regions is "
					"not supported yet. Sorry.");
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		/* If first try and runlist unmapped, map and retry. */
		अगर (!is_retry && lcn == LCN_RL_NOT_MAPPED) अणु
			is_retry = true;
			/*
			 * Attempt to map runlist, dropping lock क्रम
			 * the duration.
			 */
			up_पढ़ो(&ni->runlist.lock);
			err = ntfs_map_runlist(ni, vcn);
			अगर (likely(!err))
				जाओ lock_retry_remap;
			rl = शून्य;
		पूर्ण अन्यथा अगर (!rl)
			up_पढ़ो(&ni->runlist.lock);
		/*
		 * If buffer is outside the runlist, truncate has cut it out
		 * of the runlist.  Just clean and clear the buffer and set it
		 * uptodate so it can get discarded by the VM.
		 */
		अगर (err == -ENOENT || lcn == LCN_ENOENT) अणु
			bh->b_blocknr = -1;
			clear_buffer_dirty(bh);
			zero_user(page, bh_offset(bh), blocksize);
			set_buffer_uptodate(bh);
			err = 0;
			जारी;
		पूर्ण
		/* Failed to map the buffer, even after retrying. */
		अगर (!err)
			err = -EIO;
		bh->b_blocknr = -1;
		ntfs_error(vol->sb, "Failed to write to inode 0x%lx, "
				"attribute type 0x%x, vcn 0x%llx, offset 0x%x "
				"because its location on disk could not be "
				"determined%s (error code %i).", ni->mft_no,
				ni->type, (अचिन्हित दीर्घ दीर्घ)vcn,
				vcn_ofs, is_retry ? " even after "
				"retrying" : "", err);
		अवरोध;
	पूर्ण जबतक (block++, (bh = bh->b_this_page) != head);

	/* Release the lock अगर we took it. */
	अगर (rl)
		up_पढ़ो(&ni->runlist.lock);

	/* For the error हाल, need to reset bh to the beginning. */
	bh = head;

	/* Just an optimization, so ->पढ़ोpage() is not called later. */
	अगर (unlikely(!PageUptodate(page))) अणु
		पूर्णांक uptodate = 1;
		करो अणु
			अगर (!buffer_uptodate(bh)) अणु
				uptodate = 0;
				bh = head;
				अवरोध;
			पूर्ण
		पूर्ण जबतक ((bh = bh->b_this_page) != head);
		अगर (uptodate)
			SetPageUptodate(page);
	पूर्ण

	/* Setup all mapped, dirty buffers क्रम async ग_लिखो i/o. */
	करो अणु
		अगर (buffer_mapped(bh) && buffer_dirty(bh)) अणु
			lock_buffer(bh);
			अगर (test_clear_buffer_dirty(bh)) अणु
				BUG_ON(!buffer_uptodate(bh));
				mark_buffer_async_ग_लिखो(bh);
			पूर्ण अन्यथा
				unlock_buffer(bh);
		पूर्ण अन्यथा अगर (unlikely(err)) अणु
			/*
			 * For the error हाल. The buffer may have been set
			 * dirty during attachment to a dirty page.
			 */
			अगर (err != -ENOMEM)
				clear_buffer_dirty(bh);
		पूर्ण
	पूर्ण जबतक ((bh = bh->b_this_page) != head);

	अगर (unlikely(err)) अणु
		// TODO: Remove the -EOPNOTSUPP check later on...
		अगर (unlikely(err == -EOPNOTSUPP))
			err = 0;
		अन्यथा अगर (err == -ENOMEM) अणु
			ntfs_warning(vol->sb, "Error allocating memory. "
					"Redirtying page so we try again "
					"later.");
			/*
			 * Put the page back on mapping->dirty_pages, but
			 * leave its buffer's dirty state as-is.
			 */
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			err = 0;
		पूर्ण अन्यथा
			SetPageError(page);
	पूर्ण

	BUG_ON(PageWriteback(page));
	set_page_ग_लिखोback(page);	/* Keeps try_to_मुक्त_buffers() away. */

	/* Submit the prepared buffers क्रम i/o. */
	need_end_ग_लिखोback = true;
	करो अणु
		काष्ठा buffer_head *next = bh->b_this_page;
		अगर (buffer_async_ग_लिखो(bh)) अणु
			submit_bh(REQ_OP_WRITE, 0, bh);
			need_end_ग_लिखोback = false;
		पूर्ण
		bh = next;
	पूर्ण जबतक (bh != head);
	unlock_page(page);

	/* If no i/o was started, need to end_page_ग_लिखोback(). */
	अगर (unlikely(need_end_ग_लिखोback))
		end_page_ग_लिखोback(page);

	ntfs_debug("Done.");
	वापस err;
पूर्ण

/**
 * ntfs_ग_लिखो_mst_block - ग_लिखो a @page to the backing store
 * @page:	page cache page to ग_लिखो out
 * @wbc:	ग_लिखोback control काष्ठाure
 *
 * This function is क्रम writing pages beदीर्घing to non-resident, mst रक्षित
 * attributes to their backing store.  The only supported attributes are index
 * allocation and $MFT/$DATA.  Both directory inodes and index inodes are
 * supported क्रम the index allocation हाल.
 *
 * The page must reमुख्य locked क्रम the duration of the ग_लिखो because we apply
 * the mst fixups, ग_लिखो, and then unकरो the fixups, so अगर we were to unlock the
 * page beक्रमe unकरोing the fixups, any other user of the page will see the
 * page contents as corrupt.
 *
 * We clear the page uptodate flag क्रम the duration of the function to ensure
 * exclusion क्रम the $MFT/$DATA हाल against someone mapping an mft record we
 * are about to apply the mst fixups to.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 *
 * Based on ntfs_ग_लिखो_block(), ntfs_mft_ग_लिखोpage(), and
 * ग_लिखो_mft_record_nolock().
 */
अटल पूर्णांक ntfs_ग_लिखो_mst_block(काष्ठा page *page,
		काष्ठा ग_लिखोback_control *wbc)
अणु
	sector_t block, dblock, rec_block;
	काष्ठा inode *vi = page->mapping->host;
	ntfs_inode *ni = NTFS_I(vi);
	ntfs_volume *vol = ni->vol;
	u8 *kaddr;
	अचिन्हित पूर्णांक rec_size = ni->itype.index.block_size;
	ntfs_inode *locked_nis[PAGE_SIZE / NTFS_BLOCK_SIZE];
	काष्ठा buffer_head *bh, *head, *tbh, *rec_start_bh;
	काष्ठा buffer_head *bhs[MAX_BUF_PER_PAGE];
	runlist_element *rl;
	पूर्णांक i, nr_locked_nis, nr_recs, nr_bhs, max_bhs, bhs_per_rec, err, err2;
	अचिन्हित bh_size, rec_size_bits;
	bool sync, is_mft, page_is_dirty, rec_is_dirty;
	अचिन्हित अक्षर bh_size_bits;

	अगर (WARN_ON(rec_size < NTFS_BLOCK_SIZE))
		वापस -EINVAL;

	ntfs_debug("Entering for inode 0x%lx, attribute type 0x%x, page index "
			"0x%lx.", vi->i_ino, ni->type, page->index);
	BUG_ON(!NInoNonResident(ni));
	BUG_ON(!NInoMstProtected(ni));
	is_mft = (S_ISREG(vi->i_mode) && !vi->i_ino);
	/*
	 * NOTE: ntfs_ग_लिखो_mst_block() would be called क्रम $MFTMirr अगर a page
	 * in its page cache were to be marked dirty.  However this should
	 * never happen with the current driver and considering we करो not
	 * handle this हाल here we करो want to BUG(), at least क्रम now.
	 */
	BUG_ON(!(is_mft || S_ISसूची(vi->i_mode) ||
			(NInoAttr(ni) && ni->type == AT_INDEX_ALLOCATION)));
	bh_size = vol->sb->s_blocksize;
	bh_size_bits = vol->sb->s_blocksize_bits;
	max_bhs = PAGE_SIZE / bh_size;
	BUG_ON(!max_bhs);
	BUG_ON(max_bhs > MAX_BUF_PER_PAGE);

	/* Were we called क्रम sync purposes? */
	sync = (wbc->sync_mode == WB_SYNC_ALL);

	/* Make sure we have mapped buffers. */
	bh = head = page_buffers(page);
	BUG_ON(!bh);

	rec_size_bits = ni->itype.index.block_size_bits;
	BUG_ON(!(PAGE_SIZE >> rec_size_bits));
	bhs_per_rec = rec_size >> bh_size_bits;
	BUG_ON(!bhs_per_rec);

	/* The first block in the page. */
	rec_block = block = (sector_t)page->index <<
			(PAGE_SHIFT - bh_size_bits);

	/* The first out of bounds block क्रम the data size. */
	dblock = (i_size_पढ़ो(vi) + bh_size - 1) >> bh_size_bits;

	rl = शून्य;
	err = err2 = nr_bhs = nr_recs = nr_locked_nis = 0;
	page_is_dirty = rec_is_dirty = false;
	rec_start_bh = शून्य;
	करो अणु
		bool is_retry = false;

		अगर (likely(block < rec_block)) अणु
			अगर (unlikely(block >= dblock)) अणु
				clear_buffer_dirty(bh);
				set_buffer_uptodate(bh);
				जारी;
			पूर्ण
			/*
			 * This block is not the first one in the record.  We
			 * ignore the buffer's dirty state because we could
			 * have raced with a parallel mark_ntfs_record_dirty().
			 */
			अगर (!rec_is_dirty)
				जारी;
			अगर (unlikely(err2)) अणु
				अगर (err2 != -ENOMEM)
					clear_buffer_dirty(bh);
				जारी;
			पूर्ण
		पूर्ण अन्यथा /* अगर (block == rec_block) */ अणु
			BUG_ON(block > rec_block);
			/* This block is the first one in the record. */
			rec_block += bhs_per_rec;
			err2 = 0;
			अगर (unlikely(block >= dblock)) अणु
				clear_buffer_dirty(bh);
				जारी;
			पूर्ण
			अगर (!buffer_dirty(bh)) अणु
				/* Clean records are not written out. */
				rec_is_dirty = false;
				जारी;
			पूर्ण
			rec_is_dirty = true;
			rec_start_bh = bh;
		पूर्ण
		/* Need to map the buffer अगर it is not mapped alपढ़ोy. */
		अगर (unlikely(!buffer_mapped(bh))) अणु
			VCN vcn;
			LCN lcn;
			अचिन्हित पूर्णांक vcn_ofs;

			bh->b_bdev = vol->sb->s_bdev;
			/* Obtain the vcn and offset of the current block. */
			vcn = (VCN)block << bh_size_bits;
			vcn_ofs = vcn & vol->cluster_size_mask;
			vcn >>= vol->cluster_size_bits;
			अगर (!rl) अणु
lock_retry_remap:
				करोwn_पढ़ो(&ni->runlist.lock);
				rl = ni->runlist.rl;
			पूर्ण
			अगर (likely(rl != शून्य)) अणु
				/* Seek to element containing target vcn. */
				जबतक (rl->length && rl[1].vcn <= vcn)
					rl++;
				lcn = ntfs_rl_vcn_to_lcn(rl, vcn);
			पूर्ण अन्यथा
				lcn = LCN_RL_NOT_MAPPED;
			/* Successful remap. */
			अगर (likely(lcn >= 0)) अणु
				/* Setup buffer head to correct block. */
				bh->b_blocknr = ((lcn <<
						vol->cluster_size_bits) +
						vcn_ofs) >> bh_size_bits;
				set_buffer_mapped(bh);
			पूर्ण अन्यथा अणु
				/*
				 * Remap failed.  Retry to map the runlist once
				 * unless we are working on $MFT which always
				 * has the whole of its runlist in memory.
				 */
				अगर (!is_mft && !is_retry &&
						lcn == LCN_RL_NOT_MAPPED) अणु
					is_retry = true;
					/*
					 * Attempt to map runlist, dropping
					 * lock क्रम the duration.
					 */
					up_पढ़ो(&ni->runlist.lock);
					err2 = ntfs_map_runlist(ni, vcn);
					अगर (likely(!err2))
						जाओ lock_retry_remap;
					अगर (err2 == -ENOMEM)
						page_is_dirty = true;
					lcn = err2;
				पूर्ण अन्यथा अणु
					err2 = -EIO;
					अगर (!rl)
						up_पढ़ो(&ni->runlist.lock);
				पूर्ण
				/* Hard error.  Abort writing this record. */
				अगर (!err || err == -ENOMEM)
					err = err2;
				bh->b_blocknr = -1;
				ntfs_error(vol->sb, "Cannot write ntfs record "
						"0x%llx (inode 0x%lx, "
						"attribute type 0x%x) because "
						"its location on disk could "
						"not be determined (error "
						"code %lli).",
						(दीर्घ दीर्घ)block <<
						bh_size_bits >>
						vol->mft_record_size_bits,
						ni->mft_no, ni->type,
						(दीर्घ दीर्घ)lcn);
				/*
				 * If this is not the first buffer, हटाओ the
				 * buffers in this record from the list of
				 * buffers to ग_लिखो and clear their dirty bit
				 * अगर not error -ENOMEM.
				 */
				अगर (rec_start_bh != bh) अणु
					जबतक (bhs[--nr_bhs] != rec_start_bh)
						;
					अगर (err2 != -ENOMEM) अणु
						करो अणु
							clear_buffer_dirty(
								rec_start_bh);
						पूर्ण जबतक ((rec_start_bh =
								rec_start_bh->
								b_this_page) !=
								bh);
					पूर्ण
				पूर्ण
				जारी;
			पूर्ण
		पूर्ण
		BUG_ON(!buffer_uptodate(bh));
		BUG_ON(nr_bhs >= max_bhs);
		bhs[nr_bhs++] = bh;
	पूर्ण जबतक (block++, (bh = bh->b_this_page) != head);
	अगर (unlikely(rl))
		up_पढ़ो(&ni->runlist.lock);
	/* If there were no dirty buffers, we are करोne. */
	अगर (!nr_bhs)
		जाओ करोne;
	/* Map the page so we can access its contents. */
	kaddr = kmap(page);
	/* Clear the page uptodate flag whilst the mst fixups are applied. */
	BUG_ON(!PageUptodate(page));
	ClearPageUptodate(page);
	क्रम (i = 0; i < nr_bhs; i++) अणु
		अचिन्हित पूर्णांक ofs;

		/* Skip buffers which are not at the beginning of records. */
		अगर (i % bhs_per_rec)
			जारी;
		tbh = bhs[i];
		ofs = bh_offset(tbh);
		अगर (is_mft) अणु
			ntfs_inode *tni;
			अचिन्हित दीर्घ mft_no;

			/* Get the mft record number. */
			mft_no = (((s64)page->index << PAGE_SHIFT) + ofs)
					>> rec_size_bits;
			/* Check whether to ग_लिखो this mft record. */
			tni = शून्य;
			अगर (!ntfs_may_ग_लिखो_mft_record(vol, mft_no,
					(MFT_RECORD*)(kaddr + ofs), &tni)) अणु
				/*
				 * The record should not be written.  This
				 * means we need to redirty the page beक्रमe
				 * वापसing.
				 */
				page_is_dirty = true;
				/*
				 * Remove the buffers in this mft record from
				 * the list of buffers to ग_लिखो.
				 */
				करो अणु
					bhs[i] = शून्य;
				पूर्ण जबतक (++i % bhs_per_rec);
				जारी;
			पूर्ण
			/*
			 * The record should be written.  If a locked ntfs
			 * inode was वापसed, add it to the array of locked
			 * ntfs inodes.
			 */
			अगर (tni)
				locked_nis[nr_locked_nis++] = tni;
		पूर्ण
		/* Apply the mst protection fixups. */
		err2 = pre_ग_लिखो_mst_fixup((NTFS_RECORD*)(kaddr + ofs),
				rec_size);
		अगर (unlikely(err2)) अणु
			अगर (!err || err == -ENOMEM)
				err = -EIO;
			ntfs_error(vol->sb, "Failed to apply mst fixups "
					"(inode 0x%lx, attribute type 0x%x, "
					"page index 0x%lx, page offset 0x%x)!"
					"  Unmount and run chkdsk.", vi->i_ino,
					ni->type, page->index, ofs);
			/*
			 * Mark all the buffers in this record clean as we करो
			 * not want to ग_लिखो corrupt data to disk.
			 */
			करो अणु
				clear_buffer_dirty(bhs[i]);
				bhs[i] = शून्य;
			पूर्ण जबतक (++i % bhs_per_rec);
			जारी;
		पूर्ण
		nr_recs++;
	पूर्ण
	/* If no records are to be written out, we are करोne. */
	अगर (!nr_recs)
		जाओ unm_करोne;
	flush_dcache_page(page);
	/* Lock buffers and start synchronous ग_लिखो i/o on them. */
	क्रम (i = 0; i < nr_bhs; i++) अणु
		tbh = bhs[i];
		अगर (!tbh)
			जारी;
		अगर (!trylock_buffer(tbh))
			BUG();
		/* The buffer dirty state is now irrelevant, just clean it. */
		clear_buffer_dirty(tbh);
		BUG_ON(!buffer_uptodate(tbh));
		BUG_ON(!buffer_mapped(tbh));
		get_bh(tbh);
		tbh->b_end_io = end_buffer_ग_लिखो_sync;
		submit_bh(REQ_OP_WRITE, 0, tbh);
	पूर्ण
	/* Synchronize the mft mirror now अगर not @sync. */
	अगर (is_mft && !sync)
		जाओ करो_mirror;
करो_रुको:
	/* Wait on i/o completion of buffers. */
	क्रम (i = 0; i < nr_bhs; i++) अणु
		tbh = bhs[i];
		अगर (!tbh)
			जारी;
		रुको_on_buffer(tbh);
		अगर (unlikely(!buffer_uptodate(tbh))) अणु
			ntfs_error(vol->sb, "I/O error while writing ntfs "
					"record buffer (inode 0x%lx, "
					"attribute type 0x%x, page index "
					"0x%lx, page offset 0x%lx)!  Unmount "
					"and run chkdsk.", vi->i_ino, ni->type,
					page->index, bh_offset(tbh));
			अगर (!err || err == -ENOMEM)
				err = -EIO;
			/*
			 * Set the buffer uptodate so the page and buffer
			 * states करो not become out of sync.
			 */
			set_buffer_uptodate(tbh);
		पूर्ण
	पूर्ण
	/* If @sync, now synchronize the mft mirror. */
	अगर (is_mft && sync) अणु
करो_mirror:
		क्रम (i = 0; i < nr_bhs; i++) अणु
			अचिन्हित दीर्घ mft_no;
			अचिन्हित पूर्णांक ofs;

			/*
			 * Skip buffers which are not at the beginning of
			 * records.
			 */
			अगर (i % bhs_per_rec)
				जारी;
			tbh = bhs[i];
			/* Skip हटाओd buffers (and hence records). */
			अगर (!tbh)
				जारी;
			ofs = bh_offset(tbh);
			/* Get the mft record number. */
			mft_no = (((s64)page->index << PAGE_SHIFT) + ofs)
					>> rec_size_bits;
			अगर (mft_no < vol->mfपंचांगirr_size)
				ntfs_sync_mft_mirror(vol, mft_no,
						(MFT_RECORD*)(kaddr + ofs),
						sync);
		पूर्ण
		अगर (!sync)
			जाओ करो_रुको;
	पूर्ण
	/* Remove the mst protection fixups again. */
	क्रम (i = 0; i < nr_bhs; i++) अणु
		अगर (!(i % bhs_per_rec)) अणु
			tbh = bhs[i];
			अगर (!tbh)
				जारी;
			post_ग_लिखो_mst_fixup((NTFS_RECORD*)(kaddr +
					bh_offset(tbh)));
		पूर्ण
	पूर्ण
	flush_dcache_page(page);
unm_करोne:
	/* Unlock any locked inodes. */
	जबतक (nr_locked_nis-- > 0) अणु
		ntfs_inode *tni, *base_tni;
		
		tni = locked_nis[nr_locked_nis];
		/* Get the base inode. */
		mutex_lock(&tni->extent_lock);
		अगर (tni->nr_extents >= 0)
			base_tni = tni;
		अन्यथा अणु
			base_tni = tni->ext.base_ntfs_ino;
			BUG_ON(!base_tni);
		पूर्ण
		mutex_unlock(&tni->extent_lock);
		ntfs_debug("Unlocking %s inode 0x%lx.",
				tni == base_tni ? "base" : "extent",
				tni->mft_no);
		mutex_unlock(&tni->mrec_lock);
		atomic_dec(&tni->count);
		iput(VFS_I(base_tni));
	पूर्ण
	SetPageUptodate(page);
	kunmap(page);
करोne:
	अगर (unlikely(err && err != -ENOMEM)) अणु
		/*
		 * Set page error अगर there is only one ntfs record in the page.
		 * Otherwise we would loose per-record granularity.
		 */
		अगर (ni->itype.index.block_size == PAGE_SIZE)
			SetPageError(page);
		NVolSetErrors(vol);
	पूर्ण
	अगर (page_is_dirty) अणु
		ntfs_debug("Page still contains one or more dirty ntfs "
				"records.  Redirtying the page starting at "
				"record 0x%lx.", page->index <<
				(PAGE_SHIFT - rec_size_bits));
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		unlock_page(page);
	पूर्ण अन्यथा अणु
		/*
		 * Keep the VM happy.  This must be करोne otherwise the
		 * radix-tree tag PAGECACHE_TAG_सूचीTY reमुख्यs set even though
		 * the page is clean.
		 */
		BUG_ON(PageWriteback(page));
		set_page_ग_लिखोback(page);
		unlock_page(page);
		end_page_ग_लिखोback(page);
	पूर्ण
	अगर (likely(!err))
		ntfs_debug("Done.");
	वापस err;
पूर्ण

/**
 * ntfs_ग_लिखोpage - ग_लिखो a @page to the backing store
 * @page:	page cache page to ग_लिखो out
 * @wbc:	ग_लिखोback control काष्ठाure
 *
 * This is called from the VM when it wants to have a dirty ntfs page cache
 * page cleaned.  The VM has alपढ़ोy locked the page and marked it clean.
 *
 * For non-resident attributes, ntfs_ग_लिखोpage() ग_लिखोs the @page by calling
 * the ntfs version of the generic block_ग_लिखो_full_page() function,
 * ntfs_ग_लिखो_block(), which in turn अगर necessary creates and ग_लिखोs the
 * buffers associated with the page asynchronously.
 *
 * For resident attributes, OTOH, ntfs_ग_लिखोpage() ग_लिखोs the @page by copying
 * the data to the mft record (which at this stage is most likely in memory).
 * The mft record is then marked dirty and written out asynchronously via the
 * vfs inode dirty code path क्रम the inode the mft record beदीर्घs to or via the
 * vm page dirty code path क्रम the page the mft record is in.
 *
 * Based on ntfs_पढ़ोpage() and fs/buffer.c::block_ग_लिखो_full_page().
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल पूर्णांक ntfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	loff_t i_size;
	काष्ठा inode *vi = page->mapping->host;
	ntfs_inode *base_ni = शून्य, *ni = NTFS_I(vi);
	अक्षर *addr;
	ntfs_attr_search_ctx *ctx = शून्य;
	MFT_RECORD *m = शून्य;
	u32 attr_len;
	पूर्णांक err;

retry_ग_लिखोpage:
	BUG_ON(!PageLocked(page));
	i_size = i_size_पढ़ो(vi);
	/* Is the page fully outside i_size? (truncate in progress) */
	अगर (unlikely(page->index >= (i_size + PAGE_SIZE - 1) >>
			PAGE_SHIFT)) अणु
		/*
		 * The page may have dirty, unmapped buffers.  Make them
		 * मुक्तable here, so the page करोes not leak.
		 */
		block_invalidatepage(page, 0, PAGE_SIZE);
		unlock_page(page);
		ntfs_debug("Write outside i_size - truncated?");
		वापस 0;
	पूर्ण
	/*
	 * Only $DATA attributes can be encrypted and only unnamed $DATA
	 * attributes can be compressed.  Index root can have the flags set but
	 * this means to create compressed/encrypted files, not that the
	 * attribute is compressed/encrypted.  Note we need to check क्रम
	 * AT_INDEX_ALLOCATION since this is the type of both directory and
	 * index inodes.
	 */
	अगर (ni->type != AT_INDEX_ALLOCATION) अणु
		/* If file is encrypted, deny access, just like NT4. */
		अगर (NInoEncrypted(ni)) अणु
			unlock_page(page);
			BUG_ON(ni->type != AT_DATA);
			ntfs_debug("Denying write access to encrypted file.");
			वापस -EACCES;
		पूर्ण
		/* Compressed data streams are handled in compress.c. */
		अगर (NInoNonResident(ni) && NInoCompressed(ni)) अणु
			BUG_ON(ni->type != AT_DATA);
			BUG_ON(ni->name_len);
			// TODO: Implement and replace this with
			// वापस ntfs_ग_लिखो_compressed_block(page);
			unlock_page(page);
			ntfs_error(vi->i_sb, "Writing to compressed files is "
					"not supported yet.  Sorry.");
			वापस -EOPNOTSUPP;
		पूर्ण
		// TODO: Implement and हटाओ this check.
		अगर (NInoNonResident(ni) && NInoSparse(ni)) अणु
			unlock_page(page);
			ntfs_error(vi->i_sb, "Writing to sparse files is not "
					"supported yet.  Sorry.");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	/* NInoNonResident() == NInoIndexAllocPresent() */
	अगर (NInoNonResident(ni)) अणु
		/* We have to zero every समय due to mmap-at-end-of-file. */
		अगर (page->index >= (i_size >> PAGE_SHIFT)) अणु
			/* The page straddles i_size. */
			अचिन्हित पूर्णांक ofs = i_size & ~PAGE_MASK;
			zero_user_segment(page, ofs, PAGE_SIZE);
		पूर्ण
		/* Handle mst रक्षित attributes. */
		अगर (NInoMstProtected(ni))
			वापस ntfs_ग_लिखो_mst_block(page, wbc);
		/* Normal, non-resident data stream. */
		वापस ntfs_ग_लिखो_block(page, wbc);
	पूर्ण
	/*
	 * Attribute is resident, implying it is not compressed, encrypted, or
	 * mst रक्षित.  This also means the attribute is smaller than an mft
	 * record and hence smaller than a page, so can simply वापस error on
	 * any pages with index above 0.  Note the attribute can actually be
	 * marked compressed but अगर it is resident the actual data is not
	 * compressed so we are ok to ignore the compressed flag here.
	 */
	BUG_ON(page_has_buffers(page));
	BUG_ON(!PageUptodate(page));
	अगर (unlikely(page->index > 0)) अणु
		ntfs_error(vi->i_sb, "BUG()! page->index (0x%lx) > 0.  "
				"Aborting write.", page->index);
		BUG_ON(PageWriteback(page));
		set_page_ग_लिखोback(page);
		unlock_page(page);
		end_page_ग_लिखोback(page);
		वापस -EIO;
	पूर्ण
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
	/*
	 * If a parallel ग_लिखो made the attribute non-resident, drop the mft
	 * record and retry the ग_लिखोpage.
	 */
	अगर (unlikely(NInoNonResident(ni))) अणु
		unmap_mft_record(base_ni);
		जाओ retry_ग_लिखोpage;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err))
		जाओ err_out;
	/*
	 * Keep the VM happy.  This must be करोne otherwise the radix-tree tag
	 * PAGECACHE_TAG_सूचीTY reमुख्यs set even though the page is clean.
	 */
	BUG_ON(PageWriteback(page));
	set_page_ग_लिखोback(page);
	unlock_page(page);
	attr_len = le32_to_cpu(ctx->attr->data.resident.value_length);
	i_size = i_size_पढ़ो(vi);
	अगर (unlikely(attr_len > i_size)) अणु
		/* Race with shrinking truncate or a failed truncate. */
		attr_len = i_size;
		/*
		 * If the truncate failed, fix it up now.  If a concurrent
		 * truncate, we करो its job, so it करोes not have to करो anything.
		 */
		err = ntfs_resident_attr_value_resize(ctx->mrec, ctx->attr,
				attr_len);
		/* Shrinking cannot fail. */
		BUG_ON(err);
	पूर्ण
	addr = kmap_atomic(page);
	/* Copy the data from the page to the mft record. */
	स_नकल((u8*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset),
			addr, attr_len);
	/* Zero out of bounds area in the page cache page. */
	स_रखो(addr + attr_len, 0, PAGE_SIZE - attr_len);
	kunmap_atomic(addr);
	flush_dcache_page(page);
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	/* We are करोne with the page. */
	end_page_ग_लिखोback(page);
	/* Finally, mark the mft record dirty, so it माला_लो written back. */
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
	वापस 0;
err_out:
	अगर (err == -ENOMEM) अणु
		ntfs_warning(vi->i_sb, "Error allocating memory. Redirtying "
				"page so we try again later.");
		/*
		 * Put the page back on mapping->dirty_pages, but leave its
		 * buffers' dirty state as-is.
		 */
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		err = 0;
	पूर्ण अन्यथा अणु
		ntfs_error(vi->i_sb, "Resident attribute write failed with "
				"error %i.", err);
		SetPageError(page);
		NVolSetErrors(ni->vol);
	पूर्ण
	unlock_page(page);
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(base_ni);
	वापस err;
पूर्ण

#पूर्ण_अगर	/* NTFS_RW */

/**
 * ntfs_bmap - map logical file block to physical device block
 * @mapping:	address space mapping to which the block to be mapped beदीर्घs
 * @block:	logical block to map to its physical device block
 *
 * For regular, non-resident files (i.e. not compressed and not encrypted), map
 * the logical @block beदीर्घing to the file described by the address space
 * mapping @mapping to its physical device block.
 *
 * The size of the block is equal to the @s_blocksize field of the super block
 * of the mounted file प्रणाली which is guaranteed to be smaller than or equal
 * to the cluster size thus the block is guaranteed to fit entirely inside the
 * cluster which means we करो not need to care how many contiguous bytes are
 * available after the beginning of the block.
 *
 * Return the physical device block अगर the mapping succeeded or 0 अगर the block
 * is sparse or there was an error.
 *
 * Note: This is a problem अगर someone tries to run bmap() on $Boot प्रणाली file
 * as that really is in block zero but there is nothing we can करो.  bmap() is
 * just broken in that respect (just like it cannot distinguish sparse from
 * not available or error).
 */
अटल sector_t ntfs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	s64 ofs, size;
	loff_t i_size;
	LCN lcn;
	अचिन्हित दीर्घ blocksize, flags;
	ntfs_inode *ni = NTFS_I(mapping->host);
	ntfs_volume *vol = ni->vol;
	अचिन्हित delta;
	अचिन्हित अक्षर blocksize_bits, cluster_size_shअगरt;

	ntfs_debug("Entering for mft_no 0x%lx, logical block 0x%llx.",
			ni->mft_no, (अचिन्हित दीर्घ दीर्घ)block);
	अगर (ni->type != AT_DATA || !NInoNonResident(ni) || NInoEncrypted(ni)) अणु
		ntfs_error(vol->sb, "BMAP does not make sense for %s "
				"attributes, returning 0.",
				(ni->type != AT_DATA) ? "non-data" :
				(!NInoNonResident(ni) ? "resident" :
				"encrypted"));
		वापस 0;
	पूर्ण
	/* None of these can happen. */
	BUG_ON(NInoCompressed(ni));
	BUG_ON(NInoMstProtected(ni));
	blocksize = vol->sb->s_blocksize;
	blocksize_bits = vol->sb->s_blocksize_bits;
	ofs = (s64)block << blocksize_bits;
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	size = ni->initialized_size;
	i_size = i_size_पढ़ो(VFS_I(ni));
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	/*
	 * If the offset is outside the initialized size or the block straddles
	 * the initialized size then pretend it is a hole unless the
	 * initialized size equals the file size.
	 */
	अगर (unlikely(ofs >= size || (ofs + blocksize > size && size < i_size)))
		जाओ hole;
	cluster_size_shअगरt = vol->cluster_size_bits;
	करोwn_पढ़ो(&ni->runlist.lock);
	lcn = ntfs_attr_vcn_to_lcn_nolock(ni, ofs >> cluster_size_shअगरt, false);
	up_पढ़ो(&ni->runlist.lock);
	अगर (unlikely(lcn < LCN_HOLE)) अणु
		/*
		 * Step करोwn to an पूर्णांकeger to aव्योम gcc करोing a दीर्घ दीर्घ
		 * comparision in the चयन when we know @lcn is between
		 * LCN_HOLE and LCN_EIO (i.e. -1 to -5).
		 *
		 * Otherwise older gcc (at least on some architectures) will
		 * try to use __cmpdi2() which is of course not available in
		 * the kernel.
		 */
		चयन ((पूर्णांक)lcn) अणु
		हाल LCN_ENOENT:
			/*
			 * If the offset is out of bounds then pretend it is a
			 * hole.
			 */
			जाओ hole;
		हाल LCN_ENOMEM:
			ntfs_error(vol->sb, "Not enough memory to complete "
					"mapping for inode 0x%lx.  "
					"Returning 0.", ni->mft_no);
			अवरोध;
		शेष:
			ntfs_error(vol->sb, "Failed to complete mapping for "
					"inode 0x%lx.  Run chkdsk.  "
					"Returning 0.", ni->mft_no);
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (lcn < 0) अणु
		/* It is a hole. */
hole:
		ntfs_debug("Done (returning hole).");
		वापस 0;
	पूर्ण
	/*
	 * The block is really allocated and fullfils all our criteria.
	 * Convert the cluster to units of block size and वापस the result.
	 */
	delta = ofs & vol->cluster_size_mask;
	अगर (unlikely(माप(block) < माप(lcn))) अणु
		block = lcn = ((lcn << cluster_size_shअगरt) + delta) >>
				blocksize_bits;
		/* If the block number was truncated वापस 0. */
		अगर (unlikely(block != lcn)) अणु
			ntfs_error(vol->sb, "Physical block 0x%llx is too "
					"large to be returned, returning 0.",
					(दीर्घ दीर्घ)lcn);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा
		block = ((lcn << cluster_size_shअगरt) + delta) >>
				blocksize_bits;
	ntfs_debug("Done (returning block 0x%llx).", (अचिन्हित दीर्घ दीर्घ)lcn);
	वापस block;
पूर्ण

/**
 * ntfs_normal_aops - address space operations क्रम normal inodes and attributes
 *
 * Note these are not used क्रम compressed or mst रक्षित inodes and
 * attributes.
 */
स्थिर काष्ठा address_space_operations ntfs_normal_aops = अणु
	.पढ़ोpage	= ntfs_पढ़ोpage,
#अगर_घोषित NTFS_RW
	.ग_लिखोpage	= ntfs_ग_लिखोpage,
	.set_page_dirty	= __set_page_dirty_buffers,
#पूर्ण_अगर /* NTFS_RW */
	.bmap		= ntfs_bmap,
	.migratepage	= buffer_migrate_page,
	.is_partially_uptodate = block_is_partially_uptodate,
	.error_हटाओ_page = generic_error_हटाओ_page,
पूर्ण;

/**
 * ntfs_compressed_aops - address space operations क्रम compressed inodes
 */
स्थिर काष्ठा address_space_operations ntfs_compressed_aops = अणु
	.पढ़ोpage	= ntfs_पढ़ोpage,
#अगर_घोषित NTFS_RW
	.ग_लिखोpage	= ntfs_ग_लिखोpage,
	.set_page_dirty	= __set_page_dirty_buffers,
#पूर्ण_अगर /* NTFS_RW */
	.migratepage	= buffer_migrate_page,
	.is_partially_uptodate = block_is_partially_uptodate,
	.error_हटाओ_page = generic_error_हटाओ_page,
पूर्ण;

/**
 * ntfs_mst_aops - general address space operations क्रम mst protecteed inodes
 *		   and attributes
 */
स्थिर काष्ठा address_space_operations ntfs_mst_aops = अणु
	.पढ़ोpage	= ntfs_पढ़ोpage,	/* Fill page with data. */
#अगर_घोषित NTFS_RW
	.ग_लिखोpage	= ntfs_ग_लिखोpage,	/* Write dirty page to disk. */
	.set_page_dirty	= __set_page_dirty_nobuffers,	/* Set the page dirty
						   without touching the buffers
						   beदीर्घing to the page. */
#पूर्ण_अगर /* NTFS_RW */
	.migratepage	= buffer_migrate_page,
	.is_partially_uptodate	= block_is_partially_uptodate,
	.error_हटाओ_page = generic_error_हटाओ_page,
पूर्ण;

#अगर_घोषित NTFS_RW

/**
 * mark_ntfs_record_dirty - mark an ntfs record dirty
 * @page:	page containing the ntfs record to mark dirty
 * @ofs:	byte offset within @page at which the ntfs record begins
 *
 * Set the buffers and the page in which the ntfs record is located dirty.
 *
 * The latter also marks the vfs inode the ntfs record beदीर्घs to dirty
 * (I_सूचीTY_PAGES only).
 *
 * If the page करोes not have buffers, we create them and set them uptodate.
 * The page may not be locked which is why we need to handle the buffers under
 * the mapping->निजी_lock.  Once the buffers are marked dirty we no दीर्घer
 * need the lock since try_to_मुक्त_buffers() करोes not मुक्त dirty buffers.
 */
व्योम mark_ntfs_record_dirty(काष्ठा page *page, स्थिर अचिन्हित पूर्णांक ofs) अणु
	काष्ठा address_space *mapping = page->mapping;
	ntfs_inode *ni = NTFS_I(mapping->host);
	काष्ठा buffer_head *bh, *head, *buffers_to_मुक्त = शून्य;
	अचिन्हित पूर्णांक end, bh_size, bh_ofs;

	BUG_ON(!PageUptodate(page));
	end = ofs + ni->itype.index.block_size;
	bh_size = VFS_I(ni)->i_sb->s_blocksize;
	spin_lock(&mapping->निजी_lock);
	अगर (unlikely(!page_has_buffers(page))) अणु
		spin_unlock(&mapping->निजी_lock);
		bh = head = alloc_page_buffers(page, bh_size, true);
		spin_lock(&mapping->निजी_lock);
		अगर (likely(!page_has_buffers(page))) अणु
			काष्ठा buffer_head *tail;

			करो अणु
				set_buffer_uptodate(bh);
				tail = bh;
				bh = bh->b_this_page;
			पूर्ण जबतक (bh);
			tail->b_this_page = head;
			attach_page_निजी(page, head);
		पूर्ण अन्यथा
			buffers_to_मुक्त = bh;
	पूर्ण
	bh = head = page_buffers(page);
	BUG_ON(!bh);
	करो अणु
		bh_ofs = bh_offset(bh);
		अगर (bh_ofs + bh_size <= ofs)
			जारी;
		अगर (unlikely(bh_ofs >= end))
			अवरोध;
		set_buffer_dirty(bh);
	पूर्ण जबतक ((bh = bh->b_this_page) != head);
	spin_unlock(&mapping->निजी_lock);
	__set_page_dirty_nobuffers(page);
	अगर (unlikely(buffers_to_मुक्त)) अणु
		करो अणु
			bh = buffers_to_मुक्त->b_this_page;
			मुक्त_buffer_head(buffers_to_मुक्त);
			buffers_to_मुक्त = bh;
		पूर्ण जबतक (buffers_to_मुक्त);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* NTFS_RW */
