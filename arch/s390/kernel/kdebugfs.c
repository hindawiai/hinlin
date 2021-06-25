<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>

काष्ठा dentry *arch_debugfs_dir;
EXPORT_SYMBOL(arch_debugfs_dir);

अटल पूर्णांक __init arch_kdebugfs_init(व्योम)
अणु
	arch_debugfs_dir = debugfs_create_dir("s390", शून्य);
	वापस 0;
पूर्ण
postcore_initcall(arch_kdebugfs_init);
