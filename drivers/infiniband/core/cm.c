<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2004-2007 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004, 2005 Voltaire Corporation.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2019, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/etherdevice.h>

#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_cm.h>
#समावेश "cm_msgs.h"
#समावेश "core_priv.h"
#समावेश "cm_trace.h"

MODULE_AUTHOR("Sean Hefty");
MODULE_DESCRIPTION("InfiniBand CM");
MODULE_LICENSE("Dual BSD/GPL");

अटल स्थिर अक्षर * स्थिर ibcm_rej_reason_strs[] = अणु
	[IB_CM_REJ_NO_QP]			= "no QP",
	[IB_CM_REJ_NO_EEC]			= "no EEC",
	[IB_CM_REJ_NO_RESOURCES]		= "no resources",
	[IB_CM_REJ_TIMEOUT]			= "timeout",
	[IB_CM_REJ_UNSUPPORTED]			= "unsupported",
	[IB_CM_REJ_INVALID_COMM_ID]		= "invalid comm ID",
	[IB_CM_REJ_INVALID_COMM_INSTANCE]	= "invalid comm instance",
	[IB_CM_REJ_INVALID_SERVICE_ID]		= "invalid service ID",
	[IB_CM_REJ_INVALID_TRANSPORT_TYPE]	= "invalid transport type",
	[IB_CM_REJ_STALE_CONN]			= "stale conn",
	[IB_CM_REJ_RDC_NOT_EXIST]		= "RDC not exist",
	[IB_CM_REJ_INVALID_GID]			= "invalid GID",
	[IB_CM_REJ_INVALID_LID]			= "invalid LID",
	[IB_CM_REJ_INVALID_SL]			= "invalid SL",
	[IB_CM_REJ_INVALID_TRAFFIC_CLASS]	= "invalid traffic class",
	[IB_CM_REJ_INVALID_HOP_LIMIT]		= "invalid hop limit",
	[IB_CM_REJ_INVALID_PACKET_RATE]		= "invalid packet rate",
	[IB_CM_REJ_INVALID_ALT_GID]		= "invalid alt GID",
	[IB_CM_REJ_INVALID_ALT_LID]		= "invalid alt LID",
	[IB_CM_REJ_INVALID_ALT_SL]		= "invalid alt SL",
	[IB_CM_REJ_INVALID_ALT_TRAFFIC_CLASS]	= "invalid alt traffic class",
	[IB_CM_REJ_INVALID_ALT_HOP_LIMIT]	= "invalid alt hop limit",
	[IB_CM_REJ_INVALID_ALT_PACKET_RATE]	= "invalid alt packet rate",
	[IB_CM_REJ_PORT_CM_REसूचीECT]		= "port CM redirect",
	[IB_CM_REJ_PORT_REसूचीECT]		= "port redirect",
	[IB_CM_REJ_INVALID_MTU]			= "invalid MTU",
	[IB_CM_REJ_INSUFFICIENT_RESP_RESOURCES]	= "insufficient resp resources",
	[IB_CM_REJ_CONSUMER_DEFINED]		= "consumer defined",
	[IB_CM_REJ_INVALID_RNR_RETRY]		= "invalid RNR retry",
	[IB_CM_REJ_DUPLICATE_LOCAL_COMM_ID]	= "duplicate local comm ID",
	[IB_CM_REJ_INVALID_CLASS_VERSION]	= "invalid class version",
	[IB_CM_REJ_INVALID_FLOW_LABEL]		= "invalid flow label",
	[IB_CM_REJ_INVALID_ALT_FLOW_LABEL]	= "invalid alt flow label",
	[IB_CM_REJ_VENDOR_OPTION_NOT_SUPPORTED] =
		"vendor option is not supported",
पूर्ण;

स्थिर अक्षर *__attribute_स्थिर__ ibcm_reject_msg(पूर्णांक reason)
अणु
	माप_प्रकार index = reason;

	अगर (index < ARRAY_SIZE(ibcm_rej_reason_strs) &&
	    ibcm_rej_reason_strs[index])
		वापस ibcm_rej_reason_strs[index];
	अन्यथा
		वापस "unrecognized reason";
पूर्ण
EXPORT_SYMBOL(ibcm_reject_msg);

काष्ठा cm_id_निजी;
काष्ठा cm_work;
अटल पूर्णांक cm_add_one(काष्ठा ib_device *device);
अटल व्योम cm_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data);
अटल व्योम cm_process_work(काष्ठा cm_id_निजी *cm_id_priv,
			    काष्ठा cm_work *work);
अटल पूर्णांक cm_send_sidr_rep_locked(काष्ठा cm_id_निजी *cm_id_priv,
				   काष्ठा ib_cm_sidr_rep_param *param);
अटल पूर्णांक cm_send_dreq_locked(काष्ठा cm_id_निजी *cm_id_priv,
			       स्थिर व्योम *निजी_data, u8 निजी_data_len);
अटल पूर्णांक cm_send_drep_locked(काष्ठा cm_id_निजी *cm_id_priv,
			       व्योम *निजी_data, u8 निजी_data_len);
अटल पूर्णांक cm_send_rej_locked(काष्ठा cm_id_निजी *cm_id_priv,
			      क्रमागत ib_cm_rej_reason reason, व्योम *ari,
			      u8 ari_length, स्थिर व्योम *निजी_data,
			      u8 निजी_data_len);

अटल काष्ठा ib_client cm_client = अणु
	.name   = "cm",
	.add    = cm_add_one,
	.हटाओ = cm_हटाओ_one
पूर्ण;

अटल काष्ठा ib_cm अणु
	spinlock_t lock;
	काष्ठा list_head device_list;
	rwlock_t device_lock;
	काष्ठा rb_root listen_service_table;
	u64 listen_service_id;
	/* काष्ठा rb_root peer_service_table; toकरो: fix peer to peer */
	काष्ठा rb_root remote_qp_table;
	काष्ठा rb_root remote_id_table;
	काष्ठा rb_root remote_sidr_table;
	काष्ठा xarray local_id_table;
	u32 local_id_next;
	__be32 अक्रमom_id_opeअक्रम;
	काष्ठा list_head समयरुको_list;
	काष्ठा workqueue_काष्ठा *wq;
	/* Sync on cm change port state */
	spinlock_t state_lock;
पूर्ण cm;

/* Counter indexes ordered by attribute ID */
क्रमागत अणु
	CM_REQ_COUNTER,
	CM_MRA_COUNTER,
	CM_REJ_COUNTER,
	CM_REP_COUNTER,
	CM_RTU_COUNTER,
	CM_DREQ_COUNTER,
	CM_DREP_COUNTER,
	CM_SIDR_REQ_COUNTER,
	CM_SIDR_REP_COUNTER,
	CM_LAP_COUNTER,
	CM_APR_COUNTER,
	CM_ATTR_COUNT,
	CM_ATTR_ID_OFFSET = 0x0010,
पूर्ण;

क्रमागत अणु
	CM_XMIT,
	CM_XMIT_RETRIES,
	CM_RECV,
	CM_RECV_DUPLICATES,
	CM_COUNTER_GROUPS
पूर्ण;

अटल अक्षर स्थिर counter_group_names[CM_COUNTER_GROUPS]
				     [माप("cm_rx_duplicates")] = अणु
	"cm_tx_msgs", "cm_tx_retries",
	"cm_rx_msgs", "cm_rx_duplicates"
पूर्ण;

काष्ठा cm_counter_group अणु
	काष्ठा kobject obj;
	atomic_दीर्घ_t counter[CM_ATTR_COUNT];
पूर्ण;

काष्ठा cm_counter_attribute अणु
	काष्ठा attribute attr;
	पूर्णांक index;
पूर्ण;

#घोषणा CM_COUNTER_ATTR(_name, _index) \
काष्ठा cm_counter_attribute cm_##_name##_counter_attr = अणु \
	.attr = अणु .name = __stringअगरy(_name), .mode = 0444 पूर्ण, \
	.index = _index \
पूर्ण

अटल CM_COUNTER_ATTR(req, CM_REQ_COUNTER);
अटल CM_COUNTER_ATTR(mra, CM_MRA_COUNTER);
अटल CM_COUNTER_ATTR(rej, CM_REJ_COUNTER);
अटल CM_COUNTER_ATTR(rep, CM_REP_COUNTER);
अटल CM_COUNTER_ATTR(rtu, CM_RTU_COUNTER);
अटल CM_COUNTER_ATTR(dreq, CM_DREQ_COUNTER);
अटल CM_COUNTER_ATTR(drep, CM_DREP_COUNTER);
अटल CM_COUNTER_ATTR(sidr_req, CM_SIDR_REQ_COUNTER);
अटल CM_COUNTER_ATTR(sidr_rep, CM_SIDR_REP_COUNTER);
अटल CM_COUNTER_ATTR(lap, CM_LAP_COUNTER);
अटल CM_COUNTER_ATTR(apr, CM_APR_COUNTER);

अटल काष्ठा attribute *cm_counter_शेष_attrs[] = अणु
	&cm_req_counter_attr.attr,
	&cm_mra_counter_attr.attr,
	&cm_rej_counter_attr.attr,
	&cm_rep_counter_attr.attr,
	&cm_rtu_counter_attr.attr,
	&cm_dreq_counter_attr.attr,
	&cm_drep_counter_attr.attr,
	&cm_sidr_req_counter_attr.attr,
	&cm_sidr_rep_counter_attr.attr,
	&cm_lap_counter_attr.attr,
	&cm_apr_counter_attr.attr,
	शून्य
पूर्ण;

काष्ठा cm_port अणु
	काष्ठा cm_device *cm_dev;
	काष्ठा ib_mad_agent *mad_agent;
	u32 port_num;
	काष्ठा list_head cm_priv_prim_list;
	काष्ठा list_head cm_priv_altr_list;
	काष्ठा cm_counter_group counter_group[CM_COUNTER_GROUPS];
पूर्ण;

काष्ठा cm_device अणु
	काष्ठा list_head list;
	काष्ठा ib_device *ib_device;
	u8 ack_delay;
	पूर्णांक going_करोwn;
	काष्ठा cm_port *port[];
पूर्ण;

काष्ठा cm_av अणु
	काष्ठा cm_port *port;
	जोड़ ib_gid dgid;
	काष्ठा rdma_ah_attr ah_attr;
	u16 pkey_index;
	u8 समयout;
पूर्ण;

काष्ठा cm_work अणु
	काष्ठा delayed_work work;
	काष्ठा list_head list;
	काष्ठा cm_port *port;
	काष्ठा ib_mad_recv_wc *mad_recv_wc;	/* Received MADs */
	__be32 local_id;			/* Established / समयरुको */
	__be32 remote_id;
	काष्ठा ib_cm_event cm_event;
	काष्ठा sa_path_rec path[];
पूर्ण;

काष्ठा cm_समयरुको_info अणु
	काष्ठा cm_work work;
	काष्ठा list_head list;
	काष्ठा rb_node remote_qp_node;
	काष्ठा rb_node remote_id_node;
	__be64 remote_ca_guid;
	__be32 remote_qpn;
	u8 inserted_remote_qp;
	u8 inserted_remote_id;
पूर्ण;

काष्ठा cm_id_निजी अणु
	काष्ठा ib_cm_id	id;

	काष्ठा rb_node service_node;
	काष्ठा rb_node sidr_id_node;
	spinlock_t lock;	/* Do not acquire inside cm.lock */
	काष्ठा completion comp;
	refcount_t refcount;
	/* Number of clients sharing this ib_cm_id. Only valid क्रम listeners.
	 * Protected by the cm.lock spinlock.
	 */
	पूर्णांक listen_sharecount;
	काष्ठा rcu_head rcu;

	काष्ठा ib_mad_send_buf *msg;
	काष्ठा cm_समयरुको_info *समयरुको_info;
	/* toकरो: use alternate port on send failure */
	काष्ठा cm_av av;
	काष्ठा cm_av alt_av;

	व्योम *निजी_data;
	__be64 tid;
	__be32 local_qpn;
	__be32 remote_qpn;
	क्रमागत ib_qp_type qp_type;
	__be32 sq_psn;
	__be32 rq_psn;
	पूर्णांक समयout_ms;
	क्रमागत ib_mtu path_mtu;
	__be16 pkey;
	u8 निजी_data_len;
	u8 max_cm_retries;
	u8 responder_resources;
	u8 initiator_depth;
	u8 retry_count;
	u8 rnr_retry_count;
	u8 service_समयout;
	u8 target_ack_delay;

	काष्ठा list_head prim_list;
	काष्ठा list_head altr_list;
	/* Indicates that the send port mad is रेजिस्टरed and av is set */
	पूर्णांक prim_send_port_not_पढ़ोy;
	पूर्णांक altr_send_port_not_पढ़ोy;

	काष्ठा list_head work_list;
	atomic_t work_count;

	काष्ठा rdma_ucm_ece ece;
पूर्ण;

अटल व्योम cm_work_handler(काष्ठा work_काष्ठा *work);

अटल अंतरभूत व्योम cm_deref_id(काष्ठा cm_id_निजी *cm_id_priv)
अणु
	अगर (refcount_dec_and_test(&cm_id_priv->refcount))
		complete(&cm_id_priv->comp);
पूर्ण

अटल पूर्णांक cm_alloc_msg(काष्ठा cm_id_निजी *cm_id_priv,
			काष्ठा ib_mad_send_buf **msg)
अणु
	काष्ठा ib_mad_agent *mad_agent;
	काष्ठा ib_mad_send_buf *m;
	काष्ठा ib_ah *ah;
	काष्ठा cm_av *av;
	अचिन्हित दीर्घ flags, flags2;
	पूर्णांक ret = 0;

	/* करोn't let the port to be released till the agent is करोwn */
	spin_lock_irqsave(&cm.state_lock, flags2);
	spin_lock_irqsave(&cm.lock, flags);
	अगर (!cm_id_priv->prim_send_port_not_पढ़ोy)
		av = &cm_id_priv->av;
	अन्यथा अगर (!cm_id_priv->altr_send_port_not_पढ़ोy &&
		 (cm_id_priv->alt_av.port))
		av = &cm_id_priv->alt_av;
	अन्यथा अणु
		pr_info("%s: not valid CM id\n", __func__);
		ret = -ENODEV;
		spin_unlock_irqrestore(&cm.lock, flags);
		जाओ out;
	पूर्ण
	spin_unlock_irqrestore(&cm.lock, flags);
	/* Make sure the port haven't released the mad yet */
	mad_agent = cm_id_priv->av.port->mad_agent;
	अगर (!mad_agent) अणु
		pr_info("%s: not a valid MAD agent\n", __func__);
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	ah = rdma_create_ah(mad_agent->qp->pd, &av->ah_attr, 0);
	अगर (IS_ERR(ah)) अणु
		ret = PTR_ERR(ah);
		जाओ out;
	पूर्ण

	m = ib_create_send_mad(mad_agent, cm_id_priv->id.remote_cm_qpn,
			       av->pkey_index,
			       0, IB_MGMT_MAD_HDR, IB_MGMT_MAD_DATA,
			       GFP_ATOMIC,
			       IB_MGMT_BASE_VERSION);
	अगर (IS_ERR(m)) अणु
		rdma_destroy_ah(ah, 0);
		ret = PTR_ERR(m);
		जाओ out;
	पूर्ण

	/* Timeout set by caller अगर response is expected. */
	m->ah = ah;
	m->retries = cm_id_priv->max_cm_retries;

	refcount_inc(&cm_id_priv->refcount);
	m->context[0] = cm_id_priv;
	*msg = m;

out:
	spin_unlock_irqrestore(&cm.state_lock, flags2);
	वापस ret;
पूर्ण

अटल काष्ठा ib_mad_send_buf *cm_alloc_response_msg_no_ah(काष्ठा cm_port *port,
							   काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	वापस ib_create_send_mad(port->mad_agent, 1, mad_recv_wc->wc->pkey_index,
				  0, IB_MGMT_MAD_HDR, IB_MGMT_MAD_DATA,
				  GFP_ATOMIC,
				  IB_MGMT_BASE_VERSION);
पूर्ण

अटल पूर्णांक cm_create_response_msg_ah(काष्ठा cm_port *port,
				     काष्ठा ib_mad_recv_wc *mad_recv_wc,
				     काष्ठा ib_mad_send_buf *msg)
अणु
	काष्ठा ib_ah *ah;

	ah = ib_create_ah_from_wc(port->mad_agent->qp->pd, mad_recv_wc->wc,
				  mad_recv_wc->recv_buf.grh, port->port_num);
	अगर (IS_ERR(ah))
		वापस PTR_ERR(ah);

	msg->ah = ah;
	वापस 0;
पूर्ण

अटल व्योम cm_मुक्त_msg(काष्ठा ib_mad_send_buf *msg)
अणु
	अगर (msg->ah)
		rdma_destroy_ah(msg->ah, 0);
	अगर (msg->context[0])
		cm_deref_id(msg->context[0]);
	ib_मुक्त_send_mad(msg);
पूर्ण

अटल पूर्णांक cm_alloc_response_msg(काष्ठा cm_port *port,
				 काष्ठा ib_mad_recv_wc *mad_recv_wc,
				 काष्ठा ib_mad_send_buf **msg)
अणु
	काष्ठा ib_mad_send_buf *m;
	पूर्णांक ret;

	m = cm_alloc_response_msg_no_ah(port, mad_recv_wc);
	अगर (IS_ERR(m))
		वापस PTR_ERR(m);

	ret = cm_create_response_msg_ah(port, mad_recv_wc, m);
	अगर (ret) अणु
		cm_मुक्त_msg(m);
		वापस ret;
	पूर्ण

	*msg = m;
	वापस 0;
पूर्ण

अटल व्योम *cm_copy_निजी_data(स्थिर व्योम *निजी_data, u8 निजी_data_len)
अणु
	व्योम *data;

	अगर (!निजी_data || !निजी_data_len)
		वापस शून्य;

	data = kmemdup(निजी_data, निजी_data_len, GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	वापस data;
पूर्ण

अटल व्योम cm_set_निजी_data(काष्ठा cm_id_निजी *cm_id_priv,
				 व्योम *निजी_data, u8 निजी_data_len)
अणु
	अगर (cm_id_priv->निजी_data && cm_id_priv->निजी_data_len)
		kमुक्त(cm_id_priv->निजी_data);

	cm_id_priv->निजी_data = निजी_data;
	cm_id_priv->निजी_data_len = निजी_data_len;
पूर्ण

अटल पूर्णांक cm_init_av_क्रम_lap(काष्ठा cm_port *port, काष्ठा ib_wc *wc,
			      काष्ठा ib_grh *grh, काष्ठा cm_av *av)
अणु
	काष्ठा rdma_ah_attr new_ah_attr;
	पूर्णांक ret;

	av->port = port;
	av->pkey_index = wc->pkey_index;

	/*
	 * av->ah_attr might be initialized based on past wc during incoming
	 * connect request or जबतक sending out connect request. So initialize
	 * a new ah_attr on stack. If initialization fails, old ah_attr is
	 * used क्रम sending any responses. If initialization is successful,
	 * than new ah_attr is used by overwriting old one.
	 */
	ret = ib_init_ah_attr_from_wc(port->cm_dev->ib_device,
				      port->port_num, wc,
				      grh, &new_ah_attr);
	अगर (ret)
		वापस ret;

	rdma_move_ah_attr(&av->ah_attr, &new_ah_attr);
	वापस 0;
पूर्ण

अटल पूर्णांक cm_init_av_क्रम_response(काष्ठा cm_port *port, काष्ठा ib_wc *wc,
				   काष्ठा ib_grh *grh, काष्ठा cm_av *av)
अणु
	av->port = port;
	av->pkey_index = wc->pkey_index;
	वापस ib_init_ah_attr_from_wc(port->cm_dev->ib_device,
				       port->port_num, wc,
				       grh, &av->ah_attr);
पूर्ण

अटल व्योम add_cm_id_to_port_list(काष्ठा cm_id_निजी *cm_id_priv,
				   काष्ठा cm_av *av, काष्ठा cm_port *port)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cm.lock, flags);
	अगर (&cm_id_priv->av == av)
		list_add_tail(&cm_id_priv->prim_list, &port->cm_priv_prim_list);
	अन्यथा अगर (&cm_id_priv->alt_av == av)
		list_add_tail(&cm_id_priv->altr_list, &port->cm_priv_altr_list);
	अन्यथा
		WARN_ON(true);
	spin_unlock_irqrestore(&cm.lock, flags);
पूर्ण

अटल काष्ठा cm_port *
get_cm_port_from_path(काष्ठा sa_path_rec *path, स्थिर काष्ठा ib_gid_attr *attr)
अणु
	काष्ठा cm_device *cm_dev;
	काष्ठा cm_port *port = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (attr) अणु
		पढ़ो_lock_irqsave(&cm.device_lock, flags);
		list_क्रम_each_entry(cm_dev, &cm.device_list, list) अणु
			अगर (cm_dev->ib_device == attr->device) अणु
				port = cm_dev->port[attr->port_num - 1];
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock_irqrestore(&cm.device_lock, flags);
	पूर्ण अन्यथा अणु
		/* SGID attribute can be शून्य in following
		 * conditions.
		 * (a) Alternative path
		 * (b) IB link layer without GRH
		 * (c) LAP send messages
		 */
		पढ़ो_lock_irqsave(&cm.device_lock, flags);
		list_क्रम_each_entry(cm_dev, &cm.device_list, list) अणु
			attr = rdma_find_gid(cm_dev->ib_device,
					     &path->sgid,
					     sa_conv_pathrec_to_gid_type(path),
					     शून्य);
			अगर (!IS_ERR(attr)) अणु
				port = cm_dev->port[attr->port_num - 1];
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock_irqrestore(&cm.device_lock, flags);
		अगर (port)
			rdma_put_gid_attr(attr);
	पूर्ण
	वापस port;
पूर्ण

अटल पूर्णांक cm_init_av_by_path(काष्ठा sa_path_rec *path,
			      स्थिर काष्ठा ib_gid_attr *sgid_attr,
			      काष्ठा cm_av *av,
			      काष्ठा cm_id_निजी *cm_id_priv)
अणु
	काष्ठा rdma_ah_attr new_ah_attr;
	काष्ठा cm_device *cm_dev;
	काष्ठा cm_port *port;
	पूर्णांक ret;

	port = get_cm_port_from_path(path, sgid_attr);
	अगर (!port)
		वापस -EINVAL;
	cm_dev = port->cm_dev;

	ret = ib_find_cached_pkey(cm_dev->ib_device, port->port_num,
				  be16_to_cpu(path->pkey), &av->pkey_index);
	अगर (ret)
		वापस ret;

	av->port = port;

	/*
	 * av->ah_attr might be initialized based on wc or during
	 * request processing समय which might have reference to sgid_attr.
	 * So initialize a new ah_attr on stack.
	 * If initialization fails, old ah_attr is used क्रम sending any
	 * responses. If initialization is successful, than new ah_attr
	 * is used by overwriting the old one. So that right ah_attr
	 * can be used to वापस an error response.
	 */
	ret = ib_init_ah_attr_from_path(cm_dev->ib_device, port->port_num, path,
					&new_ah_attr, sgid_attr);
	अगर (ret)
		वापस ret;

	av->समयout = path->packet_lअगरe_समय + 1;
	add_cm_id_to_port_list(cm_id_priv, av, port);
	rdma_move_ah_attr(&av->ah_attr, &new_ah_attr);
	वापस 0;
पूर्ण

अटल u32 cm_local_id(__be32 local_id)
अणु
	वापस (__क्रमce u32) (local_id ^ cm.अक्रमom_id_opeअक्रम);
पूर्ण

अटल काष्ठा cm_id_निजी *cm_acquire_id(__be32 local_id, __be32 remote_id)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;

	rcu_पढ़ो_lock();
	cm_id_priv = xa_load(&cm.local_id_table, cm_local_id(local_id));
	अगर (!cm_id_priv || cm_id_priv->id.remote_id != remote_id ||
	    !refcount_inc_not_zero(&cm_id_priv->refcount))
		cm_id_priv = शून्य;
	rcu_पढ़ो_unlock();

	वापस cm_id_priv;
पूर्ण

/*
 * Trivial helpers to strip endian annotation and compare; the
 * endianness करोesn't actually matter since we just need a stable
 * order क्रम the RB tree.
 */
अटल पूर्णांक be32_lt(__be32 a, __be32 b)
अणु
	वापस (__क्रमce u32) a < (__क्रमce u32) b;
पूर्ण

अटल पूर्णांक be32_gt(__be32 a, __be32 b)
अणु
	वापस (__क्रमce u32) a > (__क्रमce u32) b;
पूर्ण

अटल पूर्णांक be64_lt(__be64 a, __be64 b)
अणु
	वापस (__क्रमce u64) a < (__क्रमce u64) b;
पूर्ण

अटल पूर्णांक be64_gt(__be64 a, __be64 b)
अणु
	वापस (__क्रमce u64) a > (__क्रमce u64) b;
पूर्ण

/*
 * Inserts a new cm_id_priv पूर्णांकo the listen_service_table. Returns cm_id_priv
 * अगर the new ID was inserted, शून्य अगर it could not be inserted due to a
 * collision, or the existing cm_id_priv पढ़ोy क्रम shared usage.
 */
अटल काष्ठा cm_id_निजी *cm_insert_listen(काष्ठा cm_id_निजी *cm_id_priv,
					      ib_cm_handler shared_handler)
अणु
	काष्ठा rb_node **link = &cm.listen_service_table.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा cm_id_निजी *cur_cm_id_priv;
	__be64 service_id = cm_id_priv->id.service_id;
	__be64 service_mask = cm_id_priv->id.service_mask;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cm.lock, flags);
	जबतक (*link) अणु
		parent = *link;
		cur_cm_id_priv = rb_entry(parent, काष्ठा cm_id_निजी,
					  service_node);
		अगर ((cur_cm_id_priv->id.service_mask & service_id) ==
		    (service_mask & cur_cm_id_priv->id.service_id) &&
		    (cm_id_priv->id.device == cur_cm_id_priv->id.device)) अणु
			/*
			 * Sharing an ib_cm_id with dअगरferent handlers is not
			 * supported
			 */
			अगर (cur_cm_id_priv->id.cm_handler != shared_handler ||
			    cur_cm_id_priv->id.context ||
			    WARN_ON(!cur_cm_id_priv->id.cm_handler)) अणु
				spin_unlock_irqrestore(&cm.lock, flags);
				वापस शून्य;
			पूर्ण
			refcount_inc(&cur_cm_id_priv->refcount);
			cur_cm_id_priv->listen_sharecount++;
			spin_unlock_irqrestore(&cm.lock, flags);
			वापस cur_cm_id_priv;
		पूर्ण

		अगर (cm_id_priv->id.device < cur_cm_id_priv->id.device)
			link = &(*link)->rb_left;
		अन्यथा अगर (cm_id_priv->id.device > cur_cm_id_priv->id.device)
			link = &(*link)->rb_right;
		अन्यथा अगर (be64_lt(service_id, cur_cm_id_priv->id.service_id))
			link = &(*link)->rb_left;
		अन्यथा अगर (be64_gt(service_id, cur_cm_id_priv->id.service_id))
			link = &(*link)->rb_right;
		अन्यथा
			link = &(*link)->rb_right;
	पूर्ण
	cm_id_priv->listen_sharecount++;
	rb_link_node(&cm_id_priv->service_node, parent, link);
	rb_insert_color(&cm_id_priv->service_node, &cm.listen_service_table);
	spin_unlock_irqrestore(&cm.lock, flags);
	वापस cm_id_priv;
