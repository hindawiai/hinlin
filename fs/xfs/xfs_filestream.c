<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2006-2007 Silicon Graphics, Inc.
 * Copyright (c) 2014 Christoph Hellwig.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_mru_cache.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_ag_resv.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_filestream.h"

काष्ठा xfs_fstrm_item अणु
	काष्ठा xfs_mru_cache_elem	mru;
	xfs_agnumber_t			ag; /* AG in use क्रम this directory */
पूर्ण;

क्रमागत xfs_fstrm_alloc अणु
	XFS_PICK_USERDATA = 1,
	XFS_PICK_LOWSPACE = 2,
पूर्ण;

/*
 * Allocation group filestream associations are tracked with per-ag atomic
 * counters.  These counters allow xfs_filestream_pick_ag() to tell whether a
 * particular AG alपढ़ोy has active filestreams associated with it.
 */
पूर्णांक
xfs_filestream_peek_ag(
	xfs_mount_t	*mp,
	xfs_agnumber_t	agno)
अणु
	काष्ठा xfs_perag *pag;
	पूर्णांक		ret;

	pag = xfs_perag_get(mp, agno);
	ret = atomic_पढ़ो(&pag->pagf_fstrms);
	xfs_perag_put(pag);
	वापस ret;
पूर्ण

अटल पूर्णांक
xfs_filestream_get_ag(
	xfs_mount_t	*mp,
	xfs_agnumber_t	agno)
अणु
	काष्ठा xfs_perag *pag;
	पूर्णांक		ret;

	pag = xfs_perag_get(mp, agno);
	ret = atomic_inc_वापस(&pag->pagf_fstrms);
	xfs_perag_put(pag);
	वापस ret;
पूर्ण

अटल व्योम
xfs_filestream_put_ag(
	xfs_mount_t	*mp,
	xfs_agnumber_t	agno)
अणु
	काष्ठा xfs_perag *pag;

	pag = xfs_perag_get(mp, agno);
	atomic_dec(&pag->pagf_fstrms);
	xfs_perag_put(pag);
पूर्ण

अटल व्योम
xfs_fstrm_मुक्त_func(
	व्योम			*data,
	काष्ठा xfs_mru_cache_elem *mru)
अणु
	काष्ठा xfs_mount	*mp = data;
	काष्ठा xfs_fstrm_item	*item =
		container_of(mru, काष्ठा xfs_fstrm_item, mru);

	xfs_filestream_put_ag(mp, item->ag);
	trace_xfs_filestream_मुक्त(mp, mru->key, item->ag);

	kmem_मुक्त(item);
पूर्ण

/*
 * Scan the AGs starting at startag looking क्रम an AG that isn't in use and has
 * at least minlen blocks मुक्त.
 */
अटल पूर्णांक
xfs_filestream_pick_ag(
	काष्ठा xfs_inode	*ip,
	xfs_agnumber_t		startag,
	xfs_agnumber_t		*agp,
	पूर्णांक			flags,
	xfs_extlen_t		minlen)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_fstrm_item	*item;
	काष्ठा xfs_perag	*pag;
	xfs_extlen_t		दीर्घest, मुक्त = 0, minमुक्त, maxमुक्त = 0;
	xfs_agnumber_t		ag, max_ag = शून्यAGNUMBER;
	पूर्णांक			err, trylock, nscan;

	ASSERT(S_ISसूची(VFS_I(ip)->i_mode));

	/* 2% of an AG's blocks must be मुक्त क्रम it to be chosen. */
	minमुक्त = mp->m_sb.sb_agblocks / 50;

	ag = startag;
	*agp = शून्यAGNUMBER;

	/* For the first pass, करोn't sleep trying to init the per-AG. */
	trylock = XFS_ALLOC_FLAG_TRYLOCK;

	क्रम (nscan = 0; 1; nscan++) अणु
		trace_xfs_filestream_scan(mp, ip->i_ino, ag);

		pag = xfs_perag_get(mp, ag);

		अगर (!pag->pagf_init) अणु
			err = xfs_alloc_pagf_init(mp, शून्य, ag, trylock);
			अगर (err) अणु
				xfs_perag_put(pag);
				अगर (err != -EAGAIN)
					वापस err;
				/* Couldn't lock the AGF, skip this AG. */
				जारी;
			पूर्ण
		पूर्ण

		/* Keep track of the AG with the most मुक्त blocks. */
		अगर (pag->pagf_मुक्तblks > maxमुक्त) अणु
			maxमुक्त = pag->pagf_मुक्तblks;
			max_ag = ag;
		पूर्ण

		/*
		 * The AG reference count करोes two things: it enक्रमces mutual
		 * exclusion when examining the suitability of an AG in this
		 * loop, and it guards against two filestreams being established
		 * in the same AG as each other.
		 */
		अगर (xfs_filestream_get_ag(mp, ag) > 1) अणु
			xfs_filestream_put_ag(mp, ag);
			जाओ next_ag;
		पूर्ण

		दीर्घest = xfs_alloc_दीर्घest_मुक्त_extent(pag,
				xfs_alloc_min_मुक्तlist(mp, pag),
				xfs_ag_resv_needed(pag, XFS_AG_RESV_NONE));
		अगर (((minlen && दीर्घest >= minlen) ||
		     (!minlen && pag->pagf_मुक्तblks >= minमुक्त)) &&
		    (!pag->pagf_metadata || !(flags & XFS_PICK_USERDATA) ||
		     (flags & XFS_PICK_LOWSPACE))) अणु

			/* Break out, retaining the reference on the AG. */
			मुक्त = pag->pagf_मुक्तblks;
			xfs_perag_put(pag);
			*agp = ag;
			अवरोध;
		पूर्ण

		/* Drop the reference on this AG, it's not usable. */
		xfs_filestream_put_ag(mp, ag);
