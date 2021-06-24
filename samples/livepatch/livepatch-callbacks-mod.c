<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Joe Lawrence <joe.lawrence@redhat.com>
 */

/*
 * livepatch-callbacks-mod.c - (un)patching callbacks demo support module
 *
 *
 * Purpose
 * -------
 *
 * Simple module to demonstrate livepatch (un)patching callbacks.
 *
 *
 * Usage
 * -----
 *
 * This module is not पूर्णांकended to be standalone.  See the "Usage"
 * section of livepatch-callbacks-demo.c.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

अटल पूर्णांक livepatch_callbacks_mod_init(व्योम)
अणु
	pr_info("%s\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम livepatch_callbacks_mod_निकास(व्योम)
अणु
	pr_info("%s\n", __func__);
पूर्ण

module_init(livepatch_callbacks_mod_init);
module_निकास(livepatch_callbacks_mod_निकास);
MODULE_LICENSE("GPL");
