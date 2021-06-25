<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2005 Voltaire Inc.  All rights reserved.
 * Copyright (c) 2005 Intel Corporation.  All rights reserved.
 */

#अगर_अघोषित RDMA_CM_H
#घोषणा RDMA_CM_H

#समावेश <linux/socket.h>
#समावेश <linux/in6.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_sa.h>
#समावेश <uapi/rdma/rdma_user_cm.h>

/*
 * Upon receiving a device removal event, users must destroy the associated
 * RDMA identअगरier and release all resources allocated with the device.
 */
क्रमागत rdma_cm_event_type अणु
	RDMA_CM_EVENT_ADDR_RESOLVED,
	RDMA_CM_EVENT_ADDR_ERROR,
	RDMA_CM_EVENT_ROUTE_RESOLVED,
	RDMA_CM_EVENT_ROUTE_ERROR,
	RDMA_CM_EVENT_CONNECT_REQUEST,
	RDMA_CM_EVENT_CONNECT_RESPONSE,
	RDMA_CM_EVENT_CONNECT_ERROR,
	RDMA_CM_EVENT_UNREACHABLE,
	RDMA_CM_EVENT_REJECTED,
	RDMA_CM_EVENT_ESTABLISHED,
	RDMA_CM_EVENT_DISCONNECTED,
	RDMA_CM_EVENT_DEVICE_REMOVAL,
	RDMA_CM_EVENT_MULTICAST_JOIN,
	RDMA_CM_EVENT_MULTICAST_ERROR,
	RDMA_CM_EVENT_ADDR_CHANGE,
	RDMA_CM_EVENT_TIMEWAIT_EXIT
पूर्ण;

स्थिर अक्षर *__attribute_स्थिर__ rdma_event_msg(क्रमागत rdma_cm_event_type event);

#घोषणा RDMA_IB_IP_PS_MASK   0xFFFFFFFFFFFF0000ULL
#घोषणा RDMA_IB_IP_PS_TCP    0x0000000001060000ULL
#घोषणा RDMA_IB_IP_PS_UDP    0x0000000001110000ULL
#घोषणा RDMA_IB_IP_PS_IB     0x00000000013F0000ULL

काष्ठा rdma_addr अणु
	काष्ठा sockaddr_storage src_addr;
	काष्ठा sockaddr_storage dst_addr;
	काष्ठा rdma_dev_addr dev_addr;
पूर्ण;

काष्ठा rdma_route अणु
	काष्ठा rdma_addr addr;
	काष्ठा sa_path_rec *path_rec;
	पूर्णांक num_paths;
पूर्ण;

काष्ठा rdma_conn_param अणु
	स्थिर व्योम *निजी_data;
	u8 निजी_data_len;
	u8 responder_resources;
	u8 initiator_depth;
	u8 flow_control;
	u8 retry_count;		/* ignored when accepting */
	u8 rnr_retry_count;
	/* Fields below ignored अगर a QP is created on the rdma_cm_id. */
	u8 srq;
	u32 qp_num;
	u32 qkey;
पूर्ण;

काष्ठा rdma_ud_param अणु
	स्थिर व्योम *निजी_data;
	u8 निजी_data_len;
	काष्ठा rdma_ah_attr ah_attr;
	u32 qp_num;
	u32 qkey;
पूर्ण;

काष्ठा rdma_cm_event अणु
	क्रमागत rdma_cm_event_type	 event;
	पूर्णांक			 status;
	जोड़ अणु
		काष्ठा rdma_conn_param	conn;
		काष्ठा rdma_ud_param	ud;
	पूर्ण param;
	काष्ठा rdma_ucm_ece ece;
पूर्ण;

काष्ठा rdma_cm_id;

/**
 * rdma_cm_event_handler - Callback used to report user events.
 *
 * Notes: Users may not call rdma_destroy_id from this callback to destroy
 *   the passed in id, or a corresponding listen id.  Returning a
 *   non-zero value from the callback will destroy the passed in id.
 */
प्रकार पूर्णांक (*rdma_cm_event_handler)(काष्ठा rdma_cm_id *id,
				     काष्ठा rdma_cm_event *event);

