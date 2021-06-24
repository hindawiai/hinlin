<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * mft.c - NTFS kernel mft record operations. Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2012 Anton Altaparmakov and Tuxera Inc.
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/bपन.स>

#समावेश "attrib.h"
#समावेश "aops.h"
#समावेश "bitmap.h"
#समावेश "debug.h"
#समावेश "dir.h"
#समावेश "lcnalloc.h"
#समावेश "malloc.h"
#समावेश "mft.h"
#समावेश "ntfs.h"

#घोषणा MAX_BHS	(PAGE_SIZE / NTFS_BLOCK_SIZE)

/**
 * map_mft_record_page - map the page in which a specअगरic mft record resides
 * @ni:		ntfs inode whose mft record page to map
 *
 * This maps the page in which the mft record of the ntfs inode @ni is situated
 * and वापसs a poपूर्णांकer to the mft record within the mapped page.
 *
 * Return value needs to be checked with IS_ERR() and अगर that is true PTR_ERR()
 * contains the negative error code वापसed.
 */
अटल अंतरभूत MFT_RECORD *map_mft_record_page(ntfs_inode *ni)
अणु
	loff_t i_size;
	ntfs_volume *vol = ni->vol;
	काष्ठा inode *mft_vi = vol->mft_ino;
	काष्ठा page *page;
	अचिन्हित दीर्घ index, end_index;
	अचिन्हित ofs;

	BUG_ON(ni->page);
	/*
	 * The index पूर्णांकo the page cache and the offset within the page cache
	 * page of the wanted mft record. FIXME: We need to check क्रम
	 * overflowing the अचिन्हित दीर्घ, but I करोn't think we would ever get
	 * here अगर the volume was that big...
	 */
	index = (u64)ni->mft_no << vol->mft_record_size_bits >>
			PAGE_SHIFT;
	ofs = (ni->mft_no << vol->mft_record_size_bits) & ~PAGE_MASK;

	i_size = i_size_पढ़ो(mft_vi);
	/* The maximum valid index पूर्णांकo the page cache क्रम $MFT's data. */
	end_index = i_size >> PAGE_SHIFT;

	/* If the wanted index is out of bounds the mft record करोesn't exist. */
	अगर (unlikely(index >= end_index)) अणु
		अगर (index > end_index || (i_size & ~PAGE_MASK) < ofs +
				vol->mft_record_size) अणु
			page = ERR_PTR(-ENOENT);
			ntfs_error(vol->sb, "Attempt to read mft record 0x%lx, "
					"which is beyond the end of the mft.  "
					"This is probably a bug in the ntfs "
					"driver.", ni->mft_no);
			जाओ err_out;
		पूर्ण
	पूर्ण
	/* Read, map, and pin the page. */
	page = ntfs_map_page(mft_vi->i_mapping, index);
	अगर (!IS_ERR(page)) अणु
		/* Catch multi sector transfer fixup errors. */
		अगर (likely(ntfs_is_mft_recordp((le32*)(page_address(page) +
				ofs)))) अणु
			ni->page = page;
			ni->page_ofs = ofs;
			वापस page_address(page) + ofs;
		पूर्ण
		ntfs_error(vol->sb, "Mft record 0x%lx is corrupt.  "
				"Run chkdsk.", ni->mft_no);
		ntfs_unmap_page(page);
		page = ERR_PTR(-EIO);
		NVolSetErrors(vol);
	पूर्ण
err_out:
	ni->page = शून्य;
	ni->page_ofs = 0;
	वापस (व्योम*)page;
पूर्ण

/**
 * map_mft_record - map, pin and lock an mft record
 * @ni:		ntfs inode whose MFT record to map
 *
 * First, take the mrec_lock mutex.  We might now be sleeping, जबतक रुकोing
 * क्रम the mutex अगर it was alपढ़ोy locked by someone अन्यथा.
 *
 * The page of the record is mapped using map_mft_record_page() beक्रमe being
 * वापसed to the caller.
 *
 * This in turn uses ntfs_map_page() to get the page containing the wanted mft
 * record (it in turn calls पढ़ो_cache_page() which पढ़ोs it in from disk अगर
 * necessary, increments the use count on the page so that it cannot disappear
 * under us and वापसs a reference to the page cache page).
 *
 * If पढ़ो_cache_page() invokes ntfs_पढ़ोpage() to load the page from disk, it
 * sets PG_locked and clears PG_uptodate on the page. Once I/O has completed
 * and the post-पढ़ो mst fixups on each mft record in the page have been
 * perक्रमmed, the page माला_लो PG_uptodate set and PG_locked cleared (this is करोne
 * in our asynchronous I/O completion handler end_buffer_पढ़ो_mft_async()).
 * ntfs_map_page() रुकोs क्रम PG_locked to become clear and checks अगर
 * PG_uptodate is set and वापसs an error code अगर not. This provides
 * sufficient protection against races when पढ़ोing/using the page.
 *
 * However there is the ग_लिखो mapping to think about. Doing the above described
 * checking here will be fine, because when initiating the ग_लिखो we will set
 * PG_locked and clear PG_uptodate making sure nobody is touching the page
 * contents. Doing the locking this way means that the commit to disk code in
 * the page cache code paths is स्वतःmatically sufficiently locked with us as
 * we will not touch a page that has been locked or is not uptodate. The only
 * locking problem then is them locking the page जबतक we are accessing it.
 *
 * So that code will end up having to own the mrec_lock of all mft
 * records/inodes present in the page beक्रमe I/O can proceed. In that हाल we
 * wouldn't need to bother with PG_locked and PG_uptodate as nobody will be
 * accessing anything without owning the mrec_lock mutex.  But we करो need to
 * use them because of the पढ़ो_cache_page() invocation and the code becomes so
 * much simpler this way that it is well worth it.
 *
 * The mft record is now ours and we वापस a poपूर्णांकer to it. You need to check
 * the वापसed poपूर्णांकer with IS_ERR() and अगर that is true, PTR_ERR() will वापस
 * the error code.
 *
 * NOTE: Caller is responsible क्रम setting the mft record dirty beक्रमe calling
 * unmap_mft_record(). This is obviously only necessary अगर the caller really
 * modअगरied the mft record...
 * Q: Do we want to recycle one of the VFS inode state bits instead?
 * A: No, the inode ones mean we want to change the mft record, not we want to
 * ग_लिखो it out.
 */
MFT_RECORD *map_mft_record(ntfs_inode *ni)
अणु
	MFT_RECORD *m;

	ntfs_debug("Entering for mft_no 0x%lx.", ni->mft_no);

	/* Make sure the ntfs inode करोesn't go away. */
	atomic_inc(&ni->count);

	/* Serialize access to this mft record. */
	mutex_lock(&ni->mrec_lock);

	m = map_mft_record_page(ni);
	अगर (!IS_ERR(m))
		वापस m;

	mutex_unlock(&ni->mrec_lock);
	atomic_dec(&ni->count);
	ntfs_error(ni->vol->sb, "Failed with error code %lu.", -PTR_ERR(m));
	वापस m;
पूर्ण

/**
 * unmap_mft_record_page - unmap the page in which a specअगरic mft record resides
 * @ni:		ntfs inode whose mft record page to unmap
 *
 * This unmaps the page in which the mft record of the ntfs inode @ni is
 * situated and वापसs. This is a NOOP अगर highmem is not configured.
 *
 * The unmap happens via ntfs_unmap_page() which in turn decrements the use
 * count on the page thus releasing it from the pinned state.
 *
 * We करो not actually unmap the page from memory of course, as that will be
 * करोne by the page cache code itself when memory pressure increases or
 * whatever.
 */
अटल अंतरभूत व्योम unmap_mft_record_page(ntfs_inode *ni)
अणु
	BUG_ON(!ni->page);

	// TODO: If dirty, blah...
	ntfs_unmap_page(ni->page);
	ni->page = शून्य;
	ni->page_ofs = 0;
	वापस;
पूर्ण

/**
 * unmap_mft_record - release a mapped mft record
 * @ni:		ntfs inode whose MFT record to unmap
 *
 * We release the page mapping and the mrec_lock mutex which unmaps the mft
 * record and releases it क्रम others to get hold of. We also release the ntfs
 * inode by decrementing the ntfs inode reference count.
 *
 * NOTE: If caller has modअगरied the mft record, it is imperative to set the mft
 * record dirty BEFORE calling unmap_mft_record().
 */
व्योम unmap_mft_record(ntfs_inode *ni)
अणु
	काष्ठा page *page = ni->page;

	BUG_ON(!page);

	ntfs_debug("Entering for mft_no 0x%lx.", ni->mft_no);

	unmap_mft_record_page(ni);
	mutex_unlock(&ni->mrec_lock);
	atomic_dec(&ni->count);
	/*
	 * If pure ntfs_inode, i.e. no vfs inode attached, we leave it to
	 * ntfs_clear_extent_inode() in the extent inode हाल, and to the
	 * caller in the non-extent, yet pure ntfs inode हाल, to करो the actual
	 * tear करोwn of all काष्ठाures and मुक्तing of all allocated memory.
	 */
	वापस;
पूर्ण

/**
 * map_extent_mft_record - load an extent inode and attach it to its base
 * @base_ni:	base ntfs inode
 * @mref:	mft reference of the extent inode to load
 * @ntfs_ino:	on successful वापस, poपूर्णांकer to the ntfs_inode काष्ठाure
 *
 * Load the extent mft record @mref and attach it to its base inode @base_ni.
 * Return the mapped extent mft record अगर IS_ERR(result) is false.  Otherwise
 * PTR_ERR(result) gives the negative error code.
 *
 * On successful वापस, @ntfs_ino contains a poपूर्णांकer to the ntfs_inode
 * काष्ठाure of the mapped extent inode.
 */
MFT_RECORD *map_extent_mft_record(ntfs_inode *base_ni, MFT_REF mref,
		ntfs_inode **ntfs_ino)
अणु
	MFT_RECORD *m;
	ntfs_inode *ni = शून्य;
	ntfs_inode **extent_nis = शून्य;
	पूर्णांक i;
	अचिन्हित दीर्घ mft_no = MREF(mref);
	u16 seq_no = MSEQNO(mref);
	bool destroy_ni = false;

	ntfs_debug("Mapping extent mft record 0x%lx (base mft record 0x%lx).",
			mft_no, base_ni->mft_no);
	/* Make sure the base ntfs inode करोesn't go away. */
	atomic_inc(&base_ni->count);
	/*
	 * Check अगर this extent inode has alपढ़ोy been added to the base inode,
	 * in which हाल just वापस it. If not found, add it to the base
	 * inode beक्रमe वापसing it.
	 */
	mutex_lock(&base_ni->extent_lock);
	अगर (base_ni->nr_extents > 0) अणु
		extent_nis = base_ni->ext.extent_ntfs_inos;
		क्रम (i = 0; i < base_ni->nr_extents; i++) अणु
			अगर (mft_no != extent_nis[i]->mft_no)
				जारी;
			ni = extent_nis[i];
			/* Make sure the ntfs inode करोesn't go away. */
			atomic_inc(&ni->count);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (likely(ni != शून्य)) अणु
		mutex_unlock(&base_ni->extent_lock);
		atomic_dec(&base_ni->count);
		/* We found the record; just have to map and वापस it. */
		m = map_mft_record(ni);
		/* map_mft_record() has incremented this on success. */
		atomic_dec(&ni->count);
		अगर (!IS_ERR(m)) अणु
			/* Verअगरy the sequence number. */
			अगर (likely(le16_to_cpu(m->sequence_number) == seq_no)) अणु
				ntfs_debug("Done 1.");
				*ntfs_ino = ni;
				वापस m;
			पूर्ण
			unmap_mft_record(ni);
			ntfs_error(base_ni->vol->sb, "Found stale extent mft "
					"reference! Corrupt filesystem. "
					"Run chkdsk.");
			वापस ERR_PTR(-EIO);
		पूर्ण
map_err_out:
		ntfs_error(base_ni->vol->sb, "Failed to map extent "
				"mft record, error code %ld.", -PTR_ERR(m));
		वापस m;
	पूर्ण
	/* Record wasn't there. Get a new ntfs inode and initialize it. */
	ni = ntfs_new_extent_inode(base_ni->vol->sb, mft_no);
	अगर (unlikely(!ni)) अणु
		mutex_unlock(&base_ni->extent_lock);
		atomic_dec(&base_ni->count);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	ni->vol = base_ni->vol;
	ni->seq_no = seq_no;
	ni->nr_extents = -1;
	ni->ext.base_ntfs_ino = base_ni;
	/* Now map the record. */
	m = map_mft_record(ni);
	अगर (IS_ERR(m)) अणु
		mutex_unlock(&base_ni->extent_lock);
		atomic_dec(&base_ni->count);
		ntfs_clear_extent_inode(ni);
		जाओ map_err_out;
	पूर्ण
	/* Verअगरy the sequence number अगर it is present. */
	अगर (seq_no && (le16_to_cpu(m->sequence_number) != seq_no)) अणु
		ntfs_error(base_ni->vol->sb, "Found stale extent mft "
				"reference! Corrupt filesystem. Run chkdsk.");
		destroy_ni = true;
		m = ERR_PTR(-EIO);
		जाओ unm_err_out;
	पूर्ण
	/* Attach extent inode to base inode, पुनः_स्मृतिating memory अगर needed. */
	अगर (!(base_ni->nr_extents & 3)) अणु
		ntfs_inode **पंचांगp;
		पूर्णांक new_size = (base_ni->nr_extents + 4) * माप(ntfs_inode *);

		पंचांगp = kदो_स्मृति(new_size, GFP_NOFS);
		अगर (unlikely(!पंचांगp)) अणु
			ntfs_error(base_ni->vol->sb, "Failed to allocate "
					"internal buffer.");
			destroy_ni = true;
			m = ERR_PTR(-ENOMEM);
			जाओ unm_err_out;
		पूर्ण
		अगर (base_ni->nr_extents) अणु
			BUG_ON(!base_ni->ext.extent_ntfs_inos);
			स_नकल(पंचांगp, base_ni->ext.extent_ntfs_inos, new_size -
					4 * माप(ntfs_inode *));
			kमुक्त(base_ni->ext.extent_ntfs_inos);
		पूर्ण
		base_ni->ext.extent_ntfs_inos = पंचांगp;
	पूर्ण
	base_ni->ext.extent_ntfs_inos[base_ni->nr_extents++] = ni;
	mutex_unlock(&base_ni->extent_lock);
	atomic_dec(&base_ni->count);
	ntfs_debug("Done 2.");
	*ntfs_ino = ni;
	वापस m;
unm_err_out:
	unmap_mft_record(ni);
	mutex_unlock(&base_ni->extent_lock);
	atomic_dec(&base_ni->count);
	/*
	 * If the extent inode was not attached to the base inode we need to
	 * release it or we will leak memory.
	 */
	अगर (destroy_ni)
		ntfs_clear_extent_inode(ni);
	वापस m;
पूर्ण

#अगर_घोषित NTFS_RW

/**
 * __mark_mft_record_dirty - set the mft record and the page containing it dirty
 * @ni:		ntfs inode describing the mapped mft record
 *
 * Internal function.  Users should call mark_mft_record_dirty() instead.
 *
 * Set the mapped (extent) mft record of the (base or extent) ntfs inode @ni,
 * as well as the page containing the mft record, dirty.  Also, mark the base
 * vfs inode dirty.  This ensures that any changes to the mft record are
 * written out to disk.
 *
 * NOTE:  We only set I_सूचीTY_DATASYNC (and not I_सूचीTY_PAGES)
 * on the base vfs inode, because even though file data may have been modअगरied,
 * it is dirty in the inode meta data rather than the data page cache of the
 * inode, and thus there are no data pages that need writing out.  Thereक्रमe, a
 * full mark_inode_dirty() is overसमाप्त.  A mark_inode_dirty_sync(), on the
 * other hand, is not sufficient, because ->ग_लिखो_inode needs to be called even
 * in हाल of fdatasync. This needs to happen or the file data would not
 * necessarily hit the device synchronously, even though the vfs inode has the
 * O_SYNC flag set.  Also, I_सूचीTY_DATASYNC simply "feels" better than just
 * I_सूचीTY_SYNC, since the file data has not actually hit the block device yet,
 * which is not what I_सूचीTY_SYNC on its own would suggest.
 */
