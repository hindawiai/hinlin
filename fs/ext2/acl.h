<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
  File: fs/ext2/acl.h

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#समावेश <linux/posix_acl_xattr.h>

#घोषणा EXT2_ACL_VERSION	0x0001

प्रकार काष्ठा अणु
	__le16		e_tag;
	__le16		e_perm;
	__le32		e_id;
पूर्ण ext2_acl_entry;

प्रकार काष्ठा अणु
	__le16		e_tag;
	__le16		e_perm;
पूर्ण ext2_acl_entry_लघु;

प्रकार काष्ठा अणु
	__le32		a_version;
पूर्ण ext2_acl_header;

अटल अंतरभूत माप_प्रकार ext2_acl_size(पूर्णांक count)
अणु
	अगर (count <= 4) अणु
		वापस माप(ext2_acl_header) +
		       count * माप(ext2_acl_entry_लघु);
	पूर्ण अन्यथा अणु
		वापस माप(ext2_acl_header) +
		       4 * माप(ext2_acl_entry_लघु) +
		       (count - 4) * माप(ext2_acl_entry);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ext2_acl_count(माप_प्रकार size)
अणु
	sमाप_प्रकार s;
	size -= माप(ext2_acl_header);
	s = size - 4 * माप(ext2_acl_entry_लघु);
	अगर (s < 0) अणु
		अगर (size % माप(ext2_acl_entry_लघु))
			वापस -1;
		वापस size / माप(ext2_acl_entry_लघु);
	पूर्ण अन्यथा अणु
		अगर (s % माप(ext2_acl_entry))
			वापस -1;
		वापस s / माप(ext2_acl_entry) + 4;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_EXT2_FS_POSIX_ACL

/* acl.c */
बाह्य काष्ठा posix_acl *ext2_get_acl(काष्ठा inode *inode, पूर्णांक type);
बाह्य पूर्णांक ext2_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
			काष्ठा posix_acl *acl, पूर्णांक type);
बाह्य पूर्णांक ext2_init_acl (काष्ठा inode *, काष्ठा inode *);

#अन्यथा
#समावेश <linux/sched.h>
#घोषणा ext2_get_acl	शून्य
#घोषणा ext2_set_acl	शून्य

अटल अंतरभूत पूर्णांक ext2_init_acl (काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

