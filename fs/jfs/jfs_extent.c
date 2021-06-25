<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */

#समावेश <linux/fs.h>
#समावेश <linux/quotaops.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_extent.h"
#समावेश "jfs_debug.h"

/*
 * क्रमward references
 */
अटल पूर्णांक extBalloc(काष्ठा inode *, s64, s64 *, s64 *);
#अगर_घोषित _NOTYET
अटल पूर्णांक extBपुनः_स्मृति(काष्ठा inode *, s64, s64, s64 *, s64 *);
#पूर्ण_अगर
अटल s64 extRoundDown(s64 nb);

#घोषणा DPD(a)		(prपूर्णांकk("(a): %d\n",(a)))
#घोषणा DPC(a)		(prपूर्णांकk("(a): %c\n",(a)))
#घोषणा DPL1(a)					\
अणु						\
	अगर ((a) >> 32)				\
		prपूर्णांकk("(a): %x%08x  ",(a));	\
	अन्यथा					\
		prपूर्णांकk("(a): %x  ",(a) << 32);	\
पूर्ण
#घोषणा DPL(a)					\
अणु						\
	अगर ((a) >> 32)				\
		prपूर्णांकk("(a): %x%08x\n",(a));	\
	अन्यथा					\
		prपूर्णांकk("(a): %x\n",(a) << 32);	\
पूर्ण

#घोषणा DPD1(a)		(prपूर्णांकk("(a): %d  ",(a)))
#घोषणा DPX(a)		(prपूर्णांकk("(a): %08x\n",(a)))
#घोषणा DPX1(a)		(prपूर्णांकk("(a): %08x  ",(a)))
#घोषणा DPS(a)		(prपूर्णांकk("%s\n",(a)))
#घोषणा DPE(a)		(prपूर्णांकk("\nENTERING: %s\n",(a)))
#घोषणा DPE1(a)		(prपूर्णांकk("\nENTERING: %s",(a)))
#घोषणा DPS1(a)		(prपूर्णांकk("  %s  ",(a)))


/*
 * NAME:	extAlloc()
 *
 * FUNCTION:	allocate an extent क्रम a specअगरied page range within a
 *		file.
 *
 * PARAMETERS:
 *	ip	- the inode of the file.
 *	xlen	- requested extent length.
 *	pno	- the starting page number with the file.
 *	xp	- poपूर्णांकer to an xad.  on entry, xad describes an
 *		  extent that is used as an allocation hपूर्णांक अगर the
 *		  xaddr of the xad is non-zero.  on successful निकास,
 *		  the xad describes the newly allocated extent.
 *	abnr	- bool indicating whether the newly allocated extent
 *		  should be marked as allocated but not recorded.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 *	-ENOSPC	- insufficient disk resources.
 */
