<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * alloc.c - NILFS dat/inode allocator
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Originally written by Koji Sato.
 * Two allocators were unअगरied by Ryusuke Konishi and Amagai Yoshiji.
 */

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/fs.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश "mdt.h"
#समावेश "alloc.h"


/**
 * nilfs_palloc_groups_per_desc_block - get the number of groups that a group
 *					descriptor block can मुख्यtain
 * @inode: inode of metadata file using this allocator
 */
अटल अंतरभूत अचिन्हित दीर्घ
nilfs_palloc_groups_per_desc_block(स्थिर काष्ठा inode *inode)
अणु
	वापस i_blocksize(inode) /
		माप(काष्ठा nilfs_palloc_group_desc);
पूर्ण

/**
 * nilfs_palloc_groups_count - get maximum number of groups
 * @inode: inode of metadata file using this allocator
 */
अटल अंतरभूत अचिन्हित दीर्घ
nilfs_palloc_groups_count(स्थिर काष्ठा inode *inode)
अणु
	वापस 1UL << (BITS_PER_LONG - (inode->i_blkbits + 3 /* log2(8) */));
पूर्ण

/**
 * nilfs_palloc_init_blockgroup - initialize निजी variables क्रम allocator
 * @inode: inode of metadata file using this allocator
 * @entry_size: size of the persistent object
 */
पूर्णांक nilfs_palloc_init_blockgroup(काष्ठा inode *inode, अचिन्हित पूर्णांक entry_size)
अणु
	काष्ठा nilfs_mdt_info *mi = NILFS_MDT(inode);

	mi->mi_bgl = kदो_स्मृति(माप(*mi->mi_bgl), GFP_NOFS);
	अगर (!mi->mi_bgl)
		वापस -ENOMEM;

	bgl_lock_init(mi->mi_bgl);

	nilfs_mdt_set_entry_size(inode, entry_size, 0);

	mi->mi_blocks_per_group =
		DIV_ROUND_UP(nilfs_palloc_entries_per_group(inode),
			     mi->mi_entries_per_block) + 1;
		/*
		 * Number of blocks in a group including entry blocks
		 * and a biपंचांगap block
		 */
	mi->mi_blocks_per_desc_block =
		nilfs_palloc_groups_per_desc_block(inode) *
		mi->mi_blocks_per_group + 1;
		/*
		 * Number of blocks per descriptor including the
		 * descriptor block
		 */
	वापस 0;
पूर्ण

/**
 * nilfs_palloc_group - get group number and offset from an entry number
 * @inode: inode of metadata file using this allocator
 * @nr: serial number of the entry (e.g. inode number)
 * @offset: poपूर्णांकer to store offset number in the group
 */
अटल अचिन्हित दीर्घ nilfs_palloc_group(स्थिर काष्ठा inode *inode, __u64 nr,
					अचिन्हित दीर्घ *offset)
अणु
	__u64 group = nr;

	*offset = करो_भाग(group, nilfs_palloc_entries_per_group(inode));
	वापस group;
पूर्ण

/**
 * nilfs_palloc_desc_blkoff - get block offset of a group descriptor block
 * @inode: inode of metadata file using this allocator
 * @group: group number
 *
 * nilfs_palloc_desc_blkoff() वापसs block offset of the descriptor
 * block which contains a descriptor of the specअगरied group.
 */
अटल अचिन्हित दीर्घ
nilfs_palloc_desc_blkoff(स्थिर काष्ठा inode *inode, अचिन्हित दीर्घ group)
अणु
	अचिन्हित दीर्घ desc_block =
		group / nilfs_palloc_groups_per_desc_block(inode);
	वापस desc_block * NILFS_MDT(inode)->mi_blocks_per_desc_block;
पूर्ण

/**
 * nilfs_palloc_biपंचांगap_blkoff - get block offset of a biपंचांगap block
 * @inode: inode of metadata file using this allocator
 * @group: group number
 *
 * nilfs_palloc_biपंचांगap_blkoff() वापसs block offset of the biपंचांगap
 * block used to allocate/deallocate entries in the specअगरied group.
 */
अटल अचिन्हित दीर्घ
nilfs_palloc_biपंचांगap_blkoff(स्थिर काष्ठा inode *inode, अचिन्हित दीर्घ group)
अणु
	अचिन्हित दीर्घ desc_offset =
		group % nilfs_palloc_groups_per_desc_block(inode);
	वापस nilfs_palloc_desc_blkoff(inode, group) + 1 +
		desc_offset * NILFS_MDT(inode)->mi_blocks_per_group;
