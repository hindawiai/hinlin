<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004, 2005 Voltaire Corporation.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005 Open Grid Computing, Inc. All rights reserved.
 * Copyright (c) 2005 Network Appliance, Inc. All rights reserved.
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
 *
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/sysctl.h>

#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/iw_porपंचांगap.h>
#समावेश <rdma/rdma_netlink.h>

#समावेश "iwcm.h"

MODULE_AUTHOR("Tom Tucker");
MODULE_DESCRIPTION("iWARP CM");
MODULE_LICENSE("Dual BSD/GPL");

अटल स्थिर अक्षर * स्थिर iwcm_rej_reason_strs[] = अणु
	[ECONNRESET]			= "reset by remote host",
	[ECONNREFUSED]			= "refused by remote application",
	[ETIMEDOUT]			= "setup timeout",
पूर्ण;

स्थिर अक्षर *__attribute_स्थिर__ iwcm_reject_msg(पूर्णांक reason)
अणु
	माप_प्रकार index;

	/* iWARP uses negative त्रुटि_संs */
	index = -reason;

	अगर (index < ARRAY_SIZE(iwcm_rej_reason_strs) &&
	    iwcm_rej_reason_strs[index])
		वापस iwcm_rej_reason_strs[index];
	अन्यथा
		वापस "unrecognized reason";
पूर्ण
EXPORT_SYMBOL(iwcm_reject_msg);

अटल काष्ठा rdma_nl_cbs iwcm_nl_cb_table[RDMA_NL_IWPM_NUM_OPS] = अणु
	[RDMA_NL_IWPM_REG_PID] = अणु.dump = iwpm_रेजिस्टर_pid_cbपूर्ण,
	[RDMA_NL_IWPM_ADD_MAPPING] = अणु.dump = iwpm_add_mapping_cbपूर्ण,
	[RDMA_NL_IWPM_QUERY_MAPPING] = अणु.dump = iwpm_add_and_query_mapping_cbपूर्ण,
	[RDMA_NL_IWPM_REMOTE_INFO] = अणु.dump = iwpm_remote_info_cbपूर्ण,
	[RDMA_NL_IWPM_HANDLE_ERR] = अणु.dump = iwpm_mapping_error_cbपूर्ण,
	[RDMA_NL_IWPM_MAPINFO] = अणु.dump = iwpm_mapping_info_cbपूर्ण,
	[RDMA_NL_IWPM_MAPINFO_NUM] = अणु.dump = iwpm_ack_mapping_info_cbपूर्ण,
	[RDMA_NL_IWPM_HELLO] = अणु.dump = iwpm_hello_cbपूर्ण
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *iwcm_wq;
काष्ठा iwcm_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा iwcm_id_निजी *cm_id;
	काष्ठा list_head list;
	काष्ठा iw_cm_event event;
	काष्ठा list_head मुक्त_list;
पूर्ण;

अटल अचिन्हित पूर्णांक शेष_backlog = 256;

अटल काष्ठा ctl_table_header *iwcm_ctl_table_hdr;
अटल काष्ठा ctl_table iwcm_ctl_table[] = अणु
	अणु
		.procname	= "default_backlog",
		.data		= &शेष_backlog,
		.maxlen		= माप(शेष_backlog),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * The following services provide a mechanism क्रम pre-allocating iwcm_work
 * elements.  The design pre-allocates them  based on the cm_id type:
 *	LISTENING IDS: 	Get enough elements pपुनः_स्मृतिated to handle the
 *			listen backlog.
 *	ACTIVE IDS:	4: CONNECT_REPLY, ESTABLISHED, DISCONNECT, CLOSE
 *	PASSIVE IDS:	3: ESTABLISHED, DISCONNECT, CLOSE
 *
 * Allocating them in connect and listen aव्योमs having to deal
 * with allocation failures on the event upcall from the provider (which
 * is called in the पूर्णांकerrupt context).
 *
 * One exception is when creating the cm_id क्रम incoming connection requests.
 * There are two हालs:
 * 1) in the event upcall, cm_event_handler(), क्रम a listening cm_id.  If
 *    the backlog is exceeded, then no more connection request events will
 *    be processed.  cm_event_handler() वापसs -ENOMEM in this हाल.  Its up
 *    to the provider to reject the connection request.
 * 2) in the connection request workqueue handler, cm_conn_req_handler().
 *    If work elements cannot be allocated क्रम the new connect request cm_id,
 *    then IWCM will call the provider reject method.  This is ok since
 *    cm_conn_req_handler() runs in the workqueue thपढ़ो context.
 */

अटल काष्ठा iwcm_work *get_work(काष्ठा iwcm_id_निजी *cm_id_priv)
अणु
	काष्ठा iwcm_work *work;

	अगर (list_empty(&cm_id_priv->work_मुक्त_list))
		वापस शून्य;
	work = list_entry(cm_id_priv->work_मुक्त_list.next, काष्ठा iwcm_work,
			  मुक्त_list);
	list_del_init(&work->मुक्त_list);
	वापस work;
पूर्ण

अटल व्योम put_work(काष्ठा iwcm_work *work)
अणु
	list_add(&work->मुक्त_list, &work->cm_id->work_मुक्त_list);
