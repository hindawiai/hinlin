<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

/*
 * Now we have all buffers that must be used in balancing of the tree
 * Further calculations can not cause schedule(), and thus the buffer
 * tree will be stable until the balancing will be finished
 * balance the tree according to the analysis made beक्रमe,
 * and using buffers obtained after all above.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/समय.स>
#समावेश "reiserfs.h"
#समावेश <linux/buffer_head.h>
#समावेश <linux/kernel.h>

अटल अंतरभूत व्योम buffer_info_init_left(काष्ठा tree_balance *tb,
                                         काष्ठा buffer_info *bi)
अणु
	bi->tb          = tb;
	bi->bi_bh       = tb->L[0];
	bi->bi_parent   = tb->FL[0];
	bi->bi_position = get_left_neighbor_position(tb, 0);
पूर्ण

अटल अंतरभूत व्योम buffer_info_init_right(काष्ठा tree_balance *tb,
                                          काष्ठा buffer_info *bi)
अणु
	bi->tb          = tb;
	bi->bi_bh       = tb->R[0];
	bi->bi_parent   = tb->FR[0];
	bi->bi_position = get_right_neighbor_position(tb, 0);
पूर्ण

अटल अंतरभूत व्योम buffer_info_init_tbS0(काष्ठा tree_balance *tb,
                                         काष्ठा buffer_info *bi)
अणु
	bi->tb          = tb;
	bi->bi_bh        = PATH_PLAST_BUFFER(tb->tb_path);
	bi->bi_parent   = PATH_H_PPARENT(tb->tb_path, 0);
	bi->bi_position = PATH_H_POSITION(tb->tb_path, 1);
पूर्ण

अटल अंतरभूत व्योम buffer_info_init_bh(काष्ठा tree_balance *tb,
                                       काष्ठा buffer_info *bi,
                                       काष्ठा buffer_head *bh)
अणु
	bi->tb          = tb;
	bi->bi_bh       = bh;
	bi->bi_parent   = शून्य;
	bi->bi_position = 0;
पूर्ण

अंतरभूत व्योम करो_balance_mark_leaf_dirty(काष्ठा tree_balance *tb,
				       काष्ठा buffer_head *bh, पूर्णांक flag)
अणु
	journal_mark_dirty(tb->transaction_handle, bh);
पूर्ण

#घोषणा करो_balance_mark_पूर्णांकernal_dirty करो_balance_mark_leaf_dirty
#घोषणा करो_balance_mark_sb_dirty करो_balance_mark_leaf_dirty

/*
 * summary:
 *  अगर deleting something ( tb->insert_size[0] < 0 )
 *    वापस(balance_leaf_when_delete()); (flag d handled here)
 *  अन्यथा
 *    अगर lnum is larger than 0 we put items पूर्णांकo the left node
 *    अगर rnum is larger than 0 we put items पूर्णांकo the right node
 *    अगर snum1 is larger than 0 we put items पूर्णांकo the new node s1
 *    अगर snum2 is larger than 0 we put items पूर्णांकo the new node s2
 * Note that all *num* count new items being created.
 */

अटल व्योम balance_leaf_when_delete_del(काष्ठा tree_balance *tb)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक item_pos = PATH_LAST_POSITION(tb->tb_path);
	काष्ठा buffer_info bi;
#अगर_घोषित CONFIG_REISERFS_CHECK
	काष्ठा item_head *ih = item_head(tbS0, item_pos);
#पूर्ण_अगर

	RFALSE(ih_item_len(ih) + IH_SIZE != -tb->insert_size[0],
	       "vs-12013: mode Delete, insert size %d, ih to be deleted %h",
	       -tb->insert_size[0], ih);

	buffer_info_init_tbS0(tb, &bi);
	leaf_delete_items(&bi, 0, item_pos, 1, -1);

	अगर (!item_pos && tb->CFL[0]) अणु
		अगर (B_NR_ITEMS(tbS0)) अणु
			replace_key(tb, tb->CFL[0], tb->lkey[0], tbS0, 0);
		पूर्ण अन्यथा अणु
			अगर (!PATH_H_POSITION(tb->tb_path, 1))
				replace_key(tb, tb->CFL[0], tb->lkey[0],
					    PATH_H_PPARENT(tb->tb_path, 0), 0);
		पूर्ण
	पूर्ण

	RFALSE(!item_pos && !tb->CFL[0],
	       "PAP-12020: tb->CFL[0]==%p, tb->L[0]==%p", tb->CFL[0],
	       tb->L[0]);
पूर्ण

/* cut item in S[0] */
अटल व्योम balance_leaf_when_delete_cut(काष्ठा tree_balance *tb)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक item_pos = PATH_LAST_POSITION(tb->tb_path);
	काष्ठा item_head *ih = item_head(tbS0, item_pos);
	पूर्णांक pos_in_item = tb->tb_path->pos_in_item;
	काष्ठा buffer_info bi;
	buffer_info_init_tbS0(tb, &bi);

	अगर (is_direntry_le_ih(ih)) अणु
		/*
		 * UFS unlink semantics are such that you can only
		 * delete one directory entry at a समय.
		 *
		 * when we cut a directory tb->insert_size[0] means
		 * number of entries to be cut (always 1)
		 */
		tb->insert_size[0] = -1;
		leaf_cut_from_buffer(&bi, item_pos, pos_in_item,
				     -tb->insert_size[0]);

		RFALSE(!item_pos && !pos_in_item && !tb->CFL[0],
		       "PAP-12030: can not change delimiting key. CFL[0]=%p",
		       tb->CFL[0]);

		अगर (!item_pos && !pos_in_item && tb->CFL[0])
			replace_key(tb, tb->CFL[0], tb->lkey[0], tbS0, 0);
	पूर्ण अन्यथा अणु
		leaf_cut_from_buffer(&bi, item_pos, pos_in_item,
				     -tb->insert_size[0]);

		RFALSE(!ih_item_len(ih),
		       "PAP-12035: cut must leave non-zero dynamic "
		       "length of item");
	पूर्ण
पूर्ण

अटल पूर्णांक balance_leaf_when_delete_left(काष्ठा tree_balance *tb)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n = B_NR_ITEMS(tbS0);

	/* L[0] must be joined with S[0] */
	अगर (tb->lnum[0] == -1) अणु
		/* R[0] must be also joined with S[0] */
		अगर (tb->rnum[0] == -1) अणु
			अगर (tb->FR[0] == PATH_H_PPARENT(tb->tb_path, 0)) अणु
				/*
				 * all contents of all the
				 * 3 buffers will be in L[0]
				 */
				अगर (PATH_H_POSITION(tb->tb_path, 1) == 0 &&
				    1 < B_NR_ITEMS(tb->FR[0]))
					replace_key(tb, tb->CFL[0],
						    tb->lkey[0], tb->FR[0], 1);

				leaf_move_items(LEAF_FROM_S_TO_L, tb, n, -1,
						शून्य);
				leaf_move_items(LEAF_FROM_R_TO_L, tb,
						B_NR_ITEMS(tb->R[0]), -1,
						शून्य);

				reiserfs_invalidate_buffer(tb, tbS0);
				reiserfs_invalidate_buffer(tb, tb->R[0]);

				वापस 0;
			पूर्ण

			/* all contents of all the 3 buffers will be in R[0] */
			leaf_move_items(LEAF_FROM_S_TO_R, tb, n, -1, शून्य);
			leaf_move_items(LEAF_FROM_L_TO_R, tb,
					B_NR_ITEMS(tb->L[0]), -1, शून्य);

			/* right_delimiting_key is correct in R[0] */
			replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);

			reiserfs_invalidate_buffer(tb, tbS0);
			reiserfs_invalidate_buffer(tb, tb->L[0]);

			वापस -1;
		पूर्ण

		RFALSE(tb->rnum[0] != 0,
		       "PAP-12045: rnum must be 0 (%d)", tb->rnum[0]);
		/* all contents of L[0] and S[0] will be in L[0] */
		leaf_shअगरt_left(tb, n, -1);

		reiserfs_invalidate_buffer(tb, tbS0);

		वापस 0;
	पूर्ण

	/*
	 * a part of contents of S[0] will be in L[0] and
	 * the rest part of S[0] will be in R[0]
	 */

	RFALSE((tb->lnum[0] + tb->rnum[0] < n) ||
	       (tb->lnum[0] + tb->rnum[0] > n + 1),
	       "PAP-12050: rnum(%d) and lnum(%d) and item "
	       "number(%d) in S[0] are not consistent",
	       tb->rnum[0], tb->lnum[0], n);
	RFALSE((tb->lnum[0] + tb->rnum[0] == n) &&
	       (tb->lbytes != -1 || tb->rbytes != -1),
	       "PAP-12055: bad rbytes (%d)/lbytes (%d) "
	       "parameters when items are not split",
	       tb->rbytes, tb->lbytes);
	RFALSE((tb->lnum[0] + tb->rnum[0] == n + 1) &&
	       (tb->lbytes < 1 || tb->rbytes != -1),
	       "PAP-12060: bad rbytes (%d)/lbytes (%d) "
	       "parameters when items are split",
	       tb->rbytes, tb->lbytes);

	leaf_shअगरt_left(tb, tb->lnum[0], tb->lbytes);
	leaf_shअगरt_right(tb, tb->rnum[0], tb->rbytes);

	reiserfs_invalidate_buffer(tb, tbS0);

	वापस 0;
पूर्ण

/*
 * Balance leaf node in हाल of delete or cut: insert_size[0] < 0
 *
 * lnum, rnum can have values >= -1
 *	-1 means that the neighbor must be joined with S
 *	 0 means that nothing should be करोne with the neighbor
 *	>0 means to shअगरt entirely or partly the specअगरied number of items
 *         to the neighbor
 */