व्योम __mark_mft_record_dirty(ntfs_inode *ni)
अणु
	ntfs_inode *base_ni;

	ntfs_debug("Entering for inode 0x%lx.", ni->mft_no);
	BUG_ON(NInoAttr(ni));
	mark_ntfs_record_dirty(ni->page, ni->page_ofs);
	/* Determine the base vfs inode and mark it dirty, too. */
	mutex_lock(&ni->extent_lock);
	अगर (likely(ni->nr_extents >= 0))
		base_ni = ni;
	अन्यथा
		base_ni = ni->ext.base_ntfs_ino;
	mutex_unlock(&ni->extent_lock);
	__mark_inode_dirty(VFS_I(base_ni), I_सूचीTY_DATASYNC);
पूर्ण

अटल स्थिर अक्षर *ntfs_please_email = "Please email "
		"linux-ntfs-dev@lists.sourceforge.net and say that you saw "
		"this message.  Thank you.";

/**
 * ntfs_sync_mft_mirror_umount - synchronise an mft record to the mft mirror
 * @vol:	ntfs volume on which the mft record to synchronize resides
 * @mft_no:	mft record number of mft record to synchronize
 * @m:		mapped, mst रक्षित (extent) mft record to synchronize
 *
 * Write the mapped, mst रक्षित (extent) mft record @m with mft record
 * number @mft_no to the mft mirror ($MFTMirr) of the ntfs volume @vol,
 * bypassing the page cache and the $MFTMirr inode itself.
 *
 * This function is only क्रम use at umount समय when the mft mirror inode has
 * alपढ़ोy been disposed off.  We BUG() अगर we are called जबतक the mft mirror
 * inode is still attached to the volume.
 *
 * On success वापस 0.  On error वापस -त्रुटि_सं.
 *
 * NOTE:  This function is not implemented yet as I am not convinced it can
 * actually be triggered considering the sequence of commits we करो in super.c::
 * ntfs_put_super().  But just in हाल we provide this place holder as the
 * alternative would be either to BUG() or to get a शून्य poपूर्णांकer dereference
 * and Oops.
 */
अटल पूर्णांक ntfs_sync_mft_mirror_umount(ntfs_volume *vol,
		स्थिर अचिन्हित दीर्घ mft_no, MFT_RECORD *m)
अणु
	BUG_ON(vol->mfपंचांगirr_ino);
	ntfs_error(vol->sb, "Umount time mft mirror syncing is not "
			"implemented yet.  %s", ntfs_please_email);
	वापस -EOPNOTSUPP;
पूर्ण

/**
 * ntfs_sync_mft_mirror - synchronize an mft record to the mft mirror
 * @vol:	ntfs volume on which the mft record to synchronize resides
 * @mft_no:	mft record number of mft record to synchronize
 * @m:		mapped, mst रक्षित (extent) mft record to synchronize
 * @sync:	अगर true, रुको क्रम i/o completion
 *
 * Write the mapped, mst रक्षित (extent) mft record @m with mft record
 * number @mft_no to the mft mirror ($MFTMirr) of the ntfs volume @vol.
 *
 * On success वापस 0.  On error वापस -त्रुटि_सं and set the volume errors flag
 * in the ntfs volume @vol.
 *
 * NOTE:  We always perक्रमm synchronous i/o and ignore the @sync parameter.
 *
 * TODO:  If @sync is false, want to करो truly asynchronous i/o, i.e. just
 * schedule i/o via ->ग_लिखोpage or करो it via kntfsd or whatever.
 */
पूर्णांक ntfs_sync_mft_mirror(ntfs_volume *vol, स्थिर अचिन्हित दीर्घ mft_no,
		MFT_RECORD *m, पूर्णांक sync)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक blocksize = vol->sb->s_blocksize;
	पूर्णांक max_bhs = vol->mft_record_size / blocksize;
	काष्ठा buffer_head *bhs[MAX_BHS];
	काष्ठा buffer_head *bh, *head;
	u8 *kmirr;
	runlist_element *rl;
	अचिन्हित पूर्णांक block_start, block_end, m_start, m_end, page_ofs;
	पूर्णांक i_bhs, nr_bhs, err = 0;
	अचिन्हित अक्षर blocksize_bits = vol->sb->s_blocksize_bits;

	ntfs_debug("Entering for inode 0x%lx.", mft_no);
	BUG_ON(!max_bhs);
	अगर (WARN_ON(max_bhs > MAX_BHS))
		वापस -EINVAL;
	अगर (unlikely(!vol->mfपंचांगirr_ino)) अणु
		/* This could happen during umount... */
		err = ntfs_sync_mft_mirror_umount(vol, mft_no, m);
		अगर (likely(!err))
			वापस err;
		जाओ err_out;
	पूर्ण
	/* Get the page containing the mirror copy of the mft record @m. */
	page = ntfs_map_page(vol->mfपंचांगirr_ino->i_mapping, mft_no >>
			(PAGE_SHIFT - vol->mft_record_size_bits));
	अगर (IS_ERR(page)) अणु
		ntfs_error(vol->sb, "Failed to map mft mirror page.");
		err = PTR_ERR(page);
		जाओ err_out;
	पूर्ण
	lock_page(page);
	BUG_ON(!PageUptodate(page));
	ClearPageUptodate(page);
	/* Offset of the mft mirror record inside the page. */
	page_ofs = (mft_no << vol->mft_record_size_bits) & ~PAGE_MASK;
	/* The address in the page of the mirror copy of the mft record @m. */
	kmirr = page_address(page) + page_ofs;
	/* Copy the mst रक्षित mft record to the mirror. */
	स_नकल(kmirr, m, vol->mft_record_size);
	/* Create uptodate buffers अगर not present. */
	अगर (unlikely(!page_has_buffers(page))) अणु
		काष्ठा buffer_head *tail;

		bh = head = alloc_page_buffers(page, blocksize, true);
		करो अणु
			set_buffer_uptodate(bh);
			tail = bh;
			bh = bh->b_this_page;
		पूर्ण जबतक (bh);
		tail->b_this_page = head;
		attach_page_निजी(page, head);
	पूर्ण
	bh = head = page_buffers(page);
	BUG_ON(!bh);
	rl = शून्य;
	nr_bhs = 0;
	block_start = 0;
	m_start = kmirr - (u8*)page_address(page);
	m_end = m_start + vol->mft_record_size;
	करो अणु
		block_end = block_start + blocksize;
		/* If the buffer is outside the mft record, skip it. */
		अगर (block_end <= m_start)
			जारी;
		अगर (unlikely(block_start >= m_end))
			अवरोध;
		/* Need to map the buffer अगर it is not mapped alपढ़ोy. */
		अगर (unlikely(!buffer_mapped(bh))) अणु
			VCN vcn;
			LCN lcn;
			अचिन्हित पूर्णांक vcn_ofs;

			bh->b_bdev = vol->sb->s_bdev;
			/* Obtain the vcn and offset of the current block. */
			vcn = ((VCN)mft_no << vol->mft_record_size_bits) +
					(block_start - m_start);
			vcn_ofs = vcn & vol->cluster_size_mask;
			vcn >>= vol->cluster_size_bits;
			अगर (!rl) अणु
				करोwn_पढ़ो(&NTFS_I(vol->mfपंचांगirr_ino)->
						runlist.lock);
				rl = NTFS_I(vol->mfपंचांगirr_ino)->runlist.rl;
				/*
				 * $MFTMirr always has the whole of its runlist
				 * in memory.
				 */
				BUG_ON(!rl);
			पूर्ण
			/* Seek to element containing target vcn. */
			जबतक (rl->length && rl[1].vcn <= vcn)
				rl++;
			lcn = ntfs_rl_vcn_to_lcn(rl, vcn);
			/* For $MFTMirr, only lcn >= 0 is a successful remap. */
			अगर (likely(lcn >= 0)) अणु
				/* Setup buffer head to correct block. */
				bh->b_blocknr = ((lcn <<
						vol->cluster_size_bits) +
						vcn_ofs) >> blocksize_bits;
				set_buffer_mapped(bh);
			पूर्ण अन्यथा अणु
				bh->b_blocknr = -1;
				ntfs_error(vol->sb, "Cannot write mft mirror "
						"record 0x%lx because its "
						"location on disk could not "
						"be determined (error code "
						"%lli).", mft_no,
						(दीर्घ दीर्घ)lcn);
				err = -EIO;
			पूर्ण
		पूर्ण
		BUG_ON(!buffer_uptodate(bh));
		BUG_ON(!nr_bhs && (m_start != block_start));
		BUG_ON(nr_bhs >= max_bhs);
		bhs[nr_bhs++] = bh;
		BUG_ON((nr_bhs >= max_bhs) && (m_end != block_end));
	पूर्ण जबतक (block_start = block_end, (bh = bh->b_this_page) != head);
	अगर (unlikely(rl))
		up_पढ़ो(&NTFS_I(vol->mfपंचांगirr_ino)->runlist.lock);
	अगर (likely(!err)) अणु
		/* Lock buffers and start synchronous ग_लिखो i/o on them. */
		क्रम (i_bhs = 0; i_bhs < nr_bhs; i_bhs++) अणु
			काष्ठा buffer_head *tbh = bhs[i_bhs];

			अगर (!trylock_buffer(tbh))
				BUG();
			BUG_ON(!buffer_uptodate(tbh));
			clear_buffer_dirty(tbh);
			get_bh(tbh);
			tbh->b_end_io = end_buffer_ग_लिखो_sync;
			submit_bh(REQ_OP_WRITE, 0, tbh);
		पूर्ण
		/* Wait on i/o completion of buffers. */
		क्रम (i_bhs = 0; i_bhs < nr_bhs; i_bhs++) अणु
			काष्ठा buffer_head *tbh = bhs[i_bhs];

			रुको_on_buffer(tbh);
			अगर (unlikely(!buffer_uptodate(tbh))) अणु
				err = -EIO;
				/*
				 * Set the buffer uptodate so the page and
				 * buffer states करो not become out of sync.
				 */
				set_buffer_uptodate(tbh);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा /* अगर (unlikely(err)) */ अणु
		/* Clean the buffers. */
		क्रम (i_bhs = 0; i_bhs < nr_bhs; i_bhs++)
			clear_buffer_dirty(bhs[i_bhs]);
	पूर्ण
	/* Current state: all buffers are clean, unlocked, and uptodate. */
	/* Remove the mst protection fixups again. */
	post_ग_लिखो_mst_fixup((NTFS_RECORD*)kmirr);
	flush_dcache_page(page);
	SetPageUptodate(page);
	unlock_page(page);
	ntfs_unmap_page(page);
	अगर (likely(!err)) अणु
		ntfs_debug("Done.");
	पूर्ण अन्यथा अणु
		ntfs_error(vol->sb, "I/O error while writing mft mirror "
				"record 0x%lx!", mft_no);
err_out:
		ntfs_error(vol->sb, "Failed to synchronize $MFTMirr (error "
				"code %i).  Volume will be left marked dirty "
				"on umount.  Run ntfsfix on the partition "
				"after umounting to correct this.", -err);
		NVolSetErrors(vol);
	पूर्ण
	वापस err;
पूर्ण

/**
 * ग_लिखो_mft_record_nolock - ग_लिखो out a mapped (extent) mft record
 * @ni:		ntfs inode describing the mapped (extent) mft record
 * @m:		mapped (extent) mft record to ग_लिखो
 * @sync:	अगर true, रुको क्रम i/o completion
 *
 * Write the mapped (extent) mft record @m described by the (regular or extent)
 * ntfs inode @ni to backing store.  If the mft record @m has a counterpart in
 * the mft mirror, that is also updated.
 *
 * We only ग_लिखो the mft record अगर the ntfs inode @ni is dirty and the first
 * buffer beदीर्घing to its mft record is dirty, too.  We ignore the dirty state
 * of subsequent buffers because we could have raced with
 * fs/ntfs/aops.c::mark_ntfs_record_dirty().
 *
 * On success, clean the mft record and वापस 0.  On error, leave the mft
 * record dirty and वापस -त्रुटि_सं.
 *
 * NOTE:  We always perक्रमm synchronous i/o and ignore the @sync parameter.
 * However, अगर the mft record has a counterpart in the mft mirror and @sync is
 * true, we ग_लिखो the mft record, रुको क्रम i/o completion, and only then ग_लिखो
 * the mft mirror copy.  This ensures that अगर the प्रणाली crashes either the mft
 * or the mft mirror will contain a self-consistent mft record @m.  If @sync is
 * false on the other hand, we start i/o on both and then रुको क्रम completion
 * on them.  This provides a speedup but no दीर्घer guarantees that you will end
 * up with a self-consistent mft record in the हाल of a crash but अगर you asked
 * क्रम asynchronous writing you probably करो not care about that anyway.
 *
 * TODO:  If @sync is false, want to करो truly asynchronous i/o, i.e. just
 * schedule i/o via ->ग_लिखोpage or करो it via kntfsd or whatever.
 */
पूर्णांक ग_लिखो_mft_record_nolock(ntfs_inode *ni, MFT_RECORD *m, पूर्णांक sync)
अणु
	ntfs_volume *vol = ni->vol;
	काष्ठा page *page = ni->page;
	अचिन्हित पूर्णांक blocksize = vol->sb->s_blocksize;
	अचिन्हित अक्षर blocksize_bits = vol->sb->s_blocksize_bits;
	पूर्णांक max_bhs = vol->mft_record_size / blocksize;
	काष्ठा buffer_head *bhs[MAX_BHS];
	काष्ठा buffer_head *bh, *head;
	runlist_element *rl;
	अचिन्हित पूर्णांक block_start, block_end, m_start, m_end;
	पूर्णांक i_bhs, nr_bhs, err = 0;

	ntfs_debug("Entering for inode 0x%lx.", ni->mft_no);
	BUG_ON(NInoAttr(ni));
	BUG_ON(!max_bhs);
	BUG_ON(!PageLocked(page));
	अगर (WARN_ON(max_bhs > MAX_BHS)) अणु
		err = -EINVAL;
		जाओ err_out;
	पूर्ण
	/*
	 * If the ntfs_inode is clean no need to करो anything.  If it is dirty,
	 * mark it as clean now so that it can be redirtied later on अगर needed.
	 * There is no danger of races since the caller is holding the locks
	 * क्रम the mft record @m and the page it is in.
	 */
	अगर (!NInoTestClearDirty(ni))
		जाओ करोne;
	bh = head = page_buffers(page);
	BUG_ON(!bh);
	rl = शून्य;
	nr_bhs = 0;
	block_start = 0;
	m_start = ni->page_ofs;
	m_end = m_start + vol->mft_record_size;
	करो अणु
		block_end = block_start + blocksize;
		/* If the buffer is outside the mft record, skip it. */
		अगर (block_end <= m_start)
			जारी;
		अगर (unlikely(block_start >= m_end))
			अवरोध;
		/*
		 * If this block is not the first one in the record, we ignore
		 * the buffer's dirty state because we could have raced with a
		 * parallel mark_ntfs_record_dirty().
		 */
		अगर (block_start == m_start) अणु
			/* This block is the first one in the record. */
			अगर (!buffer_dirty(bh)) अणु
				BUG_ON(nr_bhs);
				/* Clean records are not written out. */
				अवरोध;
			पूर्ण
		पूर्ण
		/* Need to map the buffer अगर it is not mapped alपढ़ोy. */
		अगर (unlikely(!buffer_mapped(bh))) अणु
			VCN vcn;
			LCN lcn;
			अचिन्हित पूर्णांक vcn_ofs;

			bh->b_bdev = vol->sb->s_bdev;
			/* Obtain the vcn and offset of the current block. */
			vcn = ((VCN)ni->mft_no << vol->mft_record_size_bits) +
					(block_start - m_start);
			vcn_ofs = vcn & vol->cluster_size_mask;
			vcn >>= vol->cluster_size_bits;
			अगर (!rl) अणु
				करोwn_पढ़ो(&NTFS_I(vol->mft_ino)->runlist.lock);
				rl = NTFS_I(vol->mft_ino)->runlist.rl;
				BUG_ON(!rl);
			पूर्ण
			/* Seek to element containing target vcn. */
			जबतक (rl->length && rl[1].vcn <= vcn)
				rl++;
			lcn = ntfs_rl_vcn_to_lcn(rl, vcn);
			/* For $MFT, only lcn >= 0 is a successful remap. */
			अगर (likely(lcn >= 0)) अणु
				/* Setup buffer head to correct block. */
				bh->b_blocknr = ((lcn <<
						vol->cluster_size_bits) +
						vcn_ofs) >> blocksize_bits;
				set_buffer_mapped(bh);
			पूर्ण अन्यथा अणु
				bh->b_blocknr = -1;
				ntfs_error(vol->sb, "Cannot write mft record "
						"0x%lx because its location "
						"on disk could not be "
						"determined (error code %lli).",
						ni->mft_no, (दीर्घ दीर्घ)lcn);
				err = -EIO;
			पूर्ण
		पूर्ण
		BUG_ON(!buffer_uptodate(bh));
		BUG_ON(!nr_bhs && (m_start != block_start));
		BUG_ON(nr_bhs >= max_bhs);
		bhs[nr_bhs++] = bh;
		BUG_ON((nr_bhs >= max_bhs) && (m_end != block_end));
	पूर्ण जबतक (block_start = block_end, (bh = bh->b_this_page) != head);
	अगर (unlikely(rl))
		up_पढ़ो(&NTFS_I(vol->mft_ino)->runlist.lock);
	अगर (!nr_bhs)
		जाओ करोne;
	अगर (unlikely(err))
		जाओ cleanup_out;
	/* Apply the mst protection fixups. */
	err = pre_ग_लिखो_mst_fixup((NTFS_RECORD*)m, vol->mft_record_size);
	अगर (err) अणु
		ntfs_error(vol->sb, "Failed to apply mst fixups!");
		जाओ cleanup_out;
	पूर्ण
	flush_dcache_mft_record_page(ni);
	/* Lock buffers and start synchronous ग_लिखो i/o on them. */
	क्रम (i_bhs = 0; i_bhs < nr_bhs; i_bhs++) अणु
		काष्ठा buffer_head *tbh = bhs[i_bhs];

		अगर (!trylock_buffer(tbh))
			BUG();
		BUG_ON(!buffer_uptodate(tbh));
		clear_buffer_dirty(tbh);
		get_bh(tbh);
		tbh->b_end_io = end_buffer_ग_लिखो_sync;
		submit_bh(REQ_OP_WRITE, 0, tbh);
	पूर्ण
	/* Synchronize the mft mirror now अगर not @sync. */
	अगर (!sync && ni->mft_no < vol->mfपंचांगirr_size)
		ntfs_sync_mft_mirror(vol, ni->mft_no, m, sync);
	/* Wait on i/o completion of buffers. */
	क्रम (i_bhs = 0; i_bhs < nr_bhs; i_bhs++) अणु
		काष्ठा buffer_head *tbh = bhs[i_bhs];

		रुको_on_buffer(tbh);
		अगर (unlikely(!buffer_uptodate(tbh))) अणु
			err = -EIO;
			/*
			 * Set the buffer uptodate so the page and buffer
			 * states करो not become out of sync.
			 */
			अगर (PageUptodate(page))
				set_buffer_uptodate(tbh);
		पूर्ण
	पूर्ण
	/* If @sync, now synchronize the mft mirror. */
	अगर (sync && ni->mft_no < vol->mfपंचांगirr_size)
		ntfs_sync_mft_mirror(vol, ni->mft_no, m, sync);
	/* Remove the mst protection fixups again. */
	post_ग_लिखो_mst_fixup((NTFS_RECORD*)m);
	flush_dcache_mft_record_page(ni);
	अगर (unlikely(err)) अणु
		/* I/O error during writing.  This is really bad! */
		ntfs_error(vol->sb, "I/O error while writing mft record "
				"0x%lx!  Marking base inode as bad.  You "
				"should unmount the volume and run chkdsk.",
				ni->mft_no);
		जाओ err_out;
	पूर्ण