पूर्ण

अटल काष्ठा cm_id_निजी *cm_find_listen(काष्ठा ib_device *device,
					    __be64 service_id)
अणु
	काष्ठा rb_node *node = cm.listen_service_table.rb_node;
	काष्ठा cm_id_निजी *cm_id_priv;

	जबतक (node) अणु
		cm_id_priv = rb_entry(node, काष्ठा cm_id_निजी, service_node);
		अगर ((cm_id_priv->id.service_mask & service_id) ==
		     cm_id_priv->id.service_id &&
		    (cm_id_priv->id.device == device)) अणु
			refcount_inc(&cm_id_priv->refcount);
			वापस cm_id_priv;
		पूर्ण
		अगर (device < cm_id_priv->id.device)
			node = node->rb_left;
		अन्यथा अगर (device > cm_id_priv->id.device)
			node = node->rb_right;
		अन्यथा अगर (be64_lt(service_id, cm_id_priv->id.service_id))
			node = node->rb_left;
		अन्यथा अगर (be64_gt(service_id, cm_id_priv->id.service_id))
			node = node->rb_right;
		अन्यथा
			node = node->rb_right;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा cm_समयरुको_info *
cm_insert_remote_id(काष्ठा cm_समयरुको_info *समयरुको_info)
अणु
	काष्ठा rb_node **link = &cm.remote_id_table.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा cm_समयरुको_info *cur_समयरुको_info;
	__be64 remote_ca_guid = समयरुको_info->remote_ca_guid;
	__be32 remote_id = समयरुको_info->work.remote_id;

	जबतक (*link) अणु
		parent = *link;
		cur_समयरुको_info = rb_entry(parent, काष्ठा cm_समयरुको_info,
					     remote_id_node);
		अगर (be32_lt(remote_id, cur_समयरुको_info->work.remote_id))
			link = &(*link)->rb_left;
		अन्यथा अगर (be32_gt(remote_id, cur_समयरुको_info->work.remote_id))
			link = &(*link)->rb_right;
		अन्यथा अगर (be64_lt(remote_ca_guid, cur_समयरुको_info->remote_ca_guid))
			link = &(*link)->rb_left;
		अन्यथा अगर (be64_gt(remote_ca_guid, cur_समयरुको_info->remote_ca_guid))
			link = &(*link)->rb_right;
		अन्यथा
			वापस cur_समयरुको_info;
	पूर्ण
	समयरुको_info->inserted_remote_id = 1;
	rb_link_node(&समयरुको_info->remote_id_node, parent, link);
	rb_insert_color(&समयरुको_info->remote_id_node, &cm.remote_id_table);
	वापस शून्य;
पूर्ण

अटल काष्ठा cm_id_निजी *cm_find_remote_id(__be64 remote_ca_guid,
					       __be32 remote_id)
अणु
	काष्ठा rb_node *node = cm.remote_id_table.rb_node;
	काष्ठा cm_समयरुको_info *समयरुको_info;
	काष्ठा cm_id_निजी *res = शून्य;

	spin_lock_irq(&cm.lock);
	जबतक (node) अणु
		समयरुको_info = rb_entry(node, काष्ठा cm_समयरुको_info,
					 remote_id_node);
		अगर (be32_lt(remote_id, समयरुको_info->work.remote_id))
			node = node->rb_left;
		अन्यथा अगर (be32_gt(remote_id, समयरुको_info->work.remote_id))
			node = node->rb_right;
		अन्यथा अगर (be64_lt(remote_ca_guid, समयरुको_info->remote_ca_guid))
			node = node->rb_left;
		अन्यथा अगर (be64_gt(remote_ca_guid, समयरुको_info->remote_ca_guid))
			node = node->rb_right;
		अन्यथा अणु
			res = cm_acquire_id(समयरुको_info->work.local_id,
					     समयरुको_info->work.remote_id);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&cm.lock);
	वापस res;
पूर्ण

अटल काष्ठा cm_समयरुको_info *
cm_insert_remote_qpn(काष्ठा cm_समयरुको_info *समयरुको_info)
अणु
	काष्ठा rb_node **link = &cm.remote_qp_table.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा cm_समयरुको_info *cur_समयरुको_info;
	__be64 remote_ca_guid = समयरुको_info->remote_ca_guid;
	__be32 remote_qpn = समयरुको_info->remote_qpn;

	जबतक (*link) अणु
		parent = *link;
		cur_समयरुको_info = rb_entry(parent, काष्ठा cm_समयरुको_info,
					     remote_qp_node);
		अगर (be32_lt(remote_qpn, cur_समयरुको_info->remote_qpn))
			link = &(*link)->rb_left;
		अन्यथा अगर (be32_gt(remote_qpn, cur_समयरुको_info->remote_qpn))
			link = &(*link)->rb_right;
		अन्यथा अगर (be64_lt(remote_ca_guid, cur_समयरुको_info->remote_ca_guid))
			link = &(*link)->rb_left;
		अन्यथा अगर (be64_gt(remote_ca_guid, cur_समयरुको_info->remote_ca_guid))
			link = &(*link)->rb_right;
		अन्यथा
			वापस cur_समयरुको_info;
	पूर्ण
	समयरुको_info->inserted_remote_qp = 1;
	rb_link_node(&समयरुको_info->remote_qp_node, parent, link);
	rb_insert_color(&समयरुको_info->remote_qp_node, &cm.remote_qp_table);
	वापस शून्य;
पूर्ण

अटल काष्ठा cm_id_निजी *
cm_insert_remote_sidr(काष्ठा cm_id_निजी *cm_id_priv)
अणु
	काष्ठा rb_node **link = &cm.remote_sidr_table.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा cm_id_निजी *cur_cm_id_priv;
	जोड़ ib_gid *port_gid = &cm_id_priv->av.dgid;
	__be32 remote_id = cm_id_priv->id.remote_id;

	जबतक (*link) अणु
		parent = *link;
		cur_cm_id_priv = rb_entry(parent, काष्ठा cm_id_निजी,
					  sidr_id_node);
		अगर (be32_lt(remote_id, cur_cm_id_priv->id.remote_id))
			link = &(*link)->rb_left;
		अन्यथा अगर (be32_gt(remote_id, cur_cm_id_priv->id.remote_id))
			link = &(*link)->rb_right;
		अन्यथा अणु
			पूर्णांक cmp;
			cmp = स_भेद(port_gid, &cur_cm_id_priv->av.dgid,
				     माप *port_gid);
			अगर (cmp < 0)
				link = &(*link)->rb_left;
			अन्यथा अगर (cmp > 0)
				link = &(*link)->rb_right;
			अन्यथा
				वापस cur_cm_id_priv;
		पूर्ण
	पूर्ण
	rb_link_node(&cm_id_priv->sidr_id_node, parent, link);
	rb_insert_color(&cm_id_priv->sidr_id_node, &cm.remote_sidr_table);
	वापस शून्य;
पूर्ण

अटल काष्ठा cm_id_निजी *cm_alloc_id_priv(काष्ठा ib_device *device,
					      ib_cm_handler cm_handler,
					      व्योम *context)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	u32 id;
	पूर्णांक ret;

	cm_id_priv = kzalloc(माप *cm_id_priv, GFP_KERNEL);
	अगर (!cm_id_priv)
		वापस ERR_PTR(-ENOMEM);

	cm_id_priv->id.state = IB_CM_IDLE;
	cm_id_priv->id.device = device;
	cm_id_priv->id.cm_handler = cm_handler;
	cm_id_priv->id.context = context;
	cm_id_priv->id.remote_cm_qpn = 1;

	RB_CLEAR_NODE(&cm_id_priv->service_node);
	RB_CLEAR_NODE(&cm_id_priv->sidr_id_node);
	spin_lock_init(&cm_id_priv->lock);
	init_completion(&cm_id_priv->comp);
	INIT_LIST_HEAD(&cm_id_priv->work_list);
	INIT_LIST_HEAD(&cm_id_priv->prim_list);
	INIT_LIST_HEAD(&cm_id_priv->altr_list);
	atomic_set(&cm_id_priv->work_count, -1);
	refcount_set(&cm_id_priv->refcount, 1);

	ret = xa_alloc_cyclic(&cm.local_id_table, &id, शून्य, xa_limit_32b,
			      &cm.local_id_next, GFP_KERNEL);
	अगर (ret < 0)
		जाओ error;
	cm_id_priv->id.local_id = (__क्रमce __be32)id ^ cm.अक्रमom_id_opeअक्रम;

	वापस cm_id_priv;

error:
	kमुक्त(cm_id_priv);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Make the ID visible to the MAD handlers and other thपढ़ोs that use the
 * xarray.
 */
अटल व्योम cm_finalize_id(काष्ठा cm_id_निजी *cm_id_priv)
अणु
	xa_store(&cm.local_id_table, cm_local_id(cm_id_priv->id.local_id),
		 cm_id_priv, GFP_ATOMIC);
पूर्ण

काष्ठा ib_cm_id *ib_create_cm_id(काष्ठा ib_device *device,
				 ib_cm_handler cm_handler,
				 व्योम *context)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;

	cm_id_priv = cm_alloc_id_priv(device, cm_handler, context);
	अगर (IS_ERR(cm_id_priv))
		वापस ERR_CAST(cm_id_priv);

	cm_finalize_id(cm_id_priv);
	वापस &cm_id_priv->id;
पूर्ण
EXPORT_SYMBOL(ib_create_cm_id);

अटल काष्ठा cm_work *cm_dequeue_work(काष्ठा cm_id_निजी *cm_id_priv)
अणु
	काष्ठा cm_work *work;

	अगर (list_empty(&cm_id_priv->work_list))
		वापस शून्य;

	work = list_entry(cm_id_priv->work_list.next, काष्ठा cm_work, list);
	list_del(&work->list);
	वापस work;
पूर्ण

अटल व्योम cm_मुक्त_work(काष्ठा cm_work *work)
अणु
	अगर (work->mad_recv_wc)
		ib_मुक्त_recv_mad(work->mad_recv_wc);
	kमुक्त(work);
पूर्ण

अटल व्योम cm_queue_work_unlock(काष्ठा cm_id_निजी *cm_id_priv,
				 काष्ठा cm_work *work)
	__releases(&cm_id_priv->lock)
अणु
	bool immediate;

	/*
	 * To deliver the event to the user callback we have the drop the
	 * spinlock, however, we need to ensure that the user callback is single
	 * thपढ़ोed and receives events in the temporal order. If there are
	 * alपढ़ोy events being processed then thपढ़ो new events onto a list,
	 * the thपढ़ो currently processing will pick them up.
	 */
	immediate = atomic_inc_and_test(&cm_id_priv->work_count);
	अगर (!immediate) अणु
		list_add_tail(&work->list, &cm_id_priv->work_list);
		/*
		 * This routine always consumes incoming reference. Once queued
		 * to the work_list then a reference is held by the thपढ़ो
		 * currently running cm_process_work() and this reference is not
		 * needed.
		 */
		cm_deref_id(cm_id_priv);
	पूर्ण
	spin_unlock_irq(&cm_id_priv->lock);

	अगर (immediate)
		cm_process_work(cm_id_priv, work);
पूर्ण

अटल अंतरभूत पूर्णांक cm_convert_to_ms(पूर्णांक iba_समय)
अणु
	/* approximate conversion to ms from 4.096us x 2^iba_समय */
	वापस 1 << max(iba_समय - 8, 0);
पूर्ण

/*
 * calculate: 4.096x2^ack_समयout = 4.096x2^ack_delay + 2x4.096x2^lअगरe_समय
 * Because of how ack_समयout is stored, adding one द्विगुनs the समयout.
 * To aव्योम large समयouts, select the max(ack_delay, lअगरe_समय + 1), and
 * increment it (round up) only अगर the other is within 50%.
 */
अटल u8 cm_ack_समयout(u8 ca_ack_delay, u8 packet_lअगरe_समय)
अणु
	पूर्णांक ack_समयout = packet_lअगरe_समय + 1;

	अगर (ack_समयout >= ca_ack_delay)
		ack_समयout += (ca_ack_delay >= (ack_समयout - 1));
	अन्यथा
		ack_समयout = ca_ack_delay +
			      (ack_समयout >= (ca_ack_delay - 1));

	वापस min(31, ack_समयout);
पूर्ण

अटल व्योम cm_हटाओ_remote(काष्ठा cm_id_निजी *cm_id_priv)
अणु
	काष्ठा cm_समयरुको_info *समयरुको_info = cm_id_priv->समयरुको_info;

	अगर (समयरुको_info->inserted_remote_id) अणु
		rb_erase(&समयरुको_info->remote_id_node, &cm.remote_id_table);
		समयरुको_info->inserted_remote_id = 0;
	पूर्ण

	अगर (समयरुको_info->inserted_remote_qp) अणु
		rb_erase(&समयरुको_info->remote_qp_node, &cm.remote_qp_table);
		समयरुको_info->inserted_remote_qp = 0;
	पूर्ण
पूर्ण

अटल काष्ठा cm_समयरुको_info *cm_create_समयरुको_info(__be32 local_id)
अणु
	काष्ठा cm_समयरुको_info *समयरुको_info;

	समयरुको_info = kzalloc(माप *समयरुको_info, GFP_KERNEL);
	अगर (!समयरुको_info)
		वापस ERR_PTR(-ENOMEM);

	समयरुको_info->work.local_id = local_id;
	INIT_DELAYED_WORK(&समयरुको_info->work.work, cm_work_handler);
	समयरुको_info->work.cm_event.event = IB_CM_TIMEWAIT_EXIT;
	वापस समयरुको_info;
पूर्ण

अटल व्योम cm_enter_समयरुको(काष्ठा cm_id_निजी *cm_id_priv)
अणु
	पूर्णांक रुको_समय;
	अचिन्हित दीर्घ flags;
	काष्ठा cm_device *cm_dev;

	lockdep_निश्चित_held(&cm_id_priv->lock);

	cm_dev = ib_get_client_data(cm_id_priv->id.device, &cm_client);
	अगर (!cm_dev)
		वापस;

	spin_lock_irqsave(&cm.lock, flags);
	cm_हटाओ_remote(cm_id_priv);
	list_add_tail(&cm_id_priv->समयरुको_info->list, &cm.समयरुको_list);
	spin_unlock_irqrestore(&cm.lock, flags);

	/*
	 * The cm_id could be destroyed by the user beक्रमe we निकास समयरुको.
	 * To protect against this, we search क्रम the cm_id after निकासing
	 * समयरुको beक्रमe notअगरying the user that we've निकासed समयरुको.
	 */
	cm_id_priv->id.state = IB_CM_TIMEWAIT;
	रुको_समय = cm_convert_to_ms(cm_id_priv->av.समयout);

	/* Check अगर the device started its हटाओ_one */
	spin_lock_irqsave(&cm.lock, flags);
	अगर (!cm_dev->going_करोwn)
		queue_delayed_work(cm.wq, &cm_id_priv->समयरुको_info->work.work,
				   msecs_to_jअगरfies(रुको_समय));
	spin_unlock_irqrestore(&cm.lock, flags);

	/*
	 * The समयरुको_info is converted पूर्णांकo a work and माला_लो मुक्तd during
	 * cm_मुक्त_work() in cm_समयरुको_handler().
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा cm_समयरुको_info, work) != 0);
	cm_id_priv->समयरुको_info = शून्य;
पूर्ण

अटल व्योम cm_reset_to_idle(काष्ठा cm_id_निजी *cm_id_priv)
अणु
	अचिन्हित दीर्घ flags;

	lockdep_निश्चित_held(&cm_id_priv->lock);

	cm_id_priv->id.state = IB_CM_IDLE;
	अगर (cm_id_priv->समयरुको_info) अणु
		spin_lock_irqsave(&cm.lock, flags);
		cm_हटाओ_remote(cm_id_priv);
		spin_unlock_irqrestore(&cm.lock, flags);
		kमुक्त(cm_id_priv->समयरुको_info);
		cm_id_priv->समयरुको_info = शून्य;
	पूर्ण
पूर्ण

अटल व्योम cm_destroy_id(काष्ठा ib_cm_id *cm_id, पूर्णांक err)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_work *work;

	cm_id_priv = container_of(cm_id, काष्ठा cm_id_निजी, id);
	spin_lock_irq(&cm_id_priv->lock);
retest:
	चयन (cm_id->state) अणु
	हाल IB_CM_LISTEN:
		spin_lock(&cm.lock);
		अगर (--cm_id_priv->listen_sharecount > 0) अणु
			/* The id is still shared. */
			WARN_ON(refcount_पढ़ो(&cm_id_priv->refcount) == 1);
			spin_unlock(&cm.lock);
			spin_unlock_irq(&cm_id_priv->lock);
			cm_deref_id(cm_id_priv);
			वापस;
		पूर्ण
		cm_id->state = IB_CM_IDLE;
		rb_erase(&cm_id_priv->service_node, &cm.listen_service_table);
		RB_CLEAR_NODE(&cm_id_priv->service_node);
		spin_unlock(&cm.lock);
		अवरोध;
	हाल IB_CM_SIDR_REQ_SENT:
		cm_id->state = IB_CM_IDLE;
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		अवरोध;
	हाल IB_CM_SIDR_REQ_RCVD:
		cm_send_sidr_rep_locked(cm_id_priv,
					&(काष्ठा ib_cm_sidr_rep_param)अणु
						.status = IB_SIDR_REJECT पूर्ण);
		/* cm_send_sidr_rep_locked will not move to IDLE अगर it fails */
		cm_id->state = IB_CM_IDLE;
		अवरोध;
	हाल IB_CM_REQ_SENT:
	हाल IB_CM_MRA_REQ_RCVD:
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		cm_send_rej_locked(cm_id_priv, IB_CM_REJ_TIMEOUT,
				   &cm_id_priv->id.device->node_guid,
				   माप(cm_id_priv->id.device->node_guid),
				   शून्य, 0);
		अवरोध;
	हाल IB_CM_REQ_RCVD:
		अगर (err == -ENOMEM) अणु
			/* Do not reject to allow future retries. */
			cm_reset_to_idle(cm_id_priv);
		पूर्ण अन्यथा अणु
			cm_send_rej_locked(cm_id_priv,
					   IB_CM_REJ_CONSUMER_DEFINED, शून्य, 0,
					   शून्य, 0);
		पूर्ण
		अवरोध;
	हाल IB_CM_REP_SENT:
	हाल IB_CM_MRA_REP_RCVD:
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		cm_send_rej_locked(cm_id_priv, IB_CM_REJ_CONSUMER_DEFINED, शून्य,
				   0, शून्य, 0);
		जाओ retest;
	हाल IB_CM_MRA_REQ_SENT:
	हाल IB_CM_REP_RCVD:
	हाल IB_CM_MRA_REP_SENT:
		cm_send_rej_locked(cm_id_priv, IB_CM_REJ_CONSUMER_DEFINED, शून्य,
				   0, शून्य, 0);
		अवरोध;
	हाल IB_CM_ESTABLISHED:
		अगर (cm_id_priv->qp_type == IB_QPT_XRC_TGT) अणु
			cm_id->state = IB_CM_IDLE;
			अवरोध;
		पूर्ण
		cm_send_dreq_locked(cm_id_priv, शून्य, 0);
		जाओ retest;
	हाल IB_CM_DREQ_SENT:
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		cm_enter_समयरुको(cm_id_priv);
		जाओ retest;
	हाल IB_CM_DREQ_RCVD:
		cm_send_drep_locked(cm_id_priv, शून्य, 0);
		WARN_ON(cm_id->state != IB_CM_TIMEWAIT);
		जाओ retest;
	हाल IB_CM_TIMEWAIT:
		/*
		 * The cm_acquire_id in cm_समयरुको_handler will stop working
		 * once we करो xa_erase below, so just move to idle here क्रम
		 * consistency.
		 */
		cm_id->state = IB_CM_IDLE;
		अवरोध;
	हाल IB_CM_IDLE:
		अवरोध;
	पूर्ण
	WARN_ON(cm_id->state != IB_CM_IDLE);

	spin_lock(&cm.lock);
	/* Required क्रम cleanup paths related cm_req_handler() */
	अगर (cm_id_priv->समयरुको_info) अणु
		cm_हटाओ_remote(cm_id_priv);
		kमुक्त(cm_id_priv->समयरुको_info);
		cm_id_priv->समयरुको_info = शून्य;
	पूर्ण
	अगर (!list_empty(&cm_id_priv->altr_list) &&
	    (!cm_id_priv->altr_send_port_not_पढ़ोy))
		list_del(&cm_id_priv->altr_list);
	अगर (!list_empty(&cm_id_priv->prim_list) &&
	    (!cm_id_priv->prim_send_port_not_पढ़ोy))
		list_del(&cm_id_priv->prim_list);
	WARN_ON(cm_id_priv->listen_sharecount);
	WARN_ON(!RB_EMPTY_NODE(&cm_id_priv->service_node));
	अगर (!RB_EMPTY_NODE(&cm_id_priv->sidr_id_node))
		rb_erase(&cm_id_priv->sidr_id_node, &cm.remote_sidr_table);
	spin_unlock(&cm.lock);
	spin_unlock_irq(&cm_id_priv->lock);

	xa_erase(&cm.local_id_table, cm_local_id(cm_id->local_id));
	cm_deref_id(cm_id_priv);
	रुको_क्रम_completion(&cm_id_priv->comp);
	जबतक ((work = cm_dequeue_work(cm_id_priv)) != शून्य)
		cm_मुक्त_work(work);

	rdma_destroy_ah_attr(&cm_id_priv->av.ah_attr);
	rdma_destroy_ah_attr(&cm_id_priv->alt_av.ah_attr);
	kमुक्त(cm_id_priv->निजी_data);
	kमुक्त_rcu(cm_id_priv, rcu);
