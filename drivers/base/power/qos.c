<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Devices PM QoS स्थिरraपूर्णांकs management
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 *
 * This module exposes the पूर्णांकerface to kernel space क्रम specअगरying
 * per-device PM QoS dependencies. It provides infraकाष्ठाure क्रम registration
 * of:
 *
 * Dependents on a QoS value : रेजिस्टर requests
 * Watchers of QoS value : get notअगरied when target QoS value changes
 *
 * This QoS design is best efक्रमt based. Dependents रेजिस्टर their QoS needs.
 * Watchers रेजिस्टर to keep track of the current QoS needs of the प्रणाली.
 * Watchers can रेजिस्टर a per-device notअगरication callback using the
 * dev_pm_qos_*_notअगरier API. The notअगरication chain data is stored in the
 * per-device स्थिरraपूर्णांक data काष्ठा.
 *
 * Note about the per-device स्थिरraपूर्णांक data काष्ठा allocation:
 * . The per-device स्थिरraपूर्णांकs data काष्ठा ptr is stored पूर्णांकo the device
 *    dev_pm_info.
 * . To minimize the data usage by the per-device स्थिरraपूर्णांकs, the data काष्ठा
 *   is only allocated at the first call to dev_pm_qos_add_request.
 * . The data is later मुक्त'd when the device is हटाओd from the प्रणाली.
 *  . A global mutex protects the स्थिरraपूर्णांकs users from the data being
 *     allocated and मुक्त'd.
 */

#समावेश <linux/pm_qos.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/export.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/err.h>
#समावेश <trace/events/घातer.h>

#समावेश "power.h"

अटल DEFINE_MUTEX(dev_pm_qos_mtx);
अटल DEFINE_MUTEX(dev_pm_qos_sysfs_mtx);

/**
 * __dev_pm_qos_flags - Check PM QoS flags क्रम a given device.
 * @dev: Device to check the PM QoS flags क्रम.
 * @mask: Flags to check against.
 *
 * This routine must be called with dev->घातer.lock held.
 */
क्रमागत pm_qos_flags_status __dev_pm_qos_flags(काष्ठा device *dev, s32 mask)
अणु
	काष्ठा dev_pm_qos *qos = dev->घातer.qos;
	काष्ठा pm_qos_flags *pqf;
	s32 val;

	lockdep_निश्चित_held(&dev->घातer.lock);

	अगर (IS_ERR_OR_शून्य(qos))
		वापस PM_QOS_FLAGS_UNDEFINED;

	pqf = &qos->flags;
	अगर (list_empty(&pqf->list))
		वापस PM_QOS_FLAGS_UNDEFINED;

	val = pqf->effective_flags & mask;
	अगर (val)
		वापस (val == mask) ? PM_QOS_FLAGS_ALL : PM_QOS_FLAGS_SOME;

	वापस PM_QOS_FLAGS_NONE;
पूर्ण

/**
 * dev_pm_qos_flags - Check PM QoS flags क्रम a given device (locked).
 * @dev: Device to check the PM QoS flags क्रम.
 * @mask: Flags to check against.
 */
क्रमागत pm_qos_flags_status dev_pm_qos_flags(काष्ठा device *dev, s32 mask)
अणु
	अचिन्हित दीर्घ irqflags;
	क्रमागत pm_qos_flags_status ret;

	spin_lock_irqsave(&dev->घातer.lock, irqflags);
	ret = __dev_pm_qos_flags(dev, mask);
	spin_unlock_irqrestore(&dev->घातer.lock, irqflags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_flags);

/**
 * __dev_pm_qos_resume_latency - Get resume latency स्थिरraपूर्णांक क्रम a given device.
 * @dev: Device to get the PM QoS स्थिरraपूर्णांक value क्रम.
 *
 * This routine must be called with dev->घातer.lock held.
 */
s32 __dev_pm_qos_resume_latency(काष्ठा device *dev)
अणु
	lockdep_निश्चित_held(&dev->घातer.lock);

	वापस dev_pm_qos_raw_resume_latency(dev);
पूर्ण

/**
 * dev_pm_qos_पढ़ो_value - Get PM QoS स्थिरraपूर्णांक क्रम a given device (locked).
 * @dev: Device to get the PM QoS स्थिरraपूर्णांक value क्रम.
 * @type: QoS request type.
 */
