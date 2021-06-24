<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS         An implementation of the IP भव server support क्रम the
 *              LINUX operating प्रणाली.  IPVS is now implemented as a module
 *              over the NetFilter framework. IPVS can be used to build a
 *              high-perक्रमmance and highly available server based on a
 *              cluster of servers.
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Peter Kese <peter.kese@ijs.si>
 *              Julian Anastasov <ja@ssi.bg>
 *
 * Changes:
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/swap.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/mutex.h>

#समावेश <net/net_namespace.h>
#समावेश <linux/nsproxy.h>
#समावेश <net/ip.h>
#अगर_घोषित CONFIG_IP_VS_IPV6
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>
#पूर्ण_अगर
#समावेश <net/route.h>
#समावेश <net/sock.h>
#समावेश <net/genetlink.h>

#समावेश <linux/uaccess.h>

#समावेश <net/ip_vs.h>

/* semaphore क्रम IPVS sockopts. And, [gs]etsockopt may sleep. */
अटल DEFINE_MUTEX(__ip_vs_mutex);

/* sysctl variables */

#अगर_घोषित CONFIG_IP_VS_DEBUG
अटल पूर्णांक sysctl_ip_vs_debug_level = 0;

पूर्णांक ip_vs_get_debug_level(व्योम)
अणु
	वापस sysctl_ip_vs_debug_level;
पूर्ण
#पूर्ण_अगर


/*  Protos */
अटल व्योम __ip_vs_del_service(काष्ठा ip_vs_service *svc, bool cleanup);


