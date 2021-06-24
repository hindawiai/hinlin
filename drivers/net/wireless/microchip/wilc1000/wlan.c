<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <net/dsfield.h>
#समावेश "cfg80211.h"
#समावेश "wlan_cfg.h"

अटल अंतरभूत bool is_wilc1000(u32 id)
अणु
	वापस (id & (~WILC_CHIP_REV_FIELD)) == WILC_1000_BASE_ID;
पूर्ण

अटल अंतरभूत व्योम acquire_bus(काष्ठा wilc *wilc, क्रमागत bus_acquire acquire)
अणु
	mutex_lock(&wilc->hअगर_cs);
	अगर (acquire == WILC_BUS_ACQUIRE_AND_WAKEUP)
		chip_wakeup(wilc);
पूर्ण

अटल अंतरभूत व्योम release_bus(काष्ठा wilc *wilc, क्रमागत bus_release release)
अणु
	अगर (release == WILC_BUS_RELEASE_ALLOW_SLEEP)
		chip_allow_sleep(wilc);
	mutex_unlock(&wilc->hअगर_cs);
पूर्ण

अटल व्योम wilc_wlan_txq_हटाओ(काष्ठा wilc *wilc, u8 q_num,
				 काष्ठा txq_entry_t *tqe)
अणु
	list_del(&tqe->list);
	wilc->txq_entries -= 1;
	wilc->txq[q_num].count--;
पूर्ण

अटल काष्ठा txq_entry_t *
wilc_wlan_txq_हटाओ_from_head(काष्ठा wilc *wilc, u8 q_num)
अणु
	काष्ठा txq_entry_t *tqe = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	अगर (!list_empty(&wilc->txq[q_num].txq_head.list)) अणु
		tqe = list_first_entry(&wilc->txq[q_num].txq_head.list,
				       काष्ठा txq_entry_t, list);
		list_del(&tqe->list);
		wilc->txq_entries -= 1;
		wilc->txq[q_num].count--;
	पूर्ण
	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);
	वापस tqe;
पूर्ण

अटल व्योम wilc_wlan_txq_add_to_tail(काष्ठा net_device *dev, u8 q_num,
				      काष्ठा txq_entry_t *tqe)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	list_add_tail(&tqe->list, &wilc->txq[q_num].txq_head.list);
	wilc->txq_entries += 1;
	wilc->txq[q_num].count++;

	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);

	complete(&wilc->txq_event);
पूर्ण

अटल व्योम wilc_wlan_txq_add_to_head(काष्ठा wilc_vअगर *vअगर, u8 q_num,
				      काष्ठा txq_entry_t *tqe)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा wilc *wilc = vअगर->wilc;

	mutex_lock(&wilc->txq_add_to_head_cs);

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	list_add(&tqe->list, &wilc->txq[q_num].txq_head.list);
	wilc->txq_entries += 1;
	wilc->txq[q_num].count++;

	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);
	mutex_unlock(&wilc->txq_add_to_head_cs);
	complete(&wilc->txq_event);
पूर्ण

#घोषणा NOT_TCP_ACK			(-1)

अटल अंतरभूत व्योम add_tcp_session(काष्ठा wilc_vअगर *vअगर, u32 src_prt,
				   u32 dst_prt, u32 seq)
अणु
	काष्ठा tcp_ack_filter *f = &vअगर->ack_filter;

	अगर (f->tcp_session < 2 * MAX_TCP_SESSION) अणु
		f->ack_session_info[f->tcp_session].seq_num = seq;
		f->ack_session_info[f->tcp_session].bigger_ack_num = 0;
		f->ack_session_info[f->tcp_session].src_port = src_prt;
		f->ack_session_info[f->tcp_session].dst_port = dst_prt;
		f->tcp_session++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_tcp_session(काष्ठा wilc_vअगर *vअगर, u32 index, u32 ack)
अणु
	काष्ठा tcp_ack_filter *f = &vअगर->ack_filter;

	अगर (index < 2 * MAX_TCP_SESSION &&
	    ack > f->ack_session_info[index].bigger_ack_num)
		f->ack_session_info[index].bigger_ack_num = ack;
पूर्ण

अटल अंतरभूत व्योम add_tcp_pending_ack(काष्ठा wilc_vअगर *vअगर, u32 ack,
				       u32 session_index,
				       काष्ठा txq_entry_t *txqe)
अणु
	काष्ठा tcp_ack_filter *f = &vअगर->ack_filter;
	u32 i = f->pending_base + f->pending_acks_idx;

	अगर (i < MAX_PENDING_ACKS) अणु
		f->pending_acks[i].ack_num = ack;
		f->pending_acks[i].txqe = txqe;
		f->pending_acks[i].session_index = session_index;
		txqe->ack_idx = i;
		f->pending_acks_idx++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम tcp_process(काष्ठा net_device *dev, काष्ठा txq_entry_t *tqe)
अणु
	व्योम *buffer = tqe->buffer;
	स्थिर काष्ठा ethhdr *eth_hdr_ptr = buffer;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;
	काष्ठा tcp_ack_filter *f = &vअगर->ack_filter;
	स्थिर काष्ठा iphdr *ip_hdr_ptr;
	स्थिर काष्ठा tcphdr *tcp_hdr_ptr;
	u32 ihl, total_length, data_offset;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	अगर (eth_hdr_ptr->h_proto != htons(ETH_P_IP))
		जाओ out;

	ip_hdr_ptr = buffer + ETH_HLEN;

	अगर (ip_hdr_ptr->protocol != IPPROTO_TCP)
		जाओ out;

	ihl = ip_hdr_ptr->ihl << 2;
	tcp_hdr_ptr = buffer + ETH_HLEN + ihl;
	total_length = ntohs(ip_hdr_ptr->tot_len);

	data_offset = tcp_hdr_ptr->करोff << 2;
	अगर (total_length == (ihl + data_offset)) अणु
		u32 seq_no, ack_no;

		seq_no = ntohl(tcp_hdr_ptr->seq);
		ack_no = ntohl(tcp_hdr_ptr->ack_seq);
		क्रम (i = 0; i < f->tcp_session; i++) अणु
			u32 j = f->ack_session_info[i].seq_num;

			अगर (i < 2 * MAX_TCP_SESSION &&
			    j == seq_no) अणु
				update_tcp_session(vअगर, i, ack_no);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == f->tcp_session)
			add_tcp_session(vअगर, 0, 0, seq_no);

		add_tcp_pending_ack(vअगर, ack_no, i, tqe);
	पूर्ण

out:
	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);
पूर्ण

