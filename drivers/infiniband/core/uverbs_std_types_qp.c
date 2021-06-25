<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2020, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <rdma/uverbs_std_types.h>
#समावेश "rdma_core.h"
#समावेश "uverbs.h"
#समावेश "core_priv.h"

अटल पूर्णांक uverbs_मुक्त_qp(काष्ठा ib_uobject *uobject,
			  क्रमागत rdma_हटाओ_reason why,
			  काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_qp *qp = uobject->object;
	काष्ठा ib_uqp_object *uqp =
		container_of(uobject, काष्ठा ib_uqp_object, uevent.uobject);
	पूर्णांक ret;

	/*
	 * If this is a user triggered destroy then करो not allow deकाष्ठाion
	 * until the user cleans up all the mcast bindings. Unlike in other
	 * places we क्रमcibly clean up the mcast attachments क्रम !DESTROY
	 * because the mcast attaches are not ubojects and will not be
	 * destroyed by anything अन्यथा during cleanup processing.
	 */
	अगर (why == RDMA_REMOVE_DESTROY) अणु
		अगर (!list_empty(&uqp->mcast_list))
			वापस -EBUSY;
	पूर्ण अन्यथा अगर (qp == qp->real_qp) अणु
		ib_uverbs_detach_umcast(qp, uqp);
	पूर्ण

	ret = ib_destroy_qp_user(qp, &attrs->driver_udata);
	अगर (ret)
		वापस ret;

	अगर (uqp->uxrcd)
		atomic_dec(&uqp->uxrcd->refcnt);

	ib_uverbs_release_uevent(&uqp->uevent);
	वापस 0;
पूर्ण

अटल पूर्णांक check_creation_flags(क्रमागत ib_qp_type qp_type,
				u32 create_flags)
अणु
	create_flags &= ~IB_UVERBS_QP_CREATE_SQ_SIG_ALL;

	अगर (!create_flags || qp_type == IB_QPT_DRIVER)
		वापस 0;

	अगर (qp_type != IB_QPT_RAW_PACKET && qp_type != IB_QPT_UD)
		वापस -EINVAL;

	अगर ((create_flags & IB_UVERBS_QP_CREATE_SCATTER_FCS ||
	     create_flags & IB_UVERBS_QP_CREATE_CVLAN_STRIPPING) &&
	     qp_type != IB_QPT_RAW_PACKET)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम set_caps(काष्ठा ib_qp_init_attr *attr,
		     काष्ठा ib_uverbs_qp_cap *cap, bool req)
अणु
	अगर (req) अणु
		attr->cap.max_send_wr = cap->max_send_wr;
		attr->cap.max_recv_wr = cap->max_recv_wr;
		attr->cap.max_send_sge = cap->max_send_sge;
		attr->cap.max_recv_sge = cap->max_recv_sge;
		attr->cap.max_अंतरभूत_data = cap->max_अंतरभूत_data;
	पूर्ण अन्यथा अणु
		cap->max_send_wr = attr->cap.max_send_wr;
		cap->max_recv_wr = attr->cap.max_recv_wr;
		cap->max_send_sge = attr->cap.max_send_sge;
		cap->max_recv_sge = attr->cap.max_recv_sge;
		cap->max_अंतरभूत_data = attr->cap.max_अंतरभूत_data;
	पूर्ण
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_QP_CREATE)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uqp_object *obj = container_of(
		uverbs_attr_get_uobject(attrs, UVERBS_ATTR_CREATE_QP_HANDLE),
		typeof(*obj), uevent.uobject);
	काष्ठा ib_qp_init_attr attr = अणुपूर्ण;
	काष्ठा ib_uverbs_qp_cap cap = अणुपूर्ण;
	काष्ठा ib_rwq_ind_table *rwq_ind_tbl = शून्य;
	काष्ठा ib_qp *qp;
	काष्ठा ib_pd *pd = शून्य;
	काष्ठा ib_srq *srq = शून्य;
	काष्ठा ib_cq *recv_cq = शून्य;
	काष्ठा ib_cq *send_cq = शून्य;
	काष्ठा ib_xrcd *xrcd = शून्य;
	काष्ठा ib_uobject *xrcd_uobj = शून्य;
	काष्ठा ib_device *device;
	u64 user_handle;
	पूर्णांक ret;

	ret = uverbs_copy_from_or_zero(&cap, attrs,
			       UVERBS_ATTR_CREATE_QP_CAP);
	अगर (!ret)
		ret = uverbs_copy_from(&user_handle, attrs,
				       UVERBS_ATTR_CREATE_QP_USER_HANDLE);
	अगर (!ret)
		ret = uverbs_get_स्थिर(&attr.qp_type, attrs,
				       UVERBS_ATTR_CREATE_QP_TYPE);
	अगर (ret)
		वापस ret;

	चयन (attr.qp_type) अणु
	हाल IB_QPT_XRC_TGT:
		अगर (uverbs_attr_is_valid(attrs,
				UVERBS_ATTR_CREATE_QP_RECV_CQ_HANDLE) ||
		    uverbs_attr_is_valid(attrs,
				UVERBS_ATTR_CREATE_QP_SEND_CQ_HANDLE) ||
		    uverbs_attr_is_valid(attrs,
				UVERBS_ATTR_CREATE_QP_PD_HANDLE) ||
		    uverbs_attr_is_valid(attrs,
				UVERBS_ATTR_CREATE_QP_IND_TABLE_HANDLE))
			वापस -EINVAL;

		xrcd_uobj = uverbs_attr_get_uobject(attrs,
					UVERBS_ATTR_CREATE_QP_XRCD_HANDLE);
		अगर (IS_ERR(xrcd_uobj))
			वापस PTR_ERR(xrcd_uobj);

		xrcd = (काष्ठा ib_xrcd *)xrcd_uobj->object;
		अगर (!xrcd)
			वापस -EINVAL;
		device = xrcd->device;
		अवरोध;
	हाल IB_UVERBS_QPT_RAW_PACKET:
		अगर (!capable(CAP_NET_RAW))
			वापस -EPERM;
		fallthrough;
	हाल IB_UVERBS_QPT_RC:
	हाल IB_UVERBS_QPT_UC:
	हाल IB_UVERBS_QPT_UD:
	हाल IB_UVERBS_QPT_XRC_INI:
	हाल IB_UVERBS_QPT_DRIVER:
		अगर (uverbs_attr_is_valid(attrs,
					 UVERBS_ATTR_CREATE_QP_XRCD_HANDLE) ||
		   (uverbs_attr_is_valid(attrs,
					 UVERBS_ATTR_CREATE_QP_SRQ_HANDLE) &&
			attr.qp_type == IB_QPT_XRC_INI))
			वापस -EINVAL;

		pd = uverbs_attr_get_obj(attrs,
					 UVERBS_ATTR_CREATE_QP_PD_HANDLE);
		अगर (IS_ERR(pd))
			वापस PTR_ERR(pd);

		rwq_ind_tbl = uverbs_attr_get_obj(attrs,
			UVERBS_ATTR_CREATE_QP_IND_TABLE_HANDLE);
		अगर (!IS_ERR(rwq_ind_tbl)) अणु
			अगर (cap.max_recv_wr || cap.max_recv_sge ||
			    uverbs_attr_is_valid(attrs,
				UVERBS_ATTR_CREATE_QP_RECV_CQ_HANDLE) ||
			    uverbs_attr_is_valid(attrs,
					UVERBS_ATTR_CREATE_QP_SRQ_HANDLE))
				वापस -EINVAL;

			/* send_cq is optinal */
			अगर (cap.max_send_wr) अणु
				send_cq = uverbs_attr_get_obj(attrs,
					UVERBS_ATTR_CREATE_QP_SEND_CQ_HANDLE);
				अगर (IS_ERR(send_cq))
					वापस PTR_ERR(send_cq);
			पूर्ण
			attr.rwq_ind_tbl = rwq_ind_tbl;
		पूर्ण अन्यथा अणु
			send_cq = uverbs_attr_get_obj(attrs,
					UVERBS_ATTR_CREATE_QP_SEND_CQ_HANDLE);
			अगर (IS_ERR(send_cq))
				वापस PTR_ERR(send_cq);

			अगर (attr.qp_type != IB_QPT_XRC_INI) अणु
				recv_cq = uverbs_attr_get_obj(attrs,
					UVERBS_ATTR_CREATE_QP_RECV_CQ_HANDLE);
				अगर (IS_ERR(recv_cq))
					वापस PTR_ERR(recv_cq);
			पूर्ण
		पूर्ण

		device = pd->device;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = uverbs_get_flags32(&attr.create_flags, attrs,
			 UVERBS_ATTR_CREATE_QP_FLAGS,
			 IB_UVERBS_QP_CREATE_BLOCK_MULTICAST_LOOPBACK |
			 IB_UVERBS_QP_CREATE_SCATTER_FCS |
			 IB_UVERBS_QP_CREATE_CVLAN_STRIPPING |
			 IB_UVERBS_QP_CREATE_PCI_WRITE_END_PADDING |
			 IB_UVERBS_QP_CREATE_SQ_SIG_ALL);
	अगर (ret)
		वापस ret;

	ret = check_creation_flags(attr.qp_type, attr.create_flags);
	अगर (ret)
		वापस ret;

	अगर (uverbs_attr_is_valid(attrs,
			UVERBS_ATTR_CREATE_QP_SOURCE_QPN)) अणु
		ret = uverbs_copy_from(&attr.source_qpn, attrs,
				       UVERBS_ATTR_CREATE_QP_SOURCE_QPN);
		अगर (ret)
			वापस ret;
		attr.create_flags |= IB_QP_CREATE_SOURCE_QPN;
	पूर्ण

	srq = uverbs_attr_get_obj(attrs,
				  UVERBS_ATTR_CREATE_QP_SRQ_HANDLE);
	अगर (!IS_ERR(srq)) अणु
		अगर ((srq->srq_type == IB_SRQT_XRC &&
			attr.qp_type != IB_QPT_XRC_TGT) ||
		    (srq->srq_type != IB_SRQT_XRC &&
			attr.qp_type == IB_QPT_XRC_TGT))
			वापस -EINVAL;
		attr.srq = srq;
	पूर्ण

	obj->uevent.event_file = ib_uverbs_get_async_event(attrs,
					UVERBS_ATTR_CREATE_QP_EVENT_FD);
	INIT_LIST_HEAD(&obj->uevent.event_list);
	INIT_LIST_HEAD(&obj->mcast_list);
	obj->uevent.uobject.user_handle = user_handle;
	attr.event_handler = ib_uverbs_qp_event_handler;
	attr.send_cq = send_cq;
	attr.recv_cq = recv_cq;
	attr.xrcd = xrcd;
	अगर (attr.create_flags & IB_UVERBS_QP_CREATE_SQ_SIG_ALL) अणु
		/* This creation bit is uverbs one, need to mask beक्रमe
		 * calling drivers. It was added to prevent an extra user attr
		 * only क्रम that when using ioctl.
		 */
		attr.create_flags &= ~IB_UVERBS_QP_CREATE_SQ_SIG_ALL;
		attr.sq_sig_type = IB_SIGNAL_ALL_WR;
	पूर्ण अन्यथा अणु
		attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	पूर्ण

	set_caps(&attr, &cap, true);
	mutex_init(&obj->mcast_lock);

	अगर (attr.qp_type == IB_QPT_XRC_TGT)
		qp = ib_create_qp(pd, &attr);
	अन्यथा
		qp = _ib_create_qp(device, pd, &attr, &attrs->driver_udata, obj,
				   शून्य);

	अगर (IS_ERR(qp)) अणु
		ret = PTR_ERR(qp);
		जाओ err_put;
	पूर्ण

	अगर (attr.qp_type != IB_QPT_XRC_TGT) अणु
		atomic_inc(&pd->usecnt);
		अगर (attr.send_cq)
			atomic_inc(&attr.send_cq->usecnt);
		अगर (attr.recv_cq)
			atomic_inc(&attr.recv_cq->usecnt);
		अगर (attr.srq)
			atomic_inc(&attr.srq->usecnt);
		अगर (attr.rwq_ind_tbl)
			atomic_inc(&attr.rwq_ind_tbl->usecnt);
	पूर्ण अन्यथा अणु
		obj->uxrcd = container_of(xrcd_uobj, काष्ठा ib_uxrcd_object,
					  uobject);
		atomic_inc(&obj->uxrcd->refcnt);
		/* It is करोne in _ib_create_qp क्रम other QP types */
		qp->uobject = obj;
	पूर्ण

	obj->uevent.uobject.object = qp;
	uverbs_finalize_uobj_create(attrs, UVERBS_ATTR_CREATE_QP_HANDLE);

	अगर (attr.qp_type != IB_QPT_XRC_TGT) अणु
		ret = ib_create_qp_security(qp, device);
		अगर (ret)
			वापस ret;
	पूर्ण

	set_caps(&attr, &cap, false);
	ret = uverbs_copy_to_काष्ठा_or_zero(attrs,
					UVERBS_ATTR_CREATE_QP_RESP_CAP, &cap,
					माप(cap));
	अगर (ret)
		वापस ret;

	ret = uverbs_copy_to(attrs, UVERBS_ATTR_CREATE_QP_RESP_QP_NUM,
			     &qp->qp_num,
			     माप(qp->qp_num));

	वापस ret;
