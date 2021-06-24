<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus operations
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/greybus.h>

#समावेश "greybus_trace.h"

अटल काष्ठा kmem_cache *gb_operation_cache;
अटल काष्ठा kmem_cache *gb_message_cache;

/* Workqueue to handle Greybus operation completions. */
अटल काष्ठा workqueue_काष्ठा *gb_operation_completion_wq;

/* Wait queue क्रम synchronous cancellations. */
अटल DECLARE_WAIT_QUEUE_HEAD(gb_operation_cancellation_queue);

/*
 * Protects updates to operation->त्रुटि_सं.
 */
अटल DEFINE_SPINLOCK(gb_operations_lock);

अटल पूर्णांक gb_operation_response_send(काष्ठा gb_operation *operation,
				      पूर्णांक त्रुटि_सं);

/*
 * Increment operation active count and add to connection list unless the
 * connection is going away.
 *
 * Caller holds operation reference.
 */
अटल पूर्णांक gb_operation_get_active(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_connection *connection = operation->connection;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&connection->lock, flags);
	चयन (connection->state) अणु
	हाल GB_CONNECTION_STATE_ENABLED:
		अवरोध;
	हाल GB_CONNECTION_STATE_ENABLED_TX:
		अगर (gb_operation_is_incoming(operation))
			जाओ err_unlock;
		अवरोध;
	हाल GB_CONNECTION_STATE_DISCONNECTING:
		अगर (!gb_operation_is_core(operation))
			जाओ err_unlock;
		अवरोध;
	शेष:
		जाओ err_unlock;
	पूर्ण

	अगर (operation->active++ == 0)
		list_add_tail(&operation->links, &connection->operations);

	trace_gb_operation_get_active(operation);

	spin_unlock_irqrestore(&connection->lock, flags);

	वापस 0;

err_unlock:
	spin_unlock_irqrestore(&connection->lock, flags);

	वापस -ENOTCONN;
पूर्ण

/* Caller holds operation reference. */
अटल व्योम gb_operation_put_active(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_connection *connection = operation->connection;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&connection->lock, flags);

	trace_gb_operation_put_active(operation);

	अगर (--operation->active == 0) अणु
		list_del(&operation->links);
		अगर (atomic_पढ़ो(&operation->रुकोers))
			wake_up(&gb_operation_cancellation_queue);
	पूर्ण
	spin_unlock_irqrestore(&connection->lock, flags);
पूर्ण

अटल bool gb_operation_is_active(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_connection *connection = operation->connection;
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&connection->lock, flags);
	ret = operation->active;
	spin_unlock_irqrestore(&connection->lock, flags);

	वापस ret;
पूर्ण

/*
 * Set an operation's result.
 *
 * Initially an outgoing operation's त्रुटि_सं value is -EBADR.
 * If no error occurs beक्रमe sending the request message the only
 * valid value operation->त्रुटि_सं can be set to is -EINPROGRESS,
 * indicating the request has been (or rather is about to be) sent.
 * At that poपूर्णांक nobody should be looking at the result until the
 * response arrives.
 *
 * The first समय the result माला_लो set after the request has been
 * sent, that result "sticks."  That is, अगर two concurrent thपढ़ोs
 * race to set the result, the first one wins.  The वापस value
 * tells the caller whether its result was recorded; अगर not the
 * caller has nothing more to करो.
 *
 * The result value -EILSEQ is reserved to संकेत an implementation
 * error; अगर it's ever observed, the code perक्रमming the request has
 * करोne something fundamentally wrong.  It is an error to try to set
 * the result to -EBADR, and attempts to करो so result in a warning,
 * and -EILSEQ is used instead.  Similarly, the only valid result
 * value to set क्रम an operation in initial state is -EINPROGRESS.
 * Attempts to करो otherwise will also record a (successful) -EILSEQ
 * operation result.
 */
अटल bool gb_operation_result_set(काष्ठा gb_operation *operation, पूर्णांक result)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक prev;

	अगर (result == -EINPROGRESS) अणु
		/*
		 * -EINPROGRESS is used to indicate the request is
		 * in flight.  It should be the first result value
		 * set after the initial -EBADR.  Issue a warning
		 * and record an implementation error अगर it's
		 * set at any other समय.
		 */
		spin_lock_irqsave(&gb_operations_lock, flags);
		prev = operation->त्रुटि_सं;
		अगर (prev == -EBADR)
			operation->त्रुटि_सं = result;
		अन्यथा
			operation->त्रुटि_सं = -EILSEQ;
		spin_unlock_irqrestore(&gb_operations_lock, flags);
		WARN_ON(prev != -EBADR);

		वापस true;
	पूर्ण

	/*
	 * The first result value set after a request has been sent
	 * will be the final result of the operation.  Subsequent
	 * attempts to set the result are ignored.
	 *
	 * Note that -EBADR is a reserved "initial state" result
	 * value.  Attempts to set this value result in a warning,
	 * and the result code is set to -EILSEQ instead.
	 */
	अगर (WARN_ON(result == -EBADR))
		result = -EILSEQ; /* Nobody should be setting -EBADR */

	spin_lock_irqsave(&gb_operations_lock, flags);
	prev = operation->त्रुटि_सं;
	अगर (prev == -EINPROGRESS)
		operation->त्रुटि_सं = result;	/* First and final result */
	spin_unlock_irqrestore(&gb_operations_lock, flags);

	वापस prev == -EINPROGRESS;
