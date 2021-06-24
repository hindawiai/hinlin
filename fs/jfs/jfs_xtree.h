<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2002
 */
#अगर_अघोषित _H_JFS_XTREE
#घोषणा _H_JFS_XTREE

/*
 *	jfs_xtree.h: extent allocation descriptor B+-tree manager
 */

#समावेश "jfs_btree.h"


/*
 *	extent allocation descriptor (xad)
 */
प्रकार काष्ठा xad अणु
	__u8 flag;	/* 1: flag */
	__u8 rsvrd[2];	/* 2: reserved */
	__u8 off1;	/* 1: offset in unit of fsblksize */
	__le32 off2;	/* 4: offset in unit of fsblksize */
	pxd_t loc;	/* 8: length and address in unit of fsblksize */
पूर्ण xad_t;			/* (16) */

#घोषणा MAXXLEN		((1 << 24) - 1)

#घोषणा XTSLOTSIZE	16
#घोषणा L2XTSLOTSIZE	4

/* xad_t field स्थिरruction */
#घोषणा XADoffset(xad, offset64)\
अणु\
	(xad)->off1 = ((u64)offset64) >> 32;\
	(xad)->off2 = __cpu_to_le32((offset64) & 0xffffffff);\
पूर्ण
#घोषणा XADaddress(xad, address64) PXDaddress(&(xad)->loc, address64)
#घोषणा XADlength(xad, length32) PXDlength(&(xad)->loc, length32)

/* xad_t field extraction */
#घोषणा offsetXAD(xad)\
	( ((s64)((xad)->off1)) << 32 | __le32_to_cpu((xad)->off2))
#घोषणा addressXAD(xad) addressPXD(&(xad)->loc)
#घोषणा lengthXAD(xad) lengthPXD(&(xad)->loc)

/* xad list */
काष्ठा xadlist अणु
	s16 maxnxad;
	s16 nxad;
	xad_t *xad;
पूर्ण;

/* xad_t flags */
#घोषणा XAD_NEW		0x01	/* new */
#घोषणा XAD_EXTENDED	0x02	/* extended */
#घोषणा XAD_COMPRESSED	0x04	/* compressed with recorded length */
#घोषणा XAD_NOTRECORDED 0x08	/* allocated but not recorded */
#घोषणा XAD_COW		0x10	/* copy-on-ग_लिखो */


/* possible values क्रम maxentry */
#घोषणा XTROOTINITSLOT_सूची 6
#घोषणा XTROOTINITSLOT	10
#घोषणा XTROOTMAXSLOT	18
#घोषणा XTPAGEMAXSLOT	256
#घोषणा XTENTRYSTART	2

/*
 *	xtree page:
 */
प्रकार जोड़ अणु
	काष्ठा xtheader अणु
		__le64 next;	/* 8: */
		__le64 prev;	/* 8: */

		u8 flag;	/* 1: */
		u8 rsrvd1;	/* 1: */
		__le16 nextindex;	/* 2: next index = number of entries */
		__le16 maxentry;	/* 2: max number of entries */
		__le16 rsrvd2;	/* 2: */

		pxd_t self;	/* 8: self */
	पूर्ण header;		/* (32) */

	xad_t xad[XTROOTMAXSLOT];	/* 16 * maxentry: xad array */
पूर्ण xtpage_t;

/*
 *	बाह्यal declaration
 */
बाह्य पूर्णांक xtLookup(काष्ठा inode *ip, s64 lstart, s64 llen,
		    पूर्णांक *pflag, s64 * paddr, पूर्णांक *plen, पूर्णांक flag);
बाह्य व्योम xtInitRoot(tid_t tid, काष्ठा inode *ip);
बाह्य पूर्णांक xtInsert(tid_t tid, काष्ठा inode *ip,
		    पूर्णांक xflag, s64 xoff, पूर्णांक xlen, s64 * xaddrp, पूर्णांक flag);
बाह्य पूर्णांक xtExtend(tid_t tid, काष्ठा inode *ip, s64 xoff, पूर्णांक xlen,
		    पूर्णांक flag);
#अगर_घोषित _NOTYET
बाह्य पूर्णांक xtTailgate(tid_t tid, काष्ठा inode *ip,
		      s64 xoff, पूर्णांक xlen, s64 xaddr, पूर्णांक flag);
#पूर्ण_अगर
बाह्य पूर्णांक xtUpdate(tid_t tid, काष्ठा inode *ip, काष्ठा xad *nxad);
बाह्य पूर्णांक xtDelete(tid_t tid, काष्ठा inode *ip, s64 xoff, पूर्णांक xlen,
		    पूर्णांक flag);
बाह्य s64 xtTruncate(tid_t tid, काष्ठा inode *ip, s64 newsize, पूर्णांक type);
बाह्य s64 xtTruncate_pmap(tid_t tid, काष्ठा inode *ip, s64 committed_size);
बाह्य पूर्णांक xtRelocate(tid_t tid, काष्ठा inode *ip,
		      xad_t * oxad, s64 nxaddr, पूर्णांक xtype);
बाह्य पूर्णांक xtAppend(tid_t tid,
		    काष्ठा inode *ip, पूर्णांक xflag, s64 xoff, पूर्णांक maxblocks,
		    पूर्णांक *xlenp, s64 * xaddrp, पूर्णांक flag);
#पूर्ण_अगर				/* !_H_JFS_XTREE */