करोne:
	ntfs_debug("Done.");
	वापस 0;
cleanup_out:
	/* Clean the buffers. */
	क्रम (i_bhs = 0; i_bhs < nr_bhs; i_bhs++)
		clear_buffer_dirty(bhs[i_bhs]);
err_out:
	/*
	 * Current state: all buffers are clean, unlocked, and uptodate.
	 * The caller should mark the base inode as bad so that no more i/o
	 * happens.  ->clear_inode() will still be invoked so all extent inodes
	 * and other allocated memory will be मुक्तd.
	 */
	अगर (err == -ENOMEM) अणु
		ntfs_error(vol->sb, "Not enough memory to write mft record.  "
				"Redirtying so the write is retried later.");
		mark_mft_record_dirty(ni);
		err = 0;
	पूर्ण अन्यथा
		NVolSetErrors(vol);
	वापस err;
पूर्ण

/**
 * ntfs_may_ग_लिखो_mft_record - check अगर an mft record may be written out
 * @vol:	[IN]  ntfs volume on which the mft record to check resides
 * @mft_no:	[IN]  mft record number of the mft record to check
 * @m:		[IN]  mapped mft record to check
 * @locked_ni:	[OUT] caller has to unlock this ntfs inode अगर one is वापसed
 *
 * Check अगर the mapped (base or extent) mft record @m with mft record number
 * @mft_no beदीर्घing to the ntfs volume @vol may be written out.  If necessary
 * and possible the ntfs inode of the mft record is locked and the base vfs
 * inode is pinned.  The locked ntfs inode is then वापसed in @locked_ni.  The
 * caller is responsible क्रम unlocking the ntfs inode and unpinning the base
 * vfs inode.
 *
 * Return 'true' if the mft record may be written out and 'false' अगर not.
 *
 * The caller has locked the page and cleared the uptodate flag on it which
 * means that we can safely ग_लिखो out any dirty mft records that करो not have
 * their inodes in icache as determined by ilookup5() as anyone
 * खोलोing/creating such an inode would block when attempting to map the mft
 * record in पढ़ो_cache_page() until we are finished with the ग_लिखो out.
 *
 * Here is a description of the tests we perक्रमm:
 *
 * If the inode is found in icache we know the mft record must be a base mft
 * record.  If it is dirty, we करो not ग_लिखो it and वापस 'false' as the vfs
 * inode ग_लिखो paths will result in the access बार being updated which would
 * cause the base mft record to be redirtied and written out again.  (We know
 * the access समय update will modअगरy the base mft record because Winकरोws
 * chkdsk complains अगर the standard inक्रमmation attribute is not in the base
 * mft record.)
 *
 * If the inode is in icache and not dirty, we attempt to lock the mft record
 * and अगर we find the lock was alपढ़ोy taken, it is not safe to ग_लिखो the mft
 * record and we वापस 'false'.
 *
 * If we manage to obtain the lock we have exclusive access to the mft record,
 * which also allows us safe ग_लिखोout of the mft record.  We then set
 * @locked_ni to the locked ntfs inode and वापस 'true'.
 *
 * Note we cannot just lock the mft record and sleep जबतक रुकोing क्रम the lock
 * because this would deadlock due to lock reversal (normally the mft record is
 * locked beक्रमe the page is locked but we alपढ़ोy have the page locked here
 * when we try to lock the mft record).
 *
 * If the inode is not in icache we need to perक्रमm further checks.
 *
 * If the mft record is not a खाता record or it is a base mft record, we can
 * safely ग_लिखो it and वापस 'true'.
 *
 * We now know the mft record is an extent mft record.  We check अगर the inode
 * corresponding to its base mft record is in icache and obtain a reference to
 * it अगर it is.  If it is not, we can safely ग_लिखो it and वापस 'true'.
 *
 * We now have the base inode क्रम the extent mft record.  We check अगर it has an
 * ntfs inode क्रम the extent mft record attached and अगर not it is safe to ग_लिखो
 * the extent mft record and we वापस 'true'.
 *
 * The ntfs inode क्रम the extent mft record is attached to the base inode so we
 * attempt to lock the extent mft record and अगर we find the lock was alपढ़ोy
 * taken, it is not safe to ग_लिखो the extent mft record and we वापस 'false'.
 *
 * If we manage to obtain the lock we have exclusive access to the extent mft
 * record, which also allows us safe ग_लिखोout of the extent mft record.  We
 * set the ntfs inode of the extent mft record clean and then set @locked_ni to
 * the now locked ntfs inode and वापस 'true'.
 *
 * Note, the reason क्रम actually writing dirty mft records here and not just
 * relying on the vfs inode dirty code paths is that we can have mft records
 * modअगरied without them ever having actual inodes in memory.  Also we can have
 * dirty mft records with clean ntfs inodes in memory.  None of the described
 * हालs would result in the dirty mft records being written out अगर we only
 * relied on the vfs inode dirty code paths.  And these हालs can really occur
 * during allocation of new mft records and in particular when the
 * initialized_size of the $MFT/$DATA attribute is extended and the new space
 * is initialized using ntfs_mft_record_क्रमmat().  The clean inode can then
 * appear अगर the mft record is reused क्रम a new inode beक्रमe it got written
 * out.
 */
bool ntfs_may_ग_लिखो_mft_record(ntfs_volume *vol, स्थिर अचिन्हित दीर्घ mft_no,
		स्थिर MFT_RECORD *m, ntfs_inode **locked_ni)
अणु
	काष्ठा super_block *sb = vol->sb;
	काष्ठा inode *mft_vi = vol->mft_ino;
	काष्ठा inode *vi;
	ntfs_inode *ni, *eni, **extent_nis;
	पूर्णांक i;
	ntfs_attr na;

	ntfs_debug("Entering for inode 0x%lx.", mft_no);
	/*
	 * Normally we करो not वापस a locked inode so set @locked_ni to शून्य.
	 */
	BUG_ON(!locked_ni);
	*locked_ni = शून्य;
	/*
	 * Check अगर the inode corresponding to this mft record is in the VFS
	 * inode cache and obtain a reference to it अगर it is.
	 */
	ntfs_debug("Looking for inode 0x%lx in icache.", mft_no);
	na.mft_no = mft_no;
	na.name = शून्य;
	na.name_len = 0;
	na.type = AT_UNUSED;
	/*
	 * Optimize inode 0, i.e. $MFT itself, since we have it in memory and
	 * we get here क्रम it rather often.
	 */
	अगर (!mft_no) अणु
		/* Balance the below iput(). */
		vi = igrab(mft_vi);
		BUG_ON(vi != mft_vi);
	पूर्ण अन्यथा अणु
		/*
		 * Have to use ilookup5_noरुको() since ilookup5() रुकोs क्रम the
		 * inode lock which causes ntfs to deadlock when a concurrent
		 * inode ग_लिखो via the inode dirty code paths and the page
		 * dirty code path of the inode dirty code path when writing
		 * $MFT occurs.
		 */
		vi = ilookup5_noरुको(sb, mft_no, ntfs_test_inode, &na);
	पूर्ण
	अगर (vi) अणु
		ntfs_debug("Base inode 0x%lx is in icache.", mft_no);
		/* The inode is in icache. */
		ni = NTFS_I(vi);
		/* Take a reference to the ntfs inode. */
		atomic_inc(&ni->count);
		/* If the inode is dirty, करो not ग_लिखो this record. */
		अगर (NInoDirty(ni)) अणु
			ntfs_debug("Inode 0x%lx is dirty, do not write it.",
					mft_no);
			atomic_dec(&ni->count);
			iput(vi);
			वापस false;
		पूर्ण
		ntfs_debug("Inode 0x%lx is not dirty.", mft_no);
		/* The inode is not dirty, try to take the mft record lock. */
		अगर (unlikely(!mutex_trylock(&ni->mrec_lock))) अणु
			ntfs_debug("Mft record 0x%lx is already locked, do "
					"not write it.", mft_no);
			atomic_dec(&ni->count);
			iput(vi);
			वापस false;
		पूर्ण
		ntfs_debug("Managed to lock mft record 0x%lx, write it.",
				mft_no);
		/*
		 * The ग_लिखो has to occur जबतक we hold the mft record lock so
		 * वापस the locked ntfs inode.
		 */
		*locked_ni = ni;
		वापस true;
	पूर्ण
	ntfs_debug("Inode 0x%lx is not in icache.", mft_no);
	/* The inode is not in icache. */
	/* Write the record अगर it is not a mft record (type "FILE"). */
	अगर (!ntfs_is_mft_record(m->magic)) अणु
		ntfs_debug("Mft record 0x%lx is not a FILE record, write it.",
				mft_no);
		वापस true;
	पूर्ण
	/* Write the mft record अगर it is a base inode. */
	अगर (!m->base_mft_record) अणु
		ntfs_debug("Mft record 0x%lx is a base record, write it.",
				mft_no);
		वापस true;
	पूर्ण
	/*
	 * This is an extent mft record.  Check अगर the inode corresponding to
	 * its base mft record is in icache and obtain a reference to it अगर it
	 * is.
	 */
	na.mft_no = MREF_LE(m->base_mft_record);
	ntfs_debug("Mft record 0x%lx is an extent record.  Looking for base "
			"inode 0x%lx in icache.", mft_no, na.mft_no);
	अगर (!na.mft_no) अणु
		/* Balance the below iput(). */
		vi = igrab(mft_vi);
		BUG_ON(vi != mft_vi);
	पूर्ण अन्यथा
		vi = ilookup5_noरुको(sb, na.mft_no, ntfs_test_inode,
				&na);
	अगर (!vi) अणु
		/*
		 * The base inode is not in icache, ग_लिखो this extent mft
		 * record.
		 */
		ntfs_debug("Base inode 0x%lx is not in icache, write the "
				"extent record.", na.mft_no);
		वापस true;
	पूर्ण
	ntfs_debug("Base inode 0x%lx is in icache.", na.mft_no);
	/*
	 * The base inode is in icache.  Check अगर it has the extent inode
	 * corresponding to this extent mft record attached.
	 */
	ni = NTFS_I(vi);
	mutex_lock(&ni->extent_lock);
	अगर (ni->nr_extents <= 0) अणु
		/*
		 * The base inode has no attached extent inodes, ग_लिखो this
		 * extent mft record.
		 */
		mutex_unlock(&ni->extent_lock);
		iput(vi);
		ntfs_debug("Base inode 0x%lx has no attached extent inodes, "
				"write the extent record.", na.mft_no);
		वापस true;
	पूर्ण
	/* Iterate over the attached extent inodes. */
	extent_nis = ni->ext.extent_ntfs_inos;
	क्रम (eni = शून्य, i = 0; i < ni->nr_extents; ++i) अणु
		अगर (mft_no == extent_nis[i]->mft_no) अणु
			/*
			 * Found the extent inode corresponding to this extent
			 * mft record.
			 */
			eni = extent_nis[i];
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * If the extent inode was not attached to the base inode, ग_लिखो this
	 * extent mft record.
	 */
	अगर (!eni) अणु
		mutex_unlock(&ni->extent_lock);
		iput(vi);
		ntfs_debug("Extent inode 0x%lx is not attached to its base "
				"inode 0x%lx, write the extent record.",
				mft_no, na.mft_no);
		वापस true;
	पूर्ण
	ntfs_debug("Extent inode 0x%lx is attached to its base inode 0x%lx.",
			mft_no, na.mft_no);
	/* Take a reference to the extent ntfs inode. */
	atomic_inc(&eni->count);
	mutex_unlock(&ni->extent_lock);
	/*
	 * Found the extent inode coresponding to this extent mft record.
	 * Try to take the mft record lock.
	 */
	अगर (unlikely(!mutex_trylock(&eni->mrec_lock))) अणु
		atomic_dec(&eni->count);
		iput(vi);
		ntfs_debug("Extent mft record 0x%lx is already locked, do "
				"not write it.", mft_no);
		वापस false;
	पूर्ण
	ntfs_debug("Managed to lock extent mft record 0x%lx, write it.",
			mft_no);
	अगर (NInoTestClearDirty(eni))
		ntfs_debug("Extent inode 0x%lx is dirty, marking it clean.",
				mft_no);
	/*
	 * The ग_लिखो has to occur जबतक we hold the mft record lock so वापस
	 * the locked extent ntfs inode.
	 */
	*locked_ni = eni;
	वापस true;
पूर्ण

अटल स्थिर अक्षर *es = "  Leaving inconsistent metadata.  Unmount and run "
		"chkdsk.";

/**
 * ntfs_mft_biपंचांगap_find_and_alloc_मुक्त_rec_nolock - see name
 * @vol:	volume on which to search क्रम a मुक्त mft record
 * @base_ni:	खोलो base inode अगर allocating an extent mft record or शून्य
 *
 * Search क्रम a मुक्त mft record in the mft biपंचांगap attribute on the ntfs volume
 * @vol.
 *
 * If @base_ni is शून्य start the search at the शेष allocator position.
 *
 * If @base_ni is not शून्य start the search at the mft record after the base
 * mft record @base_ni.
 *
 * Return the मुक्त mft record on success and -त्रुटि_सं on error.  An error code of
 * -ENOSPC means that there are no मुक्त mft records in the currently
 * initialized mft biपंचांगap.
 *
 * Locking: Caller must hold vol->mftbmp_lock क्रम writing.
 */
