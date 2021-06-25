<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_btree.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/btree.h"
#समावेश "scrub/trace.h"

/* btree scrubbing */

/*
 * Check क्रम btree operation errors.  See the section about handling
 * operational errors in common.c.
 */
अटल bool
__xchk_btree_process_error(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	पूर्णांक			*error,
	__u32			errflag,
	व्योम			*ret_ip)
अणु
	अगर (*error == 0)
		वापस true;

	चयन (*error) अणु
	हाल -EDEADLOCK:
		/* Used to restart an op with deadlock aव्योमance. */
		trace_xchk_deadlock_retry(sc->ip, sc->sm, *error);
		अवरोध;
	हाल -EFSBADCRC:
	हाल -EFSCORRUPTED:
		/* Note the badness but करोn't पात. */
		sc->sm->sm_flags |= errflag;
		*error = 0;
		/* fall through */
	शेष:
		अगर (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE)
			trace_xchk_अगरork_btree_op_error(sc, cur, level,
					*error, ret_ip);
		अन्यथा
			trace_xchk_btree_op_error(sc, cur, level,
					*error, ret_ip);
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

bool
xchk_btree_process_error(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	पूर्णांक			*error)
अणु
	वापस __xchk_btree_process_error(sc, cur, level, error,
			XFS_SCRUB_OFLAG_CORRUPT, __वापस_address);
पूर्ण

bool
xchk_btree_xref_process_error(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	पूर्णांक			*error)
अणु
	वापस __xchk_btree_process_error(sc, cur, level, error,
			XFS_SCRUB_OFLAG_XFAIL, __वापस_address);
पूर्ण

/* Record btree block corruption. */
अटल व्योम
__xchk_btree_set_corrupt(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	__u32			errflag,
	व्योम			*ret_ip)
अणु
	sc->sm->sm_flags |= errflag;

	अगर (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE)
		trace_xchk_अगरork_btree_error(sc, cur, level,
				ret_ip);
	अन्यथा
		trace_xchk_btree_error(sc, cur, level,
				ret_ip);
पूर्ण

