<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 *
 * Trivial changes by Alan Cox to हटाओ EHASHCOLLISION क्रम compatibility
 *
 * Trivial Changes:
 * Rights granted to Hans Reiser to redistribute under other terms providing
 * he accepts all liability including but not limited to patent, fitness
 * क्रम purpose, and direct or indirect claims arising from failure to perक्रमm.
 *
 * NO WARRANTY
 */

#समावेश <linux/समय.स>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश "reiserfs.h"
#समावेश "acl.h"
#समावेश "xattr.h"
#समावेश <linux/quotaops.h>

#घोषणा INC_सूची_INODE_NLINK(i) अगर (i->i_nlink != 1) अणु inc_nlink(i); अगर (i->i_nlink >= REISERFS_LINK_MAX) set_nlink(i, 1); पूर्ण
#घोषणा DEC_सूची_INODE_NLINK(i) अगर (i->i_nlink != 1) drop_nlink(i);

/*
 * directory item contains array of entry headers. This perक्रमms
 * binary search through that array
 */
अटल पूर्णांक bin_search_in_dir_item(काष्ठा reiserfs_dir_entry *de, loff_t off)
अणु
	काष्ठा item_head *ih = de->de_ih;
	काष्ठा reiserfs_de_head *deh = de->de_deh;
	पूर्णांक rbound, lbound, j;

	lbound = 0;
	rbound = ih_entry_count(ih) - 1;

	क्रम (j = (rbound + lbound) / 2; lbound <= rbound;
	     j = (rbound + lbound) / 2) अणु
		अगर (off < deh_offset(deh + j)) अणु
			rbound = j - 1;
			जारी;
		पूर्ण
		अगर (off > deh_offset(deh + j)) अणु
			lbound = j + 1;
			जारी;
		पूर्ण
		/* this is not name found, but matched third key component */
		de->de_entry_num = j;
		वापस NAME_FOUND;
	पूर्ण

	de->de_entry_num = lbound;
	वापस NAME_NOT_FOUND;
पूर्ण

/*
 * comment?  maybe something like set de to poपूर्णांक to what the path poपूर्णांकs to?
 */
अटल अंतरभूत व्योम set_de_item_location(काष्ठा reiserfs_dir_entry *de,
					काष्ठा treepath *path)
अणु
	de->de_bh = get_last_bh(path);
	de->de_ih = tp_item_head(path);
	de->de_deh = B_I_DEH(de->de_bh, de->de_ih);
	de->de_item_num = PATH_LAST_POSITION(path);
पूर्ण

/*
 * de_bh, de_ih, de_deh (poपूर्णांकs to first element of array), de_item_num is set
 */
अंतरभूत व्योम set_de_name_and_namelen(काष्ठा reiserfs_dir_entry *de)
अणु
	काष्ठा reiserfs_de_head *deh = de->de_deh + de->de_entry_num;

	BUG_ON(de->de_entry_num >= ih_entry_count(de->de_ih));

	de->de_entrylen = entry_length(de->de_bh, de->de_ih, de->de_entry_num);
	de->de_namelen = de->de_entrylen - (de_with_sd(deh) ? SD_SIZE : 0);
	de->de_name = ih_item_body(de->de_bh, de->de_ih) + deh_location(deh);
	अगर (de->de_name[de->de_namelen - 1] == 0)
		de->de_namelen = म_माप(de->de_name);
पूर्ण

/* what entry poपूर्णांकs to */
अटल अंतरभूत व्योम set_de_object_key(काष्ठा reiserfs_dir_entry *de)
अणु
	BUG_ON(de->de_entry_num >= ih_entry_count(de->de_ih));
	de->de_dir_id = deh_dir_id(&de->de_deh[de->de_entry_num]);
	de->de_objectid = deh_objectid(&de->de_deh[de->de_entry_num]);
पूर्ण

अटल अंतरभूत व्योम store_de_entry_key(काष्ठा reiserfs_dir_entry *de)
अणु
	काष्ठा reiserfs_de_head *deh = de->de_deh + de->de_entry_num;

	BUG_ON(de->de_entry_num >= ih_entry_count(de->de_ih));

	/* store key of the found entry */
	de->de_entry_key.version = KEY_FORMAT_3_5;
	de->de_entry_key.on_disk_key.k_dir_id =
	    le32_to_cpu(de->de_ih->ih_key.k_dir_id);
	de->de_entry_key.on_disk_key.k_objectid =
	    le32_to_cpu(de->de_ih->ih_key.k_objectid);
	set_cpu_key_k_offset(&de->de_entry_key, deh_offset(deh));
	set_cpu_key_k_type(&de->de_entry_key, TYPE_सूचीENTRY);
पूर्ण

/*
 * We assign a key to each directory item, and place multiple entries in a
 * single directory item.  A directory item has a key equal to the key of
 * the first directory entry in it.

 * This function first calls search_by_key, then, अगर item whose first entry
 * matches is not found it looks क्रम the entry inside directory item found
 * by search_by_key. Fills the path to the entry, and to the entry position
 * in the item
 */
/* The function is NOT SCHEDULE-SAFE! */
पूर्णांक search_by_entry_key(काष्ठा super_block *sb, स्थिर काष्ठा cpu_key *key,
			काष्ठा treepath *path, काष्ठा reiserfs_dir_entry *de)
अणु
	पूर्णांक retval;

	retval = search_item(sb, key, path);
	चयन (retval) अणु
	हाल ITEM_NOT_FOUND:
		अगर (!PATH_LAST_POSITION(path)) अणु
			reiserfs_error(sb, "vs-7000", "search_by_key "
				       "returned item position == 0");
			pathrअन्यथा(path);
			वापस IO_ERROR;
		पूर्ण
		PATH_LAST_POSITION(path)--;

	हाल ITEM_FOUND:
		अवरोध;

	हाल IO_ERROR:
		वापस retval;

	शेष:
		pathrअन्यथा(path);
		reiserfs_error(sb, "vs-7002", "no path to here");
		वापस IO_ERROR;
	पूर्ण

	set_de_item_location(de, path);

#अगर_घोषित CONFIG_REISERFS_CHECK
	अगर (!is_direntry_le_ih(de->de_ih) ||
	    COMP_SHORT_KEYS(&de->de_ih->ih_key, key)) अणु
		prपूर्णांक_block(de->de_bh, 0, -1, -1);
		reiserfs_panic(sb, "vs-7005", "found item %h is not directory "
			       "item or does not belong to the same directory "
			       "as key %K", de->de_ih, key);
	पूर्ण
#पूर्ण_अगर				/* CONFIG_REISERFS_CHECK */

	/*
	 * binary search in directory item by third component of the
	 * key. sets de->de_entry_num of de
	 */
	retval = bin_search_in_dir_item(de, cpu_key_k_offset(key));
	path->pos_in_item = de->de_entry_num;
	अगर (retval != NAME_NOT_FOUND) अणु
		/*
		 * ugly, but नाम needs de_bh, de_deh, de_name,
		 * de_namelen, de_objectid set
		 */
		set_de_name_and_namelen(de);
		set_de_object_key(de);
	पूर्ण
	वापस retval;
पूर्ण

/* Keyed 32-bit hash function using TEA in a Davis-Meyer function */

/*
 * The third component is hashed, and you can choose from more than
 * one hash function.  Per directory hashes are not yet implemented
 * but are thought about. This function should be moved to hashes.c
 * Jedi, please करो so.  -Hans
 */
अटल __u32 get_third_component(काष्ठा super_block *s,
				 स्थिर अक्षर *name, पूर्णांक len)