s32 dev_pm_qos_पढ़ो_value(काष्ठा device *dev, क्रमागत dev_pm_qos_req_type type)
अणु
	काष्ठा dev_pm_qos *qos = dev->घातer.qos;
	अचिन्हित दीर्घ flags;
	s32 ret;

	spin_lock_irqsave(&dev->घातer.lock, flags);

	चयन (type) अणु
	हाल DEV_PM_QOS_RESUME_LATENCY:
		ret = IS_ERR_OR_शून्य(qos) ? PM_QOS_RESUME_LATENCY_NO_CONSTRAINT
			: pm_qos_पढ़ो_value(&qos->resume_latency);
		अवरोध;
	हाल DEV_PM_QOS_MIN_FREQUENCY:
		ret = IS_ERR_OR_शून्य(qos) ? PM_QOS_MIN_FREQUENCY_DEFAULT_VALUE
			: freq_qos_पढ़ो_value(&qos->freq, FREQ_QOS_MIN);
		अवरोध;
	हाल DEV_PM_QOS_MAX_FREQUENCY:
		ret = IS_ERR_OR_शून्य(qos) ? PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE
			: freq_qos_पढ़ो_value(&qos->freq, FREQ_QOS_MAX);
		अवरोध;
	शेष:
		WARN_ON(1);
		ret = 0;
	पूर्ण

	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	वापस ret;
पूर्ण

/**
 * apply_स्थिरraपूर्णांक - Add/modअगरy/हटाओ device PM QoS request.
 * @req: Constraपूर्णांक request to apply
 * @action: Action to perक्रमm (add/update/हटाओ).
 * @value: Value to assign to the QoS request.
 *
 * Internal function to update the स्थिरraपूर्णांकs list using the PM QoS core
 * code and अगर needed call the per-device callbacks.
 */
अटल पूर्णांक apply_स्थिरraपूर्णांक(काष्ठा dev_pm_qos_request *req,
			    क्रमागत pm_qos_req_action action, s32 value)
अणु
	काष्ठा dev_pm_qos *qos = req->dev->घातer.qos;
	पूर्णांक ret;

	चयन(req->type) अणु
	हाल DEV_PM_QOS_RESUME_LATENCY:
		अगर (WARN_ON(action != PM_QOS_REMOVE_REQ && value < 0))
			value = 0;

		ret = pm_qos_update_target(&qos->resume_latency,
					   &req->data.pnode, action, value);
		अवरोध;
	हाल DEV_PM_QOS_LATENCY_TOLERANCE:
		ret = pm_qos_update_target(&qos->latency_tolerance,
					   &req->data.pnode, action, value);
		अगर (ret) अणु
			value = pm_qos_पढ़ो_value(&qos->latency_tolerance);
			req->dev->घातer.set_latency_tolerance(req->dev, value);
		पूर्ण
		अवरोध;
	हाल DEV_PM_QOS_MIN_FREQUENCY:
	हाल DEV_PM_QOS_MAX_FREQUENCY:
		ret = freq_qos_apply(&req->data.freq, action, value);
		अवरोध;
	हाल DEV_PM_QOS_FLAGS:
		ret = pm_qos_update_flags(&qos->flags, &req->data.flr,
					  action, value);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * dev_pm_qos_स्थिरraपूर्णांकs_allocate
 * @dev: device to allocate data क्रम
 *
 * Called at the first call to add_request, क्रम स्थिरraपूर्णांक data allocation
 * Must be called with the dev_pm_qos_mtx mutex held
 */
अटल पूर्णांक dev_pm_qos_स्थिरraपूर्णांकs_allocate(काष्ठा device *dev)
अणु
	काष्ठा dev_pm_qos *qos;
	काष्ठा pm_qos_स्थिरraपूर्णांकs *c;
	काष्ठा blocking_notअगरier_head *n;

	qos = kzalloc(माप(*qos), GFP_KERNEL);
	अगर (!qos)
		वापस -ENOMEM;

	n = kzalloc(3 * माप(*n), GFP_KERNEL);
	अगर (!n) अणु
		kमुक्त(qos);
		वापस -ENOMEM;
	पूर्ण

	c = &qos->resume_latency;
	plist_head_init(&c->list);
	c->target_value = PM_QOS_RESUME_LATENCY_DEFAULT_VALUE;
	c->शेष_value = PM_QOS_RESUME_LATENCY_DEFAULT_VALUE;
	c->no_स्थिरraपूर्णांक_value = PM_QOS_RESUME_LATENCY_NO_CONSTRAINT;
	c->type = PM_QOS_MIN;
	c->notअगरiers = n;
	BLOCKING_INIT_NOTIFIER_HEAD(n);

	c = &qos->latency_tolerance;
	plist_head_init(&c->list);
	c->target_value = PM_QOS_LATENCY_TOLERANCE_DEFAULT_VALUE;
	c->शेष_value = PM_QOS_LATENCY_TOLERANCE_DEFAULT_VALUE;
	c->no_स्थिरraपूर्णांक_value = PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT;
	c->type = PM_QOS_MIN;

	freq_स्थिरraपूर्णांकs_init(&qos->freq);

	INIT_LIST_HEAD(&qos->flags.list);

	spin_lock_irq(&dev->घातer.lock);
	dev->घातer.qos = qos;
	spin_unlock_irq(&dev->घातer.lock);

	वापस 0;
