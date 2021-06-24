<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * iSCSI transport class definitions
 *
 * Copyright (C) IBM Corporation, 2004
 * Copyright (C) Mike Christie, 2004 - 2005
 * Copyright (C) Dmitry Yusupov, 2004 - 2005
 * Copyright (C) Alex Aizman, 2004 - 2005
 */
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/bsg-lib.h>
#समावेश <linux/idr.h>
#समावेश <net/tcp.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_iscsi.h>
#समावेश <scsi/iscsi_अगर.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_bsg_iscsi.h>

#घोषणा ISCSI_TRANSPORT_VERSION "2.0-870"

#घोषणा ISCSI_SEND_MAX_ALLOWED  10

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/iscsi.h>

/*
 * Export tracepoपूर्णांक symbols to be used by other modules.
 */
EXPORT_TRACEPOINT_SYMBOL_GPL(iscsi_dbg_conn);
EXPORT_TRACEPOINT_SYMBOL_GPL(iscsi_dbg_eh);
EXPORT_TRACEPOINT_SYMBOL_GPL(iscsi_dbg_session);
EXPORT_TRACEPOINT_SYMBOL_GPL(iscsi_dbg_tcp);
EXPORT_TRACEPOINT_SYMBOL_GPL(iscsi_dbg_sw_tcp);

अटल पूर्णांक dbg_session;
module_param_named(debug_session, dbg_session, पूर्णांक,
		   S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_session,
		 "Turn on debugging for sessions in scsi_transport_iscsi "
		 "module. Set to 1 to turn on, and zero to turn off. Default "
		 "is off.");

अटल पूर्णांक dbg_conn;
module_param_named(debug_conn, dbg_conn, पूर्णांक,
		   S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_conn,
		 "Turn on debugging for connections in scsi_transport_iscsi "
		 "module. Set to 1 to turn on, and zero to turn off. Default "
		 "is off.");

#घोषणा ISCSI_DBG_TRANS_SESSION(_session, dbg_fmt, arg...)		\
	करो अणु								\
		अगर (dbg_session)					\
			iscsi_cls_session_prपूर्णांकk(KERN_INFO, _session,	\
						 "%s: " dbg_fmt,	\
						 __func__, ##arg);	\
		iscsi_dbg_trace(trace_iscsi_dbg_trans_session,		\
				&(_session)->dev,			\
				"%s " dbg_fmt, __func__, ##arg);	\
	पूर्ण जबतक (0);

#घोषणा ISCSI_DBG_TRANS_CONN(_conn, dbg_fmt, arg...)			\
	करो अणु								\
		अगर (dbg_conn)						\
			iscsi_cls_conn_prपूर्णांकk(KERN_INFO, _conn,		\
					      "%s: " dbg_fmt,		\
					      __func__, ##arg);		\
		iscsi_dbg_trace(trace_iscsi_dbg_trans_conn,		\
				&(_conn)->dev,				\
				"%s " dbg_fmt, __func__, ##arg);	\
	पूर्ण जबतक (0);

काष्ठा iscsi_पूर्णांकernal अणु
	काष्ठा scsi_transport_ढाँचा t;
	काष्ठा iscsi_transport *iscsi_transport;
	काष्ठा list_head list;
	काष्ठा device dev;

	काष्ठा transport_container conn_cont;
	काष्ठा transport_container session_cont;
पूर्ण;

/* Worker to perक्रमm connection failure on unresponsive connections
 * completely in kernel space.
 */
अटल व्योम stop_conn_work_fn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(stop_conn_work, stop_conn_work_fn);

अटल atomic_t iscsi_session_nr; /* sysfs session id क्रम next new session */
अटल काष्ठा workqueue_काष्ठा *iscsi_eh_समयr_workq;

अटल काष्ठा workqueue_काष्ठा *iscsi_destroy_workq;

अटल DEFINE_IDA(iscsi_sess_ida);
/*
 * list of रेजिस्टरed transports and lock that must
 * be held जबतक accessing list. The iscsi_transport_lock must
 * be acquired after the rx_queue_mutex.
 */
अटल LIST_HEAD(iscsi_transports);
अटल DEFINE_SPINLOCK(iscsi_transport_lock);

#घोषणा to_iscsi_पूर्णांकernal(पंचांगpl) \
	container_of(पंचांगpl, काष्ठा iscsi_पूर्णांकernal, t)

#घोषणा dev_to_iscsi_पूर्णांकernal(_dev) \
	container_of(_dev, काष्ठा iscsi_पूर्णांकernal, dev)

अटल व्योम iscsi_transport_release(काष्ठा device *dev)
अणु
	काष्ठा iscsi_पूर्णांकernal *priv = dev_to_iscsi_पूर्णांकernal(dev);
	kमुक्त(priv);
पूर्ण

/*
 * iscsi_transport_class represents the iscsi_transports that are
 * रेजिस्टरed.
 */
अटल काष्ठा class iscsi_transport_class = अणु
	.name = "iscsi_transport",
	.dev_release = iscsi_transport_release,
पूर्ण;

अटल sमाप_प्रकार
show_transport_handle(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा iscsi_पूर्णांकernal *priv = dev_to_iscsi_पूर्णांकernal(dev);

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	वापस sysfs_emit(buf, "%llu\n",
		  (अचिन्हित दीर्घ दीर्घ)iscsi_handle(priv->iscsi_transport));
पूर्ण
अटल DEVICE_ATTR(handle, S_IRUGO, show_transport_handle, शून्य);

#घोषणा show_transport_attr(name, क्रमmat)				\
अटल sमाप_प्रकार								\
show_transport_##name(काष्ठा device *dev, 				\
		      काष्ठा device_attribute *attr,अक्षर *buf)		\
अणु									\
	काष्ठा iscsi_पूर्णांकernal *priv = dev_to_iscsi_पूर्णांकernal(dev);	\
	वापस sysfs_emit(buf, क्रमmat"\n", priv->iscsi_transport->name);\
पूर्ण									\
अटल DEVICE_ATTR(name, S_IRUGO, show_transport_##name, शून्य);

show_transport_attr(caps, "0x%x");

अटल काष्ठा attribute *iscsi_transport_attrs[] = अणु
	&dev_attr_handle.attr,
	&dev_attr_caps.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group iscsi_transport_group = अणु
	.attrs = iscsi_transport_attrs,
पूर्ण;

/*
 * iSCSI endpoपूर्णांक attrs
 */
#घोषणा iscsi_dev_to_endpoपूर्णांक(_dev) \
	container_of(_dev, काष्ठा iscsi_endpoपूर्णांक, dev)

#घोषणा ISCSI_ATTR(_prefix,_name,_mode,_show,_store)	\
काष्ठा device_attribute dev_attr_##_prefix##_##_name =	\
        __ATTR(_name,_mode,_show,_store)

अटल व्योम iscsi_endpoपूर्णांक_release(काष्ठा device *dev)
अणु
	काष्ठा iscsi_endpoपूर्णांक *ep = iscsi_dev_to_endpoपूर्णांक(dev);
	kमुक्त(ep);
पूर्ण

अटल काष्ठा class iscsi_endpoपूर्णांक_class = अणु
	.name = "iscsi_endpoint",
	.dev_release = iscsi_endpoपूर्णांक_release,
पूर्ण;

अटल sमाप_प्रकार
show_ep_handle(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iscsi_endpoपूर्णांक *ep = iscsi_dev_to_endpoपूर्णांक(dev);
	वापस sysfs_emit(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ) ep->id);
पूर्ण
अटल ISCSI_ATTR(ep, handle, S_IRUGO, show_ep_handle, शून्य);

अटल काष्ठा attribute *iscsi_endpoपूर्णांक_attrs[] = अणु
	&dev_attr_ep_handle.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group iscsi_endpoपूर्णांक_group = अणु
	.attrs = iscsi_endpoपूर्णांक_attrs,
पूर्ण;

#घोषणा ISCSI_MAX_EPID -1

अटल पूर्णांक iscsi_match_epid(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा iscsi_endpoपूर्णांक *ep = iscsi_dev_to_endpoपूर्णांक(dev);
	स्थिर uपूर्णांक64_t *epid = data;

	वापस *epid == ep->id;
पूर्ण

काष्ठा iscsi_endpoपूर्णांक *
iscsi_create_endpoपूर्णांक(पूर्णांक dd_size)
अणु
	काष्ठा device *dev;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	uपूर्णांक64_t id;
	पूर्णांक err;

	क्रम (id = 1; id < ISCSI_MAX_EPID; id++) अणु
		dev = class_find_device(&iscsi_endpoपूर्णांक_class, शून्य, &id,
					iscsi_match_epid);
		अगर (!dev)
			अवरोध;
		अन्यथा
			put_device(dev);
	पूर्ण
	अगर (id == ISCSI_MAX_EPID) अणु
		prपूर्णांकk(KERN_ERR "Too many connections. Max supported %u\n",
		       ISCSI_MAX_EPID - 1);
		वापस शून्य;
	पूर्ण

	ep = kzalloc(माप(*ep) + dd_size, GFP_KERNEL);
	अगर (!ep)
		वापस शून्य;

	ep->id = id;
	ep->dev.class = &iscsi_endpoपूर्णांक_class;
	dev_set_name(&ep->dev, "ep-%llu", (अचिन्हित दीर्घ दीर्घ) id);
	err = device_रेजिस्टर(&ep->dev);
        अगर (err)
                जाओ मुक्त_ep;

	err = sysfs_create_group(&ep->dev.kobj, &iscsi_endpoपूर्णांक_group);
	अगर (err)
		जाओ unरेजिस्टर_dev;

	अगर (dd_size)
		ep->dd_data = &ep[1];
	वापस ep;

unरेजिस्टर_dev:
	device_unरेजिस्टर(&ep->dev);
	वापस शून्य;

मुक्त_ep:
	kमुक्त(ep);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_create_endpoपूर्णांक);

व्योम iscsi_destroy_endpoपूर्णांक(काष्ठा iscsi_endpoपूर्णांक *ep)
अणु
	sysfs_हटाओ_group(&ep->dev.kobj, &iscsi_endpoपूर्णांक_group);
	device_unरेजिस्टर(&ep->dev);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_destroy_endpoपूर्णांक);

काष्ठा iscsi_endpoपूर्णांक *iscsi_lookup_endpoपूर्णांक(u64 handle)
अणु
	काष्ठा iscsi_endpoपूर्णांक *ep;
	काष्ठा device *dev;

	dev = class_find_device(&iscsi_endpoपूर्णांक_class, शून्य, &handle,
				iscsi_match_epid);
	अगर (!dev)
		वापस शून्य;

	ep = iscsi_dev_to_endpoपूर्णांक(dev);
	/*
	 * we can drop this now because the पूर्णांकerface will prevent
	 * removals and lookups from racing.
	 */
	put_device(dev);
	वापस ep;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_lookup_endpoपूर्णांक);

/*
 * Interface to display network param to sysfs
 */

अटल व्योम iscsi_अगरace_release(काष्ठा device *dev)
अणु
	काष्ठा iscsi_अगरace *अगरace = iscsi_dev_to_अगरace(dev);
	काष्ठा device *parent = अगरace->dev.parent;

	kमुक्त(अगरace);
	put_device(parent);
पूर्ण


अटल काष्ठा class iscsi_अगरace_class = अणु
	.name = "iscsi_iface",
	.dev_release = iscsi_अगरace_release,
पूर्ण;

#घोषणा ISCSI_IFACE_ATTR(_prefix, _name, _mode, _show, _store)	\
काष्ठा device_attribute dev_attr_##_prefix##_##_name =		\
	__ATTR(_name, _mode, _show, _store)

/* अगरace attrs show */
#घोषणा iscsi_अगरace_attr_show(type, name, param_type, param)		\
अटल sमाप_प्रकार								\
show_##type##_##name(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		     अक्षर *buf)						\
अणु									\
	काष्ठा iscsi_अगरace *अगरace = iscsi_dev_to_अगरace(dev);		\
	काष्ठा iscsi_transport *t = अगरace->transport;			\
	वापस t->get_अगरace_param(अगरace, param_type, param, buf);	\
पूर्ण									\

#घोषणा iscsi_अगरace_net_attr(type, name, param)				\
	iscsi_अगरace_attr_show(type, name, ISCSI_NET_PARAM, param)	\
अटल ISCSI_IFACE_ATTR(type, name, S_IRUGO, show_##type##_##name, शून्य);

#घोषणा iscsi_अगरace_attr(type, name, param)				\
	iscsi_अगरace_attr_show(type, name, ISCSI_IFACE_PARAM, param)	\
अटल ISCSI_IFACE_ATTR(type, name, S_IRUGO, show_##type##_##name, शून्य);

/* generic पढ़ो only ipv4 attribute */
iscsi_अगरace_net_attr(ipv4_अगरace, ipaddress, ISCSI_NET_PARAM_IPV4_ADDR);
iscsi_अगरace_net_attr(ipv4_अगरace, gateway, ISCSI_NET_PARAM_IPV4_GW);
iscsi_अगरace_net_attr(ipv4_अगरace, subnet, ISCSI_NET_PARAM_IPV4_SUBNET);
iscsi_अगरace_net_attr(ipv4_अगरace, bootproto, ISCSI_NET_PARAM_IPV4_BOOTPROTO);
iscsi_अगरace_net_attr(ipv4_अगरace, dhcp_dns_address_en,
		     ISCSI_NET_PARAM_IPV4_DHCP_DNS_ADDR_EN);
iscsi_अगरace_net_attr(ipv4_अगरace, dhcp_slp_da_info_en,
		     ISCSI_NET_PARAM_IPV4_DHCP_SLP_DA_EN);
iscsi_अगरace_net_attr(ipv4_अगरace, tos_en, ISCSI_NET_PARAM_IPV4_TOS_EN);
iscsi_अगरace_net_attr(ipv4_अगरace, tos, ISCSI_NET_PARAM_IPV4_TOS);
iscsi_अगरace_net_attr(ipv4_अगरace, grat_arp_en,
		     ISCSI_NET_PARAM_IPV4_GRAT_ARP_EN);
iscsi_अगरace_net_attr(ipv4_अगरace, dhcp_alt_client_id_en,
		     ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID_EN);
iscsi_अगरace_net_attr(ipv4_अगरace, dhcp_alt_client_id,
		     ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID);
iscsi_अगरace_net_attr(ipv4_अगरace, dhcp_req_venकरोr_id_en,
		     ISCSI_NET_PARAM_IPV4_DHCP_REQ_VENDOR_ID_EN);
iscsi_अगरace_net_attr(ipv4_अगरace, dhcp_use_venकरोr_id_en,
		     ISCSI_NET_PARAM_IPV4_DHCP_USE_VENDOR_ID_EN);
iscsi_अगरace_net_attr(ipv4_अगरace, dhcp_venकरोr_id,
		     ISCSI_NET_PARAM_IPV4_DHCP_VENDOR_ID);
iscsi_अगरace_net_attr(ipv4_अगरace, dhcp_learn_iqn_en,
		     ISCSI_NET_PARAM_IPV4_DHCP_LEARN_IQN_EN);
iscsi_अगरace_net_attr(ipv4_अगरace, fragment_disable,
		     ISCSI_NET_PARAM_IPV4_FRAGMENT_DISABLE);
iscsi_अगरace_net_attr(ipv4_अगरace, incoming_क्रमwarding_en,
		     ISCSI_NET_PARAM_IPV4_IN_FORWARD_EN);
iscsi_अगरace_net_attr(ipv4_अगरace, ttl, ISCSI_NET_PARAM_IPV4_TTL);

/* generic पढ़ो only ipv6 attribute */
iscsi_अगरace_net_attr(ipv6_अगरace, ipaddress, ISCSI_NET_PARAM_IPV6_ADDR);
iscsi_अगरace_net_attr(ipv6_अगरace, link_local_addr,
		     ISCSI_NET_PARAM_IPV6_LINKLOCAL);
iscsi_अगरace_net_attr(ipv6_अगरace, router_addr, ISCSI_NET_PARAM_IPV6_ROUTER);
iscsi_अगरace_net_attr(ipv6_अगरace, ipaddr_स्वतःcfg,
		     ISCSI_NET_PARAM_IPV6_ADDR_AUTOCFG);
iscsi_अगरace_net_attr(ipv6_अगरace, link_local_स्वतःcfg,
		     ISCSI_NET_PARAM_IPV6_LINKLOCAL_AUTOCFG);
iscsi_अगरace_net_attr(ipv6_अगरace, link_local_state,
		     ISCSI_NET_PARAM_IPV6_LINKLOCAL_STATE);
iscsi_अगरace_net_attr(ipv6_अगरace, router_state,
		     ISCSI_NET_PARAM_IPV6_ROUTER_STATE);
iscsi_अगरace_net_attr(ipv6_अगरace, grat_neighbor_adv_en,
		     ISCSI_NET_PARAM_IPV6_GRAT_NEIGHBOR_ADV_EN);
iscsi_अगरace_net_attr(ipv6_अगरace, mld_en, ISCSI_NET_PARAM_IPV6_MLD_EN);
iscsi_अगरace_net_attr(ipv6_अगरace, flow_label, ISCSI_NET_PARAM_IPV6_FLOW_LABEL);
iscsi_अगरace_net_attr(ipv6_अगरace, traffic_class,
		     ISCSI_NET_PARAM_IPV6_TRAFFIC_CLASS);
iscsi_अगरace_net_attr(ipv6_अगरace, hop_limit, ISCSI_NET_PARAM_IPV6_HOP_LIMIT);
iscsi_अगरace_net_attr(ipv6_अगरace, nd_reachable_पंचांगo,
		     ISCSI_NET_PARAM_IPV6_ND_REACHABLE_TMO);
iscsi_अगरace_net_attr(ipv6_अगरace, nd_rexmit_समय,
		     ISCSI_NET_PARAM_IPV6_ND_REXMIT_TIME);
iscsi_अगरace_net_attr(ipv6_अगरace, nd_stale_पंचांगo,
		     ISCSI_NET_PARAM_IPV6_ND_STALE_TMO);
iscsi_अगरace_net_attr(ipv6_अगरace, dup_addr_detect_cnt,
		     ISCSI_NET_PARAM_IPV6_DUP_ADDR_DETECT_CNT);
iscsi_अगरace_net_attr(ipv6_अगरace, router_adv_link_mtu,
		     ISCSI_NET_PARAM_IPV6_RTR_ADV_LINK_MTU);

/* common पढ़ो only अगरace attribute */
iscsi_अगरace_net_attr(अगरace, enabled, ISCSI_NET_PARAM_IFACE_ENABLE);
iscsi_अगरace_net_attr(अगरace, vlan_id, ISCSI_NET_PARAM_VLAN_ID);
iscsi_अगरace_net_attr(अगरace, vlan_priority, ISCSI_NET_PARAM_VLAN_PRIORITY);
iscsi_अगरace_net_attr(अगरace, vlan_enabled, ISCSI_NET_PARAM_VLAN_ENABLED);
iscsi_अगरace_net_attr(अगरace, mtu, ISCSI_NET_PARAM_MTU);
iscsi_अगरace_net_attr(अगरace, port, ISCSI_NET_PARAM_PORT);
iscsi_अगरace_net_attr(अगरace, ipaddress_state, ISCSI_NET_PARAM_IPADDR_STATE);
iscsi_अगरace_net_attr(अगरace, delayed_ack_en, ISCSI_NET_PARAM_DELAYED_ACK_EN);
iscsi_अगरace_net_attr(अगरace, tcp_nagle_disable,
		     ISCSI_NET_PARAM_TCP_NAGLE_DISABLE);
iscsi_अगरace_net_attr(अगरace, tcp_wsf_disable, ISCSI_NET_PARAM_TCP_WSF_DISABLE);
iscsi_अगरace_net_attr(अगरace, tcp_wsf, ISCSI_NET_PARAM_TCP_WSF);
iscsi_अगरace_net_attr(अगरace, tcp_समयr_scale, ISCSI_NET_PARAM_TCP_TIMER_SCALE);
iscsi_अगरace_net_attr(अगरace, tcp_बारtamp_en, ISCSI_NET_PARAM_TCP_TIMESTAMP_EN);
iscsi_अगरace_net_attr(अगरace, cache_id, ISCSI_NET_PARAM_CACHE_ID);
iscsi_अगरace_net_attr(अगरace, redirect_en, ISCSI_NET_PARAM_REसूचीECT_EN);

/* common iscsi specअगरic settings attributes */
iscsi_अगरace_attr(अगरace, def_taskmgmt_पंचांगo, ISCSI_IFACE_PARAM_DEF_TASKMGMT_TMO);
iscsi_अगरace_attr(अगरace, header_digest, ISCSI_IFACE_PARAM_HDRDGST_EN);
iscsi_अगरace_attr(अगरace, data_digest, ISCSI_IFACE_PARAM_DATADGST_EN);
iscsi_अगरace_attr(अगरace, immediate_data, ISCSI_IFACE_PARAM_IMM_DATA_EN);
iscsi_अगरace_attr(अगरace, initial_r2t, ISCSI_IFACE_PARAM_INITIAL_R2T_EN);
iscsi_अगरace_attr(अगरace, data_seq_in_order,
		 ISCSI_IFACE_PARAM_DATASEQ_INORDER_EN);
iscsi_अगरace_attr(अगरace, data_pdu_in_order, ISCSI_IFACE_PARAM_PDU_INORDER_EN);
iscsi_अगरace_attr(अगरace, erl, ISCSI_IFACE_PARAM_ERL);
iscsi_अगरace_attr(अगरace, max_recv_dlength, ISCSI_IFACE_PARAM_MAX_RECV_DLENGTH);
iscsi_अगरace_attr(अगरace, first_burst_len, ISCSI_IFACE_PARAM_FIRST_BURST);
iscsi_अगरace_attr(अगरace, max_outstanding_r2t, ISCSI_IFACE_PARAM_MAX_R2T);
iscsi_अगरace_attr(अगरace, max_burst_len, ISCSI_IFACE_PARAM_MAX_BURST);
iscsi_अगरace_attr(अगरace, chap_auth, ISCSI_IFACE_PARAM_CHAP_AUTH_EN);
iscsi_अगरace_attr(अगरace, bidi_chap, ISCSI_IFACE_PARAM_BIDI_CHAP_EN);
iscsi_अगरace_attr(अगरace, discovery_auth_optional,
		 ISCSI_IFACE_PARAM_DISCOVERY_AUTH_OPTIONAL);
iscsi_अगरace_attr(अगरace, discovery_logout,
		 ISCSI_IFACE_PARAM_DISCOVERY_LOGOUT_EN);
iscsi_अगरace_attr(अगरace, strict_login_comp_en,
		 ISCSI_IFACE_PARAM_STRICT_LOGIN_COMP_EN);
iscsi_अगरace_attr(अगरace, initiator_name, ISCSI_IFACE_PARAM_INITIATOR_NAME);

अटल umode_t iscsi_अगरace_attr_is_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा iscsi_अगरace *अगरace = iscsi_dev_to_अगरace(dev);
	काष्ठा iscsi_transport *t = अगरace->transport;
	पूर्णांक param;
	पूर्णांक param_type;

	अगर (attr == &dev_attr_अगरace_enabled.attr)
		param = ISCSI_NET_PARAM_IFACE_ENABLE;
	अन्यथा अगर (attr == &dev_attr_अगरace_vlan_id.attr)
		param = ISCSI_NET_PARAM_VLAN_ID;
	अन्यथा अगर (attr == &dev_attr_अगरace_vlan_priority.attr)
		param = ISCSI_NET_PARAM_VLAN_PRIORITY;
	अन्यथा अगर (attr == &dev_attr_अगरace_vlan_enabled.attr)
		param = ISCSI_NET_PARAM_VLAN_ENABLED;
	अन्यथा अगर (attr == &dev_attr_अगरace_mtu.attr)
		param = ISCSI_NET_PARAM_MTU;
	अन्यथा अगर (attr == &dev_attr_अगरace_port.attr)
		param = ISCSI_NET_PARAM_PORT;
	अन्यथा अगर (attr == &dev_attr_अगरace_ipaddress_state.attr)
		param = ISCSI_NET_PARAM_IPADDR_STATE;
	अन्यथा अगर (attr == &dev_attr_अगरace_delayed_ack_en.attr)
		param = ISCSI_NET_PARAM_DELAYED_ACK_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_tcp_nagle_disable.attr)
		param = ISCSI_NET_PARAM_TCP_NAGLE_DISABLE;
	अन्यथा अगर (attr == &dev_attr_अगरace_tcp_wsf_disable.attr)
		param = ISCSI_NET_PARAM_TCP_WSF_DISABLE;
	अन्यथा अगर (attr == &dev_attr_अगरace_tcp_wsf.attr)
		param = ISCSI_NET_PARAM_TCP_WSF;
	अन्यथा अगर (attr == &dev_attr_अगरace_tcp_समयr_scale.attr)
		param = ISCSI_NET_PARAM_TCP_TIMER_SCALE;
	अन्यथा अगर (attr == &dev_attr_अगरace_tcp_बारtamp_en.attr)
		param = ISCSI_NET_PARAM_TCP_TIMESTAMP_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_cache_id.attr)
		param = ISCSI_NET_PARAM_CACHE_ID;
	अन्यथा अगर (attr == &dev_attr_अगरace_redirect_en.attr)
		param = ISCSI_NET_PARAM_REसूचीECT_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_def_taskmgmt_पंचांगo.attr)
		param = ISCSI_IFACE_PARAM_DEF_TASKMGMT_TMO;
	अन्यथा अगर (attr == &dev_attr_अगरace_header_digest.attr)
		param = ISCSI_IFACE_PARAM_HDRDGST_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_data_digest.attr)
		param = ISCSI_IFACE_PARAM_DATADGST_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_immediate_data.attr)
		param = ISCSI_IFACE_PARAM_IMM_DATA_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_initial_r2t.attr)
		param = ISCSI_IFACE_PARAM_INITIAL_R2T_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_data_seq_in_order.attr)
		param = ISCSI_IFACE_PARAM_DATASEQ_INORDER_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_data_pdu_in_order.attr)
		param = ISCSI_IFACE_PARAM_PDU_INORDER_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_erl.attr)
		param = ISCSI_IFACE_PARAM_ERL;
	अन्यथा अगर (attr == &dev_attr_अगरace_max_recv_dlength.attr)
		param = ISCSI_IFACE_PARAM_MAX_RECV_DLENGTH;
	अन्यथा अगर (attr == &dev_attr_अगरace_first_burst_len.attr)
		param = ISCSI_IFACE_PARAM_FIRST_BURST;
	अन्यथा अगर (attr == &dev_attr_अगरace_max_outstanding_r2t.attr)
		param = ISCSI_IFACE_PARAM_MAX_R2T;
	अन्यथा अगर (attr == &dev_attr_अगरace_max_burst_len.attr)
		param = ISCSI_IFACE_PARAM_MAX_BURST;
	अन्यथा अगर (attr == &dev_attr_अगरace_chap_auth.attr)
		param = ISCSI_IFACE_PARAM_CHAP_AUTH_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_bidi_chap.attr)
		param = ISCSI_IFACE_PARAM_BIDI_CHAP_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_discovery_auth_optional.attr)
		param = ISCSI_IFACE_PARAM_DISCOVERY_AUTH_OPTIONAL;
	अन्यथा अगर (attr == &dev_attr_अगरace_discovery_logout.attr)
		param = ISCSI_IFACE_PARAM_DISCOVERY_LOGOUT_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_strict_login_comp_en.attr)
		param = ISCSI_IFACE_PARAM_STRICT_LOGIN_COMP_EN;
	अन्यथा अगर (attr == &dev_attr_अगरace_initiator_name.attr)
		param = ISCSI_IFACE_PARAM_INITIATOR_NAME;
	अन्यथा अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4) अणु
		अगर (attr == &dev_attr_ipv4_अगरace_ipaddress.attr)
			param = ISCSI_NET_PARAM_IPV4_ADDR;
		अन्यथा अगर (attr == &dev_attr_ipv4_अगरace_gateway.attr)
			param = ISCSI_NET_PARAM_IPV4_GW;
		अन्यथा अगर (attr == &dev_attr_ipv4_अगरace_subnet.attr)
			param = ISCSI_NET_PARAM_IPV4_SUBNET;
		अन्यथा अगर (attr == &dev_attr_ipv4_अगरace_bootproto.attr)
			param = ISCSI_NET_PARAM_IPV4_BOOTPROTO;
		अन्यथा अगर (attr ==
			 &dev_attr_ipv4_अगरace_dhcp_dns_address_en.attr)
			param = ISCSI_NET_PARAM_IPV4_DHCP_DNS_ADDR_EN;
		अन्यथा अगर (attr ==
			 &dev_attr_ipv4_अगरace_dhcp_slp_da_info_en.attr)
			param = ISCSI_NET_PARAM_IPV4_DHCP_SLP_DA_EN;
		अन्यथा अगर (attr == &dev_attr_ipv4_अगरace_tos_en.attr)
			param = ISCSI_NET_PARAM_IPV4_TOS_EN;
		अन्यथा अगर (attr == &dev_attr_ipv4_अगरace_tos.attr)
			param = ISCSI_NET_PARAM_IPV4_TOS;
		अन्यथा अगर (attr == &dev_attr_ipv4_अगरace_grat_arp_en.attr)
			param = ISCSI_NET_PARAM_IPV4_GRAT_ARP_EN;
		अन्यथा अगर (attr ==
			 &dev_attr_ipv4_अगरace_dhcp_alt_client_id_en.attr)
			param = ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID_EN;
		अन्यथा अगर (attr == &dev_attr_ipv4_अगरace_dhcp_alt_client_id.attr)
			param = ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID;
		अन्यथा अगर (attr ==
			 &dev_attr_ipv4_अगरace_dhcp_req_venकरोr_id_en.attr)
			param = ISCSI_NET_PARAM_IPV4_DHCP_REQ_VENDOR_ID_EN;
		अन्यथा अगर (attr ==
			 &dev_attr_ipv4_अगरace_dhcp_use_venकरोr_id_en.attr)
			param = ISCSI_NET_PARAM_IPV4_DHCP_USE_VENDOR_ID_EN;
		अन्यथा अगर (attr == &dev_attr_ipv4_अगरace_dhcp_venकरोr_id.attr)
			param = ISCSI_NET_PARAM_IPV4_DHCP_VENDOR_ID;
		अन्यथा अगर (attr ==
			 &dev_attr_ipv4_अगरace_dhcp_learn_iqn_en.attr)
			param = ISCSI_NET_PARAM_IPV4_DHCP_LEARN_IQN_EN;
		अन्यथा अगर (attr ==
			 &dev_attr_ipv4_अगरace_fragment_disable.attr)
			param = ISCSI_NET_PARAM_IPV4_FRAGMENT_DISABLE;
		अन्यथा अगर (attr ==
			 &dev_attr_ipv4_अगरace_incoming_क्रमwarding_en.attr)
			param = ISCSI_NET_PARAM_IPV4_IN_FORWARD_EN;
		अन्यथा अगर (attr == &dev_attr_ipv4_अगरace_ttl.attr)
			param = ISCSI_NET_PARAM_IPV4_TTL;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV6) अणु
		अगर (attr == &dev_attr_ipv6_अगरace_ipaddress.attr)
			param = ISCSI_NET_PARAM_IPV6_ADDR;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_link_local_addr.attr)
			param = ISCSI_NET_PARAM_IPV6_LINKLOCAL;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_router_addr.attr)
			param = ISCSI_NET_PARAM_IPV6_ROUTER;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_ipaddr_स्वतःcfg.attr)
			param = ISCSI_NET_PARAM_IPV6_ADDR_AUTOCFG;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_link_local_स्वतःcfg.attr)
			param = ISCSI_NET_PARAM_IPV6_LINKLOCAL_AUTOCFG;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_link_local_state.attr)
			param = ISCSI_NET_PARAM_IPV6_LINKLOCAL_STATE;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_router_state.attr)
			param = ISCSI_NET_PARAM_IPV6_ROUTER_STATE;
		अन्यथा अगर (attr ==
			 &dev_attr_ipv6_अगरace_grat_neighbor_adv_en.attr)
			param = ISCSI_NET_PARAM_IPV6_GRAT_NEIGHBOR_ADV_EN;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_mld_en.attr)
			param = ISCSI_NET_PARAM_IPV6_MLD_EN;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_flow_label.attr)
			param = ISCSI_NET_PARAM_IPV6_FLOW_LABEL;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_traffic_class.attr)
			param = ISCSI_NET_PARAM_IPV6_TRAFFIC_CLASS;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_hop_limit.attr)
			param = ISCSI_NET_PARAM_IPV6_HOP_LIMIT;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_nd_reachable_पंचांगo.attr)
			param = ISCSI_NET_PARAM_IPV6_ND_REACHABLE_TMO;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_nd_rexmit_समय.attr)
			param = ISCSI_NET_PARAM_IPV6_ND_REXMIT_TIME;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_nd_stale_पंचांगo.attr)
			param = ISCSI_NET_PARAM_IPV6_ND_STALE_TMO;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_dup_addr_detect_cnt.attr)
			param = ISCSI_NET_PARAM_IPV6_DUP_ADDR_DETECT_CNT;
		अन्यथा अगर (attr == &dev_attr_ipv6_अगरace_router_adv_link_mtu.attr)
			param = ISCSI_NET_PARAM_IPV6_RTR_ADV_LINK_MTU;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "Invalid iface attr");
		वापस 0;
	पूर्ण

	चयन (param) अणु
	हाल ISCSI_IFACE_PARAM_DEF_TASKMGMT_TMO:
	हाल ISCSI_IFACE_PARAM_HDRDGST_EN:
	हाल ISCSI_IFACE_PARAM_DATADGST_EN:
	हाल ISCSI_IFACE_PARAM_IMM_DATA_EN:
	हाल ISCSI_IFACE_PARAM_INITIAL_R2T_EN:
	हाल ISCSI_IFACE_PARAM_DATASEQ_INORDER_EN:
	हाल ISCSI_IFACE_PARAM_PDU_INORDER_EN:
	हाल ISCSI_IFACE_PARAM_ERL:
	हाल ISCSI_IFACE_PARAM_MAX_RECV_DLENGTH:
	हाल ISCSI_IFACE_PARAM_FIRST_BURST:
	हाल ISCSI_IFACE_PARAM_MAX_R2T:
	हाल ISCSI_IFACE_PARAM_MAX_BURST:
	हाल ISCSI_IFACE_PARAM_CHAP_AUTH_EN:
	हाल ISCSI_IFACE_PARAM_BIDI_CHAP_EN:
	हाल ISCSI_IFACE_PARAM_DISCOVERY_AUTH_OPTIONAL:
	हाल ISCSI_IFACE_PARAM_DISCOVERY_LOGOUT_EN:
	हाल ISCSI_IFACE_PARAM_STRICT_LOGIN_COMP_EN:
	हाल ISCSI_IFACE_PARAM_INITIATOR_NAME:
		param_type = ISCSI_IFACE_PARAM;
		अवरोध;
	शेष:
		param_type = ISCSI_NET_PARAM;
	पूर्ण

	वापस t->attr_is_visible(param_type, param);
