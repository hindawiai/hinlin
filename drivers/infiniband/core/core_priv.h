<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
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

#अगर_अघोषित _CORE_PRIV_H
#घोषणा _CORE_PRIV_H

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cgroup_rdma.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/opa_addr.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/restrack.h>
#समावेश "mad_priv.h"
#समावेश "restrack.h"

/* Total number of ports combined across all काष्ठा ib_devices's */
#घोषणा RDMA_MAX_PORTS 8192

काष्ठा pkey_index_qp_list अणु
	काष्ठा list_head    pkey_index_list;
	u16                 pkey_index;
	/* Lock to hold जबतक iterating the qp_list. */
	spinlock_t          qp_list_lock;
	काष्ठा list_head    qp_list;
पूर्ण;

/**
 * काष्ठा rdma_dev_net - rdma net namespace metadata क्रम a net
 * @nl_sock:	Poपूर्णांकer to netlink socket
 * @net:	Poपूर्णांकer to owner net namespace
 * @id:		xarray id to identअगरy the net namespace.
 */
काष्ठा rdma_dev_net अणु
	काष्ठा sock *nl_sock;
	possible_net_t net;
	u32 id;
पूर्ण;

बाह्य स्थिर काष्ठा attribute_group ib_dev_attr_group;
बाह्य bool ib_devices_shared_netns;
बाह्य अचिन्हित पूर्णांक rdma_dev_net_id;

अटल अंतरभूत काष्ठा rdma_dev_net *rdma_net_to_dev_net(काष्ठा net *net)
अणु
	वापस net_generic(net, rdma_dev_net_id);
पूर्ण

पूर्णांक ib_device_रेजिस्टर_sysfs(काष्ठा ib_device *device);
व्योम ib_device_unरेजिस्टर_sysfs(काष्ठा ib_device *device);
पूर्णांक ib_device_नाम(काष्ठा ib_device *ibdev, स्थिर अक्षर *name);
पूर्णांक ib_device_set_dim(काष्ठा ib_device *ibdev, u8 use_dim);

प्रकार व्योम (*roce_netdev_callback)(काष्ठा ib_device *device, u32 port,
	      काष्ठा net_device *idev, व्योम *cookie);

प्रकार bool (*roce_netdev_filter)(काष्ठा ib_device *device, u32 port,
				   काष्ठा net_device *idev, व्योम *cookie);

काष्ठा net_device *ib_device_get_netdev(काष्ठा ib_device *ib_dev,
					u32 port);

व्योम ib_क्रमागत_roce_netdev(काष्ठा ib_device *ib_dev,
			 roce_netdev_filter filter,
			 व्योम *filter_cookie,
			 roce_netdev_callback cb,
			 व्योम *cookie);
व्योम ib_क्रमागत_all_roce_netdevs(roce_netdev_filter filter,
			      व्योम *filter_cookie,
			      roce_netdev_callback cb,
			      व्योम *cookie);

प्रकार पूर्णांक (*nldev_callback)(काष्ठा ib_device *device,
			      काष्ठा sk_buff *skb,
			      काष्ठा netlink_callback *cb,
			      अचिन्हित पूर्णांक idx);

पूर्णांक ib_क्रमागत_all_devs(nldev_callback nldev_cb, काष्ठा sk_buff *skb,
		     काष्ठा netlink_callback *cb);

काष्ठा ib_client_nl_info अणु
	काष्ठा sk_buff *nl_msg;
	काष्ठा device *cdev;
	u32 port;
	u64 abi;
पूर्ण;
पूर्णांक ib_get_client_nl_info(काष्ठा ib_device *ibdev, स्थिर अक्षर *client_name,
			  काष्ठा ib_client_nl_info *res);

क्रमागत ib_cache_gid_शेष_mode अणु
	IB_CACHE_GID_DEFAULT_MODE_SET,
	IB_CACHE_GID_DEFAULT_MODE_DELETE
पूर्ण;

पूर्णांक ib_cache_gid_parse_type_str(स्थिर अक्षर *buf);

