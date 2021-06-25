<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश "reiserfs.h"
#समावेश <linux/buffer_head.h>

/*
 * copy copy_count entries from source directory item to dest buffer
 * (creating new item अगर needed)
 */
अटल व्योम leaf_copy_dir_entries(काष्ठा buffer_info *dest_bi,
				  काष्ठा buffer_head *source, पूर्णांक last_first,
				  पूर्णांक item_num, पूर्णांक from, पूर्णांक copy_count)
अणु
	काष्ठा buffer_head *dest = dest_bi->bi_bh;
	/*
	 * either the number of target item, or अगर we must create a
	 * new item, the number of the item we will create it next to
	 */
	पूर्णांक item_num_in_dest;

	काष्ठा item_head *ih;
	काष्ठा reiserfs_de_head *deh;
	पूर्णांक copy_records_len;	/* length of all records in item to be copied */
	अक्षर *records;

	ih = item_head(source, item_num);

	RFALSE(!is_direntry_le_ih(ih), "vs-10000: item must be directory item");

	/*
	 * length of all record to be copied and first byte of
	 * the last of them
	 */
	deh = B_I_DEH(source, ih);
	अगर (copy_count) अणु
		copy_records_len = (from ? deh_location(&deh[from - 1]) :
				    ih_item_len(ih)) -
		    deh_location(&deh[from + copy_count - 1]);
		records =
		    source->b_data + ih_location(ih) +
		    deh_location(&deh[from + copy_count - 1]);
	पूर्ण अन्यथा अणु
		copy_records_len = 0;
		records = शून्य;
	पूर्ण

	/* when copy last to first, dest buffer can contain 0 items */
	item_num_in_dest =
	    (last_first ==
	     LAST_TO_FIRST) ? ((B_NR_ITEMS(dest)) ? 0 : -1) : (B_NR_ITEMS(dest)
							       - 1);

	/*
	 * अगर there are no items in dest or the first/last item in
	 * dest is not item of the same directory
	 */
	अगर ((item_num_in_dest == -1) ||
	    (last_first == FIRST_TO_LAST && le_ih_k_offset(ih) == DOT_OFFSET) ||
	    (last_first == LAST_TO_FIRST
	     && comp_लघु_le_keys /*COMP_SHORT_KEYS */ (&ih->ih_key,
							 leaf_key(dest,
								  item_num_in_dest))))
	अणु
		/* create new item in dest */
		काष्ठा item_head new_ih;

		/* क्रमm item header */
		स_नकल(&new_ih.ih_key, &ih->ih_key, KEY_SIZE);
		put_ih_version(&new_ih, KEY_FORMAT_3_5);
		/* calculate item len */
		put_ih_item_len(&new_ih,
				DEH_SIZE * copy_count + copy_records_len);
		put_ih_entry_count(&new_ih, 0);

		अगर (last_first == LAST_TO_FIRST) अणु
			/* क्रमm key by the following way */
			अगर (from < ih_entry_count(ih)) अणु
				set_le_ih_k_offset(&new_ih,
						   deh_offset(&deh[from]));
			पूर्ण अन्यथा अणु
				/*
				 * no entries will be copied to this
				 * item in this function
				 */
				set_le_ih_k_offset(&new_ih, U32_MAX);
				/*
				 * this item is not yet valid, but we
				 * want I_IS_सूचीECTORY_ITEM to वापस 1
				 * क्रम it, so we -1
				 */
			पूर्ण
			set_le_key_k_type(KEY_FORMAT_3_5, &new_ih.ih_key,
					  TYPE_सूचीENTRY);
		पूर्ण

		/* insert item पूर्णांकo dest buffer */
		leaf_insert_पूर्णांकo_buf(dest_bi,
				     (last_first ==
				      LAST_TO_FIRST) ? 0 : B_NR_ITEMS(dest),
				     &new_ih, शून्य, 0);
	पूर्ण अन्यथा अणु
		/* prepare space क्रम entries */
		leaf_paste_in_buffer(dest_bi,
				     (last_first ==
				      FIRST_TO_LAST) ? (B_NR_ITEMS(dest) -
							1) : 0, MAX_US_INT,
				     DEH_SIZE * copy_count + copy_records_len,
				     records, 0);
	पूर्ण

	item_num_in_dest =
	    (last_first == FIRST_TO_LAST) ? (B_NR_ITEMS(dest) - 1) : 0;

	leaf_paste_entries(dest_bi, item_num_in_dest,
			   (last_first ==
			    FIRST_TO_LAST) ? ih_entry_count(item_head(dest,
									  item_num_in_dest))
			   : 0, copy_count, deh + from, records,
			   DEH_SIZE * copy_count + copy_records_len);
पूर्ण

/*
 * Copy the first (अगर last_first == FIRST_TO_LAST) or last
 * (last_first == LAST_TO_FIRST) item or part of it or nothing
 * (see the वापस 0 below) from SOURCE to the end (अगर last_first)
 * or beginning (!last_first) of the DEST
 */
/* वापसs 1 अगर anything was copied, अन्यथा 0 */
अटल पूर्णांक leaf_copy_boundary_item(काष्ठा buffer_info *dest_bi,
				   काष्ठा buffer_head *src, पूर्णांक last_first,
				   पूर्णांक bytes_or_entries)
अणु
	काष्ठा buffer_head *dest = dest_bi->bi_bh;
	/* number of items in the source and destination buffers */
	पूर्णांक dest_nr_item, src_nr_item;
	काष्ठा item_head *ih;
	काष्ठा item_head *dih;

	dest_nr_item = B_NR_ITEMS(dest);

	/*
	 * अगर ( DEST is empty or first item of SOURCE and last item of
	 * DEST are the items of dअगरferent objects or of dअगरferent types )
	 * then there is no need to treat this item dअगरferently from the
	 * other items that we copy, so we वापस
	 */
	अगर (last_first == FIRST_TO_LAST) अणु
		ih = item_head(src, 0);
		dih = item_head(dest, dest_nr_item - 1);

		/* there is nothing to merge */
		अगर (!dest_nr_item
		    || (!op_is_left_mergeable(&ih->ih_key, src->b_size)))
			वापस 0;

		RFALSE(!ih_item_len(ih),
		       "vs-10010: item can not have empty length");

		अगर (is_direntry_le_ih(ih)) अणु
			अगर (bytes_or_entries == -1)
				/* copy all entries to dest */
				bytes_or_entries = ih_entry_count(ih);
			leaf_copy_dir_entries(dest_bi, src, FIRST_TO_LAST, 0, 0,
					      bytes_or_entries);
			वापस 1;
		पूर्ण

		/*
		 * copy part of the body of the first item of SOURCE
		 * to the end of the body of the last item of the DEST
		 * part defined by 'bytes_or_entries'; अगर bytes_or_entries
		 * == -1 copy whole body; करोn't create new item header
		 */
		अगर (bytes_or_entries == -1)
			bytes_or_entries = ih_item_len(ih);

#अगर_घोषित CONFIG_REISERFS_CHECK
		अन्यथा अणु
			अगर (bytes_or_entries == ih_item_len(ih)
			    && is_indirect_le_ih(ih))
				अगर (get_ih_मुक्त_space(ih))
					reiserfs_panic(sb_from_bi(dest_bi),
						       "vs-10020",
						       "last unformatted node "
						       "must be filled "
						       "entirely (%h)", ih);
		पूर्ण