पूर्ण

व्योम ib_destroy_cm_id(काष्ठा ib_cm_id *cm_id)
अणु
	cm_destroy_id(cm_id, 0);
पूर्ण
EXPORT_SYMBOL(ib_destroy_cm_id);

अटल पूर्णांक cm_init_listen(काष्ठा cm_id_निजी *cm_id_priv, __be64 service_id,
			  __be64 service_mask)
अणु
	service_mask = service_mask ? service_mask : ~cpu_to_be64(0);
	service_id &= service_mask;
	अगर ((service_id & IB_SERVICE_ID_AGN_MASK) == IB_CM_ASSIGN_SERVICE_ID &&
	    (service_id != IB_CM_ASSIGN_SERVICE_ID))
		वापस -EINVAL;

	अगर (service_id == IB_CM_ASSIGN_SERVICE_ID) अणु
		cm_id_priv->id.service_id = cpu_to_be64(cm.listen_service_id++);
		cm_id_priv->id.service_mask = ~cpu_to_be64(0);
	पूर्ण अन्यथा अणु
		cm_id_priv->id.service_id = service_id;
		cm_id_priv->id.service_mask = service_mask;
	पूर्ण
	वापस 0;
पूर्ण

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
पूर्णांक ib_cm_listen(काष्ठा ib_cm_id *cm_id, __be64 service_id, __be64 service_mask)
अणु
	काष्ठा cm_id_निजी *cm_id_priv =
		container_of(cm_id, काष्ठा cm_id_निजी, id);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	अगर (cm_id_priv->id.state != IB_CM_IDLE) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = cm_init_listen(cm_id_priv, service_id, service_mask);
	अगर (ret)
		जाओ out;

	अगर (!cm_insert_listen(cm_id_priv, शून्य)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	cm_id_priv->id.state = IB_CM_LISTEN;
	ret = 0;

out:
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_cm_listen);

/**
 * ib_cm_insert_listen - Create a new listening ib_cm_id and listen on
 *			 the given service ID.
 *
 * If there's an existing ID listening on that same device and service ID,
 * वापस it.
 *
 * @device: Device associated with the cm_id.  All related communication will
 * be associated with the specअगरied device.
 * @cm_handler: Callback invoked to notअगरy the user of CM events.
 * @service_id: Service identअगरier matched against incoming connection
 *   and service ID resolution requests.  The service ID should be specअगरied
 *   network-byte order.  If set to IB_CM_ASSIGN_SERVICE_ID, the CM will
 *   assign a service ID to the caller.
 *
 * Callers should call ib_destroy_cm_id when करोne with the listener ID.
 */
काष्ठा ib_cm_id *ib_cm_insert_listen(काष्ठा ib_device *device,
				     ib_cm_handler cm_handler,
				     __be64 service_id)
अणु
	काष्ठा cm_id_निजी *listen_id_priv;
	काष्ठा cm_id_निजी *cm_id_priv;
	पूर्णांक err = 0;

	/* Create an ID in advance, since the creation may sleep */
	cm_id_priv = cm_alloc_id_priv(device, cm_handler, शून्य);
	अगर (IS_ERR(cm_id_priv))
		वापस ERR_CAST(cm_id_priv);

	err = cm_init_listen(cm_id_priv, service_id, 0);
	अगर (err)
		वापस ERR_PTR(err);

	spin_lock_irq(&cm_id_priv->lock);
	listen_id_priv = cm_insert_listen(cm_id_priv, cm_handler);
	अगर (listen_id_priv != cm_id_priv) अणु
		spin_unlock_irq(&cm_id_priv->lock);
		ib_destroy_cm_id(&cm_id_priv->id);
		अगर (!listen_id_priv)
			वापस ERR_PTR(-EINVAL);
		वापस &listen_id_priv->id;
	पूर्ण
	cm_id_priv->id.state = IB_CM_LISTEN;
	spin_unlock_irq(&cm_id_priv->lock);

	/*
	 * A listen ID करोes not need to be in the xarray since it करोes not
	 * receive mads, is not placed in the remote_id or remote_qpn rbtree,
	 * and करोes not enter समयरुको.
	 */

	वापस &cm_id_priv->id;
पूर्ण
EXPORT_SYMBOL(ib_cm_insert_listen);

अटल __be64 cm_क्रमm_tid(काष्ठा cm_id_निजी *cm_id_priv)
अणु
	u64 hi_tid, low_tid;

	hi_tid   = ((u64) cm_id_priv->av.port->mad_agent->hi_tid) << 32;
	low_tid  = (u64)cm_id_priv->id.local_id;
	वापस cpu_to_be64(hi_tid | low_tid);
पूर्ण

अटल व्योम cm_क्रमmat_mad_hdr(काष्ठा ib_mad_hdr *hdr,
			      __be16 attr_id, __be64 tid)
अणु
	hdr->base_version  = IB_MGMT_BASE_VERSION;
	hdr->mgmt_class	   = IB_MGMT_CLASS_CM;
	hdr->class_version = IB_CM_CLASS_VERSION;
	hdr->method	   = IB_MGMT_METHOD_SEND;
	hdr->attr_id	   = attr_id;
	hdr->tid	   = tid;
पूर्ण

अटल व्योम cm_क्रमmat_mad_ece_hdr(काष्ठा ib_mad_hdr *hdr, __be16 attr_id,
				  __be64 tid, u32 attr_mod)
अणु
	cm_क्रमmat_mad_hdr(hdr, attr_id, tid);
	hdr->attr_mod = cpu_to_be32(attr_mod);
पूर्ण

अटल व्योम cm_क्रमmat_req(काष्ठा cm_req_msg *req_msg,
			  काष्ठा cm_id_निजी *cm_id_priv,
			  काष्ठा ib_cm_req_param *param)
अणु
	काष्ठा sa_path_rec *pri_path = param->primary_path;
	काष्ठा sa_path_rec *alt_path = param->alternate_path;
	bool pri_ext = false;

	अगर (pri_path->rec_type == SA_PATH_REC_TYPE_OPA)
		pri_ext = opa_is_extended_lid(pri_path->opa.dlid,
					      pri_path->opa.slid);

	cm_क्रमmat_mad_ece_hdr(&req_msg->hdr, CM_REQ_ATTR_ID,
			      cm_क्रमm_tid(cm_id_priv), param->ece.attr_mod);

	IBA_SET(CM_REQ_LOCAL_COMM_ID, req_msg,
		be32_to_cpu(cm_id_priv->id.local_id));
	IBA_SET(CM_REQ_SERVICE_ID, req_msg, be64_to_cpu(param->service_id));
	IBA_SET(CM_REQ_LOCAL_CA_GUID, req_msg,
		be64_to_cpu(cm_id_priv->id.device->node_guid));
	IBA_SET(CM_REQ_LOCAL_QPN, req_msg, param->qp_num);
	IBA_SET(CM_REQ_INITIATOR_DEPTH, req_msg, param->initiator_depth);
	IBA_SET(CM_REQ_REMOTE_CM_RESPONSE_TIMEOUT, req_msg,
		param->remote_cm_response_समयout);
	cm_req_set_qp_type(req_msg, param->qp_type);
	IBA_SET(CM_REQ_END_TO_END_FLOW_CONTROL, req_msg, param->flow_control);
	IBA_SET(CM_REQ_STARTING_PSN, req_msg, param->starting_psn);
	IBA_SET(CM_REQ_LOCAL_CM_RESPONSE_TIMEOUT, req_msg,
		param->local_cm_response_समयout);
	IBA_SET(CM_REQ_PARTITION_KEY, req_msg,
		be16_to_cpu(param->primary_path->pkey));
	IBA_SET(CM_REQ_PATH_PACKET_PAYLOAD_MTU, req_msg,
		param->primary_path->mtu);
	IBA_SET(CM_REQ_MAX_CM_RETRIES, req_msg, param->max_cm_retries);

	अगर (param->qp_type != IB_QPT_XRC_INI) अणु
		IBA_SET(CM_REQ_RESPONDER_RESOURCES, req_msg,
			param->responder_resources);
		IBA_SET(CM_REQ_RETRY_COUNT, req_msg, param->retry_count);
		IBA_SET(CM_REQ_RNR_RETRY_COUNT, req_msg,
			param->rnr_retry_count);
		IBA_SET(CM_REQ_SRQ, req_msg, param->srq);
	पूर्ण

	*IBA_GET_MEM_PTR(CM_REQ_PRIMARY_LOCAL_PORT_GID, req_msg) =
		pri_path->sgid;
	*IBA_GET_MEM_PTR(CM_REQ_PRIMARY_REMOTE_PORT_GID, req_msg) =
		pri_path->dgid;
	अगर (pri_ext) अणु
		IBA_GET_MEM_PTR(CM_REQ_PRIMARY_LOCAL_PORT_GID, req_msg)
			->global.पूर्णांकerface_id =
			OPA_MAKE_ID(be32_to_cpu(pri_path->opa.slid));
		IBA_GET_MEM_PTR(CM_REQ_PRIMARY_REMOTE_PORT_GID, req_msg)
			->global.पूर्णांकerface_id =
			OPA_MAKE_ID(be32_to_cpu(pri_path->opa.dlid));
	पूर्ण
	अगर (pri_path->hop_limit <= 1) अणु
		IBA_SET(CM_REQ_PRIMARY_LOCAL_PORT_LID, req_msg,
			be16_to_cpu(pri_ext ? 0 :
					      htons(ntohl(sa_path_get_slid(
						      pri_path)))));
		IBA_SET(CM_REQ_PRIMARY_REMOTE_PORT_LID, req_msg,
			be16_to_cpu(pri_ext ? 0 :
					      htons(ntohl(sa_path_get_dlid(
						      pri_path)))));
	पूर्ण अन्यथा अणु
		/* Work-around until there's a way to obtain remote LID info */
		IBA_SET(CM_REQ_PRIMARY_LOCAL_PORT_LID, req_msg,
			be16_to_cpu(IB_LID_PERMISSIVE));
		IBA_SET(CM_REQ_PRIMARY_REMOTE_PORT_LID, req_msg,
			be16_to_cpu(IB_LID_PERMISSIVE));
	पूर्ण
	IBA_SET(CM_REQ_PRIMARY_FLOW_LABEL, req_msg,
		be32_to_cpu(pri_path->flow_label));
	IBA_SET(CM_REQ_PRIMARY_PACKET_RATE, req_msg, pri_path->rate);
	IBA_SET(CM_REQ_PRIMARY_TRAFFIC_CLASS, req_msg, pri_path->traffic_class);
	IBA_SET(CM_REQ_PRIMARY_HOP_LIMIT, req_msg, pri_path->hop_limit);
	IBA_SET(CM_REQ_PRIMARY_SL, req_msg, pri_path->sl);
	IBA_SET(CM_REQ_PRIMARY_SUBNET_LOCAL, req_msg,
		(pri_path->hop_limit <= 1));
	IBA_SET(CM_REQ_PRIMARY_LOCAL_ACK_TIMEOUT, req_msg,
		cm_ack_समयout(cm_id_priv->av.port->cm_dev->ack_delay,
			       pri_path->packet_lअगरe_समय));

	अगर (alt_path) अणु
		bool alt_ext = false;

		अगर (alt_path->rec_type == SA_PATH_REC_TYPE_OPA)
			alt_ext = opa_is_extended_lid(alt_path->opa.dlid,
						      alt_path->opa.slid);

		*IBA_GET_MEM_PTR(CM_REQ_ALTERNATE_LOCAL_PORT_GID, req_msg) =
			alt_path->sgid;
		*IBA_GET_MEM_PTR(CM_REQ_ALTERNATE_REMOTE_PORT_GID, req_msg) =
			alt_path->dgid;
		अगर (alt_ext) अणु
			IBA_GET_MEM_PTR(CM_REQ_ALTERNATE_LOCAL_PORT_GID,
					req_msg)
				->global.पूर्णांकerface_id =
				OPA_MAKE_ID(be32_to_cpu(alt_path->opa.slid));
			IBA_GET_MEM_PTR(CM_REQ_ALTERNATE_REMOTE_PORT_GID,
					req_msg)
				->global.पूर्णांकerface_id =
				OPA_MAKE_ID(be32_to_cpu(alt_path->opa.dlid));
		पूर्ण
		अगर (alt_path->hop_limit <= 1) अणु
			IBA_SET(CM_REQ_ALTERNATE_LOCAL_PORT_LID, req_msg,
				be16_to_cpu(
					alt_ext ? 0 :
						  htons(ntohl(sa_path_get_slid(
							  alt_path)))));
			IBA_SET(CM_REQ_ALTERNATE_REMOTE_PORT_LID, req_msg,
				be16_to_cpu(
					alt_ext ? 0 :
						  htons(ntohl(sa_path_get_dlid(
							  alt_path)))));
		पूर्ण अन्यथा अणु
			IBA_SET(CM_REQ_ALTERNATE_LOCAL_PORT_LID, req_msg,
				be16_to_cpu(IB_LID_PERMISSIVE));
			IBA_SET(CM_REQ_ALTERNATE_REMOTE_PORT_LID, req_msg,
				be16_to_cpu(IB_LID_PERMISSIVE));
		पूर्ण
		IBA_SET(CM_REQ_ALTERNATE_FLOW_LABEL, req_msg,
			be32_to_cpu(alt_path->flow_label));
		IBA_SET(CM_REQ_ALTERNATE_PACKET_RATE, req_msg, alt_path->rate);
		IBA_SET(CM_REQ_ALTERNATE_TRAFFIC_CLASS, req_msg,
			alt_path->traffic_class);
		IBA_SET(CM_REQ_ALTERNATE_HOP_LIMIT, req_msg,
			alt_path->hop_limit);
		IBA_SET(CM_REQ_ALTERNATE_SL, req_msg, alt_path->sl);
		IBA_SET(CM_REQ_ALTERNATE_SUBNET_LOCAL, req_msg,
			(alt_path->hop_limit <= 1));
		IBA_SET(CM_REQ_ALTERNATE_LOCAL_ACK_TIMEOUT, req_msg,
			cm_ack_समयout(cm_id_priv->av.port->cm_dev->ack_delay,
				       alt_path->packet_lअगरe_समय));
	पूर्ण
	IBA_SET(CM_REQ_VENDOR_ID, req_msg, param->ece.venकरोr_id);

	अगर (param->निजी_data && param->निजी_data_len)
		IBA_SET_MEM(CM_REQ_PRIVATE_DATA, req_msg, param->निजी_data,
			    param->निजी_data_len);
पूर्ण

अटल पूर्णांक cm_validate_req_param(काष्ठा ib_cm_req_param *param)
अणु
	अगर (!param->primary_path)
		वापस -EINVAL;

	अगर (param->qp_type != IB_QPT_RC && param->qp_type != IB_QPT_UC &&
	    param->qp_type != IB_QPT_XRC_INI)
		वापस -EINVAL;

	अगर (param->निजी_data &&
	    param->निजी_data_len > IB_CM_REQ_PRIVATE_DATA_SIZE)
		वापस -EINVAL;

	अगर (param->alternate_path &&
	    (param->alternate_path->pkey != param->primary_path->pkey ||
	     param->alternate_path->mtu != param->primary_path->mtu))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक ib_send_cm_req(काष्ठा ib_cm_id *cm_id,
		   काष्ठा ib_cm_req_param *param)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_req_msg *req_msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = cm_validate_req_param(param);
	अगर (ret)
		वापस ret;

	/* Verअगरy that we're not in समयरुको. */
	cm_id_priv = container_of(cm_id, काष्ठा cm_id_निजी, id);
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	अगर (cm_id->state != IB_CM_IDLE || WARN_ON(cm_id_priv->समयरुको_info)) अणु
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	cm_id_priv->समयरुको_info = cm_create_समयरुको_info(cm_id_priv->
							    id.local_id);
	अगर (IS_ERR(cm_id_priv->समयरुको_info)) अणु
		ret = PTR_ERR(cm_id_priv->समयरुको_info);
		cm_id_priv->समयरुको_info = शून्य;
		जाओ out;
	पूर्ण

	ret = cm_init_av_by_path(param->primary_path,
				 param->ppath_sgid_attr, &cm_id_priv->av,
				 cm_id_priv);
	अगर (ret)
		जाओ out;
	अगर (param->alternate_path) अणु
		ret = cm_init_av_by_path(param->alternate_path, शून्य,
					 &cm_id_priv->alt_av, cm_id_priv);
		अगर (ret)
			जाओ out;
	पूर्ण
	cm_id->service_id = param->service_id;
	cm_id->service_mask = ~cpu_to_be64(0);
	cm_id_priv->समयout_ms = cm_convert_to_ms(
				    param->primary_path->packet_lअगरe_समय) * 2 +
				 cm_convert_to_ms(
				    param->remote_cm_response_समयout);
	cm_id_priv->max_cm_retries = param->max_cm_retries;
	cm_id_priv->initiator_depth = param->initiator_depth;
	cm_id_priv->responder_resources = param->responder_resources;
	cm_id_priv->retry_count = param->retry_count;
	cm_id_priv->path_mtu = param->primary_path->mtu;
	cm_id_priv->pkey = param->primary_path->pkey;
	cm_id_priv->qp_type = param->qp_type;

	ret = cm_alloc_msg(cm_id_priv, &cm_id_priv->msg);
	अगर (ret)
		जाओ out;

	req_msg = (काष्ठा cm_req_msg *) cm_id_priv->msg->mad;
	cm_क्रमmat_req(req_msg, cm_id_priv, param);
	cm_id_priv->tid = req_msg->hdr.tid;
	cm_id_priv->msg->समयout_ms = cm_id_priv->समयout_ms;
	cm_id_priv->msg->context[1] = (व्योम *) (अचिन्हित दीर्घ) IB_CM_REQ_SENT;

	cm_id_priv->local_qpn = cpu_to_be32(IBA_GET(CM_REQ_LOCAL_QPN, req_msg));
	cm_id_priv->rq_psn = cpu_to_be32(IBA_GET(CM_REQ_STARTING_PSN, req_msg));

	trace_icm_send_req(&cm_id_priv->id);
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	ret = ib_post_send_mad(cm_id_priv->msg, शून्य);
	अगर (ret) अणु
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		जाओ error2;
	पूर्ण
	BUG_ON(cm_id->state != IB_CM_IDLE);
	cm_id->state = IB_CM_REQ_SENT;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस 0;

error2:	cm_मुक्त_msg(cm_id_priv->msg);
out:	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_send_cm_req);

अटल पूर्णांक cm_issue_rej(काष्ठा cm_port *port,
			काष्ठा ib_mad_recv_wc *mad_recv_wc,
			क्रमागत ib_cm_rej_reason reason,
			क्रमागत cm_msg_response msg_rejected,
			व्योम *ari, u8 ari_length)
अणु
	काष्ठा ib_mad_send_buf *msg = शून्य;
	काष्ठा cm_rej_msg *rej_msg, *rcv_msg;
	पूर्णांक ret;

	ret = cm_alloc_response_msg(port, mad_recv_wc, &msg);
	अगर (ret)
		वापस ret;

	/* We just need common CM header inक्रमmation.  Cast to any message. */
	rcv_msg = (काष्ठा cm_rej_msg *) mad_recv_wc->recv_buf.mad;
	rej_msg = (काष्ठा cm_rej_msg *) msg->mad;

	cm_क्रमmat_mad_hdr(&rej_msg->hdr, CM_REJ_ATTR_ID, rcv_msg->hdr.tid);
	IBA_SET(CM_REJ_REMOTE_COMM_ID, rej_msg,
		IBA_GET(CM_REJ_LOCAL_COMM_ID, rcv_msg));
	IBA_SET(CM_REJ_LOCAL_COMM_ID, rej_msg,
		IBA_GET(CM_REJ_REMOTE_COMM_ID, rcv_msg));
	IBA_SET(CM_REJ_MESSAGE_REJECTED, rej_msg, msg_rejected);
	IBA_SET(CM_REJ_REASON, rej_msg, reason);

	अगर (ari && ari_length) अणु
		IBA_SET(CM_REJ_REJECTED_INFO_LENGTH, rej_msg, ari_length);
		IBA_SET_MEM(CM_REJ_ARI, rej_msg, ari, ari_length);
	पूर्ण

	trace_icm_issue_rej(
		IBA_GET(CM_REJ_LOCAL_COMM_ID, rcv_msg),
		IBA_GET(CM_REJ_REMOTE_COMM_ID, rcv_msg));
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret)
		cm_मुक्त_msg(msg);

	वापस ret;
पूर्ण

अटल bool cm_req_has_alt_path(काष्ठा cm_req_msg *req_msg)
अणु
	वापस ((cpu_to_be16(
			IBA_GET(CM_REQ_ALTERNATE_LOCAL_PORT_LID, req_msg))) ||
		(ib_is_opa_gid(IBA_GET_MEM_PTR(CM_REQ_ALTERNATE_LOCAL_PORT_GID,
					       req_msg))));
पूर्ण

अटल व्योम cm_path_set_rec_type(काष्ठा ib_device *ib_device, u32 port_num,
				 काष्ठा sa_path_rec *path, जोड़ ib_gid *gid)
अणु
	अगर (ib_is_opa_gid(gid) && rdma_cap_opa_ah(ib_device, port_num))
		path->rec_type = SA_PATH_REC_TYPE_OPA;
	अन्यथा
		path->rec_type = SA_PATH_REC_TYPE_IB;
पूर्ण

अटल व्योम cm_क्रमmat_path_lid_from_req(काष्ठा cm_req_msg *req_msg,
					काष्ठा sa_path_rec *primary_path,
					काष्ठा sa_path_rec *alt_path)
अणु
	u32 lid;

	अगर (primary_path->rec_type != SA_PATH_REC_TYPE_OPA) अणु
		sa_path_set_dlid(primary_path,
				 IBA_GET(CM_REQ_PRIMARY_LOCAL_PORT_LID,
					 req_msg));
		sa_path_set_slid(primary_path,
				 IBA_GET(CM_REQ_PRIMARY_REMOTE_PORT_LID,
					 req_msg));
	पूर्ण अन्यथा अणु
		lid = opa_get_lid_from_gid(IBA_GET_MEM_PTR(
			CM_REQ_PRIMARY_LOCAL_PORT_GID, req_msg));
		sa_path_set_dlid(primary_path, lid);

		lid = opa_get_lid_from_gid(IBA_GET_MEM_PTR(
			CM_REQ_PRIMARY_REMOTE_PORT_GID, req_msg));
		sa_path_set_slid(primary_path, lid);
	पूर्ण

	अगर (!cm_req_has_alt_path(req_msg))
		वापस;

	अगर (alt_path->rec_type != SA_PATH_REC_TYPE_OPA) अणु
		sa_path_set_dlid(alt_path,
				 IBA_GET(CM_REQ_ALTERNATE_LOCAL_PORT_LID,
					 req_msg));
		sa_path_set_slid(alt_path,
				 IBA_GET(CM_REQ_ALTERNATE_REMOTE_PORT_LID,
					 req_msg));
	पूर्ण अन्यथा अणु
		lid = opa_get_lid_from_gid(IBA_GET_MEM_PTR(
			CM_REQ_ALTERNATE_LOCAL_PORT_GID, req_msg));
		sa_path_set_dlid(alt_path, lid);

		lid = opa_get_lid_from_gid(IBA_GET_MEM_PTR(
			CM_REQ_ALTERNATE_REMOTE_PORT_GID, req_msg));
		sa_path_set_slid(alt_path, lid);
	पूर्ण
