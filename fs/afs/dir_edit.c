<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS fileप्रणाली directory editing
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/iversion.h>
#समावेश "internal.h"
#समावेश "xdr_fs.h"

/*
 * Find a number of contiguous clear bits in a directory block biपंचांगask.
 *
 * There are 64 slots, which means we can load the entire biपंचांगap पूर्णांकo a
 * variable.  The first bit करोesn't count as it corresponds to the block header
 * slot.  nr_slots is between 1 and 9.
 */
अटल पूर्णांक afs_find_contig_bits(जोड़ afs_xdr_dir_block *block, अचिन्हित पूर्णांक nr_slots)
अणु
	u64 biपंचांगap;
	u32 mask;
	पूर्णांक bit, n;

	biपंचांगap  = (u64)block->hdr.biपंचांगap[0] << 0 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[1] << 1 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[2] << 2 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[3] << 3 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[4] << 4 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[5] << 5 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[6] << 6 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[7] << 7 * 8;
	biपंचांगap >>= 1; /* The first entry is metadata */
	bit = 1;
	mask = (1 << nr_slots) - 1;

	करो अणु
		अगर (माप(अचिन्हित दीर्घ) == 8)
			n = ffz(biपंचांगap);
		अन्यथा
			n = ((u32)biपंचांगap) != 0 ?
				ffz((u32)biपंचांगap) :
				ffz((u32)(biपंचांगap >> 32)) + 32;
		biपंचांगap >>= n;
		bit += n;

		अगर ((biपंचांगap & mask) == 0) अणु
			अगर (bit > 64 - nr_slots)
				वापस -1;
			वापस bit;
		पूर्ण

		n = __ffs(biपंचांगap);
		biपंचांगap >>= n;
		bit += n;
	पूर्ण जबतक (biपंचांगap);

	वापस -1;
पूर्ण

/*
 * Set a number of contiguous bits in the directory block biपंचांगap.
 */
अटल व्योम afs_set_contig_bits(जोड़ afs_xdr_dir_block *block,
				पूर्णांक bit, अचिन्हित पूर्णांक nr_slots)
अणु
	u64 mask;

	mask = (1 << nr_slots) - 1;
	mask <<= bit;

	block->hdr.biपंचांगap[0] |= (u8)(mask >> 0 * 8);
	block->hdr.biपंचांगap[1] |= (u8)(mask >> 1 * 8);
	block->hdr.biपंचांगap[2] |= (u8)(mask >> 2 * 8);
	block->hdr.biपंचांगap[3] |= (u8)(mask >> 3 * 8);
	block->hdr.biपंचांगap[4] |= (u8)(mask >> 4 * 8);
	block->hdr.biपंचांगap[5] |= (u8)(mask >> 5 * 8);
	block->hdr.biपंचांगap[6] |= (u8)(mask >> 6 * 8);
	block->hdr.biपंचांगap[7] |= (u8)(mask >> 7 * 8);
पूर्ण

/*
 * Clear a number of contiguous bits in the directory block biपंचांगap.
 */
अटल व्योम afs_clear_contig_bits(जोड़ afs_xdr_dir_block *block,
				  पूर्णांक bit, अचिन्हित पूर्णांक nr_slots)
अणु
	u64 mask;

	mask = (1 << nr_slots) - 1;
	mask <<= bit;

	block->hdr.biपंचांगap[0] &= ~(u8)(mask >> 0 * 8);
	block->hdr.biपंचांगap[1] &= ~(u8)(mask >> 1 * 8);
	block->hdr.biपंचांगap[2] &= ~(u8)(mask >> 2 * 8);
	block->hdr.biपंचांगap[3] &= ~(u8)(mask >> 3 * 8);
	block->hdr.biपंचांगap[4] &= ~(u8)(mask >> 4 * 8);
	block->hdr.biपंचांगap[5] &= ~(u8)(mask >> 5 * 8);
	block->hdr.biपंचांगap[6] &= ~(u8)(mask >> 6 * 8);
	block->hdr.biपंचांगap[7] &= ~(u8)(mask >> 7 * 8);
पूर्ण

/*
 * Scan a directory block looking क्रम a dirent of the right name.
 */
अटल पूर्णांक afs_dir_scan_block(जोड़ afs_xdr_dir_block *block, काष्ठा qstr *name,
			      अचिन्हित पूर्णांक blocknum)