पूर्ण

पूर्णांक gb_operation_result(काष्ठा gb_operation *operation)
अणु
	पूर्णांक result = operation->त्रुटि_सं;

	WARN_ON(result == -EBADR);
	WARN_ON(result == -EINPROGRESS);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_result);

/*
 * Looks up an outgoing operation on a connection and वापसs a refcounted
 * poपूर्णांकer अगर found, or शून्य otherwise.
 */
अटल काष्ठा gb_operation *
gb_operation_find_outgoing(काष्ठा gb_connection *connection, u16 operation_id)
अणु
	काष्ठा gb_operation *operation;
	अचिन्हित दीर्घ flags;
	bool found = false;

	spin_lock_irqsave(&connection->lock, flags);
	list_क्रम_each_entry(operation, &connection->operations, links)
		अगर (operation->id == operation_id &&
		    !gb_operation_is_incoming(operation)) अणु
			gb_operation_get(operation);
			found = true;
			अवरोध;
		पूर्ण
	spin_unlock_irqrestore(&connection->lock, flags);

	वापस found ? operation : शून्य;
पूर्ण

अटल पूर्णांक gb_message_send(काष्ठा gb_message *message, gfp_t gfp)
अणु
	काष्ठा gb_connection *connection = message->operation->connection;

	trace_gb_message_send(message);
	वापस connection->hd->driver->message_send(connection->hd,
					connection->hd_cport_id,
					message,
					gfp);
पूर्ण

/*
 * Cancel a message we have passed to the host device layer to be sent.
 */
अटल व्योम gb_message_cancel(काष्ठा gb_message *message)
अणु
	काष्ठा gb_host_device *hd = message->operation->connection->hd;

	hd->driver->message_cancel(message);
पूर्ण

