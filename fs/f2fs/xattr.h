<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs/f2fs/xattr.h
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 *
 * Portions of this code from linux/fs/ext2/xattr.h
 *
 * On-disk क्रमmat of extended attributes क्रम the ext2 fileप्रणाली.
 *
 * (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
 */
#अगर_अघोषित __F2FS_XATTR_H__
#घोषणा __F2FS_XATTR_H__

#समावेश <linux/init.h>
#समावेश <linux/xattr.h>

/* Magic value in attribute blocks */
#घोषणा F2FS_XATTR_MAGIC                0xF2F52011

/* Maximum number of references to one attribute block */
#घोषणा F2FS_XATTR_REFCOUNT_MAX         1024

/* Name indexes */
#घोषणा F2FS_SYSTEM_ADVISE_NAME			"system.advise"
#घोषणा F2FS_XATTR_INDEX_USER			1
#घोषणा F2FS_XATTR_INDEX_POSIX_ACL_ACCESS	2
#घोषणा F2FS_XATTR_INDEX_POSIX_ACL_DEFAULT	3
#घोषणा F2FS_XATTR_INDEX_TRUSTED		4
#घोषणा F2FS_XATTR_INDEX_LUSTRE			5
#घोषणा F2FS_XATTR_INDEX_SECURITY		6
#घोषणा F2FS_XATTR_INDEX_ADVISE			7
/* Should be same as EXT4_XATTR_INDEX_ENCRYPTION */
#घोषणा F2FS_XATTR_INDEX_ENCRYPTION		9
#घोषणा F2FS_XATTR_INDEX_VERITY			11

#घोषणा F2FS_XATTR_NAME_ENCRYPTION_CONTEXT	"c"
#घोषणा F2FS_XATTR_NAME_VERITY			"v"

काष्ठा f2fs_xattr_header अणु
	__le32  h_magic;        /* magic number क्रम identअगरication */
	__le32  h_refcount;     /* reference count */
	__u32   h_reserved[4];  /* zero right now */
पूर्ण;

काष्ठा f2fs_xattr_entry अणु
	__u8    e_name_index;
	__u8    e_name_len;
	__le16  e_value_size;   /* size of attribute value */
	अक्षर    e_name[];      /* attribute name */
पूर्ण;

#घोषणा XATTR_HDR(ptr)		((काष्ठा f2fs_xattr_header *)(ptr))
#घोषणा XATTR_ENTRY(ptr)	((काष्ठा f2fs_xattr_entry *)(ptr))
#घोषणा XATTR_FIRST_ENTRY(ptr)	(XATTR_ENTRY(XATTR_HDR(ptr) + 1))
#घोषणा XATTR_ROUND		(3)

#घोषणा XATTR_ALIGN(size)	(((size) + XATTR_ROUND) & ~XATTR_ROUND)

#घोषणा ENTRY_SIZE(entry) (XATTR_ALIGN(माप(काष्ठा f2fs_xattr_entry) + \
			(entry)->e_name_len + le16_to_cpu((entry)->e_value_size)))

#घोषणा XATTR_NEXT_ENTRY(entry)	((काष्ठा f2fs_xattr_entry *)((अक्षर *)(entry) +\
			ENTRY_SIZE(entry)))

#घोषणा IS_XATTR_LAST_ENTRY(entry) (*(__u32 *)(entry) == 0)

#घोषणा list_क्रम_each_xattr(entry, addr) \
		क्रम (entry = XATTR_FIRST_ENTRY(addr);\
				!IS_XATTR_LAST_ENTRY(entry);\
				entry = XATTR_NEXT_ENTRY(entry))
#घोषणा VALID_XATTR_BLOCK_SIZE	(PAGE_SIZE - माप(काष्ठा node_footer))
#घोषणा XATTR_PADDING_SIZE	(माप(__u32))
#घोषणा XATTR_SIZE(i)		((F2FS_I(i)->i_xattr_nid ?		\
					VALID_XATTR_BLOCK_SIZE : 0) +	\
						(अंतरभूत_xattr_size(i)))
