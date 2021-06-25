<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Watchकरोg समयr driver क्रम the WinSystems EBC-C384
 * Copyright (C) 2016 William Breathitt Gray
 */
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/isa.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

#घोषणा MODULE_NAME		"ebc-c384_wdt"
#घोषणा WATCHDOG_TIMEOUT	60
/*
 * The समयout value in minutes must fit in a single byte when sent to the
 * watchकरोg समयr; the maximum समयout possible is 15300 (255 * 60) seconds.
 */
#घोषणा WATCHDOG_MAX_TIMEOUT	15300
#घोषणा BASE_ADDR		0x564
#घोषणा ADDR_EXTENT		5
#घोषणा CFG_ADDR		(BASE_ADDR + 1)
#घोषणा PET_ADDR		(BASE_ADDR + 2)

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल अचिन्हित समयout;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds (default="
	__MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल पूर्णांक ebc_c384_wdt_start(काष्ठा watchकरोg_device *wdev)
अणु
	अचिन्हित t = wdev->समयout;

	/* resolution is in minutes क्रम समयouts greater than 255 seconds */
	अगर (t > 255)
		t = DIV_ROUND_UP(t, 60);

	outb(t, PET_ADDR);

	वापस 0;
पूर्ण

अटल पूर्णांक ebc_c384_wdt_stop(काष्ठा watchकरोg_device *wdev)
अणु
	outb(0x00, PET_ADDR);

	वापस 0;
पूर्ण

अटल पूर्णांक ebc_c384_wdt_set_समयout(काष्ठा watchकरोg_device *wdev, अचिन्हित t)
अणु
	/* resolution is in minutes क्रम समयouts greater than 255 seconds */
	अगर (t > 255) अणु
		/* round second resolution up to minute granularity */
		wdev->समयout = roundup(t, 60);

		/* set watchकरोg समयr क्रम minutes */
		outb(0x00, CFG_ADDR);
	पूर्ण अन्यथा अणु
		wdev->समयout = t;

		/* set watchकरोg समयr क्रम seconds */
		outb(0x80, CFG_ADDR);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops ebc_c384_wdt_ops = अणु
	.start = ebc_c384_wdt_start,
	.stop = ebc_c384_wdt_stop,
	.set_समयout = ebc_c384_wdt_set_समयout
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info ebc_c384_wdt_info = अणु
	.options = WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE | WDIOF_SETTIMEOUT,
	.identity = MODULE_NAME
पूर्ण;

अटल पूर्णांक ebc_c384_wdt_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा watchकरोg_device *wdd;

	अगर (!devm_request_region(dev, BASE_ADDR, ADDR_EXTENT, dev_name(dev))) अणु
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			BASE_ADDR, BASE_ADDR + ADDR_EXTENT);
		वापस -EBUSY;
	पूर्ण

	wdd = devm_kzalloc(dev, माप(*wdd), GFP_KERNEL);
	अगर (!wdd)
		वापस -ENOMEM;

	wdd->info = &ebc_c384_wdt_info;
	wdd->ops = &ebc_c384_wdt_ops;
	wdd->समयout = WATCHDOG_TIMEOUT;
	wdd->min_समयout = 1;
	wdd->max_समयout = WATCHDOG_MAX_TIMEOUT;

	watchकरोg_set_nowayout(wdd, nowayout);
	watchकरोg_init_समयout(wdd, समयout, dev);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, wdd);
पूर्ण

अटल काष्ठा isa_driver ebc_c384_wdt_driver = अणु
	.probe = ebc_c384_wdt_probe,
	.driver = अणु
		.name = MODULE_NAME
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ebc_c384_wdt_init(व्योम)
अणु
	अगर (!dmi_match(DMI_BOARD_NAME, "EBC-C384 SBC"))
		वापस -ENODEV;

	वापस isa_रेजिस्टर_driver(&ebc_c384_wdt_driver, 1);
पूर्ण

अटल व्योम __निकास ebc_c384_wdt_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&ebc_c384_wdt_driver);
पूर्ण

module_init(ebc_c384_wdt_init);
module_निकास(ebc_c384_wdt_निकास);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("WinSystems EBC-C384 watchdog timer driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("isa:" MODULE_NAME);
