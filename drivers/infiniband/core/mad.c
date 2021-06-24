<शैली गुरु>
/*
 * Copyright (c) 2004-2007 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2005 Intel Corporation.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2009 HNR Consulting. All rights reserved.
 * Copyright (c) 2014,2018 Intel Corporation.  All rights reserved.
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/security.h>
#समावेश <linux/xarray.h>
#समावेश <rdma/ib_cache.h>

#समावेश "mad_priv.h"
#समावेश "core_priv.h"
#समावेश "mad_rmpp.h"
#समावेश "smi.h"
#समावेश "opa_smi.h"
#समावेश "agent.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/ib_mad.h>

#अगर_घोषित CONFIG_TRACEPOINTS
अटल व्योम create_mad_addr_info(काष्ठा ib_mad_send_wr_निजी *mad_send_wr,
			  काष्ठा ib_mad_qp_info *qp_info,
			  काष्ठा trace_event_raw_ib_mad_send_ढाँचा *entry)
अणु
	u16 pkey;
	काष्ठा ib_device *dev = qp_info->port_priv->device;
	u32 pnum = qp_info->port_priv->port_num;
	काष्ठा ib_ud_wr *wr = &mad_send_wr->send_wr;
	काष्ठा rdma_ah_attr attr = अणुपूर्ण;

	rdma_query_ah(wr->ah, &attr);

	/* These are common */
	entry->sl = attr.sl;
	ib_query_pkey(dev, pnum, wr->pkey_index, &pkey);
	entry->pkey = pkey;
	entry->rqpn = wr->remote_qpn;
	entry->rqkey = wr->remote_qkey;
	entry->dlid = rdma_ah_get_dlid(&attr);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mad_sendq_size = IB_MAD_QP_SEND_SIZE;
अटल पूर्णांक mad_recvq_size = IB_MAD_QP_RECV_SIZE;

module_param_named(send_queue_size, mad_sendq_size, पूर्णांक, 0444);
MODULE_PARM_DESC(send_queue_size, "Size of send queue in number of work requests");
module_param_named(recv_queue_size, mad_recvq_size, पूर्णांक, 0444);
MODULE_PARM_DESC(recv_queue_size, "Size of receive queue in number of work requests");

अटल DEFINE_XARRAY_ALLOC1(ib_mad_clients);
अटल u32 ib_mad_client_next;
अटल काष्ठा list_head ib_mad_port_list;

/* Port list lock */
अटल DEFINE_SPINLOCK(ib_mad_port_list_lock);

/* Forward declarations */
अटल पूर्णांक method_in_use(काष्ठा ib_mad_mgmt_method_table **method,
			 काष्ठा ib_mad_reg_req *mad_reg_req);
अटल व्योम हटाओ_mad_reg_req(काष्ठा ib_mad_agent_निजी *priv);
अटल काष्ठा ib_mad_agent_निजी *find_mad_agent(
					काष्ठा ib_mad_port_निजी *port_priv,
					स्थिर काष्ठा ib_mad_hdr *mad);
अटल पूर्णांक ib_mad_post_receive_mads(काष्ठा ib_mad_qp_info *qp_info,
				    काष्ठा ib_mad_निजी *mad);
अटल व्योम cancel_mads(काष्ठा ib_mad_agent_निजी *mad_agent_priv);
अटल व्योम समयout_sends(काष्ठा work_काष्ठा *work);
अटल व्योम local_completions(काष्ठा work_काष्ठा *work);
अटल पूर्णांक add_nonoui_reg_req(काष्ठा ib_mad_reg_req *mad_reg_req,
			      काष्ठा ib_mad_agent_निजी *agent_priv,
			      u8 mgmt_class);
अटल पूर्णांक add_oui_reg_req(काष्ठा ib_mad_reg_req *mad_reg_req,
			   काष्ठा ib_mad_agent_निजी *agent_priv);
अटल bool ib_mad_send_error(काष्ठा ib_mad_port_निजी *port_priv,
			      काष्ठा ib_wc *wc);
अटल व्योम ib_mad_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);

/*
 * Returns a ib_mad_port_निजी काष्ठाure or शून्य क्रम a device/port
 * Assumes ib_mad_port_list_lock is being held
 */
अटल अंतरभूत काष्ठा ib_mad_port_निजी *
__ib_get_mad_port(काष्ठा ib_device *device, u32 port_num)
अणु
	काष्ठा ib_mad_port_निजी *entry;

	list_क्रम_each_entry(entry, &ib_mad_port_list, port_list) अणु
		अगर (entry->device == device && entry->port_num == port_num)
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Wrapper function to वापस a ib_mad_port_निजी काष्ठाure or शून्य
 * क्रम a device/port
 */
अटल अंतरभूत काष्ठा ib_mad_port_निजी *
ib_get_mad_port(काष्ठा ib_device *device, u32 port_num)
अणु
	काष्ठा ib_mad_port_निजी *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ib_mad_port_list_lock, flags);
	entry = __ib_get_mad_port(device, port_num);
	spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);

	वापस entry;
पूर्ण

अटल अंतरभूत u8 convert_mgmt_class(u8 mgmt_class)
अणु
	/* Alias IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE to 0 */
	वापस mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE ?
		0 : mgmt_class;
पूर्ण

अटल पूर्णांक get_spl_qp_index(क्रमागत ib_qp_type qp_type)
अणु
	चयन (qp_type) अणु
	हाल IB_QPT_SMI:
		वापस 0;
	हाल IB_QPT_GSI:
		वापस 1;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक venकरोr_class_index(u8 mgmt_class)
अणु
	वापस mgmt_class - IB_MGMT_CLASS_VENDOR_RANGE2_START;
पूर्ण

अटल पूर्णांक is_venकरोr_class(u8 mgmt_class)
अणु
	अगर ((mgmt_class < IB_MGMT_CLASS_VENDOR_RANGE2_START) ||
	    (mgmt_class > IB_MGMT_CLASS_VENDOR_RANGE2_END))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक is_venकरोr_oui(अक्षर *oui)
अणु
	अगर (oui[0] || oui[1] || oui[2])
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक is_venकरोr_method_in_use(
		काष्ठा ib_mad_mgmt_venकरोr_class *venकरोr_class,
		काष्ठा ib_mad_reg_req *mad_reg_req)
अणु
	काष्ठा ib_mad_mgmt_method_table *method;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_MGMT_OUI; i++) अणु
		अगर (!स_भेद(venकरोr_class->oui[i], mad_reg_req->oui, 3)) अणु
			method = venकरोr_class->method_table[i];
			अगर (method) अणु
				अगर (method_in_use(&method, mad_reg_req))
					वापस 1;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ib_response_mad(स्थिर काष्ठा ib_mad_hdr *hdr)
अणु
	वापस ((hdr->method & IB_MGMT_METHOD_RESP) ||
		(hdr->method == IB_MGMT_METHOD_TRAP_REPRESS) ||
		((hdr->mgmt_class == IB_MGMT_CLASS_BM) &&
		 (hdr->attr_mod & IB_BM_ATTR_MOD_RESP)));
पूर्ण
EXPORT_SYMBOL(ib_response_mad);

/*
 * ib_रेजिस्टर_mad_agent - Register to send/receive MADs
 *
 * Context: Process context.
 */
काष्ठा ib_mad_agent *ib_रेजिस्टर_mad_agent(काष्ठा ib_device *device,
					   u32 port_num,
					   क्रमागत ib_qp_type qp_type,
					   काष्ठा ib_mad_reg_req *mad_reg_req,
					   u8 rmpp_version,
					   ib_mad_send_handler send_handler,
					   ib_mad_recv_handler recv_handler,
					   व्योम *context,
					   u32 registration_flags)
अणु
	काष्ठा ib_mad_port_निजी *port_priv;
	काष्ठा ib_mad_agent *ret = ERR_PTR(-EINVAL);
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;
	काष्ठा ib_mad_reg_req *reg_req = शून्य;
	काष्ठा ib_mad_mgmt_class_table *class;
	काष्ठा ib_mad_mgmt_venकरोr_class_table *venकरोr;
	काष्ठा ib_mad_mgmt_venकरोr_class *venकरोr_class;
	काष्ठा ib_mad_mgmt_method_table *method;
	पूर्णांक ret2, qpn;
	u8 mgmt_class, vclass;

	अगर ((qp_type == IB_QPT_SMI && !rdma_cap_ib_smi(device, port_num)) ||
	    (qp_type == IB_QPT_GSI && !rdma_cap_ib_cm(device, port_num)))
		वापस ERR_PTR(-EPROTONOSUPPORT);

	/* Validate parameters */
	qpn = get_spl_qp_index(qp_type);
	अगर (qpn == -1) अणु
		dev_dbg_ratelimited(&device->dev, "%s: invalid QP Type %d\n",
				    __func__, qp_type);
		जाओ error1;
	पूर्ण

	अगर (rmpp_version && rmpp_version != IB_MGMT_RMPP_VERSION) अणु
		dev_dbg_ratelimited(&device->dev,
				    "%s: invalid RMPP Version %u\n",
				    __func__, rmpp_version);
		जाओ error1;
	पूर्ण

	/* Validate MAD registration request अगर supplied */
	अगर (mad_reg_req) अणु
		अगर (mad_reg_req->mgmt_class_version >= MAX_MGMT_VERSION) अणु
			dev_dbg_ratelimited(&device->dev,
					    "%s: invalid Class Version %u\n",
					    __func__,
					    mad_reg_req->mgmt_class_version);
			जाओ error1;
		पूर्ण
		अगर (!recv_handler) अणु
			dev_dbg_ratelimited(&device->dev,
					    "%s: no recv_handler\n", __func__);
			जाओ error1;
		पूर्ण
		अगर (mad_reg_req->mgmt_class >= MAX_MGMT_CLASS) अणु
			/*
			 * IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE is the only
			 * one in this range currently allowed
			 */
			अगर (mad_reg_req->mgmt_class !=
			    IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) अणु
				dev_dbg_ratelimited(&device->dev,
					"%s: Invalid Mgmt Class 0x%x\n",
					__func__, mad_reg_req->mgmt_class);
				जाओ error1;
			पूर्ण
		पूर्ण अन्यथा अगर (mad_reg_req->mgmt_class == 0) अणु
			/*
			 * Class 0 is reserved in IBA and is used क्रम
			 * aliasing of IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE
			 */
			dev_dbg_ratelimited(&device->dev,
					    "%s: Invalid Mgmt Class 0\n",
					    __func__);
			जाओ error1;
		पूर्ण अन्यथा अगर (is_venकरोr_class(mad_reg_req->mgmt_class)) अणु
			/*
			 * If class is in "new" venकरोr range,
			 * ensure supplied OUI is not zero
			 */
			अगर (!is_venकरोr_oui(mad_reg_req->oui)) अणु
				dev_dbg_ratelimited(&device->dev,
					"%s: No OUI specified for class 0x%x\n",
					__func__,
					mad_reg_req->mgmt_class);
				जाओ error1;
			पूर्ण
		पूर्ण
		/* Make sure class supplied is consistent with RMPP */
		अगर (!ib_is_mad_class_rmpp(mad_reg_req->mgmt_class)) अणु
			अगर (rmpp_version) अणु
				dev_dbg_ratelimited(&device->dev,
					"%s: RMPP version for non-RMPP class 0x%x\n",
					__func__, mad_reg_req->mgmt_class);
				जाओ error1;
			पूर्ण
		पूर्ण

		/* Make sure class supplied is consistent with QP type */
		अगर (qp_type == IB_QPT_SMI) अणु
			अगर ((mad_reg_req->mgmt_class !=
					IB_MGMT_CLASS_SUBN_LID_ROUTED) &&
			    (mad_reg_req->mgmt_class !=
					IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)) अणु
				dev_dbg_ratelimited(&device->dev,
					"%s: Invalid SM QP type: class 0x%x\n",
					__func__, mad_reg_req->mgmt_class);
				जाओ error1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((mad_reg_req->mgmt_class ==
					IB_MGMT_CLASS_SUBN_LID_ROUTED) ||
			    (mad_reg_req->mgmt_class ==
					IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)) अणु
				dev_dbg_ratelimited(&device->dev,
					"%s: Invalid GS QP type: class 0x%x\n",
					__func__, mad_reg_req->mgmt_class);
				जाओ error1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* No registration request supplied */
		अगर (!send_handler)
			जाओ error1;
		अगर (registration_flags & IB_MAD_USER_RMPP)
			जाओ error1;
	पूर्ण

	/* Validate device and port */
	port_priv = ib_get_mad_port(device, port_num);
	अगर (!port_priv) अणु
		dev_dbg_ratelimited(&device->dev, "%s: Invalid port %d\n",
				    __func__, port_num);
		ret = ERR_PTR(-ENODEV);
		जाओ error1;
	पूर्ण

	/* Verअगरy the QP requested is supported. For example, Ethernet devices
	 * will not have QP0.
	 */
	अगर (!port_priv->qp_info[qpn].qp) अणु
		dev_dbg_ratelimited(&device->dev, "%s: QP %d not supported\n",
				    __func__, qpn);
		ret = ERR_PTR(-EPROTONOSUPPORT);
		जाओ error1;
	पूर्ण

	/* Allocate काष्ठाures */
	mad_agent_priv = kzalloc(माप *mad_agent_priv, GFP_KERNEL);
	अगर (!mad_agent_priv) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ error1;
	पूर्ण

	अगर (mad_reg_req) अणु
		reg_req = kmemdup(mad_reg_req, माप *reg_req, GFP_KERNEL);
		अगर (!reg_req) अणु
			ret = ERR_PTR(-ENOMEM);
			जाओ error3;
		पूर्ण
	पूर्ण

	/* Now, fill in the various काष्ठाures */
	mad_agent_priv->qp_info = &port_priv->qp_info[qpn];
	mad_agent_priv->reg_req = reg_req;
	mad_agent_priv->agent.rmpp_version = rmpp_version;
	mad_agent_priv->agent.device = device;
	mad_agent_priv->agent.recv_handler = recv_handler;
	mad_agent_priv->agent.send_handler = send_handler;
	mad_agent_priv->agent.context = context;
	mad_agent_priv->agent.qp = port_priv->qp_info[qpn].qp;
	mad_agent_priv->agent.port_num = port_num;
	mad_agent_priv->agent.flags = registration_flags;
	spin_lock_init(&mad_agent_priv->lock);
	INIT_LIST_HEAD(&mad_agent_priv->send_list);
	INIT_LIST_HEAD(&mad_agent_priv->रुको_list);
	INIT_LIST_HEAD(&mad_agent_priv->करोne_list);
	INIT_LIST_HEAD(&mad_agent_priv->rmpp_list);
	INIT_DELAYED_WORK(&mad_agent_priv->समयd_work, समयout_sends);
	INIT_LIST_HEAD(&mad_agent_priv->local_list);
	INIT_WORK(&mad_agent_priv->local_work, local_completions);
	refcount_set(&mad_agent_priv->refcount, 1);
	init_completion(&mad_agent_priv->comp);

	ret2 = ib_mad_agent_security_setup(&mad_agent_priv->agent, qp_type);
	अगर (ret2) अणु
		ret = ERR_PTR(ret2);
		जाओ error4;
	पूर्ण

	/*
	 * The mlx4 driver uses the top byte to distinguish which भव
	 * function generated the MAD, so we must aव्योम using it.
	 */
	ret2 = xa_alloc_cyclic(&ib_mad_clients, &mad_agent_priv->agent.hi_tid,
			mad_agent_priv, XA_LIMIT(0, (1 << 24) - 1),
			&ib_mad_client_next, GFP_KERNEL);
	अगर (ret2 < 0) अणु
		ret = ERR_PTR(ret2);
		जाओ error5;
	पूर्ण

	/*
	 * Make sure MAD registration (अगर supplied)
	 * is non overlapping with any existing ones
	 */
	spin_lock_irq(&port_priv->reg_lock);
	अगर (mad_reg_req) अणु
		mgmt_class = convert_mgmt_class(mad_reg_req->mgmt_class);
		अगर (!is_venकरोr_class(mgmt_class)) अणु
			class = port_priv->version[mad_reg_req->
						   mgmt_class_version].class;
			अगर (class) अणु
				method = class->method_table[mgmt_class];
				अगर (method) अणु
					अगर (method_in_use(&method,
							   mad_reg_req))
						जाओ error6;
				पूर्ण
			पूर्ण
			ret2 = add_nonoui_reg_req(mad_reg_req, mad_agent_priv,
						  mgmt_class);
		पूर्ण अन्यथा अणु
			/* "New" venकरोr class range */
			venकरोr = port_priv->version[mad_reg_req->
						    mgmt_class_version].venकरोr;
			अगर (venकरोr) अणु
				vclass = venकरोr_class_index(mgmt_class);
				venकरोr_class = venकरोr->venकरोr_class[vclass];
				अगर (venकरोr_class) अणु
					अगर (is_venकरोr_method_in_use(
							venकरोr_class,
							mad_reg_req))
						जाओ error6;
				पूर्ण
			पूर्ण
			ret2 = add_oui_reg_req(mad_reg_req, mad_agent_priv);
		पूर्ण
		अगर (ret2) अणु
			ret = ERR_PTR(ret2);
			जाओ error6;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&port_priv->reg_lock);

	trace_ib_mad_create_agent(mad_agent_priv);
	वापस &mad_agent_priv->agent;