अटल पूर्णांक balance_leaf_when_delete(काष्ठा tree_balance *tb, पूर्णांक flag)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	काष्ठा buffer_info bi;
	पूर्णांक n;

	RFALSE(tb->FR[0] && B_LEVEL(tb->FR[0]) != DISK_LEAF_NODE_LEVEL + 1,
	       "vs- 12000: level: wrong FR %z", tb->FR[0]);
	RFALSE(tb->blknum[0] > 1,
	       "PAP-12005: tb->blknum == %d, can not be > 1", tb->blknum[0]);
	RFALSE(!tb->blknum[0] && !PATH_H_PPARENT(tb->tb_path, 0),
	       "PAP-12010: tree can not be empty");

	buffer_info_init_tbS0(tb, &bi);

	/* Delete or truncate the item */

	BUG_ON(flag != M_DELETE && flag != M_CUT);
	अगर (flag == M_DELETE)
		balance_leaf_when_delete_del(tb);
	अन्यथा /* M_CUT */
		balance_leaf_when_delete_cut(tb);


	/*
	 * the rule is that no shअगरting occurs unless by shअगरting
	 * a node can be मुक्तd
	 */
	n = B_NR_ITEMS(tbS0);


	/* L[0] takes part in balancing */
	अगर (tb->lnum[0])
		वापस balance_leaf_when_delete_left(tb);

	अगर (tb->rnum[0] == -1) अणु
		/* all contents of R[0] and S[0] will be in R[0] */
		leaf_shअगरt_right(tb, n, -1);
		reiserfs_invalidate_buffer(tb, tbS0);
		वापस 0;
	पूर्ण

	RFALSE(tb->rnum[0],
	       "PAP-12065: bad rnum parameter must be 0 (%d)", tb->rnum[0]);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक balance_leaf_insert_left(काष्ठा tree_balance *tb,
					     काष्ठा item_head *स्थिर ih,
					     स्थिर अक्षर * स्थिर body)
अणु
	पूर्णांक ret;
	काष्ठा buffer_info bi;
	पूर्णांक n = B_NR_ITEMS(tb->L[0]);
	अचिन्हित body_shअगरt_bytes = 0;

	अगर (tb->item_pos == tb->lnum[0] - 1 && tb->lbytes != -1) अणु
		/* part of new item falls पूर्णांकo L[0] */
		पूर्णांक new_item_len, shअगरt;

		ret = leaf_shअगरt_left(tb, tb->lnum[0] - 1, -1);

		/* Calculate item length to insert to S[0] */
		new_item_len = ih_item_len(ih) - tb->lbytes;

		/* Calculate and check item length to insert to L[0] */
		put_ih_item_len(ih, ih_item_len(ih) - new_item_len);

		RFALSE(ih_item_len(ih) <= 0,
		       "PAP-12080: there is nothing to insert into L[0]: "
		       "ih_item_len=%d", ih_item_len(ih));

		/* Insert new item पूर्णांकo L[0] */
		buffer_info_init_left(tb, &bi);
		leaf_insert_पूर्णांकo_buf(&bi, n + tb->item_pos - ret, ih, body,
			     min_t(पूर्णांक, tb->zeroes_num, ih_item_len(ih)));

		/*
		 * Calculate key component, item length and body to
		 * insert पूर्णांकo S[0]
		 */
		shअगरt = 0;
		अगर (is_indirect_le_ih(ih))
			shअगरt = tb->tb_sb->s_blocksize_bits - UNFM_P_SHIFT;

		add_le_ih_k_offset(ih, tb->lbytes << shअगरt);

		put_ih_item_len(ih, new_item_len);
		अगर (tb->lbytes > tb->zeroes_num) अणु
			body_shअगरt_bytes = tb->lbytes - tb->zeroes_num;
			tb->zeroes_num = 0;
		पूर्ण अन्यथा
			tb->zeroes_num -= tb->lbytes;

		RFALSE(ih_item_len(ih) <= 0,
		       "PAP-12085: there is nothing to insert into S[0]: "
		       "ih_item_len=%d", ih_item_len(ih));
	पूर्ण अन्यथा अणु
		/* new item in whole falls पूर्णांकo L[0] */
		/* Shअगरt lnum[0]-1 items to L[0] */
		ret = leaf_shअगरt_left(tb, tb->lnum[0] - 1, tb->lbytes);

		/* Insert new item पूर्णांकo L[0] */
		buffer_info_init_left(tb, &bi);
		leaf_insert_पूर्णांकo_buf(&bi, n + tb->item_pos - ret, ih, body,
				     tb->zeroes_num);
		tb->insert_size[0] = 0;
		tb->zeroes_num = 0;
	पूर्ण
	वापस body_shअगरt_bytes;
पूर्ण

अटल व्योम balance_leaf_paste_left_shअगरt_dirent(काष्ठा tree_balance *tb,
						 काष्ठा item_head * स्थिर ih,
						 स्थिर अक्षर * स्थिर body)
अणु
	पूर्णांक n = B_NR_ITEMS(tb->L[0]);
	काष्ठा buffer_info bi;

	RFALSE(tb->zeroes_num,
	       "PAP-12090: invalid parameter in case of a directory");

	/* directory item */
	अगर (tb->lbytes > tb->pos_in_item) अणु
		/* new directory entry falls पूर्णांकo L[0] */
		काष्ठा item_head *pasted;
		पूर्णांक ret, l_pos_in_item = tb->pos_in_item;

		/*
		 * Shअगरt lnum[0] - 1 items in whole.
		 * Shअगरt lbytes - 1 entries from given directory item
		 */
		ret = leaf_shअगरt_left(tb, tb->lnum[0], tb->lbytes - 1);
		अगर (ret && !tb->item_pos) अणु
			pasted = item_head(tb->L[0], B_NR_ITEMS(tb->L[0]) - 1);
			l_pos_in_item += ih_entry_count(pasted) -
					 (tb->lbytes - 1);
		पूर्ण

		/* Append given directory entry to directory item */
		buffer_info_init_left(tb, &bi);
		leaf_paste_in_buffer(&bi, n + tb->item_pos - ret,
				     l_pos_in_item, tb->insert_size[0],
				     body, tb->zeroes_num);

		/*
		 * previous string prepared space क्रम pasting new entry,
		 * following string pastes this entry
		 */

		/*
		 * when we have merge directory item, pos_in_item
		 * has been changed too
		 */

		/* paste new directory entry. 1 is entry number */
		leaf_paste_entries(&bi, n + tb->item_pos - ret,
				   l_pos_in_item, 1,
				   (काष्ठा reiserfs_de_head *) body,
				   body + DEH_SIZE, tb->insert_size[0]);
		tb->insert_size[0] = 0;
	पूर्ण अन्यथा अणु
		/* new directory item करोesn't fall पूर्णांकo L[0] */
		/*
		 * Shअगरt lnum[0]-1 items in whole. Shअगरt lbytes
		 * directory entries from directory item number lnum[0]
		 */
		leaf_shअगरt_left(tb, tb->lnum[0], tb->lbytes);
	पूर्ण

	/* Calculate new position to append in item body */
	tb->pos_in_item -= tb->lbytes;
पूर्ण

अटल अचिन्हित पूर्णांक balance_leaf_paste_left_shअगरt(काष्ठा tree_balance *tb,
						  काष्ठा item_head * स्थिर ih,
						  स्थिर अक्षर * स्थिर body)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n = B_NR_ITEMS(tb->L[0]);
	काष्ठा buffer_info bi;
	पूर्णांक body_shअगरt_bytes = 0;

	अगर (is_direntry_le_ih(item_head(tbS0, tb->item_pos))) अणु
		balance_leaf_paste_left_shअगरt_dirent(tb, ih, body);
		वापस 0;
	पूर्ण

	RFALSE(tb->lbytes <= 0,
	       "PAP-12095: there is nothing to shift to L[0]. "
	       "lbytes=%d", tb->lbytes);
	RFALSE(tb->pos_in_item != ih_item_len(item_head(tbS0, tb->item_pos)),
	       "PAP-12100: incorrect position to paste: "
	       "item_len=%d, pos_in_item=%d",
	       ih_item_len(item_head(tbS0, tb->item_pos)), tb->pos_in_item);

	/* appended item will be in L[0] in whole */
	अगर (tb->lbytes >= tb->pos_in_item) अणु
		काष्ठा item_head *tbS0_pos_ih, *tbL0_ih;
		काष्ठा item_head *tbS0_0_ih;
		काष्ठा reiserfs_key *left_delim_key;
		पूर्णांक ret, l_n, version, temp_l;

		tbS0_pos_ih = item_head(tbS0, tb->item_pos);
		tbS0_0_ih = item_head(tbS0, 0);

		/*
		 * this bytes number must be appended
		 * to the last item of L[h]
		 */
		l_n = tb->lbytes - tb->pos_in_item;

		/* Calculate new insert_size[0] */
		tb->insert_size[0] -= l_n;

		RFALSE(tb->insert_size[0] <= 0,
		       "PAP-12105: there is nothing to paste into "
		       "L[0]. insert_size=%d", tb->insert_size[0]);

		ret = leaf_shअगरt_left(tb, tb->lnum[0],
				      ih_item_len(tbS0_pos_ih));

		tbL0_ih = item_head(tb->L[0], n + tb->item_pos - ret);

		/* Append to body of item in L[0] */
		buffer_info_init_left(tb, &bi);
		leaf_paste_in_buffer(&bi, n + tb->item_pos - ret,
				     ih_item_len(tbL0_ih), l_n, body,
				     min_t(पूर्णांक, l_n, tb->zeroes_num));

		/*
		 * 0-th item in S0 can be only of सूचीECT type
		 * when l_n != 0
		 */
		temp_l = l_n;

		RFALSE(ih_item_len(tbS0_0_ih),
		       "PAP-12106: item length must be 0");
		RFALSE(comp_लघु_le_keys(&tbS0_0_ih->ih_key,
		       leaf_key(tb->L[0], n + tb->item_pos - ret)),
		       "PAP-12107: items must be of the same file");

		अगर (is_indirect_le_ih(tbL0_ih)) अणु
			पूर्णांक shअगरt = tb->tb_sb->s_blocksize_bits - UNFM_P_SHIFT;
			temp_l = l_n << shअगरt;
		पूर्ण
		/* update key of first item in S0 */
		version = ih_version(tbS0_0_ih);
		add_le_key_k_offset(version, &tbS0_0_ih->ih_key, temp_l);

		/* update left delimiting key */
		left_delim_key = पूर्णांकernal_key(tb->CFL[0], tb->lkey[0]);
		add_le_key_k_offset(version, left_delim_key, temp_l);

		/*
		 * Calculate new body, position in item and
		 * insert_size[0]
		 */
		अगर (l_n > tb->zeroes_num) अणु
			body_shअगरt_bytes = l_n - tb->zeroes_num;
			tb->zeroes_num = 0;
		पूर्ण अन्यथा
			tb->zeroes_num -= l_n;
		tb->pos_in_item = 0;

		RFALSE(comp_लघु_le_keys(&tbS0_0_ih->ih_key,
					  leaf_key(tb->L[0],
						 B_NR_ITEMS(tb->L[0]) - 1)) ||
		       !op_is_left_mergeable(leaf_key(tbS0, 0), tbS0->b_size) ||
		       !op_is_left_mergeable(left_delim_key, tbS0->b_size),
		       "PAP-12120: item must be merge-able with left "
		       "neighboring item");
	पूर्ण अन्यथा अणु
		/* only part of the appended item will be in L[0] */

		/* Calculate position in item क्रम append in S[0] */
		tb->pos_in_item -= tb->lbytes;

		RFALSE(tb->pos_in_item <= 0,
		       "PAP-12125: no place for paste. pos_in_item=%d",
		       tb->pos_in_item);

		/*
		 * Shअगरt lnum[0] - 1 items in whole.
		 * Shअगरt lbytes - 1 byte from item number lnum[0]
		 */
		leaf_shअगरt_left(tb, tb->lnum[0], tb->lbytes);
	पूर्ण
	वापस body_shअगरt_bytes;
