<शैली गुरु>
/*
 *  Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

/*
 *  Written by Anम_से_दy P. Pinchuk pap@namesys.botik.ru
 *  Programm System Institute
 *  Pereslavl-Zalessky Russia
 */

#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/bपन.स>
#समावेश "reiserfs.h"
#समावेश <linux/buffer_head.h>
#समावेश <linux/quotaops.h>

/* Does the buffer contain a disk block which is in the tree. */
अंतरभूत पूर्णांक B_IS_IN_TREE(स्थिर काष्ठा buffer_head *bh)
अणु

	RFALSE(B_LEVEL(bh) > MAX_HEIGHT,
	       "PAP-1010: block (%b) has too big level (%z)", bh, bh);

	वापस (B_LEVEL(bh) != FREE_LEVEL);
पूर्ण

/* to get item head in le क्रमm */
अंतरभूत व्योम copy_item_head(काष्ठा item_head *to,
			   स्थिर काष्ठा item_head *from)
अणु
	स_नकल(to, from, IH_SIZE);
पूर्ण

/*
 * k1 is poपूर्णांकer to on-disk काष्ठाure which is stored in little-endian
 * क्रमm. k2 is poपूर्णांकer to cpu variable. For key of items of the same
 * object this वापसs 0.
 * Returns: -1 अगर key1 < key2
 * 0 अगर key1 == key2
 * 1 अगर key1 > key2
 */
अंतरभूत पूर्णांक comp_लघु_keys(स्थिर काष्ठा reiserfs_key *le_key,
			   स्थिर काष्ठा cpu_key *cpu_key)
अणु
	__u32 n;
	n = le32_to_cpu(le_key->k_dir_id);
	अगर (n < cpu_key->on_disk_key.k_dir_id)
		वापस -1;
	अगर (n > cpu_key->on_disk_key.k_dir_id)
		वापस 1;
	n = le32_to_cpu(le_key->k_objectid);
	अगर (n < cpu_key->on_disk_key.k_objectid)
		वापस -1;
	अगर (n > cpu_key->on_disk_key.k_objectid)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * k1 is poपूर्णांकer to on-disk काष्ठाure which is stored in little-endian
 * क्रमm. k2 is poपूर्णांकer to cpu variable.
 * Compare keys using all 4 key fields.
 * Returns: -1 अगर key1 < key2 0
 * अगर key1 = key2 1 अगर key1 > key2
 */
अटल अंतरभूत पूर्णांक comp_keys(स्थिर काष्ठा reiserfs_key *le_key,
			    स्थिर काष्ठा cpu_key *cpu_key)
अणु
	पूर्णांक retval;

	retval = comp_लघु_keys(le_key, cpu_key);
	अगर (retval)
		वापस retval;
	अगर (le_key_k_offset(le_key_version(le_key), le_key) <
	    cpu_key_k_offset(cpu_key))
		वापस -1;
	अगर (le_key_k_offset(le_key_version(le_key), le_key) >
	    cpu_key_k_offset(cpu_key))
		वापस 1;

	अगर (cpu_key->key_length == 3)
		वापस 0;

	/* this part is needed only when tail conversion is in progress */
	अगर (le_key_k_type(le_key_version(le_key), le_key) <
	    cpu_key_k_type(cpu_key))
		वापस -1;

	अगर (le_key_k_type(le_key_version(le_key), le_key) >
	    cpu_key_k_type(cpu_key))
		वापस 1;

	वापस 0;
पूर्ण

अंतरभूत पूर्णांक comp_लघु_le_keys(स्थिर काष्ठा reiserfs_key *key1,
			      स्थिर काष्ठा reiserfs_key *key2)
अणु
	__u32 *k1_u32, *k2_u32;
	पूर्णांक key_length = REISERFS_SHORT_KEY_LEN;

	k1_u32 = (__u32 *) key1;
	k2_u32 = (__u32 *) key2;
	क्रम (; key_length--; ++k1_u32, ++k2_u32) अणु
		अगर (le32_to_cpu(*k1_u32) < le32_to_cpu(*k2_u32))
			वापस -1;
		अगर (le32_to_cpu(*k1_u32) > le32_to_cpu(*k2_u32))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अंतरभूत व्योम le_key2cpu_key(काष्ठा cpu_key *to, स्थिर काष्ठा reiserfs_key *from)
अणु
	पूर्णांक version;
	to->on_disk_key.k_dir_id = le32_to_cpu(from->k_dir_id);
	to->on_disk_key.k_objectid = le32_to_cpu(from->k_objectid);

	/* find out version of the key */
	version = le_key_version(from);
	to->version = version;
	to->on_disk_key.k_offset = le_key_k_offset(version, from);
	to->on_disk_key.k_type = le_key_k_type(version, from);
पूर्ण

/*
 * this करोes not say which one is bigger, it only वापसs 1 अगर keys
 * are not equal, 0 otherwise
 */
अंतरभूत पूर्णांक comp_le_keys(स्थिर काष्ठा reiserfs_key *k1,
			स्थिर काष्ठा reiserfs_key *k2)
अणु
	वापस स_भेद(k1, k2, माप(काष्ठा reiserfs_key));
पूर्ण

/**************************************************************************
 *  Binary search toolkit function                                        *
 *  Search क्रम an item in the array by the item key                       *
 *  Returns:    1 अगर found,  0 अगर not found;                              *
 *        *pos = number of the searched element अगर found, अन्यथा the        *
 *        number of the first element that is larger than key.            *
 **************************************************************************/
/*
 * For those not familiar with binary search: lbound is the lefपंचांगost item
 * that it could be, rbound the righपंचांगost item that it could be.  We examine
 * the item halfway between lbound and rbound, and that tells us either
 * that we can increase lbound, or decrease rbound, or that we have found it,
 * or अगर lbound <= rbound that there are no possible items, and we have not
 * found it. With each examination we cut the number of possible items it
 * could be by one more than half rounded करोwn, or we find it.
 */
अटल अंतरभूत पूर्णांक bin_search(स्थिर व्योम *key,	/* Key to search क्रम. */
			     स्थिर व्योम *base,	/* First item in the array. */
			     पूर्णांक num,	/* Number of items in the array. */
			     /*
			      * Item size in the array.  searched. Lest the
			      * पढ़ोer be confused, note that this is crafted
			      * as a general function, and when it is applied
			      * specअगरically to the array of item headers in a
			      * node, width is actually the item header size
			      * not the item size.
			      */
			     पूर्णांक width,
			     पूर्णांक *pos /* Number of the searched क्रम element. */
    )
अणु
	पूर्णांक rbound, lbound, j;

	क्रम (j = ((rbound = num - 1) + (lbound = 0)) / 2;
	     lbound <= rbound; j = (rbound + lbound) / 2)
		चयन (comp_keys
			((काष्ठा reiserfs_key *)((अक्षर *)base + j * width),
			 (काष्ठा cpu_key *)key)) अणु
		हाल -1:
			lbound = j + 1;
			जारी;
		हाल 1:
			rbound = j - 1;
			जारी;
		हाल 0:
			*pos = j;
			वापस ITEM_FOUND;	/* Key found in the array.  */
		पूर्ण

	/*
	 * bin_search did not find given key, it वापसs position of key,
	 * that is minimal and greater than the given one.
	 */
	*pos = lbound;
	वापस ITEM_NOT_FOUND;
पूर्ण


/* Minimal possible key. It is never in the tree. */
स्थिर काष्ठा reiserfs_key MIN_KEY = अणु 0, 0, अणुअणु0, 0पूर्ण,पूर्ण पूर्ण;

/* Maximal possible key. It is never in the tree. */
अटल स्थिर काष्ठा reiserfs_key MAX_KEY = अणु
	cpu_to_le32(0xffffffff),
	cpu_to_le32(0xffffffff),
	अणुअणुcpu_to_le32(0xffffffff),
	  cpu_to_le32(0xffffffff)पूर्ण,पूर्ण
पूर्ण;

/*
 * Get delimiting key of the buffer by looking क्रम it in the buffers in the
 * path, starting from the bottom of the path, and going upwards.  We must
 * check the path's validity at each step.  If the key is not in the path,
 * there is no delimiting key in the tree (buffer is first or last buffer
 * in tree), and in this हाल we वापस a special key, either MIN_KEY or
 * MAX_KEY.
 */
अटल अंतरभूत स्थिर काष्ठा reiserfs_key *get_lkey(स्थिर काष्ठा treepath *chk_path,
						  स्थिर काष्ठा super_block *sb)
अणु
	पूर्णांक position, path_offset = chk_path->path_length;
	काष्ठा buffer_head *parent;

	RFALSE(path_offset < FIRST_PATH_ELEMENT_OFFSET,
	       "PAP-5010: invalid offset in the path");

	/* While not higher in path than first element. */
	जबतक (path_offset-- > FIRST_PATH_ELEMENT_OFFSET) अणु

		RFALSE(!buffer_uptodate
		       (PATH_OFFSET_PBUFFER(chk_path, path_offset)),
		       "PAP-5020: parent is not uptodate");

		/* Parent at the path is not in the tree now. */
		अगर (!B_IS_IN_TREE
		    (parent =
		     PATH_OFFSET_PBUFFER(chk_path, path_offset)))
			वापस &MAX_KEY;
		/* Check whether position in the parent is correct. */
		अगर ((position =
		     PATH_OFFSET_POSITION(chk_path,
					  path_offset)) >
		    B_NR_ITEMS(parent))
			वापस &MAX_KEY;
		/* Check whether parent at the path really poपूर्णांकs to the child. */
		अगर (B_N_CHILD_NUM(parent, position) !=
		    PATH_OFFSET_PBUFFER(chk_path,
					path_offset + 1)->b_blocknr)
			वापस &MAX_KEY;
		/*
		 * Return delimiting key अगर position in the parent
		 * is not equal to zero.
		 */
		अगर (position)
			वापस पूर्णांकernal_key(parent, position - 1);
	पूर्ण
	/* Return MIN_KEY अगर we are in the root of the buffer tree. */
	अगर (PATH_OFFSET_PBUFFER(chk_path, FIRST_PATH_ELEMENT_OFFSET)->
	    b_blocknr == SB_ROOT_BLOCK(sb))
		वापस &MIN_KEY;
	वापस &MAX_KEY;
पूर्ण

/* Get delimiting key of the buffer at the path and its right neighbor. */
अंतरभूत स्थिर काष्ठा reiserfs_key *get_rkey(स्थिर काष्ठा treepath *chk_path,
					   स्थिर काष्ठा super_block *sb)
