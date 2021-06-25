<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 1997-2004 Erez Zaकरोk
 * Copyright (C) 2001-2004 Stony Brook University
 * Copyright (C) 2004-2007 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 *              Michael C. Thompsion <mcthomps@us.ibm.com>
 */

#समावेश <linux/file.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/dcache.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_stack.h>
#समावेश <linux/slab.h>
#समावेश <linux/xattr.h>
#समावेश <linux/fileattr.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "ecryptfs_kernel.h"

अटल पूर्णांक lock_parent(काष्ठा dentry *dentry,
		       काष्ठा dentry **lower_dentry,
		       काष्ठा inode **lower_dir)
अणु
	काष्ठा dentry *lower_dir_dentry;

	lower_dir_dentry = ecryptfs_dentry_to_lower(dentry->d_parent);
	*lower_dir = d_inode(lower_dir_dentry);
	*lower_dentry = ecryptfs_dentry_to_lower(dentry);

	inode_lock_nested(*lower_dir, I_MUTEX_PARENT);
	वापस (*lower_dentry)->d_parent == lower_dir_dentry ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक ecryptfs_inode_test(काष्ठा inode *inode, व्योम *lower_inode)
अणु
	वापस ecryptfs_inode_to_lower(inode) == lower_inode;
पूर्ण

अटल पूर्णांक ecryptfs_inode_set(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा inode *lower_inode = opaque;

	ecryptfs_set_inode_lower(inode, lower_inode);
	fsstack_copy_attr_all(inode, lower_inode);
	/* i_size will be overwritten क्रम encrypted regular files */
	fsstack_copy_inode_size(inode, lower_inode);
	inode->i_ino = lower_inode->i_ino;
	inode->i_mapping->a_ops = &ecryptfs_aops;

	अगर (S_ISLNK(inode->i_mode))
		inode->i_op = &ecryptfs_symlink_iops;
	अन्यथा अगर (S_ISसूची(inode->i_mode))
		inode->i_op = &ecryptfs_dir_iops;
	अन्यथा
		inode->i_op = &ecryptfs_मुख्य_iops;

	अगर (S_ISसूची(inode->i_mode))
		inode->i_fop = &ecryptfs_dir_fops;
	अन्यथा अगर (special_file(inode->i_mode))
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
	अन्यथा
		inode->i_fop = &ecryptfs_मुख्य_fops;

	वापस 0;
पूर्ण

अटल काष्ठा inode *__ecryptfs_get_inode(काष्ठा inode *lower_inode,
					  काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode;

	अगर (lower_inode->i_sb != ecryptfs_superblock_to_lower(sb))
		वापस ERR_PTR(-EXDEV);
	अगर (!igrab(lower_inode))
		वापस ERR_PTR(-ESTALE);
	inode = iget5_locked(sb, (अचिन्हित दीर्घ)lower_inode,
			     ecryptfs_inode_test, ecryptfs_inode_set,
			     lower_inode);
	अगर (!inode) अणु
		iput(lower_inode);
		वापस ERR_PTR(-EACCES);
	पूर्ण
	अगर (!(inode->i_state & I_NEW))
		iput(lower_inode);

	वापस inode;
पूर्ण

काष्ठा inode *ecryptfs_get_inode(काष्ठा inode *lower_inode,
				 काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode = __ecryptfs_get_inode(lower_inode, sb);

	अगर (!IS_ERR(inode) && (inode->i_state & I_NEW))
		unlock_new_inode(inode);

	वापस inode;
पूर्ण

/**
 * ecryptfs_पूर्णांकerpose
 * @lower_dentry: Existing dentry in the lower fileप्रणाली
 * @dentry: ecryptfs' dentry
 * @sb: ecryptfs's super_block
 *
 * Interposes upper and lower dentries.
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक ecryptfs_पूर्णांकerpose(काष्ठा dentry *lower_dentry,
			      काष्ठा dentry *dentry, काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode = ecryptfs_get_inode(d_inode(lower_dentry), sb);

	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);
	d_instantiate(dentry, inode);

	वापस 0;
पूर्ण

अटल पूर्णांक ecryptfs_करो_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry,
			      काष्ठा inode *inode)
अणु
	काष्ठा dentry *lower_dentry;
	काष्ठा inode *lower_dir;
	पूर्णांक rc;

	rc = lock_parent(dentry, &lower_dentry, &lower_dir);
	dget(lower_dentry);	// करोn't even try to make the lower negative
	अगर (!rc) अणु
		अगर (d_unhashed(lower_dentry))
			rc = -EINVAL;
		अन्यथा
			rc = vfs_unlink(&init_user_ns, lower_dir, lower_dentry,
					शून्य);
	पूर्ण
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Error in vfs_unlink; rc = [%d]\n", rc);
		जाओ out_unlock;
	पूर्ण
	fsstack_copy_attr_बार(dir, lower_dir);
	set_nlink(inode, ecryptfs_inode_to_lower(inode)->i_nlink);
	inode->i_स_समय = dir->i_स_समय;
out_unlock:
	dput(lower_dentry);
	inode_unlock(lower_dir);
	अगर (!rc)
		d_drop(dentry);
	वापस rc;
पूर्ण

/**
 * ecryptfs_करो_create
 * @directory_inode: inode of the new file's dentry's parent in ecryptfs
 * @ecryptfs_dentry: New file's dentry in ecryptfs
 * @mode: The mode of the new file
 *
 * Creates the underlying file and the eCryptfs inode which will link to
 * it. It will also update the eCryptfs directory inode to mimic the
 * stat of the lower directory inode.
 *
 * Returns the new eCryptfs inode on success; an ERR_PTR on error condition
 */
अटल काष्ठा inode *
ecryptfs_करो_create(काष्ठा inode *directory_inode,
		   काष्ठा dentry *ecryptfs_dentry, umode_t mode)
अणु
	पूर्णांक rc;
	काष्ठा dentry *lower_dentry;
	काष्ठा inode *lower_dir;
	काष्ठा inode *inode;

	rc = lock_parent(ecryptfs_dentry, &lower_dentry, &lower_dir);
	अगर (!rc)
		rc = vfs_create(&init_user_ns, lower_dir,
				lower_dentry, mode, true);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Failure to create dentry in lower fs; "
		       "rc = [%d]\n", __func__, rc);
		inode = ERR_PTR(rc);
		जाओ out_lock;
	पूर्ण
	inode = __ecryptfs_get_inode(d_inode(lower_dentry),
				     directory_inode->i_sb);
	अगर (IS_ERR(inode)) अणु
		vfs_unlink(&init_user_ns, lower_dir, lower_dentry, शून्य);
		जाओ out_lock;
	पूर्ण
	fsstack_copy_attr_बार(directory_inode, lower_dir);
	fsstack_copy_inode_size(directory_inode, lower_dir);
out_lock:
	inode_unlock(lower_dir);
	वापस inode;
पूर्ण

/*
 * ecryptfs_initialize_file
 *
 * Cause the file to be changed from a basic empty file to an ecryptfs
 * file with a header and first data page.
 *
 * Returns zero on success
 */
पूर्णांक ecryptfs_initialize_file(काष्ठा dentry *ecryptfs_dentry,
			     काष्ठा inode *ecryptfs_inode)
अणु
	काष्ठा ecryptfs_crypt_stat *crypt_stat =
		&ecryptfs_inode_to_निजी(ecryptfs_inode)->crypt_stat;
	पूर्णांक rc = 0;

	अगर (S_ISसूची(ecryptfs_inode->i_mode)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "This is a directory\n");
		crypt_stat->flags &= ~(ECRYPTFS_ENCRYPTED);
		जाओ out;
	पूर्ण
	ecryptfs_prपूर्णांकk(KERN_DEBUG, "Initializing crypto context\n");
	rc = ecryptfs_new_file_context(ecryptfs_inode);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR, "Error creating new file "
				"context; rc = [%d]\n", rc);
		जाओ out;
	पूर्ण
	rc = ecryptfs_get_lower_file(ecryptfs_dentry, ecryptfs_inode);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to initialize "
			"the lower file for the dentry with name "
			"[%pd]; rc = [%d]\n", __func__,
			ecryptfs_dentry, rc);
		जाओ out;
	पूर्ण
	rc = ecryptfs_ग_लिखो_metadata(ecryptfs_dentry, ecryptfs_inode);
	अगर (rc)
		prपूर्णांकk(KERN_ERR "Error writing headers; rc = [%d]\n", rc);
	ecryptfs_put_lower_file(ecryptfs_inode);