#अगर_घोषित CONFIG_IP_VS_IPV6
/* Taken from rt6_fill_node() in net/ipv6/route.c, is there a better way? */
अटल bool __ip_vs_addr_is_local_v6(काष्ठा net *net,
				     स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा flowi6 fl6 = अणु
		.daddr = *addr,
	पूर्ण;
	काष्ठा dst_entry *dst = ip6_route_output(net, शून्य, &fl6);
	bool is_local;

	is_local = !dst->error && dst->dev && (dst->dev->flags & IFF_LOOPBACK);

	dst_release(dst);
	वापस is_local;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSCTL
/*
 *	update_defense_level is called from keventd and from sysctl,
 *	so it needs to protect itself from softirqs
 */
अटल व्योम update_defense_level(काष्ठा netns_ipvs *ipvs)
अणु
	काष्ठा sysinfo i;
	पूर्णांक availmem;
	पूर्णांक nomem;
	पूर्णांक to_change = -1;

	/* we only count मुक्त and buffered memory (in pages) */
	si_meminfo(&i);
	availmem = i.मुक्तram + i.bufferram;
	/* however in linux 2.5 the i.bufferram is total page cache size,
	   we need adjust it */
	/* si_swapinfo(&i); */
	/* availmem = availmem - (i.totalswap - i.मुक्तswap); */

	nomem = (availmem < ipvs->sysctl_amemthresh);

	local_bh_disable();

	/* drop_entry */
	spin_lock(&ipvs->drखोलोtry_lock);
	चयन (ipvs->sysctl_drop_entry) अणु
	हाल 0:
		atomic_set(&ipvs->drखोलोtry, 0);
		अवरोध;
	हाल 1:
		अगर (nomem) अणु
			atomic_set(&ipvs->drखोलोtry, 1);
			ipvs->sysctl_drop_entry = 2;
		पूर्ण अन्यथा अणु
			atomic_set(&ipvs->drखोलोtry, 0);
		पूर्ण
		अवरोध;
	हाल 2:
		अगर (nomem) अणु
			atomic_set(&ipvs->drखोलोtry, 1);
		पूर्ण अन्यथा अणु
			atomic_set(&ipvs->drखोलोtry, 0);
			ipvs->sysctl_drop_entry = 1;
		पूर्ण
		अवरोध;
	हाल 3:
		atomic_set(&ipvs->drखोलोtry, 1);
		अवरोध;
	पूर्ण
	spin_unlock(&ipvs->drखोलोtry_lock);

	/* drop_packet */
	spin_lock(&ipvs->droppacket_lock);
	चयन (ipvs->sysctl_drop_packet) अणु
	हाल 0:
		ipvs->drop_rate = 0;
		अवरोध;
	हाल 1:
		अगर (nomem) अणु
			ipvs->drop_rate = ipvs->drop_counter
				= ipvs->sysctl_amemthresh /
				(ipvs->sysctl_amemthresh-availmem);
			ipvs->sysctl_drop_packet = 2;
		पूर्ण अन्यथा अणु
			ipvs->drop_rate = 0;
		पूर्ण
		अवरोध;
	हाल 2:
		अगर (nomem) अणु
			ipvs->drop_rate = ipvs->drop_counter
				= ipvs->sysctl_amemthresh /
				(ipvs->sysctl_amemthresh-availmem);
		पूर्ण अन्यथा अणु
			ipvs->drop_rate = 0;
			ipvs->sysctl_drop_packet = 1;
		पूर्ण
		अवरोध;
	हाल 3:
		ipvs->drop_rate = ipvs->sysctl_am_droprate;
		अवरोध;
	पूर्ण
	spin_unlock(&ipvs->droppacket_lock);

	/* secure_tcp */
	spin_lock(&ipvs->securetcp_lock);
	चयन (ipvs->sysctl_secure_tcp) अणु
	हाल 0:
		अगर (ipvs->old_secure_tcp >= 2)
			to_change = 0;
		अवरोध;
	हाल 1:
		अगर (nomem) अणु
			अगर (ipvs->old_secure_tcp < 2)
				to_change = 1;
			ipvs->sysctl_secure_tcp = 2;
		पूर्ण अन्यथा अणु
			अगर (ipvs->old_secure_tcp >= 2)
				to_change = 0;
		पूर्ण
		अवरोध;
	हाल 2:
		अगर (nomem) अणु
			अगर (ipvs->old_secure_tcp < 2)
				to_change = 1;
		पूर्ण अन्यथा अणु
			अगर (ipvs->old_secure_tcp >= 2)
				to_change = 0;
			ipvs->sysctl_secure_tcp = 1;
		पूर्ण
		अवरोध;
	हाल 3:
		अगर (ipvs->old_secure_tcp < 2)
			to_change = 1;
		अवरोध;
	पूर्ण
	ipvs->old_secure_tcp = ipvs->sysctl_secure_tcp;
	अगर (to_change >= 0)
		ip_vs_protocol_समयout_change(ipvs,
					      ipvs->sysctl_secure_tcp > 1);
	spin_unlock(&ipvs->securetcp_lock);

	local_bh_enable();
पूर्ण

/* Handler क्रम delayed work क्रम expiring no
 * destination connections
 */
अटल व्योम expire_nodest_conn_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netns_ipvs *ipvs;

	ipvs = container_of(work, काष्ठा netns_ipvs,
			    expire_nodest_conn_work.work);
	ip_vs_expire_nodest_conn_flush(ipvs);
पूर्ण

/*
 *	Timer क्रम checking the defense
 */
#घोषणा DEFENSE_TIMER_PERIOD	1*HZ

अटल व्योम defense_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netns_ipvs *ipvs =
		container_of(work, काष्ठा netns_ipvs, defense_work.work);

	update_defense_level(ipvs);
	अगर (atomic_पढ़ो(&ipvs->drखोलोtry))
		ip_vs_अक्रमom_drखोलोtry(ipvs);
	queue_delayed_work(प्रणाली_दीर्घ_wq, &ipvs->defense_work,
			   DEFENSE_TIMER_PERIOD);
पूर्ण
#पूर्ण_अगर

पूर्णांक
ip_vs_use_count_inc(व्योम)
अणु
	वापस try_module_get(THIS_MODULE);
पूर्ण

व्योम
ip_vs_use_count_dec(व्योम)
अणु
	module_put(THIS_MODULE);
पूर्ण


/*
 *	Hash table: क्रम भव service lookups
 */
#घोषणा IP_VS_SVC_TAB_BITS 8
#घोषणा IP_VS_SVC_TAB_SIZE (1 << IP_VS_SVC_TAB_BITS)
#घोषणा IP_VS_SVC_TAB_MASK (IP_VS_SVC_TAB_SIZE - 1)

/* the service table hashed by <protocol, addr, port> */
अटल काष्ठा hlist_head ip_vs_svc_table[IP_VS_SVC_TAB_SIZE];
/* the service table hashed by fwmark */
अटल काष्ठा hlist_head ip_vs_svc_fwm_table[IP_VS_SVC_TAB_SIZE];


/*
 *	Returns hash value क्रम भव service
 */
अटल अंतरभूत अचिन्हित पूर्णांक
ip_vs_svc_hashkey(काष्ठा netns_ipvs *ipvs, पूर्णांक af, अचिन्हित पूर्णांक proto,
		  स्थिर जोड़ nf_inet_addr *addr, __be16 port)
अणु
	अचिन्हित पूर्णांक porth = ntohs(port);
	__be32 addr_fold = addr->ip;
	__u32 ahash;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		addr_fold = addr->ip6[0]^addr->ip6[1]^
			    addr->ip6[2]^addr->ip6[3];
#पूर्ण_अगर
	ahash = ntohl(addr_fold);
	ahash ^= ((माप_प्रकार) ipvs >> 8);

	वापस (proto ^ ahash ^ (porth >> IP_VS_SVC_TAB_BITS) ^ porth) &
	       IP_VS_SVC_TAB_MASK;
पूर्ण

/*
 *	Returns hash value of fwmark क्रम भव service lookup
 */
अटल अंतरभूत अचिन्हित पूर्णांक ip_vs_svc_fwm_hashkey(काष्ठा netns_ipvs *ipvs, __u32 fwmark)
अणु
	वापस (((माप_प्रकार)ipvs>>8) ^ fwmark) & IP_VS_SVC_TAB_MASK;
पूर्ण

/*
 *	Hashes a service in the ip_vs_svc_table by <netns,proto,addr,port>
 *	or in the ip_vs_svc_fwm_table by fwmark.
 *	Should be called with locked tables.
 */
अटल पूर्णांक ip_vs_svc_hash(काष्ठा ip_vs_service *svc)
अणु
	अचिन्हित पूर्णांक hash;

	अगर (svc->flags & IP_VS_SVC_F_HASHED) अणु
		pr_err("%s(): request for already hashed, called from %pS\n",
		       __func__, __builtin_वापस_address(0));
		वापस 0;
	पूर्ण

	अगर (svc->fwmark == 0) अणु
		/*
		 *  Hash it by <netns,protocol,addr,port> in ip_vs_svc_table
		 */
		hash = ip_vs_svc_hashkey(svc->ipvs, svc->af, svc->protocol,
					 &svc->addr, svc->port);
		hlist_add_head_rcu(&svc->s_list, &ip_vs_svc_table[hash]);
	पूर्ण अन्यथा अणु
		/*
		 *  Hash it by fwmark in svc_fwm_table
		 */
		hash = ip_vs_svc_fwm_hashkey(svc->ipvs, svc->fwmark);
		hlist_add_head_rcu(&svc->f_list, &ip_vs_svc_fwm_table[hash]);
	पूर्ण

	svc->flags |= IP_VS_SVC_F_HASHED;
	/* increase its refcnt because it is referenced by the svc table */
	atomic_inc(&svc->refcnt);
	वापस 1;
पूर्ण


/*
 *	Unhashes a service from svc_table / svc_fwm_table.
 *	Should be called with locked tables.
 */
अटल पूर्णांक ip_vs_svc_unhash(काष्ठा ip_vs_service *svc)
अणु
	अगर (!(svc->flags & IP_VS_SVC_F_HASHED)) अणु
		pr_err("%s(): request for unhash flagged, called from %pS\n",
		       __func__, __builtin_वापस_address(0));
		वापस 0;
	पूर्ण

	अगर (svc->fwmark == 0) अणु
		/* Remove it from the svc_table table */
		hlist_del_rcu(&svc->s_list);
	पूर्ण अन्यथा अणु
		/* Remove it from the svc_fwm_table table */
		hlist_del_rcu(&svc->f_list);
	पूर्ण

	svc->flags &= ~IP_VS_SVC_F_HASHED;
	atomic_dec(&svc->refcnt);
	वापस 1;
पूर्ण


/*
 *	Get service by अणुnetns, proto,addr,portपूर्ण in the service table.
 */
अटल अंतरभूत काष्ठा ip_vs_service *
__ip_vs_service_find(काष्ठा netns_ipvs *ipvs, पूर्णांक af, __u16 protocol,
		     स्थिर जोड़ nf_inet_addr *vaddr, __be16 vport)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा ip_vs_service *svc;

	/* Check क्रम "full" addressed entries */
	hash = ip_vs_svc_hashkey(ipvs, af, protocol, vaddr, vport);

	hlist_क्रम_each_entry_rcu(svc, &ip_vs_svc_table[hash], s_list) अणु
		अगर ((svc->af == af)
		    && ip_vs_addr_equal(af, &svc->addr, vaddr)
		    && (svc->port == vport)
		    && (svc->protocol == protocol)
		    && (svc->ipvs == ipvs)) अणु
			/* HIT */
			वापस svc;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण


/*
 *	Get service by अणुfwmarkपूर्ण in the service table.
 */
अटल अंतरभूत काष्ठा ip_vs_service *
__ip_vs_svc_fwm_find(काष्ठा netns_ipvs *ipvs, पूर्णांक af, __u32 fwmark)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा ip_vs_service *svc;

	/* Check क्रम fwmark addressed entries */
	hash = ip_vs_svc_fwm_hashkey(ipvs, fwmark);

	hlist_क्रम_each_entry_rcu(svc, &ip_vs_svc_fwm_table[hash], f_list) अणु
		अगर (svc->fwmark == fwmark && svc->af == af
		    && (svc->ipvs == ipvs)) अणु
			/* HIT */
			वापस svc;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/* Find service, called under RCU lock */
काष्ठा ip_vs_service *
ip_vs_service_find(काष्ठा netns_ipvs *ipvs, पूर्णांक af, __u32 fwmark, __u16 protocol,
		   स्थिर जोड़ nf_inet_addr *vaddr, __be16 vport)
अणु
	काष्ठा ip_vs_service *svc;

	/*
	 *	Check the table hashed by fwmark first
	 */
	अगर (fwmark) अणु
		svc = __ip_vs_svc_fwm_find(ipvs, af, fwmark);
		अगर (svc)
			जाओ out;
	पूर्ण

	/*
	 *	Check the table hashed by <protocol,addr,port>
	 *	क्रम "full" addressed entries
	 */
	svc = __ip_vs_service_find(ipvs, af, protocol, vaddr, vport);

	अगर (!svc && protocol == IPPROTO_TCP &&
	    atomic_पढ़ो(&ipvs->ftpsvc_counter) &&
	    (vport == FTPDATA || !inet_port_requires_bind_service(ipvs->net, ntohs(vport)))) अणु
		/*
		 * Check अगर ftp service entry exists, the packet
		 * might beदीर्घ to FTP data connections.
		 */
		svc = __ip_vs_service_find(ipvs, af, protocol, vaddr, FTPPORT);
	पूर्ण

	अगर (svc == शून्य
	    && atomic_पढ़ो(&ipvs->nullsvc_counter)) अणु
		/*
		 * Check अगर the catch-all port (port zero) exists
		 */
		svc = __ip_vs_service_find(ipvs, af, protocol, vaddr, 0);
	पूर्ण

  out:
	IP_VS_DBG_BUF(9, "lookup service: fwm %u %s %s:%u %s\n",
		      fwmark, ip_vs_proto_name(protocol),
		      IP_VS_DBG_ADDR(af, vaddr), ntohs(vport),
		      svc ? "hit" : "not hit");

	वापस svc;
पूर्ण


अटल अंतरभूत व्योम
__ip_vs_bind_svc(काष्ठा ip_vs_dest *dest, काष्ठा ip_vs_service *svc)
अणु
	atomic_inc(&svc->refcnt);
	rcu_assign_poपूर्णांकer(dest->svc, svc);
पूर्ण

अटल व्योम ip_vs_service_मुक्त(काष्ठा ip_vs_service *svc)
अणु
	मुक्त_percpu(svc->stats.cpustats);
	kमुक्त(svc);
पूर्ण

अटल व्योम ip_vs_service_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा ip_vs_service *svc;

	svc = container_of(head, काष्ठा ip_vs_service, rcu_head);
	ip_vs_service_मुक्त(svc);
पूर्ण

अटल व्योम __ip_vs_svc_put(काष्ठा ip_vs_service *svc, bool करो_delay)
अणु
	अगर (atomic_dec_and_test(&svc->refcnt)) अणु
		IP_VS_DBG_BUF(3, "Removing service %u/%s:%u\n",
			      svc->fwmark,
			      IP_VS_DBG_ADDR(svc->af, &svc->addr),
			      ntohs(svc->port));
		अगर (करो_delay)
			call_rcu(&svc->rcu_head, ip_vs_service_rcu_मुक्त);
		अन्यथा
			ip_vs_service_मुक्त(svc);
	पूर्ण
पूर्ण


/*
 *	Returns hash value क्रम real service
 */
अटल अंतरभूत अचिन्हित पूर्णांक ip_vs_rs_hashkey(पूर्णांक af,
					    स्थिर जोड़ nf_inet_addr *addr,
					    __be16 port)
अणु
	अचिन्हित पूर्णांक porth = ntohs(port);
	__be32 addr_fold = addr->ip;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		addr_fold = addr->ip6[0]^addr->ip6[1]^
			    addr->ip6[2]^addr->ip6[3];
#पूर्ण_अगर

	वापस (ntohl(addr_fold)^(porth>>IP_VS_RTAB_BITS)^porth)
		& IP_VS_RTAB_MASK;
पूर्ण

/* Hash ip_vs_dest in rs_table by <proto,addr,port>. */
अटल व्योम ip_vs_rs_hash(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_dest *dest)
अणु
	अचिन्हित पूर्णांक hash;
	__be16 port;

	अगर (dest->in_rs_table)
		वापस;

	चयन (IP_VS_DFWD_METHOD(dest)) अणु
	हाल IP_VS_CONN_F_MASQ:
		port = dest->port;
		अवरोध;
	हाल IP_VS_CONN_F_TUNNEL:
		चयन (dest->tun_type) अणु
		हाल IP_VS_CONN_F_TUNNEL_TYPE_GUE:
			port = dest->tun_port;
			अवरोध;
		हाल IP_VS_CONN_F_TUNNEL_TYPE_IPIP:
		हाल IP_VS_CONN_F_TUNNEL_TYPE_GRE:
			port = 0;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/*
	 *	Hash by proto,addr,port,
	 *	which are the parameters of the real service.
	 */
	hash = ip_vs_rs_hashkey(dest->af, &dest->addr, port);

	hlist_add_head_rcu(&dest->d_list, &ipvs->rs_table[hash]);
	dest->in_rs_table = 1;
पूर्ण

/* Unhash ip_vs_dest from rs_table. */
अटल व्योम ip_vs_rs_unhash(काष्ठा ip_vs_dest *dest)
अणु
	/*
	 * Remove it from the rs_table table.
	 */
	अगर (dest->in_rs_table) अणु
		hlist_del_rcu(&dest->d_list);
		dest->in_rs_table = 0;
	पूर्ण
पूर्ण

/* Check अगर real service by <proto,addr,port> is present */
bool ip_vs_has_real_service(काष्ठा netns_ipvs *ipvs, पूर्णांक af, __u16 protocol,
			    स्थिर जोड़ nf_inet_addr *daddr, __be16 dport)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा ip_vs_dest *dest;

	/* Check क्रम "full" addressed entries */
	hash = ip_vs_rs_hashkey(af, daddr, dport);

	hlist_क्रम_each_entry_rcu(dest, &ipvs->rs_table[hash], d_list) अणु
		अगर (dest->port == dport &&
		    dest->af == af &&
		    ip_vs_addr_equal(af, &dest->addr, daddr) &&
		    (dest->protocol == protocol || dest->vfwmark) &&
		    IP_VS_DFWD_METHOD(dest) == IP_VS_CONN_F_MASQ) अणु
			/* HIT */
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/* Find real service record by <proto,addr,port>.
 * In हाल of multiple records with the same <proto,addr,port>, only
 * the first found record is वापसed.
 *
 * To be called under RCU lock.
 */
काष्ठा ip_vs_dest *ip_vs_find_real_service(काष्ठा netns_ipvs *ipvs, पूर्णांक af,
					   __u16 protocol,
					   स्थिर जोड़ nf_inet_addr *daddr,
					   __be16 dport)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा ip_vs_dest *dest;

	/* Check क्रम "full" addressed entries */
	hash = ip_vs_rs_hashkey(af, daddr, dport);

	hlist_क्रम_each_entry_rcu(dest, &ipvs->rs_table[hash], d_list) अणु
		अगर (dest->port == dport &&
		    dest->af == af &&
		    ip_vs_addr_equal(af, &dest->addr, daddr) &&
		    (dest->protocol == protocol || dest->vfwmark) &&
		    IP_VS_DFWD_METHOD(dest) == IP_VS_CONN_F_MASQ) अणु
			/* HIT */
			वापस dest;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/* Find real service record by <af,addr,tun_port>.
 * In हाल of multiple records with the same <af,addr,tun_port>, only
 * the first found record is वापसed.
 *
 * To be called under RCU lock.
 */
काष्ठा ip_vs_dest *ip_vs_find_tunnel(काष्ठा netns_ipvs *ipvs, पूर्णांक af,
				     स्थिर जोड़ nf_inet_addr *daddr,
				     __be16 tun_port)
अणु
	काष्ठा ip_vs_dest *dest;
	अचिन्हित पूर्णांक hash;

	/* Check क्रम "full" addressed entries */
	hash = ip_vs_rs_hashkey(af, daddr, tun_port);

	hlist_क्रम_each_entry_rcu(dest, &ipvs->rs_table[hash], d_list) अणु
		अगर (dest->tun_port == tun_port &&
		    dest->af == af &&
		    ip_vs_addr_equal(af, &dest->addr, daddr) &&
		    IP_VS_DFWD_METHOD(dest) == IP_VS_CONN_F_TUNNEL) अणु
			/* HIT */
			वापस dest;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/* Lookup destination by अणुaddr,portपूर्ण in the given service
 * Called under RCU lock.
 */
अटल काष्ठा ip_vs_dest *
ip_vs_lookup_dest(काष्ठा ip_vs_service *svc, पूर्णांक dest_af,
		  स्थिर जोड़ nf_inet_addr *daddr, __be16 dport)
अणु
	काष्ठा ip_vs_dest *dest;

	/*
	 * Find the destination क्रम the given service
	 */
	list_क्रम_each_entry_rcu(dest, &svc->destinations, n_list) अणु
		अगर ((dest->af == dest_af) &&
		    ip_vs_addr_equal(dest_af, &dest->addr, daddr) &&
		    (dest->port == dport)) अणु
			/* HIT */
			वापस dest;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Find destination by अणुdaddr,dport,vaddr,protocolपूर्ण
 * Created to be used in ip_vs_process_message() in
 * the backup synchronization daemon. It finds the
 * destination to be bound to the received connection
 * on the backup.
 * Called under RCU lock, no refcnt is वापसed.
 */
काष्ठा ip_vs_dest *ip_vs_find_dest(काष्ठा netns_ipvs *ipvs, पूर्णांक svc_af, पूर्णांक dest_af,
				   स्थिर जोड़ nf_inet_addr *daddr,
				   __be16 dport,
				   स्थिर जोड़ nf_inet_addr *vaddr,
				   __be16 vport, __u16 protocol, __u32 fwmark,
				   __u32 flags)
अणु
	काष्ठा ip_vs_dest *dest;
	काष्ठा ip_vs_service *svc;
	__be16 port = dport;

	svc = ip_vs_service_find(ipvs, svc_af, fwmark, protocol, vaddr, vport);
	अगर (!svc)
		वापस शून्य;
	अगर (fwmark && (flags & IP_VS_CONN_F_FWD_MASK) != IP_VS_CONN_F_MASQ)
		port = 0;
	dest = ip_vs_lookup_dest(svc, dest_af, daddr, port);
	अगर (!dest)
		dest = ip_vs_lookup_dest(svc, dest_af, daddr, port ^ dport);
	वापस dest;
पूर्ण

व्योम ip_vs_dest_dst_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा ip_vs_dest_dst *dest_dst = container_of(head,
						       काष्ठा ip_vs_dest_dst,
						       rcu_head);

	dst_release(dest_dst->dst_cache);
	kमुक्त(dest_dst);
पूर्ण

/* Release dest_dst and dst_cache क्रम dest in user context */
अटल व्योम __ip_vs_dst_cache_reset(काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_dest_dst *old;

	old = rcu_dereference_रक्षित(dest->dest_dst, 1);
	अगर (old) अणु
		RCU_INIT_POINTER(dest->dest_dst, शून्य);
		call_rcu(&old->rcu_head, ip_vs_dest_dst_rcu_मुक्त);
	पूर्ण
पूर्ण

/*
 *  Lookup dest by अणुsvc,addr,portपूर्ण in the destination trash.
 *  The destination trash is used to hold the destinations that are हटाओd
 *  from the service table but are still referenced by some conn entries.
 *  The reason to add the destination trash is when the dest is temporary
 *  करोwn (either by administrator or by monitor program), the dest can be
 *  picked back from the trash, the reमुख्यing connections to the dest can
 *  जारी, and the counting inक्रमmation of the dest is also useful क्रम
 *  scheduling.
 */
अटल काष्ठा ip_vs_dest *
ip_vs_trash_get_dest(काष्ठा ip_vs_service *svc, पूर्णांक dest_af,
		     स्थिर जोड़ nf_inet_addr *daddr, __be16 dport)
अणु
	काष्ठा ip_vs_dest *dest;
	काष्ठा netns_ipvs *ipvs = svc->ipvs;

	/*
	 * Find the destination in trash
	 */
	spin_lock_bh(&ipvs->dest_trash_lock);
	list_क्रम_each_entry(dest, &ipvs->dest_trash, t_list) अणु
		IP_VS_DBG_BUF(3, "Destination %u/%s:%u still in trash, "
			      "dest->refcnt=%d\n",
			      dest->vfwmark,
			      IP_VS_DBG_ADDR(dest->af, &dest->addr),
			      ntohs(dest->port),
			      refcount_पढ़ो(&dest->refcnt));
		अगर (dest->af == dest_af &&
		    ip_vs_addr_equal(dest_af, &dest->addr, daddr) &&
		    dest->port == dport &&
		    dest->vfwmark == svc->fwmark &&
		    dest->protocol == svc->protocol &&
		    (svc->fwmark ||
		     (ip_vs_addr_equal(svc->af, &dest->vaddr, &svc->addr) &&
		      dest->vport == svc->port))) अणु
			/* HIT */
			list_del(&dest->t_list);
			जाओ out;
		पूर्ण
	पूर्ण

	dest = शून्य;

out:
	spin_unlock_bh(&ipvs->dest_trash_lock);

	वापस dest;
पूर्ण

अटल व्योम ip_vs_dest_मुक्त(काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_service *svc = rcu_dereference_रक्षित(dest->svc, 1);

	__ip_vs_dst_cache_reset(dest);
	__ip_vs_svc_put(svc, false);
	मुक्त_percpu(dest->stats.cpustats);
	ip_vs_dest_put_and_मुक्त(dest);
पूर्ण

/*
 *  Clean up all the destinations in the trash
 *  Called by the ip_vs_control_cleanup()
 *
 *  When the ip_vs_control_clearup is activated by ipvs module निकास,
 *  the service tables must have been flushed and all the connections
 *  are expired, and the refcnt of each destination in the trash must
 *  be 1, so we simply release them here.
 */
अटल व्योम ip_vs_trash_cleanup(काष्ठा netns_ipvs *ipvs)
अणु
	काष्ठा ip_vs_dest *dest, *nxt;

	del_समयr_sync(&ipvs->dest_trash_समयr);
	/* No need to use dest_trash_lock */
	list_क्रम_each_entry_safe(dest, nxt, &ipvs->dest_trash, t_list) अणु
		list_del(&dest->t_list);
		ip_vs_dest_मुक्त(dest);
	पूर्ण
पूर्ण

अटल व्योम
ip_vs_copy_stats(काष्ठा ip_vs_kstats *dst, काष्ठा ip_vs_stats *src)
अणु
#घोषणा IP_VS_SHOW_STATS_COUNTER(c) dst->c = src->kstats.c - src->kstats0.c

	spin_lock_bh(&src->lock);

	IP_VS_SHOW_STATS_COUNTER(conns);
	IP_VS_SHOW_STATS_COUNTER(inpkts);
	IP_VS_SHOW_STATS_COUNTER(outpkts);
	IP_VS_SHOW_STATS_COUNTER(inbytes);
	IP_VS_SHOW_STATS_COUNTER(outbytes);

	ip_vs_पढ़ो_estimator(dst, src);

	spin_unlock_bh(&src->lock);
पूर्ण

अटल व्योम
ip_vs_export_stats_user(काष्ठा ip_vs_stats_user *dst, काष्ठा ip_vs_kstats *src)
अणु
	dst->conns = (u32)src->conns;
	dst->inpkts = (u32)src->inpkts;
	dst->outpkts = (u32)src->outpkts;
	dst->inbytes = src->inbytes;
	dst->outbytes = src->outbytes;
	dst->cps = (u32)src->cps;
	dst->inpps = (u32)src->inpps;
	dst->outpps = (u32)src->outpps;
	dst->inbps = (u32)src->inbps;
	dst->outbps = (u32)src->outbps;
पूर्ण

अटल व्योम
ip_vs_zero_stats(काष्ठा ip_vs_stats *stats)
अणु
	spin_lock_bh(&stats->lock);

	/* get current counters as zero poपूर्णांक, rates are zeroed */

#घोषणा IP_VS_ZERO_STATS_COUNTER(c) stats->kstats0.c = stats->kstats.c

	IP_VS_ZERO_STATS_COUNTER(conns);
	IP_VS_ZERO_STATS_COUNTER(inpkts);
	IP_VS_ZERO_STATS_COUNTER(outpkts);
	IP_VS_ZERO_STATS_COUNTER(inbytes);
	IP_VS_ZERO_STATS_COUNTER(outbytes);

	ip_vs_zero_estimator(stats);

	spin_unlock_bh(&stats->lock);
पूर्ण

/*
 *	Update a destination in the given service
 */
अटल व्योम
__ip_vs_update_dest(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_dest *dest,
		    काष्ठा ip_vs_dest_user_kern *udest, पूर्णांक add)
अणु
	काष्ठा netns_ipvs *ipvs = svc->ipvs;
	काष्ठा ip_vs_service *old_svc;
	काष्ठा ip_vs_scheduler *sched;
	पूर्णांक conn_flags;

	/* We cannot modअगरy an address and change the address family */
	BUG_ON(!add && udest->af != dest->af);

	अगर (add && udest->af != svc->af)
		ipvs->mixed_address_family_dests++;

	/* keep the last_weight with latest non-0 weight */
	अगर (add || udest->weight != 0)
		atomic_set(&dest->last_weight, udest->weight);

	/* set the weight and the flags */
	atomic_set(&dest->weight, udest->weight);
	conn_flags = udest->conn_flags & IP_VS_CONN_F_DEST_MASK;
	conn_flags |= IP_VS_CONN_F_INACTIVE;

	/* Need to rehash? */
	अगर ((udest->conn_flags & IP_VS_CONN_F_FWD_MASK) !=
	    IP_VS_DFWD_METHOD(dest) ||
	    udest->tun_type != dest->tun_type ||
	    udest->tun_port != dest->tun_port)
		ip_vs_rs_unhash(dest);

	/* set the tunnel info */
	dest->tun_type = udest->tun_type;
	dest->tun_port = udest->tun_port;
	dest->tun_flags = udest->tun_flags;

	/* set the IP_VS_CONN_F_NOOUTPUT flag अगर not masquerading/NAT */
	अगर ((conn_flags & IP_VS_CONN_F_FWD_MASK) != IP_VS_CONN_F_MASQ) अणु
		conn_flags |= IP_VS_CONN_F_NOOUTPUT;
	पूर्ण अन्यथा अणु
		/* FTP-NAT requires conntrack क्रम mangling */
		अगर (svc->port == FTPPORT)
			ip_vs_रेजिस्टर_conntrack(svc);
	पूर्ण
	atomic_set(&dest->conn_flags, conn_flags);
	/* Put the real service in rs_table अगर not present. */
	ip_vs_rs_hash(ipvs, dest);

	/* bind the service */
	old_svc = rcu_dereference_रक्षित(dest->svc, 1);
	अगर (!old_svc) अणु
		__ip_vs_bind_svc(dest, svc);
	पूर्ण अन्यथा अणु
		अगर (old_svc != svc) अणु
			ip_vs_zero_stats(&dest->stats);
			__ip_vs_bind_svc(dest, svc);
			__ip_vs_svc_put(old_svc, true);
		पूर्ण
	पूर्ण

	/* set the dest status flags */
	dest->flags |= IP_VS_DEST_F_AVAILABLE;

	अगर (udest->u_threshold == 0 || udest->u_threshold > dest->u_threshold)
		dest->flags &= ~IP_VS_DEST_F_OVERLOAD;
	dest->u_threshold = udest->u_threshold;
	dest->l_threshold = udest->l_threshold;

	dest->af = udest->af;

	spin_lock_bh(&dest->dst_lock);
	__ip_vs_dst_cache_reset(dest);
	spin_unlock_bh(&dest->dst_lock);

	अगर (add) अणु
		ip_vs_start_estimator(svc->ipvs, &dest->stats);
		list_add_rcu(&dest->n_list, &svc->destinations);
		svc->num_dests++;
		sched = rcu_dereference_रक्षित(svc->scheduler, 1);
		अगर (sched && sched->add_dest)
			sched->add_dest(svc, dest);
	पूर्ण अन्यथा अणु
		sched = rcu_dereference_रक्षित(svc->scheduler, 1);
		अगर (sched && sched->upd_dest)
			sched->upd_dest(svc, dest);
	पूर्ण
पूर्ण


/*
 *	Create a destination क्रम the given service
 */
अटल पूर्णांक
ip_vs_new_dest(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_dest_user_kern *udest,
	       काष्ठा ip_vs_dest **dest_p)
अणु
	काष्ठा ip_vs_dest *dest;
	अचिन्हित पूर्णांक atype, i;

	EnterFunction(2);

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (udest->af == AF_INET6) अणु
		पूर्णांक ret;

		atype = ipv6_addr_type(&udest->addr.in6);
		अगर ((!(atype & IPV6_ADDR_UNICAST) ||
			atype & IPV6_ADDR_LINKLOCAL) &&
			!__ip_vs_addr_is_local_v6(svc->ipvs->net, &udest->addr.in6))
			वापस -EINVAL;

		ret = nf_defrag_ipv6_enable(svc->ipvs->net);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		atype = inet_addr_type(svc->ipvs->net, udest->addr.ip);
		अगर (atype != RTN_LOCAL && atype != RTN_UNICAST)
			वापस -EINVAL;
	पूर्ण

	dest = kzalloc(माप(काष्ठा ip_vs_dest), GFP_KERNEL);
	अगर (dest == शून्य)
		वापस -ENOMEM;

	dest->stats.cpustats = alloc_percpu(काष्ठा ip_vs_cpu_stats);
	अगर (!dest->stats.cpustats)
		जाओ err_alloc;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा ip_vs_cpu_stats *ip_vs_dest_stats;
		ip_vs_dest_stats = per_cpu_ptr(dest->stats.cpustats, i);
		u64_stats_init(&ip_vs_dest_stats->syncp);
	पूर्ण

	dest->af = udest->af;
	dest->protocol = svc->protocol;
	dest->vaddr = svc->addr;
	dest->vport = svc->port;
	dest->vfwmark = svc->fwmark;
	ip_vs_addr_copy(udest->af, &dest->addr, &udest->addr);
	dest->port = udest->port;

	atomic_set(&dest->activeconns, 0);
	atomic_set(&dest->inactconns, 0);
	atomic_set(&dest->persistconns, 0);
	refcount_set(&dest->refcnt, 1);

	INIT_HLIST_NODE(&dest->d_list);
	spin_lock_init(&dest->dst_lock);
	spin_lock_init(&dest->stats.lock);
	__ip_vs_update_dest(svc, dest, udest, 1);

	*dest_p = dest;

	LeaveFunction(2);
	वापस 0;

err_alloc:
	kमुक्त(dest);
	वापस -ENOMEM;
पूर्ण


/*
 *	Add a destination पूर्णांकo an existing service
 */
अटल पूर्णांक
ip_vs_add_dest(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_dest_user_kern *udest)
अणु
	काष्ठा ip_vs_dest *dest;
	जोड़ nf_inet_addr daddr;
	__be16 dport = udest->port;
	पूर्णांक ret;

	EnterFunction(2);

	अगर (udest->weight < 0) अणु
		pr_err("%s(): server weight less than zero\n", __func__);
		वापस -दुस्फल;
	पूर्ण

	अगर (udest->l_threshold > udest->u_threshold) अणु
		pr_err("%s(): lower threshold is higher than upper threshold\n",
			__func__);
		वापस -दुस्फल;
	पूर्ण

	अगर (udest->tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
		अगर (udest->tun_port == 0) अणु
			pr_err("%s(): tunnel port is zero\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ip_vs_addr_copy(udest->af, &daddr, &udest->addr);

	/* We use function that requires RCU lock */
	rcu_पढ़ो_lock();
	dest = ip_vs_lookup_dest(svc, udest->af, &daddr, dport);
	rcu_पढ़ो_unlock();

	अगर (dest != शून्य) अणु
		IP_VS_DBG(1, "%s(): dest already exists\n", __func__);
		वापस -EEXIST;
	पूर्ण

	/*
	 * Check अगर the dest alपढ़ोy exists in the trash and
	 * is from the same service
	 */
	dest = ip_vs_trash_get_dest(svc, udest->af, &daddr, dport);

	अगर (dest != शून्य) अणु
		IP_VS_DBG_BUF(3, "Get destination %s:%u from trash, "
			      "dest->refcnt=%d, service %u/%s:%u\n",
			      IP_VS_DBG_ADDR(udest->af, &daddr), ntohs(dport),
			      refcount_पढ़ो(&dest->refcnt),
			      dest->vfwmark,
			      IP_VS_DBG_ADDR(svc->af, &dest->vaddr),
			      ntohs(dest->vport));

		__ip_vs_update_dest(svc, dest, udest, 1);
		ret = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Allocate and initialize the dest काष्ठाure
		 */
		ret = ip_vs_new_dest(svc, udest, &dest);
	पूर्ण
	LeaveFunction(2);

	वापस ret;
पूर्ण


/*
 *	Edit a destination in the given service
 */
अटल पूर्णांक
ip_vs_edit_dest(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_dest_user_kern *udest)
अणु
	काष्ठा ip_vs_dest *dest;
	जोड़ nf_inet_addr daddr;
	__be16 dport = udest->port;

	EnterFunction(2);

	अगर (udest->weight < 0) अणु
		pr_err("%s(): server weight less than zero\n", __func__);
		वापस -दुस्फल;
	पूर्ण

	अगर (udest->l_threshold > udest->u_threshold) अणु
		pr_err("%s(): lower threshold is higher than upper threshold\n",
			__func__);
		वापस -दुस्फल;
	पूर्ण

	अगर (udest->tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
		अगर (udest->tun_port == 0) अणु
			pr_err("%s(): tunnel port is zero\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ip_vs_addr_copy(udest->af, &daddr, &udest->addr);

	/* We use function that requires RCU lock */
	rcu_पढ़ो_lock();
	dest = ip_vs_lookup_dest(svc, udest->af, &daddr, dport);
	rcu_पढ़ो_unlock();

	अगर (dest == शून्य) अणु
		IP_VS_DBG(1, "%s(): dest doesn't exist\n", __func__);
		वापस -ENOENT;
	पूर्ण

	__ip_vs_update_dest(svc, dest, udest, 0);
	LeaveFunction(2);

	वापस 0;
पूर्ण

/*
 *	Delete a destination (must be alपढ़ोy unlinked from the service)
 */
अटल व्योम __ip_vs_del_dest(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_dest *dest,
			     bool cleanup)
अणु
	ip_vs_stop_estimator(ipvs, &dest->stats);

	/*
	 *  Remove it from the d-linked list with the real services.
	 */
	ip_vs_rs_unhash(dest);

	spin_lock_bh(&ipvs->dest_trash_lock);
	IP_VS_DBG_BUF(3, "Moving dest %s:%u into trash, dest->refcnt=%d\n",
		      IP_VS_DBG_ADDR(dest->af, &dest->addr), ntohs(dest->port),
		      refcount_पढ़ो(&dest->refcnt));
	अगर (list_empty(&ipvs->dest_trash) && !cleanup)
		mod_समयr(&ipvs->dest_trash_समयr,
			  jअगरfies + (IP_VS_DEST_TRASH_PERIOD >> 1));
	/* dest lives in trash with reference */
	list_add(&dest->t_list, &ipvs->dest_trash);
	dest->idle_start = 0;
	spin_unlock_bh(&ipvs->dest_trash_lock);

	/* Queue up delayed work to expire all no destination connections.
	 * No-op when CONFIG_SYSCTL is disabled.
	 */
	अगर (!cleanup)
		ip_vs_enqueue_expire_nodest_conns(ipvs);
पूर्ण


/*
 *	Unlink a destination from the given service
 */
अटल व्योम __ip_vs_unlink_dest(काष्ठा ip_vs_service *svc,
				काष्ठा ip_vs_dest *dest,
				पूर्णांक svcupd)
अणु
	dest->flags &= ~IP_VS_DEST_F_AVAILABLE;

	/*
	 *  Remove it from the d-linked destination list.
	 */
	list_del_rcu(&dest->n_list);
	svc->num_dests--;

	अगर (dest->af != svc->af)
		svc->ipvs->mixed_address_family_dests--;

	अगर (svcupd) अणु
		काष्ठा ip_vs_scheduler *sched;

		sched = rcu_dereference_रक्षित(svc->scheduler, 1);
		अगर (sched && sched->del_dest)
			sched->del_dest(svc, dest);
	पूर्ण
पूर्ण


/*
 *	Delete a destination server in the given service
 */
अटल पूर्णांक
ip_vs_del_dest(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_dest_user_kern *udest)
अणु
	काष्ठा ip_vs_dest *dest;
	__be16 dport = udest->port;

	EnterFunction(2);

	/* We use function that requires RCU lock */
	rcu_पढ़ो_lock();
	dest = ip_vs_lookup_dest(svc, udest->af, &udest->addr, dport);
	rcu_पढ़ो_unlock();

	अगर (dest == शून्य) अणु
		IP_VS_DBG(1, "%s(): destination not found!\n", __func__);
		वापस -ENOENT;
	पूर्ण

	/*
	 *	Unlink dest from the service
	 */
	__ip_vs_unlink_dest(svc, dest, 1);

	/*
	 *	Delete the destination
	 */
	__ip_vs_del_dest(svc->ipvs, dest, false);

	LeaveFunction(2);

	वापस 0;
पूर्ण

अटल व्योम ip_vs_dest_trash_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा netns_ipvs *ipvs = from_समयr(ipvs, t, dest_trash_समयr);
	काष्ठा ip_vs_dest *dest, *next;
	अचिन्हित दीर्घ now = jअगरfies;

	spin_lock(&ipvs->dest_trash_lock);
	list_क्रम_each_entry_safe(dest, next, &ipvs->dest_trash, t_list) अणु
		अगर (refcount_पढ़ो(&dest->refcnt) > 1)
			जारी;
		अगर (dest->idle_start) अणु
			अगर (समय_beक्रमe(now, dest->idle_start +
					     IP_VS_DEST_TRASH_PERIOD))
				जारी;
		पूर्ण अन्यथा अणु
			dest->idle_start = max(1UL, now);
			जारी;
		पूर्ण
		IP_VS_DBG_BUF(3, "Removing destination %u/%s:%u from trash\n",
			      dest->vfwmark,
			      IP_VS_DBG_ADDR(dest->af, &dest->addr),
			      ntohs(dest->port));
		list_del(&dest->t_list);
		ip_vs_dest_मुक्त(dest);
	पूर्ण
	अगर (!list_empty(&ipvs->dest_trash))
		mod_समयr(&ipvs->dest_trash_समयr,
			  jअगरfies + (IP_VS_DEST_TRASH_PERIOD >> 1));
	spin_unlock(&ipvs->dest_trash_lock);
पूर्ण

/*
 *	Add a service पूर्णांकo the service hash table
 */
अटल पूर्णांक
ip_vs_add_service(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_service_user_kern *u,
		  काष्ठा ip_vs_service **svc_p)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा ip_vs_scheduler *sched = शून्य;
	काष्ठा ip_vs_pe *pe = शून्य;
	काष्ठा ip_vs_service *svc = शून्य;
	पूर्णांक ret_hooks = -1;

	/* increase the module use count */
	अगर (!ip_vs_use_count_inc())
		वापस -ENOPROTOOPT;

	/* Lookup the scheduler by 'u->sched_name' */
	अगर (म_भेद(u->sched_name, "none")) अणु
		sched = ip_vs_scheduler_get(u->sched_name);
		अगर (!sched) अणु
			pr_info("Scheduler module ip_vs_%s not found\n",
				u->sched_name);
			ret = -ENOENT;
			जाओ out_err;
		पूर्ण
	पूर्ण

	अगर (u->pe_name && *u->pe_name) अणु
		pe = ip_vs_pe_getbyname(u->pe_name);
		अगर (pe == शून्य) अणु
			pr_info("persistence engine module ip_vs_pe_%s "
				"not found\n", u->pe_name);
			ret = -ENOENT;
			जाओ out_err;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (u->af == AF_INET6) अणु
		__u32 plen = (__क्रमce __u32) u->neपंचांगask;

		अगर (plen < 1 || plen > 128) अणु
			ret = -EINVAL;
			जाओ out_err;
		पूर्ण

		ret = nf_defrag_ipv6_enable(ipvs->net);
		अगर (ret)
			जाओ out_err;
	पूर्ण
#पूर्ण_अगर

	अगर ((u->af == AF_INET && !ipvs->num_services) ||
	    (u->af == AF_INET6 && !ipvs->num_services6)) अणु
		ret = ip_vs_रेजिस्टर_hooks(ipvs, u->af);
		अगर (ret < 0)
			जाओ out_err;
		ret_hooks = ret;
	पूर्ण

	svc = kzalloc(माप(काष्ठा ip_vs_service), GFP_KERNEL);
	अगर (svc == शून्य) अणु
		IP_VS_DBG(1, "%s(): no memory\n", __func__);
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण
	svc->stats.cpustats = alloc_percpu(काष्ठा ip_vs_cpu_stats);
	अगर (!svc->stats.cpustats) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	क्रम_each_possible_cpu(i) अणु
		काष्ठा ip_vs_cpu_stats *ip_vs_stats;
		ip_vs_stats = per_cpu_ptr(svc->stats.cpustats, i);
		u64_stats_init(&ip_vs_stats->syncp);
	पूर्ण


	/* I'm the first user of the service */
	atomic_set(&svc->refcnt, 0);

	svc->af = u->af;
	svc->protocol = u->protocol;
	ip_vs_addr_copy(svc->af, &svc->addr, &u->addr);
	svc->port = u->port;
	svc->fwmark = u->fwmark;
	svc->flags = u->flags & ~IP_VS_SVC_F_HASHED;
	svc->समयout = u->समयout * HZ;
	svc->neपंचांगask = u->neपंचांगask;
	svc->ipvs = ipvs;

	INIT_LIST_HEAD(&svc->destinations);
	spin_lock_init(&svc->sched_lock);
	spin_lock_init(&svc->stats.lock);

	/* Bind the scheduler */
	अगर (sched) अणु
		ret = ip_vs_bind_scheduler(svc, sched);
		अगर (ret)
			जाओ out_err;
		sched = शून्य;
	पूर्ण

	/* Bind the ct retriever */
	RCU_INIT_POINTER(svc->pe, pe);
	pe = शून्य;

	/* Update the भव service counters */
	अगर (svc->port == FTPPORT)
		atomic_inc(&ipvs->ftpsvc_counter);
	अन्यथा अगर (svc->port == 0)
		atomic_inc(&ipvs->nullsvc_counter);
	अगर (svc->pe && svc->pe->conn_out)
		atomic_inc(&ipvs->conn_out_counter);

	ip_vs_start_estimator(ipvs, &svc->stats);

	/* Count only IPv4 services क्रम old get/setsockopt पूर्णांकerface */
	अगर (svc->af == AF_INET)
		ipvs->num_services++;
	अन्यथा अगर (svc->af == AF_INET6)
		ipvs->num_services6++;

	/* Hash the service पूर्णांकo the service table */
	ip_vs_svc_hash(svc);

	*svc_p = svc;
	/* Now there is a service - full throttle */
	ipvs->enable = 1;
	वापस 0;


 out_err:
	अगर (ret_hooks >= 0)
		ip_vs_unरेजिस्टर_hooks(ipvs, u->af);
	अगर (svc != शून्य) अणु
		ip_vs_unbind_scheduler(svc, sched);
		ip_vs_service_मुक्त(svc);
	पूर्ण
	ip_vs_scheduler_put(sched);
	ip_vs_pe_put(pe);

	/* decrease the module use count */
	ip_vs_use_count_dec();

	वापस ret;
पूर्ण


/*
 *	Edit a service and bind it with a new scheduler
 */
अटल पूर्णांक
ip_vs_edit_service(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_service_user_kern *u)
अणु
	काष्ठा ip_vs_scheduler *sched = शून्य, *old_sched;
	काष्ठा ip_vs_pe *pe = शून्य, *old_pe = शून्य;
	पूर्णांक ret = 0;
	bool new_pe_conn_out, old_pe_conn_out;

	/*
	 * Lookup the scheduler, by 'u->sched_name'
	 */
	अगर (म_भेद(u->sched_name, "none")) अणु
		sched = ip_vs_scheduler_get(u->sched_name);
		अगर (!sched) अणु
			pr_info("Scheduler module ip_vs_%s not found\n",
				u->sched_name);
			वापस -ENOENT;
		पूर्ण
	पूर्ण
	old_sched = sched;

	अगर (u->pe_name && *u->pe_name) अणु
		pe = ip_vs_pe_getbyname(u->pe_name);
		अगर (pe == शून्य) अणु
			pr_info("persistence engine module ip_vs_pe_%s "
				"not found\n", u->pe_name);
			ret = -ENOENT;
			जाओ out;
		पूर्ण
		old_pe = pe;
	पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (u->af == AF_INET6) अणु
		__u32 plen = (__क्रमce __u32) u->neपंचांगask;

		अगर (plen < 1 || plen > 128) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	old_sched = rcu_dereference_रक्षित(svc->scheduler, 1);
	अगर (sched != old_sched) अणु
		अगर (old_sched) अणु
			ip_vs_unbind_scheduler(svc, old_sched);
			RCU_INIT_POINTER(svc->scheduler, शून्य);
			/* Wait all svc->sched_data users */
			synchronize_rcu();
		पूर्ण
		/* Bind the new scheduler */
		अगर (sched) अणु
			ret = ip_vs_bind_scheduler(svc, sched);
			अगर (ret) अणु
				ip_vs_scheduler_put(sched);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Set the flags and समयout value
	 */
	svc->flags = u->flags | IP_VS_SVC_F_HASHED;
	svc->समयout = u->समयout * HZ;
	svc->neपंचांगask = u->neपंचांगask;

	old_pe = rcu_dereference_रक्षित(svc->pe, 1);
	अगर (pe != old_pe) अणु
		rcu_assign_poपूर्णांकer(svc->pe, pe);
		/* check क्रम optional methods in new pe */
		new_pe_conn_out = (pe && pe->conn_out) ? true : false;
		old_pe_conn_out = (old_pe && old_pe->conn_out) ? true : false;
		अगर (new_pe_conn_out && !old_pe_conn_out)
			atomic_inc(&svc->ipvs->conn_out_counter);
		अगर (old_pe_conn_out && !new_pe_conn_out)
			atomic_dec(&svc->ipvs->conn_out_counter);
	पूर्ण

out:
	ip_vs_scheduler_put(old_sched);
	ip_vs_pe_put(old_pe);
	वापस ret;
पूर्ण

/*
 *	Delete a service from the service list
 *	- The service must be unlinked, unlocked and not referenced!
 *	- We are called under _bh lock
 */
अटल व्योम __ip_vs_del_service(काष्ठा ip_vs_service *svc, bool cleanup)
अणु
	काष्ठा ip_vs_dest *dest, *nxt;
	काष्ठा ip_vs_scheduler *old_sched;
	काष्ठा ip_vs_pe *old_pe;
	काष्ठा netns_ipvs *ipvs = svc->ipvs;

	अगर (svc->af == AF_INET) अणु
		ipvs->num_services--;
		अगर (!ipvs->num_services)
			ip_vs_unरेजिस्टर_hooks(ipvs, svc->af);
	पूर्ण अन्यथा अगर (svc->af == AF_INET6) अणु
		ipvs->num_services6--;
		अगर (!ipvs->num_services6)
			ip_vs_unरेजिस्टर_hooks(ipvs, svc->af);
	पूर्ण

	ip_vs_stop_estimator(svc->ipvs, &svc->stats);

	/* Unbind scheduler */
	old_sched = rcu_dereference_रक्षित(svc->scheduler, 1);
	ip_vs_unbind_scheduler(svc, old_sched);
	ip_vs_scheduler_put(old_sched);

	/* Unbind persistence engine, keep svc->pe */
	old_pe = rcu_dereference_रक्षित(svc->pe, 1);
	अगर (old_pe && old_pe->conn_out)
		atomic_dec(&ipvs->conn_out_counter);
	ip_vs_pe_put(old_pe);

	/*
	 *    Unlink the whole destination list
	 */
	list_क्रम_each_entry_safe(dest, nxt, &svc->destinations, n_list) अणु
		__ip_vs_unlink_dest(svc, dest, 0);
		__ip_vs_del_dest(svc->ipvs, dest, cleanup);
	पूर्ण

	/*
	 *    Update the भव service counters
	 */
	अगर (svc->port == FTPPORT)
		atomic_dec(&ipvs->ftpsvc_counter);
	अन्यथा अगर (svc->port == 0)
		atomic_dec(&ipvs->nullsvc_counter);

	/*
	 *    Free the service अगर nobody refers to it
	 */
	__ip_vs_svc_put(svc, true);

	/* decrease the module use count */
	ip_vs_use_count_dec();
पूर्ण

/*
 * Unlink a service from list and try to delete it अगर its refcnt reached 0
 */
अटल व्योम ip_vs_unlink_service(काष्ठा ip_vs_service *svc, bool cleanup)
अणु
	ip_vs_unरेजिस्टर_conntrack(svc);
	/* Hold svc to aव्योम द्विगुन release from dest_trash */
	atomic_inc(&svc->refcnt);
	/*
	 * Unhash it from the service table
	 */
	ip_vs_svc_unhash(svc);

	__ip_vs_del_service(svc, cleanup);
पूर्ण

/*
 *	Delete a service from the service list
 */
अटल पूर्णांक ip_vs_del_service(काष्ठा ip_vs_service *svc)
अणु
	अगर (svc == शून्य)
		वापस -EEXIST;
	ip_vs_unlink_service(svc, false);

	वापस 0;
पूर्ण


/*
 *	Flush all the भव services
 */
अटल पूर्णांक ip_vs_flush(काष्ठा netns_ipvs *ipvs, bool cleanup)
अणु
	पूर्णांक idx;
	काष्ठा ip_vs_service *svc;
	काष्ठा hlist_node *n;

	/*
	 * Flush the service table hashed by <netns,protocol,addr,port>
	 */
	क्रम(idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		hlist_क्रम_each_entry_safe(svc, n, &ip_vs_svc_table[idx],
					  s_list) अणु
			अगर (svc->ipvs == ipvs)
				ip_vs_unlink_service(svc, cleanup);
		पूर्ण
	पूर्ण

	/*
	 * Flush the service table hashed by fwmark
	 */
	क्रम(idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		hlist_क्रम_each_entry_safe(svc, n, &ip_vs_svc_fwm_table[idx],
					  f_list) अणु
			अगर (svc->ipvs == ipvs)
				ip_vs_unlink_service(svc, cleanup);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Delete service by अणुnetnsपूर्ण in the service table.
 *	Called by __ip_vs_batch_cleanup()
 */
व्योम ip_vs_service_nets_cleanup(काष्ठा list_head *net_list)
अणु
	काष्ठा netns_ipvs *ipvs;
	काष्ठा net *net;

	EnterFunction(2);
	/* Check क्रम "full" addressed entries */
	mutex_lock(&__ip_vs_mutex);
	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		ipvs = net_ipvs(net);
		ip_vs_flush(ipvs, true);
	पूर्ण
	mutex_unlock(&__ip_vs_mutex);
	LeaveFunction(2);
पूर्ण

/* Put all references क्रम device (dst_cache) */
अटल अंतरभूत व्योम
ip_vs_क्रमget_dev(काष्ठा ip_vs_dest *dest, काष्ठा net_device *dev)
अणु
	काष्ठा ip_vs_dest_dst *dest_dst;

	spin_lock_bh(&dest->dst_lock);
	dest_dst = rcu_dereference_रक्षित(dest->dest_dst, 1);
	अगर (dest_dst && dest_dst->dst_cache->dev == dev) अणु
		IP_VS_DBG_BUF(3, "Reset dev:%s dest %s:%u ,dest->refcnt=%d\n",
			      dev->name,
			      IP_VS_DBG_ADDR(dest->af, &dest->addr),
			      ntohs(dest->port),
			      refcount_पढ़ो(&dest->refcnt));
		__ip_vs_dst_cache_reset(dest);
	पूर्ण
	spin_unlock_bh(&dest->dst_lock);

पूर्ण
/* Netdev event receiver
 * Currently only NETDEV_DOWN is handled to release refs to cached dsts
 */
अटल पूर्णांक ip_vs_dst_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);
	काष्ठा ip_vs_service *svc;
	काष्ठा ip_vs_dest *dest;
	अचिन्हित पूर्णांक idx;

	अगर (event != NETDEV_DOWN || !ipvs)
		वापस NOTIFY_DONE;
	IP_VS_DBG(3, "%s() dev=%s\n", __func__, dev->name);
	EnterFunction(2);
	mutex_lock(&__ip_vs_mutex);
	क्रम (idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		hlist_क्रम_each_entry(svc, &ip_vs_svc_table[idx], s_list) अणु
			अगर (svc->ipvs == ipvs) अणु
				list_क्रम_each_entry(dest, &svc->destinations,
						    n_list) अणु
					ip_vs_क्रमget_dev(dest, dev);
				पूर्ण
			पूर्ण
		पूर्ण

		hlist_क्रम_each_entry(svc, &ip_vs_svc_fwm_table[idx], f_list) अणु
			अगर (svc->ipvs == ipvs) अणु
				list_क्रम_each_entry(dest, &svc->destinations,
						    n_list) अणु
					ip_vs_क्रमget_dev(dest, dev);
				पूर्ण
			पूर्ण

		पूर्ण
	पूर्ण

	spin_lock_bh(&ipvs->dest_trash_lock);
	list_क्रम_each_entry(dest, &ipvs->dest_trash, t_list) अणु
		ip_vs_क्रमget_dev(dest, dev);
	पूर्ण
	spin_unlock_bh(&ipvs->dest_trash_lock);
	mutex_unlock(&__ip_vs_mutex);
	LeaveFunction(2);
	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Zero counters in a service or all services
 */
अटल पूर्णांक ip_vs_zero_service(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_dest *dest;

	list_क्रम_each_entry(dest, &svc->destinations, n_list) अणु
		ip_vs_zero_stats(&dest->stats);
	पूर्ण
	ip_vs_zero_stats(&svc->stats);
	वापस 0;
पूर्ण

अटल पूर्णांक ip_vs_zero_all(काष्ठा netns_ipvs *ipvs)
अणु
	पूर्णांक idx;
	काष्ठा ip_vs_service *svc;

	क्रम(idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		hlist_क्रम_each_entry(svc, &ip_vs_svc_table[idx], s_list) अणु
			अगर (svc->ipvs == ipvs)
				ip_vs_zero_service(svc);
		पूर्ण
	पूर्ण

	क्रम(idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		hlist_क्रम_each_entry(svc, &ip_vs_svc_fwm_table[idx], f_list) अणु
			अगर (svc->ipvs == ipvs)
				ip_vs_zero_service(svc);
		पूर्ण
	पूर्ण

	ip_vs_zero_stats(&ipvs->tot_stats);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL

अटल पूर्णांक three = 3;

अटल पूर्णांक
proc_करो_defense_mode(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा netns_ipvs *ipvs = table->extra2;
	पूर्णांक *valp = table->data;
	पूर्णांक val = *valp;
	पूर्णांक rc;

	काष्ठा ctl_table पंचांगp = अणु
		.data = &val,
		.maxlen = माप(पूर्णांक),
		.mode = table->mode,
	पूर्ण;

	rc = proc_करोपूर्णांकvec(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && (*valp != val)) अणु
		अगर (val < 0 || val > 3) अणु
			rc = -EINVAL;
		पूर्ण अन्यथा अणु
			*valp = val;
			update_defense_level(ipvs);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
proc_करो_sync_threshold(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		       व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *valp = table->data;
	पूर्णांक val[2];
	पूर्णांक rc;
	काष्ठा ctl_table पंचांगp = अणु
		.data = &val,
		.maxlen = table->maxlen,
		.mode = table->mode,
	पूर्ण;

	स_नकल(val, valp, माप(val));
	rc = proc_करोपूर्णांकvec(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो) अणु
		अगर (val[0] < 0 || val[1] < 0 ||
		    (val[0] >= val[1] && val[1]))
			rc = -EINVAL;
		अन्यथा
			स_नकल(valp, val, माप(val));
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
proc_करो_sync_ports(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *valp = table->data;
	पूर्णांक val = *valp;
	पूर्णांक rc;

	काष्ठा ctl_table पंचांगp = अणु
		.data = &val,
		.maxlen = माप(पूर्णांक),
		.mode = table->mode,
	पूर्ण;

	rc = proc_करोपूर्णांकvec(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && (*valp != val)) अणु
		अगर (val < 1 || !is_घातer_of_2(val))
			rc = -EINVAL;
		अन्यथा
			*valp = val;
	पूर्ण
	वापस rc;
पूर्ण

/*
 *	IPVS sysctl table (under the /proc/sys/net/ipv4/vs/)
 *	Do not change order or insert new entries without
 *	align with netns init in ip_vs_control_net_init()
 */

अटल काष्ठा ctl_table vs_vars[] = अणु
	अणु
		.procname	= "amemthresh",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "am_droprate",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "drop_entry",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करो_defense_mode,
	पूर्ण,
	अणु
		.procname	= "drop_packet",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करो_defense_mode,
	पूर्ण,
#अगर_घोषित CONFIG_IP_VS_NFCT
	अणु
		.procname	= "conntrack",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= &proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "secure_tcp",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करो_defense_mode,
	पूर्ण,
	अणु
		.procname	= "snat_reroute",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= &proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "sync_version",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "sync_ports",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करो_sync_ports,
	पूर्ण,
	अणु
		.procname	= "sync_persist_mode",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "sync_qlen_max",
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "sync_sock_size",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "cache_bypass",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "expire_nodest_conn",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "sloppy_tcp",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "sloppy_sctp",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "expire_quiescent_template",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "sync_threshold",
		.maxlen		=
			माप(((काष्ठा netns_ipvs *)0)->sysctl_sync_threshold),
		.mode		= 0644,
		.proc_handler	= proc_करो_sync_threshold,
	पूर्ण,
	अणु
		.procname	= "sync_refresh_period",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "sync_retries",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &three,
	पूर्ण,
	अणु
		.procname	= "nat_icmp_send",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "pmtu_disc",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "backup_only",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "conn_reuse_mode",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "schedule_icmp",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "ignore_tunneled",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#अगर_घोषित CONFIG_IP_VS_DEBUG
	अणु
		.procname	= "debug_level",
		.data		= &sysctl_ip_vs_debug_level,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS

काष्ठा ip_vs_iter अणु
	काष्ठा seq_net_निजी p;  /* Do not move this, netns depends upon it*/
	काष्ठा hlist_head *table;
	पूर्णांक bucket;
पूर्ण;

/*
 *	Write the contents of the VS rule table to a PROCfs file.
 *	(It is kept just क्रम backward compatibility)
 */
अटल अंतरभूत स्थिर अक्षर *ip_vs_fwd_name(अचिन्हित पूर्णांक flags)
अणु
	चयन (flags & IP_VS_CONN_F_FWD_MASK) अणु
	हाल IP_VS_CONN_F_LOCALNODE:
		वापस "Local";
	हाल IP_VS_CONN_F_TUNNEL:
		वापस "Tunnel";
	हाल IP_VS_CONN_F_DROUTE:
		वापस "Route";
	शेष:
		वापस "Masq";
	पूर्ण
पूर्ण


/* Get the Nth entry in the two lists */
अटल काष्ठा ip_vs_service *ip_vs_info_array(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);
	काष्ठा ip_vs_iter *iter = seq->निजी;
	पूर्णांक idx;
	काष्ठा ip_vs_service *svc;

	/* look in hash by protocol */
	क्रम (idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		hlist_क्रम_each_entry_rcu(svc, &ip_vs_svc_table[idx], s_list) अणु
			अगर ((svc->ipvs == ipvs) && pos-- == 0) अणु
				iter->table = ip_vs_svc_table;
				iter->bucket = idx;
				वापस svc;
			पूर्ण
		पूर्ण
	पूर्ण

	/* keep looking in fwmark */
	क्रम (idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		hlist_क्रम_each_entry_rcu(svc, &ip_vs_svc_fwm_table[idx],
					 f_list) अणु
			अगर ((svc->ipvs == ipvs) && pos-- == 0) अणु
				iter->table = ip_vs_svc_fwm_table;
				iter->bucket = idx;
				वापस svc;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *ip_vs_info_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस *pos ? ip_vs_info_array(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण


अटल व्योम *ip_vs_info_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा hlist_node *e;
	काष्ठा ip_vs_iter *iter;
	काष्ठा ip_vs_service *svc;

	++*pos;
	अगर (v == SEQ_START_TOKEN)
		वापस ip_vs_info_array(seq,0);

	svc = v;
	iter = seq->निजी;

	अगर (iter->table == ip_vs_svc_table) अणु
		/* next service in table hashed by protocol */
		e = rcu_dereference(hlist_next_rcu(&svc->s_list));
		अगर (e)
			वापस hlist_entry(e, काष्ठा ip_vs_service, s_list);

		जबतक (++iter->bucket < IP_VS_SVC_TAB_SIZE) अणु
			hlist_क्रम_each_entry_rcu(svc,
						 &ip_vs_svc_table[iter->bucket],
						 s_list) अणु
				वापस svc;
			पूर्ण
		पूर्ण

		iter->table = ip_vs_svc_fwm_table;
		iter->bucket = -1;
		जाओ scan_fwmark;
	पूर्ण

	/* next service in hashed by fwmark */
	e = rcu_dereference(hlist_next_rcu(&svc->f_list));
	अगर (e)
		वापस hlist_entry(e, काष्ठा ip_vs_service, f_list);

 scan_fwmark:
	जबतक (++iter->bucket < IP_VS_SVC_TAB_SIZE) अणु
		hlist_क्रम_each_entry_rcu(svc,
					 &ip_vs_svc_fwm_table[iter->bucket],
					 f_list)
			वापस svc;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ip_vs_info_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण


अटल पूर्णांक ip_vs_info_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq,
			"IP Virtual Server version %d.%d.%d (size=%d)\n",
			NVERSION(IP_VS_VERSION_CODE), ip_vs_conn_tab_size);
		seq_माला_दो(seq,
			 "Prot LocalAddress:Port Scheduler Flags\n");
		seq_माला_दो(seq,
			 "  -> RemoteAddress:Port Forward Weight ActiveConn InActConn\n");
	पूर्ण अन्यथा अणु
		काष्ठा net *net = seq_file_net(seq);
		काष्ठा netns_ipvs *ipvs = net_ipvs(net);
		स्थिर काष्ठा ip_vs_service *svc = v;
		स्थिर काष्ठा ip_vs_iter *iter = seq->निजी;
		स्थिर काष्ठा ip_vs_dest *dest;
		काष्ठा ip_vs_scheduler *sched = rcu_dereference(svc->scheduler);
		अक्षर *sched_name = sched ? sched->name : "none";

		अगर (svc->ipvs != ipvs)
			वापस 0;
		अगर (iter->table == ip_vs_svc_table) अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
			अगर (svc->af == AF_INET6)
				seq_म_लिखो(seq, "%s  [%pI6]:%04X %s ",
					   ip_vs_proto_name(svc->protocol),
					   &svc->addr.in6,
					   ntohs(svc->port),
					   sched_name);
			अन्यथा
#पूर्ण_अगर
				seq_म_लिखो(seq, "%s  %08X:%04X %s %s ",
					   ip_vs_proto_name(svc->protocol),
					   ntohl(svc->addr.ip),
					   ntohs(svc->port),
					   sched_name,
					   (svc->flags & IP_VS_SVC_F_ONEPACKET)?"ops ":"");
		पूर्ण अन्यथा अणु
			seq_म_लिखो(seq, "FWM  %08X %s %s",
				   svc->fwmark, sched_name,
				   (svc->flags & IP_VS_SVC_F_ONEPACKET)?"ops ":"");
		पूर्ण

		अगर (svc->flags & IP_VS_SVC_F_PERSISTENT)
			seq_म_लिखो(seq, "persistent %d %08X\n",
				svc->समयout,
				ntohl(svc->neपंचांगask));
		अन्यथा
			seq_अ_दो(seq, '\n');

		list_क्रम_each_entry_rcu(dest, &svc->destinations, n_list) अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
			अगर (dest->af == AF_INET6)
				seq_म_लिखो(seq,
					   "  -> [%pI6]:%04X"
					   "      %-7s %-6d %-10d %-10d\n",
					   &dest->addr.in6,
					   ntohs(dest->port),
					   ip_vs_fwd_name(atomic_पढ़ो(&dest->conn_flags)),
					   atomic_पढ़ो(&dest->weight),
					   atomic_पढ़ो(&dest->activeconns),
					   atomic_पढ़ो(&dest->inactconns));
			अन्यथा
#पूर्ण_अगर
				seq_म_लिखो(seq,
					   "  -> %08X:%04X      "
					   "%-7s %-6d %-10d %-10d\n",
					   ntohl(dest->addr.ip),
					   ntohs(dest->port),
					   ip_vs_fwd_name(atomic_पढ़ो(&dest->conn_flags)),
					   atomic_पढ़ो(&dest->weight),
					   atomic_पढ़ो(&dest->activeconns),
					   atomic_पढ़ो(&dest->inactconns));

		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ip_vs_info_seq_ops = अणु
	.start = ip_vs_info_seq_start,
	.next  = ip_vs_info_seq_next,
	.stop  = ip_vs_info_seq_stop,
	.show  = ip_vs_info_seq_show,
पूर्ण;

अटल पूर्णांक ip_vs_stats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net *net = seq_file_single_net(seq);
	काष्ठा ip_vs_kstats show;

/*               01234567 01234567 01234567 0123456701234567 0123456701234567 */
	seq_माला_दो(seq,
		 "   Total Incoming Outgoing         Incoming         Outgoing\n");
	seq_माला_दो(seq,
		 "   Conns  Packets  Packets            Bytes            Bytes\n");

	ip_vs_copy_stats(&show, &net_ipvs(net)->tot_stats);
	seq_म_लिखो(seq, "%8LX %8LX %8LX %16LX %16LX\n\n",
		   (अचिन्हित दीर्घ दीर्घ)show.conns,
		   (अचिन्हित दीर्घ दीर्घ)show.inpkts,
		   (अचिन्हित दीर्घ दीर्घ)show.outpkts,
		   (अचिन्हित दीर्घ दीर्घ)show.inbytes,
		   (अचिन्हित दीर्घ दीर्घ)show.outbytes);

/*                01234567 01234567 01234567 0123456701234567 0123456701234567*/
	seq_माला_दो(seq,
		 " Conns/s   Pkts/s   Pkts/s          Bytes/s          Bytes/s\n");
	seq_म_लिखो(seq, "%8LX %8LX %8LX %16LX %16LX\n",
		   (अचिन्हित दीर्घ दीर्घ)show.cps,
		   (अचिन्हित दीर्घ दीर्घ)show.inpps,
		   (अचिन्हित दीर्घ दीर्घ)show.outpps,
		   (अचिन्हित दीर्घ दीर्घ)show.inbps,
		   (अचिन्हित दीर्घ दीर्घ)show.outbps);

	वापस 0;
पूर्ण

अटल पूर्णांक ip_vs_stats_percpu_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net *net = seq_file_single_net(seq);
	काष्ठा ip_vs_stats *tot_stats = &net_ipvs(net)->tot_stats;
	काष्ठा ip_vs_cpu_stats __percpu *cpustats = tot_stats->cpustats;
	काष्ठा ip_vs_kstats kstats;
	पूर्णांक i;

/*               01234567 01234567 01234567 0123456701234567 0123456701234567 */
	seq_माला_दो(seq,
		 "       Total Incoming Outgoing         Incoming         Outgoing\n");
	seq_माला_दो(seq,
		 "CPU    Conns  Packets  Packets            Bytes            Bytes\n");

	क्रम_each_possible_cpu(i) अणु
		काष्ठा ip_vs_cpu_stats *u = per_cpu_ptr(cpustats, i);
		अचिन्हित पूर्णांक start;
		u64 conns, inpkts, outpkts, inbytes, outbytes;

		करो अणु
			start = u64_stats_fetch_begin_irq(&u->syncp);
			conns = u->cnt.conns;
			inpkts = u->cnt.inpkts;
			outpkts = u->cnt.outpkts;
			inbytes = u->cnt.inbytes;
			outbytes = u->cnt.outbytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&u->syncp, start));

		seq_म_लिखो(seq, "%3X %8LX %8LX %8LX %16LX %16LX\n",
			   i, (u64)conns, (u64)inpkts,
			   (u64)outpkts, (u64)inbytes,
			   (u64)outbytes);
	पूर्ण

	ip_vs_copy_stats(&kstats, tot_stats);

	seq_म_लिखो(seq, "  ~ %8LX %8LX %8LX %16LX %16LX\n\n",
		   (अचिन्हित दीर्घ दीर्घ)kstats.conns,
		   (अचिन्हित दीर्घ दीर्घ)kstats.inpkts,
		   (अचिन्हित दीर्घ दीर्घ)kstats.outpkts,
		   (अचिन्हित दीर्घ दीर्घ)kstats.inbytes,
		   (अचिन्हित दीर्घ दीर्घ)kstats.outbytes);

/*                ... 01234567 01234567 01234567 0123456701234567 0123456701234567 */
	seq_माला_दो(seq,
		 "     Conns/s   Pkts/s   Pkts/s          Bytes/s          Bytes/s\n");
	seq_म_लिखो(seq, "    %8LX %8LX %8LX %16LX %16LX\n",
		   kstats.cps,
		   kstats.inpps,
		   kstats.outpps,
		   kstats.inbps,
		   kstats.outbps);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 *	Set समयout values क्रम tcp tcpfin udp in the समयout_table.
 */
अटल पूर्णांक ip_vs_set_समयout(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_समयout_user *u)
अणु
#अगर defined(CONFIG_IP_VS_PROTO_TCP) || defined(CONFIG_IP_VS_PROTO_UDP)
	काष्ठा ip_vs_proto_data *pd;
#पूर्ण_अगर

	IP_VS_DBG(2, "Setting timeout tcp:%d tcpfin:%d udp:%d\n",
		  u->tcp_समयout,
		  u->tcp_fin_समयout,
		  u->udp_समयout);

#अगर_घोषित CONFIG_IP_VS_PROTO_TCP
	अगर (u->tcp_समयout < 0 || u->tcp_समयout > (पूर्णांक_उच्च / HZ) ||
	    u->tcp_fin_समयout < 0 || u->tcp_fin_समयout > (पूर्णांक_उच्च / HZ)) अणु
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_VS_PROTO_UDP
	अगर (u->udp_समयout < 0 || u->udp_समयout > (पूर्णांक_उच्च / HZ))
		वापस -EINVAL;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_VS_PROTO_TCP
	अगर (u->tcp_समयout) अणु
		pd = ip_vs_proto_data_get(ipvs, IPPROTO_TCP);
		pd->समयout_table[IP_VS_TCP_S_ESTABLISHED]
			= u->tcp_समयout * HZ;
	पूर्ण

	अगर (u->tcp_fin_समयout) अणु
		pd = ip_vs_proto_data_get(ipvs, IPPROTO_TCP);
		pd->समयout_table[IP_VS_TCP_S_FIN_WAIT]
			= u->tcp_fin_समयout * HZ;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_VS_PROTO_UDP
	अगर (u->udp_समयout) अणु
		pd = ip_vs_proto_data_get(ipvs, IPPROTO_UDP);
		pd->समयout_table[IP_VS_UDP_S_NORMAL]
			= u->udp_समयout * HZ;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

#घोषणा CMDID(cmd)		(cmd - IP_VS_BASE_CTL)

काष्ठा ip_vs_svcdest_user अणु
	काष्ठा ip_vs_service_user	s;
	काष्ठा ip_vs_dest_user		d;
पूर्ण;

अटल स्थिर अचिन्हित अक्षर set_arglen[CMDID(IP_VS_SO_SET_MAX) + 1] = अणु
	[CMDID(IP_VS_SO_SET_ADD)]         = माप(काष्ठा ip_vs_service_user),
	[CMDID(IP_VS_SO_SET_EDIT)]        = माप(काष्ठा ip_vs_service_user),
	[CMDID(IP_VS_SO_SET_DEL)]         = माप(काष्ठा ip_vs_service_user),
	[CMDID(IP_VS_SO_SET_ADDDEST)]     = माप(काष्ठा ip_vs_svcdest_user),
	[CMDID(IP_VS_SO_SET_DELDEST)]     = माप(काष्ठा ip_vs_svcdest_user),
	[CMDID(IP_VS_SO_SET_EDITDEST)]    = माप(काष्ठा ip_vs_svcdest_user),
	[CMDID(IP_VS_SO_SET_TIMEOUT)]     = माप(काष्ठा ip_vs_समयout_user),
	[CMDID(IP_VS_SO_SET_STARTDAEMON)] = माप(काष्ठा ip_vs_daemon_user),
	[CMDID(IP_VS_SO_SET_STOPDAEMON)]  = माप(काष्ठा ip_vs_daemon_user),
	[CMDID(IP_VS_SO_SET_ZERO)]        = माप(काष्ठा ip_vs_service_user),
पूर्ण;

जोड़ ip_vs_set_arglen अणु
	काष्ठा ip_vs_service_user	field_IP_VS_SO_SET_ADD;
	काष्ठा ip_vs_service_user	field_IP_VS_SO_SET_EDIT;
	काष्ठा ip_vs_service_user	field_IP_VS_SO_SET_DEL;
	काष्ठा ip_vs_svcdest_user	field_IP_VS_SO_SET_ADDDEST;
	काष्ठा ip_vs_svcdest_user	field_IP_VS_SO_SET_DELDEST;
	काष्ठा ip_vs_svcdest_user	field_IP_VS_SO_SET_EDITDEST;
	काष्ठा ip_vs_समयout_user	field_IP_VS_SO_SET_TIMEOUT;
	काष्ठा ip_vs_daemon_user	field_IP_VS_SO_SET_STARTDAEMON;
	काष्ठा ip_vs_daemon_user	field_IP_VS_SO_SET_STOPDAEMON;
	काष्ठा ip_vs_service_user	field_IP_VS_SO_SET_ZERO;
पूर्ण;

#घोषणा MAX_SET_ARGLEN	माप(जोड़ ip_vs_set_arglen)

अटल व्योम ip_vs_copy_usvc_compat(काष्ठा ip_vs_service_user_kern *usvc,
				  काष्ठा ip_vs_service_user *usvc_compat)
अणु
	स_रखो(usvc, 0, माप(*usvc));

	usvc->af		= AF_INET;
	usvc->protocol		= usvc_compat->protocol;
	usvc->addr.ip		= usvc_compat->addr;
	usvc->port		= usvc_compat->port;
	usvc->fwmark		= usvc_compat->fwmark;

	/* Deep copy of sched_name is not needed here */
	usvc->sched_name	= usvc_compat->sched_name;

	usvc->flags		= usvc_compat->flags;
	usvc->समयout		= usvc_compat->समयout;
	usvc->neपंचांगask		= usvc_compat->neपंचांगask;
पूर्ण

अटल व्योम ip_vs_copy_udest_compat(काष्ठा ip_vs_dest_user_kern *udest,
				   काष्ठा ip_vs_dest_user *udest_compat)
अणु
	स_रखो(udest, 0, माप(*udest));

	udest->addr.ip		= udest_compat->addr;
	udest->port		= udest_compat->port;
	udest->conn_flags	= udest_compat->conn_flags;
	udest->weight		= udest_compat->weight;
	udest->u_threshold	= udest_compat->u_threshold;
	udest->l_threshold	= udest_compat->l_threshold;
	udest->af		= AF_INET;
	udest->tun_type		= IP_VS_CONN_F_TUNNEL_TYPE_IPIP;
पूर्ण

अटल पूर्णांक
करो_ip_vs_set_ctl(काष्ठा sock *sk, पूर्णांक cmd, sockptr_t ptr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा net *net = sock_net(sk);
	पूर्णांक ret;
	अचिन्हित अक्षर arg[MAX_SET_ARGLEN];
	काष्ठा ip_vs_service_user *usvc_compat;
	काष्ठा ip_vs_service_user_kern usvc;
	काष्ठा ip_vs_service *svc;
	काष्ठा ip_vs_dest_user *udest_compat;
	काष्ठा ip_vs_dest_user_kern udest;
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	BUILD_BUG_ON(माप(arg) > 255);
	अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (cmd < IP_VS_BASE_CTL || cmd > IP_VS_SO_SET_MAX)
		वापस -EINVAL;
	अगर (len != set_arglen[CMDID(cmd)]) अणु
		IP_VS_DBG(1, "set_ctl: len %u != %u\n",
			  len, set_arglen[CMDID(cmd)]);
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_sockptr(arg, ptr, len) != 0)
		वापस -EFAULT;

	/* Handle daemons since they have another lock */
	अगर (cmd == IP_VS_SO_SET_STARTDAEMON ||
	    cmd == IP_VS_SO_SET_STOPDAEMON) अणु
		काष्ठा ip_vs_daemon_user *dm = (काष्ठा ip_vs_daemon_user *)arg;

		अगर (cmd == IP_VS_SO_SET_STARTDAEMON) अणु
			काष्ठा ipvs_sync_daemon_cfg cfg;

			स_रखो(&cfg, 0, माप(cfg));
			ret = -EINVAL;
			अगर (strscpy(cfg.mcast_अगरn, dm->mcast_अगरn,
				    माप(cfg.mcast_अगरn)) <= 0)
				वापस ret;
			cfg.syncid = dm->syncid;
			ret = start_sync_thपढ़ो(ipvs, &cfg, dm->state);
		पूर्ण अन्यथा अणु
			ret = stop_sync_thपढ़ो(ipvs, dm->state);
		पूर्ण
		वापस ret;
	पूर्ण

	mutex_lock(&__ip_vs_mutex);
	अगर (cmd == IP_VS_SO_SET_FLUSH) अणु
		/* Flush the भव service */
		ret = ip_vs_flush(ipvs, false);
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (cmd == IP_VS_SO_SET_TIMEOUT) अणु
		/* Set समयout values क्रम (tcp tcpfin udp) */
		ret = ip_vs_set_समयout(ipvs, (काष्ठा ip_vs_समयout_user *)arg);
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (!len) अणु
		/* No more commands with len == 0 below */
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	usvc_compat = (काष्ठा ip_vs_service_user *)arg;
	udest_compat = (काष्ठा ip_vs_dest_user *)(usvc_compat + 1);

	/* We only use the new काष्ठाs पूर्णांकernally, so copy userspace compat
	 * काष्ठाs to extended पूर्णांकernal versions */
	ip_vs_copy_usvc_compat(&usvc, usvc_compat);
	ip_vs_copy_udest_compat(&udest, udest_compat);

	अगर (cmd == IP_VS_SO_SET_ZERO) अणु
		/* अगर no service address is set, zero counters in all */
		अगर (!usvc.fwmark && !usvc.addr.ip && !usvc.port) अणु
			ret = ip_vs_zero_all(ipvs);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर ((cmd == IP_VS_SO_SET_ADD || cmd == IP_VS_SO_SET_EDIT) &&
	    strnlen(usvc.sched_name, IP_VS_SCHEDNAME_MAXLEN) ==
	    IP_VS_SCHEDNAME_MAXLEN) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* Check क्रम valid protocol: TCP or UDP or SCTP, even क्रम fwmark!=0 */
	अगर (usvc.protocol != IPPROTO_TCP && usvc.protocol != IPPROTO_UDP &&
	    usvc.protocol != IPPROTO_SCTP) अणु
		pr_err("set_ctl: invalid protocol: %d %pI4:%d\n",
		       usvc.protocol, &usvc.addr.ip,
		       ntohs(usvc.port));
		ret = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	/* Lookup the exact service by <protocol, addr, port> or fwmark */
	rcu_पढ़ो_lock();
	अगर (usvc.fwmark == 0)
		svc = __ip_vs_service_find(ipvs, usvc.af, usvc.protocol,
					   &usvc.addr, usvc.port);
	अन्यथा
		svc = __ip_vs_svc_fwm_find(ipvs, usvc.af, usvc.fwmark);
	rcu_पढ़ो_unlock();

	अगर (cmd != IP_VS_SO_SET_ADD
	    && (svc == शून्य || svc->protocol != usvc.protocol)) अणु
		ret = -ESRCH;
		जाओ out_unlock;
	पूर्ण

	चयन (cmd) अणु
	हाल IP_VS_SO_SET_ADD:
		अगर (svc != शून्य)
			ret = -EEXIST;
		अन्यथा
			ret = ip_vs_add_service(ipvs, &usvc, &svc);
		अवरोध;
	हाल IP_VS_SO_SET_EDIT:
		ret = ip_vs_edit_service(svc, &usvc);
		अवरोध;
	हाल IP_VS_SO_SET_DEL:
		ret = ip_vs_del_service(svc);
		अगर (!ret)
			जाओ out_unlock;
		अवरोध;
	हाल IP_VS_SO_SET_ZERO:
		ret = ip_vs_zero_service(svc);
		अवरोध;
	हाल IP_VS_SO_SET_ADDDEST:
		ret = ip_vs_add_dest(svc, &udest);
		अवरोध;
	हाल IP_VS_SO_SET_EDITDEST:
		ret = ip_vs_edit_dest(svc, &udest);
		अवरोध;
	हाल IP_VS_SO_SET_DELDEST:
		ret = ip_vs_del_dest(svc, &udest);
	पूर्ण

  out_unlock:
	mutex_unlock(&__ip_vs_mutex);
	वापस ret;
पूर्ण


अटल व्योम
ip_vs_copy_service(काष्ठा ip_vs_service_entry *dst, काष्ठा ip_vs_service *src)
अणु
	काष्ठा ip_vs_scheduler *sched;
	काष्ठा ip_vs_kstats kstats;
	अक्षर *sched_name;

	sched = rcu_dereference_रक्षित(src->scheduler, 1);
	sched_name = sched ? sched->name : "none";
	dst->protocol = src->protocol;
	dst->addr = src->addr.ip;
	dst->port = src->port;
	dst->fwmark = src->fwmark;
	strlcpy(dst->sched_name, sched_name, माप(dst->sched_name));
	dst->flags = src->flags;
	dst->समयout = src->समयout / HZ;
	dst->neपंचांगask = src->neपंचांगask;
	dst->num_dests = src->num_dests;
	ip_vs_copy_stats(&kstats, &src->stats);
	ip_vs_export_stats_user(&dst->stats, &kstats);
पूर्ण

अटल अंतरभूत पूर्णांक
__ip_vs_get_service_entries(काष्ठा netns_ipvs *ipvs,
			    स्थिर काष्ठा ip_vs_get_services *get,
			    काष्ठा ip_vs_get_services __user *uptr)
अणु
	पूर्णांक idx, count=0;
	काष्ठा ip_vs_service *svc;
	काष्ठा ip_vs_service_entry entry;
	पूर्णांक ret = 0;

	क्रम (idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		hlist_क्रम_each_entry(svc, &ip_vs_svc_table[idx], s_list) अणु
			/* Only expose IPv4 entries to old पूर्णांकerface */
			अगर (svc->af != AF_INET || (svc->ipvs != ipvs))
				जारी;

			अगर (count >= get->num_services)
				जाओ out;
			स_रखो(&entry, 0, माप(entry));
			ip_vs_copy_service(&entry, svc);
			अगर (copy_to_user(&uptr->entrytable[count],
					 &entry, माप(entry))) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
			count++;
		पूर्ण
	पूर्ण

	क्रम (idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		hlist_क्रम_each_entry(svc, &ip_vs_svc_fwm_table[idx], f_list) अणु
			/* Only expose IPv4 entries to old पूर्णांकerface */
			अगर (svc->af != AF_INET || (svc->ipvs != ipvs))
				जारी;

			अगर (count >= get->num_services)
				जाओ out;
			स_रखो(&entry, 0, माप(entry));
			ip_vs_copy_service(&entry, svc);
			अगर (copy_to_user(&uptr->entrytable[count],
					 &entry, माप(entry))) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
			count++;
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
__ip_vs_get_dest_entries(काष्ठा netns_ipvs *ipvs, स्थिर काष्ठा ip_vs_get_dests *get,
			 काष्ठा ip_vs_get_dests __user *uptr)
अणु
	काष्ठा ip_vs_service *svc;
	जोड़ nf_inet_addr addr = अणु .ip = get->addr पूर्ण;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	अगर (get->fwmark)
		svc = __ip_vs_svc_fwm_find(ipvs, AF_INET, get->fwmark);
	अन्यथा
		svc = __ip_vs_service_find(ipvs, AF_INET, get->protocol, &addr,
					   get->port);
	rcu_पढ़ो_unlock();

	अगर (svc) अणु
		पूर्णांक count = 0;
		काष्ठा ip_vs_dest *dest;
		काष्ठा ip_vs_dest_entry entry;
		काष्ठा ip_vs_kstats kstats;

		स_रखो(&entry, 0, माप(entry));
		list_क्रम_each_entry(dest, &svc->destinations, n_list) अणु
			अगर (count >= get->num_dests)
				अवरोध;

			/* Cannot expose heterogeneous members via sockopt
			 * पूर्णांकerface
			 */
			अगर (dest->af != svc->af)
				जारी;

			entry.addr = dest->addr.ip;
			entry.port = dest->port;
			entry.conn_flags = atomic_पढ़ो(&dest->conn_flags);
			entry.weight = atomic_पढ़ो(&dest->weight);
			entry.u_threshold = dest->u_threshold;
			entry.l_threshold = dest->l_threshold;
			entry.activeconns = atomic_पढ़ो(&dest->activeconns);
			entry.inactconns = atomic_पढ़ो(&dest->inactconns);
			entry.persistconns = atomic_पढ़ो(&dest->persistconns);
			ip_vs_copy_stats(&kstats, &dest->stats);
			ip_vs_export_stats_user(&entry.stats, &kstats);
			अगर (copy_to_user(&uptr->entrytable[count],
					 &entry, माप(entry))) अणु
				ret = -EFAULT;
				अवरोध;
			पूर्ण
			count++;
		पूर्ण
	पूर्ण अन्यथा
		ret = -ESRCH;
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
__ip_vs_get_समयouts(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_समयout_user *u)
अणु
#अगर defined(CONFIG_IP_VS_PROTO_TCP) || defined(CONFIG_IP_VS_PROTO_UDP)
	काष्ठा ip_vs_proto_data *pd;
#पूर्ण_अगर

	स_रखो(u, 0, माप (*u));

#अगर_घोषित CONFIG_IP_VS_PROTO_TCP
	pd = ip_vs_proto_data_get(ipvs, IPPROTO_TCP);
	u->tcp_समयout = pd->समयout_table[IP_VS_TCP_S_ESTABLISHED] / HZ;
	u->tcp_fin_समयout = pd->समयout_table[IP_VS_TCP_S_FIN_WAIT] / HZ;
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_UDP
	pd = ip_vs_proto_data_get(ipvs, IPPROTO_UDP);
	u->udp_समयout =
			pd->समयout_table[IP_VS_UDP_S_NORMAL] / HZ;
#पूर्ण_अगर
पूर्ण

अटल स्थिर अचिन्हित अक्षर get_arglen[CMDID(IP_VS_SO_GET_MAX) + 1] = अणु
	[CMDID(IP_VS_SO_GET_VERSION)]  = 64,
	[CMDID(IP_VS_SO_GET_INFO)]     = माप(काष्ठा ip_vs_getinfo),
	[CMDID(IP_VS_SO_GET_SERVICES)] = माप(काष्ठा ip_vs_get_services),
	[CMDID(IP_VS_SO_GET_SERVICE)]  = माप(काष्ठा ip_vs_service_entry),
	[CMDID(IP_VS_SO_GET_DESTS)]    = माप(काष्ठा ip_vs_get_dests),
	[CMDID(IP_VS_SO_GET_TIMEOUT)]  = माप(काष्ठा ip_vs_समयout_user),
	[CMDID(IP_VS_SO_GET_DAEMON)]   = 2 * माप(काष्ठा ip_vs_daemon_user),
पूर्ण;

जोड़ ip_vs_get_arglen अणु
	अक्षर				field_IP_VS_SO_GET_VERSION[64];
	काष्ठा ip_vs_getinfo		field_IP_VS_SO_GET_INFO;
	काष्ठा ip_vs_get_services	field_IP_VS_SO_GET_SERVICES;
	काष्ठा ip_vs_service_entry	field_IP_VS_SO_GET_SERVICE;
	काष्ठा ip_vs_get_dests		field_IP_VS_SO_GET_DESTS;
	काष्ठा ip_vs_समयout_user	field_IP_VS_SO_GET_TIMEOUT;
	काष्ठा ip_vs_daemon_user	field_IP_VS_SO_GET_DAEMON[2];
पूर्ण;

#घोषणा MAX_GET_ARGLEN	माप(जोड़ ip_vs_get_arglen)

अटल पूर्णांक
करो_ip_vs_get_ctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *user, पूर्णांक *len)
अणु
	अचिन्हित अक्षर arg[MAX_GET_ARGLEN];
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक copylen;
	काष्ठा net *net = sock_net(sk);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	BUG_ON(!net);
	BUILD_BUG_ON(माप(arg) > 255);
	अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (cmd < IP_VS_BASE_CTL || cmd > IP_VS_SO_GET_MAX)
		वापस -EINVAL;

	copylen = get_arglen[CMDID(cmd)];
	अगर (*len < (पूर्णांक) copylen) अणु
		IP_VS_DBG(1, "get_ctl: len %d < %u\n", *len, copylen);
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(arg, user, copylen) != 0)
		वापस -EFAULT;
	/*
	 * Handle daemons first since it has its own locking
	 */
	अगर (cmd == IP_VS_SO_GET_DAEMON) अणु
		काष्ठा ip_vs_daemon_user d[2];

		स_रखो(&d, 0, माप(d));
		mutex_lock(&ipvs->sync_mutex);
		अगर (ipvs->sync_state & IP_VS_STATE_MASTER) अणु
			d[0].state = IP_VS_STATE_MASTER;
			strlcpy(d[0].mcast_अगरn, ipvs->mcfg.mcast_अगरn,
				माप(d[0].mcast_अगरn));
			d[0].syncid = ipvs->mcfg.syncid;
		पूर्ण
		अगर (ipvs->sync_state & IP_VS_STATE_BACKUP) अणु
			d[1].state = IP_VS_STATE_BACKUP;
			strlcpy(d[1].mcast_अगरn, ipvs->bcfg.mcast_अगरn,
				माप(d[1].mcast_अगरn));
			d[1].syncid = ipvs->bcfg.syncid;
		पूर्ण
		अगर (copy_to_user(user, &d, माप(d)) != 0)
			ret = -EFAULT;
		mutex_unlock(&ipvs->sync_mutex);
		वापस ret;
	पूर्ण

	mutex_lock(&__ip_vs_mutex);
	चयन (cmd) अणु
	हाल IP_VS_SO_GET_VERSION:
	अणु
		अक्षर buf[64];

		प्र_लिखो(buf, "IP Virtual Server version %d.%d.%d (size=%d)",
			NVERSION(IP_VS_VERSION_CODE), ip_vs_conn_tab_size);
		अगर (copy_to_user(user, buf, म_माप(buf)+1) != 0) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		*len = म_माप(buf)+1;
	पूर्ण
	अवरोध;

	हाल IP_VS_SO_GET_INFO:
	अणु
		काष्ठा ip_vs_getinfo info;
		info.version = IP_VS_VERSION_CODE;
		info.size = ip_vs_conn_tab_size;
		info.num_services = ipvs->num_services;
		अगर (copy_to_user(user, &info, माप(info)) != 0)
			ret = -EFAULT;
	पूर्ण
	अवरोध;

	हाल IP_VS_SO_GET_SERVICES:
	अणु
		काष्ठा ip_vs_get_services *get;
		पूर्णांक size;

		get = (काष्ठा ip_vs_get_services *)arg;
		size = काष्ठा_size(get, entrytable, get->num_services);
		अगर (*len != size) अणु
			pr_err("length: %u != %u\n", *len, size);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ret = __ip_vs_get_service_entries(ipvs, get, user);
	पूर्ण
	अवरोध;

	हाल IP_VS_SO_GET_SERVICE:
	अणु
		काष्ठा ip_vs_service_entry *entry;
		काष्ठा ip_vs_service *svc;
		जोड़ nf_inet_addr addr;

		entry = (काष्ठा ip_vs_service_entry *)arg;
		addr.ip = entry->addr;
		rcu_पढ़ो_lock();
		अगर (entry->fwmark)
			svc = __ip_vs_svc_fwm_find(ipvs, AF_INET, entry->fwmark);
		अन्यथा
			svc = __ip_vs_service_find(ipvs, AF_INET,
						   entry->protocol, &addr,
						   entry->port);
		rcu_पढ़ो_unlock();
		अगर (svc) अणु
			ip_vs_copy_service(entry, svc);
			अगर (copy_to_user(user, entry, माप(*entry)) != 0)
				ret = -EFAULT;
		पूर्ण अन्यथा
			ret = -ESRCH;
	पूर्ण
	अवरोध;

	हाल IP_VS_SO_GET_DESTS:
	अणु
		काष्ठा ip_vs_get_dests *get;
		पूर्णांक size;

		get = (काष्ठा ip_vs_get_dests *)arg;
		size = काष्ठा_size(get, entrytable, get->num_dests);
		अगर (*len != size) अणु
			pr_err("length: %u != %u\n", *len, size);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ret = __ip_vs_get_dest_entries(ipvs, get, user);
	पूर्ण
	अवरोध;

	हाल IP_VS_SO_GET_TIMEOUT:
	अणु
		काष्ठा ip_vs_समयout_user t;

		__ip_vs_get_समयouts(ipvs, &t);
		अगर (copy_to_user(user, &t, माप(t)) != 0)
			ret = -EFAULT;
	पूर्ण
	अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

out:
	mutex_unlock(&__ip_vs_mutex);
	वापस ret;
पूर्ण


अटल काष्ठा nf_sockopt_ops ip_vs_sockopts = अणु
	.pf		= PF_INET,
	.set_opपंचांगin	= IP_VS_BASE_CTL,
	.set_opपंचांगax	= IP_VS_SO_SET_MAX+1,
	.set		= करो_ip_vs_set_ctl,
	.get_opपंचांगin	= IP_VS_BASE_CTL,
	.get_opपंचांगax	= IP_VS_SO_GET_MAX+1,
	.get		= करो_ip_vs_get_ctl,
	.owner		= THIS_MODULE,
पूर्ण;

/*
 * Generic Netlink पूर्णांकerface
 */

/* IPVS genetlink family */
अटल काष्ठा genl_family ip_vs_genl_family;

/* Policy used क्रम first-level command attributes */
अटल स्थिर काष्ठा nla_policy ip_vs_cmd_policy[IPVS_CMD_ATTR_MAX + 1] = अणु
	[IPVS_CMD_ATTR_SERVICE]		= अणु .type = NLA_NESTED पूर्ण,
	[IPVS_CMD_ATTR_DEST]		= अणु .type = NLA_NESTED पूर्ण,
	[IPVS_CMD_ATTR_DAEMON]		= अणु .type = NLA_NESTED पूर्ण,
	[IPVS_CMD_ATTR_TIMEOUT_TCP]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_CMD_ATTR_TIMEOUT_TCP_FIN]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_CMD_ATTR_TIMEOUT_UDP]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/* Policy used क्रम attributes in nested attribute IPVS_CMD_ATTR_DAEMON */
अटल स्थिर काष्ठा nla_policy ip_vs_daemon_policy[IPVS_DAEMON_ATTR_MAX + 1] = अणु
	[IPVS_DAEMON_ATTR_STATE]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DAEMON_ATTR_MCAST_IFN]	= अणु .type = NLA_NUL_STRING,
					    .len = IP_VS_IFNAME_MAXLEN - 1 पूर्ण,
	[IPVS_DAEMON_ATTR_SYNC_ID]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DAEMON_ATTR_SYNC_MAXLEN]	= अणु .type = NLA_U16 पूर्ण,
	[IPVS_DAEMON_ATTR_MCAST_GROUP]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DAEMON_ATTR_MCAST_GROUP6]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IPVS_DAEMON_ATTR_MCAST_PORT]	= अणु .type = NLA_U16 पूर्ण,
	[IPVS_DAEMON_ATTR_MCAST_TTL]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

/* Policy used क्रम attributes in nested attribute IPVS_CMD_ATTR_SERVICE */
अटल स्थिर काष्ठा nla_policy ip_vs_svc_policy[IPVS_SVC_ATTR_MAX + 1] = अणु
	[IPVS_SVC_ATTR_AF]		= अणु .type = NLA_U16 पूर्ण,
	[IPVS_SVC_ATTR_PROTOCOL]	= अणु .type = NLA_U16 पूर्ण,
	[IPVS_SVC_ATTR_ADDR]		= अणु .type = NLA_BINARY,
					    .len = माप(जोड़ nf_inet_addr) पूर्ण,
	[IPVS_SVC_ATTR_PORT]		= अणु .type = NLA_U16 पूर्ण,
	[IPVS_SVC_ATTR_FWMARK]		= अणु .type = NLA_U32 पूर्ण,
	[IPVS_SVC_ATTR_SCHED_NAME]	= अणु .type = NLA_NUL_STRING,
					    .len = IP_VS_SCHEDNAME_MAXLEN - 1 पूर्ण,
	[IPVS_SVC_ATTR_PE_NAME]		= अणु .type = NLA_NUL_STRING,
					    .len = IP_VS_PENAME_MAXLEN पूर्ण,
	[IPVS_SVC_ATTR_FLAGS]		= अणु .type = NLA_BINARY,
					    .len = माप(काष्ठा ip_vs_flags) पूर्ण,
	[IPVS_SVC_ATTR_TIMEOUT]		= अणु .type = NLA_U32 पूर्ण,
	[IPVS_SVC_ATTR_NETMASK]		= अणु .type = NLA_U32 पूर्ण,
	[IPVS_SVC_ATTR_STATS]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

/* Policy used क्रम attributes in nested attribute IPVS_CMD_ATTR_DEST */
अटल स्थिर काष्ठा nla_policy ip_vs_dest_policy[IPVS_DEST_ATTR_MAX + 1] = अणु
	[IPVS_DEST_ATTR_ADDR]		= अणु .type = NLA_BINARY,
					    .len = माप(जोड़ nf_inet_addr) पूर्ण,
	[IPVS_DEST_ATTR_PORT]		= अणु .type = NLA_U16 पूर्ण,
	[IPVS_DEST_ATTR_FWD_METHOD]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DEST_ATTR_WEIGHT]		= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DEST_ATTR_U_THRESH]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DEST_ATTR_L_THRESH]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DEST_ATTR_ACTIVE_CONNS]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DEST_ATTR_INACT_CONNS]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DEST_ATTR_PERSIST_CONNS]	= अणु .type = NLA_U32 पूर्ण,
	[IPVS_DEST_ATTR_STATS]		= अणु .type = NLA_NESTED पूर्ण,
	[IPVS_DEST_ATTR_ADDR_FAMILY]	= अणु .type = NLA_U16 पूर्ण,
	[IPVS_DEST_ATTR_TUN_TYPE]	= अणु .type = NLA_U8 पूर्ण,
	[IPVS_DEST_ATTR_TUN_PORT]	= अणु .type = NLA_U16 पूर्ण,
	[IPVS_DEST_ATTR_TUN_FLAGS]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक ip_vs_genl_fill_stats(काष्ठा sk_buff *skb, पूर्णांक container_type,
				 काष्ठा ip_vs_kstats *kstats)
अणु
	काष्ठा nlattr *nl_stats = nla_nest_start_noflag(skb, container_type);

	अगर (!nl_stats)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, IPVS_STATS_ATTR_CONNS, (u32)kstats->conns) ||
	    nla_put_u32(skb, IPVS_STATS_ATTR_INPKTS, (u32)kstats->inpkts) ||
	    nla_put_u32(skb, IPVS_STATS_ATTR_OUTPKTS, (u32)kstats->outpkts) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_INBYTES, kstats->inbytes,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_OUTBYTES, kstats->outbytes,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u32(skb, IPVS_STATS_ATTR_CPS, (u32)kstats->cps) ||
	    nla_put_u32(skb, IPVS_STATS_ATTR_INPPS, (u32)kstats->inpps) ||
	    nla_put_u32(skb, IPVS_STATS_ATTR_OUTPPS, (u32)kstats->outpps) ||
	    nla_put_u32(skb, IPVS_STATS_ATTR_INBPS, (u32)kstats->inbps) ||
	    nla_put_u32(skb, IPVS_STATS_ATTR_OUTBPS, (u32)kstats->outbps))
		जाओ nla_put_failure;
	nla_nest_end(skb, nl_stats);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nl_stats);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ip_vs_genl_fill_stats64(काष्ठा sk_buff *skb, पूर्णांक container_type,
				   काष्ठा ip_vs_kstats *kstats)
