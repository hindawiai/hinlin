<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2004-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश <linux/mount.h>
#समावेश <linux/fsmap.h>
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_iwalk.h"
#समावेश "xfs_itable.h"
#समावेश "xfs_fsops.h"
#समावेश "xfs_rtalloc.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_ioctl.h"
#समावेश "xfs_ioctl32.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_sb.h"

#घोषणा  _NATIVE_IOC(cmd, type) \
	  _IOC(_IOC_सूची(cmd), _IOC_TYPE(cmd), _IOC_NR(cmd), माप(type))

#अगर_घोषित BROKEN_X86_ALIGNMENT
STATIC पूर्णांक
xfs_compat_flock64_copyin(
	xfs_flock64_t		*bf,
	compat_xfs_flock64_t	__user *arg32)
अणु
	अगर (get_user(bf->l_type,	&arg32->l_type) ||
	    get_user(bf->l_whence,	&arg32->l_whence) ||
	    get_user(bf->l_start,	&arg32->l_start) ||
	    get_user(bf->l_len,		&arg32->l_len) ||
	    get_user(bf->l_sysid,	&arg32->l_sysid) ||
	    get_user(bf->l_pid,		&arg32->l_pid) ||
	    copy_from_user(bf->l_pad,	&arg32->l_pad,	4*माप(u32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_compat_ioc_fsgeometry_v1(
	काष्ठा xfs_mount	  *mp,
	compat_xfs_fsop_geom_v1_t __user *arg32)
अणु
	काष्ठा xfs_fsop_geom	  fsgeo;

	xfs_fs_geometry(&mp->m_sb, &fsgeo, 3);
	/* The 32-bit variant simply has some padding at the end */
	अगर (copy_to_user(arg32, &fsgeo, माप(काष्ठा compat_xfs_fsop_geom_v1)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_compat_growfs_data_copyin(
	काष्ठा xfs_growfs_data	 *in,
	compat_xfs_growfs_data_t __user *arg32)
अणु
	अगर (get_user(in->newblocks, &arg32->newblocks) ||
	    get_user(in->imaxpct,   &arg32->imaxpct))
		वापस -EFAULT;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_compat_growfs_rt_copyin(
	काष्ठा xfs_growfs_rt	 *in,
	compat_xfs_growfs_rt_t	__user *arg32)
अणु
	अगर (get_user(in->newblocks, &arg32->newblocks) ||
	    get_user(in->extsize,   &arg32->extsize))
		वापस -EFAULT;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_fsinumbers_fmt_compat(
	काष्ठा xfs_ibulk		*breq,
	स्थिर काष्ठा xfs_inumbers	*ig)
अणु
	काष्ठा compat_xfs_inogrp __user	*p32 = breq->ubuffer;
	काष्ठा xfs_inogrp		ig1;
	काष्ठा xfs_inogrp		*igrp = &ig1;

	xfs_inumbers_to_inogrp(&ig1, ig);

	अगर (put_user(igrp->xi_startino,   &p32->xi_startino) ||
	    put_user(igrp->xi_alloccount, &p32->xi_alloccount) ||
	    put_user(igrp->xi_allocmask,  &p32->xi_allocmask))
		वापस -EFAULT;

	वापस xfs_ibulk_advance(breq, माप(काष्ठा compat_xfs_inogrp));
पूर्ण

#अन्यथा
#घोषणा xfs_fsinumbers_fmt_compat xfs_fsinumbers_fmt
#पूर्ण_अगर	/* BROKEN_X86_ALIGNMENT */

STATIC पूर्णांक
xfs_ioctl32_bsसमय_copyin(
	xfs_bsसमय_प्रकार		*bsसमय,
	compat_xfs_bsसमय_प्रकार	__user *bsसमय32)
अणु
	old_समय32_t		sec32;	/* tv_sec dअगरfers on 64 vs. 32 */

	अगर (get_user(sec32,		&bsसमय32->tv_sec)	||
	    get_user(bsसमय->tv_nsec,	&bsसमय32->tv_nsec))
		वापस -EFAULT;
	bsसमय->tv_sec = sec32;
	वापस 0;
पूर्ण

/*
 * काष्ठा xfs_bstat has dअगरfering alignment on पूर्णांकel, & bsसमय_प्रकार sizes
 * everywhere
 */
STATIC पूर्णांक
xfs_ioctl32_bstat_copyin(
	काष्ठा xfs_bstat		*bstat,
	काष्ठा compat_xfs_bstat	__user	*bstat32)
अणु
	अगर (get_user(bstat->bs_ino,	&bstat32->bs_ino)	||
	    get_user(bstat->bs_mode,	&bstat32->bs_mode)	||
	    get_user(bstat->bs_nlink,	&bstat32->bs_nlink)	||
	    get_user(bstat->bs_uid,	&bstat32->bs_uid)	||
	    get_user(bstat->bs_gid,	&bstat32->bs_gid)	||
	    get_user(bstat->bs_rdev,	&bstat32->bs_rdev)	||
	    get_user(bstat->bs_blksize,	&bstat32->bs_blksize)	||
	    get_user(bstat->bs_size,	&bstat32->bs_size)	||
	    xfs_ioctl32_bsसमय_copyin(&bstat->bs_aसमय, &bstat32->bs_aसमय) ||
	    xfs_ioctl32_bsसमय_copyin(&bstat->bs_mसमय, &bstat32->bs_mसमय) ||
	    xfs_ioctl32_bsसमय_copyin(&bstat->bs_स_समय, &bstat32->bs_स_समय) ||
	    get_user(bstat->bs_blocks,	&bstat32->bs_size)	||
	    get_user(bstat->bs_xflags,	&bstat32->bs_size)	||
	    get_user(bstat->bs_extsize,	&bstat32->bs_extsize)	||
	    get_user(bstat->bs_extents,	&bstat32->bs_extents)	||
	    get_user(bstat->bs_gen,	&bstat32->bs_gen)	||
	    get_user(bstat->bs_projid_lo, &bstat32->bs_projid_lo) ||
	    get_user(bstat->bs_projid_hi, &bstat32->bs_projid_hi) ||
	    get_user(bstat->bs_विभाजनoff,	&bstat32->bs_विभाजनoff)	||
	    get_user(bstat->bs_dmevmask, &bstat32->bs_dmevmask)	||
	    get_user(bstat->bs_dmstate,	&bstat32->bs_dmstate)	||
	    get_user(bstat->bs_aextents, &bstat32->bs_aextents))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* XFS_IOC_FSBULKSTAT and मित्रs */

STATIC पूर्णांक
xfs_bsसमय_store_compat(
	compat_xfs_bsसमय_प्रकार	__user *p32,
	स्थिर xfs_bsसमय_प्रकार	*p)
अणु
	__s32			sec32;

	sec32 = p->tv_sec;
	अगर (put_user(sec32, &p32->tv_sec) ||
	    put_user(p->tv_nsec, &p32->tv_nsec))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* Return 0 on success or positive error (to xfs_bulkstat()) */
STATIC पूर्णांक
xfs_fsbulkstat_one_fmt_compat(
	काष्ठा xfs_ibulk		*breq,
	स्थिर काष्ठा xfs_bulkstat	*bstat)
अणु
	काष्ठा compat_xfs_bstat	__user	*p32 = breq->ubuffer;
	काष्ठा xfs_bstat		bs1;
	काष्ठा xfs_bstat		*buffer = &bs1;

	xfs_bulkstat_to_bstat(breq->mp, &bs1, bstat);

	अगर (put_user(buffer->bs_ino,	  &p32->bs_ino)		||
	    put_user(buffer->bs_mode,	  &p32->bs_mode)	||
	    put_user(buffer->bs_nlink,	  &p32->bs_nlink)	||
	    put_user(buffer->bs_uid,	  &p32->bs_uid)		||
	    put_user(buffer->bs_gid,	  &p32->bs_gid)		||
	    put_user(buffer->bs_rdev,	  &p32->bs_rdev)	||
	    put_user(buffer->bs_blksize,  &p32->bs_blksize)	||
	    put_user(buffer->bs_size,	  &p32->bs_size)	||
	    xfs_bsसमय_store_compat(&p32->bs_aसमय, &buffer->bs_aसमय) ||
	    xfs_bsसमय_store_compat(&p32->bs_mसमय, &buffer->bs_mसमय) ||
	    xfs_bsसमय_store_compat(&p32->bs_स_समय, &buffer->bs_स_समय) ||
	    put_user(buffer->bs_blocks,	  &p32->bs_blocks)	||
	    put_user(buffer->bs_xflags,	  &p32->bs_xflags)	||
	    put_user(buffer->bs_extsize,  &p32->bs_extsize)	||
	    put_user(buffer->bs_extents,  &p32->bs_extents)	||
	    put_user(buffer->bs_gen,	  &p32->bs_gen)		||
	    put_user(buffer->bs_projid,	  &p32->bs_projid)	||
	    put_user(buffer->bs_projid_hi,	&p32->bs_projid_hi)	||
	    put_user(buffer->bs_विभाजनoff,  &p32->bs_विभाजनoff)	||
	    put_user(buffer->bs_dmevmask, &p32->bs_dmevmask)	||
	    put_user(buffer->bs_dmstate,  &p32->bs_dmstate)	||
	    put_user(buffer->bs_aextents, &p32->bs_aextents))
		वापस -EFAULT;

	वापस xfs_ibulk_advance(breq, माप(काष्ठा compat_xfs_bstat));
पूर्ण

/* copied from xfs_ioctl.c */
STATIC पूर्णांक
xfs_compat_ioc_fsbulkstat(
	काष्ठा file		*file,
	अचिन्हित पूर्णांक		  cmd,
	काष्ठा compat_xfs_fsop_bulkreq __user *p32)
अणु
	काष्ठा xfs_mount	*mp = XFS_I(file_inode(file))->i_mount;
	u32			addr;
	काष्ठा xfs_fsop_bulkreq	bulkreq;
	काष्ठा xfs_ibulk	breq = अणु
		.mp		= mp,
		.mnt_userns	= file_mnt_user_ns(file),
		.ocount		= 0,
	पूर्ण;
	xfs_ino_t		lastino;
	पूर्णांक			error;

	/*
	 * Output काष्ठाure handling functions.  Depending on the command,
	 * either the xfs_bstat and xfs_inogrp काष्ठाures are written out
	 * to userpace memory via bulkreq.ubuffer.  Normally the compat
	 * functions and काष्ठाure size are the correct ones to use ...
	 */
	inumbers_fmt_pf		inumbers_func = xfs_fsinumbers_fmt_compat;
	bulkstat_one_fmt_pf	bs_one_func = xfs_fsbulkstat_one_fmt_compat;

#अगर_घोषित CONFIG_X86_X32
	अगर (in_x32_syscall()) अणु
		/*
		 * ... but on x32 the input xfs_fsop_bulkreq has poपूर्णांकers
		 * which must be handled in the "compat" (32-bit) way, जबतक
		 * the xfs_bstat and xfs_inogrp काष्ठाures follow native 64-
		 * bit layout convention.  So adjust accordingly, otherwise
		 * the data written out in compat layout will not match what
		 * x32 userspace expects.
		 */
		inumbers_func = xfs_fsinumbers_fmt;
		bs_one_func = xfs_fsbulkstat_one_fmt;
	पूर्ण
#पूर्ण_अगर

	/* करोne = 1 अगर there are more stats to get and अगर bulkstat */
	/* should be called again (unused here, but used in dmapi) */

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	अगर (get_user(addr, &p32->lastip))
		वापस -EFAULT;
	bulkreq.lastip = compat_ptr(addr);
	अगर (get_user(bulkreq.icount, &p32->icount) ||
	    get_user(addr, &p32->ubuffer))
		वापस -EFAULT;
	bulkreq.ubuffer = compat_ptr(addr);
	अगर (get_user(addr, &p32->ocount))
		वापस -EFAULT;
	bulkreq.ocount = compat_ptr(addr);

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
	अगर (cmd == XFS_IOC_FSINUMBERS_32) अणु
		breq.startino = lastino ? lastino + 1 : 0;
		error = xfs_inumbers(&breq, inumbers_func);
		lastino = breq.startino - 1;
	पूर्ण अन्यथा अगर (cmd == XFS_IOC_FSBULKSTAT_SINGLE_32) अणु
		breq.startino = lastino;
		breq.icount = 1;
		error = xfs_bulkstat_one(&breq, bs_one_func);
		lastino = breq.startino;
	पूर्ण अन्यथा अगर (cmd == XFS_IOC_FSBULKSTAT_32) अणु
		breq.startino = lastino ? lastino + 1 : 0;
		error = xfs_bulkstat(&breq, bs_one_func);
		lastino = breq.startino - 1;
	पूर्ण अन्यथा अणु
		error = -EINVAL;
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

STATIC पूर्णांक
xfs_compat_handlereq_copyin(
	xfs_fsop_handlereq_t		*hreq,
	compat_xfs_fsop_handlereq_t	__user *arg32)
अणु
	compat_xfs_fsop_handlereq_t	hreq32;

	अगर (copy_from_user(&hreq32, arg32, माप(compat_xfs_fsop_handlereq_t)))
		वापस -EFAULT;

	hreq->fd = hreq32.fd;
	hreq->path = compat_ptr(hreq32.path);
	hreq->oflags = hreq32.oflags;
	hreq->ihandle = compat_ptr(hreq32.ihandle);
	hreq->ihandlen = hreq32.ihandlen;
	hreq->ohandle = compat_ptr(hreq32.ohandle);
	hreq->ohandlen = compat_ptr(hreq32.ohandlen);

	वापस 0;
पूर्ण

STATIC काष्ठा dentry *
xfs_compat_handlereq_to_dentry(
	काष्ठा file		*parfilp,
	compat_xfs_fsop_handlereq_t *hreq)
अणु
	वापस xfs_handle_to_dentry(parfilp,
			compat_ptr(hreq->ihandle), hreq->ihandlen);
पूर्ण

STATIC पूर्णांक
xfs_compat_attrlist_by_handle(
	काष्ठा file		*parfilp,
	compat_xfs_fsop_attrlist_handlereq_t __user *p)
अणु
	compat_xfs_fsop_attrlist_handlereq_t al_hreq;
	काष्ठा dentry		*dentry;
	पूर्णांक			error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (copy_from_user(&al_hreq, p, माप(al_hreq)))
		वापस -EFAULT;

	dentry = xfs_compat_handlereq_to_dentry(parfilp, &al_hreq.hreq);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	error = xfs_ioc_attr_list(XFS_I(d_inode(dentry)),
			compat_ptr(al_hreq.buffer), al_hreq.buflen,
			al_hreq.flags, &p->pos);
	dput(dentry);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_compat_attrmulti_by_handle(
	काष्ठा file				*parfilp,
	व्योम					__user *arg)
अणु
	पूर्णांक					error;
	compat_xfs_attr_multiop_t		*ops;
	compat_xfs_fsop_attrmulti_handlereq_t	am_hreq;
	काष्ठा dentry				*dentry;
	अचिन्हित पूर्णांक				i, size;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (copy_from_user(&am_hreq, arg,
			   माप(compat_xfs_fsop_attrmulti_handlereq_t)))
		वापस -EFAULT;

	/* overflow check */
	अगर (am_hreq.opcount >= पूर्णांक_उच्च / माप(compat_xfs_attr_multiop_t))
		वापस -E2BIG;

	dentry = xfs_compat_handlereq_to_dentry(parfilp, &am_hreq.hreq);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	error = -E2BIG;
	size = am_hreq.opcount * माप(compat_xfs_attr_multiop_t);
	अगर (!size || size > 16 * PAGE_SIZE)
		जाओ out_dput;

	ops = memdup_user(compat_ptr(am_hreq.ops), size);
	अगर (IS_ERR(ops)) अणु
		error = PTR_ERR(ops);
		जाओ out_dput;
	पूर्ण

	error = 0;
	क्रम (i = 0; i < am_hreq.opcount; i++) अणु
		ops[i].am_error = xfs_ioc_attrmulti_one(parfilp,
				d_inode(dentry), ops[i].am_opcode,
				compat_ptr(ops[i].am_attrname),
				compat_ptr(ops[i].am_attrvalue),
				&ops[i].am_length, ops[i].am_flags);
	पूर्ण

	अगर (copy_to_user(compat_ptr(am_hreq.ops), ops, size))
		error = -EFAULT;

	kमुक्त(ops);
 out_dput:
	dput(dentry);
	वापस error;
पूर्ण

दीर्घ
xfs_file_compat_ioctl(
	काष्ठा file		*filp,
	अचिन्हित		cmd,
	अचिन्हित दीर्घ		p)
अणु
	काष्ठा inode		*inode = file_inode(filp);
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	व्योम			__user *arg = compat_ptr(p);
	पूर्णांक			error;

	trace_xfs_file_compat_ioctl(ip);

	चयन (cmd) अणु
#अगर defined(BROKEN_X86_ALIGNMENT)
	हाल XFS_IOC_ALLOCSP_32:
	हाल XFS_IOC_FREESP_32:
	हाल XFS_IOC_ALLOCSP64_32:
	हाल XFS_IOC_FREESP64_32: अणु
		काष्ठा xfs_flock64	bf;

		अगर (xfs_compat_flock64_copyin(&bf, arg))
			वापस -EFAULT;
		cmd = _NATIVE_IOC(cmd, काष्ठा xfs_flock64);
		वापस xfs_ioc_space(filp, &bf);
	पूर्ण
	हाल XFS_IOC_FSGEOMETRY_V1_32:
		वापस xfs_compat_ioc_fsgeometry_v1(ip->i_mount, arg);
	हाल XFS_IOC_FSGROWFSDATA_32: अणु
		काष्ठा xfs_growfs_data	in;

		अगर (xfs_compat_growfs_data_copyin(&in, arg))
			वापस -EFAULT;
		error = mnt_want_ग_लिखो_file(filp);
		अगर (error)
			वापस error;
		error = xfs_growfs_data(ip->i_mount, &in);
		mnt_drop_ग_लिखो_file(filp);
		वापस error;
	पूर्ण
	हाल XFS_IOC_FSGROWFSRT_32: अणु
		काष्ठा xfs_growfs_rt	in;

		अगर (xfs_compat_growfs_rt_copyin(&in, arg))
			वापस -EFAULT;
		error = mnt_want_ग_लिखो_file(filp);
		अगर (error)
			वापस error;
		error = xfs_growfs_rt(ip->i_mount, &in);
		mnt_drop_ग_लिखो_file(filp);
		वापस error;
	पूर्ण
#पूर्ण_अगर
	/* दीर्घ changes size, but xfs only copiese out 32 bits */
	हाल XFS_IOC_GETVERSION_32:
		cmd = _NATIVE_IOC(cmd, दीर्घ);
		वापस xfs_file_ioctl(filp, cmd, p);
	हाल XFS_IOC_SWAPEXT_32: अणु
		काष्ठा xfs_swapext	  sxp;
		काष्ठा compat_xfs_swapext __user *sxu = arg;

		/* Bulk copy in up to the sx_stat field, then copy bstat */
		अगर (copy_from_user(&sxp, sxu,
				   दुरत्व(काष्ठा xfs_swapext, sx_stat)) ||
		    xfs_ioctl32_bstat_copyin(&sxp.sx_stat, &sxu->sx_stat))
			वापस -EFAULT;
		error = mnt_want_ग_लिखो_file(filp);
		अगर (error)
			वापस error;
		error = xfs_ioc_swapext(&sxp);
		mnt_drop_ग_लिखो_file(filp);
		वापस error;
	पूर्ण
	हाल XFS_IOC_FSBULKSTAT_32:
	हाल XFS_IOC_FSBULKSTAT_SINGLE_32:
	हाल XFS_IOC_FSINUMBERS_32:
		वापस xfs_compat_ioc_fsbulkstat(filp, cmd, arg);
	हाल XFS_IOC_FD_TO_HANDLE_32:
	हाल XFS_IOC_PATH_TO_HANDLE_32:
	हाल XFS_IOC_PATH_TO_FSHANDLE_32: अणु
		काष्ठा xfs_fsop_handlereq	hreq;

		अगर (xfs_compat_handlereq_copyin(&hreq, arg))
			वापस -EFAULT;
		cmd = _NATIVE_IOC(cmd, काष्ठा xfs_fsop_handlereq);
		वापस xfs_find_handle(cmd, &hreq);
	पूर्ण
	हाल XFS_IOC_OPEN_BY_HANDLE_32: अणु
		काष्ठा xfs_fsop_handlereq	hreq;

		अगर (xfs_compat_handlereq_copyin(&hreq, arg))
			वापस -EFAULT;
		वापस xfs_खोलो_by_handle(filp, &hreq);
	पूर्ण
	हाल XFS_IOC_READLINK_BY_HANDLE_32: अणु
		काष्ठा xfs_fsop_handlereq	hreq;

		अगर (xfs_compat_handlereq_copyin(&hreq, arg))
			वापस -EFAULT;
		वापस xfs_पढ़ोlink_by_handle(filp, &hreq);
	पूर्ण
	हाल XFS_IOC_ATTRLIST_BY_HANDLE_32:
		वापस xfs_compat_attrlist_by_handle(filp, arg);
	हाल XFS_IOC_ATTRMULTI_BY_HANDLE_32:
		वापस xfs_compat_attrmulti_by_handle(filp, arg);
	शेष:
		/* try the native version */
		वापस xfs_file_ioctl(filp, cmd, (अचिन्हित दीर्घ)arg);
	पूर्ण
पूर्ण
