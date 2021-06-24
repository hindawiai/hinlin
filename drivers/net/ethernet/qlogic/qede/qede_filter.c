<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qede NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/udp_tunnel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/qed/qed_अगर.h>
#समावेश "qede.h"

#घोषणा QEDE_FILTER_PRपूर्णांक_उच्च_LEN	(64)
काष्ठा qede_arfs_tuple अणु
	जोड़ अणु
		__be32 src_ipv4;
		काष्ठा in6_addr src_ipv6;
	पूर्ण;
	जोड़ अणु
		__be32 dst_ipv4;
		काष्ठा in6_addr dst_ipv6;
	पूर्ण;
	__be16  src_port;
	__be16  dst_port;
	__be16  eth_proto;
	u8      ip_proto;

	/* Describe filtering mode needed क्रम this kind of filter */
	क्रमागत qed_filter_config_mode mode;

	/* Used to compare new/old filters. Return true अगर IPs match */
	bool (*ip_comp)(काष्ठा qede_arfs_tuple *a, काष्ठा qede_arfs_tuple *b);

	/* Given an address पूर्णांकo ethhdr build a header from tuple info */
	व्योम (*build_hdr)(काष्ठा qede_arfs_tuple *t, व्योम *header);

	/* Stringअगरy the tuple क्रम a prपूर्णांक पूर्णांकo the provided buffer */
	व्योम (*stringअगरy)(काष्ठा qede_arfs_tuple *t, व्योम *buffer);
पूर्ण;

काष्ठा qede_arfs_fltr_node अणु
#घोषणा QEDE_FLTR_VALID	 0
	अचिन्हित दीर्घ state;

	/* poपूर्णांकer to aRFS packet buffer */
	व्योम *data;

	/* dma map address of aRFS packet buffer */
	dma_addr_t mapping;

	/* length of aRFS packet buffer */
	पूर्णांक buf_len;

	/* tuples to hold from aRFS packet buffer */
	काष्ठा qede_arfs_tuple tuple;

	u32 flow_id;
	u64 sw_id;
	u16 rxq_id;
	u16 next_rxq_id;
	u8 vfid;
	bool filter_op;
	bool used;
	u8 fw_rc;
	bool b_is_drop;
	काष्ठा hlist_node node;
पूर्ण;

काष्ठा qede_arfs अणु
#घोषणा QEDE_ARFS_BUCKET_HEAD(edev, idx) (&(edev)->arfs->arfs_hl_head[idx])
#घोषणा QEDE_ARFS_POLL_COUNT	100
#घोषणा QEDE_RFS_FLW_BITSHIFT	(4)
#घोषणा QEDE_RFS_FLW_MASK	((1 << QEDE_RFS_FLW_BITSHIFT) - 1)
	काष्ठा hlist_head	arfs_hl_head[1 << QEDE_RFS_FLW_BITSHIFT];

	/* lock क्रम filter list access */
	spinlock_t		arfs_list_lock;
	अचिन्हित दीर्घ		*arfs_fltr_bmap;
	पूर्णांक			filter_count;

	/* Currently configured filtering mode */
	क्रमागत qed_filter_config_mode mode;
पूर्ण;

अटल व्योम qede_configure_arfs_fltr(काष्ठा qede_dev *edev,
				     काष्ठा qede_arfs_fltr_node *n,
				     u16 rxq_id, bool add_fltr)
अणु
	स्थिर काष्ठा qed_eth_ops *op = edev->ops;
	काष्ठा qed_ntuple_filter_params params;

	अगर (n->used)
		वापस;

	स_रखो(&params, 0, माप(params));

	params.addr = n->mapping;
	params.length = n->buf_len;
	params.qid = rxq_id;
	params.b_is_add = add_fltr;
	params.b_is_drop = n->b_is_drop;

	अगर (n->vfid) अणु
		params.b_is_vf = true;
		params.vf_id = n->vfid - 1;
	पूर्ण

	अगर (n->tuple.stringअगरy) अणु
		अक्षर tuple_buffer[QEDE_FILTER_PRपूर्णांक_उच्च_LEN];

		n->tuple.stringअगरy(&n->tuple, tuple_buffer);
		DP_VERBOSE(edev, NETIF_MSG_RX_STATUS,
			   "%s sw_id[0x%llx]: %s [vf %u queue %d]\n",
			   add_fltr ? "Adding" : "Deleting",
			   n->sw_id, tuple_buffer, n->vfid, rxq_id);
	पूर्ण

	n->used = true;
	n->filter_op = add_fltr;
	op->ntuple_filter_config(edev->cdev, n, &params);
पूर्ण

अटल व्योम
qede_मुक्त_arfs_filter(काष्ठा qede_dev *edev,  काष्ठा qede_arfs_fltr_node *fltr)
अणु
	kमुक्त(fltr->data);

	अगर (fltr->sw_id < QEDE_RFS_MAX_FLTR)
		clear_bit(fltr->sw_id, edev->arfs->arfs_fltr_bmap);

	kमुक्त(fltr);
पूर्ण

अटल पूर्णांक
qede_enqueue_fltr_and_config_searcher(काष्ठा qede_dev *edev,
				      काष्ठा qede_arfs_fltr_node *fltr,
				      u16 bucket_idx)
अणु
	fltr->mapping = dma_map_single(&edev->pdev->dev, fltr->data,
				       fltr->buf_len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&edev->pdev->dev, fltr->mapping)) अणु
		DP_NOTICE(edev, "Failed to map DMA memory for rule\n");
		qede_मुक्त_arfs_filter(edev, fltr);
		वापस -ENOMEM;
	पूर्ण

	INIT_HLIST_NODE(&fltr->node);
	hlist_add_head(&fltr->node,
		       QEDE_ARFS_BUCKET_HEAD(edev, bucket_idx));

	edev->arfs->filter_count++;
	अगर (edev->arfs->filter_count == 1 &&
	    edev->arfs->mode == QED_FILTER_CONFIG_MODE_DISABLE) अणु
		edev->ops->configure_arfs_searcher(edev->cdev,
						   fltr->tuple.mode);
		edev->arfs->mode = fltr->tuple.mode;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
qede_dequeue_fltr_and_config_searcher(काष्ठा qede_dev *edev,
				      काष्ठा qede_arfs_fltr_node *fltr)
अणु
	hlist_del(&fltr->node);
	dma_unmap_single(&edev->pdev->dev, fltr->mapping,
			 fltr->buf_len, DMA_TO_DEVICE);

	qede_मुक्त_arfs_filter(edev, fltr);

	edev->arfs->filter_count--;
	अगर (!edev->arfs->filter_count &&
	    edev->arfs->mode != QED_FILTER_CONFIG_MODE_DISABLE) अणु
		क्रमागत qed_filter_config_mode mode;

		mode = QED_FILTER_CONFIG_MODE_DISABLE;
		edev->ops->configure_arfs_searcher(edev->cdev, mode);
		edev->arfs->mode = QED_FILTER_CONFIG_MODE_DISABLE;
	पूर्ण
पूर्ण

व्योम qede_arfs_filter_op(व्योम *dev, व्योम *filter, u8 fw_rc)
अणु
	काष्ठा qede_arfs_fltr_node *fltr = filter;
	काष्ठा qede_dev *edev = dev;

	fltr->fw_rc = fw_rc;

	अगर (fw_rc) अणु
		DP_NOTICE(edev,
			  "Failed arfs filter configuration fw_rc=%d, flow_id=%d, sw_id=0x%llx, src_port=%d, dst_port=%d, rxq=%d\n",
			  fw_rc, fltr->flow_id, fltr->sw_id,
			  ntohs(fltr->tuple.src_port),
			  ntohs(fltr->tuple.dst_port), fltr->rxq_id);

		spin_lock_bh(&edev->arfs->arfs_list_lock);

		fltr->used = false;
		clear_bit(QEDE_FLTR_VALID, &fltr->state);

		spin_unlock_bh(&edev->arfs->arfs_list_lock);
		वापस;
	पूर्ण

	spin_lock_bh(&edev->arfs->arfs_list_lock);

	fltr->used = false;

	अगर (fltr->filter_op) अणु
		set_bit(QEDE_FLTR_VALID, &fltr->state);
		अगर (fltr->rxq_id != fltr->next_rxq_id)
			qede_configure_arfs_fltr(edev, fltr, fltr->rxq_id,
						 false);
	पूर्ण अन्यथा अणु
		clear_bit(QEDE_FLTR_VALID, &fltr->state);
		अगर (fltr->rxq_id != fltr->next_rxq_id) अणु
			fltr->rxq_id = fltr->next_rxq_id;
			qede_configure_arfs_fltr(edev, fltr,
						 fltr->rxq_id, true);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&edev->arfs->arfs_list_lock);
पूर्ण

/* Should be called जबतक qede_lock is held */
व्योम qede_process_arfs_filters(काष्ठा qede_dev *edev, bool मुक्त_fltr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= QEDE_RFS_FLW_MASK; i++) अणु
		काष्ठा hlist_node *temp;
		काष्ठा hlist_head *head;
		काष्ठा qede_arfs_fltr_node *fltr;

		head = &edev->arfs->arfs_hl_head[i];

		hlist_क्रम_each_entry_safe(fltr, temp, head, node) अणु
			bool del = false;

			अगर (edev->state != QEDE_STATE_OPEN)
				del = true;

			spin_lock_bh(&edev->arfs->arfs_list_lock);

			अगर ((!test_bit(QEDE_FLTR_VALID, &fltr->state) &&
			     !fltr->used) || मुक्त_fltr) अणु
				qede_dequeue_fltr_and_config_searcher(edev,
								      fltr);
			पूर्ण अन्यथा अणु
				bool flow_exp = false;
