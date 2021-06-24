<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 *   Portions Copyright (C) Tino Reiअक्षरdt, 2012
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_imap.h"
#समावेश "jfs_lock.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_debug.h"
#समावेश "jfs_discard.h"

/*
 *	SERIALIZATION of the Block Allocation Map.
 *
 *	the working state of the block allocation map is accessed in
 *	two directions:
 *
 *	1) allocation and मुक्त requests that start at the dmap
 *	   level and move up through the dmap control pages (i.e.
 *	   the vast majority of requests).
 *
 *	2) allocation requests that start at dmap control page
 *	   level and work करोwn towards the dmaps.
 *
 *	the serialization scheme used here is as follows.
 *
 *	requests which start at the bottom are serialized against each
 *	other through buffers and each requests holds onto its buffers
 *	as it works it way up from a single dmap to the required level
 *	of dmap control page.
 *	requests that start at the top are serialized against each other
 *	and request that start from the bottom by the multiple पढ़ो/single
 *	ग_लिखो inode lock of the bmap inode. requests starting at the top
 *	take this lock in ग_लिखो mode जबतक request starting at the bottom
 *	take the lock in पढ़ो mode.  a single top-करोwn request may proceed
 *	exclusively जबतक multiple bottoms-up requests may proceed
 *	simultaneously (under the protection of busy buffers).
 *
 *	in addition to inक्रमmation found in dmaps and dmap control pages,
 *	the working state of the block allocation map also includes पढ़ो/
 *	ग_लिखो inक्रमmation मुख्यtained in the bmap descriptor (i.e. total
 *	मुक्त block count, allocation group level मुक्त block counts).
 *	a single exclusive lock (BMAP_LOCK) is used to guard this inक्रमmation
 *	in the face of multiple-bottoms up requests.
 *	(lock ordering: IREAD_LOCK, BMAP_LOCK);
 *
 *	accesses to the persistent state of the block allocation map (limited
 *	to the persistent biपंचांगaps in dmaps) is guarded by (busy) buffers.
 */

#घोषणा BMAP_LOCK_INIT(bmp)	mutex_init(&bmp->db_bmaplock)
#घोषणा BMAP_LOCK(bmp)		mutex_lock(&bmp->db_bmaplock)
#घोषणा BMAP_UNLOCK(bmp)	mutex_unlock(&bmp->db_bmaplock)

/*
 * क्रमward references
 */
अटल व्योम dbAllocBits(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
			पूर्णांक nblocks);
अटल व्योम dbSplit(dmtree_t * tp, पूर्णांक leafno, पूर्णांक splitsz, पूर्णांक newval);
अटल पूर्णांक dbBackSplit(dmtree_t * tp, पूर्णांक leafno);
अटल पूर्णांक dbJoin(dmtree_t * tp, पूर्णांक leafno, पूर्णांक newval);
अटल व्योम dbAdjTree(dmtree_t * tp, पूर्णांक leafno, पूर्णांक newval);
अटल पूर्णांक dbAdjCtl(काष्ठा bmap * bmp, s64 blkno, पूर्णांक newval, पूर्णांक alloc,
		    पूर्णांक level);
अटल पूर्णांक dbAllocAny(काष्ठा bmap * bmp, s64 nblocks, पूर्णांक l2nb, s64 * results);
अटल पूर्णांक dbAllocNext(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
		       पूर्णांक nblocks);
अटल पूर्णांक dbAllocNear(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
		       पूर्णांक nblocks,
		       पूर्णांक l2nb, s64 * results);
अटल पूर्णांक dbAllocDmap(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
		       पूर्णांक nblocks);
अटल पूर्णांक dbAllocDmapLev(काष्ठा bmap * bmp, काष्ठा dmap * dp, पूर्णांक nblocks,
			  पूर्णांक l2nb,
			  s64 * results);
अटल पूर्णांक dbAllocAG(काष्ठा bmap * bmp, पूर्णांक agno, s64 nblocks, पूर्णांक l2nb,
		     s64 * results);
अटल पूर्णांक dbAllocCtl(काष्ठा bmap * bmp, s64 nblocks, पूर्णांक l2nb, s64 blkno,
		      s64 * results);
अटल पूर्णांक dbExtend(काष्ठा inode *ip, s64 blkno, s64 nblocks, s64 addnblocks);
अटल पूर्णांक dbFindBits(u32 word, पूर्णांक l2nb);
अटल पूर्णांक dbFindCtl(काष्ठा bmap * bmp, पूर्णांक l2nb, पूर्णांक level, s64 * blkno);
अटल पूर्णांक dbFindLeaf(dmtree_t * tp, पूर्णांक l2nb, पूर्णांक *leafidx);
अटल पूर्णांक dbFreeBits(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
		      पूर्णांक nblocks);
अटल पूर्णांक dbFreeDmap(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
		      पूर्णांक nblocks);
अटल पूर्णांक dbMaxBud(u8 * cp);
अटल पूर्णांक blkstol2(s64 nb);

अटल पूर्णांक cntlz(u32 value);
अटल पूर्णांक cnttz(u32 word);

अटल पूर्णांक dbAllocDmapBU(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
			 पूर्णांक nblocks);
अटल पूर्णांक dbInitDmap(काष्ठा dmap * dp, s64 blkno, पूर्णांक nblocks);
अटल पूर्णांक dbInitDmapTree(काष्ठा dmap * dp);
अटल पूर्णांक dbInitTree(काष्ठा dmaptree * dtp);
अटल पूर्णांक dbInitDmapCtl(काष्ठा dmapctl * dcp, पूर्णांक level, पूर्णांक i);
अटल पूर्णांक dbGetL2AGSize(s64 nblocks);

/*
 *	buddy table
 *
 * table used क्रम determining buddy sizes within अक्षरacters of
 * dmap biपंचांगap words.  the अक्षरacters themselves serve as indexes
 * पूर्णांकo the table, with the table elements yielding the maximum
 * binary buddy of मुक्त bits within the अक्षरacter.
 */
अटल स्थिर s8 budtab[256] = अणु
	3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, -1
पूर्ण;

/*
 * NAME:	dbMount()
 *
 * FUNCTION:	initializate the block allocation map.
 *
 *		memory is allocated क्रम the in-core bmap descriptor and
 *		the in-core descriptor is initialized from disk.
 *
 * PARAMETERS:
 *	ipbmap	- poपूर्णांकer to in-core inode क्रम the block map.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOMEM	- insufficient memory
 *	-EIO	- i/o error
 */
पूर्णांक dbMount(काष्ठा inode *ipbmap)
अणु
	काष्ठा bmap *bmp;
	काष्ठा dbmap_disk *dbmp_le;
	काष्ठा metapage *mp;
	पूर्णांक i;

	/*
	 * allocate/initialize the in-memory bmap descriptor
	 */
	/* allocate memory क्रम the in-memory bmap descriptor */
	bmp = kदो_स्मृति(माप(काष्ठा bmap), GFP_KERNEL);
	अगर (bmp == शून्य)
		वापस -ENOMEM;

	/* पढ़ो the on-disk bmap descriptor. */
	mp = पढ़ो_metapage(ipbmap,
			   BMAPBLKNO << JFS_SBI(ipbmap->i_sb)->l2nbperpage,
			   PSIZE, 0);
	अगर (mp == शून्य) अणु
		kमुक्त(bmp);
		वापस -EIO;
	पूर्ण

	/* copy the on-disk bmap descriptor to its in-memory version. */
	dbmp_le = (काष्ठा dbmap_disk *) mp->data;
	bmp->db_mapsize = le64_to_cpu(dbmp_le->dn_mapsize);
	bmp->db_nमुक्त = le64_to_cpu(dbmp_le->dn_nमुक्त);
	bmp->db_l2nbperpage = le32_to_cpu(dbmp_le->dn_l2nbperpage);
	bmp->db_numag = le32_to_cpu(dbmp_le->dn_numag);
	bmp->db_maxlevel = le32_to_cpu(dbmp_le->dn_maxlevel);
	bmp->db_maxag = le32_to_cpu(dbmp_le->dn_maxag);
	bmp->db_agpref = le32_to_cpu(dbmp_le->dn_agpref);
	bmp->db_aglevel = le32_to_cpu(dbmp_le->dn_aglevel);
	bmp->db_agheight = le32_to_cpu(dbmp_le->dn_agheight);
	bmp->db_agwidth = le32_to_cpu(dbmp_le->dn_agwidth);
	bmp->db_agstart = le32_to_cpu(dbmp_le->dn_agstart);
	bmp->db_agl2size = le32_to_cpu(dbmp_le->dn_agl2size);
	क्रम (i = 0; i < MAXAG; i++)
		bmp->db_agमुक्त[i] = le64_to_cpu(dbmp_le->dn_agमुक्त[i]);
	bmp->db_agsize = le64_to_cpu(dbmp_le->dn_agsize);
	bmp->db_maxमुक्तbud = dbmp_le->dn_maxमुक्तbud;

	/* release the buffer. */
	release_metapage(mp);

	/* bind the bmap inode and the bmap descriptor to each other. */
	bmp->db_ipbmap = ipbmap;
	JFS_SBI(ipbmap->i_sb)->bmap = bmp;

	स_रखो(bmp->db_active, 0, माप(bmp->db_active));

	/*
	 * allocate/initialize the bmap lock
	 */
	BMAP_LOCK_INIT(bmp);

	वापस (0);
पूर्ण


/*
 * NAME:	dbUnmount()
 *
 * FUNCTION:	terminate the block allocation map in preparation क्रम
 *		file प्रणाली unmount.
 *
 *		the in-core bmap descriptor is written to disk and
 *		the memory क्रम this descriptor is मुक्तd.
 *
 * PARAMETERS:
 *	ipbmap	- poपूर्णांकer to in-core inode क्रम the block map.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error
 */
पूर्णांक dbUnmount(काष्ठा inode *ipbmap, पूर्णांक mounterror)
अणु
	काष्ठा bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;

	अगर (!(mounterror || isReadOnly(ipbmap)))
		dbSync(ipbmap);

	/*
	 * Invalidate the page cache buffers
	 */
	truncate_inode_pages(ipbmap->i_mapping, 0);

	/* मुक्त the memory क्रम the in-memory bmap. */
	kमुक्त(bmp);

	वापस (0);
पूर्ण

/*
 *	dbSync()
 */
पूर्णांक dbSync(काष्ठा inode *ipbmap)
अणु
	काष्ठा dbmap_disk *dbmp_le;
	काष्ठा bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;
	काष्ठा metapage *mp;
	पूर्णांक i;

	/*
	 * ग_लिखो bmap global control page
	 */
	/* get the buffer क्रम the on-disk bmap descriptor. */
	mp = पढ़ो_metapage(ipbmap,
			   BMAPBLKNO << JFS_SBI(ipbmap->i_sb)->l2nbperpage,
			   PSIZE, 0);
	अगर (mp == शून्य) अणु
		jfs_err("dbSync: read_metapage failed!");
		वापस -EIO;
	पूर्ण
	/* copy the in-memory version of the bmap to the on-disk version */
	dbmp_le = (काष्ठा dbmap_disk *) mp->data;
	dbmp_le->dn_mapsize = cpu_to_le64(bmp->db_mapsize);
	dbmp_le->dn_nमुक्त = cpu_to_le64(bmp->db_nमुक्त);
	dbmp_le->dn_l2nbperpage = cpu_to_le32(bmp->db_l2nbperpage);
	dbmp_le->dn_numag = cpu_to_le32(bmp->db_numag);
	dbmp_le->dn_maxlevel = cpu_to_le32(bmp->db_maxlevel);
	dbmp_le->dn_maxag = cpu_to_le32(bmp->db_maxag);
	dbmp_le->dn_agpref = cpu_to_le32(bmp->db_agpref);
	dbmp_le->dn_aglevel = cpu_to_le32(bmp->db_aglevel);
	dbmp_le->dn_agheight = cpu_to_le32(bmp->db_agheight);
	dbmp_le->dn_agwidth = cpu_to_le32(bmp->db_agwidth);
	dbmp_le->dn_agstart = cpu_to_le32(bmp->db_agstart);
	dbmp_le->dn_agl2size = cpu_to_le32(bmp->db_agl2size);
	क्रम (i = 0; i < MAXAG; i++)
		dbmp_le->dn_agमुक्त[i] = cpu_to_le64(bmp->db_agमुक्त[i]);
	dbmp_le->dn_agsize = cpu_to_le64(bmp->db_agsize);
	dbmp_le->dn_maxमुक्तbud = bmp->db_maxमुक्तbud;

	/* ग_लिखो the buffer */
	ग_लिखो_metapage(mp);

	/*
	 * ग_लिखो out dirty pages of bmap
	 */
	filemap_ग_लिखो_and_रुको(ipbmap->i_mapping);

	diWriteSpecial(ipbmap, 0);

	वापस (0);
पूर्ण

/*
 * NAME:	dbFree()
 *
 * FUNCTION:	मुक्त the specअगरied block range from the working block
 *		allocation map.
 *
 *		the blocks will be मुक्त from the working map one dmap
 *		at a समय.
 *
 * PARAMETERS:
 *	ip	- poपूर्णांकer to in-core inode;
 *	blkno	- starting block number to be मुक्तd.
 *	nblocks	- number of blocks to be मुक्तd.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error
 */
पूर्णांक dbFree(काष्ठा inode *ip, s64 blkno, s64 nblocks)
अणु
	काष्ठा metapage *mp;
	काष्ठा dmap *dp;
	पूर्णांक nb, rc;
	s64 lblkno, rem;
	काष्ठा inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	काष्ठा bmap *bmp = JFS_SBI(ip->i_sb)->bmap;
	काष्ठा super_block *sb = ipbmap->i_sb;

	IREAD_LOCK(ipbmap, RDWRLOCK_DMAP);

	/* block to be मुक्तd better be within the mapsize. */
	अगर (unlikely((blkno == 0) || (blkno + nblocks > bmp->db_mapsize))) अणु
		IREAD_UNLOCK(ipbmap);
		prपूर्णांकk(KERN_ERR "blkno = %Lx, nblocks = %Lx\n",
		       (अचिन्हित दीर्घ दीर्घ) blkno,
		       (अचिन्हित दीर्घ दीर्घ) nblocks);
		jfs_error(ip->i_sb, "block to be freed is outside the map\n");
		वापस -EIO;
	पूर्ण

	/**
	 * TRIM the blocks, when mounted with discard option
	 */
	अगर (JFS_SBI(sb)->flag & JFS_DISCARD)
		अगर (JFS_SBI(sb)->minblks_trim <= nblocks)
			jfs_issue_discard(ipbmap, blkno, nblocks);

	/*
	 * मुक्त the blocks a dmap at a समय.
	 */
	mp = शून्य;
	क्रम (rem = nblocks; rem > 0; rem -= nb, blkno += nb) अणु
		/* release previous dmap अगर any */
		अगर (mp) अणु
			ग_लिखो_metapage(mp);
		पूर्ण

		/* get the buffer क्रम the current dmap. */
		lblkno = BLKTODMAP(blkno, bmp->db_l2nbperpage);
		mp = पढ़ो_metapage(ipbmap, lblkno, PSIZE, 0);
		अगर (mp == शून्य) अणु
			IREAD_UNLOCK(ipbmap);
			वापस -EIO;
		पूर्ण
		dp = (काष्ठा dmap *) mp->data;

		/* determine the number of blocks to be मुक्तd from
		 * this dmap.
		 */
		nb = min(rem, BPERDMAP - (blkno & (BPERDMAP - 1)));

		/* मुक्त the blocks. */
		अगर ((rc = dbFreeDmap(bmp, dp, blkno, nb))) अणु
			jfs_error(ip->i_sb, "error in block map\n");
			release_metapage(mp);
			IREAD_UNLOCK(ipbmap);
			वापस (rc);
		पूर्ण
	पूर्ण

	/* ग_लिखो the last buffer. */
	ग_लिखो_metapage(mp);

	IREAD_UNLOCK(ipbmap);

	वापस (0);
पूर्ण


/*
 * NAME:	dbUpdatePMap()
 *
 * FUNCTION:	update the allocation state (मुक्त or allocate) of the
 *		specअगरied block range in the persistent block allocation map.
 *
 *		the blocks will be updated in the persistent map one
 *		dmap at a समय.
 *
 * PARAMETERS:
 *	ipbmap	- poपूर्णांकer to in-core inode क्रम the block map.
 *	मुक्त	- 'true' अगर block range is to be मुक्तd from the persistent
 *		  map; 'false' अगर it is to be allocated.
 *	blkno	- starting block number of the range.
 *	nblocks	- number of contiguous blocks in the range.
 *	tblk	- transaction block;
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error
 */
पूर्णांक
dbUpdatePMap(काष्ठा inode *ipbmap,
	     पूर्णांक मुक्त, s64 blkno, s64 nblocks, काष्ठा tblock * tblk)