अणु
	__u32 res;

	अगर (!len || (len == 1 && name[0] == '.'))
		वापस DOT_OFFSET;
	अगर (len == 2 && name[0] == '.' && name[1] == '.')
		वापस DOT_DOT_OFFSET;

	res = REISERFS_SB(s)->s_hash_function(name, len);

	/* take bits from 7-th to 30-th including both bounds */
	res = GET_HASH_VALUE(res);
	अगर (res == 0)
		/*
		 * needed to have no names beक्रमe "." and ".." those have hash
		 * value == 0 and generation conters 1 and 2 accordingly
		 */
		res = 128;
	वापस res + MAX_GENERATION_NUMBER;
पूर्ण

अटल पूर्णांक reiserfs_match(काष्ठा reiserfs_dir_entry *de,
			  स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	पूर्णांक retval = NAME_NOT_FOUND;

	अगर ((namelen == de->de_namelen) &&
	    !स_भेद(de->de_name, name, de->de_namelen))
		retval =
		    (de_visible(de->de_deh + de->de_entry_num) ? NAME_FOUND :
		     NAME_FOUND_INVISIBLE);

	वापस retval;
पूर्ण

/* de's de_bh, de_ih, de_deh, de_item_num, de_entry_num are set alपढ़ोy */

/* used when hash collisions exist */

अटल पूर्णांक linear_search_in_dir_item(काष्ठा cpu_key *key,
				     काष्ठा reiserfs_dir_entry *de,
				     स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	काष्ठा reiserfs_de_head *deh = de->de_deh;
	पूर्णांक retval;
	पूर्णांक i;

	i = de->de_entry_num;

	अगर (i == ih_entry_count(de->de_ih) ||
	    GET_HASH_VALUE(deh_offset(deh + i)) !=
	    GET_HASH_VALUE(cpu_key_k_offset(key))) अणु
		i--;
	पूर्ण

	RFALSE(de->de_deh != B_I_DEH(de->de_bh, de->de_ih),
	       "vs-7010: array of entry headers not found");

	deh += i;

	क्रम (; i >= 0; i--, deh--) अणु
		/* hash value करोes not match, no need to check whole name */
		अगर (GET_HASH_VALUE(deh_offset(deh)) !=
		    GET_HASH_VALUE(cpu_key_k_offset(key))) अणु
			वापस NAME_NOT_FOUND;
		पूर्ण

		/* mark that this generation number is used */
		अगर (de->de_gen_number_bit_string)
			set_bit(GET_GENERATION_NUMBER(deh_offset(deh)),
				de->de_gen_number_bit_string);

		/* calculate poपूर्णांकer to name and namelen */
		de->de_entry_num = i;
		set_de_name_and_namelen(de);

		/*
		 * de's de_name, de_namelen, de_recordlen are set.
		 * Fill the rest.
		 */
		अगर ((retval =
		     reiserfs_match(de, name, namelen)) != NAME_NOT_FOUND) अणु

			/* key of poपूर्णांकed object */
			set_de_object_key(de);

			store_de_entry_key(de);

			/* retval can be NAME_FOUND or NAME_FOUND_INVISIBLE */
			वापस retval;
		पूर्ण
	पूर्ण

	अगर (GET_GENERATION_NUMBER(le_ih_k_offset(de->de_ih)) == 0)
		/*
		 * we have reached left most entry in the node. In common we
		 * have to go to the left neighbor, but अगर generation counter
		 * is 0 alपढ़ोy, we know क्रम sure, that there is no name with
		 * the same hash value
		 */
		/*
		 * FIXME: this work correctly only because hash value can not
		 *  be 0. Btw, in हाल of Yura's hash it is probably possible,
		 * so, this is a bug
		 */
		वापस NAME_NOT_FOUND;

	RFALSE(de->de_item_num,
	       "vs-7015: two diritems of the same directory in one node?");

	वापस GOTO_PREVIOUS_ITEM;
पूर्ण

/*
 * may वापस NAME_FOUND, NAME_FOUND_INVISIBLE, NAME_NOT_FOUND
 * FIXME: should add something like IOERROR
 */
अटल पूर्णांक reiserfs_find_entry(काष्ठा inode *dir, स्थिर अक्षर *name, पूर्णांक namelen,
			       काष्ठा treepath *path_to_entry,
			       काष्ठा reiserfs_dir_entry *de)
अणु
	काष्ठा cpu_key key_to_search;
	पूर्णांक retval;

	अगर (namelen > REISERFS_MAX_NAME(dir->i_sb->s_blocksize))
		वापस NAME_NOT_FOUND;

	/* we will search क्रम this key in the tree */
	make_cpu_key(&key_to_search, dir,
		     get_third_component(dir->i_sb, name, namelen),
		     TYPE_सूचीENTRY, 3);

	जबतक (1) अणु
		retval =
		    search_by_entry_key(dir->i_sb, &key_to_search,
					path_to_entry, de);
		अगर (retval == IO_ERROR) अणु
			reiserfs_error(dir->i_sb, "zam-7001", "io error");
			वापस IO_ERROR;
		पूर्ण

		/* compare names क्रम all entries having given hash value */
		retval =
		    linear_search_in_dir_item(&key_to_search, de, name,
					      namelen);
		/*
		 * there is no need to scan directory anymore.
		 * Given entry found or करोes not exist
		 */
		अगर (retval != GOTO_PREVIOUS_ITEM) अणु
			path_to_entry->pos_in_item = de->de_entry_num;
			वापस retval;
		पूर्ण

		/*
		 * there is left neighboring item of this directory
		 * and given entry can be there
		 */
		set_cpu_key_k_offset(&key_to_search,
				     le_ih_k_offset(de->de_ih) - 1);
		pathrअन्यथा(path_to_entry);

	पूर्ण			/* जबतक (1) */
पूर्ण

अटल काष्ठा dentry *reiserfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				      अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode = शून्य;
	काष्ठा reiserfs_dir_entry de;
	INITIALIZE_PATH(path_to_entry);

	अगर (REISERFS_MAX_NAME(dir->i_sb->s_blocksize) < dentry->d_name.len)
		वापस ERR_PTR(-ENAMETOOLONG);

	reiserfs_ग_लिखो_lock(dir->i_sb);

	de.de_gen_number_bit_string = शून्य;
	retval =
	    reiserfs_find_entry(dir, dentry->d_name.name, dentry->d_name.len,
				&path_to_entry, &de);
	pathrअन्यथा(&path_to_entry);
	अगर (retval == NAME_FOUND) अणु
		inode = reiserfs_iget(dir->i_sb,
				      (काष्ठा cpu_key *)&de.de_dir_id);
		अगर (!inode || IS_ERR(inode)) अणु
			reiserfs_ग_लिखो_unlock(dir->i_sb);
			वापस ERR_PTR(-EACCES);
		पूर्ण

		/*
		 * Propagate the निजी flag so we know we're
		 * in the priv tree.  Also clear IOP_XATTR
		 * since we करोn't have xattrs on xattr files.
		 */
		अगर (IS_PRIVATE(dir)) अणु
			inode->i_flags |= S_PRIVATE;
			inode->i_opflags &= ~IOP_XATTR;
		पूर्ण
	पूर्ण
	reiserfs_ग_लिखो_unlock(dir->i_sb);
	अगर (retval == IO_ERROR) अणु
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस d_splice_alias(inode, dentry);
पूर्ण

/*
 * looks up the dentry of the parent directory क्रम child.
 * taken from ext2_get_parent
 */
काष्ठा dentry *reiserfs_get_parent(काष्ठा dentry *child)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode = शून्य;
	काष्ठा reiserfs_dir_entry de;
	INITIALIZE_PATH(path_to_entry);
	काष्ठा inode *dir = d_inode(child);

	अगर (dir->i_nlink == 0) अणु
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	de.de_gen_number_bit_string = शून्य;

	reiserfs_ग_लिखो_lock(dir->i_sb);
	retval = reiserfs_find_entry(dir, "..", 2, &path_to_entry, &de);
	pathrअन्यथा(&path_to_entry);
	अगर (retval != NAME_FOUND) अणु
		reiserfs_ग_लिखो_unlock(dir->i_sb);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	inode = reiserfs_iget(dir->i_sb, (काष्ठा cpu_key *)&de.de_dir_id);
	reiserfs_ग_लिखो_unlock(dir->i_sb);

	वापस d_obtain_alias(inode);
पूर्ण

/* add entry to the directory (entry can be hidden).

insert definition of when hidden directories are used here -Hans

 Does not mark dir   inode dirty, करो it after successesfull call to it */

अटल पूर्णांक reiserfs_add_entry(काष्ठा reiserfs_transaction_handle *th,
			      काष्ठा inode *dir, स्थिर अक्षर *name, पूर्णांक namelen,
			      काष्ठा inode *inode, पूर्णांक visible)
अणु
	काष्ठा cpu_key entry_key;
	काष्ठा reiserfs_de_head *deh;
	INITIALIZE_PATH(path);
	काष्ठा reiserfs_dir_entry de;
	DECLARE_BITMAP(bit_string, MAX_GENERATION_NUMBER + 1);
	पूर्णांक gen_number;

	/*
	 * 48 bytes now and we aव्योम kदो_स्मृति अगर we
	 * create file with लघु name
	 */
	अक्षर small_buf[32 + DEH_SIZE];

	अक्षर *buffer;
	पूर्णांक buflen, paste_size;
	पूर्णांक retval;

	BUG_ON(!th->t_trans_id);

	/* cannot allow items to be added पूर्णांकo a busy deleted directory */
	अगर (!namelen)
		वापस -EINVAL;

	अगर (namelen > REISERFS_MAX_NAME(dir->i_sb->s_blocksize))
		वापस -ENAMETOOLONG;

	/* each entry has unique key. compose it */
	make_cpu_key(&entry_key, dir,
		     get_third_component(dir->i_sb, name, namelen),
		     TYPE_सूचीENTRY, 3);

	/* get memory क्रम composing the entry */
	buflen = DEH_SIZE + ROUND_UP(namelen);
	अगर (buflen > माप(small_buf)) अणु
		buffer = kदो_स्मृति(buflen, GFP_NOFS);
		अगर (!buffer)
			वापस -ENOMEM;
	पूर्ण अन्यथा
		buffer = small_buf;

	paste_size =
	    (get_inode_sd_version(dir) ==
	     STAT_DATA_V1) ? (DEH_SIZE + namelen) : buflen;

	/*
	 * fill buffer : directory entry head, name[, dir objectid | ,
	 * stat data | ,stat data, dir objectid ]
	 */
	deh = (काष्ठा reiserfs_de_head *)buffer;
	deh->deh_location = 0;	/* JDM Endian safe अगर 0 */
	put_deh_offset(deh, cpu_key_k_offset(&entry_key));
	deh->deh_state = 0;	/* JDM Endian safe अगर 0 */
	/* put key (ino analog) to de */

	/* safe: k_dir_id is le */
	deh->deh_dir_id = INODE_PKEY(inode)->k_dir_id;
	/* safe: k_objectid is le */
	deh->deh_objectid = INODE_PKEY(inode)->k_objectid;

	/* copy name */
	स_नकल((अक्षर *)(deh + 1), name, namelen);
	/* padd by 0s to the 4 byte boundary */
	padd_item((अक्षर *)(deh + 1), ROUND_UP(namelen), namelen);

	/*
	 * entry is पढ़ोy to be pasted पूर्णांकo tree, set 'visibility'
	 * and 'stat data in entry' attributes
	 */
	mark_de_without_sd(deh);
	visible ? mark_de_visible(deh) : mark_de_hidden(deh);

	/* find the proper place क्रम the new entry */
	स_रखो(bit_string, 0, माप(bit_string));
	de.de_gen_number_bit_string = bit_string;
	retval = reiserfs_find_entry(dir, name, namelen, &path, &de);
	अगर (retval != NAME_NOT_FOUND) अणु
		अगर (buffer != small_buf)
			kमुक्त(buffer);
		pathrअन्यथा(&path);

		अगर (retval == IO_ERROR) अणु
			वापस -EIO;
		पूर्ण

		अगर (retval != NAME_FOUND) अणु
			reiserfs_error(dir->i_sb, "zam-7002",
				       "reiserfs_find_entry() returned "
				       "unexpected value (%d)", retval);
		पूर्ण

		वापस -EEXIST;
	पूर्ण

	gen_number =
	    find_first_zero_bit(bit_string,
				MAX_GENERATION_NUMBER + 1);
	अगर (gen_number > MAX_GENERATION_NUMBER) अणु
		/* there is no मुक्त generation number */
		reiserfs_warning(dir->i_sb, "reiserfs-7010",
				 "Congratulations! we have got hash function "
				 "screwed up");
		अगर (buffer != small_buf)
			kमुक्त(buffer);
		pathrअन्यथा(&path);
		वापस -EBUSY;
	पूर्ण
	/* adjust offset of directory enrty */
	put_deh_offset(deh, SET_GENERATION_NUMBER(deh_offset(deh), gen_number));
	set_cpu_key_k_offset(&entry_key, deh_offset(deh));

	/* update max-hash-collisions counter in reiserfs_sb_info */
	PROC_INFO_MAX(th->t_super, max_hash_collisions, gen_number);

	/* we need to re-search क्रम the insertion poपूर्णांक */
	अगर (gen_number != 0) अणु
		अगर (search_by_entry_key(dir->i_sb, &entry_key, &path, &de) !=
		    NAME_NOT_FOUND) अणु
			reiserfs_warning(dir->i_sb, "vs-7032",
					 "entry with this key (%K) already "
					 "exists", &entry_key);

			अगर (buffer != small_buf)
				kमुक्त(buffer);
			pathrअन्यथा(&path);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* perक्रमm the insertion of the entry that we have prepared */
	retval =
	    reiserfs_paste_पूर्णांकo_item(th, &path, &entry_key, dir, buffer,
				     paste_size);
	अगर (buffer != small_buf)
		kमुक्त(buffer);
	अगर (retval) अणु
		reiserfs_check_path(&path);
		वापस retval;
	पूर्ण

	dir->i_size += paste_size;
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	अगर (!S_ISसूची(inode->i_mode) && visible)
		/* reiserfs_सूची_गढ़ो or reiserfs_नाम will करो that by itself */
		reiserfs_update_sd(th, dir);

	reiserfs_check_path(&path);
	वापस 0;
पूर्ण

/*
 * quota utility function, call अगर you've had to पात after calling
 * new_inode_init, and have not called reiserfs_new_inode yet.
 * This should only be called on inodes that करो not have stat data
 * inserted पूर्णांकo the tree yet.
 */
अटल पूर्णांक drop_new_inode(काष्ठा inode *inode)
अणु
	dquot_drop(inode);
	make_bad_inode(inode);
	inode->i_flags |= S_NOQUOTA;
	iput(inode);
	वापस 0;
पूर्ण

/*
 * utility function that करोes setup क्रम reiserfs_new_inode.
 * dquot_initialize needs lots of credits so it's better to have it
 * outside of a transaction, so we had to pull some bits of
 * reiserfs_new_inode out पूर्णांकo this func.
 */
अटल पूर्णांक new_inode_init(काष्ठा inode *inode, काष्ठा inode *dir, umode_t mode)
अणु
	/*
	 * Make inode invalid - just in हाल we are going to drop it beक्रमe
	 * the initialization happens
	 */
	INODE_PKEY(inode)->k_objectid = 0;

	/*
	 * the quota init calls have to know who to अक्षरge the quota to, so
	 * we have to set uid and gid here
	 */
	inode_init_owner(&init_user_ns, inode, dir, mode);
	वापस dquot_initialize(inode);
पूर्ण

अटल पूर्णांक reiserfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			   काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode;
	/*
	 * We need blocks क्रम transaction + (user+group)*(quotas
	 * क्रम new inode + update of quota क्रम directory owner)
	 */
	पूर्णांक jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 2 +
	    2 * (REISERFS_QUOTA_INIT_BLOCKS(dir->i_sb) +
		 REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb));
	काष्ठा reiserfs_transaction_handle th;
	काष्ठा reiserfs_security_handle security;

	retval = dquot_initialize(dir);
	अगर (retval)
		वापस retval;

	अगर (!(inode = new_inode(dir->i_sb))) अणु
		वापस -ENOMEM;
	पूर्ण
	retval = new_inode_init(inode, dir, mode);
	अगर (retval) अणु
		drop_new_inode(inode);
		वापस retval;
	पूर्ण

	jbegin_count += reiserfs_cache_शेष_acl(dir);
	retval = reiserfs_security_init(dir, inode, &dentry->d_name, &security);
	अगर (retval < 0) अणु
		drop_new_inode(inode);
		वापस retval;
	पूर्ण
	jbegin_count += retval;
	reiserfs_ग_लिखो_lock(dir->i_sb);

	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	अगर (retval) अणु
		drop_new_inode(inode);
		जाओ out_failed;
	पूर्ण

	retval =
	    reiserfs_new_inode(&th, dir, mode, शून्य, 0 /*i_size */ , dentry,
			       inode, &security);
	अगर (retval)
		जाओ out_failed;

	inode->i_op = &reiserfs_file_inode_operations;
	inode->i_fop = &reiserfs_file_operations;
	inode->i_mapping->a_ops = &reiserfs_address_space_operations;

	retval =
	    reiserfs_add_entry(&th, dir, dentry->d_name.name,
			       dentry->d_name.len, inode, 1 /*visible */ );
	अगर (retval) अणु
		पूर्णांक err;
		drop_nlink(inode);
		reiserfs_update_sd(&th, inode);
		err = journal_end(&th);
		अगर (err)
			retval = err;
		unlock_new_inode(inode);
		iput(inode);
		जाओ out_failed;
	पूर्ण
	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	d_instantiate_new(dentry, inode);
	retval = journal_end(&th);

out_failed:
	reiserfs_ग_लिखो_unlock(dir->i_sb);
	वापस retval;
पूर्ण

अटल पूर्णांक reiserfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			  काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode;
	काष्ठा reiserfs_transaction_handle th;
	काष्ठा reiserfs_security_handle security;
	/*
	 * We need blocks क्रम transaction + (user+group)*(quotas
	 * क्रम new inode + update of quota क्रम directory owner)
	 */
	पूर्णांक jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 +
	    2 * (REISERFS_QUOTA_INIT_BLOCKS(dir->i_sb) +
		 REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb));

	retval = dquot_initialize(dir);
	अगर (retval)
		वापस retval;

	अगर (!(inode = new_inode(dir->i_sb))) अणु
		वापस -ENOMEM;
	पूर्ण
	retval = new_inode_init(inode, dir, mode);
	अगर (retval) अणु
		drop_new_inode(inode);
		वापस retval;
	पूर्ण

	jbegin_count += reiserfs_cache_शेष_acl(dir);
	retval = reiserfs_security_init(dir, inode, &dentry->d_name, &security);
	अगर (retval < 0) अणु
		drop_new_inode(inode);
		वापस retval;
	पूर्ण
	jbegin_count += retval;
	reiserfs_ग_लिखो_lock(dir->i_sb);

	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	अगर (retval) अणु
		drop_new_inode(inode);
		जाओ out_failed;
	पूर्ण

	retval =
	    reiserfs_new_inode(&th, dir, mode, शून्य, 0 /*i_size */ , dentry,
			       inode, &security);
	अगर (retval) अणु
		जाओ out_failed;
	पूर्ण

	inode->i_op = &reiserfs_special_inode_operations;
	init_special_inode(inode, inode->i_mode, rdev);

	/* FIXME: needed क्रम block and अक्षर devices only */
	reiserfs_update_sd(&th, inode);

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	retval =
	    reiserfs_add_entry(&th, dir, dentry->d_name.name,
			       dentry->d_name.len, inode, 1 /*visible */ );
	अगर (retval) अणु
		पूर्णांक err;
		drop_nlink(inode);
		reiserfs_update_sd(&th, inode);
		err = journal_end(&th);
		अगर (err)
			retval = err;
		unlock_new_inode(inode);
		iput(inode);
		जाओ out_failed;
	पूर्ण

	d_instantiate_new(dentry, inode);
	retval = journal_end(&th);