अटल व्योम wilc_wlan_txq_filter_dup_tcp_ack(काष्ठा net_device *dev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;
	काष्ठा tcp_ack_filter *f = &vअगर->ack_filter;
	u32 i = 0;
	u32 dropped = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);
	क्रम (i = f->pending_base;
	     i < (f->pending_base + f->pending_acks_idx); i++) अणु
		u32 index;
		u32 bigger_ack_num;

		अगर (i >= MAX_PENDING_ACKS)
			अवरोध;

		index = f->pending_acks[i].session_index;

		अगर (index >= 2 * MAX_TCP_SESSION)
			अवरोध;

		bigger_ack_num = f->ack_session_info[index].bigger_ack_num;

		अगर (f->pending_acks[i].ack_num < bigger_ack_num) अणु
			काष्ठा txq_entry_t *tqe;

			tqe = f->pending_acks[i].txqe;
			अगर (tqe) अणु
				wilc_wlan_txq_हटाओ(wilc, tqe->q_num, tqe);
				tqe->status = 1;
				अगर (tqe->tx_complete_func)
					tqe->tx_complete_func(tqe->priv,
							      tqe->status);
				kमुक्त(tqe);
				dropped++;
			पूर्ण
		पूर्ण
	पूर्ण
	f->pending_acks_idx = 0;
	f->tcp_session = 0;

	अगर (f->pending_base == 0)
		f->pending_base = MAX_TCP_SESSION;
	अन्यथा
		f->pending_base = 0;

	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);

	जबतक (dropped > 0) अणु
		रुको_क्रम_completion_समयout(&wilc->txq_event,
					    msecs_to_jअगरfies(1));
		dropped--;
	पूर्ण
पूर्ण

व्योम wilc_enable_tcp_ack_filter(काष्ठा wilc_vअगर *vअगर, bool value)
अणु
	vअगर->ack_filter.enabled = value;
पूर्ण

अटल पूर्णांक wilc_wlan_txq_add_cfg_pkt(काष्ठा wilc_vअगर *vअगर, u8 *buffer,
				     u32 buffer_size)
अणु
	काष्ठा txq_entry_t *tqe;
	काष्ठा wilc *wilc = vअगर->wilc;

	netdev_dbg(vअगर->ndev, "Adding config packet ...\n");
	अगर (wilc->quit) अणु
		netdev_dbg(vअगर->ndev, "Return due to clear function\n");
		complete(&wilc->cfg_event);
		वापस 0;
	पूर्ण

	tqe = kदो_स्मृति(माप(*tqe), GFP_ATOMIC);
	अगर (!tqe) अणु
		complete(&wilc->cfg_event);
		वापस 0;
	पूर्ण

	tqe->type = WILC_CFG_PKT;
	tqe->buffer = buffer;
	tqe->buffer_size = buffer_size;
	tqe->tx_complete_func = शून्य;
	tqe->priv = शून्य;
	tqe->q_num = AC_VO_Q;
	tqe->ack_idx = NOT_TCP_ACK;
	tqe->vअगर = vअगर;

	wilc_wlan_txq_add_to_head(vअगर, AC_VO_Q, tqe);

	वापस 1;
पूर्ण

अटल bool is_ac_q_limit(काष्ठा wilc *wl, u8 q_num)
अणु
	u8 factors[NQUEUES] = अणु1, 1, 1, 1पूर्ण;
	u16 i;
	अचिन्हित दीर्घ flags;
	काष्ठा wilc_tx_queue_status *q = &wl->tx_q_limit;
	u8 end_index;
	u8 q_limit;
	bool ret = false;

	spin_lock_irqsave(&wl->txq_spinlock, flags);
	अगर (!q->initialized) अणु
		क्रम (i = 0; i < AC_BUFFER_SIZE; i++)
			q->buffer[i] = i % NQUEUES;

		क्रम (i = 0; i < NQUEUES; i++) अणु
			q->cnt[i] = AC_BUFFER_SIZE * factors[i] / NQUEUES;
			q->sum += q->cnt[i];
		पूर्ण
		q->end_index = AC_BUFFER_SIZE - 1;
		q->initialized = 1;
	पूर्ण

	end_index = q->end_index;
	q->cnt[q->buffer[end_index]] -= factors[q->buffer[end_index]];
	q->cnt[q_num] += factors[q_num];
	q->sum += (factors[q_num] - factors[q->buffer[end_index]]);

	q->buffer[end_index] = q_num;
	अगर (end_index > 0)
		q->end_index--;
	अन्यथा
		q->end_index = AC_BUFFER_SIZE - 1;

	अगर (!q->sum)
		q_limit = 1;
	अन्यथा
		q_limit = (q->cnt[q_num] * FLOW_CONTROL_UPPER_THRESHOLD / q->sum) + 1;

	अगर (wl->txq[q_num].count <= q_limit)
		ret = true;

	spin_unlock_irqrestore(&wl->txq_spinlock, flags);

	वापस ret;
पूर्ण

अटल अंतरभूत u8 ac_classअगरy(काष्ठा wilc *wilc, काष्ठा sk_buff *skb)
अणु
	u8 q_num = AC_BE_Q;
	u8 dscp;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		dscp = ipv4_get_dsfield(ip_hdr(skb)) & 0xfc;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		dscp = ipv6_get_dsfield(ipv6_hdr(skb)) & 0xfc;
		अवरोध;
	शेष:
		वापस q_num;
	पूर्ण

	चयन (dscp) अणु
	हाल 0x08:
	हाल 0x20:
	हाल 0x40:
		q_num = AC_BK_Q;
		अवरोध;
	हाल 0x80:
	हाल 0xA0:
	हाल 0x28:
		q_num = AC_VI_Q;
		अवरोध;
	हाल 0xC0:
	हाल 0xD0:
	हाल 0xE0:
	हाल 0x88:
	हाल 0xB8:
		q_num = AC_VO_Q;
		अवरोध;
	पूर्ण

	वापस q_num;
पूर्ण

अटल अंतरभूत पूर्णांक ac_balance(काष्ठा wilc *wl, u8 *ratio)
अणु
	u8 i, max_count = 0;

	अगर (!ratio)
		वापस -EINVAL;

	क्रम (i = 0; i < NQUEUES; i++)
		अगर (wl->txq[i].fw.count > max_count)
			max_count = wl->txq[i].fw.count;

	क्रम (i = 0; i < NQUEUES; i++)
		ratio[i] = max_count - wl->txq[i].fw.count;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ac_update_fw_ac_pkt_info(काष्ठा wilc *wl, u32 reg)
अणु
	wl->txq[AC_BK_Q].fw.count = FIELD_GET(BK_AC_COUNT_FIELD, reg);
	wl->txq[AC_BE_Q].fw.count = FIELD_GET(BE_AC_COUNT_FIELD, reg);
	wl->txq[AC_VI_Q].fw.count = FIELD_GET(VI_AC_COUNT_FIELD, reg);
	wl->txq[AC_VO_Q].fw.count = FIELD_GET(VO_AC_COUNT_FIELD, reg);

	wl->txq[AC_BK_Q].fw.acm = FIELD_GET(BK_AC_ACM_STAT_FIELD, reg);
	wl->txq[AC_BE_Q].fw.acm = FIELD_GET(BE_AC_ACM_STAT_FIELD, reg);
	wl->txq[AC_VI_Q].fw.acm = FIELD_GET(VI_AC_ACM_STAT_FIELD, reg);
	wl->txq[AC_VO_Q].fw.acm = FIELD_GET(VO_AC_ACM_STAT_FIELD, reg);
पूर्ण

अटल अंतरभूत u8 ac_change(काष्ठा wilc *wilc, u8 *ac)
अणु
	करो अणु
		अगर (wilc->txq[*ac].fw.acm == 0)
			वापस 0;
		(*ac)++;
	पूर्ण जबतक (*ac < NQUEUES);

	वापस 1;
