<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Landlock LSM - Security framework setup
 *
 * Copyright तऊ 2016-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#समावेश <linux/init.h>
#समावेश <linux/lsm_hooks.h>

#समावेश "common.h"
#समावेश "cred.h"
#समावेश "fs.h"
#समावेश "ptrace.h"
#समावेश "setup.h"

bool landlock_initialized __lsm_ro_after_init = false;

काष्ठा lsm_blob_sizes landlock_blob_sizes __lsm_ro_after_init = अणु
	.lbs_cred = माप(काष्ठा landlock_cred_security),
	.lbs_inode = माप(काष्ठा landlock_inode_security),
	.lbs_superblock = माप(काष्ठा landlock_superblock_security),
पूर्ण;

अटल पूर्णांक __init landlock_init(व्योम)
अणु
	landlock_add_cred_hooks();
	landlock_add_ptrace_hooks();
	landlock_add_fs_hooks();
	landlock_initialized = true;
	pr_info("Up and running.\n");
	वापस 0;
पूर्ण

DEFINE_LSM(LANDLOCK_NAME) = अणु
	.name = LANDLOCK_NAME,
	.init = landlock_init,
	.blobs = &landlock_blob_sizes,
पूर्ण;
