<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2004, 2005 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004 Voltaire Corporation.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2019, Mellanox Technologies inc.  All rights reserved.
 */

#अगर_अघोषित IB_CM_H
#घोषणा IB_CM_H

#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_sa.h>
#समावेश <rdma/rdma_cm.h>

क्रमागत ib_cm_state अणु
	IB_CM_IDLE,
	IB_CM_LISTEN,
	IB_CM_REQ_SENT,
	IB_CM_REQ_RCVD,
	IB_CM_MRA_REQ_SENT,
	IB_CM_MRA_REQ_RCVD,
	IB_CM_REP_SENT,
	IB_CM_REP_RCVD,
	IB_CM_MRA_REP_SENT,
	IB_CM_MRA_REP_RCVD,
	IB_CM_ESTABLISHED,
	IB_CM_DREQ_SENT,
	IB_CM_DREQ_RCVD,
	IB_CM_TIMEWAIT,
	IB_CM_SIDR_REQ_SENT,
	IB_CM_SIDR_REQ_RCVD
पूर्ण;

क्रमागत ib_cm_lap_state अणु
	IB_CM_LAP_UNINIT,
	IB_CM_LAP_IDLE,
	IB_CM_LAP_SENT,
	IB_CM_LAP_RCVD,
	IB_CM_MRA_LAP_SENT,
	IB_CM_MRA_LAP_RCVD,
पूर्ण;

क्रमागत ib_cm_event_type अणु
	IB_CM_REQ_ERROR,
	IB_CM_REQ_RECEIVED,
	IB_CM_REP_ERROR,
	IB_CM_REP_RECEIVED,
	IB_CM_RTU_RECEIVED,
	IB_CM_USER_ESTABLISHED,
	IB_CM_DREQ_ERROR,
	IB_CM_DREQ_RECEIVED,
	IB_CM_DREP_RECEIVED,
	IB_CM_TIMEWAIT_EXIT,
	IB_CM_MRA_RECEIVED,
	IB_CM_REJ_RECEIVED,
	IB_CM_LAP_ERROR,
	IB_CM_LAP_RECEIVED,
	IB_CM_APR_RECEIVED,
	IB_CM_SIDR_REQ_ERROR,
	IB_CM_SIDR_REQ_RECEIVED,
	IB_CM_SIDR_REP_RECEIVED
पूर्ण;

क्रमागत ib_cm_data_size अणु
	IB_CM_REQ_PRIVATE_DATA_SIZE	 = 92,
	IB_CM_MRA_PRIVATE_DATA_SIZE	 = 222,
	IB_CM_REJ_PRIVATE_DATA_SIZE	 = 148,
	IB_CM_REP_PRIVATE_DATA_SIZE	 = 196,
	IB_CM_RTU_PRIVATE_DATA_SIZE	 = 224,
	IB_CM_DREQ_PRIVATE_DATA_SIZE	 = 220,
	IB_CM_DREP_PRIVATE_DATA_SIZE	 = 224,
	IB_CM_REJ_ARI_LENGTH		 = 72,
	IB_CM_LAP_PRIVATE_DATA_SIZE	 = 168,
	IB_CM_APR_PRIVATE_DATA_SIZE	 = 148,
	IB_CM_APR_INFO_LENGTH		 = 72,
	IB_CM_SIDR_REQ_PRIVATE_DATA_SIZE = 216,
	IB_CM_SIDR_REP_PRIVATE_DATA_SIZE = 136,
	IB_CM_SIDR_REP_INFO_LENGTH	 = 72,
पूर्ण;

काष्ठा ib_cm_id;

