<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2002
 */

#अगर_अघोषित H_JFS_XATTR
#घोषणा H_JFS_XATTR

#समावेश <linux/xattr.h>

/*
 * jfs_ea_list describe the on-disk क्रमmat of the extended attributes.
 * I know the null-terminator is redundant since namelen is stored, but
 * I am मुख्यtaining compatibility with OS/2 where possible.
 */
काष्ठा jfs_ea अणु
	u8 flag;	/* Unused? */
	u8 namelen;	/* Length of name */
	__le16 valuelen;	/* Length of value */
	अक्षर name[];	/* Attribute name (includes null-terminator) */
पूर्ण;			/* Value immediately follows name */

काष्ठा jfs_ea_list अणु
	__le32 size;		/* overall size */
	काष्ठा jfs_ea ea[];	/* Variable length list */
पूर्ण;

/* Macros क्रम defining maxiumum number of bytes supported क्रम EAs */
#घोषणा MAXEASIZE	65535
#घोषणा MAXEALISTSIZE	MAXEASIZE

/*
 * some macros क्रम dealing with variable length EA lists.
 */
#घोषणा EA_SIZE(ea) \
	(माप (काष्ठा jfs_ea) + (ea)->namelen + 1 + \
	 le16_to_cpu((ea)->valuelen))
#घोषणा	NEXT_EA(ea) ((काष्ठा jfs_ea *) (((अक्षर *) (ea)) + (EA_SIZE (ea))))
#घोषणा	FIRST_EA(ealist) ((ealist)->ea)
#घोषणा	EALIST_SIZE(ealist) le32_to_cpu((ealist)->size)
#घोषणा	END_EALIST(ealist) \
	((काष्ठा jfs_ea *) (((अक्षर *) (ealist)) + EALIST_SIZE(ealist)))

बाह्य पूर्णांक __jfs_setxattr(tid_t, काष्ठा inode *, स्थिर अक्षर *, स्थिर व्योम *,
			  माप_प्रकार, पूर्णांक);
बाह्य sमाप_प्रकार __jfs_getxattr(काष्ठा inode *, स्थिर अक्षर *, व्योम *, माप_प्रकार);
बाह्य sमाप_प्रकार jfs_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);

बाह्य स्थिर काष्ठा xattr_handler *jfs_xattr_handlers[];

#अगर_घोषित CONFIG_JFS_SECURITY
बाह्य पूर्णांक jfs_init_security(tid_t, काष्ठा inode *, काष्ठा inode *,
			     स्थिर काष्ठा qstr *);
#अन्यथा
अटल अंतरभूत पूर्णांक jfs_init_security(tid_t tid, काष्ठा inode *inode,
				    काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* H_JFS_XATTR */