out_failed:
	reiserfs_ग_लिखो_unlock(dir->i_sb);
	वापस retval;
पूर्ण

अटल पूर्णांक reiserfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			  काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode;
	काष्ठा reiserfs_transaction_handle th;
	काष्ठा reiserfs_security_handle security;
	/*
	 * We need blocks क्रम transaction + (user+group)*(quotas
	 * क्रम new inode + update of quota क्रम directory owner)
	 */
	पूर्णांक jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 +
	    2 * (REISERFS_QUOTA_INIT_BLOCKS(dir->i_sb) +
		 REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb));

	retval = dquot_initialize(dir);
	अगर (retval)
		वापस retval;

#अगर_घोषित DISPLACE_NEW_PACKING_LOCALITIES
	/*
	 * set flag that new packing locality created and new blocks
	 * क्रम the content of that directory are not displaced yet
	 */
	REISERFS_I(dir)->new_packing_locality = 1;
#पूर्ण_अगर
	mode = S_IFसूची | mode;
	अगर (!(inode = new_inode(dir->i_sb))) अणु
		वापस -ENOMEM;
	पूर्ण
	retval = new_inode_init(inode, dir, mode);
	अगर (retval) अणु
		drop_new_inode(inode);
		वापस retval;
	पूर्ण

	jbegin_count += reiserfs_cache_शेष_acl(dir);
	retval = reiserfs_security_init(dir, inode, &dentry->d_name, &security);
	अगर (retval < 0) अणु
		drop_new_inode(inode);
		वापस retval;
	पूर्ण
	jbegin_count += retval;
	reiserfs_ग_लिखो_lock(dir->i_sb);

	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	अगर (retval) अणु
		drop_new_inode(inode);
		जाओ out_failed;
	पूर्ण

	/*
	 * inc the link count now, so another ग_लिखोr करोesn't overflow
	 * it जबतक we sleep later on.
	 */
	INC_सूची_INODE_NLINK(dir)

	retval = reiserfs_new_inode(&th, dir, mode, शून्य /*symlink */,
				    old_क्रमmat_only(dir->i_sb) ?
				    EMPTY_सूची_SIZE_V1 : EMPTY_सूची_SIZE,
				    dentry, inode, &security);
	अगर (retval) अणु
		DEC_सूची_INODE_NLINK(dir)
		जाओ out_failed;
	पूर्ण

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	inode->i_op = &reiserfs_dir_inode_operations;
	inode->i_fop = &reiserfs_dir_operations;

	/* note, _this_ add_entry will not update dir's stat data */
	retval =
	    reiserfs_add_entry(&th, dir, dentry->d_name.name,
			       dentry->d_name.len, inode, 1 /*visible */ );
	अगर (retval) अणु
		पूर्णांक err;
		clear_nlink(inode);
		DEC_सूची_INODE_NLINK(dir);
		reiserfs_update_sd(&th, inode);
		err = journal_end(&th);
		अगर (err)
			retval = err;
		unlock_new_inode(inode);
		iput(inode);
		जाओ out_failed;
	पूर्ण
	/* the above add_entry did not update dir's stat data */
	reiserfs_update_sd(&th, dir);

	d_instantiate_new(dentry, inode);
	retval = journal_end(&th);
