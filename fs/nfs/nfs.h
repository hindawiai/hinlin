<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012 Netapp, Inc. All rights reserved.
 *
 * Function and काष्ठाures exported by the NFS module
 * क्रम use by NFS version-specअगरic modules.
 */
#अगर_अघोषित __LINUX_INTERNAL_NFS_H
#घोषणा __LINUX_INTERNAL_NFS_H

#समावेश <linux/fs.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/nfs_xdr.h>

काष्ठा nfs_subversion अणु
	काष्ठा module *owner;	/* THIS_MODULE poपूर्णांकer */
	काष्ठा file_प्रणाली_type *nfs_fs;	/* NFS fileप्रणाली type */
	स्थिर काष्ठा rpc_version *rpc_vers;	/* NFS version inक्रमmation */
	स्थिर काष्ठा nfs_rpc_ops *rpc_ops;	/* NFS operations */
	स्थिर काष्ठा super_operations *sops;	/* NFS Super operations */
	स्थिर काष्ठा xattr_handler **xattr;	/* NFS xattr handlers */
	काष्ठा list_head list;		/* List of NFS versions */
पूर्ण;

काष्ठा nfs_subversion *get_nfs_version(अचिन्हित पूर्णांक);
व्योम put_nfs_version(काष्ठा nfs_subversion *);
व्योम रेजिस्टर_nfs_version(काष्ठा nfs_subversion *);
व्योम unरेजिस्टर_nfs_version(काष्ठा nfs_subversion *);

#पूर्ण_अगर /* __LINUX_INTERNAL_NFS_H */