अणु
	काष्ठा nlattr *nl_stats = nla_nest_start_noflag(skb, container_type);

	अगर (!nl_stats)
		वापस -EMSGSIZE;

	अगर (nla_put_u64_64bit(skb, IPVS_STATS_ATTR_CONNS, kstats->conns,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_INPKTS, kstats->inpkts,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_OUTPKTS, kstats->outpkts,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_INBYTES, kstats->inbytes,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_OUTBYTES, kstats->outbytes,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_CPS, kstats->cps,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_INPPS, kstats->inpps,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_OUTPPS, kstats->outpps,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_INBPS, kstats->inbps,
			      IPVS_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, IPVS_STATS_ATTR_OUTBPS, kstats->outbps,
			      IPVS_STATS_ATTR_PAD))
		जाओ nla_put_failure;
	nla_nest_end(skb, nl_stats);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nl_stats);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ip_vs_genl_fill_service(काष्ठा sk_buff *skb,
				   काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_scheduler *sched;
	काष्ठा ip_vs_pe *pe;
	काष्ठा nlattr *nl_service;
	काष्ठा ip_vs_flags flags = अणु .flags = svc->flags,
				     .mask = ~0 पूर्ण;
	काष्ठा ip_vs_kstats kstats;
	अक्षर *sched_name;

	nl_service = nla_nest_start_noflag(skb, IPVS_CMD_ATTR_SERVICE);
	अगर (!nl_service)
		वापस -EMSGSIZE;

	अगर (nla_put_u16(skb, IPVS_SVC_ATTR_AF, svc->af))
		जाओ nla_put_failure;
	अगर (svc->fwmark) अणु
		अगर (nla_put_u32(skb, IPVS_SVC_ATTR_FWMARK, svc->fwmark))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
		अगर (nla_put_u16(skb, IPVS_SVC_ATTR_PROTOCOL, svc->protocol) ||
		    nla_put(skb, IPVS_SVC_ATTR_ADDR, माप(svc->addr), &svc->addr) ||
		    nla_put_be16(skb, IPVS_SVC_ATTR_PORT, svc->port))
			जाओ nla_put_failure;
	पूर्ण

	sched = rcu_dereference_रक्षित(svc->scheduler, 1);
	sched_name = sched ? sched->name : "none";
	pe = rcu_dereference_रक्षित(svc->pe, 1);
	अगर (nla_put_string(skb, IPVS_SVC_ATTR_SCHED_NAME, sched_name) ||
	    (pe && nla_put_string(skb, IPVS_SVC_ATTR_PE_NAME, pe->name)) ||
	    nla_put(skb, IPVS_SVC_ATTR_FLAGS, माप(flags), &flags) ||
	    nla_put_u32(skb, IPVS_SVC_ATTR_TIMEOUT, svc->समयout / HZ) ||
	    nla_put_be32(skb, IPVS_SVC_ATTR_NETMASK, svc->neपंचांगask))
		जाओ nla_put_failure;
	ip_vs_copy_stats(&kstats, &svc->stats);
	अगर (ip_vs_genl_fill_stats(skb, IPVS_SVC_ATTR_STATS, &kstats))
		जाओ nla_put_failure;
	अगर (ip_vs_genl_fill_stats64(skb, IPVS_SVC_ATTR_STATS64, &kstats))
		जाओ nla_put_failure;

	nla_nest_end(skb, nl_service);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nl_service);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ip_vs_genl_dump_service(काष्ठा sk_buff *skb,
				   काष्ठा ip_vs_service *svc,
				   काष्ठा netlink_callback *cb)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &ip_vs_genl_family, NLM_F_MULTI,
			  IPVS_CMD_NEW_SERVICE);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (ip_vs_genl_fill_service(skb, svc) < 0)
		जाओ nla_put_failure;

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ip_vs_genl_dump_services(काष्ठा sk_buff *skb,
				    काष्ठा netlink_callback *cb)