पूर्ण

अटल काष्ठा attribute *iscsi_अगरace_attrs[] = अणु
	&dev_attr_अगरace_enabled.attr,
	&dev_attr_अगरace_vlan_id.attr,
	&dev_attr_अगरace_vlan_priority.attr,
	&dev_attr_अगरace_vlan_enabled.attr,
	&dev_attr_ipv4_अगरace_ipaddress.attr,
	&dev_attr_ipv4_अगरace_gateway.attr,
	&dev_attr_ipv4_अगरace_subnet.attr,
	&dev_attr_ipv4_अगरace_bootproto.attr,
	&dev_attr_ipv6_अगरace_ipaddress.attr,
	&dev_attr_ipv6_अगरace_link_local_addr.attr,
	&dev_attr_ipv6_अगरace_router_addr.attr,
	&dev_attr_ipv6_अगरace_ipaddr_स्वतःcfg.attr,
	&dev_attr_ipv6_अगरace_link_local_स्वतःcfg.attr,
	&dev_attr_अगरace_mtu.attr,
	&dev_attr_अगरace_port.attr,
	&dev_attr_अगरace_ipaddress_state.attr,
	&dev_attr_अगरace_delayed_ack_en.attr,
	&dev_attr_अगरace_tcp_nagle_disable.attr,
	&dev_attr_अगरace_tcp_wsf_disable.attr,
	&dev_attr_अगरace_tcp_wsf.attr,
	&dev_attr_अगरace_tcp_समयr_scale.attr,
	&dev_attr_अगरace_tcp_बारtamp_en.attr,
	&dev_attr_अगरace_cache_id.attr,
	&dev_attr_अगरace_redirect_en.attr,
	&dev_attr_अगरace_def_taskmgmt_पंचांगo.attr,
	&dev_attr_अगरace_header_digest.attr,
	&dev_attr_अगरace_data_digest.attr,
	&dev_attr_अगरace_immediate_data.attr,
	&dev_attr_अगरace_initial_r2t.attr,
	&dev_attr_अगरace_data_seq_in_order.attr,
	&dev_attr_अगरace_data_pdu_in_order.attr,
	&dev_attr_अगरace_erl.attr,
	&dev_attr_अगरace_max_recv_dlength.attr,
	&dev_attr_अगरace_first_burst_len.attr,
	&dev_attr_अगरace_max_outstanding_r2t.attr,
	&dev_attr_अगरace_max_burst_len.attr,
	&dev_attr_अगरace_chap_auth.attr,
	&dev_attr_अगरace_bidi_chap.attr,
	&dev_attr_अगरace_discovery_auth_optional.attr,
	&dev_attr_अगरace_discovery_logout.attr,
	&dev_attr_अगरace_strict_login_comp_en.attr,
	&dev_attr_अगरace_initiator_name.attr,
	&dev_attr_ipv4_अगरace_dhcp_dns_address_en.attr,
	&dev_attr_ipv4_अगरace_dhcp_slp_da_info_en.attr,
	&dev_attr_ipv4_अगरace_tos_en.attr,
	&dev_attr_ipv4_अगरace_tos.attr,
	&dev_attr_ipv4_अगरace_grat_arp_en.attr,
	&dev_attr_ipv4_अगरace_dhcp_alt_client_id_en.attr,
	&dev_attr_ipv4_अगरace_dhcp_alt_client_id.attr,
	&dev_attr_ipv4_अगरace_dhcp_req_venकरोr_id_en.attr,
	&dev_attr_ipv4_अगरace_dhcp_use_venकरोr_id_en.attr,
	&dev_attr_ipv4_अगरace_dhcp_venकरोr_id.attr,
	&dev_attr_ipv4_अगरace_dhcp_learn_iqn_en.attr,
	&dev_attr_ipv4_अगरace_fragment_disable.attr,
	&dev_attr_ipv4_अगरace_incoming_क्रमwarding_en.attr,
	&dev_attr_ipv4_अगरace_ttl.attr,
	&dev_attr_ipv6_अगरace_link_local_state.attr,
	&dev_attr_ipv6_अगरace_router_state.attr,
	&dev_attr_ipv6_अगरace_grat_neighbor_adv_en.attr,
	&dev_attr_ipv6_अगरace_mld_en.attr,
	&dev_attr_ipv6_अगरace_flow_label.attr,
	&dev_attr_ipv6_अगरace_traffic_class.attr,
	&dev_attr_ipv6_अगरace_hop_limit.attr,
	&dev_attr_ipv6_अगरace_nd_reachable_पंचांगo.attr,
	&dev_attr_ipv6_अगरace_nd_rexmit_समय.attr,
	&dev_attr_ipv6_अगरace_nd_stale_पंचांगo.attr,
	&dev_attr_ipv6_अगरace_dup_addr_detect_cnt.attr,
	&dev_attr_ipv6_अगरace_router_adv_link_mtu.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group iscsi_अगरace_group = अणु
	.attrs = iscsi_अगरace_attrs,
	.is_visible = iscsi_अगरace_attr_is_visible,
पूर्ण;

/* convert iscsi_ipaddress_state values to ascii string name */
अटल स्थिर काष्ठा अणु
	क्रमागत iscsi_ipaddress_state	value;
	अक्षर				*name;
पूर्ण iscsi_ipaddress_state_names[] = अणु
	अणुISCSI_IPDDRESS_STATE_UNCONFIGURED,	"Unconfigured" पूर्ण,
	अणुISCSI_IPDDRESS_STATE_ACQUIRING,	"Acquiring" पूर्ण,
	अणुISCSI_IPDDRESS_STATE_TENTATIVE,	"Tentative" पूर्ण,
	अणुISCSI_IPDDRESS_STATE_VALID,		"Valid" पूर्ण,
	अणुISCSI_IPDDRESS_STATE_DISABLING,	"Disabling" पूर्ण,
	अणुISCSI_IPDDRESS_STATE_INVALID,		"Invalid" पूर्ण,
	अणुISCSI_IPDDRESS_STATE_DEPRECATED,	"Deprecated" पूर्ण,
पूर्ण;

अक्षर *iscsi_get_ipaddress_state_name(क्रमागत iscsi_ipaddress_state port_state)
अणु
	पूर्णांक i;
	अक्षर *state = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(iscsi_ipaddress_state_names); i++) अणु
		अगर (iscsi_ipaddress_state_names[i].value == port_state) अणु
			state = iscsi_ipaddress_state_names[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_get_ipaddress_state_name);

/* convert iscsi_router_state values to ascii string name */
अटल स्थिर काष्ठा अणु
	क्रमागत iscsi_router_state	value;
	अक्षर			*name;
पूर्ण iscsi_router_state_names[] = अणु
	अणुISCSI_ROUTER_STATE_UNKNOWN,		"Unknown" पूर्ण,
	अणुISCSI_ROUTER_STATE_ADVERTISED,		"Advertised" पूर्ण,
	अणुISCSI_ROUTER_STATE_MANUAL,		"Manual" पूर्ण,
	अणुISCSI_ROUTER_STATE_STALE,		"Stale" पूर्ण,
पूर्ण;

अक्षर *iscsi_get_router_state_name(क्रमागत iscsi_router_state router_state)
अणु
	पूर्णांक i;
	अक्षर *state = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(iscsi_router_state_names); i++) अणु
		अगर (iscsi_router_state_names[i].value == router_state) अणु
			state = iscsi_router_state_names[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_get_router_state_name);

काष्ठा iscsi_अगरace *
iscsi_create_अगरace(काष्ठा Scsi_Host *shost, काष्ठा iscsi_transport *transport,
		   uपूर्णांक32_t अगरace_type, uपूर्णांक32_t अगरace_num, पूर्णांक dd_size)
अणु
	काष्ठा iscsi_अगरace *अगरace;
	पूर्णांक err;

	अगरace = kzalloc(माप(*अगरace) + dd_size, GFP_KERNEL);
	अगर (!अगरace)
		वापस शून्य;

	अगरace->transport = transport;
	अगरace->अगरace_type = अगरace_type;
	अगरace->अगरace_num = अगरace_num;
	अगरace->dev.release = iscsi_अगरace_release;
	अगरace->dev.class = &iscsi_अगरace_class;
	/* parent reference released in iscsi_अगरace_release */
	अगरace->dev.parent = get_device(&shost->shost_gendev);
	अगर (अगरace_type == ISCSI_IFACE_TYPE_IPV4)
		dev_set_name(&अगरace->dev, "ipv4-iface-%u-%u", shost->host_no,
			     अगरace_num);
	अन्यथा
		dev_set_name(&अगरace->dev, "ipv6-iface-%u-%u", shost->host_no,
			     अगरace_num);

	err = device_रेजिस्टर(&अगरace->dev);
	अगर (err)
		जाओ मुक्त_अगरace;

	err = sysfs_create_group(&अगरace->dev.kobj, &iscsi_अगरace_group);
	अगर (err)
		जाओ unreg_अगरace;

	अगर (dd_size)
		अगरace->dd_data = &अगरace[1];
	वापस अगरace;

unreg_अगरace:
	device_unरेजिस्टर(&अगरace->dev);
	वापस शून्य;

मुक्त_अगरace:
	put_device(अगरace->dev.parent);
	kमुक्त(अगरace);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_create_अगरace);

व्योम iscsi_destroy_अगरace(काष्ठा iscsi_अगरace *अगरace)
अणु
	sysfs_हटाओ_group(&अगरace->dev.kobj, &iscsi_अगरace_group);
	device_unरेजिस्टर(&अगरace->dev);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_destroy_अगरace);

/*
 * Interface to display flash node params to sysfs
 */

#घोषणा ISCSI_FLASHNODE_ATTR(_prefix, _name, _mode, _show, _store)	\
काष्ठा device_attribute dev_attr_##_prefix##_##_name =			\
	__ATTR(_name, _mode, _show, _store)

/* flash node session attrs show */
#घोषणा iscsi_flashnode_sess_attr_show(type, name, param)		\
अटल sमाप_प्रकार								\
show_##type##_##name(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		     अक्षर *buf)						\
अणु									\
	काष्ठा iscsi_bus_flash_session *fnode_sess =			\
					iscsi_dev_to_flash_session(dev);\
	काष्ठा iscsi_transport *t = fnode_sess->transport;		\
	वापस t->get_flashnode_param(fnode_sess, param, buf);		\
पूर्ण									\


#घोषणा iscsi_flashnode_sess_attr(type, name, param)			\
	iscsi_flashnode_sess_attr_show(type, name, param)		\
अटल ISCSI_FLASHNODE_ATTR(type, name, S_IRUGO,			\
			    show_##type##_##name, शून्य);

/* Flash node session attributes */

iscsi_flashnode_sess_attr(fnode, स्वतः_snd_tgt_disable,
			  ISCSI_FLASHNODE_AUTO_SND_TGT_DISABLE);
iscsi_flashnode_sess_attr(fnode, discovery_session,
			  ISCSI_FLASHNODE_DISCOVERY_SESS);
iscsi_flashnode_sess_attr(fnode, portal_type, ISCSI_FLASHNODE_PORTAL_TYPE);
iscsi_flashnode_sess_attr(fnode, entry_enable, ISCSI_FLASHNODE_ENTRY_EN);
iscsi_flashnode_sess_attr(fnode, immediate_data, ISCSI_FLASHNODE_IMM_DATA_EN);
iscsi_flashnode_sess_attr(fnode, initial_r2t, ISCSI_FLASHNODE_INITIAL_R2T_EN);
iscsi_flashnode_sess_attr(fnode, data_seq_in_order,
			  ISCSI_FLASHNODE_DATASEQ_INORDER);
iscsi_flashnode_sess_attr(fnode, data_pdu_in_order,
			  ISCSI_FLASHNODE_PDU_INORDER);
iscsi_flashnode_sess_attr(fnode, chap_auth, ISCSI_FLASHNODE_CHAP_AUTH_EN);
iscsi_flashnode_sess_attr(fnode, discovery_logout,
			  ISCSI_FLASHNODE_DISCOVERY_LOGOUT_EN);
iscsi_flashnode_sess_attr(fnode, bidi_chap, ISCSI_FLASHNODE_BIDI_CHAP_EN);
iscsi_flashnode_sess_attr(fnode, discovery_auth_optional,
			  ISCSI_FLASHNODE_DISCOVERY_AUTH_OPTIONAL);
iscsi_flashnode_sess_attr(fnode, erl, ISCSI_FLASHNODE_ERL);
iscsi_flashnode_sess_attr(fnode, first_burst_len, ISCSI_FLASHNODE_FIRST_BURST);
iscsi_flashnode_sess_attr(fnode, def_समय2रुको, ISCSI_FLASHNODE_DEF_TIME2WAIT);
iscsi_flashnode_sess_attr(fnode, def_समय2retain,
			  ISCSI_FLASHNODE_DEF_TIME2RETAIN);
iscsi_flashnode_sess_attr(fnode, max_outstanding_r2t, ISCSI_FLASHNODE_MAX_R2T);
iscsi_flashnode_sess_attr(fnode, isid, ISCSI_FLASHNODE_ISID);
iscsi_flashnode_sess_attr(fnode, tsid, ISCSI_FLASHNODE_TSID);
iscsi_flashnode_sess_attr(fnode, max_burst_len, ISCSI_FLASHNODE_MAX_BURST);
iscsi_flashnode_sess_attr(fnode, def_taskmgmt_पंचांगo,
			  ISCSI_FLASHNODE_DEF_TASKMGMT_TMO);
iscsi_flashnode_sess_attr(fnode, targetalias, ISCSI_FLASHNODE_ALIAS);
iscsi_flashnode_sess_attr(fnode, targetname, ISCSI_FLASHNODE_NAME);
iscsi_flashnode_sess_attr(fnode, tpgt, ISCSI_FLASHNODE_TPGT);
iscsi_flashnode_sess_attr(fnode, discovery_parent_idx,
			  ISCSI_FLASHNODE_DISCOVERY_PARENT_IDX);
iscsi_flashnode_sess_attr(fnode, discovery_parent_type,
			  ISCSI_FLASHNODE_DISCOVERY_PARENT_TYPE);
iscsi_flashnode_sess_attr(fnode, chap_in_idx, ISCSI_FLASHNODE_CHAP_IN_IDX);
iscsi_flashnode_sess_attr(fnode, chap_out_idx, ISCSI_FLASHNODE_CHAP_OUT_IDX);
iscsi_flashnode_sess_attr(fnode, username, ISCSI_FLASHNODE_USERNAME);
iscsi_flashnode_sess_attr(fnode, username_in, ISCSI_FLASHNODE_USERNAME_IN);
iscsi_flashnode_sess_attr(fnode, password, ISCSI_FLASHNODE_PASSWORD);
iscsi_flashnode_sess_attr(fnode, password_in, ISCSI_FLASHNODE_PASSWORD_IN);
iscsi_flashnode_sess_attr(fnode, is_boot_target, ISCSI_FLASHNODE_IS_BOOT_TGT);

अटल काष्ठा attribute *iscsi_flashnode_sess_attrs[] = अणु
	&dev_attr_fnode_स्वतः_snd_tgt_disable.attr,
	&dev_attr_fnode_discovery_session.attr,
	&dev_attr_fnode_portal_type.attr,
	&dev_attr_fnode_entry_enable.attr,
	&dev_attr_fnode_immediate_data.attr,
	&dev_attr_fnode_initial_r2t.attr,
	&dev_attr_fnode_data_seq_in_order.attr,
	&dev_attr_fnode_data_pdu_in_order.attr,
	&dev_attr_fnode_chap_auth.attr,
	&dev_attr_fnode_discovery_logout.attr,
	&dev_attr_fnode_bidi_chap.attr,
	&dev_attr_fnode_discovery_auth_optional.attr,
	&dev_attr_fnode_erl.attr,
	&dev_attr_fnode_first_burst_len.attr,
	&dev_attr_fnode_def_समय2रुको.attr,
	&dev_attr_fnode_def_समय2retain.attr,
	&dev_attr_fnode_max_outstanding_r2t.attr,
	&dev_attr_fnode_isid.attr,
	&dev_attr_fnode_tsid.attr,
	&dev_attr_fnode_max_burst_len.attr,
	&dev_attr_fnode_def_taskmgmt_पंचांगo.attr,
	&dev_attr_fnode_targetalias.attr,
	&dev_attr_fnode_targetname.attr,
	&dev_attr_fnode_tpgt.attr,
	&dev_attr_fnode_discovery_parent_idx.attr,
	&dev_attr_fnode_discovery_parent_type.attr,
	&dev_attr_fnode_chap_in_idx.attr,
	&dev_attr_fnode_chap_out_idx.attr,
	&dev_attr_fnode_username.attr,
	&dev_attr_fnode_username_in.attr,
	&dev_attr_fnode_password.attr,
	&dev_attr_fnode_password_in.attr,
	&dev_attr_fnode_is_boot_target.attr,
	शून्य,
पूर्ण;

अटल umode_t iscsi_flashnode_sess_attr_is_visible(काष्ठा kobject *kobj,
						    काष्ठा attribute *attr,
						    पूर्णांक i)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा iscsi_bus_flash_session *fnode_sess =
						iscsi_dev_to_flash_session(dev);
	काष्ठा iscsi_transport *t = fnode_sess->transport;
	पूर्णांक param;

	अगर (attr == &dev_attr_fnode_स्वतः_snd_tgt_disable.attr) अणु
		param = ISCSI_FLASHNODE_AUTO_SND_TGT_DISABLE;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_discovery_session.attr) अणु
		param = ISCSI_FLASHNODE_DISCOVERY_SESS;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_portal_type.attr) अणु
		param = ISCSI_FLASHNODE_PORTAL_TYPE;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_entry_enable.attr) अणु
		param = ISCSI_FLASHNODE_ENTRY_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_immediate_data.attr) अणु
		param = ISCSI_FLASHNODE_IMM_DATA_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_initial_r2t.attr) अणु
		param = ISCSI_FLASHNODE_INITIAL_R2T_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_data_seq_in_order.attr) अणु
		param = ISCSI_FLASHNODE_DATASEQ_INORDER;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_data_pdu_in_order.attr) अणु
		param = ISCSI_FLASHNODE_PDU_INORDER;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_chap_auth.attr) अणु
		param = ISCSI_FLASHNODE_CHAP_AUTH_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_discovery_logout.attr) अणु
		param = ISCSI_FLASHNODE_DISCOVERY_LOGOUT_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_bidi_chap.attr) अणु
		param = ISCSI_FLASHNODE_BIDI_CHAP_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_discovery_auth_optional.attr) अणु
		param = ISCSI_FLASHNODE_DISCOVERY_AUTH_OPTIONAL;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_erl.attr) अणु
		param = ISCSI_FLASHNODE_ERL;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_first_burst_len.attr) अणु
		param = ISCSI_FLASHNODE_FIRST_BURST;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_def_समय2रुको.attr) अणु
		param = ISCSI_FLASHNODE_DEF_TIME2WAIT;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_def_समय2retain.attr) अणु
		param = ISCSI_FLASHNODE_DEF_TIME2RETAIN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_max_outstanding_r2t.attr) अणु
		param = ISCSI_FLASHNODE_MAX_R2T;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_isid.attr) अणु
		param = ISCSI_FLASHNODE_ISID;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_tsid.attr) अणु
		param = ISCSI_FLASHNODE_TSID;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_max_burst_len.attr) अणु
		param = ISCSI_FLASHNODE_MAX_BURST;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_def_taskmgmt_पंचांगo.attr) अणु
		param = ISCSI_FLASHNODE_DEF_TASKMGMT_TMO;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_targetalias.attr) अणु
		param = ISCSI_FLASHNODE_ALIAS;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_targetname.attr) अणु
		param = ISCSI_FLASHNODE_NAME;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_tpgt.attr) अणु
		param = ISCSI_FLASHNODE_TPGT;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_discovery_parent_idx.attr) अणु
		param = ISCSI_FLASHNODE_DISCOVERY_PARENT_IDX;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_discovery_parent_type.attr) अणु
		param = ISCSI_FLASHNODE_DISCOVERY_PARENT_TYPE;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_chap_in_idx.attr) अणु
		param = ISCSI_FLASHNODE_CHAP_IN_IDX;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_chap_out_idx.attr) अणु
		param = ISCSI_FLASHNODE_CHAP_OUT_IDX;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_username.attr) अणु
		param = ISCSI_FLASHNODE_USERNAME;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_username_in.attr) अणु
		param = ISCSI_FLASHNODE_USERNAME_IN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_password.attr) अणु
		param = ISCSI_FLASHNODE_PASSWORD;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_password_in.attr) अणु
		param = ISCSI_FLASHNODE_PASSWORD_IN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_is_boot_target.attr) अणु
		param = ISCSI_FLASHNODE_IS_BOOT_TGT;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "Invalid flashnode session attr");
		वापस 0;
	पूर्ण

	वापस t->attr_is_visible(ISCSI_FLASHNODE_PARAM, param);
