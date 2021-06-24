<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8994-core.c  --  Device access क्रम Wolfson WM8994
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/machine.h>

#समावेश <linux/mfd/wm8994/core.h>
#समावेश <linux/mfd/wm8994/pdata.h>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>

#समावेश "wm8994.h"

अटल स्थिर काष्ठा mfd_cell wm8994_regulator_devs[] = अणु
	अणु
		.name = "wm8994-ldo",
		.id = 0,
		.pm_runसमय_no_callbacks = true,
	पूर्ण,
	अणु
		.name = "wm8994-ldo",
		.id = 1,
		.pm_runसमय_no_callbacks = true,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm8994_codec_resources[] = अणु
	अणु
		.start = WM8994_IRQ_TEMP_SHUT,
		.end   = WM8994_IRQ_TEMP_WARN,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm8994_gpio_resources[] = अणु
	अणु
		.start = WM8994_IRQ_GPIO(1),
		.end   = WM8994_IRQ_GPIO(11),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell wm8994_devs[] = अणु
	अणु
		.name = "wm8994-codec",
		.num_resources = ARRAY_SIZE(wm8994_codec_resources),
		.resources = wm8994_codec_resources,
	पूर्ण,

	अणु
		.name = "wm8994-gpio",
		.num_resources = ARRAY_SIZE(wm8994_gpio_resources),
		.resources = wm8994_gpio_resources,
		.pm_runसमय_no_callbacks = true,
	पूर्ण,
पूर्ण;

/*
 * Supplies क्रम the मुख्य bulk of CODEC; the LDO supplies are ignored
 * and should be handled via the standard regulator API supply
 * management.
 */
अटल स्थिर अक्षर *wm1811_मुख्य_supplies[] = अणु
	"DBVDD1",
	"DBVDD2",
	"DBVDD3",
	"DCVDD",
	"AVDD1",
	"AVDD2",
	"CPVDD",
	"SPKVDD1",
	"SPKVDD2",
पूर्ण;

अटल स्थिर अक्षर *wm8994_मुख्य_supplies[] = अणु
	"DBVDD",
	"DCVDD",
	"AVDD1",
	"AVDD2",
	"CPVDD",
	"SPKVDD1",
	"SPKVDD2",
पूर्ण;