पूर्ण

पूर्णांक wilc_wlan_txq_add_net_pkt(काष्ठा net_device *dev,
			      काष्ठा tx_complete_data *tx_data, u8 *buffer,
			      u32 buffer_size,
			      व्योम (*tx_complete_fn)(व्योम *, पूर्णांक))
अणु
	काष्ठा txq_entry_t *tqe;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc;
	u8 q_num;

	wilc = vअगर->wilc;

	अगर (wilc->quit) अणु
		tx_complete_fn(tx_data, 0);
		वापस 0;
	पूर्ण

	tqe = kदो_स्मृति(माप(*tqe), GFP_ATOMIC);

	अगर (!tqe) अणु
		tx_complete_fn(tx_data, 0);
		वापस 0;
	पूर्ण
	tqe->type = WILC_NET_PKT;
	tqe->buffer = buffer;
	tqe->buffer_size = buffer_size;
	tqe->tx_complete_func = tx_complete_fn;
	tqe->priv = tx_data;
	tqe->vअगर = vअगर;

	q_num = ac_classअगरy(wilc, tx_data->skb);
	tqe->q_num = q_num;
	अगर (ac_change(wilc, &q_num)) अणु
		tx_complete_fn(tx_data, 0);
		kमुक्त(tqe);
		वापस 0;
	पूर्ण

	अगर (is_ac_q_limit(wilc, q_num)) अणु
		tqe->ack_idx = NOT_TCP_ACK;
		अगर (vअगर->ack_filter.enabled)
			tcp_process(dev, tqe);
		wilc_wlan_txq_add_to_tail(dev, q_num, tqe);
	पूर्ण अन्यथा अणु
		tx_complete_fn(tx_data, 0);
		kमुक्त(tqe);
	पूर्ण

	वापस wilc->txq_entries;
पूर्ण

पूर्णांक wilc_wlan_txq_add_mgmt_pkt(काष्ठा net_device *dev, व्योम *priv, u8 *buffer,
			       u32 buffer_size,
			       व्योम (*tx_complete_fn)(व्योम *, पूर्णांक))
अणु
	काष्ठा txq_entry_t *tqe;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc;

	wilc = vअगर->wilc;

	अगर (wilc->quit) अणु
		tx_complete_fn(priv, 0);
		वापस 0;
	पूर्ण

	tqe = kदो_स्मृति(माप(*tqe), GFP_ATOMIC);

	अगर (!tqe) अणु
		tx_complete_fn(priv, 0);
		वापस 0;
	पूर्ण
	tqe->type = WILC_MGMT_PKT;
	tqe->buffer = buffer;
	tqe->buffer_size = buffer_size;
	tqe->tx_complete_func = tx_complete_fn;
	tqe->priv = priv;
	tqe->q_num = AC_BE_Q;
	tqe->ack_idx = NOT_TCP_ACK;
	tqe->vअगर = vअगर;
	wilc_wlan_txq_add_to_tail(dev, AC_VO_Q, tqe);
	वापस 1;
पूर्ण

अटल काष्ठा txq_entry_t *wilc_wlan_txq_get_first(काष्ठा wilc *wilc, u8 q_num)
अणु
	काष्ठा txq_entry_t *tqe = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	अगर (!list_empty(&wilc->txq[q_num].txq_head.list))
		tqe = list_first_entry(&wilc->txq[q_num].txq_head.list,
				       काष्ठा txq_entry_t, list);

	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);

	वापस tqe;
पूर्ण

अटल काष्ठा txq_entry_t *wilc_wlan_txq_get_next(काष्ठा wilc *wilc,
						  काष्ठा txq_entry_t *tqe,
						  u8 q_num)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	अगर (!list_is_last(&tqe->list, &wilc->txq[q_num].txq_head.list))
		tqe = list_next_entry(tqe, list);
	अन्यथा
		tqe = शून्य;
	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);

	वापस tqe;
पूर्ण

अटल व्योम wilc_wlan_rxq_add(काष्ठा wilc *wilc, काष्ठा rxq_entry_t *rqe)
अणु
	अगर (wilc->quit)
		वापस;

	mutex_lock(&wilc->rxq_cs);
	list_add_tail(&rqe->list, &wilc->rxq_head.list);
	mutex_unlock(&wilc->rxq_cs);
पूर्ण

अटल काष्ठा rxq_entry_t *wilc_wlan_rxq_हटाओ(काष्ठा wilc *wilc)
अणु
	काष्ठा rxq_entry_t *rqe = शून्य;

	mutex_lock(&wilc->rxq_cs);
	अगर (!list_empty(&wilc->rxq_head.list)) अणु
		rqe = list_first_entry(&wilc->rxq_head.list, काष्ठा rxq_entry_t,
				       list);
		list_del(&rqe->list);
	पूर्ण
	mutex_unlock(&wilc->rxq_cs);
	वापस rqe;
पूर्ण

व्योम chip_allow_sleep(काष्ठा wilc *wilc)
अणु
	u32 reg = 0;
	स्थिर काष्ठा wilc_hअगर_func *hअगर_func = wilc->hअगर_func;
	u32 wakeup_reg, wakeup_bit;
	u32 to_host_from_fw_reg, to_host_from_fw_bit;
	u32 from_host_to_fw_reg, from_host_to_fw_bit;
	u32 trials = 100;
	पूर्णांक ret;

	अगर (wilc->io_type == WILC_HIF_SDIO) अणु
		wakeup_reg = WILC_SDIO_WAKEUP_REG;
		wakeup_bit = WILC_SDIO_WAKEUP_BIT;
		from_host_to_fw_reg = WILC_SDIO_HOST_TO_FW_REG;
		from_host_to_fw_bit = WILC_SDIO_HOST_TO_FW_BIT;
		to_host_from_fw_reg = WILC_SDIO_FW_TO_HOST_REG;
		to_host_from_fw_bit = WILC_SDIO_FW_TO_HOST_BIT;
	पूर्ण अन्यथा अणु
		wakeup_reg = WILC_SPI_WAKEUP_REG;
		wakeup_bit = WILC_SPI_WAKEUP_BIT;
		from_host_to_fw_reg = WILC_SPI_HOST_TO_FW_REG;
		from_host_to_fw_bit = WILC_SPI_HOST_TO_FW_BIT;
		to_host_from_fw_reg = WILC_SPI_FW_TO_HOST_REG;
		to_host_from_fw_bit = WILC_SPI_FW_TO_HOST_BIT;
	पूर्ण

	जबतक (--trials) अणु
		ret = hअगर_func->hअगर_पढ़ो_reg(wilc, to_host_from_fw_reg, &reg);
		अगर (ret)
			वापस;
		अगर ((reg & to_host_from_fw_bit) == 0)
			अवरोध;
	पूर्ण
	अगर (!trials)
		pr_warn("FW not responding\n");

	/* Clear bit 1 */
	ret = hअगर_func->hअगर_पढ़ो_reg(wilc, wakeup_reg, &reg);
	अगर (ret)
		वापस;
	अगर (reg & wakeup_bit) अणु
		reg &= ~wakeup_bit;
		ret = hअगर_func->hअगर_ग_लिखो_reg(wilc, wakeup_reg, reg);
		अगर (ret)
			वापस;
	पूर्ण

	ret = hअगर_func->hअगर_पढ़ो_reg(wilc, from_host_to_fw_reg, &reg);
	अगर (ret)
		वापस;
	अगर (reg & from_host_to_fw_bit) अणु
		reg &= ~from_host_to_fw_bit;
		ret = hअगर_func->hअगर_ग_लिखो_reg(wilc, from_host_to_fw_reg, reg);
		अगर (ret)
			वापस;

	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(chip_allow_sleep);