पूर्ण

अटल व्योम cm_क्रमmat_paths_from_req(काष्ठा cm_req_msg *req_msg,
				     काष्ठा sa_path_rec *primary_path,
				     काष्ठा sa_path_rec *alt_path)
अणु
	primary_path->dgid =
		*IBA_GET_MEM_PTR(CM_REQ_PRIMARY_LOCAL_PORT_GID, req_msg);
	primary_path->sgid =
		*IBA_GET_MEM_PTR(CM_REQ_PRIMARY_REMOTE_PORT_GID, req_msg);
	primary_path->flow_label =
		cpu_to_be32(IBA_GET(CM_REQ_PRIMARY_FLOW_LABEL, req_msg));
	primary_path->hop_limit = IBA_GET(CM_REQ_PRIMARY_HOP_LIMIT, req_msg);
	primary_path->traffic_class =
		IBA_GET(CM_REQ_PRIMARY_TRAFFIC_CLASS, req_msg);
	primary_path->reversible = 1;
	primary_path->pkey =
		cpu_to_be16(IBA_GET(CM_REQ_PARTITION_KEY, req_msg));
	primary_path->sl = IBA_GET(CM_REQ_PRIMARY_SL, req_msg);
	primary_path->mtu_selector = IB_SA_EQ;
	primary_path->mtu = IBA_GET(CM_REQ_PATH_PACKET_PAYLOAD_MTU, req_msg);
	primary_path->rate_selector = IB_SA_EQ;
	primary_path->rate = IBA_GET(CM_REQ_PRIMARY_PACKET_RATE, req_msg);
	primary_path->packet_lअगरe_समय_selector = IB_SA_EQ;
	primary_path->packet_lअगरe_समय =
		IBA_GET(CM_REQ_PRIMARY_LOCAL_ACK_TIMEOUT, req_msg);
	primary_path->packet_lअगरe_समय -= (primary_path->packet_lअगरe_समय > 0);
	primary_path->service_id =
		cpu_to_be64(IBA_GET(CM_REQ_SERVICE_ID, req_msg));
	अगर (sa_path_is_roce(primary_path))
		primary_path->roce.route_resolved = false;

	अगर (cm_req_has_alt_path(req_msg)) अणु
		alt_path->dgid = *IBA_GET_MEM_PTR(
			CM_REQ_ALTERNATE_LOCAL_PORT_GID, req_msg);
		alt_path->sgid = *IBA_GET_MEM_PTR(
			CM_REQ_ALTERNATE_REMOTE_PORT_GID, req_msg);
		alt_path->flow_label = cpu_to_be32(
			IBA_GET(CM_REQ_ALTERNATE_FLOW_LABEL, req_msg));
		alt_path->hop_limit =
			IBA_GET(CM_REQ_ALTERNATE_HOP_LIMIT, req_msg);
		alt_path->traffic_class =
			IBA_GET(CM_REQ_ALTERNATE_TRAFFIC_CLASS, req_msg);
		alt_path->reversible = 1;
		alt_path->pkey =
			cpu_to_be16(IBA_GET(CM_REQ_PARTITION_KEY, req_msg));
		alt_path->sl = IBA_GET(CM_REQ_ALTERNATE_SL, req_msg);
		alt_path->mtu_selector = IB_SA_EQ;
		alt_path->mtu =
			IBA_GET(CM_REQ_PATH_PACKET_PAYLOAD_MTU, req_msg);
		alt_path->rate_selector = IB_SA_EQ;
		alt_path->rate = IBA_GET(CM_REQ_ALTERNATE_PACKET_RATE, req_msg);
		alt_path->packet_lअगरe_समय_selector = IB_SA_EQ;
		alt_path->packet_lअगरe_समय =
			IBA_GET(CM_REQ_ALTERNATE_LOCAL_ACK_TIMEOUT, req_msg);
		alt_path->packet_lअगरe_समय -= (alt_path->packet_lअगरe_समय > 0);
		alt_path->service_id =
			cpu_to_be64(IBA_GET(CM_REQ_SERVICE_ID, req_msg));

		अगर (sa_path_is_roce(alt_path))
			alt_path->roce.route_resolved = false;
	पूर्ण
	cm_क्रमmat_path_lid_from_req(req_msg, primary_path, alt_path);
पूर्ण

अटल u16 cm_get_bth_pkey(काष्ठा cm_work *work)
अणु
	काष्ठा ib_device *ib_dev = work->port->cm_dev->ib_device;
	u32 port_num = work->port->port_num;
	u16 pkey_index = work->mad_recv_wc->wc->pkey_index;
	u16 pkey;
	पूर्णांक ret;

	ret = ib_get_cached_pkey(ib_dev, port_num, pkey_index, &pkey);
	अगर (ret) अणु
		dev_warn_ratelimited(&ib_dev->dev, "ib_cm: Couldn't retrieve pkey for incoming request (port %d, pkey index %d). %d\n",
				     port_num, pkey_index, ret);
		वापस 0;
	पूर्ण

	वापस pkey;
पूर्ण

/**
 * cm_opa_to_ib_sgid - Convert OPA SGID to IB SGID
 * ULPs (such as IPoIB) करो not understand OPA GIDs and will
 * reject them as the local_gid will not match the sgid. Thereक्रमe,
 * change the pathrec's SGID to an IB SGID.
 *
 * @work: Work completion
 * @path: Path record
 */
अटल व्योम cm_opa_to_ib_sgid(काष्ठा cm_work *work,
			      काष्ठा sa_path_rec *path)
अणु
	काष्ठा ib_device *dev = work->port->cm_dev->ib_device;
	u32 port_num = work->port->port_num;

	अगर (rdma_cap_opa_ah(dev, port_num) &&
	    (ib_is_opa_gid(&path->sgid))) अणु
		जोड़ ib_gid sgid;

		अगर (rdma_query_gid(dev, port_num, 0, &sgid)) अणु
			dev_warn(&dev->dev,
				 "Error updating sgid in CM request\n");
			वापस;
		पूर्ण

		path->sgid = sgid;
	पूर्ण
पूर्ण

अटल व्योम cm_क्रमmat_req_event(काष्ठा cm_work *work,
				काष्ठा cm_id_निजी *cm_id_priv,
				काष्ठा ib_cm_id *listen_id)
अणु
	काष्ठा cm_req_msg *req_msg;
	काष्ठा ib_cm_req_event_param *param;

	req_msg = (काष्ठा cm_req_msg *)work->mad_recv_wc->recv_buf.mad;
	param = &work->cm_event.param.req_rcvd;
	param->listen_id = listen_id;
	param->bth_pkey = cm_get_bth_pkey(work);
	param->port = cm_id_priv->av.port->port_num;
	param->primary_path = &work->path[0];
	cm_opa_to_ib_sgid(work, param->primary_path);
	अगर (cm_req_has_alt_path(req_msg)) अणु
		param->alternate_path = &work->path[1];
		cm_opa_to_ib_sgid(work, param->alternate_path);
	पूर्ण अन्यथा अणु
		param->alternate_path = शून्य;
	पूर्ण
	param->remote_ca_guid =
		cpu_to_be64(IBA_GET(CM_REQ_LOCAL_CA_GUID, req_msg));
	param->remote_qkey = IBA_GET(CM_REQ_LOCAL_Q_KEY, req_msg);
	param->remote_qpn = IBA_GET(CM_REQ_LOCAL_QPN, req_msg);
	param->qp_type = cm_req_get_qp_type(req_msg);
	param->starting_psn = IBA_GET(CM_REQ_STARTING_PSN, req_msg);
	param->responder_resources = IBA_GET(CM_REQ_INITIATOR_DEPTH, req_msg);
	param->initiator_depth = IBA_GET(CM_REQ_RESPONDER_RESOURCES, req_msg);
	param->local_cm_response_समयout =
		IBA_GET(CM_REQ_REMOTE_CM_RESPONSE_TIMEOUT, req_msg);
	param->flow_control = IBA_GET(CM_REQ_END_TO_END_FLOW_CONTROL, req_msg);
	param->remote_cm_response_समयout =
		IBA_GET(CM_REQ_LOCAL_CM_RESPONSE_TIMEOUT, req_msg);
	param->retry_count = IBA_GET(CM_REQ_RETRY_COUNT, req_msg);
	param->rnr_retry_count = IBA_GET(CM_REQ_RNR_RETRY_COUNT, req_msg);
	param->srq = IBA_GET(CM_REQ_SRQ, req_msg);
	param->ppath_sgid_attr = cm_id_priv->av.ah_attr.grh.sgid_attr;
	param->ece.venकरोr_id = IBA_GET(CM_REQ_VENDOR_ID, req_msg);
	param->ece.attr_mod = be32_to_cpu(req_msg->hdr.attr_mod);

	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_REQ_PRIVATE_DATA, req_msg);
पूर्ण

अटल व्योम cm_process_work(काष्ठा cm_id_निजी *cm_id_priv,
			    काष्ठा cm_work *work)
अणु
	पूर्णांक ret;

	/* We will typically only have the current event to report. */
	ret = cm_id_priv->id.cm_handler(&cm_id_priv->id, &work->cm_event);
	cm_मुक्त_work(work);

	जबतक (!ret && !atomic_add_negative(-1, &cm_id_priv->work_count)) अणु
		spin_lock_irq(&cm_id_priv->lock);
		work = cm_dequeue_work(cm_id_priv);
		spin_unlock_irq(&cm_id_priv->lock);
		अगर (!work)
			वापस;

		ret = cm_id_priv->id.cm_handler(&cm_id_priv->id,
						&work->cm_event);
		cm_मुक्त_work(work);
	पूर्ण
	cm_deref_id(cm_id_priv);
	अगर (ret)
		cm_destroy_id(&cm_id_priv->id, ret);
पूर्ण

अटल व्योम cm_क्रमmat_mra(काष्ठा cm_mra_msg *mra_msg,
			  काष्ठा cm_id_निजी *cm_id_priv,
			  क्रमागत cm_msg_response msg_mraed, u8 service_समयout,
			  स्थिर व्योम *निजी_data, u8 निजी_data_len)
अणु
	cm_क्रमmat_mad_hdr(&mra_msg->hdr, CM_MRA_ATTR_ID, cm_id_priv->tid);
	IBA_SET(CM_MRA_MESSAGE_MRAED, mra_msg, msg_mraed);
	IBA_SET(CM_MRA_LOCAL_COMM_ID, mra_msg,
		be32_to_cpu(cm_id_priv->id.local_id));
	IBA_SET(CM_MRA_REMOTE_COMM_ID, mra_msg,
		be32_to_cpu(cm_id_priv->id.remote_id));
	IBA_SET(CM_MRA_SERVICE_TIMEOUT, mra_msg, service_समयout);

	अगर (निजी_data && निजी_data_len)
		IBA_SET_MEM(CM_MRA_PRIVATE_DATA, mra_msg, निजी_data,
			    निजी_data_len);
पूर्ण

अटल व्योम cm_क्रमmat_rej(काष्ठा cm_rej_msg *rej_msg,
			  काष्ठा cm_id_निजी *cm_id_priv,
			  क्रमागत ib_cm_rej_reason reason, व्योम *ari,
			  u8 ari_length, स्थिर व्योम *निजी_data,
			  u8 निजी_data_len, क्रमागत ib_cm_state state)
अणु
	lockdep_निश्चित_held(&cm_id_priv->lock);

	cm_क्रमmat_mad_hdr(&rej_msg->hdr, CM_REJ_ATTR_ID, cm_id_priv->tid);
	IBA_SET(CM_REJ_REMOTE_COMM_ID, rej_msg,
		be32_to_cpu(cm_id_priv->id.remote_id));

	चयन (state) अणु
	हाल IB_CM_REQ_RCVD:
		IBA_SET(CM_REJ_LOCAL_COMM_ID, rej_msg, be32_to_cpu(0));
		IBA_SET(CM_REJ_MESSAGE_REJECTED, rej_msg, CM_MSG_RESPONSE_REQ);
		अवरोध;
	हाल IB_CM_MRA_REQ_SENT:
		IBA_SET(CM_REJ_LOCAL_COMM_ID, rej_msg,
			be32_to_cpu(cm_id_priv->id.local_id));
		IBA_SET(CM_REJ_MESSAGE_REJECTED, rej_msg, CM_MSG_RESPONSE_REQ);
		अवरोध;
	हाल IB_CM_REP_RCVD:
	हाल IB_CM_MRA_REP_SENT:
		IBA_SET(CM_REJ_LOCAL_COMM_ID, rej_msg,
			be32_to_cpu(cm_id_priv->id.local_id));
		IBA_SET(CM_REJ_MESSAGE_REJECTED, rej_msg, CM_MSG_RESPONSE_REP);
		अवरोध;
	शेष:
		IBA_SET(CM_REJ_LOCAL_COMM_ID, rej_msg,
			be32_to_cpu(cm_id_priv->id.local_id));
		IBA_SET(CM_REJ_MESSAGE_REJECTED, rej_msg,
			CM_MSG_RESPONSE_OTHER);
		अवरोध;
	पूर्ण

	IBA_SET(CM_REJ_REASON, rej_msg, reason);
	अगर (ari && ari_length) अणु
		IBA_SET(CM_REJ_REJECTED_INFO_LENGTH, rej_msg, ari_length);
		IBA_SET_MEM(CM_REJ_ARI, rej_msg, ari, ari_length);
	पूर्ण

	अगर (निजी_data && निजी_data_len)
		IBA_SET_MEM(CM_REJ_PRIVATE_DATA, rej_msg, निजी_data,
			    निजी_data_len);
पूर्ण

अटल व्योम cm_dup_req_handler(काष्ठा cm_work *work,
			       काष्ठा cm_id_निजी *cm_id_priv)
अणु
	काष्ठा ib_mad_send_buf *msg = शून्य;
	पूर्णांक ret;

	atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
			counter[CM_REQ_COUNTER]);

	/* Quick state check to discard duplicate REQs. */
	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->id.state == IB_CM_REQ_RCVD) अणु
		spin_unlock_irq(&cm_id_priv->lock);
		वापस;
	पूर्ण
	spin_unlock_irq(&cm_id_priv->lock);

	ret = cm_alloc_response_msg(work->port, work->mad_recv_wc, &msg);
	अगर (ret)
		वापस;

	spin_lock_irq(&cm_id_priv->lock);
	चयन (cm_id_priv->id.state) अणु
	हाल IB_CM_MRA_REQ_SENT:
		cm_क्रमmat_mra((काष्ठा cm_mra_msg *) msg->mad, cm_id_priv,
			      CM_MSG_RESPONSE_REQ, cm_id_priv->service_समयout,
			      cm_id_priv->निजी_data,
			      cm_id_priv->निजी_data_len);
		अवरोध;
	हाल IB_CM_TIMEWAIT:
		cm_क्रमmat_rej((काष्ठा cm_rej_msg *)msg->mad, cm_id_priv,
			      IB_CM_REJ_STALE_CONN, शून्य, 0, शून्य, 0,
			      IB_CM_TIMEWAIT);
		अवरोध;
	शेष:
		जाओ unlock;
	पूर्ण
	spin_unlock_irq(&cm_id_priv->lock);

	trace_icm_send_dup_req(&cm_id_priv->id);
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret)
		जाओ मुक्त;
	वापस;

unlock:	spin_unlock_irq(&cm_id_priv->lock);
मुक्त:	cm_मुक्त_msg(msg);
पूर्ण

अटल काष्ठा cm_id_निजी *cm_match_req(काष्ठा cm_work *work,
					  काष्ठा cm_id_निजी *cm_id_priv)
अणु
	काष्ठा cm_id_निजी *listen_cm_id_priv, *cur_cm_id_priv;
	काष्ठा cm_समयरुको_info *समयरुको_info;
	काष्ठा cm_req_msg *req_msg;

	req_msg = (काष्ठा cm_req_msg *)work->mad_recv_wc->recv_buf.mad;

	/* Check क्रम possible duplicate REQ. */
	spin_lock_irq(&cm.lock);
	समयरुको_info = cm_insert_remote_id(cm_id_priv->समयरुको_info);
	अगर (समयरुको_info) अणु
		cur_cm_id_priv = cm_acquire_id(समयरुको_info->work.local_id,
					   समयरुको_info->work.remote_id);
		spin_unlock_irq(&cm.lock);
		अगर (cur_cm_id_priv) अणु
			cm_dup_req_handler(work, cur_cm_id_priv);
			cm_deref_id(cur_cm_id_priv);
		पूर्ण
		वापस शून्य;
	पूर्ण

	/* Check क्रम stale connections. */
	समयरुको_info = cm_insert_remote_qpn(cm_id_priv->समयरुको_info);
	अगर (समयरुको_info) अणु
		cm_हटाओ_remote(cm_id_priv);
		cur_cm_id_priv = cm_acquire_id(समयरुको_info->work.local_id,
					   समयरुको_info->work.remote_id);

		spin_unlock_irq(&cm.lock);
		cm_issue_rej(work->port, work->mad_recv_wc,
			     IB_CM_REJ_STALE_CONN, CM_MSG_RESPONSE_REQ,
			     शून्य, 0);
		अगर (cur_cm_id_priv) अणु
			ib_send_cm_dreq(&cur_cm_id_priv->id, शून्य, 0);
			cm_deref_id(cur_cm_id_priv);
		पूर्ण
		वापस शून्य;
	पूर्ण

	/* Find matching listen request. */
	listen_cm_id_priv = cm_find_listen(
		cm_id_priv->id.device,
		cpu_to_be64(IBA_GET(CM_REQ_SERVICE_ID, req_msg)));
	अगर (!listen_cm_id_priv) अणु
		cm_हटाओ_remote(cm_id_priv);
		spin_unlock_irq(&cm.lock);
		cm_issue_rej(work->port, work->mad_recv_wc,
			     IB_CM_REJ_INVALID_SERVICE_ID, CM_MSG_RESPONSE_REQ,
			     शून्य, 0);
		वापस शून्य;
	पूर्ण
	spin_unlock_irq(&cm.lock);
	वापस listen_cm_id_priv;
पूर्ण

/*
 * Work-around क्रम पूर्णांकer-subnet connections.  If the LIDs are permissive,
 * we need to override the LID/SL data in the REQ with the LID inक्रमmation
 * in the work completion.
 */
अटल व्योम cm_process_routed_req(काष्ठा cm_req_msg *req_msg, काष्ठा ib_wc *wc)
अणु
	अगर (!IBA_GET(CM_REQ_PRIMARY_SUBNET_LOCAL, req_msg)) अणु
		अगर (cpu_to_be16(IBA_GET(CM_REQ_PRIMARY_LOCAL_PORT_LID,
					req_msg)) == IB_LID_PERMISSIVE) अणु
			IBA_SET(CM_REQ_PRIMARY_LOCAL_PORT_LID, req_msg,
				be16_to_cpu(ib_lid_be16(wc->slid)));
			IBA_SET(CM_REQ_PRIMARY_SL, req_msg, wc->sl);
		पूर्ण

		अगर (cpu_to_be16(IBA_GET(CM_REQ_PRIMARY_REMOTE_PORT_LID,
					req_msg)) == IB_LID_PERMISSIVE)
			IBA_SET(CM_REQ_PRIMARY_REMOTE_PORT_LID, req_msg,
				wc->dlid_path_bits);
	पूर्ण

	अगर (!IBA_GET(CM_REQ_ALTERNATE_SUBNET_LOCAL, req_msg)) अणु
		अगर (cpu_to_be16(IBA_GET(CM_REQ_ALTERNATE_LOCAL_PORT_LID,
					req_msg)) == IB_LID_PERMISSIVE) अणु
			IBA_SET(CM_REQ_ALTERNATE_LOCAL_PORT_LID, req_msg,
				be16_to_cpu(ib_lid_be16(wc->slid)));
			IBA_SET(CM_REQ_ALTERNATE_SL, req_msg, wc->sl);
		पूर्ण

		अगर (cpu_to_be16(IBA_GET(CM_REQ_ALTERNATE_REMOTE_PORT_LID,
					req_msg)) == IB_LID_PERMISSIVE)
			IBA_SET(CM_REQ_ALTERNATE_REMOTE_PORT_LID, req_msg,
				wc->dlid_path_bits);
	पूर्ण
पूर्ण

