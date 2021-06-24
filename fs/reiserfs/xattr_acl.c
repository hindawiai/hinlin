<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/posix_acl.h>
#समावेश "reiserfs.h"
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/xattr.h>
#समावेश <linux/slab.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश <linux/uaccess.h>

अटल पूर्णांक __reiserfs_set_acl(काष्ठा reiserfs_transaction_handle *th,
			    काष्ठा inode *inode, पूर्णांक type,
			    काष्ठा posix_acl *acl);


पूर्णांक
reiserfs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		 काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक error, error2;
	काष्ठा reiserfs_transaction_handle th;
	माप_प्रकार jcreate_blocks;
	पूर्णांक size = acl ? posix_acl_xattr_size(acl->a_count) : 0;
	पूर्णांक update_mode = 0;
	umode_t mode = inode->i_mode;

	/*
	 * Pessimism: We can't assume that anything from the xattr root up
	 * has been created.
	 */

	jcreate_blocks = reiserfs_xattr_jcreate_nblocks(inode) +
			 reiserfs_xattr_nblocks(inode, size) * 2;

	reiserfs_ग_लिखो_lock(inode->i_sb);
	error = journal_begin(&th, inode->i_sb, jcreate_blocks);
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	अगर (error == 0) अणु
		अगर (type == ACL_TYPE_ACCESS && acl) अणु
			error = posix_acl_update_mode(&init_user_ns, inode,
						      &mode, &acl);
			अगर (error)
				जाओ unlock;
			update_mode = 1;
		पूर्ण
		error = __reiserfs_set_acl(&th, inode, type, acl);
		अगर (!error && update_mode)
			inode->i_mode = mode;
unlock:
		reiserfs_ग_लिखो_lock(inode->i_sb);
		error2 = journal_end(&th);
		reiserfs_ग_लिखो_unlock(inode->i_sb);
		अगर (error2)
			error = error2;
	पूर्ण

	वापस error;
पूर्ण

/*
 * Convert from fileप्रणाली to in-memory representation.
 */
अटल काष्ठा posix_acl *reiserfs_posix_acl_from_disk(स्थिर व्योम *value, माप_प्रकार size)
अणु
	स्थिर अक्षर *end = (अक्षर *)value + size;
	पूर्णांक n, count;
	काष्ठा posix_acl *acl;

	अगर (!value)
		वापस शून्य;
	अगर (size < माप(reiserfs_acl_header))
		वापस ERR_PTR(-EINVAL);
	अगर (((reiserfs_acl_header *) value)->a_version !=
	    cpu_to_le32(REISERFS_ACL_VERSION))
		वापस ERR_PTR(-EINVAL);
	value = (अक्षर *)value + माप(reiserfs_acl_header);
	count = reiserfs_acl_count(size);
	अगर (count < 0)
		वापस ERR_PTR(-EINVAL);
	अगर (count == 0)
		वापस शून्य;
	acl = posix_acl_alloc(count, GFP_NOFS);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);
	क्रम (n = 0; n < count; n++) अणु
		reiserfs_acl_entry *entry = (reiserfs_acl_entry *) value;
		अगर ((अक्षर *)value + माप(reiserfs_acl_entry_लघु) > end)
			जाओ fail;
		acl->a_entries[n].e_tag = le16_to_cpu(entry->e_tag);
		acl->a_entries[n].e_perm = le16_to_cpu(entry->e_perm);
		चयन (acl->a_entries[n].e_tag) अणु
		हाल ACL_USER_OBJ:
		हाल ACL_GROUP_OBJ:
		हाल ACL_MASK:
		हाल ACL_OTHER:
			value = (अक्षर *)value +
			    माप(reiserfs_acl_entry_लघु);
			अवरोध;

		हाल ACL_USER:
			value = (अक्षर *)value + माप(reiserfs_acl_entry);
			अगर ((अक्षर *)value > end)
				जाओ fail;
			acl->a_entries[n].e_uid = 
				make_kuid(&init_user_ns,
					  le32_to_cpu(entry->e_id));
			अवरोध;
		हाल ACL_GROUP:
			value = (अक्षर *)value + माप(reiserfs_acl_entry);
			अगर ((अक्षर *)value > end)
				जाओ fail;
			acl->a_entries[n].e_gid =
				make_kgid(&init_user_ns,
					  le32_to_cpu(entry->e_id));
			अवरोध;

		शेष:
			जाओ fail;
		पूर्ण
	पूर्ण
	अगर (value != end)
		जाओ fail;
	वापस acl;

fail:
	posix_acl_release(acl);
	वापस ERR_PTR(-EINVAL);