पूर्ण


/* appended item will be in L[0] in whole */
अटल व्योम balance_leaf_paste_left_whole(काष्ठा tree_balance *tb,
					  काष्ठा item_head * स्थिर ih,
					  स्थिर अक्षर * स्थिर body)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n = B_NR_ITEMS(tb->L[0]);
	काष्ठा buffer_info bi;
	काष्ठा item_head *pasted;
	पूर्णांक ret;

	/* अगर we paste पूर्णांकo first item of S[0] and it is left mergable */
	अगर (!tb->item_pos &&
	    op_is_left_mergeable(leaf_key(tbS0, 0), tbS0->b_size)) अणु
		/*
		 * then increment pos_in_item by the size of the
		 * last item in L[0]
		 */
		pasted = item_head(tb->L[0], n - 1);
		अगर (is_direntry_le_ih(pasted))
			tb->pos_in_item += ih_entry_count(pasted);
		अन्यथा
			tb->pos_in_item += ih_item_len(pasted);
	पूर्ण

	/*
	 * Shअगरt lnum[0] - 1 items in whole.
	 * Shअगरt lbytes - 1 byte from item number lnum[0]
	 */
	ret = leaf_shअगरt_left(tb, tb->lnum[0], tb->lbytes);

	/* Append to body of item in L[0] */
	buffer_info_init_left(tb, &bi);
	leaf_paste_in_buffer(&bi, n + tb->item_pos - ret, tb->pos_in_item,
			     tb->insert_size[0], body, tb->zeroes_num);

	/* अगर appended item is directory, paste entry */
	pasted = item_head(tb->L[0], n + tb->item_pos - ret);
	अगर (is_direntry_le_ih(pasted))
		leaf_paste_entries(&bi, n + tb->item_pos - ret,
				   tb->pos_in_item, 1,
				   (काष्ठा reiserfs_de_head *)body,
				   body + DEH_SIZE, tb->insert_size[0]);

	/*
	 * अगर appended item is indirect item, put unक्रमmatted node
	 * पूर्णांकo un list
	 */
	अगर (is_indirect_le_ih(pasted))
		set_ih_मुक्त_space(pasted, 0);

	tb->insert_size[0] = 0;
	tb->zeroes_num = 0;
पूर्ण

अटल अचिन्हित पूर्णांक balance_leaf_paste_left(काष्ठा tree_balance *tb,
					    काष्ठा item_head * स्थिर ih,
					    स्थिर अक्षर * स्थिर body)
अणु
	/* we must shअगरt the part of the appended item */
	अगर (tb->item_pos == tb->lnum[0] - 1 && tb->lbytes != -1)
		वापस balance_leaf_paste_left_shअगरt(tb, ih, body);
	अन्यथा
		balance_leaf_paste_left_whole(tb, ih, body);
	वापस 0;
पूर्ण

/* Shअगरt lnum[0] items from S[0] to the left neighbor L[0] */
अटल अचिन्हित पूर्णांक balance_leaf_left(काष्ठा tree_balance *tb,
				      काष्ठा item_head * स्थिर ih,
				      स्थिर अक्षर * स्थिर body, पूर्णांक flag)
अणु
	अगर (tb->lnum[0] <= 0)
		वापस 0;

	/* new item or it part falls to L[0], shअगरt it too */
	अगर (tb->item_pos < tb->lnum[0]) अणु
		BUG_ON(flag != M_INSERT && flag != M_PASTE);

		अगर (flag == M_INSERT)
			वापस balance_leaf_insert_left(tb, ih, body);
		अन्यथा /* M_PASTE */
			वापस balance_leaf_paste_left(tb, ih, body);
	पूर्ण अन्यथा
		/* new item करोesn't fall पूर्णांकo L[0] */
		leaf_shअगरt_left(tb, tb->lnum[0], tb->lbytes);
	वापस 0;
पूर्ण


अटल व्योम balance_leaf_insert_right(काष्ठा tree_balance *tb,
				      काष्ठा item_head * स्थिर ih,
				      स्थिर अक्षर * स्थिर body)
अणु

	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n = B_NR_ITEMS(tbS0);
	काष्ठा buffer_info bi;

	/* new item or part of it करोesn't fall पूर्णांकo R[0] */
	अगर (n - tb->rnum[0] >= tb->item_pos) अणु
		leaf_shअगरt_right(tb, tb->rnum[0], tb->rbytes);
		वापस;
	पूर्ण

	/* new item or its part falls to R[0] */

	/* part of new item falls पूर्णांकo R[0] */
	अगर (tb->item_pos == n - tb->rnum[0] + 1 && tb->rbytes != -1) अणु
		loff_t old_key_comp, old_len, r_zeroes_number;
		स्थिर अक्षर *r_body;
		पूर्णांक shअगरt;
		loff_t offset;

		leaf_shअगरt_right(tb, tb->rnum[0] - 1, -1);

		/* Remember key component and item length */
		old_key_comp = le_ih_k_offset(ih);
		old_len = ih_item_len(ih);

		/*
		 * Calculate key component and item length to insert
		 * पूर्णांकo R[0]
		 */
		shअगरt = 0;
		अगर (is_indirect_le_ih(ih))
			shअगरt = tb->tb_sb->s_blocksize_bits - UNFM_P_SHIFT;
		offset = le_ih_k_offset(ih) + ((old_len - tb->rbytes) << shअगरt);
		set_le_ih_k_offset(ih, offset);
		put_ih_item_len(ih, tb->rbytes);

		/* Insert part of the item पूर्णांकo R[0] */
		buffer_info_init_right(tb, &bi);
		अगर ((old_len - tb->rbytes) > tb->zeroes_num) अणु
			r_zeroes_number = 0;
			r_body = body + (old_len - tb->rbytes) - tb->zeroes_num;
		पूर्ण अन्यथा अणु
			r_body = body;
			r_zeroes_number = tb->zeroes_num -
					  (old_len - tb->rbytes);
			tb->zeroes_num -= r_zeroes_number;
		पूर्ण

		leaf_insert_पूर्णांकo_buf(&bi, 0, ih, r_body, r_zeroes_number);

		/* Replace right delimiting key by first key in R[0] */
		replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);

		/*
		 * Calculate key component and item length to
		 * insert पूर्णांकo S[0]
		 */
		set_le_ih_k_offset(ih, old_key_comp);
		put_ih_item_len(ih, old_len - tb->rbytes);

		tb->insert_size[0] -= tb->rbytes;

	पूर्ण अन्यथा अणु
		/* whole new item falls पूर्णांकo R[0] */

		/* Shअगरt rnum[0]-1 items to R[0] */
		leaf_shअगरt_right(tb, tb->rnum[0] - 1, tb->rbytes);

		/* Insert new item पूर्णांकo R[0] */
		buffer_info_init_right(tb, &bi);
		leaf_insert_पूर्णांकo_buf(&bi, tb->item_pos - n + tb->rnum[0] - 1,
				     ih, body, tb->zeroes_num);

		अगर (tb->item_pos - n + tb->rnum[0] - 1 == 0)
			replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);

		tb->zeroes_num = tb->insert_size[0] = 0;
	पूर्ण
पूर्ण


