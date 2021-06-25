<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश "reiserfs.h"
#समावेश "acl.h"
#समावेश "xattr.h"
#समावेश <linux/exportfs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mpage.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/swap.h>
#समावेश <linux/uपन.स>
#समावेश <linux/bपन.स>

पूर्णांक reiserfs_commit_ग_लिखो(काष्ठा file *f, काष्ठा page *page,
			  अचिन्हित from, अचिन्हित to);

व्योम reiserfs_evict_inode(काष्ठा inode *inode)
अणु
	/*
	 * We need blocks क्रम transaction + (user+group) quota
	 * update (possibly delete)
	 */
	पूर्णांक jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 2 +
	    2 * REISERFS_QUOTA_INIT_BLOCKS(inode->i_sb);
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक err;

	अगर (!inode->i_nlink && !is_bad_inode(inode))
		dquot_initialize(inode);

	truncate_inode_pages_final(&inode->i_data);
	अगर (inode->i_nlink)
		जाओ no_delete;

	/*
	 * The = 0 happens when we पात creating a new inode
	 * क्रम some reason like lack of space..
	 * also handles bad_inode हाल
	 */
	अगर (!(inode->i_state & I_NEW) && INODE_PKEY(inode)->k_objectid != 0) अणु

		reiserfs_delete_xattrs(inode);

		reiserfs_ग_लिखो_lock(inode->i_sb);

		अगर (journal_begin(&th, inode->i_sb, jbegin_count))
			जाओ out;
		reiserfs_update_inode_transaction(inode);

		reiserfs_discard_pपुनः_स्मृति(&th, inode);

		err = reiserfs_delete_object(&th, inode);

		/*
		 * Do quota update inside a transaction क्रम journaled quotas.
		 * We must करो that after delete_object so that quota updates
		 * go पूर्णांकo the same transaction as stat data deletion
		 */
		अगर (!err) अणु
			पूर्णांक depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
			dquot_मुक्त_inode(inode);
			reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);
		पूर्ण

		अगर (journal_end(&th))
			जाओ out;

		/*
		 * check वापस value from reiserfs_delete_object after
		 * ending the transaction
		 */
		अगर (err)
		    जाओ out;

		/*
		 * all items of file are deleted, so we can हटाओ
		 * "save" link
		 * we can't करो anything about an error here
		 */
		हटाओ_save_link(inode, 0 /* not truncate */);
out:
		reiserfs_ग_लिखो_unlock(inode->i_sb);
	पूर्ण अन्यथा अणु
		/* no object items are in the tree */
		;
	पूर्ण

	/* note this must go after the journal_end to prevent deadlock */
	clear_inode(inode);

	dquot_drop(inode);
	inode->i_blocks = 0;
	वापस;

no_delete:
	clear_inode(inode);
	dquot_drop(inode);
पूर्ण

अटल व्योम _make_cpu_key(काष्ठा cpu_key *key, पूर्णांक version, __u32 dirid,
			  __u32 objectid, loff_t offset, पूर्णांक type, पूर्णांक length)
अणु
	key->version = version;

	key->on_disk_key.k_dir_id = dirid;
	key->on_disk_key.k_objectid = objectid;
	set_cpu_key_k_offset(key, offset);
	set_cpu_key_k_type(key, type);
	key->key_length = length;
पूर्ण

/*
 * take base of inode_key (it comes from inode always) (dirid, objectid)
 * and version from an inode, set offset and type of key
 */
व्योम make_cpu_key(काष्ठा cpu_key *key, काष्ठा inode *inode, loff_t offset,
		  पूर्णांक type, पूर्णांक length)
अणु
	_make_cpu_key(key, get_inode_item_key_version(inode),
		      le32_to_cpu(INODE_PKEY(inode)->k_dir_id),
		      le32_to_cpu(INODE_PKEY(inode)->k_objectid), offset, type,
		      length);
पूर्ण

/* when key is 0, करो not set version and लघु key */
अंतरभूत व्योम make_le_item_head(काष्ठा item_head *ih, स्थिर काष्ठा cpu_key *key,
			      पूर्णांक version,
			      loff_t offset, पूर्णांक type, पूर्णांक length,
			      पूर्णांक entry_count /*or ih_मुक्त_space */ )
अणु
	अगर (key) अणु
		ih->ih_key.k_dir_id = cpu_to_le32(key->on_disk_key.k_dir_id);
		ih->ih_key.k_objectid =
		    cpu_to_le32(key->on_disk_key.k_objectid);
	पूर्ण
	put_ih_version(ih, version);
	set_le_ih_k_offset(ih, offset);
	set_le_ih_k_type(ih, type);
	put_ih_item_len(ih, length);
	/*    set_ih_मुक्त_space (ih, 0); */
	/*
	 * क्रम directory items it is entry count, क्रम directs and stat
	 * datas - 0xffff, क्रम indirects - 0
	 */
	put_ih_entry_count(ih, entry_count);
पूर्ण

/*
 * FIXME: we might cache recently accessed indirect item
 * Ugh.  Not too eager क्रम that....
 * I cut the code until such समय as I see a convincing argument (benchmark).
 * I करोn't want a bloated inode struct..., and I don't like code complनिकासy....
 */

/*
 * cutting the code is fine, since it really isn't in use yet and is easy
 * to add back in.  But, Vladimir has a really good idea here.  Think
 * about what happens क्रम पढ़ोing a file.  For each page,
 * The VFS layer calls reiserfs_पढ़ोpage, who searches the tree to find
 * an indirect item.  This indirect item has X number of poपूर्णांकers, where
 * X is a big number अगर we've करोne the block allocation right.  But,
 * we only use one or two of these poपूर्णांकers during each call to पढ़ोpage,
 * needlessly researching again later on.
 *
 * The size of the cache could be dynamic based on the size of the file.
 *
 * I'd also like to see us cache the location the stat data item, since
 * we are needlessly researching क्रम that frequently.
 *
 * --chris
 */

/*
 * If this page has a file tail in it, and
 * it was पढ़ो in by get_block_create_0, the page data is valid,
 * but tail is still sitting in a direct item, and we can't ग_लिखो to
 * it.  So, look through this page, and check all the mapped buffers
 * to make sure they have valid block numbers.  Any that करोn't need
 * to be unmapped, so that __block_ग_लिखो_begin will correctly call
 * reiserfs_get_block to convert the tail पूर्णांकo an unक्रमmatted node
 */
अटल अंतरभूत व्योम fix_tail_page_क्रम_writing(काष्ठा page *page)
अणु
	काष्ठा buffer_head *head, *next, *bh;

	अगर (page && page_has_buffers(page)) अणु
		head = page_buffers(page);
		bh = head;
		करो अणु
			next = bh->b_this_page;
			अगर (buffer_mapped(bh) && bh->b_blocknr == 0) अणु
				reiserfs_unmap_buffer(bh);
			पूर्ण
			bh = next;
		पूर्ण जबतक (bh != head);
	पूर्ण
पूर्ण

/*
 * reiserfs_get_block करोes not need to allocate a block only अगर it has been
 * करोne alपढ़ोy or non-hole position has been found in the indirect item
 */
अटल अंतरभूत पूर्णांक allocation_needed(पूर्णांक retval, b_blocknr_t allocated,
				    काष्ठा item_head *ih,
				    __le32 * item, पूर्णांक pos_in_item)
अणु
	अगर (allocated)
		वापस 0;
	अगर (retval == POSITION_FOUND && is_indirect_le_ih(ih) &&
	    get_block_num(item, pos_in_item))
		वापस 0;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक indirect_item_found(पूर्णांक retval, काष्ठा item_head *ih)
अणु
	वापस (retval == POSITION_FOUND) && is_indirect_le_ih(ih);
पूर्ण

अटल अंतरभूत व्योम set_block_dev_mapped(काष्ठा buffer_head *bh,
					b_blocknr_t block, काष्ठा inode *inode)
अणु
	map_bh(bh, inode->i_sb, block);
पूर्ण

/*
 * files which were created in the earlier version can not be दीर्घer,
 * than 2 gb
 */
अटल पूर्णांक file_capable(काष्ठा inode *inode, sector_t block)
अणु
	/* it is new file. */
	अगर (get_inode_item_key_version(inode) != KEY_FORMAT_3_5 ||
	    /* old file, but 'block' is inside of 2gb */
	    block < (1 << (31 - inode->i_sb->s_blocksize_bits)))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक restart_transaction(काष्ठा reiserfs_transaction_handle *th,
			       काष्ठा inode *inode, काष्ठा treepath *path)
अणु
	काष्ठा super_block *s = th->t_super;
	पूर्णांक err;

	BUG_ON(!th->t_trans_id);
	BUG_ON(!th->t_refcount);

	pathrअन्यथा(path);

	/* we cannot restart जबतक nested */
	अगर (th->t_refcount > 1) अणु
		वापस 0;
	पूर्ण
	reiserfs_update_sd(th, inode);
	err = journal_end(th);
	अगर (!err) अणु
		err = journal_begin(th, s, JOURNAL_PER_BALANCE_CNT * 6);
		अगर (!err)
			reiserfs_update_inode_transaction(inode);
	पूर्ण
	वापस err;
पूर्ण

/*
 * it is called by get_block when create == 0. Returns block number
 * क्रम 'block'-th logical block of file. When it hits direct item it
 * वापसs 0 (being called from bmap) or पढ़ो direct item पूर्णांकo piece
 * of page (bh_result)
 * Please improve the english/clarity in the comment above, as it is
 * hard to understand.
 */
अटल पूर्णांक _get_block_create_0(काष्ठा inode *inode, sector_t block,
			       काष्ठा buffer_head *bh_result, पूर्णांक args)
अणु
	INITIALIZE_PATH(path);
	काष्ठा cpu_key key;
	काष्ठा buffer_head *bh;
	काष्ठा item_head *ih, पंचांगp_ih;
	b_blocknr_t blocknr;
	अक्षर *p = शून्य;
	पूर्णांक अक्षरs;
	पूर्णांक ret;
	पूर्णांक result;
	पूर्णांक करोne = 0;
	अचिन्हित दीर्घ offset;

	/* prepare the key to look क्रम the 'block'-th block of file */
	make_cpu_key(&key, inode,
		     (loff_t) block * inode->i_sb->s_blocksize + 1, TYPE_ANY,
		     3);

	result = search_क्रम_position_by_key(inode->i_sb, &key, &path);
	अगर (result != POSITION_FOUND) अणु
		pathrअन्यथा(&path);
		अगर (p)
			kunmap(bh_result->b_page);
		अगर (result == IO_ERROR)
			वापस -EIO;
		/*
		 * We करो not वापस -ENOENT अगर there is a hole but page is
		 * uptodate, because it means that there is some MMAPED data
		 * associated with it that is yet to be written to disk.
		 */
		अगर ((args & GET_BLOCK_NO_HOLE)
		    && !PageUptodate(bh_result->b_page)) अणु
			वापस -ENOENT;
		पूर्ण
		वापस 0;
	पूर्ण

	bh = get_last_bh(&path);
	ih = tp_item_head(&path);
	अगर (is_indirect_le_ih(ih)) अणु
		__le32 *ind_item = (__le32 *) ih_item_body(bh, ih);

		/*
		 * FIXME: here we could cache indirect item or part of it in
		 * the inode to aव्योम search_by_key in हाल of subsequent
		 * access to file
		 */
		blocknr = get_block_num(ind_item, path.pos_in_item);
		ret = 0;
		अगर (blocknr) अणु
			map_bh(bh_result, inode->i_sb, blocknr);
			अगर (path.pos_in_item ==
			    ((ih_item_len(ih) / UNFM_P_SIZE) - 1)) अणु
				set_buffer_boundary(bh_result);
			पूर्ण
		पूर्ण अन्यथा
			/*
			 * We करो not वापस -ENOENT अगर there is a hole but
			 * page is uptodate, because it means that there is
			 * some MMAPED data associated with it that is
			 * yet to be written to disk.
			 */
		अगर ((args & GET_BLOCK_NO_HOLE)
			    && !PageUptodate(bh_result->b_page)) अणु
			ret = -ENOENT;
		पूर्ण

		pathrअन्यथा(&path);
		अगर (p)
			kunmap(bh_result->b_page);
		वापस ret;
	पूर्ण
	/* requested data are in direct item(s) */
	अगर (!(args & GET_BLOCK_READ_सूचीECT)) अणु
		/*
		 * we are called by bmap. FIXME: we can not map block of file
		 * when it is stored in direct item(s)
		 */
		pathrअन्यथा(&path);
		अगर (p)
			kunmap(bh_result->b_page);
		वापस -ENOENT;
	पूर्ण

	/*
	 * अगर we've got a direct item, and the buffer or page was uptodate,
	 * we करोn't want to pull data off disk again.  skip to the
	 * end, where we map the buffer and वापस
	 */
	अगर (buffer_uptodate(bh_result)) अणु
		जाओ finished;
	पूर्ण अन्यथा
		/*
		 * grab_tail_page can trigger calls to reiserfs_get_block on
		 * up to date pages without any buffers.  If the page is up
		 * to date, we करोn't want पढ़ो old data off disk.  Set the up
		 * to date bit on the buffer instead and jump to the end
		 */
	अगर (!bh_result->b_page || PageUptodate(bh_result->b_page)) अणु
		set_buffer_uptodate(bh_result);
		जाओ finished;
	पूर्ण
	/* पढ़ो file tail पूर्णांकo part of page */
	offset = (cpu_key_k_offset(&key) - 1) & (PAGE_SIZE - 1);
	copy_item_head(&पंचांगp_ih, ih);

	/*
	 * we only want to kmap अगर we are पढ़ोing the tail पूर्णांकo the page.
	 * this is not the common हाल, so we करोn't kmap until we are
	 * sure we need to.  But, this means the item might move अगर
	 * kmap schedules
	 */
	अगर (!p)
		p = (अक्षर *)kmap(bh_result->b_page);

	p += offset;
	स_रखो(p, 0, inode->i_sb->s_blocksize);
	करो अणु
		अगर (!is_direct_le_ih(ih)) अणु
			BUG();
		पूर्ण
		/*
		 * make sure we करोn't पढ़ो more bytes than actually exist in
		 * the file.  This can happen in odd हालs where i_size isn't
		 * correct, and when direct item padding results in a few
		 * extra bytes at the end of the direct item
		 */
		अगर ((le_ih_k_offset(ih) + path.pos_in_item) > inode->i_size)
			अवरोध;
		अगर ((le_ih_k_offset(ih) - 1 + ih_item_len(ih)) > inode->i_size) अणु
			अक्षरs =
			    inode->i_size - (le_ih_k_offset(ih) - 1) -
			    path.pos_in_item;
			करोne = 1;
		पूर्ण अन्यथा अणु
			अक्षरs = ih_item_len(ih) - path.pos_in_item;
		पूर्ण
		स_नकल(p, ih_item_body(bh, ih) + path.pos_in_item, अक्षरs);

		अगर (करोne)
			अवरोध;

		p += अक्षरs;

		/*
		 * we करोne, अगर पढ़ो direct item is not the last item of
		 * node FIXME: we could try to check right delimiting key
		 * to see whether direct item जारीs in the right
		 * neighbor or rely on i_size
		 */
		अगर (PATH_LAST_POSITION(&path) != (B_NR_ITEMS(bh) - 1))
			अवरोध;

		/* update key to look क्रम the next piece */
		set_cpu_key_k_offset(&key, cpu_key_k_offset(&key) + अक्षरs);
		result = search_क्रम_position_by_key(inode->i_sb, &key, &path);
		अगर (result != POSITION_FOUND)
			/* i/o error most likely */
			अवरोध;
		bh = get_last_bh(&path);
		ih = tp_item_head(&path);
	पूर्ण जबतक (1);

	flush_dcache_page(bh_result->b_page);
	kunmap(bh_result->b_page);

