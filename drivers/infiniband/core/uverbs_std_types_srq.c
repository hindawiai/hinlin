<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2020, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <rdma/uverbs_std_types.h>
#समावेश "rdma_core.h"
#समावेश "uverbs.h"

अटल पूर्णांक uverbs_मुक्त_srq(काष्ठा ib_uobject *uobject,
		    क्रमागत rdma_हटाओ_reason why,
		    काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_srq *srq = uobject->object;
	काष्ठा ib_uevent_object *uevent =
		container_of(uobject, काष्ठा ib_uevent_object, uobject);
	क्रमागत ib_srq_type srq_type = srq->srq_type;
	पूर्णांक ret;

	ret = ib_destroy_srq_user(srq, &attrs->driver_udata);
	अगर (ret)
		वापस ret;

	अगर (srq_type == IB_SRQT_XRC) अणु
		काष्ठा ib_usrq_object *us =
			container_of(uobject, काष्ठा ib_usrq_object,
				     uevent.uobject);

		atomic_dec(&us->uxrcd->refcnt);
	पूर्ण

	ib_uverbs_release_uevent(uevent);
	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_SRQ_CREATE)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_usrq_object *obj = container_of(
		uverbs_attr_get_uobject(attrs, UVERBS_ATTR_CREATE_SRQ_HANDLE),
		typeof(*obj), uevent.uobject);
	काष्ठा ib_pd *pd =
		uverbs_attr_get_obj(attrs, UVERBS_ATTR_CREATE_SRQ_PD_HANDLE);
	काष्ठा ib_srq_init_attr attr = अणुपूर्ण;
	काष्ठा ib_uobject *xrcd_uobj;
	काष्ठा ib_srq *srq;
	u64 user_handle;
	पूर्णांक ret;

	ret = uverbs_copy_from(&attr.attr.max_sge, attrs,
			       UVERBS_ATTR_CREATE_SRQ_MAX_SGE);
	अगर (!ret)
		ret = uverbs_copy_from(&attr.attr.max_wr, attrs,
				       UVERBS_ATTR_CREATE_SRQ_MAX_WR);
	अगर (!ret)
		ret = uverbs_copy_from(&attr.attr.srq_limit, attrs,
				       UVERBS_ATTR_CREATE_SRQ_LIMIT);
	अगर (!ret)
		ret = uverbs_copy_from(&user_handle, attrs,
				       UVERBS_ATTR_CREATE_SRQ_USER_HANDLE);
	अगर (!ret)
		ret = uverbs_get_स्थिर(&attr.srq_type, attrs,
				       UVERBS_ATTR_CREATE_SRQ_TYPE);
	अगर (ret)
		वापस ret;

	अगर (ib_srq_has_cq(attr.srq_type)) अणु
		attr.ext.cq = uverbs_attr_get_obj(attrs,
					UVERBS_ATTR_CREATE_SRQ_CQ_HANDLE);
		अगर (IS_ERR(attr.ext.cq))
			वापस PTR_ERR(attr.ext.cq);
	पूर्ण

	चयन (attr.srq_type) अणु
	हाल IB_UVERBS_SRQT_XRC:
		xrcd_uobj = uverbs_attr_get_uobject(attrs,
					UVERBS_ATTR_CREATE_SRQ_XRCD_HANDLE);
		अगर (IS_ERR(xrcd_uobj))
			वापस PTR_ERR(xrcd_uobj);

		attr.ext.xrc.xrcd = (काष्ठा ib_xrcd *)xrcd_uobj->object;
		अगर (!attr.ext.xrc.xrcd)
			वापस -EINVAL;
		obj->uxrcd = container_of(xrcd_uobj, काष्ठा ib_uxrcd_object,
					  uobject);
		atomic_inc(&obj->uxrcd->refcnt);
		अवरोध;
	हाल IB_UVERBS_SRQT_TM:
		ret = uverbs_copy_from(&attr.ext.tag_matching.max_num_tags,
				       attrs,
				       UVERBS_ATTR_CREATE_SRQ_MAX_NUM_TAGS);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल IB_UVERBS_SRQT_BASIC:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	obj->uevent.event_file = ib_uverbs_get_async_event(attrs,
					UVERBS_ATTR_CREATE_SRQ_EVENT_FD);
	INIT_LIST_HEAD(&obj->uevent.event_list);
	attr.event_handler = ib_uverbs_srq_event_handler;
	obj->uevent.uobject.user_handle = user_handle;

	srq = ib_create_srq_user(pd, &attr, obj, &attrs->driver_udata);
	अगर (IS_ERR(srq)) अणु
		ret = PTR_ERR(srq);
		जाओ err;
	पूर्ण

	obj->uevent.uobject.object = srq;
	uverbs_finalize_uobj_create(attrs, UVERBS_ATTR_CREATE_SRQ_HANDLE);

	ret = uverbs_copy_to(attrs, UVERBS_ATTR_CREATE_SRQ_RESP_MAX_WR,
			     &attr.attr.max_wr,
			     माप(attr.attr.max_wr));
	अगर (ret)
		वापस ret;

	ret = uverbs_copy_to(attrs, UVERBS_ATTR_CREATE_SRQ_RESP_MAX_SGE,
			     &attr.attr.max_sge,
			     माप(attr.attr.max_sge));
	अगर (ret)
		वापस ret;

	अगर (attr.srq_type == IB_SRQT_XRC) अणु
		ret = uverbs_copy_to(attrs,
				     UVERBS_ATTR_CREATE_SRQ_RESP_SRQ_NUM,
				     &srq->ext.xrc.srq_num,
				     माप(srq->ext.xrc.srq_num));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