अटल व्योम balance_leaf_paste_right_shअगरt_dirent(काष्ठा tree_balance *tb,
				     काष्ठा item_head * स्थिर ih,
				     स्थिर अक्षर * स्थिर body)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	काष्ठा buffer_info bi;
	पूर्णांक entry_count;

	RFALSE(tb->zeroes_num,
	       "PAP-12145: invalid parameter in case of a directory");
	entry_count = ih_entry_count(item_head(tbS0, tb->item_pos));

	/* new directory entry falls पूर्णांकo R[0] */
	अगर (entry_count - tb->rbytes < tb->pos_in_item) अणु
		पूर्णांक paste_entry_position;

		RFALSE(tb->rbytes - 1 >= entry_count || !tb->insert_size[0],
		       "PAP-12150: no enough of entries to shift to R[0]: "
		       "rbytes=%d, entry_count=%d", tb->rbytes, entry_count);

		/*
		 * Shअगरt rnum[0]-1 items in whole.
		 * Shअगरt rbytes-1 directory entries from directory
		 * item number rnum[0]
		 */
		leaf_shअगरt_right(tb, tb->rnum[0], tb->rbytes - 1);

		/* Paste given directory entry to directory item */
		paste_entry_position = tb->pos_in_item - entry_count +
				       tb->rbytes - 1;
		buffer_info_init_right(tb, &bi);
		leaf_paste_in_buffer(&bi, 0, paste_entry_position,
				     tb->insert_size[0], body, tb->zeroes_num);

		/* paste entry */
		leaf_paste_entries(&bi, 0, paste_entry_position, 1,
				   (काष्ठा reiserfs_de_head *) body,
				   body + DEH_SIZE, tb->insert_size[0]);

		/* change delimiting keys */
		अगर (paste_entry_position == 0)
			replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);

		tb->insert_size[0] = 0;
		tb->pos_in_item++;
	पूर्ण अन्यथा अणु
		/* new directory entry करोesn't fall पूर्णांकo R[0] */
		leaf_shअगरt_right(tb, tb->rnum[0], tb->rbytes);
	पूर्ण
पूर्ण

अटल व्योम balance_leaf_paste_right_shअगरt(काष्ठा tree_balance *tb,
				     काष्ठा item_head * स्थिर ih,
				     स्थिर अक्षर * स्थिर body)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n_shअगरt, n_rem, r_zeroes_number, version;
	अचिन्हित दीर्घ temp_rem;
	स्थिर अक्षर *r_body;
	काष्ठा buffer_info bi;

	/* we append to directory item */
	अगर (is_direntry_le_ih(item_head(tbS0, tb->item_pos))) अणु
		balance_leaf_paste_right_shअगरt_dirent(tb, ih, body);
		वापस;
	पूर्ण

	/* regular object */

	/*
	 * Calculate number of bytes which must be shअगरted
	 * from appended item
	 */
	n_shअगरt = tb->rbytes - tb->insert_size[0];
	अगर (n_shअगरt < 0)
		n_shअगरt = 0;

	RFALSE(tb->pos_in_item != ih_item_len(item_head(tbS0, tb->item_pos)),
	       "PAP-12155: invalid position to paste. ih_item_len=%d, "
	       "pos_in_item=%d", tb->pos_in_item,
	       ih_item_len(item_head(tbS0, tb->item_pos)));

	leaf_shअगरt_right(tb, tb->rnum[0], n_shअगरt);

	/*
	 * Calculate number of bytes which must reमुख्य in body
	 * after appending to R[0]
	 */
	n_rem = tb->insert_size[0] - tb->rbytes;
	अगर (n_rem < 0)
		n_rem = 0;

	temp_rem = n_rem;

	version = ih_version(item_head(tb->R[0], 0));

	अगर (is_indirect_le_key(version, leaf_key(tb->R[0], 0))) अणु
		पूर्णांक shअगरt = tb->tb_sb->s_blocksize_bits - UNFM_P_SHIFT;
		temp_rem = n_rem << shअगरt;
	पूर्ण

	add_le_key_k_offset(version, leaf_key(tb->R[0], 0), temp_rem);
	add_le_key_k_offset(version, पूर्णांकernal_key(tb->CFR[0], tb->rkey[0]),
			    temp_rem);

	करो_balance_mark_पूर्णांकernal_dirty(tb, tb->CFR[0], 0);

	/* Append part of body पूर्णांकo R[0] */
	buffer_info_init_right(tb, &bi);
	अगर (n_rem > tb->zeroes_num) अणु
		r_zeroes_number = 0;
		r_body = body + n_rem - tb->zeroes_num;
	पूर्ण अन्यथा अणु
		r_body = body;
		r_zeroes_number = tb->zeroes_num - n_rem;
		tb->zeroes_num -= r_zeroes_number;
	पूर्ण

	leaf_paste_in_buffer(&bi, 0, n_shअगरt, tb->insert_size[0] - n_rem,
			     r_body, r_zeroes_number);

	अगर (is_indirect_le_ih(item_head(tb->R[0], 0)))
		set_ih_मुक्त_space(item_head(tb->R[0], 0), 0);

	tb->insert_size[0] = n_rem;
	अगर (!n_rem)
		tb->pos_in_item++;
पूर्ण

अटल व्योम balance_leaf_paste_right_whole(काष्ठा tree_balance *tb,
				     काष्ठा item_head * स्थिर ih,
				     स्थिर अक्षर * स्थिर body)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n = B_NR_ITEMS(tbS0);
	काष्ठा item_head *pasted;
	काष्ठा buffer_info bi;

	buffer_info_init_right(tb, &bi);
	leaf_shअगरt_right(tb, tb->rnum[0], tb->rbytes);

	/* append item in R[0] */
	अगर (tb->pos_in_item >= 0) अणु
		buffer_info_init_right(tb, &bi);
		leaf_paste_in_buffer(&bi, tb->item_pos - n + tb->rnum[0],
				     tb->pos_in_item, tb->insert_size[0], body,
				     tb->zeroes_num);
	पूर्ण

	/* paste new entry, अगर item is directory item */
	pasted = item_head(tb->R[0], tb->item_pos - n + tb->rnum[0]);
	अगर (is_direntry_le_ih(pasted) && tb->pos_in_item >= 0) अणु
		leaf_paste_entries(&bi, tb->item_pos - n + tb->rnum[0],
				   tb->pos_in_item, 1,
				   (काष्ठा reiserfs_de_head *)body,
				   body + DEH_SIZE, tb->insert_size[0]);

		अगर (!tb->pos_in_item) अणु

			RFALSE(tb->item_pos - n + tb->rnum[0],
			       "PAP-12165: directory item must be first "
			       "item of node when pasting is in 0th position");

			/* update delimiting keys */
			replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);
		पूर्ण
	पूर्ण

	अगर (is_indirect_le_ih(pasted))
		set_ih_मुक्त_space(pasted, 0);
	tb->zeroes_num = tb->insert_size[0] = 0;
पूर्ण

अटल व्योम balance_leaf_paste_right(काष्ठा tree_balance *tb,
				     काष्ठा item_head * स्थिर ih,
				     स्थिर अक्षर * स्थिर body)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n = B_NR_ITEMS(tbS0);

	/* new item करोesn't fall पूर्णांकo R[0] */
	अगर (n - tb->rnum[0] > tb->item_pos) अणु
		leaf_shअगरt_right(tb, tb->rnum[0], tb->rbytes);
		वापस;
	पूर्ण

	/* pasted item or part of it falls to R[0] */

	अगर (tb->item_pos == n - tb->rnum[0] && tb->rbytes != -1)
		/* we must shअगरt the part of the appended item */
		balance_leaf_paste_right_shअगरt(tb, ih, body);
	अन्यथा
		/* pasted item in whole falls पूर्णांकo R[0] */
		balance_leaf_paste_right_whole(tb, ih, body);
पूर्ण

/* shअगरt rnum[0] items from S[0] to the right neighbor R[0] */
अटल व्योम balance_leaf_right(काष्ठा tree_balance *tb,
			       काष्ठा item_head * स्थिर ih,
			       स्थिर अक्षर * स्थिर body, पूर्णांक flag)
अणु
	अगर (tb->rnum[0] <= 0)
		वापस;

	BUG_ON(flag != M_INSERT && flag != M_PASTE);

	अगर (flag == M_INSERT)
		balance_leaf_insert_right(tb, ih, body);
	अन्यथा /* M_PASTE */
		balance_leaf_paste_right(tb, ih, body);
पूर्ण

अटल व्योम balance_leaf_new_nodes_insert(काष्ठा tree_balance *tb,
					  काष्ठा item_head * स्थिर ih,
					  स्थिर अक्षर * स्थिर body,
					  काष्ठा item_head *insert_key,
					  काष्ठा buffer_head **insert_ptr,
					  पूर्णांक i)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n = B_NR_ITEMS(tbS0);
	काष्ठा buffer_info bi;
	पूर्णांक shअगरt;

	/* new item or it part करोn't falls पूर्णांकo S_new[i] */
	अगर (n - tb->snum[i] >= tb->item_pos) अणु
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb,
				tb->snum[i], tb->sbytes[i], tb->S_new[i]);
		वापस;
	पूर्ण

	/* new item or it's part falls to first new node S_new[i] */

	/* part of new item falls पूर्णांकo S_new[i] */
	अगर (tb->item_pos == n - tb->snum[i] + 1 && tb->sbytes[i] != -1) अणु
		पूर्णांक old_key_comp, old_len, r_zeroes_number;
		स्थिर अक्षर *r_body;

		/* Move snum[i]-1 items from S[0] to S_new[i] */
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i] - 1, -1,
				tb->S_new[i]);

		/* Remember key component and item length */
		old_key_comp = le_ih_k_offset(ih);
		old_len = ih_item_len(ih);

		/*
		 * Calculate key component and item length to insert
		 * पूर्णांकo S_new[i]
		 */
		shअगरt = 0;
		अगर (is_indirect_le_ih(ih))
			shअगरt = tb->tb_sb->s_blocksize_bits - UNFM_P_SHIFT;
		set_le_ih_k_offset(ih,
				   le_ih_k_offset(ih) +
				   ((old_len - tb->sbytes[i]) << shअगरt));

		put_ih_item_len(ih, tb->sbytes[i]);

		/* Insert part of the item पूर्णांकo S_new[i] beक्रमe 0-th item */
		buffer_info_init_bh(tb, &bi, tb->S_new[i]);

		अगर ((old_len - tb->sbytes[i]) > tb->zeroes_num) अणु
			r_zeroes_number = 0;
			r_body = body + (old_len - tb->sbytes[i]) -
					 tb->zeroes_num;
		पूर्ण अन्यथा अणु
			r_body = body;
			r_zeroes_number = tb->zeroes_num - (old_len -
					  tb->sbytes[i]);
			tb->zeroes_num -= r_zeroes_number;
		पूर्ण

		leaf_insert_पूर्णांकo_buf(&bi, 0, ih, r_body, r_zeroes_number);

		/*
		 * Calculate key component and item length to
		 * insert पूर्णांकo S[i]
		 */
		set_le_ih_k_offset(ih, old_key_comp);
		put_ih_item_len(ih, old_len - tb->sbytes[i]);
		tb->insert_size[0] -= tb->sbytes[i];
	पूर्ण अन्यथा अणु
		/* whole new item falls पूर्णांकo S_new[i] */

		/*
		 * Shअगरt snum[0] - 1 items to S_new[i]
		 * (sbytes[i] of split item)
		 */
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb,
				tb->snum[i] - 1, tb->sbytes[i], tb->S_new[i]);

		/* Insert new item पूर्णांकo S_new[i] */
		buffer_info_init_bh(tb, &bi, tb->S_new[i]);
		leaf_insert_पूर्णांकo_buf(&bi, tb->item_pos - n + tb->snum[i] - 1,
				     ih, body, tb->zeroes_num);

		tb->zeroes_num = tb->insert_size[0] = 0;
	पूर्ण
