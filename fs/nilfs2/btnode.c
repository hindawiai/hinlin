<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * btnode.c - NILFS B-tree node cache
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Originally written by Seiji Kihara.
 * Fully revised by Ryusuke Konishi क्रम stabilization and simplअगरication.
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mm.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/gfp.h>
#समावेश "nilfs.h"
#समावेश "mdt.h"
#समावेश "dat.h"
#समावेश "page.h"
#समावेश "btnode.h"

व्योम nilfs_btnode_cache_clear(काष्ठा address_space *btnc)
अणु
	invalidate_mapping_pages(btnc, 0, -1);
	truncate_inode_pages(btnc, 0);
पूर्ण

काष्ठा buffer_head *
nilfs_btnode_create_block(काष्ठा address_space *btnc, __u64 blocknr)
अणु
	काष्ठा inode *inode = NILFS_BTNC_I(btnc);
	काष्ठा buffer_head *bh;

	bh = nilfs_grab_buffer(inode, btnc, blocknr, BIT(BH_NILFS_Node));
	अगर (unlikely(!bh))
		वापस शून्य;

	अगर (unlikely(buffer_mapped(bh) || buffer_uptodate(bh) ||
		     buffer_dirty(bh))) अणु
		brअन्यथा(bh);
		BUG();
	पूर्ण
	स_रखो(bh->b_data, 0, i_blocksize(inode));
	bh->b_bdev = inode->i_sb->s_bdev;
	bh->b_blocknr = blocknr;
	set_buffer_mapped(bh);
	set_buffer_uptodate(bh);

	unlock_page(bh->b_page);
	put_page(bh->b_page);
	वापस bh;
पूर्ण

पूर्णांक nilfs_btnode_submit_block(काष्ठा address_space *btnc, __u64 blocknr,
			      sector_t pblocknr, पूर्णांक mode, पूर्णांक mode_flags,
			      काष्ठा buffer_head **pbh, sector_t *submit_ptr)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा inode *inode = NILFS_BTNC_I(btnc);
	काष्ठा page *page;
	पूर्णांक err;

	bh = nilfs_grab_buffer(inode, btnc, blocknr, BIT(BH_NILFS_Node));
	अगर (unlikely(!bh))
		वापस -ENOMEM;

	err = -EEXIST; /* पूर्णांकernal code */
	page = bh->b_page;

	अगर (buffer_uptodate(bh) || buffer_dirty(bh))
		जाओ found;

	अगर (pblocknr == 0) अणु
		pblocknr = blocknr;
		अगर (inode->i_ino != NILFS_DAT_INO) अणु
			काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;

			/* blocknr is a भव block number */
			err = nilfs_dat_translate(nilfs->ns_dat, blocknr,
						  &pblocknr);
			अगर (unlikely(err)) अणु
				brअन्यथा(bh);
				जाओ out_locked;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (mode_flags & REQ_RAHEAD) अणु
		अगर (pblocknr != *submit_ptr + 1 || !trylock_buffer(bh)) अणु
			err = -EBUSY; /* पूर्णांकernal code */
			brअन्यथा(bh);
			जाओ out_locked;
		पूर्ण
	पूर्ण अन्यथा अणु /* mode == READ */
		lock_buffer(bh);
	पूर्ण
	अगर (buffer_uptodate(bh)) अणु
		unlock_buffer(bh);
		err = -EEXIST; /* पूर्णांकernal code */
		जाओ found;
	पूर्ण
	set_buffer_mapped(bh);
	bh->b_bdev = inode->i_sb->s_bdev;
	bh->b_blocknr = pblocknr; /* set block address क्रम पढ़ो */
	bh->b_end_io = end_buffer_पढ़ो_sync;
	get_bh(bh);
	submit_bh(mode, mode_flags, bh);
	bh->b_blocknr = blocknr; /* set back to the given block address */
	*submit_ptr = pblocknr;
	err = 0;
found:
	*pbh = bh;

out_locked:
	unlock_page(page);
	put_page(page);
	वापस err;
पूर्ण

/**
 * nilfs_btnode_delete - delete B-tree node buffer
 * @bh: buffer to be deleted
 *
 * nilfs_btnode_delete() invalidates the specअगरied buffer and delete the page
 * including the buffer अगर the page माला_लो unbusy.
 */
व्योम nilfs_btnode_delete(काष्ठा buffer_head *bh)
अणु
	काष्ठा address_space *mapping;
	काष्ठा page *page = bh->b_page;
	pgoff_t index = page_index(page);
	पूर्णांक still_dirty;

	get_page(page);
	lock_page(page);
	रुको_on_page_ग_लिखोback(page);

	nilfs_क्रमget_buffer(bh);
	still_dirty = PageDirty(page);
	mapping = page->mapping;
	unlock_page(page);
	put_page(page);

	अगर (!still_dirty && mapping)
		invalidate_inode_pages2_range(mapping, index, index);
पूर्ण

