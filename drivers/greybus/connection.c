<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus connections
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#समावेश <linux/workqueue.h>
#समावेश <linux/greybus.h>

#समावेश "greybus_trace.h"

#घोषणा GB_CONNECTION_CPORT_QUIESCE_TIMEOUT	1000

अटल व्योम gb_connection_kref_release(काष्ठा kref *kref);

अटल DEFINE_SPINLOCK(gb_connections_lock);
अटल DEFINE_MUTEX(gb_connection_mutex);

/* Caller holds gb_connection_mutex. */
अटल bool gb_connection_cport_in_use(काष्ठा gb_पूर्णांकerface *पूर्णांकf, u16 cport_id)
अणु
	काष्ठा gb_host_device *hd = पूर्णांकf->hd;
	काष्ठा gb_connection *connection;

	list_क्रम_each_entry(connection, &hd->connections, hd_links) अणु
		अगर (connection->पूर्णांकf == पूर्णांकf &&
		    connection->पूर्णांकf_cport_id == cport_id)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम gb_connection_get(काष्ठा gb_connection *connection)
अणु
	kref_get(&connection->kref);

	trace_gb_connection_get(connection);
पूर्ण

अटल व्योम gb_connection_put(काष्ठा gb_connection *connection)
अणु
	trace_gb_connection_put(connection);

	kref_put(&connection->kref, gb_connection_kref_release);
पूर्ण

/*
 * Returns a reference-counted poपूर्णांकer to the connection अगर found.
 */
अटल काष्ठा gb_connection *
gb_connection_hd_find(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	काष्ठा gb_connection *connection;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gb_connections_lock, flags);
	list_क्रम_each_entry(connection, &hd->connections, hd_links)
		अगर (connection->hd_cport_id == cport_id) अणु
			gb_connection_get(connection);
			जाओ found;
		पूर्ण
	connection = शून्य;
found:
	spin_unlock_irqrestore(&gb_connections_lock, flags);

	वापस connection;
पूर्ण

/*
 * Callback from the host driver to let us know that data has been
 * received on the bundle.
 */
व्योम greybus_data_rcvd(काष्ठा gb_host_device *hd, u16 cport_id,
		       u8 *data, माप_प्रकार length)
अणु
	काष्ठा gb_connection *connection;

	trace_gb_hd_in(hd);

	connection = gb_connection_hd_find(hd, cport_id);
	अगर (!connection) अणु
		dev_err(&hd->dev,
			"nonexistent connection (%zu bytes dropped)\n", length);
		वापस;
	पूर्ण
	gb_connection_recv(connection, data, length);
	gb_connection_put(connection);
पूर्ण
EXPORT_SYMBOL_GPL(greybus_data_rcvd);

अटल व्योम gb_connection_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा gb_connection *connection;

	connection = container_of(kref, काष्ठा gb_connection, kref);

	trace_gb_connection_release(connection);

	kमुक्त(connection);
पूर्ण

अटल व्योम gb_connection_init_name(काष्ठा gb_connection *connection)
अणु
	u16 hd_cport_id = connection->hd_cport_id;
	u16 cport_id = 0;
	u8 पूर्णांकf_id = 0;

	अगर (connection->पूर्णांकf) अणु
		पूर्णांकf_id = connection->पूर्णांकf->पूर्णांकerface_id;
		cport_id = connection->पूर्णांकf_cport_id;
	पूर्ण

	snम_लिखो(connection->name, माप(connection->name),
		 "%u/%u:%u", hd_cport_id, पूर्णांकf_id, cport_id);
पूर्ण

