<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/ceph/acl.c
 *
 * Copyright (C) 2013 Guangliang Zhao, <lucienchao@gmail.com>
 */

#समावेश <linux/ceph/ceph_debug.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश "super.h"

अटल अंतरभूत व्योम ceph_set_cached_acl(काष्ठा inode *inode,
					पूर्णांक type, काष्ठा posix_acl *acl)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);

	spin_lock(&ci->i_ceph_lock);
	अगर (__ceph_caps_issued_mask_metric(ci, CEPH_CAP_XATTR_SHARED, 0))
		set_cached_acl(inode, type, acl);
	अन्यथा
		क्रमget_cached_acl(inode, type);
	spin_unlock(&ci->i_ceph_lock);
पूर्ण

काष्ठा posix_acl *ceph_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	पूर्णांक size;
	अचिन्हित पूर्णांक retry_cnt = 0;
	स्थिर अक्षर *name;
	अक्षर *value = शून्य;
	काष्ठा posix_acl *acl;

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

retry:
	size = __ceph_getxattr(inode, name, "", 0);
	अगर (size > 0) अणु
		value = kzalloc(size, GFP_NOFS);
		अगर (!value)
			वापस ERR_PTR(-ENOMEM);
		size = __ceph_getxattr(inode, name, value, size);
	पूर्ण

	अगर (size == -दुस्फल && retry_cnt < 10) अणु
		retry_cnt++;
		kमुक्त(value);
		value = शून्य;
		जाओ retry;
	पूर्ण

	अगर (size > 0) अणु
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
	पूर्ण अन्यथा अगर (size == -ENODATA || size == 0) अणु
		acl = शून्य;
	पूर्ण अन्यथा अणु
		pr_err_ratelimited("get acl %llx.%llx failed, err=%d\n",
				   ceph_vinop(inode), size);
		acl = ERR_PTR(-EIO);
	पूर्ण

	kमुक्त(value);

	अगर (!IS_ERR(acl))
		ceph_set_cached_acl(inode, type, acl);

	वापस acl;
पूर्ण

पूर्णांक ceph_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		 काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक ret = 0, size = 0;
	स्थिर अक्षर *name = शून्य;
	अक्षर *value = शून्य;
	काष्ठा iattr newattrs;
	काष्ठा बारpec64 old_स_समय = inode->i_स_समय;
	umode_t new_mode = inode->i_mode, old_mode = inode->i_mode;

	अगर (ceph_snap(inode) != CEPH_NOSNAP) अणु
		ret = -EROFS;
		जाओ out;
	पूर्ण

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		अगर (acl) अणु
			ret = posix_acl_update_mode(&init_user_ns, inode,
						    &new_mode, &acl);
			अगर (ret)
				जाओ out;
		पूर्ण
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		अगर (!S_ISसूची(inode->i_mode)) अणु
			ret = acl ? -EINVAL : 0;
			जाओ out;
		पूर्ण
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (acl) अणु
		size = posix_acl_xattr_size(acl->a_count);
		value = kदो_स्मृति(size, GFP_NOFS);
		अगर (!value) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		ret = posix_acl_to_xattr(&init_user_ns, acl, value, size);
		अगर (ret < 0)
			जाओ out_मुक्त;
	पूर्ण

	अगर (new_mode != old_mode) अणु
		newattrs.ia_स_समय = current_समय(inode);
		newattrs.ia_mode = new_mode;
		newattrs.ia_valid = ATTR_MODE | ATTR_CTIME;
		ret = __ceph_setattr(inode, &newattrs);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	ret = __ceph_setxattr(inode, name, value, size, 0);
	अगर (ret) अणु
		अगर (new_mode != old_mode) अणु
			newattrs.ia_स_समय = old_स_समय;
			newattrs.ia_mode = old_mode;
			newattrs.ia_valid = ATTR_MODE | ATTR_CTIME;
			__ceph_setattr(inode, &newattrs);
		पूर्ण
		जाओ out_मुक्त;
	पूर्ण

	ceph_set_cached_acl(inode, type, acl);

out_मुक्त:
	kमुक्त(value);