स्थिर अक्षर *ib_cache_gid_type_str(क्रमागत ib_gid_type gid_type);

व्योम ib_cache_gid_set_शेष_gid(काष्ठा ib_device *ib_dev, u32 port,
				  काष्ठा net_device *ndev,
				  अचिन्हित दीर्घ gid_type_mask,
				  क्रमागत ib_cache_gid_शेष_mode mode);

पूर्णांक ib_cache_gid_add(काष्ठा ib_device *ib_dev, u32 port,
		     जोड़ ib_gid *gid, काष्ठा ib_gid_attr *attr);

पूर्णांक ib_cache_gid_del(काष्ठा ib_device *ib_dev, u32 port,
		     जोड़ ib_gid *gid, काष्ठा ib_gid_attr *attr);

पूर्णांक ib_cache_gid_del_all_netdev_gids(काष्ठा ib_device *ib_dev, u32 port,
				     काष्ठा net_device *ndev);

पूर्णांक roce_gid_mgmt_init(व्योम);
व्योम roce_gid_mgmt_cleanup(व्योम);

अचिन्हित दीर्घ roce_gid_type_mask_support(काष्ठा ib_device *ib_dev, u32 port);

पूर्णांक ib_cache_setup_one(काष्ठा ib_device *device);
व्योम ib_cache_cleanup_one(काष्ठा ib_device *device);
व्योम ib_cache_release_one(काष्ठा ib_device *device);
व्योम ib_dispatch_event_clients(काष्ठा ib_event *event);

#अगर_घोषित CONFIG_CGROUP_RDMA
व्योम ib_device_रेजिस्टर_rdmacg(काष्ठा ib_device *device);
व्योम ib_device_unरेजिस्टर_rdmacg(काष्ठा ib_device *device);

पूर्णांक ib_rdmacg_try_अक्षरge(काष्ठा ib_rdmacg_object *cg_obj,
			 काष्ठा ib_device *device,
			 क्रमागत rdmacg_resource_type resource_index);

व्योम ib_rdmacg_unअक्षरge(काष्ठा ib_rdmacg_object *cg_obj,
			काष्ठा ib_device *device,
			क्रमागत rdmacg_resource_type resource_index);
#अन्यथा
अटल अंतरभूत व्योम ib_device_रेजिस्टर_rdmacg(काष्ठा ib_device *device)
अणु
पूर्ण

अटल अंतरभूत व्योम ib_device_unरेजिस्टर_rdmacg(काष्ठा ib_device *device)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ib_rdmacg_try_अक्षरge(काष्ठा ib_rdmacg_object *cg_obj,
				       काष्ठा ib_device *device,
				       क्रमागत rdmacg_resource_type resource_index)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ib_rdmacg_unअक्षरge(काष्ठा ib_rdmacg_object *cg_obj,
				      काष्ठा ib_device *device,
				      क्रमागत rdmacg_resource_type resource_index)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool rdma_is_upper_dev_rcu(काष्ठा net_device *dev,
					 काष्ठा net_device *upper)
अणु
	वापस netdev_has_upper_dev_all_rcu(dev, upper);
पूर्ण

पूर्णांक addr_init(व्योम);
व्योम addr_cleanup(व्योम);

पूर्णांक ib_mad_init(व्योम);
व्योम ib_mad_cleanup(व्योम);

पूर्णांक ib_sa_init(व्योम);
व्योम ib_sa_cleanup(व्योम);

व्योम rdma_nl_init(व्योम);
व्योम rdma_nl_निकास(व्योम);

पूर्णांक ib_nl_handle_resolve_resp(काष्ठा sk_buff *skb,
			      काष्ठा nlmsghdr *nlh,
			      काष्ठा netlink_ext_ack *extack);
पूर्णांक ib_nl_handle_set_समयout(काष्ठा sk_buff *skb,
			     काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack);
पूर्णांक ib_nl_handle_ip_res_resp(काष्ठा sk_buff *skb,
			     काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack);