पूर्ण

अटल व्योम __dev_pm_qos_hide_latency_limit(काष्ठा device *dev);
अटल व्योम __dev_pm_qos_hide_flags(काष्ठा device *dev);

/**
 * dev_pm_qos_स्थिरraपूर्णांकs_destroy
 * @dev: target device
 *
 * Called from the device PM subप्रणाली on device removal under device_pm_lock().
 */
व्योम dev_pm_qos_स्थिरraपूर्णांकs_destroy(काष्ठा device *dev)
अणु
	काष्ठा dev_pm_qos *qos;
	काष्ठा dev_pm_qos_request *req, *पंचांगp;
	काष्ठा pm_qos_स्थिरraपूर्णांकs *c;
	काष्ठा pm_qos_flags *f;

	mutex_lock(&dev_pm_qos_sysfs_mtx);

	/*
	 * If the device's PM QoS resume latency limit or PM QoS flags have been
	 * exposed to user space, they have to be hidden at this poपूर्णांक.
	 */
	pm_qos_sysfs_हटाओ_resume_latency(dev);
	pm_qos_sysfs_हटाओ_flags(dev);

	mutex_lock(&dev_pm_qos_mtx);

	__dev_pm_qos_hide_latency_limit(dev);
	__dev_pm_qos_hide_flags(dev);

	qos = dev->घातer.qos;
	अगर (!qos)
		जाओ out;

	/* Flush the स्थिरraपूर्णांकs lists क्रम the device. */
	c = &qos->resume_latency;
	plist_क्रम_each_entry_safe(req, पंचांगp, &c->list, data.pnode) अणु
		/*
		 * Update स्थिरraपूर्णांकs list and call the notअगरication
		 * callbacks अगर needed
		 */
		apply_स्थिरraपूर्णांक(req, PM_QOS_REMOVE_REQ, PM_QOS_DEFAULT_VALUE);
		स_रखो(req, 0, माप(*req));
	पूर्ण

	c = &qos->latency_tolerance;
	plist_क्रम_each_entry_safe(req, पंचांगp, &c->list, data.pnode) अणु
		apply_स्थिरraपूर्णांक(req, PM_QOS_REMOVE_REQ, PM_QOS_DEFAULT_VALUE);
		स_रखो(req, 0, माप(*req));
	पूर्ण

	c = &qos->freq.min_freq;
	plist_क्रम_each_entry_safe(req, पंचांगp, &c->list, data.freq.pnode) अणु
		apply_स्थिरraपूर्णांक(req, PM_QOS_REMOVE_REQ,
				 PM_QOS_MIN_FREQUENCY_DEFAULT_VALUE);
		स_रखो(req, 0, माप(*req));
	पूर्ण

	c = &qos->freq.max_freq;
	plist_क्रम_each_entry_safe(req, पंचांगp, &c->list, data.freq.pnode) अणु
		apply_स्थिरraपूर्णांक(req, PM_QOS_REMOVE_REQ,
				 PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE);
		स_रखो(req, 0, माप(*req));
	पूर्ण

	f = &qos->flags;
	list_क्रम_each_entry_safe(req, पंचांगp, &f->list, data.flr.node) अणु
		apply_स्थिरraपूर्णांक(req, PM_QOS_REMOVE_REQ, PM_QOS_DEFAULT_VALUE);
		स_रखो(req, 0, माप(*req));
	पूर्ण

	spin_lock_irq(&dev->घातer.lock);
	dev->घातer.qos = ERR_PTR(-ENODEV);
	spin_unlock_irq(&dev->घातer.lock);

	kमुक्त(qos->resume_latency.notअगरiers);
	kमुक्त(qos);

 out:
	mutex_unlock(&dev_pm_qos_mtx);

	mutex_unlock(&dev_pm_qos_sysfs_mtx);
पूर्ण

अटल bool dev_pm_qos_invalid_req_type(काष्ठा device *dev,
					क्रमागत dev_pm_qos_req_type type)
अणु
	वापस type == DEV_PM_QOS_LATENCY_TOLERANCE &&
	       !dev->घातer.set_latency_tolerance;
पूर्ण

अटल पूर्णांक __dev_pm_qos_add_request(काष्ठा device *dev,
				    काष्ठा dev_pm_qos_request *req,
				    क्रमागत dev_pm_qos_req_type type, s32 value)