/**
 * nilfs_btnode_prepare_change_key
 *  prepare to move contents of the block क्रम old key to one of new key.
 *  the old buffer will not be हटाओd, but might be reused क्रम new buffer.
 *  it might वापस -ENOMEM because of memory allocation errors,
 *  and might वापस -EIO because of disk पढ़ो errors.
 */
पूर्णांक nilfs_btnode_prepare_change_key(काष्ठा address_space *btnc,
				    काष्ठा nilfs_btnode_chkey_ctxt *ctxt)
अणु
	काष्ठा buffer_head *obh, *nbh;
	काष्ठा inode *inode = NILFS_BTNC_I(btnc);
	__u64 oldkey = ctxt->oldkey, newkey = ctxt->newkey;
	पूर्णांक err;

	अगर (oldkey == newkey)
		वापस 0;

	obh = ctxt->bh;
	ctxt->newbh = शून्य;

	अगर (inode->i_blkbits == PAGE_SHIFT) अणु
		काष्ठा page *opage = obh->b_page;
		lock_page(opage);
retry:
		/* BUG_ON(oldkey != obh->b_page->index); */
		अगर (unlikely(oldkey != opage->index))
			NILFS_PAGE_BUG(opage,
				       "invalid oldkey %lld (newkey=%lld)",
				       (अचिन्हित दीर्घ दीर्घ)oldkey,
				       (अचिन्हित दीर्घ दीर्घ)newkey);

		xa_lock_irq(&btnc->i_pages);
		err = __xa_insert(&btnc->i_pages, newkey, opage, GFP_NOFS);
		xa_unlock_irq(&btnc->i_pages);
		/*
		 * Note: page->index will not change to newkey until
		 * nilfs_btnode_commit_change_key() will be called.
		 * To protect the page in पूर्णांकermediate state, the page lock
		 * is held.
		 */
		अगर (!err)
			वापस 0;
		अन्यथा अगर (err != -EBUSY)
			जाओ failed_unlock;

		err = invalidate_inode_pages2_range(btnc, newkey, newkey);
		अगर (!err)
			जाओ retry;
		/* fallback to copy mode */
		unlock_page(opage);
	पूर्ण

	nbh = nilfs_btnode_create_block(btnc, newkey);
	अगर (!nbh)
		वापस -ENOMEM;

	BUG_ON(nbh == obh);
	ctxt->newbh = nbh;
	वापस 0;

 failed_unlock:
	unlock_page(obh->b_page);
	वापस err;
पूर्ण

/**
 * nilfs_btnode_commit_change_key
 *  commit the change_key operation prepared by prepare_change_key().
 */
व्योम nilfs_btnode_commit_change_key(काष्ठा address_space *btnc,
				    काष्ठा nilfs_btnode_chkey_ctxt *ctxt)
अणु
	काष्ठा buffer_head *obh = ctxt->bh, *nbh = ctxt->newbh;
	__u64 oldkey = ctxt->oldkey, newkey = ctxt->newkey;
	काष्ठा page *opage;

	अगर (oldkey == newkey)
		वापस;

	अगर (nbh == शून्य) अणु	/* blocksize == pagesize */
		opage = obh->b_page;
		अगर (unlikely(oldkey != opage->index))
			NILFS_PAGE_BUG(opage,
				       "invalid oldkey %lld (newkey=%lld)",
				       (अचिन्हित दीर्घ दीर्घ)oldkey,
				       (अचिन्हित दीर्घ दीर्घ)newkey);
		mark_buffer_dirty(obh);

		xa_lock_irq(&btnc->i_pages);
		__xa_erase(&btnc->i_pages, oldkey);
		__xa_set_mark(&btnc->i_pages, newkey, PAGECACHE_TAG_सूचीTY);
		xa_unlock_irq(&btnc->i_pages);

		opage->index = obh->b_blocknr = newkey;
		unlock_page(opage);
	पूर्ण अन्यथा अणु
		nilfs_copy_buffer(nbh, obh);
		mark_buffer_dirty(nbh);

		nbh->b_blocknr = newkey;
		ctxt->bh = nbh;
		nilfs_btnode_delete(obh); /* will decrement bh->b_count */
	पूर्ण
पूर्ण

/**
 * nilfs_btnode_पात_change_key
 *  पात the change_key operation prepared by prepare_change_key().
 */
व्योम nilfs_btnode_पात_change_key(काष्ठा address_space *btnc,
				   काष्ठा nilfs_btnode_chkey_ctxt *ctxt)
अणु
	काष्ठा buffer_head *nbh = ctxt->newbh;
	__u64 oldkey = ctxt->oldkey, newkey = ctxt->newkey;

	अगर (oldkey == newkey)
		वापस;

	अगर (nbh == शून्य) अणु	/* blocksize == pagesize */
		xa_erase_irq(&btnc->i_pages, newkey);
		unlock_page(ctxt->bh->b_page);
	पूर्ण अन्यथा
		brअन्यथा(nbh);
पूर्ण