पूर्णांक ib_get_cached_subnet_prefix(काष्ठा ib_device *device,
				u32 port_num,
				u64 *sn_pfx);

#अगर_घोषित CONFIG_SECURITY_INFINIBAND
व्योम ib_security_release_port_pkey_list(काष्ठा ib_device *device);

व्योम ib_security_cache_change(काष्ठा ib_device *device,
			      u32 port_num,
			      u64 subnet_prefix);

पूर्णांक ib_security_modअगरy_qp(काष्ठा ib_qp *qp,
			  काष्ठा ib_qp_attr *qp_attr,
			  पूर्णांक qp_attr_mask,
			  काष्ठा ib_udata *udata);

पूर्णांक ib_create_qp_security(काष्ठा ib_qp *qp, काष्ठा ib_device *dev);
व्योम ib_destroy_qp_security_begin(काष्ठा ib_qp_security *sec);
व्योम ib_destroy_qp_security_पात(काष्ठा ib_qp_security *sec);
व्योम ib_destroy_qp_security_end(काष्ठा ib_qp_security *sec);
पूर्णांक ib_खोलो_shared_qp_security(काष्ठा ib_qp *qp, काष्ठा ib_device *dev);
व्योम ib_बंद_shared_qp_security(काष्ठा ib_qp_security *sec);
पूर्णांक ib_mad_agent_security_setup(काष्ठा ib_mad_agent *agent,
				क्रमागत ib_qp_type qp_type);