अटल पूर्णांक cm_req_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv, *listen_cm_id_priv;
	काष्ठा cm_req_msg *req_msg;
	स्थिर काष्ठा ib_global_route *grh;
	स्थिर काष्ठा ib_gid_attr *gid_attr;
	पूर्णांक ret;

	req_msg = (काष्ठा cm_req_msg *)work->mad_recv_wc->recv_buf.mad;

	cm_id_priv =
		cm_alloc_id_priv(work->port->cm_dev->ib_device, शून्य, शून्य);
	अगर (IS_ERR(cm_id_priv))
		वापस PTR_ERR(cm_id_priv);

	cm_id_priv->id.remote_id =
		cpu_to_be32(IBA_GET(CM_REQ_LOCAL_COMM_ID, req_msg));
	cm_id_priv->id.service_id =
		cpu_to_be64(IBA_GET(CM_REQ_SERVICE_ID, req_msg));
	cm_id_priv->id.service_mask = ~cpu_to_be64(0);
	cm_id_priv->tid = req_msg->hdr.tid;
	cm_id_priv->समयout_ms = cm_convert_to_ms(
		IBA_GET(CM_REQ_LOCAL_CM_RESPONSE_TIMEOUT, req_msg));
	cm_id_priv->max_cm_retries = IBA_GET(CM_REQ_MAX_CM_RETRIES, req_msg);
	cm_id_priv->remote_qpn =
		cpu_to_be32(IBA_GET(CM_REQ_LOCAL_QPN, req_msg));
	cm_id_priv->initiator_depth =
		IBA_GET(CM_REQ_RESPONDER_RESOURCES, req_msg);
	cm_id_priv->responder_resources =
		IBA_GET(CM_REQ_INITIATOR_DEPTH, req_msg);
	cm_id_priv->path_mtu = IBA_GET(CM_REQ_PATH_PACKET_PAYLOAD_MTU, req_msg);
	cm_id_priv->pkey = cpu_to_be16(IBA_GET(CM_REQ_PARTITION_KEY, req_msg));
	cm_id_priv->sq_psn = cpu_to_be32(IBA_GET(CM_REQ_STARTING_PSN, req_msg));
	cm_id_priv->retry_count = IBA_GET(CM_REQ_RETRY_COUNT, req_msg);
	cm_id_priv->rnr_retry_count = IBA_GET(CM_REQ_RNR_RETRY_COUNT, req_msg);
	cm_id_priv->qp_type = cm_req_get_qp_type(req_msg);

	ret = cm_init_av_क्रम_response(work->port, work->mad_recv_wc->wc,
				      work->mad_recv_wc->recv_buf.grh,
				      &cm_id_priv->av);
	अगर (ret)
		जाओ destroy;
	cm_id_priv->समयरुको_info = cm_create_समयरुको_info(cm_id_priv->
							    id.local_id);
	अगर (IS_ERR(cm_id_priv->समयरुको_info)) अणु
		ret = PTR_ERR(cm_id_priv->समयरुको_info);
		cm_id_priv->समयरुको_info = शून्य;
		जाओ destroy;
	पूर्ण
	cm_id_priv->समयरुको_info->work.remote_id = cm_id_priv->id.remote_id;
	cm_id_priv->समयरुको_info->remote_ca_guid =
		cpu_to_be64(IBA_GET(CM_REQ_LOCAL_CA_GUID, req_msg));
	cm_id_priv->समयरुको_info->remote_qpn = cm_id_priv->remote_qpn;

	/*
	 * Note that the ID poपूर्णांकer is not in the xarray at this poपूर्णांक,
	 * so this set is only visible to the local thपढ़ो.
	 */
	cm_id_priv->id.state = IB_CM_REQ_RCVD;

	listen_cm_id_priv = cm_match_req(work, cm_id_priv);
	अगर (!listen_cm_id_priv) अणु
		trace_icm_no_listener_err(&cm_id_priv->id);
		cm_id_priv->id.state = IB_CM_IDLE;
		ret = -EINVAL;
		जाओ destroy;
	पूर्ण

	स_रखो(&work->path[0], 0, माप(work->path[0]));
	अगर (cm_req_has_alt_path(req_msg))
		स_रखो(&work->path[1], 0, माप(work->path[1]));
	grh = rdma_ah_पढ़ो_grh(&cm_id_priv->av.ah_attr);
	gid_attr = grh->sgid_attr;

	अगर (cm_id_priv->av.ah_attr.type == RDMA_AH_ATTR_TYPE_ROCE) अणु
		work->path[0].rec_type =
			sa_conv_gid_to_pathrec_type(gid_attr->gid_type);
	पूर्ण अन्यथा अणु
		cm_process_routed_req(req_msg, work->mad_recv_wc->wc);
		cm_path_set_rec_type(
			work->port->cm_dev->ib_device, work->port->port_num,
			&work->path[0],
			IBA_GET_MEM_PTR(CM_REQ_PRIMARY_LOCAL_PORT_GID,
					req_msg));
	पूर्ण
	अगर (cm_req_has_alt_path(req_msg))
		work->path[1].rec_type = work->path[0].rec_type;
	cm_क्रमmat_paths_from_req(req_msg, &work->path[0],
				 &work->path[1]);
	अगर (cm_id_priv->av.ah_attr.type == RDMA_AH_ATTR_TYPE_ROCE)
		sa_path_set_dmac(&work->path[0],
				 cm_id_priv->av.ah_attr.roce.dmac);
	work->path[0].hop_limit = grh->hop_limit;
	ret = cm_init_av_by_path(&work->path[0], gid_attr, &cm_id_priv->av,
				 cm_id_priv);
	अगर (ret) अणु
		पूर्णांक err;

		err = rdma_query_gid(work->port->cm_dev->ib_device,
				     work->port->port_num, 0,
				     &work->path[0].sgid);
		अगर (err)
			ib_send_cm_rej(&cm_id_priv->id, IB_CM_REJ_INVALID_GID,
				       शून्य, 0, शून्य, 0);
		अन्यथा
			ib_send_cm_rej(&cm_id_priv->id, IB_CM_REJ_INVALID_GID,
				       &work->path[0].sgid,
				       माप(work->path[0].sgid),
				       शून्य, 0);
		जाओ rejected;
	पूर्ण
	अगर (cm_req_has_alt_path(req_msg)) अणु
		ret = cm_init_av_by_path(&work->path[1], शून्य,
					 &cm_id_priv->alt_av, cm_id_priv);
		अगर (ret) अणु
			ib_send_cm_rej(&cm_id_priv->id,
				       IB_CM_REJ_INVALID_ALT_GID,
				       &work->path[0].sgid,
				       माप(work->path[0].sgid), शून्य, 0);
			जाओ rejected;
		पूर्ण
	पूर्ण

	cm_id_priv->id.cm_handler = listen_cm_id_priv->id.cm_handler;
	cm_id_priv->id.context = listen_cm_id_priv->id.context;
	cm_क्रमmat_req_event(work, cm_id_priv, &listen_cm_id_priv->id);

	/* Now MAD handlers can see the new ID */
	spin_lock_irq(&cm_id_priv->lock);
	cm_finalize_id(cm_id_priv);

	/* Refcount beदीर्घs to the event, pairs with cm_process_work() */
	refcount_inc(&cm_id_priv->refcount);
	cm_queue_work_unlock(cm_id_priv, work);
	/*
	 * Since this ID was just created and was not made visible to other MAD
	 * handlers until the cm_finalize_id() above we know that the
	 * cm_process_work() will deliver the event and the listen_cm_id
	 * embedded in the event can be derefed here.
	 */
	cm_deref_id(listen_cm_id_priv);
	वापस 0;

rejected:
	cm_deref_id(listen_cm_id_priv);
destroy:
	ib_destroy_cm_id(&cm_id_priv->id);
	वापस ret;
पूर्ण

अटल व्योम cm_क्रमmat_rep(काष्ठा cm_rep_msg *rep_msg,
			  काष्ठा cm_id_निजी *cm_id_priv,
			  काष्ठा ib_cm_rep_param *param)
अणु
	cm_क्रमmat_mad_ece_hdr(&rep_msg->hdr, CM_REP_ATTR_ID, cm_id_priv->tid,
			      param->ece.attr_mod);
	IBA_SET(CM_REP_LOCAL_COMM_ID, rep_msg,
		be32_to_cpu(cm_id_priv->id.local_id));
	IBA_SET(CM_REP_REMOTE_COMM_ID, rep_msg,
		be32_to_cpu(cm_id_priv->id.remote_id));
	IBA_SET(CM_REP_STARTING_PSN, rep_msg, param->starting_psn);
	IBA_SET(CM_REP_RESPONDER_RESOURCES, rep_msg,
		param->responder_resources);
	IBA_SET(CM_REP_TARGET_ACK_DELAY, rep_msg,
		cm_id_priv->av.port->cm_dev->ack_delay);
	IBA_SET(CM_REP_FAILOVER_ACCEPTED, rep_msg, param->failover_accepted);
	IBA_SET(CM_REP_RNR_RETRY_COUNT, rep_msg, param->rnr_retry_count);
	IBA_SET(CM_REP_LOCAL_CA_GUID, rep_msg,
		be64_to_cpu(cm_id_priv->id.device->node_guid));

	अगर (cm_id_priv->qp_type != IB_QPT_XRC_TGT) अणु
		IBA_SET(CM_REP_INITIATOR_DEPTH, rep_msg,
			param->initiator_depth);
		IBA_SET(CM_REP_END_TO_END_FLOW_CONTROL, rep_msg,
			param->flow_control);
		IBA_SET(CM_REP_SRQ, rep_msg, param->srq);
		IBA_SET(CM_REP_LOCAL_QPN, rep_msg, param->qp_num);
	पूर्ण अन्यथा अणु
		IBA_SET(CM_REP_SRQ, rep_msg, 1);
		IBA_SET(CM_REP_LOCAL_EE_CONTEXT_NUMBER, rep_msg, param->qp_num);
	पूर्ण

	IBA_SET(CM_REP_VENDOR_ID_L, rep_msg, param->ece.venकरोr_id);
	IBA_SET(CM_REP_VENDOR_ID_M, rep_msg, param->ece.venकरोr_id >> 8);
	IBA_SET(CM_REP_VENDOR_ID_H, rep_msg, param->ece.venकरोr_id >> 16);

	अगर (param->निजी_data && param->निजी_data_len)
		IBA_SET_MEM(CM_REP_PRIVATE_DATA, rep_msg, param->निजी_data,
			    param->निजी_data_len);
पूर्ण

पूर्णांक ib_send_cm_rep(काष्ठा ib_cm_id *cm_id,
		   काष्ठा ib_cm_rep_param *param)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा ib_mad_send_buf *msg;
	काष्ठा cm_rep_msg *rep_msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (param->निजी_data &&
	    param->निजी_data_len > IB_CM_REP_PRIVATE_DATA_SIZE)
		वापस -EINVAL;

	cm_id_priv = container_of(cm_id, काष्ठा cm_id_निजी, id);
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	अगर (cm_id->state != IB_CM_REQ_RCVD &&
	    cm_id->state != IB_CM_MRA_REQ_SENT) अणु
		trace_icm_send_rep_err(cm_id_priv->id.local_id, cm_id->state);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = cm_alloc_msg(cm_id_priv, &msg);
	अगर (ret)
		जाओ out;

	rep_msg = (काष्ठा cm_rep_msg *) msg->mad;
	cm_क्रमmat_rep(rep_msg, cm_id_priv, param);
	msg->समयout_ms = cm_id_priv->समयout_ms;
	msg->context[1] = (व्योम *) (अचिन्हित दीर्घ) IB_CM_REP_SENT;

	trace_icm_send_rep(cm_id);
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret) अणु
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		cm_मुक्त_msg(msg);
		वापस ret;
	पूर्ण

	cm_id->state = IB_CM_REP_SENT;
	cm_id_priv->msg = msg;
	cm_id_priv->initiator_depth = param->initiator_depth;
	cm_id_priv->responder_resources = param->responder_resources;
	cm_id_priv->rq_psn = cpu_to_be32(IBA_GET(CM_REP_STARTING_PSN, rep_msg));
	WARN_ONCE(param->qp_num & 0xFF000000,
		  "IBTA declares QPN to be 24 bits, but it is 0x%X\n",
		  param->qp_num);
	cm_id_priv->local_qpn = cpu_to_be32(param->qp_num & 0xFFFFFF);

out:	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_send_cm_rep);

अटल व्योम cm_क्रमmat_rtu(काष्ठा cm_rtu_msg *rtu_msg,
			  काष्ठा cm_id_निजी *cm_id_priv,
			  स्थिर व्योम *निजी_data,
			  u8 निजी_data_len)
अणु
	cm_क्रमmat_mad_hdr(&rtu_msg->hdr, CM_RTU_ATTR_ID, cm_id_priv->tid);
	IBA_SET(CM_RTU_LOCAL_COMM_ID, rtu_msg,
		be32_to_cpu(cm_id_priv->id.local_id));
	IBA_SET(CM_RTU_REMOTE_COMM_ID, rtu_msg,
		be32_to_cpu(cm_id_priv->id.remote_id));

	अगर (निजी_data && निजी_data_len)
		IBA_SET_MEM(CM_RTU_PRIVATE_DATA, rtu_msg, निजी_data,
			    निजी_data_len);
पूर्ण

पूर्णांक ib_send_cm_rtu(काष्ठा ib_cm_id *cm_id,
		   स्थिर व्योम *निजी_data,
		   u8 निजी_data_len)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा ib_mad_send_buf *msg;
	अचिन्हित दीर्घ flags;
	व्योम *data;
	पूर्णांक ret;

	अगर (निजी_data && निजी_data_len > IB_CM_RTU_PRIVATE_DATA_SIZE)
		वापस -EINVAL;

	data = cm_copy_निजी_data(निजी_data, निजी_data_len);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	cm_id_priv = container_of(cm_id, काष्ठा cm_id_निजी, id);
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	अगर (cm_id->state != IB_CM_REP_RCVD &&
	    cm_id->state != IB_CM_MRA_REP_SENT) अणु
		trace_icm_send_cm_rtu_err(cm_id);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	ret = cm_alloc_msg(cm_id_priv, &msg);
	अगर (ret)
		जाओ error;

	cm_क्रमmat_rtu((काष्ठा cm_rtu_msg *) msg->mad, cm_id_priv,
		      निजी_data, निजी_data_len);

	trace_icm_send_rtu(cm_id);
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret) अणु
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		cm_मुक्त_msg(msg);
		kमुक्त(data);
		वापस ret;
	पूर्ण

	cm_id->state = IB_CM_ESTABLISHED;
	cm_set_निजी_data(cm_id_priv, data, निजी_data_len);
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस 0;

error:	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	kमुक्त(data);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_send_cm_rtu);

अटल व्योम cm_क्रमmat_rep_event(काष्ठा cm_work *work, क्रमागत ib_qp_type qp_type)
अणु
	काष्ठा cm_rep_msg *rep_msg;
	काष्ठा ib_cm_rep_event_param *param;

	rep_msg = (काष्ठा cm_rep_msg *)work->mad_recv_wc->recv_buf.mad;
	param = &work->cm_event.param.rep_rcvd;
	param->remote_ca_guid =
		cpu_to_be64(IBA_GET(CM_REP_LOCAL_CA_GUID, rep_msg));
	param->remote_qkey = IBA_GET(CM_REP_LOCAL_Q_KEY, rep_msg);
	param->remote_qpn = be32_to_cpu(cm_rep_get_qpn(rep_msg, qp_type));
	param->starting_psn = IBA_GET(CM_REP_STARTING_PSN, rep_msg);
	param->responder_resources = IBA_GET(CM_REP_INITIATOR_DEPTH, rep_msg);
	param->initiator_depth = IBA_GET(CM_REP_RESPONDER_RESOURCES, rep_msg);
	param->target_ack_delay = IBA_GET(CM_REP_TARGET_ACK_DELAY, rep_msg);
	param->failover_accepted = IBA_GET(CM_REP_FAILOVER_ACCEPTED, rep_msg);
	param->flow_control = IBA_GET(CM_REP_END_TO_END_FLOW_CONTROL, rep_msg);
	param->rnr_retry_count = IBA_GET(CM_REP_RNR_RETRY_COUNT, rep_msg);
	param->srq = IBA_GET(CM_REP_SRQ, rep_msg);
	param->ece.venकरोr_id = IBA_GET(CM_REP_VENDOR_ID_H, rep_msg) << 16;
	param->ece.venकरोr_id |= IBA_GET(CM_REP_VENDOR_ID_M, rep_msg) << 8;
	param->ece.venकरोr_id |= IBA_GET(CM_REP_VENDOR_ID_L, rep_msg);
	param->ece.attr_mod = be32_to_cpu(rep_msg->hdr.attr_mod);

	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_REP_PRIVATE_DATA, rep_msg);
पूर्ण

अटल व्योम cm_dup_rep_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_rep_msg *rep_msg;
	काष्ठा ib_mad_send_buf *msg = शून्य;
	पूर्णांक ret;

	rep_msg = (काष्ठा cm_rep_msg *) work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(
		cpu_to_be32(IBA_GET(CM_REP_REMOTE_COMM_ID, rep_msg)),
		cpu_to_be32(IBA_GET(CM_REP_LOCAL_COMM_ID, rep_msg)));
	अगर (!cm_id_priv)
		वापस;

	atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
			counter[CM_REP_COUNTER]);
	ret = cm_alloc_response_msg(work->port, work->mad_recv_wc, &msg);
	अगर (ret)
		जाओ deref;

	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->id.state == IB_CM_ESTABLISHED)
		cm_क्रमmat_rtu((काष्ठा cm_rtu_msg *) msg->mad, cm_id_priv,
			      cm_id_priv->निजी_data,
			      cm_id_priv->निजी_data_len);
	अन्यथा अगर (cm_id_priv->id.state == IB_CM_MRA_REP_SENT)
		cm_क्रमmat_mra((काष्ठा cm_mra_msg *) msg->mad, cm_id_priv,
			      CM_MSG_RESPONSE_REP, cm_id_priv->service_समयout,
			      cm_id_priv->निजी_data,
			      cm_id_priv->निजी_data_len);
	अन्यथा
		जाओ unlock;
	spin_unlock_irq(&cm_id_priv->lock);

	trace_icm_send_dup_rep(&cm_id_priv->id);
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret)
		जाओ मुक्त;
	जाओ deref;

unlock:	spin_unlock_irq(&cm_id_priv->lock);
मुक्त:	cm_मुक्त_msg(msg);
deref:	cm_deref_id(cm_id_priv);
पूर्ण

अटल पूर्णांक cm_rep_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_rep_msg *rep_msg;
	पूर्णांक ret;
	काष्ठा cm_id_निजी *cur_cm_id_priv;
	काष्ठा cm_समयरुको_info *समयरुको_info;

	rep_msg = (काष्ठा cm_rep_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(
		cpu_to_be32(IBA_GET(CM_REP_REMOTE_COMM_ID, rep_msg)), 0);
	अगर (!cm_id_priv) अणु
		cm_dup_rep_handler(work);
		trace_icm_remote_no_priv_err(
			 IBA_GET(CM_REP_REMOTE_COMM_ID, rep_msg));
		वापस -EINVAL;
	पूर्ण

	cm_क्रमmat_rep_event(work, cm_id_priv->qp_type);

	spin_lock_irq(&cm_id_priv->lock);
	चयन (cm_id_priv->id.state) अणु
	हाल IB_CM_REQ_SENT:
	हाल IB_CM_MRA_REQ_RCVD:
		अवरोध;
	शेष:
		ret = -EINVAL;
		trace_icm_rep_unknown_err(
			IBA_GET(CM_REP_LOCAL_COMM_ID, rep_msg),
			IBA_GET(CM_REP_REMOTE_COMM_ID, rep_msg),
			cm_id_priv->id.state);
		spin_unlock_irq(&cm_id_priv->lock);
		जाओ error;
	पूर्ण

	cm_id_priv->समयरुको_info->work.remote_id =
		cpu_to_be32(IBA_GET(CM_REP_LOCAL_COMM_ID, rep_msg));
	cm_id_priv->समयरुको_info->remote_ca_guid =
		cpu_to_be64(IBA_GET(CM_REP_LOCAL_CA_GUID, rep_msg));
	cm_id_priv->समयरुको_info->remote_qpn = cm_rep_get_qpn(rep_msg, cm_id_priv->qp_type);

	spin_lock(&cm.lock);
	/* Check क्रम duplicate REP. */
	अगर (cm_insert_remote_id(cm_id_priv->समयरुको_info)) अणु
		spin_unlock(&cm.lock);
		spin_unlock_irq(&cm_id_priv->lock);
		ret = -EINVAL;
		trace_icm_insert_failed_err(
			 IBA_GET(CM_REP_REMOTE_COMM_ID, rep_msg));
		जाओ error;
	पूर्ण
	/* Check क्रम a stale connection. */
	समयरुको_info = cm_insert_remote_qpn(cm_id_priv->समयरुको_info);
	अगर (समयरुको_info) अणु
		cm_हटाओ_remote(cm_id_priv);
		cur_cm_id_priv = cm_acquire_id(समयरुको_info->work.local_id,
					   समयरुको_info->work.remote_id);

		spin_unlock(&cm.lock);
		spin_unlock_irq(&cm_id_priv->lock);
		cm_issue_rej(work->port, work->mad_recv_wc,
			     IB_CM_REJ_STALE_CONN, CM_MSG_RESPONSE_REP,
			     शून्य, 0);
		ret = -EINVAL;
		trace_icm_staleconn_err(
			IBA_GET(CM_REP_LOCAL_COMM_ID, rep_msg),
			IBA_GET(CM_REP_REMOTE_COMM_ID, rep_msg));

		अगर (cur_cm_id_priv) अणु
			ib_send_cm_dreq(&cur_cm_id_priv->id, शून्य, 0);
			cm_deref_id(cur_cm_id_priv);
		पूर्ण

		जाओ error;
	पूर्ण
	spin_unlock(&cm.lock);

	cm_id_priv->id.state = IB_CM_REP_RCVD;
	cm_id_priv->id.remote_id =
		cpu_to_be32(IBA_GET(CM_REP_LOCAL_COMM_ID, rep_msg));
	cm_id_priv->remote_qpn = cm_rep_get_qpn(rep_msg, cm_id_priv->qp_type);
	cm_id_priv->initiator_depth =
		IBA_GET(CM_REP_RESPONDER_RESOURCES, rep_msg);
	cm_id_priv->responder_resources =
		IBA_GET(CM_REP_INITIATOR_DEPTH, rep_msg);
	cm_id_priv->sq_psn = cpu_to_be32(IBA_GET(CM_REP_STARTING_PSN, rep_msg));
	cm_id_priv->rnr_retry_count = IBA_GET(CM_REP_RNR_RETRY_COUNT, rep_msg);
	cm_id_priv->target_ack_delay =
		IBA_GET(CM_REP_TARGET_ACK_DELAY, rep_msg);
	cm_id_priv->av.समयout =
			cm_ack_समयout(cm_id_priv->target_ack_delay,
				       cm_id_priv->av.समयout - 1);
	cm_id_priv->alt_av.समयout =
			cm_ack_समयout(cm_id_priv->target_ack_delay,
				       cm_id_priv->alt_av.समयout - 1);

	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;

error:
	cm_deref_id(cm_id_priv);
	वापस ret;
पूर्ण

अटल पूर्णांक cm_establish_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;

	/* See comment in cm_establish about lookup. */
	cm_id_priv = cm_acquire_id(work->local_id, work->remote_id);
	अगर (!cm_id_priv)
		वापस -EINVAL;

	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->id.state != IB_CM_ESTABLISHED) अणु
		spin_unlock_irq(&cm_id_priv->lock);
		जाओ out;
	पूर्ण

	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;
out:
	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cm_rtu_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_rtu_msg *rtu_msg;

	rtu_msg = (काष्ठा cm_rtu_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(
		cpu_to_be32(IBA_GET(CM_RTU_REMOTE_COMM_ID, rtu_msg)),
		cpu_to_be32(IBA_GET(CM_RTU_LOCAL_COMM_ID, rtu_msg)));
	अगर (!cm_id_priv)
		वापस -EINVAL;

	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_RTU_PRIVATE_DATA, rtu_msg);

	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->id.state != IB_CM_REP_SENT &&
	    cm_id_priv->id.state != IB_CM_MRA_REP_RCVD) अणु
		spin_unlock_irq(&cm_id_priv->lock);
		atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_RTU_COUNTER]);
		जाओ out;
	पूर्ण
	cm_id_priv->id.state = IB_CM_ESTABLISHED;

	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;
out:
	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

अटल व्योम cm_क्रमmat_dreq(काष्ठा cm_dreq_msg *dreq_msg,
			  काष्ठा cm_id_निजी *cm_id_priv,
			  स्थिर व्योम *निजी_data,
			  u8 निजी_data_len)
अणु
	cm_क्रमmat_mad_hdr(&dreq_msg->hdr, CM_DREQ_ATTR_ID,
			  cm_क्रमm_tid(cm_id_priv));
	IBA_SET(CM_DREQ_LOCAL_COMM_ID, dreq_msg,
		be32_to_cpu(cm_id_priv->id.local_id));
	IBA_SET(CM_DREQ_REMOTE_COMM_ID, dreq_msg,
		be32_to_cpu(cm_id_priv->id.remote_id));
	IBA_SET(CM_DREQ_REMOTE_QPN_EECN, dreq_msg,
		be32_to_cpu(cm_id_priv->remote_qpn));

	अगर (निजी_data && निजी_data_len)
		IBA_SET_MEM(CM_DREQ_PRIVATE_DATA, dreq_msg, निजी_data,
			    निजी_data_len);
पूर्ण

अटल पूर्णांक cm_send_dreq_locked(काष्ठा cm_id_निजी *cm_id_priv,
			       स्थिर व्योम *निजी_data, u8 निजी_data_len)
अणु
	काष्ठा ib_mad_send_buf *msg;
	पूर्णांक ret;

	lockdep_निश्चित_held(&cm_id_priv->lock);

	अगर (निजी_data && निजी_data_len > IB_CM_DREQ_PRIVATE_DATA_SIZE)
		वापस -EINVAL;

	अगर (cm_id_priv->id.state != IB_CM_ESTABLISHED) अणु
		trace_icm_dreq_skipped(&cm_id_priv->id);
		वापस -EINVAL;
	पूर्ण

	अगर (cm_id_priv->id.lap_state == IB_CM_LAP_SENT ||
	    cm_id_priv->id.lap_state == IB_CM_MRA_LAP_RCVD)
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);

	ret = cm_alloc_msg(cm_id_priv, &msg);
	अगर (ret) अणु
		cm_enter_समयरुको(cm_id_priv);
		वापस ret;
	पूर्ण

	cm_क्रमmat_dreq((काष्ठा cm_dreq_msg *) msg->mad, cm_id_priv,
		       निजी_data, निजी_data_len);
	msg->समयout_ms = cm_id_priv->समयout_ms;
	msg->context[1] = (व्योम *) (अचिन्हित दीर्घ) IB_CM_DREQ_SENT;

	trace_icm_send_dreq(&cm_id_priv->id);
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret) अणु
		cm_enter_समयरुको(cm_id_priv);
		cm_मुक्त_msg(msg);
		वापस ret;
	पूर्ण

	cm_id_priv->id.state = IB_CM_DREQ_SENT;
	cm_id_priv->msg = msg;
	वापस 0;
पूर्ण

पूर्णांक ib_send_cm_dreq(काष्ठा ib_cm_id *cm_id, स्थिर व्योम *निजी_data,
		    u8 निजी_data_len)