पूर्ण

अटल व्योम dealloc_work_entries(काष्ठा iwcm_id_निजी *cm_id_priv)
अणु
	काष्ठा list_head *e, *पंचांगp;

	list_क्रम_each_safe(e, पंचांगp, &cm_id_priv->work_मुक्त_list) अणु
		list_del(e);
		kमुक्त(list_entry(e, काष्ठा iwcm_work, मुक्त_list));
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_work_entries(काष्ठा iwcm_id_निजी *cm_id_priv, पूर्णांक count)
अणु
	काष्ठा iwcm_work *work;

	BUG_ON(!list_empty(&cm_id_priv->work_मुक्त_list));
	जबतक (count--) अणु
		work = kदो_स्मृति(माप(काष्ठा iwcm_work), GFP_KERNEL);
		अगर (!work) अणु
			dealloc_work_entries(cm_id_priv);
			वापस -ENOMEM;
		पूर्ण
		work->cm_id = cm_id_priv;
		INIT_LIST_HEAD(&work->list);
		put_work(work);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Save निजी data from incoming connection requests to
 * iw_cm_event, so the low level driver करोesn't have to. Adjust
 * the event ptr to poपूर्णांक to the local copy.
 */
अटल पूर्णांक copy_निजी_data(काष्ठा iw_cm_event *event)
अणु
	व्योम *p;

	p = kmemdup(event->निजी_data, event->निजी_data_len, GFP_ATOMIC);
	अगर (!p)
		वापस -ENOMEM;
	event->निजी_data = p;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_cm_id(काष्ठा iwcm_id_निजी *cm_id_priv)
अणु
	dealloc_work_entries(cm_id_priv);
	kमुक्त(cm_id_priv);
पूर्ण

/*
 * Release a reference on cm_id. If the last reference is being
 * released, मुक्त the cm_id and वापस 1.
 */
अटल पूर्णांक iwcm_deref_id(काष्ठा iwcm_id_निजी *cm_id_priv)
अणु
	BUG_ON(atomic_पढ़ो(&cm_id_priv->refcount)==0);
	अगर (atomic_dec_and_test(&cm_id_priv->refcount)) अणु
		BUG_ON(!list_empty(&cm_id_priv->work_list));
		मुक्त_cm_id(cm_id_priv);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम add_ref(काष्ठा iw_cm_id *cm_id)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;
	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);
	atomic_inc(&cm_id_priv->refcount);
पूर्ण

अटल व्योम rem_ref(काष्ठा iw_cm_id *cm_id)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);

	(व्योम)iwcm_deref_id(cm_id_priv);
पूर्ण

अटल पूर्णांक cm_event_handler(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_event *event);

काष्ठा iw_cm_id *iw_create_cm_id(काष्ठा ib_device *device,
				 iw_cm_handler cm_handler,
				 व्योम *context)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;

	cm_id_priv = kzalloc(माप(*cm_id_priv), GFP_KERNEL);
	अगर (!cm_id_priv)
		वापस ERR_PTR(-ENOMEM);

	cm_id_priv->state = IW_CM_STATE_IDLE;
	cm_id_priv->id.device = device;
	cm_id_priv->id.cm_handler = cm_handler;
	cm_id_priv->id.context = context;
	cm_id_priv->id.event_handler = cm_event_handler;
	cm_id_priv->id.add_ref = add_ref;
	cm_id_priv->id.rem_ref = rem_ref;
	spin_lock_init(&cm_id_priv->lock);
	atomic_set(&cm_id_priv->refcount, 1);
	init_रुकोqueue_head(&cm_id_priv->connect_रुको);
	init_completion(&cm_id_priv->destroy_comp);
	INIT_LIST_HEAD(&cm_id_priv->work_list);
	INIT_LIST_HEAD(&cm_id_priv->work_मुक्त_list);

	वापस &cm_id_priv->id;
पूर्ण
EXPORT_SYMBOL(iw_create_cm_id);


