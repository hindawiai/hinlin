<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2008 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_IOCTL_H__
#घोषणा __XFS_IOCTL_H__

काष्ठा xfs_bstat;
काष्ठा xfs_ibulk;
काष्ठा xfs_inogrp;


बाह्य पूर्णांक
xfs_ioc_space(
	काष्ठा file		*filp,
	xfs_flock64_t		*bf);

पूर्णांक
xfs_ioc_swapext(
	xfs_swapext_t	*sxp);

बाह्य पूर्णांक
xfs_find_handle(
	अचिन्हित पूर्णांक		cmd,
	xfs_fsop_handlereq_t	*hreq);

बाह्य पूर्णांक
xfs_खोलो_by_handle(
	काष्ठा file		*parfilp,
	xfs_fsop_handlereq_t	*hreq);

बाह्य पूर्णांक
xfs_पढ़ोlink_by_handle(
	काष्ठा file		*parfilp,
	xfs_fsop_handlereq_t	*hreq);

पूर्णांक xfs_ioc_attrmulti_one(काष्ठा file *parfilp, काष्ठा inode *inode,
		uपूर्णांक32_t opcode, व्योम __user *uname, व्योम __user *value,
		uपूर्णांक32_t *len, uपूर्णांक32_t flags);
पूर्णांक xfs_ioc_attr_list(काष्ठा xfs_inode *dp, व्योम __user *ubuf, पूर्णांक bufsize,
	पूर्णांक flags, काष्ठा xfs_attrlist_cursor __user *ucursor);

बाह्य काष्ठा dentry *
xfs_handle_to_dentry(
	काष्ठा file		*parfilp,
	व्योम __user		*uhandle,
	u32			hlen);

बाह्य पूर्णांक
xfs_fileattr_get(
	काष्ठा dentry		*dentry,
	काष्ठा fileattr		*fa);

बाह्य पूर्णांक
xfs_fileattr_set(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा dentry		*dentry,
	काष्ठा fileattr		*fa);

बाह्य दीर्घ
xfs_file_ioctl(
	काष्ठा file		*filp,
	अचिन्हित पूर्णांक		cmd,
	अचिन्हित दीर्घ		p);

बाह्य दीर्घ
xfs_file_compat_ioctl(
	काष्ठा file		*file,
	अचिन्हित पूर्णांक		cmd,
	अचिन्हित दीर्घ		arg);

पूर्णांक xfs_fsbulkstat_one_fmt(काष्ठा xfs_ibulk *breq,
			   स्थिर काष्ठा xfs_bulkstat *bstat);
पूर्णांक xfs_fsinumbers_fmt(काष्ठा xfs_ibulk *breq, स्थिर काष्ठा xfs_inumbers *igrp);

#पूर्ण_अगर
