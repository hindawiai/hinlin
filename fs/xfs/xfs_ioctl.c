<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_rtalloc.h"
#समावेश "xfs_iwalk.h"
#समावेश "xfs_itable.h"
#समावेश "xfs_error.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_fsops.h"
#समावेश "xfs_discard.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_export.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_acl.h"
#समावेश "xfs_btree.h"
#समावेश <linux/fsmap.h>
#समावेश "xfs_fsmap.h"
#समावेश "scrub/xfs_scrub.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_ag.h"
#समावेश "xfs_health.h"
#समावेश "xfs_reflink.h"
#समावेश "xfs_ioctl.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"

#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/fileattr.h>

/*
 * xfs_find_handle maps from userspace xfs_fsop_handlereq काष्ठाure to
 * a file or fs handle.
 *
 * XFS_IOC_PATH_TO_FSHANDLE
 *    वापसs fs handle क्रम a mount poपूर्णांक or path within that mount poपूर्णांक
 * XFS_IOC_FD_TO_HANDLE
 *    वापसs full handle क्रम a FD खोलोed in user space
 * XFS_IOC_PATH_TO_HANDLE
 *    वापसs full handle क्रम a path
 */
पूर्णांक
xfs_find_handle(
	अचिन्हित पूर्णांक		cmd,
	xfs_fsop_handlereq_t	*hreq)
अणु
	पूर्णांक			hsize;
	xfs_handle_t		handle;
	काष्ठा inode		*inode;
	काष्ठा fd		f = अणुशून्यपूर्ण;
	काष्ठा path		path;
	पूर्णांक			error;
	काष्ठा xfs_inode	*ip;

	अगर (cmd == XFS_IOC_FD_TO_HANDLE) अणु
		f = fdget(hreq->fd);
		अगर (!f.file)
			वापस -EBADF;
		inode = file_inode(f.file);
	पूर्ण अन्यथा अणु
		error = user_path_at(AT_FDCWD, hreq->path, 0, &path);
		अगर (error)
			वापस error;
		inode = d_inode(path.dentry);
	पूर्ण
	ip = XFS_I(inode);

	/*
	 * We can only generate handles क्रम inodes residing on a XFS fileप्रणाली,
	 * and only क्रम regular files, directories or symbolic links.
	 */
	error = -EINVAL;
	अगर (inode->i_sb->s_magic != XFS_SB_MAGIC)
		जाओ out_put;

	error = -EBADF;
	अगर (!S_ISREG(inode->i_mode) &&
	    !S_ISसूची(inode->i_mode) &&
	    !S_ISLNK(inode->i_mode))
		जाओ out_put;


	स_नकल(&handle.ha_fsid, ip->i_mount->m_fixedfsid, माप(xfs_fsid_t));

	अगर (cmd == XFS_IOC_PATH_TO_FSHANDLE) अणु
		/*
		 * This handle only contains an fsid, zero the rest.
		 */
		स_रखो(&handle.ha_fid, 0, माप(handle.ha_fid));
		hsize = माप(xfs_fsid_t);
	पूर्ण अन्यथा अणु
		handle.ha_fid.fid_len = माप(xfs_fid_t) -
					माप(handle.ha_fid.fid_len);
		handle.ha_fid.fid_pad = 0;
		handle.ha_fid.fid_gen = inode->i_generation;
		handle.ha_fid.fid_ino = ip->i_ino;
		hsize = माप(xfs_handle_t);
	पूर्ण

	error = -EFAULT;
	अगर (copy_to_user(hreq->ohandle, &handle, hsize) ||
	    copy_to_user(hreq->ohandlen, &hsize, माप(__s32)))
		जाओ out_put;

	error = 0;

 out_put:
	अगर (cmd == XFS_IOC_FD_TO_HANDLE)
		fdput(f);
	अन्यथा
		path_put(&path);
	वापस error;
पूर्ण

/*
 * No need to करो permission checks on the various pathname components
 * as the handle operations are privileged.
 */
STATIC पूर्णांक
xfs_handle_acceptable(
	व्योम			*context,
	काष्ठा dentry		*dentry)
अणु
	वापस 1;
पूर्ण

/*
 * Convert userspace handle data पूर्णांकo a dentry.
 */
काष्ठा dentry *
xfs_handle_to_dentry(
	काष्ठा file		*parfilp,
	व्योम __user		*uhandle,
	u32			hlen)
अणु
	xfs_handle_t		handle;
	काष्ठा xfs_fid64	fid;

	/*
	 * Only allow handle खोलोs under a directory.
	 */
	अगर (!S_ISसूची(file_inode(parfilp)->i_mode))
		वापस ERR_PTR(-ENOTसूची);

	अगर (hlen != माप(xfs_handle_t))
		वापस ERR_PTR(-EINVAL);
	अगर (copy_from_user(&handle, uhandle, hlen))
		वापस ERR_PTR(-EFAULT);
	अगर (handle.ha_fid.fid_len !=
	    माप(handle.ha_fid) - माप(handle.ha_fid.fid_len))
		वापस ERR_PTR(-EINVAL);

	स_रखो(&fid, 0, माप(काष्ठा fid));
	fid.ino = handle.ha_fid.fid_ino;
	fid.gen = handle.ha_fid.fid_gen;

	वापस exportfs_decode_fh(parfilp->f_path.mnt, (काष्ठा fid *)&fid, 3,
			खाताID_INO32_GEN | XFS_खाताID_TYPE_64FLAG,
			xfs_handle_acceptable, शून्य);
पूर्ण

STATIC काष्ठा dentry *
xfs_handlereq_to_dentry(
	काष्ठा file		*parfilp,
	xfs_fsop_handlereq_t	*hreq)
अणु
	वापस xfs_handle_to_dentry(parfilp, hreq->ihandle, hreq->ihandlen);
पूर्ण

पूर्णांक
xfs_खोलो_by_handle(
	काष्ठा file		*parfilp,
	xfs_fsop_handlereq_t	*hreq)
अणु
	स्थिर काष्ठा cred	*cred = current_cred();
	पूर्णांक			error;
	पूर्णांक			fd;
	पूर्णांक			permflag;
	काष्ठा file		*filp;
	काष्ठा inode		*inode;
	काष्ठा dentry		*dentry;
	भ_शेषe_t			भ_शेषe;
	काष्ठा path		path;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	dentry = xfs_handlereq_to_dentry(parfilp, hreq);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);
	inode = d_inode(dentry);

	/* Restrict xfs_खोलो_by_handle to directories & regular files. */
	अगर (!(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode))) अणु
		error = -EPERM;
		जाओ out_dput;
	पूर्ण

#अगर BITS_PER_LONG != 32
	hreq->oflags |= O_LARGEखाता;
#पूर्ण_अगर

	permflag = hreq->oflags;
	भ_शेषe = OPEN_FMODE(permflag);
	अगर ((!(permflag & O_APPEND) || (permflag & O_TRUNC)) &&
	    (भ_शेषe & FMODE_WRITE) && IS_APPEND(inode)) अणु
		error = -EPERM;
		जाओ out_dput;
	पूर्ण

	अगर ((भ_शेषe & FMODE_WRITE) && IS_IMMUTABLE(inode)) अणु
		error = -EPERM;
		जाओ out_dput;
	पूर्ण

	/* Can't ग_लिखो directories. */
	अगर (S_ISसूची(inode->i_mode) && (भ_शेषe & FMODE_WRITE)) अणु
		error = -EISसूची;
		जाओ out_dput;
	पूर्ण

	fd = get_unused_fd_flags(0);
	अगर (fd < 0) अणु
		error = fd;
		जाओ out_dput;
	पूर्ण

	path.mnt = parfilp->f_path.mnt;
	path.dentry = dentry;
	filp = dentry_खोलो(&path, hreq->oflags, cred);
	dput(dentry);
	अगर (IS_ERR(filp)) अणु
		put_unused_fd(fd);
		वापस PTR_ERR(filp);
	पूर्ण

	अगर (S_ISREG(inode->i_mode)) अणु
		filp->f_flags |= O_NOATIME;
		filp->f_mode |= FMODE_NOCMTIME;
	पूर्ण

	fd_install(fd, filp);
	वापस fd;

 out_dput:
	dput(dentry);
	वापस error;
पूर्ण

पूर्णांक
xfs_पढ़ोlink_by_handle(
	काष्ठा file		*parfilp,
	xfs_fsop_handlereq_t	*hreq)
अणु
	काष्ठा dentry		*dentry;
	__u32			olen;
	पूर्णांक			error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	dentry = xfs_handlereq_to_dentry(parfilp, hreq);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	/* Restrict this handle operation to symlinks only. */
	अगर (!d_is_symlink(dentry)) अणु
		error = -EINVAL;
		जाओ out_dput;
	पूर्ण

	अगर (copy_from_user(&olen, hreq->ohandlen, माप(__u32))) अणु
		error = -EFAULT;
		जाओ out_dput;
	पूर्ण

	error = vfs_पढ़ोlink(dentry, hreq->ohandle, olen);

 out_dput:
	dput(dentry);
	वापस error;
पूर्ण

/*
 * Format an attribute and copy it out to the user's buffer.
 * Take care to check values and protect against them changing later,
 * we may be पढ़ोing them directly out of a user buffer.
 */
अटल व्योम
xfs_ioc_attr_put_listent(
	काष्ठा xfs_attr_list_context *context,
	पूर्णांक			flags,
	अचिन्हित अक्षर		*name,
	पूर्णांक			namelen,
	पूर्णांक			valuelen)
