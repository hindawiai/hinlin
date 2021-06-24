<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 Covalent IO, Inc. http://covalent.io
 */

/* Devmaps primary use is as a backend map क्रम XDP BPF helper call
 * bpf_redirect_map(). Because XDP is mostly concerned with perक्रमmance we
 * spent some efक्रमt to ensure the datapath with redirect maps करोes not use
 * any locking. This is a quick note on the details.
 *
 * We have three possible paths to get पूर्णांकo the devmap control plane bpf
 * syscalls, bpf programs, and driver side xmit/flush operations. A bpf syscall
 * will invoke an update, delete, or lookup operation. To ensure updates and
 * deletes appear atomic from the datapath side xchg() is used to modअगरy the
 * netdev_map array. Then because the datapath करोes a lookup पूर्णांकo the netdev_map
 * array (पढ़ो-only) from an RCU critical section we use call_rcu() to रुको क्रम
 * an rcu grace period beक्रमe मुक्त'ing the old data काष्ठाures. This ensures the
 * datapath always has a valid copy. However, the datapath करोes a "flush"
 * operation that pushes any pending packets in the driver outside the RCU
 * critical section. Each bpf_dtab_netdev tracks these pending operations using
 * a per-cpu flush list. The bpf_dtab_netdev object will not be destroyed  until
 * this list is empty, indicating outstanding flush operations have completed.
 *
 * BPF syscalls may race with BPF program calls on any of the update, delete
 * or lookup operations. As noted above the xchg() operation also keep the
 * netdev_map consistent in this हाल. From the devmap side BPF programs
 * calling पूर्णांकo these operations are the same as multiple user space thपढ़ोs
 * making प्रणाली calls.
 *
 * Finally, any of the above may race with a netdev_unरेजिस्टर notअगरier. The
 * unरेजिस्टर notअगरier must search क्रम net devices in the map काष्ठाure that
 * contain a reference to the net device and हटाओ them. This is a two step
 * process (a) dereference the bpf_dtab_netdev object in netdev_map and (b)
 * check to see अगर the अगरindex is the same as the net_device being हटाओd.
 * When removing the dev a cmpxchg() is used to ensure the correct dev is
 * हटाओd, in the हाल of a concurrent update or delete operation it is
 * possible that the initially referenced dev is no दीर्घer in the map. As the
 * notअगरier hook walks the map we know that new dev references can not be
 * added by the user because core infraकाष्ठाure ensures dev_get_by_index()
 * calls will fail at this poपूर्णांक.
 *
 * The devmap_hash type is a map type which पूर्णांकerprets keys as अगरindexes and
 * indexes these using a hashmap. This allows maps that use अगरindex as key to be
 * densely packed instead of having holes in the lookup array क्रम unused
 * अगरindexes. The setup and packet enqueue/send code is shared between the two
 * types of devmap; only the lookup and insertion is dअगरferent.
 */
#समावेश <linux/bpf.h>
#समावेश <net/xdp.h>
#समावेश <linux/filter.h>
#समावेश <trace/events/xdp.h>

#घोषणा DEV_CREATE_FLAG_MASK \
	(BPF_F_NUMA_NODE | BPF_F_RDONLY | BPF_F_WRONLY)

काष्ठा xdp_dev_bulk_queue अणु
	काष्ठा xdp_frame *q[DEV_MAP_BULK_SIZE];
	काष्ठा list_head flush_node;
	काष्ठा net_device *dev;
	काष्ठा net_device *dev_rx;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा bpf_dtab_netdev अणु
	काष्ठा net_device *dev; /* must be first member, due to tracepoपूर्णांक */
	काष्ठा hlist_node index_hlist;
	काष्ठा bpf_dtab *dtab;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा rcu_head rcu;
	अचिन्हित पूर्णांक idx;
	काष्ठा bpf_devmap_val val;
पूर्ण;

काष्ठा bpf_dtab अणु
	काष्ठा bpf_map map;
	काष्ठा bpf_dtab_netdev **netdev_map; /* DEVMAP type only */
	काष्ठा list_head list;

	/* these are only used क्रम DEVMAP_HASH type maps */
	काष्ठा hlist_head *dev_index_head;
	spinlock_t index_lock;
	अचिन्हित पूर्णांक items;
	u32 n_buckets;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा list_head, dev_flush_list);
