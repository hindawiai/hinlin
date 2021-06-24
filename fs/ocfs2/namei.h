<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * namei.h
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_NAMEI_H
#घोषणा OCFS2_NAMEI_H

#घोषणा OCFS2_DIO_ORPHAN_PREFIX "dio-"
#घोषणा OCFS2_DIO_ORPHAN_PREFIX_LEN 4

बाह्य स्थिर काष्ठा inode_operations ocfs2_dir_iops;

काष्ठा dentry *ocfs2_get_parent(काष्ठा dentry *child);

पूर्णांक ocfs2_orphan_del(काष्ठा ocfs2_super *osb,
		     handle_t *handle,
		     काष्ठा inode *orphan_dir_inode,
		     काष्ठा inode *inode,
		     काष्ठा buffer_head *orphan_dir_bh,
		     bool dio);
पूर्णांक ocfs2_create_inode_in_orphan(काष्ठा inode *dir,
				 पूर्णांक mode,
				 काष्ठा inode **new_inode);
पूर्णांक ocfs2_add_inode_to_orphan(काष्ठा ocfs2_super *osb,
		काष्ठा inode *inode);
पूर्णांक ocfs2_del_inode_from_orphan(काष्ठा ocfs2_super *osb,
		काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
		पूर्णांक update_isize, loff_t end);
पूर्णांक ocfs2_mv_orphaned_inode_to_new(काष्ठा inode *dir,
				   काष्ठा inode *new_inode,
				   काष्ठा dentry *new_dentry);

#पूर्ण_अगर /* OCFS2_NAMEI_H */
