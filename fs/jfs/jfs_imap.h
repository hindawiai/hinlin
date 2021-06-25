<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2002
 */
#अगर_अघोषित	_H_JFS_IMAP
#घोषणा _H_JFS_IMAP

#समावेश "jfs_txnmgr.h"

/*
 *	jfs_imap.h: disk inode manager
 */

#घोषणा	EXTSPERIAG	128	/* number of disk inode extent per iag	*/
#घोषणा IMAPBLKNO	0	/* lblkno of dinomap within inode map	*/
#घोषणा SMAPSZ		4	/* number of words per summary map	*/
#घोषणा	EXTSPERSUM	32	/* number of extents per summary map entry */
#घोषणा	L2EXTSPERSUM	5	/* l2 number of extents per summary map */
#घोषणा	PGSPERIEXT	4	/* number of 4K pages per dinode extent */
#घोषणा	MAXIAGS		((1<<20)-1)	/* maximum number of iags	*/
#घोषणा	MAXAG		128	/* maximum number of allocation groups	*/

#घोषणा AMAPSIZE	512	/* bytes in the IAG allocation maps */
#घोषणा SMAPSIZE	16	/* bytes in the IAG summary maps */

/* convert inode number to iag number */
#घोषणा	INOTOIAG(ino)	((ino) >> L2INOSPERIAG)

/* convert iag number to logical block number of the iag page */
#घोषणा IAGTOLBLK(iagno,l2nbperpg)	(((iagno) + 1) << (l2nbperpg))

/* get the starting block number of the 4K page of an inode extent
 * that contains ino.
 */
#घोषणा INOPBLK(pxd,ino,l2nbperpg)	(addressPXD((pxd)) +		\
	((((ino) & (INOSPEREXT-1)) >> L2INOSPERPAGE) << (l2nbperpg)))

/*
 *	inode allocation map:
 *
 * inode allocation map consists of
 * . the inode map control page and
 * . inode allocation group pages (per 4096 inodes)
 * which are addressed by standard JFS xtree.
 */
/*
 *	inode allocation group page (per 4096 inodes of an AG)
 */
काष्ठा iag अणु
	__le64 agstart;		/* 8: starting block of ag		*/
	__le32 iagnum;		/* 4: inode allocation group number	*/
	__le32 inoमुक्तfwd;	/* 4: ag inode मुक्त list क्रमward	*/
	__le32 inoमुक्तback;	/* 4: ag inode मुक्त list back		*/
	__le32 extमुक्तfwd;	/* 4: ag inode extent मुक्त list क्रमward	*/
	__le32 extमुक्तback;	/* 4: ag inode extent मुक्त list back	*/
	__le32 iagमुक्त;		/* 4: iag मुक्त list			*/

	/* summary map: 1 bit per inode extent */
	__le32 inosmap[SMAPSZ];	/* 16: sum map of mapwords w/ मुक्त inodes;
				 *	note: this indicates मुक्त and backed
				 *	inodes, अगर the extent is not backed the
				 *	value will be 1.  अगर the extent is
				 *	backed but all inodes are being used the
				 *	value will be 1.  अगर the extent is
				 *	backed but at least one of the inodes is
				 *	मुक्त the value will be 0.
				 */
	__le32 extsmap[SMAPSZ];	/* 16: sum map of mapwords w/ मुक्त extents */
	__le32 nमुक्तinos;	/* 4: number of मुक्त inodes		*/
	__le32 nमुक्तexts;	/* 4: number of मुक्त extents		*/
	/* (72) */
	u8 pad[1976];		/* 1976: pad to 2048 bytes */
	/* allocation bit map: 1 bit per inode (0 - मुक्त, 1 - allocated) */
	__le32 wmap[EXTSPERIAG];	/* 512: working allocation map */
	__le32 pmap[EXTSPERIAG];	/* 512: persistent allocation map */
	pxd_t inoext[EXTSPERIAG];	/* 1024: inode extent addresses */
पूर्ण;				/* (4096) */

/*
 *	per AG control inक्रमmation (in inode map control page)
 */
काष्ठा iagctl_disk अणु
	__le32 inoमुक्त;		/* 4: मुक्त inode list anchor		*/
	__le32 extमुक्त;		/* 4: मुक्त extent list anchor		*/
	__le32 numinos;		/* 4: number of backed inodes		*/
	__le32 numमुक्त;		/* 4: number of मुक्त inodes		*/
पूर्ण;				/* (16) */