out_failed:
	reiserfs_ग_लिखो_unlock(dir->i_sb);
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक reiserfs_empty_dir(काष्ठा inode *inode)
अणु
	/*
	 * we can cheat because an old क्रमmat dir cannot have
	 * EMPTY_सूची_SIZE, and a new क्रमmat dir cannot have
	 * EMPTY_सूची_SIZE_V1.  So, अगर the inode is either size,
	 * regardless of disk क्रमmat version, the directory is empty.
	 */
	अगर (inode->i_size != EMPTY_सूची_SIZE &&
	    inode->i_size != EMPTY_सूची_SIZE_V1) अणु
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक reiserfs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक retval, err;
	काष्ठा inode *inode;
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक jbegin_count;
	INITIALIZE_PATH(path);
	काष्ठा reiserfs_dir_entry de;

	/*
	 * we will be करोing 2 balancings and update 2 stat data, we
	 * change quotas of the owner of the directory and of the owner
	 * of the parent directory.  The quota काष्ठाure is possibly
	 * deleted only on last iput => outside of this transaction
	 */
	jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 2 + 2 +
	    4 * REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb);

	retval = dquot_initialize(dir);
	अगर (retval)
		वापस retval;

	reiserfs_ग_लिखो_lock(dir->i_sb);
	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	अगर (retval)
		जाओ out_सूची_हटाओ;

	de.de_gen_number_bit_string = शून्य;
	अगर ((retval =
	     reiserfs_find_entry(dir, dentry->d_name.name, dentry->d_name.len,
				 &path, &de)) == NAME_NOT_FOUND) अणु
		retval = -ENOENT;
		जाओ end_सूची_हटाओ;
	पूर्ण अन्यथा अगर (retval == IO_ERROR) अणु
		retval = -EIO;
		जाओ end_सूची_हटाओ;
	पूर्ण

	inode = d_inode(dentry);

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	अगर (de.de_objectid != inode->i_ino) अणु
		/*
		 * FIXME: compare key of an object and a key found in the entry
		 */
		retval = -EIO;
		जाओ end_सूची_हटाओ;
	पूर्ण
	अगर (!reiserfs_empty_dir(inode)) अणु
		retval = -ENOTEMPTY;
		जाओ end_सूची_हटाओ;
	पूर्ण

	/* cut entry from dir directory */
	retval = reiserfs_cut_from_item(&th, &path, &de.de_entry_key,
					dir, शून्य,	/* page */
					0 /*new file size - not used here */ );
	अगर (retval < 0)
		जाओ end_सूची_हटाओ;

	अगर (inode->i_nlink != 2 && inode->i_nlink != 1)
		reiserfs_error(inode->i_sb, "reiserfs-7040",
			       "empty directory has nlink != 2 (%d)",
			       inode->i_nlink);

	clear_nlink(inode);
	inode->i_स_समय = dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	reiserfs_update_sd(&th, inode);

	DEC_सूची_INODE_NLINK(dir)
	dir->i_size -= (DEH_SIZE + de.de_entrylen);
	reiserfs_update_sd(&th, dir);

	/* prevent empty directory from getting lost */
	add_save_link(&th, inode, 0 /* not truncate */ );

	retval = journal_end(&th);
	reiserfs_check_path(&path);
