<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Broadcom BM2835 V4L2 driver
 *
 * Copyright तऊ 2013 Raspberry Pi (Trading) Ltd.
 *
 * Authors: Vincent Sanders @ Collabora
 *          Dave Stevenson @ Broadcom
 *		(now dave.stevenson@raspberrypi.org)
 *          Simon Mellor @ Broadcom
 *          Luke Diamand @ Broadcom
 *
 * V4L2 driver MMAL vchiq पूर्णांकerface code
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/raspberrypi/vchiq.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "mmal-common.h"
#समावेश "mmal-vchiq.h"
#समावेश "mmal-msg.h"

/*
 * maximum number of components supported.
 * This matches the maximum permitted by शेष on the VPU
 */
#घोषणा VCHIQ_MMAL_MAX_COMPONENTS 64

/*
 * Timeout क्रम synchronous msg responses in seconds.
 * Helpful to increase this अगर stopping in the VPU debugger.
 */
#घोषणा SYNC_MSG_TIMEOUT       3

/*#घोषणा FULL_MSG_DUMP 1*/

#अगर_घोषित DEBUG
अटल स्थिर अक्षर *स्थिर msg_type_names[] = अणु
	"UNKNOWN",
	"QUIT",
	"SERVICE_CLOSED",
	"GET_VERSION",
	"COMPONENT_CREATE",
	"COMPONENT_DESTROY",
	"COMPONENT_ENABLE",
	"COMPONENT_DISABLE",
	"PORT_INFO_GET",
	"PORT_INFO_SET",
	"PORT_ACTION",
	"BUFFER_FROM_HOST",
	"BUFFER_TO_HOST",
	"GET_STATS",
	"PORT_PARAMETER_SET",
	"PORT_PARAMETER_GET",
	"EVENT_TO_HOST",
	"GET_CORE_STATS_FOR_PORT",
	"OPAQUE_ALLOCATOR",
	"CONSUME_MEM",
	"LMK",
	"OPAQUE_ALLOCATOR_DESC",
	"DRM_GET_LHS32",
	"DRM_GET_TIME",
	"BUFFER_FROM_HOST_ZEROLEN",
	"PORT_FLUSH",
	"HOST_LOG",
पूर्ण;
#पूर्ण_अगर

अटल स्थिर अक्षर *स्थिर port_action_type_names[] = अणु
	"UNKNOWN",
	"ENABLE",
	"DISABLE",
	"FLUSH",
	"CONNECT",
	"DISCONNECT",
	"SET_REQUIREMENTS",
पूर्ण;

#अगर defined(DEBUG)
#अगर defined(FULL_MSG_DUMP)
#घोषणा DBG_DUMP_MSG(MSG, MSG_LEN, TITLE)				\
	करो अणु								\
		pr_debug(TITLE" type:%s(%d) length:%d\n",		\
			 msg_type_names[(MSG)->h.type],			\
			 (MSG)->h.type, (MSG_LEN));			\
		prपूर्णांक_hex_dump(KERN_DEBUG, "<<h: ", DUMP_PREFIX_OFFSET,	\
			       16, 4, (MSG),				\
			       माप(काष्ठा mmal_msg_header), 1);	\
		prपूर्णांक_hex_dump(KERN_DEBUG, "<<p: ", DUMP_PREFIX_OFFSET,	\
			       16, 4,					\
			       ((u8 *)(MSG)) + माप(काष्ठा mmal_msg_header),\
			       (MSG_LEN) - माप(काष्ठा mmal_msg_header), 1); \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा DBG_DUMP_MSG(MSG, MSG_LEN, TITLE)				\
	अणु								\
		pr_debug(TITLE" type:%s(%d) length:%d\n",		\
			 msg_type_names[(MSG)->h.type],			\
			 (MSG)->h.type, (MSG_LEN));			\
	पूर्ण
#पूर्ण_अगर
#अन्यथा
#घोषणा DBG_DUMP_MSG(MSG, MSG_LEN, TITLE)
#पूर्ण_अगर

काष्ठा vchiq_mmal_instance;

/* normal message context */
काष्ठा mmal_msg_context अणु
	काष्ठा vchiq_mmal_instance *instance;

	/* Index in the context_map idr so that we can find the
	 * mmal_msg_context again when servicing the VCHI reply.
	 */
	पूर्णांक handle;

	जोड़ अणु
		काष्ठा अणु
			/* work काष्ठा क्रम buffer_cb callback */
			काष्ठा work_काष्ठा work;
			/* work काष्ठा क्रम deferred callback */
			काष्ठा work_काष्ठा buffer_to_host_work;
			/* mmal instance */
			काष्ठा vchiq_mmal_instance *instance;
			/* mmal port */
			काष्ठा vchiq_mmal_port *port;
			/* actual buffer used to store bulk reply */
			काष्ठा mmal_buffer *buffer;
			/* amount of buffer used */
			अचिन्हित दीर्घ buffer_used;
			/* MMAL buffer flags */
			u32 mmal_flags;
			/* Presentation and Decode बारtamps */
			s64 pts;
			s64 dts;

			पूर्णांक status;	/* context status */

		पूर्ण bulk;		/* bulk data */

		काष्ठा अणु
			/* message handle to release */
			काष्ठा vchiq_header *msg_handle;
			/* poपूर्णांकer to received message */
			काष्ठा mmal_msg *msg;
			/* received message length */
			u32 msg_len;
			/* completion upon reply */
			काष्ठा completion cmplt;
		पूर्ण sync;		/* synchronous response */
	पूर्ण u;

पूर्ण;

काष्ठा vchiq_mmal_instance अणु
	अचिन्हित पूर्णांक service_handle;

	/* ensure serialised access to service */
	काष्ठा mutex vchiq_mutex;

	/* vदो_स्मृति page to receive scratch bulk xfers पूर्णांकo */
	व्योम *bulk_scratch;

	काष्ठा idr context_map;
	/* protect accesses to context_map */
	काष्ठा mutex context_map_lock;

	काष्ठा vchiq_mmal_component component[VCHIQ_MMAL_MAX_COMPONENTS];

	/* ordered workqueue to process all bulk operations */
	काष्ठा workqueue_काष्ठा *bulk_wq;

	/* handle क्रम a vchiq instance */
	काष्ठा vchiq_instance *vchiq_instance;
पूर्ण;

अटल काष्ठा mmal_msg_context *
get_msg_context(काष्ठा vchiq_mmal_instance *instance)
अणु
	काष्ठा mmal_msg_context *msg_context;
	पूर्णांक handle;

	/* toकरो: should this be allocated from a pool to aव्योम kzalloc */
	msg_context = kzalloc(माप(*msg_context), GFP_KERNEL);

	अगर (!msg_context)
		वापस ERR_PTR(-ENOMEM);

	/* Create an ID that will be passed aदीर्घ with our message so
	 * that when we service the VCHI reply, we can look up what
	 * message is being replied to.
	 */
	mutex_lock(&instance->context_map_lock);
	handle = idr_alloc(&instance->context_map, msg_context,
			   0, 0, GFP_KERNEL);
	mutex_unlock(&instance->context_map_lock);

	अगर (handle < 0) अणु
		kमुक्त(msg_context);
		वापस ERR_PTR(handle);
	पूर्ण

	msg_context->instance = instance;
	msg_context->handle = handle;

	वापस msg_context;
पूर्ण

अटल काष्ठा mmal_msg_context *
lookup_msg_context(काष्ठा vchiq_mmal_instance *instance, पूर्णांक handle)
अणु
	वापस idr_find(&instance->context_map, handle);
