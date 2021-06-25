<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * mdt.h - NILFS meta data file prototype and definitions
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 */

#अगर_अघोषित _NILFS_MDT_H
#घोषणा _NILFS_MDT_H

#समावेश <linux/buffer_head.h>
#समावेश <linux/blockgroup_lock.h>
#समावेश "nilfs.h"
#समावेश "page.h"

/**
 * काष्ठा nilfs_shaकरोw_map - shaकरोw mapping of meta data file
 * @bmap_store: shaकरोw copy of bmap state
 * @frozen_data: shaकरोwed dirty data pages
 * @frozen_btnodes: shaकरोwed dirty b-tree nodes' pages
 * @frozen_buffers: list of frozen buffers
 */
काष्ठा nilfs_shaकरोw_map अणु
	काष्ठा nilfs_bmap_store bmap_store;
	काष्ठा address_space frozen_data;
	काष्ठा address_space frozen_btnodes;
	काष्ठा list_head frozen_buffers;
पूर्ण;

/**
 * काष्ठा nilfs_mdt_info - on-memory निजी data of meta data files
 * @mi_sem: पढ़ोer/ग_लिखोr semaphore क्रम meta data operations
 * @mi_bgl: per-blockgroup locking
 * @mi_entry_size: size of an entry
 * @mi_first_entry_offset: offset to the first entry
 * @mi_entries_per_block: number of entries in a block
 * @mi_palloc_cache: persistent object allocator cache
 * @mi_shaकरोw: shaकरोw of bmap and page caches
 * @mi_blocks_per_group: number of blocks in a group
 * @mi_blocks_per_desc_block: number of blocks per descriptor block
 */
काष्ठा nilfs_mdt_info अणु
	काष्ठा rw_semaphore	mi_sem;
	काष्ठा blockgroup_lock *mi_bgl;
	अचिन्हित पूर्णांक		mi_entry_size;
	अचिन्हित पूर्णांक		mi_first_entry_offset;
	अचिन्हित दीर्घ		mi_entries_per_block;
	काष्ठा nilfs_palloc_cache *mi_palloc_cache;
	काष्ठा nilfs_shaकरोw_map *mi_shaकरोw;
	अचिन्हित दीर्घ		mi_blocks_per_group;
	अचिन्हित दीर्घ		mi_blocks_per_desc_block;
पूर्ण;

अटल अंतरभूत काष्ठा nilfs_mdt_info *NILFS_MDT(स्थिर काष्ठा inode *inode)
अणु
	वापस inode->i_निजी;
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_is_metadata_file_inode(स्थिर काष्ठा inode *inode)
अणु
	वापस inode->i_निजी != शून्य;
पूर्ण

/* Default GFP flags using highmem */
#घोषणा NILFS_MDT_GFP      (__GFP_RECLAIM | __GFP_IO | __GFP_HIGHMEM)

पूर्णांक nilfs_mdt_get_block(काष्ठा inode *, अचिन्हित दीर्घ, पूर्णांक,
			व्योम (*init_block)(काष्ठा inode *,
					   काष्ठा buffer_head *, व्योम *),
			काष्ठा buffer_head **);
पूर्णांक nilfs_mdt_find_block(काष्ठा inode *inode, अचिन्हित दीर्घ start,
			 अचिन्हित दीर्घ end, अचिन्हित दीर्घ *blkoff,
			 काष्ठा buffer_head **out_bh);
पूर्णांक nilfs_mdt_delete_block(काष्ठा inode *, अचिन्हित दीर्घ);
पूर्णांक nilfs_mdt_क्रमget_block(काष्ठा inode *, अचिन्हित दीर्घ);
पूर्णांक nilfs_mdt_fetch_dirty(काष्ठा inode *);

पूर्णांक nilfs_mdt_init(काष्ठा inode *inode, gfp_t gfp_mask, माप_प्रकार objsz);
व्योम nilfs_mdt_clear(काष्ठा inode *inode);
व्योम nilfs_mdt_destroy(काष्ठा inode *inode);

व्योम nilfs_mdt_set_entry_size(काष्ठा inode *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

पूर्णांक nilfs_mdt_setup_shaकरोw_map(काष्ठा inode *inode,
			       काष्ठा nilfs_shaकरोw_map *shaकरोw);
पूर्णांक nilfs_mdt_save_to_shaकरोw_map(काष्ठा inode *inode);
व्योम nilfs_mdt_restore_from_shaकरोw_map(काष्ठा inode *inode);
व्योम nilfs_mdt_clear_shaकरोw_map(काष्ठा inode *inode);
पूर्णांक nilfs_mdt_मुक्तze_buffer(काष्ठा inode *inode, काष्ठा buffer_head *bh);
काष्ठा buffer_head *nilfs_mdt_get_frozen_buffer(काष्ठा inode *inode,
						काष्ठा buffer_head *bh);

अटल अंतरभूत व्योम nilfs_mdt_mark_dirty(काष्ठा inode *inode)
अणु
	अगर (!test_bit(NILFS_I_सूचीTY, &NILFS_I(inode)->i_state))
		set_bit(NILFS_I_सूचीTY, &NILFS_I(inode)->i_state);
पूर्ण

अटल अंतरभूत व्योम nilfs_mdt_clear_dirty(काष्ठा inode *inode)
अणु
	clear_bit(NILFS_I_सूचीTY, &NILFS_I(inode)->i_state);
पूर्ण

अटल अंतरभूत __u64 nilfs_mdt_cno(काष्ठा inode *inode)
अणु
	वापस ((काष्ठा the_nilfs *)inode->i_sb->s_fs_info)->ns_cno;
पूर्ण

अटल अंतरभूत spinlock_t *
nilfs_mdt_bgl_lock(काष्ठा inode *inode, अचिन्हित पूर्णांक block_group)
अणु
	वापस bgl_lock_ptr(NILFS_MDT(inode)->mi_bgl, block_group);
पूर्ण

#पूर्ण_अगर /* _NILFS_MDT_H */
