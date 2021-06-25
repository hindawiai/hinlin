<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012-2019, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mei_cl_bus.h>

#समावेश "mei_dev.h"
#समावेश "client.h"

#घोषणा to_mei_cl_driver(d) container_of(d, काष्ठा mei_cl_driver, driver)

/**
 * __mei_cl_send - पूर्णांकernal client send (ग_लिखो)
 *
 * @cl: host client
 * @buf: buffer to send
 * @length: buffer length
 * @vtag: भव tag
 * @mode: sending mode
 *
 * Return: written size bytes or < 0 on error
 */
sमाप_प्रकार __mei_cl_send(काष्ठा mei_cl *cl, u8 *buf, माप_प्रकार length, u8 vtag,
		      अचिन्हित पूर्णांक mode)
अणु
	काष्ठा mei_device *bus;
	काष्ठा mei_cl_cb *cb;
	sमाप_प्रकार rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	bus = cl->dev;

	mutex_lock(&bus->device_lock);
	अगर (bus->dev_state != MEI_DEV_ENABLED &&
	    bus->dev_state != MEI_DEV_POWERING_DOWN) अणु
		rets = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!mei_cl_is_connected(cl)) अणु
		rets = -ENODEV;
		जाओ out;
	पूर्ण

	/* Check अगर we have an ME client device */
	अगर (!mei_me_cl_is_active(cl->me_cl)) अणु
		rets = -ENOTTY;
		जाओ out;
	पूर्ण

	अगर (vtag) अणु
		/* Check अगर vtag is supported by client */
		rets = mei_cl_vt_support_check(cl);
		अगर (rets)
			जाओ out;
	पूर्ण

	अगर (length > mei_cl_mtu(cl)) अणु
		rets = -EFBIG;
		जाओ out;
	पूर्ण

	जबतक (cl->tx_cb_queued >= bus->tx_queue_limit) अणु
		mutex_unlock(&bus->device_lock);
		rets = रुको_event_पूर्णांकerruptible(cl->tx_रुको,
				cl->writing_state == MEI_WRITE_COMPLETE ||
				(!mei_cl_is_connected(cl)));
		mutex_lock(&bus->device_lock);
		अगर (rets) अणु
			अगर (संकेत_pending(current))
				rets = -EINTR;
			जाओ out;
		पूर्ण
		अगर (!mei_cl_is_connected(cl)) अणु
			rets = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण

	cb = mei_cl_alloc_cb(cl, length, MEI_FOP_WRITE, शून्य);
	अगर (!cb) अणु
		rets = -ENOMEM;
		जाओ out;
	पूर्ण
	cb->vtag = vtag;

	cb->पूर्णांकernal = !!(mode & MEI_CL_IO_TX_INTERNAL);
	cb->blocking = !!(mode & MEI_CL_IO_TX_BLOCKING);
	स_नकल(cb->buf.data, buf, length);

	rets = mei_cl_ग_लिखो(cl, cb);

out:
	mutex_unlock(&bus->device_lock);

	वापस rets;
पूर्ण

/**
 * __mei_cl_recv - पूर्णांकernal client receive (पढ़ो)
 *
 * @cl: host client
 * @buf: buffer to receive
 * @length: buffer length
 * @mode: io mode
 * @vtag: भव tag
 * @समयout: recv समयout, 0 क्रम infinite समयout
 *
 * Return: पढ़ो size in bytes of < 0 on error
 */
