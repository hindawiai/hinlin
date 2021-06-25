<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus operations
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#अगर_अघोषित __OPERATION_H
#घोषणा __OPERATION_H

#समावेश <linux/completion.h>
#समावेश <linux/kref.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

काष्ठा gb_host_device;
काष्ठा gb_operation;

/* The शेष amount of समय a request is given to complete */
#घोषणा GB_OPERATION_TIMEOUT_DEFAULT	1000	/* milliseconds */

/*
 * The top bit of the type in an operation message header indicates
 * whether the message is a request (bit clear) or response (bit set)
 */
#घोषणा GB_MESSAGE_TYPE_RESPONSE	((u8)0x80)

क्रमागत gb_operation_result अणु
	GB_OP_SUCCESS		= 0x00,
	GB_OP_INTERRUPTED	= 0x01,
	GB_OP_TIMEOUT		= 0x02,
	GB_OP_NO_MEMORY		= 0x03,
	GB_OP_PROTOCOL_BAD	= 0x04,
	GB_OP_OVERFLOW		= 0x05,
	GB_OP_INVALID		= 0x06,
	GB_OP_RETRY		= 0x07,
	GB_OP_NONEXISTENT	= 0x08,
	GB_OP_UNKNOWN_ERROR	= 0xfe,
	GB_OP_MALFUNCTION	= 0xff,
पूर्ण;

#घोषणा GB_OPERATION_MESSAGE_SIZE_MIN	माप(काष्ठा gb_operation_msg_hdr)
#घोषणा GB_OPERATION_MESSAGE_SIZE_MAX	U16_MAX

/*
 * Protocol code should only examine the payload and payload_size fields, and
 * host-controller drivers may use the hcpriv field. All other fields are
 * पूर्णांकended to be निजी to the operations core code.
 */
काष्ठा gb_message अणु
	काष्ठा gb_operation		*operation;
	काष्ठा gb_operation_msg_hdr	*header;

	व्योम				*payload;
	माप_प्रकार				payload_size;

	व्योम				*buffer;

	व्योम				*hcpriv;
पूर्ण;

#घोषणा GB_OPERATION_FLAG_INCOMING		BIT(0)
#घोषणा GB_OPERATION_FLAG_UNIसूचीECTIONAL	BIT(1)
#घोषणा GB_OPERATION_FLAG_SHORT_RESPONSE	BIT(2)
#घोषणा GB_OPERATION_FLAG_CORE			BIT(3)

#घोषणा GB_OPERATION_FLAG_USER_MASK	(GB_OPERATION_FLAG_SHORT_RESPONSE | \
					 GB_OPERATION_FLAG_UNIसूचीECTIONAL)

/*
 * A Greybus operation is a remote procedure call perक्रमmed over a
 * connection between two UniPro पूर्णांकerfaces.
 *
 * Every operation consists of a request message sent to the other
 * end of the connection coupled with a reply message वापसed to
 * the sender.  Every operation has a type, whose पूर्णांकerpretation is
 * dependent on the protocol associated with the connection.
 *
 * Only four things in an operation काष्ठाure are पूर्णांकended to be
 * directly usable by protocol handlers:  the operation's connection
 * poपूर्णांकer; the operation type; the request message payload (and
 * size); and the response message payload (and size).  Note that a
 * message with a 0-byte payload has a null message payload poपूर्णांकer.
 *
 * In addition, every operation has a result, which is an त्रुटि_सं
 * value.  Protocol handlers access the operation result using
 * gb_operation_result().
 */
प्रकार व्योम (*gb_operation_callback)(काष्ठा gb_operation *);
काष्ठा gb_operation अणु
	काष्ठा gb_connection	*connection;
	काष्ठा gb_message	*request;
	काष्ठा gb_message	*response;

	अचिन्हित दीर्घ		flags;
	u8			type;
	u16			id;
	पूर्णांक			त्रुटि_सं;		/* Operation result */

	काष्ठा work_काष्ठा	work;
	gb_operation_callback	callback;
	काष्ठा completion	completion;
	काष्ठा समयr_list	समयr;

	काष्ठा kref		kref;
	atomic_t		रुकोers;

	पूर्णांक			active;
	काष्ठा list_head	links;		/* connection->operations */

	व्योम			*निजी;
पूर्ण;

अटल अंतरभूत bool
gb_operation_is_incoming(काष्ठा gb_operation *operation)
अणु
	वापस operation->flags & GB_OPERATION_FLAG_INCOMING;
पूर्ण

अटल अंतरभूत bool
gb_operation_is_unidirectional(काष्ठा gb_operation *operation)
अणु
	वापस operation->flags & GB_OPERATION_FLAG_UNIसूचीECTIONAL;
