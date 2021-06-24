<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Driver क्रम watchकरोg aspect of क्रम Zodiac Inflight Innovations RAVE
 * Supervisory Processor(SP) MCU
 *
 * Copyright (C) 2017 Zodiac Inflight Innovation
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/rave-sp.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/watchकरोg.h>

क्रमागत अणु
	RAVE_SP_RESET_BYTE = 1,
	RAVE_SP_RESET_REASON_NORMAL = 0,
	RAVE_SP_RESET_DELAY_MS = 500,
पूर्ण;

/**
 * काष्ठा rave_sp_wdt_variant - RAVE SP watchकरोg variant
 *
 * @max_समयout:	Largest possible watchकरोg समयout setting
 * @min_समयout:	Smallest possible watchकरोg समयout setting
 *
 * @configure:		Function to send configuration command
 * @restart:		Function to send "restart" command
 */
काष्ठा rave_sp_wdt_variant अणु
	अचिन्हित पूर्णांक max_समयout;
	अचिन्हित पूर्णांक min_समयout;

	पूर्णांक (*configure)(काष्ठा watchकरोg_device *, bool);
	पूर्णांक (*restart)(काष्ठा watchकरोg_device *);
पूर्ण;

/**
 * काष्ठा rave_sp_wdt - RAVE SP watchकरोg
 *
 * @wdd:		Underlying watchकरोg device
 * @sp:			Poपूर्णांकer to parent RAVE SP device
 * @variant:		Device specअगरic variant inक्रमmation
 * @reboot_notअगरier:	Reboot notअगरier implementing machine reset
 */
काष्ठा rave_sp_wdt अणु
	काष्ठा watchकरोg_device wdd;
	काष्ठा rave_sp *sp;
	स्थिर काष्ठा rave_sp_wdt_variant *variant;
	काष्ठा notअगरier_block reboot_notअगरier;
पूर्ण;

अटल काष्ठा rave_sp_wdt *to_rave_sp_wdt(काष्ठा watchकरोg_device *wdd)
अणु
	वापस container_of(wdd, काष्ठा rave_sp_wdt, wdd);
पूर्ण

अटल पूर्णांक rave_sp_wdt_exec(काष्ठा watchकरोg_device *wdd, व्योम *data,
			    माप_प्रकार data_size)
अणु
	वापस rave_sp_exec(to_rave_sp_wdt(wdd)->sp,
			    data, data_size, शून्य, 0);
पूर्ण

अटल पूर्णांक rave_sp_wdt_legacy_configure(काष्ठा watchकरोg_device *wdd, bool on)
अणु
	u8 cmd[] = अणु
		[0] = RAVE_SP_CMD_SW_WDT,
		[1] = 0,
		[2] = 0,
		[3] = on,
		[4] = on ? wdd->समयout : 0,
	पूर्ण;

	वापस rave_sp_wdt_exec(wdd, cmd, माप(cmd));
पूर्ण

अटल पूर्णांक rave_sp_wdt_rdu_configure(काष्ठा watchकरोg_device *wdd, bool on)
अणु
	u8 cmd[] = अणु
		[0] = RAVE_SP_CMD_SW_WDT,
		[1] = 0,
		[2] = on,
		[3] = (u8)wdd->समयout,
		[4] = (u8)(wdd->समयout >> 8),
	पूर्ण;

	वापस rave_sp_wdt_exec(wdd, cmd, माप(cmd));
पूर्ण

/**
 * rave_sp_wdt_configure - Configure watchकरोg device
 *
 * @wdd:	Device to configure
 * @on:		Desired state of the watchकरोg समयr (ON/OFF)
 *
 * This function configures two aspects of the watchकरोg समयr:
 *
 *  - Wheither it is ON or OFF
 *  - Its समयout duration
 *
 * with first aspect specअगरied via function argument and second via
 * the value of 'wdd->timeout'.
 */
अटल पूर्णांक rave_sp_wdt_configure(काष्ठा watchकरोg_device *wdd, bool on)
अणु
	वापस to_rave_sp_wdt(wdd)->variant->configure(wdd, on);
पूर्ण

अटल पूर्णांक rave_sp_wdt_legacy_restart(काष्ठा watchकरोg_device *wdd)
अणु
	u8 cmd[] = अणु
		[0] = RAVE_SP_CMD_RESET,
		[1] = 0,
		[2] = RAVE_SP_RESET_BYTE
	पूर्ण;

	वापस rave_sp_wdt_exec(wdd, cmd, माप(cmd));
पूर्ण

अटल पूर्णांक rave_sp_wdt_rdu_restart(काष्ठा watchकरोg_device *wdd)
अणु
	u8 cmd[] = अणु
		[0] = RAVE_SP_CMD_RESET,
		[1] = 0,
		[2] = RAVE_SP_RESET_BYTE,
		[3] = RAVE_SP_RESET_REASON_NORMAL
	पूर्ण;

	वापस rave_sp_wdt_exec(wdd, cmd, माप(cmd));
पूर्ण

अटल पूर्णांक rave_sp_wdt_reboot_notअगरier(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ action, व्योम *data)
अणु
	/*
	 * Restart handler is called in atomic context which means we
	 * can't communicate to SP via UART. Luckily क्रम use SP will
	 * रुको 500ms beक्रमe actually resetting us, so we ask it to करो
	 * so here and let the rest of the प्रणाली go on wrapping
	 * things up.
	 */
	अगर (action == SYS_DOWN || action == SYS_HALT) अणु
		काष्ठा rave_sp_wdt *sp_wd =
			container_of(nb, काष्ठा rave_sp_wdt, reboot_notअगरier);

		स्थिर पूर्णांक ret = sp_wd->variant->restart(&sp_wd->wdd);

		अगर (ret < 0)
			dev_err(sp_wd->wdd.parent,
				"Failed to issue restart command (%d)", ret);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक rave_sp_wdt_restart(काष्ठा watchकरोg_device *wdd,
			       अचिन्हित दीर्घ action, व्योम *data)