finished:
	pathrअन्यथा(&path);

	अगर (result == IO_ERROR)
		वापस -EIO;

	/*
	 * this buffer has valid data, but isn't valid क्रम io.  mapping it to
	 * block #0 tells the rest of reiserfs it just has a tail in it
	 */
	map_bh(bh_result, inode->i_sb, 0);
	set_buffer_uptodate(bh_result);
	वापस 0;
पूर्ण

/*
 * this is called to create file map. So, _get_block_create_0 will not
 * पढ़ो direct item
 */
अटल पूर्णांक reiserfs_bmap(काष्ठा inode *inode, sector_t block,
			 काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	अगर (!file_capable(inode, block))
		वापस -EFBIG;

	reiserfs_ग_लिखो_lock(inode->i_sb);
	/* करो not पढ़ो the direct item */
	_get_block_create_0(inode, block, bh_result, 0);
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	वापस 0;
पूर्ण

/*
 * special version of get_block that is only used by grab_tail_page right
 * now.  It is sent to __block_ग_लिखो_begin, and when you try to get a
 * block past the end of the file (or a block from a hole) it वापसs
 * -ENOENT instead of a valid buffer.  __block_ग_लिखो_begin expects to
 * be able to करो i/o on the buffers वापसed, unless an error value
 * is also वापसed.
 *
 * So, this allows __block_ग_लिखो_begin to be used क्रम पढ़ोing a single block
 * in a page.  Where it करोes not produce a valid page क्रम holes, or past the
 * end of the file.  This turns out to be exactly what we need क्रम पढ़ोing
 * tails क्रम conversion.
 *
 * The poपूर्णांक of the wrapper is क्रमcing a certain value क्रम create, even
 * though the VFS layer is calling this function with create==1.  If you
 * करोn't want to send create == GET_BLOCK_NO_HOLE to reiserfs_get_block,
 * करोn't use this function.
*/
अटल पूर्णांक reiserfs_get_block_create_0(काष्ठा inode *inode, sector_t block,
				       काष्ठा buffer_head *bh_result,
				       पूर्णांक create)
अणु
	वापस reiserfs_get_block(inode, block, bh_result, GET_BLOCK_NO_HOLE);
पूर्ण

/*
 * This is special helper क्रम reiserfs_get_block in हाल we are executing
 * direct_IO request.
 */
अटल पूर्णांक reiserfs_get_blocks_direct_io(काष्ठा inode *inode,
					 sector_t iblock,
					 काष्ठा buffer_head *bh_result,
					 पूर्णांक create)
अणु
	पूर्णांक ret;

	bh_result->b_page = शून्य;

	/*
	 * We set the b_size beक्रमe reiserfs_get_block call since it is
	 * referenced in convert_tail_क्रम_hole() that may be called from
	 * reiserfs_get_block()
	 */
	bh_result->b_size = i_blocksize(inode);

	ret = reiserfs_get_block(inode, iblock, bh_result,
				 create | GET_BLOCK_NO_DANGLE);
	अगर (ret)
		जाओ out;

	/* करोn't allow direct io onto tail pages */
	अगर (buffer_mapped(bh_result) && bh_result->b_blocknr == 0) अणु
		/*
		 * make sure future calls to the direct io funcs क्रम this
		 * offset in the file fail by unmapping the buffer
		 */
		clear_buffer_mapped(bh_result);
		ret = -EINVAL;
	पूर्ण

	/*
	 * Possible unpacked tail. Flush the data beक्रमe pages have
	 * disappeared
	 */
	अगर (REISERFS_I(inode)->i_flags & i_pack_on_बंद_mask) अणु
		पूर्णांक err;

		reiserfs_ग_लिखो_lock(inode->i_sb);

		err = reiserfs_commit_क्रम_inode(inode);
		REISERFS_I(inode)->i_flags &= ~i_pack_on_बंद_mask;

		reiserfs_ग_लिखो_unlock(inode->i_sb);

		अगर (err < 0)
			ret = err;
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * helper function क्रम when reiserfs_get_block is called क्रम a hole
 * but the file tail is still in a direct item
 * bh_result is the buffer head क्रम the hole
 * tail_offset is the offset of the start of the tail in the file
 *
 * This calls prepare_ग_लिखो, which will start a new transaction
 * you should not be in a transaction, or have any paths held when you
 * call this.
 */
अटल पूर्णांक convert_tail_क्रम_hole(काष्ठा inode *inode,
				 काष्ठा buffer_head *bh_result,
				 loff_t tail_offset)
अणु
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ tail_end;
	अचिन्हित दीर्घ tail_start;
	काष्ठा page *tail_page;
	काष्ठा page *hole_page = bh_result->b_page;
	पूर्णांक retval = 0;

	अगर ((tail_offset & (bh_result->b_size - 1)) != 1)
		वापस -EIO;

	/* always try to पढ़ो until the end of the block */
	tail_start = tail_offset & (PAGE_SIZE - 1);
	tail_end = (tail_start | (bh_result->b_size - 1)) + 1;

	index = tail_offset >> PAGE_SHIFT;
	/*
	 * hole_page can be zero in हाल of direct_io, we are sure
	 * that we cannot get here अगर we ग_लिखो with O_सूचीECT पूर्णांकo tail page
	 */
	अगर (!hole_page || index != hole_page->index) अणु
		tail_page = grab_cache_page(inode->i_mapping, index);
		retval = -ENOMEM;
		अगर (!tail_page) अणु
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		tail_page = hole_page;
	पूर्ण

	/*
	 * we करोn't have to make sure the conversion did not happen जबतक
	 * we were locking the page because anyone that could convert
	 * must first take i_mutex.
	 *
	 * We must fix the tail page क्रम writing because it might have buffers
	 * that are mapped, but have a block number of 0.  This indicates tail
	 * data that has been पढ़ो directly पूर्णांकo the page, and
	 * __block_ग_लिखो_begin won't trigger a get_block in this हाल.
	 */
	fix_tail_page_क्रम_writing(tail_page);
	retval = __reiserfs_ग_लिखो_begin(tail_page, tail_start,
				      tail_end - tail_start);
	अगर (retval)
		जाओ unlock;

	/* tail conversion might change the data in the page */
	flush_dcache_page(tail_page);

	retval = reiserfs_commit_ग_लिखो(शून्य, tail_page, tail_start, tail_end);

unlock:
	अगर (tail_page != hole_page) अणु
		unlock_page(tail_page);
		put_page(tail_page);
	पूर्ण
out:
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक _allocate_block(काष्ठा reiserfs_transaction_handle *th,
				  sector_t block,
				  काष्ठा inode *inode,
				  b_blocknr_t * allocated_block_nr,
				  काष्ठा treepath *path, पूर्णांक flags)
अणु
	BUG_ON(!th->t_trans_id);

#अगर_घोषित REISERFS_PREALLOCATE
	अगर (!(flags & GET_BLOCK_NO_IMUX)) अणु
		वापस reiserfs_new_unf_blocknrs2(th, inode, allocated_block_nr,
						  path, block);
	पूर्ण
#पूर्ण_अगर
	वापस reiserfs_new_unf_blocknrs(th, inode, allocated_block_nr, path,
					 block);
पूर्ण

पूर्णांक reiserfs_get_block(काष्ठा inode *inode, sector_t block,
		       काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक repeat, retval = 0;
	/* b_blocknr_t is (अचिन्हित) 32 bit पूर्णांक*/
	b_blocknr_t allocated_block_nr = 0;
	INITIALIZE_PATH(path);
	पूर्णांक pos_in_item;
	काष्ठा cpu_key key;
	काष्ठा buffer_head *bh, *unbh = शून्य;
	काष्ठा item_head *ih, पंचांगp_ih;
	__le32 *item;
	पूर्णांक करोne;
	पूर्णांक fs_gen;
	काष्ठा reiserfs_transaction_handle *th = शून्य;
	/*
	 * space reserved in transaction batch:
	 * . 3 balancings in direct->indirect conversion
	 * . 1 block involved पूर्णांकo reiserfs_update_sd()
	 * XXX in practically impossible worst हाल direct2indirect()
	 * can incur (much) more than 3 balancings.
	 * quota update क्रम user, group
	 */
	पूर्णांक jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 + 1 +
	    2 * REISERFS_QUOTA_TRANS_BLOCKS(inode->i_sb);
	पूर्णांक version;
	पूर्णांक dangle = 1;
	loff_t new_offset =
	    (((loff_t) block) << inode->i_sb->s_blocksize_bits) + 1;

	reiserfs_ग_लिखो_lock(inode->i_sb);
	version = get_inode_item_key_version(inode);

	अगर (!file_capable(inode, block)) अणु
		reiserfs_ग_लिखो_unlock(inode->i_sb);
		वापस -EFBIG;
	पूर्ण

	/*
	 * अगर !create, we aren't changing the FS, so we don't need to
	 * log anything, so we करोn't need to start a transaction
	 */
	अगर (!(create & GET_BLOCK_CREATE)) अणु
		पूर्णांक ret;
		/* find number of block-th logical block of the file */
		ret = _get_block_create_0(inode, block, bh_result,
					  create | GET_BLOCK_READ_सूचीECT);
		reiserfs_ग_लिखो_unlock(inode->i_sb);
		वापस ret;
	पूर्ण

	/*
	 * अगर we're alपढ़ोy in a transaction, make sure to बंद
	 * any new transactions we start in this func
	 */
	अगर ((create & GET_BLOCK_NO_DANGLE) ||
	    reiserfs_transaction_running(inode->i_sb))
		dangle = 0;

	/*
	 * If file is of such a size, that it might have a tail and
	 * tails are enabled  we should mark it as possibly needing
	 * tail packing on बंद
	 */
	अगर ((have_large_tails(inode->i_sb)
	     && inode->i_size < i_block_size(inode) * 4)
	    || (have_small_tails(inode->i_sb)
		&& inode->i_size < i_block_size(inode)))
		REISERFS_I(inode)->i_flags |= i_pack_on_बंद_mask;

	/* set the key of the first byte in the 'block'-th block of file */
	make_cpu_key(&key, inode, new_offset, TYPE_ANY, 3 /*key length */ );
	अगर ((new_offset + inode->i_sb->s_blocksize - 1) > inode->i_size) अणु
start_trans:
		th = reiserfs_persistent_transaction(inode->i_sb, jbegin_count);
		अगर (!th) अणु
			retval = -ENOMEM;
			जाओ failure;
		पूर्ण
		reiserfs_update_inode_transaction(inode);
	पूर्ण
research:

	retval = search_क्रम_position_by_key(inode->i_sb, &key, &path);
	अगर (retval == IO_ERROR) अणु
		retval = -EIO;
		जाओ failure;
	पूर्ण

	bh = get_last_bh(&path);
	ih = tp_item_head(&path);
	item = tp_item_body(&path);
	pos_in_item = path.pos_in_item;

	fs_gen = get_generation(inode->i_sb);
	copy_item_head(&पंचांगp_ih, ih);

	अगर (allocation_needed
	    (retval, allocated_block_nr, ih, item, pos_in_item)) अणु
		/* we have to allocate block क्रम the unक्रमmatted node */
		अगर (!th) अणु
			pathrअन्यथा(&path);
			जाओ start_trans;
		पूर्ण

		repeat =
		    _allocate_block(th, block, inode, &allocated_block_nr,
				    &path, create);

		/*
		 * restart the transaction to give the journal a chance to मुक्त
		 * some blocks.  releases the path, so we have to go back to
		 * research अगर we succeed on the second try
		 */
		अगर (repeat == NO_DISK_SPACE || repeat == QUOTA_EXCEEDED) अणु
			SB_JOURNAL(inode->i_sb)->j_next_async_flush = 1;
			retval = restart_transaction(th, inode, &path);
			अगर (retval)
				जाओ failure;
			repeat =
			    _allocate_block(th, block, inode,
					    &allocated_block_nr, शून्य, create);

			अगर (repeat != NO_DISK_SPACE && repeat != QUOTA_EXCEEDED) अणु
				जाओ research;
			पूर्ण
			अगर (repeat == QUOTA_EXCEEDED)
				retval = -EDQUOT;
			अन्यथा
				retval = -ENOSPC;
			जाओ failure;
		पूर्ण

		अगर (fs_changed(fs_gen, inode->i_sb)
		    && item_moved(&पंचांगp_ih, &path)) अणु
			जाओ research;
		पूर्ण
	पूर्ण

	अगर (indirect_item_found(retval, ih)) अणु
		b_blocknr_t unfm_ptr;
		/*
		 * 'block'-th block is in the file alपढ़ोy (there is
		 * corresponding cell in some indirect item). But it may be
		 * zero unक्रमmatted node poपूर्णांकer (hole)
		 */
		unfm_ptr = get_block_num(item, pos_in_item);
		अगर (unfm_ptr == 0) अणु
			/* use allocated block to plug the hole */
			reiserfs_prepare_क्रम_journal(inode->i_sb, bh, 1);
			अगर (fs_changed(fs_gen, inode->i_sb)
			    && item_moved(&पंचांगp_ih, &path)) अणु
				reiserfs_restore_prepared_buffer(inode->i_sb,
								 bh);
				जाओ research;
			पूर्ण
			set_buffer_new(bh_result);
			अगर (buffer_dirty(bh_result)
			    && reiserfs_data_ordered(inode->i_sb))
				reiserfs_add_ordered_list(inode, bh_result);
			put_block_num(item, pos_in_item, allocated_block_nr);
			unfm_ptr = allocated_block_nr;
			journal_mark_dirty(th, bh);
			reiserfs_update_sd(th, inode);
		पूर्ण
		set_block_dev_mapped(bh_result, unfm_ptr, inode);
		pathrअन्यथा(&path);
		retval = 0;
		अगर (!dangle && th)
			retval = reiserfs_end_persistent_transaction(th);

		reiserfs_ग_लिखो_unlock(inode->i_sb);

		/*
		 * the item was found, so new blocks were not added to the file
		 * there is no need to make sure the inode is updated with this
		 * transaction
		 */
		वापस retval;
	पूर्ण

	अगर (!th) अणु
		pathrअन्यथा(&path);
		जाओ start_trans;
	पूर्ण

	/*
	 * desired position is not found or is in the direct item. We have
	 * to append file with holes up to 'block'-th block converting
	 * direct items to indirect one अगर necessary
	 */
	करोne = 0;
	करो अणु
		अगर (is_statdata_le_ih(ih)) अणु
			__le32 unp = 0;
			काष्ठा cpu_key पंचांगp_key;

			/* indirect item has to be inserted */
			make_le_item_head(&पंचांगp_ih, &key, version, 1,
					  TYPE_INसूचीECT, UNFM_P_SIZE,
					  0 /* मुक्त_space */ );

			/*
			 * we are going to add 'block'-th block to the file.
			 * Use allocated block क्रम that
			 */
			अगर (cpu_key_k_offset(&key) == 1) अणु
				unp = cpu_to_le32(allocated_block_nr);
				set_block_dev_mapped(bh_result,
						     allocated_block_nr, inode);
				set_buffer_new(bh_result);
				करोne = 1;
			पूर्ण
			पंचांगp_key = key;	/* ;) */
			set_cpu_key_k_offset(&पंचांगp_key, 1);
			PATH_LAST_POSITION(&path)++;

			retval =
			    reiserfs_insert_item(th, &path, &पंचांगp_key, &पंचांगp_ih,
						 inode, (अक्षर *)&unp);
			अगर (retval) अणु
				reiserfs_मुक्त_block(th, inode,
						    allocated_block_nr, 1);
				/*
				 * retval == -ENOSPC, -EDQUOT or -EIO
				 * or -EEXIST
				 */
				जाओ failure;
			पूर्ण
		पूर्ण अन्यथा अगर (is_direct_le_ih(ih)) अणु
			/* direct item has to be converted */
			loff_t tail_offset;

			tail_offset =
			    ((le_ih_k_offset(ih) -
			      1) & ~(inode->i_sb->s_blocksize - 1)) + 1;

			/*
			 * direct item we just found fits पूर्णांकo block we have
			 * to map. Convert it पूर्णांकo unक्रमmatted node: use
			 * bh_result क्रम the conversion
			 */
			अगर (tail_offset == cpu_key_k_offset(&key)) अणु
				set_block_dev_mapped(bh_result,
						     allocated_block_nr, inode);
				unbh = bh_result;
				करोne = 1;
			पूर्ण अन्यथा अणु
				/*
				 * we have to pad file tail stored in direct
				 * item(s) up to block size and convert it
				 * to unक्रमmatted node. FIXME: this should
				 * also get पूर्णांकo page cache
				 */

				pathrअन्यथा(&path);
				/*
				 * ugly, but we can only end the transaction अगर
				 * we aren't nested
				 */
				BUG_ON(!th->t_refcount);
				अगर (th->t_refcount == 1) अणु
					retval =
					    reiserfs_end_persistent_transaction
					    (th);
					th = शून्य;
					अगर (retval)
						जाओ failure;
				पूर्ण

				retval =
				    convert_tail_क्रम_hole(inode, bh_result,
							  tail_offset);
				अगर (retval) अणु
					अगर (retval != -ENOSPC)
						reiserfs_error(inode->i_sb,
							"clm-6004",
							"convert tail failed "
							"inode %lu, error %d",
							inode->i_ino,
							retval);
					अगर (allocated_block_nr) अणु
						/*
						 * the biपंचांगap, the super,
						 * and the stat data == 3
						 */
						अगर (!th)
							th = reiserfs_persistent_transaction(inode->i_sb, 3);
						अगर (th)
							reiserfs_मुक्त_block(th,
									    inode,
									    allocated_block_nr,
									    1);
					पूर्ण
					जाओ failure;
				पूर्ण
				जाओ research;
			पूर्ण
			retval =
			    direct2indirect(th, inode, &path, unbh,
					    tail_offset);
			अगर (retval) अणु
				reiserfs_unmap_buffer(unbh);
				reiserfs_मुक्त_block(th, inode,
						    allocated_block_nr, 1);
				जाओ failure;
			पूर्ण
			/*
			 * it is important the set_buffer_uptodate is करोne
			 * after the direct2indirect.  The buffer might
			 * contain valid data newer than the data on disk
			 * (पढ़ो by पढ़ोpage, changed, and then sent here by
			 * ग_लिखोpage).  direct2indirect needs to know अगर unbh
			 * was alपढ़ोy up to date, so it can decide अगर the
			 * data in unbh needs to be replaced with data from
			 * the disk
			 */
			set_buffer_uptodate(unbh);

			/*
			 * unbh->b_page == शून्य in हाल of सूचीECT_IO request,
			 * this means buffer will disappear लघुly, so it
			 * should not be added to
			 */
			अगर (unbh->b_page) अणु
				/*
				 * we've converted the tail, so we must
				 * flush unbh beक्रमe the transaction commits
				 */
				reiserfs_add_tail_list(inode, unbh);

				/*
				 * mark it dirty now to prevent commit_ग_लिखो
				 * from adding this buffer to the inode's
				 * dirty buffer list
				 */
				/*
				 * AKPM: changed __mark_buffer_dirty to
				 * mark_buffer_dirty().  It's still atomic,
				 * but it sets the page dirty too, which makes
				 * it eligible क्रम ग_लिखोback at any समय by the
				 * VM (which was also the हाल with
				 * __mark_buffer_dirty())
				 */
				mark_buffer_dirty(unbh);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * append indirect item with holes अगर needed, when
			 * appending poपूर्णांकer to 'block'-th block use block,
			 * which is alपढ़ोy allocated
			 */
			काष्ठा cpu_key पंचांगp_key;
			/*
			 * We use this in हाल we need to allocate
			 * only one block which is a fastpath
			 */
			unp_t unf_single = 0;
			unp_t *un;
			__u64 max_to_insert =
			    MAX_ITEM_LEN(inode->i_sb->s_blocksize) /
			    UNFM_P_SIZE;
			__u64 blocks_needed;

			RFALSE(pos_in_item != ih_item_len(ih) / UNFM_P_SIZE,
			       "vs-804: invalid position for append");
			/*
			 * indirect item has to be appended,
			 * set up key of that position
			 * (key type is unimportant)
			 */
			make_cpu_key(&पंचांगp_key, inode,
				     le_key_k_offset(version,
						     &ih->ih_key) +
				     op_bytes_number(ih,
						     inode->i_sb->s_blocksize),
				     TYPE_INसूचीECT, 3);

			RFALSE(cpu_key_k_offset(&पंचांगp_key) > cpu_key_k_offset(&key),
			       "green-805: invalid offset");
			blocks_needed =
			    1 +
			    ((cpu_key_k_offset(&key) -
			      cpu_key_k_offset(&पंचांगp_key)) >> inode->i_sb->
			     s_blocksize_bits);

			अगर (blocks_needed == 1) अणु
				un = &unf_single;
			पूर्ण अन्यथा अणु
				un = kसुस्मृति(min(blocks_needed, max_to_insert),
					     UNFM_P_SIZE, GFP_NOFS);
				अगर (!un) अणु
					un = &unf_single;
					blocks_needed = 1;
					max_to_insert = 0;
				पूर्ण
			पूर्ण
			अगर (blocks_needed <= max_to_insert) अणु
				/*
				 * we are going to add target block to
				 * the file. Use allocated block क्रम that
				 */
				un[blocks_needed - 1] =
				    cpu_to_le32(allocated_block_nr);
				set_block_dev_mapped(bh_result,
						     allocated_block_nr, inode);
				set_buffer_new(bh_result);
				करोne = 1;
			पूर्ण अन्यथा अणु
				/* paste hole to the indirect item */
				/*
				 * If kसुस्मृति failed, max_to_insert becomes
				 * zero and it means we only have space क्रम
				 * one block
				 */
				blocks_needed =
				    max_to_insert ? max_to_insert : 1;
			पूर्ण
			retval =
			    reiserfs_paste_पूर्णांकo_item(th, &path, &पंचांगp_key, inode,
						     (अक्षर *)un,
						     UNFM_P_SIZE *
						     blocks_needed);

			अगर (blocks_needed != 1)
				kमुक्त(un);

			अगर (retval) अणु
				reiserfs_मुक्त_block(th, inode,
						    allocated_block_nr, 1);
				जाओ failure;
			पूर्ण
			अगर (!करोne) अणु
				/*
				 * We need to mark new file size in हाल
				 * this function will be पूर्णांकerrupted/पातed
				 * later on. And we may करो this only क्रम
				 * holes.
				 */
				inode->i_size +=
				    inode->i_sb->s_blocksize * blocks_needed;
			पूर्ण
		पूर्ण

		अगर (करोne == 1)
			अवरोध;

		/*
		 * this loop could log more blocks than we had originally
		 * asked क्रम.  So, we have to allow the transaction to end
		 * अगर it is too big or too full.  Update the inode so things
		 * are consistent अगर we crash beक्रमe the function वापसs
		 * release the path so that anybody रुकोing on the path beक्रमe
		 * ending their transaction will be able to जारी.
		 */
		अगर (journal_transaction_should_end(th, th->t_blocks_allocated)) अणु
			retval = restart_transaction(th, inode, &path);
			अगर (retval)
				जाओ failure;
		पूर्ण
		/*
		 * inserting indirect poपूर्णांकers क्रम a hole can take a
		 * दीर्घ समय.  reschedule अगर needed and also release the ग_लिखो
		 * lock क्रम others.
		 */
		reiserfs_cond_resched(inode->i_sb);

		retval = search_क्रम_position_by_key(inode->i_sb, &key, &path);
		अगर (retval == IO_ERROR) अणु
			retval = -EIO;
			जाओ failure;
		पूर्ण
		अगर (retval == POSITION_FOUND) अणु
			reiserfs_warning(inode->i_sb, "vs-825",
					 "%K should not be found", &key);
			retval = -EEXIST;
			अगर (allocated_block_nr)
				reiserfs_मुक्त_block(th, inode,
						    allocated_block_nr, 1);
			pathrअन्यथा(&path);
			जाओ failure;
		पूर्ण
		bh = get_last_bh(&path);
		ih = tp_item_head(&path);
		item = tp_item_body(&path);
		pos_in_item = path.pos_in_item;
	पूर्ण जबतक (1);

	retval = 0;

failure:
	अगर (th && (!dangle || (retval && !th->t_trans_id))) अणु
		पूर्णांक err;
		अगर (th->t_trans_id)
			reiserfs_update_sd(th, inode);
		err = reiserfs_end_persistent_transaction(th);
		अगर (err)
			retval = err;
	पूर्ण

	reiserfs_ग_लिखो_unlock(inode->i_sb);
	reiserfs_check_path(&path);
	वापस retval;
पूर्ण

अटल व्योम reiserfs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, reiserfs_get_block);
पूर्ण

/*
 * Compute real number of used bytes by file
 * Following three functions can go away when we'll have enough space in
 * stat item
 */
अटल पूर्णांक real_space_dअगरf(काष्ठा inode *inode, पूर्णांक sd_size)
अणु
	पूर्णांक bytes;
	loff_t blocksize = inode->i_sb->s_blocksize;

	अगर (S_ISLNK(inode->i_mode) || S_ISसूची(inode->i_mode))
		वापस sd_size;

	/*
	 * End of file is also in full block with indirect reference, so round
	 * up to the next block.
	 *
	 * there is just no way to know अगर the tail is actually packed
	 * on the file, so we have to assume it isn't.  When we pack the
	 * tail, we add 4 bytes to pretend there really is an unक्रमmatted
	 * node poपूर्णांकer
	 */
	bytes =
	    ((inode->i_size +
	      (blocksize - 1)) >> inode->i_sb->s_blocksize_bits) * UNFM_P_SIZE +
	    sd_size;
	वापस bytes;
पूर्ण

अटल अंतरभूत loff_t to_real_used_space(काष्ठा inode *inode, uदीर्घ blocks,
					पूर्णांक sd_size)
अणु
	अगर (S_ISLNK(inode->i_mode) || S_ISसूची(inode->i_mode)) अणु
		वापस inode->i_size +
		    (loff_t) (real_space_dअगरf(inode, sd_size));
	पूर्ण
	वापस ((loff_t) real_space_dअगरf(inode, sd_size)) +
	    (((loff_t) blocks) << 9);
पूर्ण

/* Compute number of blocks used by file in ReiserFS counting */
अटल अंतरभूत uदीर्घ to_fake_used_blocks(काष्ठा inode *inode, पूर्णांक sd_size)
अणु
	loff_t bytes = inode_get_bytes(inode);
	loff_t real_space = real_space_dअगरf(inode, sd_size);

	/* keeps fsck and non-quota versions of reiserfs happy */
	अगर (S_ISLNK(inode->i_mode) || S_ISसूची(inode->i_mode)) अणु
		bytes += (loff_t) 511;
	पूर्ण

	/*
	 * files from beक्रमe the quota patch might i_blocks such that
	 * bytes < real_space.  Deal with that here to prevent it from
	 * going negative.
	 */
	अगर (bytes < real_space)
		वापस 0;
	वापस (bytes - real_space) >> 9;
पूर्ण

/*
 * BAD: new directories have stat data of new type and all other items
 * of old type. Version stored in the inode says about body items, so
 * in update_stat_data we can not rely on inode, but have to check
 * item version directly
 */

/* called by पढ़ो_locked_inode */
अटल व्योम init_inode(काष्ठा inode *inode, काष्ठा treepath *path)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा item_head *ih;
	__u32 rdev;

	bh = PATH_PLAST_BUFFER(path);
	ih = tp_item_head(path);

	copy_key(INODE_PKEY(inode), &ih->ih_key);

	INIT_LIST_HEAD(&REISERFS_I(inode)->i_pपुनः_स्मृति_list);
	REISERFS_I(inode)->i_flags = 0;
	REISERFS_I(inode)->i_pपुनः_स्मृति_block = 0;
	REISERFS_I(inode)->i_pपुनः_स्मृति_count = 0;
	REISERFS_I(inode)->i_trans_id = 0;
	REISERFS_I(inode)->i_jl = शून्य;
	reiserfs_init_xattr_rwsem(inode);

	अगर (stat_data_v1(ih)) अणु
		काष्ठा stat_data_v1 *sd =
		    (काष्ठा stat_data_v1 *)ih_item_body(bh, ih);
		अचिन्हित दीर्घ blocks;

		set_inode_item_key_version(inode, KEY_FORMAT_3_5);
		set_inode_sd_version(inode, STAT_DATA_V1);
		inode->i_mode = sd_v1_mode(sd);
		set_nlink(inode, sd_v1_nlink(sd));
		i_uid_ग_लिखो(inode, sd_v1_uid(sd));
		i_gid_ग_लिखो(inode, sd_v1_gid(sd));
		inode->i_size = sd_v1_size(sd);
		inode->i_aसमय.tv_sec = sd_v1_aसमय(sd);
		inode->i_mसमय.tv_sec = sd_v1_mसमय(sd);
		inode->i_स_समय.tv_sec = sd_v1_स_समय(sd);
		inode->i_aसमय.tv_nsec = 0;
		inode->i_स_समय.tv_nsec = 0;
		inode->i_mसमय.tv_nsec = 0;

		inode->i_blocks = sd_v1_blocks(sd);
		inode->i_generation = le32_to_cpu(INODE_PKEY(inode)->k_dir_id);
		blocks = (inode->i_size + 511) >> 9;
		blocks = _ROUND_UP(blocks, inode->i_sb->s_blocksize >> 9);

		/*
		 * there was a bug in <=3.5.23 when i_blocks could take
		 * negative values. Starting from 3.5.17 this value could
		 * even be stored in stat data. For such files we set
		 * i_blocks based on file size. Just 2 notes: this can be
		 * wrong क्रम sparse files. On-disk value will be only
		 * updated अगर file's inode will ever change
		 */
		अगर (inode->i_blocks > blocks) अणु
			inode->i_blocks = blocks;
		पूर्ण

		rdev = sd_v1_rdev(sd);
		REISERFS_I(inode)->i_first_direct_byte =
		    sd_v1_first_direct_byte(sd);

		/*
		 * an early bug in the quota code can give us an odd
		 * number क्रम the block count.  This is incorrect, fix it here.
		 */
		अगर (inode->i_blocks & 1) अणु
			inode->i_blocks++;
		पूर्ण
		inode_set_bytes(inode,
				to_real_used_space(inode, inode->i_blocks,
						   SD_V1_SIZE));
		/*
		 * nopack is initially zero क्रम v1 objects. For v2 objects,
		 * nopack is initialised from sd_attrs
		 */
		REISERFS_I(inode)->i_flags &= ~i_nopack_mask;
	पूर्ण अन्यथा अणु
		/*
		 * new stat data found, but object may have old items
		 * (directories and symlinks)
		 */
		काष्ठा stat_data *sd = (काष्ठा stat_data *)ih_item_body(bh, ih);

		inode->i_mode = sd_v2_mode(sd);
		set_nlink(inode, sd_v2_nlink(sd));
		i_uid_ग_लिखो(inode, sd_v2_uid(sd));
		inode->i_size = sd_v2_size(sd);
		i_gid_ग_लिखो(inode, sd_v2_gid(sd));
		inode->i_mसमय.tv_sec = sd_v2_mसमय(sd);
		inode->i_aसमय.tv_sec = sd_v2_aसमय(sd);
		inode->i_स_समय.tv_sec = sd_v2_स_समय(sd);
		inode->i_स_समय.tv_nsec = 0;
		inode->i_mसमय.tv_nsec = 0;
		inode->i_aसमय.tv_nsec = 0;
		inode->i_blocks = sd_v2_blocks(sd);
		rdev = sd_v2_rdev(sd);
		अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
			inode->i_generation =
			    le32_to_cpu(INODE_PKEY(inode)->k_dir_id);
		अन्यथा
			inode->i_generation = sd_v2_generation(sd);

		अगर (S_ISसूची(inode->i_mode) || S_ISLNK(inode->i_mode))
			set_inode_item_key_version(inode, KEY_FORMAT_3_5);
		अन्यथा
			set_inode_item_key_version(inode, KEY_FORMAT_3_6);
		REISERFS_I(inode)->i_first_direct_byte = 0;
		set_inode_sd_version(inode, STAT_DATA_V2);
		inode_set_bytes(inode,
				to_real_used_space(inode, inode->i_blocks,
						   SD_V2_SIZE));
		/*
		 * पढ़ो persistent inode attributes from sd and initialise
		 * generic inode flags from them
		 */
		REISERFS_I(inode)->i_attrs = sd_v2_attrs(sd);
		sd_attrs_to_i_attrs(sd_v2_attrs(sd), inode);
	पूर्ण

	pathrअन्यथा(path);
	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op = &reiserfs_file_inode_operations;
		inode->i_fop = &reiserfs_file_operations;
		inode->i_mapping->a_ops = &reiserfs_address_space_operations;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &reiserfs_dir_inode_operations;
		inode->i_fop = &reiserfs_dir_operations;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_op = &reiserfs_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &reiserfs_address_space_operations;
	पूर्ण अन्यथा अणु
		inode->i_blocks = 0;
		inode->i_op = &reiserfs_special_inode_operations;
		init_special_inode(inode, inode->i_mode, new_decode_dev(rdev));
	पूर्ण
पूर्ण

/* update new stat data with inode fields */
अटल व्योम inode2sd(व्योम *sd, काष्ठा inode *inode, loff_t size)
अणु
	काष्ठा stat_data *sd_v2 = (काष्ठा stat_data *)sd;

	set_sd_v2_mode(sd_v2, inode->i_mode);
	set_sd_v2_nlink(sd_v2, inode->i_nlink);
	set_sd_v2_uid(sd_v2, i_uid_पढ़ो(inode));
	set_sd_v2_size(sd_v2, size);
	set_sd_v2_gid(sd_v2, i_gid_पढ़ो(inode));
	set_sd_v2_mसमय(sd_v2, inode->i_mसमय.tv_sec);
	set_sd_v2_aसमय(sd_v2, inode->i_aसमय.tv_sec);
	set_sd_v2_स_समय(sd_v2, inode->i_स_समय.tv_sec);
	set_sd_v2_blocks(sd_v2, to_fake_used_blocks(inode, SD_V2_SIZE));
	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		set_sd_v2_rdev(sd_v2, new_encode_dev(inode->i_rdev));
	अन्यथा
		set_sd_v2_generation(sd_v2, inode->i_generation);
	set_sd_v2_attrs(sd_v2, REISERFS_I(inode)->i_attrs);
पूर्ण

/* used to copy inode's fields to old stat data */
अटल व्योम inode2sd_v1(व्योम *sd, काष्ठा inode *inode, loff_t size)
अणु
	काष्ठा stat_data_v1 *sd_v1 = (काष्ठा stat_data_v1 *)sd;

	set_sd_v1_mode(sd_v1, inode->i_mode);
	set_sd_v1_uid(sd_v1, i_uid_पढ़ो(inode));
	set_sd_v1_gid(sd_v1, i_gid_पढ़ो(inode));
	set_sd_v1_nlink(sd_v1, inode->i_nlink);
	set_sd_v1_size(sd_v1, size);
	set_sd_v1_aसमय(sd_v1, inode->i_aसमय.tv_sec);
	set_sd_v1_स_समय(sd_v1, inode->i_स_समय.tv_sec);
	set_sd_v1_mसमय(sd_v1, inode->i_mसमय.tv_sec);

	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		set_sd_v1_rdev(sd_v1, new_encode_dev(inode->i_rdev));
	अन्यथा
		set_sd_v1_blocks(sd_v1, to_fake_used_blocks(inode, SD_V1_SIZE));

	/* Sigh. i_first_direct_byte is back */
	set_sd_v1_first_direct_byte(sd_v1,
				    REISERFS_I(inode)->i_first_direct_byte);
पूर्ण

/*
 * NOTE, you must prepare the buffer head beक्रमe sending it here,
 * and then log it after the call
 */
अटल व्योम update_stat_data(काष्ठा treepath *path, काष्ठा inode *inode,
			     loff_t size)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा item_head *ih;

	bh = PATH_PLAST_BUFFER(path);
	ih = tp_item_head(path);

	अगर (!is_statdata_le_ih(ih))
		reiserfs_panic(inode->i_sb, "vs-13065", "key %k, found item %h",
			       INODE_PKEY(inode), ih);

	/* path poपूर्णांकs to old stat data */
	अगर (stat_data_v1(ih)) अणु
		inode2sd_v1(ih_item_body(bh, ih), inode, size);
	पूर्ण अन्यथा अणु
		inode2sd(ih_item_body(bh, ih), inode, size);
	पूर्ण

	वापस;
पूर्ण

व्योम reiserfs_update_sd_size(काष्ठा reiserfs_transaction_handle *th,
			     काष्ठा inode *inode, loff_t size)
अणु
	काष्ठा cpu_key key;
	INITIALIZE_PATH(path);
	काष्ठा buffer_head *bh;
	पूर्णांक fs_gen;
	काष्ठा item_head *ih, पंचांगp_ih;
	पूर्णांक retval;

	BUG_ON(!th->t_trans_id);

	/* key type is unimportant */
	make_cpu_key(&key, inode, SD_OFFSET, TYPE_STAT_DATA, 3);

	क्रम (;;) अणु
		पूर्णांक pos;
		/* look क्रम the object's stat data */
		retval = search_item(inode->i_sb, &key, &path);
		अगर (retval == IO_ERROR) अणु
			reiserfs_error(inode->i_sb, "vs-13050",
				       "i/o failure occurred trying to "
				       "update %K stat data", &key);
			वापस;
		पूर्ण
		अगर (retval == ITEM_NOT_FOUND) अणु
			pos = PATH_LAST_POSITION(&path);
			pathrअन्यथा(&path);
			अगर (inode->i_nlink == 0) अणु
				/*reiserfs_warning (inode->i_sb, "vs-13050: reiserfs_update_sd: i_nlink == 0, stat data not found"); */
				वापस;
			पूर्ण
			reiserfs_warning(inode->i_sb, "vs-13060",
					 "stat data of object %k (nlink == %d) "
					 "not found (pos %d)",
					 INODE_PKEY(inode), inode->i_nlink,
					 pos);
			reiserfs_check_path(&path);
			वापस;
		पूर्ण

		/*
		 * sigh, prepare_क्रम_journal might schedule.  When it
		 * schedules the FS might change.  We have to detect that,
		 * and loop back to the search अगर the stat data item has moved
		 */
		bh = get_last_bh(&path);
		ih = tp_item_head(&path);
		copy_item_head(&पंचांगp_ih, ih);
		fs_gen = get_generation(inode->i_sb);
		reiserfs_prepare_क्रम_journal(inode->i_sb, bh, 1);

		/* Stat_data item has been moved after scheduling. */
		अगर (fs_changed(fs_gen, inode->i_sb)
		    && item_moved(&पंचांगp_ih, &path)) अणु
			reiserfs_restore_prepared_buffer(inode->i_sb, bh);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	update_stat_data(&path, inode, size);
	journal_mark_dirty(th, bh);
	pathrअन्यथा(&path);
	वापस;
पूर्ण

/*
 * reiserfs_पढ़ो_locked_inode is called to पढ़ो the inode off disk, and it
 * करोes a make_bad_inode when things go wrong.  But, we need to make sure
 * and clear the key in the निजी portion of the inode, otherwise a
 * corresponding iput might try to delete whatever object the inode last
 * represented.
 */
अटल व्योम reiserfs_make_bad_inode(काष्ठा inode *inode)
अणु
	स_रखो(INODE_PKEY(inode), 0, KEY_SIZE);
	make_bad_inode(inode);
पूर्ण

/*
 * initially this function was derived from minix or ext2's analog and
 * evolved as the prototype did
 */
पूर्णांक reiserfs_init_locked_inode(काष्ठा inode *inode, व्योम *p)
अणु
	काष्ठा reiserfs_iget_args *args = (काष्ठा reiserfs_iget_args *)p;
	inode->i_ino = args->objectid;
	INODE_PKEY(inode)->k_dir_id = cpu_to_le32(args->dirid);
	वापस 0;
पूर्ण

/*
 * looks क्रम stat data in the tree, and fills up the fields of in-core
 * inode stat data fields
 */
व्योम reiserfs_पढ़ो_locked_inode(काष्ठा inode *inode,
				काष्ठा reiserfs_iget_args *args)
अणु
	INITIALIZE_PATH(path_to_sd);
	काष्ठा cpu_key key;
	अचिन्हित दीर्घ dirino;
	पूर्णांक retval;

	dirino = args->dirid;

	/*
	 * set version 1, version 2 could be used too, because stat data
	 * key is the same in both versions
	 */
	_make_cpu_key(&key, KEY_FORMAT_3_5, dirino, inode->i_ino, 0, 0, 3);

	/* look क्रम the object's stat data */
	retval = search_item(inode->i_sb, &key, &path_to_sd);
	अगर (retval == IO_ERROR) अणु
		reiserfs_error(inode->i_sb, "vs-13070",
			       "i/o failure occurred trying to find "
			       "stat data of %K", &key);
		reiserfs_make_bad_inode(inode);
		वापस;
	पूर्ण

	/* a stale NFS handle can trigger this without it being an error */
	अगर (retval != ITEM_FOUND) अणु
		pathrअन्यथा(&path_to_sd);
		reiserfs_make_bad_inode(inode);
		clear_nlink(inode);
		वापस;
	पूर्ण

	init_inode(inode, &path_to_sd);

	/*
	 * It is possible that knfsd is trying to access inode of a file
	 * that is being हटाओd from the disk by some other thपढ़ो. As we
	 * update sd on unlink all that is required is to check क्रम nlink
	 * here. This bug was first found by Sizअगर when debugging
	 * SquidNG/Butterfly, क्रमgotten, and found again after Philippe
	 * Gramoulle <philippe.gramoulle@mmania.com> reproduced it.

	 * More logical fix would require changes in fs/inode.c:iput() to
	 * हटाओ inode from hash-table _after_ fs cleaned disk stuff up and
	 * in iget() to वापस शून्य अगर I_FREEING inode is found in
	 * hash-table.
	 */

	/*
	 * Currently there is one place where it's ok to meet inode with
	 * nlink==0: processing of खोलो-unlinked and half-truncated files
	 * during mount (fs/reiserfs/super.c:finish_unfinished()).
	 */
	अगर ((inode->i_nlink == 0) &&
	    !REISERFS_SB(inode->i_sb)->s_is_unlinked_ok) अणु
		reiserfs_warning(inode->i_sb, "vs-13075",
				 "dead inode read from disk %K. "
				 "This is likely to be race with knfsd. Ignore",
				 &key);
		reiserfs_make_bad_inode(inode);
	पूर्ण

	/* init inode should be relsing */
	reiserfs_check_path(&path_to_sd);

	/*
	 * Stat data v1 करोesn't support ACLs.
	 */
	अगर (get_inode_sd_version(inode) == STAT_DATA_V1)
		cache_no_acl(inode);
पूर्ण

/*
 * reiserfs_find_actor() - "find actor" reiserfs supplies to iget5_locked().
 *
 * @inode:    inode from hash table to check
 * @opaque:   "cookie" passed to iget5_locked(). This is &reiserfs_iget_args.
 *
 * This function is called by iget5_locked() to distinguish reiserfs inodes
 * having the same inode numbers. Such inodes can only exist due to some
 * error condition. One of them should be bad. Inodes with identical
 * inode numbers (objectids) are distinguished by parent directory ids.
 *
 */
पूर्णांक reiserfs_find_actor(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा reiserfs_iget_args *args;

	args = opaque;
	/* args is alपढ़ोy in CPU order */
	वापस (inode->i_ino == args->objectid) &&
	    (le32_to_cpu(INODE_PKEY(inode)->k_dir_id) == args->dirid);
पूर्ण

काष्ठा inode *reiserfs_iget(काष्ठा super_block *s, स्थिर काष्ठा cpu_key *key)
अणु
	काष्ठा inode *inode;
	काष्ठा reiserfs_iget_args args;
	पूर्णांक depth;

	args.objectid = key->on_disk_key.k_objectid;
	args.dirid = key->on_disk_key.k_dir_id;
	depth = reiserfs_ग_लिखो_unlock_nested(s);
	inode = iget5_locked(s, key->on_disk_key.k_objectid,
			     reiserfs_find_actor, reiserfs_init_locked_inode,
			     (व्योम *)(&args));
	reiserfs_ग_लिखो_lock_nested(s, depth);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	अगर (inode->i_state & I_NEW) अणु
		reiserfs_पढ़ो_locked_inode(inode, &args);
		unlock_new_inode(inode);
	पूर्ण

	अगर (comp_लघु_keys(INODE_PKEY(inode), key) || is_bad_inode(inode)) अणु
		/* either due to i/o error or a stale NFS handle */
		iput(inode);
		inode = शून्य;
	पूर्ण
	वापस inode;
पूर्ण

अटल काष्ठा dentry *reiserfs_get_dentry(काष्ठा super_block *sb,
	u32 objectid, u32 dir_id, u32 generation)

अणु
	काष्ठा cpu_key key;
	काष्ठा inode *inode;

	key.on_disk_key.k_objectid = objectid;
	key.on_disk_key.k_dir_id = dir_id;
	reiserfs_ग_लिखो_lock(sb);
	inode = reiserfs_iget(sb, &key);
	अगर (inode && !IS_ERR(inode) && generation != 0 &&
	    generation != inode->i_generation) अणु
		iput(inode);
		inode = शून्य;
	पूर्ण
	reiserfs_ग_लिखो_unlock(sb);

	वापस d_obtain_alias(inode);
पूर्ण

काष्ठा dentry *reiserfs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	/*
	 * fhtype happens to reflect the number of u32s encoded.
	 * due to a bug in earlier code, fhtype might indicate there
	 * are more u32s then actually fitted.
	 * so अगर fhtype seems to be more than len, reduce fhtype.
	 * Valid types are:
	 *   2 - objectid + dir_id - legacy support
	 *   3 - objectid + dir_id + generation
	 *   4 - objectid + dir_id + objectid and dirid of parent - legacy
	 *   5 - objectid + dir_id + generation + objectid and dirid of parent
	 *   6 - as above plus generation of directory
	 * 6 करोes not fit in NFSv2 handles
	 */
	अगर (fh_type > fh_len) अणु
		अगर (fh_type != 6 || fh_len != 5)
			reiserfs_warning(sb, "reiserfs-13077",
				"nfsd/reiserfs, fhtype=%d, len=%d - odd",
				fh_type, fh_len);
		fh_type = fh_len;
	पूर्ण
	अगर (fh_len < 2)
		वापस शून्य;

	वापस reiserfs_get_dentry(sb, fid->raw[0], fid->raw[1],
		(fh_type == 3 || fh_type >= 5) ? fid->raw[2] : 0);
पूर्ण

काष्ठा dentry *reiserfs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	अगर (fh_type > fh_len)
		fh_type = fh_len;
	अगर (fh_type < 4)
		वापस शून्य;

	वापस reiserfs_get_dentry(sb,
		(fh_type >= 5) ? fid->raw[3] : fid->raw[2],
		(fh_type >= 5) ? fid->raw[4] : fid->raw[3],
		(fh_type == 6) ? fid->raw[5] : 0);
पूर्ण

पूर्णांक reiserfs_encode_fh(काष्ठा inode *inode, __u32 * data, पूर्णांक *lenp,
		       काष्ठा inode *parent)
अणु
	पूर्णांक maxlen = *lenp;

	अगर (parent && (maxlen < 5)) अणु
		*lenp = 5;
		वापस खाताID_INVALID;
	पूर्ण अन्यथा अगर (maxlen < 3) अणु
		*lenp = 3;
		वापस खाताID_INVALID;
	पूर्ण

	data[0] = inode->i_ino;
	data[1] = le32_to_cpu(INODE_PKEY(inode)->k_dir_id);
	data[2] = inode->i_generation;
	*lenp = 3;
	अगर (parent) अणु
		data[3] = parent->i_ino;
		data[4] = le32_to_cpu(INODE_PKEY(parent)->k_dir_id);
		*lenp = 5;
		अगर (maxlen >= 6) अणु
			data[5] = parent->i_generation;
			*lenp = 6;
		पूर्ण
	पूर्ण
	वापस *lenp;
पूर्ण

/*
 * looks क्रम stat data, then copies fields to it, marks the buffer
 * containing stat data as dirty
 */
/*
 * reiserfs inodes are never really dirty, since the dirty inode call
 * always logs them.  This call allows the VFS inode marking routines
 * to properly mark inodes क्रम datasync and such, but only actually
 * करोes something when called क्रम a synchronous update.
 */
पूर्णांक reiserfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक jbegin_count = 1;

	अगर (sb_rकरोnly(inode->i_sb))
		वापस -EROFS;
	/*
	 * memory pressure can someबार initiate ग_लिखो_inode calls with
	 * sync == 1,
	 * these हालs are just when the प्रणाली needs ram, not when the
	 * inode needs to reach disk क्रम safety, and they can safely be
	 * ignored because the altered inode has alपढ़ोy been logged.
	 */
	अगर (wbc->sync_mode == WB_SYNC_ALL && !(current->flags & PF_MEMALLOC)) अणु
		reiserfs_ग_लिखो_lock(inode->i_sb);
		अगर (!journal_begin(&th, inode->i_sb, jbegin_count)) अणु
			reiserfs_update_sd(&th, inode);
			journal_end_sync(&th);
		पूर्ण
		reiserfs_ग_लिखो_unlock(inode->i_sb);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * stat data of new object is inserted alपढ़ोy, this inserts the item
 * containing "." and ".." entries
 */
अटल पूर्णांक reiserfs_new_directory(काष्ठा reiserfs_transaction_handle *th,
				  काष्ठा inode *inode,
				  काष्ठा item_head *ih, काष्ठा treepath *path,
				  काष्ठा inode *dir)
अणु
	काष्ठा super_block *sb = th->t_super;
	अक्षर empty_dir[EMPTY_सूची_SIZE];
	अक्षर *body = empty_dir;
	काष्ठा cpu_key key;
	पूर्णांक retval;

	BUG_ON(!th->t_trans_id);

	_make_cpu_key(&key, KEY_FORMAT_3_5, le32_to_cpu(ih->ih_key.k_dir_id),
		      le32_to_cpu(ih->ih_key.k_objectid), DOT_OFFSET,
		      TYPE_सूचीENTRY, 3 /*key length */ );

	/*
	 * compose item head क्रम new item. Directories consist of items of
	 * old type (ITEM_VERSION_1). Do not set key (second arg is 0), it
	 * is करोne by reiserfs_new_inode
	 */
	अगर (old_क्रमmat_only(sb)) अणु
		make_le_item_head(ih, शून्य, KEY_FORMAT_3_5, DOT_OFFSET,
				  TYPE_सूचीENTRY, EMPTY_सूची_SIZE_V1, 2);

		make_empty_dir_item_v1(body, ih->ih_key.k_dir_id,
				       ih->ih_key.k_objectid,
				       INODE_PKEY(dir)->k_dir_id,
				       INODE_PKEY(dir)->k_objectid);
	पूर्ण अन्यथा अणु
		make_le_item_head(ih, शून्य, KEY_FORMAT_3_5, DOT_OFFSET,
				  TYPE_सूचीENTRY, EMPTY_सूची_SIZE, 2);

		make_empty_dir_item(body, ih->ih_key.k_dir_id,
				    ih->ih_key.k_objectid,
				    INODE_PKEY(dir)->k_dir_id,
				    INODE_PKEY(dir)->k_objectid);
	पूर्ण

	/* look क्रम place in the tree क्रम new item */
	retval = search_item(sb, &key, path);
	अगर (retval == IO_ERROR) अणु
		reiserfs_error(sb, "vs-13080",
			       "i/o failure occurred creating new directory");
		वापस -EIO;
	पूर्ण
	अगर (retval == ITEM_FOUND) अणु
		pathrअन्यथा(path);
		reiserfs_warning(sb, "vs-13070",
				 "object with this key exists (%k)",
				 &(ih->ih_key));
		वापस -EEXIST;
	पूर्ण

	/* insert item, that is empty directory item */
	वापस reiserfs_insert_item(th, path, &key, ih, inode, body);
पूर्ण

/*
 * stat data of object has been inserted, this inserts the item
 * containing the body of symlink
 */
अटल पूर्णांक reiserfs_new_symlink(काष्ठा reiserfs_transaction_handle *th,
				काष्ठा inode *inode,
				काष्ठा item_head *ih,
				काष्ठा treepath *path, स्थिर अक्षर *symname,
				पूर्णांक item_len)
अणु
	काष्ठा super_block *sb = th->t_super;
	काष्ठा cpu_key key;
	पूर्णांक retval;

	BUG_ON(!th->t_trans_id);

	_make_cpu_key(&key, KEY_FORMAT_3_5,
		      le32_to_cpu(ih->ih_key.k_dir_id),
		      le32_to_cpu(ih->ih_key.k_objectid),
		      1, TYPE_सूचीECT, 3 /*key length */ );

	make_le_item_head(ih, शून्य, KEY_FORMAT_3_5, 1, TYPE_सूचीECT, item_len,
			  0 /*मुक्त_space */ );

	/* look क्रम place in the tree क्रम new item */
	retval = search_item(sb, &key, path);
	अगर (retval == IO_ERROR) अणु
		reiserfs_error(sb, "vs-13080",
			       "i/o failure occurred creating new symlink");
		वापस -EIO;
	पूर्ण
	अगर (retval == ITEM_FOUND) अणु
		pathrअन्यथा(path);
		reiserfs_warning(sb, "vs-13080",
				 "object with this key exists (%k)",
				 &(ih->ih_key));
		वापस -EEXIST;
	पूर्ण

	/* insert item, that is body of symlink */
	वापस reiserfs_insert_item(th, path, &key, ih, inode, symname);
पूर्ण

/*
 * inserts the stat data पूर्णांकo the tree, and then calls
 * reiserfs_new_directory (to insert ".", ".." item अगर new object is
 * directory) or reiserfs_new_symlink (to insert symlink body अगर new
 * object is symlink) or nothing (अगर new object is regular file)

 * NOTE! uid and gid must alपढ़ोy be set in the inode.  If we वापस
 * non-zero due to an error, we have to drop the quota previously allocated
 * क्रम the fresh inode.  This can only be करोne outside a transaction, so
 * अगर we वापस non-zero, we also end the transaction.
 *
 * @th: active transaction handle
 * @dir: parent directory क्रम new inode
 * @mode: mode of new inode
 * @symname: symlink contents अगर inode is symlink
 * @isize: 0 क्रम regular file, EMPTY_सूची_SIZE क्रम dirs, म_माप(symname) क्रम
 *         symlinks
 * @inode: inode to be filled
 * @security: optional security context to associate with this inode
 */
पूर्णांक reiserfs_new_inode(काष्ठा reiserfs_transaction_handle *th,
		       काष्ठा inode *dir, umode_t mode, स्थिर अक्षर *symname,
		       /* 0 क्रम regular, EMTRY_सूची_SIZE क्रम dirs,
		          म_माप (symname) क्रम symlinks) */
		       loff_t i_size, काष्ठा dentry *dentry,
		       काष्ठा inode *inode,
		       काष्ठा reiserfs_security_handle *security)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा reiserfs_iget_args args;
	INITIALIZE_PATH(path_to_key);
	काष्ठा cpu_key key;
	काष्ठा item_head ih;
	काष्ठा stat_data sd;
	पूर्णांक retval;
	पूर्णांक err;
	पूर्णांक depth;

	BUG_ON(!th->t_trans_id);

	depth = reiserfs_ग_लिखो_unlock_nested(sb);
	err = dquot_alloc_inode(inode);
	reiserfs_ग_लिखो_lock_nested(sb, depth);
	अगर (err)
		जाओ out_end_trans;
	अगर (!dir->i_nlink) अणु
		err = -EPERM;
		जाओ out_bad_inode;
	पूर्ण

	/* item head of new item */
	ih.ih_key.k_dir_id = reiserfs_choose_packing(dir);
	ih.ih_key.k_objectid = cpu_to_le32(reiserfs_get_unused_objectid(th));
	अगर (!ih.ih_key.k_objectid) अणु
		err = -ENOMEM;
		जाओ out_bad_inode;
	पूर्ण
	args.objectid = inode->i_ino = le32_to_cpu(ih.ih_key.k_objectid);
	अगर (old_क्रमmat_only(sb))
		make_le_item_head(&ih, शून्य, KEY_FORMAT_3_5, SD_OFFSET,
				  TYPE_STAT_DATA, SD_V1_SIZE, MAX_US_INT);
	अन्यथा
		make_le_item_head(&ih, शून्य, KEY_FORMAT_3_6, SD_OFFSET,
				  TYPE_STAT_DATA, SD_SIZE, MAX_US_INT);
	स_नकल(INODE_PKEY(inode), &ih.ih_key, KEY_SIZE);
	args.dirid = le32_to_cpu(ih.ih_key.k_dir_id);

	depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
	err = insert_inode_locked4(inode, args.objectid,
			     reiserfs_find_actor, &args);
	reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);
	अगर (err) अणु
		err = -EINVAL;
		जाओ out_bad_inode;
	पूर्ण

	अगर (old_क्रमmat_only(sb))
		/*
		 * not a perfect generation count, as object ids can be reused,
		 * but this is as good as reiserfs can करो right now.
		 * note that the निजी part of inode isn't filled in yet,
		 * we have to use the directory.
		 */
		inode->i_generation = le32_to_cpu(INODE_PKEY(dir)->k_objectid);
	अन्यथा
#अगर defined( USE_INODE_GENERATION_COUNTER )
		inode->i_generation =
		    le32_to_cpu(REISERFS_SB(sb)->s_rs->s_inode_generation);
#अन्यथा
		inode->i_generation = ++event;
#पूर्ण_अगर

	/* fill stat data */
	set_nlink(inode, (S_ISसूची(mode) ? 2 : 1));

	/* uid and gid must alपढ़ोy be set by the caller क्रम quota init */

	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	inode->i_size = i_size;
	inode->i_blocks = 0;
	inode->i_bytes = 0;
	REISERFS_I(inode)->i_first_direct_byte = S_ISLNK(mode) ? 1 :
	    U32_MAX /*NO_BYTES_IN_सूचीECT_ITEM */ ;

	INIT_LIST_HEAD(&REISERFS_I(inode)->i_pपुनः_स्मृति_list);
	REISERFS_I(inode)->i_flags = 0;
	REISERFS_I(inode)->i_pपुनः_स्मृति_block = 0;
	REISERFS_I(inode)->i_pपुनः_स्मृति_count = 0;
	REISERFS_I(inode)->i_trans_id = 0;
	REISERFS_I(inode)->i_jl = शून्य;
	REISERFS_I(inode)->i_attrs =
	    REISERFS_I(dir)->i_attrs & REISERFS_INHERIT_MASK;
	sd_attrs_to_i_attrs(REISERFS_I(inode)->i_attrs, inode);
	reiserfs_init_xattr_rwsem(inode);

	/* key to search क्रम correct place क्रम new stat data */
	_make_cpu_key(&key, KEY_FORMAT_3_6, le32_to_cpu(ih.ih_key.k_dir_id),
		      le32_to_cpu(ih.ih_key.k_objectid), SD_OFFSET,
		      TYPE_STAT_DATA, 3 /*key length */ );

	/* find proper place क्रम inserting of stat data */
	retval = search_item(sb, &key, &path_to_key);
	अगर (retval == IO_ERROR) अणु
		err = -EIO;
		जाओ out_bad_inode;
	पूर्ण
	अगर (retval == ITEM_FOUND) अणु
		pathrअन्यथा(&path_to_key);
		err = -EEXIST;
		जाओ out_bad_inode;
	पूर्ण
	अगर (old_क्रमmat_only(sb)) अणु
		/* i_uid or i_gid is too big to be stored in stat data v3.5 */
		अगर (i_uid_पढ़ो(inode) & ~0xffff || i_gid_पढ़ो(inode) & ~0xffff) अणु
			pathrअन्यथा(&path_to_key);
			err = -EINVAL;
			जाओ out_bad_inode;
		पूर्ण
		inode2sd_v1(&sd, inode, inode->i_size);
	पूर्ण अन्यथा अणु
		inode2sd(&sd, inode, inode->i_size);
	पूर्ण
	/*
	 * store in in-core inode the key of stat data and version all
	 * object items will have (directory items will have old offset
	 * क्रमmat, other new objects will consist of new items)
	 */
	अगर (old_क्रमmat_only(sb) || S_ISसूची(mode) || S_ISLNK(mode))
		set_inode_item_key_version(inode, KEY_FORMAT_3_5);
	अन्यथा
		set_inode_item_key_version(inode, KEY_FORMAT_3_6);
	अगर (old_क्रमmat_only(sb))
		set_inode_sd_version(inode, STAT_DATA_V1);
	अन्यथा
		set_inode_sd_version(inode, STAT_DATA_V2);

	/* insert the stat data पूर्णांकo the tree */
#अगर_घोषित DISPLACE_NEW_PACKING_LOCALITIES
	अगर (REISERFS_I(dir)->new_packing_locality)
		th->displace_new_blocks = 1;
#पूर्ण_अगर
	retval =
	    reiserfs_insert_item(th, &path_to_key, &key, &ih, inode,
				 (अक्षर *)(&sd));
	अगर (retval) अणु
		err = retval;
		reiserfs_check_path(&path_to_key);
		जाओ out_bad_inode;
	पूर्ण
#अगर_घोषित DISPLACE_NEW_PACKING_LOCALITIES
	अगर (!th->displace_new_blocks)
		REISERFS_I(dir)->new_packing_locality = 0;
#पूर्ण_अगर
	अगर (S_ISसूची(mode)) अणु
		/* insert item with "." and ".." */
		retval =
		    reiserfs_new_directory(th, inode, &ih, &path_to_key, dir);
	पूर्ण

	अगर (S_ISLNK(mode)) अणु
		/* insert body of symlink */
		अगर (!old_क्रमmat_only(sb))
			i_size = ROUND_UP(i_size);
		retval =
		    reiserfs_new_symlink(th, inode, &ih, &path_to_key, symname,
					 i_size);
	पूर्ण
	अगर (retval) अणु
		err = retval;
		reiserfs_check_path(&path_to_key);
		journal_end(th);
		जाओ out_inserted_sd;
	पूर्ण

	/*
	 * Mark it निजी अगर we're creating the privroot
	 * or something under it.
	 */
	अगर (IS_PRIVATE(dir) || dentry == REISERFS_SB(sb)->priv_root) अणु
		inode->i_flags |= S_PRIVATE;
		inode->i_opflags &= ~IOP_XATTR;
	पूर्ण

	अगर (reiserfs_posixacl(inode->i_sb)) अणु
		reiserfs_ग_लिखो_unlock(inode->i_sb);
		retval = reiserfs_inherit_शेष_acl(th, dir, dentry, inode);
		reiserfs_ग_लिखो_lock(inode->i_sb);
		अगर (retval) अणु
			err = retval;
			reiserfs_check_path(&path_to_key);
			journal_end(th);
			जाओ out_inserted_sd;
		पूर्ण
	पूर्ण अन्यथा अगर (inode->i_sb->s_flags & SB_POSIXACL) अणु
		reiserfs_warning(inode->i_sb, "jdm-13090",
				 "ACLs aren't enabled in the fs, "
				 "but vfs thinks they are!");
	पूर्ण

	अगर (security->name) अणु
		reiserfs_ग_लिखो_unlock(inode->i_sb);
		retval = reiserfs_security_ग_लिखो(th, inode, security);
		reiserfs_ग_लिखो_lock(inode->i_sb);
		अगर (retval) अणु
			err = retval;
			reiserfs_check_path(&path_to_key);
			retval = journal_end(th);
			अगर (retval)
				err = retval;
			जाओ out_inserted_sd;
		पूर्ण
	पूर्ण

	reiserfs_update_sd(th, inode);
	reiserfs_check_path(&path_to_key);

	वापस 0;

out_bad_inode:
	/* Invalidate the object, nothing was inserted yet */
	INODE_PKEY(inode)->k_objectid = 0;

	/* Quota change must be inside a transaction क्रम journaling */
	depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
	dquot_मुक्त_inode(inode);
	reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);

