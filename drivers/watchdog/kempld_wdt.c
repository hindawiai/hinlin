<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kontron PLD watchकरोg driver
 *
 * Copyright (c) 2010-2013 Kontron Europe GmbH
 * Author: Michael Brunner <michael.brunner@kontron.com>
 *
 * Note: From the PLD watchकरोg poपूर्णांक of view समयout and preसमयout are
 *       defined dअगरferently than in the kernel.
 *       First the preसमयout stage runs out beक्रमe the समयout stage माला_लो
 *       active.
 *
 * Kernel/API:                     P-----| preसमयout
 *               |-----------------------T समयout
 * Watchकरोg:     |-----------------P       preसमयout_stage
 *                                 |-----T समयout_stage
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/kempld.h>

#घोषणा KEMPLD_WDT_STAGE_TIMEOUT(x)	(0x1b + (x) * 4)
#घोषणा KEMPLD_WDT_STAGE_CFG(x)		(0x18 + (x))
#घोषणा STAGE_CFG_GET_PRESCALER(x)	(((x) & 0x30) >> 4)
#घोषणा STAGE_CFG_SET_PRESCALER(x)	(((x) & 0x3) << 4)
#घोषणा STAGE_CFG_PRESCALER_MASK	0x30
#घोषणा STAGE_CFG_ACTION_MASK		0x7
#घोषणा STAGE_CFG_ASSERT		(1 << 3)

#घोषणा KEMPLD_WDT_MAX_STAGES		2
#घोषणा KEMPLD_WDT_KICK			0x16
#घोषणा KEMPLD_WDT_CFG			0x17
#घोषणा KEMPLD_WDT_CFG_ENABLE		0x10
#घोषणा KEMPLD_WDT_CFG_ENABLE_LOCK	0x8
#घोषणा KEMPLD_WDT_CFG_GLOBAL_LOCK	0x80

क्रमागत अणु
	ACTION_NONE = 0,
	ACTION_RESET,
	ACTION_NMI,
	ACTION_SMI,
	ACTION_SCI,
	ACTION_DELAY,
पूर्ण;

क्रमागत अणु
	STAGE_TIMEOUT = 0,
	STAGE_PRETIMEOUT,
पूर्ण;

क्रमागत अणु
	PRESCALER_21 = 0,
	PRESCALER_17,
	PRESCALER_12,
पूर्ण;

अटल स्थिर u32 kempld_prescaler[] = अणु
	[PRESCALER_21] = (1 << 21) - 1,
	[PRESCALER_17] = (1 << 17) - 1,
	[PRESCALER_12] = (1 << 12) - 1,
	0,
पूर्ण;

काष्ठा kempld_wdt_stage अणु
	अचिन्हित पूर्णांक	id;
	u32		mask;
पूर्ण;

काष्ठा kempld_wdt_data अणु
	काष्ठा kempld_device_data	*pld;
	काष्ठा watchकरोg_device		wdd;
	अचिन्हित पूर्णांक			preसमयout;
	काष्ठा kempld_wdt_stage		stage[KEMPLD_WDT_MAX_STAGES];
#अगर_घोषित CONFIG_PM
	u8				pm_status_store;
#पूर्ण_अगर
पूर्ण;

#घोषणा DEFAULT_TIMEOUT		30 /* seconds */
#घोषणा DEFAULT_PRETIMEOUT	0

अटल अचिन्हित पूर्णांक समयout = DEFAULT_TIMEOUT;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. (>=0, default="
	__MODULE_STRING(DEFAULT_TIMEOUT) ")");

