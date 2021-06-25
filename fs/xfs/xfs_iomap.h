<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_IOMAP_H__
#घोषणा __XFS_IOMAP_H__

#समावेश <linux/iomap.h>

काष्ठा xfs_inode;
काष्ठा xfs_bmbt_irec;

पूर्णांक xfs_iomap_ग_लिखो_direct(काष्ठा xfs_inode *ip, xfs_fileoff_t offset_fsb,
		xfs_fileoff_t count_fsb, काष्ठा xfs_bmbt_irec *imap);
पूर्णांक xfs_iomap_ग_लिखो_unwritten(काष्ठा xfs_inode *, xfs_off_t, xfs_off_t, bool);
xfs_fileoff_t xfs_iomap_eof_align_last_fsb(काष्ठा xfs_inode *ip,
		xfs_fileoff_t end_fsb);

पूर्णांक xfs_bmbt_to_iomap(काष्ठा xfs_inode *, काष्ठा iomap *,
		काष्ठा xfs_bmbt_irec *, u16);

अटल अंतरभूत xfs_filblks_t
xfs_aligned_fsb_count(
	xfs_fileoff_t		offset_fsb,
	xfs_filblks_t		count_fsb,
	xfs_extlen_t		extsz)
अणु
	अगर (extsz) अणु
		xfs_extlen_t	align;

		भाग_u64_rem(offset_fsb, extsz, &align);
		अगर (align)
			count_fsb += align;
		भाग_u64_rem(count_fsb, extsz, &align);
		अगर (align)
			count_fsb += extsz - align;
	पूर्ण

	वापस count_fsb;
पूर्ण

बाह्य स्थिर काष्ठा iomap_ops xfs_buffered_ग_लिखो_iomap_ops;
बाह्य स्थिर काष्ठा iomap_ops xfs_direct_ग_लिखो_iomap_ops;
बाह्य स्थिर काष्ठा iomap_ops xfs_पढ़ो_iomap_ops;
बाह्य स्थिर काष्ठा iomap_ops xfs_seek_iomap_ops;
बाह्य स्थिर काष्ठा iomap_ops xfs_xattr_iomap_ops;

#पूर्ण_अगर /* __XFS_IOMAP_H__*/
