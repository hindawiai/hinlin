<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext2/acl.c
 *
 * Copyright (C) 2001-2003 Andreas Gruenbacher, <agruen@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश "ext2.h"
#समावेश "xattr.h"
#समावेश "acl.h"

/*
 * Convert from fileप्रणाली to in-memory representation.
 */
अटल काष्ठा posix_acl *
ext2_acl_from_disk(स्थिर व्योम *value, माप_प्रकार size)
अणु
	स्थिर अक्षर *end = (अक्षर *)value + size;
	पूर्णांक n, count;
	काष्ठा posix_acl *acl;

	अगर (!value)
		वापस शून्य;
	अगर (size < माप(ext2_acl_header))
		 वापस ERR_PTR(-EINVAL);
	अगर (((ext2_acl_header *)value)->a_version !=
	    cpu_to_le32(EXT2_ACL_VERSION))
		वापस ERR_PTR(-EINVAL);
	value = (अक्षर *)value + माप(ext2_acl_header);
	count = ext2_acl_count(size);
	अगर (count < 0)
		वापस ERR_PTR(-EINVAL);
	अगर (count == 0)
		वापस शून्य;
	acl = posix_acl_alloc(count, GFP_KERNEL);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);
	क्रम (n=0; n < count; n++) अणु
		ext2_acl_entry *entry =
			(ext2_acl_entry *)value;
		अगर ((अक्षर *)value + माप(ext2_acl_entry_लघु) > end)
			जाओ fail;
		acl->a_entries[n].e_tag  = le16_to_cpu(entry->e_tag);
		acl->a_entries[n].e_perm = le16_to_cpu(entry->e_perm);
		चयन(acl->a_entries[n].e_tag) अणु
			हाल ACL_USER_OBJ:
			हाल ACL_GROUP_OBJ:
			हाल ACL_MASK:
			हाल ACL_OTHER:
				value = (अक्षर *)value +
					माप(ext2_acl_entry_लघु);
				अवरोध;

			हाल ACL_USER:
				value = (अक्षर *)value + माप(ext2_acl_entry);
				अगर ((अक्षर *)value > end)
					जाओ fail;
				acl->a_entries[n].e_uid =
					make_kuid(&init_user_ns,
						  le32_to_cpu(entry->e_id));
				अवरोध;
			हाल ACL_GROUP:
				value = (अक्षर *)value + माप(ext2_acl_entry);
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
अटल व्योम *
ext2_acl_to_disk(स्थिर काष्ठा posix_acl *acl, माप_प्रकार *size)
अणु
	ext2_acl_header *ext_acl;
	अक्षर *e;
	माप_प्रकार n;

	*size = ext2_acl_size(acl->a_count);
	ext_acl = kदो_स्मृति(माप(ext2_acl_header) + acl->a_count *
			माप(ext2_acl_entry), GFP_KERNEL);
	अगर (!ext_acl)
		वापस ERR_PTR(-ENOMEM);
	ext_acl->a_version = cpu_to_le32(EXT2_ACL_VERSION);
	e = (अक्षर *)ext_acl + माप(ext2_acl_header);
	क्रम (n=0; n < acl->a_count; n++) अणु
		स्थिर काष्ठा posix_acl_entry *acl_e = &acl->a_entries[n];
		ext2_acl_entry *entry = (ext2_acl_entry *)e;
		entry->e_tag  = cpu_to_le16(acl_e->e_tag);
		entry->e_perm = cpu_to_le16(acl_e->e_perm);
		चयन(acl_e->e_tag) अणु
			हाल ACL_USER:
				entry->e_id = cpu_to_le32(
					from_kuid(&init_user_ns, acl_e->e_uid));
				e += माप(ext2_acl_entry);
				अवरोध;
			हाल ACL_GROUP:
				entry->e_id = cpu_to_le32(
					from_kgid(&init_user_ns, acl_e->e_gid));
				e += माप(ext2_acl_entry);
				अवरोध;

			हाल ACL_USER_OBJ:
			हाल ACL_GROUP_OBJ:
			हाल ACL_MASK:
			हाल ACL_OTHER:
				e += माप(ext2_acl_entry_लघु);
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
 * inode->i_mutex: करोn't care
 */