err:
	अगर (obj->uevent.event_file)
		uverbs_uobject_put(&obj->uevent.event_file->uobj);
	अगर (attr.srq_type == IB_SRQT_XRC)
		atomic_dec(&obj->uxrcd->refcnt);
	वापस ret;
पूर्ण;

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_SRQ_CREATE,
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_SRQ_HANDLE,
			UVERBS_OBJECT_SRQ,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_SRQ_PD_HANDLE,
			UVERBS_OBJECT_PD,
			UVERBS_ACCESS_READ,
			UA_MANDATORY),
	UVERBS_ATTR_CONST_IN(UVERBS_ATTR_CREATE_SRQ_TYPE,
			     क्रमागत ib_uverbs_srq_type,
			     UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_CREATE_SRQ_USER_HANDLE,
			   UVERBS_ATTR_TYPE(u64),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_CREATE_SRQ_MAX_WR,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_CREATE_SRQ_MAX_SGE,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_CREATE_SRQ_LIMIT,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_SRQ_XRCD_HANDLE,
			UVERBS_OBJECT_XRCD,
			UVERBS_ACCESS_READ,
			UA_OPTIONAL),
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_SRQ_CQ_HANDLE,
			UVERBS_OBJECT_CQ,
			UVERBS_ACCESS_READ,
			UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_CREATE_SRQ_MAX_NUM_TAGS,
			   UVERBS_ATTR_TYPE(u32),
			   UA_OPTIONAL),
	UVERBS_ATTR_FD(UVERBS_ATTR_CREATE_SRQ_EVENT_FD,
		       UVERBS_OBJECT_ASYNC_EVENT,
		       UVERBS_ACCESS_READ,
		       UA_OPTIONAL),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_CREATE_SRQ_RESP_MAX_WR,
			    UVERBS_ATTR_TYPE(u32),
			    UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_CREATE_SRQ_RESP_MAX_SGE,
			    UVERBS_ATTR_TYPE(u32),
			    UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_CREATE_SRQ_RESP_SRQ_NUM,
			   UVERBS_ATTR_TYPE(u32),
			   UA_OPTIONAL),
	UVERBS_ATTR_UHW());

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_SRQ_DESTROY)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj =
		uverbs_attr_get_uobject(attrs, UVERBS_ATTR_DESTROY_SRQ_HANDLE);
	काष्ठा ib_usrq_object *obj =
		container_of(uobj, काष्ठा ib_usrq_object, uevent.uobject);
	काष्ठा ib_uverbs_destroy_srq_resp resp = अणु
		.events_reported = obj->uevent.events_reported
	पूर्ण;

	वापस uverbs_copy_to(attrs, UVERBS_ATTR_DESTROY_SRQ_RESP, &resp,
			      माप(resp));
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_SRQ_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_SRQ_HANDLE,
			UVERBS_OBJECT_SRQ,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_DESTROY_SRQ_RESP,
			    UVERBS_ATTR_TYPE(काष्ठा ib_uverbs_destroy_srq_resp),
			    UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(
	UVERBS_OBJECT_SRQ,
	UVERBS_TYPE_ALLOC_IDR_SZ(माप(काष्ठा ib_usrq_object),
				 uverbs_मुक्त_srq),
	&UVERBS_METHOD(UVERBS_METHOD_SRQ_CREATE),
	&UVERBS_METHOD(UVERBS_METHOD_SRQ_DESTROY)
);

स्थिर काष्ठा uapi_definition uverbs_def_obj_srq[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_SRQ,
				      UAPI_DEF_OBJ_NEEDS_FN(destroy_srq)),
	अणुपूर्ण
पूर्ण;
