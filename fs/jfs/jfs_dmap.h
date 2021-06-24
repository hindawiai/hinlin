<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2002
 */
#अगर_अघोषित	_H_JFS_DMAP
#घोषणा _H_JFS_DMAP

#समावेश "jfs_txnmgr.h"

#घोषणा BMAPVERSION	1	/* version number */
#घोषणा	TREESIZE	(256+64+16+4+1)	/* size of a dmap tree */
#घोषणा	LEAFIND		(64+16+4+1)	/* index of 1st leaf of a dmap tree */
#घोषणा LPERDMAP	256	/* num leaves per dmap tree */
#घोषणा L2LPERDMAP	8	/* l2 number of leaves per dmap tree */
#घोषणा	DBWORD		32	/* # of blks covered by a map word */
#घोषणा	L2DBWORD	5	/* l2 # of blks covered by a mword */
#घोषणा BUDMIN		L2DBWORD	/* max मुक्त string in a map word */
#घोषणा BPERDMAP	(LPERDMAP * DBWORD)	/* num of blks per dmap */
#घोषणा L2BPERDMAP	13	/* l2 num of blks per dmap */
#घोषणा CTLTREESIZE	(1024+256+64+16+4+1)	/* size of a dmapctl tree */
#घोषणा CTLLEAFIND	(256+64+16+4+1)	/* idx of 1st leaf of a dmapctl tree */
#घोषणा LPERCTL		1024	/* num of leaves per dmapctl tree */
#घोषणा L2LPERCTL	10	/* l2 num of leaves per dmapctl tree */
#घोषणा	ROOT		0	/* index of the root of a tree */
#घोषणा	NOFREE		((s8) -1)	/* no blocks मुक्त */
#घोषणा	MAXAG		128	/* max number of allocation groups */
#घोषणा L2MAXAG		7	/* l2 max num of AG */
#घोषणा L2MINAGSZ	25	/* l2 of minimum AG size in bytes */
#घोषणा	BMAPBLKNO	0	/* lblkno of bmap within the map */

/*
 * maximum l2 number of disk blocks at the various dmapctl levels.
 */
#घोषणा	L2MAXL0SIZE	(L2BPERDMAP + 1 * L2LPERCTL)
#घोषणा	L2MAXL1SIZE	(L2BPERDMAP + 2 * L2LPERCTL)
#घोषणा	L2MAXL2SIZE	(L2BPERDMAP + 3 * L2LPERCTL)

/*
 * maximum number of disk blocks at the various dmapctl levels.
 */
#घोषणा	MAXL0SIZE	((s64)1 << L2MAXL0SIZE)
#घोषणा	MAXL1SIZE	((s64)1 << L2MAXL1SIZE)
#घोषणा	MAXL2SIZE	((s64)1 << L2MAXL2SIZE)

#घोषणा	MAXMAPSIZE	MAXL2SIZE	/* maximum aggregate map size */

/*
 * determine the maximum मुक्त string क्रम four (lower level) nodes
 * of the tree.
 */
अटल अंतरभूत चिन्हित अक्षर TREEMAX(चिन्हित अक्षर *cp)
अणु
	चिन्हित अक्षर पंचांगp1, पंचांगp2;

	पंचांगp1 = max(*(cp+2), *(cp+3));
	पंचांगp2 = max(*(cp), *(cp+1));

	वापस max(पंचांगp1, पंचांगp2);
पूर्ण

/*
 * convert disk block number to the logical block number of the dmap
 * describing the disk block.  s is the log2(number of logical blocks per page)
 *
 * The calculation figures out how many logical pages are in front of the dmap.
 *	- the number of dmaps preceding it
 *	- the number of L0 pages preceding its L0 page
 *	- the number of L1 pages preceding its L1 page
 *	- 3 is added to account क्रम the L2, L1, and L0 page क्रम this dmap
 *	- 1 is added to account क्रम the control page of the map.
 */
#घोषणा BLKTODMAP(b,s)    \
	((((b) >> 13) + ((b) >> 23) + ((b) >> 33) + 3 + 1) << (s))

