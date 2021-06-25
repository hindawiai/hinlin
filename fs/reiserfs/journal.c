<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Write ahead logging implementation copyright Chris Mason 2000
 *
 * The background commits make this code very पूर्णांकerrelated, and
 * overly complex.  I need to rethink things a bit....The major players:
 *
 * journal_begin -- call with the number of blocks you expect to log.
 *                  If the current transaction is too
 *		    old, it will block until the current transaction is
 *		    finished, and then start a new one.
 *		    Usually, your transaction will get joined in with
 *                  previous ones क्रम speed.
 *
 * journal_join  -- same as journal_begin, but won't block on the current
 *                  transaction regardless of age.  Don't ever call
 *                  this.  Ever.  There are only two places it should be
 *                  called from, and they are both inside this file.
 *
 * journal_mark_dirty -- adds blocks पूर्णांकo this transaction.  clears any flags
 *                       that might make them get sent to disk
 *                       and then marks them BH_JDirty.  Puts the buffer head
 *                       पूर्णांकo the current transaction hash.
 *
 * journal_end -- अगर the current transaction is batchable, it करोes nothing
 *                   otherwise, it could करो an async/synchronous commit, or
 *                   a full flush of all log and real blocks in the
 *                   transaction.
 *
 * flush_old_commits -- अगर the current transaction is too old, it is ended and
 *                      commit blocks are sent to disk.  Forces commit blocks
 *                      to disk क्रम all backgrounded commits that have been
 *                      around too दीर्घ.
 *		     -- Note, अगर you call this as an immediate flush from
 *		        within kupdate, it will ignore the immediate flag
 */

#समावेश <linux/समय.स>
#समावेश <linux/semaphore.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "reiserfs.h"
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>


/* माला_लो a काष्ठा reiserfs_journal_list * from a list head */
#घोषणा JOURNAL_LIST_ENTRY(h) (list_entry((h), काष्ठा reiserfs_journal_list, \
                               j_list))

/* must be correct to keep the desc and commit काष्ठाs at 4k */
#घोषणा JOURNAL_TRANS_HALF 1018
#घोषणा BUFNR 64		/*पढ़ो ahead */

/* cnode stat bits.  Move these पूर्णांकo reiserfs_fs.h */

/* this block was मुक्तd, and can't be written.  */
#घोषणा BLOCK_FREED 2
/* this block was मुक्तd during this transaction, and can't be written */
#घोषणा BLOCK_FREED_HOLDER 3

/* used in flush_journal_list */
#घोषणा BLOCK_NEEDS_FLUSH 4
#घोषणा BLOCK_सूचीTIED 5

/* journal list state bits */
#घोषणा LIST_TOUCHED 1
#घोषणा LIST_सूचीTY   2
#घोषणा LIST_COMMIT_PENDING  4	/* someone will commit this list */

/* flags क्रम करो_journal_end */
#घोषणा FLUSH_ALL   1		/* flush commit and real blocks */
#घोषणा COMMIT_NOW  2		/* end and commit this transaction */
#घोषणा WAIT        4		/* रुको क्रम the log blocks to hit the disk */

अटल पूर्णांक करो_journal_end(काष्ठा reiserfs_transaction_handle *, पूर्णांक flags);
अटल पूर्णांक flush_journal_list(काष्ठा super_block *s,
			      काष्ठा reiserfs_journal_list *jl, पूर्णांक flushall);
अटल पूर्णांक flush_commit_list(काष्ठा super_block *s,
			     काष्ठा reiserfs_journal_list *jl, पूर्णांक flushall);
अटल पूर्णांक can_dirty(काष्ठा reiserfs_journal_cnode *cn);
अटल पूर्णांक journal_join(काष्ठा reiserfs_transaction_handle *th,
			काष्ठा super_block *sb);
अटल व्योम release_journal_dev(काष्ठा super_block *super,
			       काष्ठा reiserfs_journal *journal);
अटल व्योम dirty_one_transaction(काष्ठा super_block *s,
				 काष्ठा reiserfs_journal_list *jl);
अटल व्योम flush_async_commits(काष्ठा work_काष्ठा *work);
अटल व्योम queue_log_ग_लिखोr(काष्ठा super_block *s);

/* values क्रम join in करो_journal_begin_r */
क्रमागत अणु
	JBEGIN_REG = 0,		/* regular journal begin */
	/* join the running transaction अगर at all possible */
	JBEGIN_JOIN = 1,
	/* called from cleanup code, ignores पातed flag */
	JBEGIN_ABORT = 2,
पूर्ण;

अटल पूर्णांक करो_journal_begin_r(काष्ठा reiserfs_transaction_handle *th,
			      काष्ठा super_block *sb,
			      अचिन्हित दीर्घ nblocks, पूर्णांक join);

