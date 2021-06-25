<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Mellanox watchकरोg driver
 *
 * Copyright (C) 2019 Mellanox Technologies
 * Copyright (C) 2019 Michael Shych <mshych@mellanox.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/mlxreg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

#घोषणा MLXREG_WDT_CLOCK_SCALE		1000
#घोषणा MLXREG_WDT_MAX_TIMEOUT_TYPE1	32
#घोषणा MLXREG_WDT_MAX_TIMEOUT_TYPE2	255
#घोषणा MLXREG_WDT_MAX_TIMEOUT_TYPE3	65535
#घोषणा MLXREG_WDT_MIN_TIMEOUT		1
#घोषणा MLXREG_WDT_OPTIONS_BASE (WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE | \
				 WDIOF_SETTIMEOUT)

/**
 * काष्ठा mlxreg_wdt - wd निजी data:
 *
 * @wdd:	watchकरोg device;
 * @device:	basic device;
 * @pdata:	data received from platक्रमm driver;
 * @regmap:	रेजिस्टर map of parent device;
 * @समयout:	defined समयout in sec.;
 * @action_idx:	index क्रम direct access to action रेजिस्टर;
 * @समयout_idx:index क्रम direct access to TO रेजिस्टर;
 * @tleft_idx:	index क्रम direct access to समय left रेजिस्टर;
 * @ping_idx:	index क्रम direct access to ping रेजिस्टर;
 * @reset_idx:	index क्रम direct access to reset cause रेजिस्टर;
 * @wd_type:	watchकरोg HW type;
 */
काष्ठा mlxreg_wdt अणु
	काष्ठा watchकरोg_device wdd;
	काष्ठा mlxreg_core_platक्रमm_data *pdata;
	व्योम *regmap;
	पूर्णांक action_idx;
	पूर्णांक समयout_idx;
	पूर्णांक tleft_idx;
	पूर्णांक ping_idx;
	पूर्णांक reset_idx;
	पूर्णांक regmap_val_sz;
	क्रमागत mlxreg_wdt_type wdt_type;
पूर्ण;

