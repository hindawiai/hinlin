<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 * Copyright (c) 2017, Linaro Ltd.
 */
#अगर_अघोषित __QMI_HELPERS_H__
#घोषणा __QMI_HELPERS_H__

#समावेश <linux/completion.h>
#समावेश <linux/idr.h>
#समावेश <linux/list.h>
#समावेश <linux/qrtr.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

काष्ठा socket;

/**
 * काष्ठा qmi_header - wireक्रमmat header of QMI messages
 * @type:	type of message
 * @txn_id:	transaction id
 * @msg_id:	message id
 * @msg_len:	length of message payload following header
 */
काष्ठा qmi_header अणु
	u8 type;
	u16 txn_id;
	u16 msg_id;
	u16 msg_len;
पूर्ण __packed;

#घोषणा QMI_REQUEST	0
#घोषणा QMI_RESPONSE	2
#घोषणा QMI_INDICATION	4

#घोषणा QMI_COMMON_TLV_TYPE 0

क्रमागत qmi_elem_type अणु
	QMI_EOTI,
	QMI_OPT_FLAG,
	QMI_DATA_LEN,
	QMI_UNSIGNED_1_BYTE,
	QMI_UNSIGNED_2_BYTE,
	QMI_UNSIGNED_4_BYTE,
	QMI_UNSIGNED_8_BYTE,
	QMI_SIGNED_2_BYTE_ENUM,
	QMI_SIGNED_4_BYTE_ENUM,
	QMI_STRUCT,
	QMI_STRING,
पूर्ण;

क्रमागत qmi_array_type अणु
	NO_ARRAY,
	STATIC_ARRAY,
	VAR_LEN_ARRAY,
पूर्ण;

/**
 * काष्ठा qmi_elem_info - describes how to encode a single QMI element
 * @data_type:	Data type of this element.
 * @elem_len:	Array length of this element, अगर an array.
 * @elem_size:	Size of a single instance of this data type.
 * @array_type:	Array type of this element.
 * @tlv_type:	QMI message specअगरic type to identअगरy which element
 *		is present in an incoming message.
 * @offset:	Specअगरies the offset of the first instance of this
 *		element in the data काष्ठाure.
 * @ei_array:	Null-terminated array of @qmi_elem_info to describe nested
 *		काष्ठाures.
 */
काष्ठा qmi_elem_info अणु
	क्रमागत qmi_elem_type data_type;
	u32 elem_len;
	u32 elem_size;
	क्रमागत qmi_array_type array_type;
	u8 tlv_type;
	u32 offset;
	काष्ठा qmi_elem_info *ei_array;
पूर्ण;

#घोषणा QMI_RESULT_SUCCESS_V01			0
#घोषणा QMI_RESULT_FAILURE_V01			1

#घोषणा QMI_ERR_NONE_V01			0
#घोषणा QMI_ERR_MALFORMED_MSG_V01		1
#घोषणा QMI_ERR_NO_MEMORY_V01			2
#घोषणा QMI_ERR_INTERNAL_V01			3
#घोषणा QMI_ERR_CLIENT_IDS_EXHAUSTED_V01	5
#घोषणा QMI_ERR_INVALID_ID_V01			41
#घोषणा QMI_ERR_ENCODING_V01			58
#घोषणा QMI_ERR_DISABLED_V01                    69
#घोषणा QMI_ERR_INCOMPATIBLE_STATE_V01		90
#घोषणा QMI_ERR_NOT_SUPPORTED_V01		94

/**
 * काष्ठा qmi_response_type_v01 - common response header (decoded)
 * @result:	result of the transaction
 * @error:	error value, when @result is QMI_RESULT_FAILURE_V01
 */
काष्ठा qmi_response_type_v01 अणु
	u16 result;
	u16 error;
पूर्ण;

बाह्य काष्ठा qmi_elem_info qmi_response_type_v01_ei[];

/**
 * काष्ठा qmi_service - context to track lookup-results
 * @service:	service type
 * @version:	version of the @service
 * @instance:	instance id of the @service
 * @node:	node of the service
 * @port:	port of the service
 * @priv:	handle क्रम client's use
 * @list_node:	list_head क्रम house keeping
 */
काष्ठा qmi_service अणु
	अचिन्हित पूर्णांक service;
	अचिन्हित पूर्णांक version;
	अचिन्हित पूर्णांक instance;

	अचिन्हित पूर्णांक node;
	अचिन्हित पूर्णांक port;

	व्योम *priv;
	काष्ठा list_head list_node;
पूर्ण;

काष्ठा qmi_handle;

/**
 * काष्ठा qmi_ops - callbacks क्रम qmi_handle
 * @new_server:		inक्रमm client of a new_server lookup-result, वापसing
 *                      successfully from this call causes the library to call
 *                      @del_server as the service is हटाओd from the
 *                      lookup-result. @priv of the qmi_service can be used by
 *                      the client
 * @del_server:		inक्रमm client of a del_server lookup-result
 * @net_reset:		inक्रमm client that the name service was restarted and
 *                      that and any state needs to be released
 * @msg_handler:	invoked क्रम incoming messages, allows a client to
 *                      override the usual QMI message handler
 * @bye:                inक्रमm a client that all clients from a node are gone
 * @del_client:         inक्रमm a client that a particular client is gone
 */
