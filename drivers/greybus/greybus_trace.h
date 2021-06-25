<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus driver and device API
 *
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM greybus

#अगर !defined(_TRACE_GREYBUS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_GREYBUS_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा gb_message;
काष्ठा gb_operation;
काष्ठा gb_connection;
काष्ठा gb_bundle;
काष्ठा gb_host_device;

DECLARE_EVENT_CLASS(gb_message,

	TP_PROTO(काष्ठा gb_message *message),

	TP_ARGS(message),

	TP_STRUCT__entry(
		__field(u16, size)
		__field(u16, operation_id)
		__field(u8, type)
		__field(u8, result)
	),

	TP_fast_assign(
		__entry->size = le16_to_cpu(message->header->size);
		__entry->operation_id =
			le16_to_cpu(message->header->operation_id);
		__entry->type = message->header->type;
		__entry->result = message->header->result;
	),

	TP_prपूर्णांकk("size=%u operation_id=0x%04x type=0x%02x result=0x%02x",
		  __entry->size, __entry->operation_id,
		  __entry->type, __entry->result)
);

#घोषणा DEFINE_MESSAGE_EVENT(name)					\
		DEFINE_EVENT(gb_message, name,				\
				TP_PROTO(काष्ठा gb_message *message),	\
				TP_ARGS(message))

/*
 * Occurs immediately beक्रमe calling a host device's message_send()
 * method.
 */
DEFINE_MESSAGE_EVENT(gb_message_send);

/*
 * Occurs after an incoming request message has been received
 */
DEFINE_MESSAGE_EVENT(gb_message_recv_request);

/*
 * Occurs after an incoming response message has been received,
 * after its matching request has been found.
 */
DEFINE_MESSAGE_EVENT(gb_message_recv_response);

/*
 * Occurs after an operation has been canceled, possibly beक्रमe the
 * cancellation is complete.
 */
DEFINE_MESSAGE_EVENT(gb_message_cancel_outgoing);

/*
 * Occurs when an incoming request is cancelled; अगर the response has
 * been queued क्रम sending, this occurs after it is sent.
 */
DEFINE_MESSAGE_EVENT(gb_message_cancel_incoming);

/*
 * Occurs in the host driver message_send() function just prior to
 * handing off the data to be processed by hardware.
 */
DEFINE_MESSAGE_EVENT(gb_message_submit);

#अघोषित DEFINE_MESSAGE_EVENT

DECLARE_EVENT_CLASS(gb_operation,

	TP_PROTO(काष्ठा gb_operation *operation),

	TP_ARGS(operation),

	TP_STRUCT__entry(
		__field(u16, cport_id)	/* CPort of HD side of connection */
		__field(u16, id)	/* Operation ID */
		__field(u8, type)
		__field(अचिन्हित दीर्घ, flags)
		__field(पूर्णांक, active)
		__field(पूर्णांक, रुकोers)
		__field(पूर्णांक, त्रुटि_सं)
	),

	TP_fast_assign(
		__entry->cport_id = operation->connection->hd_cport_id;
		__entry->id = operation->id;
		__entry->type = operation->type;
		__entry->flags = operation->flags;
		__entry->active = operation->active;
		__entry->रुकोers = atomic_पढ़ो(&operation->रुकोers);
		__entry->त्रुटि_सं = operation->त्रुटि_सं;
	),

	TP_prपूर्णांकk("id=%04x type=0x%02x cport_id=%04x flags=0x%lx active=%d waiters=%d errno=%d",
		  __entry->id, __entry->cport_id, __entry->type, __entry->flags,
		  __entry->active, __entry->रुकोers, __entry->त्रुटि_सं)
);

#घोषणा DEFINE_OPERATION_EVENT(name)					\
		DEFINE_EVENT(gb_operation, name,			\
				TP_PROTO(काष्ठा gb_operation *operation), \
				TP_ARGS(operation))

/*
 * Occurs after a new operation is created क्रम an outgoing request
 * has been successfully created.
 */
DEFINE_OPERATION_EVENT(gb_operation_create);

/*
 * Occurs after a new core operation has been created.
 */
DEFINE_OPERATION_EVENT(gb_operation_create_core);

