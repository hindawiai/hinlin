<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018-2019 NXP.
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

#घोषणा DEFAULT_TIMEOUT 60
/*
 * Software समयr tick implemented in scfw side, support 10ms to 0xffffffff ms
 * in theory, but क्रम normal हाल, 1s~128s is enough, you can change this max
 * value in हाल it's not enough.
 */
#घोषणा MAX_TIMEOUT 128

#घोषणा IMX_SIP_TIMER			0xC2000002
#घोषणा IMX_SIP_TIMER_START_WDOG		0x01
#घोषणा IMX_SIP_TIMER_STOP_WDOG		0x02
#घोषणा IMX_SIP_TIMER_SET_WDOG_ACT	0x03
#घोषणा IMX_SIP_TIMER_PING_WDOG		0x04
#घोषणा IMX_SIP_TIMER_SET_TIMEOUT_WDOG	0x05
#घोषणा IMX_SIP_TIMER_GET_WDOG_STAT	0x06
#घोषणा IMX_SIP_TIMER_SET_PRETIME_WDOG	0x07

#घोषणा SC_TIMER_WDOG_ACTION_PARTITION	0

#घोषणा SC_IRQ_WDOG			1
#घोषणा SC_IRQ_GROUP_WDOG		1

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0000);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा imx_sc_wdt_device अणु
	काष्ठा watchकरोg_device wdd;
	काष्ठा notअगरier_block wdt_notअगरier;
पूर्ण;