अटल पूर्णांक ntfs_mft_biपंचांगap_find_and_alloc_मुक्त_rec_nolock(ntfs_volume *vol,
		ntfs_inode *base_ni)
अणु
	s64 pass_end, ll, data_pos, pass_start, ofs, bit;
	अचिन्हित दीर्घ flags;
	काष्ठा address_space *mftbmp_mapping;
	u8 *buf, *byte;
	काष्ठा page *page;
	अचिन्हित पूर्णांक page_ofs, size;
	u8 pass, b;

	ntfs_debug("Searching for free mft record in the currently "
			"initialized mft bitmap.");
	mftbmp_mapping = vol->mftbmp_ino->i_mapping;
	/*
	 * Set the end of the pass making sure we करो not overflow the mft
	 * biपंचांगap.
	 */
	पढ़ो_lock_irqsave(&NTFS_I(vol->mft_ino)->size_lock, flags);
	pass_end = NTFS_I(vol->mft_ino)->allocated_size >>
			vol->mft_record_size_bits;
	पढ़ो_unlock_irqrestore(&NTFS_I(vol->mft_ino)->size_lock, flags);
	पढ़ो_lock_irqsave(&NTFS_I(vol->mftbmp_ino)->size_lock, flags);
	ll = NTFS_I(vol->mftbmp_ino)->initialized_size << 3;
	पढ़ो_unlock_irqrestore(&NTFS_I(vol->mftbmp_ino)->size_lock, flags);
	अगर (pass_end > ll)
		pass_end = ll;
	pass = 1;
	अगर (!base_ni)
		data_pos = vol->mft_data_pos;
	अन्यथा
		data_pos = base_ni->mft_no + 1;
	अगर (data_pos < 24)
		data_pos = 24;
	अगर (data_pos >= pass_end) अणु
		data_pos = 24;
		pass = 2;
		/* This happens on a freshly क्रमmatted volume. */
		अगर (data_pos >= pass_end)
			वापस -ENOSPC;
	पूर्ण
	pass_start = data_pos;
	ntfs_debug("Starting bitmap search: pass %u, pass_start 0x%llx, "
			"pass_end 0x%llx, data_pos 0x%llx.", pass,
			(दीर्घ दीर्घ)pass_start, (दीर्घ दीर्घ)pass_end,
			(दीर्घ दीर्घ)data_pos);
	/* Loop until a मुक्त mft record is found. */
	क्रम (; pass <= 2;) अणु
		/* Cap size to pass_end. */
		ofs = data_pos >> 3;
		page_ofs = ofs & ~PAGE_MASK;
		size = PAGE_SIZE - page_ofs;
		ll = ((pass_end + 7) >> 3) - ofs;
		अगर (size > ll)
			size = ll;
		size <<= 3;
		/*
		 * If we are still within the active pass, search the next page
		 * क्रम a zero bit.
		 */
		अगर (size) अणु
			page = ntfs_map_page(mftbmp_mapping,
					ofs >> PAGE_SHIFT);
			अगर (IS_ERR(page)) अणु
				ntfs_error(vol->sb, "Failed to read mft "
						"bitmap, aborting.");
				वापस PTR_ERR(page);
			पूर्ण
			buf = (u8*)page_address(page) + page_ofs;
			bit = data_pos & 7;
			data_pos &= ~7ull;
			ntfs_debug("Before inner for loop: size 0x%x, "
					"data_pos 0x%llx, bit 0x%llx", size,
					(दीर्घ दीर्घ)data_pos, (दीर्घ दीर्घ)bit);
			क्रम (; bit < size && data_pos + bit < pass_end;
					bit &= ~7ull, bit += 8) अणु
				byte = buf + (bit >> 3);
				अगर (*byte == 0xff)
					जारी;
				b = ffz((अचिन्हित दीर्घ)*byte);
				अगर (b < 8 && b >= (bit & 7)) अणु
					ll = data_pos + (bit & ~7ull) + b;
					अगर (unlikely(ll > (1ll << 32))) अणु
						ntfs_unmap_page(page);
						वापस -ENOSPC;
					पूर्ण
					*byte |= 1 << b;
					flush_dcache_page(page);
					set_page_dirty(page);
					ntfs_unmap_page(page);
					ntfs_debug("Done.  (Found and "
							"allocated mft record "
							"0x%llx.)",
							(दीर्घ दीर्घ)ll);
					वापस ll;
				पूर्ण
			पूर्ण
			ntfs_debug("After inner for loop: size 0x%x, "
					"data_pos 0x%llx, bit 0x%llx", size,
					(दीर्घ दीर्घ)data_pos, (दीर्घ दीर्घ)bit);
			data_pos += size;
			ntfs_unmap_page(page);
			/*
			 * If the end of the pass has not been reached yet,
			 * जारी searching the mft biपंचांगap क्रम a zero bit.
			 */
			अगर (data_pos < pass_end)
				जारी;
		पूर्ण
		/* Do the next pass. */
		अगर (++pass == 2) अणु
			/*
			 * Starting the second pass, in which we scan the first
			 * part of the zone which we omitted earlier.
			 */
			pass_end = pass_start;
			data_pos = pass_start = 24;
			ntfs_debug("pass %i, pass_start 0x%llx, pass_end "
					"0x%llx.", pass, (दीर्घ दीर्घ)pass_start,
					(दीर्घ दीर्घ)pass_end);
			अगर (data_pos >= pass_end)
				अवरोध;
		पूर्ण
	पूर्ण
	/* No मुक्त mft records in currently initialized mft biपंचांगap. */
	ntfs_debug("Done.  (No free mft records left in currently initialized "
			"mft bitmap.)");
	वापस -ENOSPC;
पूर्ण

/**
 * ntfs_mft_biपंचांगap_extend_allocation_nolock - extend mft biपंचांगap by a cluster
 * @vol:	volume on which to extend the mft biपंचांगap attribute
 *
 * Extend the mft biपंचांगap attribute on the ntfs volume @vol by one cluster.
 *
 * Note: Only changes allocated_size, i.e. करोes not touch initialized_size or
 * data_size.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 *
 * Locking: - Caller must hold vol->mftbmp_lock क्रम writing.
 *	    - This function takes NTFS_I(vol->mftbmp_ino)->runlist.lock क्रम
 *	      writing and releases it beक्रमe वापसing.
 *	    - This function takes vol->lcnbmp_lock क्रम writing and releases it
 *	      beक्रमe वापसing.
 */
अटल पूर्णांक ntfs_mft_biपंचांगap_extend_allocation_nolock(ntfs_volume *vol)
अणु
	LCN lcn;
	s64 ll;
	अचिन्हित दीर्घ flags;
	काष्ठा page *page;
	ntfs_inode *mft_ni, *mftbmp_ni;
	runlist_element *rl, *rl2 = शून्य;
	ntfs_attr_search_ctx *ctx = शून्य;
	MFT_RECORD *mrec;
	ATTR_RECORD *a = शून्य;
	पूर्णांक ret, mp_size;
	u32 old_alen = 0;
	u8 *b, tb;
	काष्ठा अणु
		u8 added_cluster:1;
		u8 added_run:1;
		u8 mp_rebuilt:1;
	पूर्ण status = अणु 0, 0, 0 पूर्ण;

	ntfs_debug("Extending mft bitmap allocation.");
	mft_ni = NTFS_I(vol->mft_ino);
	mftbmp_ni = NTFS_I(vol->mftbmp_ino);
	/*
	 * Determine the last lcn of the mft biपंचांगap.  The allocated size of the
	 * mft biपंचांगap cannot be zero so we are ok to करो this.
	 */
	करोwn_ग_लिखो(&mftbmp_ni->runlist.lock);
	पढ़ो_lock_irqsave(&mftbmp_ni->size_lock, flags);
	ll = mftbmp_ni->allocated_size;
	पढ़ो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
	rl = ntfs_attr_find_vcn_nolock(mftbmp_ni,
			(ll - 1) >> vol->cluster_size_bits, शून्य);
	अगर (IS_ERR(rl) || unlikely(!rl->length || rl->lcn < 0)) अणु
		up_ग_लिखो(&mftbmp_ni->runlist.lock);
		ntfs_error(vol->sb, "Failed to determine last allocated "
				"cluster of mft bitmap attribute.");
		अगर (!IS_ERR(rl))
			ret = -EIO;
		अन्यथा
			ret = PTR_ERR(rl);
		वापस ret;
	पूर्ण
	lcn = rl->lcn + rl->length;
	ntfs_debug("Last lcn of mft bitmap attribute is 0x%llx.",
			(दीर्घ दीर्घ)lcn);
	/*
	 * Attempt to get the cluster following the last allocated cluster by
	 * hand as it may be in the MFT zone so the allocator would not give it
	 * to us.
	 */
	ll = lcn >> 3;
	page = ntfs_map_page(vol->lcnbmp_ino->i_mapping,
			ll >> PAGE_SHIFT);
	अगर (IS_ERR(page)) अणु
		up_ग_लिखो(&mftbmp_ni->runlist.lock);
		ntfs_error(vol->sb, "Failed to read from lcn bitmap.");
		वापस PTR_ERR(page);
	पूर्ण
	b = (u8*)page_address(page) + (ll & ~PAGE_MASK);
	tb = 1 << (lcn & 7ull);
	करोwn_ग_लिखो(&vol->lcnbmp_lock);
	अगर (*b != 0xff && !(*b & tb)) अणु
		/* Next cluster is मुक्त, allocate it. */
		*b |= tb;
		flush_dcache_page(page);
		set_page_dirty(page);
		up_ग_लिखो(&vol->lcnbmp_lock);
		ntfs_unmap_page(page);
		/* Update the mft biपंचांगap runlist. */
		rl->length++;
		rl[1].vcn++;
		status.added_cluster = 1;
		ntfs_debug("Appending one cluster to mft bitmap.");
	पूर्ण अन्यथा अणु
		up_ग_लिखो(&vol->lcnbmp_lock);
		ntfs_unmap_page(page);
		/* Allocate a cluster from the DATA_ZONE. */
		rl2 = ntfs_cluster_alloc(vol, rl[1].vcn, 1, lcn, DATA_ZONE,
				true);
		अगर (IS_ERR(rl2)) अणु
			up_ग_लिखो(&mftbmp_ni->runlist.lock);
			ntfs_error(vol->sb, "Failed to allocate a cluster for "
					"the mft bitmap.");
			वापस PTR_ERR(rl2);
		पूर्ण
		rl = ntfs_runlists_merge(mftbmp_ni->runlist.rl, rl2);
		अगर (IS_ERR(rl)) अणु
			up_ग_लिखो(&mftbmp_ni->runlist.lock);
			ntfs_error(vol->sb, "Failed to merge runlists for mft "
					"bitmap.");
			अगर (ntfs_cluster_मुक्त_from_rl(vol, rl2)) अणु
				ntfs_error(vol->sb, "Failed to deallocate "
						"allocated cluster.%s", es);
				NVolSetErrors(vol);
			पूर्ण
			ntfs_मुक्त(rl2);
			वापस PTR_ERR(rl);
		पूर्ण
		mftbmp_ni->runlist.rl = rl;
		status.added_run = 1;
		ntfs_debug("Adding one run to mft bitmap.");
		/* Find the last run in the new runlist. */
		क्रम (; rl[1].length; rl++)
			;
	पूर्ण
	/*
	 * Update the attribute record as well.  Note: @rl is the last
	 * (non-terminator) runlist element of mft biपंचांगap.
	 */
	mrec = map_mft_record(mft_ni);
	अगर (IS_ERR(mrec)) अणु
		ntfs_error(vol->sb, "Failed to map mft record.");
		ret = PTR_ERR(mrec);
		जाओ unकरो_alloc;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(mft_ni, mrec);
	अगर (unlikely(!ctx)) अणु
		ntfs_error(vol->sb, "Failed to get search context.");
		ret = -ENOMEM;
		जाओ unकरो_alloc;
	पूर्ण
	ret = ntfs_attr_lookup(mftbmp_ni->type, mftbmp_ni->name,
			mftbmp_ni->name_len, CASE_SENSITIVE, rl[1].vcn, शून्य,
			0, ctx);
	अगर (unlikely(ret)) अणु
		ntfs_error(vol->sb, "Failed to find last attribute extent of "
				"mft bitmap attribute.");
		अगर (ret == -ENOENT)
			ret = -EIO;
		जाओ unकरो_alloc;
	पूर्ण
	a = ctx->attr;
	ll = sle64_to_cpu(a->data.non_resident.lowest_vcn);
	/* Search back क्रम the previous last allocated cluster of mft biपंचांगap. */
	क्रम (rl2 = rl; rl2 > mftbmp_ni->runlist.rl; rl2--) अणु
		अगर (ll >= rl2->vcn)
			अवरोध;
	पूर्ण
	BUG_ON(ll < rl2->vcn);
	BUG_ON(ll >= rl2->vcn + rl2->length);
	/* Get the size क्रम the new mapping pairs array क्रम this extent. */
	mp_size = ntfs_get_size_क्रम_mapping_pairs(vol, rl2, ll, -1);
	अगर (unlikely(mp_size <= 0)) अणु
		ntfs_error(vol->sb, "Get size for mapping pairs failed for "
				"mft bitmap attribute extent.");
		ret = mp_size;
		अगर (!ret)
			ret = -EIO;
		जाओ unकरो_alloc;
	पूर्ण
	/* Expand the attribute record अगर necessary. */
	old_alen = le32_to_cpu(a->length);
	ret = ntfs_attr_record_resize(ctx->mrec, a, mp_size +
			le16_to_cpu(a->data.non_resident.mapping_pairs_offset));
	अगर (unlikely(ret)) अणु
		अगर (ret != -ENOSPC) अणु
			ntfs_error(vol->sb, "Failed to resize attribute "
					"record for mft bitmap attribute.");
			जाओ unकरो_alloc;
		पूर्ण
		// TODO: Deal with this by moving this extent to a new mft
		// record or by starting a new extent in a new mft record or by
		// moving other attributes out of this mft record.
		// Note: It will need to be a special mft record and अगर none of
		// those are available it माला_लो rather complicated...
		ntfs_error(vol->sb, "Not enough space in this mft record to "
				"accommodate extended mft bitmap attribute "
				"extent.  Cannot handle this yet.");
		ret = -EOPNOTSUPP;
		जाओ unकरो_alloc;
	पूर्ण
	status.mp_rebuilt = 1;
	/* Generate the mapping pairs array directly पूर्णांकo the attr record. */
	ret = ntfs_mapping_pairs_build(vol, (u8*)a +
			le16_to_cpu(a->data.non_resident.mapping_pairs_offset),
			mp_size, rl2, ll, -1, शून्य);
	अगर (unlikely(ret)) अणु
		ntfs_error(vol->sb, "Failed to build mapping pairs array for "
				"mft bitmap attribute.");
		जाओ unकरो_alloc;
	पूर्ण
	/* Update the highest_vcn. */
	a->data.non_resident.highest_vcn = cpu_to_sle64(rl[1].vcn - 1);
	/*
	 * We now have extended the mft biपंचांगap allocated_size by one cluster.
	 * Reflect this in the ntfs_inode काष्ठाure and the attribute record.
	 */
	अगर (a->data.non_resident.lowest_vcn) अणु
		/*
		 * We are not in the first attribute extent, चयन to it, but
		 * first ensure the changes will make it to disk later.
		 */
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		mark_mft_record_dirty(ctx->ntfs_ino);
		ntfs_attr_reinit_search_ctx(ctx);
		ret = ntfs_attr_lookup(mftbmp_ni->type, mftbmp_ni->name,
				mftbmp_ni->name_len, CASE_SENSITIVE, 0, शून्य,
				0, ctx);
		अगर (unlikely(ret)) अणु
			ntfs_error(vol->sb, "Failed to find first attribute "
					"extent of mft bitmap attribute.");
			जाओ restore_unकरो_alloc;
		पूर्ण
		a = ctx->attr;
	पूर्ण
	ग_लिखो_lock_irqsave(&mftbmp_ni->size_lock, flags);
	mftbmp_ni->allocated_size += vol->cluster_size;
	a->data.non_resident.allocated_size =
			cpu_to_sle64(mftbmp_ni->allocated_size);
	ग_लिखो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
	/* Ensure the changes make it to disk. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(mft_ni);
	up_ग_लिखो(&mftbmp_ni->runlist.lock);
	ntfs_debug("Done.");
	वापस 0;
restore_unकरो_alloc:
	ntfs_attr_reinit_search_ctx(ctx);
	अगर (ntfs_attr_lookup(mftbmp_ni->type, mftbmp_ni->name,
			mftbmp_ni->name_len, CASE_SENSITIVE, rl[1].vcn, शून्य,
			0, ctx)) अणु
		ntfs_error(vol->sb, "Failed to find last attribute extent of "
				"mft bitmap attribute.%s", es);
		ग_लिखो_lock_irqsave(&mftbmp_ni->size_lock, flags);
		mftbmp_ni->allocated_size += vol->cluster_size;
		ग_लिखो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(mft_ni);
		up_ग_लिखो(&mftbmp_ni->runlist.lock);
		/*
		 * The only thing that is now wrong is ->allocated_size of the
		 * base attribute extent which chkdsk should be able to fix.
		 */
		NVolSetErrors(vol);
		वापस ret;
	पूर्ण
	a = ctx->attr;
	a->data.non_resident.highest_vcn = cpu_to_sle64(rl[1].vcn - 2);