पूर्ण

अटल व्योम
release_msg_context(काष्ठा mmal_msg_context *msg_context)
अणु
	काष्ठा vchiq_mmal_instance *instance = msg_context->instance;

	mutex_lock(&instance->context_map_lock);
	idr_हटाओ(&instance->context_map, msg_context->handle);
	mutex_unlock(&instance->context_map_lock);
	kमुक्त(msg_context);
पूर्ण

/* deals with receipt of event to host message */
अटल व्योम event_to_host_cb(काष्ठा vchiq_mmal_instance *instance,
			     काष्ठा mmal_msg *msg, u32 msg_len)
अणु
	pr_debug("unhandled event\n");
	pr_debug("component:%u port type:%d num:%d cmd:0x%x length:%d\n",
		 msg->u.event_to_host.client_component,
		 msg->u.event_to_host.port_type,
		 msg->u.event_to_host.port_num,
		 msg->u.event_to_host.cmd, msg->u.event_to_host.length);
पूर्ण

/* workqueue scheduled callback
 *
 * we करो this because it is important we करो not call any other vchiq
 * sync calls from witin the message delivery thपढ़ो
 */
अटल व्योम buffer_work_cb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmal_msg_context *msg_context =
		container_of(work, काष्ठा mmal_msg_context, u.bulk.work);
	काष्ठा mmal_buffer *buffer = msg_context->u.bulk.buffer;

	अगर (!buffer) अणु
		pr_err("%s: ctx: %p, No mmal buffer to pass details\n",
		       __func__, msg_context);
		वापस;
	पूर्ण

	buffer->length = msg_context->u.bulk.buffer_used;
	buffer->mmal_flags = msg_context->u.bulk.mmal_flags;
	buffer->dts = msg_context->u.bulk.dts;
	buffer->pts = msg_context->u.bulk.pts;

	atomic_dec(&msg_context->u.bulk.port->buffers_with_vpu);

	msg_context->u.bulk.port->buffer_cb(msg_context->u.bulk.instance,
					    msg_context->u.bulk.port,
					    msg_context->u.bulk.status,
					    msg_context->u.bulk.buffer);
पूर्ण

/* workqueue scheduled callback to handle receiving buffers
 *
 * VCHI will allow up to 4 bulk receives to be scheduled beक्रमe blocking.
 * If we block in the service_callback context then we can't process the
 * VCHI_CALLBACK_BULK_RECEIVED message that would otherwise allow the blocked
 * vchiq_bulk_receive() call to complete.
 */
अटल व्योम buffer_to_host_work_cb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmal_msg_context *msg_context =
		container_of(work, काष्ठा mmal_msg_context,
			     u.bulk.buffer_to_host_work);
	काष्ठा vchiq_mmal_instance *instance = msg_context->instance;
	अचिन्हित दीर्घ len = msg_context->u.bulk.buffer_used;
	पूर्णांक ret;

	अगर (!len)
		/* Dummy receive to ensure the buffers reमुख्य in order */
		len = 8;
	/* queue the bulk submission */
	vchiq_use_service(instance->service_handle);
	ret = vchiq_bulk_receive(instance->service_handle,
				 msg_context->u.bulk.buffer->buffer,
				 /* Actual receive needs to be a multiple
				  * of 4 bytes
				  */
				(len + 3) & ~3,
				msg_context,
				VCHIQ_BULK_MODE_CALLBACK);

	vchiq_release_service(instance->service_handle);

	अगर (ret != 0)
		pr_err("%s: ctx: %p, vchiq_bulk_receive failed %d\n",
		       __func__, msg_context, ret);
पूर्ण

/* enqueue a bulk receive क्रम a given message context */
अटल पूर्णांक bulk_receive(काष्ठा vchiq_mmal_instance *instance,
			काष्ठा mmal_msg *msg,
			काष्ठा mmal_msg_context *msg_context)
अणु
	अचिन्हित दीर्घ rd_len;

	rd_len = msg->u.buffer_from_host.buffer_header.length;

	अगर (!msg_context->u.bulk.buffer) अणु
		pr_err("bulk.buffer not configured - error in buffer_from_host\n");

		/* toकरो: this is a serious error, we should never have
		 * committed a buffer_to_host operation to the mmal
		 * port without the buffer to back it up (underflow
		 * handling) and there is no obvious way to deal with
		 * this - how is the mmal servie going to react when
		 * we fail to करो the xfer and reschedule a buffer when
		 * it arrives? perhaps a starved flag to indicate a
		 * रुकोing bulk receive?
		 */

		वापस -EINVAL;
	पूर्ण

	/* ensure we करो not overrun the available buffer */
	अगर (rd_len > msg_context->u.bulk.buffer->buffer_size) अणु
		rd_len = msg_context->u.bulk.buffer->buffer_size;
		pr_warn("short read as not enough receive buffer space\n");
		/* toकरो: is this the correct response, what happens to
		 * the rest of the message data?
		 */
	पूर्ण

	/* store length */
	msg_context->u.bulk.buffer_used = rd_len;
	msg_context->u.bulk.dts = msg->u.buffer_from_host.buffer_header.dts;
	msg_context->u.bulk.pts = msg->u.buffer_from_host.buffer_header.pts;

	queue_work(msg_context->instance->bulk_wq,
		   &msg_context->u.bulk.buffer_to_host_work);

	वापस 0;
पूर्ण

/* data in message, स_नकल from packet पूर्णांकo output buffer */
अटल पूर्णांक अंतरभूत_receive(काष्ठा vchiq_mmal_instance *instance,
			  काष्ठा mmal_msg *msg,
			  काष्ठा mmal_msg_context *msg_context)
अणु
	स_नकल(msg_context->u.bulk.buffer->buffer,
	       msg->u.buffer_from_host.लघु_data,
	       msg->u.buffer_from_host.payload_in_message);

	msg_context->u.bulk.buffer_used =
	    msg->u.buffer_from_host.payload_in_message;

	वापस 0;
पूर्ण

/* queue the buffer availability with MMAL_MSG_TYPE_BUFFER_FROM_HOST */
अटल पूर्णांक
buffer_from_host(काष्ठा vchiq_mmal_instance *instance,
		 काष्ठा vchiq_mmal_port *port, काष्ठा mmal_buffer *buf)