अटल व्योम gb_operation_request_handle(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_connection *connection = operation->connection;
	पूर्णांक status;
	पूर्णांक ret;

	अगर (connection->handler) अणु
		status = connection->handler(operation);
	पूर्ण अन्यथा अणु
		dev_err(&connection->hd->dev,
			"%s: unexpected incoming request of type 0x%02x\n",
			connection->name, operation->type);

		status = -EPROTONOSUPPORT;
	पूर्ण

	ret = gb_operation_response_send(operation, status);
	अगर (ret) अणु
		dev_err(&connection->hd->dev,
			"%s: failed to send response %d for type 0x%02x: %d\n",
			connection->name, status, operation->type, ret);
		वापस;
	पूर्ण
पूर्ण

/*
 * Process operation work.
 *
 * For incoming requests, call the protocol request handler. The operation
 * result should be -EINPROGRESS at this poपूर्णांक.
 *
 * For outgoing requests, the operation result value should have
 * been set beक्रमe queueing this.  The operation callback function
 * allows the original requester to know the request has completed
 * and its result is available.
 */
अटल व्योम gb_operation_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gb_operation *operation;
	पूर्णांक ret;

	operation = container_of(work, काष्ठा gb_operation, work);

	अगर (gb_operation_is_incoming(operation)) अणु
		gb_operation_request_handle(operation);
	पूर्ण अन्यथा अणु
		ret = del_समयr_sync(&operation->समयr);
		अगर (!ret) अणु
			/* Cancel request message अगर scheduled by समयout. */
			अगर (gb_operation_result(operation) == -ETIMEDOUT)
				gb_message_cancel(operation->request);
		पूर्ण

		operation->callback(operation);
	पूर्ण

	gb_operation_put_active(operation);
	gb_operation_put(operation);
पूर्ण

अटल व्योम gb_operation_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा gb_operation *operation = from_समयr(operation, t, समयr);

	अगर (gb_operation_result_set(operation, -ETIMEDOUT)) अणु
		/*
		 * A stuck request message will be cancelled from the
		 * workqueue.
		 */
		queue_work(gb_operation_completion_wq, &operation->work);
	पूर्ण
पूर्ण

अटल व्योम gb_operation_message_init(काष्ठा gb_host_device *hd,
				      काष्ठा gb_message *message,
				      u16 operation_id,
				      माप_प्रकार payload_size, u8 type)
अणु
	काष्ठा gb_operation_msg_hdr *header;

	header = message->buffer;

	message->header = header;
	message->payload = payload_size ? header + 1 : शून्य;
	message->payload_size = payload_size;

	/*
	 * The type supplied क्रम incoming message buffers will be
	 * GB_REQUEST_TYPE_INVALID. Such buffers will be overwritten by
	 * arriving data so there's no need to initialize the message header.
	 */
	अगर (type != GB_REQUEST_TYPE_INVALID) अणु
		u16 message_size = (u16)(माप(*header) + payload_size);

		/*
		 * For a request, the operation id माला_लो filled in
		 * when the message is sent.  For a response, it
		 * will be copied from the request by the caller.
		 *
		 * The result field in a request message must be
		 * zero.  It will be set just prior to sending क्रम
		 * a response.
		 */
		header->size = cpu_to_le16(message_size);
		header->operation_id = 0;
		header->type = type;
		header->result = 0;
	पूर्ण
पूर्ण

/*
 * Allocate a message to be used क्रम an operation request or response.
 * Both types of message contain a common header.  The request message
 * क्रम an outgoing operation is outbound, as is the response message
 * क्रम an incoming operation.  The message header क्रम an outbound
 * message is partially initialized here.
 *
 * The headers क्रम inbound messages करोn't need to be initialized;
 * they'll be filled in by arriving data.
 *
 * Our message buffers have the following layout:
 *	message header  \_ these combined are
 *	message payload /  the message size
 */
अटल काष्ठा gb_message *
gb_operation_message_alloc(काष्ठा gb_host_device *hd, u8 type,
			   माप_प्रकार payload_size, gfp_t gfp_flags)
अणु
	काष्ठा gb_message *message;
	काष्ठा gb_operation_msg_hdr *header;
	माप_प्रकार message_size = payload_size + माप(*header);

	अगर (message_size > hd->buffer_size_max) अणु
		dev_warn(&hd->dev, "requested message size too big (%zu > %zu)\n",
			 message_size, hd->buffer_size_max);
		वापस शून्य;
	पूर्ण

	/* Allocate the message काष्ठाure and buffer. */
	message = kmem_cache_zalloc(gb_message_cache, gfp_flags);
	अगर (!message)
		वापस शून्य;

	message->buffer = kzalloc(message_size, gfp_flags);
	अगर (!message->buffer)
		जाओ err_मुक्त_message;

	/* Initialize the message.  Operation id is filled in later. */
	gb_operation_message_init(hd, message, 0, payload_size, type);

	वापस message;

err_मुक्त_message:
	kmem_cache_मुक्त(gb_message_cache, message);

	वापस शून्य;
पूर्ण

अटल व्योम gb_operation_message_मुक्त(काष्ठा gb_message *message)
अणु
	kमुक्त(message->buffer);
	kmem_cache_मुक्त(gb_message_cache, message);
पूर्ण

/*
 * Map an क्रमागत gb_operation_status value (which is represented in a
 * message as a single byte) to an appropriate Linux negative त्रुटि_सं.
 */
अटल पूर्णांक gb_operation_status_map(u8 status)
अणु
	चयन (status) अणु
	हाल GB_OP_SUCCESS:
		वापस 0;
	हाल GB_OP_INTERRUPTED:
		वापस -EINTR;
	हाल GB_OP_TIMEOUT:
		वापस -ETIMEDOUT;
	हाल GB_OP_NO_MEMORY:
		वापस -ENOMEM;
	हाल GB_OP_PROTOCOL_BAD:
		वापस -EPROTONOSUPPORT;
	हाल GB_OP_OVERFLOW:
		वापस -EMSGSIZE;
	हाल GB_OP_INVALID:
		वापस -EINVAL;
	हाल GB_OP_RETRY:
		वापस -EAGAIN;
	हाल GB_OP_NONEXISTENT:
		वापस -ENODEV;
	हाल GB_OP_MALFUNCTION:
		वापस -EILSEQ;
	हाल GB_OP_UNKNOWN_ERROR:
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

/*
 * Map a Linux त्रुटि_सं value (from operation->त्रुटि_सं) पूर्णांकo the value
 * that should represent it in a response message status sent
 * over the wire.  Returns an क्रमागत gb_operation_status value (which
 * is represented in a message as a single byte).
 */
अटल u8 gb_operation_त्रुटि_सं_map(पूर्णांक त्रुटि_सं)
अणु
	चयन (त्रुटि_सं) अणु
	हाल 0:
		वापस GB_OP_SUCCESS;
	हाल -EINTR:
		वापस GB_OP_INTERRUPTED;
	हाल -ETIMEDOUT:
		वापस GB_OP_TIMEOUT;
	हाल -ENOMEM:
		वापस GB_OP_NO_MEMORY;
	हाल -EPROTONOSUPPORT:
		वापस GB_OP_PROTOCOL_BAD;
	हाल -EMSGSIZE:
		वापस GB_OP_OVERFLOW;	/* Could be underflow too */
	हाल -EINVAL:
		वापस GB_OP_INVALID;
	हाल -EAGAIN:
		वापस GB_OP_RETRY;
	हाल -EILSEQ:
		वापस GB_OP_MALFUNCTION;
	हाल -ENODEV:
		वापस GB_OP_NONEXISTENT;
	हाल -EIO:
	शेष:
		वापस GB_OP_UNKNOWN_ERROR;
	पूर्ण
पूर्ण

bool gb_operation_response_alloc(काष्ठा gb_operation *operation,
				 माप_प्रकार response_size, gfp_t gfp)
अणु
	काष्ठा gb_host_device *hd = operation->connection->hd;
	काष्ठा gb_operation_msg_hdr *request_header;
	काष्ठा gb_message *response;
	u8 type;

	type = operation->type | GB_MESSAGE_TYPE_RESPONSE;
	response = gb_operation_message_alloc(hd, type, response_size, gfp);
	अगर (!response)
		वापस false;
	response->operation = operation;

	/*
	 * Size and type get initialized when the message is
	 * allocated.  The त्रुटि_सं will be set beक्रमe sending.  All
	 * that's left is the operation id, which we copy from the
	 * request message header (as-is, in little-endian order).
	 */
	request_header = operation->request->header;
	response->header->operation_id = request_header->operation_id;
	operation->response = response;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_response_alloc);