unकरो_alloc:
	अगर (status.added_cluster) अणु
		/* Truncate the last run in the runlist by one cluster. */
		rl->length--;
		rl[1].vcn--;
	पूर्ण अन्यथा अगर (status.added_run) अणु
		lcn = rl->lcn;
		/* Remove the last run from the runlist. */
		rl->lcn = rl[1].lcn;
		rl->length = 0;
	पूर्ण
	/* Deallocate the cluster. */
	करोwn_ग_लिखो(&vol->lcnbmp_lock);
	अगर (ntfs_biपंचांगap_clear_bit(vol->lcnbmp_ino, lcn)) अणु
		ntfs_error(vol->sb, "Failed to free allocated cluster.%s", es);
		NVolSetErrors(vol);
	पूर्ण
	up_ग_लिखो(&vol->lcnbmp_lock);
	अगर (status.mp_rebuilt) अणु
		अगर (ntfs_mapping_pairs_build(vol, (u8*)a + le16_to_cpu(
				a->data.non_resident.mapping_pairs_offset),
				old_alen - le16_to_cpu(
				a->data.non_resident.mapping_pairs_offset),
				rl2, ll, -1, शून्य)) अणु
			ntfs_error(vol->sb, "Failed to restore mapping pairs "
					"array.%s", es);
			NVolSetErrors(vol);
		पूर्ण
		अगर (ntfs_attr_record_resize(ctx->mrec, a, old_alen)) अणु
			ntfs_error(vol->sb, "Failed to restore attribute "
					"record.%s", es);
			NVolSetErrors(vol);
		पूर्ण
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		mark_mft_record_dirty(ctx->ntfs_ino);
	पूर्ण
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (!IS_ERR(mrec))
		unmap_mft_record(mft_ni);
	up_ग_लिखो(&mftbmp_ni->runlist.lock);
	वापस ret;
पूर्ण

/**
 * ntfs_mft_biपंचांगap_extend_initialized_nolock - extend mftbmp initialized data
 * @vol:	volume on which to extend the mft biपंचांगap attribute
 *
 * Extend the initialized portion of the mft biपंचांगap attribute on the ntfs
 * volume @vol by 8 bytes.
 *
 * Note:  Only changes initialized_size and data_size, i.e. requires that
 * allocated_size is big enough to fit the new initialized_size.
 *
 * Return 0 on success and -error on error.
 *
 * Locking: Caller must hold vol->mftbmp_lock क्रम writing.
 */
अटल पूर्णांक ntfs_mft_biपंचांगap_extend_initialized_nolock(ntfs_volume *vol)
अणु
	s64 old_data_size, old_initialized_size;
	अचिन्हित दीर्घ flags;
	काष्ठा inode *mftbmp_vi;
	ntfs_inode *mft_ni, *mftbmp_ni;
	ntfs_attr_search_ctx *ctx;
	MFT_RECORD *mrec;
	ATTR_RECORD *a;
	पूर्णांक ret;

	ntfs_debug("Extending mft bitmap initiailized (and data) size.");
	mft_ni = NTFS_I(vol->mft_ino);
	mftbmp_vi = vol->mftbmp_ino;
	mftbmp_ni = NTFS_I(mftbmp_vi);
	/* Get the attribute record. */
	mrec = map_mft_record(mft_ni);
	अगर (IS_ERR(mrec)) अणु
		ntfs_error(vol->sb, "Failed to map mft record.");
		वापस PTR_ERR(mrec);
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(mft_ni, mrec);
	अगर (unlikely(!ctx)) अणु
		ntfs_error(vol->sb, "Failed to get search context.");
		ret = -ENOMEM;
		जाओ unm_err_out;
	पूर्ण
	ret = ntfs_attr_lookup(mftbmp_ni->type, mftbmp_ni->name,
			mftbmp_ni->name_len, CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(ret)) अणु
		ntfs_error(vol->sb, "Failed to find first attribute extent of "
				"mft bitmap attribute.");
		अगर (ret == -ENOENT)
			ret = -EIO;
		जाओ put_err_out;
	पूर्ण
	a = ctx->attr;
	ग_लिखो_lock_irqsave(&mftbmp_ni->size_lock, flags);
	old_data_size = i_size_पढ़ो(mftbmp_vi);
	old_initialized_size = mftbmp_ni->initialized_size;
	/*
	 * We can simply update the initialized_size beक्रमe filling the space
	 * with zeroes because the caller is holding the mft biपंचांगap lock क्रम
	 * writing which ensures that no one अन्यथा is trying to access the data.
	 */
	mftbmp_ni->initialized_size += 8;
	a->data.non_resident.initialized_size =
			cpu_to_sle64(mftbmp_ni->initialized_size);
	अगर (mftbmp_ni->initialized_size > old_data_size) अणु
		i_size_ग_लिखो(mftbmp_vi, mftbmp_ni->initialized_size);
		a->data.non_resident.data_size =
				cpu_to_sle64(mftbmp_ni->initialized_size);
	पूर्ण
	ग_लिखो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
	/* Ensure the changes make it to disk. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(mft_ni);
	/* Initialize the mft biपंचांगap attribute value with zeroes. */
	ret = ntfs_attr_set(mftbmp_ni, old_initialized_size, 8, 0);
	अगर (likely(!ret)) अणु
		ntfs_debug("Done.  (Wrote eight initialized bytes to mft "
				"bitmap.");
		वापस 0;
	पूर्ण
	ntfs_error(vol->sb, "Failed to write to mft bitmap.");
	/* Try to recover from the error. */
	mrec = map_mft_record(mft_ni);
	अगर (IS_ERR(mrec)) अणु
		ntfs_error(vol->sb, "Failed to map mft record.%s", es);
		NVolSetErrors(vol);
		वापस ret;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(mft_ni, mrec);
	अगर (unlikely(!ctx)) अणु
		ntfs_error(vol->sb, "Failed to get search context.%s", es);
		NVolSetErrors(vol);
		जाओ unm_err_out;
	पूर्ण
	अगर (ntfs_attr_lookup(mftbmp_ni->type, mftbmp_ni->name,
			mftbmp_ni->name_len, CASE_SENSITIVE, 0, शून्य, 0, ctx)) अणु
		ntfs_error(vol->sb, "Failed to find first attribute extent of "
				"mft bitmap attribute.%s", es);
		NVolSetErrors(vol);
put_err_out:
		ntfs_attr_put_search_ctx(ctx);
unm_err_out:
		unmap_mft_record(mft_ni);
		जाओ err_out;
	पूर्ण
	a = ctx->attr;
	ग_लिखो_lock_irqsave(&mftbmp_ni->size_lock, flags);
	mftbmp_ni->initialized_size = old_initialized_size;
	a->data.non_resident.initialized_size =
			cpu_to_sle64(old_initialized_size);
	अगर (i_size_पढ़ो(mftbmp_vi) != old_data_size) अणु
		i_size_ग_लिखो(mftbmp_vi, old_data_size);
		a->data.non_resident.data_size = cpu_to_sle64(old_data_size);
	पूर्ण
	ग_लिखो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(mft_ni);
#अगर_घोषित DEBUG
	पढ़ो_lock_irqsave(&mftbmp_ni->size_lock, flags);
	ntfs_debug("Restored status of mftbmp: allocated_size 0x%llx, "
			"data_size 0x%llx, initialized_size 0x%llx.",
			(दीर्घ दीर्घ)mftbmp_ni->allocated_size,
			(दीर्घ दीर्घ)i_size_पढ़ो(mftbmp_vi),
			(दीर्घ दीर्घ)mftbmp_ni->initialized_size);
	पढ़ो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
#पूर्ण_अगर /* DEBUG */
err_out:
	वापस ret;
पूर्ण

/**
 * ntfs_mft_data_extend_allocation_nolock - extend mft data attribute
 * @vol:	volume on which to extend the mft data attribute
 *
 * Extend the mft data attribute on the ntfs volume @vol by 16 mft records
 * worth of clusters or अगर not enough space क्रम this by one mft record worth
 * of clusters.
 *
 * Note:  Only changes allocated_size, i.e. करोes not touch initialized_size or
 * data_size.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 *
 * Locking: - Caller must hold vol->mftbmp_lock क्रम writing.
 *	    - This function takes NTFS_I(vol->mft_ino)->runlist.lock क्रम
 *	      writing and releases it beक्रमe वापसing.
 *	    - This function calls functions which take vol->lcnbmp_lock क्रम
 *	      writing and release it beक्रमe वापसing.
 */
अटल पूर्णांक ntfs_mft_data_extend_allocation_nolock(ntfs_volume *vol)
अणु
	LCN lcn;
	VCN old_last_vcn;
	s64 min_nr, nr, ll;
	अचिन्हित दीर्घ flags;
	ntfs_inode *mft_ni;
	runlist_element *rl, *rl2;
	ntfs_attr_search_ctx *ctx = शून्य;
	MFT_RECORD *mrec;
	ATTR_RECORD *a = शून्य;
	पूर्णांक ret, mp_size;
	u32 old_alen = 0;
	bool mp_rebuilt = false;

	ntfs_debug("Extending mft data allocation.");
	mft_ni = NTFS_I(vol->mft_ino);
	/*
	 * Determine the preferred allocation location, i.e. the last lcn of
	 * the mft data attribute.  The allocated size of the mft data
	 * attribute cannot be zero so we are ok to करो this.
	 */
	करोwn_ग_लिखो(&mft_ni->runlist.lock);
	पढ़ो_lock_irqsave(&mft_ni->size_lock, flags);
	ll = mft_ni->allocated_size;
	पढ़ो_unlock_irqrestore(&mft_ni->size_lock, flags);
	rl = ntfs_attr_find_vcn_nolock(mft_ni,
			(ll - 1) >> vol->cluster_size_bits, शून्य);
	अगर (IS_ERR(rl) || unlikely(!rl->length || rl->lcn < 0)) अणु
		up_ग_लिखो(&mft_ni->runlist.lock);
		ntfs_error(vol->sb, "Failed to determine last allocated "
				"cluster of mft data attribute.");
		अगर (!IS_ERR(rl))
			ret = -EIO;
		अन्यथा
			ret = PTR_ERR(rl);
		वापस ret;
	पूर्ण
	lcn = rl->lcn + rl->length;
	ntfs_debug("Last lcn of mft data attribute is 0x%llx.", (दीर्घ दीर्घ)lcn);
	/* Minimum allocation is one mft record worth of clusters. */
	min_nr = vol->mft_record_size >> vol->cluster_size_bits;
	अगर (!min_nr)
		min_nr = 1;
	/* Want to allocate 16 mft records worth of clusters. */
	nr = vol->mft_record_size << 4 >> vol->cluster_size_bits;
	अगर (!nr)
		nr = min_nr;
	/* Ensure we करो not go above 2^32-1 mft records. */
	पढ़ो_lock_irqsave(&mft_ni->size_lock, flags);
	ll = mft_ni->allocated_size;
	पढ़ो_unlock_irqrestore(&mft_ni->size_lock, flags);
	अगर (unlikely((ll + (nr << vol->cluster_size_bits)) >>
			vol->mft_record_size_bits >= (1ll << 32))) अणु
		nr = min_nr;
		अगर (unlikely((ll + (nr << vol->cluster_size_bits)) >>
				vol->mft_record_size_bits >= (1ll << 32))) अणु
			ntfs_warning(vol->sb, "Cannot allocate mft record "
					"because the maximum number of inodes "
					"(2^32) has alपढ़ोy been reached.");
			up_ग_लिखो(&mft_ni->runlist.lock);
			वापस -ENOSPC;
		पूर्ण
	पूर्ण
	ntfs_debug("Trying mft data allocation with %s cluster count %lli.",
			nr > min_nr ? "default" : "minimal", (दीर्घ दीर्घ)nr);
	old_last_vcn = rl[1].vcn;
	करो अणु
		rl2 = ntfs_cluster_alloc(vol, old_last_vcn, nr, lcn, MFT_ZONE,
				true);
		अगर (!IS_ERR(rl2))
			अवरोध;
		अगर (PTR_ERR(rl2) != -ENOSPC || nr == min_nr) अणु
			ntfs_error(vol->sb, "Failed to allocate the minimal "
					"number of clusters (%lli) for the "
					"mft data attribute.", (दीर्घ दीर्घ)nr);
			up_ग_लिखो(&mft_ni->runlist.lock);
			वापस PTR_ERR(rl2);
		पूर्ण
		/*
		 * There is not enough space to करो the allocation, but there
		 * might be enough space to करो a minimal allocation so try that
		 * beक्रमe failing.
		 */
		nr = min_nr;
		ntfs_debug("Retrying mft data allocation with minimal cluster "
				"count %lli.", (दीर्घ दीर्घ)nr);
	पूर्ण जबतक (1);
	rl = ntfs_runlists_merge(mft_ni->runlist.rl, rl2);
	अगर (IS_ERR(rl)) अणु
		up_ग_लिखो(&mft_ni->runlist.lock);
		ntfs_error(vol->sb, "Failed to merge runlists for mft data "
				"attribute.");
		अगर (ntfs_cluster_मुक्त_from_rl(vol, rl2)) अणु
			ntfs_error(vol->sb, "Failed to deallocate clusters "
					"from the mft data attribute.%s", es);
			NVolSetErrors(vol);
		पूर्ण
		ntfs_मुक्त(rl2);
		वापस PTR_ERR(rl);
	पूर्ण
	mft_ni->runlist.rl = rl;
	ntfs_debug("Allocated %lli clusters.", (दीर्घ दीर्घ)nr);
	/* Find the last run in the new runlist. */
	क्रम (; rl[1].length; rl++)
		;
	/* Update the attribute record as well. */
	mrec = map_mft_record(mft_ni);
	अगर (IS_ERR(mrec)) अणु
		ntfs_error(vol->sb, "Failed to map mft record.");
		ret = PTR_ERR(mrec);
		जाओ unकरो_alloc;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(mft_ni, mrec);
	अगर (unlikely(!ctx)) अणु
		ntfs_error(vol->sb, "Failed to get search context.");
		ret = -ENOMEM;
		जाओ unकरो_alloc;
	पूर्ण
	ret = ntfs_attr_lookup(mft_ni->type, mft_ni->name, mft_ni->name_len,
			CASE_SENSITIVE, rl[1].vcn, शून्य, 0, ctx);
	अगर (unlikely(ret)) अणु
		ntfs_error(vol->sb, "Failed to find last attribute extent of "
				"mft data attribute.");
		अगर (ret == -ENOENT)
			ret = -EIO;
		जाओ unकरो_alloc;
	पूर्ण
	a = ctx->attr;
	ll = sle64_to_cpu(a->data.non_resident.lowest_vcn);
	/* Search back क्रम the previous last allocated cluster of mft biपंचांगap. */
	क्रम (rl2 = rl; rl2 > mft_ni->runlist.rl; rl2--) अणु
		अगर (ll >= rl2->vcn)
			अवरोध;
	पूर्ण
	BUG_ON(ll < rl2->vcn);
	BUG_ON(ll >= rl2->vcn + rl2->length);
	/* Get the size क्रम the new mapping pairs array क्रम this extent. */
	mp_size = ntfs_get_size_क्रम_mapping_pairs(vol, rl2, ll, -1);
	अगर (unlikely(mp_size <= 0)) अणु
		ntfs_error(vol->sb, "Get size for mapping pairs failed for "
				"mft data attribute extent.");
		ret = mp_size;
		अगर (!ret)
			ret = -EIO;
		जाओ unकरो_alloc;
	पूर्ण
	/* Expand the attribute record अगर necessary. */
	old_alen = le32_to_cpu(a->length);
	ret = ntfs_attr_record_resize(ctx->mrec, a, mp_size +
			le16_to_cpu(a->data.non_resident.mapping_pairs_offset));
	अगर (unlikely(ret)) अणु
		अगर (ret != -ENOSPC) अणु
			ntfs_error(vol->sb, "Failed to resize attribute "
					"record for mft data attribute.");
			जाओ unकरो_alloc;
		पूर्ण
		// TODO: Deal with this by moving this extent to a new mft
		// record or by starting a new extent in a new mft record or by
		// moving other attributes out of this mft record.
		// Note: Use the special reserved mft records and ensure that
		// this extent is not required to find the mft record in
		// question.  If no मुक्त special records left we would need to
		// move an existing record away, insert ours in its place, and
		// then place the moved record पूर्णांकo the newly allocated space
		// and we would then need to update all references to this mft
		// record appropriately.  This is rather complicated...
		ntfs_error(vol->sb, "Not enough space in this mft record to "
				"accommodate extended mft data attribute "
				"extent.  Cannot handle this yet.");
		ret = -EOPNOTSUPP;
		जाओ unकरो_alloc;
	पूर्ण
	mp_rebuilt = true;
	/* Generate the mapping pairs array directly पूर्णांकo the attr record. */
	ret = ntfs_mapping_pairs_build(vol, (u8*)a +
			le16_to_cpu(a->data.non_resident.mapping_pairs_offset),
			mp_size, rl2, ll, -1, शून्य);
	अगर (unlikely(ret)) अणु
		ntfs_error(vol->sb, "Failed to build mapping pairs array of "
				"mft data attribute.");
		जाओ unकरो_alloc;
	पूर्ण
	/* Update the highest_vcn. */
	a->data.non_resident.highest_vcn = cpu_to_sle64(rl[1].vcn - 1);
	/*
	 * We now have extended the mft data allocated_size by nr clusters.
	 * Reflect this in the ntfs_inode काष्ठाure and the attribute record.
	 * @rl is the last (non-terminator) runlist element of mft data
	 * attribute.
	 */
	अगर (a->data.non_resident.lowest_vcn) अणु
		/*
		 * We are not in the first attribute extent, चयन to it, but
		 * first ensure the changes will make it to disk later.
		 */
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		mark_mft_record_dirty(ctx->ntfs_ino);
		ntfs_attr_reinit_search_ctx(ctx);
		ret = ntfs_attr_lookup(mft_ni->type, mft_ni->name,
				mft_ni->name_len, CASE_SENSITIVE, 0, शून्य, 0,
				ctx);
		अगर (unlikely(ret)) अणु
			ntfs_error(vol->sb, "Failed to find first attribute "
					"extent of mft data attribute.");
			जाओ restore_unकरो_alloc;
		पूर्ण
		a = ctx->attr;
	पूर्ण
	ग_लिखो_lock_irqsave(&mft_ni->size_lock, flags);
	mft_ni->allocated_size += nr << vol->cluster_size_bits;
	a->data.non_resident.allocated_size =
			cpu_to_sle64(mft_ni->allocated_size);
	ग_लिखो_unlock_irqrestore(&mft_ni->size_lock, flags);
	/* Ensure the changes make it to disk. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(mft_ni);
	up_ग_लिखो(&mft_ni->runlist.lock);
	ntfs_debug("Done.");
	वापस 0;
restore_unकरो_alloc:
	ntfs_attr_reinit_search_ctx(ctx);
	अगर (ntfs_attr_lookup(mft_ni->type, mft_ni->name, mft_ni->name_len,
			CASE_SENSITIVE, rl[1].vcn, शून्य, 0, ctx)) अणु
		ntfs_error(vol->sb, "Failed to find last attribute extent of "
				"mft data attribute.%s", es);
		ग_लिखो_lock_irqsave(&mft_ni->size_lock, flags);
		mft_ni->allocated_size += nr << vol->cluster_size_bits;
		ग_लिखो_unlock_irqrestore(&mft_ni->size_lock, flags);
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(mft_ni);
		up_ग_लिखो(&mft_ni->runlist.lock);
		/*
		 * The only thing that is now wrong is ->allocated_size of the
		 * base attribute extent which chkdsk should be able to fix.
		 */
		NVolSetErrors(vol);
		वापस ret;
	पूर्ण
	ctx->attr->data.non_resident.highest_vcn =
			cpu_to_sle64(old_last_vcn - 1);
