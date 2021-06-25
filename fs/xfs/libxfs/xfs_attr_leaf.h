<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000,2002-2003,2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_ATTR_LEAF_H__
#घोषणा	__XFS_ATTR_LEAF_H__

काष्ठा attrlist;
काष्ठा xfs_attr_list_context;
काष्ठा xfs_da_args;
काष्ठा xfs_da_state;
काष्ठा xfs_da_state_blk;
काष्ठा xfs_inode;
काष्ठा xfs_trans;

/*
 * Incore version of the attribute leaf header.
 */
काष्ठा xfs_attr3_icleaf_hdr अणु
	uपूर्णांक32_t	क्रमw;
	uपूर्णांक32_t	back;
	uपूर्णांक16_t	magic;
	uपूर्णांक16_t	count;
	uपूर्णांक16_t	usedbytes;
	/*
	 * Firstused is 32-bit here instead of 16-bit like the on-disk variant
	 * to support maximum fsb size of 64k without overflow issues throughout
	 * the attr code. Instead, the overflow condition is handled on
	 * conversion to/from disk.
	 */
	uपूर्णांक32_t	firstused;
	__u8		holes;
	काष्ठा अणु
		uपूर्णांक16_t	base;
		uपूर्णांक16_t	size;
	पूर्ण मुक्तmap[XFS_ATTR_LEAF_MAPSIZE];
पूर्ण;

/*========================================================================
 * Function prototypes क्रम the kernel.
 *========================================================================*/

/*
 * Internal routines when attribute विभाजन size < XFS_LITINO(mp).
 */
व्योम	xfs_attr_लघुक्रमm_create(काष्ठा xfs_da_args *args);
व्योम	xfs_attr_लघुक्रमm_add(काष्ठा xfs_da_args *args, पूर्णांक विभाजनoff);
पूर्णांक	xfs_attr_लघुक्रमm_lookup(काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr_लघुक्रमm_getvalue(काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr_लघुक्रमm_to_leaf(काष्ठा xfs_da_args *args,
			काष्ठा xfs_buf **leaf_bp);
पूर्णांक	xfs_attr_लघुक्रमm_हटाओ(काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr_sf_findname(काष्ठा xfs_da_args *args,
			     काष्ठा xfs_attr_sf_entry **sfep,
			     अचिन्हित पूर्णांक *basep);
पूर्णांक	xfs_attr_लघुक्रमm_allfit(काष्ठा xfs_buf *bp, काष्ठा xfs_inode *dp);
पूर्णांक	xfs_attr_लघुक्रमm_bytesfit(काष्ठा xfs_inode *dp, पूर्णांक bytes);
xfs_failaddr_t xfs_attr_लघुक्रमm_verअगरy(काष्ठा xfs_inode *ip);
व्योम	xfs_attr_विभाजन_हटाओ(काष्ठा xfs_inode *ip, काष्ठा xfs_trans *tp);

/*
 * Internal routines when attribute विभाजन size == XFS_LBSIZE(mp).
 */
पूर्णांक	xfs_attr3_leaf_to_node(काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr3_leaf_to_लघुक्रमm(काष्ठा xfs_buf *bp,
				   काष्ठा xfs_da_args *args, पूर्णांक विभाजनoff);
पूर्णांक	xfs_attr3_leaf_clearflag(काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr3_leaf_setflag(काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr3_leaf_flipflags(काष्ठा xfs_da_args *args);

/*
 * Routines used क्रम growing the Btree.
 */
पूर्णांक	xfs_attr3_leaf_split(काष्ठा xfs_da_state *state,
				   काष्ठा xfs_da_state_blk *oldblk,
				   काष्ठा xfs_da_state_blk *newblk);
पूर्णांक	xfs_attr3_leaf_lookup_पूर्णांक(काष्ठा xfs_buf *leaf,
					काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr3_leaf_getvalue(काष्ठा xfs_buf *bp, काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr3_leaf_add(काष्ठा xfs_buf *leaf_buffer,
				 काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr3_leaf_हटाओ(काष्ठा xfs_buf *leaf_buffer,
				    काष्ठा xfs_da_args *args);
पूर्णांक	xfs_attr3_leaf_list_पूर्णांक(काष्ठा xfs_buf *bp,
				काष्ठा xfs_attr_list_context *context);

/*
 * Routines used क्रम shrinking the Btree.
 */
पूर्णांक	xfs_attr3_leaf_toosmall(काष्ठा xfs_da_state *state, पूर्णांक *retval);
व्योम	xfs_attr3_leaf_unbalance(काष्ठा xfs_da_state *state,
				       काष्ठा xfs_da_state_blk *drop_blk,
				       काष्ठा xfs_da_state_blk *save_blk);
/*
 * Utility routines.
 */
xfs_dahash_t	xfs_attr_leaf_lasthash(काष्ठा xfs_buf *bp, पूर्णांक *count);
पूर्णांक	xfs_attr_leaf_order(काष्ठा xfs_buf *leaf1_bp,
				   काष्ठा xfs_buf *leaf2_bp);
पूर्णांक	xfs_attr_leaf_newentsize(काष्ठा xfs_da_args *args, पूर्णांक *local);
पूर्णांक	xfs_attr3_leaf_पढ़ो(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
			xfs_dablk_t bno, काष्ठा xfs_buf **bpp);
व्योम	xfs_attr3_leaf_hdr_from_disk(काष्ठा xfs_da_geometry *geo,
				     काष्ठा xfs_attr3_icleaf_hdr *to,
				     काष्ठा xfs_attr_leafblock *from);
व्योम	xfs_attr3_leaf_hdr_to_disk(काष्ठा xfs_da_geometry *geo,
				   काष्ठा xfs_attr_leafblock *to,
				   काष्ठा xfs_attr3_icleaf_hdr *from);

#पूर्ण_अगर	/* __XFS_ATTR_LEAF_H__ */