/*
 * Occurs after a new operation has been created क्रम an incoming
 * request has been successfully created and initialized.
 */
DEFINE_OPERATION_EVENT(gb_operation_create_incoming);

/*
 * Occurs when the last reference to an operation has been dropped,
 * prior to मुक्तing resources.
 */
DEFINE_OPERATION_EVENT(gb_operation_destroy);

/*
 * Occurs when an operation has been marked active, after updating
 * its active count.
 */
DEFINE_OPERATION_EVENT(gb_operation_get_active);

/*
 * Occurs when an operation has been marked active, beक्रमe updating
 * its active count.
 */
DEFINE_OPERATION_EVENT(gb_operation_put_active);

#अघोषित DEFINE_OPERATION_EVENT

DECLARE_EVENT_CLASS(gb_connection,

	TP_PROTO(काष्ठा gb_connection *connection),

	TP_ARGS(connection),

	TP_STRUCT__entry(
		__field(पूर्णांक, hd_bus_id)
		__field(u8, bundle_id)
		/* name contains "hd_cport_id/intf_id:cport_id" */
		__dynamic_array(अक्षर, name, माप(connection->name))
		__field(क्रमागत gb_connection_state, state)
		__field(अचिन्हित दीर्घ, flags)
	),

	TP_fast_assign(
		__entry->hd_bus_id = connection->hd->bus_id;
		__entry->bundle_id = connection->bundle ?
				connection->bundle->id : BUNDLE_ID_NONE;
		स_नकल(__get_str(name), connection->name,
					माप(connection->name));
		__entry->state = connection->state;
		__entry->flags = connection->flags;
	),

	TP_prपूर्णांकk("hd_bus_id=%d bundle_id=0x%02x name=\"%s\" state=%u flags=0x%lx",
		  __entry->hd_bus_id, __entry->bundle_id, __get_str(name),
		  (अचिन्हित पूर्णांक)__entry->state, __entry->flags)
);

#घोषणा DEFINE_CONNECTION_EVENT(name)					\
		DEFINE_EVENT(gb_connection, name,			\
				TP_PROTO(काष्ठा gb_connection *connection), \
				TP_ARGS(connection))

/*
 * Occurs after a new connection is successfully created.
 */
DEFINE_CONNECTION_EVENT(gb_connection_create);

/*
 * Occurs when the last reference to a connection has been dropped,
 * beक्रमe its resources are मुक्तd.
 */
DEFINE_CONNECTION_EVENT(gb_connection_release);

/*
 * Occurs when a new reference to connection is added, currently
 * only when a message over the connection is received.
 */
DEFINE_CONNECTION_EVENT(gb_connection_get);

/*
 * Occurs when a new reference to connection is dropped, after a
 * a received message is handled, or when the connection is
 * destroyed.
 */
DEFINE_CONNECTION_EVENT(gb_connection_put);

/*
 * Occurs when a request to enable a connection is made, either क्रम
 * transmit only, or क्रम both transmit and receive.
 */
DEFINE_CONNECTION_EVENT(gb_connection_enable);

/*
 * Occurs when a request to disable a connection is made, either क्रम
 * receive only, or क्रम both transmit and receive.  Also occurs when
 * a request to क्रमcefully disable a connection is made.
 */
DEFINE_CONNECTION_EVENT(gb_connection_disable);

#अघोषित DEFINE_CONNECTION_EVENT

DECLARE_EVENT_CLASS(gb_bundle,

	TP_PROTO(काष्ठा gb_bundle *bundle),

	TP_ARGS(bundle),

	TP_STRUCT__entry(
		__field(u8, पूर्णांकf_id)
		__field(u8, id)
		__field(u8, class)
		__field(माप_प्रकार, num_cports)
	),

	TP_fast_assign(
		__entry->पूर्णांकf_id = bundle->पूर्णांकf->पूर्णांकerface_id;
		__entry->id = bundle->id;
		__entry->class = bundle->class;
		__entry->num_cports = bundle->num_cports;
	),

	TP_prपूर्णांकk("intf_id=0x%02x id=%02x class=0x%02x num_cports=%zu",
		  __entry->पूर्णांकf_id, __entry->id, __entry->class,
		  __entry->num_cports)
);

