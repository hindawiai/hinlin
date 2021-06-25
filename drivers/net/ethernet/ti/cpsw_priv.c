<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments Ethernet Switch Driver
 *
 * Copyright (C) 2019 Texas Instruments
 */

#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/of.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/skbuff.h>
#समावेश <net/page_pool.h>
#समावेश <net/pkt_cls.h>

#समावेश "cpsw.h"
#समावेश "cpts.h"
#समावेश "cpsw_ale.h"
#समावेश "cpsw_priv.h"
#समावेश "cpsw_sl.h"
#समावेश "davinci_cpdma.h"

#घोषणा CPTS_N_ETX_TS 4

पूर्णांक (*cpsw_slave_index)(काष्ठा cpsw_common *cpsw, काष्ठा cpsw_priv *priv);

व्योम cpsw_पूर्णांकr_enable(काष्ठा cpsw_common *cpsw)
अणु
	ग_लिखोl_relaxed(0xFF, &cpsw->wr_regs->tx_en);
	ग_लिखोl_relaxed(0xFF, &cpsw->wr_regs->rx_en);

	cpdma_ctlr_पूर्णांक_ctrl(cpsw->dma, true);
पूर्ण

व्योम cpsw_पूर्णांकr_disable(काष्ठा cpsw_common *cpsw)
अणु
	ग_लिखोl_relaxed(0, &cpsw->wr_regs->tx_en);
	ग_लिखोl_relaxed(0, &cpsw->wr_regs->rx_en);

	cpdma_ctlr_पूर्णांक_ctrl(cpsw->dma, false);
पूर्ण

व्योम cpsw_tx_handler(व्योम *token, पूर्णांक len, पूर्णांक status)
अणु
	काष्ठा cpsw_meta_xdp	*xmeta;
	काष्ठा xdp_frame	*xdpf;
	काष्ठा net_device	*ndev;
	काष्ठा netdev_queue	*txq;
	काष्ठा sk_buff		*skb;
	पूर्णांक			ch;

	अगर (cpsw_is_xdpf_handle(token)) अणु
		xdpf = cpsw_handle_to_xdpf(token);
		xmeta = (व्योम *)xdpf + CPSW_XMETA_OFFSET;
		ndev = xmeta->ndev;
		ch = xmeta->ch;
		xdp_वापस_frame(xdpf);
	पूर्ण अन्यथा अणु
		skb = token;
		ndev = skb->dev;
		ch = skb_get_queue_mapping(skb);
		cpts_tx_बारtamp(ndev_to_cpsw(ndev)->cpts, skb);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	/* Check whether the queue is stopped due to stalled tx dma, अगर the
	 * queue is stopped then start the queue as we have मुक्त desc क्रम tx
	 */
	txq = netdev_get_tx_queue(ndev, ch);
	अगर (unlikely(netअगर_tx_queue_stopped(txq)))
		netअगर_tx_wake_queue(txq);

	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += len;
पूर्ण

irqवापस_t cpsw_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cpsw_common *cpsw = dev_id;

	ग_लिखोl(0, &cpsw->wr_regs->tx_en);
	cpdma_ctlr_eoi(cpsw->dma, CPDMA_EOI_TX);

	अगर (cpsw->quirk_irq) अणु
		disable_irq_nosync(cpsw->irqs_table[1]);
		cpsw->tx_irq_disabled = true;
	पूर्ण

	napi_schedule(&cpsw->napi_tx);
	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t cpsw_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cpsw_common *cpsw = dev_id;

	ग_लिखोl(0, &cpsw->wr_regs->rx_en);
	cpdma_ctlr_eoi(cpsw->dma, CPDMA_EOI_RX);

	अगर (cpsw->quirk_irq) अणु
		disable_irq_nosync(cpsw->irqs_table[0]);
		cpsw->rx_irq_disabled = true;
	पूर्ण

	napi_schedule(&cpsw->napi_rx);
	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t cpsw_misc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cpsw_common *cpsw = dev_id;

	ग_लिखोl(0, &cpsw->wr_regs->misc_en);
	cpdma_ctlr_eoi(cpsw->dma, CPDMA_EOI_MISC);
	cpts_misc_पूर्णांकerrupt(cpsw->cpts);
	ग_लिखोl(0x10, &cpsw->wr_regs->misc_en);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक cpsw_tx_mq_poll(काष्ठा napi_काष्ठा *napi_tx, पूर्णांक budget)
अणु
	काष्ठा cpsw_common	*cpsw = napi_to_cpsw(napi_tx);
	पूर्णांक			num_tx, cur_budget, ch;
	u32			ch_map;
	काष्ठा cpsw_vector	*txv;

	/* process every unprocessed channel */
	ch_map = cpdma_ctrl_txchs_state(cpsw->dma);
	क्रम (ch = 0, num_tx = 0; ch_map & 0xff; ch_map <<= 1, ch++) अणु
		अगर (!(ch_map & 0x80))
			जारी;

		txv = &cpsw->txv[ch];
		अगर (unlikely(txv->budget > budget - num_tx))
			cur_budget = budget - num_tx;
		अन्यथा
			cur_budget = txv->budget;

		num_tx += cpdma_chan_process(txv->ch, cur_budget);
		अगर (num_tx >= budget)
			अवरोध;
	पूर्ण

	अगर (num_tx < budget) अणु
		napi_complete(napi_tx);
		ग_लिखोl(0xff, &cpsw->wr_regs->tx_en);
	पूर्ण

	वापस num_tx;
पूर्ण

पूर्णांक cpsw_tx_poll(काष्ठा napi_काष्ठा *napi_tx, पूर्णांक budget)
अणु
	काष्ठा cpsw_common *cpsw = napi_to_cpsw(napi_tx);
	पूर्णांक num_tx;

	num_tx = cpdma_chan_process(cpsw->txv[0].ch, budget);
	अगर (num_tx < budget) अणु
		napi_complete(napi_tx);
		ग_लिखोl(0xff, &cpsw->wr_regs->tx_en);
		अगर (cpsw->tx_irq_disabled) अणु
			cpsw->tx_irq_disabled = false;
			enable_irq(cpsw->irqs_table[1]);
		पूर्ण
	पूर्ण

	वापस num_tx;