#पूर्ण_अगर

		/*
		 * merge first item (or its part) of src buffer with the last
		 * item of dest buffer. Both are of the same file
		 */
		leaf_paste_in_buffer(dest_bi,
				     dest_nr_item - 1, ih_item_len(dih),
				     bytes_or_entries, ih_item_body(src, ih), 0);

		अगर (is_indirect_le_ih(dih)) अणु
			RFALSE(get_ih_मुक्त_space(dih),
			       "vs-10030: merge to left: last unformatted node of non-last indirect item %h must have zerto free space",
			       ih);
			अगर (bytes_or_entries == ih_item_len(ih))
				set_ih_मुक्त_space(dih, get_ih_मुक्त_space(ih));
		पूर्ण

		वापस 1;
	पूर्ण

	/* copy boundary item to right (last_first == LAST_TO_FIRST) */

	/*
	 * (DEST is empty or last item of SOURCE and first item of DEST
	 * are the items of dअगरferent object or of dअगरferent types)
	 */
	src_nr_item = B_NR_ITEMS(src);
	ih = item_head(src, src_nr_item - 1);
	dih = item_head(dest, 0);

	अगर (!dest_nr_item || !op_is_left_mergeable(&dih->ih_key, src->b_size))
		वापस 0;

	अगर (is_direntry_le_ih(ih)) अणु
		/*
		 * bytes_or_entries = entries number in last
		 * item body of SOURCE
		 */
		अगर (bytes_or_entries == -1)
			bytes_or_entries = ih_entry_count(ih);

		leaf_copy_dir_entries(dest_bi, src, LAST_TO_FIRST,
				      src_nr_item - 1,
				      ih_entry_count(ih) - bytes_or_entries,
				      bytes_or_entries);
		वापस 1;
	पूर्ण

	/*
	 * copy part of the body of the last item of SOURCE to the
	 * begin of the body of the first item of the DEST; part defined
	 * by 'bytes_or_entries'; अगर byte_or_entriess == -1 copy whole body;
	 * change first item key of the DEST; करोn't create new item header
	 */

	RFALSE(is_indirect_le_ih(ih) && get_ih_मुक्त_space(ih),
	       "vs-10040: merge to right: last unformatted node of non-last indirect item must be filled entirely (%h)",
	       ih);

	अगर (bytes_or_entries == -1) अणु
		/* bytes_or_entries = length of last item body of SOURCE */
		bytes_or_entries = ih_item_len(ih);

		RFALSE(le_ih_k_offset(dih) !=
		       le_ih_k_offset(ih) + op_bytes_number(ih, src->b_size),
		       "vs-10050: items %h and %h do not match", ih, dih);

		/* change first item key of the DEST */
		set_le_ih_k_offset(dih, le_ih_k_offset(ih));

		/* item becomes non-mergeable */
		/* or mergeable अगर left item was */
		set_le_ih_k_type(dih, le_ih_k_type(ih));
	पूर्ण अन्यथा अणु
		/* merge to right only part of item */
		RFALSE(ih_item_len(ih) <= bytes_or_entries,
		       "vs-10060: no so much bytes %lu (needed %lu)",
		       (अचिन्हित दीर्घ)ih_item_len(ih),
		       (अचिन्हित दीर्घ)bytes_or_entries);

		/* change first item key of the DEST */
		अगर (is_direct_le_ih(dih)) अणु
			RFALSE(le_ih_k_offset(dih) <=
			       (अचिन्हित दीर्घ)bytes_or_entries,
			       "vs-10070: dih %h, bytes_or_entries(%d)", dih,
			       bytes_or_entries);
			set_le_ih_k_offset(dih,
					   le_ih_k_offset(dih) -
					   bytes_or_entries);
		पूर्ण अन्यथा अणु
			RFALSE(le_ih_k_offset(dih) <=
			       (bytes_or_entries / UNFM_P_SIZE) * dest->b_size,
			       "vs-10080: dih %h, bytes_or_entries(%d)",
			       dih,
			       (bytes_or_entries / UNFM_P_SIZE) * dest->b_size);
			set_le_ih_k_offset(dih,
					   le_ih_k_offset(dih) -
					   ((bytes_or_entries / UNFM_P_SIZE) *
					    dest->b_size));
		पूर्ण
	पूर्ण

	leaf_paste_in_buffer(dest_bi, 0, 0, bytes_or_entries,
			     ih_item_body(src,
				       ih) + ih_item_len(ih) - bytes_or_entries,
			     0);
	वापस 1;
पूर्ण

/*
 * copy cpy_mun items from buffer src to buffer dest
 * last_first == FIRST_TO_LAST means, that we copy cpy_num items beginning
 *                             from first-th item in src to tail of dest
 * last_first == LAST_TO_FIRST means, that we copy cpy_num items beginning
 *                             from first-th item in src to head of dest
 */
अटल व्योम leaf_copy_items_entirely(काष्ठा buffer_info *dest_bi,
				     काष्ठा buffer_head *src, पूर्णांक last_first,
				     पूर्णांक first, पूर्णांक cpy_num)