पूर्ण

अटल अंतरभूत bool
gb_operation_लघु_response_allowed(काष्ठा gb_operation *operation)
अणु
	वापस operation->flags & GB_OPERATION_FLAG_SHORT_RESPONSE;
पूर्ण

अटल अंतरभूत bool gb_operation_is_core(काष्ठा gb_operation *operation)
अणु
	वापस operation->flags & GB_OPERATION_FLAG_CORE;
पूर्ण

व्योम gb_connection_recv(काष्ठा gb_connection *connection,
					व्योम *data, माप_प्रकार size);

पूर्णांक gb_operation_result(काष्ठा gb_operation *operation);

माप_प्रकार gb_operation_get_payload_size_max(काष्ठा gb_connection *connection);
काष्ठा gb_operation *
gb_operation_create_flags(काष्ठा gb_connection *connection,
				u8 type, माप_प्रकार request_size,
				माप_प्रकार response_size, अचिन्हित दीर्घ flags,
				gfp_t gfp);

अटल अंतरभूत काष्ठा gb_operation *
gb_operation_create(काष्ठा gb_connection *connection,
				u8 type, माप_प्रकार request_size,
				माप_प्रकार response_size, gfp_t gfp)
अणु
	वापस gb_operation_create_flags(connection, type, request_size,
						response_size, 0, gfp);
पूर्ण

काष्ठा gb_operation *
gb_operation_create_core(काष्ठा gb_connection *connection,
				u8 type, माप_प्रकार request_size,
				माप_प्रकार response_size, अचिन्हित दीर्घ flags,
				gfp_t gfp);

व्योम gb_operation_get(काष्ठा gb_operation *operation);
व्योम gb_operation_put(काष्ठा gb_operation *operation);

bool gb_operation_response_alloc(काष्ठा gb_operation *operation,
					माप_प्रकार response_size, gfp_t gfp);

पूर्णांक gb_operation_request_send(काष्ठा gb_operation *operation,
				gb_operation_callback callback,
				अचिन्हित पूर्णांक समयout,
				gfp_t gfp);
पूर्णांक gb_operation_request_send_sync_समयout(काष्ठा gb_operation *operation,
						अचिन्हित पूर्णांक समयout);
अटल अंतरभूत पूर्णांक
gb_operation_request_send_sync(काष्ठा gb_operation *operation)
अणु
	वापस gb_operation_request_send_sync_समयout(operation,
			GB_OPERATION_TIMEOUT_DEFAULT);
पूर्ण

व्योम gb_operation_cancel(काष्ठा gb_operation *operation, पूर्णांक त्रुटि_सं);
व्योम gb_operation_cancel_incoming(काष्ठा gb_operation *operation, पूर्णांक त्रुटि_सं);

व्योम greybus_message_sent(काष्ठा gb_host_device *hd,
				काष्ठा gb_message *message, पूर्णांक status);

पूर्णांक gb_operation_sync_समयout(काष्ठा gb_connection *connection, पूर्णांक type,
				व्योम *request, पूर्णांक request_size,
				व्योम *response, पूर्णांक response_size,
				अचिन्हित पूर्णांक समयout);
पूर्णांक gb_operation_unidirectional_समयout(काष्ठा gb_connection *connection,
				पूर्णांक type, व्योम *request, पूर्णांक request_size,
				अचिन्हित पूर्णांक समयout);

अटल अंतरभूत पूर्णांक gb_operation_sync(काष्ठा gb_connection *connection, पूर्णांक type,
		      व्योम *request, पूर्णांक request_size,
		      व्योम *response, पूर्णांक response_size)
अणु
	वापस gb_operation_sync_समयout(connection, type,
			request, request_size, response, response_size,
			GB_OPERATION_TIMEOUT_DEFAULT);
पूर्ण

अटल अंतरभूत पूर्णांक gb_operation_unidirectional(काष्ठा gb_connection *connection,
				पूर्णांक type, व्योम *request, पूर्णांक request_size)
अणु
	वापस gb_operation_unidirectional_समयout(connection, type,
			request, request_size, GB_OPERATION_TIMEOUT_DEFAULT);
पूर्ण

अटल अंतरभूत व्योम *gb_operation_get_data(काष्ठा gb_operation *operation)
अणु
	वापस operation->निजी;
पूर्ण

अटल अंतरभूत व्योम gb_operation_set_data(काष्ठा gb_operation *operation,
					 व्योम *data)
अणु
	operation->निजी = data;
पूर्ण

पूर्णांक gb_operation_init(व्योम);
व्योम gb_operation_निकास(व्योम);

#पूर्ण_अगर /* !__OPERATION_H */
