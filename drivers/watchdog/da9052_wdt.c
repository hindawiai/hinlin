<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * System monitoring driver क्रम DA9052 PMICs.
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: Anthony Olech <Anthony.Olech@diasemi.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/समय.स>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>

#समावेश <linux/mfd/da9052/reg.h>
#समावेश <linux/mfd/da9052/da9052.h>

#घोषणा DA9052_DEF_TIMEOUT	4
#घोषणा DA9052_TWDMIN		256

काष्ठा da9052_wdt_data अणु
	काष्ठा watchकरोg_device wdt;
	काष्ठा da9052 *da9052;
	अचिन्हित दीर्घ jpast;
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8 reg_val;
	पूर्णांक समय;  /* Seconds */
पूर्ण da9052_wdt_maps[] = अणु
	अणु 1, 2 पूर्ण,
	अणु 2, 4 पूर्ण,
	अणु 3, 8 पूर्ण,
	अणु 4, 16 पूर्ण,
	अणु 5, 32 पूर्ण,
	अणु 5, 33 पूर्ण,  /* Actual समय  32.768s so included both 32s and 33s */
	अणु 6, 65 पूर्ण,
	अणु 6, 66 पूर्ण,  /* Actual समय 65.536s so include both, 65s and 66s */
	अणु 7, 131 पूर्ण,
पूर्ण;


अटल पूर्णांक da9052_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा da9052_wdt_data *driver_data = watchकरोg_get_drvdata(wdt_dev);
	काष्ठा da9052 *da9052 = driver_data->da9052;
	पूर्णांक ret, i;

	/*
	 * Disable the Watchकरोg समयr beक्रमe setting
	 * new समय out.
	 */
	ret = da9052_reg_update(da9052, DA9052_CONTROL_D_REG,
				DA9052_CONTROLD_TWDSCALE, 0);
	अगर (ret < 0) अणु
		dev_err(da9052->dev, "Failed to disable watchdog bit, %d\n",
			ret);
		वापस ret;
	पूर्ण
	अगर (समयout) अणु
		/*
		 * To change the समयout, da9052 needs to
		 * be disabled क्रम at least 150 us.
		 */
		udelay(150);

		/* Set the desired समयout */
		क्रम (i = 0; i < ARRAY_SIZE(da9052_wdt_maps); i++)
			अगर (da9052_wdt_maps[i].समय == समयout)
				अवरोध;

		अगर (i == ARRAY_SIZE(da9052_wdt_maps))
			ret = -EINVAL;
		अन्यथा
			ret = da9052_reg_update(da9052, DA9052_CONTROL_D_REG,
						DA9052_CONTROLD_TWDSCALE,
						da9052_wdt_maps[i].reg_val);
		अगर (ret < 0) अणु
			dev_err(da9052->dev,
				"Failed to update timescale bit, %d\n", ret);
			वापस ret;
		पूर्ण

		wdt_dev->समयout = समयout;
		driver_data->jpast = jअगरfies;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	वापस da9052_wdt_set_समयout(wdt_dev, wdt_dev->समयout);
पूर्ण

अटल पूर्णांक da9052_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	वापस da9052_wdt_set_समयout(wdt_dev, 0);
पूर्ण

अटल पूर्णांक da9052_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा da9052_wdt_data *driver_data = watchकरोg_get_drvdata(wdt_dev);
	काष्ठा da9052 *da9052 = driver_data->da9052;
	अचिन्हित दीर्घ msec, jnow = jअगरfies;
	पूर्णांक ret;

	/*
	 * We have a minimum समय क्रम watchकरोg winकरोw called TWDMIN. A ग_लिखो
	 * to the watchकरोg beक्रमe this elapsed समय should cause an error.
	 */
	msec = (jnow - driver_data->jpast) * 1000/HZ;
	अगर (msec < DA9052_TWDMIN)
		mdelay(msec);

	/* Reset the watchकरोg समयr */
	ret = da9052_reg_update(da9052, DA9052_CONTROL_D_REG,
				DA9052_CONTROLD_WATCHDOG, 1 << 7);
	अगर (ret < 0)
		वापस ret;

	/*
	 * FIXME: Reset the watchकरोg core, in general PMIC
	 * is supposed to करो this
	 */
	वापस da9052_reg_update(da9052, DA9052_CONTROL_D_REG,
				 DA9052_CONTROLD_WATCHDOG, 0 << 7);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info da9052_wdt_info = अणु
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity	= "DA9052 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops da9052_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = da9052_wdt_start,
	.stop = da9052_wdt_stop,
	.ping = da9052_wdt_ping,
	.set_समयout = da9052_wdt_set_समयout,
पूर्ण;


अटल पूर्णांक da9052_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9052 *da9052 = dev_get_drvdata(dev->parent);
	काष्ठा da9052_wdt_data *driver_data;
	काष्ठा watchकरोg_device *da9052_wdt;
	पूर्णांक ret;

	driver_data = devm_kzalloc(dev, माप(*driver_data), GFP_KERNEL);
	अगर (!driver_data)
		वापस -ENOMEM;
	driver_data->da9052 = da9052;

	da9052_wdt = &driver_data->wdt;

	da9052_wdt->समयout = DA9052_DEF_TIMEOUT;
	da9052_wdt->info = &da9052_wdt_info;
	da9052_wdt->ops = &da9052_wdt_ops;
	da9052_wdt->parent = dev;
	watchकरोg_set_drvdata(da9052_wdt, driver_data);

	ret = da9052_reg_update(da9052, DA9052_CONTROL_D_REG,
				DA9052_CONTROLD_TWDSCALE, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to disable watchdog bits, %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &driver_data->wdt);
पूर्ण

अटल काष्ठा platक्रमm_driver da9052_wdt_driver = अणु
	.probe = da9052_wdt_probe,
	.driver = अणु
		.name	= "da9052-watchdog",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9052_wdt_driver);

MODULE_AUTHOR("Anthony Olech <Anthony.Olech@diasemi.com>");
MODULE_DESCRIPTION("DA9052 SM Device Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9052-watchdog");
