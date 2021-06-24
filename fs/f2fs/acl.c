<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/acl.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 *
 * Portions of this code from linux/fs/ext2/acl.c
 *
 * Copyright (C) 2001-2003 Andreas Gruenbacher, <agruen@suse.de>
 */
#समावेश <linux/f2fs_fs.h>
#समावेश "f2fs.h"
#समावेश "xattr.h"
#समावेश "acl.h"

अटल अंतरभूत माप_प्रकार f2fs_acl_size(पूर्णांक count)
अणु
	अगर (count <= 4) अणु
		वापस माप(काष्ठा f2fs_acl_header) +
			count * माप(काष्ठा f2fs_acl_entry_लघु);
	पूर्ण अन्यथा अणु
		वापस माप(काष्ठा f2fs_acl_header) +
			4 * माप(काष्ठा f2fs_acl_entry_लघु) +
			(count - 4) * माप(काष्ठा f2fs_acl_entry);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक f2fs_acl_count(माप_प्रकार size)
अणु
	sमाप_प्रकार s;

	size -= माप(काष्ठा f2fs_acl_header);
	s = size - 4 * माप(काष्ठा f2fs_acl_entry_लघु);
	अगर (s < 0) अणु
		अगर (size % माप(काष्ठा f2fs_acl_entry_लघु))
			वापस -1;
		वापस size / माप(काष्ठा f2fs_acl_entry_लघु);
	पूर्ण अन्यथा अणु
		अगर (s % माप(काष्ठा f2fs_acl_entry))
			वापस -1;
		वापस s / माप(काष्ठा f2fs_acl_entry) + 4;
	पूर्ण
पूर्ण

अटल काष्ठा posix_acl *f2fs_acl_from_disk(स्थिर अक्षर *value, माप_प्रकार size)
अणु
	पूर्णांक i, count;
	काष्ठा posix_acl *acl;
	काष्ठा f2fs_acl_header *hdr = (काष्ठा f2fs_acl_header *)value;
	काष्ठा f2fs_acl_entry *entry = (काष्ठा f2fs_acl_entry *)(hdr + 1);
	स्थिर अक्षर *end = value + size;

	अगर (size < माप(काष्ठा f2fs_acl_header))
		वापस ERR_PTR(-EINVAL);

	अगर (hdr->a_version != cpu_to_le32(F2FS_ACL_VERSION))
		वापस ERR_PTR(-EINVAL);

	count = f2fs_acl_count(size);
	अगर (count < 0)
		वापस ERR_PTR(-EINVAL);
	अगर (count == 0)
		वापस शून्य;

	acl = posix_acl_alloc(count, GFP_NOFS);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < count; i++) अणु

		अगर ((अक्षर *)entry > end)
			जाओ fail;

		acl->a_entries[i].e_tag  = le16_to_cpu(entry->e_tag);
		acl->a_entries[i].e_perm = le16_to_cpu(entry->e_perm);

		चयन (acl->a_entries[i].e_tag) अणु
		हाल ACL_USER_OBJ:
		हाल ACL_GROUP_OBJ:
		हाल ACL_MASK:
		हाल ACL_OTHER:
			entry = (काष्ठा f2fs_acl_entry *)((अक्षर *)entry +
					माप(काष्ठा f2fs_acl_entry_लघु));
			अवरोध;

		हाल ACL_USER:
			acl->a_entries[i].e_uid =
				make_kuid(&init_user_ns,
						le32_to_cpu(entry->e_id));
			entry = (काष्ठा f2fs_acl_entry *)((अक्षर *)entry +
					माप(काष्ठा f2fs_acl_entry));
			अवरोध;
		हाल ACL_GROUP:
			acl->a_entries[i].e_gid =
				make_kgid(&init_user_ns,
						le32_to_cpu(entry->e_id));
			entry = (काष्ठा f2fs_acl_entry *)((अक्षर *)entry +
					माप(काष्ठा f2fs_acl_entry));
			अवरोध;
		शेष:
			जाओ fail;
		पूर्ण
	पूर्ण
	अगर ((अक्षर *)entry != end)
		जाओ fail;
	वापस acl;