अणु
	जोड़ afs_xdr_dirent *de;
	u64 biपंचांगap;
	पूर्णांक d, len, n;

	_enter("");

	biपंचांगap  = (u64)block->hdr.biपंचांगap[0] << 0 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[1] << 1 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[2] << 2 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[3] << 3 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[4] << 4 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[5] << 5 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[6] << 6 * 8;
	biपंचांगap |= (u64)block->hdr.biपंचांगap[7] << 7 * 8;

	क्रम (d = (blocknum == 0 ? AFS_सूची_RESV_BLOCKS0 : AFS_सूची_RESV_BLOCKS);
	     d < AFS_सूची_SLOTS_PER_BLOCK;
	     d++) अणु
		अगर (!((biपंचांगap >> d) & 1))
			जारी;
		de = &block->dirents[d];
		अगर (de->u.valid != 1)
			जारी;

		/* The block was NUL-terminated by afs_dir_check_page(). */
		len = म_माप(de->u.name);
		अगर (len == name->len &&
		    स_भेद(de->u.name, name->name, name->len) == 0)
			वापस d;

		n = round_up(12 + len + 1 + 4, AFS_सूची_सूचीENT_SIZE);
		n /= AFS_सूची_सूचीENT_SIZE;
		d += n - 1;
	पूर्ण

	वापस -1;
पूर्ण

/*
 * Initialise a new directory block.  Note that block 0 is special and contains
 * some extra metadata.
 */
अटल व्योम afs_edit_init_block(जोड़ afs_xdr_dir_block *meta,
				जोड़ afs_xdr_dir_block *block, पूर्णांक block_num)
अणु
	स_रखो(block, 0, माप(*block));
	block->hdr.npages = htons(1);
	block->hdr.magic = AFS_सूची_MAGIC;
	block->hdr.biपंचांगap[0] = 1;

	अगर (block_num == 0) अणु
		block->hdr.biपंचांगap[0] = 0xff;
		block->hdr.biपंचांगap[1] = 0x1f;
		स_रखो(block->meta.alloc_ctrs,
		       AFS_सूची_SLOTS_PER_BLOCK,
		       माप(block->meta.alloc_ctrs));
		meta->meta.alloc_ctrs[0] =
			AFS_सूची_SLOTS_PER_BLOCK - AFS_सूची_RESV_BLOCKS0;
	पूर्ण

	अगर (block_num < AFS_सूची_BLOCKS_WITH_CTR)
		meta->meta.alloc_ctrs[block_num] =
			AFS_सूची_SLOTS_PER_BLOCK - AFS_सूची_RESV_BLOCKS;
पूर्ण

/*
 * Edit a directory's file data to add a new directory entry.  Doing this after
 * create, सूची_गढ़ो, symlink, link or नाम अगर the data version number is
 * incremented by exactly one aव्योमs the need to re-करोwnload the entire
 * directory contents.
 *
 * The caller must hold the inode locked.
 */
व्योम afs_edit_dir_add(काष्ठा afs_vnode *vnode,
		      काष्ठा qstr *name, काष्ठा afs_fid *new_fid,
		      क्रमागत afs_edit_dir_reason why)
