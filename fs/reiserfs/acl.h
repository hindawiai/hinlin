<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/init.h>
#समावेश <linux/posix_acl.h>

#घोषणा REISERFS_ACL_VERSION	0x0001

प्रकार काष्ठा अणु
	__le16 e_tag;
	__le16 e_perm;
	__le32 e_id;
पूर्ण reiserfs_acl_entry;

प्रकार काष्ठा अणु
	__le16 e_tag;
	__le16 e_perm;
पूर्ण reiserfs_acl_entry_लघु;

प्रकार काष्ठा अणु
	__le32 a_version;
पूर्ण reiserfs_acl_header;

अटल अंतरभूत माप_प्रकार reiserfs_acl_size(पूर्णांक count)
अणु
	अगर (count <= 4) अणु
		वापस माप(reiserfs_acl_header) +
		    count * माप(reiserfs_acl_entry_लघु);
	पूर्ण अन्यथा अणु
		वापस माप(reiserfs_acl_header) +
		    4 * माप(reiserfs_acl_entry_लघु) +
		    (count - 4) * माप(reiserfs_acl_entry);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक reiserfs_acl_count(माप_प्रकार size)
अणु
	sमाप_प्रकार s;
	size -= माप(reiserfs_acl_header);
	s = size - 4 * माप(reiserfs_acl_entry_लघु);
	अगर (s < 0) अणु
		अगर (size % माप(reiserfs_acl_entry_लघु))
			वापस -1;
		वापस size / माप(reiserfs_acl_entry_लघु);
	पूर्ण अन्यथा अणु
		अगर (s % माप(reiserfs_acl_entry))
			वापस -1;
		वापस s / माप(reiserfs_acl_entry) + 4;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_REISERFS_FS_POSIX_ACL
काष्ठा posix_acl *reiserfs_get_acl(काष्ठा inode *inode, पूर्णांक type);
पूर्णांक reiserfs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		     काष्ठा posix_acl *acl, पूर्णांक type);
पूर्णांक reiserfs_acl_chmod(काष्ठा inode *inode);
पूर्णांक reiserfs_inherit_शेष_acl(काष्ठा reiserfs_transaction_handle *th,
				 काष्ठा inode *dir, काष्ठा dentry *dentry,
				 काष्ठा inode *inode);
पूर्णांक reiserfs_cache_शेष_acl(काष्ठा inode *dir);

#अन्यथा

#घोषणा reiserfs_cache_शेष_acl(inode) 0
#घोषणा reiserfs_get_acl शून्य
#घोषणा reiserfs_set_acl शून्य

अटल अंतरभूत पूर्णांक reiserfs_acl_chmod(काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
reiserfs_inherit_शेष_acl(काष्ठा reiserfs_transaction_handle *th,
			     स्थिर काष्ठा inode *dir, काष्ठा dentry *dentry,
			     काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