#घोषणा DEFINE_BUNDLE_EVENT(name)					\
		DEFINE_EVENT(gb_bundle, name,			\
				TP_PROTO(काष्ठा gb_bundle *bundle), \
				TP_ARGS(bundle))

/*
 * Occurs after a new bundle is successfully created.
 */
DEFINE_BUNDLE_EVENT(gb_bundle_create);

/*
 * Occurs when the last reference to a bundle has been dropped,
 * beक्रमe its resources are मुक्तd.
 */
DEFINE_BUNDLE_EVENT(gb_bundle_release);

/*
 * Occurs when a bundle is added to an पूर्णांकerface when the पूर्णांकerface
 * is enabled.
 */
DEFINE_BUNDLE_EVENT(gb_bundle_add);

/*
 * Occurs when a रेजिस्टरed bundle माला_लो destroyed, normally at the
 * समय an पूर्णांकerface is disabled.
 */
DEFINE_BUNDLE_EVENT(gb_bundle_destroy);

#अघोषित DEFINE_BUNDLE_EVENT

DECLARE_EVENT_CLASS(gb_पूर्णांकerface,

	TP_PROTO(काष्ठा gb_पूर्णांकerface *पूर्णांकf),

	TP_ARGS(पूर्णांकf),

	TP_STRUCT__entry(
		__field(u8, module_id)
		__field(u8, id)		/* Interface id */
		__field(u8, device_id)
		__field(पूर्णांक, disconnected)	/* bool */
		__field(पूर्णांक, ejected)		/* bool */
		__field(पूर्णांक, active)		/* bool */
		__field(पूर्णांक, enabled)		/* bool */
		__field(पूर्णांक, mode_चयन)	/* bool */
	),

	TP_fast_assign(
		__entry->module_id = पूर्णांकf->module->module_id;
		__entry->id = पूर्णांकf->पूर्णांकerface_id;
		__entry->device_id = पूर्णांकf->device_id;
		__entry->disconnected = पूर्णांकf->disconnected;
		__entry->ejected = पूर्णांकf->ejected;
		__entry->active = पूर्णांकf->active;
		__entry->enabled = पूर्णांकf->enabled;
		__entry->mode_चयन = पूर्णांकf->mode_चयन;
	),

	TP_prपूर्णांकk("intf_id=%u device_id=%u module_id=%u D=%d J=%d A=%d E=%d M=%d",
		__entry->id, __entry->device_id, __entry->module_id,
		__entry->disconnected, __entry->ejected, __entry->active,
		__entry->enabled, __entry->mode_चयन)
);

#घोषणा DEFINE_INTERFACE_EVENT(name)					\
		DEFINE_EVENT(gb_पूर्णांकerface, name,			\
				TP_PROTO(काष्ठा gb_पूर्णांकerface *पूर्णांकf),	\
				TP_ARGS(पूर्णांकf))

/*
 * Occurs after a new पूर्णांकerface is successfully created.
 */
DEFINE_INTERFACE_EVENT(gb_पूर्णांकerface_create);

/*
 * Occurs after the last reference to an पूर्णांकerface has been dropped.
 */
DEFINE_INTERFACE_EVENT(gb_पूर्णांकerface_release);

/*
 * Occurs after an पूर्णांकerface been रेजिस्टरd.
 */
DEFINE_INTERFACE_EVENT(gb_पूर्णांकerface_add);

/*
 * Occurs when a रेजिस्टरed पूर्णांकerface माला_लो deरेजिस्टरd.
 */
DEFINE_INTERFACE_EVENT(gb_पूर्णांकerface_del);

/*
 * Occurs when a रेजिस्टरed पूर्णांकerface has been successfully
 * activated.
 */
DEFINE_INTERFACE_EVENT(gb_पूर्णांकerface_activate);

/*
 * Occurs when an activated पूर्णांकerface is being deactivated.
 */
DEFINE_INTERFACE_EVENT(gb_पूर्णांकerface_deactivate);

/*
 * Occurs when an पूर्णांकerface has been successfully enabled.
 */
DEFINE_INTERFACE_EVENT(gb_पूर्णांकerface_enable);

