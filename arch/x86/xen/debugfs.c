<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>

#समावेश "debugfs.h"

अटल काष्ठा dentry *d_xen_debug;

काष्ठा dentry * __init xen_init_debugfs(व्योम)
अणु
	अगर (!d_xen_debug)
		d_xen_debug = debugfs_create_dir("xen", शून्य);
	वापस d_xen_debug;
पूर्ण

