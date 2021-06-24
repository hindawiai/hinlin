<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित SQUASHFS_FS_SB
#घोषणा SQUASHFS_FS_SB
/*
 * Squashfs
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * squashfs_fs_sb.h
 */

#समावेश "squashfs_fs.h"

काष्ठा squashfs_cache अणु
	अक्षर			*name;
	पूर्णांक			entries;
	पूर्णांक			curr_blk;
	पूर्णांक			next_blk;
	पूर्णांक			num_रुकोers;
	पूर्णांक			unused;
	पूर्णांक			block_size;
	पूर्णांक			pages;
	spinlock_t		lock;
	रुको_queue_head_t	रुको_queue;
	काष्ठा squashfs_cache_entry *entry;
पूर्ण;

काष्ठा squashfs_cache_entry अणु
	u64			block;
	पूर्णांक			length;
	पूर्णांक			refcount;
	u64			next_index;
	पूर्णांक			pending;
	पूर्णांक			error;
	पूर्णांक			num_रुकोers;
	रुको_queue_head_t	रुको_queue;
	काष्ठा squashfs_cache	*cache;
	व्योम			**data;
	काष्ठा squashfs_page_actor	*actor;
पूर्ण;

काष्ठा squashfs_sb_info अणु
	स्थिर काष्ठा squashfs_decompressor	*decompressor;
	पूर्णांक					devblksize;
	पूर्णांक					devblksize_log2;
	काष्ठा squashfs_cache			*block_cache;
	काष्ठा squashfs_cache			*fragment_cache;
	काष्ठा squashfs_cache			*पढ़ो_page;
	पूर्णांक					next_meta_index;
	__le64					*id_table;
	__le64					*fragment_index;
	__le64					*xattr_id_table;
	काष्ठा mutex				meta_index_mutex;
	काष्ठा meta_index			*meta_index;
	काष्ठा squashfs_stream			*stream;
	__le64					*inode_lookup_table;
	u64					inode_table;
	u64					directory_table;
	u64					xattr_table;
	अचिन्हित पूर्णांक				block_size;
	अचिन्हित लघु				block_log;
	दीर्घ दीर्घ				bytes_used;
	अचिन्हित पूर्णांक				inodes;
	अचिन्हित पूर्णांक				fragments;
	पूर्णांक					xattr_ids;
	अचिन्हित पूर्णांक				ids;
पूर्ण;
#पूर्ण_अगर