अणु
	पूर्णांक idx = 0, i;
	पूर्णांक start = cb->args[0];
	काष्ठा ip_vs_service *svc;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	mutex_lock(&__ip_vs_mutex);
	क्रम (i = 0; i < IP_VS_SVC_TAB_SIZE; i++) अणु
		hlist_क्रम_each_entry(svc, &ip_vs_svc_table[i], s_list) अणु
			अगर (++idx <= start || (svc->ipvs != ipvs))
				जारी;
			अगर (ip_vs_genl_dump_service(skb, svc, cb) < 0) अणु
				idx--;
				जाओ nla_put_failure;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < IP_VS_SVC_TAB_SIZE; i++) अणु
		hlist_क्रम_each_entry(svc, &ip_vs_svc_fwm_table[i], f_list) अणु
			अगर (++idx <= start || (svc->ipvs != ipvs))
				जारी;
			अगर (ip_vs_genl_dump_service(skb, svc, cb) < 0) अणु
				idx--;
				जाओ nla_put_failure;
			पूर्ण
		पूर्ण
	पूर्ण

nla_put_failure:
	mutex_unlock(&__ip_vs_mutex);
	cb->args[0] = idx;

	वापस skb->len;
पूर्ण

अटल bool ip_vs_is_af_valid(पूर्णांक af)
अणु
	अगर (af == AF_INET)
		वापस true;
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6 && ipv6_mod_enabled())
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल पूर्णांक ip_vs_genl_parse_service(काष्ठा netns_ipvs *ipvs,
				    काष्ठा ip_vs_service_user_kern *usvc,
				    काष्ठा nlattr *nla, bool full_entry,
				    काष्ठा ip_vs_service **ret_svc)
