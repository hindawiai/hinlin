<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat, Inc.
 * Copyright (C) 2012 Jeremy Kerr <jeremy.kerr@canonical.com>
 */

#समावेश <linux/efi.h>
#समावेश <linux/fs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kmemleak.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>
#समावेश <linux/fileattr.h>

#समावेश "internal.h"

अटल स्थिर काष्ठा inode_operations efivarfs_file_inode_operations;

काष्ठा inode *efivarfs_get_inode(काष्ठा super_block *sb,
				स्थिर काष्ठा inode *dir, पूर्णांक mode,
				dev_t dev, bool is_removable)
अणु
	काष्ठा inode *inode = new_inode(sb);

	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode->i_mode = mode;
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		inode->i_flags = is_removable ? 0 : S_IMMUTABLE;
		चयन (mode & S_IFMT) अणु
		हाल S_IFREG:
			inode->i_op = &efivarfs_file_inode_operations;
			inode->i_fop = &efivarfs_file_operations;
			अवरोध;
		हाल S_IFसूची:
			inode->i_op = &efivarfs_dir_inode_operations;
			inode->i_fop = &simple_dir_operations;
			inc_nlink(inode);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस inode;
पूर्ण

/*
 * Return true अगर 'str' is a valid efivarfs filename of the क्रमm,
 *
 *	VariableName-12345678-1234-1234-1234-1234567891bc
 */
bool efivarfs_valid_name(स्थिर अक्षर *str, पूर्णांक len)
अणु
	स्थिर अक्षर *s = str + len - EFI_VARIABLE_GUID_LEN;

	/*
	 * We need a GUID, plus at least one letter क्रम the variable name,
	 * plus the '-' separator
	 */
	अगर (len < EFI_VARIABLE_GUID_LEN + 2)
		वापस false;

	/* GUID must be preceded by a '-' */
	अगर (*(s - 1) != '-')
		वापस false;

	/*
	 * Validate that 's' is of the correct क्रमmat, e.g.
	 *
	 *	12345678-1234-1234-1234-123456789abc
	 */
	वापस uuid_is_valid(s);
पूर्ण

अटल पूर्णांक efivarfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			   काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा efivar_entry *var;
	पूर्णांक namelen, i = 0, err = 0;
	bool is_removable = false;

	अगर (!efivarfs_valid_name(dentry->d_name.name, dentry->d_name.len))
		वापस -EINVAL;

	var = kzalloc(माप(काष्ठा efivar_entry), GFP_KERNEL);
	अगर (!var)
		वापस -ENOMEM;

	/* length of the variable name itself: हटाओ GUID and separator */
	namelen = dentry->d_name.len - EFI_VARIABLE_GUID_LEN - 1;

	err = guid_parse(dentry->d_name.name + namelen + 1, &var->var.VenकरोrGuid);
	अगर (err)
		जाओ out;

	अगर (efivar_variable_is_removable(var->var.VenकरोrGuid,
					 dentry->d_name.name, namelen))
		is_removable = true;

	inode = efivarfs_get_inode(dir->i_sb, dir, mode, 0, is_removable);
	अगर (!inode) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < namelen; i++)
		var->var.VariableName[i] = dentry->d_name.name[i];

	var->var.VariableName[i] = '\0';

	inode->i_निजी = var;
	kmemleak_ignore(var);

	err = efivar_entry_add(var, &efivarfs_list);
	अगर (err)
		जाओ out;

	d_instantiate(dentry, inode);
	dget(dentry);
out:
	अगर (err) अणु
		kमुक्त(var);
		अगर (inode)
			iput(inode);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक efivarfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा efivar_entry *var = d_inode(dentry)->i_निजी;

	अगर (efivar_entry_delete(var))
		वापस -EINVAL;

	drop_nlink(d_inode(dentry));
	dput(dentry);
	वापस 0;
पूर्ण;

स्थिर काष्ठा inode_operations efivarfs_dir_inode_operations = अणु
	.lookup = simple_lookup,
	.unlink = efivarfs_unlink,
	.create = efivarfs_create,
पूर्ण;

अटल पूर्णांक
efivarfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	अचिन्हित पूर्णांक i_flags;
	अचिन्हित पूर्णांक flags = 0;

	i_flags = d_inode(dentry)->i_flags;
	अगर (i_flags & S_IMMUTABLE)
		flags |= FS_IMMUTABLE_FL;

	fileattr_fill_flags(fa, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
efivarfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
		      काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	अचिन्हित पूर्णांक i_flags = 0;

	अगर (fileattr_has_fsx(fa))
		वापस -EOPNOTSUPP;

	अगर (fa->flags & ~FS_IMMUTABLE_FL)
		वापस -EOPNOTSUPP;

	अगर (fa->flags & FS_IMMUTABLE_FL)
		i_flags |= S_IMMUTABLE;

	inode_set_flags(d_inode(dentry), i_flags, S_IMMUTABLE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations efivarfs_file_inode_operations = अणु
	.fileattr_get = efivarfs_fileattr_get,
	.fileattr_set = efivarfs_fileattr_set,
पूर्ण;
