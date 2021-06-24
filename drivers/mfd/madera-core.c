<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core MFD support क्रम Cirrus Logic Madera codecs
 *
 * Copyright (C) 2015-2018 Cirrus Logic
 */

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>

#समावेश <linux/mfd/madera/core.h>
#समावेश <linux/mfd/madera/रेजिस्टरs.h>

#समावेश "madera.h"

#घोषणा CS47L15_SILICON_ID	0x6370
#घोषणा CS47L35_SILICON_ID	0x6360
#घोषणा CS47L85_SILICON_ID	0x6338
#घोषणा CS47L90_SILICON_ID	0x6364
#घोषणा CS47L92_SILICON_ID	0x6371

#घोषणा MADERA_32KZ_MCLK2	1

#घोषणा MADERA_RESET_MIN_US	2000
#घोषणा MADERA_RESET_MAX_US	3000

#घोषणा ERRATA_DCVDD_MIN_US	10000
#घोषणा ERRATA_DCVDD_MAX_US	15000

अटल स्थिर अक्षर * स्थिर madera_core_supplies[] = अणु
	"AVDD",
	"DBVDD1",
पूर्ण;

अटल स्थिर काष्ठा mfd_cell madera_lकरो1_devs[] = अणु
	अणु
		.name = "madera-ldo1",
		.level = MFD_DEP_LEVEL_HIGH,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs47l15_supplies[] = अणु
	"MICVDD",
	"CPVDD1",
	"SPKVDD",
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cs47l15_devs[] = अणु
	अणु .name = "madera-pinctrl", पूर्ण,
	अणु .name = "madera-irq", पूर्ण,
	अणु .name = "madera-gpio", पूर्ण,
	अणु
		.name = "madera-extcon",
		.parent_supplies = cs47l15_supplies,
		.num_parent_supplies = 1, /* We only need MICVDD */
	पूर्ण,
	अणु
		.name = "cs47l15-codec",
		.parent_supplies = cs47l15_supplies,
		.num_parent_supplies = ARRAY_SIZE(cs47l15_supplies),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs47l35_supplies[] = अणु
	"MICVDD",
	"DBVDD2",
	"CPVDD1",
	"CPVDD2",
	"SPKVDD",
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cs47l35_devs[] = अणु
	अणु .name = "madera-pinctrl", पूर्ण,
	अणु .name = "madera-irq", पूर्ण,
	अणु .name = "madera-micsupp", पूर्ण,
	अणु .name = "madera-gpio", पूर्ण,
	अणु
		.name = "madera-extcon",
		.parent_supplies = cs47l35_supplies,
		.num_parent_supplies = 1, /* We only need MICVDD */
	पूर्ण,
	अणु
		.name = "cs47l35-codec",
		.parent_supplies = cs47l35_supplies,
		.num_parent_supplies = ARRAY_SIZE(cs47l35_supplies),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs47l85_supplies[] = अणु
	"MICVDD",
	"DBVDD2",
	"DBVDD3",
	"DBVDD4",
	"CPVDD1",
	"CPVDD2",
	"SPKVDDL",
	"SPKVDDR",
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cs47l85_devs[] = अणु
	अणु .name = "madera-pinctrl", पूर्ण,
	अणु .name = "madera-irq", पूर्ण,
	अणु .name = "madera-micsupp", पूर्ण,
	अणु .name = "madera-gpio", पूर्ण,
	अणु
		.name = "madera-extcon",
		.parent_supplies = cs47l85_supplies,
		.num_parent_supplies = 1, /* We only need MICVDD */
	पूर्ण,
	अणु
		.name = "cs47l85-codec",
		.parent_supplies = cs47l85_supplies,
		.num_parent_supplies = ARRAY_SIZE(cs47l85_supplies),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs47l90_supplies[] = अणु
	"MICVDD",
	"DBVDD2",
	"DBVDD3",
	"DBVDD4",
	"CPVDD1",
	"CPVDD2",
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cs47l90_devs[] = अणु
	अणु .name = "madera-pinctrl", पूर्ण,
	अणु .name = "madera-irq", पूर्ण,
	अणु .name = "madera-micsupp", पूर्ण,
	अणु .name = "madera-gpio", पूर्ण,
	अणु
		.name = "madera-extcon",
		.parent_supplies = cs47l90_supplies,
		.num_parent_supplies = 1, /* We only need MICVDD */
	पूर्ण,
	अणु
		.name = "cs47l90-codec",
		.parent_supplies = cs47l90_supplies,
		.num_parent_supplies = ARRAY_SIZE(cs47l90_supplies),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs47l92_supplies[] = अणु
	"MICVDD",
	"CPVDD1",
	"CPVDD2",
