<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * btnode.h - NILFS B-tree node cache
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Seiji Kihara.
 * Revised by Ryusuke Konishi.
 */

#अगर_अघोषित _NILFS_BTNODE_H
#घोषणा _NILFS_BTNODE_H

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/fs.h>
#समावेश <linux/backing-dev.h>

/**
 * काष्ठा nilfs_btnode_chkey_ctxt - change key context
 * @oldkey: old key of block's moving content
 * @newkey: new key क्रम block's content
 * @bh: buffer head of old buffer
 * @newbh: buffer head of new buffer
 */
काष्ठा nilfs_btnode_chkey_ctxt अणु
	__u64 oldkey;
	__u64 newkey;
	काष्ठा buffer_head *bh;
	काष्ठा buffer_head *newbh;
पूर्ण;

व्योम nilfs_btnode_cache_clear(काष्ठा address_space *);
काष्ठा buffer_head *nilfs_btnode_create_block(काष्ठा address_space *btnc,
					      __u64 blocknr);
पूर्णांक nilfs_btnode_submit_block(काष्ठा address_space *, __u64, sector_t, पूर्णांक,
			      पूर्णांक, काष्ठा buffer_head **, sector_t *);
व्योम nilfs_btnode_delete(काष्ठा buffer_head *);
पूर्णांक nilfs_btnode_prepare_change_key(काष्ठा address_space *,
				    काष्ठा nilfs_btnode_chkey_ctxt *);
व्योम nilfs_btnode_commit_change_key(काष्ठा address_space *,
				    काष्ठा nilfs_btnode_chkey_ctxt *);
व्योम nilfs_btnode_पात_change_key(काष्ठा address_space *,
				   काष्ठा nilfs_btnode_chkey_ctxt *);

#पूर्ण_अगर	/* _NILFS_BTNODE_H */