out:
	वापस rc;
पूर्ण

/*
 * ecryptfs_create
 * @mode: The mode of the new file.
 *
 * Creates a new file.
 *
 * Returns zero on success; non-zero on error condition
 */
अटल पूर्णांक
ecryptfs_create(काष्ठा user_namespace *mnt_userns,
		काष्ठा inode *directory_inode, काष्ठा dentry *ecryptfs_dentry,
		umode_t mode, bool excl)
अणु
	काष्ठा inode *ecryptfs_inode;
	पूर्णांक rc;

	ecryptfs_inode = ecryptfs_करो_create(directory_inode, ecryptfs_dentry,
					    mode);
	अगर (IS_ERR(ecryptfs_inode)) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Failed to create file in"
				"lower filesystem\n");
		rc = PTR_ERR(ecryptfs_inode);
		जाओ out;
	पूर्ण
	/* At this poपूर्णांक, a file exists on "disk"; we need to make sure
	 * that this on disk file is prepared to be an ecryptfs file */
	rc = ecryptfs_initialize_file(ecryptfs_dentry, ecryptfs_inode);
	अगर (rc) अणु
		ecryptfs_करो_unlink(directory_inode, ecryptfs_dentry,
				   ecryptfs_inode);
		iget_failed(ecryptfs_inode);
		जाओ out;
	पूर्ण
	d_instantiate_new(ecryptfs_dentry, ecryptfs_inode);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_i_size_पढ़ो(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा ecryptfs_crypt_stat *crypt_stat;
	पूर्णांक rc;

	rc = ecryptfs_get_lower_file(dentry, inode);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to initialize "
			"the lower file for the dentry with name "
			"[%pd]; rc = [%d]\n", __func__,
			dentry, rc);
		वापस rc;
	पूर्ण

	crypt_stat = &ecryptfs_inode_to_निजी(inode)->crypt_stat;
	/* TODO: lock क्रम crypt_stat comparison */
	अगर (!(crypt_stat->flags & ECRYPTFS_POLICY_APPLIED))
		ecryptfs_set_शेष_sizes(crypt_stat);

	rc = ecryptfs_पढ़ो_and_validate_header_region(inode);
	ecryptfs_put_lower_file(inode);
	अगर (rc) अणु
		rc = ecryptfs_पढ़ो_and_validate_xattr_region(dentry, inode);
		अगर (!rc)
			crypt_stat->flags |= ECRYPTFS_METADATA_IN_XATTR;
	पूर्ण

	/* Must वापस 0 to allow non-eCryptfs files to be looked up, too */
	वापस 0;
पूर्ण

