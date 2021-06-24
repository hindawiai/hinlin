<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "xfs_ialloc_btree.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_ag_resv.h"

/*
 * Per-AG Block Reservations
 *
 * For some kinds of allocation group metadata काष्ठाures, it is advantageous
 * to reserve a small number of blocks in each AG so that future expansions of
 * that data काष्ठाure करो not encounter ENOSPC because errors during a btree
 * split cause the fileप्रणाली to go offline.
 *
 * Prior to the पूर्णांकroduction of reflink, this wasn't an issue because the मुक्त
 * space btrees मुख्यtain a reserve of space (the AGFL) to handle any expansion
 * that may be necessary; and allocations of other metadata (inodes, BMBT,
 * dir/attr) aren't restricted to a single AG.  However, with reflink it is
 * possible to allocate all the space in an AG, have subsequent reflink/CoW
 * activity expand the refcount btree, and discover that there's no space left
 * to handle that expansion.  Since we can calculate the maximum size of the
 * refcount btree, we can reserve space क्रम it and aव्योम ENOSPC.
 *
 * Handling per-AG reservations consists of three changes to the allocator's
 * behavior:  First, because these reservations are always needed, we decrease
 * the ag_max_usable counter to reflect the size of the AG after the reserved
 * blocks are taken.  Second, the reservations must be reflected in the
 * fdblocks count to मुख्यtain proper accounting.  Third, each AG must मुख्यtain
 * its own reserved block counter so that we can calculate the amount of space
 * that must reमुख्य मुक्त to मुख्यtain the reservations.  Fourth, the "reमुख्यing
 * reserved blocks" count must be used when calculating the length of the
 * दीर्घest मुक्त extent in an AG and to clamp maxlen in the per-AG allocation
 * functions.  In other words, we मुख्यtain a भव allocation via in-core
 * accounting tricks so that we करोn't have to clean up after a crash. :)
 *
 * Reserved blocks can be managed by passing one of the क्रमागत xfs_ag_resv_type
 * values via काष्ठा xfs_alloc_arg or directly to the xfs_मुक्त_extent
 * function.  It might seem a little funny to मुख्यtain a reservoir of blocks
 * to feed another reservoir, but the AGFL only holds enough blocks to get
 * through the next transaction.  The per-AG reservation is to ensure (we
 * hope) that each AG never runs out of blocks.  Each data काष्ठाure wanting
 * to use the reservation प्रणाली should update ask/used in xfs_ag_resv_init.
 */

/*
 * Are we critically low on blocks?  For now we'll define that as the number
 * of blocks we can get our hands on being less than 10% of what we reserved
 * or less than some arbitrary number (maximum btree height).
 */
bool
xfs_ag_resv_critical(
	काष्ठा xfs_perag		*pag,
	क्रमागत xfs_ag_resv_type		type)
अणु
	xfs_extlen_t			avail;
	xfs_extlen_t			orig;

	चयन (type) अणु
	हाल XFS_AG_RESV_METADATA:
		avail = pag->pagf_मुक्तblks - pag->pag_rmapbt_resv.ar_reserved;
		orig = pag->pag_meta_resv.ar_asked;
		अवरोध;
	हाल XFS_AG_RESV_RMAPBT:
		avail = pag->pagf_मुक्तblks + pag->pagf_flcount -
			pag->pag_meta_resv.ar_reserved;
		orig = pag->pag_rmapbt_resv.ar_asked;
		अवरोध;
	शेष:
		ASSERT(0);
		वापस false;
	पूर्ण

	trace_xfs_ag_resv_critical(pag, type, avail);

	/* Critically low अगर less than 10% or max btree height reमुख्यs. */
	वापस XFS_TEST_ERROR(avail < orig / 10 || avail < XFS_BTREE_MAXLEVELS,
			pag->pag_mount, XFS_ERRTAG_AG_RESV_CRITICAL);
पूर्ण

/*
 * How many blocks are reserved but not used, and thereक्रमe must not be
 * allocated away?
 */
