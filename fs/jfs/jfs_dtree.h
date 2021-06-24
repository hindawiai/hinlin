<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2002
 */
#अगर_अघोषित _H_JFS_DTREE
#घोषणा	_H_JFS_DTREE

/*
 *	jfs_dtree.h: directory B+-tree manager
 */

#समावेश "jfs_btree.h"

प्रकार जोड़ अणु
	काष्ठा अणु
		tid_t tid;
		काष्ठा inode *ip;
		u32 ino;
	पूर्ण leaf;
	pxd_t xd;
पूर्ण ddata_t;


/*
 *	entry segment/slot
 *
 * an entry consists of type dependent head/only segment/slot and
 * additional segments/slots linked vi next field;
 * N.B. last/only segment of entry is terminated by next = -1;
 */
/*
 *	directory page slot
 */
काष्ठा dtslot अणु
	s8 next;		/* 1: */
	s8 cnt;			/* 1: */
	__le16 name[15];	/* 30: */
पूर्ण;				/* (32) */


#घोषणा DATASLOTSIZE	16
#घोषणा L2DATASLOTSIZE	4
#घोषणा	DTSLOTSIZE	32
#घोषणा	L2DTSLOTSIZE	5
#घोषणा DTSLOTHDRSIZE	2
#घोषणा DTSLOTDATASIZE	30
#घोषणा DTSLOTDATALEN	15

/*
 *	 पूर्णांकernal node entry head/only segment
 */
काष्ठा idtentry अणु
	pxd_t xd;		/* 8: child extent descriptor */

	s8 next;		/* 1: */
	u8 namlen;		/* 1: */
	__le16 name[11];	/* 22: 2-byte aligned */
पूर्ण;				/* (32) */

#घोषणा DTIHDRSIZE	10
#घोषणा DTIHDRDATALEN	11

/* compute number of slots क्रम entry */
#घोषणा	NDTINTERNAL(klen) (DIV_ROUND_UP((4 + (klen)), 15))


/*
 *	leaf node entry head/only segment
 *
 *	For legacy fileप्रणालीs, name contains 13 wअक्षरs -- no index field
 */
काष्ठा ldtentry अणु
	__le32 inumber;		/* 4: 4-byte aligned */
	s8 next;		/* 1: */
	u8 namlen;		/* 1: */
	__le16 name[11];	/* 22: 2-byte aligned */
	__le32 index;		/* 4: index पूर्णांकo dir_table */
पूर्ण;				/* (32) */

#घोषणा DTLHDRSIZE	6
#घोषणा DTLHDRDATALEN_LEGACY	13	/* Old (OS/2) क्रमmat */
#घोषणा DTLHDRDATALEN	11

/*
 * dir_table used क्रम directory traversal during सूची_पढ़ो
 */

/*
 * Keep persistent index क्रम directory entries
 */
#घोषणा DO_INDEX(INODE) (JFS_SBI((INODE)->i_sb)->mntflag & JFS_सूची_INDEX)

/*
 * Maximum entry in अंतरभूत directory table
 */
#घोषणा MAX_INLINE_सूचीTABLE_ENTRY 13

काष्ठा dir_table_slot अणु
	u8 rsrvd;		/* 1: */
	u8 flag;		/* 1: 0 अगर मुक्त */
	u8 slot;		/* 1: slot within leaf page of entry */
	u8 addr1;		/* 1: upper 8 bits of leaf page address */
	__le32 addr2;		/* 4: lower 32 bits of leaf page address -OR-
				   index of next entry when this entry was deleted */
पूर्ण;				/* (8) */

/*
 * flag values
 */
#घोषणा सूची_INDEX_VALID 1
#घोषणा सूची_INDEX_FREE 0

#घोषणा DTSaddress(dir_table_slot, address64)\
अणु\
	(dir_table_slot)->addr1 = ((u64)address64) >> 32;\
	(dir_table_slot)->addr2 = __cpu_to_le32((address64) & 0xffffffff);\
पूर्ण

#घोषणा addressDTS(dts)\
	( ((s64)((dts)->addr1)) << 32 | __le32_to_cpu((dts)->addr2) )

/* compute number of slots क्रम entry */
#घोषणा	NDTLEAF_LEGACY(klen)	(DIV_ROUND_UP((2 + (klen)), 15))
#घोषणा	NDTLEAF	NDTINTERNAL


/*
 *	directory root page (in-line in on-disk inode):
 *
 * cf. dtpage_t below.
 */
प्रकार जोड़ अणु
	काष्ठा अणु
		काष्ठा dasd DASD; /* 16: DASD limit/usage info */

		u8 flag;	/* 1: */
		u8 nextindex;	/* 1: next मुक्त entry in stbl */
		s8 मुक्तcnt;	/* 1: मुक्त count */
		s8 मुक्तlist;	/* 1: मुक्तlist header */

		__le32 iकरोtकरोt;	/* 4: parent inode number */

		s8 stbl[8];	/* 8: sorted entry index table */
	पूर्ण header;		/* (32) */

	काष्ठा dtslot slot[9];