पूर्ण

पूर्णांक cpsw_rx_mq_poll(काष्ठा napi_काष्ठा *napi_rx, पूर्णांक budget)
अणु
	काष्ठा cpsw_common	*cpsw = napi_to_cpsw(napi_rx);
	पूर्णांक			num_rx, cur_budget, ch;
	u32			ch_map;
	काष्ठा cpsw_vector	*rxv;

	/* process every unprocessed channel */
	ch_map = cpdma_ctrl_rxchs_state(cpsw->dma);
	क्रम (ch = 0, num_rx = 0; ch_map; ch_map >>= 1, ch++) अणु
		अगर (!(ch_map & 0x01))
			जारी;

		rxv = &cpsw->rxv[ch];
		अगर (unlikely(rxv->budget > budget - num_rx))
			cur_budget = budget - num_rx;
		अन्यथा
			cur_budget = rxv->budget;

		num_rx += cpdma_chan_process(rxv->ch, cur_budget);
		अगर (num_rx >= budget)
			अवरोध;
	पूर्ण

	अगर (num_rx < budget) अणु
		napi_complete_करोne(napi_rx, num_rx);
		ग_लिखोl(0xff, &cpsw->wr_regs->rx_en);
	पूर्ण

	वापस num_rx;
पूर्ण

पूर्णांक cpsw_rx_poll(काष्ठा napi_काष्ठा *napi_rx, पूर्णांक budget)
अणु
	काष्ठा cpsw_common *cpsw = napi_to_cpsw(napi_rx);
	पूर्णांक num_rx;

	num_rx = cpdma_chan_process(cpsw->rxv[0].ch, budget);
	अगर (num_rx < budget) अणु
		napi_complete_करोne(napi_rx, num_rx);
		ग_लिखोl(0xff, &cpsw->wr_regs->rx_en);
		अगर (cpsw->rx_irq_disabled) अणु
			cpsw->rx_irq_disabled = false;
			enable_irq(cpsw->irqs_table[0]);
		पूर्ण
	पूर्ण

	वापस num_rx;
पूर्ण

व्योम cpsw_rx_vlan_encap(काष्ठा sk_buff *skb)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(skb->dev);
	u32 rx_vlan_encap_hdr = *((u32 *)skb->data);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	u16 vtag, vid, prio, pkt_type;

	/* Remove VLAN header encapsulation word */
	skb_pull(skb, CPSW_RX_VLAN_ENCAP_HDR_SIZE);

	pkt_type = (rx_vlan_encap_hdr >>
		    CPSW_RX_VLAN_ENCAP_HDR_PKT_TYPE_SHIFT) &
		    CPSW_RX_VLAN_ENCAP_HDR_PKT_TYPE_MSK;
	/* Ignore unknown & Priority-tagged packets*/
	अगर (pkt_type == CPSW_RX_VLAN_ENCAP_HDR_PKT_RESERV ||
	    pkt_type == CPSW_RX_VLAN_ENCAP_HDR_PKT_PRIO_TAG)
		वापस;

	vid = (rx_vlan_encap_hdr >>
	       CPSW_RX_VLAN_ENCAP_HDR_VID_SHIFT) &
	       VLAN_VID_MASK;
	/* Ignore vid 0 and pass packet as is */
	अगर (!vid)
		वापस;

	/* Untag P0 packets अगर set क्रम vlan */
	अगर (!cpsw_ale_get_vlan_p0_untag(cpsw->ale, vid)) अणु
		prio = (rx_vlan_encap_hdr >>
			CPSW_RX_VLAN_ENCAP_HDR_PRIO_SHIFT) &
			CPSW_RX_VLAN_ENCAP_HDR_PRIO_MSK;

		vtag = (prio << VLAN_PRIO_SHIFT) | vid;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vtag);
	पूर्ण

	/* strip vlan tag क्रम VLAN-tagged packet */
	अगर (pkt_type == CPSW_RX_VLAN_ENCAP_HDR_PKT_VLAN_TAG) अणु
		स_हटाओ(skb->data + VLAN_HLEN, skb->data, 2 * ETH_ALEN);
		skb_pull(skb, VLAN_HLEN);
	पूर्ण
पूर्ण

व्योम cpsw_set_slave_mac(काष्ठा cpsw_slave *slave, काष्ठा cpsw_priv *priv)
अणु
	slave_ग_लिखो(slave, mac_hi(priv->mac_addr), SA_HI);
	slave_ग_लिखो(slave, mac_lo(priv->mac_addr), SA_LO);
पूर्ण

व्योम soft_reset(स्थिर अक्षर *module, व्योम __iomem *reg)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;

	ग_लिखोl_relaxed(1, reg);
	करो अणु
		cpu_relax();
	पूर्ण जबतक ((पढ़ोl_relaxed(reg) & 1) && समय_after(समयout, jअगरfies));

	WARN(पढ़ोl_relaxed(reg) & 1, "failed to soft-reset %s\n", module);
पूर्ण

व्योम cpsw_nकरो_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक ch;

	cpsw_err(priv, tx_err, "transmit timeout, restarting dma\n");
	ndev->stats.tx_errors++;
	cpsw_पूर्णांकr_disable(cpsw);
	क्रम (ch = 0; ch < cpsw->tx_ch_num; ch++) अणु
		cpdma_chan_stop(cpsw->txv[ch].ch);
		cpdma_chan_start(cpsw->txv[ch].ch);
	पूर्ण

	cpsw_पूर्णांकr_enable(cpsw);
	netअगर_trans_update(ndev);
	netअगर_tx_wake_all_queues(ndev);
पूर्ण

अटल पूर्णांक cpsw_get_common_speed(काष्ठा cpsw_common *cpsw)
अणु
	पूर्णांक i, speed;

	क्रम (i = 0, speed = 0; i < cpsw->data.slaves; i++)
		अगर (cpsw->slaves[i].phy && cpsw->slaves[i].phy->link)
			speed += cpsw->slaves[i].phy->speed;

	वापस speed;
पूर्ण