fail:
	posix_acl_release(acl);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम *f2fs_acl_to_disk(काष्ठा f2fs_sb_info *sbi,
				स्थिर काष्ठा posix_acl *acl, माप_प्रकार *size)
अणु
	काष्ठा f2fs_acl_header *f2fs_acl;
	काष्ठा f2fs_acl_entry *entry;
	पूर्णांक i;

	f2fs_acl = f2fs_kदो_स्मृति(sbi, माप(काष्ठा f2fs_acl_header) +
			acl->a_count * माप(काष्ठा f2fs_acl_entry),
			GFP_NOFS);
	अगर (!f2fs_acl)
		वापस ERR_PTR(-ENOMEM);

	f2fs_acl->a_version = cpu_to_le32(F2FS_ACL_VERSION);
	entry = (काष्ठा f2fs_acl_entry *)(f2fs_acl + 1);

	क्रम (i = 0; i < acl->a_count; i++) अणु

		entry->e_tag  = cpu_to_le16(acl->a_entries[i].e_tag);
		entry->e_perm = cpu_to_le16(acl->a_entries[i].e_perm);

		चयन (acl->a_entries[i].e_tag) अणु
		हाल ACL_USER:
			entry->e_id = cpu_to_le32(
					from_kuid(&init_user_ns,
						acl->a_entries[i].e_uid));
			entry = (काष्ठा f2fs_acl_entry *)((अक्षर *)entry +
					माप(काष्ठा f2fs_acl_entry));
			अवरोध;
		हाल ACL_GROUP:
			entry->e_id = cpu_to_le32(
					from_kgid(&init_user_ns,
						acl->a_entries[i].e_gid));
			entry = (काष्ठा f2fs_acl_entry *)((अक्षर *)entry +
					माप(काष्ठा f2fs_acl_entry));
			अवरोध;
		हाल ACL_USER_OBJ:
		हाल ACL_GROUP_OBJ:
		हाल ACL_MASK:
		हाल ACL_OTHER:
			entry = (काष्ठा f2fs_acl_entry *)((अक्षर *)entry +
					माप(काष्ठा f2fs_acl_entry_लघु));
			अवरोध;
		शेष:
			जाओ fail;
		पूर्ण
	पूर्ण
	*size = f2fs_acl_size(acl->a_count);
	वापस (व्योम *)f2fs_acl;

fail:
	kमुक्त(f2fs_acl);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा posix_acl *__f2fs_get_acl(काष्ठा inode *inode, पूर्णांक type,
						काष्ठा page *dpage)
अणु
	पूर्णांक name_index = F2FS_XATTR_INDEX_POSIX_ACL_DEFAULT;
	व्योम *value = शून्य;
	काष्ठा posix_acl *acl;
	पूर्णांक retval;

	अगर (type == ACL_TYPE_ACCESS)
		name_index = F2FS_XATTR_INDEX_POSIX_ACL_ACCESS;

	retval = f2fs_getxattr(inode, name_index, "", शून्य, 0, dpage);
	अगर (retval > 0) अणु
		value = f2fs_kदो_स्मृति(F2FS_I_SB(inode), retval, GFP_F2FS_ZERO);
		अगर (!value)
			वापस ERR_PTR(-ENOMEM);
		retval = f2fs_getxattr(inode, name_index, "", value,
							retval, dpage);
	पूर्ण

	अगर (retval > 0)
		acl = f2fs_acl_from_disk(value, retval);
	अन्यथा अगर (retval == -ENODATA)
		acl = शून्य;
	अन्यथा
		acl = ERR_PTR(retval);
	kमुक्त(value);

	वापस acl;
पूर्ण