पूर्ण

/**
 * nilfs_palloc_group_desc_nमुक्तs - get the number of मुक्त entries in a group
 * @desc: poपूर्णांकer to descriptor काष्ठाure क्रम the group
 * @lock: spin lock protecting @desc
 */
अटल अचिन्हित दीर्घ
nilfs_palloc_group_desc_nमुक्तs(स्थिर काष्ठा nilfs_palloc_group_desc *desc,
			       spinlock_t *lock)
अणु
	अचिन्हित दीर्घ nमुक्त;

	spin_lock(lock);
	nमुक्त = le32_to_cpu(desc->pg_nमुक्तs);
	spin_unlock(lock);
	वापस nमुक्त;
पूर्ण

/**
 * nilfs_palloc_group_desc_add_entries - adjust count of मुक्त entries
 * @desc: poपूर्णांकer to descriptor काष्ठाure क्रम the group
 * @lock: spin lock protecting @desc
 * @n: delta to be added
 */
अटल u32
nilfs_palloc_group_desc_add_entries(काष्ठा nilfs_palloc_group_desc *desc,
				    spinlock_t *lock, u32 n)
अणु
	u32 nमुक्त;

	spin_lock(lock);
	le32_add_cpu(&desc->pg_nमुक्तs, n);
	nमुक्त = le32_to_cpu(desc->pg_nमुक्तs);
	spin_unlock(lock);
	वापस nमुक्त;
पूर्ण

/**
 * nilfs_palloc_entry_blkoff - get block offset of an entry block
 * @inode: inode of metadata file using this allocator
 * @nr: serial number of the entry (e.g. inode number)
 */
अटल अचिन्हित दीर्घ
nilfs_palloc_entry_blkoff(स्थिर काष्ठा inode *inode, __u64 nr)
अणु
	अचिन्हित दीर्घ group, group_offset;

	group = nilfs_palloc_group(inode, nr, &group_offset);

	वापस nilfs_palloc_biपंचांगap_blkoff(inode, group) + 1 +
		group_offset / NILFS_MDT(inode)->mi_entries_per_block;
पूर्ण

/**
 * nilfs_palloc_desc_block_init - initialize buffer of a group descriptor block
 * @inode: inode of metadata file
 * @bh: buffer head of the buffer to be initialized
 * @kaddr: kernel address mapped क्रम the page including the buffer
 */
अटल व्योम nilfs_palloc_desc_block_init(काष्ठा inode *inode,
					 काष्ठा buffer_head *bh, व्योम *kaddr)
अणु
	काष्ठा nilfs_palloc_group_desc *desc = kaddr + bh_offset(bh);
	अचिन्हित दीर्घ n = nilfs_palloc_groups_per_desc_block(inode);
	__le32 nमुक्तs;

	nमुक्तs = cpu_to_le32(nilfs_palloc_entries_per_group(inode));
	जबतक (n-- > 0) अणु
		desc->pg_nमुक्तs = nमुक्तs;
		desc++;
	पूर्ण
पूर्ण

अटल पूर्णांक nilfs_palloc_get_block(काष्ठा inode *inode, अचिन्हित दीर्घ blkoff,
				  पूर्णांक create,
				  व्योम (*init_block)(काष्ठा inode *,
						     काष्ठा buffer_head *,
						     व्योम *),
				  काष्ठा buffer_head **bhp,
				  काष्ठा nilfs_bh_assoc *prev,
				  spinlock_t *lock)
अणु
	पूर्णांक ret;

	spin_lock(lock);
	अगर (prev->bh && blkoff == prev->blkoff) अणु
		get_bh(prev->bh);
		*bhp = prev->bh;
		spin_unlock(lock);
		वापस 0;
	पूर्ण
	spin_unlock(lock);

	ret = nilfs_mdt_get_block(inode, blkoff, create, init_block, bhp);
	अगर (!ret) अणु
		spin_lock(lock);
		/*
		 * The following code must be safe क्रम change of the
		 * cache contents during the get block call.
		 */
		brअन्यथा(prev->bh);
		get_bh(*bhp);
		prev->bh = *bhp;
		prev->blkoff = blkoff;
		spin_unlock(lock);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nilfs_palloc_delete_block - delete a block on the persistent allocator file
 * @inode: inode of metadata file using this allocator
 * @blkoff: block offset
 * @prev: nilfs_bh_assoc काष्ठा of the last used buffer
 * @lock: spin lock protecting @prev
 */