काष्ठा rdma_cm_id अणु
	काष्ठा ib_device	*device;
	व्योम			*context;
	काष्ठा ib_qp		*qp;
	rdma_cm_event_handler	 event_handler;
	काष्ठा rdma_route	 route;
	क्रमागत rdma_ucm_port_space ps;
	क्रमागत ib_qp_type		 qp_type;
	u32			 port_num;
पूर्ण;

काष्ठा rdma_cm_id *
__rdma_create_kernel_id(काष्ठा net *net, rdma_cm_event_handler event_handler,
			व्योम *context, क्रमागत rdma_ucm_port_space ps,
			क्रमागत ib_qp_type qp_type, स्थिर अक्षर *caller);
काष्ठा rdma_cm_id *rdma_create_user_id(rdma_cm_event_handler event_handler,
				       व्योम *context,
				       क्रमागत rdma_ucm_port_space ps,
				       क्रमागत ib_qp_type qp_type);

/**
 * rdma_create_id - Create an RDMA identअगरier.
 *
 * @net: The network namespace in which to create the new id.
 * @event_handler: User callback invoked to report events associated with the
 *   वापसed rdma_id.
 * @context: User specअगरied context associated with the id.
 * @ps: RDMA port space.
 * @qp_type: type of queue pair associated with the id.
 *
 * Returns a new rdma_cm_id. The id holds a reference on the network
 * namespace until it is destroyed.
 *
 * The event handler callback serializes on the id's mutex and is
 * allowed to sleep.
 */
#घोषणा rdma_create_id(net, event_handler, context, ps, qp_type)               \
	__rdma_create_kernel_id(net, event_handler, context, ps, qp_type,      \
				KBUILD_MODNAME)

/**
  * rdma_destroy_id - Destroys an RDMA identअगरier.
  *
  * @id: RDMA identअगरier.
  *
  * Note: calling this function has the effect of canceling in-flight
  * asynchronous operations associated with the id.
  */
व्योम rdma_destroy_id(काष्ठा rdma_cm_id *id);

/**
 * rdma_bind_addr - Bind an RDMA identअगरier to a source address and
 *   associated RDMA device, अगर needed.
 *
 * @id: RDMA identअगरier.
 * @addr: Local address inक्रमmation.  Wildcard values are permitted.
 *
 * This associates a source address with the RDMA identअगरier beक्रमe calling
 * rdma_listen.  If a specअगरic local address is given, the RDMA identअगरier will
 * be bound to a local RDMA device.
 */
पूर्णांक rdma_bind_addr(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *addr);

/**
 * rdma_resolve_addr - Resolve destination and optional source addresses
 *   from IP addresses to an RDMA address.  If successful, the specअगरied
 *   rdma_cm_id will be bound to a local device.
 *
 * @id: RDMA identअगरier.
 * @src_addr: Source address inक्रमmation.  This parameter may be शून्य.
 * @dst_addr: Destination address inक्रमmation.
 * @समयout_ms: Time to रुको क्रम resolution to complete.
 */
पूर्णांक rdma_resolve_addr(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *src_addr,
		      स्थिर काष्ठा sockaddr *dst_addr,
		      अचिन्हित दीर्घ समयout_ms);

/**
 * rdma_resolve_route - Resolve the RDMA address bound to the RDMA identअगरier
 *   पूर्णांकo route inक्रमmation needed to establish a connection.
 *
 * This is called on the client side of a connection.
 * Users must have first called rdma_resolve_addr to resolve a dst_addr
 * पूर्णांकo an RDMA address beक्रमe calling this routine.
 */
पूर्णांक rdma_resolve_route(काष्ठा rdma_cm_id *id, अचिन्हित दीर्घ समयout_ms);

/**
 * rdma_create_qp - Allocate a QP and associate it with the specअगरied RDMA
 * identअगरier.
 *
 * QPs allocated to an rdma_cm_id will स्वतःmatically be transitioned by the CMA
 * through their states.
 */
पूर्णांक rdma_create_qp(काष्ठा rdma_cm_id *id, काष्ठा ib_pd *pd,
		   काष्ठा ib_qp_init_attr *qp_init_attr);

/**
 * rdma_destroy_qp - Deallocate the QP associated with the specअगरied RDMA
 * identअगरier.
 *
 * Users must destroy any QP associated with an RDMA identअगरier beक्रमe
 * destroying the RDMA ID.
 */
