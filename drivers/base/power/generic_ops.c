<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/घातer/generic_ops.c - Generic PM callbacks क्रम subप्रणालीs
 *
 * Copyright (c) 2010 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 */
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/export.h>

#अगर_घोषित CONFIG_PM
/**
 * pm_generic_runसमय_suspend - Generic runसमय suspend callback क्रम subप्रणालीs.
 * @dev: Device to suspend.
 *
 * If PM operations are defined क्रम the @dev's driver and they include
 * ->runसमय_suspend(), execute it and वापस its error code.  Otherwise,
 * वापस 0.
 */
पूर्णांक pm_generic_runसमय_suspend(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	पूर्णांक ret;

	ret = pm && pm->runसमय_suspend ? pm->runसमय_suspend(dev) : 0;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_runसमय_suspend);

/**
 * pm_generic_runसमय_resume - Generic runसमय resume callback क्रम subप्रणालीs.
 * @dev: Device to resume.
 *
 * If PM operations are defined क्रम the @dev's driver and they include
 * ->runसमय_resume(), execute it and वापस its error code.  Otherwise,
 * वापस 0.
 */
पूर्णांक pm_generic_runसमय_resume(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	पूर्णांक ret;

	ret = pm && pm->runसमय_resume ? pm->runसमय_resume(dev) : 0;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_runसमय_resume);
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * pm_generic_prepare - Generic routine preparing a device क्रम घातer transition.
 * @dev: Device to prepare.
 *
 * Prepare a device क्रम a प्रणाली-wide घातer transition.
 */
पूर्णांक pm_generic_prepare(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv = dev->driver;
	पूर्णांक ret = 0;

	अगर (drv && drv->pm && drv->pm->prepare)
		ret = drv->pm->prepare(dev);

	वापस ret;
पूर्ण

/**
 * pm_generic_suspend_noirq - Generic suspend_noirq callback क्रम subप्रणालीs.
 * @dev: Device to suspend.
 */
पूर्णांक pm_generic_suspend_noirq(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->suspend_noirq ? pm->suspend_noirq(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_suspend_noirq);

/**
 * pm_generic_suspend_late - Generic suspend_late callback क्रम subप्रणालीs.
 * @dev: Device to suspend.
 */
पूर्णांक pm_generic_suspend_late(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->suspend_late ? pm->suspend_late(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_suspend_late);

/**
 * pm_generic_suspend - Generic suspend callback क्रम subप्रणालीs.
 * @dev: Device to suspend.
 */
पूर्णांक pm_generic_suspend(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->suspend ? pm->suspend(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_suspend);

/**
 * pm_generic_मुक्तze_noirq - Generic मुक्तze_noirq callback क्रम subप्रणालीs.
 * @dev: Device to मुक्तze.
 */
पूर्णांक pm_generic_मुक्तze_noirq(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->मुक्तze_noirq ? pm->मुक्तze_noirq(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_मुक्तze_noirq);

/**
 * pm_generic_मुक्तze_late - Generic मुक्तze_late callback क्रम subप्रणालीs.
 * @dev: Device to मुक्तze.
 */
पूर्णांक pm_generic_मुक्तze_late(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->मुक्तze_late ? pm->मुक्तze_late(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_मुक्तze_late);

/**
 * pm_generic_मुक्तze - Generic मुक्तze callback क्रम subप्रणालीs.
 * @dev: Device to मुक्तze.
 */
पूर्णांक pm_generic_मुक्तze(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->मुक्तze ? pm->मुक्तze(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_मुक्तze);

/**
 * pm_generic_घातeroff_noirq - Generic घातeroff_noirq callback क्रम subप्रणालीs.
 * @dev: Device to handle.
 */
पूर्णांक pm_generic_घातeroff_noirq(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->घातeroff_noirq ? pm->घातeroff_noirq(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_घातeroff_noirq);

/**
 * pm_generic_घातeroff_late - Generic घातeroff_late callback क्रम subप्रणालीs.
 * @dev: Device to handle.
 */
पूर्णांक pm_generic_घातeroff_late(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->घातeroff_late ? pm->घातeroff_late(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_घातeroff_late);

/**
 * pm_generic_घातeroff - Generic घातeroff callback क्रम subप्रणालीs.
 * @dev: Device to handle.
 */
पूर्णांक pm_generic_घातeroff(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->घातeroff ? pm->घातeroff(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_घातeroff);

/**
 * pm_generic_thaw_noirq - Generic thaw_noirq callback क्रम subप्रणालीs.
 * @dev: Device to thaw.
 */
पूर्णांक pm_generic_thaw_noirq(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->thaw_noirq ? pm->thaw_noirq(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_thaw_noirq);

/**
 * pm_generic_thaw_early - Generic thaw_early callback क्रम subप्रणालीs.
 * @dev: Device to thaw.
 */
पूर्णांक pm_generic_thaw_early(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->thaw_early ? pm->thaw_early(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_thaw_early);

/**
 * pm_generic_thaw - Generic thaw callback क्रम subप्रणालीs.
 * @dev: Device to thaw.
 */
पूर्णांक pm_generic_thaw(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->thaw ? pm->thaw(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_thaw);

/**
 * pm_generic_resume_noirq - Generic resume_noirq callback क्रम subप्रणालीs.
 * @dev: Device to resume.
 */
पूर्णांक pm_generic_resume_noirq(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->resume_noirq ? pm->resume_noirq(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_resume_noirq);

/**
 * pm_generic_resume_early - Generic resume_early callback क्रम subप्रणालीs.
 * @dev: Device to resume.
 */
पूर्णांक pm_generic_resume_early(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->resume_early ? pm->resume_early(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_resume_early);

/**
 * pm_generic_resume - Generic resume callback क्रम subप्रणालीs.
 * @dev: Device to resume.
 */
पूर्णांक pm_generic_resume(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->resume ? pm->resume(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_resume);

/**
 * pm_generic_restore_noirq - Generic restore_noirq callback क्रम subप्रणालीs.
 * @dev: Device to restore.
 */
पूर्णांक pm_generic_restore_noirq(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->restore_noirq ? pm->restore_noirq(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_restore_noirq);

/**
 * pm_generic_restore_early - Generic restore_early callback क्रम subप्रणालीs.
 * @dev: Device to resume.
 */
पूर्णांक pm_generic_restore_early(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->restore_early ? pm->restore_early(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_restore_early);

/**
 * pm_generic_restore - Generic restore callback क्रम subप्रणालीs.
 * @dev: Device to restore.
 */
पूर्णांक pm_generic_restore(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;

	वापस pm && pm->restore ? pm->restore(dev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_generic_restore);

/**
 * pm_generic_complete - Generic routine completing a device घातer transition.
 * @dev: Device to handle.
 *
 * Complete a device घातer transition during a प्रणाली-wide घातer transition.
 */
व्योम pm_generic_complete(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv = dev->driver;

	अगर (drv && drv->pm && drv->pm->complete)
		drv->pm->complete(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