अटल पूर्णांक nilfs_palloc_delete_block(काष्ठा inode *inode, अचिन्हित दीर्घ blkoff,
				     काष्ठा nilfs_bh_assoc *prev,
				     spinlock_t *lock)
अणु
	spin_lock(lock);
	अगर (prev->bh && blkoff == prev->blkoff) अणु
		brअन्यथा(prev->bh);
		prev->bh = शून्य;
	पूर्ण
	spin_unlock(lock);
	वापस nilfs_mdt_delete_block(inode, blkoff);
पूर्ण

/**
 * nilfs_palloc_get_desc_block - get buffer head of a group descriptor block
 * @inode: inode of metadata file using this allocator
 * @group: group number
 * @create: create flag
 * @bhp: poपूर्णांकer to store the resultant buffer head
 */
अटल पूर्णांक nilfs_palloc_get_desc_block(काष्ठा inode *inode,
				       अचिन्हित दीर्घ group,
				       पूर्णांक create, काष्ठा buffer_head **bhp)
अणु
	काष्ठा nilfs_palloc_cache *cache = NILFS_MDT(inode)->mi_palloc_cache;

	वापस nilfs_palloc_get_block(inode,
				      nilfs_palloc_desc_blkoff(inode, group),
				      create, nilfs_palloc_desc_block_init,
				      bhp, &cache->prev_desc, &cache->lock);
पूर्ण

/**
 * nilfs_palloc_get_biपंचांगap_block - get buffer head of a biपंचांगap block
 * @inode: inode of metadata file using this allocator
 * @group: group number
 * @create: create flag
 * @bhp: poपूर्णांकer to store the resultant buffer head
 */
अटल पूर्णांक nilfs_palloc_get_biपंचांगap_block(काष्ठा inode *inode,
					 अचिन्हित दीर्घ group,
					 पूर्णांक create, काष्ठा buffer_head **bhp)
अणु
	काष्ठा nilfs_palloc_cache *cache = NILFS_MDT(inode)->mi_palloc_cache;

	वापस nilfs_palloc_get_block(inode,
				      nilfs_palloc_biपंचांगap_blkoff(inode, group),
				      create, शून्य, bhp,
				      &cache->prev_biपंचांगap, &cache->lock);
पूर्ण

/**
 * nilfs_palloc_delete_biपंचांगap_block - delete a biपंचांगap block
 * @inode: inode of metadata file using this allocator
 * @group: group number
 */
अटल पूर्णांक nilfs_palloc_delete_biपंचांगap_block(काष्ठा inode *inode,
					    अचिन्हित दीर्घ group)
अणु
	काष्ठा nilfs_palloc_cache *cache = NILFS_MDT(inode)->mi_palloc_cache;

	वापस nilfs_palloc_delete_block(inode,
					 nilfs_palloc_biपंचांगap_blkoff(inode,
								    group),
					 &cache->prev_biपंचांगap, &cache->lock);
पूर्ण

/**
 * nilfs_palloc_get_entry_block - get buffer head of an entry block
 * @inode: inode of metadata file using this allocator
 * @nr: serial number of the entry (e.g. inode number)
 * @create: create flag
 * @bhp: poपूर्णांकer to store the resultant buffer head
 */
पूर्णांक nilfs_palloc_get_entry_block(काष्ठा inode *inode, __u64 nr,
				 पूर्णांक create, काष्ठा buffer_head **bhp)
अणु
	काष्ठा nilfs_palloc_cache *cache = NILFS_MDT(inode)->mi_palloc_cache;

	वापस nilfs_palloc_get_block(inode,
				      nilfs_palloc_entry_blkoff(inode, nr),
				      create, शून्य, bhp,
				      &cache->prev_entry, &cache->lock);
पूर्ण

/**
 * nilfs_palloc_delete_entry_block - delete an entry block
 * @inode: inode of metadata file using this allocator
 * @nr: serial number of the entry
 */
अटल पूर्णांक nilfs_palloc_delete_entry_block(काष्ठा inode *inode, __u64 nr)
अणु
	काष्ठा nilfs_palloc_cache *cache = NILFS_MDT(inode)->mi_palloc_cache;

	वापस nilfs_palloc_delete_block(inode,
					 nilfs_palloc_entry_blkoff(inode, nr),
					 &cache->prev_entry, &cache->lock);
पूर्ण

/**
 * nilfs_palloc_block_get_group_desc - get kernel address of a group descriptor
 * @inode: inode of metadata file using this allocator
 * @group: group number
 * @bh: buffer head of the buffer storing the group descriptor block
 * @kaddr: kernel address mapped क्रम the page including the buffer
 */