पूर्ण

/*
 * Convert from in-memory to fileप्रणाली representation.
 */
अटल व्योम *reiserfs_posix_acl_to_disk(स्थिर काष्ठा posix_acl *acl, माप_प्रकार * size)
अणु
	reiserfs_acl_header *ext_acl;
	अक्षर *e;
	पूर्णांक n;

	*size = reiserfs_acl_size(acl->a_count);
	ext_acl = kदो_स्मृति(माप(reiserfs_acl_header) +
						  acl->a_count *
						  माप(reiserfs_acl_entry),
						  GFP_NOFS);
	अगर (!ext_acl)
		वापस ERR_PTR(-ENOMEM);
	ext_acl->a_version = cpu_to_le32(REISERFS_ACL_VERSION);
	e = (अक्षर *)ext_acl + माप(reiserfs_acl_header);
	क्रम (n = 0; n < acl->a_count; n++) अणु
		स्थिर काष्ठा posix_acl_entry *acl_e = &acl->a_entries[n];
		reiserfs_acl_entry *entry = (reiserfs_acl_entry *) e;
		entry->e_tag = cpu_to_le16(acl->a_entries[n].e_tag);
		entry->e_perm = cpu_to_le16(acl->a_entries[n].e_perm);
		चयन (acl->a_entries[n].e_tag) अणु
		हाल ACL_USER:
			entry->e_id = cpu_to_le32(
				from_kuid(&init_user_ns, acl_e->e_uid));
			e += माप(reiserfs_acl_entry);
			अवरोध;
		हाल ACL_GROUP:
			entry->e_id = cpu_to_le32(
				from_kgid(&init_user_ns, acl_e->e_gid));
			e += माप(reiserfs_acl_entry);
			अवरोध;

		हाल ACL_USER_OBJ:
		हाल ACL_GROUP_OBJ:
		हाल ACL_MASK:
		हाल ACL_OTHER:
			e += माप(reiserfs_acl_entry_लघु);
			अवरोध;

		शेष:
			जाओ fail;
		पूर्ण
	पूर्ण
	वापस (अक्षर *)ext_acl;

fail:
	kमुक्त(ext_acl);
	वापस ERR_PTR(-EINVAL);
पूर्ण

/*
 * Inode operation get_posix_acl().
 *
 * inode->i_mutex: करोwn
 * BKL held [beक्रमe 2.5.x]
 */
काष्ठा posix_acl *reiserfs_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	अक्षर *name, *value;
	काष्ठा posix_acl *acl;
	पूर्णांक size;
	पूर्णांक retval;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	size = reiserfs_xattr_get(inode, name, शून्य, 0);
	अगर (size < 0) अणु
		अगर (size == -ENODATA || size == -ENOSYS)
			वापस शून्य;
		वापस ERR_PTR(size);
	पूर्ण

	value = kदो_स्मृति(size, GFP_NOFS);
	अगर (!value)
		वापस ERR_PTR(-ENOMEM);

	retval = reiserfs_xattr_get(inode, name, value, size);
	अगर (retval == -ENODATA || retval == -ENOSYS) अणु
		/*
		 * This shouldn't actually happen as it should have
		 * been caught above.. but just in हाल
		 */
		acl = शून्य;
	पूर्ण अन्यथा अगर (retval < 0) अणु
		acl = ERR_PTR(retval);
	पूर्ण अन्यथा अणु
		acl = reiserfs_posix_acl_from_disk(value, retval);
	पूर्ण

	kमुक्त(value);
	वापस acl;
पूर्ण

/*
 * Inode operation set_posix_acl().
 *
 * inode->i_mutex: करोwn
 * BKL held [beक्रमe 2.5.x]
 */
अटल पूर्णांक
__reiserfs_set_acl(काष्ठा reiserfs_transaction_handle *th, काष्ठा inode *inode,
		 पूर्णांक type, काष्ठा posix_acl *acl)
अणु
	अक्षर *name;
	व्योम *value = शून्य;
	माप_प्रकार size = 0;
	पूर्णांक error;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		अगर (!S_ISसूची(inode->i_mode))
			वापस acl ? -EACCES : 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (acl) अणु
		value = reiserfs_posix_acl_to_disk(acl, &size);
		अगर (IS_ERR(value))
			वापस (पूर्णांक)PTR_ERR(value);
	पूर्ण

	error = reiserfs_xattr_set_handle(th, inode, name, value, size, 0);

	/*
	 * Ensure that the inode माला_लो dirtied अगर we're only using
	 * the mode bits and an old ACL didn't exist. We don't need
	 * to check अगर the inode is hashed here since we won't get
	 * called by reiserfs_inherit_शेष_acl().
	 */
	अगर (error == -ENODATA) अणु
		error = 0;
		अगर (type == ACL_TYPE_ACCESS) अणु
			inode->i_स_समय = current_समय(inode);
			mark_inode_dirty(inode);
		पूर्ण
	पूर्ण

	kमुक्त(value);

	अगर (!error)
		set_cached_acl(inode, type, acl);

	वापस error;
