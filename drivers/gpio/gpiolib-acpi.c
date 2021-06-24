<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACPI helpers क्रम GPIO API
 *
 * Copyright (C) 2012, Intel Corporation
 * Authors: Mathias Nyman <mathias.nyman@linux.पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/dmi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/export.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "gpiolib.h"
#समावेश "gpiolib-acpi.h"

अटल पूर्णांक run_edge_events_on_boot = -1;
module_param(run_edge_events_on_boot, पूर्णांक, 0444);
MODULE_PARM_DESC(run_edge_events_on_boot,
		 "Run edge _AEI event-handlers at boot: 0=no, 1=yes, -1=auto");

अटल अक्षर *ignore_wake;
module_param(ignore_wake, अक्षरp, 0444);
MODULE_PARM_DESC(ignore_wake,
		 "controller@pin combos on which to ignore the ACPI wake flag "
		 "ignore_wake=controller@pin[,controller@pin[,...]]");

काष्ठा acpi_gpiolib_dmi_quirk अणु
	bool no_edge_events_on_boot;
	अक्षर *ignore_wake;
पूर्ण;

/**
 * काष्ठा acpi_gpio_event - ACPI GPIO event handler data
 *
 * @node:	  list-entry of the events list of the काष्ठा acpi_gpio_chip
 * @handle:	  handle of ACPI method to execute when the IRQ triggers
 * @handler:	  handler function to pass to request_irq() when requesting the IRQ
 * @pin:	  GPIO pin number on the काष्ठा gpio_chip
 * @irq:	  Linux IRQ number क्रम the event, क्रम request_irq() / मुक्त_irq()
 * @irqflags:	  flags to pass to request_irq() when requesting the IRQ
 * @irq_is_wake:  If the ACPI flags indicate the IRQ is a wakeup source
 * @irq_requested:True अगर request_irq() has been करोne
 * @desc:	  काष्ठा gpio_desc क्रम the GPIO pin क्रम this event
 */
काष्ठा acpi_gpio_event अणु
	काष्ठा list_head node;
	acpi_handle handle;
	irq_handler_t handler;
	अचिन्हित पूर्णांक pin;
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ irqflags;
	bool irq_is_wake;
	bool irq_requested;
	काष्ठा gpio_desc *desc;
पूर्ण;

काष्ठा acpi_gpio_connection अणु
	काष्ठा list_head node;
	अचिन्हित पूर्णांक pin;
	काष्ठा gpio_desc *desc;
पूर्ण;

काष्ठा acpi_gpio_chip अणु
	/*
	 * ACPICA requires that the first field of the context parameter
	 * passed to acpi_install_address_space_handler() is large enough
	 * to hold काष्ठा acpi_connection_info.
	 */
	काष्ठा acpi_connection_info conn_info;
	काष्ठा list_head conns;
	काष्ठा mutex conn_lock;
	काष्ठा gpio_chip *chip;
	काष्ठा list_head events;
	काष्ठा list_head deferred_req_irqs_list_entry;
पूर्ण;

/*
 * For GPIO chips which call acpi_gpiochip_request_पूर्णांकerrupts() beक्रमe late_init
 * (so builtin drivers) we रेजिस्टर the ACPI GpioInt IRQ handlers from a
 * late_initcall_sync() handler, so that other builtin drivers can रेजिस्टर their
 * OpRegions beक्रमe the event handlers can run. This list contains GPIO chips
 * क्रम which the acpi_gpiochip_request_irqs() call has been deferred.
 */
अटल DEFINE_MUTEX(acpi_gpio_deferred_req_irqs_lock);
अटल LIST_HEAD(acpi_gpio_deferred_req_irqs_list);
अटल bool acpi_gpio_deferred_req_irqs_करोne;

अटल पूर्णांक acpi_gpiochip_find(काष्ठा gpio_chip *gc, व्योम *data)
अणु
	अगर (!gc->parent)
		वापस false;

	वापस ACPI_HANDLE(gc->parent) == data;
पूर्ण

/**
 * acpi_get_gpiod() - Translate ACPI GPIO pin to GPIO descriptor usable with GPIO API
 * @path:	ACPI GPIO controller full path name, (e.g. "\\_SB.GPO1")
 * @pin:	ACPI GPIO pin number (0-based, controller-relative)
 *
 * Return: GPIO descriptor to use with Linux generic GPIO API, or ERR_PTR
 * error value. Specअगरically वापसs %-EPROBE_DEFER अगर the referenced GPIO
 * controller करोes not have GPIO chip रेजिस्टरed at the moment. This is to
 * support probe deferral.
 */
अटल काष्ठा gpio_desc *acpi_get_gpiod(अक्षर *path, पूर्णांक pin)
अणु
	काष्ठा gpio_chip *chip;
	acpi_handle handle;
	acpi_status status;

	status = acpi_get_handle(शून्य, path, &handle);
	अगर (ACPI_FAILURE(status))
		वापस ERR_PTR(-ENODEV);

	chip = gpiochip_find(handle, acpi_gpiochip_find);
	अगर (!chip)
		वापस ERR_PTR(-EPROBE_DEFER);

	वापस gpiochip_get_desc(chip, pin);
पूर्ण

अटल irqवापस_t acpi_gpio_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा acpi_gpio_event *event = data;

	acpi_evaluate_object(event->handle, शून्य, शून्य, शून्य);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t acpi_gpio_irq_handler_evt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा acpi_gpio_event *event = data;

	acpi_execute_simple_method(event->handle, शून्य, event->pin);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम acpi_gpio_chip_dh(acpi_handle handle, व्योम *data)
अणु
	/* The address of this function is used as a key. */
पूर्ण

bool acpi_gpio_get_irq_resource(काष्ठा acpi_resource *ares,
				काष्ठा acpi_resource_gpio **agpio)
अणु
	काष्ठा acpi_resource_gpio *gpio;

	अगर (ares->type != ACPI_RESOURCE_TYPE_GPIO)
		वापस false;

	gpio = &ares->data.gpio;
	अगर (gpio->connection_type != ACPI_RESOURCE_GPIO_TYPE_INT)
		वापस false;

	*agpio = gpio;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_gpio_get_irq_resource);

अटल व्योम acpi_gpiochip_request_irq(काष्ठा acpi_gpio_chip *acpi_gpio,
				      काष्ठा acpi_gpio_event *event)
अणु
	पूर्णांक ret, value;

	ret = request_thपढ़ोed_irq(event->irq, शून्य, event->handler,
				   event->irqflags | IRQF_ONESHOT, "ACPI:Event", event);
	अगर (ret) अणु
		dev_err(acpi_gpio->chip->parent,
			"Failed to setup interrupt handler for %d\n",
			event->irq);
		वापस;
	पूर्ण

	अगर (event->irq_is_wake)
		enable_irq_wake(event->irq);

	event->irq_requested = true;

	/* Make sure we trigger the initial state of edge-triggered IRQs */
	अगर (run_edge_events_on_boot &&
	    (event->irqflags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))) अणु
		value = gpiod_get_raw_value_cansleep(event->desc);
		अगर (((event->irqflags & IRQF_TRIGGER_RISING) && value == 1) ||
		    ((event->irqflags & IRQF_TRIGGER_FALLING) && value == 0))
			event->handler(event->irq, event);
	पूर्ण
