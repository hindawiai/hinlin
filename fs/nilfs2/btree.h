<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * btree.h - NILFS B-tree.
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#अगर_अघोषित _NILFS_BTREE_H
#घोषणा _NILFS_BTREE_H

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/list.h>
#समावेश <linux/nilfs2_ondisk.h>	/* nilfs_btree_node */
#समावेश "btnode.h"
#समावेश "bmap.h"

/**
 * काष्ठा nilfs_btree_path - A path on which B-tree operations are executed
 * @bp_bh: buffer head of node block
 * @bp_sib_bh: buffer head of sibling node block
 * @bp_index: index of child node
 * @bp_oldreq: ptr end request क्रम old ptr
 * @bp_newreq: ptr alloc request क्रम new ptr
 * @bp_op: rebalance operation
 */
काष्ठा nilfs_btree_path अणु
	काष्ठा buffer_head *bp_bh;
	काष्ठा buffer_head *bp_sib_bh;
	पूर्णांक bp_index;
	जोड़ nilfs_bmap_ptr_req bp_oldreq;
	जोड़ nilfs_bmap_ptr_req bp_newreq;
	काष्ठा nilfs_btnode_chkey_ctxt bp_ctxt;
	व्योम (*bp_op)(काष्ठा nilfs_bmap *, काष्ठा nilfs_btree_path *,
		      पूर्णांक, __u64 *, __u64 *);
पूर्ण;

#घोषणा NILFS_BTREE_ROOT_SIZE		NILFS_BMAP_SIZE
#घोषणा NILFS_BTREE_ROOT_NCHILDREN_MAX					\
	((NILFS_BTREE_ROOT_SIZE - माप(काष्ठा nilfs_btree_node)) /	\
	 (माप(__le64 /* dkey */) + माप(__le64 /* dptr */)))
#घोषणा NILFS_BTREE_ROOT_NCHILDREN_MIN	0
#घोषणा NILFS_BTREE_NODE_EXTRA_PAD_SIZE	(माप(__le64))
#घोषणा NILFS_BTREE_NODE_NCHILDREN_MAX(nodesize)			\
	(((nodesize) - माप(काष्ठा nilfs_btree_node) -		\
		NILFS_BTREE_NODE_EXTRA_PAD_SIZE) /			\
	 (माप(__le64 /* dkey */) + माप(__le64 /* dptr */)))
#घोषणा NILFS_BTREE_NODE_NCHILDREN_MIN(nodesize)			\
	((NILFS_BTREE_NODE_NCHILDREN_MAX(nodesize) - 1) / 2 + 1)
#घोषणा NILFS_BTREE_KEY_MIN	((__u64)0)
#घोषणा NILFS_BTREE_KEY_MAX	(~(__u64)0)

बाह्य काष्ठा kmem_cache *nilfs_btree_path_cache;

पूर्णांक nilfs_btree_init(काष्ठा nilfs_bmap *);
पूर्णांक nilfs_btree_convert_and_insert(काष्ठा nilfs_bmap *, __u64, __u64,
				   स्थिर __u64 *, स्थिर __u64 *, पूर्णांक);
व्योम nilfs_btree_init_gc(काष्ठा nilfs_bmap *);

पूर्णांक nilfs_btree_broken_node_block(काष्ठा buffer_head *bh);

#पूर्ण_अगर	/* _NILFS_BTREE_H */