अटल व्योम mlxreg_wdt_check_card_reset(काष्ठा mlxreg_wdt *wdt)
अणु
	काष्ठा mlxreg_core_data *reg_data;
	u32 regval;
	पूर्णांक rc;

	अगर (wdt->reset_idx == -EINVAL)
		वापस;

	अगर (!(wdt->wdd.info->options & WDIOF_CARDRESET))
		वापस;

	reg_data = &wdt->pdata->data[wdt->reset_idx];
	rc = regmap_पढ़ो(wdt->regmap, reg_data->reg, &regval);
	अगर (!rc) अणु
		अगर (regval & ~reg_data->mask) अणु
			wdt->wdd.bootstatus = WDIOF_CARDRESET;
			dev_info(wdt->wdd.parent,
				 "watchdog previously reset the CPU\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mlxreg_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा mlxreg_wdt *wdt = watchकरोg_get_drvdata(wdd);
	काष्ठा mlxreg_core_data *reg_data = &wdt->pdata->data[wdt->action_idx];

	वापस regmap_update_bits(wdt->regmap, reg_data->reg, ~reg_data->mask,
				  BIT(reg_data->bit));
पूर्ण

अटल पूर्णांक mlxreg_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा mlxreg_wdt *wdt = watchकरोg_get_drvdata(wdd);
	काष्ठा mlxreg_core_data *reg_data = &wdt->pdata->data[wdt->action_idx];

	वापस regmap_update_bits(wdt->regmap, reg_data->reg, ~reg_data->mask,
				  ~BIT(reg_data->bit));
पूर्ण

अटल पूर्णांक mlxreg_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा mlxreg_wdt *wdt = watchकरोg_get_drvdata(wdd);
	काष्ठा mlxreg_core_data *reg_data = &wdt->pdata->data[wdt->ping_idx];

	वापस regmap_update_bits_base(wdt->regmap, reg_data->reg,
				       ~reg_data->mask, BIT(reg_data->bit),
				       शून्य, false, true);
पूर्ण

अटल पूर्णांक mlxreg_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा mlxreg_wdt *wdt = watchकरोg_get_drvdata(wdd);
	काष्ठा mlxreg_core_data *reg_data = &wdt->pdata->data[wdt->समयout_idx];
	u32 regval, set_समय, hw_समयout;
	पूर्णांक rc;

	चयन (wdt->wdt_type) अणु
	हाल MLX_WDT_TYPE1:
		rc = regmap_पढ़ो(wdt->regmap, reg_data->reg, &regval);
		अगर (rc)
			वापस rc;

		hw_समयout = order_base_2(समयout * MLXREG_WDT_CLOCK_SCALE);
		regval = (regval & reg_data->mask) | hw_समयout;
		/* Rownकरोwn to actual बंदst number of sec. */
		set_समय = BIT(hw_समयout) / MLXREG_WDT_CLOCK_SCALE;
		rc = regmap_ग_लिखो(wdt->regmap, reg_data->reg, regval);
		अवरोध;
	हाल MLX_WDT_TYPE2:
		set_समय = समयout;
		rc = regmap_ग_लिखो(wdt->regmap, reg_data->reg, समयout);
		अवरोध;
	हाल MLX_WDT_TYPE3:
		/* WD_TYPE3 has 2B set समय रेजिस्टर */
		set_समय = समयout;
		अगर (wdt->regmap_val_sz == 1) अणु
			regval = समयout & 0xff;
			rc = regmap_ग_लिखो(wdt->regmap, reg_data->reg, regval);
			अगर (!rc) अणु
				regval = (समयout & 0xff00) >> 8;
				rc = regmap_ग_लिखो(wdt->regmap,
						reg_data->reg + 1, regval);
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = regmap_ग_लिखो(wdt->regmap, reg_data->reg, समयout);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	wdd->समयout = set_समय;
	अगर (!rc) अणु
		/*
		 * Restart watchकरोg with new समयout period
		 * अगर watchकरोg is alपढ़ोy started.
		 */
		अगर (watchकरोg_active(wdd)) अणु
			rc = mlxreg_wdt_stop(wdd);
			अगर (!rc)
				rc = mlxreg_wdt_start(wdd);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल अचिन्हित पूर्णांक mlxreg_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा mlxreg_wdt *wdt = watchकरोg_get_drvdata(wdd);
	काष्ठा mlxreg_core_data *reg_data = &wdt->pdata->data[wdt->tleft_idx];
	u32 regval, msb, lsb;
	पूर्णांक rc;

	अगर (wdt->wdt_type == MLX_WDT_TYPE2) अणु
		rc = regmap_पढ़ो(wdt->regmap, reg_data->reg, &regval);
	पूर्ण अन्यथा अणु
		/* WD_TYPE3 has 2 byte समयleft रेजिस्टर */
		अगर (wdt->regmap_val_sz == 1) अणु
			rc = regmap_पढ़ो(wdt->regmap, reg_data->reg, &lsb);
			अगर (!rc) अणु
				rc = regmap_पढ़ो(wdt->regmap,
						reg_data->reg + 1, &msb);
				regval = (msb & 0xff) << 8 | (lsb & 0xff);
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = regmap_पढ़ो(wdt->regmap, reg_data->reg, &regval);
		पूर्ण
	पूर्ण

	/* Return 0 समयleft in हाल of failure रेजिस्टर पढ़ो. */
	वापस rc == 0 ? regval : 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops mlxreg_wdt_ops_type1 = अणु
	.start		= mlxreg_wdt_start,
	.stop		= mlxreg_wdt_stop,
	.ping		= mlxreg_wdt_ping,
	.set_समयout	= mlxreg_wdt_set_समयout,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops mlxreg_wdt_ops_type2 = अणु
	.start		= mlxreg_wdt_start,
	.stop		= mlxreg_wdt_stop,
	.ping		= mlxreg_wdt_ping,
	.set_समयout	= mlxreg_wdt_set_समयout,
	.get_समयleft	= mlxreg_wdt_get_समयleft,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info mlxreg_wdt_मुख्य_info = अणु
	.options	= MLXREG_WDT_OPTIONS_BASE
			| WDIOF_CARDRESET,
	.identity	= "mlx-wdt-main",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info mlxreg_wdt_aux_info = अणु
	.options	= MLXREG_WDT_OPTIONS_BASE
			| WDIOF_ALARMONLY,
	.identity	= "mlx-wdt-aux",
पूर्ण;

अटल व्योम mlxreg_wdt_config(काष्ठा mlxreg_wdt *wdt,
			      काष्ठा mlxreg_core_platक्रमm_data *pdata)
अणु
	काष्ठा mlxreg_core_data *data = pdata->data;
	पूर्णांक i;

	wdt->reset_idx = -EINVAL;
	क्रम (i = 0; i < pdata->counter; i++, data++) अणु
		अगर (strnstr(data->label, "action", माप(data->label)))
			wdt->action_idx = i;
		अन्यथा अगर (strnstr(data->label, "timeout", माप(data->label)))
			wdt->समयout_idx = i;
		अन्यथा अगर (strnstr(data->label, "timeleft", माप(data->label)))
			wdt->tleft_idx = i;
		अन्यथा अगर (strnstr(data->label, "ping", माप(data->label)))
			wdt->ping_idx = i;
		अन्यथा अगर (strnstr(data->label, "reset", माप(data->label)))
			wdt->reset_idx = i;
	पूर्ण

	wdt->pdata = pdata;
	अगर (strnstr(pdata->identity, mlxreg_wdt_मुख्य_info.identity,
		    माप(mlxreg_wdt_मुख्य_info.identity)))
		wdt->wdd.info = &mlxreg_wdt_मुख्य_info;
	अन्यथा
		wdt->wdd.info = &mlxreg_wdt_aux_info;

	wdt->wdt_type = pdata->version;
	चयन (wdt->wdt_type) अणु
	हाल MLX_WDT_TYPE1:
		wdt->wdd.ops = &mlxreg_wdt_ops_type1;
		wdt->wdd.max_समयout = MLXREG_WDT_MAX_TIMEOUT_TYPE1;
		अवरोध;
	हाल MLX_WDT_TYPE2:
		wdt->wdd.ops = &mlxreg_wdt_ops_type2;
		wdt->wdd.max_समयout = MLXREG_WDT_MAX_TIMEOUT_TYPE2;
		अवरोध;
	हाल MLX_WDT_TYPE3:
		wdt->wdd.ops = &mlxreg_wdt_ops_type2;
		wdt->wdd.max_समयout = MLXREG_WDT_MAX_TIMEOUT_TYPE3;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	wdt->wdd.min_समयout = MLXREG_WDT_MIN_TIMEOUT;
पूर्ण

अटल पूर्णांक mlxreg_wdt_init_समयout(काष्ठा mlxreg_wdt *wdt,
				   काष्ठा mlxreg_core_platक्रमm_data *pdata)
अणु
	u32 समयout;

	समयout = pdata->data[wdt->समयout_idx].health_cntr;
	वापस mlxreg_wdt_set_समयout(&wdt->wdd, समयout);
पूर्ण

अटल पूर्णांक mlxreg_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mlxreg_core_platक्रमm_data *pdata;
	काष्ठा mlxreg_wdt *wdt;
	पूर्णांक rc;

	pdata = dev_get_platdata(dev);
	अगर (!pdata) अणु
		dev_err(dev, "Failed to get platform data.\n");
		वापस -EINVAL;
	पूर्ण
	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->wdd.parent = dev;
	wdt->regmap = pdata->regmap;
	rc = regmap_get_val_bytes(wdt->regmap);
	अगर (rc < 0)
		वापस -EINVAL;

	wdt->regmap_val_sz = rc;
	mlxreg_wdt_config(wdt, pdata);

	अगर ((pdata->features & MLXREG_CORE_WD_FEATURE_NOWAYOUT))
		watchकरोg_set_nowayout(&wdt->wdd, WATCHDOG_NOWAYOUT);
	watchकरोg_stop_on_reboot(&wdt->wdd);
	watchकरोg_stop_on_unरेजिस्टर(&wdt->wdd);
	watchकरोg_set_drvdata(&wdt->wdd, wdt);
	rc = mlxreg_wdt_init_समयout(wdt, pdata);
	अगर (rc)
		जाओ रेजिस्टर_error;

	अगर ((pdata->features & MLXREG_CORE_WD_FEATURE_START_AT_BOOT)) अणु
		rc = mlxreg_wdt_start(&wdt->wdd);
		अगर (rc)
			जाओ रेजिस्टर_error;
		set_bit(WDOG_HW_RUNNING, &wdt->wdd.status);
	पूर्ण
	mlxreg_wdt_check_card_reset(wdt);
	rc = devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdd);

रेजिस्टर_error:
	अगर (rc)
		dev_err(dev, "Cannot register watchdog device (err=%d)\n", rc);
	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver mlxreg_wdt_driver = अणु
	.probe	= mlxreg_wdt_probe,
	.driver	= अणु
			.name = "mlx-wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mlxreg_wdt_driver);

MODULE_AUTHOR("Michael Shych <michaelsh@mellanox.com>");
MODULE_DESCRIPTION("Mellanox watchdog driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mlx-wdt");