पूर्णांक
extAlloc(काष्ठा inode *ip, s64 xlen, s64 pno, xad_t * xp, bool abnr)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	s64 nxlen, nxaddr, xoff, hपूर्णांक, xaddr = 0;
	पूर्णांक rc;
	पूर्णांक xflag;

	/* This blocks अगर we are low on resources */
	txBeginAnon(ip->i_sb);

	/* Aव्योम race with jfs_commit_inode() */
	mutex_lock(&JFS_IP(ip)->commit_mutex);

	/* validate extent length */
	अगर (xlen > MAXXLEN)
		xlen = MAXXLEN;

	/* get the page's starting extent offset */
	xoff = pno << sbi->l2nbperpage;

	/* check अगर an allocation hपूर्णांक was provided */
	अगर ((hपूर्णांक = addressXAD(xp))) अणु
		/* get the size of the extent described by the hपूर्णांक */
		nxlen = lengthXAD(xp);

		/* check अगर the hपूर्णांक is क्रम the portion of the file
		 * immediately previous to the current allocation
		 * request and अगर hपूर्णांक extent has the same abnr
		 * value as the current request.  अगर so, we can
		 * extend the hपूर्णांक extent to include the current
		 * extent अगर we can allocate the blocks immediately
		 * following the hपूर्णांक extent.
		 */
		अगर (offsetXAD(xp) + nxlen == xoff &&
		    abnr == ((xp->flag & XAD_NOTRECORDED) ? true : false))
			xaddr = hपूर्णांक + nxlen;

		/* adjust the hपूर्णांक to the last block of the extent */
		hपूर्णांक += (nxlen - 1);
	पूर्ण

	/* allocate the disk blocks क्रम the extent.  initially, extBalloc()
	 * will try to allocate disk blocks क्रम the requested size (xlen).
	 * अगर this fails (xlen contiguous मुक्त blocks not available), it'll
	 * try to allocate a smaller number of blocks (producing a smaller
	 * extent), with this smaller number of blocks consisting of the
	 * requested number of blocks rounded करोwn to the next smaller
	 * घातer of 2 number (i.e. 16 -> 8).  it'll जारी to round करोwn
	 * and retry the allocation until the number of blocks to allocate
	 * is smaller than the number of blocks per page.
	 */
	nxlen = xlen;
	अगर ((rc = extBalloc(ip, hपूर्णांक ? hपूर्णांक : INOHINT(ip), &nxlen, &nxaddr))) अणु
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		वापस (rc);
	पूर्ण

	/* Allocate blocks to quota. */
	rc = dquot_alloc_block(ip, nxlen);
	अगर (rc) अणु
		dbFree(ip, nxaddr, (s64) nxlen);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		वापस rc;
	पूर्ण

	/* determine the value of the extent flag */
	xflag = abnr ? XAD_NOTRECORDED : 0;

	/* अगर we can extend the hपूर्णांक extent to cover the current request,
	 * extend it.  otherwise, insert a new extent to
	 * cover the current request.
	 */
	अगर (xaddr && xaddr == nxaddr)
		rc = xtExtend(0, ip, xoff, (पूर्णांक) nxlen, 0);
	अन्यथा
		rc = xtInsert(0, ip, xflag, xoff, (पूर्णांक) nxlen, &nxaddr, 0);

	/* अगर the extend or insert failed,
	 * मुक्त the newly allocated blocks and वापस the error.
	 */
	अगर (rc) अणु
		dbFree(ip, nxaddr, nxlen);
		dquot_मुक्त_block(ip, nxlen);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		वापस (rc);
	पूर्ण

	/* set the results of the extent allocation */
	XADaddress(xp, nxaddr);
	XADlength(xp, nxlen);
	XADoffset(xp, xoff);
	xp->flag = xflag;

	mark_inode_dirty(ip);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	/*
	 * COMMIT_SyncList flags an anonymous tlock on page that is on
	 * sync list.
	 * We need to commit the inode to get the page written disk.
	 */
	अगर (test_and_clear_cflag(COMMIT_Synclist,ip))
		jfs_commit_inode(ip, 0);

	वापस (0);
पूर्ण


#अगर_घोषित _NOTYET
/*
 * NAME:	extRealloc()
 *
 * FUNCTION:	extend the allocation of a file extent containing a
 *		partial back last page.
 *
 * PARAMETERS:
 *	ip	- the inode of the file.
 *	cp	- cbuf क्रम the partial backed last page.
 *	xlen	- request size of the resulting extent.
 *	xp	- poपूर्णांकer to an xad. on successful निकास, the xad
 *		  describes the newly allocated extent.
 *	abnr	- bool indicating whether the newly allocated extent
 *		  should be marked as allocated but not recorded.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 *	-ENOSPC	- insufficient disk resources.
 */
