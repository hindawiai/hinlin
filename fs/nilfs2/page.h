<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * page.h - buffer/page management specअगरic to NILFS
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi and Seiji Kihara.
 */

#अगर_अघोषित _NILFS_PAGE_H
#घोषणा _NILFS_PAGE_H

#समावेश <linux/buffer_head.h>
#समावेश "nilfs.h"

/*
 * Extended buffer state bits
 */
क्रमागत अणु
	BH_NILFS_Allocated = BH_PrivateStart,
	BH_NILFS_Node,
	BH_NILFS_Volatile,
	BH_NILFS_Checked,
	BH_NILFS_Redirected,
पूर्ण;

BUFFER_FNS(NILFS_Node, nilfs_node)		/* nilfs node buffers */
BUFFER_FNS(NILFS_Volatile, nilfs_अस्थिर)
BUFFER_FNS(NILFS_Checked, nilfs_checked)	/* buffer is verअगरied */
BUFFER_FNS(NILFS_Redirected, nilfs_redirected)	/* redirected to a copy */


पूर्णांक __nilfs_clear_page_dirty(काष्ठा page *);

काष्ठा buffer_head *nilfs_grab_buffer(काष्ठा inode *, काष्ठा address_space *,
				      अचिन्हित दीर्घ, अचिन्हित दीर्घ);
व्योम nilfs_क्रमget_buffer(काष्ठा buffer_head *);
व्योम nilfs_copy_buffer(काष्ठा buffer_head *, काष्ठा buffer_head *);
पूर्णांक nilfs_page_buffers_clean(काष्ठा page *);
व्योम nilfs_page_bug(काष्ठा page *);

पूर्णांक nilfs_copy_dirty_pages(काष्ठा address_space *, काष्ठा address_space *);
व्योम nilfs_copy_back_pages(काष्ठा address_space *, काष्ठा address_space *);
व्योम nilfs_clear_dirty_page(काष्ठा page *, bool);
व्योम nilfs_clear_dirty_pages(काष्ठा address_space *, bool);
व्योम nilfs_mapping_init(काष्ठा address_space *mapping, काष्ठा inode *inode);
अचिन्हित पूर्णांक nilfs_page_count_clean_buffers(काष्ठा page *, अचिन्हित पूर्णांक,
					    अचिन्हित पूर्णांक);
अचिन्हित दीर्घ nilfs_find_uncommitted_extent(काष्ठा inode *inode,
					    sector_t start_blk,
					    sector_t *blkoff);

#घोषणा NILFS_PAGE_BUG(page, m, a...) \
	करो अणु nilfs_page_bug(page); BUG(); पूर्ण जबतक (0)

अटल अंतरभूत काष्ठा buffer_head *
nilfs_page_get_nth_block(काष्ठा page *page, अचिन्हित पूर्णांक count)
अणु
	काष्ठा buffer_head *bh = page_buffers(page);

	जबतक (count-- > 0)
		bh = bh->b_this_page;
	get_bh(bh);
	वापस bh;
पूर्ण

#पूर्ण_अगर /* _NILFS_PAGE_H */