xfs_extlen_t
xfs_ag_resv_needed(
	काष्ठा xfs_perag		*pag,
	क्रमागत xfs_ag_resv_type		type)
अणु
	xfs_extlen_t			len;

	len = pag->pag_meta_resv.ar_reserved + pag->pag_rmapbt_resv.ar_reserved;
	चयन (type) अणु
	हाल XFS_AG_RESV_METADATA:
	हाल XFS_AG_RESV_RMAPBT:
		len -= xfs_perag_resv(pag, type)->ar_reserved;
		अवरोध;
	हाल XFS_AG_RESV_NONE:
		/* empty */
		अवरोध;
	शेष:
		ASSERT(0);
	पूर्ण

	trace_xfs_ag_resv_needed(pag, type, len);

	वापस len;
पूर्ण

/* Clean out a reservation */
अटल पूर्णांक
__xfs_ag_resv_मुक्त(
	काष्ठा xfs_perag		*pag,
	क्रमागत xfs_ag_resv_type		type)
अणु
	काष्ठा xfs_ag_resv		*resv;
	xfs_extlen_t			oldresv;
	पूर्णांक				error;

	trace_xfs_ag_resv_मुक्त(pag, type, 0);

	resv = xfs_perag_resv(pag, type);
	अगर (pag->pag_agno == 0)
		pag->pag_mount->m_ag_max_usable += resv->ar_asked;
	/*
	 * RMAPBT blocks come from the AGFL and AGFL blocks are always
	 * considered "free", so whatever was reserved at mount समय must be
	 * given back at umount.
	 */
	अगर (type == XFS_AG_RESV_RMAPBT)
		oldresv = resv->ar_orig_reserved;
	अन्यथा
		oldresv = resv->ar_reserved;
	error = xfs_mod_fdblocks(pag->pag_mount, oldresv, true);
	resv->ar_reserved = 0;
	resv->ar_asked = 0;
	resv->ar_orig_reserved = 0;

	अगर (error)
		trace_xfs_ag_resv_मुक्त_error(pag->pag_mount, pag->pag_agno,
				error, _RET_IP_);
	वापस error;
पूर्ण

/* Free a per-AG reservation. */
पूर्णांक
xfs_ag_resv_मुक्त(
	काष्ठा xfs_perag		*pag)
अणु
	पूर्णांक				error;
	पूर्णांक				err2;

	error = __xfs_ag_resv_मुक्त(pag, XFS_AG_RESV_RMAPBT);
	err2 = __xfs_ag_resv_मुक्त(pag, XFS_AG_RESV_METADATA);
	अगर (err2 && !error)
		error = err2;
	वापस error;
पूर्ण

अटल पूर्णांक
__xfs_ag_resv_init(
	काष्ठा xfs_perag		*pag,
	क्रमागत xfs_ag_resv_type		type,
	xfs_extlen_t			ask,
	xfs_extlen_t			used)
अणु
	काष्ठा xfs_mount		*mp = pag->pag_mount;
	काष्ठा xfs_ag_resv		*resv;
	पूर्णांक				error;
	xfs_extlen_t			hidden_space;

	अगर (used > ask)
		ask = used;

	चयन (type) अणु
	हाल XFS_AG_RESV_RMAPBT:
		/*
		 * Space taken by the rmapbt is not subtracted from fdblocks
		 * because the rmapbt lives in the मुक्त space.  Here we must
		 * subtract the entire reservation from fdblocks so that we
		 * always have blocks available क्रम rmapbt expansion.
		 */
		hidden_space = ask;
		अवरोध;
	हाल XFS_AG_RESV_METADATA:
		/*
		 * Space taken by all other metadata btrees are accounted
		 * on-disk as used space.  We thereक्रमe only hide the space
		 * that is reserved but not used by the trees.
		 */
		hidden_space = ask - used;
		अवरोध;
	शेष:
		ASSERT(0);
		वापस -EINVAL;
	पूर्ण

	अगर (XFS_TEST_ERROR(false, mp, XFS_ERRTAG_AG_RESV_FAIL))
		error = -ENOSPC;
	अन्यथा
		error = xfs_mod_fdblocks(mp, -(पूर्णांक64_t)hidden_space, true);
	अगर (error) अणु
		trace_xfs_ag_resv_init_error(pag->pag_mount, pag->pag_agno,
				error, _RET_IP_);
		xfs_warn(mp,
"Per-AG reservation for AG %u failed.  Filesystem may run out of space.",
				pag->pag_agno);
		वापस error;
	पूर्ण

	/*
	 * Reduce the maximum per-AG allocation length by however much we're
	 * trying to reserve क्रम an AG.  Since this is a fileप्रणाली-wide
	 * counter, we only make the adjusपंचांगent क्रम AG 0.  This assumes that
	 * there aren't any AGs hungrier क्रम per-AG reservation than AG 0.
	 */
	अगर (pag->pag_agno == 0)
		mp->m_ag_max_usable -= ask;

	resv = xfs_perag_resv(pag, type);
	resv->ar_asked = ask;
	resv->ar_orig_reserved = hidden_space;
	resv->ar_reserved = ask - used;

	trace_xfs_ag_resv_init(pag, type, ask);
	वापस 0;
