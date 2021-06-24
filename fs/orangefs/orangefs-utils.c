<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 * Copyright 2018 Omnibond Systems, L.L.C.
 *
 * See COPYING in top-level directory.
 */
#समावेश <linux/kernel.h>
#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-dev-proto.h"
#समावेश "orangefs-bufmap.h"

__s32 fsid_of_op(काष्ठा orangefs_kernel_op_s *op)
अणु
	__s32 fsid = ORANGEFS_FS_ID_शून्य;

	अगर (op) अणु
		चयन (op->upcall.type) अणु
		हाल ORANGEFS_VFS_OP_खाता_IO:
			fsid = op->upcall.req.io.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_LOOKUP:
			fsid = op->upcall.req.lookup.parent_refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_CREATE:
			fsid = op->upcall.req.create.parent_refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_GETATTR:
			fsid = op->upcall.req.getattr.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_REMOVE:
			fsid = op->upcall.req.हटाओ.parent_refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_MKसूची:
			fsid = op->upcall.req.सूची_गढ़ो.parent_refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_READसूची:
			fsid = op->upcall.req.सूची_पढ़ो.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_SETATTR:
			fsid = op->upcall.req.setattr.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_SYMLINK:
			fsid = op->upcall.req.sym.parent_refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_RENAME:
			fsid = op->upcall.req.नाम.old_parent_refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_STATFS:
			fsid = op->upcall.req.statfs.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_TRUNCATE:
			fsid = op->upcall.req.truncate.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_RA_FLUSH:
			fsid = op->upcall.req.ra_cache_flush.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_FS_UMOUNT:
			fsid = op->upcall.req.fs_umount.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_GETXATTR:
			fsid = op->upcall.req.getxattr.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_SETXATTR:
			fsid = op->upcall.req.setxattr.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_LISTXATTR:
			fsid = op->upcall.req.listxattr.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_REMOVEXATTR:
			fsid = op->upcall.req.हटाओxattr.refn.fs_id;
			अवरोध;
		हाल ORANGEFS_VFS_OP_FSYNC:
			fsid = op->upcall.req.fsync.refn.fs_id;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस fsid;
पूर्ण

अटल पूर्णांक orangefs_inode_flags(काष्ठा ORANGEFS_sys_attr_s *attrs)
अणु
	पूर्णांक flags = 0;
	अगर (attrs->flags & ORANGEFS_IMMUTABLE_FL)
		flags |= S_IMMUTABLE;
	अन्यथा
		flags &= ~S_IMMUTABLE;
	अगर (attrs->flags & ORANGEFS_APPEND_FL)
		flags |= S_APPEND;
	अन्यथा
		flags &= ~S_APPEND;
	अगर (attrs->flags & ORANGEFS_NOATIME_FL)
		flags |= S_NOATIME;
	अन्यथा
		flags &= ~S_NOATIME;
	वापस flags;
पूर्ण

अटल पूर्णांक orangefs_inode_perms(काष्ठा ORANGEFS_sys_attr_s *attrs)
अणु
	पूर्णांक perm_mode = 0;

	अगर (attrs->perms & ORANGEFS_O_EXECUTE)
		perm_mode |= S_IXOTH;
	अगर (attrs->perms & ORANGEFS_O_WRITE)
		perm_mode |= S_IWOTH;
	अगर (attrs->perms & ORANGEFS_O_READ)
		perm_mode |= S_IROTH;

	अगर (attrs->perms & ORANGEFS_G_EXECUTE)
		perm_mode |= S_IXGRP;
	अगर (attrs->perms & ORANGEFS_G_WRITE)
		perm_mode |= S_IWGRP;
	अगर (attrs->perms & ORANGEFS_G_READ)
		perm_mode |= S_IRGRP;

	अगर (attrs->perms & ORANGEFS_U_EXECUTE)
		perm_mode |= S_IXUSR;
	अगर (attrs->perms & ORANGEFS_U_WRITE)
		perm_mode |= S_IWUSR;
	अगर (attrs->perms & ORANGEFS_U_READ)
		perm_mode |= S_IRUSR;

	अगर (attrs->perms & ORANGEFS_G_SGID)
		perm_mode |= S_ISGID;
	अगर (attrs->perms & ORANGEFS_U_SUID)
		perm_mode |= S_ISUID;

	वापस perm_mode;
पूर्ण

/*
 * NOTE: in kernel land, we never use the sys_attr->link_target क्रम
 * anything, so करोn't bother copying it पूर्णांकo the sys_attr object here.
 */