पूर्ण

/*
 * dir->i_mutex: locked,
 * inode is new and not released पूर्णांकo the wild yet
 */
पूर्णांक
reiserfs_inherit_शेष_acl(काष्ठा reiserfs_transaction_handle *th,
			     काष्ठा inode *dir, काष्ठा dentry *dentry,
			     काष्ठा inode *inode)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	पूर्णांक err = 0;

	/* ACLs only get applied to files and directories */
	अगर (S_ISLNK(inode->i_mode))
		वापस 0;

	/*
	 * ACLs can only be used on "new" objects, so अगर it's an old object
	 * there is nothing to inherit from
	 */
	अगर (get_inode_sd_version(dir) == STAT_DATA_V1)
		जाओ apply_umask;

	/*
	 * Don't apply ACLs to objects in the .reiserfs_priv tree.. This
	 * would be useless since permissions are ignored, and a pain because
	 * it पूर्णांकroduces locking cycles
	 */
	अगर (IS_PRIVATE(inode))
		जाओ apply_umask;

	err = posix_acl_create(dir, &inode->i_mode, &शेष_acl, &acl);
	अगर (err)
		वापस err;

	अगर (शेष_acl) अणु
		err = __reiserfs_set_acl(th, inode, ACL_TYPE_DEFAULT,
					 शेष_acl);
		posix_acl_release(शेष_acl);
	पूर्ण
	अगर (acl) अणु
		अगर (!err)
			err = __reiserfs_set_acl(th, inode, ACL_TYPE_ACCESS,
						 acl);
		posix_acl_release(acl);
	पूर्ण

	वापस err;

apply_umask:
	/* no ACL, apply umask */
	inode->i_mode &= ~current_umask();
	वापस err;
पूर्ण

/* This is used to cache the शेष acl beक्रमe a new object is created.
 * The biggest reason क्रम this is to get an idea of how many blocks will
 * actually be required क्रम the create operation अगर we must inherit an ACL.
 * An ACL ग_लिखो can add up to 3 object creations and an additional file ग_लिखो
 * so we'd prefer not to reserve that many blocks in the journal अगर we can.
 * It also has the advantage of not loading the ACL with a transaction खोलो,
 * this may seem silly, but अगर the owner of the directory is करोing the
 * creation, the ACL may not be loaded since the permissions wouldn't require
 * it.
 * We वापस the number of blocks required क्रम the transaction.
 */
पूर्णांक reiserfs_cache_शेष_acl(काष्ठा inode *inode)
अणु
	काष्ठा posix_acl *acl;
	पूर्णांक nblocks = 0;

	अगर (IS_PRIVATE(inode))
		वापस 0;

	acl = get_acl(inode, ACL_TYPE_DEFAULT);

	अगर (acl && !IS_ERR(acl)) अणु
		पूर्णांक size = reiserfs_acl_size(acl->a_count);

		/* Other xattrs can be created during inode creation. We करोn't
		 * want to claim too many blocks, so we check to see अगर we
		 * need to create the tree to the xattrs, and then we
		 * just want two files. */
		nblocks = reiserfs_xattr_jcreate_nblocks(inode);
		nblocks += JOURNAL_BLOCKS_PER_OBJECT(inode->i_sb);

		REISERFS_I(inode)->i_flags |= i_has_xattr_dir;

		/* We need to account क्रम ग_लिखोs + biपंचांगaps क्रम two files */
		nblocks += reiserfs_xattr_nblocks(inode, size) * 4;
		posix_acl_release(acl);
	पूर्ण

	वापस nblocks;
पूर्ण

/*
 * Called under i_mutex
 */
पूर्णांक reiserfs_acl_chmod(काष्ठा inode *inode)
अणु
	अगर (IS_PRIVATE(inode))
		वापस 0;
	अगर (get_inode_sd_version(inode) == STAT_DATA_V1 ||
	    !reiserfs_posixacl(inode->i_sb))
		वापस 0;

	वापस posix_acl_chmod(&init_user_ns, inode, inode->i_mode);
पूर्ण