अणु
	काष्ठा buffer_head *dest;
	पूर्णांक nr, मुक्त_space;
	पूर्णांक dest_beक्रमe;
	पूर्णांक last_loc, last_inserted_loc, location;
	पूर्णांक i, j;
	काष्ठा block_head *blkh;
	काष्ठा item_head *ih;

	RFALSE(last_first != LAST_TO_FIRST && last_first != FIRST_TO_LAST,
	       "vs-10090: bad last_first parameter %d", last_first);
	RFALSE(B_NR_ITEMS(src) - first < cpy_num,
	       "vs-10100: too few items in source %d, required %d from %d",
	       B_NR_ITEMS(src), cpy_num, first);
	RFALSE(cpy_num < 0, "vs-10110: can not copy negative amount of items");
	RFALSE(!dest_bi, "vs-10120: can not copy negative amount of items");

	dest = dest_bi->bi_bh;

	RFALSE(!dest, "vs-10130: can not copy negative amount of items");

	अगर (cpy_num == 0)
		वापस;

	blkh = B_BLK_HEAD(dest);
	nr = blkh_nr_item(blkh);
	मुक्त_space = blkh_मुक्त_space(blkh);

	/*
	 * we will insert items beक्रमe 0-th or nr-th item in dest buffer.
	 * It depends of last_first parameter
	 */
	dest_beक्रमe = (last_first == LAST_TO_FIRST) ? 0 : nr;

	/* location of head of first new item */
	ih = item_head(dest, dest_beक्रमe);

	RFALSE(blkh_मुक्त_space(blkh) < cpy_num * IH_SIZE,
	       "vs-10140: not enough free space for headers %d (needed %d)",
	       B_FREE_SPACE(dest), cpy_num * IH_SIZE);

	/* prepare space क्रम headers */
	स_हटाओ(ih + cpy_num, ih, (nr - dest_beक्रमe) * IH_SIZE);

	/* copy item headers */
	स_नकल(ih, item_head(src, first), cpy_num * IH_SIZE);

	मुक्त_space -= (IH_SIZE * cpy_num);
	set_blkh_मुक्त_space(blkh, मुक्त_space);

	/* location of unmovable item */
	j = location = (dest_beक्रमe == 0) ? dest->b_size : ih_location(ih - 1);
	क्रम (i = dest_beक्रमe; i < nr + cpy_num; i++) अणु
		location -= ih_item_len(ih + i - dest_beक्रमe);
		put_ih_location(ih + i - dest_beक्रमe, location);
	पूर्ण

	/* prepare space क्रम items */
	last_loc = ih_location(&ih[nr + cpy_num - 1 - dest_beक्रमe]);
	last_inserted_loc = ih_location(&ih[cpy_num - 1]);

	/* check मुक्त space */
	RFALSE(मुक्त_space < j - last_inserted_loc,
	       "vs-10150: not enough free space for items %d (needed %d)",
	       मुक्त_space, j - last_inserted_loc);

	स_हटाओ(dest->b_data + last_loc,
		dest->b_data + last_loc + j - last_inserted_loc,
		last_inserted_loc - last_loc);

	/* copy items */
	स_नकल(dest->b_data + last_inserted_loc,
	       item_body(src, (first + cpy_num - 1)),
	       j - last_inserted_loc);

	/* sizes, item number */
	set_blkh_nr_item(blkh, nr + cpy_num);
	set_blkh_मुक्त_space(blkh, मुक्त_space - (j - last_inserted_loc));

	करो_balance_mark_leaf_dirty(dest_bi->tb, dest, 0);

	अगर (dest_bi->bi_parent) अणु
		काष्ठा disk_child *t_dc;
		t_dc = B_N_CHILD(dest_bi->bi_parent, dest_bi->bi_position);
		RFALSE(dc_block_number(t_dc) != dest->b_blocknr,
		       "vs-10160: block number in bh does not match to field in disk_child structure %lu and %lu",
		       (दीर्घ अचिन्हित)dest->b_blocknr,
		       (दीर्घ अचिन्हित)dc_block_number(t_dc));
		put_dc_size(t_dc,
			    dc_size(t_dc) + (j - last_inserted_loc +
					     IH_SIZE * cpy_num));

		करो_balance_mark_पूर्णांकernal_dirty(dest_bi->tb, dest_bi->bi_parent,
					       0);
	पूर्ण
पूर्ण

/*
 * This function splits the (liquid) item पूर्णांकo two items (useful when
 * shअगरting part of an item पूर्णांकo another node.)
 */
अटल व्योम leaf_item_bottle(काष्ठा buffer_info *dest_bi,
			     काष्ठा buffer_head *src, पूर्णांक last_first,
			     पूर्णांक item_num, पूर्णांक cpy_bytes)