/*
 * ecryptfs_lookup_पूर्णांकerpose - Dentry पूर्णांकerposition क्रम a lookup
 */
अटल काष्ठा dentry *ecryptfs_lookup_पूर्णांकerpose(काष्ठा dentry *dentry,
				     काष्ठा dentry *lower_dentry)
अणु
	काष्ठा path *path = ecryptfs_dentry_to_lower_path(dentry->d_parent);
	काष्ठा inode *inode, *lower_inode;
	काष्ठा ecryptfs_dentry_info *dentry_info;
	पूर्णांक rc = 0;

	dentry_info = kmem_cache_alloc(ecryptfs_dentry_info_cache, GFP_KERNEL);
	अगर (!dentry_info) अणु
		dput(lower_dentry);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	fsstack_copy_attr_aसमय(d_inode(dentry->d_parent),
				d_inode(path->dentry));
	BUG_ON(!d_count(lower_dentry));

	ecryptfs_set_dentry_निजी(dentry, dentry_info);
	dentry_info->lower_path.mnt = mntget(path->mnt);
	dentry_info->lower_path.dentry = lower_dentry;

	/*
	 * negative dentry can go positive under us here - its parent is not
	 * locked.  That's OK and that could happen just as we वापस from
	 * ecryptfs_lookup() anyway.  Just need to be careful and fetch
	 * ->d_inode only once - it's not stable here.
	 */
	lower_inode = READ_ONCE(lower_dentry->d_inode);

	अगर (!lower_inode) अणु
		/* We want to add because we couldn't find in lower */
		d_add(dentry, शून्य);
		वापस शून्य;
	पूर्ण
	inode = __ecryptfs_get_inode(lower_inode, dentry->d_sb);
	अगर (IS_ERR(inode)) अणु
		prपूर्णांकk(KERN_ERR "%s: Error interposing; rc = [%ld]\n",
		       __func__, PTR_ERR(inode));
		वापस ERR_CAST(inode);
	पूर्ण
	अगर (S_ISREG(inode->i_mode)) अणु
		rc = ecryptfs_i_size_पढ़ो(dentry, inode);
		अगर (rc) अणु
			make_bad_inode(inode);
			वापस ERR_PTR(rc);
		पूर्ण
	पूर्ण

	अगर (inode->i_state & I_NEW)
		unlock_new_inode(inode);
	वापस d_splice_alias(inode, dentry);
पूर्ण

/**
 * ecryptfs_lookup
 * @ecryptfs_dir_inode: The eCryptfs directory inode
 * @ecryptfs_dentry: The eCryptfs dentry that we are looking up
 * @flags: lookup flags
 *
 * Find a file on disk. If the file करोes not exist, then we'll add it to the
 * dentry cache and जारी on to पढ़ो it from the disk.
 */
अटल काष्ठा dentry *ecryptfs_lookup(काष्ठा inode *ecryptfs_dir_inode,
				      काष्ठा dentry *ecryptfs_dentry,
				      अचिन्हित पूर्णांक flags)
अणु
	अक्षर *encrypted_and_encoded_name = शून्य;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat;
	काष्ठा dentry *lower_dir_dentry, *lower_dentry;
	स्थिर अक्षर *name = ecryptfs_dentry->d_name.name;
	माप_प्रकार len = ecryptfs_dentry->d_name.len;
	काष्ठा dentry *res;
	पूर्णांक rc = 0;

	lower_dir_dentry = ecryptfs_dentry_to_lower(ecryptfs_dentry->d_parent);

	mount_crypt_stat = &ecryptfs_superblock_to_निजी(
				ecryptfs_dentry->d_sb)->mount_crypt_stat;
	अगर (mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES) अणु
		rc = ecryptfs_encrypt_and_encode_filename(
			&encrypted_and_encoded_name, &len,
			mount_crypt_stat, name, len);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: Error attempting to encrypt and encode "
			       "filename; rc = [%d]\n", __func__, rc);
			वापस ERR_PTR(rc);
		पूर्ण
		name = encrypted_and_encoded_name;
	पूर्ण

	lower_dentry = lookup_one_len_unlocked(name, lower_dir_dentry, len);
	अगर (IS_ERR(lower_dentry)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "%s: lookup_one_len() returned "
				"[%ld] on lower_dentry = [%s]\n", __func__,
				PTR_ERR(lower_dentry),
				name);
		res = ERR_CAST(lower_dentry);
	पूर्ण अन्यथा अणु
		res = ecryptfs_lookup_पूर्णांकerpose(ecryptfs_dentry, lower_dentry);
	पूर्ण
	kमुक्त(encrypted_and_encoded_name);
	वापस res;
पूर्ण

अटल पूर्णांक ecryptfs_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
			 काष्ठा dentry *new_dentry)
अणु
	काष्ठा dentry *lower_old_dentry;
	काष्ठा dentry *lower_new_dentry;
	काष्ठा inode *lower_dir;
	u64 file_size_save;
	पूर्णांक rc;

	file_size_save = i_size_पढ़ो(d_inode(old_dentry));
	lower_old_dentry = ecryptfs_dentry_to_lower(old_dentry);
	rc = lock_parent(new_dentry, &lower_new_dentry, &lower_dir);
	अगर (!rc)
		rc = vfs_link(lower_old_dentry, &init_user_ns, lower_dir,
			      lower_new_dentry, शून्य);
	अगर (rc || d_really_is_negative(lower_new_dentry))
		जाओ out_lock;
	rc = ecryptfs_पूर्णांकerpose(lower_new_dentry, new_dentry, dir->i_sb);
	अगर (rc)
		जाओ out_lock;
	fsstack_copy_attr_बार(dir, lower_dir);
	fsstack_copy_inode_size(dir, lower_dir);
	set_nlink(d_inode(old_dentry),
		  ecryptfs_inode_to_lower(d_inode(old_dentry))->i_nlink);
	i_size_ग_लिखो(d_inode(new_dentry), file_size_save);