पूर्ण

अटल व्योम acpi_gpiochip_request_irqs(काष्ठा acpi_gpio_chip *acpi_gpio)
अणु
	काष्ठा acpi_gpio_event *event;

	list_क्रम_each_entry(event, &acpi_gpio->events, node)
		acpi_gpiochip_request_irq(acpi_gpio, event);
पूर्ण

अटल क्रमागत gpiod_flags
acpi_gpio_to_gpiod_flags(स्थिर काष्ठा acpi_resource_gpio *agpio, पूर्णांक polarity)
अणु
	/* GpioInt() implies input configuration */
	अगर (agpio->connection_type == ACPI_RESOURCE_GPIO_TYPE_INT)
		वापस GPIOD_IN;

	चयन (agpio->io_restriction) अणु
	हाल ACPI_IO_RESTRICT_INPUT:
		वापस GPIOD_IN;
	हाल ACPI_IO_RESTRICT_OUTPUT:
		/*
		 * ACPI GPIO resources करोn't contain an initial value क्रम the
		 * GPIO. Thereक्रमe we deduce that value from the pull field
		 * and the polarity instead. If the pin is pulled up we assume
		 * शेष to be high, अगर it is pulled करोwn we assume शेष
		 * to be low, otherwise we leave pin untouched. For active low
		 * polarity values will be चयनed. See also
		 * Documentation/firmware-guide/acpi/gpio-properties.rst.
		 */
		चयन (agpio->pin_config) अणु
		हाल ACPI_PIN_CONFIG_PULLUP:
			वापस polarity == GPIO_ACTIVE_LOW ? GPIOD_OUT_LOW : GPIOD_OUT_HIGH;
		हाल ACPI_PIN_CONFIG_PULLDOWN:
			वापस polarity == GPIO_ACTIVE_LOW ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Assume that the BIOS has configured the direction and pull
	 * accordingly.
	 */
	वापस GPIOD_ASIS;
पूर्ण

अटल काष्ठा gpio_desc *acpi_request_own_gpiod(काष्ठा gpio_chip *chip,
						काष्ठा acpi_resource_gpio *agpio,
						अचिन्हित पूर्णांक index,
						स्थिर अक्षर *label)
अणु
	पूर्णांक polarity = GPIO_ACTIVE_HIGH;
	क्रमागत gpiod_flags flags = acpi_gpio_to_gpiod_flags(agpio, polarity);
	अचिन्हित पूर्णांक pin = agpio->pin_table[index];
	काष्ठा gpio_desc *desc;
	पूर्णांक ret;

	desc = gpiochip_request_own_desc(chip, pin, label, polarity, flags);
	अगर (IS_ERR(desc))
		वापस desc;

	ret = gpio_set_debounce_समयout(desc, agpio->debounce_समयout);
	अगर (ret)
		gpiochip_मुक्त_own_desc(desc);

	वापस ret ? ERR_PTR(ret) : desc;
पूर्ण

अटल bool acpi_gpio_in_ignore_list(स्थिर अक्षर *controller_in, पूर्णांक pin_in)
अणु
	स्थिर अक्षर *controller, *pin_str;
	पूर्णांक len, pin;
	अक्षर *endp;

	controller = ignore_wake;
	जबतक (controller) अणु
		pin_str = म_अक्षर(controller, '@');
		अगर (!pin_str)
			जाओ err;

		len = pin_str - controller;
		अगर (len == म_माप(controller_in) &&
		    म_भेदन(controller, controller_in, len) == 0) अणु
			pin = simple_म_से_अदीर्घ(pin_str + 1, &endp, 10);
			अगर (*endp != 0 && *endp != ',')
				जाओ err;

			अगर (pin == pin_in)
				वापस true;
		पूर्ण

		controller = म_अक्षर(controller, ',');
		अगर (controller)
			controller++;
	पूर्ण

	वापस false;
err:
	pr_err_once("Error invalid value for gpiolib_acpi.ignore_wake: %s\n",
		    ignore_wake);
	वापस false;
पूर्ण

अटल bool acpi_gpio_irq_is_wake(काष्ठा device *parent,
				  काष्ठा acpi_resource_gpio *agpio)
अणु
	पूर्णांक pin = agpio->pin_table[0];

	अगर (agpio->wake_capable != ACPI_WAKE_CAPABLE)
		वापस false;

	अगर (acpi_gpio_in_ignore_list(dev_name(parent), pin)) अणु
		dev_info(parent, "Ignoring wakeup on pin %d\n", pin);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Always वापसs AE_OK so that we keep looping over the resources */
अटल acpi_status acpi_gpiochip_alloc_event(काष्ठा acpi_resource *ares,
					     व्योम *context)
अणु
	काष्ठा acpi_gpio_chip *acpi_gpio = context;
	काष्ठा gpio_chip *chip = acpi_gpio->chip;
	काष्ठा acpi_resource_gpio *agpio;
	acpi_handle handle, evt_handle;
	काष्ठा acpi_gpio_event *event;
	irq_handler_t handler = शून्य;
	काष्ठा gpio_desc *desc;
	पूर्णांक ret, pin, irq;

	अगर (!acpi_gpio_get_irq_resource(ares, &agpio))
		वापस AE_OK;

	handle = ACPI_HANDLE(chip->parent);
	pin = agpio->pin_table[0];

	अगर (pin <= 255) अणु
		अक्षर ev_name[5];
		प्र_लिखो(ev_name, "_%c%02hhX",
			agpio->triggering == ACPI_EDGE_SENSITIVE ? 'E' : 'L',
			pin);
		अगर (ACPI_SUCCESS(acpi_get_handle(handle, ev_name, &evt_handle)))
			handler = acpi_gpio_irq_handler;
	पूर्ण
	अगर (!handler) अणु
		अगर (ACPI_SUCCESS(acpi_get_handle(handle, "_EVT", &evt_handle)))
			handler = acpi_gpio_irq_handler_evt;
	पूर्ण
	अगर (!handler)
		वापस AE_OK;

	desc = acpi_request_own_gpiod(chip, agpio, 0, "ACPI:Event");
	अगर (IS_ERR(desc)) अणु
		dev_err(chip->parent,
			"Failed to request GPIO for pin 0x%04X, err %ld\n",
			pin, PTR_ERR(desc));
		वापस AE_OK;
	पूर्ण

	ret = gpiochip_lock_as_irq(chip, pin);
	अगर (ret) अणु
		dev_err(chip->parent,
			"Failed to lock GPIO pin 0x%04X as interrupt, err %d\n",
			pin, ret);
		जाओ fail_मुक्त_desc;
	पूर्ण

	irq = gpiod_to_irq(desc);
	अगर (irq < 0) अणु
		dev_err(chip->parent,
			"Failed to translate GPIO pin 0x%04X to IRQ, err %d\n",
			pin, irq);
		जाओ fail_unlock_irq;
	पूर्ण

	event = kzalloc(माप(*event), GFP_KERNEL);
	अगर (!event)
		जाओ fail_unlock_irq;

	event->irqflags = IRQF_ONESHOT;
	अगर (agpio->triggering == ACPI_LEVEL_SENSITIVE) अणु
		अगर (agpio->polarity == ACPI_ACTIVE_HIGH)
			event->irqflags |= IRQF_TRIGGER_HIGH;
		अन्यथा
			event->irqflags |= IRQF_TRIGGER_LOW;
	पूर्ण अन्यथा अणु
		चयन (agpio->polarity) अणु
		हाल ACPI_ACTIVE_HIGH:
			event->irqflags |= IRQF_TRIGGER_RISING;
			अवरोध;
		हाल ACPI_ACTIVE_LOW:
			event->irqflags |= IRQF_TRIGGER_FALLING;
			अवरोध;
		शेष:
			event->irqflags |= IRQF_TRIGGER_RISING |
					   IRQF_TRIGGER_FALLING;
			अवरोध;
		पूर्ण
	पूर्ण

	event->handle = evt_handle;
	event->handler = handler;
	event->irq = irq;
	event->irq_is_wake = acpi_gpio_irq_is_wake(chip->parent, agpio);
	event->pin = pin;
	event->desc = desc;

	list_add_tail(&event->node, &acpi_gpio->events);

	वापस AE_OK;