अणु
	काष्ठा cm_id_निजी *cm_id_priv =
		container_of(cm_id, काष्ठा cm_id_निजी, id);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	ret = cm_send_dreq_locked(cm_id_priv, निजी_data, निजी_data_len);
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_send_cm_dreq);

अटल व्योम cm_क्रमmat_drep(काष्ठा cm_drep_msg *drep_msg,
			  काष्ठा cm_id_निजी *cm_id_priv,
			  स्थिर व्योम *निजी_data,
			  u8 निजी_data_len)
अणु
	cm_क्रमmat_mad_hdr(&drep_msg->hdr, CM_DREP_ATTR_ID, cm_id_priv->tid);
	IBA_SET(CM_DREP_LOCAL_COMM_ID, drep_msg,
		be32_to_cpu(cm_id_priv->id.local_id));
	IBA_SET(CM_DREP_REMOTE_COMM_ID, drep_msg,
		be32_to_cpu(cm_id_priv->id.remote_id));

	अगर (निजी_data && निजी_data_len)
		IBA_SET_MEM(CM_DREP_PRIVATE_DATA, drep_msg, निजी_data,
			    निजी_data_len);
पूर्ण

अटल पूर्णांक cm_send_drep_locked(काष्ठा cm_id_निजी *cm_id_priv,
			       व्योम *निजी_data, u8 निजी_data_len)
अणु
	काष्ठा ib_mad_send_buf *msg;
	पूर्णांक ret;

	lockdep_निश्चित_held(&cm_id_priv->lock);

	अगर (निजी_data && निजी_data_len > IB_CM_DREP_PRIVATE_DATA_SIZE)
		वापस -EINVAL;

	अगर (cm_id_priv->id.state != IB_CM_DREQ_RCVD) अणु
		trace_icm_send_drep_err(&cm_id_priv->id);
		kमुक्त(निजी_data);
		वापस -EINVAL;
	पूर्ण

	cm_set_निजी_data(cm_id_priv, निजी_data, निजी_data_len);
	cm_enter_समयरुको(cm_id_priv);

	ret = cm_alloc_msg(cm_id_priv, &msg);
	अगर (ret)
		वापस ret;

	cm_क्रमmat_drep((काष्ठा cm_drep_msg *) msg->mad, cm_id_priv,
		       निजी_data, निजी_data_len);

	trace_icm_send_drep(&cm_id_priv->id);
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret) अणु
		cm_मुक्त_msg(msg);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ib_send_cm_drep(काष्ठा ib_cm_id *cm_id, स्थिर व्योम *निजी_data,
		    u8 निजी_data_len)
अणु
	काष्ठा cm_id_निजी *cm_id_priv =
		container_of(cm_id, काष्ठा cm_id_निजी, id);
	अचिन्हित दीर्घ flags;
	व्योम *data;
	पूर्णांक ret;

	data = cm_copy_निजी_data(निजी_data, निजी_data_len);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	ret = cm_send_drep_locked(cm_id_priv, data, निजी_data_len);
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_send_cm_drep);

अटल पूर्णांक cm_issue_drep(काष्ठा cm_port *port,
			 काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_mad_send_buf *msg = शून्य;
	काष्ठा cm_dreq_msg *dreq_msg;
	काष्ठा cm_drep_msg *drep_msg;
	पूर्णांक ret;

	ret = cm_alloc_response_msg(port, mad_recv_wc, &msg);
	अगर (ret)
		वापस ret;

	dreq_msg = (काष्ठा cm_dreq_msg *) mad_recv_wc->recv_buf.mad;
	drep_msg = (काष्ठा cm_drep_msg *) msg->mad;

	cm_क्रमmat_mad_hdr(&drep_msg->hdr, CM_DREP_ATTR_ID, dreq_msg->hdr.tid);
	IBA_SET(CM_DREP_REMOTE_COMM_ID, drep_msg,
		IBA_GET(CM_DREQ_LOCAL_COMM_ID, dreq_msg));
	IBA_SET(CM_DREP_LOCAL_COMM_ID, drep_msg,
		IBA_GET(CM_DREQ_REMOTE_COMM_ID, dreq_msg));

	trace_icm_issue_drep(
		IBA_GET(CM_DREQ_LOCAL_COMM_ID, dreq_msg),
		IBA_GET(CM_DREQ_REMOTE_COMM_ID, dreq_msg));
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret)
		cm_मुक्त_msg(msg);

	वापस ret;
पूर्ण

अटल पूर्णांक cm_dreq_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_dreq_msg *dreq_msg;
	काष्ठा ib_mad_send_buf *msg = शून्य;

	dreq_msg = (काष्ठा cm_dreq_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(
		cpu_to_be32(IBA_GET(CM_DREQ_REMOTE_COMM_ID, dreq_msg)),
		cpu_to_be32(IBA_GET(CM_DREQ_LOCAL_COMM_ID, dreq_msg)));
	अगर (!cm_id_priv) अणु
		atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_DREQ_COUNTER]);
		cm_issue_drep(work->port, work->mad_recv_wc);
		trace_icm_no_priv_err(
			IBA_GET(CM_DREQ_LOCAL_COMM_ID, dreq_msg),
			IBA_GET(CM_DREQ_REMOTE_COMM_ID, dreq_msg));
		वापस -EINVAL;
	पूर्ण

	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_DREQ_PRIVATE_DATA, dreq_msg);

	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->local_qpn !=
	    cpu_to_be32(IBA_GET(CM_DREQ_REMOTE_QPN_EECN, dreq_msg)))
		जाओ unlock;

	चयन (cm_id_priv->id.state) अणु
	हाल IB_CM_REP_SENT:
	हाल IB_CM_DREQ_SENT:
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		अवरोध;
	हाल IB_CM_ESTABLISHED:
		अगर (cm_id_priv->id.lap_state == IB_CM_LAP_SENT ||
		    cm_id_priv->id.lap_state == IB_CM_MRA_LAP_RCVD)
			ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		अवरोध;
	हाल IB_CM_MRA_REP_RCVD:
		अवरोध;
	हाल IB_CM_TIMEWAIT:
		atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_DREQ_COUNTER]);
		msg = cm_alloc_response_msg_no_ah(work->port, work->mad_recv_wc);
		अगर (IS_ERR(msg))
			जाओ unlock;

		cm_क्रमmat_drep((काष्ठा cm_drep_msg *) msg->mad, cm_id_priv,
			       cm_id_priv->निजी_data,
			       cm_id_priv->निजी_data_len);
		spin_unlock_irq(&cm_id_priv->lock);

		अगर (cm_create_response_msg_ah(work->port, work->mad_recv_wc, msg) ||
		    ib_post_send_mad(msg, शून्य))
			cm_मुक्त_msg(msg);
		जाओ deref;
	हाल IB_CM_DREQ_RCVD:
		atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_DREQ_COUNTER]);
		जाओ unlock;
	शेष:
		trace_icm_dreq_unknown_err(&cm_id_priv->id);
		जाओ unlock;
	पूर्ण
	cm_id_priv->id.state = IB_CM_DREQ_RCVD;
	cm_id_priv->tid = dreq_msg->hdr.tid;
	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;

unlock:	spin_unlock_irq(&cm_id_priv->lock);
deref:	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cm_drep_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_drep_msg *drep_msg;

	drep_msg = (काष्ठा cm_drep_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(
		cpu_to_be32(IBA_GET(CM_DREP_REMOTE_COMM_ID, drep_msg)),
		cpu_to_be32(IBA_GET(CM_DREP_LOCAL_COMM_ID, drep_msg)));
	अगर (!cm_id_priv)
		वापस -EINVAL;

	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_DREP_PRIVATE_DATA, drep_msg);

	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->id.state != IB_CM_DREQ_SENT &&
	    cm_id_priv->id.state != IB_CM_DREQ_RCVD) अणु
		spin_unlock_irq(&cm_id_priv->lock);
		जाओ out;
	पूर्ण
	cm_enter_समयरुको(cm_id_priv);

	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;
out:
	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cm_send_rej_locked(काष्ठा cm_id_निजी *cm_id_priv,
			      क्रमागत ib_cm_rej_reason reason, व्योम *ari,
			      u8 ari_length, स्थिर व्योम *निजी_data,
			      u8 निजी_data_len)
अणु
	क्रमागत ib_cm_state state = cm_id_priv->id.state;
	काष्ठा ib_mad_send_buf *msg;
	पूर्णांक ret;

	lockdep_निश्चित_held(&cm_id_priv->lock);

	अगर ((निजी_data && निजी_data_len > IB_CM_REJ_PRIVATE_DATA_SIZE) ||
	    (ari && ari_length > IB_CM_REJ_ARI_LENGTH))
		वापस -EINVAL;

	चयन (state) अणु
	हाल IB_CM_REQ_SENT:
	हाल IB_CM_MRA_REQ_RCVD:
	हाल IB_CM_REQ_RCVD:
	हाल IB_CM_MRA_REQ_SENT:
	हाल IB_CM_REP_RCVD:
	हाल IB_CM_MRA_REP_SENT:
		cm_reset_to_idle(cm_id_priv);
		ret = cm_alloc_msg(cm_id_priv, &msg);
		अगर (ret)
			वापस ret;
		cm_क्रमmat_rej((काष्ठा cm_rej_msg *)msg->mad, cm_id_priv, reason,
			      ari, ari_length, निजी_data, निजी_data_len,
			      state);
		अवरोध;
	हाल IB_CM_REP_SENT:
	हाल IB_CM_MRA_REP_RCVD:
		cm_enter_समयरुको(cm_id_priv);
		ret = cm_alloc_msg(cm_id_priv, &msg);
		अगर (ret)
			वापस ret;
		cm_क्रमmat_rej((काष्ठा cm_rej_msg *)msg->mad, cm_id_priv, reason,
			      ari, ari_length, निजी_data, निजी_data_len,
			      state);
		अवरोध;
	शेष:
		trace_icm_send_unknown_rej_err(&cm_id_priv->id);
		वापस -EINVAL;
	पूर्ण

	trace_icm_send_rej(&cm_id_priv->id, reason);
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret) अणु
		cm_मुक्त_msg(msg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ib_send_cm_rej(काष्ठा ib_cm_id *cm_id, क्रमागत ib_cm_rej_reason reason,
		   व्योम *ari, u8 ari_length, स्थिर व्योम *निजी_data,
		   u8 निजी_data_len)
अणु
	काष्ठा cm_id_निजी *cm_id_priv =
		container_of(cm_id, काष्ठा cm_id_निजी, id);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	ret = cm_send_rej_locked(cm_id_priv, reason, ari, ari_length,
				 निजी_data, निजी_data_len);
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_send_cm_rej);

अटल व्योम cm_क्रमmat_rej_event(काष्ठा cm_work *work)
अणु
	काष्ठा cm_rej_msg *rej_msg;
	काष्ठा ib_cm_rej_event_param *param;

	rej_msg = (काष्ठा cm_rej_msg *)work->mad_recv_wc->recv_buf.mad;
	param = &work->cm_event.param.rej_rcvd;
	param->ari = IBA_GET_MEM_PTR(CM_REJ_ARI, rej_msg);
	param->ari_length = IBA_GET(CM_REJ_REJECTED_INFO_LENGTH, rej_msg);
	param->reason = IBA_GET(CM_REJ_REASON, rej_msg);
	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_REJ_PRIVATE_DATA, rej_msg);
पूर्ण

अटल काष्ठा cm_id_निजी *cm_acquire_rejected_id(काष्ठा cm_rej_msg *rej_msg)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	__be32 remote_id;

	remote_id = cpu_to_be32(IBA_GET(CM_REJ_LOCAL_COMM_ID, rej_msg));

	अगर (IBA_GET(CM_REJ_REASON, rej_msg) == IB_CM_REJ_TIMEOUT) अणु
		cm_id_priv = cm_find_remote_id(
			*((__be64 *)IBA_GET_MEM_PTR(CM_REJ_ARI, rej_msg)),
			remote_id);
	पूर्ण अन्यथा अगर (IBA_GET(CM_REJ_MESSAGE_REJECTED, rej_msg) ==
		   CM_MSG_RESPONSE_REQ)
		cm_id_priv = cm_acquire_id(
			cpu_to_be32(IBA_GET(CM_REJ_REMOTE_COMM_ID, rej_msg)),
			0);
	अन्यथा
		cm_id_priv = cm_acquire_id(
			cpu_to_be32(IBA_GET(CM_REJ_REMOTE_COMM_ID, rej_msg)),
			remote_id);

	वापस cm_id_priv;
पूर्ण

अटल पूर्णांक cm_rej_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_rej_msg *rej_msg;

	rej_msg = (काष्ठा cm_rej_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_rejected_id(rej_msg);
	अगर (!cm_id_priv)
		वापस -EINVAL;

	cm_क्रमmat_rej_event(work);

	spin_lock_irq(&cm_id_priv->lock);
	चयन (cm_id_priv->id.state) अणु
	हाल IB_CM_REQ_SENT:
	हाल IB_CM_MRA_REQ_RCVD:
	हाल IB_CM_REP_SENT:
	हाल IB_CM_MRA_REP_RCVD:
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		fallthrough;
	हाल IB_CM_REQ_RCVD:
	हाल IB_CM_MRA_REQ_SENT:
		अगर (IBA_GET(CM_REJ_REASON, rej_msg) == IB_CM_REJ_STALE_CONN)
			cm_enter_समयरुको(cm_id_priv);
		अन्यथा
			cm_reset_to_idle(cm_id_priv);
		अवरोध;
	हाल IB_CM_DREQ_SENT:
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		fallthrough;
	हाल IB_CM_REP_RCVD:
	हाल IB_CM_MRA_REP_SENT:
		cm_enter_समयरुको(cm_id_priv);
		अवरोध;
	हाल IB_CM_ESTABLISHED:
		अगर (cm_id_priv->id.lap_state == IB_CM_LAP_UNINIT ||
		    cm_id_priv->id.lap_state == IB_CM_LAP_SENT) अणु
			अगर (cm_id_priv->id.lap_state == IB_CM_LAP_SENT)
				ib_cancel_mad(cm_id_priv->av.port->mad_agent,
					      cm_id_priv->msg);
			cm_enter_समयरुको(cm_id_priv);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		trace_icm_rej_unknown_err(&cm_id_priv->id);
		spin_unlock_irq(&cm_id_priv->lock);
		जाओ out;
	पूर्ण

	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;
out:
	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

पूर्णांक ib_send_cm_mra(काष्ठा ib_cm_id *cm_id,
		   u8 service_समयout,
		   स्थिर व्योम *निजी_data,
		   u8 निजी_data_len)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा ib_mad_send_buf *msg;
	क्रमागत ib_cm_state cm_state;
	क्रमागत ib_cm_lap_state lap_state;
	क्रमागत cm_msg_response msg_response;
	व्योम *data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (निजी_data && निजी_data_len > IB_CM_MRA_PRIVATE_DATA_SIZE)
		वापस -EINVAL;

	data = cm_copy_निजी_data(निजी_data, निजी_data_len);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	cm_id_priv = container_of(cm_id, काष्ठा cm_id_निजी, id);

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	चयन (cm_id_priv->id.state) अणु
	हाल IB_CM_REQ_RCVD:
		cm_state = IB_CM_MRA_REQ_SENT;
		lap_state = cm_id->lap_state;
		msg_response = CM_MSG_RESPONSE_REQ;
		अवरोध;
	हाल IB_CM_REP_RCVD:
		cm_state = IB_CM_MRA_REP_SENT;
		lap_state = cm_id->lap_state;
		msg_response = CM_MSG_RESPONSE_REP;
		अवरोध;
	हाल IB_CM_ESTABLISHED:
		अगर (cm_id->lap_state == IB_CM_LAP_RCVD) अणु
			cm_state = cm_id->state;
			lap_state = IB_CM_MRA_LAP_SENT;
			msg_response = CM_MSG_RESPONSE_OTHER;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		trace_icm_send_mra_unknown_err(&cm_id_priv->id);
		ret = -EINVAL;
		जाओ error1;
	पूर्ण

	अगर (!(service_समयout & IB_CM_MRA_FLAG_DELAY)) अणु
		ret = cm_alloc_msg(cm_id_priv, &msg);
		अगर (ret)
			जाओ error1;

		cm_क्रमmat_mra((काष्ठा cm_mra_msg *) msg->mad, cm_id_priv,
			      msg_response, service_समयout,
			      निजी_data, निजी_data_len);
		trace_icm_send_mra(cm_id);
		ret = ib_post_send_mad(msg, शून्य);
		अगर (ret)
			जाओ error2;
	पूर्ण

	cm_id->state = cm_state;
	cm_id->lap_state = lap_state;
	cm_id_priv->service_समयout = service_समयout;
	cm_set_निजी_data(cm_id_priv, data, निजी_data_len);
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस 0;

error1:	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	kमुक्त(data);
	वापस ret;

error2:	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	kमुक्त(data);
	cm_मुक्त_msg(msg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_send_cm_mra);

अटल काष्ठा cm_id_निजी *cm_acquire_mraed_id(काष्ठा cm_mra_msg *mra_msg)
अणु
	चयन (IBA_GET(CM_MRA_MESSAGE_MRAED, mra_msg)) अणु
	हाल CM_MSG_RESPONSE_REQ:
		वापस cm_acquire_id(
			cpu_to_be32(IBA_GET(CM_MRA_REMOTE_COMM_ID, mra_msg)),
			0);
	हाल CM_MSG_RESPONSE_REP:
	हाल CM_MSG_RESPONSE_OTHER:
		वापस cm_acquire_id(
			cpu_to_be32(IBA_GET(CM_MRA_REMOTE_COMM_ID, mra_msg)),
			cpu_to_be32(IBA_GET(CM_MRA_LOCAL_COMM_ID, mra_msg)));
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक cm_mra_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_mra_msg *mra_msg;
	पूर्णांक समयout;

	mra_msg = (काष्ठा cm_mra_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_mraed_id(mra_msg);
	अगर (!cm_id_priv)
		वापस -EINVAL;

	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_MRA_PRIVATE_DATA, mra_msg);
	work->cm_event.param.mra_rcvd.service_समयout =
		IBA_GET(CM_MRA_SERVICE_TIMEOUT, mra_msg);
	समयout = cm_convert_to_ms(IBA_GET(CM_MRA_SERVICE_TIMEOUT, mra_msg)) +
		  cm_convert_to_ms(cm_id_priv->av.समयout);

	spin_lock_irq(&cm_id_priv->lock);
	चयन (cm_id_priv->id.state) अणु
	हाल IB_CM_REQ_SENT:
		अगर (IBA_GET(CM_MRA_MESSAGE_MRAED, mra_msg) !=
			    CM_MSG_RESPONSE_REQ ||
		    ib_modअगरy_mad(cm_id_priv->av.port->mad_agent,
				  cm_id_priv->msg, समयout))
			जाओ out;
		cm_id_priv->id.state = IB_CM_MRA_REQ_RCVD;
		अवरोध;
	हाल IB_CM_REP_SENT:
		अगर (IBA_GET(CM_MRA_MESSAGE_MRAED, mra_msg) !=
			    CM_MSG_RESPONSE_REP ||
		    ib_modअगरy_mad(cm_id_priv->av.port->mad_agent,
				  cm_id_priv->msg, समयout))
			जाओ out;
		cm_id_priv->id.state = IB_CM_MRA_REP_RCVD;
		अवरोध;
	हाल IB_CM_ESTABLISHED:
		अगर (IBA_GET(CM_MRA_MESSAGE_MRAED, mra_msg) !=
			    CM_MSG_RESPONSE_OTHER ||
		    cm_id_priv->id.lap_state != IB_CM_LAP_SENT ||
		    ib_modअगरy_mad(cm_id_priv->av.port->mad_agent,
				  cm_id_priv->msg, समयout)) अणु
			अगर (cm_id_priv->id.lap_state == IB_CM_MRA_LAP_RCVD)
				atomic_दीर्घ_inc(&work->port->
						counter_group[CM_RECV_DUPLICATES].
						counter[CM_MRA_COUNTER]);
			जाओ out;
		पूर्ण
		cm_id_priv->id.lap_state = IB_CM_MRA_LAP_RCVD;
		अवरोध;
	हाल IB_CM_MRA_REQ_RCVD:
	हाल IB_CM_MRA_REP_RCVD:
		atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_MRA_COUNTER]);
		fallthrough;
	शेष:
		trace_icm_mra_unknown_err(&cm_id_priv->id);
		जाओ out;
	पूर्ण

	cm_id_priv->msg->context[1] = (व्योम *) (अचिन्हित दीर्घ)
				      cm_id_priv->id.state;
	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;
out:
	spin_unlock_irq(&cm_id_priv->lock);
	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

अटल व्योम cm_क्रमmat_path_lid_from_lap(काष्ठा cm_lap_msg *lap_msg,
					काष्ठा sa_path_rec *path)
अणु
	u32 lid;

	अगर (path->rec_type != SA_PATH_REC_TYPE_OPA) अणु
		sa_path_set_dlid(path, IBA_GET(CM_LAP_ALTERNATE_LOCAL_PORT_LID,
					       lap_msg));
		sa_path_set_slid(path, IBA_GET(CM_LAP_ALTERNATE_REMOTE_PORT_LID,
					       lap_msg));
	पूर्ण अन्यथा अणु
		lid = opa_get_lid_from_gid(IBA_GET_MEM_PTR(
			CM_LAP_ALTERNATE_LOCAL_PORT_GID, lap_msg));
		sa_path_set_dlid(path, lid);

		lid = opa_get_lid_from_gid(IBA_GET_MEM_PTR(
			CM_LAP_ALTERNATE_REMOTE_PORT_GID, lap_msg));
		sa_path_set_slid(path, lid);
	पूर्ण
पूर्ण

अटल व्योम cm_क्रमmat_path_from_lap(काष्ठा cm_id_निजी *cm_id_priv,
				    काष्ठा sa_path_rec *path,
				    काष्ठा cm_lap_msg *lap_msg)
अणु
	path->dgid = *IBA_GET_MEM_PTR(CM_LAP_ALTERNATE_LOCAL_PORT_GID, lap_msg);
	path->sgid =
		*IBA_GET_MEM_PTR(CM_LAP_ALTERNATE_REMOTE_PORT_GID, lap_msg);
	path->flow_label =
		cpu_to_be32(IBA_GET(CM_LAP_ALTERNATE_FLOW_LABEL, lap_msg));
	path->hop_limit = IBA_GET(CM_LAP_ALTERNATE_HOP_LIMIT, lap_msg);
	path->traffic_class = IBA_GET(CM_LAP_ALTERNATE_TRAFFIC_CLASS, lap_msg);
	path->reversible = 1;
	path->pkey = cm_id_priv->pkey;
	path->sl = IBA_GET(CM_LAP_ALTERNATE_SL, lap_msg);
	path->mtu_selector = IB_SA_EQ;
	path->mtu = cm_id_priv->path_mtu;
	path->rate_selector = IB_SA_EQ;
	path->rate = IBA_GET(CM_LAP_ALTERNATE_PACKET_RATE, lap_msg);
	path->packet_lअगरe_समय_selector = IB_SA_EQ;
	path->packet_lअगरe_समय =
		IBA_GET(CM_LAP_ALTERNATE_LOCAL_ACK_TIMEOUT, lap_msg);
	path->packet_lअगरe_समय -= (path->packet_lअगरe_समय > 0);
	cm_क्रमmat_path_lid_from_lap(lap_msg, path);
पूर्ण