अणु
	पूर्णांक nblks, dbitno, wbitno, rbits;
	पूर्णांक word, nbits, nwords;
	काष्ठा bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;
	s64 lblkno, rem, lastlblkno;
	u32 mask;
	काष्ठा dmap *dp;
	काष्ठा metapage *mp;
	काष्ठा jfs_log *log;
	पूर्णांक lsn, dअगरft, dअगरfp;
	अचिन्हित दीर्घ flags;

	/* the blocks better be within the mapsize. */
	अगर (blkno + nblocks > bmp->db_mapsize) अणु
		prपूर्णांकk(KERN_ERR "blkno = %Lx, nblocks = %Lx\n",
		       (अचिन्हित दीर्घ दीर्घ) blkno,
		       (अचिन्हित दीर्घ दीर्घ) nblocks);
		jfs_error(ipbmap->i_sb, "blocks are outside the map\n");
		वापस -EIO;
	पूर्ण

	/* compute delta of transaction lsn from log syncpt */
	lsn = tblk->lsn;
	log = (काष्ठा jfs_log *) JFS_SBI(tblk->sb)->log;
	logdअगरf(dअगरft, lsn, log);

	/*
	 * update the block state a dmap at a समय.
	 */
	mp = शून्य;
	lastlblkno = 0;
	क्रम (rem = nblocks; rem > 0; rem -= nblks, blkno += nblks) अणु
		/* get the buffer क्रम the current dmap. */
		lblkno = BLKTODMAP(blkno, bmp->db_l2nbperpage);
		अगर (lblkno != lastlblkno) अणु
			अगर (mp) अणु
				ग_लिखो_metapage(mp);
			पूर्ण

			mp = पढ़ो_metapage(bmp->db_ipbmap, lblkno, PSIZE,
					   0);
			अगर (mp == शून्य)
				वापस -EIO;
			metapage_रुको_क्रम_io(mp);
		पूर्ण
		dp = (काष्ठा dmap *) mp->data;

		/* determine the bit number and word within the dmap of
		 * the starting block.  also determine how many blocks
		 * are to be updated within this dmap.
		 */
		dbitno = blkno & (BPERDMAP - 1);
		word = dbitno >> L2DBWORD;
		nblks = min(rem, (s64)BPERDMAP - dbitno);

		/* update the bits of the dmap words. the first and last
		 * words may only have a subset of their bits updated. अगर
		 * this is the हाल, we'll work against that word (i.e.
		 * partial first and/or last) only in a single pass.  a
		 * single pass will also be used to update all words that
		 * are to have all their bits updated.
		 */
		क्रम (rbits = nblks; rbits > 0;
		     rbits -= nbits, dbitno += nbits) अणु
			/* determine the bit number within the word and
			 * the number of bits within the word.
			 */
			wbitno = dbitno & (DBWORD - 1);
			nbits = min(rbits, DBWORD - wbitno);

			/* check अगर only part of the word is to be updated. */
			अगर (nbits < DBWORD) अणु
				/* update (मुक्त or allocate) the bits
				 * in this word.
				 */
				mask =
				    (ONES << (DBWORD - nbits) >> wbitno);
				अगर (मुक्त)
					dp->pmap[word] &=
					    cpu_to_le32(~mask);
				अन्यथा
					dp->pmap[word] |=
					    cpu_to_le32(mask);

				word += 1;
			पूर्ण अन्यथा अणु
				/* one or more words are to have all
				 * their bits updated.  determine how
				 * many words and how many bits.
				 */
				nwords = rbits >> L2DBWORD;
				nbits = nwords << L2DBWORD;

				/* update (मुक्त or allocate) the bits
				 * in these words.
				 */
				अगर (मुक्त)
					स_रखो(&dp->pmap[word], 0,
					       nwords * 4);
				अन्यथा
					स_रखो(&dp->pmap[word], (पूर्णांक) ONES,
					       nwords * 4);

				word += nwords;
			पूर्ण
		पूर्ण

		/*
		 * update dmap lsn
		 */
		अगर (lblkno == lastlblkno)
			जारी;

		lastlblkno = lblkno;

		LOGSYNC_LOCK(log, flags);
		अगर (mp->lsn != 0) अणु
			/* inherit older/smaller lsn */
			logdअगरf(dअगरfp, mp->lsn, log);
			अगर (dअगरft < dअगरfp) अणु
				mp->lsn = lsn;

				/* move bp after tblock in logsync list */
				list_move(&mp->synclist, &tblk->synclist);
			पूर्ण

			/* inherit younger/larger clsn */
			logdअगरf(dअगरft, tblk->clsn, log);
			logdअगरf(dअगरfp, mp->clsn, log);
			अगर (dअगरft > dअगरfp)
				mp->clsn = tblk->clsn;
		पूर्ण अन्यथा अणु
			mp->log = log;
			mp->lsn = lsn;

			/* insert bp after tblock in logsync list */
			log->count++;
			list_add(&mp->synclist, &tblk->synclist);

			mp->clsn = tblk->clsn;
		पूर्ण
		LOGSYNC_UNLOCK(log, flags);
	पूर्ण

	/* ग_लिखो the last buffer. */
	अगर (mp) अणु
		ग_लिखो_metapage(mp);
	पूर्ण

	वापस (0);
पूर्ण


/*
 * NAME:	dbNextAG()
 *
 * FUNCTION:	find the preferred allocation group क्रम new allocations.
 *
 *		Within the allocation groups, we मुख्यtain a preferred
 *		allocation group which consists of a group with at least
 *		average मुक्त space.  It is the preferred group that we target
 *		new inode allocation towards.  The tie-in between inode
 *		allocation and block allocation occurs as we allocate the
 *		first (data) block of an inode and specअगरy the inode (block)
 *		as the allocation hपूर्णांक क्रम this block.
 *
 *		We try to aव्योम having more than one खोलो file growing in
 *		an allocation group, as this will lead to fragmentation.
 *		This dअगरfers from the old OS/2 method of trying to keep
 *		empty ags around क्रम large allocations.
 *
 * PARAMETERS:
 *	ipbmap	- poपूर्णांकer to in-core inode क्रम the block map.
 *
 * RETURN VALUES:
 *	the preferred allocation group number.
 */
पूर्णांक dbNextAG(काष्ठा inode *ipbmap)
अणु
	s64 avgमुक्त;
	पूर्णांक agpref;
	s64 hwm = 0;
	पूर्णांक i;
	पूर्णांक next_best = -1;
	काष्ठा bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;

	BMAP_LOCK(bmp);

	/* determine the average number of मुक्त blocks within the ags. */
	avgमुक्त = (u32)bmp->db_nमुक्त / bmp->db_numag;

	/*
	 * अगर the current preferred ag करोes not have an active allocator
	 * and has at least average मुक्तspace, वापस it
	 */
	agpref = bmp->db_agpref;
	अगर ((atomic_पढ़ो(&bmp->db_active[agpref]) == 0) &&
	    (bmp->db_agमुक्त[agpref] >= avgमुक्त))
		जाओ unlock;

	/* From the last preferred ag, find the next one with at least
	 * average मुक्त space.
	 */
	क्रम (i = 0 ; i < bmp->db_numag; i++, agpref++) अणु
		अगर (agpref == bmp->db_numag)
			agpref = 0;

		अगर (atomic_पढ़ो(&bmp->db_active[agpref]))
			/* खोलो file is currently growing in this ag */
			जारी;
		अगर (bmp->db_agमुक्त[agpref] >= avgमुक्त) अणु
			/* Return this one */
			bmp->db_agpref = agpref;
			जाओ unlock;
		पूर्ण अन्यथा अगर (bmp->db_agमुक्त[agpref] > hwm) अणु
			/* Less than avg. मुक्तspace, but best so far */
			hwm = bmp->db_agमुक्त[agpref];
			next_best = agpref;
		पूर्ण
	पूर्ण

	/*
	 * If no inactive ag was found with average मुक्तspace, use the
	 * next best
	 */
	अगर (next_best != -1)
		bmp->db_agpref = next_best;
	/* अन्यथा leave db_agpref unchanged */
unlock:
	BMAP_UNLOCK(bmp);

	/* वापस the preferred group.
	 */
	वापस (bmp->db_agpref);
पूर्ण

/*
 * NAME:	dbAlloc()
 *
 * FUNCTION:	attempt to allocate a specअगरied number of contiguous मुक्त
 *		blocks from the working allocation block map.
 *
 *		the block allocation policy uses hपूर्णांकs and a multi-step
 *		approach.
 *
 *		क्रम allocation requests smaller than the number of blocks
 *		per dmap, we first try to allocate the new blocks
 *		immediately following the hपूर्णांक.  अगर these blocks are not
 *		available, we try to allocate blocks near the hपूर्णांक.  अगर
 *		no blocks near the hपूर्णांक are available, we next try to
 *		allocate within the same dmap as contains the hपूर्णांक.
 *
 *		अगर no blocks are available in the dmap or the allocation
 *		request is larger than the dmap size, we try to allocate
 *		within the same allocation group as contains the hपूर्णांक. अगर
 *		this करोes not succeed, we finally try to allocate anywhere
 *		within the aggregate.
 *
 *		we also try to allocate anywhere within the aggregate
 *		क्रम allocation requests larger than the allocation group
 *		size or requests that specअगरy no hपूर्णांक value.
 *
 * PARAMETERS:
 *	ip	- poपूर्णांकer to in-core inode;
 *	hपूर्णांक	- allocation hपूर्णांक.
 *	nblocks	- number of contiguous blocks in the range.
 *	results	- on successful वापस, set to the starting block number
 *		  of the newly allocated contiguous range.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 */
पूर्णांक dbAlloc(काष्ठा inode *ip, s64 hपूर्णांक, s64 nblocks, s64 * results)
अणु
	पूर्णांक rc, agno;
	काष्ठा inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	काष्ठा bmap *bmp;
	काष्ठा metapage *mp;
	s64 lblkno, blkno;
	काष्ठा dmap *dp;
	पूर्णांक l2nb;
	s64 mapSize;
	पूर्णांक ग_लिखोrs;

	/* निश्चित that nblocks is valid */
	निश्चित(nblocks > 0);

	/* get the log2 number of blocks to be allocated.
	 * अगर the number of blocks is not a log2 multiple,
	 * it will be rounded up to the next log2 multiple.
	 */
	l2nb = BLKSTOL2(nblocks);

	bmp = JFS_SBI(ip->i_sb)->bmap;

	mapSize = bmp->db_mapsize;

	/* the hपूर्णांक should be within the map */
	अगर (hपूर्णांक >= mapSize) अणु
		jfs_error(ip->i_sb, "the hint is outside the map\n");
		वापस -EIO;
	पूर्ण

	/* अगर the number of blocks to be allocated is greater than the
	 * allocation group size, try to allocate anywhere.
	 */
	अगर (l2nb > bmp->db_agl2size) अणु
		IWRITE_LOCK(ipbmap, RDWRLOCK_DMAP);

		rc = dbAllocAny(bmp, nblocks, l2nb, results);

		जाओ ग_लिखो_unlock;
	पूर्ण

	/*
	 * If no hपूर्णांक, let dbNextAG recommend an allocation group
	 */
	अगर (hपूर्णांक == 0)
		जाओ pref_ag;

	/* we would like to allocate बंद to the hपूर्णांक.  adjust the
	 * hपूर्णांक to the block following the hपूर्णांक since the allocators
	 * will start looking क्रम मुक्त space starting at this poपूर्णांक.
	 */
	blkno = hपूर्णांक + 1;

	अगर (blkno >= bmp->db_mapsize)
		जाओ pref_ag;

	agno = blkno >> bmp->db_agl2size;

	/* check अगर blkno crosses over पूर्णांकo a new allocation group.
	 * अगर so, check अगर we should allow allocations within this
	 * allocation group.
	 */
	अगर ((blkno & (bmp->db_agsize - 1)) == 0)
		/* check अगर the AG is currently being written to.
		 * अगर so, call dbNextAG() to find a non-busy
		 * AG with sufficient मुक्त space.
		 */
		अगर (atomic_पढ़ो(&bmp->db_active[agno]))
			जाओ pref_ag;

	/* check अगर the allocation request size can be satisfied from a
	 * single dmap.  अगर so, try to allocate from the dmap containing
	 * the hपूर्णांक using a tiered strategy.
	 */
	अगर (nblocks <= BPERDMAP) अणु
		IREAD_LOCK(ipbmap, RDWRLOCK_DMAP);

		/* get the buffer क्रम the dmap containing the hपूर्णांक.
		 */
		rc = -EIO;
		lblkno = BLKTODMAP(blkno, bmp->db_l2nbperpage);
		mp = पढ़ो_metapage(ipbmap, lblkno, PSIZE, 0);
		अगर (mp == शून्य)
			जाओ पढ़ो_unlock;

		dp = (काष्ठा dmap *) mp->data;

		/* first, try to satisfy the allocation request with the
		 * blocks beginning at the hपूर्णांक.
		 */
		अगर ((rc = dbAllocNext(bmp, dp, blkno, (पूर्णांक) nblocks))
		    != -ENOSPC) अणु
			अगर (rc == 0) अणु
				*results = blkno;
				mark_metapage_dirty(mp);
			पूर्ण

			release_metapage(mp);
			जाओ पढ़ो_unlock;
		पूर्ण

		ग_लिखोrs = atomic_पढ़ो(&bmp->db_active[agno]);
		अगर ((ग_लिखोrs > 1) ||
		    ((ग_लिखोrs == 1) && (JFS_IP(ip)->active_ag != agno))) अणु
			/*
			 * Someone अन्यथा is writing in this allocation
			 * group.  To aव्योम fragmenting, try another ag
			 */
			release_metapage(mp);
			IREAD_UNLOCK(ipbmap);
			जाओ pref_ag;
		पूर्ण

		/* next, try to satisfy the allocation request with blocks
		 * near the hपूर्णांक.
		 */
		अगर ((rc =
		     dbAllocNear(bmp, dp, blkno, (पूर्णांक) nblocks, l2nb, results))
		    != -ENOSPC) अणु
			अगर (rc == 0)
				mark_metapage_dirty(mp);

			release_metapage(mp);
			जाओ पढ़ो_unlock;
		पूर्ण

		/* try to satisfy the allocation request with blocks within
		 * the same dmap as the hपूर्णांक.
		 */
		अगर ((rc = dbAllocDmapLev(bmp, dp, (पूर्णांक) nblocks, l2nb, results))
		    != -ENOSPC) अणु
			अगर (rc == 0)
				mark_metapage_dirty(mp);

			release_metapage(mp);
			जाओ पढ़ो_unlock;
		पूर्ण

		release_metapage(mp);
		IREAD_UNLOCK(ipbmap);
	पूर्ण

	/* try to satisfy the allocation request with blocks within
	 * the same allocation group as the hपूर्णांक.
	 */
	IWRITE_LOCK(ipbmap, RDWRLOCK_DMAP);
	अगर ((rc = dbAllocAG(bmp, agno, nblocks, l2nb, results)) != -ENOSPC)
		जाओ ग_लिखो_unlock;

	IWRITE_UNLOCK(ipbmap);


      pref_ag:
	/*
	 * Let dbNextAG recommend a preferred allocation group
	 */
	agno = dbNextAG(ipbmap);
	IWRITE_LOCK(ipbmap, RDWRLOCK_DMAP);

	/* Try to allocate within this allocation group.  अगर that fails, try to
	 * allocate anywhere in the map.
	 */
	अगर ((rc = dbAllocAG(bmp, agno, nblocks, l2nb, results)) == -ENOSPC)
		rc = dbAllocAny(bmp, nblocks, l2nb, results);

      ग_लिखो_unlock:
	IWRITE_UNLOCK(ipbmap);

	वापस (rc);

      पढ़ो_unlock:
	IREAD_UNLOCK(ipbmap);

	वापस (rc);
पूर्ण

#अगर_घोषित _NOTYET
/*
 * NAME:	dbAllocExact()
 *
 * FUNCTION:	try to allocate the requested extent;
 *
 * PARAMETERS:
 *	ip	- poपूर्णांकer to in-core inode;
 *	blkno	- extent address;
 *	nblocks	- extent length;
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 */
पूर्णांक dbAllocExact(काष्ठा inode *ip, s64 blkno, पूर्णांक nblocks)
अणु
	पूर्णांक rc;
	काष्ठा inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	काष्ठा bmap *bmp = JFS_SBI(ip->i_sb)->bmap;
	काष्ठा dmap *dp;
	s64 lblkno;
	काष्ठा metapage *mp;

	IREAD_LOCK(ipbmap, RDWRLOCK_DMAP);

	/*
	 * validate extent request:
	 *
	 * note: defragfs policy:
	 *  max 64 blocks will be moved.
	 *  allocation request size must be satisfied from a single dmap.
	 */
	अगर (nblocks <= 0 || nblocks > BPERDMAP || blkno >= bmp->db_mapsize) अणु
		IREAD_UNLOCK(ipbmap);
		वापस -EINVAL;
	पूर्ण

	अगर (nblocks > ((s64) 1 << bmp->db_maxमुक्तbud)) अणु
		/* the मुक्त space is no दीर्घer available */
		IREAD_UNLOCK(ipbmap);
		वापस -ENOSPC;
	पूर्ण

	/* पढ़ो in the dmap covering the extent */
	lblkno = BLKTODMAP(blkno, bmp->db_l2nbperpage);
	mp = पढ़ो_metapage(ipbmap, lblkno, PSIZE, 0);
	अगर (mp == शून्य) अणु
		IREAD_UNLOCK(ipbmap);
		वापस -EIO;
	पूर्ण
	dp = (काष्ठा dmap *) mp->data;

	/* try to allocate the requested extent */
	rc = dbAllocNext(bmp, dp, blkno, nblocks);

	IREAD_UNLOCK(ipbmap);

	अगर (rc == 0)
		mark_metapage_dirty(mp);

	release_metapage(mp);

	वापस (rc);
पूर्ण
#पूर्ण_अगर /* _NOTYET */

/*
 * NAME:	dbReAlloc()
 *
 * FUNCTION:	attempt to extend a current allocation by a specअगरied
 *		number of blocks.
 *
 *		this routine attempts to satisfy the allocation request
 *		by first trying to extend the existing allocation in
 *		place by allocating the additional blocks as the blocks
 *		immediately following the current allocation.  अगर these
 *		blocks are not available, this routine will attempt to
 *		allocate a new set of contiguous blocks large enough
 *		to cover the existing allocation plus the additional
 *		number of blocks required.
 *
 * PARAMETERS:
 *	ip	    -  poपूर्णांकer to in-core inode requiring allocation.
 *	blkno	    -  starting block of the current allocation.
 *	nblocks	    -  number of contiguous blocks within the current
 *		       allocation.
 *	addnblocks  -  number of blocks to add to the allocation.
 *	results	-      on successful वापस, set to the starting block number
 *		       of the existing allocation अगर the existing allocation
 *		       was extended in place or to a newly allocated contiguous
 *		       range अगर the existing allocation could not be extended
 *		       in place.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 */
पूर्णांक
dbReAlloc(काष्ठा inode *ip,
	  s64 blkno, s64 nblocks, s64 addnblocks, s64 * results)
अणु
	पूर्णांक rc;

	/* try to extend the allocation in place.
	 */
	अगर ((rc = dbExtend(ip, blkno, nblocks, addnblocks)) == 0) अणु
		*results = blkno;
		वापस (0);
	पूर्ण अन्यथा अणु
		अगर (rc != -ENOSPC)
			वापस (rc);
	पूर्ण

	/* could not extend the allocation in place, so allocate a
	 * new set of blocks क्रम the entire request (i.e. try to get
	 * a range of contiguous blocks large enough to cover the
	 * existing allocation plus the additional blocks.)
	 */
	वापस (dbAlloc
		(ip, blkno + nblocks - 1, addnblocks + nblocks, results));
