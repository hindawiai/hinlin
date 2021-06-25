<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>

काष्ठा dentry *arch_debugfs_dir;
EXPORT_SYMBOL(arch_debugfs_dir);

अटल पूर्णांक __init arch_kdebugfs_init(व्योम)
अणु
	arch_debugfs_dir = debugfs_create_dir("sh", शून्य);
	वापस 0;
पूर्ण
arch_initcall(arch_kdebugfs_init);