अणु
	काष्ठा mmal_msg_context *msg_context;
	काष्ठा mmal_msg m;
	पूर्णांक ret;

	अगर (!port->enabled)
		वापस -EINVAL;

	pr_debug("instance:%u buffer:%p\n", instance->service_handle, buf);

	/* get context */
	अगर (!buf->msg_context) अणु
		pr_err("%s: msg_context not allocated, buf %p\n", __func__,
		       buf);
		वापस -EINVAL;
	पूर्ण
	msg_context = buf->msg_context;

	/* store bulk message context क्रम when data arrives */
	msg_context->u.bulk.instance = instance;
	msg_context->u.bulk.port = port;
	msg_context->u.bulk.buffer = buf;
	msg_context->u.bulk.buffer_used = 0;

	/* initialise work काष्ठाure पढ़ोy to schedule callback */
	INIT_WORK(&msg_context->u.bulk.work, buffer_work_cb);
	INIT_WORK(&msg_context->u.bulk.buffer_to_host_work,
		  buffer_to_host_work_cb);

	atomic_inc(&port->buffers_with_vpu);

	/* prep the buffer from host message */
	स_रखो(&m, 0xbc, माप(m));	/* just to make debug clearer */

	m.h.type = MMAL_MSG_TYPE_BUFFER_FROM_HOST;
	m.h.magic = MMAL_MAGIC;
	m.h.context = msg_context->handle;
	m.h.status = 0;

	/* drvbuf is our निजी data passed back */
	m.u.buffer_from_host.drvbuf.magic = MMAL_MAGIC;
	m.u.buffer_from_host.drvbuf.component_handle = port->component->handle;
	m.u.buffer_from_host.drvbuf.port_handle = port->handle;
	m.u.buffer_from_host.drvbuf.client_context = msg_context->handle;

	/* buffer header */
	m.u.buffer_from_host.buffer_header.cmd = 0;
	m.u.buffer_from_host.buffer_header.data =
		(u32)(अचिन्हित दीर्घ)buf->buffer;
	m.u.buffer_from_host.buffer_header.alloc_size = buf->buffer_size;
	m.u.buffer_from_host.buffer_header.length = 0;	/* nothing used yet */
	m.u.buffer_from_host.buffer_header.offset = 0;	/* no offset */
	m.u.buffer_from_host.buffer_header.flags = 0;	/* no flags */
	m.u.buffer_from_host.buffer_header.pts = MMAL_TIME_UNKNOWN;
	m.u.buffer_from_host.buffer_header.dts = MMAL_TIME_UNKNOWN;

	/* clear buffer type specअगरic data */
	स_रखो(&m.u.buffer_from_host.buffer_header_type_specअगरic, 0,
	       माप(m.u.buffer_from_host.buffer_header_type_specअगरic));

	/* no payload in message */
	m.u.buffer_from_host.payload_in_message = 0;

	vchiq_use_service(instance->service_handle);

	ret = vchiq_queue_kernel_message(instance->service_handle, &m,
					 माप(काष्ठा mmal_msg_header) +
					 माप(m.u.buffer_from_host));
	अगर (ret)
		atomic_dec(&port->buffers_with_vpu);

	vchiq_release_service(instance->service_handle);

	वापस ret;
पूर्ण

/* deals with receipt of buffer to host message */
अटल व्योम buffer_to_host_cb(काष्ठा vchiq_mmal_instance *instance,
			      काष्ठा mmal_msg *msg, u32 msg_len)
अणु
	काष्ठा mmal_msg_context *msg_context;
	u32 handle;

	pr_debug("%s: instance:%p msg:%p msg_len:%d\n",
		 __func__, instance, msg, msg_len);

	अगर (msg->u.buffer_from_host.drvbuf.magic == MMAL_MAGIC) अणु
		handle = msg->u.buffer_from_host.drvbuf.client_context;
		msg_context = lookup_msg_context(instance, handle);

		अगर (!msg_context) अणु
			pr_err("drvbuf.client_context(%u) is invalid\n",
			       handle);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("MMAL_MSG_TYPE_BUFFER_TO_HOST with bad magic\n");
		वापस;
	पूर्ण

	msg_context->u.bulk.mmal_flags =
				msg->u.buffer_from_host.buffer_header.flags;

	अगर (msg->h.status != MMAL_MSG_STATUS_SUCCESS) अणु
		/* message reception had an error */
		pr_warn("error %d in reply\n", msg->h.status);

		msg_context->u.bulk.status = msg->h.status;

	पूर्ण अन्यथा अगर (msg->u.buffer_from_host.buffer_header.length == 0) अणु
		/* empty buffer */
		अगर (msg->u.buffer_from_host.buffer_header.flags &
		    MMAL_BUFFER_HEADER_FLAG_EOS) अणु
			msg_context->u.bulk.status =
			    bulk_receive(instance, msg, msg_context);
			अगर (msg_context->u.bulk.status == 0)
				वापस;	/* successful bulk submission, bulk
					 * completion will trigger callback
					 */
		पूर्ण अन्यथा अणु
			/* करो callback with empty buffer - not EOS though */
			msg_context->u.bulk.status = 0;
			msg_context->u.bulk.buffer_used = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (msg->u.buffer_from_host.payload_in_message == 0) अणु
		/* data is not in message, queue a bulk receive */
		msg_context->u.bulk.status =
		    bulk_receive(instance, msg, msg_context);
		अगर (msg_context->u.bulk.status == 0)
			वापस;	/* successful bulk submission, bulk
				 * completion will trigger callback
				 */

		/* failed to submit buffer, this will end badly */
		pr_err("error %d on bulk submission\n",
		       msg_context->u.bulk.status);

	पूर्ण अन्यथा अगर (msg->u.buffer_from_host.payload_in_message <=
		   MMAL_VC_SHORT_DATA) अणु
		/* data payload within message */
		msg_context->u.bulk.status = अंतरभूत_receive(instance, msg,
							    msg_context);
	पूर्ण अन्यथा अणु
		pr_err("message with invalid short payload\n");

		/* संकेत error */
		msg_context->u.bulk.status = -EINVAL;
		msg_context->u.bulk.buffer_used =
		    msg->u.buffer_from_host.payload_in_message;
	पूर्ण

	/* schedule the port callback */
	schedule_work(&msg_context->u.bulk.work);
पूर्ण

अटल व्योम bulk_receive_cb(काष्ठा vchiq_mmal_instance *instance,
			    काष्ठा mmal_msg_context *msg_context)
अणु
	msg_context->u.bulk.status = 0;

	/* schedule the port callback */
	schedule_work(&msg_context->u.bulk.work);
पूर्ण

अटल व्योम bulk_पात_cb(काष्ठा vchiq_mmal_instance *instance,
			  काष्ठा mmal_msg_context *msg_context)
अणु
	pr_err("%s: bulk ABORTED msg_context:%p\n", __func__, msg_context);

	msg_context->u.bulk.status = -EINTR;

	schedule_work(&msg_context->u.bulk.work);
पूर्ण

/* incoming event service callback */
अटल क्रमागत vchiq_status service_callback(क्रमागत vchiq_reason reason,
					  काष्ठा vchiq_header *header,
					  अचिन्हित पूर्णांक handle, व्योम *bulk_ctx)
अणु
	काष्ठा vchiq_mmal_instance *instance = vchiq_get_service_userdata(handle);
	u32 msg_len;
	काष्ठा mmal_msg *msg;
	काष्ठा mmal_msg_context *msg_context;

	अगर (!instance) अणु
		pr_err("Message callback passed NULL instance\n");
		वापस VCHIQ_SUCCESS;
	पूर्ण

	चयन (reason) अणु
	हाल VCHIQ_MESSAGE_AVAILABLE:
		msg = (व्योम *)header->data;
		msg_len = header->size;

		DBG_DUMP_MSG(msg, msg_len, "<<< reply message");

		/* handling is dअगरferent क्रम buffer messages */
		चयन (msg->h.type) अणु
		हाल MMAL_MSG_TYPE_BUFFER_FROM_HOST:
			vchiq_release_message(handle, header);
			अवरोध;

		हाल MMAL_MSG_TYPE_EVENT_TO_HOST:
			event_to_host_cb(instance, msg, msg_len);
			vchiq_release_message(handle, header);

			अवरोध;

		हाल MMAL_MSG_TYPE_BUFFER_TO_HOST:
			buffer_to_host_cb(instance, msg, msg_len);
			vchiq_release_message(handle, header);
			अवरोध;

		शेष:
			/* messages dependent on header context to complete */
			अगर (!msg->h.context) अणु
				pr_err("received message context was null!\n");
				vchiq_release_message(handle, header);
				अवरोध;
			पूर्ण

			msg_context = lookup_msg_context(instance,
							 msg->h.context);
			अगर (!msg_context) अणु
				pr_err("received invalid message context %u!\n",
				       msg->h.context);
				vchiq_release_message(handle, header);
				अवरोध;
			पूर्ण

			/* fill in context values */
			msg_context->u.sync.msg_handle = header;
			msg_context->u.sync.msg = msg;
			msg_context->u.sync.msg_len = msg_len;

			/* toकरो: should this check (completion_करोne()
			 * == 1) क्रम no one रुकोing? or करो we need a
			 * flag to tell us the completion has been
			 * पूर्णांकerrupted so we can मुक्त the message and
			 * its context. This probably also solves the
			 * message arriving after पूर्णांकerruption toकरो
			 * below
			 */

			/* complete message so caller knows it happened */
			complete(&msg_context->u.sync.cmplt);
			अवरोध;
		पूर्ण

		अवरोध;

	हाल VCHIQ_BULK_RECEIVE_DONE:
		bulk_receive_cb(instance, bulk_ctx);
		अवरोध;

	हाल VCHIQ_BULK_RECEIVE_ABORTED:
		bulk_पात_cb(instance, bulk_ctx);
		अवरोध;

	हाल VCHIQ_SERVICE_CLOSED:
		/* TODO: consider अगर this requires action अगर received when
		 * driver is not explicitly closing the service
		 */
		अवरोध;

	शेष:
		pr_err("Received unhandled message reason %d\n", reason);
		अवरोध;
	पूर्ण

	वापस VCHIQ_SUCCESS;
