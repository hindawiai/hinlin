<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pps-ldisc.c -- PPS line discipline
 *
 * Copyright (C) 2008	Roकरोlfo Giometti <giometti@linux.it>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/tty.h>
#समावेश <linux/pps_kernel.h>
#समावेश <linux/bug.h>

अटल व्योम pps_tty_dcd_change(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक status)
अणु
	काष्ठा pps_device *pps;
	काष्ठा pps_event_समय ts;

	pps_get_ts(&ts);

	pps = pps_lookup_dev(tty);
	/*
	 * This should never fail, but the ldisc locking is very
	 * convoluted, so करोn't crash just in हाल.
	 */
	अगर (WARN_ON_ONCE(pps == शून्य))
		वापस;

	/* Now करो the PPS event report */
	pps_event(pps, &ts, status ? PPS_CAPTUREASSERT :
			PPS_CAPTURECLEAR, शून्य);

	dev_dbg(pps->dev, "PPS %s at %lu\n",
			status ? "assert" : "clear", jअगरfies);
पूर्ण

अटल पूर्णांक (*alias_n_tty_खोलो)(काष्ठा tty_काष्ठा *tty);

अटल पूर्णांक pps_tty_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा pps_source_info info;
	काष्ठा tty_driver *drv = tty->driver;
	पूर्णांक index = tty->index + drv->name_base;
	काष्ठा pps_device *pps;
	पूर्णांक ret;

	info.owner = THIS_MODULE;
	info.dev = शून्य;
	snम_लिखो(info.name, PPS_MAX_NAME_LEN, "%s%d", drv->driver_name, index);
	snम_लिखो(info.path, PPS_MAX_NAME_LEN, "/dev/%s%d", drv->name, index);
	info.mode = PPS_CAPTUREBOTH | \
			PPS_OFFSETASSERT | PPS_OFFSETCLEAR | \
			PPS_CANWAIT | PPS_TSFMT_TSPEC;

	pps = pps_रेजिस्टर_source(&info, PPS_CAPTUREBOTH | \
				PPS_OFFSETASSERT | PPS_OFFSETCLEAR);
	अगर (IS_ERR(pps)) अणु
		pr_err("cannot register PPS source \"%s\"\n", info.path);
		वापस PTR_ERR(pps);
	पूर्ण
	pps->lookup_cookie = tty;

	/* Now खोलो the base class N_TTY ldisc */
	ret = alias_n_tty_खोलो(tty);
	अगर (ret < 0) अणु
		pr_err("cannot open tty ldisc \"%s\"\n", info.path);
		जाओ err_unरेजिस्टर;
	पूर्ण

	dev_info(pps->dev, "source \"%s\" added\n", info.path);

	वापस 0;

err_unरेजिस्टर:
	pps_unरेजिस्टर_source(pps);
	वापस ret;
पूर्ण

अटल व्योम (*alias_n_tty_बंद)(काष्ठा tty_काष्ठा *tty);

अटल व्योम pps_tty_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा pps_device *pps = pps_lookup_dev(tty);

	alias_n_tty_बंद(tty);

	अगर (WARN_ON(!pps))
		वापस;

	dev_info(pps->dev, "removed\n");
	pps_unरेजिस्टर_source(pps);
पूर्ण

अटल काष्ठा tty_ldisc_ops pps_ldisc_ops;

/*
 * Module stuff
 */

अटल पूर्णांक __init pps_tty_init(व्योम)
अणु
	पूर्णांक err;

	/* Inherit the N_TTY's ops */
	n_tty_inherit_ops(&pps_ldisc_ops);

	/* Save N_TTY's खोलो()/बंद() methods */
	alias_n_tty_खोलो = pps_ldisc_ops.खोलो;
	alias_n_tty_बंद = pps_ldisc_ops.बंद;

	/* Init PPS_TTY data */
	pps_ldisc_ops.owner = THIS_MODULE;
	pps_ldisc_ops.name = "pps_tty";
	pps_ldisc_ops.dcd_change = pps_tty_dcd_change;
	pps_ldisc_ops.खोलो = pps_tty_खोलो;
	pps_ldisc_ops.बंद = pps_tty_बंद;

	err = tty_रेजिस्टर_ldisc(N_PPS, &pps_ldisc_ops);
	अगर (err)
		pr_err("can't register PPS line discipline\n");
	अन्यथा
		pr_info("PPS line discipline registered\n");

	वापस err;
पूर्ण

अटल व्योम __निकास pps_tty_cleanup(व्योम)
अणु
	पूर्णांक err;

	err = tty_unरेजिस्टर_ldisc(N_PPS);
	अगर (err)
		pr_err("can't unregister PPS line discipline\n");
	अन्यथा
		pr_info("PPS line discipline removed\n");
पूर्ण

module_init(pps_tty_init);
module_निकास(pps_tty_cleanup);

MODULE_ALIAS_LDISC(N_PPS);
MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("PPS TTY device driver");
MODULE_LICENSE("GPL");