अणु
	काष्ठा buffer_head *dest = dest_bi->bi_bh;
	काष्ठा item_head *ih;

	RFALSE(cpy_bytes == -1,
	       "vs-10170: bytes == - 1 means: do not split item");

	अगर (last_first == FIRST_TO_LAST) अणु
		/*
		 * अगर ( अगर item in position item_num in buffer SOURCE
		 * is directory item )
		 */
		ih = item_head(src, item_num);
		अगर (is_direntry_le_ih(ih))
			leaf_copy_dir_entries(dest_bi, src, FIRST_TO_LAST,
					      item_num, 0, cpy_bytes);
		अन्यथा अणु
			काष्ठा item_head n_ih;

			/*
			 * copy part of the body of the item number 'item_num'
			 * of SOURCE to the end of the DEST part defined by
			 * 'cpy_bytes'; create new item header; change old
			 * item_header (????); n_ih = new item_header;
			 */
			स_नकल(&n_ih, ih, IH_SIZE);
			put_ih_item_len(&n_ih, cpy_bytes);
			अगर (is_indirect_le_ih(ih)) अणु
				RFALSE(cpy_bytes == ih_item_len(ih)
				       && get_ih_मुक्त_space(ih),
				       "vs-10180: when whole indirect item is bottle to left neighbor, it must have free_space==0 (not %lu)",
				       (दीर्घ अचिन्हित)get_ih_मुक्त_space(ih));
				set_ih_मुक्त_space(&n_ih, 0);
			पूर्ण

			RFALSE(op_is_left_mergeable(&ih->ih_key, src->b_size),
			       "vs-10190: bad mergeability of item %h", ih);
			n_ih.ih_version = ih->ih_version;	/* JDM Endian safe, both le */
			leaf_insert_पूर्णांकo_buf(dest_bi, B_NR_ITEMS(dest), &n_ih,
					     item_body(src, item_num), 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * अगर ( अगर item in position item_num in buffer
		 * SOURCE is directory item )
		 */
		ih = item_head(src, item_num);
		अगर (is_direntry_le_ih(ih))
			leaf_copy_dir_entries(dest_bi, src, LAST_TO_FIRST,
					      item_num,
					      ih_entry_count(ih) - cpy_bytes,
					      cpy_bytes);
		अन्यथा अणु
			काष्ठा item_head n_ih;

			/*
			 * copy part of the body of the item number 'item_num'
			 * of SOURCE to the begin of the DEST part defined by
			 * 'cpy_bytes'; create new item header;
			 * n_ih = new item_header;
			 */
			स_नकल(&n_ih.ih_key, &ih->ih_key, KEY_SIZE);

			/* Endian safe, both le */
			n_ih.ih_version = ih->ih_version;

			अगर (is_direct_le_ih(ih)) अणु
				set_le_ih_k_offset(&n_ih,
						   le_ih_k_offset(ih) +
						   ih_item_len(ih) - cpy_bytes);
				set_le_ih_k_type(&n_ih, TYPE_सूचीECT);
				set_ih_मुक्त_space(&n_ih, MAX_US_INT);
			पूर्ण अन्यथा अणु
				/* indirect item */
				RFALSE(!cpy_bytes && get_ih_मुक्त_space(ih),
				       "vs-10200: ih->ih_free_space must be 0 when indirect item will be appended");
				set_le_ih_k_offset(&n_ih,
						   le_ih_k_offset(ih) +
						   (ih_item_len(ih) -
						    cpy_bytes) / UNFM_P_SIZE *
						   dest->b_size);
				set_le_ih_k_type(&n_ih, TYPE_INसूचीECT);
				set_ih_मुक्त_space(&n_ih, get_ih_मुक्त_space(ih));
			पूर्ण

			/* set item length */
			put_ih_item_len(&n_ih, cpy_bytes);

			/* Endian safe, both le */
			n_ih.ih_version = ih->ih_version;

			leaf_insert_पूर्णांकo_buf(dest_bi, 0, &n_ih,
					     item_body(src, item_num) +
						ih_item_len(ih) - cpy_bytes, 0);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * If cpy_bytes equals minus one than copy cpy_num whole items from SOURCE
 * to DEST.  If cpy_bytes not equal to minus one than copy cpy_num-1 whole
 * items from SOURCE to DEST.  From last item copy cpy_num bytes क्रम regular
 * item and cpy_num directory entries क्रम directory item.
 */
अटल पूर्णांक leaf_copy_items(काष्ठा buffer_info *dest_bi, काष्ठा buffer_head *src,
			   पूर्णांक last_first, पूर्णांक cpy_num, पूर्णांक cpy_bytes)
अणु
	काष्ठा buffer_head *dest;
	पूर्णांक pos, i, src_nr_item, bytes;

	dest = dest_bi->bi_bh;
	RFALSE(!dest || !src, "vs-10210: !dest || !src");
	RFALSE(last_first != FIRST_TO_LAST && last_first != LAST_TO_FIRST,
	       "vs-10220:last_first != FIRST_TO_LAST && last_first != LAST_TO_FIRST");
	RFALSE(B_NR_ITEMS(src) < cpy_num,
	       "vs-10230: No enough items: %d, req. %d", B_NR_ITEMS(src),
	       cpy_num);
	RFALSE(cpy_num < 0, "vs-10240: cpy_num < 0 (%d)", cpy_num);

	अगर (cpy_num == 0)
		वापस 0;

	अगर (last_first == FIRST_TO_LAST) अणु
		/* copy items to left */
		pos = 0;
		अगर (cpy_num == 1)
			bytes = cpy_bytes;
		अन्यथा
			bytes = -1;

		/*
		 * copy the first item or it part or nothing to the end of
		 * the DEST (i = leaf_copy_boundary_item(DEST,SOURCE,0,bytes))
		 */
		i = leaf_copy_boundary_item(dest_bi, src, FIRST_TO_LAST, bytes);
		cpy_num -= i;
		अगर (cpy_num == 0)
			वापस i;
		pos += i;
		अगर (cpy_bytes == -1)
			/*
			 * copy first cpy_num items starting from position
			 * 'pos' of SOURCE to end of DEST
			 */
			leaf_copy_items_entirely(dest_bi, src, FIRST_TO_LAST,
						 pos, cpy_num);
		अन्यथा अणु
			/*
			 * copy first cpy_num-1 items starting from position
			 * 'pos-1' of the SOURCE to the end of the DEST
			 */
			leaf_copy_items_entirely(dest_bi, src, FIRST_TO_LAST,
						 pos, cpy_num - 1);

			/*
			 * copy part of the item which number is
			 * cpy_num+pos-1 to the end of the DEST
			 */
			leaf_item_bottle(dest_bi, src, FIRST_TO_LAST,
					 cpy_num + pos - 1, cpy_bytes);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* copy items to right */
		src_nr_item = B_NR_ITEMS(src);
		अगर (cpy_num == 1)
			bytes = cpy_bytes;
		अन्यथा
			bytes = -1;

		/*
		 * copy the last item or it part or nothing to the
		 * begin of the DEST
		 * (i = leaf_copy_boundary_item(DEST,SOURCE,1,bytes));
		 */
		i = leaf_copy_boundary_item(dest_bi, src, LAST_TO_FIRST, bytes);

		cpy_num -= i;
		अगर (cpy_num == 0)
			वापस i;

		pos = src_nr_item - cpy_num - i;
		अगर (cpy_bytes == -1) अणु
			/*
			 * starting from position 'pos' copy last cpy_num
			 * items of SOURCE to begin of DEST
			 */
			leaf_copy_items_entirely(dest_bi, src, LAST_TO_FIRST,
						 pos, cpy_num);
		पूर्ण अन्यथा अणु
			/*
			 * copy last cpy_num-1 items starting from position
			 * 'pos+1' of the SOURCE to the begin of the DEST;
			 */
			leaf_copy_items_entirely(dest_bi, src, LAST_TO_FIRST,
						 pos + 1, cpy_num - 1);

			/*
			 * copy part of the item which number is pos to
			 * the begin of the DEST
			 */
			leaf_item_bottle(dest_bi, src, LAST_TO_FIRST, pos,
					 cpy_bytes);
		पूर्ण
	पूर्ण
	वापस i;
पूर्ण

/*
 * there are types of coping: from S[0] to L[0], from S[0] to R[0],
 * from R[0] to L[0]. क्रम each of these we have to define parent and
 * positions of destination and source buffers
 */
अटल व्योम leaf_define_dest_src_infos(पूर्णांक shअगरt_mode, काष्ठा tree_balance *tb,
				       काष्ठा buffer_info *dest_bi,
				       काष्ठा buffer_info *src_bi,
				       पूर्णांक *first_last,
				       काष्ठा buffer_head *Snew)
अणु
	स_रखो(dest_bi, 0, माप(काष्ठा buffer_info));
	स_रखो(src_bi, 0, माप(काष्ठा buffer_info));

	/* define dest, src, dest parent, dest position */
	चयन (shअगरt_mode) अणु
	हाल LEAF_FROM_S_TO_L:	/* it is used in leaf_shअगरt_left */
		src_bi->tb = tb;
		src_bi->bi_bh = PATH_PLAST_BUFFER(tb->tb_path);
		src_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, 0);

		/* src->b_item_order */
		src_bi->bi_position = PATH_H_B_ITEM_ORDER(tb->tb_path, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->L[0];
		dest_bi->bi_parent = tb->FL[0];
		dest_bi->bi_position = get_left_neighbor_position(tb, 0);
		*first_last = FIRST_TO_LAST;
		अवरोध;

	हाल LEAF_FROM_S_TO_R:	/* it is used in leaf_shअगरt_right */
		src_bi->tb = tb;
		src_bi->bi_bh = PATH_PLAST_BUFFER(tb->tb_path);
		src_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, 0);
		src_bi->bi_position = PATH_H_B_ITEM_ORDER(tb->tb_path, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->R[0];
		dest_bi->bi_parent = tb->FR[0];
		dest_bi->bi_position = get_right_neighbor_position(tb, 0);
		*first_last = LAST_TO_FIRST;
		अवरोध;

	हाल LEAF_FROM_R_TO_L:	/* it is used in balance_leaf_when_delete */
		src_bi->tb = tb;
		src_bi->bi_bh = tb->R[0];
		src_bi->bi_parent = tb->FR[0];
		src_bi->bi_position = get_right_neighbor_position(tb, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->L[0];
		dest_bi->bi_parent = tb->FL[0];
		dest_bi->bi_position = get_left_neighbor_position(tb, 0);
		*first_last = FIRST_TO_LAST;
		अवरोध;

	हाल LEAF_FROM_L_TO_R:	/* it is used in balance_leaf_when_delete */
		src_bi->tb = tb;
		src_bi->bi_bh = tb->L[0];
		src_bi->bi_parent = tb->FL[0];
		src_bi->bi_position = get_left_neighbor_position(tb, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->R[0];
		dest_bi->bi_parent = tb->FR[0];
		dest_bi->bi_position = get_right_neighbor_position(tb, 0);
		*first_last = LAST_TO_FIRST;
		अवरोध;

	हाल LEAF_FROM_S_TO_SNEW:
		src_bi->tb = tb;
		src_bi->bi_bh = PATH_PLAST_BUFFER(tb->tb_path);
		src_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, 0);
		src_bi->bi_position = PATH_H_B_ITEM_ORDER(tb->tb_path, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = Snew;
		dest_bi->bi_parent = शून्य;
		dest_bi->bi_position = 0;
		*first_last = LAST_TO_FIRST;
		अवरोध;

	शेष:
		reiserfs_panic(sb_from_bi(src_bi), "vs-10250",
			       "shift type is unknown (%d)", shअगरt_mode);
	पूर्ण
	RFALSE(!src_bi->bi_bh || !dest_bi->bi_bh,
	       "vs-10260: mode==%d, source (%p) or dest (%p) buffer is initialized incorrectly",
	       shअगरt_mode, src_bi->bi_bh, dest_bi->bi_bh);
पूर्ण

/*
 * copy mov_num items and mov_bytes of the (mov_num-1)th item to
 * neighbor. Delete them from source
 */
पूर्णांक leaf_move_items(पूर्णांक shअगरt_mode, काष्ठा tree_balance *tb, पूर्णांक mov_num,
		    पूर्णांक mov_bytes, काष्ठा buffer_head *Snew)
अणु
	पूर्णांक ret_value;
	काष्ठा buffer_info dest_bi, src_bi;
	पूर्णांक first_last;

	leaf_define_dest_src_infos(shअगरt_mode, tb, &dest_bi, &src_bi,
				   &first_last, Snew);

	ret_value =
	    leaf_copy_items(&dest_bi, src_bi.bi_bh, first_last, mov_num,
			    mov_bytes);

	leaf_delete_items(&src_bi, first_last,
			  (first_last ==
			   FIRST_TO_LAST) ? 0 : (B_NR_ITEMS(src_bi.bi_bh) -
						 mov_num), mov_num, mov_bytes);

	वापस ret_value;
पूर्ण

/*
 * Shअगरt shअगरt_num items (and shअगरt_bytes of last shअगरted item अगर
 * shअगरt_bytes != -1) from S[0] to L[0] and replace the delimiting key
 */
पूर्णांक leaf_shअगरt_left(काष्ठा tree_balance *tb, पूर्णांक shअगरt_num, पूर्णांक shअगरt_bytes)
अणु
	काष्ठा buffer_head *S0 = PATH_PLAST_BUFFER(tb->tb_path);
	पूर्णांक i;

	/*
	 * move shअगरt_num (and shअगरt_bytes bytes) items from S[0]
	 * to left neighbor L[0]
	 */
	i = leaf_move_items(LEAF_FROM_S_TO_L, tb, shअगरt_num, shअगरt_bytes, शून्य);

	अगर (shअगरt_num) अणु
		/* number of items in S[0] == 0 */
		अगर (B_NR_ITEMS(S0) == 0) अणु

			RFALSE(shअगरt_bytes != -1,
			       "vs-10270: S0 is empty now, but shift_bytes != -1 (%d)",
			       shअगरt_bytes);
#अगर_घोषित CONFIG_REISERFS_CHECK
			अगर (tb->tb_mode == M_PASTE || tb->tb_mode == M_INSERT) अणु
				prपूर्णांक_cur_tb("vs-10275");
				reiserfs_panic(tb->tb_sb, "vs-10275",
					       "balance condition corrupted "
					       "(%c)", tb->tb_mode);
			पूर्ण
#पूर्ण_अगर

			अगर (PATH_H_POSITION(tb->tb_path, 1) == 0)
				replace_key(tb, tb->CFL[0], tb->lkey[0],
					    PATH_H_PPARENT(tb->tb_path, 0), 0);

		पूर्ण अन्यथा अणु
			/* replace lkey in CFL[0] by 0-th key from S[0]; */
			replace_key(tb, tb->CFL[0], tb->lkey[0], S0, 0);

			RFALSE((shअगरt_bytes != -1 &&
				!(is_direntry_le_ih(item_head(S0, 0))
				  && !ih_entry_count(item_head(S0, 0)))) &&
			       (!op_is_left_mergeable
				(leaf_key(S0, 0), S0->b_size)),
			       "vs-10280: item must be mergeable");
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण

/* CLEANING STOPPED HERE */

/*
 * Shअगरt shअगरt_num (shअगरt_bytes) items from S[0] to the right neighbor,
 * and replace the delimiting key
 */
पूर्णांक leaf_shअगरt_right(काष्ठा tree_balance *tb, पूर्णांक shअगरt_num, पूर्णांक shअगरt_bytes)
अणु
	पूर्णांक ret_value;

	/*
	 * move shअगरt_num (and shअगरt_bytes) items from S[0] to
	 * right neighbor R[0]
	 */
	ret_value =
	    leaf_move_items(LEAF_FROM_S_TO_R, tb, shअगरt_num, shअगरt_bytes, शून्य);

	/* replace rkey in CFR[0] by the 0-th key from R[0] */
	अगर (shअगरt_num) अणु
		replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);

	पूर्ण

	वापस ret_value;
पूर्ण

अटल व्योम leaf_delete_items_entirely(काष्ठा buffer_info *bi,
				       पूर्णांक first, पूर्णांक del_num);
/*
 * If del_bytes == -1, starting from position 'first' delete del_num
 * items in whole in buffer CUR.
 *   If not.
 *   If last_first == 0. Starting from position 'first' delete del_num-1
 *   items in whole. Delete part of body of the first item. Part defined by
 *   del_bytes. Don't delete first item header
 *   If last_first == 1. Starting from position 'first+1' delete del_num-1
 *   items in whole. Delete part of body of the last item . Part defined by
 *   del_bytes. Don't delete last item header.
*/
व्योम leaf_delete_items(काष्ठा buffer_info *cur_bi, पूर्णांक last_first,
		       पूर्णांक first, पूर्णांक del_num, पूर्णांक del_bytes)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक item_amount = B_NR_ITEMS(bh = cur_bi->bi_bh);

	RFALSE(!bh, "10155: bh is not defined");
	RFALSE(del_num < 0, "10160: del_num can not be < 0. del_num==%d",
	       del_num);
	RFALSE(first < 0
	       || first + del_num > item_amount,
	       "10165: invalid number of first item to be deleted (%d) or "
	       "no so much items (%d) to delete (only %d)", first,
	       first + del_num, item_amount);

	अगर (del_num == 0)
		वापस;

	अगर (first == 0 && del_num == item_amount && del_bytes == -1) अणु
		make_empty_node(cur_bi);
		करो_balance_mark_leaf_dirty(cur_bi->tb, bh, 0);
		वापस;
	पूर्ण

	अगर (del_bytes == -1)
		/* delete del_num items beginning from item in position first */
		leaf_delete_items_entirely(cur_bi, first, del_num);
	अन्यथा अणु
		अगर (last_first == FIRST_TO_LAST) अणु
			/*
			 * delete del_num-1 items beginning from
			 * item in position first
			 */
			leaf_delete_items_entirely(cur_bi, first, del_num - 1);

			/*
			 * delete the part of the first item of the bh
			 * करो not delete item header
			 */
			leaf_cut_from_buffer(cur_bi, 0, 0, del_bytes);
		पूर्ण अन्यथा अणु
			काष्ठा item_head *ih;
			पूर्णांक len;

			/*
			 * delete del_num-1 items beginning from
			 * item in position first+1
			 */
			leaf_delete_items_entirely(cur_bi, first + 1,
						   del_num - 1);

			ih = item_head(bh, B_NR_ITEMS(bh) - 1);
			अगर (is_direntry_le_ih(ih))
				/* the last item is directory  */
				/*
				 * len = numbers of directory entries
				 * in this item
				 */
				len = ih_entry_count(ih);
			अन्यथा
				/* len = body len of item */
				len = ih_item_len(ih);

			/*
			 * delete the part of the last item of the bh
			 * करो not delete item header
			 */
			leaf_cut_from_buffer(cur_bi, B_NR_ITEMS(bh) - 1,
					     len - del_bytes, del_bytes);
		पूर्ण
	पूर्ण
पूर्ण

/* insert item पूर्णांकo the leaf node in position beक्रमe */
व्योम leaf_insert_पूर्णांकo_buf(काष्ठा buffer_info *bi, पूर्णांक beक्रमe,
			  काष्ठा item_head * स्थिर inserted_item_ih,
			  स्थिर अक्षर * स्थिर inserted_item_body,
			  पूर्णांक zeros_number)
अणु
	काष्ठा buffer_head *bh = bi->bi_bh;
	पूर्णांक nr, मुक्त_space;
	काष्ठा block_head *blkh;
	काष्ठा item_head *ih;
	पूर्णांक i;
	पूर्णांक last_loc, unmoved_loc;
	अक्षर *to;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);
	मुक्त_space = blkh_मुक्त_space(blkh);

	/* check मुक्त space */
	RFALSE(मुक्त_space < ih_item_len(inserted_item_ih) + IH_SIZE,
	       "vs-10170: not enough free space in block %z, new item %h",
	       bh, inserted_item_ih);
	RFALSE(zeros_number > ih_item_len(inserted_item_ih),
	       "vs-10172: zero number == %d, item length == %d",
	       zeros_number, ih_item_len(inserted_item_ih));

	/* get item new item must be inserted beक्रमe */
	ih = item_head(bh, beक्रमe);

	/* prepare space क्रम the body of new item */
	last_loc = nr ? ih_location(&ih[nr - beक्रमe - 1]) : bh->b_size;
	unmoved_loc = beक्रमe ? ih_location(ih - 1) : bh->b_size;

	स_हटाओ(bh->b_data + last_loc - ih_item_len(inserted_item_ih),
		bh->b_data + last_loc, unmoved_loc - last_loc);

	to = bh->b_data + unmoved_loc - ih_item_len(inserted_item_ih);
	स_रखो(to, 0, zeros_number);
	to += zeros_number;

	/* copy body to prepared space */
	अगर (inserted_item_body)
		स_हटाओ(to, inserted_item_body,
			ih_item_len(inserted_item_ih) - zeros_number);
	अन्यथा
		स_रखो(to, '\0', ih_item_len(inserted_item_ih) - zeros_number);

	/* insert item header */
	स_हटाओ(ih + 1, ih, IH_SIZE * (nr - beक्रमe));
	स_हटाओ(ih, inserted_item_ih, IH_SIZE);

	/* change locations */
	क्रम (i = beक्रमe; i < nr + 1; i++) अणु
		unmoved_loc -= ih_item_len(&ih[i - beक्रमe]);
		put_ih_location(&ih[i - beक्रमe], unmoved_loc);
	पूर्ण

	/* sizes, मुक्त space, item number */
	set_blkh_nr_item(blkh, blkh_nr_item(blkh) + 1);
	set_blkh_मुक्त_space(blkh,
			    मुक्त_space - (IH_SIZE +
					  ih_item_len(inserted_item_ih)));
	करो_balance_mark_leaf_dirty(bi->tb, bh, 1);

	अगर (bi->bi_parent) अणु
		काष्ठा disk_child *t_dc;
		t_dc = B_N_CHILD(bi->bi_parent, bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) + (IH_SIZE +
					     ih_item_len(inserted_item_ih)));
		करो_balance_mark_पूर्णांकernal_dirty(bi->tb, bi->bi_parent, 0);
	पूर्ण
