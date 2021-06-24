<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2005 Voltaire Inc.  All rights reserved.
 * Copyright (c) 2002-2005, Network Appliance, Inc. All rights reserved.
 * Copyright (c) 1999-2019, Mellanox Technologies, Inc. All rights reserved.
 * Copyright (c) 2005-2006 Intel Corporation.  All rights reserved.
 */

#समावेश <linux/completion.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/igmp.h>
#समावेश <linux/xarray.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <net/route.h>

#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/tcp.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip_fib.h>
#समावेश <net/ip6_route.h>

#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/rdma_cm_ib.h>
#समावेश <rdma/rdma_netlink.h>
#समावेश <rdma/ib.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_cm.h>
#समावेश <rdma/ib_sa.h>
#समावेश <rdma/iw_cm.h>

#समावेश "core_priv.h"
#समावेश "cma_priv.h"
#समावेश "cma_trace.h"

MODULE_AUTHOR("Sean Hefty");
MODULE_DESCRIPTION("Generic RDMA CM Agent");
MODULE_LICENSE("Dual BSD/GPL");

#घोषणा CMA_CM_RESPONSE_TIMEOUT 20
#घोषणा CMA_MAX_CM_RETRIES 15
#घोषणा CMA_CM_MRA_SETTING (IB_CM_MRA_FLAG_DELAY | 24)
#घोषणा CMA_IBOE_PACKET_LIFETIME 18
#घोषणा CMA_PREFERRED_ROCE_GID_TYPE IB_GID_TYPE_ROCE_UDP_ENCAP

अटल स्थिर अक्षर * स्थिर cma_events[] = अणु
	[RDMA_CM_EVENT_ADDR_RESOLVED]	 = "address resolved",
	[RDMA_CM_EVENT_ADDR_ERROR]	 = "address error",
	[RDMA_CM_EVENT_ROUTE_RESOLVED]	 = "route resolved ",
	[RDMA_CM_EVENT_ROUTE_ERROR]	 = "route error",
	[RDMA_CM_EVENT_CONNECT_REQUEST]	 = "connect request",
	[RDMA_CM_EVENT_CONNECT_RESPONSE] = "connect response",
	[RDMA_CM_EVENT_CONNECT_ERROR]	 = "connect error",
	[RDMA_CM_EVENT_UNREACHABLE]	 = "unreachable",
	[RDMA_CM_EVENT_REJECTED]	 = "rejected",
	[RDMA_CM_EVENT_ESTABLISHED]	 = "established",
	[RDMA_CM_EVENT_DISCONNECTED]	 = "disconnected",
	[RDMA_CM_EVENT_DEVICE_REMOVAL]	 = "device removal",
	[RDMA_CM_EVENT_MULTICAST_JOIN]	 = "multicast join",
	[RDMA_CM_EVENT_MULTICAST_ERROR]	 = "multicast error",
	[RDMA_CM_EVENT_ADDR_CHANGE]	 = "address change",
	[RDMA_CM_EVENT_TIMEWAIT_EXIT]	 = "timewait exit",
पूर्ण;

अटल व्योम cma_set_mgid(काष्ठा rdma_id_निजी *id_priv, काष्ठा sockaddr *addr,
			 जोड़ ib_gid *mgid);

स्थिर अक्षर *__attribute_स्थिर__ rdma_event_msg(क्रमागत rdma_cm_event_type event)
अणु
	माप_प्रकार index = event;

	वापस (index < ARRAY_SIZE(cma_events) && cma_events[index]) ?
			cma_events[index] : "unrecognized event";
पूर्ण
EXPORT_SYMBOL(rdma_event_msg);

स्थिर अक्षर *__attribute_स्थिर__ rdma_reject_msg(काष्ठा rdma_cm_id *id,
						पूर्णांक reason)
अणु
	अगर (rdma_ib_or_roce(id->device, id->port_num))
		वापस ibcm_reject_msg(reason);

	अगर (rdma_protocol_iwarp(id->device, id->port_num))
		वापस iwcm_reject_msg(reason);

	WARN_ON_ONCE(1);
	वापस "unrecognized transport";
पूर्ण
EXPORT_SYMBOL(rdma_reject_msg);

/**
 * rdma_is_consumer_reject - वापस true अगर the consumer rejected the connect
 *                           request.
 * @id: Communication identअगरier that received the REJECT event.
 * @reason: Value वापसed in the REJECT event status field.
 */
अटल bool rdma_is_consumer_reject(काष्ठा rdma_cm_id *id, पूर्णांक reason)
अणु
	अगर (rdma_ib_or_roce(id->device, id->port_num))
		वापस reason == IB_CM_REJ_CONSUMER_DEFINED;

	अगर (rdma_protocol_iwarp(id->device, id->port_num))
		वापस reason == -ECONNREFUSED;

	WARN_ON_ONCE(1);
	वापस false;
पूर्ण

स्थिर व्योम *rdma_consumer_reject_data(काष्ठा rdma_cm_id *id,
				      काष्ठा rdma_cm_event *ev, u8 *data_len)
अणु
	स्थिर व्योम *p;

	अगर (rdma_is_consumer_reject(id, ev->status)) अणु
		*data_len = ev->param.conn.निजी_data_len;
		p = ev->param.conn.निजी_data;
	पूर्ण अन्यथा अणु
		*data_len = 0;
		p = शून्य;
	पूर्ण
	वापस p;
पूर्ण
EXPORT_SYMBOL(rdma_consumer_reject_data);

/**
 * rdma_iw_cm_id() - वापस the iw_cm_id poपूर्णांकer क्रम this cm_id.
 * @id: Communication Identअगरier
 */
काष्ठा iw_cm_id *rdma_iw_cm_id(काष्ठा rdma_cm_id *id)
अणु
	काष्ठा rdma_id_निजी *id_priv;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	अगर (id->device->node_type == RDMA_NODE_RNIC)
		वापस id_priv->cm_id.iw;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(rdma_iw_cm_id);

/**
 * rdma_res_to_id() - वापस the rdma_cm_id poपूर्णांकer क्रम this restrack.
 * @res: rdma resource tracking entry poपूर्णांकer
 */
काष्ठा rdma_cm_id *rdma_res_to_id(काष्ठा rdma_restrack_entry *res)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(res, काष्ठा rdma_id_निजी, res);

	वापस &id_priv->id;
पूर्ण
EXPORT_SYMBOL(rdma_res_to_id);

अटल पूर्णांक cma_add_one(काष्ठा ib_device *device);
अटल व्योम cma_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data);

अटल काष्ठा ib_client cma_client = अणु
	.name   = "cma",
	.add    = cma_add_one,
	.हटाओ = cma_हटाओ_one
पूर्ण;

अटल काष्ठा ib_sa_client sa_client;
अटल LIST_HEAD(dev_list);
अटल LIST_HEAD(listen_any_list);
अटल DEFINE_MUTEX(lock);
अटल काष्ठा workqueue_काष्ठा *cma_wq;
अटल अचिन्हित पूर्णांक cma_pernet_id;

काष्ठा cma_pernet अणु
	काष्ठा xarray tcp_ps;
	काष्ठा xarray udp_ps;
	काष्ठा xarray ipoib_ps;
	काष्ठा xarray ib_ps;
पूर्ण;

अटल काष्ठा cma_pernet *cma_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, cma_pernet_id);
पूर्ण

अटल
काष्ठा xarray *cma_pernet_xa(काष्ठा net *net, क्रमागत rdma_ucm_port_space ps)
अणु
	काष्ठा cma_pernet *pernet = cma_pernet(net);

	चयन (ps) अणु
	हाल RDMA_PS_TCP:
		वापस &pernet->tcp_ps;
	हाल RDMA_PS_UDP:
		वापस &pernet->udp_ps;
	हाल RDMA_PS_IPOIB:
		वापस &pernet->ipoib_ps;
	हाल RDMA_PS_IB:
		वापस &pernet->ib_ps;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

काष्ठा cma_device अणु
	काष्ठा list_head	list;
	काष्ठा ib_device	*device;
	काष्ठा completion	comp;
	refcount_t refcount;
	काष्ठा list_head	id_list;
	क्रमागत ib_gid_type	*शेष_gid_type;
	u8			*शेष_roce_tos;
पूर्ण;

काष्ठा rdma_bind_list अणु
	क्रमागत rdma_ucm_port_space ps;
	काष्ठा hlist_head	owners;
	अचिन्हित लघु		port;
पूर्ण;

अटल पूर्णांक cma_ps_alloc(काष्ठा net *net, क्रमागत rdma_ucm_port_space ps,
			काष्ठा rdma_bind_list *bind_list, पूर्णांक snum)
अणु
	काष्ठा xarray *xa = cma_pernet_xa(net, ps);

	वापस xa_insert(xa, snum, bind_list, GFP_KERNEL);
पूर्ण

अटल काष्ठा rdma_bind_list *cma_ps_find(काष्ठा net *net,
					  क्रमागत rdma_ucm_port_space ps, पूर्णांक snum)
अणु
	काष्ठा xarray *xa = cma_pernet_xa(net, ps);

	वापस xa_load(xa, snum);
पूर्ण

अटल व्योम cma_ps_हटाओ(काष्ठा net *net, क्रमागत rdma_ucm_port_space ps,
			  पूर्णांक snum)
अणु
	काष्ठा xarray *xa = cma_pernet_xa(net, ps);

	xa_erase(xa, snum);
पूर्ण

क्रमागत अणु
	CMA_OPTION_AFONLY,
पूर्ण;

व्योम cma_dev_get(काष्ठा cma_device *cma_dev)
अणु
	refcount_inc(&cma_dev->refcount);
पूर्ण

व्योम cma_dev_put(काष्ठा cma_device *cma_dev)
अणु
	अगर (refcount_dec_and_test(&cma_dev->refcount))
		complete(&cma_dev->comp);
पूर्ण

काष्ठा cma_device *cma_क्रमागत_devices_by_ibdev(cma_device_filter	filter,
					     व्योम		*cookie)
अणु
	काष्ठा cma_device *cma_dev;
	काष्ठा cma_device *found_cma_dev = शून्य;

	mutex_lock(&lock);

	list_क्रम_each_entry(cma_dev, &dev_list, list)
		अगर (filter(cma_dev->device, cookie)) अणु
			found_cma_dev = cma_dev;
			अवरोध;
		पूर्ण

	अगर (found_cma_dev)
		cma_dev_get(found_cma_dev);
	mutex_unlock(&lock);
	वापस found_cma_dev;
पूर्ण

पूर्णांक cma_get_शेष_gid_type(काष्ठा cma_device *cma_dev,
			     u32 port)
अणु
	अगर (!rdma_is_port_valid(cma_dev->device, port))
		वापस -EINVAL;

	वापस cma_dev->शेष_gid_type[port - rdma_start_port(cma_dev->device)];
पूर्ण

पूर्णांक cma_set_शेष_gid_type(काष्ठा cma_device *cma_dev,
			     u32 port,
			     क्रमागत ib_gid_type शेष_gid_type)
अणु
	अचिन्हित दीर्घ supported_gids;

	अगर (!rdma_is_port_valid(cma_dev->device, port))
		वापस -EINVAL;

	अगर (शेष_gid_type == IB_GID_TYPE_IB &&
	    rdma_protocol_roce_eth_encap(cma_dev->device, port))
		शेष_gid_type = IB_GID_TYPE_ROCE;

	supported_gids = roce_gid_type_mask_support(cma_dev->device, port);

	अगर (!(supported_gids & 1 << शेष_gid_type))
		वापस -EINVAL;

	cma_dev->शेष_gid_type[port - rdma_start_port(cma_dev->device)] =
		शेष_gid_type;

	वापस 0;
पूर्ण

पूर्णांक cma_get_शेष_roce_tos(काष्ठा cma_device *cma_dev, u32 port)
अणु
	अगर (!rdma_is_port_valid(cma_dev->device, port))
		वापस -EINVAL;

	वापस cma_dev->शेष_roce_tos[port - rdma_start_port(cma_dev->device)];
पूर्ण

पूर्णांक cma_set_शेष_roce_tos(काष्ठा cma_device *cma_dev, u32 port,
			     u8 शेष_roce_tos)
अणु
	अगर (!rdma_is_port_valid(cma_dev->device, port))
		वापस -EINVAL;

	cma_dev->शेष_roce_tos[port - rdma_start_port(cma_dev->device)] =
		 शेष_roce_tos;

	वापस 0;
पूर्ण
काष्ठा ib_device *cma_get_ib_dev(काष्ठा cma_device *cma_dev)
अणु
	वापस cma_dev->device;
पूर्ण

/*
 * Device removal can occur at anyसमय, so we need extra handling to
 * serialize notअगरying the user of device removal with other callbacks.
 * We करो this by disabling removal notअगरication जबतक a callback is in process,
 * and reporting it after the callback completes.
 */

काष्ठा cma_multicast अणु
	काष्ठा rdma_id_निजी *id_priv;
	जोड़ अणु
		काष्ठा ib_sa_multicast *sa_mc;
		काष्ठा अणु
			काष्ठा work_काष्ठा work;
			काष्ठा rdma_cm_event event;
		पूर्ण iboe_join;
	पूर्ण;
	काष्ठा list_head	list;
	व्योम			*context;
	काष्ठा sockaddr_storage	addr;
	u8			join_state;
पूर्ण;

काष्ठा cma_work अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा rdma_id_निजी	*id;
	क्रमागत rdma_cm_state	old_state;
	क्रमागत rdma_cm_state	new_state;
	काष्ठा rdma_cm_event	event;
पूर्ण;

जोड़ cma_ip_addr अणु
	काष्ठा in6_addr ip6;
	काष्ठा अणु
		__be32 pad[3];
		__be32 addr;
	पूर्ण ip4;
पूर्ण;

काष्ठा cma_hdr अणु
	u8 cma_version;
	u8 ip_version;	/* IP version: 7:4 */
	__be16 port;
	जोड़ cma_ip_addr src_addr;
	जोड़ cma_ip_addr dst_addr;
पूर्ण;

#घोषणा CMA_VERSION 0x00

काष्ठा cma_req_info अणु
	काष्ठा sockaddr_storage listen_addr_storage;
	काष्ठा sockaddr_storage src_addr_storage;
	काष्ठा ib_device *device;
	जोड़ ib_gid local_gid;
	__be64 service_id;
	पूर्णांक port;
	bool has_gid;
	u16 pkey;
पूर्ण;

अटल पूर्णांक cma_comp_exch(काष्ठा rdma_id_निजी *id_priv,
			 क्रमागत rdma_cm_state comp, क्रमागत rdma_cm_state exch)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * The FSM uses a funny द्विगुन locking where state is रक्षित by both
	 * the handler_mutex and the spinlock. State is not allowed to change
	 * to/from a handler_mutex रक्षित value without also holding
	 * handler_mutex.
	 */
	अगर (comp == RDMA_CM_CONNECT || exch == RDMA_CM_CONNECT)
		lockdep_निश्चित_held(&id_priv->handler_mutex);

	spin_lock_irqsave(&id_priv->lock, flags);
	अगर ((ret = (id_priv->state == comp)))
		id_priv->state = exch;
	spin_unlock_irqrestore(&id_priv->lock, flags);
	वापस ret;
पूर्ण

अटल अंतरभूत u8 cma_get_ip_ver(स्थिर काष्ठा cma_hdr *hdr)
अणु
	वापस hdr->ip_version >> 4;
पूर्ण

अटल अंतरभूत व्योम cma_set_ip_ver(काष्ठा cma_hdr *hdr, u8 ip_ver)
अणु
	hdr->ip_version = (ip_ver << 4) | (hdr->ip_version & 0xF);
पूर्ण

अटल पूर्णांक cma_igmp_send(काष्ठा net_device *ndev, जोड़ ib_gid *mgid, bool join)
अणु
	काष्ठा in_device *in_dev = शून्य;

	अगर (ndev) अणु
		rtnl_lock();
		in_dev = __in_dev_get_rtnl(ndev);
		अगर (in_dev) अणु
			अगर (join)
				ip_mc_inc_group(in_dev,
						*(__be32 *)(mgid->raw + 12));
			अन्यथा
				ip_mc_dec_group(in_dev,
						*(__be32 *)(mgid->raw + 12));
		पूर्ण
		rtnl_unlock();
	पूर्ण
	वापस (in_dev) ? 0 : -ENODEV;
पूर्ण

अटल व्योम _cma_attach_to_dev(काष्ठा rdma_id_निजी *id_priv,
			       काष्ठा cma_device *cma_dev)
अणु
	cma_dev_get(cma_dev);
	id_priv->cma_dev = cma_dev;
	id_priv->id.device = cma_dev->device;
	id_priv->id.route.addr.dev_addr.transport =
		rdma_node_get_transport(cma_dev->device->node_type);
	list_add_tail(&id_priv->list, &cma_dev->id_list);

	trace_cm_id_attach(id_priv, cma_dev->device);
पूर्ण

अटल व्योम cma_attach_to_dev(काष्ठा rdma_id_निजी *id_priv,
			      काष्ठा cma_device *cma_dev)
अणु
	_cma_attach_to_dev(id_priv, cma_dev);
	id_priv->gid_type =
		cma_dev->शेष_gid_type[id_priv->id.port_num -
					  rdma_start_port(cma_dev->device)];
पूर्ण

अटल व्योम cma_release_dev(काष्ठा rdma_id_निजी *id_priv)
अणु
	mutex_lock(&lock);
	list_del(&id_priv->list);
	cma_dev_put(id_priv->cma_dev);
	id_priv->cma_dev = शून्य;
	id_priv->id.device = शून्य;
	अगर (id_priv->id.route.addr.dev_addr.sgid_attr) अणु
		rdma_put_gid_attr(id_priv->id.route.addr.dev_addr.sgid_attr);
		id_priv->id.route.addr.dev_addr.sgid_attr = शून्य;
	पूर्ण
	mutex_unlock(&lock);
पूर्ण

अटल अंतरभूत काष्ठा sockaddr *cma_src_addr(काष्ठा rdma_id_निजी *id_priv)
अणु
	वापस (काष्ठा sockaddr *) &id_priv->id.route.addr.src_addr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr *cma_dst_addr(काष्ठा rdma_id_निजी *id_priv)
अणु
	वापस (काष्ठा sockaddr *) &id_priv->id.route.addr.dst_addr;
पूर्ण

अटल अंतरभूत अचिन्हित लघु cma_family(काष्ठा rdma_id_निजी *id_priv)
अणु
	वापस id_priv->id.route.addr.src_addr.ss_family;
पूर्ण

अटल पूर्णांक cma_set_qkey(काष्ठा rdma_id_निजी *id_priv, u32 qkey)
अणु
	काष्ठा ib_sa_mcmember_rec rec;
	पूर्णांक ret = 0;

	अगर (id_priv->qkey) अणु
		अगर (qkey && id_priv->qkey != qkey)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	अगर (qkey) अणु
		id_priv->qkey = qkey;
		वापस 0;
	पूर्ण

	चयन (id_priv->id.ps) अणु
	हाल RDMA_PS_UDP:
	हाल RDMA_PS_IB:
		id_priv->qkey = RDMA_UDP_QKEY;
		अवरोध;
	हाल RDMA_PS_IPOIB:
		ib_addr_get_mgid(&id_priv->id.route.addr.dev_addr, &rec.mgid);
		ret = ib_sa_get_mcmember_rec(id_priv->id.device,
					     id_priv->id.port_num, &rec.mgid,
					     &rec);
		अगर (!ret)
			id_priv->qkey = be32_to_cpu(rec.qkey);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम cma_translate_ib(काष्ठा sockaddr_ib *sib, काष्ठा rdma_dev_addr *dev_addr)
अणु
	dev_addr->dev_type = ARPHRD_INFINIBAND;
	rdma_addr_set_sgid(dev_addr, (जोड़ ib_gid *) &sib->sib_addr);
	ib_addr_set_pkey(dev_addr, ntohs(sib->sib_pkey));
पूर्ण

अटल पूर्णांक cma_translate_addr(काष्ठा sockaddr *addr, काष्ठा rdma_dev_addr *dev_addr)
अणु
	पूर्णांक ret;

	अगर (addr->sa_family != AF_IB) अणु
		ret = rdma_translate_ip(addr, dev_addr);
	पूर्ण अन्यथा अणु
		cma_translate_ib((काष्ठा sockaddr_ib *) addr, dev_addr);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ib_gid_attr *