अणु
	पूर्णांक ret = 0;

	अगर (!dev || !req || dev_pm_qos_invalid_req_type(dev, type))
		वापस -EINVAL;

	अगर (WARN(dev_pm_qos_request_active(req),
		 "%s() called for already added request\n", __func__))
		वापस -EINVAL;

	अगर (IS_ERR(dev->घातer.qos))
		ret = -ENODEV;
	अन्यथा अगर (!dev->घातer.qos)
		ret = dev_pm_qos_स्थिरraपूर्णांकs_allocate(dev);

	trace_dev_pm_qos_add_request(dev_name(dev), type, value);
	अगर (ret)
		वापस ret;

	req->dev = dev;
	req->type = type;
	अगर (req->type == DEV_PM_QOS_MIN_FREQUENCY)
		ret = freq_qos_add_request(&dev->घातer.qos->freq,
					   &req->data.freq,
					   FREQ_QOS_MIN, value);
	अन्यथा अगर (req->type == DEV_PM_QOS_MAX_FREQUENCY)
		ret = freq_qos_add_request(&dev->घातer.qos->freq,
					   &req->data.freq,
					   FREQ_QOS_MAX, value);
	अन्यथा
		ret = apply_स्थिरraपूर्णांक(req, PM_QOS_ADD_REQ, value);

	वापस ret;
पूर्ण

/**
 * dev_pm_qos_add_request - inserts new qos request पूर्णांकo the list
 * @dev: target device क्रम the स्थिरraपूर्णांक
 * @req: poपूर्णांकer to a pपुनः_स्मृतिated handle
 * @type: type of the request
 * @value: defines the qos request
 *
 * This function inserts a new entry in the device स्थिरraपूर्णांकs list of
 * requested qos perक्रमmance अक्षरacteristics. It recomputes the aggregate
 * QoS expectations of parameters and initializes the dev_pm_qos_request
 * handle.  Caller needs to save this handle क्रम later use in updates and
 * removal.
 *
 * Returns 1 अगर the aggregated स्थिरraपूर्णांक value has changed,
 * 0 अगर the aggregated स्थिरraपूर्णांक value has not changed,
 * -EINVAL in हाल of wrong parameters, -ENOMEM अगर there's not enough memory
 * to allocate क्रम data काष्ठाures, -ENODEV अगर the device has just been हटाओd
 * from the प्रणाली.
 *
 * Callers should ensure that the target device is not RPM_SUSPENDED beक्रमe
 * using this function क्रम requests of type DEV_PM_QOS_FLAGS.
 */
पूर्णांक dev_pm_qos_add_request(काष्ठा device *dev, काष्ठा dev_pm_qos_request *req,
			   क्रमागत dev_pm_qos_req_type type, s32 value)
अणु
	पूर्णांक ret;

	mutex_lock(&dev_pm_qos_mtx);
	ret = __dev_pm_qos_add_request(dev, req, type, value);
	mutex_unlock(&dev_pm_qos_mtx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_add_request);

/**
 * __dev_pm_qos_update_request - Modअगरy an existing device PM QoS request.
 * @req : PM QoS request to modअगरy.
 * @new_value: New value to request.
 */
अटल पूर्णांक __dev_pm_qos_update_request(काष्ठा dev_pm_qos_request *req,
				       s32 new_value)
अणु
	s32 curr_value;
	पूर्णांक ret = 0;

	अगर (!req) /*guard against callers passing in null */
		वापस -EINVAL;

	अगर (WARN(!dev_pm_qos_request_active(req),
		 "%s() called for unknown object\n", __func__))
		वापस -EINVAL;

	अगर (IS_ERR_OR_शून्य(req->dev->घातer.qos))
		वापस -ENODEV;

	चयन(req->type) अणु
	हाल DEV_PM_QOS_RESUME_LATENCY:
	हाल DEV_PM_QOS_LATENCY_TOLERANCE:
		curr_value = req->data.pnode.prio;
		अवरोध;
	हाल DEV_PM_QOS_MIN_FREQUENCY:
	हाल DEV_PM_QOS_MAX_FREQUENCY:
		curr_value = req->data.freq.pnode.prio;
		अवरोध;
	हाल DEV_PM_QOS_FLAGS:
		curr_value = req->data.flr.flags;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	trace_dev_pm_qos_update_request(dev_name(req->dev), req->type,
					new_value);
	अगर (curr_value != new_value)
		ret = apply_स्थिरraपूर्णांक(req, PM_QOS_UPDATE_REQ, new_value);

	वापस ret;
पूर्ण

/**
 * dev_pm_qos_update_request - modअगरies an existing qos request
 * @req : handle to list element holding a dev_pm_qos request to use
 * @new_value: defines the qos request
 *
 * Updates an existing dev PM qos request aदीर्घ with updating the
 * target value.
 *
 * Attempts are made to make this code callable on hot code paths.
 *
 * Returns 1 अगर the aggregated स्थिरraपूर्णांक value has changed,
 * 0 अगर the aggregated स्थिरraपूर्णांक value has not changed,
 * -EINVAL in हाल of wrong parameters, -ENODEV अगर the device has been
 * हटाओd from the प्रणाली
 *
 * Callers should ensure that the target device is not RPM_SUSPENDED beक्रमe
 * using this function क्रम requests of type DEV_PM_QOS_FLAGS.
 */