next_ag:
		xfs_perag_put(pag);
		/* Move to the next AG, wrapping to AG 0 अगर necessary. */
		अगर (++ag >= mp->m_sb.sb_agcount)
			ag = 0;

		/* If a full pass of the AGs hasn't been करोne yet, जारी. */
		अगर (ag != startag)
			जारी;

		/* Allow sleeping in xfs_alloc_pagf_init() on the 2nd pass. */
		अगर (trylock != 0) अणु
			trylock = 0;
			जारी;
		पूर्ण

		/* Finally, अगर lowspace wasn't set, set it क्रम the 3rd pass. */
		अगर (!(flags & XFS_PICK_LOWSPACE)) अणु
			flags |= XFS_PICK_LOWSPACE;
			जारी;
		पूर्ण

		/*
		 * Take the AG with the most मुक्त space, regardless of whether
		 * it's alपढ़ोy in use by another filestream.
		 */
		अगर (max_ag != शून्यAGNUMBER) अणु
			xfs_filestream_get_ag(mp, max_ag);
			मुक्त = maxमुक्त;
			*agp = max_ag;
			अवरोध;
		पूर्ण

		/* take AG 0 अगर none matched */
		trace_xfs_filestream_pick(ip, *agp, मुक्त, nscan);
		*agp = 0;
		वापस 0;
	पूर्ण

	trace_xfs_filestream_pick(ip, *agp, मुक्त, nscan);

	अगर (*agp == शून्यAGNUMBER)
		वापस 0;

	err = -ENOMEM;
	item = kmem_alloc(माप(*item), KM_MAYFAIL);
	अगर (!item)
		जाओ out_put_ag;

	item->ag = *agp;

	err = xfs_mru_cache_insert(mp->m_filestream, ip->i_ino, &item->mru);
	अगर (err) अणु
		अगर (err == -EEXIST)
			err = 0;
		जाओ out_मुक्त_item;
	पूर्ण

	वापस 0;

out_मुक्त_item:
	kmem_मुक्त(item);
out_put_ag:
	xfs_filestream_put_ag(mp, *agp);
	वापस err;
पूर्ण