अणु
	काष्ठा nlattr *attrs[IPVS_SVC_ATTR_MAX + 1];
	काष्ठा nlattr *nla_af, *nla_port, *nla_fwmark, *nla_protocol, *nla_addr;
	काष्ठा ip_vs_service *svc;

	/* Parse mandatory identअगरying service fields first */
	अगर (nla == शून्य ||
	    nla_parse_nested_deprecated(attrs, IPVS_SVC_ATTR_MAX, nla, ip_vs_svc_policy, शून्य))
		वापस -EINVAL;

	nla_af		= attrs[IPVS_SVC_ATTR_AF];
	nla_protocol	= attrs[IPVS_SVC_ATTR_PROTOCOL];
	nla_addr	= attrs[IPVS_SVC_ATTR_ADDR];
	nla_port	= attrs[IPVS_SVC_ATTR_PORT];
	nla_fwmark	= attrs[IPVS_SVC_ATTR_FWMARK];

	अगर (!(nla_af && (nla_fwmark || (nla_port && nla_protocol && nla_addr))))
		वापस -EINVAL;

	स_रखो(usvc, 0, माप(*usvc));

	usvc->af = nla_get_u16(nla_af);
	अगर (!ip_vs_is_af_valid(usvc->af))
		वापस -EAFNOSUPPORT;

	अगर (nla_fwmark) अणु
		usvc->protocol = IPPROTO_TCP;
		usvc->fwmark = nla_get_u32(nla_fwmark);
	पूर्ण अन्यथा अणु
		usvc->protocol = nla_get_u16(nla_protocol);
		nla_स_नकल(&usvc->addr, nla_addr, माप(usvc->addr));
		usvc->port = nla_get_be16(nla_port);
		usvc->fwmark = 0;
	पूर्ण

	rcu_पढ़ो_lock();
	अगर (usvc->fwmark)
		svc = __ip_vs_svc_fwm_find(ipvs, usvc->af, usvc->fwmark);
	अन्यथा
		svc = __ip_vs_service_find(ipvs, usvc->af, usvc->protocol,
					   &usvc->addr, usvc->port);
	rcu_पढ़ो_unlock();
	*ret_svc = svc;

	/* If a full entry was requested, check क्रम the additional fields */
	अगर (full_entry) अणु
		काष्ठा nlattr *nla_sched, *nla_flags, *nla_pe, *nla_समयout,
			      *nla_neपंचांगask;
		काष्ठा ip_vs_flags flags;

		nla_sched = attrs[IPVS_SVC_ATTR_SCHED_NAME];
		nla_pe = attrs[IPVS_SVC_ATTR_PE_NAME];
		nla_flags = attrs[IPVS_SVC_ATTR_FLAGS];
		nla_समयout = attrs[IPVS_SVC_ATTR_TIMEOUT];
		nla_neपंचांगask = attrs[IPVS_SVC_ATTR_NETMASK];

		अगर (!(nla_sched && nla_flags && nla_समयout && nla_neपंचांगask))
			वापस -EINVAL;

		nla_स_नकल(&flags, nla_flags, माप(flags));

		/* prefill flags from service अगर it alपढ़ोy exists */
		अगर (svc)
			usvc->flags = svc->flags;

		/* set new flags from userland */
		usvc->flags = (usvc->flags & ~flags.mask) |
			      (flags.flags & flags.mask);
		usvc->sched_name = nla_data(nla_sched);
		usvc->pe_name = nla_pe ? nla_data(nla_pe) : शून्य;
		usvc->समयout = nla_get_u32(nla_समयout);
		usvc->neपंचांगask = nla_get_be32(nla_neपंचांगask);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ip_vs_service *ip_vs_genl_find_service(काष्ठा netns_ipvs *ipvs,
						     काष्ठा nlattr *nla)
