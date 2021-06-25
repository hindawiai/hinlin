<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/घातer/common.c - Common device घातer management code.
 *
 * Copyright (C) 2011 Rafael J. Wysocki <rjw@sisk.pl>, Renesas Electronics Corp.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pm_करोमुख्य.h>

#समावेश "power.h"

/**
 * dev_pm_get_subsys_data - Create or refcount घातer.subsys_data क्रम device.
 * @dev: Device to handle.
 *
 * If घातer.subsys_data is शून्य, poपूर्णांक it to a new object, otherwise increment
 * its reference counter.  Return 0 अगर new object has been created or refcount
 * increased, otherwise negative error code.
 */
पूर्णांक dev_pm_get_subsys_data(काष्ठा device *dev)
अणु
	काष्ठा pm_subsys_data *psd;

	psd = kzalloc(माप(*psd), GFP_KERNEL);
	अगर (!psd)
		वापस -ENOMEM;

	spin_lock_irq(&dev->घातer.lock);

	अगर (dev->घातer.subsys_data) अणु
		dev->घातer.subsys_data->refcount++;
	पूर्ण अन्यथा अणु
		spin_lock_init(&psd->lock);
		psd->refcount = 1;
		dev->घातer.subsys_data = psd;
		pm_clk_init(dev);
		psd = शून्य;
	पूर्ण

	spin_unlock_irq(&dev->घातer.lock);

	/* kमुक्त() verअगरies that its argument is nonzero. */
	kमुक्त(psd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_get_subsys_data);

/**
 * dev_pm_put_subsys_data - Drop reference to घातer.subsys_data.
 * @dev: Device to handle.
 *
 * If the reference counter of घातer.subsys_data is zero after dropping the
 * reference, घातer.subsys_data is हटाओd.
 */
व्योम dev_pm_put_subsys_data(काष्ठा device *dev)
अणु
	काष्ठा pm_subsys_data *psd;

	spin_lock_irq(&dev->घातer.lock);

	psd = dev_to_psd(dev);
	अगर (!psd)
		जाओ out;

	अगर (--psd->refcount == 0)
		dev->घातer.subsys_data = शून्य;
	अन्यथा
		psd = शून्य;

 out:
	spin_unlock_irq(&dev->घातer.lock);
	kमुक्त(psd);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_put_subsys_data);

/**
 * dev_pm_करोमुख्य_attach - Attach a device to its PM करोमुख्य.
 * @dev: Device to attach.
 * @घातer_on: Used to indicate whether we should घातer on the device.
 *
 * The @dev may only be attached to a single PM करोमुख्य. By iterating through
 * the available alternatives we try to find a valid PM करोमुख्य क्रम the device.
 * As attachment succeeds, the ->detach() callback in the काष्ठा dev_pm_करोमुख्य
 * should be asचिन्हित by the corresponding attach function.
 *
 * This function should typically be invoked from subप्रणाली level code during
 * the probe phase. Especially क्रम those that holds devices which requires
 * घातer management through PM करोमुख्यs.
 *
 * Callers must ensure proper synchronization of this function with घातer
 * management callbacks.
 *
 * Returns 0 on successfully attached PM करोमुख्य, or when it is found that the
 * device करोesn't need a PM करोमुख्य, अन्यथा a negative error code.
 */
पूर्णांक dev_pm_करोमुख्य_attach(काष्ठा device *dev, bool घातer_on)
अणु
	पूर्णांक ret;

	अगर (dev->pm_करोमुख्य)
		वापस 0;

	ret = acpi_dev_pm_attach(dev, घातer_on);
	अगर (!ret)
		ret = genpd_dev_pm_attach(dev);

	वापस ret < 0 ? ret : 0;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_करोमुख्य_attach);