व्योम chip_wakeup(काष्ठा wilc *wilc)
अणु
	u32 reg, clk_status_reg;
	स्थिर काष्ठा wilc_hअगर_func *h = wilc->hअगर_func;

	अगर (wilc->io_type == WILC_HIF_SPI) अणु
		करो अणु
			h->hअगर_पढ़ो_reg(wilc, WILC_SPI_WAKEUP_REG, &reg);
			h->hअगर_ग_लिखो_reg(wilc, WILC_SPI_WAKEUP_REG,
					 reg | WILC_SPI_WAKEUP_BIT);
			h->hअगर_ग_लिखो_reg(wilc, WILC_SPI_WAKEUP_REG,
					 reg & ~WILC_SPI_WAKEUP_BIT);

			करो अणु
				usleep_range(2000, 2500);
				wilc_get_chipid(wilc, true);
			पूर्ण जबतक (wilc_get_chipid(wilc, true) == 0);
		पूर्ण जबतक (wilc_get_chipid(wilc, true) == 0);
	पूर्ण अन्यथा अगर (wilc->io_type == WILC_HIF_SDIO) अणु
		h->hअगर_ग_लिखो_reg(wilc, WILC_SDIO_HOST_TO_FW_REG,
				 WILC_SDIO_HOST_TO_FW_BIT);
		usleep_range(200, 400);
		h->hअगर_पढ़ो_reg(wilc, WILC_SDIO_WAKEUP_REG, &reg);
		करो अणु
			h->hअगर_ग_लिखो_reg(wilc, WILC_SDIO_WAKEUP_REG,
					 reg | WILC_SDIO_WAKEUP_BIT);
			h->hअगर_पढ़ो_reg(wilc, WILC_SDIO_CLK_STATUS_REG,
					&clk_status_reg);

			जबतक (!(clk_status_reg & WILC_SDIO_CLK_STATUS_BIT)) अणु
				usleep_range(2000, 2500);

				h->hअगर_पढ़ो_reg(wilc, WILC_SDIO_CLK_STATUS_REG,
						&clk_status_reg);
			पूर्ण
			अगर (!(clk_status_reg & WILC_SDIO_CLK_STATUS_BIT)) अणु
				h->hअगर_ग_लिखो_reg(wilc, WILC_SDIO_WAKEUP_REG,
						 reg & ~WILC_SDIO_WAKEUP_BIT);
			पूर्ण
		पूर्ण जबतक (!(clk_status_reg & WILC_SDIO_CLK_STATUS_BIT));
	पूर्ण

	अगर (wilc->chip_ps_state == WILC_CHIP_SLEEPING_MANUAL) अणु
		अगर (wilc_get_chipid(wilc, false) < WILC_1000_BASE_ID_2B) अणु
			u32 val32;

			h->hअगर_पढ़ो_reg(wilc, WILC_REG_4_TO_1_RX, &val32);
			val32 |= BIT(6);
			h->hअगर_ग_लिखो_reg(wilc, WILC_REG_4_TO_1_RX, val32);

			h->hअगर_पढ़ो_reg(wilc, WILC_REG_4_TO_1_TX_BANK0, &val32);
			val32 |= BIT(6);
			h->hअगर_ग_लिखो_reg(wilc, WILC_REG_4_TO_1_TX_BANK0, val32);
		पूर्ण
	पूर्ण
	wilc->chip_ps_state = WILC_CHIP_WAKEDUP;
पूर्ण
EXPORT_SYMBOL_GPL(chip_wakeup);

व्योम host_wakeup_notअगरy(काष्ठा wilc *wilc)
अणु
	acquire_bus(wilc, WILC_BUS_ACQUIRE_ONLY);
	wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc, WILC_CORTUS_INTERRUPT_2, 1);
	release_bus(wilc, WILC_BUS_RELEASE_ONLY);
पूर्ण
EXPORT_SYMBOL_GPL(host_wakeup_notअगरy);

व्योम host_sleep_notअगरy(काष्ठा wilc *wilc)
अणु
	acquire_bus(wilc, WILC_BUS_ACQUIRE_ONLY);
	wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc, WILC_CORTUS_INTERRUPT_1, 1);
	release_bus(wilc, WILC_BUS_RELEASE_ONLY);
पूर्ण
EXPORT_SYMBOL_GPL(host_sleep_notअगरy);