अटल अंतरभूत व्योम copy_attributes_from_inode(काष्ठा inode *inode,
    काष्ठा ORANGEFS_sys_attr_s *attrs)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	attrs->mask = 0;
	अगर (orangefs_inode->attr_valid & ATTR_UID) अणु
		attrs->owner = from_kuid(&init_user_ns, inode->i_uid);
		attrs->mask |= ORANGEFS_ATTR_SYS_UID;
		gossip_debug(GOSSIP_UTILS_DEBUG, "(UID) %d\n", attrs->owner);
	पूर्ण
	अगर (orangefs_inode->attr_valid & ATTR_GID) अणु
		attrs->group = from_kgid(&init_user_ns, inode->i_gid);
		attrs->mask |= ORANGEFS_ATTR_SYS_GID;
		gossip_debug(GOSSIP_UTILS_DEBUG, "(GID) %d\n", attrs->group);
	पूर्ण

	अगर (orangefs_inode->attr_valid & ATTR_ATIME) अणु
		attrs->mask |= ORANGEFS_ATTR_SYS_ATIME;
		अगर (orangefs_inode->attr_valid & ATTR_ATIME_SET) अणु
			attrs->aसमय = (समय64_t)inode->i_aसमय.tv_sec;
			attrs->mask |= ORANGEFS_ATTR_SYS_ATIME_SET;
		पूर्ण
	पूर्ण
	अगर (orangefs_inode->attr_valid & ATTR_MTIME) अणु
		attrs->mask |= ORANGEFS_ATTR_SYS_MTIME;
		अगर (orangefs_inode->attr_valid & ATTR_MTIME_SET) अणु
			attrs->mसमय = (समय64_t)inode->i_mसमय.tv_sec;
			attrs->mask |= ORANGEFS_ATTR_SYS_MTIME_SET;
		पूर्ण
	पूर्ण
	अगर (orangefs_inode->attr_valid & ATTR_CTIME)
		attrs->mask |= ORANGEFS_ATTR_SYS_CTIME;

	/*
	 * ORANGEFS cannot set size with a setattr operation. Probably not
	 * likely to be requested through the VFS, but just in हाल, करोn't
	 * worry about ATTR_SIZE
	 */

	अगर (orangefs_inode->attr_valid & ATTR_MODE) अणु
		attrs->perms = ORANGEFS_util_translate_mode(inode->i_mode);
		attrs->mask |= ORANGEFS_ATTR_SYS_PERM;
	पूर्ण
पूर्ण

अटल पूर्णांक orangefs_inode_type(क्रमागत orangefs_ds_type objtype)
अणु
	अगर (objtype == ORANGEFS_TYPE_METAखाता)
		वापस S_IFREG;
	अन्यथा अगर (objtype == ORANGEFS_TYPE_सूचीECTORY)
		वापस S_IFसूची;
	अन्यथा अगर (objtype == ORANGEFS_TYPE_SYMLINK)
		वापस S_IFLNK;
	अन्यथा
		वापस -1;
पूर्ण

