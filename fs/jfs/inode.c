<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */

#समावेश <linux/fs.h>
#समावेश <linux/mpage.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/uपन.स>
#समावेश <linux/ग_लिखोback.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_imap.h"
#समावेश "jfs_extent.h"
#समावेश "jfs_unicode.h"
#समावेश "jfs_debug.h"
#समावेश "jfs_dmap.h"


काष्ठा inode *jfs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा inode *inode;
	पूर्णांक ret;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	ret = diRead(inode);
	अगर (ret < 0) अणु
		iget_failed(inode);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op = &jfs_file_inode_operations;
		inode->i_fop = &jfs_file_operations;
		inode->i_mapping->a_ops = &jfs_aops;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &jfs_dir_inode_operations;
		inode->i_fop = &jfs_dir_operations;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		अगर (inode->i_size >= IDATASIZE) अणु
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
			inode->i_mapping->a_ops = &jfs_aops;
		पूर्ण अन्यथा अणु
			inode->i_op = &jfs_fast_symlink_inode_operations;
			inode->i_link = JFS_IP(inode)->i_अंतरभूत;
			/*
			 * The अंतरभूत data should be null-terminated, but
			 * करोn't let on-disk corruption crash the kernel
			 */
			inode->i_link[inode->i_size] = '\0';
		पूर्ण
	पूर्ण अन्यथा अणु
		inode->i_op = &jfs_file_inode_operations;
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
	पूर्ण
	unlock_new_inode(inode);
	वापस inode;
पूर्ण

/*
 * Workhorse of both fsync & ग_लिखो_inode
 */
पूर्णांक jfs_commit_inode(काष्ठा inode *inode, पूर्णांक रुको)
अणु
	पूर्णांक rc = 0;
	tid_t tid;
	अटल पूर्णांक noisy = 5;

	jfs_info("In jfs_commit_inode, inode = 0x%p", inode);

	/*
	 * Don't commit अगर inode has been committed since last being
	 * marked dirty, or अगर it has been deleted.
	 */
	अगर (inode->i_nlink == 0 || !test_cflag(COMMIT_Dirty, inode))
		वापस 0;

	अगर (isReadOnly(inode)) अणु
		/* kernel allows ग_लिखोs to devices on पढ़ो-only
		 * partitions and may think inode is dirty
		 */
		अगर (!special_file(inode->i_mode) && noisy) अणु
			jfs_err("jfs_commit_inode(0x%p) called on read-only volume",
				inode);
			jfs_err("Is remount racy?");
			noisy--;
		पूर्ण
		वापस 0;
	पूर्ण

	tid = txBegin(inode->i_sb, COMMIT_INODE);
	mutex_lock(&JFS_IP(inode)->commit_mutex);

	/*
	 * Retest inode state after taking commit_mutex
	 */
	अगर (inode->i_nlink && test_cflag(COMMIT_Dirty, inode))
		rc = txCommit(tid, 1, &inode, रुको ? COMMIT_SYNC : 0);

	txEnd(tid);
	mutex_unlock(&JFS_IP(inode)->commit_mutex);
	वापस rc;
पूर्ण

पूर्णांक jfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक रुको = wbc->sync_mode == WB_SYNC_ALL;

	अगर (inode->i_nlink == 0)
		वापस 0;
	/*
	 * If COMMIT_सूचीTY is not set, the inode isn't really dirty.
	 * It has been committed since the last change, but was still
	 * on the dirty inode list.
	 */
	अगर (!test_cflag(COMMIT_Dirty, inode)) अणु
		/* Make sure committed changes hit the disk */
		jfs_flush_journal(JFS_SBI(inode->i_sb)->log, रुको);
		वापस 0;
	पूर्ण

	अगर (jfs_commit_inode(inode, रुको)) अणु
		jfs_err("jfs_write_inode: jfs_commit_inode failed!");
		वापस -EIO;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