अटल काष्ठा xfs_inode *
xfs_filestream_get_parent(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा inode		*inode = VFS_I(ip), *dir = शून्य;
	काष्ठा dentry		*dentry, *parent;

	dentry = d_find_alias(inode);
	अगर (!dentry)
		जाओ out;

	parent = dget_parent(dentry);
	अगर (!parent)
		जाओ out_dput;

	dir = igrab(d_inode(parent));
	dput(parent);

out_dput:
	dput(dentry);
out:
	वापस dir ? XFS_I(dir) : शून्य;
पूर्ण

/*
 * Find the right allocation group क्रम a file, either by finding an
 * existing file stream or creating a new one.
 *
 * Returns शून्यAGNUMBER in हाल of an error.
 */
xfs_agnumber_t
xfs_filestream_lookup_ag(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_inode	*pip = शून्य;
	xfs_agnumber_t		startag, ag = शून्यAGNUMBER;
	काष्ठा xfs_mru_cache_elem *mru;

	ASSERT(S_ISREG(VFS_I(ip)->i_mode));

	pip = xfs_filestream_get_parent(ip);
	अगर (!pip)
		वापस शून्यAGNUMBER;

	mru = xfs_mru_cache_lookup(mp->m_filestream, pip->i_ino);
	अगर (mru) अणु
		ag = container_of(mru, काष्ठा xfs_fstrm_item, mru)->ag;
		xfs_mru_cache_करोne(mp->m_filestream);

		trace_xfs_filestream_lookup(mp, ip->i_ino, ag);
		जाओ out;
	पूर्ण

	/*
	 * Set the starting AG using the rotor क्रम inode32, otherwise
	 * use the directory inode's AG.
	 */
	अगर (mp->m_flags & XFS_MOUNT_32BITINODES) अणु
		xfs_agnumber_t	 rotorstep = xfs_rotorstep;
		startag = (mp->m_agfrotor / rotorstep) % mp->m_sb.sb_agcount;
		mp->m_agfrotor = (mp->m_agfrotor + 1) %
		                 (mp->m_sb.sb_agcount * rotorstep);
	पूर्ण अन्यथा
		startag = XFS_INO_TO_AGNO(mp, pip->i_ino);

	अगर (xfs_filestream_pick_ag(pip, startag, &ag, 0, 0))
		ag = शून्यAGNUMBER;
out:
	xfs_irele(pip);
	वापस ag;
पूर्ण

/*
 * Pick a new allocation group क्रम the current file and its file stream.
 *
 * This is called when the allocator can't find a suitable extent in the
 * current AG, and we have to move the stream पूर्णांकo a new AG with more space.
 */
पूर्णांक
xfs_filestream_new_ag(
	काष्ठा xfs_bदो_स्मृतिa	*ap,
	xfs_agnumber_t		*agp)
अणु
	काष्ठा xfs_inode	*ip = ap->ip, *pip;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_extlen_t		minlen = ap->length;
	xfs_agnumber_t		startag = 0;
	पूर्णांक			flags = 0;
	पूर्णांक			err = 0;
	काष्ठा xfs_mru_cache_elem *mru;

	*agp = शून्यAGNUMBER;

	pip = xfs_filestream_get_parent(ip);
	अगर (!pip)
		जाओ निकास;

	mru = xfs_mru_cache_हटाओ(mp->m_filestream, pip->i_ino);
	अगर (mru) अणु
		काष्ठा xfs_fstrm_item *item =
			container_of(mru, काष्ठा xfs_fstrm_item, mru);
		startag = (item->ag + 1) % mp->m_sb.sb_agcount;
	पूर्ण

	अगर (ap->datatype & XFS_ALLOC_USERDATA)
		flags |= XFS_PICK_USERDATA;
	अगर (ap->tp->t_flags & XFS_TRANS_LOWMODE)
		flags |= XFS_PICK_LOWSPACE;

	err = xfs_filestream_pick_ag(pip, startag, agp, flags, minlen);

	/*
	 * Only मुक्त the item here so we skip over the old AG earlier.
	 */
	अगर (mru)
		xfs_fstrm_मुक्त_func(mp, mru);

	xfs_irele(pip);
निकास:
	अगर (*agp == शून्यAGNUMBER)
		*agp = 0;
	वापस err;
पूर्ण

व्योम
xfs_filestream_deassociate(
	काष्ठा xfs_inode	*ip)
अणु
	xfs_mru_cache_delete(ip->i_mount->m_filestream, ip->i_ino);
पूर्ण

पूर्णांक
xfs_filestream_mount(
	xfs_mount_t	*mp)
अणु
	/*
	 * The filestream समयr tunable is currently fixed within the range of
	 * one second to four minutes, with five seconds being the शेष.  The
	 * group count is somewhat arbitrary, but it'd be nice to adhere to the
	 * समयr tunable to within about 10 percent.  This requires at least 10
	 * groups.
	 */
	वापस xfs_mru_cache_create(&mp->m_filestream, mp,
			xfs_fstrm_centisecs * 10, 10, xfs_fstrm_मुक्त_func);
पूर्ण

व्योम
xfs_filestream_unmount(
	xfs_mount_t	*mp)
अणु
	xfs_mru_cache_destroy(mp->m_filestream);
पूर्ण