पूर्णांक dev_pm_qos_update_request(काष्ठा dev_pm_qos_request *req, s32 new_value)
अणु
	पूर्णांक ret;

	mutex_lock(&dev_pm_qos_mtx);
	ret = __dev_pm_qos_update_request(req, new_value);
	mutex_unlock(&dev_pm_qos_mtx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_update_request);

अटल पूर्णांक __dev_pm_qos_हटाओ_request(काष्ठा dev_pm_qos_request *req)
अणु
	पूर्णांक ret;

	अगर (!req) /*guard against callers passing in null */
		वापस -EINVAL;

	अगर (WARN(!dev_pm_qos_request_active(req),
		 "%s() called for unknown object\n", __func__))
		वापस -EINVAL;

	अगर (IS_ERR_OR_शून्य(req->dev->घातer.qos))
		वापस -ENODEV;

	trace_dev_pm_qos_हटाओ_request(dev_name(req->dev), req->type,
					PM_QOS_DEFAULT_VALUE);
	ret = apply_स्थिरraपूर्णांक(req, PM_QOS_REMOVE_REQ, PM_QOS_DEFAULT_VALUE);
	स_रखो(req, 0, माप(*req));
	वापस ret;
पूर्ण

/**
 * dev_pm_qos_हटाओ_request - modअगरies an existing qos request
 * @req: handle to request list element
 *
 * Will हटाओ pm qos request from the list of स्थिरraपूर्णांकs and
 * recompute the current target value. Call this on slow code paths.
 *
 * Returns 1 अगर the aggregated स्थिरraपूर्णांक value has changed,
 * 0 अगर the aggregated स्थिरraपूर्णांक value has not changed,
 * -EINVAL in हाल of wrong parameters, -ENODEV अगर the device has been
 * हटाओd from the प्रणाली
 *
 * Callers should ensure that the target device is not RPM_SUSPENDED beक्रमe
 * using this function क्रम requests of type DEV_PM_QOS_FLAGS.
 */
पूर्णांक dev_pm_qos_हटाओ_request(काष्ठा dev_pm_qos_request *req)
अणु
	पूर्णांक ret;

	mutex_lock(&dev_pm_qos_mtx);
	ret = __dev_pm_qos_हटाओ_request(req);
	mutex_unlock(&dev_pm_qos_mtx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_हटाओ_request);

/**
 * dev_pm_qos_add_notअगरier - sets notअगरication entry क्रम changes to target value
 * of per-device PM QoS स्थिरraपूर्णांकs
 *
 * @dev: target device क्रम the स्थिरraपूर्णांक
 * @notअगरier: notअगरier block managed by caller.
 * @type: request type.
 *
 * Will रेजिस्टर the notअगरier पूर्णांकo a notअगरication chain that माला_लो called
 * upon changes to the target value क्रम the device.
 *
 * If the device's constraints object doesn't exist when this routine is called,
 * it will be created (or error code will be वापसed अगर that fails).
 */
पूर्णांक dev_pm_qos_add_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *notअगरier,
			    क्रमागत dev_pm_qos_req_type type)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&dev_pm_qos_mtx);

	अगर (IS_ERR(dev->घातer.qos))
		ret = -ENODEV;
	अन्यथा अगर (!dev->घातer.qos)
		ret = dev_pm_qos_स्थिरraपूर्णांकs_allocate(dev);

	अगर (ret)
		जाओ unlock;

	चयन (type) अणु
	हाल DEV_PM_QOS_RESUME_LATENCY:
		ret = blocking_notअगरier_chain_रेजिस्टर(dev->घातer.qos->resume_latency.notअगरiers,
						       notअगरier);
		अवरोध;
	हाल DEV_PM_QOS_MIN_FREQUENCY:
		ret = freq_qos_add_notअगरier(&dev->घातer.qos->freq,
					    FREQ_QOS_MIN, notअगरier);
		अवरोध;
	हाल DEV_PM_QOS_MAX_FREQUENCY:
		ret = freq_qos_add_notअगरier(&dev->घातer.qos->freq,
					    FREQ_QOS_MAX, notअगरier);
		अवरोध;
	शेष:
		WARN_ON(1);
		ret = -EINVAL;
	पूर्ण

unlock:
	mutex_unlock(&dev_pm_qos_mtx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_add_notअगरier);

/**
 * dev_pm_qos_हटाओ_notअगरier - deletes notअगरication क्रम changes to target value
 * of per-device PM QoS स्थिरraपूर्णांकs
 *
 * @dev: target device क्रम the स्थिरraपूर्णांक
 * @notअगरier: notअगरier block to be हटाओd.
 * @type: request type.
 *
 * Will हटाओ the notअगरier from the notअगरication chain that माला_लो called
 * upon changes to the target value.
 */