error6:
	spin_unlock_irq(&port_priv->reg_lock);
	xa_erase(&ib_mad_clients, mad_agent_priv->agent.hi_tid);
error5:
	ib_mad_agent_security_cleanup(&mad_agent_priv->agent);
error4:
	kमुक्त(reg_req);
error3:
	kमुक्त(mad_agent_priv);
error1:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_रेजिस्टर_mad_agent);

अटल अंतरभूत व्योम deref_mad_agent(काष्ठा ib_mad_agent_निजी *mad_agent_priv)
अणु
	अगर (refcount_dec_and_test(&mad_agent_priv->refcount))
		complete(&mad_agent_priv->comp);
पूर्ण

अटल व्योम unरेजिस्टर_mad_agent(काष्ठा ib_mad_agent_निजी *mad_agent_priv)
अणु
	काष्ठा ib_mad_port_निजी *port_priv;

	/* Note that we could still be handling received MADs */
	trace_ib_mad_unरेजिस्टर_agent(mad_agent_priv);

	/*
	 * Canceling all sends results in dropping received response
	 * MADs, preventing us from queuing additional work
	 */
	cancel_mads(mad_agent_priv);
	port_priv = mad_agent_priv->qp_info->port_priv;
	cancel_delayed_work(&mad_agent_priv->समयd_work);

	spin_lock_irq(&port_priv->reg_lock);
	हटाओ_mad_reg_req(mad_agent_priv);
	spin_unlock_irq(&port_priv->reg_lock);
	xa_erase(&ib_mad_clients, mad_agent_priv->agent.hi_tid);

	flush_workqueue(port_priv->wq);

	deref_mad_agent(mad_agent_priv);
	रुको_क्रम_completion(&mad_agent_priv->comp);
	ib_cancel_rmpp_recvs(mad_agent_priv);

	ib_mad_agent_security_cleanup(&mad_agent_priv->agent);

	kमुक्त(mad_agent_priv->reg_req);
	kमुक्त_rcu(mad_agent_priv, rcu);
पूर्ण

/*
 * ib_unरेजिस्टर_mad_agent - Unरेजिस्टरs a client from using MAD services
 *
 * Context: Process context.
 */
व्योम ib_unरेजिस्टर_mad_agent(काष्ठा ib_mad_agent *mad_agent)
अणु
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;

	mad_agent_priv = container_of(mad_agent,
				      काष्ठा ib_mad_agent_निजी,
				      agent);
	unरेजिस्टर_mad_agent(mad_agent_priv);
पूर्ण
EXPORT_SYMBOL(ib_unरेजिस्टर_mad_agent);

अटल व्योम dequeue_mad(काष्ठा ib_mad_list_head *mad_list)
अणु
	काष्ठा ib_mad_queue *mad_queue;
	अचिन्हित दीर्घ flags;

	mad_queue = mad_list->mad_queue;
	spin_lock_irqsave(&mad_queue->lock, flags);
	list_del(&mad_list->list);
	mad_queue->count--;
	spin_unlock_irqrestore(&mad_queue->lock, flags);
पूर्ण

अटल व्योम build_smp_wc(काष्ठा ib_qp *qp, काष्ठा ib_cqe *cqe, u16 slid,
		u16 pkey_index, u32 port_num, काष्ठा ib_wc *wc)
अणु
	स_रखो(wc, 0, माप *wc);
	wc->wr_cqe = cqe;
	wc->status = IB_WC_SUCCESS;
	wc->opcode = IB_WC_RECV;
	wc->pkey_index = pkey_index;
	wc->byte_len = माप(काष्ठा ib_mad) + माप(काष्ठा ib_grh);
	wc->src_qp = IB_QP0;
	wc->qp = qp;
	wc->slid = slid;
	wc->sl = 0;
	wc->dlid_path_bits = 0;
	wc->port_num = port_num;
पूर्ण

अटल माप_प्रकार mad_priv_size(स्थिर काष्ठा ib_mad_निजी *mp)
अणु
	वापस माप(काष्ठा ib_mad_निजी) + mp->mad_size;
पूर्ण

अटल काष्ठा ib_mad_निजी *alloc_mad_निजी(माप_प्रकार mad_size, gfp_t flags)
अणु
	माप_प्रकार size = माप(काष्ठा ib_mad_निजी) + mad_size;
	काष्ठा ib_mad_निजी *ret = kzalloc(size, flags);

	अगर (ret)
		ret->mad_size = mad_size;

	वापस ret;
पूर्ण

अटल माप_प्रकार port_mad_size(स्थिर काष्ठा ib_mad_port_निजी *port_priv)
अणु
	वापस rdma_max_mad_size(port_priv->device, port_priv->port_num);
पूर्ण

अटल माप_प्रकार mad_priv_dma_size(स्थिर काष्ठा ib_mad_निजी *mp)
अणु
	वापस माप(काष्ठा ib_grh) + mp->mad_size;
पूर्ण

/*
 * Return 0 अगर SMP is to be sent
 * Return 1 अगर SMP was consumed locally (whether or not solicited)
 * Return < 0 अगर error
 */