अटल DEFINE_SPINLOCK(dev_map_lock);
अटल LIST_HEAD(dev_map_list);

अटल काष्ठा hlist_head *dev_map_create_hash(अचिन्हित पूर्णांक entries,
					      पूर्णांक numa_node)
अणु
	पूर्णांक i;
	काष्ठा hlist_head *hash;

	hash = bpf_map_area_alloc(entries * माप(*hash), numa_node);
	अगर (hash != शून्य)
		क्रम (i = 0; i < entries; i++)
			INIT_HLIST_HEAD(&hash[i]);

	वापस hash;
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *dev_map_index_hash(काष्ठा bpf_dtab *dtab,
						    पूर्णांक idx)
अणु
	वापस &dtab->dev_index_head[idx & (dtab->n_buckets - 1)];
पूर्ण

अटल पूर्णांक dev_map_init_map(काष्ठा bpf_dtab *dtab, जोड़ bpf_attr *attr)
अणु
	u32 valsize = attr->value_size;

	/* check sanity of attributes. 2 value sizes supported:
	 * 4 bytes: अगरindex
	 * 8 bytes: अगरindex + prog fd
	 */
	अगर (attr->max_entries == 0 || attr->key_size != 4 ||
	    (valsize != दुरत्वend(काष्ठा bpf_devmap_val, अगरindex) &&
	     valsize != दुरत्वend(काष्ठा bpf_devmap_val, bpf_prog.fd)) ||
	    attr->map_flags & ~DEV_CREATE_FLAG_MASK)
		वापस -EINVAL;

	/* Lookup वापसs a poपूर्णांकer straight to dev->अगरindex, so make sure the
	 * verअगरier prevents ग_लिखोs from the BPF side
	 */
	attr->map_flags |= BPF_F_RDONLY_PROG;


	bpf_map_init_from_attr(&dtab->map, attr);

	अगर (attr->map_type == BPF_MAP_TYPE_DEVMAP_HASH) अणु
		dtab->n_buckets = roundup_घात_of_two(dtab->map.max_entries);

		अगर (!dtab->n_buckets) /* Overflow check */
			वापस -EINVAL;
	पूर्ण

	अगर (attr->map_type == BPF_MAP_TYPE_DEVMAP_HASH) अणु
		dtab->dev_index_head = dev_map_create_hash(dtab->n_buckets,
							   dtab->map.numa_node);
		अगर (!dtab->dev_index_head)
			वापस -ENOMEM;

		spin_lock_init(&dtab->index_lock);
	पूर्ण अन्यथा अणु
		dtab->netdev_map = bpf_map_area_alloc(dtab->map.max_entries *
						      माप(काष्ठा bpf_dtab_netdev *),
						      dtab->map.numa_node);
		अगर (!dtab->netdev_map)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा bpf_map *dev_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_dtab *dtab;
	पूर्णांक err;

	अगर (!capable(CAP_NET_ADMIN))
		वापस ERR_PTR(-EPERM);

	dtab = kzalloc(माप(*dtab), GFP_USER | __GFP_ACCOUNT);
	अगर (!dtab)
		वापस ERR_PTR(-ENOMEM);

	err = dev_map_init_map(dtab, attr);
	अगर (err) अणु
		kमुक्त(dtab);
		वापस ERR_PTR(err);
	पूर्ण

	spin_lock(&dev_map_lock);
	list_add_tail_rcu(&dtab->list, &dev_map_list);
	spin_unlock(&dev_map_lock);

	वापस &dtab->map;
पूर्ण