/*
 * Create a Greybus operation to be sent over the given connection.
 * The request buffer will be big enough क्रम a payload of the given
 * size.
 *
 * For outgoing requests, the request message's header will be
 * initialized with the type of the request and the message size.
 * Outgoing operations must also specअगरy the response buffer size,
 * which must be sufficient to hold all expected response data.  The
 * response message header will eventually be overwritten, so there's
 * no need to initialize it here.
 *
 * Request messages क्रम incoming operations can arrive in पूर्णांकerrupt
 * context, so they must be allocated with GFP_ATOMIC.  In this हाल
 * the request buffer will be immediately overwritten, so there is
 * no need to initialize the message header.  Responsibility क्रम
 * allocating a response buffer lies with the incoming request
 * handler क्रम a protocol.  So we करोn't allocate that here.
 *
 * Returns a poपूर्णांकer to the new operation or a null poपूर्णांकer अगर an
 * error occurs.
 */
अटल काष्ठा gb_operation *
gb_operation_create_common(काष्ठा gb_connection *connection, u8 type,
			   माप_प्रकार request_size, माप_प्रकार response_size,
			   अचिन्हित दीर्घ op_flags, gfp_t gfp_flags)
अणु
	काष्ठा gb_host_device *hd = connection->hd;
	काष्ठा gb_operation *operation;

	operation = kmem_cache_zalloc(gb_operation_cache, gfp_flags);
	अगर (!operation)
		वापस शून्य;
	operation->connection = connection;

	operation->request = gb_operation_message_alloc(hd, type, request_size,
							gfp_flags);
	अगर (!operation->request)
		जाओ err_cache;
	operation->request->operation = operation;

	/* Allocate the response buffer क्रम outgoing operations */
	अगर (!(op_flags & GB_OPERATION_FLAG_INCOMING)) अणु
		अगर (!gb_operation_response_alloc(operation, response_size,
						 gfp_flags)) अणु
			जाओ err_request;
		पूर्ण

		समयr_setup(&operation->समयr, gb_operation_समयout, 0);
	पूर्ण

	operation->flags = op_flags;
	operation->type = type;
	operation->त्रुटि_सं = -EBADR;  /* Initial value--means "never set" */

	INIT_WORK(&operation->work, gb_operation_work);
	init_completion(&operation->completion);
	kref_init(&operation->kref);
	atomic_set(&operation->रुकोers, 0);

	वापस operation;

err_request:
	gb_operation_message_मुक्त(operation->request);
err_cache:
	kmem_cache_मुक्त(gb_operation_cache, operation);

	वापस शून्य;
पूर्ण

/*
 * Create a new operation associated with the given connection.  The
 * request and response sizes provided are the number of bytes
 * required to hold the request/response payload only.  Both of
 * these are allowed to be 0.  Note that 0x00 is reserved as an
 * invalid operation type क्रम all protocols, and this is enक्रमced
 * here.
 */
काष्ठा gb_operation *
gb_operation_create_flags(काष्ठा gb_connection *connection,
			  u8 type, माप_प्रकार request_size,
			  माप_प्रकार response_size, अचिन्हित दीर्घ flags,
			  gfp_t gfp)
अणु
	काष्ठा gb_operation *operation;

	अगर (WARN_ON_ONCE(type == GB_REQUEST_TYPE_INVALID))
		वापस शून्य;
	अगर (WARN_ON_ONCE(type & GB_MESSAGE_TYPE_RESPONSE))
		type &= ~GB_MESSAGE_TYPE_RESPONSE;

	अगर (WARN_ON_ONCE(flags & ~GB_OPERATION_FLAG_USER_MASK))
		flags &= GB_OPERATION_FLAG_USER_MASK;

	operation = gb_operation_create_common(connection, type,
					       request_size, response_size,
					       flags, gfp);
	अगर (operation)
		trace_gb_operation_create(operation);

	वापस operation;
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_create_flags);

काष्ठा gb_operation *
gb_operation_create_core(काष्ठा gb_connection *connection,
			 u8 type, माप_प्रकार request_size,
			 माप_प्रकार response_size, अचिन्हित दीर्घ flags,
			 gfp_t gfp)
अणु
	काष्ठा gb_operation *operation;

	flags |= GB_OPERATION_FLAG_CORE;

	operation = gb_operation_create_common(connection, type,
					       request_size, response_size,
					       flags, gfp);
	अगर (operation)
		trace_gb_operation_create_core(operation);

	वापस operation;
पूर्ण

/* Do not export this function. */

माप_प्रकार gb_operation_get_payload_size_max(काष्ठा gb_connection *connection)
अणु
	काष्ठा gb_host_device *hd = connection->hd;

	वापस hd->buffer_size_max - माप(काष्ठा gb_operation_msg_hdr);
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_get_payload_size_max);

अटल काष्ठा gb_operation *
gb_operation_create_incoming(काष्ठा gb_connection *connection, u16 id,
			     u8 type, व्योम *data, माप_प्रकार size)