काष्ठा ib_cm_req_event_param अणु
	काष्ठा ib_cm_id		*listen_id;

	/* P_Key that was used by the GMP's BTH header */
	u16			bth_pkey;

	u8			port;

	काष्ठा sa_path_rec	*primary_path;
	काष्ठा sa_path_rec	*alternate_path;

	/*
	 * SGID attribute of the primary path. Currently only
	 * useful क्रम RoCE. Alternate path GID attributes
	 * are not yet supported.
	 */
	स्थिर काष्ठा ib_gid_attr *ppath_sgid_attr;

	__be64			remote_ca_guid;
	u32			remote_qkey;
	u32			remote_qpn;
	क्रमागत ib_qp_type		qp_type;

	u32			starting_psn;
	u8			responder_resources;
	u8			initiator_depth;
	अचिन्हित पूर्णांक		local_cm_response_समयout:5;
	अचिन्हित पूर्णांक		flow_control:1;
	अचिन्हित पूर्णांक		remote_cm_response_समयout:5;
	अचिन्हित पूर्णांक		retry_count:3;
	अचिन्हित पूर्णांक		rnr_retry_count:3;
	अचिन्हित पूर्णांक		srq:1;
	काष्ठा rdma_ucm_ece	ece;
पूर्ण;

काष्ठा ib_cm_rep_event_param अणु
	__be64			remote_ca_guid;
	u32			remote_qkey;
	u32			remote_qpn;
	u32			starting_psn;
	u8			responder_resources;
	u8			initiator_depth;
	अचिन्हित पूर्णांक		target_ack_delay:5;
	अचिन्हित पूर्णांक		failover_accepted:2;
	अचिन्हित पूर्णांक		flow_control:1;
	अचिन्हित पूर्णांक		rnr_retry_count:3;
	अचिन्हित पूर्णांक		srq:1;
	काष्ठा rdma_ucm_ece	ece;
पूर्ण;

क्रमागत ib_cm_rej_reason अणु
	IB_CM_REJ_NO_QP				= 1,
	IB_CM_REJ_NO_EEC			= 2,
	IB_CM_REJ_NO_RESOURCES			= 3,
	IB_CM_REJ_TIMEOUT			= 4,
	IB_CM_REJ_UNSUPPORTED			= 5,
	IB_CM_REJ_INVALID_COMM_ID		= 6,
	IB_CM_REJ_INVALID_COMM_INSTANCE		= 7,
	IB_CM_REJ_INVALID_SERVICE_ID		= 8,
	IB_CM_REJ_INVALID_TRANSPORT_TYPE	= 9,
	IB_CM_REJ_STALE_CONN			= 10,
	IB_CM_REJ_RDC_NOT_EXIST			= 11,
	IB_CM_REJ_INVALID_GID			= 12,
	IB_CM_REJ_INVALID_LID			= 13,
	IB_CM_REJ_INVALID_SL			= 14,
	IB_CM_REJ_INVALID_TRAFFIC_CLASS		= 15,
	IB_CM_REJ_INVALID_HOP_LIMIT		= 16,
	IB_CM_REJ_INVALID_PACKET_RATE		= 17,
	IB_CM_REJ_INVALID_ALT_GID		= 18,
	IB_CM_REJ_INVALID_ALT_LID		= 19,
	IB_CM_REJ_INVALID_ALT_SL		= 20,
	IB_CM_REJ_INVALID_ALT_TRAFFIC_CLASS	= 21,
	IB_CM_REJ_INVALID_ALT_HOP_LIMIT		= 22,
	IB_CM_REJ_INVALID_ALT_PACKET_RATE	= 23,
	IB_CM_REJ_PORT_CM_REसूचीECT		= 24,
	IB_CM_REJ_PORT_REसूचीECT			= 25,
	IB_CM_REJ_INVALID_MTU			= 26,
	IB_CM_REJ_INSUFFICIENT_RESP_RESOURCES	= 27,
	IB_CM_REJ_CONSUMER_DEFINED		= 28,
	IB_CM_REJ_INVALID_RNR_RETRY		= 29,
	IB_CM_REJ_DUPLICATE_LOCAL_COMM_ID	= 30,
	IB_CM_REJ_INVALID_CLASS_VERSION		= 31,
	IB_CM_REJ_INVALID_FLOW_LABEL		= 32,
	IB_CM_REJ_INVALID_ALT_FLOW_LABEL	= 33,
	IB_CM_REJ_VENDOR_OPTION_NOT_SUPPORTED	= 35,
पूर्ण;

काष्ठा ib_cm_rej_event_param अणु
	क्रमागत ib_cm_rej_reason	reason;
	व्योम			*ari;
	u8			ari_length;
पूर्ण;

काष्ठा ib_cm_mra_event_param अणु
	u8	service_समयout;
पूर्ण;

