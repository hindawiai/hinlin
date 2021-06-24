<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Joe Lawrence <joe.lawrence@redhat.com>
 */

/*
 * livepatch-callbacks-busymod.c - (un)patching callbacks demo support module
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
 * section of livepatch-callbacks-mod.c.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>

अटल पूर्णांक sleep_secs;
module_param(sleep_secs, पूर्णांक, 0644);
MODULE_PARM_DESC(sleep_secs, "sleep_secs (default=0)");

अटल व्योम busymod_work_func(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(work, busymod_work_func);

अटल व्योम busymod_work_func(काष्ठा work_काष्ठा *work)
अणु
	pr_info("%s, sleeping %d seconds ...\n", __func__, sleep_secs);
	msleep(sleep_secs * 1000);
	pr_info("%s exit\n", __func__);
पूर्ण

अटल पूर्णांक livepatch_callbacks_mod_init(व्योम)
अणु
	pr_info("%s\n", __func__);
	schedule_delayed_work(&work,
		msecs_to_jअगरfies(1000 * 0));
	वापस 0;
पूर्ण

अटल व्योम livepatch_callbacks_mod_निकास(व्योम)
अणु
	cancel_delayed_work_sync(&work);
	pr_info("%s\n", __func__);
पूर्ण

module_init(livepatch_callbacks_mod_init);
module_निकास(livepatch_callbacks_mod_निकास);
MODULE_LICENSE("GPL");