पूर्ण

/* Create a per-AG block reservation. */
पूर्णांक
xfs_ag_resv_init(
	काष्ठा xfs_perag		*pag,
	काष्ठा xfs_trans		*tp)
अणु
	काष्ठा xfs_mount		*mp = pag->pag_mount;
	xfs_agnumber_t			agno = pag->pag_agno;
	xfs_extlen_t			ask;
	xfs_extlen_t			used;
	पूर्णांक				error = 0, error2;
	bool				has_resv = false;

	/* Create the metadata reservation. */
	अगर (pag->pag_meta_resv.ar_asked == 0) अणु
		ask = used = 0;

		error = xfs_refcountbt_calc_reserves(mp, tp, agno, &ask, &used);
		अगर (error)
			जाओ out;

		error = xfs_finobt_calc_reserves(mp, tp, agno, &ask, &used);
		अगर (error)
			जाओ out;

		error = __xfs_ag_resv_init(pag, XFS_AG_RESV_METADATA,
				ask, used);
		अगर (error) अणु
			/*
			 * Because we didn't have per-AG reservations when the
			 * finobt feature was added we might not be able to
			 * reserve all needed blocks.  Warn and fall back to the
			 * old and potentially buggy code in that हाल, but
			 * ensure we करो have the reservation क्रम the refcountbt.
			 */
			ask = used = 0;

			mp->m_finobt_nores = true;

			error = xfs_refcountbt_calc_reserves(mp, tp, agno, &ask,
					&used);
			अगर (error)
				जाओ out;

			error = __xfs_ag_resv_init(pag, XFS_AG_RESV_METADATA,
					ask, used);
			अगर (error)
				जाओ out;
		पूर्ण
		अगर (ask)
			has_resv = true;
	पूर्ण

	/* Create the RMAPBT metadata reservation */
	अगर (pag->pag_rmapbt_resv.ar_asked == 0) अणु
		ask = used = 0;

		error = xfs_rmapbt_calc_reserves(mp, tp, agno, &ask, &used);
		अगर (error)
			जाओ out;

		error = __xfs_ag_resv_init(pag, XFS_AG_RESV_RMAPBT, ask, used);
		अगर (error)
			जाओ out;
		अगर (ask)
			has_resv = true;
	पूर्ण

out:
	/*
	 * Initialize the pagf अगर we have at least one active reservation on the
	 * AG. This may have occurred alपढ़ोy via reservation calculation, but
	 * fall back to an explicit init to ensure the in-core allocbt usage
	 * counters are initialized as soon as possible. This is important
	 * because fileप्रणालीs with large perag reservations are susceptible to
	 * मुक्त space reservation problems that the allocbt counter is used to
	 * address.
	 */
	अगर (has_resv) अणु
		error2 = xfs_alloc_pagf_init(mp, tp, pag->pag_agno, 0);
		अगर (error2)
			वापस error2;

		/*
		 * If there isn't enough space in the AG to satisfy the
		 * reservation, let the caller know that there wasn't enough
		 * space.  Callers are responsible क्रम deciding what to करो
		 * next, since (in theory) we can stumble aदीर्घ with
		 * insufficient reservation अगर data blocks are being मुक्तd to
		 * replenish the AG's मुक्त space.
		 */
		अगर (!error &&
		    xfs_perag_resv(pag, XFS_AG_RESV_METADATA)->ar_reserved +
		    xfs_perag_resv(pag, XFS_AG_RESV_RMAPBT)->ar_reserved >
		    pag->pagf_मुक्तblks + pag->pagf_flcount)
			error = -ENOSPC;
	पूर्ण

	वापस error;
