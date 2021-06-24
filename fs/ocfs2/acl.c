<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * acl.c
 *
 * Copyright (C) 2004, 2008 Oracle.  All rights reserved.
 *
 * CREDITS:
 * Lots of code in this file is copy from linux/fs/ext3/acl.c.
 * Copyright (C) 2001-2003 Andreas Gruenbacher, <agruen@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"
#समावेश "alloc.h"
#समावेश "dlmglue.h"
#समावेश "file.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "ocfs2_fs.h"

#समावेश "xattr.h"
#समावेश "acl.h"

/*
 * Convert from xattr value to acl काष्ठा.
 */
अटल काष्ठा posix_acl *ocfs2_acl_from_xattr(स्थिर व्योम *value, माप_प्रकार size)
अणु
	पूर्णांक n, count;
	काष्ठा posix_acl *acl;

	अगर (!value)
		वापस शून्य;
	अगर (size < माप(काष्ठा posix_acl_entry))
		वापस ERR_PTR(-EINVAL);

	count = size / माप(काष्ठा posix_acl_entry);

	acl = posix_acl_alloc(count, GFP_NOFS);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);
	क्रम (n = 0; n < count; n++) अणु
		काष्ठा ocfs2_acl_entry *entry =
			(काष्ठा ocfs2_acl_entry *)value;

		acl->a_entries[n].e_tag  = le16_to_cpu(entry->e_tag);
		acl->a_entries[n].e_perm = le16_to_cpu(entry->e_perm);
		चयन(acl->a_entries[n].e_tag) अणु
		हाल ACL_USER:
			acl->a_entries[n].e_uid =
				make_kuid(&init_user_ns,
					  le32_to_cpu(entry->e_id));
			अवरोध;
		हाल ACL_GROUP:
			acl->a_entries[n].e_gid =
				make_kgid(&init_user_ns,
					  le32_to_cpu(entry->e_id));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		value += माप(काष्ठा posix_acl_entry);

	पूर्ण
	वापस acl;
पूर्ण

/*
 * Convert acl काष्ठा to xattr value.
 */
अटल व्योम *ocfs2_acl_to_xattr(स्थिर काष्ठा posix_acl *acl, माप_प्रकार *size)
अणु
	काष्ठा ocfs2_acl_entry *entry = शून्य;
	अक्षर *ocfs2_acl;
	माप_प्रकार n;

	*size = acl->a_count * माप(काष्ठा posix_acl_entry);

	ocfs2_acl = kदो_स्मृति(*size, GFP_NOFS);
	अगर (!ocfs2_acl)
		वापस ERR_PTR(-ENOMEM);

	entry = (काष्ठा ocfs2_acl_entry *)ocfs2_acl;
	क्रम (n = 0; n < acl->a_count; n++, entry++) अणु
		entry->e_tag  = cpu_to_le16(acl->a_entries[n].e_tag);
		entry->e_perm = cpu_to_le16(acl->a_entries[n].e_perm);
		चयन(acl->a_entries[n].e_tag) अणु
		हाल ACL_USER:
			entry->e_id = cpu_to_le32(
				from_kuid(&init_user_ns,
					  acl->a_entries[n].e_uid));
			अवरोध;
		हाल ACL_GROUP:
			entry->e_id = cpu_to_le32(
				from_kgid(&init_user_ns,
					  acl->a_entries[n].e_gid));
			अवरोध;
		शेष:
			entry->e_id = cpu_to_le32(ACL_UNDEFINED_ID);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ocfs2_acl;
पूर्ण