व्योम
xchk_btree_set_corrupt(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	__xchk_btree_set_corrupt(sc, cur, level, XFS_SCRUB_OFLAG_CORRUPT,
			__वापस_address);
पूर्ण

व्योम
xchk_btree_xref_set_corrupt(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	__xchk_btree_set_corrupt(sc, cur, level, XFS_SCRUB_OFLAG_XCORRUPT,
			__वापस_address);
पूर्ण

/*
 * Make sure this record is in order and करोesn't stray outside of the parent
 * keys.
 */
STATIC व्योम
xchk_btree_rec(
	काष्ठा xchk_btree	*bs)
अणु
	काष्ठा xfs_btree_cur	*cur = bs->cur;
	जोड़ xfs_btree_rec	*rec;
	जोड़ xfs_btree_key	key;
	जोड़ xfs_btree_key	hkey;
	जोड़ xfs_btree_key	*keyp;
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_btree_block	*keyblock;
	काष्ठा xfs_buf		*bp;

	block = xfs_btree_get_block(cur, 0, &bp);
	rec = xfs_btree_rec_addr(cur, cur->bc_ptrs[0], block);

	trace_xchk_btree_rec(bs->sc, cur, 0);

	/* If this isn't the first record, are they in order? */
	अगर (!bs->firstrec && !cur->bc_ops->recs_inorder(cur, &bs->lastrec, rec))
		xchk_btree_set_corrupt(bs->sc, cur, 0);
	bs->firstrec = false;
	स_नकल(&bs->lastrec, rec, cur->bc_ops->rec_len);

	अगर (cur->bc_nlevels == 1)
		वापस;

	/* Is this at least as large as the parent low key? */
	cur->bc_ops->init_key_from_rec(&key, rec);
	keyblock = xfs_btree_get_block(cur, 1, &bp);
	keyp = xfs_btree_key_addr(cur, cur->bc_ptrs[1], keyblock);
	अगर (cur->bc_ops->dअगरf_two_keys(cur, &key, keyp) < 0)
		xchk_btree_set_corrupt(bs->sc, cur, 1);

	अगर (!(cur->bc_flags & XFS_BTREE_OVERLAPPING))
		वापस;

	/* Is this no larger than the parent high key? */
	cur->bc_ops->init_high_key_from_rec(&hkey, rec);
	keyp = xfs_btree_high_key_addr(cur, cur->bc_ptrs[1], keyblock);
	अगर (cur->bc_ops->dअगरf_two_keys(cur, keyp, &hkey) < 0)
		xchk_btree_set_corrupt(bs->sc, cur, 1);
पूर्ण

/*
 * Make sure this key is in order and करोesn't stray outside of the parent
 * keys.
 */
STATIC व्योम
xchk_btree_key(
	काष्ठा xchk_btree	*bs,
	पूर्णांक			level)
अणु
	काष्ठा xfs_btree_cur	*cur = bs->cur;
	जोड़ xfs_btree_key	*key;
	जोड़ xfs_btree_key	*keyp;
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_btree_block	*keyblock;
	काष्ठा xfs_buf		*bp;

	block = xfs_btree_get_block(cur, level, &bp);
	key = xfs_btree_key_addr(cur, cur->bc_ptrs[level], block);

	trace_xchk_btree_key(bs->sc, cur, level);

	/* If this isn't the first key, are they in order? */
	अगर (!bs->firstkey[level] &&
	    !cur->bc_ops->keys_inorder(cur, &bs->lastkey[level], key))
		xchk_btree_set_corrupt(bs->sc, cur, level);
	bs->firstkey[level] = false;
	स_नकल(&bs->lastkey[level], key, cur->bc_ops->key_len);

	अगर (level + 1 >= cur->bc_nlevels)
		वापस;

	/* Is this at least as large as the parent low key? */
	keyblock = xfs_btree_get_block(cur, level + 1, &bp);
	keyp = xfs_btree_key_addr(cur, cur->bc_ptrs[level + 1], keyblock);
	अगर (cur->bc_ops->dअगरf_two_keys(cur, key, keyp) < 0)
		xchk_btree_set_corrupt(bs->sc, cur, level);

	अगर (!(cur->bc_flags & XFS_BTREE_OVERLAPPING))
		वापस;

	/* Is this no larger than the parent high key? */
	key = xfs_btree_high_key_addr(cur, cur->bc_ptrs[level], block);
	keyp = xfs_btree_high_key_addr(cur, cur->bc_ptrs[level + 1], keyblock);
	अगर (cur->bc_ops->dअगरf_two_keys(cur, keyp, key) < 0)
		xchk_btree_set_corrupt(bs->sc, cur, level);
पूर्ण

/*
 * Check a btree poपूर्णांकer.  Returns true अगर it's ok to use this poपूर्णांकer.
 * Callers करो not need to set the corrupt flag.
 */
अटल bool
xchk_btree_ptr_ok(
	काष्ठा xchk_btree	*bs,
	पूर्णांक			level,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	bool			res;

	/* A btree rooted in an inode has no block poपूर्णांकer to the root. */
	अगर ((bs->cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    level == bs->cur->bc_nlevels)
		वापस true;

	/* Otherwise, check the poपूर्णांकers. */
	अगर (bs->cur->bc_flags & XFS_BTREE_LONG_PTRS)
		res = xfs_btree_check_lptr(bs->cur, be64_to_cpu(ptr->l), level);
	अन्यथा
		res = xfs_btree_check_sptr(bs->cur, be32_to_cpu(ptr->s), level);
	अगर (!res)
		xchk_btree_set_corrupt(bs->sc, bs->cur, level);

	वापस res;
पूर्ण

/* Check that a btree block's sibling matches what we expect it. */
STATIC पूर्णांक
xchk_btree_block_check_sibling(
	काष्ठा xchk_btree	*bs,
	पूर्णांक			level,
	पूर्णांक			direction,
	जोड़ xfs_btree_ptr	*sibling)
अणु
	काष्ठा xfs_btree_cur	*cur = bs->cur;
	काष्ठा xfs_btree_block	*pblock;
	काष्ठा xfs_buf		*pbp;
	काष्ठा xfs_btree_cur	*ncur = शून्य;
	जोड़ xfs_btree_ptr	*pp;
	पूर्णांक			success;
	पूर्णांक			error;

	error = xfs_btree_dup_cursor(cur, &ncur);
	अगर (!xchk_btree_process_error(bs->sc, cur, level + 1, &error) ||
	    !ncur)
		वापस error;

	/*
	 * If the poपूर्णांकer is null, we shouldn't be able to move the upper
	 * level poपूर्णांकer anywhere.
	 */
	अगर (xfs_btree_ptr_is_null(cur, sibling)) अणु
		अगर (direction > 0)
			error = xfs_btree_increment(ncur, level + 1, &success);
		अन्यथा
			error = xfs_btree_decrement(ncur, level + 1, &success);
		अगर (error == 0 && success)
			xchk_btree_set_corrupt(bs->sc, cur, level);
		error = 0;
		जाओ out;
	पूर्ण

	/* Increment upper level poपूर्णांकer. */
	अगर (direction > 0)
		error = xfs_btree_increment(ncur, level + 1, &success);
	अन्यथा
		error = xfs_btree_decrement(ncur, level + 1, &success);
	अगर (!xchk_btree_process_error(bs->sc, cur, level + 1, &error))
		जाओ out;
	अगर (!success) अणु
		xchk_btree_set_corrupt(bs->sc, cur, level + 1);
		जाओ out;
	पूर्ण

	/* Compare upper level poपूर्णांकer to sibling poपूर्णांकer. */
	pblock = xfs_btree_get_block(ncur, level + 1, &pbp);
	pp = xfs_btree_ptr_addr(ncur, ncur->bc_ptrs[level + 1], pblock);
	अगर (!xchk_btree_ptr_ok(bs, level + 1, pp))
		जाओ out;
	अगर (pbp)
		xchk_buffer_recheck(bs->sc, pbp);

	अगर (xfs_btree_dअगरf_two_ptrs(cur, pp, sibling))
		xchk_btree_set_corrupt(bs->sc, cur, level);
out:
	xfs_btree_del_cursor(ncur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/* Check the siblings of a btree block. */
STATIC पूर्णांक
xchk_btree_block_check_siblings(
	काष्ठा xchk_btree	*bs,
	काष्ठा xfs_btree_block	*block)
अणु
	काष्ठा xfs_btree_cur	*cur = bs->cur;
	जोड़ xfs_btree_ptr	leftsib;
	जोड़ xfs_btree_ptr	rightsib;
	पूर्णांक			level;
	पूर्णांक			error = 0;

	xfs_btree_get_sibling(cur, block, &leftsib, XFS_BB_LEFTSIB);
	xfs_btree_get_sibling(cur, block, &rightsib, XFS_BB_RIGHTSIB);
	level = xfs_btree_get_level(block);

	/* Root block should never have siblings. */
	अगर (level == cur->bc_nlevels - 1) अणु
		अगर (!xfs_btree_ptr_is_null(cur, &leftsib) ||
		    !xfs_btree_ptr_is_null(cur, &rightsib))
			xchk_btree_set_corrupt(bs->sc, cur, level);
		जाओ out;
	पूर्ण

	/*
	 * Does the left & right sibling poपूर्णांकers match the adjacent
	 * parent level poपूर्णांकers?
	 * (These function असलorbs error codes क्रम us.)
	 */
	error = xchk_btree_block_check_sibling(bs, level, -1, &leftsib);
	अगर (error)
		वापस error;
	error = xchk_btree_block_check_sibling(bs, level, 1, &rightsib);
	अगर (error)
		वापस error;
out:
	वापस error;
पूर्ण

काष्ठा check_owner अणु
	काष्ठा list_head	list;
	xfs_daddr_t		daddr;
	पूर्णांक			level;
पूर्ण;

/*
 * Make sure this btree block isn't in the free list and that there's
 * an rmap record क्रम it.
 */
STATIC पूर्णांक
xchk_btree_check_block_owner(
	काष्ठा xchk_btree	*bs,
	पूर्णांक			level,
	xfs_daddr_t		daddr)
अणु
	xfs_agnumber_t		agno;
	xfs_agblock_t		agbno;
	xfs_btnum_t		btnum;
	bool			init_sa;
	पूर्णांक			error = 0;

	अगर (!bs->cur)
		वापस 0;

	btnum = bs->cur->bc_btnum;
	agno = xfs_daddr_to_agno(bs->cur->bc_mp, daddr);
	agbno = xfs_daddr_to_agbno(bs->cur->bc_mp, daddr);

	init_sa = bs->cur->bc_flags & XFS_BTREE_LONG_PTRS;
	अगर (init_sa) अणु
		error = xchk_ag_init(bs->sc, agno, &bs->sc->sa);
		अगर (!xchk_btree_xref_process_error(bs->sc, bs->cur,
				level, &error))
			वापस error;
	पूर्ण

	xchk_xref_is_used_space(bs->sc, agbno, 1);
	/*
	 * The bnobt scrubber aliases bs->cur to bs->sc->sa.bno_cur, so we
	 * have to nullअगरy it (to shut करोwn further block owner checks) अगर
	 * self-xref encounters problems.
	 */
	अगर (!bs->sc->sa.bno_cur && btnum == XFS_BTNUM_BNO)
		bs->cur = शून्य;

	xchk_xref_is_owned_by(bs->sc, agbno, 1, bs->oinfo);
	अगर (!bs->sc->sa.rmap_cur && btnum == XFS_BTNUM_RMAP)
		bs->cur = शून्य;

	अगर (init_sa)
		xchk_ag_मुक्त(bs->sc, &bs->sc->sa);

	वापस error;
पूर्ण

/* Check the owner of a btree block. */
STATIC पूर्णांक
xchk_btree_check_owner(
	काष्ठा xchk_btree	*bs,
	पूर्णांक			level,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_btree_cur	*cur = bs->cur;
	काष्ठा check_owner	*co;

	/*
	 * In theory, xfs_btree_get_block should only give us a null buffer
	 * poपूर्णांकer क्रम the root of a root-in-inode btree type, but we need
	 * to check defensively here in हाल the cursor state is also screwed
	 * up.
	 */
	अगर (bp == शून्य) अणु
		अगर (!(cur->bc_flags & XFS_BTREE_ROOT_IN_INODE))
			xchk_btree_set_corrupt(bs->sc, bs->cur, level);
		वापस 0;
	पूर्ण

	/*
	 * We want to cross-reference each btree block with the bnobt
	 * and the rmapbt.  We cannot cross-reference the bnobt or
	 * rmapbt जबतक scanning the bnobt or rmapbt, respectively,
	 * because we cannot alter the cursor and we'd prefer not to
	 * duplicate cursors.  Thereक्रमe, save the buffer daddr क्रम
	 * later scanning.
	 */
	अगर (cur->bc_btnum == XFS_BTNUM_BNO || cur->bc_btnum == XFS_BTNUM_RMAP) अणु
		co = kmem_alloc(माप(काष्ठा check_owner),
				KM_MAYFAIL);
		अगर (!co)
			वापस -ENOMEM;
		co->level = level;
		co->daddr = XFS_BUF_ADDR(bp);
		list_add_tail(&co->list, &bs->to_check);
		वापस 0;
	पूर्ण

	वापस xchk_btree_check_block_owner(bs, level, XFS_BUF_ADDR(bp));
पूर्ण

/* Decide अगर we want to check minrecs of a btree block in the inode root. */
अटल अंतरभूत bool
xchk_btree_check_iroot_minrecs(
	काष्ठा xchk_btree	*bs)
अणु
	/*
	 * xfs_bmap_add_attrविभाजन_btree had an implementation bug wherein it
	 * would miscalculate the space required क्रम the data विभाजन bmbt root
	 * when adding an attr विभाजन, and promote the iroot contents to an
	 * बाह्यal block unnecessarily.  This went unnoticed क्रम many years
	 * until scrub found fileप्रणालीs in this state.  Inode rooted btrees are
	 * not supposed to have immediate child blocks that are small enough
	 * that the contents could fit in the inode root, but we can't fail
	 * existing fileप्रणालीs, so instead we disable the check क्रम data विभाजन
	 * bmap btrees when there's an attr विभाजन.
	 */
	अगर (bs->cur->bc_btnum == XFS_BTNUM_BMAP &&
	    bs->cur->bc_ino.whichविभाजन == XFS_DATA_FORK &&
	    XFS_IFORK_Q(bs->sc->ip))
		वापस false;

	वापस true;
पूर्ण

/*
 * Check that this btree block has at least minrecs records or is one of the
 * special blocks that करोn't require that.
 */
STATIC व्योम
xchk_btree_check_minrecs(
	काष्ठा xchk_btree	*bs,
	पूर्णांक			level,
	काष्ठा xfs_btree_block	*block)
अणु
	काष्ठा xfs_btree_cur	*cur = bs->cur;
	अचिन्हित पूर्णांक		root_level = cur->bc_nlevels - 1;
	अचिन्हित पूर्णांक		numrecs = be16_to_cpu(block->bb_numrecs);

	/* More records than minrecs means the block is ok. */
	अगर (numrecs >= cur->bc_ops->get_minrecs(cur, level))
		वापस;

	/*
	 * For btrees rooted in the inode, it's possible that the root block
	 * contents spilled पूर्णांकo a regular ondisk block because there wasn't
	 * enough space in the inode root.  The number of records in that
	 * child block might be less than the standard minrecs, but that's ok
	 * provided that there's only one direct child of the root.
	 */
	अगर ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    level == cur->bc_nlevels - 2) अणु
		काष्ठा xfs_btree_block	*root_block;
		काष्ठा xfs_buf		*root_bp;
		पूर्णांक			root_maxrecs;

		root_block = xfs_btree_get_block(cur, root_level, &root_bp);
		root_maxrecs = cur->bc_ops->get_dmaxrecs(cur, root_level);
		अगर (xchk_btree_check_iroot_minrecs(bs) &&
		    (be16_to_cpu(root_block->bb_numrecs) != 1 ||
		     numrecs <= root_maxrecs))
			xchk_btree_set_corrupt(bs->sc, cur, level);
		वापस;
	पूर्ण

	/*
	 * Otherwise, only the root level is allowed to have fewer than minrecs
	 * records or keyptrs.
	 */
	अगर (level < root_level)
		xchk_btree_set_corrupt(bs->sc, cur, level);
पूर्ण

/*
 * Grab and scrub a btree block given a btree poपूर्णांकer.  Returns block
 * and buffer poपूर्णांकers (अगर applicable) अगर they're ok to use.
 */
STATIC पूर्णांक
xchk_btree_get_block(
	काष्ठा xchk_btree	*bs,
	पूर्णांक			level,
	जोड़ xfs_btree_ptr	*pp,
	काष्ठा xfs_btree_block	**pblock,
	काष्ठा xfs_buf		**pbp)
अणु
	xfs_failaddr_t		failed_at;
	पूर्णांक			error;

	*pblock = शून्य;
	*pbp = शून्य;

	error = xfs_btree_lookup_get_block(bs->cur, level, pp, pblock);
	अगर (!xchk_btree_process_error(bs->sc, bs->cur, level, &error) ||
	    !*pblock)
		वापस error;

	xfs_btree_get_block(bs->cur, level, pbp);
	अगर (bs->cur->bc_flags & XFS_BTREE_LONG_PTRS)
		failed_at = __xfs_btree_check_lblock(bs->cur, *pblock,
				level, *pbp);
	अन्यथा
		failed_at = __xfs_btree_check_sblock(bs->cur, *pblock,
				 level, *pbp);
	अगर (failed_at) अणु
		xchk_btree_set_corrupt(bs->sc, bs->cur, level);
		वापस 0;
	पूर्ण
	अगर (*pbp)
		xchk_buffer_recheck(bs->sc, *pbp);

	xchk_btree_check_minrecs(bs, level, *pblock);

	/*
	 * Check the block's owner; this function असलorbs error codes
	 * क्रम us.
	 */
	error = xchk_btree_check_owner(bs, level, *pbp);
	अगर (error)
		वापस error;

	/*
	 * Check the block's siblings; this function असलorbs error codes
	 * क्रम us.
	 */
	वापस xchk_btree_block_check_siblings(bs, *pblock);
पूर्ण

/*
 * Check that the low and high keys of this block match the keys stored
 * in the parent block.
 */
STATIC व्योम
xchk_btree_block_keys(
	काष्ठा xchk_btree	*bs,
	पूर्णांक			level,
	काष्ठा xfs_btree_block	*block)
अणु
	जोड़ xfs_btree_key	block_keys;
	काष्ठा xfs_btree_cur	*cur = bs->cur;
	जोड़ xfs_btree_key	*high_bk;
	जोड़ xfs_btree_key	*parent_keys;
	जोड़ xfs_btree_key	*high_pk;
	काष्ठा xfs_btree_block	*parent_block;
	काष्ठा xfs_buf		*bp;

	अगर (level >= cur->bc_nlevels - 1)
		वापस;

	/* Calculate the keys क्रम this block. */
	xfs_btree_get_keys(cur, block, &block_keys);

	/* Obtain the parent's copy of the keys क्रम this block. */
	parent_block = xfs_btree_get_block(cur, level + 1, &bp);
	parent_keys = xfs_btree_key_addr(cur, cur->bc_ptrs[level + 1],
			parent_block);

	अगर (cur->bc_ops->dअगरf_two_keys(cur, &block_keys, parent_keys) != 0)
		xchk_btree_set_corrupt(bs->sc, cur, 1);

	अगर (!(cur->bc_flags & XFS_BTREE_OVERLAPPING))
		वापस;

	/* Get high keys */
	high_bk = xfs_btree_high_key_from_key(cur, &block_keys);
	high_pk = xfs_btree_high_key_addr(cur, cur->bc_ptrs[level + 1],
			parent_block);

	अगर (cur->bc_ops->dअगरf_two_keys(cur, high_bk, high_pk) != 0)
		xchk_btree_set_corrupt(bs->sc, cur, 1);
पूर्ण

/*
 * Visit all nodes and leaves of a btree.  Check that all poपूर्णांकers and
 * records are in order, that the keys reflect the records, and use a callback
 * so that the caller can verअगरy inभागidual records.
 */
पूर्णांक
xchk_btree(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_btree_cur		*cur,
	xchk_btree_rec_fn		scrub_fn,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	व्योम				*निजी)
अणु
	काष्ठा xchk_btree		bs = अणु
		.cur			= cur,
		.scrub_rec		= scrub_fn,
		.oinfo			= oinfo,
		.firstrec		= true,
		.निजी		= निजी,
		.sc			= sc,
	पूर्ण;
	जोड़ xfs_btree_ptr		ptr;
	जोड़ xfs_btree_ptr		*pp;
	जोड़ xfs_btree_rec		*recp;
	काष्ठा xfs_btree_block		*block;
	पूर्णांक				level;
	काष्ठा xfs_buf			*bp;
	काष्ठा check_owner		*co;
	काष्ठा check_owner		*n;
	पूर्णांक				i;
	पूर्णांक				error = 0;

	/* Initialize scrub state */
	क्रम (i = 0; i < XFS_BTREE_MAXLEVELS; i++)
		bs.firstkey[i] = true;
	INIT_LIST_HEAD(&bs.to_check);

	/* Don't try to check a tree with a height we can't handle. */
	अगर (cur->bc_nlevels > XFS_BTREE_MAXLEVELS) अणु
		xchk_btree_set_corrupt(sc, cur, 0);
		जाओ out;
	पूर्ण

	/*
	 * Load the root of the btree.  The helper function असलorbs
	 * error codes क्रम us.
	 */
	level = cur->bc_nlevels - 1;
	cur->bc_ops->init_ptr_from_cur(cur, &ptr);
	अगर (!xchk_btree_ptr_ok(&bs, cur->bc_nlevels, &ptr))
		जाओ out;
	error = xchk_btree_get_block(&bs, level, &ptr, &block, &bp);
	अगर (error || !block)
		जाओ out;

	cur->bc_ptrs[level] = 1;

	जबतक (level < cur->bc_nlevels) अणु
		block = xfs_btree_get_block(cur, level, &bp);

		अगर (level == 0) अणु
			/* End of leaf, pop back towards the root. */
			अगर (cur->bc_ptrs[level] >
			    be16_to_cpu(block->bb_numrecs)) अणु
				xchk_btree_block_keys(&bs, level, block);
				अगर (level < cur->bc_nlevels - 1)
					cur->bc_ptrs[level + 1]++;
				level++;
				जारी;
			पूर्ण

			/* Records in order क्रम scrub? */
			xchk_btree_rec(&bs);

			/* Call out to the record checker. */
			recp = xfs_btree_rec_addr(cur, cur->bc_ptrs[0], block);
			error = bs.scrub_rec(&bs, recp);
			अगर (error)
				अवरोध;
			अगर (xchk_should_terminate(sc, &error) ||
			    (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
				अवरोध;

			cur->bc_ptrs[level]++;
			जारी;
		पूर्ण

		/* End of node, pop back towards the root. */
		अगर (cur->bc_ptrs[level] > be16_to_cpu(block->bb_numrecs)) अणु
			xchk_btree_block_keys(&bs, level, block);
			अगर (level < cur->bc_nlevels - 1)
				cur->bc_ptrs[level + 1]++;
			level++;
			जारी;
		पूर्ण

		/* Keys in order क्रम scrub? */
		xchk_btree_key(&bs, level);

		/* Drill another level deeper. */
		pp = xfs_btree_ptr_addr(cur, cur->bc_ptrs[level], block);
		अगर (!xchk_btree_ptr_ok(&bs, level, pp)) अणु
			cur->bc_ptrs[level]++;
			जारी;
		पूर्ण
		level--;
		error = xchk_btree_get_block(&bs, level, pp, &block, &bp);
		अगर (error || !block)
			जाओ out;

		cur->bc_ptrs[level] = 1;
	पूर्ण

out:
	/* Process deferred owner checks on btree blocks. */
	list_क्रम_each_entry_safe(co, n, &bs.to_check, list) अणु
		अगर (!error && bs.cur)
			error = xchk_btree_check_block_owner(&bs,
					co->level, co->daddr);
		list_del(&co->list);
		kmem_मुक्त(co);
	पूर्ण

	वापस error;
पूर्ण