sमाप_प्रकार __mei_cl_recv(काष्ठा mei_cl *cl, u8 *buf, माप_प्रकार length, u8 *vtag,
		      अचिन्हित पूर्णांक mode, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा mei_device *bus;
	काष्ठा mei_cl_cb *cb;
	माप_प्रकार r_length;
	sमाप_प्रकार rets;
	bool nonblock = !!(mode & MEI_CL_IO_RX_NONBLOCK);

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	bus = cl->dev;

	mutex_lock(&bus->device_lock);
	अगर (bus->dev_state != MEI_DEV_ENABLED &&
	    bus->dev_state != MEI_DEV_POWERING_DOWN) अणु
		rets = -ENODEV;
		जाओ out;
	पूर्ण

	cb = mei_cl_पढ़ो_cb(cl, शून्य);
	अगर (cb)
		जाओ copy;

	rets = mei_cl_पढ़ो_start(cl, length, शून्य);
	अगर (rets && rets != -EBUSY)
		जाओ out;

	अगर (nonblock) अणु
		rets = -EAGAIN;
		जाओ out;
	पूर्ण

	/* रुको on event only अगर there is no other रुकोer */
	/* synchronized under device mutex */
	अगर (!रुकोqueue_active(&cl->rx_रुको)) अणु

		mutex_unlock(&bus->device_lock);

		अगर (समयout) अणु
			rets = रुको_event_पूर्णांकerruptible_समयout
					(cl->rx_रुको,
					mei_cl_पढ़ो_cb(cl, शून्य) ||
					(!mei_cl_is_connected(cl)),
					msecs_to_jअगरfies(समयout));
			अगर (rets == 0)
				वापस -ETIME;
			अगर (rets < 0) अणु
				अगर (संकेत_pending(current))
					वापस -EINTR;
				वापस -ERESTARTSYS;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (रुको_event_पूर्णांकerruptible
					(cl->rx_रुको,
					mei_cl_पढ़ो_cb(cl, शून्य) ||
					(!mei_cl_is_connected(cl)))) अणु
				अगर (संकेत_pending(current))
					वापस -EINTR;
				वापस -ERESTARTSYS;
			पूर्ण
		पूर्ण

		mutex_lock(&bus->device_lock);

		अगर (!mei_cl_is_connected(cl)) अणु
			rets = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण

	cb = mei_cl_पढ़ो_cb(cl, शून्य);
	अगर (!cb) अणु
		rets = 0;
		जाओ out;
	पूर्ण

copy:
	अगर (cb->status) अणु
		rets = cb->status;
		जाओ मुक्त;
	पूर्ण

	r_length = min_t(माप_प्रकार, length, cb->buf_idx);
	स_नकल(buf, cb->buf.data, r_length);
	rets = r_length;
	अगर (vtag)
		*vtag = cb->vtag;

मुक्त:
	mei_cl_del_rd_completed(cl, cb);
out:
	mutex_unlock(&bus->device_lock);

	वापस rets;
पूर्ण

/**
 * mei_cldev_send_vtag - me device send with vtag  (ग_लिखो)
 *
 * @cldev: me client device
 * @buf: buffer to send
 * @length: buffer length
 * @vtag: भव tag
 *
 * Return:
 *  * written size in bytes
 *  * < 0 on error
 */

sमाप_प्रकार mei_cldev_send_vtag(काष्ठा mei_cl_device *cldev, u8 *buf, माप_प्रकार length,
			    u8 vtag)
अणु
	काष्ठा mei_cl *cl = cldev->cl;

	वापस __mei_cl_send(cl, buf, length, vtag, MEI_CL_IO_TX_BLOCKING);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_send_vtag);

/**
 * mei_cldev_recv_vtag - client receive with vtag (पढ़ो)
 *
 * @cldev: me client device
 * @buf: buffer to receive
 * @length: buffer length
 * @vtag: भव tag
 *
 * Return:
 * * पढ़ो size in bytes
 * *  < 0 on error
 */

sमाप_प्रकार mei_cldev_recv_vtag(काष्ठा mei_cl_device *cldev, u8 *buf, माप_प्रकार length,
			    u8 *vtag)
अणु
	काष्ठा mei_cl *cl = cldev->cl;

	वापस __mei_cl_recv(cl, buf, length, vtag, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_recv_vtag);

/**
 * mei_cldev_recv_nonblock_vtag - non block client receive with vtag (पढ़ो)
 *
 * @cldev: me client device
 * @buf: buffer to receive
 * @length: buffer length
 * @vtag: भव tag
 *
 * Return:
 * * पढ़ो size in bytes
 * * -EAGAIN अगर function will block.
 * * < 0 on other error
 */
sमाप_प्रकार mei_cldev_recv_nonblock_vtag(काष्ठा mei_cl_device *cldev, u8 *buf,
				     माप_प्रकार length, u8 *vtag)
अणु
	काष्ठा mei_cl *cl = cldev->cl;

	वापस __mei_cl_recv(cl, buf, length, vtag, MEI_CL_IO_RX_NONBLOCK, 0);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_recv_nonblock_vtag);

/**
 * mei_cldev_send - me device send  (ग_लिखो)
 *
 * @cldev: me client device
 * @buf: buffer to send
 * @length: buffer length
 *
 * Return:
 *  * written size in bytes
 *  * < 0 on error
 */
sमाप_प्रकार mei_cldev_send(काष्ठा mei_cl_device *cldev, u8 *buf, माप_प्रकार length)
अणु
	वापस mei_cldev_send_vtag(cldev, buf, length, 0);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_send);

/**
 * mei_cldev_recv - client receive (पढ़ो)
 *
 * @cldev: me client device
 * @buf: buffer to receive
 * @length: buffer length
 *
 * Return: पढ़ो size in bytes of < 0 on error
 */
sमाप_प्रकार mei_cldev_recv(काष्ठा mei_cl_device *cldev, u8 *buf, माप_प्रकार length)
अणु
	वापस mei_cldev_recv_vtag(cldev, buf, length, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_recv);

/**
 * mei_cldev_recv_nonblock - non block client receive (पढ़ो)
 *
 * @cldev: me client device
 * @buf: buffer to receive
 * @length: buffer length
 *
 * Return: पढ़ो size in bytes of < 0 on error
 *         -EAGAIN अगर function will block.
 */
