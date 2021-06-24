<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/crypto/hooks.c
 *
 * Encryption hooks क्रम higher-level fileप्रणाली operations.
 */

#समावेश <linux/key.h>

#समावेश "fscrypt_private.h"

/**
 * fscrypt_file_खोलो() - prepare to खोलो a possibly-encrypted regular file
 * @inode: the inode being खोलोed
 * @filp: the काष्ठा file being set up
 *
 * Currently, an encrypted regular file can only be खोलोed अगर its encryption key
 * is available; access to the raw encrypted contents is not supported.
 * Thereक्रमe, we first set up the inode's encryption key (अगर not alपढ़ोy करोne)
 * and वापस an error अगर it's unavailable.
 *
 * We also verअगरy that अगर the parent directory (from the path via which the file
 * is being खोलोed) is encrypted, then the inode being खोलोed uses the same
 * encryption policy.  This is needed as part of the enक्रमcement that all files
 * in an encrypted directory tree use the same encryption policy, as a
 * protection against certain types of offline attacks.  Note that this check is
 * needed even when खोलोing an *unencrypted* file, since it's क्रमbidden to have
 * an unencrypted file in an encrypted directory.
 *
 * Return: 0 on success, -ENOKEY अगर the key is missing, or another -त्रुटि_सं code
 */
पूर्णांक fscrypt_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक err;
	काष्ठा dentry *dir;

	err = fscrypt_require_key(inode);
	अगर (err)
		वापस err;

	dir = dget_parent(file_dentry(filp));
	अगर (IS_ENCRYPTED(d_inode(dir)) &&
	    !fscrypt_has_permitted_context(d_inode(dir), inode)) अणु
		fscrypt_warn(inode,
			     "Inconsistent encryption context (parent directory: %lu)",
			     d_inode(dir)->i_ino);
		err = -EPERM;
	पूर्ण
	dput(dir);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_file_खोलो);

पूर्णांक __fscrypt_prepare_link(काष्ठा inode *inode, काष्ठा inode *dir,
			   काष्ठा dentry *dentry)
अणु
	अगर (fscrypt_is_nokey_name(dentry))
		वापस -ENOKEY;
	/*
	 * We करोn't need to separately check that the directory inode's key is
	 * available, as it's implied by the dentry not being a no-key name.
	 */

	अगर (!fscrypt_has_permitted_context(dir, inode))
		वापस -EXDEV;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__fscrypt_prepare_link);

पूर्णांक __fscrypt_prepare_नाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			     काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			     अचिन्हित पूर्णांक flags)
अणु
	अगर (fscrypt_is_nokey_name(old_dentry) ||
	    fscrypt_is_nokey_name(new_dentry))
		वापस -ENOKEY;
	/*
	 * We करोn't need to separately check that the directory inodes' keys are
	 * available, as it's implied by the dentries not being no-key names.
	 */

	अगर (old_dir != new_dir) अणु
		अगर (IS_ENCRYPTED(new_dir) &&
		    !fscrypt_has_permitted_context(new_dir,
						   d_inode(old_dentry)))
			वापस -EXDEV;

		अगर ((flags & RENAME_EXCHANGE) &&
		    IS_ENCRYPTED(old_dir) &&
		    !fscrypt_has_permitted_context(old_dir,
						   d_inode(new_dentry)))
			वापस -EXDEV;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__fscrypt_prepare_नाम);

पूर्णांक __fscrypt_prepare_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
			     काष्ठा fscrypt_name *fname)
अणु
	पूर्णांक err = fscrypt_setup_filename(dir, &dentry->d_name, 1, fname);

	अगर (err && err != -ENOENT)
		वापस err;

	अगर (fname->is_nokey_name) अणु
		spin_lock(&dentry->d_lock);
		dentry->d_flags |= DCACHE_NOKEY_NAME;
		spin_unlock(&dentry->d_lock);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__fscrypt_prepare_lookup);

पूर्णांक __fscrypt_prepare_सूची_पढ़ो(काष्ठा inode *dir)
अणु
	वापस fscrypt_get_encryption_info(dir, true);
पूर्ण
EXPORT_SYMBOL_GPL(__fscrypt_prepare_सूची_पढ़ो);

पूर्णांक __fscrypt_prepare_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	अगर (attr->ia_valid & ATTR_SIZE)
		वापस fscrypt_require_key(d_inode(dentry));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__fscrypt_prepare_setattr);

/**
 * fscrypt_prepare_setflags() - prepare to change flags with FS_IOC_SETFLAGS
 * @inode: the inode on which flags are being changed
 * @oldflags: the old flags
 * @flags: the new flags
 *
 * The caller should be holding i_rwsem क्रम ग_लिखो.
 *
 * Return: 0 on success; -त्रुटि_सं अगर the flags change isn't allowed or अगर
 *	   another error occurs.
 */