अटल पूर्णांक handle_outgoing_dr_smp(काष्ठा ib_mad_agent_निजी *mad_agent_priv,
				  काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	पूर्णांक ret = 0;
	काष्ठा ib_smp *smp = mad_send_wr->send_buf.mad;
	काष्ठा opa_smp *opa_smp = (काष्ठा opa_smp *)smp;
	अचिन्हित दीर्घ flags;
	काष्ठा ib_mad_local_निजी *local;
	काष्ठा ib_mad_निजी *mad_priv;
	काष्ठा ib_mad_port_निजी *port_priv;
	काष्ठा ib_mad_agent_निजी *recv_mad_agent = शून्य;
	काष्ठा ib_device *device = mad_agent_priv->agent.device;
	u32 port_num;
	काष्ठा ib_wc mad_wc;
	काष्ठा ib_ud_wr *send_wr = &mad_send_wr->send_wr;
	माप_प्रकार mad_size = port_mad_size(mad_agent_priv->qp_info->port_priv);
	u16 out_mad_pkey_index = 0;
	u16 drslid;
	bool opa = rdma_cap_opa_mad(mad_agent_priv->qp_info->port_priv->device,
				    mad_agent_priv->qp_info->port_priv->port_num);

	अगर (rdma_cap_ib_चयन(device) &&
	    smp->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		port_num = send_wr->port_num;
	अन्यथा
		port_num = mad_agent_priv->agent.port_num;

	/*
	 * Directed route handling starts अगर the initial LID routed part of
	 * a request or the ending LID routed part of a response is empty.
	 * If we are at the start of the LID routed part, करोn't update the
	 * hop_ptr or hop_cnt.  See section 14.2.2, Vol 1 IB spec.
	 */
	अगर (opa && smp->class_version == OPA_SM_CLASS_VERSION) अणु
		u32 opa_drslid;

		trace_ib_mad_handle_out_opa_smi(opa_smp);

		अगर ((opa_get_smp_direction(opa_smp)
		     ? opa_smp->route.dr.dr_dlid : opa_smp->route.dr.dr_slid) ==
		     OPA_LID_PERMISSIVE &&
		     opa_smi_handle_dr_smp_send(opa_smp,
						rdma_cap_ib_चयन(device),
						port_num) == IB_SMI_DISCARD) अणु
			ret = -EINVAL;
			dev_err(&device->dev, "OPA Invalid directed route\n");
			जाओ out;
		पूर्ण
		opa_drslid = be32_to_cpu(opa_smp->route.dr.dr_slid);
		अगर (opa_drslid != be32_to_cpu(OPA_LID_PERMISSIVE) &&
		    opa_drslid & 0xffff0000) अणु
			ret = -EINVAL;
			dev_err(&device->dev, "OPA Invalid dr_slid 0x%x\n",
			       opa_drslid);
			जाओ out;
		पूर्ण
		drslid = (u16)(opa_drslid & 0x0000ffff);

		/* Check to post send on QP or process locally */
		अगर (opa_smi_check_local_smp(opa_smp, device) == IB_SMI_DISCARD &&
		    opa_smi_check_local_वापसing_smp(opa_smp, device) == IB_SMI_DISCARD)
			जाओ out;
	पूर्ण अन्यथा अणु
		trace_ib_mad_handle_out_ib_smi(smp);

		अगर ((ib_get_smp_direction(smp) ? smp->dr_dlid : smp->dr_slid) ==
		     IB_LID_PERMISSIVE &&
		     smi_handle_dr_smp_send(smp, rdma_cap_ib_चयन(device), port_num) ==
		     IB_SMI_DISCARD) अणु
			ret = -EINVAL;
			dev_err(&device->dev, "Invalid directed route\n");
			जाओ out;
		पूर्ण
		drslid = be16_to_cpu(smp->dr_slid);

		/* Check to post send on QP or process locally */
		अगर (smi_check_local_smp(smp, device) == IB_SMI_DISCARD &&
		    smi_check_local_वापसing_smp(smp, device) == IB_SMI_DISCARD)
			जाओ out;
	पूर्ण

	local = kदो_स्मृति(माप *local, GFP_ATOMIC);
	अगर (!local) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	local->mad_priv = शून्य;
	local->recv_mad_agent = शून्य;
	mad_priv = alloc_mad_निजी(mad_size, GFP_ATOMIC);
	अगर (!mad_priv) अणु
		ret = -ENOMEM;
		kमुक्त(local);
		जाओ out;
	पूर्ण

	build_smp_wc(mad_agent_priv->agent.qp,
		     send_wr->wr.wr_cqe, drslid,
		     send_wr->pkey_index,
		     send_wr->port_num, &mad_wc);

	अगर (opa && smp->base_version == OPA_MGMT_BASE_VERSION) अणु
		mad_wc.byte_len = mad_send_wr->send_buf.hdr_len
					+ mad_send_wr->send_buf.data_len
					+ माप(काष्ठा ib_grh);
	पूर्ण

	/* No GRH क्रम DR SMP */
	ret = device->ops.process_mad(device, 0, port_num, &mad_wc, शून्य,
				      (स्थिर काष्ठा ib_mad *)smp,
				      (काष्ठा ib_mad *)mad_priv->mad, &mad_size,
				      &out_mad_pkey_index);
	चयन (ret) अणु
	हाल IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY:
		अगर (ib_response_mad((स्थिर काष्ठा ib_mad_hdr *)mad_priv->mad) &&
		    mad_agent_priv->agent.recv_handler) अणु
			local->mad_priv = mad_priv;
			local->recv_mad_agent = mad_agent_priv;
			/*
			 * Reference MAD agent until receive
			 * side of local completion handled
			 */
			refcount_inc(&mad_agent_priv->refcount);
		पूर्ण अन्यथा
			kमुक्त(mad_priv);
		अवरोध;
	हाल IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED:
		kमुक्त(mad_priv);
		अवरोध;
	हाल IB_MAD_RESULT_SUCCESS:
		/* Treat like an incoming receive MAD */
		port_priv = ib_get_mad_port(mad_agent_priv->agent.device,
					    mad_agent_priv->agent.port_num);
		अगर (port_priv) अणु
			स_नकल(mad_priv->mad, smp, mad_priv->mad_size);
			recv_mad_agent = find_mad_agent(port_priv,
						        (स्थिर काष्ठा ib_mad_hdr *)mad_priv->mad);
		पूर्ण
		अगर (!port_priv || !recv_mad_agent) अणु
			/*
			 * No receiving agent so drop packet and
			 * generate send completion.
			 */
			kमुक्त(mad_priv);
			अवरोध;
		पूर्ण
		local->mad_priv = mad_priv;
		local->recv_mad_agent = recv_mad_agent;
		अवरोध;
	शेष:
		kमुक्त(mad_priv);
		kमुक्त(local);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	local->mad_send_wr = mad_send_wr;
	अगर (opa) अणु
		local->mad_send_wr->send_wr.pkey_index = out_mad_pkey_index;
		local->वापस_wc_byte_len = mad_size;
	पूर्ण
	/* Reference MAD agent until send side of local completion handled */
	refcount_inc(&mad_agent_priv->refcount);
	/* Queue local completion to local list */
	spin_lock_irqsave(&mad_agent_priv->lock, flags);
	list_add_tail(&local->completion_list, &mad_agent_priv->local_list);
	spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
	queue_work(mad_agent_priv->qp_info->port_priv->wq,
		   &mad_agent_priv->local_work);
	ret = 1;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक get_pad_size(पूर्णांक hdr_len, पूर्णांक data_len, माप_प्रकार mad_size)
अणु
	पूर्णांक seg_size, pad;

	seg_size = mad_size - hdr_len;
	अगर (data_len && seg_size) अणु
		pad = seg_size - data_len % seg_size;
		वापस pad == seg_size ? 0 : pad;
	पूर्ण अन्यथा
		वापस seg_size;
पूर्ण

अटल व्योम मुक्त_send_rmpp_list(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	काष्ठा ib_rmpp_segment *s, *t;

	list_क्रम_each_entry_safe(s, t, &mad_send_wr->rmpp_list, list) अणु
		list_del(&s->list);
		kमुक्त(s);
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_send_rmpp_list(काष्ठा ib_mad_send_wr_निजी *send_wr,
				माप_प्रकार mad_size, gfp_t gfp_mask)
अणु
	काष्ठा ib_mad_send_buf *send_buf = &send_wr->send_buf;
	काष्ठा ib_rmpp_mad *rmpp_mad = send_buf->mad;
	काष्ठा ib_rmpp_segment *seg = शून्य;
	पूर्णांक left, seg_size, pad;

	send_buf->seg_size = mad_size - send_buf->hdr_len;
	send_buf->seg_rmpp_size = mad_size - IB_MGMT_RMPP_HDR;
	seg_size = send_buf->seg_size;
	pad = send_wr->pad;

	/* Allocate data segments. */
	क्रम (left = send_buf->data_len + pad; left > 0; left -= seg_size) अणु
		seg = kदो_स्मृति(माप(*seg) + seg_size, gfp_mask);
		अगर (!seg) अणु
			मुक्त_send_rmpp_list(send_wr);
			वापस -ENOMEM;
		पूर्ण
		seg->num = ++send_buf->seg_count;
		list_add_tail(&seg->list, &send_wr->rmpp_list);
	पूर्ण

	/* Zero any padding */
	अगर (pad)
		स_रखो(seg->data + seg_size - pad, 0, pad);

	rmpp_mad->rmpp_hdr.rmpp_version = send_wr->mad_agent_priv->
					  agent.rmpp_version;
	rmpp_mad->rmpp_hdr.rmpp_type = IB_MGMT_RMPP_TYPE_DATA;
	ib_set_rmpp_flags(&rmpp_mad->rmpp_hdr, IB_MGMT_RMPP_FLAG_ACTIVE);

	send_wr->cur_seg = container_of(send_wr->rmpp_list.next,
					काष्ठा ib_rmpp_segment, list);
	send_wr->last_ack_seg = send_wr->cur_seg;
	वापस 0;
पूर्ण

पूर्णांक ib_mad_kernel_rmpp_agent(स्थिर काष्ठा ib_mad_agent *agent)
अणु
	वापस agent->rmpp_version && !(agent->flags & IB_MAD_USER_RMPP);
पूर्ण
EXPORT_SYMBOL(ib_mad_kernel_rmpp_agent);

काष्ठा ib_mad_send_buf *ib_create_send_mad(काष्ठा ib_mad_agent *mad_agent,
					   u32 remote_qpn, u16 pkey_index,
					   पूर्णांक rmpp_active, पूर्णांक hdr_len,
					   पूर्णांक data_len, gfp_t gfp_mask,
					   u8 base_version)
अणु
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	पूर्णांक pad, message_size, ret, size;
	व्योम *buf;
	माप_प्रकार mad_size;
	bool opa;

	mad_agent_priv = container_of(mad_agent, काष्ठा ib_mad_agent_निजी,
				      agent);

	opa = rdma_cap_opa_mad(mad_agent->device, mad_agent->port_num);

	अगर (opa && base_version == OPA_MGMT_BASE_VERSION)
		mad_size = माप(काष्ठा opa_mad);
	अन्यथा
		mad_size = माप(काष्ठा ib_mad);

	pad = get_pad_size(hdr_len, data_len, mad_size);
	message_size = hdr_len + data_len + pad;

	अगर (ib_mad_kernel_rmpp_agent(mad_agent)) अणु
		अगर (!rmpp_active && message_size > mad_size)
			वापस ERR_PTR(-EINVAL);
	पूर्ण अन्यथा
		अगर (rmpp_active || message_size > mad_size)
			वापस ERR_PTR(-EINVAL);

	size = rmpp_active ? hdr_len : mad_size;
	buf = kzalloc(माप *mad_send_wr + size, gfp_mask);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	mad_send_wr = buf + size;
	INIT_LIST_HEAD(&mad_send_wr->rmpp_list);
	mad_send_wr->send_buf.mad = buf;
	mad_send_wr->send_buf.hdr_len = hdr_len;
	mad_send_wr->send_buf.data_len = data_len;
	mad_send_wr->pad = pad;

	mad_send_wr->mad_agent_priv = mad_agent_priv;
	mad_send_wr->sg_list[0].length = hdr_len;
	mad_send_wr->sg_list[0].lkey = mad_agent->qp->pd->local_dma_lkey;

	/* OPA MADs करोn't have to be the full 2048 bytes */
	अगर (opa && base_version == OPA_MGMT_BASE_VERSION &&
	    data_len < mad_size - hdr_len)
		mad_send_wr->sg_list[1].length = data_len;
	अन्यथा
		mad_send_wr->sg_list[1].length = mad_size - hdr_len;

	mad_send_wr->sg_list[1].lkey = mad_agent->qp->pd->local_dma_lkey;

	mad_send_wr->mad_list.cqe.करोne = ib_mad_send_करोne;

	mad_send_wr->send_wr.wr.wr_cqe = &mad_send_wr->mad_list.cqe;
	mad_send_wr->send_wr.wr.sg_list = mad_send_wr->sg_list;
	mad_send_wr->send_wr.wr.num_sge = 2;
	mad_send_wr->send_wr.wr.opcode = IB_WR_SEND;
	mad_send_wr->send_wr.wr.send_flags = IB_SEND_SIGNALED;
	mad_send_wr->send_wr.remote_qpn = remote_qpn;
	mad_send_wr->send_wr.remote_qkey = IB_QP_SET_QKEY;
	mad_send_wr->send_wr.pkey_index = pkey_index;

	अगर (rmpp_active) अणु
		ret = alloc_send_rmpp_list(mad_send_wr, mad_size, gfp_mask);
		अगर (ret) अणु
			kमुक्त(buf);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	mad_send_wr->send_buf.mad_agent = mad_agent;
	refcount_inc(&mad_agent_priv->refcount);
	वापस &mad_send_wr->send_buf;
पूर्ण
EXPORT_SYMBOL(ib_create_send_mad);

पूर्णांक ib_get_mad_data_offset(u8 mgmt_class)
अणु
	अगर (mgmt_class == IB_MGMT_CLASS_SUBN_ADM)
		वापस IB_MGMT_SA_HDR;
	अन्यथा अगर ((mgmt_class == IB_MGMT_CLASS_DEVICE_MGMT) ||
		 (mgmt_class == IB_MGMT_CLASS_DEVICE_ADM) ||
		 (mgmt_class == IB_MGMT_CLASS_BIS))
		वापस IB_MGMT_DEVICE_HDR;
	अन्यथा अगर ((mgmt_class >= IB_MGMT_CLASS_VENDOR_RANGE2_START) &&
		 (mgmt_class <= IB_MGMT_CLASS_VENDOR_RANGE2_END))
		वापस IB_MGMT_VENDOR_HDR;
	अन्यथा
		वापस IB_MGMT_MAD_HDR;
पूर्ण
EXPORT_SYMBOL(ib_get_mad_data_offset);

पूर्णांक ib_is_mad_class_rmpp(u8 mgmt_class)
अणु
	अगर ((mgmt_class == IB_MGMT_CLASS_SUBN_ADM) ||
	    (mgmt_class == IB_MGMT_CLASS_DEVICE_MGMT) ||
	    (mgmt_class == IB_MGMT_CLASS_DEVICE_ADM) ||
	    (mgmt_class == IB_MGMT_CLASS_BIS) ||
	    ((mgmt_class >= IB_MGMT_CLASS_VENDOR_RANGE2_START) &&
	     (mgmt_class <= IB_MGMT_CLASS_VENDOR_RANGE2_END)))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_is_mad_class_rmpp);

व्योम *ib_get_rmpp_segment(काष्ठा ib_mad_send_buf *send_buf, पूर्णांक seg_num)
अणु
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	काष्ठा list_head *list;

	mad_send_wr = container_of(send_buf, काष्ठा ib_mad_send_wr_निजी,
				   send_buf);
	list = &mad_send_wr->cur_seg->list;

	अगर (mad_send_wr->cur_seg->num < seg_num) अणु
		list_क्रम_each_entry(mad_send_wr->cur_seg, list, list)
			अगर (mad_send_wr->cur_seg->num == seg_num)
				अवरोध;
	पूर्ण अन्यथा अगर (mad_send_wr->cur_seg->num > seg_num) अणु
		list_क्रम_each_entry_reverse(mad_send_wr->cur_seg, list, list)
			अगर (mad_send_wr->cur_seg->num == seg_num)
				अवरोध;
	पूर्ण
	वापस mad_send_wr->cur_seg->data;
पूर्ण
EXPORT_SYMBOL(ib_get_rmpp_segment);

अटल अंतरभूत व्योम *ib_get_payload(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	अगर (mad_send_wr->send_buf.seg_count)
		वापस ib_get_rmpp_segment(&mad_send_wr->send_buf,
					   mad_send_wr->seg_num);
	अन्यथा
		वापस mad_send_wr->send_buf.mad +
		       mad_send_wr->send_buf.hdr_len;
पूर्ण

व्योम ib_मुक्त_send_mad(काष्ठा ib_mad_send_buf *send_buf)
अणु
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;

	mad_agent_priv = container_of(send_buf->mad_agent,
				      काष्ठा ib_mad_agent_निजी, agent);
	mad_send_wr = container_of(send_buf, काष्ठा ib_mad_send_wr_निजी,
				   send_buf);

	मुक्त_send_rmpp_list(mad_send_wr);
	kमुक्त(send_buf->mad);
	deref_mad_agent(mad_agent_priv);
पूर्ण
EXPORT_SYMBOL(ib_मुक्त_send_mad);

पूर्णांक ib_send_mad(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	काष्ठा ib_mad_qp_info *qp_info;
	काष्ठा list_head *list;
	काष्ठा ib_mad_agent *mad_agent;
	काष्ठा ib_sge *sge;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Set WR ID to find mad_send_wr upon completion */
	qp_info = mad_send_wr->mad_agent_priv->qp_info;
	mad_send_wr->mad_list.mad_queue = &qp_info->send_queue;
	mad_send_wr->mad_list.cqe.करोne = ib_mad_send_करोne;
	mad_send_wr->send_wr.wr.wr_cqe = &mad_send_wr->mad_list.cqe;

	mad_agent = mad_send_wr->send_buf.mad_agent;
	sge = mad_send_wr->sg_list;
	sge[0].addr = ib_dma_map_single(mad_agent->device,
					mad_send_wr->send_buf.mad,
					sge[0].length,
					DMA_TO_DEVICE);
	अगर (unlikely(ib_dma_mapping_error(mad_agent->device, sge[0].addr)))
		वापस -ENOMEM;

	mad_send_wr->header_mapping = sge[0].addr;

	sge[1].addr = ib_dma_map_single(mad_agent->device,
					ib_get_payload(mad_send_wr),
					sge[1].length,
					DMA_TO_DEVICE);
	अगर (unlikely(ib_dma_mapping_error(mad_agent->device, sge[1].addr))) अणु
		ib_dma_unmap_single(mad_agent->device,
				    mad_send_wr->header_mapping,
				    sge[0].length, DMA_TO_DEVICE);
		वापस -ENOMEM;
	पूर्ण
	mad_send_wr->payload_mapping = sge[1].addr;

	spin_lock_irqsave(&qp_info->send_queue.lock, flags);
	अगर (qp_info->send_queue.count < qp_info->send_queue.max_active) अणु
		trace_ib_mad_ib_send_mad(mad_send_wr, qp_info);
		ret = ib_post_send(mad_agent->qp, &mad_send_wr->send_wr.wr,
				   शून्य);
		list = &qp_info->send_queue.list;
	पूर्ण अन्यथा अणु
		ret = 0;
		list = &qp_info->overflow_list;
	पूर्ण

	अगर (!ret) अणु
		qp_info->send_queue.count++;
		list_add_tail(&mad_send_wr->mad_list.list, list);
	पूर्ण
	spin_unlock_irqrestore(&qp_info->send_queue.lock, flags);
	अगर (ret) अणु
		ib_dma_unmap_single(mad_agent->device,
				    mad_send_wr->header_mapping,
				    sge[0].length, DMA_TO_DEVICE);
		ib_dma_unmap_single(mad_agent->device,
				    mad_send_wr->payload_mapping,
				    sge[1].length, DMA_TO_DEVICE);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * ib_post_send_mad - Posts MAD(s) to the send queue of the QP associated
 *  with the रेजिस्टरed client
 */
पूर्णांक ib_post_send_mad(काष्ठा ib_mad_send_buf *send_buf,
		     काष्ठा ib_mad_send_buf **bad_send_buf)
अणु
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;
	काष्ठा ib_mad_send_buf *next_send_buf;
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	/* Walk list of send WRs and post each on send list */
	क्रम (; send_buf; send_buf = next_send_buf) अणु
		mad_send_wr = container_of(send_buf,
					   काष्ठा ib_mad_send_wr_निजी,
					   send_buf);
		mad_agent_priv = mad_send_wr->mad_agent_priv;

		ret = ib_mad_enक्रमce_security(mad_agent_priv,
					      mad_send_wr->send_wr.pkey_index);
		अगर (ret)
			जाओ error;

		अगर (!send_buf->mad_agent->send_handler ||
		    (send_buf->समयout_ms &&
		     !send_buf->mad_agent->recv_handler)) अणु
			ret = -EINVAL;
			जाओ error;
		पूर्ण

		अगर (!ib_is_mad_class_rmpp(((काष्ठा ib_mad_hdr *) send_buf->mad)->mgmt_class)) अणु
			अगर (mad_agent_priv->agent.rmpp_version) अणु
				ret = -EINVAL;
				जाओ error;
			पूर्ण
		पूर्ण

		/*
		 * Save poपूर्णांकer to next work request to post in हाल the
		 * current one completes, and the user modअगरies the work
		 * request associated with the completion
		 */
		next_send_buf = send_buf->next;
		mad_send_wr->send_wr.ah = send_buf->ah;

		अगर (((काष्ठा ib_mad_hdr *) send_buf->mad)->mgmt_class ==
		    IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) अणु
			ret = handle_outgoing_dr_smp(mad_agent_priv,
						     mad_send_wr);
			अगर (ret < 0)		/* error */
				जाओ error;
			अन्यथा अगर (ret == 1)	/* locally consumed */
				जारी;
		पूर्ण

		mad_send_wr->tid = ((काष्ठा ib_mad_hdr *) send_buf->mad)->tid;
		/* Timeout will be updated after send completes */
		mad_send_wr->समयout = msecs_to_jअगरfies(send_buf->समयout_ms);
		mad_send_wr->max_retries = send_buf->retries;
		mad_send_wr->retries_left = send_buf->retries;
		send_buf->retries = 0;
		/* Reference क्रम work request to QP + response */
		mad_send_wr->refcount = 1 + (mad_send_wr->समयout > 0);
		mad_send_wr->status = IB_WC_SUCCESS;

		/* Reference MAD agent until send completes */
		refcount_inc(&mad_agent_priv->refcount);
		spin_lock_irqsave(&mad_agent_priv->lock, flags);
		list_add_tail(&mad_send_wr->agent_list,
			      &mad_agent_priv->send_list);
		spin_unlock_irqrestore(&mad_agent_priv->lock, flags);

		अगर (ib_mad_kernel_rmpp_agent(&mad_agent_priv->agent)) अणु
			ret = ib_send_rmpp_mad(mad_send_wr);
			अगर (ret >= 0 && ret != IB_RMPP_RESULT_CONSUMED)
				ret = ib_send_mad(mad_send_wr);
		पूर्ण अन्यथा
			ret = ib_send_mad(mad_send_wr);
		अगर (ret < 0) अणु
			/* Fail send request */
			spin_lock_irqsave(&mad_agent_priv->lock, flags);
			list_del(&mad_send_wr->agent_list);
			spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
			deref_mad_agent(mad_agent_priv);
			जाओ error;
		पूर्ण
	पूर्ण
	वापस 0;
error:
	अगर (bad_send_buf)
		*bad_send_buf = send_buf;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_post_send_mad);

/*
 * ib_मुक्त_recv_mad - Returns data buffers used to receive
 *  a MAD to the access layer
 */
व्योम ib_मुक्त_recv_mad(काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_mad_recv_buf *mad_recv_buf, *temp_recv_buf;
	काष्ठा ib_mad_निजी_header *mad_priv_hdr;
	काष्ठा ib_mad_निजी *priv;
	काष्ठा list_head मुक्त_list;

	INIT_LIST_HEAD(&मुक्त_list);
	list_splice_init(&mad_recv_wc->rmpp_list, &मुक्त_list);

	list_क्रम_each_entry_safe(mad_recv_buf, temp_recv_buf,
					&मुक्त_list, list) अणु
		mad_recv_wc = container_of(mad_recv_buf, काष्ठा ib_mad_recv_wc,
					   recv_buf);
		mad_priv_hdr = container_of(mad_recv_wc,
					    काष्ठा ib_mad_निजी_header,
					    recv_wc);
		priv = container_of(mad_priv_hdr, काष्ठा ib_mad_निजी,
				    header);
		kमुक्त(priv);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ib_मुक्त_recv_mad);

अटल पूर्णांक method_in_use(काष्ठा ib_mad_mgmt_method_table **method,
			 काष्ठा ib_mad_reg_req *mad_reg_req)
अणु
	पूर्णांक i;

	क्रम_each_set_bit(i, mad_reg_req->method_mask, IB_MGMT_MAX_METHODS) अणु
		अगर ((*method)->agent[i]) अणु
			pr_err("Method %d already in use\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक allocate_method_table(काष्ठा ib_mad_mgmt_method_table **method)
अणु
	/* Allocate management method table */
	*method = kzalloc(माप **method, GFP_ATOMIC);
	वापस (*method) ? 0 : (-ENOMEM);
पूर्ण

/*
 * Check to see अगर there are any methods still in use
 */
अटल पूर्णांक check_method_table(काष्ठा ib_mad_mgmt_method_table *method)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IB_MGMT_MAX_METHODS; i++)
		अगर (method->agent[i])
			वापस 1;
	वापस 0;
पूर्ण

/*
 * Check to see अगर there are any method tables क्रम this class still in use
 */
अटल पूर्णांक check_class_table(काष्ठा ib_mad_mgmt_class_table *class)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_MGMT_CLASS; i++)
		अगर (class->method_table[i])
			वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक check_venकरोr_class(काष्ठा ib_mad_mgmt_venकरोr_class *venकरोr_class)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_MGMT_OUI; i++)
		अगर (venकरोr_class->method_table[i])
			वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक find_venकरोr_oui(काष्ठा ib_mad_mgmt_venकरोr_class *venकरोr_class,
			   स्थिर अक्षर *oui)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_MGMT_OUI; i++)
		/* Is there matching OUI क्रम this venकरोr class ? */
		अगर (!स_भेद(venकरोr_class->oui[i], oui, 3))
			वापस i;

	वापस -1;