अटल पूर्णांक iwcm_modअगरy_qp_err(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp_attr qp_attr;

	अगर (!qp)
		वापस -EINVAL;

	qp_attr.qp_state = IB_QPS_ERR;
	वापस ib_modअगरy_qp(qp, &qp_attr, IB_QP_STATE);
पूर्ण

/*
 * This is really the RDMAC CLOSING state. It is most similar to the
 * IB SQD QP state.
 */
अटल पूर्णांक iwcm_modअगरy_qp_sqd(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp_attr qp_attr;

	BUG_ON(qp == शून्य);
	qp_attr.qp_state = IB_QPS_SQD;
	वापस ib_modअगरy_qp(qp, &qp_attr, IB_QP_STATE);
पूर्ण

/*
 * CM_ID <-- CLOSING
 *
 * Block अगर a passive or active connection is currently being processed. Then
 * process the event as follows:
 * - If we are ESTABLISHED, move to CLOSING and modअगरy the QP state
 *   based on the abrupt flag
 * - If the connection is alपढ़ोy in the CLOSING or IDLE state, the peer is
 *   disconnecting concurrently with us and we've alपढ़ोy seen the
 *   DISCONNECT event -- ignore the request and वापस 0
 * - Disconnect on a listening endpoपूर्णांक वापसs -EINVAL
 */
पूर्णांक iw_cm_disconnect(काष्ठा iw_cm_id *cm_id, पूर्णांक abrupt)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	काष्ठा ib_qp *qp = शून्य;

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);
	/* Wait अगर we're currently in a connect or accept करोwncall */
	रुको_event(cm_id_priv->connect_रुको,
		   !test_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags));

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	चयन (cm_id_priv->state) अणु
	हाल IW_CM_STATE_ESTABLISHED:
		cm_id_priv->state = IW_CM_STATE_CLOSING;

		/* QP could be <nul> क्रम user-mode client */
		अगर (cm_id_priv->qp)
			qp = cm_id_priv->qp;
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	हाल IW_CM_STATE_LISTEN:
		ret = -EINVAL;
		अवरोध;
	हाल IW_CM_STATE_CLOSING:
		/* remote peer बंदd first */
	हाल IW_CM_STATE_IDLE:
		/* accept or connect वापसed !0 */
		अवरोध;
	हाल IW_CM_STATE_CONN_RECV:
		/*
		 * App called disconnect beक्रमe/without calling accept after
		 * connect_request event delivered.
		 */
		अवरोध;
	हाल IW_CM_STATE_CONN_SENT:
		/* Can only get here अगर रुको above fails */
	शेष:
		BUG();
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	अगर (qp) अणु
		अगर (abrupt)
			ret = iwcm_modअगरy_qp_err(qp);
		अन्यथा
			ret = iwcm_modअगरy_qp_sqd(qp);

		/*
		 * If both sides are disconnecting the QP could
		 * alपढ़ोy be in ERR or SQD states
		 */
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iw_cm_disconnect);

/*
 * CM_ID <-- DESTROYING
 *
 * Clean up all resources associated with the connection and release
 * the initial reference taken by iw_create_cm_id.
 */
अटल व्योम destroy_cm_id(काष्ठा iw_cm_id *cm_id)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;
	काष्ठा ib_qp *qp;
	अचिन्हित दीर्घ flags;

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);
	/*
	 * Wait अगर we're currently in a connect or accept करोwncall. A
	 * listening endpoपूर्णांक should never block here.
	 */
	रुको_event(cm_id_priv->connect_रुको,
		   !test_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags));

	/*
	 * Since we're deleting the cm_id, drop any events that
	 * might arrive beक्रमe the last dereference.
	 */
	set_bit(IWCM_F_DROP_EVENTS, &cm_id_priv->flags);

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	qp = cm_id_priv->qp;
	cm_id_priv->qp = शून्य;

	चयन (cm_id_priv->state) अणु
	हाल IW_CM_STATE_LISTEN:
		cm_id_priv->state = IW_CM_STATE_DESTROYING;
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		/* destroy the listening endpoपूर्णांक */
		cm_id->device->ops.iw_destroy_listen(cm_id);
		spin_lock_irqsave(&cm_id_priv->lock, flags);
		अवरोध;
	हाल IW_CM_STATE_ESTABLISHED:
		cm_id_priv->state = IW_CM_STATE_DESTROYING;
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		/* Abrupt बंद of the connection */
		(व्योम)iwcm_modअगरy_qp_err(qp);
		spin_lock_irqsave(&cm_id_priv->lock, flags);
		अवरोध;
	हाल IW_CM_STATE_IDLE:
	हाल IW_CM_STATE_CLOSING:
		cm_id_priv->state = IW_CM_STATE_DESTROYING;
		अवरोध;
	हाल IW_CM_STATE_CONN_RECV:
		/*
		 * App called destroy beक्रमe/without calling accept after
		 * receiving connection request event notअगरication or
		 * वापसed non zero from the event callback function.
		 * In either हाल, must tell the provider to reject.
		 */
		cm_id_priv->state = IW_CM_STATE_DESTROYING;
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		cm_id->device->ops.iw_reject(cm_id, शून्य, 0);
		spin_lock_irqsave(&cm_id_priv->lock, flags);
		अवरोध;
	हाल IW_CM_STATE_CONN_SENT:
	हाल IW_CM_STATE_DESTROYING:
	शेष:
		BUG();
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	अगर (qp)
		cm_id_priv->id.device->ops.iw_rem_ref(qp);

	अगर (cm_id->mapped) अणु
		iwpm_हटाओ_mapinfo(&cm_id->local_addr, &cm_id->m_local_addr);
		iwpm_हटाओ_mapping(&cm_id->local_addr, RDMA_NL_IWCM);
	पूर्ण

	(व्योम)iwcm_deref_id(cm_id_priv);
पूर्ण

/*
 * This function is only called by the application thपढ़ो and cannot
 * be called by the event thपढ़ो. The function will रुको क्रम all
 * references to be released on the cm_id and then kमुक्त the cm_id
 * object.
 */
व्योम iw_destroy_cm_id(काष्ठा iw_cm_id *cm_id)
अणु
	destroy_cm_id(cm_id);