पूर्ण;

अटल स्थिर काष्ठा mfd_cell cs47l92_devs[] = अणु
	अणु .name = "madera-pinctrl", पूर्ण,
	अणु .name = "madera-irq", पूर्ण,
	अणु .name = "madera-micsupp", पूर्ण,
	अणु .name = "madera-gpio", पूर्ण,
	अणु
		.name = "madera-extcon",
		.parent_supplies = cs47l92_supplies,
		.num_parent_supplies = 1, /* We only need MICVDD */
	पूर्ण,
	अणु
		.name = "cs47l92-codec",
		.parent_supplies = cs47l92_supplies,
		.num_parent_supplies = ARRAY_SIZE(cs47l92_supplies),
	पूर्ण,
पूर्ण;

/* Used by madera-i2c and madera-spi drivers */
स्थिर अक्षर *madera_name_from_type(क्रमागत madera_type type)
अणु
	चयन (type) अणु
	हाल CS47L15:
		वापस "CS47L15";
	हाल CS47L35:
		वापस "CS47L35";
	हाल CS47L85:
		वापस "CS47L85";
	हाल CS47L90:
		वापस "CS47L90";
	हाल CS47L91:
		वापस "CS47L91";
	हाल CS42L92:
		वापस "CS42L92";
	हाल CS47L92:
		वापस "CS47L92";
	हाल CS47L93:
		वापस "CS47L93";
	हाल WM1840:
		वापस "WM1840";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(madera_name_from_type);

#घोषणा MADERA_BOOT_POLL_INTERVAL_USEC		5000
#घोषणा MADERA_BOOT_POLL_TIMEOUT_USEC		25000

अटल पूर्णांक madera_रुको_क्रम_boot_noack(काष्ठा madera *madera)
अणु
	kसमय_प्रकार समयout;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret = 0;

	/*
	 * We can't use an पूर्णांकerrupt as we need to runसमय resume to करो so,
	 * so we poll the status bit. This won't race with the पूर्णांकerrupt
	 * handler because it will be blocked on runसमय resume.
	 * The chip could NAK a पढ़ो request जबतक it is booting so ignore
	 * errors from regmap_पढ़ो.
	 */
	समयout = kसमय_add_us(kसमय_get(), MADERA_BOOT_POLL_TIMEOUT_USEC);
	regmap_पढ़ो(madera->regmap, MADERA_IRQ1_RAW_STATUS_1, &val);
	जबतक (!(val & MADERA_BOOT_DONE_STS1) &&
	       !kसमय_after(kसमय_get(), समयout)) अणु
		usleep_range(MADERA_BOOT_POLL_INTERVAL_USEC / 2,
			     MADERA_BOOT_POLL_INTERVAL_USEC);
		regmap_पढ़ो(madera->regmap, MADERA_IRQ1_RAW_STATUS_1, &val);
	पूर्ण

	अगर (!(val & MADERA_BOOT_DONE_STS1)) अणु
		dev_err(madera->dev, "Polling BOOT_DONE_STS timed out\n");
		ret = -ETIMEDOUT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक madera_रुको_क्रम_boot(काष्ठा madera *madera)
