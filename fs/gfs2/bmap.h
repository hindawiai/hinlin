<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __BMAP_DOT_H__
#घोषणा __BMAP_DOT_H__

#समावेश <linux/iomap.h>

#समावेश "inode.h"

काष्ठा inode;
काष्ठा gfs2_inode;
काष्ठा page;


/**
 * gfs2_ग_लिखो_calc_reserv - calculate number of blocks needed to ग_लिखो to a file
 * @ip: the file
 * @len: the number of bytes to be written to the file
 * @data_blocks: वापसs the number of data blocks required
 * @ind_blocks: वापसs the number of indirect blocks required
 *
 */

अटल अंतरभूत व्योम gfs2_ग_लिखो_calc_reserv(स्थिर काष्ठा gfs2_inode *ip,
					  अचिन्हित पूर्णांक len,
					  अचिन्हित पूर्णांक *data_blocks,
					  अचिन्हित पूर्णांक *ind_blocks)
अणु
	स्थिर काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	अचिन्हित पूर्णांक पंचांगp;

	BUG_ON(gfs2_is_dir(ip));
	*data_blocks = (len >> sdp->sd_sb.sb_bsize_shअगरt) + 3;
	*ind_blocks = 3 * (sdp->sd_max_height - 1);

	क्रम (पंचांगp = *data_blocks; पंचांगp > sdp->sd_diptrs;) अणु
		पंचांगp = DIV_ROUND_UP(पंचांगp, sdp->sd_inptrs);
		*ind_blocks += पंचांगp;
	पूर्ण
पूर्ण

बाह्य स्थिर काष्ठा iomap_ops gfs2_iomap_ops;
बाह्य स्थिर काष्ठा iomap_ग_लिखोback_ops gfs2_ग_लिखोback_ops;

बाह्य पूर्णांक gfs2_unstuff_dinode(काष्ठा gfs2_inode *ip, काष्ठा page *page);
बाह्य पूर्णांक gfs2_block_map(काष्ठा inode *inode, sector_t lblock,
			  काष्ठा buffer_head *bh, पूर्णांक create);
बाह्य पूर्णांक gfs2_iomap_get(काष्ठा inode *inode, loff_t pos, loff_t length,
			  काष्ठा iomap *iomap);
बाह्य पूर्णांक gfs2_iomap_alloc(काष्ठा inode *inode, loff_t pos, loff_t length,
			    काष्ठा iomap *iomap);
बाह्य पूर्णांक gfs2_get_extent(काष्ठा inode *inode, u64 lblock, u64 *dblock,
			   अचिन्हित पूर्णांक *extlen);
बाह्य पूर्णांक gfs2_alloc_extent(काष्ठा inode *inode, u64 lblock, u64 *dblock,
			     अचिन्हित *extlen, bool *new);
बाह्य पूर्णांक gfs2_setattr_size(काष्ठा inode *inode, u64 size);
बाह्य व्योम gfs2_trim_blocks(काष्ठा inode *inode);
बाह्य पूर्णांक gfs2_truncatei_resume(काष्ठा gfs2_inode *ip);
बाह्य पूर्णांक gfs2_file_dealloc(काष्ठा gfs2_inode *ip);
बाह्य पूर्णांक gfs2_ग_लिखो_alloc_required(काष्ठा gfs2_inode *ip, u64 offset,
				     अचिन्हित पूर्णांक len);
बाह्य पूर्णांक gfs2_map_journal_extents(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_jdesc *jd);
बाह्य व्योम gfs2_मुक्त_journal_extents(काष्ठा gfs2_jdesc *jd);
बाह्य पूर्णांक __gfs2_punch_hole(काष्ठा file *file, loff_t offset, loff_t length);

#पूर्ण_अगर /* __BMAP_DOT_H__ */