व्योम ib_mad_agent_security_cleanup(काष्ठा ib_mad_agent *agent);
पूर्णांक ib_mad_enक्रमce_security(काष्ठा ib_mad_agent_निजी *map, u16 pkey_index);
व्योम ib_mad_agent_security_change(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ib_security_release_port_pkey_list(काष्ठा ib_device *device)
अणु
पूर्ण

अटल अंतरभूत व्योम ib_security_cache_change(काष्ठा ib_device *device,
					    u32 port_num,
					    u64 subnet_prefix)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ib_security_modअगरy_qp(काष्ठा ib_qp *qp,
					काष्ठा ib_qp_attr *qp_attr,
					पूर्णांक qp_attr_mask,
					काष्ठा ib_udata *udata)
अणु
	वापस qp->device->ops.modअगरy_qp(qp->real_qp,
					 qp_attr,
					 qp_attr_mask,
					 udata);
पूर्ण

अटल अंतरभूत पूर्णांक ib_create_qp_security(काष्ठा ib_qp *qp,
					काष्ठा ib_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ib_destroy_qp_security_begin(काष्ठा ib_qp_security *sec)
अणु
पूर्ण

अटल अंतरभूत व्योम ib_destroy_qp_security_पात(काष्ठा ib_qp_security *sec)
अणु
पूर्ण

अटल अंतरभूत व्योम ib_destroy_qp_security_end(काष्ठा ib_qp_security *sec)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ib_खोलो_shared_qp_security(काष्ठा ib_qp *qp,
					     काष्ठा ib_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ib_बंद_shared_qp_security(काष्ठा ib_qp_security *sec)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ib_mad_agent_security_setup(काष्ठा ib_mad_agent *agent,
					      क्रमागत ib_qp_type qp_type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ib_mad_agent_security_cleanup(काष्ठा ib_mad_agent *agent)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ib_mad_enक्रमce_security(काष्ठा ib_mad_agent_निजी *map,
					  u16 pkey_index)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ib_mad_agent_security_change(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा ib_device *ib_device_get_by_index(स्थिर काष्ठा net *net, u32 index);

/* RDMA device netlink */
व्योम nldev_init(व्योम);
व्योम nldev_निकास(व्योम);

अटल अंतरभूत काष्ठा ib_qp *
_ib_create_qp(काष्ठा ib_device *dev, काष्ठा ib_pd *pd,
	      काष्ठा ib_qp_init_attr *attr, काष्ठा ib_udata *udata,
	      काष्ठा ib_uqp_object *uobj, स्थिर अक्षर *caller)
अणु
	काष्ठा ib_qp *qp;

	अगर (!dev->ops.create_qp)
		वापस ERR_PTR(-EOPNOTSUPP);

	qp = dev->ops.create_qp(pd, attr, udata);
	अगर (IS_ERR(qp))
		वापस qp;

	qp->device = dev;
	qp->pd = pd;
	qp->uobject = uobj;
	qp->real_qp = qp;

	qp->qp_type = attr->qp_type;
	qp->rwq_ind_tbl = attr->rwq_ind_tbl;
	qp->send_cq = attr->send_cq;
	qp->recv_cq = attr->recv_cq;
	qp->srq = attr->srq;
	qp->rwq_ind_tbl = attr->rwq_ind_tbl;
	qp->event_handler = attr->event_handler;
	qp->port = attr->port_num;

	atomic_set(&qp->usecnt, 0);
	spin_lock_init(&qp->mr_lock);
	INIT_LIST_HEAD(&qp->rdma_mrs);
	INIT_LIST_HEAD(&qp->sig_mrs);

	rdma_restrack_new(&qp->res, RDMA_RESTRACK_QP);
	WARN_ONCE(!udata && !caller, "Missing kernel QP owner");
	rdma_restrack_set_name(&qp->res, udata ? शून्य : caller);
	rdma_restrack_add(&qp->res);
	वापस qp;
पूर्ण

काष्ठा rdma_dev_addr;
पूर्णांक rdma_resolve_ip_route(काष्ठा sockaddr *src_addr,
			  स्थिर काष्ठा sockaddr *dst_addr,
			  काष्ठा rdma_dev_addr *addr);

पूर्णांक rdma_addr_find_l2_eth_by_grh(स्थिर जोड़ ib_gid *sgid,
				 स्थिर जोड़ ib_gid *dgid,
				 u8 *dmac, स्थिर काष्ठा ib_gid_attr *sgid_attr,
				 पूर्णांक *hoplimit);
व्योम rdma_copy_src_l2_addr(काष्ठा rdma_dev_addr *dev_addr,
			   स्थिर काष्ठा net_device *dev);

काष्ठा sa_path_rec;
पूर्णांक roce_resolve_route_from_path(काष्ठा sa_path_rec *rec,
				 स्थिर काष्ठा ib_gid_attr *attr);

काष्ठा net_device *rdma_पढ़ो_gid_attr_ndev_rcu(स्थिर काष्ठा ib_gid_attr *attr);

व्योम ib_मुक्त_port_attrs(काष्ठा ib_core_device *coredev);
पूर्णांक ib_setup_port_attrs(काष्ठा ib_core_device *coredev);

पूर्णांक rdma_compatdev_set(u8 enable);

पूर्णांक ib_port_रेजिस्टर_module_stat(काष्ठा ib_device *device, u32 port_num,
				 काष्ठा kobject *kobj, काष्ठा kobj_type *ktype,
				 स्थिर अक्षर *name);
व्योम ib_port_unरेजिस्टर_module_stat(काष्ठा kobject *kobj);

पूर्णांक ib_device_set_netns_put(काष्ठा sk_buff *skb,
			    काष्ठा ib_device *dev, u32 ns_fd);

पूर्णांक rdma_nl_net_init(काष्ठा rdma_dev_net *rnet);
व्योम rdma_nl_net_निकास(काष्ठा rdma_dev_net *rnet);

काष्ठा rdma_umap_priv अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा list_head list;
	काष्ठा rdma_user_mmap_entry *entry;
पूर्ण;

व्योम rdma_umap_priv_init(काष्ठा rdma_umap_priv *priv,
			 काष्ठा vm_area_काष्ठा *vma,
			 काष्ठा rdma_user_mmap_entry *entry);

व्योम ib_cq_pool_cleanup(काष्ठा ib_device *dev);

#पूर्ण_अगर /* _CORE_PRIV_H */
