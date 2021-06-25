<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	fs/bfs/file.c
 *	BFS file operations.
 *	Copyright (C) 1999-2018 Tigran Aivazian <aivazian.tigran@gmail.com>
 *
 *	Make the file block allocation algorithm understand the size
 *	of the underlying block device.
 *	Copyright (C) 2007 Dmitri Vorobiev <dmitri.vorobiev@gmail.com>
 *
 */

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश "bfs.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा dम_लिखो(x...)	म_लिखो(x)
#अन्यथा
#घोषणा dम_लिखो(x...)
#पूर्ण_अगर

स्थिर काष्ठा file_operations bfs_file_operations = अणु
	.llseek 	= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
पूर्ण;

अटल पूर्णांक bfs_move_block(अचिन्हित दीर्घ from, अचिन्हित दीर्घ to,
					काष्ठा super_block *sb)
अणु
	काष्ठा buffer_head *bh, *new;

	bh = sb_bपढ़ो(sb, from);
	अगर (!bh)
		वापस -EIO;
	new = sb_getblk(sb, to);
	स_नकल(new->b_data, bh->b_data, bh->b_size);
	mark_buffer_dirty(new);
	bक्रमget(bh);
	brअन्यथा(new);
	वापस 0;
पूर्ण

अटल पूर्णांक bfs_move_blocks(काष्ठा super_block *sb, अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ end, अचिन्हित दीर्घ where)
अणु
	अचिन्हित दीर्घ i;

	dम_लिखो("%08lx-%08lx->%08lx\n", start, end, where);
	क्रम (i = start; i <= end; i++)
		अगर(bfs_move_block(i, where + i, sb)) अणु
			dम_लिखो("failed to move block %08lx -> %08lx\n", i,
								where + i);
			वापस -EIO;
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bfs_get_block(काष्ठा inode *inode, sector_t block,
			काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	अचिन्हित दीर्घ phys;
	पूर्णांक err;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा bfs_sb_info *info = BFS_SB(sb);
	काष्ठा bfs_inode_info *bi = BFS_I(inode);

	phys = bi->i_sblock + block;
	अगर (!create) अणु
		अगर (phys <= bi->i_eblock) अणु
			dम_लिखो("c=%d, b=%08lx, phys=%09lx (granted)\n",
                                create, (अचिन्हित दीर्घ)block, phys);
			map_bh(bh_result, sb, phys);
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * If the file is not empty and the requested block is within the
	 * range of blocks allocated क्रम this file, we can grant it.
	 */
	अगर (bi->i_sblock && (phys <= bi->i_eblock)) अणु
		dम_लिखो("c=%d, b=%08lx, phys=%08lx (interim block granted)\n", 
				create, (अचिन्हित दीर्घ)block, phys);
		map_bh(bh_result, sb, phys);
		वापस 0;
	पूर्ण

	/* The file will be extended, so let's see अगर there is enough space. */
	अगर (phys >= info->si_blocks)
		वापस -ENOSPC;

	/* The rest has to be रक्षित against itself. */
	mutex_lock(&info->bfs_lock);

	/*
	 * If the last data block क्रम this file is the last allocated
	 * block, we can extend the file trivially, without moving it
	 * anywhere.
	 */
	अगर (bi->i_eblock == info->si_lf_eblk) अणु
		dम_लिखो("c=%d, b=%08lx, phys=%08lx (simple extension)\n", 
				create, (अचिन्हित दीर्घ)block, phys);
		map_bh(bh_result, sb, phys);
		info->si_मुक्तb -= phys - bi->i_eblock;
		info->si_lf_eblk = bi->i_eblock = phys;
		mark_inode_dirty(inode);
		err = 0;
		जाओ out;
	पूर्ण

	/* Ok, we have to move this entire file to the next मुक्त block. */
	phys = info->si_lf_eblk + 1;
	अगर (phys + block >= info->si_blocks) अणु
		err = -ENOSPC;
		जाओ out;
	पूर्ण

	अगर (bi->i_sblock) अणु
		err = bfs_move_blocks(inode->i_sb, bi->i_sblock, 
						bi->i_eblock, phys);
		अगर (err) अणु
			dम_लिखो("failed to move ino=%08lx -> fs corruption\n",
								inode->i_ino);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		err = 0;

	dम_लिखो("c=%d, b=%08lx, phys=%08lx (moved)\n",
                create, (अचिन्हित दीर्घ)block, phys);
	bi->i_sblock = phys;
	phys += block;
	info->si_lf_eblk = bi->i_eblock = phys;

	/*
	 * This assumes nothing can ग_लिखो the inode back जबतक we are here
	 * and thus update inode->i_blocks! (XXX)
	 */
	info->si_मुक्तb -= bi->i_eblock - bi->i_sblock + 1 - inode->i_blocks;
	mark_inode_dirty(inode);
	map_bh(bh_result, sb, phys);
out:
	mutex_unlock(&info->bfs_lock);
	वापस err;
पूर्ण

अटल पूर्णांक bfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, bfs_get_block, wbc);
पूर्ण

अटल पूर्णांक bfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page, bfs_get_block);
पूर्ण

अटल व्योम bfs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size)
		truncate_pagecache(inode, inode->i_size);
पूर्ण

अटल पूर्णांक bfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	ret = block_ग_लिखो_begin(mapping, pos, len, flags, pagep,
				bfs_get_block);
	अगर (unlikely(ret))
		bfs_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल sector_t bfs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, bfs_get_block);
पूर्ण

स्थिर काष्ठा address_space_operations bfs_aops = अणु
	.पढ़ोpage	= bfs_पढ़ोpage,
	.ग_लिखोpage	= bfs_ग_लिखोpage,
	.ग_लिखो_begin	= bfs_ग_लिखो_begin,
	.ग_लिखो_end	= generic_ग_लिखो_end,
	.bmap		= bfs_bmap,
पूर्ण;

स्थिर काष्ठा inode_operations bfs_file_inops;