पूर्ण


/*
 * NAME:	dbExtend()
 *
 * FUNCTION:	attempt to extend a current allocation by a specअगरied
 *		number of blocks.
 *
 *		this routine attempts to satisfy the allocation request
 *		by first trying to extend the existing allocation in
 *		place by allocating the additional blocks as the blocks
 *		immediately following the current allocation.
 *
 * PARAMETERS:
 *	ip	    -  poपूर्णांकer to in-core inode requiring allocation.
 *	blkno	    -  starting block of the current allocation.
 *	nblocks	    -  number of contiguous blocks within the current
 *		       allocation.
 *	addnblocks  -  number of blocks to add to the allocation.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 */
अटल पूर्णांक dbExtend(काष्ठा inode *ip, s64 blkno, s64 nblocks, s64 addnblocks)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	s64 lblkno, lastblkno, extblkno;
	uपूर्णांक rel_block;
	काष्ठा metapage *mp;
	काष्ठा dmap *dp;
	पूर्णांक rc;
	काष्ठा inode *ipbmap = sbi->ipbmap;
	काष्ठा bmap *bmp;

	/*
	 * We करोn't want a non-aligned extent to cross a page boundary
	 */
	अगर (((rel_block = blkno & (sbi->nbperpage - 1))) &&
	    (rel_block + nblocks + addnblocks > sbi->nbperpage))
		वापस -ENOSPC;

	/* get the last block of the current allocation */
	lastblkno = blkno + nblocks - 1;

	/* determine the block number of the block following
	 * the existing allocation.
	 */
	extblkno = lastblkno + 1;

	IREAD_LOCK(ipbmap, RDWRLOCK_DMAP);

	/* better be within the file प्रणाली */
	bmp = sbi->bmap;
	अगर (lastblkno < 0 || lastblkno >= bmp->db_mapsize) अणु
		IREAD_UNLOCK(ipbmap);
		jfs_error(ip->i_sb, "the block is outside the filesystem\n");
		वापस -EIO;
	पूर्ण

	/* we'll attempt to extend the current allocation in place by
	 * allocating the additional blocks as the blocks immediately
	 * following the current allocation.  we only try to extend the
	 * current allocation in place अगर the number of additional blocks
	 * can fit पूर्णांकo a dmap, the last block of the current allocation
	 * is not the last block of the file प्रणाली, and the start of the
	 * inplace extension is not on an allocation group boundary.
	 */
	अगर (addnblocks > BPERDMAP || extblkno >= bmp->db_mapsize ||
	    (extblkno & (bmp->db_agsize - 1)) == 0) अणु
		IREAD_UNLOCK(ipbmap);
		वापस -ENOSPC;
	पूर्ण

	/* get the buffer क्रम the dmap containing the first block
	 * of the extension.
	 */
	lblkno = BLKTODMAP(extblkno, bmp->db_l2nbperpage);
	mp = पढ़ो_metapage(ipbmap, lblkno, PSIZE, 0);
	अगर (mp == शून्य) अणु
		IREAD_UNLOCK(ipbmap);
		वापस -EIO;
	पूर्ण

	dp = (काष्ठा dmap *) mp->data;

	/* try to allocate the blocks immediately following the
	 * current allocation.
	 */
	rc = dbAllocNext(bmp, dp, extblkno, (पूर्णांक) addnblocks);

	IREAD_UNLOCK(ipbmap);

	/* were we successful ? */
	अगर (rc == 0)
		ग_लिखो_metapage(mp);
	अन्यथा
		/* we were not successful */
		release_metapage(mp);

	वापस (rc);
पूर्ण


/*
 * NAME:	dbAllocNext()
 *
 * FUNCTION:	attempt to allocate the blocks of the specअगरied block
 *		range within a dmap.
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	dp	-  poपूर्णांकer to dmap.
 *	blkno	-  starting block number of the range.
 *	nblocks	-  number of contiguous मुक्त blocks of the range.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 *
 * serialization: IREAD_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक dbAllocNext(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
		       पूर्णांक nblocks)
अणु
	पूर्णांक dbitno, word, rembits, nb, nwords, wbitno, nw;
	पूर्णांक l2size;
	s8 *leaf;
	u32 mask;

	अगर (dp->tree.leafidx != cpu_to_le32(LEAFIND)) अणु
		jfs_error(bmp->db_ipbmap->i_sb, "Corrupt dmap page\n");
		वापस -EIO;
	पूर्ण

	/* pick up a poपूर्णांकer to the leaves of the dmap tree.
	 */
	leaf = dp->tree.stree + le32_to_cpu(dp->tree.leafidx);

	/* determine the bit number and word within the dmap of the
	 * starting block.
	 */
	dbitno = blkno & (BPERDMAP - 1);
	word = dbitno >> L2DBWORD;

	/* check अगर the specअगरied block range is contained within
	 * this dmap.
	 */
	अगर (dbitno + nblocks > BPERDMAP)
		वापस -ENOSPC;

	/* check अगर the starting leaf indicates that anything
	 * is मुक्त.
	 */
	अगर (leaf[word] == NOFREE)
		वापस -ENOSPC;

	/* check the dmaps words corresponding to block range to see
	 * अगर the block range is मुक्त.  not all bits of the first and
	 * last words may be contained within the block range.  अगर this
	 * is the हाल, we'll work against those words (i.e. partial first
	 * and/or last) on an inभागidual basis (a single pass) and examine
	 * the actual bits to determine अगर they are मुक्त.  a single pass
	 * will be used क्रम all dmap words fully contained within the
	 * specअगरied range.  within this pass, the leaves of the dmap
	 * tree will be examined to determine अगर the blocks are मुक्त. a
	 * single leaf may describe the मुक्त space of multiple dmap
	 * words, so we may visit only a subset of the actual leaves
	 * corresponding to the dmap words of the block range.
	 */
	क्रम (rembits = nblocks; rembits > 0; rembits -= nb, dbitno += nb) अणु
		/* determine the bit number within the word and
		 * the number of bits within the word.
		 */
		wbitno = dbitno & (DBWORD - 1);
		nb = min(rembits, DBWORD - wbitno);

		/* check अगर only part of the word is to be examined.
		 */
		अगर (nb < DBWORD) अणु
			/* check अगर the bits are मुक्त.
			 */
			mask = (ONES << (DBWORD - nb) >> wbitno);
			अगर ((mask & ~le32_to_cpu(dp->wmap[word])) != mask)
				वापस -ENOSPC;

			word += 1;
		पूर्ण अन्यथा अणु
			/* one or more dmap words are fully contained
			 * within the block range.  determine how many
			 * words and how many bits.
			 */
			nwords = rembits >> L2DBWORD;
			nb = nwords << L2DBWORD;

			/* now examine the appropriate leaves to determine
			 * अगर the blocks are मुक्त.
			 */
			जबतक (nwords > 0) अणु
				/* करोes the leaf describe any मुक्त space ?
				 */
				अगर (leaf[word] < BUDMIN)
					वापस -ENOSPC;

				/* determine the l2 number of bits provided
				 * by this leaf.
				 */
				l2size =
				    min_t(पूर्णांक, leaf[word], NLSTOL2BSZ(nwords));

				/* determine how many words were handled.
				 */
				nw = BUDSIZE(l2size, BUDMIN);

				nwords -= nw;
				word += nw;
			पूर्ण
		पूर्ण
	पूर्ण

	/* allocate the blocks.
	 */
	वापस (dbAllocDmap(bmp, dp, blkno, nblocks));
पूर्ण


/*
 * NAME:	dbAllocNear()
 *
 * FUNCTION:	attempt to allocate a number of contiguous मुक्त blocks near
 *		a specअगरied block (hपूर्णांक) within a dmap.
 *
 *		starting with the dmap leaf that covers the hपूर्णांक, we'll
 *		check the next four contiguous leaves क्रम sufficient मुक्त
 *		space.  अगर sufficient मुक्त space is found, we'll allocate
 *		the desired मुक्त space.
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	dp	-  poपूर्णांकer to dmap.
 *	blkno	-  block number to allocate near.
 *	nblocks	-  actual number of contiguous मुक्त blocks desired.
 *	l2nb	-  log2 number of contiguous मुक्त blocks desired.
 *	results	-  on successful वापस, set to the starting block number
 *		   of the newly allocated range.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 *
 * serialization: IREAD_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक
dbAllocNear(काष्ठा bmap * bmp,
	    काष्ठा dmap * dp, s64 blkno, पूर्णांक nblocks, पूर्णांक l2nb, s64 * results)
अणु
	पूर्णांक word, lword, rc;
	s8 *leaf;

	अगर (dp->tree.leafidx != cpu_to_le32(LEAFIND)) अणु
		jfs_error(bmp->db_ipbmap->i_sb, "Corrupt dmap page\n");
		वापस -EIO;
	पूर्ण

	leaf = dp->tree.stree + le32_to_cpu(dp->tree.leafidx);

	/* determine the word within the dmap that holds the hपूर्णांक
	 * (i.e. blkno).  also, determine the last word in the dmap
	 * that we'll include in our examination.
	 */
	word = (blkno & (BPERDMAP - 1)) >> L2DBWORD;
	lword = min(word + 4, LPERDMAP);

	/* examine the leaves क्रम sufficient मुक्त space.
	 */
	क्रम (; word < lword; word++) अणु
		/* करोes the leaf describe sufficient मुक्त space ?
		 */
		अगर (leaf[word] < l2nb)
			जारी;

		/* determine the block number within the file प्रणाली
		 * of the first block described by this dmap word.
		 */
		blkno = le64_to_cpu(dp->start) + (word << L2DBWORD);

		/* अगर not all bits of the dmap word are मुक्त, get the
		 * starting bit number within the dmap word of the required
		 * string of मुक्त bits and adjust the block number with the
		 * value.
		 */
		अगर (leaf[word] < BUDMIN)
			blkno +=
			    dbFindBits(le32_to_cpu(dp->wmap[word]), l2nb);

		/* allocate the blocks.
		 */
		अगर ((rc = dbAllocDmap(bmp, dp, blkno, nblocks)) == 0)
			*results = blkno;

		वापस (rc);
	पूर्ण

	वापस -ENOSPC;
पूर्ण


/*
 * NAME:	dbAllocAG()
 *
 * FUNCTION:	attempt to allocate the specअगरied number of contiguous
 *		मुक्त blocks within the specअगरied allocation group.
 *
 *		unless the allocation group size is equal to the number
 *		of blocks per dmap, the dmap control pages will be used to
 *		find the required मुक्त space, अगर available.  we start the
 *		search at the highest dmap control page level which
 *		distinctly describes the allocation group's मुक्त space
 *		(i.e. the highest level at which the allocation group's
 *		मुक्त space is not mixed in with that of any other group).
 *		in addition, we start the search within this level at a
 *		height of the dmapctl dmtree at which the nodes distinctly
 *		describe the allocation group's मुक्त space.  at this height,
 *		the allocation group's मुक्त space may be represented by 1
 *		or two sub-trees, depending on the allocation group size.
 *		we search the top nodes of these subtrees left to right क्रम
 *		sufficient मुक्त space.  अगर sufficient मुक्त space is found,
 *		the subtree is searched to find the lefपंचांगost leaf that
 *		has मुक्त space.  once we have made it to the leaf, we
 *		move the search to the next lower level dmap control page
 *		corresponding to this leaf.  we जारी करोwn the dmap control
 *		pages until we find the dmap that contains or starts the
 *		sufficient मुक्त space and we allocate at this dmap.
 *
 *		अगर the allocation group size is equal to the dmap size,
 *		we'll start at the dmap corresponding to the allocation
 *		group and attempt the allocation at this level.
 *
 *		the dmap control page search is also not perक्रमmed अगर the
 *		allocation group is completely मुक्त and we go to the first
 *		dmap of the allocation group to करो the allocation.  this is
 *		करोne because the allocation group may be part (not the first
 *		part) of a larger binary buddy प्रणाली, causing the dmap
 *		control pages to indicate no मुक्त space (NOFREE) within
 *		the allocation group.
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	agno	- allocation group number.
 *	nblocks	-  actual number of contiguous मुक्त blocks desired.
 *	l2nb	-  log2 number of contiguous मुक्त blocks desired.
 *	results	-  on successful वापस, set to the starting block number
 *		   of the newly allocated range.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 *
 * note: IWRITE_LOCK(ipmap) held on entry/निकास;
 */
अटल पूर्णांक
dbAllocAG(काष्ठा bmap * bmp, पूर्णांक agno, s64 nblocks, पूर्णांक l2nb, s64 * results)
अणु
	काष्ठा metapage *mp;
	काष्ठा dmapctl *dcp;
	पूर्णांक rc, ti, i, k, m, n, agperlev;
	s64 blkno, lblkno;
	पूर्णांक budmin;

	/* allocation request should not be क्रम more than the
	 * allocation group size.
	 */
	अगर (l2nb > bmp->db_agl2size) अणु
		jfs_error(bmp->db_ipbmap->i_sb,
			  "allocation request is larger than the allocation group size\n");
		वापस -EIO;
	पूर्ण

	/* determine the starting block number of the allocation
	 * group.
	 */
	blkno = (s64) agno << bmp->db_agl2size;

	/* check अगर the allocation group size is the minimum allocation
	 * group size or अगर the allocation group is completely मुक्त. अगर
	 * the allocation group size is the minimum size of BPERDMAP (i.e.
	 * 1 dmap), there is no need to search the dmap control page (below)
	 * that fully describes the allocation group since the allocation
	 * group is alपढ़ोy fully described by a dmap.  in this हाल, we
	 * just call dbAllocCtl() to search the dmap tree and allocate the
	 * required space अगर available.
	 *
	 * अगर the allocation group is completely मुक्त, dbAllocCtl() is
	 * also called to allocate the required space.  this is करोne क्रम
	 * two reasons.  first, it makes no sense searching the dmap control
	 * pages क्रम मुक्त space when we know that मुक्त space exists.  second,
	 * the dmap control pages may indicate that the allocation group
	 * has no मुक्त space अगर the allocation group is part (not the first
	 * part) of a larger binary buddy प्रणाली.
	 */
	अगर (bmp->db_agsize == BPERDMAP
	    || bmp->db_agमुक्त[agno] == bmp->db_agsize) अणु
		rc = dbAllocCtl(bmp, nblocks, l2nb, blkno, results);
		अगर ((rc == -ENOSPC) &&
		    (bmp->db_agमुक्त[agno] == bmp->db_agsize)) अणु
			prपूर्णांकk(KERN_ERR "blkno = %Lx, blocks = %Lx\n",
			       (अचिन्हित दीर्घ दीर्घ) blkno,
			       (अचिन्हित दीर्घ दीर्घ) nblocks);
			jfs_error(bmp->db_ipbmap->i_sb,
				  "dbAllocCtl failed in free AG\n");
		पूर्ण
		वापस (rc);
	पूर्ण

	/* the buffer क्रम the dmap control page that fully describes the
	 * allocation group.
	 */
	lblkno = BLKTOCTL(blkno, bmp->db_l2nbperpage, bmp->db_aglevel);
	mp = पढ़ो_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
	अगर (mp == शून्य)
		वापस -EIO;
	dcp = (काष्ठा dmapctl *) mp->data;
	budmin = dcp->budmin;

	अगर (dcp->leafidx != cpu_to_le32(CTLLEAFIND)) अणु
		jfs_error(bmp->db_ipbmap->i_sb, "Corrupt dmapctl page\n");
		release_metapage(mp);
		वापस -EIO;
	पूर्ण

	/* search the subtree(s) of the dmap control page that describes
	 * the allocation group, looking क्रम sufficient मुक्त space.  to begin,
	 * determine how many allocation groups are represented in a dmap
	 * control page at the control page level (i.e. L0, L1, L2) that
	 * fully describes an allocation group. next, determine the starting
	 * tree index of this allocation group within the control page.
	 */
	agperlev =
	    (1 << (L2LPERCTL - (bmp->db_agheight << 1))) / bmp->db_agwidth;
	ti = bmp->db_agstart + bmp->db_agwidth * (agno & (agperlev - 1));

	/* dmap control page trees fan-out by 4 and a single allocation
	 * group may be described by 1 or 2 subtrees within the ag level
	 * dmap control page, depending upon the ag size. examine the ag's
	 * subtrees क्रम sufficient मुक्त space, starting with the lefपंचांगost
	 * subtree.
	 */
	क्रम (i = 0; i < bmp->db_agwidth; i++, ti++) अणु
		/* is there sufficient मुक्त space ?
		 */
		अगर (l2nb > dcp->stree[ti])
			जारी;

		/* sufficient मुक्त space found in a subtree. now search करोwn
		 * the subtree to find the lefपंचांगost leaf that describes this
		 * मुक्त space.
		 */
		क्रम (k = bmp->db_agheight; k > 0; k--) अणु
			क्रम (n = 0, m = (ti << 2) + 1; n < 4; n++) अणु
				अगर (l2nb <= dcp->stree[m + n]) अणु
					ti = m + n;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (n == 4) अणु
				jfs_error(bmp->db_ipbmap->i_sb,
					  "failed descending stree\n");
				release_metapage(mp);
				वापस -EIO;
			पूर्ण
		पूर्ण

		/* determine the block number within the file प्रणाली
		 * that corresponds to this leaf.
		 */
		अगर (bmp->db_aglevel == 2)
			blkno = 0;
		अन्यथा अगर (bmp->db_aglevel == 1)
			blkno &= ~(MAXL1SIZE - 1);
		अन्यथा		/* bmp->db_aglevel == 0 */
			blkno &= ~(MAXL0SIZE - 1);

		blkno +=
		    ((s64) (ti - le32_to_cpu(dcp->leafidx))) << budmin;

		/* release the buffer in preparation क्रम going करोwn
		 * the next level of dmap control pages.
		 */
		release_metapage(mp);

		/* check अगर we need to जारी to search करोwn the lower
		 * level dmap control pages.  we need to अगर the number of
		 * blocks required is less than maximum number of blocks
		 * described at the next lower level.
		 */
		अगर (l2nb < budmin) अणु

			/* search the lower level dmap control pages to get
			 * the starting block number of the dmap that
			 * contains or starts off the मुक्त space.
			 */
			अगर ((rc =
			     dbFindCtl(bmp, l2nb, bmp->db_aglevel - 1,
				       &blkno))) अणु
				अगर (rc == -ENOSPC) अणु
					jfs_error(bmp->db_ipbmap->i_sb,
						  "control page inconsistent\n");
					वापस -EIO;
				पूर्ण
				वापस (rc);
			पूर्ण
		पूर्ण

		/* allocate the blocks.
		 */
		rc = dbAllocCtl(bmp, nblocks, l2nb, blkno, results);
		अगर (rc == -ENOSPC) अणु
			jfs_error(bmp->db_ipbmap->i_sb,
				  "unable to allocate blocks\n");
			rc = -EIO;
		पूर्ण
		वापस (rc);
	पूर्ण

	/* no space in the allocation group.  release the buffer and
	 * वापस -ENOSPC.
	 */
	release_metapage(mp);

	वापस -ENOSPC;