काष्ठा ib_cm_lap_event_param अणु
	काष्ठा sa_path_rec	*alternate_path;
पूर्ण;

क्रमागत ib_cm_apr_status अणु
	IB_CM_APR_SUCCESS,
	IB_CM_APR_INVALID_COMM_ID,
	IB_CM_APR_UNSUPPORTED,
	IB_CM_APR_REJECT,
	IB_CM_APR_REसूचीECT,
	IB_CM_APR_IS_CURRENT,
	IB_CM_APR_INVALID_QPN_EECN,
	IB_CM_APR_INVALID_LID,
	IB_CM_APR_INVALID_GID,
	IB_CM_APR_INVALID_FLOW_LABEL,
	IB_CM_APR_INVALID_TCLASS,
	IB_CM_APR_INVALID_HOP_LIMIT,
	IB_CM_APR_INVALID_PACKET_RATE,
	IB_CM_APR_INVALID_SL
पूर्ण;

काष्ठा ib_cm_apr_event_param अणु
	क्रमागत ib_cm_apr_status	ap_status;
	व्योम			*apr_info;
	u8			info_len;
पूर्ण;

काष्ठा ib_cm_sidr_req_event_param अणु
	काष्ठा ib_cm_id		*listen_id;
	__be64			service_id;

	/*
	 * SGID attribute of the request. Currently only
	 * useful क्रम RoCE.
	 */
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	/* P_Key that was used by the GMP's BTH header */
	u16			bth_pkey;
	u8			port;
	u16			pkey;
पूर्ण;

क्रमागत ib_cm_sidr_status अणु
	IB_SIDR_SUCCESS,
	IB_SIDR_UNSUPPORTED,
	IB_SIDR_REJECT,
	IB_SIDR_NO_QP,
	IB_SIDR_REसूचीECT,
	IB_SIDR_UNSUPPORTED_VERSION
पूर्ण;

काष्ठा ib_cm_sidr_rep_event_param अणु
	क्रमागत ib_cm_sidr_status	status;
	u32			qkey;
	u32			qpn;
	व्योम			*info;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	u8			info_len;
पूर्ण;

काष्ठा ib_cm_event अणु
	क्रमागत ib_cm_event_type	event;
	जोड़ अणु
		काष्ठा ib_cm_req_event_param	req_rcvd;
		काष्ठा ib_cm_rep_event_param	rep_rcvd;
		/* No data क्रम RTU received events. */
		काष्ठा ib_cm_rej_event_param	rej_rcvd;
		काष्ठा ib_cm_mra_event_param	mra_rcvd;
		काष्ठा ib_cm_lap_event_param	lap_rcvd;
		काष्ठा ib_cm_apr_event_param	apr_rcvd;
		/* No data क्रम DREQ/DREP received events. */
		काष्ठा ib_cm_sidr_req_event_param sidr_req_rcvd;
		काष्ठा ib_cm_sidr_rep_event_param sidr_rep_rcvd;
		क्रमागत ib_wc_status		send_status;
	पूर्ण param;

	व्योम			*निजी_data;
पूर्ण;

#घोषणा CM_REQ_ATTR_ID		cpu_to_be16(0x0010)
#घोषणा CM_MRA_ATTR_ID		cpu_to_be16(0x0011)
#घोषणा CM_REJ_ATTR_ID		cpu_to_be16(0x0012)
#घोषणा CM_REP_ATTR_ID		cpu_to_be16(0x0013)
#घोषणा CM_RTU_ATTR_ID		cpu_to_be16(0x0014)
#घोषणा CM_DREQ_ATTR_ID		cpu_to_be16(0x0015)
#घोषणा CM_DREP_ATTR_ID		cpu_to_be16(0x0016)
#घोषणा CM_SIDR_REQ_ATTR_ID	cpu_to_be16(0x0017)
#घोषणा CM_SIDR_REP_ATTR_ID	cpu_to_be16(0x0018)
#घोषणा CM_LAP_ATTR_ID		cpu_to_be16(0x0019)
#घोषणा CM_APR_ATTR_ID		cpu_to_be16(0x001A)