#अगर_घोषित CONFIG_RFS_ACCEL
				flow_exp = rps_may_expire_flow(edev->ndev,
							       fltr->rxq_id,
							       fltr->flow_id,
							       fltr->sw_id);
#पूर्ण_अगर
				अगर ((flow_exp || del) && !मुक्त_fltr)
					qede_configure_arfs_fltr(edev, fltr,
								 fltr->rxq_id,
								 false);
			पूर्ण

			spin_unlock_bh(&edev->arfs->arfs_list_lock);
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
	spin_lock_bh(&edev->arfs->arfs_list_lock);

	अगर (edev->arfs->filter_count) अणु
		set_bit(QEDE_SP_ARFS_CONFIG, &edev->sp_flags);
		schedule_delayed_work(&edev->sp_task,
				      QEDE_SP_TASK_POLL_DELAY);
	पूर्ण

	spin_unlock_bh(&edev->arfs->arfs_list_lock);
#पूर्ण_अगर
पूर्ण

/* This function रुकोs until all aRFS filters get deleted and मुक्तd.
 * On समयout it मुक्तs all filters क्रमcefully.
 */
व्योम qede_poll_क्रम_मुक्तing_arfs_filters(काष्ठा qede_dev *edev)
अणु
	पूर्णांक count = QEDE_ARFS_POLL_COUNT;

	जबतक (count) अणु
		qede_process_arfs_filters(edev, false);

		अगर (!edev->arfs->filter_count)
			अवरोध;

		msleep(100);
		count--;
	पूर्ण

	अगर (!count) अणु
		DP_NOTICE(edev, "Timeout in polling for arfs filter free\n");

		/* Something is terribly wrong, मुक्त क्रमcefully */
		qede_process_arfs_filters(edev, true);
	पूर्ण
पूर्ण