पूर्ण

अटल काष्ठा attribute_group iscsi_flashnode_sess_attr_group = अणु
	.attrs = iscsi_flashnode_sess_attrs,
	.is_visible = iscsi_flashnode_sess_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *iscsi_flashnode_sess_attr_groups[] = अणु
	&iscsi_flashnode_sess_attr_group,
	शून्य,
पूर्ण;

अटल व्योम iscsi_flashnode_sess_release(काष्ठा device *dev)
अणु
	काष्ठा iscsi_bus_flash_session *fnode_sess =
						iscsi_dev_to_flash_session(dev);

	kमुक्त(fnode_sess->targetname);
	kमुक्त(fnode_sess->targetalias);
	kमुक्त(fnode_sess->portal_type);
	kमुक्त(fnode_sess);
पूर्ण

अटल स्थिर काष्ठा device_type iscsi_flashnode_sess_dev_type = अणु
	.name = "iscsi_flashnode_sess_dev_type",
	.groups = iscsi_flashnode_sess_attr_groups,
	.release = iscsi_flashnode_sess_release,
पूर्ण;

/* flash node connection attrs show */
#घोषणा iscsi_flashnode_conn_attr_show(type, name, param)		\
अटल sमाप_प्रकार								\
show_##type##_##name(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		     अक्षर *buf)						\
अणु									\
	काष्ठा iscsi_bus_flash_conn *fnode_conn = iscsi_dev_to_flash_conn(dev);\
	काष्ठा iscsi_bus_flash_session *fnode_sess =			\
				iscsi_flash_conn_to_flash_session(fnode_conn);\
	काष्ठा iscsi_transport *t = fnode_conn->transport;		\
	वापस t->get_flashnode_param(fnode_sess, param, buf);		\
पूर्ण									\


#घोषणा iscsi_flashnode_conn_attr(type, name, param)			\
	iscsi_flashnode_conn_attr_show(type, name, param)		\
अटल ISCSI_FLASHNODE_ATTR(type, name, S_IRUGO,			\
			    show_##type##_##name, शून्य);

/* Flash node connection attributes */

iscsi_flashnode_conn_attr(fnode, is_fw_asचिन्हित_ipv6,
			  ISCSI_FLASHNODE_IS_FW_ASSIGNED_IPV6);
iscsi_flashnode_conn_attr(fnode, header_digest, ISCSI_FLASHNODE_HDR_DGST_EN);
iscsi_flashnode_conn_attr(fnode, data_digest, ISCSI_FLASHNODE_DATA_DGST_EN);
iscsi_flashnode_conn_attr(fnode, snack_req, ISCSI_FLASHNODE_SNACK_REQ_EN);
iscsi_flashnode_conn_attr(fnode, tcp_बारtamp_stat,
			  ISCSI_FLASHNODE_TCP_TIMESTAMP_STAT);
iscsi_flashnode_conn_attr(fnode, tcp_nagle_disable,
			  ISCSI_FLASHNODE_TCP_NAGLE_DISABLE);
iscsi_flashnode_conn_attr(fnode, tcp_wsf_disable,
			  ISCSI_FLASHNODE_TCP_WSF_DISABLE);
iscsi_flashnode_conn_attr(fnode, tcp_समयr_scale,
			  ISCSI_FLASHNODE_TCP_TIMER_SCALE);
iscsi_flashnode_conn_attr(fnode, tcp_बारtamp_enable,
			  ISCSI_FLASHNODE_TCP_TIMESTAMP_EN);
iscsi_flashnode_conn_attr(fnode, fragment_disable,
			  ISCSI_FLASHNODE_IP_FRAG_DISABLE);
iscsi_flashnode_conn_attr(fnode, keepalive_पंचांगo, ISCSI_FLASHNODE_KEEPALIVE_TMO);
iscsi_flashnode_conn_attr(fnode, port, ISCSI_FLASHNODE_PORT);
iscsi_flashnode_conn_attr(fnode, ipaddress, ISCSI_FLASHNODE_IPADDR);
iscsi_flashnode_conn_attr(fnode, max_recv_dlength,
			  ISCSI_FLASHNODE_MAX_RECV_DLENGTH);
iscsi_flashnode_conn_attr(fnode, max_xmit_dlength,
			  ISCSI_FLASHNODE_MAX_XMIT_DLENGTH);
iscsi_flashnode_conn_attr(fnode, local_port, ISCSI_FLASHNODE_LOCAL_PORT);
iscsi_flashnode_conn_attr(fnode, ipv4_tos, ISCSI_FLASHNODE_IPV4_TOS);
iscsi_flashnode_conn_attr(fnode, ipv6_traffic_class, ISCSI_FLASHNODE_IPV6_TC);
iscsi_flashnode_conn_attr(fnode, ipv6_flow_label,
			  ISCSI_FLASHNODE_IPV6_FLOW_LABEL);
iscsi_flashnode_conn_attr(fnode, redirect_ipaddr,
			  ISCSI_FLASHNODE_REसूचीECT_IPADDR);
iscsi_flashnode_conn_attr(fnode, max_segment_size,
			  ISCSI_FLASHNODE_MAX_SEGMENT_SIZE);
iscsi_flashnode_conn_attr(fnode, link_local_ipv6,
			  ISCSI_FLASHNODE_LINK_LOCAL_IPV6);
iscsi_flashnode_conn_attr(fnode, tcp_xmit_wsf, ISCSI_FLASHNODE_TCP_XMIT_WSF);
iscsi_flashnode_conn_attr(fnode, tcp_recv_wsf, ISCSI_FLASHNODE_TCP_RECV_WSF);
iscsi_flashnode_conn_attr(fnode, statsn, ISCSI_FLASHNODE_STATSN);
iscsi_flashnode_conn_attr(fnode, exp_statsn, ISCSI_FLASHNODE_EXP_STATSN);

अटल काष्ठा attribute *iscsi_flashnode_conn_attrs[] = अणु
	&dev_attr_fnode_is_fw_asचिन्हित_ipv6.attr,
	&dev_attr_fnode_header_digest.attr,
	&dev_attr_fnode_data_digest.attr,
	&dev_attr_fnode_snack_req.attr,
	&dev_attr_fnode_tcp_बारtamp_stat.attr,
	&dev_attr_fnode_tcp_nagle_disable.attr,
	&dev_attr_fnode_tcp_wsf_disable.attr,
	&dev_attr_fnode_tcp_समयr_scale.attr,
	&dev_attr_fnode_tcp_बारtamp_enable.attr,
	&dev_attr_fnode_fragment_disable.attr,
	&dev_attr_fnode_max_recv_dlength.attr,
	&dev_attr_fnode_max_xmit_dlength.attr,
	&dev_attr_fnode_keepalive_पंचांगo.attr,
	&dev_attr_fnode_port.attr,
	&dev_attr_fnode_ipaddress.attr,
	&dev_attr_fnode_redirect_ipaddr.attr,
	&dev_attr_fnode_max_segment_size.attr,
	&dev_attr_fnode_local_port.attr,
	&dev_attr_fnode_ipv4_tos.attr,
	&dev_attr_fnode_ipv6_traffic_class.attr,
	&dev_attr_fnode_ipv6_flow_label.attr,
	&dev_attr_fnode_link_local_ipv6.attr,
	&dev_attr_fnode_tcp_xmit_wsf.attr,
	&dev_attr_fnode_tcp_recv_wsf.attr,
	&dev_attr_fnode_statsn.attr,
	&dev_attr_fnode_exp_statsn.attr,
	शून्य,
पूर्ण;

अटल umode_t iscsi_flashnode_conn_attr_is_visible(काष्ठा kobject *kobj,
						    काष्ठा attribute *attr,
						    पूर्णांक i)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा iscsi_bus_flash_conn *fnode_conn = iscsi_dev_to_flash_conn(dev);
	काष्ठा iscsi_transport *t = fnode_conn->transport;
	पूर्णांक param;

	अगर (attr == &dev_attr_fnode_is_fw_asचिन्हित_ipv6.attr) अणु
		param = ISCSI_FLASHNODE_IS_FW_ASSIGNED_IPV6;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_header_digest.attr) अणु
		param = ISCSI_FLASHNODE_HDR_DGST_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_data_digest.attr) अणु
		param = ISCSI_FLASHNODE_DATA_DGST_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_snack_req.attr) अणु
		param = ISCSI_FLASHNODE_SNACK_REQ_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_tcp_बारtamp_stat.attr) अणु
		param = ISCSI_FLASHNODE_TCP_TIMESTAMP_STAT;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_tcp_nagle_disable.attr) अणु
		param = ISCSI_FLASHNODE_TCP_NAGLE_DISABLE;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_tcp_wsf_disable.attr) अणु
		param = ISCSI_FLASHNODE_TCP_WSF_DISABLE;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_tcp_समयr_scale.attr) अणु
		param = ISCSI_FLASHNODE_TCP_TIMER_SCALE;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_tcp_बारtamp_enable.attr) अणु
		param = ISCSI_FLASHNODE_TCP_TIMESTAMP_EN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_fragment_disable.attr) अणु
		param = ISCSI_FLASHNODE_IP_FRAG_DISABLE;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_max_recv_dlength.attr) अणु
		param = ISCSI_FLASHNODE_MAX_RECV_DLENGTH;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_max_xmit_dlength.attr) अणु
		param = ISCSI_FLASHNODE_MAX_XMIT_DLENGTH;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_keepalive_पंचांगo.attr) अणु
		param = ISCSI_FLASHNODE_KEEPALIVE_TMO;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_port.attr) अणु
		param = ISCSI_FLASHNODE_PORT;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_ipaddress.attr) अणु
		param = ISCSI_FLASHNODE_IPADDR;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_redirect_ipaddr.attr) अणु
		param = ISCSI_FLASHNODE_REसूचीECT_IPADDR;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_max_segment_size.attr) अणु
		param = ISCSI_FLASHNODE_MAX_SEGMENT_SIZE;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_local_port.attr) अणु
		param = ISCSI_FLASHNODE_LOCAL_PORT;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_ipv4_tos.attr) अणु
		param = ISCSI_FLASHNODE_IPV4_TOS;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_ipv6_traffic_class.attr) अणु
		param = ISCSI_FLASHNODE_IPV6_TC;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_ipv6_flow_label.attr) अणु
		param = ISCSI_FLASHNODE_IPV6_FLOW_LABEL;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_link_local_ipv6.attr) अणु
		param = ISCSI_FLASHNODE_LINK_LOCAL_IPV6;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_tcp_xmit_wsf.attr) अणु
		param = ISCSI_FLASHNODE_TCP_XMIT_WSF;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_tcp_recv_wsf.attr) अणु
		param = ISCSI_FLASHNODE_TCP_RECV_WSF;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_statsn.attr) अणु
		param = ISCSI_FLASHNODE_STATSN;
	पूर्ण अन्यथा अगर (attr == &dev_attr_fnode_exp_statsn.attr) अणु
		param = ISCSI_FLASHNODE_EXP_STATSN;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "Invalid flashnode connection attr");
		वापस 0;
	पूर्ण

	वापस t->attr_is_visible(ISCSI_FLASHNODE_PARAM, param);
पूर्ण

अटल काष्ठा attribute_group iscsi_flashnode_conn_attr_group = अणु
	.attrs = iscsi_flashnode_conn_attrs,
	.is_visible = iscsi_flashnode_conn_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *iscsi_flashnode_conn_attr_groups[] = अणु
	&iscsi_flashnode_conn_attr_group,
	शून्य,
पूर्ण;

अटल व्योम iscsi_flashnode_conn_release(काष्ठा device *dev)
अणु
	काष्ठा iscsi_bus_flash_conn *fnode_conn = iscsi_dev_to_flash_conn(dev);

	kमुक्त(fnode_conn->ipaddress);
	kमुक्त(fnode_conn->redirect_ipaddr);
	kमुक्त(fnode_conn->link_local_ipv6_addr);
	kमुक्त(fnode_conn);
पूर्ण

अटल स्थिर काष्ठा device_type iscsi_flashnode_conn_dev_type = अणु
	.name = "iscsi_flashnode_conn_dev_type",
	.groups = iscsi_flashnode_conn_attr_groups,
	.release = iscsi_flashnode_conn_release,
पूर्ण;

अटल काष्ठा bus_type iscsi_flashnode_bus;

पूर्णांक iscsi_flashnode_bus_match(काष्ठा device *dev,
				     काष्ठा device_driver *drv)
अणु
	अगर (dev->bus == &iscsi_flashnode_bus)
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_flashnode_bus_match);

अटल काष्ठा bus_type iscsi_flashnode_bus = अणु
	.name = "iscsi_flashnode",
	.match = &iscsi_flashnode_bus_match,
पूर्ण;

/**
 * iscsi_create_flashnode_sess - Add flashnode session entry in sysfs
 * @shost: poपूर्णांकer to host data
 * @index: index of flashnode to add in sysfs
 * @transport: poपूर्णांकer to transport data
 * @dd_size: total size to allocate
 *
 * Adds a sysfs entry क्रम the flashnode session attributes
 *
 * Returns:
 *  poपूर्णांकer to allocated flashnode sess on success
 *  %शून्य on failure
 */
काष्ठा iscsi_bus_flash_session *
iscsi_create_flashnode_sess(काष्ठा Scsi_Host *shost, पूर्णांक index,
			    काष्ठा iscsi_transport *transport,
			    पूर्णांक dd_size)
अणु
	काष्ठा iscsi_bus_flash_session *fnode_sess;
	पूर्णांक err;

	fnode_sess = kzalloc(माप(*fnode_sess) + dd_size, GFP_KERNEL);
	अगर (!fnode_sess)
		वापस शून्य;

	fnode_sess->transport = transport;
	fnode_sess->target_id = index;
	fnode_sess->dev.type = &iscsi_flashnode_sess_dev_type;
	fnode_sess->dev.bus = &iscsi_flashnode_bus;
	fnode_sess->dev.parent = &shost->shost_gendev;
	dev_set_name(&fnode_sess->dev, "flashnode_sess-%u:%u",
		     shost->host_no, index);

	err = device_रेजिस्टर(&fnode_sess->dev);
	अगर (err)
		जाओ मुक्त_fnode_sess;

	अगर (dd_size)
		fnode_sess->dd_data = &fnode_sess[1];

	वापस fnode_sess;

मुक्त_fnode_sess:
	kमुक्त(fnode_sess);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_create_flashnode_sess);

/**
 * iscsi_create_flashnode_conn - Add flashnode conn entry in sysfs
 * @shost: poपूर्णांकer to host data
 * @fnode_sess: poपूर्णांकer to the parent flashnode session entry
 * @transport: poपूर्णांकer to transport data
 * @dd_size: total size to allocate
 *
 * Adds a sysfs entry क्रम the flashnode connection attributes
 *
 * Returns:
 *  poपूर्णांकer to allocated flashnode conn on success
 *  %शून्य on failure
 */
काष्ठा iscsi_bus_flash_conn *
iscsi_create_flashnode_conn(काष्ठा Scsi_Host *shost,
			    काष्ठा iscsi_bus_flash_session *fnode_sess,
			    काष्ठा iscsi_transport *transport,
			    पूर्णांक dd_size)
अणु
	काष्ठा iscsi_bus_flash_conn *fnode_conn;
	पूर्णांक err;

	fnode_conn = kzalloc(माप(*fnode_conn) + dd_size, GFP_KERNEL);
	अगर (!fnode_conn)
		वापस शून्य;

	fnode_conn->transport = transport;
	fnode_conn->dev.type = &iscsi_flashnode_conn_dev_type;
	fnode_conn->dev.bus = &iscsi_flashnode_bus;
	fnode_conn->dev.parent = &fnode_sess->dev;
	dev_set_name(&fnode_conn->dev, "flashnode_conn-%u:%u:0",
		     shost->host_no, fnode_sess->target_id);

	err = device_रेजिस्टर(&fnode_conn->dev);
	अगर (err)
		जाओ मुक्त_fnode_conn;

	अगर (dd_size)
		fnode_conn->dd_data = &fnode_conn[1];

	वापस fnode_conn;

मुक्त_fnode_conn:
	kमुक्त(fnode_conn);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_create_flashnode_conn);

/**
 * iscsi_is_flashnode_conn_dev - verअगरy passed device is to be flashnode conn
 * @dev: device to verअगरy
 * @data: poपूर्णांकer to data containing value to use क्रम verअगरication
 *
 * Verअगरies अगर the passed device is flashnode conn device
 *
 * Returns:
 *  1 on success
 *  0 on failure
 */
अटल पूर्णांक iscsi_is_flashnode_conn_dev(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->bus == &iscsi_flashnode_bus;
पूर्ण

अटल पूर्णांक iscsi_destroy_flashnode_conn(काष्ठा iscsi_bus_flash_conn *fnode_conn)
अणु
	device_unरेजिस्टर(&fnode_conn->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक flashnode_match_index(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा iscsi_bus_flash_session *fnode_sess = शून्य;
	पूर्णांक ret = 0;

	अगर (!iscsi_flashnode_bus_match(dev, शून्य))
		जाओ निकास_match_index;

	fnode_sess = iscsi_dev_to_flash_session(dev);
	ret = (fnode_sess->target_id == *((पूर्णांक *)data)) ? 1 : 0;

निकास_match_index:
	वापस ret;
पूर्ण

/**
 * iscsi_get_flashnode_by_index -finds flashnode session entry by index
 * @shost: poपूर्णांकer to host data
 * @idx: index to match
 *
 * Finds the flashnode session object क्रम the passed index
 *
 * Returns:
 *  poपूर्णांकer to found flashnode session object on success
 *  %शून्य on failure
 */
अटल काष्ठा iscsi_bus_flash_session *
iscsi_get_flashnode_by_index(काष्ठा Scsi_Host *shost, uपूर्णांक32_t idx)
अणु
	काष्ठा iscsi_bus_flash_session *fnode_sess = शून्य;
	काष्ठा device *dev;

	dev = device_find_child(&shost->shost_gendev, &idx,
				flashnode_match_index);
	अगर (dev)
		fnode_sess = iscsi_dev_to_flash_session(dev);

	वापस fnode_sess;
पूर्ण

/**
 * iscsi_find_flashnode_sess - finds flashnode session entry
 * @shost: poपूर्णांकer to host data
 * @data: poपूर्णांकer to data containing value to use क्रम comparison
 * @fn: function poपूर्णांकer that करोes actual comparison
 *
 * Finds the flashnode session object comparing the data passed using logic
 * defined in passed function poपूर्णांकer
 *
 * Returns:
 *  poपूर्णांकer to found flashnode session device object on success
 *  %शून्य on failure
 */
काष्ठा device *
iscsi_find_flashnode_sess(काष्ठा Scsi_Host *shost, व्योम *data,
			  पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data))
अणु
	वापस device_find_child(&shost->shost_gendev, data, fn);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_find_flashnode_sess);

/**
 * iscsi_find_flashnode_conn - finds flashnode connection entry
 * @fnode_sess: poपूर्णांकer to parent flashnode session entry
 *
 * Finds the flashnode connection object comparing the data passed using logic
 * defined in passed function poपूर्णांकer
 *
 * Returns:
 *  poपूर्णांकer to found flashnode connection device object on success
 *  %शून्य on failure
 */
काष्ठा device *
iscsi_find_flashnode_conn(काष्ठा iscsi_bus_flash_session *fnode_sess)
अणु
	वापस device_find_child(&fnode_sess->dev, शून्य,
				 iscsi_is_flashnode_conn_dev);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_find_flashnode_conn);

अटल पूर्णांक iscsi_iter_destroy_flashnode_conn_fn(काष्ठा device *dev, व्योम *data)
अणु
	अगर (!iscsi_is_flashnode_conn_dev(dev, शून्य))
		वापस 0;

	वापस iscsi_destroy_flashnode_conn(iscsi_dev_to_flash_conn(dev));
पूर्ण

/**
 * iscsi_destroy_flashnode_sess - destroy flashnode session entry
 * @fnode_sess: poपूर्णांकer to flashnode session entry to be destroyed
 *
 * Deletes the flashnode session entry and all children flashnode connection
 * entries from sysfs
 */
व्योम iscsi_destroy_flashnode_sess(काष्ठा iscsi_bus_flash_session *fnode_sess)
अणु
	पूर्णांक err;

	err = device_क्रम_each_child(&fnode_sess->dev, शून्य,
				    iscsi_iter_destroy_flashnode_conn_fn);
	अगर (err)
		pr_err("Could not delete all connections for %s. Error %d.\n",
		       fnode_sess->dev.kobj.name, err);

	device_unरेजिस्टर(&fnode_sess->dev);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_destroy_flashnode_sess);

अटल पूर्णांक iscsi_iter_destroy_flashnode_fn(काष्ठा device *dev, व्योम *data)
अणु
	अगर (!iscsi_flashnode_bus_match(dev, शून्य))
		वापस 0;

	iscsi_destroy_flashnode_sess(iscsi_dev_to_flash_session(dev));
	वापस 0;
पूर्ण

/**
 * iscsi_destroy_all_flashnode - destroy all flashnode session entries
 * @shost: poपूर्णांकer to host data
 *
 * Destroys all the flashnode session entries and all corresponding children
 * flashnode connection entries from sysfs
 */
व्योम iscsi_destroy_all_flashnode(काष्ठा Scsi_Host *shost)
अणु
	device_क्रम_each_child(&shost->shost_gendev, शून्य,
			      iscsi_iter_destroy_flashnode_fn);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_destroy_all_flashnode);

/*
 * BSG support
 */
/**
 * iscsi_bsg_host_dispatch - Dispatch command to LLD.
 * @job: bsg job to be processed
 */
अटल पूर्णांक iscsi_bsg_host_dispatch(काष्ठा bsg_job *job)
अणु
	काष्ठा Scsi_Host *shost = iscsi_job_to_shost(job);
	काष्ठा iscsi_bsg_request *req = job->request;
	काष्ठा iscsi_bsg_reply *reply = job->reply;
	काष्ठा iscsi_पूर्णांकernal *i = to_iscsi_पूर्णांकernal(shost->transportt);
	पूर्णांक cmdlen = माप(uपूर्णांक32_t);	/* start with length of msgcode */
	पूर्णांक ret;

	/* check अगर we have the msgcode value at least */
	अगर (job->request_len < माप(uपूर्णांक32_t)) अणु
		ret = -ENOMSG;
		जाओ fail_host_msg;
	पूर्ण

	/* Validate the host command */
	चयन (req->msgcode) अणु
	हाल ISCSI_BSG_HST_VENDOR:
		cmdlen += माप(काष्ठा iscsi_bsg_host_venकरोr);
		अगर ((shost->hostt->venकरोr_id == 0L) ||
		    (req->rqst_data.h_venकरोr.venकरोr_id !=
			shost->hostt->venकरोr_id)) अणु
			ret = -ESRCH;
			जाओ fail_host_msg;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EBADR;
		जाओ fail_host_msg;
	पूर्ण

	/* check अगर we really have all the request data needed */
	अगर (job->request_len < cmdlen) अणु
		ret = -ENOMSG;
		जाओ fail_host_msg;
	पूर्ण

	ret = i->iscsi_transport->bsg_request(job);
	अगर (!ret)
		वापस 0;

