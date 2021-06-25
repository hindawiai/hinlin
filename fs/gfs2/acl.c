<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/gfs2_ondisk.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "acl.h"
#समावेश "xattr.h"
#समावेश "glock.h"
#समावेश "inode.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "rgrp.h"
#समावेश "trans.h"
#समावेश "util.h"

अटल स्थिर अक्षर *gfs2_acl_name(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		वापस XATTR_POSIX_ACL_ACCESS;
	हाल ACL_TYPE_DEFAULT:
		वापस XATTR_POSIX_ACL_DEFAULT;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा posix_acl *__gfs2_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा posix_acl *acl;
	स्थिर अक्षर *name;
	अक्षर *data;
	पूर्णांक len;

	अगर (!ip->i_eattr)
		वापस शून्य;

	name = gfs2_acl_name(type);
	len = gfs2_xattr_acl_get(ip, name, &data);
	अगर (len <= 0)
		वापस ERR_PTR(len);
	acl = posix_acl_from_xattr(&init_user_ns, data, len);
	kमुक्त(data);
	वापस acl;
पूर्ण

काष्ठा posix_acl *gfs2_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	bool need_unlock = false;
	काष्ठा posix_acl *acl;

	अगर (!gfs2_glock_is_locked_by_me(ip->i_gl)) अणु
		पूर्णांक ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED,
					     LM_FLAG_ANY, &gh);
		अगर (ret)
			वापस ERR_PTR(ret);
		need_unlock = true;
	पूर्ण
	acl = __gfs2_get_acl(inode, type);
	अगर (need_unlock)
		gfs2_glock_dq_uninit(&gh);
	वापस acl;
पूर्ण

पूर्णांक __gfs2_set_acl(काष्ठा inode *inode, काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक error;
	माप_प्रकार len;
	अक्षर *data;
	स्थिर अक्षर *name = gfs2_acl_name(type);

	अगर (acl) अणु
		len = posix_acl_xattr_size(acl->a_count);
		data = kदो_स्मृति(len, GFP_NOFS);
		अगर (data == शून्य)
			वापस -ENOMEM;
		error = posix_acl_to_xattr(&init_user_ns, acl, data, len);
		अगर (error < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		data = शून्य;
		len = 0;
	पूर्ण

	error = __gfs2_xattr_set(inode, name, data, len, 0, GFS2_EATYPE_SYS);
	अगर (error)
		जाओ out;
	set_cached_acl(inode, type, acl);
out:
	kमुक्त(data);
	वापस error;
पूर्ण

पूर्णांक gfs2_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		 काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	bool need_unlock = false;
	पूर्णांक ret;
	umode_t mode;

	अगर (acl && acl->a_count > GFS2_ACL_MAX_ENTRIES(GFS2_SB(inode)))
		वापस -E2BIG;

	ret = gfs2_qa_get(ip);
	अगर (ret)
		वापस ret;

	अगर (!gfs2_glock_is_locked_by_me(ip->i_gl)) अणु
		ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
		अगर (ret)
			जाओ out;
		need_unlock = true;
	पूर्ण

	mode = inode->i_mode;
	अगर (type == ACL_TYPE_ACCESS && acl) अणु
		ret = posix_acl_update_mode(&init_user_ns, inode, &mode, &acl);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	ret = __gfs2_set_acl(inode, acl, type);
	अगर (!ret && mode != inode->i_mode) अणु
		inode->i_स_समय = current_समय(inode);
		inode->i_mode = mode;
		mark_inode_dirty(inode);
	पूर्ण
unlock:
	अगर (need_unlock)
		gfs2_glock_dq_uninit(&gh);
out:
	gfs2_qa_put(ip);
	वापस ret;
पूर्ण
