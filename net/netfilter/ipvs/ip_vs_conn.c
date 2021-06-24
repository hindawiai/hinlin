<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS         An implementation of the IP भव server support क्रम the
 *              LINUX operating प्रणाली.  IPVS is now implemented as a module
 *              over the Netfilter framework. IPVS can be used to build a
 *              high-perक्रमmance and highly available server based on a
 *              cluster of servers.
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Peter Kese <peter.kese@ijs.si>
 *              Julian Anastasov <ja@ssi.bg>
 *
 * The IPVS code क्रम kernel 2.2 was करोne by Wensong Zhang and Peter Kese,
 * with changes/fixes from Julian Anastasov, Lars Marowsky-Bree, Horms
 * and others. Many code here is taken from IP MASQ code of kernel 2.2.
 *
 * Changes:
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/net.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/proc_fs.h>		/* क्रम proc_net_* */
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/jhash.h>
#समावेश <linux/अक्रमom.h>

#समावेश <net/net_namespace.h>
#समावेश <net/ip_vs.h>


#अगर_अघोषित CONFIG_IP_VS_TAB_BITS
#घोषणा CONFIG_IP_VS_TAB_BITS	12
#पूर्ण_अगर

/*
 * Connection hash size. Default is what was selected at compile समय.
*/
अटल पूर्णांक ip_vs_conn_tab_bits = CONFIG_IP_VS_TAB_BITS;
module_param_named(conn_tab_bits, ip_vs_conn_tab_bits, पूर्णांक, 0444);
MODULE_PARM_DESC(conn_tab_bits, "Set connections' hash size");

/* size and mask values */
पूर्णांक ip_vs_conn_tab_size __पढ़ो_mostly;
अटल पूर्णांक ip_vs_conn_tab_mask __पढ़ो_mostly;

/*
 *  Connection hash table: क्रम input and output packets lookups of IPVS
 */
अटल काष्ठा hlist_head *ip_vs_conn_tab __पढ़ो_mostly;

/*  SLAB cache क्रम IPVS connections */
अटल काष्ठा kmem_cache *ip_vs_conn_cachep __पढ़ो_mostly;

/*  counter क्रम no client port connections */
अटल atomic_t ip_vs_conn_no_cport_cnt = ATOMIC_INIT(0);

/* अक्रमom value क्रम IPVS connection hash */
अटल अचिन्हित पूर्णांक ip_vs_conn_rnd __पढ़ो_mostly;

/*
 *  Fine locking granularity क्रम big connection hash table
 */
#घोषणा CT_LOCKARRAY_BITS  5
#घोषणा CT_LOCKARRAY_SIZE  (1<<CT_LOCKARRAY_BITS)
#घोषणा CT_LOCKARRAY_MASK  (CT_LOCKARRAY_SIZE-1)

/* We need an addrम_माप that works with or without v6 */
#अगर_घोषित CONFIG_IP_VS_IPV6
#घोषणा IP_VS_ADDRSTRLEN INET6_ADDRSTRLEN
#अन्यथा
#घोषणा IP_VS_ADDRSTRLEN (8+1)
#पूर्ण_अगर

काष्ठा ip_vs_aligned_lock
अणु
	spinlock_t	l;
पूर्ण __attribute__((__aligned__(SMP_CACHE_BYTES)));

/* lock array क्रम conn table */
अटल काष्ठा ip_vs_aligned_lock
__ip_vs_conntbl_lock_array[CT_LOCKARRAY_SIZE] __cacheline_aligned;

अटल अंतरभूत व्योम ct_ग_लिखो_lock_bh(अचिन्हित पूर्णांक key)
अणु
	spin_lock_bh(&__ip_vs_conntbl_lock_array[key&CT_LOCKARRAY_MASK].l);
पूर्ण

अटल अंतरभूत व्योम ct_ग_लिखो_unlock_bh(अचिन्हित पूर्णांक key)
अणु
	spin_unlock_bh(&__ip_vs_conntbl_lock_array[key&CT_LOCKARRAY_MASK].l);
पूर्ण

अटल व्योम ip_vs_conn_expire(काष्ठा समयr_list *t);

/*
 *	Returns hash value क्रम IPVS connection entry
 */
अटल अचिन्हित पूर्णांक ip_vs_conn_hashkey(काष्ठा netns_ipvs *ipvs, पूर्णांक af, अचिन्हित पूर्णांक proto,
				       स्थिर जोड़ nf_inet_addr *addr,
				       __be16 port)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		वापस (jhash_3words(jhash(addr, 16, ip_vs_conn_rnd),
				    (__क्रमce u32)port, proto, ip_vs_conn_rnd) ^
			((माप_प्रकार)ipvs>>8)) & ip_vs_conn_tab_mask;
#पूर्ण_अगर
	वापस (jhash_3words((__क्रमce u32)addr->ip, (__क्रमce u32)port, proto,
			    ip_vs_conn_rnd) ^
		((माप_प्रकार)ipvs>>8)) & ip_vs_conn_tab_mask;
पूर्ण

अटल अचिन्हित पूर्णांक ip_vs_conn_hashkey_param(स्थिर काष्ठा ip_vs_conn_param *p,
					     bool inverse)
अणु
	स्थिर जोड़ nf_inet_addr *addr;
	__be16 port;

	अगर (p->pe_data && p->pe->hashkey_raw)
		वापस p->pe->hashkey_raw(p, ip_vs_conn_rnd, inverse) &
			ip_vs_conn_tab_mask;

	अगर (likely(!inverse)) अणु
		addr = p->caddr;
		port = p->cport;
	पूर्ण अन्यथा अणु
		addr = p->vaddr;
		port = p->vport;
	पूर्ण

	वापस ip_vs_conn_hashkey(p->ipvs, p->af, p->protocol, addr, port);
पूर्ण

