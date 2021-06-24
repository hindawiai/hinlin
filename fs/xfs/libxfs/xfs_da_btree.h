<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000,2002,2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_DA_BTREE_H__
#घोषणा	__XFS_DA_BTREE_H__

काष्ठा xfs_inode;
काष्ठा xfs_trans;
काष्ठा zone;

/*
 * Directory/attribute geometry inक्रमmation. There will be one of these क्रम each
 * data विभाजन type, and it will be passed around via the xfs_da_args. Global
 * काष्ठाures will be attached to the xfs_mount.
 */
काष्ठा xfs_da_geometry अणु
	अचिन्हित पूर्णांक	blksize;	/* da block size in bytes */
	अचिन्हित पूर्णांक	fsbcount;	/* da block size in fileप्रणाली blocks */
	uपूर्णांक8_t		fsblog;		/* log2 of _fileप्रणाली_ block size */
	uपूर्णांक8_t		blklog;		/* log2 of da block size */
	अचिन्हित पूर्णांक	node_hdr_size;	/* danode header size in bytes */
	अचिन्हित पूर्णांक	node_ents;	/* # of entries in a danode */
	अचिन्हित पूर्णांक	magicpct;	/* 37% of block size in bytes */
	xfs_dablk_t	datablk;	/* blockno of dir data v2 */
	अचिन्हित पूर्णांक	leaf_hdr_size;	/* dir2 leaf header size */
	अचिन्हित पूर्णांक	leaf_max_ents;	/* # of entries in dir2 leaf */
	xfs_dablk_t	leafblk;	/* blockno of leaf data v2 */
	अचिन्हित पूर्णांक	मुक्त_hdr_size;	/* dir2 मुक्त header size */
	अचिन्हित पूर्णांक	मुक्त_max_bests;	/* # of bests entries in dir2 मुक्त */
	xfs_dablk_t	मुक्तblk;	/* blockno of मुक्त data v2 */

	xfs_dir2_data_aoff_t data_first_offset;
	माप_प्रकार		data_entry_offset;
पूर्ण;

/*========================================================================
 * Btree searching and modअगरication काष्ठाure definitions.
 *========================================================================*/

/*
 * Search comparison results
 */
क्रमागत xfs_dacmp अणु
	XFS_CMP_DIFFERENT,	/* names are completely dअगरferent */
	XFS_CMP_EXACT,		/* names are exactly the same */
	XFS_CMP_CASE		/* names are same but dअगरfer in हाल */
पूर्ण;

/*
 * Structure to ease passing around component names.
 */
प्रकार काष्ठा xfs_da_args अणु
	काष्ठा xfs_da_geometry *geo;	/* da block geometry */
	स्थिर uपूर्णांक8_t		*name;		/* string (maybe not शून्य terminated) */
	पूर्णांक		namelen;	/* length of string (maybe no शून्य) */
	uपूर्णांक8_t		filetype;	/* filetype of inode क्रम directories */
	व्योम		*value;		/* set of bytes (maybe contain शून्यs) */
	पूर्णांक		valuelen;	/* length of value */
	अचिन्हित पूर्णांक	attr_filter;	/* XFS_ATTR_अणुROOT,SECURE,INCOMPLETEपूर्ण */
	अचिन्हित पूर्णांक	attr_flags;	/* XATTR_अणुCREATE,REPLACEपूर्ण */
	xfs_dahash_t	hashval;	/* hash value of name */
	xfs_ino_t	inumber;	/* input/output inode number */
	काष्ठा xfs_inode *dp;		/* directory inode to manipulate */
	काष्ठा xfs_trans *trans;	/* current trans (changes over समय) */
	xfs_extlen_t	total;		/* total blocks needed, क्रम 1st bmap */
	पूर्णांक		whichविभाजन;	/* data or attribute विभाजन */
	xfs_dablk_t	blkno;		/* blkno of attr leaf of पूर्णांकerest */
	पूर्णांक		index;		/* index of attr of पूर्णांकerest in blk */
	xfs_dablk_t	rmtblkno;	/* remote attr value starting blkno */
	पूर्णांक		rmtblkcnt;	/* remote attr value block count */
	पूर्णांक		rmtvaluelen;	/* remote attr value length in bytes */
	xfs_dablk_t	blkno2;		/* blkno of 2nd attr leaf of पूर्णांकerest */
	पूर्णांक		index2;		/* index of 2nd attr in blk */
	xfs_dablk_t	rmtblkno2;	/* remote attr value starting blkno */
	पूर्णांक		rmtblkcnt2;	/* remote attr value block count */
	पूर्णांक		rmtvaluelen2;	/* remote attr value length in bytes */
	पूर्णांक		op_flags;	/* operation flags */
	क्रमागत xfs_dacmp	cmpresult;	/* name compare result क्रम lookups */
