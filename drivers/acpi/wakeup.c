<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * wakeup.c - support wakeup devices
 * Copyright (C) 2004 Li Shaohua <shaohua.li@पूर्णांकel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "internal.h"
#समावेश "sleep.h"

काष्ठा acpi_wakeup_handler अणु
	काष्ठा list_head list_node;
	bool (*wakeup)(व्योम *context);
	व्योम *context;
पूर्ण;

अटल LIST_HEAD(acpi_wakeup_handler_head);
अटल DEFINE_MUTEX(acpi_wakeup_handler_mutex);

/*
 * We didn't lock acpi_device_lock in the file, because it invokes oops in
 * suspend/resume and isn't really required as this is called in S-state. At
 * that समय, there is no device hotplug
 **/

/**
 * acpi_enable_wakeup_devices - Enable wake-up device GPEs.
 * @sleep_state: ACPI प्रणाली sleep state.
 *
 * Enable wakeup device घातer of devices with the state.enable flag set and set
 * the wakeup enable mask bits in the GPE रेजिस्टरs that correspond to wakeup
 * devices.
 */
व्योम acpi_enable_wakeup_devices(u8 sleep_state)
अणु
	काष्ठा acpi_device *dev, *पंचांगp;

	list_क्रम_each_entry_safe(dev, पंचांगp, &acpi_wakeup_device_list,
				 wakeup_list) अणु
		अगर (!dev->wakeup.flags.valid
		    || sleep_state > (u32) dev->wakeup.sleep_state
		    || !(device_may_wakeup(&dev->dev)
			 || dev->wakeup.prepare_count))
			जारी;

		अगर (device_may_wakeup(&dev->dev))
			acpi_enable_wakeup_device_घातer(dev, sleep_state);

		/* The wake-up घातer should have been enabled alपढ़ोy. */
		acpi_set_gpe_wake_mask(dev->wakeup.gpe_device, dev->wakeup.gpe_number,
				ACPI_GPE_ENABLE);
	पूर्ण
पूर्ण

/**
 * acpi_disable_wakeup_devices - Disable devices' wakeup capability.
 * @sleep_state: ACPI प्रणाली sleep state.
 */
व्योम acpi_disable_wakeup_devices(u8 sleep_state)
अणु
	काष्ठा acpi_device *dev, *पंचांगp;

	list_क्रम_each_entry_safe(dev, पंचांगp, &acpi_wakeup_device_list,
				 wakeup_list) अणु
		अगर (!dev->wakeup.flags.valid
		    || sleep_state > (u32) dev->wakeup.sleep_state
		    || !(device_may_wakeup(&dev->dev)
			 || dev->wakeup.prepare_count))
			जारी;

		acpi_set_gpe_wake_mask(dev->wakeup.gpe_device, dev->wakeup.gpe_number,
				ACPI_GPE_DISABLE);

		अगर (device_may_wakeup(&dev->dev))
			acpi_disable_wakeup_device_घातer(dev);
	पूर्ण
पूर्ण

पूर्णांक __init acpi_wakeup_device_init(व्योम)
अणु
	काष्ठा acpi_device *dev, *पंचांगp;

	mutex_lock(&acpi_device_lock);
	list_क्रम_each_entry_safe(dev, पंचांगp, &acpi_wakeup_device_list,
				 wakeup_list) अणु
		अगर (device_can_wakeup(&dev->dev)) अणु
			/* Button GPEs are supposed to be always enabled. */
			acpi_enable_gpe(dev->wakeup.gpe_device,
					dev->wakeup.gpe_number);
			device_set_wakeup_enable(&dev->dev, true);
		पूर्ण
	पूर्ण
	mutex_unlock(&acpi_device_lock);
	वापस 0;
पूर्ण

/**
 * acpi_रेजिस्टर_wakeup_handler - Register wakeup handler
 * @wake_irq: The IRQ through which the device may receive wakeups
 * @wakeup:   Wakeup-handler to call when the SCI has triggered a wakeup
 * @context:  Context to pass to the handler when calling it
 *
 * Drivers which may share an IRQ with the SCI can use this to रेजिस्टर
 * a handler which वापसs true when the device they are managing wants
 * to trigger a wakeup.
 */
पूर्णांक acpi_रेजिस्टर_wakeup_handler(पूर्णांक wake_irq, bool (*wakeup)(व्योम *context),
				 व्योम *context)
अणु
	काष्ठा acpi_wakeup_handler *handler;

	/*
	 * If the device is not sharing its IRQ with the SCI, there is no
	 * need to रेजिस्टर the handler.
	 */
	अगर (!acpi_sci_irq_valid() || wake_irq != acpi_sci_irq)
		वापस 0;

	handler = kदो_स्मृति(माप(*handler), GFP_KERNEL);
	अगर (!handler)
		वापस -ENOMEM;

	handler->wakeup = wakeup;
	handler->context = context;

	mutex_lock(&acpi_wakeup_handler_mutex);
	list_add(&handler->list_node, &acpi_wakeup_handler_head);
	mutex_unlock(&acpi_wakeup_handler_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_रेजिस्टर_wakeup_handler);

/**
 * acpi_unरेजिस्टर_wakeup_handler - Unरेजिस्टर wakeup handler
 * @wakeup:   Wakeup-handler passed to acpi_रेजिस्टर_wakeup_handler()
 * @context:  Context passed to acpi_रेजिस्टर_wakeup_handler()
 */
व्योम acpi_unरेजिस्टर_wakeup_handler(bool (*wakeup)(व्योम *context),
				    व्योम *context)
अणु
	काष्ठा acpi_wakeup_handler *handler;

	mutex_lock(&acpi_wakeup_handler_mutex);
	list_क्रम_each_entry(handler, &acpi_wakeup_handler_head, list_node) अणु
		अगर (handler->wakeup == wakeup && handler->context == context) अणु
			list_del(&handler->list_node);
			kमुक्त(handler);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&acpi_wakeup_handler_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_unरेजिस्टर_wakeup_handler);

bool acpi_check_wakeup_handlers(व्योम)
अणु
	काष्ठा acpi_wakeup_handler *handler;

	/* No need to lock, nothing अन्यथा is running when we're called. */
	list_क्रम_each_entry(handler, &acpi_wakeup_handler_head, list_node) अणु
		अगर (handler->wakeup(handler->context))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