sमाप_प्रकार mei_cldev_recv_nonblock(काष्ठा mei_cl_device *cldev, u8 *buf,
				माप_प्रकार length)
अणु
	वापस mei_cldev_recv_nonblock_vtag(cldev, buf, length, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_recv_nonblock);

/**
 * mei_cl_bus_rx_work - dispatch rx event क्रम a bus device
 *
 * @work: work
 */
अटल व्योम mei_cl_bus_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mei_cl_device *cldev;
	काष्ठा mei_device *bus;

	cldev = container_of(work, काष्ठा mei_cl_device, rx_work);

	bus = cldev->bus;

	अगर (cldev->rx_cb)
		cldev->rx_cb(cldev);

	mutex_lock(&bus->device_lock);
	अगर (mei_cl_is_connected(cldev->cl))
		mei_cl_पढ़ो_start(cldev->cl, mei_cl_mtu(cldev->cl), शून्य);
	mutex_unlock(&bus->device_lock);
पूर्ण

/**
 * mei_cl_bus_notअगर_work - dispatch FW notअगर event क्रम a bus device
 *
 * @work: work
 */
अटल व्योम mei_cl_bus_notअगर_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mei_cl_device *cldev;

	cldev = container_of(work, काष्ठा mei_cl_device, notअगर_work);

	अगर (cldev->notअगर_cb)
		cldev->notअगर_cb(cldev);
पूर्ण

/**
 * mei_cl_bus_notअगरy_event - schedule notअगरy cb on bus client
 *
 * @cl: host client
 *
 * Return: true अगर event was scheduled
 *         false अगर the client is not रुकोing क्रम event
 */
bool mei_cl_bus_notअगरy_event(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_cl_device *cldev = cl->cldev;

	अगर (!cldev || !cldev->notअगर_cb)
		वापस false;

	अगर (!cl->notअगरy_ev)
		वापस false;

	schedule_work(&cldev->notअगर_work);

	cl->notअगरy_ev = false;

	वापस true;
पूर्ण

/**
 * mei_cl_bus_rx_event - schedule rx event
 *
 * @cl: host client
 *
 * Return: true अगर event was scheduled
 *         false अगर the client is not रुकोing क्रम event
 */
bool mei_cl_bus_rx_event(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_cl_device *cldev = cl->cldev;

	अगर (!cldev || !cldev->rx_cb)
		वापस false;

	schedule_work(&cldev->rx_work);

	वापस true;
पूर्ण

/**
 * mei_cldev_रेजिस्टर_rx_cb - रेजिस्टर Rx event callback
 *
 * @cldev: me client devices
 * @rx_cb: callback function
 *
 * Return: 0 on success
 *         -EALREADY अगर an callback is alपढ़ोy रेजिस्टरed
 *         <0 on other errors
 */
पूर्णांक mei_cldev_रेजिस्टर_rx_cb(काष्ठा mei_cl_device *cldev, mei_cldev_cb_t rx_cb)
अणु
	काष्ठा mei_device *bus = cldev->bus;
	पूर्णांक ret;

	अगर (!rx_cb)
		वापस -EINVAL;
	अगर (cldev->rx_cb)
		वापस -EALREADY;

	cldev->rx_cb = rx_cb;
	INIT_WORK(&cldev->rx_work, mei_cl_bus_rx_work);

	mutex_lock(&bus->device_lock);
	अगर (mei_cl_is_connected(cldev->cl))
		ret = mei_cl_पढ़ो_start(cldev->cl, mei_cl_mtu(cldev->cl), शून्य);
	अन्यथा
		ret = -ENODEV;
	mutex_unlock(&bus->device_lock);
	अगर (ret && ret != -EBUSY) अणु
		cancel_work_sync(&cldev->rx_work);
		cldev->rx_cb = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_रेजिस्टर_rx_cb);

/**
 * mei_cldev_रेजिस्टर_notअगर_cb - रेजिस्टर FW notअगरication event callback
 *
 * @cldev: me client devices
 * @notअगर_cb: callback function
 *
 * Return: 0 on success
 *         -EALREADY अगर an callback is alपढ़ोy रेजिस्टरed
 *         <0 on other errors
 */
पूर्णांक mei_cldev_रेजिस्टर_notअगर_cb(काष्ठा mei_cl_device *cldev,
				mei_cldev_cb_t notअगर_cb)
अणु
	काष्ठा mei_device *bus = cldev->bus;
	पूर्णांक ret;

	अगर (!notअगर_cb)
		वापस -EINVAL;

	अगर (cldev->notअगर_cb)
		वापस -EALREADY;

	cldev->notअगर_cb = notअगर_cb;
	INIT_WORK(&cldev->notअगर_work, mei_cl_bus_notअगर_work);

	mutex_lock(&bus->device_lock);
	ret = mei_cl_notअगरy_request(cldev->cl, शून्य, 1);
	mutex_unlock(&bus->device_lock);
	अगर (ret) अणु
		cancel_work_sync(&cldev->notअगर_work);
		cldev->notअगर_cb = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_रेजिस्टर_notअगर_cb);

