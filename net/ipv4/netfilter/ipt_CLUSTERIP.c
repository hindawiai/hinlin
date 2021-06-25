<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Cluster IP hashmark target
 * (C) 2003-2004 by Harald Welte <laक्रमge@netfilter.org>
 * based on ideas of Fabio Olive Leite <olive@unixक्रमge.org>
 *
 * Development of this code funded by SuSE Linux AG, https://www.suse.com/
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/jhash.h>
#समावेश <linux/bitops.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/refcount.h>
#समावेश <linux/netfilter_arp.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv4/ipt_CLUSTERIP.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/checksum.h>
#समावेश <net/ip.h>

#घोषणा CLUSTERIP_VERSION "0.8"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("Xtables: CLUSTERIP target");

काष्ठा clusterip_config अणु
	काष्ठा list_head list;			/* list of all configs */
	refcount_t refcount;			/* reference count */
	refcount_t entries;			/* number of entries/rules
						 * referencing us */

	__be32 clusterip;			/* the IP address */
	u_पूर्णांक8_t clustermac[ETH_ALEN];		/* the MAC address */
	पूर्णांक अगरindex;				/* device अगरindex */
	u_पूर्णांक16_t num_total_nodes;		/* total number of nodes */
	अचिन्हित दीर्घ local_nodes;		/* node number array */

#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *pde;		/* proc dir entry */
#पूर्ण_अगर
	क्रमागत clusterip_hashmode hash_mode;	/* which hashing mode */
	u_पूर्णांक32_t hash_initval;			/* hash initialization */
	काष्ठा rcu_head rcu;			/* क्रम call_rcu */
	काष्ठा net *net;			/* netns क्रम pernet list */
	अक्षर अगरname[IFNAMSIZ];			/* device अगरname */
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल स्थिर काष्ठा proc_ops clusterip_proc_ops;
#पूर्ण_अगर

काष्ठा clusterip_net अणु
	काष्ठा list_head configs;
	/* lock protects the configs list */
	spinlock_t lock;

#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *procdir;
	/* mutex protects the config->pde*/
	काष्ठा mutex mutex;
#पूर्ण_अगर
पूर्ण;

अटल अचिन्हित पूर्णांक clusterip_net_id __पढ़ो_mostly;
अटल अंतरभूत काष्ठा clusterip_net *clusterip_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, clusterip_net_id);
पूर्ण

अटल अंतरभूत व्योम
clusterip_config_get(काष्ठा clusterip_config *c)
अणु
	refcount_inc(&c->refcount);
पूर्ण

अटल व्योम clusterip_config_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा clusterip_config *config;
	काष्ठा net_device *dev;

	config = container_of(head, काष्ठा clusterip_config, rcu);
	dev = dev_get_by_name(config->net, config->अगरname);
	अगर (dev) अणु
		dev_mc_del(dev, config->clustermac);
		dev_put(dev);
	पूर्ण
	kमुक्त(config);
पूर्ण

अटल अंतरभूत व्योम
clusterip_config_put(काष्ठा clusterip_config *c)
अणु
	अगर (refcount_dec_and_test(&c->refcount))
		call_rcu(&c->rcu, clusterip_config_rcu_मुक्त);
पूर्ण

/* decrease the count of entries using/referencing this config.  If last
 * entry(rule) is हटाओd, हटाओ the config from lists, but करोn't मुक्त it
 * yet, since proc-files could still be holding references */
अटल अंतरभूत व्योम
clusterip_config_entry_put(काष्ठा clusterip_config *c)
अणु
	काष्ठा clusterip_net *cn = clusterip_pernet(c->net);

	local_bh_disable();
	अगर (refcount_dec_and_lock(&c->entries, &cn->lock)) अणु
		list_del_rcu(&c->list);
		spin_unlock(&cn->lock);
		local_bh_enable();
		/* In हाल anyone still accesses the file, the खोलो/बंद
		 * functions are also incrementing the refcount on their own,
		 * so it's safe to remove the entry even if it's in use. */
#अगर_घोषित CONFIG_PROC_FS
		mutex_lock(&cn->mutex);
		अगर (cn->procdir)
			proc_हटाओ(c->pde);
		mutex_unlock(&cn->mutex);
#पूर्ण_अगर
		वापस;
	पूर्ण
	local_bh_enable();
पूर्ण