व्योम rdma_destroy_qp(काष्ठा rdma_cm_id *id);

/**
 * rdma_init_qp_attr - Initializes the QP attributes क्रम use in transitioning
 *   to a specअगरied QP state.
 * @id: Communication identअगरier associated with the QP attributes to
 *   initialize.
 * @qp_attr: On input, specअगरies the desired QP state.  On output, the
 *   mandatory and desired optional attributes will be set in order to
 *   modअगरy the QP to the specअगरied state.
 * @qp_attr_mask: The QP attribute mask that may be used to transition the
 *   QP to the specअगरied state.
 *
 * Users must set the @qp_attr->qp_state to the desired QP state.  This call
 * will set all required attributes क्रम the given transition, aदीर्घ with
 * known optional attributes.  Users may override the attributes वापसed from
 * this call beक्रमe calling ib_modअगरy_qp.
 *
 * Users that wish to have their QP स्वतःmatically transitioned through its
 * states can associate a QP with the rdma_cm_id by calling rdma_create_qp().
 */
पूर्णांक rdma_init_qp_attr(काष्ठा rdma_cm_id *id, काष्ठा ib_qp_attr *qp_attr,
		       पूर्णांक *qp_attr_mask);

पूर्णांक rdma_connect(काष्ठा rdma_cm_id *id, काष्ठा rdma_conn_param *conn_param);
पूर्णांक rdma_connect_locked(काष्ठा rdma_cm_id *id,
			काष्ठा rdma_conn_param *conn_param);

पूर्णांक rdma_connect_ece(काष्ठा rdma_cm_id *id, काष्ठा rdma_conn_param *conn_param,
		     काष्ठा rdma_ucm_ece *ece);

/**
 * rdma_listen - This function is called by the passive side to
 *   listen क्रम incoming connection requests.
 *
 * Users must have bound the rdma_cm_id to a local address by calling
 * rdma_bind_addr beक्रमe calling this routine.
 */
पूर्णांक rdma_listen(काष्ठा rdma_cm_id *id, पूर्णांक backlog);

पूर्णांक rdma_accept(काष्ठा rdma_cm_id *id, काष्ठा rdma_conn_param *conn_param);

व्योम rdma_lock_handler(काष्ठा rdma_cm_id *id);
व्योम rdma_unlock_handler(काष्ठा rdma_cm_id *id);
पूर्णांक rdma_accept_ece(काष्ठा rdma_cm_id *id, काष्ठा rdma_conn_param *conn_param,
		    काष्ठा rdma_ucm_ece *ece);

/**
 * rdma_notअगरy - Notअगरies the RDMA CM of an asynchronous event that has
 * occurred on the connection.
 * @id: Connection identअगरier to transition to established.
 * @event: Asynchronous event.
 *
 * This routine should be invoked by users to notअगरy the CM of relevant
 * communication events.  Events that should be reported to the CM and
 * when to report them are:
 *
 * IB_EVENT_COMM_EST - Used when a message is received on a connected
 *    QP beक्रमe an RTU has been received.
 */
पूर्णांक rdma_notअगरy(काष्ठा rdma_cm_id *id, क्रमागत ib_event_type event);

/**
 * rdma_reject - Called to reject a connection request or response.
 */
पूर्णांक rdma_reject(काष्ठा rdma_cm_id *id, स्थिर व्योम *निजी_data,
		u8 निजी_data_len, u8 reason);

/**
 * rdma_disconnect - This function disconnects the associated QP and
 *   transitions it पूर्णांकo the error state.
 */
पूर्णांक rdma_disconnect(काष्ठा rdma_cm_id *id);

/**
 * rdma_join_multicast - Join the multicast group specअगरied by the given
 *   address.
 * @id: Communication identअगरier associated with the request.
 * @addr: Multicast address identअगरying the group to join.
 * @join_state: Multicast JoinState biपंचांगap requested by port.
 *		Biपंचांगap is based on IB_SA_MCMEMBER_REC_JOIN_STATE bits.
 * @context: User-defined context associated with the join request, वापसed
 * to the user through the निजी_data poपूर्णांकer in multicast events.
 */
पूर्णांक rdma_join_multicast(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *addr,
			u8 join_state, व्योम *context);

/**
 * rdma_leave_multicast - Leave the multicast group specअगरied by the given
 *   address.
 */
