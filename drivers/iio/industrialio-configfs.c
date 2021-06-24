<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Industrial I/O configfs bits
 *
 * Copyright (c) 2015 Intel Corporation
 */

#समावेश <linux/configfs.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/configfs.h>

अटल स्थिर काष्ठा config_item_type iio_root_group_type = अणु
	.ct_owner       = THIS_MODULE,
पूर्ण;

काष्ठा configfs_subप्रणाली iio_configfs_subsys = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf = "iio",
			.ci_type = &iio_root_group_type,
		पूर्ण,
	पूर्ण,
	.su_mutex = __MUTEX_INITIALIZER(iio_configfs_subsys.su_mutex),
पूर्ण;
EXPORT_SYMBOL(iio_configfs_subsys);

अटल पूर्णांक __init iio_configfs_init(व्योम)
अणु
	config_group_init(&iio_configfs_subsys.su_group);

	वापस configfs_रेजिस्टर_subप्रणाली(&iio_configfs_subsys);
पूर्ण
module_init(iio_configfs_init);

अटल व्योम __निकास iio_configfs_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_subप्रणाली(&iio_configfs_subsys);
पूर्ण
module_निकास(iio_configfs_निकास);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("Industrial I/O configfs support");
MODULE_LICENSE("GPL v2");
