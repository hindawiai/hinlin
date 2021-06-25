<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Registration and callback क्रम the s390 common I/O layer.
 *
 * Copyright IBM Corp. 2002, 2010
 */

#घोषणा KMSG_COMPONENT "zfcp"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश "zfcp_ext.h"
#समावेश "zfcp_reqlist.h"

#घोषणा ZFCP_MODEL_PRIV 0x4

अटल DEFINE_SPINLOCK(zfcp_ccw_adapter_ref_lock);

काष्ठा zfcp_adapter *zfcp_ccw_adapter_by_cdev(काष्ठा ccw_device *cdev)
अणु
	काष्ठा zfcp_adapter *adapter;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&zfcp_ccw_adapter_ref_lock, flags);
	adapter = dev_get_drvdata(&cdev->dev);
	अगर (adapter)
		kref_get(&adapter->ref);
	spin_unlock_irqrestore(&zfcp_ccw_adapter_ref_lock, flags);
	वापस adapter;
पूर्ण

व्योम zfcp_ccw_adapter_put(काष्ठा zfcp_adapter *adapter)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&zfcp_ccw_adapter_ref_lock, flags);
	kref_put(&adapter->ref, zfcp_adapter_release);
	spin_unlock_irqrestore(&zfcp_ccw_adapter_ref_lock, flags);
पूर्ण

/**
 * zfcp_ccw_activate - activate adapter and रुको क्रम it to finish
 * @cdev: poपूर्णांकer to beदीर्घing ccw device
 * @clear: Status flags to clear.
 * @tag: s390dbf trace record tag
 */
अटल पूर्णांक zfcp_ccw_activate(काष्ठा ccw_device *cdev, पूर्णांक clear, अक्षर *tag)
अणु
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	अगर (!adapter)
		वापस 0;

	zfcp_erp_clear_adapter_status(adapter, clear);
	zfcp_erp_set_adapter_status(adapter, ZFCP_STATUS_COMMON_RUNNING);
	zfcp_erp_adapter_reखोलो(adapter, ZFCP_STATUS_COMMON_ERP_FAILED,
				tag);

	/*
	 * We want to scan ports here, with some अक्रमom backoff and without
	 * rate limit. Recovery has alपढ़ोy scheduled a port scan क्रम us,
	 * but with both अक्रमom delay and rate limit. Nevertheless we get
	 * what we want here by flushing the scheduled work after sleeping
	 * an equivalent अक्रमom समय.
	 * Let the port scan अक्रमom delay elapse first. If recovery finishes
	 * up to that poपूर्णांक in समय, that would be perfect क्रम both recovery
	 * and port scan. If not, i.e. recovery takes ages, there was no
	 * poपूर्णांक in रुकोing a अक्रमom delay on top of the समय consumed by
	 * recovery.
	 */
	msleep(zfcp_fc_port_scan_backoff());
	zfcp_erp_रुको(adapter);
	flush_delayed_work(&adapter->scan_work);

	zfcp_ccw_adapter_put(adapter);

	वापस 0;
पूर्ण

अटल काष्ठा ccw_device_id zfcp_ccw_device_id[] = अणु
	अणु CCW_DEVICE_DEVTYPE(0x1731, 0x3, 0x1732, 0x3) पूर्ण,
	अणु CCW_DEVICE_DEVTYPE(0x1731, 0x3, 0x1732, ZFCP_MODEL_PRIV) पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ccw, zfcp_ccw_device_id);

/**
 * zfcp_ccw_probe - probe function of zfcp driver
 * @cdev: poपूर्णांकer to beदीर्घing ccw device
 *
 * This function माला_लो called by the common i/o layer क्रम each FCP
 * device found on the current प्रणाली. This is only a stub to make cio
 * work: To only allocate adapter resources क्रम devices actually used,
 * the allocation is deferred to the first call to ccw_set_online.
 */
अटल पूर्णांक zfcp_ccw_probe(काष्ठा ccw_device *cdev)
अणु
	वापस 0;
पूर्ण

/**
 * zfcp_ccw_हटाओ - हटाओ function of zfcp driver
 * @cdev: poपूर्णांकer to beदीर्घing ccw device
 *
 * This function माला_लो called by the common i/o layer and हटाओs an adapter
 * from the प्रणाली. Task of this function is to get rid of all units and
 * ports that beदीर्घ to this adapter. And in addition all resources of this
 * adapter will be मुक्तd too.
 */
अटल व्योम zfcp_ccw_हटाओ(काष्ठा ccw_device *cdev)
अणु
	काष्ठा zfcp_adapter *adapter;
	काष्ठा zfcp_port *port, *p;
	काष्ठा zfcp_unit *unit, *u;
	LIST_HEAD(unit_हटाओ_lh);
	LIST_HEAD(port_हटाओ_lh);

	ccw_device_set_offline(cdev);

	adapter = zfcp_ccw_adapter_by_cdev(cdev);
	अगर (!adapter)
		वापस;

	ग_लिखो_lock_irq(&adapter->port_list_lock);
	list_क्रम_each_entry(port, &adapter->port_list, list) अणु
		ग_लिखो_lock(&port->unit_list_lock);
		list_splice_init(&port->unit_list, &unit_हटाओ_lh);
		ग_लिखो_unlock(&port->unit_list_lock);
	पूर्ण
	list_splice_init(&adapter->port_list, &port_हटाओ_lh);
	ग_लिखो_unlock_irq(&adapter->port_list_lock);
	zfcp_ccw_adapter_put(adapter); /* put from zfcp_ccw_adapter_by_cdev */

	list_क्रम_each_entry_safe(unit, u, &unit_हटाओ_lh, list)
		device_unरेजिस्टर(&unit->dev);

	list_क्रम_each_entry_safe(port, p, &port_हटाओ_lh, list)
		device_unरेजिस्टर(&port->dev);

	zfcp_adapter_unरेजिस्टर(adapter);
