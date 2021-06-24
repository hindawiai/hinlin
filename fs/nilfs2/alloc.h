<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * भाग.स - persistent object (dat entry/disk inode) allocator/deallocator
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Originally written by Koji Sato.
 * Two allocators were unअगरied by Ryusuke Konishi and Amagai Yoshiji.
 */

#अगर_अघोषित _NILFS_ALLOC_H
#घोषणा _NILFS_ALLOC_H

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/fs.h>

/**
 * nilfs_palloc_entries_per_group - get the number of entries per group
 * @inode: inode of metadata file using this allocator
 *
 * The number of entries per group is defined by the number of bits
 * that a biपंचांगap block can मुख्यtain.
 */
अटल अंतरभूत अचिन्हित दीर्घ
nilfs_palloc_entries_per_group(स्थिर काष्ठा inode *inode)
अणु
	वापस 1UL << (inode->i_blkbits + 3 /* log2(8 = अक्षर_बिटS) */);
पूर्ण

पूर्णांक nilfs_palloc_init_blockgroup(काष्ठा inode *, अचिन्हित पूर्णांक);
पूर्णांक nilfs_palloc_get_entry_block(काष्ठा inode *, __u64, पूर्णांक,
				 काष्ठा buffer_head **);
व्योम *nilfs_palloc_block_get_entry(स्थिर काष्ठा inode *, __u64,
				   स्थिर काष्ठा buffer_head *, व्योम *);

पूर्णांक nilfs_palloc_count_max_entries(काष्ठा inode *, u64, u64 *);

/**
 * nilfs_palloc_req - persistent allocator request and reply
 * @pr_entry_nr: entry number (vblocknr or inode number)
 * @pr_desc_bh: buffer head of the buffer containing block group descriptors
 * @pr_biपंचांगap_bh: buffer head of the buffer containing a block group biपंचांगap
 * @pr_entry_bh: buffer head of the buffer containing translation entries
 */
काष्ठा nilfs_palloc_req अणु
	__u64 pr_entry_nr;
	काष्ठा buffer_head *pr_desc_bh;
	काष्ठा buffer_head *pr_biपंचांगap_bh;
	काष्ठा buffer_head *pr_entry_bh;
पूर्ण;

पूर्णांक nilfs_palloc_prepare_alloc_entry(काष्ठा inode *,
				     काष्ठा nilfs_palloc_req *);
व्योम nilfs_palloc_commit_alloc_entry(काष्ठा inode *,
				     काष्ठा nilfs_palloc_req *);
व्योम nilfs_palloc_पात_alloc_entry(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
व्योम nilfs_palloc_commit_मुक्त_entry(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
पूर्णांक nilfs_palloc_prepare_मुक्त_entry(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
व्योम nilfs_palloc_पात_मुक्त_entry(काष्ठा inode *, काष्ठा nilfs_palloc_req *);
पूर्णांक nilfs_palloc_मुक्तv(काष्ठा inode *, __u64 *, माप_प्रकार);

#घोषणा nilfs_set_bit_atomic		ext2_set_bit_atomic
#घोषणा nilfs_clear_bit_atomic		ext2_clear_bit_atomic
#घोषणा nilfs_find_next_zero_bit	find_next_zero_bit_le
#घोषणा nilfs_find_next_bit		find_next_bit_le

/**
 * काष्ठा nilfs_bh_assoc - block offset and buffer head association
 * @blkoff: block offset
 * @bh: buffer head
 */
काष्ठा nilfs_bh_assoc अणु
	अचिन्हित दीर्घ blkoff;
	काष्ठा buffer_head *bh;
पूर्ण;

/**
 * काष्ठा nilfs_palloc_cache - persistent object allocator cache
 * @lock: cache protecting lock
 * @prev_desc: blockgroup descriptors cache
 * @prev_biपंचांगap: blockgroup biपंचांगap cache
 * @prev_entry: translation entries cache
 */
काष्ठा nilfs_palloc_cache अणु
	spinlock_t lock;
	काष्ठा nilfs_bh_assoc prev_desc;
	काष्ठा nilfs_bh_assoc prev_biपंचांगap;
	काष्ठा nilfs_bh_assoc prev_entry;
पूर्ण;

व्योम nilfs_palloc_setup_cache(काष्ठा inode *inode,
			      काष्ठा nilfs_palloc_cache *cache);
व्योम nilfs_palloc_clear_cache(काष्ठा inode *inode);
व्योम nilfs_palloc_destroy_cache(काष्ठा inode *inode);

#पूर्ण_अगर	/* _NILFS_ALLOC_H */
