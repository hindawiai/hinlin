<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Joe Lawrence <joe.lawrence@redhat.com>

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>

/* load/run-समय control from sysfs ग_लिखोr  */
अटल bool block_transition;
module_param(block_transition, bool, 0644);
MODULE_PARM_DESC(block_transition, "block_transition (default=false)");

अटल व्योम busymod_work_func(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(work, busymod_work_func);

अटल व्योम busymod_work_func(काष्ठा work_काष्ठा *work)
अणु
	pr_info("%s enter\n", __func__);

	जबतक (READ_ONCE(block_transition)) अणु
		/*
		 * Busy-रुको until the sysfs ग_लिखोr has acknowledged a
		 * blocked transition and clears the flag.
		 */
		msleep(20);
	पूर्ण

	pr_info("%s exit\n", __func__);
पूर्ण

अटल पूर्णांक test_klp_callbacks_busy_init(व्योम)
अणु
	pr_info("%s\n", __func__);
	schedule_work(&work);

	अगर (!block_transition) अणु
		/*
		 * Serialize output: prपूर्णांक all messages from the work
		 * function beक्रमe वापसing from init().
		 */
		flush_work(&work);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम test_klp_callbacks_busy_निकास(व्योम)
अणु
	WRITE_ONCE(block_transition, false);
	flush_work(&work);
	pr_info("%s\n", __func__);
पूर्ण

module_init(test_klp_callbacks_busy_init);
module_निकास(test_klp_callbacks_busy_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joe Lawrence <joe.lawrence@redhat.com>");
MODULE_DESCRIPTION("Livepatch test: busy target module");