पूर्णांक extRealloc(काष्ठा inode *ip, s64 nxlen, xad_t * xp, bool abnr)
अणु
	काष्ठा super_block *sb = ip->i_sb;
	s64 xaddr, xlen, nxaddr, delta, xoff;
	s64 ntail, nextend, ninsert;
	पूर्णांक rc, nbperpage = JFS_SBI(sb)->nbperpage;
	पूर्णांक xflag;

	/* This blocks अगर we are low on resources */
	txBeginAnon(ip->i_sb);

	mutex_lock(&JFS_IP(ip)->commit_mutex);
	/* validate extent length */
	अगर (nxlen > MAXXLEN)
		nxlen = MAXXLEN;

	/* get the extend (partial) page's disk block address and
	 * number of blocks.
	 */
	xaddr = addressXAD(xp);
	xlen = lengthXAD(xp);
	xoff = offsetXAD(xp);

	/* अगर the extend page is abnr and अगर the request is क्रम
	 * the extent to be allocated and recorded,
	 * make the page allocated and recorded.
	 */
	अगर ((xp->flag & XAD_NOTRECORDED) && !abnr) अणु
		xp->flag = 0;
		अगर ((rc = xtUpdate(0, ip, xp)))
			जाओ निकास;
	पूर्ण

	/* try to allocated the request number of blocks क्रम the
	 * extent.  dbRealloc() first tries to satisfy the request
	 * by extending the allocation in place. otherwise, it will
	 * try to allocate a new set of blocks large enough क्रम the
	 * request.  in satisfying a request, dbReAlloc() may allocate
	 * less than what was request but will always allocate enough
	 * space as to satisfy the extend page.
	 */
	अगर ((rc = extBपुनः_स्मृति(ip, xaddr, xlen, &nxlen, &nxaddr)))
		जाओ निकास;

	/* Allocat blocks to quota. */
	rc = dquot_alloc_block(ip, nxlen);
	अगर (rc) अणु
		dbFree(ip, nxaddr, (s64) nxlen);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		वापस rc;
	पूर्ण

	delta = nxlen - xlen;

	/* check अगर the extend page is not abnr but the request is abnr
	 * and the allocated disk space is क्रम more than one page.  अगर this
	 * is the हाल, there is a miss match of abnr between the extend page
	 * and the one or more pages following the extend page.  as a result,
	 * two extents will have to be manipulated. the first will be that
	 * of the extent of the extend page and will be manipulated thru
	 * an xtExtend() or an xtTailgate(), depending upon whether the
	 * disk allocation occurred as an inplace extension.  the second
	 * extent will be manipulated (created) through an xtInsert() and
	 * will be क्रम the pages following the extend page.
	 */
	अगर (abnr && (!(xp->flag & XAD_NOTRECORDED)) && (nxlen > nbperpage)) अणु
		ntail = nbperpage;
		nextend = ntail - xlen;
		ninsert = nxlen - nbperpage;

		xflag = XAD_NOTRECORDED;
	पूर्ण अन्यथा अणु
		ntail = nxlen;
		nextend = delta;
		ninsert = 0;

		xflag = xp->flag;
	पूर्ण

	/* अगर we were able to extend the disk allocation in place,
	 * extend the extent.  otherwise, move the extent to a
	 * new disk location.
	 */
	अगर (xaddr == nxaddr) अणु
		/* extend the extent */
		अगर ((rc = xtExtend(0, ip, xoff + xlen, (पूर्णांक) nextend, 0))) अणु
			dbFree(ip, xaddr + xlen, delta);
			dquot_मुक्त_block(ip, nxlen);
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * move the extent to a new location:
		 *
		 * xtTailgate() accounts क्रम relocated tail extent;
		 */
		अगर ((rc = xtTailgate(0, ip, xoff, (पूर्णांक) ntail, nxaddr, 0))) अणु
			dbFree(ip, nxaddr, nxlen);
			dquot_मुक्त_block(ip, nxlen);
			जाओ निकास;
		पूर्ण
	पूर्ण


	/* check अगर we need to also insert a new extent */
	अगर (ninsert) अणु
		/* perक्रमm the insert.  अगर it fails, मुक्त the blocks
		 * to be inserted and make it appear that we only did
		 * the xtExtend() or xtTailgate() above.
		 */
		xaddr = nxaddr + ntail;
		अगर (xtInsert (0, ip, xflag, xoff + ntail, (पूर्णांक) ninsert,
			      &xaddr, 0)) अणु
			dbFree(ip, xaddr, (s64) ninsert);
			delta = nextend;
			nxlen = ntail;
			xflag = 0;
		पूर्ण
	पूर्ण

	/* set the वापस results */
	XADaddress(xp, nxaddr);
	XADlength(xp, nxlen);
	XADoffset(xp, xoff);
	xp->flag = xflag;

	mark_inode_dirty(ip);
निकास:
	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	वापस (rc);
पूर्ण
#पूर्ण_अगर			/* _NOTYET */


/*
 * NAME:	extHपूर्णांक()
 *
 * FUNCTION:	produce an extent allocation hपूर्णांक क्रम a file offset.
 *
 * PARAMETERS:
 *	ip	- the inode of the file.
 *	offset  - file offset क्रम which the hपूर्णांक is needed.
 *	xp	- poपूर्णांकer to the xad that is to be filled in with
 *		  the hपूर्णांक.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 */