अणु
	काष्ठा gb_operation *operation;
	माप_प्रकार request_size;
	अचिन्हित दीर्घ flags = GB_OPERATION_FLAG_INCOMING;

	/* Caller has made sure we at least have a message header. */
	request_size = size - माप(काष्ठा gb_operation_msg_hdr);

	अगर (!id)
		flags |= GB_OPERATION_FLAG_UNIसूचीECTIONAL;

	operation = gb_operation_create_common(connection, type,
					       request_size,
					       GB_REQUEST_TYPE_INVALID,
					       flags, GFP_ATOMIC);
	अगर (!operation)
		वापस शून्य;

	operation->id = id;
	स_नकल(operation->request->header, data, size);
	trace_gb_operation_create_incoming(operation);

	वापस operation;
पूर्ण

/*
 * Get an additional reference on an operation.
 */
व्योम gb_operation_get(काष्ठा gb_operation *operation)
अणु
	kref_get(&operation->kref);
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_get);

/*
 * Destroy a previously created operation.
 */
अटल व्योम _gb_operation_destroy(काष्ठा kref *kref)
अणु
	काष्ठा gb_operation *operation;

	operation = container_of(kref, काष्ठा gb_operation, kref);

	trace_gb_operation_destroy(operation);

	अगर (operation->response)
		gb_operation_message_मुक्त(operation->response);
	gb_operation_message_मुक्त(operation->request);

	kmem_cache_मुक्त(gb_operation_cache, operation);
पूर्ण

/*
 * Drop a reference on an operation, and destroy it when the last
 * one is gone.
 */
व्योम gb_operation_put(काष्ठा gb_operation *operation)
अणु
	अगर (WARN_ON(!operation))
		वापस;

	kref_put(&operation->kref, _gb_operation_destroy);
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_put);

/* Tell the requester we're करोne */
अटल व्योम gb_operation_sync_callback(काष्ठा gb_operation *operation)
अणु
	complete(&operation->completion);
पूर्ण

/**
 * gb_operation_request_send() - send an operation request message
 * @operation:	the operation to initiate
 * @callback:	the operation completion callback
 * @समयout:	operation समयout in milliseconds, or zero क्रम no समयout
 * @gfp:	the memory flags to use क्रम any allocations
 *
 * The caller has filled in any payload so the request message is पढ़ोy to go.
 * The callback function supplied will be called when the response message has
 * arrived, a unidirectional request has been sent, or the operation is
 * cancelled, indicating that the operation is complete. The callback function
 * can fetch the result of the operation using gb_operation_result() अगर
 * desired.
 *
 * Return: 0 अगर the request was successfully queued in the host-driver queues,
 * or a negative त्रुटि_सं.
 */
पूर्णांक gb_operation_request_send(काष्ठा gb_operation *operation,
			      gb_operation_callback callback,
			      अचिन्हित पूर्णांक समयout,
			      gfp_t gfp)
अणु
	काष्ठा gb_connection *connection = operation->connection;
	काष्ठा gb_operation_msg_hdr *header;
	अचिन्हित पूर्णांक cycle;
	पूर्णांक ret;

	अगर (gb_connection_is_offloaded(connection))
		वापस -EBUSY;

	अगर (!callback)
		वापस -EINVAL;

	/*
	 * Record the callback function, which is executed in
	 * non-atomic (workqueue) context when the final result
	 * of an operation has been set.
	 */
	operation->callback = callback;

	/*
	 * Assign the operation's id, and store it in the request header.
	 * Zero is a reserved operation id क्रम unidirectional operations.
	 */
	अगर (gb_operation_is_unidirectional(operation)) अणु
		operation->id = 0;
	पूर्ण अन्यथा अणु
		cycle = (अचिन्हित पूर्णांक)atomic_inc_वापस(&connection->op_cycle);
		operation->id = (u16)(cycle % U16_MAX + 1);
	पूर्ण

	header = operation->request->header;
	header->operation_id = cpu_to_le16(operation->id);

	gb_operation_result_set(operation, -EINPROGRESS);

	/*
	 * Get an extra reference on the operation. It'll be dropped when the
	 * operation completes.
	 */
	gb_operation_get(operation);
	ret = gb_operation_get_active(operation);
	अगर (ret)
		जाओ err_put;

	ret = gb_message_send(operation->request, gfp);
	अगर (ret)
		जाओ err_put_active;

	अगर (समयout) अणु
		operation->समयr.expires = jअगरfies + msecs_to_jअगरfies(समयout);
		add_समयr(&operation->समयr);
	पूर्ण

	वापस 0;

err_put_active:
	gb_operation_put_active(operation);
err_put:
	gb_operation_put(operation);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_request_send);

/*
 * Send a synchronous operation.  This function is expected to
 * block, वापसing only when the response has arrived, (or when an
 * error is detected.  The वापस value is the result of the
 * operation.
 */