व्योम rdma_leave_multicast(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *addr);

/**
 * rdma_set_service_type - Set the type of service associated with a
 *   connection identअगरier.
 * @id: Communication identअगरier to associated with service type.
 * @tos: Type of service.
 *
 * The type of service is पूर्णांकerpretted as a dअगरferentiated service
 * field (RFC 2474).  The service type should be specअगरied beक्रमe
 * perक्रमming route resolution, as existing communication on the
 * connection identअगरier may be unaffected.  The type of service
 * requested may not be supported by the network to all destinations.
 */
व्योम rdma_set_service_type(काष्ठा rdma_cm_id *id, पूर्णांक tos);

/**
 * rdma_set_reuseaddr - Allow the reuse of local addresses when binding
 *    the rdma_cm_id.
 * @id: Communication identअगरier to configure.
 * @reuse: Value indicating अगर the bound address is reusable.
 *
 * Reuse must be set beक्रमe an address is bound to the id.
 */
पूर्णांक rdma_set_reuseaddr(काष्ठा rdma_cm_id *id, पूर्णांक reuse);

/**
 * rdma_set_afonly - Specअगरy that listens are restricted to the
 *    bound address family only.
 * @id: Communication identअगरer to configure.
 * @afonly: Value indicating अगर listens are restricted.
 *
 * Must be set beक्रमe identअगरier is in the listening state.
 */
पूर्णांक rdma_set_afonly(काष्ठा rdma_cm_id *id, पूर्णांक afonly);

पूर्णांक rdma_set_ack_समयout(काष्ठा rdma_cm_id *id, u8 समयout);

पूर्णांक rdma_set_min_rnr_समयr(काष्ठा rdma_cm_id *id, u8 min_rnr_समयr);
 /**
 * rdma_get_service_id - Return the IB service ID क्रम a specअगरied address.
 * @id: Communication identअगरier associated with the address.
 * @addr: Address क्रम the service ID.
 */
__be64 rdma_get_service_id(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *addr);

/**
 * rdma_reject_msg - वापस a poपूर्णांकer to a reject message string.
 * @id: Communication identअगरier that received the REJECT event.
 * @reason: Value वापसed in the REJECT event status field.
 */
स्थिर अक्षर *__attribute_स्थिर__ rdma_reject_msg(काष्ठा rdma_cm_id *id,
						पूर्णांक reason);
/**
 * rdma_consumer_reject_data - वापस the consumer reject निजी data and
 *			       length, अगर any.
 * @id: Communication identअगरier that received the REJECT event.
 * @ev: RDMA CM reject event.
 * @data_len: Poपूर्णांकer to the resulting length of the consumer data.
 */
स्थिर व्योम *rdma_consumer_reject_data(काष्ठा rdma_cm_id *id,
				      काष्ठा rdma_cm_event *ev, u8 *data_len);

/**
 * rdma_पढ़ो_gids - Return the SGID and DGID used क्रम establishing
 *                  connection. This can be used after rdma_resolve_addr()
 *                  on client side. This can be use on new connection
 *                  on server side. This is applicable to IB, RoCE, iWarp.
 *                  If cm_id is not bound yet to the RDMA device, it करोesn't
 *                  copy and SGID or DGID to the given poपूर्णांकers.
 * @id: Communication identअगरier whose GIDs are queried.
 * @sgid: Poपूर्णांकer to SGID where SGID will be वापसed. It is optional.
 * @dgid: Poपूर्णांकer to DGID where DGID will be वापसed. It is optional.
 * Note: This API should not be used by any new ULPs or new code.
 * Instead, users पूर्णांकerested in querying GIDs should refer to path record
 * of the rdma_cm_id to query the GIDs.
 * This API is provided क्रम compatibility क्रम existing users.
 */

व्योम rdma_पढ़ो_gids(काष्ठा rdma_cm_id *cm_id, जोड़ ib_gid *sgid,
		    जोड़ ib_gid *dgid);

काष्ठा iw_cm_id *rdma_iw_cm_id(काष्ठा rdma_cm_id *cm_id);
काष्ठा rdma_cm_id *rdma_res_to_id(काष्ठा rdma_restrack_entry *res);

#पूर्ण_अगर /* RDMA_CM_H */