out_end_trans:
	journal_end(th);
	/*
	 * Drop can be outside and it needs more credits so it's better
	 * to have it outside
	 */
	depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
	dquot_drop(inode);
	reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);
	inode->i_flags |= S_NOQUOTA;
	make_bad_inode(inode);

out_inserted_sd:
	clear_nlink(inode);
	th->t_trans_id = 0;	/* so the caller can't use this handle later */
	अगर (inode->i_state & I_NEW)
		unlock_new_inode(inode);
	iput(inode);
	वापस err;
पूर्ण

/*
 * finds the tail page in the page cache,
 * पढ़ोs the last block in.
 *
 * On success, page_result is set to a locked, pinned page, and bh_result
 * is set to an up to date buffer क्रम the last block in the file.  वापसs 0.
 *
 * tail conversion is not करोne, so bh_result might not be valid क्रम writing
 * check buffer_mapped(bh_result) and bh_result->b_blocknr != 0 beक्रमe
 * trying to ग_लिखो the block.
 *
 * on failure, nonzero is वापसed, page_result and bh_result are untouched.
 */
अटल पूर्णांक grab_tail_page(काष्ठा inode *inode,
			  काष्ठा page **page_result,
			  काष्ठा buffer_head **bh_result)
अणु

	/*
	 * we want the page with the last byte in the file,
	 * not the page that will hold the next byte क्रम appending
	 */
	अचिन्हित दीर्घ index = (inode->i_size - 1) >> PAGE_SHIFT;
	अचिन्हित दीर्घ pos = 0;
	अचिन्हित दीर्घ start = 0;
	अचिन्हित दीर्घ blocksize = inode->i_sb->s_blocksize;
	अचिन्हित दीर्घ offset = (inode->i_size) & (PAGE_SIZE - 1);
	काष्ठा buffer_head *bh;
	काष्ठा buffer_head *head;
	काष्ठा page *page;
	पूर्णांक error;

	/*
	 * we know that we are only called with inode->i_size > 0.
	 * we also know that a file tail can never be as big as a block
	 * If i_size % blocksize == 0, our file is currently block aligned
	 * and it won't need converting or zeroing after a truncate.
	 */
	अगर ((offset & (blocksize - 1)) == 0) अणु
		वापस -ENOENT;
	पूर्ण
	page = grab_cache_page(inode->i_mapping, index);
	error = -ENOMEM;
	अगर (!page) अणु
		जाओ out;
	पूर्ण
	/* start within the page of the last block in the file */
	start = (offset / blocksize) * blocksize;

	error = __block_ग_लिखो_begin(page, start, offset - start,
				    reiserfs_get_block_create_0);
	अगर (error)
		जाओ unlock;

	head = page_buffers(page);
	bh = head;
	करो अणु
		अगर (pos >= start) अणु
			अवरोध;
		पूर्ण
		bh = bh->b_this_page;
		pos += blocksize;
	पूर्ण जबतक (bh != head);

	अगर (!buffer_uptodate(bh)) अणु
		/*
		 * note, this should never happen, prepare_ग_लिखो should be
		 * taking care of this क्रम us.  If the buffer isn't up to
		 * date, I've screwed up the code to find the buffer, or the
		 * code to call prepare_ग_लिखो
		 */
		reiserfs_error(inode->i_sb, "clm-6000",
			       "error reading block %lu", bh->b_blocknr);
		error = -EIO;
		जाओ unlock;
	पूर्ण
	*bh_result = bh;
	*page_result = page;

