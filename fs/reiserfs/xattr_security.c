<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "reiserfs.h"
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/xattr.h>
#समावेश <linux/slab.h>
#समावेश "xattr.h"
#समावेश <linux/security.h>
#समावेश <linux/uaccess.h>

अटल पूर्णांक
security_get(स्थिर काष्ठा xattr_handler *handler, काष्ठा dentry *unused,
	     काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	अगर (IS_PRIVATE(inode))
		वापस -EPERM;

	वापस reiserfs_xattr_get(inode, xattr_full_name(handler, name),
				  buffer, size);
पूर्ण

अटल पूर्णांक
security_set(स्थिर काष्ठा xattr_handler *handler,
	     काष्ठा user_namespace *mnt_userns, काष्ठा dentry *unused,
	     काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *buffer,
	     माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (IS_PRIVATE(inode))
		वापस -EPERM;

	वापस reiserfs_xattr_set(inode,
				  xattr_full_name(handler, name),
				  buffer, size, flags);
पूर्ण

अटल bool security_list(काष्ठा dentry *dentry)
अणु
	वापस !IS_PRIVATE(d_inode(dentry));
पूर्ण

/* Initializes the security context क्रम a new inode and वापसs the number
 * of blocks needed क्रम the transaction. If successful, reiserfs_security
 * must be released using reiserfs_security_मुक्त when the caller is करोne. */
पूर्णांक reiserfs_security_init(काष्ठा inode *dir, काष्ठा inode *inode,
			   स्थिर काष्ठा qstr *qstr,
			   काष्ठा reiserfs_security_handle *sec)
अणु
	पूर्णांक blocks = 0;
	पूर्णांक error;

	sec->name = शून्य;

	/* Don't add selinux attributes on xattrs - they'll never get used */
	अगर (IS_PRIVATE(dir))
		वापस 0;

	error = security_old_inode_init_security(inode, dir, qstr, &sec->name,
						 &sec->value, &sec->length);
	अगर (error) अणु
		अगर (error == -EOPNOTSUPP)
			error = 0;

		sec->name = शून्य;
		sec->value = शून्य;
		sec->length = 0;
		वापस error;
	पूर्ण

	अगर (sec->length && reiserfs_xattrs_initialized(inode->i_sb)) अणु
		blocks = reiserfs_xattr_jcreate_nblocks(inode) +
			 reiserfs_xattr_nblocks(inode, sec->length);
		/* We करोn't want to count the directories twice अगर we have
		 * a शेष ACL. */
		REISERFS_I(inode)->i_flags |= i_has_xattr_dir;
	पूर्ण
	वापस blocks;
पूर्ण

पूर्णांक reiserfs_security_ग_लिखो(काष्ठा reiserfs_transaction_handle *th,
			    काष्ठा inode *inode,
			    काष्ठा reiserfs_security_handle *sec)
अणु
	पूर्णांक error;
	अगर (म_माप(sec->name) < माप(XATTR_SECURITY_PREFIX))
		वापस -EINVAL;

	error = reiserfs_xattr_set_handle(th, inode, sec->name, sec->value,
					  sec->length, XATTR_CREATE);
	अगर (error == -ENODATA || error == -EOPNOTSUPP)
		error = 0;

	वापस error;
पूर्ण

व्योम reiserfs_security_मुक्त(काष्ठा reiserfs_security_handle *sec)
अणु
	kमुक्त(sec->name);
	kमुक्त(sec->value);
	sec->name = शून्य;
	sec->value = शून्य;
पूर्ण

स्थिर काष्ठा xattr_handler reiserfs_xattr_security_handler = अणु
	.prefix = XATTR_SECURITY_PREFIX,
	.get = security_get,
	.set = security_set,
	.list = security_list,
पूर्ण;
