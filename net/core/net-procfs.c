<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <net/wext.h>

#घोषणा BUCKET_SPACE (32 - NETDEV_HASHBITS - 1)

#घोषणा get_bucket(x) ((x) >> BUCKET_SPACE)
#घोषणा get_offset(x) ((x) & ((1 << BUCKET_SPACE) - 1))
#घोषणा set_bucket_offset(b, o) ((b) << BUCKET_SPACE | (o))

अटल अंतरभूत काष्ठा net_device *dev_from_same_bucket(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा net_device *dev;
	काष्ठा hlist_head *h;
	अचिन्हित पूर्णांक count = 0, offset = get_offset(*pos);

	h = &net->dev_index_head[get_bucket(*pos)];
	hlist_क्रम_each_entry_rcu(dev, h, index_hlist) अणु
		अगर (++count == offset)
			वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_device *dev_from_bucket(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक bucket;

	करो अणु
		dev = dev_from_same_bucket(seq, pos);
		अगर (dev)
			वापस dev;

		bucket = get_bucket(*pos) + 1;
		*pos = set_bucket_offset(bucket, 1);
	पूर्ण जबतक (bucket < NETDEV_HASHENTRIES);

	वापस शून्य;
पूर्ण

/*
 *	This is invoked by the /proc fileप्रणाली handler to display a device
 *	in detail.
 */
अटल व्योम *dev_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	अगर (!*pos)
		वापस SEQ_START_TOKEN;

	अगर (get_bucket(*pos) >= NETDEV_HASHENTRIES)
		वापस शून्य;

	वापस dev_from_bucket(seq, pos);
पूर्ण

अटल व्योम *dev_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस dev_from_bucket(seq, pos);
पूर्ण

अटल व्योम dev_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम dev_seq_म_लिखो_stats(काष्ठा seq_file *seq, काष्ठा net_device *dev)
अणु
	काष्ठा rtnl_link_stats64 temp;
	स्थिर काष्ठा rtnl_link_stats64 *stats = dev_get_stats(dev, &temp);

	seq_म_लिखो(seq, "%6s: %7llu %7llu %4llu %4llu %4llu %5llu %10llu %9llu "
		   "%8llu %7llu %4llu %4llu %4llu %5llu %7llu %10llu\n",
		   dev->name, stats->rx_bytes, stats->rx_packets,
		   stats->rx_errors,
		   stats->rx_dropped + stats->rx_missed_errors,
		   stats->rx_fअगरo_errors,
		   stats->rx_length_errors + stats->rx_over_errors +
		    stats->rx_crc_errors + stats->rx_frame_errors,
		   stats->rx_compressed, stats->multicast,
		   stats->tx_bytes, stats->tx_packets,
		   stats->tx_errors, stats->tx_dropped,
		   stats->tx_fअगरo_errors, stats->collisions,
		   stats->tx_carrier_errors +
		    stats->tx_पातed_errors +
		    stats->tx_winकरोw_errors +
		    stats->tx_heartbeat_errors,
		   stats->tx_compressed);
पूर्ण

/*
 *	Called from the PROCfs module. This now uses the new arbitrary sized
 *	/proc/net पूर्णांकerface to create /proc/net/dev
 */
अटल पूर्णांक dev_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "Inter-|   Receive                            "
			      "                    |  Transmit\n"
			      " face |bytes    packets errs drop fifo frame "
			      "compressed multicast|bytes    packets errs "
			      "drop fifo colls carrier compressed\n");
	अन्यथा
		dev_seq_म_लिखो_stats(seq, v);
	वापस 0;
पूर्ण

अटल u32 softnet_backlog_len(काष्ठा softnet_data *sd)
अणु
	वापस skb_queue_len_lockless(&sd->input_pkt_queue) +
	       skb_queue_len_lockless(&sd->process_queue);
पूर्ण

अटल काष्ठा softnet_data *softnet_get_online(loff_t *pos)
अणु
	काष्ठा softnet_data *sd = शून्य;

	जबतक (*pos < nr_cpu_ids)
		अगर (cpu_online(*pos)) अणु
			sd = &per_cpu(softnet_data, *pos);
			अवरोध;
		पूर्ण अन्यथा
			++*pos;
	वापस sd;
पूर्ण

अटल व्योम *softnet_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस softnet_get_online(pos);
पूर्ण

अटल व्योम *softnet_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस softnet_get_online(pos);
पूर्ण

अटल व्योम softnet_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक softnet_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा softnet_data *sd = v;
	अचिन्हित पूर्णांक flow_limit_count = 0;

#अगर_घोषित CONFIG_NET_FLOW_LIMIT
	काष्ठा sd_flow_limit *fl;

	rcu_पढ़ो_lock();
	fl = rcu_dereference(sd->flow_limit);
	अगर (fl)
		flow_limit_count = fl->count;
	rcu_पढ़ो_unlock();
#पूर्ण_अगर

	/* the index is the CPU id owing this sd. Since offline CPUs are not
	 * displayed, it would be othrwise not trivial क्रम the user-space
	 * mapping the data a specअगरic CPU
	 */
	seq_म_लिखो(seq,
		   "%08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x\n",
		   sd->processed, sd->dropped, sd->समय_squeeze, 0,
		   0, 0, 0, 0, /* was fastroute */
		   0,	/* was cpu_collision */
		   sd->received_rps, flow_limit_count,
		   softnet_backlog_len(sd), (पूर्णांक)seq->index);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations dev_seq_ops = अणु
	.start = dev_seq_start,
	.next  = dev_seq_next,
	.stop  = dev_seq_stop,
	.show  = dev_seq_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations softnet_seq_ops = अणु
	.start = softnet_seq_start,
	.next  = softnet_seq_next,
	.stop  = softnet_seq_stop,
	.show  = softnet_seq_show,
पूर्ण;

अटल व्योम *ptype_get_idx(loff_t pos)
अणु
	काष्ठा packet_type *pt = शून्य;
	loff_t i = 0;
	पूर्णांक t;

	list_क्रम_each_entry_rcu(pt, &ptype_all, list) अणु
		अगर (i == pos)
			वापस pt;
		++i;
	पूर्ण

	क्रम (t = 0; t < PTYPE_HASH_SIZE; t++) अणु
		list_क्रम_each_entry_rcu(pt, &ptype_base[t], list) अणु
			अगर (i == pos)
				वापस pt;
			++i;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *ptype_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस *pos ? ptype_get_idx(*pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *ptype_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा packet_type *pt;
	काष्ठा list_head *nxt;
	पूर्णांक hash;

	++*pos;
	अगर (v == SEQ_START_TOKEN)
		वापस ptype_get_idx(0);

	pt = v;
	nxt = pt->list.next;
	अगर (pt->type == htons(ETH_P_ALL)) अणु
		अगर (nxt != &ptype_all)
			जाओ found;
		hash = 0;
		nxt = ptype_base[0].next;
	पूर्ण अन्यथा
		hash = ntohs(pt->type) & PTYPE_HASH_MASK;

	जबतक (nxt == &ptype_base[hash]) अणु
		अगर (++hash >= PTYPE_HASH_SIZE)
			वापस शून्य;
		nxt = ptype_base[hash].next;
	पूर्ण
found:
	वापस list_entry(nxt, काष्ठा packet_type, list);
पूर्ण

अटल व्योम ptype_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक ptype_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा packet_type *pt = v;

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "Type Device      Function\n");
	अन्यथा अगर (pt->dev == शून्य || dev_net(pt->dev) == seq_file_net(seq)) अणु
		अगर (pt->type == htons(ETH_P_ALL))
			seq_माला_दो(seq, "ALL ");
		अन्यथा
			seq_म_लिखो(seq, "%04x", ntohs(pt->type));

		seq_म_लिखो(seq, " %-8s %ps\n",
			   pt->dev ? pt->dev->name : "", pt->func);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ptype_seq_ops = अणु
	.start = ptype_seq_start,
	.next  = ptype_seq_next,
	.stop  = ptype_seq_stop,
	.show  = ptype_seq_show,
पूर्ण;

अटल पूर्णांक __net_init dev_proc_net_init(काष्ठा net *net)
अणु
	पूर्णांक rc = -ENOMEM;

	अगर (!proc_create_net("dev", 0444, net->proc_net, &dev_seq_ops,
			माप(काष्ठा seq_net_निजी)))
		जाओ out;
	अगर (!proc_create_seq("softnet_stat", 0444, net->proc_net,
			 &softnet_seq_ops))
		जाओ out_dev;
	अगर (!proc_create_net("ptype", 0444, net->proc_net, &ptype_seq_ops,
			माप(काष्ठा seq_net_निजी)))
		जाओ out_softnet;

	अगर (wext_proc_init(net))
		जाओ out_ptype;
	rc = 0;
out:
	वापस rc;
out_ptype:
	हटाओ_proc_entry("ptype", net->proc_net);
out_softnet:
	हटाओ_proc_entry("softnet_stat", net->proc_net);
out_dev:
	हटाओ_proc_entry("dev", net->proc_net);
	जाओ out;
पूर्ण

अटल व्योम __net_निकास dev_proc_net_निकास(काष्ठा net *net)
अणु
	wext_proc_निकास(net);

	हटाओ_proc_entry("ptype", net->proc_net);
	हटाओ_proc_entry("softnet_stat", net->proc_net);
	हटाओ_proc_entry("dev", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations __net_initdata dev_proc_ops = अणु
	.init = dev_proc_net_init,
	.निकास = dev_proc_net_निकास,
पूर्ण;

अटल पूर्णांक dev_mc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा netdev_hw_addr *ha;
	काष्ठा net_device *dev = v;

	अगर (v == SEQ_START_TOKEN)
		वापस 0;

	netअगर_addr_lock_bh(dev);
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		seq_म_लिखो(seq, "%-4d %-15s %-5d %-5d %*phN\n",
			   dev->अगरindex, dev->name,
			   ha->refcount, ha->global_use,
			   (पूर्णांक)dev->addr_len, ha->addr);
	पूर्ण
	netअगर_addr_unlock_bh(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations dev_mc_seq_ops = अणु
	.start = dev_seq_start,
	.next  = dev_seq_next,
	.stop  = dev_seq_stop,
	.show  = dev_mc_seq_show,
पूर्ण;

अटल पूर्णांक __net_init dev_mc_net_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net("dev_mcast", 0, net->proc_net, &dev_mc_seq_ops,
			माप(काष्ठा seq_net_निजी)))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास dev_mc_net_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("dev_mcast", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations __net_initdata dev_mc_net_ops = अणु
	.init = dev_mc_net_init,
	.निकास = dev_mc_net_निकास,
पूर्ण;

पूर्णांक __init dev_proc_init(व्योम)
अणु
	पूर्णांक ret = रेजिस्टर_pernet_subsys(&dev_proc_ops);
	अगर (!ret)
		वापस रेजिस्टर_pernet_subsys(&dev_mc_net_ops);
	वापस ret;
पूर्ण