out:
	वापस error;

unlock:
	unlock_page(page);
	put_page(page);
	वापस error;
पूर्ण

/*
 * vfs version of truncate file.  Must NOT be called with
 * a transaction alपढ़ोy started.
 *
 * some code taken from block_truncate_page
 */
पूर्णांक reiserfs_truncate_file(काष्ठा inode *inode, पूर्णांक update_बारtamps)
अणु
	काष्ठा reiserfs_transaction_handle th;
	/* we want the offset क्रम the first byte after the end of the file */
	अचिन्हित दीर्घ offset = inode->i_size & (PAGE_SIZE - 1);
	अचिन्हित blocksize = inode->i_sb->s_blocksize;
	अचिन्हित length;
	काष्ठा page *page = शून्य;
	पूर्णांक error;
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक err2;

	reiserfs_ग_लिखो_lock(inode->i_sb);

	अगर (inode->i_size > 0) अणु
		error = grab_tail_page(inode, &page, &bh);
		अगर (error) अणु
			/*
			 * -ENOENT means we truncated past the end of the
			 * file, and get_block_create_0 could not find a
			 * block to पढ़ो in, which is ok.
			 */
			अगर (error != -ENOENT)
				reiserfs_error(inode->i_sb, "clm-6001",
					       "grab_tail_page failed %d",
					       error);
			page = शून्य;
			bh = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * so, अगर page != शून्य, we have a buffer head क्रम the offset at
	 * the end of the file. अगर the bh is mapped, and bh->b_blocknr != 0,
	 * then we have an unक्रमmatted node.  Otherwise, we have a direct item,
	 * and no zeroing is required on disk.  We zero after the truncate,
	 * because the truncate might pack the item anyway
	 * (it will unmap bh अगर it packs).
	 *
	 * it is enough to reserve space in transaction क्रम 2 balancings:
	 * one क्रम "save" link adding and another क्रम the first
	 * cut_from_item. 1 is क्रम update_sd
	 */
	error = journal_begin(&th, inode->i_sb,
			      JOURNAL_PER_BALANCE_CNT * 2 + 1);
	अगर (error)
		जाओ out;
	reiserfs_update_inode_transaction(inode);
	अगर (update_बारtamps)
		/*
		 * we are करोing real truncate: अगर the प्रणाली crashes
		 * beक्रमe the last transaction of truncating माला_लो committed
		 * - on reboot the file either appears truncated properly
		 * or not truncated at all
		 */
		add_save_link(&th, inode, 1);
	err2 = reiserfs_करो_truncate(&th, inode, page, update_बारtamps);
	error = journal_end(&th);
	अगर (error)
		जाओ out;

	/* check reiserfs_करो_truncate after ending the transaction */
	अगर (err2) अणु
		error = err2;
  		जाओ out;
	पूर्ण
	
	अगर (update_बारtamps) अणु
		error = हटाओ_save_link(inode, 1 /* truncate */);
		अगर (error)
			जाओ out;
	पूर्ण

	अगर (page) अणु
		length = offset & (blocksize - 1);
		/* अगर we are not on a block boundary */
		अगर (length) अणु
			length = blocksize - length;
			zero_user(page, offset, length);
			अगर (buffer_mapped(bh) && bh->b_blocknr != 0) अणु
				mark_buffer_dirty(bh);
			पूर्ण
		पूर्ण
		unlock_page(page);
		put_page(page);
	पूर्ण

	reiserfs_ग_लिखो_unlock(inode->i_sb);

	वापस 0;