पूर्णांक qede_alloc_arfs(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i;

	अगर (!edev->dev_info.common.b_arfs_capable)
		वापस -EINVAL;

	edev->arfs = vzalloc(माप(*edev->arfs));
	अगर (!edev->arfs)
		वापस -ENOMEM;

	spin_lock_init(&edev->arfs->arfs_list_lock);

	क्रम (i = 0; i <= QEDE_RFS_FLW_MASK; i++)
		INIT_HLIST_HEAD(QEDE_ARFS_BUCKET_HEAD(edev, i));

	edev->arfs->arfs_fltr_bmap =
		vzalloc(array_size(माप(दीर्घ),
				   BITS_TO_LONGS(QEDE_RFS_MAX_FLTR)));
	अगर (!edev->arfs->arfs_fltr_bmap) अणु
		vमुक्त(edev->arfs);
		edev->arfs = शून्य;
		वापस -ENOMEM;
	पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
	edev->ndev->rx_cpu_rmap = alloc_irq_cpu_rmap(QEDE_RSS_COUNT(edev));
	अगर (!edev->ndev->rx_cpu_rmap) अणु
		vमुक्त(edev->arfs->arfs_fltr_bmap);
		edev->arfs->arfs_fltr_bmap = शून्य;
		vमुक्त(edev->arfs);
		edev->arfs = शून्य;
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम qede_मुक्त_arfs(काष्ठा qede_dev *edev)
अणु
	अगर (!edev->arfs)
		वापस;

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर (edev->ndev->rx_cpu_rmap)
		मुक्त_irq_cpu_rmap(edev->ndev->rx_cpu_rmap);

	edev->ndev->rx_cpu_rmap = शून्य;
#पूर्ण_अगर
	vमुक्त(edev->arfs->arfs_fltr_bmap);
	edev->arfs->arfs_fltr_bmap = शून्य;
	vमुक्त(edev->arfs);
	edev->arfs = शून्य;
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
अटल bool qede_compare_ip_addr(काष्ठा qede_arfs_fltr_node *tpos,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		अगर (tpos->tuple.src_ipv4 == ip_hdr(skb)->saddr &&
		    tpos->tuple.dst_ipv4 == ip_hdr(skb)->daddr)
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण अन्यथा अणु
		काष्ठा in6_addr *src = &tpos->tuple.src_ipv6;
		u8 size = माप(काष्ठा in6_addr);

		अगर (!स_भेद(src, &ipv6_hdr(skb)->saddr, size) &&
		    !स_भेद(&tpos->tuple.dst_ipv6, &ipv6_hdr(skb)->daddr, size))
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा qede_arfs_fltr_node *
qede_arfs_htbl_key_search(काष्ठा hlist_head *h, स्थिर काष्ठा sk_buff *skb,
			  __be16 src_port, __be16 dst_port, u8 ip_proto)
अणु
	काष्ठा qede_arfs_fltr_node *tpos;

	hlist_क्रम_each_entry(tpos, h, node)
		अगर (tpos->tuple.ip_proto == ip_proto &&
		    tpos->tuple.eth_proto == skb->protocol &&
		    qede_compare_ip_addr(tpos, skb) &&
		    tpos->tuple.src_port == src_port &&
		    tpos->tuple.dst_port == dst_port)
			वापस tpos;

	वापस शून्य;
पूर्ण

अटल काष्ठा qede_arfs_fltr_node *
qede_alloc_filter(काष्ठा qede_dev *edev, पूर्णांक min_hlen)
अणु
	काष्ठा qede_arfs_fltr_node *n;
	पूर्णांक bit_id;

	bit_id = find_first_zero_bit(edev->arfs->arfs_fltr_bmap,
				     QEDE_RFS_MAX_FLTR);

	अगर (bit_id >= QEDE_RFS_MAX_FLTR)
		वापस शून्य;

	n = kzalloc(माप(*n), GFP_ATOMIC);
	अगर (!n)
		वापस शून्य;

	n->data = kzalloc(min_hlen, GFP_ATOMIC);
	अगर (!n->data) अणु
		kमुक्त(n);
		वापस शून्य;
	पूर्ण

	n->sw_id = (u16)bit_id;
	set_bit(bit_id, edev->arfs->arfs_fltr_bmap);
	वापस n;
पूर्ण

पूर्णांक qede_rx_flow_steer(काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb,
		       u16 rxq_index, u32 flow_id)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qede_arfs_fltr_node *n;
	पूर्णांक min_hlen, rc, tp_offset;
	काष्ठा ethhdr *eth;
	__be16 *ports;
	u16 tbl_idx;
	u8 ip_proto;

	अगर (skb->encapsulation)
		वापस -EPROTONOSUPPORT;

	अगर (skb->protocol != htons(ETH_P_IP) &&
	    skb->protocol != htons(ETH_P_IPV6))
		वापस -EPROTONOSUPPORT;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		ip_proto = ip_hdr(skb)->protocol;
		tp_offset = माप(काष्ठा iphdr);
	पूर्ण अन्यथा अणु
		ip_proto = ipv6_hdr(skb)->nexthdr;
		tp_offset = माप(काष्ठा ipv6hdr);
	पूर्ण

	अगर (ip_proto != IPPROTO_TCP && ip_proto != IPPROTO_UDP)
		वापस -EPROTONOSUPPORT;

	ports = (__be16 *)(skb->data + tp_offset);
	tbl_idx = skb_get_hash_raw(skb) & QEDE_RFS_FLW_MASK;

	spin_lock_bh(&edev->arfs->arfs_list_lock);

	n = qede_arfs_htbl_key_search(QEDE_ARFS_BUCKET_HEAD(edev, tbl_idx),
				      skb, ports[0], ports[1], ip_proto);
	अगर (n) अणु
		/* Filter match */
		n->next_rxq_id = rxq_index;

		अगर (test_bit(QEDE_FLTR_VALID, &n->state)) अणु
			अगर (n->rxq_id != rxq_index)
				qede_configure_arfs_fltr(edev, n, n->rxq_id,
							 false);
		पूर्ण अन्यथा अणु
			अगर (!n->used) अणु
				n->rxq_id = rxq_index;
				qede_configure_arfs_fltr(edev, n, n->rxq_id,
							 true);
			पूर्ण
		पूर्ण

		rc = n->sw_id;
		जाओ ret_unlock;
	पूर्ण

	min_hlen = ETH_HLEN + skb_headlen(skb);

	n = qede_alloc_filter(edev, min_hlen);
	अगर (!n) अणु
		rc = -ENOMEM;
		जाओ ret_unlock;
	पूर्ण

	n->buf_len = min_hlen;
	n->rxq_id = rxq_index;
	n->next_rxq_id = rxq_index;
	n->tuple.src_port = ports[0];
	n->tuple.dst_port = ports[1];
	n->flow_id = flow_id;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		n->tuple.src_ipv4 = ip_hdr(skb)->saddr;
		n->tuple.dst_ipv4 = ip_hdr(skb)->daddr;
	पूर्ण अन्यथा अणु
		स_नकल(&n->tuple.src_ipv6, &ipv6_hdr(skb)->saddr,
		       माप(काष्ठा in6_addr));
		स_नकल(&n->tuple.dst_ipv6, &ipv6_hdr(skb)->daddr,
		       माप(काष्ठा in6_addr));
	पूर्ण

	eth = (काष्ठा ethhdr *)n->data;
	eth->h_proto = skb->protocol;
	n->tuple.eth_proto = skb->protocol;
	n->tuple.ip_proto = ip_proto;
	n->tuple.mode = QED_FILTER_CONFIG_MODE_5_TUPLE;
	स_नकल(n->data + ETH_HLEN, skb->data, skb_headlen(skb));

	rc = qede_enqueue_fltr_and_config_searcher(edev, n, tbl_idx);
	अगर (rc)
		जाओ ret_unlock;

	qede_configure_arfs_fltr(edev, n, n->rxq_id, true);

	spin_unlock_bh(&edev->arfs->arfs_list_lock);

	set_bit(QEDE_SP_ARFS_CONFIG, &edev->sp_flags);
	schedule_delayed_work(&edev->sp_task, 0);

	वापस n->sw_id;

ret_unlock:
	spin_unlock_bh(&edev->arfs->arfs_list_lock);
	वापस rc;
पूर्ण
#पूर्ण_अगर

व्योम qede_udp_ports_update(व्योम *dev, u16 vxlan_port, u16 geneve_port)
अणु
	काष्ठा qede_dev *edev = dev;

	अगर (edev->vxlan_dst_port != vxlan_port)
		edev->vxlan_dst_port = 0;

	अगर (edev->geneve_dst_port != geneve_port)
		edev->geneve_dst_port = 0;
पूर्ण

व्योम qede_क्रमce_mac(व्योम *dev, u8 *mac, bool क्रमced)
अणु
	काष्ठा qede_dev *edev = dev;

	__qede_lock(edev);

	अगर (!is_valid_ether_addr(mac)) अणु
		__qede_unlock(edev);
		वापस;
	पूर्ण

	ether_addr_copy(edev->ndev->dev_addr, mac);
	__qede_unlock(edev);
पूर्ण

व्योम qede_fill_rss_params(काष्ठा qede_dev *edev,
			  काष्ठा qed_update_vport_rss_params *rss, u8 *update)
अणु
	bool need_reset = false;
	पूर्णांक i;

	अगर (QEDE_RSS_COUNT(edev) <= 1) अणु
		स_रखो(rss, 0, माप(*rss));
		*update = 0;
		वापस;
	पूर्ण

	/* Need to validate current RSS config uses valid entries */
	क्रम (i = 0; i < QED_RSS_IND_TABLE_SIZE; i++) अणु
		अगर (edev->rss_ind_table[i] >= QEDE_RSS_COUNT(edev)) अणु
			need_reset = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!(edev->rss_params_inited & QEDE_RSS_INसूची_INITED) || need_reset) अणु
		क्रम (i = 0; i < QED_RSS_IND_TABLE_SIZE; i++) अणु
			u16 indir_val, val;

			val = QEDE_RSS_COUNT(edev);
			indir_val = ethtool_rxfh_indir_शेष(i, val);
			edev->rss_ind_table[i] = indir_val;
		पूर्ण
		edev->rss_params_inited |= QEDE_RSS_INसूची_INITED;
	पूर्ण

	/* Now that we have the queue-indirection, prepare the handles */
	क्रम (i = 0; i < QED_RSS_IND_TABLE_SIZE; i++) अणु
		u16 idx = QEDE_RX_QUEUE_IDX(edev, edev->rss_ind_table[i]);

		rss->rss_ind_table[i] = edev->fp_array[idx].rxq->handle;
	पूर्ण

	अगर (!(edev->rss_params_inited & QEDE_RSS_KEY_INITED)) अणु
		netdev_rss_key_fill(edev->rss_key, माप(edev->rss_key));
		edev->rss_params_inited |= QEDE_RSS_KEY_INITED;
	पूर्ण
	स_नकल(rss->rss_key, edev->rss_key, माप(rss->rss_key));

	अगर (!(edev->rss_params_inited & QEDE_RSS_CAPS_INITED)) अणु
		edev->rss_caps = QED_RSS_IPV4 | QED_RSS_IPV6 |
		    QED_RSS_IPV4_TCP | QED_RSS_IPV6_TCP;
		edev->rss_params_inited |= QEDE_RSS_CAPS_INITED;
	पूर्ण
	rss->rss_caps = edev->rss_caps;

	*update = 1;
पूर्ण

अटल पूर्णांक qede_set_ucast_rx_mac(काष्ठा qede_dev *edev,
				 क्रमागत qed_filter_xcast_params_type opcode,
				 अचिन्हित अक्षर mac[ETH_ALEN])
अणु
	काष्ठा qed_filter_params filter_cmd;

	स_रखो(&filter_cmd, 0, माप(filter_cmd));
	filter_cmd.type = QED_FILTER_TYPE_UCAST;
	filter_cmd.filter.ucast.type = opcode;
	filter_cmd.filter.ucast.mac_valid = 1;
	ether_addr_copy(filter_cmd.filter.ucast.mac, mac);

	वापस edev->ops->filter_config(edev->cdev, &filter_cmd);
पूर्ण

अटल पूर्णांक qede_set_ucast_rx_vlan(काष्ठा qede_dev *edev,
				  क्रमागत qed_filter_xcast_params_type opcode,
				  u16 vid)
अणु
	काष्ठा qed_filter_params filter_cmd;

	स_रखो(&filter_cmd, 0, माप(filter_cmd));
	filter_cmd.type = QED_FILTER_TYPE_UCAST;
	filter_cmd.filter.ucast.type = opcode;
	filter_cmd.filter.ucast.vlan_valid = 1;
	filter_cmd.filter.ucast.vlan = vid;

	वापस edev->ops->filter_config(edev->cdev, &filter_cmd);
पूर्ण

अटल पूर्णांक qede_config_accept_any_vlan(काष्ठा qede_dev *edev, bool action)
अणु
	काष्ठा qed_update_vport_params *params;
	पूर्णांक rc;

	/* Proceed only अगर action actually needs to be perक्रमmed */
	अगर (edev->accept_any_vlan == action)
		वापस 0;

	params = vzalloc(माप(*params));
	अगर (!params)
		वापस -ENOMEM;

	params->vport_id = 0;
	params->accept_any_vlan = action;
	params->update_accept_any_vlan_flg = 1;

	rc = edev->ops->vport_update(edev->cdev, params);
	अगर (rc) अणु
		DP_ERR(edev, "Failed to %s accept-any-vlan\n",
		       action ? "enable" : "disable");
	पूर्ण अन्यथा अणु
		DP_INFO(edev, "%s accept-any-vlan\n",
			action ? "enabled" : "disabled");
		edev->accept_any_vlan = action;
	पूर्ण

	vमुक्त(params);
	वापस 0;
पूर्ण

पूर्णांक qede_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qede_vlan *vlan, *पंचांगp;
	पूर्णांक rc = 0;

	DP_VERBOSE(edev, NETIF_MSG_IFUP, "Adding vlan 0x%04x\n", vid);

	vlan = kzalloc(माप(*vlan), GFP_KERNEL);
	अगर (!vlan) अणु
		DP_INFO(edev, "Failed to allocate struct for vlan\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&vlan->list);
	vlan->vid = vid;
	vlan->configured = false;

	/* Verअगरy vlan isn't alपढ़ोy configured */
	list_क्रम_each_entry(पंचांगp, &edev->vlan_list, list) अणु
		अगर (पंचांगp->vid == vlan->vid) अणु
			DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
				   "vlan already configured\n");
			kमुक्त(vlan);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	/* If पूर्णांकerface is करोwn, cache this VLAN ID and वापस */
	__qede_lock(edev);
	अगर (edev->state != QEDE_STATE_OPEN) अणु
		DP_VERBOSE(edev, NETIF_MSG_IFDOWN,
			   "Interface is down, VLAN %d will be configured when interface is up\n",
			   vid);
		अगर (vid != 0)
			edev->non_configured_vlans++;
		list_add(&vlan->list, &edev->vlan_list);
		जाओ out;
	पूर्ण

	/* Check क्रम the filter limit.
	 * Note - vlan0 has a reserved filter and can be added without
	 * worrying about quota
	 */
	अगर ((edev->configured_vlans < edev->dev_info.num_vlan_filters) ||
	    (vlan->vid == 0)) अणु
		rc = qede_set_ucast_rx_vlan(edev,
					    QED_FILTER_XCAST_TYPE_ADD,
					    vlan->vid);
		अगर (rc) अणु
			DP_ERR(edev, "Failed to configure VLAN %d\n",
			       vlan->vid);
			kमुक्त(vlan);
			जाओ out;
		पूर्ण
		vlan->configured = true;

		/* vlan0 filter isn't consuming out of our quota */
		अगर (vlan->vid != 0)
			edev->configured_vlans++;
	पूर्ण अन्यथा अणु
		/* Out of quota; Activate accept-any-VLAN mode */
		अगर (!edev->non_configured_vlans) अणु
			rc = qede_config_accept_any_vlan(edev, true);
			अगर (rc) अणु
				kमुक्त(vlan);
				जाओ out;
			पूर्ण
		पूर्ण

		edev->non_configured_vlans++;
	पूर्ण

	list_add(&vlan->list, &edev->vlan_list);

out:
	__qede_unlock(edev);
	वापस rc;
पूर्ण

अटल व्योम qede_del_vlan_from_list(काष्ठा qede_dev *edev,
				    काष्ठा qede_vlan *vlan)
अणु
	/* vlan0 filter isn't consuming out of our quota */
	अगर (vlan->vid != 0) अणु
		अगर (vlan->configured)
			edev->configured_vlans--;
		अन्यथा
			edev->non_configured_vlans--;
	पूर्ण

	list_del(&vlan->list);
	kमुक्त(vlan);
पूर्ण

पूर्णांक qede_configure_vlan_filters(काष्ठा qede_dev *edev)
अणु
	पूर्णांक rc = 0, real_rc = 0, accept_any_vlan = 0;
	काष्ठा qed_dev_eth_info *dev_info;
	काष्ठा qede_vlan *vlan = शून्य;

	अगर (list_empty(&edev->vlan_list))
		वापस 0;

	dev_info = &edev->dev_info;

	/* Configure non-configured vlans */
	list_क्रम_each_entry(vlan, &edev->vlan_list, list) अणु
		अगर (vlan->configured)
			जारी;

		/* We have used all our credits, now enable accept_any_vlan */
		अगर ((vlan->vid != 0) &&
		    (edev->configured_vlans == dev_info->num_vlan_filters)) अणु
			accept_any_vlan = 1;
			जारी;
		पूर्ण

		DP_VERBOSE(edev, NETIF_MSG_IFUP, "Adding vlan %d\n", vlan->vid);

		rc = qede_set_ucast_rx_vlan(edev, QED_FILTER_XCAST_TYPE_ADD,
					    vlan->vid);
		अगर (rc) अणु
			DP_ERR(edev, "Failed to configure VLAN %u\n",
			       vlan->vid);
			real_rc = rc;
			जारी;
		पूर्ण

		vlan->configured = true;
		/* vlan0 filter करोesn't consume our VLAN filter's quota */
		अगर (vlan->vid != 0) अणु
			edev->non_configured_vlans--;
			edev->configured_vlans++;
		पूर्ण
	पूर्ण

	/* enable accept_any_vlan mode अगर we have more VLANs than credits,
	 * or हटाओ accept_any_vlan mode अगर we've actually हटाओd
	 * a non-configured vlan, and all reमुख्यing vlans are truly configured.
	 */

	अगर (accept_any_vlan)
		rc = qede_config_accept_any_vlan(edev, true);
	अन्यथा अगर (!edev->non_configured_vlans)
		rc = qede_config_accept_any_vlan(edev, false);

	अगर (rc && !real_rc)
		real_rc = rc;

	वापस real_rc;
पूर्ण

पूर्णांक qede_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qede_vlan *vlan = शून्य;
	पूर्णांक rc = 0;

	DP_VERBOSE(edev, NETIF_MSG_IFDOWN, "Removing vlan 0x%04x\n", vid);

	/* Find whether entry exists */
	__qede_lock(edev);
	list_क्रम_each_entry(vlan, &edev->vlan_list, list)
		अगर (vlan->vid == vid)
			अवरोध;

	अगर (!vlan || (vlan->vid != vid)) अणु
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "Vlan isn't configured\n");
		जाओ out;
	पूर्ण

	अगर (edev->state != QEDE_STATE_OPEN) अणु
		/* As पूर्णांकerface is alपढ़ोy करोwn, we करोn't have a VPORT
		 * instance to हटाओ vlan filter. So just update vlan list
		 */
		DP_VERBOSE(edev, NETIF_MSG_IFDOWN,
			   "Interface is down, removing VLAN from list only\n");
		qede_del_vlan_from_list(edev, vlan);
		जाओ out;
	पूर्ण

	/* Remove vlan */
	अगर (vlan->configured) अणु
		rc = qede_set_ucast_rx_vlan(edev, QED_FILTER_XCAST_TYPE_DEL,
					    vid);
		अगर (rc) अणु
			DP_ERR(edev, "Failed to remove VLAN %d\n", vid);
			जाओ out;
		पूर्ण
	पूर्ण

	qede_del_vlan_from_list(edev, vlan);

	/* We have हटाओd a VLAN - try to see अगर we can
	 * configure non-configured VLAN from the list.
	 */
	rc = qede_configure_vlan_filters(edev);