पूर्ण
EXPORT_SYMBOL(iw_destroy_cm_id);

/**
 * iw_cm_check_wildcard - If IP address is 0 then use original
 * @pm_addr: sockaddr containing the ip to check क्रम wildcard
 * @cm_addr: sockaddr containing the actual IP address
 * @cm_outaddr: sockaddr to set IP addr which leaving port
 *
 *  Checks the pm_addr क्रम wildcard and then sets cm_outaddr's
 *  IP to the actual (cm_addr).
 */
अटल व्योम iw_cm_check_wildcard(काष्ठा sockaddr_storage *pm_addr,
				 काष्ठा sockaddr_storage *cm_addr,
				 काष्ठा sockaddr_storage *cm_outaddr)
अणु
	अगर (pm_addr->ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *pm4_addr = (काष्ठा sockaddr_in *)pm_addr;

		अगर (pm4_addr->sin_addr.s_addr == htonl(INADDR_ANY)) अणु
			काष्ठा sockaddr_in *cm4_addr =
				(काष्ठा sockaddr_in *)cm_addr;
			काष्ठा sockaddr_in *cm4_outaddr =
				(काष्ठा sockaddr_in *)cm_outaddr;

			cm4_outaddr->sin_addr = cm4_addr->sin_addr;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *pm6_addr = (काष्ठा sockaddr_in6 *)pm_addr;

		अगर (ipv6_addr_type(&pm6_addr->sin6_addr) == IPV6_ADDR_ANY) अणु
			काष्ठा sockaddr_in6 *cm6_addr =
				(काष्ठा sockaddr_in6 *)cm_addr;
			काष्ठा sockaddr_in6 *cm6_outaddr =
				(काष्ठा sockaddr_in6 *)cm_outaddr;

			cm6_outaddr->sin6_addr = cm6_addr->sin6_addr;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * iw_cm_map - Use porपंचांगapper to map the ports
 * @cm_id: connection manager poपूर्णांकer
 * @active: Indicates the active side when true
 * वापसs nonzero क्रम error only अगर iwpm_create_mapinfo() fails
 *
 * Tries to add a mapping क्रम a port using the Porपंचांगapper. If
 * successful in mapping the IP/Port it will check the remote
 * mapped IP address क्रम a wildcard IP address and replace the
 * zero IP address with the remote_addr.
 */
अटल पूर्णांक iw_cm_map(काष्ठा iw_cm_id *cm_id, bool active)
अणु
	स्थिर अक्षर *devname = dev_name(&cm_id->device->dev);
	स्थिर अक्षर *अगरname = cm_id->device->iw_अगरname;
	काष्ठा iwpm_dev_data pm_reg_msg = अणुपूर्ण;
	काष्ठा iwpm_sa_data pm_msg;
	पूर्णांक status;

	अगर (म_माप(devname) >= माप(pm_reg_msg.dev_name) ||
	    म_माप(अगरname) >= माप(pm_reg_msg.अगर_name))
		वापस -EINVAL;

	cm_id->m_local_addr = cm_id->local_addr;
	cm_id->m_remote_addr = cm_id->remote_addr;

	म_नकल(pm_reg_msg.dev_name, devname);
	म_नकल(pm_reg_msg.अगर_name, अगरname);

	अगर (iwpm_रेजिस्टर_pid(&pm_reg_msg, RDMA_NL_IWCM) ||
	    !iwpm_valid_pid())
		वापस 0;

	cm_id->mapped = true;
	pm_msg.loc_addr = cm_id->local_addr;
	pm_msg.rem_addr = cm_id->remote_addr;
	pm_msg.flags = (cm_id->device->iw_driver_flags & IW_F_NO_PORT_MAP) ?
		       IWPM_FLAGS_NO_PORT_MAP : 0;
	अगर (active)
		status = iwpm_add_and_query_mapping(&pm_msg,
						    RDMA_NL_IWCM);
	अन्यथा
		status = iwpm_add_mapping(&pm_msg, RDMA_NL_IWCM);

	अगर (!status) अणु
		cm_id->m_local_addr = pm_msg.mapped_loc_addr;
		अगर (active) अणु
			cm_id->m_remote_addr = pm_msg.mapped_rem_addr;
			iw_cm_check_wildcard(&pm_msg.mapped_rem_addr,
					     &cm_id->remote_addr,
					     &cm_id->m_remote_addr);
		पूर्ण
	पूर्ण

	वापस iwpm_create_mapinfo(&cm_id->local_addr,
				   &cm_id->m_local_addr,
				   RDMA_NL_IWCM, pm_msg.flags);
पूर्ण

/*
 * CM_ID <-- LISTEN
 *
 * Start listening क्रम connect requests. Generates one CONNECT_REQUEST
 * event क्रम each inbound connect request.
 */
पूर्णांक iw_cm_listen(काष्ठा iw_cm_id *cm_id, पूर्णांक backlog)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);

	अगर (!backlog)
		backlog = शेष_backlog;

	ret = alloc_work_entries(cm_id_priv, backlog);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	चयन (cm_id_priv->state) अणु
	हाल IW_CM_STATE_IDLE:
		cm_id_priv->state = IW_CM_STATE_LISTEN;
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		ret = iw_cm_map(cm_id, false);
		अगर (!ret)
			ret = cm_id->device->ops.iw_create_listen(cm_id,
								  backlog);
		अगर (ret)
			cm_id_priv->state = IW_CM_STATE_IDLE;
		spin_lock_irqsave(&cm_id_priv->lock, flags);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iw_cm_listen);

