<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-jack.c  --  ALSA SoC jack handling
//
// Copyright 2008 Wolfson Microelectronics PLC.
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/suspend.h>
#समावेश <trace/events/asoc.h>

काष्ठा jack_gpio_tbl अणु
	पूर्णांक count;
	काष्ठा snd_soc_jack *jack;
	काष्ठा snd_soc_jack_gpio *gpios;
पूर्ण;

/**
 * snd_soc_jack_report - Report the current status क्रम a jack
 *
 * @jack:   the jack
 * @status: a biपंचांगask of क्रमागत snd_jack_type values that are currently detected.
 * @mask:   a biपंचांगask of क्रमागत snd_jack_type values that being reported.
 *
 * If configured using snd_soc_jack_add_pins() then the associated
 * DAPM pins will be enabled or disabled as appropriate and DAPM
 * synchronised.
 *
 * Note: This function uses mutexes and should be called from a
 * context which can sleep (such as a workqueue).
 */
व्योम snd_soc_jack_report(काष्ठा snd_soc_jack *jack, पूर्णांक status, पूर्णांक mask)
अणु
	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा snd_soc_jack_pin *pin;
	अचिन्हित पूर्णांक sync = 0;
	पूर्णांक enable;

	अगर (!jack)
		वापस;
	trace_snd_soc_jack_report(jack, mask, status);

	dapm = &jack->card->dapm;

	mutex_lock(&jack->mutex);

	jack->status &= ~mask;
	jack->status |= status & mask;

	trace_snd_soc_jack_notअगरy(jack, status);

	list_क्रम_each_entry(pin, &jack->pins, list) अणु
		enable = pin->mask & jack->status;

		अगर (pin->invert)
			enable = !enable;

		अगर (enable)
			snd_soc_dapm_enable_pin(dapm, pin->pin);
		अन्यथा
			snd_soc_dapm_disable_pin(dapm, pin->pin);

		/* we need to sync क्रम this हाल only */
		sync = 1;
	पूर्ण

	/* Report beक्रमe the DAPM sync to help users updating micbias status */
	blocking_notअगरier_call_chain(&jack->notअगरier, jack->status, jack);

	अगर (sync)
		snd_soc_dapm_sync(dapm);

	snd_jack_report(jack->jack, jack->status);

	mutex_unlock(&jack->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_jack_report);

/**
 * snd_soc_jack_add_zones - Associate voltage zones with jack
 *
 * @jack:  ASoC jack
 * @count: Number of zones
 * @zones:  Array of zones
 *
 * After this function has been called the zones specअगरied in the
 * array will be associated with the jack.
 */
पूर्णांक snd_soc_jack_add_zones(काष्ठा snd_soc_jack *jack, पूर्णांक count,
			  काष्ठा snd_soc_jack_zone *zones)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		INIT_LIST_HEAD(&zones[i].list);
		list_add(&(zones[i].list), &jack->jack_zones);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_jack_add_zones);

/**
 * snd_soc_jack_get_type - Based on the mic bias value, this function वापसs
 * the type of jack from the zones declared in the jack type
 *
 * @jack:  ASoC jack
 * @micbias_voltage:  mic bias voltage at adc channel when jack is plugged in
 *
 * Based on the mic bias value passed, this function helps identअगरy
 * the type of jack from the alपढ़ोy declared jack zones
 */
पूर्णांक snd_soc_jack_get_type(काष्ठा snd_soc_jack *jack, पूर्णांक micbias_voltage)
अणु
	काष्ठा snd_soc_jack_zone *zone;

	list_क्रम_each_entry(zone, &jack->jack_zones, list) अणु
		अगर (micbias_voltage >= zone->min_mv &&
			micbias_voltage < zone->max_mv)
				वापस zone->jack_type;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_jack_get_type);

/**
 * snd_soc_jack_add_pins - Associate DAPM pins with an ASoC jack
 *
 * @jack:  ASoC jack
 * @count: Number of pins
 * @pins:  Array of pins
 *
 * After this function has been called the DAPM pins specअगरied in the
 * pins array will have their status updated to reflect the current
 * state of the jack whenever the jack status is updated.
 */
पूर्णांक snd_soc_jack_add_pins(काष्ठा snd_soc_jack *jack, पूर्णांक count,
			  काष्ठा snd_soc_jack_pin *pins)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		अगर (!pins[i].pin) अणु
			dev_err(jack->card->dev, "ASoC: No name for pin %d\n",
				i);
			वापस -EINVAL;
		पूर्ण
		अगर (!pins[i].mask) अणु
			dev_err(jack->card->dev, "ASoC: No mask for pin %d"
				" (%s)\n", i, pins[i].pin);
			वापस -EINVAL;
		पूर्ण

		INIT_LIST_HEAD(&pins[i].list);
		list_add(&(pins[i].list), &jack->pins);
		snd_jack_add_new_kctl(jack->jack, pins[i].pin, pins[i].mask);
	पूर्ण

	/* Update to reflect the last reported status; canned jack
	 * implementations are likely to set their state beक्रमe the
	 * card has an opportunity to associate pins.
	 */
	snd_soc_jack_report(jack, 0, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_jack_add_pins);