अणु
	पूर्णांक position, path_offset = chk_path->path_length;
	काष्ठा buffer_head *parent;

	RFALSE(path_offset < FIRST_PATH_ELEMENT_OFFSET,
	       "PAP-5030: invalid offset in the path");

	जबतक (path_offset-- > FIRST_PATH_ELEMENT_OFFSET) अणु

		RFALSE(!buffer_uptodate
		       (PATH_OFFSET_PBUFFER(chk_path, path_offset)),
		       "PAP-5040: parent is not uptodate");

		/* Parent at the path is not in the tree now. */
		अगर (!B_IS_IN_TREE
		    (parent =
		     PATH_OFFSET_PBUFFER(chk_path, path_offset)))
			वापस &MIN_KEY;
		/* Check whether position in the parent is correct. */
		अगर ((position =
		     PATH_OFFSET_POSITION(chk_path,
					  path_offset)) >
		    B_NR_ITEMS(parent))
			वापस &MIN_KEY;
		/*
		 * Check whether parent at the path really poपूर्णांकs
		 * to the child.
		 */
		अगर (B_N_CHILD_NUM(parent, position) !=
		    PATH_OFFSET_PBUFFER(chk_path,
					path_offset + 1)->b_blocknr)
			वापस &MIN_KEY;

		/*
		 * Return delimiting key अगर position in the parent
		 * is not the last one.
		 */
		अगर (position != B_NR_ITEMS(parent))
			वापस पूर्णांकernal_key(parent, position);
	पूर्ण

	/* Return MAX_KEY अगर we are in the root of the buffer tree. */
	अगर (PATH_OFFSET_PBUFFER(chk_path, FIRST_PATH_ELEMENT_OFFSET)->
	    b_blocknr == SB_ROOT_BLOCK(sb))
		वापस &MAX_KEY;
	वापस &MIN_KEY;
पूर्ण

/*
 * Check whether a key is contained in the tree rooted from a buffer at a path.
 * This works by looking at the left and right delimiting keys क्रम the buffer
 * in the last path_element in the path.  These delimiting keys are stored
 * at least one level above that buffer in the tree. If the buffer is the
 * first or last node in the tree order then one of the delimiting keys may
 * be असलent, and in this हाल get_lkey and get_rkey वापस a special key
 * which is MIN_KEY or MAX_KEY.
 */
अटल अंतरभूत पूर्णांक key_in_buffer(
				/* Path which should be checked. */
				काष्ठा treepath *chk_path,
				/* Key which should be checked. */
				स्थिर काष्ठा cpu_key *key,
				काष्ठा super_block *sb
    )
अणु

	RFALSE(!key || chk_path->path_length < FIRST_PATH_ELEMENT_OFFSET
	       || chk_path->path_length > MAX_HEIGHT,
	       "PAP-5050: pointer to the key(%p) is NULL or invalid path length(%d)",
	       key, chk_path->path_length);
	RFALSE(!PATH_PLAST_BUFFER(chk_path)->b_bdev,
	       "PAP-5060: device must not be NODEV");

	अगर (comp_keys(get_lkey(chk_path, sb), key) == 1)
		/* left delimiting key is bigger, that the key we look क्रम */
		वापस 0;
	/*  अगर ( comp_keys(key, get_rkey(chk_path, sb)) != -1 ) */
	अगर (comp_keys(get_rkey(chk_path, sb), key) != 1)
		/* key must be less than right delimitiing key */
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक reiserfs_check_path(काष्ठा treepath *p)
अणु
	RFALSE(p->path_length != ILLEGAL_PATH_ELEMENT_OFFSET,
	       "path not properly relsed");
	वापस 0;
पूर्ण

/*
 * Drop the reference to each buffer in a path and restore
 * dirty bits clean when preparing the buffer क्रम the log.
 * This version should only be called from fix_nodes()
 */
व्योम pathrअन्यथा_and_restore(काष्ठा super_block *sb,
			   काष्ठा treepath *search_path)
अणु
	पूर्णांक path_offset = search_path->path_length;

	RFALSE(path_offset < ILLEGAL_PATH_ELEMENT_OFFSET,
	       "clm-4000: invalid path offset");

	जबतक (path_offset > ILLEGAL_PATH_ELEMENT_OFFSET) अणु
		काष्ठा buffer_head *bh;
		bh = PATH_OFFSET_PBUFFER(search_path, path_offset--);
		reiserfs_restore_prepared_buffer(sb, bh);
		brअन्यथा(bh);
	पूर्ण
	search_path->path_length = ILLEGAL_PATH_ELEMENT_OFFSET;
पूर्ण

/* Drop the reference to each buffer in a path */
व्योम pathrअन्यथा(काष्ठा treepath *search_path)
अणु
	पूर्णांक path_offset = search_path->path_length;

	RFALSE(path_offset < ILLEGAL_PATH_ELEMENT_OFFSET,
	       "PAP-5090: invalid path offset");

	जबतक (path_offset > ILLEGAL_PATH_ELEMENT_OFFSET)
		brअन्यथा(PATH_OFFSET_PBUFFER(search_path, path_offset--));

	search_path->path_length = ILLEGAL_PATH_ELEMENT_OFFSET;
पूर्ण

अटल पूर्णांक is_leaf(अक्षर *buf, पूर्णांक blocksize, काष्ठा buffer_head *bh)
अणु
	काष्ठा block_head *blkh;
	काष्ठा item_head *ih;
	पूर्णांक used_space;
	पूर्णांक prev_location;
	पूर्णांक i;
	पूर्णांक nr;

	blkh = (काष्ठा block_head *)buf;
	अगर (blkh_level(blkh) != DISK_LEAF_NODE_LEVEL) अणु
		reiserfs_warning(शून्य, "reiserfs-5080",
				 "this should be caught earlier");
		वापस 0;
	पूर्ण

	nr = blkh_nr_item(blkh);
	अगर (nr < 1 || nr > ((blocksize - BLKH_SIZE) / (IH_SIZE + MIN_ITEM_LEN))) अणु
		/* item number is too big or too small */
		reiserfs_warning(शून्य, "reiserfs-5081",
				 "nr_item seems wrong: %z", bh);
		वापस 0;
	पूर्ण
	ih = (काष्ठा item_head *)(buf + BLKH_SIZE) + nr - 1;
	used_space = BLKH_SIZE + IH_SIZE * nr + (blocksize - ih_location(ih));

	/* मुक्त space करोes not match to calculated amount of use space */
	अगर (used_space != blocksize - blkh_मुक्त_space(blkh)) अणु
		reiserfs_warning(शून्य, "reiserfs-5082",
				 "free space seems wrong: %z", bh);
		वापस 0;
	पूर्ण
	/*
	 * FIXME: it is_leaf will hit perक्रमmance too much - we may have
	 * वापस 1 here
	 */

	/* check tables of item heads */
	ih = (काष्ठा item_head *)(buf + BLKH_SIZE);
	prev_location = blocksize;
	क्रम (i = 0; i < nr; i++, ih++) अणु
		अगर (le_ih_k_type(ih) == TYPE_ANY) अणु
			reiserfs_warning(शून्य, "reiserfs-5083",
					 "wrong item type for item %h",
					 ih);
			वापस 0;
		पूर्ण
		अगर (ih_location(ih) >= blocksize
		    || ih_location(ih) < IH_SIZE * nr) अणु
			reiserfs_warning(शून्य, "reiserfs-5084",
					 "item location seems wrong: %h",
					 ih);
			वापस 0;
		पूर्ण
		अगर (ih_item_len(ih) < 1
		    || ih_item_len(ih) > MAX_ITEM_LEN(blocksize)) अणु
			reiserfs_warning(शून्य, "reiserfs-5085",
					 "item length seems wrong: %h",
					 ih);
			वापस 0;
		पूर्ण
		अगर (prev_location - ih_location(ih) != ih_item_len(ih)) अणु
			reiserfs_warning(शून्य, "reiserfs-5086",
					 "item location seems wrong "
					 "(second one): %h", ih);
			वापस 0;
		पूर्ण
		अगर (is_direntry_le_ih(ih) && (ih_item_len(ih) < (ih_entry_count(ih) * IH_SIZE))) अणु
			reiserfs_warning(शून्य, "reiserfs-5093",
					 "item entry count seems wrong %h",
					 ih);
			वापस 0;
		पूर्ण
		prev_location = ih_location(ih);
	पूर्ण

	/* one may imagine many more checks */
	वापस 1;
पूर्ण

/* वापसs 1 अगर buf looks like an पूर्णांकernal node, 0 otherwise */
अटल पूर्णांक is_पूर्णांकernal(अक्षर *buf, पूर्णांक blocksize, काष्ठा buffer_head *bh)
अणु
	काष्ठा block_head *blkh;
	पूर्णांक nr;
	पूर्णांक used_space;

	blkh = (काष्ठा block_head *)buf;
	nr = blkh_level(blkh);
	अगर (nr <= DISK_LEAF_NODE_LEVEL || nr > MAX_HEIGHT) अणु
		/* this level is not possible क्रम पूर्णांकernal nodes */
		reiserfs_warning(शून्य, "reiserfs-5087",
				 "this should be caught earlier");
		वापस 0;
	पूर्ण

	nr = blkh_nr_item(blkh);
	/* क्रम पूर्णांकernal which is not root we might check min number of keys */
	अगर (nr > (blocksize - BLKH_SIZE - DC_SIZE) / (KEY_SIZE + DC_SIZE)) अणु
		reiserfs_warning(शून्य, "reiserfs-5088",
				 "number of key seems wrong: %z", bh);
		वापस 0;
	पूर्ण

	used_space = BLKH_SIZE + KEY_SIZE * nr + DC_SIZE * (nr + 1);
	अगर (used_space != blocksize - blkh_मुक्त_space(blkh)) अणु
		reiserfs_warning(शून्य, "reiserfs-5089",
				 "free space seems wrong: %z", bh);
		वापस 0;
	पूर्ण

	/* one may imagine many more checks */
	वापस 1;
पूर्ण

/*
 * make sure that bh contains क्रमmatted node of reiserfs tree of
 * 'level'-th level
 */
अटल पूर्णांक is_tree_node(काष्ठा buffer_head *bh, पूर्णांक level)
अणु
	अगर (B_LEVEL(bh) != level) अणु
		reiserfs_warning(शून्य, "reiserfs-5090", "node level %d does "
				 "not match to the expected one %d",
				 B_LEVEL(bh), level);
		वापस 0;
	पूर्ण
	अगर (level == DISK_LEAF_NODE_LEVEL)
		वापस is_leaf(bh->b_data, bh->b_size, bh);

	वापस is_पूर्णांकernal(bh->b_data, bh->b_size, bh);
पूर्ण

#घोषणा SEARCH_BY_KEY_READA 16

/*
 * The function is NOT SCHEDULE-SAFE!
 * It might unlock the ग_लिखो lock अगर we needed to रुको क्रम a block
 * to be पढ़ो. Note that in this हाल it won't recover the lock to aव्योम
 * high contention resulting from too much lock requests, especially
 * the caller (search_by_key) will perक्रमm other schedule-unsafe
 * operations just after calling this function.
 *
 * @वापस depth of lock to be restored after पढ़ो completes
 */
अटल पूर्णांक search_by_key_पढ़ोa(काष्ठा super_block *s,
				काष्ठा buffer_head **bh,
				b_blocknr_t *b, पूर्णांक num)