unकरो_alloc:
	अगर (ntfs_cluster_मुक्त(mft_ni, old_last_vcn, -1, ctx) < 0) अणु
		ntfs_error(vol->sb, "Failed to free clusters from mft data "
				"attribute.%s", es);
		NVolSetErrors(vol);
	पूर्ण
	a = ctx->attr;
	अगर (ntfs_rl_truncate_nolock(vol, &mft_ni->runlist, old_last_vcn)) अणु
		ntfs_error(vol->sb, "Failed to truncate mft data attribute "
				"runlist.%s", es);
		NVolSetErrors(vol);
	पूर्ण
	अगर (mp_rebuilt && !IS_ERR(ctx->mrec)) अणु
		अगर (ntfs_mapping_pairs_build(vol, (u8*)a + le16_to_cpu(
				a->data.non_resident.mapping_pairs_offset),
				old_alen - le16_to_cpu(
				a->data.non_resident.mapping_pairs_offset),
				rl2, ll, -1, शून्य)) अणु
			ntfs_error(vol->sb, "Failed to restore mapping pairs "
					"array.%s", es);
			NVolSetErrors(vol);
		पूर्ण
		अगर (ntfs_attr_record_resize(ctx->mrec, a, old_alen)) अणु
			ntfs_error(vol->sb, "Failed to restore attribute "
					"record.%s", es);
			NVolSetErrors(vol);
		पूर्ण
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		mark_mft_record_dirty(ctx->ntfs_ino);
	पूर्ण अन्यथा अगर (IS_ERR(ctx->mrec)) अणु
		ntfs_error(vol->sb, "Failed to restore attribute search "
				"context.%s", es);
		NVolSetErrors(vol);
	पूर्ण
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (!IS_ERR(mrec))
		unmap_mft_record(mft_ni);
	up_ग_लिखो(&mft_ni->runlist.lock);
	वापस ret;
पूर्ण

/**
 * ntfs_mft_record_layout - layout an mft record पूर्णांकo a memory buffer
 * @vol:	volume to which the mft record will beदीर्घ
 * @mft_no:	mft reference specअगरying the mft record number
 * @m:		destination buffer of size >= @vol->mft_record_size bytes
 *
 * Layout an empty, unused mft record with the mft record number @mft_no पूर्णांकo
 * the buffer @m.  The volume @vol is needed because the mft record काष्ठाure
 * was modअगरied in NTFS 3.1 so we need to know which volume version this mft
 * record will be used on.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल पूर्णांक ntfs_mft_record_layout(स्थिर ntfs_volume *vol, स्थिर s64 mft_no,
		MFT_RECORD *m)
अणु
	ATTR_RECORD *a;

	ntfs_debug("Entering for mft record 0x%llx.", (दीर्घ दीर्घ)mft_no);
	अगर (mft_no >= (1ll << 32)) अणु
		ntfs_error(vol->sb, "Mft record number 0x%llx exceeds "
				"maximum of 2^32.", (दीर्घ दीर्घ)mft_no);
		वापस -दुस्फल;
	पूर्ण
	/* Start by clearing the whole mft record to gives us a clean slate. */
	स_रखो(m, 0, vol->mft_record_size);
	/* Aligned to 2-byte boundary. */
	अगर (vol->major_ver < 3 || (vol->major_ver == 3 && !vol->minor_ver))
		m->usa_ofs = cpu_to_le16((माप(MFT_RECORD_OLD) + 1) & ~1);
	अन्यथा अणु
		m->usa_ofs = cpu_to_le16((माप(MFT_RECORD) + 1) & ~1);
		/*
		 * Set the NTFS 3.1+ specअगरic fields जबतक we know that the
		 * volume version is 3.1+.
		 */
		m->reserved = 0;
		m->mft_record_number = cpu_to_le32((u32)mft_no);
	पूर्ण
	m->magic = magic_खाता;
	अगर (vol->mft_record_size >= NTFS_BLOCK_SIZE)
		m->usa_count = cpu_to_le16(vol->mft_record_size /
				NTFS_BLOCK_SIZE + 1);
	अन्यथा अणु
		m->usa_count = cpu_to_le16(1);
		ntfs_warning(vol->sb, "Sector size is bigger than mft record "
				"size.  Setting usa_count to 1.  If chkdsk "
				"reports this as corruption, please email "
				"linux-ntfs-dev@lists.sourceforge.net stating "
				"that you saw this message and that the "
				"modified filesystem created was corrupt.  "
				"Thank you.");
	पूर्ण
	/* Set the update sequence number to 1. */
	*(le16*)((u8*)m + le16_to_cpu(m->usa_ofs)) = cpu_to_le16(1);
	m->lsn = 0;
	m->sequence_number = cpu_to_le16(1);
	m->link_count = 0;
	/*
	 * Place the attributes straight after the update sequence array,
	 * aligned to 8-byte boundary.
	 */
	m->attrs_offset = cpu_to_le16((le16_to_cpu(m->usa_ofs) +
			(le16_to_cpu(m->usa_count) << 1) + 7) & ~7);
	m->flags = 0;
	/*
	 * Using attrs_offset plus eight bytes (क्रम the termination attribute).
	 * attrs_offset is alपढ़ोy aligned to 8-byte boundary, so no need to
	 * align again.
	 */
	m->bytes_in_use = cpu_to_le32(le16_to_cpu(m->attrs_offset) + 8);
	m->bytes_allocated = cpu_to_le32(vol->mft_record_size);
	m->base_mft_record = 0;
	m->next_attr_instance = 0;
	/* Add the termination attribute. */
	a = (ATTR_RECORD*)((u8*)m + le16_to_cpu(m->attrs_offset));
	a->type = AT_END;
	a->length = 0;
	ntfs_debug("Done.");
	वापस 0;
पूर्ण

/**
 * ntfs_mft_record_क्रमmat - क्रमmat an mft record on an ntfs volume
 * @vol:	volume on which to क्रमmat the mft record
 * @mft_no:	mft record number to क्रमmat
 *
 * Format the mft record @mft_no in $MFT/$DATA, i.e. lay out an empty, unused
 * mft record पूर्णांकo the appropriate place of the mft data attribute.  This is
 * used when extending the mft data attribute.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल पूर्णांक ntfs_mft_record_क्रमmat(स्थिर ntfs_volume *vol, स्थिर s64 mft_no)
अणु
	loff_t i_size;
	काष्ठा inode *mft_vi = vol->mft_ino;
	काष्ठा page *page;
	MFT_RECORD *m;
	pgoff_t index, end_index;
	अचिन्हित पूर्णांक ofs;
	पूर्णांक err;

	ntfs_debug("Entering for mft record 0x%llx.", (दीर्घ दीर्घ)mft_no);
	/*
	 * The index पूर्णांकo the page cache and the offset within the page cache
	 * page of the wanted mft record.
	 */
	index = mft_no << vol->mft_record_size_bits >> PAGE_SHIFT;
	ofs = (mft_no << vol->mft_record_size_bits) & ~PAGE_MASK;
	/* The maximum valid index पूर्णांकo the page cache क्रम $MFT's data. */
	i_size = i_size_पढ़ो(mft_vi);
	end_index = i_size >> PAGE_SHIFT;
	अगर (unlikely(index >= end_index)) अणु
		अगर (unlikely(index > end_index || ofs + vol->mft_record_size >=
				(i_size & ~PAGE_MASK))) अणु
			ntfs_error(vol->sb, "Tried to format non-existing mft "
					"record 0x%llx.", (दीर्घ दीर्घ)mft_no);
			वापस -ENOENT;
		पूर्ण
	पूर्ण
	/* Read, map, and pin the page containing the mft record. */
	page = ntfs_map_page(mft_vi->i_mapping, index);
	अगर (IS_ERR(page)) अणु
		ntfs_error(vol->sb, "Failed to map page containing mft record "
				"to format 0x%llx.", (दीर्घ दीर्घ)mft_no);
		वापस PTR_ERR(page);
	पूर्ण
	lock_page(page);
	BUG_ON(!PageUptodate(page));
	ClearPageUptodate(page);
	m = (MFT_RECORD*)((u8*)page_address(page) + ofs);
	err = ntfs_mft_record_layout(vol, mft_no, m);
	अगर (unlikely(err)) अणु
		ntfs_error(vol->sb, "Failed to layout mft record 0x%llx.",
				(दीर्घ दीर्घ)mft_no);
		SetPageUptodate(page);
		unlock_page(page);
		ntfs_unmap_page(page);
		वापस err;
	पूर्ण
	flush_dcache_page(page);
	SetPageUptodate(page);
	unlock_page(page);
	/*
	 * Make sure the mft record is written out to disk.  We could use
	 * ilookup5() to check अगर an inode is in icache and so on but this is
	 * unnecessary as ntfs_ग_लिखोpage() will ग_लिखो the dirty record anyway.
	 */
	mark_ntfs_record_dirty(page, ofs);
	ntfs_unmap_page(page);
	ntfs_debug("Done.");
	वापस 0;
पूर्ण

/**
 * ntfs_mft_record_alloc - allocate an mft record on an ntfs volume
 * @vol:	[IN]  volume on which to allocate the mft record
 * @mode:	[IN]  mode अगर want a file or directory, i.e. base inode or 0
 * @base_ni:	[IN]  खोलो base inode अगर allocating an extent mft record or शून्य
 * @mrec:	[OUT] on successful वापस this is the mapped mft record
 *
 * Allocate an mft record in $MFT/$DATA of an खोलो ntfs volume @vol.
 *
 * If @base_ni is शून्य make the mft record a base mft record, i.e. a file or
 * direvctory inode, and allocate it at the शेष allocator position.  In
 * this हाल @mode is the file mode as given to us by the caller.  We in
 * particular use @mode to distinguish whether a file or a directory is being
 * created (S_IFसूची(mode) and S_IFREG(mode), respectively).
 *
 * If @base_ni is not शून्य make the allocated mft record an extent record,
 * allocate it starting at the mft record after the base mft record and attach
 * the allocated and खोलोed ntfs inode to the base inode @base_ni.  In this
 * हाल @mode must be 0 as it is meaningless क्रम extent inodes.
 *
 * You need to check the वापस value with IS_ERR().  If false, the function
 * was successful and the वापस value is the now खोलोed ntfs inode of the
 * allocated mft record.  *@mrec is then set to the allocated, mapped, pinned,
 * and locked mft record.  If IS_ERR() is true, the function failed and the
 * error code is obtained from PTR_ERR(वापस value).  *@mrec is undefined in
 * this हाल.
 *
 * Allocation strategy:
 *
 * To find a मुक्त mft record, we scan the mft biपंचांगap क्रम a zero bit.  To
 * optimize this we start scanning at the place specअगरied by @base_ni or अगर
 * @base_ni is शून्य we start where we last stopped and we perक्रमm wrap around
 * when we reach the end.  Note, we करो not try to allocate mft records below
 * number 24 because numbers 0 to 15 are the defined प्रणाली files anyway and 16
 * to 24 are special in that they are used क्रम storing extension mft records
 * क्रम the $DATA attribute of $MFT.  This is required to aव्योम the possibility
 * of creating a runlist with a circular dependency which once written to disk
 * can never be पढ़ो in again.  Winकरोws will only use records 16 to 24 क्रम
 * normal files अगर the volume is completely out of space.  We never use them
 * which means that when the volume is really out of space we cannot create any
 * more files जबतक Winकरोws can still create up to 8 small files.  We can start
 * करोing this at some later समय, it करोes not matter much क्रम now.
 *
 * When scanning the mft biपंचांगap, we only search up to the last allocated mft
 * record.  If there are no मुक्त records left in the range 24 to number of
 * allocated mft records, then we extend the $MFT/$DATA attribute in order to
 * create मुक्त mft records.  We extend the allocated size of $MFT/$DATA by 16
 * records at a समय or one cluster, अगर cluster size is above 16kiB.  If there
 * is not sufficient space to करो this, we try to extend by a single mft record
 * or one cluster, अगर cluster size is above the mft record size.
 *
 * No matter how many mft records we allocate, we initialize only the first
 * allocated mft record, incrementing mft data size and initialized size
 * accordingly, खोलो an ntfs_inode क्रम it and वापस it to the caller, unless
 * there are less than 24 mft records, in which हाल we allocate and initialize
 * mft records until we reach record 24 which we consider as the first मुक्त mft
 * record क्रम use by normal files.
 *
 * If during any stage we overflow the initialized data in the mft biपंचांगap, we
 * extend the initialized size (and data size) by 8 bytes, allocating another
 * cluster अगर required.  The biपंचांगap data size has to be at least equal to the
 * number of mft records in the mft, but it can be bigger, in which हाल the
 * superflous bits are padded with zeroes.
 *
 * Thus, when we वापस successfully (IS_ERR() is false), we will have:
 *	- initialized / extended the mft biपंचांगap अगर necessary,
 *	- initialized / extended the mft data अगर necessary,
 *	- set the bit corresponding to the mft record being allocated in the
 *	  mft biपंचांगap,
 *	- खोलोed an ntfs_inode क्रम the allocated mft record, and we will have
 *	- वापसed the ntfs_inode as well as the allocated mapped, pinned, and
 *	  locked mft record.
 *
 * On error, the volume will be left in a consistent state and no record will
 * be allocated.  If rolling back a partial operation fails, we may leave some
 * inconsistent metadata in which हाल we set NVolErrors() so the volume is
 * left dirty when unmounted.
 *
 * Note, this function cannot make use of most of the normal functions, like
 * क्रम example क्रम attribute resizing, etc, because when the run list overflows
 * the base mft record and an attribute list is used, it is very important that
 * the extension mft records used to store the $DATA attribute of $MFT can be
 * reached without having to पढ़ो the inक्रमmation contained inside them, as
 * this would make it impossible to find them in the first place after the
 * volume is unmounted.  $MFT/$BITMAP probably करोes not need to follow this
 * rule because the biपंचांगap is not essential क्रम finding the mft records, but on
 * the other hand, handling the biपंचांगap in this special way would make lअगरe
 * easier because otherwise there might be circular invocations of functions
 * when पढ़ोing the biपंचांगap.
 */