/*
 * convert disk block number to the logical block number of the LEVEL 0
 * dmapctl describing the disk block.  s is the log2(number of logical blocks
 * per page)
 *
 * The calculation figures out how many logical pages are in front of the L0.
 *	- the number of dmap pages preceding it
 *	- the number of L0 pages preceding it
 *	- the number of L1 pages preceding its L1 page
 *	- 2 is added to account क्रम the L2, and L1 page क्रम this L0
 *	- 1 is added to account क्रम the control page of the map.
 */
#घोषणा BLKTOL0(b,s)      \
	(((((b) >> 23) << 10) + ((b) >> 23) + ((b) >> 33) + 2 + 1) << (s))

/*
 * convert disk block number to the logical block number of the LEVEL 1
 * dmapctl describing the disk block.  s is the log2(number of logical blocks
 * per page)
 *
 * The calculation figures out how many logical pages are in front of the L1.
 *	- the number of dmap pages preceding it
 *	- the number of L0 pages preceding it
 *	- the number of L1 pages preceding it
 *	- 1 is added to account क्रम the L2 page
 *	- 1 is added to account क्रम the control page of the map.
 */
#घोषणा BLKTOL1(b,s)      \
     (((((b) >> 33) << 20) + (((b) >> 33) << 10) + ((b) >> 33) + 1 + 1) << (s))

/*
 * convert disk block number to the logical block number of the dmapctl
 * at the specअगरied level which describes the disk block.
 */
#घोषणा BLKTOCTL(b,s,l)   \
	(((l) == 2) ? 1 : ((l) == 1) ? BLKTOL1((b),(s)) : BLKTOL0((b),(s)))

/*
 * convert aggregate map size to the zero origin dmapctl level of the
 * top dmapctl.
 */
#घोषणा	BMAPSZTOLEV(size)	\
	(((size) <= MAXL0SIZE) ? 0 : ((size) <= MAXL1SIZE) ? 1 : 2)

/* convert disk block number to allocation group number.
 */
#घोषणा BLKTOAG(b,sbi)	((b) >> ((sbi)->bmap->db_agl2size))

/* convert allocation group number to starting disk block
 * number.
 */
#घोषणा AGTOBLK(a,ip)	\
	((s64)(a) << (JFS_SBI((ip)->i_sb)->bmap->db_agl2size))

/*
 *	dmap summary tree
 *
 * dmaptree must be consistent with dmapctl.
 */
काष्ठा dmaptree अणु
	__le32 nleafs;		/* 4: number of tree leafs	*/
	__le32 l2nleafs;	/* 4: l2 number of tree leafs	*/
	__le32 leafidx;		/* 4: index of first tree leaf	*/
	__le32 height;		/* 4: height of the tree	*/
	s8 budmin;		/* 1: min l2 tree leaf value to combine */
	s8 stree[TREESIZE];	/* TREESIZE: tree		*/
	u8 pad[2];		/* 2: pad to word boundary	*/
पूर्ण;				/* - 360 -			*/

/*
 *	dmap page per 8K blocks biपंचांगap
 */
काष्ठा dmap अणु
	__le32 nblocks;		/* 4: num blks covered by this dmap	*/
	__le32 nमुक्त;		/* 4: num of मुक्त blks in this dmap	*/
	__le64 start;		/* 8: starting blkno क्रम this dmap	*/
	काष्ठा dmaptree tree;	/* 360: dmap tree			*/
	u8 pad[1672];		/* 1672: pad to 2048 bytes		*/
	__le32 wmap[LPERDMAP];	/* 1024: bits of the working map	*/
	__le32 pmap[LPERDMAP];	/* 1024: bits of the persistent map	*/
पूर्ण;				/* - 4096 -				*/

/*
 *	disk map control page per level.
 *
 * dmapctl must be consistent with dmaptree.
 */
काष्ठा dmapctl अणु
	__le32 nleafs;		/* 4: number of tree leafs	*/
	__le32 l2nleafs;	/* 4: l2 number of tree leafs	*/
	__le32 leafidx;		/* 4: index of the first tree leaf	*/
	__le32 height;		/* 4: height of tree		*/
	s8 budmin;		/* 1: minimum l2 tree leaf value	*/
	s8 stree[CTLTREESIZE];	/* CTLTREESIZE: dmapctl tree	*/
	u8 pad[2714];		/* 2714: pad to 4096		*/