पूर्णांक extHपूर्णांक(काष्ठा inode *ip, s64 offset, xad_t * xp)
अणु
	काष्ठा super_block *sb = ip->i_sb;
	पूर्णांक nbperpage = JFS_SBI(sb)->nbperpage;
	s64 prev;
	पूर्णांक rc = 0;
	s64 xaddr;
	पूर्णांक xlen;
	पूर्णांक xflag;

	/* init the hपूर्णांक as "no hint provided" */
	XADaddress(xp, 0);

	/* determine the starting extent offset of the page previous
	 * to the page containing the offset.
	 */
	prev = ((offset & ~POFFSET) >> JFS_SBI(sb)->l2bsize) - nbperpage;

	/* अगर the offset is in the first page of the file, no hपूर्णांक provided.
	 */
	अगर (prev < 0)
		जाओ out;

	rc = xtLookup(ip, prev, nbperpage, &xflag, &xaddr, &xlen, 0);

	अगर ((rc == 0) && xlen) अणु
		अगर (xlen != nbperpage) अणु
			jfs_error(ip->i_sb, "corrupt xtree\n");
			rc = -EIO;
		पूर्ण
		XADaddress(xp, xaddr);
		XADlength(xp, xlen);
		XADoffset(xp, prev);
		/*
		 * only preserve the abnr flag within the xad flags
		 * of the वापसed hपूर्णांक.
		 */
		xp->flag  = xflag & XAD_NOTRECORDED;
	पूर्ण अन्यथा
		rc = 0;

out:
	वापस (rc);
पूर्ण


/*
 * NAME:	extRecord()
 *
 * FUNCTION:	change a page with a file from not recorded to recorded.
 *
 * PARAMETERS:
 *	ip	- inode of the file.
 *	cp	- cbuf of the file page.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 *	-ENOSPC	- insufficient disk resources.
 */
पूर्णांक extRecord(काष्ठा inode *ip, xad_t * xp)
अणु
	पूर्णांक rc;

	txBeginAnon(ip->i_sb);

	mutex_lock(&JFS_IP(ip)->commit_mutex);

	/* update the extent */
	rc = xtUpdate(0, ip, xp);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	वापस rc;
पूर्ण


#अगर_घोषित _NOTYET
/*
 * NAME:	extFill()
 *
 * FUNCTION:	allocate disk space क्रम a file page that represents
 *		a file hole.
 *
 * PARAMETERS:
 *	ip	- the inode of the file.
 *	cp	- cbuf of the file page represent the hole.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 *	-ENOSPC	- insufficient disk resources.
 */
पूर्णांक extFill(काष्ठा inode *ip, xad_t * xp)
अणु
	पूर्णांक rc, nbperpage = JFS_SBI(ip->i_sb)->nbperpage;
	s64 blkno = offsetXAD(xp) >> ip->i_blkbits;

//	निश्चित(ISSPARSE(ip));

	/* initialize the extent allocation hपूर्णांक */
	XADaddress(xp, 0);

	/* allocate an extent to fill the hole */
	अगर ((rc = extAlloc(ip, nbperpage, blkno, xp, false)))
		वापस (rc);

	निश्चित(lengthPXD(xp) == nbperpage);

	वापस (0);
पूर्ण
#पूर्ण_अगर			/* _NOTYET */


/*
 * NAME:	extBalloc()
 *
 * FUNCTION:	allocate disk blocks to क्रमm an extent.
 *
 *		initially, we will try to allocate disk blocks क्रम the
 *		requested size (nblocks).  अगर this fails (nblocks
 *		contiguous मुक्त blocks not available), we'll try to allocate
 *		a smaller number of blocks (producing a smaller extent), with
 *		this smaller number of blocks consisting of the requested
 *		number of blocks rounded करोwn to the next smaller घातer of 2
 *		number (i.e. 16 -> 8).  we'll जारी to round करोwn and
 *		retry the allocation until the number of blocks to allocate
 *		is smaller than the number of blocks per page.
 *
 * PARAMETERS:
 *	ip	 - the inode of the file.
 *	hपूर्णांक	 - disk block number to be used as an allocation hपूर्णांक.
 *	*nblocks - poपूर्णांकer to an s64 value.  on entry, this value specअगरies
 *		   the desired number of block to be allocated. on successful
 *		   निकास, this value is set to the number of blocks actually
 *		   allocated.
 *	blkno	 - poपूर्णांकer to a block address that is filled in on successful
 *		   वापस with the starting block number of the newly
 *		   allocated block range.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 *	-ENOSPC	- insufficient disk resources.
 */