पूर्ण xfs_da_args_t;

/*
 * Operation flags:
 */
#घोषणा XFS_DA_OP_JUSTCHECK	0x0001	/* check क्रम ok with no space */
#घोषणा XFS_DA_OP_RENAME	0x0002	/* this is an atomic नाम op */
#घोषणा XFS_DA_OP_ADDNAME	0x0004	/* this is an add operation */
#घोषणा XFS_DA_OP_OKNOENT	0x0008	/* lookup/add op, ENOENT ok, अन्यथा die */
#घोषणा XFS_DA_OP_CILOOKUP	0x0010	/* lookup to वापस CI name अगर found */
#घोषणा XFS_DA_OP_NOTIME	0x0020	/* करोn't update inode बारtamps */

#घोषणा XFS_DA_OP_FLAGS \
	अणु XFS_DA_OP_JUSTCHECK,	"JUSTCHECK" पूर्ण, \
	अणु XFS_DA_OP_RENAME,	"RENAME" पूर्ण, \
	अणु XFS_DA_OP_ADDNAME,	"ADDNAME" पूर्ण, \
	अणु XFS_DA_OP_OKNOENT,	"OKNOENT" पूर्ण, \
	अणु XFS_DA_OP_CILOOKUP,	"CILOOKUP" पूर्ण, \
	अणु XFS_DA_OP_NOTIME,	"NOTIME" पूर्ण

/*
 * Storage क्रम holding state during Btree searches and split/join ops.
 *
 * Only need space क्रम 5 पूर्णांकermediate nodes.  With a minimum of 62-way
 * fanout to the Btree, we can support over 900 million directory blocks,
 * which is slightly more than enough.
 */
प्रकार काष्ठा xfs_da_state_blk अणु
	काष्ठा xfs_buf	*bp;		/* buffer containing block */
	xfs_dablk_t	blkno;		/* fileप्रणाली blkno of buffer */
	xfs_daddr_t	disk_blkno;	/* on-disk blkno (in BBs) of buffer */
	पूर्णांक		index;		/* relevant index पूर्णांकo block */
	xfs_dahash_t	hashval;	/* last hash value in block */
	पूर्णांक		magic;		/* blk's magic number, ie: blk type */
पूर्ण xfs_da_state_blk_t;

प्रकार काष्ठा xfs_da_state_path अणु
	पूर्णांक			active;		/* number of active levels */
	xfs_da_state_blk_t	blk[XFS_DA_NODE_MAXDEPTH];
पूर्ण xfs_da_state_path_t;

प्रकार काष्ठा xfs_da_state अणु
	xfs_da_args_t		*args;		/* filename arguments */
	काष्ठा xfs_mount	*mp;		/* fileप्रणाली mount poपूर्णांक */
	xfs_da_state_path_t	path;		/* search/split paths */
	xfs_da_state_path_t	altpath;	/* alternate path क्रम join */
	अचिन्हित अक्षर		inleaf;		/* insert पूर्णांकo 1->lf, 0->splf */
	अचिन्हित अक्षर		extravalid;	/* T/F: extrablk is in use */
	अचिन्हित अक्षर		extraafter;	/* T/F: extrablk is after new */
	xfs_da_state_blk_t	extrablk;	/* क्रम द्विगुन-splits on leaves */
						/* क्रम dirv2 extrablk is data */
पूर्ण xfs_da_state_t;

/*
 * In-core version of the node header to असलtract the dअगरferences in the v2 and
 * v3 disk क्रमmat of the headers. Callers need to convert to/from disk क्रमmat as
 * appropriate.
 */
काष्ठा xfs_da3_icnode_hdr अणु
	uपूर्णांक32_t		क्रमw;
	uपूर्णांक32_t		back;
	uपूर्णांक16_t		magic;
	uपूर्णांक16_t		count;
	uपूर्णांक16_t		level;

	/*
	 * Poपूर्णांकer to the on-disk क्रमmat entries, which are behind the
	 * variable size (v4 vs v5) header in the on-disk block.
	 */
	काष्ठा xfs_da_node_entry *btree;
पूर्ण;

/*
 * Utility macros to aid in logging changed काष्ठाure fields.
 */