fail_unlock_irq:
	gpiochip_unlock_as_irq(chip, pin);
fail_मुक्त_desc:
	gpiochip_मुक्त_own_desc(desc);

	वापस AE_OK;
पूर्ण

/**
 * acpi_gpiochip_request_पूर्णांकerrupts() - Register isr क्रम gpio chip ACPI events
 * @chip:      GPIO chip
 *
 * ACPI5 platक्रमms can use GPIO संकेतed ACPI events. These GPIO पूर्णांकerrupts are
 * handled by ACPI event methods which need to be called from the GPIO
 * chip's पूर्णांकerrupt handler. acpi_gpiochip_request_पूर्णांकerrupts() finds out which
 * GPIO pins have ACPI event methods and assigns पूर्णांकerrupt handlers that calls
 * the ACPI event methods क्रम those pins.
 */
व्योम acpi_gpiochip_request_पूर्णांकerrupts(काष्ठा gpio_chip *chip)
अणु
	काष्ठा acpi_gpio_chip *acpi_gpio;
	acpi_handle handle;
	acpi_status status;
	bool defer;

	अगर (!chip->parent || !chip->to_irq)
		वापस;

	handle = ACPI_HANDLE(chip->parent);
	अगर (!handle)
		वापस;

	status = acpi_get_data(handle, acpi_gpio_chip_dh, (व्योम **)&acpi_gpio);
	अगर (ACPI_FAILURE(status))
		वापस;

	acpi_walk_resources(handle, "_AEI",
			    acpi_gpiochip_alloc_event, acpi_gpio);

	mutex_lock(&acpi_gpio_deferred_req_irqs_lock);
	defer = !acpi_gpio_deferred_req_irqs_करोne;
	अगर (defer)
		list_add(&acpi_gpio->deferred_req_irqs_list_entry,
			 &acpi_gpio_deferred_req_irqs_list);
	mutex_unlock(&acpi_gpio_deferred_req_irqs_lock);

	अगर (defer)
		वापस;

	acpi_gpiochip_request_irqs(acpi_gpio);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_gpiochip_request_पूर्णांकerrupts);

/**
 * acpi_gpiochip_मुक्त_पूर्णांकerrupts() - Free GPIO ACPI event पूर्णांकerrupts.
 * @chip:      GPIO chip
 *
 * Free पूर्णांकerrupts associated with GPIO ACPI event method क्रम the given
 * GPIO chip.
 */
व्योम acpi_gpiochip_मुक्त_पूर्णांकerrupts(काष्ठा gpio_chip *chip)
अणु
	काष्ठा acpi_gpio_chip *acpi_gpio;
	काष्ठा acpi_gpio_event *event, *ep;
	acpi_handle handle;
	acpi_status status;

	अगर (!chip->parent || !chip->to_irq)
		वापस;

	handle = ACPI_HANDLE(chip->parent);
	अगर (!handle)
		वापस;

	status = acpi_get_data(handle, acpi_gpio_chip_dh, (व्योम **)&acpi_gpio);
	अगर (ACPI_FAILURE(status))
		वापस;

	mutex_lock(&acpi_gpio_deferred_req_irqs_lock);
	अगर (!list_empty(&acpi_gpio->deferred_req_irqs_list_entry))
		list_del_init(&acpi_gpio->deferred_req_irqs_list_entry);
	mutex_unlock(&acpi_gpio_deferred_req_irqs_lock);

	list_क्रम_each_entry_safe_reverse(event, ep, &acpi_gpio->events, node) अणु
		अगर (event->irq_requested) अणु
			अगर (event->irq_is_wake)
				disable_irq_wake(event->irq);

			मुक्त_irq(event->irq, event);
		पूर्ण

		gpiochip_unlock_as_irq(chip, event->pin);
		gpiochip_मुक्त_own_desc(event->desc);
		list_del(&event->node);
		kमुक्त(event);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(acpi_gpiochip_मुक्त_पूर्णांकerrupts);

पूर्णांक acpi_dev_add_driver_gpios(काष्ठा acpi_device *adev,
			      स्थिर काष्ठा acpi_gpio_mapping *gpios)
अणु
	अगर (adev && gpios) अणु
		adev->driver_gpios = gpios;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_add_driver_gpios);

व्योम acpi_dev_हटाओ_driver_gpios(काष्ठा acpi_device *adev)
अणु
	अगर (adev)
		adev->driver_gpios = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_हटाओ_driver_gpios);

अटल व्योम devm_acpi_dev_release_driver_gpios(काष्ठा device *dev, व्योम *res)
अणु
	acpi_dev_हटाओ_driver_gpios(ACPI_COMPANION(dev));
पूर्ण

पूर्णांक devm_acpi_dev_add_driver_gpios(काष्ठा device *dev,
				   स्थिर काष्ठा acpi_gpio_mapping *gpios)
अणु
	व्योम *res;
	पूर्णांक ret;

	res = devres_alloc(devm_acpi_dev_release_driver_gpios, 0, GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	ret = acpi_dev_add_driver_gpios(ACPI_COMPANION(dev), gpios);
	अगर (ret) अणु
		devres_मुक्त(res);
		वापस ret;
	पूर्ण
	devres_add(dev, res);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_acpi_dev_add_driver_gpios);

व्योम devm_acpi_dev_हटाओ_driver_gpios(काष्ठा device *dev)
अणु
	WARN_ON(devres_release(dev, devm_acpi_dev_release_driver_gpios, शून्य, शून्य));
पूर्ण
EXPORT_SYMBOL_GPL(devm_acpi_dev_हटाओ_driver_gpios);

अटल bool acpi_get_driver_gpio_data(काष्ठा acpi_device *adev,
				      स्थिर अक्षर *name, पूर्णांक index,
				      काष्ठा fwnode_reference_args *args,
				      अचिन्हित पूर्णांक *quirks)