पूर्ण

/*
 * paste paste_size bytes to affected_item_num-th item.
 * When item is a directory, this only prepare space क्रम new entries
 */
व्योम leaf_paste_in_buffer(काष्ठा buffer_info *bi, पूर्णांक affected_item_num,
			  पूर्णांक pos_in_item, पूर्णांक paste_size,
			  स्थिर अक्षर *body, पूर्णांक zeros_number)
अणु
	काष्ठा buffer_head *bh = bi->bi_bh;
	पूर्णांक nr, मुक्त_space;
	काष्ठा block_head *blkh;
	काष्ठा item_head *ih;
	पूर्णांक i;
	पूर्णांक last_loc, unmoved_loc;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);
	मुक्त_space = blkh_मुक्त_space(blkh);

	/* check मुक्त space */
	RFALSE(मुक्त_space < paste_size,
	       "vs-10175: not enough free space: needed %d, available %d",
	       paste_size, मुक्त_space);

#अगर_घोषित CONFIG_REISERFS_CHECK
	अगर (zeros_number > paste_size) अणु
		काष्ठा super_block *sb = शून्य;
		अगर (bi && bi->tb)
			sb = bi->tb->tb_sb;
		prपूर्णांक_cur_tb("10177");
		reiserfs_panic(sb, "vs-10177",
			       "zeros_number == %d, paste_size == %d",
			       zeros_number, paste_size);
	पूर्ण