पूर्ण

अटल पूर्णांक send_synchronous_mmal_msg(काष्ठा vchiq_mmal_instance *instance,
				     काष्ठा mmal_msg *msg,
				     अचिन्हित पूर्णांक payload_len,
				     काष्ठा mmal_msg **msg_out,
				     काष्ठा vchiq_header **msg_handle)
अणु
	काष्ठा mmal_msg_context *msg_context;
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;

	/* payload size must not cause message to exceed max size */
	अगर (payload_len >
	    (MMAL_MSG_MAX_SIZE - माप(काष्ठा mmal_msg_header))) अणु
		pr_err("payload length %d exceeds max:%d\n", payload_len,
		       (पूर्णांक)(MMAL_MSG_MAX_SIZE -
			    माप(काष्ठा mmal_msg_header)));
		वापस -EINVAL;
	पूर्ण

	msg_context = get_msg_context(instance);
	अगर (IS_ERR(msg_context))
		वापस PTR_ERR(msg_context);

	init_completion(&msg_context->u.sync.cmplt);

	msg->h.magic = MMAL_MAGIC;
	msg->h.context = msg_context->handle;
	msg->h.status = 0;

	DBG_DUMP_MSG(msg, (माप(काष्ठा mmal_msg_header) + payload_len),
		     ">>> sync message");

	vchiq_use_service(instance->service_handle);

	ret = vchiq_queue_kernel_message(instance->service_handle, msg,
					 माप(काष्ठा mmal_msg_header) +
					 payload_len);

	vchiq_release_service(instance->service_handle);

	अगर (ret) अणु
		pr_err("error %d queuing message\n", ret);
		release_msg_context(msg_context);
		वापस ret;
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&msg_context->u.sync.cmplt,
					      SYNC_MSG_TIMEOUT * HZ);
	अगर (समयout == 0) अणु
		pr_err("timed out waiting for sync completion\n");
		ret = -ETIME;
		/* toकरो: what happens अगर the message arrives after पातing */
		release_msg_context(msg_context);
		वापस ret;
	पूर्ण

	*msg_out = msg_context->u.sync.msg;
	*msg_handle = msg_context->u.sync.msg_handle;
	release_msg_context(msg_context);

	वापस 0;
पूर्ण

अटल व्योम dump_port_info(काष्ठा vchiq_mmal_port *port)
अणु
	pr_debug("port handle:0x%x enabled:%d\n", port->handle, port->enabled);

	pr_debug("buffer minimum num:%d size:%d align:%d\n",
		 port->minimum_buffer.num,
		 port->minimum_buffer.size, port->minimum_buffer.alignment);

	pr_debug("buffer recommended num:%d size:%d align:%d\n",
		 port->recommended_buffer.num,
		 port->recommended_buffer.size,
		 port->recommended_buffer.alignment);

	pr_debug("buffer current values num:%d size:%d align:%d\n",
		 port->current_buffer.num,
		 port->current_buffer.size, port->current_buffer.alignment);

	pr_debug("elementary stream: type:%d encoding:0x%x variant:0x%x\n",
		 port->क्रमmat.type,
		 port->क्रमmat.encoding, port->क्रमmat.encoding_variant);

	pr_debug("		    bitrate:%d flags:0x%x\n",
		 port->क्रमmat.bitrate, port->क्रमmat.flags);

	अगर (port->क्रमmat.type == MMAL_ES_TYPE_VIDEO) अणु
		pr_debug
		    ("es video format: width:%d height:%d colourspace:0x%x\n",
		     port->es.video.width, port->es.video.height,
		     port->es.video.color_space);

		pr_debug("		 : crop xywh %d,%d,%d,%d\n",
			 port->es.video.crop.x,
			 port->es.video.crop.y,
			 port->es.video.crop.width, port->es.video.crop.height);
		pr_debug("		 : framerate %d/%d  aspect %d/%d\n",
			 port->es.video.frame_rate.num,
			 port->es.video.frame_rate.den,
			 port->es.video.par.num, port->es.video.par.den);
	पूर्ण
पूर्ण

अटल व्योम port_to_mmal_msg(काष्ठा vchiq_mmal_port *port, काष्ठा mmal_port *p)
अणु
	/* toकरो करो पढ़ोonly fields need setting at all? */
	p->type = port->type;
	p->index = port->index;
	p->index_all = 0;
	p->is_enabled = port->enabled;
	p->buffer_num_min = port->minimum_buffer.num;
	p->buffer_size_min = port->minimum_buffer.size;
	p->buffer_alignment_min = port->minimum_buffer.alignment;
	p->buffer_num_recommended = port->recommended_buffer.num;
	p->buffer_size_recommended = port->recommended_buffer.size;

	/* only three writable fields in a port */
	p->buffer_num = port->current_buffer.num;
	p->buffer_size = port->current_buffer.size;
	p->userdata = (u32)(अचिन्हित दीर्घ)port;
पूर्ण

अटल पूर्णांक port_info_set(काष्ठा vchiq_mmal_instance *instance,
			 काष्ठा vchiq_mmal_port *port)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	pr_debug("setting port info port %p\n", port);
	अगर (!port)
		वापस -1;
	dump_port_info(port);

	m.h.type = MMAL_MSG_TYPE_PORT_INFO_SET;

	m.u.port_info_set.component_handle = port->component->handle;
	m.u.port_info_set.port_type = port->type;
	m.u.port_info_set.port_index = port->index;

	port_to_mmal_msg(port, &m.u.port_info_set.port);

	/* elementary stream क्रमmat setup */
	m.u.port_info_set.क्रमmat.type = port->क्रमmat.type;
	m.u.port_info_set.क्रमmat.encoding = port->क्रमmat.encoding;
	m.u.port_info_set.क्रमmat.encoding_variant =
	    port->क्रमmat.encoding_variant;
	m.u.port_info_set.क्रमmat.bitrate = port->क्रमmat.bitrate;
	m.u.port_info_set.क्रमmat.flags = port->क्रमmat.flags;

	स_नकल(&m.u.port_info_set.es, &port->es,
	       माप(जोड़ mmal_es_specअगरic_क्रमmat));

	m.u.port_info_set.क्रमmat.extradata_size = port->क्रमmat.extradata_size;
	स_नकल(&m.u.port_info_set.extradata, port->क्रमmat.extradata,
	       port->क्रमmat.extradata_size);

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(m.u.port_info_set),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != MMAL_MSG_TYPE_PORT_INFO_SET) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	/* वापस operation status */
	ret = -rmsg->u.port_info_get_reply.status;

	pr_debug("%s:result:%d component:0x%x port:%d\n", __func__, ret,
		 port->component->handle, port->handle);

