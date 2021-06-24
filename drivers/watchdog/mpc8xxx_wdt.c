<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mpc8xxx_wdt.c - MPC8xx/MPC83xx/MPC86xx watchकरोg userspace पूर्णांकerface
 *
 * Authors: Dave Updegraff <dave@cray.org>
 *	    Kumar Gala <galak@kernel.crashing.org>
 *		Attribution: from 83xx_wst: Florian Schirmer <jolt@tuxbox.org>
 *				..and from sc520_wdt
 * Copyright (c) 2008  MontaVista Software, Inc.
 *                     Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * Note: it appears that you can only actually ENABLE or DISABLE the thing
 * once after POR. Once enabled, you cannot disable, and vice versa.
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <sysdev/fsl_soc.h>

#घोषणा WATCHDOG_TIMEOUT 10

काष्ठा mpc8xxx_wdt अणु
	__be32 res0;
	__be32 swcrr; /* System watchकरोg control रेजिस्टर */
#घोषणा SWCRR_SWTC 0xFFFF0000 /* Software Watchकरोg Time Count. */
#घोषणा SWCRR_SWF  0x00000008 /* Software Watchकरोg Freeze (mpc8xx). */
#घोषणा SWCRR_SWEN 0x00000004 /* Watchकरोg Enable bit. */
#घोषणा SWCRR_SWRI 0x00000002 /* Software Watchकरोg Reset/Interrupt Select bit.*/
#घोषणा SWCRR_SWPR 0x00000001 /* Software Watchकरोg Counter Prescale bit. */
	__be32 swcnr; /* System watchकरोg count रेजिस्टर */
	u8 res1[2];
	__be16 swsrr; /* System watchकरोg service रेजिस्टर */
	u8 res2[0xF0];
पूर्ण;

काष्ठा mpc8xxx_wdt_type अणु
	पूर्णांक prescaler;
	bool hw_enabled;
	u32 rsr_mask;
पूर्ण;

काष्ठा mpc8xxx_wdt_ddata अणु
	काष्ठा mpc8xxx_wdt __iomem *base;
	काष्ठा watchकरोg_device wdd;
	spinlock_t lock;
	u16 swtc;
पूर्ण;