पूर्णांक gb_operation_request_send_sync_समयout(काष्ठा gb_operation *operation,
					   अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक ret;

	ret = gb_operation_request_send(operation, gb_operation_sync_callback,
					समयout, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_completion_पूर्णांकerruptible(&operation->completion);
	अगर (ret < 0) अणु
		/* Cancel the operation अगर पूर्णांकerrupted */
		gb_operation_cancel(operation, -ECANCELED);
	पूर्ण

	वापस gb_operation_result(operation);
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_request_send_sync_समयout);

/*
 * Send a response क्रम an incoming operation request.  A non-zero
 * त्रुटि_सं indicates a failed operation.
 *
 * If there is any response payload, the incoming request handler is
 * responsible क्रम allocating the response message.  Otherwise the
 * it can simply supply the result त्रुटि_सं; this function will
 * allocate the response message अगर necessary.
 */
अटल पूर्णांक gb_operation_response_send(काष्ठा gb_operation *operation,
				      पूर्णांक त्रुटि_सं)
अणु
	काष्ठा gb_connection *connection = operation->connection;
	पूर्णांक ret;

	अगर (!operation->response &&
	    !gb_operation_is_unidirectional(operation)) अणु
		अगर (!gb_operation_response_alloc(operation, 0, GFP_KERNEL))
			वापस -ENOMEM;
	पूर्ण

	/* Record the result */
	अगर (!gb_operation_result_set(operation, त्रुटि_सं)) अणु
		dev_err(&connection->hd->dev, "request result already set\n");
		वापस -EIO;	/* Shouldn't happen */
	पूर्ण

	/* Sender of request करोes not care about response. */
	अगर (gb_operation_is_unidirectional(operation))
		वापस 0;

	/* Reference will be dropped when message has been sent. */
	gb_operation_get(operation);
	ret = gb_operation_get_active(operation);
	अगर (ret)
		जाओ err_put;

	/* Fill in the response header and send it */
	operation->response->header->result = gb_operation_त्रुटि_सं_map(त्रुटि_सं);

	ret = gb_message_send(operation->response, GFP_KERNEL);
	अगर (ret)
		जाओ err_put_active;

	वापस 0;

err_put_active:
	gb_operation_put_active(operation);
err_put:
	gb_operation_put(operation);

	वापस ret;
पूर्ण

/*
 * This function is called when a message send request has completed.
 */
व्योम greybus_message_sent(काष्ठा gb_host_device *hd,
			  काष्ठा gb_message *message, पूर्णांक status)
अणु
	काष्ठा gb_operation *operation = message->operation;
	काष्ठा gb_connection *connection = operation->connection;

	/*
	 * If the message was a response, we just need to drop our
	 * reference to the operation.  If an error occurred, report
	 * it.
	 *
	 * For requests, अगर there's no error and the operation in not
	 * unidirectional, there's nothing more to करो until the response
	 * arrives. If an error occurred attempting to send it, or अगर the
	 * operation is unidrectional, record the result of the operation and
	 * schedule its completion.
	 */
	अगर (message == operation->response) अणु
		अगर (status) अणु
			dev_err(&connection->hd->dev,
				"%s: error sending response 0x%02x: %d\n",
				connection->name, operation->type, status);
		पूर्ण

		gb_operation_put_active(operation);
		gb_operation_put(operation);
	पूर्ण अन्यथा अगर (status || gb_operation_is_unidirectional(operation)) अणु
		अगर (gb_operation_result_set(operation, status)) अणु
			queue_work(gb_operation_completion_wq,
				   &operation->work);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(greybus_message_sent);

/*
 * We've received data on a connection, and it doesn't look like a
 * response, so we assume it's a request.
 *
 * This is called in पूर्णांकerrupt context, so just copy the incoming
 * data पूर्णांकo the request buffer and handle the rest via workqueue.
 */
अटल व्योम gb_connection_recv_request(काष्ठा gb_connection *connection,
				स्थिर काष्ठा gb_operation_msg_hdr *header,
				व्योम *data, माप_प्रकार size)
अणु
	काष्ठा gb_operation *operation;
	u16 operation_id;
	u8 type;
	पूर्णांक ret;

	operation_id = le16_to_cpu(header->operation_id);
	type = header->type;

	operation = gb_operation_create_incoming(connection, operation_id,
						 type, data, size);
	अगर (!operation) अणु
		dev_err(&connection->hd->dev,
			"%s: can't create incoming operation\n",
			connection->name);
		वापस;
	पूर्ण

	ret = gb_operation_get_active(operation);
	अगर (ret) अणु
		gb_operation_put(operation);
		वापस;
	पूर्ण
	trace_gb_message_recv_request(operation->request);

	/*
	 * The initial reference to the operation will be dropped when the
	 * request handler वापसs.
	 */
	अगर (gb_operation_result_set(operation, -EINPROGRESS))
		queue_work(connection->wq, &operation->work);
पूर्ण

/*
 * We've received data that appears to be an operation response
 * message.  Look up the operation, and record that we've received
 * its response.
 *
 * This is called in पूर्णांकerrupt context, so just copy the incoming
 * data पूर्णांकo the response buffer and handle the rest via workqueue.
 */
अटल व्योम gb_connection_recv_response(काष्ठा gb_connection *connection,
				स्थिर काष्ठा gb_operation_msg_hdr *header,
				व्योम *data, माप_प्रकार size)
अणु
	काष्ठा gb_operation *operation;
	काष्ठा gb_message *message;
	माप_प्रकार message_size;
	u16 operation_id;
	पूर्णांक त्रुटि_सं;

	operation_id = le16_to_cpu(header->operation_id);

	अगर (!operation_id) अणु
		dev_err_ratelimited(&connection->hd->dev,
				    "%s: invalid response id 0 received\n",
				    connection->name);
		वापस;
	पूर्ण

	operation = gb_operation_find_outgoing(connection, operation_id);
	अगर (!operation) अणु
		dev_err_ratelimited(&connection->hd->dev,
				    "%s: unexpected response id 0x%04x received\n",
				    connection->name, operation_id);
		वापस;
	पूर्ण

	त्रुटि_सं = gb_operation_status_map(header->result);
	message = operation->response;
	message_size = माप(*header) + message->payload_size;
	अगर (!त्रुटि_सं && size > message_size) अणु
		dev_err_ratelimited(&connection->hd->dev,
				    "%s: malformed response 0x%02x received (%zu > %zu)\n",
				    connection->name, header->type,
				    size, message_size);
		त्रुटि_सं = -EMSGSIZE;
	पूर्ण अन्यथा अगर (!त्रुटि_सं && size < message_size) अणु
		अगर (gb_operation_लघु_response_allowed(operation)) अणु
			message->payload_size = size - माप(*header);
		पूर्ण अन्यथा अणु
			dev_err_ratelimited(&connection->hd->dev,
					    "%s: short response 0x%02x received (%zu < %zu)\n",
					    connection->name, header->type,
					    size, message_size);
			त्रुटि_सं = -EMSGSIZE;
		पूर्ण
	पूर्ण

	/* We must ignore the payload अगर a bad status is वापसed */
	अगर (त्रुटि_सं)
		size = माप(*header);

	/* The rest will be handled in work queue context */
	अगर (gb_operation_result_set(operation, त्रुटि_सं)) अणु
		स_नकल(message->buffer, data, size);

		trace_gb_message_recv_response(message);

		queue_work(gb_operation_completion_wq, &operation->work);
	पूर्ण

	gb_operation_put(operation);
पूर्ण

/*
 * Handle data arriving on a connection.  As soon as we वापस the
 * supplied data buffer will be reused (so unless we करो something
 * with, it's effectively dropped).
 */
व्योम gb_connection_recv(काष्ठा gb_connection *connection,
			व्योम *data, माप_प्रकार size)
अणु
	काष्ठा gb_operation_msg_hdr header;
	काष्ठा device *dev = &connection->hd->dev;
	माप_प्रकार msg_size;

	अगर (connection->state == GB_CONNECTION_STATE_DISABLED ||
	    gb_connection_is_offloaded(connection)) अणु
		dev_warn_ratelimited(dev, "%s: dropping %zu received bytes\n",
				     connection->name, size);
		वापस;
	पूर्ण

	अगर (size < माप(header)) अणु
		dev_err_ratelimited(dev, "%s: short message received\n",
				    connection->name);
		वापस;
	पूर्ण

	/* Use स_नकल as data may be unaligned */
	स_नकल(&header, data, माप(header));
	msg_size = le16_to_cpu(header.size);
	अगर (size < msg_size) अणु
		dev_err_ratelimited(dev,
				    "%s: incomplete message 0x%04x of type 0x%02x received (%zu < %zu)\n",
				    connection->name,
				    le16_to_cpu(header.operation_id),
				    header.type, size, msg_size);
		वापस;		/* XXX Should still complete operation */
	पूर्ण

	अगर (header.type & GB_MESSAGE_TYPE_RESPONSE) अणु
		gb_connection_recv_response(connection,	&header, data,
					    msg_size);
	पूर्ण अन्यथा अणु
		gb_connection_recv_request(connection, &header, data,
					   msg_size);
	पूर्ण
पूर्ण

/*
 * Cancel an outgoing operation synchronously, and record the given error to
 * indicate why.
 */
व्योम gb_operation_cancel(काष्ठा gb_operation *operation, पूर्णांक त्रुटि_सं)
अणु
	अगर (WARN_ON(gb_operation_is_incoming(operation)))
		वापस;

	अगर (gb_operation_result_set(operation, त्रुटि_सं)) अणु
		gb_message_cancel(operation->request);
		queue_work(gb_operation_completion_wq, &operation->work);
	पूर्ण
	trace_gb_message_cancel_outgoing(operation->request);

	atomic_inc(&operation->रुकोers);
	रुको_event(gb_operation_cancellation_queue,
		   !gb_operation_is_active(operation));
	atomic_dec(&operation->रुकोers);
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_cancel);