release_msg:
	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

/* use port info get message to retrieve port inक्रमmation */
अटल पूर्णांक port_info_get(काष्ठा vchiq_mmal_instance *instance,
			 काष्ठा vchiq_mmal_port *port)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	/* port info समय */
	m.h.type = MMAL_MSG_TYPE_PORT_INFO_GET;
	m.u.port_info_get.component_handle = port->component->handle;
	m.u.port_info_get.port_type = port->type;
	m.u.port_info_get.index = port->index;

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(m.u.port_info_get),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != MMAL_MSG_TYPE_PORT_INFO_GET) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	/* वापस operation status */
	ret = -rmsg->u.port_info_get_reply.status;
	अगर (ret != MMAL_MSG_STATUS_SUCCESS)
		जाओ release_msg;

	अगर (rmsg->u.port_info_get_reply.port.is_enabled == 0)
		port->enabled = 0;
	अन्यथा
		port->enabled = 1;

	/* copy the values out of the message */
	port->handle = rmsg->u.port_info_get_reply.port_handle;

	/* port type and index cached to use on port info set because
	 * it करोes not use a port handle
	 */
	port->type = rmsg->u.port_info_get_reply.port_type;
	port->index = rmsg->u.port_info_get_reply.port_index;

	port->minimum_buffer.num =
	    rmsg->u.port_info_get_reply.port.buffer_num_min;
	port->minimum_buffer.size =
	    rmsg->u.port_info_get_reply.port.buffer_size_min;
	port->minimum_buffer.alignment =
	    rmsg->u.port_info_get_reply.port.buffer_alignment_min;

	port->recommended_buffer.alignment =
	    rmsg->u.port_info_get_reply.port.buffer_alignment_min;
	port->recommended_buffer.num =
	    rmsg->u.port_info_get_reply.port.buffer_num_recommended;

	port->current_buffer.num = rmsg->u.port_info_get_reply.port.buffer_num;
	port->current_buffer.size =
	    rmsg->u.port_info_get_reply.port.buffer_size;

	/* stream क्रमmat */
	port->क्रमmat.type = rmsg->u.port_info_get_reply.क्रमmat.type;
	port->क्रमmat.encoding = rmsg->u.port_info_get_reply.क्रमmat.encoding;
	port->क्रमmat.encoding_variant =
	    rmsg->u.port_info_get_reply.क्रमmat.encoding_variant;
	port->क्रमmat.bitrate = rmsg->u.port_info_get_reply.क्रमmat.bitrate;
	port->क्रमmat.flags = rmsg->u.port_info_get_reply.क्रमmat.flags;

	/* elementary stream क्रमmat */
	स_नकल(&port->es,
	       &rmsg->u.port_info_get_reply.es,
	       माप(जोड़ mmal_es_specअगरic_क्रमmat));
	port->क्रमmat.es = &port->es;

	port->क्रमmat.extradata_size =
	    rmsg->u.port_info_get_reply.क्रमmat.extradata_size;
	स_नकल(port->क्रमmat.extradata,
	       rmsg->u.port_info_get_reply.extradata,
	       port->क्रमmat.extradata_size);

	pr_debug("received port info\n");
	dump_port_info(port);

release_msg:

	pr_debug("%s:result:%d component:0x%x port:%d\n",
		 __func__, ret, port->component->handle, port->handle);

	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

/* create component on vc */
अटल पूर्णांक create_component(काष्ठा vchiq_mmal_instance *instance,
			    काष्ठा vchiq_mmal_component *component,
			    स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	/* build component create message */
	m.h.type = MMAL_MSG_TYPE_COMPONENT_CREATE;
	m.u.component_create.client_component = component->client_component;
	म_नकलन(m.u.component_create.name, name,
		माप(m.u.component_create.name));

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(m.u.component_create),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != m.h.type) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	ret = -rmsg->u.component_create_reply.status;
	अगर (ret != MMAL_MSG_STATUS_SUCCESS)
		जाओ release_msg;

	/* a valid component response received */
	component->handle = rmsg->u.component_create_reply.component_handle;
	component->inमाला_दो = rmsg->u.component_create_reply.input_num;
	component->outमाला_दो = rmsg->u.component_create_reply.output_num;
	component->घड़ीs = rmsg->u.component_create_reply.घड़ी_num;

	pr_debug("Component handle:0x%x in:%d out:%d clock:%d\n",
		 component->handle,
		 component->inमाला_दो, component->outमाला_दो, component->घड़ीs);

release_msg:
	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

/* destroys a component on vc */
अटल पूर्णांक destroy_component(काष्ठा vchiq_mmal_instance *instance,
			     काष्ठा vchiq_mmal_component *component)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_COMPONENT_DESTROY;
	m.u.component_destroy.component_handle = component->handle;

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(m.u.component_destroy),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != m.h.type) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	ret = -rmsg->u.component_destroy_reply.status;

release_msg:

	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

/* enable a component on vc */
अटल पूर्णांक enable_component(काष्ठा vchiq_mmal_instance *instance,
			    काष्ठा vchiq_mmal_component *component)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_COMPONENT_ENABLE;
	m.u.component_enable.component_handle = component->handle;

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(m.u.component_enable),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != m.h.type) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	ret = -rmsg->u.component_enable_reply.status;

release_msg:
	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

/* disable a component on vc */
अटल पूर्णांक disable_component(काष्ठा vchiq_mmal_instance *instance,
			     काष्ठा vchiq_mmal_component *component)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_COMPONENT_DISABLE;
	m.u.component_disable.component_handle = component->handle;

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(m.u.component_disable),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != m.h.type) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	ret = -rmsg->u.component_disable_reply.status;

release_msg:

	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

/* get version of mmal implementation */
अटल पूर्णांक get_version(काष्ठा vchiq_mmal_instance *instance,
		       u32 *major_out, u32 *minor_out)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_GET_VERSION;

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(m.u.version),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != m.h.type) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	*major_out = rmsg->u.version.major;
	*minor_out = rmsg->u.version.minor;

release_msg:
	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

/* करो a port action with a port as a parameter */
अटल पूर्णांक port_action_port(काष्ठा vchiq_mmal_instance *instance,
			    काष्ठा vchiq_mmal_port *port,
			    क्रमागत mmal_msg_port_action_type action_type)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_PORT_ACTION;
	m.u.port_action_port.component_handle = port->component->handle;
	m.u.port_action_port.port_handle = port->handle;
	m.u.port_action_port.action = action_type;

	port_to_mmal_msg(port, &m.u.port_action_port.port);

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(m.u.port_action_port),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != MMAL_MSG_TYPE_PORT_ACTION) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	ret = -rmsg->u.port_action_reply.status;

	pr_debug("%s:result:%d component:0x%x port:%d action:%s(%d)\n",
		 __func__,
		 ret, port->component->handle, port->handle,
		 port_action_type_names[action_type], action_type);

release_msg:
	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

