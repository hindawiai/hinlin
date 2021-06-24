<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved
 */

#समावेश "autofs_i.h"

अटल स्थिर अक्षर *स्वतःfs_get_link(काष्ठा dentry *dentry,
				   काष्ठा inode *inode,
				   काष्ठा delayed_call *करोne)
अणु
	काष्ठा स्वतःfs_sb_info *sbi;
	काष्ठा स्वतःfs_info *ino;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);
	sbi = स्वतःfs_sbi(dentry->d_sb);
	ino = स्वतःfs_dentry_ino(dentry);
	अगर (ino && !स्वतःfs_oz_mode(sbi))
		ino->last_used = jअगरfies;
	वापस d_inode(dentry)->i_निजी;
पूर्ण

स्थिर काष्ठा inode_operations स्वतःfs_symlink_inode_operations = अणु
	.get_link	= स्वतःfs_get_link
पूर्ण;