पूर्ण

अटल पूर्णांक check_venकरोr_table(काष्ठा ib_mad_mgmt_venकरोr_class_table *venकरोr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_MGMT_VENDOR_RANGE2; i++)
		अगर (venकरोr->venकरोr_class[i])
			वापस 1;

	वापस 0;
पूर्ण

अटल व्योम हटाओ_methods_mad_agent(काष्ठा ib_mad_mgmt_method_table *method,
				     काष्ठा ib_mad_agent_निजी *agent)
अणु
	पूर्णांक i;

	/* Remove any methods क्रम this mad agent */
	क्रम (i = 0; i < IB_MGMT_MAX_METHODS; i++)
		अगर (method->agent[i] == agent)
			method->agent[i] = शून्य;
पूर्ण

अटल पूर्णांक add_nonoui_reg_req(काष्ठा ib_mad_reg_req *mad_reg_req,
			      काष्ठा ib_mad_agent_निजी *agent_priv,
			      u8 mgmt_class)
अणु
	काष्ठा ib_mad_port_निजी *port_priv;
	काष्ठा ib_mad_mgmt_class_table **class;
	काष्ठा ib_mad_mgmt_method_table **method;
	पूर्णांक i, ret;

	port_priv = agent_priv->qp_info->port_priv;
	class = &port_priv->version[mad_reg_req->mgmt_class_version].class;
	अगर (!*class) अणु
		/* Allocate management class table क्रम "new" class version */
		*class = kzalloc(माप **class, GFP_ATOMIC);
		अगर (!*class) अणु
			ret = -ENOMEM;
			जाओ error1;
		पूर्ण

		/* Allocate method table क्रम this management class */
		method = &(*class)->method_table[mgmt_class];
		अगर ((ret = allocate_method_table(method)))
			जाओ error2;
	पूर्ण अन्यथा अणु
		method = &(*class)->method_table[mgmt_class];
		अगर (!*method) अणु
			/* Allocate method table क्रम this management class */
			अगर ((ret = allocate_method_table(method)))
				जाओ error1;
		पूर्ण
	पूर्ण

	/* Now, make sure methods are not alपढ़ोy in use */
	अगर (method_in_use(method, mad_reg_req))
		जाओ error3;

	/* Finally, add in methods being रेजिस्टरed */
	क्रम_each_set_bit(i, mad_reg_req->method_mask, IB_MGMT_MAX_METHODS)
		(*method)->agent[i] = agent_priv;

	वापस 0;

error3:
	/* Remove any methods क्रम this mad agent */
	हटाओ_methods_mad_agent(*method, agent_priv);
	/* Now, check to see अगर there are any methods in use */
	अगर (!check_method_table(*method)) अणु
		/* If not, release management method table */
		kमुक्त(*method);
		*method = शून्य;
	पूर्ण
	ret = -EINVAL;
	जाओ error1;
error2:
	kमुक्त(*class);
	*class = शून्य;
error1:
	वापस ret;
पूर्ण

अटल पूर्णांक add_oui_reg_req(काष्ठा ib_mad_reg_req *mad_reg_req,
			   काष्ठा ib_mad_agent_निजी *agent_priv)
अणु
	काष्ठा ib_mad_port_निजी *port_priv;
	काष्ठा ib_mad_mgmt_venकरोr_class_table **venकरोr_table;
	काष्ठा ib_mad_mgmt_venकरोr_class_table *venकरोr = शून्य;
	काष्ठा ib_mad_mgmt_venकरोr_class *venकरोr_class = शून्य;
	काष्ठा ib_mad_mgmt_method_table **method;
	पूर्णांक i, ret = -ENOMEM;
	u8 vclass;

	/* "New" venकरोr (with OUI) class */
	vclass = venकरोr_class_index(mad_reg_req->mgmt_class);
	port_priv = agent_priv->qp_info->port_priv;
	venकरोr_table = &port_priv->version[
				mad_reg_req->mgmt_class_version].venकरोr;
	अगर (!*venकरोr_table) अणु
		/* Allocate mgmt venकरोr class table क्रम "new" class version */
		venकरोr = kzalloc(माप *venकरोr, GFP_ATOMIC);
		अगर (!venकरोr)
			जाओ error1;

		*venकरोr_table = venकरोr;
	पूर्ण
	अगर (!(*venकरोr_table)->venकरोr_class[vclass]) अणु
		/* Allocate table क्रम this management venकरोr class */
		venकरोr_class = kzalloc(माप *venकरोr_class, GFP_ATOMIC);
		अगर (!venकरोr_class)
			जाओ error2;

		(*venकरोr_table)->venकरोr_class[vclass] = venकरोr_class;
	पूर्ण
	क्रम (i = 0; i < MAX_MGMT_OUI; i++) अणु
		/* Is there matching OUI क्रम this venकरोr class ? */
		अगर (!स_भेद((*venकरोr_table)->venकरोr_class[vclass]->oui[i],
			    mad_reg_req->oui, 3)) अणु
			method = &(*venकरोr_table)->venकरोr_class[
						vclass]->method_table[i];
			अगर (!*method)
				जाओ error3;
			जाओ check_in_use;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < MAX_MGMT_OUI; i++) अणु
		/* OUI slot available ? */
		अगर (!is_venकरोr_oui((*venकरोr_table)->venकरोr_class[
				vclass]->oui[i])) अणु
			method = &(*venकरोr_table)->venकरोr_class[
				vclass]->method_table[i];
			/* Allocate method table क्रम this OUI */
			अगर (!*method) अणु
				ret = allocate_method_table(method);
				अगर (ret)
					जाओ error3;
			पूर्ण
			स_नकल((*venकरोr_table)->venकरोr_class[vclass]->oui[i],
			       mad_reg_req->oui, 3);
			जाओ check_in_use;
		पूर्ण
	पूर्ण
	dev_err(&agent_priv->agent.device->dev, "All OUI slots in use\n");
	जाओ error3;

check_in_use:
	/* Now, make sure methods are not alपढ़ोy in use */
	अगर (method_in_use(method, mad_reg_req))
		जाओ error4;

	/* Finally, add in methods being रेजिस्टरed */
	क्रम_each_set_bit(i, mad_reg_req->method_mask, IB_MGMT_MAX_METHODS)
		(*method)->agent[i] = agent_priv;

	वापस 0;

error4:
	/* Remove any methods क्रम this mad agent */
	हटाओ_methods_mad_agent(*method, agent_priv);
	/* Now, check to see अगर there are any methods in use */
	अगर (!check_method_table(*method)) अणु
		/* If not, release management method table */
		kमुक्त(*method);
		*method = शून्य;
	पूर्ण
	ret = -EINVAL;
error3:
	अगर (venकरोr_class) अणु
		(*venकरोr_table)->venकरोr_class[vclass] = शून्य;
		kमुक्त(venकरोr_class);
	पूर्ण
error2:
	अगर (venकरोr) अणु
		*venकरोr_table = शून्य;
		kमुक्त(venकरोr);
	पूर्ण
error1:
	वापस ret;
पूर्ण

अटल व्योम हटाओ_mad_reg_req(काष्ठा ib_mad_agent_निजी *agent_priv)
अणु
	काष्ठा ib_mad_port_निजी *port_priv;
	काष्ठा ib_mad_mgmt_class_table *class;
	काष्ठा ib_mad_mgmt_method_table *method;
	काष्ठा ib_mad_mgmt_venकरोr_class_table *venकरोr;
	काष्ठा ib_mad_mgmt_venकरोr_class *venकरोr_class;
	पूर्णांक index;
	u8 mgmt_class;

	/*
	 * Was MAD registration request supplied
	 * with original registration ?
	 */
	अगर (!agent_priv->reg_req)
		जाओ out;

	port_priv = agent_priv->qp_info->port_priv;
	mgmt_class = convert_mgmt_class(agent_priv->reg_req->mgmt_class);
	class = port_priv->version[
			agent_priv->reg_req->mgmt_class_version].class;
	अगर (!class)
		जाओ venकरोr_check;

	method = class->method_table[mgmt_class];
	अगर (method) अणु
		/* Remove any methods क्रम this mad agent */
		हटाओ_methods_mad_agent(method, agent_priv);
		/* Now, check to see अगर there are any methods still in use */
		अगर (!check_method_table(method)) अणु
			/* If not, release management method table */
			kमुक्त(method);
			class->method_table[mgmt_class] = शून्य;
			/* Any management classes left ? */
			अगर (!check_class_table(class)) अणु
				/* If not, release management class table */
				kमुक्त(class);
				port_priv->version[
					agent_priv->reg_req->
					mgmt_class_version].class = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

venकरोr_check:
	अगर (!is_venकरोr_class(mgmt_class))
		जाओ out;

	/* normalize mgmt_class to venकरोr range 2 */
	mgmt_class = venकरोr_class_index(agent_priv->reg_req->mgmt_class);
	venकरोr = port_priv->version[
			agent_priv->reg_req->mgmt_class_version].venकरोr;

	अगर (!venकरोr)
		जाओ out;

	venकरोr_class = venकरोr->venकरोr_class[mgmt_class];
	अगर (venकरोr_class) अणु
		index = find_venकरोr_oui(venकरोr_class, agent_priv->reg_req->oui);
		अगर (index < 0)
			जाओ out;
		method = venकरोr_class->method_table[index];
		अगर (method) अणु
			/* Remove any methods क्रम this mad agent */
			हटाओ_methods_mad_agent(method, agent_priv);
			/*
			 * Now, check to see अगर there are
			 * any methods still in use
			 */
			अगर (!check_method_table(method)) अणु
				/* If not, release management method table */
				kमुक्त(method);
				venकरोr_class->method_table[index] = शून्य;
				स_रखो(venकरोr_class->oui[index], 0, 3);
				/* Any OUIs left ? */
				अगर (!check_venकरोr_class(venकरोr_class)) अणु
					/* If not, release venकरोr class table */
					kमुक्त(venकरोr_class);
					venकरोr->venकरोr_class[mgmt_class] = शून्य;
					/* Any other venकरोr classes left ? */
					अगर (!check_venकरोr_table(venकरोr)) अणु
						kमुक्त(venकरोr);
						port_priv->version[
							agent_priv->reg_req->
							mgmt_class_version].
							venकरोr = शून्य;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस;
पूर्ण

अटल काष्ठा ib_mad_agent_निजी *
find_mad_agent(काष्ठा ib_mad_port_निजी *port_priv,
	       स्थिर काष्ठा ib_mad_hdr *mad_hdr)
अणु
	काष्ठा ib_mad_agent_निजी *mad_agent = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (ib_response_mad(mad_hdr)) अणु
		u32 hi_tid;

		/*
		 * Routing is based on high 32 bits of transaction ID
		 * of MAD.
		 */
		hi_tid = be64_to_cpu(mad_hdr->tid) >> 32;
		rcu_पढ़ो_lock();
		mad_agent = xa_load(&ib_mad_clients, hi_tid);
		अगर (mad_agent && !refcount_inc_not_zero(&mad_agent->refcount))
			mad_agent = शून्य;
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		काष्ठा ib_mad_mgmt_class_table *class;
		काष्ठा ib_mad_mgmt_method_table *method;
		काष्ठा ib_mad_mgmt_venकरोr_class_table *venकरोr;
		काष्ठा ib_mad_mgmt_venकरोr_class *venकरोr_class;
		स्थिर काष्ठा ib_venकरोr_mad *venकरोr_mad;
		पूर्णांक index;

		spin_lock_irqsave(&port_priv->reg_lock, flags);
		/*
		 * Routing is based on version, class, and method
		 * For "newer" venकरोr MADs, also based on OUI
		 */
		अगर (mad_hdr->class_version >= MAX_MGMT_VERSION)
			जाओ out;
		अगर (!is_venकरोr_class(mad_hdr->mgmt_class)) अणु
			class = port_priv->version[
					mad_hdr->class_version].class;
			अगर (!class)
				जाओ out;
			अगर (convert_mgmt_class(mad_hdr->mgmt_class) >=
			    ARRAY_SIZE(class->method_table))
				जाओ out;
			method = class->method_table[convert_mgmt_class(
							mad_hdr->mgmt_class)];
			अगर (method)
				mad_agent = method->agent[mad_hdr->method &
							  ~IB_MGMT_METHOD_RESP];
		पूर्ण अन्यथा अणु
			venकरोr = port_priv->version[
					mad_hdr->class_version].venकरोr;
			अगर (!venकरोr)
				जाओ out;
			venकरोr_class = venकरोr->venकरोr_class[venकरोr_class_index(
						mad_hdr->mgmt_class)];
			अगर (!venकरोr_class)
				जाओ out;
			/* Find matching OUI */
			venकरोr_mad = (स्थिर काष्ठा ib_venकरोr_mad *)mad_hdr;
			index = find_venकरोr_oui(venकरोr_class, venकरोr_mad->oui);
			अगर (index == -1)
				जाओ out;
			method = venकरोr_class->method_table[index];
			अगर (method) अणु
				mad_agent = method->agent[mad_hdr->method &
							  ~IB_MGMT_METHOD_RESP];
			पूर्ण
		पूर्ण
		अगर (mad_agent)
			refcount_inc(&mad_agent->refcount);