out:
	__qede_unlock(edev);
	वापस rc;
पूर्ण

व्योम qede_vlan_mark_nonconfigured(काष्ठा qede_dev *edev)
अणु
	काष्ठा qede_vlan *vlan = शून्य;

	अगर (list_empty(&edev->vlan_list))
		वापस;

	list_क्रम_each_entry(vlan, &edev->vlan_list, list) अणु
		अगर (!vlan->configured)
			जारी;

		vlan->configured = false;

		/* vlan0 filter isn't consuming out of our quota */
		अगर (vlan->vid != 0) अणु
			edev->non_configured_vlans++;
			edev->configured_vlans--;
		पूर्ण

		DP_VERBOSE(edev, NETIF_MSG_IFDOWN,
			   "marked vlan %d as non-configured\n", vlan->vid);
	पूर्ण

	edev->accept_any_vlan = false;
पूर्ण

अटल व्योम qede_set_features_reload(काष्ठा qede_dev *edev,
				     काष्ठा qede_reload_args *args)
अणु
	edev->ndev->features = args->u.features;
पूर्ण

netdev_features_t qede_fix_features(काष्ठा net_device *dev,
				    netdev_features_t features)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	अगर (edev->xdp_prog || edev->ndev->mtu > PAGE_SIZE ||
	    !(features & NETIF_F_GRO))
		features &= ~NETIF_F_GRO_HW;

	वापस features;
पूर्ण

पूर्णांक qede_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	netdev_features_t changes = features ^ dev->features;
	bool need_reload = false;

	अगर (changes & NETIF_F_GRO_HW)
		need_reload = true;

	अगर (need_reload) अणु
		काष्ठा qede_reload_args args;

		args.u.features = features;
		args.func = &qede_set_features_reload;

		/* Make sure that we definitely need to reload.
		 * In हाल of an eBPF attached program, there will be no FW
		 * aggregations, so no need to actually reload.
		 */
		__qede_lock(edev);
		अगर (edev->xdp_prog)
			args.func(edev, &args);
		अन्यथा
			qede_reload(edev, &args, true);
		__qede_unlock(edev);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qede_udp_tunnel_sync(काष्ठा net_device *dev, अचिन्हित पूर्णांक table)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_tunn_params tunn_params;
	काष्ठा udp_tunnel_info ti;
	u16 *save_port;
	पूर्णांक rc;

	स_रखो(&tunn_params, 0, माप(tunn_params));

	udp_tunnel_nic_get_port(dev, table, 0, &ti);
	अगर (ti.type == UDP_TUNNEL_TYPE_VXLAN) अणु
		tunn_params.update_vxlan_port = 1;
		tunn_params.vxlan_port = ntohs(ti.port);
		save_port = &edev->vxlan_dst_port;
	पूर्ण अन्यथा अणु
		tunn_params.update_geneve_port = 1;
		tunn_params.geneve_port = ntohs(ti.port);
		save_port = &edev->geneve_dst_port;
	पूर्ण

	__qede_lock(edev);
	rc = edev->ops->tunn_config(edev->cdev, &tunn_params);
	__qede_unlock(edev);
	अगर (rc)
		वापस rc;

	*save_port = ntohs(ti.port);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info qede_udp_tunnels_both = अणु
	.sync_table	= qede_udp_tunnel_sync,
	.flags		= UDP_TUNNEL_NIC_INFO_MAY_SLEEP,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN,  पूर्ण,
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_GENEVE, पूर्ण,
	पूर्ण,
पूर्ण, qede_udp_tunnels_vxlan = अणु
	.sync_table	= qede_udp_tunnel_sync,
	.flags		= UDP_TUNNEL_NIC_INFO_MAY_SLEEP,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN,  पूर्ण,
	पूर्ण,
पूर्ण, qede_udp_tunnels_geneve = अणु
	.sync_table	= qede_udp_tunnel_sync,
	.flags		= UDP_TUNNEL_NIC_INFO_MAY_SLEEP,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_GENEVE, पूर्ण,
	पूर्ण,
पूर्ण;

व्योम qede_set_udp_tunnels(काष्ठा qede_dev *edev)
अणु
	अगर (edev->dev_info.common.vxlan_enable &&
	    edev->dev_info.common.geneve_enable)
		edev->ndev->udp_tunnel_nic_info = &qede_udp_tunnels_both;
	अन्यथा अगर (edev->dev_info.common.vxlan_enable)
		edev->ndev->udp_tunnel_nic_info = &qede_udp_tunnels_vxlan;
	अन्यथा अगर (edev->dev_info.common.geneve_enable)
		edev->ndev->udp_tunnel_nic_info = &qede_udp_tunnels_geneve;
पूर्ण

अटल व्योम qede_xdp_reload_func(काष्ठा qede_dev *edev,
				 काष्ठा qede_reload_args *args)
अणु
	काष्ठा bpf_prog *old;

	old = xchg(&edev->xdp_prog, args->u.new_prog);
	अगर (old)
		bpf_prog_put(old);
पूर्ण

अटल पूर्णांक qede_xdp_set(काष्ठा qede_dev *edev, काष्ठा bpf_prog *prog)
अणु
	काष्ठा qede_reload_args args;

	/* If we're called, there was alपढ़ोy a bpf reference increment */
	args.func = &qede_xdp_reload_func;
	args.u.new_prog = prog;
	qede_reload(edev, &args, false);

	वापस 0;
