<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies inc.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <rdma/uverbs_std_types.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <linux/bug.h>
#समावेश <linux/file.h>
#समावेश <rdma/restrack.h>
#समावेश "rdma_core.h"
#समावेश "uverbs.h"

अटल पूर्णांक uverbs_मुक्त_ah(काष्ठा ib_uobject *uobject,
			  क्रमागत rdma_हटाओ_reason why,
			  काष्ठा uverbs_attr_bundle *attrs)
अणु
	वापस rdma_destroy_ah_user((काष्ठा ib_ah *)uobject->object,
				    RDMA_DESTROY_AH_SLEEPABLE,
				    &attrs->driver_udata);
पूर्ण

अटल पूर्णांक uverbs_मुक्त_flow(काष्ठा ib_uobject *uobject,
			    क्रमागत rdma_हटाओ_reason why,
			    काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_flow *flow = (काष्ठा ib_flow *)uobject->object;
	काष्ठा ib_uflow_object *uflow =
		container_of(uobject, काष्ठा ib_uflow_object, uobject);
	काष्ठा ib_qp *qp = flow->qp;
	पूर्णांक ret;

	ret = flow->device->ops.destroy_flow(flow);
	अगर (!ret) अणु
		अगर (qp)
			atomic_dec(&qp->usecnt);
		ib_uverbs_flow_resources_मुक्त(uflow->resources);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक uverbs_मुक्त_mw(काष्ठा ib_uobject *uobject,
			  क्रमागत rdma_हटाओ_reason why,
			  काष्ठा uverbs_attr_bundle *attrs)
अणु
	वापस uverbs_dealloc_mw((काष्ठा ib_mw *)uobject->object);
पूर्ण

अटल पूर्णांक uverbs_मुक्त_rwq_ind_tbl(काष्ठा ib_uobject *uobject,
				   क्रमागत rdma_हटाओ_reason why,
				   काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_rwq_ind_table *rwq_ind_tbl = uobject->object;
	काष्ठा ib_wq **ind_tbl = rwq_ind_tbl->ind_tbl;
	u32 table_size = (1 << rwq_ind_tbl->log_ind_tbl_size);
	पूर्णांक ret, i;

	अगर (atomic_पढ़ो(&rwq_ind_tbl->usecnt))
		वापस -EBUSY;

	ret = rwq_ind_tbl->device->ops.destroy_rwq_ind_table(rwq_ind_tbl);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < table_size; i++)
		atomic_dec(&ind_tbl[i]->usecnt);

	kमुक्त(rwq_ind_tbl);
	kमुक्त(ind_tbl);
	वापस 0;
पूर्ण

अटल पूर्णांक uverbs_मुक्त_xrcd(काष्ठा ib_uobject *uobject,
			    क्रमागत rdma_हटाओ_reason why,
			    काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_xrcd *xrcd = uobject->object;
	काष्ठा ib_uxrcd_object *uxrcd =
		container_of(uobject, काष्ठा ib_uxrcd_object, uobject);
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&uxrcd->refcnt))
		वापस -EBUSY;

	mutex_lock(&attrs->ufile->device->xrcd_tree_mutex);
	ret = ib_uverbs_dealloc_xrcd(uobject, xrcd, why, attrs);
	mutex_unlock(&attrs->ufile->device->xrcd_tree_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक uverbs_मुक्त_pd(काष्ठा ib_uobject *uobject,
			  क्रमागत rdma_हटाओ_reason why,
			  काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_pd *pd = uobject->object;

	अगर (atomic_पढ़ो(&pd->usecnt))
		वापस -EBUSY;

	वापस ib_dealloc_pd_user(pd, &attrs->driver_udata);
पूर्ण

व्योम ib_uverbs_मुक्त_event_queue(काष्ठा ib_uverbs_event_queue *event_queue)
अणु
	काष्ठा ib_uverbs_event *entry, *पंचांगp;

	spin_lock_irq(&event_queue->lock);
	/*
	 * The user must ensure that no new items are added to the event_list
	 * once is_बंदd is set.
	 */
	event_queue->is_बंदd = 1;
	spin_unlock_irq(&event_queue->lock);
	wake_up_पूर्णांकerruptible(&event_queue->poll_रुको);
	समाप्त_fasync(&event_queue->async_queue, SIGIO, POLL_IN);

	spin_lock_irq(&event_queue->lock);
	list_क्रम_each_entry_safe(entry, पंचांगp, &event_queue->event_list, list) अणु
		अगर (entry->counter)
			list_del(&entry->obj_list);
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
	spin_unlock_irq(&event_queue->lock);
पूर्ण

अटल व्योम
uverbs_completion_event_file_destroy_uobj(काष्ठा ib_uobject *uobj,
					  क्रमागत rdma_हटाओ_reason why)
अणु
	काष्ठा ib_uverbs_completion_event_file *file =
		container_of(uobj, काष्ठा ib_uverbs_completion_event_file,
			     uobj);

	ib_uverbs_मुक्त_event_queue(&file->ev_queue);
पूर्ण

पूर्णांक uverbs_destroy_def_handler(काष्ठा uverbs_attr_bundle *attrs)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(uverbs_destroy_def_handler);

DECLARE_UVERBS_NAMED_OBJECT(
	UVERBS_OBJECT_COMP_CHANNEL,
	UVERBS_TYPE_ALLOC_FD(माप(काष्ठा ib_uverbs_completion_event_file),
			     uverbs_completion_event_file_destroy_uobj,
			     &uverbs_event_fops,
			     "[infinibandevent]",
			     O_RDONLY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	UVERBS_METHOD_MW_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_MW_HANDLE,
			UVERBS_OBJECT_MW,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(UVERBS_OBJECT_MW,
			    UVERBS_TYPE_ALLOC_IDR(uverbs_मुक्त_mw),
			    &UVERBS_METHOD(UVERBS_METHOD_MW_DESTROY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	UVERBS_METHOD_AH_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_AH_HANDLE,
			UVERBS_OBJECT_AH,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(UVERBS_OBJECT_AH,
			    UVERBS_TYPE_ALLOC_IDR(uverbs_मुक्त_ah),
			    &UVERBS_METHOD(UVERBS_METHOD_AH_DESTROY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	UVERBS_METHOD_FLOW_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_FLOW_HANDLE,
			UVERBS_OBJECT_FLOW,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(
	UVERBS_OBJECT_FLOW,
	UVERBS_TYPE_ALLOC_IDR_SZ(माप(काष्ठा ib_uflow_object),
				 uverbs_मुक्त_flow),
			    &UVERBS_METHOD(UVERBS_METHOD_FLOW_DESTROY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	UVERBS_METHOD_RWQ_IND_TBL_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_RWQ_IND_TBL_HANDLE,
			UVERBS_OBJECT_RWQ_IND_TBL,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(UVERBS_OBJECT_RWQ_IND_TBL,
			    UVERBS_TYPE_ALLOC_IDR(uverbs_मुक्त_rwq_ind_tbl),
			    &UVERBS_METHOD(UVERBS_METHOD_RWQ_IND_TBL_DESTROY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	UVERBS_METHOD_XRCD_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_XRCD_HANDLE,
			UVERBS_OBJECT_XRCD,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(
	UVERBS_OBJECT_XRCD,
	UVERBS_TYPE_ALLOC_IDR_SZ(माप(काष्ठा ib_uxrcd_object),
				 uverbs_मुक्त_xrcd),
			    &UVERBS_METHOD(UVERBS_METHOD_XRCD_DESTROY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	UVERBS_METHOD_PD_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_PD_HANDLE,
			UVERBS_OBJECT_PD,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(UVERBS_OBJECT_PD,
			    UVERBS_TYPE_ALLOC_IDR(uverbs_मुक्त_pd),
			    &UVERBS_METHOD(UVERBS_METHOD_PD_DESTROY));

स्थिर काष्ठा uapi_definition uverbs_def_obj_पूर्णांकf[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_PD,
				      UAPI_DEF_OBJ_NEEDS_FN(dealloc_pd)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_COMP_CHANNEL,
				      UAPI_DEF_OBJ_NEEDS_FN(dealloc_pd)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_AH,
				      UAPI_DEF_OBJ_NEEDS_FN(destroy_ah)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_MW,
				      UAPI_DEF_OBJ_NEEDS_FN(dealloc_mw)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_FLOW,
				      UAPI_DEF_OBJ_NEEDS_FN(destroy_flow)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(
		UVERBS_OBJECT_RWQ_IND_TBL,
		UAPI_DEF_OBJ_NEEDS_FN(destroy_rwq_ind_table)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_XRCD,
				      UAPI_DEF_OBJ_NEEDS_FN(dealloc_xrcd)),
	अणुपूर्ण
पूर्ण;