अटल काष्ठा nilfs_palloc_group_desc *
nilfs_palloc_block_get_group_desc(स्थिर काष्ठा inode *inode,
				  अचिन्हित दीर्घ group,
				  स्थिर काष्ठा buffer_head *bh, व्योम *kaddr)
अणु
	वापस (काष्ठा nilfs_palloc_group_desc *)(kaddr + bh_offset(bh)) +
		group % nilfs_palloc_groups_per_desc_block(inode);
पूर्ण

/**
 * nilfs_palloc_block_get_entry - get kernel address of an entry
 * @inode: inode of metadata file using this allocator
 * @nr: serial number of the entry (e.g. inode number)
 * @bh: buffer head of the buffer storing the entry block
 * @kaddr: kernel address mapped क्रम the page including the buffer
 */
व्योम *nilfs_palloc_block_get_entry(स्थिर काष्ठा inode *inode, __u64 nr,
				   स्थिर काष्ठा buffer_head *bh, व्योम *kaddr)
अणु
	अचिन्हित दीर्घ entry_offset, group_offset;

	nilfs_palloc_group(inode, nr, &group_offset);
	entry_offset = group_offset % NILFS_MDT(inode)->mi_entries_per_block;

	वापस kaddr + bh_offset(bh) +
		entry_offset * NILFS_MDT(inode)->mi_entry_size;
पूर्ण

/**
 * nilfs_palloc_find_available_slot - find available slot in a group
 * @biपंचांगap: biपंचांगap of the group
 * @target: offset number of an entry in the group (start poपूर्णांक)
 * @bsize: size in bits
 * @lock: spin lock protecting @biपंचांगap
 */
अटल पूर्णांक nilfs_palloc_find_available_slot(अचिन्हित अक्षर *biपंचांगap,
					    अचिन्हित दीर्घ target,
					    अचिन्हित पूर्णांक bsize,
					    spinlock_t *lock)
अणु
	पूर्णांक pos, end = bsize;

	अगर (likely(target < bsize)) अणु
		pos = target;
		करो अणु
			pos = nilfs_find_next_zero_bit(biपंचांगap, end, pos);
			अगर (pos >= end)
				अवरोध;
			अगर (!nilfs_set_bit_atomic(lock, pos, biपंचांगap))
				वापस pos;
		पूर्ण जबतक (++pos < end);

		end = target;
	पूर्ण

	/* wrap around */
	क्रम (pos = 0; pos < end; pos++) अणु
		pos = nilfs_find_next_zero_bit(biपंचांगap, end, pos);
		अगर (pos >= end)
			अवरोध;
		अगर (!nilfs_set_bit_atomic(lock, pos, biपंचांगap))
			वापस pos;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

/**
 * nilfs_palloc_rest_groups_in_desc_block - get the reमुख्यing number of groups
 *					    in a group descriptor block
 * @inode: inode of metadata file using this allocator
 * @curr: current group number
 * @max: maximum number of groups
 */
अटल अचिन्हित दीर्घ
nilfs_palloc_rest_groups_in_desc_block(स्थिर काष्ठा inode *inode,
				       अचिन्हित दीर्घ curr, अचिन्हित दीर्घ max)
अणु
	वापस min_t(अचिन्हित दीर्घ,
		     nilfs_palloc_groups_per_desc_block(inode) -
		     curr % nilfs_palloc_groups_per_desc_block(inode),
		     max - curr + 1);
पूर्ण

/**
 * nilfs_palloc_count_desc_blocks - count descriptor blocks number
 * @inode: inode of metadata file using this allocator
 * @desc_blocks: descriptor blocks number [out]
 */
अटल पूर्णांक nilfs_palloc_count_desc_blocks(काष्ठा inode *inode,
					    अचिन्हित दीर्घ *desc_blocks)
अणु
	__u64 blknum;
	पूर्णांक ret;

	ret = nilfs_bmap_last_key(NILFS_I(inode)->i_bmap, &blknum);
	अगर (likely(!ret))
		*desc_blocks = DIV_ROUND_UP(
			(अचिन्हित दीर्घ)blknum,
			NILFS_MDT(inode)->mi_blocks_per_desc_block);
	वापस ret;
पूर्ण

/**
 * nilfs_palloc_mdt_file_can_grow - check potential opportunity क्रम
 *					MDT file growing
 * @inode: inode of metadata file using this allocator
 * @desc_blocks: known current descriptor blocks count
 */