out:
	अगर (page) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण

	reiserfs_ग_लिखो_unlock(inode->i_sb);

	वापस error;
पूर्ण

अटल पूर्णांक map_block_क्रम_ग_लिखोpage(काष्ठा inode *inode,
				   काष्ठा buffer_head *bh_result,
				   अचिन्हित दीर्घ block)
अणु
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक fs_gen;
	काष्ठा item_head पंचांगp_ih;
	काष्ठा item_head *ih;
	काष्ठा buffer_head *bh;
	__le32 *item;
	काष्ठा cpu_key key;
	INITIALIZE_PATH(path);
	पूर्णांक pos_in_item;
	पूर्णांक jbegin_count = JOURNAL_PER_BALANCE_CNT;
	loff_t byte_offset = ((loff_t)block << inode->i_sb->s_blocksize_bits)+1;
	पूर्णांक retval;
	पूर्णांक use_get_block = 0;
	पूर्णांक bytes_copied = 0;
	पूर्णांक copy_size;
	पूर्णांक trans_running = 0;

	/*
	 * catch places below that try to log something without
	 * starting a trans
	 */
	th.t_trans_id = 0;

	अगर (!buffer_uptodate(bh_result)) अणु
		वापस -EIO;
	पूर्ण

	kmap(bh_result->b_page);