पूर्णांक cpsw_need_resplit(काष्ठा cpsw_common *cpsw)
अणु
	पूर्णांक i, rlim_ch_num;
	पूर्णांक speed, ch_rate;

	/* re-split resources only in हाल speed was changed */
	speed = cpsw_get_common_speed(cpsw);
	अगर (speed == cpsw->speed || !speed)
		वापस 0;

	cpsw->speed = speed;

	क्रम (i = 0, rlim_ch_num = 0; i < cpsw->tx_ch_num; i++) अणु
		ch_rate = cpdma_chan_get_rate(cpsw->txv[i].ch);
		अगर (!ch_rate)
			अवरोध;

		rlim_ch_num++;
	पूर्ण

	/* हालs not dependent on speed */
	अगर (!rlim_ch_num || rlim_ch_num == cpsw->tx_ch_num)
		वापस 0;

	वापस 1;
पूर्ण

व्योम cpsw_split_res(काष्ठा cpsw_common *cpsw)
अणु
	u32 consumed_rate = 0, bigest_rate = 0;
	काष्ठा cpsw_vector *txv = cpsw->txv;
	पूर्णांक i, ch_weight, rlim_ch_num = 0;
	पूर्णांक budget, bigest_rate_ch = 0;
	u32 ch_rate, max_rate;
	पूर्णांक ch_budget = 0;

	क्रम (i = 0; i < cpsw->tx_ch_num; i++) अणु
		ch_rate = cpdma_chan_get_rate(txv[i].ch);
		अगर (!ch_rate)
			जारी;

		rlim_ch_num++;
		consumed_rate += ch_rate;
	पूर्ण

	अगर (cpsw->tx_ch_num == rlim_ch_num) अणु
		max_rate = consumed_rate;
	पूर्ण अन्यथा अगर (!rlim_ch_num) अणु
		ch_budget = CPSW_POLL_WEIGHT / cpsw->tx_ch_num;
		bigest_rate = 0;
		max_rate = consumed_rate;
	पूर्ण अन्यथा अणु
		max_rate = cpsw->speed * 1000;

		/* अगर max_rate is less then expected due to reduced link speed,
		 * split proportionally according next potential max speed
		 */
		अगर (max_rate < consumed_rate)
			max_rate *= 10;

		अगर (max_rate < consumed_rate)
			max_rate *= 10;

		ch_budget = (consumed_rate * CPSW_POLL_WEIGHT) / max_rate;
		ch_budget = (CPSW_POLL_WEIGHT - ch_budget) /
			    (cpsw->tx_ch_num - rlim_ch_num);
		bigest_rate = (max_rate - consumed_rate) /
			      (cpsw->tx_ch_num - rlim_ch_num);
	पूर्ण

	/* split tx weight/budget */
	budget = CPSW_POLL_WEIGHT;
	क्रम (i = 0; i < cpsw->tx_ch_num; i++) अणु
		ch_rate = cpdma_chan_get_rate(txv[i].ch);
		अगर (ch_rate) अणु
			txv[i].budget = (ch_rate * CPSW_POLL_WEIGHT) / max_rate;
			अगर (!txv[i].budget)
				txv[i].budget++;
			अगर (ch_rate > bigest_rate) अणु
				bigest_rate_ch = i;
				bigest_rate = ch_rate;
			पूर्ण

			ch_weight = (ch_rate * 100) / max_rate;
			अगर (!ch_weight)
				ch_weight++;
			cpdma_chan_set_weight(cpsw->txv[i].ch, ch_weight);
		पूर्ण अन्यथा अणु
			txv[i].budget = ch_budget;
			अगर (!bigest_rate_ch)
				bigest_rate_ch = i;
			cpdma_chan_set_weight(cpsw->txv[i].ch, 0);
		पूर्ण

		budget -= txv[i].budget;
	पूर्ण

	अगर (budget)
		txv[bigest_rate_ch].budget += budget;

	/* split rx budget */
	budget = CPSW_POLL_WEIGHT;
	ch_budget = budget / cpsw->rx_ch_num;
	क्रम (i = 0; i < cpsw->rx_ch_num; i++) अणु
		cpsw->rxv[i].budget = ch_budget;
		budget -= ch_budget;
	पूर्ण

	अगर (budget)
		cpsw->rxv[0].budget += budget;
पूर्ण

पूर्णांक cpsw_init_common(काष्ठा cpsw_common *cpsw, व्योम __iomem *ss_regs,
		     पूर्णांक ale_ageout, phys_addr_t desc_mem_phys,
		     पूर्णांक descs_pool_size)