अटल अंतरभूत bool nilfs_palloc_mdt_file_can_grow(काष्ठा inode *inode,
						    अचिन्हित दीर्घ desc_blocks)
अणु
	वापस (nilfs_palloc_groups_per_desc_block(inode) * desc_blocks) <
			nilfs_palloc_groups_count(inode);
पूर्ण

/**
 * nilfs_palloc_count_max_entries - count max number of entries that can be
 *					described by descriptor blocks count
 * @inode: inode of metadata file using this allocator
 * @nused: current number of used entries
 * @nmaxp: max number of entries [out]
 */
पूर्णांक nilfs_palloc_count_max_entries(काष्ठा inode *inode, u64 nused, u64 *nmaxp)
अणु
	अचिन्हित दीर्घ desc_blocks = 0;
	u64 entries_per_desc_block, nmax;
	पूर्णांक err;

	err = nilfs_palloc_count_desc_blocks(inode, &desc_blocks);
	अगर (unlikely(err))
		वापस err;

	entries_per_desc_block = (u64)nilfs_palloc_entries_per_group(inode) *
				nilfs_palloc_groups_per_desc_block(inode);
	nmax = entries_per_desc_block * desc_blocks;

	अगर (nused == nmax &&
			nilfs_palloc_mdt_file_can_grow(inode, desc_blocks))
		nmax += entries_per_desc_block;

	अगर (nused > nmax)
		वापस -दुस्फल;

	*nmaxp = nmax;
	वापस 0;
पूर्ण

/**
 * nilfs_palloc_prepare_alloc_entry - prepare to allocate a persistent object
 * @inode: inode of metadata file using this allocator
 * @req: nilfs_palloc_req काष्ठाure exchanged क्रम the allocation
 */
पूर्णांक nilfs_palloc_prepare_alloc_entry(काष्ठा inode *inode,
				     काष्ठा nilfs_palloc_req *req)
अणु
	काष्ठा buffer_head *desc_bh, *biपंचांगap_bh;
	काष्ठा nilfs_palloc_group_desc *desc;
	अचिन्हित अक्षर *biपंचांगap;
	व्योम *desc_kaddr, *biपंचांगap_kaddr;
	अचिन्हित दीर्घ group, maxgroup, ngroups;
	अचिन्हित दीर्घ group_offset, maxgroup_offset;
	अचिन्हित दीर्घ n, entries_per_group;
	अचिन्हित दीर्घ i, j;
	spinlock_t *lock;
	पूर्णांक pos, ret;

	ngroups = nilfs_palloc_groups_count(inode);
	maxgroup = ngroups - 1;
	group = nilfs_palloc_group(inode, req->pr_entry_nr, &group_offset);
	entries_per_group = nilfs_palloc_entries_per_group(inode);

	क्रम (i = 0; i < ngroups; i += n) अणु
		अगर (group >= ngroups) अणु
			/* wrap around */
			group = 0;
			maxgroup = nilfs_palloc_group(inode, req->pr_entry_nr,
						      &maxgroup_offset) - 1;
		पूर्ण
		ret = nilfs_palloc_get_desc_block(inode, group, 1, &desc_bh);
		अगर (ret < 0)
			वापस ret;
		desc_kaddr = kmap(desc_bh->b_page);
		desc = nilfs_palloc_block_get_group_desc(
			inode, group, desc_bh, desc_kaddr);
		n = nilfs_palloc_rest_groups_in_desc_block(inode, group,
							   maxgroup);
		क्रम (j = 0; j < n; j++, desc++, group++) अणु
			lock = nilfs_mdt_bgl_lock(inode, group);
			अगर (nilfs_palloc_group_desc_nमुक्तs(desc, lock) > 0) अणु
				ret = nilfs_palloc_get_biपंचांगap_block(
					inode, group, 1, &biपंचांगap_bh);
				अगर (ret < 0)
					जाओ out_desc;
				biपंचांगap_kaddr = kmap(biपंचांगap_bh->b_page);
				biपंचांगap = biपंचांगap_kaddr + bh_offset(biपंचांगap_bh);
				pos = nilfs_palloc_find_available_slot(
					biपंचांगap, group_offset,
					entries_per_group, lock);
				अगर (pos >= 0) अणु
					/* found a मुक्त entry */
					nilfs_palloc_group_desc_add_entries(
						desc, lock, -1);
					req->pr_entry_nr =
						entries_per_group * group + pos;
					kunmap(desc_bh->b_page);
					kunmap(biपंचांगap_bh->b_page);

					req->pr_desc_bh = desc_bh;
					req->pr_biपंचांगap_bh = biपंचांगap_bh;
					वापस 0;
				पूर्ण
				kunmap(biपंचांगap_bh->b_page);
				brअन्यथा(biपंचांगap_bh);
			पूर्ण

			group_offset = 0;
		पूर्ण

		kunmap(desc_bh->b_page);
		brअन्यथा(desc_bh);
	पूर्ण

	/* no entries left */
	वापस -ENOSPC;

 out_desc:
	kunmap(desc_bh->b_page);
	brअन्यथा(desc_bh);
	वापस ret;
