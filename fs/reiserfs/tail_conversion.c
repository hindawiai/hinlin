<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 1999 Hans Reiser, see reiserfs/README क्रम licensing and copyright
 * details
 */

#समावेश <linux/समय.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/buffer_head.h>
#समावेश "reiserfs.h"

/*
 * access to tail : when one is going to पढ़ो tail it must make sure, that is
 * not running.  direct2indirect and indirect2direct can not run concurrently
 */

/*
 * Converts direct items to an unक्रमmatted node. Panics अगर file has no
 * tail. -ENOSPC अगर no disk space क्रम conversion
 */
/*
 * path poपूर्णांकs to first direct item of the file regardless of how many of
 * them are there
 */
पूर्णांक direct2indirect(काष्ठा reiserfs_transaction_handle *th, काष्ठा inode *inode,
		    काष्ठा treepath *path, काष्ठा buffer_head *unbh,
		    loff_t tail_offset)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *up_to_date_bh;
	काष्ठा item_head *p_le_ih = tp_item_head(path);
	अचिन्हित दीर्घ total_tail = 0;

	/* Key to search क्रम the last byte of the converted item. */
	काष्ठा cpu_key end_key;

	/*
	 * new indirect item to be inserted or key
	 * of unfm poपूर्णांकer to be pasted
	 */
	काष्ठा item_head ind_ih;
	पूर्णांक blk_size;
	/* वापसed value क्रम reiserfs_insert_item and clones */
	पूर्णांक  retval;
	/* Handle on an unक्रमmatted node that will be inserted in the tree. */
	unp_t unfm_ptr;

	BUG_ON(!th->t_trans_id);

	REISERFS_SB(sb)->s_direct2indirect++;

	blk_size = sb->s_blocksize;

	/*
	 * and key to search क्रम append or insert poपूर्णांकer to the new
	 * unक्रमmatted node.
	 */
	copy_item_head(&ind_ih, p_le_ih);
	set_le_ih_k_offset(&ind_ih, tail_offset);
	set_le_ih_k_type(&ind_ih, TYPE_INसूचीECT);

	/* Set the key to search क्रम the place क्रम new unfm poपूर्णांकer */
	make_cpu_key(&end_key, inode, tail_offset, TYPE_INसूचीECT, 4);

	/* FIXME: we could aव्योम this */
	अगर (search_क्रम_position_by_key(sb, &end_key, path) == POSITION_FOUND) अणु
		reiserfs_error(sb, "PAP-14030",
			       "pasted or inserted byte exists in "
			       "the tree %K. Use fsck to repair.", &end_key);
		pathrअन्यथा(path);
		वापस -EIO;
	पूर्ण

	p_le_ih = tp_item_head(path);

	unfm_ptr = cpu_to_le32(unbh->b_blocknr);

	अगर (is_statdata_le_ih(p_le_ih)) अणु
		/* Insert new indirect item. */
		set_ih_मुक्त_space(&ind_ih, 0);	/* delete at nearest future */
		put_ih_item_len(&ind_ih, UNFM_P_SIZE);
		PATH_LAST_POSITION(path)++;
		retval =
		    reiserfs_insert_item(th, path, &end_key, &ind_ih, inode,
					 (अक्षर *)&unfm_ptr);
	पूर्ण अन्यथा अणु
		/* Paste पूर्णांकo last indirect item of an object. */
		retval = reiserfs_paste_पूर्णांकo_item(th, path, &end_key, inode,
						    (अक्षर *)&unfm_ptr,
						    UNFM_P_SIZE);
	पूर्ण
	अगर (retval) अणु
		वापस retval;
	पूर्ण
	/*
	 * note: from here there are two keys which have matching first
	 *  three key components. They only dअगरfer by the fourth one.
	 */

	/* Set the key to search क्रम the direct items of the file */
	make_cpu_key(&end_key, inode, max_reiserfs_offset(inode), TYPE_सूचीECT,
		     4);

	/*
	 * Move bytes from the direct items to the new unक्रमmatted node
	 * and delete them.
	 */
	जबतक (1) अणु
		पूर्णांक tail_size;

		/*
		 * end_key.k_offset is set so, that we will always have found
		 * last item of the file
		 */
		अगर (search_क्रम_position_by_key(sb, &end_key, path) ==
		    POSITION_FOUND)
			reiserfs_panic(sb, "PAP-14050",
				       "direct item (%K) not found", &end_key);
		p_le_ih = tp_item_head(path);
		RFALSE(!is_direct_le_ih(p_le_ih),
		       "vs-14055: direct item expected(%K), found %h",
		       &end_key, p_le_ih);
		tail_size = (le_ih_k_offset(p_le_ih) & (blk_size - 1))
		    + ih_item_len(p_le_ih) - 1;

		/*
		 * we only send the unbh poपूर्णांकer अगर the buffer is not
		 * up to date.  this aव्योमs overwriting good data from
		 * ग_लिखोpage() with old data from the disk or buffer cache
		 * Special हाल: unbh->b_page will be शून्य अगर we are coming
		 * through सूचीECT_IO handler here.
		 */
		अगर (!unbh->b_page || buffer_uptodate(unbh)
		    || PageUptodate(unbh->b_page)) अणु
			up_to_date_bh = शून्य;
		पूर्ण अन्यथा अणु
			up_to_date_bh = unbh;
		पूर्ण
		retval = reiserfs_delete_item(th, path, &end_key, inode,
						up_to_date_bh);

		total_tail += retval;

		/* करोne: file करोes not have direct items anymore */
		अगर (tail_size == retval)
			अवरोध;

	पूर्ण
	/*
	 * अगर we've copied bytes from disk पूर्णांकo the page, we need to zero
	 * out the unused part of the block (it was not up to date beक्रमe)
	 */
	अगर (up_to_date_bh) अणु
		अचिन्हित pgoff =
		    (tail_offset + total_tail - 1) & (PAGE_SIZE - 1);
		अक्षर *kaddr = kmap_atomic(up_to_date_bh->b_page);
		स_रखो(kaddr + pgoff, 0, blk_size - total_tail);
		kunmap_atomic(kaddr);
	पूर्ण

	REISERFS_I(inode)->i_first_direct_byte = U32_MAX;

	वापस 0;