अटल पूर्णांक cm_lap_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_lap_msg *lap_msg;
	काष्ठा ib_cm_lap_event_param *param;
	काष्ठा ib_mad_send_buf *msg = शून्य;
	पूर्णांक ret;

	/* Currently Alternate path messages are not supported क्रम
	 * RoCE link layer.
	 */
	अगर (rdma_protocol_roce(work->port->cm_dev->ib_device,
			       work->port->port_num))
		वापस -EINVAL;

	/* toकरो: verअगरy LAP request and send reject APR अगर invalid. */
	lap_msg = (काष्ठा cm_lap_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(
		cpu_to_be32(IBA_GET(CM_LAP_REMOTE_COMM_ID, lap_msg)),
		cpu_to_be32(IBA_GET(CM_LAP_LOCAL_COMM_ID, lap_msg)));
	अगर (!cm_id_priv)
		वापस -EINVAL;

	param = &work->cm_event.param.lap_rcvd;
	स_रखो(&work->path[0], 0, माप(work->path[1]));
	cm_path_set_rec_type(work->port->cm_dev->ib_device,
			     work->port->port_num, &work->path[0],
			     IBA_GET_MEM_PTR(CM_LAP_ALTERNATE_LOCAL_PORT_GID,
					     lap_msg));
	param->alternate_path = &work->path[0];
	cm_क्रमmat_path_from_lap(cm_id_priv, param->alternate_path, lap_msg);
	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_LAP_PRIVATE_DATA, lap_msg);

	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->id.state != IB_CM_ESTABLISHED)
		जाओ unlock;

	चयन (cm_id_priv->id.lap_state) अणु
	हाल IB_CM_LAP_UNINIT:
	हाल IB_CM_LAP_IDLE:
		अवरोध;
	हाल IB_CM_MRA_LAP_SENT:
		atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_LAP_COUNTER]);
		msg = cm_alloc_response_msg_no_ah(work->port, work->mad_recv_wc);
		अगर (IS_ERR(msg))
			जाओ unlock;

		cm_क्रमmat_mra((काष्ठा cm_mra_msg *) msg->mad, cm_id_priv,
			      CM_MSG_RESPONSE_OTHER,
			      cm_id_priv->service_समयout,
			      cm_id_priv->निजी_data,
			      cm_id_priv->निजी_data_len);
		spin_unlock_irq(&cm_id_priv->lock);

		अगर (cm_create_response_msg_ah(work->port, work->mad_recv_wc, msg) ||
		    ib_post_send_mad(msg, शून्य))
			cm_मुक्त_msg(msg);
		जाओ deref;
	हाल IB_CM_LAP_RCVD:
		atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_LAP_COUNTER]);
		जाओ unlock;
	शेष:
		जाओ unlock;
	पूर्ण

	ret = cm_init_av_क्रम_lap(work->port, work->mad_recv_wc->wc,
				 work->mad_recv_wc->recv_buf.grh,
				 &cm_id_priv->av);
	अगर (ret)
		जाओ unlock;

	ret = cm_init_av_by_path(param->alternate_path, शून्य,
				 &cm_id_priv->alt_av, cm_id_priv);
	अगर (ret)
		जाओ unlock;

	cm_id_priv->id.lap_state = IB_CM_LAP_RCVD;
	cm_id_priv->tid = lap_msg->hdr.tid;
	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;

unlock:	spin_unlock_irq(&cm_id_priv->lock);
deref:	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cm_apr_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_apr_msg *apr_msg;

	/* Currently Alternate path messages are not supported क्रम
	 * RoCE link layer.
	 */
	अगर (rdma_protocol_roce(work->port->cm_dev->ib_device,
			       work->port->port_num))
		वापस -EINVAL;

	apr_msg = (काष्ठा cm_apr_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(
		cpu_to_be32(IBA_GET(CM_APR_REMOTE_COMM_ID, apr_msg)),
		cpu_to_be32(IBA_GET(CM_APR_LOCAL_COMM_ID, apr_msg)));
	अगर (!cm_id_priv)
		वापस -EINVAL; /* Unmatched reply. */

	work->cm_event.param.apr_rcvd.ap_status =
		IBA_GET(CM_APR_AR_STATUS, apr_msg);
	work->cm_event.param.apr_rcvd.apr_info =
		IBA_GET_MEM_PTR(CM_APR_ADDITIONAL_INFORMATION, apr_msg);
	work->cm_event.param.apr_rcvd.info_len =
		IBA_GET(CM_APR_ADDITIONAL_INFORMATION_LENGTH, apr_msg);
	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_APR_PRIVATE_DATA, apr_msg);

	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->id.state != IB_CM_ESTABLISHED ||
	    (cm_id_priv->id.lap_state != IB_CM_LAP_SENT &&
	     cm_id_priv->id.lap_state != IB_CM_MRA_LAP_RCVD)) अणु
		spin_unlock_irq(&cm_id_priv->lock);
		जाओ out;
	पूर्ण
	cm_id_priv->id.lap_state = IB_CM_LAP_IDLE;
	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
	cm_id_priv->msg = शून्य;
	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;
out:
	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cm_समयरुको_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_समयरुको_info *समयरुको_info;
	काष्ठा cm_id_निजी *cm_id_priv;

	समयरुको_info = container_of(work, काष्ठा cm_समयरुको_info, work);
	spin_lock_irq(&cm.lock);
	list_del(&समयरुको_info->list);
	spin_unlock_irq(&cm.lock);

	cm_id_priv = cm_acquire_id(समयरुको_info->work.local_id,
				   समयरुको_info->work.remote_id);
	अगर (!cm_id_priv)
		वापस -EINVAL;

	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->id.state != IB_CM_TIMEWAIT ||
	    cm_id_priv->remote_qpn != समयरुको_info->remote_qpn) अणु
		spin_unlock_irq(&cm_id_priv->lock);
		जाओ out;
	पूर्ण
	cm_id_priv->id.state = IB_CM_IDLE;
	cm_queue_work_unlock(cm_id_priv, work);
	वापस 0;
out:
	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

अटल व्योम cm_क्रमmat_sidr_req(काष्ठा cm_sidr_req_msg *sidr_req_msg,
			       काष्ठा cm_id_निजी *cm_id_priv,
			       काष्ठा ib_cm_sidr_req_param *param)
अणु
	cm_क्रमmat_mad_hdr(&sidr_req_msg->hdr, CM_SIDR_REQ_ATTR_ID,
			  cm_क्रमm_tid(cm_id_priv));
	IBA_SET(CM_SIDR_REQ_REQUESTID, sidr_req_msg,
		be32_to_cpu(cm_id_priv->id.local_id));
	IBA_SET(CM_SIDR_REQ_PARTITION_KEY, sidr_req_msg,
		be16_to_cpu(param->path->pkey));
	IBA_SET(CM_SIDR_REQ_SERVICEID, sidr_req_msg,
		be64_to_cpu(param->service_id));

	अगर (param->निजी_data && param->निजी_data_len)
		IBA_SET_MEM(CM_SIDR_REQ_PRIVATE_DATA, sidr_req_msg,
			    param->निजी_data, param->निजी_data_len);
पूर्ण

पूर्णांक ib_send_cm_sidr_req(काष्ठा ib_cm_id *cm_id,
			काष्ठा ib_cm_sidr_req_param *param)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा ib_mad_send_buf *msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!param->path || (param->निजी_data &&
	     param->निजी_data_len > IB_CM_SIDR_REQ_PRIVATE_DATA_SIZE))
		वापस -EINVAL;

	cm_id_priv = container_of(cm_id, काष्ठा cm_id_निजी, id);
	ret = cm_init_av_by_path(param->path, param->sgid_attr,
				 &cm_id_priv->av,
				 cm_id_priv);
	अगर (ret)
		जाओ out;

	cm_id->service_id = param->service_id;
	cm_id->service_mask = ~cpu_to_be64(0);
	cm_id_priv->समयout_ms = param->समयout_ms;
	cm_id_priv->max_cm_retries = param->max_cm_retries;
	ret = cm_alloc_msg(cm_id_priv, &msg);
	अगर (ret)
		जाओ out;

	cm_क्रमmat_sidr_req((काष्ठा cm_sidr_req_msg *) msg->mad, cm_id_priv,
			   param);
	msg->समयout_ms = cm_id_priv->समयout_ms;
	msg->context[1] = (व्योम *) (अचिन्हित दीर्घ) IB_CM_SIDR_REQ_SENT;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	अगर (cm_id->state == IB_CM_IDLE) अणु
		trace_icm_send_sidr_req(&cm_id_priv->id);
		ret = ib_post_send_mad(msg, शून्य);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	अगर (ret) अणु
		spin_unlock_irqrestore(&cm_id_priv->lock, flags);
		cm_मुक्त_msg(msg);
		जाओ out;
	पूर्ण
	cm_id->state = IB_CM_SIDR_REQ_SENT;
	cm_id_priv->msg = msg;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_send_cm_sidr_req);

अटल व्योम cm_क्रमmat_sidr_req_event(काष्ठा cm_work *work,
				     स्थिर काष्ठा cm_id_निजी *rx_cm_id,
				     काष्ठा ib_cm_id *listen_id)
अणु
	काष्ठा cm_sidr_req_msg *sidr_req_msg;
	काष्ठा ib_cm_sidr_req_event_param *param;

	sidr_req_msg = (काष्ठा cm_sidr_req_msg *)
				work->mad_recv_wc->recv_buf.mad;
	param = &work->cm_event.param.sidr_req_rcvd;
	param->pkey = IBA_GET(CM_SIDR_REQ_PARTITION_KEY, sidr_req_msg);
	param->listen_id = listen_id;
	param->service_id =
		cpu_to_be64(IBA_GET(CM_SIDR_REQ_SERVICEID, sidr_req_msg));
	param->bth_pkey = cm_get_bth_pkey(work);
	param->port = work->port->port_num;
	param->sgid_attr = rx_cm_id->av.ah_attr.grh.sgid_attr;
	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_SIDR_REQ_PRIVATE_DATA, sidr_req_msg);
पूर्ण

अटल पूर्णांक cm_sidr_req_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_id_निजी *cm_id_priv, *listen_cm_id_priv;
	काष्ठा cm_sidr_req_msg *sidr_req_msg;
	काष्ठा ib_wc *wc;
	पूर्णांक ret;

	cm_id_priv =
		cm_alloc_id_priv(work->port->cm_dev->ib_device, शून्य, शून्य);
	अगर (IS_ERR(cm_id_priv))
		वापस PTR_ERR(cm_id_priv);

	/* Record SGID/SLID and request ID क्रम lookup. */
	sidr_req_msg = (काष्ठा cm_sidr_req_msg *)
				work->mad_recv_wc->recv_buf.mad;

	cm_id_priv->id.remote_id =
		cpu_to_be32(IBA_GET(CM_SIDR_REQ_REQUESTID, sidr_req_msg));
	cm_id_priv->id.service_id =
		cpu_to_be64(IBA_GET(CM_SIDR_REQ_SERVICEID, sidr_req_msg));
	cm_id_priv->id.service_mask = ~cpu_to_be64(0);
	cm_id_priv->tid = sidr_req_msg->hdr.tid;

	wc = work->mad_recv_wc->wc;
	cm_id_priv->av.dgid.global.subnet_prefix = cpu_to_be64(wc->slid);
	cm_id_priv->av.dgid.global.पूर्णांकerface_id = 0;
	ret = cm_init_av_क्रम_response(work->port, work->mad_recv_wc->wc,
				      work->mad_recv_wc->recv_buf.grh,
				      &cm_id_priv->av);
	अगर (ret)
		जाओ out;

	spin_lock_irq(&cm.lock);
	listen_cm_id_priv = cm_insert_remote_sidr(cm_id_priv);
	अगर (listen_cm_id_priv) अणु
		spin_unlock_irq(&cm.lock);
		atomic_दीर्घ_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_SIDR_REQ_COUNTER]);
		जाओ out; /* Duplicate message. */
	पूर्ण
	cm_id_priv->id.state = IB_CM_SIDR_REQ_RCVD;
	listen_cm_id_priv = cm_find_listen(cm_id_priv->id.device,
					   cm_id_priv->id.service_id);
	अगर (!listen_cm_id_priv) अणु
		spin_unlock_irq(&cm.lock);
		ib_send_cm_sidr_rep(&cm_id_priv->id,
				    &(काष्ठा ib_cm_sidr_rep_param)अणु
					    .status = IB_SIDR_UNSUPPORTED पूर्ण);
		जाओ out; /* No match. */
	पूर्ण
	spin_unlock_irq(&cm.lock);

	cm_id_priv->id.cm_handler = listen_cm_id_priv->id.cm_handler;
	cm_id_priv->id.context = listen_cm_id_priv->id.context;

	/*
	 * A SIDR ID करोes not need to be in the xarray since it करोes not receive
	 * mads, is not placed in the remote_id or remote_qpn rbtree, and करोes
	 * not enter समयरुको.
	 */

	cm_क्रमmat_sidr_req_event(work, cm_id_priv, &listen_cm_id_priv->id);
	ret = cm_id_priv->id.cm_handler(&cm_id_priv->id, &work->cm_event);
	cm_मुक्त_work(work);
	/*
	 * A poपूर्णांकer to the listen_cm_id is held in the event, so this deref
	 * must be after the event is delivered above.
	 */
	cm_deref_id(listen_cm_id_priv);
	अगर (ret)
		cm_destroy_id(&cm_id_priv->id, ret);
	वापस 0;
out:
	ib_destroy_cm_id(&cm_id_priv->id);
	वापस -EINVAL;
पूर्ण

अटल व्योम cm_क्रमmat_sidr_rep(काष्ठा cm_sidr_rep_msg *sidr_rep_msg,
			       काष्ठा cm_id_निजी *cm_id_priv,
			       काष्ठा ib_cm_sidr_rep_param *param)
अणु
	cm_क्रमmat_mad_ece_hdr(&sidr_rep_msg->hdr, CM_SIDR_REP_ATTR_ID,
			      cm_id_priv->tid, param->ece.attr_mod);
	IBA_SET(CM_SIDR_REP_REQUESTID, sidr_rep_msg,
		be32_to_cpu(cm_id_priv->id.remote_id));
	IBA_SET(CM_SIDR_REP_STATUS, sidr_rep_msg, param->status);
	IBA_SET(CM_SIDR_REP_QPN, sidr_rep_msg, param->qp_num);
	IBA_SET(CM_SIDR_REP_SERVICEID, sidr_rep_msg,
		be64_to_cpu(cm_id_priv->id.service_id));
	IBA_SET(CM_SIDR_REP_Q_KEY, sidr_rep_msg, param->qkey);
	IBA_SET(CM_SIDR_REP_VENDOR_ID_L, sidr_rep_msg,
		param->ece.venकरोr_id & 0xFF);
	IBA_SET(CM_SIDR_REP_VENDOR_ID_H, sidr_rep_msg,
		(param->ece.venकरोr_id >> 8) & 0xFF);

	अगर (param->info && param->info_length)
		IBA_SET_MEM(CM_SIDR_REP_ADDITIONAL_INFORMATION, sidr_rep_msg,
			    param->info, param->info_length);

	अगर (param->निजी_data && param->निजी_data_len)
		IBA_SET_MEM(CM_SIDR_REP_PRIVATE_DATA, sidr_rep_msg,
			    param->निजी_data, param->निजी_data_len);
पूर्ण

अटल पूर्णांक cm_send_sidr_rep_locked(काष्ठा cm_id_निजी *cm_id_priv,
				   काष्ठा ib_cm_sidr_rep_param *param)
अणु
	काष्ठा ib_mad_send_buf *msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	lockdep_निश्चित_held(&cm_id_priv->lock);

	अगर ((param->info && param->info_length > IB_CM_SIDR_REP_INFO_LENGTH) ||
	    (param->निजी_data &&
	     param->निजी_data_len > IB_CM_SIDR_REP_PRIVATE_DATA_SIZE))
		वापस -EINVAL;

	अगर (cm_id_priv->id.state != IB_CM_SIDR_REQ_RCVD)
		वापस -EINVAL;

	ret = cm_alloc_msg(cm_id_priv, &msg);
	अगर (ret)
		वापस ret;

	cm_क्रमmat_sidr_rep((काष्ठा cm_sidr_rep_msg *) msg->mad, cm_id_priv,
			   param);
	trace_icm_send_sidr_rep(&cm_id_priv->id);
	ret = ib_post_send_mad(msg, शून्य);
	अगर (ret) अणु
		cm_मुक्त_msg(msg);
		वापस ret;
	पूर्ण
	cm_id_priv->id.state = IB_CM_IDLE;
	spin_lock_irqsave(&cm.lock, flags);
	अगर (!RB_EMPTY_NODE(&cm_id_priv->sidr_id_node)) अणु
		rb_erase(&cm_id_priv->sidr_id_node, &cm.remote_sidr_table);
		RB_CLEAR_NODE(&cm_id_priv->sidr_id_node);
	पूर्ण
	spin_unlock_irqrestore(&cm.lock, flags);
	वापस 0;
पूर्ण

पूर्णांक ib_send_cm_sidr_rep(काष्ठा ib_cm_id *cm_id,
			काष्ठा ib_cm_sidr_rep_param *param)
अणु
	काष्ठा cm_id_निजी *cm_id_priv =
		container_of(cm_id, काष्ठा cm_id_निजी, id);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	ret = cm_send_sidr_rep_locked(cm_id_priv, param);
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_send_cm_sidr_rep);

अटल व्योम cm_क्रमmat_sidr_rep_event(काष्ठा cm_work *work,
				     स्थिर काष्ठा cm_id_निजी *cm_id_priv)
अणु
	काष्ठा cm_sidr_rep_msg *sidr_rep_msg;
	काष्ठा ib_cm_sidr_rep_event_param *param;

	sidr_rep_msg = (काष्ठा cm_sidr_rep_msg *)
				work->mad_recv_wc->recv_buf.mad;
	param = &work->cm_event.param.sidr_rep_rcvd;
	param->status = IBA_GET(CM_SIDR_REP_STATUS, sidr_rep_msg);
	param->qkey = IBA_GET(CM_SIDR_REP_Q_KEY, sidr_rep_msg);
	param->qpn = IBA_GET(CM_SIDR_REP_QPN, sidr_rep_msg);
	param->info = IBA_GET_MEM_PTR(CM_SIDR_REP_ADDITIONAL_INFORMATION,
				      sidr_rep_msg);
	param->info_len = IBA_GET(CM_SIDR_REP_ADDITIONAL_INFORMATION_LENGTH,
				  sidr_rep_msg);
	param->sgid_attr = cm_id_priv->av.ah_attr.grh.sgid_attr;
	work->cm_event.निजी_data =
		IBA_GET_MEM_PTR(CM_SIDR_REP_PRIVATE_DATA, sidr_rep_msg);
पूर्ण

अटल पूर्णांक cm_sidr_rep_handler(काष्ठा cm_work *work)
अणु
	काष्ठा cm_sidr_rep_msg *sidr_rep_msg;
	काष्ठा cm_id_निजी *cm_id_priv;

	sidr_rep_msg = (काष्ठा cm_sidr_rep_msg *)
				work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(
		cpu_to_be32(IBA_GET(CM_SIDR_REP_REQUESTID, sidr_rep_msg)), 0);
	अगर (!cm_id_priv)
		वापस -EINVAL; /* Unmatched reply. */

	spin_lock_irq(&cm_id_priv->lock);
	अगर (cm_id_priv->id.state != IB_CM_SIDR_REQ_SENT) अणु
		spin_unlock_irq(&cm_id_priv->lock);
		जाओ out;
	पूर्ण
	cm_id_priv->id.state = IB_CM_IDLE;
	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
	spin_unlock_irq(&cm_id_priv->lock);

	cm_क्रमmat_sidr_rep_event(work, cm_id_priv);
	cm_process_work(cm_id_priv, work);
	वापस 0;
out:
	cm_deref_id(cm_id_priv);
	वापस -EINVAL;
पूर्ण

अटल व्योम cm_process_send_error(काष्ठा ib_mad_send_buf *msg,
				  क्रमागत ib_wc_status wc_status)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा ib_cm_event cm_event;
	क्रमागत ib_cm_state state;
	पूर्णांक ret;

	स_रखो(&cm_event, 0, माप cm_event);
	cm_id_priv = msg->context[0];

	/* Discard old sends or ones without a response. */
	spin_lock_irq(&cm_id_priv->lock);
	state = (क्रमागत ib_cm_state) (अचिन्हित दीर्घ) msg->context[1];
	अगर (msg != cm_id_priv->msg || state != cm_id_priv->id.state)
		जाओ discard;

	trace_icm_mad_send_err(state, wc_status);
	चयन (state) अणु
	हाल IB_CM_REQ_SENT:
	हाल IB_CM_MRA_REQ_RCVD:
		cm_reset_to_idle(cm_id_priv);
		cm_event.event = IB_CM_REQ_ERROR;
		अवरोध;
	हाल IB_CM_REP_SENT:
	हाल IB_CM_MRA_REP_RCVD:
		cm_reset_to_idle(cm_id_priv);
		cm_event.event = IB_CM_REP_ERROR;
		अवरोध;
	हाल IB_CM_DREQ_SENT:
		cm_enter_समयरुको(cm_id_priv);
		cm_event.event = IB_CM_DREQ_ERROR;
		अवरोध;
	हाल IB_CM_SIDR_REQ_SENT:
		cm_id_priv->id.state = IB_CM_IDLE;
		cm_event.event = IB_CM_SIDR_REQ_ERROR;
		अवरोध;
	शेष:
		जाओ discard;
	पूर्ण
	spin_unlock_irq(&cm_id_priv->lock);
	cm_event.param.send_status = wc_status;

	/* No other events can occur on the cm_id at this poपूर्णांक. */
	ret = cm_id_priv->id.cm_handler(&cm_id_priv->id, &cm_event);
	cm_मुक्त_msg(msg);
	अगर (ret)
		ib_destroy_cm_id(&cm_id_priv->id);
	वापस;
discard:
	spin_unlock_irq(&cm_id_priv->lock);
	cm_मुक्त_msg(msg);
पूर्ण

अटल व्योम cm_send_handler(काष्ठा ib_mad_agent *mad_agent,
			    काष्ठा ib_mad_send_wc *mad_send_wc)
