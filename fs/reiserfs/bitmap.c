<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */
/* Reiserfs block (de)allocator, biपंचांगap-based. */

#समावेश <linux/समय.स>
#समावेश "reiserfs.h"
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/seq_file.h>

#घोषणा PREALLOCATION_SIZE 9

/* dअगरferent reiserfs block allocator options */

#घोषणा SB_ALLOC_OPTS(s) (REISERFS_SB(s)->s_alloc_options.bits)

#घोषणा  _ALLOC_concentrating_क्रमmatted_nodes 0
#घोषणा  _ALLOC_displacing_large_files 1
#घोषणा  _ALLOC_displacing_new_packing_localities 2
#घोषणा  _ALLOC_old_hashed_relocation 3
#घोषणा  _ALLOC_new_hashed_relocation 4
#घोषणा  _ALLOC_skip_busy 5
#घोषणा  _ALLOC_displace_based_on_dirid 6
#घोषणा  _ALLOC_hashed_क्रमmatted_nodes 7
#घोषणा  _ALLOC_old_way 8
#घोषणा  _ALLOC_hundredth_slices 9
#घोषणा  _ALLOC_dirid_groups 10
#घोषणा  _ALLOC_oid_groups 11
#घोषणा  _ALLOC_packing_groups 12

#घोषणा  concentrating_क्रमmatted_nodes(s)	test_bit(_ALLOC_concentrating_क्रमmatted_nodes, &SB_ALLOC_OPTS(s))
#घोषणा  displacing_large_files(s)		test_bit(_ALLOC_displacing_large_files, &SB_ALLOC_OPTS(s))
#घोषणा  displacing_new_packing_localities(s)	test_bit(_ALLOC_displacing_new_packing_localities, &SB_ALLOC_OPTS(s))

