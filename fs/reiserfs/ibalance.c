<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश "reiserfs.h"
#समावेश <linux/buffer_head.h>

/* this is one and only function that is used outside (करो_balance.c) */
पूर्णांक balance_पूर्णांकernal(काष्ठा tree_balance *,
		     पूर्णांक, पूर्णांक, काष्ठा item_head *, काष्ठा buffer_head **);

/*
 * modes of पूर्णांकernal_shअगरt_left, पूर्णांकernal_shअगरt_right and
 * पूर्णांकernal_insert_childs
 */
#घोषणा INTERNAL_SHIFT_FROM_S_TO_L 0
#घोषणा INTERNAL_SHIFT_FROM_R_TO_S 1
#घोषणा INTERNAL_SHIFT_FROM_L_TO_S 2
#घोषणा INTERNAL_SHIFT_FROM_S_TO_R 3
#घोषणा INTERNAL_INSERT_TO_S 4
#घोषणा INTERNAL_INSERT_TO_L 5
#घोषणा INTERNAL_INSERT_TO_R 6

अटल व्योम पूर्णांकernal_define_dest_src_infos(पूर्णांक shअगरt_mode,
					   काष्ठा tree_balance *tb,
					   पूर्णांक h,
					   काष्ठा buffer_info *dest_bi,
					   काष्ठा buffer_info *src_bi,
					   पूर्णांक *d_key, काष्ठा buffer_head **cf)
अणु
	स_रखो(dest_bi, 0, माप(काष्ठा buffer_info));
	स_रखो(src_bi, 0, माप(काष्ठा buffer_info));
	/* define dest, src, dest parent, dest position */
	चयन (shअगरt_mode) अणु

	/* used in पूर्णांकernal_shअगरt_left */
	हाल INTERNAL_SHIFT_FROM_S_TO_L:
		src_bi->tb = tb;
		src_bi->bi_bh = PATH_H_PBUFFER(tb->tb_path, h);
		src_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, h);
		src_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->L[h];
		dest_bi->bi_parent = tb->FL[h];
		dest_bi->bi_position = get_left_neighbor_position(tb, h);
		*d_key = tb->lkey[h];
		*cf = tb->CFL[h];
		अवरोध;
	हाल INTERNAL_SHIFT_FROM_L_TO_S:
		src_bi->tb = tb;
		src_bi->bi_bh = tb->L[h];
		src_bi->bi_parent = tb->FL[h];
		src_bi->bi_position = get_left_neighbor_position(tb, h);
		dest_bi->tb = tb;
		dest_bi->bi_bh = PATH_H_PBUFFER(tb->tb_path, h);
		dest_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, h);
		/* dest position is analog of dest->b_item_order */
		dest_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		*d_key = tb->lkey[h];
		*cf = tb->CFL[h];
		अवरोध;

	/* used in पूर्णांकernal_shअगरt_left */
	हाल INTERNAL_SHIFT_FROM_R_TO_S:
		src_bi->tb = tb;
		src_bi->bi_bh = tb->R[h];
		src_bi->bi_parent = tb->FR[h];
		src_bi->bi_position = get_right_neighbor_position(tb, h);
		dest_bi->tb = tb;
		dest_bi->bi_bh = PATH_H_PBUFFER(tb->tb_path, h);
		dest_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, h);
		dest_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		*d_key = tb->rkey[h];
		*cf = tb->CFR[h];
		अवरोध;

	हाल INTERNAL_SHIFT_FROM_S_TO_R:
		src_bi->tb = tb;
		src_bi->bi_bh = PATH_H_PBUFFER(tb->tb_path, h);
		src_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, h);
		src_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->R[h];
		dest_bi->bi_parent = tb->FR[h];
		dest_bi->bi_position = get_right_neighbor_position(tb, h);
		*d_key = tb->rkey[h];
		*cf = tb->CFR[h];
		अवरोध;

	हाल INTERNAL_INSERT_TO_L:
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->L[h];
		dest_bi->bi_parent = tb->FL[h];
		dest_bi->bi_position = get_left_neighbor_position(tb, h);
		अवरोध;

	हाल INTERNAL_INSERT_TO_S:
		dest_bi->tb = tb;
		dest_bi->bi_bh = PATH_H_PBUFFER(tb->tb_path, h);
		dest_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, h);
		dest_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		अवरोध;

	हाल INTERNAL_INSERT_TO_R:
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->R[h];
		dest_bi->bi_parent = tb->FR[h];
		dest_bi->bi_position = get_right_neighbor_position(tb, h);
		अवरोध;

	शेष:
		reiserfs_panic(tb->tb_sb, "ibalance-1",
			       "shift type is unknown (%d)",
			       shअगरt_mode);
	पूर्ण
पूर्ण

/*
 * Insert count node poपूर्णांकers पूर्णांकo buffer cur beक्रमe position to + 1.
 * Insert count items पूर्णांकo buffer cur beक्रमe position to.
 * Items and node poपूर्णांकers are specअगरied by inserted and bh respectively.
 */
अटल व्योम पूर्णांकernal_insert_childs(काष्ठा buffer_info *cur_bi,
				   पूर्णांक to, पूर्णांक count,
				   काष्ठा item_head *inserted,
				   काष्ठा buffer_head **bh)