पूर्ण

पूर्णांक qede_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस qede_xdp_set(edev, xdp->prog);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक qede_set_mcast_rx_mac(काष्ठा qede_dev *edev,
				 क्रमागत qed_filter_xcast_params_type opcode,
				 अचिन्हित अक्षर *mac, पूर्णांक num_macs)
अणु
	काष्ठा qed_filter_params filter_cmd;
	पूर्णांक i;

	स_रखो(&filter_cmd, 0, माप(filter_cmd));
	filter_cmd.type = QED_FILTER_TYPE_MCAST;
	filter_cmd.filter.mcast.type = opcode;
	filter_cmd.filter.mcast.num = num_macs;

	क्रम (i = 0; i < num_macs; i++, mac += ETH_ALEN)
		ether_addr_copy(filter_cmd.filter.mcast.mac[i], mac);

	वापस edev->ops->filter_config(edev->cdev, &filter_cmd);
पूर्ण

पूर्णांक qede_set_mac_addr(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	काष्ठा sockaddr *addr = p;
	पूर्णांक rc = 0;

	/* Make sure the state करोesn't transition जबतक changing the MAC.
	 * Also, all flows accessing the dev_addr field are करोing that under
	 * this lock.
	 */
	__qede_lock(edev);

	अगर (!is_valid_ether_addr(addr->sa_data)) अणु
		DP_NOTICE(edev, "The MAC address is not valid\n");
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (!edev->ops->check_mac(edev->cdev, addr->sa_data)) अणु
		DP_NOTICE(edev, "qed prevents setting MAC %pM\n",
			  addr->sa_data);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (edev->state == QEDE_STATE_OPEN) अणु
		/* Remove the previous primary mac */
		rc = qede_set_ucast_rx_mac(edev, QED_FILTER_XCAST_TYPE_DEL,
					   ndev->dev_addr);
		अगर (rc)
			जाओ out;
	पूर्ण

	ether_addr_copy(ndev->dev_addr, addr->sa_data);
	DP_INFO(edev, "Setting device MAC to %pM\n", addr->sa_data);

	अगर (edev->state != QEDE_STATE_OPEN) अणु
		DP_VERBOSE(edev, NETIF_MSG_IFDOWN,
			   "The device is currently down\n");
		/* Ask PF to explicitly update a copy in bulletin board */
		अगर (IS_VF(edev) && edev->ops->req_bulletin_update_mac)
			edev->ops->req_bulletin_update_mac(edev->cdev,
							   ndev->dev_addr);
		जाओ out;
	पूर्ण

	edev->ops->common->update_mac(edev->cdev, ndev->dev_addr);

	rc = qede_set_ucast_rx_mac(edev, QED_FILTER_XCAST_TYPE_ADD,
				   ndev->dev_addr);
out:
	__qede_unlock(edev);
	वापस rc;
पूर्ण

अटल पूर्णांक
qede_configure_mcast_filtering(काष्ठा net_device *ndev,
			       क्रमागत qed_filter_rx_mode_type *accept_flags)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	अचिन्हित अक्षर *mc_macs, *temp;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक rc = 0, mc_count;
	माप_प्रकार size;

	size = 64 * ETH_ALEN;

	mc_macs = kzalloc(size, GFP_KERNEL);
	अगर (!mc_macs) अणु
		DP_NOTICE(edev,
			  "Failed to allocate memory for multicast MACs\n");
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण

	temp = mc_macs;

	/* Remove all previously configured MAC filters */
	rc = qede_set_mcast_rx_mac(edev, QED_FILTER_XCAST_TYPE_DEL,
				   mc_macs, 1);
	अगर (rc)
		जाओ निकास;

	netअगर_addr_lock_bh(ndev);

	mc_count = netdev_mc_count(ndev);
	अगर (mc_count <= 64) अणु
		netdev_क्रम_each_mc_addr(ha, ndev) अणु
			ether_addr_copy(temp, ha->addr);
			temp += ETH_ALEN;
		पूर्ण
	पूर्ण

	netअगर_addr_unlock_bh(ndev);

	/* Check क्रम all multicast @@@TBD resource allocation */
	अगर ((ndev->flags & IFF_ALLMULTI) || (mc_count > 64)) अणु
		अगर (*accept_flags == QED_FILTER_RX_MODE_TYPE_REGULAR)
			*accept_flags = QED_FILTER_RX_MODE_TYPE_MULTI_PROMISC;
	पूर्ण अन्यथा अणु
		/* Add all multicast MAC filters */
		rc = qede_set_mcast_rx_mac(edev, QED_FILTER_XCAST_TYPE_ADD,
					   mc_macs, mc_count);
	पूर्ण

निकास:
	kमुक्त(mc_macs);
	वापस rc;
पूर्ण

व्योम qede_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);

	set_bit(QEDE_SP_RX_MODE, &edev->sp_flags);
	schedule_delayed_work(&edev->sp_task, 0);
पूर्ण

/* Must be called with qede_lock held */
व्योम qede_config_rx_mode(काष्ठा net_device *ndev)
अणु
	क्रमागत qed_filter_rx_mode_type accept_flags;
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	काष्ठा qed_filter_params rx_mode;
	अचिन्हित अक्षर *uc_macs, *temp;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक rc, uc_count;
	माप_प्रकार size;

	netअगर_addr_lock_bh(ndev);

	uc_count = netdev_uc_count(ndev);
	size = uc_count * ETH_ALEN;

	uc_macs = kzalloc(size, GFP_ATOMIC);
	अगर (!uc_macs) अणु
		DP_NOTICE(edev, "Failed to allocate memory for unicast MACs\n");
		netअगर_addr_unlock_bh(ndev);
		वापस;
	पूर्ण

	temp = uc_macs;
	netdev_क्रम_each_uc_addr(ha, ndev) अणु
		ether_addr_copy(temp, ha->addr);
		temp += ETH_ALEN;
	पूर्ण

	netअगर_addr_unlock_bh(ndev);

	/* Configure the काष्ठा क्रम the Rx mode */
	स_रखो(&rx_mode, 0, माप(काष्ठा qed_filter_params));
	rx_mode.type = QED_FILTER_TYPE_RX_MODE;

	/* Remove all previous unicast secondary macs and multicast macs
	 * (configure / leave the primary mac)
	 */
	rc = qede_set_ucast_rx_mac(edev, QED_FILTER_XCAST_TYPE_REPLACE,
				   edev->ndev->dev_addr);
	अगर (rc)
		जाओ out;

	/* Check क्रम promiscuous */
	अगर (ndev->flags & IFF_PROMISC)
		accept_flags = QED_FILTER_RX_MODE_TYPE_PROMISC;
	अन्यथा
		accept_flags = QED_FILTER_RX_MODE_TYPE_REGULAR;

	/* Configure all filters regardless, in हाल promisc is rejected */
	अगर (uc_count < edev->dev_info.num_mac_filters) अणु
		पूर्णांक i;

		temp = uc_macs;
		क्रम (i = 0; i < uc_count; i++) अणु
			rc = qede_set_ucast_rx_mac(edev,
						   QED_FILTER_XCAST_TYPE_ADD,
						   temp);
			अगर (rc)
				जाओ out;

			temp += ETH_ALEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		accept_flags = QED_FILTER_RX_MODE_TYPE_PROMISC;
	पूर्ण

	rc = qede_configure_mcast_filtering(ndev, &accept_flags);
	अगर (rc)
		जाओ out;

	/* take care of VLAN mode */
	अगर (ndev->flags & IFF_PROMISC) अणु
		qede_config_accept_any_vlan(edev, true);
	पूर्ण अन्यथा अगर (!edev->non_configured_vlans) अणु
		/* It's possible that accept_any_vlan mode is set due to a
		 * previous setting of IFF_PROMISC. If vlan credits are
		 * sufficient, disable accept_any_vlan.
		 */
		qede_config_accept_any_vlan(edev, false);
	पूर्ण

	rx_mode.filter.accept_flags = accept_flags;
	edev->ops->filter_config(edev->cdev, &rx_mode);
out:
	kमुक्त(uc_macs);
पूर्ण

अटल काष्ठा qede_arfs_fltr_node *
qede_get_arfs_fltr_by_loc(काष्ठा hlist_head *head, u64 location)
अणु
	काष्ठा qede_arfs_fltr_node *fltr;

	hlist_क्रम_each_entry(fltr, head, node)
		अगर (location == fltr->sw_id)
			वापस fltr;

	वापस शून्य;
पूर्ण

पूर्णांक qede_get_cls_rule_all(काष्ठा qede_dev *edev, काष्ठा ethtool_rxnfc *info,
			  u32 *rule_locs)
अणु
	काष्ठा qede_arfs_fltr_node *fltr;
	काष्ठा hlist_head *head;
	पूर्णांक cnt = 0, rc = 0;

	info->data = QEDE_RFS_MAX_FLTR;

	__qede_lock(edev);

	अगर (!edev->arfs) अणु
		rc = -EPERM;
		जाओ unlock;
	पूर्ण

	head = QEDE_ARFS_BUCKET_HEAD(edev, 0);

	hlist_क्रम_each_entry(fltr, head, node) अणु
		अगर (cnt == info->rule_cnt) अणु
			rc = -EMSGSIZE;
			जाओ unlock;
		पूर्ण

		rule_locs[cnt] = fltr->sw_id;
		cnt++;
	पूर्ण

	info->rule_cnt = cnt;

