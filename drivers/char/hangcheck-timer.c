<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * hangcheck-समयr.c
 *
 * Driver क्रम a little io fencing समयr.
 *
 * Copyright (C) 2002, 2003 Oracle.  All rights reserved.
 *
 * Author: Joel Becker <joel.becker@oracle.com>
 */

/*
 * The hangcheck-समयr driver uses the TSC to catch delays that
 * jअगरfies करोes not notice.  A समयr is set.  When the समयr fires, it
 * checks whether it was delayed and अगर that delay exceeds a given
 * margin of error.  The hangcheck_tick module parameter takes the समयr
 * duration in seconds.  The hangcheck_margin parameter defines the
 * margin of error, in seconds.  The शेषs are 60 seconds क्रम the
 * समयr and 180 seconds क्रम the margin of error.  IOW, a समयr is set
 * क्रम 60 seconds.  When the समयr fires, the callback checks the
 * actual duration that the समयr रुकोed.  If the duration exceeds the
 * allotted समय and margin (here 60 + 180, or 240 seconds), the machine
 * is restarted.  A healthy machine will have the duration match the
 * expected समयout very बंदly.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/समयr.h>
#समावेश <linux/hrसमयr.h>

#घोषणा VERSION_STR "0.9.1"

#घोषणा DEFAULT_IOFENCE_MARGIN 60	/* Default fudge factor, in seconds */
#घोषणा DEFAULT_IOFENCE_TICK 180	/* Default समयr समयout, in seconds */

अटल पूर्णांक hangcheck_tick = DEFAULT_IOFENCE_TICK;
अटल पूर्णांक hangcheck_margin = DEFAULT_IOFENCE_MARGIN;
अटल पूर्णांक hangcheck_reboot;  /* Defaults to not reboot */
अटल पूर्णांक hangcheck_dump_tasks;  /* Defaults to not dumping SysRQ T */

/* options - modular */
module_param(hangcheck_tick, पूर्णांक, 0);
MODULE_PARM_DESC(hangcheck_tick, "Timer delay.");
module_param(hangcheck_margin, पूर्णांक, 0);
MODULE_PARM_DESC(hangcheck_margin, "If the hangcheck timer has been delayed more than hangcheck_margin seconds, the driver will fire.");
module_param(hangcheck_reboot, पूर्णांक, 0);
MODULE_PARM_DESC(hangcheck_reboot, "If nonzero, the machine will reboot when the timer margin is exceeded.");
module_param(hangcheck_dump_tasks, पूर्णांक, 0);
MODULE_PARM_DESC(hangcheck_dump_tasks, "If nonzero, the machine will dump the system task state when the timer margin is exceeded.");

MODULE_AUTHOR("Oracle");
MODULE_DESCRIPTION("Hangcheck-timer detects when the system has gone out to lunch past a certain margin.");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION_STR);

/* options - nonmodular */
#अगर_अघोषित MODULE

अटल पूर्णांक __init hangcheck_parse_tick(अक्षर *str)
अणु
	पूर्णांक par;
	अगर (get_option(&str,&par))
		hangcheck_tick = par;
	वापस 1;
पूर्ण

अटल पूर्णांक __init hangcheck_parse_margin(अक्षर *str)
अणु
	पूर्णांक par;
	अगर (get_option(&str,&par))
		hangcheck_margin = par;
	वापस 1;
पूर्ण

अटल पूर्णांक __init hangcheck_parse_reboot(अक्षर *str)
अणु
	पूर्णांक par;
	अगर (get_option(&str,&par))
		hangcheck_reboot = par;
	वापस 1;
पूर्ण

अटल पूर्णांक __init hangcheck_parse_dump_tasks(अक्षर *str)
अणु
	पूर्णांक par;
	अगर (get_option(&str,&par))
		hangcheck_dump_tasks = par;
	वापस 1;
पूर्ण

__setup("hcheck_tick", hangcheck_parse_tick);
__setup("hcheck_margin", hangcheck_parse_margin);
__setup("hcheck_reboot", hangcheck_parse_reboot);
__setup("hcheck_dump_tasks", hangcheck_parse_dump_tasks);
#पूर्ण_अगर /* not MODULE */

#घोषणा TIMER_FREQ 1000000000ULL

/* Last समय scheduled */
अटल अचिन्हित दीर्घ दीर्घ hangcheck_tsc, hangcheck_tsc_margin;

अटल व्योम hangcheck_fire(काष्ठा समयr_list *);

अटल DEFINE_TIMER(hangcheck_ticktock, hangcheck_fire);

अटल व्योम hangcheck_fire(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ दीर्घ cur_tsc, tsc_dअगरf;

	cur_tsc = kसमय_get_ns();

	अगर (cur_tsc > hangcheck_tsc)
		tsc_dअगरf = cur_tsc - hangcheck_tsc;
	अन्यथा
		tsc_dअगरf = (cur_tsc + (~0ULL - hangcheck_tsc)); /* or something */

	अगर (tsc_dअगरf > hangcheck_tsc_margin) अणु
		अगर (hangcheck_dump_tasks) अणु
			prपूर्णांकk(KERN_CRIT "Hangcheck: Task state:\n");
#अगर_घोषित CONFIG_MAGIC_SYSRQ
			handle_sysrq('t');
#पूर्ण_अगर  /* CONFIG_MAGIC_SYSRQ */
		पूर्ण
		अगर (hangcheck_reboot) अणु
			prपूर्णांकk(KERN_CRIT "Hangcheck: hangcheck is restarting the machine.\n");
			emergency_restart();
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_CRIT "Hangcheck: hangcheck value past margin!\n");
		पूर्ण
	पूर्ण
#अगर 0
	/*
	 * Enable to investigate delays in detail
	 */
	prपूर्णांकk("Hangcheck: called %Ld ns since last time (%Ld ns overshoot)\n",
			tsc_dअगरf, tsc_dअगरf - hangcheck_tick*TIMER_FREQ);
#पूर्ण_अगर
	mod_समयr(&hangcheck_ticktock, jअगरfies + (hangcheck_tick*HZ));
	hangcheck_tsc = kसमय_get_ns();
पूर्ण


अटल पूर्णांक __init hangcheck_init(व्योम)
अणु
	prपूर्णांकk("Hangcheck: starting hangcheck timer %s (tick is %d seconds, margin is %d seconds).\n",
	       VERSION_STR, hangcheck_tick, hangcheck_margin);
	hangcheck_tsc_margin =
		(अचिन्हित दीर्घ दीर्घ)hangcheck_margin + hangcheck_tick;
	hangcheck_tsc_margin *= TIMER_FREQ;

	hangcheck_tsc = kसमय_get_ns();
	mod_समयr(&hangcheck_ticktock, jअगरfies + (hangcheck_tick*HZ));

	वापस 0;
पूर्ण


अटल व्योम __निकास hangcheck_निकास(व्योम)
अणु
	del_समयr_sync(&hangcheck_ticktock);
        prपूर्णांकk("Hangcheck: Stopped hangcheck timer.\n");
पूर्ण

module_init(hangcheck_init);
module_निकास(hangcheck_निकास);