अणु
	काष्ठा ib_mad_send_buf *msg = mad_send_wc->send_buf;
	काष्ठा cm_port *port;
	u16 attr_index;

	port = mad_agent->context;
	attr_index = be16_to_cpu(((काष्ठा ib_mad_hdr *)
				  msg->mad)->attr_id) - CM_ATTR_ID_OFFSET;

	/*
	 * If the send was in response to a received message (context[0] is not
	 * set to a cm_id), and is not a REJ, then it is a send that was
	 * manually retried.
	 */
	अगर (!msg->context[0] && (attr_index != CM_REJ_COUNTER))
		msg->retries = 1;

	atomic_दीर्घ_add(1 + msg->retries,
			&port->counter_group[CM_XMIT].counter[attr_index]);
	अगर (msg->retries)
		atomic_दीर्घ_add(msg->retries,
				&port->counter_group[CM_XMIT_RETRIES].
				counter[attr_index]);

	चयन (mad_send_wc->status) अणु
	हाल IB_WC_SUCCESS:
	हाल IB_WC_WR_FLUSH_ERR:
		cm_मुक्त_msg(msg);
		अवरोध;
	शेष:
		अगर (msg->context[0] && msg->context[1])
			cm_process_send_error(msg, mad_send_wc->status);
		अन्यथा
			cm_मुक्त_msg(msg);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cm_work_handler(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा cm_work *work = container_of(_work, काष्ठा cm_work, work.work);
	पूर्णांक ret;

	चयन (work->cm_event.event) अणु
	हाल IB_CM_REQ_RECEIVED:
		ret = cm_req_handler(work);
		अवरोध;
	हाल IB_CM_MRA_RECEIVED:
		ret = cm_mra_handler(work);
		अवरोध;
	हाल IB_CM_REJ_RECEIVED:
		ret = cm_rej_handler(work);
		अवरोध;
	हाल IB_CM_REP_RECEIVED:
		ret = cm_rep_handler(work);
		अवरोध;
	हाल IB_CM_RTU_RECEIVED:
		ret = cm_rtu_handler(work);
		अवरोध;
	हाल IB_CM_USER_ESTABLISHED:
		ret = cm_establish_handler(work);
		अवरोध;
	हाल IB_CM_DREQ_RECEIVED:
		ret = cm_dreq_handler(work);
		अवरोध;
	हाल IB_CM_DREP_RECEIVED:
		ret = cm_drep_handler(work);
		अवरोध;
	हाल IB_CM_SIDR_REQ_RECEIVED:
		ret = cm_sidr_req_handler(work);
		अवरोध;
	हाल IB_CM_SIDR_REP_RECEIVED:
		ret = cm_sidr_rep_handler(work);
		अवरोध;
	हाल IB_CM_LAP_RECEIVED:
		ret = cm_lap_handler(work);
		अवरोध;
	हाल IB_CM_APR_RECEIVED:
		ret = cm_apr_handler(work);
		अवरोध;
	हाल IB_CM_TIMEWAIT_EXIT:
		ret = cm_समयरुको_handler(work);
		अवरोध;
	शेष:
		trace_icm_handler_err(work->cm_event.event);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (ret)
		cm_मुक्त_work(work);
पूर्ण

अटल पूर्णांक cm_establish(काष्ठा ib_cm_id *cm_id)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_work *work;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	काष्ठा cm_device *cm_dev;

	cm_dev = ib_get_client_data(cm_id->device, &cm_client);
	अगर (!cm_dev)
		वापस -ENODEV;

	work = kदो_स्मृति(माप *work, GFP_ATOMIC);
	अगर (!work)
		वापस -ENOMEM;

	cm_id_priv = container_of(cm_id, काष्ठा cm_id_निजी, id);
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	चयन (cm_id->state) अणु
	हाल IB_CM_REP_SENT:
	हाल IB_CM_MRA_REP_RCVD:
		cm_id->state = IB_CM_ESTABLISHED;
		अवरोध;
	हाल IB_CM_ESTABLISHED:
		ret = -EISCONN;
		अवरोध;
	शेष:
		trace_icm_establish_err(cm_id);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	अगर (ret) अणु
		kमुक्त(work);
		जाओ out;
	पूर्ण

	/*
	 * The CM worker thपढ़ो may try to destroy the cm_id beक्रमe it
	 * can execute this work item.  To prevent potential deadlock,
	 * we need to find the cm_id once we're in the context of the
	 * worker thपढ़ो, rather than holding a reference on it.
	 */
	INIT_DELAYED_WORK(&work->work, cm_work_handler);
	work->local_id = cm_id->local_id;
	work->remote_id = cm_id->remote_id;
	work->mad_recv_wc = शून्य;
	work->cm_event.event = IB_CM_USER_ESTABLISHED;

	/* Check अगर the device started its हटाओ_one */
	spin_lock_irqsave(&cm.lock, flags);
	अगर (!cm_dev->going_करोwn) अणु
		queue_delayed_work(cm.wq, &work->work, 0);
	पूर्ण अन्यथा अणु
		kमुक्त(work);
		ret = -ENODEV;
	पूर्ण
	spin_unlock_irqrestore(&cm.lock, flags);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक cm_migrate(काष्ठा ib_cm_id *cm_id)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा cm_av पंचांगp_av;
	अचिन्हित दीर्घ flags;
	पूर्णांक पंचांगp_send_port_not_पढ़ोy;
	पूर्णांक ret = 0;

	cm_id_priv = container_of(cm_id, काष्ठा cm_id_निजी, id);
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	अगर (cm_id->state == IB_CM_ESTABLISHED &&
	    (cm_id->lap_state == IB_CM_LAP_UNINIT ||
	     cm_id->lap_state == IB_CM_LAP_IDLE)) अणु
		cm_id->lap_state = IB_CM_LAP_IDLE;
		/* Swap address vector */
		पंचांगp_av = cm_id_priv->av;
		cm_id_priv->av = cm_id_priv->alt_av;
		cm_id_priv->alt_av = पंचांगp_av;
		/* Swap port send पढ़ोy state */
		पंचांगp_send_port_not_पढ़ोy = cm_id_priv->prim_send_port_not_पढ़ोy;
		cm_id_priv->prim_send_port_not_पढ़ोy = cm_id_priv->altr_send_port_not_पढ़ोy;
		cm_id_priv->altr_send_port_not_पढ़ोy = पंचांगp_send_port_not_पढ़ोy;
	पूर्ण अन्यथा
		ret = -EINVAL;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	वापस ret;
पूर्ण

पूर्णांक ib_cm_notअगरy(काष्ठा ib_cm_id *cm_id, क्रमागत ib_event_type event)
अणु
	पूर्णांक ret;

	चयन (event) अणु
	हाल IB_EVENT_COMM_EST:
		ret = cm_establish(cm_id);
		अवरोध;
	हाल IB_EVENT_PATH_MIG:
		ret = cm_migrate(cm_id);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_cm_notअगरy);

अटल व्योम cm_recv_handler(काष्ठा ib_mad_agent *mad_agent,
			    काष्ठा ib_mad_send_buf *send_buf,
			    काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा cm_port *port = mad_agent->context;
	काष्ठा cm_work *work;
	क्रमागत ib_cm_event_type event;
	bool alt_path = false;
	u16 attr_id;
	पूर्णांक paths = 0;
	पूर्णांक going_करोwn = 0;

	चयन (mad_recv_wc->recv_buf.mad->mad_hdr.attr_id) अणु
	हाल CM_REQ_ATTR_ID:
		alt_path = cm_req_has_alt_path((काष्ठा cm_req_msg *)
						mad_recv_wc->recv_buf.mad);
		paths = 1 + (alt_path != 0);
		event = IB_CM_REQ_RECEIVED;
		अवरोध;
	हाल CM_MRA_ATTR_ID:
		event = IB_CM_MRA_RECEIVED;
		अवरोध;
	हाल CM_REJ_ATTR_ID:
		event = IB_CM_REJ_RECEIVED;
		अवरोध;
	हाल CM_REP_ATTR_ID:
		event = IB_CM_REP_RECEIVED;
		अवरोध;
	हाल CM_RTU_ATTR_ID:
		event = IB_CM_RTU_RECEIVED;
		अवरोध;
	हाल CM_DREQ_ATTR_ID:
		event = IB_CM_DREQ_RECEIVED;
		अवरोध;
	हाल CM_DREP_ATTR_ID:
		event = IB_CM_DREP_RECEIVED;
		अवरोध;
	हाल CM_SIDR_REQ_ATTR_ID:
		event = IB_CM_SIDR_REQ_RECEIVED;
		अवरोध;
	हाल CM_SIDR_REP_ATTR_ID:
		event = IB_CM_SIDR_REP_RECEIVED;
		अवरोध;
	हाल CM_LAP_ATTR_ID:
		paths = 1;
		event = IB_CM_LAP_RECEIVED;
		अवरोध;
	हाल CM_APR_ATTR_ID:
		event = IB_CM_APR_RECEIVED;
		अवरोध;
	शेष:
		ib_मुक्त_recv_mad(mad_recv_wc);
		वापस;
	पूर्ण

	attr_id = be16_to_cpu(mad_recv_wc->recv_buf.mad->mad_hdr.attr_id);
	atomic_दीर्घ_inc(&port->counter_group[CM_RECV].
			counter[attr_id - CM_ATTR_ID_OFFSET]);

	work = kदो_स्मृति(काष्ठा_size(work, path, paths), GFP_KERNEL);
	अगर (!work) अणु
		ib_मुक्त_recv_mad(mad_recv_wc);
		वापस;
	पूर्ण

	INIT_DELAYED_WORK(&work->work, cm_work_handler);
	work->cm_event.event = event;
	work->mad_recv_wc = mad_recv_wc;
	work->port = port;

	/* Check अगर the device started its हटाओ_one */
	spin_lock_irq(&cm.lock);
	अगर (!port->cm_dev->going_करोwn)
		queue_delayed_work(cm.wq, &work->work, 0);
	अन्यथा
		going_करोwn = 1;
	spin_unlock_irq(&cm.lock);

	अगर (going_करोwn) अणु
		kमुक्त(work);
		ib_मुक्त_recv_mad(mad_recv_wc);
	पूर्ण
पूर्ण

अटल पूर्णांक cm_init_qp_init_attr(काष्ठा cm_id_निजी *cm_id_priv,
				काष्ठा ib_qp_attr *qp_attr,
				पूर्णांक *qp_attr_mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	चयन (cm_id_priv->id.state) अणु
	हाल IB_CM_REQ_SENT:
	हाल IB_CM_MRA_REQ_RCVD:
	हाल IB_CM_REQ_RCVD:
	हाल IB_CM_MRA_REQ_SENT:
	हाल IB_CM_REP_RCVD:
	हाल IB_CM_MRA_REP_SENT:
	हाल IB_CM_REP_SENT:
	हाल IB_CM_MRA_REP_RCVD:
	हाल IB_CM_ESTABLISHED:
		*qp_attr_mask = IB_QP_STATE | IB_QP_ACCESS_FLAGS |
				IB_QP_PKEY_INDEX | IB_QP_PORT;
		qp_attr->qp_access_flags = IB_ACCESS_REMOTE_WRITE;
		अगर (cm_id_priv->responder_resources)
			qp_attr->qp_access_flags |= IB_ACCESS_REMOTE_READ |
						    IB_ACCESS_REMOTE_ATOMIC;
		qp_attr->pkey_index = cm_id_priv->av.pkey_index;
		qp_attr->port_num = cm_id_priv->av.port->port_num;
		ret = 0;
		अवरोध;
	शेष:
		trace_icm_qp_init_err(&cm_id_priv->id);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक cm_init_qp_rtr_attr(काष्ठा cm_id_निजी *cm_id_priv,
			       काष्ठा ib_qp_attr *qp_attr,
			       पूर्णांक *qp_attr_mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	चयन (cm_id_priv->id.state) अणु
	हाल IB_CM_REQ_RCVD:
	हाल IB_CM_MRA_REQ_SENT:
	हाल IB_CM_REP_RCVD:
	हाल IB_CM_MRA_REP_SENT:
	हाल IB_CM_REP_SENT:
	हाल IB_CM_MRA_REP_RCVD:
	हाल IB_CM_ESTABLISHED:
		*qp_attr_mask = IB_QP_STATE | IB_QP_AV | IB_QP_PATH_MTU |
				IB_QP_DEST_QPN | IB_QP_RQ_PSN;
		qp_attr->ah_attr = cm_id_priv->av.ah_attr;
		qp_attr->path_mtu = cm_id_priv->path_mtu;
		qp_attr->dest_qp_num = be32_to_cpu(cm_id_priv->remote_qpn);
		qp_attr->rq_psn = be32_to_cpu(cm_id_priv->rq_psn);
		अगर (cm_id_priv->qp_type == IB_QPT_RC ||
		    cm_id_priv->qp_type == IB_QPT_XRC_TGT) अणु
			*qp_attr_mask |= IB_QP_MAX_DEST_RD_ATOMIC |
					 IB_QP_MIN_RNR_TIMER;
			qp_attr->max_dest_rd_atomic =
					cm_id_priv->responder_resources;
			qp_attr->min_rnr_समयr = 0;
		पूर्ण
		अगर (rdma_ah_get_dlid(&cm_id_priv->alt_av.ah_attr)) अणु
			*qp_attr_mask |= IB_QP_ALT_PATH;
			qp_attr->alt_port_num = cm_id_priv->alt_av.port->port_num;
			qp_attr->alt_pkey_index = cm_id_priv->alt_av.pkey_index;
			qp_attr->alt_समयout = cm_id_priv->alt_av.समयout;
			qp_attr->alt_ah_attr = cm_id_priv->alt_av.ah_attr;
		पूर्ण
		ret = 0;
		अवरोध;
	शेष:
		trace_icm_qp_rtr_err(&cm_id_priv->id);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक cm_init_qp_rts_attr(काष्ठा cm_id_निजी *cm_id_priv,
			       काष्ठा ib_qp_attr *qp_attr,
			       पूर्णांक *qp_attr_mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	चयन (cm_id_priv->id.state) अणु
	/* Allow transition to RTS beक्रमe sending REP */
	हाल IB_CM_REQ_RCVD:
	हाल IB_CM_MRA_REQ_SENT:

	हाल IB_CM_REP_RCVD:
	हाल IB_CM_MRA_REP_SENT:
	हाल IB_CM_REP_SENT:
	हाल IB_CM_MRA_REP_RCVD:
	हाल IB_CM_ESTABLISHED:
		अगर (cm_id_priv->id.lap_state == IB_CM_LAP_UNINIT) अणु
			*qp_attr_mask = IB_QP_STATE | IB_QP_SQ_PSN;
			qp_attr->sq_psn = be32_to_cpu(cm_id_priv->sq_psn);
			चयन (cm_id_priv->qp_type) अणु
			हाल IB_QPT_RC:
			हाल IB_QPT_XRC_INI:
				*qp_attr_mask |= IB_QP_RETRY_CNT | IB_QP_RNR_RETRY |
						 IB_QP_MAX_QP_RD_ATOMIC;
				qp_attr->retry_cnt = cm_id_priv->retry_count;
				qp_attr->rnr_retry = cm_id_priv->rnr_retry_count;
				qp_attr->max_rd_atomic = cm_id_priv->initiator_depth;
				fallthrough;
			हाल IB_QPT_XRC_TGT:
				*qp_attr_mask |= IB_QP_TIMEOUT;
				qp_attr->समयout = cm_id_priv->av.समयout;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अगर (rdma_ah_get_dlid(&cm_id_priv->alt_av.ah_attr)) अणु
				*qp_attr_mask |= IB_QP_PATH_MIG_STATE;
				qp_attr->path_mig_state = IB_MIG_REARM;
			पूर्ण
		पूर्ण अन्यथा अणु
			*qp_attr_mask = IB_QP_ALT_PATH | IB_QP_PATH_MIG_STATE;
			qp_attr->alt_port_num = cm_id_priv->alt_av.port->port_num;
			qp_attr->alt_pkey_index = cm_id_priv->alt_av.pkey_index;
			qp_attr->alt_समयout = cm_id_priv->alt_av.समयout;
			qp_attr->alt_ah_attr = cm_id_priv->alt_av.ah_attr;
			qp_attr->path_mig_state = IB_MIG_REARM;
		पूर्ण
		ret = 0;
		अवरोध;
	शेष:
		trace_icm_qp_rts_err(&cm_id_priv->id);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक ib_cm_init_qp_attr(काष्ठा ib_cm_id *cm_id,
		       काष्ठा ib_qp_attr *qp_attr,
		       पूर्णांक *qp_attr_mask)
अणु
	काष्ठा cm_id_निजी *cm_id_priv;
	पूर्णांक ret;

	cm_id_priv = container_of(cm_id, काष्ठा cm_id_निजी, id);
	चयन (qp_attr->qp_state) अणु
	हाल IB_QPS_INIT:
		ret = cm_init_qp_init_attr(cm_id_priv, qp_attr, qp_attr_mask);
		अवरोध;
	हाल IB_QPS_RTR:
		ret = cm_init_qp_rtr_attr(cm_id_priv, qp_attr, qp_attr_mask);
		अवरोध;
	हाल IB_QPS_RTS:
		ret = cm_init_qp_rts_attr(cm_id_priv, qp_attr, qp_attr_mask);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_cm_init_qp_attr);

अटल sमाप_प्रकार cm_show_counter(काष्ठा kobject *obj, काष्ठा attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा cm_counter_group *group;
	काष्ठा cm_counter_attribute *cm_attr;

	group = container_of(obj, काष्ठा cm_counter_group, obj);
	cm_attr = container_of(attr, काष्ठा cm_counter_attribute, attr);

	वापस sysfs_emit(buf, "%ld\n",
			  atomic_दीर्घ_पढ़ो(&group->counter[cm_attr->index]));
पूर्ण

अटल स्थिर काष्ठा sysfs_ops cm_counter_ops = अणु
	.show = cm_show_counter
पूर्ण;

अटल काष्ठा kobj_type cm_counter_obj_type = अणु
	.sysfs_ops = &cm_counter_ops,
	.शेष_attrs = cm_counter_शेष_attrs
पूर्ण;

अटल पूर्णांक cm_create_port_fs(काष्ठा cm_port *port)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < CM_COUNTER_GROUPS; i++) अणु
		ret = ib_port_रेजिस्टर_module_stat(port->cm_dev->ib_device,
						   port->port_num,
						   &port->counter_group[i].obj,
						   &cm_counter_obj_type,
						   counter_group_names[i]);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	जबतक (i--)
		ib_port_unरेजिस्टर_module_stat(&port->counter_group[i].obj);
	वापस ret;

पूर्ण

अटल व्योम cm_हटाओ_port_fs(काष्ठा cm_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CM_COUNTER_GROUPS; i++)
		ib_port_unरेजिस्टर_module_stat(&port->counter_group[i].obj);

पूर्ण

अटल पूर्णांक cm_add_one(काष्ठा ib_device *ib_device)
अणु
	काष्ठा cm_device *cm_dev;
	काष्ठा cm_port *port;
	काष्ठा ib_mad_reg_req reg_req = अणु
		.mgmt_class = IB_MGMT_CLASS_CM,
		.mgmt_class_version = IB_CM_CLASS_VERSION,
	पूर्ण;
	काष्ठा ib_port_modअगरy port_modअगरy = अणु
		.set_port_cap_mask = IB_PORT_CM_SUP
	पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	पूर्णांक count = 0;
	u32 i;

	cm_dev = kzalloc(काष्ठा_size(cm_dev, port, ib_device->phys_port_cnt),
			 GFP_KERNEL);
	अगर (!cm_dev)
		वापस -ENOMEM;

	cm_dev->ib_device = ib_device;
	cm_dev->ack_delay = ib_device->attrs.local_ca_ack_delay;
	cm_dev->going_करोwn = 0;

	set_bit(IB_MGMT_METHOD_SEND, reg_req.method_mask);
	rdma_क्रम_each_port (ib_device, i) अणु
		अगर (!rdma_cap_ib_cm(ib_device, i))
			जारी;

		port = kzalloc(माप *port, GFP_KERNEL);
		अगर (!port) अणु
			ret = -ENOMEM;
			जाओ error1;
		पूर्ण

		cm_dev->port[i-1] = port;
		port->cm_dev = cm_dev;
		port->port_num = i;

		INIT_LIST_HEAD(&port->cm_priv_prim_list);
		INIT_LIST_HEAD(&port->cm_priv_altr_list);

		ret = cm_create_port_fs(port);
		अगर (ret)
			जाओ error1;

		port->mad_agent = ib_रेजिस्टर_mad_agent(ib_device, i,
							IB_QPT_GSI,
							&reg_req,
							0,
							cm_send_handler,
							cm_recv_handler,
							port,
							0);
		अगर (IS_ERR(port->mad_agent)) अणु
			ret = PTR_ERR(port->mad_agent);
			जाओ error2;
		पूर्ण

		ret = ib_modअगरy_port(ib_device, i, 0, &port_modअगरy);
		अगर (ret)
			जाओ error3;

		count++;
	पूर्ण

	अगर (!count) अणु
		ret = -EOPNOTSUPP;
		जाओ मुक्त;
	पूर्ण

	ib_set_client_data(ib_device, &cm_client, cm_dev);

	ग_लिखो_lock_irqsave(&cm.device_lock, flags);
	list_add_tail(&cm_dev->list, &cm.device_list);
	ग_लिखो_unlock_irqrestore(&cm.device_lock, flags);
	वापस 0;

error3:
	ib_unरेजिस्टर_mad_agent(port->mad_agent);
error2:
	cm_हटाओ_port_fs(port);
error1:
	port_modअगरy.set_port_cap_mask = 0;
	port_modअगरy.clr_port_cap_mask = IB_PORT_CM_SUP;
	kमुक्त(port);
	जबतक (--i) अणु
		अगर (!rdma_cap_ib_cm(ib_device, i))
			जारी;

		port = cm_dev->port[i-1];
		ib_modअगरy_port(ib_device, port->port_num, 0, &port_modअगरy);
		ib_unरेजिस्टर_mad_agent(port->mad_agent);
		cm_हटाओ_port_fs(port);
		kमुक्त(port);
	पूर्ण
मुक्त:
	kमुक्त(cm_dev);
	वापस ret;
पूर्ण

अटल व्योम cm_हटाओ_one(काष्ठा ib_device *ib_device, व्योम *client_data)
अणु
	काष्ठा cm_device *cm_dev = client_data;
	काष्ठा cm_port *port;
	काष्ठा cm_id_निजी *cm_id_priv;
	काष्ठा ib_mad_agent *cur_mad_agent;
	काष्ठा ib_port_modअगरy port_modअगरy = अणु
		.clr_port_cap_mask = IB_PORT_CM_SUP
	पूर्ण;
	अचिन्हित दीर्घ flags;
	u32 i;

	ग_लिखो_lock_irqsave(&cm.device_lock, flags);
	list_del(&cm_dev->list);
	ग_लिखो_unlock_irqrestore(&cm.device_lock, flags);

	spin_lock_irq(&cm.lock);
	cm_dev->going_करोwn = 1;
	spin_unlock_irq(&cm.lock);

	rdma_क्रम_each_port (ib_device, i) अणु
		अगर (!rdma_cap_ib_cm(ib_device, i))
			जारी;

		port = cm_dev->port[i-1];
		ib_modअगरy_port(ib_device, port->port_num, 0, &port_modअगरy);
		/* Mark all the cm_id's as not valid */
		spin_lock_irq(&cm.lock);
		list_क्रम_each_entry(cm_id_priv, &port->cm_priv_altr_list, altr_list)
			cm_id_priv->altr_send_port_not_पढ़ोy = 1;
		list_क्रम_each_entry(cm_id_priv, &port->cm_priv_prim_list, prim_list)
			cm_id_priv->prim_send_port_not_पढ़ोy = 1;
		spin_unlock_irq(&cm.lock);
		/*
		 * We flush the queue here after the going_करोwn set, this
		 * verअगरy that no new works will be queued in the recv handler,
		 * after that we can call the unरेजिस्टर_mad_agent
		 */
		flush_workqueue(cm.wq);
		spin_lock_irq(&cm.state_lock);
		cur_mad_agent = port->mad_agent;
		port->mad_agent = शून्य;
		spin_unlock_irq(&cm.state_lock);
		ib_unरेजिस्टर_mad_agent(cur_mad_agent);
		cm_हटाओ_port_fs(port);
		kमुक्त(port);
	पूर्ण

	kमुक्त(cm_dev);
पूर्ण

अटल पूर्णांक __init ib_cm_init(व्योम)
अणु
	पूर्णांक ret;

	INIT_LIST_HEAD(&cm.device_list);
	rwlock_init(&cm.device_lock);
	spin_lock_init(&cm.lock);
	spin_lock_init(&cm.state_lock);
	cm.listen_service_table = RB_ROOT;
	cm.listen_service_id = be64_to_cpu(IB_CM_ASSIGN_SERVICE_ID);
	cm.remote_id_table = RB_ROOT;
	cm.remote_qp_table = RB_ROOT;
	cm.remote_sidr_table = RB_ROOT;
	xa_init_flags(&cm.local_id_table, XA_FLAGS_ALLOC);
	get_अक्रमom_bytes(&cm.अक्रमom_id_opeअक्रम, माप cm.अक्रमom_id_opeअक्रम);
	INIT_LIST_HEAD(&cm.समयरुको_list);

	cm.wq = alloc_workqueue("ib_cm", 0, 1);
	अगर (!cm.wq) अणु
		ret = -ENOMEM;
		जाओ error2;
	पूर्ण

	ret = ib_रेजिस्टर_client(&cm_client);
	अगर (ret)
		जाओ error3;

	वापस 0;
error3:
	destroy_workqueue(cm.wq);
error2:
	वापस ret;
पूर्ण

अटल व्योम __निकास ib_cm_cleanup(व्योम)
अणु
	काष्ठा cm_समयरुको_info *समयरुको_info, *पंचांगp;

	spin_lock_irq(&cm.lock);
	list_क्रम_each_entry(समयरुको_info, &cm.समयरुको_list, list)
		cancel_delayed_work(&समयरुको_info->work.work);
	spin_unlock_irq(&cm.lock);

	ib_unरेजिस्टर_client(&cm_client);
	destroy_workqueue(cm.wq);

	list_क्रम_each_entry_safe(समयरुको_info, पंचांगp, &cm.समयरुको_list, list) अणु
		list_del(&समयरुको_info->list);
		kमुक्त(समयरुको_info);
	पूर्ण

	WARN_ON(!xa_empty(&cm.local_id_table));
पूर्ण

module_init(ib_cm_init);
module_निकास(ib_cm_cleanup);