/**
 * mei_cldev_get_drvdata - driver data getter
 *
 * @cldev: mei client device
 *
 * Return: driver निजी data
 */
व्योम *mei_cldev_get_drvdata(स्थिर काष्ठा mei_cl_device *cldev)
अणु
	वापस dev_get_drvdata(&cldev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_get_drvdata);

/**
 * mei_cldev_set_drvdata - driver data setter
 *
 * @cldev: mei client device
 * @data: data to store
 */
व्योम mei_cldev_set_drvdata(काष्ठा mei_cl_device *cldev, व्योम *data)
अणु
	dev_set_drvdata(&cldev->dev, data);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_set_drvdata);

/**
 * mei_cldev_uuid - वापस uuid of the underlying me client
 *
 * @cldev: mei client device
 *
 * Return: me client uuid
 */
स्थिर uuid_le *mei_cldev_uuid(स्थिर काष्ठा mei_cl_device *cldev)
अणु
	वापस mei_me_cl_uuid(cldev->me_cl);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_uuid);

/**
 * mei_cldev_ver - वापस protocol version of the underlying me client
 *
 * @cldev: mei client device
 *
 * Return: me client protocol version
 */
u8 mei_cldev_ver(स्थिर काष्ठा mei_cl_device *cldev)
अणु
	वापस mei_me_cl_ver(cldev->me_cl);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_ver);

/**
 * mei_cldev_enabled - check whether the device is enabled
 *
 * @cldev: mei client device
 *
 * Return: true अगर me client is initialized and connected
 */
bool mei_cldev_enabled(काष्ठा mei_cl_device *cldev)
अणु
	वापस mei_cl_is_connected(cldev->cl);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_enabled);

/**
 * mei_cl_bus_module_get - acquire module of the underlying
 *    hw driver.
 *
 * @cldev: mei client device
 *
 * Return: true on success; false अगर the module was हटाओd.
 */
अटल bool mei_cl_bus_module_get(काष्ठा mei_cl_device *cldev)
अणु
	वापस try_module_get(cldev->bus->dev->driver->owner);
पूर्ण

/**
 * mei_cl_bus_module_put -  release the underlying hw module.
 *
 * @cldev: mei client device
 */
अटल व्योम mei_cl_bus_module_put(काष्ठा mei_cl_device *cldev)
अणु
	module_put(cldev->bus->dev->driver->owner);
पूर्ण

/**
 * mei_cl_bus_vtag - get bus vtag entry wrapper
 *     The tag क्रम bus client is always first.
 *
 * @cl: host client
 *
 * Return: bus vtag or शून्य
 */
अटल अंतरभूत काष्ठा mei_cl_vtag *mei_cl_bus_vtag(काष्ठा mei_cl *cl)
अणु
	वापस list_first_entry_or_null(&cl->vtag_map,
					काष्ठा mei_cl_vtag, list);
पूर्ण

/**
 * mei_cl_bus_vtag_alloc - add bus client entry to vtag map
 *
 * @cldev: me client device
 *
 * Return:
 * * 0 on success
 * * -ENOMEM अगर memory allocation failed
 */
