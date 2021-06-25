<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C)2003,2004 USAGI/WIDE Project
 *
 * Authors	Mitsuru KANDA  <mk@linux-ipv6.org>
 *		YOSHIFUJI Hideaki <yoshfuji@linux-ipv6.org>
 *
 * Based on net/ipv4/xfrm4_tunnel.c
 */
#समावेश <linux/module.h>
#समावेश <linux/xfrm.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>
#समावेश <net/ip.h>
#समावेश <net/xfrm.h>
#समावेश <net/ipv6.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/mutex.h>
#समावेश <net/netns/generic.h>

#घोषणा XFRM6_TUNNEL_SPI_BYADDR_HSIZE 256
#घोषणा XFRM6_TUNNEL_SPI_BYSPI_HSIZE 256

#घोषणा XFRM6_TUNNEL_SPI_MIN	1
#घोषणा XFRM6_TUNNEL_SPI_MAX	0xffffffff

काष्ठा xfrm6_tunnel_net अणु
	काष्ठा hlist_head spi_byaddr[XFRM6_TUNNEL_SPI_BYADDR_HSIZE];
	काष्ठा hlist_head spi_byspi[XFRM6_TUNNEL_SPI_BYSPI_HSIZE];
	u32 spi;
पूर्ण;

अटल अचिन्हित पूर्णांक xfrm6_tunnel_net_id __पढ़ो_mostly;
अटल अंतरभूत काष्ठा xfrm6_tunnel_net *xfrm6_tunnel_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, xfrm6_tunnel_net_id);
पूर्ण

/*
 * xfrm_tunnel_spi things are क्रम allocating unique id ("spi")
 * per xfrm_address_t.
 */
काष्ठा xfrm6_tunnel_spi अणु
	काष्ठा hlist_node	list_byaddr;
	काष्ठा hlist_node	list_byspi;
	xfrm_address_t		addr;
	u32			spi;
	refcount_t		refcnt;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

अटल DEFINE_SPINLOCK(xfrm6_tunnel_spi_lock);

अटल काष्ठा kmem_cache *xfrm6_tunnel_spi_kmem __पढ़ो_mostly;

अटल अंतरभूत अचिन्हित पूर्णांक xfrm6_tunnel_spi_hash_byaddr(स्थिर xfrm_address_t *addr)
अणु
	अचिन्हित पूर्णांक h;

	h = ipv6_addr_hash((स्थिर काष्ठा in6_addr *)addr);
	h ^= h >> 16;
	h ^= h >> 8;
	h &= XFRM6_TUNNEL_SPI_BYADDR_HSIZE - 1;

	वापस h;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm6_tunnel_spi_hash_byspi(u32 spi)
अणु
	वापस spi % XFRM6_TUNNEL_SPI_BYSPI_HSIZE;
पूर्ण

अटल काष्ठा xfrm6_tunnel_spi *__xfrm6_tunnel_spi_lookup(काष्ठा net *net, स्थिर xfrm_address_t *saddr)
अणु
	काष्ठा xfrm6_tunnel_net *xfrm6_tn = xfrm6_tunnel_pernet(net);
	काष्ठा xfrm6_tunnel_spi *x6spi;

	hlist_क्रम_each_entry_rcu(x6spi,
			     &xfrm6_tn->spi_byaddr[xfrm6_tunnel_spi_hash_byaddr(saddr)],
			     list_byaddr, lockdep_is_held(&xfrm6_tunnel_spi_lock)) अणु
		अगर (xfrm6_addr_equal(&x6spi->addr, saddr))
			वापस x6spi;
	पूर्ण

	वापस शून्य;
पूर्ण

__be32 xfrm6_tunnel_spi_lookup(काष्ठा net *net, स्थिर xfrm_address_t *saddr)
अणु
	काष्ठा xfrm6_tunnel_spi *x6spi;
	u32 spi;

	rcu_पढ़ो_lock_bh();
	x6spi = __xfrm6_tunnel_spi_lookup(net, saddr);
	spi = x6spi ? x6spi->spi : 0;
	rcu_पढ़ो_unlock_bh();
	वापस htonl(spi);
पूर्ण
EXPORT_SYMBOL(xfrm6_tunnel_spi_lookup);