पूर्णांक dev_pm_qos_हटाओ_notअगरier(काष्ठा device *dev,
			       काष्ठा notअगरier_block *notअगरier,
			       क्रमागत dev_pm_qos_req_type type)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&dev_pm_qos_mtx);

	/* Silently वापस अगर the स्थिरraपूर्णांकs object is not present. */
	अगर (IS_ERR_OR_शून्य(dev->घातer.qos))
		जाओ unlock;

	चयन (type) अणु
	हाल DEV_PM_QOS_RESUME_LATENCY:
		ret = blocking_notअगरier_chain_unरेजिस्टर(dev->घातer.qos->resume_latency.notअगरiers,
							 notअगरier);
		अवरोध;
	हाल DEV_PM_QOS_MIN_FREQUENCY:
		ret = freq_qos_हटाओ_notअगरier(&dev->घातer.qos->freq,
					       FREQ_QOS_MIN, notअगरier);
		अवरोध;
	हाल DEV_PM_QOS_MAX_FREQUENCY:
		ret = freq_qos_हटाओ_notअगरier(&dev->घातer.qos->freq,
					       FREQ_QOS_MAX, notअगरier);
		अवरोध;
	शेष:
		WARN_ON(1);
		ret = -EINVAL;
	पूर्ण

unlock:
	mutex_unlock(&dev_pm_qos_mtx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_हटाओ_notअगरier);

/**
 * dev_pm_qos_add_ancestor_request - Add PM QoS request क्रम device's ancestor.
 * @dev: Device whose ancestor to add the request क्रम.
 * @req: Poपूर्णांकer to the pपुनः_स्मृतिated handle.
 * @type: Type of the request.
 * @value: Constraपूर्णांक latency value.
 */
पूर्णांक dev_pm_qos_add_ancestor_request(काष्ठा device *dev,
				    काष्ठा dev_pm_qos_request *req,
				    क्रमागत dev_pm_qos_req_type type, s32 value)
अणु
	काष्ठा device *ancestor = dev->parent;
	पूर्णांक ret = -ENODEV;

	चयन (type) अणु
	हाल DEV_PM_QOS_RESUME_LATENCY:
		जबतक (ancestor && !ancestor->घातer.ignore_children)
			ancestor = ancestor->parent;

		अवरोध;
	हाल DEV_PM_QOS_LATENCY_TOLERANCE:
		जबतक (ancestor && !ancestor->घातer.set_latency_tolerance)
			ancestor = ancestor->parent;

		अवरोध;
	शेष:
		ancestor = शून्य;
	पूर्ण
	अगर (ancestor)
		ret = dev_pm_qos_add_request(ancestor, req, type, value);

	अगर (ret < 0)
		req->dev = शून्य;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_add_ancestor_request);

अटल व्योम __dev_pm_qos_drop_user_request(काष्ठा device *dev,
					   क्रमागत dev_pm_qos_req_type type)
अणु
	काष्ठा dev_pm_qos_request *req = शून्य;

	चयन(type) अणु
	हाल DEV_PM_QOS_RESUME_LATENCY:
		req = dev->घातer.qos->resume_latency_req;
		dev->घातer.qos->resume_latency_req = शून्य;
		अवरोध;
	हाल DEV_PM_QOS_LATENCY_TOLERANCE:
		req = dev->घातer.qos->latency_tolerance_req;
		dev->घातer.qos->latency_tolerance_req = शून्य;
		अवरोध;
	हाल DEV_PM_QOS_FLAGS:
		req = dev->घातer.qos->flags_req;
		dev->घातer.qos->flags_req = शून्य;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण
	__dev_pm_qos_हटाओ_request(req);
	kमुक्त(req);
पूर्ण

अटल व्योम dev_pm_qos_drop_user_request(काष्ठा device *dev,
					 क्रमागत dev_pm_qos_req_type type)
अणु
	mutex_lock(&dev_pm_qos_mtx);
	__dev_pm_qos_drop_user_request(dev, type);
	mutex_unlock(&dev_pm_qos_mtx);
पूर्ण

/**
 * dev_pm_qos_expose_latency_limit - Expose PM QoS latency limit to user space.
 * @dev: Device whose PM QoS latency limit is to be exposed to user space.
 * @value: Initial value of the latency limit.
 */