fail_host_msg:
	/* वापस the त्रुटि_सं failure code as the only status */
	BUG_ON(job->reply_len < माप(uपूर्णांक32_t));
	reply->reply_payload_rcv_len = 0;
	reply->result = ret;
	job->reply_len = माप(uपूर्णांक32_t);
	bsg_job_करोne(job, ret, 0);
	वापस 0;
पूर्ण

/**
 * iscsi_bsg_host_add - Create and add the bsg hooks to receive requests
 * @shost: shost क्रम iscsi_host
 * @ihost: iscsi_cls_host adding the काष्ठाures to
 */
अटल पूर्णांक
iscsi_bsg_host_add(काष्ठा Scsi_Host *shost, काष्ठा iscsi_cls_host *ihost)
अणु
	काष्ठा device *dev = &shost->shost_gendev;
	काष्ठा iscsi_पूर्णांकernal *i = to_iscsi_पूर्णांकernal(shost->transportt);
	काष्ठा request_queue *q;
	अक्षर bsg_name[20];

	अगर (!i->iscsi_transport->bsg_request)
		वापस -ENOTSUPP;

	snम_लिखो(bsg_name, माप(bsg_name), "iscsi_host%d", shost->host_no);
	q = bsg_setup_queue(dev, bsg_name, iscsi_bsg_host_dispatch, शून्य, 0);
	अगर (IS_ERR(q)) अणु
		shost_prपूर्णांकk(KERN_ERR, shost, "bsg interface failed to "
			     "initialize - no request queue\n");
		वापस PTR_ERR(q);
	पूर्ण
	__scsi_init_queue(shost, q);

	ihost->bsg_q = q;
	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_setup_host(काष्ठा transport_container *tc, काष्ठा device *dev,
			    काष्ठा device *cdev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;

	स_रखो(ihost, 0, माप(*ihost));
	atomic_set(&ihost->nr_scans, 0);
	mutex_init(&ihost->mutex);

	iscsi_bsg_host_add(shost, ihost);
	/* ignore any bsg add error - we just can't करो sgio */

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_हटाओ_host(काष्ठा transport_container *tc,
			     काष्ठा device *dev, काष्ठा device *cdev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;

	bsg_हटाओ_queue(ihost->bsg_q);
	वापस 0;
पूर्ण

अटल DECLARE_TRANSPORT_CLASS(iscsi_host_class,
			       "iscsi_host",
			       iscsi_setup_host,
			       iscsi_हटाओ_host,
			       शून्य);

अटल DECLARE_TRANSPORT_CLASS(iscsi_session_class,
			       "iscsi_session",
			       शून्य,
			       शून्य,
			       शून्य);

अटल DECLARE_TRANSPORT_CLASS(iscsi_connection_class,
			       "iscsi_connection",
			       शून्य,
			       शून्य,
			       शून्य);

अटल काष्ठा sock *nls;
अटल DEFINE_MUTEX(rx_queue_mutex);

/*
 * conn_mutex protects the अणुstart,bind,stop,destroyपूर्ण_conn from racing
 * against the kernel stop_connection recovery mechanism
 */
अटल DEFINE_MUTEX(conn_mutex);

अटल LIST_HEAD(sesslist);
अटल DEFINE_SPINLOCK(sesslock);
अटल LIST_HEAD(connlist);
अटल LIST_HEAD(connlist_err);
अटल DEFINE_SPINLOCK(connlock);

अटल uपूर्णांक32_t iscsi_conn_get_sid(काष्ठा iscsi_cls_conn *conn)
अणु
	काष्ठा iscsi_cls_session *sess = iscsi_dev_to_session(conn->dev.parent);
	वापस sess->sid;
पूर्ण

/*
 * Returns the matching session to a given sid
 */
अटल काष्ठा iscsi_cls_session *iscsi_session_lookup(uपूर्णांक32_t sid)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा iscsi_cls_session *sess;

	spin_lock_irqsave(&sesslock, flags);
	list_क्रम_each_entry(sess, &sesslist, sess_list) अणु
		अगर (sess->sid == sid) अणु
			spin_unlock_irqrestore(&sesslock, flags);
			वापस sess;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&sesslock, flags);
	वापस शून्य;
पूर्ण

/*
 * Returns the matching connection to a given sid / cid tuple
 */
अटल काष्ठा iscsi_cls_conn *iscsi_conn_lookup(uपूर्णांक32_t sid, uपूर्णांक32_t cid)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा iscsi_cls_conn *conn;

	spin_lock_irqsave(&connlock, flags);
	list_क्रम_each_entry(conn, &connlist, conn_list) अणु
		अगर ((conn->cid == cid) && (iscsi_conn_get_sid(conn) == sid)) अणु
			spin_unlock_irqrestore(&connlock, flags);
			वापस conn;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&connlock, flags);
	वापस शून्य;
पूर्ण

/*
 * The following functions can be used by LLDs that allocate
 * their own scsi_hosts or by software iscsi LLDs
 */
अटल काष्ठा अणु
	पूर्णांक value;
	अक्षर *name;
पूर्ण iscsi_session_state_names[] = अणु
	अणु ISCSI_SESSION_LOGGED_IN,	"LOGGED_IN" पूर्ण,
	अणु ISCSI_SESSION_FAILED,		"FAILED" पूर्ण,
	अणु ISCSI_SESSION_FREE,		"FREE" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *iscsi_session_state_name(पूर्णांक state)
अणु
	पूर्णांक i;
	अक्षर *name = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(iscsi_session_state_names); i++) अणु
		अगर (iscsi_session_state_names[i].value == state) अणु
			name = iscsi_session_state_names[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस name;
पूर्ण

पूर्णांक iscsi_session_chkपढ़ोy(काष्ठा iscsi_cls_session *session)
अणु
	पूर्णांक err;

	चयन (session->state) अणु
	हाल ISCSI_SESSION_LOGGED_IN:
		err = 0;
		अवरोध;
	हाल ISCSI_SESSION_FAILED:
		err = DID_IMM_RETRY << 16;
		अवरोध;
	हाल ISCSI_SESSION_FREE:
		err = DID_TRANSPORT_FAILFAST << 16;
		अवरोध;
	शेष:
		err = DID_NO_CONNECT << 16;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_session_chkपढ़ोy);

पूर्णांक iscsi_is_session_online(काष्ठा iscsi_cls_session *session)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&session->lock, flags);
	अगर (session->state == ISCSI_SESSION_LOGGED_IN)
		ret = 1;
	spin_unlock_irqrestore(&session->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_is_session_online);

अटल व्योम iscsi_session_release(काष्ठा device *dev)
अणु
	काष्ठा iscsi_cls_session *session = iscsi_dev_to_session(dev);
	काष्ठा Scsi_Host *shost;

	shost = iscsi_session_to_shost(session);
	scsi_host_put(shost);
	ISCSI_DBG_TRANS_SESSION(session, "Completing session release\n");
	kमुक्त(session);
पूर्ण

पूर्णांक iscsi_is_session_dev(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == iscsi_session_release;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_is_session_dev);

अटल पूर्णांक iscsi_iter_session_fn(काष्ठा device *dev, व्योम *data)
अणु
	व्योम (* fn) (काष्ठा iscsi_cls_session *) = data;

	अगर (!iscsi_is_session_dev(dev))
		वापस 0;
	fn(iscsi_dev_to_session(dev));
	वापस 0;
पूर्ण

व्योम iscsi_host_क्रम_each_session(काष्ठा Scsi_Host *shost,
				 व्योम (*fn)(काष्ठा iscsi_cls_session *))
अणु
	device_क्रम_each_child(&shost->shost_gendev, fn,
			      iscsi_iter_session_fn);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_host_क्रम_each_session);

/**
 * iscsi_scan_finished - helper to report when running scans are करोne
 * @shost: scsi host
 * @समय: scan run समय
 *
 * This function can be used by drives like qla4xxx to report to the scsi
 * layer when the scans it kicked off at module load समय are करोne.
 */
पूर्णांक iscsi_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;
	/*
	 * qla4xxx will have kicked off some session unblocks beक्रमe calling
	 * scsi_scan_host, so just रुको क्रम them to complete.
	 */
	वापस !atomic_पढ़ो(&ihost->nr_scans);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_scan_finished);

काष्ठा iscsi_scan_data अणु
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक id;
	u64 lun;
	क्रमागत scsi_scan_mode rescan;
पूर्ण;

अटल पूर्णांक iscsi_user_scan_session(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा iscsi_scan_data *scan_data = data;
	काष्ठा iscsi_cls_session *session;
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_cls_host *ihost;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक id;

	अगर (!iscsi_is_session_dev(dev))
		वापस 0;

	session = iscsi_dev_to_session(dev);

	ISCSI_DBG_TRANS_SESSION(session, "Scanning session\n");

	shost = iscsi_session_to_shost(session);
	ihost = shost->shost_data;

	mutex_lock(&ihost->mutex);
	spin_lock_irqsave(&session->lock, flags);
	अगर (session->state != ISCSI_SESSION_LOGGED_IN) अणु
		spin_unlock_irqrestore(&session->lock, flags);
		जाओ user_scan_निकास;
	पूर्ण
	id = session->target_id;
	spin_unlock_irqrestore(&session->lock, flags);

	अगर (id != ISCSI_MAX_TARGET) अणु
		अगर ((scan_data->channel == SCAN_WILD_CARD ||
		     scan_data->channel == 0) &&
		    (scan_data->id == SCAN_WILD_CARD ||
		     scan_data->id == id))
			scsi_scan_target(&session->dev, 0, id,
					 scan_data->lun, scan_data->rescan);
	पूर्ण

user_scan_निकास:
	mutex_unlock(&ihost->mutex);
	ISCSI_DBG_TRANS_SESSION(session, "Completed session scan\n");
	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_user_scan(काष्ठा Scsi_Host *shost, uपूर्णांक channel,
			   uपूर्णांक id, u64 lun)
अणु
	काष्ठा iscsi_scan_data scan_data;

	scan_data.channel = channel;
	scan_data.id = id;
	scan_data.lun = lun;
	scan_data.rescan = SCSI_SCAN_MANUAL;

	वापस device_क्रम_each_child(&shost->shost_gendev, &scan_data,
				     iscsi_user_scan_session);
पूर्ण

अटल व्योम iscsi_scan_session(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iscsi_cls_session *session =
			container_of(work, काष्ठा iscsi_cls_session, scan_work);
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(session);
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;
	काष्ठा iscsi_scan_data scan_data;

	scan_data.channel = 0;
	scan_data.id = SCAN_WILD_CARD;
	scan_data.lun = SCAN_WILD_CARD;
	scan_data.rescan = SCSI_SCAN_RESCAN;

	iscsi_user_scan_session(&session->dev, &scan_data);
	atomic_dec(&ihost->nr_scans);
पूर्ण

/**
 * iscsi_block_scsi_eh - block scsi eh until session state has transistioned
 * @cmd: scsi cmd passed to scsi eh handler
 *
 * If the session is करोwn this function will रुको क्रम the recovery
 * समयr to fire or क्रम the session to be logged back in. If the
 * recovery समयr fires then FAST_IO_FAIL is वापसed. The caller
 * should pass this error value to the scsi eh.
 */
पूर्णांक iscsi_block_scsi_eh(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा iscsi_cls_session *session =
			starget_to_session(scsi_target(cmd->device));
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&session->lock, flags);
	जबतक (session->state != ISCSI_SESSION_LOGGED_IN) अणु
		अगर (session->state == ISCSI_SESSION_FREE) अणु
			ret = FAST_IO_FAIL;
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&session->lock, flags);
		msleep(1000);
		spin_lock_irqsave(&session->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&session->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_block_scsi_eh);

अटल व्योम session_recovery_समयकरोut(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iscsi_cls_session *session =
		container_of(work, काष्ठा iscsi_cls_session,
			     recovery_work.work);
	अचिन्हित दीर्घ flags;

	iscsi_cls_session_prपूर्णांकk(KERN_INFO, session,
				 "session recovery timed out after %d secs\n",
				 session->recovery_पंचांगo);

	spin_lock_irqsave(&session->lock, flags);
	चयन (session->state) अणु
	हाल ISCSI_SESSION_FAILED:
		session->state = ISCSI_SESSION_FREE;
		अवरोध;
	हाल ISCSI_SESSION_LOGGED_IN:
	हाल ISCSI_SESSION_FREE:
		/* we raced with the unblock's flush */
		spin_unlock_irqrestore(&session->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&session->lock, flags);

	अगर (session->transport->session_recovery_समयकरोut)
		session->transport->session_recovery_समयकरोut(session);

	ISCSI_DBG_TRANS_SESSION(session, "Unblocking SCSI target\n");
	scsi_target_unblock(&session->dev, SDEV_TRANSPORT_OFFLINE);
	ISCSI_DBG_TRANS_SESSION(session, "Completed unblocking SCSI target\n");
पूर्ण

अटल व्योम __iscsi_unblock_session(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iscsi_cls_session *session =
			container_of(work, काष्ठा iscsi_cls_session,
				     unblock_work);
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(session);
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;
	अचिन्हित दीर्घ flags;

	ISCSI_DBG_TRANS_SESSION(session, "Unblocking session\n");
	/*
	 * The recovery and unblock work get run from the same workqueue,
	 * so try to cancel it अगर it was going to run after this unblock.
	 */
	cancel_delayed_work(&session->recovery_work);
	spin_lock_irqsave(&session->lock, flags);
	session->state = ISCSI_SESSION_LOGGED_IN;
	spin_unlock_irqrestore(&session->lock, flags);
	/* start IO */
	scsi_target_unblock(&session->dev, SDEV_RUNNING);
	/*
	 * Only करो kernel scanning अगर the driver is properly hooked पूर्णांकo
	 * the async scanning code (drivers like iscsi_tcp करो login and
	 * scanning from userspace).
	 */
	अगर (shost->hostt->scan_finished) अणु
		अगर (scsi_queue_work(shost, &session->scan_work))
			atomic_inc(&ihost->nr_scans);
	पूर्ण
	ISCSI_DBG_TRANS_SESSION(session, "Completed unblocking session\n");
पूर्ण

/**
 * iscsi_unblock_session - set a session as logged in and start IO.
 * @session: iscsi session
 *
 * Mark a session as पढ़ोy to accept IO.
 */
व्योम iscsi_unblock_session(काष्ठा iscsi_cls_session *session)
अणु
	queue_work(iscsi_eh_समयr_workq, &session->unblock_work);
	/*
	 * Blocking the session can be करोne from any context so we only
	 * queue the block work. Make sure the unblock work has completed
	 * because it flushes/cancels the other works and updates the state.
	 */
	flush_work(&session->unblock_work);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_unblock_session);

अटल व्योम __iscsi_block_session(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iscsi_cls_session *session =
			container_of(work, काष्ठा iscsi_cls_session,
				     block_work);
	अचिन्हित दीर्घ flags;

	ISCSI_DBG_TRANS_SESSION(session, "Blocking session\n");
	spin_lock_irqsave(&session->lock, flags);
	session->state = ISCSI_SESSION_FAILED;
	spin_unlock_irqrestore(&session->lock, flags);
	scsi_target_block(&session->dev);
	ISCSI_DBG_TRANS_SESSION(session, "Completed SCSI target blocking\n");
	अगर (session->recovery_पंचांगo >= 0)
		queue_delayed_work(iscsi_eh_समयr_workq,
				   &session->recovery_work,
				   session->recovery_पंचांगo * HZ);
पूर्ण

व्योम iscsi_block_session(काष्ठा iscsi_cls_session *session)
अणु
	queue_work(iscsi_eh_समयr_workq, &session->block_work);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_block_session);

अटल व्योम __iscsi_unbind_session(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iscsi_cls_session *session =
			container_of(work, काष्ठा iscsi_cls_session,
				     unbind_work);
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(session);
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक target_id;

	ISCSI_DBG_TRANS_SESSION(session, "Unbinding session\n");

	/* Prevent new scans and make sure scanning is not in progress */
	mutex_lock(&ihost->mutex);
	spin_lock_irqsave(&session->lock, flags);
	अगर (session->target_id == ISCSI_MAX_TARGET) अणु
		spin_unlock_irqrestore(&session->lock, flags);
		mutex_unlock(&ihost->mutex);
		जाओ unbind_session_निकास;
	पूर्ण

	target_id = session->target_id;
	session->target_id = ISCSI_MAX_TARGET;
	spin_unlock_irqrestore(&session->lock, flags);
	mutex_unlock(&ihost->mutex);

	scsi_हटाओ_target(&session->dev);

	अगर (session->ida_used)
		ida_simple_हटाओ(&iscsi_sess_ida, target_id);

unbind_session_निकास:
	iscsi_session_event(session, ISCSI_KEVENT_UNBIND_SESSION);
	ISCSI_DBG_TRANS_SESSION(session, "Completed target removal\n");
पूर्ण

अटल व्योम __iscsi_destroy_session(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iscsi_cls_session *session =
		container_of(work, काष्ठा iscsi_cls_session, destroy_work);

	session->transport->destroy_session(session);
पूर्ण

काष्ठा iscsi_cls_session *
iscsi_alloc_session(काष्ठा Scsi_Host *shost, काष्ठा iscsi_transport *transport,
		    पूर्णांक dd_size)
अणु
	काष्ठा iscsi_cls_session *session;

	session = kzalloc(माप(*session) + dd_size,
			  GFP_KERNEL);
	अगर (!session)
		वापस शून्य;

	session->transport = transport;
	session->creator = -1;
	session->recovery_पंचांगo = 120;
	session->recovery_पंचांगo_sysfs_override = false;
	session->state = ISCSI_SESSION_FREE;
	INIT_DELAYED_WORK(&session->recovery_work, session_recovery_समयकरोut);
	INIT_LIST_HEAD(&session->sess_list);
	INIT_WORK(&session->unblock_work, __iscsi_unblock_session);
	INIT_WORK(&session->block_work, __iscsi_block_session);
	INIT_WORK(&session->unbind_work, __iscsi_unbind_session);
	INIT_WORK(&session->scan_work, iscsi_scan_session);
	INIT_WORK(&session->destroy_work, __iscsi_destroy_session);
	spin_lock_init(&session->lock);

	/* this is released in the dev's release function */
	scsi_host_get(shost);
	session->dev.parent = &shost->shost_gendev;
	session->dev.release = iscsi_session_release;
	device_initialize(&session->dev);
	अगर (dd_size)
		session->dd_data = &session[1];

	ISCSI_DBG_TRANS_SESSION(session, "Completed session allocation\n");
	वापस session;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_alloc_session);

पूर्णांक iscsi_add_session(काष्ठा iscsi_cls_session *session, अचिन्हित पूर्णांक target_id)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक id = 0;
	पूर्णांक err;

	session->sid = atomic_add_वापस(1, &iscsi_session_nr);

	अगर (target_id == ISCSI_MAX_TARGET) अणु
		id = ida_simple_get(&iscsi_sess_ida, 0, 0, GFP_KERNEL);

		अगर (id < 0) अणु
			iscsi_cls_session_prपूर्णांकk(KERN_ERR, session,
					"Failure in Target ID Allocation\n");
			वापस id;
		पूर्ण
		session->target_id = (अचिन्हित पूर्णांक)id;
		session->ida_used = true;
	पूर्ण अन्यथा
		session->target_id = target_id;

	dev_set_name(&session->dev, "session%u", session->sid);
	err = device_add(&session->dev);
	अगर (err) अणु
		iscsi_cls_session_prपूर्णांकk(KERN_ERR, session,
					 "could not register session's dev\n");
		जाओ release_ida;
	पूर्ण
	err = transport_रेजिस्टर_device(&session->dev);
	अगर (err) अणु
		iscsi_cls_session_prपूर्णांकk(KERN_ERR, session,
					 "could not register transport's dev\n");
		जाओ release_dev;
	पूर्ण

	spin_lock_irqsave(&sesslock, flags);
	list_add(&session->sess_list, &sesslist);
	spin_unlock_irqrestore(&sesslock, flags);

	iscsi_session_event(session, ISCSI_KEVENT_CREATE_SESSION);
	ISCSI_DBG_TRANS_SESSION(session, "Completed session adding\n");
	वापस 0;

release_dev:
	device_del(&session->dev);
release_ida:
	अगर (session->ida_used)
		ida_simple_हटाओ(&iscsi_sess_ida, session->target_id);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_add_session);

/**
 * iscsi_create_session - create iscsi class session
 * @shost: scsi host
 * @transport: iscsi transport
 * @dd_size: निजी driver data size
 * @target_id: which target
 *
 * This can be called from a LLD or iscsi_transport.
 */
काष्ठा iscsi_cls_session *
iscsi_create_session(काष्ठा Scsi_Host *shost, काष्ठा iscsi_transport *transport,
		     पूर्णांक dd_size, अचिन्हित पूर्णांक target_id)
अणु
	काष्ठा iscsi_cls_session *session;

	session = iscsi_alloc_session(shost, transport, dd_size);
	अगर (!session)
		वापस शून्य;

	अगर (iscsi_add_session(session, target_id)) अणु
		iscsi_मुक्त_session(session);
		वापस शून्य;
	पूर्ण
	वापस session;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_create_session);

अटल व्योम iscsi_conn_release(काष्ठा device *dev)
अणु
	काष्ठा iscsi_cls_conn *conn = iscsi_dev_to_conn(dev);
	काष्ठा device *parent = conn->dev.parent;

	ISCSI_DBG_TRANS_CONN(conn, "Releasing conn\n");
	kमुक्त(conn);
	put_device(parent);
पूर्ण

अटल पूर्णांक iscsi_is_conn_dev(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == iscsi_conn_release;
पूर्ण

अटल पूर्णांक iscsi_iter_destroy_conn_fn(काष्ठा device *dev, व्योम *data)
अणु
	अगर (!iscsi_is_conn_dev(dev))
		वापस 0;
	वापस iscsi_destroy_conn(iscsi_dev_to_conn(dev));
पूर्ण

व्योम iscsi_हटाओ_session(काष्ठा iscsi_cls_session *session)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	ISCSI_DBG_TRANS_SESSION(session, "Removing session\n");

	spin_lock_irqsave(&sesslock, flags);
	अगर (!list_empty(&session->sess_list))
		list_del(&session->sess_list);
	spin_unlock_irqrestore(&sesslock, flags);

	flush_work(&session->block_work);
	flush_work(&session->unblock_work);
	cancel_delayed_work_sync(&session->recovery_work);
	/*
	 * If we are blocked let commands flow again. The lld or iscsi
	 * layer should set up the queuecommand to fail commands.
	 * We assume that LLD will not be calling block/unblock जबतक
	 * removing the session.
	 */
	spin_lock_irqsave(&session->lock, flags);
	session->state = ISCSI_SESSION_FREE;
	spin_unlock_irqrestore(&session->lock, flags);

	scsi_target_unblock(&session->dev, SDEV_TRANSPORT_OFFLINE);
	/* flush running scans then delete devices */
	flush_work(&session->scan_work);
	/* flush running unbind operations */
	flush_work(&session->unbind_work);
	__iscsi_unbind_session(&session->unbind_work);

	/* hw iscsi may not have हटाओd all connections from session */
	err = device_क्रम_each_child(&session->dev, शून्य,
				    iscsi_iter_destroy_conn_fn);
	अगर (err)
		iscsi_cls_session_prपूर्णांकk(KERN_ERR, session,
					 "Could not delete all connections "
					 "for session. Error %d.\n", err);

	transport_unरेजिस्टर_device(&session->dev);

	ISCSI_DBG_TRANS_SESSION(session, "Completing session removal\n");
	device_del(&session->dev);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_हटाओ_session);

व्योम iscsi_मुक्त_session(काष्ठा iscsi_cls_session *session)
अणु
	ISCSI_DBG_TRANS_SESSION(session, "Freeing session\n");
	iscsi_session_event(session, ISCSI_KEVENT_DESTROY_SESSION);
	put_device(&session->dev);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_मुक्त_session);

/**
 * iscsi_create_conn - create iscsi class connection
 * @session: iscsi cls session
 * @dd_size: निजी driver data size
 * @cid: connection id
 *
 * This can be called from a LLD or iscsi_transport. The connection
 * is child of the session so cid must be unique क्रम all connections
 * on the session.
 *
 * Since we करो not support MCS, cid will normally be zero. In some हालs
 * क्रम software iscsi we could be trying to pपुनः_स्मृतिate a connection काष्ठा
 * in which हाल there could be two connection काष्ठाs and cid would be
 * non-zero.
 */
काष्ठा iscsi_cls_conn *
iscsi_create_conn(काष्ठा iscsi_cls_session *session, पूर्णांक dd_size, uपूर्णांक32_t cid)
अणु
	काष्ठा iscsi_transport *transport = session->transport;
	काष्ठा iscsi_cls_conn *conn;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	conn = kzalloc(माप(*conn) + dd_size, GFP_KERNEL);
	अगर (!conn)
		वापस शून्य;
	अगर (dd_size)
		conn->dd_data = &conn[1];

	mutex_init(&conn->ep_mutex);
	INIT_LIST_HEAD(&conn->conn_list);
	INIT_LIST_HEAD(&conn->conn_list_err);
	conn->transport = transport;
	conn->cid = cid;
	conn->state = ISCSI_CONN_DOWN;

	/* this is released in the dev's release function */
	अगर (!get_device(&session->dev))
		जाओ मुक्त_conn;

	dev_set_name(&conn->dev, "connection%d:%u", session->sid, cid);
	conn->dev.parent = &session->dev;
	conn->dev.release = iscsi_conn_release;
	err = device_रेजिस्टर(&conn->dev);
	अगर (err) अणु
		iscsi_cls_session_prपूर्णांकk(KERN_ERR, session, "could not "
					 "register connection's dev\n");
		जाओ release_parent_ref;
	पूर्ण
	err = transport_रेजिस्टर_device(&conn->dev);
	अगर (err) अणु
		iscsi_cls_session_prपूर्णांकk(KERN_ERR, session, "could not "
					 "register transport's dev\n");
		जाओ release_conn_ref;
	पूर्ण

	spin_lock_irqsave(&connlock, flags);
	list_add(&conn->conn_list, &connlist);
	spin_unlock_irqrestore(&connlock, flags);

	ISCSI_DBG_TRANS_CONN(conn, "Completed conn creation\n");
	वापस conn;

release_conn_ref:
	device_unरेजिस्टर(&conn->dev);
	put_device(&session->dev);
	वापस शून्य;
