<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_INODE_BUF_H__
#घोषणा	__XFS_INODE_BUF_H__

काष्ठा xfs_inode;
काष्ठा xfs_dinode;

/*
 * Inode location inक्रमmation.  Stored in the inode and passed to
 * xfs_imap_to_bp() to get a buffer and dinode क्रम a given inode.
 */
काष्ठा xfs_imap अणु
	xfs_daddr_t	im_blkno;	/* starting BB of inode chunk */
	अचिन्हित लघु	im_len;		/* length in BBs of inode chunk */
	अचिन्हित लघु	im_boffset;	/* inode offset in block in bytes */
पूर्ण;

पूर्णांक	xfs_imap_to_bp(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		       काष्ठा xfs_imap *imap, काष्ठा xfs_buf **bpp);
व्योम	xfs_dinode_calc_crc(काष्ठा xfs_mount *, काष्ठा xfs_dinode *);
व्योम	xfs_inode_to_disk(काष्ठा xfs_inode *ip, काष्ठा xfs_dinode *to,
			  xfs_lsn_t lsn);
पूर्णांक	xfs_inode_from_disk(काष्ठा xfs_inode *ip, काष्ठा xfs_dinode *from);

xfs_failaddr_t xfs_dinode_verअगरy(काष्ठा xfs_mount *mp, xfs_ino_t ino,
			   काष्ठा xfs_dinode *dip);
xfs_failaddr_t xfs_inode_validate_extsize(काष्ठा xfs_mount *mp,
		uपूर्णांक32_t extsize, uपूर्णांक16_t mode, uपूर्णांक16_t flags);
xfs_failaddr_t xfs_inode_validate_cowextsize(काष्ठा xfs_mount *mp,
		uपूर्णांक32_t cowextsize, uपूर्णांक16_t mode, uपूर्णांक16_t flags,
		uपूर्णांक64_t flags2);

अटल अंतरभूत uपूर्णांक64_t xfs_inode_encode_bigसमय(काष्ठा बारpec64 tv)
अणु
	वापस xfs_unix_to_bigसमय(tv.tv_sec) * NSEC_PER_SEC + tv.tv_nsec;
पूर्ण

काष्ठा बारpec64 xfs_inode_from_disk_ts(काष्ठा xfs_dinode *dip,
		स्थिर xfs_बारtamp_t ts);

#पूर्ण_अगर	/* __XFS_INODE_BUF_H__ */