/*
 * CM_ID <-- IDLE
 *
 * Rejects an inbound connection request. No events are generated.
 */
पूर्णांक iw_cm_reject(काष्ठा iw_cm_id *cm_id,
		 स्थिर व्योम *निजी_data,
		 u8 निजी_data_len)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);
	set_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	अगर (cm_id_priv->state != IW_CM_STATE_CONN_RECV) अणु
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		clear_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
		wake_up_all(&cm_id_priv->connect_रुको);
		वापस -EINVAL;
	पूर्ण
	cm_id_priv->state = IW_CM_STATE_IDLE;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	ret = cm_id->device->ops.iw_reject(cm_id, निजी_data,
					  निजी_data_len);

	clear_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
	wake_up_all(&cm_id_priv->connect_रुको);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iw_cm_reject);

/*
 * CM_ID <-- ESTABLISHED
 *
 * Accepts an inbound connection request and generates an ESTABLISHED
 * event. Callers of iw_cm_disconnect and iw_destroy_cm_id will block
 * until the ESTABLISHED event is received from the provider.
 */
पूर्णांक iw_cm_accept(काष्ठा iw_cm_id *cm_id,
		 काष्ठा iw_cm_conn_param *iw_param)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;
	काष्ठा ib_qp *qp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);
	set_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	अगर (cm_id_priv->state != IW_CM_STATE_CONN_RECV) अणु
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		clear_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
		wake_up_all(&cm_id_priv->connect_रुको);
		वापस -EINVAL;
	पूर्ण
	/* Get the ib_qp given the QPN */
	qp = cm_id->device->ops.iw_get_qp(cm_id->device, iw_param->qpn);
	अगर (!qp) अणु
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		clear_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
		wake_up_all(&cm_id_priv->connect_रुको);
		वापस -EINVAL;
	पूर्ण
	cm_id->device->ops.iw_add_ref(qp);
	cm_id_priv->qp = qp;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	ret = cm_id->device->ops.iw_accept(cm_id, iw_param);
	अगर (ret) अणु
		/* An error on accept precludes provider events */
		BUG_ON(cm_id_priv->state != IW_CM_STATE_CONN_RECV);
		cm_id_priv->state = IW_CM_STATE_IDLE;
		spin_lock_irqsave(&cm_id_priv->lock, flags);
		qp = cm_id_priv->qp;
		cm_id_priv->qp = शून्य;
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		अगर (qp)
			cm_id->device->ops.iw_rem_ref(qp);
		clear_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
		wake_up_all(&cm_id_priv->connect_रुको);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iw_cm_accept);

/*
 * Active Side: CM_ID <-- CONN_SENT
 *
 * If successful, results in the generation of a CONNECT_REPLY
 * event. iw_cm_disconnect and iw_cm_destroy will block until the
 * CONNECT_REPLY event is received from the provider.
 */
पूर्णांक iw_cm_connect(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *iw_param)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा ib_qp *qp = शून्य;

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);

	ret = alloc_work_entries(cm_id_priv, 4);
	अगर (ret)
		वापस ret;

	set_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
	spin_lock_irqsave(&cm_id_priv->lock, flags);

	अगर (cm_id_priv->state != IW_CM_STATE_IDLE) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Get the ib_qp given the QPN */
	qp = cm_id->device->ops.iw_get_qp(cm_id->device, iw_param->qpn);
	अगर (!qp) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	cm_id->device->ops.iw_add_ref(qp);
	cm_id_priv->qp = qp;
	cm_id_priv->state = IW_CM_STATE_CONN_SENT;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	ret = iw_cm_map(cm_id, true);
	अगर (!ret)
		ret = cm_id->device->ops.iw_connect(cm_id, iw_param);
	अगर (!ret)
		वापस 0;	/* success */

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	qp = cm_id_priv->qp;
	cm_id_priv->qp = शून्य;
	cm_id_priv->state = IW_CM_STATE_IDLE;
err:
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	अगर (qp)
		cm_id->device->ops.iw_rem_ref(qp);
	clear_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
	wake_up_all(&cm_id_priv->connect_रुको);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(iw_cm_connect);

/*
 * Passive Side: new CM_ID <-- CONN_RECV
 *
 * Handles an inbound connect request. The function creates a new
 * iw_cm_id to represent the new connection and inherits the client
 * callback function and other attributes from the listening parent.
 *
 * The work item contains a poपूर्णांकer to the listen_cm_id and the event. The
 * listen_cm_id contains the client cm_handler, context and
 * device. These are copied when the device is cloned. The event
 * contains the new four tuple.
 *
 * An error on the child should not affect the parent, so this
 * function करोes not वापस a value.
 */