अणु
	पूर्णांक i, j;
	पूर्णांक depth = -1;

	क्रम (i = 0; i < num; i++) अणु
		bh[i] = sb_getblk(s, b[i]);
	पूर्ण
	/*
	 * We are going to पढ़ो some blocks on which we
	 * have a reference. It's safe, though we might be
	 * पढ़ोing blocks concurrently changed अगर we release
	 * the lock. But it's still fine because we check later
	 * अगर the tree changed
	 */
	क्रम (j = 0; j < i; j++) अणु
		/*
		 * note, this needs attention अगर we are getting rid of the BKL
		 * you have to make sure the prepared bit isn't set on this
		 * buffer
		 */
		अगर (!buffer_uptodate(bh[j])) अणु
			अगर (depth == -1)
				depth = reiserfs_ग_लिखो_unlock_nested(s);
			ll_rw_block(REQ_OP_READ, REQ_RAHEAD, 1, bh + j);
		पूर्ण
		brअन्यथा(bh[j]);
	पूर्ण
	वापस depth;
पूर्ण

/*
 * This function fills up the path from the root to the leaf as it
 * descends the tree looking क्रम the key.  It uses reiserfs_bपढ़ो to
 * try to find buffers in the cache given their block number.  If it
 * करोes not find them in the cache it पढ़ोs them from disk.  For each
 * node search_by_key finds using reiserfs_bपढ़ो it then uses
 * bin_search to look through that node.  bin_search will find the
 * position of the block_number of the next node अगर it is looking
 * through an पूर्णांकernal node.  If it is looking through a leaf node
 * bin_search will find the position of the item which has key either
 * equal to given key, or which is the maximal key less than the given
 * key.  search_by_key वापसs a path that must be checked क्रम the
 * correctness of the top of the path but need not be checked क्रम the
 * correctness of the bottom of the path
 */
/*
 * search_by_key - search क्रम key (and item) in stree
 * @sb: superblock
 * @key: poपूर्णांकer to key to search क्रम
 * @search_path: Allocated and initialized काष्ठा treepath; Returned filled
 *		 on success.
 * @stop_level: How far करोwn the tree to search, Use DISK_LEAF_NODE_LEVEL to
 *		stop at leaf level.
 *
 * The function is NOT SCHEDULE-SAFE!
 */
पूर्णांक search_by_key(काष्ठा super_block *sb, स्थिर काष्ठा cpu_key *key,
		  काष्ठा treepath *search_path, पूर्णांक stop_level)
अणु
	b_blocknr_t block_number;
	पूर्णांक expected_level;
	काष्ठा buffer_head *bh;
	काष्ठा path_element *last_element;
	पूर्णांक node_level, retval;
	पूर्णांक fs_gen;
	काष्ठा buffer_head *पढ़ोa_bh[SEARCH_BY_KEY_READA];
	b_blocknr_t पढ़ोa_blocks[SEARCH_BY_KEY_READA];
	पूर्णांक पढ़ोa_count = 0;

#अगर_घोषित CONFIG_REISERFS_CHECK
	पूर्णांक repeat_counter = 0;
#पूर्ण_अगर

	PROC_INFO_INC(sb, search_by_key);

	/*
	 * As we add each node to a path we increase its count.  This means
	 * that we must be careful to release all nodes in a path beक्रमe we
	 * either discard the path काष्ठा or re-use the path काष्ठा, as we
	 * करो here.
	 */

	pathrअन्यथा(search_path);

	/*
	 * With each iteration of this loop we search through the items in the
	 * current node, and calculate the next current node(next path element)
	 * क्रम the next iteration of this loop..
	 */
	block_number = SB_ROOT_BLOCK(sb);
	expected_level = -1;
	जबतक (1) अणु

#अगर_घोषित CONFIG_REISERFS_CHECK
		अगर (!(++repeat_counter % 50000))
			reiserfs_warning(sb, "PAP-5100",
					 "%s: there were %d iterations of "
					 "while loop looking for key %K",
					 current->comm, repeat_counter,
					 key);
#पूर्ण_अगर

		/* prep path to have another element added to it. */
		last_element =
		    PATH_OFFSET_PELEMENT(search_path,
					 ++search_path->path_length);
		fs_gen = get_generation(sb);

		/*
		 * Read the next tree node, and set the last element
		 * in the path to have a poपूर्णांकer to it.
		 */
		अगर ((bh = last_element->pe_buffer =
		     sb_getblk(sb, block_number))) अणु

			/*
			 * We'll need to drop the lock अगर we encounter any
			 * buffers that need to be पढ़ो. If all of them are
			 * alपढ़ोy up to date, we करोn't need to drop the lock.
			 */
			पूर्णांक depth = -1;

			अगर (!buffer_uptodate(bh) && पढ़ोa_count > 1)
				depth = search_by_key_पढ़ोa(sb, पढ़ोa_bh,
						    पढ़ोa_blocks, पढ़ोa_count);

			अगर (!buffer_uptodate(bh) && depth == -1)
				depth = reiserfs_ग_लिखो_unlock_nested(sb);

			ll_rw_block(REQ_OP_READ, 0, 1, &bh);
			रुको_on_buffer(bh);

			अगर (depth != -1)
				reiserfs_ग_लिखो_lock_nested(sb, depth);
			अगर (!buffer_uptodate(bh))
				जाओ io_error;
		पूर्ण अन्यथा अणु
io_error:
			search_path->path_length--;
			pathrअन्यथा(search_path);
			वापस IO_ERROR;
		पूर्ण
		पढ़ोa_count = 0;
		अगर (expected_level == -1)
			expected_level = SB_TREE_HEIGHT(sb);
		expected_level--;

		/*
		 * It is possible that schedule occurred. We must check
		 * whether the key to search is still in the tree rooted
		 * from the current buffer. If not then repeat search
		 * from the root.
		 */
		अगर (fs_changed(fs_gen, sb) &&
		    (!B_IS_IN_TREE(bh) ||
		     B_LEVEL(bh) != expected_level ||
		     !key_in_buffer(search_path, key, sb))) अणु
			PROC_INFO_INC(sb, search_by_key_fs_changed);
			PROC_INFO_INC(sb, search_by_key_restarted);
			PROC_INFO_INC(sb,
				      sbk_restarted[expected_level - 1]);
			pathrअन्यथा(search_path);

			/*
			 * Get the root block number so that we can
			 * repeat the search starting from the root.
			 */
			block_number = SB_ROOT_BLOCK(sb);
			expected_level = -1;

			/* repeat search from the root */
			जारी;
		पूर्ण

		/*
		 * only check that the key is in the buffer अगर key is not
		 * equal to the MAX_KEY. Latter हाल is only possible in
		 * "finish_unfinished()" processing during mount.
		 */
		RFALSE(comp_keys(&MAX_KEY, key) &&
		       !key_in_buffer(search_path, key, sb),
		       "PAP-5130: key is not in the buffer");
#अगर_घोषित CONFIG_REISERFS_CHECK
		अगर (REISERFS_SB(sb)->cur_tb) अणु
			prपूर्णांक_cur_tb("5140");
			reiserfs_panic(sb, "PAP-5140",
				       "schedule occurred in do_balance!");
		पूर्ण
#पूर्ण_अगर

		/*
		 * make sure, that the node contents look like a node of
		 * certain level
		 */
		अगर (!is_tree_node(bh, expected_level)) अणु
			reiserfs_error(sb, "vs-5150",
				       "invalid format found in block %ld. "
				       "Fsck?", bh->b_blocknr);
			pathrअन्यथा(search_path);
			वापस IO_ERROR;
		पूर्ण

		/* ok, we have acquired next क्रमmatted node in the tree */
		node_level = B_LEVEL(bh);

		PROC_INFO_BH_STAT(sb, bh, node_level - 1);

		RFALSE(node_level < stop_level,
		       "vs-5152: tree level (%d) is less than stop level (%d)",
		       node_level, stop_level);

		retval = bin_search(key, item_head(bh, 0),
				      B_NR_ITEMS(bh),
				      (node_level ==
				       DISK_LEAF_NODE_LEVEL) ? IH_SIZE :
				      KEY_SIZE,
				      &last_element->pe_position);
		अगर (node_level == stop_level) अणु
			वापस retval;
		पूर्ण

		/* we are not in the stop level */
		/*
		 * item has been found, so we choose the poपूर्णांकer which
		 * is to the right of the found one
		 */
		अगर (retval == ITEM_FOUND)
			last_element->pe_position++;

		/*
		 * अगर item was not found we choose the position which is to
		 * the left of the found item. This requires no code,
		 * bin_search did it alपढ़ोy.
		 */

		/*
		 * So we have chosen a position in the current node which is
		 * an पूर्णांकernal node.  Now we calculate child block number by
		 * position in the node.
		 */
		block_number =
		    B_N_CHILD_NUM(bh, last_element->pe_position);

		/*
		 * अगर we are going to पढ़ो leaf nodes, try क्रम पढ़ो
		 * ahead as well
		 */
		अगर ((search_path->पढ़ोa & PATH_READA) &&
		    node_level == DISK_LEAF_NODE_LEVEL + 1) अणु
			पूर्णांक pos = last_element->pe_position;
			पूर्णांक limit = B_NR_ITEMS(bh);
			काष्ठा reiserfs_key *le_key;

			अगर (search_path->पढ़ोa & PATH_READA_BACK)
				limit = 0;
			जबतक (पढ़ोa_count < SEARCH_BY_KEY_READA) अणु
				अगर (pos == limit)
					अवरोध;
				पढ़ोa_blocks[पढ़ोa_count++] =
				    B_N_CHILD_NUM(bh, pos);
				अगर (search_path->पढ़ोa & PATH_READA_BACK)
					pos--;
				अन्यथा
					pos++;

				/*
				 * check to make sure we're in the same object
				 */
				le_key = पूर्णांकernal_key(bh, pos);
				अगर (le32_to_cpu(le_key->k_objectid) !=
				    key->on_disk_key.k_objectid) अणु
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Form the path to an item and position in this item which contains
 * file byte defined by key. If there is no such item
 * corresponding to the key, we poपूर्णांक the path to the item with
 * maximal key less than key, and *pos_in_item is set to one
 * past the last entry/byte in the item.  If searching क्रम entry in a
 * directory item, and it is not found, *pos_in_item is set to one
 * entry more than the entry with maximal key which is less than the
 * sought key.
 *
 * Note that अगर there is no entry in this same node which is one more,
 * then we poपूर्णांक to an imaginary entry.  क्रम direct items, the
 * position is in units of bytes, क्रम indirect items the position is
 * in units of blocknr entries, क्रम directory items the position is in
 * units of directory entries.
 */
/* The function is NOT SCHEDULE-SAFE! */
पूर्णांक search_क्रम_position_by_key(काष्ठा super_block *sb,
			       /* Key to search (cpu variable) */
			       स्थिर काष्ठा cpu_key *p_cpu_key,
			       /* Filled up by this function. */
			       काष्ठा treepath *search_path)