अणु
	u32 slave_offset, sliver_offset, slave_size;
	काष्ठा cpsw_ale_params ale_params;
	काष्ठा cpsw_platक्रमm_data *data;
	काष्ठा cpdma_params dma_params;
	काष्ठा device *dev = cpsw->dev;
	काष्ठा device_node *cpts_node;
	व्योम __iomem *cpts_regs;
	पूर्णांक ret = 0, i;

	data = &cpsw->data;
	cpsw->rx_ch_num = 1;
	cpsw->tx_ch_num = 1;

	cpsw->version = पढ़ोl(&cpsw->regs->id_ver);

	स_रखो(&dma_params, 0, माप(dma_params));
	स_रखो(&ale_params, 0, माप(ale_params));

	चयन (cpsw->version) अणु
	हाल CPSW_VERSION_1:
		cpsw->host_port_regs = ss_regs + CPSW1_HOST_PORT_OFFSET;
		cpts_regs	     = ss_regs + CPSW1_CPTS_OFFSET;
		cpsw->hw_stats	     = ss_regs + CPSW1_HW_STATS;
		dma_params.dmaregs   = ss_regs + CPSW1_CPDMA_OFFSET;
		dma_params.txhdp     = ss_regs + CPSW1_STATERAM_OFFSET;
		ale_params.ale_regs  = ss_regs + CPSW1_ALE_OFFSET;
		slave_offset         = CPSW1_SLAVE_OFFSET;
		slave_size           = CPSW1_SLAVE_SIZE;
		sliver_offset        = CPSW1_SLIVER_OFFSET;
		dma_params.desc_mem_phys = 0;
		अवरोध;
	हाल CPSW_VERSION_2:
	हाल CPSW_VERSION_3:
	हाल CPSW_VERSION_4:
		cpsw->host_port_regs = ss_regs + CPSW2_HOST_PORT_OFFSET;
		cpts_regs	     = ss_regs + CPSW2_CPTS_OFFSET;
		cpsw->hw_stats	     = ss_regs + CPSW2_HW_STATS;
		dma_params.dmaregs   = ss_regs + CPSW2_CPDMA_OFFSET;
		dma_params.txhdp     = ss_regs + CPSW2_STATERAM_OFFSET;
		ale_params.ale_regs  = ss_regs + CPSW2_ALE_OFFSET;
		slave_offset         = CPSW2_SLAVE_OFFSET;
		slave_size           = CPSW2_SLAVE_SIZE;
		sliver_offset        = CPSW2_SLIVER_OFFSET;
		dma_params.desc_mem_phys = desc_mem_phys;
		अवरोध;
	शेष:
		dev_err(dev, "unknown version 0x%08x\n", cpsw->version);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		काष्ठा cpsw_slave *slave = &cpsw->slaves[i];
		व्योम __iomem		*regs = cpsw->regs;

		slave->slave_num = i;
		slave->data	= &cpsw->data.slave_data[i];
		slave->regs	= regs + slave_offset;
		slave->port_vlan = slave->data->dual_emac_res_vlan;
		slave->mac_sl = cpsw_sl_get("cpsw", dev, regs + sliver_offset);
		अगर (IS_ERR(slave->mac_sl))
			वापस PTR_ERR(slave->mac_sl);

		slave_offset  += slave_size;
		sliver_offset += SLIVER_SIZE;
	पूर्ण

	ale_params.dev			= dev;
	ale_params.ale_ageout		= ale_ageout;
	ale_params.ale_ports		= CPSW_ALE_PORTS_NUM;
	ale_params.dev_id		= "cpsw";

	cpsw->ale = cpsw_ale_create(&ale_params);
	अगर (IS_ERR(cpsw->ale)) अणु
		dev_err(dev, "error initializing ale engine\n");
		वापस PTR_ERR(cpsw->ale);
	पूर्ण

	dma_params.dev		= dev;
	dma_params.rxthresh	= dma_params.dmaregs + CPDMA_RXTHRESH;
	dma_params.rxमुक्त	= dma_params.dmaregs + CPDMA_RXFREE;
	dma_params.rxhdp	= dma_params.txhdp + CPDMA_RXHDP;
	dma_params.txcp		= dma_params.txhdp + CPDMA_TXCP;
	dma_params.rxcp		= dma_params.txhdp + CPDMA_RXCP;

	dma_params.num_chan		= data->channels;
	dma_params.has_soft_reset	= true;
	dma_params.min_packet_size	= CPSW_MIN_PACKET_SIZE;
	dma_params.desc_mem_size	= data->bd_ram_size;
	dma_params.desc_align		= 16;
	dma_params.has_ext_regs		= true;
	dma_params.desc_hw_addr         = dma_params.desc_mem_phys;
	dma_params.bus_freq_mhz		= cpsw->bus_freq_mhz;
	dma_params.descs_pool_size	= descs_pool_size;

	cpsw->dma = cpdma_ctlr_create(&dma_params);
	अगर (!cpsw->dma) अणु
		dev_err(dev, "error initializing dma\n");
		वापस -ENOMEM;
	पूर्ण

	cpts_node = of_get_child_by_name(cpsw->dev->of_node, "cpts");
	अगर (!cpts_node)
		cpts_node = cpsw->dev->of_node;

	cpsw->cpts = cpts_create(cpsw->dev, cpts_regs, cpts_node,
				 CPTS_N_ETX_TS);
	अगर (IS_ERR(cpsw->cpts)) अणु
		ret = PTR_ERR(cpsw->cpts);
		cpdma_ctlr_destroy(cpsw->dma);
	पूर्ण
	of_node_put(cpts_node);

	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_TI_CPTS)

अटल व्योम cpsw_hwtstamp_v1(काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_slave *slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];
	u32 ts_en, seq_id;

	अगर (!priv->tx_ts_enabled && !priv->rx_ts_enabled) अणु
		slave_ग_लिखो(slave, 0, CPSW1_TS_CTL);
		वापस;
	पूर्ण

	seq_id = (30 << CPSW_V1_SEQ_ID_OFS_SHIFT) | ETH_P_1588;
	ts_en = EVENT_MSG_BITS << CPSW_V1_MSG_TYPE_OFS;

	अगर (priv->tx_ts_enabled)
		ts_en |= CPSW_V1_TS_TX_EN;

	अगर (priv->rx_ts_enabled)
		ts_en |= CPSW_V1_TS_RX_EN;

	slave_ग_लिखो(slave, ts_en, CPSW1_TS_CTL);
	slave_ग_लिखो(slave, seq_id, CPSW1_TS_SEQ_LTYPE);
पूर्ण

अटल व्योम cpsw_hwtstamp_v2(काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_slave *slave;
	u32 ctrl, mtype;

	slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];

	ctrl = slave_पढ़ो(slave, CPSW2_CONTROL);
	चयन (cpsw->version) अणु
	हाल CPSW_VERSION_2:
		ctrl &= ~CTRL_V2_ALL_TS_MASK;

		अगर (priv->tx_ts_enabled)
			ctrl |= CTRL_V2_TX_TS_BITS;

		अगर (priv->rx_ts_enabled)
			ctrl |= CTRL_V2_RX_TS_BITS;
		अवरोध;
	हाल CPSW_VERSION_3:
	शेष:
		ctrl &= ~CTRL_V3_ALL_TS_MASK;

		अगर (priv->tx_ts_enabled)
			ctrl |= CTRL_V3_TX_TS_BITS;

		अगर (priv->rx_ts_enabled)
			ctrl |= CTRL_V3_RX_TS_BITS;
		अवरोध;
	पूर्ण

	mtype = (30 << TS_SEQ_ID_OFFSET_SHIFT) | EVENT_MSG_BITS;

	slave_ग_लिखो(slave, mtype, CPSW2_TS_SEQ_MTYPE);
	slave_ग_लिखो(slave, ctrl, CPSW2_CONTROL);
	ग_लिखोl_relaxed(ETH_P_1588, &cpsw->regs->ts_ltype);
	ग_लिखोl_relaxed(ETH_P_8021Q, &cpsw->regs->vlan_ltype);