अटल स्थिर अक्षर *wm8958_मुख्य_supplies[] = अणु
	"DBVDD1",
	"DBVDD2",
	"DBVDD3",
	"DCVDD",
	"AVDD1",
	"AVDD2",
	"CPVDD",
	"SPKVDD1",
	"SPKVDD2",
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wm8994_suspend(काष्ठा device *dev)
अणु
	काष्ठा wm8994 *wm8994 = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Don't actually go through with the suspend अगर the CODEC is
	 * still active क्रम accessory detect. */
	चयन (wm8994->type) अणु
	हाल WM8958:
	हाल WM1811:
		ret = wm8994_reg_पढ़ो(wm8994, WM8958_MIC_DETECT_1);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to read power status: %d\n", ret);
		पूर्ण अन्यथा अगर (ret & WM8958_MICD_ENA) अणु
			dev_dbg(dev, "CODEC still active, ignoring suspend\n");
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Disable LDO pullकरोwns जबतक the device is suspended अगर we
	 * करोn't know that something will be driving them. */
	अगर (!wm8994->lकरो_ena_always_driven)
		wm8994_set_bits(wm8994, WM8994_PULL_CONTROL_2,
				WM8994_LDO1ENA_PD | WM8994_LDO2ENA_PD,
				WM8994_LDO1ENA_PD | WM8994_LDO2ENA_PD);

	/* Explicitly put the device पूर्णांकo reset in हाल regulators
	 * करोn't get disabled in order to ensure consistent restart.
	 */
	wm8994_reg_ग_लिखो(wm8994, WM8994_SOFTWARE_RESET,
			 wm8994_reg_पढ़ो(wm8994, WM8994_SOFTWARE_RESET));

	regcache_mark_dirty(wm8994->regmap);

	/* Restore GPIO रेजिस्टरs to prevent problems with mismatched
	 * pin configurations.
	 */
	ret = regcache_sync_region(wm8994->regmap, WM8994_GPIO_1,
				   WM8994_GPIO_11);
	अगर (ret != 0)
		dev_err(dev, "Failed to restore GPIO registers: %d\n", ret);

	/* In हाल one of the GPIOs is used as a wake input. */
	ret = regcache_sync_region(wm8994->regmap,
				   WM8994_INTERRUPT_STATUS_1_MASK,
				   WM8994_INTERRUPT_STATUS_1_MASK);
	अगर (ret != 0)
		dev_err(dev, "Failed to restore interrupt mask: %d\n", ret);

	regcache_cache_only(wm8994->regmap, true);
	wm8994->suspended = true;

	ret = regulator_bulk_disable(wm8994->num_supplies,
				     wm8994->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to disable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_resume(काष्ठा device *dev)
अणु
	काष्ठा wm8994 *wm8994 = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* We may have lied to the PM core about suspending */
	अगर (!wm8994->suspended)
		वापस 0;

	ret = regulator_bulk_enable(wm8994->num_supplies,
				    wm8994->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(wm8994->regmap, false);
	ret = regcache_sync(wm8994->regmap);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to restore register map: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	/* Disable LDO pullकरोwns जबतक the device is active */
	wm8994_set_bits(wm8994, WM8994_PULL_CONTROL_2,
			WM8994_LDO1ENA_PD | WM8994_LDO2ENA_PD,
			0);

	wm8994->suspended = false;

	वापस 0;

err_enable:
	regulator_bulk_disable(wm8994->num_supplies, wm8994->supplies);

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_REGULATOR
अटल पूर्णांक wm8994_lकरो_in_use(काष्ठा wm8994_pdata *pdata, पूर्णांक lकरो)
अणु
	काष्ठा wm8994_lकरो_pdata *lकरो_pdata;

	अगर (!pdata)
		वापस 0;

	lकरो_pdata = &pdata->lकरो[lकरो];

	अगर (!lकरो_pdata->init_data)
		वापस 0;

	वापस lकरो_pdata->init_data->num_consumer_supplies != 0;
पूर्ण
#अन्यथा
अटल पूर्णांक wm8994_lकरो_in_use(काष्ठा wm8994_pdata *pdata, पूर्णांक lकरो)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा reg_sequence wm8994_revc_patch[] = अणु
	अणु 0x102, 0x3 पूर्ण,
	अणु 0x56, 0x3 पूर्ण,
	अणु 0x817, 0x0 पूर्ण,
	अणु 0x102, 0x0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence wm8958_reva_patch[] = अणु
	अणु 0x102, 0x3 पूर्ण,
	अणु 0xcb, 0x81 पूर्ण,
	अणु 0x817, 0x0 पूर्ण,
	अणु 0x102, 0x0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence wm1811_reva_patch[] = अणु
	अणु 0x102, 0x3 पूर्ण,
	अणु 0x56, 0xc07 पूर्ण,
	अणु 0x5d, 0x7e पूर्ण,
	अणु 0x5e, 0x0 पूर्ण,
	अणु 0x102, 0x0 पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल पूर्णांक wm8994_set_pdata_from_of(काष्ठा wm8994 *wm8994)
अणु
	काष्ठा device_node *np = wm8994->dev->of_node;
	काष्ठा wm8994_pdata *pdata = &wm8994->pdata;
	पूर्णांक i;

	अगर (!np)
		वापस 0;

	अगर (of_property_पढ़ो_u32_array(np, "wlf,gpio-cfg", pdata->gpio_शेषs,
				       ARRAY_SIZE(pdata->gpio_शेषs)) >= 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(pdata->gpio_शेषs); i++) अणु
			अगर (wm8994->pdata.gpio_शेषs[i] == 0)
				pdata->gpio_शेषs[i]
					= WM8994_CONFIGURE_GPIO;
		पूर्ण
	पूर्ण

	of_property_पढ़ो_u32_array(np, "wlf,micbias-cfg", pdata->micbias,
				   ARRAY_SIZE(pdata->micbias));

	pdata->lineout1_dअगरf = true;
	pdata->lineout2_dअगरf = true;
	अगर (of_find_property(np, "wlf,lineout1-se", शून्य))
		pdata->lineout1_dअगरf = false;
	अगर (of_find_property(np, "wlf,lineout2-se", शून्य))
		pdata->lineout2_dअगरf = false;

	अगर (of_find_property(np, "wlf,lineout1-feedback", शून्य))
		pdata->lineout1fb = true;
	अगर (of_find_property(np, "wlf,lineout2-feedback", शून्य))
		pdata->lineout2fb = true;

	अगर (of_find_property(np, "wlf,ldoena-always-driven", शून्य))
		pdata->lineout2fb = true;

	pdata->spkmode_pu = of_property_पढ़ो_bool(np, "wlf,spkmode-pu");

	pdata->csnaddr_pd = of_property_पढ़ो_bool(np, "wlf,csnaddr-pd");

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक wm8994_set_pdata_from_of(काष्ठा wm8994 *wm8994)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Instantiate the generic non-control parts of the device.
 */
अटल पूर्णांक wm8994_device_init(काष्ठा wm8994 *wm8994, पूर्णांक irq)
अणु
	काष्ठा wm8994_pdata *pdata;
	काष्ठा regmap_config *regmap_config;
	स्थिर काष्ठा reg_sequence *regmap_patch = शून्य;
	स्थिर अक्षर *devname;
	पूर्णांक ret, i, patch_regs = 0;
	पूर्णांक pulls = 0;

	अगर (dev_get_platdata(wm8994->dev)) अणु
		pdata = dev_get_platdata(wm8994->dev);
		wm8994->pdata = *pdata;
	पूर्ण
	pdata = &wm8994->pdata;

	ret = wm8994_set_pdata_from_of(wm8994);
	अगर (ret != 0)
		वापस ret;

	dev_set_drvdata(wm8994->dev, wm8994);

	/* Add the on-chip regulators first क्रम bootstrapping */
	ret = mfd_add_devices(wm8994->dev, 0,
			      wm8994_regulator_devs,
			      ARRAY_SIZE(wm8994_regulator_devs),
			      शून्य, 0, शून्य);
	अगर (ret != 0) अणु
		dev_err(wm8994->dev, "Failed to add children: %d\n", ret);
		जाओ err;
	पूर्ण

	चयन (wm8994->type) अणु
	हाल WM1811:
		wm8994->num_supplies = ARRAY_SIZE(wm1811_मुख्य_supplies);
		अवरोध;
	हाल WM8994:
		wm8994->num_supplies = ARRAY_SIZE(wm8994_मुख्य_supplies);
		अवरोध;
	हाल WM8958:
		wm8994->num_supplies = ARRAY_SIZE(wm8958_मुख्य_supplies);
		अवरोध;
	शेष:
		BUG();
		जाओ err;
	पूर्ण

	wm8994->supplies = devm_kसुस्मृति(wm8994->dev,
					wm8994->num_supplies,
					माप(काष्ठा regulator_bulk_data),
					GFP_KERNEL);
	अगर (!wm8994->supplies) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	चयन (wm8994->type) अणु
	हाल WM1811:
		क्रम (i = 0; i < ARRAY_SIZE(wm1811_मुख्य_supplies); i++)
			wm8994->supplies[i].supply = wm1811_मुख्य_supplies[i];
		अवरोध;
	हाल WM8994:
		क्रम (i = 0; i < ARRAY_SIZE(wm8994_मुख्य_supplies); i++)
			wm8994->supplies[i].supply = wm8994_मुख्य_supplies[i];
		अवरोध;
	हाल WM8958:
		क्रम (i = 0; i < ARRAY_SIZE(wm8958_मुख्य_supplies); i++)
			wm8994->supplies[i].supply = wm8958_मुख्य_supplies[i];
		अवरोध;
	शेष:
		BUG();
		जाओ err;
	पूर्ण

	/*
	 * Can't use devres helper here as some of the supplies are provided by
	 * wm8994->dev's children (regulators) and those regulators are
	 * unरेजिस्टरed by the devres core beक्रमe the supplies are मुक्तd.
	 */
	ret = regulator_bulk_get(wm8994->dev, wm8994->num_supplies,
				 wm8994->supplies);
	अगर (ret != 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(wm8994->dev, "Failed to get supplies: %d\n",
				ret);
		जाओ err;
	पूर्ण

	ret = regulator_bulk_enable(wm8994->num_supplies, wm8994->supplies);
	अगर (ret != 0) अणु
		dev_err(wm8994->dev, "Failed to enable supplies: %d\n", ret);
		जाओ err_regulator_मुक्त;
	पूर्ण

	ret = wm8994_reg_पढ़ो(wm8994, WM8994_SOFTWARE_RESET);
	अगर (ret < 0) अणु
		dev_err(wm8994->dev, "Failed to read ID register\n");
		जाओ err_enable;
	पूर्ण
	चयन (ret) अणु
	हाल 0x1811:
		devname = "WM1811";
		अगर (wm8994->type != WM1811)
			dev_warn(wm8994->dev, "Device registered as type %d\n",
				 wm8994->type);
		wm8994->type = WM1811;
		अवरोध;
	हाल 0x8994:
		devname = "WM8994";
		अगर (wm8994->type != WM8994)
			dev_warn(wm8994->dev, "Device registered as type %d\n",
				 wm8994->type);
		wm8994->type = WM8994;
		अवरोध;
	हाल 0x8958:
		devname = "WM8958";
		अगर (wm8994->type != WM8958)
			dev_warn(wm8994->dev, "Device registered as type %d\n",
				 wm8994->type);
		wm8994->type = WM8958;
		अवरोध;
	शेष:
		dev_err(wm8994->dev, "Device is not a WM8994, ID is %x\n",
			ret);
		ret = -EINVAL;
		जाओ err_enable;
	पूर्ण

	ret = wm8994_reg_पढ़ो(wm8994, WM8994_CHIP_REVISION);
	अगर (ret < 0) अणु
		dev_err(wm8994->dev, "Failed to read revision register: %d\n",
			ret);
		जाओ err_enable;
	पूर्ण
	wm8994->revision = ret & WM8994_CHIP_REV_MASK;
	wm8994->cust_id = (ret & WM8994_CUST_ID_MASK) >> WM8994_CUST_ID_SHIFT;

	चयन (wm8994->type) अणु
	हाल WM8994:
		चयन (wm8994->revision) अणु
		हाल 0:
		हाल 1:
			dev_warn(wm8994->dev,
				 "revision %c not fully supported\n",
				 'A' + wm8994->revision);
			अवरोध;
		हाल 2:
		हाल 3:
		शेष:
			regmap_patch = wm8994_revc_patch;
			patch_regs = ARRAY_SIZE(wm8994_revc_patch);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल WM8958:
		चयन (wm8994->revision) अणु
		हाल 0:
			regmap_patch = wm8958_reva_patch;
			patch_regs = ARRAY_SIZE(wm8958_reva_patch);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल WM1811:
		/* Revision C did not change the relevant layer */
		अगर (wm8994->revision > 1)
			wm8994->revision++;

		regmap_patch = wm1811_reva_patch;
		patch_regs = ARRAY_SIZE(wm1811_reva_patch);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	dev_info(wm8994->dev, "%s revision %c CUST_ID %02x\n", devname,
		 'A' + wm8994->revision, wm8994->cust_id);

	चयन (wm8994->type) अणु
	हाल WM1811:
		regmap_config = &wm1811_regmap_config;
		अवरोध;
	हाल WM8994:
		regmap_config = &wm8994_regmap_config;
		अवरोध;
	हाल WM8958:
		regmap_config = &wm8958_regmap_config;
		अवरोध;
	शेष:
		dev_err(wm8994->dev, "Unknown device type %d\n", wm8994->type);
		ret = -EINVAL;
		जाओ err_enable;
	पूर्ण

	ret = regmap_reinit_cache(wm8994->regmap, regmap_config);
	अगर (ret != 0) अणु
		dev_err(wm8994->dev, "Failed to reinit register cache: %d\n",
			ret);
		जाओ err_enable;
	पूर्ण

	/* Explicitly put the device पूर्णांकo reset in हाल regulators
	 * करोn't get disabled in order to ensure we know the device
	 * state.
	 */
	ret = wm8994_reg_ग_लिखो(wm8994, WM8994_SOFTWARE_RESET,
			       wm8994_reg_पढ़ो(wm8994, WM8994_SOFTWARE_RESET));
	अगर (ret != 0) अणु
		dev_err(wm8994->dev, "Failed to reset device: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	अगर (regmap_patch) अणु
		ret = regmap_रेजिस्टर_patch(wm8994->regmap, regmap_patch,
					    patch_regs);
		अगर (ret != 0) अणु
			dev_err(wm8994->dev, "Failed to register patch: %d\n",
				ret);
			जाओ err_enable;
		पूर्ण
	पूर्ण

	wm8994->irq_base = pdata->irq_base;
	wm8994->gpio_base = pdata->gpio_base;

	/* GPIO configuration is only applied अगर it's non-zero */
	क्रम (i = 0; i < ARRAY_SIZE(pdata->gpio_शेषs); i++) अणु
		अगर (pdata->gpio_शेषs[i]) अणु
			wm8994_set_bits(wm8994, WM8994_GPIO_1 + i,
					0xffff, pdata->gpio_शेषs[i]);
		पूर्ण
	पूर्ण

	wm8994->lकरो_ena_always_driven = pdata->lकरो_ena_always_driven;

	अगर (pdata->spkmode_pu)
		pulls |= WM8994_SPKMODE_PU;
	अगर (pdata->csnaddr_pd)
		pulls |= WM8994_CSNADDR_PD;

	/* Disable unneeded pulls */
	wm8994_set_bits(wm8994, WM8994_PULL_CONTROL_2,
			WM8994_LDO1ENA_PD | WM8994_LDO2ENA_PD |
			WM8994_SPKMODE_PU | WM8994_CSNADDR_PD,
			pulls);

	/* In some प्रणाली designs where the regulators are not in use,
	 * we can achieve a small reduction in leakage currents by
	 * भग्नing LDO outमाला_दो.  This bit makes no dअगरference अगर the
	 * LDOs are enabled, it only affects हालs where the LDOs were
	 * in operation and are then disabled.
	 */
	क्रम (i = 0; i < WM8994_NUM_LDO_REGS; i++) अणु
		अगर (wm8994_lकरो_in_use(pdata, i))
			wm8994_set_bits(wm8994, WM8994_LDO_1 + i,
					WM8994_LDO1_DISCH, WM8994_LDO1_DISCH);
		अन्यथा
			wm8994_set_bits(wm8994, WM8994_LDO_1 + i,
					WM8994_LDO1_DISCH, 0);
	पूर्ण

	wm8994_irq_init(wm8994);

	ret = mfd_add_devices(wm8994->dev, -1,
			      wm8994_devs, ARRAY_SIZE(wm8994_devs),
			      शून्य, 0, शून्य);
	अगर (ret != 0) अणु
		dev_err(wm8994->dev, "Failed to add children: %d\n", ret);
		जाओ err_irq;
	पूर्ण

	pm_runसमय_set_active(wm8994->dev);
	pm_runसमय_enable(wm8994->dev);
	pm_runसमय_idle(wm8994->dev);

	वापस 0;

err_irq:
	wm8994_irq_निकास(wm8994);
err_enable:
	regulator_bulk_disable(wm8994->num_supplies,
			       wm8994->supplies);
err_regulator_मुक्त:
	regulator_bulk_मुक्त(wm8994->num_supplies, wm8994->supplies);
err:
	mfd_हटाओ_devices(wm8994->dev);
	वापस ret;
पूर्ण

अटल व्योम wm8994_device_निकास(काष्ठा wm8994 *wm8994)
अणु
	pm_runसमय_get_sync(wm8994->dev);
	pm_runसमय_disable(wm8994->dev);
	pm_runसमय_put_noidle(wm8994->dev);
	wm8994_irq_निकास(wm8994);
	regulator_bulk_disable(wm8994->num_supplies, wm8994->supplies);
	regulator_bulk_मुक्त(wm8994->num_supplies, wm8994->supplies);
	mfd_हटाओ_devices(wm8994->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id wm8994_of_match[] = अणु
	अणु .compatible = "wlf,wm1811", .data = (व्योम *)WM1811 पूर्ण,
	अणु .compatible = "wlf,wm8994", .data = (व्योम *)WM8994 पूर्ण,
	अणु .compatible = "wlf,wm8958", .data = (व्योम *)WM8958 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8994_of_match);

अटल पूर्णांक wm8994_i2c_probe(काष्ठा i2c_client *i2c,
				      स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा wm8994 *wm8994;
	पूर्णांक ret;

	wm8994 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8994), GFP_KERNEL);
	अगर (wm8994 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, wm8994);
	wm8994->dev = &i2c->dev;
	wm8994->irq = i2c->irq;

	अगर (i2c->dev.of_node) अणु
		of_id = of_match_device(wm8994_of_match, &i2c->dev);
		अगर (of_id)
			wm8994->type = (क्रमागत wm8994_type)of_id->data;
	पूर्ण अन्यथा अणु
		wm8994->type = id->driver_data;
	पूर्ण

	wm8994->regmap = devm_regmap_init_i2c(i2c, &wm8994_base_regmap_config);
	अगर (IS_ERR(wm8994->regmap)) अणु
		ret = PTR_ERR(wm8994->regmap);
		dev_err(wm8994->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस wm8994_device_init(wm8994, i2c->irq);
पूर्ण

अटल पूर्णांक wm8994_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा wm8994 *wm8994 = i2c_get_clientdata(i2c);

	wm8994_device_निकास(wm8994);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8994_i2c_id[] = अणु
	अणु "wm1811", WM1811 पूर्ण,
	अणु "wm1811a", WM1811 पूर्ण,
	अणु "wm8994", WM8994 पूर्ण,
	अणु "wm8958", WM8958 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8994_i2c_id);

अटल स्थिर काष्ठा dev_pm_ops wm8994_pm_ops = अणु
	SET_RUNTIME_PM_OPS(wm8994_suspend, wm8994_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver wm8994_i2c_driver = अणु
	.driver = अणु
		.name = "wm8994",
		.pm = &wm8994_pm_ops,
		.of_match_table = wm8994_of_match,
	पूर्ण,
	.probe = wm8994_i2c_probe,
	.हटाओ = wm8994_i2c_हटाओ,
	.id_table = wm8994_i2c_id,
पूर्ण;

module_i2c_driver(wm8994_i2c_driver);

MODULE_DESCRIPTION("Core support for the WM8994 audio CODEC");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_SOFTDEP("pre: wm8994_regulator");