अटल व्योम dev_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_dtab *dtab = container_of(map, काष्ठा bpf_dtab, map);
	पूर्णांक i;

	/* At this poपूर्णांक bpf_prog->aux->refcnt == 0 and this map->refcnt == 0,
	 * so the programs (can be more than one that used this map) were
	 * disconnected from events. The following synchronize_rcu() guarantees
	 * both rcu पढ़ो critical sections complete and रुकोs क्रम
	 * preempt-disable regions (NAPI being the relevant context here) so we
	 * are certain there will be no further पढ़ोs against the netdev_map and
	 * all flush operations are complete. Flush operations can only be करोne
	 * from NAPI context क्रम this reason.
	 */

	spin_lock(&dev_map_lock);
	list_del_rcu(&dtab->list);
	spin_unlock(&dev_map_lock);

	synchronize_rcu();

	/* Make sure prior __dev_map_entry_मुक्त() have completed. */
	rcu_barrier();

	अगर (dtab->map.map_type == BPF_MAP_TYPE_DEVMAP_HASH) अणु
		क्रम (i = 0; i < dtab->n_buckets; i++) अणु
			काष्ठा bpf_dtab_netdev *dev;
			काष्ठा hlist_head *head;
			काष्ठा hlist_node *next;

			head = dev_map_index_hash(dtab, i);

			hlist_क्रम_each_entry_safe(dev, next, head, index_hlist) अणु
				hlist_del_rcu(&dev->index_hlist);
				अगर (dev->xdp_prog)
					bpf_prog_put(dev->xdp_prog);
				dev_put(dev->dev);
				kमुक्त(dev);
			पूर्ण
		पूर्ण

		bpf_map_area_मुक्त(dtab->dev_index_head);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < dtab->map.max_entries; i++) अणु
			काष्ठा bpf_dtab_netdev *dev;

			dev = dtab->netdev_map[i];
			अगर (!dev)
				जारी;

			अगर (dev->xdp_prog)
				bpf_prog_put(dev->xdp_prog);
			dev_put(dev->dev);
			kमुक्त(dev);
		पूर्ण

		bpf_map_area_मुक्त(dtab->netdev_map);
	पूर्ण

	kमुक्त(dtab);
पूर्ण

