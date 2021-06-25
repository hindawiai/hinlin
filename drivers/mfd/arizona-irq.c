<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Arizona पूर्णांकerrupt support
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>

#समावेश "arizona.h"

#घोषणा ARIZONA_AOD_IRQ_INDEX 0
#घोषणा ARIZONA_MAIN_IRQ_INDEX 1

अटल पूर्णांक arizona_map_irq(काष्ठा arizona *arizona, पूर्णांक irq)
अणु
	पूर्णांक ret;

	अगर (arizona->aod_irq_chip) अणु
		ret = regmap_irq_get_virq(arizona->aod_irq_chip, irq);
		अगर (ret >= 0)
			वापस ret;
	पूर्ण

	वापस regmap_irq_get_virq(arizona->irq_chip, irq);
पूर्ण

पूर्णांक arizona_request_irq(काष्ठा arizona *arizona, पूर्णांक irq, अक्षर *name,
			   irq_handler_t handler, व्योम *data)
अणु
	irq = arizona_map_irq(arizona, irq);
	अगर (irq < 0)
		वापस irq;

	वापस request_thपढ़ोed_irq(irq, शून्य, handler, IRQF_ONESHOT,
				    name, data);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_request_irq);

व्योम arizona_मुक्त_irq(काष्ठा arizona *arizona, पूर्णांक irq, व्योम *data)
अणु
	irq = arizona_map_irq(arizona, irq);
	अगर (irq < 0)
		वापस;

	मुक्त_irq(irq, data);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_मुक्त_irq);

पूर्णांक arizona_set_irq_wake(काष्ठा arizona *arizona, पूर्णांक irq, पूर्णांक on)
अणु
	irq = arizona_map_irq(arizona, irq);
	अगर (irq < 0)
		वापस irq;

	वापस irq_set_irq_wake(irq, on);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_set_irq_wake);