पूर्ण;				/* - 4096 -			*/

/*
 *	common definition क्रम dmaptree within dmap and dmapctl
 */
प्रकार जोड़ dmtree अणु
	काष्ठा dmaptree t1;
	काष्ठा dmapctl t2;
पूर्ण dmtree_t;

/* macros क्रम accessing fields within dmtree */
#घोषणा	dmt_nleafs	t1.nleafs
#घोषणा	dmt_l2nleafs	t1.l2nleafs
#घोषणा	dmt_leafidx	t1.leafidx
#घोषणा	dmt_height	t1.height
#घोषणा	dmt_budmin	t1.budmin
#घोषणा	dmt_stree	t2.stree

/*
 *	on-disk aggregate disk allocation map descriptor.
 */
काष्ठा dbmap_disk अणु
	__le64 dn_mapsize;	/* 8: number of blocks in aggregate	*/
	__le64 dn_nमुक्त;	/* 8: num मुक्त blks in aggregate map	*/
	__le32 dn_l2nbperpage;	/* 4: number of blks per page		*/
	__le32 dn_numag;	/* 4: total number of ags		*/
	__le32 dn_maxlevel;	/* 4: number of active ags		*/
	__le32 dn_maxag;	/* 4: max active alloc group number	*/
	__le32 dn_agpref;	/* 4: preferred alloc group (hपूर्णांक)	*/
	__le32 dn_aglevel;	/* 4: dmapctl level holding the AG	*/
	__le32 dn_agheight;	/* 4: height in dmapctl of the AG	*/
	__le32 dn_agwidth;	/* 4: width in dmapctl of the AG	*/
	__le32 dn_agstart;	/* 4: start tree index at AG height	*/
	__le32 dn_agl2size;	/* 4: l2 num of blks per alloc group	*/
	__le64 dn_agमुक्त[MAXAG];/* 8*MAXAG: per AG मुक्त count		*/
	__le64 dn_agsize;	/* 8: num of blks per alloc group	*/
	s8 dn_maxमुक्तbud;	/* 1: max मुक्त buddy प्रणाली		*/
	u8 pad[3007];		/* 3007: pad to 4096			*/
पूर्ण;				/* - 4096 -				*/

काष्ठा dbmap अणु
	s64 dn_mapsize;		/* number of blocks in aggregate	*/
	s64 dn_nमुक्त;		/* num मुक्त blks in aggregate map	*/
	पूर्णांक dn_l2nbperpage;	/* number of blks per page		*/
	पूर्णांक dn_numag;		/* total number of ags			*/
	पूर्णांक dn_maxlevel;	/* number of active ags			*/
	पूर्णांक dn_maxag;		/* max active alloc group number	*/
	पूर्णांक dn_agpref;		/* preferred alloc group (hपूर्णांक)		*/
	पूर्णांक dn_aglevel;		/* dmapctl level holding the AG		*/
	पूर्णांक dn_agheight;	/* height in dmapctl of the AG		*/
	पूर्णांक dn_agwidth;		/* width in dmapctl of the AG		*/
	पूर्णांक dn_agstart;		/* start tree index at AG height	*/
	पूर्णांक dn_agl2size;	/* l2 num of blks per alloc group	*/
	s64 dn_agमुक्त[MAXAG];	/* per AG मुक्त count			*/
	s64 dn_agsize;		/* num of blks per alloc group		*/
	चिन्हित अक्षर dn_maxमुक्तbud;	/* max मुक्त buddy प्रणाली	*/
पूर्ण;				/* - 4096 -				*/
/*
 *	in-memory aggregate disk allocation map descriptor.
 */
काष्ठा bmap अणु
	काष्ठा dbmap db_bmap;		/* on-disk aggregate map descriptor */
	काष्ठा inode *db_ipbmap;	/* ptr to aggregate map incore inode */
	काष्ठा mutex db_bmaplock;	/* aggregate map lock */
	atomic_t db_active[MAXAG];	/* count of active, खोलो files in AG */
	u32 *db_DBmap;