पूर्णांक wilc_wlan_handle_txq(काष्ठा wilc *wilc, u32 *txq_count)
अणु
	पूर्णांक i, entries = 0;
	u8 k, ac;
	u32 sum;
	u32 reg;
	u8 ac_desired_ratio[NQUEUES] = अणु0, 0, 0, 0पूर्ण;
	u8 ac_preserve_ratio[NQUEUES] = अणु1, 1, 1, 1पूर्ण;
	u8 *num_pkts_to_add;
	u8 vmm_entries_ac[WILC_VMM_TBL_SIZE];
	u32 offset = 0;
	bool max_size_over = 0, ac_exist = 0;
	पूर्णांक vmm_sz = 0;
	काष्ठा txq_entry_t *tqe_q[NQUEUES];
	पूर्णांक ret = 0;
	पूर्णांक counter;
	पूर्णांक समयout;
	u32 vmm_table[WILC_VMM_TBL_SIZE];
	u8 ac_pkt_num_to_chip[NQUEUES] = अणु0, 0, 0, 0पूर्ण;
	स्थिर काष्ठा wilc_hअगर_func *func;
	पूर्णांक srcu_idx;
	u8 *txb = wilc->tx_buffer;
	काष्ठा wilc_vअगर *vअगर;

	अगर (wilc->quit)
		जाओ out_update_cnt;

	अगर (ac_balance(wilc, ac_desired_ratio))
		वापस -EINVAL;

	mutex_lock(&wilc->txq_add_to_head_cs);

	srcu_idx = srcu_पढ़ो_lock(&wilc->srcu);
	list_क्रम_each_entry_rcu(vअगर, &wilc->vअगर_list, list)
		wilc_wlan_txq_filter_dup_tcp_ack(vअगर->ndev);
	srcu_पढ़ो_unlock(&wilc->srcu, srcu_idx);

	क्रम (ac = 0; ac < NQUEUES; ac++)
		tqe_q[ac] = wilc_wlan_txq_get_first(wilc, ac);

	i = 0;
	sum = 0;
	max_size_over = 0;
	num_pkts_to_add = ac_desired_ratio;
	करो अणु
		ac_exist = 0;
		क्रम (ac = 0; (ac < NQUEUES) && (!max_size_over); ac++) अणु
			अगर (!tqe_q[ac])
				जारी;

			ac_exist = 1;
			क्रम (k = 0; (k < num_pkts_to_add[ac]) &&
			     (!max_size_over) && tqe_q[ac]; k++) अणु
				अगर (i >= (WILC_VMM_TBL_SIZE - 1)) अणु
					max_size_over = 1;
					अवरोध;
				पूर्ण

				अगर (tqe_q[ac]->type == WILC_CFG_PKT)
					vmm_sz = ETH_CONFIG_PKT_HDR_OFFSET;
				अन्यथा अगर (tqe_q[ac]->type == WILC_NET_PKT)
					vmm_sz = ETH_ETHERNET_HDR_OFFSET;
				अन्यथा
					vmm_sz = HOST_HDR_OFFSET;

				vmm_sz += tqe_q[ac]->buffer_size;
				vmm_sz = ALIGN(vmm_sz, 4);

				अगर ((sum + vmm_sz) > WILC_TX_BUFF_SIZE) अणु
					max_size_over = 1;
					अवरोध;
				पूर्ण
				vmm_table[i] = vmm_sz / 4;
				अगर (tqe_q[ac]->type == WILC_CFG_PKT)
					vmm_table[i] |= BIT(10);

				cpu_to_le32s(&vmm_table[i]);
				vmm_entries_ac[i] = ac;

				i++;
				sum += vmm_sz;
				tqe_q[ac] = wilc_wlan_txq_get_next(wilc,
								   tqe_q[ac],
								   ac);
			पूर्ण
		पूर्ण
		num_pkts_to_add = ac_preserve_ratio;
	पूर्ण जबतक (!max_size_over && ac_exist);

	अगर (i == 0)
		जाओ out_unlock;
	vmm_table[i] = 0x0;

	acquire_bus(wilc, WILC_BUS_ACQUIRE_AND_WAKEUP);
	counter = 0;
	func = wilc->hअगर_func;
	करो अणु
		ret = func->hअगर_पढ़ो_reg(wilc, WILC_HOST_TX_CTRL, &reg);
		अगर (ret)
			अवरोध;

		अगर ((reg & 0x1) == 0) अणु
			ac_update_fw_ac_pkt_info(wilc, reg);
			अवरोध;
		पूर्ण

		counter++;
		अगर (counter > 200) अणु
			counter = 0;
			ret = func->hअगर_ग_लिखो_reg(wilc, WILC_HOST_TX_CTRL, 0);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!wilc->quit);

	अगर (ret)
		जाओ out_release_bus;

	समयout = 200;
	करो अणु
		ret = func->hअगर_block_tx(wilc,
					 WILC_VMM_TBL_RX_SHADOW_BASE,
					 (u8 *)vmm_table,
					 ((i + 1) * 4));
		अगर (ret)
			अवरोध;

		ret = func->hअगर_ग_लिखो_reg(wilc, WILC_HOST_VMM_CTL, 0x2);
		अगर (ret)
			अवरोध;

		करो अणु
			ret = func->hअगर_पढ़ो_reg(wilc, WILC_HOST_VMM_CTL, &reg);
			अगर (ret)
				अवरोध;
			अगर (FIELD_GET(WILC_VMM_ENTRY_AVAILABLE, reg)) अणु
				entries = FIELD_GET(WILC_VMM_ENTRY_COUNT, reg);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (--समयout);
		अगर (समयout <= 0) अणु
			ret = func->hअगर_ग_लिखो_reg(wilc, WILC_HOST_VMM_CTL, 0x0);
			अवरोध;
		पूर्ण

		अगर (ret)
			अवरोध;

		अगर (entries == 0) अणु
			ret = func->hअगर_पढ़ो_reg(wilc, WILC_HOST_TX_CTRL, &reg);
			अगर (ret)
				अवरोध;
			reg &= ~BIT(0);
			ret = func->hअगर_ग_लिखो_reg(wilc, WILC_HOST_TX_CTRL, reg);
		पूर्ण
	पूर्ण जबतक (0);

	अगर (ret)
		जाओ out_release_bus;

	अगर (entries == 0) अणु
		/*
		 * No VMM space available in firmware so retry to transmit
		 * the packet from tx queue.
		 */
		ret = WILC_VMM_ENTRY_FULL_RETRY;
		जाओ out_release_bus;
	पूर्ण

	release_bus(wilc, WILC_BUS_RELEASE_ALLOW_SLEEP);

	offset = 0;
	i = 0;
	करो अणु
		काष्ठा txq_entry_t *tqe;
		u32 header, buffer_offset;
		अक्षर *bssid;
		u8 mgmt_ptk = 0;

		tqe = wilc_wlan_txq_हटाओ_from_head(wilc, vmm_entries_ac[i]);
		ac_pkt_num_to_chip[vmm_entries_ac[i]]++;
		अगर (!tqe)
			अवरोध;

		vअगर = tqe->vअगर;
		अगर (vmm_table[i] == 0)
			अवरोध;

		le32_to_cpus(&vmm_table[i]);
		vmm_sz = FIELD_GET(WILC_VMM_BUFFER_SIZE, vmm_table[i]);
		vmm_sz *= 4;

		अगर (tqe->type == WILC_MGMT_PKT)
			mgmt_ptk = 1;

		header = (FIELD_PREP(WILC_VMM_HDR_TYPE, tqe->type) |
			  FIELD_PREP(WILC_VMM_HDR_MGMT_FIELD, mgmt_ptk) |
			  FIELD_PREP(WILC_VMM_HDR_PKT_SIZE, tqe->buffer_size) |
			  FIELD_PREP(WILC_VMM_HDR_BUFF_SIZE, vmm_sz));

		cpu_to_le32s(&header);
		स_नकल(&txb[offset], &header, 4);
		अगर (tqe->type == WILC_CFG_PKT) अणु
			buffer_offset = ETH_CONFIG_PKT_HDR_OFFSET;
		पूर्ण अन्यथा अगर (tqe->type == WILC_NET_PKT) अणु
			पूर्णांक prio = tqe->q_num;

			bssid = tqe->vअगर->bssid;
			buffer_offset = ETH_ETHERNET_HDR_OFFSET;
			स_नकल(&txb[offset + 4], &prio, माप(prio));
			स_नकल(&txb[offset + 8], bssid, 6);
		पूर्ण अन्यथा अणु
			buffer_offset = HOST_HDR_OFFSET;
		पूर्ण

		स_नकल(&txb[offset + buffer_offset],
		       tqe->buffer, tqe->buffer_size);
		offset += vmm_sz;
		i++;
		tqe->status = 1;
		अगर (tqe->tx_complete_func)
			tqe->tx_complete_func(tqe->priv, tqe->status);
		अगर (tqe->ack_idx != NOT_TCP_ACK &&
		    tqe->ack_idx < MAX_PENDING_ACKS)
			vअगर->ack_filter.pending_acks[tqe->ack_idx].txqe = शून्य;
		kमुक्त(tqe);
	पूर्ण जबतक (--entries);
	क्रम (i = 0; i < NQUEUES; i++)
		wilc->txq[i].fw.count += ac_pkt_num_to_chip[i];

	acquire_bus(wilc, WILC_BUS_ACQUIRE_AND_WAKEUP);

	ret = func->hअगर_clear_पूर्णांक_ext(wilc, ENABLE_TX_VMM);
	अगर (ret)
		जाओ out_release_bus;

	ret = func->hअगर_block_tx_ext(wilc, 0, txb, offset);