unlock:
	__qede_unlock(edev);
	वापस rc;
पूर्ण

पूर्णांक qede_get_cls_rule_entry(काष्ठा qede_dev *edev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp = &cmd->fs;
	काष्ठा qede_arfs_fltr_node *fltr = शून्य;
	पूर्णांक rc = 0;

	cmd->data = QEDE_RFS_MAX_FLTR;

	__qede_lock(edev);

	अगर (!edev->arfs) अणु
		rc = -EPERM;
		जाओ unlock;
	पूर्ण

	fltr = qede_get_arfs_fltr_by_loc(QEDE_ARFS_BUCKET_HEAD(edev, 0),
					 fsp->location);
	अगर (!fltr) अणु
		DP_NOTICE(edev, "Rule not found - location=0x%x\n",
			  fsp->location);
		rc = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (fltr->tuple.eth_proto == htons(ETH_P_IP)) अणु
		अगर (fltr->tuple.ip_proto == IPPROTO_TCP)
			fsp->flow_type = TCP_V4_FLOW;
		अन्यथा
			fsp->flow_type = UDP_V4_FLOW;

		fsp->h_u.tcp_ip4_spec.psrc = fltr->tuple.src_port;
		fsp->h_u.tcp_ip4_spec.pdst = fltr->tuple.dst_port;
		fsp->h_u.tcp_ip4_spec.ip4src = fltr->tuple.src_ipv4;
		fsp->h_u.tcp_ip4_spec.ip4dst = fltr->tuple.dst_ipv4;
	पूर्ण अन्यथा अणु
		अगर (fltr->tuple.ip_proto == IPPROTO_TCP)
			fsp->flow_type = TCP_V6_FLOW;
		अन्यथा
			fsp->flow_type = UDP_V6_FLOW;
		fsp->h_u.tcp_ip6_spec.psrc = fltr->tuple.src_port;
		fsp->h_u.tcp_ip6_spec.pdst = fltr->tuple.dst_port;
		स_नकल(&fsp->h_u.tcp_ip6_spec.ip6src,
		       &fltr->tuple.src_ipv6, माप(काष्ठा in6_addr));
		स_नकल(&fsp->h_u.tcp_ip6_spec.ip6dst,
		       &fltr->tuple.dst_ipv6, माप(काष्ठा in6_addr));
	पूर्ण

	fsp->ring_cookie = fltr->rxq_id;

	अगर (fltr->vfid) अणु
		fsp->ring_cookie |= ((u64)fltr->vfid) <<
					ETHTOOL_RX_FLOW_SPEC_RING_VF_OFF;
	पूर्ण

	अगर (fltr->b_is_drop)
		fsp->ring_cookie = RX_CLS_FLOW_DISC;
unlock:
	__qede_unlock(edev);
	वापस rc;
पूर्ण

अटल पूर्णांक
qede_poll_arfs_filter_config(काष्ठा qede_dev *edev,
			     काष्ठा qede_arfs_fltr_node *fltr)
अणु
	पूर्णांक count = QEDE_ARFS_POLL_COUNT;

	जबतक (fltr->used && count) अणु
		msleep(20);
		count--;
	पूर्ण

	अगर (count == 0 || fltr->fw_rc) अणु
		DP_NOTICE(edev, "Timeout in polling filter config\n");
		qede_dequeue_fltr_and_config_searcher(edev, fltr);
		वापस -EIO;
	पूर्ण

	वापस fltr->fw_rc;
पूर्ण

अटल पूर्णांक qede_flow_get_min_header_size(काष्ठा qede_arfs_tuple *t)
अणु
	पूर्णांक size = ETH_HLEN;

	अगर (t->eth_proto == htons(ETH_P_IP))
		size += माप(काष्ठा iphdr);
	अन्यथा
		size += माप(काष्ठा ipv6hdr);

	अगर (t->ip_proto == IPPROTO_TCP)
		size += माप(काष्ठा tcphdr);
	अन्यथा
		size += माप(काष्ठा udphdr);

	वापस size;
पूर्ण

अटल bool qede_flow_spec_ipv4_cmp(काष्ठा qede_arfs_tuple *a,
				    काष्ठा qede_arfs_tuple *b)
अणु
	अगर (a->eth_proto != htons(ETH_P_IP) ||
	    b->eth_proto != htons(ETH_P_IP))
		वापस false;

	वापस (a->src_ipv4 == b->src_ipv4) &&
	       (a->dst_ipv4 == b->dst_ipv4);
पूर्ण

अटल व्योम qede_flow_build_ipv4_hdr(काष्ठा qede_arfs_tuple *t,
				     व्योम *header)
अणु
	__be16 *ports = (__be16 *)(header + ETH_HLEN + माप(काष्ठा iphdr));
	काष्ठा iphdr *ip = (काष्ठा iphdr *)(header + ETH_HLEN);
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)header;

	eth->h_proto = t->eth_proto;
	ip->saddr = t->src_ipv4;
	ip->daddr = t->dst_ipv4;
	ip->version = 0x4;
	ip->ihl = 0x5;
	ip->protocol = t->ip_proto;
	ip->tot_len = cpu_to_be16(qede_flow_get_min_header_size(t) - ETH_HLEN);

	/* ports is weakly typed to suit both TCP and UDP ports */
	ports[0] = t->src_port;
	ports[1] = t->dst_port;
पूर्ण

अटल व्योम qede_flow_stringअगरy_ipv4_hdr(काष्ठा qede_arfs_tuple *t,
					 व्योम *buffer)
अणु
	स्थिर अक्षर *prefix = t->ip_proto == IPPROTO_TCP ? "TCP" : "UDP";

	snम_लिखो(buffer, QEDE_FILTER_PRपूर्णांक_उच्च_LEN,
		 "%s %pI4 (%04x) -> %pI4 (%04x)",
		 prefix, &t->src_ipv4, t->src_port,
		 &t->dst_ipv4, t->dst_port);
पूर्ण

अटल bool qede_flow_spec_ipv6_cmp(काष्ठा qede_arfs_tuple *a,
				    काष्ठा qede_arfs_tuple *b)
अणु
	अगर (a->eth_proto != htons(ETH_P_IPV6) ||
	    b->eth_proto != htons(ETH_P_IPV6))
		वापस false;

	अगर (स_भेद(&a->src_ipv6, &b->src_ipv6, माप(काष्ठा in6_addr)))
		वापस false;

	अगर (स_भेद(&a->dst_ipv6, &b->dst_ipv6, माप(काष्ठा in6_addr)))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम qede_flow_build_ipv6_hdr(काष्ठा qede_arfs_tuple *t,
				     व्योम *header)
अणु
	__be16 *ports = (__be16 *)(header + ETH_HLEN + माप(काष्ठा ipv6hdr));
	काष्ठा ipv6hdr *ip6 = (काष्ठा ipv6hdr *)(header + ETH_HLEN);
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)header;

	eth->h_proto = t->eth_proto;
	स_नकल(&ip6->saddr, &t->src_ipv6, माप(काष्ठा in6_addr));
	स_नकल(&ip6->daddr, &t->dst_ipv6, माप(काष्ठा in6_addr));
	ip6->version = 0x6;

	अगर (t->ip_proto == IPPROTO_TCP) अणु
		ip6->nexthdr = NEXTHDR_TCP;
		ip6->payload_len = cpu_to_be16(माप(काष्ठा tcphdr));
	पूर्ण अन्यथा अणु
		ip6->nexthdr = NEXTHDR_UDP;
		ip6->payload_len = cpu_to_be16(माप(काष्ठा udphdr));
	पूर्ण

	/* ports is weakly typed to suit both TCP and UDP ports */
	ports[0] = t->src_port;
	ports[1] = t->dst_port;
पूर्ण

/* Validate fields which are set and not accepted by the driver */
अटल पूर्णांक qede_flow_spec_validate_unused(काष्ठा qede_dev *edev,
					  काष्ठा ethtool_rx_flow_spec *fs)
अणु
	अगर (fs->flow_type & FLOW_MAC_EXT) अणु
		DP_INFO(edev, "Don't support MAC extensions\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((fs->flow_type & FLOW_EXT) &&
	    (fs->h_ext.vlan_etype || fs->h_ext.vlan_tci)) अणु
		DP_INFO(edev, "Don't support vlan-based classification\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((fs->flow_type & FLOW_EXT) &&
	    (fs->h_ext.data[0] || fs->h_ext.data[1])) अणु
		DP_INFO(edev, "Don't support user defined data\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qede_set_v4_tuple_to_profile(काष्ठा qede_dev *edev,
					काष्ठा qede_arfs_tuple *t)
