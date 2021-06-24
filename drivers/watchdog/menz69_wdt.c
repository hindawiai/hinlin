<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Watchकरोg driver क्रम the MEN z069 IP-Core
 *
 * Copyright (C) 2018 Johannes Thumshirn <jth@kernel.org>
 */
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mcb.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>

काष्ठा men_z069_drv अणु
	काष्ठा watchकरोg_device wdt;
	व्योम __iomem *base;
	काष्ठा resource *mem;
पूर्ण;

#घोषणा MEN_Z069_WTR			0x10
#घोषणा MEN_Z069_WTR_WDEN		BIT(15)
#घोषणा MEN_Z069_WTR_WDET_MASK		0x7fff
#घोषणा MEN_Z069_WVR			0x14

#घोषणा MEN_Z069_TIMER_FREQ		500 /* 500 Hz */
#घोषणा MEN_Z069_WDT_COUNTER_MIN	1
#घोषणा MEN_Z069_WDT_COUNTER_MAX	0x7fff
#घोषणा MEN_Z069_DEFAULT_TIMEOUT	30

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
			    __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक men_z069_wdt_start(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा men_z069_drv *drv = watchकरोg_get_drvdata(wdt);
	u16 val;

	val = पढ़ोw(drv->base + MEN_Z069_WTR);
	val |= MEN_Z069_WTR_WDEN;
	ग_लिखोw(val, drv->base + MEN_Z069_WTR);

	वापस 0;
पूर्ण

अटल पूर्णांक men_z069_wdt_stop(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा men_z069_drv *drv = watchकरोg_get_drvdata(wdt);
	u16 val;

	val = पढ़ोw(drv->base + MEN_Z069_WTR);
	val &= ~MEN_Z069_WTR_WDEN;
	ग_लिखोw(val, drv->base + MEN_Z069_WTR);

	वापस 0;
पूर्ण

अटल पूर्णांक men_z069_wdt_ping(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा men_z069_drv *drv = watchकरोg_get_drvdata(wdt);
	u16 val;

	/* The watchकरोg trigger value toggles between 0x5555 and 0xaaaa */
	val = पढ़ोw(drv->base + MEN_Z069_WVR);
	val ^= 0xffff;
	ग_लिखोw(val, drv->base + MEN_Z069_WVR);

	वापस 0;
पूर्ण

अटल पूर्णांक men_z069_wdt_set_समयout(काष्ठा watchकरोg_device *wdt,
				    अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा men_z069_drv *drv = watchकरोg_get_drvdata(wdt);
	u16 reg, val, ena;

	wdt->समयout = समयout;
	val = समयout * MEN_Z069_TIMER_FREQ;

	reg = पढ़ोw(drv->base + MEN_Z069_WVR);
	ena = reg & MEN_Z069_WTR_WDEN;
	reg = ena | val;
	ग_लिखोw(reg, drv->base + MEN_Z069_WTR);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info men_z069_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "MEN z069 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops men_z069_ops = अणु
	.owner = THIS_MODULE,
	.start = men_z069_wdt_start,
	.stop = men_z069_wdt_stop,
	.ping = men_z069_wdt_ping,
	.set_समयout = men_z069_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device men_z069_wdt = अणु
	.info = &men_z069_info,
	.ops = &men_z069_ops,
	.समयout = MEN_Z069_DEFAULT_TIMEOUT,
	.min_समयout = 1,
	.max_समयout = MEN_Z069_WDT_COUNTER_MAX / MEN_Z069_TIMER_FREQ,
पूर्ण;

अटल पूर्णांक men_z069_probe(काष्ठा mcb_device *dev,
			  स्थिर काष्ठा mcb_device_id *id)
अणु
	काष्ठा men_z069_drv *drv;
	काष्ठा resource *mem;

	drv = devm_kzalloc(&dev->dev, माप(काष्ठा men_z069_drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	mem = mcb_request_mem(dev, "z069-wdt");
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	drv->base = devm_ioremap(&dev->dev, mem->start, resource_size(mem));
	अगर (drv->base == शून्य)
		जाओ release_mem;

	drv->mem = mem;

	drv->wdt = men_z069_wdt;
	watchकरोg_init_समयout(&drv->wdt, 0, &dev->dev);
	watchकरोg_set_nowayout(&drv->wdt, nowayout);
	watchकरोg_set_drvdata(&drv->wdt, drv);
	drv->wdt.parent = &dev->dev;
	mcb_set_drvdata(dev, drv);

	वापस watchकरोg_रेजिस्टर_device(&men_z069_wdt);

release_mem:
	mcb_release_mem(mem);
	वापस -ENOMEM;
पूर्ण

अटल व्योम men_z069_हटाओ(काष्ठा mcb_device *dev)
अणु
	काष्ठा men_z069_drv *drv = mcb_get_drvdata(dev);

	watchकरोg_unरेजिस्टर_device(&drv->wdt);
	mcb_release_mem(drv->mem);
पूर्ण

अटल स्थिर काष्ठा mcb_device_id men_z069_ids[] = अणु
	अणु .device = 0x45 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mcb, men_z069_ids);

अटल काष्ठा mcb_driver men_z069_driver = अणु
	.driver = अणु
		.name = "z069-wdt",
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = men_z069_probe,
	.हटाओ = men_z069_हटाओ,
	.id_table = men_z069_ids,
पूर्ण;
module_mcb_driver(men_z069_driver);

MODULE_AUTHOR("Johannes Thumshirn <jth@kernel.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("mcb:16z069");
MODULE_IMPORT_NS(MCB);
