<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* RomFS पूर्णांकernal definitions
 *
 * Copyright तऊ 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/romfs_fs.h>

काष्ठा romfs_inode_info अणु
	काष्ठा inode	vfs_inode;
	अचिन्हित दीर्घ	i_metasize;	/* size of non-data area */
	अचिन्हित दीर्घ	i_dataoffset;	/* from the start of fs */
पूर्ण;

अटल अंतरभूत माप_प्रकार romfs_maxsize(काष्ठा super_block *sb)
अणु
	वापस (माप_प्रकार) (अचिन्हित दीर्घ) sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा romfs_inode_info *ROMFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा romfs_inode_info, vfs_inode);
पूर्ण

/*
 * mmap-nommu.c
 */
#अगर !defined(CONFIG_MMU) && defined(CONFIG_ROMFS_ON_MTD)
बाह्य स्थिर काष्ठा file_operations romfs_ro_fops;
#अन्यथा
#घोषणा romfs_ro_fops	generic_ro_fops
#पूर्ण_अगर

/*
 * storage.c
 */
बाह्य पूर्णांक romfs_dev_पढ़ो(काष्ठा super_block *sb, अचिन्हित दीर्घ pos,
			  व्योम *buf, माप_प्रकार buflen);
बाह्य sमाप_प्रकार romfs_dev_strnlen(काष्ठा super_block *sb,
				 अचिन्हित दीर्घ pos, माप_प्रकार maxlen);
बाह्य पूर्णांक romfs_dev_म_भेद(काष्ठा super_block *sb, अचिन्हित दीर्घ pos,
			    स्थिर अक्षर *str, माप_प्रकार size);