अणु
	/*
	 * The actual work was करोne by reboot notअगरier above. SP
	 * firmware रुकोs 500 ms beक्रमe issuing reset, so let's hang
	 * here क्रम twice that delay and hopefuly we'd never reach
	 * the वापस statement.
	 */
	mdelay(2 * RAVE_SP_RESET_DELAY_MS);

	वापस -EIO;
पूर्ण

अटल पूर्णांक rave_sp_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक ret;

	ret = rave_sp_wdt_configure(wdd, true);
	अगर (!ret)
		set_bit(WDOG_HW_RUNNING, &wdd->status);

	वापस ret;
पूर्ण

अटल पूर्णांक rave_sp_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	वापस rave_sp_wdt_configure(wdd, false);
पूर्ण

अटल पूर्णांक rave_sp_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				   अचिन्हित पूर्णांक समयout)
अणु
	wdd->समयout = समयout;

	वापस rave_sp_wdt_configure(wdd, watchकरोg_active(wdd));
पूर्ण

अटल पूर्णांक rave_sp_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	u8 cmd[] = अणु
		[0] = RAVE_SP_CMD_PET_WDT,
		[1] = 0,
	पूर्ण;

	वापस rave_sp_wdt_exec(wdd, cmd, माप(cmd));
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info rave_sp_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "RAVE SP Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops rave_sp_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = rave_sp_wdt_start,
	.stop = rave_sp_wdt_stop,
	.ping = rave_sp_wdt_ping,
	.set_समयout = rave_sp_wdt_set_समयout,
	.restart = rave_sp_wdt_restart,
पूर्ण;

अटल स्थिर काष्ठा rave_sp_wdt_variant rave_sp_wdt_legacy = अणु
	.max_समयout = 255,
	.min_समयout = 1,
	.configure = rave_sp_wdt_legacy_configure,
	.restart   = rave_sp_wdt_legacy_restart,
पूर्ण;

अटल स्थिर काष्ठा rave_sp_wdt_variant rave_sp_wdt_rdu = अणु
	.max_समयout = 180,
	.min_समयout = 60,
	.configure = rave_sp_wdt_rdu_configure,
	.restart   = rave_sp_wdt_rdu_restart,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rave_sp_wdt_of_match[] = अणु
	अणु
		.compatible = "zii,rave-sp-watchdog-legacy",
		.data = &rave_sp_wdt_legacy,
	पूर्ण,
	अणु
		.compatible = "zii,rave-sp-watchdog",
		.data = &rave_sp_wdt_rdu,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक rave_sp_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा rave_sp_wdt *sp_wd;
	काष्ठा nvmem_cell *cell;
	__le16 समयout = 0;
	पूर्णांक ret;

	sp_wd = devm_kzalloc(dev, माप(*sp_wd), GFP_KERNEL);
	अगर (!sp_wd)
		वापस -ENOMEM;

	sp_wd->variant = of_device_get_match_data(dev);
	sp_wd->sp      = dev_get_drvdata(dev->parent);

	wdd              = &sp_wd->wdd;
	wdd->parent      = dev;
	wdd->info        = &rave_sp_wdt_info;
	wdd->ops         = &rave_sp_wdt_ops;
	wdd->min_समयout = sp_wd->variant->min_समयout;
	wdd->max_समयout = sp_wd->variant->max_समयout;
	wdd->status      = WATCHDOG_NOWAYOUT_INIT_STATUS;
	wdd->समयout     = 60;

	cell = nvmem_cell_get(dev, "wdt-timeout");
	अगर (!IS_ERR(cell)) अणु
		माप_प्रकार len;
		व्योम *value = nvmem_cell_पढ़ो(cell, &len);

		अगर (!IS_ERR(value)) अणु
			स_नकल(&समयout, value, min(len, माप(समयout)));
			kमुक्त(value);
		पूर्ण
		nvmem_cell_put(cell);
	पूर्ण
	watchकरोg_init_समयout(wdd, le16_to_cpu(समयout), dev);
	watchकरोg_set_restart_priority(wdd, 255);
	watchकरोg_stop_on_unरेजिस्टर(wdd);

	sp_wd->reboot_notअगरier.notअगरier_call = rave_sp_wdt_reboot_notअगरier;
	ret = devm_रेजिस्टर_reboot_notअगरier(dev, &sp_wd->reboot_notअगरier);
	अगर (ret) अणु
		dev_err(dev, "Failed to register reboot notifier\n");
		वापस ret;
	पूर्ण

	/*
	 * We करोn't know if watchdog is running now. To be sure, let's
	 * start it and depend on watchकरोg core to ping it
	 */
	wdd->max_hw_heartbeat_ms = wdd->max_समयout * 1000;
	ret = rave_sp_wdt_start(wdd);
	अगर (ret) अणु
		dev_err(dev, "Watchdog didn't start\n");
		वापस ret;
	पूर्ण

	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret) अणु
		rave_sp_wdt_stop(wdd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rave_sp_wdt_driver = अणु
	.probe = rave_sp_wdt_probe,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = rave_sp_wdt_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rave_sp_wdt_driver);

MODULE_DEVICE_TABLE(of, rave_sp_wdt_of_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrey Vostrikov <andrey.vostrikov@cogentembedded.com>");
MODULE_AUTHOR("Nikita Yushchenko <nikita.yoush@cogentembedded.com>");
MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("RAVE SP Watchdog driver");
MODULE_ALIAS("platform:rave-sp-watchdog");