अटल पूर्णांक dev_map_get_next_key(काष्ठा bpf_map *map, व्योम *key, व्योम *next_key)
अणु
	काष्ठा bpf_dtab *dtab = container_of(map, काष्ठा bpf_dtab, map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = next_key;

	अगर (index >= dtab->map.max_entries) अणु
		*next = 0;
		वापस 0;
	पूर्ण

	अगर (index == dtab->map.max_entries - 1)
		वापस -ENOENT;
	*next = index + 1;
	वापस 0;
पूर्ण

अटल व्योम *__dev_map_hash_lookup_elem(काष्ठा bpf_map *map, u32 key)
अणु
	काष्ठा bpf_dtab *dtab = container_of(map, काष्ठा bpf_dtab, map);
	काष्ठा hlist_head *head = dev_map_index_hash(dtab, key);
	काष्ठा bpf_dtab_netdev *dev;

	hlist_क्रम_each_entry_rcu(dev, head, index_hlist,
				 lockdep_is_held(&dtab->index_lock))
		अगर (dev->idx == key)
			वापस dev;

	वापस शून्य;
पूर्ण

अटल पूर्णांक dev_map_hash_get_next_key(काष्ठा bpf_map *map, व्योम *key,
				    व्योम *next_key)
अणु
	काष्ठा bpf_dtab *dtab = container_of(map, काष्ठा bpf_dtab, map);
	u32 idx, *next = next_key;
	काष्ठा bpf_dtab_netdev *dev, *next_dev;
	काष्ठा hlist_head *head;
	पूर्णांक i = 0;

	अगर (!key)
		जाओ find_first;

	idx = *(u32 *)key;

	dev = __dev_map_hash_lookup_elem(map, idx);
	अगर (!dev)
		जाओ find_first;

	next_dev = hlist_entry_safe(rcu_dereference_raw(hlist_next_rcu(&dev->index_hlist)),
				    काष्ठा bpf_dtab_netdev, index_hlist);

	अगर (next_dev) अणु
		*next = next_dev->idx;
		वापस 0;
	पूर्ण

	i = idx & (dtab->n_buckets - 1);
	i++;

 find_first:
	क्रम (; i < dtab->n_buckets; i++) अणु
		head = dev_map_index_hash(dtab, i);

		next_dev = hlist_entry_safe(rcu_dereference_raw(hlist_first_rcu(head)),
					    काष्ठा bpf_dtab_netdev,
					    index_hlist);
		अगर (next_dev) अणु
			*next = next_dev->idx;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

bool dev_map_can_have_prog(काष्ठा bpf_map *map)
अणु
	अगर ((map->map_type == BPF_MAP_TYPE_DEVMAP ||
	     map->map_type == BPF_MAP_TYPE_DEVMAP_HASH) &&
	    map->value_size != दुरत्वend(काष्ठा bpf_devmap_val, अगरindex))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम bq_xmit_all(काष्ठा xdp_dev_bulk_queue *bq, u32 flags)
अणु
	काष्ठा net_device *dev = bq->dev;
	पूर्णांक sent = 0, err = 0;
	पूर्णांक i;

	अगर (unlikely(!bq->count))
		वापस;

	क्रम (i = 0; i < bq->count; i++) अणु
		काष्ठा xdp_frame *xdpf = bq->q[i];

		prefetch(xdpf);
	पूर्ण

	sent = dev->netdev_ops->nकरो_xdp_xmit(dev, bq->count, bq->q, flags);
	अगर (sent < 0) अणु
		/* If nकरो_xdp_xmit fails with an त्रुटि_सं, no frames have
		 * been xmit'ed.
		 */
		err = sent;
		sent = 0;
	पूर्ण

	/* If not all frames have been transmitted, it is our
	 * responsibility to मुक्त them
	 */
	क्रम (i = sent; unlikely(i < bq->count); i++)
		xdp_वापस_frame_rx_napi(bq->q[i]);

	trace_xdp_devmap_xmit(bq->dev_rx, dev, sent, bq->count - sent, err);
	bq->dev_rx = शून्य;
	bq->count = 0;
	__list_del_clearprev(&bq->flush_node);
पूर्ण

/* __dev_flush is called from xdp_करो_flush() which _must_ be संकेतed
 * from the driver beक्रमe वापसing from its napi->poll() routine. The poll()
 * routine is called either from busy_poll context or net_rx_action संकेतed
 * from NET_RX_SOFTIRQ. Either way the poll routine must complete beक्रमe the
 * net device can be torn करोwn. On devmap tear करोwn we ensure the flush list
 * is empty beक्रमe completing to ensure all flush operations have completed.
 * When drivers update the bpf program they may need to ensure any flush ops
 * are also complete. Using synchronize_rcu or call_rcu will suffice क्रम this
 * because both रुको क्रम napi context to निकास.
 */
व्योम __dev_flush(व्योम)
अणु
	काष्ठा list_head *flush_list = this_cpu_ptr(&dev_flush_list);
	काष्ठा xdp_dev_bulk_queue *bq, *पंचांगp;

	list_क्रम_each_entry_safe(bq, पंचांगp, flush_list, flush_node)
		bq_xmit_all(bq, XDP_XMIT_FLUSH);
पूर्ण

/* rcu_पढ़ो_lock (from syscall and BPF contexts) ensures that अगर a delete and/or
 * update happens in parallel here a dev_put wont happen until after पढ़ोing the
 * अगरindex.
 */
अटल व्योम *__dev_map_lookup_elem(काष्ठा bpf_map *map, u32 key)
अणु
	काष्ठा bpf_dtab *dtab = container_of(map, काष्ठा bpf_dtab, map);
	काष्ठा bpf_dtab_netdev *obj;

	अगर (key >= map->max_entries)
		वापस शून्य;

	obj = READ_ONCE(dtab->netdev_map[key]);
	वापस obj;
पूर्ण

/* Runs under RCU-पढ़ो-side, plus in softirq under NAPI protection.
 * Thus, safe percpu variable access.
 */
अटल व्योम bq_enqueue(काष्ठा net_device *dev, काष्ठा xdp_frame *xdpf,
		       काष्ठा net_device *dev_rx)
अणु
	काष्ठा list_head *flush_list = this_cpu_ptr(&dev_flush_list);
	काष्ठा xdp_dev_bulk_queue *bq = this_cpu_ptr(dev->xdp_bulkq);

	अगर (unlikely(bq->count == DEV_MAP_BULK_SIZE))
		bq_xmit_all(bq, 0);

	/* Ingress dev_rx will be the same क्रम all xdp_frame's in
	 * bulk_queue, because bq stored per-CPU and must be flushed
	 * from net_device drivers NAPI func end.
	 */
	अगर (!bq->dev_rx)
		bq->dev_rx = dev_rx;

	bq->q[bq->count++] = xdpf;

	अगर (!bq->flush_node.prev)
		list_add(&bq->flush_node, flush_list);
पूर्ण

अटल अंतरभूत पूर्णांक __xdp_enqueue(काष्ठा net_device *dev, काष्ठा xdp_buff *xdp,
			       काष्ठा net_device *dev_rx)
अणु
	काष्ठा xdp_frame *xdpf;
	पूर्णांक err;

	अगर (!dev->netdev_ops->nकरो_xdp_xmit)
		वापस -EOPNOTSUPP;

	err = xdp_ok_fwd_dev(dev, xdp->data_end - xdp->data);
	अगर (unlikely(err))
		वापस err;

	xdpf = xdp_convert_buff_to_frame(xdp);
	अगर (unlikely(!xdpf))
		वापस -EOVERFLOW;

	bq_enqueue(dev, xdpf, dev_rx);
	वापस 0;
पूर्ण

अटल काष्ठा xdp_buff *dev_map_run_prog(काष्ठा net_device *dev,
					 काष्ठा xdp_buff *xdp,
					 काष्ठा bpf_prog *xdp_prog)
अणु
	काष्ठा xdp_txq_info txq = अणु .dev = dev पूर्ण;
	u32 act;

	xdp_set_data_meta_invalid(xdp);
	xdp->txq = &txq;

	act = bpf_prog_run_xdp(xdp_prog, xdp);
	चयन (act) अणु
	हाल XDP_PASS:
		वापस xdp;
	हाल XDP_DROP:
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(dev, xdp_prog, act);
		अवरोध;
	पूर्ण

	xdp_वापस_buff(xdp);
	वापस शून्य;
पूर्ण

पूर्णांक dev_xdp_enqueue(काष्ठा net_device *dev, काष्ठा xdp_buff *xdp,
		    काष्ठा net_device *dev_rx)
अणु
	वापस __xdp_enqueue(dev, xdp, dev_rx);
पूर्ण

पूर्णांक dev_map_enqueue(काष्ठा bpf_dtab_netdev *dst, काष्ठा xdp_buff *xdp,
		    काष्ठा net_device *dev_rx)
अणु
	काष्ठा net_device *dev = dst->dev;

	अगर (dst->xdp_prog) अणु
		xdp = dev_map_run_prog(dev, xdp, dst->xdp_prog);
		अगर (!xdp)
			वापस 0;
	पूर्ण
	वापस __xdp_enqueue(dev, xdp, dev_rx);
पूर्ण

पूर्णांक dev_map_generic_redirect(काष्ठा bpf_dtab_netdev *dst, काष्ठा sk_buff *skb,
			     काष्ठा bpf_prog *xdp_prog)
अणु
	पूर्णांक err;

	err = xdp_ok_fwd_dev(dst->dev, skb->len);
	अगर (unlikely(err))
		वापस err;
	skb->dev = dst->dev;
	generic_xdp_tx(skb, xdp_prog);

	वापस 0;
पूर्ण

अटल व्योम *dev_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_dtab_netdev *obj = __dev_map_lookup_elem(map, *(u32 *)key);

	वापस obj ? &obj->val : शून्य;
पूर्ण

अटल व्योम *dev_map_hash_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_dtab_netdev *obj = __dev_map_hash_lookup_elem(map,
								*(u32 *)key);
	वापस obj ? &obj->val : शून्य;
पूर्ण

अटल व्योम __dev_map_entry_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा bpf_dtab_netdev *dev;

	dev = container_of(rcu, काष्ठा bpf_dtab_netdev, rcu);
	अगर (dev->xdp_prog)
		bpf_prog_put(dev->xdp_prog);
	dev_put(dev->dev);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक dev_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_dtab *dtab = container_of(map, काष्ठा bpf_dtab, map);
	काष्ठा bpf_dtab_netdev *old_dev;
	पूर्णांक k = *(u32 *)key;

	अगर (k >= map->max_entries)
		वापस -EINVAL;

	/* Use call_rcu() here to ensure any rcu critical sections have
	 * completed as well as any flush operations because call_rcu
	 * will रुको क्रम preempt-disable region to complete, NAPI in this
	 * context.  And additionally, the driver tear करोwn ensures all
	 * soft irqs are complete beक्रमe removing the net device in the
	 * हाल of dev_put equals zero.
	 */
	old_dev = xchg(&dtab->netdev_map[k], शून्य);
	अगर (old_dev)
		call_rcu(&old_dev->rcu, __dev_map_entry_मुक्त);
	वापस 0;
पूर्ण

अटल पूर्णांक dev_map_hash_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_dtab *dtab = container_of(map, काष्ठा bpf_dtab, map);
	काष्ठा bpf_dtab_netdev *old_dev;
	पूर्णांक k = *(u32 *)key;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENOENT;

	spin_lock_irqsave(&dtab->index_lock, flags);

	old_dev = __dev_map_hash_lookup_elem(map, k);
	अगर (old_dev) अणु
		dtab->items--;
		hlist_del_init_rcu(&old_dev->index_hlist);
		call_rcu(&old_dev->rcu, __dev_map_entry_मुक्त);
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&dtab->index_lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा bpf_dtab_netdev *__dev_map_alloc_node(काष्ठा net *net,
						    काष्ठा bpf_dtab *dtab,
						    काष्ठा bpf_devmap_val *val,
						    अचिन्हित पूर्णांक idx)
अणु
	काष्ठा bpf_prog *prog = शून्य;
	काष्ठा bpf_dtab_netdev *dev;

	dev = bpf_map_kदो_स्मृति_node(&dtab->map, माप(*dev),
				   GFP_ATOMIC | __GFP_NOWARN,
				   dtab->map.numa_node);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	dev->dev = dev_get_by_index(net, val->अगरindex);
	अगर (!dev->dev)
		जाओ err_out;

	अगर (val->bpf_prog.fd > 0) अणु
		prog = bpf_prog_get_type_dev(val->bpf_prog.fd,
					     BPF_PROG_TYPE_XDP, false);
		अगर (IS_ERR(prog))
			जाओ err_put_dev;
		अगर (prog->expected_attach_type != BPF_XDP_DEVMAP)
			जाओ err_put_prog;
	पूर्ण

	dev->idx = idx;
	dev->dtab = dtab;
	अगर (prog) अणु
		dev->xdp_prog = prog;
		dev->val.bpf_prog.id = prog->aux->id;
	पूर्ण अन्यथा अणु
		dev->xdp_prog = शून्य;
		dev->val.bpf_prog.id = 0;
	पूर्ण
	dev->val.अगरindex = val->अगरindex;

	वापस dev;
err_put_prog:
	bpf_prog_put(prog);
err_put_dev:
	dev_put(dev->dev);
err_out:
	kमुक्त(dev);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक __dev_map_update_elem(काष्ठा net *net, काष्ठा bpf_map *map,
				 व्योम *key, व्योम *value, u64 map_flags)
अणु
	काष्ठा bpf_dtab *dtab = container_of(map, काष्ठा bpf_dtab, map);
	काष्ठा bpf_dtab_netdev *dev, *old_dev;
	काष्ठा bpf_devmap_val val = अणुपूर्ण;
	u32 i = *(u32 *)key;

	अगर (unlikely(map_flags > BPF_EXIST))
		वापस -EINVAL;
	अगर (unlikely(i >= dtab->map.max_entries))
		वापस -E2BIG;
	अगर (unlikely(map_flags == BPF_NOEXIST))
		वापस -EEXIST;

	/* alपढ़ोy verअगरied value_size <= माप val */
	स_नकल(&val, value, map->value_size);

	अगर (!val.अगरindex) अणु
		dev = शून्य;
		/* can not specअगरy fd अगर अगरindex is 0 */
		अगर (val.bpf_prog.fd > 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		dev = __dev_map_alloc_node(net, dtab, &val, i);
		अगर (IS_ERR(dev))
			वापस PTR_ERR(dev);
	पूर्ण

	/* Use call_rcu() here to ensure rcu critical sections have completed
	 * Remembering the driver side flush operation will happen beक्रमe the
	 * net device is हटाओd.
	 */
	old_dev = xchg(&dtab->netdev_map[i], dev);
	अगर (old_dev)
		call_rcu(&old_dev->rcu, __dev_map_entry_मुक्त);

	वापस 0;
पूर्ण

अटल पूर्णांक dev_map_update_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
			       u64 map_flags)
अणु
	वापस __dev_map_update_elem(current->nsproxy->net_ns,
				     map, key, value, map_flags);
पूर्ण

अटल पूर्णांक __dev_map_hash_update_elem(काष्ठा net *net, काष्ठा bpf_map *map,
				     व्योम *key, व्योम *value, u64 map_flags)
अणु
	काष्ठा bpf_dtab *dtab = container_of(map, काष्ठा bpf_dtab, map);
	काष्ठा bpf_dtab_netdev *dev, *old_dev;
	काष्ठा bpf_devmap_val val = अणुपूर्ण;
	u32 idx = *(u32 *)key;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EEXIST;

	/* alपढ़ोy verअगरied value_size <= माप val */
	स_नकल(&val, value, map->value_size);

	अगर (unlikely(map_flags > BPF_EXIST || !val.अगरindex))
		वापस -EINVAL;

	spin_lock_irqsave(&dtab->index_lock, flags);

	old_dev = __dev_map_hash_lookup_elem(map, idx);
	अगर (old_dev && (map_flags & BPF_NOEXIST))
		जाओ out_err;

	dev = __dev_map_alloc_node(net, dtab, &val, idx);
	अगर (IS_ERR(dev)) अणु
		err = PTR_ERR(dev);
		जाओ out_err;
	पूर्ण

	अगर (old_dev) अणु
		hlist_del_rcu(&old_dev->index_hlist);
	पूर्ण अन्यथा अणु
		अगर (dtab->items >= dtab->map.max_entries) अणु
			spin_unlock_irqrestore(&dtab->index_lock, flags);
			call_rcu(&dev->rcu, __dev_map_entry_मुक्त);
			वापस -E2BIG;
		पूर्ण
		dtab->items++;
	पूर्ण

	hlist_add_head_rcu(&dev->index_hlist,
			   dev_map_index_hash(dtab, idx));
	spin_unlock_irqrestore(&dtab->index_lock, flags);

	अगर (old_dev)
		call_rcu(&old_dev->rcu, __dev_map_entry_मुक्त);

	वापस 0;

out_err:
	spin_unlock_irqrestore(&dtab->index_lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक dev_map_hash_update_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
				   u64 map_flags)
अणु
	वापस __dev_map_hash_update_elem(current->nsproxy->net_ns,
					 map, key, value, map_flags);
पूर्ण

अटल पूर्णांक dev_map_redirect(काष्ठा bpf_map *map, u32 अगरindex, u64 flags)
अणु
	वापस __bpf_xdp_redirect_map(map, अगरindex, flags, __dev_map_lookup_elem);
पूर्ण

अटल पूर्णांक dev_hash_map_redirect(काष्ठा bpf_map *map, u32 अगरindex, u64 flags)
अणु
	वापस __bpf_xdp_redirect_map(map, अगरindex, flags, __dev_map_hash_lookup_elem);
पूर्ण

अटल पूर्णांक dev_map_btf_id;
स्थिर काष्ठा bpf_map_ops dev_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc = dev_map_alloc,
	.map_मुक्त = dev_map_मुक्त,
	.map_get_next_key = dev_map_get_next_key,
	.map_lookup_elem = dev_map_lookup_elem,
	.map_update_elem = dev_map_update_elem,
	.map_delete_elem = dev_map_delete_elem,
	.map_check_btf = map_check_no_btf,
	.map_btf_name = "bpf_dtab",
	.map_btf_id = &dev_map_btf_id,
	.map_redirect = dev_map_redirect,
पूर्ण;

अटल पूर्णांक dev_map_hash_map_btf_id;
स्थिर काष्ठा bpf_map_ops dev_map_hash_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc = dev_map_alloc,
	.map_मुक्त = dev_map_मुक्त,
	.map_get_next_key = dev_map_hash_get_next_key,
	.map_lookup_elem = dev_map_hash_lookup_elem,
	.map_update_elem = dev_map_hash_update_elem,
	.map_delete_elem = dev_map_hash_delete_elem,
	.map_check_btf = map_check_no_btf,
	.map_btf_name = "bpf_dtab",
	.map_btf_id = &dev_map_hash_map_btf_id,
	.map_redirect = dev_hash_map_redirect,
पूर्ण;

अटल व्योम dev_map_hash_हटाओ_netdev(काष्ठा bpf_dtab *dtab,
				       काष्ठा net_device *netdev)
अणु
	अचिन्हित दीर्घ flags;
	u32 i;

	spin_lock_irqsave(&dtab->index_lock, flags);
	क्रम (i = 0; i < dtab->n_buckets; i++) अणु
		काष्ठा bpf_dtab_netdev *dev;
		काष्ठा hlist_head *head;
		काष्ठा hlist_node *next;

		head = dev_map_index_hash(dtab, i);

		hlist_क्रम_each_entry_safe(dev, next, head, index_hlist) अणु
			अगर (netdev != dev->dev)
				जारी;

			dtab->items--;
			hlist_del_rcu(&dev->index_hlist);
			call_rcu(&dev->rcu, __dev_map_entry_मुक्त);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dtab->index_lock, flags);