काष्ठा qmi_ops अणु
	पूर्णांक (*new_server)(काष्ठा qmi_handle *qmi, काष्ठा qmi_service *svc);
	व्योम (*del_server)(काष्ठा qmi_handle *qmi, काष्ठा qmi_service *svc);
	व्योम (*net_reset)(काष्ठा qmi_handle *qmi);
	व्योम (*msg_handler)(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			    स्थिर व्योम *data, माप_प्रकार count);
	व्योम (*bye)(काष्ठा qmi_handle *qmi, अचिन्हित पूर्णांक node);
	व्योम (*del_client)(काष्ठा qmi_handle *qmi,
			   अचिन्हित पूर्णांक node, अचिन्हित पूर्णांक port);
पूर्ण;

/**
 * काष्ठा qmi_txn - transaction context
 * @qmi:	QMI handle this transaction is associated with
 * @id:		transaction id
 * @lock:	क्रम synchronization between handler and रुकोer of messages
 * @completion:	completion object as the transaction receives a response
 * @result:	result code क्रम the completed transaction
 * @ei:		description of the QMI encoded response (optional)
 * @dest:	destination buffer to decode message पूर्णांकo (optional)
 */
काष्ठा qmi_txn अणु
	काष्ठा qmi_handle *qmi;

	u16 id;

	काष्ठा mutex lock;
	काष्ठा completion completion;
	पूर्णांक result;

	काष्ठा qmi_elem_info *ei;
	व्योम *dest;
पूर्ण;

/**
 * काष्ठा qmi_msg_handler - description of QMI message handler
 * @type:	type of message
 * @msg_id:	message id
 * @ei:		description of the QMI encoded message
 * @decoded_size:	size of the decoded object
 * @fn:		function to invoke as the message is decoded
 */
काष्ठा qmi_msg_handler अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक msg_id;

	काष्ठा qmi_elem_info *ei;

	माप_प्रकार decoded_size;
	व्योम (*fn)(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
		   काष्ठा qmi_txn *txn, स्थिर व्योम *decoded);
पूर्ण;

/**
 * काष्ठा qmi_handle - QMI context
 * @sock:	socket handle
 * @sock_lock:	synchronization of @sock modअगरications
 * @sq:		sockaddr of @sock
 * @work:	work क्रम handling incoming messages
 * @wq:		workqueue to post @work on
 * @recv_buf:	scratch buffer क्रम handling incoming messages
 * @recv_buf_size:	size of @recv_buf
 * @lookups:		list of रेजिस्टरed lookup requests
 * @lookup_results:	list of lookup-results advertised to the client
 * @services:		list of रेजिस्टरed services (by this client)
 * @ops:	reference to callbacks
 * @txns:	outstanding transactions
 * @txn_lock:	lock क्रम modअगरications of @txns
 * @handlers:	list of handlers क्रम incoming messages
 */
काष्ठा qmi_handle अणु
	काष्ठा socket *sock;
	काष्ठा mutex sock_lock;

	काष्ठा sockaddr_qrtr sq;

	काष्ठा work_काष्ठा work;
	काष्ठा workqueue_काष्ठा *wq;

	व्योम *recv_buf;
	माप_प्रकार recv_buf_size;

	काष्ठा list_head lookups;
	काष्ठा list_head lookup_results;
	काष्ठा list_head services;

	काष्ठा qmi_ops ops;

	काष्ठा idr txns;
	काष्ठा mutex txn_lock;

	स्थिर काष्ठा qmi_msg_handler *handlers;
पूर्ण;

पूर्णांक qmi_add_lookup(काष्ठा qmi_handle *qmi, अचिन्हित पूर्णांक service,
		   अचिन्हित पूर्णांक version, अचिन्हित पूर्णांक instance);
पूर्णांक qmi_add_server(काष्ठा qmi_handle *qmi, अचिन्हित पूर्णांक service,
		   अचिन्हित पूर्णांक version, अचिन्हित पूर्णांक instance);

पूर्णांक qmi_handle_init(काष्ठा qmi_handle *qmi, माप_प्रकार max_msg_len,
		    स्थिर काष्ठा qmi_ops *ops,
		    स्थिर काष्ठा qmi_msg_handler *handlers);
व्योम qmi_handle_release(काष्ठा qmi_handle *qmi);

sमाप_प्रकार qmi_send_request(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			 काष्ठा qmi_txn *txn, पूर्णांक msg_id, माप_प्रकार len,
			 काष्ठा qmi_elem_info *ei, स्थिर व्योम *c_काष्ठा);
sमाप_प्रकार qmi_send_response(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			  काष्ठा qmi_txn *txn, पूर्णांक msg_id, माप_प्रकार len,
			  काष्ठा qmi_elem_info *ei, स्थिर व्योम *c_काष्ठा);
sमाप_प्रकार qmi_send_indication(काष्ठा qmi_handle *qmi, काष्ठा sockaddr_qrtr *sq,
			    पूर्णांक msg_id, माप_प्रकार len, काष्ठा qmi_elem_info *ei,
			    स्थिर व्योम *c_काष्ठा);

व्योम *qmi_encode_message(पूर्णांक type, अचिन्हित पूर्णांक msg_id, माप_प्रकार *len,
			 अचिन्हित पूर्णांक txn_id, काष्ठा qmi_elem_info *ei,
			 स्थिर व्योम *c_काष्ठा);

पूर्णांक qmi_decode_message(स्थिर व्योम *buf, माप_प्रकार len,
		       काष्ठा qmi_elem_info *ei, व्योम *c_काष्ठा);

पूर्णांक qmi_txn_init(काष्ठा qmi_handle *qmi, काष्ठा qmi_txn *txn,
		 काष्ठा qmi_elem_info *ei, व्योम *c_काष्ठा);
पूर्णांक qmi_txn_रुको(काष्ठा qmi_txn *txn, अचिन्हित दीर्घ समयout);
व्योम qmi_txn_cancel(काष्ठा qmi_txn *txn);

#पूर्ण_अगर