/**
 * snd_soc_jack_notअगरier_रेजिस्टर - Register a notअगरier क्रम jack status
 *
 * @jack:  ASoC jack
 * @nb:    Notअगरier block to रेजिस्टर
 *
 * Register क्रम notअगरication of the current status of the jack.  Note
 * that it is not possible to report additional jack events in the
 * callback from the notअगरier, this is पूर्णांकended to support
 * applications such as enabling electrical detection only when a
 * mechanical detection event has occurred.
 */
व्योम snd_soc_jack_notअगरier_रेजिस्टर(काष्ठा snd_soc_jack *jack,
				    काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_रेजिस्टर(&jack->notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_jack_notअगरier_रेजिस्टर);

/**
 * snd_soc_jack_notअगरier_unरेजिस्टर - Unरेजिस्टर a notअगरier क्रम jack status
 *
 * @jack:  ASoC jack
 * @nb:    Notअगरier block to unरेजिस्टर
 *
 * Stop notअगरying क्रम status changes.
 */
व्योम snd_soc_jack_notअगरier_unरेजिस्टर(काष्ठा snd_soc_jack *jack,
				      काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&jack->notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_jack_notअगरier_unरेजिस्टर);

#अगर_घोषित CONFIG_GPIOLIB
/* gpio detect */
अटल व्योम snd_soc_jack_gpio_detect(काष्ठा snd_soc_jack_gpio *gpio)
अणु
	काष्ठा snd_soc_jack *jack = gpio->jack;
	पूर्णांक enable;
	पूर्णांक report;

	enable = gpiod_get_value_cansleep(gpio->desc);
	अगर (gpio->invert)
		enable = !enable;

	अगर (enable)
		report = gpio->report;
	अन्यथा
		report = 0;

	अगर (gpio->jack_status_check)
		report = gpio->jack_status_check(gpio->data);

	snd_soc_jack_report(jack, report, gpio->report);
पूर्ण

/* irq handler क्रम gpio pin */
अटल irqवापस_t gpio_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snd_soc_jack_gpio *gpio = data;
	काष्ठा device *dev = gpio->jack->card->dev;

	trace_snd_soc_jack_irq(gpio->name);

	अगर (device_may_wakeup(dev))
		pm_wakeup_event(dev, gpio->debounce_समय + 50);

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &gpio->work,
			      msecs_to_jअगरfies(gpio->debounce_समय));

	वापस IRQ_HANDLED;
पूर्ण

/* gpio work */
अटल व्योम gpio_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_soc_jack_gpio *gpio;

	gpio = container_of(work, काष्ठा snd_soc_jack_gpio, work.work);
	snd_soc_jack_gpio_detect(gpio);
पूर्ण

