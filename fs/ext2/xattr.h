<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
  File: linux/ext2_xattr.h

  On-disk क्रमmat of extended attributes क्रम the ext2 fileप्रणाली.

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#समावेश <linux/init.h>
#समावेश <linux/xattr.h>

/* Magic value in attribute blocks */
#घोषणा EXT2_XATTR_MAGIC		0xEA020000

/* Maximum number of references to one attribute block */
#घोषणा EXT2_XATTR_REFCOUNT_MAX		1024

/* Name indexes */
#घोषणा EXT2_XATTR_INDEX_USER			1
#घोषणा EXT2_XATTR_INDEX_POSIX_ACL_ACCESS	2
#घोषणा EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT	3
#घोषणा EXT2_XATTR_INDEX_TRUSTED		4
#घोषणा	EXT2_XATTR_INDEX_LUSTRE			5
#घोषणा EXT2_XATTR_INDEX_SECURITY	        6

काष्ठा ext2_xattr_header अणु
	__le32	h_magic;	/* magic number क्रम identअगरication */
	__le32	h_refcount;	/* reference count */
	__le32	h_blocks;	/* number of disk blocks used */
	__le32	h_hash;		/* hash value of all attributes */
	__u32	h_reserved[4];	/* zero right now */
पूर्ण;

काष्ठा ext2_xattr_entry अणु
	__u8	e_name_len;	/* length of name */
	__u8	e_name_index;	/* attribute name index */
	__le16	e_value_offs;	/* offset in disk block of value */
	__le32	e_value_block;	/* disk block attribute is stored on (n/i) */
	__le32	e_value_size;	/* size of attribute value */
	__le32	e_hash;		/* hash value of name and value */
	अक्षर	e_name[];	/* attribute name */
पूर्ण;

#घोषणा EXT2_XATTR_PAD_BITS		2
#घोषणा EXT2_XATTR_PAD		(1<<EXT2_XATTR_PAD_BITS)
#घोषणा EXT2_XATTR_ROUND		(EXT2_XATTR_PAD-1)
#घोषणा EXT2_XATTR_LEN(name_len) \
	(((name_len) + EXT2_XATTR_ROUND + \
	माप(काष्ठा ext2_xattr_entry)) & ~EXT2_XATTR_ROUND)
#घोषणा EXT2_XATTR_NEXT(entry) \
	( (काष्ठा ext2_xattr_entry *)( \
	  (अक्षर *)(entry) + EXT2_XATTR_LEN((entry)->e_name_len)) )
#घोषणा EXT2_XATTR_SIZE(size) \
	(((size) + EXT2_XATTR_ROUND) & ~EXT2_XATTR_ROUND)

काष्ठा mb_cache;

# अगरdef CONFIG_EXT2_FS_XATTR

बाह्य स्थिर काष्ठा xattr_handler ext2_xattr_user_handler;
बाह्य स्थिर काष्ठा xattr_handler ext2_xattr_trusted_handler;
बाह्य स्थिर काष्ठा xattr_handler ext2_xattr_security_handler;

बाह्य sमाप_प्रकार ext2_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);

बाह्य पूर्णांक ext2_xattr_get(काष्ठा inode *, पूर्णांक, स्थिर अक्षर *, व्योम *, माप_प्रकार);
बाह्य पूर्णांक ext2_xattr_set(काष्ठा inode *, पूर्णांक, स्थिर अक्षर *, स्थिर व्योम *, माप_प्रकार, पूर्णांक);

बाह्य व्योम ext2_xattr_delete_inode(काष्ठा inode *);

बाह्य काष्ठा mb_cache *ext2_xattr_create_cache(व्योम);
बाह्य व्योम ext2_xattr_destroy_cache(काष्ठा mb_cache *cache);

बाह्य स्थिर काष्ठा xattr_handler *ext2_xattr_handlers[];

# अन्यथा  /* CONFIG_EXT2_FS_XATTR */

अटल अंतरभूत पूर्णांक
ext2_xattr_get(काष्ठा inode *inode, पूर्णांक name_index,
	       स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ext2_xattr_set(काष्ठा inode *inode, पूर्णांक name_index, स्थिर अक्षर *name,
	       स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम
ext2_xattr_delete_inode(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत व्योम ext2_xattr_destroy_cache(काष्ठा mb_cache *cache)
अणु
पूर्ण

#घोषणा ext2_xattr_handlers शून्य
#घोषणा ext2_listxattr शून्य

# endअगर  /* CONFIG_EXT2_FS_XATTR */

#अगर_घोषित CONFIG_EXT2_FS_SECURITY
बाह्य पूर्णांक ext2_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
			      स्थिर काष्ठा qstr *qstr);
#अन्यथा
अटल अंतरभूत पूर्णांक ext2_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				     स्थिर काष्ठा qstr *qstr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