/**
 * ib_cm_handler - User-defined callback to process communication events.
 * @cm_id: Communication identअगरier associated with the reported event.
 * @event: Inक्रमmation about the communication event.
 *
 * IB_CM_REQ_RECEIVED and IB_CM_SIDR_REQ_RECEIVED communication events
 * generated as a result of listen requests result in the allocation of a
 * new @cm_id.  The new @cm_id is वापसed to the user through this callback.
 * Clients are responsible क्रम destroying the new @cm_id.  For peer-to-peer
 * IB_CM_REQ_RECEIVED and all other events, the वापसed @cm_id corresponds
 * to a user's existing communication identअगरier.
 *
 * Users may not call ib_destroy_cm_id जबतक in the context of this callback;
 * however, वापसing a non-zero value inकाष्ठाs the communication manager to
 * destroy the @cm_id after the callback completes.
 */
प्रकार पूर्णांक (*ib_cm_handler)(काष्ठा ib_cm_id *cm_id,
			     स्थिर काष्ठा ib_cm_event *event);

काष्ठा ib_cm_id अणु
	ib_cm_handler		cm_handler;
	व्योम			*context;
	काष्ठा ib_device	*device;
	__be64			service_id;
	__be64			service_mask;
	क्रमागत ib_cm_state	state;		/* पूर्णांकernal CM/debug use */
	क्रमागत ib_cm_lap_state	lap_state;	/* पूर्णांकernal CM/debug use */
	__be32			local_id;
	__be32			remote_id;
	u32			remote_cm_qpn;  /* 1 unless redirected */
पूर्ण;

/**
 * ib_create_cm_id - Allocate a communication identअगरier.
 * @device: Device associated with the cm_id.  All related communication will
 * be associated with the specअगरied device.
 * @cm_handler: Callback invoked to notअगरy the user of CM events.
 * @context: User specअगरied context associated with the communication
 *   identअगरier.
 *
 * Communication identअगरiers are used to track connection states, service
 * ID resolution requests, and listen requests.
 */
काष्ठा ib_cm_id *ib_create_cm_id(काष्ठा ib_device *device,
				 ib_cm_handler cm_handler,
				 व्योम *context);

/**
 * ib_destroy_cm_id - Destroy a connection identअगरier.
 * @cm_id: Connection identअगरier to destroy.
 *
 * This call blocks until the connection identअगरier is destroyed.
 */
व्योम ib_destroy_cm_id(काष्ठा ib_cm_id *cm_id);

#घोषणा IB_SERVICE_ID_AGN_MASK	cpu_to_be64(0xFF00000000000000ULL)
#घोषणा IB_CM_ASSIGN_SERVICE_ID	cpu_to_be64(0x0200000000000000ULL)
#घोषणा IB_CMA_SERVICE_ID	cpu_to_be64(0x0000000001000000ULL)
#घोषणा IB_CMA_SERVICE_ID_MASK	cpu_to_be64(0xFFFFFFFFFF000000ULL)
#घोषणा IB_SDP_SERVICE_ID	cpu_to_be64(0x0000000000010000ULL)
#घोषणा IB_SDP_SERVICE_ID_MASK	cpu_to_be64(0xFFFFFFFFFFFF0000ULL)

/**
 * ib_cm_listen - Initiates listening on the specअगरied service ID क्रम
 *   connection and service ID resolution requests.
 * @cm_id: Connection identअगरier associated with the listen request.
 * @service_id: Service identअगरier matched against incoming connection
 *   and service ID resolution requests.  The service ID should be specअगरied
 *   network-byte order.  If set to IB_CM_ASSIGN_SERVICE_ID, the CM will
 *   assign a service ID to the caller.
 * @service_mask: Mask applied to service ID used to listen across a
 *   range of service IDs.  If set to 0, the service ID is matched
 *   exactly.  This parameter is ignored अगर %service_id is set to
 *   IB_CM_ASSIGN_SERVICE_ID.
 */
पूर्णांक ib_cm_listen(काष्ठा ib_cm_id *cm_id, __be64 service_id,
		 __be64 service_mask);

काष्ठा ib_cm_id *ib_cm_insert_listen(काष्ठा ib_device *device,
				     ib_cm_handler cm_handler,
				     __be64 service_id);