start_over:
	reiserfs_ग_लिखो_lock(inode->i_sb);
	make_cpu_key(&key, inode, byte_offset, TYPE_ANY, 3);

research:
	retval = search_क्रम_position_by_key(inode->i_sb, &key, &path);
	अगर (retval != POSITION_FOUND) अणु
		use_get_block = 1;
		जाओ out;
	पूर्ण

	bh = get_last_bh(&path);
	ih = tp_item_head(&path);
	item = tp_item_body(&path);
	pos_in_item = path.pos_in_item;

	/* we've found an unक्रमmatted node */
	अगर (indirect_item_found(retval, ih)) अणु
		अगर (bytes_copied > 0) अणु
			reiserfs_warning(inode->i_sb, "clm-6002",
					 "bytes_copied %d", bytes_copied);
		पूर्ण
		अगर (!get_block_num(item, pos_in_item)) अणु
			/* crap, we are writing to a hole */
			use_get_block = 1;
			जाओ out;
		पूर्ण
		set_block_dev_mapped(bh_result,
				     get_block_num(item, pos_in_item), inode);
	पूर्ण अन्यथा अगर (is_direct_le_ih(ih)) अणु
		अक्षर *p;
		p = page_address(bh_result->b_page);
		p += (byte_offset - 1) & (PAGE_SIZE - 1);
		copy_size = ih_item_len(ih) - pos_in_item;

		fs_gen = get_generation(inode->i_sb);
		copy_item_head(&पंचांगp_ih, ih);

		अगर (!trans_running) अणु
			/* vs-3050 is gone, no need to drop the path */
			retval = journal_begin(&th, inode->i_sb, jbegin_count);
			अगर (retval)
				जाओ out;
			reiserfs_update_inode_transaction(inode);
			trans_running = 1;
			अगर (fs_changed(fs_gen, inode->i_sb)
			    && item_moved(&पंचांगp_ih, &path)) अणु
				reiserfs_restore_prepared_buffer(inode->i_sb,
								 bh);
				जाओ research;
			पूर्ण
		पूर्ण

		reiserfs_prepare_क्रम_journal(inode->i_sb, bh, 1);

		अगर (fs_changed(fs_gen, inode->i_sb)
		    && item_moved(&पंचांगp_ih, &path)) अणु
			reiserfs_restore_prepared_buffer(inode->i_sb, bh);
			जाओ research;
		पूर्ण

		स_नकल(ih_item_body(bh, ih) + pos_in_item, p + bytes_copied,
		       copy_size);

		journal_mark_dirty(&th, bh);
		bytes_copied += copy_size;
		set_block_dev_mapped(bh_result, 0, inode);

		/* are there still bytes left? */
		अगर (bytes_copied < bh_result->b_size &&
		    (byte_offset + bytes_copied) < inode->i_size) अणु
			set_cpu_key_k_offset(&key,
					     cpu_key_k_offset(&key) +
					     copy_size);
			जाओ research;
		पूर्ण
	पूर्ण अन्यथा अणु
		reiserfs_warning(inode->i_sb, "clm-6003",
				 "bad item inode %lu", inode->i_ino);
		retval = -EIO;
		जाओ out;
	पूर्ण
	retval = 0;

out:
	pathrअन्यथा(&path);
	अगर (trans_running) अणु
		पूर्णांक err = journal_end(&th);
		अगर (err)
			retval = err;
		trans_running = 0;
	पूर्ण
	reiserfs_ग_लिखो_unlock(inode->i_sb);

	/* this is where we fill in holes in the file. */
	अगर (use_get_block) अणु
		retval = reiserfs_get_block(inode, block, bh_result,
					    GET_BLOCK_CREATE | GET_BLOCK_NO_IMUX
					    | GET_BLOCK_NO_DANGLE);
		अगर (!retval) अणु
			अगर (!buffer_mapped(bh_result)
			    || bh_result->b_blocknr == 0) अणु
				/* get_block failed to find a mapped unक्रमmatted node. */
				use_get_block = 0;
				जाओ start_over;
			पूर्ण
		पूर्ण
	पूर्ण
	kunmap(bh_result->b_page);

	अगर (!retval && buffer_mapped(bh_result) && bh_result->b_blocknr == 0) अणु
		/*
		 * we've copied data from the page पूर्णांकo the direct item, so the
		 * buffer in the page is now clean, mark it to reflect that.
		 */
		lock_buffer(bh_result);
		clear_buffer_dirty(bh_result);
		unlock_buffer(bh_result);
	पूर्ण
	वापस retval;
पूर्ण

/*
 * mason@suse.com: updated in 2.5.54 to follow the same general io
 * start/recovery path as __block_ग_लिखो_full_page, aदीर्घ with special
 * code to handle reiserfs tails.
 */
