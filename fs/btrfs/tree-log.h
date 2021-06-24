<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_TREE_LOG_H
#घोषणा BTRFS_TREE_LOG_H

#समावेश "ctree.h"
#समावेश "transaction.h"

/* वापस value क्रम btrfs_log_dentry_safe that means we करोn't need to log it at all */
#घोषणा BTRFS_NO_LOG_SYNC 256

काष्ठा btrfs_log_ctx अणु
	पूर्णांक log_ret;
	पूर्णांक log_transid;
	bool log_new_dentries;
	bool logging_new_name;
	काष्ठा inode *inode;
	काष्ठा list_head list;
	/* Only used क्रम fast fsyncs. */
	काष्ठा list_head ordered_extents;
पूर्ण;

अटल अंतरभूत व्योम btrfs_init_log_ctx(काष्ठा btrfs_log_ctx *ctx,
				      काष्ठा inode *inode)
अणु
	ctx->log_ret = 0;
	ctx->log_transid = 0;
	ctx->log_new_dentries = false;
	ctx->logging_new_name = false;
	ctx->inode = inode;
	INIT_LIST_HEAD(&ctx->list);
	INIT_LIST_HEAD(&ctx->ordered_extents);
पूर्ण

अटल अंतरभूत व्योम btrfs_release_log_ctx_extents(काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा btrfs_ordered_extent *पंचांगp;

	ASSERT(inode_is_locked(ctx->inode));

	list_क्रम_each_entry_safe(ordered, पंचांगp, &ctx->ordered_extents, log_list) अणु
		list_del_init(&ordered->log_list);
		btrfs_put_ordered_extent(ordered);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम btrfs_set_log_full_commit(काष्ठा btrfs_trans_handle *trans)
अणु
	WRITE_ONCE(trans->fs_info->last_trans_log_full_commit, trans->transid);
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_need_log_full_commit(काष्ठा btrfs_trans_handle *trans)
अणु
	वापस READ_ONCE(trans->fs_info->last_trans_log_full_commit) ==
		trans->transid;
पूर्ण

पूर्णांक btrfs_sync_log(काष्ठा btrfs_trans_handle *trans,
		   काष्ठा btrfs_root *root, काष्ठा btrfs_log_ctx *ctx);
पूर्णांक btrfs_मुक्त_log(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root);
पूर्णांक btrfs_मुक्त_log_root_tree(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_recover_log_trees(काष्ठा btrfs_root *tree_root);
पूर्णांक btrfs_log_dentry_safe(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा dentry *dentry,
			  काष्ठा btrfs_log_ctx *ctx);
पूर्णांक btrfs_del_dir_entries_in_log(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root,
				 स्थिर अक्षर *name, पूर्णांक name_len,
				 काष्ठा btrfs_inode *dir, u64 index);
पूर्णांक btrfs_del_inode_ref_in_log(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       स्थिर अक्षर *name, पूर्णांक name_len,
			       काष्ठा btrfs_inode *inode, u64 dirid);
व्योम btrfs_end_log_trans(काष्ठा btrfs_root *root);
व्योम btrfs_pin_log_trans(काष्ठा btrfs_root *root);
व्योम btrfs_record_unlink_dir(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_inode *dir, काष्ठा btrfs_inode *inode,
			     पूर्णांक क्रम_नाम);
व्योम btrfs_record_snapshot_destroy(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_inode *dir);
व्योम btrfs_log_new_name(काष्ठा btrfs_trans_handle *trans,
			काष्ठा btrfs_inode *inode, काष्ठा btrfs_inode *old_dir,
			काष्ठा dentry *parent);

#पूर्ण_अगर
