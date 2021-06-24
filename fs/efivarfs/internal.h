<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Red Hat, Inc.
 * Copyright (C) 2012 Jeremy Kerr <jeremy.kerr@canonical.com>
 */
#अगर_अघोषित EFIVAR_FS_INTERNAL_H
#घोषणा EFIVAR_FS_INTERNAL_H

#समावेश <linux/list.h>

बाह्य स्थिर काष्ठा file_operations efivarfs_file_operations;
बाह्य स्थिर काष्ठा inode_operations efivarfs_dir_inode_operations;
बाह्य bool efivarfs_valid_name(स्थिर अक्षर *str, पूर्णांक len);
बाह्य काष्ठा inode *efivarfs_get_inode(काष्ठा super_block *sb,
			स्थिर काष्ठा inode *dir, पूर्णांक mode, dev_t dev,
			bool is_removable);

बाह्य काष्ठा list_head efivarfs_list;

#पूर्ण_अगर /* EFIVAR_FS_INTERNAL_H */