काष्ठा posix_acl *f2fs_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	वापस __f2fs_get_acl(inode, type, शून्य);
पूर्ण

अटल पूर्णांक f2fs_acl_update_mode(काष्ठा inode *inode, umode_t *mode_p,
			  काष्ठा posix_acl **acl)
अणु
	umode_t mode = inode->i_mode;
	पूर्णांक error;

	अगर (is_inode_flag_set(inode, FI_ACL_MODE))
		mode = F2FS_I(inode)->i_acl_mode;

	error = posix_acl_equiv_mode(*acl, &mode);
	अगर (error < 0)
		वापस error;
	अगर (error == 0)
		*acl = शून्य;
	अगर (!in_group_p(i_gid_पूर्णांकo_mnt(&init_user_ns, inode)) &&
	    !capable_wrt_inode_uidgid(&init_user_ns, inode, CAP_FSETID))
		mode &= ~S_ISGID;
	*mode_p = mode;
	वापस 0;
पूर्ण

अटल पूर्णांक __f2fs_set_acl(काष्ठा inode *inode, पूर्णांक type,
			काष्ठा posix_acl *acl, काष्ठा page *ipage)
अणु
	पूर्णांक name_index;
	व्योम *value = शून्य;
	माप_प्रकार size = 0;
	पूर्णांक error;
	umode_t mode = inode->i_mode;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name_index = F2FS_XATTR_INDEX_POSIX_ACL_ACCESS;
		अगर (acl && !ipage) अणु
			error = f2fs_acl_update_mode(inode, &mode, &acl);
			अगर (error)
				वापस error;
			set_acl_inode(inode, mode);
		पूर्ण
		अवरोध;

	हाल ACL_TYPE_DEFAULT:
		name_index = F2FS_XATTR_INDEX_POSIX_ACL_DEFAULT;
		अगर (!S_ISसूची(inode->i_mode))
			वापस acl ? -EACCES : 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (acl) अणु
		value = f2fs_acl_to_disk(F2FS_I_SB(inode), acl, &size);
		अगर (IS_ERR(value)) अणु
			clear_inode_flag(inode, FI_ACL_MODE);
			वापस PTR_ERR(value);
		पूर्ण
	पूर्ण

	error = f2fs_setxattr(inode, name_index, "", value, size, ipage, 0);

	kमुक्त(value);
	अगर (!error)
		set_cached_acl(inode, type, acl);

	clear_inode_flag(inode, FI_ACL_MODE);
	वापस error;
पूर्ण

पूर्णांक f2fs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		 काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		वापस -EIO;

	वापस __f2fs_set_acl(inode, type, acl, शून्य);
पूर्ण

/*
 * Most part of f2fs_acl_clone, f2fs_acl_create_masq, f2fs_acl_create
 * are copied from posix_acl.c
 */
अटल काष्ठा posix_acl *f2fs_acl_clone(स्थिर काष्ठा posix_acl *acl,
							gfp_t flags)
अणु
	काष्ठा posix_acl *clone = शून्य;

	अगर (acl) अणु
		पूर्णांक size = माप(काष्ठा posix_acl) + acl->a_count *
				माप(काष्ठा posix_acl_entry);
		clone = kmemdup(acl, size, flags);
		अगर (clone)
			refcount_set(&clone->a_refcount, 1);
	पूर्ण
	वापस clone;
पूर्ण