पूर्ण

/* we append to directory item */
अटल व्योम balance_leaf_new_nodes_paste_dirent(काष्ठा tree_balance *tb,
					 काष्ठा item_head * स्थिर ih,
					 स्थिर अक्षर * स्थिर body,
					 काष्ठा item_head *insert_key,
					 काष्ठा buffer_head **insert_ptr,
					 पूर्णांक i)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	काष्ठा item_head *aux_ih = item_head(tbS0, tb->item_pos);
	पूर्णांक entry_count = ih_entry_count(aux_ih);
	काष्ठा buffer_info bi;

	अगर (entry_count - tb->sbytes[i] < tb->pos_in_item &&
	    tb->pos_in_item <= entry_count) अणु
		/* new directory entry falls पूर्णांकo S_new[i] */

		RFALSE(!tb->insert_size[0],
		       "PAP-12215: insert_size is already 0");
		RFALSE(tb->sbytes[i] - 1 >= entry_count,
		       "PAP-12220: there are no so much entries (%d), only %d",
		       tb->sbytes[i] - 1, entry_count);

		/*
		 * Shअगरt snum[i]-1 items in whole.
		 * Shअगरt sbytes[i] directory entries
		 * from directory item number snum[i]
		 */
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i],
				tb->sbytes[i] - 1, tb->S_new[i]);

		/*
		 * Paste given directory entry to
		 * directory item
		 */
		buffer_info_init_bh(tb, &bi, tb->S_new[i]);
		leaf_paste_in_buffer(&bi, 0, tb->pos_in_item - entry_count +
				     tb->sbytes[i] - 1, tb->insert_size[0],
				     body, tb->zeroes_num);

		/* paste new directory entry */
		leaf_paste_entries(&bi, 0, tb->pos_in_item - entry_count +
				   tb->sbytes[i] - 1, 1,
				   (काष्ठा reiserfs_de_head *) body,
				   body + DEH_SIZE, tb->insert_size[0]);

		tb->insert_size[0] = 0;
		tb->pos_in_item++;
	पूर्ण अन्यथा अणु
		/* new directory entry करोesn't fall पूर्णांकo S_new[i] */
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i],
				tb->sbytes[i], tb->S_new[i]);
	पूर्ण

पूर्ण

अटल व्योम balance_leaf_new_nodes_paste_shअगरt(काष्ठा tree_balance *tb,
					 काष्ठा item_head * स्थिर ih,
					 स्थिर अक्षर * स्थिर body,
					 काष्ठा item_head *insert_key,
					 काष्ठा buffer_head **insert_ptr,
					 पूर्णांक i)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	काष्ठा item_head *aux_ih = item_head(tbS0, tb->item_pos);
	पूर्णांक n_shअगरt, n_rem, r_zeroes_number, shअगरt;
	स्थिर अक्षर *r_body;
	काष्ठा item_head *पंचांगp;
	काष्ठा buffer_info bi;

	RFALSE(ih, "PAP-12210: ih must be 0");

	अगर (is_direntry_le_ih(aux_ih)) अणु
		balance_leaf_new_nodes_paste_dirent(tb, ih, body, insert_key,
						    insert_ptr, i);
		वापस;
	पूर्ण

	/* regular object */


	RFALSE(tb->pos_in_item != ih_item_len(item_head(tbS0, tb->item_pos)) ||
	       tb->insert_size[0] <= 0,
	       "PAP-12225: item too short or insert_size <= 0");

	/*
	 * Calculate number of bytes which must be shअगरted from appended item
	 */
	n_shअगरt = tb->sbytes[i] - tb->insert_size[0];
	अगर (n_shअगरt < 0)
		n_shअगरt = 0;
	leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i], n_shअगरt,
			tb->S_new[i]);

	/*
	 * Calculate number of bytes which must reमुख्य in body after
	 * append to S_new[i]
	 */
	n_rem = tb->insert_size[0] - tb->sbytes[i];
	अगर (n_rem < 0)
		n_rem = 0;

	/* Append part of body पूर्णांकo S_new[0] */
	buffer_info_init_bh(tb, &bi, tb->S_new[i]);
	अगर (n_rem > tb->zeroes_num) अणु
		r_zeroes_number = 0;
		r_body = body + n_rem - tb->zeroes_num;
	पूर्ण अन्यथा अणु
		r_body = body;
		r_zeroes_number = tb->zeroes_num - n_rem;
		tb->zeroes_num -= r_zeroes_number;
	पूर्ण

	leaf_paste_in_buffer(&bi, 0, n_shअगरt, tb->insert_size[0] - n_rem,
			     r_body, r_zeroes_number);

	पंचांगp = item_head(tb->S_new[i], 0);
	shअगरt = 0;
	अगर (is_indirect_le_ih(पंचांगp)) अणु
		set_ih_मुक्त_space(पंचांगp, 0);
		shअगरt = tb->tb_sb->s_blocksize_bits - UNFM_P_SHIFT;
	पूर्ण
	add_le_ih_k_offset(पंचांगp, n_rem << shअगरt);

	tb->insert_size[0] = n_rem;
	अगर (!n_rem)
		tb->pos_in_item++;
पूर्ण

अटल व्योम balance_leaf_new_nodes_paste_whole(काष्ठा tree_balance *tb,
					       काष्ठा item_head * स्थिर ih,
					       स्थिर अक्षर * स्थिर body,
					       काष्ठा item_head *insert_key,
					       काष्ठा buffer_head **insert_ptr,
					       पूर्णांक i)

अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n = B_NR_ITEMS(tbS0);
	पूर्णांक leaf_mi;
	काष्ठा item_head *pasted;
	काष्ठा buffer_info bi;

#अगर_घोषित CONFIG_REISERFS_CHECK
	काष्ठा item_head *ih_check = item_head(tbS0, tb->item_pos);

	अगर (!is_direntry_le_ih(ih_check) &&
	    (tb->pos_in_item != ih_item_len(ih_check) ||
	    tb->insert_size[0] <= 0))
		reiserfs_panic(tb->tb_sb,
			     "PAP-12235",
			     "pos_in_item must be equal to ih_item_len");
#पूर्ण_अगर

	leaf_mi = leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i],
				  tb->sbytes[i], tb->S_new[i]);

	RFALSE(leaf_mi,
	       "PAP-12240: unexpected value returned by leaf_move_items (%d)",
	       leaf_mi);

	/* paste पूर्णांकo item */
	buffer_info_init_bh(tb, &bi, tb->S_new[i]);
	leaf_paste_in_buffer(&bi, tb->item_pos - n + tb->snum[i],
			     tb->pos_in_item, tb->insert_size[0],
			     body, tb->zeroes_num);

	pasted = item_head(tb->S_new[i], tb->item_pos - n +
			   tb->snum[i]);
	अगर (is_direntry_le_ih(pasted))
		leaf_paste_entries(&bi, tb->item_pos - n + tb->snum[i],
				   tb->pos_in_item, 1,
				   (काष्ठा reiserfs_de_head *)body,
				   body + DEH_SIZE, tb->insert_size[0]);

	/* अगर we paste to indirect item update ih_मुक्त_space */
	अगर (is_indirect_le_ih(pasted))
		set_ih_मुक्त_space(pasted, 0);

	tb->zeroes_num = tb->insert_size[0] = 0;

पूर्ण
अटल व्योम balance_leaf_new_nodes_paste(काष्ठा tree_balance *tb,
					 काष्ठा item_head * स्थिर ih,
					 स्थिर अक्षर * स्थिर body,
					 काष्ठा item_head *insert_key,
					 काष्ठा buffer_head **insert_ptr,
					 पूर्णांक i)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक n = B_NR_ITEMS(tbS0);

	/* pasted item करोesn't fall पूर्णांकo S_new[i] */
	अगर (n - tb->snum[i] > tb->item_pos) अणु
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb,
				tb->snum[i], tb->sbytes[i], tb->S_new[i]);
		वापस;
	पूर्ण

	/* pasted item or part अगर it falls to S_new[i] */

	अगर (tb->item_pos == n - tb->snum[i] && tb->sbytes[i] != -1)
		/* we must shअगरt part of the appended item */
		balance_leaf_new_nodes_paste_shअगरt(tb, ih, body, insert_key,
						   insert_ptr, i);
	अन्यथा
		/* item falls wholly पूर्णांकo S_new[i] */
		balance_leaf_new_nodes_paste_whole(tb, ih, body, insert_key,
						   insert_ptr, i);
