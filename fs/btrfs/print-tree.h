<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_PRINT_TREE_H
#घोषणा BTRFS_PRINT_TREE_H

/* Buffer size to contain tree name and possibly additional data (offset) */
#घोषणा BTRFS_ROOT_NAME_BUF_LEN				48

व्योम btrfs_prपूर्णांक_leaf(काष्ठा extent_buffer *l);
व्योम btrfs_prपूर्णांक_tree(काष्ठा extent_buffer *c, bool follow);
स्थिर अक्षर *btrfs_root_name(स्थिर काष्ठा btrfs_key *key, अक्षर *buf);

#पूर्ण_अगर