पूर्ण

/**
 * nilfs_palloc_commit_alloc_entry - finish allocation of a persistent object
 * @inode: inode of metadata file using this allocator
 * @req: nilfs_palloc_req काष्ठाure exchanged क्रम the allocation
 */
व्योम nilfs_palloc_commit_alloc_entry(काष्ठा inode *inode,
				     काष्ठा nilfs_palloc_req *req)
अणु
	mark_buffer_dirty(req->pr_biपंचांगap_bh);
	mark_buffer_dirty(req->pr_desc_bh);
	nilfs_mdt_mark_dirty(inode);

	brअन्यथा(req->pr_biपंचांगap_bh);
	brअन्यथा(req->pr_desc_bh);
पूर्ण

/**
 * nilfs_palloc_commit_मुक्त_entry - finish deallocating a persistent object
 * @inode: inode of metadata file using this allocator
 * @req: nilfs_palloc_req काष्ठाure exchanged क्रम the removal
 */
व्योम nilfs_palloc_commit_मुक्त_entry(काष्ठा inode *inode,
				    काष्ठा nilfs_palloc_req *req)
अणु
	काष्ठा nilfs_palloc_group_desc *desc;
	अचिन्हित दीर्घ group, group_offset;
	अचिन्हित अक्षर *biपंचांगap;
	व्योम *desc_kaddr, *biपंचांगap_kaddr;
	spinlock_t *lock;

	group = nilfs_palloc_group(inode, req->pr_entry_nr, &group_offset);
	desc_kaddr = kmap(req->pr_desc_bh->b_page);
	desc = nilfs_palloc_block_get_group_desc(inode, group,
						 req->pr_desc_bh, desc_kaddr);
	biपंचांगap_kaddr = kmap(req->pr_biपंचांगap_bh->b_page);
	biपंचांगap = biपंचांगap_kaddr + bh_offset(req->pr_biपंचांगap_bh);
	lock = nilfs_mdt_bgl_lock(inode, group);

	अगर (!nilfs_clear_bit_atomic(lock, group_offset, biपंचांगap))
		nilfs_warn(inode->i_sb,
			   "%s (ino=%lu): entry number %llu already freed",
			   __func__, inode->i_ino,
			   (अचिन्हित दीर्घ दीर्घ)req->pr_entry_nr);
	अन्यथा
		nilfs_palloc_group_desc_add_entries(desc, lock, 1);

	kunmap(req->pr_biपंचांगap_bh->b_page);
	kunmap(req->pr_desc_bh->b_page);

	mark_buffer_dirty(req->pr_desc_bh);
	mark_buffer_dirty(req->pr_biपंचांगap_bh);
	nilfs_mdt_mark_dirty(inode);

	brअन्यथा(req->pr_biपंचांगap_bh);
	brअन्यथा(req->pr_desc_bh);
पूर्ण

/**
 * nilfs_palloc_पात_alloc_entry - cancel allocation of a persistent object
 * @inode: inode of metadata file using this allocator
 * @req: nilfs_palloc_req काष्ठाure exchanged क्रम the allocation
 */
व्योम nilfs_palloc_पात_alloc_entry(काष्ठा inode *inode,
				    काष्ठा nilfs_palloc_req *req)