/*
 * _gb_connection_create() - create a Greybus connection
 * @hd:			host device of the connection
 * @hd_cport_id:	host-device cport id, or -1 क्रम dynamic allocation
 * @पूर्णांकf:		remote पूर्णांकerface, or शून्य क्रम अटल connections
 * @bundle:		remote-पूर्णांकerface bundle (may be शून्य)
 * @cport_id:		remote-पूर्णांकerface cport id, or 0 क्रम अटल connections
 * @handler:		request handler (may be शून्य)
 * @flags:		connection flags
 *
 * Create a Greybus connection, representing the bidirectional link
 * between a CPort on a (local) Greybus host device and a CPort on
 * another Greybus पूर्णांकerface.
 *
 * A connection also मुख्यtains the state of operations sent over the
 * connection.
 *
 * Serialised against concurrent create and destroy using the
 * gb_connection_mutex.
 *
 * Return: A poपूर्णांकer to the new connection अगर successful, or an ERR_PTR
 * otherwise.
 */
अटल काष्ठा gb_connection *
_gb_connection_create(काष्ठा gb_host_device *hd, पूर्णांक hd_cport_id,
		      काष्ठा gb_पूर्णांकerface *पूर्णांकf,
		      काष्ठा gb_bundle *bundle, पूर्णांक cport_id,
		      gb_request_handler_t handler,
		      अचिन्हित दीर्घ flags)
अणु
	काष्ठा gb_connection *connection;
	पूर्णांक ret;

	mutex_lock(&gb_connection_mutex);

	अगर (पूर्णांकf && gb_connection_cport_in_use(पूर्णांकf, cport_id)) अणु
		dev_err(&पूर्णांकf->dev, "cport %u already in use\n", cport_id);
		ret = -EBUSY;
		जाओ err_unlock;
	पूर्ण

	ret = gb_hd_cport_allocate(hd, hd_cport_id, flags);
	अगर (ret < 0) अणु
		dev_err(&hd->dev, "failed to allocate cport: %d\n", ret);
		जाओ err_unlock;
	पूर्ण
	hd_cport_id = ret;

	connection = kzalloc(माप(*connection), GFP_KERNEL);
	अगर (!connection) अणु
		ret = -ENOMEM;
		जाओ err_hd_cport_release;
	पूर्ण

	connection->hd_cport_id = hd_cport_id;
	connection->पूर्णांकf_cport_id = cport_id;
	connection->hd = hd;
	connection->पूर्णांकf = पूर्णांकf;
	connection->bundle = bundle;
	connection->handler = handler;
	connection->flags = flags;
	अगर (पूर्णांकf && (पूर्णांकf->quirks & GB_INTERFACE_QUIRK_NO_CPORT_FEATURES))
		connection->flags |= GB_CONNECTION_FLAG_NO_FLOWCTRL;
	connection->state = GB_CONNECTION_STATE_DISABLED;

	atomic_set(&connection->op_cycle, 0);
	mutex_init(&connection->mutex);
	spin_lock_init(&connection->lock);
	INIT_LIST_HEAD(&connection->operations);

	connection->wq = alloc_workqueue("%s:%d", WQ_UNBOUND, 1,
					 dev_name(&hd->dev), hd_cport_id);
	अगर (!connection->wq) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_connection;
	पूर्ण

	kref_init(&connection->kref);

	gb_connection_init_name(connection);

	spin_lock_irq(&gb_connections_lock);
	list_add(&connection->hd_links, &hd->connections);

	अगर (bundle)
		list_add(&connection->bundle_links, &bundle->connections);
	अन्यथा
		INIT_LIST_HEAD(&connection->bundle_links);

	spin_unlock_irq(&gb_connections_lock);

	mutex_unlock(&gb_connection_mutex);

	trace_gb_connection_create(connection);

	वापस connection;

err_मुक्त_connection:
	kमुक्त(connection);
err_hd_cport_release:
	gb_hd_cport_release(hd, hd_cport_id);
err_unlock:
	mutex_unlock(&gb_connection_mutex);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा gb_connection *
gb_connection_create_अटल(काष्ठा gb_host_device *hd, u16 hd_cport_id,
			    gb_request_handler_t handler)
अणु
	वापस _gb_connection_create(hd, hd_cport_id, शून्य, शून्य, 0, handler,
				     GB_CONNECTION_FLAG_HIGH_PRIO);
पूर्ण

