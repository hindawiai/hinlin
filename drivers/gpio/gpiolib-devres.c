<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * devres.c - managed gpio resources
 * This file is based on kernel/irq/devres.c
 *
 * Copyright (c) 2011 John Crispin <john@phrozen.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>

#समावेश "gpiolib.h"

अटल व्योम devm_gpiod_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा gpio_desc **desc = res;

	gpiod_put(*desc);
पूर्ण

अटल पूर्णांक devm_gpiod_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा gpio_desc **this = res, **gpio = data;

	वापस *this == *gpio;
पूर्ण

अटल व्योम devm_gpiod_release_array(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा gpio_descs **descs = res;

	gpiod_put_array(*descs);
पूर्ण

अटल पूर्णांक devm_gpiod_match_array(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा gpio_descs **this = res, **gpios = data;

	वापस *this == *gpios;
पूर्ण

/**
 * devm_gpiod_get - Resource-managed gpiod_get()
 * @dev:	GPIO consumer
 * @con_id:	function within the GPIO consumer
 * @flags:	optional GPIO initialization flags
 *
 * Managed gpiod_get(). GPIO descriptors वापसed from this function are
 * स्वतःmatically disposed on driver detach. See gpiod_get() क्रम detailed
 * inक्रमmation about behavior and वापस values.
 */
काष्ठा gpio_desc *__must_check devm_gpiod_get(काष्ठा device *dev,
					      स्थिर अक्षर *con_id,
					      क्रमागत gpiod_flags flags)
अणु
	वापस devm_gpiod_get_index(dev, con_id, 0, flags);
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_get);

/**
 * devm_gpiod_get_optional - Resource-managed gpiod_get_optional()
 * @dev: GPIO consumer
 * @con_id: function within the GPIO consumer
 * @flags: optional GPIO initialization flags
 *
 * Managed gpiod_get_optional(). GPIO descriptors वापसed from this function
 * are स्वतःmatically disposed on driver detach. See gpiod_get_optional() क्रम
 * detailed inक्रमmation about behavior and वापस values.
 */
काष्ठा gpio_desc *__must_check devm_gpiod_get_optional(काष्ठा device *dev,
						       स्थिर अक्षर *con_id,
						       क्रमागत gpiod_flags flags)
अणु
	वापस devm_gpiod_get_index_optional(dev, con_id, 0, flags);
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_get_optional);

/**
 * devm_gpiod_get_index - Resource-managed gpiod_get_index()
 * @dev:	GPIO consumer
 * @con_id:	function within the GPIO consumer
 * @idx:	index of the GPIO to obtain in the consumer
 * @flags:	optional GPIO initialization flags
 *
 * Managed gpiod_get_index(). GPIO descriptors वापसed from this function are
 * स्वतःmatically disposed on driver detach. See gpiod_get_index() क्रम detailed
 * inक्रमmation about behavior and वापस values.
 */
काष्ठा gpio_desc *__must_check devm_gpiod_get_index(काष्ठा device *dev,
						    स्थिर अक्षर *con_id,
						    अचिन्हित पूर्णांक idx,
						    क्रमागत gpiod_flags flags)
अणु
	काष्ठा gpio_desc **dr;
	काष्ठा gpio_desc *desc;

	desc = gpiod_get_index(dev, con_id, idx, flags);
	अगर (IS_ERR(desc))
		वापस desc;

	/*
	 * For non-exclusive GPIO descriptors, check अगर this descriptor is
	 * alपढ़ोy under resource management by this device.
	 */
	अगर (flags & GPIOD_FLAGS_BIT_NONEXCLUSIVE) अणु
		काष्ठा devres *dres;

		dres = devres_find(dev, devm_gpiod_release,
				   devm_gpiod_match, &desc);
		अगर (dres)
			वापस desc;
	पूर्ण

	dr = devres_alloc(devm_gpiod_release, माप(काष्ठा gpio_desc *),
			  GFP_KERNEL);
	अगर (!dr) अणु
		gpiod_put(desc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	*dr = desc;
	devres_add(dev, dr);

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_get_index);