काष्ठा posix_acl *
ext2_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	पूर्णांक name_index;
	अक्षर *value = शून्य;
	काष्ठा posix_acl *acl;
	पूर्णांक retval;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name_index = EXT2_XATTR_INDEX_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		name_index = EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	retval = ext2_xattr_get(inode, name_index, "", शून्य, 0);
	अगर (retval > 0) अणु
		value = kदो_स्मृति(retval, GFP_KERNEL);
		अगर (!value)
			वापस ERR_PTR(-ENOMEM);
		retval = ext2_xattr_get(inode, name_index, "", value, retval);
	पूर्ण
	अगर (retval > 0)
		acl = ext2_acl_from_disk(value, retval);
	अन्यथा अगर (retval == -ENODATA || retval == -ENOSYS)
		acl = शून्य;
	अन्यथा
		acl = ERR_PTR(retval);
	kमुक्त(value);

	वापस acl;
पूर्ण

अटल पूर्णांक
__ext2_set_acl(काष्ठा inode *inode, काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक name_index;
	व्योम *value = शून्य;
	माप_प्रकार size = 0;
	पूर्णांक error;

	चयन(type) अणु
		हाल ACL_TYPE_ACCESS:
			name_index = EXT2_XATTR_INDEX_POSIX_ACL_ACCESS;
			अवरोध;

		हाल ACL_TYPE_DEFAULT:
			name_index = EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT;
			अगर (!S_ISसूची(inode->i_mode))
				वापस acl ? -EACCES : 0;
			अवरोध;

		शेष:
			वापस -EINVAL;
	पूर्ण
 	अगर (acl) अणु
		value = ext2_acl_to_disk(acl, &size);
		अगर (IS_ERR(value))
			वापस (पूर्णांक)PTR_ERR(value);
	पूर्ण

	error = ext2_xattr_set(inode, name_index, "", value, size, 0);

	kमुक्त(value);
	अगर (!error)
		set_cached_acl(inode, type, acl);
	वापस error;
पूर्ण

/*
 * inode->i_mutex: करोwn
 */
पूर्णांक
ext2_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
	     काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक error;
	पूर्णांक update_mode = 0;
	umode_t mode = inode->i_mode;

	अगर (type == ACL_TYPE_ACCESS && acl) अणु
		error = posix_acl_update_mode(&init_user_ns, inode, &mode,
					      &acl);
		अगर (error)
			वापस error;
		update_mode = 1;
	पूर्ण
	error = __ext2_set_acl(inode, acl, type);
	अगर (!error && update_mode) अणु
		inode->i_mode = mode;
		inode->i_स_समय = current_समय(inode);
		mark_inode_dirty(inode);
	पूर्ण
	वापस error;
पूर्ण

/*
 * Initialize the ACLs of a new inode. Called from ext2_new_inode.
 *
 * dir->i_mutex: करोwn
 * inode->i_mutex: up (access to inode is still exclusive)
 */
पूर्णांक
ext2_init_acl(काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	पूर्णांक error;

	error = posix_acl_create(dir, &inode->i_mode, &शेष_acl, &acl);
	अगर (error)
		वापस error;

	अगर (शेष_acl) अणु
		error = __ext2_set_acl(inode, शेष_acl, ACL_TYPE_DEFAULT);
		posix_acl_release(शेष_acl);
	पूर्ण अन्यथा अणु
		inode->i_शेष_acl = शून्य;
	पूर्ण
	अगर (acl) अणु
		अगर (!error)
			error = __ext2_set_acl(inode, acl, ACL_TYPE_ACCESS);
		posix_acl_release(acl);
	पूर्ण अन्यथा अणु
		inode->i_acl = शून्य;
	पूर्ण
	वापस error;
पूर्ण