अटल काष्ठा posix_acl *ocfs2_get_acl_nolock(काष्ठा inode *inode,
					      पूर्णांक type,
					      काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक name_index;
	अक्षर *value = शून्य;
	काष्ठा posix_acl *acl;
	पूर्णांक retval;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name_index = OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		name_index = OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	retval = ocfs2_xattr_get_nolock(inode, di_bh, name_index, "", शून्य, 0);
	अगर (retval > 0) अणु
		value = kदो_स्मृति(retval, GFP_NOFS);
		अगर (!value)
			वापस ERR_PTR(-ENOMEM);
		retval = ocfs2_xattr_get_nolock(inode, di_bh, name_index,
						"", value, retval);
	पूर्ण

	अगर (retval > 0)
		acl = ocfs2_acl_from_xattr(value, retval);
	अन्यथा अगर (retval == -ENODATA || retval == 0)
		acl = शून्य;
	अन्यथा
		acl = ERR_PTR(retval);

	kमुक्त(value);

	वापस acl;
पूर्ण

/*
 * Helper function to set i_mode in memory and disk. Some call paths
 * will not have di_bh or a journal handle to pass, in which हाल it
 * will create it's own.
 */
अटल पूर्णांक ocfs2_acl_set_mode(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
			      handle_t *handle, umode_t new_mode)
अणु
	पूर्णांक ret, commit_handle = 0;
	काष्ठा ocfs2_dinode *di;

	अगर (di_bh == शून्य) अणु
		ret = ocfs2_पढ़ो_inode_block(inode, &di_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		get_bh(di_bh);

	अगर (handle == शून्य) अणु
		handle = ocfs2_start_trans(OCFS2_SB(inode->i_sb),
					   OCFS2_INODE_UPDATE_CREDITS);
		अगर (IS_ERR(handle)) अणु
			ret = PTR_ERR(handle);
			mlog_त्रुटि_सं(ret);
			जाओ out_brअन्यथा;
		पूर्ण

		commit_handle = 1;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	inode->i_mode = new_mode;
	inode->i_स_समय = current_समय(inode);
	di->i_mode = cpu_to_le16(inode->i_mode);
	di->i_स_समय = cpu_to_le64(inode->i_स_समय.tv_sec);
	di->i_स_समय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);

	ocfs2_journal_dirty(handle, di_bh);

out_commit:
	अगर (commit_handle)
		ocfs2_commit_trans(OCFS2_SB(inode->i_sb), handle);
out_brअन्यथा:
	brअन्यथा(di_bh);
out:
	वापस ret;
पूर्ण

/*
 * Set the access or शेष ACL of an inode.
 */
अटल पूर्णांक ocfs2_set_acl(handle_t *handle,
			 काष्ठा inode *inode,
			 काष्ठा buffer_head *di_bh,
			 पूर्णांक type,
			 काष्ठा posix_acl *acl,
			 काष्ठा ocfs2_alloc_context *meta_ac,
			 काष्ठा ocfs2_alloc_context *data_ac)
अणु
	पूर्णांक name_index;
	व्योम *value = शून्य;
	माप_प्रकार size = 0;
	पूर्णांक ret;

	अगर (S_ISLNK(inode->i_mode))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name_index = OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		name_index = OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT;
		अगर (!S_ISसूची(inode->i_mode))
			वापस acl ? -EACCES : 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (acl) अणु
		value = ocfs2_acl_to_xattr(acl, &size);
		अगर (IS_ERR(value))
			वापस (पूर्णांक)PTR_ERR(value);
	पूर्ण

	अगर (handle)
		ret = ocfs2_xattr_set_handle(handle, inode, di_bh, name_index,
					     "", value, size, 0,
					     meta_ac, data_ac);
	अन्यथा
		ret = ocfs2_xattr_set(inode, name_index, "", value, size, 0);

	kमुक्त(value);
	अगर (!ret)
		set_cached_acl(inode, type, acl);

	वापस ret;
पूर्ण

पूर्णांक ocfs2_iop_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		      काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक status, had_lock;
	काष्ठा ocfs2_lock_holder oh;

	had_lock = ocfs2_inode_lock_tracker(inode, &bh, 1, &oh);
	अगर (had_lock < 0)
		वापस had_lock;
	अगर (type == ACL_TYPE_ACCESS && acl) अणु
		umode_t mode;

		status = posix_acl_update_mode(&init_user_ns, inode, &mode,
					       &acl);
		अगर (status)
			जाओ unlock;

		status = ocfs2_acl_set_mode(inode, bh, शून्य, mode);
		अगर (status)
			जाओ unlock;
	पूर्ण
	status = ocfs2_set_acl(शून्य, inode, bh, type, acl, शून्य, शून्य);
unlock:
	ocfs2_inode_unlock_tracker(inode, 1, &oh, had_lock);
	brअन्यथा(bh);
	वापस status;
पूर्ण

काष्ठा posix_acl *ocfs2_iop_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा ocfs2_super *osb;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा posix_acl *acl;
	पूर्णांक had_lock;
	काष्ठा ocfs2_lock_holder oh;

	osb = OCFS2_SB(inode->i_sb);
	अगर (!(osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL))
		वापस शून्य;

	had_lock = ocfs2_inode_lock_tracker(inode, &di_bh, 0, &oh);
	अगर (had_lock < 0)
		वापस ERR_PTR(had_lock);

	करोwn_पढ़ो(&OCFS2_I(inode)->ip_xattr_sem);
	acl = ocfs2_get_acl_nolock(inode, type, di_bh);
	up_पढ़ो(&OCFS2_I(inode)->ip_xattr_sem);

	ocfs2_inode_unlock_tracker(inode, 0, &oh, had_lock);
	brअन्यथा(di_bh);
	वापस acl;
पूर्ण

पूर्णांक ocfs2_acl_chmod(काष्ठा inode *inode, काष्ठा buffer_head *bh)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा posix_acl *acl;
	पूर्णांक ret;

	अगर (S_ISLNK(inode->i_mode))
		वापस -EOPNOTSUPP;

	अगर (!(osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL))
		वापस 0;

	करोwn_पढ़ो(&OCFS2_I(inode)->ip_xattr_sem);
	acl = ocfs2_get_acl_nolock(inode, ACL_TYPE_ACCESS, bh);
	up_पढ़ो(&OCFS2_I(inode)->ip_xattr_sem);
	अगर (IS_ERR_OR_शून्य(acl))
		वापस PTR_ERR_OR_ZERO(acl);
	ret = __posix_acl_chmod(&acl, GFP_KERNEL, inode->i_mode);
	अगर (ret)
		वापस ret;
	ret = ocfs2_set_acl(शून्य, inode, शून्य, ACL_TYPE_ACCESS,
			    acl, शून्य, शून्य);
	posix_acl_release(acl);
	वापस ret;
पूर्ण

/*
 * Initialize the ACLs of a new inode. If parent directory has शेष ACL,
 * then clone to new inode. Called from ocfs2_mknod.
 */
पूर्णांक ocfs2_init_acl(handle_t *handle,
		   काष्ठा inode *inode,
		   काष्ठा inode *dir,
		   काष्ठा buffer_head *di_bh,
		   काष्ठा buffer_head *dir_bh,
		   काष्ठा ocfs2_alloc_context *meta_ac,
		   काष्ठा ocfs2_alloc_context *data_ac)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा posix_acl *acl = शून्य;
	पूर्णांक ret = 0, ret2;
	umode_t mode;

	अगर (!S_ISLNK(inode->i_mode)) अणु
		अगर (osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL) अणु
			करोwn_पढ़ो(&OCFS2_I(dir)->ip_xattr_sem);
			acl = ocfs2_get_acl_nolock(dir, ACL_TYPE_DEFAULT,
						   dir_bh);
			up_पढ़ो(&OCFS2_I(dir)->ip_xattr_sem);
			अगर (IS_ERR(acl))
				वापस PTR_ERR(acl);
		पूर्ण
		अगर (!acl) अणु
			mode = inode->i_mode & ~current_umask();
			ret = ocfs2_acl_set_mode(inode, di_bh, handle, mode);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ cleanup;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL) && acl) अणु
		अगर (S_ISसूची(inode->i_mode)) अणु
			ret = ocfs2_set_acl(handle, inode, di_bh,
					    ACL_TYPE_DEFAULT, acl,
					    meta_ac, data_ac);
			अगर (ret)
				जाओ cleanup;
		पूर्ण
		mode = inode->i_mode;
		ret = __posix_acl_create(&acl, GFP_NOFS, &mode);
		अगर (ret < 0)
			वापस ret;

		ret2 = ocfs2_acl_set_mode(inode, di_bh, handle, mode);
		अगर (ret2) अणु
			mlog_त्रुटि_सं(ret2);
			ret = ret2;
			जाओ cleanup;
		पूर्ण
		अगर (ret > 0) अणु
			ret = ocfs2_set_acl(handle, inode,
					    di_bh, ACL_TYPE_ACCESS,
					    acl, meta_ac, data_ac);
		पूर्ण
	पूर्ण
cleanup:
	posix_acl_release(acl);
	वापस ret;
पूर्ण