अणु
	स्थिर काष्ठा acpi_gpio_mapping *gm;

	अगर (!adev->driver_gpios)
		वापस false;

	क्रम (gm = adev->driver_gpios; gm->name; gm++)
		अगर (!म_भेद(name, gm->name) && gm->data && index < gm->size) अणु
			स्थिर काष्ठा acpi_gpio_params *par = gm->data + index;

			args->fwnode = acpi_fwnode_handle(adev);
			args->args[0] = par->crs_entry_index;
			args->args[1] = par->line_index;
			args->args[2] = par->active_low;
			args->nargs = 3;

			*quirks = gm->quirks;
			वापस true;
		पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
__acpi_gpio_update_gpiod_flags(क्रमागत gpiod_flags *flags, क्रमागत gpiod_flags update)
अणु
	स्थिर क्रमागत gpiod_flags mask =
		GPIOD_FLAGS_BIT_सूची_SET | GPIOD_FLAGS_BIT_सूची_OUT |
		GPIOD_FLAGS_BIT_सूची_VAL;
	पूर्णांक ret = 0;

	/*
	 * Check अगर the BIOS has IoRestriction with explicitly set direction
	 * and update @flags accordingly. Otherwise use whatever caller asked
	 * क्रम.
	 */
	अगर (update & GPIOD_FLAGS_BIT_सूची_SET) अणु
		क्रमागत gpiod_flags dअगरf = *flags ^ update;

		/*
		 * Check अगर caller supplied incompatible GPIO initialization
		 * flags.
		 *
		 * Return %-EINVAL to notअगरy that firmware has dअगरferent
		 * settings and we are going to use them.
		 */
		अगर (((*flags & GPIOD_FLAGS_BIT_सूची_SET) && (dअगरf & GPIOD_FLAGS_BIT_सूची_OUT)) ||
		    ((*flags & GPIOD_FLAGS_BIT_सूची_OUT) && (dअगरf & GPIOD_FLAGS_BIT_सूची_VAL)))
			ret = -EINVAL;
		*flags = (*flags & ~mask) | (update & mask);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
acpi_gpio_update_gpiod_flags(क्रमागत gpiod_flags *flags, काष्ठा acpi_gpio_info *info)
अणु
	काष्ठा device *dev = &info->adev->dev;
	क्रमागत gpiod_flags old = *flags;
	पूर्णांक ret;

	ret = __acpi_gpio_update_gpiod_flags(&old, info->flags);
	अगर (info->quirks & ACPI_GPIO_QUIRK_NO_IO_RESTRICTION) अणु
		अगर (ret)
			dev_warn(dev, FW_BUG "GPIO not in correct mode, fixing\n");
	पूर्ण अन्यथा अणु
		अगर (ret)
			dev_dbg(dev, "Override GPIO initialization flags\n");
		*flags = old;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक acpi_gpio_update_gpiod_lookup_flags(अचिन्हित दीर्घ *lookupflags,
					काष्ठा acpi_gpio_info *info)
अणु
	चयन (info->pin_config) अणु
	हाल ACPI_PIN_CONFIG_PULLUP:
		*lookupflags |= GPIO_PULL_UP;
		अवरोध;
	हाल ACPI_PIN_CONFIG_PULLDOWN:
		*lookupflags |= GPIO_PULL_DOWN;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (info->polarity == GPIO_ACTIVE_LOW)
		*lookupflags |= GPIO_ACTIVE_LOW;

	वापस 0;
पूर्ण

काष्ठा acpi_gpio_lookup अणु
	काष्ठा acpi_gpio_info info;
	पूर्णांक index;
	u16 pin_index;
	bool active_low;
	काष्ठा gpio_desc *desc;
	पूर्णांक n;
पूर्ण;