अटल काष्ठा clusterip_config *
__clusterip_config_find(काष्ठा net *net, __be32 clusterip)
अणु
	काष्ठा clusterip_config *c;
	काष्ठा clusterip_net *cn = clusterip_pernet(net);

	list_क्रम_each_entry_rcu(c, &cn->configs, list) अणु
		अगर (c->clusterip == clusterip)
			वापस c;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा clusterip_config *
clusterip_config_find_get(काष्ठा net *net, __be32 clusterip, पूर्णांक entry)
अणु
	काष्ठा clusterip_config *c;

	rcu_पढ़ो_lock_bh();
	c = __clusterip_config_find(net, clusterip);
	अगर (c) अणु
#अगर_घोषित CONFIG_PROC_FS
		अगर (!c->pde)
			c = शून्य;
		अन्यथा
#पूर्ण_अगर
		अगर (unlikely(!refcount_inc_not_zero(&c->refcount)))
			c = शून्य;
		अन्यथा अगर (entry) अणु
			अगर (unlikely(!refcount_inc_not_zero(&c->entries))) अणु
				clusterip_config_put(c);
				c = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	वापस c;
पूर्ण

अटल व्योम
clusterip_config_init_nodelist(काष्ठा clusterip_config *c,
			       स्थिर काष्ठा ipt_clusterip_tgt_info *i)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < i->num_local_nodes; n++)
		set_bit(i->local_nodes[n] - 1, &c->local_nodes);
पूर्ण

अटल पूर्णांक
clusterip_netdev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
		       व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);
	काष्ठा clusterip_net *cn = clusterip_pernet(net);
	काष्ठा clusterip_config *c;

	spin_lock_bh(&cn->lock);
	list_क्रम_each_entry_rcu(c, &cn->configs, list) अणु
		चयन (event) अणु
		हाल NETDEV_REGISTER:
			अगर (!म_भेद(dev->name, c->अगरname)) अणु
				c->अगरindex = dev->अगरindex;
				dev_mc_add(dev, c->clustermac);
			पूर्ण
			अवरोध;
		हाल NETDEV_UNREGISTER:
			अगर (dev->अगरindex == c->अगरindex) अणु
				dev_mc_del(dev, c->clustermac);
				c->अगरindex = -1;
			पूर्ण
			अवरोध;
		हाल NETDEV_CHANGENAME:
			अगर (!म_भेद(dev->name, c->अगरname)) अणु
				c->अगरindex = dev->अगरindex;
				dev_mc_add(dev, c->clustermac);
			पूर्ण अन्यथा अगर (dev->अगरindex == c->अगरindex) अणु
				dev_mc_del(dev, c->clustermac);
				c->अगरindex = -1;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cn->lock);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा clusterip_config *
clusterip_config_init(काष्ठा net *net, स्थिर काष्ठा ipt_clusterip_tgt_info *i,
		      __be32 ip, स्थिर अक्षर *inअगरace)