/*
 * Occurs when an enabled पूर्णांकerface is being disabled.
 */
DEFINE_INTERFACE_EVENT(gb_पूर्णांकerface_disable);

#अघोषित DEFINE_INTERFACE_EVENT

DECLARE_EVENT_CLASS(gb_module,

	TP_PROTO(काष्ठा gb_module *module),

	TP_ARGS(module),

	TP_STRUCT__entry(
		__field(पूर्णांक, hd_bus_id)
		__field(u8, module_id)
		__field(माप_प्रकार, num_पूर्णांकerfaces)
		__field(पूर्णांक, disconnected)	/* bool */
	),

	TP_fast_assign(
		__entry->hd_bus_id = module->hd->bus_id;
		__entry->module_id = module->module_id;
		__entry->num_पूर्णांकerfaces = module->num_पूर्णांकerfaces;
		__entry->disconnected = module->disconnected;
	),

	TP_prपूर्णांकk("hd_bus_id=%d module_id=%u num_interfaces=%zu disconnected=%d",
		__entry->hd_bus_id, __entry->module_id,
		__entry->num_पूर्णांकerfaces, __entry->disconnected)
);

#घोषणा DEFINE_MODULE_EVENT(name)					\
		DEFINE_EVENT(gb_module, name,				\
				TP_PROTO(काष्ठा gb_module *module),	\
				TP_ARGS(module))

/*
 * Occurs after a new module is successfully created, beक्रमe
 * creating any of its पूर्णांकerfaces.
 */
DEFINE_MODULE_EVENT(gb_module_create);

/*
 * Occurs after the last reference to a module has been dropped.
 */
DEFINE_MODULE_EVENT(gb_module_release);

/*
 * Occurs after a module is successfully created, beक्रमe रेजिस्टरing
 * any of its पूर्णांकerfaces.
 */
DEFINE_MODULE_EVENT(gb_module_add);

/*
 * Occurs when a module is deleted, beक्रमe deरेजिस्टरing its
 * पूर्णांकerfaces.
 */
DEFINE_MODULE_EVENT(gb_module_del);

#अघोषित DEFINE_MODULE_EVENT

DECLARE_EVENT_CLASS(gb_host_device,

	TP_PROTO(काष्ठा gb_host_device *hd),

	TP_ARGS(hd),

	TP_STRUCT__entry(
		__field(पूर्णांक, bus_id)
		__field(माप_प्रकार, num_cports)
		__field(माप_प्रकार, buffer_size_max)
	),

	TP_fast_assign(
		__entry->bus_id = hd->bus_id;
		__entry->num_cports = hd->num_cports;
		__entry->buffer_size_max = hd->buffer_size_max;
	),

	TP_prपूर्णांकk("bus_id=%d num_cports=%zu mtu=%zu",
		__entry->bus_id, __entry->num_cports,
		__entry->buffer_size_max)
);

#घोषणा DEFINE_HD_EVENT(name)						\
		DEFINE_EVENT(gb_host_device, name,			\
				TP_PROTO(काष्ठा gb_host_device *hd),	\
				TP_ARGS(hd))

/*
 * Occurs after a new host device is successfully created, beक्रमe
 * its SVC has been set up.
 */
DEFINE_HD_EVENT(gb_hd_create);

/*
 * Occurs after the last reference to a host device has been
 * dropped.
 */
DEFINE_HD_EVENT(gb_hd_release);

/*
 * Occurs after a new host device has been added, after the
 * connection to its SVC has been enabled.
 */
DEFINE_HD_EVENT(gb_hd_add);

/*
 * Occurs when a host device is being disconnected from the AP USB
 * host controller.
 */
DEFINE_HD_EVENT(gb_hd_del);

/*
 * Occurs when a host device has passed received data to the Greybus
 * core, after it has been determined it is destined क्रम a valid
 * CPort.
 */
DEFINE_HD_EVENT(gb_hd_in);

#अघोषित DEFINE_HD_EVENT

#पूर्ण_अगर /* _TRACE_GREYBUS_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

/*
 * TRACE_INCLUDE_खाता is not needed अगर the filename and TRACE_SYSTEM are equal
 */
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता greybus_trace
#समावेश <trace/define_trace.h>

