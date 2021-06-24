<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2005 Network Appliance, Inc. All rights reserved.
 * Copyright (c) 2005 Open Grid Computing, Inc. All rights reserved.
 */

#अगर_अघोषित IW_CM_H
#घोषणा IW_CM_H

#समावेश <linux/in.h>
#समावेश <rdma/ib_cm.h>

काष्ठा iw_cm_id;

क्रमागत iw_cm_event_type अणु
	IW_CM_EVENT_CONNECT_REQUEST = 1, /* connect request received */
	IW_CM_EVENT_CONNECT_REPLY,	 /* reply from active connect request */
	IW_CM_EVENT_ESTABLISHED,	 /* passive side accept successful */
	IW_CM_EVENT_DISCONNECT,		 /* orderly shutकरोwn */
	IW_CM_EVENT_CLOSE		 /* बंद complete */
पूर्ण;

काष्ठा iw_cm_event अणु
	क्रमागत iw_cm_event_type event;
	पूर्णांक			 status;
	काष्ठा sockaddr_storage local_addr;
	काष्ठा sockaddr_storage remote_addr;
	व्योम *निजी_data;
	व्योम *provider_data;
	u8 निजी_data_len;
	u8 ord;
	u8 ird;
पूर्ण;

/**
 * iw_cm_handler - Function to be called by the IW CM when delivering events
 * to the client.
 *
 * @cm_id: The IW CM identअगरier associated with the event.
 * @event: Poपूर्णांकer to the event काष्ठाure.
 */
प्रकार पूर्णांक (*iw_cm_handler)(काष्ठा iw_cm_id *cm_id,
			     काष्ठा iw_cm_event *event);

/**
 * iw_event_handler - Function called by the provider when delivering provider
 * events to the IW CM.  Returns either 0 indicating the event was processed
 * or -त्रुटि_सं अगर the event could not be processed.
 *
 * @cm_id: The IW CM identअगरier associated with the event.
 * @event: Poपूर्णांकer to the event काष्ठाure.
 */
प्रकार पूर्णांक (*iw_event_handler)(काष्ठा iw_cm_id *cm_id,
				 काष्ठा iw_cm_event *event);

काष्ठा iw_cm_id अणु
	iw_cm_handler		cm_handler;      /* client callback function */
	व्योम		        *context;	 /* client cb context */
	काष्ठा ib_device	*device;
	काष्ठा sockaddr_storage local_addr;      /* local addr */
	काष्ठा sockaddr_storage	remote_addr;
	काष्ठा sockaddr_storage m_local_addr;	 /* nmapped local addr */
	काष्ठा sockaddr_storage	m_remote_addr;	 /* nmapped rem addr */
	व्योम			*provider_data;	 /* provider निजी data */
	iw_event_handler        event_handler;   /* cb क्रम provider
						    events */
	/* Used by provider to add and हटाओ refs on IW cm_id */
	व्योम (*add_ref)(काष्ठा iw_cm_id *);
	व्योम (*rem_ref)(काष्ठा iw_cm_id *);
	u8  tos;
	bool tos_set:1;
	bool mapped:1;
	bool afonly:1;
पूर्ण;

काष्ठा iw_cm_conn_param अणु
	स्थिर व्योम *निजी_data;
	u16 निजी_data_len;
	u32 ord;
	u32 ird;
	u32 qpn;
पूर्ण;

क्रमागत iw_flags अणु

	/*
	 * This flag allows the iwcm and iwpmd to still advertise
	 * mappings but the real and mapped port numbers are the
	 * same.  Further, iwpmd will not bind any user socket to
	 * reserve the port.  This is required क्रम soft iwarp
	 * to play in the port mapped iwarp space.
	 */
	IW_F_NO_PORT_MAP = (1 << 0),
पूर्ण;

/**
 * iw_create_cm_id - Create an IW CM identअगरier.
 *
 * @device: The IB device on which to create the IW CM identier.
 * @event_handler: User callback invoked to report events associated with the
 *   वापसed IW CM identअगरier.
 * @context: User specअगरied context associated with the id.
 */
काष्ठा iw_cm_id *iw_create_cm_id(काष्ठा ib_device *device,
				 iw_cm_handler cm_handler, व्योम *context);

/**
 * iw_destroy_cm_id - Destroy an IW CM identअगरier.
 *
 * @cm_id: The previously created IW CM identअगरier to destroy.
 *
 * The client can assume that no events will be delivered क्रम the CM ID after
 * this function वापसs.
 */
व्योम iw_destroy_cm_id(काष्ठा iw_cm_id *cm_id);

