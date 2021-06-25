<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Joe Lawrence <joe.lawrence@redhat.com>

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

अटल पूर्णांक test_klp_callbacks_mod_init(व्योम)
अणु
	pr_info("%s\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम test_klp_callbacks_mod_निकास(व्योम)
अणु
	pr_info("%s\n", __func__);
पूर्ण

module_init(test_klp_callbacks_mod_init);
module_निकास(test_klp_callbacks_mod_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joe Lawrence <joe.lawrence@redhat.com>");
MODULE_DESCRIPTION("Livepatch test: target module");