अटल पूर्णांक imx_sc_wdt_ping(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(IMX_SIP_TIMER, IMX_SIP_TIMER_PING_WDOG,
		      0, 0, 0, 0, 0, 0, &res);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_sc_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(IMX_SIP_TIMER, IMX_SIP_TIMER_START_WDOG,
		      0, 0, 0, 0, 0, 0, &res);
	अगर (res.a0)
		वापस -EACCES;

	arm_smccc_smc(IMX_SIP_TIMER, IMX_SIP_TIMER_SET_WDOG_ACT,
		      SC_TIMER_WDOG_ACTION_PARTITION,
		      0, 0, 0, 0, 0, &res);
	वापस res.a0 ? -EACCES : 0;
पूर्ण

अटल पूर्णांक imx_sc_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(IMX_SIP_TIMER, IMX_SIP_TIMER_STOP_WDOG,
		      0, 0, 0, 0, 0, 0, &res);

	वापस res.a0 ? -EACCES : 0;
पूर्ण

अटल पूर्णांक imx_sc_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा arm_smccc_res res;

	wकरोg->समयout = समयout;
	arm_smccc_smc(IMX_SIP_TIMER, IMX_SIP_TIMER_SET_TIMEOUT_WDOG,
		      समयout * 1000, 0, 0, 0, 0, 0, &res);

	वापस res.a0 ? -EACCES : 0;
पूर्ण

अटल पूर्णांक imx_sc_wdt_set_preसमयout(काष्ठा watchकरोg_device *wकरोg,
				     अचिन्हित पूर्णांक preसमयout)
अणु
	काष्ठा arm_smccc_res res;

	/*
	 * SCU firmware calculates preसमयout based on current समय
	 * stamp instead of watchकरोg समयout stamp, need to convert
	 * the preसमयout to SCU firmware's समयout value.
	 */
	arm_smccc_smc(IMX_SIP_TIMER, IMX_SIP_TIMER_SET_PRETIME_WDOG,
		      (wकरोg->समयout - preसमयout) * 1000, 0, 0, 0,
		      0, 0, &res);
	अगर (res.a0)
		वापस -EACCES;

	wकरोg->preसमयout = preसमयout;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_sc_wdt_notअगरy(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ event, व्योम *group)
अणु
	काष्ठा imx_sc_wdt_device *imx_sc_wdd =
				 container_of(nb,
					      काष्ठा imx_sc_wdt_device,
					      wdt_notअगरier);

	अगर (event & SC_IRQ_WDOG &&
	    *(u8 *)group == SC_IRQ_GROUP_WDOG)
		watchकरोg_notअगरy_preसमयout(&imx_sc_wdd->wdd);

	वापस 0;
पूर्ण

अटल व्योम imx_sc_wdt_action(व्योम *data)
अणु
	काष्ठा notअगरier_block *wdt_notअगरier = data;

	imx_scu_irq_unरेजिस्टर_notअगरier(wdt_notअगरier);
	imx_scu_irq_group_enable(SC_IRQ_GROUP_WDOG,
				 SC_IRQ_WDOG,
				 false);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops imx_sc_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = imx_sc_wdt_start,
	.stop  = imx_sc_wdt_stop,
	.ping  = imx_sc_wdt_ping,
	.set_समयout = imx_sc_wdt_set_समयout,
	.set_preसमयout = imx_sc_wdt_set_preसमयout,
पूर्ण;

अटल काष्ठा watchकरोg_info imx_sc_wdt_info = अणु
	.identity	= "i.MX SC watchdog timer",
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

अटल पूर्णांक imx_sc_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_sc_wdt_device *imx_sc_wdd;
	काष्ठा watchकरोg_device *wकरोg;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	imx_sc_wdd = devm_kzalloc(dev, माप(*imx_sc_wdd), GFP_KERNEL);
	अगर (!imx_sc_wdd)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, imx_sc_wdd);

	wकरोg = &imx_sc_wdd->wdd;
	wकरोg->info = &imx_sc_wdt_info;
	wकरोg->ops = &imx_sc_wdt_ops;
	wकरोg->min_समयout = 1;
	wकरोg->max_समयout = MAX_TIMEOUT;
	wकरोg->parent = dev;
	wकरोg->समयout = DEFAULT_TIMEOUT;

	watchकरोg_init_समयout(wकरोg, 0, dev);

	ret = imx_sc_wdt_set_समयout(wकरोg, wकरोg->समयout);
	अगर (ret)
		वापस ret;

	watchकरोg_stop_on_reboot(wकरोg);
	watchकरोg_stop_on_unरेजिस्टर(wकरोg);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, wकरोg);
	अगर (ret)
		वापस ret;

	ret = imx_scu_irq_group_enable(SC_IRQ_GROUP_WDOG,
				       SC_IRQ_WDOG,
				       true);
	अगर (ret) अणु
		dev_warn(dev, "Enable irq failed, pretimeout NOT supported\n");
		वापस 0;
	पूर्ण

	imx_sc_wdd->wdt_notअगरier.notअगरier_call = imx_sc_wdt_notअगरy;
	ret = imx_scu_irq_रेजिस्टर_notअगरier(&imx_sc_wdd->wdt_notअगरier);
	अगर (ret) अणु
		imx_scu_irq_group_enable(SC_IRQ_GROUP_WDOG,
					 SC_IRQ_WDOG,
					 false);
		dev_warn(dev,
			 "Register irq notifier failed, pretimeout NOT supported\n");
		वापस 0;
	पूर्ण

	ret = devm_add_action_or_reset(dev, imx_sc_wdt_action,
				       &imx_sc_wdd->wdt_notअगरier);
	अगर (!ret)
		imx_sc_wdt_info.options |= WDIOF_PRETIMEOUT;
	अन्यथा
		dev_warn(dev, "Add action failed, pretimeout NOT supported\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_sc_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा imx_sc_wdt_device *imx_sc_wdd = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&imx_sc_wdd->wdd))
		imx_sc_wdt_stop(&imx_sc_wdd->wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_sc_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा imx_sc_wdt_device *imx_sc_wdd = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&imx_sc_wdd->wdd))
		imx_sc_wdt_start(&imx_sc_wdd->wdd);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(imx_sc_wdt_pm_ops,
			 imx_sc_wdt_suspend, imx_sc_wdt_resume);

अटल स्थिर काष्ठा of_device_id imx_sc_wdt_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-sc-wdt", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_sc_wdt_dt_ids);

अटल काष्ठा platक्रमm_driver imx_sc_wdt_driver = अणु
	.probe		= imx_sc_wdt_probe,
	.driver		= अणु
		.name	= "imx-sc-wdt",
		.of_match_table = imx_sc_wdt_dt_ids,
		.pm	= &imx_sc_wdt_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_sc_wdt_driver);

MODULE_AUTHOR("Robin Gong <yibin.gong@nxp.com>");
MODULE_DESCRIPTION("NXP i.MX system controller watchdog driver");
MODULE_LICENSE("GPL v2");