अणु
	जोड़ afs_xdr_dir_block *meta, *block;
	काष्ठा afs_xdr_dir_page *meta_page, *dir_page;
	जोड़ afs_xdr_dirent *de;
	काष्ठा page *page0, *page;
	अचिन्हित पूर्णांक need_slots, nr_blocks, b;
	pgoff_t index;
	loff_t i_size;
	gfp_t gfp;
	पूर्णांक slot;

	_enter(",,{%d,%s},", name->len, name->name);

	i_size = i_size_पढ़ो(&vnode->vfs_inode);
	अगर (i_size > AFS_सूची_BLOCK_SIZE * AFS_सूची_MAX_BLOCKS ||
	    (i_size & (AFS_सूची_BLOCK_SIZE - 1))) अणु
		clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
		वापस;
	पूर्ण

	gfp = vnode->vfs_inode.i_mapping->gfp_mask;
	page0 = find_or_create_page(vnode->vfs_inode.i_mapping, 0, gfp);
	अगर (!page0) अणु
		clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
		_leave(" [fgp]");
		वापस;
	पूर्ण

	/* Work out how many slots we're going to need. */
	need_slots = afs_dir_calc_slots(name->len);

	meta_page = kmap(page0);
	meta = &meta_page->blocks[0];
	अगर (i_size == 0)
		जाओ new_directory;
	nr_blocks = i_size / AFS_सूची_BLOCK_SIZE;

	/* Find a block that has sufficient slots available.  Each VM page
	 * contains two or more directory blocks.
	 */
	क्रम (b = 0; b < nr_blocks + 1; b++) अणु
		/* If the directory extended पूर्णांकo a new page, then we need to
		 * tack a new page on the end.
		 */
		index = b / AFS_सूची_BLOCKS_PER_PAGE;
		अगर (index == 0) अणु
			page = page0;
			dir_page = meta_page;
		पूर्ण अन्यथा अणु
			अगर (nr_blocks >= AFS_सूची_MAX_BLOCKS)
				जाओ error;
			gfp = vnode->vfs_inode.i_mapping->gfp_mask;
			page = find_or_create_page(vnode->vfs_inode.i_mapping,
						   index, gfp);
			अगर (!page)
				जाओ error;
			अगर (!PagePrivate(page))
				attach_page_निजी(page, (व्योम *)1);
			dir_page = kmap(page);
		पूर्ण

		/* Abanकरोn the edit अगर we got a callback अवरोध. */
		अगर (!test_bit(AFS_VNODE_सूची_VALID, &vnode->flags))
			जाओ invalidated;

		block = &dir_page->blocks[b % AFS_सूची_BLOCKS_PER_PAGE];

		_debug("block %u: %2u %3u %u",
		       b,
		       (b < AFS_सूची_BLOCKS_WITH_CTR) ? meta->meta.alloc_ctrs[b] : 99,
		       ntohs(block->hdr.npages),
		       ntohs(block->hdr.magic));

		/* Initialise the block अगर necessary. */
		अगर (b == nr_blocks) अणु
			_debug("init %u", b);
			afs_edit_init_block(meta, block, b);
			i_size_ग_लिखो(&vnode->vfs_inode, (b + 1) * AFS_सूची_BLOCK_SIZE);
		पूर्ण

		/* Only lower dir pages have a counter in the header. */
		अगर (b >= AFS_सूची_BLOCKS_WITH_CTR ||
		    meta->meta.alloc_ctrs[b] >= need_slots) अणु
			/* We need to try and find one or more consecutive
			 * slots to hold the entry.
			 */
			slot = afs_find_contig_bits(block, need_slots);
			अगर (slot >= 0) अणु
				_debug("slot %u", slot);
				जाओ found_space;
			पूर्ण
		पूर्ण

		अगर (page != page0) अणु
			unlock_page(page);
			kunmap(page);
			put_page(page);
		पूर्ण
	पूर्ण

	/* There are no spare slots of sufficient size, yet the operation
	 * succeeded.  Download the directory again.
	 */
	trace_afs_edit_dir(vnode, why, afs_edit_dir_create_nospc, 0, 0, 0, 0, name->name);
	clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
	जाओ out_unmap;

new_directory:
	afs_edit_init_block(meta, meta, 0);
	i_size = AFS_सूची_BLOCK_SIZE;
	i_size_ग_लिखो(&vnode->vfs_inode, i_size);
	slot = AFS_सूची_RESV_BLOCKS0;
	page = page0;
	block = meta;
	nr_blocks = 1;
	b = 0;

found_space:
	/* Set the dirent slot. */
	trace_afs_edit_dir(vnode, why, afs_edit_dir_create, b, slot,
			   new_fid->vnode, new_fid->unique, name->name);
	de = &block->dirents[slot];
	de->u.valid	= 1;
	de->u.unused[0]	= 0;
	de->u.hash_next	= 0; // TODO: Really need to मुख्यtain this
	de->u.vnode	= htonl(new_fid->vnode);
	de->u.unique	= htonl(new_fid->unique);
	स_नकल(de->u.name, name->name, name->len + 1);
	de->u.name[name->len] = 0;

	/* Adjust the biपंचांगap. */
	afs_set_contig_bits(block, slot, need_slots);
	अगर (page != page0) अणु
		unlock_page(page);
		kunmap(page);
		put_page(page);
	पूर्ण

	/* Adjust the allocation counter. */
	अगर (b < AFS_सूची_BLOCKS_WITH_CTR)
		meta->meta.alloc_ctrs[b] -= need_slots;

	inode_inc_iversion_raw(&vnode->vfs_inode);
	afs_stat_v(vnode, n_dir_cr);
	_debug("Insert %s in %u[%u]", name->name, b, slot);

out_unmap:
	unlock_page(page0);
	kunmap(page0);
	put_page(page0);
	_leave("");
	वापस;

invalidated:
	trace_afs_edit_dir(vnode, why, afs_edit_dir_create_inval, 0, 0, 0, 0, name->name);
	clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
	अगर (page != page0) अणु
		kunmap(page);
		put_page(page);
	पूर्ण
	जाओ out_unmap;

error:
	trace_afs_edit_dir(vnode, why, afs_edit_dir_create_error, 0, 0, 0, 0, name->name);
	clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
	जाओ out_unmap;
पूर्ण

/*
 * Edit a directory's file data to हटाओ a new directory entry.  Doing this
 * after unlink, सूची_हटाओ or नाम अगर the data version number is incremented by
 * exactly one aव्योमs the need to re-करोwnload the entire directory contents.
 *
 * The caller must hold the inode locked.
 */