अटल पूर्णांक f2fs_acl_create_masq(काष्ठा posix_acl *acl, umode_t *mode_p)
अणु
	काष्ठा posix_acl_entry *pa, *pe;
	काष्ठा posix_acl_entry *group_obj = शून्य, *mask_obj = शून्य;
	umode_t mode = *mode_p;
	पूर्णांक not_equiv = 0;

	/* निश्चित(atomic_पढ़ो(acl->a_refcount) == 1); */

	FOREACH_ACL_ENTRY(pa, acl, pe) अणु
		चयन (pa->e_tag) अणु
		हाल ACL_USER_OBJ:
			pa->e_perm &= (mode >> 6) | ~S_IRWXO;
			mode &= (pa->e_perm << 6) | ~S_IRWXU;
			अवरोध;

		हाल ACL_USER:
		हाल ACL_GROUP:
			not_equiv = 1;
			अवरोध;

		हाल ACL_GROUP_OBJ:
			group_obj = pa;
			अवरोध;

		हाल ACL_OTHER:
			pa->e_perm &= mode | ~S_IRWXO;
			mode &= pa->e_perm | ~S_IRWXO;
			अवरोध;

		हाल ACL_MASK:
			mask_obj = pa;
			not_equiv = 1;
			अवरोध;

		शेष:
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (mask_obj) अणु
		mask_obj->e_perm &= (mode >> 3) | ~S_IRWXO;
		mode &= (mask_obj->e_perm << 3) | ~S_IRWXG;
	पूर्ण अन्यथा अणु
		अगर (!group_obj)
			वापस -EIO;
		group_obj->e_perm &= (mode >> 3) | ~S_IRWXO;
		mode &= (group_obj->e_perm << 3) | ~S_IRWXG;
	पूर्ण

	*mode_p = (*mode_p & ~S_IRWXUGO) | mode;
	वापस not_equiv;
पूर्ण

अटल पूर्णांक f2fs_acl_create(काष्ठा inode *dir, umode_t *mode,
		काष्ठा posix_acl **शेष_acl, काष्ठा posix_acl **acl,
		काष्ठा page *dpage)
अणु
	काष्ठा posix_acl *p;
	काष्ठा posix_acl *clone;
	पूर्णांक ret;

	*acl = शून्य;
	*शेष_acl = शून्य;

	अगर (S_ISLNK(*mode) || !IS_POSIXACL(dir))
		वापस 0;

	p = __f2fs_get_acl(dir, ACL_TYPE_DEFAULT, dpage);
	अगर (!p || p == ERR_PTR(-EOPNOTSUPP)) अणु
		*mode &= ~current_umask();
		वापस 0;
	पूर्ण
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	clone = f2fs_acl_clone(p, GFP_NOFS);
	अगर (!clone) अणु
		ret = -ENOMEM;
		जाओ release_acl;
	पूर्ण

	ret = f2fs_acl_create_masq(clone, mode);
	अगर (ret < 0)
		जाओ release_clone;

	अगर (ret == 0)
		posix_acl_release(clone);
	अन्यथा
		*acl = clone;

	अगर (!S_ISसूची(*mode))
		posix_acl_release(p);
	अन्यथा
		*शेष_acl = p;

	वापस 0;

release_clone:
	posix_acl_release(clone);
release_acl:
	posix_acl_release(p);
	वापस ret;
पूर्ण

पूर्णांक f2fs_init_acl(काष्ठा inode *inode, काष्ठा inode *dir, काष्ठा page *ipage,
							काष्ठा page *dpage)
अणु
	काष्ठा posix_acl *शेष_acl = शून्य, *acl = शून्य;
	पूर्णांक error;

	error = f2fs_acl_create(dir, &inode->i_mode, &शेष_acl, &acl, dpage);
	अगर (error)
		वापस error;

	f2fs_mark_inode_dirty_sync(inode, true);

	अगर (शेष_acl) अणु
		error = __f2fs_set_acl(inode, ACL_TYPE_DEFAULT, शेष_acl,
				       ipage);
		posix_acl_release(शेष_acl);
	पूर्ण अन्यथा अणु
		inode->i_शेष_acl = शून्य;
	पूर्ण
	अगर (acl) अणु
		अगर (!error)
			error = __f2fs_set_acl(inode, ACL_TYPE_ACCESS, acl,
					       ipage);
		posix_acl_release(acl);
	पूर्ण अन्यथा अणु
		inode->i_acl = शून्य;
	पूर्ण

	वापस error;
पूर्ण