अटल पूर्णांक
extBalloc(काष्ठा inode *ip, s64 hपूर्णांक, s64 * nblocks, s64 * blkno)
अणु
	काष्ठा jfs_inode_info *ji = JFS_IP(ip);
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	s64 nb, nblks, daddr, max;
	पूर्णांक rc, nbperpage = sbi->nbperpage;
	काष्ठा bmap *bmp = sbi->bmap;
	पूर्णांक ag;

	/* get the number of blocks to initially attempt to allocate.
	 * we'll first try the number of blocks requested unless this
	 * number is greater than the maximum number of contiguous मुक्त
	 * blocks in the map. in that हाल, we'll start off with the
	 * maximum मुक्त.
	 */
	max = (s64) 1 << bmp->db_maxमुक्तbud;
	अगर (*nblocks >= max && *nblocks > nbperpage)
		nb = nblks = (max > nbperpage) ? max : nbperpage;
	अन्यथा
		nb = nblks = *nblocks;

	/* try to allocate blocks */
	जबतक ((rc = dbAlloc(ip, hपूर्णांक, nb, &daddr)) != 0) अणु
		/* अगर something other than an out of space error,
		 * stop and वापस this error.
		 */
		अगर (rc != -ENOSPC)
			वापस (rc);

		/* decrease the allocation request size */
		nb = min(nblks, extRoundDown(nb));

		/* give up अगर we cannot cover a page */
		अगर (nb < nbperpage)
			वापस (rc);
	पूर्ण

	*nblocks = nb;
	*blkno = daddr;

	अगर (S_ISREG(ip->i_mode) && (ji->fileset == खाताSYSTEM_I)) अणु
		ag = BLKTOAG(daddr, sbi);
		spin_lock_irq(&ji->ag_lock);
		अगर (ji->active_ag == -1) अणु
			atomic_inc(&bmp->db_active[ag]);
			ji->active_ag = ag;
		पूर्ण अन्यथा अगर (ji->active_ag != ag) अणु
			atomic_dec(&bmp->db_active[ji->active_ag]);
			atomic_inc(&bmp->db_active[ag]);
			ji->active_ag = ag;
		पूर्ण
		spin_unlock_irq(&ji->ag_lock);
	पूर्ण

	वापस (0);
पूर्ण


#अगर_घोषित _NOTYET
/*
 * NAME:	extBपुनः_स्मृति()
 *
 * FUNCTION:	attempt to extend an extent's allocation.
 *
 *		Initially, we will try to extend the extent's allocation
 *		in place.  If this fails, we'll try to move the extent
 *		to a new set of blocks.  If moving the extent, we initially
 *		will try to allocate disk blocks क्रम the requested size
 *		(newnblks).  अगर this fails (new contiguous मुक्त blocks not
 *		available), we'll try to allocate a smaller number of
 *		blocks (producing a smaller extent), with this smaller
 *		number of blocks consisting of the requested number of
 *		blocks rounded करोwn to the next smaller घातer of 2
 *		number (i.e. 16 -> 8).  We'll जारी to round करोwn and
 *		retry the allocation until the number of blocks to allocate
 *		is smaller than the number of blocks per page.
 *
 * PARAMETERS:
 *	ip	 - the inode of the file.
 *	blkno	 - starting block number of the extents current allocation.
 *	nblks	 - number of blocks within the extents current allocation.
 *	newnblks - poपूर्णांकer to a s64 value.  on entry, this value is the
 *		   new desired extent size (number of blocks).  on
 *		   successful निकास, this value is set to the extent's actual
 *		   new size (new number of blocks).
 *	newblkno - the starting block number of the extents new allocation.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 *	-ENOSPC	- insufficient disk resources.
 */
अटल पूर्णांक
extBपुनः_स्मृति(काष्ठा inode *ip,
	    s64 blkno, s64 nblks, s64 * newnblks, s64 * newblkno)
अणु
	पूर्णांक rc;

	/* try to extend in place */
	अगर ((rc = dbExtend(ip, blkno, nblks, *newnblks - nblks)) == 0) अणु
		*newblkno = blkno;
		वापस (0);
	पूर्ण अन्यथा अणु
		अगर (rc != -ENOSPC)
			वापस (rc);
	पूर्ण

	/* in place extension not possible.
	 * try to move the extent to a new set of blocks.
	 */
	वापस (extBalloc(ip, blkno, newnblks, newblkno));
पूर्ण
#पूर्ण_अगर			/* _NOTYET */


/*
 * NAME:	extRoundDown()
 *
 * FUNCTION:	round करोwn a specअगरied number of blocks to the next
 *		smallest घातer of 2 number.
 *
 * PARAMETERS:
 *	nb	- the inode of the file.
 *
 * RETURN VALUES:
 *	next smallest घातer of 2 number.
 */
अटल s64 extRoundDown(s64 nb)
अणु
	पूर्णांक i;
	u64 m, k;

	क्रम (i = 0, m = (u64) 1 << 63; i < 64; i++, m >>= 1) अणु
		अगर (m & nb)
			अवरोध;
	पूर्ण

	i = 63 - i;
	k = (u64) 1 << i;
	k = ((k - 1) & nb) ? k : k >> 1;

	वापस (k);
पूर्ण