out_lock:
	inode_unlock(lower_dir);
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	वापस ecryptfs_करो_unlink(dir, dentry, d_inode(dentry));
पूर्ण

अटल पूर्णांक ecryptfs_symlink(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *dir, काष्ठा dentry *dentry,
			    स्थिर अक्षर *symname)
अणु
	पूर्णांक rc;
	काष्ठा dentry *lower_dentry;
	काष्ठा inode *lower_dir;
	अक्षर *encoded_symname;
	माप_प्रकार encoded_symlen;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat = शून्य;

	rc = lock_parent(dentry, &lower_dentry, &lower_dir);
	अगर (rc)
		जाओ out_lock;
	mount_crypt_stat = &ecryptfs_superblock_to_निजी(
		dir->i_sb)->mount_crypt_stat;
	rc = ecryptfs_encrypt_and_encode_filename(&encoded_symname,
						  &encoded_symlen,
						  mount_crypt_stat, symname,
						  म_माप(symname));
	अगर (rc)
		जाओ out_lock;
	rc = vfs_symlink(&init_user_ns, lower_dir, lower_dentry,
			 encoded_symname);
	kमुक्त(encoded_symname);
	अगर (rc || d_really_is_negative(lower_dentry))
		जाओ out_lock;
	rc = ecryptfs_पूर्णांकerpose(lower_dentry, dentry, dir->i_sb);
	अगर (rc)
		जाओ out_lock;
	fsstack_copy_attr_बार(dir, lower_dir);
	fsstack_copy_inode_size(dir, lower_dir);
out_lock:
	inode_unlock(lower_dir);
	अगर (d_really_is_negative(dentry))
		d_drop(dentry);
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			  काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक rc;
	काष्ठा dentry *lower_dentry;
	काष्ठा inode *lower_dir;

	rc = lock_parent(dentry, &lower_dentry, &lower_dir);
	अगर (!rc)
		rc = vfs_सूची_गढ़ो(&init_user_ns, lower_dir,
			       lower_dentry, mode);
	अगर (rc || d_really_is_negative(lower_dentry))
		जाओ out;
	rc = ecryptfs_पूर्णांकerpose(lower_dentry, dentry, dir->i_sb);
	अगर (rc)
		जाओ out;
	fsstack_copy_attr_बार(dir, lower_dir);
	fsstack_copy_inode_size(dir, lower_dir);
	set_nlink(dir, lower_dir->i_nlink);
out:
	inode_unlock(lower_dir);
	अगर (d_really_is_negative(dentry))
		d_drop(dentry);
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *lower_dentry;
	काष्ठा inode *lower_dir;
	पूर्णांक rc;

	rc = lock_parent(dentry, &lower_dentry, &lower_dir);
	dget(lower_dentry);	// करोn't even try to make the lower negative
	अगर (!rc) अणु
		अगर (d_unhashed(lower_dentry))
			rc = -EINVAL;
		अन्यथा
			rc = vfs_सूची_हटाओ(&init_user_ns, lower_dir, lower_dentry);
	पूर्ण
	अगर (!rc) अणु
		clear_nlink(d_inode(dentry));
		fsstack_copy_attr_बार(dir, lower_dir);
		set_nlink(dir, lower_dir->i_nlink);
	पूर्ण
	dput(lower_dentry);
	inode_unlock(lower_dir);
	अगर (!rc)
		d_drop(dentry);
	वापस rc;
पूर्ण

अटल पूर्णांक
ecryptfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	       काष्ठा dentry *dentry, umode_t mode, dev_t dev)
अणु
	पूर्णांक rc;
	काष्ठा dentry *lower_dentry;
	काष्ठा inode *lower_dir;

	rc = lock_parent(dentry, &lower_dentry, &lower_dir);
	अगर (!rc)
		rc = vfs_mknod(&init_user_ns, lower_dir,
			       lower_dentry, mode, dev);
	अगर (rc || d_really_is_negative(lower_dentry))
		जाओ out;
	rc = ecryptfs_पूर्णांकerpose(lower_dentry, dentry, dir->i_sb);
	अगर (rc)
		जाओ out;
	fsstack_copy_attr_बार(dir, lower_dir);
	fsstack_copy_inode_size(dir, lower_dir);
out:
	inode_unlock(lower_dir);
	अगर (d_really_is_negative(dentry))
		d_drop(dentry);
	वापस rc;
पूर्ण

