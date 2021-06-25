<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments Ethernet Switch Driver ethtool पूर्णांकf
 *
 * Copyright (C) 2019 Texas Instruments
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/skbuff.h>

#समावेश "cpsw.h"
#समावेश "cpts.h"
#समावेश "cpsw_ale.h"
#समावेश "cpsw_priv.h"
#समावेश "davinci_cpdma.h"

काष्ठा cpsw_hw_stats अणु
	u32	rxgoodframes;
	u32	rxbroadcastframes;
	u32	rxmulticastframes;
	u32	rxछोड़ोframes;
	u32	rxcrcerrors;
	u32	rxaligncodeerrors;
	u32	rxoversizedframes;
	u32	rxjabberframes;
	u32	rxundersizedframes;
	u32	rxfragments;
	u32	__pad_0[2];
	u32	rxoctets;
	u32	txgoodframes;
	u32	txbroadcastframes;
	u32	txmulticastframes;
	u32	txछोड़ोframes;
	u32	txdeferredframes;
	u32	txcollisionframes;
	u32	txsinglecollframes;
	u32	txmultcollframes;
	u32	txexcessivecollisions;
	u32	txlatecollisions;
	u32	txunderrun;
	u32	txcarriersenseerrors;
	u32	txoctets;
	u32	octetframes64;
	u32	octetframes65t127;
	u32	octetframes128t255;
	u32	octetframes256t511;
	u32	octetframes512t1023;
	u32	octetframes1024tup;
	u32	netoctets;
	u32	rxsofoverruns;
	u32	rxmofoverruns;
	u32	rxdmaoverruns;
पूर्ण;

काष्ठा cpsw_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक type;
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

क्रमागत अणु
	CPSW_STATS,
	CPDMA_RX_STATS,
	CPDMA_TX_STATS,
पूर्ण;

#घोषणा CPSW_STAT(m)		CPSW_STATS,				\
				माप_field(काष्ठा cpsw_hw_stats, m), \
				दुरत्व(काष्ठा cpsw_hw_stats, m)
#घोषणा CPDMA_RX_STAT(m)	CPDMA_RX_STATS,				   \
				माप_field(काष्ठा cpdma_chan_stats, m), \
				दुरत्व(काष्ठा cpdma_chan_stats, m)
#घोषणा CPDMA_TX_STAT(m)	CPDMA_TX_STATS,				   \
				माप_field(काष्ठा cpdma_chan_stats, m), \
				दुरत्व(काष्ठा cpdma_chan_stats, m)