अणु
	काष्ठा item_head *p_le_ih;	/* poपूर्णांकer to on-disk काष्ठाure */
	पूर्णांक blk_size;
	loff_t item_offset, offset;
	काष्ठा reiserfs_dir_entry de;
	पूर्णांक retval;

	/* If searching क्रम directory entry. */
	अगर (is_direntry_cpu_key(p_cpu_key))
		वापस search_by_entry_key(sb, p_cpu_key, search_path,
					   &de);

	/* If not searching क्रम directory entry. */

	/* If item is found. */
	retval = search_item(sb, p_cpu_key, search_path);
	अगर (retval == IO_ERROR)
		वापस retval;
	अगर (retval == ITEM_FOUND) अणु

		RFALSE(!ih_item_len
		       (item_head
			(PATH_PLAST_BUFFER(search_path),
			 PATH_LAST_POSITION(search_path))),
		       "PAP-5165: item length equals zero");

		pos_in_item(search_path) = 0;
		वापस POSITION_FOUND;
	पूर्ण

	RFALSE(!PATH_LAST_POSITION(search_path),
	       "PAP-5170: position equals zero");

	/* Item is not found. Set path to the previous item. */
	p_le_ih =
	    item_head(PATH_PLAST_BUFFER(search_path),
			   --PATH_LAST_POSITION(search_path));
	blk_size = sb->s_blocksize;

	अगर (comp_लघु_keys(&p_le_ih->ih_key, p_cpu_key))
		वापस खाता_NOT_FOUND;

	/* FIXME: quite ugly this far */

	item_offset = le_ih_k_offset(p_le_ih);
	offset = cpu_key_k_offset(p_cpu_key);

	/* Needed byte is contained in the item poपूर्णांकed to by the path. */
	अगर (item_offset <= offset &&
	    item_offset + op_bytes_number(p_le_ih, blk_size) > offset) अणु
		pos_in_item(search_path) = offset - item_offset;
		अगर (is_indirect_le_ih(p_le_ih)) अणु
			pos_in_item(search_path) /= blk_size;
		पूर्ण
		वापस POSITION_FOUND;
	पूर्ण

	/*
	 * Needed byte is not contained in the item poपूर्णांकed to by the
	 * path. Set pos_in_item out of the item.
	 */
	अगर (is_indirect_le_ih(p_le_ih))
		pos_in_item(search_path) =
		    ih_item_len(p_le_ih) / UNFM_P_SIZE;
	अन्यथा
		pos_in_item(search_path) = ih_item_len(p_le_ih);

	वापस POSITION_NOT_FOUND;
पूर्ण

/* Compare given item and item poपूर्णांकed to by the path. */
पूर्णांक comp_items(स्थिर काष्ठा item_head *stored_ih, स्थिर काष्ठा treepath *path)
अणु
	काष्ठा buffer_head *bh = PATH_PLAST_BUFFER(path);
	काष्ठा item_head *ih;

	/* Last buffer at the path is not in the tree. */
	अगर (!B_IS_IN_TREE(bh))
		वापस 1;

	/* Last path position is invalid. */
	अगर (PATH_LAST_POSITION(path) >= B_NR_ITEMS(bh))
		वापस 1;

	/* we need only to know, whether it is the same item */
	ih = tp_item_head(path);
	वापस स_भेद(stored_ih, ih, IH_SIZE);
पूर्ण

/* prepare क्रम delete or cut of direct item */
अटल अंतरभूत पूर्णांक prepare_क्रम_direct_item(काष्ठा treepath *path,
					  काष्ठा item_head *le_ih,
					  काष्ठा inode *inode,
					  loff_t new_file_length, पूर्णांक *cut_size)
अणु
	loff_t round_len;

	अगर (new_file_length == max_reiserfs_offset(inode)) अणु
		/* item has to be deleted */
		*cut_size = -(IH_SIZE + ih_item_len(le_ih));
		वापस M_DELETE;
	पूर्ण
	/* new file माला_लो truncated */
	अगर (get_inode_item_key_version(inode) == KEY_FORMAT_3_6) अणु
		round_len = ROUND_UP(new_file_length);
		/* this was new_file_length < le_ih ... */
		अगर (round_len < le_ih_k_offset(le_ih)) अणु
			*cut_size = -(IH_SIZE + ih_item_len(le_ih));
			वापस M_DELETE;	/* Delete this item. */
		पूर्ण
		/* Calculate first position and size क्रम cutting from item. */
		pos_in_item(path) = round_len - (le_ih_k_offset(le_ih) - 1);
		*cut_size = -(ih_item_len(le_ih) - pos_in_item(path));

		वापस M_CUT;	/* Cut from this item. */
	पूर्ण

	/* old file: items may have any length */

	अगर (new_file_length < le_ih_k_offset(le_ih)) अणु
		*cut_size = -(IH_SIZE + ih_item_len(le_ih));
		वापस M_DELETE;	/* Delete this item. */
	पूर्ण

	/* Calculate first position and size क्रम cutting from item. */
	*cut_size = -(ih_item_len(le_ih) -
		      (pos_in_item(path) =
		       new_file_length + 1 - le_ih_k_offset(le_ih)));
	वापस M_CUT;		/* Cut from this item. */
पूर्ण

अटल अंतरभूत पूर्णांक prepare_क्रम_direntry_item(काष्ठा treepath *path,
					    काष्ठा item_head *le_ih,
					    काष्ठा inode *inode,
					    loff_t new_file_length,
					    पूर्णांक *cut_size)
अणु
	अगर (le_ih_k_offset(le_ih) == DOT_OFFSET &&
	    new_file_length == max_reiserfs_offset(inode)) अणु
		RFALSE(ih_entry_count(le_ih) != 2,
		       "PAP-5220: incorrect empty directory item (%h)", le_ih);
		*cut_size = -(IH_SIZE + ih_item_len(le_ih));
		/* Delete the directory item containing "." and ".." entry. */
		वापस M_DELETE;
	पूर्ण

	अगर (ih_entry_count(le_ih) == 1) अणु
		/*
		 * Delete the directory item such as there is one record only
		 * in this item
		 */
		*cut_size = -(IH_SIZE + ih_item_len(le_ih));
		वापस M_DELETE;
	पूर्ण

	/* Cut one record from the directory item. */
	*cut_size =
	    -(DEH_SIZE +
	      entry_length(get_last_bh(path), le_ih, pos_in_item(path)));
	वापस M_CUT;
पूर्ण

#घोषणा JOURNAL_FOR_FREE_BLOCK_AND_UPDATE_SD (2 * JOURNAL_PER_BALANCE_CNT + 1)

/*
 * If the path poपूर्णांकs to a directory or direct item, calculate mode
 * and the size cut, क्रम balance.
 * If the path poपूर्णांकs to an indirect item, हटाओ some number of its
 * unक्रमmatted nodes.
 * In हाल of file truncate calculate whether this item must be
 * deleted/truncated or last unक्रमmatted node of this item will be
 * converted to a direct item.
 * This function वापसs a determination of what balance mode the
 * calling function should employ.
 */
अटल अक्षर prepare_क्रम_delete_or_cut(काष्ठा reiserfs_transaction_handle *th,
				      काष्ठा inode *inode,
				      काष्ठा treepath *path,
				      स्थिर काष्ठा cpu_key *item_key,
				      /*
				       * Number of unक्रमmatted nodes
				       * which were हटाओd from end
				       * of the file.
				       */
				      पूर्णांक *हटाओd,
				      पूर्णांक *cut_size,
				      /* MAX_KEY_OFFSET in हाल of delete. */
				      अचिन्हित दीर्घ दीर्घ new_file_length
    )
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा item_head *p_le_ih = tp_item_head(path);
	काष्ठा buffer_head *bh = PATH_PLAST_BUFFER(path);

	BUG_ON(!th->t_trans_id);

	/* Stat_data item. */
	अगर (is_statdata_le_ih(p_le_ih)) अणु

		RFALSE(new_file_length != max_reiserfs_offset(inode),
		       "PAP-5210: mode must be M_DELETE");

		*cut_size = -(IH_SIZE + ih_item_len(p_le_ih));
		वापस M_DELETE;
	पूर्ण

	/* Directory item. */
	अगर (is_direntry_le_ih(p_le_ih))
		वापस prepare_क्रम_direntry_item(path, p_le_ih, inode,
						 new_file_length,
						 cut_size);

	/* Direct item. */
	अगर (is_direct_le_ih(p_le_ih))
		वापस prepare_क्रम_direct_item(path, p_le_ih, inode,
					       new_file_length, cut_size);

	/* Case of an indirect item. */
	अणु
	    पूर्णांक blk_size = sb->s_blocksize;
	    काष्ठा item_head s_ih;
	    पूर्णांक need_re_search;
	    पूर्णांक delete = 0;
	    पूर्णांक result = M_CUT;
	    पूर्णांक pos = 0;

	    अगर ( new_file_length == max_reiserfs_offset (inode) ) अणु
		/*
		 * prepare_क्रम_delete_or_cut() is called by
		 * reiserfs_delete_item()
		 */
		new_file_length = 0;
		delete = 1;
	    पूर्ण

	    करो अणु
		need_re_search = 0;
		*cut_size = 0;
		bh = PATH_PLAST_BUFFER(path);
		copy_item_head(&s_ih, tp_item_head(path));
		pos = I_UNFM_NUM(&s_ih);

		जबतक (le_ih_k_offset (&s_ih) + (pos - 1) * blk_size > new_file_length) अणु
		    __le32 *unfm;
		    __u32 block;

		    /*
		     * Each unक्रमmatted block deletion may involve
		     * one additional biपंचांगap block पूर्णांकo the transaction,
		     * thereby the initial journal space reservation
		     * might not be enough.
		     */
		    अगर (!delete && (*cut_size) != 0 &&
			reiserfs_transaction_मुक्त_space(th) < JOURNAL_FOR_FREE_BLOCK_AND_UPDATE_SD)
			अवरोध;

		    unfm = (__le32 *)ih_item_body(bh, &s_ih) + pos - 1;
		    block = get_block_num(unfm, 0);

		    अगर (block != 0) अणु
			reiserfs_prepare_क्रम_journal(sb, bh, 1);
			put_block_num(unfm, 0, 0);
			journal_mark_dirty(th, bh);
			reiserfs_मुक्त_block(th, inode, block, 1);
		    पूर्ण

		    reiserfs_cond_resched(sb);

		    अगर (item_moved (&s_ih, path))  अणु
			need_re_search = 1;
			अवरोध;
		    पूर्ण

		    pos --;
		    (*हटाओd)++;
		    (*cut_size) -= UNFM_P_SIZE;

		    अगर (pos == 0) अणु
			(*cut_size) -= IH_SIZE;
			result = M_DELETE;
			अवरोध;
		    पूर्ण
		पूर्ण
		/*
		 * a trick.  If the buffer has been logged, this will
		 * करो nothing.  If we've broken the loop without logging
		 * it, it will restore the buffer
		 */
		reiserfs_restore_prepared_buffer(sb, bh);
	    पूर्ण जबतक (need_re_search &&
		     search_क्रम_position_by_key(sb, item_key, path) == POSITION_FOUND);
	    pos_in_item(path) = pos * UNFM_P_SIZE;

	    अगर (*cut_size == 0) अणु
		/*
		 * Nothing was cut. maybe convert last unक्रमmatted node to the
		 * direct item?
		 */
		result = M_CONVERT;
	    पूर्ण
	    वापस result;
	पूर्ण
