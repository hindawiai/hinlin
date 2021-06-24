<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat, Inc.
 * Copyright (C) 2012 Jeremy Kerr <jeremy.kerr@canonical.com>
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/efi.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ucs2_माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/magic.h>

#समावेश "internal.h"

LIST_HEAD(efivarfs_list);

अटल व्योम efivarfs_evict_inode(काष्ठा inode *inode)
अणु
	clear_inode(inode);
पूर्ण

अटल स्थिर काष्ठा super_operations efivarfs_ops = अणु
	.statfs = simple_statfs,
	.drop_inode = generic_delete_inode,
	.evict_inode = efivarfs_evict_inode,
पूर्ण;

/*
 * Compare two efivarfs file names.
 *
 * An efivarfs filename is composed of two parts,
 *
 *	1. A हाल-sensitive variable name
 *	2. A हाल-insensitive GUID
 *
 * So we need to perक्रमm a हाल-sensitive match on part 1 and a
 * हाल-insensitive match on part 2.
 */
अटल पूर्णांक efivarfs_d_compare(स्थिर काष्ठा dentry *dentry,
			      अचिन्हित पूर्णांक len, स्थिर अक्षर *str,
			      स्थिर काष्ठा qstr *name)
अणु
	पूर्णांक guid = len - EFI_VARIABLE_GUID_LEN;

	अगर (name->len != len)
		वापस 1;

	/* Case-sensitive compare क्रम the variable name */
	अगर (स_भेद(str, name->name, guid))
		वापस 1;

	/* Case-insensitive compare क्रम the GUID */
	वापस strnहालcmp(name->name + guid, str + guid, EFI_VARIABLE_GUID_LEN);
पूर्ण