पूर्ण

अटल पूर्णांक cpsw_hwtstamp_set(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(dev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा hwtstamp_config cfg;

	अगर (cpsw->version != CPSW_VERSION_1 &&
	    cpsw->version != CPSW_VERSION_2 &&
	    cpsw->version != CPSW_VERSION_3)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (cfg.flags)
		वापस -EINVAL;

	अगर (cfg.tx_type != HWTSTAMP_TX_OFF && cfg.tx_type != HWTSTAMP_TX_ON)
		वापस -दुस्फल;

	चयन (cfg.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		priv->rx_ts_enabled = 0;
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_NTP_ALL:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		वापस -दुस्फल;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		priv->rx_ts_enabled = HWTSTAMP_FILTER_PTP_V2_EVENT;
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	priv->tx_ts_enabled = cfg.tx_type == HWTSTAMP_TX_ON;

	चयन (cpsw->version) अणु
	हाल CPSW_VERSION_1:
		cpsw_hwtstamp_v1(priv);
		अवरोध;
	हाल CPSW_VERSION_2:
	हाल CPSW_VERSION_3:
		cpsw_hwtstamp_v2(priv);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक cpsw_hwtstamp_get(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(dev);
	काष्ठा cpsw_priv *priv = netdev_priv(dev);
	काष्ठा hwtstamp_config cfg;

	अगर (cpsw->version != CPSW_VERSION_1 &&
	    cpsw->version != CPSW_VERSION_2 &&
	    cpsw->version != CPSW_VERSION_3)
		वापस -EOPNOTSUPP;

	cfg.flags = 0;
	cfg.tx_type = priv->tx_ts_enabled ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;
	cfg.rx_filter = priv->rx_ts_enabled;

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण
#अन्यथा
अटल पूर्णांक cpsw_hwtstamp_get(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक cpsw_hwtstamp_set(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /*CONFIG_TI_CPTS*/

पूर्णांक cpsw_nकरो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(dev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक slave_no = cpsw_slave_index(cpsw, priv);

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस cpsw_hwtstamp_set(dev, req);
	हाल SIOCGHWTSTAMP:
		वापस cpsw_hwtstamp_get(dev, req);
	पूर्ण

	अगर (!cpsw->slaves[slave_no].phy)
		वापस -EOPNOTSUPP;
	वापस phy_mii_ioctl(cpsw->slaves[slave_no].phy, req, cmd);
पूर्ण

पूर्णांक cpsw_nकरो_set_tx_maxrate(काष्ठा net_device *ndev, पूर्णांक queue, u32 rate)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_slave *slave;
	u32 min_rate;
	u32 ch_rate;
	पूर्णांक i, ret;

	ch_rate = netdev_get_tx_queue(ndev, queue)->tx_maxrate;
	अगर (ch_rate == rate)
		वापस 0;

	ch_rate = rate * 1000;
	min_rate = cpdma_chan_get_min_rate(cpsw->dma);
	अगर ((ch_rate < min_rate && ch_rate)) अणु
		dev_err(priv->dev, "The channel rate cannot be less than %dMbps",
			min_rate);
		वापस -EINVAL;
	पूर्ण

	अगर (rate > cpsw->speed) अणु
		dev_err(priv->dev, "The channel rate cannot be more than 2Gbps");
		वापस -EINVAL;
	पूर्ण

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	ret = cpdma_chan_set_rate(cpsw->txv[queue].ch, ch_rate);
	pm_runसमय_put(cpsw->dev);

	अगर (ret)
		वापस ret;

	/* update rates क्रम slaves tx queues */
	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		slave = &cpsw->slaves[i];
		अगर (!slave->ndev)
			जारी;

		netdev_get_tx_queue(slave->ndev, queue)->tx_maxrate = rate;
	पूर्ण

	cpsw_split_res(cpsw);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_tc_to_fअगरo(पूर्णांक tc, पूर्णांक num_tc)
अणु
	अगर (tc == num_tc - 1)
		वापस 0;

	वापस CPSW_FIFO_SHAPERS_NUM - tc;
पूर्ण

bool cpsw_shp_is_off(काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_slave *slave;
	u32 shअगरt, mask, val;

	val = पढ़ोl_relaxed(&cpsw->regs->ptype);

	slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];
	shअगरt = CPSW_FIFO_SHAPE_EN_SHIFT + 3 * slave->slave_num;
	mask = 7 << shअगरt;
	val = val & mask;

	वापस !val;
पूर्ण

अटल व्योम cpsw_fअगरo_shp_on(काष्ठा cpsw_priv *priv, पूर्णांक fअगरo, पूर्णांक on)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_slave *slave;
	u32 shअगरt, mask, val;

	val = पढ़ोl_relaxed(&cpsw->regs->ptype);

	slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];
	shअगरt = CPSW_FIFO_SHAPE_EN_SHIFT + 3 * slave->slave_num;
	mask = (1 << --fअगरo) << shअगरt;
	val = on ? val | mask : val & ~mask;

	ग_लिखोl_relaxed(val, &cpsw->regs->ptype);
पूर्ण

अटल पूर्णांक cpsw_set_fअगरo_bw(काष्ठा cpsw_priv *priv, पूर्णांक fअगरo, पूर्णांक bw)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	u32 val = 0, send_pct, shअगरt;
	काष्ठा cpsw_slave *slave;
	पूर्णांक pct = 0, i;

	अगर (bw > priv->shp_cfg_speed * 1000)
		जाओ err;

	/* shaping has to stay enabled क्रम highest fअगरos linearly
	 * and fअगरo bw no more then पूर्णांकerface can allow
	 */
	slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];
	send_pct = slave_पढ़ो(slave, SEND_PERCENT);
	क्रम (i = CPSW_FIFO_SHAPERS_NUM; i > 0; i--) अणु
		अगर (!bw) अणु
			अगर (i >= fअगरo || !priv->fअगरo_bw[i])
				जारी;

			dev_warn(priv->dev, "Prev FIFO%d is shaped", i);
			जारी;
		पूर्ण

		अगर (!priv->fअगरo_bw[i] && i > fअगरo) अणु
			dev_err(priv->dev, "Upper FIFO%d is not shaped", i);
			वापस -EINVAL;
		पूर्ण

		shअगरt = (i - 1) * 8;
		अगर (i == fअगरo) अणु
			send_pct &= ~(CPSW_PCT_MASK << shअगरt);
			val = DIV_ROUND_UP(bw, priv->shp_cfg_speed * 10);
			अगर (!val)
				val = 1;

			send_pct |= val << shअगरt;
			pct += val;
			जारी;
		पूर्ण

		अगर (priv->fअगरo_bw[i])
			pct += (send_pct >> shअगरt) & CPSW_PCT_MASK;
	पूर्ण

	अगर (pct >= 100)
		जाओ err;

	slave_ग_लिखो(slave, send_pct, SEND_PERCENT);
	priv->fअगरo_bw[fअगरo] = bw;

	dev_warn(priv->dev, "set FIFO%d bw = %d\n", fअगरo,
		 DIV_ROUND_CLOSEST(val * priv->shp_cfg_speed, 100));

	वापस 0;
err:
	dev_err(priv->dev, "Bandwidth doesn't fit in tc configuration");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cpsw_set_fअगरo_rlimit(काष्ठा cpsw_priv *priv, पूर्णांक fअगरo, पूर्णांक bw)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_slave *slave;
	u32 tx_in_ctl_rg, val;
	पूर्णांक ret;

	ret = cpsw_set_fअगरo_bw(priv, fअगरo, bw);
	अगर (ret)
		वापस ret;

	slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];
	tx_in_ctl_rg = cpsw->version == CPSW_VERSION_1 ?
		       CPSW1_TX_IN_CTL : CPSW2_TX_IN_CTL;

	अगर (!bw)
		cpsw_fअगरo_shp_on(priv, fअगरo, bw);

	val = slave_पढ़ो(slave, tx_in_ctl_rg);
	अगर (cpsw_shp_is_off(priv)) अणु
		/* disable FIFOs rate limited queues */
		val &= ~(0xf << CPSW_FIFO_RATE_EN_SHIFT);

		/* set type of FIFO queues to normal priority mode */
		val &= ~(3 << CPSW_FIFO_QUEUE_TYPE_SHIFT);

		/* set type of FIFO queues to be rate limited */
		अगर (bw)
			val |= 2 << CPSW_FIFO_QUEUE_TYPE_SHIFT;
		अन्यथा
			priv->shp_cfg_speed = 0;
	पूर्ण

	/* toggle a FIFO rate limited queue */
	अगर (bw)
		val |= BIT(fअगरo + CPSW_FIFO_RATE_EN_SHIFT);
	अन्यथा
		val &= ~BIT(fअगरo + CPSW_FIFO_RATE_EN_SHIFT);
	slave_ग_लिखो(slave, val, tx_in_ctl_rg);

	/* FIFO transmit shape enable */
	cpsw_fअगरo_shp_on(priv, fअगरo, bw);
	वापस 0;
पूर्ण

/* Defaults:
 * class A - prio 3
 * class B - prio 2
 * shaping क्रम class A should be set first
 */
अटल पूर्णांक cpsw_set_cbs(काष्ठा net_device *ndev,
			काष्ठा tc_cbs_qopt_offload *qopt)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_slave *slave;
	पूर्णांक prev_speed = 0;
	पूर्णांक tc, ret, fअगरo;
	u32 bw = 0;

	tc = netdev_txq_to_tc(priv->ndev, qopt->queue);

	/* enable channels in backward order, as highest FIFOs must be rate
	 * limited first and क्रम compliance with CPDMA rate limited channels
	 * that also used in bacward order. FIFO0 cannot be rate limited.
	 */
	fअगरo = cpsw_tc_to_fअगरo(tc, ndev->num_tc);
	अगर (!fअगरo) अणु
		dev_err(priv->dev, "Last tc%d can't be rate limited", tc);
		वापस -EINVAL;
	पूर्ण

	/* करो nothing, it's disabled anyway */
	अगर (!qopt->enable && !priv->fअगरo_bw[fअगरo])
		वापस 0;

	/* shapers can be set अगर link speed is known */
	slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];
	अगर (slave->phy && slave->phy->link) अणु
		अगर (priv->shp_cfg_speed &&
		    priv->shp_cfg_speed != slave->phy->speed)
			prev_speed = priv->shp_cfg_speed;

		priv->shp_cfg_speed = slave->phy->speed;
	पूर्ण

	अगर (!priv->shp_cfg_speed) अणु
		dev_err(priv->dev, "Link speed is not known");
		वापस -1;
	पूर्ण

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	bw = qopt->enable ? qopt->idleslope : 0;
	ret = cpsw_set_fअगरo_rlimit(priv, fअगरo, bw);
	अगर (ret) अणु
		priv->shp_cfg_speed = prev_speed;
		prev_speed = 0;
	पूर्ण

	अगर (bw && prev_speed)
		dev_warn(priv->dev,
			 "Speed was changed, CBS shaper speeds are changed!");

	pm_runसमय_put_sync(cpsw->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_set_mqprio(काष्ठा net_device *ndev, व्योम *type_data)
अणु
	काष्ठा tc_mqprio_qopt_offload *mqprio = type_data;
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक fअगरo, num_tc, count, offset;
	काष्ठा cpsw_slave *slave;
	u32 tx_prio_map = 0;
	पूर्णांक i, tc, ret;

	num_tc = mqprio->qopt.num_tc;
	अगर (num_tc > CPSW_TC_NUM)
		वापस -EINVAL;

	अगर (mqprio->mode != TC_MQPRIO_MODE_DCB)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	अगर (num_tc) अणु
		क्रम (i = 0; i < 8; i++) अणु
			tc = mqprio->qopt.prio_tc_map[i];
			fअगरo = cpsw_tc_to_fअगरo(tc, num_tc);
			tx_prio_map |= fअगरo << (4 * i);
		पूर्ण

		netdev_set_num_tc(ndev, num_tc);
		क्रम (i = 0; i < num_tc; i++) अणु
			count = mqprio->qopt.count[i];
			offset = mqprio->qopt.offset[i];
			netdev_set_tc_queue(ndev, i, count, offset);
		पूर्ण
	पूर्ण

	अगर (!mqprio->qopt.hw) अणु
		/* restore शेष configuration */
		netdev_reset_tc(ndev);
		tx_prio_map = TX_PRIORITY_MAPPING;
	पूर्ण

	priv->mqprio_hw = mqprio->qopt.hw;

	offset = cpsw->version == CPSW_VERSION_1 ?
		 CPSW1_TX_PRI_MAP : CPSW2_TX_PRI_MAP;

	slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];
	slave_ग_लिखो(slave, tx_prio_map, offset);

	pm_runसमय_put_sync(cpsw->dev);

	वापस 0;
पूर्ण

पूर्णांक cpsw_nकरो_setup_tc(काष्ठा net_device *ndev, क्रमागत tc_setup_type type,
		      व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_QDISC_CBS:
		वापस cpsw_set_cbs(ndev, type_data);

	हाल TC_SETUP_QDISC_MQPRIO:
		वापस cpsw_set_mqprio(ndev, type_data);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

व्योम cpsw_cbs_resume(काष्ठा cpsw_slave *slave, काष्ठा cpsw_priv *priv)
अणु
	पूर्णांक fअगरo, bw;

	क्रम (fअगरo = CPSW_FIFO_SHAPERS_NUM; fअगरo > 0; fअगरo--) अणु
		bw = priv->fअगरo_bw[fअगरo];
		अगर (!bw)
			जारी;

		cpsw_set_fअगरo_rlimit(priv, fअगरo, bw);
	पूर्ण
पूर्ण

व्योम cpsw_mqprio_resume(काष्ठा cpsw_slave *slave, काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	u32 tx_prio_map = 0;
	पूर्णांक i, tc, fअगरo;
	u32 tx_prio_rg;

	अगर (!priv->mqprio_hw)
		वापस;

	क्रम (i = 0; i < 8; i++) अणु
		tc = netdev_get_prio_tc_map(priv->ndev, i);
		fअगरo = CPSW_FIFO_SHAPERS_NUM - tc;
		tx_prio_map |= fअगरo << (4 * i);
	पूर्ण

	tx_prio_rg = cpsw->version == CPSW_VERSION_1 ?
		     CPSW1_TX_PRI_MAP : CPSW2_TX_PRI_MAP;

	slave_ग_लिखो(slave, tx_prio_map, tx_prio_rg);
पूर्ण

पूर्णांक cpsw_fill_rx_channels(काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_meta_xdp *xmeta;
	काष्ठा page_pool *pool;
	काष्ठा page *page;
	पूर्णांक ch_buf_num;
	पूर्णांक ch, i, ret;
	dma_addr_t dma;

	क्रम (ch = 0; ch < cpsw->rx_ch_num; ch++) अणु
		pool = cpsw->page_pool[ch];
		ch_buf_num = cpdma_chan_get_rx_buf_num(cpsw->rxv[ch].ch);
		क्रम (i = 0; i < ch_buf_num; i++) अणु
			page = page_pool_dev_alloc_pages(pool);
			अगर (!page) अणु
				cpsw_err(priv, अगरup, "allocate rx page err\n");
				वापस -ENOMEM;
			पूर्ण

			xmeta = page_address(page) + CPSW_XMETA_OFFSET;
			xmeta->ndev = priv->ndev;
			xmeta->ch = ch;

			dma = page_pool_get_dma_addr(page) + CPSW_HEADROOM;
			ret = cpdma_chan_idle_submit_mapped(cpsw->rxv[ch].ch,
							    page, dma,
							    cpsw->rx_packet_max,
							    0);
			अगर (ret < 0) अणु
				cpsw_err(priv, अगरup,
					 "cannot submit page to channel %d rx, error %d\n",
					 ch, ret);
				page_pool_recycle_direct(pool, page);
				वापस ret;
			पूर्ण
		पूर्ण

		cpsw_info(priv, अगरup, "ch %d rx, submitted %d descriptors\n",
			  ch, ch_buf_num);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा page_pool *cpsw_create_page_pool(काष्ठा cpsw_common *cpsw,
					       पूर्णांक size)
अणु
	काष्ठा page_pool_params pp_params;
	काष्ठा page_pool *pool;

	pp_params.order = 0;
	pp_params.flags = PP_FLAG_DMA_MAP;
	pp_params.pool_size = size;
	pp_params.nid = NUMA_NO_NODE;
	pp_params.dma_dir = DMA_BIसूचीECTIONAL;
	pp_params.dev = cpsw->dev;

	pool = page_pool_create(&pp_params);
	अगर (IS_ERR(pool))
		dev_err(cpsw->dev, "cannot create rx page pool\n");

	वापस pool;
पूर्ण

अटल पूर्णांक cpsw_create_rx_pool(काष्ठा cpsw_common *cpsw, पूर्णांक ch)
अणु
	काष्ठा page_pool *pool;
	पूर्णांक ret = 0, pool_size;

	pool_size = cpdma_chan_get_rx_buf_num(cpsw->rxv[ch].ch);
	pool = cpsw_create_page_pool(cpsw, pool_size);
	अगर (IS_ERR(pool))
		ret = PTR_ERR(pool);
	अन्यथा
		cpsw->page_pool[ch] = pool;

	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_ndev_create_xdp_rxq(काष्ठा cpsw_priv *priv, पूर्णांक ch)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा xdp_rxq_info *rxq;
	काष्ठा page_pool *pool;
	पूर्णांक ret;

	pool = cpsw->page_pool[ch];
	rxq = &priv->xdp_rxq[ch];

	ret = xdp_rxq_info_reg(rxq, priv->ndev, ch, 0);
	अगर (ret)
		वापस ret;

	ret = xdp_rxq_info_reg_mem_model(rxq, MEM_TYPE_PAGE_POOL, pool);
	अगर (ret)
		xdp_rxq_info_unreg(rxq);

	वापस ret;
पूर्ण

अटल व्योम cpsw_ndev_destroy_xdp_rxq(काष्ठा cpsw_priv *priv, पूर्णांक ch)
अणु
	काष्ठा xdp_rxq_info *rxq = &priv->xdp_rxq[ch];

	अगर (!xdp_rxq_info_is_reg(rxq))
		वापस;

	xdp_rxq_info_unreg(rxq);
पूर्ण

व्योम cpsw_destroy_xdp_rxqs(काष्ठा cpsw_common *cpsw)
अणु
	काष्ठा net_device *ndev;
	पूर्णांक i, ch;

	क्रम (ch = 0; ch < cpsw->rx_ch_num; ch++) अणु
		क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
			ndev = cpsw->slaves[i].ndev;
			अगर (!ndev)
				जारी;

			cpsw_ndev_destroy_xdp_rxq(netdev_priv(ndev), ch);
		पूर्ण

		page_pool_destroy(cpsw->page_pool[ch]);
		cpsw->page_pool[ch] = शून्य;
	पूर्ण
पूर्ण

पूर्णांक cpsw_create_xdp_rxqs(काष्ठा cpsw_common *cpsw)
अणु
	काष्ठा net_device *ndev;
	पूर्णांक i, ch, ret;

	क्रम (ch = 0; ch < cpsw->rx_ch_num; ch++) अणु
		ret = cpsw_create_rx_pool(cpsw, ch);
		अगर (ret)
			जाओ err_cleanup;

		/* using same page pool is allowed as no running rx handlers
		 * simultaneously क्रम both ndevs
		 */
		क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
			ndev = cpsw->slaves[i].ndev;
			अगर (!ndev)
				जारी;

			ret = cpsw_ndev_create_xdp_rxq(netdev_priv(ndev), ch);
			अगर (ret)
				जाओ err_cleanup;
		पूर्ण
	पूर्ण

	वापस 0;

err_cleanup:
	cpsw_destroy_xdp_rxqs(cpsw);

	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_xdp_prog_setup(काष्ठा cpsw_priv *priv, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा bpf_prog *prog = bpf->prog;

	अगर (!priv->xdpi.prog && !prog)
		वापस 0;

	WRITE_ONCE(priv->xdp_prog, prog);

	xdp_attachment_setup(&priv->xdpi, bpf);

	वापस 0;
पूर्ण

पूर्णांक cpsw_nकरो_bpf(काष्ठा net_device *ndev, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);

	चयन (bpf->command) अणु
	हाल XDP_SETUP_PROG:
		वापस cpsw_xdp_prog_setup(priv, bpf);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक cpsw_xdp_tx_frame(काष्ठा cpsw_priv *priv, काष्ठा xdp_frame *xdpf,
		      काष्ठा page *page, पूर्णांक port)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_meta_xdp *xmeta;
	काष्ठा cpdma_chan *txch;
	dma_addr_t dma;
	पूर्णांक ret;

	xmeta = (व्योम *)xdpf + CPSW_XMETA_OFFSET;
	xmeta->ndev = priv->ndev;
	xmeta->ch = 0;
	txch = cpsw->txv[0].ch;

	अगर (page) अणु
		dma = page_pool_get_dma_addr(page);
		dma += xdpf->headroom + माप(काष्ठा xdp_frame);
		ret = cpdma_chan_submit_mapped(txch, cpsw_xdpf_to_handle(xdpf),
					       dma, xdpf->len, port);
	पूर्ण अन्यथा अणु
		अगर (माप(*xmeta) > xdpf->headroom)
			वापस -EINVAL;

		ret = cpdma_chan_submit(txch, cpsw_xdpf_to_handle(xdpf),
					xdpf->data, xdpf->len, port);
	पूर्ण

	अगर (ret)
		priv->ndev->stats.tx_dropped++;

	वापस ret;
पूर्ण

पूर्णांक cpsw_run_xdp(काष्ठा cpsw_priv *priv, पूर्णांक ch, काष्ठा xdp_buff *xdp,
		 काष्ठा page *page, पूर्णांक port, पूर्णांक *len)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा net_device *ndev = priv->ndev;
	पूर्णांक ret = CPSW_XDP_CONSUMED;
	काष्ठा xdp_frame *xdpf;
	काष्ठा bpf_prog *prog;
	u32 act;

	rcu_पढ़ो_lock();

	prog = READ_ONCE(priv->xdp_prog);
	अगर (!prog) अणु
		ret = CPSW_XDP_PASS;
		जाओ out;
	पूर्ण

	act = bpf_prog_run_xdp(prog, xdp);
	/* XDP prog might have changed packet data and boundaries */
	*len = xdp->data_end - xdp->data;

	चयन (act) अणु
	हाल XDP_PASS:
		ret = CPSW_XDP_PASS;
		जाओ out;
	हाल XDP_TX:
		xdpf = xdp_convert_buff_to_frame(xdp);
		अगर (unlikely(!xdpf))
			जाओ drop;

		अगर (cpsw_xdp_tx_frame(priv, xdpf, page, port))
			xdp_वापस_frame_rx_napi(xdpf);
		अवरोध;
	हाल XDP_REसूचीECT:
		अगर (xdp_करो_redirect(ndev, xdp, prog))
			जाओ drop;

		/*  Have to flush here, per packet, instead of करोing it in bulk
		 *  at the end of the napi handler. The RX devices on this
		 *  particular hardware is sharing a common queue, so the
		 *  incoming device might change per packet.
		 */
		xdp_करो_flush_map();
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(ndev, prog, act);
		fallthrough;	/* handle पातs by dropping packet */
	हाल XDP_DROP:
		ndev->stats.rx_bytes += *len;
		ndev->stats.rx_packets++;
		जाओ drop;
	पूर्ण

	ndev->stats.rx_bytes += *len;
	ndev->stats.rx_packets++;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
drop:
	rcu_पढ़ो_unlock();
	page_pool_recycle_direct(cpsw->page_pool[ch], page);
	वापस ret;
पूर्ण
