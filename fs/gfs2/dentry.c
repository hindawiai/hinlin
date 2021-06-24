<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/namei.h>
#समावेश <linux/crc32.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "dir.h"
#समावेश "glock.h"
#समावेश "super.h"
#समावेश "util.h"
#समावेश "inode.h"

/**
 * gfs2_drevalidate - Check directory lookup consistency
 * @dentry: the mapping to check
 * @flags: lookup flags
 *
 * Check to make sure the lookup necessary to arrive at this inode from its
 * parent is still good.
 *
 * Returns: 1 अगर the dentry is ok, 0 अगर it isn't
 */

अटल पूर्णांक gfs2_drevalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *parent;
	काष्ठा gfs2_sbd *sdp;
	काष्ठा gfs2_inode *dip;
	काष्ठा inode *inode;
	काष्ठा gfs2_holder d_gh;
	काष्ठा gfs2_inode *ip = शून्य;
	पूर्णांक error, valid = 0;
	पूर्णांक had_lock = 0;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	parent = dget_parent(dentry);
	sdp = GFS2_SB(d_inode(parent));
	dip = GFS2_I(d_inode(parent));
	inode = d_inode(dentry);

	अगर (inode) अणु
		अगर (is_bad_inode(inode))
			जाओ out;
		ip = GFS2_I(inode);
	पूर्ण

	अगर (sdp->sd_lockकाष्ठा.ls_ops->lm_mount == शून्य) अणु
		valid = 1;
		जाओ out;
	पूर्ण

	had_lock = (gfs2_glock_is_locked_by_me(dip->i_gl) != शून्य);
	अगर (!had_lock) अणु
		error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, &d_gh);
		अगर (error)
			जाओ out;
	पूर्ण

	error = gfs2_dir_check(d_inode(parent), &dentry->d_name, ip);
	valid = inode ? !error : (error == -ENOENT);

	अगर (!had_lock)
		gfs2_glock_dq_uninit(&d_gh);
out:
	dput(parent);
	वापस valid;
पूर्ण

अटल पूर्णांक gfs2_dhash(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *str)
अणु
	str->hash = gfs2_disk_hash(str->name, str->len);
	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_dentry_delete(स्थिर काष्ठा dentry *dentry)
अणु
	काष्ठा gfs2_inode *ginode;

	अगर (d_really_is_negative(dentry))
		वापस 0;

	ginode = GFS2_I(d_inode(dentry));
	अगर (!gfs2_holder_initialized(&ginode->i_iखोलो_gh))
		वापस 0;

	अगर (test_bit(GLF_DEMOTE, &ginode->i_iखोलो_gh.gh_gl->gl_flags))
		वापस 1;

	वापस 0;
पूर्ण

स्थिर काष्ठा dentry_operations gfs2_करोps = अणु
	.d_revalidate = gfs2_drevalidate,
	.d_hash = gfs2_dhash,
	.d_delete = gfs2_dentry_delete,
पूर्ण;