out_सूची_हटाओ:
	reiserfs_ग_लिखो_unlock(dir->i_sb);
	वापस retval;

end_सूची_हटाओ:
	/*
	 * we must release path, because we did not call
	 * reiserfs_cut_from_item, or reiserfs_cut_from_item करोes not
	 * release path अगर operation was not complete
	 */
	pathrअन्यथा(&path);
	err = journal_end(&th);
	reiserfs_ग_लिखो_unlock(dir->i_sb);
	वापस err ? err : retval;
पूर्ण

अटल पूर्णांक reiserfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक retval, err;
	काष्ठा inode *inode;
	काष्ठा reiserfs_dir_entry de;
	INITIALIZE_PATH(path);
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक jbegin_count;
	अचिन्हित दीर्घ savelink;

	retval = dquot_initialize(dir);
	अगर (retval)
		वापस retval;

	inode = d_inode(dentry);

	/*
	 * in this transaction we can be करोing at max two balancings and
	 * update two stat datas, we change quotas of the owner of the
	 * directory and of the owner of the parent directory. The quota
	 * काष्ठाure is possibly deleted only on iput => outside of
	 * this transaction
	 */
	jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 2 + 2 +
	    4 * REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb);

	reiserfs_ग_लिखो_lock(dir->i_sb);
	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	अगर (retval)
		जाओ out_unlink;

	de.de_gen_number_bit_string = शून्य;
	अगर ((retval =
	     reiserfs_find_entry(dir, dentry->d_name.name, dentry->d_name.len,
				 &path, &de)) == NAME_NOT_FOUND) अणु
		retval = -ENOENT;
		जाओ end_unlink;
	पूर्ण अन्यथा अगर (retval == IO_ERROR) अणु
		retval = -EIO;
		जाओ end_unlink;
	पूर्ण

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	अगर (de.de_objectid != inode->i_ino) अणु
		/*
		 * FIXME: compare key of an object and a key found in the entry
		 */
		retval = -EIO;
		जाओ end_unlink;
	पूर्ण

	अगर (!inode->i_nlink) अणु
		reiserfs_warning(inode->i_sb, "reiserfs-7042",
				 "deleting nonexistent file (%lu), %d",
				 inode->i_ino, inode->i_nlink);
		set_nlink(inode, 1);
	पूर्ण

	drop_nlink(inode);

	/*
	 * we schedule beक्रमe करोing the add_save_link call, save the link
	 * count so we करोn't race
	 */
	savelink = inode->i_nlink;

	retval =
	    reiserfs_cut_from_item(&th, &path, &de.de_entry_key, dir, शून्य,
				   0);
	अगर (retval < 0) अणु
		inc_nlink(inode);
		जाओ end_unlink;
	पूर्ण
	inode->i_स_समय = current_समय(inode);
	reiserfs_update_sd(&th, inode);

	dir->i_size -= (de.de_entrylen + DEH_SIZE);
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	reiserfs_update_sd(&th, dir);

	अगर (!savelink)
		/* prevent file from getting lost */
		add_save_link(&th, inode, 0 /* not truncate */ );

	retval = journal_end(&th);
	reiserfs_check_path(&path);
	reiserfs_ग_लिखो_unlock(dir->i_sb);
	वापस retval;