अटल पूर्णांक snd_soc_jack_pm_notअगरier(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा snd_soc_jack_gpio *gpio =
			container_of(nb, काष्ठा snd_soc_jack_gpio, pm_notअगरier);

	चयन (action) अणु
	हाल PM_POST_SUSPEND:
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_RESTORE:
		/*
		 * Use workqueue so we करो not have to care about running
		 * concurrently with work triggered by the पूर्णांकerrupt handler.
		 */
		queue_delayed_work(प्रणाली_घातer_efficient_wq, &gpio->work, 0);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम jack_मुक्त_gpios(काष्ठा snd_soc_jack *jack, पूर्णांक count,
			    काष्ठा snd_soc_jack_gpio *gpios)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		gpiod_unexport(gpios[i].desc);
		unरेजिस्टर_pm_notअगरier(&gpios[i].pm_notअगरier);
		मुक्त_irq(gpiod_to_irq(gpios[i].desc), &gpios[i]);
		cancel_delayed_work_sync(&gpios[i].work);
		gpiod_put(gpios[i].desc);
		gpios[i].jack = शून्य;
	पूर्ण
पूर्ण

अटल व्योम jack_devres_मुक्त_gpios(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा jack_gpio_tbl *tbl = res;

	jack_मुक्त_gpios(tbl->jack, tbl->count, tbl->gpios);
पूर्ण

/**
 * snd_soc_jack_add_gpios - Associate GPIO pins with an ASoC jack
 *
 * @jack:  ASoC jack
 * @count: number of pins
 * @gpios: array of gpio pins
 *
 * This function will request gpio, set data direction and request irq
 * क्रम each gpio in the array.
 */
पूर्णांक snd_soc_jack_add_gpios(काष्ठा snd_soc_jack *jack, पूर्णांक count,
			काष्ठा snd_soc_jack_gpio *gpios)
अणु
	पूर्णांक i, ret;
	काष्ठा jack_gpio_tbl *tbl;

	tbl = devres_alloc(jack_devres_मुक्त_gpios, माप(*tbl), GFP_KERNEL);
	अगर (!tbl)
		वापस -ENOMEM;
	tbl->jack = jack;
	tbl->count = count;
	tbl->gpios = gpios;

	क्रम (i = 0; i < count; i++) अणु
		अगर (!gpios[i].name) अणु
			dev_err(jack->card->dev,
				"ASoC: No name for gpio at index %d\n", i);
			ret = -EINVAL;
			जाओ unकरो;
		पूर्ण

		अगर (gpios[i].desc) अणु
			/* Alपढ़ोy have a GPIO descriptor. */
			जाओ got_gpio;
		पूर्ण अन्यथा अगर (gpios[i].gpiod_dev) अणु
			/* Get a GPIO descriptor */
			gpios[i].desc = gpiod_get_index(gpios[i].gpiod_dev,
							gpios[i].name,
							gpios[i].idx, GPIOD_IN);
			अगर (IS_ERR(gpios[i].desc)) अणु
				ret = PTR_ERR(gpios[i].desc);
				dev_err(gpios[i].gpiod_dev,
					"ASoC: Cannot get gpio at index %d: %d",
					i, ret);
				जाओ unकरो;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* legacy GPIO number */
			अगर (!gpio_is_valid(gpios[i].gpio)) अणु
				dev_err(jack->card->dev,
					"ASoC: Invalid gpio %d\n",
					gpios[i].gpio);
				ret = -EINVAL;
				जाओ unकरो;
			पूर्ण

			ret = gpio_request_one(gpios[i].gpio, GPIOF_IN,
					       gpios[i].name);
			अगर (ret)
				जाओ unकरो;

			gpios[i].desc = gpio_to_desc(gpios[i].gpio);
		पूर्ण
got_gpio:
		INIT_DELAYED_WORK(&gpios[i].work, gpio_work);
		gpios[i].jack = jack;

		ret = request_any_context_irq(gpiod_to_irq(gpios[i].desc),
					      gpio_handler,
					      IRQF_TRIGGER_RISING |
					      IRQF_TRIGGER_FALLING,
					      gpios[i].name,
					      &gpios[i]);
		अगर (ret < 0)
			जाओ err;

		अगर (gpios[i].wake) अणु
			ret = irq_set_irq_wake(gpiod_to_irq(gpios[i].desc), 1);
			अगर (ret != 0)
				dev_err(jack->card->dev,
					"ASoC: Failed to mark GPIO at index %d as wake source: %d\n",
					i, ret);
		पूर्ण

		/*
		 * Register PM notअगरier so we करो not miss state transitions
		 * happening जबतक प्रणाली is asleep.
		 */
		gpios[i].pm_notअगरier.notअगरier_call = snd_soc_jack_pm_notअगरier;
		रेजिस्टर_pm_notअगरier(&gpios[i].pm_notअगरier);

		/* Expose GPIO value over sysfs क्रम diagnostic purposes */
		gpiod_export(gpios[i].desc, false);

		/* Update initial jack status */
		schedule_delayed_work(&gpios[i].work,
				      msecs_to_jअगरfies(gpios[i].debounce_समय));
	पूर्ण

	devres_add(jack->card->dev, tbl);
	वापस 0;

err:
	gpio_मुक्त(gpios[i].gpio);
unकरो:
	jack_मुक्त_gpios(jack, i, gpios);
	devres_मुक्त(tbl);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_jack_add_gpios);

/**
 * snd_soc_jack_add_gpiods - Associate GPIO descriptor pins with an ASoC jack
 *
 * @gpiod_dev: GPIO consumer device
 * @jack:      ASoC jack
 * @count:     number of pins
 * @gpios:     array of gpio pins
 *
 * This function will request gpio, set data direction and request irq
 * क्रम each gpio in the array.
 */
पूर्णांक snd_soc_jack_add_gpiods(काष्ठा device *gpiod_dev,
			    काष्ठा snd_soc_jack *jack,
			    पूर्णांक count, काष्ठा snd_soc_jack_gpio *gpios)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		gpios[i].gpiod_dev = gpiod_dev;

	वापस snd_soc_jack_add_gpios(jack, count, gpios);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_jack_add_gpiods);

/**
 * snd_soc_jack_मुक्त_gpios - Release GPIO pins' resources of an ASoC jack
 *
 * @jack:  ASoC jack
 * @count: number of pins
 * @gpios: array of gpio pins
 *
 * Release gpio and irq resources क्रम gpio pins associated with an ASoC jack.
 */
व्योम snd_soc_jack_मुक्त_gpios(काष्ठा snd_soc_jack *jack, पूर्णांक count,
			काष्ठा snd_soc_jack_gpio *gpios)
अणु
	jack_मुक्त_gpios(jack, count, gpios);
	devres_destroy(jack->card->dev, jack_devres_मुक्त_gpios, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_jack_मुक्त_gpios);
#पूर्ण_अगर	/* CONFIG_GPIOLIB */
