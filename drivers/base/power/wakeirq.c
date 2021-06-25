<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Device wakeirq helper functions */
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>

#समावेश "power.h"

/**
 * dev_pm_attach_wake_irq - Attach device पूर्णांकerrupt as a wake IRQ
 * @dev: Device entry
 * @irq: Device wake-up capable पूर्णांकerrupt
 * @wirq: Wake irq specअगरic data
 *
 * Internal function to attach either a device IO पूर्णांकerrupt or a
 * dedicated wake-up पूर्णांकerrupt as a wake IRQ.
 */
अटल पूर्णांक dev_pm_attach_wake_irq(काष्ठा device *dev, पूर्णांक irq,
				  काष्ठा wake_irq *wirq)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!dev || !wirq)
		वापस -EINVAL;

	spin_lock_irqsave(&dev->घातer.lock, flags);
	अगर (dev_WARN_ONCE(dev, dev->घातer.wakeirq,
			  "wake irq already initialized\n")) अणु
		spin_unlock_irqrestore(&dev->घातer.lock, flags);
		वापस -EEXIST;
	पूर्ण

	dev->घातer.wakeirq = wirq;
	device_wakeup_attach_irq(dev, wirq);

	spin_unlock_irqrestore(&dev->घातer.lock, flags);
	वापस 0;
पूर्ण

/**
 * dev_pm_set_wake_irq - Attach device IO पूर्णांकerrupt as wake IRQ
 * @dev: Device entry
 * @irq: Device IO पूर्णांकerrupt
 *
 * Attach a device IO पूर्णांकerrupt as a wake IRQ. The wake IRQ माला_लो
 * स्वतःmatically configured क्रम wake-up from suspend  based
 * on the device specअगरic sysfs wakeup entry. Typically called
 * during driver probe after calling device_init_wakeup().
 */
पूर्णांक dev_pm_set_wake_irq(काष्ठा device *dev, पूर्णांक irq)
अणु
	काष्ठा wake_irq *wirq;
	पूर्णांक err;

	अगर (irq < 0)
		वापस -EINVAL;

	wirq = kzalloc(माप(*wirq), GFP_KERNEL);
	अगर (!wirq)
		वापस -ENOMEM;

	wirq->dev = dev;
	wirq->irq = irq;

	err = dev_pm_attach_wake_irq(dev, irq, wirq);
	अगर (err)
		kमुक्त(wirq);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_set_wake_irq);

/**
 * dev_pm_clear_wake_irq - Detach a device IO पूर्णांकerrupt wake IRQ
 * @dev: Device entry
 *
 * Detach a device wake IRQ and मुक्त resources.
 *
 * Note that it's OK क्रम drivers to call this without calling
 * dev_pm_set_wake_irq() as all the driver instances may not have
 * a wake IRQ configured. This aव्योम adding wake IRQ specअगरic
 * checks पूर्णांकo the drivers.
 */
व्योम dev_pm_clear_wake_irq(काष्ठा device *dev)
अणु
	काष्ठा wake_irq *wirq = dev->घातer.wakeirq;
	अचिन्हित दीर्घ flags;

	अगर (!wirq)
		वापस;

	spin_lock_irqsave(&dev->घातer.lock, flags);
	device_wakeup_detach_irq(dev);
	dev->घातer.wakeirq = शून्य;
	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	अगर (wirq->status & WAKE_IRQ_DEDICATED_ALLOCATED) अणु
		मुक्त_irq(wirq->irq, wirq);
		wirq->status &= ~WAKE_IRQ_DEDICATED_MASK;
	पूर्ण
	kमुक्त(wirq->name);
	kमुक्त(wirq);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_clear_wake_irq);

/**
 * handle_thपढ़ोed_wake_irq - Handler क्रम dedicated wake-up पूर्णांकerrupts
 * @irq: Device specअगरic dedicated wake-up पूर्णांकerrupt
 * @_wirq: Wake IRQ data
 *
 * Some devices have a separate wake-up पूर्णांकerrupt in addition to the
 * device IO पूर्णांकerrupt. The wake-up पूर्णांकerrupt संकेतs that a device
 * should be woken up from it's idle state. This handler uses device
 * specअगरic pm_runसमय functions to wake the device, and then it's
 * up to the device to करो whatever it needs to. Note that as the
 * device may need to restore context and start up regulators, we
 * use a thपढ़ोed IRQ.
 *
 * Also note that we are not resending the lost device पूर्णांकerrupts.
 * We assume that the wake-up पूर्णांकerrupt just needs to wake-up the
 * device, and then device's pm_runसमय_resume() can deal with the
 * situation.
 */