/* करो a port action with handles as parameters */
अटल पूर्णांक port_action_handle(काष्ठा vchiq_mmal_instance *instance,
			      काष्ठा vchiq_mmal_port *port,
			      क्रमागत mmal_msg_port_action_type action_type,
			      u32 connect_component_handle,
			      u32 connect_port_handle)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_PORT_ACTION;

	m.u.port_action_handle.component_handle = port->component->handle;
	m.u.port_action_handle.port_handle = port->handle;
	m.u.port_action_handle.action = action_type;

	m.u.port_action_handle.connect_component_handle =
	    connect_component_handle;
	m.u.port_action_handle.connect_port_handle = connect_port_handle;

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(m.u.port_action_handle),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != MMAL_MSG_TYPE_PORT_ACTION) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	ret = -rmsg->u.port_action_reply.status;

	pr_debug("%s:result:%d component:0x%x port:%d action:%s(%d) connect component:0x%x connect port:%d\n",
		 __func__,
		 ret, port->component->handle, port->handle,
		 port_action_type_names[action_type],
		 action_type, connect_component_handle, connect_port_handle);

release_msg:
	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

अटल पूर्णांक port_parameter_set(काष्ठा vchiq_mmal_instance *instance,
			      काष्ठा vchiq_mmal_port *port,
			      u32 parameter_id, व्योम *value, u32 value_size)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_PORT_PARAMETER_SET;

	m.u.port_parameter_set.component_handle = port->component->handle;
	m.u.port_parameter_set.port_handle = port->handle;
	m.u.port_parameter_set.id = parameter_id;
	m.u.port_parameter_set.size = (2 * माप(u32)) + value_size;
	स_नकल(&m.u.port_parameter_set.value, value, value_size);

	ret = send_synchronous_mmal_msg(instance, &m,
					(4 * माप(u32)) + value_size,
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != MMAL_MSG_TYPE_PORT_PARAMETER_SET) अणु
		/* got an unexpected message type in reply */
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	ret = -rmsg->u.port_parameter_set_reply.status;

	pr_debug("%s:result:%d component:0x%x port:%d parameter:%d\n",
		 __func__,
		 ret, port->component->handle, port->handle, parameter_id);

release_msg:
	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

अटल पूर्णांक port_parameter_get(काष्ठा vchiq_mmal_instance *instance,
			      काष्ठा vchiq_mmal_port *port,
			      u32 parameter_id, व्योम *value, u32 *value_size)
अणु
	पूर्णांक ret;
	काष्ठा mmal_msg m;
	काष्ठा mmal_msg *rmsg;
	काष्ठा vchiq_header *rmsg_handle;

	m.h.type = MMAL_MSG_TYPE_PORT_PARAMETER_GET;

	m.u.port_parameter_get.component_handle = port->component->handle;
	m.u.port_parameter_get.port_handle = port->handle;
	m.u.port_parameter_get.id = parameter_id;
	m.u.port_parameter_get.size = (2 * माप(u32)) + *value_size;

	ret = send_synchronous_mmal_msg(instance, &m,
					माप(काष्ठा
					       mmal_msg_port_parameter_get),
					&rmsg, &rmsg_handle);
	अगर (ret)
		वापस ret;

	अगर (rmsg->h.type != MMAL_MSG_TYPE_PORT_PARAMETER_GET) अणु
		/* got an unexpected message type in reply */
		pr_err("Incorrect reply type %d\n", rmsg->h.type);
		ret = -EINVAL;
		जाओ release_msg;
	पूर्ण

	ret = rmsg->u.port_parameter_get_reply.status;

	/* port_parameter_get_reply.size includes the header,
	 * whilst *value_size करोesn't.
	 */
	rmsg->u.port_parameter_get_reply.size -= (2 * माप(u32));

	अगर (ret || rmsg->u.port_parameter_get_reply.size > *value_size) अणु
		/* Copy only as much as we have space क्रम
		 * but report true size of parameter
		 */
		स_नकल(value, &rmsg->u.port_parameter_get_reply.value,
		       *value_size);
	पूर्ण अन्यथा अणु
		स_नकल(value, &rmsg->u.port_parameter_get_reply.value,
		       rmsg->u.port_parameter_get_reply.size);
	पूर्ण
	/* Always report the size of the वापसed parameter to the caller */
	*value_size = rmsg->u.port_parameter_get_reply.size;

	pr_debug("%s:result:%d component:0x%x port:%d parameter:%d\n", __func__,
		 ret, port->component->handle, port->handle, parameter_id);

release_msg:
	vchiq_release_message(instance->service_handle, rmsg_handle);

	वापस ret;
पूर्ण

/* disables a port and drains buffers from it */
अटल पूर्णांक port_disable(काष्ठा vchiq_mmal_instance *instance,
			काष्ठा vchiq_mmal_port *port)
अणु
	पूर्णांक ret;
	काष्ठा list_head *q, *buf_head;
	अचिन्हित दीर्घ flags = 0;

	अगर (!port->enabled)
		वापस 0;

	port->enabled = 0;

	ret = port_action_port(instance, port,
			       MMAL_MSG_PORT_ACTION_TYPE_DISABLE);
	अगर (ret == 0) अणु
		/*
		 * Drain all queued buffers on port. This should only
		 * apply to buffers that have been queued beक्रमe the port
		 * has been enabled. If the port has been enabled and buffers
		 * passed, then the buffers should have been हटाओd from this
		 * list, and we should get the relevant callbacks via VCHIQ
		 * to release the buffers.
		 */
		spin_lock_irqsave(&port->slock, flags);

		list_क्रम_each_safe(buf_head, q, &port->buffers) अणु
			काष्ठा mmal_buffer *mmalbuf;

			mmalbuf = list_entry(buf_head, काष्ठा mmal_buffer,
					     list);
			list_del(buf_head);
			अगर (port->buffer_cb) अणु
				mmalbuf->length = 0;
				mmalbuf->mmal_flags = 0;
				mmalbuf->dts = MMAL_TIME_UNKNOWN;
				mmalbuf->pts = MMAL_TIME_UNKNOWN;
				port->buffer_cb(instance,
						port, 0, mmalbuf);
			पूर्ण
		पूर्ण

		spin_unlock_irqrestore(&port->slock, flags);

		ret = port_info_get(instance, port);
	पूर्ण

	वापस ret;
पूर्ण

/* enable a port */
अटल पूर्णांक port_enable(काष्ठा vchiq_mmal_instance *instance,
		       काष्ठा vchiq_mmal_port *port)
अणु
	अचिन्हित पूर्णांक hdr_count;
	काष्ठा list_head *q, *buf_head;
	पूर्णांक ret;

	अगर (port->enabled)
		वापस 0;

	ret = port_action_port(instance, port,
			       MMAL_MSG_PORT_ACTION_TYPE_ENABLE);
	अगर (ret)
		जाओ करोne;

	port->enabled = 1;

	अगर (port->buffer_cb) अणु
		/* send buffer headers to videocore */
		hdr_count = 1;
		list_क्रम_each_safe(buf_head, q, &port->buffers) अणु
			काष्ठा mmal_buffer *mmalbuf;

			mmalbuf = list_entry(buf_head, काष्ठा mmal_buffer,
					     list);
			ret = buffer_from_host(instance, port, mmalbuf);
			अगर (ret)
				जाओ करोne;

			list_del(buf_head);
			hdr_count++;
			अगर (hdr_count > port->current_buffer.num)
				अवरोध;
		पूर्ण
	पूर्ण

	ret = port_info_get(instance, port);

करोne:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------
 * Exported API
 *------------------------------------------------------------------
 */

