<शैली गुरु>
/*
 * Copyright (c) 2006, 2019 Oracle and/or its affiliates. All rights reserved.
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
#समावेश <linux/kernel.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <net/addrconf.h>

#समावेश "rds_single_path.h"
#समावेश "rds.h"
#समावेश "ib.h"
#समावेश "ib_mr.h"

अटल अचिन्हित पूर्णांक rds_ib_mr_1m_pool_size = RDS_MR_1M_POOL_SIZE;
अटल अचिन्हित पूर्णांक rds_ib_mr_8k_pool_size = RDS_MR_8K_POOL_SIZE;
अचिन्हित पूर्णांक rds_ib_retry_count = RDS_IB_DEFAULT_RETRY_COUNT;
अटल atomic_t rds_ib_unloading;

module_param(rds_ib_mr_1m_pool_size, पूर्णांक, 0444);
MODULE_PARM_DESC(rds_ib_mr_1m_pool_size, " Max number of 1M mr per HCA");
module_param(rds_ib_mr_8k_pool_size, पूर्णांक, 0444);
MODULE_PARM_DESC(rds_ib_mr_8k_pool_size, " Max number of 8K mr per HCA");
module_param(rds_ib_retry_count, पूर्णांक, 0444);
MODULE_PARM_DESC(rds_ib_retry_count, " Number of hw retries before reporting an error");

/*
 * we have a clumsy combination of RCU and a rwsem protecting this list
 * because it is used both in the get_mr fast path and जबतक blocking in
 * the FMR flushing path.
 */
DECLARE_RWSEM(rds_ib_devices_lock);
काष्ठा list_head rds_ib_devices;

/* NOTE: अगर also grabbing ibdev lock, grab this first */
DEFINE_SPINLOCK(ib_nodev_conns_lock);
LIST_HEAD(ib_nodev_conns);

अटल व्योम rds_ib_nodev_connect(व्योम)
अणु
	काष्ठा rds_ib_connection *ic;

	spin_lock(&ib_nodev_conns_lock);
	list_क्रम_each_entry(ic, &ib_nodev_conns, ib_node)
		rds_conn_connect_अगर_करोwn(ic->conn);
	spin_unlock(&ib_nodev_conns_lock);
पूर्ण

अटल व्योम rds_ib_dev_shutकरोwn(काष्ठा rds_ib_device *rds_ibdev)
अणु
	काष्ठा rds_ib_connection *ic;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rds_ibdev->spinlock, flags);
	list_क्रम_each_entry(ic, &rds_ibdev->conn_list, ib_node)
		rds_conn_path_drop(&ic->conn->c_path[0], true);
	spin_unlock_irqrestore(&rds_ibdev->spinlock, flags);
पूर्ण

/*
 * rds_ib_destroy_mr_pool() blocks on a few things and mrs drop references
 * from पूर्णांकerrupt context so we push freing off पूर्णांकo a work काष्ठा in krdsd.
 */