अटल पूर्णांक __xfrm6_tunnel_spi_check(काष्ठा net *net, u32 spi)
अणु
	काष्ठा xfrm6_tunnel_net *xfrm6_tn = xfrm6_tunnel_pernet(net);
	काष्ठा xfrm6_tunnel_spi *x6spi;
	पूर्णांक index = xfrm6_tunnel_spi_hash_byspi(spi);

	hlist_क्रम_each_entry(x6spi,
			     &xfrm6_tn->spi_byspi[index],
			     list_byspi) अणु
		अगर (x6spi->spi == spi)
			वापस -1;
	पूर्ण
	वापस index;
पूर्ण

अटल u32 __xfrm6_tunnel_alloc_spi(काष्ठा net *net, xfrm_address_t *saddr)
अणु
	काष्ठा xfrm6_tunnel_net *xfrm6_tn = xfrm6_tunnel_pernet(net);
	u32 spi;
	काष्ठा xfrm6_tunnel_spi *x6spi;
	पूर्णांक index;

	अगर (xfrm6_tn->spi < XFRM6_TUNNEL_SPI_MIN ||
	    xfrm6_tn->spi >= XFRM6_TUNNEL_SPI_MAX)
		xfrm6_tn->spi = XFRM6_TUNNEL_SPI_MIN;
	अन्यथा
		xfrm6_tn->spi++;

	क्रम (spi = xfrm6_tn->spi; spi <= XFRM6_TUNNEL_SPI_MAX; spi++) अणु
		index = __xfrm6_tunnel_spi_check(net, spi);
		अगर (index >= 0)
			जाओ alloc_spi;

		अगर (spi == XFRM6_TUNNEL_SPI_MAX)
			अवरोध;
	पूर्ण
	क्रम (spi = XFRM6_TUNNEL_SPI_MIN; spi < xfrm6_tn->spi; spi++) अणु
		index = __xfrm6_tunnel_spi_check(net, spi);
		अगर (index >= 0)
			जाओ alloc_spi;
	पूर्ण
	spi = 0;
	जाओ out;
alloc_spi:
	xfrm6_tn->spi = spi;
	x6spi = kmem_cache_alloc(xfrm6_tunnel_spi_kmem, GFP_ATOMIC);
	अगर (!x6spi)
		जाओ out;

	स_नकल(&x6spi->addr, saddr, माप(x6spi->addr));
	x6spi->spi = spi;
	refcount_set(&x6spi->refcnt, 1);

	hlist_add_head_rcu(&x6spi->list_byspi, &xfrm6_tn->spi_byspi[index]);

	index = xfrm6_tunnel_spi_hash_byaddr(saddr);
	hlist_add_head_rcu(&x6spi->list_byaddr, &xfrm6_tn->spi_byaddr[index]);
out:
	वापस spi;
पूर्ण

__be32 xfrm6_tunnel_alloc_spi(काष्ठा net *net, xfrm_address_t *saddr)
अणु
	काष्ठा xfrm6_tunnel_spi *x6spi;
	u32 spi;

	spin_lock_bh(&xfrm6_tunnel_spi_lock);
	x6spi = __xfrm6_tunnel_spi_lookup(net, saddr);
	अगर (x6spi) अणु
		refcount_inc(&x6spi->refcnt);
		spi = x6spi->spi;
	पूर्ण अन्यथा
		spi = __xfrm6_tunnel_alloc_spi(net, saddr);
	spin_unlock_bh(&xfrm6_tunnel_spi_lock);

	वापस htonl(spi);
पूर्ण
EXPORT_SYMBOL(xfrm6_tunnel_alloc_spi);

अटल व्योम x6spi_destroy_rcu(काष्ठा rcu_head *head)
अणु
	kmem_cache_मुक्त(xfrm6_tunnel_spi_kmem,
			container_of(head, काष्ठा xfrm6_tunnel_spi, rcu_head));
पूर्ण