out_release_bus:
	release_bus(wilc, WILC_BUS_RELEASE_ALLOW_SLEEP);

out_unlock:
	mutex_unlock(&wilc->txq_add_to_head_cs);

out_update_cnt:
	*txq_count = wilc->txq_entries;
	वापस ret;
पूर्ण

अटल व्योम wilc_wlan_handle_rx_buff(काष्ठा wilc *wilc, u8 *buffer, पूर्णांक size)
अणु
	पूर्णांक offset = 0;
	u32 header;
	u32 pkt_len, pkt_offset, tp_len;
	पूर्णांक is_cfg_packet;
	u8 *buff_ptr;

	करो अणु
		buff_ptr = buffer + offset;
		header = get_unaligned_le32(buff_ptr);

		is_cfg_packet = FIELD_GET(WILC_PKT_HDR_CONFIG_FIELD, header);
		pkt_offset = FIELD_GET(WILC_PKT_HDR_OFFSET_FIELD, header);
		tp_len = FIELD_GET(WILC_PKT_HDR_TOTAL_LEN_FIELD, header);
		pkt_len = FIELD_GET(WILC_PKT_HDR_LEN_FIELD, header);

		अगर (pkt_len == 0 || tp_len == 0)
			अवरोध;

		अगर (pkt_offset & IS_MANAGMEMENT) अणु
			buff_ptr += HOST_HDR_OFFSET;
			wilc_wfi_mgmt_rx(wilc, buff_ptr, pkt_len);
		पूर्ण अन्यथा अणु
			अगर (!is_cfg_packet) अणु
				wilc_frmw_to_host(wilc, buff_ptr, pkt_len,
						  pkt_offset);
			पूर्ण अन्यथा अणु
				काष्ठा wilc_cfg_rsp rsp;

				buff_ptr += pkt_offset;

				wilc_wlan_cfg_indicate_rx(wilc, buff_ptr,
							  pkt_len,
							  &rsp);
				अगर (rsp.type == WILC_CFG_RSP) अणु
					अगर (wilc->cfg_seq_no == rsp.seq_no)
						complete(&wilc->cfg_event);
				पूर्ण अन्यथा अगर (rsp.type == WILC_CFG_RSP_STATUS) अणु
					wilc_mac_indicate(wilc);
				पूर्ण
			पूर्ण
		पूर्ण
		offset += tp_len;
	पूर्ण जबतक (offset < size);
पूर्ण

अटल व्योम wilc_wlan_handle_rxq(काष्ठा wilc *wilc)
अणु
	पूर्णांक size;
	u8 *buffer;
	काष्ठा rxq_entry_t *rqe;

	जबतक (!wilc->quit) अणु
		rqe = wilc_wlan_rxq_हटाओ(wilc);
		अगर (!rqe)
			अवरोध;

		buffer = rqe->buffer;
		size = rqe->buffer_size;
		wilc_wlan_handle_rx_buff(wilc, buffer, size);

		kमुक्त(rqe);
	पूर्ण
	अगर (wilc->quit)
		complete(&wilc->cfg_event);
पूर्ण

अटल व्योम wilc_unknown_isr_ext(काष्ठा wilc *wilc)
अणु
	wilc->hअगर_func->hअगर_clear_पूर्णांक_ext(wilc, 0);
पूर्ण

अटल व्योम wilc_wlan_handle_isr_ext(काष्ठा wilc *wilc, u32 पूर्णांक_status)
अणु
	u32 offset = wilc->rx_buffer_offset;
	u8 *buffer = शून्य;
	u32 size;
	u32 retries = 0;
	पूर्णांक ret = 0;
	काष्ठा rxq_entry_t *rqe;

	size = FIELD_GET(WILC_INTERRUPT_DATA_SIZE, पूर्णांक_status) << 2;

	जबतक (!size && retries < 10) अणु
		wilc->hअगर_func->hअगर_पढ़ो_size(wilc, &size);
		size = FIELD_GET(WILC_INTERRUPT_DATA_SIZE, size) << 2;
		retries++;
	पूर्ण

	अगर (size <= 0)
		वापस;

	अगर (WILC_RX_BUFF_SIZE - offset < size)
		offset = 0;

	buffer = &wilc->rx_buffer[offset];

	wilc->hअगर_func->hअगर_clear_पूर्णांक_ext(wilc, DATA_INT_CLR | ENABLE_RX_VMM);
	ret = wilc->hअगर_func->hअगर_block_rx_ext(wilc, 0, buffer, size);
	अगर (ret)
		वापस;

	offset += size;
	wilc->rx_buffer_offset = offset;
	rqe = kदो_स्मृति(माप(*rqe), GFP_KERNEL);
	अगर (!rqe)
		वापस;

	rqe->buffer = buffer;
	rqe->buffer_size = size;
	wilc_wlan_rxq_add(wilc, rqe);
	wilc_wlan_handle_rxq(wilc);
पूर्ण

व्योम wilc_handle_isr(काष्ठा wilc *wilc)
अणु
	u32 पूर्णांक_status;

	acquire_bus(wilc, WILC_BUS_ACQUIRE_AND_WAKEUP);
	wilc->hअगर_func->hअगर_पढ़ो_पूर्णांक(wilc, &पूर्णांक_status);

	अगर (पूर्णांक_status & DATA_INT_EXT)
		wilc_wlan_handle_isr_ext(wilc, पूर्णांक_status);

	अगर (!(पूर्णांक_status & (ALL_INT_EXT)))
		wilc_unknown_isr_ext(wilc);

	release_bus(wilc, WILC_BUS_RELEASE_ALLOW_SLEEP);
पूर्ण
EXPORT_SYMBOL_GPL(wilc_handle_isr);

पूर्णांक wilc_wlan_firmware_करोwnload(काष्ठा wilc *wilc, स्थिर u8 *buffer,
				u32 buffer_size)
अणु
	u32 offset;
	u32 addr, size, size2, blksz;
	u8 *dma_buffer;
	पूर्णांक ret = 0;

	blksz = BIT(12);

	dma_buffer = kदो_स्मृति(blksz, GFP_KERNEL);
	अगर (!dma_buffer)
		वापस -EIO;

	offset = 0;
	करो अणु
		addr = get_unaligned_le32(&buffer[offset]);
		size = get_unaligned_le32(&buffer[offset + 4]);
		acquire_bus(wilc, WILC_BUS_ACQUIRE_ONLY);
		offset += 8;
		जबतक (((पूर्णांक)size) && (offset < buffer_size)) अणु
			अगर (size <= blksz)
				size2 = size;
			अन्यथा
				size2 = blksz;

			स_नकल(dma_buffer, &buffer[offset], size2);
			ret = wilc->hअगर_func->hअगर_block_tx(wilc, addr,
							   dma_buffer, size2);
			अगर (ret)
				अवरोध;

			addr += size2;
			offset += size2;
			size -= size2;
		पूर्ण
		release_bus(wilc, WILC_BUS_RELEASE_ONLY);

		अगर (ret)
			जाओ fail;
	पूर्ण जबतक (offset < buffer_size);