अणु
	काष्ठा buffer_head *cur = cur_bi->bi_bh;
	काष्ठा block_head *blkh;
	पूर्णांक nr;
	काष्ठा reiserfs_key *ih;
	काष्ठा disk_child new_dc[2];
	काष्ठा disk_child *dc;
	पूर्णांक i;

	अगर (count <= 0)
		वापस;

	blkh = B_BLK_HEAD(cur);
	nr = blkh_nr_item(blkh);

	RFALSE(count > 2, "too many children (%d) are to be inserted", count);
	RFALSE(B_FREE_SPACE(cur) < count * (KEY_SIZE + DC_SIZE),
	       "no enough free space (%d), needed %d bytes",
	       B_FREE_SPACE(cur), count * (KEY_SIZE + DC_SIZE));

	/* prepare space क्रम count disk_child */
	dc = B_N_CHILD(cur, to + 1);

	स_हटाओ(dc + count, dc, (nr + 1 - (to + 1)) * DC_SIZE);

	/* copy to_be_insert disk children */
	क्रम (i = 0; i < count; i++) अणु
		put_dc_size(&new_dc[i],
			    MAX_CHILD_SIZE(bh[i]) - B_FREE_SPACE(bh[i]));
		put_dc_block_number(&new_dc[i], bh[i]->b_blocknr);
	पूर्ण
	स_नकल(dc, new_dc, DC_SIZE * count);

	/* prepare space क्रम count items  */
	ih = पूर्णांकernal_key(cur, ((to == -1) ? 0 : to));

	स_हटाओ(ih + count, ih,
		(nr - to) * KEY_SIZE + (nr + 1 + count) * DC_SIZE);

	/* copy item headers (keys) */
	स_नकल(ih, inserted, KEY_SIZE);
	अगर (count > 1)
		स_नकल(ih + 1, inserted + 1, KEY_SIZE);

	/* sizes, item number */
	set_blkh_nr_item(blkh, blkh_nr_item(blkh) + count);
	set_blkh_मुक्त_space(blkh,
			    blkh_मुक्त_space(blkh) - count * (DC_SIZE +
							     KEY_SIZE));

	करो_balance_mark_पूर्णांकernal_dirty(cur_bi->tb, cur, 0);

	/*&&&&&&&&&&&&&&&&&&&&&&&& */
	check_पूर्णांकernal(cur);
	/*&&&&&&&&&&&&&&&&&&&&&&&& */

	अगर (cur_bi->bi_parent) अणु
		काष्ठा disk_child *t_dc =
		    B_N_CHILD(cur_bi->bi_parent, cur_bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) + (count * (DC_SIZE + KEY_SIZE)));
		करो_balance_mark_पूर्णांकernal_dirty(cur_bi->tb, cur_bi->bi_parent,
					       0);

		/*&&&&&&&&&&&&&&&&&&&&&&&& */
		check_पूर्णांकernal(cur_bi->bi_parent);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
	पूर्ण

पूर्ण

/*
 * Delete del_num items and node poपूर्णांकers from buffer cur starting from
 * the first_i'th item and first_p'th poपूर्णांकers respectively.
 */
अटल व्योम पूर्णांकernal_delete_poपूर्णांकers_items(काष्ठा buffer_info *cur_bi,
					   पूर्णांक first_p,
					   पूर्णांक first_i, पूर्णांक del_num)
अणु
	काष्ठा buffer_head *cur = cur_bi->bi_bh;
	पूर्णांक nr;
	काष्ठा block_head *blkh;
	काष्ठा reiserfs_key *key;
	काष्ठा disk_child *dc;

	RFALSE(cur == शून्य, "buffer is 0");
	RFALSE(del_num < 0,
	       "negative number of items (%d) can not be deleted", del_num);
	RFALSE(first_p < 0 || first_p + del_num > B_NR_ITEMS(cur) + 1
	       || first_i < 0,
	       "first pointer order (%d) < 0 or "
	       "no so many pointers (%d), only (%d) or "
	       "first key order %d < 0", first_p, first_p + del_num,
	       B_NR_ITEMS(cur) + 1, first_i);
	अगर (del_num == 0)
		वापस;

	blkh = B_BLK_HEAD(cur);
	nr = blkh_nr_item(blkh);

	अगर (first_p == 0 && del_num == nr + 1) अणु
		RFALSE(first_i != 0,
		       "1st deleted key must have order 0, not %d", first_i);
		make_empty_node(cur_bi);
		वापस;
	पूर्ण

	RFALSE(first_i + del_num > B_NR_ITEMS(cur),
	       "first_i = %d del_num = %d "
	       "no so many keys (%d) in the node (%b)(%z)",
	       first_i, del_num, first_i + del_num, cur, cur);

	/* deleting */
	dc = B_N_CHILD(cur, first_p);

	स_हटाओ(dc, dc + del_num, (nr + 1 - first_p - del_num) * DC_SIZE);
	key = पूर्णांकernal_key(cur, first_i);
	स_हटाओ(key, key + del_num,
		(nr - first_i - del_num) * KEY_SIZE + (nr + 1 -
						       del_num) * DC_SIZE);

	/* sizes, item number */
	set_blkh_nr_item(blkh, blkh_nr_item(blkh) - del_num);
	set_blkh_मुक्त_space(blkh,
			    blkh_मुक्त_space(blkh) +
			    (del_num * (KEY_SIZE + DC_SIZE)));

	करो_balance_mark_पूर्णांकernal_dirty(cur_bi->tb, cur, 0);
	/*&&&&&&&&&&&&&&&&&&&&&&& */
	check_पूर्णांकernal(cur);
	/*&&&&&&&&&&&&&&&&&&&&&&& */

	अगर (cur_bi->bi_parent) अणु
		काष्ठा disk_child *t_dc;
		t_dc = B_N_CHILD(cur_bi->bi_parent, cur_bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) - (del_num * (KEY_SIZE + DC_SIZE)));

		करो_balance_mark_पूर्णांकernal_dirty(cur_bi->tb, cur_bi->bi_parent,
					       0);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
		check_पूर्णांकernal(cur_bi->bi_parent);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
	पूर्ण
पूर्ण

/* delete n node poपूर्णांकers and items starting from given position */
अटल व्योम पूर्णांकernal_delete_childs(काष्ठा buffer_info *cur_bi, पूर्णांक from, पूर्णांक n)
अणु
	पूर्णांक i_from;

	i_from = (from == 0) ? from : from - 1;

	/*
	 * delete n poपूर्णांकers starting from `from' position in CUR;
	 * delete n keys starting from 'i_from' position in CUR;
	 */
	पूर्णांकernal_delete_poपूर्णांकers_items(cur_bi, from, i_from, n);
पूर्ण

/*
 * copy cpy_num node poपूर्णांकers and cpy_num - 1 items from buffer src to buffer
 * dest
 * last_first == FIRST_TO_LAST means that we copy first items
 *                             from src to tail of dest
 * last_first == LAST_TO_FIRST means that we copy last items
 *                             from src to head of dest
 */
अटल व्योम पूर्णांकernal_copy_poपूर्णांकers_items(काष्ठा buffer_info *dest_bi,
					 काष्ठा buffer_head *src,
					 पूर्णांक last_first, पूर्णांक cpy_num)