अटल irqवापस_t handle_thपढ़ोed_wake_irq(पूर्णांक irq, व्योम *_wirq)
अणु
	काष्ठा wake_irq *wirq = _wirq;
	पूर्णांक res;

	/* Maybe पात suspend? */
	अगर (irqd_is_wakeup_set(irq_get_irq_data(irq))) अणु
		pm_wakeup_event(wirq->dev, 0);

		वापस IRQ_HANDLED;
	पूर्ण

	/* We करोn't want RPM_ASYNC or RPM_NOWAIT here */
	res = pm_runसमय_resume(wirq->dev);
	अगर (res < 0)
		dev_warn(wirq->dev,
			 "wake IRQ with no resume: %i\n", res);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * dev_pm_set_dedicated_wake_irq - Request a dedicated wake-up पूर्णांकerrupt
 * @dev: Device entry
 * @irq: Device wake-up पूर्णांकerrupt
 *
 * Unless your hardware has separate wake-up पूर्णांकerrupts in addition
 * to the device IO पूर्णांकerrupts, you करोn't need this.
 *
 * Sets up a thपढ़ोed पूर्णांकerrupt handler क्रम a device that has
 * a dedicated wake-up पूर्णांकerrupt in addition to the device IO
 * पूर्णांकerrupt.
 *
 * The पूर्णांकerrupt starts disabled, and needs to be managed क्रम
 * the device by the bus code or the device driver using
 * dev_pm_enable_wake_irq() and dev_pm_disable_wake_irq()
 * functions.
 */
पूर्णांक dev_pm_set_dedicated_wake_irq(काष्ठा device *dev, पूर्णांक irq)
अणु
	काष्ठा wake_irq *wirq;
	पूर्णांक err;

	अगर (irq < 0)
		वापस -EINVAL;

	wirq = kzalloc(माप(*wirq), GFP_KERNEL);
	अगर (!wirq)
		वापस -ENOMEM;

	wirq->name = kaप्र_लिखो(GFP_KERNEL, "%s:wakeup", dev_name(dev));
	अगर (!wirq->name) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	wirq->dev = dev;
	wirq->irq = irq;
	irq_set_status_flags(irq, IRQ_NOAUTOEN);

	/* Prevent deferred spurious wakeirqs with disable_irq_nosync() */
	irq_set_status_flags(irq, IRQ_DISABLE_UNLAZY);

	/*
	 * Consumer device may need to घातer up and restore state
	 * so we use a thपढ़ोed irq.
	 */
	err = request_thपढ़ोed_irq(irq, शून्य, handle_thपढ़ोed_wake_irq,
				   IRQF_ONESHOT, wirq->name, wirq);
	अगर (err)
		जाओ err_मुक्त_name;

	err = dev_pm_attach_wake_irq(dev, irq, wirq);
	अगर (err)
		जाओ err_मुक्त_irq;

	wirq->status = WAKE_IRQ_DEDICATED_ALLOCATED;

	वापस err;

err_मुक्त_irq:
	मुक्त_irq(irq, wirq);
err_मुक्त_name:
	kमुक्त(wirq->name);
err_मुक्त:
	kमुक्त(wirq);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_set_dedicated_wake_irq);

/**
 * dev_pm_enable_wake_irq - Enable device wake-up पूर्णांकerrupt
 * @dev: Device
 *
 * Optionally called from the bus code or the device driver क्रम
 * runसमय_resume() to override the PM runसमय core managed wake-up
 * पूर्णांकerrupt handling to enable the wake-up पूर्णांकerrupt.
 *
 * Note that क्रम runसमय_suspend()) the wake-up पूर्णांकerrupts
 * should be unconditionally enabled unlike क्रम suspend()
 * that is conditional.
 */
व्योम dev_pm_enable_wake_irq(काष्ठा device *dev)
अणु
	काष्ठा wake_irq *wirq = dev->घातer.wakeirq;

	अगर (wirq && (wirq->status & WAKE_IRQ_DEDICATED_ALLOCATED))
		enable_irq(wirq->irq);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_enable_wake_irq);