अटल स्थिर काष्ठा cpsw_stats cpsw_gstrings_stats[] = अणु
	अणु "Good Rx Frames", CPSW_STAT(rxgoodframes) पूर्ण,
	अणु "Broadcast Rx Frames", CPSW_STAT(rxbroadcastframes) पूर्ण,
	अणु "Multicast Rx Frames", CPSW_STAT(rxmulticastframes) पूर्ण,
	अणु "Pause Rx Frames", CPSW_STAT(rxछोड़ोframes) पूर्ण,
	अणु "Rx CRC Errors", CPSW_STAT(rxcrcerrors) पूर्ण,
	अणु "Rx Align/Code Errors", CPSW_STAT(rxaligncodeerrors) पूर्ण,
	अणु "Oversize Rx Frames", CPSW_STAT(rxoversizedframes) पूर्ण,
	अणु "Rx Jabbers", CPSW_STAT(rxjabberframes) पूर्ण,
	अणु "Undersize (Short) Rx Frames", CPSW_STAT(rxundersizedframes) पूर्ण,
	अणु "Rx Fragments", CPSW_STAT(rxfragments) पूर्ण,
	अणु "Rx Octets", CPSW_STAT(rxoctets) पूर्ण,
	अणु "Good Tx Frames", CPSW_STAT(txgoodframes) पूर्ण,
	अणु "Broadcast Tx Frames", CPSW_STAT(txbroadcastframes) पूर्ण,
	अणु "Multicast Tx Frames", CPSW_STAT(txmulticastframes) पूर्ण,
	अणु "Pause Tx Frames", CPSW_STAT(txछोड़ोframes) पूर्ण,
	अणु "Deferred Tx Frames", CPSW_STAT(txdeferredframes) पूर्ण,
	अणु "Collisions", CPSW_STAT(txcollisionframes) पूर्ण,
	अणु "Single Collision Tx Frames", CPSW_STAT(txsinglecollframes) पूर्ण,
	अणु "Multiple Collision Tx Frames", CPSW_STAT(txmultcollframes) पूर्ण,
	अणु "Excessive Collisions", CPSW_STAT(txexcessivecollisions) पूर्ण,
	अणु "Late Collisions", CPSW_STAT(txlatecollisions) पूर्ण,
	अणु "Tx Underrun", CPSW_STAT(txunderrun) पूर्ण,
	अणु "Carrier Sense Errors", CPSW_STAT(txcarriersenseerrors) पूर्ण,
	अणु "Tx Octets", CPSW_STAT(txoctets) पूर्ण,
	अणु "Rx + Tx 64 Octet Frames", CPSW_STAT(octetframes64) पूर्ण,
	अणु "Rx + Tx 65-127 Octet Frames", CPSW_STAT(octetframes65t127) पूर्ण,
	अणु "Rx + Tx 128-255 Octet Frames", CPSW_STAT(octetframes128t255) पूर्ण,
	अणु "Rx + Tx 256-511 Octet Frames", CPSW_STAT(octetframes256t511) पूर्ण,
	अणु "Rx + Tx 512-1023 Octet Frames", CPSW_STAT(octetframes512t1023) पूर्ण,
	अणु "Rx + Tx 1024-Up Octet Frames", CPSW_STAT(octetframes1024tup) पूर्ण,
	अणु "Net Octets", CPSW_STAT(netoctets) पूर्ण,
	अणु "Rx Start of Frame Overruns", CPSW_STAT(rxsofoverruns) पूर्ण,
	अणु "Rx Middle of Frame Overruns", CPSW_STAT(rxmofoverruns) पूर्ण,
	अणु "Rx DMA Overruns", CPSW_STAT(rxdmaoverruns) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cpsw_stats cpsw_gstrings_ch_stats[] = अणु
	अणु "head_enqueue", CPDMA_RX_STAT(head_enqueue) पूर्ण,
	अणु "tail_enqueue", CPDMA_RX_STAT(tail_enqueue) पूर्ण,
	अणु "pad_enqueue", CPDMA_RX_STAT(pad_enqueue) पूर्ण,
	अणु "misqueued", CPDMA_RX_STAT(misqueued) पूर्ण,
	अणु "desc_alloc_fail", CPDMA_RX_STAT(desc_alloc_fail) पूर्ण,
	अणु "pad_alloc_fail", CPDMA_RX_STAT(pad_alloc_fail) पूर्ण,
	अणु "runt_receive_buf", CPDMA_RX_STAT(runt_receive_buff) पूर्ण,
	अणु "runt_transmit_buf", CPDMA_RX_STAT(runt_transmit_buff) पूर्ण,
	अणु "empty_dequeue", CPDMA_RX_STAT(empty_dequeue) पूर्ण,
	अणु "busy_dequeue", CPDMA_RX_STAT(busy_dequeue) पूर्ण,
	अणु "good_dequeue", CPDMA_RX_STAT(good_dequeue) पूर्ण,
	अणु "requeue", CPDMA_RX_STAT(requeue) पूर्ण,
	अणु "teardown_dequeue", CPDMA_RX_STAT(tearकरोwn_dequeue) पूर्ण,
पूर्ण;

#घोषणा CPSW_STATS_COMMON_LEN	ARRAY_SIZE(cpsw_gstrings_stats)
#घोषणा CPSW_STATS_CH_LEN	ARRAY_SIZE(cpsw_gstrings_ch_stats)

u32 cpsw_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);

	वापस priv->msg_enable;
पूर्ण

व्योम cpsw_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);

	priv->msg_enable = value;
पूर्ण

पूर्णांक cpsw_get_coalesce(काष्ठा net_device *ndev, काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);

	coal->rx_coalesce_usecs = cpsw->coal_पूर्णांकvl;
	वापस 0;
पूर्ण