अणु
	/*
	 * ATTENTION! Number of node poपूर्णांकers in DEST is equal to number
	 * of items in DEST  as delimiting key have alपढ़ोy inserted to
	 * buffer dest.
	 */
	काष्ठा buffer_head *dest = dest_bi->bi_bh;
	पूर्णांक nr_dest, nr_src;
	पूर्णांक dest_order, src_order;
	काष्ठा block_head *blkh;
	काष्ठा reiserfs_key *key;
	काष्ठा disk_child *dc;

	nr_src = B_NR_ITEMS(src);

	RFALSE(dest == शून्य || src == शून्य,
	       "src (%p) or dest (%p) buffer is 0", src, dest);
	RFALSE(last_first != FIRST_TO_LAST && last_first != LAST_TO_FIRST,
	       "invalid last_first parameter (%d)", last_first);
	RFALSE(nr_src < cpy_num - 1,
	       "no so many items (%d) in src (%d)", cpy_num, nr_src);
	RFALSE(cpy_num < 0, "cpy_num less than 0 (%d)", cpy_num);
	RFALSE(cpy_num - 1 + B_NR_ITEMS(dest) > (पूर्णांक)MAX_NR_KEY(dest),
	       "cpy_num (%d) + item number in dest (%d) can not be > MAX_NR_KEY(%d)",
	       cpy_num, B_NR_ITEMS(dest), MAX_NR_KEY(dest));

	अगर (cpy_num == 0)
		वापस;

	/* coping */
	blkh = B_BLK_HEAD(dest);
	nr_dest = blkh_nr_item(blkh);

	/*dest_order = (last_first == LAST_TO_FIRST) ? 0 : nr_dest; */
	/*src_order = (last_first == LAST_TO_FIRST) ? (nr_src - cpy_num + 1) : 0; */
	(last_first == LAST_TO_FIRST) ? (dest_order = 0, src_order =
					 nr_src - cpy_num + 1) : (dest_order =
								  nr_dest,
								  src_order =
								  0);

	/* prepare space क्रम cpy_num poपूर्णांकers */
	dc = B_N_CHILD(dest, dest_order);

	स_हटाओ(dc + cpy_num, dc, (nr_dest - dest_order) * DC_SIZE);

	/* insert poपूर्णांकers */
	स_नकल(dc, B_N_CHILD(src, src_order), DC_SIZE * cpy_num);

	/* prepare space क्रम cpy_num - 1 item headers */
	key = पूर्णांकernal_key(dest, dest_order);
	स_हटाओ(key + cpy_num - 1, key,
		KEY_SIZE * (nr_dest - dest_order) + DC_SIZE * (nr_dest +
							       cpy_num));

	/* insert headers */
	स_नकल(key, पूर्णांकernal_key(src, src_order), KEY_SIZE * (cpy_num - 1));

	/* sizes, item number */
	set_blkh_nr_item(blkh, blkh_nr_item(blkh) + (cpy_num - 1));
	set_blkh_मुक्त_space(blkh,
			    blkh_मुक्त_space(blkh) - (KEY_SIZE * (cpy_num - 1) +
						     DC_SIZE * cpy_num));

	करो_balance_mark_पूर्णांकernal_dirty(dest_bi->tb, dest, 0);

	/*&&&&&&&&&&&&&&&&&&&&&&&& */
	check_पूर्णांकernal(dest);
	/*&&&&&&&&&&&&&&&&&&&&&&&& */

	अगर (dest_bi->bi_parent) अणु
		काष्ठा disk_child *t_dc;
		t_dc = B_N_CHILD(dest_bi->bi_parent, dest_bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) + (KEY_SIZE * (cpy_num - 1) +
					     DC_SIZE * cpy_num));

		करो_balance_mark_पूर्णांकernal_dirty(dest_bi->tb, dest_bi->bi_parent,
					       0);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
		check_पूर्णांकernal(dest_bi->bi_parent);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
	पूर्ण

पूर्ण

/*
 * Copy cpy_num node poपूर्णांकers and cpy_num - 1 items from buffer src to
 * buffer dest.
 * Delete cpy_num - del_par items and node poपूर्णांकers from buffer src.
 * last_first == FIRST_TO_LAST means, that we copy/delete first items from src.
 * last_first == LAST_TO_FIRST means, that we copy/delete last items from src.
 */
अटल व्योम पूर्णांकernal_move_poपूर्णांकers_items(काष्ठा buffer_info *dest_bi,
					 काष्ठा buffer_info *src_bi,
					 पूर्णांक last_first, पूर्णांक cpy_num,
					 पूर्णांक del_par)
अणु
	पूर्णांक first_poपूर्णांकer;
	पूर्णांक first_item;

	पूर्णांकernal_copy_poपूर्णांकers_items(dest_bi, src_bi->bi_bh, last_first,
				     cpy_num);

	अगर (last_first == FIRST_TO_LAST) अणु	/* shअगरt_left occurs */
		first_poपूर्णांकer = 0;
		first_item = 0;
		/*
		 * delete cpy_num - del_par poपूर्णांकers and keys starting क्रम
		 * poपूर्णांकers with first_poपूर्णांकer, क्रम key - with first_item
		 */
		पूर्णांकernal_delete_poपूर्णांकers_items(src_bi, first_poपूर्णांकer,
					       first_item, cpy_num - del_par);
	पूर्ण अन्यथा अणु		/* shअगरt_right occurs */
		पूर्णांक i, j;

		i = (cpy_num - del_par ==
		     (j =
		      B_NR_ITEMS(src_bi->bi_bh)) + 1) ? 0 : j - cpy_num +
		    del_par;

		पूर्णांकernal_delete_poपूर्णांकers_items(src_bi,
					       j + 1 - cpy_num + del_par, i,
					       cpy_num - del_par);
	पूर्ण
पूर्ण

/* Insert n_src'th key of buffer src before n_dest'th key of buffer dest. */
अटल व्योम पूर्णांकernal_insert_key(काष्ठा buffer_info *dest_bi,
				/* insert key beक्रमe key with n_dest number */
				पूर्णांक dest_position_beक्रमe,
				काष्ठा buffer_head *src, पूर्णांक src_position)