पूर्ण


/*
 * NAME:	dbAllocAny()
 *
 * FUNCTION:	attempt to allocate the specअगरied number of contiguous
 *		मुक्त blocks anywhere in the file प्रणाली.
 *
 *		dbAllocAny() attempts to find the sufficient मुक्त space by
 *		searching करोwn the dmap control pages, starting with the
 *		highest level (i.e. L0, L1, L2) control page.  अगर मुक्त space
 *		large enough to satisfy the desired मुक्त space is found, the
 *		desired मुक्त space is allocated.
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	nblocks	 -  actual number of contiguous मुक्त blocks desired.
 *	l2nb	 -  log2 number of contiguous मुक्त blocks desired.
 *	results	-  on successful वापस, set to the starting block number
 *		   of the newly allocated range.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 *
 * serialization: IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक dbAllocAny(काष्ठा bmap * bmp, s64 nblocks, पूर्णांक l2nb, s64 * results)
अणु
	पूर्णांक rc;
	s64 blkno = 0;

	/* starting with the top level dmap control page, search
	 * करोwn the dmap control levels क्रम sufficient मुक्त space.
	 * अगर मुक्त space is found, dbFindCtl() वापसs the starting
	 * block number of the dmap that contains or starts off the
	 * range of मुक्त space.
	 */
	अगर ((rc = dbFindCtl(bmp, l2nb, bmp->db_maxlevel, &blkno)))
		वापस (rc);

	/* allocate the blocks.
	 */
	rc = dbAllocCtl(bmp, nblocks, l2nb, blkno, results);
	अगर (rc == -ENOSPC) अणु
		jfs_error(bmp->db_ipbmap->i_sb, "unable to allocate blocks\n");
		वापस -EIO;
	पूर्ण
	वापस (rc);
पूर्ण


/*
 * NAME:	dbDiscardAG()
 *
 * FUNCTION:	attempt to discard (TRIM) all मुक्त blocks of specअगरic AG
 *
 *		algorithm:
 *		1) allocate blocks, as large as possible and save them
 *		   जबतक holding IWRITE_LOCK on ipbmap
 *		2) trim all these saved block/length values
 *		3) mark the blocks मुक्त again
 *
 *		benefit:
 *		- we work only on one ag at some समय, minimizing how दीर्घ we
 *		  need to lock ipbmap
 *		- पढ़ोing / writing the fs is possible most समय, even on
 *		  trimming
 *
 *		करोwnside:
 *		- we ग_लिखो two बार to the dmapctl and dmap pages
 *		- but क्रम me, this seems the best way, better ideas?
 *		/TR 2012
 *
 * PARAMETERS:
 *	ip	- poपूर्णांकer to in-core inode
 *	agno	- ag to trim
 *	minlen	- minimum value of contiguous blocks
 *
 * RETURN VALUES:
 *	s64	- actual number of blocks trimmed
 */
s64 dbDiscardAG(काष्ठा inode *ip, पूर्णांक agno, s64 minlen)
अणु
	काष्ठा inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	काष्ठा bmap *bmp = JFS_SBI(ip->i_sb)->bmap;
	s64 nblocks, blkno;
	u64 trimmed = 0;
	पूर्णांक rc, l2nb;
	काष्ठा super_block *sb = ipbmap->i_sb;

	काष्ठा range2trim अणु
		u64 blkno;
		u64 nblocks;
	पूर्ण *totrim, *tt;

	/* max blkno / nblocks pairs to trim */
	पूर्णांक count = 0, range_cnt;
	u64 max_ranges;

	/* prevent others from writing new stuff here, जबतक trimming */
	IWRITE_LOCK(ipbmap, RDWRLOCK_DMAP);

	nblocks = bmp->db_agमुक्त[agno];
	max_ranges = nblocks;
	करो_भाग(max_ranges, minlen);
	range_cnt = min_t(u64, max_ranges + 1, 32 * 1024);
	totrim = kदो_स्मृति_array(range_cnt, माप(काष्ठा range2trim), GFP_NOFS);
	अगर (totrim == शून्य) अणु
		jfs_error(bmp->db_ipbmap->i_sb, "no memory for trim array\n");
		IWRITE_UNLOCK(ipbmap);
		वापस 0;
	पूर्ण

	tt = totrim;
	जबतक (nblocks >= minlen) अणु
		l2nb = BLKSTOL2(nblocks);

		/* 0 = okay, -EIO = fatal, -ENOSPC -> try smaller block */
		rc = dbAllocAG(bmp, agno, nblocks, l2nb, &blkno);
		अगर (rc == 0) अणु
			tt->blkno = blkno;
			tt->nblocks = nblocks;
			tt++; count++;

			/* the whole ag is मुक्त, trim now */
			अगर (bmp->db_agमुक्त[agno] == 0)
				अवरोध;

			/* give a hपूर्णांक क्रम the next जबतक */
			nblocks = bmp->db_agमुक्त[agno];
			जारी;
		पूर्ण अन्यथा अगर (rc == -ENOSPC) अणु
			/* search क्रम next smaller log2 block */
			l2nb = BLKSTOL2(nblocks) - 1;
			nblocks = 1LL << l2nb;
		पूर्ण अन्यथा अणु
			/* Trim any alपढ़ोy allocated blocks */
			jfs_error(bmp->db_ipbmap->i_sb, "-EIO\n");
			अवरोध;
		पूर्ण

		/* check, अगर our trim array is full */
		अगर (unlikely(count >= range_cnt - 1))
			अवरोध;
	पूर्ण
	IWRITE_UNLOCK(ipbmap);

	tt->nblocks = 0; /* mark the current end */
	क्रम (tt = totrim; tt->nblocks != 0; tt++) अणु
		/* when mounted with online discard, dbFree() will
		 * call jfs_issue_discard() itself */
		अगर (!(JFS_SBI(sb)->flag & JFS_DISCARD))
			jfs_issue_discard(ip, tt->blkno, tt->nblocks);
		dbFree(ip, tt->blkno, tt->nblocks);
		trimmed += tt->nblocks;
	पूर्ण
	kमुक्त(totrim);

	वापस trimmed;
पूर्ण

/*
 * NAME:	dbFindCtl()
 *
 * FUNCTION:	starting at a specअगरied dmap control page level and block
 *		number, search करोwn the dmap control levels क्रम a range of
 *		contiguous मुक्त blocks large enough to satisfy an allocation
 *		request क्रम the specअगरied number of मुक्त blocks.
 *
 *		अगर sufficient contiguous मुक्त blocks are found, this routine
 *		वापसs the starting block number within a dmap page that
 *		contains or starts a range of contiqious मुक्त blocks that
 *		is sufficient in size.
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	level	-  starting dmap control page level.
 *	l2nb	-  log2 number of contiguous मुक्त blocks desired.
 *	*blkno	-  on entry, starting block number क्रम conducting the search.
 *		   on successful वापस, the first block within a dmap page
 *		   that contains or starts a range of contiguous मुक्त blocks.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 *
 * serialization: IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक dbFindCtl(काष्ठा bmap * bmp, पूर्णांक l2nb, पूर्णांक level, s64 * blkno)
अणु
	पूर्णांक rc, leafidx, lev;
	s64 b, lblkno;
	काष्ठा dmapctl *dcp;
	पूर्णांक budmin;
	काष्ठा metapage *mp;

	/* starting at the specअगरied dmap control page level and block
	 * number, search करोwn the dmap control levels क्रम the starting
	 * block number of a dmap page that contains or starts off
	 * sufficient मुक्त blocks.
	 */
	क्रम (lev = level, b = *blkno; lev >= 0; lev--) अणु
		/* get the buffer of the dmap control page क्रम the block
		 * number and level (i.e. L0, L1, L2).
		 */
		lblkno = BLKTOCTL(b, bmp->db_l2nbperpage, lev);
		mp = पढ़ो_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
		अगर (mp == शून्य)
			वापस -EIO;
		dcp = (काष्ठा dmapctl *) mp->data;
		budmin = dcp->budmin;

		अगर (dcp->leafidx != cpu_to_le32(CTLLEAFIND)) अणु
			jfs_error(bmp->db_ipbmap->i_sb,
				  "Corrupt dmapctl page\n");
			release_metapage(mp);
			वापस -EIO;
		पूर्ण

		/* search the tree within the dmap control page क्रम
		 * sufficient मुक्त space.  अगर sufficient मुक्त space is found,
		 * dbFindLeaf() वापसs the index of the leaf at which
		 * मुक्त space was found.
		 */
		rc = dbFindLeaf((dmtree_t *) dcp, l2nb, &leafidx);

		/* release the buffer.
		 */
		release_metapage(mp);

		/* space found ?
		 */
		अगर (rc) अणु
			अगर (lev != level) अणु
				jfs_error(bmp->db_ipbmap->i_sb,
					  "dmap inconsistent\n");
				वापस -EIO;
			पूर्ण
			वापस -ENOSPC;
		पूर्ण

		/* adjust the block number to reflect the location within
		 * the dmap control page (i.e. the leaf) at which मुक्त
		 * space was found.
		 */
		b += (((s64) leafidx) << budmin);

		/* we stop the search at this dmap control page level अगर
		 * the number of blocks required is greater than or equal
		 * to the maximum number of blocks described at the next
		 * (lower) level.
		 */
		अगर (l2nb >= budmin)
			अवरोध;
	पूर्ण

	*blkno = b;
	वापस (0);
पूर्ण


/*
 * NAME:	dbAllocCtl()
 *
 * FUNCTION:	attempt to allocate a specअगरied number of contiguous
 *		blocks starting within a specअगरic dmap.
 *
 *		this routine is called by higher level routines that search
 *		the dmap control pages above the actual dmaps क्रम contiguous
 *		मुक्त space.  the result of successful searches by these
 *		routines are the starting block numbers within dmaps, with
 *		the dmaps themselves containing the desired contiguous मुक्त
 *		space or starting a contiguous मुक्त space of desired size
 *		that is made up of the blocks of one or more dmaps. these
 *		calls should not fail due to insufficent resources.
 *
 *		this routine is called in some हालs where it is not known
 *		whether it will fail due to insufficient resources.  more
 *		specअगरically, this occurs when allocating from an allocation
 *		group whose size is equal to the number of blocks per dmap.
 *		in this हाल, the dmap control pages are not examined prior
 *		to calling this routine (to save pathlength) and the call
 *		might fail.
 *
 *		क्रम a request size that fits within a dmap, this routine relies
 *		upon the dmap's dmtree to find the requested contiguous मुक्त
 *		space.  क्रम request sizes that are larger than a dmap, the
 *		requested मुक्त space will start at the first block of the
 *		first dmap (i.e. blkno).
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	nblocks	 -  actual number of contiguous मुक्त blocks to allocate.
 *	l2nb	 -  log2 number of contiguous मुक्त blocks to allocate.
 *	blkno	 -  starting block number of the dmap to start the allocation
 *		    from.
 *	results	-  on successful वापस, set to the starting block number
 *		   of the newly allocated range.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 *
 * serialization: IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक
dbAllocCtl(काष्ठा bmap * bmp, s64 nblocks, पूर्णांक l2nb, s64 blkno, s64 * results)
अणु
	पूर्णांक rc, nb;
	s64 b, lblkno, n;
	काष्ठा metapage *mp;
	काष्ठा dmap *dp;

	/* check अगर the allocation request is confined to a single dmap.
	 */
	अगर (l2nb <= L2BPERDMAP) अणु
		/* get the buffer क्रम the dmap.
		 */
		lblkno = BLKTODMAP(blkno, bmp->db_l2nbperpage);
		mp = पढ़ो_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
		अगर (mp == शून्य)
			वापस -EIO;
		dp = (काष्ठा dmap *) mp->data;

		/* try to allocate the blocks.
		 */
		rc = dbAllocDmapLev(bmp, dp, (पूर्णांक) nblocks, l2nb, results);
		अगर (rc == 0)
			mark_metapage_dirty(mp);

		release_metapage(mp);

		वापस (rc);
	पूर्ण

	/* allocation request involving multiple dmaps. it must start on
	 * a dmap boundary.
	 */
	निश्चित((blkno & (BPERDMAP - 1)) == 0);

	/* allocate the blocks dmap by dmap.
	 */
	क्रम (n = nblocks, b = blkno; n > 0; n -= nb, b += nb) अणु
		/* get the buffer क्रम the dmap.
		 */
		lblkno = BLKTODMAP(b, bmp->db_l2nbperpage);
		mp = पढ़ो_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
		अगर (mp == शून्य) अणु
			rc = -EIO;
			जाओ backout;
		पूर्ण
		dp = (काष्ठा dmap *) mp->data;

		/* the dmap better be all मुक्त.
		 */
		अगर (dp->tree.stree[ROOT] != L2BPERDMAP) अणु
			release_metapage(mp);
			jfs_error(bmp->db_ipbmap->i_sb,
				  "the dmap is not all free\n");
			rc = -EIO;
			जाओ backout;
		पूर्ण

		/* determine how many blocks to allocate from this dmap.
		 */
		nb = min_t(s64, n, BPERDMAP);

		/* allocate the blocks from the dmap.
		 */
		अगर ((rc = dbAllocDmap(bmp, dp, b, nb))) अणु
			release_metapage(mp);
			जाओ backout;
		पूर्ण

		/* ग_लिखो the buffer.
		 */
		ग_लिखो_metapage(mp);
	पूर्ण

	/* set the results (starting block number) and वापस.
	 */
	*results = blkno;
	वापस (0);

	/* something failed in handling an allocation request involving
	 * multiple dmaps.  we'll try to clean up by backing out any
	 * allocation that has alपढ़ोy happened क्रम this request.  अगर
	 * we fail in backing out the allocation, we'll mark the file
	 * प्रणाली to indicate that blocks have been leaked.
	 */
      backout:

	/* try to backout the allocations dmap by dmap.
	 */
	क्रम (n = nblocks - n, b = blkno; n > 0;
	     n -= BPERDMAP, b += BPERDMAP) अणु
		/* get the buffer क्रम this dmap.
		 */
		lblkno = BLKTODMAP(b, bmp->db_l2nbperpage);
		mp = पढ़ो_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
		अगर (mp == शून्य) अणु
			/* could not back out.  mark the file प्रणाली
			 * to indicate that we have leaked blocks.
			 */
			jfs_error(bmp->db_ipbmap->i_sb,
				  "I/O Error: Block Leakage\n");
			जारी;
		पूर्ण
		dp = (काष्ठा dmap *) mp->data;

		/* मुक्त the blocks is this dmap.
		 */
		अगर (dbFreeDmap(bmp, dp, b, BPERDMAP)) अणु
			/* could not back out.  mark the file प्रणाली
			 * to indicate that we have leaked blocks.
			 */
			release_metapage(mp);
			jfs_error(bmp->db_ipbmap->i_sb, "Block Leakage\n");
			जारी;
		पूर्ण

		/* ग_लिखो the buffer.
		 */
		ग_लिखो_metapage(mp);
	पूर्ण

	वापस (rc);
पूर्ण


/*
 * NAME:	dbAllocDmapLev()
 *
 * FUNCTION:	attempt to allocate a specअगरied number of contiguous blocks
 *		from a specअगरied dmap.
 *
 *		this routine checks अगर the contiguous blocks are available.
 *		अगर so, nblocks of blocks are allocated; otherwise, ENOSPC is
 *		वापसed.
 *
 * PARAMETERS:
 *	mp	-  poपूर्णांकer to bmap descriptor
 *	dp	-  poपूर्णांकer to dmap to attempt to allocate blocks from.
 *	l2nb	-  log2 number of contiguous block desired.
 *	nblocks	-  actual number of contiguous block desired.
 *	results	-  on successful वापस, set to the starting block number
 *		   of the newly allocated range.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk resources
 *	-EIO	- i/o error
 *
 * serialization: IREAD_LOCK(ipbmap), e.g., from dbAlloc(), or
 *	IWRITE_LOCK(ipbmap), e.g., dbAllocCtl(), held on entry/निकास;
 */
अटल पूर्णांक
dbAllocDmapLev(काष्ठा bmap * bmp,
	       काष्ठा dmap * dp, पूर्णांक nblocks, पूर्णांक l2nb, s64 * results)
अणु
	s64 blkno;
	पूर्णांक leafidx, rc;

	/* can't be more than a dmaps worth of blocks */
	निश्चित(l2nb <= L2BPERDMAP);

	/* search the tree within the dmap page क्रम sufficient
	 * मुक्त space.  अगर sufficient मुक्त space is found, dbFindLeaf()
	 * वापसs the index of the leaf at which मुक्त space was found.
	 */
	अगर (dbFindLeaf((dmtree_t *) & dp->tree, l2nb, &leafidx))
		वापस -ENOSPC;

	/* determine the block number within the file प्रणाली corresponding
	 * to the leaf at which मुक्त space was found.
	 */
	blkno = le64_to_cpu(dp->start) + (leafidx << L2DBWORD);

	/* अगर not all bits of the dmap word are मुक्त, get the starting
	 * bit number within the dmap word of the required string of मुक्त
	 * bits and adjust the block number with this value.
	 */
	अगर (dp->tree.stree[leafidx + LEAFIND] < BUDMIN)
		blkno += dbFindBits(le32_to_cpu(dp->wmap[leafidx]), l2nb);

	/* allocate the blocks */
	अगर ((rc = dbAllocDmap(bmp, dp, blkno, nblocks)) == 0)
		*results = blkno;

	वापस (rc);