/*
 * Cancel an incoming operation synchronously. Called during connection tear
 * करोwn.
 */
व्योम gb_operation_cancel_incoming(काष्ठा gb_operation *operation, पूर्णांक त्रुटि_सं)
अणु
	अगर (WARN_ON(!gb_operation_is_incoming(operation)))
		वापस;

	अगर (!gb_operation_is_unidirectional(operation)) अणु
		/*
		 * Make sure the request handler has submitted the response
		 * beक्रमe cancelling it.
		 */
		flush_work(&operation->work);
		अगर (!gb_operation_result_set(operation, त्रुटि_सं))
			gb_message_cancel(operation->response);
	पूर्ण
	trace_gb_message_cancel_incoming(operation->response);

	atomic_inc(&operation->रुकोers);
	रुको_event(gb_operation_cancellation_queue,
		   !gb_operation_is_active(operation));
	atomic_dec(&operation->रुकोers);
पूर्ण

/**
 * gb_operation_sync_समयout() - implement a "simple" synchronous operation
 * @connection: the Greybus connection to send this to
 * @type: the type of operation to send
 * @request: poपूर्णांकer to a memory buffer to copy the request from
 * @request_size: size of @request
 * @response: poपूर्णांकer to a memory buffer to copy the response to
 * @response_size: the size of @response.
 * @समयout: operation समयout in milliseconds
 *
 * This function implements a simple synchronous Greybus operation.  It sends
 * the provided operation request and रुकोs (sleeps) until the corresponding
 * operation response message has been successfully received, or an error
 * occurs.  @request and @response are buffers to hold the request and response
 * data respectively, and अगर they are not शून्य, their size must be specअगरied in
 * @request_size and @response_size.
 *
 * If a response payload is to come back, and @response is not शून्य,
 * @response_size number of bytes will be copied पूर्णांकo @response अगर the operation
 * is successful.
 *
 * If there is an error, the response buffer is left alone.
 */