अटल पूर्णांक mei_cl_bus_vtag_alloc(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा mei_cl *cl = cldev->cl;
	काष्ठा mei_cl_vtag *cl_vtag;

	/*
	 * Bail out अगर the client करोes not supports vtags
	 * or has alपढ़ोy allocated one
	 */
	अगर (mei_cl_vt_support_check(cl) || mei_cl_bus_vtag(cl))
		वापस 0;

	cl_vtag = mei_cl_vtag_alloc(शून्य, 0);
	अगर (IS_ERR(cl_vtag))
		वापस -ENOMEM;

	list_add_tail(&cl_vtag->list, &cl->vtag_map);

	वापस 0;
पूर्ण

/**
 * mei_cl_bus_vtag_मुक्त - हटाओ the bus entry from vtag map
 *
 * @cldev: me client device
 */
अटल व्योम mei_cl_bus_vtag_मुक्त(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा mei_cl *cl = cldev->cl;
	काष्ठा mei_cl_vtag *cl_vtag;

	cl_vtag = mei_cl_bus_vtag(cl);
	अगर (!cl_vtag)
		वापस;

	list_del(&cl_vtag->list);
	kमुक्त(cl_vtag);
पूर्ण

/**
 * mei_cldev_enable - enable me client device
 *     create connection with me client
 *
 * @cldev: me client device
 *
 * Return: 0 on success and < 0 on error
 */
पूर्णांक mei_cldev_enable(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा mei_device *bus = cldev->bus;
	काष्ठा mei_cl *cl;
	पूर्णांक ret;

	cl = cldev->cl;

	mutex_lock(&bus->device_lock);
	अगर (cl->state == MEI_खाता_UNINITIALIZED) अणु
		ret = mei_cl_link(cl);
		अगर (ret)
			जाओ out;
		/* update poपूर्णांकers */
		cl->cldev = cldev;
	पूर्ण

	अगर (mei_cl_is_connected(cl)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (!mei_me_cl_is_active(cldev->me_cl)) अणु
		dev_err(&cldev->dev, "me client is not active\n");
		ret = -ENOTTY;
		जाओ out;
	पूर्ण

	ret = mei_cl_bus_vtag_alloc(cldev);
	अगर (ret)
		जाओ out;

	ret = mei_cl_connect(cl, cldev->me_cl, शून्य);
	अगर (ret < 0) अणु
		dev_err(&cldev->dev, "cannot connect\n");
		mei_cl_bus_vtag_मुक्त(cldev);
	पूर्ण

out:
	mutex_unlock(&bus->device_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_enable);

/**
 * mei_cldev_unरेजिस्टर_callbacks - पूर्णांकernal wrapper क्रम unरेजिस्टरing
 *  callbacks.
 *
 * @cldev: client device
 */
अटल व्योम mei_cldev_unरेजिस्टर_callbacks(काष्ठा mei_cl_device *cldev)
अणु
	अगर (cldev->rx_cb) अणु
		cancel_work_sync(&cldev->rx_work);
		cldev->rx_cb = शून्य;
	पूर्ण

	अगर (cldev->notअगर_cb) अणु
		cancel_work_sync(&cldev->notअगर_work);
		cldev->notअगर_cb = शून्य;
	पूर्ण
पूर्ण

/**
 * mei_cldev_disable - disable me client device
 *     disconnect क्रमm the me client
 *
 * @cldev: me client device
 *
 * Return: 0 on success and < 0 on error
 */
पूर्णांक mei_cldev_disable(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा mei_device *bus;
	काष्ठा mei_cl *cl;
	पूर्णांक err;

	अगर (!cldev)
		वापस -ENODEV;

	cl = cldev->cl;

	bus = cldev->bus;

	mei_cldev_unरेजिस्टर_callbacks(cldev);

	mutex_lock(&bus->device_lock);

	mei_cl_bus_vtag_मुक्त(cldev);

	अगर (!mei_cl_is_connected(cl)) अणु
		dev_dbg(bus->dev, "Already disconnected\n");
		err = 0;
		जाओ out;
	पूर्ण

	err = mei_cl_disconnect(cl);
	अगर (err < 0)
		dev_err(bus->dev, "Could not disconnect from the ME client\n");

out:
	/* Flush queues and हटाओ any pending पढ़ो */
	mei_cl_flush_queues(cl, शून्य);
	mei_cl_unlink(cl);

	mutex_unlock(&bus->device_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_disable);

/**
 * mei_cl_device_find - find matching entry in the driver id table
 *
 * @cldev: me client device
 * @cldrv: me client driver
 *
 * Return: id on success; शून्य अगर no id is matching
 */
अटल स्थिर
काष्ठा mei_cl_device_id *mei_cl_device_find(काष्ठा mei_cl_device *cldev,
					    काष्ठा mei_cl_driver *cldrv)
अणु
	स्थिर काष्ठा mei_cl_device_id *id;
	स्थिर uuid_le *uuid;
	u8 version;
	bool match;

	uuid = mei_me_cl_uuid(cldev->me_cl);
	version = mei_me_cl_ver(cldev->me_cl);

	id = cldrv->id_table;
	जबतक (uuid_le_cmp(शून्य_UUID_LE, id->uuid)) अणु
		अगर (!uuid_le_cmp(*uuid, id->uuid)) अणु
			match = true;

			अगर (cldev->name[0])
				अगर (म_भेदन(cldev->name, id->name,
					    माप(id->name)))
					match = false;

			अगर (id->version != MEI_CL_VERSION_ANY)
				अगर (id->version != version)
					match = false;
			अगर (match)
				वापस id;
		पूर्ण

		id++;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * mei_cl_device_match  - device match function
 *
 * @dev: device
 * @drv: driver
 *
 * Return:  1 अगर matching device was found 0 otherwise
 */
अटल पूर्णांक mei_cl_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	काष्ठा mei_cl_driver *cldrv = to_mei_cl_driver(drv);
	स्थिर काष्ठा mei_cl_device_id *found_id;

	अगर (!cldev)
		वापस 0;

	अगर (!cldev->करो_match)
		वापस 0;

	अगर (!cldrv || !cldrv->id_table)
		वापस 0;

	found_id = mei_cl_device_find(cldev, cldrv);
	अगर (found_id)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * mei_cl_device_probe - bus probe function
 *
 * @dev: device
 *
 * Return:  0 on success; < 0 otherwise
 */
अटल पूर्णांक mei_cl_device_probe(काष्ठा device *dev)
अणु
	काष्ठा mei_cl_device *cldev;
	काष्ठा mei_cl_driver *cldrv;
	स्थिर काष्ठा mei_cl_device_id *id;
	पूर्णांक ret;

	cldev = to_mei_cl_device(dev);
	cldrv = to_mei_cl_driver(dev->driver);

	अगर (!cldev)
		वापस 0;

	अगर (!cldrv || !cldrv->probe)
		वापस -ENODEV;

	id = mei_cl_device_find(cldev, cldrv);
	अगर (!id)
		वापस -ENODEV;

	अगर (!mei_cl_bus_module_get(cldev)) अणु
		dev_err(&cldev->dev, "get hw module failed");
		वापस -ENODEV;
	पूर्ण

	ret = cldrv->probe(cldev, id);
	अगर (ret) अणु
		mei_cl_bus_module_put(cldev);
		वापस ret;
	पूर्ण

	__module_get(THIS_MODULE);
	वापस 0;
पूर्ण

/**
 * mei_cl_device_हटाओ - हटाओ device from the bus
 *
 * @dev: device
 *
 * Return:  0 on success; < 0 otherwise
 */
अटल पूर्णांक mei_cl_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	काष्ठा mei_cl_driver *cldrv = to_mei_cl_driver(dev->driver);

	अगर (cldrv->हटाओ)
		cldrv->हटाओ(cldev);

	mei_cldev_unरेजिस्टर_callbacks(cldev);

	mei_cl_bus_module_put(cldev);
	module_put(THIS_MODULE);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			     अक्षर *buf)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s", cldev->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार uuid_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			     अक्षर *buf)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	स्थिर uuid_le *uuid = mei_me_cl_uuid(cldev->me_cl);

	वापस प्र_लिखो(buf, "%pUl", uuid);
पूर्ण
अटल DEVICE_ATTR_RO(uuid);

अटल sमाप_प्रकार version_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			     अक्षर *buf)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	u8 version = mei_me_cl_ver(cldev->me_cl);

	वापस प्र_लिखो(buf, "%02X", version);
पूर्ण
अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			     अक्षर *buf)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	स्थिर uuid_le *uuid = mei_me_cl_uuid(cldev->me_cl);
	u8 version = mei_me_cl_ver(cldev->me_cl);

	वापस scnम_लिखो(buf, PAGE_SIZE, "mei:%s:%pUl:%02X:",
			 cldev->name, uuid, version);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार max_conn_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			     अक्षर *buf)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	u8 maxconn = mei_me_cl_max_conn(cldev->me_cl);

	वापस प्र_लिखो(buf, "%d", maxconn);
पूर्ण
अटल DEVICE_ATTR_RO(max_conn);

अटल sमाप_प्रकार fixed_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			  अक्षर *buf)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	u8 fixed = mei_me_cl_fixed(cldev->me_cl);

	वापस प्र_लिखो(buf, "%d", fixed);