अणु
	काष्ठा clusterip_net *cn = clusterip_pernet(net);
	काष्ठा clusterip_config *c;
	काष्ठा net_device *dev;
	पूर्णांक err;

	अगर (inअगरace[0] == '\0') अणु
		pr_info("Please specify an interface name\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	c = kzalloc(माप(*c), GFP_ATOMIC);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	dev = dev_get_by_name(net, inअगरace);
	अगर (!dev) अणु
		pr_info("no such interface %s\n", inअगरace);
		kमुक्त(c);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	c->अगरindex = dev->अगरindex;
	म_नकल(c->अगरname, dev->name);
	स_नकल(&c->clustermac, &i->clustermac, ETH_ALEN);
	dev_mc_add(dev, c->clustermac);
	dev_put(dev);

	c->clusterip = ip;
	c->num_total_nodes = i->num_total_nodes;
	clusterip_config_init_nodelist(c, i);
	c->hash_mode = i->hash_mode;
	c->hash_initval = i->hash_initval;
	c->net = net;
	refcount_set(&c->refcount, 1);

	spin_lock_bh(&cn->lock);
	अगर (__clusterip_config_find(net, ip)) अणु
		err = -EBUSY;
		जाओ out_config_put;
	पूर्ण

	list_add_rcu(&c->list, &cn->configs);
	spin_unlock_bh(&cn->lock);

#अगर_घोषित CONFIG_PROC_FS
	अणु
		अक्षर buffer[16];

		/* create proc dir entry */
		प्र_लिखो(buffer, "%pI4", &ip);
		mutex_lock(&cn->mutex);
		c->pde = proc_create_data(buffer, 0600,
					  cn->procdir,
					  &clusterip_proc_ops, c);
		mutex_unlock(&cn->mutex);
		अगर (!c->pde) अणु
			err = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	refcount_set(&c->entries, 1);
	वापस c;

#अगर_घोषित CONFIG_PROC_FS
err:
#पूर्ण_अगर
	spin_lock_bh(&cn->lock);
	list_del_rcu(&c->list);
out_config_put:
	spin_unlock_bh(&cn->lock);
	clusterip_config_put(c);
	वापस ERR_PTR(err);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक
clusterip_add_node(काष्ठा clusterip_config *c, u_पूर्णांक16_t nodक्रमागत)
अणु

	अगर (nodक्रमागत == 0 ||
	    nodक्रमागत > c->num_total_nodes)
		वापस 1;

	/* check अगर we alपढ़ोy have this number in our bitfield */
	अगर (test_and_set_bit(nodक्रमागत - 1, &c->local_nodes))
		वापस 1;

	वापस 0;
पूर्ण

अटल bool
clusterip_del_node(काष्ठा clusterip_config *c, u_पूर्णांक16_t nodक्रमागत)
अणु
	अगर (nodक्रमागत == 0 ||
	    nodक्रमागत > c->num_total_nodes)
		वापस true;

	अगर (test_and_clear_bit(nodक्रमागत - 1, &c->local_nodes))
		वापस false;

	वापस true;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u_पूर्णांक32_t
clusterip_hashfn(स्थिर काष्ठा sk_buff *skb,
		 स्थिर काष्ठा clusterip_config *config)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	अचिन्हित दीर्घ hashval;
	u_पूर्णांक16_t sport = 0, dport = 0;
	पूर्णांक poff;

	poff = proto_ports_offset(iph->protocol);
	अगर (poff >= 0) अणु
		स्थिर u_पूर्णांक16_t *ports;
		u16 _ports[2];

		ports = skb_header_poपूर्णांकer(skb, iph->ihl * 4 + poff, 4, _ports);
		अगर (ports) अणु
			sport = ports[0];
			dport = ports[1];
		पूर्ण
	पूर्ण अन्यथा अणु
		net_info_ratelimited("unknown protocol %u\n", iph->protocol);
	पूर्ण

	चयन (config->hash_mode) अणु
	हाल CLUSTERIP_HASHMODE_SIP:
		hashval = jhash_1word(ntohl(iph->saddr),
				      config->hash_initval);
		अवरोध;
	हाल CLUSTERIP_HASHMODE_SIP_SPT:
		hashval = jhash_2words(ntohl(iph->saddr), sport,
				       config->hash_initval);
		अवरोध;
	हाल CLUSTERIP_HASHMODE_SIP_SPT_DPT:
		hashval = jhash_3words(ntohl(iph->saddr), sport, dport,
				       config->hash_initval);
		अवरोध;
	शेष:
		/* to make gcc happy */
		hashval = 0;
		/* This cannot happen, unless the check function wasn't called
		 * at rule load समय */
		pr_info("unknown mode %u\n", config->hash_mode);
		BUG();
		अवरोध;
	पूर्ण

	/* node numbers are 1..n, not 0..n */
	वापस reciprocal_scale(hashval, config->num_total_nodes) + 1;
पूर्ण

अटल अंतरभूत पूर्णांक
clusterip_responsible(स्थिर काष्ठा clusterip_config *config, u_पूर्णांक32_t hash)
अणु
	वापस test_bit(hash - 1, &config->local_nodes);
पूर्ण

/***********************************************************************
 * IPTABLES TARGET
 ***********************************************************************/

अटल अचिन्हित पूर्णांक
clusterip_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ipt_clusterip_tgt_info *cipinfo = par->targinfo;
	काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	u_पूर्णांक32_t hash;

	/* करोn't need to clusterip_config_get() here, since refcount
	 * is only decremented by destroy() - and ip_tables guarantees
	 * that the ->target() function isn't called after ->destroy() */

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct == शून्य)
		वापस NF_DROP;

	/* special हाल: ICMP error handling. conntrack distinguishes between
	 * error messages (RELATED) and inक्रमmation requests (see below) */
	अगर (ip_hdr(skb)->protocol == IPPROTO_ICMP &&
	    (ctinfo == IP_CT_RELATED ||
	     ctinfo == IP_CT_RELATED_REPLY))
		वापस XT_CONTINUE;

	/* nf_conntrack_proto_icmp guarantees us that we only have ICMP_ECHO,
	 * TIMESTAMP, INFO_REQUEST or ICMP_ADDRESS type icmp packets from here
	 * on, which all have an ID field [relevant क्रम hashing]. */

	hash = clusterip_hashfn(skb, cipinfo->config);

	चयन (ctinfo) अणु
	हाल IP_CT_NEW:
		ct->mark = hash;
		अवरोध;
	हाल IP_CT_RELATED:
	हाल IP_CT_RELATED_REPLY:
		/* FIXME: we करोn't handle expectations at the moment.
		 * They can arrive on a dअगरferent node than
		 * the master connection (e.g. FTP passive mode) */
	हाल IP_CT_ESTABLISHED:
	हाल IP_CT_ESTABLISHED_REPLY:
		अवरोध;
	शेष:			/* Prevent gcc warnings */
		अवरोध;
	पूर्ण

