<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arizona-spi.c  --  Arizona SPI bus पूर्णांकerface
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of.h>
#समावेश <uapi/linux/input-event-codes.h>

#समावेश <linux/mfd/arizona/core.h>

#समावेश "arizona.h"

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_gpio_params reset_gpios = अणु 1, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params lकरोena_gpios = अणु 2, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping arizona_acpi_gpios[] = अणु
	अणु "reset-gpios", &reset_gpios, 1, पूर्ण,
	अणु "wlf,ldoena-gpios", &lकरोena_gpios, 1 पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * The ACPI resources क्रम the device only describe बाह्यal GPIO-s. They करो
 * not provide mappings क्रम the GPIO-s coming from the Arizona codec itself.
 */
अटल स्थिर काष्ठा gpiod_lookup arizona_soc_gpios[] = अणु
	अणु "arizona", 2, "wlf,spkvdd-ena", 0, GPIO_ACTIVE_HIGH पूर्ण,
	अणु "arizona", 4, "wlf,micd-pol", 0, GPIO_ACTIVE_LOW पूर्ण,
पूर्ण;

/*
 * The AOSP 3.5 mm Headset: Accessory Specअगरication gives the following values:
 * Function A Play/Pause:           0 ohm
 * Function D Voice assistant:    135 ohm
 * Function B Volume Up           240 ohm
 * Function C Volume Down         470 ohm
 * Minimum Mic DC resistance     1000 ohm
 * Minimum Ear speaker impedance   16 ohm
 * Note the first max value below must be less then the min. speaker impedance,
 * to allow CTIA/OMTP detection to work. The other max values are the बंदst
 * value from extcon-arizona.c:arizona_micd_levels halfway 2 button resistances.
 */
अटल स्थिर काष्ठा arizona_micd_range arizona_micd_aosp_ranges[] = अणु
	अणु .max =  11, .key = KEY_PLAYPAUSE पूर्ण,
	अणु .max = 186, .key = KEY_VOICECOMMAND पूर्ण,
	अणु .max = 348, .key = KEY_VOLUMEUP पूर्ण,
	अणु .max = 752, .key = KEY_VOLUMEDOWN पूर्ण,
पूर्ण;

अटल व्योम arizona_spi_acpi_हटाओ_lookup(व्योम *lookup)
अणु
	gpiod_हटाओ_lookup_table(lookup);
पूर्ण

अटल पूर्णांक arizona_spi_acpi_probe(काष्ठा arizona *arizona)
अणु
	काष्ठा gpiod_lookup_table *lookup;
	acpi_status status;
	पूर्णांक ret;

	/* Add mappings क्रम the 2 ACPI declared GPIOs used क्रम reset and lकरो-ena */
	devm_acpi_dev_add_driver_gpios(arizona->dev, arizona_acpi_gpios);

	/* Add lookups क्रम the SoCs own GPIOs used क्रम micdet-polarity and spkVDD-enable */
	lookup = devm_kzalloc(arizona->dev,
			      काष्ठा_size(lookup, table, ARRAY_SIZE(arizona_soc_gpios) + 1),
			      GFP_KERNEL);
	अगर (!lookup)
		वापस -ENOMEM;

	lookup->dev_id = dev_name(arizona->dev);
	स_नकल(lookup->table, arizona_soc_gpios, माप(arizona_soc_gpios));

	gpiod_add_lookup_table(lookup);
	ret = devm_add_action_or_reset(arizona->dev, arizona_spi_acpi_हटाओ_lookup, lookup);
	अगर (ret)
		वापस ret;

	/* Enable 32KHz घड़ी from SoC to codec क्रम jack-detect */
	status = acpi_evaluate_object(ACPI_HANDLE(arizona->dev), "CLKE", शून्य, शून्य);
	अगर (ACPI_FAILURE(status))
		dev_warn(arizona->dev, "Failed to enable 32KHz clk ACPI error %d\n", status);

	/*
	 * Some DSDTs wrongly declare the IRQ trigger-type as IRQF_TRIGGER_FALLING
	 * The IRQ line will stay low when a new IRQ event happens between पढ़ोing
	 * the IRQ status flags and acknowledging them. When the IRQ line stays
	 * low like this the IRQ will never trigger again when its type is set
	 * to IRQF_TRIGGER_FALLING. Correct the IRQ trigger-type to fix this.
	 *
	 * Note theoretically it is possible that some boards are not capable
	 * of handling active low level पूर्णांकerrupts. In that हाल setting the
	 * flag to IRQF_TRIGGER_FALLING would not be a bug (and we would need
	 * to work around this) but so far all known usages of IRQF_TRIGGER_FALLING
	 * are a bug in the board's DSDT.
	 */
	arizona->pdata.irq_flags = IRQF_TRIGGER_LOW;

	/* Wait 200 ms after jack insertion */
	arizona->pdata.micd_detect_debounce = 200;

	/* Use standard AOSP values क्रम headset-button mappings */
	arizona->pdata.micd_ranges = arizona_micd_aosp_ranges;
	arizona->pdata.num_micd_ranges = ARRAY_SIZE(arizona_micd_aosp_ranges);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id arizona_acpi_match[] = अणु
	अणु
		.id = "WM510204",
		.driver_data = WM5102,
	पूर्ण,
	अणु
		.id = "WM510205",
		.driver_data = WM5102,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, arizona_acpi_match);