अटल पूर्णांक
ecryptfs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक rc;
	काष्ठा dentry *lower_old_dentry;
	काष्ठा dentry *lower_new_dentry;
	काष्ठा dentry *lower_old_dir_dentry;
	काष्ठा dentry *lower_new_dir_dentry;
	काष्ठा dentry *trap;
	काष्ठा inode *target_inode;
	काष्ठा नामdata rd = अणुपूर्ण;

	अगर (flags)
		वापस -EINVAL;

	lower_old_dir_dentry = ecryptfs_dentry_to_lower(old_dentry->d_parent);
	lower_new_dir_dentry = ecryptfs_dentry_to_lower(new_dentry->d_parent);

	lower_old_dentry = ecryptfs_dentry_to_lower(old_dentry);
	lower_new_dentry = ecryptfs_dentry_to_lower(new_dentry);

	target_inode = d_inode(new_dentry);

	trap = lock_नाम(lower_old_dir_dentry, lower_new_dir_dentry);
	dget(lower_new_dentry);
	rc = -EINVAL;
	अगर (lower_old_dentry->d_parent != lower_old_dir_dentry)
		जाओ out_lock;
	अगर (lower_new_dentry->d_parent != lower_new_dir_dentry)
		जाओ out_lock;
	अगर (d_unhashed(lower_old_dentry) || d_unhashed(lower_new_dentry))
		जाओ out_lock;
	/* source should not be ancestor of target */
	अगर (trap == lower_old_dentry)
		जाओ out_lock;
	/* target should not be ancestor of source */
	अगर (trap == lower_new_dentry) अणु
		rc = -ENOTEMPTY;
		जाओ out_lock;
	पूर्ण

	rd.old_mnt_userns	= &init_user_ns;
	rd.old_dir		= d_inode(lower_old_dir_dentry);
	rd.old_dentry		= lower_old_dentry;
	rd.new_mnt_userns	= &init_user_ns;
	rd.new_dir		= d_inode(lower_new_dir_dentry);
	rd.new_dentry		= lower_new_dentry;
	rc = vfs_नाम(&rd);
	अगर (rc)
		जाओ out_lock;
	अगर (target_inode)
		fsstack_copy_attr_all(target_inode,
				      ecryptfs_inode_to_lower(target_inode));
	fsstack_copy_attr_all(new_dir, d_inode(lower_new_dir_dentry));
	अगर (new_dir != old_dir)
		fsstack_copy_attr_all(old_dir, d_inode(lower_old_dir_dentry));
out_lock:
	dput(lower_new_dentry);
	unlock_नाम(lower_old_dir_dentry, lower_new_dir_dentry);
	वापस rc;
पूर्ण

अटल अक्षर *ecryptfs_पढ़ोlink_lower(काष्ठा dentry *dentry, माप_प्रकार *bufsiz)
अणु
	DEFINE_DELAYED_CALL(करोne);
	काष्ठा dentry *lower_dentry = ecryptfs_dentry_to_lower(dentry);
	स्थिर अक्षर *link;
	अक्षर *buf;
	पूर्णांक rc;

	link = vfs_get_link(lower_dentry, &करोne);
	अगर (IS_ERR(link))
		वापस ERR_CAST(link);

	rc = ecryptfs_decode_and_decrypt_filename(&buf, bufsiz, dentry->d_sb,
						  link, म_माप(link));
	करो_delayed_call(&करोne);
	अगर (rc)
		वापस ERR_PTR(rc);

	वापस buf;
पूर्ण

अटल स्थिर अक्षर *ecryptfs_get_link(काष्ठा dentry *dentry,
				     काष्ठा inode *inode,
				     काष्ठा delayed_call *करोne)
अणु
	माप_प्रकार len;
	अक्षर *buf;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	buf = ecryptfs_पढ़ोlink_lower(dentry, &len);
	अगर (IS_ERR(buf))
		वापस buf;
	fsstack_copy_attr_aसमय(d_inode(dentry),
				d_inode(ecryptfs_dentry_to_lower(dentry)));
	buf[len] = '\0';
	set_delayed_call(करोne, kमुक्त_link, buf);
	वापस buf;
पूर्ण

/**
 * upper_माप_प्रकारo_lower_size
 * @crypt_stat: Crypt_stat associated with file
 * @upper_size: Size of the upper file
 *
 * Calculate the required size of the lower file based on the
 * specअगरied size of the upper file. This calculation is based on the
 * number of headers in the underlying file and the extent size.
 *
 * Returns Calculated size of the lower file.
 */
अटल loff_t
upper_माप_प्रकारo_lower_size(काष्ठा ecryptfs_crypt_stat *crypt_stat,
			 loff_t upper_size)
अणु
	loff_t lower_size;

	lower_size = ecryptfs_lower_header_size(crypt_stat);
	अगर (upper_size != 0) अणु
		loff_t num_extents;

		num_extents = upper_size >> crypt_stat->extent_shअगरt;
		अगर (upper_size & ~crypt_stat->extent_mask)
			num_extents++;
		lower_size += (num_extents * crypt_stat->extent_size);
	पूर्ण
	वापस lower_size;
पूर्ण

