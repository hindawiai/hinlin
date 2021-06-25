<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   S/390 common I/O debugfs पूर्णांकerface
 *
 *    Copyright IBM Corp. 2021
 *    Author(s): Vineeth Vijayan <vneethv@linux.ibm.com>
 */

#समावेश <linux/debugfs.h>
#समावेश "cio_debug.h"

काष्ठा dentry *cio_debugfs_dir;

/* Create the debugfs directory क्रम CIO under the arch_debugfs_dir
 * i.e /sys/kernel/debug/s390/cio
 */
अटल पूर्णांक __init cio_debugfs_init(व्योम)
अणु
	cio_debugfs_dir = debugfs_create_dir("cio", arch_debugfs_dir);

	वापस 0;
पूर्ण
subsys_initcall(cio_debugfs_init);
