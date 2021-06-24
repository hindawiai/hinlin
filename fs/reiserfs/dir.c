<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश "reiserfs.h"
#समावेश <linux/स्थिति.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

बाह्य स्थिर काष्ठा reiserfs_key MIN_KEY;

अटल पूर्णांक reiserfs_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);
अटल पूर्णांक reiserfs_dir_fsync(काष्ठा file *filp, loff_t start, loff_t end,
			      पूर्णांक datasync);

स्थिर काष्ठा file_operations reiserfs_dir_operations = अणु
	.llseek = generic_file_llseek,
	.पढ़ो = generic_पढ़ो_dir,
	.iterate_shared = reiserfs_सूची_पढ़ो,
	.fsync = reiserfs_dir_fsync,
	.unlocked_ioctl = reiserfs_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = reiserfs_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक reiserfs_dir_fsync(काष्ठा file *filp, loff_t start, loff_t end,
			      पूर्णांक datasync)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक err;

	err = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (err)
		वापस err;

	inode_lock(inode);
	reiserfs_ग_लिखो_lock(inode->i_sb);
	err = reiserfs_commit_क्रम_inode(inode);
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	inode_unlock(inode);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

#घोषणा store_ih(where,what) copy_item_head (where, what)

अटल अंतरभूत bool is_privroot_deh(काष्ठा inode *dir, काष्ठा reiserfs_de_head *deh)
अणु
	काष्ठा dentry *privroot = REISERFS_SB(dir->i_sb)->priv_root;
	वापस (d_really_is_positive(privroot) &&
	        deh->deh_objectid == INODE_PKEY(d_inode(privroot))->k_objectid);
पूर्ण

पूर्णांक reiserfs_सूची_पढ़ो_inode(काष्ठा inode *inode, काष्ठा dir_context *ctx)
अणु

	/* key of current position in the directory (key of directory entry) */
	काष्ठा cpu_key pos_key;

	INITIALIZE_PATH(path_to_entry);
	काष्ठा buffer_head *bh;
	पूर्णांक item_num, entry_num;
	स्थिर काष्ठा reiserfs_key *rkey;
	काष्ठा item_head *ih, पंचांगp_ih;
	पूर्णांक search_res;
	अक्षर *local_buf;
	loff_t next_pos;
	अक्षर small_buf[32];	/* aव्योम kदो_स्मृति अगर we can */
	काष्ठा reiserfs_dir_entry de;
	पूर्णांक ret = 0;
	पूर्णांक depth;

	reiserfs_ग_लिखो_lock(inode->i_sb);

	reiserfs_check_lock_depth(inode->i_sb, "readdir");

	/*
	 * क्रमm key क्रम search the next directory entry using
	 * f_pos field of file काष्ठाure
	 */
	make_cpu_key(&pos_key, inode, ctx->pos ?: DOT_OFFSET, TYPE_सूचीENTRY, 3);
	next_pos = cpu_key_k_offset(&pos_key);

	path_to_entry.पढ़ोa = PATH_READA;
	जबतक (1) अणु
