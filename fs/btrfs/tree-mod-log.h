<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित BTRFS_TREE_MOD_LOG_H
#घोषणा BTRFS_TREE_MOD_LOG_H

#समावेश "ctree.h"

/* Represents a tree mod log user. */
काष्ठा btrfs_seq_list अणु
	काष्ठा list_head list;
	u64 seq;
पूर्ण;

#घोषणा BTRFS_SEQ_LIST_INIT(name) अणु .list = LIST_HEAD_INIT((name).list), .seq = 0 पूर्ण
#घोषणा BTRFS_SEQ_LAST            ((u64)-1)

क्रमागत btrfs_mod_log_op अणु
	BTRFS_MOD_LOG_KEY_REPLACE,
	BTRFS_MOD_LOG_KEY_ADD,
	BTRFS_MOD_LOG_KEY_REMOVE,
	BTRFS_MOD_LOG_KEY_REMOVE_WHILE_FREEING,
	BTRFS_MOD_LOG_KEY_REMOVE_WHILE_MOVING,
	BTRFS_MOD_LOG_MOVE_KEYS,
	BTRFS_MOD_LOG_ROOT_REPLACE,
पूर्ण;

u64 btrfs_get_tree_mod_seq(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_seq_list *elem);
व्योम btrfs_put_tree_mod_seq(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_seq_list *elem);
पूर्णांक btrfs_tree_mod_log_insert_root(काष्ठा extent_buffer *old_root,
				   काष्ठा extent_buffer *new_root,
				   bool log_removal);
पूर्णांक btrfs_tree_mod_log_insert_key(काष्ठा extent_buffer *eb, पूर्णांक slot,
				  क्रमागत btrfs_mod_log_op op, gfp_t flags);
पूर्णांक btrfs_tree_mod_log_मुक्त_eb(काष्ठा extent_buffer *eb);
काष्ठा extent_buffer *btrfs_tree_mod_log_शुरुआत(काष्ठा btrfs_fs_info *fs_info,
						काष्ठा btrfs_path *path,
						काष्ठा extent_buffer *eb,
						u64 समय_seq);
काष्ठा extent_buffer *btrfs_get_old_root(काष्ठा btrfs_root *root, u64 समय_seq);
पूर्णांक btrfs_old_root_level(काष्ठा btrfs_root *root, u64 समय_seq);
पूर्णांक btrfs_tree_mod_log_eb_copy(काष्ठा extent_buffer *dst,
			       काष्ठा extent_buffer *src,
			       अचिन्हित दीर्घ dst_offset,
			       अचिन्हित दीर्घ src_offset,
			       पूर्णांक nr_items);
पूर्णांक btrfs_tree_mod_log_insert_move(काष्ठा extent_buffer *eb,
				   पूर्णांक dst_slot, पूर्णांक src_slot,
				   पूर्णांक nr_items);
u64 btrfs_tree_mod_log_lowest_seq(काष्ठा btrfs_fs_info *fs_info);

#पूर्ण_अगर
