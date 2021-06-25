<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/समय.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "reiserfs.h"
#समावेश <linux/buffer_head.h>

/*
 * To make any changes in the tree we find a node that contains item
 * to be changed/deleted or position in the node we insert a new item
 * to. We call this node S. To करो balancing we need to decide what we
 * will shअगरt to left/right neighbor, or to a new node, where new item
 * will be etc. To make this analysis simpler we build भव
 * node. Virtual node is an array of items, that will replace items of
 * node S. (For instance अगर we are going to delete an item, भव
 * node करोes not contain it). Virtual node keeps inक्रमmation about
 * item sizes and types, mergeability of first and last items, sizes
 * of all entries in directory item. We use this array of items when
 * calculating what we can shअगरt to neighbors and how many nodes we
 * have to have अगर we करो not any shअगरtings, अगर we shअगरt to left/right
 * neighbor or to both.
 */

/*
 * Takes item number in भव node, वापसs number of item
 * that it has in source buffer
 */
अटल अंतरभूत पूर्णांक old_item_num(पूर्णांक new_num, पूर्णांक affected_item_num, पूर्णांक mode)
अणु
	अगर (mode == M_PASTE || mode == M_CUT || new_num < affected_item_num)
		वापस new_num;

	अगर (mode == M_INSERT) अणु

		RFALSE(new_num == 0,
		       "vs-8005: for INSERT mode and item number of inserted item");

		वापस new_num - 1;
	पूर्ण

	RFALSE(mode != M_DELETE,
	       "vs-8010: old_item_num: mode must be M_DELETE (mode = \'%c\'",
	       mode);
	/* delete mode */
	वापस new_num + 1;
पूर्ण

