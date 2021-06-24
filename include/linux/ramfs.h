<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RAMFS_H
#घोषणा _LINUX_RAMFS_H

#समावेश <linux/fs_parser.h> // bleh...

काष्ठा inode *ramfs_get_inode(काष्ठा super_block *sb, स्थिर काष्ठा inode *dir,
	 umode_t mode, dev_t dev);
बाह्य पूर्णांक ramfs_init_fs_context(काष्ठा fs_context *fc);

#अगर_घोषित CONFIG_MMU
अटल अंतरभूत पूर्णांक
ramfs_nommu_expand_क्रम_mapping(काष्ठा inode *inode, माप_प्रकार newsize)
अणु
	वापस 0;
पूर्ण
#अन्यथा
बाह्य पूर्णांक ramfs_nommu_expand_क्रम_mapping(काष्ठा inode *inode, माप_प्रकार newsize);
#पूर्ण_अगर

बाह्य स्थिर काष्ठा fs_parameter_spec ramfs_fs_parameters[];
बाह्य स्थिर काष्ठा file_operations ramfs_file_operations;
बाह्य स्थिर काष्ठा vm_operations_काष्ठा generic_file_vm_ops;

#पूर्ण_अगर