पूर्णांक dev_pm_qos_expose_latency_limit(काष्ठा device *dev, s32 value)
अणु
	काष्ठा dev_pm_qos_request *req;
	पूर्णांक ret;

	अगर (!device_is_रेजिस्टरed(dev) || value < 0)
		वापस -EINVAL;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	ret = dev_pm_qos_add_request(dev, req, DEV_PM_QOS_RESUME_LATENCY, value);
	अगर (ret < 0) अणु
		kमुक्त(req);
		वापस ret;
	पूर्ण

	mutex_lock(&dev_pm_qos_sysfs_mtx);

	mutex_lock(&dev_pm_qos_mtx);

	अगर (IS_ERR_OR_शून्य(dev->घातer.qos))
		ret = -ENODEV;
	अन्यथा अगर (dev->घातer.qos->resume_latency_req)
		ret = -EEXIST;

	अगर (ret < 0) अणु
		__dev_pm_qos_हटाओ_request(req);
		kमुक्त(req);
		mutex_unlock(&dev_pm_qos_mtx);
		जाओ out;
	पूर्ण
	dev->घातer.qos->resume_latency_req = req;

	mutex_unlock(&dev_pm_qos_mtx);

	ret = pm_qos_sysfs_add_resume_latency(dev);
	अगर (ret)
		dev_pm_qos_drop_user_request(dev, DEV_PM_QOS_RESUME_LATENCY);

 out:
	mutex_unlock(&dev_pm_qos_sysfs_mtx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_expose_latency_limit);

अटल व्योम __dev_pm_qos_hide_latency_limit(काष्ठा device *dev)
अणु
	अगर (!IS_ERR_OR_शून्य(dev->घातer.qos) && dev->घातer.qos->resume_latency_req)
		__dev_pm_qos_drop_user_request(dev, DEV_PM_QOS_RESUME_LATENCY);
पूर्ण

/**
 * dev_pm_qos_hide_latency_limit - Hide PM QoS latency limit from user space.
 * @dev: Device whose PM QoS latency limit is to be hidden from user space.
 */
व्योम dev_pm_qos_hide_latency_limit(काष्ठा device *dev)
अणु
	mutex_lock(&dev_pm_qos_sysfs_mtx);

	pm_qos_sysfs_हटाओ_resume_latency(dev);

	mutex_lock(&dev_pm_qos_mtx);
	__dev_pm_qos_hide_latency_limit(dev);
	mutex_unlock(&dev_pm_qos_mtx);

	mutex_unlock(&dev_pm_qos_sysfs_mtx);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_hide_latency_limit);

/**
 * dev_pm_qos_expose_flags - Expose PM QoS flags of a device to user space.
 * @dev: Device whose PM QoS flags are to be exposed to user space.
 * @val: Initial values of the flags.
 */
पूर्णांक dev_pm_qos_expose_flags(काष्ठा device *dev, s32 val)
अणु
	काष्ठा dev_pm_qos_request *req;
	पूर्णांक ret;

	अगर (!device_is_रेजिस्टरed(dev))
		वापस -EINVAL;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	ret = dev_pm_qos_add_request(dev, req, DEV_PM_QOS_FLAGS, val);
	अगर (ret < 0) अणु
		kमुक्त(req);
		वापस ret;
	पूर्ण

	pm_runसमय_get_sync(dev);
	mutex_lock(&dev_pm_qos_sysfs_mtx);

	mutex_lock(&dev_pm_qos_mtx);

	अगर (IS_ERR_OR_शून्य(dev->घातer.qos))
		ret = -ENODEV;
	अन्यथा अगर (dev->घातer.qos->flags_req)
		ret = -EEXIST;

	अगर (ret < 0) अणु
		__dev_pm_qos_हटाओ_request(req);
		kमुक्त(req);
		mutex_unlock(&dev_pm_qos_mtx);
		जाओ out;
	पूर्ण
	dev->घातer.qos->flags_req = req;

	mutex_unlock(&dev_pm_qos_mtx);

	ret = pm_qos_sysfs_add_flags(dev);
	अगर (ret)
		dev_pm_qos_drop_user_request(dev, DEV_PM_QOS_FLAGS);

 out:
	mutex_unlock(&dev_pm_qos_sysfs_mtx);
	pm_runसमय_put(dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_expose_flags);

अटल व्योम __dev_pm_qos_hide_flags(काष्ठा device *dev)
अणु
	अगर (!IS_ERR_OR_शून्य(dev->घातer.qos) && dev->घातer.qos->flags_req)
		__dev_pm_qos_drop_user_request(dev, DEV_PM_QOS_FLAGS);
पूर्ण

/**
 * dev_pm_qos_hide_flags - Hide PM QoS flags of a device from user space.
 * @dev: Device whose PM QoS flags are to be hidden from user space.
 */
व्योम dev_pm_qos_hide_flags(काष्ठा device *dev)
अणु
	pm_runसमय_get_sync(dev);
	mutex_lock(&dev_pm_qos_sysfs_mtx);

	pm_qos_sysfs_हटाओ_flags(dev);

	mutex_lock(&dev_pm_qos_mtx);
	__dev_pm_qos_hide_flags(dev);
	mutex_unlock(&dev_pm_qos_mtx);

	mutex_unlock(&dev_pm_qos_sysfs_mtx);
	pm_runसमय_put(dev);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_hide_flags);