#घोषणा XFS_DA_LOGOFF(BASE, ADDR)	((अक्षर *)(ADDR) - (अक्षर *)(BASE))
#घोषणा XFS_DA_LOGRANGE(BASE, ADDR, SIZE)	\
		(uपूर्णांक)(XFS_DA_LOGOFF(BASE, ADDR)), \
		(uपूर्णांक)(XFS_DA_LOGOFF(BASE, ADDR)+(SIZE)-1)

/*========================================================================
 * Function prototypes.
 *========================================================================*/

/*
 * Routines used क्रम growing the Btree.
 */
पूर्णांक	xfs_da3_node_create(काष्ठा xfs_da_args *args, xfs_dablk_t blkno,
			    पूर्णांक level, काष्ठा xfs_buf **bpp, पूर्णांक whichविभाजन);
पूर्णांक	xfs_da3_split(xfs_da_state_t *state);

/*
 * Routines used क्रम shrinking the Btree.
 */
पूर्णांक	xfs_da3_join(xfs_da_state_t *state);
व्योम	xfs_da3_fixhashpath(काष्ठा xfs_da_state *state,
			    काष्ठा xfs_da_state_path *path_to_to_fix);

/*
 * Routines used क्रम finding things in the Btree.
 */
पूर्णांक	xfs_da3_node_lookup_पूर्णांक(xfs_da_state_t *state, पूर्णांक *result);
पूर्णांक	xfs_da3_path_shअगरt(xfs_da_state_t *state, xfs_da_state_path_t *path,
					 पूर्णांक क्रमward, पूर्णांक release, पूर्णांक *result);
/*
 * Utility routines.
 */
पूर्णांक	xfs_da3_blk_link(xfs_da_state_t *state, xfs_da_state_blk_t *old_blk,
				       xfs_da_state_blk_t *new_blk);
पूर्णांक	xfs_da3_node_पढ़ो(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
			xfs_dablk_t bno, काष्ठा xfs_buf **bpp, पूर्णांक whichविभाजन);
पूर्णांक	xfs_da3_node_पढ़ो_mapped(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
			xfs_daddr_t mappedbno, काष्ठा xfs_buf **bpp,
			पूर्णांक whichविभाजन);

/*
 * Utility routines.
 */

#घोषणा XFS_DABUF_MAP_HOLE_OK	(1 << 0)

पूर्णांक	xfs_da_grow_inode(xfs_da_args_t *args, xfs_dablk_t *new_blkno);
पूर्णांक	xfs_da_grow_inode_पूर्णांक(काष्ठा xfs_da_args *args, xfs_fileoff_t *bno,
			      पूर्णांक count);
पूर्णांक	xfs_da_get_buf(काष्ठा xfs_trans *trans, काष्ठा xfs_inode *dp,
		xfs_dablk_t bno, काष्ठा xfs_buf **bp, पूर्णांक whichविभाजन);
पूर्णांक	xfs_da_पढ़ो_buf(काष्ठा xfs_trans *trans, काष्ठा xfs_inode *dp,
		xfs_dablk_t bno, अचिन्हित पूर्णांक flags, काष्ठा xfs_buf **bpp,
		पूर्णांक whichविभाजन, स्थिर काष्ठा xfs_buf_ops *ops);
पूर्णांक	xfs_da_पढ़ोa_buf(काष्ठा xfs_inode *dp, xfs_dablk_t bno,
		अचिन्हित पूर्णांक flags, पूर्णांक whichविभाजन,
		स्थिर काष्ठा xfs_buf_ops *ops);
पूर्णांक	xfs_da_shrink_inode(xfs_da_args_t *args, xfs_dablk_t dead_blkno,
					  काष्ठा xfs_buf *dead_buf);

uपूर्णांक xfs_da_hashname(स्थिर uपूर्णांक8_t *name_string, पूर्णांक name_length);
क्रमागत xfs_dacmp xfs_da_compname(काष्ठा xfs_da_args *args,
				स्थिर अचिन्हित अक्षर *name, पूर्णांक len);


काष्ठा xfs_da_state *xfs_da_state_alloc(काष्ठा xfs_da_args *args);
व्योम xfs_da_state_मुक्त(xfs_da_state_t *state);

व्योम	xfs_da3_node_hdr_from_disk(काष्ठा xfs_mount *mp,
		काष्ठा xfs_da3_icnode_hdr *to, काष्ठा xfs_da_पूर्णांकnode *from);
व्योम	xfs_da3_node_hdr_to_disk(काष्ठा xfs_mount *mp,
		काष्ठा xfs_da_पूर्णांकnode *to, काष्ठा xfs_da3_icnode_hdr *from);

बाह्य काष्ठा kmem_zone *xfs_da_state_zone;

#पूर्ण_अगर	/* __XFS_DA_BTREE_H__ */