अणु
	काष्ठा nilfs_palloc_group_desc *desc;
	व्योम *desc_kaddr, *biपंचांगap_kaddr;
	अचिन्हित अक्षर *biपंचांगap;
	अचिन्हित दीर्घ group, group_offset;
	spinlock_t *lock;

	group = nilfs_palloc_group(inode, req->pr_entry_nr, &group_offset);
	desc_kaddr = kmap(req->pr_desc_bh->b_page);
	desc = nilfs_palloc_block_get_group_desc(inode, group,
						 req->pr_desc_bh, desc_kaddr);
	biपंचांगap_kaddr = kmap(req->pr_biपंचांगap_bh->b_page);
	biपंचांगap = biपंचांगap_kaddr + bh_offset(req->pr_biपंचांगap_bh);
	lock = nilfs_mdt_bgl_lock(inode, group);

	अगर (!nilfs_clear_bit_atomic(lock, group_offset, biपंचांगap))
		nilfs_warn(inode->i_sb,
			   "%s (ino=%lu): entry number %llu already freed",
			   __func__, inode->i_ino,
			   (अचिन्हित दीर्घ दीर्घ)req->pr_entry_nr);
	अन्यथा
		nilfs_palloc_group_desc_add_entries(desc, lock, 1);

	kunmap(req->pr_biपंचांगap_bh->b_page);
	kunmap(req->pr_desc_bh->b_page);

	brअन्यथा(req->pr_biपंचांगap_bh);
	brअन्यथा(req->pr_desc_bh);

	req->pr_entry_nr = 0;
	req->pr_biपंचांगap_bh = शून्य;
	req->pr_desc_bh = शून्य;
पूर्ण

/**
 * nilfs_palloc_prepare_मुक्त_entry - prepare to deallocate a persistent object
 * @inode: inode of metadata file using this allocator
 * @req: nilfs_palloc_req काष्ठाure exchanged क्रम the removal
 */
पूर्णांक nilfs_palloc_prepare_मुक्त_entry(काष्ठा inode *inode,
				    काष्ठा nilfs_palloc_req *req)
अणु
	काष्ठा buffer_head *desc_bh, *biपंचांगap_bh;
	अचिन्हित दीर्घ group, group_offset;
	पूर्णांक ret;

	group = nilfs_palloc_group(inode, req->pr_entry_nr, &group_offset);
	ret = nilfs_palloc_get_desc_block(inode, group, 1, &desc_bh);
	अगर (ret < 0)
		वापस ret;
	ret = nilfs_palloc_get_biपंचांगap_block(inode, group, 1, &biपंचांगap_bh);
	अगर (ret < 0) अणु
		brअन्यथा(desc_bh);
		वापस ret;
	पूर्ण

	req->pr_desc_bh = desc_bh;
	req->pr_biपंचांगap_bh = biपंचांगap_bh;
	वापस 0;
पूर्ण

/**
 * nilfs_palloc_पात_मुक्त_entry - cancel deallocating a persistent object
 * @inode: inode of metadata file using this allocator
 * @req: nilfs_palloc_req काष्ठाure exchanged क्रम the removal
 */
व्योम nilfs_palloc_पात_मुक्त_entry(काष्ठा inode *inode,
				   काष्ठा nilfs_palloc_req *req)
अणु
	brअन्यथा(req->pr_biपंचांगap_bh);
	brअन्यथा(req->pr_desc_bh);

	req->pr_entry_nr = 0;
	req->pr_biपंचांगap_bh = शून्य;
	req->pr_desc_bh = शून्य;
पूर्ण

/**
 * nilfs_palloc_मुक्तv - deallocate a set of persistent objects
 * @inode: inode of metadata file using this allocator
 * @entry_nrs: array of entry numbers to be deallocated
 * @nitems: number of entries stored in @entry_nrs
 */