पूर्णांक vchiq_mmal_port_set_क्रमmat(काष्ठा vchiq_mmal_instance *instance,
			       काष्ठा vchiq_mmal_port *port)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	ret = port_info_set(instance, port);
	अगर (ret)
		जाओ release_unlock;

	/* पढ़ो what has actually been set */
	ret = port_info_get(instance, port);

release_unlock:
	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_port_set_क्रमmat);

पूर्णांक vchiq_mmal_port_parameter_set(काष्ठा vchiq_mmal_instance *instance,
				  काष्ठा vchiq_mmal_port *port,
				  u32 parameter, व्योम *value, u32 value_size)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	ret = port_parameter_set(instance, port, parameter, value, value_size);

	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_port_parameter_set);

पूर्णांक vchiq_mmal_port_parameter_get(काष्ठा vchiq_mmal_instance *instance,
				  काष्ठा vchiq_mmal_port *port,
				  u32 parameter, व्योम *value, u32 *value_size)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	ret = port_parameter_get(instance, port, parameter, value, value_size);

	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_port_parameter_get);

/* enable a port
 *
 * enables a port and queues buffers क्रम satisfying callbacks अगर we
 * provide a callback handler
 */
पूर्णांक vchiq_mmal_port_enable(काष्ठा vchiq_mmal_instance *instance,
			   काष्ठा vchiq_mmal_port *port,
			   vchiq_mmal_buffer_cb buffer_cb)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	/* alपढ़ोy enabled - noop */
	अगर (port->enabled) अणु
		ret = 0;
		जाओ unlock;
	पूर्ण

	port->buffer_cb = buffer_cb;

	ret = port_enable(instance, port);

unlock:
	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_port_enable);

पूर्णांक vchiq_mmal_port_disable(काष्ठा vchiq_mmal_instance *instance,
			    काष्ठा vchiq_mmal_port *port)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	अगर (!port->enabled) अणु
		mutex_unlock(&instance->vchiq_mutex);
		वापस 0;
	पूर्ण

	ret = port_disable(instance, port);

	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_port_disable);

/* ports will be connected in a tunneled manner so data buffers
 * are not handled by client.
 */
पूर्णांक vchiq_mmal_port_connect_tunnel(काष्ठा vchiq_mmal_instance *instance,
				   काष्ठा vchiq_mmal_port *src,
				   काष्ठा vchiq_mmal_port *dst)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	/* disconnect ports अगर connected */
	अगर (src->connected) अणु
		ret = port_disable(instance, src);
		अगर (ret) अणु
			pr_err("failed disabling src port(%d)\n", ret);
			जाओ release_unlock;
		पूर्ण

		/* करो not need to disable the destination port as they
		 * are connected and it is करोne स्वतःmatically
		 */

		ret = port_action_handle(instance, src,
					 MMAL_MSG_PORT_ACTION_TYPE_DISCONNECT,
					 src->connected->component->handle,
					 src->connected->handle);
		अगर (ret < 0) अणु
			pr_err("failed disconnecting src port\n");
			जाओ release_unlock;
		पूर्ण
		src->connected->enabled = 0;
		src->connected = शून्य;
	पूर्ण

	अगर (!dst) अणु
		/* करो not make new connection */
		ret = 0;
		pr_debug("not making new connection\n");
		जाओ release_unlock;
	पूर्ण

	/* copy src port क्रमmat to dst */
	dst->क्रमmat.encoding = src->क्रमmat.encoding;
	dst->es.video.width = src->es.video.width;
	dst->es.video.height = src->es.video.height;
	dst->es.video.crop.x = src->es.video.crop.x;
	dst->es.video.crop.y = src->es.video.crop.y;
	dst->es.video.crop.width = src->es.video.crop.width;
	dst->es.video.crop.height = src->es.video.crop.height;
	dst->es.video.frame_rate.num = src->es.video.frame_rate.num;
	dst->es.video.frame_rate.den = src->es.video.frame_rate.den;

	/* set new क्रमmat */
	ret = port_info_set(instance, dst);
	अगर (ret) अणु
		pr_debug("setting port info failed\n");
		जाओ release_unlock;
	पूर्ण

	/* पढ़ो what has actually been set */
	ret = port_info_get(instance, dst);
	अगर (ret) अणु
		pr_debug("read back port info failed\n");
		जाओ release_unlock;
	पूर्ण

	/* connect two ports together */
	ret = port_action_handle(instance, src,
				 MMAL_MSG_PORT_ACTION_TYPE_CONNECT,
				 dst->component->handle, dst->handle);
	अगर (ret < 0) अणु
		pr_debug("connecting port %d:%d to %d:%d failed\n",
			 src->component->handle, src->handle,
			 dst->component->handle, dst->handle);
		जाओ release_unlock;
	पूर्ण
	src->connected = dst;

release_unlock:

	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_port_connect_tunnel);

पूर्णांक vchiq_mmal_submit_buffer(काष्ठा vchiq_mmal_instance *instance,
			     काष्ठा vchiq_mmal_port *port,
			     काष्ठा mmal_buffer *buffer)
अणु
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	ret = buffer_from_host(instance, port, buffer);
	अगर (ret == -EINVAL) अणु
		/* Port is disabled. Queue क्रम when it is enabled. */
		spin_lock_irqsave(&port->slock, flags);
		list_add_tail(&buffer->list, &port->buffers);
		spin_unlock_irqrestore(&port->slock, flags);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_submit_buffer);

पूर्णांक mmal_vchi_buffer_init(काष्ठा vchiq_mmal_instance *instance,
			  काष्ठा mmal_buffer *buf)
अणु
	काष्ठा mmal_msg_context *msg_context = get_msg_context(instance);

	अगर (IS_ERR(msg_context))
		वापस (PTR_ERR(msg_context));

	buf->msg_context = msg_context;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mmal_vchi_buffer_init);

पूर्णांक mmal_vchi_buffer_cleanup(काष्ठा mmal_buffer *buf)
अणु
	काष्ठा mmal_msg_context *msg_context = buf->msg_context;

	अगर (msg_context)
		release_msg_context(msg_context);
	buf->msg_context = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mmal_vchi_buffer_cleanup);

/* Initialise a mmal component and its ports
 *
 */
पूर्णांक vchiq_mmal_component_init(काष्ठा vchiq_mmal_instance *instance,
			      स्थिर अक्षर *name,
			      काष्ठा vchiq_mmal_component **component_out)