अटल व्योम cm_conn_req_handler(काष्ठा iwcm_id_निजी *listen_id_priv,
				काष्ठा iw_cm_event *iw_event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा iw_cm_id *cm_id;
	काष्ठा iwcm_id_निजी *cm_id_priv;
	पूर्णांक ret;

	/*
	 * The provider should never generate a connection request
	 * event with a bad status.
	 */
	BUG_ON(iw_event->status);

	cm_id = iw_create_cm_id(listen_id_priv->id.device,
				listen_id_priv->id.cm_handler,
				listen_id_priv->id.context);
	/* If the cm_id could not be created, ignore the request */
	अगर (IS_ERR(cm_id))
		जाओ out;

	cm_id->provider_data = iw_event->provider_data;
	cm_id->m_local_addr = iw_event->local_addr;
	cm_id->m_remote_addr = iw_event->remote_addr;
	cm_id->local_addr = listen_id_priv->id.local_addr;

	ret = iwpm_get_remote_info(&listen_id_priv->id.m_local_addr,
				   &iw_event->remote_addr,
				   &cm_id->remote_addr,
				   RDMA_NL_IWCM);
	अगर (ret) अणु
		cm_id->remote_addr = iw_event->remote_addr;
	पूर्ण अन्यथा अणु
		iw_cm_check_wildcard(&listen_id_priv->id.m_local_addr,
				     &iw_event->local_addr,
				     &cm_id->local_addr);
		iw_event->local_addr = cm_id->local_addr;
		iw_event->remote_addr = cm_id->remote_addr;
	पूर्ण

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);
	cm_id_priv->state = IW_CM_STATE_CONN_RECV;

	/*
	 * We could be destroying the listening id. If so, ignore this
	 * upcall.
	 */
	spin_lock_irqsave(&listen_id_priv->lock, flags);
	अगर (listen_id_priv->state != IW_CM_STATE_LISTEN) अणु
		spin_unlock_irqrestore(&listen_id_priv->lock, flags);
		iw_cm_reject(cm_id, शून्य, 0);
		iw_destroy_cm_id(cm_id);
		जाओ out;
	पूर्ण
	spin_unlock_irqrestore(&listen_id_priv->lock, flags);

	ret = alloc_work_entries(cm_id_priv, 3);
	अगर (ret) अणु
		iw_cm_reject(cm_id, शून्य, 0);
		iw_destroy_cm_id(cm_id);
		जाओ out;
	पूर्ण

	/* Call the client CM handler */
	ret = cm_id->cm_handler(cm_id, iw_event);
	अगर (ret) अणु
		iw_cm_reject(cm_id, शून्य, 0);
		iw_destroy_cm_id(cm_id);
	पूर्ण

out:
	अगर (iw_event->निजी_data_len)
		kमुक्त(iw_event->निजी_data);
पूर्ण

/*
 * Passive Side: CM_ID <-- ESTABLISHED
 *
 * The provider generated an ESTABLISHED event which means that
 * the MPA negotion has completed successfully and we are now in MPA
 * FPDU mode.
 *
 * This event can only be received in the CONN_RECV state. If the
 * remote peer बंदd, the ESTABLISHED event would be received followed
 * by the CLOSE event. If the app बंदs, it will block until we wake
 * it up after processing this event.
 */
अटल पूर्णांक cm_conn_est_handler(काष्ठा iwcm_id_निजी *cm_id_priv,
			       काष्ठा iw_cm_event *iw_event)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);

	/*
	 * We clear the CONNECT_WAIT bit here to allow the callback
	 * function to call iw_cm_disconnect. Calling iw_destroy_cm_id
	 * from a callback handler is not allowed.
	 */
	clear_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
	BUG_ON(cm_id_priv->state != IW_CM_STATE_CONN_RECV);
	cm_id_priv->state = IW_CM_STATE_ESTABLISHED;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	ret = cm_id_priv->id.cm_handler(&cm_id_priv->id, iw_event);
	wake_up_all(&cm_id_priv->connect_रुको);

	वापस ret;
पूर्ण

/*
 * Active Side: CM_ID <-- ESTABLISHED
 *
 * The app has called connect and is रुकोing क्रम the established event to
 * post it's requests to the server. This event will wake up anyone
 * blocked in iw_cm_disconnect or iw_destroy_id.
 */
अटल पूर्णांक cm_conn_rep_handler(काष्ठा iwcm_id_निजी *cm_id_priv,
			       काष्ठा iw_cm_event *iw_event)
अणु
	काष्ठा ib_qp *qp = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	/*
	 * Clear the connect रुको bit so a callback function calling
	 * iw_cm_disconnect will not रुको and deadlock this thपढ़ो
	 */
	clear_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
	BUG_ON(cm_id_priv->state != IW_CM_STATE_CONN_SENT);
	अगर (iw_event->status == 0) अणु
		cm_id_priv->id.m_local_addr = iw_event->local_addr;
		cm_id_priv->id.m_remote_addr = iw_event->remote_addr;
		iw_event->local_addr = cm_id_priv->id.local_addr;
		iw_event->remote_addr = cm_id_priv->id.remote_addr;
		cm_id_priv->state = IW_CM_STATE_ESTABLISHED;
	पूर्ण अन्यथा अणु
		/* REJECTED or RESET */
		qp = cm_id_priv->qp;
		cm_id_priv->qp = शून्य;
		cm_id_priv->state = IW_CM_STATE_IDLE;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	अगर (qp)
		cm_id_priv->id.device->ops.iw_rem_ref(qp);
	ret = cm_id_priv->id.cm_handler(&cm_id_priv->id, iw_event);

	अगर (iw_event->निजी_data_len)
		kमुक्त(iw_event->निजी_data);

	/* Wake up रुकोers on connect complete */
	wake_up_all(&cm_id_priv->connect_रुको);

	वापस ret;