पूर्णांक fscrypt_prepare_setflags(काष्ठा inode *inode,
			     अचिन्हित पूर्णांक oldflags, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fscrypt_info *ci;
	काष्ठा key *key;
	काष्ठा fscrypt_master_key *mk;
	पूर्णांक err;

	/*
	 * When the CASEFOLD flag is set on an encrypted directory, we must
	 * derive the secret key needed क्रम the dirhash.  This is only possible
	 * अगर the directory uses a v2 encryption policy.
	 */
	अगर (IS_ENCRYPTED(inode) && (flags & ~oldflags & FS_CASEFOLD_FL)) अणु
		err = fscrypt_require_key(inode);
		अगर (err)
			वापस err;
		ci = inode->i_crypt_info;
		अगर (ci->ci_policy.version != FSCRYPT_POLICY_V2)
			वापस -EINVAL;
		key = ci->ci_master_key;
		mk = key->payload.data[0];
		करोwn_पढ़ो(&key->sem);
		अगर (is_master_key_secret_present(&mk->mk_secret))
			err = fscrypt_derive_dirhash_key(ci, mk);
		अन्यथा
			err = -ENOKEY;
		up_पढ़ो(&key->sem);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * fscrypt_prepare_symlink() - prepare to create a possibly-encrypted symlink
 * @dir: directory in which the symlink is being created
 * @target: plaपूर्णांकext symlink target
 * @len: length of @target excluding null terminator
 * @max_len: space the fileप्रणाली has available to store the symlink target
 * @disk_link: (out) the on-disk symlink target being prepared
 *
 * This function computes the size the symlink target will require on-disk,
 * stores it in @disk_link->len, and validates it against @max_len.  An
 * encrypted symlink may be दीर्घer than the original.
 *
 * Additionally, @disk_link->name is set to @target अगर the symlink will be
 * unencrypted, but left शून्य अगर the symlink will be encrypted.  For encrypted
 * symlinks, the fileप्रणाली must call fscrypt_encrypt_symlink() to create the
 * on-disk target later.  (The reason क्रम the two-step process is that some
 * fileप्रणालीs need to know the size of the symlink target beक्रमe creating the
 * inode, e.g. to determine whether it will be a "fast" or "slow" symlink.)
 *
 * Return: 0 on success, -ENAMETOOLONG अगर the symlink target is too दीर्घ,
 * -ENOKEY अगर the encryption key is missing, or another -त्रुटि_सं code अगर a problem
 * occurred जबतक setting up the encryption key.
 */
पूर्णांक fscrypt_prepare_symlink(काष्ठा inode *dir, स्थिर अक्षर *target,
			    अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक max_len,
			    काष्ठा fscrypt_str *disk_link)
अणु
	स्थिर जोड़ fscrypt_policy *policy;

	/*
	 * To calculate the size of the encrypted symlink target we need to know
	 * the amount of NUL padding, which is determined by the flags set in
	 * the encryption policy which will be inherited from the directory.
	 */
	policy = fscrypt_policy_to_inherit(dir);
	अगर (policy == शून्य) अणु
		/* Not encrypted */
		disk_link->name = (अचिन्हित अक्षर *)target;
		disk_link->len = len + 1;
		अगर (disk_link->len > max_len)
			वापस -ENAMETOOLONG;
		वापस 0;
	पूर्ण
	अगर (IS_ERR(policy))
		वापस PTR_ERR(policy);

	/*
	 * Calculate the size of the encrypted symlink and verअगरy it won't
	 * exceed max_len.  Note that क्रम historical reasons, encrypted symlink
	 * tarमाला_लो are prefixed with the ciphertext length, despite this
	 * actually being redundant with i_size.  This decreases by 2 bytes the
	 * दीर्घest symlink target we can accept.
	 *
	 * We could recover 1 byte by not counting a null terminator, but
	 * counting it (even though it is meaningless क्रम ciphertext) is simpler
	 * क्रम now since fileप्रणालीs will assume it is there and subtract it.
	 */
	अगर (!fscrypt_fname_encrypted_size(policy, len,
					  max_len - माप(काष्ठा fscrypt_symlink_data),
					  &disk_link->len))
		वापस -ENAMETOOLONG;
	disk_link->len += माप(काष्ठा fscrypt_symlink_data);

	disk_link->name = शून्य;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_prepare_symlink);

पूर्णांक __fscrypt_encrypt_symlink(काष्ठा inode *inode, स्थिर अक्षर *target,
			      अचिन्हित पूर्णांक len, काष्ठा fscrypt_str *disk_link)