/**
 * devm_gpiod_get_from_of_node() - obtain a GPIO from an OF node
 * @dev:	device क्रम lअगरecycle management
 * @node:	handle of the OF node
 * @propname:	name of the DT property representing the GPIO
 * @index:	index of the GPIO to obtain क्रम the consumer
 * @dflags:	GPIO initialization flags
 * @label:	label to attach to the requested GPIO
 *
 * Returns:
 * On successful request the GPIO pin is configured in accordance with
 * provided @dflags.
 *
 * In हाल of error an ERR_PTR() is वापसed.
 */
काष्ठा gpio_desc *devm_gpiod_get_from_of_node(काष्ठा device *dev,
					      काष्ठा device_node *node,
					      स्थिर अक्षर *propname, पूर्णांक index,
					      क्रमागत gpiod_flags dflags,
					      स्थिर अक्षर *label)
अणु
	काष्ठा gpio_desc **dr;
	काष्ठा gpio_desc *desc;

	desc = gpiod_get_from_of_node(node, propname, index, dflags, label);
	अगर (IS_ERR(desc))
		वापस desc;

	/*
	 * For non-exclusive GPIO descriptors, check अगर this descriptor is
	 * alपढ़ोy under resource management by this device.
	 */
	अगर (dflags & GPIOD_FLAGS_BIT_NONEXCLUSIVE) अणु
		काष्ठा devres *dres;

		dres = devres_find(dev, devm_gpiod_release,
				   devm_gpiod_match, &desc);
		अगर (dres)
			वापस desc;
	पूर्ण

	dr = devres_alloc(devm_gpiod_release, माप(काष्ठा gpio_desc *),
			  GFP_KERNEL);
	अगर (!dr) अणु
		gpiod_put(desc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	*dr = desc;
	devres_add(dev, dr);

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_get_from_of_node);

/**
 * devm_fwnode_gpiod_get_index - get a GPIO descriptor from a given node
 * @dev:	GPIO consumer
 * @fwnode:	firmware node containing GPIO reference
 * @con_id:	function within the GPIO consumer
 * @index:	index of the GPIO to obtain in the consumer
 * @flags:	GPIO initialization flags
 * @label:	label to attach to the requested GPIO
 *
 * GPIO descriptors वापसed from this function are स्वतःmatically disposed on
 * driver detach.
 *
 * On successful request the GPIO pin is configured in accordance with
 * provided @flags.
 */
काष्ठा gpio_desc *devm_fwnode_gpiod_get_index(काष्ठा device *dev,
					      काष्ठा fwnode_handle *fwnode,
					      स्थिर अक्षर *con_id, पूर्णांक index,
					      क्रमागत gpiod_flags flags,
					      स्थिर अक्षर *label)
अणु
	काष्ठा gpio_desc **dr;
	काष्ठा gpio_desc *desc;

	dr = devres_alloc(devm_gpiod_release, माप(काष्ठा gpio_desc *),
			  GFP_KERNEL);
	अगर (!dr)
		वापस ERR_PTR(-ENOMEM);

	desc = fwnode_gpiod_get_index(fwnode, con_id, index, flags, label);
	अगर (IS_ERR(desc)) अणु
		devres_मुक्त(dr);
		वापस desc;
	पूर्ण

	*dr = desc;
	devres_add(dev, dr);

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_fwnode_gpiod_get_index);

/**
 * devm_gpiod_get_index_optional - Resource-managed gpiod_get_index_optional()
 * @dev: GPIO consumer
 * @con_id: function within the GPIO consumer
 * @index: index of the GPIO to obtain in the consumer
 * @flags: optional GPIO initialization flags
 *
 * Managed gpiod_get_index_optional(). GPIO descriptors वापसed from this
 * function are स्वतःmatically disposed on driver detach. See
 * gpiod_get_index_optional() क्रम detailed inक्रमmation about behavior and
 * वापस values.
 */
काष्ठा gpio_desc *__must_check devm_gpiod_get_index_optional(काष्ठा device *dev,
							     स्थिर अक्षर *con_id,
							     अचिन्हित पूर्णांक index,
							     क्रमागत gpiod_flags flags)
अणु
	काष्ठा gpio_desc *desc;

	desc = devm_gpiod_get_index(dev, con_id, index, flags);
	अगर (gpiod_not_found(desc))
		वापस शून्य;

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_get_index_optional);

/**
 * devm_gpiod_get_array - Resource-managed gpiod_get_array()
 * @dev:	GPIO consumer
 * @con_id:	function within the GPIO consumer
 * @flags:	optional GPIO initialization flags
 *
 * Managed gpiod_get_array(). GPIO descriptors वापसed from this function are
 * स्वतःmatically disposed on driver detach. See gpiod_get_array() क्रम detailed
 * inक्रमmation about behavior and वापस values.
 */