release_parent_ref:
	put_device(&session->dev);
मुक्त_conn:
	kमुक्त(conn);
	वापस शून्य;
पूर्ण

EXPORT_SYMBOL_GPL(iscsi_create_conn);

/**
 * iscsi_destroy_conn - destroy iscsi class connection
 * @conn: iscsi cls session
 *
 * This can be called from a LLD or iscsi_transport.
 */
पूर्णांक iscsi_destroy_conn(काष्ठा iscsi_cls_conn *conn)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&connlock, flags);
	list_del(&conn->conn_list);
	list_del(&conn->conn_list_err);
	spin_unlock_irqrestore(&connlock, flags);

	transport_unरेजिस्टर_device(&conn->dev);
	ISCSI_DBG_TRANS_CONN(conn, "Completing conn destruction\n");
	device_unरेजिस्टर(&conn->dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_destroy_conn);

/*
 * iscsi पूर्णांकerface functions
 */
अटल काष्ठा iscsi_पूर्णांकernal *
iscsi_अगर_transport_lookup(काष्ठा iscsi_transport *tt)
अणु
	काष्ठा iscsi_पूर्णांकernal *priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iscsi_transport_lock, flags);
	list_क्रम_each_entry(priv, &iscsi_transports, list) अणु
		अगर (tt == priv->iscsi_transport) अणु
			spin_unlock_irqrestore(&iscsi_transport_lock, flags);
			वापस priv;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&iscsi_transport_lock, flags);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
iscsi_multicast_skb(काष्ठा sk_buff *skb, uपूर्णांक32_t group, gfp_t gfp)
अणु
	वापस nlmsg_multicast(nls, skb, 0, group, gfp);
पूर्ण

अटल पूर्णांक
iscsi_unicast_skb(काष्ठा sk_buff *skb, u32 portid)
अणु
	वापस nlmsg_unicast(nls, skb, portid);
पूर्ण

पूर्णांक iscsi_recv_pdu(काष्ठा iscsi_cls_conn *conn, काष्ठा iscsi_hdr *hdr,
		   अक्षर *data, uपूर्णांक32_t data_size)
अणु
	काष्ठा nlmsghdr	*nlh;
	काष्ठा sk_buff *skb;
	काष्ठा iscsi_uevent *ev;
	अक्षर *pdu;
	काष्ठा iscsi_पूर्णांकernal *priv;
	पूर्णांक len = nlmsg_total_size(माप(*ev) + माप(काष्ठा iscsi_hdr) +
				   data_size);

	priv = iscsi_अगर_transport_lookup(conn->transport);
	अगर (!priv)
		वापस -EINVAL;

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb) अणु
		iscsi_conn_error_event(conn, ISCSI_ERR_CONN_FAILED);
		iscsi_cls_conn_prपूर्णांकk(KERN_ERR, conn, "can not deliver "
				      "control PDU: OOM\n");
		वापस -ENOMEM;
	पूर्ण

	nlh = __nlmsg_put(skb, 0, 0, 0, (len - माप(*nlh)), 0);
	ev = nlmsg_data(nlh);
	स_रखो(ev, 0, माप(*ev));
	ev->transport_handle = iscsi_handle(conn->transport);
	ev->type = ISCSI_KEVENT_RECV_PDU;
	ev->r.recv_req.cid = conn->cid;
	ev->r.recv_req.sid = iscsi_conn_get_sid(conn);
	pdu = (अक्षर*)ev + माप(*ev);
	स_नकल(pdu, hdr, माप(काष्ठा iscsi_hdr));
	स_नकल(pdu + माप(काष्ठा iscsi_hdr), data, data_size);

	वापस iscsi_multicast_skb(skb, ISCSI_NL_GRP_ISCSID, GFP_ATOMIC);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_recv_pdu);

पूर्णांक iscsi_offload_mesg(काष्ठा Scsi_Host *shost,
		       काष्ठा iscsi_transport *transport, uपूर्णांक32_t type,
		       अक्षर *data, uपूर्णांक16_t data_size)
अणु
	काष्ठा nlmsghdr	*nlh;
	काष्ठा sk_buff *skb;
	काष्ठा iscsi_uevent *ev;
	पूर्णांक len = nlmsg_total_size(माप(*ev) + data_size);

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_ERR "can not deliver iscsi offload message:OOM\n");
		वापस -ENOMEM;
	पूर्ण

	nlh = __nlmsg_put(skb, 0, 0, 0, (len - माप(*nlh)), 0);
	ev = nlmsg_data(nlh);
	स_रखो(ev, 0, माप(*ev));
	ev->type = type;
	ev->transport_handle = iscsi_handle(transport);
	चयन (type) अणु
	हाल ISCSI_KEVENT_PATH_REQ:
		ev->r.req_path.host_no = shost->host_no;
		अवरोध;
	हाल ISCSI_KEVENT_IF_DOWN:
		ev->r.notअगरy_अगर_करोwn.host_no = shost->host_no;
		अवरोध;
	पूर्ण

	स_नकल((अक्षर *)ev + माप(*ev), data, data_size);

	वापस iscsi_multicast_skb(skb, ISCSI_NL_GRP_UIP, GFP_ATOMIC);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_offload_mesg);

/*
 * This can be called without the rx_queue_mutex, अगर invoked by the kernel
 * stop work. But, in that हाल, it is guaranteed not to race with
 * iscsi_destroy by conn_mutex.
 */
अटल व्योम iscsi_अगर_stop_conn(काष्ठा iscsi_cls_conn *conn, पूर्णांक flag)
अणु
	/*
	 * It is important that this path करोesn't rely on
	 * rx_queue_mutex, otherwise, a thपढ़ो करोing allocation on a
	 * start_session/start_connection could sleep रुकोing on a
	 * ग_लिखोback to a failed iscsi device, that cannot be recovered
	 * because the lock is held.  If we करोn't hold it here, the
	 * kernel stop_conn_work_fn has a chance to stop the broken
	 * session and resolve the allocation.
	 *
	 * Still, the user invoked .stop_conn() needs to be serialized
	 * with stop_conn_work_fn by a निजी mutex.  Not pretty, but
	 * it works.
	 */
	mutex_lock(&conn_mutex);
	चयन (flag) अणु
	हाल STOP_CONN_RECOVER:
		conn->state = ISCSI_CONN_FAILED;
		अवरोध;
	हाल STOP_CONN_TERM:
		conn->state = ISCSI_CONN_DOWN;
		अवरोध;
	शेष:
		iscsi_cls_conn_prपूर्णांकk(KERN_ERR, conn,
				      "invalid stop flag %d\n", flag);
		जाओ unlock;
	पूर्ण

	conn->transport->stop_conn(conn, flag);
unlock:
	mutex_unlock(&conn_mutex);
पूर्ण

अटल व्योम stop_conn_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iscsi_cls_conn *conn, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(recovery_list);

	spin_lock_irqsave(&connlock, flags);
	अगर (list_empty(&connlist_err)) अणु
		spin_unlock_irqrestore(&connlock, flags);
		वापस;
	पूर्ण
	list_splice_init(&connlist_err, &recovery_list);
	spin_unlock_irqrestore(&connlock, flags);

	list_क्रम_each_entry_safe(conn, पंचांगp, &recovery_list, conn_list_err) अणु
		uपूर्णांक32_t sid = iscsi_conn_get_sid(conn);
		काष्ठा iscsi_cls_session *session;

		session = iscsi_session_lookup(sid);
		अगर (session) अणु
			अगर (प्रणाली_state != SYSTEM_RUNNING) अणु
				session->recovery_पंचांगo = 0;
				iscsi_अगर_stop_conn(conn, STOP_CONN_TERM);
			पूर्ण अन्यथा अणु
				iscsi_अगर_stop_conn(conn, STOP_CONN_RECOVER);
			पूर्ण
		पूर्ण

		list_del_init(&conn->conn_list_err);
	पूर्ण
पूर्ण

व्योम iscsi_conn_error_event(काष्ठा iscsi_cls_conn *conn, क्रमागत iscsi_err error)
अणु
	काष्ठा nlmsghdr	*nlh;
	काष्ठा sk_buff	*skb;
	काष्ठा iscsi_uevent *ev;
	काष्ठा iscsi_पूर्णांकernal *priv;
	पूर्णांक len = nlmsg_total_size(माप(*ev));
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&connlock, flags);
	list_add(&conn->conn_list_err, &connlist_err);
	spin_unlock_irqrestore(&connlock, flags);
	queue_work(प्रणाली_unbound_wq, &stop_conn_work);

	priv = iscsi_अगर_transport_lookup(conn->transport);
	अगर (!priv)
		वापस;

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb) अणु
		iscsi_cls_conn_prपूर्णांकk(KERN_ERR, conn, "gracefully ignored "
				      "conn error (%d)\n", error);
		वापस;
	पूर्ण

	nlh = __nlmsg_put(skb, 0, 0, 0, (len - माप(*nlh)), 0);
	ev = nlmsg_data(nlh);
	ev->transport_handle = iscsi_handle(conn->transport);
	ev->type = ISCSI_KEVENT_CONN_ERROR;
	ev->r.connerror.error = error;
	ev->r.connerror.cid = conn->cid;
	ev->r.connerror.sid = iscsi_conn_get_sid(conn);

	iscsi_multicast_skb(skb, ISCSI_NL_GRP_ISCSID, GFP_ATOMIC);

	iscsi_cls_conn_prपूर्णांकk(KERN_INFO, conn, "detected conn error (%d)\n",
			      error);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_error_event);

व्योम iscsi_conn_login_event(काष्ठा iscsi_cls_conn *conn,
			    क्रमागत iscsi_conn_state state)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff  *skb;
	काष्ठा iscsi_uevent *ev;
	काष्ठा iscsi_पूर्णांकernal *priv;
	पूर्णांक len = nlmsg_total_size(माप(*ev));

	priv = iscsi_अगर_transport_lookup(conn->transport);
	अगर (!priv)
		वापस;

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb) अणु
		iscsi_cls_conn_prपूर्णांकk(KERN_ERR, conn, "gracefully ignored "
				      "conn login (%d)\n", state);
		वापस;
	पूर्ण

	nlh = __nlmsg_put(skb, 0, 0, 0, (len - माप(*nlh)), 0);
	ev = nlmsg_data(nlh);
	ev->transport_handle = iscsi_handle(conn->transport);
	ev->type = ISCSI_KEVENT_CONN_LOGIN_STATE;
	ev->r.conn_login.state = state;
	ev->r.conn_login.cid = conn->cid;
	ev->r.conn_login.sid = iscsi_conn_get_sid(conn);
	iscsi_multicast_skb(skb, ISCSI_NL_GRP_ISCSID, GFP_ATOMIC);

	iscsi_cls_conn_prपूर्णांकk(KERN_INFO, conn, "detected conn login (%d)\n",
			      state);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_conn_login_event);

व्योम iscsi_post_host_event(uपूर्णांक32_t host_no, काष्ठा iscsi_transport *transport,
			   क्रमागत iscsi_host_event_code code, uपूर्णांक32_t data_size,
			   uपूर्णांक8_t *data)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	काष्ठा iscsi_uevent *ev;
	पूर्णांक len = nlmsg_total_size(माप(*ev) + data_size);

	skb = alloc_skb(len, GFP_NOIO);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_ERR "gracefully ignored host event (%d):%d OOM\n",
		       host_no, code);
		वापस;
	पूर्ण

	nlh = __nlmsg_put(skb, 0, 0, 0, (len - माप(*nlh)), 0);
	ev = nlmsg_data(nlh);
	ev->transport_handle = iscsi_handle(transport);
	ev->type = ISCSI_KEVENT_HOST_EVENT;
	ev->r.host_event.host_no = host_no;
	ev->r.host_event.code = code;
	ev->r.host_event.data_size = data_size;

	अगर (data_size)
		स_नकल((अक्षर *)ev + माप(*ev), data, data_size);

	iscsi_multicast_skb(skb, ISCSI_NL_GRP_ISCSID, GFP_NOIO);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_post_host_event);

व्योम iscsi_ping_comp_event(uपूर्णांक32_t host_no, काष्ठा iscsi_transport *transport,
			   uपूर्णांक32_t status, uपूर्णांक32_t pid, uपूर्णांक32_t data_size,
			   uपूर्णांक8_t *data)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	काष्ठा iscsi_uevent *ev;
	पूर्णांक len = nlmsg_total_size(माप(*ev) + data_size);

	skb = alloc_skb(len, GFP_NOIO);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_ERR "gracefully ignored ping comp: OOM\n");
		वापस;
	पूर्ण

	nlh = __nlmsg_put(skb, 0, 0, 0, (len - माप(*nlh)), 0);
	ev = nlmsg_data(nlh);
	ev->transport_handle = iscsi_handle(transport);
	ev->type = ISCSI_KEVENT_PING_COMP;
	ev->r.ping_comp.host_no = host_no;
	ev->r.ping_comp.status = status;
	ev->r.ping_comp.pid = pid;
	ev->r.ping_comp.data_size = data_size;
	स_नकल((अक्षर *)ev + माप(*ev), data, data_size);

	iscsi_multicast_skb(skb, ISCSI_NL_GRP_ISCSID, GFP_NOIO);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_ping_comp_event);

अटल पूर्णांक
iscsi_अगर_send_reply(u32 portid, पूर्णांक type, व्योम *payload, पूर्णांक size)
अणु
	काष्ठा sk_buff	*skb;
	काष्ठा nlmsghdr	*nlh;
	पूर्णांक len = nlmsg_total_size(size);

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_ERR "Could not allocate skb to send reply.\n");
		वापस -ENOMEM;
	पूर्ण

	nlh = __nlmsg_put(skb, 0, 0, type, (len - माप(*nlh)), 0);
	स_नकल(nlmsg_data(nlh), payload, size);
	वापस iscsi_unicast_skb(skb, portid);
पूर्ण

अटल पूर्णांक
iscsi_अगर_get_stats(काष्ठा iscsi_transport *transport, काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा iscsi_uevent *ev = nlmsg_data(nlh);
	काष्ठा iscsi_stats *stats;
	काष्ठा sk_buff *skbstat;
	काष्ठा iscsi_cls_conn *conn;
	काष्ठा nlmsghdr	*nlhstat;
	काष्ठा iscsi_uevent *evstat;
	काष्ठा iscsi_पूर्णांकernal *priv;
	पूर्णांक len = nlmsg_total_size(माप(*ev) +
				   माप(काष्ठा iscsi_stats) +
				   माप(काष्ठा iscsi_stats_custom) *
				   ISCSI_STATS_CUSTOM_MAX);
	पूर्णांक err = 0;

	priv = iscsi_अगर_transport_lookup(transport);
	अगर (!priv)
		वापस -EINVAL;

	conn = iscsi_conn_lookup(ev->u.get_stats.sid, ev->u.get_stats.cid);
	अगर (!conn)
		वापस -EEXIST;

	करो अणु
		पूर्णांक actual_size;

		skbstat = alloc_skb(len, GFP_ATOMIC);
		अगर (!skbstat) अणु
			iscsi_cls_conn_prपूर्णांकk(KERN_ERR, conn, "can not "
					      "deliver stats: OOM\n");
			वापस -ENOMEM;
		पूर्ण

		nlhstat = __nlmsg_put(skbstat, 0, 0, 0,
				      (len - माप(*nlhstat)), 0);
		evstat = nlmsg_data(nlhstat);
		स_रखो(evstat, 0, माप(*evstat));
		evstat->transport_handle = iscsi_handle(conn->transport);
		evstat->type = nlh->nlmsg_type;
		evstat->u.get_stats.cid =
			ev->u.get_stats.cid;
		evstat->u.get_stats.sid =
			ev->u.get_stats.sid;
		stats = (काष्ठा iscsi_stats *)
			((अक्षर*)evstat + माप(*evstat));
		स_रखो(stats, 0, माप(*stats));

		transport->get_stats(conn, stats);
		actual_size = nlmsg_total_size(माप(काष्ठा iscsi_uevent) +
					       माप(काष्ठा iscsi_stats) +
					       माप(काष्ठा iscsi_stats_custom) *
					       stats->custom_length);
		actual_size -= माप(*nlhstat);
		actual_size = nlmsg_msg_size(actual_size);
		skb_trim(skbstat, NLMSG_ALIGN(actual_size));
		nlhstat->nlmsg_len = actual_size;

		err = iscsi_multicast_skb(skbstat, ISCSI_NL_GRP_ISCSID,
					  GFP_ATOMIC);
	पूर्ण जबतक (err < 0 && err != -ECONNREFUSED);

	वापस err;
पूर्ण

/**
 * iscsi_session_event - send session destr. completion event
 * @session: iscsi class session
 * @event: type of event
 */
पूर्णांक iscsi_session_event(काष्ठा iscsi_cls_session *session,
			क्रमागत iscsi_uevent_e event)
अणु
	काष्ठा iscsi_पूर्णांकernal *priv;
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_uevent *ev;
	काष्ठा sk_buff  *skb;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक rc, len = nlmsg_total_size(माप(*ev));

	priv = iscsi_अगर_transport_lookup(session->transport);
	अगर (!priv)
		वापस -EINVAL;
	shost = iscsi_session_to_shost(session);

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb) अणु
		iscsi_cls_session_prपूर्णांकk(KERN_ERR, session,
					 "Cannot notify userspace of session "
					 "event %u\n", event);
		वापस -ENOMEM;
	पूर्ण

	nlh = __nlmsg_put(skb, 0, 0, 0, (len - माप(*nlh)), 0);
	ev = nlmsg_data(nlh);
	ev->transport_handle = iscsi_handle(session->transport);

	ev->type = event;
	चयन (event) अणु
	हाल ISCSI_KEVENT_DESTROY_SESSION:
		ev->r.d_session.host_no = shost->host_no;
		ev->r.d_session.sid = session->sid;
		अवरोध;
	हाल ISCSI_KEVENT_CREATE_SESSION:
		ev->r.c_session_ret.host_no = shost->host_no;
		ev->r.c_session_ret.sid = session->sid;
		अवरोध;
	हाल ISCSI_KEVENT_UNBIND_SESSION:
		ev->r.unbind_session.host_no = shost->host_no;
		ev->r.unbind_session.sid = session->sid;
		अवरोध;
	शेष:
		iscsi_cls_session_prपूर्णांकk(KERN_ERR, session, "Invalid event "
					 "%u.\n", event);
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	/*
	 * this will occur अगर the daemon is not up, so we just warn
	 * the user and when the daemon is restarted it will handle it
	 */
	rc = iscsi_multicast_skb(skb, ISCSI_NL_GRP_ISCSID, GFP_KERNEL);
	अगर (rc == -ESRCH)
		iscsi_cls_session_prपूर्णांकk(KERN_ERR, session,
					 "Cannot notify userspace of session "
					 "event %u. Check iscsi daemon\n",
					 event);

	ISCSI_DBG_TRANS_SESSION(session, "Completed handling event %d rc %d\n",
				event, rc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_session_event);

अटल पूर्णांक
iscsi_अगर_create_session(काष्ठा iscsi_पूर्णांकernal *priv, काष्ठा iscsi_endpoपूर्णांक *ep,
			काष्ठा iscsi_uevent *ev, pid_t pid,
			uपूर्णांक32_t initial_cmdsn,	uपूर्णांक16_t cmds_max,
			uपूर्णांक16_t queue_depth)
अणु
	काष्ठा iscsi_transport *transport = priv->iscsi_transport;
	काष्ठा iscsi_cls_session *session;
	काष्ठा Scsi_Host *shost;

	session = transport->create_session(ep, cmds_max, queue_depth,
					    initial_cmdsn);
	अगर (!session)
		वापस -ENOMEM;

	session->creator = pid;
	shost = iscsi_session_to_shost(session);
	ev->r.c_session_ret.host_no = shost->host_no;
	ev->r.c_session_ret.sid = session->sid;
	ISCSI_DBG_TRANS_SESSION(session,
				"Completed creating transport session\n");
	वापस 0;
पूर्ण