/**
 * dev_pm_qos_update_flags - Update PM QoS flags request owned by user space.
 * @dev: Device to update the PM QoS flags request क्रम.
 * @mask: Flags to set/clear.
 * @set: Whether to set or clear the flags (true means set).
 */
पूर्णांक dev_pm_qos_update_flags(काष्ठा device *dev, s32 mask, bool set)
अणु
	s32 value;
	पूर्णांक ret;

	pm_runसमय_get_sync(dev);
	mutex_lock(&dev_pm_qos_mtx);

	अगर (IS_ERR_OR_शून्य(dev->घातer.qos) || !dev->घातer.qos->flags_req) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	value = dev_pm_qos_requested_flags(dev);
	अगर (set)
		value |= mask;
	अन्यथा
		value &= ~mask;

	ret = __dev_pm_qos_update_request(dev->घातer.qos->flags_req, value);

 out:
	mutex_unlock(&dev_pm_qos_mtx);
	pm_runसमय_put(dev);
	वापस ret;
पूर्ण

/**
 * dev_pm_qos_get_user_latency_tolerance - Get user space latency tolerance.
 * @dev: Device to obtain the user space latency tolerance क्रम.
 */
s32 dev_pm_qos_get_user_latency_tolerance(काष्ठा device *dev)
अणु
	s32 ret;

	mutex_lock(&dev_pm_qos_mtx);
	ret = IS_ERR_OR_शून्य(dev->घातer.qos)
		|| !dev->घातer.qos->latency_tolerance_req ?
			PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT :
			dev->घातer.qos->latency_tolerance_req->data.pnode.prio;
	mutex_unlock(&dev_pm_qos_mtx);
	वापस ret;
पूर्ण

/**
 * dev_pm_qos_update_user_latency_tolerance - Update user space latency tolerance.
 * @dev: Device to update the user space latency tolerance क्रम.
 * @val: New user space latency tolerance क्रम @dev (negative values disable).
 */
पूर्णांक dev_pm_qos_update_user_latency_tolerance(काष्ठा device *dev, s32 val)
अणु
	पूर्णांक ret;

	mutex_lock(&dev_pm_qos_mtx);

	अगर (IS_ERR_OR_शून्य(dev->घातer.qos)
	    || !dev->घातer.qos->latency_tolerance_req) अणु
		काष्ठा dev_pm_qos_request *req;

		अगर (val < 0) अणु
			अगर (val == PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT)
				ret = 0;
			अन्यथा
				ret = -EINVAL;
			जाओ out;
		पूर्ण
		req = kzalloc(माप(*req), GFP_KERNEL);
		अगर (!req) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		ret = __dev_pm_qos_add_request(dev, req, DEV_PM_QOS_LATENCY_TOLERANCE, val);
		अगर (ret < 0) अणु
			kमुक्त(req);
			जाओ out;
		पूर्ण
		dev->घातer.qos->latency_tolerance_req = req;
	पूर्ण अन्यथा अणु
		अगर (val < 0) अणु
			__dev_pm_qos_drop_user_request(dev, DEV_PM_QOS_LATENCY_TOLERANCE);
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = __dev_pm_qos_update_request(dev->घातer.qos->latency_tolerance_req, val);
		पूर्ण
	पूर्ण

 out:
	mutex_unlock(&dev_pm_qos_mtx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_update_user_latency_tolerance);

/**
 * dev_pm_qos_expose_latency_tolerance - Expose latency tolerance to userspace
 * @dev: Device whose latency tolerance to expose
 */
पूर्णांक dev_pm_qos_expose_latency_tolerance(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (!dev->घातer.set_latency_tolerance)
		वापस -EINVAL;

	mutex_lock(&dev_pm_qos_sysfs_mtx);
	ret = pm_qos_sysfs_add_latency_tolerance(dev);
	mutex_unlock(&dev_pm_qos_sysfs_mtx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_expose_latency_tolerance);

/**
 * dev_pm_qos_hide_latency_tolerance - Hide latency tolerance from userspace
 * @dev: Device whose latency tolerance to hide
 */
व्योम dev_pm_qos_hide_latency_tolerance(काष्ठा device *dev)
अणु
	mutex_lock(&dev_pm_qos_sysfs_mtx);
	pm_qos_sysfs_हटाओ_latency_tolerance(dev);
	mutex_unlock(&dev_pm_qos_sysfs_mtx);

	/* Remove the request from user space now */
	pm_runसमय_get_sync(dev);
	dev_pm_qos_update_user_latency_tolerance(dev,
		PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT);
	pm_runसमय_put(dev);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_qos_hide_latency_tolerance);