पूर्ण

/* Fill new nodes that appear in place of S[0] */
अटल व्योम balance_leaf_new_nodes(काष्ठा tree_balance *tb,
				   काष्ठा item_head * स्थिर ih,
				   स्थिर अक्षर * स्थिर body,
				   काष्ठा item_head *insert_key,
				   काष्ठा buffer_head **insert_ptr,
				   पूर्णांक flag)
अणु
	पूर्णांक i;
	क्रम (i = tb->blknum[0] - 2; i >= 0; i--) अणु
		BUG_ON(flag != M_INSERT && flag != M_PASTE);

		RFALSE(!tb->snum[i],
		       "PAP-12200: snum[%d] == %d. Must be > 0", i,
		       tb->snum[i]);

		/* here we shअगरt from S to S_new nodes */

		tb->S_new[i] = get_FEB(tb);

		/* initialized block type and tree level */
		set_blkh_level(B_BLK_HEAD(tb->S_new[i]), DISK_LEAF_NODE_LEVEL);

		अगर (flag == M_INSERT)
			balance_leaf_new_nodes_insert(tb, ih, body, insert_key,
						      insert_ptr, i);
		अन्यथा /* M_PASTE */
			balance_leaf_new_nodes_paste(tb, ih, body, insert_key,
						     insert_ptr, i);

		स_नकल(insert_key + i, leaf_key(tb->S_new[i], 0), KEY_SIZE);
		insert_ptr[i] = tb->S_new[i];

		RFALSE(!buffer_journaled(tb->S_new[i])
		       || buffer_journal_dirty(tb->S_new[i])
		       || buffer_dirty(tb->S_new[i]),
		       "PAP-12247: S_new[%d] : (%b)",
		       i, tb->S_new[i]);
	पूर्ण
पूर्ण

अटल व्योम balance_leaf_finish_node_insert(काष्ठा tree_balance *tb,
					    काष्ठा item_head * स्थिर ih,
					    स्थिर अक्षर * स्थिर body)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	काष्ठा buffer_info bi;
	buffer_info_init_tbS0(tb, &bi);
	leaf_insert_पूर्णांकo_buf(&bi, tb->item_pos, ih, body, tb->zeroes_num);

	/* If we insert the first key change the delimiting key */
	अगर (tb->item_pos == 0) अणु
		अगर (tb->CFL[0])	/* can be 0 in reiserfsck */
			replace_key(tb, tb->CFL[0], tb->lkey[0], tbS0, 0);

	पूर्ण
पूर्ण

अटल व्योम balance_leaf_finish_node_paste_dirent(काष्ठा tree_balance *tb,
						  काष्ठा item_head * स्थिर ih,
						  स्थिर अक्षर * स्थिर body)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	काष्ठा item_head *pasted = item_head(tbS0, tb->item_pos);
	काष्ठा buffer_info bi;

	अगर (tb->pos_in_item >= 0 && tb->pos_in_item <= ih_entry_count(pasted)) अणु
		RFALSE(!tb->insert_size[0],
		       "PAP-12260: insert_size is 0 already");

		/* prepare space */
		buffer_info_init_tbS0(tb, &bi);
		leaf_paste_in_buffer(&bi, tb->item_pos, tb->pos_in_item,
				     tb->insert_size[0], body, tb->zeroes_num);

		/* paste entry */
		leaf_paste_entries(&bi, tb->item_pos, tb->pos_in_item, 1,
				   (काष्ठा reiserfs_de_head *)body,
				   body + DEH_SIZE, tb->insert_size[0]);

		अगर (!tb->item_pos && !tb->pos_in_item) अणु
			RFALSE(!tb->CFL[0] || !tb->L[0],
			       "PAP-12270: CFL[0]/L[0] must  be specified");
			अगर (tb->CFL[0])
				replace_key(tb, tb->CFL[0], tb->lkey[0],
					    tbS0, 0);
		पूर्ण

		tb->insert_size[0] = 0;
	पूर्ण
पूर्ण

अटल व्योम balance_leaf_finish_node_paste(काष्ठा tree_balance *tb,
					   काष्ठा item_head * स्थिर ih,
					   स्थिर अक्षर * स्थिर body)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	काष्ठा buffer_info bi;
	काष्ठा item_head *pasted = item_head(tbS0, tb->item_pos);

	/* when directory, may be new entry alपढ़ोy pasted */
	अगर (is_direntry_le_ih(pasted)) अणु
		balance_leaf_finish_node_paste_dirent(tb, ih, body);
		वापस;
	पूर्ण

	/* regular object */

	अगर (tb->pos_in_item == ih_item_len(pasted)) अणु
		RFALSE(tb->insert_size[0] <= 0,
		       "PAP-12275: insert size must not be %d",
		       tb->insert_size[0]);
		buffer_info_init_tbS0(tb, &bi);
		leaf_paste_in_buffer(&bi, tb->item_pos,
				     tb->pos_in_item, tb->insert_size[0], body,
				     tb->zeroes_num);

		अगर (is_indirect_le_ih(pasted))
			set_ih_मुक्त_space(pasted, 0);

		tb->insert_size[0] = 0;
	पूर्ण
#अगर_घोषित CONFIG_REISERFS_CHECK
	अन्यथा अगर (tb->insert_size[0]) अणु
		prपूर्णांक_cur_tb("12285");
		reiserfs_panic(tb->tb_sb, "PAP-12285",
		    "insert_size must be 0 (%d)", tb->insert_size[0]);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * अगर the affected item was not wholly shअगरted then we
 * perक्रमm all necessary operations on that part or whole
 * of the affected item which reमुख्यs in S
 */
अटल व्योम balance_leaf_finish_node(काष्ठा tree_balance *tb,
				      काष्ठा item_head * स्थिर ih,
				      स्थिर अक्षर * स्थिर body, पूर्णांक flag)
अणु
	/* अगर we must insert or append पूर्णांकo buffer S[0] */
	अगर (0 <= tb->item_pos && tb->item_pos < tb->s0num) अणु
		अगर (flag == M_INSERT)
			balance_leaf_finish_node_insert(tb, ih, body);
		अन्यथा /* M_PASTE */
			balance_leaf_finish_node_paste(tb, ih, body);
	पूर्ण
पूर्ण

/**
 * balance_leaf - reiserfs tree balancing algorithm
 * @tb: tree balance state
 * @ih: item header of inserted item (little endian)
 * @body: body of inserted item or bytes to paste
 * @flag: i - insert, d - delete, c - cut, p - paste (see करो_balance)
 * passed back:
 * @insert_key: key to insert new nodes
 * @insert_ptr: array of nodes to insert at the next level
 *
 * In our processing of one level we someबार determine what must be
 * inserted पूर्णांकo the next higher level.  This insertion consists of a
 * key or two keys and their corresponding poपूर्णांकers.
 */
अटल पूर्णांक balance_leaf(काष्ठा tree_balance *tb, काष्ठा item_head *ih,
			स्थिर अक्षर *body, पूर्णांक flag,
			काष्ठा item_head *insert_key,
			काष्ठा buffer_head **insert_ptr)
अणु
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);

	PROC_INFO_INC(tb->tb_sb, balance_at[0]);

	/* Make balance in हाल insert_size[0] < 0 */
	अगर (tb->insert_size[0] < 0)
		वापस balance_leaf_when_delete(tb, flag);

	tb->item_pos = PATH_LAST_POSITION(tb->tb_path),
	tb->pos_in_item = tb->tb_path->pos_in_item,
	tb->zeroes_num = 0;
	अगर (flag == M_INSERT && !body)
		tb->zeroes_num = ih_item_len(ih);

	/*
	 * क्रम indirect item pos_in_item is measured in unक्रमmatted node
	 * poपूर्णांकers. Recalculate to bytes
	 */
	अगर (flag != M_INSERT
	    && is_indirect_le_ih(item_head(tbS0, tb->item_pos)))
		tb->pos_in_item *= UNFM_P_SIZE;

	body += balance_leaf_left(tb, ih, body, flag);

	/* tb->lnum[0] > 0 */
	/* Calculate new item position */
	tb->item_pos -= (tb->lnum[0] - ((tb->lbytes != -1) ? 1 : 0));

	balance_leaf_right(tb, ih, body, flag);

	/* tb->rnum[0] > 0 */
	RFALSE(tb->blknum[0] > 3,
	       "PAP-12180: blknum can not be %d. It must be <= 3", tb->blknum[0]);
	RFALSE(tb->blknum[0] < 0,
	       "PAP-12185: blknum can not be %d. It must be >= 0", tb->blknum[0]);

	/*
	 * अगर जबतक adding to a node we discover that it is possible to split
	 * it in two, and merge the left part पूर्णांकo the left neighbor and the
	 * right part पूर्णांकo the right neighbor, eliminating the node
	 */
	अगर (tb->blknum[0] == 0) अणु	/* node S[0] is empty now */

		RFALSE(!tb->lnum[0] || !tb->rnum[0],
		       "PAP-12190: lnum and rnum must not be zero");
		/*
		 * अगर insertion was करोne beक्रमe 0-th position in R[0], right
		 * delimiting key of the tb->L[0]'s and left delimiting key are
		 * not set correctly
		 */
		अगर (tb->CFL[0]) अणु
			अगर (!tb->CFR[0])
				reiserfs_panic(tb->tb_sb, "vs-12195",
					       "CFR not initialized");
			copy_key(पूर्णांकernal_key(tb->CFL[0], tb->lkey[0]),
				 पूर्णांकernal_key(tb->CFR[0], tb->rkey[0]));
			करो_balance_mark_पूर्णांकernal_dirty(tb, tb->CFL[0], 0);
		पूर्ण

		reiserfs_invalidate_buffer(tb, tbS0);
		वापस 0;
	पूर्ण

	balance_leaf_new_nodes(tb, ih, body, insert_key, insert_ptr, flag);

	balance_leaf_finish_node(tb, ih, body, flag);