व्योम jfs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा jfs_inode_info *ji = JFS_IP(inode);

	jfs_info("In jfs_evict_inode, inode = 0x%p", inode);

	अगर (!inode->i_nlink && !is_bad_inode(inode)) अणु
		dquot_initialize(inode);

		अगर (JFS_IP(inode)->fileset == खाताSYSTEM_I) अणु
			truncate_inode_pages_final(&inode->i_data);

			अगर (test_cflag(COMMIT_Freewmap, inode))
				jfs_मुक्त_zero_link(inode);

			diFree(inode);

			/*
			 * Free the inode from the quota allocation.
			 */
			dquot_मुक्त_inode(inode);
		पूर्ण
	पूर्ण अन्यथा अणु
		truncate_inode_pages_final(&inode->i_data);
	पूर्ण
	clear_inode(inode);
	dquot_drop(inode);

	BUG_ON(!list_empty(&ji->anon_inode_list));

	spin_lock_irq(&ji->ag_lock);
	अगर (ji->active_ag != -1) अणु
		काष्ठा bmap *bmap = JFS_SBI(inode->i_sb)->bmap;
		atomic_dec(&bmap->db_active[ji->active_ag]);
		ji->active_ag = -1;
	पूर्ण
	spin_unlock_irq(&ji->ag_lock);
पूर्ण

व्योम jfs_dirty_inode(काष्ठा inode *inode, पूर्णांक flags)
अणु
	अटल पूर्णांक noisy = 5;

	अगर (isReadOnly(inode)) अणु
		अगर (!special_file(inode->i_mode) && noisy) अणु
			/* kernel allows ग_लिखोs to devices on पढ़ो-only
			 * partitions and may try to mark inode dirty
			 */
			jfs_err("jfs_dirty_inode called on read-only volume");
			jfs_err("Is remount racy?");
			noisy--;
		पूर्ण
		वापस;
	पूर्ण

	set_cflag(COMMIT_Dirty, inode);
पूर्ण

पूर्णांक jfs_get_block(काष्ठा inode *ip, sector_t lblock,
		  काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	s64 lblock64 = lblock;
	पूर्णांक rc = 0;
	xad_t xad;
	s64 xaddr;
	पूर्णांक xflag;
	s32 xlen = bh_result->b_size >> ip->i_blkbits;

	/*
	 * Take appropriate lock on inode
	 */
	अगर (create)
		IWRITE_LOCK(ip, RDWRLOCK_NORMAL);
	अन्यथा
		IREAD_LOCK(ip, RDWRLOCK_NORMAL);

	अगर (((lblock64 << ip->i_sb->s_blocksize_bits) < ip->i_size) &&
	    (!xtLookup(ip, lblock64, xlen, &xflag, &xaddr, &xlen, 0)) &&
	    xaddr) अणु
		अगर (xflag & XAD_NOTRECORDED) अणु
			अगर (!create)
				/*
				 * Allocated but not recorded, पढ़ो treats
				 * this as a hole
				 */
				जाओ unlock;
#अगर_घोषित _JFS_4K
			XADoffset(&xad, lblock64);
			XADlength(&xad, xlen);
			XADaddress(&xad, xaddr);
#अन्यथा				/* _JFS_4K */
			/*
			 * As दीर्घ as block size = 4K, this isn't a problem.
			 * We should mark the whole page not ABNR, but how
			 * will we know to mark the other blocks BH_New?
			 */
			BUG();
#पूर्ण_अगर				/* _JFS_4K */
			rc = extRecord(ip, &xad);
			अगर (rc)
				जाओ unlock;
			set_buffer_new(bh_result);
		पूर्ण

		map_bh(bh_result, ip->i_sb, xaddr);
		bh_result->b_size = xlen << ip->i_blkbits;
		जाओ unlock;
	पूर्ण
	अगर (!create)
		जाओ unlock;

	/*
	 * Allocate a new block
	 */
#अगर_घोषित _JFS_4K
	अगर ((rc = extHपूर्णांक(ip, lblock64 << ip->i_sb->s_blocksize_bits, &xad)))
		जाओ unlock;
	rc = extAlloc(ip, xlen, lblock64, &xad, false);
	अगर (rc)
		जाओ unlock;

	set_buffer_new(bh_result);
	map_bh(bh_result, ip->i_sb, addressXAD(&xad));
	bh_result->b_size = lengthXAD(&xad) << ip->i_blkbits;

#अन्यथा				/* _JFS_4K */
	/*
	 * We need to करो whatever it takes to keep all but the last buffers
	 * in 4K pages - see jfs_ग_लिखो.c
	 */
	BUG();
#पूर्ण_अगर				/* _JFS_4K */

      unlock:
	/*
	 * Release lock on inode
	 */
	अगर (create)
		IWRITE_UNLOCK(ip);
	अन्यथा
		IREAD_UNLOCK(ip);
	वापस rc;
पूर्ण

अटल पूर्णांक jfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, jfs_get_block, wbc);
पूर्ण