ntfs_inode *ntfs_mft_record_alloc(ntfs_volume *vol, स्थिर पूर्णांक mode,
		ntfs_inode *base_ni, MFT_RECORD **mrec)
अणु
	s64 ll, bit, old_data_initialized, old_data_size;
	अचिन्हित दीर्घ flags;
	काष्ठा inode *vi;
	काष्ठा page *page;
	ntfs_inode *mft_ni, *mftbmp_ni, *ni;
	ntfs_attr_search_ctx *ctx;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	pgoff_t index;
	अचिन्हित पूर्णांक ofs;
	पूर्णांक err;
	le16 seq_no, usn;
	bool record_क्रमmatted = false;

	अगर (base_ni) अणु
		ntfs_debug("Entering (allocating an extent mft record for "
				"base mft record 0x%llx).",
				(दीर्घ दीर्घ)base_ni->mft_no);
		/* @mode and @base_ni are mutually exclusive. */
		BUG_ON(mode);
	पूर्ण अन्यथा
		ntfs_debug("Entering (allocating a base mft record).");
	अगर (mode) अणु
		/* @mode and @base_ni are mutually exclusive. */
		BUG_ON(base_ni);
		/* We only support creation of normal files and directories. */
		अगर (!S_ISREG(mode) && !S_ISसूची(mode))
			वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण
	BUG_ON(!mrec);
	mft_ni = NTFS_I(vol->mft_ino);
	mftbmp_ni = NTFS_I(vol->mftbmp_ino);
	करोwn_ग_लिखो(&vol->mftbmp_lock);
	bit = ntfs_mft_biपंचांगap_find_and_alloc_मुक्त_rec_nolock(vol, base_ni);
	अगर (bit >= 0) अणु
		ntfs_debug("Found and allocated free record (#1), bit 0x%llx.",
				(दीर्घ दीर्घ)bit);
		जाओ have_alloc_rec;
	पूर्ण
	अगर (bit != -ENOSPC) अणु
		up_ग_लिखो(&vol->mftbmp_lock);
		वापस ERR_PTR(bit);
	पूर्ण
	/*
	 * No मुक्त mft records left.  If the mft biपंचांगap alपढ़ोy covers more
	 * than the currently used mft records, the next records are all मुक्त,
	 * so we can simply allocate the first unused mft record.
	 * Note: We also have to make sure that the mft biपंचांगap at least covers
	 * the first 24 mft records as they are special and whilst they may not
	 * be in use, we करो not allocate from them.
	 */
	पढ़ो_lock_irqsave(&mft_ni->size_lock, flags);
	ll = mft_ni->initialized_size >> vol->mft_record_size_bits;
	पढ़ो_unlock_irqrestore(&mft_ni->size_lock, flags);
	पढ़ो_lock_irqsave(&mftbmp_ni->size_lock, flags);
	old_data_initialized = mftbmp_ni->initialized_size;
	पढ़ो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
	अगर (old_data_initialized << 3 > ll && old_data_initialized > 3) अणु
		bit = ll;
		अगर (bit < 24)
			bit = 24;
		अगर (unlikely(bit >= (1ll << 32)))
			जाओ max_err_out;
		ntfs_debug("Found free record (#2), bit 0x%llx.",
				(दीर्घ दीर्घ)bit);
		जाओ found_मुक्त_rec;
	पूर्ण
	/*
	 * The mft biपंचांगap needs to be expanded until it covers the first unused
	 * mft record that we can allocate.
	 * Note: The smallest mft record we allocate is mft record 24.
	 */
	bit = old_data_initialized << 3;
	अगर (unlikely(bit >= (1ll << 32)))
		जाओ max_err_out;
	पढ़ो_lock_irqsave(&mftbmp_ni->size_lock, flags);
	old_data_size = mftbmp_ni->allocated_size;
	ntfs_debug("Status of mftbmp before extension: allocated_size 0x%llx, "
			"data_size 0x%llx, initialized_size 0x%llx.",
			(दीर्घ दीर्घ)old_data_size,
			(दीर्घ दीर्घ)i_size_पढ़ो(vol->mftbmp_ino),
			(दीर्घ दीर्घ)old_data_initialized);
	पढ़ो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
	अगर (old_data_initialized + 8 > old_data_size) अणु
		/* Need to extend biपंचांगap by one more cluster. */
		ntfs_debug("mftbmp: initialized_size + 8 > allocated_size.");
		err = ntfs_mft_biपंचांगap_extend_allocation_nolock(vol);
		अगर (unlikely(err)) अणु
			up_ग_लिखो(&vol->mftbmp_lock);
			जाओ err_out;
		पूर्ण
#अगर_घोषित DEBUG
		पढ़ो_lock_irqsave(&mftbmp_ni->size_lock, flags);
		ntfs_debug("Status of mftbmp after allocation extension: "
				"allocated_size 0x%llx, data_size 0x%llx, "
				"initialized_size 0x%llx.",
				(दीर्घ दीर्घ)mftbmp_ni->allocated_size,
				(दीर्घ दीर्घ)i_size_पढ़ो(vol->mftbmp_ino),
				(दीर्घ दीर्घ)mftbmp_ni->initialized_size);
		पढ़ो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
#पूर्ण_अगर /* DEBUG */
	पूर्ण
	/*
	 * We now have sufficient allocated space, extend the initialized_size
	 * as well as the data_size अगर necessary and fill the new space with
	 * zeroes.
	 */
	err = ntfs_mft_biपंचांगap_extend_initialized_nolock(vol);
	अगर (unlikely(err)) अणु
		up_ग_लिखो(&vol->mftbmp_lock);
		जाओ err_out;
	पूर्ण
#अगर_घोषित DEBUG
	पढ़ो_lock_irqsave(&mftbmp_ni->size_lock, flags);
	ntfs_debug("Status of mftbmp after initialized extension: "
			"allocated_size 0x%llx, data_size 0x%llx, "
			"initialized_size 0x%llx.",
			(दीर्घ दीर्घ)mftbmp_ni->allocated_size,
			(दीर्घ दीर्घ)i_size_पढ़ो(vol->mftbmp_ino),
			(दीर्घ दीर्घ)mftbmp_ni->initialized_size);
	पढ़ो_unlock_irqrestore(&mftbmp_ni->size_lock, flags);
#पूर्ण_अगर /* DEBUG */
	ntfs_debug("Found free record (#3), bit 0x%llx.", (दीर्घ दीर्घ)bit);
found_मुक्त_rec:
	/* @bit is the found मुक्त mft record, allocate it in the mft biपंचांगap. */
	ntfs_debug("At found_free_rec.");
	err = ntfs_biपंचांगap_set_bit(vol->mftbmp_ino, bit);
	अगर (unlikely(err)) अणु
		ntfs_error(vol->sb, "Failed to allocate bit in mft bitmap.");
		up_ग_लिखो(&vol->mftbmp_lock);
		जाओ err_out;
	पूर्ण
	ntfs_debug("Set bit 0x%llx in mft bitmap.", (दीर्घ दीर्घ)bit);