अटल व्योम rds_ib_dev_मुक्त(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rds_ib_ipaddr *i_ipaddr, *i_next;
	काष्ठा rds_ib_device *rds_ibdev = container_of(work,
					काष्ठा rds_ib_device, मुक्त_work);

	अगर (rds_ibdev->mr_8k_pool)
		rds_ib_destroy_mr_pool(rds_ibdev->mr_8k_pool);
	अगर (rds_ibdev->mr_1m_pool)
		rds_ib_destroy_mr_pool(rds_ibdev->mr_1m_pool);
	अगर (rds_ibdev->pd)
		ib_dealloc_pd(rds_ibdev->pd);

	list_क्रम_each_entry_safe(i_ipaddr, i_next, &rds_ibdev->ipaddr_list, list) अणु
		list_del(&i_ipaddr->list);
		kमुक्त(i_ipaddr);
	पूर्ण

	kमुक्त(rds_ibdev->vector_load);

	kमुक्त(rds_ibdev);
पूर्ण

व्योम rds_ib_dev_put(काष्ठा rds_ib_device *rds_ibdev)
अणु
	BUG_ON(refcount_पढ़ो(&rds_ibdev->refcount) == 0);
	अगर (refcount_dec_and_test(&rds_ibdev->refcount))
		queue_work(rds_wq, &rds_ibdev->मुक्त_work);
पूर्ण

अटल पूर्णांक rds_ib_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा rds_ib_device *rds_ibdev;
	पूर्णांक ret;

	/* Only handle IB (no iWARP) devices */
	अगर (device->node_type != RDMA_NODE_IB_CA)
		वापस -EOPNOTSUPP;

	/* Device must support FRWR */
	अगर (!(device->attrs.device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS))
		वापस -EOPNOTSUPP;

	rds_ibdev = kzalloc_node(माप(काष्ठा rds_ib_device), GFP_KERNEL,
				 ibdev_to_node(device));
	अगर (!rds_ibdev)
		वापस -ENOMEM;

	spin_lock_init(&rds_ibdev->spinlock);
	refcount_set(&rds_ibdev->refcount, 1);
	INIT_WORK(&rds_ibdev->मुक्त_work, rds_ib_dev_मुक्त);

	INIT_LIST_HEAD(&rds_ibdev->ipaddr_list);
	INIT_LIST_HEAD(&rds_ibdev->conn_list);

	rds_ibdev->max_wrs = device->attrs.max_qp_wr;
	rds_ibdev->max_sge = min(device->attrs.max_send_sge, RDS_IB_MAX_SGE);

	rds_ibdev->odp_capable =
		!!(device->attrs.device_cap_flags &
		   IB_DEVICE_ON_DEMAND_PAGING) &&
		!!(device->attrs.odp_caps.per_transport_caps.rc_odp_caps &
		   IB_ODP_SUPPORT_WRITE) &&
		!!(device->attrs.odp_caps.per_transport_caps.rc_odp_caps &
		   IB_ODP_SUPPORT_READ);

	rds_ibdev->max_1m_mrs = device->attrs.max_mr ?
		min_t(अचिन्हित पूर्णांक, (device->attrs.max_mr / 2),
		      rds_ib_mr_1m_pool_size) : rds_ib_mr_1m_pool_size;

	rds_ibdev->max_8k_mrs = device->attrs.max_mr ?
		min_t(अचिन्हित पूर्णांक, ((device->attrs.max_mr / 2) * RDS_MR_8K_SCALE),
		      rds_ib_mr_8k_pool_size) : rds_ib_mr_8k_pool_size;

	rds_ibdev->max_initiator_depth = device->attrs.max_qp_init_rd_atom;
	rds_ibdev->max_responder_resources = device->attrs.max_qp_rd_atom;

	rds_ibdev->vector_load = kसुस्मृति(device->num_comp_vectors,
					 माप(पूर्णांक),
					 GFP_KERNEL);
	अगर (!rds_ibdev->vector_load) अणु
		pr_err("RDS/IB: %s failed to allocate vector memory\n",
			__func__);
		ret = -ENOMEM;
		जाओ put_dev;
	पूर्ण

	rds_ibdev->dev = device;
	rds_ibdev->pd = ib_alloc_pd(device, 0);
	अगर (IS_ERR(rds_ibdev->pd)) अणु
		ret = PTR_ERR(rds_ibdev->pd);
		rds_ibdev->pd = शून्य;
		जाओ put_dev;
	पूर्ण

	rds_ibdev->mr_1m_pool =
		rds_ib_create_mr_pool(rds_ibdev, RDS_IB_MR_1M_POOL);
	अगर (IS_ERR(rds_ibdev->mr_1m_pool)) अणु
		ret = PTR_ERR(rds_ibdev->mr_1m_pool);
		rds_ibdev->mr_1m_pool = शून्य;
		जाओ put_dev;
	पूर्ण

	rds_ibdev->mr_8k_pool =
		rds_ib_create_mr_pool(rds_ibdev, RDS_IB_MR_8K_POOL);
	अगर (IS_ERR(rds_ibdev->mr_8k_pool)) अणु
		ret = PTR_ERR(rds_ibdev->mr_8k_pool);
		rds_ibdev->mr_8k_pool = शून्य;
		जाओ put_dev;
	पूर्ण

	rdsdebug("RDS/IB: max_mr = %d, max_wrs = %d, max_sge = %d, max_1m_mrs = %d, max_8k_mrs = %d\n",
		 device->attrs.max_mr, rds_ibdev->max_wrs, rds_ibdev->max_sge,
		 rds_ibdev->max_1m_mrs, rds_ibdev->max_8k_mrs);

	pr_info("RDS/IB: %s: added\n", device->name);

	करोwn_ग_लिखो(&rds_ib_devices_lock);
	list_add_tail_rcu(&rds_ibdev->list, &rds_ib_devices);
	up_ग_लिखो(&rds_ib_devices_lock);
	refcount_inc(&rds_ibdev->refcount);

	ib_set_client_data(device, &rds_ib_client, rds_ibdev);

	rds_ib_nodev_connect();
	वापस 0;

put_dev:
	rds_ib_dev_put(rds_ibdev);
	वापस ret;
पूर्ण

/*
 * New connections use this to find the device to associate with the
 * connection.  It's not in the fast path so we're not concerned about the
 * perक्रमmance of the IB call.  (As of this writing, it uses an पूर्णांकerrupt
 * blocking spinlock to serialize walking a per-device list of all रेजिस्टरed
 * clients.)
 *
 * RCU is used to handle incoming connections racing with device tearकरोwn.
 * Rather than use a lock to serialize removal from the client_data and
 * getting a new reference, we use an RCU grace period.  The deकाष्ठाion
 * path हटाओs the device from client_data and then रुकोs क्रम all RCU
 * पढ़ोers to finish.
 *
 * A new connection can get शून्य from this अगर its arriving on a
 * device that is in the process of being हटाओd.
 */
काष्ठा rds_ib_device *rds_ib_get_client_data(काष्ठा ib_device *device)
अणु
	काष्ठा rds_ib_device *rds_ibdev;

	rcu_पढ़ो_lock();
	rds_ibdev = ib_get_client_data(device, &rds_ib_client);
	अगर (rds_ibdev)
		refcount_inc(&rds_ibdev->refcount);
	rcu_पढ़ो_unlock();
	वापस rds_ibdev;
पूर्ण

/*
 * The IB stack is letting us know that a device is going away.  This can
 * happen अगर the underlying HCA driver is हटाओd or अगर PCI hotplug is removing
 * the pci function, क्रम example.
 *
 * This can be called at any समय and can be racing with any other RDS path.
 */
अटल व्योम rds_ib_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा rds_ib_device *rds_ibdev = client_data;

	rds_ib_dev_shutकरोwn(rds_ibdev);

	/* stop connection attempts from getting a reference to this device. */
	ib_set_client_data(device, &rds_ib_client, शून्य);

	करोwn_ग_लिखो(&rds_ib_devices_lock);
	list_del_rcu(&rds_ibdev->list);
	up_ग_लिखो(&rds_ib_devices_lock);

	/*
	 * This synchronize rcu is रुकोing क्रम पढ़ोers of both the ib
	 * client data and the devices list to finish beक्रमe we drop
	 * both of those references.
	 */
	synchronize_rcu();
	rds_ib_dev_put(rds_ibdev);
	rds_ib_dev_put(rds_ibdev);
पूर्ण

काष्ठा ib_client rds_ib_client = अणु
	.name   = "rds_ib",
	.add    = rds_ib_add_one,
	.हटाओ = rds_ib_हटाओ_one
पूर्ण;

अटल पूर्णांक rds_ib_conn_info_visitor(काष्ठा rds_connection *conn,
				    व्योम *buffer)
अणु
	काष्ठा rds_info_rdma_connection *iinfo = buffer;
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	/* We will only ever look at IB transports */
	अगर (conn->c_trans != &rds_ib_transport)
		वापस 0;
	अगर (conn->c_isv6)
		वापस 0;

	iinfo->src_addr = conn->c_laddr.s6_addr32[3];
	iinfo->dst_addr = conn->c_faddr.s6_addr32[3];
	अगर (ic) अणु
		iinfo->tos = conn->c_tos;
		iinfo->sl = ic->i_sl;
	पूर्ण

	स_रखो(&iinfo->src_gid, 0, माप(iinfo->src_gid));
	स_रखो(&iinfo->dst_gid, 0, माप(iinfo->dst_gid));
	अगर (rds_conn_state(conn) == RDS_CONN_UP) अणु
		काष्ठा rds_ib_device *rds_ibdev;

		rdma_पढ़ो_gids(ic->i_cm_id, (जोड़ ib_gid *)&iinfo->src_gid,
			       (जोड़ ib_gid *)&iinfo->dst_gid);

		rds_ibdev = ic->rds_ibdev;
		iinfo->max_send_wr = ic->i_send_ring.w_nr;
		iinfo->max_recv_wr = ic->i_recv_ring.w_nr;
		iinfo->max_send_sge = rds_ibdev->max_sge;
		rds_ib_get_mr_info(rds_ibdev, iinfo);
		iinfo->cache_allocs = atomic_पढ़ो(&ic->i_cache_allocs);
	पूर्ण
	वापस 1;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/* IPv6 version of rds_ib_conn_info_visitor(). */
अटल पूर्णांक rds6_ib_conn_info_visitor(काष्ठा rds_connection *conn,
				     व्योम *buffer)
अणु
	काष्ठा rds6_info_rdma_connection *iinfo6 = buffer;
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	/* We will only ever look at IB transports */
	अगर (conn->c_trans != &rds_ib_transport)
		वापस 0;

	iinfo6->src_addr = conn->c_laddr;
	iinfo6->dst_addr = conn->c_faddr;
	अगर (ic) अणु
		iinfo6->tos = conn->c_tos;
		iinfo6->sl = ic->i_sl;
	पूर्ण

	स_रखो(&iinfo6->src_gid, 0, माप(iinfo6->src_gid));
	स_रखो(&iinfo6->dst_gid, 0, माप(iinfo6->dst_gid));

	अगर (rds_conn_state(conn) == RDS_CONN_UP) अणु
		काष्ठा rds_ib_device *rds_ibdev;

		rdma_पढ़ो_gids(ic->i_cm_id, (जोड़ ib_gid *)&iinfo6->src_gid,
			       (जोड़ ib_gid *)&iinfo6->dst_gid);
		rds_ibdev = ic->rds_ibdev;
		iinfo6->max_send_wr = ic->i_send_ring.w_nr;
		iinfo6->max_recv_wr = ic->i_recv_ring.w_nr;
		iinfo6->max_send_sge = rds_ibdev->max_sge;
		rds6_ib_get_mr_info(rds_ibdev, iinfo6);
		iinfo6->cache_allocs = atomic_पढ़ो(&ic->i_cache_allocs);
	पूर्ण
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल व्योम rds_ib_ic_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			   काष्ठा rds_info_iterator *iter,
			   काष्ठा rds_info_lengths *lens)
