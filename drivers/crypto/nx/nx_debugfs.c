<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * debugfs routines supporting the Power 7+ Nest Accelerators driver
 *
 * Copyright (C) 2011-2012 International Business Machines Inc.
 *
 * Author: Kent Yoder <yoder1@us.ibm.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/hash.h>
#समावेश <यंत्र/vपन.स>

#समावेश "nx_csbcpb.h"
#समावेश "nx.h"

#अगर_घोषित CONFIG_DEBUG_FS

/*
 * debugfs
 *
 * For करोcumentation on these attributes, please see:
 *
 * Documentation/ABI/testing/debugfs-pfo-nx-crypto
 */

व्योम nx_debugfs_init(काष्ठा nx_crypto_driver *drv)
अणु
	काष्ठा dentry *root;

	root = debugfs_create_dir(NX_NAME, शून्य);
	drv->dfs_root = root;

	debugfs_create_u32("aes_ops", S_IRUSR | S_IRGRP | S_IROTH,
			   root, &drv->stats.aes_ops.counter);
	debugfs_create_u32("sha256_ops", S_IRUSR | S_IRGRP | S_IROTH,
			   root, &drv->stats.sha256_ops.counter);
	debugfs_create_u32("sha512_ops", S_IRUSR | S_IRGRP | S_IROTH,
			   root, &drv->stats.sha512_ops.counter);
	debugfs_create_u64("aes_bytes", S_IRUSR | S_IRGRP | S_IROTH,
			   root, &drv->stats.aes_bytes.counter);
	debugfs_create_u64("sha256_bytes", S_IRUSR | S_IRGRP | S_IROTH,
			   root, &drv->stats.sha256_bytes.counter);
	debugfs_create_u64("sha512_bytes", S_IRUSR | S_IRGRP | S_IROTH,
			   root, &drv->stats.sha512_bytes.counter);
	debugfs_create_u32("errors", S_IRUSR | S_IRGRP | S_IROTH,
			   root, &drv->stats.errors.counter);
	debugfs_create_u32("last_error", S_IRUSR | S_IRGRP | S_IROTH,
			   root, &drv->stats.last_error.counter);
	debugfs_create_u32("last_error_pid", S_IRUSR | S_IRGRP | S_IROTH,
			   root, &drv->stats.last_error_pid.counter);
पूर्ण

व्योम
nx_debugfs_fini(काष्ठा nx_crypto_driver *drv)
अणु
	debugfs_हटाओ_recursive(drv->dfs_root);
पूर्ण

#पूर्ण_अगर
