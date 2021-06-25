<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2004, 2011 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004 Voltaire Corporation.  All rights reserved.
 * Copyright (c) 2019, Mellanox Technologies inc.  All rights reserved.
 */
#अगर_अघोषित CM_MSGS_H
#घोषणा CM_MSGS_H

#समावेश <rdma/ibta_vol1_c12.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_cm.h>

/*
 * Parameters to routines below should be in network-byte order, and values
 * are वापसed in network-byte order.
 */

#घोषणा IB_CM_CLASS_VERSION	2 /* IB specअगरication 1.2 */

अटल अंतरभूत क्रमागत ib_qp_type cm_req_get_qp_type(काष्ठा cm_req_msg *req_msg)
अणु
	u8 transport_type = IBA_GET(CM_REQ_TRANSPORT_SERVICE_TYPE, req_msg);
	चयन (transport_type) अणु
	हाल 0: वापस IB_QPT_RC;
	हाल 1: वापस IB_QPT_UC;
	हाल 3:
		चयन (IBA_GET(CM_REQ_EXTENDED_TRANSPORT_TYPE, req_msg)) अणु
		हाल 1: वापस IB_QPT_XRC_TGT;
		शेष: वापस 0;
		पूर्ण
	शेष: वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cm_req_set_qp_type(काष्ठा cm_req_msg *req_msg,
				      क्रमागत ib_qp_type qp_type)
अणु
	चयन (qp_type) अणु
	हाल IB_QPT_UC:
		IBA_SET(CM_REQ_TRANSPORT_SERVICE_TYPE, req_msg, 1);
		अवरोध;
	हाल IB_QPT_XRC_INI:
		IBA_SET(CM_REQ_TRANSPORT_SERVICE_TYPE, req_msg, 3);
		IBA_SET(CM_REQ_EXTENDED_TRANSPORT_TYPE, req_msg, 1);
		अवरोध;
	शेष:
		IBA_SET(CM_REQ_TRANSPORT_SERVICE_TYPE, req_msg, 0);
	पूर्ण
पूर्ण

/* Message REJected or MRAed */
क्रमागत cm_msg_response अणु
	CM_MSG_RESPONSE_REQ = 0x0,
	CM_MSG_RESPONSE_REP = 0x1,
	CM_MSG_RESPONSE_OTHER = 0x2
पूर्ण;

अटल अंतरभूत __be32 cm_rep_get_qpn(काष्ठा cm_rep_msg *rep_msg, क्रमागत ib_qp_type qp_type)
अणु
	वापस (qp_type == IB_QPT_XRC_INI) ?
		       cpu_to_be32(IBA_GET(CM_REP_LOCAL_EE_CONTEXT_NUMBER,
					   rep_msg)) :
		       cpu_to_be32(IBA_GET(CM_REP_LOCAL_QPN, rep_msg));
पूर्ण

#पूर्ण_अगर /* CM_MSGS_H */