पूर्ण
अटल DEVICE_ATTR_RO(fixed);

अटल sमाप_प्रकार vtag_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			 अक्षर *buf)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	bool vt = mei_me_cl_vt(cldev->me_cl);

	वापस प्र_लिखो(buf, "%d", vt);
पूर्ण
अटल DEVICE_ATTR_RO(vtag);

अटल sमाप_प्रकार max_len_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			    अक्षर *buf)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	u32 maxlen = mei_me_cl_max_len(cldev->me_cl);

	वापस प्र_लिखो(buf, "%u", maxlen);
पूर्ण
अटल DEVICE_ATTR_RO(max_len);

अटल काष्ठा attribute *mei_cldev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_uuid.attr,
	&dev_attr_version.attr,
	&dev_attr_modalias.attr,
	&dev_attr_max_conn.attr,
	&dev_attr_fixed.attr,
	&dev_attr_vtag.attr,
	&dev_attr_max_len.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(mei_cldev);

/**
 * mei_cl_device_uevent - me client bus uevent handler
 *
 * @dev: device
 * @env: uevent kobject
 *
 * Return: 0 on success -ENOMEM on when add_uevent_var fails
 */
अटल पूर्णांक mei_cl_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	स्थिर uuid_le *uuid = mei_me_cl_uuid(cldev->me_cl);
	u8 version = mei_me_cl_ver(cldev->me_cl);

	अगर (add_uevent_var(env, "MEI_CL_VERSION=%d", version))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "MEI_CL_UUID=%pUl", uuid))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "MEI_CL_NAME=%s", cldev->name))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "MODALIAS=mei:%s:%pUl:%02X:",
			   cldev->name, uuid, version))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल काष्ठा bus_type mei_cl_bus_type = अणु
	.name		= "mei",
	.dev_groups	= mei_cldev_groups,
	.match		= mei_cl_device_match,
	.probe		= mei_cl_device_probe,
	.हटाओ		= mei_cl_device_हटाओ,
	.uevent		= mei_cl_device_uevent,