#घोषणा MIN_OFFSET(i)		XATTR_ALIGN(अंतरभूत_xattr_size(i) +	\
						VALID_XATTR_BLOCK_SIZE)

#घोषणा MAX_VALUE_LEN(i)	(MIN_OFFSET(i) -			\
				माप(काष्ठा f2fs_xattr_header) -	\
				माप(काष्ठा f2fs_xattr_entry))

#घोषणा MAX_INLINE_XATTR_SIZE						\
			(DEF_ADDRS_PER_INODE -				\
			F2FS_TOTAL_EXTRA_ATTR_SIZE / माप(__le32) -	\
			DEF_INLINE_RESERVED_SIZE -			\
			MIN_INLINE_DENTRY_SIZE / माप(__le32))

/*
 * On-disk काष्ठाure of f2fs_xattr
 * We use अंतरभूत xattrs space + 1 block क्रम xattr.
 *
 * +--------------------+
 * | f2fs_xattr_header  |
 * |                    |
 * +--------------------+
 * | f2fs_xattr_entry   |
 * | .e_name_index = 1  |
 * | .e_name_len = 3    |
 * | .e_value_size = 14 |
 * | .e_name = "foo"    |
 * | "value_of_xattr"   |<- value_offs = e_name + e_name_len
 * +--------------------+
 * | f2fs_xattr_entry   |
 * | .e_name_index = 4  |
 * | .e_name = "bar"    |
 * +--------------------+
 * |                    |
 * |        Free        |
 * |                    |
 * +--------------------+<- MIN_OFFSET
 * |   node_footer      |
 * | (nid, ino, offset) |
 * +--------------------+
 *
 **/

#अगर_घोषित CONFIG_F2FS_FS_XATTR
बाह्य स्थिर काष्ठा xattr_handler f2fs_xattr_user_handler;
बाह्य स्थिर काष्ठा xattr_handler f2fs_xattr_trusted_handler;
बाह्य स्थिर काष्ठा xattr_handler f2fs_xattr_advise_handler;
बाह्य स्थिर काष्ठा xattr_handler f2fs_xattr_security_handler;

बाह्य स्थिर काष्ठा xattr_handler *f2fs_xattr_handlers[];

बाह्य पूर्णांक f2fs_setxattr(काष्ठा inode *, पूर्णांक, स्थिर अक्षर *,
				स्थिर व्योम *, माप_प्रकार, काष्ठा page *, पूर्णांक);
बाह्य पूर्णांक f2fs_getxattr(काष्ठा inode *, पूर्णांक, स्थिर अक्षर *, व्योम *,
						माप_प्रकार, काष्ठा page *);
बाह्य sमाप_प्रकार f2fs_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);
बाह्य पूर्णांक f2fs_init_xattr_caches(काष्ठा f2fs_sb_info *);
बाह्य व्योम f2fs_destroy_xattr_caches(काष्ठा f2fs_sb_info *);
#अन्यथा

#घोषणा f2fs_xattr_handlers	शून्य
#घोषणा f2fs_listxattr		शून्य
अटल अंतरभूत पूर्णांक f2fs_setxattr(काष्ठा inode *inode, पूर्णांक index,
		स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size,
		काष्ठा page *page, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक f2fs_getxattr(काष्ठा inode *inode, पूर्णांक index,
			स्थिर अक्षर *name, व्योम *buffer,
			माप_प्रकार buffer_size, काष्ठा page *dpage)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक f2fs_init_xattr_caches(काष्ठा f2fs_sb_info *sbi) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम f2fs_destroy_xattr_caches(काष्ठा f2fs_sb_info *sbi) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_F2FS_FS_SECURITY
बाह्य पूर्णांक f2fs_init_security(काष्ठा inode *, काष्ठा inode *,
				स्थिर काष्ठा qstr *, काष्ठा page *);
#अन्यथा
अटल अंतरभूत पूर्णांक f2fs_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				स्थिर काष्ठा qstr *qstr, काष्ठा page *ipage)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __F2FS_XATTR_H__ */
