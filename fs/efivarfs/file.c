<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat, Inc.
 * Copyright (C) 2012 Jeremy Kerr <jeremy.kerr@canonical.com>
 */

#समावेश <linux/efi.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/mount.h>

#समावेश "internal.h"

अटल sमाप_प्रकार efivarfs_file_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *userbuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा efivar_entry *var = file->निजी_data;
	व्योम *data;
	u32 attributes;
	काष्ठा inode *inode = file->f_mapping->host;
	अचिन्हित दीर्घ datasize = count - माप(attributes);
	sमाप_प्रकार bytes;
	bool set = false;

	अगर (count < माप(attributes))
		वापस -EINVAL;

	अगर (copy_from_user(&attributes, userbuf, माप(attributes)))
		वापस -EFAULT;

	अगर (attributes & ~(EFI_VARIABLE_MASK))
		वापस -EINVAL;

	data = memdup_user(userbuf + माप(attributes), datasize);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	bytes = efivar_entry_set_get_size(var, attributes, &datasize,
					  data, &set);
	अगर (!set && bytes) अणु
		अगर (bytes == -ENOENT)
			bytes = -EIO;
		जाओ out;
	पूर्ण

	अगर (bytes == -ENOENT) अणु
		drop_nlink(inode);
		d_delete(file->f_path.dentry);
		dput(file->f_path.dentry);
	पूर्ण अन्यथा अणु
		inode_lock(inode);
		i_size_ग_लिखो(inode, datasize + माप(attributes));
		inode->i_mसमय = current_समय(inode);
		inode_unlock(inode);
	पूर्ण

	bytes = count;

out:
	kमुक्त(data);

	वापस bytes;
पूर्ण

अटल sमाप_प्रकार efivarfs_file_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा efivar_entry *var = file->निजी_data;
	अचिन्हित दीर्घ datasize = 0;
	u32 attributes;
	व्योम *data;
	sमाप_प्रकार size = 0;
	पूर्णांक err;

	जबतक (!__ratelimit(&file->f_cred->user->ratelimit))
		msleep(50);

	err = efivar_entry_size(var, &datasize);

	/*
	 * efivarfs represents uncommitted variables with
	 * zero-length files. Reading them should वापस खातापूर्ण.
	 */
	अगर (err == -ENOENT)
		वापस 0;
	अन्यथा अगर (err)
		वापस err;

	data = kदो_स्मृति(datasize + माप(attributes), GFP_KERNEL);

	अगर (!data)
		वापस -ENOMEM;

	size = efivar_entry_get(var, &attributes, &datasize,
				data + माप(attributes));
	अगर (size)
		जाओ out_मुक्त;

	स_नकल(data, &attributes, माप(attributes));
	size = simple_पढ़ो_from_buffer(userbuf, count, ppos,
				       data, datasize + माप(attributes));
out_मुक्त:
	kमुक्त(data);

	वापस size;
पूर्ण

स्थिर काष्ठा file_operations efivarfs_file_operations = अणु
	.खोलो	= simple_खोलो,
	.पढ़ो	= efivarfs_file_पढ़ो,
	.ग_लिखो	= efivarfs_file_ग_लिखो,
	.llseek	= no_llseek,
पूर्ण;