/**
 * iw_cm_bind_qp - Unbind the specअगरied IW CM identअगरier and QP
 *
 * @cm_id: The IW CM idenfier to unbind from the QP.
 * @qp: The QP
 *
 * This is called by the provider when destroying the QP to ensure
 * that any references held by the IWCM are released. It may also
 * be called by the IWCM when destroying a CM_ID to that any
 * references held by the provider are released.
 */
व्योम iw_cm_unbind_qp(काष्ठा iw_cm_id *cm_id, काष्ठा ib_qp *qp);

/**
 * iw_cm_get_qp - Return the ib_qp associated with a QPN
 *
 * @ib_device: The IB device
 * @qpn: The queue pair number
 */
काष्ठा ib_qp *iw_cm_get_qp(काष्ठा ib_device *device, पूर्णांक qpn);

/**
 * iw_cm_listen - Listen क्रम incoming connection requests on the
 * specअगरied IW CM id.
 *
 * @cm_id: The IW CM identअगरier.
 * @backlog: The maximum number of outstanding un-accepted inbound listen
 *   requests to queue.
 *
 * The source address and port number are specअगरied in the IW CM identअगरier
 * काष्ठाure.
 */
पूर्णांक iw_cm_listen(काष्ठा iw_cm_id *cm_id, पूर्णांक backlog);

/**
 * iw_cm_accept - Called to accept an incoming connect request.
 *
 * @cm_id: The IW CM identअगरier associated with the connection request.
 * @iw_param: Poपूर्णांकer to a काष्ठाure containing connection establishment
 *   parameters.
 *
 * The specअगरied cm_id will have been provided in the event data क्रम a
 * CONNECT_REQUEST event. Subsequent events related to this connection will be
 * delivered to the specअगरied IW CM identअगरier prior and may occur prior to
 * the वापस of this function. If this function वापसs a non-zero value, the
 * client can assume that no events will be delivered to the specअगरied IW CM
 * identअगरier.
 */
पूर्णांक iw_cm_accept(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *iw_param);

/**
 * iw_cm_reject - Reject an incoming connection request.
 *
 * @cm_id: Connection identअगरier associated with the request.
 * @निजी_daa: Poपूर्णांकer to data to deliver to the remote peer as part of the
 *   reject message.
 * @निजी_data_len: The number of bytes in the निजी_data parameter.
 *
 * The client can assume that no events will be delivered to the specअगरied IW
 * CM identअगरier following the वापस of this function. The निजी_data
 * buffer is available क्रम reuse when this function वापसs.
 */
पूर्णांक iw_cm_reject(काष्ठा iw_cm_id *cm_id, स्थिर व्योम *निजी_data,
		 u8 निजी_data_len);

/**
 * iw_cm_connect - Called to request a connection to a remote peer.
 *
 * @cm_id: The IW CM identअगरier क्रम the connection.
 * @iw_param: Poपूर्णांकer to a काष्ठाure containing connection  establishment
 *   parameters.
 *
 * Events may be delivered to the specअगरied IW CM identअगरier prior to the
 * वापस of this function. If this function वापसs a non-zero value, the
 * client can assume that no events will be delivered to the specअगरied IW CM
 * identअगरier.
 */
पूर्णांक iw_cm_connect(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *iw_param);

/**
 * iw_cm_disconnect - Close the specअगरied connection.
 *
 * @cm_id: The IW CM identअगरier to बंद.
 * @abrupt: If 0, the connection will be बंदd gracefully, otherwise, the
 *   connection will be reset.
 *
 * The IW CM identअगरier is still active until the IW_CM_EVENT_CLOSE event is
 * delivered.
 */
पूर्णांक iw_cm_disconnect(काष्ठा iw_cm_id *cm_id, पूर्णांक abrupt);

/**
 * iw_cm_init_qp_attr - Called to initialize the attributes of the QP
 * associated with a IW CM identअगरier.
 *
 * @cm_id: The IW CM identअगरier associated with the QP
 * @qp_attr: Poपूर्णांकer to the QP attributes काष्ठाure.
 * @qp_attr_mask: Poपूर्णांकer to a bit vector specअगरying which QP attributes are
 *   valid.
 */
पूर्णांक iw_cm_init_qp_attr(काष्ठा iw_cm_id *cm_id, काष्ठा ib_qp_attr *qp_attr,
		       पूर्णांक *qp_attr_mask);

/**
 * iwcm_reject_msg - वापस a poपूर्णांकer to a reject message string.
 * @reason: Value वापसed in the REJECT event status field.
 */
स्थिर अक्षर *__attribute_स्थिर__ iwcm_reject_msg(पूर्णांक reason);

#पूर्ण_अगर /* IW_CM_H */