पूर्णांक cpsw_set_coalesce(काष्ठा net_device *ndev, काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	u32 पूर्णांक_ctrl;
	u32 num_पूर्णांकerrupts = 0;
	u32 prescale = 0;
	u32 addnl_dvdr = 1;
	u32 coal_पूर्णांकvl = 0;
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	coal_पूर्णांकvl = coal->rx_coalesce_usecs;

	पूर्णांक_ctrl =  पढ़ोl(&cpsw->wr_regs->पूर्णांक_control);
	prescale = cpsw->bus_freq_mhz * 4;

	अगर (!coal->rx_coalesce_usecs) अणु
		पूर्णांक_ctrl &= ~(CPSW_INTPRESCALE_MASK | CPSW_INTPACEEN);
		जाओ update_वापस;
	पूर्ण

	अगर (coal_पूर्णांकvl < CPSW_CMINTMIN_INTVL)
		coal_पूर्णांकvl = CPSW_CMINTMIN_INTVL;

	अगर (coal_पूर्णांकvl > CPSW_CMINTMAX_INTVL) अणु
		/* Interrupt pacer works with 4us Pulse, we can
		 * throttle further by dilating the 4us pulse.
		 */
		addnl_dvdr = CPSW_INTPRESCALE_MASK / prescale;

		अगर (addnl_dvdr > 1) अणु
			prescale *= addnl_dvdr;
			अगर (coal_पूर्णांकvl > (CPSW_CMINTMAX_INTVL * addnl_dvdr))
				coal_पूर्णांकvl = (CPSW_CMINTMAX_INTVL
						* addnl_dvdr);
		पूर्ण अन्यथा अणु
			addnl_dvdr = 1;
			coal_पूर्णांकvl = CPSW_CMINTMAX_INTVL;
		पूर्ण
	पूर्ण

	num_पूर्णांकerrupts = (1000 * addnl_dvdr) / coal_पूर्णांकvl;
	ग_लिखोl(num_पूर्णांकerrupts, &cpsw->wr_regs->rx_imax);
	ग_लिखोl(num_पूर्णांकerrupts, &cpsw->wr_regs->tx_imax);

	पूर्णांक_ctrl |= CPSW_INTPACEEN;
	पूर्णांक_ctrl &= (~CPSW_INTPRESCALE_MASK);
	पूर्णांक_ctrl |= (prescale & CPSW_INTPRESCALE_MASK);

update_वापस:
	ग_लिखोl(पूर्णांक_ctrl, &cpsw->wr_regs->पूर्णांक_control);

	cpsw_notice(priv, समयr, "Set coalesce to %d usecs.\n", coal_पूर्णांकvl);
	cpsw->coal_पूर्णांकvl = coal_पूर्णांकvl;

	वापस 0;
पूर्ण

पूर्णांक cpsw_get_sset_count(काष्ठा net_device *ndev, पूर्णांक sset)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस (CPSW_STATS_COMMON_LEN +
		       (cpsw->rx_ch_num + cpsw->tx_ch_num) *
		       CPSW_STATS_CH_LEN);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम cpsw_add_ch_strings(u8 **p, पूर्णांक ch_num, पूर्णांक rx_dir)
अणु
	पूर्णांक ch_stats_len;
	पूर्णांक line;
	पूर्णांक i;

	ch_stats_len = CPSW_STATS_CH_LEN * ch_num;
	क्रम (i = 0; i < ch_stats_len; i++) अणु
		line = i % CPSW_STATS_CH_LEN;
		snम_लिखो(*p, ETH_GSTRING_LEN,
			 "%s DMA chan %ld: %s", rx_dir ? "Rx" : "Tx",
			 (दीर्घ)(i / CPSW_STATS_CH_LEN),
			 cpsw_gstrings_ch_stats[line].stat_string);
		*p += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

व्योम cpsw_get_strings(काष्ठा net_device *ndev, u32 stringset, u8 *data)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < CPSW_STATS_COMMON_LEN; i++) अणु
			स_नकल(p, cpsw_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		cpsw_add_ch_strings(&p, cpsw->rx_ch_num, 1);
		cpsw_add_ch_strings(&p, cpsw->tx_ch_num, 0);
		अवरोध;
	पूर्ण
पूर्ण

व्योम cpsw_get_ethtool_stats(काष्ठा net_device *ndev,
			    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	u8 *p;
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);
	काष्ठा cpdma_chan_stats ch_stats;
	पूर्णांक i, l, ch;

	/* Collect Davinci CPDMA stats क्रम Rx and Tx Channel */
	क्रम (l = 0; l < CPSW_STATS_COMMON_LEN; l++)
		data[l] = पढ़ोl(cpsw->hw_stats +
				cpsw_gstrings_stats[l].stat_offset);

	क्रम (ch = 0; ch < cpsw->rx_ch_num; ch++) अणु
		cpdma_chan_get_stats(cpsw->rxv[ch].ch, &ch_stats);
		क्रम (i = 0; i < CPSW_STATS_CH_LEN; i++, l++) अणु
			p = (u8 *)&ch_stats +
				cpsw_gstrings_ch_stats[i].stat_offset;
			data[l] = *(u32 *)p;
		पूर्ण
	पूर्ण

	क्रम (ch = 0; ch < cpsw->tx_ch_num; ch++) अणु
		cpdma_chan_get_stats(cpsw->txv[ch].ch, &ch_stats);
		क्रम (i = 0; i < CPSW_STATS_CH_LEN; i++, l++) अणु
			p = (u8 *)&ch_stats +
				cpsw_gstrings_ch_stats[i].stat_offset;
			data[l] = *(u32 *)p;
		पूर्ण
	पूर्ण
पूर्ण

व्योम cpsw_get_छोड़ोparam(काष्ठा net_device *ndev,
			 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);

	छोड़ो->स्वतःneg = AUTONEG_DISABLE;
	छोड़ो->rx_छोड़ो = priv->rx_छोड़ो ? true : false;
	छोड़ो->tx_छोड़ो = priv->tx_छोड़ो ? true : false;
पूर्ण

व्योम cpsw_get_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक slave_no = cpsw_slave_index(cpsw, priv);

	wol->supported = 0;
	wol->wolopts = 0;

	अगर (cpsw->slaves[slave_no].phy)
		phy_ethtool_get_wol(cpsw->slaves[slave_no].phy, wol);
पूर्ण

पूर्णांक cpsw_set_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक slave_no = cpsw_slave_index(cpsw, priv);

	अगर (cpsw->slaves[slave_no].phy)
		वापस phy_ethtool_set_wol(cpsw->slaves[slave_no].phy, wol);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक cpsw_get_regs_len(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);

	वापस cpsw_ale_get_num_entries(cpsw->ale) *
	       ALE_ENTRY_WORDS * माप(u32);
पूर्ण

व्योम cpsw_get_regs(काष्ठा net_device *ndev, काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	u32 *reg = p;
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);

	/* update CPSW IP version */
	regs->version = cpsw->version;

	cpsw_ale_dump(cpsw->ale, reg);
पूर्ण

पूर्णांक cpsw_ethtool_op_begin(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		cpsw_err(priv, drv, "ethtool begin failed %d\n", ret);
		pm_runसमय_put_noidle(cpsw->dev);
	पूर्ण

	वापस ret;
पूर्ण

व्योम cpsw_ethtool_op_complete(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	ret = pm_runसमय_put(priv->cpsw->dev);
	अगर (ret < 0)
		cpsw_err(priv, drv, "ethtool complete failed %d\n", ret);
पूर्ण

व्योम cpsw_get_channels(काष्ठा net_device *ndev, काष्ठा ethtool_channels *ch)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);

	ch->max_rx = cpsw->quirk_irq ? 1 : CPSW_MAX_QUEUES;
	ch->max_tx = cpsw->quirk_irq ? 1 : CPSW_MAX_QUEUES;
	ch->max_combined = 0;
	ch->max_other = 0;
	ch->other_count = 0;
	ch->rx_count = cpsw->rx_ch_num;
	ch->tx_count = cpsw->tx_ch_num;
	ch->combined_count = 0;
पूर्ण

पूर्णांक cpsw_get_link_ksettings(काष्ठा net_device *ndev,
			    काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक slave_no = cpsw_slave_index(cpsw, priv);

	अगर (!cpsw->slaves[slave_no].phy)
		वापस -EOPNOTSUPP;

	phy_ethtool_ksettings_get(cpsw->slaves[slave_no].phy, ecmd);
	वापस 0;
पूर्ण

पूर्णांक cpsw_set_link_ksettings(काष्ठा net_device *ndev,
			    स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक slave_no = cpsw_slave_index(cpsw, priv);

	अगर (!cpsw->slaves[slave_no].phy)
		वापस -EOPNOTSUPP;

	वापस phy_ethtool_ksettings_set(cpsw->slaves[slave_no].phy, ecmd);
पूर्ण

पूर्णांक cpsw_get_eee(काष्ठा net_device *ndev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक slave_no = cpsw_slave_index(cpsw, priv);

	अगर (cpsw->slaves[slave_no].phy)
		वापस phy_ethtool_get_eee(cpsw->slaves[slave_no].phy, edata);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक cpsw_set_eee(काष्ठा net_device *ndev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक slave_no = cpsw_slave_index(cpsw, priv);

	अगर (cpsw->slaves[slave_no].phy)
		वापस phy_ethtool_set_eee(cpsw->slaves[slave_no].phy, edata);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक cpsw_nway_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक slave_no = cpsw_slave_index(cpsw, priv);

	अगर (cpsw->slaves[slave_no].phy)
		वापस genphy_restart_aneg(cpsw->slaves[slave_no].phy);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम cpsw_suspend_data_pass(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);
	पूर्णांक i;

	/* Disable NAPI scheduling */
	cpsw_पूर्णांकr_disable(cpsw);

	/* Stop all transmit queues क्रम every network device.
	 */
	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		ndev = cpsw->slaves[i].ndev;
		अगर (!(ndev && netअगर_running(ndev)))
			जारी;

		netअगर_tx_stop_all_queues(ndev);

		/* Barrier, so that stop_queue visible to other cpus */
		smp_mb__after_atomic();
	पूर्ण

	/* Handle rest of tx packets and stop cpdma channels */
	cpdma_ctlr_stop(cpsw->dma);
पूर्ण

अटल पूर्णांक cpsw_resume_data_pass(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक i, ret;

	/* After this receive is started */
	अगर (cpsw->usage_count) अणु
		ret = cpsw_fill_rx_channels(priv);
		अगर (ret)
			वापस ret;

		cpdma_ctlr_start(cpsw->dma);
		cpsw_पूर्णांकr_enable(cpsw);
	पूर्ण

	/* Resume transmit क्रम every affected पूर्णांकerface */
	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		ndev = cpsw->slaves[i].ndev;
		अगर (ndev && netअगर_running(ndev))
			netअगर_tx_start_all_queues(ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_check_ch_settings(काष्ठा cpsw_common *cpsw,
				  काष्ठा ethtool_channels *ch)
अणु
	अगर (cpsw->quirk_irq) अणु
		dev_err(cpsw->dev, "Maximum one tx/rx queue is allowed");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (ch->combined_count)
		वापस -EINVAL;

	/* verअगरy we have at least one channel in each direction */
	अगर (!ch->rx_count || !ch->tx_count)
		वापस -EINVAL;

	अगर (ch->rx_count > cpsw->data.channels ||
	    ch->tx_count > cpsw->data.channels)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_update_channels_res(काष्ठा cpsw_priv *priv, पूर्णांक ch_num, पूर्णांक rx,
				    cpdma_handler_fn rx_handler)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	व्योम (*handler)(व्योम *, पूर्णांक, पूर्णांक);
	काष्ठा netdev_queue *queue;
	काष्ठा cpsw_vector *vec;
	पूर्णांक ret, *ch, vch;

	अगर (rx) अणु
		ch = &cpsw->rx_ch_num;
		vec = cpsw->rxv;
		handler = rx_handler;
	पूर्ण अन्यथा अणु
		ch = &cpsw->tx_ch_num;
		vec = cpsw->txv;
		handler = cpsw_tx_handler;
	पूर्ण

	जबतक (*ch < ch_num) अणु
		vch = rx ? *ch : 7 - *ch;
		vec[*ch].ch = cpdma_chan_create(cpsw->dma, vch, handler, rx);
		queue = netdev_get_tx_queue(priv->ndev, *ch);
		queue->tx_maxrate = 0;

		अगर (IS_ERR(vec[*ch].ch))
			वापस PTR_ERR(vec[*ch].ch);

		अगर (!vec[*ch].ch)
			वापस -EINVAL;

		cpsw_info(priv, अगरup, "created new %d %s channel\n", *ch,
			  (rx ? "rx" : "tx"));
		(*ch)++;
	पूर्ण

	जबतक (*ch > ch_num) अणु
		(*ch)--;

		ret = cpdma_chan_destroy(vec[*ch].ch);
		अगर (ret)
			वापस ret;

		cpsw_info(priv, अगरup, "destroyed %d %s channel\n", *ch,
			  (rx ? "rx" : "tx"));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cpsw_fail(काष्ठा cpsw_common *cpsw)
अणु
	काष्ठा net_device *ndev;
	पूर्णांक i;

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		ndev = cpsw->slaves[i].ndev;
		अगर (ndev)
			dev_बंद(ndev);
	पूर्ण
पूर्ण

पूर्णांक cpsw_set_channels_common(काष्ठा net_device *ndev,
			     काष्ठा ethtool_channels *chs,
			     cpdma_handler_fn rx_handler)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा net_device *sl_ndev;
	पूर्णांक i, new_pools, ret;

	ret = cpsw_check_ch_settings(cpsw, chs);
	अगर (ret < 0)
		वापस ret;

	cpsw_suspend_data_pass(ndev);

	new_pools = (chs->rx_count != cpsw->rx_ch_num) && cpsw->usage_count;

	ret = cpsw_update_channels_res(priv, chs->rx_count, 1, rx_handler);
	अगर (ret)
		जाओ err;

	ret = cpsw_update_channels_res(priv, chs->tx_count, 0, rx_handler);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		sl_ndev = cpsw->slaves[i].ndev;
		अगर (!(sl_ndev && netअगर_running(sl_ndev)))
			जारी;

		/* Inक्रमm stack about new count of queues */
		ret = netअगर_set_real_num_tx_queues(sl_ndev, cpsw->tx_ch_num);
		अगर (ret) अणु
			dev_err(priv->dev, "cannot set real number of tx queues\n");
			जाओ err;
		पूर्ण

		ret = netअगर_set_real_num_rx_queues(sl_ndev, cpsw->rx_ch_num);
		अगर (ret) अणु
			dev_err(priv->dev, "cannot set real number of rx queues\n");
			जाओ err;
		पूर्ण
	पूर्ण

	cpsw_split_res(cpsw);

	अगर (new_pools) अणु
		cpsw_destroy_xdp_rxqs(cpsw);
		ret = cpsw_create_xdp_rxqs(cpsw);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = cpsw_resume_data_pass(ndev);
	अगर (!ret)
		वापस 0;
err:
	dev_err(priv->dev, "cannot update channels number, closing device\n");
	cpsw_fail(cpsw);
	वापस ret;
पूर्ण

व्योम cpsw_get_ringparam(काष्ठा net_device *ndev,
			काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	/* not supported */
	ering->tx_max_pending = cpsw->descs_pool_size - CPSW_MAX_QUEUES;
	ering->tx_pending = cpdma_get_num_tx_descs(cpsw->dma);
	ering->rx_max_pending = cpsw->descs_pool_size - CPSW_MAX_QUEUES;
	ering->rx_pending = cpdma_get_num_rx_descs(cpsw->dma);
पूर्ण

पूर्णांक cpsw_set_ringparam(काष्ठा net_device *ndev,
		       काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);
	पूर्णांक descs_num, ret;

	/* ignore ering->tx_pending - only rx_pending adjusपंचांगent is supported */

	अगर (ering->rx_mini_pending || ering->rx_jumbo_pending ||
	    ering->rx_pending < CPSW_MAX_QUEUES ||
	    ering->rx_pending > (cpsw->descs_pool_size - CPSW_MAX_QUEUES))
		वापस -EINVAL;

	descs_num = cpdma_get_num_rx_descs(cpsw->dma);
	अगर (ering->rx_pending == descs_num)
		वापस 0;

	cpsw_suspend_data_pass(ndev);

	ret = cpdma_set_num_rx_descs(cpsw->dma, ering->rx_pending);
	अगर (ret) अणु
		अगर (cpsw_resume_data_pass(ndev))
			जाओ err;

		वापस ret;
	पूर्ण

	अगर (cpsw->usage_count) अणु
		cpsw_destroy_xdp_rxqs(cpsw);
		ret = cpsw_create_xdp_rxqs(cpsw);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = cpsw_resume_data_pass(ndev);
	अगर (!ret)
		वापस 0;
err:
	cpdma_set_num_rx_descs(cpsw->dma, descs_num);
	dev_err(cpsw->dev, "cannot set ring params, closing device\n");
	cpsw_fail(cpsw);
	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_TI_CPTS)
पूर्णांक cpsw_get_ts_info(काष्ठा net_device *ndev, काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);

	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_TX_SOFTWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->phc_index = cpsw->cpts->phc_index;
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON);
	info->rx_filters =
		(1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V2_EVENT);
	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक cpsw_get_ts_info(काष्ठा net_device *ndev, काष्ठा ethtool_ts_info *info)
अणु
	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_SOFTWARE |
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE;
	info->phc_index = -1;
	info->tx_types = 0;
	info->rx_filters = 0;
	वापस 0;
पूर्ण
#पूर्ण_अगर