अटल अचिन्हित पूर्णांक preसमयout = DEFAULT_PRETIMEOUT;
module_param(preसमयout, uपूर्णांक, 0);
MODULE_PARM_DESC(preसमयout,
	"Watchdog pretimeout in seconds. (>=0, default="
	__MODULE_STRING(DEFAULT_PRETIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक kempld_wdt_set_stage_action(काष्ठा kempld_wdt_data *wdt_data,
					काष्ठा kempld_wdt_stage *stage,
					u8 action)
अणु
	काष्ठा kempld_device_data *pld = wdt_data->pld;
	u8 stage_cfg;

	अगर (!stage || !stage->mask)
		वापस -EINVAL;

	kempld_get_mutex(pld);
	stage_cfg = kempld_पढ़ो8(pld, KEMPLD_WDT_STAGE_CFG(stage->id));
	stage_cfg &= ~STAGE_CFG_ACTION_MASK;
	stage_cfg |= (action & STAGE_CFG_ACTION_MASK);

	अगर (action == ACTION_RESET)
		stage_cfg |= STAGE_CFG_ASSERT;
	अन्यथा
		stage_cfg &= ~STAGE_CFG_ASSERT;

	kempld_ग_लिखो8(pld, KEMPLD_WDT_STAGE_CFG(stage->id), stage_cfg);
	kempld_release_mutex(pld);

	वापस 0;
पूर्ण

अटल पूर्णांक kempld_wdt_set_stage_समयout(काष्ठा kempld_wdt_data *wdt_data,
					काष्ठा kempld_wdt_stage *stage,
					अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा kempld_device_data *pld = wdt_data->pld;
	u32 prescaler;
	u64 stage_समयout64;
	u32 stage_समयout;
	u32 reमुख्यder;
	u8 stage_cfg;

	prescaler = kempld_prescaler[PRESCALER_21];

	अगर (!stage)
		वापस -EINVAL;

	stage_समयout64 = (u64)समयout * pld->pld_घड़ी;
	reमुख्यder = करो_भाग(stage_समयout64, prescaler);
	अगर (reमुख्यder)
		stage_समयout64++;

	अगर (stage_समयout64 > stage->mask)
		वापस -EINVAL;

	stage_समयout = stage_समयout64 & stage->mask;

	kempld_get_mutex(pld);
	stage_cfg = kempld_पढ़ो8(pld, KEMPLD_WDT_STAGE_CFG(stage->id));
	stage_cfg &= ~STAGE_CFG_PRESCALER_MASK;
	stage_cfg |= STAGE_CFG_SET_PRESCALER(PRESCALER_21);
	kempld_ग_लिखो8(pld, KEMPLD_WDT_STAGE_CFG(stage->id), stage_cfg);
	kempld_ग_लिखो32(pld, KEMPLD_WDT_STAGE_TIMEOUT(stage->id),
			stage_समयout);
	kempld_release_mutex(pld);

	वापस 0;
पूर्ण

/*
 * kempld_get_mutex must be called prior to calling this function.
 */
अटल अचिन्हित पूर्णांक kempld_wdt_get_समयout(काष्ठा kempld_wdt_data *wdt_data,
						काष्ठा kempld_wdt_stage *stage)
अणु
	काष्ठा kempld_device_data *pld = wdt_data->pld;
	अचिन्हित पूर्णांक समयout;
	u64 stage_समयout;
	u32 prescaler;
	u32 reमुख्यder;
	u8 stage_cfg;

	अगर (!stage->mask)
		वापस 0;

	stage_cfg = kempld_पढ़ो8(pld, KEMPLD_WDT_STAGE_CFG(stage->id));
	stage_समयout = kempld_पढ़ो32(pld, KEMPLD_WDT_STAGE_TIMEOUT(stage->id));
	prescaler = kempld_prescaler[STAGE_CFG_GET_PRESCALER(stage_cfg)];

	stage_समयout = (stage_समयout & stage->mask) * prescaler;
	reमुख्यder = करो_भाग(stage_समयout, pld->pld_घड़ी);
	अगर (reमुख्यder)
		stage_समयout++;

	समयout = stage_समयout;
	WARN_ON_ONCE(समयout != stage_समयout);

	वापस समयout;
पूर्ण

अटल पूर्णांक kempld_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
					अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा kempld_wdt_data *wdt_data = watchकरोg_get_drvdata(wdd);
	काष्ठा kempld_wdt_stage *preसमयout_stage;
	काष्ठा kempld_wdt_stage *समयout_stage;
	पूर्णांक ret;

	समयout_stage = &wdt_data->stage[STAGE_TIMEOUT];
	preसमयout_stage = &wdt_data->stage[STAGE_PRETIMEOUT];

	अगर (preसमयout_stage->mask && wdt_data->preसमयout > 0)
		समयout = wdt_data->preसमयout;

	ret = kempld_wdt_set_stage_action(wdt_data, समयout_stage,
						ACTION_RESET);
	अगर (ret)
		वापस ret;
	ret = kempld_wdt_set_stage_समयout(wdt_data, समयout_stage,
						समयout);
	अगर (ret)
		वापस ret;

	wdd->समयout = समयout;
	वापस 0;
पूर्ण

अटल पूर्णांक kempld_wdt_set_preसमयout(काष्ठा watchकरोg_device *wdd,
					अचिन्हित पूर्णांक preसमयout)
अणु
	काष्ठा kempld_wdt_data *wdt_data = watchकरोg_get_drvdata(wdd);
	काष्ठा kempld_wdt_stage *preसमयout_stage;
	u8 action = ACTION_NONE;
	पूर्णांक ret;

	preसमयout_stage = &wdt_data->stage[STAGE_PRETIMEOUT];

	अगर (!preसमयout_stage->mask)
		वापस -ENXIO;

	अगर (preसमयout > wdd->समयout)
		वापस -EINVAL;

	अगर (preसमयout > 0)
		action = ACTION_NMI;

	ret = kempld_wdt_set_stage_action(wdt_data, preसमयout_stage,
						action);
	अगर (ret)
		वापस ret;
	ret = kempld_wdt_set_stage_समयout(wdt_data, preसमयout_stage,
						wdd->समयout - preसमयout);
	अगर (ret)
		वापस ret;

	wdt_data->preसमयout = preसमयout;
	वापस 0;
पूर्ण

अटल व्योम kempld_wdt_update_समयouts(काष्ठा kempld_wdt_data *wdt_data)
अणु
	काष्ठा kempld_device_data *pld = wdt_data->pld;
	काष्ठा kempld_wdt_stage *preसमयout_stage;
	काष्ठा kempld_wdt_stage *समयout_stage;
	अचिन्हित पूर्णांक preसमयout, समयout;

	preसमयout_stage = &wdt_data->stage[STAGE_PRETIMEOUT];
	समयout_stage = &wdt_data->stage[STAGE_TIMEOUT];

	kempld_get_mutex(pld);
	preसमयout = kempld_wdt_get_समयout(wdt_data, preसमयout_stage);
	समयout = kempld_wdt_get_समयout(wdt_data, समयout_stage);
	kempld_release_mutex(pld);

	अगर (preसमयout)
		wdt_data->preसमयout = समयout;
	अन्यथा
		wdt_data->preसमयout = 0;

	wdt_data->wdd.समयout = preसमयout + समयout;
पूर्ण

अटल पूर्णांक kempld_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा kempld_wdt_data *wdt_data = watchकरोg_get_drvdata(wdd);
	काष्ठा kempld_device_data *pld = wdt_data->pld;
	u8 status;
	पूर्णांक ret;

	ret = kempld_wdt_set_समयout(wdd, wdd->समयout);
	अगर (ret)
		वापस ret;

	kempld_get_mutex(pld);
	status = kempld_पढ़ो8(pld, KEMPLD_WDT_CFG);
	status |= KEMPLD_WDT_CFG_ENABLE;
	kempld_ग_लिखो8(pld, KEMPLD_WDT_CFG, status);
	status = kempld_पढ़ो8(pld, KEMPLD_WDT_CFG);
	kempld_release_mutex(pld);

	/* Check अगर the watchकरोg was enabled */
	अगर (!(status & KEMPLD_WDT_CFG_ENABLE))
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल पूर्णांक kempld_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा kempld_wdt_data *wdt_data = watchकरोg_get_drvdata(wdd);
	काष्ठा kempld_device_data *pld = wdt_data->pld;
	u8 status;

	kempld_get_mutex(pld);
	status = kempld_पढ़ो8(pld, KEMPLD_WDT_CFG);
	status &= ~KEMPLD_WDT_CFG_ENABLE;
	kempld_ग_लिखो8(pld, KEMPLD_WDT_CFG, status);
	status = kempld_पढ़ो8(pld, KEMPLD_WDT_CFG);
	kempld_release_mutex(pld);

	/* Check अगर the watchकरोg was disabled */
	अगर (status & KEMPLD_WDT_CFG_ENABLE)
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल पूर्णांक kempld_wdt_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा kempld_wdt_data *wdt_data = watchकरोg_get_drvdata(wdd);
	काष्ठा kempld_device_data *pld = wdt_data->pld;

	kempld_get_mutex(pld);
	kempld_ग_लिखो8(pld, KEMPLD_WDT_KICK, 'K');
	kempld_release_mutex(pld);

	वापस 0;
पूर्ण

अटल दीर्घ kempld_wdt_ioctl(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा kempld_wdt_data *wdt_data = watchकरोg_get_drvdata(wdd);
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक ret = -ENOIOCTLCMD;
	पूर्णांक __user *p = argp;
	पूर्णांक new_value;

	चयन (cmd) अणु
	हाल WDIOC_SETPRETIMEOUT:
		अगर (get_user(new_value, p))
			वापस -EFAULT;
		ret = kempld_wdt_set_preसमयout(wdd, new_value);
		अगर (ret)
			वापस ret;
		ret = kempld_wdt_keepalive(wdd);
		अवरोध;
	हाल WDIOC_GETPRETIMEOUT:
		ret = put_user(wdt_data->preसमयout, (पूर्णांक __user *)arg);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kempld_wdt_probe_stages(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा kempld_wdt_data *wdt_data = watchकरोg_get_drvdata(wdd);
	काष्ठा kempld_device_data *pld = wdt_data->pld;
	काष्ठा kempld_wdt_stage *preसमयout_stage;
	काष्ठा kempld_wdt_stage *समयout_stage;
	u8 index, data, data_orig;
	u32 mask;
	पूर्णांक i, j;

	preसमयout_stage = &wdt_data->stage[STAGE_PRETIMEOUT];
	समयout_stage = &wdt_data->stage[STAGE_TIMEOUT];

	preसमयout_stage->mask = 0;
	समयout_stage->mask = 0;

	क्रम (i = 0; i < 3; i++) अणु
		index = KEMPLD_WDT_STAGE_TIMEOUT(i);
		mask = 0;

		kempld_get_mutex(pld);
		/* Probe each byte inभागidually. */
		क्रम (j = 0; j < 4; j++) अणु
			data_orig = kempld_पढ़ो8(pld, index + j);
			kempld_ग_लिखो8(pld, index + j, 0x00);
			data = kempld_पढ़ो8(pld, index + j);
			/* A failed ग_लिखो means this byte is reserved */
			अगर (data != 0x00)
				अवरोध;
			kempld_ग_लिखो8(pld, index + j, data_orig);
			mask |= 0xff << (j * 8);
		पूर्ण
		kempld_release_mutex(pld);

		/* Assign available stages to समयout and preसमयout */
		अगर (!समयout_stage->mask) अणु
			समयout_stage->mask = mask;
			समयout_stage->id = i;
		पूर्ण अन्यथा अणु
			अगर (pld->feature_mask & KEMPLD_FEATURE_BIT_NMI) अणु
				preसमयout_stage->mask = समयout_stage->mask;
				समयout_stage->mask = mask;
				preसमयout_stage->id = समयout_stage->id;
				समयout_stage->id = i;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!समयout_stage->mask)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info kempld_wdt_info = अणु
	.identity	= "KEMPLD Watchdog",
	.options	= WDIOF_SETTIMEOUT |
			WDIOF_KEEPALIVEPING |
			WDIOF_MAGICCLOSE |
			WDIOF_PRETIMEOUT
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops kempld_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= kempld_wdt_start,
	.stop		= kempld_wdt_stop,
	.ping		= kempld_wdt_keepalive,
	.set_समयout	= kempld_wdt_set_समयout,
	.ioctl		= kempld_wdt_ioctl,
पूर्ण;

अटल पूर्णांक kempld_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kempld_device_data *pld = dev_get_drvdata(pdev->dev.parent);
	काष्ठा kempld_wdt_data *wdt_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdd;
	u8 status;
	पूर्णांक ret = 0;

	wdt_data = devm_kzalloc(dev, माप(*wdt_data), GFP_KERNEL);
	अगर (!wdt_data)
		वापस -ENOMEM;

	wdt_data->pld = pld;
	wdd = &wdt_data->wdd;
	wdd->parent = dev;

	kempld_get_mutex(pld);
	status = kempld_पढ़ो8(pld, KEMPLD_WDT_CFG);
	kempld_release_mutex(pld);

	/* Enable nowayout अगर watchकरोg is alपढ़ोy locked */
	अगर (status & (KEMPLD_WDT_CFG_ENABLE_LOCK |
			KEMPLD_WDT_CFG_GLOBAL_LOCK)) अणु
		अगर (!nowayout)
			dev_warn(dev,
				 "Forcing nowayout - watchdog lock enabled!\n");
		nowayout = true;
	पूर्ण

	wdd->info = &kempld_wdt_info;
	wdd->ops = &kempld_wdt_ops;

	watchकरोg_set_drvdata(wdd, wdt_data);
	watchकरोg_set_nowayout(wdd, nowayout);

	ret = kempld_wdt_probe_stages(wdd);
	अगर (ret)
		वापस ret;

	kempld_wdt_set_समयout(wdd, समयout);
	kempld_wdt_set_preसमयout(wdd, preसमयout);

	/* Check अगर watchकरोg is alपढ़ोy enabled */
	अगर (status & KEMPLD_WDT_CFG_ENABLE) अणु
		/* Get current watchकरोg settings */
		kempld_wdt_update_समयouts(wdt_data);
		dev_info(dev, "Watchdog was already enabled\n");
	पूर्ण

	platक्रमm_set_drvdata(pdev, wdt_data);
	watchकरोg_stop_on_reboot(wdd);
	watchकरोg_stop_on_unरेजिस्टर(wdd);
	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	dev_info(dev, "Watchdog registered with %ds timeout\n", wdd->समयout);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
/* Disable watchकरोg अगर it is active during suspend */
अटल पूर्णांक kempld_wdt_suspend(काष्ठा platक्रमm_device *pdev,
				pm_message_t message)
अणु
	काष्ठा kempld_wdt_data *wdt_data = platक्रमm_get_drvdata(pdev);
	काष्ठा kempld_device_data *pld = wdt_data->pld;
	काष्ठा watchकरोg_device *wdd = &wdt_data->wdd;

	kempld_get_mutex(pld);
	wdt_data->pm_status_store = kempld_पढ़ो8(pld, KEMPLD_WDT_CFG);
	kempld_release_mutex(pld);

	kempld_wdt_update_समयouts(wdt_data);

	अगर (wdt_data->pm_status_store & KEMPLD_WDT_CFG_ENABLE)
		वापस kempld_wdt_stop(wdd);

	वापस 0;
पूर्ण

/* Enable watchकरोg and configure it अगर necessary */
अटल पूर्णांक kempld_wdt_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kempld_wdt_data *wdt_data = platक्रमm_get_drvdata(pdev);
	काष्ठा watchकरोg_device *wdd = &wdt_data->wdd;

	/*
	 * If watchकरोg was stopped beक्रमe suspend be sure it माला_लो disabled
	 * again, क्रम the हाल BIOS has enabled it during resume
	 */
	अगर (wdt_data->pm_status_store & KEMPLD_WDT_CFG_ENABLE)
		वापस kempld_wdt_start(wdd);
	अन्यथा
		वापस kempld_wdt_stop(wdd);
पूर्ण
#अन्यथा
#घोषणा kempld_wdt_suspend	शून्य
#घोषणा kempld_wdt_resume	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver kempld_wdt_driver = अणु
	.driver		= अणु
		.name	= "kempld-wdt",
	पूर्ण,
	.probe		= kempld_wdt_probe,
	.suspend	= kempld_wdt_suspend,
	.resume		= kempld_wdt_resume,
पूर्ण;

module_platक्रमm_driver(kempld_wdt_driver);

MODULE_DESCRIPTION("KEM PLD Watchdog Driver");
MODULE_AUTHOR("Michael Brunner <michael.brunner@kontron.com>");
MODULE_LICENSE("GPL");