#पूर्ण_अगर				/* CONFIG_REISERFS_CHECK */

	/* item to be appended */
	ih = item_head(bh, affected_item_num);

	last_loc = ih_location(&ih[nr - affected_item_num - 1]);
	unmoved_loc = affected_item_num ? ih_location(ih - 1) : bh->b_size;

	/* prepare space */
	स_हटाओ(bh->b_data + last_loc - paste_size, bh->b_data + last_loc,
		unmoved_loc - last_loc);

	/* change locations */
	क्रम (i = affected_item_num; i < nr; i++)
		put_ih_location(&ih[i - affected_item_num],
				ih_location(&ih[i - affected_item_num]) -
				paste_size);

	अगर (body) अणु
		अगर (!is_direntry_le_ih(ih)) अणु
			अगर (!pos_in_item) अणु
				/* shअगरt data to right */
				स_हटाओ(bh->b_data + ih_location(ih) +
					paste_size,
					bh->b_data + ih_location(ih),
					ih_item_len(ih));
				/* paste data in the head of item */
				स_रखो(bh->b_data + ih_location(ih), 0,
				       zeros_number);
				स_नकल(bh->b_data + ih_location(ih) +
				       zeros_number, body,
				       paste_size - zeros_number);
			पूर्ण अन्यथा अणु
				स_रखो(bh->b_data + unmoved_loc - paste_size, 0,
				       zeros_number);
				स_नकल(bh->b_data + unmoved_loc - paste_size +
				       zeros_number, body,
				       paste_size - zeros_number);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		स_रखो(bh->b_data + unmoved_loc - paste_size, '\0', paste_size);

	put_ih_item_len(ih, ih_item_len(ih) + paste_size);

	/* change मुक्त space */
	set_blkh_मुक्त_space(blkh, मुक्त_space - paste_size);

	करो_balance_mark_leaf_dirty(bi->tb, bh, 0);

	अगर (bi->bi_parent) अणु
		काष्ठा disk_child *t_dc =
		    B_N_CHILD(bi->bi_parent, bi->bi_position);
		put_dc_size(t_dc, dc_size(t_dc) + paste_size);
		करो_balance_mark_पूर्णांकernal_dirty(bi->tb, bi->bi_parent, 0);
	पूर्ण