/**
 * dev_pm_करोमुख्य_attach_by_id - Associate a device with one of its PM करोमुख्यs.
 * @dev: The device used to lookup the PM करोमुख्य.
 * @index: The index of the PM करोमुख्य.
 *
 * As @dev may only be attached to a single PM करोमुख्य, the backend PM करोमुख्य
 * provider creates a भव device to attach instead. If attachment succeeds,
 * the ->detach() callback in the काष्ठा dev_pm_करोमुख्य are asचिन्हित by the
 * corresponding backend attach function, as to deal with detaching of the
 * created भव device.
 *
 * This function should typically be invoked by a driver during the probe phase,
 * in हाल its device requires घातer management through multiple PM करोमुख्यs. The
 * driver may benefit from using the received device, to configure device-links
 * towards its original device. Depending on the use-हाल and अगर needed, the
 * links may be dynamically changed by the driver, which allows it to control
 * the घातer to the PM करोमुख्यs independently from each other.
 *
 * Callers must ensure proper synchronization of this function with घातer
 * management callbacks.
 *
 * Returns the भव created device when successfully attached to its PM
 * करोमुख्य, शून्य in हाल @dev करोn't need a PM करोमुख्य, अन्यथा an ERR_PTR().
 * Note that, to detach the वापसed भव device, the driver shall call
 * dev_pm_करोमुख्य_detach() on it, typically during the हटाओ phase.
 */
काष्ठा device *dev_pm_करोमुख्य_attach_by_id(काष्ठा device *dev,
					  अचिन्हित पूर्णांक index)
अणु
	अगर (dev->pm_करोमुख्य)
		वापस ERR_PTR(-EEXIST);

	वापस genpd_dev_pm_attach_by_id(dev, index);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_करोमुख्य_attach_by_id);

/**
 * dev_pm_करोमुख्य_attach_by_name - Associate a device with one of its PM करोमुख्यs.
 * @dev: The device used to lookup the PM करोमुख्य.
 * @name: The name of the PM करोमुख्य.
 *
 * For a detailed function description, see dev_pm_करोमुख्य_attach_by_id().
 */
काष्ठा device *dev_pm_करोमुख्य_attach_by_name(काष्ठा device *dev,
					    स्थिर अक्षर *name)
अणु
	अगर (dev->pm_करोमुख्य)
		वापस ERR_PTR(-EEXIST);

	वापस genpd_dev_pm_attach_by_name(dev, name);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_करोमुख्य_attach_by_name);

/**
 * dev_pm_करोमुख्य_detach - Detach a device from its PM करोमुख्य.
 * @dev: Device to detach.
 * @घातer_off: Used to indicate whether we should घातer off the device.
 *
 * This functions will reverse the actions from dev_pm_करोमुख्य_attach() and
 * dev_pm_करोमुख्य_attach_by_id(), thus it detaches @dev from its PM करोमुख्य.
 * Typically it should be invoked during the हटाओ phase, either from
 * subप्रणाली level code or from drivers.
 *
 * Callers must ensure proper synchronization of this function with घातer
 * management callbacks.
 */
व्योम dev_pm_करोमुख्य_detach(काष्ठा device *dev, bool घातer_off)
अणु
	अगर (dev->pm_करोमुख्य && dev->pm_करोमुख्य->detach)
		dev->pm_करोमुख्य->detach(dev, घातer_off);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_करोमुख्य_detach);

/**
 * dev_pm_करोमुख्य_start - Start the device through its PM करोमुख्य.
 * @dev: Device to start.
 *
 * This function should typically be called during probe by a subप्रणाली/driver,
 * when it needs to start its device from the PM करोमुख्य's perspective. Note
 * that, it's assumed that the PM करोमुख्य is alपढ़ोy घातered on when this
 * function is called.
 *
 * Returns 0 on success and negative error values on failures.
 */
पूर्णांक dev_pm_करोमुख्य_start(काष्ठा device *dev)
अणु
	अगर (dev->pm_करोमुख्य && dev->pm_करोमुख्य->start)
		वापस dev->pm_करोमुख्य->start(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_करोमुख्य_start);

/**
 * dev_pm_करोमुख्य_set - Set PM करोमुख्य of a device.
 * @dev: Device whose PM करोमुख्य is to be set.
 * @pd: PM करोमुख्य to be set, or शून्य.
 *
 * Sets the PM करोमुख्य the device beदीर्घs to. The PM करोमुख्य of a device needs
 * to be set beक्रमe its probe finishes (it's bound to a driver).
 *
 * This function must be called with the device lock held.
 */
व्योम dev_pm_करोमुख्य_set(काष्ठा device *dev, काष्ठा dev_pm_करोमुख्य *pd)
अणु
	अगर (dev->pm_करोमुख्य == pd)
		वापस;

	WARN(pd && device_is_bound(dev),
	     "PM domains can only be changed for unbound devices\n");
	dev->pm_करोमुख्य = pd;
	device_pm_check_callbacks(dev);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_करोमुख्य_set);