अटल पूर्णांक
iscsi_अगर_create_conn(काष्ठा iscsi_transport *transport, काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा iscsi_cls_conn *conn;
	काष्ठा iscsi_cls_session *session;

	session = iscsi_session_lookup(ev->u.c_conn.sid);
	अगर (!session) अणु
		prपूर्णांकk(KERN_ERR "iscsi: invalid session %d.\n",
		       ev->u.c_conn.sid);
		वापस -EINVAL;
	पूर्ण

	conn = transport->create_conn(session, ev->u.c_conn.cid);
	अगर (!conn) अणु
		iscsi_cls_session_prपूर्णांकk(KERN_ERR, session,
					 "couldn't create a new connection.");
		वापस -ENOMEM;
	पूर्ण

	ev->r.c_conn_ret.sid = session->sid;
	ev->r.c_conn_ret.cid = conn->cid;

	ISCSI_DBG_TRANS_CONN(conn, "Completed creating transport conn\n");
	वापस 0;
पूर्ण

अटल पूर्णांक
iscsi_अगर_destroy_conn(काष्ठा iscsi_transport *transport, काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा iscsi_cls_conn *conn;
	अचिन्हित दीर्घ flags;

	conn = iscsi_conn_lookup(ev->u.d_conn.sid, ev->u.d_conn.cid);
	अगर (!conn)
		वापस -EINVAL;

	spin_lock_irqsave(&connlock, flags);
	अगर (!list_empty(&conn->conn_list_err)) अणु
		spin_unlock_irqrestore(&connlock, flags);
		वापस -EAGAIN;
	पूर्ण
	spin_unlock_irqrestore(&connlock, flags);

	ISCSI_DBG_TRANS_CONN(conn, "Destroying transport conn\n");

	mutex_lock(&conn_mutex);
	अगर (transport->destroy_conn)
		transport->destroy_conn(conn);
	mutex_unlock(&conn_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
iscsi_set_param(काष्ठा iscsi_transport *transport, काष्ठा iscsi_uevent *ev)
अणु
	अक्षर *data = (अक्षर*)ev + माप(*ev);
	काष्ठा iscsi_cls_conn *conn;
	काष्ठा iscsi_cls_session *session;
	पूर्णांक err = 0, value = 0;

	अगर (ev->u.set_param.len > PAGE_SIZE)
		वापस -EINVAL;

	session = iscsi_session_lookup(ev->u.set_param.sid);
	conn = iscsi_conn_lookup(ev->u.set_param.sid, ev->u.set_param.cid);
	अगर (!conn || !session)
		वापस -EINVAL;

	चयन (ev->u.set_param.param) अणु
	हाल ISCSI_PARAM_SESS_RECOVERY_TMO:
		माला_पूछो(data, "%d", &value);
		अगर (!session->recovery_पंचांगo_sysfs_override)
			session->recovery_पंचांगo = value;
		अवरोध;
	शेष:
		err = transport->set_param(conn, ev->u.set_param.param,
					   data, ev->u.set_param.len);
		अगर ((conn->state == ISCSI_CONN_BOUND) ||
			(conn->state == ISCSI_CONN_UP)) अणु
			err = transport->set_param(conn, ev->u.set_param.param,
					data, ev->u.set_param.len);
		पूर्ण अन्यथा अणु
			वापस -ENOTCONN;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक iscsi_अगर_ep_connect(काष्ठा iscsi_transport *transport,
			       काष्ठा iscsi_uevent *ev, पूर्णांक msg_type)
अणु
	काष्ठा iscsi_endpoपूर्णांक *ep;
	काष्ठा sockaddr *dst_addr;
	काष्ठा Scsi_Host *shost = शून्य;
	पूर्णांक non_blocking, err = 0;

	अगर (!transport->ep_connect)
		वापस -EINVAL;

	अगर (msg_type == ISCSI_UEVENT_TRANSPORT_EP_CONNECT_THROUGH_HOST) अणु
		shost = scsi_host_lookup(ev->u.ep_connect_through_host.host_no);
		अगर (!shost) अणु
			prपूर्णांकk(KERN_ERR "ep connect failed. Could not find "
			       "host no %u\n",
			       ev->u.ep_connect_through_host.host_no);
			वापस -ENODEV;
		पूर्ण
		non_blocking = ev->u.ep_connect_through_host.non_blocking;
	पूर्ण अन्यथा
		non_blocking = ev->u.ep_connect.non_blocking;

	dst_addr = (काष्ठा sockaddr *)((अक्षर*)ev + माप(*ev));
	ep = transport->ep_connect(shost, dst_addr, non_blocking);
	अगर (IS_ERR(ep)) अणु
		err = PTR_ERR(ep);
		जाओ release_host;
	पूर्ण

	ev->r.ep_connect_ret.handle = ep->id;
release_host:
	अगर (shost)
		scsi_host_put(shost);
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_अगर_ep_disconnect(काष्ठा iscsi_transport *transport,
				  u64 ep_handle)
अणु
	काष्ठा iscsi_cls_conn *conn;
	काष्ठा iscsi_endpoपूर्णांक *ep;

	अगर (!transport->ep_disconnect)
		वापस -EINVAL;

	ep = iscsi_lookup_endpoपूर्णांक(ep_handle);
	अगर (!ep)
		वापस -EINVAL;
	conn = ep->conn;
	अगर (conn) अणु
		mutex_lock(&conn->ep_mutex);
		conn->ep = शून्य;
		mutex_unlock(&conn->ep_mutex);
		conn->state = ISCSI_CONN_FAILED;
	पूर्ण

	transport->ep_disconnect(ep);
	वापस 0;
पूर्ण

अटल पूर्णांक
iscsi_अगर_transport_ep(काष्ठा iscsi_transport *transport,
		      काष्ठा iscsi_uevent *ev, पूर्णांक msg_type)
अणु
	काष्ठा iscsi_endpoपूर्णांक *ep;
	पूर्णांक rc = 0;

	चयन (msg_type) अणु
	हाल ISCSI_UEVENT_TRANSPORT_EP_CONNECT_THROUGH_HOST:
	हाल ISCSI_UEVENT_TRANSPORT_EP_CONNECT:
		rc = iscsi_अगर_ep_connect(transport, ev, msg_type);
		अवरोध;
	हाल ISCSI_UEVENT_TRANSPORT_EP_POLL:
		अगर (!transport->ep_poll)
			वापस -EINVAL;

		ep = iscsi_lookup_endpoपूर्णांक(ev->u.ep_poll.ep_handle);
		अगर (!ep)
			वापस -EINVAL;

		ev->r.retcode = transport->ep_poll(ep,
						   ev->u.ep_poll.समयout_ms);
		अवरोध;
	हाल ISCSI_UEVENT_TRANSPORT_EP_DISCONNECT:
		rc = iscsi_अगर_ep_disconnect(transport,
					    ev->u.ep_disconnect.ep_handle);
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
iscsi_tgt_dscvr(काष्ठा iscsi_transport *transport,
		काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा sockaddr *dst_addr;
	पूर्णांक err;

	अगर (!transport->tgt_dscvr)
		वापस -EINVAL;

	shost = scsi_host_lookup(ev->u.tgt_dscvr.host_no);
	अगर (!shost) अणु
		prपूर्णांकk(KERN_ERR "target discovery could not find host no %u\n",
		       ev->u.tgt_dscvr.host_no);
		वापस -ENODEV;
	पूर्ण


	dst_addr = (काष्ठा sockaddr *)((अक्षर*)ev + माप(*ev));
	err = transport->tgt_dscvr(shost, ev->u.tgt_dscvr.type,
				   ev->u.tgt_dscvr.enable, dst_addr);
	scsi_host_put(shost);
	वापस err;
पूर्ण

अटल पूर्णांक
iscsi_set_host_param(काष्ठा iscsi_transport *transport,
		     काष्ठा iscsi_uevent *ev)
अणु
	अक्षर *data = (अक्षर*)ev + माप(*ev);
	काष्ठा Scsi_Host *shost;
	पूर्णांक err;

	अगर (!transport->set_host_param)
		वापस -ENOSYS;

	अगर (ev->u.set_host_param.len > PAGE_SIZE)
		वापस -EINVAL;

	shost = scsi_host_lookup(ev->u.set_host_param.host_no);
	अगर (!shost) अणु
		prपूर्णांकk(KERN_ERR "set_host_param could not find host no %u\n",
		       ev->u.set_host_param.host_no);
		वापस -ENODEV;
	पूर्ण

	err = transport->set_host_param(shost, ev->u.set_host_param.param,
					data, ev->u.set_host_param.len);
	scsi_host_put(shost);
	वापस err;
पूर्ण

अटल पूर्णांक
iscsi_set_path(काष्ठा iscsi_transport *transport, काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_path *params;
	पूर्णांक err;

	अगर (!transport->set_path)
		वापस -ENOSYS;

	shost = scsi_host_lookup(ev->u.set_path.host_no);
	अगर (!shost) अणु
		prपूर्णांकk(KERN_ERR "set path could not find host no %u\n",
		       ev->u.set_path.host_no);
		वापस -ENODEV;
	पूर्ण

	params = (काष्ठा iscsi_path *)((अक्षर *)ev + माप(*ev));
	err = transport->set_path(shost, params);

	scsi_host_put(shost);
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_session_has_conns(पूर्णांक sid)
अणु
	काष्ठा iscsi_cls_conn *conn;
	अचिन्हित दीर्घ flags;
	पूर्णांक found = 0;

	spin_lock_irqsave(&connlock, flags);
	list_क्रम_each_entry(conn, &connlist, conn_list) अणु
		अगर (iscsi_conn_get_sid(conn) == sid) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&connlock, flags);

	वापस found;
पूर्ण

अटल पूर्णांक
iscsi_set_अगरace_params(काष्ठा iscsi_transport *transport,
		       काष्ठा iscsi_uevent *ev, uपूर्णांक32_t len)
अणु
	अक्षर *data = (अक्षर *)ev + माप(*ev);
	काष्ठा Scsi_Host *shost;
	पूर्णांक err;

	अगर (!transport->set_अगरace_param)
		वापस -ENOSYS;

	shost = scsi_host_lookup(ev->u.set_अगरace_params.host_no);
	अगर (!shost) अणु
		prपूर्णांकk(KERN_ERR "set_iface_params could not find host no %u\n",
		       ev->u.set_अगरace_params.host_no);
		वापस -ENODEV;
	पूर्ण

	err = transport->set_अगरace_param(shost, data, len);
	scsi_host_put(shost);
	वापस err;
पूर्ण

अटल पूर्णांक
iscsi_send_ping(काष्ठा iscsi_transport *transport, काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा sockaddr *dst_addr;
	पूर्णांक err;

	अगर (!transport->send_ping)
		वापस -ENOSYS;

	shost = scsi_host_lookup(ev->u.iscsi_ping.host_no);
	अगर (!shost) अणु
		prपूर्णांकk(KERN_ERR "iscsi_ping could not find host no %u\n",
		       ev->u.iscsi_ping.host_no);
		वापस -ENODEV;
	पूर्ण

	dst_addr = (काष्ठा sockaddr *)((अक्षर *)ev + माप(*ev));
	err = transport->send_ping(shost, ev->u.iscsi_ping.अगरace_num,
				   ev->u.iscsi_ping.अगरace_type,
				   ev->u.iscsi_ping.payload_size,
				   ev->u.iscsi_ping.pid,
				   dst_addr);
	scsi_host_put(shost);
	वापस err;
पूर्ण

अटल पूर्णांक
iscsi_get_chap(काष्ठा iscsi_transport *transport, काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा iscsi_uevent *ev = nlmsg_data(nlh);
	काष्ठा Scsi_Host *shost = शून्य;
	काष्ठा iscsi_chap_rec *chap_rec;
	काष्ठा iscsi_पूर्णांकernal *priv;
	काष्ठा sk_buff *skbchap;
	काष्ठा nlmsghdr *nlhchap;
	काष्ठा iscsi_uevent *evchap;
	uपूर्णांक32_t chap_buf_size;
	पूर्णांक len, err = 0;
	अक्षर *buf;

	अगर (!transport->get_chap)
		वापस -EINVAL;

	priv = iscsi_अगर_transport_lookup(transport);
	अगर (!priv)
		वापस -EINVAL;

	chap_buf_size = (ev->u.get_chap.num_entries * माप(*chap_rec));
	len = nlmsg_total_size(माप(*ev) + chap_buf_size);

	shost = scsi_host_lookup(ev->u.get_chap.host_no);
	अगर (!shost) अणु
		prपूर्णांकk(KERN_ERR "%s: failed. Could not find host no %u\n",
		       __func__, ev->u.get_chap.host_no);
		वापस -ENODEV;
	पूर्ण

	करो अणु
		पूर्णांक actual_size;

		skbchap = alloc_skb(len, GFP_KERNEL);
		अगर (!skbchap) अणु
			prपूर्णांकk(KERN_ERR "can not deliver chap: OOM\n");
			err = -ENOMEM;
			जाओ निकास_get_chap;
		पूर्ण

		nlhchap = __nlmsg_put(skbchap, 0, 0, 0,
				      (len - माप(*nlhchap)), 0);
		evchap = nlmsg_data(nlhchap);
		स_रखो(evchap, 0, माप(*evchap));
		evchap->transport_handle = iscsi_handle(transport);
		evchap->type = nlh->nlmsg_type;
		evchap->u.get_chap.host_no = ev->u.get_chap.host_no;
		evchap->u.get_chap.chap_tbl_idx = ev->u.get_chap.chap_tbl_idx;
		evchap->u.get_chap.num_entries = ev->u.get_chap.num_entries;
		buf = (अक्षर *)evchap + माप(*evchap);
		स_रखो(buf, 0, chap_buf_size);

		err = transport->get_chap(shost, ev->u.get_chap.chap_tbl_idx,
				    &evchap->u.get_chap.num_entries, buf);

		actual_size = nlmsg_total_size(माप(*ev) + chap_buf_size);
		skb_trim(skbchap, NLMSG_ALIGN(actual_size));
		nlhchap->nlmsg_len = actual_size;

		err = iscsi_multicast_skb(skbchap, ISCSI_NL_GRP_ISCSID,
					  GFP_KERNEL);
	पूर्ण जबतक (err < 0 && err != -ECONNREFUSED);

निकास_get_chap:
	scsi_host_put(shost);
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_set_chap(काष्ठा iscsi_transport *transport,
			  काष्ठा iscsi_uevent *ev, uपूर्णांक32_t len)
अणु
	अक्षर *data = (अक्षर *)ev + माप(*ev);
	काष्ठा Scsi_Host *shost;
	पूर्णांक err = 0;

	अगर (!transport->set_chap)
		वापस -ENOSYS;

	shost = scsi_host_lookup(ev->u.set_path.host_no);
	अगर (!shost) अणु
		pr_err("%s could not find host no %u\n",
		       __func__, ev->u.set_path.host_no);
		वापस -ENODEV;
	पूर्ण

	err = transport->set_chap(shost, data, len);
	scsi_host_put(shost);
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_delete_chap(काष्ठा iscsi_transport *transport,
			     काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा Scsi_Host *shost;
	पूर्णांक err = 0;

	अगर (!transport->delete_chap)
		वापस -ENOSYS;

	shost = scsi_host_lookup(ev->u.delete_chap.host_no);
	अगर (!shost) अणु
		prपूर्णांकk(KERN_ERR "%s could not find host no %u\n",
		       __func__, ev->u.delete_chap.host_no);
		वापस -ENODEV;
	पूर्ण

	err = transport->delete_chap(shost, ev->u.delete_chap.chap_tbl_idx);
	scsi_host_put(shost);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा अणु
	क्रमागत iscsi_discovery_parent_type value;
	अक्षर				*name;
पूर्ण iscsi_discovery_parent_names[] = अणु
	अणुISCSI_DISC_PARENT_UNKNOWN,	"Unknown" पूर्ण,
	अणुISCSI_DISC_PARENT_SENDTGT,	"Sendtarget" पूर्ण,
	अणुISCSI_DISC_PARENT_ISNS,	"isns" पूर्ण,
पूर्ण;

अक्षर *iscsi_get_discovery_parent_name(पूर्णांक parent_type)
अणु
	पूर्णांक i;
	अक्षर *state = "Unknown!";

	क्रम (i = 0; i < ARRAY_SIZE(iscsi_discovery_parent_names); i++) अणु
		अगर (iscsi_discovery_parent_names[i].value & parent_type) अणु
			state = iscsi_discovery_parent_names[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_get_discovery_parent_name);

अटल पूर्णांक iscsi_set_flashnode_param(काष्ठा iscsi_transport *transport,
				     काष्ठा iscsi_uevent *ev, uपूर्णांक32_t len)
अणु
	अक्षर *data = (अक्षर *)ev + माप(*ev);
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_bus_flash_session *fnode_sess;
	काष्ठा iscsi_bus_flash_conn *fnode_conn;
	काष्ठा device *dev;
	uपूर्णांक32_t idx;
	पूर्णांक err = 0;

	अगर (!transport->set_flashnode_param) अणु
		err = -ENOSYS;
		जाओ निकास_set_fnode;
	पूर्ण

	shost = scsi_host_lookup(ev->u.set_flashnode.host_no);
	अगर (!shost) अणु
		pr_err("%s could not find host no %u\n",
		       __func__, ev->u.set_flashnode.host_no);
		err = -ENODEV;
		जाओ निकास_set_fnode;
	पूर्ण

	idx = ev->u.set_flashnode.flashnode_idx;
	fnode_sess = iscsi_get_flashnode_by_index(shost, idx);
	अगर (!fnode_sess) अणु
		pr_err("%s could not find flashnode %u for host no %u\n",
		       __func__, idx, ev->u.set_flashnode.host_no);
		err = -ENODEV;
		जाओ put_host;
	पूर्ण

	dev = iscsi_find_flashnode_conn(fnode_sess);
	अगर (!dev) अणु
		err = -ENODEV;
		जाओ put_sess;
	पूर्ण

	fnode_conn = iscsi_dev_to_flash_conn(dev);
	err = transport->set_flashnode_param(fnode_sess, fnode_conn, data, len);
	put_device(dev);

put_sess:
	put_device(&fnode_sess->dev);

put_host:
	scsi_host_put(shost);

निकास_set_fnode:
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_new_flashnode(काष्ठा iscsi_transport *transport,
			       काष्ठा iscsi_uevent *ev, uपूर्णांक32_t len)
अणु
	अक्षर *data = (अक्षर *)ev + माप(*ev);
	काष्ठा Scsi_Host *shost;
	पूर्णांक index;
	पूर्णांक err = 0;

	अगर (!transport->new_flashnode) अणु
		err = -ENOSYS;
		जाओ निकास_new_fnode;
	पूर्ण

	shost = scsi_host_lookup(ev->u.new_flashnode.host_no);
	अगर (!shost) अणु
		pr_err("%s could not find host no %u\n",
		       __func__, ev->u.new_flashnode.host_no);
		err = -ENODEV;
		जाओ put_host;
	पूर्ण

	index = transport->new_flashnode(shost, data, len);

	अगर (index >= 0)
		ev->r.new_flashnode_ret.flashnode_idx = index;
	अन्यथा
		err = -EIO;

put_host:
	scsi_host_put(shost);

निकास_new_fnode:
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_del_flashnode(काष्ठा iscsi_transport *transport,
			       काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_bus_flash_session *fnode_sess;
	uपूर्णांक32_t idx;
	पूर्णांक err = 0;

	अगर (!transport->del_flashnode) अणु
		err = -ENOSYS;
		जाओ निकास_del_fnode;
	पूर्ण

	shost = scsi_host_lookup(ev->u.del_flashnode.host_no);
	अगर (!shost) अणु
		pr_err("%s could not find host no %u\n",
		       __func__, ev->u.del_flashnode.host_no);
		err = -ENODEV;
		जाओ put_host;
	पूर्ण

	idx = ev->u.del_flashnode.flashnode_idx;
	fnode_sess = iscsi_get_flashnode_by_index(shost, idx);
	अगर (!fnode_sess) अणु
		pr_err("%s could not find flashnode %u for host no %u\n",
		       __func__, idx, ev->u.del_flashnode.host_no);
		err = -ENODEV;
		जाओ put_host;
	पूर्ण

	err = transport->del_flashnode(fnode_sess);
	put_device(&fnode_sess->dev);

put_host:
	scsi_host_put(shost);

निकास_del_fnode:
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_login_flashnode(काष्ठा iscsi_transport *transport,
				 काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_bus_flash_session *fnode_sess;
	काष्ठा iscsi_bus_flash_conn *fnode_conn;
	काष्ठा device *dev;
	uपूर्णांक32_t idx;
	पूर्णांक err = 0;

	अगर (!transport->login_flashnode) अणु
		err = -ENOSYS;
		जाओ निकास_login_fnode;
	पूर्ण

	shost = scsi_host_lookup(ev->u.login_flashnode.host_no);
	अगर (!shost) अणु
		pr_err("%s could not find host no %u\n",
		       __func__, ev->u.login_flashnode.host_no);
		err = -ENODEV;
		जाओ put_host;
	पूर्ण

	idx = ev->u.login_flashnode.flashnode_idx;
	fnode_sess = iscsi_get_flashnode_by_index(shost, idx);
	अगर (!fnode_sess) अणु
		pr_err("%s could not find flashnode %u for host no %u\n",
		       __func__, idx, ev->u.login_flashnode.host_no);
		err = -ENODEV;
		जाओ put_host;
	पूर्ण

	dev = iscsi_find_flashnode_conn(fnode_sess);
	अगर (!dev) अणु
		err = -ENODEV;
		जाओ put_sess;
	पूर्ण

	fnode_conn = iscsi_dev_to_flash_conn(dev);
	err = transport->login_flashnode(fnode_sess, fnode_conn);
	put_device(dev);

put_sess:
	put_device(&fnode_sess->dev);

put_host:
	scsi_host_put(shost);

निकास_login_fnode:
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_logout_flashnode(काष्ठा iscsi_transport *transport,
				  काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_bus_flash_session *fnode_sess;
	काष्ठा iscsi_bus_flash_conn *fnode_conn;
	काष्ठा device *dev;
	uपूर्णांक32_t idx;
	पूर्णांक err = 0;

	अगर (!transport->logout_flashnode) अणु
		err = -ENOSYS;
		जाओ निकास_logout_fnode;
	पूर्ण

	shost = scsi_host_lookup(ev->u.logout_flashnode.host_no);
	अगर (!shost) अणु
		pr_err("%s could not find host no %u\n",
		       __func__, ev->u.logout_flashnode.host_no);
		err = -ENODEV;
		जाओ put_host;
	पूर्ण

	idx = ev->u.logout_flashnode.flashnode_idx;
	fnode_sess = iscsi_get_flashnode_by_index(shost, idx);
	अगर (!fnode_sess) अणु
		pr_err("%s could not find flashnode %u for host no %u\n",
		       __func__, idx, ev->u.logout_flashnode.host_no);
		err = -ENODEV;
		जाओ put_host;
	पूर्ण

	dev = iscsi_find_flashnode_conn(fnode_sess);
	अगर (!dev) अणु
		err = -ENODEV;
		जाओ put_sess;
	पूर्ण

	fnode_conn = iscsi_dev_to_flash_conn(dev);

	err = transport->logout_flashnode(fnode_sess, fnode_conn);
	put_device(dev);

put_sess:
	put_device(&fnode_sess->dev);

put_host:
	scsi_host_put(shost);

निकास_logout_fnode:
	वापस err;
पूर्ण

अटल पूर्णांक iscsi_logout_flashnode_sid(काष्ठा iscsi_transport *transport,
				      काष्ठा iscsi_uevent *ev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_cls_session *session;
	पूर्णांक err = 0;

	अगर (!transport->logout_flashnode_sid) अणु
		err = -ENOSYS;
		जाओ निकास_logout_sid;
	पूर्ण

	shost = scsi_host_lookup(ev->u.logout_flashnode_sid.host_no);
	अगर (!shost) अणु
		pr_err("%s could not find host no %u\n",
		       __func__, ev->u.logout_flashnode.host_no);
		err = -ENODEV;
		जाओ put_host;
	पूर्ण

	session = iscsi_session_lookup(ev->u.logout_flashnode_sid.sid);
	अगर (!session) अणु
		pr_err("%s could not find session id %u\n",
		       __func__, ev->u.logout_flashnode_sid.sid);
		err = -EINVAL;
		जाओ put_host;
	पूर्ण

	err = transport->logout_flashnode_sid(session);

put_host:
	scsi_host_put(shost);

निकास_logout_sid:
	वापस err;
पूर्ण

अटल पूर्णांक
iscsi_get_host_stats(काष्ठा iscsi_transport *transport, काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा iscsi_uevent *ev = nlmsg_data(nlh);
	काष्ठा Scsi_Host *shost = शून्य;
	काष्ठा iscsi_पूर्णांकernal *priv;
	काष्ठा sk_buff *skbhost_stats;
	काष्ठा nlmsghdr *nlhhost_stats;
	काष्ठा iscsi_uevent *evhost_stats;
	पूर्णांक host_stats_size = 0;
	पूर्णांक len, err = 0;
	अक्षर *buf;

	अगर (!transport->get_host_stats)
		वापस -ENOSYS;

	priv = iscsi_अगर_transport_lookup(transport);
	अगर (!priv)
		वापस -EINVAL;

	host_stats_size = माप(काष्ठा iscsi_offload_host_stats);
	len = nlmsg_total_size(माप(*ev) + host_stats_size);

	shost = scsi_host_lookup(ev->u.get_host_stats.host_no);
	अगर (!shost) अणु
		pr_err("%s: failed. Could not find host no %u\n",
		       __func__, ev->u.get_host_stats.host_no);
		वापस -ENODEV;
	पूर्ण

	करो अणु
		पूर्णांक actual_size;

		skbhost_stats = alloc_skb(len, GFP_KERNEL);
		अगर (!skbhost_stats) अणु
			pr_err("cannot deliver host stats: OOM\n");
			err = -ENOMEM;
			जाओ निकास_host_stats;
		पूर्ण

		nlhhost_stats = __nlmsg_put(skbhost_stats, 0, 0, 0,
				      (len - माप(*nlhhost_stats)), 0);
		evhost_stats = nlmsg_data(nlhhost_stats);
		स_रखो(evhost_stats, 0, माप(*evhost_stats));
		evhost_stats->transport_handle = iscsi_handle(transport);
		evhost_stats->type = nlh->nlmsg_type;
		evhost_stats->u.get_host_stats.host_no =
					ev->u.get_host_stats.host_no;
		buf = (अक्षर *)evhost_stats + माप(*evhost_stats);
		स_रखो(buf, 0, host_stats_size);

		err = transport->get_host_stats(shost, buf, host_stats_size);
		अगर (err) अणु
			kमुक्त_skb(skbhost_stats);
			जाओ निकास_host_stats;
		पूर्ण

		actual_size = nlmsg_total_size(माप(*ev) + host_stats_size);
		skb_trim(skbhost_stats, NLMSG_ALIGN(actual_size));
		nlhhost_stats->nlmsg_len = actual_size;

		err = iscsi_multicast_skb(skbhost_stats, ISCSI_NL_GRP_ISCSID,
					  GFP_KERNEL);
	पूर्ण जबतक (err < 0 && err != -ECONNREFUSED);

निकास_host_stats:
	scsi_host_put(shost);
	वापस err;
पूर्ण


अटल पूर्णांक
iscsi_अगर_recv_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh, uपूर्णांक32_t *group)
अणु
	पूर्णांक err = 0;
	u32 portid;
	u32 pdu_len;
	काष्ठा iscsi_uevent *ev = nlmsg_data(nlh);
	काष्ठा iscsi_transport *transport = शून्य;
	काष्ठा iscsi_पूर्णांकernal *priv;
	काष्ठा iscsi_cls_session *session;
	काष्ठा iscsi_cls_conn *conn;
	काष्ठा iscsi_endpoपूर्णांक *ep = शून्य;

	अगर (!netlink_capable(skb, CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (nlh->nlmsg_type == ISCSI_UEVENT_PATH_UPDATE)
		*group = ISCSI_NL_GRP_UIP;
	अन्यथा
		*group = ISCSI_NL_GRP_ISCSID;

	priv = iscsi_अगर_transport_lookup(iscsi_ptr(ev->transport_handle));
	अगर (!priv)
		वापस -EINVAL;
	transport = priv->iscsi_transport;

	अगर (!try_module_get(transport->owner))
		वापस -EINVAL;

	portid = NETLINK_CB(skb).portid;

	चयन (nlh->nlmsg_type) अणु
	हाल ISCSI_UEVENT_CREATE_SESSION:
		err = iscsi_अगर_create_session(priv, ep, ev,
					      portid,
					      ev->u.c_session.initial_cmdsn,
					      ev->u.c_session.cmds_max,
					      ev->u.c_session.queue_depth);
		अवरोध;
	हाल ISCSI_UEVENT_CREATE_BOUND_SESSION:
		ep = iscsi_lookup_endpoपूर्णांक(ev->u.c_bound_session.ep_handle);
		अगर (!ep) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		err = iscsi_अगर_create_session(priv, ep, ev,
					portid,
					ev->u.c_bound_session.initial_cmdsn,
					ev->u.c_bound_session.cmds_max,
					ev->u.c_bound_session.queue_depth);
		अवरोध;
	हाल ISCSI_UEVENT_DESTROY_SESSION:
		session = iscsi_session_lookup(ev->u.d_session.sid);
		अगर (!session)
			err = -EINVAL;
		अन्यथा अगर (iscsi_session_has_conns(ev->u.d_session.sid))
			err = -EBUSY;
		अन्यथा
			transport->destroy_session(session);
		अवरोध;
	हाल ISCSI_UEVENT_DESTROY_SESSION_ASYNC:
		session = iscsi_session_lookup(ev->u.d_session.sid);
		अगर (!session)
			err = -EINVAL;
		अन्यथा अगर (iscsi_session_has_conns(ev->u.d_session.sid))
			err = -EBUSY;
		अन्यथा अणु
			अचिन्हित दीर्घ flags;

			/* Prevent this session from being found again */
			spin_lock_irqsave(&sesslock, flags);
			list_del_init(&session->sess_list);
			spin_unlock_irqrestore(&sesslock, flags);

			queue_work(iscsi_destroy_workq, &session->destroy_work);
		पूर्ण
		अवरोध;
	हाल ISCSI_UEVENT_UNBIND_SESSION:
		session = iscsi_session_lookup(ev->u.d_session.sid);
		अगर (session)
			scsi_queue_work(iscsi_session_to_shost(session),
					&session->unbind_work);
		अन्यथा
			err = -EINVAL;
		अवरोध;
	हाल ISCSI_UEVENT_CREATE_CONN:
		err = iscsi_अगर_create_conn(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_DESTROY_CONN:
		err = iscsi_अगर_destroy_conn(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_BIND_CONN:
		session = iscsi_session_lookup(ev->u.b_conn.sid);
		conn = iscsi_conn_lookup(ev->u.b_conn.sid, ev->u.b_conn.cid);

		अगर (conn && conn->ep)
			iscsi_अगर_ep_disconnect(transport, conn->ep->id);

		अगर (!session || !conn) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		mutex_lock(&conn_mutex);
		ev->r.retcode =	transport->bind_conn(session, conn,
						ev->u.b_conn.transport_eph,
						ev->u.b_conn.is_leading);
		अगर (!ev->r.retcode)
			conn->state = ISCSI_CONN_BOUND;
		mutex_unlock(&conn_mutex);

		अगर (ev->r.retcode || !transport->ep_connect)
			अवरोध;

		ep = iscsi_lookup_endpoपूर्णांक(ev->u.b_conn.transport_eph);
		अगर (ep) अणु
			ep->conn = conn;

			mutex_lock(&conn->ep_mutex);
			conn->ep = ep;
			mutex_unlock(&conn->ep_mutex);
		पूर्ण अन्यथा
			iscsi_cls_conn_prपूर्णांकk(KERN_ERR, conn,
					      "Could not set ep conn "
					      "binding\n");
		अवरोध;
	हाल ISCSI_UEVENT_SET_PARAM:
		err = iscsi_set_param(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_START_CONN:
		conn = iscsi_conn_lookup(ev->u.start_conn.sid, ev->u.start_conn.cid);
		अगर (conn) अणु
			mutex_lock(&conn_mutex);
			ev->r.retcode = transport->start_conn(conn);
			अगर (!ev->r.retcode)
				conn->state = ISCSI_CONN_UP;
			mutex_unlock(&conn_mutex);
		पूर्ण
		अन्यथा
			err = -EINVAL;
		अवरोध;
	हाल ISCSI_UEVENT_STOP_CONN:
		conn = iscsi_conn_lookup(ev->u.stop_conn.sid, ev->u.stop_conn.cid);
		अगर (conn)
			iscsi_अगर_stop_conn(conn, ev->u.stop_conn.flag);
		अन्यथा
			err = -EINVAL;
		अवरोध;
	हाल ISCSI_UEVENT_SEND_PDU:
		pdu_len = nlh->nlmsg_len - माप(*nlh) - माप(*ev);

		अगर ((ev->u.send_pdu.hdr_size > pdu_len) ||
		    (ev->u.send_pdu.data_size > (pdu_len - ev->u.send_pdu.hdr_size))) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		conn = iscsi_conn_lookup(ev->u.send_pdu.sid, ev->u.send_pdu.cid);
		अगर (conn) अणु
			mutex_lock(&conn_mutex);
			ev->r.retcode =	transport->send_pdu(conn,
				(काष्ठा iscsi_hdr*)((अक्षर*)ev + माप(*ev)),
				(अक्षर*)ev + माप(*ev) + ev->u.send_pdu.hdr_size,
				ev->u.send_pdu.data_size);
			mutex_unlock(&conn_mutex);
		पूर्ण
		अन्यथा
			err = -EINVAL;
		अवरोध;
	हाल ISCSI_UEVENT_GET_STATS:
		err = iscsi_अगर_get_stats(transport, nlh);
		अवरोध;
	हाल ISCSI_UEVENT_TRANSPORT_EP_CONNECT:
	हाल ISCSI_UEVENT_TRANSPORT_EP_POLL:
	हाल ISCSI_UEVENT_TRANSPORT_EP_DISCONNECT:
	हाल ISCSI_UEVENT_TRANSPORT_EP_CONNECT_THROUGH_HOST:
		err = iscsi_अगर_transport_ep(transport, ev, nlh->nlmsg_type);
		अवरोध;
	हाल ISCSI_UEVENT_TGT_DSCVR:
		err = iscsi_tgt_dscvr(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_SET_HOST_PARAM:
		err = iscsi_set_host_param(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_PATH_UPDATE:
		err = iscsi_set_path(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_SET_IFACE_PARAMS:
		err = iscsi_set_अगरace_params(transport, ev,
					     nlmsg_attrlen(nlh, माप(*ev)));
		अवरोध;
	हाल ISCSI_UEVENT_PING:
		err = iscsi_send_ping(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_GET_CHAP:
		err = iscsi_get_chap(transport, nlh);
		अवरोध;
	हाल ISCSI_UEVENT_DELETE_CHAP:
		err = iscsi_delete_chap(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_SET_FLASHNODE_PARAMS:
		err = iscsi_set_flashnode_param(transport, ev,
						nlmsg_attrlen(nlh,
							      माप(*ev)));
		अवरोध;
	हाल ISCSI_UEVENT_NEW_FLASHNODE:
		err = iscsi_new_flashnode(transport, ev,
					  nlmsg_attrlen(nlh, माप(*ev)));
		अवरोध;
	हाल ISCSI_UEVENT_DEL_FLASHNODE:
		err = iscsi_del_flashnode(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_LOGIN_FLASHNODE:
		err = iscsi_login_flashnode(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_LOGOUT_FLASHNODE:
		err = iscsi_logout_flashnode(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_LOGOUT_FLASHNODE_SID:
		err = iscsi_logout_flashnode_sid(transport, ev);
		अवरोध;
	हाल ISCSI_UEVENT_SET_CHAP:
		err = iscsi_set_chap(transport, ev,
				     nlmsg_attrlen(nlh, माप(*ev)));
		अवरोध;
	हाल ISCSI_UEVENT_GET_HOST_STATS:
		err = iscsi_get_host_stats(transport, nlh);
		अवरोध;
	शेष:
		err = -ENOSYS;
		अवरोध;
	पूर्ण

	module_put(transport->owner);
	वापस err;
पूर्ण

/*
 * Get message from skb.  Each message is processed by iscsi_अगर_recv_msg.
 * Malक्रमmed skbs with wrong lengths or invalid creds are not processed.
 */
अटल व्योम
iscsi_अगर_rx(काष्ठा sk_buff *skb)
अणु
	u32 portid = NETLINK_CB(skb).portid;

	mutex_lock(&rx_queue_mutex);
	जबतक (skb->len >= NLMSG_HDRLEN) अणु
		पूर्णांक err;
		uपूर्णांक32_t rlen;
		काष्ठा nlmsghdr	*nlh;
		काष्ठा iscsi_uevent *ev;
		uपूर्णांक32_t group;
		पूर्णांक retries = ISCSI_SEND_MAX_ALLOWED;

		nlh = nlmsg_hdr(skb);
		अगर (nlh->nlmsg_len < माप(*nlh) + माप(*ev) ||
		    skb->len < nlh->nlmsg_len) अणु
			अवरोध;
		पूर्ण

		ev = nlmsg_data(nlh);
		rlen = NLMSG_ALIGN(nlh->nlmsg_len);
		अगर (rlen > skb->len)
			rlen = skb->len;

		err = iscsi_अगर_recv_msg(skb, nlh, &group);
		अगर (err) अणु
			ev->type = ISCSI_KEVENT_IF_ERROR;
			ev->अगरerror = err;
		पूर्ण
		करो अणु
			/*
			 * special हाल क्रम GET_STATS:
			 * on success - sending reply and stats from
			 * inside of अगर_recv_msg(),
			 * on error - fall through.
			 */
			अगर (ev->type == ISCSI_UEVENT_GET_STATS && !err)
				अवरोध;
			अगर (ev->type == ISCSI_UEVENT_GET_CHAP && !err)
				अवरोध;
			err = iscsi_अगर_send_reply(portid, nlh->nlmsg_type,
						  ev, माप(*ev));
			अगर (err == -EAGAIN && --retries < 0) अणु
				prपूर्णांकk(KERN_WARNING "Send reply failed, error %d\n", err);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (err < 0 && err != -ECONNREFUSED && err != -ESRCH);
		skb_pull(skb, rlen);
	पूर्ण
	mutex_unlock(&rx_queue_mutex);
पूर्ण

#घोषणा ISCSI_CLASS_ATTR(_prefix,_name,_mode,_show,_store)		\
काष्ठा device_attribute dev_attr_##_prefix##_##_name =	\
	__ATTR(_name,_mode,_show,_store)

/*
 * iSCSI connection attrs
 */
#घोषणा iscsi_conn_attr_show(param)					\
अटल sमाप_प्रकार								\
show_conn_param_##param(काष्ठा device *dev, 				\
			काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा iscsi_cls_conn *conn = iscsi_dev_to_conn(dev->parent);	\
	काष्ठा iscsi_transport *t = conn->transport;			\
	वापस t->get_conn_param(conn, param, buf);			\
पूर्ण

#घोषणा iscsi_conn_attr(field, param)					\
	iscsi_conn_attr_show(param)					\
अटल ISCSI_CLASS_ATTR(conn, field, S_IRUGO, show_conn_param_##param,	\
			शून्य);

iscsi_conn_attr(max_recv_dlength, ISCSI_PARAM_MAX_RECV_DLENGTH);
iscsi_conn_attr(max_xmit_dlength, ISCSI_PARAM_MAX_XMIT_DLENGTH);
iscsi_conn_attr(header_digest, ISCSI_PARAM_HDRDGST_EN);
iscsi_conn_attr(data_digest, ISCSI_PARAM_DATADGST_EN);
iscsi_conn_attr(अगरmarker, ISCSI_PARAM_IFMARKER_EN);
iscsi_conn_attr(ofmarker, ISCSI_PARAM_OFMARKER_EN);
iscsi_conn_attr(persistent_port, ISCSI_PARAM_PERSISTENT_PORT);
iscsi_conn_attr(exp_statsn, ISCSI_PARAM_EXP_STATSN);
iscsi_conn_attr(persistent_address, ISCSI_PARAM_PERSISTENT_ADDRESS);
iscsi_conn_attr(ping_पंचांगo, ISCSI_PARAM_PING_TMO);
iscsi_conn_attr(recv_पंचांगo, ISCSI_PARAM_RECV_TMO);
iscsi_conn_attr(local_port, ISCSI_PARAM_LOCAL_PORT);
iscsi_conn_attr(statsn, ISCSI_PARAM_STATSN);
iscsi_conn_attr(keepalive_पंचांगo, ISCSI_PARAM_KEEPALIVE_TMO);
iscsi_conn_attr(max_segment_size, ISCSI_PARAM_MAX_SEGMENT_SIZE);
iscsi_conn_attr(tcp_बारtamp_stat, ISCSI_PARAM_TCP_TIMESTAMP_STAT);
iscsi_conn_attr(tcp_wsf_disable, ISCSI_PARAM_TCP_WSF_DISABLE);
iscsi_conn_attr(tcp_nagle_disable, ISCSI_PARAM_TCP_NAGLE_DISABLE);
iscsi_conn_attr(tcp_समयr_scale, ISCSI_PARAM_TCP_TIMER_SCALE);
iscsi_conn_attr(tcp_बारtamp_enable, ISCSI_PARAM_TCP_TIMESTAMP_EN);
iscsi_conn_attr(fragment_disable, ISCSI_PARAM_IP_FRAGMENT_DISABLE);
iscsi_conn_attr(ipv4_tos, ISCSI_PARAM_IPV4_TOS);
iscsi_conn_attr(ipv6_traffic_class, ISCSI_PARAM_IPV6_TC);
iscsi_conn_attr(ipv6_flow_label, ISCSI_PARAM_IPV6_FLOW_LABEL);
iscsi_conn_attr(is_fw_asचिन्हित_ipv6, ISCSI_PARAM_IS_FW_ASSIGNED_IPV6);
iscsi_conn_attr(tcp_xmit_wsf, ISCSI_PARAM_TCP_XMIT_WSF);
iscsi_conn_attr(tcp_recv_wsf, ISCSI_PARAM_TCP_RECV_WSF);
iscsi_conn_attr(local_ipaddr, ISCSI_PARAM_LOCAL_IPADDR);

अटल स्थिर अक्षर *स्थिर connection_state_names[] = अणु
	[ISCSI_CONN_UP] = "up",
	[ISCSI_CONN_DOWN] = "down",
	[ISCSI_CONN_FAILED] = "failed",
	[ISCSI_CONN_BOUND] = "bound"
पूर्ण;

अटल sमाप_प्रकार show_conn_state(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iscsi_cls_conn *conn = iscsi_dev_to_conn(dev->parent);
	स्थिर अक्षर *state = "unknown";

	अगर (conn->state >= 0 &&
	    conn->state < ARRAY_SIZE(connection_state_names))
		state = connection_state_names[conn->state];

	वापस sysfs_emit(buf, "%s\n", state);
पूर्ण
अटल ISCSI_CLASS_ATTR(conn, state, S_IRUGO, show_conn_state,
			शून्य);

#घोषणा iscsi_conn_ep_attr_show(param)					\
अटल sमाप_प्रकार show_conn_ep_param_##param(काष्ठा device *dev,		\
					  काष्ठा device_attribute *attr,\
					  अक्षर *buf)			\
अणु									\
	काष्ठा iscsi_cls_conn *conn = iscsi_dev_to_conn(dev->parent);	\
	काष्ठा iscsi_transport *t = conn->transport;			\
	काष्ठा iscsi_endpoपूर्णांक *ep;					\
	sमाप_प्रकार rc;							\
									\
	/*								\
	 * Need to make sure ep_disconnect करोes not मुक्त the LLD's	\
	 * पूर्णांकerconnect resources जबतक we are trying to पढ़ो them.	\
	 */								\
	mutex_lock(&conn->ep_mutex);					\
	ep = conn->ep;							\
	अगर (!ep && t->ep_connect) अणु					\
		mutex_unlock(&conn->ep_mutex);				\
		वापस -ENOTCONN;					\
	पूर्ण								\
									\
	अगर (ep)								\
		rc = t->get_ep_param(ep, param, buf);			\
	अन्यथा								\
		rc = t->get_conn_param(conn, param, buf);		\
	mutex_unlock(&conn->ep_mutex);					\
	वापस rc;							\
पूर्ण

#घोषणा iscsi_conn_ep_attr(field, param)				\
	iscsi_conn_ep_attr_show(param)					\
अटल ISCSI_CLASS_ATTR(conn, field, S_IRUGO,				\
			show_conn_ep_param_##param, शून्य);

iscsi_conn_ep_attr(address, ISCSI_PARAM_CONN_ADDRESS);
iscsi_conn_ep_attr(port, ISCSI_PARAM_CONN_PORT);

अटल काष्ठा attribute *iscsi_conn_attrs[] = अणु
	&dev_attr_conn_max_recv_dlength.attr,
	&dev_attr_conn_max_xmit_dlength.attr,
	&dev_attr_conn_header_digest.attr,
	&dev_attr_conn_data_digest.attr,
	&dev_attr_conn_अगरmarker.attr,
	&dev_attr_conn_ofmarker.attr,
	&dev_attr_conn_address.attr,
	&dev_attr_conn_port.attr,
	&dev_attr_conn_exp_statsn.attr,
	&dev_attr_conn_persistent_address.attr,
	&dev_attr_conn_persistent_port.attr,
	&dev_attr_conn_ping_पंचांगo.attr,
	&dev_attr_conn_recv_पंचांगo.attr,
	&dev_attr_conn_local_port.attr,
	&dev_attr_conn_statsn.attr,
	&dev_attr_conn_keepalive_पंचांगo.attr,
	&dev_attr_conn_max_segment_size.attr,
	&dev_attr_conn_tcp_बारtamp_stat.attr,
	&dev_attr_conn_tcp_wsf_disable.attr,
	&dev_attr_conn_tcp_nagle_disable.attr,
	&dev_attr_conn_tcp_समयr_scale.attr,
	&dev_attr_conn_tcp_बारtamp_enable.attr,
	&dev_attr_conn_fragment_disable.attr,
	&dev_attr_conn_ipv4_tos.attr,
	&dev_attr_conn_ipv6_traffic_class.attr,
	&dev_attr_conn_ipv6_flow_label.attr,
	&dev_attr_conn_is_fw_asचिन्हित_ipv6.attr,
	&dev_attr_conn_tcp_xmit_wsf.attr,
	&dev_attr_conn_tcp_recv_wsf.attr,
	&dev_attr_conn_local_ipaddr.attr,
	&dev_attr_conn_state.attr,
	शून्य,
पूर्ण;

अटल umode_t iscsi_conn_attr_is_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *cdev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा iscsi_cls_conn *conn = transport_class_to_conn(cdev);
	काष्ठा iscsi_transport *t = conn->transport;
	पूर्णांक param;

	अगर (attr == &dev_attr_conn_max_recv_dlength.attr)
		param = ISCSI_PARAM_MAX_RECV_DLENGTH;
	अन्यथा अगर (attr == &dev_attr_conn_max_xmit_dlength.attr)
		param = ISCSI_PARAM_MAX_XMIT_DLENGTH;
	अन्यथा अगर (attr == &dev_attr_conn_header_digest.attr)
		param = ISCSI_PARAM_HDRDGST_EN;
	अन्यथा अगर (attr == &dev_attr_conn_data_digest.attr)
		param = ISCSI_PARAM_DATADGST_EN;
	अन्यथा अगर (attr == &dev_attr_conn_अगरmarker.attr)
		param = ISCSI_PARAM_IFMARKER_EN;
	अन्यथा अगर (attr == &dev_attr_conn_ofmarker.attr)
		param = ISCSI_PARAM_OFMARKER_EN;
	अन्यथा अगर (attr == &dev_attr_conn_address.attr)
		param = ISCSI_PARAM_CONN_ADDRESS;
	अन्यथा अगर (attr == &dev_attr_conn_port.attr)
		param = ISCSI_PARAM_CONN_PORT;
	अन्यथा अगर (attr == &dev_attr_conn_exp_statsn.attr)
		param = ISCSI_PARAM_EXP_STATSN;
	अन्यथा अगर (attr == &dev_attr_conn_persistent_address.attr)
		param = ISCSI_PARAM_PERSISTENT_ADDRESS;
	अन्यथा अगर (attr == &dev_attr_conn_persistent_port.attr)
		param = ISCSI_PARAM_PERSISTENT_PORT;
	अन्यथा अगर (attr == &dev_attr_conn_ping_पंचांगo.attr)
		param = ISCSI_PARAM_PING_TMO;
	अन्यथा अगर (attr == &dev_attr_conn_recv_पंचांगo.attr)
		param = ISCSI_PARAM_RECV_TMO;
	अन्यथा अगर (attr == &dev_attr_conn_local_port.attr)
		param = ISCSI_PARAM_LOCAL_PORT;
	अन्यथा अगर (attr == &dev_attr_conn_statsn.attr)
		param = ISCSI_PARAM_STATSN;
	अन्यथा अगर (attr == &dev_attr_conn_keepalive_पंचांगo.attr)
		param = ISCSI_PARAM_KEEPALIVE_TMO;
	अन्यथा अगर (attr == &dev_attr_conn_max_segment_size.attr)
		param = ISCSI_PARAM_MAX_SEGMENT_SIZE;
	अन्यथा अगर (attr == &dev_attr_conn_tcp_बारtamp_stat.attr)
		param = ISCSI_PARAM_TCP_TIMESTAMP_STAT;
	अन्यथा अगर (attr == &dev_attr_conn_tcp_wsf_disable.attr)
		param = ISCSI_PARAM_TCP_WSF_DISABLE;
	अन्यथा अगर (attr == &dev_attr_conn_tcp_nagle_disable.attr)
		param = ISCSI_PARAM_TCP_NAGLE_DISABLE;
	अन्यथा अगर (attr == &dev_attr_conn_tcp_समयr_scale.attr)
		param = ISCSI_PARAM_TCP_TIMER_SCALE;
	अन्यथा अगर (attr == &dev_attr_conn_tcp_बारtamp_enable.attr)
		param = ISCSI_PARAM_TCP_TIMESTAMP_EN;
	अन्यथा अगर (attr == &dev_attr_conn_fragment_disable.attr)
		param = ISCSI_PARAM_IP_FRAGMENT_DISABLE;
	अन्यथा अगर (attr == &dev_attr_conn_ipv4_tos.attr)
		param = ISCSI_PARAM_IPV4_TOS;
	अन्यथा अगर (attr == &dev_attr_conn_ipv6_traffic_class.attr)
		param = ISCSI_PARAM_IPV6_TC;
	अन्यथा अगर (attr == &dev_attr_conn_ipv6_flow_label.attr)
		param = ISCSI_PARAM_IPV6_FLOW_LABEL;
	अन्यथा अगर (attr == &dev_attr_conn_is_fw_asचिन्हित_ipv6.attr)
		param = ISCSI_PARAM_IS_FW_ASSIGNED_IPV6;
	अन्यथा अगर (attr == &dev_attr_conn_tcp_xmit_wsf.attr)
		param = ISCSI_PARAM_TCP_XMIT_WSF;
	अन्यथा अगर (attr == &dev_attr_conn_tcp_recv_wsf.attr)
		param = ISCSI_PARAM_TCP_RECV_WSF;
	अन्यथा अगर (attr == &dev_attr_conn_local_ipaddr.attr)
		param = ISCSI_PARAM_LOCAL_IPADDR;
	अन्यथा अगर (attr == &dev_attr_conn_state.attr)
		वापस S_IRUGO;
	अन्यथा अणु
		WARN_ONCE(1, "Invalid conn attr");
		वापस 0;
	पूर्ण

	वापस t->attr_is_visible(ISCSI_PARAM, param);
पूर्ण

अटल काष्ठा attribute_group iscsi_conn_group = अणु
	.attrs = iscsi_conn_attrs,
	.is_visible = iscsi_conn_attr_is_visible,
पूर्ण;

/*
 * iSCSI session attrs
 */
#घोषणा iscsi_session_attr_show(param, perm)				\
अटल sमाप_प्रकार								\
show_session_param_##param(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा iscsi_cls_session *session = 				\
		iscsi_dev_to_session(dev->parent);			\
	काष्ठा iscsi_transport *t = session->transport;			\
									\
	अगर (perm && !capable(CAP_SYS_ADMIN))				\
		वापस -EACCES;						\
	वापस t->get_session_param(session, param, buf);		\
पूर्ण

#घोषणा iscsi_session_attr(field, param, perm)				\
	iscsi_session_attr_show(param, perm)				\
अटल ISCSI_CLASS_ATTR(sess, field, S_IRUGO, show_session_param_##param, \
			शून्य);
iscsi_session_attr(targetname, ISCSI_PARAM_TARGET_NAME, 0);
iscsi_session_attr(initial_r2t, ISCSI_PARAM_INITIAL_R2T_EN, 0);
iscsi_session_attr(max_outstanding_r2t, ISCSI_PARAM_MAX_R2T, 0);
iscsi_session_attr(immediate_data, ISCSI_PARAM_IMM_DATA_EN, 0);
iscsi_session_attr(first_burst_len, ISCSI_PARAM_FIRST_BURST, 0);
iscsi_session_attr(max_burst_len, ISCSI_PARAM_MAX_BURST, 0);
iscsi_session_attr(data_pdu_in_order, ISCSI_PARAM_PDU_INORDER_EN, 0);
iscsi_session_attr(data_seq_in_order, ISCSI_PARAM_DATASEQ_INORDER_EN, 0);
iscsi_session_attr(erl, ISCSI_PARAM_ERL, 0);
iscsi_session_attr(tpgt, ISCSI_PARAM_TPGT, 0);
iscsi_session_attr(username, ISCSI_PARAM_USERNAME, 1);
iscsi_session_attr(username_in, ISCSI_PARAM_USERNAME_IN, 1);
iscsi_session_attr(password, ISCSI_PARAM_PASSWORD, 1);
iscsi_session_attr(password_in, ISCSI_PARAM_PASSWORD_IN, 1);
iscsi_session_attr(chap_out_idx, ISCSI_PARAM_CHAP_OUT_IDX, 1);
iscsi_session_attr(chap_in_idx, ISCSI_PARAM_CHAP_IN_IDX, 1);
iscsi_session_attr(fast_पात, ISCSI_PARAM_FAST_ABORT, 0);
iscsi_session_attr(पात_पंचांगo, ISCSI_PARAM_ABORT_TMO, 0);
iscsi_session_attr(lu_reset_पंचांगo, ISCSI_PARAM_LU_RESET_TMO, 0);
iscsi_session_attr(tgt_reset_पंचांगo, ISCSI_PARAM_TGT_RESET_TMO, 0);
iscsi_session_attr(अगरacename, ISCSI_PARAM_IFACE_NAME, 0);
iscsi_session_attr(initiatorname, ISCSI_PARAM_INITIATOR_NAME, 0);
iscsi_session_attr(targetalias, ISCSI_PARAM_TARGET_ALIAS, 0);
iscsi_session_attr(boot_root, ISCSI_PARAM_BOOT_ROOT, 0);
iscsi_session_attr(boot_nic, ISCSI_PARAM_BOOT_NIC, 0);
iscsi_session_attr(boot_target, ISCSI_PARAM_BOOT_TARGET, 0);
iscsi_session_attr(स्वतः_snd_tgt_disable, ISCSI_PARAM_AUTO_SND_TGT_DISABLE, 0);
iscsi_session_attr(discovery_session, ISCSI_PARAM_DISCOVERY_SESS, 0);
iscsi_session_attr(portal_type, ISCSI_PARAM_PORTAL_TYPE, 0);
iscsi_session_attr(chap_auth, ISCSI_PARAM_CHAP_AUTH_EN, 0);
iscsi_session_attr(discovery_logout, ISCSI_PARAM_DISCOVERY_LOGOUT_EN, 0);
iscsi_session_attr(bidi_chap, ISCSI_PARAM_BIDI_CHAP_EN, 0);
iscsi_session_attr(discovery_auth_optional,
		   ISCSI_PARAM_DISCOVERY_AUTH_OPTIONAL, 0);
iscsi_session_attr(def_समय2रुको, ISCSI_PARAM_DEF_TIME2WAIT, 0);
iscsi_session_attr(def_समय2retain, ISCSI_PARAM_DEF_TIME2RETAIN, 0);
iscsi_session_attr(isid, ISCSI_PARAM_ISID, 0);
iscsi_session_attr(tsid, ISCSI_PARAM_TSID, 0);
iscsi_session_attr(def_taskmgmt_पंचांगo, ISCSI_PARAM_DEF_TASKMGMT_TMO, 0);
iscsi_session_attr(discovery_parent_idx, ISCSI_PARAM_DISCOVERY_PARENT_IDX, 0);
iscsi_session_attr(discovery_parent_type, ISCSI_PARAM_DISCOVERY_PARENT_TYPE, 0);

अटल sमाप_प्रकार
show_priv_session_state(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा iscsi_cls_session *session = iscsi_dev_to_session(dev->parent);
	वापस sysfs_emit(buf, "%s\n", iscsi_session_state_name(session->state));
पूर्ण
अटल ISCSI_CLASS_ATTR(priv_sess, state, S_IRUGO, show_priv_session_state,
			शून्य);
अटल sमाप_प्रकार
show_priv_session_creator(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा iscsi_cls_session *session = iscsi_dev_to_session(dev->parent);
	वापस sysfs_emit(buf, "%d\n", session->creator);
पूर्ण
अटल ISCSI_CLASS_ATTR(priv_sess, creator, S_IRUGO, show_priv_session_creator,
			शून्य);
अटल sमाप_प्रकार
show_priv_session_target_id(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा iscsi_cls_session *session = iscsi_dev_to_session(dev->parent);
	वापस sysfs_emit(buf, "%d\n", session->target_id);
पूर्ण
अटल ISCSI_CLASS_ATTR(priv_sess, target_id, S_IRUGO,
			show_priv_session_target_id, शून्य);

#घोषणा iscsi_priv_session_attr_show(field, क्रमmat)			\
अटल sमाप_प्रकार								\
show_priv_session_##field(काष्ठा device *dev, 				\
			  काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा iscsi_cls_session *session = 				\
			iscsi_dev_to_session(dev->parent);		\
	अगर (session->field == -1)					\
		वापस sysfs_emit(buf, "off\n");			\
	वापस sysfs_emit(buf, क्रमmat"\n", session->field);		\
पूर्ण

#घोषणा iscsi_priv_session_attr_store(field)				\
अटल sमाप_प्रकार								\
store_priv_session_##field(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr,		\
			   स्थिर अक्षर *buf, माप_प्रकार count)		\
अणु									\
	पूर्णांक val;							\
	अक्षर *cp;							\
	काष्ठा iscsi_cls_session *session =				\
		iscsi_dev_to_session(dev->parent);			\
	अगर ((session->state == ISCSI_SESSION_FREE) ||			\
	    (session->state == ISCSI_SESSION_FAILED))			\
		वापस -EBUSY;						\
	अगर (म_भेदन(buf, "off", 3) == 0) अणु				\
		session->field = -1;					\
		session->field##_sysfs_override = true;			\
	पूर्ण अन्यथा अणु							\
		val = simple_म_से_अदीर्घ(buf, &cp, 0);			\
		अगर (*cp != '\0' && *cp != '\n')				\
			वापस -EINVAL;					\
		session->field = val;					\
		session->field##_sysfs_override = true;			\
	पूर्ण								\
	वापस count;							\
पूर्ण

#घोषणा iscsi_priv_session_rw_attr(field, क्रमmat)			\
	iscsi_priv_session_attr_show(field, क्रमmat)			\
	iscsi_priv_session_attr_store(field)				\
अटल ISCSI_CLASS_ATTR(priv_sess, field, S_IRUGO | S_IWUSR,		\
			show_priv_session_##field,			\
			store_priv_session_##field)

iscsi_priv_session_rw_attr(recovery_पंचांगo, "%d");

अटल काष्ठा attribute *iscsi_session_attrs[] = अणु
	&dev_attr_sess_initial_r2t.attr,
	&dev_attr_sess_max_outstanding_r2t.attr,
	&dev_attr_sess_immediate_data.attr,
	&dev_attr_sess_first_burst_len.attr,
	&dev_attr_sess_max_burst_len.attr,
	&dev_attr_sess_data_pdu_in_order.attr,
	&dev_attr_sess_data_seq_in_order.attr,
	&dev_attr_sess_erl.attr,
	&dev_attr_sess_targetname.attr,
	&dev_attr_sess_tpgt.attr,
	&dev_attr_sess_password.attr,
	&dev_attr_sess_password_in.attr,
	&dev_attr_sess_username.attr,
	&dev_attr_sess_username_in.attr,
	&dev_attr_sess_fast_पात.attr,
	&dev_attr_sess_पात_पंचांगo.attr,
	&dev_attr_sess_lu_reset_पंचांगo.attr,
	&dev_attr_sess_tgt_reset_पंचांगo.attr,
	&dev_attr_sess_अगरacename.attr,
	&dev_attr_sess_initiatorname.attr,
	&dev_attr_sess_targetalias.attr,
	&dev_attr_sess_boot_root.attr,
	&dev_attr_sess_boot_nic.attr,
	&dev_attr_sess_boot_target.attr,
	&dev_attr_priv_sess_recovery_पंचांगo.attr,
	&dev_attr_priv_sess_state.attr,
	&dev_attr_priv_sess_creator.attr,
	&dev_attr_sess_chap_out_idx.attr,
	&dev_attr_sess_chap_in_idx.attr,
	&dev_attr_priv_sess_target_id.attr,
	&dev_attr_sess_स्वतः_snd_tgt_disable.attr,
	&dev_attr_sess_discovery_session.attr,
	&dev_attr_sess_portal_type.attr,
	&dev_attr_sess_chap_auth.attr,
	&dev_attr_sess_discovery_logout.attr,
	&dev_attr_sess_bidi_chap.attr,
	&dev_attr_sess_discovery_auth_optional.attr,
	&dev_attr_sess_def_समय2रुको.attr,
	&dev_attr_sess_def_समय2retain.attr,
	&dev_attr_sess_isid.attr,
	&dev_attr_sess_tsid.attr,
	&dev_attr_sess_def_taskmgmt_पंचांगo.attr,
	&dev_attr_sess_discovery_parent_idx.attr,
	&dev_attr_sess_discovery_parent_type.attr,
	शून्य,
पूर्ण;

अटल umode_t iscsi_session_attr_is_visible(काष्ठा kobject *kobj,
					    काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *cdev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा iscsi_cls_session *session = transport_class_to_session(cdev);
	काष्ठा iscsi_transport *t = session->transport;
	पूर्णांक param;

	अगर (attr == &dev_attr_sess_initial_r2t.attr)
		param = ISCSI_PARAM_INITIAL_R2T_EN;
	अन्यथा अगर (attr == &dev_attr_sess_max_outstanding_r2t.attr)
		param = ISCSI_PARAM_MAX_R2T;
	अन्यथा अगर (attr == &dev_attr_sess_immediate_data.attr)
		param = ISCSI_PARAM_IMM_DATA_EN;
	अन्यथा अगर (attr == &dev_attr_sess_first_burst_len.attr)
		param = ISCSI_PARAM_FIRST_BURST;
	अन्यथा अगर (attr == &dev_attr_sess_max_burst_len.attr)
		param = ISCSI_PARAM_MAX_BURST;
	अन्यथा अगर (attr == &dev_attr_sess_data_pdu_in_order.attr)
		param = ISCSI_PARAM_PDU_INORDER_EN;
	अन्यथा अगर (attr == &dev_attr_sess_data_seq_in_order.attr)
		param = ISCSI_PARAM_DATASEQ_INORDER_EN;
	अन्यथा अगर (attr == &dev_attr_sess_erl.attr)
		param = ISCSI_PARAM_ERL;
	अन्यथा अगर (attr == &dev_attr_sess_targetname.attr)
		param = ISCSI_PARAM_TARGET_NAME;
	अन्यथा अगर (attr == &dev_attr_sess_tpgt.attr)
		param = ISCSI_PARAM_TPGT;
	अन्यथा अगर (attr == &dev_attr_sess_chap_in_idx.attr)
		param = ISCSI_PARAM_CHAP_IN_IDX;
	अन्यथा अगर (attr == &dev_attr_sess_chap_out_idx.attr)
		param = ISCSI_PARAM_CHAP_OUT_IDX;
	अन्यथा अगर (attr == &dev_attr_sess_password.attr)
		param = ISCSI_PARAM_USERNAME;
	अन्यथा अगर (attr == &dev_attr_sess_password_in.attr)
		param = ISCSI_PARAM_USERNAME_IN;
	अन्यथा अगर (attr == &dev_attr_sess_username.attr)
		param = ISCSI_PARAM_PASSWORD;
	अन्यथा अगर (attr == &dev_attr_sess_username_in.attr)
		param = ISCSI_PARAM_PASSWORD_IN;
	अन्यथा अगर (attr == &dev_attr_sess_fast_पात.attr)
		param = ISCSI_PARAM_FAST_ABORT;
	अन्यथा अगर (attr == &dev_attr_sess_पात_पंचांगo.attr)
		param = ISCSI_PARAM_ABORT_TMO;
	अन्यथा अगर (attr == &dev_attr_sess_lu_reset_पंचांगo.attr)
		param = ISCSI_PARAM_LU_RESET_TMO;
	अन्यथा अगर (attr == &dev_attr_sess_tgt_reset_पंचांगo.attr)
		param = ISCSI_PARAM_TGT_RESET_TMO;
	अन्यथा अगर (attr == &dev_attr_sess_अगरacename.attr)
		param = ISCSI_PARAM_IFACE_NAME;
	अन्यथा अगर (attr == &dev_attr_sess_initiatorname.attr)
		param = ISCSI_PARAM_INITIATOR_NAME;
	अन्यथा अगर (attr == &dev_attr_sess_targetalias.attr)
		param = ISCSI_PARAM_TARGET_ALIAS;
	अन्यथा अगर (attr == &dev_attr_sess_boot_root.attr)
		param = ISCSI_PARAM_BOOT_ROOT;
	अन्यथा अगर (attr == &dev_attr_sess_boot_nic.attr)
		param = ISCSI_PARAM_BOOT_NIC;
	अन्यथा अगर (attr == &dev_attr_sess_boot_target.attr)
		param = ISCSI_PARAM_BOOT_TARGET;
	अन्यथा अगर (attr == &dev_attr_sess_स्वतः_snd_tgt_disable.attr)
		param = ISCSI_PARAM_AUTO_SND_TGT_DISABLE;
	अन्यथा अगर (attr == &dev_attr_sess_discovery_session.attr)
		param = ISCSI_PARAM_DISCOVERY_SESS;
	अन्यथा अगर (attr == &dev_attr_sess_portal_type.attr)
		param = ISCSI_PARAM_PORTAL_TYPE;
	अन्यथा अगर (attr == &dev_attr_sess_chap_auth.attr)
		param = ISCSI_PARAM_CHAP_AUTH_EN;
	अन्यथा अगर (attr == &dev_attr_sess_discovery_logout.attr)
		param = ISCSI_PARAM_DISCOVERY_LOGOUT_EN;
	अन्यथा अगर (attr == &dev_attr_sess_bidi_chap.attr)
		param = ISCSI_PARAM_BIDI_CHAP_EN;
	अन्यथा अगर (attr == &dev_attr_sess_discovery_auth_optional.attr)
		param = ISCSI_PARAM_DISCOVERY_AUTH_OPTIONAL;
	अन्यथा अगर (attr == &dev_attr_sess_def_समय2रुको.attr)
		param = ISCSI_PARAM_DEF_TIME2WAIT;
	अन्यथा अगर (attr == &dev_attr_sess_def_समय2retain.attr)
		param = ISCSI_PARAM_DEF_TIME2RETAIN;
	अन्यथा अगर (attr == &dev_attr_sess_isid.attr)
		param = ISCSI_PARAM_ISID;
	अन्यथा अगर (attr == &dev_attr_sess_tsid.attr)
		param = ISCSI_PARAM_TSID;
	अन्यथा अगर (attr == &dev_attr_sess_def_taskmgmt_पंचांगo.attr)
		param = ISCSI_PARAM_DEF_TASKMGMT_TMO;
	अन्यथा अगर (attr == &dev_attr_sess_discovery_parent_idx.attr)
		param = ISCSI_PARAM_DISCOVERY_PARENT_IDX;
	अन्यथा अगर (attr == &dev_attr_sess_discovery_parent_type.attr)
		param = ISCSI_PARAM_DISCOVERY_PARENT_TYPE;
	अन्यथा अगर (attr == &dev_attr_priv_sess_recovery_पंचांगo.attr)
		वापस S_IRUGO | S_IWUSR;
	अन्यथा अगर (attr == &dev_attr_priv_sess_state.attr)
		वापस S_IRUGO;
	अन्यथा अगर (attr == &dev_attr_priv_sess_creator.attr)
		वापस S_IRUGO;
	अन्यथा अगर (attr == &dev_attr_priv_sess_target_id.attr)
		वापस S_IRUGO;
	अन्यथा अणु
		WARN_ONCE(1, "Invalid session attr");
		वापस 0;
	पूर्ण

	वापस t->attr_is_visible(ISCSI_PARAM, param);
पूर्ण

अटल काष्ठा attribute_group iscsi_session_group = अणु
	.attrs = iscsi_session_attrs,
	.is_visible = iscsi_session_attr_is_visible,
पूर्ण;

/*
 * iSCSI host attrs
 */
#घोषणा iscsi_host_attr_show(param)					\
अटल sमाप_प्रकार								\
show_host_param_##param(काष्ठा device *dev, 				\
			काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);	\
	काष्ठा iscsi_पूर्णांकernal *priv = to_iscsi_पूर्णांकernal(shost->transportt); \
	वापस priv->iscsi_transport->get_host_param(shost, param, buf); \
पूर्ण

#घोषणा iscsi_host_attr(field, param)					\
	iscsi_host_attr_show(param)					\
अटल ISCSI_CLASS_ATTR(host, field, S_IRUGO, show_host_param_##param,	\
			शून्य);

iscsi_host_attr(netdev, ISCSI_HOST_PARAM_NETDEV_NAME);
iscsi_host_attr(hwaddress, ISCSI_HOST_PARAM_HWADDRESS);
iscsi_host_attr(ipaddress, ISCSI_HOST_PARAM_IPADDRESS);
iscsi_host_attr(initiatorname, ISCSI_HOST_PARAM_INITIATOR_NAME);
iscsi_host_attr(port_state, ISCSI_HOST_PARAM_PORT_STATE);
iscsi_host_attr(port_speed, ISCSI_HOST_PARAM_PORT_SPEED);

अटल काष्ठा attribute *iscsi_host_attrs[] = अणु
	&dev_attr_host_netdev.attr,
	&dev_attr_host_hwaddress.attr,
	&dev_attr_host_ipaddress.attr,
	&dev_attr_host_initiatorname.attr,
	&dev_attr_host_port_state.attr,
	&dev_attr_host_port_speed.attr,
	शून्य,
पूर्ण;

अटल umode_t iscsi_host_attr_is_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *cdev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा Scsi_Host *shost = transport_class_to_shost(cdev);
	काष्ठा iscsi_पूर्णांकernal *priv = to_iscsi_पूर्णांकernal(shost->transportt);
	पूर्णांक param;

	अगर (attr == &dev_attr_host_netdev.attr)
		param = ISCSI_HOST_PARAM_NETDEV_NAME;
	अन्यथा अगर (attr == &dev_attr_host_hwaddress.attr)
		param = ISCSI_HOST_PARAM_HWADDRESS;
	अन्यथा अगर (attr == &dev_attr_host_ipaddress.attr)
		param = ISCSI_HOST_PARAM_IPADDRESS;
	अन्यथा अगर (attr == &dev_attr_host_initiatorname.attr)
		param = ISCSI_HOST_PARAM_INITIATOR_NAME;
	अन्यथा अगर (attr == &dev_attr_host_port_state.attr)
		param = ISCSI_HOST_PARAM_PORT_STATE;
	अन्यथा अगर (attr == &dev_attr_host_port_speed.attr)
		param = ISCSI_HOST_PARAM_PORT_SPEED;
	अन्यथा अणु
		WARN_ONCE(1, "Invalid host attr");
		वापस 0;
	पूर्ण

	वापस priv->iscsi_transport->attr_is_visible(ISCSI_HOST_PARAM, param);
पूर्ण

अटल काष्ठा attribute_group iscsi_host_group = अणु
	.attrs = iscsi_host_attrs,
	.is_visible = iscsi_host_attr_is_visible,
पूर्ण;

/* convert iscsi_port_speed values to ascii string name */
अटल स्थिर काष्ठा अणु
	क्रमागत iscsi_port_speed	value;
	अक्षर			*name;
पूर्ण iscsi_port_speed_names[] = अणु
	अणुISCSI_PORT_SPEED_UNKNOWN,	"Unknown" पूर्ण,
	अणुISCSI_PORT_SPEED_10MBPS,	"10 Mbps" पूर्ण,
	अणुISCSI_PORT_SPEED_100MBPS,	"100 Mbps" पूर्ण,
	अणुISCSI_PORT_SPEED_1GBPS,	"1 Gbps" पूर्ण,
	अणुISCSI_PORT_SPEED_10GBPS,	"10 Gbps" पूर्ण,
	अणुISCSI_PORT_SPEED_25GBPS,       "25 Gbps" पूर्ण,
	अणुISCSI_PORT_SPEED_40GBPS,       "40 Gbps" पूर्ण,
पूर्ण;

अक्षर *iscsi_get_port_speed_name(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक i;
	अक्षर *speed = "Unknown!";
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;
	uपूर्णांक32_t port_speed = ihost->port_speed;

	क्रम (i = 0; i < ARRAY_SIZE(iscsi_port_speed_names); i++) अणु
		अगर (iscsi_port_speed_names[i].value & port_speed) अणु
			speed = iscsi_port_speed_names[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस speed;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_get_port_speed_name);

/* convert iscsi_port_state values to ascii string name */
अटल स्थिर काष्ठा अणु
	क्रमागत iscsi_port_state	value;
	अक्षर			*name;
पूर्ण iscsi_port_state_names[] = अणु
	अणुISCSI_PORT_STATE_DOWN,		"LINK DOWN" पूर्ण,
	अणुISCSI_PORT_STATE_UP,		"LINK UP" पूर्ण,
पूर्ण;

अक्षर *iscsi_get_port_state_name(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक i;
	अक्षर *state = "Unknown!";
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;
	uपूर्णांक32_t port_state = ihost->port_state;

	क्रम (i = 0; i < ARRAY_SIZE(iscsi_port_state_names); i++) अणु
		अगर (iscsi_port_state_names[i].value & port_state) अणु
			state = iscsi_port_state_names[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_get_port_state_name);

अटल पूर्णांक iscsi_session_match(काष्ठा attribute_container *cont,
			   काष्ठा device *dev)
अणु
	काष्ठा iscsi_cls_session *session;
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_पूर्णांकernal *priv;

	अगर (!iscsi_is_session_dev(dev))
		वापस 0;

	session = iscsi_dev_to_session(dev);
	shost = iscsi_session_to_shost(session);
	अगर (!shost->transportt)
		वापस 0;

	priv = to_iscsi_पूर्णांकernal(shost->transportt);
	अगर (priv->session_cont.ac.class != &iscsi_session_class.class)
		वापस 0;

	वापस &priv->session_cont.ac == cont;
पूर्ण

अटल पूर्णांक iscsi_conn_match(काष्ठा attribute_container *cont,
			   काष्ठा device *dev)
अणु
	काष्ठा iscsi_cls_session *session;
	काष्ठा iscsi_cls_conn *conn;
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_पूर्णांकernal *priv;

	अगर (!iscsi_is_conn_dev(dev))
		वापस 0;

	conn = iscsi_dev_to_conn(dev);
	session = iscsi_dev_to_session(conn->dev.parent);
	shost = iscsi_session_to_shost(session);

	अगर (!shost->transportt)
		वापस 0;

	priv = to_iscsi_पूर्णांकernal(shost->transportt);
	अगर (priv->conn_cont.ac.class != &iscsi_connection_class.class)
		वापस 0;

	वापस &priv->conn_cont.ac == cont;
पूर्ण

अटल पूर्णांक iscsi_host_match(काष्ठा attribute_container *cont,
			    काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_पूर्णांकernal *priv;

	अगर (!scsi_is_host_device(dev))
		वापस 0;

	shost = dev_to_shost(dev);
	अगर (!shost->transportt  ||
	    shost->transportt->host_attrs.ac.class != &iscsi_host_class.class)
		वापस 0;

        priv = to_iscsi_पूर्णांकernal(shost->transportt);
        वापस &priv->t.host_attrs.ac == cont;
पूर्ण

काष्ठा scsi_transport_ढाँचा *
iscsi_रेजिस्टर_transport(काष्ठा iscsi_transport *tt)
अणु
	काष्ठा iscsi_पूर्णांकernal *priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	BUG_ON(!tt);

	priv = iscsi_अगर_transport_lookup(tt);
	अगर (priv)
		वापस शून्य;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;
	INIT_LIST_HEAD(&priv->list);
	priv->iscsi_transport = tt;
	priv->t.user_scan = iscsi_user_scan;
	priv->t.create_work_queue = 1;

	priv->dev.class = &iscsi_transport_class;
	dev_set_name(&priv->dev, "%s", tt->name);
	err = device_रेजिस्टर(&priv->dev);
	अगर (err)
		जाओ मुक्त_priv;

	err = sysfs_create_group(&priv->dev.kobj, &iscsi_transport_group);
	अगर (err)
		जाओ unरेजिस्टर_dev;

	/* host parameters */
	priv->t.host_attrs.ac.class = &iscsi_host_class.class;
	priv->t.host_attrs.ac.match = iscsi_host_match;
	priv->t.host_attrs.ac.grp = &iscsi_host_group;
	priv->t.host_size = माप(काष्ठा iscsi_cls_host);
	transport_container_रेजिस्टर(&priv->t.host_attrs);

	/* connection parameters */
	priv->conn_cont.ac.class = &iscsi_connection_class.class;
	priv->conn_cont.ac.match = iscsi_conn_match;
	priv->conn_cont.ac.grp = &iscsi_conn_group;
	transport_container_रेजिस्टर(&priv->conn_cont);

	/* session parameters */
	priv->session_cont.ac.class = &iscsi_session_class.class;
	priv->session_cont.ac.match = iscsi_session_match;
	priv->session_cont.ac.grp = &iscsi_session_group;
	transport_container_रेजिस्टर(&priv->session_cont);

	spin_lock_irqsave(&iscsi_transport_lock, flags);
	list_add(&priv->list, &iscsi_transports);
	spin_unlock_irqrestore(&iscsi_transport_lock, flags);

	prपूर्णांकk(KERN_NOTICE "iscsi: registered transport (%s)\n", tt->name);
	वापस &priv->t;

unरेजिस्टर_dev:
	device_unरेजिस्टर(&priv->dev);
	वापस शून्य;
मुक्त_priv:
	kमुक्त(priv);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_रेजिस्टर_transport);

पूर्णांक iscsi_unरेजिस्टर_transport(काष्ठा iscsi_transport *tt)
अणु
	काष्ठा iscsi_पूर्णांकernal *priv;
	अचिन्हित दीर्घ flags;

	BUG_ON(!tt);

	mutex_lock(&rx_queue_mutex);

	priv = iscsi_अगर_transport_lookup(tt);
	BUG_ON (!priv);

	spin_lock_irqsave(&iscsi_transport_lock, flags);
	list_del(&priv->list);
	spin_unlock_irqrestore(&iscsi_transport_lock, flags);

	transport_container_unरेजिस्टर(&priv->conn_cont);
	transport_container_unरेजिस्टर(&priv->session_cont);
	transport_container_unरेजिस्टर(&priv->t.host_attrs);

	sysfs_हटाओ_group(&priv->dev.kobj, &iscsi_transport_group);
	device_unरेजिस्टर(&priv->dev);
	mutex_unlock(&rx_queue_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_unरेजिस्टर_transport);

व्योम iscsi_dbg_trace(व्योम (*trace)(काष्ठा device *dev, काष्ठा va_क्रमmat *),
		     काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	trace(dev, &vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(iscsi_dbg_trace);

अटल __init पूर्णांक iscsi_transport_init(व्योम)
अणु
	पूर्णांक err;
	काष्ठा netlink_kernel_cfg cfg = अणु
		.groups	= 1,
		.input	= iscsi_अगर_rx,
	पूर्ण;
	prपूर्णांकk(KERN_INFO "Loading iSCSI transport class v%s.\n",
		ISCSI_TRANSPORT_VERSION);

	atomic_set(&iscsi_session_nr, 0);

	err = class_रेजिस्टर(&iscsi_transport_class);
	अगर (err)
		वापस err;

	err = class_रेजिस्टर(&iscsi_endpoपूर्णांक_class);
	अगर (err)
		जाओ unरेजिस्टर_transport_class;

	err = class_रेजिस्टर(&iscsi_अगरace_class);
	अगर (err)
		जाओ unरेजिस्टर_endpoपूर्णांक_class;

	err = transport_class_रेजिस्टर(&iscsi_host_class);
	अगर (err)
		जाओ unरेजिस्टर_अगरace_class;

	err = transport_class_रेजिस्टर(&iscsi_connection_class);
	अगर (err)
		जाओ unरेजिस्टर_host_class;

	err = transport_class_रेजिस्टर(&iscsi_session_class);
	अगर (err)
		जाओ unरेजिस्टर_conn_class;

	err = bus_रेजिस्टर(&iscsi_flashnode_bus);
	अगर (err)
		जाओ unरेजिस्टर_session_class;

	nls = netlink_kernel_create(&init_net, NETLINK_ISCSI, &cfg);
	अगर (!nls) अणु
		err = -ENOBUFS;
		जाओ unरेजिस्टर_flashnode_bus;
	पूर्ण

	iscsi_eh_समयr_workq = alloc_workqueue("%s",
			WQ_SYSFS | __WQ_LEGACY | WQ_MEM_RECLAIM | WQ_UNBOUND,
			1, "iscsi_eh");
	अगर (!iscsi_eh_समयr_workq) अणु
		err = -ENOMEM;
		जाओ release_nls;
	पूर्ण

	iscsi_destroy_workq = alloc_workqueue("%s",
			WQ_SYSFS | __WQ_LEGACY | WQ_MEM_RECLAIM | WQ_UNBOUND,
			1, "iscsi_destroy");
	अगर (!iscsi_destroy_workq) अणु
		err = -ENOMEM;
		जाओ destroy_wq;
	पूर्ण

	वापस 0;

destroy_wq:
	destroy_workqueue(iscsi_eh_समयr_workq);
release_nls:
	netlink_kernel_release(nls);
unरेजिस्टर_flashnode_bus:
	bus_unरेजिस्टर(&iscsi_flashnode_bus);
unरेजिस्टर_session_class:
	transport_class_unरेजिस्टर(&iscsi_session_class);
unरेजिस्टर_conn_class:
	transport_class_unरेजिस्टर(&iscsi_connection_class);
unरेजिस्टर_host_class:
	transport_class_unरेजिस्टर(&iscsi_host_class);
unरेजिस्टर_अगरace_class:
	class_unरेजिस्टर(&iscsi_अगरace_class);
unरेजिस्टर_endpoपूर्णांक_class:
	class_unरेजिस्टर(&iscsi_endpoपूर्णांक_class);
unरेजिस्टर_transport_class:
	class_unरेजिस्टर(&iscsi_transport_class);
	वापस err;
पूर्ण

अटल व्योम __निकास iscsi_transport_निकास(व्योम)
अणु
	destroy_workqueue(iscsi_destroy_workq);
	destroy_workqueue(iscsi_eh_समयr_workq);
	netlink_kernel_release(nls);
	bus_unरेजिस्टर(&iscsi_flashnode_bus);
	transport_class_unरेजिस्टर(&iscsi_connection_class);
	transport_class_unरेजिस्टर(&iscsi_session_class);
	transport_class_unरेजिस्टर(&iscsi_host_class);
	class_unरेजिस्टर(&iscsi_endpoपूर्णांक_class);
	class_unरेजिस्टर(&iscsi_अगरace_class);
	class_unरेजिस्टर(&iscsi_transport_class);
पूर्ण

module_init(iscsi_transport_init);
module_निकास(iscsi_transport_निकास);

MODULE_AUTHOR("Mike Christie <michaelc@cs.wisc.edu>, "
	      "Dmitry Yusupov <dmitry_yus@yahoo.com>, "
	      "Alex Aizman <itn780@yahoo.com>");
MODULE_DESCRIPTION("iSCSI Transport Interface");
MODULE_LICENSE("GPL");
MODULE_VERSION(ISCSI_TRANSPORT_VERSION);
MODULE_ALIAS_NET_PF_PROTO(PF_NETLINK, NETLINK_ISCSI);