end_unlink:
	pathrअन्यथा(&path);
	err = journal_end(&th);
	reiserfs_check_path(&path);
	अगर (err)
		retval = err;
out_unlink:
	reiserfs_ग_लिखो_unlock(dir->i_sb);
	वापस retval;
पूर्ण

अटल पूर्णांक reiserfs_symlink(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *parent_dir, काष्ठा dentry *dentry,
			    स्थिर अक्षर *symname)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode;
	अक्षर *name;
	पूर्णांक item_len;
	काष्ठा reiserfs_transaction_handle th;
	काष्ठा reiserfs_security_handle security;
	पूर्णांक mode = S_IFLNK | S_IRWXUGO;
	/*
	 * We need blocks क्रम transaction + (user+group)*(quotas क्रम
	 * new inode + update of quota क्रम directory owner)
	 */
	पूर्णांक jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 +
	    2 * (REISERFS_QUOTA_INIT_BLOCKS(parent_dir->i_sb) +
		 REISERFS_QUOTA_TRANS_BLOCKS(parent_dir->i_sb));

	retval = dquot_initialize(parent_dir);
	अगर (retval)
		वापस retval;

	अगर (!(inode = new_inode(parent_dir->i_sb))) अणु
		वापस -ENOMEM;
	पूर्ण
	retval = new_inode_init(inode, parent_dir, mode);
	अगर (retval) अणु
		drop_new_inode(inode);
		वापस retval;
	पूर्ण

	retval = reiserfs_security_init(parent_dir, inode, &dentry->d_name,
					&security);
	अगर (retval < 0) अणु
		drop_new_inode(inode);
		वापस retval;
	पूर्ण
	jbegin_count += retval;

	reiserfs_ग_लिखो_lock(parent_dir->i_sb);
	item_len = ROUND_UP(म_माप(symname));
	अगर (item_len > MAX_सूचीECT_ITEM_LEN(parent_dir->i_sb->s_blocksize)) अणु
		retval = -ENAMETOOLONG;
		drop_new_inode(inode);
		जाओ out_failed;
	पूर्ण

	name = kदो_स्मृति(item_len, GFP_NOFS);
	अगर (!name) अणु
		drop_new_inode(inode);
		retval = -ENOMEM;
		जाओ out_failed;
	पूर्ण
	स_नकल(name, symname, म_माप(symname));
	padd_item(name, item_len, म_माप(symname));

	retval = journal_begin(&th, parent_dir->i_sb, jbegin_count);
	अगर (retval) अणु
		drop_new_inode(inode);
		kमुक्त(name);
		जाओ out_failed;
	पूर्ण

	retval =
	    reiserfs_new_inode(&th, parent_dir, mode, name, म_माप(symname),
			       dentry, inode, &security);
	kमुक्त(name);
	अगर (retval) अणु		/* reiserfs_new_inode iमाला_दो क्रम us */
		जाओ out_failed;
	पूर्ण

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(parent_dir);

	inode->i_op = &reiserfs_symlink_inode_operations;
	inode_nohighmem(inode);
	inode->i_mapping->a_ops = &reiserfs_address_space_operations;

	retval = reiserfs_add_entry(&th, parent_dir, dentry->d_name.name,
				    dentry->d_name.len, inode, 1 /*visible */ );
	अगर (retval) अणु
		पूर्णांक err;
		drop_nlink(inode);
		reiserfs_update_sd(&th, inode);
		err = journal_end(&th);
		अगर (err)
			retval = err;
		unlock_new_inode(inode);
		iput(inode);
		जाओ out_failed;
	पूर्ण

	d_instantiate_new(dentry, inode);
	retval = journal_end(&th);
out_failed:
	reiserfs_ग_लिखो_unlock(parent_dir->i_sb);
	वापस retval;
पूर्ण

अटल पूर्णांक reiserfs_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
			 काष्ठा dentry *dentry)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode = d_inode(old_dentry);
	काष्ठा reiserfs_transaction_handle th;
	/*
	 * We need blocks क्रम transaction + update of quotas क्रम
	 * the owners of the directory
	 */
	पूर्णांक jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 +
	    2 * REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb);

	retval = dquot_initialize(dir);
	अगर (retval)
		वापस retval;

	reiserfs_ग_लिखो_lock(dir->i_sb);
	अगर (inode->i_nlink >= REISERFS_LINK_MAX) अणु
		/* FIXME: sd_nlink is 32 bit क्रम new files */
		reiserfs_ग_लिखो_unlock(dir->i_sb);
		वापस -EMLINK;
	पूर्ण

	/* inc beक्रमe scheduling so reiserfs_unlink knows we are here */
	inc_nlink(inode);

	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	अगर (retval) अणु
		drop_nlink(inode);
		reiserfs_ग_लिखो_unlock(dir->i_sb);
		वापस retval;
	पूर्ण

	/* create new entry */
	retval =
	    reiserfs_add_entry(&th, dir, dentry->d_name.name,
			       dentry->d_name.len, inode, 1 /*visible */ );

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	अगर (retval) अणु
		पूर्णांक err;
		drop_nlink(inode);
		err = journal_end(&th);
		reiserfs_ग_लिखो_unlock(dir->i_sb);
		वापस err ? err : retval;
	पूर्ण

	inode->i_स_समय = current_समय(inode);
	reiserfs_update_sd(&th, inode);

	ihold(inode);
	d_instantiate(dentry, inode);
	retval = journal_end(&th);
	reiserfs_ग_लिखो_unlock(dir->i_sb);
	वापस retval;
पूर्ण

/* de contains inक्रमmation poपूर्णांकing to an entry which */
अटल पूर्णांक de_still_valid(स्थिर अक्षर *name, पूर्णांक len,
			  काष्ठा reiserfs_dir_entry *de)
अणु
	काष्ठा reiserfs_dir_entry पंचांगp = *de;

	/* recalculate poपूर्णांकer to name and name length */
	set_de_name_and_namelen(&पंचांगp);
	/* FIXME: could check more */
	अगर (पंचांगp.de_namelen != len || स_भेद(name, de->de_name, len))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक entry_poपूर्णांकs_to_object(स्थिर अक्षर *name, पूर्णांक len,
				  काष्ठा reiserfs_dir_entry *de,
				  काष्ठा inode *inode)
अणु
	अगर (!de_still_valid(name, len, de))
		वापस 0;

	अगर (inode) अणु
		अगर (!de_visible(de->de_deh + de->de_entry_num))
			reiserfs_panic(inode->i_sb, "vs-7042",
				       "entry must be visible");
		वापस (de->de_objectid == inode->i_ino) ? 1 : 0;
	पूर्ण

	/* this must be added hidden entry */
	अगर (de_visible(de->de_deh + de->de_entry_num))
		reiserfs_panic(शून्य, "vs-7043", "entry must be visible");

	वापस 1;
पूर्ण

/* sets key of objectid the entry has to poपूर्णांक to */
अटल व्योम set_ino_in_dir_entry(काष्ठा reiserfs_dir_entry *de,
				 काष्ठा reiserfs_key *key)
अणु
	/* JDM These operations are endian safe - both are le */
	de->de_deh[de->de_entry_num].deh_dir_id = key->k_dir_id;
	de->de_deh[de->de_entry_num].deh_objectid = key->k_objectid;
पूर्ण

/*
 * process, that is going to call fix_nodes/करो_balance must hold only
 * one path. If it holds 2 or more, it can get पूर्णांकo endless रुकोing in
 * get_empty_nodes or its clones
 */