पूर्ण


/*
 * NAME:	dbAllocDmap()
 *
 * FUNCTION:	adjust the disk allocation map to reflect the allocation
 *		of a specअगरied block range within a dmap.
 *
 *		this routine allocates the specअगरied blocks from the dmap
 *		through a call to dbAllocBits(). अगर the allocation of the
 *		block range causes the maximum string of मुक्त blocks within
 *		the dmap to change (i.e. the value of the root of the dmap's
 *		dmtree), this routine will cause this change to be reflected
 *		up through the appropriate levels of the dmap control pages
 *		by a call to dbAdjCtl() क्रम the L0 dmap control page that
 *		covers this dmap.
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	dp	-  poपूर्णांकer to dmap to allocate the block range from.
 *	blkno	-  starting block number of the block to be allocated.
 *	nblocks	-  number of blocks to be allocated.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error
 *
 * serialization: IREAD_LOCK(ipbmap) or IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक dbAllocDmap(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
		       पूर्णांक nblocks)
अणु
	s8 oldroot;
	पूर्णांक rc;

	/* save the current value of the root (i.e. maximum मुक्त string)
	 * of the dmap tree.
	 */
	oldroot = dp->tree.stree[ROOT];

	/* allocate the specअगरied (blocks) bits */
	dbAllocBits(bmp, dp, blkno, nblocks);

	/* अगर the root has not changed, करोne. */
	अगर (dp->tree.stree[ROOT] == oldroot)
		वापस (0);

	/* root changed. bubble the change up to the dmap control pages.
	 * अगर the adjusपंचांगent of the upper level control pages fails,
	 * backout the bit allocation (thus making everything consistent).
	 */
	अगर ((rc = dbAdjCtl(bmp, blkno, dp->tree.stree[ROOT], 1, 0)))
		dbFreeBits(bmp, dp, blkno, nblocks);

	वापस (rc);
पूर्ण


/*
 * NAME:	dbFreeDmap()
 *
 * FUNCTION:	adjust the disk allocation map to reflect the allocation
 *		of a specअगरied block range within a dmap.
 *
 *		this routine मुक्तs the specअगरied blocks from the dmap through
 *		a call to dbFreeBits(). अगर the deallocation of the block range
 *		causes the maximum string of मुक्त blocks within the dmap to
 *		change (i.e. the value of the root of the dmap's dmtree), this
 *		routine will cause this change to be reflected up through the
 *		appropriate levels of the dmap control pages by a call to
 *		dbAdjCtl() क्रम the L0 dmap control page that covers this dmap.
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	dp	-  poपूर्णांकer to dmap to मुक्त the block range from.
 *	blkno	-  starting block number of the block to be मुक्तd.
 *	nblocks	-  number of blocks to be मुक्तd.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error
 *
 * serialization: IREAD_LOCK(ipbmap) or IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक dbFreeDmap(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
		      पूर्णांक nblocks)
अणु
	s8 oldroot;
	पूर्णांक rc = 0, word;

	/* save the current value of the root (i.e. maximum मुक्त string)
	 * of the dmap tree.
	 */
	oldroot = dp->tree.stree[ROOT];

	/* मुक्त the specअगरied (blocks) bits */
	rc = dbFreeBits(bmp, dp, blkno, nblocks);

	/* अगर error or the root has not changed, करोne. */
	अगर (rc || (dp->tree.stree[ROOT] == oldroot))
		वापस (rc);

	/* root changed. bubble the change up to the dmap control pages.
	 * अगर the adjusपंचांगent of the upper level control pages fails,
	 * backout the deallocation.
	 */
	अगर ((rc = dbAdjCtl(bmp, blkno, dp->tree.stree[ROOT], 0, 0))) अणु
		word = (blkno & (BPERDMAP - 1)) >> L2DBWORD;

		/* as part of backing out the deallocation, we will have
		 * to back split the dmap tree अगर the deallocation caused
		 * the मुक्तd blocks to become part of a larger binary buddy
		 * प्रणाली.
		 */
		अगर (dp->tree.stree[word] == NOFREE)
			dbBackSplit((dmtree_t *) & dp->tree, word);

		dbAllocBits(bmp, dp, blkno, nblocks);
	पूर्ण

	वापस (rc);
पूर्ण


/*
 * NAME:	dbAllocBits()
 *
 * FUNCTION:	allocate a specअगरied block range from a dmap.
 *
 *		this routine updates the dmap to reflect the working
 *		state allocation of the specअगरied block range. it directly
 *		updates the bits of the working map and causes the adjusपंचांगent
 *		of the binary buddy प्रणाली described by the dmap's dmtree
 *		leaves to reflect the bits allocated.  it also causes the
 *		dmap's dmtree, as a whole, to reflect the allocated range.
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	dp	-  poपूर्णांकer to dmap to allocate bits from.
 *	blkno	-  starting block number of the bits to be allocated.
 *	nblocks	-  number of bits to be allocated.
 *
 * RETURN VALUES: none
 *
 * serialization: IREAD_LOCK(ipbmap) or IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल व्योम dbAllocBits(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
			पूर्णांक nblocks)
अणु
	पूर्णांक dbitno, word, rembits, nb, nwords, wbitno, nw, agno;
	dmtree_t *tp = (dmtree_t *) & dp->tree;
	पूर्णांक size;
	s8 *leaf;

	/* pick up a poपूर्णांकer to the leaves of the dmap tree */
	leaf = dp->tree.stree + LEAFIND;

	/* determine the bit number and word within the dmap of the
	 * starting block.
	 */
	dbitno = blkno & (BPERDMAP - 1);
	word = dbitno >> L2DBWORD;

	/* block range better be within the dmap */
	निश्चित(dbitno + nblocks <= BPERDMAP);

	/* allocate the bits of the dmap's words corresponding to the block
	 * range. not all bits of the first and last words may be contained
	 * within the block range.  अगर this is the हाल, we'll work against
	 * those words (i.e. partial first and/or last) on an inभागidual basis
	 * (a single pass), allocating the bits of पूर्णांकerest by hand and
	 * updating the leaf corresponding to the dmap word. a single pass
	 * will be used क्रम all dmap words fully contained within the
	 * specअगरied range.  within this pass, the bits of all fully contained
	 * dmap words will be marked as मुक्त in a single shot and the leaves
	 * will be updated. a single leaf may describe the मुक्त space of
	 * multiple dmap words, so we may update only a subset of the actual
	 * leaves corresponding to the dmap words of the block range.
	 */
	क्रम (rembits = nblocks; rembits > 0; rembits -= nb, dbitno += nb) अणु
		/* determine the bit number within the word and
		 * the number of bits within the word.
		 */
		wbitno = dbitno & (DBWORD - 1);
		nb = min(rembits, DBWORD - wbitno);

		/* check अगर only part of a word is to be allocated.
		 */
		अगर (nb < DBWORD) अणु
			/* allocate (set to 1) the appropriate bits within
			 * this dmap word.
			 */
			dp->wmap[word] |= cpu_to_le32(ONES << (DBWORD - nb)
						      >> wbitno);

			/* update the leaf क्रम this dmap word. in addition
			 * to setting the leaf value to the binary buddy max
			 * of the updated dmap word, dbSplit() will split
			 * the binary प्रणाली of the leaves अगर need be.
			 */
			dbSplit(tp, word, BUDMIN,
				dbMaxBud((u8 *) & dp->wmap[word]));

			word += 1;
		पूर्ण अन्यथा अणु
			/* one or more dmap words are fully contained
			 * within the block range.  determine how many
			 * words and allocate (set to 1) the bits of these
			 * words.
			 */
			nwords = rembits >> L2DBWORD;
			स_रखो(&dp->wmap[word], (पूर्णांक) ONES, nwords * 4);

			/* determine how many bits.
			 */
			nb = nwords << L2DBWORD;

			/* now update the appropriate leaves to reflect
			 * the allocated words.
			 */
			क्रम (; nwords > 0; nwords -= nw) अणु
				अगर (leaf[word] < BUDMIN) अणु
					jfs_error(bmp->db_ipbmap->i_sb,
						  "leaf page corrupt\n");
					अवरोध;
				पूर्ण

				/* determine what the leaf value should be
				 * updated to as the minimum of the l2 number
				 * of bits being allocated and the l2 number
				 * of bits currently described by this leaf.
				 */
				size = min_t(पूर्णांक, leaf[word],
					     NLSTOL2BSZ(nwords));

				/* update the leaf to reflect the allocation.
				 * in addition to setting the leaf value to
				 * NOFREE, dbSplit() will split the binary
				 * प्रणाली of the leaves to reflect the current
				 * allocation (size).
				 */
				dbSplit(tp, word, size, NOFREE);

				/* get the number of dmap words handled */
				nw = BUDSIZE(size, BUDMIN);
				word += nw;
			पूर्ण
		पूर्ण
	पूर्ण

	/* update the मुक्त count क्रम this dmap */
	le32_add_cpu(&dp->nमुक्त, -nblocks);

	BMAP_LOCK(bmp);

	/* अगर this allocation group is completely मुक्त,
	 * update the maximum allocation group number अगर this allocation
	 * group is the new max.
	 */
	agno = blkno >> bmp->db_agl2size;
	अगर (agno > bmp->db_maxag)
		bmp->db_maxag = agno;

	/* update the मुक्त count क्रम the allocation group and map */
	bmp->db_agमुक्त[agno] -= nblocks;
	bmp->db_nमुक्त -= nblocks;

	BMAP_UNLOCK(bmp);
पूर्ण


/*
 * NAME:	dbFreeBits()
 *
 * FUNCTION:	मुक्त a specअगरied block range from a dmap.
 *
 *		this routine updates the dmap to reflect the working
 *		state allocation of the specअगरied block range. it directly
 *		updates the bits of the working map and causes the adjusपंचांगent
 *		of the binary buddy प्रणाली described by the dmap's dmtree
 *		leaves to reflect the bits मुक्तd.  it also causes the dmap's
 *		dmtree, as a whole, to reflect the deallocated range.
 *
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	dp	-  poपूर्णांकer to dmap to मुक्त bits from.
 *	blkno	-  starting block number of the bits to be मुक्तd.
 *	nblocks	-  number of bits to be मुक्तd.
 *
 * RETURN VALUES: 0 क्रम success
 *
 * serialization: IREAD_LOCK(ipbmap) or IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक dbFreeBits(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
		       पूर्णांक nblocks)
अणु
	पूर्णांक dbitno, word, rembits, nb, nwords, wbitno, nw, agno;
	dmtree_t *tp = (dmtree_t *) & dp->tree;
	पूर्णांक rc = 0;
	पूर्णांक size;

	/* determine the bit number and word within the dmap of the
	 * starting block.
	 */
	dbitno = blkno & (BPERDMAP - 1);
	word = dbitno >> L2DBWORD;

	/* block range better be within the dmap.
	 */
	निश्चित(dbitno + nblocks <= BPERDMAP);

	/* मुक्त the bits of the dmaps words corresponding to the block range.
	 * not all bits of the first and last words may be contained within
	 * the block range.  अगर this is the हाल, we'll work against those
	 * words (i.e. partial first and/or last) on an inभागidual basis
	 * (a single pass), मुक्तing the bits of पूर्णांकerest by hand and updating
	 * the leaf corresponding to the dmap word. a single pass will be used
	 * क्रम all dmap words fully contained within the specअगरied range.
	 * within this pass, the bits of all fully contained dmap words will
	 * be marked as मुक्त in a single shot and the leaves will be updated. a
	 * single leaf may describe the मुक्त space of multiple dmap words,
	 * so we may update only a subset of the actual leaves corresponding
	 * to the dmap words of the block range.
	 *
	 * dbJoin() is used to update leaf values and will join the binary
	 * buddy प्रणाली of the leaves अगर the new leaf values indicate this
	 * should be करोne.
	 */
	क्रम (rembits = nblocks; rembits > 0; rembits -= nb, dbitno += nb) अणु
		/* determine the bit number within the word and
		 * the number of bits within the word.
		 */
		wbitno = dbitno & (DBWORD - 1);
		nb = min(rembits, DBWORD - wbitno);

		/* check अगर only part of a word is to be मुक्तd.
		 */
		अगर (nb < DBWORD) अणु
			/* मुक्त (zero) the appropriate bits within this
			 * dmap word.
			 */
			dp->wmap[word] &=
			    cpu_to_le32(~(ONES << (DBWORD - nb)
					  >> wbitno));

			/* update the leaf क्रम this dmap word.
			 */
			rc = dbJoin(tp, word,
				    dbMaxBud((u8 *) & dp->wmap[word]));
			अगर (rc)
				वापस rc;

			word += 1;
		पूर्ण अन्यथा अणु
			/* one or more dmap words are fully contained
			 * within the block range.  determine how many
			 * words and मुक्त (zero) the bits of these words.
			 */
			nwords = rembits >> L2DBWORD;
			स_रखो(&dp->wmap[word], 0, nwords * 4);

			/* determine how many bits.
			 */
			nb = nwords << L2DBWORD;

			/* now update the appropriate leaves to reflect
			 * the मुक्तd words.
			 */
			क्रम (; nwords > 0; nwords -= nw) अणु
				/* determine what the leaf value should be
				 * updated to as the minimum of the l2 number
				 * of bits being मुक्तd and the l2 (max) number
				 * of bits that can be described by this leaf.
				 */
				size =
				    min(LITOL2BSZ
					(word, L2LPERDMAP, BUDMIN),
					NLSTOL2BSZ(nwords));

				/* update the leaf.
				 */
				rc = dbJoin(tp, word, size);
				अगर (rc)
					वापस rc;

				/* get the number of dmap words handled.
				 */
				nw = BUDSIZE(size, BUDMIN);
				word += nw;
			पूर्ण
		पूर्ण
	पूर्ण

	/* update the मुक्त count क्रम this dmap.
	 */
	le32_add_cpu(&dp->nमुक्त, nblocks);

	BMAP_LOCK(bmp);

	/* update the मुक्त count क्रम the allocation group and
	 * map.
	 */
	agno = blkno >> bmp->db_agl2size;
	bmp->db_nमुक्त += nblocks;
	bmp->db_agमुक्त[agno] += nblocks;

	/* check अगर this allocation group is not completely मुक्त and
	 * अगर it is currently the maximum (righपंचांगost) allocation group.
	 * अगर so, establish the new maximum allocation group number by
	 * searching left क्रम the first allocation group with allocation.
	 */
	अगर ((bmp->db_agमुक्त[agno] == bmp->db_agsize && agno == bmp->db_maxag) ||
	    (agno == bmp->db_numag - 1 &&
	     bmp->db_agमुक्त[agno] == (bmp-> db_mapsize & (BPERDMAP - 1)))) अणु
		जबतक (bmp->db_maxag > 0) अणु
			bmp->db_maxag -= 1;
			अगर (bmp->db_agमुक्त[bmp->db_maxag] !=
			    bmp->db_agsize)
				अवरोध;
		पूर्ण

		/* re-establish the allocation group preference अगर the
		 * current preference is right of the maximum allocation
		 * group.
		 */
		अगर (bmp->db_agpref > bmp->db_maxag)
			bmp->db_agpref = bmp->db_maxag;
	पूर्ण

	BMAP_UNLOCK(bmp);

	वापस 0;
पूर्ण