अटल पूर्णांक reiserfs_ग_लिखो_full_page(काष्ठा page *page,
				    काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	अचिन्हित दीर्घ end_index = inode->i_size >> PAGE_SHIFT;
	पूर्णांक error = 0;
	अचिन्हित दीर्घ block;
	sector_t last_block;
	काष्ठा buffer_head *head, *bh;
	पूर्णांक partial = 0;
	पूर्णांक nr = 0;
	पूर्णांक checked = PageChecked(page);
	काष्ठा reiserfs_transaction_handle th;
	काष्ठा super_block *s = inode->i_sb;
	पूर्णांक bh_per_page = PAGE_SIZE / s->s_blocksize;
	th.t_trans_id = 0;

	/* no logging allowed when nonblocking or from PF_MEMALLOC */
	अगर (checked && (current->flags & PF_MEMALLOC)) अणु
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		unlock_page(page);
		वापस 0;
	पूर्ण

	/*
	 * The page dirty bit is cleared beक्रमe ग_लिखोpage is called, which
	 * means we have to tell create_empty_buffers to make dirty buffers
	 * The page really should be up to date at this poपूर्णांक, so tossing
	 * in the BH_Uptodate is just a sanity check.
	 */
	अगर (!page_has_buffers(page)) अणु
		create_empty_buffers(page, s->s_blocksize,
				     (1 << BH_Dirty) | (1 << BH_Uptodate));
	पूर्ण
	head = page_buffers(page);

	/*
	 * last page in the file, zero out any contents past the
	 * last byte in the file
	 */
	अगर (page->index >= end_index) अणु
		अचिन्हित last_offset;

		last_offset = inode->i_size & (PAGE_SIZE - 1);
		/* no file contents in this page */
		अगर (page->index >= end_index + 1 || !last_offset) अणु
			unlock_page(page);
			वापस 0;
		पूर्ण
		zero_user_segment(page, last_offset, PAGE_SIZE);
	पूर्ण
	bh = head;
	block = page->index << (PAGE_SHIFT - s->s_blocksize_bits);
	last_block = (i_size_पढ़ो(inode) - 1) >> inode->i_blkbits;
	/* first map all the buffers, logging any direct items we find */
	करो अणु
		अगर (block > last_block) अणु
			/*
			 * This can happen when the block size is less than
			 * the page size.  The corresponding bytes in the page
			 * were zero filled above
			 */
			clear_buffer_dirty(bh);
			set_buffer_uptodate(bh);
		पूर्ण अन्यथा अगर ((checked || buffer_dirty(bh)) &&
		           (!buffer_mapped(bh) || (buffer_mapped(bh)
						       && bh->b_blocknr ==
						       0))) अणु
			/*
			 * not mapped yet, or it poपूर्णांकs to a direct item, search
			 * the btree क्रम the mapping info, and log any direct
			 * items found
			 */
			अगर ((error = map_block_क्रम_ग_लिखोpage(inode, bh, block))) अणु
				जाओ fail;
			पूर्ण
		पूर्ण
		bh = bh->b_this_page;
		block++;
	पूर्ण जबतक (bh != head);

	/*
	 * we start the transaction after map_block_क्रम_ग_लिखोpage,
	 * because it can create holes in the file (an unbounded operation).
	 * starting it here, we can make a reliable estimate क्रम how many
	 * blocks we're going to log
	 */
	अगर (checked) अणु
		ClearPageChecked(page);
		reiserfs_ग_लिखो_lock(s);
		error = journal_begin(&th, s, bh_per_page + 1);
		अगर (error) अणु
			reiserfs_ग_लिखो_unlock(s);
			जाओ fail;
		पूर्ण
		reiserfs_update_inode_transaction(inode);
	पूर्ण
	/* now go through and lock any dirty buffers on the page */
	करो अणु
		get_bh(bh);
		अगर (!buffer_mapped(bh))
			जारी;
		अगर (buffer_mapped(bh) && bh->b_blocknr == 0)
			जारी;

		अगर (checked) अणु
			reiserfs_prepare_क्रम_journal(s, bh, 1);
			journal_mark_dirty(&th, bh);
			जारी;
		पूर्ण
		/*
		 * from this poपूर्णांक on, we know the buffer is mapped to a
		 * real block and not a direct item
		 */
		अगर (wbc->sync_mode != WB_SYNC_NONE) अणु
			lock_buffer(bh);
		पूर्ण अन्यथा अणु
			अगर (!trylock_buffer(bh)) अणु
				redirty_page_क्रम_ग_लिखोpage(wbc, page);
				जारी;
			पूर्ण
		पूर्ण
		अगर (test_clear_buffer_dirty(bh)) अणु
			mark_buffer_async_ग_लिखो(bh);
		पूर्ण अन्यथा अणु
			unlock_buffer(bh);
		पूर्ण
	पूर्ण जबतक ((bh = bh->b_this_page) != head);

	अगर (checked) अणु
		error = journal_end(&th);
		reiserfs_ग_लिखो_unlock(s);
		अगर (error)
			जाओ fail;
	पूर्ण
	BUG_ON(PageWriteback(page));
	set_page_ग_लिखोback(page);
	unlock_page(page);

	/*
	 * since any buffer might be the only dirty buffer on the page,
	 * the first submit_bh can bring the page out of ग_लिखोback.
	 * be careful with the buffers.
	 */
	करो अणु
		काष्ठा buffer_head *next = bh->b_this_page;
		अगर (buffer_async_ग_लिखो(bh)) अणु
			submit_bh(REQ_OP_WRITE, 0, bh);
			nr++;
		पूर्ण
		put_bh(bh);
		bh = next;
	पूर्ण जबतक (bh != head);

	error = 0;
करोne:
	अगर (nr == 0) अणु
		/*
		 * अगर this page only had a direct item, it is very possible क्रम
		 * no io to be required without there being an error.  Or,
		 * someone अन्यथा could have locked them and sent them करोwn the
		 * pipe without locking the page
		 */
		bh = head;
		करो अणु
			अगर (!buffer_uptodate(bh)) अणु
				partial = 1;
				अवरोध;
			पूर्ण
			bh = bh->b_this_page;
		पूर्ण जबतक (bh != head);
		अगर (!partial)
			SetPageUptodate(page);
		end_page_ग_लिखोback(page);
	पूर्ण
	वापस error;

fail:
	/*
	 * catches various errors, we need to make sure any valid dirty blocks
	 * get to the media.  The page is currently locked and not marked क्रम
	 * ग_लिखोback
	 */
	ClearPageUptodate(page);
	bh = head;
	करो अणु
		get_bh(bh);
		अगर (buffer_mapped(bh) && buffer_dirty(bh) && bh->b_blocknr) अणु
			lock_buffer(bh);
			mark_buffer_async_ग_लिखो(bh);
		पूर्ण अन्यथा अणु
			/*
			 * clear any dirty bits that might have come from
			 * getting attached to a dirty page
			 */
			clear_buffer_dirty(bh);
		पूर्ण
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
	SetPageError(page);
	BUG_ON(PageWriteback(page));
	set_page_ग_लिखोback(page);
	unlock_page(page);
	करो अणु
		काष्ठा buffer_head *next = bh->b_this_page;
		अगर (buffer_async_ग_लिखो(bh)) अणु
			clear_buffer_dirty(bh);
			submit_bh(REQ_OP_WRITE, 0, bh);
			nr++;
		पूर्ण
		put_bh(bh);
		bh = next;
	पूर्ण जबतक (bh != head);
	जाओ करोne;
पूर्ण

अटल पूर्णांक reiserfs_पढ़ोpage(काष्ठा file *f, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page, reiserfs_get_block);
पूर्ण

अटल पूर्णांक reiserfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	reiserfs_रुको_on_ग_लिखो_block(inode->i_sb);
	वापस reiserfs_ग_लिखो_full_page(page, wbc);
पूर्ण

अटल व्योम reiserfs_truncate_failed_ग_लिखो(काष्ठा inode *inode)
अणु
	truncate_inode_pages(inode->i_mapping, inode->i_size);
	reiserfs_truncate_file(inode, 0);
पूर्ण

अटल पूर्णांक reiserfs_ग_लिखो_begin(काष्ठा file *file,
				काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित flags,
				काष्ठा page **pagep, व्योम **fsdata)
अणु
	काष्ठा inode *inode;
	काष्ठा page *page;
	pgoff_t index;
	पूर्णांक ret;
	पूर्णांक old_ref = 0;

 	inode = mapping->host;
	*fsdata = शून्य;
 	अगर (flags & AOP_FLAG_CONT_EXPAND &&
 	    (pos & (inode->i_sb->s_blocksize - 1)) == 0) अणु
 		pos ++;
		*fsdata = (व्योम *)(अचिन्हित दीर्घ)flags;
	पूर्ण

	index = pos >> PAGE_SHIFT;
	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;
	*pagep = page;

	reiserfs_रुको_on_ग_लिखो_block(inode->i_sb);
	fix_tail_page_क्रम_writing(page);
	अगर (reiserfs_transaction_running(inode->i_sb)) अणु
		काष्ठा reiserfs_transaction_handle *th;
		th = (काष्ठा reiserfs_transaction_handle *)current->
		    journal_info;
		BUG_ON(!th->t_refcount);
		BUG_ON(!th->t_trans_id);
		old_ref = th->t_refcount;
		th->t_refcount++;
	पूर्ण
	ret = __block_ग_लिखो_begin(page, pos, len, reiserfs_get_block);
	अगर (ret && reiserfs_transaction_running(inode->i_sb)) अणु
		काष्ठा reiserfs_transaction_handle *th = current->journal_info;
		/*
		 * this माला_लो a little ugly.  If reiserfs_get_block वापसed an
		 * error and left a transacstion running, we've got to बंद
		 * it, and we've got to मुक्त handle अगर it was a persistent
		 * transaction.
		 *
		 * But, अगर we had nested पूर्णांकo an existing transaction, we need
		 * to just drop the ref count on the handle.
		 *
		 * If old_ref == 0, the transaction is from reiserfs_get_block,
		 * and it was a persistent trans.  Otherwise, it was nested
		 * above.
		 */
		अगर (th->t_refcount > old_ref) अणु
			अगर (old_ref)
				th->t_refcount--;
			अन्यथा अणु
				पूर्णांक err;
				reiserfs_ग_लिखो_lock(inode->i_sb);
				err = reiserfs_end_persistent_transaction(th);
				reiserfs_ग_लिखो_unlock(inode->i_sb);
				अगर (err)
					ret = err;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		unlock_page(page);
		put_page(page);
		/* Truncate allocated blocks */
		reiserfs_truncate_failed_ग_लिखो(inode);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक __reiserfs_ग_लिखो_begin(काष्ठा page *page, अचिन्हित from, अचिन्हित len)
अणु
	काष्ठा inode *inode = page->mapping->host;
	पूर्णांक ret;
	पूर्णांक old_ref = 0;
	पूर्णांक depth;

	depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
	reiserfs_रुको_on_ग_लिखो_block(inode->i_sb);
	reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);

	fix_tail_page_क्रम_writing(page);
	अगर (reiserfs_transaction_running(inode->i_sb)) अणु
		काष्ठा reiserfs_transaction_handle *th;
		th = (काष्ठा reiserfs_transaction_handle *)current->
		    journal_info;
		BUG_ON(!th->t_refcount);
		BUG_ON(!th->t_trans_id);
		old_ref = th->t_refcount;
		th->t_refcount++;
	पूर्ण

	ret = __block_ग_लिखो_begin(page, from, len, reiserfs_get_block);
	अगर (ret && reiserfs_transaction_running(inode->i_sb)) अणु
		काष्ठा reiserfs_transaction_handle *th = current->journal_info;
		/*
		 * this माला_लो a little ugly.  If reiserfs_get_block वापसed an
		 * error and left a transacstion running, we've got to बंद
		 * it, and we've got to मुक्त handle अगर it was a persistent
		 * transaction.
		 *
		 * But, अगर we had nested पूर्णांकo an existing transaction, we need
		 * to just drop the ref count on the handle.
		 *
		 * If old_ref == 0, the transaction is from reiserfs_get_block,
		 * and it was a persistent trans.  Otherwise, it was nested
		 * above.
		 */
		अगर (th->t_refcount > old_ref) अणु
			अगर (old_ref)
				th->t_refcount--;
			अन्यथा अणु
				पूर्णांक err;
				reiserfs_ग_लिखो_lock(inode->i_sb);
				err = reiserfs_end_persistent_transaction(th);
				reiserfs_ग_लिखो_unlock(inode->i_sb);
				अगर (err)
					ret = err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;

पूर्ण

अटल sector_t reiserfs_aop_bmap(काष्ठा address_space *as, sector_t block)
अणु
	वापस generic_block_bmap(as, block, reiserfs_bmap);
पूर्ण

अटल पूर्णांक reiserfs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			      loff_t pos, अचिन्हित len, अचिन्हित copied,
			      काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = page->mapping->host;
	पूर्णांक ret = 0;
	पूर्णांक update_sd = 0;
	काष्ठा reiserfs_transaction_handle *th;
	अचिन्हित start;
	bool locked = false;

	अगर ((अचिन्हित दीर्घ)fsdata & AOP_FLAG_CONT_EXPAND)
		pos ++;

	reiserfs_रुको_on_ग_लिखो_block(inode->i_sb);
	अगर (reiserfs_transaction_running(inode->i_sb))
		th = current->journal_info;
	अन्यथा
		th = शून्य;

	start = pos & (PAGE_SIZE - 1);
	अगर (unlikely(copied < len)) अणु
		अगर (!PageUptodate(page))
			copied = 0;

		page_zero_new_buffers(page, start + copied, start + len);
	पूर्ण
	flush_dcache_page(page);

	reiserfs_commit_page(inode, page, start, start + copied);

	/*
	 * generic_commit_ग_लिखो करोes this क्रम us, but करोes not update the
	 * transaction tracking stuff when the size changes.  So, we have
	 * to करो the i_size updates here.
	 */
	अगर (pos + copied > inode->i_size) अणु
		काष्ठा reiserfs_transaction_handle myth;
		reiserfs_ग_लिखो_lock(inode->i_sb);
		locked = true;
		/*
		 * If the file have grown beyond the border where it
		 * can have a tail, unmark it as needing a tail
		 * packing
		 */
		अगर ((have_large_tails(inode->i_sb)
		     && inode->i_size > i_block_size(inode) * 4)
		    || (have_small_tails(inode->i_sb)
			&& inode->i_size > i_block_size(inode)))
			REISERFS_I(inode)->i_flags &= ~i_pack_on_बंद_mask;

		ret = journal_begin(&myth, inode->i_sb, 1);
		अगर (ret)
			जाओ journal_error;

		reiserfs_update_inode_transaction(inode);
		inode->i_size = pos + copied;
		/*
		 * this will just nest पूर्णांकo our transaction.  It's important
		 * to use mark_inode_dirty so the inode माला_लो pushed around on
		 * the dirty lists, and so that O_SYNC works as expected
		 */
		mark_inode_dirty(inode);
		reiserfs_update_sd(&myth, inode);
		update_sd = 1;
		ret = journal_end(&myth);
		अगर (ret)
			जाओ journal_error;
	पूर्ण
	अगर (th) अणु
		अगर (!locked) अणु
			reiserfs_ग_लिखो_lock(inode->i_sb);
			locked = true;
		पूर्ण
		अगर (!update_sd)
			mark_inode_dirty(inode);
		ret = reiserfs_end_persistent_transaction(th);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	अगर (locked)
		reiserfs_ग_लिखो_unlock(inode->i_sb);
	unlock_page(page);
	put_page(page);

	अगर (pos + len > inode->i_size)
		reiserfs_truncate_failed_ग_लिखो(inode);

	वापस ret == 0 ? copied : ret;

journal_error:
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	locked = false;
	अगर (th) अणु
		अगर (!update_sd)
			reiserfs_update_sd(th, inode);
		ret = reiserfs_end_persistent_transaction(th);
	पूर्ण
	जाओ out;
पूर्ण