पूर्ण;

अटल काष्ठा mei_device *mei_dev_bus_get(काष्ठा mei_device *bus)
अणु
	अगर (bus)
		get_device(bus->dev);

	वापस bus;
पूर्ण

अटल व्योम mei_dev_bus_put(काष्ठा mei_device *bus)
अणु
	अगर (bus)
		put_device(bus->dev);
पूर्ण

अटल व्योम mei_cl_bus_dev_release(काष्ठा device *dev)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);

	अगर (!cldev)
		वापस;

	mei_me_cl_put(cldev->me_cl);
	mei_dev_bus_put(cldev->bus);
	mei_cl_unlink(cldev->cl);
	kमुक्त(cldev->cl);
	kमुक्त(cldev);
पूर्ण

अटल स्थिर काष्ठा device_type mei_cl_device_type = अणु
	.release = mei_cl_bus_dev_release,
पूर्ण;

/**
 * mei_cl_bus_set_name - set device name क्रम me client device
 *  <controller>-<client device>
 *  Example: 0000:00:16.0-55213584-9a29-4916-badf-0fb7ed682aeb
 *
 * @cldev: me client device
 */
अटल अंतरभूत व्योम mei_cl_bus_set_name(काष्ठा mei_cl_device *cldev)
अणु
	dev_set_name(&cldev->dev, "%s-%pUl",
		     dev_name(cldev->bus->dev),
		     mei_me_cl_uuid(cldev->me_cl));
पूर्ण

/**
 * mei_cl_bus_dev_alloc - initialize and allocate mei client device
 *
 * @bus: mei device
 * @me_cl: me client
 *
 * Return: allocated device काष्ठाur or शून्य on allocation failure
 */
अटल काष्ठा mei_cl_device *mei_cl_bus_dev_alloc(काष्ठा mei_device *bus,
						  काष्ठा mei_me_client *me_cl)
अणु
	काष्ठा mei_cl_device *cldev;
	काष्ठा mei_cl *cl;

	cldev = kzalloc(माप(*cldev), GFP_KERNEL);
	अगर (!cldev)
		वापस शून्य;

	cl = mei_cl_allocate(bus);
	अगर (!cl) अणु
		kमुक्त(cldev);
		वापस शून्य;
	पूर्ण

	device_initialize(&cldev->dev);
	cldev->dev.parent = bus->dev;
	cldev->dev.bus    = &mei_cl_bus_type;
	cldev->dev.type   = &mei_cl_device_type;
	cldev->bus        = mei_dev_bus_get(bus);
	cldev->me_cl      = mei_me_cl_get(me_cl);
	cldev->cl         = cl;
	mei_cl_bus_set_name(cldev);
	cldev->is_added   = 0;
	INIT_LIST_HEAD(&cldev->bus_list);

	वापस cldev;
पूर्ण

/**
 * mei_cl_bus_dev_setup - setup me client device
 *    run fix up routines and set the device name
 *
 * @bus: mei device
 * @cldev: me client device
 *
 * Return: true अगर the device is eligible क्रम क्रमागतeration
 */
अटल bool mei_cl_bus_dev_setup(काष्ठा mei_device *bus,
				 काष्ठा mei_cl_device *cldev)
अणु
	cldev->करो_match = 1;
	mei_cl_bus_dev_fixup(cldev);

	/* the device name can change during fix up */
	अगर (cldev->करो_match)
		mei_cl_bus_set_name(cldev);

	वापस cldev->करो_match == 1;
पूर्ण

/**
 * mei_cl_bus_dev_add - add me client devices
 *
 * @cldev: me client device
 *
 * Return: 0 on success; < 0 on failre
 */
अटल पूर्णांक mei_cl_bus_dev_add(काष्ठा mei_cl_device *cldev)
अणु
	पूर्णांक ret;

	dev_dbg(cldev->bus->dev, "adding %pUL:%02X\n",
		mei_me_cl_uuid(cldev->me_cl),
		mei_me_cl_ver(cldev->me_cl));
	ret = device_add(&cldev->dev);
	अगर (!ret)
		cldev->is_added = 1;

	वापस ret;
पूर्ण

/**
 * mei_cl_bus_dev_stop - stop the driver
 *
 * @cldev: me client device
 */
अटल व्योम mei_cl_bus_dev_stop(काष्ठा mei_cl_device *cldev)
अणु
	अगर (cldev->is_added)
		device_release_driver(&cldev->dev);
पूर्ण

/**
 * mei_cl_bus_dev_destroy - destroy me client devices object
 *
 * @cldev: me client device
 *
 * Locking: called under "dev->cl_bus_lock" lock
 */