अटल व्योम xfrm6_tunnel_मुक्त_spi(काष्ठा net *net, xfrm_address_t *saddr)
अणु
	काष्ठा xfrm6_tunnel_net *xfrm6_tn = xfrm6_tunnel_pernet(net);
	काष्ठा xfrm6_tunnel_spi *x6spi;
	काष्ठा hlist_node *n;

	spin_lock_bh(&xfrm6_tunnel_spi_lock);

	hlist_क्रम_each_entry_safe(x6spi, n,
				  &xfrm6_tn->spi_byaddr[xfrm6_tunnel_spi_hash_byaddr(saddr)],
				  list_byaddr)
	अणु
		अगर (xfrm6_addr_equal(&x6spi->addr, saddr)) अणु
			अगर (refcount_dec_and_test(&x6spi->refcnt)) अणु
				hlist_del_rcu(&x6spi->list_byaddr);
				hlist_del_rcu(&x6spi->list_byspi);
				call_rcu(&x6spi->rcu_head, x6spi_destroy_rcu);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&xfrm6_tunnel_spi_lock);
पूर्ण

अटल पूर्णांक xfrm6_tunnel_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	skb_push(skb, -skb_network_offset(skb));
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm6_tunnel_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	वापस skb_network_header(skb)[IP6CB(skb)->nhoff];
पूर्ण

अटल पूर्णांक xfrm6_tunnel_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	__be32 spi;

	spi = xfrm6_tunnel_spi_lookup(net, (स्थिर xfrm_address_t *)&iph->saddr);
	वापस xfrm6_rcv_spi(skb, IPPROTO_IPV6, spi, शून्य);
पूर्ण

अटल पूर्णांक xfrm6_tunnel_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			    u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	/* xfrm6_tunnel native err handling */
	चयन (type) अणु
	हाल ICMPV6_DEST_UNREACH:
		चयन (code) अणु
		हाल ICMPV6_NOROUTE:
		हाल ICMPV6_ADM_PROHIBITED:
		हाल ICMPV6_NOT_NEIGHBOUR:
		हाल ICMPV6_ADDR_UNREACH:
		हाल ICMPV6_PORT_UNREACH:
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ICMPV6_PKT_TOOBIG:
		अवरोध;
	हाल ICMPV6_TIME_EXCEED:
		चयन (code) अणु
		हाल ICMPV6_EXC_HOPLIMIT:
			अवरोध;
		हाल ICMPV6_EXC_FRAGTIME:
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ICMPV6_PARAMPROB:
		चयन (code) अणु
		हाल ICMPV6_HDR_FIELD: अवरोध;
		हाल ICMPV6_UNK_NEXTHDR: अवरोध;
		हाल ICMPV6_UNK_OPTION: अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm6_tunnel_init_state(काष्ठा xfrm_state *x)
अणु
	अगर (x->props.mode != XFRM_MODE_TUNNEL)
		वापस -EINVAL;

	अगर (x->encap)
		वापस -EINVAL;

	x->props.header_len = माप(काष्ठा ipv6hdr);

	वापस 0;
पूर्ण

अटल व्योम xfrm6_tunnel_destroy(काष्ठा xfrm_state *x)
अणु
	काष्ठा net *net = xs_net(x);

	xfrm6_tunnel_मुक्त_spi(net, (xfrm_address_t *)&x->props.saddr);
पूर्ण

अटल स्थिर काष्ठा xfrm_type xfrm6_tunnel_type = अणु
	.description	= "IP6IP6",
	.owner          = THIS_MODULE,
	.proto		= IPPROTO_IPV6,
	.init_state	= xfrm6_tunnel_init_state,
	.deकाष्ठाor	= xfrm6_tunnel_destroy,
	.input		= xfrm6_tunnel_input,
	.output		= xfrm6_tunnel_output,
पूर्ण;

अटल काष्ठा xfrm6_tunnel xfrm6_tunnel_handler __पढ़ो_mostly = अणु
	.handler	= xfrm6_tunnel_rcv,
	.err_handler	= xfrm6_tunnel_err,
	.priority	= 3,
पूर्ण;

अटल काष्ठा xfrm6_tunnel xfrm46_tunnel_handler __पढ़ो_mostly = अणु
	.handler	= xfrm6_tunnel_rcv,
	.err_handler	= xfrm6_tunnel_err,
	.priority	= 3,
पूर्ण;