अणु
	काष्ठा buffer_head *dest = dest_bi->bi_bh;
	पूर्णांक nr;
	काष्ठा block_head *blkh;
	काष्ठा reiserfs_key *key;

	RFALSE(dest == शून्य || src == शून्य,
	       "source(%p) or dest(%p) buffer is 0", src, dest);
	RFALSE(dest_position_beक्रमe < 0 || src_position < 0,
	       "source(%d) or dest(%d) key number less than 0",
	       src_position, dest_position_beक्रमe);
	RFALSE(dest_position_beक्रमe > B_NR_ITEMS(dest) ||
	       src_position >= B_NR_ITEMS(src),
	       "invalid position in dest (%d (key number %d)) or in src (%d (key number %d))",
	       dest_position_beक्रमe, B_NR_ITEMS(dest),
	       src_position, B_NR_ITEMS(src));
	RFALSE(B_FREE_SPACE(dest) < KEY_SIZE,
	       "no enough free space (%d) in dest buffer", B_FREE_SPACE(dest));

	blkh = B_BLK_HEAD(dest);
	nr = blkh_nr_item(blkh);

	/* prepare space क्रम inserting key */
	key = पूर्णांकernal_key(dest, dest_position_beक्रमe);
	स_हटाओ(key + 1, key,
		(nr - dest_position_beक्रमe) * KEY_SIZE + (nr + 1) * DC_SIZE);

	/* insert key */
	स_नकल(key, पूर्णांकernal_key(src, src_position), KEY_SIZE);

	/* Change dirt, मुक्त space, item number fields. */

	set_blkh_nr_item(blkh, blkh_nr_item(blkh) + 1);
	set_blkh_मुक्त_space(blkh, blkh_मुक्त_space(blkh) - KEY_SIZE);

	करो_balance_mark_पूर्णांकernal_dirty(dest_bi->tb, dest, 0);

	अगर (dest_bi->bi_parent) अणु
		काष्ठा disk_child *t_dc;
		t_dc = B_N_CHILD(dest_bi->bi_parent, dest_bi->bi_position);
		put_dc_size(t_dc, dc_size(t_dc) + KEY_SIZE);

		करो_balance_mark_पूर्णांकernal_dirty(dest_bi->tb, dest_bi->bi_parent,
					       0);
	पूर्ण
पूर्ण

/*
 * Insert d_key'th (delimiting) key from buffer cfl to tail of dest.
 * Copy poपूर्णांकer_amount node poपूर्णांकers and poपूर्णांकer_amount - 1 items from
 * buffer src to buffer dest.
 * Replace  d_key'th key in buffer cfl.
 * Delete poपूर्णांकer_amount items and node poपूर्णांकers from buffer src.
 */
/* this can be invoked both to shअगरt from S to L and from R to S */
अटल व्योम पूर्णांकernal_shअगरt_left(
				/*
				 * INTERNAL_FROM_S_TO_L | INTERNAL_FROM_R_TO_S
				 */
				पूर्णांक mode,
				काष्ठा tree_balance *tb,
				पूर्णांक h, पूर्णांक poपूर्णांकer_amount)
अणु
	काष्ठा buffer_info dest_bi, src_bi;
	काष्ठा buffer_head *cf;
	पूर्णांक d_key_position;

	पूर्णांकernal_define_dest_src_infos(mode, tb, h, &dest_bi, &src_bi,
				       &d_key_position, &cf);

	/*prपूर्णांकk("pointer_amount = %d\n",poपूर्णांकer_amount); */

	अगर (poपूर्णांकer_amount) अणु
		/*
		 * insert delimiting key from common father of dest and
		 * src to node dest पूर्णांकo position B_NR_ITEM(dest)
		 */
		पूर्णांकernal_insert_key(&dest_bi, B_NR_ITEMS(dest_bi.bi_bh), cf,
				    d_key_position);

		अगर (B_NR_ITEMS(src_bi.bi_bh) == poपूर्णांकer_amount - 1) अणु
			अगर (src_bi.bi_position /*src->b_item_order */  == 0)
				replace_key(tb, cf, d_key_position,
					    src_bi.
					    bi_parent /*src->b_parent */ , 0);
		पूर्ण अन्यथा
			replace_key(tb, cf, d_key_position, src_bi.bi_bh,
				    poपूर्णांकer_amount - 1);
	पूर्ण
	/* last parameter is del_parameter */
	पूर्णांकernal_move_poपूर्णांकers_items(&dest_bi, &src_bi, FIRST_TO_LAST,
				     poपूर्णांकer_amount, 0);

पूर्ण

/*
 * Insert delimiting key to L[h].
 * Copy n node poपूर्णांकers and n - 1 items from buffer S[h] to L[h].
 * Delete n - 1 items and node poपूर्णांकers from buffer S[h].
 */
/* it always shअगरts from S[h] to L[h] */
अटल व्योम पूर्णांकernal_shअगरt1_left(काष्ठा tree_balance *tb,
				 पूर्णांक h, पूर्णांक poपूर्णांकer_amount)
अणु
	काष्ठा buffer_info dest_bi, src_bi;
	काष्ठा buffer_head *cf;
	पूर्णांक d_key_position;

	पूर्णांकernal_define_dest_src_infos(INTERNAL_SHIFT_FROM_S_TO_L, tb, h,
				       &dest_bi, &src_bi, &d_key_position, &cf);

	/* insert lkey[h]-th key  from CFL[h] to left neighbor L[h] */
	अगर (poपूर्णांकer_amount > 0)
		पूर्णांकernal_insert_key(&dest_bi, B_NR_ITEMS(dest_bi.bi_bh), cf,
				    d_key_position);

	/* last parameter is del_parameter */
	पूर्णांकernal_move_poपूर्णांकers_items(&dest_bi, &src_bi, FIRST_TO_LAST,
				     poपूर्णांकer_amount, 1);
पूर्ण

/*
 * Insert d_key'th (delimiting) key from buffer cfr to head of dest.
 * Copy n node poपूर्णांकers and n - 1 items from buffer src to buffer dest.
 * Replace  d_key'th key in buffer cfr.
 * Delete n items and node poपूर्णांकers from buffer src.
 */
अटल व्योम पूर्णांकernal_shअगरt_right(
				 /*
				  * INTERNAL_FROM_S_TO_R | INTERNAL_FROM_L_TO_S
				  */
				 पूर्णांक mode,
				 काष्ठा tree_balance *tb,
				 पूर्णांक h, पूर्णांक poपूर्णांकer_amount)
अणु
	काष्ठा buffer_info dest_bi, src_bi;
	काष्ठा buffer_head *cf;
	पूर्णांक d_key_position;
	पूर्णांक nr;

	पूर्णांकernal_define_dest_src_infos(mode, tb, h, &dest_bi, &src_bi,
				       &d_key_position, &cf);

	nr = B_NR_ITEMS(src_bi.bi_bh);

	अगर (poपूर्णांकer_amount > 0) अणु
		/*
		 * insert delimiting key from common father of dest
		 * and src to dest node पूर्णांकo position 0
		 */
		पूर्णांकernal_insert_key(&dest_bi, 0, cf, d_key_position);
		अगर (nr == poपूर्णांकer_amount - 1) अणु
			RFALSE(src_bi.bi_bh != PATH_H_PBUFFER(tb->tb_path, h) /*tb->S[h] */ ||
			       dest_bi.bi_bh != tb->R[h],
			       "src (%p) must be == tb->S[h](%p) when it disappears",
			       src_bi.bi_bh, PATH_H_PBUFFER(tb->tb_path, h));
			/* when S[h] disappers replace left delemiting key as well */
			अगर (tb->CFL[h])
				replace_key(tb, cf, d_key_position, tb->CFL[h],
					    tb->lkey[h]);
		पूर्ण अन्यथा
			replace_key(tb, cf, d_key_position, src_bi.bi_bh,
				    nr - poपूर्णांकer_amount);
	पूर्ण

	/* last parameter is del_parameter */
	पूर्णांकernal_move_poपूर्णांकers_items(&dest_bi, &src_bi, LAST_TO_FIRST,
				     poपूर्णांकer_amount, 0);