have_alloc_rec:
	/*
	 * The mft biपंचांगap is now uptodate.  Deal with mft data attribute now.
	 * Note, we keep hold of the mft biपंचांगap lock क्रम writing until all
	 * modअगरications to the mft data attribute are complete, too, as they
	 * will impact decisions क्रम mft biपंचांगap and mft record allocation करोne
	 * by a parallel allocation and अगर the lock is not मुख्यtained a
	 * parallel allocation could allocate the same mft record as this one.
	 */
	ll = (bit + 1) << vol->mft_record_size_bits;
	पढ़ो_lock_irqsave(&mft_ni->size_lock, flags);
	old_data_initialized = mft_ni->initialized_size;
	पढ़ो_unlock_irqrestore(&mft_ni->size_lock, flags);
	अगर (ll <= old_data_initialized) अणु
		ntfs_debug("Allocated mft record already initialized.");
		जाओ mft_rec_alपढ़ोy_initialized;
	पूर्ण
	ntfs_debug("Initializing allocated mft record.");
	/*
	 * The mft record is outside the initialized data.  Extend the mft data
	 * attribute until it covers the allocated record.  The loop is only
	 * actually traversed more than once when a freshly क्रमmatted volume is
	 * first written to so it optimizes away nicely in the common हाल.
	 */
	पढ़ो_lock_irqsave(&mft_ni->size_lock, flags);
	ntfs_debug("Status of mft data before extension: "
			"allocated_size 0x%llx, data_size 0x%llx, "
			"initialized_size 0x%llx.",
			(दीर्घ दीर्घ)mft_ni->allocated_size,
			(दीर्घ दीर्घ)i_size_पढ़ो(vol->mft_ino),
			(दीर्घ दीर्घ)mft_ni->initialized_size);
	जबतक (ll > mft_ni->allocated_size) अणु
		पढ़ो_unlock_irqrestore(&mft_ni->size_lock, flags);
		err = ntfs_mft_data_extend_allocation_nolock(vol);
		अगर (unlikely(err)) अणु
			ntfs_error(vol->sb, "Failed to extend mft data "
					"allocation.");
			जाओ unकरो_mftbmp_alloc_nolock;
		पूर्ण
		पढ़ो_lock_irqsave(&mft_ni->size_lock, flags);
		ntfs_debug("Status of mft data after allocation extension: "
				"allocated_size 0x%llx, data_size 0x%llx, "
				"initialized_size 0x%llx.",
				(दीर्घ दीर्घ)mft_ni->allocated_size,
				(दीर्घ दीर्घ)i_size_पढ़ो(vol->mft_ino),
				(दीर्घ दीर्घ)mft_ni->initialized_size);
	पूर्ण
	पढ़ो_unlock_irqrestore(&mft_ni->size_lock, flags);
	/*
	 * Extend mft data initialized size (and data size of course) to reach
	 * the allocated mft record, क्रमmatting the mft records alदीर्घ the way.
	 * Note: We only modअगरy the ntfs_inode काष्ठाure as that is all that is
	 * needed by ntfs_mft_record_क्रमmat().  We will update the attribute
	 * record itself in one fell swoop later on.
	 */
	ग_लिखो_lock_irqsave(&mft_ni->size_lock, flags);
	old_data_initialized = mft_ni->initialized_size;
	old_data_size = vol->mft_ino->i_size;
	जबतक (ll > mft_ni->initialized_size) अणु
		s64 new_initialized_size, mft_no;
		
		new_initialized_size = mft_ni->initialized_size +
				vol->mft_record_size;
		mft_no = mft_ni->initialized_size >> vol->mft_record_size_bits;
		अगर (new_initialized_size > i_size_पढ़ो(vol->mft_ino))
			i_size_ग_लिखो(vol->mft_ino, new_initialized_size);
		ग_लिखो_unlock_irqrestore(&mft_ni->size_lock, flags);
		ntfs_debug("Initializing mft record 0x%llx.",
				(दीर्घ दीर्घ)mft_no);
		err = ntfs_mft_record_क्रमmat(vol, mft_no);
		अगर (unlikely(err)) अणु
			ntfs_error(vol->sb, "Failed to format mft record.");
			जाओ unकरो_data_init;
		पूर्ण
		ग_लिखो_lock_irqsave(&mft_ni->size_lock, flags);
		mft_ni->initialized_size = new_initialized_size;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&mft_ni->size_lock, flags);
	record_क्रमmatted = true;
	/* Update the mft data attribute record to reflect the new sizes. */
	m = map_mft_record(mft_ni);
	अगर (IS_ERR(m)) अणु
		ntfs_error(vol->sb, "Failed to map mft record.");
		err = PTR_ERR(m);
		जाओ unकरो_data_init;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(mft_ni, m);
	अगर (unlikely(!ctx)) अणु
		ntfs_error(vol->sb, "Failed to get search context.");
		err = -ENOMEM;
		unmap_mft_record(mft_ni);
		जाओ unकरो_data_init;
	पूर्ण
	err = ntfs_attr_lookup(mft_ni->type, mft_ni->name, mft_ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		ntfs_error(vol->sb, "Failed to find first attribute extent of "
				"mft data attribute.");
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(mft_ni);
		जाओ unकरो_data_init;
	पूर्ण
	a = ctx->attr;
	पढ़ो_lock_irqsave(&mft_ni->size_lock, flags);
	a->data.non_resident.initialized_size =
			cpu_to_sle64(mft_ni->initialized_size);
	a->data.non_resident.data_size =
			cpu_to_sle64(i_size_पढ़ो(vol->mft_ino));
	पढ़ो_unlock_irqrestore(&mft_ni->size_lock, flags);
	/* Ensure the changes make it to disk. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(mft_ni);
	पढ़ो_lock_irqsave(&mft_ni->size_lock, flags);
	ntfs_debug("Status of mft data after mft record initialization: "
			"allocated_size 0x%llx, data_size 0x%llx, "
			"initialized_size 0x%llx.",
			(दीर्घ दीर्घ)mft_ni->allocated_size,
			(दीर्घ दीर्घ)i_size_पढ़ो(vol->mft_ino),
			(दीर्घ दीर्घ)mft_ni->initialized_size);
	BUG_ON(i_size_पढ़ो(vol->mft_ino) > mft_ni->allocated_size);
	BUG_ON(mft_ni->initialized_size > i_size_पढ़ो(vol->mft_ino));
	पढ़ो_unlock_irqrestore(&mft_ni->size_lock, flags);
mft_rec_alपढ़ोy_initialized:
	/*
	 * We can finally drop the mft biपंचांगap lock as the mft data attribute
	 * has been fully updated.  The only disparity left is that the
	 * allocated mft record still needs to be marked as in use to match the
	 * set bit in the mft biपंचांगap but this is actually not a problem since
	 * this mft record is not referenced from anywhere yet and the fact
	 * that it is allocated in the mft biपंचांगap means that no-one will try to
	 * allocate it either.
	 */
	up_ग_लिखो(&vol->mftbmp_lock);
	/*
	 * We now have allocated and initialized the mft record.  Calculate the
	 * index of and the offset within the page cache page the record is in.
	 */
	index = bit << vol->mft_record_size_bits >> PAGE_SHIFT;
	ofs = (bit << vol->mft_record_size_bits) & ~PAGE_MASK;
	/* Read, map, and pin the page containing the mft record. */
	page = ntfs_map_page(vol->mft_ino->i_mapping, index);
	अगर (IS_ERR(page)) अणु
		ntfs_error(vol->sb, "Failed to map page containing allocated "
				"mft record 0x%llx.", (दीर्घ दीर्घ)bit);
		err = PTR_ERR(page);
		जाओ unकरो_mftbmp_alloc;
	पूर्ण
	lock_page(page);
	BUG_ON(!PageUptodate(page));
	ClearPageUptodate(page);
	m = (MFT_RECORD*)((u8*)page_address(page) + ofs);
	/* If we just क्रमmatted the mft record no need to करो it again. */
	अगर (!record_क्रमmatted) अणु
		/* Sanity check that the mft record is really not in use. */
		अगर (ntfs_is_file_record(m->magic) &&
				(m->flags & MFT_RECORD_IN_USE)) अणु
			ntfs_error(vol->sb, "Mft record 0x%llx was marked "
					"free in mft bitmap but is marked "
					"used itself.  Corrupt filesystem.  "
					"Unmount and run chkdsk.",
					(दीर्घ दीर्घ)bit);
			err = -EIO;
			SetPageUptodate(page);
			unlock_page(page);
			ntfs_unmap_page(page);
			NVolSetErrors(vol);
			जाओ unकरो_mftbmp_alloc;
		पूर्ण
		/*
		 * We need to (re-)क्रमmat the mft record, preserving the
		 * sequence number अगर it is not zero as well as the update
		 * sequence number अगर it is not zero or -1 (0xffff).  This
		 * means we करो not need to care whether or not something went
		 * wrong with the previous mft record.
		 */
		seq_no = m->sequence_number;
		usn = *(le16*)((u8*)m + le16_to_cpu(m->usa_ofs));
		err = ntfs_mft_record_layout(vol, bit, m);
		अगर (unlikely(err)) अणु
			ntfs_error(vol->sb, "Failed to layout allocated mft "
					"record 0x%llx.", (दीर्घ दीर्घ)bit);
			SetPageUptodate(page);
			unlock_page(page);
			ntfs_unmap_page(page);
			जाओ unकरो_mftbmp_alloc;
		पूर्ण
		अगर (seq_no)
			m->sequence_number = seq_no;
		अगर (usn && le16_to_cpu(usn) != 0xffff)
			*(le16*)((u8*)m + le16_to_cpu(m->usa_ofs)) = usn;
	पूर्ण
	/* Set the mft record itself in use. */
	m->flags |= MFT_RECORD_IN_USE;
	अगर (S_ISसूची(mode))
		m->flags |= MFT_RECORD_IS_सूचीECTORY;
	flush_dcache_page(page);
	SetPageUptodate(page);
	अगर (base_ni) अणु
		MFT_RECORD *m_पंचांगp;

		/*
		 * Setup the base mft record in the extent mft record.  This
		 * completes initialization of the allocated extent mft record
		 * and we can simply use it with map_extent_mft_record().
		 */
		m->base_mft_record = MK_LE_MREF(base_ni->mft_no,
				base_ni->seq_no);
		/*
		 * Allocate an extent inode काष्ठाure क्रम the new mft record,
		 * attach it to the base inode @base_ni and map, pin, and lock
		 * its, i.e. the allocated, mft record.
		 */
		m_पंचांगp = map_extent_mft_record(base_ni, bit, &ni);
		अगर (IS_ERR(m_पंचांगp)) अणु
			ntfs_error(vol->sb, "Failed to map allocated extent "
					"mft record 0x%llx.", (दीर्घ दीर्घ)bit);
			err = PTR_ERR(m_पंचांगp);
			/* Set the mft record itself not in use. */
			m->flags &= cpu_to_le16(
					~le16_to_cpu(MFT_RECORD_IN_USE));
			flush_dcache_page(page);
			/* Make sure the mft record is written out to disk. */
			mark_ntfs_record_dirty(page, ofs);
			unlock_page(page);
			ntfs_unmap_page(page);
			जाओ unकरो_mftbmp_alloc;
		पूर्ण
		BUG_ON(m != m_पंचांगp);
		/*
		 * Make sure the allocated mft record is written out to disk.
		 * No need to set the inode dirty because the caller is going
		 * to करो that anyway after finishing with the new extent mft
		 * record (e.g. at a minimum a new attribute will be added to
		 * the mft record.
		 */
		mark_ntfs_record_dirty(page, ofs);
		unlock_page(page);
		/*
		 * Need to unmap the page since map_extent_mft_record() mapped
		 * it as well so we have it mapped twice at the moment.
		 */
		ntfs_unmap_page(page);
	पूर्ण अन्यथा अणु
		/*
		 * Allocate a new VFS inode and set it up.  NOTE: @vi->i_nlink
		 * is set to 1 but the mft record->link_count is 0.  The caller
		 * needs to bear this in mind.
		 */
		vi = new_inode(vol->sb);
		अगर (unlikely(!vi)) अणु
			err = -ENOMEM;
			/* Set the mft record itself not in use. */
			m->flags &= cpu_to_le16(
					~le16_to_cpu(MFT_RECORD_IN_USE));
			flush_dcache_page(page);
			/* Make sure the mft record is written out to disk. */
			mark_ntfs_record_dirty(page, ofs);
			unlock_page(page);
			ntfs_unmap_page(page);
			जाओ unकरो_mftbmp_alloc;
		पूर्ण
		vi->i_ino = bit;

		/* The owner and group come from the ntfs volume. */
		vi->i_uid = vol->uid;
		vi->i_gid = vol->gid;

		/* Initialize the ntfs specअगरic part of @vi. */
		ntfs_init_big_inode(vi);
		ni = NTFS_I(vi);
		/*
		 * Set the appropriate mode, attribute type, and name.  For
		 * directories, also setup the index values to the शेषs.
		 */
		अगर (S_ISसूची(mode)) अणु
			vi->i_mode = S_IFसूची | S_IRWXUGO;
			vi->i_mode &= ~vol->dmask;

			NInoSetMstProtected(ni);
			ni->type = AT_INDEX_ALLOCATION;
			ni->name = I30;
			ni->name_len = 4;

			ni->itype.index.block_size = 4096;
			ni->itype.index.block_size_bits = ntfs_ffs(4096) - 1;
			ni->itype.index.collation_rule = COLLATION_खाता_NAME;
			अगर (vol->cluster_size <= ni->itype.index.block_size) अणु
				ni->itype.index.vcn_size = vol->cluster_size;
				ni->itype.index.vcn_size_bits =
						vol->cluster_size_bits;
			पूर्ण अन्यथा अणु
				ni->itype.index.vcn_size = vol->sector_size;
				ni->itype.index.vcn_size_bits =
						vol->sector_size_bits;
			पूर्ण
		पूर्ण अन्यथा अणु
			vi->i_mode = S_IFREG | S_IRWXUGO;
			vi->i_mode &= ~vol->fmask;

			ni->type = AT_DATA;
			ni->name = शून्य;
			ni->name_len = 0;
		पूर्ण
		अगर (IS_RDONLY(vi))
			vi->i_mode &= ~S_IWUGO;

		/* Set the inode बार to the current समय. */
		vi->i_aसमय = vi->i_mसमय = vi->i_स_समय =
			current_समय(vi);
		/*
		 * Set the file size to 0, the ntfs inode sizes are set to 0 by
		 * the call to ntfs_init_big_inode() below.
		 */
		vi->i_size = 0;
		vi->i_blocks = 0;

		/* Set the sequence number. */
		vi->i_generation = ni->seq_no = le16_to_cpu(m->sequence_number);
		/*
		 * Manually map, pin, and lock the mft record as we alपढ़ोy
		 * have its page mapped and it is very easy to करो.
		 */
		atomic_inc(&ni->count);
		mutex_lock(&ni->mrec_lock);
		ni->page = page;
		ni->page_ofs = ofs;
		/*
		 * Make sure the allocated mft record is written out to disk.
		 * NOTE: We करो not set the ntfs inode dirty because this would
		 * fail in ntfs_ग_लिखो_inode() because the inode करोes not have a
		 * standard inक्रमmation attribute yet.  Also, there is no need
		 * to set the inode dirty because the caller is going to करो
		 * that anyway after finishing with the new mft record (e.g. at
		 * a minimum some new attributes will be added to the mft
		 * record.
		 */
		mark_ntfs_record_dirty(page, ofs);
		unlock_page(page);

		/* Add the inode to the inode hash क्रम the superblock. */
		insert_inode_hash(vi);

		/* Update the शेष mft allocation position. */
		vol->mft_data_pos = bit + 1;
	पूर्ण
	/*
	 * Return the खोलोed, allocated inode of the allocated mft record as
	 * well as the mapped, pinned, and locked mft record.
	 */
	ntfs_debug("Returning opened, allocated %sinode 0x%llx.",
			base_ni ? "extent " : "", (दीर्घ दीर्घ)bit);
	*mrec = m;
	वापस ni;
unकरो_data_init:
	ग_लिखो_lock_irqsave(&mft_ni->size_lock, flags);
	mft_ni->initialized_size = old_data_initialized;
	i_size_ग_लिखो(vol->mft_ino, old_data_size);
	ग_लिखो_unlock_irqrestore(&mft_ni->size_lock, flags);
	जाओ unकरो_mftbmp_alloc_nolock;
unकरो_mftbmp_alloc:
	करोwn_ग_लिखो(&vol->mftbmp_lock);
unकरो_mftbmp_alloc_nolock:
	अगर (ntfs_biपंचांगap_clear_bit(vol->mftbmp_ino, bit)) अणु
		ntfs_error(vol->sb, "Failed to clear bit in mft bitmap.%s", es);
		NVolSetErrors(vol);
	पूर्ण
	up_ग_लिखो(&vol->mftbmp_lock);
err_out:
	वापस ERR_PTR(err);
max_err_out:
	ntfs_warning(vol->sb, "Cannot allocate mft record because the maximum "
			"number of inodes (2^32) has alपढ़ोy been reached.");
	up_ग_लिखो(&vol->mftbmp_lock);
	वापस ERR_PTR(-ENOSPC);
पूर्ण

/**
 * ntfs_extent_mft_record_मुक्त - मुक्त an extent mft record on an ntfs volume
 * @ni:		ntfs inode of the mapped extent mft record to मुक्त
 * @m:		mapped extent mft record of the ntfs inode @ni
 *
 * Free the mapped extent mft record @m of the extent ntfs inode @ni.
 *
 * Note that this function unmaps the mft record and बंदs and destroys @ni
 * पूर्णांकernally and hence you cannot use either @ni nor @m any more after this
 * function वापसs success.
 *
 * On success वापस 0 and on error वापस -त्रुटि_सं.  @ni and @m are still valid
 * in this हाल and have not been मुक्तd.
 *
 * For some errors an error message is displayed and the success code 0 is
 * वापसed and the volume is then left dirty on umount.  This makes sense in
 * हाल we could not rollback the changes that were alपढ़ोy करोne since the
 * caller no दीर्घer wants to reference this mft record so it करोes not matter to
 * the caller अगर something is wrong with it as दीर्घ as it is properly detached
 * from the base inode.
 */
पूर्णांक ntfs_extent_mft_record_मुक्त(ntfs_inode *ni, MFT_RECORD *m)
अणु
	अचिन्हित दीर्घ mft_no = ni->mft_no;
	ntfs_volume *vol = ni->vol;
	ntfs_inode *base_ni;
	ntfs_inode **extent_nis;
	पूर्णांक i, err;
	le16 old_seq_no;
	u16 seq_no;
	
	BUG_ON(NInoAttr(ni));
	BUG_ON(ni->nr_extents != -1);

	mutex_lock(&ni->extent_lock);
	base_ni = ni->ext.base_ntfs_ino;
	mutex_unlock(&ni->extent_lock);

	BUG_ON(base_ni->nr_extents <= 0);

	ntfs_debug("Entering for extent inode 0x%lx, base inode 0x%lx.\n",
			mft_no, base_ni->mft_no);

	mutex_lock(&base_ni->extent_lock);

	/* Make sure we are holding the only reference to the extent inode. */
	अगर (atomic_पढ़ो(&ni->count) > 2) अणु
		ntfs_error(vol->sb, "Tried to free busy extent inode 0x%lx, "
				"not freeing.", base_ni->mft_no);
		mutex_unlock(&base_ni->extent_lock);
		वापस -EBUSY;
	पूर्ण

	/* Dissociate the ntfs inode from the base inode. */
	extent_nis = base_ni->ext.extent_ntfs_inos;
	err = -ENOENT;
	क्रम (i = 0; i < base_ni->nr_extents; i++) अणु
		अगर (ni != extent_nis[i])
			जारी;
		extent_nis += i;
		base_ni->nr_extents--;
		स_हटाओ(extent_nis, extent_nis + 1, (base_ni->nr_extents - i) *
				माप(ntfs_inode*));
		err = 0;
		अवरोध;
	पूर्ण

	mutex_unlock(&base_ni->extent_lock);

	अगर (unlikely(err)) अणु
		ntfs_error(vol->sb, "Extent inode 0x%lx is not attached to "
				"its base inode 0x%lx.", mft_no,
				base_ni->mft_no);
		BUG();
	पूर्ण

	/*
	 * The extent inode is no दीर्घer attached to the base inode so no one
	 * can get a reference to it any more.
	 */

	/* Mark the mft record as not in use. */
	m->flags &= ~MFT_RECORD_IN_USE;

	/* Increment the sequence number, skipping zero, अगर it is not zero. */
	old_seq_no = m->sequence_number;
	seq_no = le16_to_cpu(old_seq_no);
	अगर (seq_no == 0xffff)
		seq_no = 1;
	अन्यथा अगर (seq_no)
		seq_no++;
	m->sequence_number = cpu_to_le16(seq_no);

	/*
	 * Set the ntfs inode dirty and ग_लिखो it out.  We करो not need to worry
	 * about the base inode here since whatever caused the extent mft
	 * record to be मुक्तd is guaranteed to करो it alपढ़ोy.
	 */
	NInoSetDirty(ni);
	err = ग_लिखो_mft_record(ni, m, 0);
	अगर (unlikely(err)) अणु
		ntfs_error(vol->sb, "Failed to write mft record 0x%lx, not "
				"freeing.", mft_no);
		जाओ rollback;
	पूर्ण
rollback_error:
	/* Unmap and throw away the now मुक्तd extent inode. */
	unmap_extent_mft_record(ni);
	ntfs_clear_extent_inode(ni);

	/* Clear the bit in the $MFT/$BITMAP corresponding to this record. */
	करोwn_ग_लिखो(&vol->mftbmp_lock);
	err = ntfs_biपंचांगap_clear_bit(vol->mftbmp_ino, mft_no);
	up_ग_लिखो(&vol->mftbmp_lock);
	अगर (unlikely(err)) अणु
		/*
		 * The extent inode is gone but we failed to deallocate it in
		 * the mft biपंचांगap.  Just emit a warning and leave the volume
		 * dirty on umount.
		 */
		ntfs_error(vol->sb, "Failed to clear bit in mft bitmap.%s", es);
		NVolSetErrors(vol);
	पूर्ण
	वापस 0;
rollback:
	/* Rollback what we did... */
	mutex_lock(&base_ni->extent_lock);
	extent_nis = base_ni->ext.extent_ntfs_inos;
	अगर (!(base_ni->nr_extents & 3)) अणु
		पूर्णांक new_size = (base_ni->nr_extents + 4) * माप(ntfs_inode*);

		extent_nis = kदो_स्मृति(new_size, GFP_NOFS);
		अगर (unlikely(!extent_nis)) अणु
			ntfs_error(vol->sb, "Failed to allocate internal "
					"buffer during rollback.%s", es);
			mutex_unlock(&base_ni->extent_lock);
			NVolSetErrors(vol);
			जाओ rollback_error;
		पूर्ण
		अगर (base_ni->nr_extents) अणु
			BUG_ON(!base_ni->ext.extent_ntfs_inos);
			स_नकल(extent_nis, base_ni->ext.extent_ntfs_inos,
					new_size - 4 * माप(ntfs_inode*));
			kमुक्त(base_ni->ext.extent_ntfs_inos);
		पूर्ण
		base_ni->ext.extent_ntfs_inos = extent_nis;
	पूर्ण
	m->flags |= MFT_RECORD_IN_USE;
	m->sequence_number = old_seq_no;
	extent_nis[base_ni->nr_extents++] = ni;
	mutex_unlock(&base_ni->extent_lock);
	mark_mft_record_dirty(ni);
	वापस err;
पूर्ण
#पूर्ण_अगर /* NTFS_RW */