अटल पूर्णांक acpi_populate_gpio_lookup(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा acpi_gpio_lookup *lookup = data;

	अगर (ares->type != ACPI_RESOURCE_TYPE_GPIO)
		वापस 1;

	अगर (!lookup->desc) अणु
		स्थिर काष्ठा acpi_resource_gpio *agpio = &ares->data.gpio;
		bool gpioपूर्णांक = agpio->connection_type == ACPI_RESOURCE_GPIO_TYPE_INT;
		काष्ठा gpio_desc *desc;
		u16 pin_index;

		अगर (lookup->info.quirks & ACPI_GPIO_QUIRK_ONLY_GPIOIO && gpioपूर्णांक)
			lookup->index++;

		अगर (lookup->n++ != lookup->index)
			वापस 1;

		pin_index = lookup->pin_index;
		अगर (pin_index >= agpio->pin_table_length)
			वापस 1;

		अगर (lookup->info.quirks & ACPI_GPIO_QUIRK_ABSOLUTE_NUMBER)
			desc = gpio_to_desc(agpio->pin_table[pin_index]);
		अन्यथा
			desc = acpi_get_gpiod(agpio->resource_source.string_ptr,
					      agpio->pin_table[pin_index]);
		lookup->desc = desc;
		lookup->info.pin_config = agpio->pin_config;
		lookup->info.debounce = agpio->debounce_समयout;
		lookup->info.gpioपूर्णांक = gpioपूर्णांक;

		/*
		 * Polarity and triggering are only specअगरied क्रम GpioInt
		 * resource.
		 * Note: we expect here:
		 * - ACPI_ACTIVE_LOW == GPIO_ACTIVE_LOW
		 * - ACPI_ACTIVE_HIGH == GPIO_ACTIVE_HIGH
		 */
		अगर (lookup->info.gpioपूर्णांक) अणु
			lookup->info.polarity = agpio->polarity;
			lookup->info.triggering = agpio->triggering;
		पूर्ण अन्यथा अणु
			lookup->info.polarity = lookup->active_low;
		पूर्ण

		lookup->info.flags = acpi_gpio_to_gpiod_flags(agpio, lookup->info.polarity);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक acpi_gpio_resource_lookup(काष्ठा acpi_gpio_lookup *lookup,
				     काष्ठा acpi_gpio_info *info)
अणु
	काष्ठा acpi_device *adev = lookup->info.adev;
	काष्ठा list_head res_list;
	पूर्णांक ret;

	INIT_LIST_HEAD(&res_list);

	ret = acpi_dev_get_resources(adev, &res_list,
				     acpi_populate_gpio_lookup,
				     lookup);
	अगर (ret < 0)
		वापस ret;

	acpi_dev_मुक्त_resource_list(&res_list);

	अगर (!lookup->desc)
		वापस -ENOENT;

	अगर (info)
		*info = lookup->info;
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_gpio_property_lookup(काष्ठा fwnode_handle *fwnode,
				     स्थिर अक्षर *propname, पूर्णांक index,
				     काष्ठा acpi_gpio_lookup *lookup)
अणु
	काष्ठा fwnode_reference_args args;
	अचिन्हित पूर्णांक quirks = 0;
	पूर्णांक ret;

	स_रखो(&args, 0, माप(args));
	ret = __acpi_node_get_property_reference(fwnode, propname, index, 3,
						 &args);
	अगर (ret) अणु
		काष्ठा acpi_device *adev = to_acpi_device_node(fwnode);

		अगर (!adev)
			वापस ret;

		अगर (!acpi_get_driver_gpio_data(adev, propname, index, &args,
					       &quirks))
			वापस ret;
	पूर्ण
	/*
	 * The property was found and resolved, so need to lookup the GPIO based
	 * on वापसed args.
	 */
	अगर (!to_acpi_device_node(args.fwnode))
		वापस -EINVAL;
	अगर (args.nargs != 3)
		वापस -EPROTO;

	lookup->index = args.args[0];
	lookup->pin_index = args.args[1];
	lookup->active_low = !!args.args[2];

	lookup->info.adev = to_acpi_device_node(args.fwnode);
	lookup->info.quirks = quirks;

	वापस 0;
पूर्ण

/**
 * acpi_get_gpiod_by_index() - get a GPIO descriptor from device resources
 * @adev: poपूर्णांकer to a ACPI device to get GPIO from
 * @propname: Property name of the GPIO (optional)
 * @index: index of GpioIo/GpioInt resource (starting from %0)
 * @info: info poपूर्णांकer to fill in (optional)
 *
 * Function goes through ACPI resources क्रम @adev and based on @index looks
 * up a GpioIo/GpioInt resource, translates it to the Linux GPIO descriptor,
 * and वापसs it. @index matches GpioIo/GpioInt resources only so अगर there
 * are total %3 GPIO resources, the index goes from %0 to %2.
 *
 * If @propname is specअगरied the GPIO is looked using device property. In
 * that हाल @index is used to select the GPIO entry in the property value
 * (in हाल of multiple).
 *
 * If the GPIO cannot be translated or there is an error, an ERR_PTR is
 * वापसed.
 *
 * Note: अगर the GPIO resource has multiple entries in the pin list, this
 * function only वापसs the first.
 */
अटल काष्ठा gpio_desc *acpi_get_gpiod_by_index(काष्ठा acpi_device *adev,
					  स्थिर अक्षर *propname, पूर्णांक index,
					  काष्ठा acpi_gpio_info *info)
अणु
	काष्ठा acpi_gpio_lookup lookup;
	पूर्णांक ret;

	अगर (!adev)
		वापस ERR_PTR(-ENODEV);

	स_रखो(&lookup, 0, माप(lookup));
	lookup.index = index;

	अगर (propname) अणु
		dev_dbg(&adev->dev, "GPIO: looking up %s\n", propname);

		ret = acpi_gpio_property_lookup(acpi_fwnode_handle(adev),
						propname, index, &lookup);
		अगर (ret)
			वापस ERR_PTR(ret);

		dev_dbg(&adev->dev, "GPIO: _DSD returned %s %d %u %u\n",
			dev_name(&lookup.info.adev->dev), lookup.index,
			lookup.pin_index, lookup.active_low);
	पूर्ण अन्यथा अणु
		dev_dbg(&adev->dev, "GPIO: looking up %d in _CRS\n", index);
		lookup.info.adev = adev;
	पूर्ण

	ret = acpi_gpio_resource_lookup(&lookup, info);
	वापस ret ? ERR_PTR(ret) : lookup.desc;
पूर्ण

अटल bool acpi_can_fallback_to_crs(काष्ठा acpi_device *adev,
				     स्थिर अक्षर *con_id)
अणु
	/* Never allow fallback अगर the device has properties */
	अगर (acpi_dev_has_props(adev) || adev->driver_gpios)
		वापस false;

	वापस con_id == शून्य;
पूर्ण

काष्ठा gpio_desc *acpi_find_gpio(काष्ठा device *dev,
				 स्थिर अक्षर *con_id,
				 अचिन्हित पूर्णांक idx,
				 क्रमागत gpiod_flags *dflags,
				 अचिन्हित दीर्घ *lookupflags)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	काष्ठा acpi_gpio_info info;
	काष्ठा gpio_desc *desc;
	अक्षर propname[32];
	पूर्णांक i;

	/* Try first from _DSD */
	क्रम (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) अणु
		अगर (con_id) अणु
			snम_लिखो(propname, माप(propname), "%s-%s",
				 con_id, gpio_suffixes[i]);
		पूर्ण अन्यथा अणु
			snम_लिखो(propname, माप(propname), "%s",
				 gpio_suffixes[i]);
		पूर्ण

		desc = acpi_get_gpiod_by_index(adev, propname, idx, &info);
		अगर (!IS_ERR(desc))
			अवरोध;
		अगर (PTR_ERR(desc) == -EPROBE_DEFER)
			वापस ERR_CAST(desc);
	पूर्ण

	/* Then from plain _CRS GPIOs */
	अगर (IS_ERR(desc)) अणु
		अगर (!acpi_can_fallback_to_crs(adev, con_id))
			वापस ERR_PTR(-ENOENT);

		desc = acpi_get_gpiod_by_index(adev, शून्य, idx, &info);
		अगर (IS_ERR(desc))
			वापस desc;
	पूर्ण

	अगर (info.gpioपूर्णांक &&
	    (*dflags == GPIOD_OUT_LOW || *dflags == GPIOD_OUT_HIGH)) अणु
		dev_dbg(dev, "refusing GpioInt() entry when doing GPIOD_OUT_* lookup\n");
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	acpi_gpio_update_gpiod_flags(dflags, &info);
	acpi_gpio_update_gpiod_lookup_flags(lookupflags, &info);
	वापस desc;
पूर्ण

/**
 * acpi_node_get_gpiod() - get a GPIO descriptor from ACPI resources
 * @fwnode: poपूर्णांकer to an ACPI firmware node to get the GPIO inक्रमmation from
 * @propname: Property name of the GPIO
 * @index: index of GpioIo/GpioInt resource (starting from %0)
 * @info: info poपूर्णांकer to fill in (optional)
 *
 * If @fwnode is an ACPI device object, call acpi_get_gpiod_by_index() क्रम it.
 * Otherwise (i.e. it is a data-only non-device object), use the property-based
 * GPIO lookup to get to the GPIO resource with the relevant inक्रमmation and use
 * that to obtain the GPIO descriptor to वापस.
 *
 * If the GPIO cannot be translated or there is an error an ERR_PTR is
 * वापसed.
 */
काष्ठा gpio_desc *acpi_node_get_gpiod(काष्ठा fwnode_handle *fwnode,
				      स्थिर अक्षर *propname, पूर्णांक index,
				      काष्ठा acpi_gpio_info *info)
अणु
	काष्ठा acpi_gpio_lookup lookup;
	काष्ठा acpi_device *adev;
	पूर्णांक ret;

	adev = to_acpi_device_node(fwnode);
	अगर (adev)
		वापस acpi_get_gpiod_by_index(adev, propname, index, info);

	अगर (!is_acpi_data_node(fwnode))
		वापस ERR_PTR(-ENODEV);

	अगर (!propname)
		वापस ERR_PTR(-EINVAL);

	स_रखो(&lookup, 0, माप(lookup));
	lookup.index = index;

	ret = acpi_gpio_property_lookup(fwnode, propname, index, &lookup);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = acpi_gpio_resource_lookup(&lookup, info);
	वापस ret ? ERR_PTR(ret) : lookup.desc;
पूर्ण

/**
 * acpi_dev_gpio_irq_get_by() - Find GpioInt and translate it to Linux IRQ number
 * @adev: poपूर्णांकer to a ACPI device to get IRQ from
 * @name: optional name of GpioInt resource
 * @index: index of GpioInt resource (starting from %0)
 *
 * If the device has one or more GpioInt resources, this function can be
 * used to translate from the GPIO offset in the resource to the Linux IRQ
 * number.
 *
 * The function is idempotent, though each समय it runs it will configure GPIO
 * pin direction according to the flags in GpioInt resource.
 *
 * The function takes optional @name parameter. If the resource has a property
 * name, then only those will be taken पूर्णांकo account.
 *
 * Return: Linux IRQ number (> %0) on success, negative त्रुटि_सं on failure.
 */
पूर्णांक acpi_dev_gpio_irq_get_by(काष्ठा acpi_device *adev, स्थिर अक्षर *name, पूर्णांक index)
अणु
	पूर्णांक idx, i;
	अचिन्हित पूर्णांक irq_flags;
	पूर्णांक ret;

	क्रम (i = 0, idx = 0; idx <= index; i++) अणु
		काष्ठा acpi_gpio_info info;
		काष्ठा gpio_desc *desc;

		desc = acpi_get_gpiod_by_index(adev, name, i, &info);

		/* Ignore -EPROBE_DEFER, it only matters अगर idx matches */
		अगर (IS_ERR(desc) && PTR_ERR(desc) != -EPROBE_DEFER)
			वापस PTR_ERR(desc);

		अगर (info.gpioपूर्णांक && idx++ == index) अणु
			अचिन्हित दीर्घ lflags = GPIO_LOOKUP_FLAGS_DEFAULT;
			क्रमागत gpiod_flags dflags = GPIOD_ASIS;
			अक्षर label[32];
			पूर्णांक irq;

			अगर (IS_ERR(desc))
				वापस PTR_ERR(desc);

			irq = gpiod_to_irq(desc);
			अगर (irq < 0)
				वापस irq;

			acpi_gpio_update_gpiod_flags(&dflags, &info);
			acpi_gpio_update_gpiod_lookup_flags(&lflags, &info);

			snम_लिखो(label, माप(label), "GpioInt() %d", index);
			ret = gpiod_configure_flags(desc, label, lflags, dflags);
			अगर (ret < 0)
				वापस ret;

			ret = gpio_set_debounce_समयout(desc, info.debounce);
			अगर (ret)
				वापस ret;

			irq_flags = acpi_dev_get_irq_type(info.triggering,
							  info.polarity);

			/* Set type अगर specअगरied and dअगरferent than the current one */
			अगर (irq_flags != IRQ_TYPE_NONE &&
			    irq_flags != irq_get_trigger_type(irq))
				irq_set_irq_type(irq, irq_flags);

			वापस irq;
		पूर्ण

	पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_gpio_irq_get_by);