अटल अचिन्हित पूर्णांक ip_vs_conn_hashkey_conn(स्थिर काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा ip_vs_conn_param p;

	ip_vs_conn_fill_param(cp->ipvs, cp->af, cp->protocol,
			      &cp->caddr, cp->cport, शून्य, 0, &p);

	अगर (cp->pe) अणु
		p.pe = cp->pe;
		p.pe_data = cp->pe_data;
		p.pe_data_len = cp->pe_data_len;
	पूर्ण

	वापस ip_vs_conn_hashkey_param(&p, false);
पूर्ण

/*
 *	Hashes ip_vs_conn in ip_vs_conn_tab by netns,proto,addr,port.
 *	वापसs bool success.
 */
अटल अंतरभूत पूर्णांक ip_vs_conn_hash(काष्ठा ip_vs_conn *cp)
अणु
	अचिन्हित पूर्णांक hash;
	पूर्णांक ret;

	अगर (cp->flags & IP_VS_CONN_F_ONE_PACKET)
		वापस 0;

	/* Hash by protocol, client address and port */
	hash = ip_vs_conn_hashkey_conn(cp);

	ct_ग_लिखो_lock_bh(hash);
	spin_lock(&cp->lock);

	अगर (!(cp->flags & IP_VS_CONN_F_HASHED)) अणु
		cp->flags |= IP_VS_CONN_F_HASHED;
		refcount_inc(&cp->refcnt);
		hlist_add_head_rcu(&cp->c_list, &ip_vs_conn_tab[hash]);
		ret = 1;
	पूर्ण अन्यथा अणु
		pr_err("%s(): request for already hashed, called from %pS\n",
		       __func__, __builtin_वापस_address(0));
		ret = 0;
	पूर्ण

	spin_unlock(&cp->lock);
	ct_ग_लिखो_unlock_bh(hash);

	वापस ret;
पूर्ण


/*
 *	UNhashes ip_vs_conn from ip_vs_conn_tab.
 *	वापसs bool success. Caller should hold conn reference.
 */
अटल अंतरभूत पूर्णांक ip_vs_conn_unhash(काष्ठा ip_vs_conn *cp)
अणु
	अचिन्हित पूर्णांक hash;
	पूर्णांक ret;

	/* unhash it and decrease its reference counter */
	hash = ip_vs_conn_hashkey_conn(cp);

	ct_ग_लिखो_lock_bh(hash);
	spin_lock(&cp->lock);

	अगर (cp->flags & IP_VS_CONN_F_HASHED) अणु
		hlist_del_rcu(&cp->c_list);
		cp->flags &= ~IP_VS_CONN_F_HASHED;
		refcount_dec(&cp->refcnt);
		ret = 1;
	पूर्ण अन्यथा
		ret = 0;

	spin_unlock(&cp->lock);
	ct_ग_लिखो_unlock_bh(hash);

	वापस ret;
पूर्ण

/* Try to unlink ip_vs_conn from ip_vs_conn_tab.
 * वापसs bool success.
 */
अटल अंतरभूत bool ip_vs_conn_unlink(काष्ठा ip_vs_conn *cp)
अणु
	अचिन्हित पूर्णांक hash;
	bool ret = false;

	अगर (cp->flags & IP_VS_CONN_F_ONE_PACKET)
		वापस refcount_dec_अगर_one(&cp->refcnt);

	hash = ip_vs_conn_hashkey_conn(cp);

	ct_ग_लिखो_lock_bh(hash);
	spin_lock(&cp->lock);

	अगर (cp->flags & IP_VS_CONN_F_HASHED) अणु
		/* Decrease refcnt and unlink conn only अगर we are last user */
		अगर (refcount_dec_अगर_one(&cp->refcnt)) अणु
			hlist_del_rcu(&cp->c_list);
			cp->flags &= ~IP_VS_CONN_F_HASHED;
			ret = true;
		पूर्ण
	पूर्ण

	spin_unlock(&cp->lock);
	ct_ग_लिखो_unlock_bh(hash);

	वापस ret;
पूर्ण


/*
 *  Gets ip_vs_conn associated with supplied parameters in the ip_vs_conn_tab.
 *  Called क्रम pkts coming from OUTside-to-INside.
 *	p->caddr, p->cport: pkt source address (क्रमeign host)
 *	p->vaddr, p->vport: pkt dest address (load balancer)
 */
अटल अंतरभूत काष्ठा ip_vs_conn *
__ip_vs_conn_in_get(स्थिर काष्ठा ip_vs_conn_param *p)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा ip_vs_conn *cp;

	hash = ip_vs_conn_hashkey_param(p, false);

	rcu_पढ़ो_lock();

	hlist_क्रम_each_entry_rcu(cp, &ip_vs_conn_tab[hash], c_list) अणु
		अगर (p->cport == cp->cport && p->vport == cp->vport &&
		    cp->af == p->af &&
		    ip_vs_addr_equal(p->af, p->caddr, &cp->caddr) &&
		    ip_vs_addr_equal(p->af, p->vaddr, &cp->vaddr) &&
		    ((!p->cport) ^ (!(cp->flags & IP_VS_CONN_F_NO_CPORT))) &&
		    p->protocol == cp->protocol &&
		    cp->ipvs == p->ipvs) अणु
			अगर (!__ip_vs_conn_get(cp))
				जारी;
			/* HIT */
			rcu_पढ़ो_unlock();
			वापस cp;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

काष्ठा ip_vs_conn *ip_vs_conn_in_get(स्थिर काष्ठा ip_vs_conn_param *p)
अणु
	काष्ठा ip_vs_conn *cp;

	cp = __ip_vs_conn_in_get(p);
	अगर (!cp && atomic_पढ़ो(&ip_vs_conn_no_cport_cnt)) अणु
		काष्ठा ip_vs_conn_param cport_zero_p = *p;
		cport_zero_p.cport = 0;
		cp = __ip_vs_conn_in_get(&cport_zero_p);
	पूर्ण

	IP_VS_DBG_BUF(9, "lookup/in %s %s:%d->%s:%d %s\n",
		      ip_vs_proto_name(p->protocol),
		      IP_VS_DBG_ADDR(p->af, p->caddr), ntohs(p->cport),
		      IP_VS_DBG_ADDR(p->af, p->vaddr), ntohs(p->vport),
		      cp ? "hit" : "not hit");

	वापस cp;
पूर्ण

अटल पूर्णांक
ip_vs_conn_fill_param_proto(काष्ठा netns_ipvs *ipvs,
			    पूर्णांक af, स्थिर काष्ठा sk_buff *skb,
			    स्थिर काष्ठा ip_vs_iphdr *iph,
			    काष्ठा ip_vs_conn_param *p)
अणु
	__be16 _ports[2], *pptr;

	pptr = frag_safe_skb_hp(skb, iph->len, माप(_ports), _ports);
	अगर (pptr == शून्य)
		वापस 1;

	अगर (likely(!ip_vs_iph_inverse(iph)))
		ip_vs_conn_fill_param(ipvs, af, iph->protocol, &iph->saddr,
				      pptr[0], &iph->daddr, pptr[1], p);
	अन्यथा
		ip_vs_conn_fill_param(ipvs, af, iph->protocol, &iph->daddr,
				      pptr[1], &iph->saddr, pptr[0], p);
	वापस 0;
पूर्ण

काष्ठा ip_vs_conn *
ip_vs_conn_in_get_proto(काष्ठा netns_ipvs *ipvs, पूर्णांक af,
			स्थिर काष्ठा sk_buff *skb,
			स्थिर काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_conn_param p;

	अगर (ip_vs_conn_fill_param_proto(ipvs, af, skb, iph, &p))
		वापस शून्य;

	वापस ip_vs_conn_in_get(&p);
पूर्ण
EXPORT_SYMBOL_GPL(ip_vs_conn_in_get_proto);

/* Get reference to connection ढाँचा */
काष्ठा ip_vs_conn *ip_vs_ct_in_get(स्थिर काष्ठा ip_vs_conn_param *p)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा ip_vs_conn *cp;

	hash = ip_vs_conn_hashkey_param(p, false);

	rcu_पढ़ो_lock();

	hlist_क्रम_each_entry_rcu(cp, &ip_vs_conn_tab[hash], c_list) अणु
		अगर (unlikely(p->pe_data && p->pe->ct_match)) अणु
			अगर (cp->ipvs != p->ipvs)
				जारी;
			अगर (p->pe == cp->pe && p->pe->ct_match(p, cp)) अणु
				अगर (__ip_vs_conn_get(cp))
					जाओ out;
			पूर्ण
			जारी;
		पूर्ण

		अगर (cp->af == p->af &&
		    ip_vs_addr_equal(p->af, p->caddr, &cp->caddr) &&
		    /* protocol should only be IPPROTO_IP अगर
		     * p->vaddr is a fwmark */
		    ip_vs_addr_equal(p->protocol == IPPROTO_IP ? AF_UNSPEC :
				     p->af, p->vaddr, &cp->vaddr) &&
		    p->vport == cp->vport && p->cport == cp->cport &&
		    cp->flags & IP_VS_CONN_F_TEMPLATE &&
		    p->protocol == cp->protocol &&
		    cp->ipvs == p->ipvs) अणु
			अगर (__ip_vs_conn_get(cp))
				जाओ out;
		पूर्ण
	पूर्ण
	cp = शून्य;

  out:
	rcu_पढ़ो_unlock();

	IP_VS_DBG_BUF(9, "template lookup/in %s %s:%d->%s:%d %s\n",
		      ip_vs_proto_name(p->protocol),
		      IP_VS_DBG_ADDR(p->af, p->caddr), ntohs(p->cport),
		      IP_VS_DBG_ADDR(p->af, p->vaddr), ntohs(p->vport),
		      cp ? "hit" : "not hit");

	वापस cp;
पूर्ण

/* Gets ip_vs_conn associated with supplied parameters in the ip_vs_conn_tab.
 * Called क्रम pkts coming from inside-to-OUTside.
 *	p->caddr, p->cport: pkt source address (inside host)
 *	p->vaddr, p->vport: pkt dest address (क्रमeign host) */
काष्ठा ip_vs_conn *ip_vs_conn_out_get(स्थिर काष्ठा ip_vs_conn_param *p)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा ip_vs_conn *cp, *ret=शून्य;
	स्थिर जोड़ nf_inet_addr *saddr;
	__be16 sport;

	/*
	 *	Check क्रम "full" addressed entries
	 */
	hash = ip_vs_conn_hashkey_param(p, true);

	rcu_पढ़ो_lock();

	hlist_क्रम_each_entry_rcu(cp, &ip_vs_conn_tab[hash], c_list) अणु
		अगर (p->vport != cp->cport)
			जारी;

		अगर (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ) अणु
			sport = cp->vport;
			saddr = &cp->vaddr;
		पूर्ण अन्यथा अणु
			sport = cp->dport;
			saddr = &cp->daddr;
		पूर्ण

		अगर (p->cport == sport && cp->af == p->af &&
		    ip_vs_addr_equal(p->af, p->vaddr, &cp->caddr) &&
		    ip_vs_addr_equal(p->af, p->caddr, saddr) &&
		    p->protocol == cp->protocol &&
		    cp->ipvs == p->ipvs) अणु
			अगर (!__ip_vs_conn_get(cp))
				जारी;
			/* HIT */
			ret = cp;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	IP_VS_DBG_BUF(9, "lookup/out %s %s:%d->%s:%d %s\n",
		      ip_vs_proto_name(p->protocol),
		      IP_VS_DBG_ADDR(p->af, p->caddr), ntohs(p->cport),
		      IP_VS_DBG_ADDR(p->af, p->vaddr), ntohs(p->vport),
		      ret ? "hit" : "not hit");

	वापस ret;
पूर्ण

काष्ठा ip_vs_conn *
ip_vs_conn_out_get_proto(काष्ठा netns_ipvs *ipvs, पूर्णांक af,
			 स्थिर काष्ठा sk_buff *skb,
			 स्थिर काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_conn_param p;

	अगर (ip_vs_conn_fill_param_proto(ipvs, af, skb, iph, &p))
		वापस शून्य;

	वापस ip_vs_conn_out_get(&p);
पूर्ण
EXPORT_SYMBOL_GPL(ip_vs_conn_out_get_proto);

/*
 *      Put back the conn and restart its समयr with its समयout
 */
अटल व्योम __ip_vs_conn_put_समयr(काष्ठा ip_vs_conn *cp)
अणु
	अचिन्हित दीर्घ t = (cp->flags & IP_VS_CONN_F_ONE_PACKET) ?
		0 : cp->समयout;
	mod_समयr(&cp->समयr, jअगरfies+t);

	__ip_vs_conn_put(cp);
पूर्ण

व्योम ip_vs_conn_put(काष्ठा ip_vs_conn *cp)
अणु
	अगर ((cp->flags & IP_VS_CONN_F_ONE_PACKET) &&
	    (refcount_पढ़ो(&cp->refcnt) == 1) &&
	    !समयr_pending(&cp->समयr))
		/* expire connection immediately */
		ip_vs_conn_expire(&cp->समयr);
	अन्यथा
		__ip_vs_conn_put_समयr(cp);
पूर्ण

/*
 *	Fill a no_client_port connection with a client port number
 */
व्योम ip_vs_conn_fill_cport(काष्ठा ip_vs_conn *cp, __be16 cport)
अणु
	अगर (ip_vs_conn_unhash(cp)) अणु
		spin_lock_bh(&cp->lock);
		अगर (cp->flags & IP_VS_CONN_F_NO_CPORT) अणु
			atomic_dec(&ip_vs_conn_no_cport_cnt);
			cp->flags &= ~IP_VS_CONN_F_NO_CPORT;
			cp->cport = cport;
		पूर्ण
		spin_unlock_bh(&cp->lock);

		/* hash on new dport */
		ip_vs_conn_hash(cp);
	पूर्ण
पूर्ण


/*
 *	Bind a connection entry with the corresponding packet_xmit.
 *	Called by ip_vs_conn_new.
 */
अटल अंतरभूत व्योम ip_vs_bind_xmit(काष्ठा ip_vs_conn *cp)
अणु
	चयन (IP_VS_FWD_METHOD(cp)) अणु
	हाल IP_VS_CONN_F_MASQ:
		cp->packet_xmit = ip_vs_nat_xmit;
		अवरोध;

	हाल IP_VS_CONN_F_TUNNEL:
#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->daf == AF_INET6)
			cp->packet_xmit = ip_vs_tunnel_xmit_v6;
		अन्यथा
#पूर्ण_अगर
			cp->packet_xmit = ip_vs_tunnel_xmit;
		अवरोध;

	हाल IP_VS_CONN_F_DROUTE:
		cp->packet_xmit = ip_vs_dr_xmit;
		अवरोध;

	हाल IP_VS_CONN_F_LOCALNODE:
		cp->packet_xmit = ip_vs_null_xmit;
		अवरोध;

	हाल IP_VS_CONN_F_BYPASS:
		cp->packet_xmit = ip_vs_bypass_xmit;
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल अंतरभूत व्योम ip_vs_bind_xmit_v6(काष्ठा ip_vs_conn *cp)
अणु
	चयन (IP_VS_FWD_METHOD(cp)) अणु
	हाल IP_VS_CONN_F_MASQ:
		cp->packet_xmit = ip_vs_nat_xmit_v6;
		अवरोध;

	हाल IP_VS_CONN_F_TUNNEL:
		अगर (cp->daf == AF_INET6)
			cp->packet_xmit = ip_vs_tunnel_xmit_v6;
		अन्यथा
			cp->packet_xmit = ip_vs_tunnel_xmit;
		अवरोध;

	हाल IP_VS_CONN_F_DROUTE:
		cp->packet_xmit = ip_vs_dr_xmit_v6;
		अवरोध;

	हाल IP_VS_CONN_F_LOCALNODE:
		cp->packet_xmit = ip_vs_null_xmit;
		अवरोध;

	हाल IP_VS_CONN_F_BYPASS:
		cp->packet_xmit = ip_vs_bypass_xmit_v6;
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर


अटल अंतरभूत पूर्णांक ip_vs_dest_totalconns(काष्ठा ip_vs_dest *dest)
अणु
	वापस atomic_पढ़ो(&dest->activeconns)
		+ atomic_पढ़ो(&dest->inactconns);
पूर्ण

/*
 *	Bind a connection entry with a भव service destination
 *	Called just after a new connection entry is created.
 */
अटल अंतरभूत व्योम
ip_vs_bind_dest(काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_dest *dest)
अणु
	अचिन्हित पूर्णांक conn_flags;
	__u32 flags;

	/* अगर dest is शून्य, then वापस directly */
	अगर (!dest)
		वापस;

	/* Increase the refcnt counter of the dest */
	ip_vs_dest_hold(dest);

	conn_flags = atomic_पढ़ो(&dest->conn_flags);
	अगर (cp->protocol != IPPROTO_UDP)
		conn_flags &= ~IP_VS_CONN_F_ONE_PACKET;
	flags = cp->flags;
	/* Bind with the destination and its corresponding transmitter */
	अगर (flags & IP_VS_CONN_F_SYNC) अणु
		/* अगर the connection is not ढाँचा and is created
		 * by sync, preserve the activity flag.
		 */
		अगर (!(flags & IP_VS_CONN_F_TEMPLATE))
			conn_flags &= ~IP_VS_CONN_F_INACTIVE;
		/* connections inherit क्रमwarding method from dest */
		flags &= ~(IP_VS_CONN_F_FWD_MASK | IP_VS_CONN_F_NOOUTPUT);
	पूर्ण
	flags |= conn_flags;
	cp->flags = flags;
	cp->dest = dest;

	IP_VS_DBG_BUF(7, "Bind-dest %s c:%s:%d v:%s:%d "
		      "d:%s:%d fwd:%c s:%u conn->flags:%X conn->refcnt:%d "
		      "dest->refcnt:%d\n",
		      ip_vs_proto_name(cp->protocol),
		      IP_VS_DBG_ADDR(cp->af, &cp->caddr), ntohs(cp->cport),
		      IP_VS_DBG_ADDR(cp->af, &cp->vaddr), ntohs(cp->vport),
		      IP_VS_DBG_ADDR(cp->daf, &cp->daddr), ntohs(cp->dport),
		      ip_vs_fwd_tag(cp), cp->state,
		      cp->flags, refcount_पढ़ो(&cp->refcnt),
		      refcount_पढ़ो(&dest->refcnt));

	/* Update the connection counters */
	अगर (!(flags & IP_VS_CONN_F_TEMPLATE)) अणु
		/* It is a normal connection, so modअगरy the counters
		 * according to the flags, later the protocol can
		 * update them on state change
		 */
		अगर (!(flags & IP_VS_CONN_F_INACTIVE))
			atomic_inc(&dest->activeconns);
		अन्यथा
			atomic_inc(&dest->inactconns);
	पूर्ण अन्यथा अणु
		/* It is a persistent connection/ढाँचा, so increase
		   the persistent connection counter */
		atomic_inc(&dest->persistconns);
	पूर्ण

	अगर (dest->u_threshold != 0 &&
	    ip_vs_dest_totalconns(dest) >= dest->u_threshold)
		dest->flags |= IP_VS_DEST_F_OVERLOAD;
पूर्ण


/*
 * Check अगर there is a destination क्रम the connection, अगर so
 * bind the connection to the destination.
 */
व्योम ip_vs_try_bind_dest(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा ip_vs_dest *dest;

	rcu_पढ़ो_lock();

	/* This function is only invoked by the synchronization code. We करो
	 * not currently support heterogeneous pools with synchronization,
	 * so we can make the assumption that the svc_af is the same as the
	 * dest_af
	 */
	dest = ip_vs_find_dest(cp->ipvs, cp->af, cp->af, &cp->daddr,
			       cp->dport, &cp->vaddr, cp->vport,
			       cp->protocol, cp->fwmark, cp->flags);
	अगर (dest) अणु
		काष्ठा ip_vs_proto_data *pd;

		spin_lock_bh(&cp->lock);
		अगर (cp->dest) अणु
			spin_unlock_bh(&cp->lock);
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण

		/* Applications work depending on the क्रमwarding method
		 * but better to reassign them always when binding dest */
		अगर (cp->app)
			ip_vs_unbind_app(cp);

		ip_vs_bind_dest(cp, dest);
		spin_unlock_bh(&cp->lock);

		/* Update its packet transmitter */
		cp->packet_xmit = शून्य;
#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->af == AF_INET6)
			ip_vs_bind_xmit_v6(cp);
		अन्यथा
#पूर्ण_अगर
			ip_vs_bind_xmit(cp);

		pd = ip_vs_proto_data_get(cp->ipvs, cp->protocol);
		अगर (pd && atomic_पढ़ो(&pd->appcnt))
			ip_vs_bind_app(cp, pd->pp);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण


/*
 *	Unbind a connection entry with its VS destination
 *	Called by the ip_vs_conn_expire function.
 */
अटल अंतरभूत व्योम ip_vs_unbind_dest(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा ip_vs_dest *dest = cp->dest;

	अगर (!dest)
		वापस;

	IP_VS_DBG_BUF(7, "Unbind-dest %s c:%s:%d v:%s:%d "
		      "d:%s:%d fwd:%c s:%u conn->flags:%X conn->refcnt:%d "
		      "dest->refcnt:%d\n",
		      ip_vs_proto_name(cp->protocol),
		      IP_VS_DBG_ADDR(cp->af, &cp->caddr), ntohs(cp->cport),
		      IP_VS_DBG_ADDR(cp->af, &cp->vaddr), ntohs(cp->vport),
		      IP_VS_DBG_ADDR(cp->daf, &cp->daddr), ntohs(cp->dport),
		      ip_vs_fwd_tag(cp), cp->state,
		      cp->flags, refcount_पढ़ो(&cp->refcnt),
		      refcount_पढ़ो(&dest->refcnt));

	/* Update the connection counters */
	अगर (!(cp->flags & IP_VS_CONN_F_TEMPLATE)) अणु
		/* It is a normal connection, so decrease the inactconns
		   or activeconns counter */
		अगर (cp->flags & IP_VS_CONN_F_INACTIVE) अणु
			atomic_dec(&dest->inactconns);
		पूर्ण अन्यथा अणु
			atomic_dec(&dest->activeconns);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* It is a persistent connection/ढाँचा, so decrease
		   the persistent connection counter */
		atomic_dec(&dest->persistconns);
	पूर्ण

	अगर (dest->l_threshold != 0) अणु
		अगर (ip_vs_dest_totalconns(dest) < dest->l_threshold)
			dest->flags &= ~IP_VS_DEST_F_OVERLOAD;
	पूर्ण अन्यथा अगर (dest->u_threshold != 0) अणु
		अगर (ip_vs_dest_totalconns(dest) * 4 < dest->u_threshold * 3)
			dest->flags &= ~IP_VS_DEST_F_OVERLOAD;
	पूर्ण अन्यथा अणु
		अगर (dest->flags & IP_VS_DEST_F_OVERLOAD)
			dest->flags &= ~IP_VS_DEST_F_OVERLOAD;
	पूर्ण

	ip_vs_dest_put(dest);
पूर्ण

अटल पूर्णांक expire_quiescent_ढाँचा(काष्ठा netns_ipvs *ipvs,
				     काष्ठा ip_vs_dest *dest)
अणु
#अगर_घोषित CONFIG_SYSCTL
	वापस ipvs->sysctl_expire_quiescent_ढाँचा &&
		(atomic_पढ़ो(&dest->weight) == 0);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 *	Checking अगर the destination of a connection ढाँचा is available.
 *	If available, वापस 1, otherwise invalidate this connection
 *	ढाँचा and वापस 0.
 */
पूर्णांक ip_vs_check_ढाँचा(काष्ठा ip_vs_conn *ct, काष्ठा ip_vs_dest *cdest)
अणु
	काष्ठा ip_vs_dest *dest = ct->dest;
	काष्ठा netns_ipvs *ipvs = ct->ipvs;

	/*
	 * Checking the dest server status.
	 */
	अगर ((dest == शून्य) ||
	    !(dest->flags & IP_VS_DEST_F_AVAILABLE) ||
	    expire_quiescent_ढाँचा(ipvs, dest) ||
	    (cdest && (dest != cdest))) अणु
		IP_VS_DBG_BUF(9, "check_template: dest not available for "
			      "protocol %s s:%s:%d v:%s:%d "
			      "-> d:%s:%d\n",
			      ip_vs_proto_name(ct->protocol),
			      IP_VS_DBG_ADDR(ct->af, &ct->caddr),
			      ntohs(ct->cport),
			      IP_VS_DBG_ADDR(ct->af, &ct->vaddr),
			      ntohs(ct->vport),
			      IP_VS_DBG_ADDR(ct->daf, &ct->daddr),
			      ntohs(ct->dport));

		/*
		 * Invalidate the connection ढाँचा
		 */
		अगर (ct->vport != htons(0xffff)) अणु
			अगर (ip_vs_conn_unhash(ct)) अणु
				ct->dport = htons(0xffff);
				ct->vport = htons(0xffff);
				ct->cport = 0;
				ip_vs_conn_hash(ct);
			पूर्ण
		पूर्ण

		/*
		 * Simply decrease the refcnt of the ढाँचा,
		 * करोn't restart its समयr.
		 */
		__ip_vs_conn_put(ct);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम ip_vs_conn_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा ip_vs_conn *cp = container_of(head, काष्ठा ip_vs_conn,
					     rcu_head);

	ip_vs_pe_put(cp->pe);
	kमुक्त(cp->pe_data);
	kmem_cache_मुक्त(ip_vs_conn_cachep, cp);
पूर्ण

/* Try to delete connection जबतक not holding reference */
अटल व्योम ip_vs_conn_del(काष्ठा ip_vs_conn *cp)
अणु
	अगर (del_समयr(&cp->समयr)) अणु
		/* Drop cp->control chain too */
		अगर (cp->control)
			cp->समयout = 0;
		ip_vs_conn_expire(&cp->समयr);
	पूर्ण
पूर्ण

/* Try to delete connection जबतक holding reference */
अटल व्योम ip_vs_conn_del_put(काष्ठा ip_vs_conn *cp)
अणु
	अगर (del_समयr(&cp->समयr)) अणु
		/* Drop cp->control chain too */
		अगर (cp->control)
			cp->समयout = 0;
		__ip_vs_conn_put(cp);
		ip_vs_conn_expire(&cp->समयr);
	पूर्ण अन्यथा अणु
		__ip_vs_conn_put(cp);
	पूर्ण
पूर्ण

अटल व्योम ip_vs_conn_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा ip_vs_conn *cp = from_समयr(cp, t, समयr);
	काष्ठा netns_ipvs *ipvs = cp->ipvs;

	/*
	 *	करो I control anybody?
	 */
	अगर (atomic_पढ़ो(&cp->n_control))
		जाओ expire_later;

	/* Unlink conn अगर not referenced anymore */
	अगर (likely(ip_vs_conn_unlink(cp))) अणु
		काष्ठा ip_vs_conn *ct = cp->control;

		/* delete the समयr अगर it is activated by other users */
		del_समयr(&cp->समयr);

		/* करोes anybody control me? */
		अगर (ct) अणु
			bool has_ref = !cp->समयout && __ip_vs_conn_get(ct);

			ip_vs_control_del(cp);
			/* Drop CTL or non-assured TPL अगर not used anymore */
			अगर (has_ref && !atomic_पढ़ो(&ct->n_control) &&
			    (!(ct->flags & IP_VS_CONN_F_TEMPLATE) ||
			     !(ct->state & IP_VS_CTPL_S_ASSURED))) अणु
				IP_VS_DBG(4, "drop controlling connection\n");
				ip_vs_conn_del_put(ct);
			पूर्ण अन्यथा अगर (has_ref) अणु
				__ip_vs_conn_put(ct);
			पूर्ण
		पूर्ण

		अगर ((cp->flags & IP_VS_CONN_F_NFCT) &&
		    !(cp->flags & IP_VS_CONN_F_ONE_PACKET)) अणु
			/* Do not access conntracks during subsys cleanup
			 * because nf_conntrack_find_get can not be used after
			 * conntrack cleanup क्रम the net.
			 */
			smp_rmb();
			अगर (ipvs->enable)
				ip_vs_conn_drop_conntrack(cp);
		पूर्ण

		अगर (unlikely(cp->app != शून्य))
			ip_vs_unbind_app(cp);
		ip_vs_unbind_dest(cp);
		अगर (cp->flags & IP_VS_CONN_F_NO_CPORT)
			atomic_dec(&ip_vs_conn_no_cport_cnt);
		अगर (cp->flags & IP_VS_CONN_F_ONE_PACKET)
			ip_vs_conn_rcu_मुक्त(&cp->rcu_head);
		अन्यथा
			call_rcu(&cp->rcu_head, ip_vs_conn_rcu_मुक्त);
		atomic_dec(&ipvs->conn_count);
		वापस;
	पूर्ण

  expire_later:
	IP_VS_DBG(7, "delayed: conn->refcnt=%d conn->n_control=%d\n",
		  refcount_पढ़ो(&cp->refcnt),
		  atomic_पढ़ो(&cp->n_control));

	refcount_inc(&cp->refcnt);
	cp->समयout = 60*HZ;

	अगर (ipvs->sync_state & IP_VS_STATE_MASTER)
		ip_vs_sync_conn(ipvs, cp, sysctl_sync_threshold(ipvs));

	__ip_vs_conn_put_समयr(cp);
पूर्ण

/* Modअगरy समयr, so that it expires as soon as possible.
 * Can be called without reference only अगर under RCU lock.
 * We can have such chain of conns linked with ->control: DATA->CTL->TPL
 * - DATA (eg. FTP) and TPL (persistence) can be present depending on setup
 * - cp->समयout=0 indicates all conns from chain should be dropped but
 * TPL is not dropped अगर in assured state
 */
व्योम ip_vs_conn_expire_now(काष्ठा ip_vs_conn *cp)
अणु
	/* Using mod_समयr_pending will ensure the समयr is not
	 * modअगरied after the final del_समयr in ip_vs_conn_expire.
	 */
	अगर (समयr_pending(&cp->समयr) &&
	    समय_after(cp->समयr.expires, jअगरfies))
		mod_समयr_pending(&cp->समयr, jअगरfies);
पूर्ण


/*
 *	Create a new connection entry and hash it पूर्णांकo the ip_vs_conn_tab
 */
काष्ठा ip_vs_conn *
ip_vs_conn_new(स्थिर काष्ठा ip_vs_conn_param *p, पूर्णांक dest_af,
	       स्थिर जोड़ nf_inet_addr *daddr, __be16 dport, अचिन्हित पूर्णांक flags,
	       काष्ठा ip_vs_dest *dest, __u32 fwmark)
अणु
	काष्ठा ip_vs_conn *cp;
	काष्ठा netns_ipvs *ipvs = p->ipvs;
	काष्ठा ip_vs_proto_data *pd = ip_vs_proto_data_get(p->ipvs,
							   p->protocol);

	cp = kmem_cache_alloc(ip_vs_conn_cachep, GFP_ATOMIC);
	अगर (cp == शून्य) अणु
		IP_VS_ERR_RL("%s(): no memory\n", __func__);
		वापस शून्य;
	पूर्ण

	INIT_HLIST_NODE(&cp->c_list);
	समयr_setup(&cp->समयr, ip_vs_conn_expire, 0);
	cp->ipvs	   = ipvs;
	cp->af		   = p->af;
	cp->daf		   = dest_af;
	cp->protocol	   = p->protocol;
	ip_vs_addr_set(p->af, &cp->caddr, p->caddr);
	cp->cport	   = p->cport;
	/* proto should only be IPPROTO_IP अगर p->vaddr is a fwmark */
	ip_vs_addr_set(p->protocol == IPPROTO_IP ? AF_UNSPEC : p->af,
		       &cp->vaddr, p->vaddr);
	cp->vport	   = p->vport;
	ip_vs_addr_set(cp->daf, &cp->daddr, daddr);
	cp->dport          = dport;
	cp->flags	   = flags;
	cp->fwmark         = fwmark;
	अगर (flags & IP_VS_CONN_F_TEMPLATE && p->pe) अणु
		ip_vs_pe_get(p->pe);
		cp->pe = p->pe;
		cp->pe_data = p->pe_data;
		cp->pe_data_len = p->pe_data_len;
	पूर्ण अन्यथा अणु
		cp->pe = शून्य;
		cp->pe_data = शून्य;
		cp->pe_data_len = 0;
	पूर्ण
	spin_lock_init(&cp->lock);

	/*
	 * Set the entry is referenced by the current thपढ़ो beक्रमe hashing
	 * it in the table, so that other thपढ़ो run ip_vs_अक्रमom_drखोलोtry
	 * but cannot drop this entry.
	 */
	refcount_set(&cp->refcnt, 1);

	cp->control = शून्य;
	atomic_set(&cp->n_control, 0);
	atomic_set(&cp->in_pkts, 0);

	cp->packet_xmit = शून्य;
	cp->app = शून्य;
	cp->app_data = शून्य;
	/* reset काष्ठा ip_vs_seq */
	cp->in_seq.delta = 0;
	cp->out_seq.delta = 0;

	atomic_inc(&ipvs->conn_count);
	अगर (flags & IP_VS_CONN_F_NO_CPORT)
		atomic_inc(&ip_vs_conn_no_cport_cnt);

	/* Bind the connection with a destination server */
	cp->dest = शून्य;
	ip_vs_bind_dest(cp, dest);

	/* Set its state and समयout */
	cp->state = 0;
	cp->old_state = 0;
	cp->समयout = 3*HZ;
	cp->sync_endसमय = jअगरfies & ~3UL;

	/* Bind its packet transmitter */
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (p->af == AF_INET6)
		ip_vs_bind_xmit_v6(cp);
	अन्यथा
#पूर्ण_अगर
		ip_vs_bind_xmit(cp);

	अगर (unlikely(pd && atomic_पढ़ो(&pd->appcnt)))
		ip_vs_bind_app(cp, pd->pp);

	/*
	 * Allow conntrack to be preserved. By शेष, conntrack
	 * is created and destroyed क्रम every packet.
	 * Someबार keeping conntrack can be useful क्रम
	 * IP_VS_CONN_F_ONE_PACKET too.
	 */

	अगर (ip_vs_conntrack_enabled(ipvs))
		cp->flags |= IP_VS_CONN_F_NFCT;

	/* Hash it in the ip_vs_conn_tab finally */
	ip_vs_conn_hash(cp);

	वापस cp;
पूर्ण

/*
 *	/proc/net/ip_vs_conn entries
 */
#अगर_घोषित CONFIG_PROC_FS
काष्ठा ip_vs_iter_state अणु
	काष्ठा seq_net_निजी	p;
	काष्ठा hlist_head	*l;
पूर्ण;

अटल व्योम *ip_vs_conn_array(काष्ठा seq_file *seq, loff_t pos)
अणु
	पूर्णांक idx;
	काष्ठा ip_vs_conn *cp;
	काष्ठा ip_vs_iter_state *iter = seq->निजी;

	क्रम (idx = 0; idx < ip_vs_conn_tab_size; idx++) अणु
		hlist_क्रम_each_entry_rcu(cp, &ip_vs_conn_tab[idx], c_list) अणु
			/* __ip_vs_conn_get() is not needed by
			 * ip_vs_conn_seq_show and ip_vs_conn_sync_seq_show
			 */
			अगर (pos-- == 0) अणु
				iter->l = &ip_vs_conn_tab[idx];
				वापस cp;
			पूर्ण
		पूर्ण
		cond_resched_rcu();
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *ip_vs_conn_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा ip_vs_iter_state *iter = seq->निजी;

	iter->l = शून्य;
	rcu_पढ़ो_lock();
	वापस *pos ? ip_vs_conn_array(seq, *pos - 1) :SEQ_START_TOKEN;
पूर्ण

अटल व्योम *ip_vs_conn_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा ip_vs_conn *cp = v;
	काष्ठा ip_vs_iter_state *iter = seq->निजी;
	काष्ठा hlist_node *e;
	काष्ठा hlist_head *l = iter->l;
	पूर्णांक idx;

	++*pos;
	अगर (v == SEQ_START_TOKEN)
		वापस ip_vs_conn_array(seq, 0);

	/* more on same hash chain? */
	e = rcu_dereference(hlist_next_rcu(&cp->c_list));
	अगर (e)
		वापस hlist_entry(e, काष्ठा ip_vs_conn, c_list);

	idx = l - ip_vs_conn_tab;
	जबतक (++idx < ip_vs_conn_tab_size) अणु
		hlist_क्रम_each_entry_rcu(cp, &ip_vs_conn_tab[idx], c_list) अणु
			iter->l = &ip_vs_conn_tab[idx];
			वापस cp;
		पूर्ण
		cond_resched_rcu();
	पूर्ण
	iter->l = शून्य;
	वापस शून्य;
पूर्ण

अटल व्योम ip_vs_conn_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक ip_vs_conn_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq,
   "Pro FromIP   FPrt ToIP     TPrt DestIP   DPrt State       Expires PEName PEData\n");
	अन्यथा अणु
		स्थिर काष्ठा ip_vs_conn *cp = v;
		काष्ठा net *net = seq_file_net(seq);
		अक्षर pe_data[IP_VS_PENAME_MAXLEN + IP_VS_PEDATA_MAXLEN + 3];
		माप_प्रकार len = 0;
		अक्षर dbuf[IP_VS_ADDRSTRLEN];

		अगर (!net_eq(cp->ipvs->net, net))
			वापस 0;
		अगर (cp->pe_data) अणु
			pe_data[0] = ' ';
			len = म_माप(cp->pe->name);
			स_नकल(pe_data + 1, cp->pe->name, len);
			pe_data[len + 1] = ' ';
			len += 2;
			len += cp->pe->show_pe_data(cp, pe_data + len);
		पूर्ण
		pe_data[len] = '\0';

#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->daf == AF_INET6)
			snम_लिखो(dbuf, माप(dbuf), "%pI6", &cp->daddr.in6);
		अन्यथा
#पूर्ण_अगर
			snम_लिखो(dbuf, माप(dbuf), "%08X",
				 ntohl(cp->daddr.ip));

#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->af == AF_INET6)
			seq_म_लिखो(seq, "%-3s %pI6 %04X %pI6 %04X "
				"%s %04X %-11s %7u%s\n",
				ip_vs_proto_name(cp->protocol),
				&cp->caddr.in6, ntohs(cp->cport),
				&cp->vaddr.in6, ntohs(cp->vport),
				dbuf, ntohs(cp->dport),
				ip_vs_state_name(cp),
				jअगरfies_delta_to_msecs(cp->समयr.expires -
						       jअगरfies) / 1000,
				pe_data);
		अन्यथा
#पूर्ण_अगर
			seq_म_लिखो(seq,
				"%-3s %08X %04X %08X %04X"
				" %s %04X %-11s %7u%s\n",
				ip_vs_proto_name(cp->protocol),
				ntohl(cp->caddr.ip), ntohs(cp->cport),
				ntohl(cp->vaddr.ip), ntohs(cp->vport),
				dbuf, ntohs(cp->dport),
				ip_vs_state_name(cp),
				jअगरfies_delta_to_msecs(cp->समयr.expires -
						       jअगरfies) / 1000,
				pe_data);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ip_vs_conn_seq_ops = अणु
	.start = ip_vs_conn_seq_start,
	.next  = ip_vs_conn_seq_next,
	.stop  = ip_vs_conn_seq_stop,
	.show  = ip_vs_conn_seq_show,
पूर्ण;

अटल स्थिर अक्षर *ip_vs_origin_name(अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & IP_VS_CONN_F_SYNC)
		वापस "SYNC";
	अन्यथा
		वापस "LOCAL";
पूर्ण

अटल पूर्णांक ip_vs_conn_sync_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर dbuf[IP_VS_ADDRSTRLEN];

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq,
   "Pro FromIP   FPrt ToIP     TPrt DestIP   DPrt State       Origin Expires\n");
	अन्यथा अणु
		स्थिर काष्ठा ip_vs_conn *cp = v;
		काष्ठा net *net = seq_file_net(seq);

		अगर (!net_eq(cp->ipvs->net, net))
			वापस 0;

#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->daf == AF_INET6)
			snम_लिखो(dbuf, माप(dbuf), "%pI6", &cp->daddr.in6);
		अन्यथा
#पूर्ण_अगर
			snम_लिखो(dbuf, माप(dbuf), "%08X",
				 ntohl(cp->daddr.ip));

#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->af == AF_INET6)
			seq_म_लिखो(seq, "%-3s %pI6 %04X %pI6 %04X "
				"%s %04X %-11s %-6s %7u\n",
				ip_vs_proto_name(cp->protocol),
				&cp->caddr.in6, ntohs(cp->cport),
				&cp->vaddr.in6, ntohs(cp->vport),
				dbuf, ntohs(cp->dport),
				ip_vs_state_name(cp),
				ip_vs_origin_name(cp->flags),
				jअगरfies_delta_to_msecs(cp->समयr.expires -
						       jअगरfies) / 1000);
		अन्यथा
#पूर्ण_अगर
			seq_म_लिखो(seq,
				"%-3s %08X %04X %08X %04X "
				"%s %04X %-11s %-6s %7u\n",
				ip_vs_proto_name(cp->protocol),
				ntohl(cp->caddr.ip), ntohs(cp->cport),
				ntohl(cp->vaddr.ip), ntohs(cp->vport),
				dbuf, ntohs(cp->dport),
				ip_vs_state_name(cp),
				ip_vs_origin_name(cp->flags),
				jअगरfies_delta_to_msecs(cp->समयr.expires -
						       jअगरfies) / 1000);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ip_vs_conn_sync_seq_ops = अणु
	.start = ip_vs_conn_seq_start,
	.next  = ip_vs_conn_seq_next,
	.stop  = ip_vs_conn_seq_stop,
	.show  = ip_vs_conn_sync_seq_show,
पूर्ण;
#पूर्ण_अगर


/* Ranकरोmly drop connection entries beक्रमe running out of memory
 * Can be used क्रम DATA and CTL conns. For TPL conns there are exceptions:
 * - traffic क्रम services in OPS mode increases ct->in_pkts, so it is supported
 * - traffic क्रम services not in OPS mode करोes not increase ct->in_pkts in
 * all हालs, so it is not supported
 */
अटल अंतरभूत पूर्णांक todrop_entry(काष्ठा ip_vs_conn *cp)
अणु
	/*
	 * The drop rate array needs tuning क्रम real environments.
	 * Called from समयr bh only => no locking
	 */
	अटल स्थिर अक्षर todrop_rate[9] = अणु0, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण;
	अटल अक्षर todrop_counter[9] = अणु0पूर्ण;
	पूर्णांक i;

	/* अगर the conn entry hasn't lasted for 60 seconds, don't drop it.
	   This will leave enough समय क्रम normal connection to get
	   through. */
	अगर (समय_beक्रमe(cp->समयout + jअगरfies, cp->समयr.expires + 60*HZ))
		वापस 0;

	/* Don't drop the entry अगर its number of incoming packets is not
	   located in [0, 8] */
	i = atomic_पढ़ो(&cp->in_pkts);
	अगर (i > 8 || i < 0) वापस 0;

	अगर (!todrop_rate[i]) वापस 0;
	अगर (--todrop_counter[i] > 0) वापस 0;

	todrop_counter[i] = todrop_rate[i];
	वापस 1;
पूर्ण

अटल अंतरभूत bool ip_vs_conn_ops_mode(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा ip_vs_service *svc;

	अगर (!cp->dest)
		वापस false;
	svc = rcu_dereference(cp->dest->svc);
	वापस svc && (svc->flags & IP_VS_SVC_F_ONEPACKET);
पूर्ण

/* Called from keventd and must protect itself from softirqs */
व्योम ip_vs_अक्रमom_drखोलोtry(काष्ठा netns_ipvs *ipvs)
अणु
	पूर्णांक idx;
	काष्ठा ip_vs_conn *cp;

	rcu_पढ़ो_lock();
	/*
	 * Ranकरोmly scan 1/32 of the whole table every second
	 */
	क्रम (idx = 0; idx < (ip_vs_conn_tab_size>>5); idx++) अणु
		अचिन्हित पूर्णांक hash = pअक्रमom_u32() & ip_vs_conn_tab_mask;

		hlist_क्रम_each_entry_rcu(cp, &ip_vs_conn_tab[hash], c_list) अणु
			अगर (cp->ipvs != ipvs)
				जारी;
			अगर (atomic_पढ़ो(&cp->n_control))
				जारी;
			अगर (cp->flags & IP_VS_CONN_F_TEMPLATE) अणु
				/* connection ढाँचा of OPS */
				अगर (ip_vs_conn_ops_mode(cp))
					जाओ try_drop;
				अगर (!(cp->state & IP_VS_CTPL_S_ASSURED))
					जाओ drop;
				जारी;
			पूर्ण
			अगर (cp->protocol == IPPROTO_TCP) अणु
				चयन(cp->state) अणु
				हाल IP_VS_TCP_S_SYN_RECV:
				हाल IP_VS_TCP_S_SYNACK:
					अवरोध;

				हाल IP_VS_TCP_S_ESTABLISHED:
					अगर (todrop_entry(cp))
						अवरोध;
					जारी;

				शेष:
					जारी;
				पूर्ण
			पूर्ण अन्यथा अगर (cp->protocol == IPPROTO_SCTP) अणु
				चयन (cp->state) अणु
				हाल IP_VS_SCTP_S_INIT1:
				हाल IP_VS_SCTP_S_INIT:
					अवरोध;
				हाल IP_VS_SCTP_S_ESTABLISHED:
					अगर (todrop_entry(cp))
						अवरोध;
					जारी;
				शेष:
					जारी;
				पूर्ण
			पूर्ण अन्यथा अणु
try_drop:
				अगर (!todrop_entry(cp))
					जारी;
			पूर्ण

drop:
			IP_VS_DBG(4, "drop connection\n");
			ip_vs_conn_del(cp);
		पूर्ण
		cond_resched_rcu();
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण


/*
 *      Flush all the connection entries in the ip_vs_conn_tab
 */
अटल व्योम ip_vs_conn_flush(काष्ठा netns_ipvs *ipvs)
अणु
	पूर्णांक idx;
	काष्ठा ip_vs_conn *cp, *cp_c;

flush_again:
	rcu_पढ़ो_lock();
	क्रम (idx = 0; idx < ip_vs_conn_tab_size; idx++) अणु

		hlist_क्रम_each_entry_rcu(cp, &ip_vs_conn_tab[idx], c_list) अणु
			अगर (cp->ipvs != ipvs)
				जारी;
			अगर (atomic_पढ़ो(&cp->n_control))
				जारी;
			cp_c = cp->control;
			IP_VS_DBG(4, "del connection\n");
			ip_vs_conn_del(cp);
			अगर (cp_c && !atomic_पढ़ो(&cp_c->n_control)) अणु
				IP_VS_DBG(4, "del controlling connection\n");
				ip_vs_conn_del(cp_c);
			पूर्ण
		पूर्ण
		cond_resched_rcu();
	पूर्ण
	rcu_पढ़ो_unlock();

	/* the counter may be not शून्य, because maybe some conn entries
	   are run by slow समयr handler or unhashed but still referred */
	अगर (atomic_पढ़ो(&ipvs->conn_count) != 0) अणु
		schedule();
		जाओ flush_again;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
व्योम ip_vs_expire_nodest_conn_flush(काष्ठा netns_ipvs *ipvs)
अणु
	पूर्णांक idx;
	काष्ठा ip_vs_conn *cp, *cp_c;
	काष्ठा ip_vs_dest *dest;

	rcu_पढ़ो_lock();
	क्रम (idx = 0; idx < ip_vs_conn_tab_size; idx++) अणु
		hlist_क्रम_each_entry_rcu(cp, &ip_vs_conn_tab[idx], c_list) अणु
			अगर (cp->ipvs != ipvs)
				जारी;

			dest = cp->dest;
			अगर (!dest || (dest->flags & IP_VS_DEST_F_AVAILABLE))
				जारी;

			अगर (atomic_पढ़ो(&cp->n_control))
				जारी;

			cp_c = cp->control;
			IP_VS_DBG(4, "del connection\n");
			ip_vs_conn_del(cp);
			अगर (cp_c && !atomic_पढ़ो(&cp_c->n_control)) अणु
				IP_VS_DBG(4, "del controlling connection\n");
				ip_vs_conn_del(cp_c);
			पूर्ण
		पूर्ण
		cond_resched_rcu();

		/* netns clean up started, पात delayed work */
		अगर (!ipvs->enable)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर

/*
 * per netns init and निकास
 */
पूर्णांक __net_init ip_vs_conn_net_init(काष्ठा netns_ipvs *ipvs)
अणु
	atomic_set(&ipvs->conn_count, 0);

	proc_create_net("ip_vs_conn", 0, ipvs->net->proc_net,
			&ip_vs_conn_seq_ops, माप(काष्ठा ip_vs_iter_state));
	proc_create_net("ip_vs_conn_sync", 0, ipvs->net->proc_net,
			&ip_vs_conn_sync_seq_ops,
			माप(काष्ठा ip_vs_iter_state));
	वापस 0;
पूर्ण

व्योम __net_निकास ip_vs_conn_net_cleanup(काष्ठा netns_ipvs *ipvs)
अणु
	/* flush all the connection entries first */
	ip_vs_conn_flush(ipvs);
	हटाओ_proc_entry("ip_vs_conn", ipvs->net->proc_net);
	हटाओ_proc_entry("ip_vs_conn_sync", ipvs->net->proc_net);
पूर्ण

पूर्णांक __init ip_vs_conn_init(व्योम)
अणु
	पूर्णांक idx;

	/* Compute size and mask */
	ip_vs_conn_tab_size = 1 << ip_vs_conn_tab_bits;
	ip_vs_conn_tab_mask = ip_vs_conn_tab_size - 1;

	/*
	 * Allocate the connection hash table and initialize its list heads
	 */
	ip_vs_conn_tab = vदो_स्मृति(array_size(ip_vs_conn_tab_size,
					    माप(*ip_vs_conn_tab)));
	अगर (!ip_vs_conn_tab)
		वापस -ENOMEM;

	/* Allocate ip_vs_conn slab cache */
	ip_vs_conn_cachep = kmem_cache_create("ip_vs_conn",
					      माप(काष्ठा ip_vs_conn), 0,
					      SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!ip_vs_conn_cachep) अणु
		vमुक्त(ip_vs_conn_tab);
		वापस -ENOMEM;
	पूर्ण

	pr_info("Connection hash table configured "
		"(size=%d, memory=%ldKbytes)\n",
		ip_vs_conn_tab_size,
		(दीर्घ)(ip_vs_conn_tab_size*माप(काष्ठा list_head))/1024);
	IP_VS_DBG(0, "Each connection entry needs %zd bytes at least\n",
		  माप(काष्ठा ip_vs_conn));

	क्रम (idx = 0; idx < ip_vs_conn_tab_size; idx++)
		INIT_HLIST_HEAD(&ip_vs_conn_tab[idx]);

	क्रम (idx = 0; idx < CT_LOCKARRAY_SIZE; idx++)  अणु
		spin_lock_init(&__ip_vs_conntbl_lock_array[idx].l);
	पूर्ण

	/* calculate the अक्रमom value क्रम connection hash */
	get_अक्रमom_bytes(&ip_vs_conn_rnd, माप(ip_vs_conn_rnd));

	वापस 0;
पूर्ण

व्योम ip_vs_conn_cleanup(व्योम)
अणु
	/* Wait all ip_vs_conn_rcu_मुक्त() callbacks to complete */
	rcu_barrier();
	/* Release the empty cache */
	kmem_cache_destroy(ip_vs_conn_cachep);
	vमुक्त(ip_vs_conn_tab);
पूर्ण