पूर्ण

/*
 * Insert delimiting key to R[h].
 * Copy n node poपूर्णांकers and n - 1 items from buffer S[h] to R[h].
 * Delete n - 1 items and node poपूर्णांकers from buffer S[h].
 */
/* it always shअगरt from S[h] to R[h] */
अटल व्योम पूर्णांकernal_shअगरt1_right(काष्ठा tree_balance *tb,
				  पूर्णांक h, पूर्णांक poपूर्णांकer_amount)
अणु
	काष्ठा buffer_info dest_bi, src_bi;
	काष्ठा buffer_head *cf;
	पूर्णांक d_key_position;

	पूर्णांकernal_define_dest_src_infos(INTERNAL_SHIFT_FROM_S_TO_R, tb, h,
				       &dest_bi, &src_bi, &d_key_position, &cf);

	/* insert rkey from CFR[h] to right neighbor R[h] */
	अगर (poपूर्णांकer_amount > 0)
		पूर्णांकernal_insert_key(&dest_bi, 0, cf, d_key_position);

	/* last parameter is del_parameter */
	पूर्णांकernal_move_poपूर्णांकers_items(&dest_bi, &src_bi, LAST_TO_FIRST,
				     poपूर्णांकer_amount, 1);
पूर्ण

/*
 * Delete insert_num node poपूर्णांकers together with their left items
 * and balance current node.
 */
अटल व्योम balance_पूर्णांकernal_when_delete(काष्ठा tree_balance *tb,
					 पूर्णांक h, पूर्णांक child_pos)
अणु
	पूर्णांक insert_num;
	पूर्णांक n;
	काष्ठा buffer_head *tbSh = PATH_H_PBUFFER(tb->tb_path, h);
	काष्ठा buffer_info bi;

	insert_num = tb->insert_size[h] / ((पूर्णांक)(DC_SIZE + KEY_SIZE));

	/* delete child-node-poपूर्णांकer(s) together with their left item(s) */
	bi.tb = tb;
	bi.bi_bh = tbSh;
	bi.bi_parent = PATH_H_PPARENT(tb->tb_path, h);
	bi.bi_position = PATH_H_POSITION(tb->tb_path, h + 1);

	पूर्णांकernal_delete_childs(&bi, child_pos, -insert_num);

	RFALSE(tb->blknum[h] > 1,
	       "tb->blknum[%d]=%d when insert_size < 0", h, tb->blknum[h]);

	n = B_NR_ITEMS(tbSh);

	अगर (tb->lnum[h] == 0 && tb->rnum[h] == 0) अणु
		अगर (tb->blknum[h] == 0) अणु
			/* node S[h] (root of the tree) is empty now */
			काष्ठा buffer_head *new_root;

			RFALSE(n
			       || B_FREE_SPACE(tbSh) !=
			       MAX_CHILD_SIZE(tbSh) - DC_SIZE,
			       "buffer must have only 0 keys (%d)", n);
			RFALSE(bi.bi_parent, "root has parent (%p)",
			       bi.bi_parent);

			/* choose a new root */
			अगर (!tb->L[h - 1] || !B_NR_ITEMS(tb->L[h - 1]))
				new_root = tb->R[h - 1];
			अन्यथा
				new_root = tb->L[h - 1];
			/*
			 * चयन super block's tree root block
			 * number to the new value */
			PUT_SB_ROOT_BLOCK(tb->tb_sb, new_root->b_blocknr);
			/*REISERFS_SB(tb->tb_sb)->s_rs->s_tree_height --; */
			PUT_SB_TREE_HEIGHT(tb->tb_sb,
					   SB_TREE_HEIGHT(tb->tb_sb) - 1);

			करो_balance_mark_sb_dirty(tb,
						 REISERFS_SB(tb->tb_sb)->s_sbh,
						 1);
			/*&&&&&&&&&&&&&&&&&&&&&& */
			/* use check_पूर्णांकernal अगर new root is an पूर्णांकernal node */
			अगर (h > 1)
				check_पूर्णांकernal(new_root);
			/*&&&&&&&&&&&&&&&&&&&&&& */

			/* करो what is needed क्रम buffer thrown from tree */
			reiserfs_invalidate_buffer(tb, tbSh);
			वापस;
		पूर्ण
		वापस;
	पूर्ण

	/* join S[h] with L[h] */
	अगर (tb->L[h] && tb->lnum[h] == -B_NR_ITEMS(tb->L[h]) - 1) अणु

		RFALSE(tb->rnum[h] != 0,
		       "invalid tb->rnum[%d]==%d when joining S[h] with L[h]",
		       h, tb->rnum[h]);

		पूर्णांकernal_shअगरt_left(INTERNAL_SHIFT_FROM_S_TO_L, tb, h, n + 1);
		reiserfs_invalidate_buffer(tb, tbSh);

		वापस;
	पूर्ण

	/* join S[h] with R[h] */
	अगर (tb->R[h] && tb->rnum[h] == -B_NR_ITEMS(tb->R[h]) - 1) अणु
		RFALSE(tb->lnum[h] != 0,
		       "invalid tb->lnum[%d]==%d when joining S[h] with R[h]",
		       h, tb->lnum[h]);

		पूर्णांकernal_shअगरt_right(INTERNAL_SHIFT_FROM_S_TO_R, tb, h, n + 1);

		reiserfs_invalidate_buffer(tb, tbSh);
		वापस;
	पूर्ण

	/* borrow from left neighbor L[h] */
	अगर (tb->lnum[h] < 0) अणु
		RFALSE(tb->rnum[h] != 0,
		       "wrong tb->rnum[%d]==%d when borrow from L[h]", h,
		       tb->rnum[h]);
		पूर्णांकernal_shअगरt_right(INTERNAL_SHIFT_FROM_L_TO_S, tb, h,
				     -tb->lnum[h]);
		वापस;
	पूर्ण

	/* borrow from right neighbor R[h] */
	अगर (tb->rnum[h] < 0) अणु
		RFALSE(tb->lnum[h] != 0,
		       "invalid tb->lnum[%d]==%d when borrow from R[h]",
		       h, tb->lnum[h]);
		पूर्णांकernal_shअगरt_left(INTERNAL_SHIFT_FROM_R_TO_S, tb, h, -tb->rnum[h]);	/*tb->S[h], tb->CFR[h], tb->rkey[h], tb->R[h], -tb->rnum[h]); */
		वापस;
	पूर्ण

	/* split S[h] पूर्णांकo two parts and put them पूर्णांकo neighbors */
	अगर (tb->lnum[h] > 0) अणु
		RFALSE(tb->rnum[h] == 0 || tb->lnum[h] + tb->rnum[h] != n + 1,
		       "invalid tb->lnum[%d]==%d or tb->rnum[%d]==%d when S[h](item number == %d) is split between them",
		       h, tb->lnum[h], h, tb->rnum[h], n);

		पूर्णांकernal_shअगरt_left(INTERNAL_SHIFT_FROM_S_TO_L, tb, h, tb->lnum[h]);	/*tb->L[h], tb->CFL[h], tb->lkey[h], tb->S[h], tb->lnum[h]); */
		पूर्णांकernal_shअगरt_right(INTERNAL_SHIFT_FROM_S_TO_R, tb, h,
				     tb->rnum[h]);

		reiserfs_invalidate_buffer(tb, tbSh);

		वापस;
	पूर्ण
	reiserfs_panic(tb->tb_sb, "ibalance-2",
		       "unexpected tb->lnum[%d]==%d or tb->rnum[%d]==%d",
		       h, tb->lnum[h], h, tb->rnum[h]);