अटल acpi_status
acpi_gpio_adr_space_handler(u32 function, acpi_physical_address address,
			    u32 bits, u64 *value, व्योम *handler_context,
			    व्योम *region_context)
अणु
	काष्ठा acpi_gpio_chip *achip = region_context;
	काष्ठा gpio_chip *chip = achip->chip;
	काष्ठा acpi_resource_gpio *agpio;
	काष्ठा acpi_resource *ares;
	u16 pin_index = address;
	acpi_status status;
	पूर्णांक length;
	पूर्णांक i;

	status = acpi_buffer_to_resource(achip->conn_info.connection,
					 achip->conn_info.length, &ares);
	अगर (ACPI_FAILURE(status))
		वापस status;

	अगर (WARN_ON(ares->type != ACPI_RESOURCE_TYPE_GPIO)) अणु
		ACPI_FREE(ares);
		वापस AE_BAD_PARAMETER;
	पूर्ण

	agpio = &ares->data.gpio;

	अगर (WARN_ON(agpio->io_restriction == ACPI_IO_RESTRICT_INPUT &&
	    function == ACPI_WRITE)) अणु
		ACPI_FREE(ares);
		वापस AE_BAD_PARAMETER;
	पूर्ण

	length = min_t(u16, agpio->pin_table_length, pin_index + bits);
	क्रम (i = pin_index; i < length; ++i) अणु
		पूर्णांक pin = agpio->pin_table[i];
		काष्ठा acpi_gpio_connection *conn;
		काष्ठा gpio_desc *desc;
		bool found;

		mutex_lock(&achip->conn_lock);

		found = false;
		list_क्रम_each_entry(conn, &achip->conns, node) अणु
			अगर (conn->pin == pin) अणु
				found = true;
				desc = conn->desc;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * The same GPIO can be shared between operation region and
		 * event but only अगर the access here is ACPI_READ. In that
		 * हाल we "borrow" the event GPIO instead.
		 */
		अगर (!found && agpio->shareable == ACPI_SHARED &&
		     function == ACPI_READ) अणु
			काष्ठा acpi_gpio_event *event;

			list_क्रम_each_entry(event, &achip->events, node) अणु
				अगर (event->pin == pin) अणु
					desc = event->desc;
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			desc = acpi_request_own_gpiod(chip, agpio, i, "ACPI:OpRegion");
			अगर (IS_ERR(desc)) अणु
				mutex_unlock(&achip->conn_lock);
				status = AE_ERROR;
				जाओ out;
			पूर्ण

			conn = kzalloc(माप(*conn), GFP_KERNEL);
			अगर (!conn) अणु
				gpiochip_मुक्त_own_desc(desc);
				mutex_unlock(&achip->conn_lock);
				status = AE_NO_MEMORY;
				जाओ out;
			पूर्ण

			conn->pin = pin;
			conn->desc = desc;
			list_add_tail(&conn->node, &achip->conns);
		पूर्ण

		mutex_unlock(&achip->conn_lock);

		अगर (function == ACPI_WRITE)
			gpiod_set_raw_value_cansleep(desc, !!(*value & BIT(i)));
		अन्यथा
			*value |= (u64)gpiod_get_raw_value_cansleep(desc) << i;
	पूर्ण

out:
	ACPI_FREE(ares);
	वापस status;
पूर्ण

अटल व्योम acpi_gpiochip_request_regions(काष्ठा acpi_gpio_chip *achip)
अणु
	काष्ठा gpio_chip *chip = achip->chip;
	acpi_handle handle = ACPI_HANDLE(chip->parent);
	acpi_status status;

	INIT_LIST_HEAD(&achip->conns);
	mutex_init(&achip->conn_lock);
	status = acpi_install_address_space_handler(handle, ACPI_ADR_SPACE_GPIO,
						    acpi_gpio_adr_space_handler,
						    शून्य, achip);
	अगर (ACPI_FAILURE(status))
		dev_err(chip->parent,
		        "Failed to install GPIO OpRegion handler\n");
पूर्ण