fail:

	kमुक्त(dma_buffer);

	वापस ret;
पूर्ण

पूर्णांक wilc_wlan_start(काष्ठा wilc *wilc)
अणु
	u32 reg = 0;
	पूर्णांक ret;
	u32 chipid;

	अगर (wilc->io_type == WILC_HIF_SDIO) अणु
		reg = 0;
		reg |= BIT(3);
	पूर्ण अन्यथा अगर (wilc->io_type == WILC_HIF_SPI) अणु
		reg = 1;
	पूर्ण
	acquire_bus(wilc, WILC_BUS_ACQUIRE_ONLY);
	ret = wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc, WILC_VMM_CORE_CFG, reg);
	अगर (ret) अणु
		release_bus(wilc, WILC_BUS_RELEASE_ONLY);
		वापस ret;
	पूर्ण
	reg = 0;
	अगर (wilc->io_type == WILC_HIF_SDIO && wilc->dev_irq_num)
		reg |= WILC_HAVE_SDIO_IRQ_GPIO;

	ret = wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc, WILC_GP_REG_1, reg);
	अगर (ret) अणु
		release_bus(wilc, WILC_BUS_RELEASE_ONLY);
		वापस ret;
	पूर्ण

	wilc->hअगर_func->hअगर_sync_ext(wilc, NUM_INT_EXT);

	ret = wilc->hअगर_func->hअगर_पढ़ो_reg(wilc, WILC_CHIPID, &chipid);
	अगर (ret) अणु
		release_bus(wilc, WILC_BUS_RELEASE_ONLY);
		वापस ret;
	पूर्ण

	wilc->hअगर_func->hअगर_पढ़ो_reg(wilc, WILC_GLB_RESET_0, &reg);
	अगर ((reg & BIT(10)) == BIT(10)) अणु
		reg &= ~BIT(10);
		wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc, WILC_GLB_RESET_0, reg);
		wilc->hअगर_func->hअगर_पढ़ो_reg(wilc, WILC_GLB_RESET_0, &reg);
	पूर्ण

	reg |= BIT(10);
	ret = wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc, WILC_GLB_RESET_0, reg);
	wilc->hअगर_func->hअगर_पढ़ो_reg(wilc, WILC_GLB_RESET_0, &reg);
	release_bus(wilc, WILC_BUS_RELEASE_ONLY);

	वापस ret;
पूर्ण

पूर्णांक wilc_wlan_stop(काष्ठा wilc *wilc, काष्ठा wilc_vअगर *vअगर)
अणु
	u32 reg = 0;
	पूर्णांक ret;

	acquire_bus(wilc, WILC_BUS_ACQUIRE_AND_WAKEUP);

	ret = wilc->hअगर_func->hअगर_पढ़ो_reg(wilc, WILC_GP_REG_0, &reg);
	अगर (ret) अणु
		netdev_err(vअगर->ndev, "Error while reading reg\n");
		release_bus(wilc, WILC_BUS_RELEASE_ALLOW_SLEEP);
		वापस ret;
	पूर्ण

	ret = wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc, WILC_GP_REG_0,
					(reg | WILC_ABORT_REQ_BIT));
	अगर (ret) अणु
		netdev_err(vअगर->ndev, "Error while writing reg\n");
		release_bus(wilc, WILC_BUS_RELEASE_ALLOW_SLEEP);
		वापस ret;
	पूर्ण

	ret = wilc->hअगर_func->hअगर_पढ़ो_reg(wilc, WILC_FW_HOST_COMM, &reg);
	अगर (ret) अणु
		netdev_err(vअगर->ndev, "Error while reading reg\n");
		release_bus(wilc, WILC_BUS_RELEASE_ALLOW_SLEEP);
		वापस ret;
	पूर्ण
	reg = BIT(0);

	ret = wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc, WILC_FW_HOST_COMM, reg);
	अगर (ret) अणु
		netdev_err(vअगर->ndev, "Error while writing reg\n");
		release_bus(wilc, WILC_BUS_RELEASE_ALLOW_SLEEP);
		वापस ret;
	पूर्ण

	release_bus(wilc, WILC_BUS_RELEASE_ALLOW_SLEEP);

	वापस 0;
पूर्ण

व्योम wilc_wlan_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा txq_entry_t *tqe;
	काष्ठा rxq_entry_t *rqe;
	u8 ac;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;

	wilc->quit = 1;
	क्रम (ac = 0; ac < NQUEUES; ac++) अणु
		जबतक ((tqe = wilc_wlan_txq_हटाओ_from_head(wilc, ac))) अणु
			अगर (tqe->tx_complete_func)
				tqe->tx_complete_func(tqe->priv, 0);
			kमुक्त(tqe);
		पूर्ण
	पूर्ण

	जबतक ((rqe = wilc_wlan_rxq_हटाओ(wilc)))
		kमुक्त(rqe);

	kमुक्त(wilc->rx_buffer);
	wilc->rx_buffer = शून्य;
	kमुक्त(wilc->tx_buffer);
	wilc->tx_buffer = शून्य;
	wilc->hअगर_func->hअगर_deinit(शून्य);
पूर्ण

अटल पूर्णांक wilc_wlan_cfg_commit(काष्ठा wilc_vअगर *vअगर, पूर्णांक type,
				u32 drv_handler)
अणु
	काष्ठा wilc *wilc = vअगर->wilc;
	काष्ठा wilc_cfg_frame *cfg = &wilc->cfg_frame;
	पूर्णांक t_len = wilc->cfg_frame_offset + माप(काष्ठा wilc_cfg_cmd_hdr);

	अगर (type == WILC_CFG_SET)
		cfg->hdr.cmd_type = 'W';
	अन्यथा
		cfg->hdr.cmd_type = 'Q';

	cfg->hdr.seq_no = wilc->cfg_seq_no % 256;
	cfg->hdr.total_len = cpu_to_le16(t_len);
	cfg->hdr.driver_handler = cpu_to_le32(drv_handler);
	wilc->cfg_seq_no = cfg->hdr.seq_no;

	अगर (!wilc_wlan_txq_add_cfg_pkt(vअगर, (u8 *)&cfg->hdr, t_len))
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक wilc_wlan_cfg_set(काष्ठा wilc_vअगर *vअगर, पूर्णांक start, u16 wid, u8 *buffer,
		      u32 buffer_size, पूर्णांक commit, u32 drv_handler)
अणु
	u32 offset;
	पूर्णांक ret_size;
	काष्ठा wilc *wilc = vअगर->wilc;

	mutex_lock(&wilc->cfg_cmd_lock);

	अगर (start)
		wilc->cfg_frame_offset = 0;

	offset = wilc->cfg_frame_offset;
	ret_size = wilc_wlan_cfg_set_wid(wilc->cfg_frame.frame, offset,
					 wid, buffer, buffer_size);
	offset += ret_size;
	wilc->cfg_frame_offset = offset;

	अगर (!commit) अणु
		mutex_unlock(&wilc->cfg_cmd_lock);
		वापस ret_size;
	पूर्ण

	netdev_dbg(vअगर->ndev, "%s: seqno[%d]\n", __func__, wilc->cfg_seq_no);

	अगर (wilc_wlan_cfg_commit(vअगर, WILC_CFG_SET, drv_handler))
		ret_size = 0;

	अगर (!रुको_क्रम_completion_समयout(&wilc->cfg_event,
					 WILC_CFG_PKTS_TIMEOUT)) अणु
		netdev_dbg(vअगर->ndev, "%s: Timed Out\n", __func__);
		ret_size = 0;
	पूर्ण

	wilc->cfg_frame_offset = 0;
	wilc->cfg_seq_no += 1;
	mutex_unlock(&wilc->cfg_cmd_lock);

	वापस ret_size;