पूर्णांक gb_operation_sync_समयout(काष्ठा gb_connection *connection, पूर्णांक type,
			      व्योम *request, पूर्णांक request_size,
			      व्योम *response, पूर्णांक response_size,
			      अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा gb_operation *operation;
	पूर्णांक ret;

	अगर ((response_size && !response) ||
	    (request_size && !request))
		वापस -EINVAL;

	operation = gb_operation_create(connection, type,
					request_size, response_size,
					GFP_KERNEL);
	अगर (!operation)
		वापस -ENOMEM;

	अगर (request_size)
		स_नकल(operation->request->payload, request, request_size);

	ret = gb_operation_request_send_sync_समयout(operation, समयout);
	अगर (ret) अणु
		dev_err(&connection->hd->dev,
			"%s: synchronous operation id 0x%04x of type 0x%02x failed: %d\n",
			connection->name, operation->id, type, ret);
	पूर्ण अन्यथा अणु
		अगर (response_size) अणु
			स_नकल(response, operation->response->payload,
			       response_size);
		पूर्ण
	पूर्ण

	gb_operation_put(operation);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_sync_समयout);

/**
 * gb_operation_unidirectional_समयout() - initiate a unidirectional operation
 * @connection:		connection to use
 * @type:		type of operation to send
 * @request:		memory buffer to copy the request from
 * @request_size:	size of @request
 * @समयout:		send समयout in milliseconds
 *
 * Initiate a unidirectional operation by sending a request message and
 * रुकोing क्रम it to be acknowledged as sent by the host device.
 *
 * Note that successful send of a unidirectional operation करोes not imply that
 * the request as actually reached the remote end of the connection.
 */
पूर्णांक gb_operation_unidirectional_समयout(काष्ठा gb_connection *connection,
					पूर्णांक type, व्योम *request,
					पूर्णांक request_size,
					अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा gb_operation *operation;
	पूर्णांक ret;

	अगर (request_size && !request)
		वापस -EINVAL;

	operation = gb_operation_create_flags(connection, type,
					      request_size, 0,
					      GB_OPERATION_FLAG_UNIसूचीECTIONAL,
					      GFP_KERNEL);
	अगर (!operation)
		वापस -ENOMEM;

	अगर (request_size)
		स_नकल(operation->request->payload, request, request_size);

	ret = gb_operation_request_send_sync_समयout(operation, समयout);
	अगर (ret) अणु
		dev_err(&connection->hd->dev,
			"%s: unidirectional operation of type 0x%02x failed: %d\n",
			connection->name, type, ret);
	पूर्ण

	gb_operation_put(operation);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gb_operation_unidirectional_समयout);

पूर्णांक __init gb_operation_init(व्योम)
अणु
	gb_message_cache = kmem_cache_create("gb_message_cache",
					     माप(काष्ठा gb_message), 0, 0,
					     शून्य);
	अगर (!gb_message_cache)
		वापस -ENOMEM;

	gb_operation_cache = kmem_cache_create("gb_operation_cache",
					       माप(काष्ठा gb_operation), 0,
					       0, शून्य);
	अगर (!gb_operation_cache)
		जाओ err_destroy_message_cache;

	gb_operation_completion_wq = alloc_workqueue("greybus_completion",
						     0, 0);
	अगर (!gb_operation_completion_wq)
		जाओ err_destroy_operation_cache;

	वापस 0;

err_destroy_operation_cache:
	kmem_cache_destroy(gb_operation_cache);
	gb_operation_cache = शून्य;
err_destroy_message_cache:
	kmem_cache_destroy(gb_message_cache);
	gb_message_cache = शून्य;

	वापस -ENOMEM;
पूर्ण

व्योम gb_operation_निकास(व्योम)
अणु
	destroy_workqueue(gb_operation_completion_wq);
	gb_operation_completion_wq = शून्य;
	kmem_cache_destroy(gb_operation_cache);
	gb_operation_cache = शून्य;
	kmem_cache_destroy(gb_message_cache);
	gb_message_cache = शून्य;
पूर्ण