पूर्ण

/* Calculate number of bytes which will be deleted or cut during balance */
अटल पूर्णांक calc_deleted_bytes_number(काष्ठा tree_balance *tb, अक्षर mode)
अणु
	पूर्णांक del_size;
	काष्ठा item_head *p_le_ih = tp_item_head(tb->tb_path);

	अगर (is_statdata_le_ih(p_le_ih))
		वापस 0;

	del_size =
	    (mode ==
	     M_DELETE) ? ih_item_len(p_le_ih) : -tb->insert_size[0];
	अगर (is_direntry_le_ih(p_le_ih)) अणु
		/*
		 * वापस EMPTY_सूची_SIZE; We delete emty directories only.
		 * we can't use EMPTY_सूची_SIZE, as old क्रमmat dirs have a
		 * dअगरferent empty size.  ick. FIXME, is this right?
		 */
		वापस del_size;
	पूर्ण

	अगर (is_indirect_le_ih(p_le_ih))
		del_size = (del_size / UNFM_P_SIZE) *
				(PATH_PLAST_BUFFER(tb->tb_path)->b_size);
	वापस del_size;
पूर्ण

अटल व्योम init_tb_काष्ठा(काष्ठा reiserfs_transaction_handle *th,
			   काष्ठा tree_balance *tb,
			   काष्ठा super_block *sb,
			   काष्ठा treepath *path, पूर्णांक size)
अणु

	BUG_ON(!th->t_trans_id);

	स_रखो(tb, '\0', माप(काष्ठा tree_balance));
	tb->transaction_handle = th;
	tb->tb_sb = sb;
	tb->tb_path = path;
	PATH_OFFSET_PBUFFER(path, ILLEGAL_PATH_ELEMENT_OFFSET) = शून्य;
	PATH_OFFSET_POSITION(path, ILLEGAL_PATH_ELEMENT_OFFSET) = 0;
	tb->insert_size[0] = size;
पूर्ण

व्योम padd_item(अक्षर *item, पूर्णांक total_length, पूर्णांक length)
अणु
	पूर्णांक i;

	क्रम (i = total_length; i > length;)
		item[--i] = 0;
पूर्ण

#अगर_घोषित REISERQUOTA_DEBUG
अक्षर key2type(काष्ठा reiserfs_key *ih)
अणु
	अगर (is_direntry_le_key(2, ih))
		वापस 'd';
	अगर (is_direct_le_key(2, ih))
		वापस 'D';
	अगर (is_indirect_le_key(2, ih))
		वापस 'i';
	अगर (is_statdata_le_key(2, ih))
		वापस 's';
	वापस 'u';
पूर्ण

अक्षर head2type(काष्ठा item_head *ih)
अणु
	अगर (is_direntry_le_ih(ih))
		वापस 'd';
	अगर (is_direct_le_ih(ih))
		वापस 'D';
	अगर (is_indirect_le_ih(ih))
		वापस 'i';
	अगर (is_statdata_le_ih(ih))
		वापस 's';
	वापस 'u';
पूर्ण
#पूर्ण_अगर

/*
 * Delete object item.
 * th       - active transaction handle
 * path     - path to the deleted item
 * item_key - key to search क्रम the deleted item
 * inकरोde   - used क्रम updating i_blocks and quotas
 * un_bh    - शून्य or unक्रमmatted node poपूर्णांकer
 */
पूर्णांक reiserfs_delete_item(काष्ठा reiserfs_transaction_handle *th,
			 काष्ठा treepath *path, स्थिर काष्ठा cpu_key *item_key,
			 काष्ठा inode *inode, काष्ठा buffer_head *un_bh)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा tree_balance s_del_balance;
	काष्ठा item_head s_ih;
	काष्ठा item_head *q_ih;
	पूर्णांक quota_cut_bytes;
	पूर्णांक ret_value, del_size, हटाओd;
	पूर्णांक depth;

#अगर_घोषित CONFIG_REISERFS_CHECK
	अक्षर mode;
	पूर्णांक iter = 0;
#पूर्ण_अगर

	BUG_ON(!th->t_trans_id);

	init_tb_काष्ठा(th, &s_del_balance, sb, path,
		       0 /*size is unknown */ );

	जबतक (1) अणु
		हटाओd = 0;

#अगर_घोषित CONFIG_REISERFS_CHECK
		iter++;
		mode =
#पूर्ण_अगर
		    prepare_क्रम_delete_or_cut(th, inode, path,
					      item_key, &हटाओd,
					      &del_size,
					      max_reiserfs_offset(inode));

		RFALSE(mode != M_DELETE, "PAP-5320: mode must be M_DELETE");

		copy_item_head(&s_ih, tp_item_head(path));
		s_del_balance.insert_size[0] = del_size;

		ret_value = fix_nodes(M_DELETE, &s_del_balance, शून्य, शून्य);
		अगर (ret_value != REPEAT_SEARCH)
			अवरोध;

		PROC_INFO_INC(sb, delete_item_restarted);

		/* file प्रणाली changed, repeat search */
		ret_value =
		    search_क्रम_position_by_key(sb, item_key, path);
		अगर (ret_value == IO_ERROR)
			अवरोध;
		अगर (ret_value == खाता_NOT_FOUND) अणु
			reiserfs_warning(sb, "vs-5340",
					 "no items of the file %K found",
					 item_key);
			अवरोध;
		पूर्ण
	पूर्ण			/* जबतक (1) */

	अगर (ret_value != CARRY_ON) अणु
		unfix_nodes(&s_del_balance);
		वापस 0;
	पूर्ण

	/* reiserfs_delete_item वापसs item length when success */
	ret_value = calc_deleted_bytes_number(&s_del_balance, M_DELETE);
	q_ih = tp_item_head(path);
	quota_cut_bytes = ih_item_len(q_ih);

	/*
	 * hack so the quota code करोesn't have to guess अगर the file has a
	 * tail.  On tail insert, we allocate quota क्रम 1 unक्रमmatted node.
	 * We test the offset because the tail might have been
	 * split पूर्णांकo multiple items, and we only want to decrement क्रम
	 * the unfm node once
	 */
	अगर (!S_ISLNK(inode->i_mode) && is_direct_le_ih(q_ih)) अणु
		अगर ((le_ih_k_offset(q_ih) & (sb->s_blocksize - 1)) == 1) अणु
			quota_cut_bytes = sb->s_blocksize + UNFM_P_SIZE;
		पूर्ण अन्यथा अणु
			quota_cut_bytes = 0;
		पूर्ण
	पूर्ण

	अगर (un_bh) अणु
		पूर्णांक off;
		अक्षर *data;

		/*
		 * We are in direct2indirect conversion, so move tail contents
		 * to the unक्रमmatted node
		 */
		/*
		 * note, we करो the copy beक्रमe preparing the buffer because we
		 * करोn't care about the contents of the unक्रमmatted node yet.
		 * the only thing we really care about is the direct item's
		 * data is in the unक्रमmatted node.
		 *
		 * Otherwise, we would have to call
		 * reiserfs_prepare_क्रम_journal on the unक्रमmatted node,
		 * which might schedule, meaning we'd have to loop all the
		 * way back up to the start of the जबतक loop.
		 *
		 * The unक्रमmatted node must be dirtied later on.  We can't be
		 * sure here अगर the entire tail has been deleted yet.
		 *
		 * un_bh is from the page cache (all unक्रमmatted nodes are
		 * from the page cache) and might be a highmem page.  So, we
		 * can't use un_bh->b_data.
		 * -clm
		 */

		data = kmap_atomic(un_bh->b_page);
		off = ((le_ih_k_offset(&s_ih) - 1) & (PAGE_SIZE - 1));
		स_नकल(data + off,
		       ih_item_body(PATH_PLAST_BUFFER(path), &s_ih),
		       ret_value);
		kunmap_atomic(data);
	पूर्ण

	/* Perक्रमm balancing after all resources have been collected at once. */
	करो_balance(&s_del_balance, शून्य, शून्य, M_DELETE);

#अगर_घोषित REISERQUOTA_DEBUG
	reiserfs_debug(sb, REISERFS_DEBUG_CODE,
		       "reiserquota delete_item(): freeing %u, id=%u type=%c",
		       quota_cut_bytes, inode->i_uid, head2type(&s_ih));
#पूर्ण_अगर
	depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
	dquot_मुक्त_space_nodirty(inode, quota_cut_bytes);
	reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);

	/* Return deleted body length */
	वापस ret_value;
पूर्ण

/*
 * Summary Of Mechanisms For Handling Collisions Between Processes:
 *
 *  deletion of the body of the object is perक्रमmed by iput(), with the
 *  result that अगर multiple processes are operating on a file, the
 *  deletion of the body of the file is deferred until the last process
 *  that has an खोलो inode perक्रमms its iput().
 *
 *  ग_लिखोs and truncates are रक्षित from collisions by use of
 *  semaphores.
 *
 *  creates, linking, and mknod are रक्षित from collisions with other
 *  processes by making the reiserfs_add_entry() the last step in the
 *  creation, and then rolling back all changes अगर there was a collision.
 *  - Hans
*/

/* this deletes item which never माला_लो split */
व्योम reiserfs_delete_solid_item(काष्ठा reiserfs_transaction_handle *th,
				काष्ठा inode *inode, काष्ठा reiserfs_key *key)
अणु
	काष्ठा super_block *sb = th->t_super;
	काष्ठा tree_balance tb;
	INITIALIZE_PATH(path);
	पूर्णांक item_len = 0;
	पूर्णांक tb_init = 0;
	काष्ठा cpu_key cpu_key;
	पूर्णांक retval;
	पूर्णांक quota_cut_bytes = 0;

	BUG_ON(!th->t_trans_id);

	le_key2cpu_key(&cpu_key, key);

	जबतक (1) अणु
		retval = search_item(th->t_super, &cpu_key, &path);
		अगर (retval == IO_ERROR) अणु
			reiserfs_error(th->t_super, "vs-5350",
				       "i/o failure occurred trying "
				       "to delete %K", &cpu_key);
			अवरोध;
		पूर्ण
		अगर (retval != ITEM_FOUND) अणु
			pathrअन्यथा(&path);
			/*
			 * No need क्रम a warning, अगर there is just no मुक्त
			 * space to insert '..' item पूर्णांकo the
			 * newly-created subdir
			 */
			अगर (!
			    ((अचिन्हित दीर्घ दीर्घ)
			     GET_HASH_VALUE(le_key_k_offset
					    (le_key_version(key), key)) == 0
			     && (अचिन्हित दीर्घ दीर्घ)
			     GET_GENERATION_NUMBER(le_key_k_offset
						   (le_key_version(key),
						    key)) == 1))
				reiserfs_warning(th->t_super, "vs-5355",
						 "%k not found", key);
			अवरोध;
		पूर्ण
		अगर (!tb_init) अणु
			tb_init = 1;
			item_len = ih_item_len(tp_item_head(&path));
			init_tb_काष्ठा(th, &tb, th->t_super, &path,
				       -(IH_SIZE + item_len));
		पूर्ण
		quota_cut_bytes = ih_item_len(tp_item_head(&path));

		retval = fix_nodes(M_DELETE, &tb, शून्य, शून्य);
		अगर (retval == REPEAT_SEARCH) अणु
			PROC_INFO_INC(th->t_super, delete_solid_item_restarted);
			जारी;
		पूर्ण

		अगर (retval == CARRY_ON) अणु
			करो_balance(&tb, शून्य, शून्य, M_DELETE);
			/*
			 * Should we count quota क्रम item? (we करोn't
			 * count quotas क्रम save-links)
			 */
			अगर (inode) अणु
				पूर्णांक depth;
