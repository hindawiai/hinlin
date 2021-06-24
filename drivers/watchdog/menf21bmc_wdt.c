<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  MEN 14F021P00 Board Management Controller (BMC) Watchकरोg Driver.
 *
 *  Copyright (C) 2014 MEN Mikro Elektronik Nuernberg GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>

#घोषणा DEVNAME "menf21bmc_wdt"

#घोषणा BMC_CMD_WD_ON		0x11
#घोषणा BMC_CMD_WD_OFF		0x12
#घोषणा BMC_CMD_WD_TRIG		0x13
#घोषणा BMC_CMD_WD_TIME		0x14
#घोषणा BMC_CMD_WD_STATE	0x17
#घोषणा BMC_WD_OFF_VAL		0x69
#घोषणा BMC_CMD_RST_RSN		0x92

#घोषणा BMC_WD_TIMEOUT_MIN	1	/* in sec */
#घोषणा BMC_WD_TIMEOUT_MAX	6553	/* in sec */

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा menf21bmc_wdt अणु
	काष्ठा watchकरोg_device wdt;
	काष्ठा i2c_client *i2c_client;
पूर्ण;

अटल पूर्णांक menf21bmc_wdt_set_bootstatus(काष्ठा menf21bmc_wdt *data)
अणु
	पूर्णांक rst_rsn;

	rst_rsn = i2c_smbus_पढ़ो_byte_data(data->i2c_client, BMC_CMD_RST_RSN);
	अगर (rst_rsn < 0)
		वापस rst_rsn;

	अगर (rst_rsn == 0x02)
		data->wdt.bootstatus |= WDIOF_CARDRESET;
	अन्यथा अगर (rst_rsn == 0x05)
		data->wdt.bootstatus |= WDIOF_EXTERN1;
	अन्यथा अगर (rst_rsn == 0x06)
		data->wdt.bootstatus |= WDIOF_EXTERN2;
	अन्यथा अगर (rst_rsn == 0x0A)
		data->wdt.bootstatus |= WDIOF_POWERUNDER;

	वापस 0;
पूर्ण

अटल पूर्णांक menf21bmc_wdt_start(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा menf21bmc_wdt *drv_data = watchकरोg_get_drvdata(wdt);

	वापस i2c_smbus_ग_लिखो_byte(drv_data->i2c_client, BMC_CMD_WD_ON);
पूर्ण

अटल पूर्णांक menf21bmc_wdt_stop(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा menf21bmc_wdt *drv_data = watchकरोg_get_drvdata(wdt);

	वापस i2c_smbus_ग_लिखो_byte_data(drv_data->i2c_client,
					 BMC_CMD_WD_OFF, BMC_WD_OFF_VAL);
पूर्ण

अटल पूर्णांक
menf21bmc_wdt_समय_रखोout(काष्ठा watchकरोg_device *wdt, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक ret;
	काष्ठा menf21bmc_wdt *drv_data = watchकरोg_get_drvdata(wdt);

	/*
	 *  BMC Watchकरोg करोes have a resolution of 100ms.
	 *  Watchकरोg API defines the समयout in seconds, so we have to
	 *  multiply the value.
	 */
	ret = i2c_smbus_ग_लिखो_word_data(drv_data->i2c_client,
					BMC_CMD_WD_TIME, समयout * 10);
	अगर (ret < 0)
		वापस ret;

	wdt->समयout = समयout;

	वापस 0;
पूर्ण

अटल पूर्णांक menf21bmc_wdt_ping(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा menf21bmc_wdt *drv_data = watchकरोg_get_drvdata(wdt);

	वापस i2c_smbus_ग_लिखो_byte(drv_data->i2c_client, BMC_CMD_WD_TRIG);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info menf21bmc_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity = DEVNAME,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops menf21bmc_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= menf21bmc_wdt_start,
	.stop		= menf21bmc_wdt_stop,
	.ping		= menf21bmc_wdt_ping,
	.set_समयout	= menf21bmc_wdt_समय_रखोout,
पूर्ण;

अटल पूर्णांक menf21bmc_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, bmc_समयout;
	काष्ठा menf21bmc_wdt *drv_data;
	काष्ठा i2c_client *i2c_client = to_i2c_client(dev->parent);

	drv_data = devm_kzalloc(dev, माप(काष्ठा menf21bmc_wdt), GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	drv_data->wdt.ops = &menf21bmc_wdt_ops;
	drv_data->wdt.info = &menf21bmc_wdt_info;
	drv_data->wdt.min_समयout = BMC_WD_TIMEOUT_MIN;
	drv_data->wdt.max_समयout = BMC_WD_TIMEOUT_MAX;
	drv_data->wdt.parent = dev;
	drv_data->i2c_client = i2c_client;

	/*
	 * Get the current wdt समयout value from the BMC because
	 * the BMC will save the value set beक्रमe अगर the प्रणाली restarts.
	 */
	bmc_समयout = i2c_smbus_पढ़ो_word_data(drv_data->i2c_client,
					       BMC_CMD_WD_TIME);
	अगर (bmc_समयout < 0) अणु
		dev_err(dev, "failed to get current WDT timeout\n");
		वापस bmc_समयout;
	पूर्ण

	watchकरोg_init_समयout(&drv_data->wdt, bmc_समयout / 10, dev);
	watchकरोg_set_nowayout(&drv_data->wdt, nowayout);
	watchकरोg_set_drvdata(&drv_data->wdt, drv_data);
	platक्रमm_set_drvdata(pdev, drv_data);

	ret = menf21bmc_wdt_set_bootstatus(drv_data);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set Watchdog bootstatus\n");
		वापस ret;
	पूर्ण

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &drv_data->wdt);
	अगर (ret)
		वापस ret;

	dev_info(dev, "MEN 14F021P00 BMC Watchdog device enabled\n");

	वापस 0;
पूर्ण

अटल व्योम menf21bmc_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा menf21bmc_wdt *drv_data = platक्रमm_get_drvdata(pdev);

	i2c_smbus_ग_लिखो_word_data(drv_data->i2c_client,
				  BMC_CMD_WD_OFF, BMC_WD_OFF_VAL);
पूर्ण

अटल काष्ठा  platक्रमm_driver menf21bmc_wdt = अणु
	.driver		= अणु
		.name	= DEVNAME,
	पूर्ण,
	.probe		= menf21bmc_wdt_probe,
	.shutकरोwn	= menf21bmc_wdt_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(menf21bmc_wdt);

MODULE_DESCRIPTION("MEN 14F021P00 BMC Watchdog driver");
MODULE_AUTHOR("Andreas Werner <andreas.werner@men.de>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:menf21bmc_wdt");