काष्ठा gpio_descs *__must_check devm_gpiod_get_array(काष्ठा device *dev,
						     स्थिर अक्षर *con_id,
						     क्रमागत gpiod_flags flags)
अणु
	काष्ठा gpio_descs **dr;
	काष्ठा gpio_descs *descs;

	dr = devres_alloc(devm_gpiod_release_array,
			  माप(काष्ठा gpio_descs *), GFP_KERNEL);
	अगर (!dr)
		वापस ERR_PTR(-ENOMEM);

	descs = gpiod_get_array(dev, con_id, flags);
	अगर (IS_ERR(descs)) अणु
		devres_मुक्त(dr);
		वापस descs;
	पूर्ण

	*dr = descs;
	devres_add(dev, dr);

	वापस descs;
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_get_array);

/**
 * devm_gpiod_get_array_optional - Resource-managed gpiod_get_array_optional()
 * @dev:	GPIO consumer
 * @con_id:	function within the GPIO consumer
 * @flags:	optional GPIO initialization flags
 *
 * Managed gpiod_get_array_optional(). GPIO descriptors वापसed from this
 * function are स्वतःmatically disposed on driver detach.
 * See gpiod_get_array_optional() क्रम detailed inक्रमmation about behavior and
 * वापस values.
 */
काष्ठा gpio_descs *__must_check
devm_gpiod_get_array_optional(काष्ठा device *dev, स्थिर अक्षर *con_id,
			      क्रमागत gpiod_flags flags)
अणु
	काष्ठा gpio_descs *descs;

	descs = devm_gpiod_get_array(dev, con_id, flags);
	अगर (gpiod_not_found(descs))
		वापस शून्य;

	वापस descs;
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_get_array_optional);

/**
 * devm_gpiod_put - Resource-managed gpiod_put()
 * @dev:	GPIO consumer
 * @desc:	GPIO descriptor to dispose of
 *
 * Dispose of a GPIO descriptor obtained with devm_gpiod_get() or
 * devm_gpiod_get_index(). Normally this function will not be called as the GPIO
 * will be disposed of by the resource management code.
 */
व्योम devm_gpiod_put(काष्ठा device *dev, काष्ठा gpio_desc *desc)
अणु
	WARN_ON(devres_release(dev, devm_gpiod_release, devm_gpiod_match,
		&desc));
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_put);

/**
 * devm_gpiod_unhinge - Remove resource management from a gpio descriptor
 * @dev:	GPIO consumer
 * @desc:	GPIO descriptor to हटाओ resource management from
 *
 * Remove resource management from a GPIO descriptor. This is needed when
 * you want to hand over lअगरecycle management of a descriptor to another
 * mechanism.
 */

व्योम devm_gpiod_unhinge(काष्ठा device *dev, काष्ठा gpio_desc *desc)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(desc))
		वापस;
	ret = devres_destroy(dev, devm_gpiod_release,
			     devm_gpiod_match, &desc);
	/*
	 * If the GPIO descriptor is requested as nonexclusive, we
	 * may call this function several बार on the same descriptor
	 * so it is OK अगर devres_destroy() वापसs -ENOENT.
	 */
	अगर (ret == -ENOENT)
		वापस;
	/* Anything अन्यथा we should warn about */
	WARN_ON(ret);
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_unhinge);

/**
 * devm_gpiod_put_array - Resource-managed gpiod_put_array()
 * @dev:	GPIO consumer
 * @descs:	GPIO descriptor array to dispose of
 *
 * Dispose of an array of GPIO descriptors obtained with devm_gpiod_get_array().
 * Normally this function will not be called as the GPIOs will be disposed of
 * by the resource management code.
 */
व्योम devm_gpiod_put_array(काष्ठा device *dev, काष्ठा gpio_descs *descs)
अणु
	WARN_ON(devres_release(dev, devm_gpiod_release_array,
			       devm_gpiod_match_array, &descs));
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiod_put_array);




अटल व्योम devm_gpio_release(काष्ठा device *dev, व्योम *res)
अणु
	अचिन्हित *gpio = res;

	gpio_मुक्त(*gpio);
पूर्ण