/*
 * NAME:	dbAdjCtl()
 *
 * FUNCTION:	adjust a dmap control page at a specअगरied level to reflect
 *		the change in a lower level dmap or dmap control page's
 *		maximum string of मुक्त blocks (i.e. a change in the root
 *		of the lower level object's dmtree) due to the allocation
 *		or deallocation of a range of blocks with a single dmap.
 *
 *		on entry, this routine is provided with the new value of
 *		the lower level dmap or dmap control page root and the
 *		starting block number of the block range whose allocation
 *		or deallocation resulted in the root change.  this range
 *		is respresented by a single leaf of the current dmapctl
 *		and the leaf will be updated with this value, possibly
 *		causing a binary buddy प्रणाली within the leaves to be
 *		split or joined.  the update may also cause the dmapctl's
 *		dmtree to be updated.
 *
 *		अगर the adjusपंचांगent of the dmap control page, itself, causes its
 *		root to change, this change will be bubbled up to the next dmap
 *		control level by a recursive call to this routine, specअगरying
 *		the new root value and the next dmap control page level to
 *		be adjusted.
 * PARAMETERS:
 *	bmp	-  poपूर्णांकer to bmap descriptor
 *	blkno	-  the first block of a block range within a dmap.  it is
 *		   the allocation or deallocation of this block range that
 *		   requires the dmap control page to be adjusted.
 *	newval	-  the new value of the lower level dmap or dmap control
 *		   page root.
 *	alloc	-  'true' अगर adjusपंचांगent is due to an allocation.
 *	level	-  current level of dmap control page (i.e. L0, L1, L2) to
 *		   be adjusted.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error
 *
 * serialization: IREAD_LOCK(ipbmap) or IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक
dbAdjCtl(काष्ठा bmap * bmp, s64 blkno, पूर्णांक newval, पूर्णांक alloc, पूर्णांक level)
अणु
	काष्ठा metapage *mp;
	s8 oldroot;
	पूर्णांक oldval;
	s64 lblkno;
	काष्ठा dmapctl *dcp;
	पूर्णांक rc, leafno, ti;

	/* get the buffer क्रम the dmap control page क्रम the specअगरied
	 * block number and control page level.
	 */
	lblkno = BLKTOCTL(blkno, bmp->db_l2nbperpage, level);
	mp = पढ़ो_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
	अगर (mp == शून्य)
		वापस -EIO;
	dcp = (काष्ठा dmapctl *) mp->data;

	अगर (dcp->leafidx != cpu_to_le32(CTLLEAFIND)) अणु
		jfs_error(bmp->db_ipbmap->i_sb, "Corrupt dmapctl page\n");
		release_metapage(mp);
		वापस -EIO;
	पूर्ण

	/* determine the leaf number corresponding to the block and
	 * the index within the dmap control tree.
	 */
	leafno = BLKTOCTLLEAF(blkno, dcp->budmin);
	ti = leafno + le32_to_cpu(dcp->leafidx);

	/* save the current leaf value and the current root level (i.e.
	 * maximum l2 मुक्त string described by this dmapctl).
	 */
	oldval = dcp->stree[ti];
	oldroot = dcp->stree[ROOT];

	/* check अगर this is a control page update क्रम an allocation.
	 * अगर so, update the leaf to reflect the new leaf value using
	 * dbSplit(); otherwise (deallocation), use dbJoin() to update
	 * the leaf with the new value.  in addition to updating the
	 * leaf, dbSplit() will also split the binary buddy प्रणाली of
	 * the leaves, अगर required, and bubble new values within the
	 * dmapctl tree, अगर required.  similarly, dbJoin() will join
	 * the binary buddy प्रणाली of leaves and bubble new values up
	 * the dmapctl tree as required by the new leaf value.
	 */
	अगर (alloc) अणु
		/* check अगर we are in the middle of a binary buddy
		 * प्रणाली.  this happens when we are perक्रमming the
		 * first allocation out of an allocation group that
		 * is part (not the first part) of a larger binary
		 * buddy प्रणाली.  अगर we are in the middle, back split
		 * the प्रणाली prior to calling dbSplit() which assumes
		 * that it is at the front of a binary buddy प्रणाली.
		 */
		अगर (oldval == NOFREE) अणु
			rc = dbBackSplit((dmtree_t *) dcp, leafno);
			अगर (rc) अणु
				release_metapage(mp);
				वापस rc;
			पूर्ण
			oldval = dcp->stree[ti];
		पूर्ण
		dbSplit((dmtree_t *) dcp, leafno, dcp->budmin, newval);
	पूर्ण अन्यथा अणु
		rc = dbJoin((dmtree_t *) dcp, leafno, newval);
		अगर (rc) अणु
			release_metapage(mp);
			वापस rc;
		पूर्ण
	पूर्ण

	/* check अगर the root of the current dmap control page changed due
	 * to the update and अगर the current dmap control page is not at
	 * the current top level (i.e. L0, L1, L2) of the map.  अगर so (i.e.
	 * root changed and this is not the top level), call this routine
	 * again (recursion) क्रम the next higher level of the mapping to
	 * reflect the change in root क्रम the current dmap control page.
	 */
	अगर (dcp->stree[ROOT] != oldroot) अणु
		/* are we below the top level of the map.  अगर so,
		 * bubble the root up to the next higher level.
		 */
		अगर (level < bmp->db_maxlevel) अणु
			/* bubble up the new root of this dmap control page to
			 * the next level.
			 */
			अगर ((rc =
			     dbAdjCtl(bmp, blkno, dcp->stree[ROOT], alloc,
				      level + 1))) अणु
				/* something went wrong in bubbling up the new
				 * root value, so backout the changes to the
				 * current dmap control page.
				 */
				अगर (alloc) अणु
					dbJoin((dmtree_t *) dcp, leafno,
					       oldval);
				पूर्ण अन्यथा अणु
					/* the dbJoin() above might have
					 * caused a larger binary buddy प्रणाली
					 * to क्रमm and we may now be in the
					 * middle of it.  अगर this is the हाल,
					 * back split the buddies.
					 */
					अगर (dcp->stree[ti] == NOFREE)
						dbBackSplit((dmtree_t *)
							    dcp, leafno);
					dbSplit((dmtree_t *) dcp, leafno,
						dcp->budmin, oldval);
				पूर्ण

				/* release the buffer and वापस the error.
				 */
				release_metapage(mp);
				वापस (rc);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* we're at the top level of the map. update
			 * the bmap control page to reflect the size
			 * of the maximum मुक्त buddy प्रणाली.
			 */
			निश्चित(level == bmp->db_maxlevel);
			अगर (bmp->db_maxमुक्तbud != oldroot) अणु
				jfs_error(bmp->db_ipbmap->i_sb,
					  "the maximum free buddy is not the old root\n");
			पूर्ण
			bmp->db_maxमुक्तbud = dcp->stree[ROOT];
		पूर्ण
	पूर्ण

	/* ग_लिखो the buffer.
	 */
	ग_लिखो_metapage(mp);

	वापस (0);
पूर्ण


/*
 * NAME:	dbSplit()
 *
 * FUNCTION:	update the leaf of a dmtree with a new value, splitting
 *		the leaf from the binary buddy प्रणाली of the dmtree's
 *		leaves, as required.
 *
 * PARAMETERS:
 *	tp	- poपूर्णांकer to the tree containing the leaf.
 *	leafno	- the number of the leaf to be updated.
 *	splitsz	- the size the binary buddy प्रणाली starting at the leaf
 *		  must be split to, specअगरied as the log2 number of blocks.
 *	newval	- the new value क्रम the leaf.
 *
 * RETURN VALUES: none
 *
 * serialization: IREAD_LOCK(ipbmap) or IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल व्योम dbSplit(dmtree_t * tp, पूर्णांक leafno, पूर्णांक splitsz, पूर्णांक newval)
अणु
	पूर्णांक budsz;
	पूर्णांक cursz;
	s8 *leaf = tp->dmt_stree + le32_to_cpu(tp->dmt_leafidx);

	/* check अगर the leaf needs to be split.
	 */
	अगर (leaf[leafno] > tp->dmt_budmin) अणु
		/* the split occurs by cutting the buddy प्रणाली in half
		 * at the specअगरied leaf until we reach the specअगरied
		 * size.  pick up the starting split size (current size
		 * - 1 in l2) and the corresponding buddy size.
		 */
		cursz = leaf[leafno] - 1;
		budsz = BUDSIZE(cursz, tp->dmt_budmin);

		/* split until we reach the specअगरied size.
		 */
		जबतक (cursz >= splitsz) अणु
			/* update the buddy's leaf with its new value.
			 */
			dbAdjTree(tp, leafno ^ budsz, cursz);

			/* on to the next size and buddy.
			 */
			cursz -= 1;
			budsz >>= 1;
		पूर्ण
	पूर्ण

	/* adjust the dmap tree to reflect the specअगरied leaf's new
	 * value.
	 */
	dbAdjTree(tp, leafno, newval);
पूर्ण


/*
 * NAME:	dbBackSplit()
 *
 * FUNCTION:	back split the binary buddy प्रणाली of dmtree leaves
 *		that hold a specअगरied leaf until the specअगरied leaf
 *		starts its own binary buddy प्रणाली.
 *
 *		the allocators typically perक्रमm allocations at the start
 *		of binary buddy प्रणालीs and dbSplit() is used to accomplish
 *		any required splits.  in some हालs, however, allocation
 *		may occur in the middle of a binary प्रणाली and requires a
 *		back split, with the split proceeding out from the middle of
 *		the प्रणाली (less efficient) rather than the start of the
 *		प्रणाली (more efficient).  the हालs in which a back split
 *		is required are rare and are limited to the first allocation
 *		within an allocation group which is a part (not first part)
 *		of a larger binary buddy प्रणाली and a few exception हालs
 *		in which a previous join operation must be backed out.
 *
 * PARAMETERS:
 *	tp	- poपूर्णांकer to the tree containing the leaf.
 *	leafno	- the number of the leaf to be updated.
 *
 * RETURN VALUES: none
 *
 * serialization: IREAD_LOCK(ipbmap) or IWRITE_LOCK(ipbmap) held on entry/निकास;
 */
अटल पूर्णांक dbBackSplit(dmtree_t * tp, पूर्णांक leafno)
अणु
	पूर्णांक budsz, bud, w, bsz, size;
	पूर्णांक cursz;
	s8 *leaf = tp->dmt_stree + le32_to_cpu(tp->dmt_leafidx);

	/* leaf should be part (not first part) of a binary
	 * buddy प्रणाली.
	 */
	निश्चित(leaf[leafno] == NOFREE);

	/* the back split is accomplished by iteratively finding the leaf
	 * that starts the buddy प्रणाली that contains the specअगरied leaf and
	 * splitting that प्रणाली in two.  this iteration जारीs until
	 * the specअगरied leaf becomes the start of a buddy प्रणाली.
	 *
	 * determine maximum possible l2 size क्रम the specअगरied leaf.
	 */
	size =
	    LITOL2BSZ(leafno, le32_to_cpu(tp->dmt_l2nleafs),
		      tp->dmt_budmin);

	/* determine the number of leaves covered by this size.  this
	 * is the buddy size that we will start with as we search क्रम
	 * the buddy प्रणाली that contains the specअगरied leaf.
	 */
	budsz = BUDSIZE(size, tp->dmt_budmin);

	/* back split.
	 */
	जबतक (leaf[leafno] == NOFREE) अणु
		/* find the lefपंचांगost buddy leaf.
		 */
		क्रम (w = leafno, bsz = budsz;; bsz <<= 1,
		     w = (w < bud) ? w : bud) अणु
			अगर (bsz >= le32_to_cpu(tp->dmt_nleafs)) अणु
				jfs_err("JFS: block map error in dbBackSplit");
				वापस -EIO;
			पूर्ण

			/* determine the buddy.
			 */
			bud = w ^ bsz;

			/* check अगर this buddy is the start of the प्रणाली.
			 */
			अगर (leaf[bud] != NOFREE) अणु
				/* split the leaf at the start of the
				 * प्रणाली in two.
				 */
				cursz = leaf[bud] - 1;
				dbSplit(tp, bud, cursz, cursz);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (leaf[leafno] != size) अणु
		jfs_err("JFS: wrong leaf value in dbBackSplit");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * NAME:	dbJoin()
 *
 * FUNCTION:	update the leaf of a dmtree with a new value, joining
 *		the leaf with other leaves of the dmtree पूर्णांकo a multi-leaf
 *		binary buddy प्रणाली, as required.
 *
 * PARAMETERS:
 *	tp	- poपूर्णांकer to the tree containing the leaf.
 *	leafno	- the number of the leaf to be updated.
 *	newval	- the new value क्रम the leaf.
 *
 * RETURN VALUES: none
 */
अटल पूर्णांक dbJoin(dmtree_t * tp, पूर्णांक leafno, पूर्णांक newval)
अणु
	पूर्णांक budsz, buddy;
	s8 *leaf;

	/* can the new leaf value require a join with other leaves ?
	 */
	अगर (newval >= tp->dmt_budmin) अणु
		/* pickup a poपूर्णांकer to the leaves of the tree.
		 */
		leaf = tp->dmt_stree + le32_to_cpu(tp->dmt_leafidx);

		/* try to join the specअगरied leaf पूर्णांकo a large binary
		 * buddy प्रणाली.  the join proceeds by attempting to join
		 * the specअगरied leafno with its buddy (leaf) at new value.
		 * अगर the join occurs, we attempt to join the left leaf
		 * of the joined buddies with its buddy at new value + 1.
		 * we जारी to join until we find a buddy that cannot be
		 * joined (करोes not have a value equal to the size of the
		 * last join) or until all leaves have been joined पूर्णांकo a
		 * single प्रणाली.
		 *
		 * get the buddy size (number of words covered) of
		 * the new value.
		 */
		budsz = BUDSIZE(newval, tp->dmt_budmin);

		/* try to join.
		 */
		जबतक (budsz < le32_to_cpu(tp->dmt_nleafs)) अणु
			/* get the buddy leaf.
			 */
			buddy = leafno ^ budsz;

			/* अगर the leaf's new value is greater than its
			 * buddy's value, we join no more.
			 */
			अगर (newval > leaf[buddy])
				अवरोध;

			/* It shouldn't be less */
			अगर (newval < leaf[buddy])
				वापस -EIO;

			/* check which (leafno or buddy) is the left buddy.
			 * the left buddy माला_लो to claim the blocks resulting
			 * from the join जबतक the right माला_लो to claim none.
			 * the left buddy is also eligible to participate in
			 * a join at the next higher level जबतक the right
			 * is not.
			 *
			 */
			अगर (leafno < buddy) अणु
				/* leafno is the left buddy.
				 */
				dbAdjTree(tp, buddy, NOFREE);
			पूर्ण अन्यथा अणु
				/* buddy is the left buddy and becomes
				 * leafno.
				 */
				dbAdjTree(tp, leafno, NOFREE);
				leafno = buddy;
			पूर्ण

			/* on to try the next join.
			 */
			newval += 1;
			budsz <<= 1;
		पूर्ण
	पूर्ण

	/* update the leaf value.
	 */
	dbAdjTree(tp, leafno, newval);

	वापस 0;
पूर्ण


/*
 * NAME:	dbAdjTree()
 *
 * FUNCTION:	update a leaf of a dmtree with a new value, adjusting
 *		the dmtree, as required, to reflect the new leaf value.
 *		the combination of any buddies must alपढ़ोy be करोne beक्रमe
 *		this is called.
 *
 * PARAMETERS:
 *	tp	- poपूर्णांकer to the tree to be adjusted.
 *	leafno	- the number of the leaf to be updated.
 *	newval	- the new value क्रम the leaf.
 *
 * RETURN VALUES: none
 */
अटल व्योम dbAdjTree(dmtree_t * tp, पूर्णांक leafno, पूर्णांक newval)
अणु
	पूर्णांक lp, pp, k;
	पूर्णांक max;

	/* pick up the index of the leaf क्रम this leafno.
	 */
	lp = leafno + le32_to_cpu(tp->dmt_leafidx);

	/* is the current value the same as the old value ?  अगर so,
	 * there is nothing to करो.
	 */
	अगर (tp->dmt_stree[lp] == newval)
		वापस;

	/* set the new value.
	 */
	tp->dmt_stree[lp] = newval;

	/* bubble the new value up the tree as required.
	 */
	क्रम (k = 0; k < le32_to_cpu(tp->dmt_height); k++) अणु
		/* get the index of the first leaf of the 4 leaf
		 * group containing the specअगरied leaf (leafno).
		 */
		lp = ((lp - 1) & ~0x03) + 1;

		/* get the index of the parent of this 4 leaf group.
		 */
		pp = (lp - 1) >> 2;

		/* determine the maximum of the 4 leaves.
		 */
		max = TREEMAX(&tp->dmt_stree[lp]);

		/* अगर the maximum of the 4 is the same as the
		 * parent's value, we're करोne.
		 */
		अगर (tp->dmt_stree[pp] == max)
			अवरोध;

		/* parent माला_लो new value.
		 */
		tp->dmt_stree[pp] = max;

		/* parent becomes leaf क्रम next go-round.
		 */
		lp = pp;
	पूर्ण
पूर्ण


/*
 * NAME:	dbFindLeaf()
 *
 * FUNCTION:	search a dmtree_t क्रम sufficient मुक्त blocks, वापसing
 *		the index of a leaf describing the मुक्त blocks अगर
 *		sufficient मुक्त blocks are found.
 *
 *		the search starts at the top of the dmtree_t tree and
 *		proceeds करोwn the tree to the lefपंचांगost leaf with sufficient
 *		मुक्त space.
 *
 * PARAMETERS:
 *	tp	- poपूर्णांकer to the tree to be searched.
 *	l2nb	- log2 number of मुक्त blocks to search क्रम.
 *	leafidx	- वापस poपूर्णांकer to be set to the index of the leaf
 *		  describing at least l2nb मुक्त blocks अगर sufficient
 *		  मुक्त blocks are found.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOSPC	- insufficient मुक्त blocks.
 */
अटल पूर्णांक dbFindLeaf(dmtree_t * tp, पूर्णांक l2nb, पूर्णांक *leafidx)
अणु
	पूर्णांक ti, n = 0, k, x = 0;

	/* first check the root of the tree to see अगर there is
	 * sufficient मुक्त space.
	 */
	अगर (l2nb > tp->dmt_stree[ROOT])
		वापस -ENOSPC;

	/* sufficient मुक्त space available. now search करोwn the tree
	 * starting at the next level क्रम the lefपंचांगost leaf that
	 * describes sufficient मुक्त space.
	 */
	क्रम (k = le32_to_cpu(tp->dmt_height), ti = 1;
	     k > 0; k--, ti = ((ti + n) << 2) + 1) अणु
		/* search the four nodes at this level, starting from
		 * the left.
		 */
		क्रम (x = ti, n = 0; n < 4; n++) अणु
			/* sufficient मुक्त space found.  move to the next
			 * level (or quit अगर this is the last level).
			 */
			अगर (l2nb <= tp->dmt_stree[x + n])
				अवरोध;
		पूर्ण

		/* better have found something since the higher
		 * levels of the tree said it was here.
		 */
		निश्चित(n < 4);
	पूर्ण

	/* set the वापस to the lefपंचांगost leaf describing sufficient
	 * मुक्त space.
	 */
	*leafidx = x + n - le32_to_cpu(tp->dmt_leafidx);

	वापस (0);
पूर्ण


/*
 * NAME:	dbFindBits()
 *
 * FUNCTION:	find a specअगरied number of binary buddy मुक्त bits within a
 *		dmap biपंचांगap word value.
 *
 *		this routine searches the biपंचांगap value क्रम (1 << l2nb) मुक्त
 *		bits at (1 << l2nb) alignments within the value.
 *
 * PARAMETERS:
 *	word	-  dmap biपंचांगap word value.
 *	l2nb	-  number of मुक्त bits specअगरied as a log2 number.
 *
 * RETURN VALUES:
 *	starting bit number of मुक्त bits.
 */
अटल पूर्णांक dbFindBits(u32 word, पूर्णांक l2nb)
अणु
	पूर्णांक bitno, nb;
	u32 mask;

	/* get the number of bits.
	 */
	nb = 1 << l2nb;
	निश्चित(nb <= DBWORD);

	/* complement the word so we can use a mask (i.e. 0s represent
	 * मुक्त bits) and compute the mask.
	 */
	word = ~word;
	mask = ONES << (DBWORD - nb);

	/* scan the word क्रम nb मुक्त bits at nb alignments.
	 */
	क्रम (bitno = 0; mask != 0; bitno += nb, mask >>= nb) अणु
		अगर ((mask & word) == mask)
			अवरोध;
	पूर्ण

	ASSERT(bitno < 32);

	/* वापस the bit number.
	 */
	वापस (bitno);
पूर्ण