पूर्ण

/*
 * CM_ID <-- CLOSING
 *
 * If in the ESTABLISHED state, move to CLOSING.
 */
अटल व्योम cm_disconnect_handler(काष्ठा iwcm_id_निजी *cm_id_priv,
				  काष्ठा iw_cm_event *iw_event)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	अगर (cm_id_priv->state == IW_CM_STATE_ESTABLISHED)
		cm_id_priv->state = IW_CM_STATE_CLOSING;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
पूर्ण

/*
 * CM_ID <-- IDLE
 *
 * If in the ESTBLISHED or CLOSING states, the QP will have have been
 * moved by the provider to the ERR state. Disassociate the CM_ID from
 * the QP,  move to IDLE, and हटाओ the 'connected' reference.
 *
 * If in some other state, the cm_id was destroyed asynchronously.
 * This is the last reference that will result in waking up
 * the app thपढ़ो blocked in iw_destroy_cm_id.
 */
अटल पूर्णांक cm_बंद_handler(काष्ठा iwcm_id_निजी *cm_id_priv,
				  काष्ठा iw_cm_event *iw_event)
अणु
	काष्ठा ib_qp *qp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0, notअगरy_event = 0;
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	qp = cm_id_priv->qp;
	cm_id_priv->qp = शून्य;

	चयन (cm_id_priv->state) अणु
	हाल IW_CM_STATE_ESTABLISHED:
	हाल IW_CM_STATE_CLOSING:
		cm_id_priv->state = IW_CM_STATE_IDLE;
		notअगरy_event = 1;
		अवरोध;
	हाल IW_CM_STATE_DESTROYING:
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	अगर (qp)
		cm_id_priv->id.device->ops.iw_rem_ref(qp);
	अगर (notअगरy_event)
		ret = cm_id_priv->id.cm_handler(&cm_id_priv->id, iw_event);
	वापस ret;
पूर्ण

अटल पूर्णांक process_event(काष्ठा iwcm_id_निजी *cm_id_priv,
			 काष्ठा iw_cm_event *iw_event)
अणु
	पूर्णांक ret = 0;

	चयन (iw_event->event) अणु
	हाल IW_CM_EVENT_CONNECT_REQUEST:
		cm_conn_req_handler(cm_id_priv, iw_event);
		अवरोध;
	हाल IW_CM_EVENT_CONNECT_REPLY:
		ret = cm_conn_rep_handler(cm_id_priv, iw_event);
		अवरोध;
	हाल IW_CM_EVENT_ESTABLISHED:
		ret = cm_conn_est_handler(cm_id_priv, iw_event);
		अवरोध;
	हाल IW_CM_EVENT_DISCONNECT:
		cm_disconnect_handler(cm_id_priv, iw_event);
		अवरोध;
	हाल IW_CM_EVENT_CLOSE:
		ret = cm_बंद_handler(cm_id_priv, iw_event);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Process events on the work_list क्रम the cm_id. If the callback
 * function requests that the cm_id be deleted, a flag is set in the
 * cm_id flags to indicate that when the last reference is
 * हटाओd, the cm_id is to be destroyed. This is necessary to
 * distinguish between an object that will be destroyed by the app
 * thपढ़ो asleep on the destroy_comp list vs. an object destroyed
 * here synchronously when the last reference is हटाओd.
 */
