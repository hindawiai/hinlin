<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012 Netapp, Inc. All rights reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/nfs_fs.h>
#समावेश "internal.h"
#समावेश "nfs.h"

अटल काष्ठा nfs_subversion nfs_v2 = अणु
	.owner = THIS_MODULE,
	.nfs_fs   = &nfs_fs_type,
	.rpc_vers = &nfs_version2,
	.rpc_ops  = &nfs_v2_clientops,
	.sops     = &nfs_sops,
पूर्ण;

अटल पूर्णांक __init init_nfs_v2(व्योम)
अणु
	रेजिस्टर_nfs_version(&nfs_v2);
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_nfs_v2(व्योम)
अणु
	unरेजिस्टर_nfs_version(&nfs_v2);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_nfs_v2);
module_निकास(निकास_nfs_v2);