#अगर_घोषित REISERQUOTA_DEBUG
				reiserfs_debug(th->t_super, REISERFS_DEBUG_CODE,
					       "reiserquota delete_solid_item(): freeing %u id=%u type=%c",
					       quota_cut_bytes, inode->i_uid,
					       key2type(key));
#पूर्ण_अगर
				depth = reiserfs_ग_लिखो_unlock_nested(sb);
				dquot_मुक्त_space_nodirty(inode,
							 quota_cut_bytes);
				reiserfs_ग_लिखो_lock_nested(sb, depth);
			पूर्ण
			अवरोध;
		पूर्ण

		/* IO_ERROR, NO_DISK_SPACE, etc */
		reiserfs_warning(th->t_super, "vs-5360",
				 "could not delete %K due to fix_nodes failure",
				 &cpu_key);
		unfix_nodes(&tb);
		अवरोध;
	पूर्ण

	reiserfs_check_path(&path);
पूर्ण

पूर्णांक reiserfs_delete_object(काष्ठा reiserfs_transaction_handle *th,
			   काष्ठा inode *inode)
अणु
	पूर्णांक err;
	inode->i_size = 0;
	BUG_ON(!th->t_trans_id);

	/* क्रम directory this deletes item containing "." and ".." */
	err =
	    reiserfs_करो_truncate(th, inode, शून्य, 0 /*no बारtamp updates */ );
	अगर (err)
		वापस err;

#अगर defined( USE_INODE_GENERATION_COUNTER )
	अगर (!old_क्रमmat_only(th->t_super)) अणु
		__le32 *inode_generation;

		inode_generation =
		    &REISERFS_SB(th->t_super)->s_rs->s_inode_generation;
		le32_add_cpu(inode_generation, 1);
	पूर्ण
/* USE_INODE_GENERATION_COUNTER */
#पूर्ण_अगर
	reiserfs_delete_solid_item(th, inode, INODE_PKEY(inode));

	वापस err;
पूर्ण