काष्ठा ib_cm_req_param अणु
	काष्ठा sa_path_rec	*primary_path;
	काष्ठा sa_path_rec	*alternate_path;
	स्थिर काष्ठा ib_gid_attr *ppath_sgid_attr;
	__be64			service_id;
	u32			qp_num;
	क्रमागत ib_qp_type		qp_type;
	u32			starting_psn;
	स्थिर व्योम		*निजी_data;
	u8			निजी_data_len;
	u8			responder_resources;
	u8			initiator_depth;
	u8			remote_cm_response_समयout;
	u8			flow_control;
	u8			local_cm_response_समयout;
	u8			retry_count;
	u8			rnr_retry_count;
	u8			max_cm_retries;
	u8			srq;
	काष्ठा rdma_ucm_ece	ece;
पूर्ण;

/**
 * ib_send_cm_req - Sends a connection request to the remote node.
 * @cm_id: Connection identअगरier that will be associated with the
 *   connection request.
 * @param: Connection request inक्रमmation needed to establish the
 *   connection.
 */
पूर्णांक ib_send_cm_req(काष्ठा ib_cm_id *cm_id,
		   काष्ठा ib_cm_req_param *param);

काष्ठा ib_cm_rep_param अणु
	u32		qp_num;
	u32		starting_psn;
	स्थिर व्योम	*निजी_data;
	u8		निजी_data_len;
	u8		responder_resources;
	u8		initiator_depth;
	u8		failover_accepted;
	u8		flow_control;
	u8		rnr_retry_count;
	u8		srq;
	काष्ठा rdma_ucm_ece ece;
पूर्ण;

/**
 * ib_send_cm_rep - Sends a connection reply in response to a connection
 *   request.
 * @cm_id: Connection identअगरier that will be associated with the
 *   connection request.
 * @param: Connection reply inक्रमmation needed to establish the
 *   connection.
 */
पूर्णांक ib_send_cm_rep(काष्ठा ib_cm_id *cm_id,
		   काष्ठा ib_cm_rep_param *param);

/**
 * ib_send_cm_rtu - Sends a connection पढ़ोy to use message in response
 *   to a connection reply message.
 * @cm_id: Connection identअगरier associated with the connection request.
 * @निजी_data: Optional user-defined निजी data sent with the
 *   पढ़ोy to use message.
 * @निजी_data_len: Size of the निजी data buffer, in bytes.
 */
पूर्णांक ib_send_cm_rtu(काष्ठा ib_cm_id *cm_id,
		   स्थिर व्योम *निजी_data,
		   u8 निजी_data_len);

/**
 * ib_send_cm_dreq - Sends a disconnection request क्रम an existing
 *   connection.
 * @cm_id: Connection identअगरier associated with the connection being
 *   released.
 * @निजी_data: Optional user-defined निजी data sent with the
 *   disconnection request message.
 * @निजी_data_len: Size of the निजी data buffer, in bytes.
 */
पूर्णांक ib_send_cm_dreq(काष्ठा ib_cm_id *cm_id,
		    स्थिर व्योम *निजी_data,
		    u8 निजी_data_len);

/**
 * ib_send_cm_drep - Sends a disconnection reply to a disconnection request.
 * @cm_id: Connection identअगरier associated with the connection being
 *   released.
 * @निजी_data: Optional user-defined निजी data sent with the
 *   disconnection reply message.
 * @निजी_data_len: Size of the निजी data buffer, in bytes.
 *
 * If the cm_id is in the correct state, the CM will transition the connection
 * to the समयरुको state, even अगर an error occurs sending the DREP message.
 */
पूर्णांक ib_send_cm_drep(काष्ठा ib_cm_id *cm_id,
		    स्थिर व्योम *निजी_data,
		    u8 निजी_data_len);

/**
 * ib_cm_notअगरy - Notअगरies the CM of an event reported to the consumer.
 * @cm_id: Connection identअगरier to transition to established.
 * @event: Type of event.
 *
 * This routine should be invoked by users to notअगरy the CM of relevant
 * communication events.  Events that should be reported to the CM and
 * when to report them are:
 *
 * IB_EVENT_COMM_EST - Used when a message is received on a connected
 *    QP beक्रमe an RTU has been received.
 * IB_EVENT_PATH_MIG - Notअगरies the CM that the connection has failed over
 *   to the alternate path.
 */