out:
		spin_unlock_irqrestore(&port_priv->reg_lock, flags);
	पूर्ण

	अगर (mad_agent && !mad_agent->agent.recv_handler) अणु
		dev_notice(&port_priv->device->dev,
			   "No receive handler for client %p on port %u\n",
			   &mad_agent->agent, port_priv->port_num);
		deref_mad_agent(mad_agent);
		mad_agent = शून्य;
	पूर्ण

	वापस mad_agent;
पूर्ण

अटल पूर्णांक validate_mad(स्थिर काष्ठा ib_mad_hdr *mad_hdr,
			स्थिर काष्ठा ib_mad_qp_info *qp_info,
			bool opa)
अणु
	पूर्णांक valid = 0;
	u32 qp_num = qp_info->qp->qp_num;

	/* Make sure MAD base version is understood */
	अगर (mad_hdr->base_version != IB_MGMT_BASE_VERSION &&
	    (!opa || mad_hdr->base_version != OPA_MGMT_BASE_VERSION)) अणु
		pr_err("MAD received with unsupported base version %d %s\n",
		       mad_hdr->base_version, opa ? "(opa)" : "");
		जाओ out;
	पूर्ण

	/* Filter SMI packets sent to other than QP0 */
	अगर ((mad_hdr->mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED) ||
	    (mad_hdr->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)) अणु
		अगर (qp_num == 0)
			valid = 1;
	पूर्ण अन्यथा अणु
		/* CM attributes other than ClassPortInfo only use Send method */
		अगर ((mad_hdr->mgmt_class == IB_MGMT_CLASS_CM) &&
		    (mad_hdr->attr_id != IB_MGMT_CLASSPORTINFO_ATTR_ID) &&
		    (mad_hdr->method != IB_MGMT_METHOD_SEND))
			जाओ out;
		/* Filter GSI packets sent to QP0 */
		अगर (qp_num != 0)
			valid = 1;
	पूर्ण

out:
	वापस valid;
पूर्ण

अटल पूर्णांक is_rmpp_data_mad(स्थिर काष्ठा ib_mad_agent_निजी *mad_agent_priv,
			    स्थिर काष्ठा ib_mad_hdr *mad_hdr)
अणु
	काष्ठा ib_rmpp_mad *rmpp_mad;

	rmpp_mad = (काष्ठा ib_rmpp_mad *)mad_hdr;
	वापस !mad_agent_priv->agent.rmpp_version ||
		!ib_mad_kernel_rmpp_agent(&mad_agent_priv->agent) ||
		!(ib_get_rmpp_flags(&rmpp_mad->rmpp_hdr) &
				    IB_MGMT_RMPP_FLAG_ACTIVE) ||
		(rmpp_mad->rmpp_hdr.rmpp_type == IB_MGMT_RMPP_TYPE_DATA);
पूर्ण

अटल अंतरभूत पूर्णांक rcv_has_same_class(स्थिर काष्ठा ib_mad_send_wr_निजी *wr,
				     स्थिर काष्ठा ib_mad_recv_wc *rwc)
अणु
	वापस ((काष्ठा ib_mad_hdr *)(wr->send_buf.mad))->mgmt_class ==
		rwc->recv_buf.mad->mad_hdr.mgmt_class;
पूर्ण

अटल अंतरभूत पूर्णांक
rcv_has_same_gid(स्थिर काष्ठा ib_mad_agent_निजी *mad_agent_priv,
		 स्थिर काष्ठा ib_mad_send_wr_निजी *wr,
		 स्थिर काष्ठा ib_mad_recv_wc *rwc)
अणु
	काष्ठा rdma_ah_attr attr;
	u8 send_resp, rcv_resp;
	जोड़ ib_gid sgid;
	काष्ठा ib_device *device = mad_agent_priv->agent.device;
	u32 port_num = mad_agent_priv->agent.port_num;
	u8 lmc;
	bool has_grh;

	send_resp = ib_response_mad((काष्ठा ib_mad_hdr *)wr->send_buf.mad);
	rcv_resp = ib_response_mad(&rwc->recv_buf.mad->mad_hdr);

	अगर (send_resp == rcv_resp)
		/* both requests, or both responses. GIDs dअगरferent */
		वापस 0;

	अगर (rdma_query_ah(wr->send_buf.ah, &attr))
		/* Assume not equal, to aव्योम false positives. */
		वापस 0;

	has_grh = !!(rdma_ah_get_ah_flags(&attr) & IB_AH_GRH);
	अगर (has_grh != !!(rwc->wc->wc_flags & IB_WC_GRH))
		/* one has GID, other करोes not.  Assume dअगरferent */
		वापस 0;

	अगर (!send_resp && rcv_resp) अणु
		/* is request/response. */
		अगर (!has_grh) अणु
			अगर (ib_get_cached_lmc(device, port_num, &lmc))
				वापस 0;
			वापस (!lmc || !((rdma_ah_get_path_bits(&attr) ^
					   rwc->wc->dlid_path_bits) &
					  ((1 << lmc) - 1)));
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा ib_global_route *grh =
					rdma_ah_पढ़ो_grh(&attr);

			अगर (rdma_query_gid(device, port_num,
					   grh->sgid_index, &sgid))
				वापस 0;
			वापस !स_भेद(sgid.raw, rwc->recv_buf.grh->dgid.raw,
				       16);
		पूर्ण
	पूर्ण

	अगर (!has_grh)
		वापस rdma_ah_get_dlid(&attr) == rwc->wc->slid;
	अन्यथा
		वापस !स_भेद(rdma_ah_पढ़ो_grh(&attr)->dgid.raw,
			       rwc->recv_buf.grh->sgid.raw,
			       16);
पूर्ण

अटल अंतरभूत पूर्णांक is_direct(u8 class)
अणु
	वापस (class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE);
पूर्ण

काष्ठा ib_mad_send_wr_निजी*
ib_find_send_mad(स्थिर काष्ठा ib_mad_agent_निजी *mad_agent_priv,
		 स्थिर काष्ठा ib_mad_recv_wc *wc)