पूर्ण

/*
 * cuts DEL_COUNT entries beginning from FROM-th entry. Directory item
 * करोes not have मुक्त space, so it moves DEHs and reमुख्यing records as
 * necessary. Return value is size of हटाओd part of directory item
 * in bytes.
 */
अटल पूर्णांक leaf_cut_entries(काष्ठा buffer_head *bh,
			    काष्ठा item_head *ih, पूर्णांक from, पूर्णांक del_count)
अणु
	अक्षर *item;
	काष्ठा reiserfs_de_head *deh;
	पूर्णांक prev_record_offset;	/* offset of record, that is (from-1)th */
	अक्षर *prev_record;	/* */
	पूर्णांक cut_records_len;	/* length of all हटाओd records */
	पूर्णांक i;

	/*
	 * make sure that item is directory and there are enough entries to
	 * हटाओ
	 */
	RFALSE(!is_direntry_le_ih(ih), "10180: item is not directory item");
	RFALSE(ih_entry_count(ih) < from + del_count,
	       "10185: item contains not enough entries: entry_count = %d, from = %d, to delete = %d",
	       ih_entry_count(ih), from, del_count);

	अगर (del_count == 0)
		वापस 0;

	/* first byte of item */
	item = bh->b_data + ih_location(ih);

	/* entry head array */
	deh = B_I_DEH(bh, ih);

	/*
	 * first byte of reमुख्यing entries, those are BEFORE cut entries
	 * (prev_record) and length of all हटाओd records (cut_records_len)
	 */
	prev_record_offset =
	    (from ? deh_location(&deh[from - 1]) : ih_item_len(ih));
	cut_records_len = prev_record_offset /*from_record */  -
	    deh_location(&deh[from + del_count - 1]);
	prev_record = item + prev_record_offset;

	/* adjust locations of reमुख्यing entries */
	क्रम (i = ih_entry_count(ih) - 1; i > from + del_count - 1; i--)
		put_deh_location(&deh[i],
				 deh_location(&deh[i]) -
				 (DEH_SIZE * del_count));

	क्रम (i = 0; i < from; i++)
		put_deh_location(&deh[i],
				 deh_location(&deh[i]) - (DEH_SIZE * del_count +
							  cut_records_len));

	put_ih_entry_count(ih, ih_entry_count(ih) - del_count);

	/* shअगरt entry head array and entries those are AFTER हटाओd entries */
	स_हटाओ((अक्षर *)(deh + from),
		deh + from + del_count,
		prev_record - cut_records_len - (अक्षर *)(deh + from +
							 del_count));

	/* shअगरt records, those are BEFORE हटाओd entries */
	स_हटाओ(prev_record - cut_records_len - DEH_SIZE * del_count,
		prev_record, item + ih_item_len(ih) - prev_record);

	वापस DEH_SIZE * del_count + cut_records_len;
पूर्ण

/*
 * when cut item is part of regular file
 *      pos_in_item - first byte that must be cut
 *      cut_size - number of bytes to be cut beginning from pos_in_item
 *
 * when cut item is part of directory
 *      pos_in_item - number of first deleted entry
 *      cut_size - count of deleted entries
 */
व्योम leaf_cut_from_buffer(काष्ठा buffer_info *bi, पूर्णांक cut_item_num,
			  पूर्णांक pos_in_item, पूर्णांक cut_size)
अणु
	पूर्णांक nr;
	काष्ठा buffer_head *bh = bi->bi_bh;
	काष्ठा block_head *blkh;
	काष्ठा item_head *ih;
	पूर्णांक last_loc, unmoved_loc;
	पूर्णांक i;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);

	/* item head of truncated item */
	ih = item_head(bh, cut_item_num);

	अगर (is_direntry_le_ih(ih)) अणु
		/* first cut entry () */
		cut_size = leaf_cut_entries(bh, ih, pos_in_item, cut_size);
		अगर (pos_in_item == 0) अणु
			/* change key */
			RFALSE(cut_item_num,
			       "when 0-th enrty of item is cut, that item must be first in the node, not %d-th",
			       cut_item_num);
			/* change item key by key of first entry in the item */
			set_le_ih_k_offset(ih, deh_offset(B_I_DEH(bh, ih)));
		पूर्ण
	पूर्ण अन्यथा अणु
		/* item is direct or indirect */
		RFALSE(is_statdata_le_ih(ih), "10195: item is stat data");
		RFALSE(pos_in_item && pos_in_item + cut_size != ih_item_len(ih),
		       "10200: invalid offset (%lu) or trunc_size (%lu) or ih_item_len (%lu)",
		       (दीर्घ अचिन्हित)pos_in_item, (दीर्घ अचिन्हित)cut_size,
		       (दीर्घ अचिन्हित)ih_item_len(ih));

		/* shअगरt item body to left अगर cut is from the head of item */
		अगर (pos_in_item == 0) अणु
			स_हटाओ(bh->b_data + ih_location(ih),
				bh->b_data + ih_location(ih) + cut_size,
				ih_item_len(ih) - cut_size);

			/* change key of item */
			अगर (is_direct_le_ih(ih))
				set_le_ih_k_offset(ih,
						   le_ih_k_offset(ih) +
						   cut_size);
			अन्यथा अणु
				set_le_ih_k_offset(ih,
						   le_ih_k_offset(ih) +
						   (cut_size / UNFM_P_SIZE) *
						   bh->b_size);
				RFALSE(ih_item_len(ih) == cut_size
				       && get_ih_मुक्त_space(ih),
				       "10205: invalid ih_free_space (%h)", ih);
			पूर्ण
		पूर्ण
	पूर्ण

	/* location of the last item */
	last_loc = ih_location(&ih[nr - cut_item_num - 1]);

	/* location of the item, which is reमुख्यing at the same place */
	unmoved_loc = cut_item_num ? ih_location(ih - 1) : bh->b_size;

	/* shअगरt */
	स_हटाओ(bh->b_data + last_loc + cut_size, bh->b_data + last_loc,
		unmoved_loc - last_loc - cut_size);

	/* change item length */
	put_ih_item_len(ih, ih_item_len(ih) - cut_size);

	अगर (is_indirect_le_ih(ih)) अणु
		अगर (pos_in_item)
			set_ih_मुक्त_space(ih, 0);
	पूर्ण

	/* change locations */
	क्रम (i = cut_item_num; i < nr; i++)
		put_ih_location(&ih[i - cut_item_num],
				ih_location(&ih[i - cut_item_num]) + cut_size);

	/* size, मुक्त space */
	set_blkh_मुक्त_space(blkh, blkh_मुक्त_space(blkh) + cut_size);

	करो_balance_mark_leaf_dirty(bi->tb, bh, 0);

	अगर (bi->bi_parent) अणु
		काष्ठा disk_child *t_dc;
		t_dc = B_N_CHILD(bi->bi_parent, bi->bi_position);
		put_dc_size(t_dc, dc_size(t_dc) - cut_size);
		करो_balance_mark_पूर्णांकernal_dirty(bi->tb, bi->bi_parent, 0);
	पूर्ण
