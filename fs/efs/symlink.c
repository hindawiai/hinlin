<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * symlink.c
 *
 * Copyright (c) 1999 Al Smith
 *
 * Portions derived from work (c) 1995,1996 Christian Vogelgsang.
 */

#समावेश <linux/माला.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/buffer_head.h>
#समावेश "efs.h"

अटल पूर्णांक efs_symlink_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	अक्षर *link = page_address(page);
	काष्ठा buffer_head * bh;
	काष्ठा inode * inode = page->mapping->host;
	efs_block_t size = inode->i_size;
	पूर्णांक err;
  
	err = -ENAMETOOLONG;
	अगर (size > 2 * EFS_BLOCKSIZE)
		जाओ fail;
  
	/* पढ़ो first 512 bytes of link target */
	err = -EIO;
	bh = sb_bपढ़ो(inode->i_sb, efs_bmap(inode, 0));
	अगर (!bh)
		जाओ fail;
	स_नकल(link, bh->b_data, (size > EFS_BLOCKSIZE) ? EFS_BLOCKSIZE : size);
	brअन्यथा(bh);
	अगर (size > EFS_BLOCKSIZE) अणु
		bh = sb_bपढ़ो(inode->i_sb, efs_bmap(inode, 1));
		अगर (!bh)
			जाओ fail;
		स_नकल(link + EFS_BLOCKSIZE, bh->b_data, size - EFS_BLOCKSIZE);
		brअन्यथा(bh);
	पूर्ण
	link[size] = '\0';
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;
fail:
	SetPageError(page);
	unlock_page(page);
	वापस err;
पूर्ण

स्थिर काष्ठा address_space_operations efs_symlink_aops = अणु
	.पढ़ोpage	= efs_symlink_पढ़ोpage
पूर्ण;