अणु
	काष्ठा ib_mad_send_wr_निजी *wr;
	स्थिर काष्ठा ib_mad_hdr *mad_hdr;

	mad_hdr = &wc->recv_buf.mad->mad_hdr;

	list_क्रम_each_entry(wr, &mad_agent_priv->रुको_list, agent_list) अणु
		अगर ((wr->tid == mad_hdr->tid) &&
		    rcv_has_same_class(wr, wc) &&
		    /*
		     * Don't check GID क्रम direct routed MADs.
		     * These might have permissive LIDs.
		     */
		    (is_direct(mad_hdr->mgmt_class) ||
		     rcv_has_same_gid(mad_agent_priv, wr, wc)))
			वापस (wr->status == IB_WC_SUCCESS) ? wr : शून्य;
	पूर्ण

	/*
	 * It's possible to receive the response before we've
	 * been notअगरied that the send has completed
	 */
	list_क्रम_each_entry(wr, &mad_agent_priv->send_list, agent_list) अणु
		अगर (is_rmpp_data_mad(mad_agent_priv, wr->send_buf.mad) &&
		    wr->tid == mad_hdr->tid &&
		    wr->समयout &&
		    rcv_has_same_class(wr, wc) &&
		    /*
		     * Don't check GID क्रम direct routed MADs.
		     * These might have permissive LIDs.
		     */
		    (is_direct(mad_hdr->mgmt_class) ||
		     rcv_has_same_gid(mad_agent_priv, wr, wc)))
			/* Verअगरy request has not been canceled */
			वापस (wr->status == IB_WC_SUCCESS) ? wr : शून्य;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम ib_mark_mad_करोne(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	mad_send_wr->समयout = 0;
	अगर (mad_send_wr->refcount == 1)
		list_move_tail(&mad_send_wr->agent_list,
			      &mad_send_wr->mad_agent_priv->करोne_list);
पूर्ण

अटल व्योम ib_mad_complete_recv(काष्ठा ib_mad_agent_निजी *mad_agent_priv,
				 काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	काष्ठा ib_mad_send_wc mad_send_wc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	INIT_LIST_HEAD(&mad_recv_wc->rmpp_list);
	ret = ib_mad_enक्रमce_security(mad_agent_priv,
				      mad_recv_wc->wc->pkey_index);
	अगर (ret) अणु
		ib_मुक्त_recv_mad(mad_recv_wc);
		deref_mad_agent(mad_agent_priv);
		वापस;
	पूर्ण

	list_add(&mad_recv_wc->recv_buf.list, &mad_recv_wc->rmpp_list);
	अगर (ib_mad_kernel_rmpp_agent(&mad_agent_priv->agent)) अणु
		mad_recv_wc = ib_process_rmpp_recv_wc(mad_agent_priv,
						      mad_recv_wc);
		अगर (!mad_recv_wc) अणु
			deref_mad_agent(mad_agent_priv);
			वापस;
		पूर्ण
	पूर्ण

	/* Complete corresponding request */
	अगर (ib_response_mad(&mad_recv_wc->recv_buf.mad->mad_hdr)) अणु
		spin_lock_irqsave(&mad_agent_priv->lock, flags);
		mad_send_wr = ib_find_send_mad(mad_agent_priv, mad_recv_wc);
		अगर (!mad_send_wr) अणु
			spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
			अगर (!ib_mad_kernel_rmpp_agent(&mad_agent_priv->agent)
			   && ib_is_mad_class_rmpp(mad_recv_wc->recv_buf.mad->mad_hdr.mgmt_class)
			   && (ib_get_rmpp_flags(&((काष्ठा ib_rmpp_mad *)mad_recv_wc->recv_buf.mad)->rmpp_hdr)
					& IB_MGMT_RMPP_FLAG_ACTIVE)) अणु
				/* user rmpp is in effect
				 * and this is an active RMPP MAD
				 */
				mad_agent_priv->agent.recv_handler(
						&mad_agent_priv->agent, शून्य,
						mad_recv_wc);
				deref_mad_agent(mad_agent_priv);
			पूर्ण अन्यथा अणु
				/* not user rmpp, revert to normal behavior and
				 * drop the mad
				 */
				ib_मुक्त_recv_mad(mad_recv_wc);
				deref_mad_agent(mad_agent_priv);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			ib_mark_mad_करोne(mad_send_wr);
			spin_unlock_irqrestore(&mad_agent_priv->lock, flags);

			/* Defined behavior is to complete response beक्रमe request */
			mad_agent_priv->agent.recv_handler(
					&mad_agent_priv->agent,
					&mad_send_wr->send_buf,
					mad_recv_wc);
			deref_mad_agent(mad_agent_priv);

			mad_send_wc.status = IB_WC_SUCCESS;
			mad_send_wc.venकरोr_err = 0;
			mad_send_wc.send_buf = &mad_send_wr->send_buf;
			ib_mad_complete_send_wr(mad_send_wr, &mad_send_wc);
		पूर्ण
	पूर्ण अन्यथा अणु
		mad_agent_priv->agent.recv_handler(&mad_agent_priv->agent, शून्य,
						   mad_recv_wc);
		deref_mad_agent(mad_agent_priv);
	पूर्ण
पूर्ण

अटल क्रमागत smi_action handle_ib_smi(स्थिर काष्ठा ib_mad_port_निजी *port_priv,
				     स्थिर काष्ठा ib_mad_qp_info *qp_info,
				     स्थिर काष्ठा ib_wc *wc,
				     u32 port_num,
				     काष्ठा ib_mad_निजी *recv,
				     काष्ठा ib_mad_निजी *response)
अणु
	क्रमागत smi_क्रमward_action retsmi;
	काष्ठा ib_smp *smp = (काष्ठा ib_smp *)recv->mad;

	trace_ib_mad_handle_ib_smi(smp);

	अगर (smi_handle_dr_smp_recv(smp,
				   rdma_cap_ib_चयन(port_priv->device),
				   port_num,
				   port_priv->device->phys_port_cnt) ==
				   IB_SMI_DISCARD)
		वापस IB_SMI_DISCARD;

	retsmi = smi_check_क्रमward_dr_smp(smp);
	अगर (retsmi == IB_SMI_LOCAL)
		वापस IB_SMI_HANDLE;

	अगर (retsmi == IB_SMI_SEND) अणु /* करोn't क्रमward */
		अगर (smi_handle_dr_smp_send(smp,
					   rdma_cap_ib_चयन(port_priv->device),
					   port_num) == IB_SMI_DISCARD)
			वापस IB_SMI_DISCARD;

		अगर (smi_check_local_smp(smp, port_priv->device) == IB_SMI_DISCARD)
			वापस IB_SMI_DISCARD;
	पूर्ण अन्यथा अगर (rdma_cap_ib_चयन(port_priv->device)) अणु
		/* क्रमward हाल क्रम चयनes */
		स_नकल(response, recv, mad_priv_size(response));
		response->header.recv_wc.wc = &response->header.wc;
		response->header.recv_wc.recv_buf.mad = (काष्ठा ib_mad *)response->mad;
		response->header.recv_wc.recv_buf.grh = &response->grh;

		agent_send_response((स्थिर काष्ठा ib_mad_hdr *)response->mad,
				    &response->grh, wc,
				    port_priv->device,
				    smi_get_fwd_port(smp),
				    qp_info->qp->qp_num,
				    response->mad_size,
				    false);

		वापस IB_SMI_DISCARD;
	पूर्ण
	वापस IB_SMI_HANDLE;
पूर्ण

अटल bool generate_unmatched_resp(स्थिर काष्ठा ib_mad_निजी *recv,
				    काष्ठा ib_mad_निजी *response,
				    माप_प्रकार *resp_len, bool opa)
अणु
	स्थिर काष्ठा ib_mad_hdr *recv_hdr = (स्थिर काष्ठा ib_mad_hdr *)recv->mad;
	काष्ठा ib_mad_hdr *resp_hdr = (काष्ठा ib_mad_hdr *)response->mad;

	अगर (recv_hdr->method == IB_MGMT_METHOD_GET ||
	    recv_hdr->method == IB_MGMT_METHOD_SET) अणु
		स_नकल(response, recv, mad_priv_size(response));
		response->header.recv_wc.wc = &response->header.wc;
		response->header.recv_wc.recv_buf.mad = (काष्ठा ib_mad *)response->mad;
		response->header.recv_wc.recv_buf.grh = &response->grh;
		resp_hdr->method = IB_MGMT_METHOD_GET_RESP;
		resp_hdr->status = cpu_to_be16(IB_MGMT_MAD_STATUS_UNSUPPORTED_METHOD_ATTRIB);
		अगर (recv_hdr->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
			resp_hdr->status |= IB_SMP_सूचीECTION;

		अगर (opa && recv_hdr->base_version == OPA_MGMT_BASE_VERSION) अणु
			अगर (recv_hdr->mgmt_class ==
			    IB_MGMT_CLASS_SUBN_LID_ROUTED ||
			    recv_hdr->mgmt_class ==
			    IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
				*resp_len = opa_get_smp_header_size(
							(काष्ठा opa_smp *)recv->mad);
			अन्यथा
				*resp_len = माप(काष्ठा ib_mad_hdr);
		पूर्ण

		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

अटल क्रमागत smi_action
handle_opa_smi(काष्ठा ib_mad_port_निजी *port_priv,
	       काष्ठा ib_mad_qp_info *qp_info,
	       काष्ठा ib_wc *wc,
	       u32 port_num,
	       काष्ठा ib_mad_निजी *recv,
	       काष्ठा ib_mad_निजी *response)
अणु
	क्रमागत smi_क्रमward_action retsmi;
	काष्ठा opa_smp *smp = (काष्ठा opa_smp *)recv->mad;

	trace_ib_mad_handle_opa_smi(smp);

	अगर (opa_smi_handle_dr_smp_recv(smp,
				   rdma_cap_ib_चयन(port_priv->device),
				   port_num,
				   port_priv->device->phys_port_cnt) ==
				   IB_SMI_DISCARD)
		वापस IB_SMI_DISCARD;

	retsmi = opa_smi_check_क्रमward_dr_smp(smp);
	अगर (retsmi == IB_SMI_LOCAL)
		वापस IB_SMI_HANDLE;

	अगर (retsmi == IB_SMI_SEND) अणु /* करोn't क्रमward */
		अगर (opa_smi_handle_dr_smp_send(smp,
					   rdma_cap_ib_चयन(port_priv->device),
					   port_num) == IB_SMI_DISCARD)
			वापस IB_SMI_DISCARD;

		अगर (opa_smi_check_local_smp(smp, port_priv->device) ==
		    IB_SMI_DISCARD)
			वापस IB_SMI_DISCARD;

	पूर्ण अन्यथा अगर (rdma_cap_ib_चयन(port_priv->device)) अणु
		/* क्रमward हाल क्रम चयनes */
		स_नकल(response, recv, mad_priv_size(response));
		response->header.recv_wc.wc = &response->header.wc;
		response->header.recv_wc.recv_buf.opa_mad =
				(काष्ठा opa_mad *)response->mad;
		response->header.recv_wc.recv_buf.grh = &response->grh;

		agent_send_response((स्थिर काष्ठा ib_mad_hdr *)response->mad,
				    &response->grh, wc,
				    port_priv->device,
				    opa_smi_get_fwd_port(smp),
				    qp_info->qp->qp_num,
				    recv->header.wc.byte_len,
				    true);

		वापस IB_SMI_DISCARD;
	पूर्ण

	वापस IB_SMI_HANDLE;
पूर्ण

अटल क्रमागत smi_action
handle_smi(काष्ठा ib_mad_port_निजी *port_priv,
	   काष्ठा ib_mad_qp_info *qp_info,
	   काष्ठा ib_wc *wc,
	   u32 port_num,
	   काष्ठा ib_mad_निजी *recv,
	   काष्ठा ib_mad_निजी *response,
	   bool opa)
अणु
	काष्ठा ib_mad_hdr *mad_hdr = (काष्ठा ib_mad_hdr *)recv->mad;

	अगर (opa && mad_hdr->base_version == OPA_MGMT_BASE_VERSION &&
	    mad_hdr->class_version == OPA_SM_CLASS_VERSION)
		वापस handle_opa_smi(port_priv, qp_info, wc, port_num, recv,
				      response);

	वापस handle_ib_smi(port_priv, qp_info, wc, port_num, recv, response);
पूर्ण

अटल व्योम ib_mad_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_mad_port_निजी *port_priv = cq->cq_context;
	काष्ठा ib_mad_list_head *mad_list =
		container_of(wc->wr_cqe, काष्ठा ib_mad_list_head, cqe);
	काष्ठा ib_mad_qp_info *qp_info;
	काष्ठा ib_mad_निजी_header *mad_priv_hdr;
	काष्ठा ib_mad_निजी *recv, *response = शून्य;
	काष्ठा ib_mad_agent_निजी *mad_agent;
	u32 port_num;
	पूर्णांक ret = IB_MAD_RESULT_SUCCESS;
	माप_प्रकार mad_size;
	u16 resp_mad_pkey_index = 0;
	bool opa;

	अगर (list_empty_careful(&port_priv->port_list))
		वापस;

	अगर (wc->status != IB_WC_SUCCESS) अणु
		/*
		 * Receive errors indicate that the QP has entered the error
		 * state - error handling/shutकरोwn code will cleanup
		 */
		वापस;
	पूर्ण

	qp_info = mad_list->mad_queue->qp_info;
	dequeue_mad(mad_list);

	opa = rdma_cap_opa_mad(qp_info->port_priv->device,
			       qp_info->port_priv->port_num);

	mad_priv_hdr = container_of(mad_list, काष्ठा ib_mad_निजी_header,
				    mad_list);
	recv = container_of(mad_priv_hdr, काष्ठा ib_mad_निजी, header);
	ib_dma_unmap_single(port_priv->device,
			    recv->header.mapping,
			    mad_priv_dma_size(recv),
			    DMA_FROM_DEVICE);

	/* Setup MAD receive work completion from "normal" work completion */
	recv->header.wc = *wc;
	recv->header.recv_wc.wc = &recv->header.wc;

	अगर (opa && ((काष्ठा ib_mad_hdr *)(recv->mad))->base_version == OPA_MGMT_BASE_VERSION) अणु
		recv->header.recv_wc.mad_len = wc->byte_len - माप(काष्ठा ib_grh);
		recv->header.recv_wc.mad_seg_size = माप(काष्ठा opa_mad);
	पूर्ण अन्यथा अणु
		recv->header.recv_wc.mad_len = माप(काष्ठा ib_mad);
		recv->header.recv_wc.mad_seg_size = माप(काष्ठा ib_mad);
	पूर्ण

	recv->header.recv_wc.recv_buf.mad = (काष्ठा ib_mad *)recv->mad;
	recv->header.recv_wc.recv_buf.grh = &recv->grh;

	/* Validate MAD */
	अगर (!validate_mad((स्थिर काष्ठा ib_mad_hdr *)recv->mad, qp_info, opa))
		जाओ out;

	trace_ib_mad_recv_करोne_handler(qp_info, wc,
				       (काष्ठा ib_mad_hdr *)recv->mad);

	mad_size = recv->mad_size;
	response = alloc_mad_निजी(mad_size, GFP_KERNEL);
	अगर (!response)
		जाओ out;

	अगर (rdma_cap_ib_चयन(port_priv->device))
		port_num = wc->port_num;
	अन्यथा
		port_num = port_priv->port_num;

	अगर (((काष्ठा ib_mad_hdr *)recv->mad)->mgmt_class ==
	    IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) अणु
		अगर (handle_smi(port_priv, qp_info, wc, port_num, recv,
			       response, opa)
		    == IB_SMI_DISCARD)
			जाओ out;
	पूर्ण

	/* Give driver "right of first refusal" on incoming MAD */
	अगर (port_priv->device->ops.process_mad) अणु
		ret = port_priv->device->ops.process_mad(
			port_priv->device, 0, port_priv->port_num, wc,
			&recv->grh, (स्थिर काष्ठा ib_mad *)recv->mad,
			(काष्ठा ib_mad *)response->mad, &mad_size,
			&resp_mad_pkey_index);

		अगर (opa)
			wc->pkey_index = resp_mad_pkey_index;

		अगर (ret & IB_MAD_RESULT_SUCCESS) अणु
			अगर (ret & IB_MAD_RESULT_CONSUMED)
				जाओ out;
			अगर (ret & IB_MAD_RESULT_REPLY) अणु
				agent_send_response((स्थिर काष्ठा ib_mad_hdr *)response->mad,
						    &recv->grh, wc,
						    port_priv->device,
						    port_num,
						    qp_info->qp->qp_num,
						    mad_size, opa);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	mad_agent = find_mad_agent(port_priv, (स्थिर काष्ठा ib_mad_hdr *)recv->mad);
	अगर (mad_agent) अणु
		trace_ib_mad_recv_करोne_agent(mad_agent);
		ib_mad_complete_recv(mad_agent, &recv->header.recv_wc);
		/*
		 * recv is मुक्तd up in error हालs in ib_mad_complete_recv
		 * or via recv_handler in ib_mad_complete_recv()
		 */
		recv = शून्य;
	पूर्ण अन्यथा अगर ((ret & IB_MAD_RESULT_SUCCESS) &&
		   generate_unmatched_resp(recv, response, &mad_size, opa)) अणु
		agent_send_response((स्थिर काष्ठा ib_mad_hdr *)response->mad, &recv->grh, wc,
				    port_priv->device, port_num,
				    qp_info->qp->qp_num, mad_size, opa);
	पूर्ण

out:
	/* Post another receive request क्रम this QP */
	अगर (response) अणु
		ib_mad_post_receive_mads(qp_info, response);
		kमुक्त(recv);
	पूर्ण अन्यथा
		ib_mad_post_receive_mads(qp_info, recv);
पूर्ण

अटल व्योम adjust_समयout(काष्ठा ib_mad_agent_निजी *mad_agent_priv)
अणु
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	अचिन्हित दीर्घ delay;

	अगर (list_empty(&mad_agent_priv->रुको_list)) अणु
		cancel_delayed_work(&mad_agent_priv->समयd_work);
	पूर्ण अन्यथा अणु
		mad_send_wr = list_entry(mad_agent_priv->रुको_list.next,
					 काष्ठा ib_mad_send_wr_निजी,
					 agent_list);

		अगर (समय_after(mad_agent_priv->समयout,
			       mad_send_wr->समयout)) अणु
			mad_agent_priv->समयout = mad_send_wr->समयout;
			delay = mad_send_wr->समयout - jअगरfies;
			अगर ((दीर्घ)delay <= 0)
				delay = 1;
			mod_delayed_work(mad_agent_priv->qp_info->port_priv->wq,
					 &mad_agent_priv->समयd_work, delay);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम रुको_क्रम_response(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;
	काष्ठा ib_mad_send_wr_निजी *temp_mad_send_wr;
	काष्ठा list_head *list_item;
	अचिन्हित दीर्घ delay;

	mad_agent_priv = mad_send_wr->mad_agent_priv;
	list_del(&mad_send_wr->agent_list);

	delay = mad_send_wr->समयout;
	mad_send_wr->समयout += jअगरfies;

	अगर (delay) अणु
		list_क्रम_each_prev(list_item, &mad_agent_priv->रुको_list) अणु
			temp_mad_send_wr = list_entry(list_item,
						काष्ठा ib_mad_send_wr_निजी,
						agent_list);
			अगर (समय_after(mad_send_wr->समयout,
				       temp_mad_send_wr->समयout))
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_item = &mad_agent_priv->रुको_list;
	पूर्ण

	list_add(&mad_send_wr->agent_list, list_item);

	/* Reschedule a work item अगर we have a लघुer समयout */
	अगर (mad_agent_priv->रुको_list.next == &mad_send_wr->agent_list)
		mod_delayed_work(mad_agent_priv->qp_info->port_priv->wq,
				 &mad_agent_priv->समयd_work, delay);
पूर्ण

व्योम ib_reset_mad_समयout(काष्ठा ib_mad_send_wr_निजी *mad_send_wr,
			  अचिन्हित दीर्घ समयout_ms)
अणु
	mad_send_wr->समयout = msecs_to_jअगरfies(समयout_ms);
	रुको_क्रम_response(mad_send_wr);
पूर्ण

/*
 * Process a send work completion
 */
व्योम ib_mad_complete_send_wr(काष्ठा ib_mad_send_wr_निजी *mad_send_wr,
			     काष्ठा ib_mad_send_wc *mad_send_wc)
अणु
	काष्ठा ib_mad_agent_निजी	*mad_agent_priv;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				ret;

	mad_agent_priv = mad_send_wr->mad_agent_priv;
	spin_lock_irqsave(&mad_agent_priv->lock, flags);
	अगर (ib_mad_kernel_rmpp_agent(&mad_agent_priv->agent)) अणु
		ret = ib_process_rmpp_send_wc(mad_send_wr, mad_send_wc);
		अगर (ret == IB_RMPP_RESULT_CONSUMED)
			जाओ करोne;
	पूर्ण अन्यथा
		ret = IB_RMPP_RESULT_UNHANDLED;

	अगर (mad_send_wc->status != IB_WC_SUCCESS &&
	    mad_send_wr->status == IB_WC_SUCCESS) अणु
		mad_send_wr->status = mad_send_wc->status;
		mad_send_wr->refcount -= (mad_send_wr->समयout > 0);
	पूर्ण

	अगर (--mad_send_wr->refcount > 0) अणु
		अगर (mad_send_wr->refcount == 1 && mad_send_wr->समयout &&
		    mad_send_wr->status == IB_WC_SUCCESS) अणु
			रुको_क्रम_response(mad_send_wr);
		पूर्ण
		जाओ करोne;
	पूर्ण

	/* Remove send from MAD agent and notअगरy client of completion */
	list_del(&mad_send_wr->agent_list);
	adjust_समयout(mad_agent_priv);
	spin_unlock_irqrestore(&mad_agent_priv->lock, flags);

	अगर (mad_send_wr->status != IB_WC_SUCCESS)
		mad_send_wc->status = mad_send_wr->status;
	अगर (ret == IB_RMPP_RESULT_INTERNAL)
		ib_rmpp_send_handler(mad_send_wc);
	अन्यथा
		mad_agent_priv->agent.send_handler(&mad_agent_priv->agent,
						   mad_send_wc);

	/* Release reference on agent taken when sending */
	deref_mad_agent(mad_agent_priv);
	वापस;
करोne:
	spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
पूर्ण

अटल व्योम ib_mad_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_mad_port_निजी *port_priv = cq->cq_context;
	काष्ठा ib_mad_list_head *mad_list =
		container_of(wc->wr_cqe, काष्ठा ib_mad_list_head, cqe);
	काष्ठा ib_mad_send_wr_निजी	*mad_send_wr, *queued_send_wr;
	काष्ठा ib_mad_qp_info		*qp_info;
	काष्ठा ib_mad_queue		*send_queue;
	काष्ठा ib_mad_send_wc		mad_send_wc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (list_empty_careful(&port_priv->port_list))
		वापस;

	अगर (wc->status != IB_WC_SUCCESS) अणु
		अगर (!ib_mad_send_error(port_priv, wc))
			वापस;
	पूर्ण

	mad_send_wr = container_of(mad_list, काष्ठा ib_mad_send_wr_निजी,
				   mad_list);
	send_queue = mad_list->mad_queue;
	qp_info = send_queue->qp_info;

	trace_ib_mad_send_करोne_agent(mad_send_wr->mad_agent_priv);
	trace_ib_mad_send_करोne_handler(mad_send_wr, wc);

retry:
	ib_dma_unmap_single(mad_send_wr->send_buf.mad_agent->device,
			    mad_send_wr->header_mapping,
			    mad_send_wr->sg_list[0].length, DMA_TO_DEVICE);
	ib_dma_unmap_single(mad_send_wr->send_buf.mad_agent->device,
			    mad_send_wr->payload_mapping,
			    mad_send_wr->sg_list[1].length, DMA_TO_DEVICE);
	queued_send_wr = शून्य;
	spin_lock_irqsave(&send_queue->lock, flags);
	list_del(&mad_list->list);

	/* Move queued send to the send queue */
	अगर (send_queue->count-- > send_queue->max_active) अणु
		mad_list = container_of(qp_info->overflow_list.next,
					काष्ठा ib_mad_list_head, list);
		queued_send_wr = container_of(mad_list,
					काष्ठा ib_mad_send_wr_निजी,
					mad_list);
		list_move_tail(&mad_list->list, &send_queue->list);
	पूर्ण
	spin_unlock_irqrestore(&send_queue->lock, flags);

	mad_send_wc.send_buf = &mad_send_wr->send_buf;
	mad_send_wc.status = wc->status;
	mad_send_wc.venकरोr_err = wc->venकरोr_err;
	ib_mad_complete_send_wr(mad_send_wr, &mad_send_wc);

	अगर (queued_send_wr) अणु
		trace_ib_mad_send_करोne_resend(queued_send_wr, qp_info);
		ret = ib_post_send(qp_info->qp, &queued_send_wr->send_wr.wr,
				   शून्य);
		अगर (ret) अणु
			dev_err(&port_priv->device->dev,
				"ib_post_send failed: %d\n", ret);
			mad_send_wr = queued_send_wr;
			wc->status = IB_WC_LOC_QP_OP_ERR;
			जाओ retry;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mark_sends_क्रम_retry(काष्ठा ib_mad_qp_info *qp_info)
अणु
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	काष्ठा ib_mad_list_head *mad_list;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp_info->send_queue.lock, flags);
	list_क्रम_each_entry(mad_list, &qp_info->send_queue.list, list) अणु
		mad_send_wr = container_of(mad_list,
					   काष्ठा ib_mad_send_wr_निजी,
					   mad_list);
		mad_send_wr->retry = 1;
	पूर्ण
	spin_unlock_irqrestore(&qp_info->send_queue.lock, flags);
पूर्ण

अटल bool ib_mad_send_error(काष्ठा ib_mad_port_निजी *port_priv,
		काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_mad_list_head *mad_list =
		container_of(wc->wr_cqe, काष्ठा ib_mad_list_head, cqe);
	काष्ठा ib_mad_qp_info *qp_info = mad_list->mad_queue->qp_info;
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	पूर्णांक ret;

	/*
	 * Send errors will transition the QP to SQE - move
	 * QP to RTS and repost flushed work requests
	 */
	mad_send_wr = container_of(mad_list, काष्ठा ib_mad_send_wr_निजी,
				   mad_list);
	अगर (wc->status == IB_WC_WR_FLUSH_ERR) अणु
		अगर (mad_send_wr->retry) अणु
			/* Repost send */
			mad_send_wr->retry = 0;
			trace_ib_mad_error_handler(mad_send_wr, qp_info);
			ret = ib_post_send(qp_info->qp, &mad_send_wr->send_wr.wr,
					   शून्य);
			अगर (!ret)
				वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा ib_qp_attr *attr;

		/* Transition QP to RTS and fail offending send */
		attr = kदो_स्मृति(माप *attr, GFP_KERNEL);
		अगर (attr) अणु
			attr->qp_state = IB_QPS_RTS;
			attr->cur_qp_state = IB_QPS_SQE;
			ret = ib_modअगरy_qp(qp_info->qp, attr,
					   IB_QP_STATE | IB_QP_CUR_STATE);
			kमुक्त(attr);
			अगर (ret)
				dev_err(&port_priv->device->dev,
					"%s - ib_modify_qp to RTS: %d\n",
					__func__, ret);
			अन्यथा
				mark_sends_क्रम_retry(qp_info);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम cancel_mads(काष्ठा ib_mad_agent_निजी *mad_agent_priv)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr, *temp_mad_send_wr;
	काष्ठा ib_mad_send_wc mad_send_wc;
	काष्ठा list_head cancel_list;

	INIT_LIST_HEAD(&cancel_list);

	spin_lock_irqsave(&mad_agent_priv->lock, flags);
	list_क्रम_each_entry_safe(mad_send_wr, temp_mad_send_wr,
				 &mad_agent_priv->send_list, agent_list) अणु
		अगर (mad_send_wr->status == IB_WC_SUCCESS) अणु
			mad_send_wr->status = IB_WC_WR_FLUSH_ERR;
			mad_send_wr->refcount -= (mad_send_wr->समयout > 0);
		पूर्ण
	पूर्ण

	/* Empty रुको list to prevent receives from finding a request */
	list_splice_init(&mad_agent_priv->रुको_list, &cancel_list);
	spin_unlock_irqrestore(&mad_agent_priv->lock, flags);

	/* Report all cancelled requests */
	mad_send_wc.status = IB_WC_WR_FLUSH_ERR;
	mad_send_wc.venकरोr_err = 0;

	list_क्रम_each_entry_safe(mad_send_wr, temp_mad_send_wr,
				 &cancel_list, agent_list) अणु
		mad_send_wc.send_buf = &mad_send_wr->send_buf;
		list_del(&mad_send_wr->agent_list);
		mad_agent_priv->agent.send_handler(&mad_agent_priv->agent,
						   &mad_send_wc);
		deref_mad_agent(mad_agent_priv);
	पूर्ण
पूर्ण

अटल काष्ठा ib_mad_send_wr_निजी*
find_send_wr(काष्ठा ib_mad_agent_निजी *mad_agent_priv,
	     काष्ठा ib_mad_send_buf *send_buf)
अणु
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;

	list_क्रम_each_entry(mad_send_wr, &mad_agent_priv->रुको_list,
			    agent_list) अणु
		अगर (&mad_send_wr->send_buf == send_buf)
			वापस mad_send_wr;
	पूर्ण

	list_क्रम_each_entry(mad_send_wr, &mad_agent_priv->send_list,
			    agent_list) अणु
		अगर (is_rmpp_data_mad(mad_agent_priv,
				     mad_send_wr->send_buf.mad) &&
		    &mad_send_wr->send_buf == send_buf)
			वापस mad_send_wr;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक ib_modअगरy_mad(काष्ठा ib_mad_agent *mad_agent,
		  काष्ठा ib_mad_send_buf *send_buf, u32 समयout_ms)
अणु
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	अचिन्हित दीर्घ flags;
	पूर्णांक active;

	mad_agent_priv = container_of(mad_agent, काष्ठा ib_mad_agent_निजी,
				      agent);
	spin_lock_irqsave(&mad_agent_priv->lock, flags);
	mad_send_wr = find_send_wr(mad_agent_priv, send_buf);
	अगर (!mad_send_wr || mad_send_wr->status != IB_WC_SUCCESS) अणु
		spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
		वापस -EINVAL;
	पूर्ण

	active = (!mad_send_wr->समयout || mad_send_wr->refcount > 1);
	अगर (!समयout_ms) अणु
		mad_send_wr->status = IB_WC_WR_FLUSH_ERR;
		mad_send_wr->refcount -= (mad_send_wr->समयout > 0);
	पूर्ण

	mad_send_wr->send_buf.समयout_ms = समयout_ms;
	अगर (active)
		mad_send_wr->समयout = msecs_to_jअगरfies(समयout_ms);
	अन्यथा
		ib_reset_mad_समयout(mad_send_wr, समयout_ms);

	spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_modअगरy_mad);

व्योम ib_cancel_mad(काष्ठा ib_mad_agent *mad_agent,
		   काष्ठा ib_mad_send_buf *send_buf)
अणु
	ib_modअगरy_mad(mad_agent, send_buf, 0);
पूर्ण
EXPORT_SYMBOL(ib_cancel_mad);

अटल व्योम local_completions(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;
	काष्ठा ib_mad_local_निजी *local;
	काष्ठा ib_mad_agent_निजी *recv_mad_agent;
	अचिन्हित दीर्घ flags;
	पूर्णांक मुक्त_mad;
	काष्ठा ib_wc wc;
	काष्ठा ib_mad_send_wc mad_send_wc;
	bool opa;

	mad_agent_priv =
		container_of(work, काष्ठा ib_mad_agent_निजी, local_work);

	opa = rdma_cap_opa_mad(mad_agent_priv->qp_info->port_priv->device,
			       mad_agent_priv->qp_info->port_priv->port_num);

	spin_lock_irqsave(&mad_agent_priv->lock, flags);
	जबतक (!list_empty(&mad_agent_priv->local_list)) अणु
		local = list_entry(mad_agent_priv->local_list.next,
				   काष्ठा ib_mad_local_निजी,
				   completion_list);
		list_del(&local->completion_list);
		spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
		मुक्त_mad = 0;
		अगर (local->mad_priv) अणु
			u8 base_version;
			recv_mad_agent = local->recv_mad_agent;
			अगर (!recv_mad_agent) अणु
				dev_err(&mad_agent_priv->agent.device->dev,
					"No receive MAD agent for local completion\n");
				मुक्त_mad = 1;
				जाओ local_send_completion;
			पूर्ण

			/*
			 * Defined behavior is to complete response
			 * beक्रमe request
			 */
			build_smp_wc(recv_mad_agent->agent.qp,
				     local->mad_send_wr->send_wr.wr.wr_cqe,
				     be16_to_cpu(IB_LID_PERMISSIVE),
				     local->mad_send_wr->send_wr.pkey_index,
				     recv_mad_agent->agent.port_num, &wc);

			local->mad_priv->header.recv_wc.wc = &wc;

			base_version = ((काष्ठा ib_mad_hdr *)(local->mad_priv->mad))->base_version;
			अगर (opa && base_version == OPA_MGMT_BASE_VERSION) अणु
				local->mad_priv->header.recv_wc.mad_len = local->वापस_wc_byte_len;
				local->mad_priv->header.recv_wc.mad_seg_size = माप(काष्ठा opa_mad);
			पूर्ण अन्यथा अणु
				local->mad_priv->header.recv_wc.mad_len = माप(काष्ठा ib_mad);
				local->mad_priv->header.recv_wc.mad_seg_size = माप(काष्ठा ib_mad);
			पूर्ण

			INIT_LIST_HEAD(&local->mad_priv->header.recv_wc.rmpp_list);
			list_add(&local->mad_priv->header.recv_wc.recv_buf.list,
				 &local->mad_priv->header.recv_wc.rmpp_list);
			local->mad_priv->header.recv_wc.recv_buf.grh = शून्य;
			local->mad_priv->header.recv_wc.recv_buf.mad =
						(काष्ठा ib_mad *)local->mad_priv->mad;
			recv_mad_agent->agent.recv_handler(
						&recv_mad_agent->agent,
						&local->mad_send_wr->send_buf,
						&local->mad_priv->header.recv_wc);
			spin_lock_irqsave(&recv_mad_agent->lock, flags);
			deref_mad_agent(recv_mad_agent);
			spin_unlock_irqrestore(&recv_mad_agent->lock, flags);
		पूर्ण

local_send_completion:
		/* Complete send */
		mad_send_wc.status = IB_WC_SUCCESS;
		mad_send_wc.venकरोr_err = 0;
		mad_send_wc.send_buf = &local->mad_send_wr->send_buf;
		mad_agent_priv->agent.send_handler(&mad_agent_priv->agent,
						   &mad_send_wc);

		spin_lock_irqsave(&mad_agent_priv->lock, flags);
		deref_mad_agent(mad_agent_priv);
		अगर (मुक्त_mad)
			kमुक्त(local->mad_priv);
		kमुक्त(local);
	पूर्ण
	spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
पूर्ण

अटल पूर्णांक retry_send(काष्ठा ib_mad_send_wr_निजी *mad_send_wr)
अणु
	पूर्णांक ret;

	अगर (!mad_send_wr->retries_left)
		वापस -ETIMEDOUT;

	mad_send_wr->retries_left--;
	mad_send_wr->send_buf.retries++;

	mad_send_wr->समयout = msecs_to_jअगरfies(mad_send_wr->send_buf.समयout_ms);

	अगर (ib_mad_kernel_rmpp_agent(&mad_send_wr->mad_agent_priv->agent)) अणु
		ret = ib_retry_rmpp(mad_send_wr);
		चयन (ret) अणु
		हाल IB_RMPP_RESULT_UNHANDLED:
			ret = ib_send_mad(mad_send_wr);
			अवरोध;
		हाल IB_RMPP_RESULT_CONSUMED:
			ret = 0;
			अवरोध;
		शेष:
			ret = -ECOMM;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		ret = ib_send_mad(mad_send_wr);

	अगर (!ret) अणु
		mad_send_wr->refcount++;
		list_add_tail(&mad_send_wr->agent_list,
			      &mad_send_wr->mad_agent_priv->send_list);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम समयout_sends(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_mad_agent_निजी *mad_agent_priv;
	काष्ठा ib_mad_send_wr_निजी *mad_send_wr;
	काष्ठा ib_mad_send_wc mad_send_wc;
	अचिन्हित दीर्घ flags, delay;

	mad_agent_priv = container_of(work, काष्ठा ib_mad_agent_निजी,
				      समयd_work.work);
	mad_send_wc.venकरोr_err = 0;

	spin_lock_irqsave(&mad_agent_priv->lock, flags);
	जबतक (!list_empty(&mad_agent_priv->रुको_list)) अणु
		mad_send_wr = list_entry(mad_agent_priv->रुको_list.next,
					 काष्ठा ib_mad_send_wr_निजी,
					 agent_list);

		अगर (समय_after(mad_send_wr->समयout, jअगरfies)) अणु
			delay = mad_send_wr->समयout - jअगरfies;
			अगर ((दीर्घ)delay <= 0)
				delay = 1;
			queue_delayed_work(mad_agent_priv->qp_info->
					   port_priv->wq,
					   &mad_agent_priv->समयd_work, delay);
			अवरोध;
		पूर्ण

		list_del(&mad_send_wr->agent_list);
		अगर (mad_send_wr->status == IB_WC_SUCCESS &&
		    !retry_send(mad_send_wr))
			जारी;

		spin_unlock_irqrestore(&mad_agent_priv->lock, flags);

		अगर (mad_send_wr->status == IB_WC_SUCCESS)
			mad_send_wc.status = IB_WC_RESP_TIMEOUT_ERR;
		अन्यथा
			mad_send_wc.status = mad_send_wr->status;
		mad_send_wc.send_buf = &mad_send_wr->send_buf;
		mad_agent_priv->agent.send_handler(&mad_agent_priv->agent,
						   &mad_send_wc);

		deref_mad_agent(mad_agent_priv);
		spin_lock_irqsave(&mad_agent_priv->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
पूर्ण

/*
 * Allocate receive MADs and post receive WRs क्रम them
 */
अटल पूर्णांक ib_mad_post_receive_mads(काष्ठा ib_mad_qp_info *qp_info,
				    काष्ठा ib_mad_निजी *mad)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक post, ret;
	काष्ठा ib_mad_निजी *mad_priv;
	काष्ठा ib_sge sg_list;
	काष्ठा ib_recv_wr recv_wr;
	काष्ठा ib_mad_queue *recv_queue = &qp_info->recv_queue;

	/* Initialize common scatter list fields */
	sg_list.lkey = qp_info->port_priv->pd->local_dma_lkey;

	/* Initialize common receive WR fields */
	recv_wr.next = शून्य;
	recv_wr.sg_list = &sg_list;
	recv_wr.num_sge = 1;

	करो अणु
		/* Allocate and map receive buffer */
		अगर (mad) अणु
			mad_priv = mad;
			mad = शून्य;
		पूर्ण अन्यथा अणु
			mad_priv = alloc_mad_निजी(port_mad_size(qp_info->port_priv),
						     GFP_ATOMIC);
			अगर (!mad_priv) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
		पूर्ण
		sg_list.length = mad_priv_dma_size(mad_priv);
		sg_list.addr = ib_dma_map_single(qp_info->port_priv->device,
						 &mad_priv->grh,
						 mad_priv_dma_size(mad_priv),
						 DMA_FROM_DEVICE);
		अगर (unlikely(ib_dma_mapping_error(qp_info->port_priv->device,
						  sg_list.addr))) अणु
			kमुक्त(mad_priv);
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		mad_priv->header.mapping = sg_list.addr;
		mad_priv->header.mad_list.mad_queue = recv_queue;
		mad_priv->header.mad_list.cqe.करोne = ib_mad_recv_करोne;
		recv_wr.wr_cqe = &mad_priv->header.mad_list.cqe;

		/* Post receive WR */
		spin_lock_irqsave(&recv_queue->lock, flags);
		post = (++recv_queue->count < recv_queue->max_active);
		list_add_tail(&mad_priv->header.mad_list.list, &recv_queue->list);
		spin_unlock_irqrestore(&recv_queue->lock, flags);
		ret = ib_post_recv(qp_info->qp, &recv_wr, शून्य);
		अगर (ret) अणु
			spin_lock_irqsave(&recv_queue->lock, flags);
			list_del(&mad_priv->header.mad_list.list);
			recv_queue->count--;
			spin_unlock_irqrestore(&recv_queue->lock, flags);
			ib_dma_unmap_single(qp_info->port_priv->device,
					    mad_priv->header.mapping,
					    mad_priv_dma_size(mad_priv),
					    DMA_FROM_DEVICE);
			kमुक्त(mad_priv);
			dev_err(&qp_info->port_priv->device->dev,
				"ib_post_recv failed: %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (post);

	वापस ret;
पूर्ण

/*
 * Return all the posted receive MADs
 */
अटल व्योम cleanup_recv_queue(काष्ठा ib_mad_qp_info *qp_info)
अणु
	काष्ठा ib_mad_निजी_header *mad_priv_hdr;
	काष्ठा ib_mad_निजी *recv;
	काष्ठा ib_mad_list_head *mad_list;

	अगर (!qp_info->qp)
		वापस;

	जबतक (!list_empty(&qp_info->recv_queue.list)) अणु

		mad_list = list_entry(qp_info->recv_queue.list.next,
				      काष्ठा ib_mad_list_head, list);
		mad_priv_hdr = container_of(mad_list,
					    काष्ठा ib_mad_निजी_header,
					    mad_list);
		recv = container_of(mad_priv_hdr, काष्ठा ib_mad_निजी,
				    header);

		/* Remove from posted receive MAD list */
		list_del(&mad_list->list);

		ib_dma_unmap_single(qp_info->port_priv->device,
				    recv->header.mapping,
				    mad_priv_dma_size(recv),
				    DMA_FROM_DEVICE);
		kमुक्त(recv);
	पूर्ण

	qp_info->recv_queue.count = 0;
पूर्ण

/*
 * Start the port
 */
अटल पूर्णांक ib_mad_port_start(काष्ठा ib_mad_port_निजी *port_priv)
अणु
	पूर्णांक ret, i;
	काष्ठा ib_qp_attr *attr;
	काष्ठा ib_qp *qp;
	u16 pkey_index;

	attr = kदो_स्मृति(माप *attr, GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	ret = ib_find_pkey(port_priv->device, port_priv->port_num,
			   IB_DEFAULT_PKEY_FULL, &pkey_index);
	अगर (ret)
		pkey_index = 0;

	क्रम (i = 0; i < IB_MAD_QPS_CORE; i++) अणु
		qp = port_priv->qp_info[i].qp;
		अगर (!qp)
			जारी;

		/*
		 * PKey index क्रम QP1 is irrelevant but
		 * one is needed क्रम the Reset to Init transition
		 */
		attr->qp_state = IB_QPS_INIT;
		attr->pkey_index = pkey_index;
		attr->qkey = (qp->qp_num == 0) ? 0 : IB_QP1_QKEY;
		ret = ib_modअगरy_qp(qp, attr, IB_QP_STATE |
					     IB_QP_PKEY_INDEX | IB_QP_QKEY);
		अगर (ret) अणु
			dev_err(&port_priv->device->dev,
				"Couldn't change QP%d state to INIT: %d\n",
				i, ret);
			जाओ out;
		पूर्ण

		attr->qp_state = IB_QPS_RTR;
		ret = ib_modअगरy_qp(qp, attr, IB_QP_STATE);
		अगर (ret) अणु
			dev_err(&port_priv->device->dev,
				"Couldn't change QP%d state to RTR: %d\n",
				i, ret);
			जाओ out;
		पूर्ण

		attr->qp_state = IB_QPS_RTS;
		attr->sq_psn = IB_MAD_SEND_Q_PSN;
		ret = ib_modअगरy_qp(qp, attr, IB_QP_STATE | IB_QP_SQ_PSN);
		अगर (ret) अणु
			dev_err(&port_priv->device->dev,
				"Couldn't change QP%d state to RTS: %d\n",
				i, ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ib_req_notअगरy_cq(port_priv->cq, IB_CQ_NEXT_COMP);
	अगर (ret) अणु
		dev_err(&port_priv->device->dev,
			"Failed to request completion notification: %d\n",
			ret);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < IB_MAD_QPS_CORE; i++) अणु
		अगर (!port_priv->qp_info[i].qp)
			जारी;

		ret = ib_mad_post_receive_mads(&port_priv->qp_info[i], शून्य);
		अगर (ret) अणु
			dev_err(&port_priv->device->dev,
				"Couldn't post receive WRs\n");
			जाओ out;
		पूर्ण
	पूर्ण
out:
	kमुक्त(attr);
	वापस ret;
पूर्ण

अटल व्योम qp_event_handler(काष्ठा ib_event *event, व्योम *qp_context)
अणु
	काष्ठा ib_mad_qp_info	*qp_info = qp_context;

	/* It's worse than that! He's dead, Jim! */
	dev_err(&qp_info->port_priv->device->dev,
		"Fatal error (%d) on MAD QP (%d)\n",
		event->event, qp_info->qp->qp_num);
पूर्ण

अटल व्योम init_mad_queue(काष्ठा ib_mad_qp_info *qp_info,
			   काष्ठा ib_mad_queue *mad_queue)
अणु
	mad_queue->qp_info = qp_info;
	mad_queue->count = 0;
	spin_lock_init(&mad_queue->lock);
	INIT_LIST_HEAD(&mad_queue->list);
पूर्ण

अटल व्योम init_mad_qp(काष्ठा ib_mad_port_निजी *port_priv,
			काष्ठा ib_mad_qp_info *qp_info)
अणु
	qp_info->port_priv = port_priv;
	init_mad_queue(qp_info, &qp_info->send_queue);
	init_mad_queue(qp_info, &qp_info->recv_queue);
	INIT_LIST_HEAD(&qp_info->overflow_list);
पूर्ण

अटल पूर्णांक create_mad_qp(काष्ठा ib_mad_qp_info *qp_info,
			 क्रमागत ib_qp_type qp_type)
अणु
	काष्ठा ib_qp_init_attr	qp_init_attr;
	पूर्णांक ret;

	स_रखो(&qp_init_attr, 0, माप qp_init_attr);
	qp_init_attr.send_cq = qp_info->port_priv->cq;
	qp_init_attr.recv_cq = qp_info->port_priv->cq;
	qp_init_attr.sq_sig_type = IB_SIGNAL_ALL_WR;
	qp_init_attr.cap.max_send_wr = mad_sendq_size;
	qp_init_attr.cap.max_recv_wr = mad_recvq_size;
	qp_init_attr.cap.max_send_sge = IB_MAD_SEND_REQ_MAX_SG;
	qp_init_attr.cap.max_recv_sge = IB_MAD_RECV_REQ_MAX_SG;
	qp_init_attr.qp_type = qp_type;
	qp_init_attr.port_num = qp_info->port_priv->port_num;
	qp_init_attr.qp_context = qp_info;
	qp_init_attr.event_handler = qp_event_handler;
	qp_info->qp = ib_create_qp(qp_info->port_priv->pd, &qp_init_attr);
	अगर (IS_ERR(qp_info->qp)) अणु
		dev_err(&qp_info->port_priv->device->dev,
			"Couldn't create ib_mad QP%d\n",
			get_spl_qp_index(qp_type));
		ret = PTR_ERR(qp_info->qp);
		जाओ error;
	पूर्ण
	/* Use minimum queue sizes unless the CQ is resized */
	qp_info->send_queue.max_active = mad_sendq_size;
	qp_info->recv_queue.max_active = mad_recvq_size;
	वापस 0;

error:
	वापस ret;
पूर्ण

अटल व्योम destroy_mad_qp(काष्ठा ib_mad_qp_info *qp_info)
अणु
	अगर (!qp_info->qp)
		वापस;

	ib_destroy_qp(qp_info->qp);
पूर्ण

/*
 * Open the port
 * Create the QP, PD, MR, and CQ अगर needed
 */
अटल पूर्णांक ib_mad_port_खोलो(काष्ठा ib_device *device,
			    u32 port_num)
अणु
	पूर्णांक ret, cq_size;
	काष्ठा ib_mad_port_निजी *port_priv;
	अचिन्हित दीर्घ flags;
	अक्षर name[माप "ib_mad123"];
	पूर्णांक has_smi;

	अगर (WARN_ON(rdma_max_mad_size(device, port_num) < IB_MGMT_MAD_SIZE))
		वापस -EFAULT;

	अगर (WARN_ON(rdma_cap_opa_mad(device, port_num) &&
		    rdma_max_mad_size(device, port_num) < OPA_MGMT_MAD_SIZE))
		वापस -EFAULT;

	/* Create new device info */
	port_priv = kzalloc(माप *port_priv, GFP_KERNEL);
	अगर (!port_priv)
		वापस -ENOMEM;

	port_priv->device = device;
	port_priv->port_num = port_num;
	spin_lock_init(&port_priv->reg_lock);
	init_mad_qp(port_priv, &port_priv->qp_info[0]);
	init_mad_qp(port_priv, &port_priv->qp_info[1]);

	cq_size = mad_sendq_size + mad_recvq_size;
	has_smi = rdma_cap_ib_smi(device, port_num);
	अगर (has_smi)
		cq_size *= 2;

	port_priv->pd = ib_alloc_pd(device, 0);
	अगर (IS_ERR(port_priv->pd)) अणु
		dev_err(&device->dev, "Couldn't create ib_mad PD\n");
		ret = PTR_ERR(port_priv->pd);
		जाओ error3;
	पूर्ण

	port_priv->cq = ib_alloc_cq(port_priv->device, port_priv, cq_size, 0,
			IB_POLL_UNBOUND_WORKQUEUE);
	अगर (IS_ERR(port_priv->cq)) अणु
		dev_err(&device->dev, "Couldn't create ib_mad CQ\n");
		ret = PTR_ERR(port_priv->cq);
		जाओ error4;
	पूर्ण

	अगर (has_smi) अणु
		ret = create_mad_qp(&port_priv->qp_info[0], IB_QPT_SMI);
		अगर (ret)
			जाओ error6;
	पूर्ण
	ret = create_mad_qp(&port_priv->qp_info[1], IB_QPT_GSI);
	अगर (ret)
		जाओ error7;

	snम_लिखो(name, माप(name), "ib_mad%u", port_num);
	port_priv->wq = alloc_ordered_workqueue(name, WQ_MEM_RECLAIM);
	अगर (!port_priv->wq) अणु
		ret = -ENOMEM;
		जाओ error8;
	पूर्ण

	spin_lock_irqsave(&ib_mad_port_list_lock, flags);
	list_add_tail(&port_priv->port_list, &ib_mad_port_list);
	spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);

	ret = ib_mad_port_start(port_priv);
	अगर (ret) अणु
		dev_err(&device->dev, "Couldn't start port\n");
		जाओ error9;
	पूर्ण

	वापस 0;

error9:
	spin_lock_irqsave(&ib_mad_port_list_lock, flags);
	list_del_init(&port_priv->port_list);
	spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);

	destroy_workqueue(port_priv->wq);
error8:
	destroy_mad_qp(&port_priv->qp_info[1]);
error7:
	destroy_mad_qp(&port_priv->qp_info[0]);
error6:
	ib_मुक्त_cq(port_priv->cq);
	cleanup_recv_queue(&port_priv->qp_info[1]);
	cleanup_recv_queue(&port_priv->qp_info[0]);
error4:
	ib_dealloc_pd(port_priv->pd);
error3:
	kमुक्त(port_priv);

	वापस ret;
पूर्ण

/*
 * Close the port
 * If there are no classes using the port, मुक्त the port
 * resources (CQ, MR, PD, QP) and हटाओ the port's info काष्ठाure
 */
अटल पूर्णांक ib_mad_port_बंद(काष्ठा ib_device *device, u32 port_num)
अणु
	काष्ठा ib_mad_port_निजी *port_priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ib_mad_port_list_lock, flags);
	port_priv = __ib_get_mad_port(device, port_num);
	अगर (port_priv == शून्य) अणु
		spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);
		dev_err(&device->dev, "Port %u not found\n", port_num);
		वापस -ENODEV;
	पूर्ण
	list_del_init(&port_priv->port_list);
	spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);

	destroy_workqueue(port_priv->wq);
	destroy_mad_qp(&port_priv->qp_info[1]);
	destroy_mad_qp(&port_priv->qp_info[0]);
	ib_मुक्त_cq(port_priv->cq);
	ib_dealloc_pd(port_priv->pd);
	cleanup_recv_queue(&port_priv->qp_info[1]);
	cleanup_recv_queue(&port_priv->qp_info[0]);
	/* XXX: Handle deallocation of MAD registration tables */

	kमुक्त(port_priv);

	वापस 0;
पूर्ण

अटल पूर्णांक ib_mad_init_device(काष्ठा ib_device *device)
अणु
	पूर्णांक start, i;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक ret;

	start = rdma_start_port(device);

	क्रम (i = start; i <= rdma_end_port(device); i++) अणु
		अगर (!rdma_cap_ib_mad(device, i))
			जारी;

		ret = ib_mad_port_खोलो(device, i);
		अगर (ret) अणु
			dev_err(&device->dev, "Couldn't open port %d\n", i);
			जाओ error;
		पूर्ण
		ret = ib_agent_port_खोलो(device, i);
		अगर (ret) अणु
			dev_err(&device->dev,
				"Couldn't open port %d for agents\n", i);
			जाओ error_agent;
		पूर्ण
		count++;
	पूर्ण
	अगर (!count)
		वापस -EOPNOTSUPP;

	वापस 0;

error_agent:
	अगर (ib_mad_port_बंद(device, i))
		dev_err(&device->dev, "Couldn't close port %d\n", i);

error:
	जबतक (--i >= start) अणु
		अगर (!rdma_cap_ib_mad(device, i))
			जारी;

		अगर (ib_agent_port_बंद(device, i))
			dev_err(&device->dev,
				"Couldn't close port %d for agents\n", i);
		अगर (ib_mad_port_बंद(device, i))
			dev_err(&device->dev, "Couldn't close port %d\n", i);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ib_mad_हटाओ_device(काष्ठा ib_device *device, व्योम *client_data)
अणु
	अचिन्हित पूर्णांक i;

	rdma_क्रम_each_port (device, i) अणु
		अगर (!rdma_cap_ib_mad(device, i))
			जारी;

		अगर (ib_agent_port_बंद(device, i))
			dev_err(&device->dev,
				"Couldn't close port %d for agents\n", i);
		अगर (ib_mad_port_बंद(device, i))
			dev_err(&device->dev, "Couldn't close port %d\n", i);
	पूर्ण
पूर्ण

अटल काष्ठा ib_client mad_client = अणु
	.name   = "mad",
	.add = ib_mad_init_device,
	.हटाओ = ib_mad_हटाओ_device
पूर्ण;

पूर्णांक ib_mad_init(व्योम)
अणु
	mad_recvq_size = min(mad_recvq_size, IB_MAD_QP_MAX_SIZE);
	mad_recvq_size = max(mad_recvq_size, IB_MAD_QP_MIN_SIZE);

	mad_sendq_size = min(mad_sendq_size, IB_MAD_QP_MAX_SIZE);
	mad_sendq_size = max(mad_sendq_size, IB_MAD_QP_MIN_SIZE);

	INIT_LIST_HEAD(&ib_mad_port_list);

	अगर (ib_रेजिस्टर_client(&mad_client)) अणु
		pr_err("Couldn't register ib_mad client\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ib_mad_cleanup(व्योम)
अणु
	ib_unरेजिस्टर_client(&mad_client);
पूर्ण