अणु
	पूर्णांक err;
	काष्ठा qstr iname = QSTR_INIT(target, len);
	काष्ठा fscrypt_symlink_data *sd;
	अचिन्हित पूर्णांक ciphertext_len;

	/*
	 * fscrypt_prepare_new_inode() should have alपढ़ोy set up the new
	 * symlink inode's encryption key.  We don't रुको until now to करो it,
	 * since we may be in a fileप्रणाली transaction now.
	 */
	अगर (WARN_ON_ONCE(!fscrypt_has_encryption_key(inode)))
		वापस -ENOKEY;

	अगर (disk_link->name) अणु
		/* fileप्रणाली-provided buffer */
		sd = (काष्ठा fscrypt_symlink_data *)disk_link->name;
	पूर्ण अन्यथा अणु
		sd = kदो_स्मृति(disk_link->len, GFP_NOFS);
		अगर (!sd)
			वापस -ENOMEM;
	पूर्ण
	ciphertext_len = disk_link->len - माप(*sd);
	sd->len = cpu_to_le16(ciphertext_len);

	err = fscrypt_fname_encrypt(inode, &iname, sd->encrypted_path,
				    ciphertext_len);
	अगर (err)
		जाओ err_मुक्त_sd;

	/*
	 * Null-terminating the ciphertext करोesn't make sense, but we still
	 * count the null terminator in the length, so we might as well
	 * initialize it just in हाल the fileप्रणाली ग_लिखोs it out.
	 */
	sd->encrypted_path[ciphertext_len] = '\0';

	/* Cache the plaपूर्णांकext symlink target क्रम later use by get_link() */
	err = -ENOMEM;
	inode->i_link = kmemdup(target, len + 1, GFP_NOFS);
	अगर (!inode->i_link)
		जाओ err_मुक्त_sd;

	अगर (!disk_link->name)
		disk_link->name = (अचिन्हित अक्षर *)sd;
	वापस 0;

err_मुक्त_sd:
	अगर (!disk_link->name)
		kमुक्त(sd);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__fscrypt_encrypt_symlink);

/**
 * fscrypt_get_symlink() - get the target of an encrypted symlink
 * @inode: the symlink inode
 * @caddr: the on-disk contents of the symlink
 * @max_size: size of @caddr buffer
 * @करोne: अगर successful, will be set up to मुक्त the वापसed target अगर needed
 *
 * If the symlink's encryption key is available, we decrypt its target.
 * Otherwise, we encode its target क्रम presentation.
 *
 * This may sleep, so the fileप्रणाली must have dropped out of RCU mode alपढ़ोy.
 *
 * Return: the presentable symlink target or an ERR_PTR()
 */
स्थिर अक्षर *fscrypt_get_symlink(काष्ठा inode *inode, स्थिर व्योम *caddr,
				अचिन्हित पूर्णांक max_size,
				काष्ठा delayed_call *करोne)
अणु
	स्थिर काष्ठा fscrypt_symlink_data *sd;
	काष्ठा fscrypt_str cstr, pstr;
	bool has_key;
	पूर्णांक err;

	/* This is क्रम encrypted symlinks only */
	अगर (WARN_ON(!IS_ENCRYPTED(inode)))
		वापस ERR_PTR(-EINVAL);

	/* If the decrypted target is alपढ़ोy cached, just वापस it. */
	pstr.name = READ_ONCE(inode->i_link);
	अगर (pstr.name)
		वापस pstr.name;

	/*
	 * Try to set up the symlink's encryption key, but we can जारी
	 * regardless of whether the key is available or not.
	 */
	err = fscrypt_get_encryption_info(inode, false);
	अगर (err)
		वापस ERR_PTR(err);
	has_key = fscrypt_has_encryption_key(inode);

	/*
	 * For historical reasons, encrypted symlink tarमाला_लो are prefixed with
	 * the ciphertext length, even though this is redundant with i_size.
	 */

	अगर (max_size < माप(*sd))
		वापस ERR_PTR(-EUCLEAN);
	sd = caddr;
	cstr.name = (अचिन्हित अक्षर *)sd->encrypted_path;
	cstr.len = le16_to_cpu(sd->len);

	अगर (cstr.len == 0)
		वापस ERR_PTR(-EUCLEAN);

	अगर (cstr.len + माप(*sd) - 1 > max_size)
		वापस ERR_PTR(-EUCLEAN);

	err = fscrypt_fname_alloc_buffer(cstr.len, &pstr);
	अगर (err)
		वापस ERR_PTR(err);

	err = fscrypt_fname_disk_to_usr(inode, 0, 0, &cstr, &pstr);
	अगर (err)
		जाओ err_kमुक्त;

	err = -EUCLEAN;
	अगर (pstr.name[0] == '\0')
		जाओ err_kमुक्त;

	pstr.name[pstr.len] = '\0';

	/*
	 * Cache decrypted symlink tarमाला_लो in i_link क्रम later use.  Don't cache
	 * symlink tarमाला_लो encoded without the key, since those become outdated
	 * once the key is added.  This pairs with the READ_ONCE() above and in
	 * the VFS path lookup code.
	 */
	अगर (!has_key ||
	    cmpxchg_release(&inode->i_link, शून्य, pstr.name) != शून्य)
		set_delayed_call(करोne, kमुक्त_link, pstr.name);

	वापस pstr.name;

err_kमुक्त:
	kमुक्त(pstr.name);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_get_symlink);