अटल व्योम orangefs_make_bad_inode(काष्ठा inode *inode)
अणु
	अगर (is_root_handle(inode)) अणु
		/*
		 * अगर this occurs, the pvfs2-client-core was समाप्तed but we
		 * can't afक्रमd to lose the inode operations and such
		 * associated with the root handle in any हाल.
		 */
		gossip_debug(GOSSIP_UTILS_DEBUG,
			     "*** NOT making bad root inode %pU\n",
			     get_khandle_from_ino(inode));
	पूर्ण अन्यथा अणु
		gossip_debug(GOSSIP_UTILS_DEBUG,
			     "*** making bad inode %pU\n",
			     get_khandle_from_ino(inode));
		make_bad_inode(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक orangefs_inode_is_stale(काष्ठा inode *inode,
    काष्ठा ORANGEFS_sys_attr_s *attrs, अक्षर *link_target)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	पूर्णांक type = orangefs_inode_type(attrs->objtype);
	/*
	 * If the inode type or symlink target have changed then this
	 * inode is stale.
	 */
	अगर (type == -1 || inode_wrong_type(inode, type)) अणु
		orangefs_make_bad_inode(inode);
		वापस 1;
	पूर्ण
	अगर (type == S_IFLNK && म_भेदन(orangefs_inode->link_target,
	    link_target, ORANGEFS_NAME_MAX)) अणु
		orangefs_make_bad_inode(inode);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक orangefs_inode_getattr(काष्ठा inode *inode, पूर्णांक flags)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_kernel_op_s *new_op;
	loff_t inode_size;
	पूर्णांक ret, type;

	gossip_debug(GOSSIP_UTILS_DEBUG, "%s: called on inode %pU flags %d\n",
	    __func__, get_khandle_from_ino(inode), flags);

again:
	spin_lock(&inode->i_lock);
	/* Must have all the attributes in the mask and be within cache समय. */
	अगर ((!flags && समय_beक्रमe(jअगरfies, orangefs_inode->getattr_समय)) ||
	    orangefs_inode->attr_valid || inode->i_state & I_सूचीTY_PAGES) अणु
		अगर (orangefs_inode->attr_valid) अणु
			spin_unlock(&inode->i_lock);
			ग_लिखो_inode_now(inode, 1);
			जाओ again;
		पूर्ण
		spin_unlock(&inode->i_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&inode->i_lock);

	new_op = op_alloc(ORANGEFS_VFS_OP_GETATTR);
	अगर (!new_op)
		वापस -ENOMEM;
	new_op->upcall.req.getattr.refn = orangefs_inode->refn;
	/*
	 * Size is the hardest attribute to get.  The incremental cost of any
	 * other attribute is essentially zero.
	 */
	अगर (flags)
		new_op->upcall.req.getattr.mask = ORANGEFS_ATTR_SYS_ALL_NOHINT;
	अन्यथा
		new_op->upcall.req.getattr.mask =
		    ORANGEFS_ATTR_SYS_ALL_NOHINT & ~ORANGEFS_ATTR_SYS_SIZE;

	ret = service_operation(new_op, __func__,
	    get_पूर्णांकerruptible_flag(inode));
	अगर (ret != 0)
		जाओ out;

again2:
	spin_lock(&inode->i_lock);
	/* Must have all the attributes in the mask and be within cache समय. */
	अगर ((!flags && समय_beक्रमe(jअगरfies, orangefs_inode->getattr_समय)) ||
	    orangefs_inode->attr_valid || inode->i_state & I_सूचीTY_PAGES) अणु
		अगर (orangefs_inode->attr_valid) अणु
			spin_unlock(&inode->i_lock);
			ग_लिखो_inode_now(inode, 1);
			जाओ again2;
		पूर्ण
		अगर (inode->i_state & I_सूचीTY_PAGES) अणु
			ret = 0;
			जाओ out_unlock;
		पूर्ण
		gossip_debug(GOSSIP_UTILS_DEBUG, "%s: in cache or dirty\n",
		    __func__);
		ret = 0;
		जाओ out_unlock;
	पूर्ण

	अगर (!(flags & ORANGEFS_GETATTR_NEW)) अणु
		ret = orangefs_inode_is_stale(inode,
		    &new_op->करोwncall.resp.getattr.attributes,
		    new_op->करोwncall.resp.getattr.link_target);
		अगर (ret) अणु
			ret = -ESTALE;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	type = orangefs_inode_type(new_op->
	    करोwncall.resp.getattr.attributes.objtype);
	चयन (type) अणु
	हाल S_IFREG:
		inode->i_flags = orangefs_inode_flags(&new_op->
		    करोwncall.resp.getattr.attributes);
		अगर (flags) अणु
			inode_size = (loff_t)new_op->
			    करोwncall.resp.getattr.attributes.size;
			inode->i_size = inode_size;
			inode->i_blkbits = ffs(new_op->करोwncall.resp.getattr.
			    attributes.blksize);
			inode->i_bytes = inode_size;
			inode->i_blocks =
			    (inode_size + 512 - inode_size % 512)/512;
		पूर्ण
		अवरोध;
	हाल S_IFसूची:
		अगर (flags) अणु
			inode->i_size = PAGE_SIZE;
			inode_set_bytes(inode, inode->i_size);
		पूर्ण
		set_nlink(inode, 1);
		अवरोध;
	हाल S_IFLNK:
		अगर (flags & ORANGEFS_GETATTR_NEW) अणु
			inode->i_size = (loff_t)म_माप(new_op->
			    करोwncall.resp.getattr.link_target);
			ret = strscpy(orangefs_inode->link_target,
			    new_op->करोwncall.resp.getattr.link_target,
			    ORANGEFS_NAME_MAX);
			अगर (ret == -E2BIG) अणु
				ret = -EIO;
				जाओ out_unlock;
			पूर्ण
			inode->i_link = orangefs_inode->link_target;
		पूर्ण
		अवरोध;
	/* i.e. -1 */
	शेष:
		/* XXX: ESTALE?  This is what is करोne अगर it is not new. */
		orangefs_make_bad_inode(inode);
		ret = -ESTALE;
		जाओ out_unlock;
	पूर्ण

	inode->i_uid = make_kuid(&init_user_ns, new_op->
	    करोwncall.resp.getattr.attributes.owner);
	inode->i_gid = make_kgid(&init_user_ns, new_op->
	    करोwncall.resp.getattr.attributes.group);
	inode->i_aसमय.tv_sec = (समय64_t)new_op->
	    करोwncall.resp.getattr.attributes.aसमय;
	inode->i_mसमय.tv_sec = (समय64_t)new_op->
	    करोwncall.resp.getattr.attributes.mसमय;
	inode->i_स_समय.tv_sec = (समय64_t)new_op->
	    करोwncall.resp.getattr.attributes.स_समय;
	inode->i_aसमय.tv_nsec = 0;
	inode->i_mसमय.tv_nsec = 0;
	inode->i_स_समय.tv_nsec = 0;

	/* special हाल: mark the root inode as sticky */
	inode->i_mode = type | (is_root_handle(inode) ? S_ISVTX : 0) |
	    orangefs_inode_perms(&new_op->करोwncall.resp.getattr.attributes);

	orangefs_inode->getattr_समय = jअगरfies +
	    orangefs_getattr_समयout_msecs*HZ/1000;
	ret = 0;
out_unlock:
	spin_unlock(&inode->i_lock);
out:
	op_release(new_op);
	वापस ret;
पूर्ण

पूर्णांक orangefs_inode_check_changed(काष्ठा inode *inode)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_kernel_op_s *new_op;
	पूर्णांक ret;

	gossip_debug(GOSSIP_UTILS_DEBUG, "%s: called on inode %pU\n", __func__,
	    get_khandle_from_ino(inode));

	new_op = op_alloc(ORANGEFS_VFS_OP_GETATTR);
	अगर (!new_op)
		वापस -ENOMEM;
	new_op->upcall.req.getattr.refn = orangefs_inode->refn;
	new_op->upcall.req.getattr.mask = ORANGEFS_ATTR_SYS_TYPE |
	    ORANGEFS_ATTR_SYS_LNK_TARGET;

	ret = service_operation(new_op, __func__,
	    get_पूर्णांकerruptible_flag(inode));
	अगर (ret != 0)
		जाओ out;

	ret = orangefs_inode_is_stale(inode,
	    &new_op->करोwncall.resp.getattr.attributes,
	    new_op->करोwncall.resp.getattr.link_target);
out:
	op_release(new_op);
	वापस ret;
पूर्ण

/*
 * issues a orangefs setattr request to make sure the new attribute values
 * take effect अगर successful.  वापसs 0 on success; -त्रुटि_सं otherwise
 */
पूर्णांक orangefs_inode_setattr(काष्ठा inode *inode)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_kernel_op_s *new_op;
	पूर्णांक ret;

	new_op = op_alloc(ORANGEFS_VFS_OP_SETATTR);
	अगर (!new_op)
		वापस -ENOMEM;

	spin_lock(&inode->i_lock);
	new_op->upcall.uid = from_kuid(&init_user_ns, orangefs_inode->attr_uid);
	new_op->upcall.gid = from_kgid(&init_user_ns, orangefs_inode->attr_gid);
	new_op->upcall.req.setattr.refn = orangefs_inode->refn;
	copy_attributes_from_inode(inode,
	    &new_op->upcall.req.setattr.attributes);
	orangefs_inode->attr_valid = 0;
	अगर (!new_op->upcall.req.setattr.attributes.mask) अणु
		spin_unlock(&inode->i_lock);
		op_release(new_op);
		वापस 0;
	पूर्ण
	spin_unlock(&inode->i_lock);

	ret = service_operation(new_op, __func__,
	    get_पूर्णांकerruptible_flag(inode) | ORANGEFS_OP_WRITEBACK);
	gossip_debug(GOSSIP_UTILS_DEBUG,
	    "orangefs_inode_setattr: returning %d\n", ret);
	अगर (ret)
		orangefs_make_bad_inode(inode);

	op_release(new_op);

	अगर (ret == 0)
		orangefs_inode->getattr_समय = jअगरfies - 1;
	वापस ret;
पूर्ण

/*
 * The following is a very dirty hack that is now a permanent part of the
 * ORANGEFS protocol. See protocol.h क्रम more error definitions.
 */

/* The order matches include/orangefs-types.h in the OrangeFS source. */
अटल पूर्णांक PINT_त्रुटि_सं_mapping[] = अणु
	0, EPERM, ENOENT, EINTR, EIO, ENXIO, EBADF, EAGAIN, ENOMEM,
	EFAULT, EBUSY, EEXIST, ENODEV, ENOTसूची, EISसूची, EINVAL, EMखाता,
	EFBIG, ENOSPC, EROFS, EMLINK, EPIPE, EDEADLK, ENAMETOOLONG,
	ENOLCK, ENOSYS, ENOTEMPTY, ELOOP, EWOULDBLOCK, ENOMSG, EUNATCH,
	EBADR, EDEADLOCK, ENODATA, ETIME, ENONET, EREMOTE, ECOMM,
	EPROTO, EBADMSG, EOVERFLOW, ERESTART, EMSGSIZE, EPROTOTYPE,
	ENOPROTOOPT, EPROTONOSUPPORT, EOPNOTSUPP, EADDRINUSE,
	EADDRNOTAVAIL, ENETDOWN, ENETUNREACH, ENETRESET, ENOBUFS,
	ETIMEDOUT, ECONNREFUSED, EHOSTDOWN, EHOSTUNREACH, EALREADY,
	EACCES, ECONNRESET, दुस्फल
पूर्ण;

पूर्णांक orangefs_normalize_to_त्रुटि_सं(__s32 error_code)
अणु
	__u32 i;

	/* Success */
	अगर (error_code == 0) अणु
		वापस 0;
	/*
	 * This shouldn't ever happen. If it करोes it should be fixed on the
	 * server.
	 */
	पूर्ण अन्यथा अगर (error_code > 0) अणु
		gossip_err("orangefs: error status received.\n");
		gossip_err("orangefs: assuming error code is inverted.\n");
		error_code = -error_code;
	पूर्ण

	/*
	 * XXX: This is very bad since error codes from ORANGEFS may not be
	 * suitable क्रम वापस पूर्णांकo userspace.
	 */

	/*
	 * Convert ORANGEFS error values पूर्णांकo त्रुटि_सं values suitable क्रम वापस
	 * from the kernel.
	 */
	अगर ((-error_code) & ORANGEFS_NON_ERRNO_ERROR_BIT) अणु
		अगर (((-error_code) &
		    (ORANGEFS_ERROR_NUMBER_BITS|ORANGEFS_NON_ERRNO_ERROR_BIT|
		    ORANGEFS_ERROR_BIT)) == ORANGEFS_ECANCEL) अणु
			/*
			 * cancellation error codes generally correspond to
			 * a समयout from the client's perspective
			 */
			error_code = -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			/* assume a शेष error code */
			gossip_err("%s: bad error code :%d:.\n",
				__func__,
				error_code);
			error_code = -EINVAL;
		पूर्ण

	/* Convert ORANGEFS encoded त्रुटि_सं values पूर्णांकo regular त्रुटि_सं values. */
	पूर्ण अन्यथा अगर ((-error_code) & ORANGEFS_ERROR_BIT) अणु
		i = (-error_code) & ~(ORANGEFS_ERROR_BIT|ORANGEFS_ERROR_CLASS_BITS);
		अगर (i < ARRAY_SIZE(PINT_त्रुटि_सं_mapping))
			error_code = -PINT_त्रुटि_सं_mapping[i];
		अन्यथा
			error_code = -EINVAL;

	/*
	 * Only ORANGEFS protocol error codes should ever come here. Otherwise
	 * there is a bug somewhere.
	 */
	पूर्ण अन्यथा अणु
		gossip_err("%s: unknown error code.\n", __func__);
		error_code = -EINVAL;
	पूर्ण
	वापस error_code;
पूर्ण

#घोषणा NUM_MODES 11
__s32 ORANGEFS_util_translate_mode(पूर्णांक mode)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i = 0;
	अटल पूर्णांक modes[NUM_MODES] = अणु
		S_IXOTH, S_IWOTH, S_IROTH,
		S_IXGRP, S_IWGRP, S_IRGRP,
		S_IXUSR, S_IWUSR, S_IRUSR,
		S_ISGID, S_ISUID
	पूर्ण;
	अटल पूर्णांक orangefs_modes[NUM_MODES] = अणु
		ORANGEFS_O_EXECUTE, ORANGEFS_O_WRITE, ORANGEFS_O_READ,
		ORANGEFS_G_EXECUTE, ORANGEFS_G_WRITE, ORANGEFS_G_READ,
		ORANGEFS_U_EXECUTE, ORANGEFS_U_WRITE, ORANGEFS_U_READ,
		ORANGEFS_G_SGID, ORANGEFS_U_SUID
	पूर्ण;

	क्रम (i = 0; i < NUM_MODES; i++)
		अगर (mode & modes[i])
			ret |= orangefs_modes[i];

	वापस ret;
पूर्ण
#अघोषित NUM_MODES