अटल u16 समयout;
module_param(समयout, uलघु, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. (1<timeout<65535, default="
	__MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल bool reset = 1;
module_param(reset, bool, 0);
MODULE_PARM_DESC(reset,
	"Watchdog Interrupt/Reset Mode. 0 = interrupt, 1 = reset");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
		 "(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल व्योम mpc8xxx_wdt_keepalive(काष्ठा mpc8xxx_wdt_ddata *ddata)
अणु
	/* Ping the WDT */
	spin_lock(&ddata->lock);
	out_be16(&ddata->base->swsrr, 0x556c);
	out_be16(&ddata->base->swsrr, 0xaa39);
	spin_unlock(&ddata->lock);
पूर्ण

अटल पूर्णांक mpc8xxx_wdt_start(काष्ठा watchकरोg_device *w)
अणु
	काष्ठा mpc8xxx_wdt_ddata *ddata =
		container_of(w, काष्ठा mpc8xxx_wdt_ddata, wdd);
	u32 पंचांगp = in_be32(&ddata->base->swcrr);

	/* Good, fire up the show */
	पंचांगp &= ~(SWCRR_SWTC | SWCRR_SWF | SWCRR_SWEN | SWCRR_SWRI | SWCRR_SWPR);
	पंचांगp |= SWCRR_SWEN | SWCRR_SWPR | (ddata->swtc << 16);

	अगर (reset)
		पंचांगp |= SWCRR_SWRI;

	out_be32(&ddata->base->swcrr, पंचांगp);

	पंचांगp = in_be32(&ddata->base->swcrr);
	अगर (!(पंचांगp & SWCRR_SWEN))
		वापस -EOPNOTSUPP;

	ddata->swtc = पंचांगp >> 16;
	set_bit(WDOG_HW_RUNNING, &ddata->wdd.status);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc8xxx_wdt_ping(काष्ठा watchकरोg_device *w)
अणु
	काष्ठा mpc8xxx_wdt_ddata *ddata =
		container_of(w, काष्ठा mpc8xxx_wdt_ddata, wdd);

	mpc8xxx_wdt_keepalive(ddata);
	वापस 0;
पूर्ण

अटल काष्ठा watchकरोg_info mpc8xxx_wdt_info = अणु
	.options = WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE | WDIOF_SETTIMEOUT,
	.firmware_version = 1,
	.identity = "MPC8xxx",
पूर्ण;

अटल काष्ठा watchकरोg_ops mpc8xxx_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = mpc8xxx_wdt_start,
	.ping = mpc8xxx_wdt_ping,
पूर्ण;

अटल पूर्णांक mpc8xxx_wdt_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *res;
	स्थिर काष्ठा mpc8xxx_wdt_type *wdt_type;
	काष्ठा mpc8xxx_wdt_ddata *ddata;
	u32 freq = fsl_get_sys_freq();
	bool enabled;
	काष्ठा device *dev = &ofdev->dev;

	wdt_type = of_device_get_match_data(dev);
	अगर (!wdt_type)
		वापस -EINVAL;

	अगर (!freq || freq == -1)
		वापस -EINVAL;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->base = devm_platक्रमm_ioremap_resource(ofdev, 0);
	अगर (IS_ERR(ddata->base))
		वापस PTR_ERR(ddata->base);

	enabled = in_be32(&ddata->base->swcrr) & SWCRR_SWEN;
	अगर (!enabled && wdt_type->hw_enabled) अणु
		dev_info(dev, "could not be enabled in software\n");
		वापस -ENODEV;
	पूर्ण

	res = platक्रमm_get_resource(ofdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		bool status;
		u32 __iomem *rsr = ioremap(res->start, resource_size(res));

		अगर (!rsr)
			वापस -ENOMEM;

		status = in_be32(rsr) & wdt_type->rsr_mask;
		ddata->wdd.bootstatus = status ? WDIOF_CARDRESET : 0;
		 /* clear reset status bits related to watchकरोg समयr */
		out_be32(rsr, wdt_type->rsr_mask);
		iounmap(rsr);

		dev_info(dev, "Last boot was %scaused by watchdog\n",
			 status ? "" : "not ");
	पूर्ण

	spin_lock_init(&ddata->lock);

	ddata->wdd.info = &mpc8xxx_wdt_info;
	ddata->wdd.ops = &mpc8xxx_wdt_ops;

	ddata->wdd.समयout = WATCHDOG_TIMEOUT;
	watchकरोg_init_समयout(&ddata->wdd, समयout, dev);

	watchकरोg_set_nowayout(&ddata->wdd, nowayout);

	ddata->swtc = min(ddata->wdd.समयout * freq / wdt_type->prescaler,
			  0xffffU);

	/*
	 * If the watchकरोg was previously enabled or we're running on
	 * MPC8xxx, we should ping the wdt from the kernel until the
	 * userspace handles it.
	 */
	अगर (enabled)
		mpc8xxx_wdt_start(&ddata->wdd);

	ddata->wdd.max_hw_heartbeat_ms = (ddata->swtc * wdt_type->prescaler) /
					 (freq / 1000);
	ddata->wdd.min_समयout = ddata->wdd.max_hw_heartbeat_ms / 1000;
	अगर (ddata->wdd.समयout < ddata->wdd.min_समयout)
		ddata->wdd.समयout = ddata->wdd.min_समयout;

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &ddata->wdd);
	अगर (ret)
		वापस ret;

	dev_info(dev,
		 "WDT driver for MPC8xxx initialized. mode:%s timeout=%d sec\n",
		 reset ? "reset" : "interrupt", ddata->wdd.समयout);

	platक्रमm_set_drvdata(ofdev, ddata);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc8xxx_wdt_match[] = अणु
	अणु
		.compatible = "mpc83xx_wdt",
		.data = &(काष्ठा mpc8xxx_wdt_type) अणु
			.prescaler = 0x10000,
			.rsr_mask = BIT(3), /* RSR Bit SWRS */
		पूर्ण,
	पूर्ण,
	अणु
		.compatible = "fsl,mpc8610-wdt",
		.data = &(काष्ठा mpc8xxx_wdt_type) अणु
			.prescaler = 0x10000,
			.hw_enabled = true,
			.rsr_mask = BIT(20), /* RSTRSCR Bit WDT_RR */
		पूर्ण,
	पूर्ण,
	अणु
		.compatible = "fsl,mpc823-wdt",
		.data = &(काष्ठा mpc8xxx_wdt_type) अणु
			.prescaler = 0x800,
			.hw_enabled = true,
			.rsr_mask = BIT(28), /* RSR Bit SWRS */
		पूर्ण,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc8xxx_wdt_match);

अटल काष्ठा platक्रमm_driver mpc8xxx_wdt_driver = अणु
	.probe		= mpc8xxx_wdt_probe,
	.driver = अणु
		.name = "mpc8xxx_wdt",
		.of_match_table = mpc8xxx_wdt_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mpc8xxx_wdt_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mpc8xxx_wdt_driver);
पूर्ण
arch_initcall(mpc8xxx_wdt_init);

अटल व्योम __निकास mpc8xxx_wdt_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mpc8xxx_wdt_driver);
पूर्ण
module_निकास(mpc8xxx_wdt_निकास);

MODULE_AUTHOR("Dave Updegraff, Kumar Gala");
MODULE_DESCRIPTION("Driver for watchdog timer in MPC8xx/MPC83xx/MPC86xx "
		   "uProcessors");
MODULE_LICENSE("GPL");
