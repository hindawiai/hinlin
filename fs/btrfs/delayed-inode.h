<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2011 Fujitsu.  All rights reserved.
 * Written by Miao Xie <miaox@cn.fujitsu.com>
 */

#अगर_अघोषित BTRFS_DELAYED_INODE_H
#घोषणा BTRFS_DELAYED_INODE_H

#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश "ctree.h"

/* types of the delayed item */
#घोषणा BTRFS_DELAYED_INSERTION_ITEM	1
#घोषणा BTRFS_DELAYED_DELETION_ITEM	2

काष्ठा btrfs_delayed_root अणु
	spinlock_t lock;
	काष्ठा list_head node_list;
	/*
	 * Used क्रम delayed nodes which is रुकोing to be dealt with by the
	 * worker. If the delayed node is inserted पूर्णांकo the work queue, we
	 * drop it from this list.
	 */
	काष्ठा list_head prepare_list;
	atomic_t items;		/* क्रम delayed items */
	atomic_t items_seq;	/* क्रम delayed items */
	पूर्णांक nodes;		/* क्रम delayed nodes */
	रुको_queue_head_t रुको;
पूर्ण;

#घोषणा BTRFS_DELAYED_NODE_IN_LIST	0
#घोषणा BTRFS_DELAYED_NODE_INODE_सूचीTY	1
#घोषणा BTRFS_DELAYED_NODE_DEL_IREF	2

काष्ठा btrfs_delayed_node अणु
	u64 inode_id;
	u64 bytes_reserved;
	काष्ठा btrfs_root *root;
	/* Used to add the node पूर्णांकo the delayed root's node list. */
	काष्ठा list_head n_list;
	/*
	 * Used to add the node पूर्णांकo the prepare list, the nodes in this list
	 * is रुकोing to be dealt with by the async worker.
	 */
	काष्ठा list_head p_list;
	काष्ठा rb_root_cached ins_root;
	काष्ठा rb_root_cached del_root;
	काष्ठा mutex mutex;
	काष्ठा btrfs_inode_item inode_item;
	refcount_t refs;
	u64 index_cnt;
	अचिन्हित दीर्घ flags;
	पूर्णांक count;
पूर्ण;

काष्ठा btrfs_delayed_item अणु
	काष्ठा rb_node rb_node;
	काष्ठा btrfs_key key;
	काष्ठा list_head tree_list;	/* used क्रम batch insert/delete items */
	काष्ठा list_head सूची_पढ़ो_list;	/* used क्रम सूची_पढ़ो items */
	u64 bytes_reserved;
	काष्ठा btrfs_delayed_node *delayed_node;
	refcount_t refs;
	पूर्णांक ins_or_del;
	u32 data_len;
	अक्षर data[];
पूर्ण;

अटल अंतरभूत व्योम btrfs_init_delayed_root(
				काष्ठा btrfs_delayed_root *delayed_root)
अणु
	atomic_set(&delayed_root->items, 0);
	atomic_set(&delayed_root->items_seq, 0);
	delayed_root->nodes = 0;
	spin_lock_init(&delayed_root->lock);
	init_रुकोqueue_head(&delayed_root->रुको);
	INIT_LIST_HEAD(&delayed_root->node_list);
	INIT_LIST_HEAD(&delayed_root->prepare_list);
पूर्ण

पूर्णांक btrfs_insert_delayed_dir_index(काष्ठा btrfs_trans_handle *trans,
				   स्थिर अक्षर *name, पूर्णांक name_len,
				   काष्ठा btrfs_inode *dir,
				   काष्ठा btrfs_disk_key *disk_key, u8 type,
				   u64 index);

पूर्णांक btrfs_delete_delayed_dir_index(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_inode *dir, u64 index);

पूर्णांक btrfs_inode_delayed_dir_index_count(काष्ठा btrfs_inode *inode);

पूर्णांक btrfs_run_delayed_items(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_run_delayed_items_nr(काष्ठा btrfs_trans_handle *trans, पूर्णांक nr);

व्योम btrfs_balance_delayed_items(काष्ठा btrfs_fs_info *fs_info);

पूर्णांक btrfs_commit_inode_delayed_items(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_inode *inode);
/* Used क्रम evicting the inode. */
व्योम btrfs_हटाओ_delayed_node(काष्ठा btrfs_inode *inode);
व्योम btrfs_समाप्त_delayed_inode_items(काष्ठा btrfs_inode *inode);
पूर्णांक btrfs_commit_inode_delayed_inode(काष्ठा btrfs_inode *inode);


पूर्णांक btrfs_delayed_update_inode(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       काष्ठा btrfs_inode *inode);
पूर्णांक btrfs_fill_inode(काष्ठा inode *inode, u32 *rdev);
पूर्णांक btrfs_delayed_delete_inode_ref(काष्ठा btrfs_inode *inode);

/* Used क्रम drop dead root */
व्योम btrfs_समाप्त_all_delayed_nodes(काष्ठा btrfs_root *root);

/* Used क्रम clean the transaction */
व्योम btrfs_destroy_delayed_inodes(काष्ठा btrfs_fs_info *fs_info);

/* Used क्रम सूची_पढ़ो() */
bool btrfs_सूची_पढ़ो_get_delayed_items(काष्ठा inode *inode,
				     काष्ठा list_head *ins_list,
				     काष्ठा list_head *del_list);
व्योम btrfs_सूची_पढ़ो_put_delayed_items(काष्ठा inode *inode,
				     काष्ठा list_head *ins_list,
				     काष्ठा list_head *del_list);
पूर्णांक btrfs_should_delete_dir_index(काष्ठा list_head *del_list,
				  u64 index);
पूर्णांक btrfs_सूची_पढ़ो_delayed_dir_index(काष्ठा dir_context *ctx,
				    काष्ठा list_head *ins_list);

/* क्रम init */
पूर्णांक __init btrfs_delayed_inode_init(व्योम);
व्योम __cold btrfs_delayed_inode_निकास(व्योम);

/* क्रम debugging */
व्योम btrfs_निश्चित_delayed_root_empty(काष्ठा btrfs_fs_info *fs_info);

#पूर्ण_अगर