पूर्ण

पूर्णांक wilc_wlan_cfg_get(काष्ठा wilc_vअगर *vअगर, पूर्णांक start, u16 wid, पूर्णांक commit,
		      u32 drv_handler)
अणु
	u32 offset;
	पूर्णांक ret_size;
	काष्ठा wilc *wilc = vअगर->wilc;

	mutex_lock(&wilc->cfg_cmd_lock);

	अगर (start)
		wilc->cfg_frame_offset = 0;

	offset = wilc->cfg_frame_offset;
	ret_size = wilc_wlan_cfg_get_wid(wilc->cfg_frame.frame, offset, wid);
	offset += ret_size;
	wilc->cfg_frame_offset = offset;

	अगर (!commit) अणु
		mutex_unlock(&wilc->cfg_cmd_lock);
		वापस ret_size;
	पूर्ण

	अगर (wilc_wlan_cfg_commit(vअगर, WILC_CFG_QUERY, drv_handler))
		ret_size = 0;

	अगर (!रुको_क्रम_completion_समयout(&wilc->cfg_event,
					 WILC_CFG_PKTS_TIMEOUT)) अणु
		netdev_dbg(vअगर->ndev, "%s: Timed Out\n", __func__);
		ret_size = 0;
	पूर्ण
	wilc->cfg_frame_offset = 0;
	wilc->cfg_seq_no += 1;
	mutex_unlock(&wilc->cfg_cmd_lock);

	वापस ret_size;
पूर्ण

पूर्णांक wilc_send_config_pkt(काष्ठा wilc_vअगर *vअगर, u8 mode, काष्ठा wid *wids,
			 u32 count)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	u32 drv = wilc_get_vअगर_idx(vअगर);

	अगर (mode == WILC_GET_CFG) अणु
		क्रम (i = 0; i < count; i++) अणु
			अगर (!wilc_wlan_cfg_get(vअगर, !i,
					       wids[i].id,
					       (i == count - 1),
					       drv)) अणु
				ret = -ETIMEDOUT;
				अवरोध;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < count; i++) अणु
			wids[i].size = wilc_wlan_cfg_get_val(vअगर->wilc,
							     wids[i].id,
							     wids[i].val,
							     wids[i].size);
		पूर्ण
	पूर्ण अन्यथा अगर (mode == WILC_SET_CFG) अणु
		क्रम (i = 0; i < count; i++) अणु
			अगर (!wilc_wlan_cfg_set(vअगर, !i,
					       wids[i].id,
					       wids[i].val,
					       wids[i].size,
					       (i == count - 1),
					       drv)) अणु
				ret = -ETIMEDOUT;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक init_chip(काष्ठा net_device *dev)
अणु
	u32 chipid;
	u32 reg;
	पूर्णांक ret = 0;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc = vअगर->wilc;

	acquire_bus(wilc, WILC_BUS_ACQUIRE_ONLY);

	chipid = wilc_get_chipid(wilc, true);

	अगर ((chipid & 0xfff) != 0xa0) अणु
		ret = wilc->hअगर_func->hअगर_पढ़ो_reg(wilc,
						   WILC_CORTUS_RESET_MUX_SEL,
						   &reg);
		अगर (ret) अणु
			netdev_err(dev, "fail read reg 0x1118\n");
			जाओ release;
		पूर्ण
		reg |= BIT(0);
		ret = wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc,
						    WILC_CORTUS_RESET_MUX_SEL,
						    reg);
		अगर (ret) अणु
			netdev_err(dev, "fail write reg 0x1118\n");
			जाओ release;
		पूर्ण
		ret = wilc->hअगर_func->hअगर_ग_लिखो_reg(wilc,
						    WILC_CORTUS_BOOT_REGISTER,
						    WILC_CORTUS_BOOT_FROM_IRAM);
		अगर (ret) अणु
			netdev_err(dev, "fail write reg 0xc0000\n");
			जाओ release;
		पूर्ण
	पूर्ण

release:
	release_bus(wilc, WILC_BUS_RELEASE_ONLY);

	वापस ret;
पूर्ण

u32 wilc_get_chipid(काष्ठा wilc *wilc, bool update)
अणु
	अटल u32 chipid;
	u32 tempchipid = 0;
	u32 rfrevid = 0;

	अगर (chipid == 0 || update) अणु
		wilc->hअगर_func->hअगर_पढ़ो_reg(wilc, WILC_CHIPID, &tempchipid);
		wilc->hअगर_func->hअगर_पढ़ो_reg(wilc, WILC_RF_REVISION_ID,
					     &rfrevid);
		अगर (!is_wilc1000(tempchipid)) अणु
			chipid = 0;
			वापस chipid;
		पूर्ण
		अगर (tempchipid == WILC_1000_BASE_ID_2A) अणु /* 0x1002A0 */
			अगर (rfrevid != 0x1)
				tempchipid = WILC_1000_BASE_ID_2A_REV1;
		पूर्ण अन्यथा अगर (tempchipid == WILC_1000_BASE_ID_2B) अणु /* 0x1002B0 */
			अगर (rfrevid == 0x4)
				tempchipid = WILC_1000_BASE_ID_2B_REV1;
			अन्यथा अगर (rfrevid != 0x3)
				tempchipid = WILC_1000_BASE_ID_2B_REV2;
		पूर्ण

		chipid = tempchipid;
	पूर्ण
	वापस chipid;
पूर्ण

पूर्णांक wilc_wlan_init(काष्ठा net_device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wilc;

	wilc = vअगर->wilc;

	wilc->quit = 0;

	अगर (wilc->hअगर_func->hअगर_init(wilc, false)) अणु
		ret = -EIO;
		जाओ fail;
	पूर्ण

	अगर (!wilc->tx_buffer)
		wilc->tx_buffer = kदो_स्मृति(WILC_TX_BUFF_SIZE, GFP_KERNEL);

	अगर (!wilc->tx_buffer) अणु
		ret = -ENOBUFS;
		जाओ fail;
	पूर्ण

	अगर (!wilc->rx_buffer)
		wilc->rx_buffer = kदो_स्मृति(WILC_RX_BUFF_SIZE, GFP_KERNEL);

	अगर (!wilc->rx_buffer) अणु
		ret = -ENOBUFS;
		जाओ fail;
	पूर्ण

	अगर (init_chip(dev)) अणु
		ret = -EIO;
		जाओ fail;
	पूर्ण

	वापस 0;

fail:

	kमुक्त(wilc->rx_buffer);
	wilc->rx_buffer = शून्य;
	kमुक्त(wilc->tx_buffer);
	wilc->tx_buffer = शून्य;

	वापस ret;
पूर्ण