#अगर_घोषित DEBUG
	nf_ct_dump_tuple_ip(&ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple);
#पूर्ण_अगर
	pr_debug("hash=%u ct_hash=%u ", hash, ct->mark);
	अगर (!clusterip_responsible(cipinfo->config, hash)) अणु
		pr_debug("not responsible\n");
		वापस NF_DROP;
	पूर्ण
	pr_debug("responsible\n");

	/* despite being received via linklayer multicast, this is
	 * actually a unicast IP packet. TCP करोesn't like PACKET_MULTICAST */
	skb->pkt_type = PACKET_HOST;

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक clusterip_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा ipt_clusterip_tgt_info *cipinfo = par->targinfo;
	स्थिर काष्ठा ipt_entry *e = par->entryinfo;
	काष्ठा clusterip_config *config;
	पूर्णांक ret, i;

	अगर (par->nft_compat) अणु
		pr_err("cannot use CLUSTERIP target from nftables compat\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (cipinfo->hash_mode != CLUSTERIP_HASHMODE_SIP &&
	    cipinfo->hash_mode != CLUSTERIP_HASHMODE_SIP_SPT &&
	    cipinfo->hash_mode != CLUSTERIP_HASHMODE_SIP_SPT_DPT) अणु
		pr_info("unknown mode %u\n", cipinfo->hash_mode);
		वापस -EINVAL;

	पूर्ण
	अगर (e->ip.dmsk.s_addr != htonl(0xffffffff) ||
	    e->ip.dst.s_addr == 0) अणु
		pr_info("Please specify destination IP\n");
		वापस -EINVAL;
	पूर्ण
	अगर (cipinfo->num_local_nodes > ARRAY_SIZE(cipinfo->local_nodes)) अणु
		pr_info("bad num_local_nodes %u\n", cipinfo->num_local_nodes);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < cipinfo->num_local_nodes; i++) अणु
		अगर (cipinfo->local_nodes[i] - 1 >=
		    माप(config->local_nodes) * 8) अणु
			pr_info("bad local_nodes[%d] %u\n",
				i, cipinfo->local_nodes[i]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	config = clusterip_config_find_get(par->net, e->ip.dst.s_addr, 1);
	अगर (!config) अणु
		अगर (!(cipinfo->flags & CLUSTERIP_FLAG_NEW)) अणु
			pr_info("no config found for %pI4, need 'new'\n",
				&e->ip.dst.s_addr);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			config = clusterip_config_init(par->net, cipinfo,
						       e->ip.dst.s_addr,
						       e->ip.inअगरace);
			अगर (IS_ERR(config))
				वापस PTR_ERR(config);
		पूर्ण
	पूर्ण अन्यथा अगर (स_भेद(&config->clustermac, &cipinfo->clustermac, ETH_ALEN))
		वापस -EINVAL;

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0) अणु
		pr_info("cannot load conntrack support for proto=%u\n",
			par->family);
		clusterip_config_entry_put(config);
		clusterip_config_put(config);
		वापस ret;
	पूर्ण

	अगर (!par->net->xt.clusterip_deprecated_warning) अणु
		pr_info("ipt_CLUSTERIP is deprecated and it will removed soon, "
			"use xt_cluster instead\n");
		par->net->xt.clusterip_deprecated_warning = true;
	पूर्ण

	cipinfo->config = config;
	वापस ret;
