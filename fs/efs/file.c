<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * file.c
 *
 * Copyright (c) 1999 Al Smith
 *
 * Portions derived from work (c) 1995,1996 Christian Vogelgsang.
 */

#समावेश <linux/buffer_head.h>
#समावेश "efs.h"

पूर्णांक efs_get_block(काष्ठा inode *inode, sector_t iblock,
		  काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक error = -EROFS;
	दीर्घ phys;

	अगर (create)
		वापस error;
	अगर (iblock >= inode->i_blocks) अणु
#अगर_घोषित DEBUG
		/*
		 * i have no idea why this happens as often as it करोes
		 */
		pr_warn("%s(): block %d >= %ld (filesize %ld)\n",
			__func__, block, inode->i_blocks, inode->i_size);
#पूर्ण_अगर
		वापस 0;
	पूर्ण
	phys = efs_map_block(inode, iblock);
	अगर (phys)
		map_bh(bh_result, inode->i_sb, phys);
	वापस 0;
पूर्ण

पूर्णांक efs_bmap(काष्ठा inode *inode, efs_block_t block) अणु

	अगर (block < 0) अणु
		pr_warn("%s(): block < 0\n", __func__);
		वापस 0;
	पूर्ण

	/* are we about to पढ़ो past the end of a file ? */
	अगर (!(block < inode->i_blocks)) अणु
#अगर_घोषित DEBUG
		/*
		 * i have no idea why this happens as often as it करोes
		 */
		pr_warn("%s(): block %d >= %ld (filesize %ld)\n",
			__func__, block, inode->i_blocks, inode->i_size);
#पूर्ण_अगर
		वापस 0;
	पूर्ण

	वापस efs_map_block(inode, block);
पूर्ण