अणु
	काष्ठा ip_vs_service_user_kern usvc;
	काष्ठा ip_vs_service *svc;
	पूर्णांक ret;

	ret = ip_vs_genl_parse_service(ipvs, &usvc, nla, false, &svc);
	वापस ret ? ERR_PTR(ret) : svc;
पूर्ण

अटल पूर्णांक ip_vs_genl_fill_dest(काष्ठा sk_buff *skb, काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा nlattr *nl_dest;
	काष्ठा ip_vs_kstats kstats;

	nl_dest = nla_nest_start_noflag(skb, IPVS_CMD_ATTR_DEST);
	अगर (!nl_dest)
		वापस -EMSGSIZE;

	अगर (nla_put(skb, IPVS_DEST_ATTR_ADDR, माप(dest->addr), &dest->addr) ||
	    nla_put_be16(skb, IPVS_DEST_ATTR_PORT, dest->port) ||
	    nla_put_u32(skb, IPVS_DEST_ATTR_FWD_METHOD,
			(atomic_पढ़ो(&dest->conn_flags) &
			 IP_VS_CONN_F_FWD_MASK)) ||
	    nla_put_u32(skb, IPVS_DEST_ATTR_WEIGHT,
			atomic_पढ़ो(&dest->weight)) ||
	    nla_put_u8(skb, IPVS_DEST_ATTR_TUN_TYPE,
		       dest->tun_type) ||
	    nla_put_be16(skb, IPVS_DEST_ATTR_TUN_PORT,
			 dest->tun_port) ||
	    nla_put_u16(skb, IPVS_DEST_ATTR_TUN_FLAGS,
			dest->tun_flags) ||
	    nla_put_u32(skb, IPVS_DEST_ATTR_U_THRESH, dest->u_threshold) ||
	    nla_put_u32(skb, IPVS_DEST_ATTR_L_THRESH, dest->l_threshold) ||
	    nla_put_u32(skb, IPVS_DEST_ATTR_ACTIVE_CONNS,
			atomic_पढ़ो(&dest->activeconns)) ||
	    nla_put_u32(skb, IPVS_DEST_ATTR_INACT_CONNS,
			atomic_पढ़ो(&dest->inactconns)) ||
	    nla_put_u32(skb, IPVS_DEST_ATTR_PERSIST_CONNS,
			atomic_पढ़ो(&dest->persistconns)) ||
	    nla_put_u16(skb, IPVS_DEST_ATTR_ADDR_FAMILY, dest->af))
		जाओ nla_put_failure;
	ip_vs_copy_stats(&kstats, &dest->stats);
	अगर (ip_vs_genl_fill_stats(skb, IPVS_DEST_ATTR_STATS, &kstats))
		जाओ nla_put_failure;
	अगर (ip_vs_genl_fill_stats64(skb, IPVS_DEST_ATTR_STATS64, &kstats))
		जाओ nla_put_failure;

	nla_nest_end(skb, nl_dest);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nl_dest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ip_vs_genl_dump_dest(काष्ठा sk_buff *skb, काष्ठा ip_vs_dest *dest,
				काष्ठा netlink_callback *cb)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &ip_vs_genl_family, NLM_F_MULTI,
			  IPVS_CMD_NEW_DEST);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (ip_vs_genl_fill_dest(skb, dest) < 0)
		जाओ nla_put_failure;

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ip_vs_genl_dump_dests(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	पूर्णांक idx = 0;
	पूर्णांक start = cb->args[0];
	काष्ठा ip_vs_service *svc;
	काष्ठा ip_vs_dest *dest;
	काष्ठा nlattr *attrs[IPVS_CMD_ATTR_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	mutex_lock(&__ip_vs_mutex);

	/* Try to find the service क्रम which to dump destinations */
	अगर (nlmsg_parse_deprecated(cb->nlh, GENL_HDRLEN, attrs, IPVS_CMD_ATTR_MAX, ip_vs_cmd_policy, cb->extack))
		जाओ out_err;


	svc = ip_vs_genl_find_service(ipvs, attrs[IPVS_CMD_ATTR_SERVICE]);
	अगर (IS_ERR_OR_शून्य(svc))
		जाओ out_err;

	/* Dump the destinations */
	list_क्रम_each_entry(dest, &svc->destinations, n_list) अणु
		अगर (++idx <= start)
			जारी;
		अगर (ip_vs_genl_dump_dest(skb, dest, cb) < 0) अणु
			idx--;
			जाओ nla_put_failure;
		पूर्ण
	पूर्ण

nla_put_failure:
	cb->args[0] = idx;

out_err:
	mutex_unlock(&__ip_vs_mutex);

	वापस skb->len;
पूर्ण

अटल पूर्णांक ip_vs_genl_parse_dest(काष्ठा ip_vs_dest_user_kern *udest,
				 काष्ठा nlattr *nla, bool full_entry)
अणु
	काष्ठा nlattr *attrs[IPVS_DEST_ATTR_MAX + 1];
	काष्ठा nlattr *nla_addr, *nla_port;
	काष्ठा nlattr *nla_addr_family;

	/* Parse mandatory identअगरying destination fields first */
	अगर (nla == शून्य ||
	    nla_parse_nested_deprecated(attrs, IPVS_DEST_ATTR_MAX, nla, ip_vs_dest_policy, शून्य))
		वापस -EINVAL;

	nla_addr	= attrs[IPVS_DEST_ATTR_ADDR];
	nla_port	= attrs[IPVS_DEST_ATTR_PORT];
	nla_addr_family	= attrs[IPVS_DEST_ATTR_ADDR_FAMILY];

	अगर (!(nla_addr && nla_port))
		वापस -EINVAL;

	स_रखो(udest, 0, माप(*udest));

	nla_स_नकल(&udest->addr, nla_addr, माप(udest->addr));
	udest->port = nla_get_be16(nla_port);

	अगर (nla_addr_family)
		udest->af = nla_get_u16(nla_addr_family);
	अन्यथा
		udest->af = 0;

	/* If a full entry was requested, check क्रम the additional fields */
	अगर (full_entry) अणु
		काष्ठा nlattr *nla_fwd, *nla_weight, *nla_u_thresh,
			      *nla_l_thresh, *nla_tun_type, *nla_tun_port,
			      *nla_tun_flags;

		nla_fwd		= attrs[IPVS_DEST_ATTR_FWD_METHOD];
		nla_weight	= attrs[IPVS_DEST_ATTR_WEIGHT];
		nla_u_thresh	= attrs[IPVS_DEST_ATTR_U_THRESH];
		nla_l_thresh	= attrs[IPVS_DEST_ATTR_L_THRESH];
		nla_tun_type	= attrs[IPVS_DEST_ATTR_TUN_TYPE];
		nla_tun_port	= attrs[IPVS_DEST_ATTR_TUN_PORT];
		nla_tun_flags	= attrs[IPVS_DEST_ATTR_TUN_FLAGS];

		अगर (!(nla_fwd && nla_weight && nla_u_thresh && nla_l_thresh))
			वापस -EINVAL;

		udest->conn_flags = nla_get_u32(nla_fwd)
				    & IP_VS_CONN_F_FWD_MASK;
		udest->weight = nla_get_u32(nla_weight);
		udest->u_threshold = nla_get_u32(nla_u_thresh);
		udest->l_threshold = nla_get_u32(nla_l_thresh);

		अगर (nla_tun_type)
			udest->tun_type = nla_get_u8(nla_tun_type);

		अगर (nla_tun_port)
			udest->tun_port = nla_get_be16(nla_tun_port);

		अगर (nla_tun_flags)
			udest->tun_flags = nla_get_u16(nla_tun_flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ip_vs_genl_fill_daemon(काष्ठा sk_buff *skb, __u32 state,
				  काष्ठा ipvs_sync_daemon_cfg *c)
अणु
	काष्ठा nlattr *nl_daemon;

	nl_daemon = nla_nest_start_noflag(skb, IPVS_CMD_ATTR_DAEMON);
	अगर (!nl_daemon)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, IPVS_DAEMON_ATTR_STATE, state) ||
	    nla_put_string(skb, IPVS_DAEMON_ATTR_MCAST_IFN, c->mcast_अगरn) ||
	    nla_put_u32(skb, IPVS_DAEMON_ATTR_SYNC_ID, c->syncid) ||
	    nla_put_u16(skb, IPVS_DAEMON_ATTR_SYNC_MAXLEN, c->sync_maxlen) ||
	    nla_put_u16(skb, IPVS_DAEMON_ATTR_MCAST_PORT, c->mcast_port) ||
	    nla_put_u8(skb, IPVS_DAEMON_ATTR_MCAST_TTL, c->mcast_ttl))
		जाओ nla_put_failure;
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (c->mcast_af == AF_INET6) अणु
		अगर (nla_put_in6_addr(skb, IPVS_DAEMON_ATTR_MCAST_GROUP6,
				     &c->mcast_group.in6))
			जाओ nla_put_failure;
	पूर्ण अन्यथा
#पूर्ण_अगर
		अगर (c->mcast_af == AF_INET &&
		    nla_put_in_addr(skb, IPVS_DAEMON_ATTR_MCAST_GROUP,
				    c->mcast_group.ip))
			जाओ nla_put_failure;
	nla_nest_end(skb, nl_daemon);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nl_daemon);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ip_vs_genl_dump_daemon(काष्ठा sk_buff *skb, __u32 state,
				  काष्ठा ipvs_sync_daemon_cfg *c,
				  काष्ठा netlink_callback *cb)