अटल पूर्णांक reiserfs_नाम(काष्ठा user_namespace *mnt_userns,
			   काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			   काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			   अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक retval;
	INITIALIZE_PATH(old_entry_path);
	INITIALIZE_PATH(new_entry_path);
	INITIALIZE_PATH(करोt_करोt_entry_path);
	काष्ठा item_head new_entry_ih, old_entry_ih, करोt_करोt_ih;
	काष्ठा reiserfs_dir_entry old_de, new_de, करोt_करोt_de;
	काष्ठा inode *old_inode, *new_dentry_inode;
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक jbegin_count;
	umode_t old_inode_mode;
	अचिन्हित दीर्घ savelink = 1;
	काष्ठा बारpec64 स_समय;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	/*
	 * three balancings: (1) old name removal, (2) new name insertion
	 * and (3) maybe "save" link insertion
	 * stat data updates: (1) old directory,
	 * (2) new directory and (3) maybe old object stat data (when it is
	 * directory) and (4) maybe stat data of object to which new entry
	 * poपूर्णांकed initially and (5) maybe block containing ".." of
	 * नामd directory
	 * quota updates: two parent directories
	 */
	jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 + 5 +
	    4 * REISERFS_QUOTA_TRANS_BLOCKS(old_dir->i_sb);

	retval = dquot_initialize(old_dir);
	अगर (retval)
		वापस retval;
	retval = dquot_initialize(new_dir);
	अगर (retval)
		वापस retval;

	old_inode = d_inode(old_dentry);
	new_dentry_inode = d_inode(new_dentry);

	/*
	 * make sure that oldname still exists and poपूर्णांकs to an object we
	 * are going to नाम
	 */
	old_de.de_gen_number_bit_string = शून्य;
	reiserfs_ग_लिखो_lock(old_dir->i_sb);
	retval =
	    reiserfs_find_entry(old_dir, old_dentry->d_name.name,
				old_dentry->d_name.len, &old_entry_path,
				&old_de);
	pathrअन्यथा(&old_entry_path);
	अगर (retval == IO_ERROR) अणु
		reiserfs_ग_लिखो_unlock(old_dir->i_sb);
		वापस -EIO;
	पूर्ण

	अगर (retval != NAME_FOUND || old_de.de_objectid != old_inode->i_ino) अणु
		reiserfs_ग_लिखो_unlock(old_dir->i_sb);
		वापस -ENOENT;
	पूर्ण

	old_inode_mode = old_inode->i_mode;
	अगर (S_ISसूची(old_inode_mode)) अणु
		/*
		 * make sure that directory being नामd has correct ".."
		 * and that its new parent directory has not too many links
		 * alपढ़ोy
		 */
		अगर (new_dentry_inode) अणु
			अगर (!reiserfs_empty_dir(new_dentry_inode)) अणु
				reiserfs_ग_लिखो_unlock(old_dir->i_sb);
				वापस -ENOTEMPTY;
			पूर्ण
		पूर्ण

		/*
		 * directory is नामd, its parent directory will be changed,
		 * so find ".." entry
		 */
		करोt_करोt_de.de_gen_number_bit_string = शून्य;
		retval =
		    reiserfs_find_entry(old_inode, "..", 2, &करोt_करोt_entry_path,
					&करोt_करोt_de);
		pathrअन्यथा(&करोt_करोt_entry_path);
		अगर (retval != NAME_FOUND) अणु
			reiserfs_ग_लिखो_unlock(old_dir->i_sb);
			वापस -EIO;
		पूर्ण

		/* inode number of .. must equal old_dir->i_ino */
		अगर (करोt_करोt_de.de_objectid != old_dir->i_ino) अणु
			reiserfs_ग_लिखो_unlock(old_dir->i_sb);
			वापस -EIO;
		पूर्ण
	पूर्ण

	retval = journal_begin(&th, old_dir->i_sb, jbegin_count);
	अगर (retval) अणु
		reiserfs_ग_लिखो_unlock(old_dir->i_sb);
		वापस retval;
	पूर्ण

	/* add new entry (or find the existing one) */
	retval =
	    reiserfs_add_entry(&th, new_dir, new_dentry->d_name.name,
			       new_dentry->d_name.len, old_inode, 0);
	अगर (retval == -EEXIST) अणु
		अगर (!new_dentry_inode) अणु
			reiserfs_panic(old_dir->i_sb, "vs-7050",
				       "new entry is found, new inode == 0");
		पूर्ण
	पूर्ण अन्यथा अगर (retval) अणु
		पूर्णांक err = journal_end(&th);
		reiserfs_ग_लिखो_unlock(old_dir->i_sb);
		वापस err ? err : retval;
	पूर्ण

	reiserfs_update_inode_transaction(old_dir);
	reiserfs_update_inode_transaction(new_dir);

	/*
	 * this makes it so an fsync on an खोलो fd क्रम the old name will
	 * commit the नाम operation
	 */
	reiserfs_update_inode_transaction(old_inode);

	अगर (new_dentry_inode)
		reiserfs_update_inode_transaction(new_dentry_inode);

	जबतक (1) अणु
		/*
		 * look क्रम old name using corresponding entry key
		 * (found by reiserfs_find_entry)
		 */
		अगर ((retval =
		     search_by_entry_key(new_dir->i_sb, &old_de.de_entry_key,
					 &old_entry_path,
					 &old_de)) != NAME_FOUND) अणु
			pathrअन्यथा(&old_entry_path);
			journal_end(&th);
			reiserfs_ग_लिखो_unlock(old_dir->i_sb);
			वापस -EIO;
		पूर्ण

		copy_item_head(&old_entry_ih, tp_item_head(&old_entry_path));

		reiserfs_prepare_क्रम_journal(old_inode->i_sb, old_de.de_bh, 1);

		/* look क्रम new name by reiserfs_find_entry */
		new_de.de_gen_number_bit_string = शून्य;
		retval =
		    reiserfs_find_entry(new_dir, new_dentry->d_name.name,
					new_dentry->d_name.len, &new_entry_path,
					&new_de);
		/*
		 * reiserfs_add_entry should not वापस IO_ERROR,
		 * because it is called with essentially same parameters from
		 * reiserfs_add_entry above, and we'll catch any i/o errors
		 * beक्रमe we get here.
		 */
		अगर (retval != NAME_FOUND_INVISIBLE && retval != NAME_FOUND) अणु
			pathrअन्यथा(&new_entry_path);
			pathrअन्यथा(&old_entry_path);
			journal_end(&th);
			reiserfs_ग_लिखो_unlock(old_dir->i_sb);
			वापस -EIO;
		पूर्ण

		copy_item_head(&new_entry_ih, tp_item_head(&new_entry_path));

		reiserfs_prepare_क्रम_journal(old_inode->i_sb, new_de.de_bh, 1);

		अगर (S_ISसूची(old_inode->i_mode)) अणु
			अगर ((retval =
			     search_by_entry_key(new_dir->i_sb,
						 &करोt_करोt_de.de_entry_key,
						 &करोt_करोt_entry_path,
						 &करोt_करोt_de)) != NAME_FOUND) अणु
				pathrअन्यथा(&करोt_करोt_entry_path);
				pathrअन्यथा(&new_entry_path);
				pathrअन्यथा(&old_entry_path);
				journal_end(&th);
				reiserfs_ग_लिखो_unlock(old_dir->i_sb);
				वापस -EIO;
			पूर्ण
			copy_item_head(&करोt_करोt_ih,
				       tp_item_head(&करोt_करोt_entry_path));
			/* node containing ".." माला_लो पूर्णांकo transaction */
			reiserfs_prepare_क्रम_journal(old_inode->i_sb,
						     करोt_करोt_de.de_bh, 1);
		पूर्ण
		/*
		 * we should check seals here, not करो
		 * this stuff, yes? Then, having
		 * gathered everything पूर्णांकo RAM we
		 * should lock the buffers, yes?  -Hans
		 */
		/*
		 * probably.  our नाम needs to hold more
		 * than one path at once.  The seals would
		 * have to be written to deal with multi-path
		 * issues -chris
		 */
		/*
		 * sanity checking beक्रमe करोing the नाम - aव्योम races many
		 * of the above checks could have scheduled.  We have to be
		 * sure our items haven't been shअगरted by another process.
		 */
		अगर (item_moved(&new_entry_ih, &new_entry_path) ||
		    !entry_poपूर्णांकs_to_object(new_dentry->d_name.name,
					    new_dentry->d_name.len,
					    &new_de, new_dentry_inode) ||
		    item_moved(&old_entry_ih, &old_entry_path) ||
		    !entry_poपूर्णांकs_to_object(old_dentry->d_name.name,
					    old_dentry->d_name.len,
					    &old_de, old_inode)) अणु
			reiserfs_restore_prepared_buffer(old_inode->i_sb,
							 new_de.de_bh);
			reiserfs_restore_prepared_buffer(old_inode->i_sb,
							 old_de.de_bh);
			अगर (S_ISसूची(old_inode_mode))
				reiserfs_restore_prepared_buffer(old_inode->
								 i_sb,
								 करोt_करोt_de.
								 de_bh);
			जारी;
		पूर्ण
		अगर (S_ISसूची(old_inode_mode)) अणु
			अगर (item_moved(&करोt_करोt_ih, &करोt_करोt_entry_path) ||
			    !entry_poपूर्णांकs_to_object("..", 2, &करोt_करोt_de,
						    old_dir)) अणु
				reiserfs_restore_prepared_buffer(old_inode->
								 i_sb,
								 old_de.de_bh);
				reiserfs_restore_prepared_buffer(old_inode->
								 i_sb,
								 new_de.de_bh);
				reiserfs_restore_prepared_buffer(old_inode->
								 i_sb,
								 करोt_करोt_de.
								 de_bh);
				जारी;
			पूर्ण
		पूर्ण

		RFALSE(S_ISसूची(old_inode_mode) &&
		       !buffer_journal_prepared(करोt_करोt_de.de_bh), "");

		अवरोध;
	पूर्ण

	/*
	 * ok, all the changes can be करोne in one fell swoop when we
	 * have claimed all the buffers needed.
	 */

	mark_de_visible(new_de.de_deh + new_de.de_entry_num);
	set_ino_in_dir_entry(&new_de, INODE_PKEY(old_inode));
	journal_mark_dirty(&th, new_de.de_bh);

	mark_de_hidden(old_de.de_deh + old_de.de_entry_num);
	journal_mark_dirty(&th, old_de.de_bh);
	स_समय = current_समय(old_dir);
	old_dir->i_स_समय = old_dir->i_mसमय = स_समय;
	new_dir->i_स_समय = new_dir->i_mसमय = स_समय;
	/*
	 * thanks to Alex Adriaanse <alex_a@caltech.edu> क्रम patch
	 * which adds स_समय update of नामd object
	 */
	old_inode->i_स_समय = स_समय;

	अगर (new_dentry_inode) अणु
		/* adjust link number of the victim */
		अगर (S_ISसूची(new_dentry_inode->i_mode)) अणु
			clear_nlink(new_dentry_inode);
		पूर्ण अन्यथा अणु
			drop_nlink(new_dentry_inode);
		पूर्ण
		new_dentry_inode->i_स_समय = स_समय;
		savelink = new_dentry_inode->i_nlink;
	पूर्ण

	अगर (S_ISसूची(old_inode_mode)) अणु
		/* adjust ".." of नामd directory */
		set_ino_in_dir_entry(&करोt_करोt_de, INODE_PKEY(new_dir));
		journal_mark_dirty(&th, करोt_करोt_de.de_bh);

		/*
		 * there (in new_dir) was no directory, so it got new link
		 * (".."  of नामd directory)
		 */
		अगर (!new_dentry_inode)
			INC_सूची_INODE_NLINK(new_dir);

		/* old directory lost one link - ".. " of नामd directory */
		DEC_सूची_INODE_NLINK(old_dir);
	पूर्ण
	/*
	 * looks like in 2.3.99pre3 brअन्यथा is atomic.
	 * so we can use pathrअन्यथा
	 */
	pathrअन्यथा(&new_entry_path);
	pathrअन्यथा(&करोt_करोt_entry_path);

	/*
	 * FIXME: this reiserfs_cut_from_item's वापस value may screw up
	 * anybody, but it will panic अगर will not be able to find the
	 * entry. This needs one more clean up
	 */
	अगर (reiserfs_cut_from_item
	    (&th, &old_entry_path, &old_de.de_entry_key, old_dir, शून्य,
	     0) < 0)
		reiserfs_error(old_dir->i_sb, "vs-7060",
			       "couldn't not cut old name. Fsck later?");

	old_dir->i_size -= DEH_SIZE + old_de.de_entrylen;

	reiserfs_update_sd(&th, old_dir);
	reiserfs_update_sd(&th, new_dir);
	reiserfs_update_sd(&th, old_inode);

	अगर (new_dentry_inode) अणु
		अगर (savelink == 0)
			add_save_link(&th, new_dentry_inode,
				      0 /* not truncate */ );
		reiserfs_update_sd(&th, new_dentry_inode);
	पूर्ण

	retval = journal_end(&th);
	reiserfs_ग_लिखो_unlock(old_dir->i_sb);
	वापस retval;
पूर्ण

/* directories can handle most operations...  */
स्थिर काष्ठा inode_operations reiserfs_dir_inode_operations = अणु
	.create = reiserfs_create,
	.lookup = reiserfs_lookup,
	.link = reiserfs_link,
	.unlink = reiserfs_unlink,
	.symlink = reiserfs_symlink,
	.सूची_गढ़ो = reiserfs_सूची_गढ़ो,
	.सूची_हटाओ = reiserfs_सूची_हटाओ,
	.mknod = reiserfs_mknod,
	.नाम = reiserfs_नाम,
	.setattr = reiserfs_setattr,
	.listxattr = reiserfs_listxattr,
	.permission = reiserfs_permission,
	.get_acl = reiserfs_get_acl,
	.set_acl = reiserfs_set_acl,
	.fileattr_get = reiserfs_fileattr_get,
	.fileattr_set = reiserfs_fileattr_set,
पूर्ण;

/*
 * symlink operations.. same as page_symlink_inode_operations, with xattr
 * stuff added
 */
स्थिर काष्ठा inode_operations reiserfs_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.setattr = reiserfs_setattr,
	.listxattr = reiserfs_listxattr,
	.permission = reiserfs_permission,
पूर्ण;

/*
 * special file operations.. just xattr/acl stuff
 */
स्थिर काष्ठा inode_operations reiserfs_special_inode_operations = अणु
	.setattr = reiserfs_setattr,
	.listxattr = reiserfs_listxattr,
	.permission = reiserfs_permission,
	.get_acl = reiserfs_get_acl,
	.set_acl = reiserfs_set_acl,
पूर्ण;