अटल व्योम unmap_buffers(काष्ठा page *page, loff_t pos)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा buffer_head *head;
	काष्ठा buffer_head *next;
	अचिन्हित दीर्घ tail_index;
	अचिन्हित दीर्घ cur_index;

	अगर (page) अणु
		अगर (page_has_buffers(page)) अणु
			tail_index = pos & (PAGE_SIZE - 1);
			cur_index = 0;
			head = page_buffers(page);
			bh = head;
			करो अणु
				next = bh->b_this_page;

				/*
				 * we want to unmap the buffers that contain
				 * the tail, and all the buffers after it
				 * (since the tail must be at the end of the
				 * file).  We करोn't want to unmap file data
				 * beक्रमe the tail, since it might be dirty
				 * and रुकोing to reach disk
				 */
				cur_index += bh->b_size;
				अगर (cur_index > tail_index) अणु
					reiserfs_unmap_buffer(bh);
				पूर्ण
				bh = next;
			पूर्ण जबतक (bh != head);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक maybe_indirect_to_direct(काष्ठा reiserfs_transaction_handle *th,
				    काष्ठा inode *inode,
				    काष्ठा page *page,
				    काष्ठा treepath *path,
				    स्थिर काष्ठा cpu_key *item_key,
				    loff_t new_file_size, अक्षर *mode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक block_size = sb->s_blocksize;
	पूर्णांक cut_bytes;
	BUG_ON(!th->t_trans_id);
	BUG_ON(new_file_size != inode->i_size);

	/*
	 * the page being sent in could be शून्य अगर there was an i/o error
	 * पढ़ोing in the last block.  The user will hit problems trying to
	 * पढ़ो the file, but क्रम now we just skip the indirect2direct
	 */
	अगर (atomic_पढ़ो(&inode->i_count) > 1 ||
	    !tail_has_to_be_packed(inode) ||
	    !page || (REISERFS_I(inode)->i_flags & i_nopack_mask)) अणु
		/* leave tail in an unक्रमmatted node */
		*mode = M_SKIP_BALANCING;
		cut_bytes =
		    block_size - (new_file_size & (block_size - 1));
		pathrअन्यथा(path);
		वापस cut_bytes;
	पूर्ण

	/* Perक्रमm the conversion to a direct_item. */
	वापस indirect2direct(th, inode, page, path, item_key,
			       new_file_size, mode);
पूर्ण

/*
 * we did indirect_to_direct conversion. And we have inserted direct
 * item successesfully, but there were no disk space to cut unfm
 * poपूर्णांकer being converted. Thereक्रमe we have to delete inserted
 * direct item(s)
 */
अटल व्योम indirect_to_direct_roll_back(काष्ठा reiserfs_transaction_handle *th,
					 काष्ठा inode *inode, काष्ठा treepath *path)
अणु
	काष्ठा cpu_key tail_key;
	पूर्णांक tail_len;
	पूर्णांक हटाओd;
	BUG_ON(!th->t_trans_id);

	make_cpu_key(&tail_key, inode, inode->i_size + 1, TYPE_सूचीECT, 4);
	tail_key.key_length = 4;

	tail_len =
	    (cpu_key_k_offset(&tail_key) & (inode->i_sb->s_blocksize - 1)) - 1;
	जबतक (tail_len) अणु
		/* look क्रम the last byte of the tail */
		अगर (search_क्रम_position_by_key(inode->i_sb, &tail_key, path) ==
		    POSITION_NOT_FOUND)
			reiserfs_panic(inode->i_sb, "vs-5615",
				       "found invalid item");
		RFALSE(path->pos_in_item !=
		       ih_item_len(tp_item_head(path)) - 1,
		       "vs-5616: appended bytes found");
		PATH_LAST_POSITION(path)--;

		हटाओd =
		    reiserfs_delete_item(th, path, &tail_key, inode,
					 शून्य /*unbh not needed */ );
		RFALSE(हटाओd <= 0
		       || हटाओd > tail_len,
		       "vs-5617: there was tail %d bytes, removed item length %d bytes",
		       tail_len, हटाओd);
		tail_len -= हटाओd;
		set_cpu_key_k_offset(&tail_key,
				     cpu_key_k_offset(&tail_key) - हटाओd);
	पूर्ण
	reiserfs_warning(inode->i_sb, "reiserfs-5091", "indirect_to_direct "
			 "conversion has been rolled back due to "
			 "lack of disk space");
	mark_inode_dirty(inode);
पूर्ण

/* (Truncate or cut entry) or delete object item. Returns < 0 on failure */
पूर्णांक reiserfs_cut_from_item(काष्ठा reiserfs_transaction_handle *th,
			   काष्ठा treepath *path,
			   काष्ठा cpu_key *item_key,
			   काष्ठा inode *inode,
			   काष्ठा page *page, loff_t new_file_size)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	/*
	 * Every function which is going to call करो_balance must first
	 * create a tree_balance काष्ठाure.  Then it must fill up this
	 * काष्ठाure by using the init_tb_काष्ठा and fix_nodes functions.
	 * After that we can make tree balancing.
	 */
	काष्ठा tree_balance s_cut_balance;
	काष्ठा item_head *p_le_ih;
	पूर्णांक cut_size = 0;	/* Amount to be cut. */
	पूर्णांक ret_value = CARRY_ON;
	पूर्णांक हटाओd = 0;	/* Number of the हटाओd unक्रमmatted nodes. */
	पूर्णांक is_inode_locked = 0;
	अक्षर mode;		/* Mode of the balance. */
	पूर्णांक retval2 = -1;
	पूर्णांक quota_cut_bytes;
	loff_t tail_pos = 0;
	पूर्णांक depth;

	BUG_ON(!th->t_trans_id);

	init_tb_काष्ठा(th, &s_cut_balance, inode->i_sb, path,
		       cut_size);

	/*
	 * Repeat this loop until we either cut the item without needing
	 * to balance, or we fix_nodes without schedule occurring
	 */
	जबतक (1) अणु
		/*
		 * Determine the balance mode, position of the first byte to
		 * be cut, and size to be cut.  In हाल of the indirect item
		 * मुक्त unक्रमmatted nodes which are poपूर्णांकed to by the cut
		 * poपूर्णांकers.
		 */

		mode =
		    prepare_क्रम_delete_or_cut(th, inode, path,
					      item_key, &हटाओd,
					      &cut_size, new_file_size);
		अगर (mode == M_CONVERT) अणु
			/*
			 * convert last unक्रमmatted node to direct item or
			 * leave tail in the unक्रमmatted node
			 */
			RFALSE(ret_value != CARRY_ON,
			       "PAP-5570: can not convert twice");

			ret_value =
			    maybe_indirect_to_direct(th, inode, page,
						     path, item_key,
						     new_file_size, &mode);
			अगर (mode == M_SKIP_BALANCING)
				/* tail has been left in the unक्रमmatted node */
				वापस ret_value;

			is_inode_locked = 1;

			/*
			 * removing of last unक्रमmatted node will
			 * change value we have to वापस to truncate.
			 * Save it
			 */
			retval2 = ret_value;

			/*
			 * So, we have perक्रमmed the first part of the
			 * conversion:
			 * inserting the new direct item.  Now we are
			 * removing the last unक्रमmatted node poपूर्णांकer.
			 * Set key to search क्रम it.
			 */
			set_cpu_key_k_type(item_key, TYPE_INसूचीECT);
			item_key->key_length = 4;
			new_file_size -=
			    (new_file_size & (sb->s_blocksize - 1));
			tail_pos = new_file_size;
			set_cpu_key_k_offset(item_key, new_file_size + 1);
			अगर (search_क्रम_position_by_key
			    (sb, item_key,
			     path) == POSITION_NOT_FOUND) अणु
				prपूर्णांक_block(PATH_PLAST_BUFFER(path), 3,
					    PATH_LAST_POSITION(path) - 1,
					    PATH_LAST_POSITION(path) + 1);
				reiserfs_panic(sb, "PAP-5580", "item to "
					       "convert does not exist (%K)",
					       item_key);
			पूर्ण
			जारी;
		पूर्ण
		अगर (cut_size == 0) अणु
			pathrअन्यथा(path);
			वापस 0;
		पूर्ण

		s_cut_balance.insert_size[0] = cut_size;

		ret_value = fix_nodes(mode, &s_cut_balance, शून्य, शून्य);
		अगर (ret_value != REPEAT_SEARCH)
			अवरोध;

		PROC_INFO_INC(sb, cut_from_item_restarted);

		ret_value =
		    search_क्रम_position_by_key(sb, item_key, path);
		अगर (ret_value == POSITION_FOUND)
			जारी;

		reiserfs_warning(sb, "PAP-5610", "item %K not found",
				 item_key);
		unfix_nodes(&s_cut_balance);
		वापस (ret_value == IO_ERROR) ? -EIO : -ENOENT;
	पूर्ण			/* जबतक */

	/* check fix_nodes results (IO_ERROR or NO_DISK_SPACE) */
	अगर (ret_value != CARRY_ON) अणु
		अगर (is_inode_locked) अणु
			/*
			 * FIXME: this seems to be not needed: we are always
			 * able to cut item
			 */
			indirect_to_direct_roll_back(th, inode, path);
		पूर्ण
		अगर (ret_value == NO_DISK_SPACE)
			reiserfs_warning(sb, "reiserfs-5092",
					 "NO_DISK_SPACE");
		unfix_nodes(&s_cut_balance);
		वापस -EIO;
	पूर्ण

	/* go ahead and perक्रमm balancing */

	RFALSE(mode == M_PASTE || mode == M_INSERT, "invalid mode");

	/* Calculate number of bytes that need to be cut from the item. */
	quota_cut_bytes =
	    (mode ==
	     M_DELETE) ? ih_item_len(tp_item_head(path)) : -s_cut_balance.
	    insert_size[0];
	अगर (retval2 == -1)
		ret_value = calc_deleted_bytes_number(&s_cut_balance, mode);
	अन्यथा
		ret_value = retval2;

	/*
	 * For direct items, we only change the quota when deleting the last
	 * item.
	 */
	p_le_ih = tp_item_head(s_cut_balance.tb_path);
	अगर (!S_ISLNK(inode->i_mode) && is_direct_le_ih(p_le_ih)) अणु
		अगर (mode == M_DELETE &&
		    (le_ih_k_offset(p_le_ih) & (sb->s_blocksize - 1)) ==
		    1) अणु
			/* FIXME: this is to keep 3.5 happy */
			REISERFS_I(inode)->i_first_direct_byte = U32_MAX;
			quota_cut_bytes = sb->s_blocksize + UNFM_P_SIZE;
		पूर्ण अन्यथा अणु
			quota_cut_bytes = 0;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_REISERFS_CHECK
	अगर (is_inode_locked) अणु
		काष्ठा item_head *le_ih =
		    tp_item_head(s_cut_balance.tb_path);
		/*
		 * we are going to complete indirect2direct conversion. Make
		 * sure, that we exactly हटाओ last unक्रमmatted node poपूर्णांकer
		 * of the item
		 */
		अगर (!is_indirect_le_ih(le_ih))
			reiserfs_panic(sb, "vs-5652",
				       "item must be indirect %h", le_ih);

		अगर (mode == M_DELETE && ih_item_len(le_ih) != UNFM_P_SIZE)
			reiserfs_panic(sb, "vs-5653", "completing "
				       "indirect2direct conversion indirect "
				       "item %h being deleted must be of "
				       "4 byte long", le_ih);

		अगर (mode == M_CUT
		    && s_cut_balance.insert_size[0] != -UNFM_P_SIZE) अणु
			reiserfs_panic(sb, "vs-5654", "can not complete "
				       "indirect2direct conversion of %h "
				       "(CUT, insert_size==%d)",
				       le_ih, s_cut_balance.insert_size[0]);
		पूर्ण
		/*
		 * it would be useful to make sure, that right neighboring
		 * item is direct item of this file
		 */
	पूर्ण
#पूर्ण_अगर

	करो_balance(&s_cut_balance, शून्य, शून्य, mode);
	अगर (is_inode_locked) अणु
		/*
		 * we've करोne an indirect->direct conversion.  when the
		 * data block was मुक्तd, it was हटाओd from the list of
		 * blocks that must be flushed beक्रमe the transaction
		 * commits, make sure to unmap and invalidate it
		 */
		unmap_buffers(page, tail_pos);
		REISERFS_I(inode)->i_flags &= ~i_pack_on_बंद_mask;
	पूर्ण
#अगर_घोषित REISERQUOTA_DEBUG
	reiserfs_debug(inode->i_sb, REISERFS_DEBUG_CODE,
		       "reiserquota cut_from_item(): freeing %u id=%u type=%c",
		       quota_cut_bytes, inode->i_uid, '?');
#पूर्ण_अगर
	depth = reiserfs_ग_लिखो_unlock_nested(sb);
	dquot_मुक्त_space_nodirty(inode, quota_cut_bytes);
	reiserfs_ग_लिखो_lock_nested(sb, depth);
	वापस ret_value;
पूर्ण

अटल व्योम truncate_directory(काष्ठा reiserfs_transaction_handle *th,
			       काष्ठा inode *inode)
अणु
	BUG_ON(!th->t_trans_id);
	अगर (inode->i_nlink)
		reiserfs_error(inode->i_sb, "vs-5655", "link count != 0");

	set_le_key_k_offset(KEY_FORMAT_3_5, INODE_PKEY(inode), DOT_OFFSET);
	set_le_key_k_type(KEY_FORMAT_3_5, INODE_PKEY(inode), TYPE_सूचीENTRY);
	reiserfs_delete_solid_item(th, inode, INODE_PKEY(inode));
	reiserfs_update_sd(th, inode);
	set_le_key_k_offset(KEY_FORMAT_3_5, INODE_PKEY(inode), SD_OFFSET);
	set_le_key_k_type(KEY_FORMAT_3_5, INODE_PKEY(inode), TYPE_STAT_DATA);
पूर्ण

/*
 * Truncate file to the new size. Note, this must be called with a
 * transaction alपढ़ोy started
 */
पूर्णांक reiserfs_करो_truncate(काष्ठा reiserfs_transaction_handle *th,
			 काष्ठा inode *inode,	/* ->i_size contains new size */
			 काष्ठा page *page,	/* up to date क्रम last block */
			 /*
			  * when it is called by file_release to convert
			  * the tail - no बारtamps should be updated
			  */
			 पूर्णांक update_बारtamps
    )
अणु
	INITIALIZE_PATH(s_search_path);	/* Path to the current object item. */
	काष्ठा item_head *p_le_ih;	/* Poपूर्णांकer to an item header. */

	/* Key to search क्रम a previous file item. */
	काष्ठा cpu_key s_item_key;
	loff_t file_size,	/* Old file size. */
	 new_file_size;	/* New file size. */
	पूर्णांक deleted;		/* Number of deleted or truncated bytes. */
	पूर्णांक retval;
	पूर्णांक err = 0;

	BUG_ON(!th->t_trans_id);
	अगर (!
	    (S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode)
	     || S_ISLNK(inode->i_mode)))
		वापस 0;

	/* deletion of directory - no need to update बारtamps */
	अगर (S_ISसूची(inode->i_mode)) अणु
		truncate_directory(th, inode);
		वापस 0;
	पूर्ण

	/* Get new file size. */
	new_file_size = inode->i_size;

	/* FIXME: note, that key type is unimportant here */
	make_cpu_key(&s_item_key, inode, max_reiserfs_offset(inode),
		     TYPE_सूचीECT, 3);

	retval =
	    search_क्रम_position_by_key(inode->i_sb, &s_item_key,
				       &s_search_path);
	अगर (retval == IO_ERROR) अणु
		reiserfs_error(inode->i_sb, "vs-5657",
			       "i/o failure occurred trying to truncate %K",
			       &s_item_key);
		err = -EIO;
		जाओ out;
	पूर्ण
	अगर (retval == POSITION_FOUND || retval == खाता_NOT_FOUND) अणु
		reiserfs_error(inode->i_sb, "PAP-5660",
			       "wrong result %d of search for %K", retval,
			       &s_item_key);

		err = -EIO;
		जाओ out;
	पूर्ण

	s_search_path.pos_in_item--;

	/* Get real file size (total length of all file items) */
	p_le_ih = tp_item_head(&s_search_path);
	अगर (is_statdata_le_ih(p_le_ih))
		file_size = 0;
	अन्यथा अणु
		loff_t offset = le_ih_k_offset(p_le_ih);
		पूर्णांक bytes =
		    op_bytes_number(p_le_ih, inode->i_sb->s_blocksize);

		/*
		 * this may mismatch with real file size: अगर last direct item
		 * had no padding zeros and last unक्रमmatted node had no मुक्त
		 * space, this file would have this file size
		 */
		file_size = offset + bytes - 1;
	पूर्ण
	/*
	 * are we करोing a full truncate or delete, अगर so
	 * kick in the पढ़ोa code
	 */
	अगर (new_file_size == 0)
		s_search_path.पढ़ोa = PATH_READA | PATH_READA_BACK;

	अगर (file_size == 0 || file_size < new_file_size) अणु
		जाओ update_and_out;
	पूर्ण

	/* Update key to search क्रम the last file item. */
	set_cpu_key_k_offset(&s_item_key, file_size);

	करो अणु
		/* Cut or delete file item. */
		deleted =
		    reiserfs_cut_from_item(th, &s_search_path, &s_item_key,
					   inode, page, new_file_size);
		अगर (deleted < 0) अणु
			reiserfs_warning(inode->i_sb, "vs-5665",
					 "reiserfs_cut_from_item failed");
			reiserfs_check_path(&s_search_path);
			वापस 0;
		पूर्ण

		RFALSE(deleted > file_size,
		       "PAP-5670: reiserfs_cut_from_item: too many bytes deleted: deleted %d, file_size %lu, item_key %K",
		       deleted, file_size, &s_item_key);

		/* Change key to search the last file item. */
		file_size -= deleted;

		set_cpu_key_k_offset(&s_item_key, file_size);

		/*
		 * While there are bytes to truncate and previous
		 * file item is presented in the tree.
		 */

		/*
		 * This loop could take a really दीर्घ समय, and could log
		 * many more blocks than a transaction can hold.  So, we करो
		 * a polite journal end here, and अगर the transaction needs
		 * ending, we make sure the file is consistent beक्रमe ending
		 * the current trans and starting a new one
		 */
		अगर (journal_transaction_should_end(th, 0) ||
		    reiserfs_transaction_मुक्त_space(th) <= JOURNAL_FOR_FREE_BLOCK_AND_UPDATE_SD) अणु
			pathrअन्यथा(&s_search_path);

			अगर (update_बारtamps) अणु
				inode->i_mसमय = current_समय(inode);
				inode->i_स_समय = current_समय(inode);
			पूर्ण
			reiserfs_update_sd(th, inode);

			err = journal_end(th);
			अगर (err)
				जाओ out;
			err = journal_begin(th, inode->i_sb,
					    JOURNAL_FOR_FREE_BLOCK_AND_UPDATE_SD + JOURNAL_PER_BALANCE_CNT * 4) ;
			अगर (err)
				जाओ out;
			reiserfs_update_inode_transaction(inode);
		पूर्ण
	पूर्ण जबतक (file_size > ROUND_UP(new_file_size) &&
		 search_क्रम_position_by_key(inode->i_sb, &s_item_key,
					    &s_search_path) == POSITION_FOUND);

	RFALSE(file_size > ROUND_UP(new_file_size),
	       "PAP-5680: truncate did not finish: new_file_size %lld, current %lld, oid %d",
	       new_file_size, file_size, s_item_key.on_disk_key.k_objectid);