अणु
	काष्ठा xfs_attrlist	*alist = context->buffer;
	काष्ठा xfs_attrlist_ent	*aep;
	पूर्णांक			arraytop;

	ASSERT(!context->seen_enough);
	ASSERT(context->count >= 0);
	ASSERT(context->count < (ATTR_MAX_VALUELEN/8));
	ASSERT(context->firstu >= माप(*alist));
	ASSERT(context->firstu <= context->bufsize);

	/*
	 * Only list entries in the right namespace.
	 */
	अगर (context->attr_filter != (flags & XFS_ATTR_NSP_ONDISK_MASK))
		वापस;

	arraytop = माप(*alist) +
			context->count * माप(alist->al_offset[0]);

	/* decrement by the actual bytes used by the attr */
	context->firstu -= round_up(दुरत्व(काष्ठा xfs_attrlist_ent, a_name) +
			namelen + 1, माप(uपूर्णांक32_t));
	अगर (context->firstu < arraytop) अणु
		trace_xfs_attr_list_full(context);
		alist->al_more = 1;
		context->seen_enough = 1;
		वापस;
	पूर्ण

	aep = context->buffer + context->firstu;
	aep->a_valuelen = valuelen;
	स_नकल(aep->a_name, name, namelen);
	aep->a_name[namelen] = 0;
	alist->al_offset[context->count++] = context->firstu;
	alist->al_count = context->count;
	trace_xfs_attr_list_add(context);
पूर्ण

अटल अचिन्हित पूर्णांक
xfs_attr_filter(
	u32			ioc_flags)
अणु
	अगर (ioc_flags & XFS_IOC_ATTR_ROOT)
		वापस XFS_ATTR_ROOT;
	अगर (ioc_flags & XFS_IOC_ATTR_SECURE)
		वापस XFS_ATTR_SECURE;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
xfs_attr_flags(
	u32			ioc_flags)
अणु
	अगर (ioc_flags & XFS_IOC_ATTR_CREATE)
		वापस XATTR_CREATE;
	अगर (ioc_flags & XFS_IOC_ATTR_REPLACE)
		वापस XATTR_REPLACE;
	वापस 0;
पूर्ण

पूर्णांक
xfs_ioc_attr_list(
	काष्ठा xfs_inode		*dp,
	व्योम __user			*ubuf,
	पूर्णांक				bufsize,
	पूर्णांक				flags,
	काष्ठा xfs_attrlist_cursor __user *ucursor)