पूर्ण

अटल पूर्णांक dev_map_notअगरication(काष्ठा notअगरier_block *notअगरier,
				uदीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा bpf_dtab *dtab;
	पूर्णांक i, cpu;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		अगर (!netdev->netdev_ops->nकरो_xdp_xmit || netdev->xdp_bulkq)
			अवरोध;

		/* will be मुक्तd in मुक्त_netdev() */
		netdev->xdp_bulkq = alloc_percpu(काष्ठा xdp_dev_bulk_queue);
		अगर (!netdev->xdp_bulkq)
			वापस NOTIFY_BAD;

		क्रम_each_possible_cpu(cpu)
			per_cpu_ptr(netdev->xdp_bulkq, cpu)->dev = netdev;
		अवरोध;
	हाल NETDEV_UNREGISTER:
		/* This rcu_पढ़ो_lock/unlock pair is needed because
		 * dev_map_list is an RCU list AND to ensure a delete
		 * operation करोes not मुक्त a netdev_map entry जबतक we
		 * are comparing it against the netdev being unरेजिस्टरed.
		 */
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(dtab, &dev_map_list, list) अणु
			अगर (dtab->map.map_type == BPF_MAP_TYPE_DEVMAP_HASH) अणु
				dev_map_hash_हटाओ_netdev(dtab, netdev);
				जारी;
			पूर्ण

			क्रम (i = 0; i < dtab->map.max_entries; i++) अणु
				काष्ठा bpf_dtab_netdev *dev, *odev;

				dev = READ_ONCE(dtab->netdev_map[i]);
				अगर (!dev || netdev != dev->dev)
					जारी;
				odev = cmpxchg(&dtab->netdev_map[i], dev, शून्य);
				अगर (dev == odev)
					call_rcu(&dev->rcu,
						 __dev_map_entry_मुक्त);
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block dev_map_notअगरier = अणु
	.notअगरier_call = dev_map_notअगरication,
पूर्ण;

अटल पूर्णांक __init dev_map_init(व्योम)
अणु
	पूर्णांक cpu;

	/* Assure tracepoपूर्णांक shaकरोw काष्ठा _bpf_dtab_netdev is in sync */
	BUILD_BUG_ON(दुरत्व(काष्ठा bpf_dtab_netdev, dev) !=
		     दुरत्व(काष्ठा _bpf_dtab_netdev, dev));
	रेजिस्टर_netdevice_notअगरier(&dev_map_notअगरier);

	क्रम_each_possible_cpu(cpu)
		INIT_LIST_HEAD(&per_cpu(dev_flush_list, cpu));
	वापस 0;
पूर्ण

subsys_initcall(dev_map_init);
