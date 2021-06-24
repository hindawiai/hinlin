<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012 Netapp, Inc. All rights reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/nfs_fs.h>
#समावेश "internal.h"
#समावेश "nfs3_fs.h"
#समावेश "nfs.h"

काष्ठा nfs_subversion nfs_v3 = अणु
	.owner = THIS_MODULE,
	.nfs_fs   = &nfs_fs_type,
	.rpc_vers = &nfs_version3,
	.rpc_ops  = &nfs_v3_clientops,
	.sops     = &nfs_sops,
#अगर_घोषित CONFIG_NFS_V3_ACL
	.xattr    = nfs3_xattr_handlers,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init init_nfs_v3(व्योम)
अणु
	रेजिस्टर_nfs_version(&nfs_v3);
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_nfs_v3(व्योम)
अणु
	unरेजिस्टर_nfs_version(&nfs_v3);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_nfs_v3);
module_निकास(निकास_nfs_v3);