/**
 * truncate_upper
 * @dentry: The ecryptfs layer dentry
 * @ia: Address of the ecryptfs inode's attributes
 * @lower_ia: Address of the lower inode's attributes
 *
 * Function to handle truncations modअगरying the size of the file. Note
 * that the file sizes are पूर्णांकerpolated. When expanding, we are simply
 * writing strings of 0's out. When truncating, we truncate the upper
 * inode and update the lower_ia according to the page index
 * पूर्णांकerpolations. If ATTR_SIZE is set in lower_ia->ia_valid upon वापस,
 * the caller must use lower_ia in a call to notअगरy_change() to perक्रमm
 * the truncation of the lower inode.
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक truncate_upper(काष्ठा dentry *dentry, काष्ठा iattr *ia,
			  काष्ठा iattr *lower_ia)
अणु
	पूर्णांक rc = 0;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा ecryptfs_crypt_stat *crypt_stat;
	loff_t i_size = i_size_पढ़ो(inode);
	loff_t lower_size_beक्रमe_truncate;
	loff_t lower_size_after_truncate;

	अगर (unlikely((ia->ia_size == i_size))) अणु
		lower_ia->ia_valid &= ~ATTR_SIZE;
		वापस 0;
	पूर्ण
	rc = ecryptfs_get_lower_file(dentry, inode);
	अगर (rc)
		वापस rc;
	crypt_stat = &ecryptfs_inode_to_निजी(d_inode(dentry))->crypt_stat;
	/* Switch on growing or shrinking file */
	अगर (ia->ia_size > i_size) अणु
		अक्षर zero[] = अणु 0x00 पूर्ण;

		lower_ia->ia_valid &= ~ATTR_SIZE;
		/* Write a single 0 at the last position of the file;
		 * this triggers code that will fill in 0's throughout
		 * the पूर्णांकermediate portion of the previous end of the
		 * file and the new and of the file */
		rc = ecryptfs_ग_लिखो(inode, zero,
				    (ia->ia_size - 1), 1);
	पूर्ण अन्यथा अणु /* ia->ia_size < i_size_पढ़ो(inode) */
		/* We're chopping off all the pages करोwn to the page
		 * in which ia->ia_size is located. Fill in the end of
		 * that page from (ia->ia_size & ~PAGE_MASK) to
		 * PAGE_SIZE with zeros. */
		माप_प्रकार num_zeros = (PAGE_SIZE
				    - (ia->ia_size & ~PAGE_MASK));

		अगर (!(crypt_stat->flags & ECRYPTFS_ENCRYPTED)) अणु
			truncate_setsize(inode, ia->ia_size);
			lower_ia->ia_size = ia->ia_size;
			lower_ia->ia_valid |= ATTR_SIZE;
			जाओ out;
		पूर्ण
		अगर (num_zeros) अणु
			अक्षर *zeros_virt;

			zeros_virt = kzalloc(num_zeros, GFP_KERNEL);
			अगर (!zeros_virt) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण
			rc = ecryptfs_ग_लिखो(inode, zeros_virt,
					    ia->ia_size, num_zeros);
			kमुक्त(zeros_virt);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR "Error attempting to zero out "
				       "the remainder of the end page on "
				       "reducing truncate; rc = [%d]\n", rc);
				जाओ out;
			पूर्ण
		पूर्ण
		truncate_setsize(inode, ia->ia_size);
		rc = ecryptfs_ग_लिखो_inode_माप_प्रकारo_metadata(inode);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR	"Problem with "
			       "ecryptfs_write_inode_size_to_metadata; "
			       "rc = [%d]\n", rc);
			जाओ out;
		पूर्ण
		/* We are reducing the size of the ecryptfs file, and need to
		 * know अगर we need to reduce the size of the lower file. */
		lower_size_beक्रमe_truncate =
		    upper_माप_प्रकारo_lower_size(crypt_stat, i_size);
		lower_size_after_truncate =
		    upper_माप_प्रकारo_lower_size(crypt_stat, ia->ia_size);
		अगर (lower_size_after_truncate < lower_size_beक्रमe_truncate) अणु
			lower_ia->ia_size = lower_size_after_truncate;
			lower_ia->ia_valid |= ATTR_SIZE;
		पूर्ण अन्यथा
			lower_ia->ia_valid &= ~ATTR_SIZE;
	पूर्ण
out:
	ecryptfs_put_lower_file(inode);
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_inode_newsize_ok(काष्ठा inode *inode, loff_t offset)
अणु
	काष्ठा ecryptfs_crypt_stat *crypt_stat;
	loff_t lower_oldsize, lower_newsize;

	crypt_stat = &ecryptfs_inode_to_निजी(inode)->crypt_stat;
	lower_oldsize = upper_माप_प्रकारo_lower_size(crypt_stat,
						 i_size_पढ़ो(inode));
	lower_newsize = upper_माप_प्रकारo_lower_size(crypt_stat, offset);
	अगर (lower_newsize > lower_oldsize) अणु
		/*
		 * The eCryptfs inode and the new *lower* size are mixed here
		 * because we may not have the lower i_mutex held and/or it may
		 * not be appropriate to call inode_newsize_ok() with inodes
		 * from other fileप्रणालीs.
		 */
		वापस inode_newsize_ok(inode, lower_newsize);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ecryptfs_truncate
 * @dentry: The ecryptfs layer dentry
 * @new_length: The length to expand the file to
 *
 * Simple function that handles the truncation of an eCryptfs inode and
 * its corresponding lower inode.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक ecryptfs_truncate(काष्ठा dentry *dentry, loff_t new_length)
अणु
	काष्ठा iattr ia = अणु .ia_valid = ATTR_SIZE, .ia_size = new_length पूर्ण;
	काष्ठा iattr lower_ia = अणु .ia_valid = 0 पूर्ण;
	पूर्णांक rc;

	rc = ecryptfs_inode_newsize_ok(d_inode(dentry), new_length);
	अगर (rc)
		वापस rc;

	rc = truncate_upper(dentry, &ia, &lower_ia);
	अगर (!rc && lower_ia.ia_valid & ATTR_SIZE) अणु
		काष्ठा dentry *lower_dentry = ecryptfs_dentry_to_lower(dentry);

		inode_lock(d_inode(lower_dentry));
		rc = notअगरy_change(&init_user_ns, lower_dentry,
				   &lower_ia, शून्य);
		inode_unlock(d_inode(lower_dentry));
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
ecryptfs_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		    पूर्णांक mask)
अणु
	वापस inode_permission(&init_user_ns,
				ecryptfs_inode_to_lower(inode), mask);
पूर्ण

/**
 * ecryptfs_setattr
 * @mnt_userns: user namespace of the target mount
 * @dentry: dentry handle to the inode to modअगरy
 * @ia: Structure with flags of what to change and values
 *
 * Updates the metadata of an inode. If the update is to the size
 * i.e. truncation, then ecryptfs_truncate will handle the size modअगरication
 * of both the ecryptfs inode and the lower inode.
 *
 * All other metadata changes will be passed right to the lower fileप्रणाली,
 * and we will just update our inode to look like the lower.
 */