cma_validate_port(काष्ठा ib_device *device, u32 port,
		  क्रमागत ib_gid_type gid_type,
		  जोड़ ib_gid *gid,
		  काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	पूर्णांक bound_अगर_index = dev_addr->bound_dev_अगर;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	पूर्णांक dev_type = dev_addr->dev_type;
	काष्ठा net_device *ndev = शून्य;

	अगर (!rdma_dev_access_netns(device, id_priv->id.route.addr.dev_addr.net))
		वापस ERR_PTR(-ENODEV);

	अगर ((dev_type == ARPHRD_INFINIBAND) && !rdma_protocol_ib(device, port))
		वापस ERR_PTR(-ENODEV);

	अगर ((dev_type != ARPHRD_INFINIBAND) && rdma_protocol_ib(device, port))
		वापस ERR_PTR(-ENODEV);

	अगर (dev_type == ARPHRD_ETHER && rdma_protocol_roce(device, port)) अणु
		ndev = dev_get_by_index(dev_addr->net, bound_अगर_index);
		अगर (!ndev)
			वापस ERR_PTR(-ENODEV);
	पूर्ण अन्यथा अणु
		gid_type = IB_GID_TYPE_IB;
	पूर्ण

	sgid_attr = rdma_find_gid_by_port(device, gid, gid_type, port, ndev);
	अगर (ndev)
		dev_put(ndev);
	वापस sgid_attr;
पूर्ण

अटल व्योम cma_bind_sgid_attr(काष्ठा rdma_id_निजी *id_priv,
			       स्थिर काष्ठा ib_gid_attr *sgid_attr)
अणु
	WARN_ON(id_priv->id.route.addr.dev_addr.sgid_attr);
	id_priv->id.route.addr.dev_addr.sgid_attr = sgid_attr;
पूर्ण

/**
 * cma_acquire_dev_by_src_ip - Acquire cma device, port, gid attribute
 * based on source ip address.
 * @id_priv:	cm_id which should be bound to cma device
 *
 * cma_acquire_dev_by_src_ip() binds cm id to cma device, port and GID attribute
 * based on source IP address. It वापसs 0 on success or error code otherwise.
 * It is applicable to active and passive side cm_id.
 */
अटल पूर्णांक cma_acquire_dev_by_src_ip(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	जोड़ ib_gid gid, iboe_gid, *gidp;
	काष्ठा cma_device *cma_dev;
	क्रमागत ib_gid_type gid_type;
	पूर्णांक ret = -ENODEV;
	u32 port;

	अगर (dev_addr->dev_type != ARPHRD_INFINIBAND &&
	    id_priv->id.ps == RDMA_PS_IPOIB)
		वापस -EINVAL;

	rdma_ip2gid((काष्ठा sockaddr *)&id_priv->id.route.addr.src_addr,
		    &iboe_gid);

	स_नकल(&gid, dev_addr->src_dev_addr +
	       rdma_addr_gid_offset(dev_addr), माप(gid));

	mutex_lock(&lock);
	list_क्रम_each_entry(cma_dev, &dev_list, list) अणु
		rdma_क्रम_each_port (cma_dev->device, port) अणु
			gidp = rdma_protocol_roce(cma_dev->device, port) ?
			       &iboe_gid : &gid;
			gid_type = cma_dev->शेष_gid_type[port - 1];
			sgid_attr = cma_validate_port(cma_dev->device, port,
						      gid_type, gidp, id_priv);
			अगर (!IS_ERR(sgid_attr)) अणु
				id_priv->id.port_num = port;
				cma_bind_sgid_attr(id_priv, sgid_attr);
				cma_attach_to_dev(id_priv, cma_dev);
				ret = 0;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&lock);
	वापस ret;
पूर्ण

/**
 * cma_ib_acquire_dev - Acquire cma device, port and SGID attribute
 * @id_priv:		cm id to bind to cma device
 * @listen_id_priv:	listener cm id to match against
 * @req:		Poपूर्णांकer to req काष्ठाure containaining incoming
 *			request inक्रमmation
 * cma_ib_acquire_dev() acquires cma device, port and SGID attribute when
 * rdma device matches क्रम listen_id and incoming request. It also verअगरies
 * that a GID table entry is present क्रम the source address.
 * Returns 0 on success, or वापसs error code otherwise.
 */
अटल पूर्णांक cma_ib_acquire_dev(काष्ठा rdma_id_निजी *id_priv,
			      स्थिर काष्ठा rdma_id_निजी *listen_id_priv,
			      काष्ठा cma_req_info *req)
अणु
	काष्ठा rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	क्रमागत ib_gid_type gid_type;
	जोड़ ib_gid gid;

	अगर (dev_addr->dev_type != ARPHRD_INFINIBAND &&
	    id_priv->id.ps == RDMA_PS_IPOIB)
		वापस -EINVAL;

	अगर (rdma_protocol_roce(req->device, req->port))
		rdma_ip2gid((काष्ठा sockaddr *)&id_priv->id.route.addr.src_addr,
			    &gid);
	अन्यथा
		स_नकल(&gid, dev_addr->src_dev_addr +
		       rdma_addr_gid_offset(dev_addr), माप(gid));

	gid_type = listen_id_priv->cma_dev->शेष_gid_type[req->port - 1];
	sgid_attr = cma_validate_port(req->device, req->port,
				      gid_type, &gid, id_priv);
	अगर (IS_ERR(sgid_attr))
		वापस PTR_ERR(sgid_attr);

	id_priv->id.port_num = req->port;
	cma_bind_sgid_attr(id_priv, sgid_attr);
	/* Need to acquire lock to protect against पढ़ोer
	 * of cma_dev->id_list such as cma_netdev_callback() and
	 * cma_process_हटाओ().
	 */
	mutex_lock(&lock);
	cma_attach_to_dev(id_priv, listen_id_priv->cma_dev);
	mutex_unlock(&lock);
	rdma_restrack_add(&id_priv->res);
	वापस 0;
पूर्ण

अटल पूर्णांक cma_iw_acquire_dev(काष्ठा rdma_id_निजी *id_priv,
			      स्थिर काष्ठा rdma_id_निजी *listen_id_priv)
अणु
	काष्ठा rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	काष्ठा cma_device *cma_dev;
	क्रमागत ib_gid_type gid_type;
	पूर्णांक ret = -ENODEV;
	जोड़ ib_gid gid;
	u32 port;

	अगर (dev_addr->dev_type != ARPHRD_INFINIBAND &&
	    id_priv->id.ps == RDMA_PS_IPOIB)
		वापस -EINVAL;

	स_नकल(&gid, dev_addr->src_dev_addr +
	       rdma_addr_gid_offset(dev_addr), माप(gid));

	mutex_lock(&lock);

	cma_dev = listen_id_priv->cma_dev;
	port = listen_id_priv->id.port_num;
	gid_type = listen_id_priv->gid_type;
	sgid_attr = cma_validate_port(cma_dev->device, port,
				      gid_type, &gid, id_priv);
	अगर (!IS_ERR(sgid_attr)) अणु
		id_priv->id.port_num = port;
		cma_bind_sgid_attr(id_priv, sgid_attr);
		ret = 0;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(cma_dev, &dev_list, list) अणु
		rdma_क्रम_each_port (cma_dev->device, port) अणु
			अगर (listen_id_priv->cma_dev == cma_dev &&
			    listen_id_priv->id.port_num == port)
				जारी;

			gid_type = cma_dev->शेष_gid_type[port - 1];
			sgid_attr = cma_validate_port(cma_dev->device, port,
						      gid_type, &gid, id_priv);
			अगर (!IS_ERR(sgid_attr)) अणु
				id_priv->id.port_num = port;
				cma_bind_sgid_attr(id_priv, sgid_attr);
				ret = 0;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	अगर (!ret) अणु
		cma_attach_to_dev(id_priv, cma_dev);
		rdma_restrack_add(&id_priv->res);
	पूर्ण

	mutex_unlock(&lock);
	वापस ret;
पूर्ण

/*
 * Select the source IB device and address to reach the destination IB address.
 */
अटल पूर्णांक cma_resolve_ib_dev(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा cma_device *cma_dev, *cur_dev;
	काष्ठा sockaddr_ib *addr;
	जोड़ ib_gid gid, sgid, *dgid;
	अचिन्हित पूर्णांक p;
	u16 pkey, index;
	क्रमागत ib_port_state port_state;
	पूर्णांक i;

	cma_dev = शून्य;
	addr = (काष्ठा sockaddr_ib *) cma_dst_addr(id_priv);
	dgid = (जोड़ ib_gid *) &addr->sib_addr;
	pkey = ntohs(addr->sib_pkey);

	mutex_lock(&lock);
	list_क्रम_each_entry(cur_dev, &dev_list, list) अणु
		rdma_क्रम_each_port (cur_dev->device, p) अणु
			अगर (!rdma_cap_af_ib(cur_dev->device, p))
				जारी;

			अगर (ib_find_cached_pkey(cur_dev->device, p, pkey, &index))
				जारी;

			अगर (ib_get_cached_port_state(cur_dev->device, p, &port_state))
				जारी;
			क्रम (i = 0; !rdma_query_gid(cur_dev->device,
						    p, i, &gid);
			     i++) अणु
				अगर (!स_भेद(&gid, dgid, माप(gid))) अणु
					cma_dev = cur_dev;
					sgid = gid;
					id_priv->id.port_num = p;
					जाओ found;
				पूर्ण

				अगर (!cma_dev && (gid.global.subnet_prefix ==
				    dgid->global.subnet_prefix) &&
				    port_state == IB_PORT_ACTIVE) अणु
					cma_dev = cur_dev;
					sgid = gid;
					id_priv->id.port_num = p;
					जाओ found;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&lock);
	वापस -ENODEV;

found:
	cma_attach_to_dev(id_priv, cma_dev);
	rdma_restrack_add(&id_priv->res);
	mutex_unlock(&lock);
	addr = (काष्ठा sockaddr_ib *)cma_src_addr(id_priv);
	स_नकल(&addr->sib_addr, &sgid, माप(sgid));
	cma_translate_ib(addr, &id_priv->id.route.addr.dev_addr);
	वापस 0;
पूर्ण

अटल व्योम cma_id_get(काष्ठा rdma_id_निजी *id_priv)
अणु
	refcount_inc(&id_priv->refcount);
पूर्ण

अटल व्योम cma_id_put(काष्ठा rdma_id_निजी *id_priv)
अणु
	अगर (refcount_dec_and_test(&id_priv->refcount))
		complete(&id_priv->comp);
पूर्ण

अटल काष्ठा rdma_id_निजी *
__rdma_create_id(काष्ठा net *net, rdma_cm_event_handler event_handler,
		 व्योम *context, क्रमागत rdma_ucm_port_space ps,
		 क्रमागत ib_qp_type qp_type, स्थिर काष्ठा rdma_id_निजी *parent)
अणु
	काष्ठा rdma_id_निजी *id_priv;

	id_priv = kzalloc(माप *id_priv, GFP_KERNEL);
	अगर (!id_priv)
		वापस ERR_PTR(-ENOMEM);

	id_priv->state = RDMA_CM_IDLE;
	id_priv->id.context = context;
	id_priv->id.event_handler = event_handler;
	id_priv->id.ps = ps;
	id_priv->id.qp_type = qp_type;
	id_priv->tos_set = false;
	id_priv->समयout_set = false;
	id_priv->min_rnr_समयr_set = false;
	id_priv->gid_type = IB_GID_TYPE_IB;
	spin_lock_init(&id_priv->lock);
	mutex_init(&id_priv->qp_mutex);
	init_completion(&id_priv->comp);
	refcount_set(&id_priv->refcount, 1);
	mutex_init(&id_priv->handler_mutex);
	INIT_LIST_HEAD(&id_priv->listen_list);
	INIT_LIST_HEAD(&id_priv->mc_list);
	get_अक्रमom_bytes(&id_priv->seq_num, माप id_priv->seq_num);
	id_priv->id.route.addr.dev_addr.net = get_net(net);
	id_priv->seq_num &= 0x00ffffff;

	rdma_restrack_new(&id_priv->res, RDMA_RESTRACK_CM_ID);
	अगर (parent)
		rdma_restrack_parent_name(&id_priv->res, &parent->res);

	वापस id_priv;
पूर्ण

काष्ठा rdma_cm_id *
__rdma_create_kernel_id(काष्ठा net *net, rdma_cm_event_handler event_handler,
			व्योम *context, क्रमागत rdma_ucm_port_space ps,
			क्रमागत ib_qp_type qp_type, स्थिर अक्षर *caller)
अणु
	काष्ठा rdma_id_निजी *ret;

	ret = __rdma_create_id(net, event_handler, context, ps, qp_type, शून्य);
	अगर (IS_ERR(ret))
		वापस ERR_CAST(ret);

	rdma_restrack_set_name(&ret->res, caller);
	वापस &ret->id;
पूर्ण
EXPORT_SYMBOL(__rdma_create_kernel_id);

काष्ठा rdma_cm_id *rdma_create_user_id(rdma_cm_event_handler event_handler,
				       व्योम *context,
				       क्रमागत rdma_ucm_port_space ps,
				       क्रमागत ib_qp_type qp_type)
अणु
	काष्ठा rdma_id_निजी *ret;

	ret = __rdma_create_id(current->nsproxy->net_ns, event_handler, context,
			       ps, qp_type, शून्य);
	अगर (IS_ERR(ret))
		वापस ERR_CAST(ret);

	rdma_restrack_set_name(&ret->res, शून्य);
	वापस &ret->id;
पूर्ण
EXPORT_SYMBOL(rdma_create_user_id);

अटल पूर्णांक cma_init_ud_qp(काष्ठा rdma_id_निजी *id_priv, काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक qp_attr_mask, ret;

	qp_attr.qp_state = IB_QPS_INIT;
	ret = rdma_init_qp_attr(&id_priv->id, &qp_attr, &qp_attr_mask);
	अगर (ret)
		वापस ret;

	ret = ib_modअगरy_qp(qp, &qp_attr, qp_attr_mask);
	अगर (ret)
		वापस ret;

	qp_attr.qp_state = IB_QPS_RTR;
	ret = ib_modअगरy_qp(qp, &qp_attr, IB_QP_STATE);
	अगर (ret)
		वापस ret;

	qp_attr.qp_state = IB_QPS_RTS;
	qp_attr.sq_psn = 0;
	ret = ib_modअगरy_qp(qp, &qp_attr, IB_QP_STATE | IB_QP_SQ_PSN);

	वापस ret;
पूर्ण

अटल पूर्णांक cma_init_conn_qp(काष्ठा rdma_id_निजी *id_priv, काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक qp_attr_mask, ret;

	qp_attr.qp_state = IB_QPS_INIT;
	ret = rdma_init_qp_attr(&id_priv->id, &qp_attr, &qp_attr_mask);
	अगर (ret)
		वापस ret;

	वापस ib_modअगरy_qp(qp, &qp_attr, qp_attr_mask);
पूर्ण

पूर्णांक rdma_create_qp(काष्ठा rdma_cm_id *id, काष्ठा ib_pd *pd,
		   काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	काष्ठा ib_qp *qp;
	पूर्णांक ret;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	अगर (id->device != pd->device) अणु
		ret = -EINVAL;
		जाओ out_err;
	पूर्ण

	qp_init_attr->port_num = id->port_num;
	qp = ib_create_qp(pd, qp_init_attr);
	अगर (IS_ERR(qp)) अणु
		ret = PTR_ERR(qp);
		जाओ out_err;
	पूर्ण

	अगर (id->qp_type == IB_QPT_UD)
		ret = cma_init_ud_qp(id_priv, qp);
	अन्यथा
		ret = cma_init_conn_qp(id_priv, qp);
	अगर (ret)
		जाओ out_destroy;

	id->qp = qp;
	id_priv->qp_num = qp->qp_num;
	id_priv->srq = (qp->srq != शून्य);
	trace_cm_qp_create(id_priv, pd, qp_init_attr, 0);
	वापस 0;
out_destroy:
	ib_destroy_qp(qp);
out_err:
	trace_cm_qp_create(id_priv, pd, qp_init_attr, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_create_qp);

व्योम rdma_destroy_qp(काष्ठा rdma_cm_id *id)
अणु
	काष्ठा rdma_id_निजी *id_priv;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	trace_cm_qp_destroy(id_priv);
	mutex_lock(&id_priv->qp_mutex);
	ib_destroy_qp(id_priv->id.qp);
	id_priv->id.qp = शून्य;
	mutex_unlock(&id_priv->qp_mutex);
पूर्ण
EXPORT_SYMBOL(rdma_destroy_qp);

अटल पूर्णांक cma_modअगरy_qp_rtr(काष्ठा rdma_id_निजी *id_priv,
			     काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक qp_attr_mask, ret;

	mutex_lock(&id_priv->qp_mutex);
	अगर (!id_priv->id.qp) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/* Need to update QP attributes from शेष values. */
	qp_attr.qp_state = IB_QPS_INIT;
	ret = rdma_init_qp_attr(&id_priv->id, &qp_attr, &qp_attr_mask);
	अगर (ret)
		जाओ out;

	ret = ib_modअगरy_qp(id_priv->id.qp, &qp_attr, qp_attr_mask);
	अगर (ret)
		जाओ out;

	qp_attr.qp_state = IB_QPS_RTR;
	ret = rdma_init_qp_attr(&id_priv->id, &qp_attr, &qp_attr_mask);
	अगर (ret)
		जाओ out;

	BUG_ON(id_priv->cma_dev->device != id_priv->id.device);

	अगर (conn_param)
		qp_attr.max_dest_rd_atomic = conn_param->responder_resources;
	ret = ib_modअगरy_qp(id_priv->id.qp, &qp_attr, qp_attr_mask);
out:
	mutex_unlock(&id_priv->qp_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_modअगरy_qp_rts(काष्ठा rdma_id_निजी *id_priv,
			     काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक qp_attr_mask, ret;

	mutex_lock(&id_priv->qp_mutex);
	अगर (!id_priv->id.qp) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	qp_attr.qp_state = IB_QPS_RTS;
	ret = rdma_init_qp_attr(&id_priv->id, &qp_attr, &qp_attr_mask);
	अगर (ret)
		जाओ out;

	अगर (conn_param)
		qp_attr.max_rd_atomic = conn_param->initiator_depth;
	ret = ib_modअगरy_qp(id_priv->id.qp, &qp_attr, qp_attr_mask);
out:
	mutex_unlock(&id_priv->qp_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_modअगरy_qp_err(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक ret;

	mutex_lock(&id_priv->qp_mutex);
	अगर (!id_priv->id.qp) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	qp_attr.qp_state = IB_QPS_ERR;
	ret = ib_modअगरy_qp(id_priv->id.qp, &qp_attr, IB_QP_STATE);
out:
	mutex_unlock(&id_priv->qp_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_ib_init_qp_attr(काष्ठा rdma_id_निजी *id_priv,
			       काष्ठा ib_qp_attr *qp_attr, पूर्णांक *qp_attr_mask)
अणु
	काष्ठा rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	पूर्णांक ret;
	u16 pkey;

	अगर (rdma_cap_eth_ah(id_priv->id.device, id_priv->id.port_num))
		pkey = 0xffff;
	अन्यथा
		pkey = ib_addr_get_pkey(dev_addr);

	ret = ib_find_cached_pkey(id_priv->id.device, id_priv->id.port_num,
				  pkey, &qp_attr->pkey_index);
	अगर (ret)
		वापस ret;

	qp_attr->port_num = id_priv->id.port_num;
	*qp_attr_mask = IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_PORT;

	अगर (id_priv->id.qp_type == IB_QPT_UD) अणु
		ret = cma_set_qkey(id_priv, 0);
		अगर (ret)
			वापस ret;

		qp_attr->qkey = id_priv->qkey;
		*qp_attr_mask |= IB_QP_QKEY;
	पूर्ण अन्यथा अणु
		qp_attr->qp_access_flags = 0;
		*qp_attr_mask |= IB_QP_ACCESS_FLAGS;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक rdma_init_qp_attr(काष्ठा rdma_cm_id *id, काष्ठा ib_qp_attr *qp_attr,
		       पूर्णांक *qp_attr_mask)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	पूर्णांक ret = 0;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	अगर (rdma_cap_ib_cm(id->device, id->port_num)) अणु
		अगर (!id_priv->cm_id.ib || (id_priv->id.qp_type == IB_QPT_UD))
			ret = cma_ib_init_qp_attr(id_priv, qp_attr, qp_attr_mask);
		अन्यथा
			ret = ib_cm_init_qp_attr(id_priv->cm_id.ib, qp_attr,
						 qp_attr_mask);

		अगर (qp_attr->qp_state == IB_QPS_RTR)
			qp_attr->rq_psn = id_priv->seq_num;
	पूर्ण अन्यथा अगर (rdma_cap_iw_cm(id->device, id->port_num)) अणु
		अगर (!id_priv->cm_id.iw) अणु
			qp_attr->qp_access_flags = 0;
			*qp_attr_mask = IB_QP_STATE | IB_QP_ACCESS_FLAGS;
		पूर्ण अन्यथा
			ret = iw_cm_init_qp_attr(id_priv->cm_id.iw, qp_attr,
						 qp_attr_mask);
		qp_attr->port_num = id_priv->id.port_num;
		*qp_attr_mask |= IB_QP_PORT;
	पूर्ण अन्यथा अणु
		ret = -ENOSYS;
	पूर्ण

	अगर ((*qp_attr_mask & IB_QP_TIMEOUT) && id_priv->समयout_set)
		qp_attr->समयout = id_priv->समयout;

	अगर ((*qp_attr_mask & IB_QP_MIN_RNR_TIMER) && id_priv->min_rnr_समयr_set)
		qp_attr->min_rnr_समयr = id_priv->min_rnr_समयr;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_init_qp_attr);

अटल अंतरभूत bool cma_zero_addr(स्थिर काष्ठा sockaddr *addr)
अणु
	चयन (addr->sa_family) अणु
	हाल AF_INET:
		वापस ipv4_is_zeronet(((काष्ठा sockaddr_in *)addr)->sin_addr.s_addr);
	हाल AF_INET6:
		वापस ipv6_addr_any(&((काष्ठा sockaddr_in6 *)addr)->sin6_addr);
	हाल AF_IB:
		वापस ib_addr_any(&((काष्ठा sockaddr_ib *)addr)->sib_addr);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool cma_loopback_addr(स्थिर काष्ठा sockaddr *addr)
अणु
	चयन (addr->sa_family) अणु
	हाल AF_INET:
		वापस ipv4_is_loopback(
			((काष्ठा sockaddr_in *)addr)->sin_addr.s_addr);
	हाल AF_INET6:
		वापस ipv6_addr_loopback(
			&((काष्ठा sockaddr_in6 *)addr)->sin6_addr);
	हाल AF_IB:
		वापस ib_addr_loopback(
			&((काष्ठा sockaddr_ib *)addr)->sib_addr);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool cma_any_addr(स्थिर काष्ठा sockaddr *addr)
अणु
	वापस cma_zero_addr(addr) || cma_loopback_addr(addr);
पूर्ण

अटल पूर्णांक cma_addr_cmp(स्थिर काष्ठा sockaddr *src, स्थिर काष्ठा sockaddr *dst)
अणु
	अगर (src->sa_family != dst->sa_family)
		वापस -1;

	चयन (src->sa_family) अणु
	हाल AF_INET:
		वापस ((काष्ठा sockaddr_in *)src)->sin_addr.s_addr !=
		       ((काष्ठा sockaddr_in *)dst)->sin_addr.s_addr;
	हाल AF_INET6: अणु
		काष्ठा sockaddr_in6 *src_addr6 = (काष्ठा sockaddr_in6 *)src;
		काष्ठा sockaddr_in6 *dst_addr6 = (काष्ठा sockaddr_in6 *)dst;
		bool link_local;

		अगर (ipv6_addr_cmp(&src_addr6->sin6_addr,
					  &dst_addr6->sin6_addr))
			वापस 1;
		link_local = ipv6_addr_type(&dst_addr6->sin6_addr) &
			     IPV6_ADDR_LINKLOCAL;
		/* Link local must match their scope_ids */
		वापस link_local ? (src_addr6->sin6_scope_id !=
				     dst_addr6->sin6_scope_id) :
				    0;
	पूर्ण

	शेष:
		वापस ib_addr_cmp(&((काष्ठा sockaddr_ib *) src)->sib_addr,
				   &((काष्ठा sockaddr_ib *) dst)->sib_addr);
	पूर्ण
पूर्ण

अटल __be16 cma_port(स्थिर काष्ठा sockaddr *addr)
अणु
	काष्ठा sockaddr_ib *sib;

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		वापस ((काष्ठा sockaddr_in *) addr)->sin_port;
	हाल AF_INET6:
		वापस ((काष्ठा sockaddr_in6 *) addr)->sin6_port;
	हाल AF_IB:
		sib = (काष्ठा sockaddr_ib *) addr;
		वापस htons((u16) (be64_to_cpu(sib->sib_sid) &
				    be64_to_cpu(sib->sib_sid_mask)));
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक cma_any_port(स्थिर काष्ठा sockaddr *addr)
अणु
	वापस !cma_port(addr);
पूर्ण

अटल व्योम cma_save_ib_info(काष्ठा sockaddr *src_addr,
			     काष्ठा sockaddr *dst_addr,
			     स्थिर काष्ठा rdma_cm_id *listen_id,
			     स्थिर काष्ठा sa_path_rec *path)
अणु
	काष्ठा sockaddr_ib *listen_ib, *ib;

	listen_ib = (काष्ठा sockaddr_ib *) &listen_id->route.addr.src_addr;
	अगर (src_addr) अणु
		ib = (काष्ठा sockaddr_ib *)src_addr;
		ib->sib_family = AF_IB;
		अगर (path) अणु
			ib->sib_pkey = path->pkey;
			ib->sib_flowinfo = path->flow_label;
			स_नकल(&ib->sib_addr, &path->sgid, 16);
			ib->sib_sid = path->service_id;
			ib->sib_scope_id = 0;
		पूर्ण अन्यथा अणु
			ib->sib_pkey = listen_ib->sib_pkey;
			ib->sib_flowinfo = listen_ib->sib_flowinfo;
			ib->sib_addr = listen_ib->sib_addr;
			ib->sib_sid = listen_ib->sib_sid;
			ib->sib_scope_id = listen_ib->sib_scope_id;
		पूर्ण
		ib->sib_sid_mask = cpu_to_be64(0xffffffffffffffffULL);
	पूर्ण
	अगर (dst_addr) अणु
		ib = (काष्ठा sockaddr_ib *)dst_addr;
		ib->sib_family = AF_IB;
		अगर (path) अणु
			ib->sib_pkey = path->pkey;
			ib->sib_flowinfo = path->flow_label;
			स_नकल(&ib->sib_addr, &path->dgid, 16);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cma_save_ip4_info(काष्ठा sockaddr_in *src_addr,
			      काष्ठा sockaddr_in *dst_addr,
			      काष्ठा cma_hdr *hdr,
			      __be16 local_port)
अणु
	अगर (src_addr) अणु
		*src_addr = (काष्ठा sockaddr_in) अणु
			.sin_family = AF_INET,
			.sin_addr.s_addr = hdr->dst_addr.ip4.addr,
			.sin_port = local_port,
		पूर्ण;
	पूर्ण

	अगर (dst_addr) अणु
		*dst_addr = (काष्ठा sockaddr_in) अणु
			.sin_family = AF_INET,
			.sin_addr.s_addr = hdr->src_addr.ip4.addr,
			.sin_port = hdr->port,
		पूर्ण;
	पूर्ण
पूर्ण

अटल व्योम cma_save_ip6_info(काष्ठा sockaddr_in6 *src_addr,
			      काष्ठा sockaddr_in6 *dst_addr,
			      काष्ठा cma_hdr *hdr,
			      __be16 local_port)
अणु
	अगर (src_addr) अणु
		*src_addr = (काष्ठा sockaddr_in6) अणु
			.sin6_family = AF_INET6,
			.sin6_addr = hdr->dst_addr.ip6,
			.sin6_port = local_port,
		पूर्ण;
	पूर्ण

	अगर (dst_addr) अणु
		*dst_addr = (काष्ठा sockaddr_in6) अणु
			.sin6_family = AF_INET6,
			.sin6_addr = hdr->src_addr.ip6,
			.sin6_port = hdr->port,
		पूर्ण;
	पूर्ण
पूर्ण

अटल u16 cma_port_from_service_id(__be64 service_id)
अणु
	वापस (u16)be64_to_cpu(service_id);
पूर्ण

अटल पूर्णांक cma_save_ip_info(काष्ठा sockaddr *src_addr,
			    काष्ठा sockaddr *dst_addr,
			    स्थिर काष्ठा ib_cm_event *ib_event,
			    __be64 service_id)
अणु
	काष्ठा cma_hdr *hdr;
	__be16 port;

	hdr = ib_event->निजी_data;
	अगर (hdr->cma_version != CMA_VERSION)
		वापस -EINVAL;

	port = htons(cma_port_from_service_id(service_id));

	चयन (cma_get_ip_ver(hdr)) अणु
	हाल 4:
		cma_save_ip4_info((काष्ठा sockaddr_in *)src_addr,
				  (काष्ठा sockaddr_in *)dst_addr, hdr, port);
		अवरोध;
	हाल 6:
		cma_save_ip6_info((काष्ठा sockaddr_in6 *)src_addr,
				  (काष्ठा sockaddr_in6 *)dst_addr, hdr, port);
		अवरोध;
	शेष:
		वापस -EAFNOSUPPORT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cma_save_net_info(काष्ठा sockaddr *src_addr,
			     काष्ठा sockaddr *dst_addr,
			     स्थिर काष्ठा rdma_cm_id *listen_id,
			     स्थिर काष्ठा ib_cm_event *ib_event,
			     sa_family_t sa_family, __be64 service_id)
अणु
	अगर (sa_family == AF_IB) अणु
		अगर (ib_event->event == IB_CM_REQ_RECEIVED)
			cma_save_ib_info(src_addr, dst_addr, listen_id,
					 ib_event->param.req_rcvd.primary_path);
		अन्यथा अगर (ib_event->event == IB_CM_SIDR_REQ_RECEIVED)
			cma_save_ib_info(src_addr, dst_addr, listen_id, शून्य);
		वापस 0;
	पूर्ण

	वापस cma_save_ip_info(src_addr, dst_addr, ib_event, service_id);
पूर्ण

अटल पूर्णांक cma_save_req_info(स्थिर काष्ठा ib_cm_event *ib_event,
			     काष्ठा cma_req_info *req)
अणु
	स्थिर काष्ठा ib_cm_req_event_param *req_param =
		&ib_event->param.req_rcvd;
	स्थिर काष्ठा ib_cm_sidr_req_event_param *sidr_param =
		&ib_event->param.sidr_req_rcvd;

	चयन (ib_event->event) अणु
	हाल IB_CM_REQ_RECEIVED:
		req->device	= req_param->listen_id->device;
		req->port	= req_param->port;
		स_नकल(&req->local_gid, &req_param->primary_path->sgid,
		       माप(req->local_gid));
		req->has_gid	= true;
		req->service_id = req_param->primary_path->service_id;
		req->pkey	= be16_to_cpu(req_param->primary_path->pkey);
		अगर (req->pkey != req_param->bth_pkey)
			pr_warn_ratelimited("RDMA CMA: got different BTH P_Key (0x%x) and primary path P_Key (0x%x)\n"
					    "RDMA CMA: in the future this may cause the request to be dropped\n",
					    req_param->bth_pkey, req->pkey);
		अवरोध;
	हाल IB_CM_SIDR_REQ_RECEIVED:
		req->device	= sidr_param->listen_id->device;
		req->port	= sidr_param->port;
		req->has_gid	= false;
		req->service_id	= sidr_param->service_id;
		req->pkey	= sidr_param->pkey;
		अगर (req->pkey != sidr_param->bth_pkey)
			pr_warn_ratelimited("RDMA CMA: got different BTH P_Key (0x%x) and SIDR request payload P_Key (0x%x)\n"
					    "RDMA CMA: in the future this may cause the request to be dropped\n",
					    sidr_param->bth_pkey, req->pkey);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool validate_ipv4_net_dev(काष्ठा net_device *net_dev,
				  स्थिर काष्ठा sockaddr_in *dst_addr,
				  स्थिर काष्ठा sockaddr_in *src_addr)
अणु
	__be32 daddr = dst_addr->sin_addr.s_addr,
	       saddr = src_addr->sin_addr.s_addr;
	काष्ठा fib_result res;
	काष्ठा flowi4 fl4;
	पूर्णांक err;
	bool ret;

	अगर (ipv4_is_multicast(saddr) || ipv4_is_lbcast(saddr) ||
	    ipv4_is_lbcast(daddr) || ipv4_is_zeronet(saddr) ||
	    ipv4_is_zeronet(daddr) || ipv4_is_loopback(daddr) ||
	    ipv4_is_loopback(saddr))
		वापस false;

	स_रखो(&fl4, 0, माप(fl4));
	fl4.flowi4_iअगर = net_dev->अगरindex;
	fl4.daddr = daddr;
	fl4.saddr = saddr;

	rcu_पढ़ो_lock();
	err = fib_lookup(dev_net(net_dev), &fl4, &res, 0);
	ret = err == 0 && FIB_RES_DEV(res) == net_dev;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल bool validate_ipv6_net_dev(काष्ठा net_device *net_dev,
				  स्थिर काष्ठा sockaddr_in6 *dst_addr,
				  स्थिर काष्ठा sockaddr_in6 *src_addr)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	स्थिर पूर्णांक strict = ipv6_addr_type(&dst_addr->sin6_addr) &
			   IPV6_ADDR_LINKLOCAL;
	काष्ठा rt6_info *rt = rt6_lookup(dev_net(net_dev), &dst_addr->sin6_addr,
					 &src_addr->sin6_addr, net_dev->अगरindex,
					 शून्य, strict);
	bool ret;

	अगर (!rt)
		वापस false;

	ret = rt->rt6i_idev->dev == net_dev;
	ip6_rt_put(rt);

	वापस ret;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल bool validate_net_dev(काष्ठा net_device *net_dev,
			     स्थिर काष्ठा sockaddr *daddr,
			     स्थिर काष्ठा sockaddr *saddr)
अणु
	स्थिर काष्ठा sockaddr_in *daddr4 = (स्थिर काष्ठा sockaddr_in *)daddr;
	स्थिर काष्ठा sockaddr_in *saddr4 = (स्थिर काष्ठा sockaddr_in *)saddr;
	स्थिर काष्ठा sockaddr_in6 *daddr6 = (स्थिर काष्ठा sockaddr_in6 *)daddr;
	स्थिर काष्ठा sockaddr_in6 *saddr6 = (स्थिर काष्ठा sockaddr_in6 *)saddr;

	चयन (daddr->sa_family) अणु
	हाल AF_INET:
		वापस saddr->sa_family == AF_INET &&
		       validate_ipv4_net_dev(net_dev, daddr4, saddr4);

	हाल AF_INET6:
		वापस saddr->sa_family == AF_INET6 &&
		       validate_ipv6_net_dev(net_dev, daddr6, saddr6);

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा net_device *
roce_get_net_dev_by_cm_event(स्थिर काष्ठा ib_cm_event *ib_event)
अणु
	स्थिर काष्ठा ib_gid_attr *sgid_attr = शून्य;
	काष्ठा net_device *ndev;

	अगर (ib_event->event == IB_CM_REQ_RECEIVED)
		sgid_attr = ib_event->param.req_rcvd.ppath_sgid_attr;
	अन्यथा अगर (ib_event->event == IB_CM_SIDR_REQ_RECEIVED)
		sgid_attr = ib_event->param.sidr_req_rcvd.sgid_attr;

	अगर (!sgid_attr)
		वापस शून्य;

	rcu_पढ़ो_lock();
	ndev = rdma_पढ़ो_gid_attr_ndev_rcu(sgid_attr);
	अगर (IS_ERR(ndev))
		ndev = शून्य;
	अन्यथा
		dev_hold(ndev);
	rcu_पढ़ो_unlock();
	वापस ndev;
पूर्ण

अटल काष्ठा net_device *cma_get_net_dev(स्थिर काष्ठा ib_cm_event *ib_event,
					  काष्ठा cma_req_info *req)
अणु
	काष्ठा sockaddr *listen_addr =
			(काष्ठा sockaddr *)&req->listen_addr_storage;
	काष्ठा sockaddr *src_addr = (काष्ठा sockaddr *)&req->src_addr_storage;
	काष्ठा net_device *net_dev;
	स्थिर जोड़ ib_gid *gid = req->has_gid ? &req->local_gid : शून्य;
	पूर्णांक err;

	err = cma_save_ip_info(listen_addr, src_addr, ib_event,
			       req->service_id);
	अगर (err)
		वापस ERR_PTR(err);

	अगर (rdma_protocol_roce(req->device, req->port))
		net_dev = roce_get_net_dev_by_cm_event(ib_event);
	अन्यथा
		net_dev = ib_get_net_dev_by_params(req->device, req->port,
						   req->pkey,
						   gid, listen_addr);
	अगर (!net_dev)
		वापस ERR_PTR(-ENODEV);

	वापस net_dev;
पूर्ण

अटल क्रमागत rdma_ucm_port_space rdma_ps_from_service_id(__be64 service_id)
अणु
	वापस (be64_to_cpu(service_id) >> 16) & 0xffff;
पूर्ण

अटल bool cma_match_निजी_data(काष्ठा rdma_id_निजी *id_priv,
				   स्थिर काष्ठा cma_hdr *hdr)
अणु
	काष्ठा sockaddr *addr = cma_src_addr(id_priv);
	__be32 ip4_addr;
	काष्ठा in6_addr ip6_addr;

	अगर (cma_any_addr(addr) && !id_priv->afonly)
		वापस true;

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		ip4_addr = ((काष्ठा sockaddr_in *)addr)->sin_addr.s_addr;
		अगर (cma_get_ip_ver(hdr) != 4)
			वापस false;
		अगर (!cma_any_addr(addr) &&
		    hdr->dst_addr.ip4.addr != ip4_addr)
			वापस false;
		अवरोध;
	हाल AF_INET6:
		ip6_addr = ((काष्ठा sockaddr_in6 *)addr)->sin6_addr;
		अगर (cma_get_ip_ver(hdr) != 6)
			वापस false;
		अगर (!cma_any_addr(addr) &&
		    स_भेद(&hdr->dst_addr.ip6, &ip6_addr, माप(ip6_addr)))
			वापस false;
		अवरोध;
	हाल AF_IB:
		वापस true;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool cma_protocol_roce(स्थिर काष्ठा rdma_cm_id *id)
अणु
	काष्ठा ib_device *device = id->device;
	स्थिर u32 port_num = id->port_num ?: rdma_start_port(device);

	वापस rdma_protocol_roce(device, port_num);
पूर्ण

अटल bool cma_is_req_ipv6_ll(स्थिर काष्ठा cma_req_info *req)
अणु
	स्थिर काष्ठा sockaddr *daddr =
			(स्थिर काष्ठा sockaddr *)&req->listen_addr_storage;
	स्थिर काष्ठा sockaddr_in6 *daddr6 = (स्थिर काष्ठा sockaddr_in6 *)daddr;

	/* Returns true अगर the req is क्रम IPv6 link local */
	वापस (daddr->sa_family == AF_INET6 &&
		(ipv6_addr_type(&daddr6->sin6_addr) & IPV6_ADDR_LINKLOCAL));
पूर्ण

अटल bool cma_match_net_dev(स्थिर काष्ठा rdma_cm_id *id,
			      स्थिर काष्ठा net_device *net_dev,
			      स्थिर काष्ठा cma_req_info *req)
अणु
	स्थिर काष्ठा rdma_addr *addr = &id->route.addr;

	अगर (!net_dev)
		/* This request is an AF_IB request */
		वापस (!id->port_num || id->port_num == req->port) &&
		       (addr->src_addr.ss_family == AF_IB);

	/*
	 * If the request is not क्रम IPv6 link local, allow matching
	 * request to any netdevice of the one or multiport rdma device.
	 */
	अगर (!cma_is_req_ipv6_ll(req))
		वापस true;
	/*
	 * Net namespaces must match, and अगर the listner is listening
	 * on a specअगरic netdevice than netdevice must match as well.
	 */
	अगर (net_eq(dev_net(net_dev), addr->dev_addr.net) &&
	    (!!addr->dev_addr.bound_dev_अगर ==
	     (addr->dev_addr.bound_dev_अगर == net_dev->अगरindex)))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल काष्ठा rdma_id_निजी *cma_find_listener(
		स्थिर काष्ठा rdma_bind_list *bind_list,
		स्थिर काष्ठा ib_cm_id *cm_id,
		स्थिर काष्ठा ib_cm_event *ib_event,
		स्थिर काष्ठा cma_req_info *req,
		स्थिर काष्ठा net_device *net_dev)
अणु
	काष्ठा rdma_id_निजी *id_priv, *id_priv_dev;

	lockdep_निश्चित_held(&lock);

	अगर (!bind_list)
		वापस ERR_PTR(-EINVAL);

	hlist_क्रम_each_entry(id_priv, &bind_list->owners, node) अणु
		अगर (cma_match_निजी_data(id_priv, ib_event->निजी_data)) अणु
			अगर (id_priv->id.device == cm_id->device &&
			    cma_match_net_dev(&id_priv->id, net_dev, req))
				वापस id_priv;
			list_क्रम_each_entry(id_priv_dev,
					    &id_priv->listen_list,
					    listen_list) अणु
				अगर (id_priv_dev->id.device == cm_id->device &&
				    cma_match_net_dev(&id_priv_dev->id,
						      net_dev, req))
					वापस id_priv_dev;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा rdma_id_निजी *
cma_ib_id_from_event(काष्ठा ib_cm_id *cm_id,
		     स्थिर काष्ठा ib_cm_event *ib_event,
		     काष्ठा cma_req_info *req,
		     काष्ठा net_device **net_dev)
अणु
	काष्ठा rdma_bind_list *bind_list;
	काष्ठा rdma_id_निजी *id_priv;
	पूर्णांक err;

	err = cma_save_req_info(ib_event, req);
	अगर (err)
		वापस ERR_PTR(err);

	*net_dev = cma_get_net_dev(ib_event, req);
	अगर (IS_ERR(*net_dev)) अणु
		अगर (PTR_ERR(*net_dev) == -EAFNOSUPPORT) अणु
			/* Assuming the protocol is AF_IB */
			*net_dev = शून्य;
		पूर्ण अन्यथा अणु
			वापस ERR_CAST(*net_dev);
		पूर्ण
	पूर्ण

	mutex_lock(&lock);
	/*
	 * Net namespace might be getting deleted जबतक route lookup,
	 * cm_id lookup is in progress. Thereक्रमe, perक्रमm netdevice
	 * validation, cm_id lookup under rcu lock.
	 * RCU lock aदीर्घ with netdevice state check, synchronizes with
	 * netdevice migrating to dअगरferent net namespace and also aव्योमs
	 * हाल where net namespace करोesn't get deleted जबतक lookup is in
	 * progress.
	 * If the device state is not IFF_UP, its properties such as अगरindex
	 * and nd_net cannot be trusted to reमुख्य valid without rcu lock.
	 * net/core/dev.c change_net_namespace() ensures to synchronize with
	 * ongoing operations on net device after device is बंदd using
	 * synchronize_net().
	 */
	rcu_पढ़ो_lock();
	अगर (*net_dev) अणु
		/*
		 * If netdevice is करोwn, it is likely that it is administratively
		 * करोwn or it might be migrating to dअगरferent namespace.
		 * In that हाल aव्योम further processing, as the net namespace
		 * or अगरindex may change.
		 */
		अगर (((*net_dev)->flags & IFF_UP) == 0) अणु
			id_priv = ERR_PTR(-EHOSTUNREACH);
			जाओ err;
		पूर्ण

		अगर (!validate_net_dev(*net_dev,
				 (काष्ठा sockaddr *)&req->listen_addr_storage,
				 (काष्ठा sockaddr *)&req->src_addr_storage)) अणु
			id_priv = ERR_PTR(-EHOSTUNREACH);
			जाओ err;
		पूर्ण
	पूर्ण

	bind_list = cma_ps_find(*net_dev ? dev_net(*net_dev) : &init_net,
				rdma_ps_from_service_id(req->service_id),
				cma_port_from_service_id(req->service_id));
	id_priv = cma_find_listener(bind_list, cm_id, ib_event, req, *net_dev);
err:
	rcu_पढ़ो_unlock();
	mutex_unlock(&lock);
	अगर (IS_ERR(id_priv) && *net_dev) अणु
		dev_put(*net_dev);
		*net_dev = शून्य;
	पूर्ण
	वापस id_priv;
पूर्ण

अटल अंतरभूत u8 cma_user_data_offset(काष्ठा rdma_id_निजी *id_priv)
अणु
	वापस cma_family(id_priv) == AF_IB ? 0 : माप(काष्ठा cma_hdr);
पूर्ण

अटल व्योम cma_cancel_route(काष्ठा rdma_id_निजी *id_priv)
अणु
	अगर (rdma_cap_ib_sa(id_priv->id.device, id_priv->id.port_num)) अणु
		अगर (id_priv->query)
			ib_sa_cancel_query(id_priv->query_id, id_priv->query);
	पूर्ण
पूर्ण

अटल व्योम cma_cancel_listens(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_id_निजी *dev_id_priv;

	/*
	 * Remove from listen_any_list to prevent added devices from spawning
	 * additional listen requests.
	 */
	mutex_lock(&lock);
	list_del(&id_priv->list);

	जबतक (!list_empty(&id_priv->listen_list)) अणु
		dev_id_priv = list_entry(id_priv->listen_list.next,
					 काष्ठा rdma_id_निजी, listen_list);
		/* sync with device removal to aव्योम duplicate deकाष्ठाion */
		list_del_init(&dev_id_priv->list);
		list_del(&dev_id_priv->listen_list);
		mutex_unlock(&lock);

		rdma_destroy_id(&dev_id_priv->id);
		mutex_lock(&lock);
	पूर्ण
	mutex_unlock(&lock);
पूर्ण

अटल व्योम cma_cancel_operation(काष्ठा rdma_id_निजी *id_priv,
				 क्रमागत rdma_cm_state state)
अणु
	चयन (state) अणु
	हाल RDMA_CM_ADDR_QUERY:
		rdma_addr_cancel(&id_priv->id.route.addr.dev_addr);
		अवरोध;
	हाल RDMA_CM_ROUTE_QUERY:
		cma_cancel_route(id_priv);
		अवरोध;
	हाल RDMA_CM_LISTEN:
		अगर (cma_any_addr(cma_src_addr(id_priv)) && !id_priv->cma_dev)
			cma_cancel_listens(id_priv);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cma_release_port(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_bind_list *bind_list = id_priv->bind_list;
	काष्ठा net *net = id_priv->id.route.addr.dev_addr.net;

	अगर (!bind_list)
		वापस;

	mutex_lock(&lock);
	hlist_del(&id_priv->node);
	अगर (hlist_empty(&bind_list->owners)) अणु
		cma_ps_हटाओ(net, bind_list->ps, bind_list->port);
		kमुक्त(bind_list);
	पूर्ण
	mutex_unlock(&lock);
पूर्ण

अटल व्योम destroy_mc(काष्ठा rdma_id_निजी *id_priv,
		       काष्ठा cma_multicast *mc)
अणु
	अगर (rdma_cap_ib_mcast(id_priv->id.device, id_priv->id.port_num))
		ib_sa_मुक्त_multicast(mc->sa_mc);

	अगर (rdma_protocol_roce(id_priv->id.device, id_priv->id.port_num)) अणु
		काष्ठा rdma_dev_addr *dev_addr =
			&id_priv->id.route.addr.dev_addr;
		काष्ठा net_device *ndev = शून्य;

		अगर (dev_addr->bound_dev_अगर)
			ndev = dev_get_by_index(dev_addr->net,
						dev_addr->bound_dev_अगर);
		अगर (ndev) अणु
			जोड़ ib_gid mgid;

			cma_set_mgid(id_priv, (काष्ठा sockaddr *)&mc->addr,
				     &mgid);
			cma_igmp_send(ndev, &mgid, false);
			dev_put(ndev);
		पूर्ण

		cancel_work_sync(&mc->iboe_join.work);
	पूर्ण
	kमुक्त(mc);
पूर्ण

अटल व्योम cma_leave_mc_groups(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा cma_multicast *mc;

	जबतक (!list_empty(&id_priv->mc_list)) अणु
		mc = list_first_entry(&id_priv->mc_list, काष्ठा cma_multicast,
				      list);
		list_del(&mc->list);
		destroy_mc(id_priv, mc);
	पूर्ण
पूर्ण

अटल व्योम _destroy_id(काष्ठा rdma_id_निजी *id_priv,
			क्रमागत rdma_cm_state state)
अणु
	cma_cancel_operation(id_priv, state);

	अगर (id_priv->cma_dev) अणु
		अगर (rdma_cap_ib_cm(id_priv->id.device, 1)) अणु
			अगर (id_priv->cm_id.ib)
				ib_destroy_cm_id(id_priv->cm_id.ib);
		पूर्ण अन्यथा अगर (rdma_cap_iw_cm(id_priv->id.device, 1)) अणु
			अगर (id_priv->cm_id.iw)
				iw_destroy_cm_id(id_priv->cm_id.iw);
		पूर्ण
		cma_leave_mc_groups(id_priv);
		rdma_restrack_del(&id_priv->res);
		cma_release_dev(id_priv);
	पूर्ण

	cma_release_port(id_priv);
	cma_id_put(id_priv);
	रुको_क्रम_completion(&id_priv->comp);

	अगर (id_priv->पूर्णांकernal_id)
		cma_id_put(id_priv->id.context);

	kमुक्त(id_priv->id.route.path_rec);

	put_net(id_priv->id.route.addr.dev_addr.net);
	kमुक्त(id_priv);
पूर्ण

/*
 * destroy an ID from within the handler_mutex. This ensures that no other
 * handlers can start running concurrently.
 */
अटल व्योम destroy_id_handler_unlock(काष्ठा rdma_id_निजी *id_priv)
	__releases(&idprv->handler_mutex)
अणु
	क्रमागत rdma_cm_state state;
	अचिन्हित दीर्घ flags;

	trace_cm_id_destroy(id_priv);

	/*
	 * Setting the state to destroyed under the handler mutex provides a
	 * fence against calling handler callbacks. If this is invoked due to
	 * the failure of a handler callback then it guarentees that no future
	 * handlers will be called.
	 */
	lockdep_निश्चित_held(&id_priv->handler_mutex);
	spin_lock_irqsave(&id_priv->lock, flags);
	state = id_priv->state;
	id_priv->state = RDMA_CM_DESTROYING;
	spin_unlock_irqrestore(&id_priv->lock, flags);
	mutex_unlock(&id_priv->handler_mutex);
	_destroy_id(id_priv, state);
पूर्ण

व्योम rdma_destroy_id(काष्ठा rdma_cm_id *id)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);

	mutex_lock(&id_priv->handler_mutex);
	destroy_id_handler_unlock(id_priv);
पूर्ण
EXPORT_SYMBOL(rdma_destroy_id);

अटल पूर्णांक cma_rep_recv(काष्ठा rdma_id_निजी *id_priv)
अणु
	पूर्णांक ret;

	ret = cma_modअगरy_qp_rtr(id_priv, शून्य);
	अगर (ret)
		जाओ reject;

	ret = cma_modअगरy_qp_rts(id_priv, शून्य);
	अगर (ret)
		जाओ reject;

	trace_cm_send_rtu(id_priv);
	ret = ib_send_cm_rtu(id_priv->cm_id.ib, शून्य, 0);
	अगर (ret)
		जाओ reject;

	वापस 0;
reject:
	pr_debug_ratelimited("RDMA CM: CONNECT_ERROR: failed to handle reply. status %d\n", ret);
	cma_modअगरy_qp_err(id_priv);
	trace_cm_send_rej(id_priv);
	ib_send_cm_rej(id_priv->cm_id.ib, IB_CM_REJ_CONSUMER_DEFINED,
		       शून्य, 0, शून्य, 0);
	वापस ret;
पूर्ण

अटल व्योम cma_set_rep_event_data(काष्ठा rdma_cm_event *event,
				   स्थिर काष्ठा ib_cm_rep_event_param *rep_data,
				   व्योम *निजी_data)
अणु
	event->param.conn.निजी_data = निजी_data;
	event->param.conn.निजी_data_len = IB_CM_REP_PRIVATE_DATA_SIZE;
	event->param.conn.responder_resources = rep_data->responder_resources;
	event->param.conn.initiator_depth = rep_data->initiator_depth;
	event->param.conn.flow_control = rep_data->flow_control;
	event->param.conn.rnr_retry_count = rep_data->rnr_retry_count;
	event->param.conn.srq = rep_data->srq;
	event->param.conn.qp_num = rep_data->remote_qpn;

	event->ece.venकरोr_id = rep_data->ece.venकरोr_id;
	event->ece.attr_mod = rep_data->ece.attr_mod;
पूर्ण

अटल पूर्णांक cma_cm_event_handler(काष्ठा rdma_id_निजी *id_priv,
				काष्ठा rdma_cm_event *event)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&id_priv->handler_mutex);

	trace_cm_event_handler(id_priv, event);
	ret = id_priv->id.event_handler(&id_priv->id, event);
	trace_cm_event_करोne(id_priv, event, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_ib_handler(काष्ठा ib_cm_id *cm_id,
			  स्थिर काष्ठा ib_cm_event *ib_event)
अणु
	काष्ठा rdma_id_निजी *id_priv = cm_id->context;
	काष्ठा rdma_cm_event event = अणुपूर्ण;
	क्रमागत rdma_cm_state state;
	पूर्णांक ret;

	mutex_lock(&id_priv->handler_mutex);
	state = READ_ONCE(id_priv->state);
	अगर ((ib_event->event != IB_CM_TIMEWAIT_EXIT &&
	     state != RDMA_CM_CONNECT) ||
	    (ib_event->event == IB_CM_TIMEWAIT_EXIT &&
	     state != RDMA_CM_DISCONNECT))
		जाओ out;

	चयन (ib_event->event) अणु
	हाल IB_CM_REQ_ERROR:
	हाल IB_CM_REP_ERROR:
		event.event = RDMA_CM_EVENT_UNREACHABLE;
		event.status = -ETIMEDOUT;
		अवरोध;
	हाल IB_CM_REP_RECEIVED:
		अगर (state == RDMA_CM_CONNECT &&
		    (id_priv->id.qp_type != IB_QPT_UD)) अणु
			trace_cm_send_mra(id_priv);
			ib_send_cm_mra(cm_id, CMA_CM_MRA_SETTING, शून्य, 0);
		पूर्ण
		अगर (id_priv->id.qp) अणु
			event.status = cma_rep_recv(id_priv);
			event.event = event.status ? RDMA_CM_EVENT_CONNECT_ERROR :
						     RDMA_CM_EVENT_ESTABLISHED;
		पूर्ण अन्यथा अणु
			event.event = RDMA_CM_EVENT_CONNECT_RESPONSE;
		पूर्ण
		cma_set_rep_event_data(&event, &ib_event->param.rep_rcvd,
				       ib_event->निजी_data);
		अवरोध;
	हाल IB_CM_RTU_RECEIVED:
	हाल IB_CM_USER_ESTABLISHED:
		event.event = RDMA_CM_EVENT_ESTABLISHED;
		अवरोध;
	हाल IB_CM_DREQ_ERROR:
		event.status = -ETIMEDOUT;
		fallthrough;
	हाल IB_CM_DREQ_RECEIVED:
	हाल IB_CM_DREP_RECEIVED:
		अगर (!cma_comp_exch(id_priv, RDMA_CM_CONNECT,
				   RDMA_CM_DISCONNECT))
			जाओ out;
		event.event = RDMA_CM_EVENT_DISCONNECTED;
		अवरोध;
	हाल IB_CM_TIMEWAIT_EXIT:
		event.event = RDMA_CM_EVENT_TIMEWAIT_EXIT;
		अवरोध;
	हाल IB_CM_MRA_RECEIVED:
		/* ignore event */
		जाओ out;
	हाल IB_CM_REJ_RECEIVED:
		pr_debug_ratelimited("RDMA CM: REJECTED: %s\n", rdma_reject_msg(&id_priv->id,
										ib_event->param.rej_rcvd.reason));
		cma_modअगरy_qp_err(id_priv);
		event.status = ib_event->param.rej_rcvd.reason;
		event.event = RDMA_CM_EVENT_REJECTED;
		event.param.conn.निजी_data = ib_event->निजी_data;
		event.param.conn.निजी_data_len = IB_CM_REJ_PRIVATE_DATA_SIZE;
		अवरोध;
	शेष:
		pr_err("RDMA CMA: unexpected IB CM event: %d\n",
		       ib_event->event);
		जाओ out;
	पूर्ण

	ret = cma_cm_event_handler(id_priv, &event);
	अगर (ret) अणु
		/* Destroy the CM ID by वापसing a non-zero value. */
		id_priv->cm_id.ib = शून्य;
		destroy_id_handler_unlock(id_priv);
		वापस ret;
	पूर्ण
out:
	mutex_unlock(&id_priv->handler_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा rdma_id_निजी *
cma_ib_new_conn_id(स्थिर काष्ठा rdma_cm_id *listen_id,
		   स्थिर काष्ठा ib_cm_event *ib_event,
		   काष्ठा net_device *net_dev)
अणु
	काष्ठा rdma_id_निजी *listen_id_priv;
	काष्ठा rdma_id_निजी *id_priv;
	काष्ठा rdma_cm_id *id;
	काष्ठा rdma_route *rt;
	स्थिर sa_family_t ss_family = listen_id->route.addr.src_addr.ss_family;
	काष्ठा sa_path_rec *path = ib_event->param.req_rcvd.primary_path;
	स्थिर __be64 service_id =
		ib_event->param.req_rcvd.primary_path->service_id;
	पूर्णांक ret;

	listen_id_priv = container_of(listen_id, काष्ठा rdma_id_निजी, id);
	id_priv = __rdma_create_id(listen_id->route.addr.dev_addr.net,
				   listen_id->event_handler, listen_id->context,
				   listen_id->ps,
				   ib_event->param.req_rcvd.qp_type,
				   listen_id_priv);
	अगर (IS_ERR(id_priv))
		वापस शून्य;

	id = &id_priv->id;
	अगर (cma_save_net_info((काष्ठा sockaddr *)&id->route.addr.src_addr,
			      (काष्ठा sockaddr *)&id->route.addr.dst_addr,
			      listen_id, ib_event, ss_family, service_id))
		जाओ err;

	rt = &id->route;
	rt->num_paths = ib_event->param.req_rcvd.alternate_path ? 2 : 1;
	rt->path_rec = kदो_स्मृति_array(rt->num_paths, माप(*rt->path_rec),
				     GFP_KERNEL);
	अगर (!rt->path_rec)
		जाओ err;

	rt->path_rec[0] = *path;
	अगर (rt->num_paths == 2)
		rt->path_rec[1] = *ib_event->param.req_rcvd.alternate_path;

	अगर (net_dev) अणु
		rdma_copy_src_l2_addr(&rt->addr.dev_addr, net_dev);
	पूर्ण अन्यथा अणु
		अगर (!cma_protocol_roce(listen_id) &&
		    cma_any_addr(cma_src_addr(id_priv))) अणु
			rt->addr.dev_addr.dev_type = ARPHRD_INFINIBAND;
			rdma_addr_set_sgid(&rt->addr.dev_addr, &rt->path_rec[0].sgid);
			ib_addr_set_pkey(&rt->addr.dev_addr, be16_to_cpu(rt->path_rec[0].pkey));
		पूर्ण अन्यथा अगर (!cma_any_addr(cma_src_addr(id_priv))) अणु
			ret = cma_translate_addr(cma_src_addr(id_priv), &rt->addr.dev_addr);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण
	rdma_addr_set_dgid(&rt->addr.dev_addr, &rt->path_rec[0].dgid);

	id_priv->state = RDMA_CM_CONNECT;
	वापस id_priv;

err:
	rdma_destroy_id(id);
	वापस शून्य;
पूर्ण

अटल काष्ठा rdma_id_निजी *
cma_ib_new_udp_id(स्थिर काष्ठा rdma_cm_id *listen_id,
		  स्थिर काष्ठा ib_cm_event *ib_event,
		  काष्ठा net_device *net_dev)
अणु
	स्थिर काष्ठा rdma_id_निजी *listen_id_priv;
	काष्ठा rdma_id_निजी *id_priv;
	काष्ठा rdma_cm_id *id;
	स्थिर sa_family_t ss_family = listen_id->route.addr.src_addr.ss_family;
	काष्ठा net *net = listen_id->route.addr.dev_addr.net;
	पूर्णांक ret;

	listen_id_priv = container_of(listen_id, काष्ठा rdma_id_निजी, id);
	id_priv = __rdma_create_id(net, listen_id->event_handler,
				   listen_id->context, listen_id->ps, IB_QPT_UD,
				   listen_id_priv);
	अगर (IS_ERR(id_priv))
		वापस शून्य;

	id = &id_priv->id;
	अगर (cma_save_net_info((काष्ठा sockaddr *)&id->route.addr.src_addr,
			      (काष्ठा sockaddr *)&id->route.addr.dst_addr,
			      listen_id, ib_event, ss_family,
			      ib_event->param.sidr_req_rcvd.service_id))
		जाओ err;

	अगर (net_dev) अणु
		rdma_copy_src_l2_addr(&id->route.addr.dev_addr, net_dev);
	पूर्ण अन्यथा अणु
		अगर (!cma_any_addr(cma_src_addr(id_priv))) अणु
			ret = cma_translate_addr(cma_src_addr(id_priv),
						 &id->route.addr.dev_addr);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण

	id_priv->state = RDMA_CM_CONNECT;
	वापस id_priv;
err:
	rdma_destroy_id(id);
	वापस शून्य;
पूर्ण

अटल व्योम cma_set_req_event_data(काष्ठा rdma_cm_event *event,
				   स्थिर काष्ठा ib_cm_req_event_param *req_data,
				   व्योम *निजी_data, पूर्णांक offset)
अणु
	event->param.conn.निजी_data = निजी_data + offset;
	event->param.conn.निजी_data_len = IB_CM_REQ_PRIVATE_DATA_SIZE - offset;
	event->param.conn.responder_resources = req_data->responder_resources;
	event->param.conn.initiator_depth = req_data->initiator_depth;
	event->param.conn.flow_control = req_data->flow_control;
	event->param.conn.retry_count = req_data->retry_count;
	event->param.conn.rnr_retry_count = req_data->rnr_retry_count;
	event->param.conn.srq = req_data->srq;
	event->param.conn.qp_num = req_data->remote_qpn;

	event->ece.venकरोr_id = req_data->ece.venकरोr_id;
	event->ece.attr_mod = req_data->ece.attr_mod;
पूर्ण

अटल पूर्णांक cma_ib_check_req_qp_type(स्थिर काष्ठा rdma_cm_id *id,
				    स्थिर काष्ठा ib_cm_event *ib_event)
अणु
	वापस (((ib_event->event == IB_CM_REQ_RECEIVED) &&
		 (ib_event->param.req_rcvd.qp_type == id->qp_type)) ||
		((ib_event->event == IB_CM_SIDR_REQ_RECEIVED) &&
		 (id->qp_type == IB_QPT_UD)) ||
		(!id->qp_type));
पूर्ण

अटल पूर्णांक cma_ib_req_handler(काष्ठा ib_cm_id *cm_id,
			      स्थिर काष्ठा ib_cm_event *ib_event)
अणु
	काष्ठा rdma_id_निजी *listen_id, *conn_id = शून्य;
	काष्ठा rdma_cm_event event = अणुपूर्ण;
	काष्ठा cma_req_info req = अणुपूर्ण;
	काष्ठा net_device *net_dev;
	u8 offset;
	पूर्णांक ret;

	listen_id = cma_ib_id_from_event(cm_id, ib_event, &req, &net_dev);
	अगर (IS_ERR(listen_id))
		वापस PTR_ERR(listen_id);

	trace_cm_req_handler(listen_id, ib_event->event);
	अगर (!cma_ib_check_req_qp_type(&listen_id->id, ib_event)) अणु
		ret = -EINVAL;
		जाओ net_dev_put;
	पूर्ण

	mutex_lock(&listen_id->handler_mutex);
	अगर (READ_ONCE(listen_id->state) != RDMA_CM_LISTEN) अणु
		ret = -ECONNABORTED;
		जाओ err_unlock;
	पूर्ण

	offset = cma_user_data_offset(listen_id);
	event.event = RDMA_CM_EVENT_CONNECT_REQUEST;
	अगर (ib_event->event == IB_CM_SIDR_REQ_RECEIVED) अणु
		conn_id = cma_ib_new_udp_id(&listen_id->id, ib_event, net_dev);
		event.param.ud.निजी_data = ib_event->निजी_data + offset;
		event.param.ud.निजी_data_len =
				IB_CM_SIDR_REQ_PRIVATE_DATA_SIZE - offset;
	पूर्ण अन्यथा अणु
		conn_id = cma_ib_new_conn_id(&listen_id->id, ib_event, net_dev);
		cma_set_req_event_data(&event, &ib_event->param.req_rcvd,
				       ib_event->निजी_data, offset);
	पूर्ण
	अगर (!conn_id) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	mutex_lock_nested(&conn_id->handler_mutex, SINGLE_DEPTH_NESTING);
	ret = cma_ib_acquire_dev(conn_id, listen_id, &req);
	अगर (ret) अणु
		destroy_id_handler_unlock(conn_id);
		जाओ err_unlock;
	पूर्ण

	conn_id->cm_id.ib = cm_id;
	cm_id->context = conn_id;
	cm_id->cm_handler = cma_ib_handler;

	ret = cma_cm_event_handler(conn_id, &event);
	अगर (ret) अणु
		/* Destroy the CM ID by वापसing a non-zero value. */
		conn_id->cm_id.ib = शून्य;
		mutex_unlock(&listen_id->handler_mutex);
		destroy_id_handler_unlock(conn_id);
		जाओ net_dev_put;
	पूर्ण

	अगर (READ_ONCE(conn_id->state) == RDMA_CM_CONNECT &&
	    conn_id->id.qp_type != IB_QPT_UD) अणु
		trace_cm_send_mra(cm_id->context);
		ib_send_cm_mra(cm_id, CMA_CM_MRA_SETTING, शून्य, 0);
	पूर्ण
	mutex_unlock(&conn_id->handler_mutex);

err_unlock:
	mutex_unlock(&listen_id->handler_mutex);

net_dev_put:
	अगर (net_dev)
		dev_put(net_dev);

	वापस ret;
पूर्ण

__be64 rdma_get_service_id(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *addr)
अणु
	अगर (addr->sa_family == AF_IB)
		वापस ((काष्ठा sockaddr_ib *) addr)->sib_sid;

	वापस cpu_to_be64(((u64)id->ps << 16) + be16_to_cpu(cma_port(addr)));
पूर्ण
EXPORT_SYMBOL(rdma_get_service_id);

व्योम rdma_पढ़ो_gids(काष्ठा rdma_cm_id *cm_id, जोड़ ib_gid *sgid,
		    जोड़ ib_gid *dgid)
अणु
	काष्ठा rdma_addr *addr = &cm_id->route.addr;

	अगर (!cm_id->device) अणु
		अगर (sgid)
			स_रखो(sgid, 0, माप(*sgid));
		अगर (dgid)
			स_रखो(dgid, 0, माप(*dgid));
		वापस;
	पूर्ण

	अगर (rdma_protocol_roce(cm_id->device, cm_id->port_num)) अणु
		अगर (sgid)
			rdma_ip2gid((काष्ठा sockaddr *)&addr->src_addr, sgid);
		अगर (dgid)
			rdma_ip2gid((काष्ठा sockaddr *)&addr->dst_addr, dgid);
	पूर्ण अन्यथा अणु
		अगर (sgid)
			rdma_addr_get_sgid(&addr->dev_addr, sgid);
		अगर (dgid)
			rdma_addr_get_dgid(&addr->dev_addr, dgid);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rdma_पढ़ो_gids);

अटल पूर्णांक cma_iw_handler(काष्ठा iw_cm_id *iw_id, काष्ठा iw_cm_event *iw_event)
अणु
	काष्ठा rdma_id_निजी *id_priv = iw_id->context;
	काष्ठा rdma_cm_event event = अणुपूर्ण;
	पूर्णांक ret = 0;
	काष्ठा sockaddr *laddr = (काष्ठा sockaddr *)&iw_event->local_addr;
	काष्ठा sockaddr *raddr = (काष्ठा sockaddr *)&iw_event->remote_addr;

	mutex_lock(&id_priv->handler_mutex);
	अगर (READ_ONCE(id_priv->state) != RDMA_CM_CONNECT)
		जाओ out;

	चयन (iw_event->event) अणु
	हाल IW_CM_EVENT_CLOSE:
		event.event = RDMA_CM_EVENT_DISCONNECTED;
		अवरोध;
	हाल IW_CM_EVENT_CONNECT_REPLY:
		स_नकल(cma_src_addr(id_priv), laddr,
		       rdma_addr_size(laddr));
		स_नकल(cma_dst_addr(id_priv), raddr,
		       rdma_addr_size(raddr));
		चयन (iw_event->status) अणु
		हाल 0:
			event.event = RDMA_CM_EVENT_ESTABLISHED;
			event.param.conn.initiator_depth = iw_event->ird;
			event.param.conn.responder_resources = iw_event->ord;
			अवरोध;
		हाल -ECONNRESET:
		हाल -ECONNREFUSED:
			event.event = RDMA_CM_EVENT_REJECTED;
			अवरोध;
		हाल -ETIMEDOUT:
			event.event = RDMA_CM_EVENT_UNREACHABLE;
			अवरोध;
		शेष:
			event.event = RDMA_CM_EVENT_CONNECT_ERROR;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IW_CM_EVENT_ESTABLISHED:
		event.event = RDMA_CM_EVENT_ESTABLISHED;
		event.param.conn.initiator_depth = iw_event->ird;
		event.param.conn.responder_resources = iw_event->ord;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	event.status = iw_event->status;
	event.param.conn.निजी_data = iw_event->निजी_data;
	event.param.conn.निजी_data_len = iw_event->निजी_data_len;
	ret = cma_cm_event_handler(id_priv, &event);
	अगर (ret) अणु
		/* Destroy the CM ID by वापसing a non-zero value. */
		id_priv->cm_id.iw = शून्य;
		destroy_id_handler_unlock(id_priv);
		वापस ret;
	पूर्ण

out:
	mutex_unlock(&id_priv->handler_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक iw_conn_req_handler(काष्ठा iw_cm_id *cm_id,
			       काष्ठा iw_cm_event *iw_event)
अणु
	काष्ठा rdma_id_निजी *listen_id, *conn_id;
	काष्ठा rdma_cm_event event = अणुपूर्ण;
	पूर्णांक ret = -ECONNABORTED;
	काष्ठा sockaddr *laddr = (काष्ठा sockaddr *)&iw_event->local_addr;
	काष्ठा sockaddr *raddr = (काष्ठा sockaddr *)&iw_event->remote_addr;

	event.event = RDMA_CM_EVENT_CONNECT_REQUEST;
	event.param.conn.निजी_data = iw_event->निजी_data;
	event.param.conn.निजी_data_len = iw_event->निजी_data_len;
	event.param.conn.initiator_depth = iw_event->ird;
	event.param.conn.responder_resources = iw_event->ord;

	listen_id = cm_id->context;

	mutex_lock(&listen_id->handler_mutex);
	अगर (READ_ONCE(listen_id->state) != RDMA_CM_LISTEN)
		जाओ out;

	/* Create a new RDMA id क्रम the new IW CM ID */
	conn_id = __rdma_create_id(listen_id->id.route.addr.dev_addr.net,
				   listen_id->id.event_handler,
				   listen_id->id.context, RDMA_PS_TCP,
				   IB_QPT_RC, listen_id);
	अगर (IS_ERR(conn_id)) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	mutex_lock_nested(&conn_id->handler_mutex, SINGLE_DEPTH_NESTING);
	conn_id->state = RDMA_CM_CONNECT;

	ret = rdma_translate_ip(laddr, &conn_id->id.route.addr.dev_addr);
	अगर (ret) अणु
		mutex_unlock(&listen_id->handler_mutex);
		destroy_id_handler_unlock(conn_id);
		वापस ret;
	पूर्ण

	ret = cma_iw_acquire_dev(conn_id, listen_id);
	अगर (ret) अणु
		mutex_unlock(&listen_id->handler_mutex);
		destroy_id_handler_unlock(conn_id);
		वापस ret;
	पूर्ण

	conn_id->cm_id.iw = cm_id;
	cm_id->context = conn_id;
	cm_id->cm_handler = cma_iw_handler;

	स_नकल(cma_src_addr(conn_id), laddr, rdma_addr_size(laddr));
	स_नकल(cma_dst_addr(conn_id), raddr, rdma_addr_size(raddr));

	ret = cma_cm_event_handler(conn_id, &event);
	अगर (ret) अणु
		/* User wants to destroy the CM ID */
		conn_id->cm_id.iw = शून्य;
		mutex_unlock(&listen_id->handler_mutex);
		destroy_id_handler_unlock(conn_id);
		वापस ret;
	पूर्ण

	mutex_unlock(&conn_id->handler_mutex);

out:
	mutex_unlock(&listen_id->handler_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_ib_listen(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा sockaddr *addr;
	काष्ठा ib_cm_id	*id;
	__be64 svc_id;

	addr = cma_src_addr(id_priv);
	svc_id = rdma_get_service_id(&id_priv->id, addr);
	id = ib_cm_insert_listen(id_priv->id.device,
				 cma_ib_req_handler, svc_id);
	अगर (IS_ERR(id))
		वापस PTR_ERR(id);
	id_priv->cm_id.ib = id;

	वापस 0;
पूर्ण

अटल पूर्णांक cma_iw_listen(काष्ठा rdma_id_निजी *id_priv, पूर्णांक backlog)
अणु
	पूर्णांक ret;
	काष्ठा iw_cm_id	*id;

	id = iw_create_cm_id(id_priv->id.device,
			     iw_conn_req_handler,
			     id_priv);
	अगर (IS_ERR(id))
		वापस PTR_ERR(id);

	id->tos = id_priv->tos;
	id->tos_set = id_priv->tos_set;
	id->afonly = id_priv->afonly;
	id_priv->cm_id.iw = id;

	स_नकल(&id_priv->cm_id.iw->local_addr, cma_src_addr(id_priv),
	       rdma_addr_size(cma_src_addr(id_priv)));

	ret = iw_cm_listen(id_priv->cm_id.iw, backlog);

	अगर (ret) अणु
		iw_destroy_cm_id(id_priv->cm_id.iw);
		id_priv->cm_id.iw = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cma_listen_handler(काष्ठा rdma_cm_id *id,
			      काष्ठा rdma_cm_event *event)
अणु
	काष्ठा rdma_id_निजी *id_priv = id->context;

	/* Listening IDs are always destroyed on removal */
	अगर (event->event == RDMA_CM_EVENT_DEVICE_REMOVAL)
		वापस -1;

	id->context = id_priv->id.context;
	id->event_handler = id_priv->id.event_handler;
	trace_cm_event_handler(id_priv, event);
	वापस id_priv->id.event_handler(id, event);
पूर्ण

अटल पूर्णांक cma_listen_on_dev(काष्ठा rdma_id_निजी *id_priv,
			     काष्ठा cma_device *cma_dev,
			     काष्ठा rdma_id_निजी **to_destroy)
अणु
	काष्ठा rdma_id_निजी *dev_id_priv;
	काष्ठा net *net = id_priv->id.route.addr.dev_addr.net;
	पूर्णांक ret;

	lockdep_निश्चित_held(&lock);

	*to_destroy = शून्य;
	अगर (cma_family(id_priv) == AF_IB && !rdma_cap_ib_cm(cma_dev->device, 1))
		वापस 0;

	dev_id_priv =
		__rdma_create_id(net, cma_listen_handler, id_priv,
				 id_priv->id.ps, id_priv->id.qp_type, id_priv);
	अगर (IS_ERR(dev_id_priv))
		वापस PTR_ERR(dev_id_priv);

	dev_id_priv->state = RDMA_CM_ADDR_BOUND;
	स_नकल(cma_src_addr(dev_id_priv), cma_src_addr(id_priv),
	       rdma_addr_size(cma_src_addr(id_priv)));

	_cma_attach_to_dev(dev_id_priv, cma_dev);
	rdma_restrack_add(&dev_id_priv->res);
	cma_id_get(id_priv);
	dev_id_priv->पूर्णांकernal_id = 1;
	dev_id_priv->afonly = id_priv->afonly;
	dev_id_priv->tos_set = id_priv->tos_set;
	dev_id_priv->tos = id_priv->tos;

	ret = rdma_listen(&dev_id_priv->id, id_priv->backlog);
	अगर (ret)
		जाओ err_listen;
	list_add_tail(&dev_id_priv->listen_list, &id_priv->listen_list);
	वापस 0;
err_listen:
	/* Caller must destroy this after releasing lock */
	*to_destroy = dev_id_priv;
	dev_warn(&cma_dev->device->dev, "RDMA CMA: %s, error %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_listen_on_all(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_id_निजी *to_destroy;
	काष्ठा cma_device *cma_dev;
	पूर्णांक ret;

	mutex_lock(&lock);
	list_add_tail(&id_priv->list, &listen_any_list);
	list_क्रम_each_entry(cma_dev, &dev_list, list) अणु
		ret = cma_listen_on_dev(id_priv, cma_dev, &to_destroy);
		अगर (ret) अणु
			/* Prevent racing with cma_process_हटाओ() */
			अगर (to_destroy)
				list_del_init(&to_destroy->list);
			जाओ err_listen;
		पूर्ण
	पूर्ण
	mutex_unlock(&lock);
	वापस 0;

err_listen:
	list_del(&id_priv->list);
	mutex_unlock(&lock);
	अगर (to_destroy)
		rdma_destroy_id(&to_destroy->id);
	वापस ret;
पूर्ण

व्योम rdma_set_service_type(काष्ठा rdma_cm_id *id, पूर्णांक tos)
अणु
	काष्ठा rdma_id_निजी *id_priv;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	id_priv->tos = (u8) tos;
	id_priv->tos_set = true;
पूर्ण
EXPORT_SYMBOL(rdma_set_service_type);

/**
 * rdma_set_ack_समयout() - Set the ack समयout of QP associated
 *                          with a connection identअगरier.
 * @id: Communication identअगरier to associated with service type.
 * @समयout: Ack समयout to set a QP, expressed as 4.096 * 2^(समयout) usec.
 *
 * This function should be called beक्रमe rdma_connect() on active side,
 * and on passive side beक्रमe rdma_accept(). It is applicable to primary
 * path only. The समयout will affect the local side of the QP, it is not
 * negotiated with remote side and zero disables the समयr. In हाल it is
 * set beक्रमe rdma_resolve_route, the value will also be used to determine
 * PacketLअगरeTime क्रम RoCE.
 *
 * Return: 0 क्रम success
 */
पूर्णांक rdma_set_ack_समयout(काष्ठा rdma_cm_id *id, u8 समयout)
अणु
	काष्ठा rdma_id_निजी *id_priv;

	अगर (id->qp_type != IB_QPT_RC)
		वापस -EINVAL;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	id_priv->समयout = समयout;
	id_priv->समयout_set = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rdma_set_ack_समयout);

/**
 * rdma_set_min_rnr_समयr() - Set the minimum RNR Retry समयr of the
 *			      QP associated with a connection identअगरier.
 * @id: Communication identअगरier to associated with service type.
 * @min_rnr_समयr: 5-bit value encoded as Table 45: "Encoding क्रम RNR NAK
 *		   Timer Field" in the IBTA specअगरication.
 *
 * This function should be called beक्रमe rdma_connect() on active
 * side, and on passive side beक्रमe rdma_accept(). The समयr value
 * will be associated with the local QP. When it receives a send it is
 * not पढ़ो to handle, typically अगर the receive queue is empty, an RNR
 * Retry NAK is वापसed to the requester with the min_rnr_समयr
 * encoded. The requester will then रुको at least the समय specअगरied
 * in the NAK beक्रमe retrying. The शेष is zero, which translates
 * to a minimum RNR Timer value of 655 ms.
 *
 * Return: 0 क्रम success
 */
पूर्णांक rdma_set_min_rnr_समयr(काष्ठा rdma_cm_id *id, u8 min_rnr_समयr)
अणु
	काष्ठा rdma_id_निजी *id_priv;

	/* It is a five-bit value */
	अगर (min_rnr_समयr & 0xe0)
		वापस -EINVAL;

	अगर (WARN_ON(id->qp_type != IB_QPT_RC && id->qp_type != IB_QPT_XRC_TGT))
		वापस -EINVAL;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	id_priv->min_rnr_समयr = min_rnr_समयr;
	id_priv->min_rnr_समयr_set = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rdma_set_min_rnr_समयr);

अटल व्योम cma_query_handler(पूर्णांक status, काष्ठा sa_path_rec *path_rec,
			      व्योम *context)
अणु
	काष्ठा cma_work *work = context;
	काष्ठा rdma_route *route;

	route = &work->id->id.route;

	अगर (!status) अणु
		route->num_paths = 1;
		*route->path_rec = *path_rec;
	पूर्ण अन्यथा अणु
		work->old_state = RDMA_CM_ROUTE_QUERY;
		work->new_state = RDMA_CM_ADDR_RESOLVED;
		work->event.event = RDMA_CM_EVENT_ROUTE_ERROR;
		work->event.status = status;
		pr_debug_ratelimited("RDMA CM: ROUTE_ERROR: failed to query path. status %d\n",
				     status);
	पूर्ण

	queue_work(cma_wq, &work->work);
पूर्ण

अटल पूर्णांक cma_query_ib_route(काष्ठा rdma_id_निजी *id_priv,
			      अचिन्हित दीर्घ समयout_ms, काष्ठा cma_work *work)
अणु
	काष्ठा rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	काष्ठा sa_path_rec path_rec;
	ib_sa_comp_mask comp_mask;
	काष्ठा sockaddr_in6 *sin6;
	काष्ठा sockaddr_ib *sib;

	स_रखो(&path_rec, 0, माप path_rec);

	अगर (rdma_cap_opa_ah(id_priv->id.device, id_priv->id.port_num))
		path_rec.rec_type = SA_PATH_REC_TYPE_OPA;
	अन्यथा
		path_rec.rec_type = SA_PATH_REC_TYPE_IB;
	rdma_addr_get_sgid(dev_addr, &path_rec.sgid);
	rdma_addr_get_dgid(dev_addr, &path_rec.dgid);
	path_rec.pkey = cpu_to_be16(ib_addr_get_pkey(dev_addr));
	path_rec.numb_path = 1;
	path_rec.reversible = 1;
	path_rec.service_id = rdma_get_service_id(&id_priv->id,
						  cma_dst_addr(id_priv));

	comp_mask = IB_SA_PATH_REC_DGID | IB_SA_PATH_REC_SGID |
		    IB_SA_PATH_REC_PKEY | IB_SA_PATH_REC_NUMB_PATH |
		    IB_SA_PATH_REC_REVERSIBLE | IB_SA_PATH_REC_SERVICE_ID;

	चयन (cma_family(id_priv)) अणु
	हाल AF_INET:
		path_rec.qos_class = cpu_to_be16((u16) id_priv->tos);
		comp_mask |= IB_SA_PATH_REC_QOS_CLASS;
		अवरोध;
	हाल AF_INET6:
		sin6 = (काष्ठा sockaddr_in6 *) cma_src_addr(id_priv);
		path_rec.traffic_class = (u8) (be32_to_cpu(sin6->sin6_flowinfo) >> 20);
		comp_mask |= IB_SA_PATH_REC_TRAFFIC_CLASS;
		अवरोध;
	हाल AF_IB:
		sib = (काष्ठा sockaddr_ib *) cma_src_addr(id_priv);
		path_rec.traffic_class = (u8) (be32_to_cpu(sib->sib_flowinfo) >> 20);
		comp_mask |= IB_SA_PATH_REC_TRAFFIC_CLASS;
		अवरोध;
	पूर्ण

	id_priv->query_id = ib_sa_path_rec_get(&sa_client, id_priv->id.device,
					       id_priv->id.port_num, &path_rec,
					       comp_mask, समयout_ms,
					       GFP_KERNEL, cma_query_handler,
					       work, &id_priv->query);

	वापस (id_priv->query_id < 0) ? id_priv->query_id : 0;
पूर्ण

अटल व्योम cma_iboe_join_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cma_multicast *mc =
		container_of(work, काष्ठा cma_multicast, iboe_join.work);
	काष्ठा rdma_cm_event *event = &mc->iboe_join.event;
	काष्ठा rdma_id_निजी *id_priv = mc->id_priv;
	पूर्णांक ret;

	mutex_lock(&id_priv->handler_mutex);
	अगर (READ_ONCE(id_priv->state) == RDMA_CM_DESTROYING ||
	    READ_ONCE(id_priv->state) == RDMA_CM_DEVICE_REMOVAL)
		जाओ out_unlock;

	ret = cma_cm_event_handler(id_priv, event);
	WARN_ON(ret);

out_unlock:
	mutex_unlock(&id_priv->handler_mutex);
	अगर (event->event == RDMA_CM_EVENT_MULTICAST_JOIN)
		rdma_destroy_ah_attr(&event->param.ud.ah_attr);
पूर्ण

अटल व्योम cma_work_handler(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा cma_work *work = container_of(_work, काष्ठा cma_work, work);
	काष्ठा rdma_id_निजी *id_priv = work->id;

	mutex_lock(&id_priv->handler_mutex);
	अगर (READ_ONCE(id_priv->state) == RDMA_CM_DESTROYING ||
	    READ_ONCE(id_priv->state) == RDMA_CM_DEVICE_REMOVAL)
		जाओ out_unlock;
	अगर (work->old_state != 0 || work->new_state != 0) अणु
		अगर (!cma_comp_exch(id_priv, work->old_state, work->new_state))
			जाओ out_unlock;
	पूर्ण

	अगर (cma_cm_event_handler(id_priv, &work->event)) अणु
		cma_id_put(id_priv);
		destroy_id_handler_unlock(id_priv);
		जाओ out_मुक्त;
	पूर्ण

out_unlock:
	mutex_unlock(&id_priv->handler_mutex);
	cma_id_put(id_priv);
out_मुक्त:
	अगर (work->event.event == RDMA_CM_EVENT_MULTICAST_JOIN)
		rdma_destroy_ah_attr(&work->event.param.ud.ah_attr);
	kमुक्त(work);
पूर्ण

अटल व्योम cma_init_resolve_route_work(काष्ठा cma_work *work,
					काष्ठा rdma_id_निजी *id_priv)
अणु
	work->id = id_priv;
	INIT_WORK(&work->work, cma_work_handler);
	work->old_state = RDMA_CM_ROUTE_QUERY;
	work->new_state = RDMA_CM_ROUTE_RESOLVED;
	work->event.event = RDMA_CM_EVENT_ROUTE_RESOLVED;
पूर्ण

अटल व्योम enqueue_resolve_addr_work(काष्ठा cma_work *work,
				      काष्ठा rdma_id_निजी *id_priv)
अणु
	/* Balances with cma_id_put() in cma_work_handler */
	cma_id_get(id_priv);

	work->id = id_priv;
	INIT_WORK(&work->work, cma_work_handler);
	work->old_state = RDMA_CM_ADDR_QUERY;
	work->new_state = RDMA_CM_ADDR_RESOLVED;
	work->event.event = RDMA_CM_EVENT_ADDR_RESOLVED;

	queue_work(cma_wq, &work->work);
पूर्ण

अटल पूर्णांक cma_resolve_ib_route(काष्ठा rdma_id_निजी *id_priv,
				अचिन्हित दीर्घ समयout_ms)
अणु
	काष्ठा rdma_route *route = &id_priv->id.route;
	काष्ठा cma_work *work;
	पूर्णांक ret;

	work = kzalloc(माप *work, GFP_KERNEL);
	अगर (!work)
		वापस -ENOMEM;

	cma_init_resolve_route_work(work, id_priv);

	route->path_rec = kदो_स्मृति(माप *route->path_rec, GFP_KERNEL);
	अगर (!route->path_rec) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	ret = cma_query_ib_route(id_priv, समयout_ms, work);
	अगर (ret)
		जाओ err2;

	वापस 0;
err2:
	kमुक्त(route->path_rec);
	route->path_rec = शून्य;
err1:
	kमुक्त(work);
	वापस ret;
पूर्ण

अटल क्रमागत ib_gid_type cma_route_gid_type(क्रमागत rdma_network_type network_type,
					   अचिन्हित दीर्घ supported_gids,
					   क्रमागत ib_gid_type शेष_gid)
अणु
	अगर ((network_type == RDMA_NETWORK_IPV4 ||
	     network_type == RDMA_NETWORK_IPV6) &&
	    test_bit(IB_GID_TYPE_ROCE_UDP_ENCAP, &supported_gids))
		वापस IB_GID_TYPE_ROCE_UDP_ENCAP;

	वापस शेष_gid;
पूर्ण

/*
 * cma_iboe_set_path_rec_l2_fields() is helper function which sets
 * path record type based on GID type.
 * It also sets up other L2 fields which includes destination mac address
 * netdev अगरindex, of the path record.
 * It वापसs the netdev of the bound पूर्णांकerface क्रम this path record entry.
 */
अटल काष्ठा net_device *
cma_iboe_set_path_rec_l2_fields(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_route *route = &id_priv->id.route;
	क्रमागत ib_gid_type gid_type = IB_GID_TYPE_ROCE;
	काष्ठा rdma_addr *addr = &route->addr;
	अचिन्हित दीर्घ supported_gids;
	काष्ठा net_device *ndev;

	अगर (!addr->dev_addr.bound_dev_अगर)
		वापस शून्य;

	ndev = dev_get_by_index(addr->dev_addr.net,
				addr->dev_addr.bound_dev_अगर);
	अगर (!ndev)
		वापस शून्य;

	supported_gids = roce_gid_type_mask_support(id_priv->id.device,
						    id_priv->id.port_num);
	gid_type = cma_route_gid_type(addr->dev_addr.network,
				      supported_gids,
				      id_priv->gid_type);
	/* Use the hपूर्णांक from IP Stack to select GID Type */
	अगर (gid_type < ib_network_to_gid_type(addr->dev_addr.network))
		gid_type = ib_network_to_gid_type(addr->dev_addr.network);
	route->path_rec->rec_type = sa_conv_gid_to_pathrec_type(gid_type);

	route->path_rec->roce.route_resolved = true;
	sa_path_set_dmac(route->path_rec, addr->dev_addr.dst_dev_addr);
	वापस ndev;
पूर्ण

पूर्णांक rdma_set_ib_path(काष्ठा rdma_cm_id *id,
		     काष्ठा sa_path_rec *path_rec)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	काष्ठा net_device *ndev;
	पूर्णांक ret;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	अगर (!cma_comp_exch(id_priv, RDMA_CM_ADDR_RESOLVED,
			   RDMA_CM_ROUTE_RESOLVED))
		वापस -EINVAL;

	id->route.path_rec = kmemdup(path_rec, माप(*path_rec),
				     GFP_KERNEL);
	अगर (!id->route.path_rec) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	अगर (rdma_protocol_roce(id->device, id->port_num)) अणु
		ndev = cma_iboe_set_path_rec_l2_fields(id_priv);
		अगर (!ndev) अणु
			ret = -ENODEV;
			जाओ err_मुक्त;
		पूर्ण
		dev_put(ndev);
	पूर्ण

	id->route.num_paths = 1;
	वापस 0;

err_मुक्त:
	kमुक्त(id->route.path_rec);
	id->route.path_rec = शून्य;
err:
	cma_comp_exch(id_priv, RDMA_CM_ROUTE_RESOLVED, RDMA_CM_ADDR_RESOLVED);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_set_ib_path);

अटल पूर्णांक cma_resolve_iw_route(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा cma_work *work;

	work = kzalloc(माप *work, GFP_KERNEL);
	अगर (!work)
		वापस -ENOMEM;

	cma_init_resolve_route_work(work, id_priv);
	queue_work(cma_wq, &work->work);
	वापस 0;
पूर्ण

अटल पूर्णांक get_vlan_ndev_tc(काष्ठा net_device *vlan_ndev, पूर्णांक prio)
अणु
	काष्ठा net_device *dev;

	dev = vlan_dev_real_dev(vlan_ndev);
	अगर (dev->num_tc)
		वापस netdev_get_prio_tc_map(dev, prio);

	वापस (vlan_dev_get_egress_qos_mask(vlan_ndev, prio) &
		VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
पूर्ण

काष्ठा iboe_prio_tc_map अणु
	पूर्णांक input_prio;
	पूर्णांक output_tc;
	bool found;
पूर्ण;

अटल पूर्णांक get_lower_vlan_dev_tc(काष्ठा net_device *dev,
				 काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा iboe_prio_tc_map *map = (काष्ठा iboe_prio_tc_map *)priv->data;

	अगर (is_vlan_dev(dev))
		map->output_tc = get_vlan_ndev_tc(dev, map->input_prio);
	अन्यथा अगर (dev->num_tc)
		map->output_tc = netdev_get_prio_tc_map(dev, map->input_prio);
	अन्यथा
		map->output_tc = 0;
	/* We are पूर्णांकerested only in first level VLAN device, so always
	 * वापस 1 to stop iterating over next level devices.
	 */
	map->found = true;
	वापस 1;
पूर्ण

अटल पूर्णांक iboe_tos_to_sl(काष्ठा net_device *ndev, पूर्णांक tos)
अणु
	काष्ठा iboe_prio_tc_map prio_tc_map = अणुपूर्ण;
	पूर्णांक prio = rt_tos2priority(tos);
	काष्ठा netdev_nested_priv priv;

	/* If VLAN device, get it directly from the VLAN netdev */
	अगर (is_vlan_dev(ndev))
		वापस get_vlan_ndev_tc(ndev, prio);

	prio_tc_map.input_prio = prio;
	priv.data = (व्योम *)&prio_tc_map;
	rcu_पढ़ो_lock();
	netdev_walk_all_lower_dev_rcu(ndev,
				      get_lower_vlan_dev_tc,
				      &priv);
	rcu_पढ़ो_unlock();
	/* If map is found from lower device, use it; Otherwise
	 * जारी with the current netdevice to get priority to tc map.
	 */
	अगर (prio_tc_map.found)
		वापस prio_tc_map.output_tc;
	अन्यथा अगर (ndev->num_tc)
		वापस netdev_get_prio_tc_map(ndev, prio);
	अन्यथा
		वापस 0;
पूर्ण

अटल __be32 cma_get_roce_udp_flow_label(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा sockaddr_in6 *addr6;
	u16 dport, sport;
	u32 hash, fl;

	addr6 = (काष्ठा sockaddr_in6 *)cma_src_addr(id_priv);
	fl = be32_to_cpu(addr6->sin6_flowinfo) & IB_GRH_FLOWLABEL_MASK;
	अगर ((cma_family(id_priv) != AF_INET6) || !fl) अणु
		dport = be16_to_cpu(cma_port(cma_dst_addr(id_priv)));
		sport = be16_to_cpu(cma_port(cma_src_addr(id_priv)));
		hash = (u32)sport * 31 + dport;
		fl = hash & IB_GRH_FLOWLABEL_MASK;
	पूर्ण

	वापस cpu_to_be32(fl);
पूर्ण

अटल पूर्णांक cma_resolve_iboe_route(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_route *route = &id_priv->id.route;
	काष्ठा rdma_addr *addr = &route->addr;
	काष्ठा cma_work *work;
	पूर्णांक ret;
	काष्ठा net_device *ndev;

	u8 शेष_roce_tos = id_priv->cma_dev->शेष_roce_tos[id_priv->id.port_num -
					rdma_start_port(id_priv->cma_dev->device)];
	u8 tos = id_priv->tos_set ? id_priv->tos : शेष_roce_tos;


	work = kzalloc(माप *work, GFP_KERNEL);
	अगर (!work)
		वापस -ENOMEM;

	route->path_rec = kzalloc(माप *route->path_rec, GFP_KERNEL);
	अगर (!route->path_rec) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	route->num_paths = 1;

	ndev = cma_iboe_set_path_rec_l2_fields(id_priv);
	अगर (!ndev) अणु
		ret = -ENODEV;
		जाओ err2;
	पूर्ण

	rdma_ip2gid((काष्ठा sockaddr *)&id_priv->id.route.addr.src_addr,
		    &route->path_rec->sgid);
	rdma_ip2gid((काष्ठा sockaddr *)&id_priv->id.route.addr.dst_addr,
		    &route->path_rec->dgid);

	अगर (((काष्ठा sockaddr *)&id_priv->id.route.addr.dst_addr)->sa_family != AF_IB)
		/* TODO: get the hoplimit from the inet/inet6 device */
		route->path_rec->hop_limit = addr->dev_addr.hoplimit;
	अन्यथा
		route->path_rec->hop_limit = 1;
	route->path_rec->reversible = 1;
	route->path_rec->pkey = cpu_to_be16(0xffff);
	route->path_rec->mtu_selector = IB_SA_EQ;
	route->path_rec->sl = iboe_tos_to_sl(ndev, tos);
	route->path_rec->traffic_class = tos;
	route->path_rec->mtu = iboe_get_mtu(ndev->mtu);
	route->path_rec->rate_selector = IB_SA_EQ;
	route->path_rec->rate = iboe_get_rate(ndev);
	dev_put(ndev);
	route->path_rec->packet_lअगरe_समय_selector = IB_SA_EQ;
	/* In हाल ACK समयout is set, use this value to calculate
	 * PacketLअगरeTime.  As per IBTA 12.7.34,
	 * local ACK समयout = (2 * PacketLअगरeTime + Local CAै s ACK delay).
	 * Assuming a negligible local ACK delay, we can use
	 * PacketLअगरeTime = local ACK समयout/2
	 * as a reasonable approximation क्रम RoCE networks.
	 */
	route->path_rec->packet_lअगरe_समय = id_priv->समयout_set ?
		id_priv->समयout - 1 : CMA_IBOE_PACKET_LIFETIME;

	अगर (!route->path_rec->mtu) अणु
		ret = -EINVAL;
		जाओ err2;
	पूर्ण

	अगर (rdma_protocol_roce_udp_encap(id_priv->id.device,
					 id_priv->id.port_num))
		route->path_rec->flow_label =
			cma_get_roce_udp_flow_label(id_priv);

	cma_init_resolve_route_work(work, id_priv);
	queue_work(cma_wq, &work->work);

	वापस 0;

err2:
	kमुक्त(route->path_rec);
	route->path_rec = शून्य;
	route->num_paths = 0;
err1:
	kमुक्त(work);
	वापस ret;
पूर्ण

पूर्णांक rdma_resolve_route(काष्ठा rdma_cm_id *id, अचिन्हित दीर्घ समयout_ms)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	पूर्णांक ret;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	अगर (!cma_comp_exch(id_priv, RDMA_CM_ADDR_RESOLVED, RDMA_CM_ROUTE_QUERY))
		वापस -EINVAL;

	cma_id_get(id_priv);
	अगर (rdma_cap_ib_sa(id->device, id->port_num))
		ret = cma_resolve_ib_route(id_priv, समयout_ms);
	अन्यथा अगर (rdma_protocol_roce(id->device, id->port_num))
		ret = cma_resolve_iboe_route(id_priv);
	अन्यथा अगर (rdma_protocol_iwarp(id->device, id->port_num))
		ret = cma_resolve_iw_route(id_priv);
	अन्यथा
		ret = -ENOSYS;

	अगर (ret)
		जाओ err;

	वापस 0;
err:
	cma_comp_exch(id_priv, RDMA_CM_ROUTE_QUERY, RDMA_CM_ADDR_RESOLVED);
	cma_id_put(id_priv);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_resolve_route);

अटल व्योम cma_set_loopback(काष्ठा sockaddr *addr)
अणु
	चयन (addr->sa_family) अणु
	हाल AF_INET:
		((काष्ठा sockaddr_in *) addr)->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		अवरोध;
	हाल AF_INET6:
		ipv6_addr_set(&((काष्ठा sockaddr_in6 *) addr)->sin6_addr,
			      0, 0, 0, htonl(1));
		अवरोध;
	शेष:
		ib_addr_set(&((काष्ठा sockaddr_ib *) addr)->sib_addr,
			    0, 0, 0, htonl(1));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cma_bind_loopback(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा cma_device *cma_dev, *cur_dev;
	जोड़ ib_gid gid;
	क्रमागत ib_port_state port_state;
	अचिन्हित पूर्णांक p;
	u16 pkey;
	पूर्णांक ret;

	cma_dev = शून्य;
	mutex_lock(&lock);
	list_क्रम_each_entry(cur_dev, &dev_list, list) अणु
		अगर (cma_family(id_priv) == AF_IB &&
		    !rdma_cap_ib_cm(cur_dev->device, 1))
			जारी;

		अगर (!cma_dev)
			cma_dev = cur_dev;

		rdma_क्रम_each_port (cur_dev->device, p) अणु
			अगर (!ib_get_cached_port_state(cur_dev->device, p, &port_state) &&
			    port_state == IB_PORT_ACTIVE) अणु
				cma_dev = cur_dev;
				जाओ port_found;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!cma_dev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	p = 1;

port_found:
	ret = rdma_query_gid(cma_dev->device, p, 0, &gid);
	अगर (ret)
		जाओ out;

	ret = ib_get_cached_pkey(cma_dev->device, p, 0, &pkey);
	अगर (ret)
		जाओ out;

	id_priv->id.route.addr.dev_addr.dev_type =
		(rdma_protocol_ib(cma_dev->device, p)) ?
		ARPHRD_INFINIBAND : ARPHRD_ETHER;

	rdma_addr_set_sgid(&id_priv->id.route.addr.dev_addr, &gid);
	ib_addr_set_pkey(&id_priv->id.route.addr.dev_addr, pkey);
	id_priv->id.port_num = p;
	cma_attach_to_dev(id_priv, cma_dev);
	rdma_restrack_add(&id_priv->res);
	cma_set_loopback(cma_src_addr(id_priv));
out:
	mutex_unlock(&lock);
	वापस ret;
पूर्ण

अटल व्योम addr_handler(पूर्णांक status, काष्ठा sockaddr *src_addr,
			 काष्ठा rdma_dev_addr *dev_addr, व्योम *context)
अणु
	काष्ठा rdma_id_निजी *id_priv = context;
	काष्ठा rdma_cm_event event = अणुपूर्ण;
	काष्ठा sockaddr *addr;
	काष्ठा sockaddr_storage old_addr;

	mutex_lock(&id_priv->handler_mutex);
	अगर (!cma_comp_exch(id_priv, RDMA_CM_ADDR_QUERY,
			   RDMA_CM_ADDR_RESOLVED))
		जाओ out;

	/*
	 * Store the previous src address, so that अगर we fail to acquire
	 * matching rdma device, old address can be restored back, which helps
	 * to cancel the cma listen operation correctly.
	 */
	addr = cma_src_addr(id_priv);
	स_नकल(&old_addr, addr, rdma_addr_size(addr));
	स_नकल(addr, src_addr, rdma_addr_size(src_addr));
	अगर (!status && !id_priv->cma_dev) अणु
		status = cma_acquire_dev_by_src_ip(id_priv);
		अगर (status)
			pr_debug_ratelimited("RDMA CM: ADDR_ERROR: failed to acquire device. status %d\n",
					     status);
		rdma_restrack_add(&id_priv->res);
	पूर्ण अन्यथा अगर (status) अणु
		pr_debug_ratelimited("RDMA CM: ADDR_ERROR: failed to resolve IP. status %d\n", status);
	पूर्ण

	अगर (status) अणु
		स_नकल(addr, &old_addr,
		       rdma_addr_size((काष्ठा sockaddr *)&old_addr));
		अगर (!cma_comp_exch(id_priv, RDMA_CM_ADDR_RESOLVED,
				   RDMA_CM_ADDR_BOUND))
			जाओ out;
		event.event = RDMA_CM_EVENT_ADDR_ERROR;
		event.status = status;
	पूर्ण अन्यथा
		event.event = RDMA_CM_EVENT_ADDR_RESOLVED;

	अगर (cma_cm_event_handler(id_priv, &event)) अणु
		destroy_id_handler_unlock(id_priv);
		वापस;
	पूर्ण
out:
	mutex_unlock(&id_priv->handler_mutex);
पूर्ण

अटल पूर्णांक cma_resolve_loopback(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा cma_work *work;
	जोड़ ib_gid gid;
	पूर्णांक ret;

	work = kzalloc(माप *work, GFP_KERNEL);
	अगर (!work)
		वापस -ENOMEM;

	अगर (!id_priv->cma_dev) अणु
		ret = cma_bind_loopback(id_priv);
		अगर (ret)
			जाओ err;
	पूर्ण

	rdma_addr_get_sgid(&id_priv->id.route.addr.dev_addr, &gid);
	rdma_addr_set_dgid(&id_priv->id.route.addr.dev_addr, &gid);

	enqueue_resolve_addr_work(work, id_priv);
	वापस 0;
err:
	kमुक्त(work);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_resolve_ib_addr(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा cma_work *work;
	पूर्णांक ret;

	work = kzalloc(माप *work, GFP_KERNEL);
	अगर (!work)
		वापस -ENOMEM;

	अगर (!id_priv->cma_dev) अणु
		ret = cma_resolve_ib_dev(id_priv);
		अगर (ret)
			जाओ err;
	पूर्ण

	rdma_addr_set_dgid(&id_priv->id.route.addr.dev_addr, (जोड़ ib_gid *)
		&(((काष्ठा sockaddr_ib *) &id_priv->id.route.addr.dst_addr)->sib_addr));

	enqueue_resolve_addr_work(work, id_priv);
	वापस 0;
err:
	kमुक्त(work);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_bind_addr(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *src_addr,
			 स्थिर काष्ठा sockaddr *dst_addr)
अणु
	अगर (!src_addr || !src_addr->sa_family) अणु
		src_addr = (काष्ठा sockaddr *) &id->route.addr.src_addr;
		src_addr->sa_family = dst_addr->sa_family;
		अगर (IS_ENABLED(CONFIG_IPV6) &&
		    dst_addr->sa_family == AF_INET6) अणु
			काष्ठा sockaddr_in6 *src_addr6 = (काष्ठा sockaddr_in6 *) src_addr;
			काष्ठा sockaddr_in6 *dst_addr6 = (काष्ठा sockaddr_in6 *) dst_addr;
			src_addr6->sin6_scope_id = dst_addr6->sin6_scope_id;
			अगर (ipv6_addr_type(&dst_addr6->sin6_addr) & IPV6_ADDR_LINKLOCAL)
				id->route.addr.dev_addr.bound_dev_अगर = dst_addr6->sin6_scope_id;
		पूर्ण अन्यथा अगर (dst_addr->sa_family == AF_IB) अणु
			((काष्ठा sockaddr_ib *) src_addr)->sib_pkey =
				((काष्ठा sockaddr_ib *) dst_addr)->sib_pkey;
		पूर्ण
	पूर्ण
	वापस rdma_bind_addr(id, src_addr);
पूर्ण

/*
 * If required, resolve the source address क्रम bind and leave the id_priv in
 * state RDMA_CM_ADDR_BOUND. This oddly uses the state to determine the prior
 * calls made by ULP, a previously bound ID will not be re-bound and src_addr is
 * ignored.
 */
अटल पूर्णांक resolve_prepare_src(काष्ठा rdma_id_निजी *id_priv,
			       काष्ठा sockaddr *src_addr,
			       स्थिर काष्ठा sockaddr *dst_addr)
अणु
	पूर्णांक ret;

	स_नकल(cma_dst_addr(id_priv), dst_addr, rdma_addr_size(dst_addr));
	अगर (!cma_comp_exch(id_priv, RDMA_CM_ADDR_BOUND, RDMA_CM_ADDR_QUERY)) अणु
		/* For a well behaved ULP state will be RDMA_CM_IDLE */
		ret = cma_bind_addr(&id_priv->id, src_addr, dst_addr);
		अगर (ret)
			जाओ err_dst;
		अगर (WARN_ON(!cma_comp_exch(id_priv, RDMA_CM_ADDR_BOUND,
					   RDMA_CM_ADDR_QUERY))) अणु
			ret = -EINVAL;
			जाओ err_dst;
		पूर्ण
	पूर्ण

	अगर (cma_family(id_priv) != dst_addr->sa_family) अणु
		ret = -EINVAL;
		जाओ err_state;
	पूर्ण
	वापस 0;

err_state:
	cma_comp_exch(id_priv, RDMA_CM_ADDR_QUERY, RDMA_CM_ADDR_BOUND);
err_dst:
	स_रखो(cma_dst_addr(id_priv), 0, rdma_addr_size(dst_addr));
	वापस ret;
पूर्ण

पूर्णांक rdma_resolve_addr(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *src_addr,
		      स्थिर काष्ठा sockaddr *dst_addr, अचिन्हित दीर्घ समयout_ms)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);
	पूर्णांक ret;

	ret = resolve_prepare_src(id_priv, src_addr, dst_addr);
	अगर (ret)
		वापस ret;

	अगर (cma_any_addr(dst_addr)) अणु
		ret = cma_resolve_loopback(id_priv);
	पूर्ण अन्यथा अणु
		अगर (dst_addr->sa_family == AF_IB) अणु
			ret = cma_resolve_ib_addr(id_priv);
		पूर्ण अन्यथा अणु
			ret = rdma_resolve_ip(cma_src_addr(id_priv), dst_addr,
					      &id->route.addr.dev_addr,
					      समयout_ms, addr_handler,
					      false, id_priv);
		पूर्ण
	पूर्ण
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	cma_comp_exch(id_priv, RDMA_CM_ADDR_QUERY, RDMA_CM_ADDR_BOUND);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_resolve_addr);

पूर्णांक rdma_set_reuseaddr(काष्ठा rdma_cm_id *id, पूर्णांक reuse)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	spin_lock_irqsave(&id_priv->lock, flags);
	अगर ((reuse && id_priv->state != RDMA_CM_LISTEN) ||
	    id_priv->state == RDMA_CM_IDLE) अणु
		id_priv->reuseaddr = reuse;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&id_priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_set_reuseaddr);

पूर्णांक rdma_set_afonly(काष्ठा rdma_cm_id *id, पूर्णांक afonly)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	spin_lock_irqsave(&id_priv->lock, flags);
	अगर (id_priv->state == RDMA_CM_IDLE || id_priv->state == RDMA_CM_ADDR_BOUND) अणु
		id_priv->options |= (1 << CMA_OPTION_AFONLY);
		id_priv->afonly = afonly;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&id_priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_set_afonly);

अटल व्योम cma_bind_port(काष्ठा rdma_bind_list *bind_list,
			  काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा sockaddr *addr;
	काष्ठा sockaddr_ib *sib;
	u64 sid, mask;
	__be16 port;

	lockdep_निश्चित_held(&lock);

	addr = cma_src_addr(id_priv);
	port = htons(bind_list->port);

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		((काष्ठा sockaddr_in *) addr)->sin_port = port;
		अवरोध;
	हाल AF_INET6:
		((काष्ठा sockaddr_in6 *) addr)->sin6_port = port;
		अवरोध;
	हाल AF_IB:
		sib = (काष्ठा sockaddr_ib *) addr;
		sid = be64_to_cpu(sib->sib_sid);
		mask = be64_to_cpu(sib->sib_sid_mask);
		sib->sib_sid = cpu_to_be64((sid & mask) | (u64) ntohs(port));
		sib->sib_sid_mask = cpu_to_be64(~0ULL);
		अवरोध;
	पूर्ण
	id_priv->bind_list = bind_list;
	hlist_add_head(&id_priv->node, &bind_list->owners);
पूर्ण

अटल पूर्णांक cma_alloc_port(क्रमागत rdma_ucm_port_space ps,
			  काष्ठा rdma_id_निजी *id_priv, अचिन्हित लघु snum)
अणु
	काष्ठा rdma_bind_list *bind_list;
	पूर्णांक ret;

	lockdep_निश्चित_held(&lock);

	bind_list = kzalloc(माप *bind_list, GFP_KERNEL);
	अगर (!bind_list)
		वापस -ENOMEM;

	ret = cma_ps_alloc(id_priv->id.route.addr.dev_addr.net, ps, bind_list,
			   snum);
	अगर (ret < 0)
		जाओ err;

	bind_list->ps = ps;
	bind_list->port = snum;
	cma_bind_port(bind_list, id_priv);
	वापस 0;
err:
	kमुक्त(bind_list);
	वापस ret == -ENOSPC ? -EADDRNOTAVAIL : ret;
पूर्ण

अटल पूर्णांक cma_port_is_unique(काष्ठा rdma_bind_list *bind_list,
			      काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_id_निजी *cur_id;
	काष्ठा sockaddr  *daddr = cma_dst_addr(id_priv);
	काष्ठा sockaddr  *saddr = cma_src_addr(id_priv);
	__be16 dport = cma_port(daddr);

	lockdep_निश्चित_held(&lock);

	hlist_क्रम_each_entry(cur_id, &bind_list->owners, node) अणु
		काष्ठा sockaddr  *cur_daddr = cma_dst_addr(cur_id);
		काष्ठा sockaddr  *cur_saddr = cma_src_addr(cur_id);
		__be16 cur_dport = cma_port(cur_daddr);

		अगर (id_priv == cur_id)
			जारी;

		/* dअगरferent dest port -> unique */
		अगर (!cma_any_port(daddr) &&
		    !cma_any_port(cur_daddr) &&
		    (dport != cur_dport))
			जारी;

		/* dअगरferent src address -> unique */
		अगर (!cma_any_addr(saddr) &&
		    !cma_any_addr(cur_saddr) &&
		    cma_addr_cmp(saddr, cur_saddr))
			जारी;

		/* dअगरferent dst address -> unique */
		अगर (!cma_any_addr(daddr) &&
		    !cma_any_addr(cur_daddr) &&
		    cma_addr_cmp(daddr, cur_daddr))
			जारी;

		वापस -EADDRNOTAVAIL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cma_alloc_any_port(क्रमागत rdma_ucm_port_space ps,
			      काष्ठा rdma_id_निजी *id_priv)
अणु
	अटल अचिन्हित पूर्णांक last_used_port;
	पूर्णांक low, high, reमुख्यing;
	अचिन्हित पूर्णांक rover;
	काष्ठा net *net = id_priv->id.route.addr.dev_addr.net;

	lockdep_निश्चित_held(&lock);

	inet_get_local_port_range(net, &low, &high);
	reमुख्यing = (high - low) + 1;
	rover = pअक्रमom_u32() % reमुख्यing + low;
retry:
	अगर (last_used_port != rover) अणु
		काष्ठा rdma_bind_list *bind_list;
		पूर्णांक ret;

		bind_list = cma_ps_find(net, ps, (अचिन्हित लघु)rover);

		अगर (!bind_list) अणु
			ret = cma_alloc_port(ps, id_priv, rover);
		पूर्ण अन्यथा अणु
			ret = cma_port_is_unique(bind_list, id_priv);
			अगर (!ret)
				cma_bind_port(bind_list, id_priv);
		पूर्ण
		/*
		 * Remember previously used port number in order to aव्योम
		 * re-using same port immediately after it is बंदd.
		 */
		अगर (!ret)
			last_used_port = rover;
		अगर (ret != -EADDRNOTAVAIL)
			वापस ret;
	पूर्ण
	अगर (--reमुख्यing) अणु
		rover++;
		अगर ((rover < low) || (rover > high))
			rover = low;
		जाओ retry;
	पूर्ण
	वापस -EADDRNOTAVAIL;
पूर्ण

/*
 * Check that the requested port is available.  This is called when trying to
 * bind to a specअगरic port, or when trying to listen on a bound port.  In
 * the latter हाल, the provided id_priv may alपढ़ोy be on the bind_list, but
 * we still need to check that it's okay to start listening.
 */
अटल पूर्णांक cma_check_port(काष्ठा rdma_bind_list *bind_list,
			  काष्ठा rdma_id_निजी *id_priv, uपूर्णांक8_t reuseaddr)
अणु
	काष्ठा rdma_id_निजी *cur_id;
	काष्ठा sockaddr *addr, *cur_addr;

	lockdep_निश्चित_held(&lock);

	addr = cma_src_addr(id_priv);
	hlist_क्रम_each_entry(cur_id, &bind_list->owners, node) अणु
		अगर (id_priv == cur_id)
			जारी;

		अगर (reuseaddr && cur_id->reuseaddr)
			जारी;

		cur_addr = cma_src_addr(cur_id);
		अगर (id_priv->afonly && cur_id->afonly &&
		    (addr->sa_family != cur_addr->sa_family))
			जारी;

		अगर (cma_any_addr(addr) || cma_any_addr(cur_addr))
			वापस -EADDRNOTAVAIL;

		अगर (!cma_addr_cmp(addr, cur_addr))
			वापस -EADDRINUSE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cma_use_port(क्रमागत rdma_ucm_port_space ps,
			काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_bind_list *bind_list;
	अचिन्हित लघु snum;
	पूर्णांक ret;

	lockdep_निश्चित_held(&lock);

	snum = ntohs(cma_port(cma_src_addr(id_priv)));
	अगर (snum < PROT_SOCK && !capable(CAP_NET_BIND_SERVICE))
		वापस -EACCES;

	bind_list = cma_ps_find(id_priv->id.route.addr.dev_addr.net, ps, snum);
	अगर (!bind_list) अणु
		ret = cma_alloc_port(ps, id_priv, snum);
	पूर्ण अन्यथा अणु
		ret = cma_check_port(bind_list, id_priv, id_priv->reuseaddr);
		अगर (!ret)
			cma_bind_port(bind_list, id_priv);
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत rdma_ucm_port_space
cma_select_inet_ps(काष्ठा rdma_id_निजी *id_priv)
अणु
	चयन (id_priv->id.ps) अणु
	हाल RDMA_PS_TCP:
	हाल RDMA_PS_UDP:
	हाल RDMA_PS_IPOIB:
	हाल RDMA_PS_IB:
		वापस id_priv->id.ps;
	शेष:

		वापस 0;
	पूर्ण
पूर्ण

अटल क्रमागत rdma_ucm_port_space
cma_select_ib_ps(काष्ठा rdma_id_निजी *id_priv)
अणु
	क्रमागत rdma_ucm_port_space ps = 0;
	काष्ठा sockaddr_ib *sib;
	u64 sid_ps, mask, sid;

	sib = (काष्ठा sockaddr_ib *) cma_src_addr(id_priv);
	mask = be64_to_cpu(sib->sib_sid_mask) & RDMA_IB_IP_PS_MASK;
	sid = be64_to_cpu(sib->sib_sid) & mask;

	अगर ((id_priv->id.ps == RDMA_PS_IB) && (sid == (RDMA_IB_IP_PS_IB & mask))) अणु
		sid_ps = RDMA_IB_IP_PS_IB;
		ps = RDMA_PS_IB;
	पूर्ण अन्यथा अगर (((id_priv->id.ps == RDMA_PS_IB) || (id_priv->id.ps == RDMA_PS_TCP)) &&
		   (sid == (RDMA_IB_IP_PS_TCP & mask))) अणु
		sid_ps = RDMA_IB_IP_PS_TCP;
		ps = RDMA_PS_TCP;
	पूर्ण अन्यथा अगर (((id_priv->id.ps == RDMA_PS_IB) || (id_priv->id.ps == RDMA_PS_UDP)) &&
		   (sid == (RDMA_IB_IP_PS_UDP & mask))) अणु
		sid_ps = RDMA_IB_IP_PS_UDP;
		ps = RDMA_PS_UDP;
	पूर्ण

	अगर (ps) अणु
		sib->sib_sid = cpu_to_be64(sid_ps | ntohs(cma_port((काष्ठा sockaddr *) sib)));
		sib->sib_sid_mask = cpu_to_be64(RDMA_IB_IP_PS_MASK |
						be64_to_cpu(sib->sib_sid_mask));
	पूर्ण
	वापस ps;
पूर्ण

अटल पूर्णांक cma_get_port(काष्ठा rdma_id_निजी *id_priv)
अणु
	क्रमागत rdma_ucm_port_space ps;
	पूर्णांक ret;

	अगर (cma_family(id_priv) != AF_IB)
		ps = cma_select_inet_ps(id_priv);
	अन्यथा
		ps = cma_select_ib_ps(id_priv);
	अगर (!ps)
		वापस -EPROTONOSUPPORT;

	mutex_lock(&lock);
	अगर (cma_any_port(cma_src_addr(id_priv)))
		ret = cma_alloc_any_port(ps, id_priv);
	अन्यथा
		ret = cma_use_port(ps, id_priv);
	mutex_unlock(&lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cma_check_linklocal(काष्ठा rdma_dev_addr *dev_addr,
			       काष्ठा sockaddr *addr)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा sockaddr_in6 *sin6;

	अगर (addr->sa_family != AF_INET6)
		वापस 0;

	sin6 = (काष्ठा sockaddr_in6 *) addr;

	अगर (!(ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_LINKLOCAL))
		वापस 0;

	अगर (!sin6->sin6_scope_id)
			वापस -EINVAL;

	dev_addr->bound_dev_अगर = sin6->sin6_scope_id;
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक rdma_listen(काष्ठा rdma_cm_id *id, पूर्णांक backlog)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);
	पूर्णांक ret;

	अगर (!cma_comp_exch(id_priv, RDMA_CM_ADDR_BOUND, RDMA_CM_LISTEN)) अणु
		/* For a well behaved ULP state will be RDMA_CM_IDLE */
		id->route.addr.src_addr.ss_family = AF_INET;
		ret = rdma_bind_addr(id, cma_src_addr(id_priv));
		अगर (ret)
			वापस ret;
		अगर (WARN_ON(!cma_comp_exch(id_priv, RDMA_CM_ADDR_BOUND,
					   RDMA_CM_LISTEN)))
			वापस -EINVAL;
	पूर्ण

	/*
	 * Once the ID reaches RDMA_CM_LISTEN it is not allowed to be reusable
	 * any more, and has to be unique in the bind list.
	 */
	अगर (id_priv->reuseaddr) अणु
		mutex_lock(&lock);
		ret = cma_check_port(id_priv->bind_list, id_priv, 0);
		अगर (!ret)
			id_priv->reuseaddr = 0;
		mutex_unlock(&lock);
		अगर (ret)
			जाओ err;
	पूर्ण

	id_priv->backlog = backlog;
	अगर (id_priv->cma_dev) अणु
		अगर (rdma_cap_ib_cm(id->device, 1)) अणु
			ret = cma_ib_listen(id_priv);
			अगर (ret)
				जाओ err;
		पूर्ण अन्यथा अगर (rdma_cap_iw_cm(id->device, 1)) अणु
			ret = cma_iw_listen(id_priv, backlog);
			अगर (ret)
				जाओ err;
		पूर्ण अन्यथा अणु
			ret = -ENOSYS;
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = cma_listen_on_all(id_priv);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	id_priv->backlog = 0;
	/*
	 * All the failure paths that lead here will not allow the req_handler's
	 * to have run.
	 */
	cma_comp_exch(id_priv, RDMA_CM_LISTEN, RDMA_CM_ADDR_BOUND);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_listen);

पूर्णांक rdma_bind_addr(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *addr)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	पूर्णांक ret;
	काष्ठा sockaddr  *daddr;

	अगर (addr->sa_family != AF_INET && addr->sa_family != AF_INET6 &&
	    addr->sa_family != AF_IB)
		वापस -EAFNOSUPPORT;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	अगर (!cma_comp_exch(id_priv, RDMA_CM_IDLE, RDMA_CM_ADDR_BOUND))
		वापस -EINVAL;

	ret = cma_check_linklocal(&id->route.addr.dev_addr, addr);
	अगर (ret)
		जाओ err1;

	स_नकल(cma_src_addr(id_priv), addr, rdma_addr_size(addr));
	अगर (!cma_any_addr(addr)) अणु
		ret = cma_translate_addr(addr, &id->route.addr.dev_addr);
		अगर (ret)
			जाओ err1;

		ret = cma_acquire_dev_by_src_ip(id_priv);
		अगर (ret)
			जाओ err1;
	पूर्ण

	अगर (!(id_priv->options & (1 << CMA_OPTION_AFONLY))) अणु
		अगर (addr->sa_family == AF_INET)
			id_priv->afonly = 1;
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (addr->sa_family == AF_INET6) अणु
			काष्ठा net *net = id_priv->id.route.addr.dev_addr.net;

			id_priv->afonly = net->ipv6.sysctl.bindv6only;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	daddr = cma_dst_addr(id_priv);
	daddr->sa_family = addr->sa_family;

	ret = cma_get_port(id_priv);
	अगर (ret)
		जाओ err2;

	अगर (!cma_any_addr(addr))
		rdma_restrack_add(&id_priv->res);
	वापस 0;
err2:
	अगर (id_priv->cma_dev)
		cma_release_dev(id_priv);
err1:
	cma_comp_exch(id_priv, RDMA_CM_ADDR_BOUND, RDMA_CM_IDLE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_bind_addr);

अटल पूर्णांक cma_क्रमmat_hdr(व्योम *hdr, काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा cma_hdr *cma_hdr;

	cma_hdr = hdr;
	cma_hdr->cma_version = CMA_VERSION;
	अगर (cma_family(id_priv) == AF_INET) अणु
		काष्ठा sockaddr_in *src4, *dst4;

		src4 = (काष्ठा sockaddr_in *) cma_src_addr(id_priv);
		dst4 = (काष्ठा sockaddr_in *) cma_dst_addr(id_priv);

		cma_set_ip_ver(cma_hdr, 4);
		cma_hdr->src_addr.ip4.addr = src4->sin_addr.s_addr;
		cma_hdr->dst_addr.ip4.addr = dst4->sin_addr.s_addr;
		cma_hdr->port = src4->sin_port;
	पूर्ण अन्यथा अगर (cma_family(id_priv) == AF_INET6) अणु
		काष्ठा sockaddr_in6 *src6, *dst6;

		src6 = (काष्ठा sockaddr_in6 *) cma_src_addr(id_priv);
		dst6 = (काष्ठा sockaddr_in6 *) cma_dst_addr(id_priv);

		cma_set_ip_ver(cma_hdr, 6);
		cma_hdr->src_addr.ip6 = src6->sin6_addr;
		cma_hdr->dst_addr.ip6 = dst6->sin6_addr;
		cma_hdr->port = src6->sin6_port;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cma_sidr_rep_handler(काष्ठा ib_cm_id *cm_id,
				स्थिर काष्ठा ib_cm_event *ib_event)
अणु
	काष्ठा rdma_id_निजी *id_priv = cm_id->context;
	काष्ठा rdma_cm_event event = अणुपूर्ण;
	स्थिर काष्ठा ib_cm_sidr_rep_event_param *rep =
				&ib_event->param.sidr_rep_rcvd;
	पूर्णांक ret;

	mutex_lock(&id_priv->handler_mutex);
	अगर (READ_ONCE(id_priv->state) != RDMA_CM_CONNECT)
		जाओ out;

	चयन (ib_event->event) अणु
	हाल IB_CM_SIDR_REQ_ERROR:
		event.event = RDMA_CM_EVENT_UNREACHABLE;
		event.status = -ETIMEDOUT;
		अवरोध;
	हाल IB_CM_SIDR_REP_RECEIVED:
		event.param.ud.निजी_data = ib_event->निजी_data;
		event.param.ud.निजी_data_len = IB_CM_SIDR_REP_PRIVATE_DATA_SIZE;
		अगर (rep->status != IB_SIDR_SUCCESS) अणु
			event.event = RDMA_CM_EVENT_UNREACHABLE;
			event.status = ib_event->param.sidr_rep_rcvd.status;
			pr_debug_ratelimited("RDMA CM: UNREACHABLE: bad SIDR reply. status %d\n",
					     event.status);
			अवरोध;
		पूर्ण
		ret = cma_set_qkey(id_priv, rep->qkey);
		अगर (ret) अणु
			pr_debug_ratelimited("RDMA CM: ADDR_ERROR: failed to set qkey. status %d\n", ret);
			event.event = RDMA_CM_EVENT_ADDR_ERROR;
			event.status = ret;
			अवरोध;
		पूर्ण
		ib_init_ah_attr_from_path(id_priv->id.device,
					  id_priv->id.port_num,
					  id_priv->id.route.path_rec,
					  &event.param.ud.ah_attr,
					  rep->sgid_attr);
		event.param.ud.qp_num = rep->qpn;
		event.param.ud.qkey = rep->qkey;
		event.event = RDMA_CM_EVENT_ESTABLISHED;
		event.status = 0;
		अवरोध;
	शेष:
		pr_err("RDMA CMA: unexpected IB CM event: %d\n",
		       ib_event->event);
		जाओ out;
	पूर्ण

	ret = cma_cm_event_handler(id_priv, &event);

	rdma_destroy_ah_attr(&event.param.ud.ah_attr);
	अगर (ret) अणु
		/* Destroy the CM ID by वापसing a non-zero value. */
		id_priv->cm_id.ib = शून्य;
		destroy_id_handler_unlock(id_priv);
		वापस ret;
	पूर्ण
out:
	mutex_unlock(&id_priv->handler_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक cma_resolve_ib_udp(काष्ठा rdma_id_निजी *id_priv,
			      काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा ib_cm_sidr_req_param req;
	काष्ठा ib_cm_id	*id;
	व्योम *निजी_data;
	u8 offset;
	पूर्णांक ret;

	स_रखो(&req, 0, माप req);
	offset = cma_user_data_offset(id_priv);
	req.निजी_data_len = offset + conn_param->निजी_data_len;
	अगर (req.निजी_data_len < conn_param->निजी_data_len)
		वापस -EINVAL;

	अगर (req.निजी_data_len) अणु
		निजी_data = kzalloc(req.निजी_data_len, GFP_ATOMIC);
		अगर (!निजी_data)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		निजी_data = शून्य;
	पूर्ण

	अगर (conn_param->निजी_data && conn_param->निजी_data_len)
		स_नकल(निजी_data + offset, conn_param->निजी_data,
		       conn_param->निजी_data_len);

	अगर (निजी_data) अणु
		ret = cma_क्रमmat_hdr(निजी_data, id_priv);
		अगर (ret)
			जाओ out;
		req.निजी_data = निजी_data;
	पूर्ण

	id = ib_create_cm_id(id_priv->id.device, cma_sidr_rep_handler,
			     id_priv);
	अगर (IS_ERR(id)) अणु
		ret = PTR_ERR(id);
		जाओ out;
	पूर्ण
	id_priv->cm_id.ib = id;

	req.path = id_priv->id.route.path_rec;
	req.sgid_attr = id_priv->id.route.addr.dev_addr.sgid_attr;
	req.service_id = rdma_get_service_id(&id_priv->id, cma_dst_addr(id_priv));
	req.समयout_ms = 1 << (CMA_CM_RESPONSE_TIMEOUT - 8);
	req.max_cm_retries = CMA_MAX_CM_RETRIES;

	trace_cm_send_sidr_req(id_priv);
	ret = ib_send_cm_sidr_req(id_priv->cm_id.ib, &req);
	अगर (ret) अणु
		ib_destroy_cm_id(id_priv->cm_id.ib);
		id_priv->cm_id.ib = शून्य;
	पूर्ण
out:
	kमुक्त(निजी_data);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_connect_ib(काष्ठा rdma_id_निजी *id_priv,
			  काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा ib_cm_req_param req;
	काष्ठा rdma_route *route;
	व्योम *निजी_data;
	काष्ठा ib_cm_id	*id;
	u8 offset;
	पूर्णांक ret;

	स_रखो(&req, 0, माप req);
	offset = cma_user_data_offset(id_priv);
	req.निजी_data_len = offset + conn_param->निजी_data_len;
	अगर (req.निजी_data_len < conn_param->निजी_data_len)
		वापस -EINVAL;

	अगर (req.निजी_data_len) अणु
		निजी_data = kzalloc(req.निजी_data_len, GFP_ATOMIC);
		अगर (!निजी_data)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		निजी_data = शून्य;
	पूर्ण

	अगर (conn_param->निजी_data && conn_param->निजी_data_len)
		स_नकल(निजी_data + offset, conn_param->निजी_data,
		       conn_param->निजी_data_len);

	id = ib_create_cm_id(id_priv->id.device, cma_ib_handler, id_priv);
	अगर (IS_ERR(id)) अणु
		ret = PTR_ERR(id);
		जाओ out;
	पूर्ण
	id_priv->cm_id.ib = id;

	route = &id_priv->id.route;
	अगर (निजी_data) अणु
		ret = cma_क्रमmat_hdr(निजी_data, id_priv);
		अगर (ret)
			जाओ out;
		req.निजी_data = निजी_data;
	पूर्ण

	req.primary_path = &route->path_rec[0];
	अगर (route->num_paths == 2)
		req.alternate_path = &route->path_rec[1];

	req.ppath_sgid_attr = id_priv->id.route.addr.dev_addr.sgid_attr;
	/* Alternate path SGID attribute currently unsupported */
	req.service_id = rdma_get_service_id(&id_priv->id, cma_dst_addr(id_priv));
	req.qp_num = id_priv->qp_num;
	req.qp_type = id_priv->id.qp_type;
	req.starting_psn = id_priv->seq_num;
	req.responder_resources = conn_param->responder_resources;
	req.initiator_depth = conn_param->initiator_depth;
	req.flow_control = conn_param->flow_control;
	req.retry_count = min_t(u8, 7, conn_param->retry_count);
	req.rnr_retry_count = min_t(u8, 7, conn_param->rnr_retry_count);
	req.remote_cm_response_समयout = CMA_CM_RESPONSE_TIMEOUT;
	req.local_cm_response_समयout = CMA_CM_RESPONSE_TIMEOUT;
	req.max_cm_retries = CMA_MAX_CM_RETRIES;
	req.srq = id_priv->srq ? 1 : 0;
	req.ece.venकरोr_id = id_priv->ece.venकरोr_id;
	req.ece.attr_mod = id_priv->ece.attr_mod;

	trace_cm_send_req(id_priv);
	ret = ib_send_cm_req(id_priv->cm_id.ib, &req);
out:
	अगर (ret && !IS_ERR(id)) अणु
		ib_destroy_cm_id(id);
		id_priv->cm_id.ib = शून्य;
	पूर्ण

	kमुक्त(निजी_data);
	वापस ret;
पूर्ण

अटल पूर्णांक cma_connect_iw(काष्ठा rdma_id_निजी *id_priv,
			  काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा iw_cm_id *cm_id;
	पूर्णांक ret;
	काष्ठा iw_cm_conn_param iw_param;

	cm_id = iw_create_cm_id(id_priv->id.device, cma_iw_handler, id_priv);
	अगर (IS_ERR(cm_id))
		वापस PTR_ERR(cm_id);

	cm_id->tos = id_priv->tos;
	cm_id->tos_set = id_priv->tos_set;
	id_priv->cm_id.iw = cm_id;

	स_नकल(&cm_id->local_addr, cma_src_addr(id_priv),
	       rdma_addr_size(cma_src_addr(id_priv)));
	स_नकल(&cm_id->remote_addr, cma_dst_addr(id_priv),
	       rdma_addr_size(cma_dst_addr(id_priv)));

	ret = cma_modअगरy_qp_rtr(id_priv, conn_param);
	अगर (ret)
		जाओ out;

	अगर (conn_param) अणु
		iw_param.ord = conn_param->initiator_depth;
		iw_param.ird = conn_param->responder_resources;
		iw_param.निजी_data = conn_param->निजी_data;
		iw_param.निजी_data_len = conn_param->निजी_data_len;
		iw_param.qpn = id_priv->id.qp ? id_priv->qp_num : conn_param->qp_num;
	पूर्ण अन्यथा अणु
		स_रखो(&iw_param, 0, माप iw_param);
		iw_param.qpn = id_priv->qp_num;
	पूर्ण
	ret = iw_cm_connect(cm_id, &iw_param);
out:
	अगर (ret) अणु
		iw_destroy_cm_id(cm_id);
		id_priv->cm_id.iw = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * rdma_connect_locked - Initiate an active connection request.
 * @id: Connection identअगरier to connect.
 * @conn_param: Connection inक्रमmation used क्रम connected QPs.
 *
 * Same as rdma_connect() but can only be called from the
 * RDMA_CM_EVENT_ROUTE_RESOLVED handler callback.
 */
पूर्णांक rdma_connect_locked(काष्ठा rdma_cm_id *id,
			काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);
	पूर्णांक ret;

	अगर (!cma_comp_exch(id_priv, RDMA_CM_ROUTE_RESOLVED, RDMA_CM_CONNECT))
		वापस -EINVAL;

	अगर (!id->qp) अणु
		id_priv->qp_num = conn_param->qp_num;
		id_priv->srq = conn_param->srq;
	पूर्ण

	अगर (rdma_cap_ib_cm(id->device, id->port_num)) अणु
		अगर (id->qp_type == IB_QPT_UD)
			ret = cma_resolve_ib_udp(id_priv, conn_param);
		अन्यथा
			ret = cma_connect_ib(id_priv, conn_param);
	पूर्ण अन्यथा अगर (rdma_cap_iw_cm(id->device, id->port_num)) अणु
		ret = cma_connect_iw(id_priv, conn_param);
	पूर्ण अन्यथा अणु
		ret = -ENOSYS;
	पूर्ण
	अगर (ret)
		जाओ err_state;
	वापस 0;
err_state:
	cma_comp_exch(id_priv, RDMA_CM_CONNECT, RDMA_CM_ROUTE_RESOLVED);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_connect_locked);

/**
 * rdma_connect - Initiate an active connection request.
 * @id: Connection identअगरier to connect.
 * @conn_param: Connection inक्रमmation used क्रम connected QPs.
 *
 * Users must have resolved a route क्रम the rdma_cm_id to connect with by having
 * called rdma_resolve_route beक्रमe calling this routine.
 *
 * This call will either connect to a remote QP or obtain remote QP inक्रमmation
 * क्रम unconnected rdma_cm_id's.  The actual operation is based on the
 * rdma_cm_id's port space.
 */
पूर्णांक rdma_connect(काष्ठा rdma_cm_id *id, काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);
	पूर्णांक ret;

	mutex_lock(&id_priv->handler_mutex);
	ret = rdma_connect_locked(id, conn_param);
	mutex_unlock(&id_priv->handler_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_connect);

/**
 * rdma_connect_ece - Initiate an active connection request with ECE data.
 * @id: Connection identअगरier to connect.
 * @conn_param: Connection inक्रमmation used क्रम connected QPs.
 * @ece: ECE parameters
 *
 * See rdma_connect() explanation.
 */
पूर्णांक rdma_connect_ece(काष्ठा rdma_cm_id *id, काष्ठा rdma_conn_param *conn_param,
		     काष्ठा rdma_ucm_ece *ece)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);

	id_priv->ece.venकरोr_id = ece->venकरोr_id;
	id_priv->ece.attr_mod = ece->attr_mod;

	वापस rdma_connect(id, conn_param);
पूर्ण
EXPORT_SYMBOL(rdma_connect_ece);

अटल पूर्णांक cma_accept_ib(काष्ठा rdma_id_निजी *id_priv,
			 काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा ib_cm_rep_param rep;
	पूर्णांक ret;

	ret = cma_modअगरy_qp_rtr(id_priv, conn_param);
	अगर (ret)
		जाओ out;

	ret = cma_modअगरy_qp_rts(id_priv, conn_param);
	अगर (ret)
		जाओ out;

	स_रखो(&rep, 0, माप rep);
	rep.qp_num = id_priv->qp_num;
	rep.starting_psn = id_priv->seq_num;
	rep.निजी_data = conn_param->निजी_data;
	rep.निजी_data_len = conn_param->निजी_data_len;
	rep.responder_resources = conn_param->responder_resources;
	rep.initiator_depth = conn_param->initiator_depth;
	rep.failover_accepted = 0;
	rep.flow_control = conn_param->flow_control;
	rep.rnr_retry_count = min_t(u8, 7, conn_param->rnr_retry_count);
	rep.srq = id_priv->srq ? 1 : 0;
	rep.ece.venकरोr_id = id_priv->ece.venकरोr_id;
	rep.ece.attr_mod = id_priv->ece.attr_mod;

	trace_cm_send_rep(id_priv);
	ret = ib_send_cm_rep(id_priv->cm_id.ib, &rep);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक cma_accept_iw(काष्ठा rdma_id_निजी *id_priv,
		  काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा iw_cm_conn_param iw_param;
	पूर्णांक ret;

	अगर (!conn_param)
		वापस -EINVAL;

	ret = cma_modअगरy_qp_rtr(id_priv, conn_param);
	अगर (ret)
		वापस ret;

	iw_param.ord = conn_param->initiator_depth;
	iw_param.ird = conn_param->responder_resources;
	iw_param.निजी_data = conn_param->निजी_data;
	iw_param.निजी_data_len = conn_param->निजी_data_len;
	अगर (id_priv->id.qp)
		iw_param.qpn = id_priv->qp_num;
	अन्यथा
		iw_param.qpn = conn_param->qp_num;

	वापस iw_cm_accept(id_priv->cm_id.iw, &iw_param);
पूर्ण

अटल पूर्णांक cma_send_sidr_rep(काष्ठा rdma_id_निजी *id_priv,
			     क्रमागत ib_cm_sidr_status status, u32 qkey,
			     स्थिर व्योम *निजी_data, पूर्णांक निजी_data_len)
अणु
	काष्ठा ib_cm_sidr_rep_param rep;
	पूर्णांक ret;

	स_रखो(&rep, 0, माप rep);
	rep.status = status;
	अगर (status == IB_SIDR_SUCCESS) अणु
		ret = cma_set_qkey(id_priv, qkey);
		अगर (ret)
			वापस ret;
		rep.qp_num = id_priv->qp_num;
		rep.qkey = id_priv->qkey;

		rep.ece.venकरोr_id = id_priv->ece.venकरोr_id;
		rep.ece.attr_mod = id_priv->ece.attr_mod;
	पूर्ण

	rep.निजी_data = निजी_data;
	rep.निजी_data_len = निजी_data_len;

	trace_cm_send_sidr_rep(id_priv);
	वापस ib_send_cm_sidr_rep(id_priv->cm_id.ib, &rep);
पूर्ण

/**
 * rdma_accept - Called to accept a connection request or response.
 * @id: Connection identअगरier associated with the request.
 * @conn_param: Inक्रमmation needed to establish the connection.  This must be
 *   provided अगर accepting a connection request.  If accepting a connection
 *   response, this parameter must be शून्य.
 *
 * Typically, this routine is only called by the listener to accept a connection
 * request.  It must also be called on the active side of a connection अगर the
 * user is perक्रमming their own QP transitions.
 *
 * In the हाल of error, a reject message is sent to the remote side and the
 * state of the qp associated with the id is modअगरied to error, such that any
 * previously posted receive buffers would be flushed.
 *
 * This function is क्रम use by kernel ULPs and must be called from under the
 * handler callback.
 */
पूर्णांक rdma_accept(काष्ठा rdma_cm_id *id, काष्ठा rdma_conn_param *conn_param)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);
	पूर्णांक ret;

	lockdep_निश्चित_held(&id_priv->handler_mutex);

	अगर (READ_ONCE(id_priv->state) != RDMA_CM_CONNECT)
		वापस -EINVAL;

	अगर (!id->qp && conn_param) अणु
		id_priv->qp_num = conn_param->qp_num;
		id_priv->srq = conn_param->srq;
	पूर्ण

	अगर (rdma_cap_ib_cm(id->device, id->port_num)) अणु
		अगर (id->qp_type == IB_QPT_UD) अणु
			अगर (conn_param)
				ret = cma_send_sidr_rep(id_priv, IB_SIDR_SUCCESS,
							conn_param->qkey,
							conn_param->निजी_data,
							conn_param->निजी_data_len);
			अन्यथा
				ret = cma_send_sidr_rep(id_priv, IB_SIDR_SUCCESS,
							0, शून्य, 0);
		पूर्ण अन्यथा अणु
			अगर (conn_param)
				ret = cma_accept_ib(id_priv, conn_param);
			अन्यथा
				ret = cma_rep_recv(id_priv);
		पूर्ण
	पूर्ण अन्यथा अगर (rdma_cap_iw_cm(id->device, id->port_num)) अणु
		ret = cma_accept_iw(id_priv, conn_param);
	पूर्ण अन्यथा अणु
		ret = -ENOSYS;
	पूर्ण
	अगर (ret)
		जाओ reject;

	वापस 0;
reject:
	cma_modअगरy_qp_err(id_priv);
	rdma_reject(id, शून्य, 0, IB_CM_REJ_CONSUMER_DEFINED);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_accept);

पूर्णांक rdma_accept_ece(काष्ठा rdma_cm_id *id, काष्ठा rdma_conn_param *conn_param,
		    काष्ठा rdma_ucm_ece *ece)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);

	id_priv->ece.venकरोr_id = ece->venकरोr_id;
	id_priv->ece.attr_mod = ece->attr_mod;

	वापस rdma_accept(id, conn_param);
पूर्ण
EXPORT_SYMBOL(rdma_accept_ece);

व्योम rdma_lock_handler(काष्ठा rdma_cm_id *id)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);

	mutex_lock(&id_priv->handler_mutex);
पूर्ण
EXPORT_SYMBOL(rdma_lock_handler);

व्योम rdma_unlock_handler(काष्ठा rdma_cm_id *id)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);

	mutex_unlock(&id_priv->handler_mutex);
पूर्ण
EXPORT_SYMBOL(rdma_unlock_handler);

पूर्णांक rdma_notअगरy(काष्ठा rdma_cm_id *id, क्रमागत ib_event_type event)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	पूर्णांक ret;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	अगर (!id_priv->cm_id.ib)
		वापस -EINVAL;

	चयन (id->device->node_type) अणु
	हाल RDMA_NODE_IB_CA:
		ret = ib_cm_notअगरy(id_priv->cm_id.ib, event);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_notअगरy);

पूर्णांक rdma_reject(काष्ठा rdma_cm_id *id, स्थिर व्योम *निजी_data,
		u8 निजी_data_len, u8 reason)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	पूर्णांक ret;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	अगर (!id_priv->cm_id.ib)
		वापस -EINVAL;

	अगर (rdma_cap_ib_cm(id->device, id->port_num)) अणु
		अगर (id->qp_type == IB_QPT_UD) अणु
			ret = cma_send_sidr_rep(id_priv, IB_SIDR_REJECT, 0,
						निजी_data, निजी_data_len);
		पूर्ण अन्यथा अणु
			trace_cm_send_rej(id_priv);
			ret = ib_send_cm_rej(id_priv->cm_id.ib, reason, शून्य, 0,
					     निजी_data, निजी_data_len);
		पूर्ण
	पूर्ण अन्यथा अगर (rdma_cap_iw_cm(id->device, id->port_num)) अणु
		ret = iw_cm_reject(id_priv->cm_id.iw,
				   निजी_data, निजी_data_len);
	पूर्ण अन्यथा अणु
		ret = -ENOSYS;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_reject);

पूर्णांक rdma_disconnect(काष्ठा rdma_cm_id *id)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	पूर्णांक ret;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	अगर (!id_priv->cm_id.ib)
		वापस -EINVAL;

	अगर (rdma_cap_ib_cm(id->device, id->port_num)) अणु
		ret = cma_modअगरy_qp_err(id_priv);
		अगर (ret)
			जाओ out;
		/* Initiate or respond to a disconnect. */
		trace_cm_disconnect(id_priv);
		अगर (ib_send_cm_dreq(id_priv->cm_id.ib, शून्य, 0)) अणु
			अगर (!ib_send_cm_drep(id_priv->cm_id.ib, शून्य, 0))
				trace_cm_sent_drep(id_priv);
		पूर्ण अन्यथा अणु
			trace_cm_sent_dreq(id_priv);
		पूर्ण
	पूर्ण अन्यथा अगर (rdma_cap_iw_cm(id->device, id->port_num)) अणु
		ret = iw_cm_disconnect(id_priv->cm_id.iw, 0);
	पूर्ण अन्यथा
		ret = -EINVAL;

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_disconnect);

अटल व्योम cma_make_mc_event(पूर्णांक status, काष्ठा rdma_id_निजी *id_priv,
			      काष्ठा ib_sa_multicast *multicast,
			      काष्ठा rdma_cm_event *event,
			      काष्ठा cma_multicast *mc)
अणु
	काष्ठा rdma_dev_addr *dev_addr;
	क्रमागत ib_gid_type gid_type;
	काष्ठा net_device *ndev;

	अगर (!status)
		status = cma_set_qkey(id_priv, be32_to_cpu(multicast->rec.qkey));
	अन्यथा
		pr_debug_ratelimited("RDMA CM: MULTICAST_ERROR: failed to join multicast. status %d\n",
				     status);

	event->status = status;
	event->param.ud.निजी_data = mc->context;
	अगर (status) अणु
		event->event = RDMA_CM_EVENT_MULTICAST_ERROR;
		वापस;
	पूर्ण

	dev_addr = &id_priv->id.route.addr.dev_addr;
	ndev = dev_get_by_index(dev_addr->net, dev_addr->bound_dev_अगर);
	gid_type =
		id_priv->cma_dev
			->शेष_gid_type[id_priv->id.port_num -
					   rdma_start_port(
						   id_priv->cma_dev->device)];

	event->event = RDMA_CM_EVENT_MULTICAST_JOIN;
	अगर (ib_init_ah_from_mcmember(id_priv->id.device, id_priv->id.port_num,
				     &multicast->rec, ndev, gid_type,
				     &event->param.ud.ah_attr)) अणु
		event->event = RDMA_CM_EVENT_MULTICAST_ERROR;
		जाओ out;
	पूर्ण

	event->param.ud.qp_num = 0xFFFFFF;
	event->param.ud.qkey = be32_to_cpu(multicast->rec.qkey);

out:
	अगर (ndev)
		dev_put(ndev);
पूर्ण

अटल पूर्णांक cma_ib_mc_handler(पूर्णांक status, काष्ठा ib_sa_multicast *multicast)
अणु
	काष्ठा cma_multicast *mc = multicast->context;
	काष्ठा rdma_id_निजी *id_priv = mc->id_priv;
	काष्ठा rdma_cm_event event = अणुपूर्ण;
	पूर्णांक ret = 0;

	mutex_lock(&id_priv->handler_mutex);
	अगर (READ_ONCE(id_priv->state) == RDMA_CM_DEVICE_REMOVAL ||
	    READ_ONCE(id_priv->state) == RDMA_CM_DESTROYING)
		जाओ out;

	cma_make_mc_event(status, id_priv, multicast, &event, mc);
	ret = cma_cm_event_handler(id_priv, &event);
	rdma_destroy_ah_attr(&event.param.ud.ah_attr);
	WARN_ON(ret);

out:
	mutex_unlock(&id_priv->handler_mutex);
	वापस 0;
पूर्ण

अटल व्योम cma_set_mgid(काष्ठा rdma_id_निजी *id_priv,
			 काष्ठा sockaddr *addr, जोड़ ib_gid *mgid)
अणु
	अचिन्हित अक्षर mc_map[MAX_ADDR_LEN];
	काष्ठा rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *) addr;
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *) addr;

	अगर (cma_any_addr(addr)) अणु
		स_रखो(mgid, 0, माप *mgid);
	पूर्ण अन्यथा अगर ((addr->sa_family == AF_INET6) &&
		   ((be32_to_cpu(sin6->sin6_addr.s6_addr32[0]) & 0xFFF0FFFF) ==
								 0xFF10A01B)) अणु
		/* IPv6 address is an SA asचिन्हित MGID. */
		स_नकल(mgid, &sin6->sin6_addr, माप *mgid);
	पूर्ण अन्यथा अगर (addr->sa_family == AF_IB) अणु
		स_नकल(mgid, &((काष्ठा sockaddr_ib *) addr)->sib_addr, माप *mgid);
	पूर्ण अन्यथा अगर (addr->sa_family == AF_INET6) अणु
		ipv6_ib_mc_map(&sin6->sin6_addr, dev_addr->broadcast, mc_map);
		अगर (id_priv->id.ps == RDMA_PS_UDP)
			mc_map[7] = 0x01;	/* Use RDMA CM signature */
		*mgid = *(जोड़ ib_gid *) (mc_map + 4);
	पूर्ण अन्यथा अणु
		ip_ib_mc_map(sin->sin_addr.s_addr, dev_addr->broadcast, mc_map);
		अगर (id_priv->id.ps == RDMA_PS_UDP)
			mc_map[7] = 0x01;	/* Use RDMA CM signature */
		*mgid = *(जोड़ ib_gid *) (mc_map + 4);
	पूर्ण
पूर्ण

अटल पूर्णांक cma_join_ib_multicast(काष्ठा rdma_id_निजी *id_priv,
				 काष्ठा cma_multicast *mc)
अणु
	काष्ठा ib_sa_mcmember_rec rec;
	काष्ठा rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	ib_sa_comp_mask comp_mask;
	पूर्णांक ret;

	ib_addr_get_mgid(dev_addr, &rec.mgid);
	ret = ib_sa_get_mcmember_rec(id_priv->id.device, id_priv->id.port_num,
				     &rec.mgid, &rec);
	अगर (ret)
		वापस ret;

	ret = cma_set_qkey(id_priv, 0);
	अगर (ret)
		वापस ret;

	cma_set_mgid(id_priv, (काष्ठा sockaddr *) &mc->addr, &rec.mgid);
	rec.qkey = cpu_to_be32(id_priv->qkey);
	rdma_addr_get_sgid(dev_addr, &rec.port_gid);
	rec.pkey = cpu_to_be16(ib_addr_get_pkey(dev_addr));
	rec.join_state = mc->join_state;

	comp_mask = IB_SA_MCMEMBER_REC_MGID | IB_SA_MCMEMBER_REC_PORT_GID |
		    IB_SA_MCMEMBER_REC_PKEY | IB_SA_MCMEMBER_REC_JOIN_STATE |
		    IB_SA_MCMEMBER_REC_QKEY | IB_SA_MCMEMBER_REC_SL |
		    IB_SA_MCMEMBER_REC_FLOW_LABEL |
		    IB_SA_MCMEMBER_REC_TRAFFIC_CLASS;

	अगर (id_priv->id.ps == RDMA_PS_IPOIB)
		comp_mask |= IB_SA_MCMEMBER_REC_RATE |
			     IB_SA_MCMEMBER_REC_RATE_SELECTOR |
			     IB_SA_MCMEMBER_REC_MTU_SELECTOR |
			     IB_SA_MCMEMBER_REC_MTU |
			     IB_SA_MCMEMBER_REC_HOP_LIMIT;

	mc->sa_mc = ib_sa_join_multicast(&sa_client, id_priv->id.device,
					 id_priv->id.port_num, &rec, comp_mask,
					 GFP_KERNEL, cma_ib_mc_handler, mc);
	वापस PTR_ERR_OR_ZERO(mc->sa_mc);
पूर्ण

अटल व्योम cma_iboe_set_mgid(काष्ठा sockaddr *addr, जोड़ ib_gid *mgid,
			      क्रमागत ib_gid_type gid_type)
अणु
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)addr;
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)addr;

	अगर (cma_any_addr(addr)) अणु
		स_रखो(mgid, 0, माप *mgid);
	पूर्ण अन्यथा अगर (addr->sa_family == AF_INET6) अणु
		स_नकल(mgid, &sin6->sin6_addr, माप *mgid);
	पूर्ण अन्यथा अणु
		mgid->raw[0] =
			(gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) ? 0 : 0xff;
		mgid->raw[1] =
			(gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) ? 0 : 0x0e;
		mgid->raw[2] = 0;
		mgid->raw[3] = 0;
		mgid->raw[4] = 0;
		mgid->raw[5] = 0;
		mgid->raw[6] = 0;
		mgid->raw[7] = 0;
		mgid->raw[8] = 0;
		mgid->raw[9] = 0;
		mgid->raw[10] = 0xff;
		mgid->raw[11] = 0xff;
		*(__be32 *)(&mgid->raw[12]) = sin->sin_addr.s_addr;
	पूर्ण
पूर्ण

अटल पूर्णांक cma_iboe_join_multicast(काष्ठा rdma_id_निजी *id_priv,
				   काष्ठा cma_multicast *mc)
अणु
	काष्ठा rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	पूर्णांक err = 0;
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *)&mc->addr;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा ib_sa_multicast ib;
	क्रमागत ib_gid_type gid_type;
	bool send_only;

	send_only = mc->join_state == BIT(SENDONLY_FULLMEMBER_JOIN);

	अगर (cma_zero_addr(addr))
		वापस -EINVAL;

	gid_type = id_priv->cma_dev->शेष_gid_type[id_priv->id.port_num -
		   rdma_start_port(id_priv->cma_dev->device)];
	cma_iboe_set_mgid(addr, &ib.rec.mgid, gid_type);

	ib.rec.pkey = cpu_to_be16(0xffff);
	अगर (id_priv->id.ps == RDMA_PS_UDP)
		ib.rec.qkey = cpu_to_be32(RDMA_UDP_QKEY);

	अगर (dev_addr->bound_dev_अगर)
		ndev = dev_get_by_index(dev_addr->net, dev_addr->bound_dev_अगर);
	अगर (!ndev)
		वापस -ENODEV;

	ib.rec.rate = iboe_get_rate(ndev);
	ib.rec.hop_limit = 1;
	ib.rec.mtu = iboe_get_mtu(ndev->mtu);

	अगर (addr->sa_family == AF_INET) अणु
		अगर (gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) अणु
			ib.rec.hop_limit = IPV6_DEFAULT_HOPLIMIT;
			अगर (!send_only) अणु
				err = cma_igmp_send(ndev, &ib.rec.mgid,
						    true);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP)
			err = -ENOTSUPP;
	पूर्ण
	dev_put(ndev);
	अगर (err || !ib.rec.mtu)
		वापस err ?: -EINVAL;

	rdma_ip2gid((काष्ठा sockaddr *)&id_priv->id.route.addr.src_addr,
		    &ib.rec.port_gid);
	INIT_WORK(&mc->iboe_join.work, cma_iboe_join_work_handler);
	cma_make_mc_event(0, id_priv, &ib, &mc->iboe_join.event, mc);
	queue_work(cma_wq, &mc->iboe_join.work);
	वापस 0;
पूर्ण

पूर्णांक rdma_join_multicast(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *addr,
			u8 join_state, व्योम *context)
अणु
	काष्ठा rdma_id_निजी *id_priv =
		container_of(id, काष्ठा rdma_id_निजी, id);
	काष्ठा cma_multicast *mc;
	पूर्णांक ret;

	/* Not supported क्रम kernel QPs */
	अगर (WARN_ON(id->qp))
		वापस -EINVAL;

	/* ULP is calling this wrong. */
	अगर (!id->device || (READ_ONCE(id_priv->state) != RDMA_CM_ADDR_BOUND &&
			    READ_ONCE(id_priv->state) != RDMA_CM_ADDR_RESOLVED))
		वापस -EINVAL;

	mc = kzalloc(माप(*mc), GFP_KERNEL);
	अगर (!mc)
		वापस -ENOMEM;

	स_नकल(&mc->addr, addr, rdma_addr_size(addr));
	mc->context = context;
	mc->id_priv = id_priv;
	mc->join_state = join_state;

	अगर (rdma_protocol_roce(id->device, id->port_num)) अणु
		ret = cma_iboe_join_multicast(id_priv, mc);
		अगर (ret)
			जाओ out_err;
	पूर्ण अन्यथा अगर (rdma_cap_ib_mcast(id->device, id->port_num)) अणु
		ret = cma_join_ib_multicast(id_priv, mc);
		अगर (ret)
			जाओ out_err;
	पूर्ण अन्यथा अणु
		ret = -ENOSYS;
		जाओ out_err;
	पूर्ण

	spin_lock(&id_priv->lock);
	list_add(&mc->list, &id_priv->mc_list);
	spin_unlock(&id_priv->lock);

	वापस 0;
out_err:
	kमुक्त(mc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_join_multicast);

व्योम rdma_leave_multicast(काष्ठा rdma_cm_id *id, काष्ठा sockaddr *addr)
अणु
	काष्ठा rdma_id_निजी *id_priv;
	काष्ठा cma_multicast *mc;

	id_priv = container_of(id, काष्ठा rdma_id_निजी, id);
	spin_lock_irq(&id_priv->lock);
	list_क्रम_each_entry(mc, &id_priv->mc_list, list) अणु
		अगर (स_भेद(&mc->addr, addr, rdma_addr_size(addr)) != 0)
			जारी;
		list_del(&mc->list);
		spin_unlock_irq(&id_priv->lock);

		WARN_ON(id_priv->cma_dev->device != id->device);
		destroy_mc(id_priv, mc);
		वापस;
	पूर्ण
	spin_unlock_irq(&id_priv->lock);
पूर्ण
EXPORT_SYMBOL(rdma_leave_multicast);

अटल पूर्णांक cma_netdev_change(काष्ठा net_device *ndev, काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_dev_addr *dev_addr;
	काष्ठा cma_work *work;

	dev_addr = &id_priv->id.route.addr.dev_addr;

	अगर ((dev_addr->bound_dev_अगर == ndev->अगरindex) &&
	    (net_eq(dev_net(ndev), dev_addr->net)) &&
	    स_भेद(dev_addr->src_dev_addr, ndev->dev_addr, ndev->addr_len)) अणु
		pr_info("RDMA CM addr change for ndev %s used by id %p\n",
			ndev->name, &id_priv->id);
		work = kzalloc(माप *work, GFP_KERNEL);
		अगर (!work)
			वापस -ENOMEM;

		INIT_WORK(&work->work, cma_work_handler);
		work->id = id_priv;
		work->event.event = RDMA_CM_EVENT_ADDR_CHANGE;
		cma_id_get(id_priv);
		queue_work(cma_wq, &work->work);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cma_netdev_callback(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ event,
			       व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा cma_device *cma_dev;
	काष्ठा rdma_id_निजी *id_priv;
	पूर्णांक ret = NOTIFY_DONE;

	अगर (event != NETDEV_BONDING_FAILOVER)
		वापस NOTIFY_DONE;

	अगर (!netअगर_is_bond_master(ndev))
		वापस NOTIFY_DONE;

	mutex_lock(&lock);
	list_क्रम_each_entry(cma_dev, &dev_list, list)
		list_क्रम_each_entry(id_priv, &cma_dev->id_list, list) अणु
			ret = cma_netdev_change(ndev, id_priv);
			अगर (ret)
				जाओ out;
		पूर्ण

out:
	mutex_unlock(&lock);
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block cma_nb = अणु
	.notअगरier_call = cma_netdev_callback
पूर्ण;

अटल व्योम cma_send_device_removal_put(काष्ठा rdma_id_निजी *id_priv)
अणु
	काष्ठा rdma_cm_event event = अणु .event = RDMA_CM_EVENT_DEVICE_REMOVAL पूर्ण;
	क्रमागत rdma_cm_state state;
	अचिन्हित दीर्घ flags;

	mutex_lock(&id_priv->handler_mutex);
	/* Record that we want to हटाओ the device */
	spin_lock_irqsave(&id_priv->lock, flags);
	state = id_priv->state;
	अगर (state == RDMA_CM_DESTROYING || state == RDMA_CM_DEVICE_REMOVAL) अणु
		spin_unlock_irqrestore(&id_priv->lock, flags);
		mutex_unlock(&id_priv->handler_mutex);
		cma_id_put(id_priv);
		वापस;
	पूर्ण
	id_priv->state = RDMA_CM_DEVICE_REMOVAL;
	spin_unlock_irqrestore(&id_priv->lock, flags);

	अगर (cma_cm_event_handler(id_priv, &event)) अणु
		/*
		 * At this poपूर्णांक the ULP promises it won't call
		 * rdma_destroy_id() concurrently
		 */
		cma_id_put(id_priv);
		mutex_unlock(&id_priv->handler_mutex);
		trace_cm_id_destroy(id_priv);
		_destroy_id(id_priv, state);
		वापस;
	पूर्ण
	mutex_unlock(&id_priv->handler_mutex);

	/*
	 * If this races with destroy then the thपढ़ो that first assigns state
	 * to a destroying करोes the cancel.
	 */
	cma_cancel_operation(id_priv, state);
	cma_id_put(id_priv);
पूर्ण

अटल व्योम cma_process_हटाओ(काष्ठा cma_device *cma_dev)
अणु
	mutex_lock(&lock);
	जबतक (!list_empty(&cma_dev->id_list)) अणु
		काष्ठा rdma_id_निजी *id_priv = list_first_entry(
			&cma_dev->id_list, काष्ठा rdma_id_निजी, list);

		list_del(&id_priv->listen_list);
		list_del_init(&id_priv->list);
		cma_id_get(id_priv);
		mutex_unlock(&lock);

		cma_send_device_removal_put(id_priv);

		mutex_lock(&lock);
	पूर्ण
	mutex_unlock(&lock);

	cma_dev_put(cma_dev);
	रुको_क्रम_completion(&cma_dev->comp);
पूर्ण

अटल bool cma_supported(काष्ठा ib_device *device)
अणु
	u32 i;

	rdma_क्रम_each_port(device, i) अणु
		अगर (rdma_cap_ib_cm(device, i) || rdma_cap_iw_cm(device, i))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक cma_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा rdma_id_निजी *to_destroy;
	काष्ठा cma_device *cma_dev;
	काष्ठा rdma_id_निजी *id_priv;
	अचिन्हित दीर्घ supported_gids = 0;
	पूर्णांक ret;
	u32 i;

	अगर (!cma_supported(device))
		वापस -EOPNOTSUPP;

	cma_dev = kदो_स्मृति(माप(*cma_dev), GFP_KERNEL);
	अगर (!cma_dev)
		वापस -ENOMEM;

	cma_dev->device = device;
	cma_dev->शेष_gid_type = kसुस्मृति(device->phys_port_cnt,
					    माप(*cma_dev->शेष_gid_type),
					    GFP_KERNEL);
	अगर (!cma_dev->शेष_gid_type) अणु
		ret = -ENOMEM;
		जाओ मुक्त_cma_dev;
	पूर्ण

	cma_dev->शेष_roce_tos = kसुस्मृति(device->phys_port_cnt,
					    माप(*cma_dev->शेष_roce_tos),
					    GFP_KERNEL);
	अगर (!cma_dev->शेष_roce_tos) अणु
		ret = -ENOMEM;
		जाओ मुक्त_gid_type;
	पूर्ण

	rdma_क्रम_each_port (device, i) अणु
		supported_gids = roce_gid_type_mask_support(device, i);
		WARN_ON(!supported_gids);
		अगर (supported_gids & (1 << CMA_PREFERRED_ROCE_GID_TYPE))
			cma_dev->शेष_gid_type[i - rdma_start_port(device)] =
				CMA_PREFERRED_ROCE_GID_TYPE;
		अन्यथा
			cma_dev->शेष_gid_type[i - rdma_start_port(device)] =
				find_first_bit(&supported_gids, BITS_PER_LONG);
		cma_dev->शेष_roce_tos[i - rdma_start_port(device)] = 0;
	पूर्ण

	init_completion(&cma_dev->comp);
	refcount_set(&cma_dev->refcount, 1);
	INIT_LIST_HEAD(&cma_dev->id_list);
	ib_set_client_data(device, &cma_client, cma_dev);

	mutex_lock(&lock);
	list_add_tail(&cma_dev->list, &dev_list);
	list_क्रम_each_entry(id_priv, &listen_any_list, list) अणु
		ret = cma_listen_on_dev(id_priv, cma_dev, &to_destroy);
		अगर (ret)
			जाओ मुक्त_listen;
	पूर्ण
	mutex_unlock(&lock);

	trace_cm_add_one(device);
	वापस 0;

मुक्त_listen:
	list_del(&cma_dev->list);
	mutex_unlock(&lock);

	/* cma_process_हटाओ() will delete to_destroy */
	cma_process_हटाओ(cma_dev);
	kमुक्त(cma_dev->शेष_roce_tos);
मुक्त_gid_type:
	kमुक्त(cma_dev->शेष_gid_type);

मुक्त_cma_dev:
	kमुक्त(cma_dev);
	वापस ret;
पूर्ण

अटल व्योम cma_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा cma_device *cma_dev = client_data;

	trace_cm_हटाओ_one(device);

	mutex_lock(&lock);
	list_del(&cma_dev->list);
	mutex_unlock(&lock);

	cma_process_हटाओ(cma_dev);
	kमुक्त(cma_dev->शेष_roce_tos);
	kमुक्त(cma_dev->शेष_gid_type);
	kमुक्त(cma_dev);
पूर्ण

अटल पूर्णांक cma_init_net(काष्ठा net *net)
अणु
	काष्ठा cma_pernet *pernet = cma_pernet(net);

	xa_init(&pernet->tcp_ps);
	xa_init(&pernet->udp_ps);
	xa_init(&pernet->ipoib_ps);
	xa_init(&pernet->ib_ps);

	वापस 0;
पूर्ण

अटल व्योम cma_निकास_net(काष्ठा net *net)
अणु
	काष्ठा cma_pernet *pernet = cma_pernet(net);

	WARN_ON(!xa_empty(&pernet->tcp_ps));
	WARN_ON(!xa_empty(&pernet->udp_ps));
	WARN_ON(!xa_empty(&pernet->ipoib_ps));
	WARN_ON(!xa_empty(&pernet->ib_ps));
पूर्ण

अटल काष्ठा pernet_operations cma_pernet_operations = अणु
	.init = cma_init_net,
	.निकास = cma_निकास_net,
	.id = &cma_pernet_id,
	.size = माप(काष्ठा cma_pernet),
पूर्ण;

अटल पूर्णांक __init cma_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * There is a rare lock ordering dependency in cma_netdev_callback()
	 * that only happens when bonding is enabled. Teach lockdep that rtnl
	 * must never be nested under lock so it can find these without having
	 * to test with bonding.
	 */
	अगर (IS_ENABLED(CONFIG_LOCKDEP)) अणु
		rtnl_lock();
		mutex_lock(&lock);
		mutex_unlock(&lock);
		rtnl_unlock();
	पूर्ण

	cma_wq = alloc_ordered_workqueue("rdma_cm", WQ_MEM_RECLAIM);
	अगर (!cma_wq)
		वापस -ENOMEM;

	ret = रेजिस्टर_pernet_subsys(&cma_pernet_operations);
	अगर (ret)
		जाओ err_wq;

	ib_sa_रेजिस्टर_client(&sa_client);
	रेजिस्टर_netdevice_notअगरier(&cma_nb);

	ret = ib_रेजिस्टर_client(&cma_client);
	अगर (ret)
		जाओ err;

	ret = cma_configfs_init();
	अगर (ret)
		जाओ err_ib;

	वापस 0;

err_ib:
	ib_unरेजिस्टर_client(&cma_client);
err:
	unरेजिस्टर_netdevice_notअगरier(&cma_nb);
	ib_sa_unरेजिस्टर_client(&sa_client);
	unरेजिस्टर_pernet_subsys(&cma_pernet_operations);
err_wq:
	destroy_workqueue(cma_wq);
	वापस ret;
पूर्ण

अटल व्योम __निकास cma_cleanup(व्योम)
अणु
	cma_configfs_निकास();
	ib_unरेजिस्टर_client(&cma_client);
	unरेजिस्टर_netdevice_notअगरier(&cma_nb);
	ib_sa_unरेजिस्टर_client(&sa_client);
	unरेजिस्टर_pernet_subsys(&cma_pernet_operations);
	destroy_workqueue(cma_wq);
पूर्ण

module_init(cma_init);
module_निकास(cma_cleanup);