पूर्णांक ib_cm_notअगरy(काष्ठा ib_cm_id *cm_id, क्रमागत ib_event_type event);

/**
 * ib_send_cm_rej - Sends a connection rejection message to the
 *   remote node.
 * @cm_id: Connection identअगरier associated with the connection being
 *   rejected.
 * @reason: Reason क्रम the connection request rejection.
 * @ari: Optional additional rejection inक्रमmation.
 * @ari_length: Size of the additional rejection inक्रमmation, in bytes.
 * @निजी_data: Optional user-defined निजी data sent with the
 *   rejection message.
 * @निजी_data_len: Size of the निजी data buffer, in bytes.
 */
पूर्णांक ib_send_cm_rej(काष्ठा ib_cm_id *cm_id,
		   क्रमागत ib_cm_rej_reason reason,
		   व्योम *ari,
		   u8 ari_length,
		   स्थिर व्योम *निजी_data,
		   u8 निजी_data_len);

#घोषणा IB_CM_MRA_FLAG_DELAY 0x80  /* Send MRA only after a duplicate msg */

/**
 * ib_send_cm_mra - Sends a message receipt acknowledgement to a connection
 *   message.
 * @cm_id: Connection identअगरier associated with the connection message.
 * @service_समयout: The lower 5-bits specअगरy the maximum समय required क्रम
 *   the sender to reply to the connection message.  The upper 3-bits
 *   specअगरy additional control flags.
 * @निजी_data: Optional user-defined निजी data sent with the
 *   message receipt acknowledgement.
 * @निजी_data_len: Size of the निजी data buffer, in bytes.
 */
पूर्णांक ib_send_cm_mra(काष्ठा ib_cm_id *cm_id,
		   u8 service_समयout,
		   स्थिर व्योम *निजी_data,
		   u8 निजी_data_len);

/**
 * ib_cm_init_qp_attr - Initializes the QP attributes क्रम use in transitioning
 *   to a specअगरied QP state.
 * @cm_id: Communication identअगरier associated with the QP attributes to
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
 */
पूर्णांक ib_cm_init_qp_attr(काष्ठा ib_cm_id *cm_id,
		       काष्ठा ib_qp_attr *qp_attr,
		       पूर्णांक *qp_attr_mask);

काष्ठा ib_cm_sidr_req_param अणु
	काष्ठा sa_path_rec	*path;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	__be64			service_id;
	अचिन्हित दीर्घ		समयout_ms;
	स्थिर व्योम		*निजी_data;
	u8			निजी_data_len;
	u8			max_cm_retries;
पूर्ण;

/**
 * ib_send_cm_sidr_req - Sends a service ID resolution request to the
 *   remote node.
 * @cm_id: Communication identअगरier that will be associated with the
 *   service ID resolution request.
 * @param: Service ID resolution request inक्रमmation.
 */
पूर्णांक ib_send_cm_sidr_req(काष्ठा ib_cm_id *cm_id,
			काष्ठा ib_cm_sidr_req_param *param);

काष्ठा ib_cm_sidr_rep_param अणु
	u32			qp_num;
	u32			qkey;
	क्रमागत ib_cm_sidr_status	status;
	स्थिर व्योम		*info;
	u8			info_length;
	स्थिर व्योम		*निजी_data;
	u8			निजी_data_len;
	काष्ठा rdma_ucm_ece	ece;
पूर्ण;

/**
 * ib_send_cm_sidr_rep - Sends a service ID resolution reply to the
 *   remote node.
 * @cm_id: Communication identअगरier associated with the received service ID
 *   resolution request.
 * @param: Service ID resolution reply inक्रमmation.
 */
पूर्णांक ib_send_cm_sidr_rep(काष्ठा ib_cm_id *cm_id,
			काष्ठा ib_cm_sidr_rep_param *param);

/**
 * ibcm_reject_msg - वापस a poपूर्णांकer to a reject message string.
 * @reason: Value वापसed in the REJECT event status field.
 */
स्थिर अक्षर *__attribute_स्थिर__ ibcm_reject_msg(पूर्णांक reason);

#पूर्ण_अगर /* IB_CM_H */