पूर्ण

/* stolen from fs/buffer.c */
व्योम reiserfs_unmap_buffer(काष्ठा buffer_head *bh)
अणु
	lock_buffer(bh);
	अगर (buffer_journaled(bh) || buffer_journal_dirty(bh)) अणु
		BUG();
	पूर्ण
	clear_buffer_dirty(bh);
	/*
	 * Remove the buffer from whatever list it beदीर्घs to. We are mostly
	 * पूर्णांकerested in removing it from per-sb j_dirty_buffers list, to aव्योम
	 * BUG() on attempt to ग_लिखो not mapped buffer
	 */
	अगर ((!list_empty(&bh->b_assoc_buffers) || bh->b_निजी) && bh->b_page) अणु
		काष्ठा inode *inode = bh->b_page->mapping->host;
		काष्ठा reiserfs_journal *j = SB_JOURNAL(inode->i_sb);
		spin_lock(&j->j_dirty_buffers_lock);
		list_del_init(&bh->b_assoc_buffers);
		reiserfs_मुक्त_jh(bh);
		spin_unlock(&j->j_dirty_buffers_lock);
	पूर्ण
	clear_buffer_mapped(bh);
	clear_buffer_req(bh);
	clear_buffer_new(bh);
	bh->b_bdev = शून्य;
	unlock_buffer(bh);
पूर्ण

/*
 * this first locks inode (neither पढ़ोs nor sync are permitted),
 * पढ़ोs tail through page cache, insert direct item. When direct item
 * inserted successfully inode is left locked. Return value is always
 * what we expect from it (number of cut bytes). But when tail reमुख्यs
 * in the unक्रमmatted node, we set mode to SKIP_BALANCING and unlock
 * inode
 */