अटल irqवापस_t arizona_boot_करोne(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona *arizona = data;

	dev_dbg(arizona->dev, "Boot done\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arizona_ctrlअगर_err(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona *arizona = data;

	/*
	 * For pretty much all potential sources a रेजिस्टर cache sync
	 * won't help, we've just got a software bug somewhere.
	 */
	dev_err(arizona->dev, "Control interface error\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arizona_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona *arizona = data;
	bool poll;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(arizona->dev);
	अगर (ret < 0) अणु
		dev_err(arizona->dev, "Failed to resume device: %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	करो अणु
		poll = false;

		अगर (arizona->aod_irq_chip) अणु
			/*
			 * Check the AOD status रेजिस्टर to determine whether
			 * the nested IRQ handler should be called.
			 */
			ret = regmap_पढ़ो(arizona->regmap,
					  ARIZONA_AOD_IRQ1, &val);
			अगर (ret)
				dev_warn(arizona->dev,
					"Failed to read AOD IRQ1 %d\n", ret);
			अन्यथा अगर (val)
				handle_nested_irq(
					irq_find_mapping(arizona->virq, 0));
		पूर्ण

		/*
		 * Check अगर one of the मुख्य पूर्णांकerrupts is निश्चितed and only
		 * check that करोमुख्य अगर it is.
		 */
		ret = regmap_पढ़ो(arizona->regmap, ARIZONA_IRQ_PIN_STATUS,
				  &val);
		अगर (ret == 0 && val & ARIZONA_IRQ1_STS) अणु
			handle_nested_irq(irq_find_mapping(arizona->virq, 1));
		पूर्ण अन्यथा अगर (ret != 0) अणु
			dev_err(arizona->dev,
				"Failed to read main IRQ status: %d\n", ret);
		पूर्ण

		/*
		 * Poll the IRQ pin status to see अगर we're really करोne
		 * अगर the पूर्णांकerrupt controller can't करो it क्रम us.
		 */
		अगर (!arizona->pdata.irq_gpio) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (arizona->pdata.irq_flags & IRQF_TRIGGER_RISING &&
			   gpio_get_value_cansleep(arizona->pdata.irq_gpio)) अणु
			poll = true;
		पूर्ण अन्यथा अगर (arizona->pdata.irq_flags & IRQF_TRIGGER_FALLING &&
			   !gpio_get_value_cansleep(arizona->pdata.irq_gpio)) अणु
			poll = true;
		पूर्ण
	पूर्ण जबतक (poll);

	pm_runसमय_mark_last_busy(arizona->dev);
	pm_runसमय_put_स्वतःsuspend(arizona->dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम arizona_irq_enable(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम arizona_irq_disable(काष्ठा irq_data *data)
अणु
पूर्ण

अटल पूर्णांक arizona_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा arizona *arizona = irq_data_get_irq_chip_data(data);

	वापस irq_set_irq_wake(arizona->irq, on);
पूर्ण

अटल काष्ठा irq_chip arizona_irq_chip = अणु
	.name			= "arizona",
	.irq_disable		= arizona_irq_disable,
	.irq_enable		= arizona_irq_enable,
	.irq_set_wake		= arizona_irq_set_wake,
पूर्ण;

अटल काष्ठा lock_class_key arizona_irq_lock_class;
अटल काष्ठा lock_class_key arizona_irq_request_class;

अटल पूर्णांक arizona_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			      irq_hw_number_t hw)
अणु
	काष्ठा arizona *data = h->host_data;

	irq_set_chip_data(virq, data);
	irq_set_lockdep_class(virq, &arizona_irq_lock_class,
		&arizona_irq_request_class);
	irq_set_chip_and_handler(virq, &arizona_irq_chip, handle_simple_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops arizona_करोमुख्य_ops = अणु
	.map	= arizona_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

पूर्णांक arizona_irq_init(काष्ठा arizona *arizona)
अणु
	पूर्णांक flags = IRQF_ONESHOT;
	पूर्णांक ret;
	स्थिर काष्ठा regmap_irq_chip *aod, *irq;
	काष्ठा irq_data *irq_data;
	अचिन्हित पूर्णांक virq;

	arizona->ctrlअगर_error = true;

	चयन (arizona->type) अणु
#अगर_घोषित CONFIG_MFD_WM5102
	हाल WM5102:
		aod = &wm5102_aod;
		irq = &wm5102_irq;

		arizona->ctrlअगर_error = false;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MFD_WM5110
	हाल WM5110:
	हाल WM8280:
		aod = &wm5110_aod;

		चयन (arizona->rev) अणु
		हाल 0 ... 2:
			irq = &wm5110_irq;
			अवरोध;
		शेष:
			irq = &wm5110_revd_irq;
			अवरोध;
		पूर्ण

		arizona->ctrlअगर_error = false;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MFD_CS47L24
	हाल WM1831:
	हाल CS47L24:
		aod = शून्य;
		irq = &cs47l24_irq;

		arizona->ctrlअगर_error = false;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MFD_WM8997
	हाल WM8997:
		aod = &wm8997_aod;
		irq = &wm8997_irq;

		arizona->ctrlअगर_error = false;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MFD_WM8998
	हाल WM8998:
	हाल WM1814:
		aod = &wm8998_aod;
		irq = &wm8998_irq;

		arizona->ctrlअगर_error = false;
		अवरोध;
#पूर्ण_अगर
	शेष:
		BUG_ON("Unknown Arizona class device" == शून्य);
		वापस -EINVAL;
	पूर्ण

	/* Disable all wake sources by शेष */
	regmap_ग_लिखो(arizona->regmap, ARIZONA_WAKE_CONTROL, 0);

	/* Read the flags from the पूर्णांकerrupt controller अगर not specअगरied */
	अगर (!arizona->pdata.irq_flags) अणु
		irq_data = irq_get_irq_data(arizona->irq);
		अगर (!irq_data) अणु
			dev_err(arizona->dev, "Invalid IRQ: %d\n",
				arizona->irq);
			वापस -EINVAL;
		पूर्ण

		arizona->pdata.irq_flags = irqd_get_trigger_type(irq_data);
		चयन (arizona->pdata.irq_flags) अणु
		हाल IRQF_TRIGGER_LOW:
		हाल IRQF_TRIGGER_HIGH:
		हाल IRQF_TRIGGER_RISING:
		हाल IRQF_TRIGGER_FALLING:
			अवरोध;

		हाल IRQ_TYPE_NONE:
		शेष:
			/* Device शेष */
			arizona->pdata.irq_flags = IRQF_TRIGGER_LOW;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (arizona->pdata.irq_flags & (IRQF_TRIGGER_HIGH |
					IRQF_TRIGGER_RISING)) अणु
		ret = regmap_update_bits(arizona->regmap, ARIZONA_IRQ_CTRL_1,
					 ARIZONA_IRQ_POL, 0);
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Couldn't set IRQ polarity: %d\n",
				ret);
			जाओ err;
		पूर्ण
	पूर्ण

	flags |= arizona->pdata.irq_flags;

	/* Allocate a भव IRQ करोमुख्य to distribute to the regmap करोमुख्यs */
	arizona->virq = irq_करोमुख्य_add_linear(शून्य, 2, &arizona_करोमुख्य_ops,
					      arizona);
	अगर (!arizona->virq) अणु
		dev_err(arizona->dev, "Failed to add core IRQ domain\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (aod) अणु
		virq = irq_create_mapping(arizona->virq, ARIZONA_AOD_IRQ_INDEX);
		अगर (!virq) अणु
			dev_err(arizona->dev, "Failed to map AOD IRQs\n");
			ret = -EINVAL;
			जाओ err_करोमुख्य;
		पूर्ण

		ret = regmap_add_irq_chip(arizona->regmap, virq, IRQF_ONESHOT,
					  0, aod, &arizona->aod_irq_chip);
		अगर (ret != 0) अणु
			dev_err(arizona->dev,
				"Failed to add AOD IRQs: %d\n", ret);
			जाओ err_map_aod;
		पूर्ण
	पूर्ण

	virq = irq_create_mapping(arizona->virq, ARIZONA_MAIN_IRQ_INDEX);
	अगर (!virq) अणु
		dev_err(arizona->dev, "Failed to map main IRQs\n");
		ret = -EINVAL;
		जाओ err_aod;
	पूर्ण

	ret = regmap_add_irq_chip(arizona->regmap, virq, IRQF_ONESHOT,
				  0, irq, &arizona->irq_chip);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to add main IRQs: %d\n", ret);
		जाओ err_map_मुख्य_irq;
	पूर्ण

	/* Used to emulate edge trigger and to work around broken pinmux */
	अगर (arizona->pdata.irq_gpio) अणु
		अगर (gpio_to_irq(arizona->pdata.irq_gpio) != arizona->irq) अणु
			dev_warn(arizona->dev, "IRQ %d is not GPIO %d (%d)\n",
				 arizona->irq, arizona->pdata.irq_gpio,
				 gpio_to_irq(arizona->pdata.irq_gpio));
			arizona->irq = gpio_to_irq(arizona->pdata.irq_gpio);
		पूर्ण

		ret = devm_gpio_request_one(arizona->dev,
					    arizona->pdata.irq_gpio,
					    GPIOF_IN, "arizona IRQ");
		अगर (ret != 0) अणु
			dev_err(arizona->dev,
				"Failed to request IRQ GPIO %d:: %d\n",
				arizona->pdata.irq_gpio, ret);
			arizona->pdata.irq_gpio = 0;
		पूर्ण
	पूर्ण

	ret = request_thपढ़ोed_irq(arizona->irq, शून्य, arizona_irq_thपढ़ो,
				   flags, "arizona", arizona);

	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to request primary IRQ %d: %d\n",
			arizona->irq, ret);
		जाओ err_मुख्य_irq;
	पूर्ण

	/* Make sure the boot करोne IRQ is unmasked क्रम resumes */
	ret = arizona_request_irq(arizona, ARIZONA_IRQ_BOOT_DONE, "Boot done",
				  arizona_boot_करोne, arizona);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to request boot done %d: %d\n",
			arizona->irq, ret);
		जाओ err_boot_करोne;
	पूर्ण

	/* Handle control पूर्णांकerface errors in the core */
	अगर (arizona->ctrlअगर_error) अणु
		ret = arizona_request_irq(arizona, ARIZONA_IRQ_CTRLIF_ERR,
					  "Control interface error",
					  arizona_ctrlअगर_err, arizona);
		अगर (ret != 0) अणु
			dev_err(arizona->dev,
				"Failed to request CTRLIF_ERR %d: %d\n",
				arizona->irq, ret);
			जाओ err_ctrlअगर;
		पूर्ण
	पूर्ण

	वापस 0;

err_ctrlअगर:
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_BOOT_DONE, arizona);
err_boot_करोne:
	मुक्त_irq(arizona->irq, arizona);
err_मुख्य_irq:
	regmap_del_irq_chip(irq_find_mapping(arizona->virq,
					     ARIZONA_MAIN_IRQ_INDEX),
			    arizona->irq_chip);
err_map_मुख्य_irq:
	irq_dispose_mapping(irq_find_mapping(arizona->virq,
					     ARIZONA_MAIN_IRQ_INDEX));
err_aod:
	regmap_del_irq_chip(irq_find_mapping(arizona->virq,
					     ARIZONA_AOD_IRQ_INDEX),
			    arizona->aod_irq_chip);
err_map_aod:
	irq_dispose_mapping(irq_find_mapping(arizona->virq,
					     ARIZONA_AOD_IRQ_INDEX));
err_करोमुख्य:
	irq_करोमुख्य_हटाओ(arizona->virq);
err:
	वापस ret;
पूर्ण

पूर्णांक arizona_irq_निकास(काष्ठा arizona *arizona)
अणु
	अचिन्हित पूर्णांक virq;

	अगर (arizona->ctrlअगर_error)
		arizona_मुक्त_irq(arizona, ARIZONA_IRQ_CTRLIF_ERR, arizona);
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_BOOT_DONE, arizona);

	virq = irq_find_mapping(arizona->virq, ARIZONA_MAIN_IRQ_INDEX);
	regmap_del_irq_chip(virq, arizona->irq_chip);
	irq_dispose_mapping(virq);

	virq = irq_find_mapping(arizona->virq, ARIZONA_AOD_IRQ_INDEX);
	regmap_del_irq_chip(virq, arizona->aod_irq_chip);
	irq_dispose_mapping(virq);

	irq_करोमुख्य_हटाओ(arizona->virq);

	मुक्त_irq(arizona->irq, arizona);

	वापस 0;
पूर्ण