अटल व्योम acpi_gpiochip_मुक्त_regions(काष्ठा acpi_gpio_chip *achip)
अणु
	काष्ठा gpio_chip *chip = achip->chip;
	acpi_handle handle = ACPI_HANDLE(chip->parent);
	काष्ठा acpi_gpio_connection *conn, *पंचांगp;
	acpi_status status;

	status = acpi_हटाओ_address_space_handler(handle, ACPI_ADR_SPACE_GPIO,
						   acpi_gpio_adr_space_handler);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(chip->parent,
			"Failed to remove GPIO OpRegion handler\n");
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe_reverse(conn, पंचांगp, &achip->conns, node) अणु
		gpiochip_मुक्त_own_desc(conn->desc);
		list_del(&conn->node);
		kमुक्त(conn);
	पूर्ण
पूर्ण

अटल काष्ठा gpio_desc *
acpi_gpiochip_parse_own_gpio(काष्ठा acpi_gpio_chip *achip,
			     काष्ठा fwnode_handle *fwnode,
			     स्थिर अक्षर **name,
			     अचिन्हित दीर्घ *lflags,
			     क्रमागत gpiod_flags *dflags)
अणु
	काष्ठा gpio_chip *chip = achip->chip;
	काष्ठा gpio_desc *desc;
	u32 gpios[2];
	पूर्णांक ret;

	*lflags = GPIO_LOOKUP_FLAGS_DEFAULT;
	*dflags = GPIOD_ASIS;
	*name = शून्य;

	ret = fwnode_property_पढ़ो_u32_array(fwnode, "gpios", gpios,
					     ARRAY_SIZE(gpios));
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	desc = gpiochip_get_desc(chip, gpios[0]);
	अगर (IS_ERR(desc))
		वापस desc;

	अगर (gpios[1])
		*lflags |= GPIO_ACTIVE_LOW;

	अगर (fwnode_property_present(fwnode, "input"))
		*dflags |= GPIOD_IN;
	अन्यथा अगर (fwnode_property_present(fwnode, "output-low"))
		*dflags |= GPIOD_OUT_LOW;
	अन्यथा अगर (fwnode_property_present(fwnode, "output-high"))
		*dflags |= GPIOD_OUT_HIGH;
	अन्यथा
		वापस ERR_PTR(-EINVAL);

	fwnode_property_पढ़ो_string(fwnode, "line-name", name);

	वापस desc;
पूर्ण

अटल व्योम acpi_gpiochip_scan_gpios(काष्ठा acpi_gpio_chip *achip)
अणु
	काष्ठा gpio_chip *chip = achip->chip;
	काष्ठा fwnode_handle *fwnode;

	device_क्रम_each_child_node(chip->parent, fwnode) अणु
		अचिन्हित दीर्घ lflags;
		क्रमागत gpiod_flags dflags;
		काष्ठा gpio_desc *desc;
		स्थिर अक्षर *name;
		पूर्णांक ret;

		अगर (!fwnode_property_present(fwnode, "gpio-hog"))
			जारी;

		desc = acpi_gpiochip_parse_own_gpio(achip, fwnode, &name,
						    &lflags, &dflags);
		अगर (IS_ERR(desc))
			जारी;

		ret = gpiod_hog(desc, name, lflags, dflags);
		अगर (ret) अणु
			dev_err(chip->parent, "Failed to hog GPIO\n");
			fwnode_handle_put(fwnode);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

व्योम acpi_gpiochip_add(काष्ठा gpio_chip *chip)
अणु
	काष्ठा acpi_gpio_chip *acpi_gpio;
	acpi_handle handle;
	acpi_status status;

	अगर (!chip || !chip->parent)
		वापस;

	handle = ACPI_HANDLE(chip->parent);
	अगर (!handle)
		वापस;

	acpi_gpio = kzalloc(माप(*acpi_gpio), GFP_KERNEL);
	अगर (!acpi_gpio) अणु
		dev_err(chip->parent,
			"Failed to allocate memory for ACPI GPIO chip\n");
		वापस;
	पूर्ण

	acpi_gpio->chip = chip;
	INIT_LIST_HEAD(&acpi_gpio->events);
	INIT_LIST_HEAD(&acpi_gpio->deferred_req_irqs_list_entry);

	status = acpi_attach_data(handle, acpi_gpio_chip_dh, acpi_gpio);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(chip->parent, "Failed to attach ACPI GPIO chip\n");
		kमुक्त(acpi_gpio);
		वापस;
	पूर्ण

	acpi_gpiochip_request_regions(acpi_gpio);
	acpi_gpiochip_scan_gpios(acpi_gpio);
	acpi_walk_dep_device_list(handle);
पूर्ण

व्योम acpi_gpiochip_हटाओ(काष्ठा gpio_chip *chip)
अणु
	काष्ठा acpi_gpio_chip *acpi_gpio;
	acpi_handle handle;
	acpi_status status;

	अगर (!chip || !chip->parent)
		वापस;

	handle = ACPI_HANDLE(chip->parent);
	अगर (!handle)
		वापस;

	status = acpi_get_data(handle, acpi_gpio_chip_dh, (व्योम **)&acpi_gpio);
	अगर (ACPI_FAILURE(status)) अणु
		dev_warn(chip->parent, "Failed to retrieve ACPI GPIO chip\n");
		वापस;
	पूर्ण

	acpi_gpiochip_मुक्त_regions(acpi_gpio);

	acpi_detach_data(handle, acpi_gpio_chip_dh);
	kमुक्त(acpi_gpio);
पूर्ण

व्योम acpi_gpio_dev_init(काष्ठा gpio_chip *gc, काष्ठा gpio_device *gdev)
अणु
	/* Set शेष fwnode to parent's one अगर present */
	अगर (gc->parent)
		ACPI_COMPANION_SET(&gdev->dev, ACPI_COMPANION(gc->parent));
पूर्ण

