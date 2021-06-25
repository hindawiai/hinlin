<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus debugfs code
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/greybus.h>

अटल काष्ठा dentry *gb_debug_root;

व्योम __init gb_debugfs_init(व्योम)
अणु
	gb_debug_root = debugfs_create_dir("greybus", शून्य);
पूर्ण

व्योम gb_debugfs_cleanup(व्योम)
अणु
	debugfs_हटाओ_recursive(gb_debug_root);
	gb_debug_root = शून्य;
पूर्ण

काष्ठा dentry *gb_debugfs_get(व्योम)
अणु
	वापस gb_debug_root;
पूर्ण
EXPORT_SYMBOL_GPL(gb_debugfs_get);