अटल पूर्णांक devm_gpio_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	अचिन्हित *this = res, *gpio = data;

	वापस *this == *gpio;
पूर्ण

/**
 *      devm_gpio_request - request a GPIO क्रम a managed device
 *      @dev: device to request the GPIO क्रम
 *      @gpio: GPIO to allocate
 *      @label: the name of the requested GPIO
 *
 *      Except क्रम the extra @dev argument, this function takes the
 *      same arguments and perक्रमms the same function as
 *      gpio_request().  GPIOs requested with this function will be
 *      स्वतःmatically मुक्तd on driver detach.
 *
 *      If an GPIO allocated with this function needs to be मुक्तd
 *      separately, devm_gpio_मुक्त() must be used.
 */

पूर्णांक devm_gpio_request(काष्ठा device *dev, अचिन्हित gpio, स्थिर अक्षर *label)
अणु
	अचिन्हित *dr;
	पूर्णांक rc;

	dr = devres_alloc(devm_gpio_release, माप(अचिन्हित), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	rc = gpio_request(gpio, label);
	अगर (rc) अणु
		devres_मुक्त(dr);
		वापस rc;
	पूर्ण

	*dr = gpio;
	devres_add(dev, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpio_request);

/**
 *	devm_gpio_request_one - request a single GPIO with initial setup
 *	@dev:   device to request क्रम
 *	@gpio:	the GPIO number
 *	@flags:	GPIO configuration as specअगरied by GPIOF_*
 *	@label:	a literal description string of this GPIO
 */
पूर्णांक devm_gpio_request_one(काष्ठा device *dev, अचिन्हित gpio,
			  अचिन्हित दीर्घ flags, स्थिर अक्षर *label)
अणु
	अचिन्हित *dr;
	पूर्णांक rc;

	dr = devres_alloc(devm_gpio_release, माप(अचिन्हित), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	rc = gpio_request_one(gpio, flags, label);
	अगर (rc) अणु
		devres_मुक्त(dr);
		वापस rc;
	पूर्ण

	*dr = gpio;
	devres_add(dev, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpio_request_one);

/**
 *      devm_gpio_मुक्त - मुक्त a GPIO
 *      @dev: device to मुक्त GPIO क्रम
 *      @gpio: GPIO to मुक्त
 *
 *      Except क्रम the extra @dev argument, this function takes the
 *      same arguments and perक्रमms the same function as gpio_मुक्त().
 *      This function instead of gpio_मुक्त() should be used to manually
 *      मुक्त GPIOs allocated with devm_gpio_request().
 */
व्योम devm_gpio_मुक्त(काष्ठा device *dev, अचिन्हित पूर्णांक gpio)
अणु

	WARN_ON(devres_release(dev, devm_gpio_release, devm_gpio_match,
		&gpio));
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpio_मुक्त);

अटल व्योम devm_gpio_chip_release(व्योम *data)
अणु
	काष्ठा gpio_chip *gc = data;

	gpiochip_हटाओ(gc);
पूर्ण

/**
 * devm_gpiochip_add_data_with_key() - Resource managed gpiochip_add_data_with_key()
 * @dev: poपूर्णांकer to the device that gpio_chip beदीर्घs to.
 * @gc: the GPIO chip to रेजिस्टर
 * @data: driver-निजी data associated with this chip
 * @lock_key: lockdep class क्रम IRQ lock
 * @request_key: lockdep class क्रम IRQ request
 *
 * Context: potentially beक्रमe irqs will work
 *
 * The gpio chip स्वतःmatically be released when the device is unbound.
 *
 * Returns:
 * A negative त्रुटि_सं अगर the chip can't be रेजिस्टरed, such as because the
 * gc->base is invalid or alपढ़ोy associated with a dअगरferent chip.
 * Otherwise it वापसs zero as a success code.
 */
पूर्णांक devm_gpiochip_add_data_with_key(काष्ठा device *dev, काष्ठा gpio_chip *gc, व्योम *data,
				    काष्ठा lock_class_key *lock_key,
				    काष्ठा lock_class_key *request_key)
अणु
	पूर्णांक ret;

	ret = gpiochip_add_data_with_key(gc, data, lock_key, request_key);
	अगर (ret < 0)
		वापस ret;

	वापस devm_add_action_or_reset(dev, devm_gpio_chip_release, gc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpiochip_add_data_with_key);