अटल पूर्णांक acpi_gpio_package_count(स्थिर जोड़ acpi_object *obj)
अणु
	स्थिर जोड़ acpi_object *element = obj->package.elements;
	स्थिर जोड़ acpi_object *end = element + obj->package.count;
	अचिन्हित पूर्णांक count = 0;

	जबतक (element < end) अणु
		चयन (element->type) अणु
		हाल ACPI_TYPE_LOCAL_REFERENCE:
			element += 3;
			fallthrough;
		हाल ACPI_TYPE_INTEGER:
			element++;
			count++;
			अवरोध;

		शेष:
			वापस -EPROTO;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक acpi_find_gpio_count(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	अचिन्हित पूर्णांक *count = data;

	अगर (ares->type == ACPI_RESOURCE_TYPE_GPIO)
		*count += ares->data.gpio.pin_table_length;

	वापस 1;
पूर्ण

/**
 * acpi_gpio_count - count the GPIOs associated with a device / function
 * @dev:	GPIO consumer, can be %शून्य क्रम प्रणाली-global GPIOs
 * @con_id:	function within the GPIO consumer
 *
 * Return:
 * The number of GPIOs associated with a device / function or %-ENOENT,
 * अगर no GPIO has been asचिन्हित to the requested function.
 */
पूर्णांक acpi_gpio_count(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	स्थिर जोड़ acpi_object *obj;
	स्थिर काष्ठा acpi_gpio_mapping *gm;
	पूर्णांक count = -ENOENT;
	पूर्णांक ret;
	अक्षर propname[32];
	अचिन्हित पूर्णांक i;

	/* Try first from _DSD */
	क्रम (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) अणु
		अगर (con_id)
			snम_लिखो(propname, माप(propname), "%s-%s",
				 con_id, gpio_suffixes[i]);
		अन्यथा
			snम_लिखो(propname, माप(propname), "%s",
				 gpio_suffixes[i]);

		ret = acpi_dev_get_property(adev, propname, ACPI_TYPE_ANY,
					    &obj);
		अगर (ret == 0) अणु
			अगर (obj->type == ACPI_TYPE_LOCAL_REFERENCE)
				count = 1;
			अन्यथा अगर (obj->type == ACPI_TYPE_PACKAGE)
				count = acpi_gpio_package_count(obj);
		पूर्ण अन्यथा अगर (adev->driver_gpios) अणु
			क्रम (gm = adev->driver_gpios; gm->name; gm++)
				अगर (म_भेद(propname, gm->name) == 0) अणु
					count = gm->size;
					अवरोध;
				पूर्ण
		पूर्ण
		अगर (count > 0)
			अवरोध;
	पूर्ण

	/* Then from plain _CRS GPIOs */
	अगर (count < 0) अणु
		काष्ठा list_head resource_list;
		अचिन्हित पूर्णांक crs_count = 0;

		अगर (!acpi_can_fallback_to_crs(adev, con_id))
			वापस count;

		INIT_LIST_HEAD(&resource_list);
		acpi_dev_get_resources(adev, &resource_list,
				       acpi_find_gpio_count, &crs_count);
		acpi_dev_मुक्त_resource_list(&resource_list);
		अगर (crs_count > 0)
			count = crs_count;
	पूर्ण
	वापस count ? count : -ENOENT;
पूर्ण

/* Run deferred acpi_gpiochip_request_irqs() */
अटल पूर्णांक __init acpi_gpio_handle_deferred_request_irqs(व्योम)
अणु
	काष्ठा acpi_gpio_chip *acpi_gpio, *पंचांगp;

	mutex_lock(&acpi_gpio_deferred_req_irqs_lock);
	list_क्रम_each_entry_safe(acpi_gpio, पंचांगp,
				 &acpi_gpio_deferred_req_irqs_list,
				 deferred_req_irqs_list_entry)
		acpi_gpiochip_request_irqs(acpi_gpio);

	acpi_gpio_deferred_req_irqs_करोne = true;
	mutex_unlock(&acpi_gpio_deferred_req_irqs_lock);

	वापस 0;
पूर्ण
/* We must use _sync so that this runs after the first deferred_probe run */
late_initcall_sync(acpi_gpio_handle_deferred_request_irqs);

अटल स्थिर काष्ठा dmi_प्रणाली_id gpiolib_acpi_quirks[] __initस्थिर = अणु
	अणु
		/*
		 * The Minix Neo Z83-4 has a micro-USB-B id-pin handler क्रम
		 * a non existing micro-USB-B connector which माला_दो the HDMI
		 * DDC pins in GPIO mode, अवरोधing HDMI support.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MINIX"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Z83-4"),
		पूर्ण,
		.driver_data = &(काष्ठा acpi_gpiolib_dmi_quirk) अणु
			.no_edge_events_on_boot = true,
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * The Terra Pad 1061 has a micro-USB-B id-pin handler, which
		 * instead of controlling the actual micro-USB-B turns the 5V
		 * boost क्रम its USB-A connector off. The actual micro-USB-B
		 * connector is wired क्रम अक्षरging only.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Wortmann_AG"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TERRA_PAD_1061"),
		पूर्ण,
		.driver_data = &(काष्ठा acpi_gpiolib_dmi_quirk) अणु
			.no_edge_events_on_boot = true,
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * The Dell Venue 10 Pro 5055, with Bay Trail SoC + TI PMIC uses an
		 * बाह्यal embedded-controller connected via I2C + an ACPI GPIO
		 * event handler on INT33FFC:02 pin 12, causing spurious wakeups.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Venue 10 Pro 5055"),
		पूर्ण,
		.driver_data = &(काष्ठा acpi_gpiolib_dmi_quirk) अणु
			.ignore_wake = "INT33FC:02@12",
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * HP X2 10 models with Cherry Trail SoC + TI PMIC use an
		 * बाह्यal embedded-controller connected via I2C + an ACPI GPIO
		 * event handler on INT33FF:01 pin 0, causing spurious wakeups.
		 * When suspending by closing the LID, the घातer to the USB
		 * keyboard is turned off, causing INT0002 ACPI events to
		 * trigger once the XHCI controller notices the keyboard is
		 * gone. So INT0002 events cause spurious wakeups too. Ignoring
		 * EC wakes अवरोधs wakeup when खोलोing the lid, the user needs
		 * to press the घातer-button to wakeup the प्रणाली. The
		 * alternative is suspend simply not working, which is worse.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP x2 Detachable 10-p0XX"),
		पूर्ण,
		.driver_data = &(काष्ठा acpi_gpiolib_dmi_quirk) अणु
			.ignore_wake = "INT33FF:01@0,INT0002:00@2",
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * HP X2 10 models with Bay Trail SoC + AXP288 PMIC use an
		 * बाह्यal embedded-controller connected via I2C + an ACPI GPIO
		 * event handler on INT33FC:02 pin 28, causing spurious wakeups.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion x2 Detachable"),
			DMI_MATCH(DMI_BOARD_NAME, "815D"),
		पूर्ण,
		.driver_data = &(काष्ठा acpi_gpiolib_dmi_quirk) अणु
			.ignore_wake = "INT33FC:02@28",
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * HP X2 10 models with Cherry Trail SoC + AXP288 PMIC use an
		 * बाह्यal embedded-controller connected via I2C + an ACPI GPIO
		 * event handler on INT33FF:01 pin 0, causing spurious wakeups.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion x2 Detachable"),
			DMI_MATCH(DMI_BOARD_NAME, "813E"),
		पूर्ण,
		.driver_data = &(काष्ठा acpi_gpiolib_dmi_quirk) अणु
			.ignore_wake = "INT33FF:01@0",
		पूर्ण,
	पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;

अटल पूर्णांक __init acpi_gpio_setup_params(व्योम)
अणु
	स्थिर काष्ठा acpi_gpiolib_dmi_quirk *quirk = शून्य;
	स्थिर काष्ठा dmi_प्रणाली_id *id;

	id = dmi_first_match(gpiolib_acpi_quirks);
	अगर (id)
		quirk = id->driver_data;

	अगर (run_edge_events_on_boot < 0) अणु
		अगर (quirk && quirk->no_edge_events_on_boot)
			run_edge_events_on_boot = 0;
		अन्यथा
			run_edge_events_on_boot = 1;
	पूर्ण

	अगर (ignore_wake == शून्य && quirk && quirk->ignore_wake)
		ignore_wake = quirk->ignore_wake;

	वापस 0;
पूर्ण

/* Directly after dmi_setup() which runs as core_initcall() */
postcore_initcall(acpi_gpio_setup_params);