/*
 * NAME:	dbMaxBud(u8 *cp)
 *
 * FUNCTION:	determine the largest binary buddy string of मुक्त
 *		bits within 32-bits of the map.
 *
 * PARAMETERS:
 *	cp	-  poपूर्णांकer to the 32-bit value.
 *
 * RETURN VALUES:
 *	largest binary buddy of मुक्त bits within a dmap word.
 */
अटल पूर्णांक dbMaxBud(u8 * cp)
अणु
	चिन्हित अक्षर पंचांगp1, पंचांगp2;

	/* check अगर the wmap word is all मुक्त. अगर so, the
	 * मुक्त buddy size is BUDMIN.
	 */
	अगर (*((uपूर्णांक *) cp) == 0)
		वापस (BUDMIN);

	/* check अगर the wmap word is half मुक्त. अगर so, the
	 * मुक्त buddy size is BUDMIN-1.
	 */
	अगर (*((u16 *) cp) == 0 || *((u16 *) cp + 1) == 0)
		वापस (BUDMIN - 1);

	/* not all मुक्त or half मुक्त. determine the मुक्त buddy
	 * size thru table lookup using quarters of the wmap word.
	 */
	पंचांगp1 = max(budtab[cp[2]], budtab[cp[3]]);
	पंचांगp2 = max(budtab[cp[0]], budtab[cp[1]]);
	वापस (max(पंचांगp1, पंचांगp2));
पूर्ण


/*
 * NAME:	cnttz(uपूर्णांक word)
 *
 * FUNCTION:	determine the number of trailing zeros within a 32-bit
 *		value.
 *
 * PARAMETERS:
 *	value	-  32-bit value to be examined.
 *
 * RETURN VALUES:
 *	count of trailing zeros
 */
अटल पूर्णांक cnttz(u32 word)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < 32; n++, word >>= 1) अणु
		अगर (word & 0x01)
			अवरोध;
	पूर्ण

	वापस (n);
पूर्ण


/*
 * NAME:	cntlz(u32 value)
 *
 * FUNCTION:	determine the number of leading zeros within a 32-bit
 *		value.
 *
 * PARAMETERS:
 *	value	-  32-bit value to be examined.
 *
 * RETURN VALUES:
 *	count of leading zeros
 */
अटल पूर्णांक cntlz(u32 value)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < 32; n++, value <<= 1) अणु
		अगर (value & HIGHORDER)
			अवरोध;
	पूर्ण
	वापस (n);
पूर्ण


/*
 * NAME:	blkstol2(s64 nb)
 *
 * FUNCTION:	convert a block count to its log2 value. अगर the block
 *		count is not a l2 multiple, it is rounded up to the next
 *		larger l2 multiple.
 *
 * PARAMETERS:
 *	nb	-  number of blocks
 *
 * RETURN VALUES:
 *	log2 number of blocks
 */
अटल पूर्णांक blkstol2(s64 nb)
अणु
	पूर्णांक l2nb;
	s64 mask;		/* meant to be चिन्हित */

	mask = (s64) 1 << (64 - 1);

	/* count the leading bits.
	 */
	क्रम (l2nb = 0; l2nb < 64; l2nb++, mask >>= 1) अणु
		/* leading bit found.
		 */
		अगर (nb & mask) अणु
			/* determine the l2 value.
			 */
			l2nb = (64 - 1) - l2nb;

			/* check अगर we need to round up.
			 */
			अगर (~mask & nb)
				l2nb++;

			वापस (l2nb);
		पूर्ण
	पूर्ण
	निश्चित(0);
	वापस 0;		/* fix compiler warning */
पूर्ण


/*
 * NAME:	dbAllocBottomUp()
 *
 * FUNCTION:	alloc the specअगरied block range from the working block
 *		allocation map.
 *
 *		the blocks will be alloc from the working map one dmap
 *		at a समय.
 *
 * PARAMETERS:
 *	ip	-  poपूर्णांकer to in-core inode;
 *	blkno	-  starting block number to be मुक्तd.
 *	nblocks	-  number of blocks to be मुक्तd.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error
 */
पूर्णांक dbAllocBottomUp(काष्ठा inode *ip, s64 blkno, s64 nblocks)
अणु
	काष्ठा metapage *mp;
	काष्ठा dmap *dp;
	पूर्णांक nb, rc;
	s64 lblkno, rem;
	काष्ठा inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	काष्ठा bmap *bmp = JFS_SBI(ip->i_sb)->bmap;

	IREAD_LOCK(ipbmap, RDWRLOCK_DMAP);

	/* block to be allocated better be within the mapsize. */
	ASSERT(nblocks <= bmp->db_mapsize - blkno);

	/*
	 * allocate the blocks a dmap at a समय.
	 */
	mp = शून्य;
	क्रम (rem = nblocks; rem > 0; rem -= nb, blkno += nb) अणु
		/* release previous dmap अगर any */
		अगर (mp) अणु
			ग_लिखो_metapage(mp);
		पूर्ण

		/* get the buffer क्रम the current dmap. */
		lblkno = BLKTODMAP(blkno, bmp->db_l2nbperpage);
		mp = पढ़ो_metapage(ipbmap, lblkno, PSIZE, 0);
		अगर (mp == शून्य) अणु
			IREAD_UNLOCK(ipbmap);
			वापस -EIO;
		पूर्ण
		dp = (काष्ठा dmap *) mp->data;

		/* determine the number of blocks to be allocated from
		 * this dmap.
		 */
		nb = min(rem, BPERDMAP - (blkno & (BPERDMAP - 1)));

		/* allocate the blocks. */
		अगर ((rc = dbAllocDmapBU(bmp, dp, blkno, nb))) अणु
			release_metapage(mp);
			IREAD_UNLOCK(ipbmap);
			वापस (rc);
		पूर्ण
	पूर्ण

	/* ग_लिखो the last buffer. */
	ग_लिखो_metapage(mp);

	IREAD_UNLOCK(ipbmap);

	वापस (0);
पूर्ण


अटल पूर्णांक dbAllocDmapBU(काष्ठा bmap * bmp, काष्ठा dmap * dp, s64 blkno,
			 पूर्णांक nblocks)
अणु
	पूर्णांक rc;
	पूर्णांक dbitno, word, rembits, nb, nwords, wbitno, agno;
	s8 oldroot;
	काष्ठा dmaptree *tp = (काष्ठा dmaptree *) & dp->tree;

	/* save the current value of the root (i.e. maximum मुक्त string)
	 * of the dmap tree.
	 */
	oldroot = tp->stree[ROOT];

	/* determine the bit number and word within the dmap of the
	 * starting block.
	 */
	dbitno = blkno & (BPERDMAP - 1);
	word = dbitno >> L2DBWORD;

	/* block range better be within the dmap */
	निश्चित(dbitno + nblocks <= BPERDMAP);

	/* allocate the bits of the dmap's words corresponding to the block
	 * range. not all bits of the first and last words may be contained
	 * within the block range.  अगर this is the हाल, we'll work against
	 * those words (i.e. partial first and/or last) on an inभागidual basis
	 * (a single pass), allocating the bits of पूर्णांकerest by hand and
	 * updating the leaf corresponding to the dmap word. a single pass
	 * will be used क्रम all dmap words fully contained within the
	 * specअगरied range.  within this pass, the bits of all fully contained
	 * dmap words will be marked as मुक्त in a single shot and the leaves
	 * will be updated. a single leaf may describe the मुक्त space of
	 * multiple dmap words, so we may update only a subset of the actual
	 * leaves corresponding to the dmap words of the block range.
	 */
	क्रम (rembits = nblocks; rembits > 0; rembits -= nb, dbitno += nb) अणु
		/* determine the bit number within the word and
		 * the number of bits within the word.
		 */
		wbitno = dbitno & (DBWORD - 1);
		nb = min(rembits, DBWORD - wbitno);

		/* check अगर only part of a word is to be allocated.
		 */
		अगर (nb < DBWORD) अणु
			/* allocate (set to 1) the appropriate bits within
			 * this dmap word.
			 */
			dp->wmap[word] |= cpu_to_le32(ONES << (DBWORD - nb)
						      >> wbitno);

			word++;
		पूर्ण अन्यथा अणु
			/* one or more dmap words are fully contained
			 * within the block range.  determine how many
			 * words and allocate (set to 1) the bits of these
			 * words.
			 */
			nwords = rembits >> L2DBWORD;
			स_रखो(&dp->wmap[word], (पूर्णांक) ONES, nwords * 4);

			/* determine how many bits */
			nb = nwords << L2DBWORD;
			word += nwords;
		पूर्ण
	पूर्ण

	/* update the मुक्त count क्रम this dmap */
	le32_add_cpu(&dp->nमुक्त, -nblocks);

	/* reस्थिरruct summary tree */
	dbInitDmapTree(dp);

	BMAP_LOCK(bmp);

	/* अगर this allocation group is completely मुक्त,
	 * update the highest active allocation group number
	 * अगर this allocation group is the new max.
	 */
	agno = blkno >> bmp->db_agl2size;
	अगर (agno > bmp->db_maxag)
		bmp->db_maxag = agno;

	/* update the मुक्त count क्रम the allocation group and map */
	bmp->db_agमुक्त[agno] -= nblocks;
	bmp->db_nमुक्त -= nblocks;

	BMAP_UNLOCK(bmp);

	/* अगर the root has not changed, करोne. */
	अगर (tp->stree[ROOT] == oldroot)
		वापस (0);

	/* root changed. bubble the change up to the dmap control pages.
	 * अगर the adjusपंचांगent of the upper level control pages fails,
	 * backout the bit allocation (thus making everything consistent).
	 */
	अगर ((rc = dbAdjCtl(bmp, blkno, tp->stree[ROOT], 1, 0)))
		dbFreeBits(bmp, dp, blkno, nblocks);

	वापस (rc);
पूर्ण


/*
 * NAME:	dbExtendFS()
 *
 * FUNCTION:	extend bmap from blkno क्रम nblocks;
 *		dbExtendFS() updates bmap पढ़ोy क्रम dbAllocBottomUp();
 *
 * L2
 *  |
 *   L1---------------------------------L1
 *    |					 |
 *     L0---------L0---------L0		  L0---------L0---------L0
 *      |	   |	      |		   |	      |		 |
 *	 d0,...,dn  d0,...,dn  d0,...,dn    d0,...,dn  d0,...,dn  d0,.,dm;
 * L2L1L0d0,...,dnL0d0,...,dnL0d0,...,dnL1L0d0,...,dnL0d0,...,dnL0d0,..dm
 *
 * <---old---><----------------------------extend----------------------->
 */
पूर्णांक dbExtendFS(काष्ठा inode *ipbmap, s64 blkno,	s64 nblocks)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ipbmap->i_sb);
	पूर्णांक nbperpage = sbi->nbperpage;
	पूर्णांक i, i0 = true, j, j0 = true, k, n;
	s64 newsize;
	s64 p;
	काष्ठा metapage *mp, *l2mp, *l1mp = शून्य, *l0mp = शून्य;
	काष्ठा dmapctl *l2dcp, *l1dcp, *l0dcp;
	काष्ठा dmap *dp;
	s8 *l0leaf, *l1leaf, *l2leaf;
	काष्ठा bmap *bmp = sbi->bmap;
	पूर्णांक agno, l2agsize, oldl2agsize;
	s64 ag_rem;

	newsize = blkno + nblocks;

	jfs_info("dbExtendFS: blkno:%Ld nblocks:%Ld newsize:%Ld",
		 (दीर्घ दीर्घ) blkno, (दीर्घ दीर्घ) nblocks, (दीर्घ दीर्घ) newsize);

	/*
	 *	initialize bmap control page.
	 *
	 * all the data in bmap control page should exclude
	 * the mkfs hidden dmap page.
	 */

	/* update mapsize */
	bmp->db_mapsize = newsize;
	bmp->db_maxlevel = BMAPSZTOLEV(bmp->db_mapsize);

	/* compute new AG size */
	l2agsize = dbGetL2AGSize(newsize);
	oldl2agsize = bmp->db_agl2size;

	bmp->db_agl2size = l2agsize;
	bmp->db_agsize = 1 << l2agsize;

	/* compute new number of AG */
	agno = bmp->db_numag;
	bmp->db_numag = newsize >> l2agsize;
	bmp->db_numag += ((u32) newsize % (u32) bmp->db_agsize) ? 1 : 0;

	/*
	 *	reconfigure db_agमुक्त[]
	 * from old AG configuration to new AG configuration;
	 *
	 * coalesce contiguous k (newAGSize/oldAGSize) AGs;
	 * i.e., (AGi, ..., AGj) where i = k*n and j = k*(n+1) - 1 to AGn;
	 * note: new AG size = old AG size * (2**x).
	 */
	अगर (l2agsize == oldl2agsize)
		जाओ extend;
	k = 1 << (l2agsize - oldl2agsize);
	ag_rem = bmp->db_agमुक्त[0];	/* save agमुक्त[0] */
	क्रम (i = 0, n = 0; i < agno; n++) अणु
		bmp->db_agमुक्त[n] = 0;	/* init collection poपूर्णांक */

		/* coalesce contiguous k AGs; */
		क्रम (j = 0; j < k && i < agno; j++, i++) अणु
			/* merge AGi to AGn */
			bmp->db_agमुक्त[n] += bmp->db_agमुक्त[i];
		पूर्ण
	पूर्ण
	bmp->db_agमुक्त[0] += ag_rem;	/* restore agमुक्त[0] */

	क्रम (; n < MAXAG; n++)
		bmp->db_agमुक्त[n] = 0;

	/*
	 * update highest active ag number
	 */

	bmp->db_maxag = bmp->db_maxag / k;

	/*
	 *	extend bmap
	 *
	 * update bit maps and corresponding level control pages;
	 * global control page db_nमुक्त, db_agमुक्त[agno], db_maxमुक्तbud;
	 */
      extend:
	/* get L2 page */
	p = BMAPBLKNO + nbperpage;	/* L2 page */
	l2mp = पढ़ो_metapage(ipbmap, p, PSIZE, 0);
	अगर (!l2mp) अणु
		jfs_error(ipbmap->i_sb, "L2 page could not be read\n");
		वापस -EIO;
	पूर्ण
	l2dcp = (काष्ठा dmapctl *) l2mp->data;

	/* compute start L1 */
	k = blkno >> L2MAXL1SIZE;
	l2leaf = l2dcp->stree + CTLLEAFIND + k;
	p = BLKTOL1(blkno, sbi->l2nbperpage);	/* L1 page */

	/*
	 * extend each L1 in L2
	 */
	क्रम (; k < LPERCTL; k++, p += nbperpage) अणु
		/* get L1 page */
		अगर (j0) अणु
			/* पढ़ो in L1 page: (blkno & (MAXL1SIZE - 1)) */
			l1mp = पढ़ो_metapage(ipbmap, p, PSIZE, 0);
			अगर (l1mp == शून्य)
				जाओ errout;
			l1dcp = (काष्ठा dmapctl *) l1mp->data;

			/* compute start L0 */
			j = (blkno & (MAXL1SIZE - 1)) >> L2MAXL0SIZE;
			l1leaf = l1dcp->stree + CTLLEAFIND + j;
			p = BLKTOL0(blkno, sbi->l2nbperpage);
			j0 = false;
		पूर्ण अन्यथा अणु
			/* assign/init L1 page */
			l1mp = get_metapage(ipbmap, p, PSIZE, 0);
			अगर (l1mp == शून्य)
				जाओ errout;

			l1dcp = (काष्ठा dmapctl *) l1mp->data;

			/* compute start L0 */
			j = 0;
			l1leaf = l1dcp->stree + CTLLEAFIND;
			p += nbperpage;	/* 1st L0 of L1.k */
		पूर्ण

		/*
		 * extend each L0 in L1
		 */
		क्रम (; j < LPERCTL; j++) अणु
			/* get L0 page */
			अगर (i0) अणु
				/* पढ़ो in L0 page: (blkno & (MAXL0SIZE - 1)) */

				l0mp = पढ़ो_metapage(ipbmap, p, PSIZE, 0);
				अगर (l0mp == शून्य)
					जाओ errout;
				l0dcp = (काष्ठा dmapctl *) l0mp->data;

				/* compute start dmap */
				i = (blkno & (MAXL0SIZE - 1)) >>
				    L2BPERDMAP;
				l0leaf = l0dcp->stree + CTLLEAFIND + i;
				p = BLKTODMAP(blkno,
					      sbi->l2nbperpage);
				i0 = false;
			पूर्ण अन्यथा अणु
				/* assign/init L0 page */
				l0mp = get_metapage(ipbmap, p, PSIZE, 0);
				अगर (l0mp == शून्य)
					जाओ errout;

				l0dcp = (काष्ठा dmapctl *) l0mp->data;

				/* compute start dmap */
				i = 0;
				l0leaf = l0dcp->stree + CTLLEAFIND;
				p += nbperpage;	/* 1st dmap of L0.j */
			पूर्ण

			/*
			 * extend each dmap in L0
			 */
			क्रम (; i < LPERCTL; i++) अणु
				/*
				 * reस्थिरruct the dmap page, and
				 * initialize corresponding parent L0 leaf
				 */
				अगर ((n = blkno & (BPERDMAP - 1))) अणु
					/* पढ़ो in dmap page: */
					mp = पढ़ो_metapage(ipbmap, p,
							   PSIZE, 0);
					अगर (mp == शून्य)
						जाओ errout;
					n = min(nblocks, (s64)BPERDMAP - n);
				पूर्ण अन्यथा अणु
					/* assign/init dmap page */
					mp = पढ़ो_metapage(ipbmap, p,
							   PSIZE, 0);
					अगर (mp == शून्य)
						जाओ errout;

					n = min_t(s64, nblocks, BPERDMAP);
				पूर्ण

				dp = (काष्ठा dmap *) mp->data;
				*l0leaf = dbInitDmap(dp, blkno, n);

				bmp->db_nमुक्त += n;
				agno = le64_to_cpu(dp->start) >> l2agsize;
				bmp->db_agमुक्त[agno] += n;

				ग_लिखो_metapage(mp);

				l0leaf++;
				p += nbperpage;

				blkno += n;
				nblocks -= n;
				अगर (nblocks == 0)
					अवरोध;
			पूर्ण	/* क्रम each dmap in a L0 */

			/*
			 * build current L0 page from its leaves, and
			 * initialize corresponding parent L1 leaf
			 */
			*l1leaf = dbInitDmapCtl(l0dcp, 0, ++i);
			ग_लिखो_metapage(l0mp);
			l0mp = शून्य;

			अगर (nblocks)
				l1leaf++;	/* जारी क्रम next L0 */
			अन्यथा अणु
				/* more than 1 L0 ? */
				अगर (j > 0)
					अवरोध;	/* build L1 page */
				अन्यथा अणु
					/* summarize in global bmap page */
					bmp->db_maxमुक्तbud = *l1leaf;
					release_metapage(l1mp);
					release_metapage(l2mp);
					जाओ finalize;
				पूर्ण
			पूर्ण
		पूर्ण		/* क्रम each L0 in a L1 */

		/*
		 * build current L1 page from its leaves, and
		 * initialize corresponding parent L2 leaf
		 */
		*l2leaf = dbInitDmapCtl(l1dcp, 1, ++j);
		ग_लिखो_metapage(l1mp);
		l1mp = शून्य;

		अगर (nblocks)
			l2leaf++;	/* जारी क्रम next L1 */
		अन्यथा अणु
			/* more than 1 L1 ? */
			अगर (k > 0)
				अवरोध;	/* build L2 page */
			अन्यथा अणु
				/* summarize in global bmap page */
				bmp->db_maxमुक्तbud = *l2leaf;
				release_metapage(l2mp);
				जाओ finalize;
			पूर्ण
		पूर्ण
	पूर्ण			/* क्रम each L1 in a L2 */

	jfs_error(ipbmap->i_sb, "function has not returned as expected\n");