अटल पूर्णांक __net_init xfrm6_tunnel_net_init(काष्ठा net *net)
अणु
	काष्ठा xfrm6_tunnel_net *xfrm6_tn = xfrm6_tunnel_pernet(net);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < XFRM6_TUNNEL_SPI_BYADDR_HSIZE; i++)
		INIT_HLIST_HEAD(&xfrm6_tn->spi_byaddr[i]);
	क्रम (i = 0; i < XFRM6_TUNNEL_SPI_BYSPI_HSIZE; i++)
		INIT_HLIST_HEAD(&xfrm6_tn->spi_byspi[i]);
	xfrm6_tn->spi = 0;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास xfrm6_tunnel_net_निकास(काष्ठा net *net)
अणु
	काष्ठा xfrm6_tunnel_net *xfrm6_tn = xfrm6_tunnel_pernet(net);
	अचिन्हित पूर्णांक i;

	xfrm_flush_gc();
	xfrm_state_flush(net, 0, false, true);

	क्रम (i = 0; i < XFRM6_TUNNEL_SPI_BYADDR_HSIZE; i++)
		WARN_ON_ONCE(!hlist_empty(&xfrm6_tn->spi_byaddr[i]));

	क्रम (i = 0; i < XFRM6_TUNNEL_SPI_BYSPI_HSIZE; i++)
		WARN_ON_ONCE(!hlist_empty(&xfrm6_tn->spi_byspi[i]));
पूर्ण

अटल काष्ठा pernet_operations xfrm6_tunnel_net_ops = अणु
	.init	= xfrm6_tunnel_net_init,
	.निकास	= xfrm6_tunnel_net_निकास,
	.id	= &xfrm6_tunnel_net_id,
	.size	= माप(काष्ठा xfrm6_tunnel_net),
पूर्ण;

अटल पूर्णांक __init xfrm6_tunnel_init(व्योम)
अणु
	पूर्णांक rv;

	xfrm6_tunnel_spi_kmem = kmem_cache_create("xfrm6_tunnel_spi",
						  माप(काष्ठा xfrm6_tunnel_spi),
						  0, SLAB_HWCACHE_ALIGN,
						  शून्य);
	अगर (!xfrm6_tunnel_spi_kmem)
		वापस -ENOMEM;
	rv = रेजिस्टर_pernet_subsys(&xfrm6_tunnel_net_ops);
	अगर (rv < 0)
		जाओ out_pernet;
	rv = xfrm_रेजिस्टर_type(&xfrm6_tunnel_type, AF_INET6);
	अगर (rv < 0)
		जाओ out_type;
	rv = xfrm6_tunnel_रेजिस्टर(&xfrm6_tunnel_handler, AF_INET6);
	अगर (rv < 0)
		जाओ out_xfrm6;
	rv = xfrm6_tunnel_रेजिस्टर(&xfrm46_tunnel_handler, AF_INET);
	अगर (rv < 0)
		जाओ out_xfrm46;
	वापस 0;

out_xfrm46:
	xfrm6_tunnel_deरेजिस्टर(&xfrm6_tunnel_handler, AF_INET6);
out_xfrm6:
	xfrm_unरेजिस्टर_type(&xfrm6_tunnel_type, AF_INET6);
out_type:
	unरेजिस्टर_pernet_subsys(&xfrm6_tunnel_net_ops);
out_pernet:
	kmem_cache_destroy(xfrm6_tunnel_spi_kmem);
	वापस rv;
पूर्ण

अटल व्योम __निकास xfrm6_tunnel_fini(व्योम)
अणु
	xfrm6_tunnel_deरेजिस्टर(&xfrm46_tunnel_handler, AF_INET);
	xfrm6_tunnel_deरेजिस्टर(&xfrm6_tunnel_handler, AF_INET6);
	xfrm_unरेजिस्टर_type(&xfrm6_tunnel_type, AF_INET6);
	unरेजिस्टर_pernet_subsys(&xfrm6_tunnel_net_ops);
	/* Someone maybe has gotten the xfrm6_tunnel_spi.
	 * So need to रुको it.
	 */
	rcu_barrier();
	kmem_cache_destroy(xfrm6_tunnel_spi_kmem);
पूर्ण

module_init(xfrm6_tunnel_init);
module_निकास(xfrm6_tunnel_fini);
MODULE_LICENSE("GPL");
MODULE_ALIAS_XFRM_TYPE(AF_INET6, XFRM_PROTO_IPV6);
