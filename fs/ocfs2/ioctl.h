<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ioctl.h
 *
 * Function prototypes
 *
 * Copyright (C) 2006 Herbert Poetzl
 *
 */

#अगर_अघोषित OCFS2_IOCTL_PROTO_H
#घोषणा OCFS2_IOCTL_PROTO_H

पूर्णांक ocfs2_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक ocfs2_fileattr_set(काष्ठा user_namespace *mnt_userns,
		       काष्ठा dentry *dentry, काष्ठा fileattr *fa);
दीर्घ ocfs2_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ ocfs2_compat_ioctl(काष्ठा file *file, अचिन्हित cmd, अचिन्हित दीर्घ arg);

#पूर्ण_अगर /* OCFS2_IOCTL_PROTO_H */