पूर्ण

/* drop reference count of cluster config when rule is deleted */
अटल व्योम clusterip_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	स्थिर काष्ठा ipt_clusterip_tgt_info *cipinfo = par->targinfo;

	/* अगर no more entries are referencing the config, हटाओ it
	 * from the list and destroy the proc entry */
	clusterip_config_entry_put(cipinfo->config);

	clusterip_config_put(cipinfo->config);

	nf_ct_netns_put(par->net, par->family);
पूर्ण

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
काष्ठा compat_ipt_clusterip_tgt_info
अणु
	u_पूर्णांक32_t	flags;
	u_पूर्णांक8_t	clustermac[6];
	u_पूर्णांक16_t	num_total_nodes;
	u_पूर्णांक16_t	num_local_nodes;
	u_पूर्णांक16_t	local_nodes[CLUSTERIP_MAX_NODES];
	u_पूर्णांक32_t	hash_mode;
	u_पूर्णांक32_t	hash_initval;
	compat_uptr_t	config;
पूर्ण;
#पूर्ण_अगर /* CONFIG_NETFILTER_XTABLES_COMPAT */

अटल काष्ठा xt_target clusterip_tg_reg __पढ़ो_mostly = अणु
	.name		= "CLUSTERIP",
	.family		= NFPROTO_IPV4,
	.target		= clusterip_tg,
	.checkentry	= clusterip_tg_check,
	.destroy	= clusterip_tg_destroy,
	.tarमाला_लोize	= माप(काष्ठा ipt_clusterip_tgt_info),
	.usersize	= दुरत्व(काष्ठा ipt_clusterip_tgt_info, config),
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	.compatsize	= माप(काष्ठा compat_ipt_clusterip_tgt_info),
#पूर्ण_अगर /* CONFIG_NETFILTER_XTABLES_COMPAT */
	.me		= THIS_MODULE
पूर्ण;


/***********************************************************************
 * ARP MANGLING CODE
 ***********************************************************************/

/* hardcoded क्रम 48bit ethernet and 32bit ipv4 addresses */
काष्ठा arp_payload अणु
	u_पूर्णांक8_t src_hw[ETH_ALEN];
	__be32 src_ip;
	u_पूर्णांक8_t dst_hw[ETH_ALEN];
	__be32 dst_ip;
पूर्ण __packed;