काष्ठा iagctl अणु
	पूर्णांक inoमुक्त;		/* मुक्त inode list anchor		*/
	पूर्णांक extमुक्त;		/* मुक्त extent list anchor		*/
	पूर्णांक numinos;		/* number of backed inodes		*/
	पूर्णांक numमुक्त;		/* number of मुक्त inodes		*/
पूर्ण;

/*
 *	per fileset/aggregate inode map control page
 */
काष्ठा dinomap_disk अणु
	__le32 in_मुक्तiag;	/* 4: मुक्त iag list anchor	*/
	__le32 in_nextiag;	/* 4: next मुक्त iag number	*/
	__le32 in_numinos;	/* 4: num of backed inodes	*/
	__le32 in_numमुक्त;	/* 4: num of मुक्त backed inodes */
	__le32 in_nbperiext;	/* 4: num of blocks per inode extent */
	__le32 in_l2nbperiext;	/* 4: l2 of in_nbperiext	*/
	__le32 in_diskblock;	/* 4: क्रम standalone test driver */
	__le32 in_maxag;	/* 4: क्रम standalone test driver */
	u8 pad[2016];		/* 2016: pad to 2048		*/
	काष्ठा iagctl_disk in_agctl[MAXAG]; /* 2048: AG control inक्रमmation */
पूर्ण;				/* (4096) */

काष्ठा dinomap अणु
	पूर्णांक in_मुक्तiag;		/* मुक्त iag list anchor		*/
	पूर्णांक in_nextiag;		/* next मुक्त iag number		*/
	पूर्णांक in_numinos;		/* num of backed inodes		*/
	पूर्णांक in_numमुक्त;		/* num of मुक्त backed inodes	*/
	पूर्णांक in_nbperiext;	/* num of blocks per inode extent */
	पूर्णांक in_l2nbperiext;	/* l2 of in_nbperiext		*/
	पूर्णांक in_diskblock;	/* क्रम standalone test driver	*/
	पूर्णांक in_maxag;		/* क्रम standalone test driver	*/
	काष्ठा iagctl in_agctl[MAXAG];	/* AG control inक्रमmation */
पूर्ण;

/*
 *	In-core inode map control page
 */
काष्ठा inomap अणु
	काष्ठा dinomap im_imap;		/* 4096: inode allocation control */
	काष्ठा inode *im_ipimap;	/* 4: ptr to inode क्रम imap	*/
	काष्ठा mutex im_मुक्तlock;	/* 4: iag मुक्त list lock	*/
	काष्ठा mutex im_aglock[MAXAG];	/* 512: per AG locks		*/
	u32 *im_DBGdimap;
	atomic_t im_numinos;	/* num of backed inodes */
	atomic_t im_numमुक्त;	/* num of मुक्त backed inodes */
पूर्ण;

#घोषणा	im_मुक्तiag	im_imap.in_मुक्तiag
#घोषणा	im_nextiag	im_imap.in_nextiag
#घोषणा	im_agctl	im_imap.in_agctl
#घोषणा	im_nbperiext	im_imap.in_nbperiext
#घोषणा	im_l2nbperiext	im_imap.in_l2nbperiext

/* क्रम standalone testdriver
 */
#घोषणा	im_diskblock	im_imap.in_diskblock
#घोषणा	im_maxag	im_imap.in_maxag

बाह्य पूर्णांक diFree(काष्ठा inode *);
बाह्य पूर्णांक diAlloc(काष्ठा inode *, bool, काष्ठा inode *);
बाह्य पूर्णांक diSync(काष्ठा inode *);
/* बाह्यal references */
बाह्य पूर्णांक diUpdatePMap(काष्ठा inode *ipimap, अचिन्हित दीर्घ inum,
			bool is_मुक्त, काष्ठा tblock * tblk);
बाह्य पूर्णांक diExtendFS(काष्ठा inode *ipimap, काष्ठा inode *ipbmap);
बाह्य पूर्णांक diMount(काष्ठा inode *);
बाह्य पूर्णांक diUnmount(काष्ठा inode *, पूर्णांक);
बाह्य पूर्णांक diRead(काष्ठा inode *);
बाह्य काष्ठा inode *diReadSpecial(काष्ठा super_block *, ino_t, पूर्णांक);
बाह्य व्योम diWriteSpecial(काष्ठा inode *, पूर्णांक);
बाह्य व्योम diFreeSpecial(काष्ठा inode *);
बाह्य पूर्णांक diWrite(tid_t tid, काष्ठा inode *);
#पूर्ण_अगर				/* _H_JFS_IMAP */
