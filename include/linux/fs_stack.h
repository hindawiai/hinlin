<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FS_STACK_H
#घोषणा _LINUX_FS_STACK_H

/* This file defines generic functions used primarily by stackable
 * fileप्रणालीs; none of these functions require i_mutex to be held.
 */

#समावेश <linux/fs.h>

/* बाह्यs क्रम fs/stack.c */
बाह्य व्योम fsstack_copy_attr_all(काष्ठा inode *dest, स्थिर काष्ठा inode *src);
बाह्य व्योम fsstack_copy_inode_size(काष्ठा inode *dst, काष्ठा inode *src);

/* अंतरभूतs */
अटल अंतरभूत व्योम fsstack_copy_attr_aसमय(काष्ठा inode *dest,
					   स्थिर काष्ठा inode *src)
अणु
	dest->i_aसमय = src->i_aसमय;
पूर्ण

अटल अंतरभूत व्योम fsstack_copy_attr_बार(काष्ठा inode *dest,
					   स्थिर काष्ठा inode *src)
अणु
	dest->i_aसमय = src->i_aसमय;
	dest->i_mसमय = src->i_mसमय;
	dest->i_स_समय = src->i_स_समय;
पूर्ण

#पूर्ण_अगर /* _LINUX_FS_STACK_H */