अटल व्योम create_भव_node(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा item_head *ih;
	काष्ठा भव_node *vn = tb->tb_vn;
	पूर्णांक new_num;
	काष्ठा buffer_head *Sh;	/* this comes from tb->S[h] */

	Sh = PATH_H_PBUFFER(tb->tb_path, h);

	/* size of changed node */
	vn->vn_size =
	    MAX_CHILD_SIZE(Sh) - B_FREE_SPACE(Sh) + tb->insert_size[h];

	/* क्रम पूर्णांकernal nodes array अगर भव items is not created */
	अगर (h) अणु
		vn->vn_nr_item = (vn->vn_size - DC_SIZE) / (DC_SIZE + KEY_SIZE);
		वापस;
	पूर्ण

	/* number of items in भव node  */
	vn->vn_nr_item =
	    B_NR_ITEMS(Sh) + ((vn->vn_mode == M_INSERT) ? 1 : 0) -
	    ((vn->vn_mode == M_DELETE) ? 1 : 0);

	/* first भव item */
	vn->vn_vi = (काष्ठा भव_item *)(tb->tb_vn + 1);
	स_रखो(vn->vn_vi, 0, vn->vn_nr_item * माप(काष्ठा भव_item));
	vn->vn_मुक्त_ptr += vn->vn_nr_item * माप(काष्ठा भव_item);

	/* first item in the node */
	ih = item_head(Sh, 0);

	/* define the mergeability क्रम 0-th item (अगर it is not being deleted) */
	अगर (op_is_left_mergeable(&ih->ih_key, Sh->b_size)
	    && (vn->vn_mode != M_DELETE || vn->vn_affected_item_num))
		vn->vn_vi[0].vi_type |= VI_TYPE_LEFT_MERGEABLE;

	/*
	 * go through all items that reमुख्य in the भव
	 * node (except क्रम the new (inserted) one)
	 */
	क्रम (new_num = 0; new_num < vn->vn_nr_item; new_num++) अणु
		पूर्णांक j;
		काष्ठा भव_item *vi = vn->vn_vi + new_num;
		पूर्णांक is_affected =
		    ((new_num != vn->vn_affected_item_num) ? 0 : 1);

		अगर (is_affected && vn->vn_mode == M_INSERT)
			जारी;

		/* get item number in source node */
		j = old_item_num(new_num, vn->vn_affected_item_num,
				 vn->vn_mode);

		vi->vi_item_len += ih_item_len(ih + j) + IH_SIZE;
		vi->vi_ih = ih + j;
		vi->vi_item = ih_item_body(Sh, ih + j);
		vi->vi_uarea = vn->vn_मुक्त_ptr;

		/*
		 * FIXME: there is no check that item operation did not
		 * consume too much memory
		 */
		vn->vn_मुक्त_ptr +=
		    op_create_vi(vn, vi, is_affected, tb->insert_size[0]);
		अगर (tb->vn_buf + tb->vn_buf_size < vn->vn_मुक्त_ptr)
			reiserfs_panic(tb->tb_sb, "vs-8030",
				       "virtual node space consumed");

		अगर (!is_affected)
			/* this is not being changed */
			जारी;

		अगर (vn->vn_mode == M_PASTE || vn->vn_mode == M_CUT) अणु
			vn->vn_vi[new_num].vi_item_len += tb->insert_size[0];
			/* poपूर्णांकer to data which is going to be pasted */
			vi->vi_new_data = vn->vn_data;
		पूर्ण
	पूर्ण

	/* भव inserted item is not defined yet */
	अगर (vn->vn_mode == M_INSERT) अणु
		काष्ठा भव_item *vi = vn->vn_vi + vn->vn_affected_item_num;

		RFALSE(vn->vn_ins_ih == शून्य,
		       "vs-8040: item header of inserted item is not specified");
		vi->vi_item_len = tb->insert_size[0];
		vi->vi_ih = vn->vn_ins_ih;
		vi->vi_item = vn->vn_data;
		vi->vi_uarea = vn->vn_मुक्त_ptr;

		op_create_vi(vn, vi, 0 /*not pasted or cut */ ,
			     tb->insert_size[0]);
	पूर्ण

	/*
	 * set right merge flag we take right delimiting key and
	 * check whether it is a mergeable item
	 */
	अगर (tb->CFR[0]) अणु
		काष्ठा reiserfs_key *key;

		key = पूर्णांकernal_key(tb->CFR[0], tb->rkey[0]);
		अगर (op_is_left_mergeable(key, Sh->b_size)
		    && (vn->vn_mode != M_DELETE
			|| vn->vn_affected_item_num != B_NR_ITEMS(Sh) - 1))
			vn->vn_vi[vn->vn_nr_item - 1].vi_type |=
			    VI_TYPE_RIGHT_MERGEABLE;

#अगर_घोषित CONFIG_REISERFS_CHECK
		अगर (op_is_left_mergeable(key, Sh->b_size) &&
		    !(vn->vn_mode != M_DELETE
		      || vn->vn_affected_item_num != B_NR_ITEMS(Sh) - 1)) अणु
			/*
			 * we delete last item and it could be merged
			 * with right neighbor's first item
			 */
			अगर (!
			    (B_NR_ITEMS(Sh) == 1
			     && is_direntry_le_ih(item_head(Sh, 0))
			     && ih_entry_count(item_head(Sh, 0)) == 1)) अणु
				/*
				 * node contains more than 1 item, or item
				 * is not directory item, or this item
				 * contains more than 1 entry
				 */
				prपूर्णांक_block(Sh, 0, -1, -1);
				reiserfs_panic(tb->tb_sb, "vs-8045",
					       "rdkey %k, affected item==%d "
					       "(mode==%c) Must be %c",
					       key, vn->vn_affected_item_num,
					       vn->vn_mode, M_DELETE);
			पूर्ण
		पूर्ण
#पूर्ण_अगर

	पूर्ण
पूर्ण

/*
 * Using भव node check, how many items can be
 * shअगरted to left neighbor
 */
अटल व्योम check_left(काष्ठा tree_balance *tb, पूर्णांक h, पूर्णांक cur_मुक्त)
अणु
	पूर्णांक i;
	काष्ठा भव_node *vn = tb->tb_vn;
	काष्ठा भव_item *vi;
	पूर्णांक d_size, ih_size;

	RFALSE(cur_मुक्त < 0, "vs-8050: cur_free (%d) < 0", cur_मुक्त);

	/* पूर्णांकernal level */
	अगर (h > 0) अणु
		tb->lnum[h] = cur_मुक्त / (DC_SIZE + KEY_SIZE);
		वापस;
	पूर्ण

	/* leaf level */

	अगर (!cur_मुक्त || !vn->vn_nr_item) अणु
		/* no मुक्त space or nothing to move */
		tb->lnum[h] = 0;
		tb->lbytes = -1;
		वापस;
	पूर्ण

	RFALSE(!PATH_H_PPARENT(tb->tb_path, 0),
	       "vs-8055: parent does not exist or invalid");

	vi = vn->vn_vi;
	अगर ((अचिन्हित पूर्णांक)cur_मुक्त >=
	    (vn->vn_size -
	     ((vi->vi_type & VI_TYPE_LEFT_MERGEABLE) ? IH_SIZE : 0))) अणु
		/* all contents of S[0] fits पूर्णांकo L[0] */

		RFALSE(vn->vn_mode == M_INSERT || vn->vn_mode == M_PASTE,
		       "vs-8055: invalid mode or balance condition failed");

		tb->lnum[0] = vn->vn_nr_item;
		tb->lbytes = -1;
		वापस;
	पूर्ण

	d_size = 0, ih_size = IH_SIZE;

	/* first item may be merge with last item in left neighbor */
	अगर (vi->vi_type & VI_TYPE_LEFT_MERGEABLE)
		d_size = -((पूर्णांक)IH_SIZE), ih_size = 0;

	tb->lnum[0] = 0;
	क्रम (i = 0; i < vn->vn_nr_item;
	     i++, ih_size = IH_SIZE, d_size = 0, vi++) अणु
		d_size += vi->vi_item_len;
		अगर (cur_मुक्त >= d_size) अणु
			/* the item can be shअगरted entirely */
			cur_मुक्त -= d_size;
			tb->lnum[0]++;
			जारी;
		पूर्ण

		/* the item cannot be shअगरted entirely, try to split it */
		/*
		 * check whether L[0] can hold ih and at least one byte
		 * of the item body
		 */

		/* cannot shअगरt even a part of the current item */
		अगर (cur_मुक्त <= ih_size) अणु
			tb->lbytes = -1;
			वापस;
		पूर्ण
		cur_मुक्त -= ih_size;

		tb->lbytes = op_check_left(vi, cur_मुक्त, 0, 0);
		अगर (tb->lbytes != -1)
			/* count partially shअगरted item */
			tb->lnum[0]++;

		अवरोध;
	पूर्ण

	वापस;
पूर्ण

/*
 * Using भव node check, how many items can be
 * shअगरted to right neighbor
 */
अटल व्योम check_right(काष्ठा tree_balance *tb, पूर्णांक h, पूर्णांक cur_मुक्त)
अणु
	पूर्णांक i;
	काष्ठा भव_node *vn = tb->tb_vn;
	काष्ठा भव_item *vi;
	पूर्णांक d_size, ih_size;

	RFALSE(cur_मुक्त < 0, "vs-8070: cur_free < 0");

	/* पूर्णांकernal level */
	अगर (h > 0) अणु
		tb->rnum[h] = cur_मुक्त / (DC_SIZE + KEY_SIZE);
		वापस;
	पूर्ण

	/* leaf level */

	अगर (!cur_मुक्त || !vn->vn_nr_item) अणु
		/* no मुक्त space  */
		tb->rnum[h] = 0;
		tb->rbytes = -1;
		वापस;
	पूर्ण

	RFALSE(!PATH_H_PPARENT(tb->tb_path, 0),
	       "vs-8075: parent does not exist or invalid");

	vi = vn->vn_vi + vn->vn_nr_item - 1;
	अगर ((अचिन्हित पूर्णांक)cur_मुक्त >=
	    (vn->vn_size -
	     ((vi->vi_type & VI_TYPE_RIGHT_MERGEABLE) ? IH_SIZE : 0))) अणु
		/* all contents of S[0] fits पूर्णांकo R[0] */

		RFALSE(vn->vn_mode == M_INSERT || vn->vn_mode == M_PASTE,
		       "vs-8080: invalid mode or balance condition failed");

		tb->rnum[h] = vn->vn_nr_item;
		tb->rbytes = -1;
		वापस;
	पूर्ण

	d_size = 0, ih_size = IH_SIZE;

	/* last item may be merge with first item in right neighbor */
	अगर (vi->vi_type & VI_TYPE_RIGHT_MERGEABLE)
		d_size = -(पूर्णांक)IH_SIZE, ih_size = 0;

	tb->rnum[0] = 0;
	क्रम (i = vn->vn_nr_item - 1; i >= 0;
	     i--, d_size = 0, ih_size = IH_SIZE, vi--) अणु
		d_size += vi->vi_item_len;
		अगर (cur_मुक्त >= d_size) अणु
			/* the item can be shअगरted entirely */
			cur_मुक्त -= d_size;
			tb->rnum[0]++;
			जारी;
		पूर्ण

		/*
		 * check whether R[0] can hold ih and at least one
		 * byte of the item body
		 */

		/* cannot shअगरt even a part of the current item */
		अगर (cur_मुक्त <= ih_size) अणु
			tb->rbytes = -1;
			वापस;
		पूर्ण

		/*
		 * R[0] can hold the header of the item and at least
		 * one byte of its body
		 */
		cur_मुक्त -= ih_size;	/* cur_मुक्त is still > 0 */

		tb->rbytes = op_check_right(vi, cur_मुक्त);
		अगर (tb->rbytes != -1)
			/* count partially shअगरted item */
			tb->rnum[0]++;

		अवरोध;
	पूर्ण

	वापस;
पूर्ण

/*
 * from - number of items, which are shअगरted to left neighbor entirely
 * to - number of item, which are shअगरted to right neighbor entirely
 * from_bytes - number of bytes of boundary item (or directory entries)
 *              which are shअगरted to left neighbor
 * to_bytes - number of bytes of boundary item (or directory entries)
 *            which are shअगरted to right neighbor
 */
अटल पूर्णांक get_num_ver(पूर्णांक mode, काष्ठा tree_balance *tb, पूर्णांक h,
		       पूर्णांक from, पूर्णांक from_bytes,
		       पूर्णांक to, पूर्णांक to_bytes, लघु *snum012, पूर्णांक flow)
अणु
	पूर्णांक i;
	पूर्णांक units;
	काष्ठा भव_node *vn = tb->tb_vn;
	पूर्णांक total_node_size, max_node_size, current_item_size;
	पूर्णांक needed_nodes;

	/* position of item we start filling node from */
	पूर्णांक start_item;

	/* position of item we finish filling node by */
	पूर्णांक end_item;

	/*
	 * number of first bytes (entries क्रम directory) of start_item-th item
	 * we करो not include पूर्णांकo node that is being filled
	 */
	पूर्णांक start_bytes;

	/*
	 * number of last bytes (entries क्रम directory) of end_item-th item
	 * we करो node include पूर्णांकo node that is being filled
	 */
	पूर्णांक end_bytes;

	/*
	 * these are positions in भव item of items, that are split
	 * between S[0] and S1new and S1new and S2new
	 */
	पूर्णांक split_item_positions[2];

	split_item_positions[0] = -1;
	split_item_positions[1] = -1;

	/*
	 * We only create additional nodes अगर we are in insert or paste mode
	 * or we are in replace mode at the पूर्णांकernal level. If h is 0 and
	 * the mode is M_REPLACE then in fix_nodes we change the mode to
	 * paste or insert beक्रमe we get here in the code.
	 */
	RFALSE(tb->insert_size[h] < 0 || (mode != M_INSERT && mode != M_PASTE),
	       "vs-8100: insert_size < 0 in overflow");

	max_node_size = MAX_CHILD_SIZE(PATH_H_PBUFFER(tb->tb_path, h));

	/*
	 * snum012 [0-2] - number of items, that lay
	 * to S[0], first new node and second new node
	 */
	snum012[3] = -1;	/* s1bytes */
	snum012[4] = -1;	/* s2bytes */

	/* पूर्णांकernal level */
	अगर (h > 0) अणु
		i = ((to - from) * (KEY_SIZE + DC_SIZE) + DC_SIZE);
		अगर (i == max_node_size)
			वापस 1;
		वापस (i / max_node_size + 1);
	पूर्ण

	/* leaf level */
	needed_nodes = 1;
	total_node_size = 0;

	/* start from 'from'-th item */
	start_item = from;
	/* skip its first 'start_bytes' units */
	start_bytes = ((from_bytes != -1) ? from_bytes : 0);

	/* last included item is the 'end_item'-th one */
	end_item = vn->vn_nr_item - to - 1;
	/* करो not count last 'end_bytes' units of 'end_item'-th item */
	end_bytes = (to_bytes != -1) ? to_bytes : 0;

	/*
	 * go through all item beginning from the start_item-th item
	 * and ending by the end_item-th item. Do not count first
	 * 'start_bytes' units of 'start_item'-th item and last
	 * 'end_bytes' of 'end_item'-th item
	 */
	क्रम (i = start_item; i <= end_item; i++) अणु
		काष्ठा भव_item *vi = vn->vn_vi + i;
		पूर्णांक skip_from_end = ((i == end_item) ? end_bytes : 0);

		RFALSE(needed_nodes > 3, "vs-8105: too many nodes are needed");

		/* get size of current item */
		current_item_size = vi->vi_item_len;

		/*
		 * करो not take in calculation head part (from_bytes)
		 * of from-th item
		 */
		current_item_size -=
		    op_part_size(vi, 0 /*from start */ , start_bytes);

		/* करो not take in calculation tail part of last item */
		current_item_size -=
		    op_part_size(vi, 1 /*from end */ , skip_from_end);

		/* अगर item fits पूर्णांकo current node entierly */
		अगर (total_node_size + current_item_size <= max_node_size) अणु
			snum012[needed_nodes - 1]++;
			total_node_size += current_item_size;
			start_bytes = 0;
			जारी;
		पूर्ण

		/*
		 * भव item length is दीर्घer, than max size of item in
		 * a node. It is impossible क्रम direct item
		 */
		अगर (current_item_size > max_node_size) अणु
			RFALSE(is_direct_le_ih(vi->vi_ih),
			       "vs-8110: "
			       "direct item length is %d. It can not be longer than %d",
			       current_item_size, max_node_size);
			/* we will try to split it */
			flow = 1;
		पूर्ण

		/* as we करो not split items, take new node and जारी */
		अगर (!flow) अणु
			needed_nodes++;
			i--;
			total_node_size = 0;
			जारी;
		पूर्ण

		/*
		 * calculate number of item units which fit पूर्णांकo node being
		 * filled
		 */
		अणु
			पूर्णांक मुक्त_space;

			मुक्त_space = max_node_size - total_node_size - IH_SIZE;
			units =
			    op_check_left(vi, मुक्त_space, start_bytes,
					  skip_from_end);
			/*
			 * nothing fits पूर्णांकo current node, take new
			 * node and जारी
			 */
			अगर (units == -1) अणु
				needed_nodes++, i--, total_node_size = 0;
				जारी;
			पूर्ण
		पूर्ण

		/* something fits पूर्णांकo the current node */
		start_bytes += units;
		snum012[needed_nodes - 1 + 3] = units;

		अगर (needed_nodes > 2)
			reiserfs_warning(tb->tb_sb, "vs-8111",
					 "split_item_position is out of range");
		snum012[needed_nodes - 1]++;
		split_item_positions[needed_nodes - 1] = i;
		needed_nodes++;
		/* जारी from the same item with start_bytes != -1 */
		start_item = i;
		i--;
		total_node_size = 0;
	पूर्ण

	/*
	 * sum012[4] (अगर it is not -1) contains number of units of which
	 * are to be in S1new, snum012[3] - to be in S0. They are supposed
	 * to be S1bytes and S2bytes correspondingly, so recalculate
	 */
	अगर (snum012[4] > 0) अणु
		पूर्णांक split_item_num;
		पूर्णांक bytes_to_r, bytes_to_l;
		पूर्णांक bytes_to_S1new;

		split_item_num = split_item_positions[1];
		bytes_to_l =
		    ((from == split_item_num
		      && from_bytes != -1) ? from_bytes : 0);
		bytes_to_r =
		    ((end_item == split_item_num
		      && end_bytes != -1) ? end_bytes : 0);
		bytes_to_S1new =
		    ((split_item_positions[0] ==
		      split_item_positions[1]) ? snum012[3] : 0);

		/* s2bytes */
		snum012[4] =
		    op_unit_num(&vn->vn_vi[split_item_num]) - snum012[4] -
		    bytes_to_r - bytes_to_l - bytes_to_S1new;

		अगर (vn->vn_vi[split_item_num].vi_index != TYPE_सूचीENTRY &&
		    vn->vn_vi[split_item_num].vi_index != TYPE_INसूचीECT)
			reiserfs_warning(tb->tb_sb, "vs-8115",
					 "not directory or indirect item");
	पूर्ण

	/* now we know S2bytes, calculate S1bytes */
	अगर (snum012[3] > 0) अणु
		पूर्णांक split_item_num;
		पूर्णांक bytes_to_r, bytes_to_l;
		पूर्णांक bytes_to_S2new;

		split_item_num = split_item_positions[0];
		bytes_to_l =
		    ((from == split_item_num
		      && from_bytes != -1) ? from_bytes : 0);
		bytes_to_r =
		    ((end_item == split_item_num
		      && end_bytes != -1) ? end_bytes : 0);
		bytes_to_S2new =
		    ((split_item_positions[0] == split_item_positions[1]
		      && snum012[4] != -1) ? snum012[4] : 0);

		/* s1bytes */
		snum012[3] =
		    op_unit_num(&vn->vn_vi[split_item_num]) - snum012[3] -
		    bytes_to_r - bytes_to_l - bytes_to_S2new;
	पूर्ण

	वापस needed_nodes;
पूर्ण


/*
 * Set parameters क्रम balancing.
 * Perक्रमms ग_लिखो of results of analysis of balancing पूर्णांकo काष्ठाure tb,
 * where it will later be used by the functions that actually करो the balancing.
 * Parameters:
 *	tb	tree_balance काष्ठाure;
 *	h	current level of the node;
 *	lnum	number of items from S[h] that must be shअगरted to L[h];
 *	rnum	number of items from S[h] that must be shअगरted to R[h];
 *	blk_num	number of blocks that S[h] will be splitted पूर्णांकo;
 *	s012	number of items that fall पूर्णांकo splitted nodes.
 *	lbytes	number of bytes which flow to the left neighbor from the
 *              item that is not shअगरted entirely
 *	rbytes	number of bytes which flow to the right neighbor from the
 *              item that is not shअगरted entirely
 *	s1bytes	number of bytes which flow to the first  new node when
 *              S[0] splits (this number is contained in s012 array)
 */

अटल व्योम set_parameters(काष्ठा tree_balance *tb, पूर्णांक h, पूर्णांक lnum,
			   पूर्णांक rnum, पूर्णांक blk_num, लघु *s012, पूर्णांक lb, पूर्णांक rb)
अणु

	tb->lnum[h] = lnum;
	tb->rnum[h] = rnum;
	tb->blknum[h] = blk_num;

	/* only क्रम leaf level */
	अगर (h == 0) अणु
		अगर (s012 != शून्य) अणु
			tb->s0num = *s012++;
			tb->snum[0] = *s012++;
			tb->snum[1] = *s012++;
			tb->sbytes[0] = *s012++;
			tb->sbytes[1] = *s012;
		पूर्ण
		tb->lbytes = lb;
		tb->rbytes = rb;
	पूर्ण
	PROC_INFO_ADD(tb->tb_sb, lnum[h], lnum);
	PROC_INFO_ADD(tb->tb_sb, rnum[h], rnum);

	PROC_INFO_ADD(tb->tb_sb, lbytes[h], lb);
	PROC_INFO_ADD(tb->tb_sb, rbytes[h], rb);
पूर्ण

/*
 * check अगर node disappears अगर we shअगरt tb->lnum[0] items to left
 * neighbor and tb->rnum[0] to the right one.
 */
अटल पूर्णांक is_leaf_removable(काष्ठा tree_balance *tb)
अणु
	काष्ठा भव_node *vn = tb->tb_vn;
	पूर्णांक to_left, to_right;
	पूर्णांक size;
	पूर्णांक reमुख्य_items;

	/*
	 * number of items that will be shअगरted to left (right) neighbor
	 * entirely
	 */
	to_left = tb->lnum[0] - ((tb->lbytes != -1) ? 1 : 0);
	to_right = tb->rnum[0] - ((tb->rbytes != -1) ? 1 : 0);
	reमुख्य_items = vn->vn_nr_item;

	/* how many items reमुख्य in S[0] after shअगरtings to neighbors */
	reमुख्य_items -= (to_left + to_right);

	/* all content of node can be shअगरted to neighbors */
	अगर (reमुख्य_items < 1) अणु
		set_parameters(tb, 0, to_left, vn->vn_nr_item - to_left, 0,
			       शून्य, -1, -1);
		वापस 1;
	पूर्ण

	/* S[0] is not removable */
	अगर (reमुख्य_items > 1 || tb->lbytes == -1 || tb->rbytes == -1)
		वापस 0;

	/* check whether we can भागide 1 reमुख्यing item between neighbors */

	/* get size of reमुख्यing item (in item units) */
	size = op_unit_num(&vn->vn_vi[to_left]);

	अगर (tb->lbytes + tb->rbytes >= size) अणु
		set_parameters(tb, 0, to_left + 1, to_right + 1, 0, शून्य,
			       tb->lbytes, -1);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* check whether L, S, R can be joined in one node */
अटल पूर्णांक are_leaves_removable(काष्ठा tree_balance *tb, पूर्णांक lमुक्त, पूर्णांक rमुक्त)
अणु
	काष्ठा भव_node *vn = tb->tb_vn;
	पूर्णांक ih_size;
	काष्ठा buffer_head *S0;

	S0 = PATH_H_PBUFFER(tb->tb_path, 0);

	ih_size = 0;
	अगर (vn->vn_nr_item) अणु
		अगर (vn->vn_vi[0].vi_type & VI_TYPE_LEFT_MERGEABLE)
			ih_size += IH_SIZE;

		अगर (vn->vn_vi[vn->vn_nr_item - 1].
		    vi_type & VI_TYPE_RIGHT_MERGEABLE)
			ih_size += IH_SIZE;
	पूर्ण अन्यथा अणु
		/* there was only one item and it will be deleted */
		काष्ठा item_head *ih;

		RFALSE(B_NR_ITEMS(S0) != 1,
		       "vs-8125: item number must be 1: it is %d",
		       B_NR_ITEMS(S0));

		ih = item_head(S0, 0);
		अगर (tb->CFR[0]
		    && !comp_लघु_le_keys(&ih->ih_key,
					   पूर्णांकernal_key(tb->CFR[0],
							  tb->rkey[0])))
			/*
			 * Directory must be in correct state here: that is
			 * somewhere at the left side should exist first
			 * directory item. But the item being deleted can
			 * not be that first one because its right neighbor
			 * is item of the same directory. (But first item
			 * always माला_लो deleted in last turn). So, neighbors
			 * of deleted item can be merged, so we can save
			 * ih_size
			 */
			अगर (is_direntry_le_ih(ih)) अणु
				ih_size = IH_SIZE;

				/*
				 * we might check that left neighbor exists
				 * and is of the same directory
				 */
				RFALSE(le_ih_k_offset(ih) == DOT_OFFSET,
				       "vs-8130: first directory item can not be removed until directory is not empty");
			पूर्ण

	पूर्ण

	अगर (MAX_CHILD_SIZE(S0) + vn->vn_size <= rमुक्त + lमुक्त + ih_size) अणु
		set_parameters(tb, 0, -1, -1, -1, शून्य, -1, -1);
		PROC_INFO_INC(tb->tb_sb, leaves_removable);
		वापस 1;
	पूर्ण
	वापस 0;

पूर्ण

/* when we करो not split item, lnum and rnum are numbers of entire items */
#घोषणा SET_PAR_SHIFT_LEFT \
अगर (h)\
अणु\
   पूर्णांक to_l;\
   \
   to_l = (MAX_NR_KEY(Sh)+1 - lpar + vn->vn_nr_item + 1) / 2 -\
	      (MAX_NR_KEY(Sh) + 1 - lpar);\
	      \
	      set_parameters (tb, h, to_l, 0, lnver, शून्य, -1, -1);\
पूर्ण\
अन्यथा \
अणु\
   अगर (lset==LEFT_SHIFT_FLOW)\
     set_parameters (tb, h, lpar, 0, lnver, snum012+lset,\
		     tb->lbytes, -1);\
   अन्यथा\
     set_parameters (tb, h, lpar - (tb->lbytes!=-1), 0, lnver, snum012+lset,\
		     -1, -1);\
पूर्ण

#घोषणा SET_PAR_SHIFT_RIGHT \
अगर (h)\
अणु\
   पूर्णांक to_r;\
   \
   to_r = (MAX_NR_KEY(Sh)+1 - rpar + vn->vn_nr_item + 1) / 2 - (MAX_NR_KEY(Sh) + 1 - rpar);\
   \
   set_parameters (tb, h, 0, to_r, rnver, शून्य, -1, -1);\
पूर्ण\
अन्यथा \
अणु\
   अगर (rset==RIGHT_SHIFT_FLOW)\
     set_parameters (tb, h, 0, rpar, rnver, snum012+rset,\
		  -1, tb->rbytes);\
   अन्यथा\
     set_parameters (tb, h, 0, rpar - (tb->rbytes!=-1), rnver, snum012+rset,\
		  -1, -1);\
पूर्ण

अटल व्योम मुक्त_buffers_in_tb(काष्ठा tree_balance *tb)
अणु
	पूर्णांक i;

	pathrअन्यथा(tb->tb_path);

	क्रम (i = 0; i < MAX_HEIGHT; i++) अणु
		brअन्यथा(tb->L[i]);
		brअन्यथा(tb->R[i]);
		brअन्यथा(tb->FL[i]);
		brअन्यथा(tb->FR[i]);
		brअन्यथा(tb->CFL[i]);
		brअन्यथा(tb->CFR[i]);

		tb->L[i] = शून्य;
		tb->R[i] = शून्य;
		tb->FL[i] = शून्य;
		tb->FR[i] = शून्य;
		tb->CFL[i] = शून्य;
		tb->CFR[i] = शून्य;
	पूर्ण
पूर्ण

/*
 * Get new buffers क्रम storing new nodes that are created जबतक balancing.
 * Returns:	SCHEDULE_OCCURRED - schedule occurred जबतक the function worked;
 *	        CARRY_ON - schedule didn't occur जबतक the function worked;
 *	        NO_DISK_SPACE - no disk space.
 */
/* The function is NOT SCHEDULE-SAFE! */
अटल पूर्णांक get_empty_nodes(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा buffer_head *new_bh, *Sh = PATH_H_PBUFFER(tb->tb_path, h);
	b_blocknr_t *blocknr, blocknrs[MAX_AMOUNT_NEEDED] = अणु 0, पूर्ण;
	पूर्णांक counter, number_of_मुक्तblk;
	पूर्णांक  amount_needed;	/* number of needed empty blocks */
	पूर्णांक  retval = CARRY_ON;
	काष्ठा super_block *sb = tb->tb_sb;

	/*
	 * number_of_मुक्तblk is the number of empty blocks which have been
	 * acquired क्रम use by the balancing algorithm minus the number of
	 * empty blocks used in the previous levels of the analysis,
	 * number_of_मुक्तblk = tb->cur_blknum can be non-zero अगर a schedule
	 * occurs after empty blocks are acquired, and the balancing analysis
	 * is then restarted, amount_needed is the number needed by this
	 * level (h) of the balancing analysis.
	 *
	 * Note that क्रम प्रणालीs with many processes writing, it would be
	 * more layout optimal to calculate the total number needed by all
	 * levels and then to run reiserfs_new_blocks to get all of them at
	 * once.
	 */

	/*
	 * Initiate number_of_मुक्तblk to the amount acquired prior to the
	 * restart of the analysis or 0 अगर not restarted, then subtract the
	 * amount needed by all of the levels of the tree below h.
	 */
	/* blknum includes S[h], so we subtract 1 in this calculation */
	क्रम (counter = 0, number_of_मुक्तblk = tb->cur_blknum;
	     counter < h; counter++)
		number_of_मुक्तblk -=
		    (tb->blknum[counter]) ? (tb->blknum[counter] -
						   1) : 0;

	/* Allocate missing empty blocks. */
	/* अगर Sh == 0  then we are getting a new root */
	amount_needed = (Sh) ? (tb->blknum[h] - 1) : 1;
	/*
	 * Amount_needed = the amount that we need more than the
	 * amount that we have.
	 */
	अगर (amount_needed > number_of_मुक्तblk)
		amount_needed -= number_of_मुक्तblk;
	अन्यथा	/* If we have enough alपढ़ोy then there is nothing to करो. */
		वापस CARRY_ON;

	/*
	 * No need to check quota - is not allocated क्रम blocks used
	 * क्रम क्रमmatted nodes
	 */
	अगर (reiserfs_new_क्रमm_blocknrs(tb, blocknrs,
				       amount_needed) == NO_DISK_SPACE)
		वापस NO_DISK_SPACE;

	/* क्रम each blocknumber we just got, get a buffer and stick it on FEB */
	क्रम (blocknr = blocknrs, counter = 0;
	     counter < amount_needed; blocknr++, counter++) अणु

		RFALSE(!*blocknr,
		       "PAP-8135: reiserfs_new_blocknrs failed when got new blocks");

		new_bh = sb_getblk(sb, *blocknr);
		RFALSE(buffer_dirty(new_bh) ||
		       buffer_journaled(new_bh) ||
		       buffer_journal_dirty(new_bh),
		       "PAP-8140: journaled or dirty buffer %b for the new block",
		       new_bh);

		/* Put empty buffers पूर्णांकo the array. */
		RFALSE(tb->FEB[tb->cur_blknum],
		       "PAP-8141: busy slot for new buffer");

		set_buffer_journal_new(new_bh);
		tb->FEB[tb->cur_blknum++] = new_bh;
	पूर्ण

	अगर (retval == CARRY_ON && खाताSYSTEM_CHANGED_TB(tb))
		retval = REPEAT_SEARCH;

	वापस retval;
पूर्ण

/*
 * Get मुक्त space of the left neighbor, which is stored in the parent
 * node of the left neighbor.
 */
अटल पूर्णांक get_lमुक्त(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा buffer_head *l, *f;
	पूर्णांक order;

	अगर ((f = PATH_H_PPARENT(tb->tb_path, h)) == शून्य ||
	    (l = tb->FL[h]) == शून्य)
		वापस 0;

	अगर (f == l)
		order = PATH_H_B_ITEM_ORDER(tb->tb_path, h) - 1;
	अन्यथा अणु
		order = B_NR_ITEMS(l);
		f = l;
	पूर्ण

	वापस (MAX_CHILD_SIZE(f) - dc_size(B_N_CHILD(f, order)));
पूर्ण

/*
 * Get मुक्त space of the right neighbor,
 * which is stored in the parent node of the right neighbor.
 */
अटल पूर्णांक get_rमुक्त(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा buffer_head *r, *f;
	पूर्णांक order;

	अगर ((f = PATH_H_PPARENT(tb->tb_path, h)) == शून्य ||
	    (r = tb->FR[h]) == शून्य)
		वापस 0;

	अगर (f == r)
		order = PATH_H_B_ITEM_ORDER(tb->tb_path, h) + 1;
	अन्यथा अणु
		order = 0;
		f = r;
	पूर्ण

	वापस (MAX_CHILD_SIZE(f) - dc_size(B_N_CHILD(f, order)));

पूर्ण

/* Check whether left neighbor is in memory. */
अटल पूर्णांक is_left_neighbor_in_cache(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा buffer_head *father, *left;
	काष्ठा super_block *sb = tb->tb_sb;
	b_blocknr_t left_neighbor_blocknr;
	पूर्णांक left_neighbor_position;

	/* Father of the left neighbor करोes not exist. */
	अगर (!tb->FL[h])
		वापस 0;

	/* Calculate father of the node to be balanced. */
	father = PATH_H_PBUFFER(tb->tb_path, h + 1);

	RFALSE(!father ||
	       !B_IS_IN_TREE(father) ||
	       !B_IS_IN_TREE(tb->FL[h]) ||
	       !buffer_uptodate(father) ||
	       !buffer_uptodate(tb->FL[h]),
	       "vs-8165: F[h] (%b) or FL[h] (%b) is invalid",
	       father, tb->FL[h]);

	/*
	 * Get position of the poपूर्णांकer to the left neighbor
	 * पूर्णांकo the left father.
	 */
	left_neighbor_position = (father == tb->FL[h]) ?
	    tb->lkey[h] : B_NR_ITEMS(tb->FL[h]);
	/* Get left neighbor block number. */
	left_neighbor_blocknr =
	    B_N_CHILD_NUM(tb->FL[h], left_neighbor_position);
	/* Look क्रम the left neighbor in the cache. */
	अगर ((left = sb_find_get_block(sb, left_neighbor_blocknr))) अणु

		RFALSE(buffer_uptodate(left) && !B_IS_IN_TREE(left),
		       "vs-8170: left neighbor (%b %z) is not in the tree",
		       left, left);
		put_bh(left);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा LEFT_PARENTS  'l'
#घोषणा RIGHT_PARENTS 'r'

अटल व्योम decrement_key(काष्ठा cpu_key *key)
अणु
	/* call item specअगरic function क्रम this key */
	item_ops[cpu_key_k_type(key)]->decrement_key(key);
पूर्ण

/*
 * Calculate far left/right parent of the left/right neighbor of the
 * current node, that is calculate the left/right (FL[h]/FR[h]) neighbor
 * of the parent F[h].
 * Calculate left/right common parent of the current node and L[h]/R[h].
 * Calculate left/right delimiting key position.
 * Returns:	PATH_INCORRECT    - path in the tree is not correct
 *		SCHEDULE_OCCURRED - schedule occurred जबतक the function worked
 *	        CARRY_ON          - schedule didn't occur जबतक the function
 *				    worked
 */
अटल पूर्णांक get_far_parent(काष्ठा tree_balance *tb,
			  पूर्णांक h,
			  काष्ठा buffer_head **pfather,
			  काष्ठा buffer_head **pcom_father, अक्षर c_lr_par)
अणु
	काष्ठा buffer_head *parent;
	INITIALIZE_PATH(s_path_to_neighbor_father);
	काष्ठा treepath *path = tb->tb_path;
	काष्ठा cpu_key s_lr_father_key;
	पूर्णांक counter,
	    position = पूर्णांक_उच्च,
	    first_last_position = 0,
	    path_offset = PATH_H_PATH_OFFSET(path, h);

	/*
	 * Starting from F[h] go upwards in the tree, and look क्रम the common
	 * ancestor of F[h], and its neighbor l/r, that should be obtained.
	 */

	counter = path_offset;

	RFALSE(counter < FIRST_PATH_ELEMENT_OFFSET,
	       "PAP-8180: invalid path length");

	क्रम (; counter > FIRST_PATH_ELEMENT_OFFSET; counter--) अणु
		/*
		 * Check whether parent of the current buffer in the path
		 * is really parent in the tree.
		 */
		अगर (!B_IS_IN_TREE
		    (parent = PATH_OFFSET_PBUFFER(path, counter - 1)))
			वापस REPEAT_SEARCH;

		/* Check whether position in the parent is correct. */
		अगर ((position =
		     PATH_OFFSET_POSITION(path,
					  counter - 1)) >
		    B_NR_ITEMS(parent))
			वापस REPEAT_SEARCH;

		/*
		 * Check whether parent at the path really poपूर्णांकs
		 * to the child.
		 */
		अगर (B_N_CHILD_NUM(parent, position) !=
		    PATH_OFFSET_PBUFFER(path, counter)->b_blocknr)
			वापस REPEAT_SEARCH;

		/*
		 * Return delimiting key अगर position in the parent is not
		 * equal to first/last one.
		 */
		अगर (c_lr_par == RIGHT_PARENTS)
			first_last_position = B_NR_ITEMS(parent);
		अगर (position != first_last_position) अणु
			*pcom_father = parent;
			get_bh(*pcom_father);
			/*(*pcom_father = parent)->b_count++; */
			अवरोध;
		पूर्ण
	पूर्ण

	/* अगर we are in the root of the tree, then there is no common father */
	अगर (counter == FIRST_PATH_ELEMENT_OFFSET) अणु
		/*
		 * Check whether first buffer in the path is the
		 * root of the tree.
		 */
		अगर (PATH_OFFSET_PBUFFER
		    (tb->tb_path,
		     FIRST_PATH_ELEMENT_OFFSET)->b_blocknr ==
		    SB_ROOT_BLOCK(tb->tb_sb)) अणु
			*pfather = *pcom_father = शून्य;
			वापस CARRY_ON;
		पूर्ण
		वापस REPEAT_SEARCH;
	पूर्ण

	RFALSE(B_LEVEL(*pcom_father) <= DISK_LEAF_NODE_LEVEL,
	       "PAP-8185: (%b %z) level too small",
	       *pcom_father, *pcom_father);

	/* Check whether the common parent is locked. */

	अगर (buffer_locked(*pcom_father)) अणु

		/* Release the ग_लिखो lock जबतक the buffer is busy */
		पूर्णांक depth = reiserfs_ग_लिखो_unlock_nested(tb->tb_sb);
		__रुको_on_buffer(*pcom_father);
		reiserfs_ग_लिखो_lock_nested(tb->tb_sb, depth);
		अगर (खाताSYSTEM_CHANGED_TB(tb)) अणु
			brअन्यथा(*pcom_father);
			वापस REPEAT_SEARCH;
		पूर्ण
	पूर्ण

	/*
	 * So, we got common parent of the current node and its
	 * left/right neighbor.  Now we are getting the parent of the
	 * left/right neighbor.
	 */

	/* Form key to get parent of the left/right neighbor. */
	le_key2cpu_key(&s_lr_father_key,
		       पूर्णांकernal_key(*pcom_father,
				      (c_lr_par ==
				       LEFT_PARENTS) ? (tb->lkey[h - 1] =
							position -
							1) : (tb->rkey[h -
									   1] =
							      position)));

	अगर (c_lr_par == LEFT_PARENTS)
		decrement_key(&s_lr_father_key);

	अगर (search_by_key
	    (tb->tb_sb, &s_lr_father_key, &s_path_to_neighbor_father,
	     h + 1) == IO_ERROR)
		/* path is released */
		वापस IO_ERROR;

	अगर (खाताSYSTEM_CHANGED_TB(tb)) अणु
		pathrअन्यथा(&s_path_to_neighbor_father);
		brअन्यथा(*pcom_father);
		वापस REPEAT_SEARCH;
	पूर्ण

	*pfather = PATH_PLAST_BUFFER(&s_path_to_neighbor_father);

	RFALSE(B_LEVEL(*pfather) != h + 1,
	       "PAP-8190: (%b %z) level too small", *pfather, *pfather);
	RFALSE(s_path_to_neighbor_father.path_length <
	       FIRST_PATH_ELEMENT_OFFSET, "PAP-8192: path length is too small");

	s_path_to_neighbor_father.path_length--;
	pathrअन्यथा(&s_path_to_neighbor_father);
	वापस CARRY_ON;
पूर्ण

/*
 * Get parents of neighbors of node in the path(S[path_offset]) and
 * common parents of S[path_offset] and L[path_offset]/R[path_offset]:
 * F[path_offset], FL[path_offset], FR[path_offset], CFL[path_offset],
 * CFR[path_offset].
 * Calculate numbers of left and right delimiting keys position:
 * lkey[path_offset], rkey[path_offset].
 * Returns:	SCHEDULE_OCCURRED - schedule occurred जबतक the function worked
 *	        CARRY_ON - schedule didn't occur जबतक the function worked
 */
अटल पूर्णांक get_parents(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा treepath *path = tb->tb_path;
	पूर्णांक position,
	    ret,
	    path_offset = PATH_H_PATH_OFFSET(tb->tb_path, h);
	काष्ठा buffer_head *curf, *curcf;

	/* Current node is the root of the tree or will be root of the tree */
	अगर (path_offset <= FIRST_PATH_ELEMENT_OFFSET) अणु
		/*
		 * The root can not have parents.
		 * Release nodes which previously were obtained as
		 * parents of the current node neighbors.
		 */
		brअन्यथा(tb->FL[h]);
		brअन्यथा(tb->CFL[h]);
		brअन्यथा(tb->FR[h]);
		brअन्यथा(tb->CFR[h]);
		tb->FL[h]  = शून्य;
		tb->CFL[h] = शून्य;
		tb->FR[h]  = शून्य;
		tb->CFR[h] = शून्य;
		वापस CARRY_ON;
	पूर्ण

	/* Get parent FL[path_offset] of L[path_offset]. */
	position = PATH_OFFSET_POSITION(path, path_offset - 1);
	अगर (position) अणु
		/* Current node is not the first child of its parent. */
		curf = PATH_OFFSET_PBUFFER(path, path_offset - 1);
		curcf = PATH_OFFSET_PBUFFER(path, path_offset - 1);
		get_bh(curf);
		get_bh(curf);
		tb->lkey[h] = position - 1;
	पूर्ण अन्यथा अणु
		/*
		 * Calculate current parent of L[path_offset], which is the
		 * left neighbor of the current node.  Calculate current
		 * common parent of L[path_offset] and the current node.
		 * Note that CFL[path_offset] not equal FL[path_offset] and
		 * CFL[path_offset] not equal F[path_offset].
		 * Calculate lkey[path_offset].
		 */
		अगर ((ret = get_far_parent(tb, h + 1, &curf,
						  &curcf,
						  LEFT_PARENTS)) != CARRY_ON)
			वापस ret;
	पूर्ण

	brअन्यथा(tb->FL[h]);
	tb->FL[h] = curf;	/* New initialization of FL[h]. */
	brअन्यथा(tb->CFL[h]);
	tb->CFL[h] = curcf;	/* New initialization of CFL[h]. */

	RFALSE((curf && !B_IS_IN_TREE(curf)) ||
	       (curcf && !B_IS_IN_TREE(curcf)),
	       "PAP-8195: FL (%b) or CFL (%b) is invalid", curf, curcf);

	/* Get parent FR[h] of R[h]. */

	/* Current node is the last child of F[h]. FR[h] != F[h]. */
	अगर (position == B_NR_ITEMS(PATH_H_PBUFFER(path, h + 1))) अणु
		/*
		 * Calculate current parent of R[h], which is the right
		 * neighbor of F[h].  Calculate current common parent of
		 * R[h] and current node. Note that CFR[h] not equal
		 * FR[path_offset] and CFR[h] not equal F[h].
		 */
		अगर ((ret =
		     get_far_parent(tb, h + 1, &curf, &curcf,
				    RIGHT_PARENTS)) != CARRY_ON)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Current node is not the last child of its parent F[h]. */
		curf = PATH_OFFSET_PBUFFER(path, path_offset - 1);
		curcf = PATH_OFFSET_PBUFFER(path, path_offset - 1);
		get_bh(curf);
		get_bh(curf);
		tb->rkey[h] = position;
	पूर्ण

	brअन्यथा(tb->FR[h]);
	/* New initialization of FR[path_offset]. */
	tb->FR[h] = curf;

	brअन्यथा(tb->CFR[h]);
	/* New initialization of CFR[path_offset]. */
	tb->CFR[h] = curcf;

	RFALSE((curf && !B_IS_IN_TREE(curf)) ||
	       (curcf && !B_IS_IN_TREE(curcf)),
	       "PAP-8205: FR (%b) or CFR (%b) is invalid", curf, curcf);

	वापस CARRY_ON;
पूर्ण

/*
 * it is possible to हटाओ node as result of shअगरtings to
 * neighbors even when we insert or paste item.
 */
अटल अंतरभूत पूर्णांक can_node_be_हटाओd(पूर्णांक mode, पूर्णांक lमुक्त, पूर्णांक sमुक्त, पूर्णांक rमुक्त,
				      काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा buffer_head *Sh = PATH_H_PBUFFER(tb->tb_path, h);
	पूर्णांक levbytes = tb->insert_size[h];
	काष्ठा item_head *ih;
	काष्ठा reiserfs_key *r_key = शून्य;

	ih = item_head(Sh, 0);
	अगर (tb->CFR[h])
		r_key = पूर्णांकernal_key(tb->CFR[h], tb->rkey[h]);

	अगर (lमुक्त + rमुक्त + sमुक्त < MAX_CHILD_SIZE(Sh) + levbytes
	    /* shअगरting may merge items which might save space */
	    -
	    ((!h
	      && op_is_left_mergeable(&ih->ih_key, Sh->b_size)) ? IH_SIZE : 0)
	    -
	    ((!h && r_key
	      && op_is_left_mergeable(r_key, Sh->b_size)) ? IH_SIZE : 0)
	    + ((h) ? KEY_SIZE : 0)) अणु
		/* node can not be हटाओd */
		अगर (sमुक्त >= levbytes) अणु
			/* new item fits पूर्णांकo node S[h] without any shअगरting */
			अगर (!h)
				tb->s0num =
				    B_NR_ITEMS(Sh) +
				    ((mode == M_INSERT) ? 1 : 0);
			set_parameters(tb, h, 0, 0, 1, शून्य, -1, -1);
			वापस NO_BALANCING_NEEDED;
		पूर्ण
	पूर्ण
	PROC_INFO_INC(tb->tb_sb, can_node_be_हटाओd[h]);
	वापस !NO_BALANCING_NEEDED;
पूर्ण

/*
 * Check whether current node S[h] is balanced when increasing its size by
 * Inserting or Pasting.
 * Calculate parameters क्रम balancing क्रम current level h.
 * Parameters:
 *	tb	tree_balance काष्ठाure;
 *	h	current level of the node;
 *	inum	item number in S[h];
 *	mode	i - insert, p - paste;
 * Returns:	1 - schedule occurred;
 *	        0 - balancing क्रम higher levels needed;
 *	       -1 - no balancing क्रम higher levels needed;
 *	       -2 - no disk space.
 */
/* ip means Inserting or Pasting */
अटल पूर्णांक ip_check_balance(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा भव_node *vn = tb->tb_vn;
	/*
	 * Number of bytes that must be inserted पूर्णांकo (value is negative
	 * अगर bytes are deleted) buffer which contains node being balanced.
	 * The mnemonic is that the attempted change in node space used
	 * level is levbytes bytes.
	 */
	पूर्णांक levbytes;
	पूर्णांक ret;

	पूर्णांक lमुक्त, sमुक्त, rमुक्त /* मुक्त space in L, S and R */ ;

	/*
	 * nver is लघु क्रम number of vertixes, and lnver is the number अगर
	 * we shअगरt to the left, rnver is the number अगर we shअगरt to the
	 * right, and lrnver is the number अगर we shअगरt in both directions.
	 * The goal is to minimize first the number of vertixes, and second,
	 * the number of vertixes whose contents are changed by shअगरting,
	 * and third the number of uncached vertixes whose contents are
	 * changed by shअगरting and must be पढ़ो from disk.
	 */
	पूर्णांक nver, lnver, rnver, lrnver;

	/*
	 * used at leaf level only, S0 = S[0] is the node being balanced,
	 * sInum [ I = 0,1,2 ] is the number of items that will
	 * reमुख्य in node SI after balancing.  S1 and S2 are new
	 * nodes that might be created.
	 */

	/*
	 * we perक्रमm 8 calls to get_num_ver().  For each call we
	 * calculate five parameters.  where 4th parameter is s1bytes
	 * and 5th - s2bytes
	 *
	 * s0num, s1num, s2num क्रम 8 हालs
	 * 0,1 - करो not shअगरt and करो not shअगरt but bottle
	 * 2   - shअगरt only whole item to left
	 * 3   - shअगरt to left and bottle as much as possible
	 * 4,5 - shअगरt to right (whole items and as much as possible
	 * 6,7 - shअगरt to both directions (whole items and as much as possible)
	 */
	लघु snum012[40] = अणु 0, पूर्ण;

	/* Sh is the node whose balance is currently being checked */
	काष्ठा buffer_head *Sh;

	Sh = PATH_H_PBUFFER(tb->tb_path, h);
	levbytes = tb->insert_size[h];

	/* Calculate balance parameters क्रम creating new root. */
	अगर (!Sh) अणु
		अगर (!h)
			reiserfs_panic(tb->tb_sb, "vs-8210",
				       "S[0] can not be 0");
		चयन (ret = get_empty_nodes(tb, h)) अणु
		/* no balancing क्रम higher levels needed */
		हाल CARRY_ON:
			set_parameters(tb, h, 0, 0, 1, शून्य, -1, -1);
			वापस NO_BALANCING_NEEDED;

		हाल NO_DISK_SPACE:
		हाल REPEAT_SEARCH:
			वापस ret;
		शेष:
			reiserfs_panic(tb->tb_sb, "vs-8215", "incorrect "
				       "return value of get_empty_nodes");
		पूर्ण
	पूर्ण

	/* get parents of S[h] neighbors. */
	ret = get_parents(tb, h);
	अगर (ret != CARRY_ON)
		वापस ret;

	sमुक्त = B_FREE_SPACE(Sh);

	/* get मुक्त space of neighbors */
	rमुक्त = get_rमुक्त(tb, h);
	lमुक्त = get_lमुक्त(tb, h);

	/* and new item fits पूर्णांकo node S[h] without any shअगरting */
	अगर (can_node_be_हटाओd(vn->vn_mode, lमुक्त, sमुक्त, rमुक्त, tb, h) ==
	    NO_BALANCING_NEEDED)
		वापस NO_BALANCING_NEEDED;

	create_भव_node(tb, h);

	/*
	 * determine maximal number of items we can shअगरt to the left
	 * neighbor (in tb काष्ठाure) and the maximal number of bytes
	 * that can flow to the left neighbor from the left most liquid
	 * item that cannot be shअगरted from S[0] entirely (वापसed value)
	 */
	check_left(tb, h, lमुक्त);

	/*
	 * determine maximal number of items we can shअगरt to the right
	 * neighbor (in tb काष्ठाure) and the maximal number of bytes
	 * that can flow to the right neighbor from the right most liquid
	 * item that cannot be shअगरted from S[0] entirely (वापसed value)
	 */
	check_right(tb, h, rमुक्त);

	/*
	 * all contents of पूर्णांकernal node S[h] can be moved पूर्णांकo its
	 * neighbors, S[h] will be हटाओd after balancing
	 */
	अगर (h && (tb->rnum[h] + tb->lnum[h] >= vn->vn_nr_item + 1)) अणु
		पूर्णांक to_r;

		/*
		 * Since we are working on पूर्णांकernal nodes, and our पूर्णांकernal
		 * nodes have fixed size entries, then we can balance by the
		 * number of items rather than the space they consume.  In this
		 * routine we set the left node equal to the right node,
		 * allowing a dअगरference of less than or equal to 1 child
		 * poपूर्णांकer.
		 */
		to_r =
		    ((MAX_NR_KEY(Sh) << 1) + 2 - tb->lnum[h] - tb->rnum[h] +
		     vn->vn_nr_item + 1) / 2 - (MAX_NR_KEY(Sh) + 1 -
						tb->rnum[h]);
		set_parameters(tb, h, vn->vn_nr_item + 1 - to_r, to_r, 0, शून्य,
			       -1, -1);
		वापस CARRY_ON;
	पूर्ण

	/*
	 * this checks balance condition, that any two neighboring nodes
	 * can not fit in one node
	 */
	RFALSE(h &&
	       (tb->lnum[h] >= vn->vn_nr_item + 1 ||
		tb->rnum[h] >= vn->vn_nr_item + 1),
	       "vs-8220: tree is not balanced on internal level");
	RFALSE(!h && ((tb->lnum[h] >= vn->vn_nr_item && (tb->lbytes == -1)) ||
		      (tb->rnum[h] >= vn->vn_nr_item && (tb->rbytes == -1))),
	       "vs-8225: tree is not balanced on leaf level");

	/*
	 * all contents of S[0] can be moved पूर्णांकo its neighbors
	 * S[0] will be हटाओd after balancing.
	 */
	अगर (!h && is_leaf_removable(tb))
		वापस CARRY_ON;

	/*
	 * why करो we perक्रमm this check here rather than earlier??
	 * Answer: we can win 1 node in some हालs above. Moreover we
	 * checked it above, when we checked, that S[0] is not removable
	 * in principle
	 */

	 /* new item fits पूर्णांकo node S[h] without any shअगरting */
	अगर (sमुक्त >= levbytes) अणु
		अगर (!h)
			tb->s0num = vn->vn_nr_item;
		set_parameters(tb, h, 0, 0, 1, शून्य, -1, -1);
		वापस NO_BALANCING_NEEDED;
	पूर्ण

	अणु
		पूर्णांक lpar, rpar, nset, lset, rset, lrset;
		/* regular overflowing of the node */

		/*
		 * get_num_ver works in 2 modes (FLOW & NO_FLOW)
		 * lpar, rpar - number of items we can shअगरt to left/right
		 *              neighbor (including splitting item)
		 * nset, lset, rset, lrset - shows, whether flowing items
		 *                           give better packing
		 */
#घोषणा FLOW 1
#घोषणा NO_FLOW 0		/* करो not any splitting */

		/* we choose one of the following */
#घोषणा NOTHING_SHIFT_NO_FLOW	0
#घोषणा NOTHING_SHIFT_FLOW	5
#घोषणा LEFT_SHIFT_NO_FLOW	10
#घोषणा LEFT_SHIFT_FLOW		15
#घोषणा RIGHT_SHIFT_NO_FLOW	20
#घोषणा RIGHT_SHIFT_FLOW	25
#घोषणा LR_SHIFT_NO_FLOW	30
#घोषणा LR_SHIFT_FLOW		35

		lpar = tb->lnum[h];
		rpar = tb->rnum[h];

		/*
		 * calculate number of blocks S[h] must be split पूर्णांकo when
		 * nothing is shअगरted to the neighbors, as well as number of
		 * items in each part of the split node (s012 numbers),
		 * and number of bytes (s1bytes) of the shared drop which
		 * flow to S1 अगर any
		 */
		nset = NOTHING_SHIFT_NO_FLOW;
		nver = get_num_ver(vn->vn_mode, tb, h,
				   0, -1, h ? vn->vn_nr_item : 0, -1,
				   snum012, NO_FLOW);

		अगर (!h) अणु
			पूर्णांक nver1;

			/*
			 * note, that in this हाल we try to bottle
			 * between S[0] and S1 (S1 - the first new node)
			 */
			nver1 = get_num_ver(vn->vn_mode, tb, h,
					    0, -1, 0, -1,
					    snum012 + NOTHING_SHIFT_FLOW, FLOW);
			अगर (nver > nver1)
				nset = NOTHING_SHIFT_FLOW, nver = nver1;
		पूर्ण

		/*
		 * calculate number of blocks S[h] must be split पूर्णांकo when
		 * l_shअगरt_num first items and l_shअगरt_bytes of the right
		 * most liquid item to be shअगरted are shअगरted to the left
		 * neighbor, as well as number of items in each part of the
		 * splitted node (s012 numbers), and number of bytes
		 * (s1bytes) of the shared drop which flow to S1 अगर any
		 */
		lset = LEFT_SHIFT_NO_FLOW;
		lnver = get_num_ver(vn->vn_mode, tb, h,
				    lpar - ((h || tb->lbytes == -1) ? 0 : 1),
				    -1, h ? vn->vn_nr_item : 0, -1,
				    snum012 + LEFT_SHIFT_NO_FLOW, NO_FLOW);
		अगर (!h) अणु
			पूर्णांक lnver1;

			lnver1 = get_num_ver(vn->vn_mode, tb, h,
					     lpar -
					     ((tb->lbytes != -1) ? 1 : 0),
					     tb->lbytes, 0, -1,
					     snum012 + LEFT_SHIFT_FLOW, FLOW);
			अगर (lnver > lnver1)
				lset = LEFT_SHIFT_FLOW, lnver = lnver1;
		पूर्ण

		/*
		 * calculate number of blocks S[h] must be split पूर्णांकo when
		 * r_shअगरt_num first items and r_shअगरt_bytes of the left most
		 * liquid item to be shअगरted are shअगरted to the right neighbor,
		 * as well as number of items in each part of the splitted
		 * node (s012 numbers), and number of bytes (s1bytes) of the
		 * shared drop which flow to S1 अगर any
		 */
		rset = RIGHT_SHIFT_NO_FLOW;
		rnver = get_num_ver(vn->vn_mode, tb, h,
				    0, -1,
				    h ? (vn->vn_nr_item - rpar) : (rpar -
								   ((tb->
								     rbytes !=
								     -1) ? 1 :
								    0)), -1,
				    snum012 + RIGHT_SHIFT_NO_FLOW, NO_FLOW);
		अगर (!h) अणु
			पूर्णांक rnver1;

			rnver1 = get_num_ver(vn->vn_mode, tb, h,
					     0, -1,
					     (rpar -
					      ((tb->rbytes != -1) ? 1 : 0)),
					     tb->rbytes,
					     snum012 + RIGHT_SHIFT_FLOW, FLOW);

			अगर (rnver > rnver1)
				rset = RIGHT_SHIFT_FLOW, rnver = rnver1;
		पूर्ण

		/*
		 * calculate number of blocks S[h] must be split पूर्णांकo when
		 * items are shअगरted in both directions, as well as number
		 * of items in each part of the splitted node (s012 numbers),
		 * and number of bytes (s1bytes) of the shared drop which
		 * flow to S1 अगर any
		 */
		lrset = LR_SHIFT_NO_FLOW;
		lrnver = get_num_ver(vn->vn_mode, tb, h,
				     lpar - ((h || tb->lbytes == -1) ? 0 : 1),
				     -1,
				     h ? (vn->vn_nr_item - rpar) : (rpar -
								    ((tb->
								      rbytes !=
								      -1) ? 1 :
								     0)), -1,
				     snum012 + LR_SHIFT_NO_FLOW, NO_FLOW);
		अगर (!h) अणु
			पूर्णांक lrnver1;

			lrnver1 = get_num_ver(vn->vn_mode, tb, h,
					      lpar -
					      ((tb->lbytes != -1) ? 1 : 0),
					      tb->lbytes,
					      (rpar -
					       ((tb->rbytes != -1) ? 1 : 0)),
					      tb->rbytes,
					      snum012 + LR_SHIFT_FLOW, FLOW);
			अगर (lrnver > lrnver1)
				lrset = LR_SHIFT_FLOW, lrnver = lrnver1;
		पूर्ण

		/*
		 * Our general shअगरting strategy is:
		 * 1) to minimized number of new nodes;
		 * 2) to minimized number of neighbors involved in shअगरting;
		 * 3) to minimized number of disk पढ़ोs;
		 */

		/* we can win TWO or ONE nodes by shअगरting in both directions */
		अगर (lrnver < lnver && lrnver < rnver) अणु
			RFALSE(h &&
			       (tb->lnum[h] != 1 ||
				tb->rnum[h] != 1 ||
				lrnver != 1 || rnver != 2 || lnver != 2
				|| h != 1), "vs-8230: bad h");
			अगर (lrset == LR_SHIFT_FLOW)
				set_parameters(tb, h, tb->lnum[h], tb->rnum[h],
					       lrnver, snum012 + lrset,
					       tb->lbytes, tb->rbytes);
			अन्यथा
				set_parameters(tb, h,
					       tb->lnum[h] -
					       ((tb->lbytes == -1) ? 0 : 1),
					       tb->rnum[h] -
					       ((tb->rbytes == -1) ? 0 : 1),
					       lrnver, snum012 + lrset, -1, -1);

			वापस CARRY_ON;
		पूर्ण

		/*
		 * अगर shअगरting करोesn't lead to better packing
		 * then करोn't shअगरt
		 */
		अगर (nver == lrnver) अणु
			set_parameters(tb, h, 0, 0, nver, snum012 + nset, -1,
				       -1);
			वापस CARRY_ON;
		पूर्ण

		/*
		 * now we know that क्रम better packing shअगरting in only one
		 * direction either to the left or to the right is required
		 */

		/*
		 * अगर shअगरting to the left is better than
		 * shअगरting to the right
		 */
		अगर (lnver < rnver) अणु
			SET_PAR_SHIFT_LEFT;
			वापस CARRY_ON;
		पूर्ण

		/*
		 * अगर shअगरting to the right is better than
		 * shअगरting to the left
		 */
		अगर (lnver > rnver) अणु
			SET_PAR_SHIFT_RIGHT;
			वापस CARRY_ON;
		पूर्ण

		/*
		 * now shअगरting in either direction gives the same number
		 * of nodes and we can make use of the cached neighbors
		 */
		अगर (is_left_neighbor_in_cache(tb, h)) अणु
			SET_PAR_SHIFT_LEFT;
			वापस CARRY_ON;
		पूर्ण

		/*
		 * shअगरt to the right independently on whether the
		 * right neighbor in cache or not
		 */
		SET_PAR_SHIFT_RIGHT;
		वापस CARRY_ON;
	पूर्ण
पूर्ण

/*
 * Check whether current node S[h] is balanced when Decreasing its size by
 * Deleting or Cutting क्रम INTERNAL node of S+tree.
 * Calculate parameters क्रम balancing क्रम current level h.
 * Parameters:
 *	tb	tree_balance काष्ठाure;
 *	h	current level of the node;
 *	inum	item number in S[h];
 *	mode	i - insert, p - paste;
 * Returns:	1 - schedule occurred;
 *	        0 - balancing क्रम higher levels needed;
 *	       -1 - no balancing क्रम higher levels needed;
 *	       -2 - no disk space.
 *
 * Note: Items of पूर्णांकernal nodes have fixed size, so the balance condition क्रम
 * the पूर्णांकernal part of S+tree is as क्रम the B-trees.
 */
अटल पूर्णांक dc_check_balance_पूर्णांकernal(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा भव_node *vn = tb->tb_vn;

	/*
	 * Sh is the node whose balance is currently being checked,
	 * and Fh is its father.
	 */
	काष्ठा buffer_head *Sh, *Fh;
	पूर्णांक ret;
	पूर्णांक lमुक्त, rमुक्त /* मुक्त space in L and R */ ;

	Sh = PATH_H_PBUFFER(tb->tb_path, h);
	Fh = PATH_H_PPARENT(tb->tb_path, h);

	/*
	 * using tb->insert_size[h], which is negative in this हाल,
	 * create_भव_node calculates:
	 * new_nr_item = number of items node would have अगर operation is
	 * perक्रमmed without balancing (new_nr_item);
	 */
	create_भव_node(tb, h);

	अगर (!Fh) अणु		/* S[h] is the root. */
		/* no balancing क्रम higher levels needed */
		अगर (vn->vn_nr_item > 0) अणु
			set_parameters(tb, h, 0, 0, 1, शून्य, -1, -1);
			वापस NO_BALANCING_NEEDED;
		पूर्ण
		/*
		 * new_nr_item == 0.
		 * Current root will be deleted resulting in
		 * decrementing the tree height.
		 */
		set_parameters(tb, h, 0, 0, 0, शून्य, -1, -1);
		वापस CARRY_ON;
	पूर्ण

	अगर ((ret = get_parents(tb, h)) != CARRY_ON)
		वापस ret;

	/* get मुक्त space of neighbors */
	rमुक्त = get_rमुक्त(tb, h);
	lमुक्त = get_lमुक्त(tb, h);

	/* determine maximal number of items we can fit पूर्णांकo neighbors */
	check_left(tb, h, lमुक्त);
	check_right(tb, h, rमुक्त);

	/*
	 * Balance condition क्रम the पूर्णांकernal node is valid.
	 * In this हाल we balance only अगर it leads to better packing.
	 */
	अगर (vn->vn_nr_item >= MIN_NR_KEY(Sh)) अणु
		/*
		 * Here we join S[h] with one of its neighbors,
		 * which is impossible with greater values of new_nr_item.
		 */
		अगर (vn->vn_nr_item == MIN_NR_KEY(Sh)) अणु
			/* All contents of S[h] can be moved to L[h]. */
			अगर (tb->lnum[h] >= vn->vn_nr_item + 1) अणु
				पूर्णांक n;
				पूर्णांक order_L;

				order_L =
				    ((n =
				      PATH_H_B_ITEM_ORDER(tb->tb_path,
							  h)) ==
				     0) ? B_NR_ITEMS(tb->FL[h]) : n - 1;
				n = dc_size(B_N_CHILD(tb->FL[h], order_L)) /
				    (DC_SIZE + KEY_SIZE);
				set_parameters(tb, h, -n - 1, 0, 0, शून्य, -1,
					       -1);
				वापस CARRY_ON;
			पूर्ण

			/* All contents of S[h] can be moved to R[h]. */
			अगर (tb->rnum[h] >= vn->vn_nr_item + 1) अणु
				पूर्णांक n;
				पूर्णांक order_R;

				order_R =
				    ((n =
				      PATH_H_B_ITEM_ORDER(tb->tb_path,
							  h)) ==
				     B_NR_ITEMS(Fh)) ? 0 : n + 1;
				n = dc_size(B_N_CHILD(tb->FR[h], order_R)) /
				    (DC_SIZE + KEY_SIZE);
				set_parameters(tb, h, 0, -n - 1, 0, शून्य, -1,
					       -1);
				वापस CARRY_ON;
			पूर्ण
		पूर्ण

		/*
		 * All contents of S[h] can be moved to the neighbors
		 * (L[h] & R[h]).
		 */
		अगर (tb->rnum[h] + tb->lnum[h] >= vn->vn_nr_item + 1) अणु
			पूर्णांक to_r;

			to_r =
			    ((MAX_NR_KEY(Sh) << 1) + 2 - tb->lnum[h] -
			     tb->rnum[h] + vn->vn_nr_item + 1) / 2 -
			    (MAX_NR_KEY(Sh) + 1 - tb->rnum[h]);
			set_parameters(tb, h, vn->vn_nr_item + 1 - to_r, to_r,
				       0, शून्य, -1, -1);
			वापस CARRY_ON;
		पूर्ण

		/* Balancing करोes not lead to better packing. */
		set_parameters(tb, h, 0, 0, 1, शून्य, -1, -1);
		वापस NO_BALANCING_NEEDED;
	पूर्ण

	/*
	 * Current node contain insufficient number of items.
	 * Balancing is required.
	 */
	/* Check whether we can merge S[h] with left neighbor. */
	अगर (tb->lnum[h] >= vn->vn_nr_item + 1)
		अगर (is_left_neighbor_in_cache(tb, h)
		    || tb->rnum[h] < vn->vn_nr_item + 1 || !tb->FR[h]) अणु
			पूर्णांक n;
			पूर्णांक order_L;

			order_L =
			    ((n =
			      PATH_H_B_ITEM_ORDER(tb->tb_path,
						  h)) ==
			     0) ? B_NR_ITEMS(tb->FL[h]) : n - 1;
			n = dc_size(B_N_CHILD(tb->FL[h], order_L)) / (DC_SIZE +
								      KEY_SIZE);
			set_parameters(tb, h, -n - 1, 0, 0, शून्य, -1, -1);
			वापस CARRY_ON;
		पूर्ण

	/* Check whether we can merge S[h] with right neighbor. */
	अगर (tb->rnum[h] >= vn->vn_nr_item + 1) अणु
		पूर्णांक n;
		पूर्णांक order_R;

		order_R =
		    ((n =
		      PATH_H_B_ITEM_ORDER(tb->tb_path,
					  h)) == B_NR_ITEMS(Fh)) ? 0 : (n + 1);
		n = dc_size(B_N_CHILD(tb->FR[h], order_R)) / (DC_SIZE +
							      KEY_SIZE);
		set_parameters(tb, h, 0, -n - 1, 0, शून्य, -1, -1);
		वापस CARRY_ON;
	पूर्ण

	/* All contents of S[h] can be moved to the neighbors (L[h] & R[h]). */
	अगर (tb->rnum[h] + tb->lnum[h] >= vn->vn_nr_item + 1) अणु
		पूर्णांक to_r;

		to_r =
		    ((MAX_NR_KEY(Sh) << 1) + 2 - tb->lnum[h] - tb->rnum[h] +
		     vn->vn_nr_item + 1) / 2 - (MAX_NR_KEY(Sh) + 1 -
						tb->rnum[h]);
		set_parameters(tb, h, vn->vn_nr_item + 1 - to_r, to_r, 0, शून्य,
			       -1, -1);
		वापस CARRY_ON;
	पूर्ण

	/* For पूर्णांकernal nodes try to borrow item from a neighbor */
	RFALSE(!tb->FL[h] && !tb->FR[h], "vs-8235: trying to borrow for root");

	/* Borrow one or two items from caching neighbor */
	अगर (is_left_neighbor_in_cache(tb, h) || !tb->FR[h]) अणु
		पूर्णांक from_l;

		from_l =
		    (MAX_NR_KEY(Sh) + 1 - tb->lnum[h] + vn->vn_nr_item +
		     1) / 2 - (vn->vn_nr_item + 1);
		set_parameters(tb, h, -from_l, 0, 1, शून्य, -1, -1);
		वापस CARRY_ON;
	पूर्ण

	set_parameters(tb, h, 0,
		       -((MAX_NR_KEY(Sh) + 1 - tb->rnum[h] + vn->vn_nr_item +
			  1) / 2 - (vn->vn_nr_item + 1)), 1, शून्य, -1, -1);
	वापस CARRY_ON;
पूर्ण

/*
 * Check whether current node S[h] is balanced when Decreasing its size by
 * Deleting or Truncating क्रम LEAF node of S+tree.
 * Calculate parameters क्रम balancing क्रम current level h.
 * Parameters:
 *	tb	tree_balance काष्ठाure;
 *	h	current level of the node;
 *	inum	item number in S[h];
 *	mode	i - insert, p - paste;
 * Returns:	1 - schedule occurred;
 *	        0 - balancing क्रम higher levels needed;
 *	       -1 - no balancing क्रम higher levels needed;
 *	       -2 - no disk space.
 */
अटल पूर्णांक dc_check_balance_leaf(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा भव_node *vn = tb->tb_vn;

	/*
	 * Number of bytes that must be deleted from
	 * (value is negative अगर bytes are deleted) buffer which
	 * contains node being balanced.  The mnemonic is that the
	 * attempted change in node space used level is levbytes bytes.
	 */
	पूर्णांक levbytes;

	/* the maximal item size */
	पूर्णांक maxsize, ret;

	/*
	 * S0 is the node whose balance is currently being checked,
	 * and F0 is its father.
	 */
	काष्ठा buffer_head *S0, *F0;
	पूर्णांक lमुक्त, rमुक्त /* मुक्त space in L and R */ ;

	S0 = PATH_H_PBUFFER(tb->tb_path, 0);
	F0 = PATH_H_PPARENT(tb->tb_path, 0);

	levbytes = tb->insert_size[h];

	maxsize = MAX_CHILD_SIZE(S0);	/* maximal possible size of an item */

	अगर (!F0) अणु		/* S[0] is the root now. */

		RFALSE(-levbytes >= maxsize - B_FREE_SPACE(S0),
		       "vs-8240: attempt to create empty buffer tree");

		set_parameters(tb, h, 0, 0, 1, शून्य, -1, -1);
		वापस NO_BALANCING_NEEDED;
	पूर्ण

	अगर ((ret = get_parents(tb, h)) != CARRY_ON)
		वापस ret;

	/* get मुक्त space of neighbors */
	rमुक्त = get_rमुक्त(tb, h);
	lमुक्त = get_lमुक्त(tb, h);

	create_भव_node(tb, h);

	/* अगर 3 leaves can be merge to one, set parameters and वापस */
	अगर (are_leaves_removable(tb, lमुक्त, rमुक्त))
		वापस CARRY_ON;

	/*
	 * determine maximal number of items we can shअगरt to the left/right
	 * neighbor and the maximal number of bytes that can flow to the
	 * left/right neighbor from the left/right most liquid item that
	 * cannot be shअगरted from S[0] entirely
	 */
	check_left(tb, h, lमुक्त);
	check_right(tb, h, rमुक्त);

	/* check whether we can merge S with left neighbor. */
	अगर (tb->lnum[0] >= vn->vn_nr_item && tb->lbytes == -1)
		अगर (is_left_neighbor_in_cache(tb, h) || ((tb->rnum[0] - ((tb->rbytes == -1) ? 0 : 1)) < vn->vn_nr_item) ||	/* S can not be merged with R */
		    !tb->FR[h]) अणु

			RFALSE(!tb->FL[h],
			       "vs-8245: dc_check_balance_leaf: FL[h] must exist");

			/* set parameter to merge S[0] with its left neighbor */
			set_parameters(tb, h, -1, 0, 0, शून्य, -1, -1);
			वापस CARRY_ON;
		पूर्ण

	/* check whether we can merge S[0] with right neighbor. */
	अगर (tb->rnum[0] >= vn->vn_nr_item && tb->rbytes == -1) अणु
		set_parameters(tb, h, 0, -1, 0, शून्य, -1, -1);
		वापस CARRY_ON;
	पूर्ण

	/*
	 * All contents of S[0] can be moved to the neighbors (L[0] & R[0]).
	 * Set parameters and वापस
	 */
	अगर (is_leaf_removable(tb))
		वापस CARRY_ON;

	/* Balancing is not required. */
	tb->s0num = vn->vn_nr_item;
	set_parameters(tb, h, 0, 0, 1, शून्य, -1, -1);
	वापस NO_BALANCING_NEEDED;
पूर्ण

/*
 * Check whether current node S[h] is balanced when Decreasing its size by
 * Deleting or Cutting.
 * Calculate parameters क्रम balancing क्रम current level h.
 * Parameters:
 *	tb	tree_balance काष्ठाure;
 *	h	current level of the node;
 *	inum	item number in S[h];
 *	mode	d - delete, c - cut.
 * Returns:	1 - schedule occurred;
 *	        0 - balancing क्रम higher levels needed;
 *	       -1 - no balancing क्रम higher levels needed;
 *	       -2 - no disk space.
 */
अटल पूर्णांक dc_check_balance(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	RFALSE(!(PATH_H_PBUFFER(tb->tb_path, h)),
	       "vs-8250: S is not initialized");

	अगर (h)
		वापस dc_check_balance_पूर्णांकernal(tb, h);
	अन्यथा
		वापस dc_check_balance_leaf(tb, h);
पूर्ण

/*
 * Check whether current node S[h] is balanced.
 * Calculate parameters क्रम balancing क्रम current level h.
 * Parameters:
 *
 *	tb	tree_balance काष्ठाure:
 *
 *              tb is a large काष्ठाure that must be पढ़ो about in the header
 *		file at the same समय as this procedure अगर the पढ़ोer is
 *		to successfully understand this procedure
 *
 *	h	current level of the node;
 *	inum	item number in S[h];
 *	mode	i - insert, p - paste, d - delete, c - cut.
 * Returns:	1 - schedule occurred;
 *	        0 - balancing क्रम higher levels needed;
 *	       -1 - no balancing क्रम higher levels needed;
 *	       -2 - no disk space.
 */
अटल पूर्णांक check_balance(पूर्णांक mode,
			 काष्ठा tree_balance *tb,
			 पूर्णांक h,
			 पूर्णांक inum,
			 पूर्णांक pos_in_item,
			 काष्ठा item_head *ins_ih, स्थिर व्योम *data)
अणु
	काष्ठा भव_node *vn;

	vn = tb->tb_vn = (काष्ठा भव_node *)(tb->vn_buf);
	vn->vn_मुक्त_ptr = (अक्षर *)(tb->tb_vn + 1);
	vn->vn_mode = mode;
	vn->vn_affected_item_num = inum;
	vn->vn_pos_in_item = pos_in_item;
	vn->vn_ins_ih = ins_ih;
	vn->vn_data = data;

	RFALSE(mode == M_INSERT && !vn->vn_ins_ih,
	       "vs-8255: ins_ih can not be 0 in insert mode");

	/* Calculate balance parameters when size of node is increasing. */
	अगर (tb->insert_size[h] > 0)
		वापस ip_check_balance(tb, h);

	/* Calculate balance parameters when  size of node is decreasing. */
	वापस dc_check_balance(tb, h);
पूर्ण

/* Check whether parent at the path is the really parent of the current node.*/
अटल पूर्णांक get_direct_parent(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा treepath *path = tb->tb_path;
	पूर्णांक position,
	    path_offset = PATH_H_PATH_OFFSET(tb->tb_path, h);

	/* We are in the root or in the new root. */
	अगर (path_offset <= FIRST_PATH_ELEMENT_OFFSET) अणु

		RFALSE(path_offset < FIRST_PATH_ELEMENT_OFFSET - 1,
		       "PAP-8260: invalid offset in the path");

		अगर (PATH_OFFSET_PBUFFER(path, FIRST_PATH_ELEMENT_OFFSET)->
		    b_blocknr == SB_ROOT_BLOCK(tb->tb_sb)) अणु
			/* Root is not changed. */
			PATH_OFFSET_PBUFFER(path, path_offset - 1) = शून्य;
			PATH_OFFSET_POSITION(path, path_offset - 1) = 0;
			वापस CARRY_ON;
		पूर्ण
		/* Root is changed and we must recalculate the path. */
		वापस REPEAT_SEARCH;
	पूर्ण

	/* Parent in the path is not in the tree. */
	अगर (!B_IS_IN_TREE
	    (bh = PATH_OFFSET_PBUFFER(path, path_offset - 1)))
		वापस REPEAT_SEARCH;

	अगर ((position =
	     PATH_OFFSET_POSITION(path,
				  path_offset - 1)) > B_NR_ITEMS(bh))
		वापस REPEAT_SEARCH;

	/* Parent in the path is not parent of the current node in the tree. */
	अगर (B_N_CHILD_NUM(bh, position) !=
	    PATH_OFFSET_PBUFFER(path, path_offset)->b_blocknr)
		वापस REPEAT_SEARCH;

	अगर (buffer_locked(bh)) अणु
		पूर्णांक depth = reiserfs_ग_लिखो_unlock_nested(tb->tb_sb);
		__रुको_on_buffer(bh);
		reiserfs_ग_लिखो_lock_nested(tb->tb_sb, depth);
		अगर (खाताSYSTEM_CHANGED_TB(tb))
			वापस REPEAT_SEARCH;
	पूर्ण

	/*
	 * Parent in the path is unlocked and really parent
	 * of the current node.
	 */
	वापस CARRY_ON;
पूर्ण

/*
 * Using lnum[h] and rnum[h] we should determine what neighbors
 * of S[h] we
 * need in order to balance S[h], and get them अगर necessary.
 * Returns:	SCHEDULE_OCCURRED - schedule occurred जबतक the function worked;
 *	        CARRY_ON - schedule didn't occur जबतक the function worked;
 */
अटल पूर्णांक get_neighbors(काष्ठा tree_balance *tb, पूर्णांक h)
अणु
	पूर्णांक child_position,
	    path_offset = PATH_H_PATH_OFFSET(tb->tb_path, h + 1);
	अचिन्हित दीर्घ son_number;
	काष्ठा super_block *sb = tb->tb_sb;
	काष्ठा buffer_head *bh;
	पूर्णांक depth;

	PROC_INFO_INC(sb, get_neighbors[h]);

	अगर (tb->lnum[h]) अणु
		/* We need left neighbor to balance S[h]. */
		PROC_INFO_INC(sb, need_l_neighbor[h]);
		bh = PATH_OFFSET_PBUFFER(tb->tb_path, path_offset);

		RFALSE(bh == tb->FL[h] &&
		       !PATH_OFFSET_POSITION(tb->tb_path, path_offset),
		       "PAP-8270: invalid position in the parent");

		child_position =
		    (bh ==
		     tb->FL[h]) ? tb->lkey[h] : B_NR_ITEMS(tb->
								       FL[h]);
		son_number = B_N_CHILD_NUM(tb->FL[h], child_position);
		depth = reiserfs_ग_लिखो_unlock_nested(tb->tb_sb);
		bh = sb_bपढ़ो(sb, son_number);
		reiserfs_ग_लिखो_lock_nested(tb->tb_sb, depth);
		अगर (!bh)
			वापस IO_ERROR;
		अगर (खाताSYSTEM_CHANGED_TB(tb)) अणु
			brअन्यथा(bh);
			PROC_INFO_INC(sb, get_neighbors_restart[h]);
			वापस REPEAT_SEARCH;
		पूर्ण

		RFALSE(!B_IS_IN_TREE(tb->FL[h]) ||
		       child_position > B_NR_ITEMS(tb->FL[h]) ||
		       B_N_CHILD_NUM(tb->FL[h], child_position) !=
		       bh->b_blocknr, "PAP-8275: invalid parent");
		RFALSE(!B_IS_IN_TREE(bh), "PAP-8280: invalid child");
		RFALSE(!h &&
		       B_FREE_SPACE(bh) !=
		       MAX_CHILD_SIZE(bh) -
		       dc_size(B_N_CHILD(tb->FL[0], child_position)),
		       "PAP-8290: invalid child size of left neighbor");

		brअन्यथा(tb->L[h]);
		tb->L[h] = bh;
	पूर्ण

	/* We need right neighbor to balance S[path_offset]. */
	अगर (tb->rnum[h]) अणु
		PROC_INFO_INC(sb, need_r_neighbor[h]);
		bh = PATH_OFFSET_PBUFFER(tb->tb_path, path_offset);

		RFALSE(bh == tb->FR[h] &&
		       PATH_OFFSET_POSITION(tb->tb_path,
					    path_offset) >=
		       B_NR_ITEMS(bh),
		       "PAP-8295: invalid position in the parent");

		child_position =
		    (bh == tb->FR[h]) ? tb->rkey[h] + 1 : 0;
		son_number = B_N_CHILD_NUM(tb->FR[h], child_position);
		depth = reiserfs_ग_लिखो_unlock_nested(tb->tb_sb);
		bh = sb_bपढ़ो(sb, son_number);
		reiserfs_ग_लिखो_lock_nested(tb->tb_sb, depth);
		अगर (!bh)
			वापस IO_ERROR;
		अगर (खाताSYSTEM_CHANGED_TB(tb)) अणु
			brअन्यथा(bh);
			PROC_INFO_INC(sb, get_neighbors_restart[h]);
			वापस REPEAT_SEARCH;
		पूर्ण
		brअन्यथा(tb->R[h]);
		tb->R[h] = bh;

		RFALSE(!h
		       && B_FREE_SPACE(bh) !=
		       MAX_CHILD_SIZE(bh) -
		       dc_size(B_N_CHILD(tb->FR[0], child_position)),
		       "PAP-8300: invalid child size of right neighbor (%d != %d - %d)",
		       B_FREE_SPACE(bh), MAX_CHILD_SIZE(bh),
		       dc_size(B_N_CHILD(tb->FR[0], child_position)));

	पूर्ण
	वापस CARRY_ON;
पूर्ण

अटल पूर्णांक get_भव_node_size(काष्ठा super_block *sb, काष्ठा buffer_head *bh)
अणु
	पूर्णांक max_num_of_items;
	पूर्णांक max_num_of_entries;
	अचिन्हित दीर्घ blocksize = sb->s_blocksize;

#घोषणा MIN_NAME_LEN 1

	max_num_of_items = (blocksize - BLKH_SIZE) / (IH_SIZE + MIN_ITEM_LEN);
	max_num_of_entries = (blocksize - BLKH_SIZE - IH_SIZE) /
	    (DEH_SIZE + MIN_NAME_LEN);

	वापस माप(काष्ठा भव_node) +
	    max(max_num_of_items * माप(काष्ठा भव_item),
		माप(काष्ठा भव_item) + माप(काष्ठा direntry_uarea) +
		(max_num_of_entries - 1) * माप(__u16));
पूर्ण

/*
 * maybe we should fail balancing we are going to perक्रमm when kदो_स्मृति
 * fails several बार. But now it will loop until kदो_स्मृति माला_लो
 * required memory
 */
अटल पूर्णांक get_mem_क्रम_भव_node(काष्ठा tree_balance *tb)
अणु
	पूर्णांक check_fs = 0;
	पूर्णांक size;
	अक्षर *buf;

	size = get_भव_node_size(tb->tb_sb, PATH_PLAST_BUFFER(tb->tb_path));

	/* we have to allocate more memory क्रम भव node */
	अगर (size > tb->vn_buf_size) अणु
		अगर (tb->vn_buf) अणु
			/* मुक्त memory allocated beक्रमe */
			kमुक्त(tb->vn_buf);
			/* this is not needed अगर kमुक्त is atomic */
			check_fs = 1;
		पूर्ण

		/* भव node requires now more memory */
		tb->vn_buf_size = size;

		/* get memory क्रम भव item */
		buf = kदो_स्मृति(size, GFP_ATOMIC | __GFP_NOWARN);
		अगर (!buf) अणु
			/*
			 * getting memory with GFP_KERNEL priority may involve
			 * balancing now (due to indirect_to_direct conversion
			 * on dcache shrinking). So, release path and collected
			 * resources here
			 */
			मुक्त_buffers_in_tb(tb);
			buf = kदो_स्मृति(size, GFP_NOFS);
			अगर (!buf) अणु
				tb->vn_buf_size = 0;
			पूर्ण
			tb->vn_buf = buf;
			schedule();
			वापस REPEAT_SEARCH;
		पूर्ण

		tb->vn_buf = buf;
	पूर्ण

	अगर (check_fs && खाताSYSTEM_CHANGED_TB(tb))
		वापस REPEAT_SEARCH;

	वापस CARRY_ON;
पूर्ण

#अगर_घोषित CONFIG_REISERFS_CHECK
अटल व्योम tb_buffer_sanity_check(काष्ठा super_block *sb,
				   काष्ठा buffer_head *bh,
				   स्थिर अक्षर *descr, पूर्णांक level)
अणु
	अगर (bh) अणु
		अगर (atomic_पढ़ो(&(bh->b_count)) <= 0)

			reiserfs_panic(sb, "jmacd-1", "negative or zero "
				       "reference counter for buffer %s[%d] "
				       "(%b)", descr, level, bh);

		अगर (!buffer_uptodate(bh))
			reiserfs_panic(sb, "jmacd-2", "buffer is not up "
				       "to date %s[%d] (%b)",
				       descr, level, bh);

		अगर (!B_IS_IN_TREE(bh))
			reiserfs_panic(sb, "jmacd-3", "buffer is not "
				       "in tree %s[%d] (%b)",
				       descr, level, bh);

		अगर (bh->b_bdev != sb->s_bdev)
			reiserfs_panic(sb, "jmacd-4", "buffer has wrong "
				       "device %s[%d] (%b)",
				       descr, level, bh);

		अगर (bh->b_size != sb->s_blocksize)
			reiserfs_panic(sb, "jmacd-5", "buffer has wrong "
				       "blocksize %s[%d] (%b)",
				       descr, level, bh);

		अगर (bh->b_blocknr > SB_BLOCK_COUNT(sb))
			reiserfs_panic(sb, "jmacd-6", "buffer block "
				       "number too high %s[%d] (%b)",
				       descr, level, bh);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम tb_buffer_sanity_check(काष्ठा super_block *sb,
				   काष्ठा buffer_head *bh,
				   स्थिर अक्षर *descr, पूर्णांक level)
अणु;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक clear_all_dirty_bits(काष्ठा super_block *s, काष्ठा buffer_head *bh)
अणु
	वापस reiserfs_prepare_क्रम_journal(s, bh, 0);
पूर्ण

अटल पूर्णांक रुको_tb_buffers_until_unlocked(काष्ठा tree_balance *tb)
अणु
	काष्ठा buffer_head *locked;
#अगर_घोषित CONFIG_REISERFS_CHECK
	पूर्णांक repeat_counter = 0;
#पूर्ण_अगर
	पूर्णांक i;

	करो अणु

		locked = शून्य;

		क्रम (i = tb->tb_path->path_length;
		     !locked && i > ILLEGAL_PATH_ELEMENT_OFFSET; i--) अणु
			अगर (PATH_OFFSET_PBUFFER(tb->tb_path, i)) अणु
				/*
				 * अगर I understand correctly, we can only
				 * be sure the last buffer in the path is
				 * in the tree --clm
				 */
#अगर_घोषित CONFIG_REISERFS_CHECK
				अगर (PATH_PLAST_BUFFER(tb->tb_path) ==
				    PATH_OFFSET_PBUFFER(tb->tb_path, i))
					tb_buffer_sanity_check(tb->tb_sb,
							       PATH_OFFSET_PBUFFER
							       (tb->tb_path,
								i), "S",
							       tb->tb_path->
							       path_length - i);
#पूर्ण_अगर
				अगर (!clear_all_dirty_bits(tb->tb_sb,
							  PATH_OFFSET_PBUFFER
							  (tb->tb_path,
							   i))) अणु
					locked =
					    PATH_OFFSET_PBUFFER(tb->tb_path,
								i);
				पूर्ण
			पूर्ण
		पूर्ण

		क्रम (i = 0; !locked && i < MAX_HEIGHT && tb->insert_size[i];
		     i++) अणु

			अगर (tb->lnum[i]) अणु

				अगर (tb->L[i]) अणु
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->L[i],
							       "L", i);
					अगर (!clear_all_dirty_bits
					    (tb->tb_sb, tb->L[i]))
						locked = tb->L[i];
				पूर्ण

				अगर (!locked && tb->FL[i]) अणु
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->FL[i],
							       "FL", i);
					अगर (!clear_all_dirty_bits
					    (tb->tb_sb, tb->FL[i]))
						locked = tb->FL[i];
				पूर्ण

				अगर (!locked && tb->CFL[i]) अणु
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->CFL[i],
							       "CFL", i);
					अगर (!clear_all_dirty_bits
					    (tb->tb_sb, tb->CFL[i]))
						locked = tb->CFL[i];
				पूर्ण

			पूर्ण

			अगर (!locked && (tb->rnum[i])) अणु

				अगर (tb->R[i]) अणु
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->R[i],
							       "R", i);
					अगर (!clear_all_dirty_bits
					    (tb->tb_sb, tb->R[i]))
						locked = tb->R[i];
				पूर्ण

				अगर (!locked && tb->FR[i]) अणु
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->FR[i],
							       "FR", i);
					अगर (!clear_all_dirty_bits
					    (tb->tb_sb, tb->FR[i]))
						locked = tb->FR[i];
				पूर्ण

				अगर (!locked && tb->CFR[i]) अणु
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->CFR[i],
							       "CFR", i);
					अगर (!clear_all_dirty_bits
					    (tb->tb_sb, tb->CFR[i]))
						locked = tb->CFR[i];
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * as far as I can tell, this is not required.  The FEB list
		 * seems to be full of newly allocated nodes, which will
		 * never be locked, dirty, or anything अन्यथा.
		 * To be safe, I'm putting in the checks and रुकोs in.
		 * For the moment, they are needed to keep the code in
		 * journal.c from complaining about the buffer.
		 * That code is inside CONFIG_REISERFS_CHECK as well.  --clm
		 */
		क्रम (i = 0; !locked && i < MAX_FEB_SIZE; i++) अणु
			अगर (tb->FEB[i]) अणु
				अगर (!clear_all_dirty_bits
				    (tb->tb_sb, tb->FEB[i]))
					locked = tb->FEB[i];
			पूर्ण
		पूर्ण

		अगर (locked) अणु
			पूर्णांक depth;
#अगर_घोषित CONFIG_REISERFS_CHECK
			repeat_counter++;
			अगर ((repeat_counter % 10000) == 0) अणु
				reiserfs_warning(tb->tb_sb, "reiserfs-8200",
						 "too many iterations waiting "
						 "for buffer to unlock "
						 "(%b)", locked);

				/* Don't loop क्रमever.  Try to recover from possible error. */

				वापस (खाताSYSTEM_CHANGED_TB(tb)) ?
				    REPEAT_SEARCH : CARRY_ON;
			पूर्ण
#पूर्ण_अगर
			depth = reiserfs_ग_लिखो_unlock_nested(tb->tb_sb);
			__रुको_on_buffer(locked);
			reiserfs_ग_लिखो_lock_nested(tb->tb_sb, depth);
			अगर (खाताSYSTEM_CHANGED_TB(tb))
				वापस REPEAT_SEARCH;
		पूर्ण

	पूर्ण जबतक (locked);

	वापस CARRY_ON;
पूर्ण

/*
 * Prepare क्रम balancing, that is
 *	get all necessary parents, and neighbors;
 *	analyze what and where should be moved;
 *	get sufficient number of new nodes;
 * Balancing will start only after all resources will be collected at a समय.
 *
 * When ported to SMP kernels, only at the last moment after all needed nodes
 * are collected in cache, will the resources be locked using the usual
 * textbook ordered lock acquisition algorithms.  Note that ensuring that
 * this code neither ग_लिखो locks what it करोes not need to ग_लिखो lock nor locks
 * out of order will be a pain in the butt that could have been aव्योमed.
 * Grumble grumble. -Hans
 *
 * fix is meant in the sense of render unchanging
 *
 * Latency might be improved by first gathering a list of what buffers
 * are needed and then getting as many of them in parallel as possible? -Hans
 *
 * Parameters:
 *	op_mode	i - insert, d - delete, c - cut (truncate), p - paste (append)
 *	tb	tree_balance काष्ठाure;
 *	inum	item number in S[h];
 *      pos_in_item - comment this अगर you can
 *      ins_ih	item head of item being inserted
 *	data	inserted item or data to be pasted
 * Returns:	1 - schedule occurred जबतक the function worked;
 *	        0 - schedule didn't occur जबतक the function worked;
 *             -1 - अगर no_disk_space
 */

पूर्णांक fix_nodes(पूर्णांक op_mode, काष्ठा tree_balance *tb,
	      काष्ठा item_head *ins_ih, स्थिर व्योम *data)
अणु
	पूर्णांक ret, h, item_num = PATH_LAST_POSITION(tb->tb_path);
	पूर्णांक pos_in_item;

	/*
	 * we set रुको_tb_buffers_run when we have to restore any dirty
	 * bits cleared during रुको_tb_buffers_run
	 */
	पूर्णांक रुको_tb_buffers_run = 0;
	काष्ठा buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);

	++REISERFS_SB(tb->tb_sb)->s_fix_nodes;

	pos_in_item = tb->tb_path->pos_in_item;

	tb->fs_gen = get_generation(tb->tb_sb);

	/*
	 * we prepare and log the super here so it will alपढ़ोy be in the
	 * transaction when करो_balance needs to change it.
	 * This way करो_balance won't have to schedule when trying to prepare
	 * the super क्रम logging
	 */
	reiserfs_prepare_क्रम_journal(tb->tb_sb,
				     SB_BUFFER_WITH_SB(tb->tb_sb), 1);
	journal_mark_dirty(tb->transaction_handle,
			   SB_BUFFER_WITH_SB(tb->tb_sb));
	अगर (खाताSYSTEM_CHANGED_TB(tb))
		वापस REPEAT_SEARCH;

	/* अगर it possible in indirect_to_direct conversion */
	अगर (buffer_locked(tbS0)) अणु
		पूर्णांक depth = reiserfs_ग_लिखो_unlock_nested(tb->tb_sb);
		__रुको_on_buffer(tbS0);
		reiserfs_ग_लिखो_lock_nested(tb->tb_sb, depth);
		अगर (खाताSYSTEM_CHANGED_TB(tb))
			वापस REPEAT_SEARCH;
	पूर्ण
#अगर_घोषित CONFIG_REISERFS_CHECK
	अगर (REISERFS_SB(tb->tb_sb)->cur_tb) अणु
		prपूर्णांक_cur_tb("fix_nodes");
		reiserfs_panic(tb->tb_sb, "PAP-8305",
			       "there is pending do_balance");
	पूर्ण

	अगर (!buffer_uptodate(tbS0) || !B_IS_IN_TREE(tbS0))
		reiserfs_panic(tb->tb_sb, "PAP-8320", "S[0] (%b %z) is "
			       "not uptodate at the beginning of fix_nodes "
			       "or not in tree (mode %c)",
			       tbS0, tbS0, op_mode);

	/* Check parameters. */
	चयन (op_mode) अणु
	हाल M_INSERT:
		अगर (item_num <= 0 || item_num > B_NR_ITEMS(tbS0))
			reiserfs_panic(tb->tb_sb, "PAP-8330", "Incorrect "
				       "item number %d (in S0 - %d) in case "
				       "of insert", item_num,
				       B_NR_ITEMS(tbS0));
		अवरोध;
	हाल M_PASTE:
	हाल M_DELETE:
	हाल M_CUT:
		अगर (item_num < 0 || item_num >= B_NR_ITEMS(tbS0)) अणु
			prपूर्णांक_block(tbS0, 0, -1, -1);
			reiserfs_panic(tb->tb_sb, "PAP-8335", "Incorrect "
				       "item number(%d); mode = %c "
				       "insert_size = %d",
				       item_num, op_mode,
				       tb->insert_size[0]);
		पूर्ण
		अवरोध;
	शेष:
		reiserfs_panic(tb->tb_sb, "PAP-8340", "Incorrect mode "
			       "of operation");
	पूर्ण
#पूर्ण_अगर

	अगर (get_mem_क्रम_भव_node(tb) == REPEAT_SEARCH)
		/* FIXME: maybe -ENOMEM when tb->vn_buf == 0? Now just repeat */
		वापस REPEAT_SEARCH;

	/* Starting from the leaf level; क्रम all levels h of the tree. */
	क्रम (h = 0; h < MAX_HEIGHT && tb->insert_size[h]; h++) अणु
		ret = get_direct_parent(tb, h);
		अगर (ret != CARRY_ON)
			जाओ repeat;

		ret = check_balance(op_mode, tb, h, item_num,
				    pos_in_item, ins_ih, data);
		अगर (ret != CARRY_ON) अणु
			अगर (ret == NO_BALANCING_NEEDED) अणु
				/* No balancing क्रम higher levels needed. */
				ret = get_neighbors(tb, h);
				अगर (ret != CARRY_ON)
					जाओ repeat;
				अगर (h != MAX_HEIGHT - 1)
					tb->insert_size[h + 1] = 0;
				/*
				 * ok, analysis and resource gathering
				 * are complete
				 */
				अवरोध;
			पूर्ण
			जाओ repeat;
		पूर्ण

		ret = get_neighbors(tb, h);
		अगर (ret != CARRY_ON)
			जाओ repeat;

		/*
		 * No disk space, or schedule occurred and analysis may be
		 * invalid and needs to be reकरोne.
		 */
		ret = get_empty_nodes(tb, h);
		अगर (ret != CARRY_ON)
			जाओ repeat;

		/*
		 * We have a positive insert size but no nodes exist on this
		 * level, this means that we are creating a new root.
		 */
		अगर (!PATH_H_PBUFFER(tb->tb_path, h)) अणु

			RFALSE(tb->blknum[h] != 1,
			       "PAP-8350: creating new empty root");

			अगर (h < MAX_HEIGHT - 1)
				tb->insert_size[h + 1] = 0;
		पूर्ण अन्यथा अगर (!PATH_H_PBUFFER(tb->tb_path, h + 1)) अणु
			/*
			 * The tree needs to be grown, so this node S[h]
			 * which is the root node is split पूर्णांकo two nodes,
			 * and a new node (S[h+1]) will be created to
			 * become the root node.
			 */
			अगर (tb->blknum[h] > 1) अणु

				RFALSE(h == MAX_HEIGHT - 1,
				       "PAP-8355: attempt to create too high of a tree");

				tb->insert_size[h + 1] =
				    (DC_SIZE +
				     KEY_SIZE) * (tb->blknum[h] - 1) +
				    DC_SIZE;
			पूर्ण अन्यथा अगर (h < MAX_HEIGHT - 1)
				tb->insert_size[h + 1] = 0;
		पूर्ण अन्यथा
			tb->insert_size[h + 1] =
			    (DC_SIZE + KEY_SIZE) * (tb->blknum[h] - 1);
	पूर्ण

	ret = रुको_tb_buffers_until_unlocked(tb);
	अगर (ret == CARRY_ON) अणु
		अगर (खाताSYSTEM_CHANGED_TB(tb)) अणु
			रुको_tb_buffers_run = 1;
			ret = REPEAT_SEARCH;
			जाओ repeat;
		पूर्ण अन्यथा अणु
			वापस CARRY_ON;
		पूर्ण
	पूर्ण अन्यथा अणु
		रुको_tb_buffers_run = 1;
		जाओ repeat;
	पूर्ण

repeat:
	/*
	 * fix_nodes was unable to perक्रमm its calculation due to
	 * fileप्रणाली got changed under us, lack of मुक्त disk space or i/o
	 * failure. If the first is the हाल - the search will be
	 * repeated. For now - मुक्त all resources acquired so far except
	 * क्रम the new allocated nodes
	 */
	अणु
		पूर्णांक i;

		/* Release path buffers. */
		अगर (रुको_tb_buffers_run) अणु
			pathrअन्यथा_and_restore(tb->tb_sb, tb->tb_path);
		पूर्ण अन्यथा अणु
			pathrअन्यथा(tb->tb_path);
		पूर्ण
		/* brअन्यथा all resources collected क्रम balancing */
		क्रम (i = 0; i < MAX_HEIGHT; i++) अणु
			अगर (रुको_tb_buffers_run) अणु
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->L[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->R[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->FL[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->FR[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->
								 CFL[i]);
				reiserfs_restore_prepared_buffer(tb->tb_sb,
								 tb->
								 CFR[i]);
			पूर्ण

			brअन्यथा(tb->L[i]);
			brअन्यथा(tb->R[i]);
			brअन्यथा(tb->FL[i]);
			brअन्यथा(tb->FR[i]);
			brअन्यथा(tb->CFL[i]);
			brअन्यथा(tb->CFR[i]);

			tb->L[i] = शून्य;
			tb->R[i] = शून्य;
			tb->FL[i] = शून्य;
			tb->FR[i] = शून्य;
			tb->CFL[i] = शून्य;
			tb->CFR[i] = शून्य;
		पूर्ण

		अगर (रुको_tb_buffers_run) अणु
			क्रम (i = 0; i < MAX_FEB_SIZE; i++) अणु
				अगर (tb->FEB[i])
					reiserfs_restore_prepared_buffer
					    (tb->tb_sb, tb->FEB[i]);
			पूर्ण
		पूर्ण
		वापस ret;
	पूर्ण

पूर्ण

व्योम unfix_nodes(काष्ठा tree_balance *tb)
अणु
	पूर्णांक i;

	/* Release path buffers. */
	pathrअन्यथा_and_restore(tb->tb_sb, tb->tb_path);

	/* brअन्यथा all resources collected क्रम balancing */
	क्रम (i = 0; i < MAX_HEIGHT; i++) अणु
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->L[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->R[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->FL[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->FR[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->CFL[i]);
		reiserfs_restore_prepared_buffer(tb->tb_sb, tb->CFR[i]);

		brअन्यथा(tb->L[i]);
		brअन्यथा(tb->R[i]);
		brअन्यथा(tb->FL[i]);
		brअन्यथा(tb->FR[i]);
		brअन्यथा(tb->CFL[i]);
		brअन्यथा(tb->CFR[i]);
	पूर्ण

	/* deal with list of allocated (used and unused) nodes */
	क्रम (i = 0; i < MAX_FEB_SIZE; i++) अणु
		अगर (tb->FEB[i]) अणु
			b_blocknr_t blocknr = tb->FEB[i]->b_blocknr;
			/*
			 * de-allocated block which was not used by
			 * balancing and bक्रमget about buffer क्रम it
			 */
			brअन्यथा(tb->FEB[i]);
			reiserfs_मुक्त_block(tb->transaction_handle, शून्य,
					    blocknr, 0);
		पूर्ण
		अगर (tb->used[i]) अणु
			/* release used as new nodes including a new root */
			brअन्यथा(tb->used[i]);
		पूर्ण
	पूर्ण

	kमुक्त(tb->vn_buf);

पूर्ण