पूर्ण

/* Replace delimiting key of buffers L[h] and S[h] by the given key.*/
अटल व्योम replace_lkey(काष्ठा tree_balance *tb, पूर्णांक h, काष्ठा item_head *key)
अणु
	RFALSE(tb->L[h] == शून्य || tb->CFL[h] == शून्य,
	       "L[h](%p) and CFL[h](%p) must exist in replace_lkey",
	       tb->L[h], tb->CFL[h]);

	अगर (B_NR_ITEMS(PATH_H_PBUFFER(tb->tb_path, h)) == 0)
		वापस;

	स_नकल(पूर्णांकernal_key(tb->CFL[h], tb->lkey[h]), key, KEY_SIZE);

	करो_balance_mark_पूर्णांकernal_dirty(tb, tb->CFL[h], 0);
पूर्ण

/* Replace delimiting key of buffers S[h] and R[h] by the given key.*/
अटल व्योम replace_rkey(काष्ठा tree_balance *tb, पूर्णांक h, काष्ठा item_head *key)
अणु
	RFALSE(tb->R[h] == शून्य || tb->CFR[h] == शून्य,
	       "R[h](%p) and CFR[h](%p) must exist in replace_rkey",
	       tb->R[h], tb->CFR[h]);
	RFALSE(B_NR_ITEMS(tb->R[h]) == 0,
	       "R[h] can not be empty if it exists (item number=%d)",
	       B_NR_ITEMS(tb->R[h]));

	स_नकल(पूर्णांकernal_key(tb->CFR[h], tb->rkey[h]), key, KEY_SIZE);

	करो_balance_mark_पूर्णांकernal_dirty(tb, tb->CFR[h], 0);
पूर्ण


/*
 * अगर inserting/pasting अणु
 *   child_pos is the position of the node-poपूर्णांकer in S[h] that
 *   poपूर्णांकed to S[h-1] beक्रमe balancing of the h-1 level;
 *   this means that new poपूर्णांकers and items must be inserted AFTER
 *   child_pos
 * पूर्ण अन्यथा अणु
 *   it is the position of the lefपंचांगost poपूर्णांकer that must be deleted
 *   (together with its corresponding key to the left of the poपूर्णांकer)
 *   as a result of the previous level's balancing.
 * पूर्ण
 */

पूर्णांक balance_पूर्णांकernal(काष्ठा tree_balance *tb,
		     पूर्णांक h,	/* level of the tree */
		     पूर्णांक child_pos,
		     /* key क्रम insertion on higher level    */
		     काष्ठा item_head *insert_key,
		     /* node क्रम insertion on higher level */
		     काष्ठा buffer_head **insert_ptr)
