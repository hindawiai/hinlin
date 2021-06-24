<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश "autofs_i.h"

अटल काष्ठा dentry *स्वतःfs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_nodev(fs_type, flags, data, स्वतःfs_fill_super);
पूर्ण

काष्ठा file_प्रणाली_type स्वतःfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "autofs",
	.mount		= स्वतःfs_mount,
	.समाप्त_sb	= स्वतःfs_समाप्त_sb,
पूर्ण;
MODULE_ALIAS_FS("autofs");
MODULE_ALIAS("autofs");

अटल पूर्णांक __init init_स्वतःfs_fs(व्योम)
अणु
	पूर्णांक err;

	स्वतःfs_dev_ioctl_init();

	err = रेजिस्टर_fileप्रणाली(&स्वतःfs_fs_type);
	अगर (err)
		स्वतःfs_dev_ioctl_निकास();

	वापस err;
पूर्ण

अटल व्योम __निकास निकास_स्वतःfs_fs(व्योम)
अणु
	स्वतःfs_dev_ioctl_निकास();
	unरेजिस्टर_fileप्रणाली(&स्वतःfs_fs_type);
पूर्ण

module_init(init_स्वतःfs_fs)
module_निकास(निकास_स्वतःfs_fs)
MODULE_LICENSE("GPL");