पूर्ण;

/* macros क्रम accessing fields within in-memory aggregate map descriptor */
#घोषणा	db_mapsize	db_bmap.dn_mapsize
#घोषणा	db_nमुक्त	db_bmap.dn_nमुक्त
#घोषणा	db_agमुक्त	db_bmap.dn_agमुक्त
#घोषणा	db_agsize	db_bmap.dn_agsize
#घोषणा	db_agl2size	db_bmap.dn_agl2size
#घोषणा	db_agwidth	db_bmap.dn_agwidth
#घोषणा	db_agheight	db_bmap.dn_agheight
#घोषणा	db_agstart	db_bmap.dn_agstart
#घोषणा	db_numag	db_bmap.dn_numag
#घोषणा	db_maxlevel	db_bmap.dn_maxlevel
#घोषणा	db_aglevel	db_bmap.dn_aglevel
#घोषणा	db_agpref	db_bmap.dn_agpref
#घोषणा	db_maxag	db_bmap.dn_maxag
#घोषणा	db_maxमुक्तbud	db_bmap.dn_maxमुक्तbud
#घोषणा	db_l2nbperpage	db_bmap.dn_l2nbperpage

/*
 * macros क्रम various conversions needed by the allocators.
 * blkstol2(), cntlz(), and cnttz() are operating प्रणाली dependent functions.
 */
/* convert number of blocks to log2 number of blocks, rounding up to
 * the next log2 value अगर blocks is not a l2 multiple.
 */
#घोषणा	BLKSTOL2(d)		(blkstol2(d))

/* convert number of leafs to log2 leaf value */
#घोषणा	NLSTOL2BSZ(n)		(31 - cntlz((n)) + BUDMIN)

/* convert leaf index to log2 leaf value */
#घोषणा	LITOL2BSZ(n,m,b)	((((n) == 0) ? (m) : cnttz((n))) + (b))

/* convert a block number to a dmap control leaf index */
#घोषणा BLKTOCTLLEAF(b,m)	\
	(((b) & (((s64)1 << ((m) + L2LPERCTL)) - 1)) >> (m))

/* convert log2 leaf value to buddy size */
#घोषणा	BUDSIZE(s,m)		(1 << ((s) - (m)))

/*
 *	बाह्यal references.
 */
बाह्य पूर्णांक dbMount(काष्ठा inode *ipbmap);

बाह्य पूर्णांक dbUnmount(काष्ठा inode *ipbmap, पूर्णांक mounterror);

बाह्य पूर्णांक dbFree(काष्ठा inode *ipbmap, s64 blkno, s64 nblocks);

बाह्य पूर्णांक dbUpdatePMap(काष्ठा inode *ipbmap,
			पूर्णांक मुक्त, s64 blkno, s64 nblocks, काष्ठा tblock * tblk);

बाह्य पूर्णांक dbNextAG(काष्ठा inode *ipbmap);

बाह्य पूर्णांक dbAlloc(काष्ठा inode *ipbmap, s64 hपूर्णांक, s64 nblocks, s64 * results);

बाह्य पूर्णांक dbReAlloc(काष्ठा inode *ipbmap,
		     s64 blkno, s64 nblocks, s64 addnblocks, s64 * results);

बाह्य पूर्णांक dbSync(काष्ठा inode *ipbmap);
बाह्य पूर्णांक dbAllocBottomUp(काष्ठा inode *ip, s64 blkno, s64 nblocks);
बाह्य पूर्णांक dbExtendFS(काष्ठा inode *ipbmap, s64 blkno, s64 nblocks);
बाह्य व्योम dbFinalizeBmap(काष्ठा inode *ipbmap);
बाह्य s64 dbMapFileSizeToMapSize(काष्ठा inode *ipbmap);
बाह्य s64 dbDiscardAG(काष्ठा inode *ip, पूर्णांक agno, s64 minlen);

#पूर्ण_अगर				/* _H_JFS_DMAP */