अटल व्योम init_journal_hash(काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	स_रखो(journal->j_hash_table, 0,
	       JOURNAL_HASH_SIZE * माप(काष्ठा reiserfs_journal_cnode *));
पूर्ण

/*
 * clears BH_Dirty and sticks the buffer on the clean list.  Called because
 * I can't allow refile_buffer to make schedule happen after I've मुक्तd a
 * block.  Look at हटाओ_from_transaction and journal_mark_मुक्तd क्रम
 * more details.
 */
अटल पूर्णांक reiserfs_clean_and_file_buffer(काष्ठा buffer_head *bh)
अणु
	अगर (bh) अणु
		clear_buffer_dirty(bh);
		clear_buffer_journal_test(bh);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा reiserfs_biपंचांगap_node *allocate_biपंचांगap_node(काष्ठा super_block
							 *sb)
अणु
	काष्ठा reiserfs_biपंचांगap_node *bn;
	अटल पूर्णांक id;

	bn = kदो_स्मृति(माप(काष्ठा reiserfs_biपंचांगap_node), GFP_NOFS);
	अगर (!bn) अणु
		वापस शून्य;
	पूर्ण
	bn->data = kzalloc(sb->s_blocksize, GFP_NOFS);
	अगर (!bn->data) अणु
		kमुक्त(bn);
		वापस शून्य;
	पूर्ण
	bn->id = id++;
	INIT_LIST_HEAD(&bn->list);
	वापस bn;
पूर्ण

अटल काष्ठा reiserfs_biपंचांगap_node *get_biपंचांगap_node(काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_biपंचांगap_node *bn = शून्य;
	काष्ठा list_head *entry = journal->j_biपंचांगap_nodes.next;

	journal->j_used_biपंचांगap_nodes++;
repeat:

	अगर (entry != &journal->j_biपंचांगap_nodes) अणु
		bn = list_entry(entry, काष्ठा reiserfs_biपंचांगap_node, list);
		list_del(entry);
		स_रखो(bn->data, 0, sb->s_blocksize);
		journal->j_मुक्त_biपंचांगap_nodes--;
		वापस bn;
	पूर्ण
	bn = allocate_biपंचांगap_node(sb);
	अगर (!bn) अणु
		yield();
		जाओ repeat;
	पूर्ण
	वापस bn;
पूर्ण
अटल अंतरभूत व्योम मुक्त_biपंचांगap_node(काष्ठा super_block *sb,
				    काष्ठा reiserfs_biपंचांगap_node *bn)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	journal->j_used_biपंचांगap_nodes--;
	अगर (journal->j_मुक्त_biपंचांगap_nodes > REISERFS_MAX_BITMAP_NODES) अणु
		kमुक्त(bn->data);
		kमुक्त(bn);
	पूर्ण अन्यथा अणु
		list_add(&bn->list, &journal->j_biपंचांगap_nodes);
		journal->j_मुक्त_biपंचांगap_nodes++;
	पूर्ण
पूर्ण

अटल व्योम allocate_biपंचांगap_nodes(काष्ठा super_block *sb)
अणु
	पूर्णांक i;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_biपंचांगap_node *bn = शून्य;
	क्रम (i = 0; i < REISERFS_MIN_BITMAP_NODES; i++) अणु
		bn = allocate_biपंचांगap_node(sb);
		अगर (bn) अणु
			list_add(&bn->list, &journal->j_biपंचांगap_nodes);
			journal->j_मुक्त_biपंचांगap_nodes++;
		पूर्ण अन्यथा अणु
			/* this is ok, we'll try again when more are needed */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक set_bit_in_list_biपंचांगap(काष्ठा super_block *sb,
				  b_blocknr_t block,
				  काष्ठा reiserfs_list_biपंचांगap *jb)
अणु
	अचिन्हित पूर्णांक bmap_nr = block / (sb->s_blocksize << 3);
	अचिन्हित पूर्णांक bit_nr = block % (sb->s_blocksize << 3);

	अगर (!jb->biपंचांगaps[bmap_nr]) अणु
		jb->biपंचांगaps[bmap_nr] = get_biपंचांगap_node(sb);
	पूर्ण
	set_bit(bit_nr, (अचिन्हित दीर्घ *)jb->biपंचांगaps[bmap_nr]->data);
	वापस 0;
पूर्ण

अटल व्योम cleanup_biपंचांगap_list(काष्ठा super_block *sb,
				काष्ठा reiserfs_list_biपंचांगap *jb)
अणु
	पूर्णांक i;
	अगर (jb->biपंचांगaps == शून्य)
		वापस;

	क्रम (i = 0; i < reiserfs_bmap_count(sb); i++) अणु
		अगर (jb->biपंचांगaps[i]) अणु
			मुक्त_biपंचांगap_node(sb, jb->biपंचांगaps[i]);
			jb->biपंचांगaps[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * only call this on FS unmount.
 */
अटल पूर्णांक मुक्त_list_biपंचांगaps(काष्ठा super_block *sb,
			     काष्ठा reiserfs_list_biपंचांगap *jb_array)
अणु
	पूर्णांक i;
	काष्ठा reiserfs_list_biपंचांगap *jb;
	क्रम (i = 0; i < JOURNAL_NUM_BITMAPS; i++) अणु
		jb = jb_array + i;
		jb->journal_list = शून्य;
		cleanup_biपंचांगap_list(sb, jb);
		vमुक्त(jb->biपंचांगaps);
		jb->biपंचांगaps = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक मुक्त_biपंचांगap_nodes(काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा list_head *next = journal->j_biपंचांगap_nodes.next;
	काष्ठा reiserfs_biपंचांगap_node *bn;

	जबतक (next != &journal->j_biपंचांगap_nodes) अणु
		bn = list_entry(next, काष्ठा reiserfs_biपंचांगap_node, list);
		list_del(next);
		kमुक्त(bn->data);
		kमुक्त(bn);
		next = journal->j_biपंचांगap_nodes.next;
		journal->j_मुक्त_biपंचांगap_nodes--;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * get memory क्रम JOURNAL_NUM_BITMAPS worth of biपंचांगaps.
 * jb_array is the array to be filled in.
 */
पूर्णांक reiserfs_allocate_list_biपंचांगaps(काष्ठा super_block *sb,
				   काष्ठा reiserfs_list_biपंचांगap *jb_array,
				   अचिन्हित पूर्णांक bmap_nr)
अणु
	पूर्णांक i;
	पूर्णांक failed = 0;
	काष्ठा reiserfs_list_biपंचांगap *jb;
	पूर्णांक mem = bmap_nr * माप(काष्ठा reiserfs_biपंचांगap_node *);

	क्रम (i = 0; i < JOURNAL_NUM_BITMAPS; i++) अणु
		jb = jb_array + i;
		jb->journal_list = शून्य;
		jb->biपंचांगaps = vzalloc(mem);
		अगर (!jb->biपंचांगaps) अणु
			reiserfs_warning(sb, "clm-2000", "unable to "
					 "allocate bitmaps for journal lists");
			failed = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (failed) अणु
		मुक्त_list_biपंचांगaps(sb, jb_array);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * find an available list biपंचांगap.  If you can't find one, flush a commit list
 * and try again
 */
अटल काष्ठा reiserfs_list_biपंचांगap *get_list_biपंचांगap(काष्ठा super_block *sb,
						    काष्ठा reiserfs_journal_list
						    *jl)
अणु
	पूर्णांक i, j;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_list_biपंचांगap *jb = शून्य;

	क्रम (j = 0; j < (JOURNAL_NUM_BITMAPS * 3); j++) अणु
		i = journal->j_list_biपंचांगap_index;
		journal->j_list_biपंचांगap_index = (i + 1) % JOURNAL_NUM_BITMAPS;
		jb = journal->j_list_biपंचांगap + i;
		अगर (journal->j_list_biपंचांगap[i].journal_list) अणु
			flush_commit_list(sb,
					  journal->j_list_biपंचांगap[i].
					  journal_list, 1);
			अगर (!journal->j_list_biपंचांगap[i].journal_list) अणु
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	/* द्विगुन check to make sure अगर flushed correctly */
	अगर (jb->journal_list)
		वापस शून्य;
	jb->journal_list = jl;
	वापस jb;
पूर्ण

/*
 * allocates a new chunk of X nodes, and links them all together as a list.
 * Uses the cnode->next and cnode->prev poपूर्णांकers
 * वापसs शून्य on failure
 */
अटल काष्ठा reiserfs_journal_cnode *allocate_cnodes(पूर्णांक num_cnodes)
अणु
	काष्ठा reiserfs_journal_cnode *head;
	पूर्णांक i;
	अगर (num_cnodes <= 0) अणु
		वापस शून्य;
	पूर्ण
	head = vzalloc(array_size(num_cnodes,
				  माप(काष्ठा reiserfs_journal_cnode)));
	अगर (!head) अणु
		वापस शून्य;
	पूर्ण
	head[0].prev = शून्य;
	head[0].next = head + 1;
	क्रम (i = 1; i < num_cnodes; i++) अणु
		head[i].prev = head + (i - 1);
		head[i].next = head + (i + 1);	/* अगर last one, overग_लिखो it after the अगर */
	पूर्ण
	head[num_cnodes - 1].next = शून्य;
	वापस head;
पूर्ण

/* pulls a cnode off the मुक्त list, or वापसs शून्य on failure */
अटल काष्ठा reiserfs_journal_cnode *get_cnode(काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_journal_cnode *cn;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);

	reiserfs_check_lock_depth(sb, "get_cnode");

	अगर (journal->j_cnode_मुक्त <= 0) अणु
		वापस शून्य;
	पूर्ण
	journal->j_cnode_used++;
	journal->j_cnode_मुक्त--;
	cn = journal->j_cnode_मुक्त_list;
	अगर (!cn) अणु
		वापस cn;
	पूर्ण
	अगर (cn->next) अणु
		cn->next->prev = शून्य;
	पूर्ण
	journal->j_cnode_मुक्त_list = cn->next;
	स_रखो(cn, 0, माप(काष्ठा reiserfs_journal_cnode));
	वापस cn;
पूर्ण

/*
 * वापसs a cnode to the मुक्त list
 */
अटल व्योम मुक्त_cnode(काष्ठा super_block *sb,
		       काष्ठा reiserfs_journal_cnode *cn)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);

	reiserfs_check_lock_depth(sb, "free_cnode");

	journal->j_cnode_used--;
	journal->j_cnode_मुक्त++;
	/* स_रखो(cn, 0, माप(काष्ठा reiserfs_journal_cnode)) ; */
	cn->next = journal->j_cnode_मुक्त_list;
	अगर (journal->j_cnode_मुक्त_list) अणु
		journal->j_cnode_मुक्त_list->prev = cn;
	पूर्ण
	cn->prev = शून्य;	/* not needed with the स_रखो, but I might समाप्त the स_रखो, and क्रमget to करो this */
	journal->j_cnode_मुक्त_list = cn;
पूर्ण

अटल व्योम clear_prepared_bits(काष्ठा buffer_head *bh)
अणु
	clear_buffer_journal_prepared(bh);
	clear_buffer_journal_restore_dirty(bh);
पूर्ण

/*
 * वापस a cnode with same dev, block number and size in table,
 * or null अगर not found
 */
अटल अंतरभूत काष्ठा reiserfs_journal_cnode *get_journal_hash_dev(काष्ठा
								  super_block
								  *sb,
								  काष्ठा
								  reiserfs_journal_cnode
								  **table,
								  दीर्घ bl)
अणु
	काष्ठा reiserfs_journal_cnode *cn;
	cn = journal_hash(table, sb, bl);
	जबतक (cn) अणु
		अगर (cn->blocknr == bl && cn->sb == sb)
			वापस cn;
		cn = cn->hnext;
	पूर्ण
	वापस (काष्ठा reiserfs_journal_cnode *)0;
पूर्ण

/*
 * this actually means 'can this block be reallocated yet?'.  If you set
 * search_all, a block can only be allocated अगर it is not in the current
 * transaction, was not मुक्तd by the current transaction, and has no chance
 * of ever being overwritten by a replay after crashing.
 *
 * If you करोn't set search_all, a block can only be allocated अगर it is not
 * in the current transaction.  Since deleting a block हटाओs it from the
 * current transaction, this हाल should never happen.  If you करोn't set
 * search_all, make sure you never ग_लिखो the block without logging it.
 *
 * next_zero_bit is a suggestion about the next block to try क्रम find_क्रमward.
 * when bl is rejected because it is set in a journal list biपंचांगap, we search
 * क्रम the next zero bit in the biपंचांगap that rejected bl.  Then, we वापस
 * that through next_zero_bit क्रम find_क्रमward to try.
 *
 * Just because we वापस something in next_zero_bit करोes not mean we won't
 * reject it on the next call to reiserfs_in_journal
 */
पूर्णांक reiserfs_in_journal(काष्ठा super_block *sb,
			अचिन्हित पूर्णांक bmap_nr, पूर्णांक bit_nr, पूर्णांक search_all,
			b_blocknr_t * next_zero_bit)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_list_biपंचांगap *jb;
	पूर्णांक i;
	अचिन्हित दीर्घ bl;

	*next_zero_bit = 0;	/* always start this at zero. */

	PROC_INFO_INC(sb, journal.in_journal);
	/*
	 * If we aren't करोing a search_all, this is a metablock, and it
	 * will be logged beक्रमe use.  अगर we crash beक्रमe the transaction
	 * that मुक्तd it commits,  this transaction won't have committed
	 * either, and the block will never be written
	 */
	अगर (search_all) अणु
		क्रम (i = 0; i < JOURNAL_NUM_BITMAPS; i++) अणु
			PROC_INFO_INC(sb, journal.in_journal_biपंचांगap);
			jb = journal->j_list_biपंचांगap + i;
			अगर (jb->journal_list && jb->biपंचांगaps[bmap_nr] &&
			    test_bit(bit_nr,
				     (अचिन्हित दीर्घ *)jb->biपंचांगaps[bmap_nr]->
				     data)) अणु
				*next_zero_bit =
				    find_next_zero_bit((अचिन्हित दीर्घ *)
						       (jb->biपंचांगaps[bmap_nr]->
							data),
						       sb->s_blocksize << 3,
						       bit_nr + 1);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	bl = bmap_nr * (sb->s_blocksize << 3) + bit_nr;
	/* is it in any old transactions? */
	अगर (search_all
	    && (get_journal_hash_dev(sb, journal->j_list_hash_table, bl))) अणु
		वापस 1;
	पूर्ण

	/* is it in the current transaction.  This should never happen */
	अगर ((get_journal_hash_dev(sb, journal->j_hash_table, bl))) अणु
		BUG();
		वापस 1;
	पूर्ण

	PROC_INFO_INC(sb, journal.in_journal_reusable);
	/* safe क्रम reuse */
	वापस 0;
पूर्ण

/* insert cn पूर्णांकo table */
अटल अंतरभूत व्योम insert_journal_hash(काष्ठा reiserfs_journal_cnode **table,
				       काष्ठा reiserfs_journal_cnode *cn)
अणु
	काष्ठा reiserfs_journal_cnode *cn_orig;

	cn_orig = journal_hash(table, cn->sb, cn->blocknr);
	cn->hnext = cn_orig;
	cn->hprev = शून्य;
	अगर (cn_orig) अणु
		cn_orig->hprev = cn;
	पूर्ण
	journal_hash(table, cn->sb, cn->blocknr) = cn;
पूर्ण

/* lock the current transaction */
अटल अंतरभूत व्योम lock_journal(काष्ठा super_block *sb)
अणु
	PROC_INFO_INC(sb, journal.lock_journal);

	reiserfs_mutex_lock_safe(&SB_JOURNAL(sb)->j_mutex, sb);
पूर्ण

/* unlock the current transaction */
अटल अंतरभूत व्योम unlock_journal(काष्ठा super_block *sb)
अणु
	mutex_unlock(&SB_JOURNAL(sb)->j_mutex);
पूर्ण

अटल अंतरभूत व्योम get_journal_list(काष्ठा reiserfs_journal_list *jl)
अणु
	jl->j_refcount++;
पूर्ण

अटल अंतरभूत व्योम put_journal_list(काष्ठा super_block *s,
				    काष्ठा reiserfs_journal_list *jl)
अणु
	अगर (jl->j_refcount < 1) अणु
		reiserfs_panic(s, "journal-2", "trans id %u, refcount at %d",
			       jl->j_trans_id, jl->j_refcount);
	पूर्ण
	अगर (--jl->j_refcount == 0)
		kमुक्त(jl);
पूर्ण

/*
 * this used to be much more involved, and I'm keeping it just in हाल
 * things get ugly again.  it माला_लो called by flush_commit_list, and
 * cleans up any data stored about blocks मुक्तd during a transaction.
 */
अटल व्योम cleanup_मुक्तd_क्रम_journal_list(काष्ठा super_block *sb,
					   काष्ठा reiserfs_journal_list *jl)
अणु

	काष्ठा reiserfs_list_biपंचांगap *jb = jl->j_list_biपंचांगap;
	अगर (jb) अणु
		cleanup_biपंचांगap_list(sb, jb);
	पूर्ण
	jl->j_list_biपंचांगap->journal_list = शून्य;
	jl->j_list_biपंचांगap = शून्य;
पूर्ण

अटल पूर्णांक journal_list_still_alive(काष्ठा super_block *s,
				    अचिन्हित पूर्णांक trans_id)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	काष्ठा list_head *entry = &journal->j_journal_list;
	काष्ठा reiserfs_journal_list *jl;

	अगर (!list_empty(entry)) अणु
		jl = JOURNAL_LIST_ENTRY(entry->next);
		अगर (jl->j_trans_id <= trans_id) अणु
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * If page->mapping was null, we failed to truncate this page क्रम
 * some reason.  Most likely because it was truncated after being
 * logged via data=journal.
 *
 * This करोes a check to see अगर the buffer beदीर्घs to one of these
 * lost pages beक्रमe करोing the final put_bh.  If page->mapping was
 * null, it tries to मुक्त buffers on the page, which should make the
 * final put_page drop the page from the lru.
 */
अटल व्योम release_buffer_page(काष्ठा buffer_head *bh)
अणु
	काष्ठा page *page = bh->b_page;
	अगर (!page->mapping && trylock_page(page)) अणु
		get_page(page);
		put_bh(bh);
		अगर (!page->mapping)
			try_to_मुक्त_buffers(page);
		unlock_page(page);
		put_page(page);
	पूर्ण अन्यथा अणु
		put_bh(bh);
	पूर्ण
पूर्ण

अटल व्योम reiserfs_end_buffer_io_sync(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	अगर (buffer_journaled(bh)) अणु
		reiserfs_warning(शून्य, "clm-2084",
				 "pinned buffer %lu:%pg sent to disk",
				 bh->b_blocknr, bh->b_bdev);
	पूर्ण
	अगर (uptodate)
		set_buffer_uptodate(bh);
	अन्यथा
		clear_buffer_uptodate(bh);

	unlock_buffer(bh);
	release_buffer_page(bh);
पूर्ण

अटल व्योम reiserfs_end_ordered_io(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	अगर (uptodate)
		set_buffer_uptodate(bh);
	अन्यथा
		clear_buffer_uptodate(bh);
	unlock_buffer(bh);
	put_bh(bh);
पूर्ण

अटल व्योम submit_logged_buffer(काष्ठा buffer_head *bh)
अणु
	get_bh(bh);
	bh->b_end_io = reiserfs_end_buffer_io_sync;
	clear_buffer_journal_new(bh);
	clear_buffer_dirty(bh);
	अगर (!test_clear_buffer_journal_test(bh))
		BUG();
	अगर (!buffer_uptodate(bh))
		BUG();
	submit_bh(REQ_OP_WRITE, 0, bh);
पूर्ण

अटल व्योम submit_ordered_buffer(काष्ठा buffer_head *bh)
अणु
	get_bh(bh);
	bh->b_end_io = reiserfs_end_ordered_io;
	clear_buffer_dirty(bh);
	अगर (!buffer_uptodate(bh))
		BUG();
	submit_bh(REQ_OP_WRITE, 0, bh);
पूर्ण

#घोषणा CHUNK_SIZE 32
काष्ठा buffer_chunk अणु
	काष्ठा buffer_head *bh[CHUNK_SIZE];
	पूर्णांक nr;
पूर्ण;

अटल व्योम ग_लिखो_chunk(काष्ठा buffer_chunk *chunk)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < chunk->nr; i++) अणु
		submit_logged_buffer(chunk->bh[i]);
	पूर्ण
	chunk->nr = 0;
पूर्ण

अटल व्योम ग_लिखो_ordered_chunk(काष्ठा buffer_chunk *chunk)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < chunk->nr; i++) अणु
		submit_ordered_buffer(chunk->bh[i]);
	पूर्ण
	chunk->nr = 0;
पूर्ण

अटल पूर्णांक add_to_chunk(काष्ठा buffer_chunk *chunk, काष्ठा buffer_head *bh,
			spinlock_t * lock, व्योम (fn) (काष्ठा buffer_chunk *))
अणु
	पूर्णांक ret = 0;
	BUG_ON(chunk->nr >= CHUNK_SIZE);
	chunk->bh[chunk->nr++] = bh;
	अगर (chunk->nr >= CHUNK_SIZE) अणु
		ret = 1;
		अगर (lock) अणु
			spin_unlock(lock);
			fn(chunk);
			spin_lock(lock);
		पूर्ण अन्यथा अणु
			fn(chunk);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल atomic_t nr_reiserfs_jh = ATOMIC_INIT(0);
अटल काष्ठा reiserfs_jh *alloc_jh(व्योम)
अणु
	काष्ठा reiserfs_jh *jh;
	जबतक (1) अणु
		jh = kदो_स्मृति(माप(*jh), GFP_NOFS);
		अगर (jh) अणु
			atomic_inc(&nr_reiserfs_jh);
			वापस jh;
		पूर्ण
		yield();
	पूर्ण
पूर्ण

/*
 * we want to मुक्त the jh when the buffer has been written
 * and रुकोed on
 */
व्योम reiserfs_मुक्त_jh(काष्ठा buffer_head *bh)
अणु
	काष्ठा reiserfs_jh *jh;

	jh = bh->b_निजी;
	अगर (jh) अणु
		bh->b_निजी = शून्य;
		jh->bh = शून्य;
		list_del_init(&jh->list);
		kमुक्त(jh);
		अगर (atomic_पढ़ो(&nr_reiserfs_jh) <= 0)
			BUG();
		atomic_dec(&nr_reiserfs_jh);
		put_bh(bh);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक __add_jh(काष्ठा reiserfs_journal *j, काष्ठा buffer_head *bh,
			   पूर्णांक tail)
अणु
	काष्ठा reiserfs_jh *jh;

	अगर (bh->b_निजी) अणु
		spin_lock(&j->j_dirty_buffers_lock);
		अगर (!bh->b_निजी) अणु
			spin_unlock(&j->j_dirty_buffers_lock);
			जाओ no_jh;
		पूर्ण
		jh = bh->b_निजी;
		list_del_init(&jh->list);
	पूर्ण अन्यथा अणु
no_jh:
		get_bh(bh);
		jh = alloc_jh();
		spin_lock(&j->j_dirty_buffers_lock);
		/*
		 * buffer must be locked क्रम __add_jh, should be able to have
		 * two adds at the same समय
		 */
		BUG_ON(bh->b_निजी);
		jh->bh = bh;
		bh->b_निजी = jh;
	पूर्ण
	jh->jl = j->j_current_jl;
	अगर (tail)
		list_add_tail(&jh->list, &jh->jl->j_tail_bh_list);
	अन्यथा अणु
		list_add_tail(&jh->list, &jh->jl->j_bh_list);
	पूर्ण
	spin_unlock(&j->j_dirty_buffers_lock);
	वापस 0;
पूर्ण

पूर्णांक reiserfs_add_tail_list(काष्ठा inode *inode, काष्ठा buffer_head *bh)
अणु
	वापस __add_jh(SB_JOURNAL(inode->i_sb), bh, 1);
पूर्ण
पूर्णांक reiserfs_add_ordered_list(काष्ठा inode *inode, काष्ठा buffer_head *bh)
अणु
	वापस __add_jh(SB_JOURNAL(inode->i_sb), bh, 0);
पूर्ण

#घोषणा JH_ENTRY(l) list_entry((l), काष्ठा reiserfs_jh, list)
अटल पूर्णांक ग_लिखो_ordered_buffers(spinlock_t * lock,
				 काष्ठा reiserfs_journal *j,
				 काष्ठा reiserfs_journal_list *jl,
				 काष्ठा list_head *list)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा reiserfs_jh *jh;
	पूर्णांक ret = j->j_त्रुटि_सं;
	काष्ठा buffer_chunk chunk;
	काष्ठा list_head पंचांगp;
	INIT_LIST_HEAD(&पंचांगp);

	chunk.nr = 0;
	spin_lock(lock);
	जबतक (!list_empty(list)) अणु
		jh = JH_ENTRY(list->next);
		bh = jh->bh;
		get_bh(bh);
		अगर (!trylock_buffer(bh)) अणु
			अगर (!buffer_dirty(bh)) अणु
				list_move(&jh->list, &पंचांगp);
				जाओ loop_next;
			पूर्ण
			spin_unlock(lock);
			अगर (chunk.nr)
				ग_लिखो_ordered_chunk(&chunk);
			रुको_on_buffer(bh);
			cond_resched();
			spin_lock(lock);
			जाओ loop_next;
		पूर्ण
		/*
		 * in theory, dirty non-uptodate buffers should never get here,
		 * but the upper layer io error paths still have a few quirks.
		 * Handle them here as gracefully as we can
		 */
		अगर (!buffer_uptodate(bh) && buffer_dirty(bh)) अणु
			clear_buffer_dirty(bh);
			ret = -EIO;
		पूर्ण
		अगर (buffer_dirty(bh)) अणु
			list_move(&jh->list, &पंचांगp);
			add_to_chunk(&chunk, bh, lock, ग_लिखो_ordered_chunk);
		पूर्ण अन्यथा अणु
			reiserfs_मुक्त_jh(bh);
			unlock_buffer(bh);
		पूर्ण
loop_next:
		put_bh(bh);
		cond_resched_lock(lock);
	पूर्ण
	अगर (chunk.nr) अणु
		spin_unlock(lock);
		ग_लिखो_ordered_chunk(&chunk);
		spin_lock(lock);
	पूर्ण
	जबतक (!list_empty(&पंचांगp)) अणु
		jh = JH_ENTRY(पंचांगp.prev);
		bh = jh->bh;
		get_bh(bh);
		reiserfs_मुक्त_jh(bh);

		अगर (buffer_locked(bh)) अणु
			spin_unlock(lock);
			रुको_on_buffer(bh);
			spin_lock(lock);
		पूर्ण
		अगर (!buffer_uptodate(bh)) अणु
			ret = -EIO;
		पूर्ण
		/*
		 * ugly पूर्णांकeraction with invalidatepage here.
		 * reiserfs_invalidate_page will pin any buffer that has a
		 * valid journal head from an older transaction.  If someone
		 * अन्यथा sets our buffer dirty after we ग_लिखो it in the first
		 * loop, and then someone truncates the page away, nobody
		 * will ever ग_लिखो the buffer. We're safe अगर we ग_लिखो the
		 * page one last समय after मुक्तing the journal header.
		 */
		अगर (buffer_dirty(bh) && unlikely(bh->b_page->mapping == शून्य)) अणु
			spin_unlock(lock);
			ll_rw_block(REQ_OP_WRITE, 0, 1, &bh);
			spin_lock(lock);
		पूर्ण
		put_bh(bh);
		cond_resched_lock(lock);
	पूर्ण
	spin_unlock(lock);
	वापस ret;
पूर्ण

अटल पूर्णांक flush_older_commits(काष्ठा super_block *s,
			       काष्ठा reiserfs_journal_list *jl)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	काष्ठा reiserfs_journal_list *other_jl;
	काष्ठा reiserfs_journal_list *first_jl;
	काष्ठा list_head *entry;
	अचिन्हित पूर्णांक trans_id = jl->j_trans_id;
	अचिन्हित पूर्णांक other_trans_id;

find_first:
	/*
	 * first we walk backwards to find the oldest uncommitted transation
	 */
	first_jl = jl;
	entry = jl->j_list.prev;
	जबतक (1) अणु
		other_jl = JOURNAL_LIST_ENTRY(entry);
		अगर (entry == &journal->j_journal_list ||
		    atomic_पढ़ो(&other_jl->j_older_commits_करोne))
			अवरोध;

		first_jl = other_jl;
		entry = other_jl->j_list.prev;
	पूर्ण

	/* अगर we didn't find any older uncommitted transactions, वापस now */
	अगर (first_jl == jl) अणु
		वापस 0;
	पूर्ण

	entry = &first_jl->j_list;
	जबतक (1) अणु
		other_jl = JOURNAL_LIST_ENTRY(entry);
		other_trans_id = other_jl->j_trans_id;

		अगर (other_trans_id < trans_id) अणु
			अगर (atomic_पढ़ो(&other_jl->j_commit_left) != 0) अणु
				flush_commit_list(s, other_jl, 0);

				/* list we were called with is gone, वापस */
				अगर (!journal_list_still_alive(s, trans_id))
					वापस 1;

				/*
				 * the one we just flushed is gone, this means
				 * all older lists are also gone, so first_jl
				 * is no दीर्घer valid either.  Go back to the
				 * beginning.
				 */
				अगर (!journal_list_still_alive
				    (s, other_trans_id)) अणु
					जाओ find_first;
				पूर्ण
			पूर्ण
			entry = entry->next;
			अगर (entry == &journal->j_journal_list)
				वापस 0;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक reiserfs_async_progress_रुको(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_journal *j = SB_JOURNAL(s);

	अगर (atomic_पढ़ो(&j->j_async_throttle)) अणु
		पूर्णांक depth;

		depth = reiserfs_ग_लिखो_unlock_nested(s);
		congestion_रुको(BLK_RW_ASYNC, HZ / 10);
		reiserfs_ग_लिखो_lock_nested(s, depth);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * अगर this journal list still has commit blocks unflushed, send them to disk.
 *
 * log areas must be flushed in order (transaction 2 can't commit beक्रमe
 * transaction 1) Beक्रमe the commit block can by written, every other log
 * block must be safely on disk
 */
अटल पूर्णांक flush_commit_list(काष्ठा super_block *s,
			     काष्ठा reiserfs_journal_list *jl, पूर्णांक flushall)
अणु
	पूर्णांक i;
	b_blocknr_t bn;
	काष्ठा buffer_head *tbh = शून्य;
	अचिन्हित पूर्णांक trans_id = jl->j_trans_id;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	पूर्णांक retval = 0;
	पूर्णांक ग_लिखो_len;
	पूर्णांक depth;

	reiserfs_check_lock_depth(s, "flush_commit_list");

	अगर (atomic_पढ़ो(&jl->j_older_commits_करोne)) अणु
		वापस 0;
	पूर्ण

	/*
	 * beक्रमe we can put our commit blocks on disk, we have to make
	 * sure everyone older than us is on disk too
	 */
	BUG_ON(jl->j_len <= 0);
	BUG_ON(trans_id == journal->j_trans_id);

	get_journal_list(jl);
	अगर (flushall) अणु
		अगर (flush_older_commits(s, jl) == 1) अणु
			/*
			 * list disappeared during flush_older_commits.
			 * वापस
			 */
			जाओ put_jl;
		पूर्ण
	पूर्ण

	/* make sure nobody is trying to flush this one at the same समय */
	reiserfs_mutex_lock_safe(&jl->j_commit_mutex, s);

	अगर (!journal_list_still_alive(s, trans_id)) अणु
		mutex_unlock(&jl->j_commit_mutex);
		जाओ put_jl;
	पूर्ण
	BUG_ON(jl->j_trans_id == 0);

	/* this commit is करोne, निकास */
	अगर (atomic_पढ़ो(&jl->j_commit_left) <= 0) अणु
		अगर (flushall) अणु
			atomic_set(&jl->j_older_commits_करोne, 1);
		पूर्ण
		mutex_unlock(&jl->j_commit_mutex);
		जाओ put_jl;
	पूर्ण

	अगर (!list_empty(&jl->j_bh_list)) अणु
		पूर्णांक ret;

		/*
		 * We might sleep in numerous places inside
		 * ग_लिखो_ordered_buffers. Relax the ग_लिखो lock.
		 */
		depth = reiserfs_ग_लिखो_unlock_nested(s);
		ret = ग_लिखो_ordered_buffers(&journal->j_dirty_buffers_lock,
					    journal, jl, &jl->j_bh_list);
		अगर (ret < 0 && retval == 0)
			retval = ret;
		reiserfs_ग_लिखो_lock_nested(s, depth);
	पूर्ण
	BUG_ON(!list_empty(&jl->j_bh_list));
	/*
	 * क्रम the description block and all the log blocks, submit any buffers
	 * that haven't alपढ़ोy reached the disk.  Try to ग_लिखो at least 256
	 * log blocks. later on, we will only रुको on blocks that correspond
	 * to this transaction, but जबतक we're unplugging we might as well
	 * get a chunk of data on there.
	 */
	atomic_inc(&journal->j_async_throttle);
	ग_लिखो_len = jl->j_len + 1;
	अगर (ग_लिखो_len < 256)
		ग_लिखो_len = 256;
	क्रम (i = 0 ; i < ग_लिखो_len ; i++) अणु
		bn = SB_ONDISK_JOURNAL_1st_BLOCK(s) + (jl->j_start + i) %
		    SB_ONDISK_JOURNAL_SIZE(s);
		tbh = journal_find_get_block(s, bn);
		अगर (tbh) अणु
			अगर (buffer_dirty(tbh)) अणु
		            depth = reiserfs_ग_लिखो_unlock_nested(s);
			    ll_rw_block(REQ_OP_WRITE, 0, 1, &tbh);
			    reiserfs_ग_लिखो_lock_nested(s, depth);
			पूर्ण
			put_bh(tbh) ;
		पूर्ण
	पूर्ण
	atomic_dec(&journal->j_async_throttle);

	क्रम (i = 0; i < (jl->j_len + 1); i++) अणु
		bn = SB_ONDISK_JOURNAL_1st_BLOCK(s) +
		    (jl->j_start + i) % SB_ONDISK_JOURNAL_SIZE(s);
		tbh = journal_find_get_block(s, bn);

		depth = reiserfs_ग_लिखो_unlock_nested(s);
		__रुको_on_buffer(tbh);
		reiserfs_ग_लिखो_lock_nested(s, depth);
		/*
		 * since we're using ll_rw_blk above, it might have skipped
		 * over a locked buffer.  Double check here
		 */
		/* redundant, sync_dirty_buffer() checks */
		अगर (buffer_dirty(tbh)) अणु
			depth = reiserfs_ग_लिखो_unlock_nested(s);
			sync_dirty_buffer(tbh);
			reiserfs_ग_लिखो_lock_nested(s, depth);
		पूर्ण
		अगर (unlikely(!buffer_uptodate(tbh))) अणु
#अगर_घोषित CONFIG_REISERFS_CHECK
			reiserfs_warning(s, "journal-601",
					 "buffer write failed");
#पूर्ण_अगर
			retval = -EIO;
		पूर्ण
		/* once क्रम journal_find_get_block */
		put_bh(tbh);
		/* once due to original getblk in करो_journal_end */
		put_bh(tbh);
		atomic_dec(&jl->j_commit_left);
	पूर्ण

	BUG_ON(atomic_पढ़ो(&jl->j_commit_left) != 1);

	/*
	 * If there was a ग_लिखो error in the journal - we can't commit
	 * this transaction - it will be invalid and, अगर successful,
	 * will just end up propagating the ग_लिखो error out to
	 * the file प्रणाली.
	 */
	अगर (likely(!retval && !reiserfs_is_journal_पातed (journal))) अणु
		अगर (buffer_dirty(jl->j_commit_bh))
			BUG();
		mark_buffer_dirty(jl->j_commit_bh) ;
		depth = reiserfs_ग_लिखो_unlock_nested(s);
		अगर (reiserfs_barrier_flush(s))
			__sync_dirty_buffer(jl->j_commit_bh,
					REQ_SYNC | REQ_PREFLUSH | REQ_FUA);
		अन्यथा
			sync_dirty_buffer(jl->j_commit_bh);
		reiserfs_ग_लिखो_lock_nested(s, depth);
	पूर्ण

	/*
	 * If there was a ग_लिखो error in the journal - we can't commit this
	 * transaction - it will be invalid and, अगर successful, will just end
	 * up propagating the ग_लिखो error out to the fileप्रणाली.
	 */
	अगर (unlikely(!buffer_uptodate(jl->j_commit_bh))) अणु
#अगर_घोषित CONFIG_REISERFS_CHECK
		reiserfs_warning(s, "journal-615", "buffer write failed");
#पूर्ण_अगर
		retval = -EIO;
	पूर्ण
	bक्रमget(jl->j_commit_bh);
	अगर (journal->j_last_commit_id != 0 &&
	    (jl->j_trans_id - journal->j_last_commit_id) != 1) अणु
		reiserfs_warning(s, "clm-2200", "last commit %lu, current %lu",
				 journal->j_last_commit_id, jl->j_trans_id);
	पूर्ण
	journal->j_last_commit_id = jl->j_trans_id;

	/*
	 * now, every commit block is on the disk.  It is safe to allow
	 * blocks मुक्तd during this transaction to be पुनः_स्मृतिated
	 */
	cleanup_मुक्तd_क्रम_journal_list(s, jl);

	retval = retval ? retval : journal->j_त्रुटि_सं;

	/* mark the metadata dirty */
	अगर (!retval)
		dirty_one_transaction(s, jl);
	atomic_dec(&jl->j_commit_left);

	अगर (flushall) अणु
		atomic_set(&jl->j_older_commits_करोne, 1);
	पूर्ण
	mutex_unlock(&jl->j_commit_mutex);
put_jl:
	put_journal_list(s, jl);

	अगर (retval)
		reiserfs_पात(s, retval, "Journal write error in %s",
			       __func__);
	वापस retval;
पूर्ण

/*
 * flush_journal_list frequently needs to find a newer transaction क्रम a
 * given block.  This करोes that, or वापसs शून्य अगर it can't find anything
 */
अटल काष्ठा reiserfs_journal_list *find_newer_jl_क्रम_cn(काष्ठा
							  reiserfs_journal_cnode
							  *cn)
अणु
	काष्ठा super_block *sb = cn->sb;
	b_blocknr_t blocknr = cn->blocknr;

	cn = cn->hprev;
	जबतक (cn) अणु
		अगर (cn->sb == sb && cn->blocknr == blocknr && cn->jlist) अणु
			वापस cn->jlist;
		पूर्ण
		cn = cn->hprev;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम हटाओ_journal_hash(काष्ठा super_block *,
				काष्ठा reiserfs_journal_cnode **,
				काष्ठा reiserfs_journal_list *, अचिन्हित दीर्घ,
				पूर्णांक);

/*
 * once all the real blocks have been flushed, it is safe to हटाओ them
 * from the journal list क्रम this transaction.  Aside from मुक्तing the
 * cnode, this also allows the block to be पुनः_स्मृतिated क्रम data blocks
 * अगर it had been deleted.
 */
अटल व्योम हटाओ_all_from_journal_list(काष्ठा super_block *sb,
					 काष्ठा reiserfs_journal_list *jl,
					 पूर्णांक debug)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_journal_cnode *cn, *last;
	cn = jl->j_realblock;

	/*
	 * which is better, to lock once around the whole loop, or
	 * to lock क्रम each call to हटाओ_journal_hash?
	 */
	जबतक (cn) अणु
		अगर (cn->blocknr != 0) अणु
			अगर (debug) अणु
				reiserfs_warning(sb, "reiserfs-2201",
						 "block %u, bh is %d, state %ld",
						 cn->blocknr, cn->bh ? 1 : 0,
						 cn->state);
			पूर्ण
			cn->state = 0;
			हटाओ_journal_hash(sb, journal->j_list_hash_table,
					    jl, cn->blocknr, 1);
		पूर्ण
		last = cn;
		cn = cn->next;
		मुक्त_cnode(sb, last);
	पूर्ण
	jl->j_realblock = शून्य;
पूर्ण

/*
 * अगर this बारtamp is greater than the बारtamp we wrote last to the
 * header block, ग_लिखो it to the header block.  once this is करोne, I can
 * safely say the log area क्रम this transaction won't ever be replayed,
 * and I can start releasing blocks in this transaction क्रम reuse as data
 * blocks.  called by flush_journal_list, beक्रमe it calls
 * हटाओ_all_from_journal_list
 */
अटल पूर्णांक _update_journal_header_block(काष्ठा super_block *sb,
					अचिन्हित दीर्घ offset,
					अचिन्हित पूर्णांक trans_id)
अणु
	काष्ठा reiserfs_journal_header *jh;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	पूर्णांक depth;

	अगर (reiserfs_is_journal_पातed(journal))
		वापस -EIO;

	अगर (trans_id >= journal->j_last_flush_trans_id) अणु
		अगर (buffer_locked((journal->j_header_bh))) अणु
			depth = reiserfs_ग_लिखो_unlock_nested(sb);
			__रुको_on_buffer(journal->j_header_bh);
			reiserfs_ग_लिखो_lock_nested(sb, depth);
			अगर (unlikely(!buffer_uptodate(journal->j_header_bh))) अणु
#अगर_घोषित CONFIG_REISERFS_CHECK
				reiserfs_warning(sb, "journal-699",
						 "buffer write failed");
#पूर्ण_अगर
				वापस -EIO;
			पूर्ण
		पूर्ण
		journal->j_last_flush_trans_id = trans_id;
		journal->j_first_unflushed_offset = offset;
		jh = (काष्ठा reiserfs_journal_header *)(journal->j_header_bh->
							b_data);
		jh->j_last_flush_trans_id = cpu_to_le32(trans_id);
		jh->j_first_unflushed_offset = cpu_to_le32(offset);
		jh->j_mount_id = cpu_to_le32(journal->j_mount_id);

		set_buffer_dirty(journal->j_header_bh);
		depth = reiserfs_ग_लिखो_unlock_nested(sb);

		अगर (reiserfs_barrier_flush(sb))
			__sync_dirty_buffer(journal->j_header_bh,
					REQ_SYNC | REQ_PREFLUSH | REQ_FUA);
		अन्यथा
			sync_dirty_buffer(journal->j_header_bh);

		reiserfs_ग_लिखो_lock_nested(sb, depth);
		अगर (!buffer_uptodate(journal->j_header_bh)) अणु
			reiserfs_warning(sb, "journal-837",
					 "IO error during journal replay");
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक update_journal_header_block(काष्ठा super_block *sb,
				       अचिन्हित दीर्घ offset,
				       अचिन्हित पूर्णांक trans_id)
अणु
	वापस _update_journal_header_block(sb, offset, trans_id);
पूर्ण

/*
** flush any and all journal lists older than you are
** can only be called from flush_journal_list
*/
अटल पूर्णांक flush_older_journal_lists(काष्ठा super_block *sb,
				     काष्ठा reiserfs_journal_list *jl)
अणु
	काष्ठा list_head *entry;
	काष्ठा reiserfs_journal_list *other_jl;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	अचिन्हित पूर्णांक trans_id = jl->j_trans_id;

	/*
	 * we know we are the only ones flushing things, no extra race
	 * protection is required.
	 */
restart:
	entry = journal->j_journal_list.next;
	/* Did we wrap? */
	अगर (entry == &journal->j_journal_list)
		वापस 0;
	other_jl = JOURNAL_LIST_ENTRY(entry);
	अगर (other_jl->j_trans_id < trans_id) अणु
		BUG_ON(other_jl->j_refcount <= 0);
		/* करो not flush all */
		flush_journal_list(sb, other_jl, 0);

		/* other_jl is now deleted from the list */
		जाओ restart;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम del_from_work_list(काष्ठा super_block *s,
			       काष्ठा reiserfs_journal_list *jl)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	अगर (!list_empty(&jl->j_working_list)) अणु
		list_del_init(&jl->j_working_list);
		journal->j_num_work_lists--;
	पूर्ण
पूर्ण

/*
 * flush a journal list, both commit and real blocks
 *
 * always set flushall to 1, unless you are calling from inside
 * flush_journal_list
 *
 * IMPORTANT.  This can only be called जबतक there are no journal ग_लिखोrs,
 * and the journal is locked.  That means it can only be called from
 * करो_journal_end, or by journal_release
 */
अटल पूर्णांक flush_journal_list(काष्ठा super_block *s,
			      काष्ठा reiserfs_journal_list *jl, पूर्णांक flushall)
अणु
	काष्ठा reiserfs_journal_list *pjl;
	काष्ठा reiserfs_journal_cnode *cn;
	पूर्णांक count;
	पूर्णांक was_jरुको = 0;
	पूर्णांक was_dirty = 0;
	काष्ठा buffer_head *saved_bh;
	अचिन्हित दीर्घ j_len_saved = jl->j_len;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	पूर्णांक err = 0;
	पूर्णांक depth;

	BUG_ON(j_len_saved <= 0);

	अगर (atomic_पढ़ो(&journal->j_wcount) != 0) अणु
		reiserfs_warning(s, "clm-2048", "called with wcount %d",
				 atomic_पढ़ो(&journal->j_wcount));
	पूर्ण

	/* अगर flushall == 0, the lock is alपढ़ोy held */
	अगर (flushall) अणु
		reiserfs_mutex_lock_safe(&journal->j_flush_mutex, s);
	पूर्ण अन्यथा अगर (mutex_trylock(&journal->j_flush_mutex)) अणु
		BUG();
	पूर्ण

	count = 0;
	अगर (j_len_saved > journal->j_trans_max) अणु
		reiserfs_panic(s, "journal-715", "length is %lu, trans id %lu",
			       j_len_saved, jl->j_trans_id);
		वापस 0;
	पूर्ण

	/* अगर all the work is alपढ़ोy करोne, get out of here */
	अगर (atomic_पढ़ो(&jl->j_nonzerolen) <= 0 &&
	    atomic_पढ़ो(&jl->j_commit_left) <= 0) अणु
		जाओ flush_older_and_वापस;
	पूर्ण

	/*
	 * start by putting the commit list on disk.  This will also flush
	 * the commit lists of any olders transactions
	 */
	flush_commit_list(s, jl, 1);

	अगर (!(jl->j_state & LIST_सूचीTY)
	    && !reiserfs_is_journal_पातed(journal))
		BUG();

	/* are we करोne now? */
	अगर (atomic_पढ़ो(&jl->j_nonzerolen) <= 0 &&
	    atomic_पढ़ो(&jl->j_commit_left) <= 0) अणु
		जाओ flush_older_and_वापस;
	पूर्ण

	/*
	 * loop through each cnode, see अगर we need to ग_लिखो it,
	 * or रुको on a more recent transaction, or just ignore it
	 */
	अगर (atomic_पढ़ो(&journal->j_wcount) != 0) अणु
		reiserfs_panic(s, "journal-844", "journal list is flushing, "
			       "wcount is not 0");
	पूर्ण
	cn = jl->j_realblock;
	जबतक (cn) अणु
		was_jरुको = 0;
		was_dirty = 0;
		saved_bh = शून्य;
		/* blocknr of 0 is no दीर्घer in the hash, ignore it */
		अगर (cn->blocknr == 0) अणु
			जाओ मुक्त_cnode;
		पूर्ण

		/*
		 * This transaction failed commit.
		 * Don't ग_लिखो out to the disk
		 */
		अगर (!(jl->j_state & LIST_सूचीTY))
			जाओ मुक्त_cnode;

		pjl = find_newer_jl_क्रम_cn(cn);
		/*
		 * the order is important here.  We check pjl to make sure we
		 * करोn't clear BH_JDirty_wait if we aren't the one writing this
		 * block to disk
		 */
		अगर (!pjl && cn->bh) अणु
			saved_bh = cn->bh;

			/*
			 * we करो this to make sure nobody releases the
			 * buffer जबतक we are working with it
			 */
			get_bh(saved_bh);

			अगर (buffer_journal_dirty(saved_bh)) अणु
				BUG_ON(!can_dirty(cn));
				was_jरुको = 1;
				was_dirty = 1;
			पूर्ण अन्यथा अगर (can_dirty(cn)) अणु
				/*
				 * everything with !pjl && jरुको
				 * should be writable
				 */
				BUG();
			पूर्ण
		पूर्ण

		/*
		 * अगर someone has this block in a newer transaction, just make
		 * sure they are committed, and करोn't try writing it to disk
		 */
		अगर (pjl) अणु
			अगर (atomic_पढ़ो(&pjl->j_commit_left))
				flush_commit_list(s, pjl, 1);
			जाओ मुक्त_cnode;
		पूर्ण

		/*
		 * bh == शून्य when the block got to disk on its own, OR,
		 * the block got मुक्तd in a future transaction
		 */
		अगर (saved_bh == शून्य) अणु
			जाओ मुक्त_cnode;
		पूर्ण

		/*
		 * this should never happen.  kupdate_one_transaction has
		 * this list locked जबतक it works, so we should never see a
		 * buffer here that is not marked JDirty_रुको
		 */
		अगर ((!was_jरुको) && !buffer_locked(saved_bh)) अणु
			reiserfs_warning(s, "journal-813",
					 "BAD! buffer %llu %cdirty %cjwait, "
					 "not in a newer transaction",
					 (अचिन्हित दीर्घ दीर्घ)saved_bh->
					 b_blocknr, was_dirty ? ' ' : '!',
					 was_jरुको ? ' ' : '!');
		पूर्ण
		अगर (was_dirty) अणु
			/*
			 * we inc again because saved_bh माला_लो decremented
			 * at मुक्त_cnode
			 */
			get_bh(saved_bh);
			set_bit(BLOCK_NEEDS_FLUSH, &cn->state);
			lock_buffer(saved_bh);
			BUG_ON(cn->blocknr != saved_bh->b_blocknr);
			अगर (buffer_dirty(saved_bh))
				submit_logged_buffer(saved_bh);
			अन्यथा
				unlock_buffer(saved_bh);
			count++;
		पूर्ण अन्यथा अणु
			reiserfs_warning(s, "clm-2082",
					 "Unable to flush buffer %llu in %s",
					 (अचिन्हित दीर्घ दीर्घ)saved_bh->
					 b_blocknr, __func__);
		पूर्ण
मुक्त_cnode:
		cn = cn->next;
		अगर (saved_bh) अणु
			/*
			 * we incremented this to keep others from
			 * taking the buffer head away
			 */
			put_bh(saved_bh);
			अगर (atomic_पढ़ो(&saved_bh->b_count) < 0) अणु
				reiserfs_warning(s, "journal-945",
						 "saved_bh->b_count < 0");
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (count > 0) अणु
		cn = jl->j_realblock;
		जबतक (cn) अणु
			अगर (test_bit(BLOCK_NEEDS_FLUSH, &cn->state)) अणु
				अगर (!cn->bh) अणु
					reiserfs_panic(s, "journal-1011",
						       "cn->bh is NULL");
				पूर्ण

				depth = reiserfs_ग_लिखो_unlock_nested(s);
				__रुको_on_buffer(cn->bh);
				reiserfs_ग_लिखो_lock_nested(s, depth);

				अगर (!cn->bh) अणु
					reiserfs_panic(s, "journal-1012",
						       "cn->bh is NULL");
				पूर्ण
				अगर (unlikely(!buffer_uptodate(cn->bh))) अणु
#अगर_घोषित CONFIG_REISERFS_CHECK
					reiserfs_warning(s, "journal-949",
							 "buffer write failed");
#पूर्ण_अगर
					err = -EIO;
				पूर्ण
				/*
				 * note, we must clear the JDirty_रुको bit
				 * after the up to date check, otherwise we
				 * race against our flushpage routine
				 */
				BUG_ON(!test_clear_buffer_journal_dirty
				       (cn->bh));

				/* drop one ref क्रम us */
				put_bh(cn->bh);
				/* drop one ref क्रम journal_mark_dirty */
				release_buffer_page(cn->bh);
			पूर्ण
			cn = cn->next;
		पूर्ण
	पूर्ण

	अगर (err)
		reiserfs_पात(s, -EIO,
			       "Write error while pushing transaction to disk in %s",
			       __func__);
flush_older_and_वापस:

	/*
	 * beक्रमe we can update the journal header block, we _must_ flush all
	 * real blocks from all older transactions to disk.  This is because
	 * once the header block is updated, this transaction will not be
	 * replayed after a crash
	 */
	अगर (flushall) अणु
		flush_older_journal_lists(s, jl);
	पूर्ण

	err = journal->j_त्रुटि_सं;
	/*
	 * beक्रमe we can हटाओ everything from the hash tables क्रम this
	 * transaction, we must make sure it can never be replayed
	 *
	 * since we are only called from करो_journal_end, we know क्रम sure there
	 * are no allocations going on जबतक we are flushing journal lists.  So,
	 * we only need to update the journal header block क्रम the last list
	 * being flushed
	 */
	अगर (!err && flushall) अणु
		err =
		    update_journal_header_block(s,
						(jl->j_start + jl->j_len +
						 2) % SB_ONDISK_JOURNAL_SIZE(s),
						jl->j_trans_id);
		अगर (err)
			reiserfs_पात(s, -EIO,
				       "Write error while updating journal header in %s",
				       __func__);
	पूर्ण
	हटाओ_all_from_journal_list(s, jl, 0);
	list_del_init(&jl->j_list);
	journal->j_num_lists--;
	del_from_work_list(s, jl);

	अगर (journal->j_last_flush_id != 0 &&
	    (jl->j_trans_id - journal->j_last_flush_id) != 1) अणु
		reiserfs_warning(s, "clm-2201", "last flush %lu, current %lu",
				 journal->j_last_flush_id, jl->j_trans_id);
	पूर्ण
	journal->j_last_flush_id = jl->j_trans_id;

	/*
	 * not strictly required since we are मुक्तing the list, but it should
	 * help find code using dead lists later on
	 */
	jl->j_len = 0;
	atomic_set(&jl->j_nonzerolen, 0);
	jl->j_start = 0;
	jl->j_realblock = शून्य;
	jl->j_commit_bh = शून्य;
	jl->j_trans_id = 0;
	jl->j_state = 0;
	put_journal_list(s, jl);
	अगर (flushall)
		mutex_unlock(&journal->j_flush_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ग_लिखो_one_transaction(काष्ठा super_block *s,
				 काष्ठा reiserfs_journal_list *jl,
				 काष्ठा buffer_chunk *chunk)
अणु
	काष्ठा reiserfs_journal_cnode *cn;
	पूर्णांक ret = 0;

	jl->j_state |= LIST_TOUCHED;
	del_from_work_list(s, jl);
	अगर (jl->j_len == 0 || atomic_पढ़ो(&jl->j_nonzerolen) == 0) अणु
		वापस 0;
	पूर्ण

	cn = jl->j_realblock;
	जबतक (cn) अणु
		/*
		 * अगर the blocknr == 0, this has been cleared from the hash,
		 * skip it
		 */
		अगर (cn->blocknr == 0) अणु
			जाओ next;
		पूर्ण
		अगर (cn->bh && can_dirty(cn) && buffer_dirty(cn->bh)) अणु
			काष्ठा buffer_head *पंचांगp_bh;
			/*
			 * we can race against journal_mark_मुक्तd when we try
			 * to lock_buffer(cn->bh), so we have to inc the buffer
			 * count, and recheck things after locking
			 */
			पंचांगp_bh = cn->bh;
			get_bh(पंचांगp_bh);
			lock_buffer(पंचांगp_bh);
			अगर (cn->bh && can_dirty(cn) && buffer_dirty(पंचांगp_bh)) अणु
				अगर (!buffer_journal_dirty(पंचांगp_bh) ||
				    buffer_journal_prepared(पंचांगp_bh))
					BUG();
				add_to_chunk(chunk, पंचांगp_bh, शून्य, ग_लिखो_chunk);
				ret++;
			पूर्ण अन्यथा अणु
				/* note, cn->bh might be null now */
				unlock_buffer(पंचांगp_bh);
			पूर्ण
			put_bh(पंचांगp_bh);
		पूर्ण
next:
		cn = cn->next;
		cond_resched();
	पूर्ण
	वापस ret;
पूर्ण

/* used by flush_commit_list */
अटल व्योम dirty_one_transaction(काष्ठा super_block *s,
				 काष्ठा reiserfs_journal_list *jl)
अणु
	काष्ठा reiserfs_journal_cnode *cn;
	काष्ठा reiserfs_journal_list *pjl;

	jl->j_state |= LIST_सूचीTY;
	cn = jl->j_realblock;
	जबतक (cn) अणु
		/*
		 * look क्रम a more recent transaction that logged this
		 * buffer.  Only the most recent transaction with a buffer in
		 * it is allowed to send that buffer to disk
		 */
		pjl = find_newer_jl_क्रम_cn(cn);
		अगर (!pjl && cn->blocknr && cn->bh
		    && buffer_journal_dirty(cn->bh)) अणु
			BUG_ON(!can_dirty(cn));
			/*
			 * अगर the buffer is prepared, it will either be logged
			 * or restored.  If restored, we need to make sure
			 * it actually माला_लो marked dirty
			 */
			clear_buffer_journal_new(cn->bh);
			अगर (buffer_journal_prepared(cn->bh)) अणु
				set_buffer_journal_restore_dirty(cn->bh);
			पूर्ण अन्यथा अणु
				set_buffer_journal_test(cn->bh);
				mark_buffer_dirty(cn->bh);
			पूर्ण
		पूर्ण
		cn = cn->next;
	पूर्ण
पूर्ण

अटल पूर्णांक kupdate_transactions(काष्ठा super_block *s,
				काष्ठा reiserfs_journal_list *jl,
				काष्ठा reiserfs_journal_list **next_jl,
				अचिन्हित पूर्णांक *next_trans_id,
				पूर्णांक num_blocks, पूर्णांक num_trans)
अणु
	पूर्णांक ret = 0;
	पूर्णांक written = 0;
	पूर्णांक transactions_flushed = 0;
	अचिन्हित पूर्णांक orig_trans_id = jl->j_trans_id;
	काष्ठा buffer_chunk chunk;
	काष्ठा list_head *entry;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	chunk.nr = 0;

	reiserfs_mutex_lock_safe(&journal->j_flush_mutex, s);
	अगर (!journal_list_still_alive(s, orig_trans_id)) अणु
		जाओ करोne;
	पूर्ण

	/*
	 * we've got j_flush_mutex held, nobody is going to delete any
	 * of these lists out from underneath us
	 */
	जबतक ((num_trans && transactions_flushed < num_trans) ||
	       (!num_trans && written < num_blocks)) अणु

		अगर (jl->j_len == 0 || (jl->j_state & LIST_TOUCHED) ||
		    atomic_पढ़ो(&jl->j_commit_left)
		    || !(jl->j_state & LIST_सूचीTY)) अणु
			del_from_work_list(s, jl);
			अवरोध;
		पूर्ण
		ret = ग_लिखो_one_transaction(s, jl, &chunk);

		अगर (ret < 0)
			जाओ करोne;
		transactions_flushed++;
		written += ret;
		entry = jl->j_list.next;

		/* did we wrap? */
		अगर (entry == &journal->j_journal_list) अणु
			अवरोध;
		पूर्ण
		jl = JOURNAL_LIST_ENTRY(entry);

		/* करोn't bother with older transactions */
		अगर (jl->j_trans_id <= orig_trans_id)
			अवरोध;
	पूर्ण
	अगर (chunk.nr) अणु
		ग_लिखो_chunk(&chunk);
	पूर्ण

करोne:
	mutex_unlock(&journal->j_flush_mutex);
	वापस ret;
पूर्ण

/*
 * क्रम o_sync and fsync heavy applications, they tend to use
 * all the journa list slots with tiny transactions.  These
 * trigger lots and lots of calls to update the header block, which
 * adds seeks and slows things करोwn.
 *
 * This function tries to clear out a large chunk of the journal lists
 * at once, which makes everything faster since only the newest journal
 * list updates the header block
 */
अटल पूर्णांक flush_used_journal_lists(काष्ठा super_block *s,
				    काष्ठा reiserfs_journal_list *jl)
अणु
	अचिन्हित दीर्घ len = 0;
	अचिन्हित दीर्घ cur_len;
	पूर्णांक i;
	पूर्णांक limit = 256;
	काष्ठा reiserfs_journal_list *tjl;
	काष्ठा reiserfs_journal_list *flush_jl;
	अचिन्हित पूर्णांक trans_id;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);

	flush_jl = tjl = jl;

	/* in data logging mode, try harder to flush a lot of blocks */
	अगर (reiserfs_data_log(s))
		limit = 1024;
	/* flush क्रम 256 transactions or limit blocks, whichever comes first */
	क्रम (i = 0; i < 256 && len < limit; i++) अणु
		अगर (atomic_पढ़ो(&tjl->j_commit_left) ||
		    tjl->j_trans_id < jl->j_trans_id) अणु
			अवरोध;
		पूर्ण
		cur_len = atomic_पढ़ो(&tjl->j_nonzerolen);
		अगर (cur_len > 0) अणु
			tjl->j_state &= ~LIST_TOUCHED;
		पूर्ण
		len += cur_len;
		flush_jl = tjl;
		अगर (tjl->j_list.next == &journal->j_journal_list)
			अवरोध;
		tjl = JOURNAL_LIST_ENTRY(tjl->j_list.next);
	पूर्ण
	get_journal_list(jl);
	get_journal_list(flush_jl);

	/*
	 * try to find a group of blocks we can flush across all the
	 * transactions, but only bother अगर we've actually spanned
	 * across multiple lists
	 */
	अगर (flush_jl != jl)
		kupdate_transactions(s, jl, &tjl, &trans_id, len, i);

	flush_journal_list(s, flush_jl, 1);
	put_journal_list(s, flush_jl);
	put_journal_list(s, jl);
	वापस 0;
पूर्ण

/*
 * हटाओs any nodes in table with name block and dev as bh.
 * only touchs the hnext and hprev poपूर्णांकers.
 */
अटल व्योम हटाओ_journal_hash(काष्ठा super_block *sb,
			 काष्ठा reiserfs_journal_cnode **table,
			 काष्ठा reiserfs_journal_list *jl,
			 अचिन्हित दीर्घ block, पूर्णांक हटाओ_मुक्तd)
अणु
	काष्ठा reiserfs_journal_cnode *cur;
	काष्ठा reiserfs_journal_cnode **head;

	head = &(journal_hash(table, sb, block));
	अगर (!head) अणु
		वापस;
	पूर्ण
	cur = *head;
	जबतक (cur) अणु
		अगर (cur->blocknr == block && cur->sb == sb
		    && (jl == शून्य || jl == cur->jlist)
		    && (!test_bit(BLOCK_FREED, &cur->state) || हटाओ_मुक्तd)) अणु
			अगर (cur->hnext) अणु
				cur->hnext->hprev = cur->hprev;
			पूर्ण
			अगर (cur->hprev) अणु
				cur->hprev->hnext = cur->hnext;
			पूर्ण अन्यथा अणु
				*head = cur->hnext;
			पूर्ण
			cur->blocknr = 0;
			cur->sb = शून्य;
			cur->state = 0;
			/*
			 * anybody who clears the cur->bh will also
			 * dec the nonzerolen
			 */
			अगर (cur->bh && cur->jlist)
				atomic_dec(&cur->jlist->j_nonzerolen);
			cur->bh = शून्य;
			cur->jlist = शून्य;
		पूर्ण
		cur = cur->hnext;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_journal_ram(काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	kमुक्त(journal->j_current_jl);
	journal->j_num_lists--;

	vमुक्त(journal->j_cnode_मुक्त_orig);
	मुक्त_list_biपंचांगaps(sb, journal->j_list_biपंचांगap);
	मुक्त_biपंचांगap_nodes(sb);	/* must be after मुक्त_list_biपंचांगaps */
	अगर (journal->j_header_bh) अणु
		brअन्यथा(journal->j_header_bh);
	पूर्ण
	/*
	 * j_header_bh is on the journal dev, make sure
	 * not to release the journal dev until we brअन्यथा j_header_bh
	 */
	release_journal_dev(sb, journal);
	vमुक्त(journal);
पूर्ण

/*
 * call on unmount.  Only set error to 1 अगर you haven't made your way out
 * of पढ़ो_super() yet.  Any other caller must keep error at 0.
 */
अटल पूर्णांक करो_journal_release(काष्ठा reiserfs_transaction_handle *th,
			      काष्ठा super_block *sb, पूर्णांक error)
अणु
	काष्ठा reiserfs_transaction_handle myth;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);

	/*
	 * we only want to flush out transactions अगर we were
	 * called with error == 0
	 */
	अगर (!error && !sb_rकरोnly(sb)) अणु
		/* end the current trans */
		BUG_ON(!th->t_trans_id);
		करो_journal_end(th, FLUSH_ALL);

		/*
		 * make sure something माला_लो logged to क्रमce
		 * our way पूर्णांकo the flush code
		 */
		अगर (!journal_join(&myth, sb)) अणु
			reiserfs_prepare_क्रम_journal(sb,
						     SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&myth, SB_BUFFER_WITH_SB(sb));
			करो_journal_end(&myth, FLUSH_ALL);
		पूर्ण
	पूर्ण

	/* this also catches errors during the करो_journal_end above */
	अगर (!error && reiserfs_is_journal_पातed(journal)) अणु
		स_रखो(&myth, 0, माप(myth));
		अगर (!journal_join_पात(&myth, sb)) अणु
			reiserfs_prepare_क्रम_journal(sb,
						     SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&myth, SB_BUFFER_WITH_SB(sb));
			करो_journal_end(&myth, FLUSH_ALL);
		पूर्ण
	पूर्ण


	/*
	 * We must release the ग_लिखो lock here because
	 * the workqueue job (flush_async_commit) needs this lock
	 */
	reiserfs_ग_लिखो_unlock(sb);

	/*
	 * Cancel flushing of old commits. Note that neither of these works
	 * will be requeued because superblock is being shutकरोwn and करोesn't
	 * have SB_ACTIVE set.
	 */
	reiserfs_cancel_old_flush(sb);
	/* रुको क्रम all commits to finish */
	cancel_delayed_work_sync(&SB_JOURNAL(sb)->j_work);

	मुक्त_journal_ram(sb);

	reiserfs_ग_लिखो_lock(sb);

	वापस 0;
पूर्ण

/* * call on unmount.  flush all journal trans, release all alloc'd ram */
पूर्णांक journal_release(काष्ठा reiserfs_transaction_handle *th,
		    काष्ठा super_block *sb)
अणु
	वापस करो_journal_release(th, sb, 0);
पूर्ण

/* only call from an error condition inside reiserfs_पढ़ो_super!  */
पूर्णांक journal_release_error(काष्ठा reiserfs_transaction_handle *th,
			  काष्ठा super_block *sb)
अणु
	वापस करो_journal_release(th, sb, 1);
पूर्ण

/*
 * compares description block with commit block.
 * वापसs 1 अगर they dअगरfer, 0 अगर they are the same
 */
अटल पूर्णांक journal_compare_desc_commit(काष्ठा super_block *sb,
				       काष्ठा reiserfs_journal_desc *desc,
				       काष्ठा reiserfs_journal_commit *commit)
अणु
	अगर (get_commit_trans_id(commit) != get_desc_trans_id(desc) ||
	    get_commit_trans_len(commit) != get_desc_trans_len(desc) ||
	    get_commit_trans_len(commit) > SB_JOURNAL(sb)->j_trans_max ||
	    get_commit_trans_len(commit) <= 0) अणु
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * वापसs 0 अगर it did not find a description block
 * वापसs -1 अगर it found a corrupt commit block
 * वापसs 1 अगर both desc and commit were valid
 * NOTE: only called during fs mount
 */
अटल पूर्णांक journal_transaction_is_valid(काष्ठा super_block *sb,
					काष्ठा buffer_head *d_bh,
					अचिन्हित पूर्णांक *oldest_invalid_trans_id,
					अचिन्हित दीर्घ *newest_mount_id)
अणु
	काष्ठा reiserfs_journal_desc *desc;
	काष्ठा reiserfs_journal_commit *commit;
	काष्ठा buffer_head *c_bh;
	अचिन्हित दीर्घ offset;

	अगर (!d_bh)
		वापस 0;

	desc = (काष्ठा reiserfs_journal_desc *)d_bh->b_data;
	अगर (get_desc_trans_len(desc) > 0
	    && !स_भेद(get_journal_desc_magic(d_bh), JOURNAL_DESC_MAGIC, 8)) अणु
		अगर (oldest_invalid_trans_id && *oldest_invalid_trans_id
		    && get_desc_trans_id(desc) > *oldest_invalid_trans_id) अणु
			reiserfs_debug(sb, REISERFS_DEBUG_CODE,
				       "journal-986: transaction "
				       "is valid returning because trans_id %d is greater than "
				       "oldest_invalid %lu",
				       get_desc_trans_id(desc),
				       *oldest_invalid_trans_id);
			वापस 0;
		पूर्ण
		अगर (newest_mount_id
		    && *newest_mount_id > get_desc_mount_id(desc)) अणु
			reiserfs_debug(sb, REISERFS_DEBUG_CODE,
				       "journal-1087: transaction "
				       "is valid returning because mount_id %d is less than "
				       "newest_mount_id %lu",
				       get_desc_mount_id(desc),
				       *newest_mount_id);
			वापस -1;
		पूर्ण
		अगर (get_desc_trans_len(desc) > SB_JOURNAL(sb)->j_trans_max) अणु
			reiserfs_warning(sb, "journal-2018",
					 "Bad transaction length %d "
					 "encountered, ignoring transaction",
					 get_desc_trans_len(desc));
			वापस -1;
		पूर्ण
		offset = d_bh->b_blocknr - SB_ONDISK_JOURNAL_1st_BLOCK(sb);

		/*
		 * ok, we have a journal description block,
		 * let's see अगर the transaction was valid
		 */
		c_bh =
		    journal_bपढ़ो(sb,
				  SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
				  ((offset + get_desc_trans_len(desc) +
				    1) % SB_ONDISK_JOURNAL_SIZE(sb)));
		अगर (!c_bh)
			वापस 0;
		commit = (काष्ठा reiserfs_journal_commit *)c_bh->b_data;
		अगर (journal_compare_desc_commit(sb, desc, commit)) अणु
			reiserfs_debug(sb, REISERFS_DEBUG_CODE,
				       "journal_transaction_is_valid, commit offset %ld had bad "
				       "time %d or length %d",
				       c_bh->b_blocknr -
				       SB_ONDISK_JOURNAL_1st_BLOCK(sb),
				       get_commit_trans_id(commit),
				       get_commit_trans_len(commit));
			brअन्यथा(c_bh);
			अगर (oldest_invalid_trans_id) अणु
				*oldest_invalid_trans_id =
				    get_desc_trans_id(desc);
				reiserfs_debug(sb, REISERFS_DEBUG_CODE,
					       "journal-1004: "
					       "transaction_is_valid setting oldest invalid trans_id "
					       "to %d",
					       get_desc_trans_id(desc));
			पूर्ण
			वापस -1;
		पूर्ण
		brअन्यथा(c_bh);
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal-1006: found valid "
			       "transaction start offset %llu, len %d id %d",
			       d_bh->b_blocknr -
			       SB_ONDISK_JOURNAL_1st_BLOCK(sb),
			       get_desc_trans_len(desc),
			       get_desc_trans_id(desc));
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम brअन्यथा_array(काष्ठा buffer_head **heads, पूर्णांक num)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < num; i++) अणु
		brअन्यथा(heads[i]);
	पूर्ण
पूर्ण

/*
 * given the start, and values क्रम the oldest acceptable transactions,
 * this either पढ़ोs in a replays a transaction, or वापसs because the
 * transaction is invalid, or too old.
 * NOTE: only called during fs mount
 */
अटल पूर्णांक journal_पढ़ो_transaction(काष्ठा super_block *sb,
				    अचिन्हित दीर्घ cur_dblock,
				    अचिन्हित दीर्घ oldest_start,
				    अचिन्हित पूर्णांक oldest_trans_id,
				    अचिन्हित दीर्घ newest_mount_id)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_journal_desc *desc;
	काष्ठा reiserfs_journal_commit *commit;
	अचिन्हित पूर्णांक trans_id = 0;
	काष्ठा buffer_head *c_bh;
	काष्ठा buffer_head *d_bh;
	काष्ठा buffer_head **log_blocks = शून्य;
	काष्ठा buffer_head **real_blocks = शून्य;
	अचिन्हित पूर्णांक trans_offset;
	पूर्णांक i;
	पूर्णांक trans_half;

	d_bh = journal_bपढ़ो(sb, cur_dblock);
	अगर (!d_bh)
		वापस 1;
	desc = (काष्ठा reiserfs_journal_desc *)d_bh->b_data;
	trans_offset = d_bh->b_blocknr - SB_ONDISK_JOURNAL_1st_BLOCK(sb);
	reiserfs_debug(sb, REISERFS_DEBUG_CODE, "journal-1037: "
		       "journal_read_transaction, offset %llu, len %d mount_id %d",
		       d_bh->b_blocknr - SB_ONDISK_JOURNAL_1st_BLOCK(sb),
		       get_desc_trans_len(desc), get_desc_mount_id(desc));
	अगर (get_desc_trans_id(desc) < oldest_trans_id) अणु
		reiserfs_debug(sb, REISERFS_DEBUG_CODE, "journal-1039: "
			       "journal_read_trans skipping because %lu is too old",
			       cur_dblock -
			       SB_ONDISK_JOURNAL_1st_BLOCK(sb));
		brअन्यथा(d_bh);
		वापस 1;
	पूर्ण
	अगर (get_desc_mount_id(desc) != newest_mount_id) अणु
		reiserfs_debug(sb, REISERFS_DEBUG_CODE, "journal-1146: "
			       "journal_read_trans skipping because %d is != "
			       "newest_mount_id %lu", get_desc_mount_id(desc),
			       newest_mount_id);
		brअन्यथा(d_bh);
		वापस 1;
	पूर्ण
	c_bh = journal_bपढ़ो(sb, SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
			     ((trans_offset + get_desc_trans_len(desc) + 1) %
			      SB_ONDISK_JOURNAL_SIZE(sb)));
	अगर (!c_bh) अणु
		brअन्यथा(d_bh);
		वापस 1;
	पूर्ण
	commit = (काष्ठा reiserfs_journal_commit *)c_bh->b_data;
	अगर (journal_compare_desc_commit(sb, desc, commit)) अणु
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal_read_transaction, "
			       "commit offset %llu had bad time %d or length %d",
			       c_bh->b_blocknr -
			       SB_ONDISK_JOURNAL_1st_BLOCK(sb),
			       get_commit_trans_id(commit),
			       get_commit_trans_len(commit));
		brअन्यथा(c_bh);
		brअन्यथा(d_bh);
		वापस 1;
	पूर्ण

	अगर (bdev_पढ़ो_only(sb->s_bdev)) अणु
		reiserfs_warning(sb, "clm-2076",
				 "device is readonly, unable to replay log");
		brअन्यथा(c_bh);
		brअन्यथा(d_bh);
		वापस -EROFS;
	पूर्ण

	trans_id = get_desc_trans_id(desc);
	/*
	 * now we know we've got a good transaction, and it was
	 * inside the valid समय ranges
	 */
	log_blocks = kदो_स्मृति_array(get_desc_trans_len(desc),
				   माप(काष्ठा buffer_head *),
				   GFP_NOFS);
	real_blocks = kदो_स्मृति_array(get_desc_trans_len(desc),
				    माप(काष्ठा buffer_head *),
				    GFP_NOFS);
	अगर (!log_blocks || !real_blocks) अणु
		brअन्यथा(c_bh);
		brअन्यथा(d_bh);
		kमुक्त(log_blocks);
		kमुक्त(real_blocks);
		reiserfs_warning(sb, "journal-1169",
				 "kmalloc failed, unable to mount FS");
		वापस -1;
	पूर्ण
	/* get all the buffer heads */
	trans_half = journal_trans_half(sb->s_blocksize);
	क्रम (i = 0; i < get_desc_trans_len(desc); i++) अणु
		log_blocks[i] =
		    journal_getblk(sb,
				   SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
				   (trans_offset + 1 +
				    i) % SB_ONDISK_JOURNAL_SIZE(sb));
		अगर (i < trans_half) अणु
			real_blocks[i] =
			    sb_getblk(sb,
				      le32_to_cpu(desc->j_realblock[i]));
		पूर्ण अन्यथा अणु
			real_blocks[i] =
			    sb_getblk(sb,
				      le32_to_cpu(commit->
						  j_realblock[i - trans_half]));
		पूर्ण
		अगर (real_blocks[i]->b_blocknr > SB_BLOCK_COUNT(sb)) अणु
			reiserfs_warning(sb, "journal-1207",
					 "REPLAY FAILURE fsck required! "
					 "Block to replay is outside of "
					 "filesystem");
			जाओ पात_replay;
		पूर्ण
		/* make sure we करोn't try to replay onto log or reserved area */
		अगर (is_block_in_log_or_reserved_area
		    (sb, real_blocks[i]->b_blocknr)) अणु
			reiserfs_warning(sb, "journal-1204",
					 "REPLAY FAILURE fsck required! "
					 "Trying to replay onto a log block");
पात_replay:
			brअन्यथा_array(log_blocks, i);
			brअन्यथा_array(real_blocks, i);
			brअन्यथा(c_bh);
			brअन्यथा(d_bh);
			kमुक्त(log_blocks);
			kमुक्त(real_blocks);
			वापस -1;
		पूर्ण
	पूर्ण
	/* पढ़ो in the log blocks, स_नकल to the corresponding real block */
	ll_rw_block(REQ_OP_READ, 0, get_desc_trans_len(desc), log_blocks);
	क्रम (i = 0; i < get_desc_trans_len(desc); i++) अणु

		रुको_on_buffer(log_blocks[i]);
		अगर (!buffer_uptodate(log_blocks[i])) अणु
			reiserfs_warning(sb, "journal-1212",
					 "REPLAY FAILURE fsck required! "
					 "buffer write failed");
			brअन्यथा_array(log_blocks + i,
				     get_desc_trans_len(desc) - i);
			brअन्यथा_array(real_blocks, get_desc_trans_len(desc));
			brअन्यथा(c_bh);
			brअन्यथा(d_bh);
			kमुक्त(log_blocks);
			kमुक्त(real_blocks);
			वापस -1;
		पूर्ण
		स_नकल(real_blocks[i]->b_data, log_blocks[i]->b_data,
		       real_blocks[i]->b_size);
		set_buffer_uptodate(real_blocks[i]);
		brअन्यथा(log_blocks[i]);
	पूर्ण
	/* flush out the real blocks */
	क्रम (i = 0; i < get_desc_trans_len(desc); i++) अणु
		set_buffer_dirty(real_blocks[i]);
		ग_लिखो_dirty_buffer(real_blocks[i], 0);
	पूर्ण
	क्रम (i = 0; i < get_desc_trans_len(desc); i++) अणु
		रुको_on_buffer(real_blocks[i]);
		अगर (!buffer_uptodate(real_blocks[i])) अणु
			reiserfs_warning(sb, "journal-1226",
					 "REPLAY FAILURE, fsck required! "
					 "buffer write failed");
			brअन्यथा_array(real_blocks + i,
				     get_desc_trans_len(desc) - i);
			brअन्यथा(c_bh);
			brअन्यथा(d_bh);
			kमुक्त(log_blocks);
			kमुक्त(real_blocks);
			वापस -1;
		पूर्ण
		brअन्यथा(real_blocks[i]);
	पूर्ण
	cur_dblock =
	    SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
	    ((trans_offset + get_desc_trans_len(desc) +
	      2) % SB_ONDISK_JOURNAL_SIZE(sb));
	reiserfs_debug(sb, REISERFS_DEBUG_CODE,
		       "journal-1095: setting journal " "start to offset %ld",
		       cur_dblock - SB_ONDISK_JOURNAL_1st_BLOCK(sb));

	/*
	 * init starting values क्रम the first transaction, in हाल
	 * this is the last transaction to be replayed.
	 */
	journal->j_start = cur_dblock - SB_ONDISK_JOURNAL_1st_BLOCK(sb);
	journal->j_last_flush_trans_id = trans_id;
	journal->j_trans_id = trans_id + 1;
	/* check क्रम trans_id overflow */
	अगर (journal->j_trans_id == 0)
		journal->j_trans_id = 10;
	brअन्यथा(c_bh);
	brअन्यथा(d_bh);
	kमुक्त(log_blocks);
	kमुक्त(real_blocks);
	वापस 0;
पूर्ण

/*
 * This function पढ़ोs blocks starting from block and to max_block of bufsize
 * size (but no more than BUFNR blocks at a समय). This proved to improve
 * mounting speed on self-rebuilding raid5 arrays at least.
 * Right now it is only used from journal code. But later we might use it
 * from other places.
 * Note: Do not use journal_getblk/sb_getblk functions here!
 */
अटल काष्ठा buffer_head *reiserfs_bपढ़ोa(काष्ठा block_device *dev,
					   b_blocknr_t block, पूर्णांक bufsize,
					   b_blocknr_t max_block)
अणु
	काष्ठा buffer_head *bhlist[BUFNR];
	अचिन्हित पूर्णांक blocks = BUFNR;
	काष्ठा buffer_head *bh;
	पूर्णांक i, j;

	bh = __getblk(dev, block, bufsize);
	अगर (buffer_uptodate(bh))
		वापस (bh);

	अगर (block + BUFNR > max_block) अणु
		blocks = max_block - block;
	पूर्ण
	bhlist[0] = bh;
	j = 1;
	क्रम (i = 1; i < blocks; i++) अणु
		bh = __getblk(dev, block + i, bufsize);
		अगर (buffer_uptodate(bh)) अणु
			brअन्यथा(bh);
			अवरोध;
		पूर्ण अन्यथा
			bhlist[j++] = bh;
	पूर्ण
	ll_rw_block(REQ_OP_READ, 0, j, bhlist);
	क्रम (i = 1; i < j; i++)
		brअन्यथा(bhlist[i]);
	bh = bhlist[0];
	रुको_on_buffer(bh);
	अगर (buffer_uptodate(bh))
		वापस bh;
	brअन्यथा(bh);
	वापस शून्य;
पूर्ण

/*
 * पढ़ो and replay the log
 * on a clean unmount, the journal header's next unflushed poपूर्णांकer will be
 * to an invalid transaction.  This tests that beक्रमe finding all the
 * transactions in the log, which makes normal mount बार fast.
 *
 * After a crash, this starts with the next unflushed transaction, and
 * replays until it finds one too old, or invalid.
 *
 * On निकास, it sets things up so the first transaction will work correctly.
 * NOTE: only called during fs mount
 */
अटल पूर्णांक journal_पढ़ो(काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_journal_desc *desc;
	अचिन्हित पूर्णांक oldest_trans_id = 0;
	अचिन्हित पूर्णांक oldest_invalid_trans_id = 0;
	समय64_t start;
	अचिन्हित दीर्घ oldest_start = 0;
	अचिन्हित दीर्घ cur_dblock = 0;
	अचिन्हित दीर्घ newest_mount_id = 9;
	काष्ठा buffer_head *d_bh;
	काष्ठा reiserfs_journal_header *jh;
	पूर्णांक valid_journal_header = 0;
	पूर्णांक replay_count = 0;
	पूर्णांक जारी_replay = 1;
	पूर्णांक ret;

	cur_dblock = SB_ONDISK_JOURNAL_1st_BLOCK(sb);
	reiserfs_info(sb, "checking transaction log (%pg)\n",
		      journal->j_dev_bd);
	start = kसमय_get_seconds();

	/*
	 * step 1, पढ़ो in the journal header block.  Check the transaction
	 * it says is the first unflushed, and अगर that transaction is not
	 * valid, replay is करोne
	 */
	journal->j_header_bh = journal_bपढ़ो(sb,
					     SB_ONDISK_JOURNAL_1st_BLOCK(sb)
					     + SB_ONDISK_JOURNAL_SIZE(sb));
	अगर (!journal->j_header_bh) अणु
		वापस 1;
	पूर्ण
	jh = (काष्ठा reiserfs_journal_header *)(journal->j_header_bh->b_data);
	अगर (le32_to_cpu(jh->j_first_unflushed_offset) <
	    SB_ONDISK_JOURNAL_SIZE(sb)
	    && le32_to_cpu(jh->j_last_flush_trans_id) > 0) अणु
		oldest_start =
		    SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
		    le32_to_cpu(jh->j_first_unflushed_offset);
		oldest_trans_id = le32_to_cpu(jh->j_last_flush_trans_id) + 1;
		newest_mount_id = le32_to_cpu(jh->j_mount_id);
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal-1153: found in "
			       "header: first_unflushed_offset %d, last_flushed_trans_id "
			       "%lu", le32_to_cpu(jh->j_first_unflushed_offset),
			       le32_to_cpu(jh->j_last_flush_trans_id));
		valid_journal_header = 1;

		/*
		 * now, we try to पढ़ो the first unflushed offset.  If it
		 * is not valid, there is nothing more we can करो, and it
		 * makes no sense to पढ़ो through the whole log.
		 */
		d_bh =
		    journal_bपढ़ो(sb,
				  SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
				  le32_to_cpu(jh->j_first_unflushed_offset));
		ret = journal_transaction_is_valid(sb, d_bh, शून्य, शून्य);
		अगर (!ret) अणु
			जारी_replay = 0;
		पूर्ण
		brअन्यथा(d_bh);
		जाओ start_log_replay;
	पूर्ण

	/*
	 * ok, there are transactions that need to be replayed.  start
	 * with the first log block, find all the valid transactions, and
	 * pick out the oldest.
	 */
	जबतक (जारी_replay
	       && cur_dblock <
	       (SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
		SB_ONDISK_JOURNAL_SIZE(sb))) अणु
		/*
		 * Note that it is required क्रम blocksize of primary fs
		 * device and journal device to be the same
		 */
		d_bh =
		    reiserfs_bपढ़ोa(journal->j_dev_bd, cur_dblock,
				    sb->s_blocksize,
				    SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
				    SB_ONDISK_JOURNAL_SIZE(sb));
		ret =
		    journal_transaction_is_valid(sb, d_bh,
						 &oldest_invalid_trans_id,
						 &newest_mount_id);
		अगर (ret == 1) अणु
			desc = (काष्ठा reiserfs_journal_desc *)d_bh->b_data;
			अगर (oldest_start == 0) अणु	/* init all oldest_ values */
				oldest_trans_id = get_desc_trans_id(desc);
				oldest_start = d_bh->b_blocknr;
				newest_mount_id = get_desc_mount_id(desc);
				reiserfs_debug(sb, REISERFS_DEBUG_CODE,
					       "journal-1179: Setting "
					       "oldest_start to offset %llu, trans_id %lu",
					       oldest_start -
					       SB_ONDISK_JOURNAL_1st_BLOCK
					       (sb), oldest_trans_id);
			पूर्ण अन्यथा अगर (oldest_trans_id > get_desc_trans_id(desc)) अणु
				/* one we just पढ़ो was older */
				oldest_trans_id = get_desc_trans_id(desc);
				oldest_start = d_bh->b_blocknr;
				reiserfs_debug(sb, REISERFS_DEBUG_CODE,
					       "journal-1180: Resetting "
					       "oldest_start to offset %lu, trans_id %lu",
					       oldest_start -
					       SB_ONDISK_JOURNAL_1st_BLOCK
					       (sb), oldest_trans_id);
			पूर्ण
			अगर (newest_mount_id < get_desc_mount_id(desc)) अणु
				newest_mount_id = get_desc_mount_id(desc);
				reiserfs_debug(sb, REISERFS_DEBUG_CODE,
					       "journal-1299: Setting "
					       "newest_mount_id to %d",
					       get_desc_mount_id(desc));
			पूर्ण
			cur_dblock += get_desc_trans_len(desc) + 2;
		पूर्ण अन्यथा अणु
			cur_dblock++;
		पूर्ण
		brअन्यथा(d_bh);
	पूर्ण

start_log_replay:
	cur_dblock = oldest_start;
	अगर (oldest_trans_id) अणु
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal-1206: Starting replay "
			       "from offset %llu, trans_id %lu",
			       cur_dblock - SB_ONDISK_JOURNAL_1st_BLOCK(sb),
			       oldest_trans_id);

	पूर्ण
	replay_count = 0;
	जबतक (जारी_replay && oldest_trans_id > 0) अणु
		ret =
		    journal_पढ़ो_transaction(sb, cur_dblock, oldest_start,
					     oldest_trans_id, newest_mount_id);
		अगर (ret < 0) अणु
			वापस ret;
		पूर्ण अन्यथा अगर (ret != 0) अणु
			अवरोध;
		पूर्ण
		cur_dblock =
		    SB_ONDISK_JOURNAL_1st_BLOCK(sb) + journal->j_start;
		replay_count++;
		अगर (cur_dblock == oldest_start)
			अवरोध;
	पूर्ण

	अगर (oldest_trans_id == 0) अणु
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal-1225: No valid " "transactions found");
	पूर्ण
	/*
	 * j_start करोes not get set correctly अगर we करोn't replay any
	 * transactions.  अगर we had a valid journal_header, set j_start
	 * to the first unflushed transaction value, copy the trans_id
	 * from the header
	 */
	अगर (valid_journal_header && replay_count == 0) अणु
		journal->j_start = le32_to_cpu(jh->j_first_unflushed_offset);
		journal->j_trans_id =
		    le32_to_cpu(jh->j_last_flush_trans_id) + 1;
		/* check क्रम trans_id overflow */
		अगर (journal->j_trans_id == 0)
			journal->j_trans_id = 10;
		journal->j_last_flush_trans_id =
		    le32_to_cpu(jh->j_last_flush_trans_id);
		journal->j_mount_id = le32_to_cpu(jh->j_mount_id) + 1;
	पूर्ण अन्यथा अणु
		journal->j_mount_id = newest_mount_id + 1;
	पूर्ण
	reiserfs_debug(sb, REISERFS_DEBUG_CODE, "journal-1299: Setting "
		       "newest_mount_id to %lu", journal->j_mount_id);
	journal->j_first_unflushed_offset = journal->j_start;
	अगर (replay_count > 0) अणु
		reiserfs_info(sb,
			      "replayed %d transactions in %lu seconds\n",
			      replay_count, kसमय_get_seconds() - start);
	पूर्ण
	/* needed to satisfy the locking in _update_journal_header_block */
	reiserfs_ग_लिखो_lock(sb);
	अगर (!bdev_पढ़ो_only(sb->s_bdev) &&
	    _update_journal_header_block(sb, journal->j_start,
					 journal->j_last_flush_trans_id)) अणु
		reiserfs_ग_लिखो_unlock(sb);
		/*
		 * replay failed, caller must call मुक्त_journal_ram and पात
		 * the mount
		 */
		वापस -1;
	पूर्ण
	reiserfs_ग_लिखो_unlock(sb);
	वापस 0;
