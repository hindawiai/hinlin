<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) Qu Wenruo 2017.  All rights reserved.
 */

#अगर_अघोषित BTRFS_TREE_CHECKER_H
#घोषणा BTRFS_TREE_CHECKER_H

#समावेश "ctree.h"
#समावेश "extent_io.h"

/*
 * Comprehensive leaf checker.
 * Will check not only the item poपूर्णांकers, but also every possible member
 * in item data.
 */
पूर्णांक btrfs_check_leaf_full(काष्ठा extent_buffer *leaf);

/*
 * Less strict leaf checker.
 * Will only check item poपूर्णांकers, not पढ़ोing item data.
 */
पूर्णांक btrfs_check_leaf_relaxed(काष्ठा extent_buffer *leaf);
पूर्णांक btrfs_check_node(काष्ठा extent_buffer *node);

पूर्णांक btrfs_check_chunk_valid(काष्ठा extent_buffer *leaf,
			    काष्ठा btrfs_chunk *chunk, u64 logical);

#पूर्ण_अगर