#अन्यथा
अटल पूर्णांक arizona_spi_acpi_probe(काष्ठा arizona *arizona)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक arizona_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	स्थिर व्योम *match_data;
	काष्ठा arizona *arizona;
	स्थिर काष्ठा regmap_config *regmap_config = शून्य;
	अचिन्हित दीर्घ type = 0;
	पूर्णांक ret;

	match_data = device_get_match_data(&spi->dev);
	अगर (match_data)
		type = (अचिन्हित दीर्घ)match_data;
	अन्यथा अगर (id)
		type = id->driver_data;

	चयन (type) अणु
	हाल WM5102:
		अगर (IS_ENABLED(CONFIG_MFD_WM5102))
			regmap_config = &wm5102_spi_regmap;
		अवरोध;
	हाल WM5110:
	हाल WM8280:
		अगर (IS_ENABLED(CONFIG_MFD_WM5110))
			regmap_config = &wm5110_spi_regmap;
		अवरोध;
	हाल WM1831:
	हाल CS47L24:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L24))
			regmap_config = &cs47l24_spi_regmap;
		अवरोध;
	शेष:
		dev_err(&spi->dev, "Unknown device type %ld\n", type);
		वापस -EINVAL;
	पूर्ण

	अगर (!regmap_config) अणु
		dev_err(&spi->dev,
			"No kernel support for device type %ld\n", type);
		वापस -EINVAL;
	पूर्ण

	arizona = devm_kzalloc(&spi->dev, माप(*arizona), GFP_KERNEL);
	अगर (arizona == शून्य)
		वापस -ENOMEM;

	arizona->regmap = devm_regmap_init_spi(spi, regmap_config);
	अगर (IS_ERR(arizona->regmap)) अणु
		ret = PTR_ERR(arizona->regmap);
		dev_err(&spi->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	arizona->type = type;
	arizona->dev = &spi->dev;
	arizona->irq = spi->irq;

	अगर (has_acpi_companion(&spi->dev)) अणु
		ret = arizona_spi_acpi_probe(arizona);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस arizona_dev_init(arizona);
पूर्ण

अटल पूर्णांक arizona_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा arizona *arizona = spi_get_drvdata(spi);

	arizona_dev_निकास(arizona);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id arizona_spi_ids[] = अणु
	अणु "wm5102", WM5102 पूर्ण,
	अणु "wm5110", WM5110 पूर्ण,
	अणु "wm8280", WM8280 पूर्ण,
	अणु "wm1831", WM1831 पूर्ण,
	अणु "cs47l24", CS47L24 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, arizona_spi_ids);

अटल काष्ठा spi_driver arizona_spi_driver = अणु
	.driver = अणु
		.name	= "arizona",
		.pm	= &arizona_pm_ops,
		.of_match_table	= of_match_ptr(arizona_of_match),
		.acpi_match_table = ACPI_PTR(arizona_acpi_match),
	पूर्ण,
	.probe		= arizona_spi_probe,
	.हटाओ		= arizona_spi_हटाओ,
	.id_table	= arizona_spi_ids,
पूर्ण;

module_spi_driver(arizona_spi_driver);

MODULE_SOFTDEP("pre: arizona_ldo1");
MODULE_DESCRIPTION("Arizona SPI bus interface");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