err_put:
	अगर (obj->uevent.event_file)
		uverbs_uobject_put(&obj->uevent.event_file->uobj);
	वापस ret;
पूर्ण;

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_QP_CREATE,
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_QP_HANDLE,
			UVERBS_OBJECT_QP,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_QP_XRCD_HANDLE,
			UVERBS_OBJECT_XRCD,
			UVERBS_ACCESS_READ,
			UA_OPTIONAL),
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_QP_PD_HANDLE,
			UVERBS_OBJECT_PD,
			UVERBS_ACCESS_READ,
			UA_OPTIONAL),
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_QP_SRQ_HANDLE,
			UVERBS_OBJECT_SRQ,
			UVERBS_ACCESS_READ,
			UA_OPTIONAL),
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_QP_SEND_CQ_HANDLE,
			UVERBS_OBJECT_CQ,
			UVERBS_ACCESS_READ,
			UA_OPTIONAL),
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_QP_RECV_CQ_HANDLE,
			UVERBS_OBJECT_CQ,
			UVERBS_ACCESS_READ,
			UA_OPTIONAL),
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_QP_IND_TABLE_HANDLE,
			UVERBS_OBJECT_RWQ_IND_TBL,
			UVERBS_ACCESS_READ,
			UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_CREATE_QP_USER_HANDLE,
			   UVERBS_ATTR_TYPE(u64),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_CREATE_QP_CAP,
			   UVERBS_ATTR_STRUCT(काष्ठा ib_uverbs_qp_cap,
					      max_अंतरभूत_data),
			   UA_MANDATORY),
	UVERBS_ATTR_CONST_IN(UVERBS_ATTR_CREATE_QP_TYPE,
			     क्रमागत ib_uverbs_qp_type,
			     UA_MANDATORY),
	UVERBS_ATTR_FLAGS_IN(UVERBS_ATTR_CREATE_QP_FLAGS,
			     क्रमागत ib_uverbs_qp_create_flags,
			     UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_CREATE_QP_SOURCE_QPN,
			   UVERBS_ATTR_TYPE(u32),
			   UA_OPTIONAL),
	UVERBS_ATTR_FD(UVERBS_ATTR_CREATE_QP_EVENT_FD,
		       UVERBS_OBJECT_ASYNC_EVENT,
		       UVERBS_ACCESS_READ,
		       UA_OPTIONAL),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_CREATE_QP_RESP_CAP,
			    UVERBS_ATTR_STRUCT(काष्ठा ib_uverbs_qp_cap,
					       max_अंतरभूत_data),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_CREATE_QP_RESP_QP_NUM,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_UHW());

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_QP_DESTROY)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj =
		uverbs_attr_get_uobject(attrs, UVERBS_ATTR_DESTROY_QP_HANDLE);
	काष्ठा ib_uqp_object *obj =
		container_of(uobj, काष्ठा ib_uqp_object, uevent.uobject);
	काष्ठा ib_uverbs_destroy_qp_resp resp = अणु
		.events_reported = obj->uevent.events_reported
	पूर्ण;

	वापस uverbs_copy_to(attrs, UVERBS_ATTR_DESTROY_QP_RESP, &resp,
			      माप(resp));
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_QP_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_QP_HANDLE,
			UVERBS_OBJECT_QP,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_DESTROY_QP_RESP,
			    UVERBS_ATTR_TYPE(काष्ठा ib_uverbs_destroy_qp_resp),
			    UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(
	UVERBS_OBJECT_QP,
	UVERBS_TYPE_ALLOC_IDR_SZ(माप(काष्ठा ib_uqp_object), uverbs_मुक्त_qp),
	&UVERBS_METHOD(UVERBS_METHOD_QP_CREATE),
	&UVERBS_METHOD(UVERBS_METHOD_QP_DESTROY));

स्थिर काष्ठा uapi_definition uverbs_def_obj_qp[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_QP,
				      UAPI_DEF_OBJ_NEEDS_FN(destroy_qp)),
	अणुपूर्ण
पूर्ण;
