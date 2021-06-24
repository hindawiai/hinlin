<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014 Filipe David Borba Manana <fdmanana@gmail.com>
 */

#अगर_अघोषित BTRFS_PROPS_H
#घोषणा BTRFS_PROPS_H

#समावेश "ctree.h"

व्योम __init btrfs_props_init(व्योम);

पूर्णांक btrfs_set_prop(काष्ठा btrfs_trans_handle *trans, काष्ठा inode *inode,
		   स्थिर अक्षर *name, स्थिर अक्षर *value, माप_प्रकार value_len,
		   पूर्णांक flags);
पूर्णांक btrfs_validate_prop(स्थिर अक्षर *name, स्थिर अक्षर *value, माप_प्रकार value_len);

पूर्णांक btrfs_load_inode_props(काष्ठा inode *inode, काष्ठा btrfs_path *path);

पूर्णांक btrfs_inode_inherit_props(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा inode *inode,
			      काष्ठा inode *dir);

पूर्णांक btrfs_subvol_inherit_props(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       काष्ठा btrfs_root *parent_root);

#पूर्ण_अगर