पूर्णांक nilfs_palloc_मुक्तv(काष्ठा inode *inode, __u64 *entry_nrs, माप_प्रकार nitems)
अणु
	काष्ठा buffer_head *desc_bh, *biपंचांगap_bh;
	काष्ठा nilfs_palloc_group_desc *desc;
	अचिन्हित अक्षर *biपंचांगap;
	व्योम *desc_kaddr, *biपंचांगap_kaddr;
	अचिन्हित दीर्घ group, group_offset;
	__u64 group_min_nr, last_nrs[8];
	स्थिर अचिन्हित दीर्घ epg = nilfs_palloc_entries_per_group(inode);
	स्थिर अचिन्हित पूर्णांक epb = NILFS_MDT(inode)->mi_entries_per_block;
	अचिन्हित पूर्णांक entry_start, end, pos;
	spinlock_t *lock;
	पूर्णांक i, j, k, ret;
	u32 nमुक्त;

	क्रम (i = 0; i < nitems; i = j) अणु
		पूर्णांक change_group = false;
		पूर्णांक nempties = 0, n = 0;

		group = nilfs_palloc_group(inode, entry_nrs[i], &group_offset);
		ret = nilfs_palloc_get_desc_block(inode, group, 0, &desc_bh);
		अगर (ret < 0)
			वापस ret;
		ret = nilfs_palloc_get_biपंचांगap_block(inode, group, 0,
						    &biपंचांगap_bh);
		अगर (ret < 0) अणु
			brअन्यथा(desc_bh);
			वापस ret;
		पूर्ण

		/* Get the first entry number of the group */
		group_min_nr = (__u64)group * epg;

		biपंचांगap_kaddr = kmap(biपंचांगap_bh->b_page);
		biपंचांगap = biपंचांगap_kaddr + bh_offset(biपंचांगap_bh);
		lock = nilfs_mdt_bgl_lock(inode, group);

		j = i;
		entry_start = roundकरोwn(group_offset, epb);
		करो अणु
			अगर (!nilfs_clear_bit_atomic(lock, group_offset,
						    biपंचांगap)) अणु
				nilfs_warn(inode->i_sb,
					   "%s (ino=%lu): entry number %llu already freed",
					   __func__, inode->i_ino,
					   (अचिन्हित दीर्घ दीर्घ)entry_nrs[j]);
			पूर्ण अन्यथा अणु
				n++;
			पूर्ण

			j++;
			अगर (j >= nitems || entry_nrs[j] < group_min_nr ||
			    entry_nrs[j] >= group_min_nr + epg) अणु
				change_group = true;
			पूर्ण अन्यथा अणु
				group_offset = entry_nrs[j] - group_min_nr;
				अगर (group_offset >= entry_start &&
				    group_offset < entry_start + epb) अणु
					/* This entry is in the same block */
					जारी;
				पूर्ण
			पूर्ण

			/* Test अगर the entry block is empty or not */
			end = entry_start + epb;
			pos = nilfs_find_next_bit(biपंचांगap, end, entry_start);
			अगर (pos >= end) अणु
				last_nrs[nempties++] = entry_nrs[j - 1];
				अगर (nempties >= ARRAY_SIZE(last_nrs))
					अवरोध;
			पूर्ण

			अगर (change_group)
				अवरोध;

			/* Go on to the next entry block */
			entry_start = roundकरोwn(group_offset, epb);
		पूर्ण जबतक (true);

		kunmap(biपंचांगap_bh->b_page);
		mark_buffer_dirty(biपंचांगap_bh);
		brअन्यथा(biपंचांगap_bh);

		क्रम (k = 0; k < nempties; k++) अणु
			ret = nilfs_palloc_delete_entry_block(inode,
							      last_nrs[k]);
			अगर (ret && ret != -ENOENT)
				nilfs_warn(inode->i_sb,
					   "error %d deleting block that object (entry=%llu, ino=%lu) belongs to",
					   ret, (अचिन्हित दीर्घ दीर्घ)last_nrs[k],
					   inode->i_ino);
		पूर्ण

		desc_kaddr = kmap_atomic(desc_bh->b_page);
		desc = nilfs_palloc_block_get_group_desc(
			inode, group, desc_bh, desc_kaddr);
		nमुक्त = nilfs_palloc_group_desc_add_entries(desc, lock, n);
		kunmap_atomic(desc_kaddr);
		mark_buffer_dirty(desc_bh);
		nilfs_mdt_mark_dirty(inode);
		brअन्यथा(desc_bh);

		अगर (nमुक्त == nilfs_palloc_entries_per_group(inode)) अणु
			ret = nilfs_palloc_delete_biपंचांगap_block(inode, group);
			अगर (ret && ret != -ENOENT)
				nilfs_warn(inode->i_sb,
					   "error %d deleting bitmap block of group=%lu, ino=%lu",
					   ret, group, inode->i_ino);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम nilfs_palloc_setup_cache(काष्ठा inode *inode,
			      काष्ठा nilfs_palloc_cache *cache)
अणु
	NILFS_MDT(inode)->mi_palloc_cache = cache;
	spin_lock_init(&cache->lock);
पूर्ण

व्योम nilfs_palloc_clear_cache(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_palloc_cache *cache = NILFS_MDT(inode)->mi_palloc_cache;

	spin_lock(&cache->lock);
	brअन्यथा(cache->prev_desc.bh);
	brअन्यथा(cache->prev_biपंचांगap.bh);
	brअन्यथा(cache->prev_entry.bh);
	cache->prev_desc.bh = शून्य;
	cache->prev_biपंचांगap.bh = शून्य;
	cache->prev_entry.bh = शून्य;
	spin_unlock(&cache->lock);
पूर्ण

व्योम nilfs_palloc_destroy_cache(काष्ठा inode *inode)
अणु
	nilfs_palloc_clear_cache(inode);
	NILFS_MDT(inode)->mi_palloc_cache = शून्य;
पूर्ण