#अगर_घोषित DEBUG
अटल व्योम arp_prपूर्णांक(काष्ठा arp_payload *payload)
अणु
#घोषणा HBUFFERLEN 30
	अक्षर hbuffer[HBUFFERLEN];
	पूर्णांक j, k;

	क्रम (k = 0, j = 0; k < HBUFFERLEN - 3 && j < ETH_ALEN; j++) अणु
		hbuffer[k++] = hex_asc_hi(payload->src_hw[j]);
		hbuffer[k++] = hex_asc_lo(payload->src_hw[j]);
		hbuffer[k++] = ':';
	पूर्ण
	hbuffer[--k] = '\0';

	pr_debug("src %pI4@%s, dst %pI4\n",
		 &payload->src_ip, hbuffer, &payload->dst_ip);
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक
arp_mangle(व्योम *priv,
	   काष्ठा sk_buff *skb,
	   स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा arphdr *arp = arp_hdr(skb);
	काष्ठा arp_payload *payload;
	काष्ठा clusterip_config *c;
	काष्ठा net *net = state->net;

	/* we करोn't care about non-ethernet and non-ipv4 ARP */
	अगर (arp->ar_hrd != htons(ARPHRD_ETHER) ||
	    arp->ar_pro != htons(ETH_P_IP) ||
	    arp->ar_pln != 4 || arp->ar_hln != ETH_ALEN)
		वापस NF_ACCEPT;

	/* we only want to mangle arp requests and replies */
	अगर (arp->ar_op != htons(ARPOP_REPLY) &&
	    arp->ar_op != htons(ARPOP_REQUEST))
		वापस NF_ACCEPT;

	payload = (व्योम *)(arp+1);

	/* अगर there is no clusterip configuration क्रम the arp reply's
	 * source ip, we करोn't want to mangle it */
	c = clusterip_config_find_get(net, payload->src_ip, 0);
	अगर (!c)
		वापस NF_ACCEPT;

	/* normally the linux kernel always replies to arp queries of
	 * addresses on dअगरferent पूर्णांकerfacs.  However, in the CLUSTERIP हाल
	 * this wouldn't work, since we didn't subscribe the mcast group on
	 * other पूर्णांकerfaces */
	अगर (c->अगरindex != state->out->अगरindex) अणु
		pr_debug("not mangling arp reply on different interface: cip'%d'-skb'%d'\n",
			 c->अगरindex, state->out->अगरindex);
		clusterip_config_put(c);
		वापस NF_ACCEPT;
	पूर्ण

	/* mangle reply hardware address */
	स_नकल(payload->src_hw, c->clustermac, arp->ar_hln);

#अगर_घोषित DEBUG
	pr_debug("mangled arp reply: ");
	arp_prपूर्णांक(payload);
#पूर्ण_अगर

	clusterip_config_put(c);

	वापस NF_ACCEPT;
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops cip_arp_ops = अणु
	.hook = arp_mangle,
	.pf = NFPROTO_ARP,
	.hooknum = NF_ARP_OUT,
	.priority = -1
पूर्ण;

/***********************************************************************
 * PROC सूची HANDLING
 ***********************************************************************/

#अगर_घोषित CONFIG_PROC_FS

काष्ठा clusterip_seq_position अणु
	अचिन्हित पूर्णांक pos;	/* position */
	अचिन्हित पूर्णांक weight;	/* number of bits set == size */
	अचिन्हित पूर्णांक bit;	/* current bit */
	अचिन्हित दीर्घ val;	/* current value */
पूर्ण;

अटल व्योम *clusterip_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा clusterip_config *c = s->निजी;
	अचिन्हित पूर्णांक weight;
	u_पूर्णांक32_t local_nodes;
	काष्ठा clusterip_seq_position *idx;

	/* FIXME: possible race */
	local_nodes = c->local_nodes;
	weight = hweight32(local_nodes);
	अगर (*pos >= weight)
		वापस शून्य;

	idx = kदो_स्मृति(माप(काष्ठा clusterip_seq_position), GFP_KERNEL);
	अगर (!idx)
		वापस ERR_PTR(-ENOMEM);

	idx->pos = *pos;
	idx->weight = weight;
	idx->bit = ffs(local_nodes);
	idx->val = local_nodes;
	clear_bit(idx->bit - 1, &idx->val);

	वापस idx;
पूर्ण

अटल व्योम *clusterip_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा clusterip_seq_position *idx = v;

	*pos = ++idx->pos;
	अगर (*pos >= idx->weight) अणु
		kमुक्त(v);
		वापस शून्य;
	पूर्ण
	idx->bit = ffs(idx->val);
	clear_bit(idx->bit - 1, &idx->val);
	वापस idx;
पूर्ण

अटल व्योम clusterip_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	अगर (!IS_ERR(v))
		kमुक्त(v);
पूर्ण

अटल पूर्णांक clusterip_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा clusterip_seq_position *idx = v;

	अगर (idx->pos != 0)
		seq_अ_दो(s, ',');

	seq_म_लिखो(s, "%u", idx->bit);

	अगर (idx->pos == idx->weight - 1)
		seq_अ_दो(s, '\n');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations clusterip_seq_ops = अणु
	.start	= clusterip_seq_start,
	.next	= clusterip_seq_next,
	.stop	= clusterip_seq_stop,
	.show	= clusterip_seq_show,
पूर्ण;

अटल पूर्णांक clusterip_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = seq_खोलो(file, &clusterip_seq_ops);

	अगर (!ret) अणु
		काष्ठा seq_file *sf = file->निजी_data;
		काष्ठा clusterip_config *c = PDE_DATA(inode);

		sf->निजी = c;

		clusterip_config_get(c);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clusterip_proc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा clusterip_config *c = PDE_DATA(inode);
	पूर्णांक ret;

	ret = seq_release(inode, file);

	अगर (!ret)
		clusterip_config_put(c);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार clusterip_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *input,
				माप_प्रकार size, loff_t *ofs)
अणु
	काष्ठा clusterip_config *c = PDE_DATA(file_inode(file));
