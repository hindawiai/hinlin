<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_REFLINK_H
#घोषणा __XFS_REFLINK_H 1

अटल अंतरभूत bool xfs_is_always_cow_inode(काष्ठा xfs_inode *ip)
अणु
	वापस ip->i_mount->m_always_cow &&
		xfs_sb_version_hasreflink(&ip->i_mount->m_sb);
पूर्ण

अटल अंतरभूत bool xfs_is_cow_inode(काष्ठा xfs_inode *ip)
अणु
	वापस xfs_is_reflink_inode(ip) || xfs_is_always_cow_inode(ip);
पूर्ण

बाह्य पूर्णांक xfs_reflink_find_shared(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		xfs_agnumber_t agno, xfs_agblock_t agbno, xfs_extlen_t aglen,
		xfs_agblock_t *fbno, xfs_extlen_t *flen, bool find_maximal);
बाह्य पूर्णांक xfs_reflink_trim_around_shared(काष्ठा xfs_inode *ip,
		काष्ठा xfs_bmbt_irec *irec, bool *shared);
पूर्णांक xfs_bmap_trim_cow(काष्ठा xfs_inode *ip, काष्ठा xfs_bmbt_irec *imap,
		bool *shared);

पूर्णांक xfs_reflink_allocate_cow(काष्ठा xfs_inode *ip, काष्ठा xfs_bmbt_irec *imap,
		काष्ठा xfs_bmbt_irec *cmap, bool *shared, uपूर्णांक *lockmode,
		bool convert_now);
बाह्य पूर्णांक xfs_reflink_convert_cow(काष्ठा xfs_inode *ip, xfs_off_t offset,
		xfs_off_t count);

बाह्य पूर्णांक xfs_reflink_cancel_cow_blocks(काष्ठा xfs_inode *ip,
		काष्ठा xfs_trans **tpp, xfs_fileoff_t offset_fsb,
		xfs_fileoff_t end_fsb, bool cancel_real);
बाह्य पूर्णांक xfs_reflink_cancel_cow_range(काष्ठा xfs_inode *ip, xfs_off_t offset,
		xfs_off_t count, bool cancel_real);
बाह्य पूर्णांक xfs_reflink_end_cow(काष्ठा xfs_inode *ip, xfs_off_t offset,
		xfs_off_t count);
बाह्य पूर्णांक xfs_reflink_recover_cow(काष्ठा xfs_mount *mp);
बाह्य loff_t xfs_reflink_remap_range(काष्ठा file *file_in, loff_t pos_in,
		काष्ठा file *file_out, loff_t pos_out, loff_t len,
		अचिन्हित पूर्णांक remap_flags);
बाह्य पूर्णांक xfs_reflink_inode_has_shared_extents(काष्ठा xfs_trans *tp,
		काष्ठा xfs_inode *ip, bool *has_shared);
बाह्य पूर्णांक xfs_reflink_clear_inode_flag(काष्ठा xfs_inode *ip,
		काष्ठा xfs_trans **tpp);
बाह्य पूर्णांक xfs_reflink_unshare(काष्ठा xfs_inode *ip, xfs_off_t offset,
		xfs_off_t len);
बाह्य पूर्णांक xfs_reflink_remap_prep(काष्ठा file *file_in, loff_t pos_in,
		काष्ठा file *file_out, loff_t pos_out, loff_t *len,
		अचिन्हित पूर्णांक remap_flags);
बाह्य पूर्णांक xfs_reflink_remap_blocks(काष्ठा xfs_inode *src, loff_t pos_in,
		काष्ठा xfs_inode *dest, loff_t pos_out, loff_t remap_len,
		loff_t *remapped);
बाह्य पूर्णांक xfs_reflink_update_dest(काष्ठा xfs_inode *dest, xfs_off_t newlen,
		xfs_extlen_t cowextsize, अचिन्हित पूर्णांक remap_flags);

#पूर्ण_अगर /* __XFS_REFLINK_H */
