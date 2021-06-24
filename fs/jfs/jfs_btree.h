<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */
#अगर_अघोषित	_H_JFS_BTREE
#घोषणा _H_JFS_BTREE

/*
 *	jfs_btree.h: B+-tree
 *
 * JFS B+-tree (dtree and xtree) common definitions
 */

/*
 *	basic btree page - btpage
 *
काष्ठा btpage अणु
	s64 next;		right sibling bn
	s64 prev;		left sibling bn

	u8 flag;
	u8 rsrvd[7];		type specअगरic
	s64 self;		self address

	u8 entry[4064];
पूर्ण;						*/

/* btpaget_t flag */
#घोषणा BT_TYPE		0x07	/* B+-tree index */
#घोषणा	BT_ROOT		0x01	/* root page */
#घोषणा	BT_LEAF		0x02	/* leaf page */
#घोषणा	BT_INTERNAL	0x04	/* पूर्णांकernal page */
#घोषणा	BT_RIGHTMOST	0x10	/* righपंचांगost page */
#घोषणा	BT_LEFTMOST	0x20	/* lefपंचांगost page */
#घोषणा	BT_SWAPPED	0x80	/* used by fsck क्रम endian swapping */

/* btorder (in inode) */
#घोषणा	BT_RANDOM		0x0000
#घोषणा	BT_SEQUENTIAL		0x0001
#घोषणा	BT_LOOKUP		0x0010
#घोषणा	BT_INSERT		0x0020
#घोषणा	BT_DELETE		0x0040

/*
 *	btree page buffer cache access
 */
#घोषणा BT_IS_ROOT(MP) (((MP)->xflag & COMMIT_PAGE) == 0)

/* get page from buffer page */
#घोषणा BT_PAGE(IP, MP, TYPE, ROOT)\
	(BT_IS_ROOT(MP) ? (TYPE *)&JFS_IP(IP)->ROOT : (TYPE *)(MP)->data)

/* get the page buffer and the page क्रम specअगरied block address */
#घोषणा BT_GETPAGE(IP, BN, MP, TYPE, SIZE, P, RC, ROOT)\
अणु\
	अगर ((BN) == 0)\
	अणु\
		MP = (काष्ठा metapage *)&JFS_IP(IP)->bxflag;\
		P = (TYPE *)&JFS_IP(IP)->ROOT;\
		RC = 0;\
	पूर्ण\
	अन्यथा\
	अणु\
		MP = पढ़ो_metapage((IP), BN, SIZE, 1);\
		अगर (MP) अणु\
			RC = 0;\
			P = (MP)->data;\
		पूर्ण अन्यथा अणु\
			P = शून्य;\
			jfs_err("bread failed!");\
			RC = -EIO;\
		पूर्ण\
	पूर्ण\
पूर्ण

#घोषणा BT_MARK_सूचीTY(MP, IP)\
अणु\
	अगर (BT_IS_ROOT(MP))\
		mark_inode_dirty(IP);\
	अन्यथा\
		mark_metapage_dirty(MP);\
पूर्ण

/* put the page buffer */
#घोषणा BT_PUTPAGE(MP)\
अणु\
	अगर (! BT_IS_ROOT(MP)) \
		release_metapage(MP); \
पूर्ण


/*
 *	btree traversal stack
 *
 * record the path traversed during the search;
 * top frame record the leaf page/entry selected.
 */
काष्ठा btframe अणु	/* stack frame */
	s64 bn;			/* 8: */
	s16 index;		/* 2: */
	s16 lastindex;		/* 2: unused */
	काष्ठा metapage *mp;	/* 4/8: */
पूर्ण;				/* (16/24) */

काष्ठा btstack अणु
	काष्ठा btframe *top;
	पूर्णांक nsplit;
	काष्ठा btframe stack[MAXTREEHEIGHT];
पूर्ण;

#घोषणा BT_CLR(btstack)\
	(btstack)->top = (btstack)->stack

#घोषणा BT_STACK_FULL(btstack)\
	( (btstack)->top == &((btstack)->stack[MAXTREEHEIGHT-1]))

#घोषणा BT_PUSH(BTSTACK, BN, INDEX)\
अणु\
	निश्चित(!BT_STACK_FULL(BTSTACK));\
	(BTSTACK)->top->bn = BN;\
	(BTSTACK)->top->index = INDEX;\
	++(BTSTACK)->top;\
पूर्ण

#घोषणा BT_POP(btstack)\
	( (btstack)->top == (btstack)->stack ? शून्य : --(btstack)->top )

#घोषणा BT_STACK(btstack)\
	( (btstack)->top == (btstack)->stack ? शून्य : (btstack)->top )

अटल अंतरभूत व्योम BT_STACK_DUMP(काष्ठा btstack *btstack)
अणु
	पूर्णांक i;
	prपूर्णांकk("btstack dump:\n");
	क्रम (i = 0; i < MAXTREEHEIGHT; i++)
		prपूर्णांकk(KERN_ERR "bn = %Lx, index = %d\n",
		       (दीर्घ दीर्घ)btstack->stack[i].bn,
		       btstack->stack[i].index);
पूर्ण

/* retrieve search results */
#घोषणा BT_GETSEARCH(IP, LEAF, BN, MP, TYPE, P, INDEX, ROOT)\
अणु\
	BN = (LEAF)->bn;\
	MP = (LEAF)->mp;\
	अगर (BN)\
		P = (TYPE *)MP->data;\
	अन्यथा\
		P = (TYPE *)&JFS_IP(IP)->ROOT;\
	INDEX = (LEAF)->index;\
पूर्ण

/* put the page buffer of search */
#घोषणा BT_PUTSEARCH(BTSTACK)\
अणु\
	अगर (! BT_IS_ROOT((BTSTACK)->top->mp))\
		release_metapage((BTSTACK)->top->mp);\
पूर्ण
#पूर्ण_अगर				/* _H_JFS_BTREE */