update_and_out:
	अगर (update_बारtamps) अणु
		/* this is truncate, not file closing */
		inode->i_mसमय = current_समय(inode);
		inode->i_स_समय = current_समय(inode);
	पूर्ण
	reiserfs_update_sd(th, inode);

out:
	pathrअन्यथा(&s_search_path);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_REISERFS_CHECK
/* this makes sure, that we __append__, not overग_लिखो or add holes */
अटल व्योम check_research_क्रम_paste(काष्ठा treepath *path,
				     स्थिर काष्ठा cpu_key *key)
अणु
	काष्ठा item_head *found_ih = tp_item_head(path);

	अगर (is_direct_le_ih(found_ih)) अणु
		अगर (le_ih_k_offset(found_ih) +
		    op_bytes_number(found_ih,
				    get_last_bh(path)->b_size) !=
		    cpu_key_k_offset(key)
		    || op_bytes_number(found_ih,
				       get_last_bh(path)->b_size) !=
		    pos_in_item(path))
			reiserfs_panic(शून्य, "PAP-5720", "found direct item "
				       "%h or position (%d) does not match "
				       "to key %K", found_ih,
				       pos_in_item(path), key);
	पूर्ण
	अगर (is_indirect_le_ih(found_ih)) अणु
		अगर (le_ih_k_offset(found_ih) +
		    op_bytes_number(found_ih,
				    get_last_bh(path)->b_size) !=
		    cpu_key_k_offset(key)
		    || I_UNFM_NUM(found_ih) != pos_in_item(path)
		    || get_ih_मुक्त_space(found_ih) != 0)
			reiserfs_panic(शून्य, "PAP-5730", "found indirect "
				       "item (%h) or position (%d) does not "
				       "match to key (%K)",
				       found_ih, pos_in_item(path), key);
	पूर्ण
पूर्ण
#पूर्ण_अगर				/* config reiserfs check */

/*
 * Paste bytes to the existing item.
 * Returns bytes number pasted पूर्णांकo the item.
 */
पूर्णांक reiserfs_paste_पूर्णांकo_item(काष्ठा reiserfs_transaction_handle *th,
			     /* Path to the pasted item. */
			     काष्ठा treepath *search_path,
			     /* Key to search क्रम the needed item. */
			     स्थिर काष्ठा cpu_key *key,
			     /* Inode item beदीर्घs to */
			     काष्ठा inode *inode,
			     /* Poपूर्णांकer to the bytes to paste. */
			     स्थिर अक्षर *body,
			     /* Size of pasted bytes. */
			     पूर्णांक pasted_size)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा tree_balance s_paste_balance;
	पूर्णांक retval;
	पूर्णांक fs_gen;
	पूर्णांक depth;

	BUG_ON(!th->t_trans_id);

	fs_gen = get_generation(inode->i_sb);

#अगर_घोषित REISERQUOTA_DEBUG
	reiserfs_debug(inode->i_sb, REISERFS_DEBUG_CODE,
		       "reiserquota paste_into_item(): allocating %u id=%u type=%c",
		       pasted_size, inode->i_uid,
		       key2type(&key->on_disk_key));
#पूर्ण_अगर

	depth = reiserfs_ग_लिखो_unlock_nested(sb);
	retval = dquot_alloc_space_nodirty(inode, pasted_size);
	reiserfs_ग_लिखो_lock_nested(sb, depth);
	अगर (retval) अणु
		pathrअन्यथा(search_path);
		वापस retval;
	पूर्ण
	init_tb_काष्ठा(th, &s_paste_balance, th->t_super, search_path,
		       pasted_size);
#अगर_घोषित DISPLACE_NEW_PACKING_LOCALITIES
	s_paste_balance.key = key->on_disk_key;
#पूर्ण_अगर

	/* DQUOT_* can schedule, must check beक्रमe the fix_nodes */
	अगर (fs_changed(fs_gen, inode->i_sb)) अणु
		जाओ search_again;
	पूर्ण

	जबतक ((retval =
		fix_nodes(M_PASTE, &s_paste_balance, शून्य,
			  body)) == REPEAT_SEARCH) अणु
search_again:
		/* file प्रणाली changed जबतक we were in the fix_nodes */
		PROC_INFO_INC(th->t_super, paste_पूर्णांकo_item_restarted);
		retval =
		    search_क्रम_position_by_key(th->t_super, key,
					       search_path);
		अगर (retval == IO_ERROR) अणु
			retval = -EIO;
			जाओ error_out;
		पूर्ण
		अगर (retval == POSITION_FOUND) अणु
			reiserfs_warning(inode->i_sb, "PAP-5710",
					 "entry or pasted byte (%K) exists",
					 key);
			retval = -EEXIST;
			जाओ error_out;
		पूर्ण
#अगर_घोषित CONFIG_REISERFS_CHECK
		check_research_क्रम_paste(search_path, key);
#पूर्ण_अगर
	पूर्ण

	/*
	 * Perक्रमm balancing after all resources are collected by fix_nodes,
	 * and accessing them will not risk triggering schedule.
	 */
	अगर (retval == CARRY_ON) अणु
		करो_balance(&s_paste_balance, शून्य /*ih */ , body, M_PASTE);
		वापस 0;
	पूर्ण
	retval = (retval == NO_DISK_SPACE) ? -ENOSPC : -EIO;
error_out:
	/* this also releases the path */
	unfix_nodes(&s_paste_balance);
#अगर_घोषित REISERQUOTA_DEBUG
	reiserfs_debug(inode->i_sb, REISERFS_DEBUG_CODE,
		       "reiserquota paste_into_item(): freeing %u id=%u type=%c",
		       pasted_size, inode->i_uid,
		       key2type(&key->on_disk_key));
#पूर्ण_अगर
	depth = reiserfs_ग_लिखो_unlock_nested(sb);
	dquot_मुक्त_space_nodirty(inode, pasted_size);
	reiserfs_ग_लिखो_lock_nested(sb, depth);
	वापस retval;
पूर्ण

/*
 * Insert new item पूर्णांकo the buffer at the path.
 * th   - active transaction handle
 * path - path to the inserted item
 * ih   - poपूर्णांकer to the item header to insert
 * body - poपूर्णांकer to the bytes to insert
 */
पूर्णांक reiserfs_insert_item(काष्ठा reiserfs_transaction_handle *th,
			 काष्ठा treepath *path, स्थिर काष्ठा cpu_key *key,
			 काष्ठा item_head *ih, काष्ठा inode *inode,
			 स्थिर अक्षर *body)
अणु
	काष्ठा tree_balance s_ins_balance;
	पूर्णांक retval;
	पूर्णांक fs_gen = 0;
	पूर्णांक quota_bytes = 0;

	BUG_ON(!th->t_trans_id);

	अगर (inode) अणु		/* Do we count quotas क्रम item? */
		पूर्णांक depth;
		fs_gen = get_generation(inode->i_sb);
		quota_bytes = ih_item_len(ih);

		/*
		 * hack so the quota code करोesn't have to guess
		 * अगर the file has a tail, links are always tails,
		 * so there's no guessing needed
		 */
		अगर (!S_ISLNK(inode->i_mode) && is_direct_le_ih(ih))
			quota_bytes = inode->i_sb->s_blocksize + UNFM_P_SIZE;
#अगर_घोषित REISERQUOTA_DEBUG
		reiserfs_debug(inode->i_sb, REISERFS_DEBUG_CODE,
			       "reiserquota insert_item(): allocating %u id=%u type=%c",
			       quota_bytes, inode->i_uid, head2type(ih));
#पूर्ण_अगर
		/*
		 * We can't dirty inode here. It would be immediately
		 * written but appropriate stat item isn't inserted yet...
		 */
		depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
		retval = dquot_alloc_space_nodirty(inode, quota_bytes);
		reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);
		अगर (retval) अणु
			pathrअन्यथा(path);
			वापस retval;
		पूर्ण
	पूर्ण
	init_tb_काष्ठा(th, &s_ins_balance, th->t_super, path,
		       IH_SIZE + ih_item_len(ih));
#अगर_घोषित DISPLACE_NEW_PACKING_LOCALITIES
	s_ins_balance.key = key->on_disk_key;
#पूर्ण_अगर
	/*
	 * DQUOT_* can schedule, must check to be sure calling
	 * fix_nodes is safe
	 */
	अगर (inode && fs_changed(fs_gen, inode->i_sb)) अणु
		जाओ search_again;
	पूर्ण

	जबतक ((retval =
		fix_nodes(M_INSERT, &s_ins_balance, ih,
			  body)) == REPEAT_SEARCH) अणु
search_again:
		/* file प्रणाली changed जबतक we were in the fix_nodes */
		PROC_INFO_INC(th->t_super, insert_item_restarted);
		retval = search_item(th->t_super, key, path);
		अगर (retval == IO_ERROR) अणु
			retval = -EIO;
			जाओ error_out;
		पूर्ण
		अगर (retval == ITEM_FOUND) अणु
			reiserfs_warning(th->t_super, "PAP-5760",
					 "key %K already exists in the tree",
					 key);
			retval = -EEXIST;
			जाओ error_out;
		पूर्ण
	पूर्ण

	/* make balancing after all resources will be collected at a समय */
	अगर (retval == CARRY_ON) अणु
		करो_balance(&s_ins_balance, ih, body, M_INSERT);
		वापस 0;
	पूर्ण

	retval = (retval == NO_DISK_SPACE) ? -ENOSPC : -EIO;
error_out:
	/* also releases the path */
	unfix_nodes(&s_ins_balance);
#अगर_घोषित REISERQUOTA_DEBUG
	अगर (inode)
		reiserfs_debug(th->t_super, REISERFS_DEBUG_CODE,
		       "reiserquota insert_item(): freeing %u id=%u type=%c",
		       quota_bytes, inode->i_uid, head2type(ih));
#पूर्ण_अगर
	अगर (inode) अणु
		पूर्णांक depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
		dquot_मुक्त_space_nodirty(inode, quota_bytes);
		reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);
	पूर्ण
	वापस retval;
पूर्ण
