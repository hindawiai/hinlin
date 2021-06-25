<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * घातeroff.c - sysrq handler to gracefully घातer करोwn machine.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/init.h>
#समावेश <linux/pm.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/reboot.h>
#समावेश <linux/cpumask.h>

/*
 * When the user hits Sys-Rq o to घातer करोwn the machine this is the
 * callback we use.
 */

अटल व्योम करो_घातeroff(काष्ठा work_काष्ठा *dummy)
अणु
	kernel_घातer_off();
पूर्ण

अटल DECLARE_WORK(घातeroff_work, करो_घातeroff);

अटल व्योम handle_घातeroff(पूर्णांक key)
अणु
	/* run sysrq घातeroff on boot cpu */
	schedule_work_on(cpumask_first(cpu_online_mask), &घातeroff_work);
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op	sysrq_घातeroff_op = अणु
	.handler        = handle_घातeroff,
	.help_msg       = "poweroff(o)",
	.action_msg     = "Power Off",
	.enable_mask	= SYSRQ_ENABLE_BOOT,
पूर्ण;

अटल पूर्णांक __init pm_sysrq_init(व्योम)
अणु
	रेजिस्टर_sysrq_key('o', &sysrq_घातeroff_op);
	वापस 0;
पूर्ण

subsys_initcall(pm_sysrq_init);