#घोषणा SET_OPTION(optname) \
   करो अणु \
	reiserfs_info(s, "block allocator option \"%s\" is set", #optname); \
	set_bit(_ALLOC_ ## optname , &SB_ALLOC_OPTS(s)); \
    पूर्ण जबतक(0)
#घोषणा TEST_OPTION(optname, s) \
    test_bit(_ALLOC_ ## optname , &SB_ALLOC_OPTS(s))

अटल अंतरभूत व्योम get_bit_address(काष्ठा super_block *s,
				   b_blocknr_t block,
				   अचिन्हित पूर्णांक *bmap_nr,
				   अचिन्हित पूर्णांक *offset)
अणु
	/*
	 * It is in the biपंचांगap block number equal to the block
	 * number भागided by the number of bits in a block.
	 */
	*bmap_nr = block >> (s->s_blocksize_bits + 3);
	/* Within that biपंचांगap block it is located at bit offset *offset. */
	*offset = block & ((s->s_blocksize << 3) - 1);
पूर्ण

पूर्णांक is_reusable(काष्ठा super_block *s, b_blocknr_t block, पूर्णांक bit_value)
अणु
	अचिन्हित पूर्णांक bmap, offset;
	अचिन्हित पूर्णांक bmap_count = reiserfs_bmap_count(s);

	अगर (block == 0 || block >= SB_BLOCK_COUNT(s)) अणु
		reiserfs_error(s, "vs-4010",
			       "block number is out of range %lu (%u)",
			       block, SB_BLOCK_COUNT(s));
		वापस 0;
	पूर्ण

	get_bit_address(s, block, &bmap, &offset);

	/*
	 * Old क्रमmat fileप्रणाली? Unlikely, but the biपंचांगaps are all
	 * up front so we need to account क्रम it.
	 */
	अगर (unlikely(test_bit(REISERFS_OLD_FORMAT,
			      &REISERFS_SB(s)->s_properties))) अणु
		b_blocknr_t bmap1 = REISERFS_SB(s)->s_sbh->b_blocknr + 1;
		अगर (block >= bmap1 &&
		    block <= bmap1 + bmap_count) अणु
			reiserfs_error(s, "vs-4019", "bitmap block %lu(%u) "
				       "can't be freed or reused",
				       block, bmap_count);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (offset == 0) अणु
			reiserfs_error(s, "vs-4020", "bitmap block %lu(%u) "
				       "can't be freed or reused",
				       block, bmap_count);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (bmap >= bmap_count) अणु
		reiserfs_error(s, "vs-4030", "bitmap for requested block "
			       "is out of range: block=%lu, bitmap_nr=%u",
			       block, bmap);
		वापस 0;
	पूर्ण

	अगर (bit_value == 0 && block == SB_ROOT_BLOCK(s)) अणु
		reiserfs_error(s, "vs-4050", "this is root block (%u), "
			       "it must be busy", SB_ROOT_BLOCK(s));
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Searches in journal काष्ठाures क्रम a given block number (bmap, off).
 * If block is found in reiserfs journal it suggests next मुक्त block
 * candidate to test.
 */
अटल अंतरभूत पूर्णांक is_block_in_journal(काष्ठा super_block *s, अचिन्हित पूर्णांक bmap,
				      पूर्णांक off, पूर्णांक *next)
अणु
	b_blocknr_t पंचांगp;

	अगर (reiserfs_in_journal(s, bmap, off, 1, &पंचांगp)) अणु
		अगर (पंचांगp) अणु	/* hपूर्णांक supplied */
			*next = पंचांगp;
			PROC_INFO_INC(s, scan_biपंचांगap.in_journal_hपूर्णांक);
		पूर्ण अन्यथा अणु
			(*next) = off + 1;  /* inc offset to aव्योम looping. */
			PROC_INFO_INC(s, scan_biपंचांगap.in_journal_nohपूर्णांक);
		पूर्ण
		PROC_INFO_INC(s, scan_biपंचांगap.retry);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Searches क्रम a winकरोw of zero bits with given minimum and maximum
 * lengths in one biपंचांगap block
 */
अटल पूर्णांक scan_biपंचांगap_block(काष्ठा reiserfs_transaction_handle *th,
			     अचिन्हित पूर्णांक bmap_n, पूर्णांक *beg, पूर्णांक boundary,
			     पूर्णांक min, पूर्णांक max, पूर्णांक unfm)
अणु
	काष्ठा super_block *s = th->t_super;
	काष्ठा reiserfs_biपंचांगap_info *bi = &SB_AP_BITMAP(s)[bmap_n];
	काष्ठा buffer_head *bh;
	पूर्णांक end, next;
	पूर्णांक org = *beg;

	BUG_ON(!th->t_trans_id);
	RFALSE(bmap_n >= reiserfs_bmap_count(s), "Bitmap %u is out of "
	       "range (0..%u)", bmap_n, reiserfs_bmap_count(s) - 1);
	PROC_INFO_INC(s, scan_biपंचांगap.bmap);

	अगर (!bi) अणु
		reiserfs_error(s, "jdm-4055", "NULL bitmap info pointer "
			       "for bitmap %d", bmap_n);
		वापस 0;
	पूर्ण

	bh = reiserfs_पढ़ो_biपंचांगap_block(s, bmap_n);
	अगर (bh == शून्य)
		वापस 0;

	जबतक (1) अणु
cont:
		अगर (bi->मुक्त_count < min) अणु
			brअन्यथा(bh);
			वापस 0;	/* No मुक्त blocks in this biपंचांगap */
		पूर्ण

		/* search क्रम a first zero bit -- beginning of a winकरोw */
		*beg = reiserfs_find_next_zero_le_bit
		    ((अचिन्हित दीर्घ *)(bh->b_data), boundary, *beg);

		/*
		 * search क्रम a zero bit fails or the rest of biपंचांगap block
		 * cannot contain a zero winकरोw of minimum size
		 */
		अगर (*beg + min > boundary) अणु
			brअन्यथा(bh);
			वापस 0;
		पूर्ण

		अगर (unfm && is_block_in_journal(s, bmap_n, *beg, beg))
			जारी;
		/* first zero bit found; we check next bits */
		क्रम (end = *beg + 1;; end++) अणु
			अगर (end >= *beg + max || end >= boundary
			    || reiserfs_test_le_bit(end, bh->b_data)) अणु
				next = end;
				अवरोध;
			पूर्ण

			/*
			 * finding the other end of zero bit winकरोw requires
			 * looking पूर्णांकo journal काष्ठाures (in हाल of
			 * searching क्रम मुक्त blocks क्रम unक्रमmatted nodes)
			 */
			अगर (unfm && is_block_in_journal(s, bmap_n, end, &next))
				अवरोध;
		पूर्ण

		/*
		 * now (*beg) poपूर्णांकs to beginning of zero bits winकरोw,
		 * (end) poपूर्णांकs to one bit after the winकरोw end
		 */

		/* found winकरोw of proper size */
		अगर (end - *beg >= min) अणु
			पूर्णांक i;
			reiserfs_prepare_क्रम_journal(s, bh, 1);
			/*
			 * try to set all blocks used checking are
			 * they still मुक्त
			 */
			क्रम (i = *beg; i < end; i++) अणु
				/* Don't check in journal again. */
				अगर (reiserfs_test_and_set_le_bit
				    (i, bh->b_data)) अणु
					/*
					 * bit was set by another process जबतक
					 * we slept in prepare_क्रम_journal()
					 */
					PROC_INFO_INC(s, scan_biपंचांगap.stolen);

					/*
					 * we can जारी with smaller set
					 * of allocated blocks, अगर length of
					 * this set is more or equal to `min'
					 */
					अगर (i >= *beg + min) अणु
						end = i;
						अवरोध;
					पूर्ण

					/*
					 * otherwise we clear all bit
					 * were set ...
					 */
					जबतक (--i >= *beg)
						reiserfs_clear_le_bit
						    (i, bh->b_data);
					reiserfs_restore_prepared_buffer(s, bh);
					*beg = org;

					/*
					 * Search again in current block
					 * from beginning
					 */
					जाओ cont;
				पूर्ण
			पूर्ण
			bi->मुक्त_count -= (end - *beg);
			journal_mark_dirty(th, bh);
			brअन्यथा(bh);

			/* मुक्त block count calculation */
			reiserfs_prepare_क्रम_journal(s, SB_BUFFER_WITH_SB(s),
						     1);
			PUT_SB_FREE_BLOCKS(s, SB_FREE_BLOCKS(s) - (end - *beg));
			journal_mark_dirty(th, SB_BUFFER_WITH_SB(s));

			वापस end - (*beg);
		पूर्ण अन्यथा अणु
			*beg = next;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bmap_hash_id(काष्ठा super_block *s, u32 id)
अणु
	अक्षर *hash_in = शून्य;
	अचिन्हित दीर्घ hash;
	अचिन्हित bm;

	अगर (id <= 2) अणु
		bm = 1;
	पूर्ण अन्यथा अणु
		hash_in = (अक्षर *)(&id);
		hash = keyed_hash(hash_in, 4);
		bm = hash % reiserfs_bmap_count(s);
		अगर (!bm)
			bm = 1;
	पूर्ण
	/* this can only be true when SB_BMAP_NR = 1 */
	अगर (bm >= reiserfs_bmap_count(s))
		bm = 0;
	वापस bm;
पूर्ण

/*
 * hashes the id and then वापसs > 0 अगर the block group क्रम the
 * corresponding hash is full
 */
अटल अंतरभूत पूर्णांक block_group_used(काष्ठा super_block *s, u32 id)
अणु
	पूर्णांक bm = bmap_hash_id(s, id);
	काष्ठा reiserfs_biपंचांगap_info *info = &SB_AP_BITMAP(s)[bm];

	/*
	 * If we करोn't have cached information on this bitmap block, we're
	 * going to have to load it later anyway. Loading it here allows us
	 * to make a better decision. This favors दीर्घ-term perक्रमmance gain
	 * with a better on-disk layout vs. a लघु term gain of skipping the
	 * पढ़ो and potentially having a bad placement.
	 */
	अगर (info->मुक्त_count == अच_पूर्णांक_उच्च) अणु
		काष्ठा buffer_head *bh = reiserfs_पढ़ो_biपंचांगap_block(s, bm);
		brअन्यथा(bh);
	पूर्ण

	अगर (info->मुक्त_count > ((s->s_blocksize << 3) * 60 / 100)) अणु
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * the packing is वापसed in disk byte order
 */
__le32 reiserfs_choose_packing(काष्ठा inode * dir)
अणु
	__le32 packing;
	अगर (TEST_OPTION(packing_groups, dir->i_sb)) अणु
		u32 parent_dir = le32_to_cpu(INODE_PKEY(dir)->k_dir_id);
		/*
		 * some versions of reiserfsck expect packing locality 1 to be
		 * special
		 */
		अगर (parent_dir == 1 || block_group_used(dir->i_sb, parent_dir))
			packing = INODE_PKEY(dir)->k_objectid;
		अन्यथा
			packing = INODE_PKEY(dir)->k_dir_id;
	पूर्ण अन्यथा
		packing = INODE_PKEY(dir)->k_objectid;
	वापस packing;
पूर्ण

/*
 * Tries to find contiguous zero bit winकरोw (given size) in given region of
 * biपंचांगap and place new blocks there. Returns number of allocated blocks.
 */
अटल पूर्णांक scan_biपंचांगap(काष्ठा reiserfs_transaction_handle *th,
		       b_blocknr_t * start, b_blocknr_t finish,
		       पूर्णांक min, पूर्णांक max, पूर्णांक unfm, sector_t file_block)
अणु
	पूर्णांक nr_allocated = 0;
	काष्ठा super_block *s = th->t_super;
	अचिन्हित पूर्णांक bm, off;
	अचिन्हित पूर्णांक end_bm, end_off;
	अचिन्हित पूर्णांक off_max = s->s_blocksize << 3;

	BUG_ON(!th->t_trans_id);
	PROC_INFO_INC(s, scan_biपंचांगap.call);

	/* No poपूर्णांक in looking क्रम more मुक्त blocks */
	अगर (SB_FREE_BLOCKS(s) <= 0)
		वापस 0;

	get_bit_address(s, *start, &bm, &off);
	get_bit_address(s, finish, &end_bm, &end_off);
	अगर (bm > reiserfs_bmap_count(s))
		वापस 0;
	अगर (end_bm > reiserfs_bmap_count(s))
		end_bm = reiserfs_bmap_count(s);

	/*
	 * When the biपंचांगap is more than 10% मुक्त, anyone can allocate.
	 * When it's less than 10% मुक्त, only files that alपढ़ोy use the
	 * biपंचांगap are allowed. Once we pass 80% full, this restriction
	 * is lअगरted.
	 *
	 * We करो this so that files that grow later still have space बंद to
	 * their original allocation. This improves locality, and presumably
	 * perक्रमmance as a result.
	 *
	 * This is only an allocation policy and करोes not make up क्रम getting a
	 * bad hपूर्णांक. Decent hपूर्णांकing must be implemented क्रम this to work well.
	 */
	अगर (TEST_OPTION(skip_busy, s)
	    && SB_FREE_BLOCKS(s) > SB_BLOCK_COUNT(s) / 20) अणु
		क्रम (; bm < end_bm; bm++, off = 0) अणु
			अगर ((off && (!unfm || (file_block != 0)))
			    || SB_AP_BITMAP(s)[bm].मुक्त_count >
			    (s->s_blocksize << 3) / 10)
				nr_allocated =
				    scan_biपंचांगap_block(th, bm, &off, off_max,
						      min, max, unfm);
			अगर (nr_allocated)
				जाओ ret;
		पूर्ण
		/* we know from above that start is a reasonable number */
		get_bit_address(s, *start, &bm, &off);
	पूर्ण

	क्रम (; bm < end_bm; bm++, off = 0) अणु
		nr_allocated =
		    scan_biपंचांगap_block(th, bm, &off, off_max, min, max, unfm);
		अगर (nr_allocated)
			जाओ ret;
	पूर्ण

	nr_allocated =
	    scan_biपंचांगap_block(th, bm, &off, end_off + 1, min, max, unfm);

ret:
	*start = bm * off_max + off;
	वापस nr_allocated;

पूर्ण

अटल व्योम _reiserfs_मुक्त_block(काष्ठा reiserfs_transaction_handle *th,
				 काष्ठा inode *inode, b_blocknr_t block,
				 पूर्णांक क्रम_unक्रमmatted)
अणु
	काष्ठा super_block *s = th->t_super;
	काष्ठा reiserfs_super_block *rs;
	काष्ठा buffer_head *sbh, *bmbh;
	काष्ठा reiserfs_biपंचांगap_info *apbi;
	अचिन्हित पूर्णांक nr, offset;

	BUG_ON(!th->t_trans_id);
	PROC_INFO_INC(s, मुक्त_block);
	rs = SB_DISK_SUPER_BLOCK(s);
	sbh = SB_BUFFER_WITH_SB(s);
	apbi = SB_AP_BITMAP(s);

	get_bit_address(s, block, &nr, &offset);

	अगर (nr >= reiserfs_bmap_count(s)) अणु
		reiserfs_error(s, "vs-4075", "block %lu is out of range",
			       block);
		वापस;
	पूर्ण

	bmbh = reiserfs_पढ़ो_biपंचांगap_block(s, nr);
	अगर (!bmbh)
		वापस;

	reiserfs_prepare_क्रम_journal(s, bmbh, 1);

	/* clear bit क्रम the given block in bit map */
	अगर (!reiserfs_test_and_clear_le_bit(offset, bmbh->b_data)) अणु
		reiserfs_error(s, "vs-4080",
			       "block %lu: bit already cleared", block);
	पूर्ण
	apbi[nr].मुक्त_count++;
	journal_mark_dirty(th, bmbh);
	brअन्यथा(bmbh);

	reiserfs_prepare_क्रम_journal(s, sbh, 1);
	/* update super block */
	set_sb_मुक्त_blocks(rs, sb_मुक्त_blocks(rs) + 1);

	journal_mark_dirty(th, sbh);
	अगर (क्रम_unक्रमmatted) अणु
		पूर्णांक depth = reiserfs_ग_लिखो_unlock_nested(s);
		dquot_मुक्त_block_nodirty(inode, 1);
		reiserfs_ग_लिखो_lock_nested(s, depth);
	पूर्ण
पूर्ण

व्योम reiserfs_मुक्त_block(काष्ठा reiserfs_transaction_handle *th,
			 काष्ठा inode *inode, b_blocknr_t block,
			 पूर्णांक क्रम_unक्रमmatted)
अणु
	काष्ठा super_block *s = th->t_super;

	BUG_ON(!th->t_trans_id);
	RFALSE(!s, "vs-4061: trying to free block on nonexistent device");
	अगर (!is_reusable(s, block, 1))
		वापस;

	अगर (block > sb_block_count(REISERFS_SB(s)->s_rs)) अणु
		reiserfs_error(th->t_super, "bitmap-4072",
			       "Trying to free block outside file system "
			       "boundaries (%lu > %lu)",
			       block, sb_block_count(REISERFS_SB(s)->s_rs));
		वापस;
	पूर्ण
	/* mark it beक्रमe we clear it, just in हाल */
	journal_mark_मुक्तd(th, s, block);
	_reiserfs_मुक्त_block(th, inode, block, क्रम_unक्रमmatted);
पूर्ण

/* pपुनः_स्मृतिated blocks करोn't need to be run through journal_mark_मुक्तd */
अटल व्योम reiserfs_मुक्त_pपुनः_स्मृति_block(काष्ठा reiserfs_transaction_handle *th,
					 काष्ठा inode *inode, b_blocknr_t block)
अणु
	BUG_ON(!th->t_trans_id);
	RFALSE(!th->t_super,
	       "vs-4060: trying to free block on nonexistent device");
	अगर (!is_reusable(th->t_super, block, 1))
		वापस;
	_reiserfs_मुक्त_block(th, inode, block, 1);
पूर्ण

अटल व्योम __discard_pपुनः_स्मृति(काष्ठा reiserfs_transaction_handle *th,
			       काष्ठा reiserfs_inode_info *ei)
अणु
	अचिन्हित दीर्घ save = ei->i_pपुनः_स्मृति_block;
	पूर्णांक dirty = 0;
	काष्ठा inode *inode = &ei->vfs_inode;

	BUG_ON(!th->t_trans_id);
#अगर_घोषित CONFIG_REISERFS_CHECK
	अगर (ei->i_pपुनः_स्मृति_count < 0)
		reiserfs_error(th->t_super, "zam-4001",
			       "inode has negative prealloc blocks count.");
#पूर्ण_अगर
	जबतक (ei->i_pपुनः_स्मृति_count > 0) अणु
		b_blocknr_t block_to_मुक्त;

		/*
		 * reiserfs_मुक्त_pपुनः_स्मृति_block can drop the ग_लिखो lock,
		 * which could allow another caller to मुक्त the same block.
		 * We can protect against it by modअगरying the pपुनः_स्मृति
		 * state beक्रमe calling it.
		 */
		block_to_मुक्त = ei->i_pपुनः_स्मृति_block++;
		ei->i_pपुनः_स्मृति_count--;
		reiserfs_मुक्त_pपुनः_स्मृति_block(th, inode, block_to_मुक्त);
		dirty = 1;
	पूर्ण
	अगर (dirty)
		reiserfs_update_sd(th, inode);
	ei->i_pपुनः_स्मृति_block = save;
	list_del_init(&ei->i_pपुनः_स्मृति_list);
पूर्ण

/* FIXME: It should be अंतरभूत function */
व्योम reiserfs_discard_pपुनः_स्मृति(काष्ठा reiserfs_transaction_handle *th,
			       काष्ठा inode *inode)
अणु
	काष्ठा reiserfs_inode_info *ei = REISERFS_I(inode);

	BUG_ON(!th->t_trans_id);
	अगर (ei->i_pपुनः_स्मृति_count)
		__discard_pपुनः_स्मृति(th, ei);
पूर्ण

व्योम reiserfs_discard_all_pपुनः_स्मृति(काष्ठा reiserfs_transaction_handle *th)
अणु
	काष्ठा list_head *plist = &SB_JOURNAL(th->t_super)->j_pपुनः_स्मृति_list;

	BUG_ON(!th->t_trans_id);
	जबतक (!list_empty(plist)) अणु
		काष्ठा reiserfs_inode_info *ei;
		ei = list_entry(plist->next, काष्ठा reiserfs_inode_info,
				i_pपुनः_स्मृति_list);
#अगर_घोषित CONFIG_REISERFS_CHECK
		अगर (!ei->i_pपुनः_स्मृति_count) अणु
			reiserfs_error(th->t_super, "zam-4001",
				       "inode is in prealloc list but has "
				       "no preallocated blocks.");
		पूर्ण
#पूर्ण_अगर
		__discard_pपुनः_स्मृति(th, ei);
	पूर्ण
पूर्ण

व्योम reiserfs_init_alloc_options(काष्ठा super_block *s)
अणु
	set_bit(_ALLOC_skip_busy, &SB_ALLOC_OPTS(s));
	set_bit(_ALLOC_dirid_groups, &SB_ALLOC_OPTS(s));
	set_bit(_ALLOC_packing_groups, &SB_ALLOC_OPTS(s));
पूर्ण

/* block allocator related options are parsed here */
पूर्णांक reiserfs_parse_alloc_options(काष्ठा super_block *s, अक्षर *options)
अणु
	अक्षर *this_अक्षर, *value;

	/* clear शेष settings */
	REISERFS_SB(s)->s_alloc_options.bits = 0;

	जबतक ((this_अक्षर = strsep(&options, ":")) != शून्य) अणु
		अगर ((value = म_अक्षर(this_अक्षर, '=')) != शून्य)
			*value++ = 0;

		अगर (!म_भेद(this_अक्षर, "concentrating_formatted_nodes")) अणु
			पूर्णांक temp;
			SET_OPTION(concentrating_क्रमmatted_nodes);
			temp = (value
				&& *value) ? simple_म_से_अदीर्घ(value, &value,
							    0) : 10;
			अगर (temp <= 0 || temp > 100) अणु
				REISERFS_SB(s)->s_alloc_options.border = 10;
			पूर्ण अन्यथा अणु
				REISERFS_SB(s)->s_alloc_options.border =
				    100 / temp;
			पूर्ण
			जारी;
		पूर्ण
		अगर (!म_भेद(this_अक्षर, "displacing_large_files")) अणु
			SET_OPTION(displacing_large_files);
			REISERFS_SB(s)->s_alloc_options.large_file_size =
			    (value
			     && *value) ? simple_म_से_अदीर्घ(value, &value, 0) : 16;
			जारी;
		पूर्ण
		अगर (!म_भेद(this_अक्षर, "displacing_new_packing_localities")) अणु
			SET_OPTION(displacing_new_packing_localities);
			जारी;
		पूर्ण

		अगर (!म_भेद(this_अक्षर, "old_hashed_relocation")) अणु
			SET_OPTION(old_hashed_relocation);
			जारी;
		पूर्ण

		अगर (!म_भेद(this_अक्षर, "new_hashed_relocation")) अणु
			SET_OPTION(new_hashed_relocation);
			जारी;
		पूर्ण

		अगर (!म_भेद(this_अक्षर, "dirid_groups")) अणु
			SET_OPTION(dirid_groups);
			जारी;
		पूर्ण
		अगर (!म_भेद(this_अक्षर, "oid_groups")) अणु
			SET_OPTION(oid_groups);
			जारी;
		पूर्ण
		अगर (!म_भेद(this_अक्षर, "packing_groups")) अणु
			SET_OPTION(packing_groups);
			जारी;
		पूर्ण
		अगर (!म_भेद(this_अक्षर, "hashed_formatted_nodes")) अणु
			SET_OPTION(hashed_क्रमmatted_nodes);
			जारी;
		पूर्ण

		अगर (!म_भेद(this_अक्षर, "skip_busy")) अणु
			SET_OPTION(skip_busy);
			जारी;
		पूर्ण

		अगर (!म_भेद(this_अक्षर, "hundredth_slices")) अणु
			SET_OPTION(hundredth_slices);
			जारी;
		पूर्ण

		अगर (!म_भेद(this_अक्षर, "old_way")) अणु
			SET_OPTION(old_way);
			जारी;
		पूर्ण

		अगर (!म_भेद(this_अक्षर, "displace_based_on_dirid")) अणु
			SET_OPTION(displace_based_on_dirid);
			जारी;
		पूर्ण

		अगर (!म_भेद(this_अक्षर, "preallocmin")) अणु
			REISERFS_SB(s)->s_alloc_options.pपुनः_स्मृतिmin =
			    (value
			     && *value) ? simple_म_से_अदीर्घ(value, &value, 0) : 4;
			जारी;
		पूर्ण

		अगर (!म_भेद(this_अक्षर, "preallocsize")) अणु
			REISERFS_SB(s)->s_alloc_options.pपुनः_स्मृतिsize =
			    (value
			     && *value) ? simple_म_से_अदीर्घ(value, &value,
							 0) :
			    PREALLOCATION_SIZE;
			जारी;
		पूर्ण

		reiserfs_warning(s, "zam-4001", "unknown option - %s",
				 this_अक्षर);
		वापस 1;
	पूर्ण

	reiserfs_info(s, "allocator options = [%08x]\n", SB_ALLOC_OPTS(s));
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_sep(काष्ठा seq_file *seq, पूर्णांक *first)
अणु
	अगर (!*first)
		seq_माला_दो(seq, ":");
	अन्यथा
		*first = 0;
पूर्ण

व्योम show_alloc_options(काष्ठा seq_file *seq, काष्ठा super_block *s)
अणु
	पूर्णांक first = 1;

	अगर (SB_ALLOC_OPTS(s) == ((1 << _ALLOC_skip_busy) |
		(1 << _ALLOC_dirid_groups) | (1 << _ALLOC_packing_groups)))
		वापस;

	seq_माला_दो(seq, ",alloc=");

	अगर (TEST_OPTION(concentrating_क्रमmatted_nodes, s)) अणु
		prपूर्णांक_sep(seq, &first);
		अगर (REISERFS_SB(s)->s_alloc_options.border != 10) अणु
			seq_म_लिखो(seq, "concentrating_formatted_nodes=%d",
				100 / REISERFS_SB(s)->s_alloc_options.border);
		पूर्ण अन्यथा
			seq_माला_दो(seq, "concentrating_formatted_nodes");
	पूर्ण
	अगर (TEST_OPTION(displacing_large_files, s)) अणु
		prपूर्णांक_sep(seq, &first);
		अगर (REISERFS_SB(s)->s_alloc_options.large_file_size != 16) अणु
			seq_म_लिखो(seq, "displacing_large_files=%lu",
			    REISERFS_SB(s)->s_alloc_options.large_file_size);
		पूर्ण अन्यथा
			seq_माला_दो(seq, "displacing_large_files");
	पूर्ण
	अगर (TEST_OPTION(displacing_new_packing_localities, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "displacing_new_packing_localities");
	पूर्ण
	अगर (TEST_OPTION(old_hashed_relocation, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "old_hashed_relocation");
	पूर्ण
	अगर (TEST_OPTION(new_hashed_relocation, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "new_hashed_relocation");
	पूर्ण
	अगर (TEST_OPTION(dirid_groups, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "dirid_groups");
	पूर्ण
	अगर (TEST_OPTION(oid_groups, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "oid_groups");
	पूर्ण
	अगर (TEST_OPTION(packing_groups, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "packing_groups");
	पूर्ण
	अगर (TEST_OPTION(hashed_क्रमmatted_nodes, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "hashed_formatted_nodes");
	पूर्ण
	अगर (TEST_OPTION(skip_busy, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "skip_busy");
	पूर्ण
	अगर (TEST_OPTION(hundredth_slices, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "hundredth_slices");
	पूर्ण
	अगर (TEST_OPTION(old_way, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "old_way");
	पूर्ण
	अगर (TEST_OPTION(displace_based_on_dirid, s)) अणु
		prपूर्णांक_sep(seq, &first);
		seq_माला_दो(seq, "displace_based_on_dirid");
	पूर्ण
	अगर (REISERFS_SB(s)->s_alloc_options.pपुनः_स्मृतिmin != 0) अणु
		prपूर्णांक_sep(seq, &first);
		seq_म_लिखो(seq, "preallocmin=%d",
				REISERFS_SB(s)->s_alloc_options.pपुनः_स्मृतिmin);
	पूर्ण
	अगर (REISERFS_SB(s)->s_alloc_options.pपुनः_स्मृतिsize != 17) अणु
		prपूर्णांक_sep(seq, &first);
		seq_म_लिखो(seq, "preallocsize=%d",
				REISERFS_SB(s)->s_alloc_options.pपुनः_स्मृतिsize);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम new_hashed_relocation(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	अक्षर *hash_in;

	अगर (hपूर्णांक->क्रमmatted_node) अणु
		hash_in = (अक्षर *)&hपूर्णांक->key.k_dir_id;
	पूर्ण अन्यथा अणु
		अगर (!hपूर्णांक->inode) अणु
			/*hपूर्णांक->search_start = hपूर्णांक->beg;*/
			hash_in = (अक्षर *)&hपूर्णांक->key.k_dir_id;
		पूर्ण अन्यथा
		    अगर (TEST_OPTION(displace_based_on_dirid, hपूर्णांक->th->t_super))
			hash_in = (अक्षर *)(&INODE_PKEY(hपूर्णांक->inode)->k_dir_id);
		अन्यथा
			hash_in =
			    (अक्षर *)(&INODE_PKEY(hपूर्णांक->inode)->k_objectid);
	पूर्ण

	hपूर्णांक->search_start =
	    hपूर्णांक->beg + keyed_hash(hash_in, 4) % (hपूर्णांक->end - hपूर्णांक->beg);
पूर्ण

/*
 * Relocation based on dirid, hashing them पूर्णांकo a given biपंचांगap block
 * files. Formatted nodes are unaffected, a separate policy covers them
 */
अटल व्योम dirid_groups(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	अचिन्हित दीर्घ hash;
	__u32 dirid = 0;
	पूर्णांक bm = 0;
	काष्ठा super_block *sb = hपूर्णांक->th->t_super;

	अगर (hपूर्णांक->inode)
		dirid = le32_to_cpu(INODE_PKEY(hपूर्णांक->inode)->k_dir_id);
	अन्यथा अगर (hपूर्णांक->क्रमmatted_node)
		dirid = hपूर्णांक->key.k_dir_id;

	अगर (dirid) अणु
		bm = bmap_hash_id(sb, dirid);
		hash = bm * (sb->s_blocksize << 3);
		/* give a portion of the block group to metadata */
		अगर (hपूर्णांक->inode)
			hash += sb->s_blocksize / 2;
		hपूर्णांक->search_start = hash;
	पूर्ण
पूर्ण

/*
 * Relocation based on oid, hashing them पूर्णांकo a given biपंचांगap block
 * files. Formatted nodes are unaffected, a separate policy covers them
 */
अटल व्योम oid_groups(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	अगर (hपूर्णांक->inode) अणु
		अचिन्हित दीर्घ hash;
		__u32 oid;
		__u32 dirid;
		पूर्णांक bm;

		dirid = le32_to_cpu(INODE_PKEY(hपूर्णांक->inode)->k_dir_id);

		/*
		 * keep the root dir and it's first set of subdirs बंद to
		 * the start of the disk
		 */
		अगर (dirid <= 2)
			hash = (hपूर्णांक->inode->i_sb->s_blocksize << 3);
		अन्यथा अणु
			oid = le32_to_cpu(INODE_PKEY(hपूर्णांक->inode)->k_objectid);
			bm = bmap_hash_id(hपूर्णांक->inode->i_sb, oid);
			hash = bm * (hपूर्णांक->inode->i_sb->s_blocksize << 3);
		पूर्ण
		hपूर्णांक->search_start = hash;
	पूर्ण
पूर्ण

/*
 * वापसs 1 अगर it finds an indirect item and माला_लो valid hपूर्णांक info
 * from it, otherwise 0
 */
अटल पूर्णांक get_left_neighbor(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	काष्ठा treepath *path;
	काष्ठा buffer_head *bh;
	काष्ठा item_head *ih;
	पूर्णांक pos_in_item;
	__le32 *item;
	पूर्णांक ret = 0;

	/*
	 * reiserfs code can call this function w/o poपूर्णांकer to path
	 * काष्ठाure supplied; then we rely on supplied search_start
	 */
	अगर (!hपूर्णांक->path)
		वापस 0;

	path = hपूर्णांक->path;
	bh = get_last_bh(path);
	RFALSE(!bh, "green-4002: Illegal path specified to get_left_neighbor");
	ih = tp_item_head(path);
	pos_in_item = path->pos_in_item;
	item = tp_item_body(path);

	hपूर्णांक->search_start = bh->b_blocknr;

	/*
	 * क्रम indirect item: go to left and look क्रम the first non-hole entry
	 * in the indirect item
	 */
	अगर (!hपूर्णांक->क्रमmatted_node && is_indirect_le_ih(ih)) अणु
		अगर (pos_in_item == I_UNFM_NUM(ih))
			pos_in_item--;
		जबतक (pos_in_item >= 0) अणु
			पूर्णांक t = get_block_num(item, pos_in_item);
			अगर (t) अणु
				hपूर्णांक->search_start = t;
				ret = 1;
				अवरोध;
			पूर्ण
			pos_in_item--;
		पूर्ण
	पूर्ण

	/* करोes result value fit पूर्णांकo specअगरied region? */
	वापस ret;
पूर्ण

/*
 * should be, अगर क्रमmatted node, then try to put on first part of the device
 * specअगरied as number of percent with mount option device, अन्यथा try to put
 * on last of device.  This is not to say it is good code to करो so,
 * but the effect should be measured.
 */
अटल अंतरभूत व्योम set_border_in_hपूर्णांक(काष्ठा super_block *s,
				      reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	b_blocknr_t border =
	    SB_BLOCK_COUNT(s) / REISERFS_SB(s)->s_alloc_options.border;

	अगर (hपूर्णांक->क्रमmatted_node)
		hपूर्णांक->end = border - 1;
	अन्यथा
		hपूर्णांक->beg = border;
पूर्ण

अटल अंतरभूत व्योम displace_large_file(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	अगर (TEST_OPTION(displace_based_on_dirid, hपूर्णांक->th->t_super))
		hपूर्णांक->search_start =
		    hपूर्णांक->beg +
		    keyed_hash((अक्षर *)(&INODE_PKEY(hपूर्णांक->inode)->k_dir_id),
			       4) % (hपूर्णांक->end - hपूर्णांक->beg);
	अन्यथा
		hपूर्णांक->search_start =
		    hपूर्णांक->beg +
		    keyed_hash((अक्षर *)(&INODE_PKEY(hपूर्णांक->inode)->k_objectid),
			       4) % (hपूर्णांक->end - hपूर्णांक->beg);
पूर्ण

अटल अंतरभूत व्योम hash_क्रमmatted_node(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	अक्षर *hash_in;

	अगर (!hपूर्णांक->inode)
		hash_in = (अक्षर *)&hपूर्णांक->key.k_dir_id;
	अन्यथा अगर (TEST_OPTION(displace_based_on_dirid, hपूर्णांक->th->t_super))
		hash_in = (अक्षर *)(&INODE_PKEY(hपूर्णांक->inode)->k_dir_id);
	अन्यथा
		hash_in = (अक्षर *)(&INODE_PKEY(hपूर्णांक->inode)->k_objectid);

	hपूर्णांक->search_start =
	    hपूर्णांक->beg + keyed_hash(hash_in, 4) % (hपूर्णांक->end - hपूर्णांक->beg);
पूर्ण

अटल अंतरभूत पूर्णांक
this_blocknr_allocation_would_make_it_a_large_file(reiserfs_blocknr_hपूर्णांक_t *
						   hपूर्णांक)
अणु
	वापस hपूर्णांक->block ==
	    REISERFS_SB(hपूर्णांक->th->t_super)->s_alloc_options.large_file_size;
पूर्ण

#अगर_घोषित DISPLACE_NEW_PACKING_LOCALITIES
अटल अंतरभूत व्योम displace_new_packing_locality(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	काष्ठा in_core_key *key = &hपूर्णांक->key;

	hपूर्णांक->th->displace_new_blocks = 0;
	hपूर्णांक->search_start =
	    hपूर्णांक->beg + keyed_hash((अक्षर *)(&key->k_objectid),
				   4) % (hपूर्णांक->end - hपूर्णांक->beg);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक old_hashed_relocation(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	b_blocknr_t border;
	u32 hash_in;

	अगर (hपूर्णांक->क्रमmatted_node || hपूर्णांक->inode == शून्य) अणु
		वापस 0;
	पूर्ण

	hash_in = le32_to_cpu((INODE_PKEY(hपूर्णांक->inode))->k_dir_id);
	border =
	    hपूर्णांक->beg + (u32) keyed_hash(((अक्षर *)(&hash_in)),
					 4) % (hपूर्णांक->end - hपूर्णांक->beg - 1);
	अगर (border > hपूर्णांक->search_start)
		hपूर्णांक->search_start = border;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक old_way(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	b_blocknr_t border;

	अगर (hपूर्णांक->क्रमmatted_node || hपूर्णांक->inode == शून्य) अणु
		वापस 0;
	पूर्ण

	border =
	    hपूर्णांक->beg +
	    le32_to_cpu(INODE_PKEY(hपूर्णांक->inode)->k_dir_id) % (hपूर्णांक->end -
							      hपूर्णांक->beg);
	अगर (border > hपूर्णांक->search_start)
		hपूर्णांक->search_start = border;

	वापस 1;
पूर्ण

अटल अंतरभूत व्योम hundredth_slices(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	काष्ठा in_core_key *key = &hपूर्णांक->key;
	b_blocknr_t slice_start;

	slice_start =
	    (keyed_hash((अक्षर *)(&key->k_dir_id), 4) % 100) * (hपूर्णांक->end / 100);
	अगर (slice_start > hपूर्णांक->search_start
	    || slice_start + (hपूर्णांक->end / 100) <= hपूर्णांक->search_start) अणु
		hपूर्णांक->search_start = slice_start;
	पूर्ण
पूर्ण

अटल व्योम determine_search_start(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक,
				   पूर्णांक amount_needed)
अणु
	काष्ठा super_block *s = hपूर्णांक->th->t_super;
	पूर्णांक unfm_hपूर्णांक;

	hपूर्णांक->beg = 0;
	hपूर्णांक->end = SB_BLOCK_COUNT(s) - 1;

	/* This is क्रमmer border algorithm. Now with tunable border offset */
	अगर (concentrating_क्रमmatted_nodes(s))
		set_border_in_hपूर्णांक(s, hपूर्णांक);

#अगर_घोषित DISPLACE_NEW_PACKING_LOCALITIES
	/*
	 * whenever we create a new directory, we displace it.  At first
	 * we will hash क्रम location, later we might look क्रम a moderately
	 * empty place क्रम it
	 */
	अगर (displacing_new_packing_localities(s)
	    && hपूर्णांक->th->displace_new_blocks) अणु
		displace_new_packing_locality(hपूर्णांक);

		/*
		 * we करो not जारी determine_search_start,
		 * अगर new packing locality is being displaced
		 */
		वापस;
	पूर्ण
#पूर्ण_अगर

	/*
	 * all persons should feel encouraged to add more special हालs
	 * here and test them
	 */

	अगर (displacing_large_files(s) && !hपूर्णांक->क्रमmatted_node
	    && this_blocknr_allocation_would_make_it_a_large_file(hपूर्णांक)) अणु
		displace_large_file(hपूर्णांक);
		वापस;
	पूर्ण

	/*
	 * अगर none of our special हालs is relevant, use the left
	 * neighbor in the tree order of the new node we are allocating क्रम
	 */
	अगर (hपूर्णांक->क्रमmatted_node && TEST_OPTION(hashed_क्रमmatted_nodes, s)) अणु
		hash_क्रमmatted_node(hपूर्णांक);
		वापस;
	पूर्ण

	unfm_hपूर्णांक = get_left_neighbor(hपूर्णांक);

	/*
	 * Mimic old block allocator behaviour, that is अगर VFS allowed क्रम
	 * pपुनः_स्मृतिation, new blocks are displaced based on directory ID.
	 * Also, अगर suggested search_start is less than last pपुनः_स्मृतिated
	 * block, we start searching from it, assuming that HDD dataflow
	 * is faster in क्रमward direction
	 */
	अगर (TEST_OPTION(old_way, s)) अणु
		अगर (!hपूर्णांक->क्रमmatted_node) अणु
			अगर (!reiserfs_hashed_relocation(s))
				old_way(hपूर्णांक);
			अन्यथा अगर (!reiserfs_no_unhashed_relocation(s))
				old_hashed_relocation(hपूर्णांक);

			अगर (hपूर्णांक->inode
			    && hपूर्णांक->search_start <
			    REISERFS_I(hपूर्णांक->inode)->i_pपुनः_स्मृति_block)
				hपूर्णांक->search_start =
				    REISERFS_I(hपूर्णांक->inode)->i_pपुनः_स्मृति_block;
		पूर्ण
		वापस;
	पूर्ण

	/* This is an approach proposed by Hans */
	अगर (TEST_OPTION(hundredth_slices, s)
	    && !(displacing_large_files(s) && !hपूर्णांक->क्रमmatted_node)) अणु
		hundredth_slices(hपूर्णांक);
		वापस;
	पूर्ण

	/* old_hashed_relocation only works on unक्रमmatted */
	अगर (!unfm_hपूर्णांक && !hपूर्णांक->क्रमmatted_node &&
	    TEST_OPTION(old_hashed_relocation, s)) अणु
		old_hashed_relocation(hपूर्णांक);
	पूर्ण

	/* new_hashed_relocation works with both क्रमmatted/unक्रमmatted nodes */
	अगर ((!unfm_hपूर्णांक || hपूर्णांक->क्रमmatted_node) &&
	    TEST_OPTION(new_hashed_relocation, s)) अणु
		new_hashed_relocation(hपूर्णांक);
	पूर्ण

	/* dirid grouping works only on unक्रमmatted nodes */
	अगर (!unfm_hपूर्णांक && !hपूर्णांक->क्रमmatted_node && TEST_OPTION(dirid_groups, s)) अणु
		dirid_groups(hपूर्णांक);
	पूर्ण
#अगर_घोषित DISPLACE_NEW_PACKING_LOCALITIES
	अगर (hपूर्णांक->क्रमmatted_node && TEST_OPTION(dirid_groups, s)) अणु
		dirid_groups(hपूर्णांक);
	पूर्ण
#पूर्ण_अगर

	/* oid grouping works only on unक्रमmatted nodes */
	अगर (!unfm_hपूर्णांक && !hपूर्णांक->क्रमmatted_node && TEST_OPTION(oid_groups, s)) अणु
		oid_groups(hपूर्णांक);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक determine_pपुनः_स्मृति_size(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक)
अणु
	/* make minimum size a mount option and benchmark both ways */
	/* we pपुनः_स्मृतिate blocks only क्रम regular files, specअगरic size */
	/* benchmark pपुनः_स्मृतिating always and see what happens */

	hपूर्णांक->pपुनः_स्मृति_size = 0;

	अगर (!hपूर्णांक->क्रमmatted_node && hपूर्णांक->pपुनः_स्मृतिate) अणु
		अगर (S_ISREG(hपूर्णांक->inode->i_mode) && !IS_PRIVATE(hपूर्णांक->inode)
		    && hपूर्णांक->inode->i_size >=
		    REISERFS_SB(hपूर्णांक->th->t_super)->s_alloc_options.
		    pपुनः_स्मृतिmin * hपूर्णांक->inode->i_sb->s_blocksize)
			hपूर्णांक->pपुनः_स्मृति_size =
			    REISERFS_SB(hपूर्णांक->th->t_super)->s_alloc_options.
			    pपुनः_स्मृतिsize - 1;
	पूर्ण
	वापस CARRY_ON;
पूर्ण

अटल अंतरभूत पूर्णांक allocate_without_wrapping_disk(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक,
						 b_blocknr_t * new_blocknrs,
						 b_blocknr_t start,
						 b_blocknr_t finish, पूर्णांक min,
						 पूर्णांक amount_needed,
						 पूर्णांक pपुनः_स्मृति_size)
अणु
	पूर्णांक rest = amount_needed;
	पूर्णांक nr_allocated;

	जबतक (rest > 0 && start <= finish) अणु
		nr_allocated = scan_biपंचांगap(hपूर्णांक->th, &start, finish, min,
					   rest + pपुनः_स्मृति_size,
					   !hपूर्णांक->क्रमmatted_node, hपूर्णांक->block);

		अगर (nr_allocated == 0)	/* no new blocks allocated, वापस */
			अवरोध;

		/* fill मुक्त_blocknrs array first */
		जबतक (rest > 0 && nr_allocated > 0) अणु
			*new_blocknrs++ = start++;
			rest--;
			nr_allocated--;
		पूर्ण

		/* करो we have something to fill pपुनः_स्मृति. array also ? */
		अगर (nr_allocated > 0) अणु
			/*
			 * it means pपुनः_स्मृति_size was greater that 0 and
			 * we करो pपुनः_स्मृतिation
			 */
			list_add(&REISERFS_I(hपूर्णांक->inode)->i_pपुनः_स्मृति_list,
				 &SB_JOURNAL(hपूर्णांक->th->t_super)->
				 j_pपुनः_स्मृति_list);
			REISERFS_I(hपूर्णांक->inode)->i_pपुनः_स्मृति_block = start;
			REISERFS_I(hपूर्णांक->inode)->i_pपुनः_स्मृति_count =
			    nr_allocated;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (amount_needed - rest);
पूर्ण

अटल अंतरभूत पूर्णांक blocknrs_and_pपुनः_स्मृति_arrays_from_search_start
    (reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक, b_blocknr_t * new_blocknrs,
     पूर्णांक amount_needed) अणु
	काष्ठा super_block *s = hपूर्णांक->th->t_super;
	b_blocknr_t start = hपूर्णांक->search_start;
	b_blocknr_t finish = SB_BLOCK_COUNT(s) - 1;
	पूर्णांक passno = 0;
	पूर्णांक nr_allocated = 0;
	पूर्णांक depth;

	determine_pपुनः_स्मृति_size(hपूर्णांक);
	अगर (!hपूर्णांक->क्रमmatted_node) अणु
		पूर्णांक quota_ret;
#अगर_घोषित REISERQUOTA_DEBUG
		reiserfs_debug(s, REISERFS_DEBUG_CODE,
			       "reiserquota: allocating %d blocks id=%u",
			       amount_needed, hपूर्णांक->inode->i_uid);
#पूर्ण_अगर
		depth = reiserfs_ग_लिखो_unlock_nested(s);
		quota_ret =
		    dquot_alloc_block_nodirty(hपूर्णांक->inode, amount_needed);
		अगर (quota_ret) अणु	/* Quota exceeded? */
			reiserfs_ग_लिखो_lock_nested(s, depth);
			वापस QUOTA_EXCEEDED;
		पूर्ण
		अगर (hपूर्णांक->pपुनः_स्मृतिate && hपूर्णांक->pपुनः_स्मृति_size) अणु
#अगर_घोषित REISERQUOTA_DEBUG
			reiserfs_debug(s, REISERFS_DEBUG_CODE,
				       "reiserquota: allocating (prealloc) %d blocks id=%u",
				       hपूर्णांक->pपुनः_स्मृति_size, hपूर्णांक->inode->i_uid);
#पूर्ण_अगर
			quota_ret = dquot_pपुनः_स्मृति_block_nodirty(hपूर्णांक->inode,
							 hपूर्णांक->pपुनः_स्मृति_size);
			अगर (quota_ret)
				hपूर्णांक->pपुनः_स्मृतिate = hपूर्णांक->pपुनः_स्मृति_size = 0;
		पूर्ण
		/* क्रम unक्रमmatted nodes, क्रमce large allocations */
		reiserfs_ग_लिखो_lock_nested(s, depth);
	पूर्ण

	करो अणु
		चयन (passno++) अणु
		हाल 0:	/* Search from hपूर्णांक->search_start to end of disk */
			start = hपूर्णांक->search_start;
			finish = SB_BLOCK_COUNT(s) - 1;
			अवरोध;
		हाल 1:	/* Search from hपूर्णांक->beg to hपूर्णांक->search_start */
			start = hपूर्णांक->beg;
			finish = hपूर्णांक->search_start;
			अवरोध;
		हाल 2:	/* Last chance: Search from 0 to hपूर्णांक->beg */
			start = 0;
			finish = hपूर्णांक->beg;
			अवरोध;
		शेष:
			/* We've tried searching everywhere, not enough space */
			/* Free the blocks */
			अगर (!hपूर्णांक->क्रमmatted_node) अणु
#अगर_घोषित REISERQUOTA_DEBUG
				reiserfs_debug(s, REISERFS_DEBUG_CODE,
					       "reiserquota: freeing (nospace) %d blocks id=%u",
					       amount_needed +
					       hपूर्णांक->pपुनः_स्मृति_size -
					       nr_allocated,
					       hपूर्णांक->inode->i_uid);
#पूर्ण_अगर
				/* Free not allocated blocks */
				depth = reiserfs_ग_लिखो_unlock_nested(s);
				dquot_मुक्त_block_nodirty(hपूर्णांक->inode,
					amount_needed + hपूर्णांक->pपुनः_स्मृति_size -
					nr_allocated);
				reiserfs_ग_लिखो_lock_nested(s, depth);
			पूर्ण
			जबतक (nr_allocated--)
				reiserfs_मुक्त_block(hपूर्णांक->th, hपूर्णांक->inode,
						    new_blocknrs[nr_allocated],
						    !hपूर्णांक->क्रमmatted_node);

			वापस NO_DISK_SPACE;
		पूर्ण
	पूर्ण जबतक ((nr_allocated += allocate_without_wrapping_disk(hपूर्णांक,
								 new_blocknrs +
								 nr_allocated,
								 start, finish,
								 1,
								 amount_needed -
								 nr_allocated,
								 hपूर्णांक->
								 pपुनः_स्मृति_size))
		 < amount_needed);
	अगर (!hपूर्णांक->क्रमmatted_node &&
	    amount_needed + hपूर्णांक->pपुनः_स्मृति_size >
	    nr_allocated + REISERFS_I(hपूर्णांक->inode)->i_pपुनः_स्मृति_count) अणु
		/* Some of pपुनः_स्मृतिation blocks were not allocated */
#अगर_घोषित REISERQUOTA_DEBUG
		reiserfs_debug(s, REISERFS_DEBUG_CODE,
			       "reiserquota: freeing (failed prealloc) %d blocks id=%u",
			       amount_needed + hपूर्णांक->pपुनः_स्मृति_size -
			       nr_allocated -
			       REISERFS_I(hपूर्णांक->inode)->i_pपुनः_स्मृति_count,
			       hपूर्णांक->inode->i_uid);
#पूर्ण_अगर

		depth = reiserfs_ग_लिखो_unlock_nested(s);
		dquot_मुक्त_block_nodirty(hपूर्णांक->inode, amount_needed +
					 hपूर्णांक->pपुनः_स्मृति_size - nr_allocated -
					 REISERFS_I(hपूर्णांक->inode)->
					 i_pपुनः_स्मृति_count);
		reiserfs_ग_लिखो_lock_nested(s, depth);
	पूर्ण

	वापस CARRY_ON;
पूर्ण

/* grab new blocknrs from pपुनः_स्मृतिated list */
/* वापस amount still needed after using them */
अटल पूर्णांक use_pपुनः_स्मृतिated_list_अगर_available(reiserfs_blocknr_hपूर्णांक_t * hपूर्णांक,
					      b_blocknr_t * new_blocknrs,
					      पूर्णांक amount_needed)
अणु
	काष्ठा inode *inode = hपूर्णांक->inode;

	अगर (REISERFS_I(inode)->i_pपुनः_स्मृति_count > 0) अणु
		जबतक (amount_needed) अणु

			*new_blocknrs++ = REISERFS_I(inode)->i_pपुनः_स्मृति_block++;
			REISERFS_I(inode)->i_pपुनः_स्मृति_count--;

			amount_needed--;

			अगर (REISERFS_I(inode)->i_pपुनः_स्मृति_count <= 0) अणु
				list_del(&REISERFS_I(inode)->i_pपुनः_स्मृति_list);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/* वापस amount still needed after using pपुनः_स्मृतिated blocks */
	वापस amount_needed;
पूर्ण

पूर्णांक reiserfs_allocate_blocknrs(reiserfs_blocknr_hपूर्णांक_t *hपूर्णांक,
			       b_blocknr_t *new_blocknrs,
			       पूर्णांक amount_needed,
			       /* Amount of blocks we have alपढ़ोy reserved */
			       पूर्णांक reserved_by_us)
अणु
	पूर्णांक initial_amount_needed = amount_needed;
	पूर्णांक ret;
	काष्ठा super_block *s = hपूर्णांक->th->t_super;

	/* Check अगर there is enough space, taking पूर्णांकo account reserved space */
	अगर (SB_FREE_BLOCKS(s) - REISERFS_SB(s)->reserved_blocks <
	    amount_needed - reserved_by_us)
		वापस NO_DISK_SPACE;
	/* should this be अगर !hपूर्णांक->inode &&  hपूर्णांक->pपुनः_स्मृतिate? */
	/* करो you mean hपूर्णांक->क्रमmatted_node can be हटाओd ? - Zam */
	/*
	 * hपूर्णांक->क्रमmatted_node cannot be हटाओd because we try to access
	 * inode inक्रमmation here, and there is often no inode associated with
	 * metadata allocations - green
	 */

	अगर (!hपूर्णांक->क्रमmatted_node && hपूर्णांक->pपुनः_स्मृतिate) अणु
		amount_needed = use_pपुनः_स्मृतिated_list_अगर_available
		    (hपूर्णांक, new_blocknrs, amount_needed);

		/*
		 * We have all the block numbers we need from the
		 * pपुनः_स्मृति list
		 */
		अगर (amount_needed == 0)
			वापस CARRY_ON;
		new_blocknrs += (initial_amount_needed - amount_needed);
	पूर्ण

	/* find search start and save it in hपूर्णांक काष्ठाure */
	determine_search_start(hपूर्णांक, amount_needed);
	अगर (hपूर्णांक->search_start >= SB_BLOCK_COUNT(s))
		hपूर्णांक->search_start = SB_BLOCK_COUNT(s) - 1;

	/* allocation itself; fill new_blocknrs and pपुनः_स्मृतिation arrays */
	ret = blocknrs_and_pपुनः_स्मृति_arrays_from_search_start
	    (hपूर्णांक, new_blocknrs, amount_needed);

	/*
	 * We used pपुनः_स्मृति. list to fill (partially) new_blocknrs array.
	 * If final allocation fails we need to वापस blocks back to
	 * pपुनः_स्मृति. list or just मुक्त them. -- Zam (I chose second
	 * variant)
	 */
	अगर (ret != CARRY_ON) अणु
		जबतक (amount_needed++ < initial_amount_needed) अणु
			reiserfs_मुक्त_block(hपूर्णांक->th, hपूर्णांक->inode,
					    *(--new_blocknrs), 1);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

व्योम reiserfs_cache_biपंचांगap_metadata(काष्ठा super_block *sb,
                                    काष्ठा buffer_head *bh,
                                    काष्ठा reiserfs_biपंचांगap_info *info)
अणु
	अचिन्हित दीर्घ *cur = (अचिन्हित दीर्घ *)(bh->b_data + bh->b_size);

	/* The first bit must ALWAYS be 1 */
	अगर (!reiserfs_test_le_bit(0, (अचिन्हित दीर्घ *)bh->b_data))
		reiserfs_error(sb, "reiserfs-2025", "bitmap block %lu is "
			       "corrupted: first bit must be 1", bh->b_blocknr);

	info->मुक्त_count = 0;

	जबतक (--cur >= (अचिन्हित दीर्घ *)bh->b_data) अणु
		/* 0 and ~0 are special, we can optimize क्रम them */
		अगर (*cur == 0)
			info->मुक्त_count += BITS_PER_LONG;
		अन्यथा अगर (*cur != ~0L)	/* A mix, investigate */
			info->मुक्त_count += BITS_PER_LONG - hweight_दीर्घ(*cur);
	पूर्ण
पूर्ण

काष्ठा buffer_head *reiserfs_पढ़ो_biपंचांगap_block(काष्ठा super_block *sb,
                                               अचिन्हित पूर्णांक biपंचांगap)
अणु
	b_blocknr_t block = (sb->s_blocksize << 3) * biपंचांगap;
	काष्ठा reiserfs_biपंचांगap_info *info = SB_AP_BITMAP(sb) + biपंचांगap;
	काष्ठा buffer_head *bh;

	/*
	 * Way old क्रमmat fileप्रणालीs had the biपंचांगaps packed up front.
	 * I करोubt there are any of these left, but just in हाल...
	 */
	अगर (unlikely(test_bit(REISERFS_OLD_FORMAT,
			      &REISERFS_SB(sb)->s_properties)))
		block = REISERFS_SB(sb)->s_sbh->b_blocknr + 1 + biपंचांगap;
	अन्यथा अगर (biपंचांगap == 0)
		block = (REISERFS_DISK_OFFSET_IN_BYTES >> sb->s_blocksize_bits) + 1;

	bh = sb_bपढ़ो(sb, block);
	अगर (bh == शून्य)
		reiserfs_warning(sb, "sh-2029: %s: bitmap block (#%u) "
		                 "reading failed", __func__, block);
	अन्यथा अणु
		अगर (buffer_locked(bh)) अणु
			पूर्णांक depth;
			PROC_INFO_INC(sb, scan_biपंचांगap.रुको);
			depth = reiserfs_ग_लिखो_unlock_nested(sb);
			__रुको_on_buffer(bh);
			reiserfs_ग_लिखो_lock_nested(sb, depth);
		पूर्ण
		BUG_ON(!buffer_uptodate(bh));
		BUG_ON(atomic_पढ़ो(&bh->b_count) == 0);

		अगर (info->मुक्त_count == अच_पूर्णांक_उच्च)
			reiserfs_cache_biपंचांगap_metadata(sb, bh, info);
	पूर्ण

	वापस bh;
पूर्ण

पूर्णांक reiserfs_init_biपंचांगap_cache(काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_biपंचांगap_info *biपंचांगap;
	अचिन्हित पूर्णांक bmap_nr = reiserfs_bmap_count(sb);

	biपंचांगap = vदो_स्मृति(array_size(bmap_nr, माप(*biपंचांगap)));
	अगर (biपंचांगap == शून्य)
		वापस -ENOMEM;

	स_रखो(biपंचांगap, 0xff, माप(*biपंचांगap) * bmap_nr);

	SB_AP_BITMAP(sb) = biपंचांगap;

	वापस 0;
पूर्ण

व्योम reiserfs_मुक्त_biपंचांगap_cache(काष्ठा super_block *sb)
अणु
	अगर (SB_AP_BITMAP(sb)) अणु
		vमुक्त(SB_AP_BITMAP(sb));
		SB_AP_BITMAP(sb) = शून्य;
	पूर्ण
पूर्ण