अटल व्योम mei_cl_bus_dev_destroy(काष्ठा mei_cl_device *cldev)
अणु

	WARN_ON(!mutex_is_locked(&cldev->bus->cl_bus_lock));

	अगर (!cldev->is_added)
		वापस;

	device_del(&cldev->dev);

	list_del_init(&cldev->bus_list);

	cldev->is_added = 0;
	put_device(&cldev->dev);
पूर्ण

/**
 * mei_cl_bus_हटाओ_device - हटाओ a devices क्रमm the bus
 *
 * @cldev: me client device
 */
अटल व्योम mei_cl_bus_हटाओ_device(काष्ठा mei_cl_device *cldev)
अणु
	mei_cl_bus_dev_stop(cldev);
	mei_cl_bus_dev_destroy(cldev);
पूर्ण

/**
 * mei_cl_bus_हटाओ_devices - हटाओ all devices क्रमm the bus
 *
 * @bus: mei device
 */
व्योम mei_cl_bus_हटाओ_devices(काष्ठा mei_device *bus)
अणु
	काष्ठा mei_cl_device *cldev, *next;

	mutex_lock(&bus->cl_bus_lock);
	list_क्रम_each_entry_safe(cldev, next, &bus->device_list, bus_list)
		mei_cl_bus_हटाओ_device(cldev);
	mutex_unlock(&bus->cl_bus_lock);
पूर्ण


/**
 * mei_cl_bus_dev_init - allocate and initializes an mei client devices
 *     based on me client
 *
 * @bus: mei device
 * @me_cl: me client
 *
 * Locking: called under "dev->cl_bus_lock" lock
 */
अटल व्योम mei_cl_bus_dev_init(काष्ठा mei_device *bus,
				काष्ठा mei_me_client *me_cl)
अणु
	काष्ठा mei_cl_device *cldev;

	WARN_ON(!mutex_is_locked(&bus->cl_bus_lock));

	dev_dbg(bus->dev, "initializing %pUl", mei_me_cl_uuid(me_cl));

	अगर (me_cl->bus_added)
		वापस;

	cldev = mei_cl_bus_dev_alloc(bus, me_cl);
	अगर (!cldev)
		वापस;

	me_cl->bus_added = true;
	list_add_tail(&cldev->bus_list, &bus->device_list);

पूर्ण

/**
 * mei_cl_bus_rescan - scan me clients list and add create
 *    devices क्रम eligible clients
 *
 * @bus: mei device
 */
अटल व्योम mei_cl_bus_rescan(काष्ठा mei_device *bus)
अणु
	काष्ठा mei_cl_device *cldev, *n;
	काष्ठा mei_me_client *me_cl;

	mutex_lock(&bus->cl_bus_lock);

	करोwn_पढ़ो(&bus->me_clients_rwsem);
	list_क्रम_each_entry(me_cl, &bus->me_clients, list)
		mei_cl_bus_dev_init(bus, me_cl);
	up_पढ़ो(&bus->me_clients_rwsem);

	list_क्रम_each_entry_safe(cldev, n, &bus->device_list, bus_list) अणु

		अगर (!mei_me_cl_is_active(cldev->me_cl)) अणु
			mei_cl_bus_हटाओ_device(cldev);
			जारी;
		पूर्ण

		अगर (cldev->is_added)
			जारी;

		अगर (mei_cl_bus_dev_setup(bus, cldev))
			mei_cl_bus_dev_add(cldev);
		अन्यथा अणु
			list_del_init(&cldev->bus_list);
			put_device(&cldev->dev);
		पूर्ण
	पूर्ण
	mutex_unlock(&bus->cl_bus_lock);

	dev_dbg(bus->dev, "rescan end");
पूर्ण

व्योम mei_cl_bus_rescan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mei_device *bus =
		container_of(work, काष्ठा mei_device, bus_rescan_work);

	mei_cl_bus_rescan(bus);
पूर्ण

पूर्णांक __mei_cldev_driver_रेजिस्टर(काष्ठा mei_cl_driver *cldrv,
				काष्ठा module *owner)
अणु
	पूर्णांक err;

	cldrv->driver.name = cldrv->name;
	cldrv->driver.owner = owner;
	cldrv->driver.bus = &mei_cl_bus_type;

	err = driver_रेजिस्टर(&cldrv->driver);
	अगर (err)
		वापस err;

	pr_debug("mei: driver [%s] registered\n", cldrv->driver.name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__mei_cldev_driver_रेजिस्टर);

व्योम mei_cldev_driver_unरेजिस्टर(काष्ठा mei_cl_driver *cldrv)
अणु
	driver_unरेजिस्टर(&cldrv->driver);

	pr_debug("mei: driver [%s] unregistered\n", cldrv->driver.name);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cldev_driver_unरेजिस्टर);


पूर्णांक __init mei_cl_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&mei_cl_bus_type);
पूर्ण

व्योम __निकास mei_cl_bus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&mei_cl_bus_type);
पूर्ण