#घोषणा PROC_WRITELEN	10
	अक्षर buffer[PROC_WRITELEN+1];
	अचिन्हित दीर्घ nodक्रमागत;
	पूर्णांक rc;

	अगर (size > PROC_WRITELEN)
		वापस -EIO;
	अगर (copy_from_user(buffer, input, size))
		वापस -EFAULT;
	buffer[size] = 0;

	अगर (*buffer == '+') अणु
		rc = kम_से_अदीर्घ(buffer+1, 10, &nodक्रमागत);
		अगर (rc)
			वापस rc;
		अगर (clusterip_add_node(c, nodक्रमागत))
			वापस -ENOMEM;
	पूर्ण अन्यथा अगर (*buffer == '-') अणु
		rc = kम_से_अदीर्घ(buffer+1, 10, &nodक्रमागत);
		अगर (rc)
			वापस rc;
		अगर (clusterip_del_node(c, nodक्रमागत))
			वापस -ENOENT;
	पूर्ण अन्यथा
		वापस -EIO;

	वापस size;
पूर्ण

अटल स्थिर काष्ठा proc_ops clusterip_proc_ops = अणु
	.proc_खोलो	= clusterip_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= clusterip_proc_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= clusterip_proc_release,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल पूर्णांक clusterip_net_init(काष्ठा net *net)
अणु
	काष्ठा clusterip_net *cn = clusterip_pernet(net);
	पूर्णांक ret;

	INIT_LIST_HEAD(&cn->configs);

	spin_lock_init(&cn->lock);

	ret = nf_रेजिस्टर_net_hook(net, &cip_arp_ops);
	अगर (ret < 0)
		वापस ret;

#अगर_घोषित CONFIG_PROC_FS
	cn->procdir = proc_सूची_गढ़ो("ipt_CLUSTERIP", net->proc_net);
	अगर (!cn->procdir) अणु
		nf_unरेजिस्टर_net_hook(net, &cip_arp_ops);
		pr_err("Unable to proc dir entry\n");
		वापस -ENOMEM;
	पूर्ण
	mutex_init(&cn->mutex);
#पूर्ण_अगर /* CONFIG_PROC_FS */

	वापस 0;
पूर्ण

अटल व्योम clusterip_net_निकास(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा clusterip_net *cn = clusterip_pernet(net);

	mutex_lock(&cn->mutex);
	proc_हटाओ(cn->procdir);
	cn->procdir = शून्य;
	mutex_unlock(&cn->mutex);
#पूर्ण_अगर
	nf_unरेजिस्टर_net_hook(net, &cip_arp_ops);
पूर्ण

अटल काष्ठा pernet_operations clusterip_net_ops = अणु
	.init = clusterip_net_init,
	.निकास = clusterip_net_निकास,
	.id   = &clusterip_net_id,
	.size = माप(काष्ठा clusterip_net),
पूर्ण;

अटल काष्ठा notअगरier_block cip_netdev_notअगरier = अणु
	.notअगरier_call = clusterip_netdev_event
पूर्ण;

अटल पूर्णांक __init clusterip_tg_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&clusterip_net_ops);
	अगर (ret < 0)
		वापस ret;

	ret = xt_रेजिस्टर_target(&clusterip_tg_reg);
	अगर (ret < 0)
		जाओ cleanup_subsys;

	ret = रेजिस्टर_netdevice_notअगरier(&cip_netdev_notअगरier);
	अगर (ret < 0)
		जाओ unरेजिस्टर_target;

	pr_info("ClusterIP Version %s loaded successfully\n",
		CLUSTERIP_VERSION);

	वापस 0;

unरेजिस्टर_target:
	xt_unरेजिस्टर_target(&clusterip_tg_reg);
cleanup_subsys:
	unरेजिस्टर_pernet_subsys(&clusterip_net_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास clusterip_tg_निकास(व्योम)
अणु
	pr_info("ClusterIP Version %s unloading\n", CLUSTERIP_VERSION);

	unरेजिस्टर_netdevice_notअगरier(&cip_netdev_notअगरier);
	xt_unरेजिस्टर_target(&clusterip_tg_reg);
	unरेजिस्टर_pernet_subsys(&clusterip_net_ops);

	/* Wait क्रम completion of call_rcu()'s (clusterip_config_rcu_मुक्त) */
	rcu_barrier();
पूर्ण

module_init(clusterip_tg_init);
module_निकास(clusterip_tg_निकास);