पूर्णांक reiserfs_commit_ग_लिखो(काष्ठा file *f, काष्ठा page *page,
			  अचिन्हित from, अचिन्हित to)
अणु
	काष्ठा inode *inode = page->mapping->host;
	loff_t pos = ((loff_t) page->index << PAGE_SHIFT) + to;
	पूर्णांक ret = 0;
	पूर्णांक update_sd = 0;
	काष्ठा reiserfs_transaction_handle *th = शून्य;
	पूर्णांक depth;

	depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
	reiserfs_रुको_on_ग_लिखो_block(inode->i_sb);
	reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);

	अगर (reiserfs_transaction_running(inode->i_sb)) अणु
		th = current->journal_info;
	पूर्ण
	reiserfs_commit_page(inode, page, from, to);

	/*
	 * generic_commit_ग_लिखो करोes this क्रम us, but करोes not update the
	 * transaction tracking stuff when the size changes.  So, we have
	 * to करो the i_size updates here.
	 */
	अगर (pos > inode->i_size) अणु
		काष्ठा reiserfs_transaction_handle myth;
		/*
		 * If the file have grown beyond the border where it
		 * can have a tail, unmark it as needing a tail
		 * packing
		 */
		अगर ((have_large_tails(inode->i_sb)
		     && inode->i_size > i_block_size(inode) * 4)
		    || (have_small_tails(inode->i_sb)
			&& inode->i_size > i_block_size(inode)))
			REISERFS_I(inode)->i_flags &= ~i_pack_on_बंद_mask;

		ret = journal_begin(&myth, inode->i_sb, 1);
		अगर (ret)
			जाओ journal_error;

		reiserfs_update_inode_transaction(inode);
		inode->i_size = pos;
		/*
		 * this will just nest पूर्णांकo our transaction.  It's important
		 * to use mark_inode_dirty so the inode माला_लो pushed around
		 * on the dirty lists, and so that O_SYNC works as expected
		 */
		mark_inode_dirty(inode);
		reiserfs_update_sd(&myth, inode);
		update_sd = 1;
		ret = journal_end(&myth);
		अगर (ret)
			जाओ journal_error;
	पूर्ण
	अगर (th) अणु
		अगर (!update_sd)
			mark_inode_dirty(inode);
		ret = reiserfs_end_persistent_transaction(th);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	वापस ret;

journal_error:
	अगर (th) अणु
		अगर (!update_sd)
			reiserfs_update_sd(th, inode);
		ret = reiserfs_end_persistent_transaction(th);
	पूर्ण

	वापस ret;
पूर्ण

व्योम sd_attrs_to_i_attrs(__u16 sd_attrs, काष्ठा inode *inode)
अणु
	अगर (reiserfs_attrs(inode->i_sb)) अणु
		अगर (sd_attrs & REISERFS_SYNC_FL)
			inode->i_flags |= S_SYNC;
		अन्यथा
			inode->i_flags &= ~S_SYNC;
		अगर (sd_attrs & REISERFS_IMMUTABLE_FL)
			inode->i_flags |= S_IMMUTABLE;
		अन्यथा
			inode->i_flags &= ~S_IMMUTABLE;
		अगर (sd_attrs & REISERFS_APPEND_FL)
			inode->i_flags |= S_APPEND;
		अन्यथा
			inode->i_flags &= ~S_APPEND;
		अगर (sd_attrs & REISERFS_NOATIME_FL)
			inode->i_flags |= S_NOATIME;
		अन्यथा
			inode->i_flags &= ~S_NOATIME;
		अगर (sd_attrs & REISERFS_NOTAIL_FL)
			REISERFS_I(inode)->i_flags |= i_nopack_mask;
		अन्यथा
			REISERFS_I(inode)->i_flags &= ~i_nopack_mask;
	पूर्ण
पूर्ण

/*
 * decide अगर this buffer needs to stay around क्रम data logging or ordered
 * ग_लिखो purposes
 */
अटल पूर्णांक invalidatepage_can_drop(काष्ठा inode *inode, काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret = 1;
	काष्ठा reiserfs_journal *j = SB_JOURNAL(inode->i_sb);

	lock_buffer(bh);
	spin_lock(&j->j_dirty_buffers_lock);
	अगर (!buffer_mapped(bh)) अणु
		जाओ मुक्त_jh;
	पूर्ण
	/*
	 * the page is locked, and the only places that log a data buffer
	 * also lock the page.
	 */
	अगर (reiserfs_file_data_log(inode)) अणु
		/*
		 * very conservative, leave the buffer pinned अगर
		 * anyone might need it.
		 */
		अगर (buffer_journaled(bh) || buffer_journal_dirty(bh)) अणु
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा  अगर (buffer_dirty(bh)) अणु
		काष्ठा reiserfs_journal_list *jl;
		काष्ठा reiserfs_jh *jh = bh->b_निजी;

		/*
		 * why is this safe?
		 * reiserfs_setattr updates i_size in the on disk
		 * stat data beक्रमe allowing vmtruncate to be called.
		 *
		 * If buffer was put onto the ordered list क्रम this
		 * transaction, we know क्रम sure either this transaction
		 * or an older one alपढ़ोy has updated i_size on disk,
		 * and this ordered data won't be referenced in the file
		 * अगर we crash.
		 *
		 * अगर the buffer was put onto the ordered list क्रम an older
		 * transaction, we need to leave it around
		 */
		अगर (jh && (jl = jh->jl)
		    && jl != SB_JOURNAL(inode->i_sb)->j_current_jl)
			ret = 0;
	पूर्ण
मुक्त_jh:
	अगर (ret && bh->b_निजी) अणु
		reiserfs_मुक्त_jh(bh);
	पूर्ण
	spin_unlock(&j->j_dirty_buffers_lock);
	unlock_buffer(bh);
	वापस ret;
पूर्ण

/* clm -- taken from fs/buffer.c:block_invalidate_page */
अटल व्योम reiserfs_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				    अचिन्हित पूर्णांक length)
अणु
	काष्ठा buffer_head *head, *bh, *next;
	काष्ठा inode *inode = page->mapping->host;
	अचिन्हित पूर्णांक curr_off = 0;
	अचिन्हित पूर्णांक stop = offset + length;
	पूर्णांक partial_page = (offset || length < PAGE_SIZE);
	पूर्णांक ret = 1;

	BUG_ON(!PageLocked(page));

	अगर (!partial_page)
		ClearPageChecked(page);

	अगर (!page_has_buffers(page))
		जाओ out;

	head = page_buffers(page);
	bh = head;
	करो अणु
		अचिन्हित पूर्णांक next_off = curr_off + bh->b_size;
		next = bh->b_this_page;

		अगर (next_off > stop)
			जाओ out;

		/*
		 * is this block fully invalidated?
		 */
		अगर (offset <= curr_off) अणु
			अगर (invalidatepage_can_drop(inode, bh))
				reiserfs_unmap_buffer(bh);
			अन्यथा
				ret = 0;
		पूर्ण
		curr_off = next_off;
		bh = next;
	पूर्ण जबतक (bh != head);

	/*
	 * We release buffers only अगर the entire page is being invalidated.
	 * The get_block cached value has been unconditionally invalidated,
	 * so real IO is not possible anymore.
	 */
	अगर (!partial_page && ret) अणु
		ret = try_to_release_page(page, 0);
		/* maybe should BUG_ON(!ret); - neilb */
	पूर्ण
out:
	वापस;
पूर्ण

अटल पूर्णांक reiserfs_set_page_dirty(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	अगर (reiserfs_file_data_log(inode)) अणु
		SetPageChecked(page);
		वापस __set_page_dirty_nobuffers(page);
	पूर्ण
	वापस __set_page_dirty_buffers(page);
पूर्ण

/*
 * Returns 1 अगर the page's buffers were dropped.  The page is locked.
 *
 * Takes j_dirty_buffers_lock to protect the b_assoc_buffers list_heads
 * in the buffers at page_buffers(page).
 *
 * even in -o notail mode, we can't be sure an old mount without -o notail
 * didn't create files with tails.
 */
अटल पूर्णांक reiserfs_releasepage(काष्ठा page *page, gfp_t unused_gfp_flags)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा reiserfs_journal *j = SB_JOURNAL(inode->i_sb);
	काष्ठा buffer_head *head;
	काष्ठा buffer_head *bh;
	पूर्णांक ret = 1;

	WARN_ON(PageChecked(page));
	spin_lock(&j->j_dirty_buffers_lock);
	head = page_buffers(page);
	bh = head;
	करो अणु
		अगर (bh->b_निजी) अणु
			अगर (!buffer_dirty(bh) && !buffer_locked(bh)) अणु
				reiserfs_मुक्त_jh(bh);
			पूर्ण अन्यथा अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
	अगर (ret)
		ret = try_to_मुक्त_buffers(page);
	spin_unlock(&j->j_dirty_buffers_lock);
	वापस ret;
पूर्ण

/*
 * We thank Mingming Cao क्रम helping us understand in great detail what
 * to करो in this section of the code.
 */
अटल sमाप_प्रकार reiserfs_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file->f_mapping->host;
	माप_प्रकार count = iov_iter_count(iter);
	sमाप_प्रकार ret;

	ret = blockdev_direct_IO(iocb, inode, iter,
				 reiserfs_get_blocks_direct_io);

	/*
	 * In हाल of error extending ग_लिखो may have instantiated a few
	 * blocks outside i_size. Trim these off again.
	 */
	अगर (unlikely(iov_iter_rw(iter) == WRITE && ret < 0)) अणु
		loff_t isize = i_size_पढ़ो(inode);
		loff_t end = iocb->ki_pos + count;

		अगर ((end > isize) && inode_newsize_ok(inode, isize) == 0) अणु
			truncate_setsize(inode, isize);
			reiserfs_vfs_truncate_file(inode);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक reiserfs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		     काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	अचिन्हित पूर्णांक ia_valid;
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	/* must be turned off क्रम recursive notअगरy_change calls */
	ia_valid = attr->ia_valid &= ~(ATTR_KILL_SUID|ATTR_KILL_SGID);

	अगर (is_quota_modअगरication(inode, attr)) अणु
		error = dquot_initialize(inode);
		अगर (error)
			वापस error;
	पूर्ण
	reiserfs_ग_लिखो_lock(inode->i_sb);
	अगर (attr->ia_valid & ATTR_SIZE) अणु
		/*
		 * version 2 items will be caught by the s_maxbytes check
		 * करोne क्रम us in vmtruncate
		 */
		अगर (get_inode_item_key_version(inode) == KEY_FORMAT_3_5 &&
		    attr->ia_size > MAX_NON_LFS) अणु
			reiserfs_ग_लिखो_unlock(inode->i_sb);
			error = -EFBIG;
			जाओ out;
		पूर्ण

		inode_dio_रुको(inode);

		/* fill in hole poपूर्णांकers in the expanding truncate हाल. */
		अगर (attr->ia_size > inode->i_size) अणु
			error = generic_cont_expand_simple(inode, attr->ia_size);
			अगर (REISERFS_I(inode)->i_pपुनः_स्मृति_count > 0) अणु
				पूर्णांक err;
				काष्ठा reiserfs_transaction_handle th;
				/* we're changing at most 2 biपंचांगaps, inode + super */
				err = journal_begin(&th, inode->i_sb, 4);
				अगर (!err) अणु
					reiserfs_discard_pपुनः_स्मृति(&th, inode);
					err = journal_end(&th);
				पूर्ण
				अगर (err)
					error = err;
			पूर्ण
			अगर (error) अणु
				reiserfs_ग_लिखो_unlock(inode->i_sb);
				जाओ out;
			पूर्ण
			/*
			 * file size is changed, स_समय and mसमय are
			 * to be updated
			 */
			attr->ia_valid |= (ATTR_MTIME | ATTR_CTIME);
		पूर्ण
	पूर्ण
	reiserfs_ग_लिखो_unlock(inode->i_sb);

	अगर ((((attr->ia_valid & ATTR_UID) && (from_kuid(&init_user_ns, attr->ia_uid) & ~0xffff)) ||
	     ((attr->ia_valid & ATTR_GID) && (from_kgid(&init_user_ns, attr->ia_gid) & ~0xffff))) &&
	    (get_inode_sd_version(inode) == STAT_DATA_V1)) अणु
		/* stat data of क्रमmat v3.5 has 16 bit uid and gid */
		error = -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((ia_valid & ATTR_UID && !uid_eq(attr->ia_uid, inode->i_uid)) ||
	    (ia_valid & ATTR_GID && !gid_eq(attr->ia_gid, inode->i_gid))) अणु
		काष्ठा reiserfs_transaction_handle th;
		पूर्णांक jbegin_count =
		    2 *
		    (REISERFS_QUOTA_INIT_BLOCKS(inode->i_sb) +
		     REISERFS_QUOTA_DEL_BLOCKS(inode->i_sb)) +
		    2;

		error = reiserfs_chown_xattrs(inode, attr);

		अगर (error)
			वापस error;

		/*
		 * (user+group)*(old+new) काष्ठाure - we count quota
		 * info and , inode ग_लिखो (sb, inode)
		 */
		reiserfs_ग_लिखो_lock(inode->i_sb);
		error = journal_begin(&th, inode->i_sb, jbegin_count);
		reiserfs_ग_लिखो_unlock(inode->i_sb);
		अगर (error)
			जाओ out;
		error = dquot_transfer(inode, attr);
		reiserfs_ग_लिखो_lock(inode->i_sb);
		अगर (error) अणु
			journal_end(&th);
			reiserfs_ग_लिखो_unlock(inode->i_sb);
			जाओ out;
		पूर्ण

		/*
		 * Update corresponding info in inode so that everything
		 * is in one transaction
		 */
		अगर (attr->ia_valid & ATTR_UID)
			inode->i_uid = attr->ia_uid;
		अगर (attr->ia_valid & ATTR_GID)
			inode->i_gid = attr->ia_gid;
		mark_inode_dirty(inode);
		error = journal_end(&th);
		reiserfs_ग_लिखो_unlock(inode->i_sb);
		अगर (error)
			जाओ out;
	पूर्ण

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_पढ़ो(inode)) अणु
		error = inode_newsize_ok(inode, attr->ia_size);
		अगर (!error) अणु
			/*
			 * Could race against reiserfs_file_release
			 * अगर called from NFS, so take tailpack mutex.
			 */
			mutex_lock(&REISERFS_I(inode)->tailpack);
			truncate_setsize(inode, attr->ia_size);
			reiserfs_truncate_file(inode, 1);
			mutex_unlock(&REISERFS_I(inode)->tailpack);
		पूर्ण
	पूर्ण

	अगर (!error) अणु
		setattr_copy(&init_user_ns, inode, attr);
		mark_inode_dirty(inode);
	पूर्ण

	अगर (!error && reiserfs_posixacl(inode->i_sb)) अणु
		अगर (attr->ia_valid & ATTR_MODE)
			error = reiserfs_acl_chmod(inode);
	पूर्ण

out:
	वापस error;
पूर्ण

स्थिर काष्ठा address_space_operations reiserfs_address_space_operations = अणु
	.ग_लिखोpage = reiserfs_ग_लिखोpage,
	.पढ़ोpage = reiserfs_पढ़ोpage,
	.पढ़ोahead = reiserfs_पढ़ोahead,
	.releasepage = reiserfs_releasepage,
	.invalidatepage = reiserfs_invalidatepage,
	.ग_लिखो_begin = reiserfs_ग_लिखो_begin,
	.ग_लिखो_end = reiserfs_ग_लिखो_end,
	.bmap = reiserfs_aop_bmap,
	.direct_IO = reiserfs_direct_IO,
	.set_page_dirty = reiserfs_set_page_dirty,
पूर्ण;