अटल पूर्णांक jfs_ग_लिखोpages(काष्ठा address_space *mapping,
			काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस mpage_ग_लिखोpages(mapping, wbc, jfs_get_block);
पूर्ण

अटल पूर्णांक jfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस mpage_पढ़ोpage(page, jfs_get_block);
पूर्ण

अटल व्योम jfs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, jfs_get_block);
पूर्ण

अटल व्योम jfs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		jfs_truncate(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक jfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित flags,
				काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	ret = nobh_ग_लिखो_begin(mapping, pos, len, flags, pagep, fsdata,
				jfs_get_block);
	अगर (unlikely(ret))
		jfs_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल sector_t jfs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, jfs_get_block);
पूर्ण

अटल sमाप_प्रकार jfs_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = file->f_mapping->host;
	माप_प्रकार count = iov_iter_count(iter);
	sमाप_प्रकार ret;

	ret = blockdev_direct_IO(iocb, inode, iter, jfs_get_block);

	/*
	 * In हाल of error extending ग_लिखो may have instantiated a few
	 * blocks outside i_size. Trim these off again.
	 */
	अगर (unlikely(iov_iter_rw(iter) == WRITE && ret < 0)) अणु
		loff_t isize = i_size_पढ़ो(inode);
		loff_t end = iocb->ki_pos + count;

		अगर (end > isize)
			jfs_ग_लिखो_failed(mapping, end);
	पूर्ण

	वापस ret;
पूर्ण

स्थिर काष्ठा address_space_operations jfs_aops = अणु
	.पढ़ोpage	= jfs_पढ़ोpage,
	.पढ़ोahead	= jfs_पढ़ोahead,
	.ग_लिखोpage	= jfs_ग_लिखोpage,
	.ग_लिखोpages	= jfs_ग_लिखोpages,
	.ग_लिखो_begin	= jfs_ग_लिखो_begin,
	.ग_लिखो_end	= nobh_ग_लिखो_end,
	.bmap		= jfs_bmap,
	.direct_IO	= jfs_direct_IO,
पूर्ण;

/*
 * Guts of jfs_truncate.  Called with locks alपढ़ोy held.  Can be called
 * with directory क्रम truncating directory index table.
 */
व्योम jfs_truncate_nolock(काष्ठा inode *ip, loff_t length)
अणु
	loff_t newsize;
	tid_t tid;

	ASSERT(length >= 0);

	अगर (test_cflag(COMMIT_Nolink, ip)) अणु
		xtTruncate(0, ip, length, COMMIT_WMAP);
		वापस;
	पूर्ण

	करो अणु
		tid = txBegin(ip->i_sb, 0);

		/*
		 * The commit_mutex cannot be taken beक्रमe txBegin.
		 * txBegin may block and there is a chance the inode
		 * could be marked dirty and need to be committed
		 * beक्रमe txBegin unblocks
		 */
		mutex_lock(&JFS_IP(ip)->commit_mutex);

		newsize = xtTruncate(tid, ip, length,
				     COMMIT_TRUNCATE | COMMIT_PWMAP);
		अगर (newsize < 0) अणु
			txEnd(tid);
			mutex_unlock(&JFS_IP(ip)->commit_mutex);
			अवरोध;
		पूर्ण

		ip->i_mसमय = ip->i_स_समय = current_समय(ip);
		mark_inode_dirty(ip);

		txCommit(tid, 1, &ip, 0);
		txEnd(tid);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
	पूर्ण जबतक (newsize > length);	/* Truncate isn't always atomic */
पूर्ण

व्योम jfs_truncate(काष्ठा inode *ip)
अणु
	jfs_info("jfs_truncate: size = 0x%lx", (uदीर्घ) ip->i_size);

	nobh_truncate_page(ip->i_mapping, ip->i_size, jfs_get_block);

	IWRITE_LOCK(ip, RDWRLOCK_NORMAL);
	jfs_truncate_nolock(ip, ip->i_size);
	IWRITE_UNLOCK(ip);
पूर्ण