अणु
	व्योम *hdr;
	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &ip_vs_genl_family, NLM_F_MULTI,
			  IPVS_CMD_NEW_DAEMON);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (ip_vs_genl_fill_daemon(skb, state, c))
		जाओ nla_put_failure;

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ip_vs_genl_dump_daemons(काष्ठा sk_buff *skb,
				   काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	mutex_lock(&ipvs->sync_mutex);
	अगर ((ipvs->sync_state & IP_VS_STATE_MASTER) && !cb->args[0]) अणु
		अगर (ip_vs_genl_dump_daemon(skb, IP_VS_STATE_MASTER,
					   &ipvs->mcfg, cb) < 0)
			जाओ nla_put_failure;

		cb->args[0] = 1;
	पूर्ण

	अगर ((ipvs->sync_state & IP_VS_STATE_BACKUP) && !cb->args[1]) अणु
		अगर (ip_vs_genl_dump_daemon(skb, IP_VS_STATE_BACKUP,
					   &ipvs->bcfg, cb) < 0)
			जाओ nla_put_failure;

		cb->args[1] = 1;
	पूर्ण

nla_put_failure:
	mutex_unlock(&ipvs->sync_mutex);

	वापस skb->len;
पूर्ण

अटल पूर्णांक ip_vs_genl_new_daemon(काष्ठा netns_ipvs *ipvs, काष्ठा nlattr **attrs)
अणु
	काष्ठा ipvs_sync_daemon_cfg c;
	काष्ठा nlattr *a;
	पूर्णांक ret;

	स_रखो(&c, 0, माप(c));
	अगर (!(attrs[IPVS_DAEMON_ATTR_STATE] &&
	      attrs[IPVS_DAEMON_ATTR_MCAST_IFN] &&
	      attrs[IPVS_DAEMON_ATTR_SYNC_ID]))
		वापस -EINVAL;
	strlcpy(c.mcast_अगरn, nla_data(attrs[IPVS_DAEMON_ATTR_MCAST_IFN]),
		माप(c.mcast_अगरn));
	c.syncid = nla_get_u32(attrs[IPVS_DAEMON_ATTR_SYNC_ID]);

	a = attrs[IPVS_DAEMON_ATTR_SYNC_MAXLEN];
	अगर (a)
		c.sync_maxlen = nla_get_u16(a);

	a = attrs[IPVS_DAEMON_ATTR_MCAST_GROUP];
	अगर (a) अणु
		c.mcast_af = AF_INET;
		c.mcast_group.ip = nla_get_in_addr(a);
		अगर (!ipv4_is_multicast(c.mcast_group.ip))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		a = attrs[IPVS_DAEMON_ATTR_MCAST_GROUP6];
		अगर (a) अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
			पूर्णांक addr_type;

			c.mcast_af = AF_INET6;
			c.mcast_group.in6 = nla_get_in6_addr(a);
			addr_type = ipv6_addr_type(&c.mcast_group.in6);
			अगर (!(addr_type & IPV6_ADDR_MULTICAST))
				वापस -EINVAL;
#अन्यथा
			वापस -EAFNOSUPPORT;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	a = attrs[IPVS_DAEMON_ATTR_MCAST_PORT];
	अगर (a)
		c.mcast_port = nla_get_u16(a);

	a = attrs[IPVS_DAEMON_ATTR_MCAST_TTL];
	अगर (a)
		c.mcast_ttl = nla_get_u8(a);

	/* The synchronization protocol is incompatible with mixed family
	 * services
	 */
	अगर (ipvs->mixed_address_family_dests > 0)
		वापस -EINVAL;

	ret = start_sync_thपढ़ो(ipvs, &c,
				nla_get_u32(attrs[IPVS_DAEMON_ATTR_STATE]));
	वापस ret;
पूर्ण

अटल पूर्णांक ip_vs_genl_del_daemon(काष्ठा netns_ipvs *ipvs, काष्ठा nlattr **attrs)
अणु
	पूर्णांक ret;

	अगर (!attrs[IPVS_DAEMON_ATTR_STATE])
		वापस -EINVAL;

	ret = stop_sync_thपढ़ो(ipvs,
			       nla_get_u32(attrs[IPVS_DAEMON_ATTR_STATE]));
	वापस ret;
पूर्ण

अटल पूर्णांक ip_vs_genl_set_config(काष्ठा netns_ipvs *ipvs, काष्ठा nlattr **attrs)
अणु
	काष्ठा ip_vs_समयout_user t;

	__ip_vs_get_समयouts(ipvs, &t);

	अगर (attrs[IPVS_CMD_ATTR_TIMEOUT_TCP])
		t.tcp_समयout = nla_get_u32(attrs[IPVS_CMD_ATTR_TIMEOUT_TCP]);

	अगर (attrs[IPVS_CMD_ATTR_TIMEOUT_TCP_FIN])
		t.tcp_fin_समयout =
			nla_get_u32(attrs[IPVS_CMD_ATTR_TIMEOUT_TCP_FIN]);

	अगर (attrs[IPVS_CMD_ATTR_TIMEOUT_UDP])
		t.udp_समयout = nla_get_u32(attrs[IPVS_CMD_ATTR_TIMEOUT_UDP]);

	वापस ip_vs_set_समयout(ipvs, &t);
पूर्ण

अटल पूर्णांक ip_vs_genl_set_daemon(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret = -EINVAL, cmd;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	cmd = info->genlhdr->cmd;

	अगर (cmd == IPVS_CMD_NEW_DAEMON || cmd == IPVS_CMD_DEL_DAEMON) अणु
		काष्ठा nlattr *daemon_attrs[IPVS_DAEMON_ATTR_MAX + 1];

		अगर (!info->attrs[IPVS_CMD_ATTR_DAEMON] ||
		    nla_parse_nested_deprecated(daemon_attrs, IPVS_DAEMON_ATTR_MAX, info->attrs[IPVS_CMD_ATTR_DAEMON], ip_vs_daemon_policy, info->extack))
			जाओ out;

		अगर (cmd == IPVS_CMD_NEW_DAEMON)
			ret = ip_vs_genl_new_daemon(ipvs, daemon_attrs);
		अन्यथा
			ret = ip_vs_genl_del_daemon(ipvs, daemon_attrs);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ip_vs_genl_set_cmd(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	bool need_full_svc = false, need_full_dest = false;
	काष्ठा ip_vs_service *svc = शून्य;
	काष्ठा ip_vs_service_user_kern usvc;
	काष्ठा ip_vs_dest_user_kern udest;
	पूर्णांक ret = 0, cmd;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	cmd = info->genlhdr->cmd;

	mutex_lock(&__ip_vs_mutex);

	अगर (cmd == IPVS_CMD_FLUSH) अणु
		ret = ip_vs_flush(ipvs, false);
		जाओ out;
	पूर्ण अन्यथा अगर (cmd == IPVS_CMD_SET_CONFIG) अणु
		ret = ip_vs_genl_set_config(ipvs, info->attrs);
		जाओ out;
	पूर्ण अन्यथा अगर (cmd == IPVS_CMD_ZERO &&
		   !info->attrs[IPVS_CMD_ATTR_SERVICE]) अणु
		ret = ip_vs_zero_all(ipvs);
		जाओ out;
	पूर्ण

	/* All following commands require a service argument, so check अगर we
	 * received a valid one. We need a full service specअगरication when
	 * adding / editing a service. Only identअगरying members otherwise. */
	अगर (cmd == IPVS_CMD_NEW_SERVICE || cmd == IPVS_CMD_SET_SERVICE)
		need_full_svc = true;

	ret = ip_vs_genl_parse_service(ipvs, &usvc,
				       info->attrs[IPVS_CMD_ATTR_SERVICE],
				       need_full_svc, &svc);
	अगर (ret)
		जाओ out;

	/* Unless we're adding a new service, the service must alपढ़ोy exist */
	अगर ((cmd != IPVS_CMD_NEW_SERVICE) && (svc == शून्य)) अणु
		ret = -ESRCH;
		जाओ out;
	पूर्ण

	/* Destination commands require a valid destination argument. For
	 * adding / editing a destination, we need a full destination
	 * specअगरication. */
	अगर (cmd == IPVS_CMD_NEW_DEST || cmd == IPVS_CMD_SET_DEST ||
	    cmd == IPVS_CMD_DEL_DEST) अणु
		अगर (cmd != IPVS_CMD_DEL_DEST)
			need_full_dest = true;

		ret = ip_vs_genl_parse_dest(&udest,
					    info->attrs[IPVS_CMD_ATTR_DEST],
					    need_full_dest);
		अगर (ret)
			जाओ out;

		/* Old protocols did not allow the user to specअगरy address
		 * family, so we set it to zero instead.  We also didn't
		 * allow heterogeneous pools in the old code, so it's safe
		 * to assume that this will have the same address family as
		 * the service.
		 */
		अगर (udest.af == 0)
			udest.af = svc->af;

		अगर (!ip_vs_is_af_valid(udest.af)) अणु
			ret = -EAFNOSUPPORT;
			जाओ out;
		पूर्ण

		अगर (udest.af != svc->af && cmd != IPVS_CMD_DEL_DEST) अणु
			/* The synchronization protocol is incompatible
			 * with mixed family services
			 */
			अगर (ipvs->sync_state) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			/* Which connection types करो we support? */
			चयन (udest.conn_flags) अणु
			हाल IP_VS_CONN_F_TUNNEL:
				/* We are able to क्रमward this */
				अवरोध;
			शेष:
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (cmd) अणु
	हाल IPVS_CMD_NEW_SERVICE:
		अगर (svc == शून्य)
			ret = ip_vs_add_service(ipvs, &usvc, &svc);
		अन्यथा
			ret = -EEXIST;
		अवरोध;
	हाल IPVS_CMD_SET_SERVICE:
		ret = ip_vs_edit_service(svc, &usvc);
		अवरोध;
	हाल IPVS_CMD_DEL_SERVICE:
		ret = ip_vs_del_service(svc);
		/* करो not use svc, it can be मुक्तd */
		अवरोध;
	हाल IPVS_CMD_NEW_DEST:
		ret = ip_vs_add_dest(svc, &udest);
		अवरोध;
	हाल IPVS_CMD_SET_DEST:
		ret = ip_vs_edit_dest(svc, &udest);
		अवरोध;
	हाल IPVS_CMD_DEL_DEST:
		ret = ip_vs_del_dest(svc, &udest);
		अवरोध;
	हाल IPVS_CMD_ZERO:
		ret = ip_vs_zero_service(svc);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

out:
	mutex_unlock(&__ip_vs_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ip_vs_genl_get_cmd(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	व्योम *reply;
	पूर्णांक ret, cmd, reply_cmd;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	cmd = info->genlhdr->cmd;

	अगर (cmd == IPVS_CMD_GET_SERVICE)
		reply_cmd = IPVS_CMD_NEW_SERVICE;
	अन्यथा अगर (cmd == IPVS_CMD_GET_INFO)
		reply_cmd = IPVS_CMD_SET_INFO;
	अन्यथा अगर (cmd == IPVS_CMD_GET_CONFIG)
		reply_cmd = IPVS_CMD_SET_CONFIG;
	अन्यथा अणु
		pr_err("unknown Generic Netlink command\n");
		वापस -EINVAL;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	mutex_lock(&__ip_vs_mutex);

	reply = genlmsg_put_reply(msg, info, &ip_vs_genl_family, 0, reply_cmd);
	अगर (reply == शून्य)
		जाओ nla_put_failure;

	चयन (cmd) अणु
	हाल IPVS_CMD_GET_SERVICE:
	अणु
		काष्ठा ip_vs_service *svc;

		svc = ip_vs_genl_find_service(ipvs,
					      info->attrs[IPVS_CMD_ATTR_SERVICE]);
		अगर (IS_ERR(svc)) अणु
			ret = PTR_ERR(svc);
			जाओ out_err;
		पूर्ण अन्यथा अगर (svc) अणु
			ret = ip_vs_genl_fill_service(msg, svc);
			अगर (ret)
				जाओ nla_put_failure;
		पूर्ण अन्यथा अणु
			ret = -ESRCH;
			जाओ out_err;
		पूर्ण

		अवरोध;
	पूर्ण

	हाल IPVS_CMD_GET_CONFIG:
	अणु
		काष्ठा ip_vs_समयout_user t;

		__ip_vs_get_समयouts(ipvs, &t);
#अगर_घोषित CONFIG_IP_VS_PROTO_TCP
		अगर (nla_put_u32(msg, IPVS_CMD_ATTR_TIMEOUT_TCP,
				t.tcp_समयout) ||
		    nla_put_u32(msg, IPVS_CMD_ATTR_TIMEOUT_TCP_FIN,
				t.tcp_fin_समयout))
			जाओ nla_put_failure;
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_UDP
		अगर (nla_put_u32(msg, IPVS_CMD_ATTR_TIMEOUT_UDP, t.udp_समयout))
			जाओ nla_put_failure;
#पूर्ण_अगर

		अवरोध;
	पूर्ण

	हाल IPVS_CMD_GET_INFO:
		अगर (nla_put_u32(msg, IPVS_INFO_ATTR_VERSION,
				IP_VS_VERSION_CODE) ||
		    nla_put_u32(msg, IPVS_INFO_ATTR_CONN_TAB_SIZE,
				ip_vs_conn_tab_size))
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण

	genlmsg_end(msg, reply);
	ret = genlmsg_reply(msg, info);
	जाओ out;

nla_put_failure:
	pr_err("not enough space in Netlink message\n");
	ret = -EMSGSIZE;

out_err:
	nlmsg_मुक्त(msg);
out:
	mutex_unlock(&__ip_vs_mutex);

	वापस ret;
पूर्ण


अटल स्थिर काष्ठा genl_small_ops ip_vs_genl_ops[] = अणु
	अणु
		.cmd	= IPVS_CMD_NEW_SERVICE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_SET_SERVICE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_DEL_SERVICE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_GET_SERVICE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_get_cmd,
		.dumpit	= ip_vs_genl_dump_services,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_NEW_DEST,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_SET_DEST,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_DEL_DEST,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_GET_DEST,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.dumpit	= ip_vs_genl_dump_dests,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_NEW_DAEMON,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_daemon,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_DEL_DAEMON,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_daemon,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_GET_DAEMON,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.dumpit	= ip_vs_genl_dump_daemons,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_SET_CONFIG,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_GET_CONFIG,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_get_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_GET_INFO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_get_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_ZERO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_cmd,
	पूर्ण,
	अणु
		.cmd	= IPVS_CMD_FLUSH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= ip_vs_genl_set_cmd,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family ip_vs_genl_family __ro_after_init = अणु
	.hdrsize	= 0,
	.name		= IPVS_GENL_NAME,
	.version	= IPVS_GENL_VERSION,
	.maxattr	= IPVS_CMD_ATTR_MAX,
	.policy = ip_vs_cmd_policy,
	.netnsok        = true,         /* Make ipvsadm to work on netns */
	.module		= THIS_MODULE,
	.small_ops	= ip_vs_genl_ops,
	.n_small_ops	= ARRAY_SIZE(ip_vs_genl_ops),
पूर्ण;

अटल पूर्णांक __init ip_vs_genl_रेजिस्टर(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&ip_vs_genl_family);
पूर्ण

अटल व्योम ip_vs_genl_unरेजिस्टर(व्योम)
अणु
	genl_unरेजिस्टर_family(&ip_vs_genl_family);
पूर्ण

/* End of Generic Netlink पूर्णांकerface definitions */

/*
 * per netns पूर्णांकit/निकास func.
 */
#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक __net_init ip_vs_control_net_init_sysctl(काष्ठा netns_ipvs *ipvs)
अणु
	काष्ठा net *net = ipvs->net;
	पूर्णांक idx;
	काष्ठा ctl_table *tbl;

	atomic_set(&ipvs->drखोलोtry, 0);
	spin_lock_init(&ipvs->drखोलोtry_lock);
	spin_lock_init(&ipvs->droppacket_lock);
	spin_lock_init(&ipvs->securetcp_lock);

	अगर (!net_eq(net, &init_net)) अणु
		tbl = kmemdup(vs_vars, माप(vs_vars), GFP_KERNEL);
		अगर (tbl == शून्य)
			वापस -ENOMEM;

		/* Don't export sysctls to unprivileged users */
		अगर (net->user_ns != &init_user_ns)
			tbl[0].procname = शून्य;
	पूर्ण अन्यथा
		tbl = vs_vars;
	/* Initialize sysctl शेषs */
	क्रम (idx = 0; idx < ARRAY_SIZE(vs_vars); idx++) अणु
		अगर (tbl[idx].proc_handler == proc_करो_defense_mode)
			tbl[idx].extra2 = ipvs;
	पूर्ण
	idx = 0;
	ipvs->sysctl_amemthresh = 1024;
	tbl[idx++].data = &ipvs->sysctl_amemthresh;
	ipvs->sysctl_am_droprate = 10;
	tbl[idx++].data = &ipvs->sysctl_am_droprate;
	tbl[idx++].data = &ipvs->sysctl_drop_entry;
	tbl[idx++].data = &ipvs->sysctl_drop_packet;
#अगर_घोषित CONFIG_IP_VS_NFCT
	tbl[idx++].data = &ipvs->sysctl_conntrack;
#पूर्ण_अगर
	tbl[idx++].data = &ipvs->sysctl_secure_tcp;
	ipvs->sysctl_snat_reroute = 1;
	tbl[idx++].data = &ipvs->sysctl_snat_reroute;
	ipvs->sysctl_sync_ver = 1;
	tbl[idx++].data = &ipvs->sysctl_sync_ver;
	ipvs->sysctl_sync_ports = 1;
	tbl[idx++].data = &ipvs->sysctl_sync_ports;
	tbl[idx++].data = &ipvs->sysctl_sync_persist_mode;
	ipvs->sysctl_sync_qlen_max = nr_मुक्त_buffer_pages() / 32;
	tbl[idx++].data = &ipvs->sysctl_sync_qlen_max;
	ipvs->sysctl_sync_sock_size = 0;
	tbl[idx++].data = &ipvs->sysctl_sync_sock_size;
	tbl[idx++].data = &ipvs->sysctl_cache_bypass;
	tbl[idx++].data = &ipvs->sysctl_expire_nodest_conn;
	tbl[idx++].data = &ipvs->sysctl_sloppy_tcp;
	tbl[idx++].data = &ipvs->sysctl_sloppy_sctp;
	tbl[idx++].data = &ipvs->sysctl_expire_quiescent_ढाँचा;
	ipvs->sysctl_sync_threshold[0] = DEFAULT_SYNC_THRESHOLD;
	ipvs->sysctl_sync_threshold[1] = DEFAULT_SYNC_PERIOD;
	tbl[idx].data = &ipvs->sysctl_sync_threshold;
	tbl[idx++].maxlen = माप(ipvs->sysctl_sync_threshold);
	ipvs->sysctl_sync_refresh_period = DEFAULT_SYNC_REFRESH_PERIOD;
	tbl[idx++].data = &ipvs->sysctl_sync_refresh_period;
	ipvs->sysctl_sync_retries = clamp_t(पूर्णांक, DEFAULT_SYNC_RETRIES, 0, 3);
	tbl[idx++].data = &ipvs->sysctl_sync_retries;
	tbl[idx++].data = &ipvs->sysctl_nat_icmp_send;
	ipvs->sysctl_pmtu_disc = 1;
	tbl[idx++].data = &ipvs->sysctl_pmtu_disc;
	tbl[idx++].data = &ipvs->sysctl_backup_only;
	ipvs->sysctl_conn_reuse_mode = 1;
	tbl[idx++].data = &ipvs->sysctl_conn_reuse_mode;
	tbl[idx++].data = &ipvs->sysctl_schedule_icmp;
	tbl[idx++].data = &ipvs->sysctl_ignore_tunneled;

	ipvs->sysctl_hdr = रेजिस्टर_net_sysctl(net, "net/ipv4/vs", tbl);
	अगर (ipvs->sysctl_hdr == शून्य) अणु
		अगर (!net_eq(net, &init_net))
			kमुक्त(tbl);
		वापस -ENOMEM;
	पूर्ण
	ip_vs_start_estimator(ipvs, &ipvs->tot_stats);
	ipvs->sysctl_tbl = tbl;
	/* Schedule defense work */
	INIT_DELAYED_WORK(&ipvs->defense_work, defense_work_handler);
	queue_delayed_work(प्रणाली_दीर्घ_wq, &ipvs->defense_work,
			   DEFENSE_TIMER_PERIOD);

	/* Init delayed work क्रम expiring no dest conn */
	INIT_DELAYED_WORK(&ipvs->expire_nodest_conn_work,
			  expire_nodest_conn_handler);

	वापस 0;
पूर्ण

अटल व्योम __net_निकास ip_vs_control_net_cleanup_sysctl(काष्ठा netns_ipvs *ipvs)
अणु
	काष्ठा net *net = ipvs->net;

	cancel_delayed_work_sync(&ipvs->expire_nodest_conn_work);
	cancel_delayed_work_sync(&ipvs->defense_work);
	cancel_work_sync(&ipvs->defense_work.work);
	unरेजिस्टर_net_sysctl_table(ipvs->sysctl_hdr);
	ip_vs_stop_estimator(ipvs, &ipvs->tot_stats);

	अगर (!net_eq(net, &init_net))
		kमुक्त(ipvs->sysctl_tbl);
पूर्ण

#अन्यथा

अटल पूर्णांक __net_init ip_vs_control_net_init_sysctl(काष्ठा netns_ipvs *ipvs) अणु वापस 0; पूर्ण
अटल व्योम __net_निकास ip_vs_control_net_cleanup_sysctl(काष्ठा netns_ipvs *ipvs) अणु पूर्ण

#पूर्ण_अगर

अटल काष्ठा notअगरier_block ip_vs_dst_notअगरier = अणु
	.notअगरier_call = ip_vs_dst_event,
#अगर_घोषित CONFIG_IP_VS_IPV6
	.priority = ADDRCONF_NOTIFY_PRIORITY + 5,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __net_init ip_vs_control_net_init(काष्ठा netns_ipvs *ipvs)
अणु
	पूर्णांक i, idx;

	/* Initialize rs_table */
	क्रम (idx = 0; idx < IP_VS_RTAB_SIZE; idx++)
		INIT_HLIST_HEAD(&ipvs->rs_table[idx]);

	INIT_LIST_HEAD(&ipvs->dest_trash);
	spin_lock_init(&ipvs->dest_trash_lock);
	समयr_setup(&ipvs->dest_trash_समयr, ip_vs_dest_trash_expire, 0);
	atomic_set(&ipvs->ftpsvc_counter, 0);
	atomic_set(&ipvs->nullsvc_counter, 0);
	atomic_set(&ipvs->conn_out_counter, 0);

	/* procfs stats */
	ipvs->tot_stats.cpustats = alloc_percpu(काष्ठा ip_vs_cpu_stats);
	अगर (!ipvs->tot_stats.cpustats)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा ip_vs_cpu_stats *ipvs_tot_stats;
		ipvs_tot_stats = per_cpu_ptr(ipvs->tot_stats.cpustats, i);
		u64_stats_init(&ipvs_tot_stats->syncp);
	पूर्ण

	spin_lock_init(&ipvs->tot_stats.lock);

#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_net("ip_vs", 0, ipvs->net->proc_net,
			     &ip_vs_info_seq_ops, माप(काष्ठा ip_vs_iter)))
		जाओ err_vs;
	अगर (!proc_create_net_single("ip_vs_stats", 0, ipvs->net->proc_net,
				    ip_vs_stats_show, शून्य))
		जाओ err_stats;
	अगर (!proc_create_net_single("ip_vs_stats_percpu", 0,
				    ipvs->net->proc_net,
				    ip_vs_stats_percpu_show, शून्य))
		जाओ err_percpu;
#पूर्ण_अगर

	अगर (ip_vs_control_net_init_sysctl(ipvs))
		जाओ err;

	वापस 0;

err:
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("ip_vs_stats_percpu", ipvs->net->proc_net);

err_percpu:
	हटाओ_proc_entry("ip_vs_stats", ipvs->net->proc_net);

err_stats:
	हटाओ_proc_entry("ip_vs", ipvs->net->proc_net);

err_vs:
#पूर्ण_अगर
	मुक्त_percpu(ipvs->tot_stats.cpustats);
	वापस -ENOMEM;
पूर्ण

व्योम __net_निकास ip_vs_control_net_cleanup(काष्ठा netns_ipvs *ipvs)
अणु
	ip_vs_trash_cleanup(ipvs);
	ip_vs_control_net_cleanup_sysctl(ipvs);
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("ip_vs_stats_percpu", ipvs->net->proc_net);
	हटाओ_proc_entry("ip_vs_stats", ipvs->net->proc_net);
	हटाओ_proc_entry("ip_vs", ipvs->net->proc_net);
#पूर्ण_अगर
	मुक्त_percpu(ipvs->tot_stats.cpustats);
पूर्ण

पूर्णांक __init ip_vs_रेजिस्टर_nl_ioctl(व्योम)
अणु
	पूर्णांक ret;

	ret = nf_रेजिस्टर_sockopt(&ip_vs_sockopts);
	अगर (ret) अणु
		pr_err("cannot register sockopt.\n");
		जाओ err_sock;
	पूर्ण

	ret = ip_vs_genl_रेजिस्टर();
	अगर (ret) अणु
		pr_err("cannot register Generic Netlink interface.\n");
		जाओ err_genl;
	पूर्ण
	वापस 0;

err_genl:
	nf_unरेजिस्टर_sockopt(&ip_vs_sockopts);
err_sock:
	वापस ret;
पूर्ण

व्योम ip_vs_unरेजिस्टर_nl_ioctl(व्योम)
अणु
	ip_vs_genl_unरेजिस्टर();
	nf_unरेजिस्टर_sockopt(&ip_vs_sockopts);
पूर्ण

पूर्णांक __init ip_vs_control_init(व्योम)
अणु
	पूर्णांक idx;
	पूर्णांक ret;

	EnterFunction(2);

	/* Initialize svc_table, ip_vs_svc_fwm_table */
	क्रम (idx = 0; idx < IP_VS_SVC_TAB_SIZE; idx++) अणु
		INIT_HLIST_HEAD(&ip_vs_svc_table[idx]);
		INIT_HLIST_HEAD(&ip_vs_svc_fwm_table[idx]);
	पूर्ण

	smp_wmb();	/* Do we really need it now ? */

	ret = रेजिस्टर_netdevice_notअगरier(&ip_vs_dst_notअगरier);
	अगर (ret < 0)
		वापस ret;

	LeaveFunction(2);
	वापस 0;
पूर्ण


व्योम ip_vs_control_cleanup(व्योम)
अणु
	EnterFunction(2);
	unरेजिस्टर_netdevice_notअगरier(&ip_vs_dst_notअगरier);
	LeaveFunction(2);
पूर्ण