अणु
	काष्ठा buffer_head *tbSh = PATH_H_PBUFFER(tb->tb_path, h);
	काष्ठा buffer_info bi;

	/*
	 * we वापस this: it is 0 अगर there is no S[h],
	 * अन्यथा it is tb->S[h]->b_item_order
	 */
	पूर्णांक order;
	पूर्णांक insert_num, n, k;
	काष्ठा buffer_head *S_new;
	काष्ठा item_head new_insert_key;
	काष्ठा buffer_head *new_insert_ptr = शून्य;
	काष्ठा item_head *new_insert_key_addr = insert_key;

	RFALSE(h < 1, "h (%d) can not be < 1 on internal level", h);

	PROC_INFO_INC(tb->tb_sb, balance_at[h]);

	order =
	    (tbSh) ? PATH_H_POSITION(tb->tb_path,
				     h + 1) /*tb->S[h]->b_item_order */ : 0;

	/*
	 * Using insert_size[h] calculate the number insert_num of items
	 * that must be inserted to or deleted from S[h].
	 */
	insert_num = tb->insert_size[h] / ((पूर्णांक)(KEY_SIZE + DC_SIZE));

	/* Check whether insert_num is proper * */
	RFALSE(insert_num < -2 || insert_num > 2,
	       "incorrect number of items inserted to the internal node (%d)",
	       insert_num);
	RFALSE(h > 1 && (insert_num > 1 || insert_num < -1),
	       "incorrect number of items (%d) inserted to the internal node on a level (h=%d) higher than last internal level",
	       insert_num, h);

	/* Make balance in हाल insert_num < 0 */
	अगर (insert_num < 0) अणु
		balance_पूर्णांकernal_when_delete(tb, h, child_pos);
		वापस order;
	पूर्ण

	k = 0;
	अगर (tb->lnum[h] > 0) अणु
		/*
		 * shअगरt lnum[h] items from S[h] to the left neighbor L[h].
		 * check how many of new items fall पूर्णांकo L[h] or CFL[h] after
		 * shअगरting
		 */
		n = B_NR_ITEMS(tb->L[h]);	/* number of items in L[h] */
		अगर (tb->lnum[h] <= child_pos) अणु
			/* new items करोn't fall पूर्णांकo L[h] or CFL[h] */
			पूर्णांकernal_shअगरt_left(INTERNAL_SHIFT_FROM_S_TO_L, tb, h,
					    tb->lnum[h]);
			child_pos -= tb->lnum[h];
		पूर्ण अन्यथा अगर (tb->lnum[h] > child_pos + insert_num) अणु
			/* all new items fall पूर्णांकo L[h] */
			पूर्णांकernal_shअगरt_left(INTERNAL_SHIFT_FROM_S_TO_L, tb, h,
					    tb->lnum[h] - insert_num);
			/* insert insert_num keys and node-poपूर्णांकers पूर्णांकo L[h] */
			bi.tb = tb;
			bi.bi_bh = tb->L[h];
			bi.bi_parent = tb->FL[h];
			bi.bi_position = get_left_neighbor_position(tb, h);
			पूर्णांकernal_insert_childs(&bi,
					       /*tb->L[h], tb->S[h-1]->b_next */
					       n + child_pos + 1,
					       insert_num, insert_key,
					       insert_ptr);

			insert_num = 0;
		पूर्ण अन्यथा अणु
			काष्ठा disk_child *dc;

			/*
			 * some items fall पूर्णांकo L[h] or CFL[h],
			 * but some करोn't fall
			 */
			पूर्णांकernal_shअगरt1_left(tb, h, child_pos + 1);
			/* calculate number of new items that fall पूर्णांकo L[h] */
			k = tb->lnum[h] - child_pos - 1;
			bi.tb = tb;
			bi.bi_bh = tb->L[h];
			bi.bi_parent = tb->FL[h];
			bi.bi_position = get_left_neighbor_position(tb, h);
			पूर्णांकernal_insert_childs(&bi,
					       /*tb->L[h], tb->S[h-1]->b_next, */
					       n + child_pos + 1, k,
					       insert_key, insert_ptr);

			replace_lkey(tb, h, insert_key + k);

			/*
			 * replace the first node-ptr in S[h] by
			 * node-ptr to insert_ptr[k]
			 */
			dc = B_N_CHILD(tbSh, 0);
			put_dc_size(dc,
				    MAX_CHILD_SIZE(insert_ptr[k]) -
				    B_FREE_SPACE(insert_ptr[k]));
			put_dc_block_number(dc, insert_ptr[k]->b_blocknr);

			करो_balance_mark_पूर्णांकernal_dirty(tb, tbSh, 0);

			k++;
			insert_key += k;
			insert_ptr += k;
			insert_num -= k;
			child_pos = 0;
		पूर्ण
	पूर्ण
	/* tb->lnum[h] > 0 */
	अगर (tb->rnum[h] > 0) अणु
		/*shअगरt rnum[h] items from S[h] to the right neighbor R[h] */
		/*
		 * check how many of new items fall पूर्णांकo R or CFR
		 * after shअगरting
		 */
		n = B_NR_ITEMS(tbSh);	/* number of items in S[h] */
		अगर (n - tb->rnum[h] >= child_pos)
			/* new items fall पूर्णांकo S[h] */
			पूर्णांकernal_shअगरt_right(INTERNAL_SHIFT_FROM_S_TO_R, tb, h,
					     tb->rnum[h]);
		अन्यथा अगर (n + insert_num - tb->rnum[h] < child_pos) अणु
			/* all new items fall पूर्णांकo R[h] */
			पूर्णांकernal_shअगरt_right(INTERNAL_SHIFT_FROM_S_TO_R, tb, h,
					     tb->rnum[h] - insert_num);

			/* insert insert_num keys and node-poपूर्णांकers पूर्णांकo R[h] */
			bi.tb = tb;
			bi.bi_bh = tb->R[h];
			bi.bi_parent = tb->FR[h];
			bi.bi_position = get_right_neighbor_position(tb, h);
			पूर्णांकernal_insert_childs(&bi,
					       /*tb->R[h],tb->S[h-1]->b_next */
					       child_pos - n - insert_num +
					       tb->rnum[h] - 1,
					       insert_num, insert_key,
					       insert_ptr);
			insert_num = 0;
		पूर्ण अन्यथा अणु
			काष्ठा disk_child *dc;

			/* one of the items falls पूर्णांकo CFR[h] */
			पूर्णांकernal_shअगरt1_right(tb, h, n - child_pos + 1);
			/* calculate number of new items that fall पूर्णांकo R[h] */
			k = tb->rnum[h] - n + child_pos - 1;
			bi.tb = tb;
			bi.bi_bh = tb->R[h];
			bi.bi_parent = tb->FR[h];
			bi.bi_position = get_right_neighbor_position(tb, h);
			पूर्णांकernal_insert_childs(&bi,
					       /*tb->R[h], tb->R[h]->b_child, */
					       0, k, insert_key + 1,
					       insert_ptr + 1);

			replace_rkey(tb, h, insert_key + insert_num - k - 1);

			/*
			 * replace the first node-ptr in R[h] by
			 * node-ptr insert_ptr[insert_num-k-1]
			 */
			dc = B_N_CHILD(tb->R[h], 0);
			put_dc_size(dc,
				    MAX_CHILD_SIZE(insert_ptr
						   [insert_num - k - 1]) -
				    B_FREE_SPACE(insert_ptr
						 [insert_num - k - 1]));
			put_dc_block_number(dc,
					    insert_ptr[insert_num - k -
						       1]->b_blocknr);

			करो_balance_mark_पूर्णांकernal_dirty(tb, tb->R[h], 0);

			insert_num -= (k + 1);
		पूर्ण
	पूर्ण

	/** Fill new node that appears instead of S[h] **/
	RFALSE(tb->blknum[h] > 2, "blknum can not be > 2 for internal level");
	RFALSE(tb->blknum[h] < 0, "blknum can not be < 0");

	अगर (!tb->blknum[h]) अणु	/* node S[h] is empty now */
		RFALSE(!tbSh, "S[h] is equal NULL");

		/* करो what is needed क्रम buffer thrown from tree */
		reiserfs_invalidate_buffer(tb, tbSh);
		वापस order;
	पूर्ण

	अगर (!tbSh) अणु
		/* create new root */
		काष्ठा disk_child *dc;
		काष्ठा buffer_head *tbSh_1 = PATH_H_PBUFFER(tb->tb_path, h - 1);
		काष्ठा block_head *blkh;

		अगर (tb->blknum[h] != 1)
			reiserfs_panic(शून्य, "ibalance-3", "One new node "
				       "required for creating the new root");
		/* S[h] = empty buffer from the list FEB. */
		tbSh = get_FEB(tb);
		blkh = B_BLK_HEAD(tbSh);
		set_blkh_level(blkh, h + 1);

		/* Put the unique node-poपूर्णांकer to S[h] that poपूर्णांकs to S[h-1]. */

		dc = B_N_CHILD(tbSh, 0);
		put_dc_block_number(dc, tbSh_1->b_blocknr);
		put_dc_size(dc,
			    (MAX_CHILD_SIZE(tbSh_1) - B_FREE_SPACE(tbSh_1)));

		tb->insert_size[h] -= DC_SIZE;
		set_blkh_मुक्त_space(blkh, blkh_मुक्त_space(blkh) - DC_SIZE);

		करो_balance_mark_पूर्णांकernal_dirty(tb, tbSh, 0);

		/*&&&&&&&&&&&&&&&&&&&&&&&& */
		check_पूर्णांकernal(tbSh);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */

		/* put new root पूर्णांकo path काष्ठाure */
		PATH_OFFSET_PBUFFER(tb->tb_path, ILLEGAL_PATH_ELEMENT_OFFSET) =
		    tbSh;

		/* Change root in काष्ठाure super block. */
		PUT_SB_ROOT_BLOCK(tb->tb_sb, tbSh->b_blocknr);
		PUT_SB_TREE_HEIGHT(tb->tb_sb, SB_TREE_HEIGHT(tb->tb_sb) + 1);
		करो_balance_mark_sb_dirty(tb, REISERFS_SB(tb->tb_sb)->s_sbh, 1);
	पूर्ण

	अगर (tb->blknum[h] == 2) अणु
		पूर्णांक snum;
		काष्ठा buffer_info dest_bi, src_bi;

		/* S_new = मुक्त buffer from list FEB */
		S_new = get_FEB(tb);

		set_blkh_level(B_BLK_HEAD(S_new), h + 1);

		dest_bi.tb = tb;
		dest_bi.bi_bh = S_new;
		dest_bi.bi_parent = शून्य;
		dest_bi.bi_position = 0;
		src_bi.tb = tb;
		src_bi.bi_bh = tbSh;
		src_bi.bi_parent = PATH_H_PPARENT(tb->tb_path, h);
		src_bi.bi_position = PATH_H_POSITION(tb->tb_path, h + 1);

		n = B_NR_ITEMS(tbSh);	/* number of items in S[h] */
		snum = (insert_num + n + 1) / 2;
		अगर (n - snum >= child_pos) अणु
			/* new items करोn't fall पूर्णांकo S_new */
			/*  store the delimiting key क्रम the next level */
			/* new_insert_key = (n - snum)'th key in S[h] */
			स_नकल(&new_insert_key, पूर्णांकernal_key(tbSh, n - snum),
			       KEY_SIZE);
			/* last parameter is del_par */
			पूर्णांकernal_move_poपूर्णांकers_items(&dest_bi, &src_bi,
						     LAST_TO_FIRST, snum, 0);
		पूर्ण अन्यथा अगर (n + insert_num - snum < child_pos) अणु
			/* all new items fall पूर्णांकo S_new */
			/*  store the delimiting key क्रम the next level */
			/*
			 * new_insert_key = (n + insert_item - snum)'th
			 * key in S[h]
			 */
			स_नकल(&new_insert_key,
			       पूर्णांकernal_key(tbSh, n + insert_num - snum),
			       KEY_SIZE);
			/* last parameter is del_par */
			पूर्णांकernal_move_poपूर्णांकers_items(&dest_bi, &src_bi,
						     LAST_TO_FIRST,
						     snum - insert_num, 0);

			/*
			 * insert insert_num keys and node-poपूर्णांकers
			 * पूर्णांकo S_new
			 */
			पूर्णांकernal_insert_childs(&dest_bi,
					       /*S_new,tb->S[h-1]->b_next, */
					       child_pos - n - insert_num +
					       snum - 1,
					       insert_num, insert_key,
					       insert_ptr);

			insert_num = 0;
		पूर्ण अन्यथा अणु
			काष्ठा disk_child *dc;

			/* some items fall पूर्णांकo S_new, but some करोn't fall */
			/* last parameter is del_par */
			पूर्णांकernal_move_poपूर्णांकers_items(&dest_bi, &src_bi,
						     LAST_TO_FIRST,
						     n - child_pos + 1, 1);
			/* calculate number of new items that fall पूर्णांकo S_new */
			k = snum - n + child_pos - 1;

			पूर्णांकernal_insert_childs(&dest_bi, /*S_new, */ 0, k,
					       insert_key + 1, insert_ptr + 1);

			/* new_insert_key = insert_key[insert_num - k - 1] */
			स_नकल(&new_insert_key, insert_key + insert_num - k - 1,
			       KEY_SIZE);
			/*
			 * replace first node-ptr in S_new by node-ptr
			 * to insert_ptr[insert_num-k-1]
			 */

			dc = B_N_CHILD(S_new, 0);
			put_dc_size(dc,
				    (MAX_CHILD_SIZE
				     (insert_ptr[insert_num - k - 1]) -
				     B_FREE_SPACE(insert_ptr
						  [insert_num - k - 1])));
			put_dc_block_number(dc,
					    insert_ptr[insert_num - k -
						       1]->b_blocknr);

			करो_balance_mark_पूर्णांकernal_dirty(tb, S_new, 0);

			insert_num -= (k + 1);
		पूर्ण
		/* new_insert_ptr = node_poपूर्णांकer to S_new */
		new_insert_ptr = S_new;

		RFALSE(!buffer_journaled(S_new) || buffer_journal_dirty(S_new)
		       || buffer_dirty(S_new), "cm-00001: bad S_new (%b)",
		       S_new);

		/* S_new is released in unfix_nodes */
	पूर्ण

	n = B_NR_ITEMS(tbSh);	/*number of items in S[h] */

	अगर (0 <= child_pos && child_pos <= n && insert_num > 0) अणु
		bi.tb = tb;
		bi.bi_bh = tbSh;
		bi.bi_parent = PATH_H_PPARENT(tb->tb_path, h);
		bi.bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		पूर्णांकernal_insert_childs(&bi,	/*tbSh, */
				       /*          ( tb->S[h-1]->b_parent == tb->S[h] ) ? tb->S[h-1]->b_next :  tb->S[h]->b_child->b_next, */
				       child_pos, insert_num, insert_key,
				       insert_ptr);
	पूर्ण

	insert_ptr[0] = new_insert_ptr;
	अगर (new_insert_ptr)
		स_नकल(new_insert_key_addr, &new_insert_key, KEY_SIZE);

	वापस order;
पूर्ण
