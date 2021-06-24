<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/fs/hfs/btree.h
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 */

#समावेश "hfs_fs.h"

प्रकार पूर्णांक (*btree_keycmp)(स्थिर btree_key *, स्थिर btree_key *);

#घोषणा NODE_HASH_SIZE  256

/* A HFS BTree held in memory */
काष्ठा hfs_btree अणु
	काष्ठा super_block *sb;
	काष्ठा inode *inode;
	btree_keycmp keycmp;

	u32 cnid;
	u32 root;
	u32 leaf_count;
	u32 leaf_head;
	u32 leaf_tail;
	u32 node_count;
	u32 मुक्त_nodes;
	u32 attributes;

	अचिन्हित पूर्णांक node_size;
	अचिन्हित पूर्णांक node_size_shअगरt;
	अचिन्हित पूर्णांक max_key_len;
	अचिन्हित पूर्णांक depth;

	//अचिन्हित पूर्णांक map1_size, map_size;
	काष्ठा mutex tree_lock;

	अचिन्हित पूर्णांक pages_per_bnode;
	spinlock_t hash_lock;
	काष्ठा hfs_bnode *node_hash[NODE_HASH_SIZE];
	पूर्णांक node_hash_cnt;
पूर्ण;

/* A HFS BTree node in memory */
काष्ठा hfs_bnode अणु
	काष्ठा hfs_btree *tree;

	u32 prev;
	u32 this;
	u32 next;
	u32 parent;

	u16 num_recs;
	u8 type;
	u8 height;

	काष्ठा hfs_bnode *next_hash;
	अचिन्हित दीर्घ flags;
	रुको_queue_head_t lock_wq;
	atomic_t refcnt;
	अचिन्हित पूर्णांक page_offset;
	काष्ठा page *page[];
पूर्ण;

#घोषणा HFS_BNODE_ERROR		0
#घोषणा HFS_BNODE_NEW		1
#घोषणा HFS_BNODE_DELETED	2

काष्ठा hfs_find_data अणु
	btree_key *key;
	btree_key *search_key;
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *bnode;
	पूर्णांक record;
	पूर्णांक keyoffset, keylength;
	पूर्णांक entryoffset, entrylength;
पूर्ण;


/* btree.c */
बाह्य काष्ठा hfs_btree *hfs_btree_खोलो(काष्ठा super_block *, u32, btree_keycmp);
बाह्य व्योम hfs_btree_बंद(काष्ठा hfs_btree *);
बाह्य व्योम hfs_btree_ग_लिखो(काष्ठा hfs_btree *);
बाह्य पूर्णांक hfs_bmap_reserve(काष्ठा hfs_btree *, पूर्णांक);
बाह्य काष्ठा hfs_bnode * hfs_bmap_alloc(काष्ठा hfs_btree *);
बाह्य व्योम hfs_bmap_मुक्त(काष्ठा hfs_bnode *node);

/* bnode.c */
बाह्य व्योम hfs_bnode_पढ़ो(काष्ठा hfs_bnode *, व्योम *, पूर्णांक, पूर्णांक);
बाह्य u16 hfs_bnode_पढ़ो_u16(काष्ठा hfs_bnode *, पूर्णांक);
बाह्य u8 hfs_bnode_पढ़ो_u8(काष्ठा hfs_bnode *, पूर्णांक);
बाह्य व्योम hfs_bnode_पढ़ो_key(काष्ठा hfs_bnode *, व्योम *, पूर्णांक);
बाह्य व्योम hfs_bnode_ग_लिखो(काष्ठा hfs_bnode *, व्योम *, पूर्णांक, पूर्णांक);
बाह्य व्योम hfs_bnode_ग_लिखो_u16(काष्ठा hfs_bnode *, पूर्णांक, u16);
बाह्य व्योम hfs_bnode_ग_लिखो_u8(काष्ठा hfs_bnode *, पूर्णांक, u8);
बाह्य व्योम hfs_bnode_clear(काष्ठा hfs_bnode *, पूर्णांक, पूर्णांक);
बाह्य व्योम hfs_bnode_copy(काष्ठा hfs_bnode *, पूर्णांक,
			   काष्ठा hfs_bnode *, पूर्णांक, पूर्णांक);