अटल व्योम cm_work_handler(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा iwcm_work *work = container_of(_work, काष्ठा iwcm_work, work);
	काष्ठा iw_cm_event levent;
	काष्ठा iwcm_id_निजी *cm_id_priv = work->cm_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक empty;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	empty = list_empty(&cm_id_priv->work_list);
	जबतक (!empty) अणु
		work = list_entry(cm_id_priv->work_list.next,
				  काष्ठा iwcm_work, list);
		list_del_init(&work->list);
		empty = list_empty(&cm_id_priv->work_list);
		levent = work->event;
		put_work(work);
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);

		अगर (!test_bit(IWCM_F_DROP_EVENTS, &cm_id_priv->flags)) अणु
			ret = process_event(cm_id_priv, &levent);
			अगर (ret)
				destroy_cm_id(&cm_id_priv->id);
		पूर्ण अन्यथा
			pr_debug("dropping event %d\n", levent.event);
		अगर (iwcm_deref_id(cm_id_priv))
			वापस;
		अगर (empty)
			वापस;
		spin_lock_irqsave(&cm_id_priv->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
पूर्ण

/*
 * This function is called on पूर्णांकerrupt context. Schedule events on
 * the iwcm_wq thपढ़ो to allow callback functions to करोwncall पूर्णांकo
 * the CM and/or block.  Events are queued to a per-CM_ID
 * work_list. If this is the first event on the work_list, the work
 * element is also queued on the iwcm_wq thपढ़ो.
 *
 * Each event holds a reference on the cm_id. Until the last posted
 * event has been delivered and processed, the cm_id cannot be
 * deleted.
 *
 * Returns:
 * 	      0	- the event was handled.
 *	-ENOMEM	- the event was not handled due to lack of resources.
 */
अटल पूर्णांक cm_event_handler(काष्ठा iw_cm_id *cm_id,
			     काष्ठा iw_cm_event *iw_event)
अणु
	काष्ठा iwcm_work *work;
	काष्ठा iwcm_id_निजी *cm_id_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	work = get_work(cm_id_priv);
	अगर (!work) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_WORK(&work->work, cm_work_handler);
	work->cm_id = cm_id_priv;
	work->event = *iw_event;

	अगर ((work->event.event == IW_CM_EVENT_CONNECT_REQUEST ||
	     work->event.event == IW_CM_EVENT_CONNECT_REPLY) &&
	    work->event.निजी_data_len) अणु
		ret = copy_निजी_data(&work->event);
		अगर (ret) अणु
			put_work(work);
			जाओ out;
		पूर्ण
	पूर्ण

	atomic_inc(&cm_id_priv->refcount);
	अगर (list_empty(&cm_id_priv->work_list)) अणु
		list_add_tail(&work->list, &cm_id_priv->work_list);
		queue_work(iwcm_wq, &work->work);
	पूर्ण अन्यथा
		list_add_tail(&work->list, &cm_id_priv->work_list);
out:
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक iwcm_init_qp_init_attr(काष्ठा iwcm_id_निजी *cm_id_priv,
				  काष्ठा ib_qp_attr *qp_attr,
				  पूर्णांक *qp_attr_mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	चयन (cm_id_priv->state) अणु
	हाल IW_CM_STATE_IDLE:
	हाल IW_CM_STATE_CONN_SENT:
	हाल IW_CM_STATE_CONN_RECV:
	हाल IW_CM_STATE_ESTABLISHED:
		*qp_attr_mask = IB_QP_STATE | IB_QP_ACCESS_FLAGS;
		qp_attr->qp_access_flags = IB_ACCESS_REMOTE_WRITE|
					   IB_ACCESS_REMOTE_READ;
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक iwcm_init_qp_rts_attr(काष्ठा iwcm_id_निजी *cm_id_priv,
				  काष्ठा ib_qp_attr *qp_attr,
				  पूर्णांक *qp_attr_mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	चयन (cm_id_priv->state) अणु
	हाल IW_CM_STATE_IDLE:
	हाल IW_CM_STATE_CONN_SENT:
	हाल IW_CM_STATE_CONN_RECV:
	हाल IW_CM_STATE_ESTABLISHED:
		*qp_attr_mask = 0;
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक iw_cm_init_qp_attr(काष्ठा iw_cm_id *cm_id,
		       काष्ठा ib_qp_attr *qp_attr,
		       पूर्णांक *qp_attr_mask)
अणु
	काष्ठा iwcm_id_निजी *cm_id_priv;
	पूर्णांक ret;

	cm_id_priv = container_of(cm_id, काष्ठा iwcm_id_निजी, id);
	चयन (qp_attr->qp_state) अणु
	हाल IB_QPS_INIT:
	हाल IB_QPS_RTR:
		ret = iwcm_init_qp_init_attr(cm_id_priv,
					     qp_attr, qp_attr_mask);
		अवरोध;
	हाल IB_QPS_RTS:
		ret = iwcm_init_qp_rts_attr(cm_id_priv,
					    qp_attr, qp_attr_mask);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(iw_cm_init_qp_attr);

अटल पूर्णांक __init iw_cm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = iwpm_init(RDMA_NL_IWCM);
	अगर (ret)
		pr_err("iw_cm: couldn't init iwpm\n");
	अन्यथा
		rdma_nl_रेजिस्टर(RDMA_NL_IWCM, iwcm_nl_cb_table);
	iwcm_wq = alloc_ordered_workqueue("iw_cm_wq", 0);
	अगर (!iwcm_wq)
		वापस -ENOMEM;

	iwcm_ctl_table_hdr = रेजिस्टर_net_sysctl(&init_net, "net/iw_cm",
						 iwcm_ctl_table);
	अगर (!iwcm_ctl_table_hdr) अणु
		pr_err("iw_cm: couldn't register sysctl paths\n");
		destroy_workqueue(iwcm_wq);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास iw_cm_cleanup(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(iwcm_ctl_table_hdr);
	destroy_workqueue(iwcm_wq);
	rdma_nl_unरेजिस्टर(RDMA_NL_IWCM);
	iwpm_निकास(RDMA_NL_IWCM);
पूर्ण

MODULE_ALIAS_RDMA_NETLINK(RDMA_NL_IWCM, 2);

module_init(iw_cm_init);
module_निकास(iw_cm_cleanup);