#अगर_घोषित CONFIG_REISERFS_CHECK
	अगर (flag == M_PASTE && tb->insert_size[0]) अणु
		prपूर्णांक_cur_tb("12290");
		reiserfs_panic(tb->tb_sb,
			       "PAP-12290", "insert_size is still not 0 (%d)",
			       tb->insert_size[0]);
	पूर्ण
#पूर्ण_अगर

	/* Leaf level of the tree is balanced (end of balance_leaf) */
	वापस 0;
पूर्ण

/* Make empty node */
व्योम make_empty_node(काष्ठा buffer_info *bi)
अणु
	काष्ठा block_head *blkh;

	RFALSE(bi->bi_bh == शून्य, "PAP-12295: pointer to the buffer is NULL");

	blkh = B_BLK_HEAD(bi->bi_bh);
	set_blkh_nr_item(blkh, 0);
	set_blkh_मुक्त_space(blkh, MAX_CHILD_SIZE(bi->bi_bh));

	अगर (bi->bi_parent)
		B_N_CHILD(bi->bi_parent, bi->bi_position)->dc_size = 0;	/* Endian safe अगर 0 */
पूर्ण

/* Get first empty buffer */
काष्ठा buffer_head *get_FEB(काष्ठा tree_balance *tb)
अणु
	पूर्णांक i;
	काष्ठा buffer_info bi;

	क्रम (i = 0; i < MAX_FEB_SIZE; i++)
		अगर (tb->FEB[i] != शून्य)
			अवरोध;

	अगर (i == MAX_FEB_SIZE)
		reiserfs_panic(tb->tb_sb, "vs-12300", "FEB list is empty");

	buffer_info_init_bh(tb, &bi, tb->FEB[i]);
	make_empty_node(&bi);
	set_buffer_uptodate(tb->FEB[i]);
	tb->used[i] = tb->FEB[i];
	tb->FEB[i] = शून्य;

	वापस tb->used[i];
पूर्ण

/* This is now used because reiserfs_मुक्त_block has to be able to schedule. */
अटल व्योम store_thrown(काष्ठा tree_balance *tb, काष्ठा buffer_head *bh)
अणु
	पूर्णांक i;

	अगर (buffer_dirty(bh))
		reiserfs_warning(tb->tb_sb, "reiserfs-12320",
				 "called with dirty buffer");
	क्रम (i = 0; i < ARRAY_SIZE(tb->thrown); i++)
		अगर (!tb->thrown[i]) अणु
			tb->thrown[i] = bh;
			get_bh(bh);	/* मुक्त_thrown माला_दो this */
			वापस;
		पूर्ण
	reiserfs_warning(tb->tb_sb, "reiserfs-12321",
			 "too many thrown buffers");
पूर्ण