पूर्णांक indirect2direct(काष्ठा reiserfs_transaction_handle *th,
		    काष्ठा inode *inode, काष्ठा page *page,
		    काष्ठा treepath *path,	/* path to the indirect item. */
		    स्थिर काष्ठा cpu_key *item_key,	/* Key to look क्रम
							 * unक्रमmatted node
							 * poपूर्णांकer to be cut. */
		    loff_t n_new_file_size,	/* New file size. */
		    अक्षर *mode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा item_head s_ih;
	अचिन्हित दीर्घ block_size = sb->s_blocksize;
	अक्षर *tail;
	पूर्णांक tail_len, round_tail_len;
	loff_t pos, pos1;	/* position of first byte of the tail */
	काष्ठा cpu_key key;

	BUG_ON(!th->t_trans_id);

	REISERFS_SB(sb)->s_indirect2direct++;

	*mode = M_SKIP_BALANCING;

	/* store item head path poपूर्णांकs to. */
	copy_item_head(&s_ih, tp_item_head(path));

	tail_len = (n_new_file_size & (block_size - 1));
	अगर (get_inode_sd_version(inode) == STAT_DATA_V2)
		round_tail_len = ROUND_UP(tail_len);
	अन्यथा
		round_tail_len = tail_len;

	pos =
	    le_ih_k_offset(&s_ih) - 1 + (ih_item_len(&s_ih) / UNFM_P_SIZE -
					 1) * sb->s_blocksize;
	pos1 = pos;

	/*
	 * we are रक्षित by i_mutex. The tail can not disapper, not
	 * append can be करोne either
	 * we are in truncate or packing tail in file_release
	 */

	tail = (अक्षर *)kmap(page);	/* this can schedule */

	अगर (path_changed(&s_ih, path)) अणु
		/* re-search indirect item */
		अगर (search_क्रम_position_by_key(sb, item_key, path)
		    == POSITION_NOT_FOUND)
			reiserfs_panic(sb, "PAP-5520",
				       "item to be converted %K does not exist",
				       item_key);
		copy_item_head(&s_ih, tp_item_head(path));
#अगर_घोषित CONFIG_REISERFS_CHECK
		pos = le_ih_k_offset(&s_ih) - 1 +
		    (ih_item_len(&s_ih) / UNFM_P_SIZE -
		     1) * sb->s_blocksize;
		अगर (pos != pos1)
			reiserfs_panic(sb, "vs-5530", "tail position "
				       "changed while we were reading it");
#पूर्ण_अगर
	पूर्ण

	/* Set direct item header to insert. */
	make_le_item_head(&s_ih, शून्य, get_inode_item_key_version(inode),
			  pos1 + 1, TYPE_सूचीECT, round_tail_len,
			  0xffff /*ih_मुक्त_space */ );

	/*
	 * we want a poपूर्णांकer to the first byte of the tail in the page.
	 * the page was locked and this part of the page was up to date when
	 * indirect2direct was called, so we know the bytes are still valid
	 */
	tail = tail + (pos & (PAGE_SIZE - 1));

	PATH_LAST_POSITION(path)++;

	key = *item_key;
	set_cpu_key_k_type(&key, TYPE_सूचीECT);
	key.key_length = 4;
	/* Insert tail as new direct item in the tree */
	अगर (reiserfs_insert_item(th, path, &key, &s_ih, inode,
				 tail ? tail : शून्य) < 0) अणु
		/*
		 * No disk memory. So we can not convert last unक्रमmatted node
		 * to the direct item.  In this हाल we used to adjust
		 * indirect items's ih_मुक्त_space. Now ih_मुक्त_space is not
		 * used, it would be ideal to ग_लिखो zeros to corresponding
		 * unक्रमmatted node. For now i_size is considered as guard क्रम
		 * going out of file size
		 */
		kunmap(page);
		वापस block_size - round_tail_len;
	पूर्ण
	kunmap(page);

	/* make sure to get the i_blocks changes from reiserfs_insert_item */
	reiserfs_update_sd(th, inode);

	/*
	 * note: we have now the same as in above direct2indirect
	 * conversion: there are two keys which have matching first three
	 * key components. They only dअगरfer by the fourth one.
	 */

	/*
	 * We have inserted new direct item and must हटाओ last
	 * unक्रमmatted node.
	 */
	*mode = M_CUT;

	/* we store position of first direct item in the in-core inode */
	/* mark_file_with_tail (inode, pos1 + 1); */
	REISERFS_I(inode)->i_first_direct_byte = pos1 + 1;

	वापस block_size - round_tail_len;
पूर्ण