अणु
	u64 buffer[(माप(काष्ठा rds_info_rdma_connection) + 7) / 8];

	rds_क्रम_each_conn_info(sock, len, iter, lens,
				rds_ib_conn_info_visitor,
				buffer,
				माप(काष्ठा rds_info_rdma_connection));
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/* IPv6 version of rds_ib_ic_info(). */
अटल व्योम rds6_ib_ic_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			    काष्ठा rds_info_iterator *iter,
			    काष्ठा rds_info_lengths *lens)
अणु
	u64 buffer[(माप(काष्ठा rds6_info_rdma_connection) + 7) / 8];

	rds_क्रम_each_conn_info(sock, len, iter, lens,
			       rds6_ib_conn_info_visitor,
			       buffer,
			       माप(काष्ठा rds6_info_rdma_connection));
पूर्ण
#पूर्ण_अगर

/*
 * Early RDS/IB was built to only bind to an address अगर there is an IPoIB
 * device with that address set.
 *
 * If it were me, I'd advocate क्रम something more flexible.  Sending and
 * receiving should be device-agnostic.  Transports would try and मुख्यtain
 * connections between peers who have messages queued.  Userspace would be
 * allowed to influence which paths have priority.  We could call userspace
 * निश्चितing this policy "routing".
 */
अटल पूर्णांक rds_ib_laddr_check(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			      __u32 scope_id)
अणु
	पूर्णांक ret;
	काष्ठा rdma_cm_id *cm_id;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा sockaddr_in6 sin6;