अटल पूर्णांक efivarfs_d_hash(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	अचिन्हित दीर्घ hash = init_name_hash(dentry);
	स्थिर अचिन्हित अक्षर *s = qstr->name;
	अचिन्हित पूर्णांक len = qstr->len;

	अगर (!efivarfs_valid_name(s, len))
		वापस -EINVAL;

	जबतक (len-- > EFI_VARIABLE_GUID_LEN)
		hash = partial_name_hash(*s++, hash);

	/* GUID is हाल-insensitive. */
	जबतक (len--)
		hash = partial_name_hash(छोटे(*s++), hash);

	qstr->hash = end_name_hash(hash);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dentry_operations efivarfs_d_ops = अणु
	.d_compare = efivarfs_d_compare,
	.d_hash = efivarfs_d_hash,
	.d_delete = always_delete_dentry,
पूर्ण;

अटल काष्ठा dentry *efivarfs_alloc_dentry(काष्ठा dentry *parent, अक्षर *name)
अणु
	काष्ठा dentry *d;
	काष्ठा qstr q;
	पूर्णांक err;

	q.name = name;
	q.len = म_माप(name);

	err = efivarfs_d_hash(parent, &q);
	अगर (err)
		वापस ERR_PTR(err);

	d = d_alloc(parent, &q);
	अगर (d)
		वापस d;

	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक efivarfs_callback(efi_अक्षर16_t *name16, efi_guid_t venकरोr,
			     अचिन्हित दीर्घ name_size, व्योम *data)
अणु
	काष्ठा super_block *sb = (काष्ठा super_block *)data;
	काष्ठा efivar_entry *entry;
	काष्ठा inode *inode = शून्य;
	काष्ठा dentry *dentry, *root = sb->s_root;
	अचिन्हित दीर्घ size = 0;
	अक्षर *name;
	पूर्णांक len;
	पूर्णांक err = -ENOMEM;
	bool is_removable = false;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस err;

	स_नकल(entry->var.VariableName, name16, name_size);
	स_नकल(&(entry->var.VenकरोrGuid), &venकरोr, माप(efi_guid_t));

	len = ucs2_utf8size(entry->var.VariableName);

	/* name, plus '-', plus GUID, plus NUL*/
	name = kदो_स्मृति(len + 1 + EFI_VARIABLE_GUID_LEN + 1, GFP_KERNEL);
	अगर (!name)
		जाओ fail;

	ucs2_as_utf8(name, entry->var.VariableName, len);

	अगर (efivar_variable_is_removable(entry->var.VenकरोrGuid, name, len))
		is_removable = true;

	name[len] = '-';

	efi_guid_to_str(&entry->var.VenकरोrGuid, name + len + 1);

	name[len + EFI_VARIABLE_GUID_LEN+1] = '\0';

	/* replace invalid slashes like kobject_set_name_vargs करोes क्रम /sys/firmware/efi/vars. */
	strreplace(name, '/', '!');

	inode = efivarfs_get_inode(sb, d_inode(root), S_IFREG | 0644, 0,
				   is_removable);
	अगर (!inode)
		जाओ fail_name;

	dentry = efivarfs_alloc_dentry(root, name);
	अगर (IS_ERR(dentry)) अणु
		err = PTR_ERR(dentry);
		जाओ fail_inode;
	पूर्ण

	efivar_entry_size(entry, &size);
	err = efivar_entry_add(entry, &efivarfs_list);
	अगर (err)
		जाओ fail_inode;

	/* copied by the above to local storage in the dentry. */
	kमुक्त(name);

	inode_lock(inode);
	inode->i_निजी = entry;
	i_size_ग_लिखो(inode, size + माप(entry->var.Attributes));
	inode_unlock(inode);
	d_add(dentry, inode);

	वापस 0;

fail_inode:
	iput(inode);
fail_name:
	kमुक्त(name);
fail:
	kमुक्त(entry);
	वापस err;
पूर्ण

अटल पूर्णांक efivarfs_destroy(काष्ठा efivar_entry *entry, व्योम *data)
अणु
	पूर्णांक err = efivar_entry_हटाओ(entry);

	अगर (err)
		वापस err;
	kमुक्त(entry);
	वापस 0;
पूर्ण

अटल पूर्णांक efivarfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा dentry *root;
	पूर्णांक err;

	sb->s_maxbytes          = MAX_LFS_खाताSIZE;
	sb->s_blocksize         = PAGE_SIZE;
	sb->s_blocksize_bits    = PAGE_SHIFT;
	sb->s_magic             = EFIVARFS_MAGIC;
	sb->s_op                = &efivarfs_ops;
	sb->s_d_op		= &efivarfs_d_ops;
	sb->s_समय_gran         = 1;

	अगर (!efivar_supports_ग_लिखोs())
		sb->s_flags |= SB_RDONLY;

	inode = efivarfs_get_inode(sb, शून्य, S_IFसूची | 0755, 0, true);
	अगर (!inode)
		वापस -ENOMEM;
	inode->i_op = &efivarfs_dir_inode_operations;

	root = d_make_root(inode);
	sb->s_root = root;
	अगर (!root)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&efivarfs_list);

	err = efivar_init(efivarfs_callback, (व्योम *)sb, true, &efivarfs_list);
	अगर (err)
		__efivar_entry_iter(efivarfs_destroy, &efivarfs_list, शून्य, शून्य);

	वापस err;
पूर्ण

अटल पूर्णांक efivarfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, efivarfs_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations efivarfs_context_ops = अणु
	.get_tree	= efivarfs_get_tree,
पूर्ण;

अटल पूर्णांक efivarfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &efivarfs_context_ops;
	वापस 0;
पूर्ण

अटल व्योम efivarfs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	समाप्त_litter_super(sb);

	/* Remove all entries and destroy */
	__efivar_entry_iter(efivarfs_destroy, &efivarfs_list, शून्य, शून्य);
पूर्ण

अटल काष्ठा file_प्रणाली_type efivarfs_type = अणु
	.owner   = THIS_MODULE,
	.name    = "efivarfs",
	.init_fs_context = efivarfs_init_fs_context,
	.समाप्त_sb = efivarfs_समाप्त_sb,
पूर्ण;

अटल __init पूर्णांक efivarfs_init(व्योम)
अणु
	अगर (!efivars_kobject())
		वापस -ENODEV;

	वापस रेजिस्टर_fileप्रणाली(&efivarfs_type);
पूर्ण

अटल __निकास व्योम efivarfs_निकास(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&efivarfs_type);
पूर्ण

MODULE_AUTHOR("Matthew Garrett, Jeremy Kerr");
MODULE_DESCRIPTION("EFI Variable Filesystem");
MODULE_LICENSE("GPL");
MODULE_ALIAS_FS("efivarfs");

module_init(efivarfs_init);
module_निकास(efivarfs_निकास);