अणु
	/* We must have Only 4-tuples/l4 port/src ip/dst ip
	 * as an input.
	 */
	अगर (t->src_port && t->dst_port && t->src_ipv4 && t->dst_ipv4) अणु
		t->mode = QED_FILTER_CONFIG_MODE_5_TUPLE;
	पूर्ण अन्यथा अगर (!t->src_port && t->dst_port &&
		   !t->src_ipv4 && !t->dst_ipv4) अणु
		t->mode = QED_FILTER_CONFIG_MODE_L4_PORT;
	पूर्ण अन्यथा अगर (!t->src_port && !t->dst_port &&
		   !t->dst_ipv4 && t->src_ipv4) अणु
		t->mode = QED_FILTER_CONFIG_MODE_IP_SRC;
	पूर्ण अन्यथा अगर (!t->src_port && !t->dst_port &&
		   t->dst_ipv4 && !t->src_ipv4) अणु
		t->mode = QED_FILTER_CONFIG_MODE_IP_DEST;
	पूर्ण अन्यथा अणु
		DP_INFO(edev, "Invalid N-tuple\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	t->ip_comp = qede_flow_spec_ipv4_cmp;
	t->build_hdr = qede_flow_build_ipv4_hdr;
	t->stringअगरy = qede_flow_stringअगरy_ipv4_hdr;

	वापस 0;
पूर्ण

अटल पूर्णांक qede_set_v6_tuple_to_profile(काष्ठा qede_dev *edev,
					काष्ठा qede_arfs_tuple *t,
					काष्ठा in6_addr *zaddr)
अणु
	/* We must have Only 4-tuples/l4 port/src ip/dst ip
	 * as an input.
	 */
	अगर (t->src_port && t->dst_port &&
	    स_भेद(&t->src_ipv6, zaddr, माप(काष्ठा in6_addr)) &&
	    स_भेद(&t->dst_ipv6, zaddr, माप(काष्ठा in6_addr))) अणु
		t->mode = QED_FILTER_CONFIG_MODE_5_TUPLE;
	पूर्ण अन्यथा अगर (!t->src_port && t->dst_port &&
		   !स_भेद(&t->src_ipv6, zaddr, माप(काष्ठा in6_addr)) &&
		   !स_भेद(&t->dst_ipv6, zaddr, माप(काष्ठा in6_addr))) अणु
		t->mode = QED_FILTER_CONFIG_MODE_L4_PORT;
	पूर्ण अन्यथा अगर (!t->src_port && !t->dst_port &&
		   !स_भेद(&t->dst_ipv6, zaddr, माप(काष्ठा in6_addr)) &&
		   स_भेद(&t->src_ipv6, zaddr, माप(काष्ठा in6_addr))) अणु
		t->mode = QED_FILTER_CONFIG_MODE_IP_SRC;
	पूर्ण अन्यथा अगर (!t->src_port && !t->dst_port &&
		   स_भेद(&t->dst_ipv6, zaddr, माप(काष्ठा in6_addr)) &&
		   !स_भेद(&t->src_ipv6, zaddr, माप(काष्ठा in6_addr))) अणु
		t->mode = QED_FILTER_CONFIG_MODE_IP_DEST;
	पूर्ण अन्यथा अणु
		DP_INFO(edev, "Invalid N-tuple\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	t->ip_comp = qede_flow_spec_ipv6_cmp;
	t->build_hdr = qede_flow_build_ipv6_hdr;

	वापस 0;
पूर्ण

/* Must be called जबतक qede lock is held */
अटल काष्ठा qede_arfs_fltr_node *
qede_flow_find_fltr(काष्ठा qede_dev *edev, काष्ठा qede_arfs_tuple *t)
अणु
	काष्ठा qede_arfs_fltr_node *fltr;
	काष्ठा hlist_node *temp;
	काष्ठा hlist_head *head;

	head = QEDE_ARFS_BUCKET_HEAD(edev, 0);

	hlist_क्रम_each_entry_safe(fltr, temp, head, node) अणु
		अगर (fltr->tuple.ip_proto == t->ip_proto &&
		    fltr->tuple.src_port == t->src_port &&
		    fltr->tuple.dst_port == t->dst_port &&
		    t->ip_comp(&fltr->tuple, t))
			वापस fltr;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम qede_flow_set_destination(काष्ठा qede_dev *edev,
				      काष्ठा qede_arfs_fltr_node *n,
				      काष्ठा ethtool_rx_flow_spec *fs)
अणु
	अगर (fs->ring_cookie == RX_CLS_FLOW_DISC) अणु
		n->b_is_drop = true;
		वापस;
	पूर्ण

	n->vfid = ethtool_get_flow_spec_ring_vf(fs->ring_cookie);
	n->rxq_id = ethtool_get_flow_spec_ring(fs->ring_cookie);
	n->next_rxq_id = n->rxq_id;

	अगर (n->vfid)
		DP_VERBOSE(edev, QED_MSG_SP,
			   "Configuring N-tuple for VF 0x%02x\n", n->vfid - 1);
पूर्ण

पूर्णांक qede_delete_flow_filter(काष्ठा qede_dev *edev, u64 cookie)
अणु
	काष्ठा qede_arfs_fltr_node *fltr = शून्य;
	पूर्णांक rc = -EPERM;

	__qede_lock(edev);
	अगर (!edev->arfs)
		जाओ unlock;

	fltr = qede_get_arfs_fltr_by_loc(QEDE_ARFS_BUCKET_HEAD(edev, 0),
					 cookie);
	अगर (!fltr)
		जाओ unlock;

	qede_configure_arfs_fltr(edev, fltr, fltr->rxq_id, false);

	rc = qede_poll_arfs_filter_config(edev, fltr);
	अगर (rc == 0)
		qede_dequeue_fltr_and_config_searcher(edev, fltr);

unlock:
	__qede_unlock(edev);
	वापस rc;
पूर्ण

पूर्णांक qede_get_arfs_filter_count(काष्ठा qede_dev *edev)
अणु
	पूर्णांक count = 0;

	__qede_lock(edev);

	अगर (!edev->arfs)
		जाओ unlock;

	count = edev->arfs->filter_count;

unlock:
	__qede_unlock(edev);
	वापस count;
पूर्ण

अटल पूर्णांक qede_parse_actions(काष्ठा qede_dev *edev,
			      काष्ठा flow_action *flow_action,
			      काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा flow_action_entry *act;
	पूर्णांक i;

	अगर (!flow_action_has_entries(flow_action)) अणु
		DP_NOTICE(edev, "No actions received\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!flow_action_basic_hw_stats_check(flow_action, extack))
		वापस -EOPNOTSUPP;

	flow_action_क्रम_each(i, act, flow_action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_DROP:
			अवरोध;
		हाल FLOW_ACTION_QUEUE:
			अगर (act->queue.vf)
				अवरोध;

			अगर (act->queue.index >= QEDE_RSS_COUNT(edev)) अणु
				DP_INFO(edev, "Queue out-of-bounds\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qede_flow_parse_ports(काष्ठा qede_dev *edev, काष्ठा flow_rule *rule,
		      काष्ठा qede_arfs_tuple *t)
अणु
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		अगर ((match.key->src && match.mask->src != htons(U16_MAX)) ||
		    (match.key->dst && match.mask->dst != htons(U16_MAX))) अणु
			DP_NOTICE(edev, "Do not support ports masks\n");
			वापस -EINVAL;
		पूर्ण

		t->src_port = match.key->src;
		t->dst_port = match.key->dst;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qede_flow_parse_v6_common(काष्ठा qede_dev *edev, काष्ठा flow_rule *rule,
			  काष्ठा qede_arfs_tuple *t)
अणु
	काष्ठा in6_addr zero_addr, addr;

	स_रखो(&zero_addr, 0, माप(addr));
	स_रखो(&addr, 0xff, माप(addr));

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS)) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);
		अगर ((स_भेद(&match.key->src, &zero_addr, माप(addr)) &&
		     स_भेद(&match.mask->src, &addr, माप(addr))) ||
		    (स_भेद(&match.key->dst, &zero_addr, माप(addr)) &&
		     स_भेद(&match.mask->dst, &addr, माप(addr)))) अणु
			DP_NOTICE(edev,
				  "Do not support IPv6 address prefix/mask\n");
			वापस -EINVAL;
		पूर्ण

		स_नकल(&t->src_ipv6, &match.key->src, माप(addr));
		स_नकल(&t->dst_ipv6, &match.key->dst, माप(addr));
	पूर्ण

	अगर (qede_flow_parse_ports(edev, rule, t))
		वापस -EINVAL;

	वापस qede_set_v6_tuple_to_profile(edev, t, &zero_addr);
पूर्ण

अटल पूर्णांक
qede_flow_parse_v4_common(काष्ठा qede_dev *edev, काष्ठा flow_rule *rule,
			काष्ठा qede_arfs_tuple *t)
अणु
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		अगर ((match.key->src && match.mask->src != htonl(U32_MAX)) ||
		    (match.key->dst && match.mask->dst != htonl(U32_MAX))) अणु
			DP_NOTICE(edev, "Do not support ipv4 prefix/masks\n");
			वापस -EINVAL;
		पूर्ण

		t->src_ipv4 = match.key->src;
		t->dst_ipv4 = match.key->dst;
	पूर्ण

	अगर (qede_flow_parse_ports(edev, rule, t))
		वापस -EINVAL;

	वापस qede_set_v4_tuple_to_profile(edev, t);
पूर्ण

अटल पूर्णांक
qede_flow_parse_tcp_v6(काष्ठा qede_dev *edev, काष्ठा flow_rule *rule,
		     काष्ठा qede_arfs_tuple *tuple)
अणु
	tuple->ip_proto = IPPROTO_TCP;
	tuple->eth_proto = htons(ETH_P_IPV6);

	वापस qede_flow_parse_v6_common(edev, rule, tuple);
पूर्ण

अटल पूर्णांक
qede_flow_parse_tcp_v4(काष्ठा qede_dev *edev, काष्ठा flow_rule *rule,
		     काष्ठा qede_arfs_tuple *tuple)
अणु
	tuple->ip_proto = IPPROTO_TCP;
	tuple->eth_proto = htons(ETH_P_IP);

	वापस qede_flow_parse_v4_common(edev, rule, tuple);
पूर्ण

अटल पूर्णांक
qede_flow_parse_udp_v6(काष्ठा qede_dev *edev, काष्ठा flow_rule *rule,
		     काष्ठा qede_arfs_tuple *tuple)
अणु
	tuple->ip_proto = IPPROTO_UDP;
	tuple->eth_proto = htons(ETH_P_IPV6);

	वापस qede_flow_parse_v6_common(edev, rule, tuple);
पूर्ण

अटल पूर्णांक
qede_flow_parse_udp_v4(काष्ठा qede_dev *edev, काष्ठा flow_rule *rule,
		     काष्ठा qede_arfs_tuple *tuple)
अणु
	tuple->ip_proto = IPPROTO_UDP;
	tuple->eth_proto = htons(ETH_P_IP);

	वापस qede_flow_parse_v4_common(edev, rule, tuple);
पूर्ण

अटल पूर्णांक
qede_parse_flow_attr(काष्ठा qede_dev *edev, __be16 proto,
		     काष्ठा flow_rule *rule, काष्ठा qede_arfs_tuple *tuple)
अणु
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	पूर्णांक rc = -EINVAL;
	u8 ip_proto = 0;

	स_रखो(tuple, 0, माप(*tuple));

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS))) अणु
		DP_NOTICE(edev, "Unsupported key set:0x%x\n",
			  dissector->used_keys);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (proto != htons(ETH_P_IP) &&
	    proto != htons(ETH_P_IPV6)) अणु
		DP_NOTICE(edev, "Unsupported proto=0x%x\n", proto);
		वापस -EPROTONOSUPPORT;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		ip_proto = match.key->ip_proto;
	पूर्ण

	अगर (ip_proto == IPPROTO_TCP && proto == htons(ETH_P_IP))
		rc = qede_flow_parse_tcp_v4(edev, rule, tuple);
	अन्यथा अगर (ip_proto == IPPROTO_TCP && proto == htons(ETH_P_IPV6))
		rc = qede_flow_parse_tcp_v6(edev, rule, tuple);
	अन्यथा अगर (ip_proto == IPPROTO_UDP && proto == htons(ETH_P_IP))
		rc = qede_flow_parse_udp_v4(edev, rule, tuple);
	अन्यथा अगर (ip_proto == IPPROTO_UDP && proto == htons(ETH_P_IPV6))
		rc = qede_flow_parse_udp_v6(edev, rule, tuple);
	अन्यथा
		DP_NOTICE(edev, "Invalid protocol request\n");

	वापस rc;