#पूर्ण_अगर
	काष्ठा sockaddr_in sin;
	काष्ठा sockaddr *sa;
	bool isv4;

	isv4 = ipv6_addr_v4mapped(addr);
	/* Create a CMA ID and try to bind it. This catches both
	 * IB and iWARP capable NICs.
	 */
	cm_id = rdma_create_id(&init_net, rds_rdma_cm_event_handler,
			       शून्य, RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(cm_id))
		वापस PTR_ERR(cm_id);

	अगर (isv4) अणु
		स_रखो(&sin, 0, माप(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = addr->s6_addr32[3];
		sa = (काष्ठा sockaddr *)&sin;
	पूर्ण अन्यथा अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		स_रखो(&sin6, 0, माप(sin6));
		sin6.sin6_family = AF_INET6;
		sin6.sin6_addr = *addr;
		sin6.sin6_scope_id = scope_id;
		sa = (काष्ठा sockaddr *)&sin6;

		/* XXX Do a special IPv6 link local address check here.  The
		 * reason is that rdma_bind_addr() always succeeds with IPv6
		 * link local address regardless it is indeed configured in a
		 * प्रणाली.
		 */
		अगर (ipv6_addr_type(addr) & IPV6_ADDR_LINKLOCAL) अणु
			काष्ठा net_device *dev;

			अगर (scope_id == 0) अणु
				ret = -EADDRNOTAVAIL;
				जाओ out;
			पूर्ण

			/* Use init_net क्रम now as RDS is not network
			 * name space aware.
			 */
			dev = dev_get_by_index(&init_net, scope_id);
			अगर (!dev) अणु
				ret = -EADDRNOTAVAIL;
				जाओ out;
			पूर्ण
			अगर (!ipv6_chk_addr(&init_net, addr, dev, 1)) अणु
				dev_put(dev);
				ret = -EADDRNOTAVAIL;
				जाओ out;
			पूर्ण
			dev_put(dev);
		पूर्ण
#अन्यथा
		ret = -EADDRNOTAVAIL;
		जाओ out;
#पूर्ण_अगर
	पूर्ण

	/* rdma_bind_addr will only succeed क्रम IB & iWARP devices */
	ret = rdma_bind_addr(cm_id, sa);
	/* due to this, we will claim to support iWARP devices unless we
	   check node_type. */
	अगर (ret || !cm_id->device ||
	    cm_id->device->node_type != RDMA_NODE_IB_CA)
		ret = -EADDRNOTAVAIL;

	rdsdebug("addr %pI6c%%%u ret %d node type %d\n",
		 addr, scope_id, ret,
		 cm_id->device ? cm_id->device->node_type : -1);

out:
	rdma_destroy_id(cm_id);

	वापस ret;
पूर्ण

अटल व्योम rds_ib_unरेजिस्टर_client(व्योम)
अणु
	ib_unरेजिस्टर_client(&rds_ib_client);
	/* रुको क्रम rds_ib_dev_मुक्त() to complete */
	flush_workqueue(rds_wq);
पूर्ण

अटल व्योम rds_ib_set_unloading(व्योम)
अणु
	atomic_set(&rds_ib_unloading, 1);
पूर्ण

अटल bool rds_ib_is_unloading(काष्ठा rds_connection *conn)
अणु
	काष्ठा rds_conn_path *cp = &conn->c_path[0];

	वापस (test_bit(RDS_DESTROY_PENDING, &cp->cp_flags) ||
		atomic_पढ़ो(&rds_ib_unloading) != 0);
पूर्ण

व्योम rds_ib_निकास(व्योम)
अणु
	rds_ib_set_unloading();
	synchronize_rcu();
	rds_info_deरेजिस्टर_func(RDS_INFO_IB_CONNECTIONS, rds_ib_ic_info);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds_info_deरेजिस्टर_func(RDS6_INFO_IB_CONNECTIONS, rds6_ib_ic_info);
#पूर्ण_अगर
	rds_ib_unरेजिस्टर_client();
	rds_ib_destroy_nodev_conns();
	rds_ib_sysctl_निकास();
	rds_ib_recv_निकास();
	rds_trans_unरेजिस्टर(&rds_ib_transport);
	rds_ib_mr_निकास();
पूर्ण

अटल u8 rds_ib_get_tos_map(u8 tos)
अणु
	/* 1:1 user to transport map क्रम RDMA transport.
	 * In future, अगर custom map is desired, hook can export
	 * user configurable map.
	 */
	वापस tos;
पूर्ण

काष्ठा rds_transport rds_ib_transport = अणु
	.laddr_check		= rds_ib_laddr_check,
	.xmit_path_complete	= rds_ib_xmit_path_complete,
	.xmit			= rds_ib_xmit,
	.xmit_rdma		= rds_ib_xmit_rdma,
	.xmit_atomic		= rds_ib_xmit_atomic,
	.recv_path		= rds_ib_recv_path,
	.conn_alloc		= rds_ib_conn_alloc,
	.conn_मुक्त		= rds_ib_conn_मुक्त,
	.conn_path_connect	= rds_ib_conn_path_connect,
	.conn_path_shutकरोwn	= rds_ib_conn_path_shutकरोwn,
	.inc_copy_to_user	= rds_ib_inc_copy_to_user,
	.inc_मुक्त		= rds_ib_inc_मुक्त,
	.cm_initiate_connect	= rds_ib_cm_initiate_connect,
	.cm_handle_connect	= rds_ib_cm_handle_connect,
	.cm_connect_complete	= rds_ib_cm_connect_complete,
	.stats_info_copy	= rds_ib_stats_info_copy,
	.निकास			= rds_ib_निकास,
	.get_mr			= rds_ib_get_mr,
	.sync_mr		= rds_ib_sync_mr,
	.मुक्त_mr		= rds_ib_मुक्त_mr,
	.flush_mrs		= rds_ib_flush_mrs,
	.get_tos_map		= rds_ib_get_tos_map,
	.t_owner		= THIS_MODULE,
	.t_name			= "infiniband",
	.t_unloading		= rds_ib_is_unloading,
	.t_type			= RDS_TRANS_IB
पूर्ण;

पूर्णांक rds_ib_init(व्योम)
अणु
	पूर्णांक ret;

	INIT_LIST_HEAD(&rds_ib_devices);

	ret = rds_ib_mr_init();
	अगर (ret)
		जाओ out;

	ret = ib_रेजिस्टर_client(&rds_ib_client);
	अगर (ret)
		जाओ out_mr_निकास;

	ret = rds_ib_sysctl_init();
	अगर (ret)
		जाओ out_ibreg;

	ret = rds_ib_recv_init();
	अगर (ret)
		जाओ out_sysctl;

	rds_trans_रेजिस्टर(&rds_ib_transport);

	rds_info_रेजिस्टर_func(RDS_INFO_IB_CONNECTIONS, rds_ib_ic_info);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds_info_रेजिस्टर_func(RDS6_INFO_IB_CONNECTIONS, rds6_ib_ic_info);
#पूर्ण_अगर

	जाओ out;

out_sysctl:
	rds_ib_sysctl_निकास();
out_ibreg:
	rds_ib_unरेजिस्टर_client();
out_mr_निकास:
	rds_ib_mr_निकास();
out:
	वापस ret;
पूर्ण

MODULE_LICENSE("GPL");