research:
		/*
		 * search the directory item, containing entry with
		 * specअगरied key
		 */
		search_res =
		    search_by_entry_key(inode->i_sb, &pos_key, &path_to_entry,
					&de);
		अगर (search_res == IO_ERROR) अणु
			/*
			 * FIXME: we could just skip part of directory
			 * which could not be पढ़ो
			 */
			ret = -EIO;
			जाओ out;
		पूर्ण
		entry_num = de.de_entry_num;
		bh = de.de_bh;
		item_num = de.de_item_num;
		ih = de.de_ih;
		store_ih(&पंचांगp_ih, ih);

		/* we must have found item, that is item of this directory, */
		RFALSE(COMP_SHORT_KEYS(&ih->ih_key, &pos_key),
		       "vs-9000: found item %h does not match to dir we readdir %K",
		       ih, &pos_key);
		RFALSE(item_num > B_NR_ITEMS(bh) - 1,
		       "vs-9005 item_num == %d, item amount == %d",
		       item_num, B_NR_ITEMS(bh));

		/*
		 * and entry must be not more than number of entries
		 * in the item
		 */
		RFALSE(ih_entry_count(ih) < entry_num,
		       "vs-9010: entry number is too big %d (%d)",
		       entry_num, ih_entry_count(ih));

		/*
		 * go through all entries in the directory item beginning
		 * from the entry, that has been found
		 */
		अगर (search_res == POSITION_FOUND
		    || entry_num < ih_entry_count(ih)) अणु
			काष्ठा reiserfs_de_head *deh =
			    B_I_DEH(bh, ih) + entry_num;

			क्रम (; entry_num < ih_entry_count(ih);
			     entry_num++, deh++) अणु
				पूर्णांक d_reclen;
				अक्षर *d_name;
				ino_t d_ino;
				loff_t cur_pos = deh_offset(deh);

				/* it is hidden entry */
				अगर (!de_visible(deh))
					जारी;
				d_reclen = entry_length(bh, ih, entry_num);
				d_name = B_I_DEH_ENTRY_खाता_NAME(bh, ih, deh);

				अगर (d_reclen <= 0 ||
				    d_name + d_reclen > bh->b_data + bh->b_size) अणु
					/*
					 * There is corrupted data in entry,
					 * We'd better stop here
					 */
					pathrअन्यथा(&path_to_entry);
					ret = -EIO;
					जाओ out;
				पूर्ण

				अगर (!d_name[d_reclen - 1])
					d_reclen = म_माप(d_name);

				/* too big to send back to VFS */
				अगर (d_reclen >
				    REISERFS_MAX_NAME(inode->i_sb->
						      s_blocksize)) अणु
					जारी;
				पूर्ण

				/* Ignore the .reiserfs_priv entry */
				अगर (is_privroot_deh(inode, deh))
					जारी;

				ctx->pos = deh_offset(deh);
				d_ino = deh_objectid(deh);
				अगर (d_reclen <= 32) अणु
					local_buf = small_buf;
				पूर्ण अन्यथा अणु
					local_buf = kदो_स्मृति(d_reclen,
							    GFP_NOFS);
					अगर (!local_buf) अणु
						pathrअन्यथा(&path_to_entry);
						ret = -ENOMEM;
						जाओ out;
					पूर्ण
					अगर (item_moved(&पंचांगp_ih, &path_to_entry)) अणु
						kमुक्त(local_buf);
						जाओ research;
					पूर्ण
				पूर्ण

				/*
				 * Note, that we copy name to user space via
				 * temporary buffer (local_buf) because
				 * filldir will block अगर user space buffer is
				 * swapped out. At that समय entry can move to
				 * somewhere अन्यथा
				 */
				स_नकल(local_buf, d_name, d_reclen);

				/*
				 * Since filldir might sleep, we can release
				 * the ग_लिखो lock here क्रम other रुकोers
				 */
				depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
				अगर (!dir_emit
				    (ctx, local_buf, d_reclen, d_ino,
				     DT_UNKNOWN)) अणु
					reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);
					अगर (local_buf != small_buf) अणु
						kमुक्त(local_buf);
					पूर्ण
					जाओ end;
				पूर्ण
				reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);
				अगर (local_buf != small_buf) अणु
					kमुक्त(local_buf);
				पूर्ण

				/* deh_offset(deh) may be invalid now. */
				next_pos = cur_pos + 1;

				अगर (item_moved(&पंचांगp_ih, &path_to_entry)) अणु
					set_cpu_key_k_offset(&pos_key,
							     next_pos);
					जाओ research;
				पूर्ण
			पूर्ण	/* क्रम */
		पूर्ण

		/* end of directory has been reached */
		अगर (item_num != B_NR_ITEMS(bh) - 1)
			जाओ end;

		/*
		 * item we went through is last item of node. Using right
		 * delimiting key check is it directory end
		 */
		rkey = get_rkey(&path_to_entry, inode->i_sb);
		अगर (!comp_le_keys(rkey, &MIN_KEY)) अणु
			/*
			 * set pos_key to key, that is the smallest and greater
			 * that key of the last entry in the item
			 */
			set_cpu_key_k_offset(&pos_key, next_pos);
			जारी;
		पूर्ण

		/* end of directory has been reached */
		अगर (COMP_SHORT_KEYS(rkey, &pos_key)) अणु
			जाओ end;
		पूर्ण

		/* directory जारीs in the right neighboring block */
		set_cpu_key_k_offset(&pos_key,
				     le_key_k_offset(KEY_FORMAT_3_5, rkey));

	पूर्ण			/* जबतक */