काष्ठा gb_connection *
gb_connection_create_control(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस _gb_connection_create(पूर्णांकf->hd, -1, पूर्णांकf, शून्य, 0, शून्य,
				     GB_CONNECTION_FLAG_CONTROL |
				     GB_CONNECTION_FLAG_HIGH_PRIO);
पूर्ण

काष्ठा gb_connection *
gb_connection_create(काष्ठा gb_bundle *bundle, u16 cport_id,
		     gb_request_handler_t handler)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = bundle->पूर्णांकf;

	वापस _gb_connection_create(पूर्णांकf->hd, -1, पूर्णांकf, bundle, cport_id,
				     handler, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_create);

काष्ठा gb_connection *
gb_connection_create_flags(काष्ठा gb_bundle *bundle, u16 cport_id,
			   gb_request_handler_t handler,
			   अचिन्हित दीर्घ flags)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = bundle->पूर्णांकf;

	अगर (WARN_ON_ONCE(flags & GB_CONNECTION_FLAG_CORE_MASK))
		flags &= ~GB_CONNECTION_FLAG_CORE_MASK;

	वापस _gb_connection_create(पूर्णांकf->hd, -1, पूर्णांकf, bundle, cport_id,
				     handler, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_create_flags);

काष्ठा gb_connection *
gb_connection_create_offloaded(काष्ठा gb_bundle *bundle, u16 cport_id,
			       अचिन्हित दीर्घ flags)
अणु
	flags |= GB_CONNECTION_FLAG_OFFLOADED;

	वापस gb_connection_create_flags(bundle, cport_id, शून्य, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_create_offloaded);

अटल पूर्णांक gb_connection_hd_cport_enable(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	पूर्णांक ret;

	अगर (!hd->driver->cport_enable)
		वापस 0;

	ret = hd->driver->cport_enable(hd, connection->hd_cport_id,
				       connection->flags);
	अगर (ret) अणु
		dev_err(&hd->dev, "%s: failed to enable host cport: %d\n",
			connection->name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gb_connection_hd_cport_disable(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	पूर्णांक ret;

	अगर (!hd->driver->cport_disable)
		वापस;

	ret = hd->driver->cport_disable(hd, connection->hd_cport_id);
	अगर (ret) अणु
		dev_err(&hd->dev, "%s: failed to disable host cport: %d\n",
			connection->name, ret);
	पूर्ण
पूर्ण

अटल पूर्णांक gb_connection_hd_cport_connected(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	पूर्णांक ret;

	अगर (!hd->driver->cport_connected)
		वापस 0;

	ret = hd->driver->cport_connected(hd, connection->hd_cport_id);
	अगर (ret) अणु
		dev_err(&hd->dev, "%s: failed to set connected state: %d\n",
			connection->name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_connection_hd_cport_flush(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	पूर्णांक ret;

	अगर (!hd->driver->cport_flush)
		वापस 0;

	ret = hd->driver->cport_flush(hd, connection->hd_cport_id);
	अगर (ret) अणु
		dev_err(&hd->dev, "%s: failed to flush host cport: %d\n",
			connection->name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_connection_hd_cport_quiesce(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	माप_प्रकार peer_space;
	पूर्णांक ret;

	अगर (!hd->driver->cport_quiesce)
		वापस 0;

	peer_space = माप(काष्ठा gb_operation_msg_hdr) +
			माप(काष्ठा gb_cport_shutकरोwn_request);

	अगर (connection->mode_चयन)
		peer_space += माप(काष्ठा gb_operation_msg_hdr);

	ret = hd->driver->cport_quiesce(hd, connection->hd_cport_id,
					peer_space,
					GB_CONNECTION_CPORT_QUIESCE_TIMEOUT);
	अगर (ret) अणु
		dev_err(&hd->dev, "%s: failed to quiesce host cport: %d\n",
			connection->name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_connection_hd_cport_clear(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	पूर्णांक ret;

	अगर (!hd->driver->cport_clear)
		वापस 0;

	ret = hd->driver->cport_clear(hd, connection->hd_cport_id);
	अगर (ret) अणु
		dev_err(&hd->dev, "%s: failed to clear host cport: %d\n",
			connection->name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Request the SVC to create a connection from AP's cport to interface's
 * cport.
 */
अटल पूर्णांक
gb_connection_svc_connection_create(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	काष्ठा gb_पूर्णांकerface *पूर्णांकf;
	u8 cport_flags;
	पूर्णांक ret;

	अगर (gb_connection_is_अटल(connection))
		वापस 0;

	पूर्णांकf = connection->पूर्णांकf;

	/*
	 * Enable either E2EFC or CSD, unless no flow control is requested.
	 */
	cport_flags = GB_SVC_CPORT_FLAG_CSV_N;
	अगर (gb_connection_flow_control_disabled(connection)) अणु
		cport_flags |= GB_SVC_CPORT_FLAG_CSD_N;
	पूर्ण अन्यथा अगर (gb_connection_e2efc_enabled(connection)) अणु
		cport_flags |= GB_SVC_CPORT_FLAG_CSD_N |
				GB_SVC_CPORT_FLAG_E2EFC;
	पूर्ण

	ret = gb_svc_connection_create(hd->svc,
				       hd->svc->ap_पूर्णांकf_id,
				       connection->hd_cport_id,
				       पूर्णांकf->पूर्णांकerface_id,
				       connection->पूर्णांकf_cport_id,
				       cport_flags);
	अगर (ret) अणु
		dev_err(&connection->hd->dev,
			"%s: failed to create svc connection: %d\n",
			connection->name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
gb_connection_svc_connection_destroy(काष्ठा gb_connection *connection)
अणु
	अगर (gb_connection_is_अटल(connection))
		वापस;

	gb_svc_connection_destroy(connection->hd->svc,
				  connection->hd->svc->ap_पूर्णांकf_id,
				  connection->hd_cport_id,
				  connection->पूर्णांकf->पूर्णांकerface_id,
				  connection->पूर्णांकf_cport_id);
पूर्ण

/* Inक्रमm Interface about active CPorts */
अटल पूर्णांक gb_connection_control_connected(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_control *control;
	u16 cport_id = connection->पूर्णांकf_cport_id;
	पूर्णांक ret;

	अगर (gb_connection_is_अटल(connection))
		वापस 0;

	अगर (gb_connection_is_control(connection))
		वापस 0;

	control = connection->पूर्णांकf->control;

	ret = gb_control_connected_operation(control, cport_id);
	अगर (ret) अणु
		dev_err(&connection->bundle->dev,
			"failed to connect cport: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
gb_connection_control_disconnecting(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_control *control;
	u16 cport_id = connection->पूर्णांकf_cport_id;
	पूर्णांक ret;

	अगर (gb_connection_is_अटल(connection))
		वापस;

	control = connection->पूर्णांकf->control;

	ret = gb_control_disconnecting_operation(control, cport_id);
	अगर (ret) अणु
		dev_err(&connection->hd->dev,
			"%s: failed to send disconnecting: %d\n",
			connection->name, ret);
	पूर्ण
पूर्ण

अटल व्योम
gb_connection_control_disconnected(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_control *control;
	u16 cport_id = connection->पूर्णांकf_cport_id;
	पूर्णांक ret;

	अगर (gb_connection_is_अटल(connection))
		वापस;

	control = connection->पूर्णांकf->control;

	अगर (gb_connection_is_control(connection)) अणु
		अगर (connection->mode_चयन) अणु
			ret = gb_control_mode_चयन_operation(control);
			अगर (ret) अणु
				/*
				 * Allow mode चयन to समय out रुकोing क्रम
				 * mailbox event.
				 */
				वापस;
			पूर्ण
		पूर्ण

		वापस;
	पूर्ण

	ret = gb_control_disconnected_operation(control, cport_id);
	अगर (ret) अणु
		dev_warn(&connection->bundle->dev,
			 "failed to disconnect cport: %d\n", ret);
	पूर्ण
पूर्ण

अटल पूर्णांक gb_connection_shutकरोwn_operation(काष्ठा gb_connection *connection,
					    u8 phase)
अणु
	काष्ठा gb_cport_shutकरोwn_request *req;
	काष्ठा gb_operation *operation;
	पूर्णांक ret;

	operation = gb_operation_create_core(connection,
					     GB_REQUEST_TYPE_CPORT_SHUTDOWN,
					     माप(*req), 0, 0,
					     GFP_KERNEL);
	अगर (!operation)
		वापस -ENOMEM;

	req = operation->request->payload;
	req->phase = phase;

	ret = gb_operation_request_send_sync(operation);

	gb_operation_put(operation);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_connection_cport_shutकरोwn(काष्ठा gb_connection *connection,
					u8 phase)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	स्थिर काष्ठा gb_hd_driver *drv = hd->driver;
	पूर्णांक ret;

	अगर (gb_connection_is_अटल(connection))
		वापस 0;

	अगर (gb_connection_is_offloaded(connection)) अणु
		अगर (!drv->cport_shutकरोwn)
			वापस 0;

		ret = drv->cport_shutकरोwn(hd, connection->hd_cport_id, phase,
					  GB_OPERATION_TIMEOUT_DEFAULT);
	पूर्ण अन्यथा अणु
		ret = gb_connection_shutकरोwn_operation(connection, phase);
	पूर्ण

	अगर (ret) अणु
		dev_err(&hd->dev, "%s: failed to send cport shutdown (phase %d): %d\n",
			connection->name, phase, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gb_connection_cport_shutकरोwn_phase_1(काष्ठा gb_connection *connection)
अणु
	वापस gb_connection_cport_shutकरोwn(connection, 1);
पूर्ण

अटल पूर्णांक
gb_connection_cport_shutकरोwn_phase_2(काष्ठा gb_connection *connection)
अणु
	वापस gb_connection_cport_shutकरोwn(connection, 2);
पूर्ण

/*
 * Cancel all active operations on a connection.
 *
 * Locking: Called with connection lock held and state set to DISABLED or
 * DISCONNECTING.
 */
अटल व्योम gb_connection_cancel_operations(काष्ठा gb_connection *connection,
					    पूर्णांक त्रुटि_सं)
	__must_hold(&connection->lock)
अणु
	काष्ठा gb_operation *operation;

	जबतक (!list_empty(&connection->operations)) अणु
		operation = list_last_entry(&connection->operations,
					    काष्ठा gb_operation, links);
		gb_operation_get(operation);
		spin_unlock_irq(&connection->lock);

		अगर (gb_operation_is_incoming(operation))
			gb_operation_cancel_incoming(operation, त्रुटि_सं);
		अन्यथा
			gb_operation_cancel(operation, त्रुटि_सं);

		gb_operation_put(operation);

		spin_lock_irq(&connection->lock);
	पूर्ण
पूर्ण

/*
 * Cancel all active incoming operations on a connection.
 *
 * Locking: Called with connection lock held and state set to ENABLED_TX.
 */
अटल व्योम
gb_connection_flush_incoming_operations(काष्ठा gb_connection *connection,
					पूर्णांक त्रुटि_सं)
	__must_hold(&connection->lock)
अणु
	काष्ठा gb_operation *operation;
	bool incoming;

	जबतक (!list_empty(&connection->operations)) अणु
		incoming = false;
		list_क्रम_each_entry(operation, &connection->operations,
				    links) अणु
			अगर (gb_operation_is_incoming(operation)) अणु
				gb_operation_get(operation);
				incoming = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!incoming)
			अवरोध;

		spin_unlock_irq(&connection->lock);

		/* FIXME: flush, not cancel? */
		gb_operation_cancel_incoming(operation, त्रुटि_सं);
		gb_operation_put(operation);

		spin_lock_irq(&connection->lock);
	पूर्ण
पूर्ण

/*
 * _gb_connection_enable() - enable a connection
 * @connection:		connection to enable
 * @rx:			whether to enable incoming requests
 *
 * Connection-enable helper क्रम DISABLED->ENABLED, DISABLED->ENABLED_TX, and
 * ENABLED_TX->ENABLED state transitions.
 *
 * Locking: Caller holds connection->mutex.
 */
अटल पूर्णांक _gb_connection_enable(काष्ठा gb_connection *connection, bool rx)
अणु
	पूर्णांक ret;

	/* Handle ENABLED_TX -> ENABLED transitions. */
	अगर (connection->state == GB_CONNECTION_STATE_ENABLED_TX) अणु
		अगर (!(connection->handler && rx))
			वापस 0;

		spin_lock_irq(&connection->lock);
		connection->state = GB_CONNECTION_STATE_ENABLED;
		spin_unlock_irq(&connection->lock);

		वापस 0;
	पूर्ण

	ret = gb_connection_hd_cport_enable(connection);
	अगर (ret)
		वापस ret;

	ret = gb_connection_svc_connection_create(connection);
	अगर (ret)
		जाओ err_hd_cport_clear;

	ret = gb_connection_hd_cport_connected(connection);
	अगर (ret)
		जाओ err_svc_connection_destroy;

	spin_lock_irq(&connection->lock);
	अगर (connection->handler && rx)
		connection->state = GB_CONNECTION_STATE_ENABLED;
	अन्यथा
		connection->state = GB_CONNECTION_STATE_ENABLED_TX;
	spin_unlock_irq(&connection->lock);

	ret = gb_connection_control_connected(connection);
	अगर (ret)
		जाओ err_control_disconnecting;

	वापस 0;

err_control_disconnecting:
	spin_lock_irq(&connection->lock);
	connection->state = GB_CONNECTION_STATE_DISCONNECTING;
	gb_connection_cancel_operations(connection, -ESHUTDOWN);
	spin_unlock_irq(&connection->lock);

	/* Transmit queue should alपढ़ोy be empty. */
	gb_connection_hd_cport_flush(connection);

	gb_connection_control_disconnecting(connection);
	gb_connection_cport_shutकरोwn_phase_1(connection);
	gb_connection_hd_cport_quiesce(connection);
	gb_connection_cport_shutकरोwn_phase_2(connection);
	gb_connection_control_disconnected(connection);
	connection->state = GB_CONNECTION_STATE_DISABLED;
err_svc_connection_destroy:
	gb_connection_svc_connection_destroy(connection);
err_hd_cport_clear:
	gb_connection_hd_cport_clear(connection);

	gb_connection_hd_cport_disable(connection);

	वापस ret;
पूर्ण

पूर्णांक gb_connection_enable(काष्ठा gb_connection *connection)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&connection->mutex);

	अगर (connection->state == GB_CONNECTION_STATE_ENABLED)
		जाओ out_unlock;

	ret = _gb_connection_enable(connection, true);
	अगर (!ret)
		trace_gb_connection_enable(connection);

out_unlock:
	mutex_unlock(&connection->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_enable);

पूर्णांक gb_connection_enable_tx(काष्ठा gb_connection *connection)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&connection->mutex);

	अगर (connection->state == GB_CONNECTION_STATE_ENABLED) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (connection->state == GB_CONNECTION_STATE_ENABLED_TX)
		जाओ out_unlock;

	ret = _gb_connection_enable(connection, false);
	अगर (!ret)
		trace_gb_connection_enable(connection);

out_unlock:
	mutex_unlock(&connection->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_enable_tx);

व्योम gb_connection_disable_rx(काष्ठा gb_connection *connection)
अणु
	mutex_lock(&connection->mutex);

	spin_lock_irq(&connection->lock);
	अगर (connection->state != GB_CONNECTION_STATE_ENABLED) अणु
		spin_unlock_irq(&connection->lock);
		जाओ out_unlock;
	पूर्ण
	connection->state = GB_CONNECTION_STATE_ENABLED_TX;
	gb_connection_flush_incoming_operations(connection, -ESHUTDOWN);
	spin_unlock_irq(&connection->lock);

	trace_gb_connection_disable(connection);

out_unlock:
	mutex_unlock(&connection->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_disable_rx);

व्योम gb_connection_mode_चयन_prepare(काष्ठा gb_connection *connection)
अणु
	connection->mode_चयन = true;
पूर्ण

व्योम gb_connection_mode_चयन_complete(काष्ठा gb_connection *connection)
अणु
	gb_connection_svc_connection_destroy(connection);
	gb_connection_hd_cport_clear(connection);

	gb_connection_hd_cport_disable(connection);

	connection->mode_चयन = false;
पूर्ण

व्योम gb_connection_disable(काष्ठा gb_connection *connection)
अणु
	mutex_lock(&connection->mutex);

	अगर (connection->state == GB_CONNECTION_STATE_DISABLED)
		जाओ out_unlock;

	trace_gb_connection_disable(connection);

	spin_lock_irq(&connection->lock);
	connection->state = GB_CONNECTION_STATE_DISCONNECTING;
	gb_connection_cancel_operations(connection, -ESHUTDOWN);
	spin_unlock_irq(&connection->lock);

	gb_connection_hd_cport_flush(connection);

	gb_connection_control_disconnecting(connection);
	gb_connection_cport_shutकरोwn_phase_1(connection);
	gb_connection_hd_cport_quiesce(connection);
	gb_connection_cport_shutकरोwn_phase_2(connection);
	gb_connection_control_disconnected(connection);

	connection->state = GB_CONNECTION_STATE_DISABLED;

	/* control-connection tear करोwn is deferred when mode चयनing */
	अगर (!connection->mode_चयन) अणु
		gb_connection_svc_connection_destroy(connection);
		gb_connection_hd_cport_clear(connection);

		gb_connection_hd_cport_disable(connection);
	पूर्ण

out_unlock:
	mutex_unlock(&connection->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_disable);

/* Disable a connection without communicating with the remote end. */
व्योम gb_connection_disable_क्रमced(काष्ठा gb_connection *connection)
अणु
	mutex_lock(&connection->mutex);

	अगर (connection->state == GB_CONNECTION_STATE_DISABLED)
		जाओ out_unlock;

	trace_gb_connection_disable(connection);

	spin_lock_irq(&connection->lock);
	connection->state = GB_CONNECTION_STATE_DISABLED;
	gb_connection_cancel_operations(connection, -ESHUTDOWN);
	spin_unlock_irq(&connection->lock);

	gb_connection_hd_cport_flush(connection);

	gb_connection_svc_connection_destroy(connection);
	gb_connection_hd_cport_clear(connection);

	gb_connection_hd_cport_disable(connection);
out_unlock:
	mutex_unlock(&connection->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_disable_क्रमced);

/* Caller must have disabled the connection beक्रमe destroying it. */
व्योम gb_connection_destroy(काष्ठा gb_connection *connection)
अणु
	अगर (!connection)
		वापस;

	अगर (WARN_ON(connection->state != GB_CONNECTION_STATE_DISABLED))
		gb_connection_disable(connection);

	mutex_lock(&gb_connection_mutex);

	spin_lock_irq(&gb_connections_lock);
	list_del(&connection->bundle_links);
	list_del(&connection->hd_links);
	spin_unlock_irq(&gb_connections_lock);

	destroy_workqueue(connection->wq);

	gb_hd_cport_release(connection->hd, connection->hd_cport_id);
	connection->hd_cport_id = CPORT_ID_BAD;

	mutex_unlock(&gb_connection_mutex);

	gb_connection_put(connection);
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_destroy);

व्योम gb_connection_latency_tag_enable(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	पूर्णांक ret;

	अगर (!hd->driver->latency_tag_enable)
		वापस;

	ret = hd->driver->latency_tag_enable(hd, connection->hd_cport_id);
	अगर (ret) अणु
		dev_err(&connection->hd->dev,
			"%s: failed to enable latency tag: %d\n",
			connection->name, ret);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_latency_tag_enable);

व्योम gb_connection_latency_tag_disable(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	पूर्णांक ret;

	अगर (!hd->driver->latency_tag_disable)
		वापस;

	ret = hd->driver->latency_tag_disable(hd, connection->hd_cport_id);
	अगर (ret) अणु
		dev_err(&connection->hd->dev,
			"%s: failed to disable latency tag: %d\n",
			connection->name, ret);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(gb_connection_latency_tag_disable);
