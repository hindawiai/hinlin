<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित _LINUX_DM_TRANSACTION_MANAGER_H
#घोषणा _LINUX_DM_TRANSACTION_MANAGER_H

#समावेश "dm-block-manager.h"

काष्ठा dm_transaction_manager;
काष्ठा dm_space_map;

/*----------------------------------------------------------------*/

/*
 * This manages the scope of a transaction.  It also enक्रमces immutability
 * of the on-disk data काष्ठाures by limiting access to ग_लिखोable blocks.
 *
 * Clients should not fiddle with the block manager directly.
 */

व्योम dm_पंचांग_destroy(काष्ठा dm_transaction_manager *पंचांग);

/*
 * The non-blocking version of a transaction manager is पूर्णांकended क्रम use in
 * fast path code that needs to करो lookups e.g. a dm mapping function.
 * You create the non-blocking variant from a normal पंचांग.  The पूर्णांकerface is
 * the same, except that most functions will just वापस -EWOULDBLOCK.
 * Methods that वापस व्योम yet may block should not be called on a clone
 * viz. dm_पंचांग_inc, dm_पंचांग_dec.  Call dm_पंचांग_destroy() as you would with a normal
 * पंचांग when you've finished with it.  You may not destroy the original prior
 * to clones.
 */
काष्ठा dm_transaction_manager *dm_पंचांग_create_non_blocking_clone(काष्ठा dm_transaction_manager *real);

/*
 * We use a 2-phase commit here.
 *
 * i) Make all changes क्रम the transaction *except* क्रम the superblock.
 * Then call dm_पंचांग_pre_commit() to flush them to disk.
 *
 * ii) Lock your superblock.  Update.  Then call dm_पंचांग_commit() which will
 * unlock the superblock and flush it.  No other blocks should be updated
 * during this period.  Care should be taken to never unlock a partially
 * updated superblock; perक्रमm any operations that could fail *beक्रमe* you
 * take the superblock lock.
 */
पूर्णांक dm_पंचांग_pre_commit(काष्ठा dm_transaction_manager *पंचांग);
पूर्णांक dm_पंचांग_commit(काष्ठा dm_transaction_manager *पंचांग, काष्ठा dm_block *superblock);

/*
 * These methods are the only way to get hold of a ग_लिखोable block.
 */

/*
 * dm_पंचांग_new_block() is pretty self-explanatory.  Make sure you करो actually
 * ग_लिखो to the whole of @data beक्रमe you unlock, otherwise you could get
 * a data leak.  (The other option is क्रम पंचांग_new_block() to zero new blocks
 * beक्रमe handing them out, which will be redundant in most, अगर not all,
 * हालs).
 * Zeroes the new block and वापसs with ग_लिखो lock held.
 */
पूर्णांक dm_पंचांग_new_block(काष्ठा dm_transaction_manager *पंचांग,
		    काष्ठा dm_block_validator *v,
		    काष्ठा dm_block **result);

/*
 * dm_पंचांग_shaकरोw_block() allocates a new block and copies the data from @orig
 * to it.  It then decrements the reference count on original block.  Use
 * this to update the contents of a block in a data काष्ठाure, करोn't
 * confuse this with a clone - you shouldn't access the orig block after
 * this operation.  Because the पंचांग knows the scope of the transaction it
 * can optimise requests क्रम a shaकरोw of a shaकरोw to a no-op.  Don't क्रमget
 * to unlock when you've finished with the shaकरोw.
 *
 * The @inc_children flag is used to tell the caller whether it needs to
 * adjust reference counts क्रम children.  (Data in the block may refer to
 * other blocks.)
 *
 * Shaकरोwing implicitly drops a reference on @orig so you must not have
 * it locked when you call this.
 */
पूर्णांक dm_पंचांग_shaकरोw_block(काष्ठा dm_transaction_manager *पंचांग, dm_block_t orig,
		       काष्ठा dm_block_validator *v,
		       काष्ठा dm_block **result, पूर्णांक *inc_children);

/*
 * Read access.  You can lock any block you want.  If there's a ग_लिखो lock
 * on it outstanding then it'll block.
 */
पूर्णांक dm_पंचांग_पढ़ो_lock(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b,
		    काष्ठा dm_block_validator *v,
		    काष्ठा dm_block **result);

व्योम dm_पंचांग_unlock(काष्ठा dm_transaction_manager *पंचांग, काष्ठा dm_block *b);

/*
 * Functions क्रम altering the reference count of a block directly.
 */
व्योम dm_पंचांग_inc(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b);

व्योम dm_पंचांग_dec(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b);

पूर्णांक dm_पंचांग_ref(काष्ठा dm_transaction_manager *पंचांग, dm_block_t b,
	      uपूर्णांक32_t *result);

काष्ठा dm_block_manager *dm_पंचांग_get_bm(काष्ठा dm_transaction_manager *पंचांग);

/*
 * If you're using a non-blocking clone the पंचांग will build up a list of
 * requested blocks that weren't in core.  This call will request those
 * blocks to be prefetched.
 */
व्योम dm_पंचांग_issue_prefetches(काष्ठा dm_transaction_manager *पंचांग);

/*
 * A little utility that ties the knot by producing a transaction manager
 * that has a space map managed by the transaction manager...
 *
 * Returns a पंचांग that has an खोलो transaction to ग_लिखो the new disk sm.
 * Caller should store the new sm root and commit.
 *
 * The superblock location is passed so the metadata space map knows it
 * shouldn't be used.
 */
पूर्णांक dm_पंचांग_create_with_sm(काष्ठा dm_block_manager *bm, dm_block_t sb_location,
			 काष्ठा dm_transaction_manager **पंचांग,
			 काष्ठा dm_space_map **sm);

पूर्णांक dm_पंचांग_खोलो_with_sm(काष्ठा dm_block_manager *bm, dm_block_t sb_location,
		       व्योम *sm_root, माप_प्रकार root_len,
		       काष्ठा dm_transaction_manager **पंचांग,
		       काष्ठा dm_space_map **sm);

#पूर्ण_अगर	/* _LINUX_DM_TRANSACTION_MANAGER_H */