पूर्ण dtroot_t;

#घोषणा PARENT(IP) \
	(le32_to_cpu(JFS_IP(IP)->i_dtroot.header.iकरोtकरोt))

#घोषणा DTROOTMAXSLOT	9

#घोषणा	dtEmpty(IP) (JFS_IP(IP)->i_dtroot.header.nextindex == 0)


/*
 *	directory regular page:
 *
 *	entry slot array of 32 byte slot
 *
 * sorted entry slot index table (stbl):
 * contiguous slots at slot specअगरied by stblindex,
 * 1-byte per entry
 *   512 byte block:  16 entry tbl (1 slot)
 *  1024 byte block:  32 entry tbl (1 slot)
 *  2048 byte block:  64 entry tbl (2 slot)
 *  4096 byte block: 128 entry tbl (4 slot)
 *
 * data area:
 *   512 byte block:  16 - 2 =  14 slot
 *  1024 byte block:  32 - 2 =  30 slot
 *  2048 byte block:  64 - 3 =  61 slot
 *  4096 byte block: 128 - 5 = 123 slot
 *
 * N.B. index is 0-based; index fields refer to slot index
 * except nextindex which refers to entry index in stbl;
 * end of entry stot list or मुक्तlist is marked with -1.
 */
प्रकार जोड़ अणु
	काष्ठा अणु
		__le64 next;	/* 8: next sibling */
		__le64 prev;	/* 8: previous sibling */

		u8 flag;	/* 1: */
		u8 nextindex;	/* 1: next entry index in stbl */
		s8 मुक्तcnt;	/* 1: */
		s8 मुक्तlist;	/* 1: slot index of head of मुक्तlist */

		u8 maxslot;	/* 1: number of slots in page slot[] */
		u8 stblindex;	/* 1: slot index of start of stbl */
		u8 rsrvd[2];	/* 2: */

		pxd_t self;	/* 8: self pxd */
	पूर्ण header;		/* (32) */

	काष्ठा dtslot slot[128];
पूर्ण dtpage_t;

#घोषणा DTPAGEMAXSLOT        128

#घोषणा DT8THPGNODEBYTES     512
#घोषणा DT8THPGNODETSLOTS      1
#घोषणा DT8THPGNODESLOTS      16

#घोषणा DTQTRPGNODEBYTES    1024
#घोषणा DTQTRPGNODETSLOTS      1
#घोषणा DTQTRPGNODESLOTS      32

#घोषणा DTHALFPGNODEBYTES   2048
#घोषणा DTHALFPGNODETSLOTS     2
#घोषणा DTHALFPGNODESLOTS     64

#घोषणा DTFULLPGNODEBYTES   4096
#घोषणा DTFULLPGNODETSLOTS     4
#घोषणा DTFULLPGNODESLOTS    128

#घोषणा DTENTRYSTART	1

/* get sorted entry table of the page */
#घोषणा DT_GETSTBL(p) ( ((p)->header.flag & BT_ROOT) ?\
	((dtroot_t *)(p))->header.stbl : \
	(s8 *)&(p)->slot[(p)->header.stblindex] )

/*
 * Flags क्रम dtSearch
 */
#घोषणा JFS_CREATE 1
#घोषणा JFS_LOOKUP 2
#घोषणा JFS_REMOVE 3
#घोषणा JFS_RENAME 4

/*
 * Maximum file offset क्रम directories.
 */
#घोषणा सूचीEND	पूर्णांक_उच्च

/*
 *	बाह्यal declarations
 */
बाह्य व्योम dtInitRoot(tid_t tid, काष्ठा inode *ip, u32 iकरोtकरोt);

बाह्य पूर्णांक dtSearch(काष्ठा inode *ip, काष्ठा component_name * key,
		    ino_t * data, काष्ठा btstack * btstack, पूर्णांक flag);

बाह्य पूर्णांक dtInsert(tid_t tid, काष्ठा inode *ip, काष्ठा component_name * key,
		    ino_t * ino, काष्ठा btstack * btstack);

बाह्य पूर्णांक dtDelete(tid_t tid, काष्ठा inode *ip, काष्ठा component_name * key,
		    ino_t * data, पूर्णांक flag);

बाह्य पूर्णांक dtModअगरy(tid_t tid, काष्ठा inode *ip, काष्ठा component_name * key,
		    ino_t * orig_ino, ino_t new_ino, पूर्णांक flag);

बाह्य पूर्णांक jfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx);
#पूर्ण_अगर				/* !_H_JFS_DTREE */