पूर्ण

/* Allocate a block from the reservation. */
व्योम
xfs_ag_resv_alloc_extent(
	काष्ठा xfs_perag		*pag,
	क्रमागत xfs_ag_resv_type		type,
	काष्ठा xfs_alloc_arg		*args)
अणु
	काष्ठा xfs_ag_resv		*resv;
	xfs_extlen_t			len;
	uपूर्णांक				field;

	trace_xfs_ag_resv_alloc_extent(pag, type, args->len);

	चयन (type) अणु
	हाल XFS_AG_RESV_AGFL:
		वापस;
	हाल XFS_AG_RESV_METADATA:
	हाल XFS_AG_RESV_RMAPBT:
		resv = xfs_perag_resv(pag, type);
		अवरोध;
	शेष:
		ASSERT(0);
		/* fall through */
	हाल XFS_AG_RESV_NONE:
		field = args->wasdel ? XFS_TRANS_SB_RES_FDBLOCKS :
				       XFS_TRANS_SB_FDBLOCKS;
		xfs_trans_mod_sb(args->tp, field, -(पूर्णांक64_t)args->len);
		वापस;
	पूर्ण

	len = min_t(xfs_extlen_t, args->len, resv->ar_reserved);
	resv->ar_reserved -= len;
	अगर (type == XFS_AG_RESV_RMAPBT)
		वापस;
	/* Allocations of reserved blocks only need on-disk sb updates... */
	xfs_trans_mod_sb(args->tp, XFS_TRANS_SB_RES_FDBLOCKS, -(पूर्णांक64_t)len);
	/* ...but non-reserved blocks need in-core and on-disk updates. */
	अगर (args->len > len)
		xfs_trans_mod_sb(args->tp, XFS_TRANS_SB_FDBLOCKS,
				-((पूर्णांक64_t)args->len - len));
पूर्ण

/* Free a block to the reservation. */
व्योम
xfs_ag_resv_मुक्त_extent(
	काष्ठा xfs_perag		*pag,
	क्रमागत xfs_ag_resv_type		type,
	काष्ठा xfs_trans		*tp,
	xfs_extlen_t			len)
अणु
	xfs_extlen_t			leftover;
	काष्ठा xfs_ag_resv		*resv;

	trace_xfs_ag_resv_मुक्त_extent(pag, type, len);

	चयन (type) अणु
	हाल XFS_AG_RESV_AGFL:
		वापस;
	हाल XFS_AG_RESV_METADATA:
	हाल XFS_AG_RESV_RMAPBT:
		resv = xfs_perag_resv(pag, type);
		अवरोध;
	शेष:
		ASSERT(0);
		/* fall through */
	हाल XFS_AG_RESV_NONE:
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_FDBLOCKS, (पूर्णांक64_t)len);
		वापस;
	पूर्ण

	leftover = min_t(xfs_extlen_t, len, resv->ar_asked - resv->ar_reserved);
	resv->ar_reserved += leftover;
	अगर (type == XFS_AG_RESV_RMAPBT)
		वापस;
	/* Freeing पूर्णांकo the reserved pool only requires on-disk update... */
	xfs_trans_mod_sb(tp, XFS_TRANS_SB_RES_FDBLOCKS, len);
	/* ...but मुक्तing beyond that requires in-core and on-disk update. */
	अगर (len > leftover)
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_FDBLOCKS, len - leftover);
पूर्ण