अटल पूर्णांक ecryptfs_setattr(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry, काष्ठा iattr *ia)
अणु
	पूर्णांक rc = 0;
	काष्ठा dentry *lower_dentry;
	काष्ठा iattr lower_ia;
	काष्ठा inode *inode;
	काष्ठा inode *lower_inode;
	काष्ठा ecryptfs_crypt_stat *crypt_stat;

	crypt_stat = &ecryptfs_inode_to_निजी(d_inode(dentry))->crypt_stat;
	अगर (!(crypt_stat->flags & ECRYPTFS_STRUCT_INITIALIZED)) अणु
		rc = ecryptfs_init_crypt_stat(crypt_stat);
		अगर (rc)
			वापस rc;
	पूर्ण
	inode = d_inode(dentry);
	lower_inode = ecryptfs_inode_to_lower(inode);
	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	mutex_lock(&crypt_stat->cs_mutex);
	अगर (d_is_dir(dentry))
		crypt_stat->flags &= ~(ECRYPTFS_ENCRYPTED);
	अन्यथा अगर (d_is_reg(dentry)
		 && (!(crypt_stat->flags & ECRYPTFS_POLICY_APPLIED)
		     || !(crypt_stat->flags & ECRYPTFS_KEY_VALID))) अणु
		काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat;

		mount_crypt_stat = &ecryptfs_superblock_to_निजी(
			dentry->d_sb)->mount_crypt_stat;
		rc = ecryptfs_get_lower_file(dentry, inode);
		अगर (rc) अणु
			mutex_unlock(&crypt_stat->cs_mutex);
			जाओ out;
		पूर्ण
		rc = ecryptfs_पढ़ो_metadata(dentry);
		ecryptfs_put_lower_file(inode);
		अगर (rc) अणु
			अगर (!(mount_crypt_stat->flags
			      & ECRYPTFS_PLAINTEXT_PASSTHROUGH_ENABLED)) अणु
				rc = -EIO;
				prपूर्णांकk(KERN_WARNING "Either the lower file "
				       "is not in a valid eCryptfs format, "
				       "or the key could not be retrieved. "
				       "Plaintext passthrough mode is not "
				       "enabled; returning -EIO\n");
				mutex_unlock(&crypt_stat->cs_mutex);
				जाओ out;
			पूर्ण
			rc = 0;
			crypt_stat->flags &= ~(ECRYPTFS_I_SIZE_INITIALIZED
					       | ECRYPTFS_ENCRYPTED);
		पूर्ण
	पूर्ण
	mutex_unlock(&crypt_stat->cs_mutex);

	rc = setattr_prepare(&init_user_ns, dentry, ia);
	अगर (rc)
		जाओ out;
	अगर (ia->ia_valid & ATTR_SIZE) अणु
		rc = ecryptfs_inode_newsize_ok(inode, ia->ia_size);
		अगर (rc)
			जाओ out;
	पूर्ण

	स_नकल(&lower_ia, ia, माप(lower_ia));
	अगर (ia->ia_valid & ATTR_खाता)
		lower_ia.ia_file = ecryptfs_file_to_lower(ia->ia_file);
	अगर (ia->ia_valid & ATTR_SIZE) अणु
		rc = truncate_upper(dentry, ia, &lower_ia);
		अगर (rc < 0)
			जाओ out;
	पूर्ण

	/*
	 * mode change is क्रम clearing setuid/setgid bits. Allow lower fs
	 * to पूर्णांकerpret this in its own way.
	 */
	अगर (lower_ia.ia_valid & (ATTR_KILL_SUID | ATTR_KILL_SGID))
		lower_ia.ia_valid &= ~ATTR_MODE;

	inode_lock(d_inode(lower_dentry));
	rc = notअगरy_change(&init_user_ns, lower_dentry, &lower_ia, शून्य);
	inode_unlock(d_inode(lower_dentry));
