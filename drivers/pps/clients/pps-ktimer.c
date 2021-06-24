<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pps-kसमयr.c -- kernel समयr test client
 *
 * Copyright (C) 2005-2006   Roकरोlfo Giometti <giometti@linux.it>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/pps_kernel.h>

/*
 * Global variables
 */

अटल काष्ठा pps_device *pps;
अटल काष्ठा समयr_list kसमयr;

/*
 * The kernel समयr
 */

अटल व्योम pps_kसमयr_event(काष्ठा समयr_list *unused)
अणु
	काष्ठा pps_event_समय ts;

	/* First of all we get the समय stamp... */
	pps_get_ts(&ts);

	pps_event(pps, &ts, PPS_CAPTUREASSERT, शून्य);

	mod_समयr(&kसमयr, jअगरfies + HZ);
पूर्ण

/*
 * The PPS info काष्ठा
 */

अटल काष्ठा pps_source_info pps_kसमयr_info = अणु
	.name		= "ktimer",
	.path		= "",
	.mode		= PPS_CAPTUREASSERT | PPS_OFFSETASSERT |
			  PPS_ECHOASSERT |
			  PPS_CANWAIT | PPS_TSFMT_TSPEC,
	.owner		= THIS_MODULE,
पूर्ण;

/*
 * Module staff
 */

अटल व्योम __निकास pps_kसमयr_निकास(व्योम)
अणु
	dev_info(pps->dev, "ktimer PPS source unregistered\n");

	del_समयr_sync(&kसमयr);
	pps_unरेजिस्टर_source(pps);
पूर्ण

अटल पूर्णांक __init pps_kसमयr_init(व्योम)
अणु
	pps = pps_रेजिस्टर_source(&pps_kसमयr_info,
				PPS_CAPTUREASSERT | PPS_OFFSETASSERT);
	अगर (IS_ERR(pps)) अणु
		pr_err("cannot register PPS source\n");
		वापस PTR_ERR(pps);
	पूर्ण

	समयr_setup(&kसमयr, pps_kसमयr_event, 0);
	mod_समयr(&kसमयr, jअगरfies + HZ);

	dev_info(pps->dev, "ktimer PPS source registered\n");

	वापस 0;
पूर्ण

module_init(pps_kसमयr_init);
module_निकास(pps_kसमयr_निकास);

MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("dummy PPS source by using a kernel timer (just for debug)");
MODULE_LICENSE("GPL");