errout:
	अगर (l0mp)
		release_metapage(l0mp);
	अगर (l1mp)
		release_metapage(l1mp);
	release_metapage(l2mp);
	वापस -EIO;

	/*
	 *	finalize bmap control page
	 */
finalize:

	वापस 0;
पूर्ण


/*
 *	dbFinalizeBmap()
 */
व्योम dbFinalizeBmap(काष्ठा inode *ipbmap)
अणु
	काष्ठा bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;
	पूर्णांक actags, inactags, l2nl;
	s64 ag_rem, actमुक्त, inactमुक्त, avgमुक्त;
	पूर्णांक i, n;

	/*
	 *	finalize bmap control page
	 */
//finalize:
	/*
	 * compute db_agpref: preferred ag to allocate from
	 * (the lefपंचांगost ag with average मुक्त space in it);
	 */
//agpref:
	/* get the number of active ags and inacitve ags */
	actags = bmp->db_maxag + 1;
	inactags = bmp->db_numag - actags;
	ag_rem = bmp->db_mapsize & (bmp->db_agsize - 1);	/* ??? */

	/* determine how many blocks are in the inactive allocation
	 * groups. in करोing this, we must account क्रम the fact that
	 * the righपंचांगost group might be a partial group (i.e. file
	 * प्रणाली size is not a multiple of the group size).
	 */
	inactमुक्त = (inactags && ag_rem) ?
	    ((inactags - 1) << bmp->db_agl2size) + ag_rem
	    : inactags << bmp->db_agl2size;

	/* determine how many मुक्त blocks are in the active
	 * allocation groups plus the average number of मुक्त blocks
	 * within the active ags.
	 */
	actमुक्त = bmp->db_nमुक्त - inactमुक्त;
	avgमुक्त = (u32) actमुक्त / (u32) actags;

	/* अगर the preferred allocation group has not average मुक्त space.
	 * re-establish the preferred group as the lefपंचांगost
	 * group with average मुक्त space.
	 */
	अगर (bmp->db_agमुक्त[bmp->db_agpref] < avgमुक्त) अणु
		क्रम (bmp->db_agpref = 0; bmp->db_agpref < actags;
		     bmp->db_agpref++) अणु
			अगर (bmp->db_agमुक्त[bmp->db_agpref] >= avgमुक्त)
				अवरोध;
		पूर्ण
		अगर (bmp->db_agpref >= bmp->db_numag) अणु
			jfs_error(ipbmap->i_sb,
				  "cannot find ag with average freespace\n");
		पूर्ण
	पूर्ण

	/*
	 * compute db_aglevel, db_agheight, db_width, db_agstart:
	 * an ag is covered in aglevel dmapctl summary tree,
	 * at agheight level height (from leaf) with agwidth number of nodes
	 * each, which starts at agstart index node of the smmary tree node
	 * array;
	 */
	bmp->db_aglevel = BMAPSZTOLEV(bmp->db_agsize);
	l2nl =
	    bmp->db_agl2size - (L2BPERDMAP + bmp->db_aglevel * L2LPERCTL);
	bmp->db_agheight = l2nl >> 1;
	bmp->db_agwidth = 1 << (l2nl - (bmp->db_agheight << 1));
	क्रम (i = 5 - bmp->db_agheight, bmp->db_agstart = 0, n = 1; i > 0;
	     i--) अणु
		bmp->db_agstart += n;
		n <<= 2;
	पूर्ण

पूर्ण


/*
 * NAME:	dbInitDmap()/ujfs_idmap_page()
 *
 * FUNCTION:	initialize working/persistent biपंचांगap of the dmap page
 *		क्रम the specअगरied number of blocks:
 *
 *		at entry, the biपंचांगaps had been initialized as मुक्त (ZEROS);
 *		The number of blocks will only account क्रम the actually
 *		existing blocks. Blocks which करोn't actually exist in
 *		the aggregate will be marked as allocated (ONES);
 *
 * PARAMETERS:
 *	dp	- poपूर्णांकer to page of map
 *	nblocks	- number of blocks this page
 *
 * RETURNS: NONE
 */
अटल पूर्णांक dbInitDmap(काष्ठा dmap * dp, s64 Blkno, पूर्णांक nblocks)
अणु
	पूर्णांक blkno, w, b, r, nw, nb, i;

	/* starting block number within the dmap */
	blkno = Blkno & (BPERDMAP - 1);

	अगर (blkno == 0) अणु
		dp->nblocks = dp->nमुक्त = cpu_to_le32(nblocks);
		dp->start = cpu_to_le64(Blkno);

		अगर (nblocks == BPERDMAP) अणु
			स_रखो(&dp->wmap[0], 0, LPERDMAP * 4);
			स_रखो(&dp->pmap[0], 0, LPERDMAP * 4);
			जाओ initTree;
		पूर्ण
	पूर्ण अन्यथा अणु
		le32_add_cpu(&dp->nblocks, nblocks);
		le32_add_cpu(&dp->nमुक्त, nblocks);
	पूर्ण

	/* word number containing start block number */
	w = blkno >> L2DBWORD;

	/*
	 * मुक्त the bits corresponding to the block range (ZEROS):
	 * note: not all bits of the first and last words may be contained
	 * within the block range.
	 */
	क्रम (r = nblocks; r > 0; r -= nb, blkno += nb) अणु
		/* number of bits preceding range to be मुक्तd in the word */
		b = blkno & (DBWORD - 1);
		/* number of bits to मुक्त in the word */
		nb = min(r, DBWORD - b);

		/* is partial word to be मुक्तd ? */
		अगर (nb < DBWORD) अणु
			/* मुक्त (set to 0) from the biपंचांगap word */
			dp->wmap[w] &= cpu_to_le32(~(ONES << (DBWORD - nb)
						     >> b));
			dp->pmap[w] &= cpu_to_le32(~(ONES << (DBWORD - nb)
						     >> b));

			/* skip the word मुक्तd */
			w++;
		पूर्ण अन्यथा अणु
			/* मुक्त (set to 0) contiguous biपंचांगap words */
			nw = r >> L2DBWORD;
			स_रखो(&dp->wmap[w], 0, nw * 4);
			स_रखो(&dp->pmap[w], 0, nw * 4);

			/* skip the words मुक्तd */
			nb = nw << L2DBWORD;
			w += nw;
		पूर्ण
	पूर्ण

	/*
	 * mark bits following the range to be मुक्तd (non-existing
	 * blocks) as allocated (ONES)
	 */

	अगर (blkno == BPERDMAP)
		जाओ initTree;

	/* the first word beyond the end of existing blocks */
	w = blkno >> L2DBWORD;

	/* करोes nblocks fall on a 32-bit boundary ? */
	b = blkno & (DBWORD - 1);
	अगर (b) अणु
		/* mark a partial word allocated */
		dp->wmap[w] = dp->pmap[w] = cpu_to_le32(ONES >> b);
		w++;
	पूर्ण

	/* set the rest of the words in the page to allocated (ONES) */
	क्रम (i = w; i < LPERDMAP; i++)
		dp->pmap[i] = dp->wmap[i] = cpu_to_le32(ONES);

	/*
	 * init tree
	 */
      initTree:
	वापस (dbInitDmapTree(dp));
पूर्ण


/*
 * NAME:	dbInitDmapTree()/ujfs_complete_dmap()
 *
 * FUNCTION:	initialize summary tree of the specअगरied dmap:
 *
 *		at entry, biपंचांगap of the dmap has been initialized;
 *
 * PARAMETERS:
 *	dp	- dmap to complete
 *	blkno	- starting block number क्रम this dmap
 *	treemax	- will be filled in with max मुक्त क्रम this dmap
 *
 * RETURNS:	max मुक्त string at the root of the tree
 */
अटल पूर्णांक dbInitDmapTree(काष्ठा dmap * dp)
अणु
	काष्ठा dmaptree *tp;
	s8 *cp;
	पूर्णांक i;

	/* init fixed info of tree */
	tp = &dp->tree;
	tp->nleafs = cpu_to_le32(LPERDMAP);
	tp->l2nleafs = cpu_to_le32(L2LPERDMAP);
	tp->leafidx = cpu_to_le32(LEAFIND);
	tp->height = cpu_to_le32(4);
	tp->budmin = BUDMIN;

	/* init each leaf from corresponding wmap word:
	 * note: leaf is set to NOFREE(-1) अगर all blocks of corresponding
	 * biपंचांगap word are allocated.
	 */
	cp = tp->stree + le32_to_cpu(tp->leafidx);
	क्रम (i = 0; i < LPERDMAP; i++)
		*cp++ = dbMaxBud((u8 *) & dp->wmap[i]);

	/* build the dmap's binary buddy summary tree */
	वापस (dbInitTree(tp));
पूर्ण


/*
 * NAME:	dbInitTree()/ujfs_adjtree()
 *
 * FUNCTION:	initialize binary buddy summary tree of a dmap or dmapctl.
 *
 *		at entry, the leaves of the tree has been initialized
 *		from corresponding biपंचांगap word or root of summary tree
 *		of the child control page;
 *		configure binary buddy प्रणाली at the leaf level, then
 *		bubble up the values of the leaf nodes up the tree.
 *
 * PARAMETERS:
 *	cp	- Poपूर्णांकer to the root of the tree
 *	l2leaves- Number of leaf nodes as a घातer of 2
 *	l2min	- Number of blocks that can be covered by a leaf
 *		  as a घातer of 2
 *
 * RETURNS: max मुक्त string at the root of the tree
 */
अटल पूर्णांक dbInitTree(काष्ठा dmaptree * dtp)
अणु
	पूर्णांक l2max, l2मुक्त, bsize, nextb, i;
	पूर्णांक child, parent, nparent;
	s8 *tp, *cp, *cp1;

	tp = dtp->stree;

	/* Determine the maximum मुक्त string possible क्रम the leaves */
	l2max = le32_to_cpu(dtp->l2nleafs) + dtp->budmin;

	/*
	 * configure the leaf levevl पूर्णांकo binary buddy प्रणाली
	 *
	 * Try to combine buddies starting with a buddy size of 1
	 * (i.e. two leaves). At a buddy size of 1 two buddy leaves
	 * can be combined अगर both buddies have a maximum मुक्त of l2min;
	 * the combination will result in the left-most buddy leaf having
	 * a maximum मुक्त of l2min+1.
	 * After processing all buddies क्रम a given size, process buddies
	 * at the next higher buddy size (i.e. current size * 2) and
	 * the next maximum मुक्त (current मुक्त + 1).
	 * This जारीs until the maximum possible buddy combination
	 * yields maximum मुक्त.
	 */
	क्रम (l2मुक्त = dtp->budmin, bsize = 1; l2मुक्त < l2max;
	     l2मुक्त++, bsize = nextb) अणु
		/* get next buddy size == current buddy pair size */
		nextb = bsize << 1;

		/* scan each adjacent buddy pair at current buddy size */
		क्रम (i = 0, cp = tp + le32_to_cpu(dtp->leafidx);
		     i < le32_to_cpu(dtp->nleafs);
		     i += nextb, cp += nextb) अणु
			/* coalesce अगर both adjacent buddies are max मुक्त */
			अगर (*cp == l2मुक्त && *(cp + bsize) == l2मुक्त) अणु
				*cp = l2मुक्त + 1;	/* left take right */
				*(cp + bsize) = -1;	/* right give left */
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * bubble summary inक्रमmation of leaves up the tree.
	 *
	 * Starting at the leaf node level, the four nodes described by
	 * the higher level parent node are compared क्रम a maximum मुक्त and
	 * this maximum becomes the value of the parent node.
	 * when all lower level nodes are processed in this fashion then
	 * move up to the next level (parent becomes a lower level node) and
	 * जारी the process क्रम that level.
	 */
	क्रम (child = le32_to_cpu(dtp->leafidx),
	     nparent = le32_to_cpu(dtp->nleafs) >> 2;
	     nparent > 0; nparent >>= 2, child = parent) अणु
		/* get index of 1st node of parent level */
		parent = (child - 1) >> 2;

		/* set the value of the parent node as the maximum
		 * of the four nodes of the current level.
		 */
		क्रम (i = 0, cp = tp + child, cp1 = tp + parent;
		     i < nparent; i++, cp += 4, cp1++)
			*cp1 = TREEMAX(cp);
	पूर्ण

	वापस (*tp);
पूर्ण


/*
 *	dbInitDmapCtl()
 *
 * function: initialize dmapctl page
 */
अटल पूर्णांक dbInitDmapCtl(काष्ठा dmapctl * dcp, पूर्णांक level, पूर्णांक i)
अणु				/* start leaf index not covered by range */
	s8 *cp;

	dcp->nleafs = cpu_to_le32(LPERCTL);
	dcp->l2nleafs = cpu_to_le32(L2LPERCTL);
	dcp->leafidx = cpu_to_le32(CTLLEAFIND);
	dcp->height = cpu_to_le32(5);
	dcp->budmin = L2BPERDMAP + L2LPERCTL * level;

	/*
	 * initialize the leaves of current level that were not covered
	 * by the specअगरied input block range (i.e. the leaves have no
	 * low level dmapctl or dmap).
	 */
	cp = &dcp->stree[CTLLEAFIND + i];
	क्रम (; i < LPERCTL; i++)
		*cp++ = NOFREE;

	/* build the dmap's binary buddy summary tree */
	वापस (dbInitTree((काष्ठा dmaptree *) dcp));
पूर्ण


/*
 * NAME:	dbGetL2AGSize()/ujfs_getagl2size()
 *
 * FUNCTION:	Determine log2(allocation group size) from aggregate size
 *
 * PARAMETERS:
 *	nblocks	- Number of blocks in aggregate
 *
 * RETURNS: log2(allocation group size) in aggregate blocks
 */
अटल पूर्णांक dbGetL2AGSize(s64 nblocks)
अणु
	s64 sz;
	s64 m;
	पूर्णांक l2sz;

	अगर (nblocks < BPERDMAP * MAXAG)
		वापस (L2BPERDMAP);

	/* round up aggregate size to घातer of 2 */
	m = ((u64) 1 << (64 - 1));
	क्रम (l2sz = 64; l2sz >= 0; l2sz--, m >>= 1) अणु
		अगर (m & nblocks)
			अवरोध;
	पूर्ण

	sz = (s64) 1 << l2sz;
	अगर (sz < nblocks)
		l2sz += 1;

	/* agsize = roundupSize/max_number_of_ag */
	वापस (l2sz - L2MAXAG);
पूर्ण


/*
 * NAME:	dbMapFileSizeToMapSize()
 *
 * FUNCTION:	compute number of blocks the block allocation map file
 *		can cover from the map file size;
 *
 * RETURNS:	Number of blocks which can be covered by this block map file;
 */

/*
 * maximum number of map pages at each level including control pages
 */
#घोषणा MAXL0PAGES	(1 + LPERCTL)
#घोषणा MAXL1PAGES	(1 + LPERCTL * MAXL0PAGES)

/*
 * convert number of map pages to the zero origin top dmapctl level
 */
#घोषणा BMAPPGTOLEV(npages)	\
	(((npages) <= 3 + MAXL0PAGES) ? 0 : \
	 ((npages) <= 2 + MAXL1PAGES) ? 1 : 2)

s64 dbMapFileSizeToMapSize(काष्ठा inode * ipbmap)
अणु
	काष्ठा super_block *sb = ipbmap->i_sb;
	s64 nblocks;
	s64 npages, ndmaps;
	पूर्णांक level, i;
	पूर्णांक complete, factor;

	nblocks = ipbmap->i_size >> JFS_SBI(sb)->l2bsize;
	npages = nblocks >> JFS_SBI(sb)->l2nbperpage;
	level = BMAPPGTOLEV(npages);

	/* At each level, accumulate the number of dmap pages covered by
	 * the number of full child levels below it;
	 * repeat क्रम the last incomplete child level.
	 */
	ndmaps = 0;
	npages--;		/* skip the first global control page */
	/* skip higher level control pages above top level covered by map */
	npages -= (2 - level);
	npages--;		/* skip top level's control page */
	क्रम (i = level; i >= 0; i--) अणु
		factor =
		    (i == 2) ? MAXL1PAGES : ((i == 1) ? MAXL0PAGES : 1);
		complete = (u32) npages / factor;
		ndmaps += complete * ((i == 2) ? LPERCTL * LPERCTL :
				      ((i == 1) ? LPERCTL : 1));

		/* pages in last/incomplete child */
		npages = (u32) npages % factor;
		/* skip incomplete child's level control page */
		npages--;
	पूर्ण

	/* convert the number of dmaps पूर्णांकo the number of blocks
	 * which can be covered by the dmaps;
	 */
	nblocks = ndmaps << L2BPERDMAP;

	वापस (nblocks);
पूर्ण