अटल व्योम मुक्त_thrown(काष्ठा tree_balance *tb)
अणु
	पूर्णांक i;
	b_blocknr_t blocknr;
	क्रम (i = 0; i < ARRAY_SIZE(tb->thrown); i++) अणु
		अगर (tb->thrown[i]) अणु
			blocknr = tb->thrown[i]->b_blocknr;
			अगर (buffer_dirty(tb->thrown[i]))
				reiserfs_warning(tb->tb_sb, "reiserfs-12322",
						 "called with dirty buffer %d",
						 blocknr);
			brअन्यथा(tb->thrown[i]);	/* incremented in store_thrown */
			reiserfs_मुक्त_block(tb->transaction_handle, शून्य,
					    blocknr, 0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम reiserfs_invalidate_buffer(काष्ठा tree_balance *tb, काष्ठा buffer_head *bh)
अणु
	काष्ठा block_head *blkh;
	blkh = B_BLK_HEAD(bh);
	set_blkh_level(blkh, FREE_LEVEL);
	set_blkh_nr_item(blkh, 0);

	clear_buffer_dirty(bh);
	store_thrown(tb, bh);
पूर्ण

/* Replace n_dest'th key in buffer dest by n_src'th key of buffer src.*/
व्योम replace_key(काष्ठा tree_balance *tb, काष्ठा buffer_head *dest, पूर्णांक n_dest,
		 काष्ठा buffer_head *src, पूर्णांक n_src)
अणु

	RFALSE(dest == शून्य || src == शून्य,
	       "vs-12305: source or destination buffer is 0 (src=%p, dest=%p)",
	       src, dest);
	RFALSE(!B_IS_KEYS_LEVEL(dest),
	       "vs-12310: invalid level (%z) for destination buffer. dest must be leaf",
	       dest);
	RFALSE(n_dest < 0 || n_src < 0,
	       "vs-12315: src(%d) or dest(%d) key number < 0", n_src, n_dest);
	RFALSE(n_dest >= B_NR_ITEMS(dest) || n_src >= B_NR_ITEMS(src),
	       "vs-12320: src(%d(%d)) or dest(%d(%d)) key number is too big",
	       n_src, B_NR_ITEMS(src), n_dest, B_NR_ITEMS(dest));

	अगर (B_IS_ITEMS_LEVEL(src))
		/* source buffer contains leaf node */
		स_नकल(पूर्णांकernal_key(dest, n_dest), item_head(src, n_src),
		       KEY_SIZE);
	अन्यथा
		स_नकल(पूर्णांकernal_key(dest, n_dest), पूर्णांकernal_key(src, n_src),
		       KEY_SIZE);

	करो_balance_mark_पूर्णांकernal_dirty(tb, dest, 0);
पूर्ण

पूर्णांक get_left_neighbor_position(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	पूर्णांक Sh_position = PATH_H_POSITION(tb->tb_path, h + 1);

	RFALSE(PATH_H_PPARENT(tb->tb_path, h) == शून्य || tb->FL[h] == शून्य,
	       "vs-12325: FL[%d](%p) or F[%d](%p) does not exist",
	       h, tb->FL[h], h, PATH_H_PPARENT(tb->tb_path, h));

	अगर (Sh_position == 0)
		वापस B_NR_ITEMS(tb->FL[h]);
	अन्यथा
		वापस Sh_position - 1;
पूर्ण

पूर्णांक get_right_neighbor_position(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	पूर्णांक Sh_position = PATH_H_POSITION(tb->tb_path, h + 1);

	RFALSE(PATH_H_PPARENT(tb->tb_path, h) == शून्य || tb->FR[h] == शून्य,
	       "vs-12330: F[%d](%p) or FR[%d](%p) does not exist",
	       h, PATH_H_PPARENT(tb->tb_path, h), h, tb->FR[h]);

	अगर (Sh_position == B_NR_ITEMS(PATH_H_PPARENT(tb->tb_path, h)))
		वापस 0;
	अन्यथा
		वापस Sh_position + 1;
पूर्ण

#अगर_घोषित CONFIG_REISERFS_CHECK

पूर्णांक is_reusable(काष्ठा super_block *s, b_blocknr_t block, पूर्णांक bit_value);
अटल व्योम check_पूर्णांकernal_node(काष्ठा super_block *s, काष्ठा buffer_head *bh,
				अक्षर *mes)
अणु
	काष्ठा disk_child *dc;
	पूर्णांक i;

	RFALSE(!bh, "PAP-12336: bh == 0");

	अगर (!bh || !B_IS_IN_TREE(bh))
		वापस;

	RFALSE(!buffer_dirty(bh) &&
	       !(buffer_journaled(bh) || buffer_journal_dirty(bh)),
	       "PAP-12337: buffer (%b) must be dirty", bh);
	dc = B_N_CHILD(bh, 0);

	क्रम (i = 0; i <= B_NR_ITEMS(bh); i++, dc++) अणु
		अगर (!is_reusable(s, dc_block_number(dc), 1)) अणु
			prपूर्णांक_cur_tb(mes);
			reiserfs_panic(s, "PAP-12338",
				       "invalid child pointer %y in %b",
				       dc, bh);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक locked_or_not_in_tree(काष्ठा tree_balance *tb,
				  काष्ठा buffer_head *bh, अक्षर *which)
अणु
	अगर ((!buffer_journal_prepared(bh) && buffer_locked(bh)) ||
	    !B_IS_IN_TREE(bh)) अणु
		reiserfs_warning(tb->tb_sb, "vs-12339", "%s (%b)", which, bh);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_beक्रमe_balancing(काष्ठा tree_balance *tb)
अणु
	पूर्णांक retval = 0;

	अगर (REISERFS_SB(tb->tb_sb)->cur_tb) अणु
		reiserfs_panic(tb->tb_sb, "vs-12335", "suspect that schedule "
			       "occurred based on cur_tb not being null at "
			       "this point in code. do_balance cannot properly "
			       "handle concurrent tree accesses on a same "
			       "mount point.");
	पूर्ण

	/*
	 * द्विगुन check that buffers that we will modअगरy are unlocked.
	 * (fix_nodes should alपढ़ोy have prepped all of these क्रम us).
	 */
	अगर (tb->lnum[0]) अणु
		retval |= locked_or_not_in_tree(tb, tb->L[0], "L[0]");
		retval |= locked_or_not_in_tree(tb, tb->FL[0], "FL[0]");
		retval |= locked_or_not_in_tree(tb, tb->CFL[0], "CFL[0]");
		check_leaf(tb->L[0]);
	पूर्ण
	अगर (tb->rnum[0]) अणु
		retval |= locked_or_not_in_tree(tb, tb->R[0], "R[0]");
		retval |= locked_or_not_in_tree(tb, tb->FR[0], "FR[0]");
		retval |= locked_or_not_in_tree(tb, tb->CFR[0], "CFR[0]");
		check_leaf(tb->R[0]);
	पूर्ण
	retval |= locked_or_not_in_tree(tb, PATH_PLAST_BUFFER(tb->tb_path),
					"S[0]");
	check_leaf(PATH_PLAST_BUFFER(tb->tb_path));

	वापस retval;
पूर्ण

अटल व्योम check_after_balance_leaf(काष्ठा tree_balance *tb)
अणु
	अगर (tb->lnum[0]) अणु
		अगर (B_FREE_SPACE(tb->L[0]) !=
		    MAX_CHILD_SIZE(tb->L[0]) -
		    dc_size(B_N_CHILD
			    (tb->FL[0], get_left_neighbor_position(tb, 0)))) अणु
			prपूर्णांक_cur_tb("12221");
			reiserfs_panic(tb->tb_sb, "PAP-12355",
				       "shift to left was incorrect");
		पूर्ण
	पूर्ण
	अगर (tb->rnum[0]) अणु
		अगर (B_FREE_SPACE(tb->R[0]) !=
		    MAX_CHILD_SIZE(tb->R[0]) -
		    dc_size(B_N_CHILD
			    (tb->FR[0], get_right_neighbor_position(tb, 0)))) अणु
			prपूर्णांक_cur_tb("12222");
			reiserfs_panic(tb->tb_sb, "PAP-12360",
				       "shift to right was incorrect");
		पूर्ण
	पूर्ण
	अगर (PATH_H_PBUFFER(tb->tb_path, 1) &&
	    (B_FREE_SPACE(PATH_H_PBUFFER(tb->tb_path, 0)) !=
	     (MAX_CHILD_SIZE(PATH_H_PBUFFER(tb->tb_path, 0)) -
	      dc_size(B_N_CHILD(PATH_H_PBUFFER(tb->tb_path, 1),
				PATH_H_POSITION(tb->tb_path, 1)))))) अणु
		पूर्णांक left = B_FREE_SPACE(PATH_H_PBUFFER(tb->tb_path, 0));
		पूर्णांक right = (MAX_CHILD_SIZE(PATH_H_PBUFFER(tb->tb_path, 0)) -
			     dc_size(B_N_CHILD(PATH_H_PBUFFER(tb->tb_path, 1),
					       PATH_H_POSITION(tb->tb_path,
							       1))));
		prपूर्णांक_cur_tb("12223");
		reiserfs_warning(tb->tb_sb, "reiserfs-12363",
				 "B_FREE_SPACE (PATH_H_PBUFFER(tb->tb_path,0)) = %d; "
				 "MAX_CHILD_SIZE (%d) - dc_size( %y, %d ) [%d] = %d",
				 left,
				 MAX_CHILD_SIZE(PATH_H_PBUFFER(tb->tb_path, 0)),
				 PATH_H_PBUFFER(tb->tb_path, 1),
				 PATH_H_POSITION(tb->tb_path, 1),
				 dc_size(B_N_CHILD
					 (PATH_H_PBUFFER(tb->tb_path, 1),
					  PATH_H_POSITION(tb->tb_path, 1))),
				 right);
		reiserfs_panic(tb->tb_sb, "PAP-12365", "S is incorrect");
	पूर्ण
पूर्ण

अटल व्योम check_leaf_level(काष्ठा tree_balance *tb)
अणु
	check_leaf(tb->L[0]);
	check_leaf(tb->R[0]);
	check_leaf(PATH_PLAST_BUFFER(tb->tb_path));
पूर्ण

अटल व्योम check_पूर्णांकernal_levels(काष्ठा tree_balance *tb)
अणु
	पूर्णांक h;

	/* check all पूर्णांकernal nodes */
	क्रम (h = 1; tb->insert_size[h]; h++) अणु
		check_पूर्णांकernal_node(tb->tb_sb, PATH_H_PBUFFER(tb->tb_path, h),
				    "BAD BUFFER ON PATH");
		अगर (tb->lnum[h])
			check_पूर्णांकernal_node(tb->tb_sb, tb->L[h], "BAD L");
		अगर (tb->rnum[h])
			check_पूर्णांकernal_node(tb->tb_sb, tb->R[h], "BAD R");
	पूर्ण

पूर्ण

#पूर्ण_अगर

/*
 * Now we have all of the buffers that must be used in balancing of
 * the tree.  We rely on the assumption that schedule() will not occur
 * जबतक करो_balance works. ( Only पूर्णांकerrupt handlers are acceptable.)
 * We balance the tree according to the analysis made beक्रमe this,
 * using buffers alपढ़ोy obtained.  For SMP support it will someday be
 * necessary to add ordered locking of tb.
 */

/*
 * Some पूर्णांकeresting rules of balancing:
 * we delete a maximum of two nodes per level per balancing: we never
 * delete R, when we delete two of three nodes L, S, R then we move
 * them पूर्णांकo R.
 *
 * we only delete L अगर we are deleting two nodes, अगर we delete only
 * one node we delete S
 *
 * अगर we shअगरt leaves then we shअगरt as much as we can: this is a
 * deliberate policy of extremism in node packing which results in
 * higher average utilization after repeated अक्रमom balance operations
 * at the cost of more memory copies and more balancing as a result of
 * small insertions to full nodes.
 *
 * अगर we shअगरt पूर्णांकernal nodes we try to evenly balance the node
 * utilization, with consequent less balancing at the cost of lower
 * utilization.
 *
 * one could argue that the policy क्रम directories in leaves should be
 * that of पूर्णांकernal nodes, but we will रुको until another day to
 * evaluate this....  It would be nice to someday measure and prove
 * these assumptions as to what is optimal....
 */

अटल अंतरभूत व्योम करो_balance_starts(काष्ठा tree_balance *tb)
अणु
	/* use prपूर्णांक_cur_tb() to see initial state of काष्ठा tree_balance */

	/* store_prपूर्णांक_tb (tb); */

	/* करो not delete, just comment it out */
	/*
	prपूर्णांक_tb(flag, PATH_LAST_POSITION(tb->tb_path),
		 tb->tb_path->pos_in_item, tb, "check");
	*/
	RFALSE(check_beक्रमe_balancing(tb), "PAP-12340: locked buffers in TB");
#अगर_घोषित CONFIG_REISERFS_CHECK
	REISERFS_SB(tb->tb_sb)->cur_tb = tb;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम करो_balance_completed(काष्ठा tree_balance *tb)
अणु

#अगर_घोषित CONFIG_REISERFS_CHECK
	check_leaf_level(tb);
	check_पूर्णांकernal_levels(tb);
	REISERFS_SB(tb->tb_sb)->cur_tb = शून्य;
#पूर्ण_अगर

	/*
	 * reiserfs_मुक्त_block is no दीर्घer schedule safe.  So, we need to
	 * put the buffers we want मुक्तd on the thrown list during करो_balance,
	 * and then मुक्त them now
	 */

	REISERFS_SB(tb->tb_sb)->s_करो_balance++;

	/* release all nodes hold to perक्रमm the balancing */
	unfix_nodes(tb);

	मुक्त_thrown(tb);
पूर्ण

/*
 * करो_balance - balance the tree
 *
 * @tb: tree_balance काष्ठाure
 * @ih: item header of inserted item
 * @body: body of inserted item or bytes to paste
 * @flag: 'i' - insert, 'd' - delete, 'c' - cut, 'p' paste
 *
 * Cut means delete part of an item (includes removing an entry from a
 * directory).
 *
 * Delete means delete whole item.
 *
 * Insert means add a new item पूर्णांकo the tree.
 *
 * Paste means to append to the end of an existing file or to
 * insert a directory entry.
 */
व्योम करो_balance(काष्ठा tree_balance *tb, काष्ठा item_head *ih,
		स्थिर अक्षर *body, पूर्णांक flag)
अणु
	पूर्णांक child_pos;		/* position of a child node in its parent */
	पूर्णांक h;			/* level of the tree being processed */

	/*
	 * in our processing of one level we someबार determine what
	 * must be inserted पूर्णांकo the next higher level.  This insertion
	 * consists of a key or two keys and their corresponding
	 * poपूर्णांकers
	 */
	काष्ठा item_head insert_key[2];

	/* inserted node-ptrs क्रम the next level */
	काष्ठा buffer_head *insert_ptr[2];

	tb->tb_mode = flag;
	tb->need_balance_dirty = 0;

	अगर (खाताSYSTEM_CHANGED_TB(tb)) अणु
		reiserfs_panic(tb->tb_sb, "clm-6000", "fs generation has "
			       "changed");
	पूर्ण
	/* अगर we have no real work to करो  */
	अगर (!tb->insert_size[0]) अणु
		reiserfs_warning(tb->tb_sb, "PAP-12350",
				 "insert_size == 0, mode == %c", flag);
		unfix_nodes(tb);
		वापस;
	पूर्ण

	atomic_inc(&fs_generation(tb->tb_sb));
	करो_balance_starts(tb);

	/*
	 * balance_leaf वापसs 0 except अगर combining L R and S पूर्णांकo
	 * one node.  see balance_पूर्णांकernal() क्रम explanation of this
	 * line of code.
	 */
	child_pos = PATH_H_B_ITEM_ORDER(tb->tb_path, 0) +
	    balance_leaf(tb, ih, body, flag, insert_key, insert_ptr);

#अगर_घोषित CONFIG_REISERFS_CHECK
	check_after_balance_leaf(tb);
#पूर्ण_अगर

	/* Balance पूर्णांकernal level of the tree. */
	क्रम (h = 1; h < MAX_HEIGHT && tb->insert_size[h]; h++)
		child_pos = balance_पूर्णांकernal(tb, h, child_pos, insert_key,
					     insert_ptr);

	करो_balance_completed(tb);
पूर्ण