end:
	ctx->pos = next_pos;
	pathrअन्यथा(&path_to_entry);
	reiserfs_check_path(&path_to_entry);
out:
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	वापस ret;
पूर्ण

अटल पूर्णांक reiserfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	वापस reiserfs_सूची_पढ़ो_inode(file_inode(file), ctx);
पूर्ण

/*
 * compose directory item containing "." and ".." entries (entries are
 * not aligned to 4 byte boundary)
 */
व्योम make_empty_dir_item_v1(अक्षर *body, __le32 dirid, __le32 objid,
			    __le32 par_dirid, __le32 par_objid)
अणु
	काष्ठा reiserfs_de_head *करोt, *करोtकरोt;

	स_रखो(body, 0, EMPTY_सूची_SIZE_V1);
	करोt = (काष्ठा reiserfs_de_head *)body;
	करोtकरोt = करोt + 1;

	/* direntry header of "." */
	put_deh_offset(करोt, DOT_OFFSET);
	/* these two are from make_le_item_head, and are LE */
	करोt->deh_dir_id = dirid;
	करोt->deh_objectid = objid;
	करोt->deh_state = 0;	/* Endian safe अगर 0 */
	put_deh_location(करोt, EMPTY_सूची_SIZE_V1 - म_माप("."));
	mark_de_visible(करोt);

	/* direntry header of ".." */
	put_deh_offset(करोtकरोt, DOT_DOT_OFFSET);
	/* key of ".." क्रम the root directory */
	/* these two are from the inode, and are LE */
	करोtकरोt->deh_dir_id = par_dirid;
	करोtकरोt->deh_objectid = par_objid;
	करोtकरोt->deh_state = 0;	/* Endian safe अगर 0 */
	put_deh_location(करोtकरोt, deh_location(करोt) - म_माप(".."));
	mark_de_visible(करोtकरोt);

	/* copy ".." and "." */
	स_नकल(body + deh_location(करोt), ".", 1);
	स_नकल(body + deh_location(करोtकरोt), "..", 2);
पूर्ण

/* compose directory item containing "." and ".." entries */
व्योम make_empty_dir_item(अक्षर *body, __le32 dirid, __le32 objid,
			 __le32 par_dirid, __le32 par_objid)
अणु
	काष्ठा reiserfs_de_head *करोt, *करोtकरोt;

	स_रखो(body, 0, EMPTY_सूची_SIZE);
	करोt = (काष्ठा reiserfs_de_head *)body;
	करोtकरोt = करोt + 1;

	/* direntry header of "." */
	put_deh_offset(करोt, DOT_OFFSET);
	/* these two are from make_le_item_head, and are LE */
	करोt->deh_dir_id = dirid;
	करोt->deh_objectid = objid;
	करोt->deh_state = 0;	/* Endian safe अगर 0 */
	put_deh_location(करोt, EMPTY_सूची_SIZE - ROUND_UP(म_माप(".")));
	mark_de_visible(करोt);

	/* direntry header of ".." */
	put_deh_offset(करोtकरोt, DOT_DOT_OFFSET);
	/* key of ".." क्रम the root directory */
	/* these two are from the inode, and are LE */
	करोtकरोt->deh_dir_id = par_dirid;
	करोtकरोt->deh_objectid = par_objid;
	करोtकरोt->deh_state = 0;	/* Endian safe अगर 0 */
	put_deh_location(करोtकरोt, deh_location(करोt) - ROUND_UP(म_माप("..")));
	mark_de_visible(करोtकरोt);

	/* copy ".." and "." */
	स_नकल(body + deh_location(करोt), ".", 1);
	स_नकल(body + deh_location(करोtकरोt), "..", 2);
पूर्ण