पूर्ण

अटल काष्ठा reiserfs_journal_list *alloc_journal_list(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_journal_list *jl;
	jl = kzalloc(माप(काष्ठा reiserfs_journal_list),
		     GFP_NOFS | __GFP_NOFAIL);
	INIT_LIST_HEAD(&jl->j_list);
	INIT_LIST_HEAD(&jl->j_working_list);
	INIT_LIST_HEAD(&jl->j_tail_bh_list);
	INIT_LIST_HEAD(&jl->j_bh_list);
	mutex_init(&jl->j_commit_mutex);
	SB_JOURNAL(s)->j_num_lists++;
	get_journal_list(jl);
	वापस jl;
पूर्ण

अटल व्योम journal_list_init(काष्ठा super_block *sb)
अणु
	SB_JOURNAL(sb)->j_current_jl = alloc_journal_list(sb);
पूर्ण

अटल व्योम release_journal_dev(काष्ठा super_block *super,
			       काष्ठा reiserfs_journal *journal)
अणु
	अगर (journal->j_dev_bd != शून्य) अणु
		blkdev_put(journal->j_dev_bd, journal->j_dev_mode);
		journal->j_dev_bd = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक journal_init_dev(काष्ठा super_block *super,
			    काष्ठा reiserfs_journal *journal,
			    स्थिर अक्षर *jdev_name)
अणु
	पूर्णांक result;
	dev_t jdev;
	भ_शेषe_t blkdev_mode = FMODE_READ | FMODE_WRITE | FMODE_EXCL;

	result = 0;

	journal->j_dev_bd = शून्य;
	jdev = SB_ONDISK_JOURNAL_DEVICE(super) ?
	    new_decode_dev(SB_ONDISK_JOURNAL_DEVICE(super)) : super->s_dev;

	अगर (bdev_पढ़ो_only(super->s_bdev))
		blkdev_mode = FMODE_READ;

	/* there is no "jdev" option and journal is on separate device */
	अगर ((!jdev_name || !jdev_name[0])) अणु
		अगर (jdev == super->s_dev)
			blkdev_mode &= ~FMODE_EXCL;
		journal->j_dev_bd = blkdev_get_by_dev(jdev, blkdev_mode,
						      journal);
		journal->j_dev_mode = blkdev_mode;
		अगर (IS_ERR(journal->j_dev_bd)) अणु
			result = PTR_ERR(journal->j_dev_bd);
			journal->j_dev_bd = शून्य;
			reiserfs_warning(super, "sh-458",
					 "cannot init journal device unknown-block(%u,%u): %i",
					 MAJOR(jdev), MINOR(jdev), result);
			वापस result;
		पूर्ण अन्यथा अगर (jdev != super->s_dev)
			set_blocksize(journal->j_dev_bd, super->s_blocksize);

		वापस 0;
	पूर्ण

	journal->j_dev_mode = blkdev_mode;
	journal->j_dev_bd = blkdev_get_by_path(jdev_name, blkdev_mode, journal);
	अगर (IS_ERR(journal->j_dev_bd)) अणु
		result = PTR_ERR(journal->j_dev_bd);
		journal->j_dev_bd = शून्य;
		reiserfs_warning(super, "sh-457",
				 "journal_init_dev: Cannot open '%s': %i",
				 jdev_name, result);
		वापस result;
	पूर्ण

	set_blocksize(journal->j_dev_bd, super->s_blocksize);
	reiserfs_info(super,
		      "journal_init_dev: journal device: %pg\n",
		      journal->j_dev_bd);
	वापस 0;
पूर्ण

/*
 * When creating/tuning a file प्रणाली user can assign some
 * journal params within boundaries which depend on the ratio
 * blocksize/standard_blocksize.
 *
 * For blocks >= standard_blocksize transaction size should
 * be not less then JOURNAL_TRANS_MIN_DEFAULT, and not more
 * then JOURNAL_TRANS_MAX_DEFAULT.
 *
 * For blocks < standard_blocksize these boundaries should be
 * decreased proportionally.
 */
#घोषणा REISERFS_STANDARD_BLKSIZE (4096)

अटल पूर्णांक check_advise_trans_params(काष्ठा super_block *sb,
				     काष्ठा reiserfs_journal *journal)
अणु
        अगर (journal->j_trans_max) अणु
		/* Non-शेष journal params.  Do sanity check क्रम them. */
	        पूर्णांक ratio = 1;
		अगर (sb->s_blocksize < REISERFS_STANDARD_BLKSIZE)
		        ratio = REISERFS_STANDARD_BLKSIZE / sb->s_blocksize;

		अगर (journal->j_trans_max > JOURNAL_TRANS_MAX_DEFAULT / ratio ||
		    journal->j_trans_max < JOURNAL_TRANS_MIN_DEFAULT / ratio ||
		    SB_ONDISK_JOURNAL_SIZE(sb) / journal->j_trans_max <
		    JOURNAL_MIN_RATIO) अणु
			reiserfs_warning(sb, "sh-462",
					 "bad transaction max size (%u). "
					 "FSCK?", journal->j_trans_max);
			वापस 1;
		पूर्ण
		अगर (journal->j_max_batch != (journal->j_trans_max) *
		        JOURNAL_MAX_BATCH_DEFAULT/JOURNAL_TRANS_MAX_DEFAULT) अणु
			reiserfs_warning(sb, "sh-463",
					 "bad transaction max batch (%u). "
					 "FSCK?", journal->j_max_batch);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Default journal params.
		 * The file प्रणाली was created by old version
		 * of mkreiserfs, so some fields contain zeros,
		 * and we need to advise proper values क्रम them
		 */
		अगर (sb->s_blocksize != REISERFS_STANDARD_BLKSIZE) अणु
			reiserfs_warning(sb, "sh-464", "bad blocksize (%u)",
					 sb->s_blocksize);
			वापस 1;
		पूर्ण
		journal->j_trans_max = JOURNAL_TRANS_MAX_DEFAULT;
		journal->j_max_batch = JOURNAL_MAX_BATCH_DEFAULT;
		journal->j_max_commit_age = JOURNAL_MAX_COMMIT_AGE;
	पूर्ण
	वापस 0;
पूर्ण

/* must be called once on fs mount.  calls journal_पढ़ो क्रम you */
पूर्णांक journal_init(काष्ठा super_block *sb, स्थिर अक्षर *j_dev_name,
		 पूर्णांक old_क्रमmat, अचिन्हित पूर्णांक commit_max_age)
अणु
	पूर्णांक num_cnodes = SB_ONDISK_JOURNAL_SIZE(sb) * 2;
	काष्ठा buffer_head *bhjh;
	काष्ठा reiserfs_super_block *rs;
	काष्ठा reiserfs_journal_header *jh;
	काष्ठा reiserfs_journal *journal;
	काष्ठा reiserfs_journal_list *jl;
	पूर्णांक ret;

	journal = SB_JOURNAL(sb) = vzalloc(माप(काष्ठा reiserfs_journal));
	अगर (!journal) अणु
		reiserfs_warning(sb, "journal-1256",
				 "unable to get memory for journal structure");
		वापस 1;
	पूर्ण
	INIT_LIST_HEAD(&journal->j_biपंचांगap_nodes);
	INIT_LIST_HEAD(&journal->j_pपुनः_स्मृति_list);
	INIT_LIST_HEAD(&journal->j_working_list);
	INIT_LIST_HEAD(&journal->j_journal_list);
	journal->j_persistent_trans = 0;
	अगर (reiserfs_allocate_list_biपंचांगaps(sb, journal->j_list_biपंचांगap,
					   reiserfs_bmap_count(sb)))
		जाओ मुक्त_and_वापस;

	allocate_biपंचांगap_nodes(sb);

	/* reserved क्रम journal area support */
	SB_JOURNAL_1st_RESERVED_BLOCK(sb) = (old_क्रमmat ?
						 REISERFS_OLD_DISK_OFFSET_IN_BYTES
						 / sb->s_blocksize +
						 reiserfs_bmap_count(sb) +
						 1 :
						 REISERFS_DISK_OFFSET_IN_BYTES /
						 sb->s_blocksize + 2);

	/*
	 * Sanity check to see is the standard journal fitting
	 * within first biपंचांगap (actual क्रम small blocksizes)
	 */
	अगर (!SB_ONDISK_JOURNAL_DEVICE(sb) &&
	    (SB_JOURNAL_1st_RESERVED_BLOCK(sb) +
	     SB_ONDISK_JOURNAL_SIZE(sb) > sb->s_blocksize * 8)) अणु
		reiserfs_warning(sb, "journal-1393",
				 "journal does not fit for area addressed "
				 "by first of bitmap blocks. It starts at "
				 "%u and its size is %u. Block size %ld",
				 SB_JOURNAL_1st_RESERVED_BLOCK(sb),
				 SB_ONDISK_JOURNAL_SIZE(sb),
				 sb->s_blocksize);
		जाओ मुक्त_and_वापस;
	पूर्ण

	अगर (journal_init_dev(sb, journal, j_dev_name) != 0) अणु
		reiserfs_warning(sb, "sh-462",
				 "unable to initialize journal device");
		जाओ मुक्त_and_वापस;
	पूर्ण

	rs = SB_DISK_SUPER_BLOCK(sb);

	/* पढ़ो journal header */
	bhjh = journal_bपढ़ो(sb,
			     SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
			     SB_ONDISK_JOURNAL_SIZE(sb));
	अगर (!bhjh) अणु
		reiserfs_warning(sb, "sh-459",
				 "unable to read journal header");
		जाओ मुक्त_and_वापस;
	पूर्ण
	jh = (काष्ठा reiserfs_journal_header *)(bhjh->b_data);

	/* make sure that journal matches to the super block */
	अगर (is_reiserfs_jr(rs)
	    && (le32_to_cpu(jh->jh_journal.jp_journal_magic) !=
		sb_jp_journal_magic(rs))) अणु
		reiserfs_warning(sb, "sh-460",
				 "journal header magic %x (device %pg) does "
				 "not match to magic found in super block %x",
				 jh->jh_journal.jp_journal_magic,
				 journal->j_dev_bd,
				 sb_jp_journal_magic(rs));
		brअन्यथा(bhjh);
		जाओ मुक्त_and_वापस;
	पूर्ण

	journal->j_trans_max = le32_to_cpu(jh->jh_journal.jp_journal_trans_max);
	journal->j_max_batch = le32_to_cpu(jh->jh_journal.jp_journal_max_batch);
	journal->j_max_commit_age =
	    le32_to_cpu(jh->jh_journal.jp_journal_max_commit_age);
	journal->j_max_trans_age = JOURNAL_MAX_TRANS_AGE;

	अगर (check_advise_trans_params(sb, journal) != 0)
	        जाओ मुक्त_and_वापस;
	journal->j_शेष_max_commit_age = journal->j_max_commit_age;

	अगर (commit_max_age != 0) अणु
		journal->j_max_commit_age = commit_max_age;
		journal->j_max_trans_age = commit_max_age;
	पूर्ण

	reiserfs_info(sb, "journal params: device %pg, size %u, "
		      "journal first block %u, max trans len %u, max batch %u, "
		      "max commit age %u, max trans age %u\n",
		      journal->j_dev_bd,
		      SB_ONDISK_JOURNAL_SIZE(sb),
		      SB_ONDISK_JOURNAL_1st_BLOCK(sb),
		      journal->j_trans_max,
		      journal->j_max_batch,
		      journal->j_max_commit_age, journal->j_max_trans_age);

	brअन्यथा(bhjh);

	journal->j_list_biपंचांगap_index = 0;
	journal_list_init(sb);

	स_रखो(journal->j_list_hash_table, 0,
	       JOURNAL_HASH_SIZE * माप(काष्ठा reiserfs_journal_cnode *));

	INIT_LIST_HEAD(&journal->j_dirty_buffers);
	spin_lock_init(&journal->j_dirty_buffers_lock);

	journal->j_start = 0;
	journal->j_len = 0;
	journal->j_len_alloc = 0;
	atomic_set(&journal->j_wcount, 0);
	atomic_set(&journal->j_async_throttle, 0);
	journal->j_bcount = 0;
	journal->j_trans_start_समय = 0;
	journal->j_last = शून्य;
	journal->j_first = शून्य;
	init_रुकोqueue_head(&journal->j_join_रुको);
	mutex_init(&journal->j_mutex);
	mutex_init(&journal->j_flush_mutex);

	journal->j_trans_id = 10;
	journal->j_mount_id = 10;
	journal->j_state = 0;
	atomic_set(&journal->j_jlock, 0);
	journal->j_cnode_मुक्त_list = allocate_cnodes(num_cnodes);
	journal->j_cnode_मुक्त_orig = journal->j_cnode_मुक्त_list;
	journal->j_cnode_मुक्त = journal->j_cnode_मुक्त_list ? num_cnodes : 0;
	journal->j_cnode_used = 0;
	journal->j_must_रुको = 0;

	अगर (journal->j_cnode_मुक्त == 0) अणु
		reiserfs_warning(sb, "journal-2004", "Journal cnode memory "
		                 "allocation failed (%ld bytes). Journal is "
		                 "too large for available memory. Usually "
		                 "this is due to a journal that is too large.",
		                 माप (काष्ठा reiserfs_journal_cnode) * num_cnodes);
        	जाओ मुक्त_and_वापस;
	पूर्ण

	init_journal_hash(sb);
	jl = journal->j_current_jl;

	/*
	 * get_list_biपंचांगap() may call flush_commit_list() which
	 * requires the lock. Calling flush_commit_list() shouldn't happen
	 * this early but I like to be paranoid.
	 */
	reiserfs_ग_लिखो_lock(sb);
	jl->j_list_biपंचांगap = get_list_biपंचांगap(sb, jl);
	reiserfs_ग_लिखो_unlock(sb);
	अगर (!jl->j_list_biपंचांगap) अणु
		reiserfs_warning(sb, "journal-2005",
				 "get_list_bitmap failed for journal list 0");
		जाओ मुक्त_and_वापस;
	पूर्ण

	ret = journal_पढ़ो(sb);
	अगर (ret < 0) अणु
		reiserfs_warning(sb, "reiserfs-2006",
				 "Replay Failure, unable to mount");
		जाओ मुक्त_and_वापस;
	पूर्ण

	INIT_DELAYED_WORK(&journal->j_work, flush_async_commits);
	journal->j_work_sb = sb;
	वापस 0;
मुक्त_and_वापस:
	मुक्त_journal_ram(sb);
	वापस 1;
पूर्ण

/*
 * test क्रम a polite end of the current transaction.  Used by file_ग_लिखो,
 * and should be used by delete to make sure they करोn't ग_लिखो more than
 * can fit inside a single transaction
 */
पूर्णांक journal_transaction_should_end(काष्ठा reiserfs_transaction_handle *th,
				   पूर्णांक new_alloc)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(th->t_super);
	समय64_t now = kसमय_get_seconds();
	/* cannot restart जबतक nested */
	BUG_ON(!th->t_trans_id);
	अगर (th->t_refcount > 1)
		वापस 0;
	अगर (journal->j_must_रुको > 0 ||
	    (journal->j_len_alloc + new_alloc) >= journal->j_max_batch ||
	    atomic_पढ़ो(&journal->j_jlock) ||
	    (now - journal->j_trans_start_समय) > journal->j_max_trans_age ||
	    journal->j_cnode_मुक्त < (journal->j_trans_max * 3)) अणु
		वापस 1;
	पूर्ण

	journal->j_len_alloc += new_alloc;
	th->t_blocks_allocated += new_alloc ;
	वापस 0;
पूर्ण

/* this must be called inside a transaction */
व्योम reiserfs_block_ग_लिखोs(काष्ठा reiserfs_transaction_handle *th)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(th->t_super);
	BUG_ON(!th->t_trans_id);
	journal->j_must_रुको = 1;
	set_bit(J_WRITERS_BLOCKED, &journal->j_state);
	वापस;
पूर्ण

/* this must be called without a transaction started */
व्योम reiserfs_allow_ग_लिखोs(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	clear_bit(J_WRITERS_BLOCKED, &journal->j_state);
	wake_up(&journal->j_join_रुको);
पूर्ण

/* this must be called without a transaction started */
व्योम reiserfs_रुको_on_ग_लिखो_block(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	रुको_event(journal->j_join_रुको,
		   !test_bit(J_WRITERS_BLOCKED, &journal->j_state));
पूर्ण

अटल व्योम queue_log_ग_लिखोr(काष्ठा super_block *s)
अणु
	रुको_queue_entry_t रुको;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	set_bit(J_WRITERS_QUEUED, &journal->j_state);

	/*
	 * we करोn't want to use रुको_event here because
	 * we only want to रुको once.
	 */
	init_रुकोqueue_entry(&रुको, current);
	add_रुको_queue(&journal->j_join_रुको, &रुको);
	set_current_state(TASK_UNINTERRUPTIBLE);
	अगर (test_bit(J_WRITERS_QUEUED, &journal->j_state)) अणु
		पूर्णांक depth = reiserfs_ग_लिखो_unlock_nested(s);
		schedule();
		reiserfs_ग_लिखो_lock_nested(s, depth);
	पूर्ण
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&journal->j_join_रुको, &रुको);
पूर्ण

अटल व्योम wake_queued_ग_लिखोrs(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	अगर (test_and_clear_bit(J_WRITERS_QUEUED, &journal->j_state))
		wake_up(&journal->j_join_रुको);
पूर्ण

अटल व्योम let_transaction_grow(काष्ठा super_block *sb, अचिन्हित पूर्णांक trans_id)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	अचिन्हित दीर्घ bcount = journal->j_bcount;
	जबतक (1) अणु
		पूर्णांक depth;

		depth = reiserfs_ग_लिखो_unlock_nested(sb);
		schedule_समयout_unपूर्णांकerruptible(1);
		reiserfs_ग_लिखो_lock_nested(sb, depth);

		journal->j_current_jl->j_state |= LIST_COMMIT_PENDING;
		जबतक ((atomic_पढ़ो(&journal->j_wcount) > 0 ||
			atomic_पढ़ो(&journal->j_jlock)) &&
		       journal->j_trans_id == trans_id) अणु
			queue_log_ग_लिखोr(sb);
		पूर्ण
		अगर (journal->j_trans_id != trans_id)
			अवरोध;
		अगर (bcount == journal->j_bcount)
			अवरोध;
		bcount = journal->j_bcount;
	पूर्ण
पूर्ण

/*
 * join == true अगर you must join an existing transaction.
 * join == false अगर you can deal with रुकोing क्रम others to finish
 *
 * this will block until the transaction is joinable.  send the number of
 * blocks you expect to use in nblocks.
*/
अटल पूर्णांक करो_journal_begin_r(काष्ठा reiserfs_transaction_handle *th,
			      काष्ठा super_block *sb, अचिन्हित दीर्घ nblocks,
			      पूर्णांक join)
अणु
	समय64_t now = kसमय_get_seconds();
	अचिन्हित पूर्णांक old_trans_id;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_transaction_handle myth;
	पूर्णांक sched_count = 0;
	पूर्णांक retval;
	पूर्णांक depth;

	reiserfs_check_lock_depth(sb, "journal_begin");
	BUG_ON(nblocks > journal->j_trans_max);

	PROC_INFO_INC(sb, journal.journal_being);
	/* set here क्रम journal_join */
	th->t_refcount = 1;
	th->t_super = sb;

relock:
	lock_journal(sb);
	अगर (join != JBEGIN_ABORT && reiserfs_is_journal_पातed(journal)) अणु
		unlock_journal(sb);
		retval = journal->j_त्रुटि_सं;
		जाओ out_fail;
	पूर्ण
	journal->j_bcount++;

	अगर (test_bit(J_WRITERS_BLOCKED, &journal->j_state)) अणु
		unlock_journal(sb);
		depth = reiserfs_ग_लिखो_unlock_nested(sb);
		reiserfs_रुको_on_ग_लिखो_block(sb);
		reiserfs_ग_लिखो_lock_nested(sb, depth);
		PROC_INFO_INC(sb, journal.journal_relock_ग_लिखोrs);
		जाओ relock;
	पूर्ण
	now = kसमय_get_seconds();

	/*
	 * अगर there is no room in the journal OR
	 * अगर this transaction is too old, and we weren't called joinable,
	 * रुको क्रम it to finish beक्रमe beginning we करोn't sleep अगर there
	 * aren't other ग_लिखोrs
	 */

	अगर ((!join && journal->j_must_रुको > 0) ||
	    (!join
	     && (journal->j_len_alloc + nblocks + 2) >= journal->j_max_batch)
	    || (!join && atomic_पढ़ो(&journal->j_wcount) > 0
		&& journal->j_trans_start_समय > 0
		&& (now - journal->j_trans_start_समय) >
		journal->j_max_trans_age) || (!join
					      && atomic_पढ़ो(&journal->j_jlock))
	    || (!join && journal->j_cnode_मुक्त < (journal->j_trans_max * 3))) अणु

		old_trans_id = journal->j_trans_id;
		/* allow others to finish this transaction */
		unlock_journal(sb);

		अगर (!join && (journal->j_len_alloc + nblocks + 2) >=
		    journal->j_max_batch &&
		    ((journal->j_len + nblocks + 2) * 100) <
		    (journal->j_len_alloc * 75)) अणु
			अगर (atomic_पढ़ो(&journal->j_wcount) > 10) अणु
				sched_count++;
				queue_log_ग_लिखोr(sb);
				जाओ relock;
			पूर्ण
		पूर्ण
		/*
		 * करोn't mess with joining the transaction अगर all we
		 * have to करो is रुको क्रम someone अन्यथा to करो a commit
		 */
		अगर (atomic_पढ़ो(&journal->j_jlock)) अणु
			जबतक (journal->j_trans_id == old_trans_id &&
			       atomic_पढ़ो(&journal->j_jlock)) अणु
				queue_log_ग_लिखोr(sb);
			पूर्ण
			जाओ relock;
		पूर्ण
		retval = journal_join(&myth, sb);
		अगर (retval)
			जाओ out_fail;

		/* someone might have ended the transaction जबतक we joined */
		अगर (old_trans_id != journal->j_trans_id) अणु
			retval = करो_journal_end(&myth, 0);
		पूर्ण अन्यथा अणु
			retval = करो_journal_end(&myth, COMMIT_NOW);
		पूर्ण

		अगर (retval)
			जाओ out_fail;

		PROC_INFO_INC(sb, journal.journal_relock_wcount);
		जाओ relock;
	पूर्ण
	/* we are the first ग_लिखोr, set trans_id */
	अगर (journal->j_trans_start_समय == 0) अणु
		journal->j_trans_start_समय = kसमय_get_seconds();
	पूर्ण
	atomic_inc(&journal->j_wcount);
	journal->j_len_alloc += nblocks;
	th->t_blocks_logged = 0;
	th->t_blocks_allocated = nblocks;
	th->t_trans_id = journal->j_trans_id;
	unlock_journal(sb);
	INIT_LIST_HEAD(&th->t_list);
	वापस 0;

out_fail:
	स_रखो(th, 0, माप(*th));
	/*
	 * Re-set th->t_super, so we can properly keep track of how many
	 * persistent transactions there are. We need to करो this so अगर this
	 * call is part of a failed restart_transaction, we can मुक्त it later
	 */
	th->t_super = sb;
	वापस retval;
पूर्ण

काष्ठा reiserfs_transaction_handle *reiserfs_persistent_transaction(काष्ठा
								    super_block
								    *s,
								    पूर्णांक nblocks)
अणु
	पूर्णांक ret;
	काष्ठा reiserfs_transaction_handle *th;

	/*
	 * अगर we're nesting पूर्णांकo an existing transaction.  It will be
	 * persistent on its own
	 */
	अगर (reiserfs_transaction_running(s)) अणु
		th = current->journal_info;
		th->t_refcount++;
		BUG_ON(th->t_refcount < 2);

		वापस th;
	पूर्ण
	th = kदो_स्मृति(माप(काष्ठा reiserfs_transaction_handle), GFP_NOFS);
	अगर (!th)
		वापस शून्य;
	ret = journal_begin(th, s, nblocks);
	अगर (ret) अणु
		kमुक्त(th);
		वापस शून्य;
	पूर्ण

	SB_JOURNAL(s)->j_persistent_trans++;
	वापस th;
पूर्ण

पूर्णांक reiserfs_end_persistent_transaction(काष्ठा reiserfs_transaction_handle *th)
अणु
	काष्ठा super_block *s = th->t_super;
	पूर्णांक ret = 0;
	अगर (th->t_trans_id)
		ret = journal_end(th);
	अन्यथा
		ret = -EIO;
	अगर (th->t_refcount == 0) अणु
		SB_JOURNAL(s)->j_persistent_trans--;
		kमुक्त(th);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक journal_join(काष्ठा reiserfs_transaction_handle *th,
			काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_transaction_handle *cur_th = current->journal_info;

	/*
	 * this keeps करो_journal_end from शून्यing out the
	 * current->journal_info poपूर्णांकer
	 */
	th->t_handle_save = cur_th;
	BUG_ON(cur_th && cur_th->t_refcount > 1);
	वापस करो_journal_begin_r(th, sb, 1, JBEGIN_JOIN);
पूर्ण

पूर्णांक journal_join_पात(काष्ठा reiserfs_transaction_handle *th,
		       काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_transaction_handle *cur_th = current->journal_info;

	/*
	 * this keeps करो_journal_end from शून्यing out the
	 * current->journal_info poपूर्णांकer
	 */
	th->t_handle_save = cur_th;
	BUG_ON(cur_th && cur_th->t_refcount > 1);
	वापस करो_journal_begin_r(th, sb, 1, JBEGIN_ABORT);
पूर्ण

पूर्णांक journal_begin(काष्ठा reiserfs_transaction_handle *th,
		  काष्ठा super_block *sb, अचिन्हित दीर्घ nblocks)
अणु
	काष्ठा reiserfs_transaction_handle *cur_th = current->journal_info;
	पूर्णांक ret;

	th->t_handle_save = शून्य;
	अगर (cur_th) अणु
		/* we are nesting पूर्णांकo the current transaction */
		अगर (cur_th->t_super == sb) अणु
			BUG_ON(!cur_th->t_refcount);
			cur_th->t_refcount++;
			स_नकल(th, cur_th, माप(*th));
			अगर (th->t_refcount <= 1)
				reiserfs_warning(sb, "reiserfs-2005",
						 "BAD: refcount <= 1, but "
						 "journal_info != 0");
			वापस 0;
		पूर्ण अन्यथा अणु
			/*
			 * we've ended up with a handle from a dअगरferent
			 * fileप्रणाली.  save it and restore on journal_end.
			 * This should never really happen...
			 */
			reiserfs_warning(sb, "clm-2100",
					 "nesting info a different FS");
			th->t_handle_save = current->journal_info;
			current->journal_info = th;
		पूर्ण
	पूर्ण अन्यथा अणु
		current->journal_info = th;
	पूर्ण
	ret = करो_journal_begin_r(th, sb, nblocks, JBEGIN_REG);
	BUG_ON(current->journal_info != th);

	/*
	 * I guess this boils करोwn to being the reciprocal of clm-2100 above.
	 * If करो_journal_begin_r fails, we need to put it back, since
	 * journal_end won't be called to करो it. */
	अगर (ret)
		current->journal_info = th->t_handle_save;
	अन्यथा
		BUG_ON(!th->t_refcount);

	वापस ret;
पूर्ण

/*
 * माला_दो bh पूर्णांकo the current transaction.  If it was alपढ़ोy there, reorders
 * हटाओs the old poपूर्णांकers from the hash, and माला_दो new ones in (to make
 * sure replay happen in the right order).
 *
 * अगर it was dirty, cleans and files onto the clean list.  I can't let it
 * be dirty again until the transaction is committed.
 *
 * अगर j_len, is bigger than j_len_alloc, it pushes j_len_alloc to 10 + j_len.
 */
पूर्णांक journal_mark_dirty(काष्ठा reiserfs_transaction_handle *th,
		       काष्ठा buffer_head *bh)
अणु
	काष्ठा super_block *sb = th->t_super;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_journal_cnode *cn = शून्य;
	पूर्णांक count_alपढ़ोy_incd = 0;
	पूर्णांक prepared = 0;
	BUG_ON(!th->t_trans_id);

	PROC_INFO_INC(sb, journal.mark_dirty);
	अगर (th->t_trans_id != journal->j_trans_id) अणु
		reiserfs_panic(th->t_super, "journal-1577",
			       "handle trans id %ld != current trans id %ld",
			       th->t_trans_id, journal->j_trans_id);
	पूर्ण

	prepared = test_clear_buffer_journal_prepared(bh);
	clear_buffer_journal_restore_dirty(bh);
	/* alपढ़ोy in this transaction, we are करोne */
	अगर (buffer_journaled(bh)) अणु
		PROC_INFO_INC(sb, journal.mark_dirty_alपढ़ोy);
		वापस 0;
	पूर्ण

	/*
	 * this must be turned पूर्णांकo a panic instead of a warning.  We can't
	 * allow a dirty or journal_dirty or locked buffer to be logged, as
	 * some changes could get to disk too early.  NOT GOOD.
	 */
	अगर (!prepared || buffer_dirty(bh)) अणु
		reiserfs_warning(sb, "journal-1777",
				 "buffer %llu bad state "
				 "%cPREPARED %cLOCKED %cDIRTY %cJDIRTY_WAIT",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 prepared ? ' ' : '!',
				 buffer_locked(bh) ? ' ' : '!',
				 buffer_dirty(bh) ? ' ' : '!',
				 buffer_journal_dirty(bh) ? ' ' : '!');
	पूर्ण

	अगर (atomic_पढ़ो(&journal->j_wcount) <= 0) अणु
		reiserfs_warning(sb, "journal-1409",
				 "returning because j_wcount was %d",
				 atomic_पढ़ो(&journal->j_wcount));
		वापस 1;
	पूर्ण
	/*
	 * this error means I've screwed up, and we've overflowed
	 * the transaction.  Nothing can be करोne here, except make the
	 * FS पढ़ोonly or panic.
	 */
	अगर (journal->j_len >= journal->j_trans_max) अणु
		reiserfs_panic(th->t_super, "journal-1413",
			       "j_len (%lu) is too big",
			       journal->j_len);
	पूर्ण

	अगर (buffer_journal_dirty(bh)) अणु
		count_alपढ़ोy_incd = 1;
		PROC_INFO_INC(sb, journal.mark_dirty_notjournal);
		clear_buffer_journal_dirty(bh);
	पूर्ण

	अगर (journal->j_len > journal->j_len_alloc) अणु
		journal->j_len_alloc = journal->j_len + JOURNAL_PER_BALANCE_CNT;
	पूर्ण

	set_buffer_journaled(bh);

	/* now put this guy on the end */
	अगर (!cn) अणु
		cn = get_cnode(sb);
		अगर (!cn) अणु
			reiserfs_panic(sb, "journal-4", "get_cnode failed!");
		पूर्ण

		अगर (th->t_blocks_logged == th->t_blocks_allocated) अणु
			th->t_blocks_allocated += JOURNAL_PER_BALANCE_CNT;
			journal->j_len_alloc += JOURNAL_PER_BALANCE_CNT;
		पूर्ण
		th->t_blocks_logged++;
		journal->j_len++;

		cn->bh = bh;
		cn->blocknr = bh->b_blocknr;
		cn->sb = sb;
		cn->jlist = शून्य;
		insert_journal_hash(journal->j_hash_table, cn);
		अगर (!count_alपढ़ोy_incd) अणु
			get_bh(bh);
		पूर्ण
	पूर्ण
	cn->next = शून्य;
	cn->prev = journal->j_last;
	cn->bh = bh;
	अगर (journal->j_last) अणु
		journal->j_last->next = cn;
		journal->j_last = cn;
	पूर्ण अन्यथा अणु
		journal->j_first = cn;
		journal->j_last = cn;
	पूर्ण
	reiserfs_schedule_old_flush(sb);
	वापस 0;
पूर्ण

पूर्णांक journal_end(काष्ठा reiserfs_transaction_handle *th)
अणु
	काष्ठा super_block *sb = th->t_super;
	अगर (!current->journal_info && th->t_refcount > 1)
		reiserfs_warning(sb, "REISER-NESTING",
				 "th NULL, refcount %d", th->t_refcount);

	अगर (!th->t_trans_id) अणु
		WARN_ON(1);
		वापस -EIO;
	पूर्ण

	th->t_refcount--;
	अगर (th->t_refcount > 0) अणु
		काष्ठा reiserfs_transaction_handle *cur_th =
		    current->journal_info;

		/*
		 * we aren't allowed to बंद a nested transaction on a
		 * dअगरferent fileप्रणाली from the one in the task काष्ठा
		 */
		BUG_ON(cur_th->t_super != th->t_super);

		अगर (th != cur_th) अणु
			स_नकल(current->journal_info, th, माप(*th));
			th->t_trans_id = 0;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस करो_journal_end(th, 0);
	पूर्ण
पूर्ण

/*
 * हटाओs from the current transaction, relsing and descrementing any counters.
 * also files the हटाओd buffer directly onto the clean list
 *
 * called by journal_mark_मुक्तd when a block has been deleted
 *
 * वापसs 1 अगर it cleaned and rअन्यथाd the buffer. 0 otherwise
 */
अटल पूर्णांक हटाओ_from_transaction(काष्ठा super_block *sb,
				   b_blocknr_t blocknr, पूर्णांक alपढ़ोy_cleaned)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा reiserfs_journal_cnode *cn;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	पूर्णांक ret = 0;

	cn = get_journal_hash_dev(sb, journal->j_hash_table, blocknr);
	अगर (!cn || !cn->bh) अणु
		वापस ret;
	पूर्ण
	bh = cn->bh;
	अगर (cn->prev) अणु
		cn->prev->next = cn->next;
	पूर्ण
	अगर (cn->next) अणु
		cn->next->prev = cn->prev;
	पूर्ण
	अगर (cn == journal->j_first) अणु
		journal->j_first = cn->next;
	पूर्ण
	अगर (cn == journal->j_last) अणु
		journal->j_last = cn->prev;
	पूर्ण
	हटाओ_journal_hash(sb, journal->j_hash_table, शून्य,
			    bh->b_blocknr, 0);
	clear_buffer_journaled(bh);	/* करोn't log this one */

	अगर (!alपढ़ोy_cleaned) अणु
		clear_buffer_journal_dirty(bh);
		clear_buffer_dirty(bh);
		clear_buffer_journal_test(bh);
		put_bh(bh);
		अगर (atomic_पढ़ो(&bh->b_count) < 0) अणु
			reiserfs_warning(sb, "journal-1752",
					 "b_count < 0");
		पूर्ण
		ret = 1;
	पूर्ण
	journal->j_len--;
	journal->j_len_alloc--;
	मुक्त_cnode(sb, cn);
	वापस ret;
पूर्ण

/*
 * क्रम any cnode in a journal list, it can only be dirtied of all the
 * transactions that include it are committed to disk.
 * this checks through each transaction, and वापसs 1 अगर you are allowed
 * to dirty, and 0 अगर you aren't
 *
 * it is called by dirty_journal_list, which is called after
 * flush_commit_list has gotten all the log blocks क्रम a given
 * transaction on disk
 *
 */
अटल पूर्णांक can_dirty(काष्ठा reiserfs_journal_cnode *cn)
अणु
	काष्ठा super_block *sb = cn->sb;
	b_blocknr_t blocknr = cn->blocknr;
	काष्ठा reiserfs_journal_cnode *cur = cn->hprev;
	पूर्णांक can_dirty = 1;

	/*
	 * first test hprev.  These are all newer than cn, so any node here
	 * with the same block number and dev means this node can't be sent
	 * to disk right now.
	 */
	जबतक (cur && can_dirty) अणु
		अगर (cur->jlist && cur->bh && cur->blocknr && cur->sb == sb &&
		    cur->blocknr == blocknr) अणु
			can_dirty = 0;
		पूर्ण
		cur = cur->hprev;
	पूर्ण
	/*
	 * then test hnext.  These are all older than cn.  As दीर्घ as they
	 * are committed to the log, it is safe to ग_लिखो cn to disk
	 */
	cur = cn->hnext;
	जबतक (cur && can_dirty) अणु
		अगर (cur->jlist && cur->jlist->j_len > 0 &&
		    atomic_पढ़ो(&cur->jlist->j_commit_left) > 0 && cur->bh &&
		    cur->blocknr && cur->sb == sb && cur->blocknr == blocknr) अणु
			can_dirty = 0;
		पूर्ण
		cur = cur->hnext;
	पूर्ण
	वापस can_dirty;
पूर्ण

/*
 * syncs the commit blocks, but करोes not क्रमce the real buffers to disk
 * will रुको until the current transaction is करोne/committed beक्रमe वापसing
 */
पूर्णांक journal_end_sync(काष्ठा reiserfs_transaction_handle *th)
अणु
	काष्ठा super_block *sb = th->t_super;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);

	BUG_ON(!th->t_trans_id);
	/* you can sync जबतक nested, very, very bad */
	BUG_ON(th->t_refcount > 1);
	अगर (journal->j_len == 0) अणु
		reiserfs_prepare_क्रम_journal(sb, SB_BUFFER_WITH_SB(sb),
					     1);
		journal_mark_dirty(th, SB_BUFFER_WITH_SB(sb));
	पूर्ण
	वापस करो_journal_end(th, COMMIT_NOW | WAIT);
पूर्ण

/* ग_लिखोback the pending async commits to disk */
अटल व्योम flush_async_commits(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा reiserfs_journal *journal =
		container_of(work, काष्ठा reiserfs_journal, j_work.work);
	काष्ठा super_block *sb = journal->j_work_sb;
	काष्ठा reiserfs_journal_list *jl;
	काष्ठा list_head *entry;

	reiserfs_ग_लिखो_lock(sb);
	अगर (!list_empty(&journal->j_journal_list)) अणु
		/* last entry is the youngest, commit it and you get everything */
		entry = journal->j_journal_list.prev;
		jl = JOURNAL_LIST_ENTRY(entry);
		flush_commit_list(sb, jl, 1);
	पूर्ण
	reiserfs_ग_लिखो_unlock(sb);
पूर्ण

/*
 * flushes any old transactions to disk
 * ends the current transaction अगर it is too old
 */
व्योम reiserfs_flush_old_commits(काष्ठा super_block *sb)
अणु
	समय64_t now;
	काष्ठा reiserfs_transaction_handle th;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);

	now = kसमय_get_seconds();
	/*
	 * safety check so we करोn't flush जबतक we are replaying the log during
	 * mount
	 */
	अगर (list_empty(&journal->j_journal_list))
		वापस;

	/*
	 * check the current transaction.  If there are no ग_लिखोrs, and it is
	 * too old, finish it, and क्रमce the commit blocks to disk
	 */
	अगर (atomic_पढ़ो(&journal->j_wcount) <= 0 &&
	    journal->j_trans_start_समय > 0 &&
	    journal->j_len > 0 &&
	    (now - journal->j_trans_start_समय) > journal->j_max_trans_age) अणु
		अगर (!journal_join(&th, sb)) अणु
			reiserfs_prepare_क्रम_journal(sb,
						     SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&th, SB_BUFFER_WITH_SB(sb));

			/*
			 * we're only being called from kreiserfsd, it makes
			 * no sense to करो an async commit so that kreiserfsd
			 * can करो it later
			 */
			करो_journal_end(&th, COMMIT_NOW | WAIT);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * वापसs 0 अगर करो_journal_end should वापस right away, वापसs 1 अगर
 * करो_journal_end should finish the commit
 *
 * अगर the current transaction is too old, but still has ग_लिखोrs, this will
 * रुको on j_join_रुको until all the ग_लिखोrs are करोne.  By the समय it
 * wakes up, the transaction it was called has alपढ़ोy ended, so it just
 * flushes the commit list and वापसs 0.
 *
 * Won't batch when flush or commit_now is set.  Also won't batch when
 * others are रुकोing on j_join_रुको.
 *
 * Note, we can't allow the journal_end to proceed जबतक there are still
 * ग_लिखोrs in the log.
 */
अटल पूर्णांक check_journal_end(काष्ठा reiserfs_transaction_handle *th, पूर्णांक flags)
अणु

	समय64_t now;
	पूर्णांक flush = flags & FLUSH_ALL;
	पूर्णांक commit_now = flags & COMMIT_NOW;
	पूर्णांक रुको_on_commit = flags & WAIT;
	काष्ठा reiserfs_journal_list *jl;
	काष्ठा super_block *sb = th->t_super;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);

	BUG_ON(!th->t_trans_id);

	अगर (th->t_trans_id != journal->j_trans_id) अणु
		reiserfs_panic(th->t_super, "journal-1577",
			       "handle trans id %ld != current trans id %ld",
			       th->t_trans_id, journal->j_trans_id);
	पूर्ण

	journal->j_len_alloc -= (th->t_blocks_allocated - th->t_blocks_logged);
	/* <= 0 is allowed.  unmounting might not call begin */
	अगर (atomic_पढ़ो(&journal->j_wcount) > 0)
		atomic_dec(&journal->j_wcount);

	/*
	 * BUG, deal with हाल where j_len is 0, but people previously
	 * मुक्तd blocks need to be released will be dealt with by next
	 * transaction that actually ग_लिखोs something, but should be taken
	 * care of in this trans
	 */
	BUG_ON(journal->j_len == 0);

	/*
	 * अगर wcount > 0, and we are called to with flush or commit_now,
	 * we रुको on j_join_रुको.  We will wake up when the last ग_लिखोr has
	 * finished the transaction, and started it on its way to the disk.
	 * Then, we flush the commit or journal list, and just वापस 0
	 * because the rest of journal end was alपढ़ोy करोne क्रम this
	 * transaction.
	 */
	अगर (atomic_पढ़ो(&journal->j_wcount) > 0) अणु
		अगर (flush || commit_now) अणु
			अचिन्हित trans_id;

			jl = journal->j_current_jl;
			trans_id = jl->j_trans_id;
			अगर (रुको_on_commit)
				jl->j_state |= LIST_COMMIT_PENDING;
			atomic_set(&journal->j_jlock, 1);
			अगर (flush) अणु
				journal->j_next_full_flush = 1;
			पूर्ण
			unlock_journal(sb);

			/*
			 * sleep जबतक the current transaction is
			 * still j_jlocked
			 */
			जबतक (journal->j_trans_id == trans_id) अणु
				अगर (atomic_पढ़ो(&journal->j_jlock)) अणु
					queue_log_ग_लिखोr(sb);
				पूर्ण अन्यथा अणु
					lock_journal(sb);
					अगर (journal->j_trans_id == trans_id) अणु
						atomic_set(&journal->j_jlock,
							   1);
					पूर्ण
					unlock_journal(sb);
				पूर्ण
			पूर्ण
			BUG_ON(journal->j_trans_id == trans_id);

			अगर (commit_now
			    && journal_list_still_alive(sb, trans_id)
			    && रुको_on_commit) अणु
				flush_commit_list(sb, jl, 1);
			पूर्ण
			वापस 0;
		पूर्ण
		unlock_journal(sb);
		वापस 0;
	पूर्ण

	/* deal with old transactions where we are the last ग_लिखोrs */
	now = kसमय_get_seconds();
	अगर ((now - journal->j_trans_start_समय) > journal->j_max_trans_age) अणु
		commit_now = 1;
		journal->j_next_async_flush = 1;
	पूर्ण
	/* करोn't batch when someone is रुकोing on j_join_रुको */
	/* करोn't batch when syncing the commit or flushing the whole trans */
	अगर (!(journal->j_must_रुको > 0) && !(atomic_पढ़ो(&journal->j_jlock))
	    && !flush && !commit_now && (journal->j_len < journal->j_max_batch)
	    && journal->j_len_alloc < journal->j_max_batch
	    && journal->j_cnode_मुक्त > (journal->j_trans_max * 3)) अणु
		journal->j_bcount++;
		unlock_journal(sb);
		वापस 0;
	पूर्ण

	अगर (journal->j_start > SB_ONDISK_JOURNAL_SIZE(sb)) अणु
		reiserfs_panic(sb, "journal-003",
			       "j_start (%ld) is too high",
			       journal->j_start);
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Does all the work that makes deleting blocks safe.
 * when deleting a block mark BH_JNew, just हटाओ it from the current
 * transaction, clean it's buffer_head and move on.
 *
 * otherwise:
 * set a bit क्रम the block in the journal biपंचांगap.  That will prevent it from
 * being allocated क्रम unक्रमmatted nodes beक्रमe this transaction has finished.
 *
 * mark any cnodes क्रम this block as BLOCK_FREED, and clear their bh poपूर्णांकers.
 * That will prevent any old transactions with this block from trying to flush
 * to the real location.  Since we aren't removing the cnode from the
 * journal_list_hash, *the block can't be पुनः_स्मृतिated yet.
 *
 * Then हटाओ it from the current transaction, decrementing any counters and
 * filing it on the clean list.
 */
पूर्णांक journal_mark_मुक्तd(काष्ठा reiserfs_transaction_handle *th,
		       काष्ठा super_block *sb, b_blocknr_t blocknr)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_journal_cnode *cn = शून्य;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा reiserfs_list_biपंचांगap *jb = शून्य;
	पूर्णांक cleaned = 0;
	BUG_ON(!th->t_trans_id);

	cn = get_journal_hash_dev(sb, journal->j_hash_table, blocknr);
	अगर (cn && cn->bh) अणु
		bh = cn->bh;
		get_bh(bh);
	पूर्ण
	/* अगर it is journal new, we just हटाओ it from this transaction */
	अगर (bh && buffer_journal_new(bh)) अणु
		clear_buffer_journal_new(bh);
		clear_prepared_bits(bh);
		reiserfs_clean_and_file_buffer(bh);
		cleaned = हटाओ_from_transaction(sb, blocknr, cleaned);
	पूर्ण अन्यथा अणु
		/*
		 * set the bit क्रम this block in the journal biपंचांगap
		 * क्रम this transaction
		 */
		jb = journal->j_current_jl->j_list_biपंचांगap;
		अगर (!jb) अणु
			reiserfs_panic(sb, "journal-1702",
				       "journal_list_bitmap is NULL");
		पूर्ण
		set_bit_in_list_biपंचांगap(sb, blocknr, jb);

		/* Note, the entire जबतक loop is not allowed to schedule.  */

		अगर (bh) अणु
			clear_prepared_bits(bh);
			reiserfs_clean_and_file_buffer(bh);
		पूर्ण
		cleaned = हटाओ_from_transaction(sb, blocknr, cleaned);

		/*
		 * find all older transactions with this block,
		 * make sure they करोn't try to ग_लिखो it out
		 */
		cn = get_journal_hash_dev(sb, journal->j_list_hash_table,
					  blocknr);
		जबतक (cn) अणु
			अगर (sb == cn->sb && blocknr == cn->blocknr) अणु
				set_bit(BLOCK_FREED, &cn->state);
				अगर (cn->bh) अणु
					/*
					 * हटाओ_from_transaction will brअन्यथा
					 * the buffer अगर it was in the current
					 * trans
					 */
					अगर (!cleaned) अणु
						clear_buffer_journal_dirty(cn->
									   bh);
						clear_buffer_dirty(cn->bh);
						clear_buffer_journal_test(cn->
									  bh);
						cleaned = 1;
						put_bh(cn->bh);
						अगर (atomic_पढ़ो
						    (&cn->bh->b_count) < 0) अणु
							reiserfs_warning(sb,
								 "journal-2138",
								 "cn->bh->b_count < 0");
						पूर्ण
					पूर्ण
					/*
					 * since we are clearing the bh,
					 * we MUST dec nonzerolen
					 */
					अगर (cn->jlist) अणु
						atomic_dec(&cn->jlist->
							   j_nonzerolen);
					पूर्ण
					cn->bh = शून्य;
				पूर्ण
			पूर्ण
			cn = cn->hnext;
		पूर्ण
	पूर्ण

	अगर (bh)
		release_buffer_page(bh); /* get_hash grअसल the buffer */
	वापस 0;
पूर्ण

व्योम reiserfs_update_inode_transaction(काष्ठा inode *inode)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(inode->i_sb);
	REISERFS_I(inode)->i_jl = journal->j_current_jl;
	REISERFS_I(inode)->i_trans_id = journal->j_trans_id;
पूर्ण

/*
 * वापसs -1 on error, 0 अगर no commits/barriers were करोne and 1
 * अगर a transaction was actually committed and the barrier was करोne
 */
अटल पूर्णांक __commit_trans_jl(काष्ठा inode *inode, अचिन्हित दीर्घ id,
			     काष्ठा reiserfs_journal_list *jl)
अणु
	काष्ठा reiserfs_transaction_handle th;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	पूर्णांक ret = 0;

	/*
	 * is it from the current transaction,
	 * or from an unknown transaction?
	 */
	अगर (id == journal->j_trans_id) अणु
		jl = journal->j_current_jl;
		/*
		 * try to let other ग_लिखोrs come in and
		 * grow this transaction
		 */
		let_transaction_grow(sb, id);
		अगर (journal->j_trans_id != id) अणु
			जाओ flush_commit_only;
		पूर्ण

		ret = journal_begin(&th, sb, 1);
		अगर (ret)
			वापस ret;

		/* someone might have ended this transaction जबतक we joined */
		अगर (journal->j_trans_id != id) अणु
			reiserfs_prepare_क्रम_journal(sb, SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&th, SB_BUFFER_WITH_SB(sb));
			ret = journal_end(&th);
			जाओ flush_commit_only;
		पूर्ण

		ret = journal_end_sync(&th);
		अगर (!ret)
			ret = 1;

	पूर्ण अन्यथा अणु
		/*
		 * this माला_लो tricky, we have to make sure the journal list in
		 * the inode still exists.  We know the list is still around
		 * अगर we've got a larger transaction id than the oldest list
		 */
flush_commit_only:
		अगर (journal_list_still_alive(inode->i_sb, id)) अणु
			/*
			 * we only set ret to 1 when we know क्रम sure
			 * the barrier hasn't been started yet on the commit
			 * block.
			 */
			अगर (atomic_पढ़ो(&jl->j_commit_left) > 1)
				ret = 1;
			flush_commit_list(sb, jl, 1);
			अगर (journal->j_त्रुटि_सं)
				ret = journal->j_त्रुटि_सं;
		पूर्ण
	पूर्ण
	/* otherwise the list is gone, and दीर्घ since committed */
	वापस ret;
पूर्ण

पूर्णांक reiserfs_commit_क्रम_inode(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक id = REISERFS_I(inode)->i_trans_id;
	काष्ठा reiserfs_journal_list *jl = REISERFS_I(inode)->i_jl;

	/*
	 * क्रम the whole inode, assume unset id means it was
	 * changed in the current transaction.  More conservative
	 */
	अगर (!id || !jl) अणु
		reiserfs_update_inode_transaction(inode);
		id = REISERFS_I(inode)->i_trans_id;
		/* jl will be updated in __commit_trans_jl */
	पूर्ण

	वापस __commit_trans_jl(inode, id, jl);
पूर्ण

व्योम reiserfs_restore_prepared_buffer(काष्ठा super_block *sb,
				      काष्ठा buffer_head *bh)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	PROC_INFO_INC(sb, journal.restore_prepared);
	अगर (!bh) अणु
		वापस;
	पूर्ण
	अगर (test_clear_buffer_journal_restore_dirty(bh) &&
	    buffer_journal_dirty(bh)) अणु
		काष्ठा reiserfs_journal_cnode *cn;
		reiserfs_ग_लिखो_lock(sb);
		cn = get_journal_hash_dev(sb,
					  journal->j_list_hash_table,
					  bh->b_blocknr);
		अगर (cn && can_dirty(cn)) अणु
			set_buffer_journal_test(bh);
			mark_buffer_dirty(bh);
		पूर्ण
		reiserfs_ग_लिखो_unlock(sb);
	पूर्ण
	clear_buffer_journal_prepared(bh);
पूर्ण

बाह्य काष्ठा tree_balance *cur_tb;
/*
 * beक्रमe we can change a metadata block, we have to make sure it won't
 * be written to disk जबतक we are altering it.  So, we must:
 * clean it
 * रुको on it.
 */
पूर्णांक reiserfs_prepare_क्रम_journal(काष्ठा super_block *sb,
				 काष्ठा buffer_head *bh, पूर्णांक रुको)
अणु
	PROC_INFO_INC(sb, journal.prepare);

	अगर (!trylock_buffer(bh)) अणु
		अगर (!रुको)
			वापस 0;
		lock_buffer(bh);
	पूर्ण
	set_buffer_journal_prepared(bh);
	अगर (test_clear_buffer_dirty(bh) && buffer_journal_dirty(bh)) अणु
		clear_buffer_journal_test(bh);
		set_buffer_journal_restore_dirty(bh);
	पूर्ण
	unlock_buffer(bh);
	वापस 1;
पूर्ण

/*
 * दीर्घ and ugly.  If flush, will not वापस until all commit
 * blocks and all real buffers in the trans are on disk.
 * If no_async, won't वापस until all commit blocks are on disk.
 *
 * keep पढ़ोing, there are comments as you go aदीर्घ
 *
 * If the journal is पातed, we just clean up. Things like flushing
 * journal lists, etc just won't happen.
 */
अटल पूर्णांक करो_journal_end(काष्ठा reiserfs_transaction_handle *th, पूर्णांक flags)
अणु
	काष्ठा super_block *sb = th->t_super;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	काष्ठा reiserfs_journal_cnode *cn, *next, *jl_cn;
	काष्ठा reiserfs_journal_cnode *last_cn = शून्य;
	काष्ठा reiserfs_journal_desc *desc;
	काष्ठा reiserfs_journal_commit *commit;
	काष्ठा buffer_head *c_bh;	/* commit bh */
	काष्ठा buffer_head *d_bh;	/* desc bh */
	पूर्णांक cur_ग_लिखो_start = 0;	/* start index of current log ग_लिखो */
	पूर्णांक i;
	पूर्णांक flush;
	पूर्णांक रुको_on_commit;
	काष्ठा reiserfs_journal_list *jl, *temp_jl;
	काष्ठा list_head *entry, *safe;
	अचिन्हित दीर्घ jindex;
	अचिन्हित पूर्णांक commit_trans_id;
	पूर्णांक trans_half;
	पूर्णांक depth;

	BUG_ON(th->t_refcount > 1);
	BUG_ON(!th->t_trans_id);
	BUG_ON(!th->t_super);

	/*
	 * protect flush_older_commits from करोing mistakes अगर the
	 * transaction ID counter माला_लो overflowed.
	 */
	अगर (th->t_trans_id == ~0U)
		flags |= FLUSH_ALL | COMMIT_NOW | WAIT;
	flush = flags & FLUSH_ALL;
	रुको_on_commit = flags & WAIT;

	current->journal_info = th->t_handle_save;
	reiserfs_check_lock_depth(sb, "journal end");
	अगर (journal->j_len == 0) अणु
		reiserfs_prepare_क्रम_journal(sb, SB_BUFFER_WITH_SB(sb),
					     1);
		journal_mark_dirty(th, SB_BUFFER_WITH_SB(sb));
	पूर्ण

	lock_journal(sb);
	अगर (journal->j_next_full_flush) अणु
		flags |= FLUSH_ALL;
		flush = 1;
	पूर्ण
	अगर (journal->j_next_async_flush) अणु
		flags |= COMMIT_NOW | WAIT;
		रुको_on_commit = 1;
	पूर्ण

	/*
	 * check_journal_end locks the journal, and unlocks अगर it करोes
	 * not वापस 1 it tells us अगर we should जारी with the
	 * journal_end, or just वापस
	 */
	अगर (!check_journal_end(th, flags)) अणु
		reiserfs_schedule_old_flush(sb);
		wake_queued_ग_लिखोrs(sb);
		reiserfs_async_progress_रुको(sb);
		जाओ out;
	पूर्ण

	/* check_journal_end might set these, check again */
	अगर (journal->j_next_full_flush) अणु
		flush = 1;
	पूर्ण

	/*
	 * j must रुको means we have to flush the log blocks, and the
	 * real blocks क्रम this transaction
	 */
	अगर (journal->j_must_रुको > 0) अणु
		flush = 1;
	पूर्ण
#अगर_घोषित REISERFS_PREALLOCATE
	/*
	 * quota ops might need to nest, setup the journal_info poपूर्णांकer
	 * क्रम them and उठाओ the refcount so that it is > 0.
	 */
	current->journal_info = th;
	th->t_refcount++;

	/* it should not involve new blocks पूर्णांकo the transaction */
	reiserfs_discard_all_pपुनः_स्मृति(th);

	th->t_refcount--;
	current->journal_info = th->t_handle_save;
#पूर्ण_अगर

	/* setup description block */
	d_bh =
	    journal_getblk(sb,
			   SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
			   journal->j_start);
	set_buffer_uptodate(d_bh);
	desc = (काष्ठा reiserfs_journal_desc *)(d_bh)->b_data;
	स_रखो(d_bh->b_data, 0, d_bh->b_size);
	स_नकल(get_journal_desc_magic(d_bh), JOURNAL_DESC_MAGIC, 8);
	set_desc_trans_id(desc, journal->j_trans_id);

	/*
	 * setup commit block.  Don't ग_लिखो (keep it clean too) this one
	 * until after everyone अन्यथा is written
	 */
	c_bh = journal_getblk(sb, SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
			      ((journal->j_start + journal->j_len +
				1) % SB_ONDISK_JOURNAL_SIZE(sb)));
	commit = (काष्ठा reiserfs_journal_commit *)c_bh->b_data;
	स_रखो(c_bh->b_data, 0, c_bh->b_size);
	set_commit_trans_id(commit, journal->j_trans_id);
	set_buffer_uptodate(c_bh);

	/* init this journal list */
	jl = journal->j_current_jl;

	/*
	 * we lock the commit beक्रमe करोing anything because
	 * we want to make sure nobody tries to run flush_commit_list until
	 * the new transaction is fully setup, and we've alपढ़ोy flushed the
	 * ordered bh list
	 */
	reiserfs_mutex_lock_safe(&jl->j_commit_mutex, sb);

	/* save the transaction id in हाल we need to commit it later */
	commit_trans_id = jl->j_trans_id;

	atomic_set(&jl->j_older_commits_करोne, 0);
	jl->j_trans_id = journal->j_trans_id;
	jl->j_बारtamp = journal->j_trans_start_समय;
	jl->j_commit_bh = c_bh;
	jl->j_start = journal->j_start;
	jl->j_len = journal->j_len;
	atomic_set(&jl->j_nonzerolen, journal->j_len);
	atomic_set(&jl->j_commit_left, journal->j_len + 2);
	jl->j_realblock = शून्य;

	/*
	 * The ENTIRE FOR LOOP MUST not cause schedule to occur.
	 * क्रम each real block, add it to the journal list hash,
	 * copy पूर्णांकo real block index array in the commit or desc block
	 */
	trans_half = journal_trans_half(sb->s_blocksize);
	क्रम (i = 0, cn = journal->j_first; cn; cn = cn->next, i++) अणु
		अगर (buffer_journaled(cn->bh)) अणु
			jl_cn = get_cnode(sb);
			अगर (!jl_cn) अणु
				reiserfs_panic(sb, "journal-1676",
					       "get_cnode returned NULL");
			पूर्ण
			अगर (i == 0) अणु
				jl->j_realblock = jl_cn;
			पूर्ण
			jl_cn->prev = last_cn;
			jl_cn->next = शून्य;
			अगर (last_cn) अणु
				last_cn->next = jl_cn;
			पूर्ण
			last_cn = jl_cn;
			/*
			 * make sure the block we are trying to log
			 * is not a block of journal or reserved area
			 */
			अगर (is_block_in_log_or_reserved_area
			    (sb, cn->bh->b_blocknr)) अणु
				reiserfs_panic(sb, "journal-2332",
					       "Trying to log block %lu, "
					       "which is a log block",
					       cn->bh->b_blocknr);
			पूर्ण
			jl_cn->blocknr = cn->bh->b_blocknr;
			jl_cn->state = 0;
			jl_cn->sb = sb;
			jl_cn->bh = cn->bh;
			jl_cn->jlist = jl;
			insert_journal_hash(journal->j_list_hash_table, jl_cn);
			अगर (i < trans_half) अणु
				desc->j_realblock[i] =
				    cpu_to_le32(cn->bh->b_blocknr);
			पूर्ण अन्यथा अणु
				commit->j_realblock[i - trans_half] =
				    cpu_to_le32(cn->bh->b_blocknr);
			पूर्ण
		पूर्ण अन्यथा अणु
			i--;
		पूर्ण
	पूर्ण
	set_desc_trans_len(desc, journal->j_len);
	set_desc_mount_id(desc, journal->j_mount_id);
	set_desc_trans_id(desc, journal->j_trans_id);
	set_commit_trans_len(commit, journal->j_len);

	/*
	 * special check in हाल all buffers in the journal
	 * were marked क्रम not logging
	 */
	BUG_ON(journal->j_len == 0);

	/*
	 * we're about to dirty all the log blocks, mark the description block
	 * dirty now too.  Don't mark the commit block dirty until all the
	 * others are on disk
	 */
	mark_buffer_dirty(d_bh);

	/*
	 * first data block is j_start + 1, so add one to
	 * cur_ग_लिखो_start wherever you use it
	 */
	cur_ग_लिखो_start = journal->j_start;
	cn = journal->j_first;
	jindex = 1;	/* start at one so we करोn't get the desc again */
	जबतक (cn) अणु
		clear_buffer_journal_new(cn->bh);
		/* copy all the real blocks पूर्णांकo log area.  dirty log blocks */
		अगर (buffer_journaled(cn->bh)) अणु
			काष्ठा buffer_head *पंचांगp_bh;
			अक्षर *addr;
			काष्ठा page *page;
			पंचांगp_bh =
			    journal_getblk(sb,
					   SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
					   ((cur_ग_लिखो_start +
					     jindex) %
					    SB_ONDISK_JOURNAL_SIZE(sb)));
			set_buffer_uptodate(पंचांगp_bh);
			page = cn->bh->b_page;
			addr = kmap(page);
			स_नकल(पंचांगp_bh->b_data,
			       addr + offset_in_page(cn->bh->b_data),
			       cn->bh->b_size);
			kunmap(page);
			mark_buffer_dirty(पंचांगp_bh);
			jindex++;
			set_buffer_journal_dirty(cn->bh);
			clear_buffer_journaled(cn->bh);
		पूर्ण अन्यथा अणु
			/*
			 * JDirty cleared someसमय during transaction.
			 * करोn't log this one
			 */
			reiserfs_warning(sb, "journal-2048",
					 "BAD, buffer in journal hash, "
					 "but not JDirty!");
			brअन्यथा(cn->bh);
		पूर्ण
		next = cn->next;
		मुक्त_cnode(sb, cn);
		cn = next;
		reiserfs_cond_resched(sb);
	पूर्ण

	/*
	 * we are करोne with both the c_bh and d_bh, but
	 * c_bh must be written after all other commit blocks,
	 * so we dirty/rअन्यथा c_bh in flush_commit_list, with commit_left <= 1.
	 */

	journal->j_current_jl = alloc_journal_list(sb);

	/* now it is safe to insert this transaction on the मुख्य list */
	list_add_tail(&jl->j_list, &journal->j_journal_list);
	list_add_tail(&jl->j_working_list, &journal->j_working_list);
	journal->j_num_work_lists++;

	/* reset journal values क्रम the next transaction */
	journal->j_start =
	    (journal->j_start + journal->j_len +
	     2) % SB_ONDISK_JOURNAL_SIZE(sb);
	atomic_set(&journal->j_wcount, 0);
	journal->j_bcount = 0;
	journal->j_last = शून्य;
	journal->j_first = शून्य;
	journal->j_len = 0;
	journal->j_trans_start_समय = 0;
	/* check क्रम trans_id overflow */
	अगर (++journal->j_trans_id == 0)
		journal->j_trans_id = 10;
	journal->j_current_jl->j_trans_id = journal->j_trans_id;
	journal->j_must_रुको = 0;
	journal->j_len_alloc = 0;
	journal->j_next_full_flush = 0;
	journal->j_next_async_flush = 0;
	init_journal_hash(sb);

	/*
	 * make sure reiserfs_add_jh sees the new current_jl beक्रमe we
	 * ग_लिखो out the tails
	 */
	smp_mb();

	/*
	 * tail conversion tarमाला_लो have to hit the disk beक्रमe we end the
	 * transaction.  Otherwise a later transaction might repack the tail
	 * beक्रमe this transaction commits, leaving the data block unflushed
	 * and clean, अगर we crash beक्रमe the later transaction commits, the
	 * data block is lost.
	 */
	अगर (!list_empty(&jl->j_tail_bh_list)) अणु
		depth = reiserfs_ग_लिखो_unlock_nested(sb);
		ग_लिखो_ordered_buffers(&journal->j_dirty_buffers_lock,
				      journal, jl, &jl->j_tail_bh_list);
		reiserfs_ग_लिखो_lock_nested(sb, depth);
	पूर्ण
	BUG_ON(!list_empty(&jl->j_tail_bh_list));
	mutex_unlock(&jl->j_commit_mutex);

	/*
	 * honor the flush wishes from the caller, simple commits can
	 * be करोne outside the journal lock, they are करोne below
	 *
	 * अगर we करोn't flush the commit list right now, we put it पूर्णांकo
	 * the work queue so the people रुकोing on the async progress work
	 * queue करोn't रुको क्रम this proc to flush journal lists and such.
	 */
	अगर (flush) अणु
		flush_commit_list(sb, jl, 1);
		flush_journal_list(sb, jl, 1);
	पूर्ण अन्यथा अगर (!(jl->j_state & LIST_COMMIT_PENDING)) अणु
		/*
		 * Aव्योम queueing work when sb is being shut करोwn. Transaction
		 * will be flushed on journal shutकरोwn.
		 */
		अगर (sb->s_flags & SB_ACTIVE)
			queue_delayed_work(REISERFS_SB(sb)->commit_wq,
					   &journal->j_work, HZ / 10);
	पूर्ण

	/*
	 * अगर the next transaction has any chance of wrapping, flush
	 * transactions that might get overwritten.  If any journal lists
	 * are very old flush them as well.
	 */
first_jl:
	list_क्रम_each_safe(entry, safe, &journal->j_journal_list) अणु
		temp_jl = JOURNAL_LIST_ENTRY(entry);
		अगर (journal->j_start <= temp_jl->j_start) अणु
			अगर ((journal->j_start + journal->j_trans_max + 1) >=
			    temp_jl->j_start) अणु
				flush_used_journal_lists(sb, temp_jl);
				जाओ first_jl;
			पूर्ण अन्यथा अगर ((journal->j_start +
				    journal->j_trans_max + 1) <
				   SB_ONDISK_JOURNAL_SIZE(sb)) अणु
				/*
				 * अगर we करोn't cross पूर्णांकo the next
				 * transaction and we करोn't wrap, there is
				 * no way we can overlap any later transactions
				 * अवरोध now
				 */
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर ((journal->j_start +
			    journal->j_trans_max + 1) >
			   SB_ONDISK_JOURNAL_SIZE(sb)) अणु
			अगर (((journal->j_start + journal->j_trans_max + 1) %
			     SB_ONDISK_JOURNAL_SIZE(sb)) >=
			    temp_jl->j_start) अणु
				flush_used_journal_lists(sb, temp_jl);
				जाओ first_jl;
			पूर्ण अन्यथा अणु
				/*
				* we करोn't overlap anything from out start
				* to the end of the log, and our wrapped
				* portion करोesn't overlap anything at
				* the start of the log.  We can अवरोध
				*/
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	journal->j_current_jl->j_list_biपंचांगap =
	    get_list_biपंचांगap(sb, journal->j_current_jl);

	अगर (!(journal->j_current_jl->j_list_biपंचांगap)) अणु
		reiserfs_panic(sb, "journal-1996",
			       "could not get a list bitmap");
	पूर्ण

	atomic_set(&journal->j_jlock, 0);
	unlock_journal(sb);
	/* wake up any body रुकोing to join. */
	clear_bit(J_WRITERS_QUEUED, &journal->j_state);
	wake_up(&journal->j_join_रुको);

	अगर (!flush && रुको_on_commit &&
	    journal_list_still_alive(sb, commit_trans_id)) अणु
		flush_commit_list(sb, jl, 1);
	पूर्ण
out:
	reiserfs_check_lock_depth(sb, "journal end2");

	स_रखो(th, 0, माप(*th));
	/*
	 * Re-set th->t_super, so we can properly keep track of how many
	 * persistent transactions there are. We need to करो this so अगर this
	 * call is part of a failed restart_transaction, we can मुक्त it later
	 */
	th->t_super = sb;

	वापस journal->j_त्रुटि_सं;
पूर्ण

/* Send the file प्रणाली पढ़ो only and refuse new transactions */
व्योम reiserfs_पात_journal(काष्ठा super_block *sb, पूर्णांक त्रुटि_सं)
अणु
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(sb);
	अगर (test_bit(J_ABORTED, &journal->j_state))
		वापस;

	अगर (!journal->j_त्रुटि_सं)
		journal->j_त्रुटि_सं = त्रुटि_सं;

	sb->s_flags |= SB_RDONLY;
	set_bit(J_ABORTED, &journal->j_state);

#अगर_घोषित CONFIG_REISERFS_CHECK
	dump_stack();
#पूर्ण_अगर
पूर्ण