पूर्ण

/**
 * zfcp_ccw_set_online - set_online function of zfcp driver
 * @cdev: poपूर्णांकer to beदीर्घing ccw device
 *
 * This function माला_लो called by the common i/o layer and sets an
 * adapter पूर्णांकo state online.  The first call will allocate all
 * adapter resources that will be retained until the device is हटाओd
 * via zfcp_ccw_हटाओ.
 *
 * Setting an fcp device online means that it will be रेजिस्टरed with
 * the SCSI stack, that the QDIO queues will be set up and that the
 * adapter will be खोलोed.
 */
अटल पूर्णांक zfcp_ccw_set_online(काष्ठा ccw_device *cdev)
अणु
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	अगर (!adapter) अणु
		adapter = zfcp_adapter_enqueue(cdev);

		अगर (IS_ERR(adapter)) अणु
			dev_err(&cdev->dev,
				"Setting up data structures for the "
				"FCP adapter failed\n");
			वापस PTR_ERR(adapter);
		पूर्ण
		kref_get(&adapter->ref);
	पूर्ण

	/* initialize request counter */
	BUG_ON(!zfcp_reqlist_isempty(adapter->req_list));
	adapter->req_no = 0;

	zfcp_ccw_activate(cdev, 0, "ccsonl1");

	/*
	 * We want to scan ports here, always, with some अक्रमom delay and
	 * without rate limit - basically what zfcp_ccw_activate() has
	 * achieved क्रम us. Not quite! That port scan depended on
	 * !no_स्वतः_port_rescan. So let's cover the no_स्वतः_port_rescan
	 * हाल here to make sure a port scan is करोne unconditionally.
	 * Since zfcp_ccw_activate() has रुकोed the desired अक्रमom समय,
	 * we can immediately schedule and flush a port scan क्रम the
	 * reमुख्यing हालs.
	 */
	zfcp_fc_inverse_conditional_port_scan(adapter);
	flush_delayed_work(&adapter->scan_work);
	zfcp_ccw_adapter_put(adapter);
	वापस 0;
पूर्ण

/**
 * zfcp_ccw_set_offline - set_offline function of zfcp driver
 * @cdev: poपूर्णांकer to beदीर्घing ccw device
 *
 * This function माला_लो called by the common i/o layer and sets an adapter
 * पूर्णांकo state offline.
 */
अटल पूर्णांक zfcp_ccw_set_offline(काष्ठा ccw_device *cdev)
अणु
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	अगर (!adapter)
		वापस 0;

	zfcp_erp_set_adapter_status(adapter, 0);
	zfcp_erp_adapter_shutकरोwn(adapter, 0, "ccsoff1");
	zfcp_erp_रुको(adapter);

	zfcp_ccw_adapter_put(adapter);
	वापस 0;
पूर्ण

/**
 * zfcp_ccw_notअगरy - ccw notअगरy function
 * @cdev: poपूर्णांकer to beदीर्घing ccw device
 * @event: indicates अगर adapter was detached or attached
 *
 * This function माला_लो called by the common i/o layer अगर an adapter has gone
 * or reappeared.
 */
अटल पूर्णांक zfcp_ccw_notअगरy(काष्ठा ccw_device *cdev, पूर्णांक event)
अणु
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	अगर (!adapter)
		वापस 1;

	चयन (event) अणु
	हाल CIO_GONE:
		dev_warn(&cdev->dev, "The FCP device has been detached\n");
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "ccnoti1");
		अवरोध;
	हाल CIO_NO_PATH:
		dev_warn(&cdev->dev,
			 "The CHPID for the FCP device is offline\n");
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "ccnoti2");
		अवरोध;
	हाल CIO_OPER:
		dev_info(&cdev->dev, "The FCP device is operational again\n");
		zfcp_erp_set_adapter_status(adapter,
					    ZFCP_STATUS_COMMON_RUNNING);
		zfcp_erp_adapter_reखोलो(adapter, ZFCP_STATUS_COMMON_ERP_FAILED,
					"ccnoti4");
		अवरोध;
	हाल CIO_BOXED:
		dev_warn(&cdev->dev, "The FCP device did not respond within "
				     "the specified time\n");
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "ccnoti5");
		अवरोध;
	पूर्ण

	zfcp_ccw_adapter_put(adapter);
	वापस 1;
पूर्ण

/**
 * zfcp_ccw_shutकरोwn - handle shutकरोwn from cio
 * @cdev: device क्रम adapter to shutकरोwn.
 */
अटल व्योम zfcp_ccw_shutकरोwn(काष्ठा ccw_device *cdev)
अणु
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	अगर (!adapter)
		वापस;

	zfcp_erp_adapter_shutकरोwn(adapter, 0, "ccshut1");
	zfcp_erp_रुको(adapter);
	zfcp_erp_thपढ़ो_समाप्त(adapter);

	zfcp_ccw_adapter_put(adapter);
पूर्ण

काष्ठा ccw_driver zfcp_ccw_driver = अणु
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= "zfcp",
	पूर्ण,
	.ids         = zfcp_ccw_device_id,
	.probe       = zfcp_ccw_probe,
	.हटाओ      = zfcp_ccw_हटाओ,
	.set_online  = zfcp_ccw_set_online,
	.set_offline = zfcp_ccw_set_offline,
	.notअगरy      = zfcp_ccw_notअगरy,
	.shutकरोwn    = zfcp_ccw_shutकरोwn,
पूर्ण;