पूर्ण

पूर्णांक qede_add_tc_flower_fltr(काष्ठा qede_dev *edev, __be16 proto,
			    काष्ठा flow_cls_offload *f)
अणु
	काष्ठा qede_arfs_fltr_node *n;
	पूर्णांक min_hlen, rc = -EINVAL;
	काष्ठा qede_arfs_tuple t;

	__qede_lock(edev);

	अगर (!edev->arfs) अणु
		rc = -EPERM;
		जाओ unlock;
	पूर्ण

	/* parse flower attribute and prepare filter */
	अगर (qede_parse_flow_attr(edev, proto, f->rule, &t))
		जाओ unlock;

	/* Validate profile mode and number of filters */
	अगर ((edev->arfs->filter_count && edev->arfs->mode != t.mode) ||
	    edev->arfs->filter_count == QEDE_RFS_MAX_FLTR) अणु
		DP_NOTICE(edev,
			  "Filter configuration invalidated, filter mode=0x%x, configured mode=0x%x, filter count=0x%x\n",
			  t.mode, edev->arfs->mode, edev->arfs->filter_count);
		जाओ unlock;
	पूर्ण

	/* parse tc actions and get the vf_id */
	अगर (qede_parse_actions(edev, &f->rule->action, f->common.extack))
		जाओ unlock;

	अगर (qede_flow_find_fltr(edev, &t)) अणु
		rc = -EEXIST;
		जाओ unlock;
	पूर्ण

	n = kzalloc(माप(*n), GFP_KERNEL);
	अगर (!n) अणु
		rc = -ENOMEM;
		जाओ unlock;
	पूर्ण

	min_hlen = qede_flow_get_min_header_size(&t);

	n->data = kzalloc(min_hlen, GFP_KERNEL);
	अगर (!n->data) अणु
		kमुक्त(n);
		rc = -ENOMEM;
		जाओ unlock;
	पूर्ण

	स_नकल(&n->tuple, &t, माप(n->tuple));

	n->buf_len = min_hlen;
	n->b_is_drop = true;
	n->sw_id = f->cookie;

	n->tuple.build_hdr(&n->tuple, n->data);

	rc = qede_enqueue_fltr_and_config_searcher(edev, n, 0);
	अगर (rc)
		जाओ unlock;

	qede_configure_arfs_fltr(edev, n, n->rxq_id, true);
	rc = qede_poll_arfs_filter_config(edev, n);

unlock:
	__qede_unlock(edev);
	वापस rc;
पूर्ण

अटल पूर्णांक qede_flow_spec_validate(काष्ठा qede_dev *edev,
				   काष्ठा flow_action *flow_action,
				   काष्ठा qede_arfs_tuple *t,
				   __u32 location)
अणु
	अगर (location >= QEDE_RFS_MAX_FLTR) अणु
		DP_INFO(edev, "Location out-of-bounds\n");
		वापस -EINVAL;
	पूर्ण

	/* Check location isn't alपढ़ोy in use */
	अगर (test_bit(location, edev->arfs->arfs_fltr_bmap)) अणु
		DP_INFO(edev, "Location already in use\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर the filtering-mode could support the filter */
	अगर (edev->arfs->filter_count &&
	    edev->arfs->mode != t->mode) अणु
		DP_INFO(edev,
			"flow_spec would require filtering mode %08x, but %08x is configured\n",
			t->mode, edev->arfs->filter_count);
		वापस -EINVAL;
	पूर्ण

	अगर (qede_parse_actions(edev, flow_action, शून्य))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qede_flow_spec_to_rule(काष्ठा qede_dev *edev,
				  काष्ठा qede_arfs_tuple *t,
				  काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_rx_flow_spec_input input = अणुपूर्ण;
	काष्ठा ethtool_rx_flow_rule *flow;
	__be16 proto;
	पूर्णांक err = 0;

	अगर (qede_flow_spec_validate_unused(edev, fs))
		वापस -EOPNOTSUPP;

	चयन ((fs->flow_type & ~FLOW_EXT)) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		proto = htons(ETH_P_IP);
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		proto = htons(ETH_P_IPV6);
		अवरोध;
	शेष:
		DP_VERBOSE(edev, NETIF_MSG_IFUP,
			   "Can't support flow of type %08x\n", fs->flow_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	input.fs = fs;
	flow = ethtool_rx_flow_rule_create(&input);
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	अगर (qede_parse_flow_attr(edev, proto, flow->rule, t)) अणु
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	/* Make sure location is valid and filter isn't alपढ़ोy set */
	err = qede_flow_spec_validate(edev, &flow->rule->action, t,
				      fs->location);
err_out:
	ethtool_rx_flow_rule_destroy(flow);
	वापस err;

पूर्ण

पूर्णांक qede_add_cls_rule(काष्ठा qede_dev *edev, काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp = &info->fs;
	काष्ठा qede_arfs_fltr_node *n;
	काष्ठा qede_arfs_tuple t;
	पूर्णांक min_hlen, rc;

	__qede_lock(edev);

	अगर (!edev->arfs) अणु
		rc = -EPERM;
		जाओ unlock;
	पूर्ण

	/* Translate the flow specअगरication पूर्णांकo something fittign our DB */
	rc = qede_flow_spec_to_rule(edev, &t, fsp);
	अगर (rc)
		जाओ unlock;

	अगर (qede_flow_find_fltr(edev, &t)) अणु
		rc = -EINVAL;
		जाओ unlock;
	पूर्ण

	n = kzalloc(माप(*n), GFP_KERNEL);
	अगर (!n) अणु
		rc = -ENOMEM;
		जाओ unlock;
	पूर्ण

	min_hlen = qede_flow_get_min_header_size(&t);
	n->data = kzalloc(min_hlen, GFP_KERNEL);
	अगर (!n->data) अणु
		kमुक्त(n);
		rc = -ENOMEM;
		जाओ unlock;
	पूर्ण

	n->sw_id = fsp->location;
	set_bit(n->sw_id, edev->arfs->arfs_fltr_bmap);
	n->buf_len = min_hlen;

	स_नकल(&n->tuple, &t, माप(n->tuple));

	qede_flow_set_destination(edev, n, fsp);

	/* Build a minimal header according to the flow */
	n->tuple.build_hdr(&n->tuple, n->data);

	rc = qede_enqueue_fltr_and_config_searcher(edev, n, 0);
	अगर (rc)
		जाओ unlock;

	qede_configure_arfs_fltr(edev, n, n->rxq_id, true);
	rc = qede_poll_arfs_filter_config(edev, n);
unlock:
	__qede_unlock(edev);

	वापस rc;
पूर्ण