बाह्य व्योम hfs_bnode_move(काष्ठा hfs_bnode *, पूर्णांक, पूर्णांक, पूर्णांक);
बाह्य व्योम hfs_bnode_dump(काष्ठा hfs_bnode *);
बाह्य व्योम hfs_bnode_unlink(काष्ठा hfs_bnode *);
बाह्य काष्ठा hfs_bnode *hfs_bnode_findhash(काष्ठा hfs_btree *, u32);
बाह्य काष्ठा hfs_bnode *hfs_bnode_find(काष्ठा hfs_btree *, u32);
बाह्य व्योम hfs_bnode_unhash(काष्ठा hfs_bnode *);
बाह्य व्योम hfs_bnode_मुक्त(काष्ठा hfs_bnode *);
बाह्य काष्ठा hfs_bnode *hfs_bnode_create(काष्ठा hfs_btree *, u32);
बाह्य व्योम hfs_bnode_get(काष्ठा hfs_bnode *);
बाह्य व्योम hfs_bnode_put(काष्ठा hfs_bnode *);

/* brec.c */
बाह्य u16 hfs_brec_lenoff(काष्ठा hfs_bnode *, u16, u16 *);
बाह्य u16 hfs_brec_keylen(काष्ठा hfs_bnode *, u16);
बाह्य पूर्णांक hfs_brec_insert(काष्ठा hfs_find_data *, व्योम *, पूर्णांक);
बाह्य पूर्णांक hfs_brec_हटाओ(काष्ठा hfs_find_data *);

/* bfind.c */
बाह्य पूर्णांक hfs_find_init(काष्ठा hfs_btree *, काष्ठा hfs_find_data *);
बाह्य व्योम hfs_find_निकास(काष्ठा hfs_find_data *);
बाह्य पूर्णांक __hfs_brec_find(काष्ठा hfs_bnode *, काष्ठा hfs_find_data *);
बाह्य पूर्णांक hfs_brec_find(काष्ठा hfs_find_data *);
बाह्य पूर्णांक hfs_brec_पढ़ो(काष्ठा hfs_find_data *, व्योम *, पूर्णांक);
बाह्य पूर्णांक hfs_brec_जाओ(काष्ठा hfs_find_data *, पूर्णांक);


काष्ठा hfs_bnode_desc अणु
	__be32 next;		/* (V) Number of the next node at this level */
	__be32 prev;		/* (V) Number of the prev node at this level */
	u8 type;		/* (F) The type of node */
	u8 height;		/* (F) The level of this node (leaves=1) */
	__be16 num_recs;	/* (V) The number of records in this node */
	u16 reserved;
पूर्ण __packed;

#घोषणा HFS_NODE_INDEX	0x00	/* An पूर्णांकernal (index) node */
#घोषणा HFS_NODE_HEADER	0x01	/* The tree header node (node 0) */
#घोषणा HFS_NODE_MAP	0x02	/* Holds part of the biपंचांगap of used nodes */
#घोषणा HFS_NODE_LEAF	0xFF	/* A leaf (ndNHeight==1) node */

काष्ठा hfs_btree_header_rec अणु
	__be16 depth;		/* (V) The number of levels in this B-tree */
	__be32 root;		/* (V) The node number of the root node */
	__be32 leaf_count;	/* (V) The number of leaf records */
	__be32 leaf_head;	/* (V) The number of the first leaf node */
	__be32 leaf_tail;	/* (V) The number of the last leaf node */
	__be16 node_size;	/* (F) The number of bytes in a node (=512) */
	__be16 max_key_len;	/* (F) The length of a key in an index node */
	__be32 node_count;	/* (V) The total number of nodes */
	__be32 मुक्त_nodes;	/* (V) The number of unused nodes */
	u16 reserved1;
	__be32 clump_size;	/* (F) clump size. not usually used. */
	u8 btree_type;		/* (F) BTree type */
	u8 reserved2;
	__be32 attributes;	/* (F) attributes */
	u32 reserved3[16];
पूर्ण __packed;

#घोषणा BTREE_ATTR_BADCLOSE	0x00000001	/* b-tree not बंदd properly. not
						   used by hfsplus. */
#घोषणा HFS_TREE_BIGKEYS	0x00000002	/* key length is u16 instead of u8.
						   used by hfsplus. */
#घोषणा HFS_TREE_VARIDXKEYS	0x00000004	/* variable key length instead of
						   max key length. use din catalog
						   b-tree but not in extents
						   b-tree (hfsplus). */