out:
	fsstack_copy_attr_all(inode, lower_inode);
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_getattr_link(काष्ठा user_namespace *mnt_userns,
				 स्थिर काष्ठा path *path, काष्ठा kstat *stat,
				 u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat;
	पूर्णांक rc = 0;

	mount_crypt_stat = &ecryptfs_superblock_to_निजी(
						dentry->d_sb)->mount_crypt_stat;
	generic_fillattr(&init_user_ns, d_inode(dentry), stat);
	अगर (mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_खाताNAMES) अणु
		अक्षर *target;
		माप_प्रकार tarमाला_लोiz;

		target = ecryptfs_पढ़ोlink_lower(dentry, &tarमाला_लोiz);
		अगर (!IS_ERR(target)) अणु
			kमुक्त(target);
			stat->size = tarमाला_लोiz;
		पूर्ण अन्यथा अणु
			rc = PTR_ERR(target);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_getattr(काष्ठा user_namespace *mnt_userns,
			    स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			    u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा kstat lower_stat;
	पूर्णांक rc;

	rc = vfs_getattr(ecryptfs_dentry_to_lower_path(dentry), &lower_stat,
			 request_mask, flags);
	अगर (!rc) अणु
		fsstack_copy_attr_all(d_inode(dentry),
				      ecryptfs_inode_to_lower(d_inode(dentry)));
		generic_fillattr(&init_user_ns, d_inode(dentry), stat);
		stat->blocks = lower_stat.blocks;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक
ecryptfs_setxattr(काष्ठा dentry *dentry, काष्ठा inode *inode,
		  स्थिर अक्षर *name, स्थिर व्योम *value,
		  माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक rc;
	काष्ठा dentry *lower_dentry;
	काष्ठा inode *lower_inode;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	lower_inode = d_inode(lower_dentry);
	अगर (!(lower_inode->i_opflags & IOP_XATTR)) अणु
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	inode_lock(lower_inode);
	rc = __vfs_setxattr_locked(&init_user_ns, lower_dentry, name, value, size, flags, शून्य);
	inode_unlock(lower_inode);
	अगर (!rc && inode)
		fsstack_copy_attr_all(inode, lower_inode);
out:
	वापस rc;
पूर्ण

sमाप_प्रकार
ecryptfs_getxattr_lower(काष्ठा dentry *lower_dentry, काष्ठा inode *lower_inode,
			स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	पूर्णांक rc;

	अगर (!(lower_inode->i_opflags & IOP_XATTR)) अणु
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	inode_lock(lower_inode);
	rc = __vfs_getxattr(lower_dentry, lower_inode, name, value, size);
	inode_unlock(lower_inode);
out:
	वापस rc;
पूर्ण

अटल sमाप_प्रकार
ecryptfs_getxattr(काष्ठा dentry *dentry, काष्ठा inode *inode,
		  स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	वापस ecryptfs_getxattr_lower(ecryptfs_dentry_to_lower(dentry),
				       ecryptfs_inode_to_lower(inode),
				       name, value, size);
पूर्ण

अटल sमाप_प्रकार
ecryptfs_listxattr(काष्ठा dentry *dentry, अक्षर *list, माप_प्रकार size)
अणु
	पूर्णांक rc = 0;
	काष्ठा dentry *lower_dentry;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	अगर (!d_inode(lower_dentry)->i_op->listxattr) अणु
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	inode_lock(d_inode(lower_dentry));
	rc = d_inode(lower_dentry)->i_op->listxattr(lower_dentry, list, size);
	inode_unlock(d_inode(lower_dentry));
out:
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_हटाओxattr(काष्ठा dentry *dentry, काष्ठा inode *inode,
				स्थिर अक्षर *name)
अणु
	पूर्णांक rc;
	काष्ठा dentry *lower_dentry;
	काष्ठा inode *lower_inode;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	lower_inode = ecryptfs_inode_to_lower(inode);
	अगर (!(lower_inode->i_opflags & IOP_XATTR)) अणु
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	inode_lock(lower_inode);
	rc = __vfs_हटाओxattr(&init_user_ns, lower_dentry, name);
	inode_unlock(lower_inode);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	वापस vfs_fileattr_get(ecryptfs_dentry_to_lower(dentry), fa);
पूर्ण

अटल पूर्णांक ecryptfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
				 काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा dentry *lower_dentry = ecryptfs_dentry_to_lower(dentry);
	पूर्णांक rc;

	rc = vfs_fileattr_set(&init_user_ns, lower_dentry, fa);
	fsstack_copy_attr_all(d_inode(dentry), d_inode(lower_dentry));

	वापस rc;
पूर्ण

स्थिर काष्ठा inode_operations ecryptfs_symlink_iops = अणु
	.get_link = ecryptfs_get_link,
	.permission = ecryptfs_permission,
	.setattr = ecryptfs_setattr,
	.getattr = ecryptfs_getattr_link,
	.listxattr = ecryptfs_listxattr,
पूर्ण;

स्थिर काष्ठा inode_operations ecryptfs_dir_iops = अणु
	.create = ecryptfs_create,
	.lookup = ecryptfs_lookup,
	.link = ecryptfs_link,
	.unlink = ecryptfs_unlink,
	.symlink = ecryptfs_symlink,
	.सूची_गढ़ो = ecryptfs_सूची_गढ़ो,
	.सूची_हटाओ = ecryptfs_सूची_हटाओ,
	.mknod = ecryptfs_mknod,
	.नाम = ecryptfs_नाम,
	.permission = ecryptfs_permission,
	.setattr = ecryptfs_setattr,
	.listxattr = ecryptfs_listxattr,
	.fileattr_get = ecryptfs_fileattr_get,
	.fileattr_set = ecryptfs_fileattr_set,
पूर्ण;

स्थिर काष्ठा inode_operations ecryptfs_मुख्य_iops = अणु
	.permission = ecryptfs_permission,
	.setattr = ecryptfs_setattr,
	.getattr = ecryptfs_getattr,
	.listxattr = ecryptfs_listxattr,
	.fileattr_get = ecryptfs_fileattr_get,
	.fileattr_set = ecryptfs_fileattr_set,
पूर्ण;

अटल पूर्णांक ecryptfs_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			      काष्ठा dentry *dentry, काष्ठा inode *inode,
			      स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस ecryptfs_getxattr(dentry, inode, name, buffer, size);
पूर्ण

अटल पूर्णांक ecryptfs_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			      काष्ठा user_namespace *mnt_userns,
			      काष्ठा dentry *dentry, काष्ठा inode *inode,
			      स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size,
			      पूर्णांक flags)
अणु
	अगर (value)
		वापस ecryptfs_setxattr(dentry, inode, name, value, size, flags);
	अन्यथा अणु
		BUG_ON(flags != XATTR_REPLACE);
		वापस ecryptfs_हटाओxattr(dentry, inode, name);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा xattr_handler ecryptfs_xattr_handler = अणु
	.prefix = "",  /* match anything */
	.get = ecryptfs_xattr_get,
	.set = ecryptfs_xattr_set,
पूर्ण;

स्थिर काष्ठा xattr_handler *ecryptfs_xattr_handlers[] = अणु
	&ecryptfs_xattr_handler,
	शून्य
पूर्ण;
