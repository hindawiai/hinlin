<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_BMAP_UTIL_H__
#घोषणा	__XFS_BMAP_UTIL_H__

/* Kernel only BMAP related definitions and functions */

काष्ठा xfs_bmbt_irec;
काष्ठा xfs_extent_मुक्त_item;
काष्ठा xfs_अगरork;
काष्ठा xfs_inode;
काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_bदो_स्मृतिa;

#अगर_घोषित CONFIG_XFS_RT
पूर्णांक	xfs_bmap_rtalloc(काष्ठा xfs_bदो_स्मृतिa *ap);
#अन्यथा /* !CONFIG_XFS_RT */
/*
 * Attempts to allocate RT extents when RT is disable indicates corruption and
 * should trigger a shutकरोwn.
 */
अटल अंतरभूत पूर्णांक
xfs_bmap_rtalloc(काष्ठा xfs_bदो_स्मृतिa *ap)
अणु
	वापस -EFSCORRUPTED;
पूर्ण
#पूर्ण_अगर /* CONFIG_XFS_RT */

पूर्णांक	xfs_bmap_punch_delalloc_range(काष्ठा xfs_inode *ip,
		xfs_fileoff_t start_fsb, xfs_fileoff_t length);

काष्ठा kgetbmap अणु
	__s64		bmv_offset;	/* file offset of segment in blocks */
	__s64		bmv_block;	/* starting block (64-bit daddr_t)  */
	__s64		bmv_length;	/* length of segment, blocks	    */
	__s32		bmv_oflags;	/* output flags */
पूर्ण;
पूर्णांक	xfs_getbmap(काष्ठा xfs_inode *ip, काष्ठा getbmapx *bmv,
		काष्ठा kgetbmap *out);

/* functions in xfs_bmap.c that are only needed by xfs_bmap_util.c */
पूर्णांक	xfs_bmap_extsize_align(काष्ठा xfs_mount *mp, काष्ठा xfs_bmbt_irec *gotp,
			       काष्ठा xfs_bmbt_irec *prevp, xfs_extlen_t extsz,
			       पूर्णांक rt, पूर्णांक eof, पूर्णांक delay, पूर्णांक convert,
			       xfs_fileoff_t *offp, xfs_extlen_t *lenp);
व्योम	xfs_bmap_adjacent(काष्ठा xfs_bदो_स्मृतिa *ap);
पूर्णांक	xfs_bmap_last_extent(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
			     पूर्णांक whichविभाजन, काष्ठा xfs_bmbt_irec *rec,
			     पूर्णांक *is_empty);

/* pपुनः_स्मृतिation and hole punch पूर्णांकerface */
पूर्णांक	xfs_alloc_file_space(काष्ठा xfs_inode *ip, xfs_off_t offset,
			     xfs_off_t len, पूर्णांक alloc_type);
पूर्णांक	xfs_मुक्त_file_space(काष्ठा xfs_inode *ip, xfs_off_t offset,
			    xfs_off_t len);
पूर्णांक	xfs_collapse_file_space(काष्ठा xfs_inode *, xfs_off_t offset,
				xfs_off_t len);
पूर्णांक	xfs_insert_file_space(काष्ठा xfs_inode *, xfs_off_t offset,
				xfs_off_t len);

/* खातापूर्ण block manipulation functions */
bool	xfs_can_मुक्त_eofblocks(काष्ठा xfs_inode *ip, bool क्रमce);
पूर्णांक	xfs_मुक्त_eofblocks(काष्ठा xfs_inode *ip);

पूर्णांक	xfs_swap_extents(काष्ठा xfs_inode *ip, काष्ठा xfs_inode *tip,
			 काष्ठा xfs_swapext *sx);

xfs_daddr_t xfs_fsb_to_db(काष्ठा xfs_inode *ip, xfs_fsblock_t fsb);

xfs_extnum_t xfs_bmap_count_leaves(काष्ठा xfs_अगरork *अगरp, xfs_filblks_t *count);
पूर्णांक xfs_bmap_count_blocks(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
			  पूर्णांक whichविभाजन, xfs_extnum_t *nextents,
			  xfs_filblks_t *count);

पूर्णांक	xfs_flush_unmap_range(काष्ठा xfs_inode *ip, xfs_off_t offset,
			      xfs_off_t len);

#पूर्ण_अगर	/* __XFS_BMAP_UTIL_H__ */