अणु
	पूर्णांक ret;
	पूर्णांक idx;		/* port index */
	काष्ठा vchiq_mmal_component *component = शून्य;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	क्रम (idx = 0; idx < VCHIQ_MMAL_MAX_COMPONENTS; idx++) अणु
		अगर (!instance->component[idx].in_use) अणु
			component = &instance->component[idx];
			component->in_use = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!component) अणु
		ret = -EINVAL;	/* toकरो is this correct error? */
		जाओ unlock;
	पूर्ण

	/* We need a handle to reference back to our component काष्ठाure.
	 * Use the array index in instance->component rather than rolling
	 * another IDR.
	 */
	component->client_component = idx;

	ret = create_component(instance, component, name);
	अगर (ret < 0) अणु
		pr_err("%s: failed to create component %d (Not enough GPU mem?)\n",
		       __func__, ret);
		जाओ unlock;
	पूर्ण

	/* ports info needs gathering */
	component->control.type = MMAL_PORT_TYPE_CONTROL;
	component->control.index = 0;
	component->control.component = component;
	spin_lock_init(&component->control.slock);
	INIT_LIST_HEAD(&component->control.buffers);
	ret = port_info_get(instance, &component->control);
	अगर (ret < 0)
		जाओ release_component;

	क्रम (idx = 0; idx < component->inमाला_दो; idx++) अणु
		component->input[idx].type = MMAL_PORT_TYPE_INPUT;
		component->input[idx].index = idx;
		component->input[idx].component = component;
		spin_lock_init(&component->input[idx].slock);
		INIT_LIST_HEAD(&component->input[idx].buffers);
		ret = port_info_get(instance, &component->input[idx]);
		अगर (ret < 0)
			जाओ release_component;
	पूर्ण

	क्रम (idx = 0; idx < component->outमाला_दो; idx++) अणु
		component->output[idx].type = MMAL_PORT_TYPE_OUTPUT;
		component->output[idx].index = idx;
		component->output[idx].component = component;
		spin_lock_init(&component->output[idx].slock);
		INIT_LIST_HEAD(&component->output[idx].buffers);
		ret = port_info_get(instance, &component->output[idx]);
		अगर (ret < 0)
			जाओ release_component;
	पूर्ण

	क्रम (idx = 0; idx < component->घड़ीs; idx++) अणु
		component->घड़ी[idx].type = MMAL_PORT_TYPE_CLOCK;
		component->घड़ी[idx].index = idx;
		component->घड़ी[idx].component = component;
		spin_lock_init(&component->घड़ी[idx].slock);
		INIT_LIST_HEAD(&component->घड़ी[idx].buffers);
		ret = port_info_get(instance, &component->घड़ी[idx]);
		अगर (ret < 0)
			जाओ release_component;
	पूर्ण

	*component_out = component;

	mutex_unlock(&instance->vchiq_mutex);

	वापस 0;

release_component:
	destroy_component(instance, component);
unlock:
	अगर (component)
		component->in_use = 0;
	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_component_init);

/*
 * cause a mmal component to be destroyed
 */
पूर्णांक vchiq_mmal_component_finalise(काष्ठा vchiq_mmal_instance *instance,
				  काष्ठा vchiq_mmal_component *component)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	अगर (component->enabled)
		ret = disable_component(instance, component);

	ret = destroy_component(instance, component);

	component->in_use = 0;

	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_component_finalise);

/*
 * cause a mmal component to be enabled
 */
पूर्णांक vchiq_mmal_component_enable(काष्ठा vchiq_mmal_instance *instance,
				काष्ठा vchiq_mmal_component *component)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	अगर (component->enabled) अणु
		mutex_unlock(&instance->vchiq_mutex);
		वापस 0;
	पूर्ण

	ret = enable_component(instance, component);
	अगर (ret == 0)
		component->enabled = true;

	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_component_enable);

/*
 * cause a mmal component to be enabled
 */
पूर्णांक vchiq_mmal_component_disable(काष्ठा vchiq_mmal_instance *instance,
				 काष्ठा vchiq_mmal_component *component)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	अगर (!component->enabled) अणु
		mutex_unlock(&instance->vchiq_mutex);
		वापस 0;
	पूर्ण

	ret = disable_component(instance, component);
	अगर (ret == 0)
		component->enabled = 0;

	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_component_disable);

पूर्णांक vchiq_mmal_version(काष्ठा vchiq_mmal_instance *instance,
		       u32 *major_out, u32 *minor_out)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	ret = get_version(instance, major_out, minor_out);

	mutex_unlock(&instance->vchiq_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_version);

पूर्णांक vchiq_mmal_finalise(काष्ठा vchiq_mmal_instance *instance)
अणु
	पूर्णांक status = 0;

	अगर (!instance)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->vchiq_mutex))
		वापस -EINTR;

	vchiq_use_service(instance->service_handle);

	status = vchiq_बंद_service(instance->service_handle);
	अगर (status != 0)
		pr_err("mmal-vchiq: VCHIQ close failed\n");

	mutex_unlock(&instance->vchiq_mutex);

	vchiq_shutकरोwn(instance->vchiq_instance);
	flush_workqueue(instance->bulk_wq);
	destroy_workqueue(instance->bulk_wq);

	vमुक्त(instance->bulk_scratch);

	idr_destroy(&instance->context_map);

	kमुक्त(instance);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_finalise);

पूर्णांक vchiq_mmal_init(काष्ठा vchiq_mmal_instance **out_instance)
अणु
	पूर्णांक status;
	पूर्णांक err = -ENODEV;
	काष्ठा vchiq_mmal_instance *instance;
	अटल काष्ठा vchiq_instance *vchiq_instance;
	काष्ठा vchiq_service_params_kernel params = अणु
		.version		= VC_MMAL_VER,
		.version_min		= VC_MMAL_MIN_VER,
		.fourcc			= VCHIQ_MAKE_FOURCC('m', 'm', 'a', 'l'),
		.callback		= service_callback,
		.userdata		= शून्य,
	पूर्ण;

	/* compile समय checks to ensure काष्ठाure size as they are
	 * directly (de)serialised from memory.
	 */

	/* ensure the header काष्ठाure has packed to the correct size */
	BUILD_BUG_ON(माप(काष्ठा mmal_msg_header) != 24);

	/* ensure message काष्ठाure करोes not exceed maximum length */
	BUILD_BUG_ON(माप(काष्ठा mmal_msg) > MMAL_MSG_MAX_SIZE);

	/* mmal port काष्ठा is correct size */
	BUILD_BUG_ON(माप(काष्ठा mmal_port) != 64);

	/* create a vchi instance */
	status = vchiq_initialise(&vchiq_instance);
	अगर (status) अणु
		pr_err("Failed to initialise VCHI instance (status=%d)\n",
		       status);
		वापस -EIO;
	पूर्ण

	status = vchiq_connect(vchiq_instance);
	अगर (status) अणु
		pr_err("Failed to connect VCHI instance (status=%d)\n", status);
		err = -EIO;
		जाओ err_shutकरोwn_vchiq;
	पूर्ण

	instance = kzalloc(माप(*instance), GFP_KERNEL);

	अगर (!instance) अणु
		err = -ENOMEM;
		जाओ err_shutकरोwn_vchiq;
	पूर्ण

	mutex_init(&instance->vchiq_mutex);

	instance->bulk_scratch = vदो_स्मृति(PAGE_SIZE);
	instance->vchiq_instance = vchiq_instance;

	mutex_init(&instance->context_map_lock);
	idr_init_base(&instance->context_map, 1);

	params.userdata = instance;

	instance->bulk_wq = alloc_ordered_workqueue("mmal-vchiq",
						    WQ_MEM_RECLAIM);
	अगर (!instance->bulk_wq)
		जाओ err_मुक्त;

	status = vchiq_खोलो_service(vchiq_instance, &params,
				    &instance->service_handle);
	अगर (status) अणु
		pr_err("Failed to open VCHI service connection (status=%d)\n",
		       status);
		जाओ err_बंद_services;
	पूर्ण

	vchiq_release_service(instance->service_handle);

	*out_instance = instance;

	वापस 0;

err_बंद_services:
	vchiq_बंद_service(instance->service_handle);
	destroy_workqueue(instance->bulk_wq);
err_मुक्त:
	vमुक्त(instance->bulk_scratch);
	kमुक्त(instance);
err_shutकरोwn_vchiq:
	vchiq_shutकरोwn(vchiq_instance);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vchiq_mmal_init);

MODULE_DESCRIPTION("BCM2835 MMAL VCHIQ interface");
MODULE_AUTHOR("Dave Stevenson, <dave.stevenson@raspberrypi.org>");
MODULE_LICENSE("GPL");