/**
 * dev_pm_disable_wake_irq - Disable device wake-up पूर्णांकerrupt
 * @dev: Device
 *
 * Optionally called from the bus code or the device driver क्रम
 * runसमय_suspend() to override the PM runसमय core managed wake-up
 * पूर्णांकerrupt handling to disable the wake-up पूर्णांकerrupt.
 */
व्योम dev_pm_disable_wake_irq(काष्ठा device *dev)
अणु
	काष्ठा wake_irq *wirq = dev->घातer.wakeirq;

	अगर (wirq && (wirq->status & WAKE_IRQ_DEDICATED_ALLOCATED))
		disable_irq_nosync(wirq->irq);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_disable_wake_irq);

/**
 * dev_pm_enable_wake_irq_check - Checks and enables wake-up पूर्णांकerrupt
 * @dev: Device
 * @can_change_status: Can change wake-up पूर्णांकerrupt status
 *
 * Enables wakeirq conditionally. We need to enable wake-up पूर्णांकerrupt
 * lazily on the first rpm_suspend(). This is needed as the consumer device
 * starts in RPM_SUSPENDED state, and the the first pm_runसमय_get() would
 * otherwise try to disable alपढ़ोy disabled wakeirq. The wake-up पूर्णांकerrupt
 * starts disabled with IRQ_NOAUTOEN set.
 *
 * Should be only called from rpm_suspend() and rpm_resume() path.
 * Caller must hold &dev->घातer.lock to change wirq->status
 */
व्योम dev_pm_enable_wake_irq_check(काष्ठा device *dev,
				  bool can_change_status)
अणु
	काष्ठा wake_irq *wirq = dev->घातer.wakeirq;

	अगर (!wirq || !(wirq->status & WAKE_IRQ_DEDICATED_MASK))
		वापस;

	अगर (likely(wirq->status & WAKE_IRQ_DEDICATED_MANAGED)) अणु
		जाओ enable;
	पूर्ण अन्यथा अगर (can_change_status) अणु
		wirq->status |= WAKE_IRQ_DEDICATED_MANAGED;
		जाओ enable;
	पूर्ण

	वापस;

enable:
	enable_irq(wirq->irq);
पूर्ण

/**
 * dev_pm_disable_wake_irq_check - Checks and disables wake-up पूर्णांकerrupt
 * @dev: Device
 *
 * Disables wake-up पूर्णांकerrupt conditionally based on status.
 * Should be only called from rpm_suspend() and rpm_resume() path.
 */
व्योम dev_pm_disable_wake_irq_check(काष्ठा device *dev)
अणु
	काष्ठा wake_irq *wirq = dev->घातer.wakeirq;

	अगर (!wirq || !(wirq->status & WAKE_IRQ_DEDICATED_MASK))
		वापस;

	अगर (wirq->status & WAKE_IRQ_DEDICATED_MANAGED)
		disable_irq_nosync(wirq->irq);
पूर्ण

/**
 * dev_pm_arm_wake_irq - Arm device wake-up
 * @wirq: Device wake-up पूर्णांकerrupt
 *
 * Sets up the wake-up event conditionally based on the
 * device_may_wake().
 */
व्योम dev_pm_arm_wake_irq(काष्ठा wake_irq *wirq)
अणु
	अगर (!wirq)
		वापस;

	अगर (device_may_wakeup(wirq->dev)) अणु
		अगर (wirq->status & WAKE_IRQ_DEDICATED_ALLOCATED &&
		    !pm_runसमय_status_suspended(wirq->dev))
			enable_irq(wirq->irq);

		enable_irq_wake(wirq->irq);
	पूर्ण
पूर्ण

/**
 * dev_pm_disarm_wake_irq - Disarm device wake-up
 * @wirq: Device wake-up पूर्णांकerrupt
 *
 * Clears up the wake-up event conditionally based on the
 * device_may_wake().
 */
व्योम dev_pm_disarm_wake_irq(काष्ठा wake_irq *wirq)
अणु
	अगर (!wirq)
		वापस;

	अगर (device_may_wakeup(wirq->dev)) अणु
		disable_irq_wake(wirq->irq);

		अगर (wirq->status & WAKE_IRQ_DEDICATED_ALLOCATED &&
		    !pm_runसमय_status_suspended(wirq->dev))
			disable_irq_nosync(wirq->irq);
	पूर्ण
पूर्ण