व्योम afs_edit_dir_हटाओ(काष्ठा afs_vnode *vnode,
			 काष्ठा qstr *name, क्रमागत afs_edit_dir_reason why)
अणु
	काष्ठा afs_xdr_dir_page *meta_page, *dir_page;
	जोड़ afs_xdr_dir_block *meta, *block;
	जोड़ afs_xdr_dirent *de;
	काष्ठा page *page0, *page;
	अचिन्हित पूर्णांक need_slots, nr_blocks, b;
	pgoff_t index;
	loff_t i_size;
	पूर्णांक slot;

	_enter(",,{%d,%s},", name->len, name->name);

	i_size = i_size_पढ़ो(&vnode->vfs_inode);
	अगर (i_size < AFS_सूची_BLOCK_SIZE ||
	    i_size > AFS_सूची_BLOCK_SIZE * AFS_सूची_MAX_BLOCKS ||
	    (i_size & (AFS_सूची_BLOCK_SIZE - 1))) अणु
		clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
		वापस;
	पूर्ण
	nr_blocks = i_size / AFS_सूची_BLOCK_SIZE;

	page0 = find_lock_page(vnode->vfs_inode.i_mapping, 0);
	अगर (!page0) अणु
		clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
		_leave(" [fgp]");
		वापस;
	पूर्ण

	/* Work out how many slots we're going to discard. */
	need_slots = afs_dir_calc_slots(name->len);

	meta_page = kmap(page0);
	meta = &meta_page->blocks[0];

	/* Find a page that has sufficient slots available.  Each VM page
	 * contains two or more directory blocks.
	 */
	क्रम (b = 0; b < nr_blocks; b++) अणु
		index = b / AFS_सूची_BLOCKS_PER_PAGE;
		अगर (index != 0) अणु
			page = find_lock_page(vnode->vfs_inode.i_mapping, index);
			अगर (!page)
				जाओ error;
			dir_page = kmap(page);
		पूर्ण अन्यथा अणु
			page = page0;
			dir_page = meta_page;
		पूर्ण

		/* Abanकरोn the edit अगर we got a callback अवरोध. */
		अगर (!test_bit(AFS_VNODE_सूची_VALID, &vnode->flags))
			जाओ invalidated;

		block = &dir_page->blocks[b % AFS_सूची_BLOCKS_PER_PAGE];

		अगर (b > AFS_सूची_BLOCKS_WITH_CTR ||
		    meta->meta.alloc_ctrs[b] <= AFS_सूची_SLOTS_PER_BLOCK - 1 - need_slots) अणु
			slot = afs_dir_scan_block(block, name, b);
			अगर (slot >= 0)
				जाओ found_dirent;
		पूर्ण

		अगर (page != page0) अणु
			unlock_page(page);
			kunmap(page);
			put_page(page);
		पूर्ण
	पूर्ण

	/* Didn't find the dirent to clobber.  Download the directory again. */
	trace_afs_edit_dir(vnode, why, afs_edit_dir_delete_noent,
			   0, 0, 0, 0, name->name);
	clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
	जाओ out_unmap;

found_dirent:
	de = &block->dirents[slot];

	trace_afs_edit_dir(vnode, why, afs_edit_dir_delete, b, slot,
			   ntohl(de->u.vnode), ntohl(de->u.unique),
			   name->name);

	स_रखो(de, 0, माप(*de) * need_slots);

	/* Adjust the biपंचांगap. */
	afs_clear_contig_bits(block, slot, need_slots);
	अगर (page != page0) अणु
		unlock_page(page);
		kunmap(page);
		put_page(page);
	पूर्ण

	/* Adjust the allocation counter. */
	अगर (b < AFS_सूची_BLOCKS_WITH_CTR)
		meta->meta.alloc_ctrs[b] += need_slots;

	inode_set_iversion_raw(&vnode->vfs_inode, vnode->status.data_version);
	afs_stat_v(vnode, n_dir_rm);
	_debug("Remove %s from %u[%u]", name->name, b, slot);

out_unmap:
	unlock_page(page0);
	kunmap(page0);
	put_page(page0);
	_leave("");
	वापस;

invalidated:
	trace_afs_edit_dir(vnode, why, afs_edit_dir_delete_inval,
			   0, 0, 0, 0, name->name);
	clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
	अगर (page != page0) अणु
		unlock_page(page);
		kunmap(page);
		put_page(page);
	पूर्ण
	जाओ out_unmap;

error:
	trace_afs_edit_dir(vnode, why, afs_edit_dir_delete_error,
			   0, 0, 0, 0, name->name);
	clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
	जाओ out_unmap;
पूर्ण