अणु
	काष्ठा xfs_attr_list_context	context = अणु पूर्ण;
	काष्ठा xfs_attrlist		*alist;
	व्योम				*buffer;
	पूर्णांक				error;

	अगर (bufsize < माप(काष्ठा xfs_attrlist) ||
	    bufsize > XFS_XATTR_LIST_MAX)
		वापस -EINVAL;

	/*
	 * Reject flags, only allow namespaces.
	 */
	अगर (flags & ~(XFS_IOC_ATTR_ROOT | XFS_IOC_ATTR_SECURE))
		वापस -EINVAL;
	अगर (flags == (XFS_IOC_ATTR_ROOT | XFS_IOC_ATTR_SECURE))
		वापस -EINVAL;

	/*
	 * Validate the cursor.
	 */
	अगर (copy_from_user(&context.cursor, ucursor, माप(context.cursor)))
		वापस -EFAULT;
	अगर (context.cursor.pad1 || context.cursor.pad2)
		वापस -EINVAL;
	अगर (!context.cursor.initted &&
	    (context.cursor.hashval || context.cursor.blkno ||
	     context.cursor.offset))
		वापस -EINVAL;

	buffer = kvzalloc(bufsize, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	/*
	 * Initialize the output buffer.
	 */
	context.dp = dp;
	context.resynch = 1;
	context.attr_filter = xfs_attr_filter(flags);
	context.buffer = buffer;
	context.bufsize = round_करोwn(bufsize, माप(uपूर्णांक32_t));
	context.firstu = context.bufsize;
	context.put_listent = xfs_ioc_attr_put_listent;

	alist = context.buffer;
	alist->al_count = 0;
	alist->al_more = 0;
	alist->al_offset[0] = context.bufsize;

	error = xfs_attr_list(&context);
	अगर (error)
		जाओ out_मुक्त;

	अगर (copy_to_user(ubuf, buffer, bufsize) ||
	    copy_to_user(ucursor, &context.cursor, माप(context.cursor)))
		error = -EFAULT;
out_मुक्त:
	kmem_मुक्त(buffer);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_attrlist_by_handle(
	काष्ठा file		*parfilp,
	काष्ठा xfs_fsop_attrlist_handlereq __user *p)
अणु
	काष्ठा xfs_fsop_attrlist_handlereq al_hreq;
	काष्ठा dentry		*dentry;
	पूर्णांक			error = -ENOMEM;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (copy_from_user(&al_hreq, p, माप(al_hreq)))
		वापस -EFAULT;

	dentry = xfs_handlereq_to_dentry(parfilp, &al_hreq.hreq);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	error = xfs_ioc_attr_list(XFS_I(d_inode(dentry)), al_hreq.buffer,
				  al_hreq.buflen, al_hreq.flags, &p->pos);
	dput(dentry);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_attrmulti_attr_get(
	काष्ठा inode		*inode,
	अचिन्हित अक्षर		*name,
	अचिन्हित अक्षर		__user *ubuf,
	uपूर्णांक32_t		*len,
	uपूर्णांक32_t		flags)
अणु
	काष्ठा xfs_da_args	args = अणु
		.dp		= XFS_I(inode),
		.attr_filter	= xfs_attr_filter(flags),
		.attr_flags	= xfs_attr_flags(flags),
		.name		= name,
		.namelen	= म_माप(name),
		.valuelen	= *len,
	पूर्ण;
	पूर्णांक			error;

	अगर (*len > XFS_XATTR_SIZE_MAX)
		वापस -EINVAL;

	error = xfs_attr_get(&args);
	अगर (error)
		जाओ out_kमुक्त;

	*len = args.valuelen;
	अगर (copy_to_user(ubuf, args.value, args.valuelen))
		error = -EFAULT;

out_kमुक्त:
	kmem_मुक्त(args.value);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_attrmulti_attr_set(
	काष्ठा inode		*inode,
	अचिन्हित अक्षर		*name,
	स्थिर अचिन्हित अक्षर	__user *ubuf,
	uपूर्णांक32_t		len,
	uपूर्णांक32_t		flags)
अणु
	काष्ठा xfs_da_args	args = अणु
		.dp		= XFS_I(inode),
		.attr_filter	= xfs_attr_filter(flags),
		.attr_flags	= xfs_attr_flags(flags),
		.name		= name,
		.namelen	= म_माप(name),
	पूर्ण;
	पूर्णांक			error;

	अगर (IS_IMMUTABLE(inode) || IS_APPEND(inode))
		वापस -EPERM;

	अगर (ubuf) अणु
		अगर (len > XFS_XATTR_SIZE_MAX)
			वापस -EINVAL;
		args.value = memdup_user(ubuf, len);
		अगर (IS_ERR(args.value))
			वापस PTR_ERR(args.value);
		args.valuelen = len;
	पूर्ण

	error = xfs_attr_set(&args);
	अगर (!error && (flags & XFS_IOC_ATTR_ROOT))
		xfs_क्रमget_acl(inode, name);
	kमुक्त(args.value);
	वापस error;
पूर्ण

पूर्णांक
xfs_ioc_attrmulti_one(
	काष्ठा file		*parfilp,
	काष्ठा inode		*inode,
	uपूर्णांक32_t		opcode,
	व्योम __user		*uname,
	व्योम __user		*value,
	uपूर्णांक32_t		*len,
	uपूर्णांक32_t		flags)
अणु
	अचिन्हित अक्षर		*name;
	पूर्णांक			error;

	अगर ((flags & XFS_IOC_ATTR_ROOT) && (flags & XFS_IOC_ATTR_SECURE))
		वापस -EINVAL;

	name = strndup_user(uname, MAXNAMELEN);
	अगर (IS_ERR(name))
		वापस PTR_ERR(name);

	चयन (opcode) अणु
	हाल ATTR_OP_GET:
		error = xfs_attrmulti_attr_get(inode, name, value, len, flags);
		अवरोध;
	हाल ATTR_OP_REMOVE:
		value = शून्य;
		*len = 0;
		/* fall through */
	हाल ATTR_OP_SET:
		error = mnt_want_ग_लिखो_file(parfilp);
		अगर (error)
			अवरोध;
		error = xfs_attrmulti_attr_set(inode, name, value, *len, flags);
		mnt_drop_ग_लिखो_file(parfilp);
		अवरोध;
	शेष:
		error = -EINVAL;
		अवरोध;
	पूर्ण

	kमुक्त(name);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_attrmulti_by_handle(
	काष्ठा file		*parfilp,
	व्योम			__user *arg)
अणु
	पूर्णांक			error;
	xfs_attr_multiop_t	*ops;
	xfs_fsop_attrmulti_handlereq_t am_hreq;
	काष्ठा dentry		*dentry;
	अचिन्हित पूर्णांक		i, size;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (copy_from_user(&am_hreq, arg, माप(xfs_fsop_attrmulti_handlereq_t)))
		वापस -EFAULT;

	/* overflow check */
	अगर (am_hreq.opcount >= पूर्णांक_उच्च / माप(xfs_attr_multiop_t))
		वापस -E2BIG;

	dentry = xfs_handlereq_to_dentry(parfilp, &am_hreq.hreq);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	error = -E2BIG;
	size = am_hreq.opcount * माप(xfs_attr_multiop_t);
	अगर (!size || size > 16 * PAGE_SIZE)
		जाओ out_dput;

	ops = memdup_user(am_hreq.ops, size);
	अगर (IS_ERR(ops)) अणु
		error = PTR_ERR(ops);
		जाओ out_dput;
	पूर्ण

	error = 0;
	क्रम (i = 0; i < am_hreq.opcount; i++) अणु
		ops[i].am_error = xfs_ioc_attrmulti_one(parfilp,
				d_inode(dentry), ops[i].am_opcode,
				ops[i].am_attrname, ops[i].am_attrvalue,
				&ops[i].am_length, ops[i].am_flags);
	पूर्ण

	अगर (copy_to_user(am_hreq.ops, ops, size))
		error = -EFAULT;

	kमुक्त(ops);
 out_dput:
	dput(dentry);
	वापस error;
पूर्ण

पूर्णांक
xfs_ioc_space(
	काष्ठा file		*filp,
	xfs_flock64_t		*bf)
अणु
	काष्ठा inode		*inode = file_inode(filp);
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा iattr		iattr;
	क्रमागत xfs_pपुनः_स्मृति_flags	flags = XFS_PREALLOC_CLEAR;
	uपूर्णांक			iolock = XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL;
	पूर्णांक			error;

	अगर (inode->i_flags & (S_IMMUTABLE|S_APPEND))
		वापस -EPERM;

	अगर (!(filp->f_mode & FMODE_WRITE))
		वापस -EBADF;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	अगर (xfs_is_always_cow_inode(ip))
		वापस -EOPNOTSUPP;

	अगर (filp->f_flags & O_DSYNC)
		flags |= XFS_PREALLOC_SYNC;
	अगर (filp->f_mode & FMODE_NOCMTIME)
		flags |= XFS_PREALLOC_INVISIBLE;

	error = mnt_want_ग_लिखो_file(filp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, iolock);
	error = xfs_अवरोध_layouts(inode, &iolock, BREAK_UNMAP);
	अगर (error)
		जाओ out_unlock;
	inode_dio_रुको(inode);

	चयन (bf->l_whence) अणु
	हाल 0: /*शुरू_से*/
		अवरोध;
	हाल 1: /*प्रस्तुत_से*/
		bf->l_start += filp->f_pos;
		अवरोध;
	हाल 2: /*अंत_से*/
		bf->l_start += XFS_ISIZE(ip);
		अवरोध;
	शेष:
		error = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (bf->l_start < 0 || bf->l_start > inode->i_sb->s_maxbytes) अणु
		error = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (bf->l_start > XFS_ISIZE(ip)) अणु
		error = xfs_alloc_file_space(ip, XFS_ISIZE(ip),
				bf->l_start - XFS_ISIZE(ip), 0);
		अगर (error)
			जाओ out_unlock;
	पूर्ण

	iattr.ia_valid = ATTR_SIZE;
	iattr.ia_size = bf->l_start;
	error = xfs_vn_setattr_size(file_mnt_user_ns(filp), file_dentry(filp),
				    &iattr);
	अगर (error)
		जाओ out_unlock;

	error = xfs_update_pपुनः_स्मृति_flags(ip, flags);

out_unlock:
	xfs_iunlock(ip, iolock);
	mnt_drop_ग_लिखो_file(filp);
	वापस error;
पूर्ण

/* Return 0 on success or positive error */
पूर्णांक
xfs_fsbulkstat_one_fmt(
	काष्ठा xfs_ibulk		*breq,
	स्थिर काष्ठा xfs_bulkstat	*bstat)
अणु
	काष्ठा xfs_bstat		bs1;

	xfs_bulkstat_to_bstat(breq->mp, &bs1, bstat);
	अगर (copy_to_user(breq->ubuffer, &bs1, माप(bs1)))
		वापस -EFAULT;
	वापस xfs_ibulk_advance(breq, माप(काष्ठा xfs_bstat));
पूर्ण

पूर्णांक
xfs_fsinumbers_fmt(
	काष्ठा xfs_ibulk		*breq,
	स्थिर काष्ठा xfs_inumbers	*igrp)
अणु
	काष्ठा xfs_inogrp		ig1;

	xfs_inumbers_to_inogrp(&ig1, igrp);
	अगर (copy_to_user(breq->ubuffer, &ig1, माप(काष्ठा xfs_inogrp)))
		वापस -EFAULT;
	वापस xfs_ibulk_advance(breq, माप(काष्ठा xfs_inogrp));
पूर्ण

STATIC पूर्णांक
xfs_ioc_fsbulkstat(
	काष्ठा file		*file,
	अचिन्हित पूर्णांक		cmd,
	व्योम			__user *arg)
अणु
	काष्ठा xfs_mount	*mp = XFS_I(file_inode(file))->i_mount;
	काष्ठा xfs_fsop_bulkreq	bulkreq;
	काष्ठा xfs_ibulk	breq = अणु
		.mp		= mp,
		.mnt_userns	= file_mnt_user_ns(file),
		.ocount		= 0,
	पूर्ण;
	xfs_ino_t		lastino;
	पूर्णांक			error;

	/* करोne = 1 अगर there are more stats to get and अगर bulkstat */
	/* should be called again (unused here, but used in dmapi) */

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	अगर (copy_from_user(&bulkreq, arg, माप(काष्ठा xfs_fsop_bulkreq)))
		वापस -EFAULT;

	अगर (copy_from_user(&lastino, bulkreq.lastip, माप(__s64)))
		वापस -EFAULT;

	अगर (bulkreq.icount <= 0)
		वापस -EINVAL;

	अगर (bulkreq.ubuffer == शून्य)
		वापस -EINVAL;

	breq.ubuffer = bulkreq.ubuffer;
	breq.icount = bulkreq.icount;

	/*
	 * FSBULKSTAT_SINGLE expects that *lastip contains the inode number
	 * that we want to stat.  However, FSINUMBERS and FSBULKSTAT expect
	 * that *lastip contains either zero or the number of the last inode to
	 * be examined by the previous call and वापस results starting with
	 * the next inode after that.  The new bulk request back end functions
	 * take the inode to start with, so we have to compute the startino
	 * parameter from lastino to मुख्यtain correct function.  lastino == 0
	 * is a special हाल because it has traditionally meant "first inode
	 * in fileप्रणाली".
	 */
	अगर (cmd == XFS_IOC_FSINUMBERS) अणु
		breq.startino = lastino ? lastino + 1 : 0;
		error = xfs_inumbers(&breq, xfs_fsinumbers_fmt);
		lastino = breq.startino - 1;
	पूर्ण अन्यथा अगर (cmd == XFS_IOC_FSBULKSTAT_SINGLE) अणु
		breq.startino = lastino;
		breq.icount = 1;
		error = xfs_bulkstat_one(&breq, xfs_fsbulkstat_one_fmt);
	पूर्ण अन्यथा अणु	/* XFS_IOC_FSBULKSTAT */
		breq.startino = lastino ? lastino + 1 : 0;
		error = xfs_bulkstat(&breq, xfs_fsbulkstat_one_fmt);
		lastino = breq.startino - 1;
	पूर्ण

	अगर (error)
		वापस error;

	अगर (bulkreq.lastip != शून्य &&
	    copy_to_user(bulkreq.lastip, &lastino, माप(xfs_ino_t)))
		वापस -EFAULT;

	अगर (bulkreq.ocount != शून्य &&
	    copy_to_user(bulkreq.ocount, &breq.ocount, माप(__s32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* Return 0 on success or positive error */
अटल पूर्णांक
xfs_bulkstat_fmt(
	काष्ठा xfs_ibulk		*breq,
	स्थिर काष्ठा xfs_bulkstat	*bstat)
अणु
	अगर (copy_to_user(breq->ubuffer, bstat, माप(काष्ठा xfs_bulkstat)))
		वापस -EFAULT;
	वापस xfs_ibulk_advance(breq, माप(काष्ठा xfs_bulkstat));
पूर्ण

/*
 * Check the incoming bulk request @hdr from userspace and initialize the
 * पूर्णांकernal @breq bulk request appropriately.  Returns 0 अगर the bulk request
 * should proceed; -ECANCELED अगर there's nothing to करो; or the usual
 * negative error code.
 */
अटल पूर्णांक
xfs_bulk_ireq_setup(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_bulk_ireq	*hdr,
	काष्ठा xfs_ibulk	*breq,
	व्योम __user		*ubuffer)
अणु
	अगर (hdr->icount == 0 ||
	    (hdr->flags & ~XFS_BULK_IREQ_FLAGS_ALL) ||
	    स_प्रथम_inv(hdr->reserved, 0, माप(hdr->reserved)))
		वापस -EINVAL;

	breq->startino = hdr->ino;
	breq->ubuffer = ubuffer;
	breq->icount = hdr->icount;
	breq->ocount = 0;
	breq->flags = 0;

	/*
	 * The @ino parameter is a special value, so we must look it up here.
	 * We're not allowed to have IREQ_AGNO, and we only वापस one inode
	 * worth of data.
	 */
	अगर (hdr->flags & XFS_BULK_IREQ_SPECIAL) अणु
		अगर (hdr->flags & XFS_BULK_IREQ_AGNO)
			वापस -EINVAL;

		चयन (hdr->ino) अणु
		हाल XFS_BULK_IREQ_SPECIAL_ROOT:
			hdr->ino = mp->m_sb.sb_rootino;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		breq->icount = 1;
	पूर्ण

	/*
	 * The IREQ_AGNO flag means that we only want results from a given AG.
	 * If @hdr->ino is zero, we start iterating in that AG.  If @hdr->ino is
	 * beyond the specअगरied AG then we वापस no results.
	 */
	अगर (hdr->flags & XFS_BULK_IREQ_AGNO) अणु
		अगर (hdr->agno >= mp->m_sb.sb_agcount)
			वापस -EINVAL;

		अगर (breq->startino == 0)
			breq->startino = XFS_AGINO_TO_INO(mp, hdr->agno, 0);
		अन्यथा अगर (XFS_INO_TO_AGNO(mp, breq->startino) < hdr->agno)
			वापस -EINVAL;

		breq->flags |= XFS_IBULK_SAME_AG;

		/* Asking क्रम an inode past the end of the AG?  We're करोne! */
		अगर (XFS_INO_TO_AGNO(mp, breq->startino) > hdr->agno)
			वापस -ECANCELED;
	पूर्ण अन्यथा अगर (hdr->agno)
		वापस -EINVAL;

	/* Asking क्रम an inode past the end of the FS?  We're करोne! */
	अगर (XFS_INO_TO_AGNO(mp, breq->startino) >= mp->m_sb.sb_agcount)
		वापस -ECANCELED;

	वापस 0;
पूर्ण

/*
 * Update the userspace bulk request @hdr to reflect the end state of the
 * पूर्णांकernal bulk request @breq.
 */
अटल व्योम
xfs_bulk_ireq_tearकरोwn(
	काष्ठा xfs_bulk_ireq	*hdr,
	काष्ठा xfs_ibulk	*breq)
अणु
	hdr->ino = breq->startino;
	hdr->ocount = breq->ocount;
पूर्ण

/* Handle the v5 bulkstat ioctl. */
STATIC पूर्णांक
xfs_ioc_bulkstat(
	काष्ठा file			*file,
	अचिन्हित पूर्णांक			cmd,
	काष्ठा xfs_bulkstat_req __user	*arg)
अणु
	काष्ठा xfs_mount		*mp = XFS_I(file_inode(file))->i_mount;
	काष्ठा xfs_bulk_ireq		hdr;
	काष्ठा xfs_ibulk		breq = अणु
		.mp			= mp,
		.mnt_userns		= file_mnt_user_ns(file),
	पूर्ण;
	पूर्णांक				error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	अगर (copy_from_user(&hdr, &arg->hdr, माप(hdr)))
		वापस -EFAULT;

	error = xfs_bulk_ireq_setup(mp, &hdr, &breq, arg->bulkstat);
	अगर (error == -ECANCELED)
		जाओ out_tearकरोwn;
	अगर (error < 0)
		वापस error;

	error = xfs_bulkstat(&breq, xfs_bulkstat_fmt);
	अगर (error)
		वापस error;

out_tearकरोwn:
	xfs_bulk_ireq_tearकरोwn(&hdr, &breq);
	अगर (copy_to_user(&arg->hdr, &hdr, माप(hdr)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_inumbers_fmt(
	काष्ठा xfs_ibulk		*breq,
	स्थिर काष्ठा xfs_inumbers	*igrp)
अणु
	अगर (copy_to_user(breq->ubuffer, igrp, माप(काष्ठा xfs_inumbers)))
		वापस -EFAULT;
	वापस xfs_ibulk_advance(breq, माप(काष्ठा xfs_inumbers));
पूर्ण

/* Handle the v5 inumbers ioctl. */
STATIC पूर्णांक
xfs_ioc_inumbers(
	काष्ठा xfs_mount		*mp,
	अचिन्हित पूर्णांक			cmd,
	काष्ठा xfs_inumbers_req __user	*arg)
अणु
	काष्ठा xfs_bulk_ireq		hdr;
	काष्ठा xfs_ibulk		breq = अणु
		.mp			= mp,
	पूर्ण;
	पूर्णांक				error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	अगर (copy_from_user(&hdr, &arg->hdr, माप(hdr)))
		वापस -EFAULT;

	error = xfs_bulk_ireq_setup(mp, &hdr, &breq, arg->inumbers);
	अगर (error == -ECANCELED)
		जाओ out_tearकरोwn;
	अगर (error < 0)
		वापस error;

	error = xfs_inumbers(&breq, xfs_inumbers_fmt);
	अगर (error)
		वापस error;

out_tearकरोwn:
	xfs_bulk_ireq_tearकरोwn(&hdr, &breq);
	अगर (copy_to_user(&arg->hdr, &hdr, माप(hdr)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_ioc_fsgeometry(
	काष्ठा xfs_mount	*mp,
	व्योम			__user *arg,
	पूर्णांक			काष्ठा_version)
अणु
	काष्ठा xfs_fsop_geom	fsgeo;
	माप_प्रकार			len;

	xfs_fs_geometry(&mp->m_sb, &fsgeo, काष्ठा_version);

	अगर (काष्ठा_version <= 3)
		len = माप(काष्ठा xfs_fsop_geom_v1);
	अन्यथा अगर (काष्ठा_version == 4)
		len = माप(काष्ठा xfs_fsop_geom_v4);
	अन्यथा अणु
		xfs_fsop_geom_health(mp, &fsgeo);
		len = माप(fsgeo);
	पूर्ण

	अगर (copy_to_user(arg, &fsgeo, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_ioc_ag_geometry(
	काष्ठा xfs_mount	*mp,
	व्योम			__user *arg)
अणु
	काष्ठा xfs_ag_geometry	ageo;
	पूर्णांक			error;

	अगर (copy_from_user(&ageo, arg, माप(ageo)))
		वापस -EFAULT;
	अगर (ageo.ag_flags)
		वापस -EINVAL;
	अगर (स_प्रथम_inv(&ageo.ag_reserved, 0, माप(ageo.ag_reserved)))
		वापस -EINVAL;

	error = xfs_ag_get_geometry(mp, ageo.ag_number, &ageo);
	अगर (error)
		वापस error;

	अगर (copy_to_user(arg, &ageo, माप(ageo)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * Linux extended inode flags पूर्णांकerface.
 */

अटल व्योम
xfs_fill_fsxattr(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	काष्ठा fileattr		*fa)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);

	fileattr_fill_xflags(fa, xfs_ip2xflags(ip));

	fa->fsx_extsize = XFS_FSB_TO_B(mp, ip->i_extsize);
	अगर (ip->i_dअगरlags2 & XFS_DIFLAG2_COWEXTSIZE)
		fa->fsx_cowextsize = XFS_FSB_TO_B(mp, ip->i_cowextsize);
	fa->fsx_projid = ip->i_projid;
	अगर (अगरp && !xfs_need_iपढ़ो_extents(अगरp))
		fa->fsx_nextents = xfs_iext_count(अगरp);
	अन्यथा
		fa->fsx_nextents = xfs_अगरork_nextents(अगरp);
पूर्ण

STATIC पूर्णांक
xfs_ioc_fsgetxattra(
	xfs_inode_t		*ip,
	व्योम			__user *arg)
अणु
	काष्ठा fileattr		fa;

	xfs_ilock(ip, XFS_ILOCK_SHARED);
	xfs_fill_fsxattr(ip, XFS_ATTR_FORK, &fa);
	xfs_iunlock(ip, XFS_ILOCK_SHARED);

	वापस copy_fsxattr_to_user(&fa, arg);
पूर्ण

पूर्णांक
xfs_fileattr_get(
	काष्ठा dentry		*dentry,
	काष्ठा fileattr		*fa)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(d_inode(dentry));

	अगर (d_is_special(dentry))
		वापस -ENOTTY;

	xfs_ilock(ip, XFS_ILOCK_SHARED);
	xfs_fill_fsxattr(ip, XFS_DATA_FORK, fa);
	xfs_iunlock(ip, XFS_ILOCK_SHARED);

	वापस 0;
पूर्ण

STATIC uपूर्णांक16_t
xfs_flags2dअगरlags(
	काष्ठा xfs_inode	*ip,
	अचिन्हित पूर्णांक		xflags)
अणु
	/* can't set PREALLOC this way, just preserve it */
	uपूर्णांक16_t		di_flags =
		(ip->i_dअगरlags & XFS_DIFLAG_PREALLOC);

	अगर (xflags & FS_XFLAG_IMMUTABLE)
		di_flags |= XFS_DIFLAG_IMMUTABLE;
	अगर (xflags & FS_XFLAG_APPEND)
		di_flags |= XFS_DIFLAG_APPEND;
	अगर (xflags & FS_XFLAG_SYNC)
		di_flags |= XFS_DIFLAG_SYNC;
	अगर (xflags & FS_XFLAG_NOATIME)
		di_flags |= XFS_DIFLAG_NOATIME;
	अगर (xflags & FS_XFLAG_NODUMP)
		di_flags |= XFS_DIFLAG_NODUMP;
	अगर (xflags & FS_XFLAG_NODEFRAG)
		di_flags |= XFS_DIFLAG_NODEFRAG;
	अगर (xflags & FS_XFLAG_खाताSTREAM)
		di_flags |= XFS_DIFLAG_खाताSTREAM;
	अगर (S_ISसूची(VFS_I(ip)->i_mode)) अणु
		अगर (xflags & FS_XFLAG_RTINHERIT)
			di_flags |= XFS_DIFLAG_RTINHERIT;
		अगर (xflags & FS_XFLAG_NOSYMLINKS)
			di_flags |= XFS_DIFLAG_NOSYMLINKS;
		अगर (xflags & FS_XFLAG_EXTSZINHERIT)
			di_flags |= XFS_DIFLAG_EXTSZINHERIT;
		अगर (xflags & FS_XFLAG_PROJINHERIT)
			di_flags |= XFS_DIFLAG_PROJINHERIT;
	पूर्ण अन्यथा अगर (S_ISREG(VFS_I(ip)->i_mode)) अणु
		अगर (xflags & FS_XFLAG_REALTIME)
			di_flags |= XFS_DIFLAG_REALTIME;
		अगर (xflags & FS_XFLAG_EXTSIZE)
			di_flags |= XFS_DIFLAG_EXTSIZE;
	पूर्ण

	वापस di_flags;
पूर्ण

STATIC uपूर्णांक64_t
xfs_flags2dअगरlags2(
	काष्ठा xfs_inode	*ip,
	अचिन्हित पूर्णांक		xflags)
अणु
	uपूर्णांक64_t		di_flags2 =
		(ip->i_dअगरlags2 & (XFS_DIFLAG2_REFLINK |
				   XFS_DIFLAG2_BIGTIME));

	अगर (xflags & FS_XFLAG_DAX)
		di_flags2 |= XFS_DIFLAG2_DAX;
	अगर (xflags & FS_XFLAG_COWEXTSIZE)
		di_flags2 |= XFS_DIFLAG2_COWEXTSIZE;

	वापस di_flags2;
पूर्ण

अटल पूर्णांक
xfs_ioctl_setattr_xflags(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	काष्ठा fileattr		*fa)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	uपूर्णांक64_t		i_flags2;

	/* Can't change realसमय flag अगर any extents are allocated. */
	अगर ((ip->i_df.अगर_nextents || ip->i_delayed_blks) &&
	    XFS_IS_REALTIME_INODE(ip) != (fa->fsx_xflags & FS_XFLAG_REALTIME))
		वापस -EINVAL;

	/* If realसमय flag is set then must have realसमय device */
	अगर (fa->fsx_xflags & FS_XFLAG_REALTIME) अणु
		अगर (mp->m_sb.sb_rblocks == 0 || mp->m_sb.sb_rextsize == 0 ||
		    (ip->i_extsize % mp->m_sb.sb_rextsize))
			वापस -EINVAL;
	पूर्ण

	/* Clear reflink अगर we are actually able to set the rt flag. */
	अगर ((fa->fsx_xflags & FS_XFLAG_REALTIME) && xfs_is_reflink_inode(ip))
		ip->i_dअगरlags2 &= ~XFS_DIFLAG2_REFLINK;

	/* Don't allow us to set DAX mode क्रम a reflinked file क्रम now. */
	अगर ((fa->fsx_xflags & FS_XFLAG_DAX) && xfs_is_reflink_inode(ip))
		वापस -EINVAL;

	/* dअगरlags2 only valid क्रम v3 inodes. */
	i_flags2 = xfs_flags2dअगरlags2(ip, fa->fsx_xflags);
	अगर (i_flags2 && !xfs_sb_version_has_v3inode(&mp->m_sb))
		वापस -EINVAL;

	ip->i_dअगरlags = xfs_flags2dअगरlags(ip, fa->fsx_xflags);
	ip->i_dअगरlags2 = i_flags2;

	xfs_dअगरlags_to_अगरlags(ip, false);
	xfs_trans_ichgसमय(tp, ip, XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	XFS_STATS_INC(mp, xs_ig_attrchg);
	वापस 0;
पूर्ण

अटल व्योम
xfs_ioctl_setattr_prepare_dax(
	काष्ठा xfs_inode	*ip,
	काष्ठा fileattr		*fa)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा inode            *inode = VFS_I(ip);

	अगर (S_ISसूची(inode->i_mode))
		वापस;

	अगर ((mp->m_flags & XFS_MOUNT_DAX_ALWAYS) ||
	    (mp->m_flags & XFS_MOUNT_DAX_NEVER))
		वापस;

	अगर (((fa->fsx_xflags & FS_XFLAG_DAX) &&
	    !(ip->i_dअगरlags2 & XFS_DIFLAG2_DAX)) ||
	    (!(fa->fsx_xflags & FS_XFLAG_DAX) &&
	     (ip->i_dअगरlags2 & XFS_DIFLAG2_DAX)))
		d_mark_करोntcache(inode);
पूर्ण

/*
 * Set up the transaction काष्ठाure क्रम the setattr operation, checking that we
 * have permission to करो so. On success, वापस a clean transaction and the
 * inode locked exclusively पढ़ोy क्रम further operation specअगरic checks. On
 * failure, वापस an error without modअगरying or locking the inode.
 */
अटल काष्ठा xfs_trans *
xfs_ioctl_setattr_get_trans(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_dquot	*pdqp)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error = -EROFS;

	अगर (mp->m_flags & XFS_MOUNT_RDONLY)
		जाओ out_error;
	error = -EIO;
	अगर (XFS_FORCED_SHUTDOWN(mp))
		जाओ out_error;

	error = xfs_trans_alloc_ichange(ip, शून्य, शून्य, pdqp,
			capable(CAP_FOWNER), &tp);
	अगर (error)
		जाओ out_error;

	अगर (mp->m_flags & XFS_MOUNT_WSYNC)
		xfs_trans_set_sync(tp);

	वापस tp;

out_error:
	वापस ERR_PTR(error);
पूर्ण

/*
 * Validate a proposed extent size hपूर्णांक.  For regular files, the hपूर्णांक can only
 * be changed अगर no extents are allocated.
 */
अटल पूर्णांक
xfs_ioctl_setattr_check_extsize(
	काष्ठा xfs_inode	*ip,
	काष्ठा fileattr		*fa)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_failaddr_t		failaddr;
	uपूर्णांक16_t		new_dअगरlags;

	अगर (!fa->fsx_valid)
		वापस 0;

	अगर (S_ISREG(VFS_I(ip)->i_mode) && ip->i_df.अगर_nextents &&
	    XFS_FSB_TO_B(mp, ip->i_extsize) != fa->fsx_extsize)
		वापस -EINVAL;

	अगर (fa->fsx_extsize & mp->m_blockmask)
		वापस -EINVAL;

	new_dअगरlags = xfs_flags2dअगरlags(ip, fa->fsx_xflags);

	/*
	 * Inode verअगरiers on older kernels करोn't check that the extent size
	 * hपूर्णांक is an पूर्णांकeger multiple of the rt extent size on a directory
	 * with both rtinherit and extszinherit flags set.  Don't let sysadmins
	 * misconfigure directories.
	 */
	अगर ((new_dअगरlags & XFS_DIFLAG_RTINHERIT) &&
	    (new_dअगरlags & XFS_DIFLAG_EXTSZINHERIT)) अणु
		अचिन्हित पूर्णांक	rtextsize_bytes;

		rtextsize_bytes = XFS_FSB_TO_B(mp, mp->m_sb.sb_rextsize);
		अगर (fa->fsx_extsize % rtextsize_bytes)
			वापस -EINVAL;
	पूर्ण

	failaddr = xfs_inode_validate_extsize(ip->i_mount,
			XFS_B_TO_FSB(mp, fa->fsx_extsize),
			VFS_I(ip)->i_mode, new_dअगरlags);
	वापस failaddr != शून्य ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक
xfs_ioctl_setattr_check_cowextsize(
	काष्ठा xfs_inode	*ip,
	काष्ठा fileattr		*fa)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_failaddr_t		failaddr;
	uपूर्णांक64_t		new_dअगरlags2;
	uपूर्णांक16_t		new_dअगरlags;

	अगर (!fa->fsx_valid)
		वापस 0;

	अगर (fa->fsx_cowextsize & mp->m_blockmask)
		वापस -EINVAL;

	new_dअगरlags = xfs_flags2dअगरlags(ip, fa->fsx_xflags);
	new_dअगरlags2 = xfs_flags2dअगरlags2(ip, fa->fsx_xflags);

	failaddr = xfs_inode_validate_cowextsize(ip->i_mount,
			XFS_B_TO_FSB(mp, fa->fsx_cowextsize),
			VFS_I(ip)->i_mode, new_dअगरlags, new_dअगरlags2);
	वापस failaddr != शून्य ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक
xfs_ioctl_setattr_check_projid(
	काष्ठा xfs_inode	*ip,
	काष्ठा fileattr		*fa)
अणु
	अगर (!fa->fsx_valid)
		वापस 0;

	/* Disallow 32bit project ids अगर projid32bit feature is not enabled. */
	अगर (fa->fsx_projid > (uपूर्णांक16_t)-1 &&
	    !xfs_sb_version_hasprojid32bit(&ip->i_mount->m_sb))
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक
xfs_fileattr_set(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा dentry		*dentry,
	काष्ठा fileattr		*fa)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(d_inode(dentry));
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_dquot	*pdqp = शून्य;
	काष्ठा xfs_dquot	*olddquot = शून्य;
	पूर्णांक			error;

	trace_xfs_ioctl_setattr(ip);

	अगर (d_is_special(dentry))
		वापस -ENOTTY;

	अगर (!fa->fsx_valid) अणु
		अगर (fa->flags & ~(FS_IMMUTABLE_FL | FS_APPEND_FL |
				  FS_NOATIME_FL | FS_NODUMP_FL |
				  FS_SYNC_FL | FS_DAX_FL | FS_PROJINHERIT_FL))
			वापस -EOPNOTSUPP;
	पूर्ण

	error = xfs_ioctl_setattr_check_projid(ip, fa);
	अगर (error)
		वापस error;

	/*
	 * If disk quotas is on, we make sure that the dquots करो exist on disk,
	 * beक्रमe we start any other transactions. Trying to करो this later
	 * is messy. We करोn't care to take a पढ़ोlock to look at the ids
	 * in inode here, because we can't hold it across the trans_reserve.
	 * If the IDs करो change beक्रमe we take the ilock, we're covered
	 * because the i_*dquot fields will get updated anyway.
	 */
	अगर (fa->fsx_valid && XFS_IS_QUOTA_ON(mp)) अणु
		error = xfs_qm_vop_dqalloc(ip, VFS_I(ip)->i_uid,
				VFS_I(ip)->i_gid, fa->fsx_projid,
				XFS_QMOPT_PQUOTA, शून्य, शून्य, &pdqp);
		अगर (error)
			वापस error;
	पूर्ण

	xfs_ioctl_setattr_prepare_dax(ip, fa);

	tp = xfs_ioctl_setattr_get_trans(ip, pdqp);
	अगर (IS_ERR(tp)) अणु
		error = PTR_ERR(tp);
		जाओ error_मुक्त_dquots;
	पूर्ण

	error = xfs_ioctl_setattr_check_extsize(ip, fa);
	अगर (error)
		जाओ error_trans_cancel;

	error = xfs_ioctl_setattr_check_cowextsize(ip, fa);
	अगर (error)
		जाओ error_trans_cancel;

	error = xfs_ioctl_setattr_xflags(tp, ip, fa);
	अगर (error)
		जाओ error_trans_cancel;

	अगर (!fa->fsx_valid)
		जाओ skip_xattr;
	/*
	 * Change file ownership.  Must be the owner or privileged.  CAP_FSETID
	 * overrides the following restrictions:
	 *
	 * The set-user-ID and set-group-ID bits of a file will be cleared upon
	 * successful वापस from chown()
	 */

	अगर ((VFS_I(ip)->i_mode & (S_ISUID|S_ISGID)) &&
	    !capable_wrt_inode_uidgid(mnt_userns, VFS_I(ip), CAP_FSETID))
		VFS_I(ip)->i_mode &= ~(S_ISUID|S_ISGID);

	/* Change the ownerships and रेजिस्टर project quota modअगरications */
	अगर (ip->i_projid != fa->fsx_projid) अणु
		अगर (XFS_IS_QUOTA_RUNNING(mp) && XFS_IS_PQUOTA_ON(mp)) अणु
			olddquot = xfs_qm_vop_chown(tp, ip,
						&ip->i_pdquot, pdqp);
		पूर्ण
		ip->i_projid = fa->fsx_projid;
	पूर्ण

	/*
	 * Only set the extent size hपूर्णांक अगर we've alपढ़ोy determined that the
	 * extent size hपूर्णांक should be set on the inode. If no extent size flags
	 * are set on the inode then unconditionally clear the extent size hपूर्णांक.
	 */
	अगर (ip->i_dअगरlags & (XFS_DIFLAG_EXTSIZE | XFS_DIFLAG_EXTSZINHERIT))
		ip->i_extsize = XFS_B_TO_FSB(mp, fa->fsx_extsize);
	अन्यथा
		ip->i_extsize = 0;

	अगर (xfs_sb_version_has_v3inode(&mp->m_sb)) अणु
		अगर (ip->i_dअगरlags2 & XFS_DIFLAG2_COWEXTSIZE)
			ip->i_cowextsize = XFS_B_TO_FSB(mp, fa->fsx_cowextsize);
		अन्यथा
			ip->i_cowextsize = 0;
	पूर्ण

skip_xattr:
	error = xfs_trans_commit(tp);

	/*
	 * Release any dquot(s) the inode had kept beक्रमe chown.
	 */
	xfs_qm_dqrele(olddquot);
	xfs_qm_dqrele(pdqp);

	वापस error;

error_trans_cancel:
	xfs_trans_cancel(tp);
error_मुक्त_dquots:
	xfs_qm_dqrele(pdqp);
	वापस error;
पूर्ण

अटल bool
xfs_getbmap_क्रमmat(
	काष्ठा kgetbmap		*p,
	काष्ठा getbmapx __user	*u,
	माप_प्रकार			recsize)
अणु
	अगर (put_user(p->bmv_offset, &u->bmv_offset) ||
	    put_user(p->bmv_block, &u->bmv_block) ||
	    put_user(p->bmv_length, &u->bmv_length) ||
	    put_user(0, &u->bmv_count) ||
	    put_user(0, &u->bmv_entries))
		वापस false;
	अगर (recsize < माप(काष्ठा getbmapx))
		वापस true;
	अगर (put_user(0, &u->bmv_अगरlags) ||
	    put_user(p->bmv_oflags, &u->bmv_oflags) ||
	    put_user(0, &u->bmv_unused1) ||
	    put_user(0, &u->bmv_unused2))
		वापस false;
	वापस true;
पूर्ण

STATIC पूर्णांक
xfs_ioc_getbmap(
	काष्ठा file		*file,
	अचिन्हित पूर्णांक		cmd,
	व्योम			__user *arg)
अणु
	काष्ठा getbmapx		bmx = अणु 0 पूर्ण;
	काष्ठा kgetbmap		*buf;
	माप_प्रकार			recsize;
	पूर्णांक			error, i;

	चयन (cmd) अणु
	हाल XFS_IOC_GETBMAPA:
		bmx.bmv_अगरlags = BMV_IF_ATTRFORK;
		/*FALLTHRU*/
	हाल XFS_IOC_GETBMAP:
		/* काष्ठा getbmap is a strict subset of काष्ठा getbmapx. */
		recsize = माप(काष्ठा getbmap);
		अवरोध;
	हाल XFS_IOC_GETBMAPX:
		recsize = माप(काष्ठा getbmapx);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&bmx, arg, recsize))
		वापस -EFAULT;

	अगर (bmx.bmv_count < 2)
		वापस -EINVAL;
	अगर (bmx.bmv_count > अच_दीर्घ_उच्च / recsize)
		वापस -ENOMEM;

	buf = kvzalloc(bmx.bmv_count * माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	error = xfs_getbmap(XFS_I(file_inode(file)), &bmx, buf);
	अगर (error)
		जाओ out_मुक्त_buf;

	error = -EFAULT;
	अगर (copy_to_user(arg, &bmx, recsize))
		जाओ out_मुक्त_buf;
	arg += recsize;

	क्रम (i = 0; i < bmx.bmv_entries; i++) अणु
		अगर (!xfs_getbmap_क्रमmat(buf + i, arg, recsize))
			जाओ out_मुक्त_buf;
		arg += recsize;
	पूर्ण

	error = 0;
out_मुक्त_buf:
	kmem_मुक्त(buf);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_ioc_getfsmap(
	काष्ठा xfs_inode	*ip,
	काष्ठा fsmap_head	__user *arg)
अणु
	काष्ठा xfs_fsmap_head	xhead = अणु0पूर्ण;
	काष्ठा fsmap_head	head;
	काष्ठा fsmap		*recs;
	अचिन्हित पूर्णांक		count;
	__u32			last_flags = 0;
	bool			करोne = false;
	पूर्णांक			error;

	अगर (copy_from_user(&head, arg, माप(काष्ठा fsmap_head)))
		वापस -EFAULT;
	अगर (स_प्रथम_inv(head.fmh_reserved, 0, माप(head.fmh_reserved)) ||
	    स_प्रथम_inv(head.fmh_keys[0].fmr_reserved, 0,
		       माप(head.fmh_keys[0].fmr_reserved)) ||
	    स_प्रथम_inv(head.fmh_keys[1].fmr_reserved, 0,
		       माप(head.fmh_keys[1].fmr_reserved)))
		वापस -EINVAL;

	/*
	 * Use an पूर्णांकernal memory buffer so that we करोn't have to copy fsmap
	 * data to userspace जबतक holding locks.  Start by trying to allocate
	 * up to 128k क्रम the buffer, but fall back to a single page अगर needed.
	 */
	count = min_t(अचिन्हित पूर्णांक, head.fmh_count,
			131072 / माप(काष्ठा fsmap));
	recs = kvzalloc(count * माप(काष्ठा fsmap), GFP_KERNEL);
	अगर (!recs) अणु
		count = min_t(अचिन्हित पूर्णांक, head.fmh_count,
				PAGE_SIZE / माप(काष्ठा fsmap));
		recs = kvzalloc(count * माप(काष्ठा fsmap), GFP_KERNEL);
		अगर (!recs)
			वापस -ENOMEM;
	पूर्ण

	xhead.fmh_अगरlags = head.fmh_अगरlags;
	xfs_fsmap_to_पूर्णांकernal(&xhead.fmh_keys[0], &head.fmh_keys[0]);
	xfs_fsmap_to_पूर्णांकernal(&xhead.fmh_keys[1], &head.fmh_keys[1]);

	trace_xfs_getfsmap_low_key(ip->i_mount, &xhead.fmh_keys[0]);
	trace_xfs_getfsmap_high_key(ip->i_mount, &xhead.fmh_keys[1]);

	head.fmh_entries = 0;
	करो अणु
		काष्ठा fsmap __user	*user_recs;
		काष्ठा fsmap		*last_rec;

		user_recs = &arg->fmh_recs[head.fmh_entries];
		xhead.fmh_entries = 0;
		xhead.fmh_count = min_t(अचिन्हित पूर्णांक, count,
					head.fmh_count - head.fmh_entries);

		/* Run query, record how many entries we got. */
		error = xfs_getfsmap(ip->i_mount, &xhead, recs);
		चयन (error) अणु
		हाल 0:
			/*
			 * There are no more records in the result set.  Copy
			 * whatever we got to userspace and अवरोध out.
			 */
			करोne = true;
			अवरोध;
		हाल -ECANCELED:
			/*
			 * The पूर्णांकernal memory buffer is full.  Copy whatever
			 * records we got to userspace and go again अगर we have
			 * not yet filled the userspace buffer.
			 */
			error = 0;
			अवरोध;
		शेष:
			जाओ out_मुक्त;
		पूर्ण
		head.fmh_entries += xhead.fmh_entries;
		head.fmh_oflags = xhead.fmh_oflags;

		/*
		 * If the caller wanted a record count or there aren't any
		 * new records to वापस, we're करोne.
		 */
		अगर (head.fmh_count == 0 || xhead.fmh_entries == 0)
			अवरोध;

		/* Copy all the records we got out to userspace. */
		अगर (copy_to_user(user_recs, recs,
				 xhead.fmh_entries * माप(काष्ठा fsmap))) अणु
			error = -EFAULT;
			जाओ out_मुक्त;
		पूर्ण

		/* Remember the last record flags we copied to userspace. */
		last_rec = &recs[xhead.fmh_entries - 1];
		last_flags = last_rec->fmr_flags;

		/* Set up the low key क्रम the next iteration. */
		xfs_fsmap_to_पूर्णांकernal(&xhead.fmh_keys[0], last_rec);
		trace_xfs_getfsmap_low_key(ip->i_mount, &xhead.fmh_keys[0]);
	पूर्ण जबतक (!करोne && head.fmh_entries < head.fmh_count);

	/*
	 * If there are no more records in the query result set and we're not
	 * in counting mode, mark the last record वापसed with the LAST flag.
	 */
	अगर (करोne && head.fmh_count > 0 && head.fmh_entries > 0) अणु
		काष्ठा fsmap __user	*user_rec;

		last_flags |= FMR_OF_LAST;
		user_rec = &arg->fmh_recs[head.fmh_entries - 1];

		अगर (copy_to_user(&user_rec->fmr_flags, &last_flags,
					माप(last_flags))) अणु
			error = -EFAULT;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	/* copy back header */
	अगर (copy_to_user(arg, &head, माप(काष्ठा fsmap_head))) अणु
		error = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kmem_मुक्त(recs);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_ioc_scrub_metadata(
	काष्ठा file			*file,
	व्योम				__user *arg)
अणु
	काष्ठा xfs_scrub_metadata	scrub;
	पूर्णांक				error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (copy_from_user(&scrub, arg, माप(scrub)))
		वापस -EFAULT;

	error = xfs_scrub_metadata(file, &scrub);
	अगर (error)
		वापस error;

	अगर (copy_to_user(arg, &scrub, माप(scrub)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक
xfs_ioc_swapext(
	xfs_swapext_t	*sxp)
अणु
	xfs_inode_t     *ip, *tip;
	काष्ठा fd	f, पंचांगp;
	पूर्णांक		error = 0;

	/* Pull inक्रमmation क्रम the target fd */
	f = fdget((पूर्णांक)sxp->sx_fdtarget);
	अगर (!f.file) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!(f.file->f_mode & FMODE_WRITE) ||
	    !(f.file->f_mode & FMODE_READ) ||
	    (f.file->f_flags & O_APPEND)) अणु
		error = -EBADF;
		जाओ out_put_file;
	पूर्ण

	पंचांगp = fdget((पूर्णांक)sxp->sx_fdपंचांगp);
	अगर (!पंचांगp.file) अणु
		error = -EINVAL;
		जाओ out_put_file;
	पूर्ण

	अगर (!(पंचांगp.file->f_mode & FMODE_WRITE) ||
	    !(पंचांगp.file->f_mode & FMODE_READ) ||
	    (पंचांगp.file->f_flags & O_APPEND)) अणु
		error = -EBADF;
		जाओ out_put_पंचांगp_file;
	पूर्ण

	अगर (IS_SWAPखाता(file_inode(f.file)) ||
	    IS_SWAPखाता(file_inode(पंचांगp.file))) अणु
		error = -EINVAL;
		जाओ out_put_पंचांगp_file;
	पूर्ण

	/*
	 * We need to ensure that the fds passed in poपूर्णांक to XFS inodes
	 * beक्रमe we cast and access them as XFS काष्ठाures as we have no
	 * control over what the user passes us here.
	 */
	अगर (f.file->f_op != &xfs_file_operations ||
	    पंचांगp.file->f_op != &xfs_file_operations) अणु
		error = -EINVAL;
		जाओ out_put_पंचांगp_file;
	पूर्ण

	ip = XFS_I(file_inode(f.file));
	tip = XFS_I(file_inode(पंचांगp.file));

	अगर (ip->i_mount != tip->i_mount) अणु
		error = -EINVAL;
		जाओ out_put_पंचांगp_file;
	पूर्ण

	अगर (ip->i_ino == tip->i_ino) अणु
		error = -EINVAL;
		जाओ out_put_पंचांगp_file;
	पूर्ण

	अगर (XFS_FORCED_SHUTDOWN(ip->i_mount)) अणु
		error = -EIO;
		जाओ out_put_पंचांगp_file;
	पूर्ण

	error = xfs_swap_extents(ip, tip, sxp);

 out_put_पंचांगp_file:
	fdput(पंचांगp);
 out_put_file:
	fdput(f);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_ioc_getlabel(
	काष्ठा xfs_mount	*mp,
	अक्षर			__user *user_label)
अणु
	काष्ठा xfs_sb		*sbp = &mp->m_sb;
	अक्षर			label[XFSLABEL_MAX + 1];

	/* Paranoia */
	BUILD_BUG_ON(माप(sbp->sb_fname) > FSLABEL_MAX);

	/* 1 larger than sb_fname, so this ensures a trailing NUL अक्षर */
	स_रखो(label, 0, माप(label));
	spin_lock(&mp->m_sb_lock);
	म_नकलन(label, sbp->sb_fname, XFSLABEL_MAX);
	spin_unlock(&mp->m_sb_lock);

	अगर (copy_to_user(user_label, label, माप(label)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_ioc_setlabel(
	काष्ठा file		*filp,
	काष्ठा xfs_mount	*mp,
	अक्षर			__user *newlabel)
अणु
	काष्ठा xfs_sb		*sbp = &mp->m_sb;
	अक्षर			label[XFSLABEL_MAX + 1];
	माप_प्रकार			len;
	पूर्णांक			error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	/*
	 * The generic ioctl allows up to FSLABEL_MAX अक्षरs, but XFS is much
	 * smaller, at 12 bytes.  We copy one more to be sure we find the
	 * (required) शून्य अक्षरacter to test the incoming label length.
	 * NB: The on disk label करोesn't need to be null terminated.
	 */
	अगर (copy_from_user(label, newlabel, XFSLABEL_MAX + 1))
		वापस -EFAULT;
	len = strnlen(label, XFSLABEL_MAX + 1);
	अगर (len > माप(sbp->sb_fname))
		वापस -EINVAL;

	error = mnt_want_ग_लिखो_file(filp);
	अगर (error)
		वापस error;

	spin_lock(&mp->m_sb_lock);
	स_रखो(sbp->sb_fname, 0, माप(sbp->sb_fname));
	स_नकल(sbp->sb_fname, label, len);
	spin_unlock(&mp->m_sb_lock);

	/*
	 * Now we करो several things to satisfy userspace.
	 * In addition to normal logging of the primary superblock, we also
	 * immediately ग_लिखो these changes to sector zero क्रम the primary, then
	 * update all backup supers (as xfs_db करोes क्रम a label change), then
	 * invalidate the block device page cache.  This is so that any prior
	 * buffered पढ़ोs from userspace (i.e. from blkid) are invalidated,
	 * and userspace will see the newly-written label.
	 */
	error = xfs_sync_sb_buf(mp);
	अगर (error)
		जाओ out;
	/*
	 * growfs also updates backup supers so lock against that.
	 */
	mutex_lock(&mp->m_growlock);
	error = xfs_update_secondary_sbs(mp);
	mutex_unlock(&mp->m_growlock);

	invalidate_bdev(mp->m_ddev_targp->bt_bdev);

out:
	mnt_drop_ग_लिखो_file(filp);
	वापस error;
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_fs_eofblocks_from_user(
	काष्ठा xfs_fs_eofblocks		*src,
	काष्ठा xfs_eofblocks		*dst)
अणु
	अगर (src->eof_version != XFS_खातापूर्णBLOCKS_VERSION)
		वापस -EINVAL;

	अगर (src->eof_flags & ~XFS_खातापूर्ण_FLAGS_VALID)
		वापस -EINVAL;

	अगर (स_प्रथम_inv(&src->pad32, 0, माप(src->pad32)) ||
	    स_प्रथम_inv(src->pad64, 0, माप(src->pad64)))
		वापस -EINVAL;

	dst->eof_flags = src->eof_flags;
	dst->eof_prid = src->eof_prid;
	dst->eof_min_file_size = src->eof_min_file_size;

	dst->eof_uid = INVALID_UID;
	अगर (src->eof_flags & XFS_खातापूर्ण_FLAGS_UID) अणु
		dst->eof_uid = make_kuid(current_user_ns(), src->eof_uid);
		अगर (!uid_valid(dst->eof_uid))
			वापस -EINVAL;
	पूर्ण

	dst->eof_gid = INVALID_GID;
	अगर (src->eof_flags & XFS_खातापूर्ण_FLAGS_GID) अणु
		dst->eof_gid = make_kgid(current_user_ns(), src->eof_gid);
		अगर (!gid_valid(dst->eof_gid))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Note: some of the ioctl's वापस positive numbers as a
 * byte count indicating success, such as पढ़ोlink_by_handle.
 * So we करोn't "sign flip" like most other routines.  This means
 * true errors need to be वापसed as a negative value.
 */
दीर्घ
xfs_file_ioctl(
	काष्ठा file		*filp,
	अचिन्हित पूर्णांक		cmd,
	अचिन्हित दीर्घ		p)
अणु
	काष्ठा inode		*inode = file_inode(filp);
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	व्योम			__user *arg = (व्योम __user *)p;
	पूर्णांक			error;

	trace_xfs_file_ioctl(ip);

	चयन (cmd) अणु
	हाल FITRIM:
		वापस xfs_ioc_trim(mp, arg);
	हाल FS_IOC_GETFSLABEL:
		वापस xfs_ioc_getlabel(mp, arg);
	हाल FS_IOC_SETFSLABEL:
		वापस xfs_ioc_setlabel(filp, mp, arg);
	हाल XFS_IOC_ALLOCSP:
	हाल XFS_IOC_FREESP:
	हाल XFS_IOC_ALLOCSP64:
	हाल XFS_IOC_FREESP64: अणु
		xfs_flock64_t		bf;

		अगर (copy_from_user(&bf, arg, माप(bf)))
			वापस -EFAULT;
		वापस xfs_ioc_space(filp, &bf);
	पूर्ण
	हाल XFS_IOC_DIOINFO: अणु
		काष्ठा xfs_buftarg	*target = xfs_inode_buftarg(ip);
		काष्ठा dioattr		da;

		da.d_mem =  da.d_miniosz = target->bt_logical_sectorsize;
		da.d_maxiosz = पूर्णांक_उच्च & ~(da.d_miniosz - 1);

		अगर (copy_to_user(arg, &da, माप(da)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	हाल XFS_IOC_FSBULKSTAT_SINGLE:
	हाल XFS_IOC_FSBULKSTAT:
	हाल XFS_IOC_FSINUMBERS:
		वापस xfs_ioc_fsbulkstat(filp, cmd, arg);

	हाल XFS_IOC_BULKSTAT:
		वापस xfs_ioc_bulkstat(filp, cmd, arg);
	हाल XFS_IOC_INUMBERS:
		वापस xfs_ioc_inumbers(mp, cmd, arg);

	हाल XFS_IOC_FSGEOMETRY_V1:
		वापस xfs_ioc_fsgeometry(mp, arg, 3);
	हाल XFS_IOC_FSGEOMETRY_V4:
		वापस xfs_ioc_fsgeometry(mp, arg, 4);
	हाल XFS_IOC_FSGEOMETRY:
		वापस xfs_ioc_fsgeometry(mp, arg, 5);

	हाल XFS_IOC_AG_GEOMETRY:
		वापस xfs_ioc_ag_geometry(mp, arg);

	हाल XFS_IOC_GETVERSION:
		वापस put_user(inode->i_generation, (पूर्णांक __user *)arg);

	हाल XFS_IOC_FSGETXATTRA:
		वापस xfs_ioc_fsgetxattra(ip, arg);

	हाल XFS_IOC_GETBMAP:
	हाल XFS_IOC_GETBMAPA:
	हाल XFS_IOC_GETBMAPX:
		वापस xfs_ioc_getbmap(filp, cmd, arg);

	हाल FS_IOC_GETFSMAP:
		वापस xfs_ioc_getfsmap(ip, arg);

	हाल XFS_IOC_SCRUB_METADATA:
		वापस xfs_ioc_scrub_metadata(filp, arg);

	हाल XFS_IOC_FD_TO_HANDLE:
	हाल XFS_IOC_PATH_TO_HANDLE:
	हाल XFS_IOC_PATH_TO_FSHANDLE: अणु
		xfs_fsop_handlereq_t	hreq;

		अगर (copy_from_user(&hreq, arg, माप(hreq)))
			वापस -EFAULT;
		वापस xfs_find_handle(cmd, &hreq);
	पूर्ण
	हाल XFS_IOC_OPEN_BY_HANDLE: अणु
		xfs_fsop_handlereq_t	hreq;

		अगर (copy_from_user(&hreq, arg, माप(xfs_fsop_handlereq_t)))
			वापस -EFAULT;
		वापस xfs_खोलो_by_handle(filp, &hreq);
	पूर्ण

	हाल XFS_IOC_READLINK_BY_HANDLE: अणु
		xfs_fsop_handlereq_t	hreq;

		अगर (copy_from_user(&hreq, arg, माप(xfs_fsop_handlereq_t)))
			वापस -EFAULT;
		वापस xfs_पढ़ोlink_by_handle(filp, &hreq);
	पूर्ण
	हाल XFS_IOC_ATTRLIST_BY_HANDLE:
		वापस xfs_attrlist_by_handle(filp, arg);

	हाल XFS_IOC_ATTRMULTI_BY_HANDLE:
		वापस xfs_attrmulti_by_handle(filp, arg);

	हाल XFS_IOC_SWAPEXT: अणु
		काष्ठा xfs_swapext	sxp;

		अगर (copy_from_user(&sxp, arg, माप(xfs_swapext_t)))
			वापस -EFAULT;
		error = mnt_want_ग_लिखो_file(filp);
		अगर (error)
			वापस error;
		error = xfs_ioc_swapext(&sxp);
		mnt_drop_ग_लिखो_file(filp);
		वापस error;
	पूर्ण

	हाल XFS_IOC_FSCOUNTS: अणु
		xfs_fsop_counts_t out;

		xfs_fs_counts(mp, &out);

		अगर (copy_to_user(arg, &out, माप(out)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	हाल XFS_IOC_SET_RESBLKS: अणु
		xfs_fsop_resblks_t inout;
		uपूर्णांक64_t	   in;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (mp->m_flags & XFS_MOUNT_RDONLY)
			वापस -EROFS;

		अगर (copy_from_user(&inout, arg, माप(inout)))
			वापस -EFAULT;

		error = mnt_want_ग_लिखो_file(filp);
		अगर (error)
			वापस error;

		/* input parameter is passed in resblks field of काष्ठाure */
		in = inout.resblks;
		error = xfs_reserve_blocks(mp, &in, &inout);
		mnt_drop_ग_लिखो_file(filp);
		अगर (error)
			वापस error;

		अगर (copy_to_user(arg, &inout, माप(inout)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	हाल XFS_IOC_GET_RESBLKS: अणु
		xfs_fsop_resblks_t out;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		error = xfs_reserve_blocks(mp, शून्य, &out);
		अगर (error)
			वापस error;

		अगर (copy_to_user(arg, &out, माप(out)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल XFS_IOC_FSGROWFSDATA: अणु
		काष्ठा xfs_growfs_data in;

		अगर (copy_from_user(&in, arg, माप(in)))
			वापस -EFAULT;

		error = mnt_want_ग_लिखो_file(filp);
		अगर (error)
			वापस error;
		error = xfs_growfs_data(mp, &in);
		mnt_drop_ग_लिखो_file(filp);
		वापस error;
	पूर्ण

	हाल XFS_IOC_FSGROWFSLOG: अणु
		काष्ठा xfs_growfs_log in;

		अगर (copy_from_user(&in, arg, माप(in)))
			वापस -EFAULT;

		error = mnt_want_ग_लिखो_file(filp);
		अगर (error)
			वापस error;
		error = xfs_growfs_log(mp, &in);
		mnt_drop_ग_लिखो_file(filp);
		वापस error;
	पूर्ण

	हाल XFS_IOC_FSGROWFSRT: अणु
		xfs_growfs_rt_t in;

		अगर (copy_from_user(&in, arg, माप(in)))
			वापस -EFAULT;

		error = mnt_want_ग_लिखो_file(filp);
		अगर (error)
			वापस error;
		error = xfs_growfs_rt(mp, &in);
		mnt_drop_ग_लिखो_file(filp);
		वापस error;
	पूर्ण

	हाल XFS_IOC_GOINGDOWN: अणु
		uपूर्णांक32_t in;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (get_user(in, (uपूर्णांक32_t __user *)arg))
			वापस -EFAULT;

		वापस xfs_fs_goingकरोwn(mp, in);
	पूर्ण

	हाल XFS_IOC_ERROR_INJECTION: अणु
		xfs_error_injection_t in;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(&in, arg, माप(in)))
			वापस -EFAULT;

		वापस xfs_errortag_add(mp, in.errtag);
	पूर्ण

	हाल XFS_IOC_ERROR_CLEARALL:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		वापस xfs_errortag_clearall(mp);

	हाल XFS_IOC_FREE_खातापूर्णBLOCKS: अणु
		काष्ठा xfs_fs_eofblocks eofb;
		काष्ठा xfs_eofblocks keofb;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (mp->m_flags & XFS_MOUNT_RDONLY)
			वापस -EROFS;

		अगर (copy_from_user(&eofb, arg, माप(eofb)))
			वापस -EFAULT;

		error = xfs_fs_eofblocks_from_user(&eofb, &keofb);
		अगर (error)
			वापस error;

		trace_xfs_ioc_मुक्त_eofblocks(mp, &keofb, _RET_IP_);

		sb_start_ग_लिखो(mp->m_super);
		error = xfs_blockgc_मुक्त_space(mp, &keofb);
		sb_end_ग_लिखो(mp->m_super);
		वापस error;
	पूर्ण

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण
