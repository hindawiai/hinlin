<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/reiserfs_xattr.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/xattr.h>

काष्ठा inode;
काष्ठा dentry;
काष्ठा iattr;
काष्ठा super_block;

पूर्णांक reiserfs_xattr_रेजिस्टर_handlers(व्योम) __init;
व्योम reiserfs_xattr_unरेजिस्टर_handlers(व्योम);
पूर्णांक reiserfs_xattr_init(काष्ठा super_block *sb, पूर्णांक mount_flags);
पूर्णांक reiserfs_lookup_privroot(काष्ठा super_block *sb);
पूर्णांक reiserfs_delete_xattrs(काष्ठा inode *inode);
पूर्णांक reiserfs_chown_xattrs(काष्ठा inode *inode, काष्ठा iattr *attrs);
पूर्णांक reiserfs_permission(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *inode, पूर्णांक mask);

#अगर_घोषित CONFIG_REISERFS_FS_XATTR
#घोषणा has_xattr_dir(inode) (REISERFS_I(inode)->i_flags & i_has_xattr_dir)
sमाप_प्रकार reiserfs_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size);

पूर्णांक reiserfs_xattr_get(काष्ठा inode *, स्थिर अक्षर *, व्योम *, माप_प्रकार);
पूर्णांक reiserfs_xattr_set(काष्ठा inode *, स्थिर अक्षर *, स्थिर व्योम *, माप_प्रकार, पूर्णांक);
पूर्णांक reiserfs_xattr_set_handle(काष्ठा reiserfs_transaction_handle *,
			      काष्ठा inode *, स्थिर अक्षर *, स्थिर व्योम *,
			      माप_प्रकार, पूर्णांक);

बाह्य स्थिर काष्ठा xattr_handler reiserfs_xattr_user_handler;
बाह्य स्थिर काष्ठा xattr_handler reiserfs_xattr_trusted_handler;
बाह्य स्थिर काष्ठा xattr_handler reiserfs_xattr_security_handler;
#अगर_घोषित CONFIG_REISERFS_FS_SECURITY
पूर्णांक reiserfs_security_init(काष्ठा inode *dir, काष्ठा inode *inode,
			   स्थिर काष्ठा qstr *qstr,
			   काष्ठा reiserfs_security_handle *sec);
पूर्णांक reiserfs_security_ग_लिखो(काष्ठा reiserfs_transaction_handle *th,
			    काष्ठा inode *inode,
			    काष्ठा reiserfs_security_handle *sec);
व्योम reiserfs_security_मुक्त(काष्ठा reiserfs_security_handle *sec);
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक reiserfs_xattrs_initialized(काष्ठा super_block *sb)
अणु
	वापस REISERFS_SB(sb)->priv_root && REISERFS_SB(sb)->xattr_root;
पूर्ण

#घोषणा xattr_size(size) ((size) + माप(काष्ठा reiserfs_xattr_header))
अटल अंतरभूत loff_t reiserfs_xattr_nblocks(काष्ठा inode *inode, loff_t size)
अणु
	loff_t ret = 0;
	अगर (reiserfs_file_data_log(inode)) अणु
		ret = _ROUND_UP(xattr_size(size), inode->i_sb->s_blocksize);
		ret >>= inode->i_sb->s_blocksize_bits;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * We may have to create up to 3 objects: xattr root, xattr dir, xattr file.
 * Let's try to be smart about it.
 * xattr root: We cache it. If it's not cached, we may need to create it.
 * xattr dir: If anything has been loaded क्रम this inode, we can set a flag
 *            saying so.
 * xattr file: Since we करोn't cache xattrs, we can't tell. We always include
 *             blocks क्रम it.
 *
 * However, since root and dir can be created between calls - YOU MUST SAVE
 * THIS VALUE.
 */
अटल अंतरभूत माप_प्रकार reiserfs_xattr_jcreate_nblocks(काष्ठा inode *inode)
अणु
	माप_प्रकार nblocks = JOURNAL_BLOCKS_PER_OBJECT(inode->i_sb);

	अगर ((REISERFS_I(inode)->i_flags & i_has_xattr_dir) == 0) अणु
		nblocks += JOURNAL_BLOCKS_PER_OBJECT(inode->i_sb);
		अगर (d_really_is_negative(REISERFS_SB(inode->i_sb)->xattr_root))
			nblocks += JOURNAL_BLOCKS_PER_OBJECT(inode->i_sb);
	पूर्ण

	वापस nblocks;
पूर्ण

अटल अंतरभूत व्योम reiserfs_init_xattr_rwsem(काष्ठा inode *inode)
अणु
	init_rwsem(&REISERFS_I(inode)->i_xattr_sem);
पूर्ण

#अन्यथा

#घोषणा reiserfs_listxattr शून्य

अटल अंतरभूत व्योम reiserfs_init_xattr_rwsem(काष्ठा inode *inode)
अणु
पूर्ण
#पूर्ण_अगर  /*  CONFIG_REISERFS_FS_XATTR  */

#अगर_अघोषित CONFIG_REISERFS_FS_SECURITY
अटल अंतरभूत पूर्णांक reiserfs_security_init(काष्ठा inode *dir,
					 काष्ठा inode *inode,
					 स्थिर काष्ठा qstr *qstr,
					 काष्ठा reiserfs_security_handle *sec)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक
reiserfs_security_ग_लिखो(काष्ठा reiserfs_transaction_handle *th,
			काष्ठा inode *inode,
			काष्ठा reiserfs_security_handle *sec)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम reiserfs_security_मुक्त(काष्ठा reiserfs_security_handle *sec)
अणुपूर्ण
#पूर्ण_अगर