पूर्ण

/* delete del_num items from buffer starting from the first'th item */
अटल व्योम leaf_delete_items_entirely(काष्ठा buffer_info *bi,
				       पूर्णांक first, पूर्णांक del_num)
अणु
	काष्ठा buffer_head *bh = bi->bi_bh;
	पूर्णांक nr;
	पूर्णांक i, j;
	पूर्णांक last_loc, last_हटाओd_loc;
	काष्ठा block_head *blkh;
	काष्ठा item_head *ih;

	RFALSE(bh == शून्य, "10210: buffer is 0");
	RFALSE(del_num < 0, "10215: del_num less than 0 (%d)", del_num);

	अगर (del_num == 0)
		वापस;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);

	RFALSE(first < 0 || first + del_num > nr,
	       "10220: first=%d, number=%d, there is %d items", first, del_num,
	       nr);

	अगर (first == 0 && del_num == nr) अणु
		/* this करोes not work */
		make_empty_node(bi);

		करो_balance_mark_leaf_dirty(bi->tb, bh, 0);
		वापस;
	पूर्ण

	ih = item_head(bh, first);

	/* location of unmovable item */
	j = (first == 0) ? bh->b_size : ih_location(ih - 1);

	/* delete items */
	last_loc = ih_location(&ih[nr - 1 - first]);
	last_हटाओd_loc = ih_location(&ih[del_num - 1]);

	स_हटाओ(bh->b_data + last_loc + j - last_हटाओd_loc,
		bh->b_data + last_loc, last_हटाओd_loc - last_loc);

	/* delete item headers */
	स_हटाओ(ih, ih + del_num, (nr - first - del_num) * IH_SIZE);

	/* change item location */
	क्रम (i = first; i < nr - del_num; i++)
		put_ih_location(&ih[i - first],
				ih_location(&ih[i - first]) + (j -
								 last_हटाओd_loc));

	/* sizes, item number */
	set_blkh_nr_item(blkh, blkh_nr_item(blkh) - del_num);
	set_blkh_मुक्त_space(blkh,
			    blkh_मुक्त_space(blkh) + (j - last_हटाओd_loc +
						     IH_SIZE * del_num));

	करो_balance_mark_leaf_dirty(bi->tb, bh, 0);

	अगर (bi->bi_parent) अणु
		काष्ठा disk_child *t_dc =
		    B_N_CHILD(bi->bi_parent, bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) - (j - last_हटाओd_loc +
					     IH_SIZE * del_num));
		करो_balance_mark_पूर्णांकernal_dirty(bi->tb, bi->bi_parent, 0);
	पूर्ण
पूर्ण

/*
 * paste new_entry_count entries (new_dehs, records) पूर्णांकo position
 * beक्रमe to item_num-th item
 */
व्योम leaf_paste_entries(काष्ठा buffer_info *bi,
			पूर्णांक item_num,
			पूर्णांक beक्रमe,
			पूर्णांक new_entry_count,
			काष्ठा reiserfs_de_head *new_dehs,
			स्थिर अक्षर *records, पूर्णांक paste_size)
अणु
	काष्ठा item_head *ih;
	अक्षर *item;
	काष्ठा reiserfs_de_head *deh;
	अक्षर *insert_poपूर्णांक;
	पूर्णांक i;
	काष्ठा buffer_head *bh = bi->bi_bh;

	अगर (new_entry_count == 0)
		वापस;

	ih = item_head(bh, item_num);

	/*
	 * make sure, that item is directory, and there are enough
	 * records in it
	 */
	RFALSE(!is_direntry_le_ih(ih), "10225: item is not directory item");
	RFALSE(ih_entry_count(ih) < beक्रमe,
	       "10230: there are no entry we paste entries before. entry_count = %d, before = %d",
	       ih_entry_count(ih), beक्रमe);

	/* first byte of dest item */
	item = bh->b_data + ih_location(ih);

	/* entry head array */
	deh = B_I_DEH(bh, ih);

	/* new records will be pasted at this poपूर्णांक */
	insert_poपूर्णांक =
	    item +
	    (beक्रमe ? deh_location(&deh[beक्रमe - 1])
	     : (ih_item_len(ih) - paste_size));

	/* adjust locations of records that will be AFTER new records */
	क्रम (i = ih_entry_count(ih) - 1; i >= beक्रमe; i--)
		put_deh_location(&deh[i],
				 deh_location(&deh[i]) +
				 (DEH_SIZE * new_entry_count));

	/* adjust locations of records that will be BEFORE new records */
	क्रम (i = 0; i < beक्रमe; i++)
		put_deh_location(&deh[i],
				 deh_location(&deh[i]) + paste_size);

	put_ih_entry_count(ih, ih_entry_count(ih) + new_entry_count);

	/* prepare space क्रम pasted records */
	स_हटाओ(insert_poपूर्णांक + paste_size, insert_poपूर्णांक,
		item + (ih_item_len(ih) - paste_size) - insert_poपूर्णांक);

	/* copy new records */
	स_नकल(insert_poपूर्णांक + DEH_SIZE * new_entry_count, records,
	       paste_size - DEH_SIZE * new_entry_count);

	/* prepare space क्रम new entry heads */
	deh += beक्रमe;
	स_हटाओ((अक्षर *)(deh + new_entry_count), deh,
		insert_poपूर्णांक - (अक्षर *)deh);

	/* copy new entry heads */
	deh = (काष्ठा reiserfs_de_head *)((अक्षर *)deh);
	स_नकल(deh, new_dehs, DEH_SIZE * new_entry_count);

	/* set locations of new records */
	क्रम (i = 0; i < new_entry_count; i++) अणु
		put_deh_location(&deh[i],
				 deh_location(&deh[i]) +
				 (-deh_location
				  (&new_dehs[new_entry_count - 1]) +
				  insert_poपूर्णांक + DEH_SIZE * new_entry_count -
				  item));
	पूर्ण

	/* change item key अगर necessary (when we paste beक्रमe 0-th entry */
	अगर (!beक्रमe) अणु
		set_le_ih_k_offset(ih, deh_offset(new_dehs));
	पूर्ण
#अगर_घोषित CONFIG_REISERFS_CHECK
	अणु
		पूर्णांक prev, next;
		/* check record locations */
		deh = B_I_DEH(bh, ih);
		क्रम (i = 0; i < ih_entry_count(ih); i++) अणु
			next =
			    (i <
			     ih_entry_count(ih) -
			     1) ? deh_location(&deh[i + 1]) : 0;
			prev = (i != 0) ? deh_location(&deh[i - 1]) : 0;

			अगर (prev && prev <= deh_location(&deh[i]))
				reiserfs_error(sb_from_bi(bi), "vs-10240",
					       "directory item (%h) "
					       "corrupted (prev %a, "
					       "cur(%d) %a)",
					       ih, deh + i - 1, i, deh + i);
			अगर (next && next >= deh_location(&deh[i]))
				reiserfs_error(sb_from_bi(bi), "vs-10250",
					       "directory item (%h) "
					       "corrupted (cur(%d) %a, "
					       "next %a)",
					       ih, i, deh + i, deh + i + 1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

पूर्ण
