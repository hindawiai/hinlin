<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM Secure Monitor Call watchकरोg driver
 *
 * Copyright 2020 Google LLC.
 * Julius Werner <jwerner@chromium.org>
 * Based on mtk_wdt.c
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <uapi/linux/psci.h>

#घोषणा DRV_NAME		"arm_smc_wdt"
#घोषणा DRV_VERSION		"1.0"

क्रमागत smcwd_call अणु
	SMCWD_INIT		= 0,
	SMCWD_SET_TIMEOUT	= 1,
	SMCWD_ENABLE		= 2,
	SMCWD_PET		= 3,
	SMCWD_GET_TIMELEFT	= 4,
पूर्ण;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित पूर्णांक समयout;

अटल पूर्णांक smcwd_call(काष्ठा watchकरोg_device *wdd, क्रमागत smcwd_call call,
		      अचिन्हित दीर्घ arg, काष्ठा arm_smccc_res *res)
अणु
	काष्ठा arm_smccc_res local_res;

	अगर (!res)
		res = &local_res;

	arm_smccc_smc((u32)(uपूर्णांकptr_t)watchकरोg_get_drvdata(wdd), call, arg, 0,
		      0, 0, 0, 0, res);

	अगर (res->a0 == PSCI_RET_NOT_SUPPORTED)
		वापस -ENODEV;
	अगर (res->a0 == PSCI_RET_INVALID_PARAMS)
		वापस -EINVAL;
	अगर (res->a0 != PSCI_RET_SUCCESS)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक smcwd_ping(काष्ठा watchकरोg_device *wdd)
अणु
	वापस smcwd_call(wdd, SMCWD_PET, 0, शून्य);
पूर्ण

अटल अचिन्हित पूर्णांक smcwd_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा arm_smccc_res res;

	smcwd_call(wdd, SMCWD_GET_TIMELEFT, 0, &res);
	अगर (res.a0)
		वापस 0;
	वापस res.a1;
पूर्ण

अटल पूर्णांक smcwd_set_समयout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक res;

	res = smcwd_call(wdd, SMCWD_SET_TIMEOUT, समयout, शून्य);
	अगर (!res)
		wdd->समयout = समयout;
	वापस res;
पूर्ण

अटल पूर्णांक smcwd_stop(काष्ठा watchकरोg_device *wdd)
अणु
	वापस smcwd_call(wdd, SMCWD_ENABLE, 0, शून्य);
पूर्ण

अटल पूर्णांक smcwd_start(काष्ठा watchकरोg_device *wdd)
अणु
	वापस smcwd_call(wdd, SMCWD_ENABLE, 1, शून्य);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info smcwd_info = अणु
	.identity	= DRV_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops smcwd_ops = अणु
	.start		= smcwd_start,
	.stop		= smcwd_stop,
	.ping		= smcwd_ping,
	.set_समयout	= smcwd_set_समयout,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops smcwd_समयleft_ops = अणु
	.start		= smcwd_start,
	.stop		= smcwd_stop,
	.ping		= smcwd_ping,
	.set_समयout	= smcwd_set_समयout,
	.get_समयleft	= smcwd_get_समयleft,
पूर्ण;

अटल पूर्णांक smcwd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा watchकरोg_device *wdd;
	पूर्णांक err;
	काष्ठा arm_smccc_res res;
	u32 smc_func_id;

	wdd = devm_kzalloc(&pdev->dev, माप(*wdd), GFP_KERNEL);
	अगर (!wdd)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, wdd);

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "arm,smc-id",
				 &smc_func_id))
		smc_func_id = 0x82003D06;
	watchकरोg_set_drvdata(wdd, (व्योम *)(uपूर्णांकptr_t)smc_func_id);

	err = smcwd_call(wdd, SMCWD_INIT, 0, &res);
	अगर (err < 0)
		वापस err;

	wdd->info = &smcwd_info;
	/* get_समयleft is optional */
	अगर (smcwd_call(wdd, SMCWD_GET_TIMELEFT, 0, शून्य))
		wdd->ops = &smcwd_ops;
	अन्यथा
		wdd->ops = &smcwd_समयleft_ops;
	wdd->समयout = res.a2;
	wdd->max_समयout = res.a2;
	wdd->min_समयout = res.a1;
	wdd->parent = &pdev->dev;

	watchकरोg_stop_on_reboot(wdd);
	watchकरोg_stop_on_unरेजिस्टर(wdd);
	watchकरोg_set_nowayout(wdd, nowayout);
	watchकरोg_init_समयout(wdd, समयout, &pdev->dev);
	err = smcwd_set_समयout(wdd, wdd->समयout);
	अगर (err)
		वापस err;

	err = devm_watchकरोg_रेजिस्टर_device(&pdev->dev, wdd);
	अगर (err)
		वापस err;

	dev_info(&pdev->dev,
		 "Watchdog registered (timeout=%d sec, nowayout=%d)\n",
		 wdd->समयout, nowayout);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id smcwd_dt_ids[] = अणु
	अणु .compatible = "arm,smc-wdt" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, smcwd_dt_ids);

अटल काष्ठा platक्रमm_driver smcwd_driver = अणु
	.probe		= smcwd_probe,
	.driver		= अणु
		.name		= DRV_NAME,
		.of_match_table	= smcwd_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(smcwd_driver);

module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog heartbeat in seconds");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
			__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Julius Werner <jwerner@chromium.org>");
MODULE_DESCRIPTION("ARM Secure Monitor Call Watchdog Driver");
MODULE_VERSION(DRV_VERSION);