out:
	वापस ret;
पूर्ण

पूर्णांक ceph_pre_init_acls(काष्ठा inode *dir, umode_t *mode,
		       काष्ठा ceph_acl_sec_ctx *as_ctx)
अणु
	काष्ठा posix_acl *acl, *शेष_acl;
	माप_प्रकार val_size1 = 0, val_size2 = 0;
	काष्ठा ceph_pagelist *pagelist = शून्य;
	व्योम *पंचांगp_buf = शून्य;
	पूर्णांक err;

	err = posix_acl_create(dir, mode, &शेष_acl, &acl);
	अगर (err)
		वापस err;

	अगर (acl) अणु
		err = posix_acl_equiv_mode(acl, mode);
		अगर (err < 0)
			जाओ out_err;
		अगर (err == 0) अणु
			posix_acl_release(acl);
			acl = शून्य;
		पूर्ण
	पूर्ण

	अगर (!शेष_acl && !acl)
		वापस 0;

	अगर (acl)
		val_size1 = posix_acl_xattr_size(acl->a_count);
	अगर (शेष_acl)
		val_size2 = posix_acl_xattr_size(शेष_acl->a_count);

	err = -ENOMEM;
	पंचांगp_buf = kदो_स्मृति(max(val_size1, val_size2), GFP_KERNEL);
	अगर (!पंचांगp_buf)
		जाओ out_err;
	pagelist = ceph_pagelist_alloc(GFP_KERNEL);
	अगर (!pagelist)
		जाओ out_err;

	err = ceph_pagelist_reserve(pagelist, PAGE_SIZE);
	अगर (err)
		जाओ out_err;

	ceph_pagelist_encode_32(pagelist, acl && शेष_acl ? 2 : 1);

	अगर (acl) अणु
		माप_प्रकार len = म_माप(XATTR_NAME_POSIX_ACL_ACCESS);
		err = ceph_pagelist_reserve(pagelist, len + val_size1 + 8);
		अगर (err)
			जाओ out_err;
		ceph_pagelist_encode_string(pagelist, XATTR_NAME_POSIX_ACL_ACCESS,
					    len);
		err = posix_acl_to_xattr(&init_user_ns, acl,
					 पंचांगp_buf, val_size1);
		अगर (err < 0)
			जाओ out_err;
		ceph_pagelist_encode_32(pagelist, val_size1);
		ceph_pagelist_append(pagelist, पंचांगp_buf, val_size1);
	पूर्ण
	अगर (शेष_acl) अणु
		माप_प्रकार len = म_माप(XATTR_NAME_POSIX_ACL_DEFAULT);
		err = ceph_pagelist_reserve(pagelist, len + val_size2 + 8);
		अगर (err)
			जाओ out_err;
		ceph_pagelist_encode_string(pagelist,
					  XATTR_NAME_POSIX_ACL_DEFAULT, len);
		err = posix_acl_to_xattr(&init_user_ns, शेष_acl,
					 पंचांगp_buf, val_size2);
		अगर (err < 0)
			जाओ out_err;
		ceph_pagelist_encode_32(pagelist, val_size2);
		ceph_pagelist_append(pagelist, पंचांगp_buf, val_size2);
	पूर्ण

	kमुक्त(पंचांगp_buf);

	as_ctx->acl = acl;
	as_ctx->शेष_acl = शेष_acl;
	as_ctx->pagelist = pagelist;
	वापस 0;

out_err:
	posix_acl_release(acl);
	posix_acl_release(शेष_acl);
	kमुक्त(पंचांगp_buf);
	अगर (pagelist)
		ceph_pagelist_release(pagelist);
	वापस err;
पूर्ण

व्योम ceph_init_inode_acls(काष्ठा inode *inode, काष्ठा ceph_acl_sec_ctx *as_ctx)
अणु
	अगर (!inode)
		वापस;
	ceph_set_cached_acl(inode, ACL_TYPE_ACCESS, as_ctx->acl);
	ceph_set_cached_acl(inode, ACL_TYPE_DEFAULT, as_ctx->शेष_acl);
पूर्ण
