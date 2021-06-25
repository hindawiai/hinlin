<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * symlink.h
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_SYMLINK_H
#घोषणा OCFS2_SYMLINK_H

बाह्य स्थिर काष्ठा inode_operations ocfs2_symlink_inode_operations;
बाह्य स्थिर काष्ठा address_space_operations ocfs2_fast_symlink_aops;

/*
 * Test whether an inode is a fast symlink.
 */
अटल अंतरभूत पूर्णांक ocfs2_inode_is_fast_symlink(काष्ठा inode *inode)
अणु
	वापस (S_ISLNK(inode->i_mode) &&
		inode->i_blocks == 0);
पूर्ण


#पूर्ण_अगर /* OCFS2_SYMLINK_H */