अणु
	पूर्णांक ret = madera_रुको_क्रम_boot_noack(madera);

	/*
	 * BOOT_DONE शेषs to unmasked on boot so we must ack it.
	 * Do this even after a समयout to aव्योम पूर्णांकerrupt storms.
	 */
	regmap_ग_लिखो(madera->regmap, MADERA_IRQ1_STATUS_1,
		     MADERA_BOOT_DONE_EINT1);

	pm_runसमय_mark_last_busy(madera->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक madera_soft_reset(काष्ठा madera *madera)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(madera->regmap, MADERA_SOFTWARE_RESET, 0);
	अगर (ret != 0) अणु
		dev_err(madera->dev, "Failed to soft reset device: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Allow समय क्रम पूर्णांकernal घड़ीs to startup after reset */
	usleep_range(MADERA_RESET_MIN_US, MADERA_RESET_MAX_US);

	वापस 0;
पूर्ण

अटल व्योम madera_enable_hard_reset(काष्ठा madera *madera)
अणु
	/*
	 * There are many existing out-of-tree users of these codecs that we
	 * can't अवरोध so preserve the expected behaviour of setting the line
	 * low to निश्चित reset.
	 */
	gpiod_set_raw_value_cansleep(madera->pdata.reset, 0);
पूर्ण

अटल व्योम madera_disable_hard_reset(काष्ठा madera *madera)
अणु
	gpiod_set_raw_value_cansleep(madera->pdata.reset, 1);

	usleep_range(MADERA_RESET_MIN_US, MADERA_RESET_MAX_US);
पूर्ण

अटल पूर्णांक __maybe_unused madera_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(dev);
	पूर्णांक ret;

	dev_dbg(dev, "Leaving sleep mode\n");

	अगर (!madera->reset_errata)
		madera_enable_hard_reset(madera);

	ret = regulator_enable(madera->dcvdd);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable DCVDD: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(madera->regmap, false);
	regcache_cache_only(madera->regmap_32bit, false);

	अगर (madera->reset_errata)
		usleep_range(ERRATA_DCVDD_MIN_US, ERRATA_DCVDD_MAX_US);
	अन्यथा
		madera_disable_hard_reset(madera);

	अगर (!madera->pdata.reset || madera->reset_errata) अणु
		ret = madera_रुको_क्रम_boot(madera);
		अगर (ret)
			जाओ err;

		ret = madera_soft_reset(madera);
		अगर (ret) अणु
			dev_err(dev, "Failed to reset: %d\n", ret);
			जाओ err;
		पूर्ण
	पूर्ण

	ret = madera_रुको_क्रम_boot(madera);
	अगर (ret)
		जाओ err;

	ret = regcache_sync(madera->regmap);
	अगर (ret) अणु
		dev_err(dev, "Failed to restore 16-bit register cache\n");
		जाओ err;
	पूर्ण

	ret = regcache_sync(madera->regmap_32bit);
	अगर (ret) अणु
		dev_err(dev, "Failed to restore 32-bit register cache\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	regcache_cache_only(madera->regmap_32bit, true);
	regcache_cache_only(madera->regmap, true);
	regulator_disable(madera->dcvdd);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused madera_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(dev);

	dev_dbg(madera->dev, "Entering sleep mode\n");

	regcache_cache_only(madera->regmap, true);
	regcache_mark_dirty(madera->regmap);
	regcache_cache_only(madera->regmap_32bit, true);
	regcache_mark_dirty(madera->regmap_32bit);

	regulator_disable(madera->dcvdd);

	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops madera_pm_ops = अणु
	SET_RUNTIME_PM_OPS(madera_runसमय_suspend,
			   madera_runसमय_resume,
			   शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(madera_pm_ops);

स्थिर काष्ठा of_device_id madera_of_match[] = अणु
	अणु .compatible = "cirrus,cs47l15", .data = (व्योम *)CS47L15 पूर्ण,
	अणु .compatible = "cirrus,cs47l35", .data = (व्योम *)CS47L35 पूर्ण,
	अणु .compatible = "cirrus,cs47l85", .data = (व्योम *)CS47L85 पूर्ण,
	अणु .compatible = "cirrus,cs47l90", .data = (व्योम *)CS47L90 पूर्ण,
	अणु .compatible = "cirrus,cs47l91", .data = (व्योम *)CS47L91 पूर्ण,
	अणु .compatible = "cirrus,cs42l92", .data = (व्योम *)CS42L92 पूर्ण,
	अणु .compatible = "cirrus,cs47l92", .data = (व्योम *)CS47L92 पूर्ण,
	अणु .compatible = "cirrus,cs47l93", .data = (व्योम *)CS47L93 पूर्ण,
	अणु .compatible = "cirrus,wm1840", .data = (व्योम *)WM1840 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, madera_of_match);
EXPORT_SYMBOL_GPL(madera_of_match);

अटल पूर्णांक madera_get_reset_gpio(काष्ठा madera *madera)
अणु
	काष्ठा gpio_desc *reset;

	अगर (madera->pdata.reset)
		वापस 0;

	reset = devm_gpiod_get_optional(madera->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(reset))
		वापस dev_err_probe(madera->dev, PTR_ERR(reset),
				"Failed to request /RESET");

	/*
	 * A hard reset is needed क्रम full reset of the chip. We allow running
	 * without hard reset only because it can be useful क्रम early
	 * prototyping and some debugging, but we need to warn it's not ideal.
	 */
	अगर (!reset)
		dev_warn(madera->dev,
			 "Running without reset GPIO is not recommended\n");

	madera->pdata.reset = reset;

	वापस 0;
पूर्ण

अटल व्योम madera_set_micbias_info(काष्ठा madera *madera)
अणु
	/*
	 * num_childbias is an array because future codecs can have dअगरferent
	 * childbiases क्रम each micbias. Unspecअगरied values शेष to 0.
	 */
	चयन (madera->type) अणु
	हाल CS47L15:
		madera->num_micbias = 1;
		madera->num_childbias[0] = 3;
		वापस;
	हाल CS47L35:
		madera->num_micbias = 2;
		madera->num_childbias[0] = 2;
		madera->num_childbias[1] = 2;
		वापस;
	हाल CS47L85:
	हाल WM1840:
		madera->num_micbias = 4;
		/* no child biases */
		वापस;
	हाल CS47L90:
	हाल CS47L91:
		madera->num_micbias = 2;
		madera->num_childbias[0] = 4;
		madera->num_childbias[1] = 4;
		वापस;
	हाल CS42L92:
	हाल CS47L92:
	हाल CS47L93:
		madera->num_micbias = 2;
		madera->num_childbias[0] = 4;
		madera->num_childbias[1] = 2;
		वापस;
	शेष:
		वापस;
	पूर्ण
पूर्ण

पूर्णांक madera_dev_init(काष्ठा madera *madera)
अणु
	काष्ठा device *dev = madera->dev;
	अचिन्हित पूर्णांक hwid;
	पूर्णांक (*patch_fn)(काष्ठा madera *) = शून्य;
	स्थिर काष्ठा mfd_cell *mfd_devs;
	पूर्णांक n_devs = 0;
	पूर्णांक i, ret;

	dev_set_drvdata(madera->dev, madera);
	BLOCKING_INIT_NOTIFIER_HEAD(&madera->notअगरier);
	mutex_init(&madera->dapm_ptr_lock);

	madera_set_micbias_info(madera);

	/*
	 * We need writable hw config info that all children can share.
	 * Simplest to take one shared copy of pdata काष्ठा.
	 */
	अगर (dev_get_platdata(madera->dev)) अणु
		स_नकल(&madera->pdata, dev_get_platdata(madera->dev),
		       माप(madera->pdata));
	पूर्ण

	madera->mclk[MADERA_MCLK1].id = "mclk1";
	madera->mclk[MADERA_MCLK2].id = "mclk2";
	madera->mclk[MADERA_MCLK3].id = "mclk3";

	ret = devm_clk_bulk_get_optional(madera->dev, ARRAY_SIZE(madera->mclk),
					 madera->mclk);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to get clocks: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Not using devm_clk_get to prevent अवरोधage of existing DTs */
	अगर (!madera->mclk[MADERA_MCLK2].clk)
		dev_warn(madera->dev, "Missing MCLK2, requires 32kHz clock\n");

	ret = madera_get_reset_gpio(madera);
	अगर (ret)
		वापस ret;

	regcache_cache_only(madera->regmap, true);
	regcache_cache_only(madera->regmap_32bit, true);

	क्रम (i = 0; i < ARRAY_SIZE(madera_core_supplies); i++)
		madera->core_supplies[i].supply = madera_core_supplies[i];

	madera->num_core_supplies = ARRAY_SIZE(madera_core_supplies);

	/*
	 * On some codecs DCVDD could be supplied by the पूर्णांकernal LDO1.
	 * For those we must add the LDO1 driver beक्रमe requesting DCVDD
	 * No devm_ because we need to control shutकरोwn order of children.
	 */
	चयन (madera->type) अणु
	हाल CS47L15:
		madera->reset_errata = true;
		अवरोध;
	हाल CS47L35:
	हाल CS47L90:
	हाल CS47L91:
	हाल CS42L92:
	हाल CS47L92:
	हाल CS47L93:
		अवरोध;
	हाल CS47L85:
	हाल WM1840:
		ret = mfd_add_devices(madera->dev, PLATFORM_DEVID_NONE,
				      madera_lकरो1_devs,
				      ARRAY_SIZE(madera_lकरो1_devs),
				      शून्य, 0, शून्य);
		अगर (ret) अणु
			dev_err(dev, "Failed to add LDO1 child: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		/* No poपूर्णांक continuing अगर the type is unknown */
		dev_err(madera->dev, "Unknown device type %d\n", madera->type);
		वापस -ENODEV;
	पूर्ण

	ret = devm_regulator_bulk_get(dev, madera->num_core_supplies,
				      madera->core_supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to request core supplies: %d\n", ret);
		जाओ err_devs;
	पूर्ण

	/*
	 * Don't use devres here. If the regulator is one of our children it
	 * will alपढ़ोy have been हटाओd beक्रमe devres cleanup on this mfd
	 * driver tries to call put() on it. We need control of shutकरोwn order.
	 */
	madera->dcvdd = regulator_get(madera->dev, "DCVDD");
	अगर (IS_ERR(madera->dcvdd)) अणु
		ret = PTR_ERR(madera->dcvdd);
		dev_err(dev, "Failed to request DCVDD: %d\n", ret);
		जाओ err_devs;
	पूर्ण

	ret = regulator_bulk_enable(madera->num_core_supplies,
				    madera->core_supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable core supplies: %d\n", ret);
		जाओ err_dcvdd;
	पूर्ण

	अगर (madera->reset_errata)
		madera_disable_hard_reset(madera);

	ret = regulator_enable(madera->dcvdd);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable DCVDD: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	अगर (madera->reset_errata)
		usleep_range(ERRATA_DCVDD_MIN_US, ERRATA_DCVDD_MAX_US);
	अन्यथा
		madera_disable_hard_reset(madera);

	regcache_cache_only(madera->regmap, false);
	regcache_cache_only(madera->regmap_32bit, false);

	ret = madera_रुको_क्रम_boot_noack(madera);
	अगर (ret) अणु
		dev_err(madera->dev, "Device failed initial boot: %d\n", ret);
		जाओ err_reset;
	पूर्ण

	/*
	 * Now we can घातer up and verअगरy that this is a chip we know about
	 * beक्रमe we start करोing any ग_लिखोs to its रेजिस्टरs.
	 */
	ret = regmap_पढ़ो(madera->regmap, MADERA_SOFTWARE_RESET, &hwid);
	अगर (ret) अणु
		dev_err(dev, "Failed to read ID register: %d\n", ret);
		जाओ err_reset;
	पूर्ण

	चयन (hwid) अणु
	हाल CS47L15_SILICON_ID:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L15)) अणु
			चयन (madera->type) अणु
			हाल CS47L15:
				patch_fn = &cs47l15_patch;
				mfd_devs = cs47l15_devs;
				n_devs = ARRAY_SIZE(cs47l15_devs);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल CS47L35_SILICON_ID:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L35)) अणु
			चयन (madera->type) अणु
			हाल CS47L35:
				patch_fn = cs47l35_patch;
				mfd_devs = cs47l35_devs;
				n_devs = ARRAY_SIZE(cs47l35_devs);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल CS47L85_SILICON_ID:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L85)) अणु
			चयन (madera->type) अणु
			हाल CS47L85:
			हाल WM1840:
				patch_fn = cs47l85_patch;
				mfd_devs = cs47l85_devs;
				n_devs = ARRAY_SIZE(cs47l85_devs);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल CS47L90_SILICON_ID:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L90)) अणु
			चयन (madera->type) अणु
			हाल CS47L90:
			हाल CS47L91:
				patch_fn = cs47l90_patch;
				mfd_devs = cs47l90_devs;
				n_devs = ARRAY_SIZE(cs47l90_devs);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल CS47L92_SILICON_ID:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L92)) अणु
			चयन (madera->type) अणु
			हाल CS42L92:
			हाल CS47L92:
			हाल CS47L93:
				patch_fn = cs47l92_patch;
				mfd_devs = cs47l92_devs;
				n_devs = ARRAY_SIZE(cs47l92_devs);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		dev_err(madera->dev, "Unknown device ID: %x\n", hwid);
		ret = -EINVAL;
		जाओ err_reset;
	पूर्ण

	अगर (!n_devs) अणु
		dev_err(madera->dev, "Device ID 0x%x not a %s\n", hwid,
			madera->type_name);
		ret = -ENODEV;
		जाओ err_reset;
	पूर्ण

	/*
	 * It looks like a device we support. If we करोn't have a hard reset
	 * we can now attempt a soft reset.
	 */
	अगर (!madera->pdata.reset || madera->reset_errata) अणु
		ret = madera_soft_reset(madera);
		अगर (ret)
			जाओ err_reset;
	पूर्ण

	ret = madera_रुको_क्रम_boot(madera);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to clear boot done: %d\n", ret);
		जाओ err_reset;
	पूर्ण

	ret = regmap_पढ़ो(madera->regmap, MADERA_HARDWARE_REVISION,
			  &madera->rev);
	अगर (ret) अणु
		dev_err(dev, "Failed to read revision register: %d\n", ret);
		जाओ err_reset;
	पूर्ण
	madera->rev &= MADERA_HW_REVISION_MASK;

	dev_info(dev, "%s silicon revision %d\n", madera->type_name,
		 madera->rev);

	/* Apply hardware patch */
	अगर (patch_fn) अणु
		ret = patch_fn(madera);
		अगर (ret) अणु
			dev_err(madera->dev, "Failed to apply patch %d\n", ret);
			जाओ err_reset;
		पूर्ण
	पूर्ण

	/* Init 32k घड़ी sourced from MCLK2 */
	ret = clk_prepare_enable(madera->mclk[MADERA_MCLK2].clk);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to enable 32k clock: %d\n", ret);
		जाओ err_reset;
	पूर्ण

	ret = regmap_update_bits(madera->regmap,
			MADERA_CLOCK_32K_1,
			MADERA_CLK_32K_ENA_MASK | MADERA_CLK_32K_SRC_MASK,
			MADERA_CLK_32K_ENA | MADERA_32KZ_MCLK2);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to init 32k clock: %d\n", ret);
		जाओ err_घड़ी;
	पूर्ण

	pm_runसमय_set_active(madera->dev);
	pm_runसमय_enable(madera->dev);
	pm_runसमय_set_स्वतःsuspend_delay(madera->dev, 100);
	pm_runसमय_use_स्वतःsuspend(madera->dev);

	/* No devm_ because we need to control shutकरोwn order of children */
	ret = mfd_add_devices(madera->dev, PLATFORM_DEVID_NONE,
			      mfd_devs, n_devs,
			      शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to add subdevices: %d\n", ret);
		जाओ err_pm_runसमय;
	पूर्ण

	वापस 0;

err_pm_runसमय:
	pm_runसमय_disable(madera->dev);
err_घड़ी:
	clk_disable_unprepare(madera->mclk[MADERA_MCLK2].clk);
err_reset:
	madera_enable_hard_reset(madera);
	regulator_disable(madera->dcvdd);
err_enable:
	regulator_bulk_disable(madera->num_core_supplies,
			       madera->core_supplies);
err_dcvdd:
	regulator_put(madera->dcvdd);
err_devs:
	mfd_हटाओ_devices(dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(madera_dev_init);

पूर्णांक madera_dev_निकास(काष्ठा madera *madera)
अणु
	/* Prevent any IRQs being serviced जबतक we clean up */
	disable_irq(madera->irq);

	pm_runसमय_get_sync(madera->dev);

	mfd_हटाओ_devices(madera->dev);

	pm_runसमय_disable(madera->dev);

	regulator_disable(madera->dcvdd);
	regulator_put(madera->dcvdd);

	mfd_हटाओ_devices_late(madera->dev);

	pm_runसमय_set_suspended(madera->dev);
	pm_runसमय_put_noidle(madera->dev);

	clk_disable_unprepare(madera->mclk[MADERA_MCLK2].clk);

	madera_enable_hard_reset(madera);

	regulator_bulk_disable(madera->num_core_supplies,
			       madera->core_supplies);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_dev_निकास);

MODULE_DESCRIPTION("Madera core MFD driver");
MODULE_AUTHOR("Richard Fitzgerald <rf@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
