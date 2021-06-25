<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: cxgb2.c                                                             *
 * $Revision: 1.25 $                                                         *
 * $Date: 2005/06/22 00:43:25 $                                              *
 * Description:                                                              *
 *  Chelsio 10Gb Ethernet Driver.                                            *
 *                                                                           *
 * This program is मुक्त software; you can redistribute it and/or modअगरy      *
 * it under the terms of the GNU General Public License, version 2, as       *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 * You should have received a copy of the GNU General Public License aदीर्घ   *
 * with this program; अगर not, see <http://www.gnu.org/licenses/>.            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED    *
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF      *
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.                     *
 *                                                                           *
 * http://www.chelsio.com                                                    *
 *                                                                           *
 * Copyright (c) 2003 - 2005 Chelsio Communications, Inc.                    *
 * All rights reserved.                                                      *
 *                                                                           *
 * Maपूर्णांकainers: मुख्यtainers@chelsio.com                                      *
 *                                                                           *
 * Authors: Dimitrios Michailidis   <dm@chelsio.com>                         *
 *          Tina Yang               <tainay@chelsio.com>                     *
 *          Felix Marti             <felix@chelsio.com>                      *
 *          Scott Barकरोne           <sbarकरोne@chelsio.com>                   *
 *          Kurt Ottaway            <kottaway@chelsio.com>                   *
 *          Frank DiMambro          <frank@chelsio.com>                      *
 *                                                                           *
 * History:                                                                  *
 *                                                                           *
 ****************************************************************************/

#समावेश "common.h"
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/mii.h>
#समावेश <linux/sockios.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/uaccess.h>

#समावेश "cpl5_cmd.h"
#समावेश "regs.h"
#समावेश "gmac.h"
#समावेश "cphy.h"
#समावेश "sge.h"
#समावेश "tp.h"
#समावेश "espi.h"
#समावेश "elmer0.h"

#समावेश <linux/workqueue.h>

अटल अंतरभूत व्योम schedule_mac_stats_update(काष्ठा adapter *ap, पूर्णांक secs)
अणु
	schedule_delayed_work(&ap->stats_update_task, secs * HZ);
पूर्ण

अटल अंतरभूत व्योम cancel_mac_stats_update(काष्ठा adapter *ap)
अणु
	cancel_delayed_work(&ap->stats_update_task);
पूर्ण

#घोषणा MAX_CMDQ_ENTRIES	16384
#घोषणा MAX_CMDQ1_ENTRIES	1024
#घोषणा MAX_RX_BUFFERS		16384
#घोषणा MAX_RX_JUMBO_BUFFERS	16384
#घोषणा MAX_TX_BUFFERS_HIGH	16384U
#घोषणा MAX_TX_BUFFERS_LOW	1536U
#घोषणा MAX_TX_BUFFERS		1460U
#घोषणा MIN_FL_ENTRIES		32

#घोषणा DFLT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK | \
			 NETIF_MSG_TIMER | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP |\
			 NETIF_MSG_RX_ERR | NETIF_MSG_TX_ERR)

/*
 * The EEPROM is actually bigger but only the first few bytes are used so we
 * only report those.
 */
#घोषणा EEPROM_SIZE 32

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR("Chelsio Communications");
MODULE_LICENSE("GPL");

अटल पूर्णांक dflt_msg_enable = DFLT_MSG_ENABLE;

module_param(dflt_msg_enable, पूर्णांक, 0);
MODULE_PARM_DESC(dflt_msg_enable, "Chelsio T1 default message enable bitmap");

#घोषणा HCLOCK 0x0
#घोषणा LCLOCK 0x1

/* T1 cards घातersave mode */
अटल पूर्णांक t1_घड़ी(काष्ठा adapter *adapter, पूर्णांक mode);
अटल पूर्णांक t1घातersave = 1;	/* HW शेष is घातersave mode. */

module_param(t1घातersave, पूर्णांक, 0);
MODULE_PARM_DESC(t1घातersave, "Enable/Disable T1 powersaving mode");

अटल पूर्णांक disable_msi = 0;
module_param(disable_msi, पूर्णांक, 0);
MODULE_PARM_DESC(disable_msi, "Disable Message Signaled Interrupt (MSI)");

/*
 * Setup MAC to receive the types of packets we want.
 */
अटल व्योम t1_set_rxmode(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा cmac *mac = adapter->port[dev->अगर_port].mac;
	काष्ठा t1_rx_mode rm;

	rm.dev = dev;
	mac->ops->set_rx_mode(mac, &rm);
पूर्ण

अटल व्योम link_report(काष्ठा port_info *p)
अणु
	अगर (!netअगर_carrier_ok(p->dev))
		netdev_info(p->dev, "link down\n");
	अन्यथा अणु
		स्थिर अक्षर *s = "10Mbps";

		चयन (p->link_config.speed) अणु
			हाल SPEED_10000: s = "10Gbps"; अवरोध;
			हाल SPEED_1000:  s = "1000Mbps"; अवरोध;
			हाल SPEED_100:   s = "100Mbps"; अवरोध;
		पूर्ण

		netdev_info(p->dev, "link up, %s, %s-duplex\n",
			    s, p->link_config.duplex == DUPLEX_FULL
			    ? "full" : "half");
	पूर्ण
पूर्ण

व्योम t1_link_negotiated(काष्ठा adapter *adapter, पूर्णांक port_id, पूर्णांक link_stat,
			पूर्णांक speed, पूर्णांक duplex, पूर्णांक छोड़ो)
अणु
	काष्ठा port_info *p = &adapter->port[port_id];

	अगर (link_stat != netअगर_carrier_ok(p->dev)) अणु
		अगर (link_stat)
			netअगर_carrier_on(p->dev);
		अन्यथा
			netअगर_carrier_off(p->dev);
		link_report(p);

		/* multi-ports: inक्रमm toe */
		अगर ((speed > 0) && (adapter->params.nports > 1)) अणु
			अचिन्हित पूर्णांक sched_speed = 10;
			चयन (speed) अणु
			हाल SPEED_1000:
				sched_speed = 1000;
				अवरोध;
			हाल SPEED_100:
				sched_speed = 100;
				अवरोध;
			हाल SPEED_10:
				sched_speed = 10;
				अवरोध;
			पूर्ण
			t1_sched_update_parms(adapter->sge, port_id, 0, sched_speed);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम link_start(काष्ठा port_info *p)
अणु
	काष्ठा cmac *mac = p->mac;

	mac->ops->reset(mac);
	अगर (mac->ops->macaddress_set)
		mac->ops->macaddress_set(mac, p->dev->dev_addr);
	t1_set_rxmode(p->dev);
	t1_link_start(p->phy, mac, &p->link_config);
	mac->ops->enable(mac, MAC_सूचीECTION_RX | MAC_सूचीECTION_TX);
पूर्ण

अटल व्योम enable_hw_csum(काष्ठा adapter *adapter)
अणु
	अगर (adapter->port[0].dev->hw_features & NETIF_F_TSO)
		t1_tp_set_ip_checksum_offload(adapter->tp, 1);	/* क्रम TSO only */
	t1_tp_set_tcp_checksum_offload(adapter->tp, 1);
पूर्ण

/*
 * Things to करो upon first use of a card.
 * This must run with the rtnl lock held.
 */
अटल पूर्णांक cxgb_up(काष्ठा adapter *adapter)
अणु
	पूर्णांक err = 0;

	अगर (!(adapter->flags & FULL_INIT_DONE)) अणु
		err = t1_init_hw_modules(adapter);
		अगर (err)
			जाओ out_err;

		enable_hw_csum(adapter);
		adapter->flags |= FULL_INIT_DONE;
	पूर्ण

	t1_पूर्णांकerrupts_clear(adapter);

	adapter->params.has_msi = !disable_msi && !pci_enable_msi(adapter->pdev);
	err = request_thपढ़ोed_irq(adapter->pdev->irq, t1_पूर्णांकerrupt,
				   t1_पूर्णांकerrupt_thपढ़ो,
				   adapter->params.has_msi ? 0 : IRQF_SHARED,
				   adapter->name, adapter);
	अगर (err) अणु
		अगर (adapter->params.has_msi)
			pci_disable_msi(adapter->pdev);

		जाओ out_err;
	पूर्ण

	t1_sge_start(adapter->sge);
	t1_पूर्णांकerrupts_enable(adapter);
out_err:
	वापस err;
पूर्ण

/*
 * Release resources when all the ports have been stopped.
 */
अटल व्योम cxgb_करोwn(काष्ठा adapter *adapter)
अणु
	t1_sge_stop(adapter->sge);
	t1_पूर्णांकerrupts_disable(adapter);
	मुक्त_irq(adapter->pdev->irq, adapter);
	अगर (adapter->params.has_msi)
		pci_disable_msi(adapter->pdev);
पूर्ण

अटल पूर्णांक cxgb_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक err;
	काष्ठा adapter *adapter = dev->ml_priv;
	पूर्णांक other_ports = adapter->खोलो_device_map & PORT_MASK;

	napi_enable(&adapter->napi);
	अगर (!adapter->खोलो_device_map && (err = cxgb_up(adapter)) < 0) अणु
		napi_disable(&adapter->napi);
		वापस err;
	पूर्ण

	__set_bit(dev->अगर_port, &adapter->खोलो_device_map);
	link_start(&adapter->port[dev->अगर_port]);
	netअगर_start_queue(dev);
	अगर (!other_ports && adapter->params.stats_update_period)
		schedule_mac_stats_update(adapter,
					  adapter->params.stats_update_period);

	t1_vlan_mode(adapter, dev->features);
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा port_info *p = &adapter->port[dev->अगर_port];
	काष्ठा cmac *mac = p->mac;

	netअगर_stop_queue(dev);
	napi_disable(&adapter->napi);
	mac->ops->disable(mac, MAC_सूचीECTION_TX | MAC_सूचीECTION_RX);
	netअगर_carrier_off(dev);

	clear_bit(dev->अगर_port, &adapter->खोलो_device_map);
	अगर (adapter->params.stats_update_period &&
	    !(adapter->खोलो_device_map & PORT_MASK)) अणु
		/* Stop statistics accumulation. */
		smp_mb__after_atomic();
		spin_lock(&adapter->work_lock);   /* sync with update task */
		spin_unlock(&adapter->work_lock);
		cancel_mac_stats_update(adapter);
	पूर्ण

	अगर (!adapter->खोलो_device_map)
		cxgb_करोwn(adapter);
	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *t1_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा port_info *p = &adapter->port[dev->अगर_port];
	काष्ठा net_device_stats *ns = &dev->stats;
	स्थिर काष्ठा cmac_statistics *pstats;

	/* Do a full update of the MAC stats */
	pstats = p->mac->ops->statistics_update(p->mac,
						MAC_STATS_UPDATE_FULL);

	ns->tx_packets = pstats->TxUnicastFramesOK +
		pstats->TxMulticastFramesOK + pstats->TxBroadcastFramesOK;

	ns->rx_packets = pstats->RxUnicastFramesOK +
		pstats->RxMulticastFramesOK + pstats->RxBroadcastFramesOK;

	ns->tx_bytes = pstats->TxOctetsOK;
	ns->rx_bytes = pstats->RxOctetsOK;

	ns->tx_errors = pstats->TxLateCollisions + pstats->TxLengthErrors +
		pstats->TxUnderrun + pstats->TxFramesAbortedDueToXSCollisions;
	ns->rx_errors = pstats->RxDataErrors + pstats->RxJabberErrors +
		pstats->RxFCSErrors + pstats->RxAlignErrors +
		pstats->RxSequenceErrors + pstats->RxFrameTooLongErrors +
		pstats->RxSymbolErrors + pstats->RxRuntErrors;

	ns->multicast  = pstats->RxMulticastFramesOK;
	ns->collisions = pstats->TxTotalCollisions;

	/* detailed rx_errors */
	ns->rx_length_errors = pstats->RxFrameTooLongErrors +
		pstats->RxJabberErrors;
	ns->rx_over_errors   = 0;
	ns->rx_crc_errors    = pstats->RxFCSErrors;
	ns->rx_frame_errors  = pstats->RxAlignErrors;
	ns->rx_fअगरo_errors   = 0;
	ns->rx_missed_errors = 0;

	/* detailed tx_errors */
	ns->tx_पातed_errors   = pstats->TxFramesAbortedDueToXSCollisions;
	ns->tx_carrier_errors   = 0;
	ns->tx_fअगरo_errors      = pstats->TxUnderrun;
	ns->tx_heartbeat_errors = 0;
	ns->tx_winकरोw_errors    = pstats->TxLateCollisions;
	वापस ns;
पूर्ण

अटल u32 get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;

	वापस adapter->msg_enable;
पूर्ण

अटल व्योम set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;

	adapter->msg_enable = val;
पूर्ण

अटल स्थिर अक्षर stats_strings[][ETH_GSTRING_LEN] = अणु
	"TxOctetsOK",
	"TxOctetsBad",
	"TxUnicastFramesOK",
	"TxMulticastFramesOK",
	"TxBroadcastFramesOK",
	"TxPauseFrames",
	"TxFramesWithDeferredXmissions",
	"TxLateCollisions",
	"TxTotalCollisions",
	"TxFramesAbortedDueToXSCollisions",
	"TxUnderrun",
	"TxLengthErrors",
	"TxInternalMACXmitError",
	"TxFramesWithExcessiveDeferral",
	"TxFCSErrors",
	"TxJumboFramesOk",
	"TxJumboOctetsOk",
	
	"RxOctetsOK",
	"RxOctetsBad",
	"RxUnicastFramesOK",
	"RxMulticastFramesOK",
	"RxBroadcastFramesOK",
	"RxPauseFrames",
	"RxFCSErrors",
	"RxAlignErrors",
	"RxSymbolErrors",
	"RxDataErrors",
	"RxSequenceErrors",
	"RxRuntErrors",
	"RxJabberErrors",
	"RxInternalMACRcvError",
	"RxInRangeLengthErrors",
	"RxOutOfRangeLengthField",
	"RxFrameTooLongErrors",
	"RxJumboFramesOk",
	"RxJumboOctetsOk",

	/* Port stats */
	"RxCsumGood",
	"TxCsumOffload",
	"TxTso",
	"RxVlan",
	"TxVlan",
	"TxNeedHeadroom", 
	
	/* Interrupt stats */
	"rx drops",
	"pure_rsps",
	"unhandled irqs",
	"respQ_empty",
	"respQ_overflow",
	"freelistQ_empty",
	"pkt_too_big",
	"pkt_mismatch",
	"cmdQ_full0",
	"cmdQ_full1",

	"espi_DIP2ParityErr",
	"espi_DIP4Err",
	"espi_RxDrops",
	"espi_TxDrops",
	"espi_RxOvfl",
	"espi_ParityErr"
पूर्ण;

#घोषणा T2_REGMAP_SIZE (3 * 1024)

अटल पूर्णांक get_regs_len(काष्ठा net_device *dev)
अणु
	वापस T2_REGMAP_SIZE;
पूर्ण

अटल व्योम get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(adapter->pdev),
		माप(info->bus_info));
पूर्ण

अटल पूर्णांक get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(stats_strings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	अगर (stringset == ETH_SS_STATS)
		स_नकल(data, stats_strings, माप(stats_strings));
पूर्ण

अटल व्योम get_stats(काष्ठा net_device *dev, काष्ठा ethtool_stats *stats,
		      u64 *data)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा cmac *mac = adapter->port[dev->अगर_port].mac;
	स्थिर काष्ठा cmac_statistics *s;
	स्थिर काष्ठा sge_पूर्णांकr_counts *t;
	काष्ठा sge_port_stats ss;

	s = mac->ops->statistics_update(mac, MAC_STATS_UPDATE_FULL);
	t = t1_sge_get_पूर्णांकr_counts(adapter->sge);
	t1_sge_get_port_stats(adapter->sge, dev->अगर_port, &ss);

	*data++ = s->TxOctetsOK;
	*data++ = s->TxOctetsBad;
	*data++ = s->TxUnicastFramesOK;
	*data++ = s->TxMulticastFramesOK;
	*data++ = s->TxBroadcastFramesOK;
	*data++ = s->TxPauseFrames;
	*data++ = s->TxFramesWithDeferredXmissions;
	*data++ = s->TxLateCollisions;
	*data++ = s->TxTotalCollisions;
	*data++ = s->TxFramesAbortedDueToXSCollisions;
	*data++ = s->TxUnderrun;
	*data++ = s->TxLengthErrors;
	*data++ = s->TxInternalMACXmitError;
	*data++ = s->TxFramesWithExcessiveDeferral;
	*data++ = s->TxFCSErrors;
	*data++ = s->TxJumboFramesOK;
	*data++ = s->TxJumboOctetsOK;

	*data++ = s->RxOctetsOK;
	*data++ = s->RxOctetsBad;
	*data++ = s->RxUnicastFramesOK;
	*data++ = s->RxMulticastFramesOK;
	*data++ = s->RxBroadcastFramesOK;
	*data++ = s->RxPauseFrames;
	*data++ = s->RxFCSErrors;
	*data++ = s->RxAlignErrors;
	*data++ = s->RxSymbolErrors;
	*data++ = s->RxDataErrors;
	*data++ = s->RxSequenceErrors;
	*data++ = s->RxRuntErrors;
	*data++ = s->RxJabberErrors;
	*data++ = s->RxInternalMACRcvError;
	*data++ = s->RxInRangeLengthErrors;
	*data++ = s->RxOutOfRangeLengthField;
	*data++ = s->RxFrameTooLongErrors;
	*data++ = s->RxJumboFramesOK;
	*data++ = s->RxJumboOctetsOK;

	*data++ = ss.rx_cso_good;
	*data++ = ss.tx_cso;
	*data++ = ss.tx_tso;
	*data++ = ss.vlan_xtract;
	*data++ = ss.vlan_insert;
	*data++ = ss.tx_need_hdrroom;
	
	*data++ = t->rx_drops;
	*data++ = t->pure_rsps;
	*data++ = t->unhandled_irqs;
	*data++ = t->respQ_empty;
	*data++ = t->respQ_overflow;
	*data++ = t->मुक्तlistQ_empty;
	*data++ = t->pkt_too_big;
	*data++ = t->pkt_mismatch;
	*data++ = t->cmdQ_full[0];
	*data++ = t->cmdQ_full[1];

	अगर (adapter->espi) अणु
		स्थिर काष्ठा espi_पूर्णांकr_counts *e;

		e = t1_espi_get_पूर्णांकr_counts(adapter->espi);
		*data++ = e->DIP2_parity_err;
		*data++ = e->DIP4_err;
		*data++ = e->rx_drops;
		*data++ = e->tx_drops;
		*data++ = e->rx_ovflw;
		*data++ = e->parity_err;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम reg_block_dump(काष्ठा adapter *ap, व्योम *buf,
				  अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	u32 *p = buf + start;

	क्रम ( ; start <= end; start += माप(u32))
		*p++ = पढ़ोl(ap->regs + start);
पूर्ण

अटल व्योम get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
		     व्योम *buf)
अणु
	काष्ठा adapter *ap = dev->ml_priv;

	/*
	 * Version scheme: bits 0..9: chip version, bits 10..15: chip revision
	 */
	regs->version = 2;

	स_रखो(buf, 0, T2_REGMAP_SIZE);
	reg_block_dump(ap, buf, 0, A_SG_RESPACCUTIMER);
	reg_block_dump(ap, buf, A_MC3_CFG, A_MC4_INT_CAUSE);
	reg_block_dump(ap, buf, A_TPI_ADDR, A_TPI_PAR);
	reg_block_dump(ap, buf, A_TP_IN_CONFIG, A_TP_TX_DROP_COUNT);
	reg_block_dump(ap, buf, A_RAT_ROUTE_CONTROL, A_RAT_INTR_CAUSE);
	reg_block_dump(ap, buf, A_CSPI_RX_AE_WM, A_CSPI_INTR_ENABLE);
	reg_block_dump(ap, buf, A_ESPI_SCH_TOKEN0, A_ESPI_GOSTAT);
	reg_block_dump(ap, buf, A_ULP_ULIMIT, A_ULP_PIO_CTRL);
	reg_block_dump(ap, buf, A_PL_ENABLE, A_PL_CAUSE);
	reg_block_dump(ap, buf, A_MC5_CONFIG, A_MC5_MASK_WRITE_CMD);
पूर्ण

अटल पूर्णांक get_link_ksettings(काष्ठा net_device *dev,
			      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा port_info *p = &adapter->port[dev->अगर_port];
	u32 supported, advertising;

	supported = p->link_config.supported;
	advertising = p->link_config.advertising;

	अगर (netअगर_carrier_ok(dev)) अणु
		cmd->base.speed = p->link_config.speed;
		cmd->base.duplex = p->link_config.duplex;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	cmd->base.port = (supported & SUPPORTED_TP) ? PORT_TP : PORT_FIBRE;
	cmd->base.phy_address = p->phy->mdio.prtad;
	cmd->base.स्वतःneg = p->link_config.स्वतःneg;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक speed_duplex_to_caps(पूर्णांक speed, पूर्णांक duplex)
अणु
	पूर्णांक cap = 0;

	चयन (speed) अणु
	हाल SPEED_10:
		अगर (duplex == DUPLEX_FULL)
			cap = SUPPORTED_10baseT_Full;
		अन्यथा
			cap = SUPPORTED_10baseT_Half;
		अवरोध;
	हाल SPEED_100:
		अगर (duplex == DUPLEX_FULL)
			cap = SUPPORTED_100baseT_Full;
		अन्यथा
			cap = SUPPORTED_100baseT_Half;
		अवरोध;
	हाल SPEED_1000:
		अगर (duplex == DUPLEX_FULL)
			cap = SUPPORTED_1000baseT_Full;
		अन्यथा
			cap = SUPPORTED_1000baseT_Half;
		अवरोध;
	हाल SPEED_10000:
		अगर (duplex == DUPLEX_FULL)
			cap = SUPPORTED_10000baseT_Full;
	पूर्ण
	वापस cap;
पूर्ण

#घोषणा ADVERTISED_MASK (ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full | \
		      ADVERTISED_100baseT_Half | ADVERTISED_100baseT_Full | \
		      ADVERTISED_1000baseT_Half | ADVERTISED_1000baseT_Full | \
		      ADVERTISED_10000baseT_Full)

अटल पूर्णांक set_link_ksettings(काष्ठा net_device *dev,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा port_info *p = &adapter->port[dev->अगर_port];
	काष्ठा link_config *lc = &p->link_config;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (!(lc->supported & SUPPORTED_Autoneg))
		वापस -EOPNOTSUPP;             /* can't change speed/duplex */

	अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE) अणु
		u32 speed = cmd->base.speed;
		पूर्णांक cap = speed_duplex_to_caps(speed, cmd->base.duplex);

		अगर (!(lc->supported & cap) || (speed == SPEED_1000))
			वापस -EINVAL;
		lc->requested_speed = speed;
		lc->requested_duplex = cmd->base.duplex;
		lc->advertising = 0;
	पूर्ण अन्यथा अणु
		advertising &= ADVERTISED_MASK;
		अगर (advertising & (advertising - 1))
			advertising = lc->supported;
		advertising &= lc->supported;
		अगर (!advertising)
			वापस -EINVAL;
		lc->requested_speed = SPEED_INVALID;
		lc->requested_duplex = DUPLEX_INVALID;
		lc->advertising = advertising | ADVERTISED_Autoneg;
	पूर्ण
	lc->स्वतःneg = cmd->base.स्वतःneg;
	अगर (netअगर_running(dev))
		t1_link_start(p->phy, p->mac, lc);
	वापस 0;
पूर्ण

अटल व्योम get_छोड़ोparam(काष्ठा net_device *dev,
			   काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा port_info *p = &adapter->port[dev->अगर_port];

	eछोड़ो->स्वतःneg = (p->link_config.requested_fc & PAUSE_AUTONEG) != 0;
	eछोड़ो->rx_छोड़ो = (p->link_config.fc & PAUSE_RX) != 0;
	eछोड़ो->tx_छोड़ो = (p->link_config.fc & PAUSE_TX) != 0;
पूर्ण

अटल पूर्णांक set_छोड़ोparam(काष्ठा net_device *dev,
			  काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा port_info *p = &adapter->port[dev->अगर_port];
	काष्ठा link_config *lc = &p->link_config;

	अगर (eछोड़ो->स्वतःneg == AUTONEG_DISABLE)
		lc->requested_fc = 0;
	अन्यथा अगर (lc->supported & SUPPORTED_Autoneg)
		lc->requested_fc = PAUSE_AUTONEG;
	अन्यथा
		वापस -EINVAL;

	अगर (eछोड़ो->rx_छोड़ो)
		lc->requested_fc |= PAUSE_RX;
	अगर (eछोड़ो->tx_छोड़ो)
		lc->requested_fc |= PAUSE_TX;
	अगर (lc->स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (netअगर_running(dev))
			t1_link_start(p->phy, p->mac, lc);
	पूर्ण अन्यथा अणु
		lc->fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);
		अगर (netअगर_running(dev))
			p->mac->ops->set_speed_duplex_fc(p->mac, -1, -1,
							 lc->fc);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम get_sge_param(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *e)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	पूर्णांक jumbo_fl = t1_is_T1B(adapter) ? 1 : 0;

	e->rx_max_pending = MAX_RX_BUFFERS;
	e->rx_jumbo_max_pending = MAX_RX_JUMBO_BUFFERS;
	e->tx_max_pending = MAX_CMDQ_ENTRIES;

	e->rx_pending = adapter->params.sge.मुक्तlQ_size[!jumbo_fl];
	e->rx_jumbo_pending = adapter->params.sge.मुक्तlQ_size[jumbo_fl];
	e->tx_pending = adapter->params.sge.cmdQ_size[0];
पूर्ण

अटल पूर्णांक set_sge_param(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *e)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	पूर्णांक jumbo_fl = t1_is_T1B(adapter) ? 1 : 0;

	अगर (e->rx_pending > MAX_RX_BUFFERS || e->rx_mini_pending ||
	    e->rx_jumbo_pending > MAX_RX_JUMBO_BUFFERS ||
	    e->tx_pending > MAX_CMDQ_ENTRIES ||
	    e->rx_pending < MIN_FL_ENTRIES ||
	    e->rx_jumbo_pending < MIN_FL_ENTRIES ||
	    e->tx_pending < (adapter->params.nports + 1) * (MAX_SKB_FRAGS + 1))
		वापस -EINVAL;

	अगर (adapter->flags & FULL_INIT_DONE)
		वापस -EBUSY;

	adapter->params.sge.मुक्तlQ_size[!jumbo_fl] = e->rx_pending;
	adapter->params.sge.मुक्तlQ_size[jumbo_fl] = e->rx_jumbo_pending;
	adapter->params.sge.cmdQ_size[0] = e->tx_pending;
	adapter->params.sge.cmdQ_size[1] = e->tx_pending > MAX_CMDQ1_ENTRIES ?
		MAX_CMDQ1_ENTRIES : e->tx_pending;
	वापस 0;
पूर्ण

अटल पूर्णांक set_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;

	adapter->params.sge.rx_coalesce_usecs = c->rx_coalesce_usecs;
	adapter->params.sge.coalesce_enable = c->use_adaptive_rx_coalesce;
	adapter->params.sge.sample_पूर्णांकerval_usecs = c->rate_sample_पूर्णांकerval;
	t1_sge_set_coalesce_params(adapter->sge, &adapter->params.sge);
	वापस 0;
पूर्ण

अटल पूर्णांक get_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;

	c->rx_coalesce_usecs = adapter->params.sge.rx_coalesce_usecs;
	c->rate_sample_पूर्णांकerval = adapter->params.sge.sample_पूर्णांकerval_usecs;
	c->use_adaptive_rx_coalesce = adapter->params.sge.coalesce_enable;
	वापस 0;
पूर्ण

अटल पूर्णांक get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;

	वापस t1_is_asic(adapter) ? EEPROM_SIZE : 0;
पूर्ण

#घोषणा EEPROM_MAGIC(ap) \
	(PCI_VENDOR_ID_CHELSIO | ((ap)->params.chip_version << 16))

अटल पूर्णांक get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *e,
		      u8 *data)
अणु
	पूर्णांक i;
	u8 buf[EEPROM_SIZE] __attribute__((aligned(4)));
	काष्ठा adapter *adapter = dev->ml_priv;

	e->magic = EEPROM_MAGIC(adapter);
	क्रम (i = e->offset & ~3; i < e->offset + e->len; i += माप(u32))
		t1_seeprom_पढ़ो(adapter, i, (__le32 *)&buf[i]);
	स_नकल(data, buf + e->offset, e->len);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops t1_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX |
				     ETHTOOL_COALESCE_RATE_SAMPLE_INTERVAL,
	.get_drvinfo       = get_drvinfo,
	.get_msglevel      = get_msglevel,
	.set_msglevel      = set_msglevel,
	.get_ringparam     = get_sge_param,
	.set_ringparam     = set_sge_param,
	.get_coalesce      = get_coalesce,
	.set_coalesce      = set_coalesce,
	.get_eeprom_len    = get_eeprom_len,
	.get_eeprom        = get_eeprom,
	.get_छोड़ोparam    = get_छोड़ोparam,
	.set_छोड़ोparam    = set_छोड़ोparam,
	.get_link          = ethtool_op_get_link,
	.get_strings       = get_strings,
	.get_sset_count	   = get_sset_count,
	.get_ethtool_stats = get_stats,
	.get_regs_len      = get_regs_len,
	.get_regs          = get_regs,
	.get_link_ksettings = get_link_ksettings,
	.set_link_ksettings = set_link_ksettings,
पूर्ण;

अटल पूर्णांक t1_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा mdio_अगर_info *mdio = &adapter->port[dev->अगर_port].phy->mdio;

	वापस mdio_mii_ioctl(mdio, अगर_mii(req), cmd);
पूर्ण

अटल पूर्णांक t1_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	पूर्णांक ret;
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा cmac *mac = adapter->port[dev->अगर_port].mac;

	अगर (!mac->ops->set_mtu)
		वापस -EOPNOTSUPP;
	अगर ((ret = mac->ops->set_mtu(mac, new_mtu)))
		वापस ret;
	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल पूर्णांक t1_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा cmac *mac = adapter->port[dev->अगर_port].mac;
	काष्ठा sockaddr *addr = p;

	अगर (!mac->ops->macaddress_set)
		वापस -EOPNOTSUPP;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	mac->ops->macaddress_set(mac, dev->dev_addr);
	वापस 0;
पूर्ण

अटल netdev_features_t t1_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	/*
	 * Since there is no support क्रम separate rx/tx vlan accel
	 * enable/disable make sure tx flag is always in same state as rx.
	 */
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		features |= NETIF_F_HW_VLAN_CTAG_TX;
	अन्यथा
		features &= ~NETIF_F_HW_VLAN_CTAG_TX;

	वापस features;
पूर्ण

अटल पूर्णांक t1_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	netdev_features_t changed = dev->features ^ features;
	काष्ठा adapter *adapter = dev->ml_priv;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		t1_vlan_mode(adapter, features);

	वापस 0;
पूर्ण
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम t1_netpoll(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा adapter *adapter = dev->ml_priv;

	local_irq_save(flags);
	t1_पूर्णांकerrupt(adapter->pdev->irq, adapter);
	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर

/*
 * Periodic accumulation of MAC statistics.  This is used only अगर the MAC
 * करोes not have any other way to prevent stats counter overflow.
 */
अटल व्योम mac_stats_task(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i;
	काष्ठा adapter *adapter =
		container_of(work, काष्ठा adapter, stats_update_task.work);

	क्रम_each_port(adapter, i) अणु
		काष्ठा port_info *p = &adapter->port[i];

		अगर (netअगर_running(p->dev))
			p->mac->ops->statistics_update(p->mac,
						       MAC_STATS_UPDATE_FAST);
	पूर्ण

	/* Schedule the next statistics update अगर any port is active. */
	spin_lock(&adapter->work_lock);
	अगर (adapter->खोलो_device_map & PORT_MASK)
		schedule_mac_stats_update(adapter,
					  adapter->params.stats_update_period);
	spin_unlock(&adapter->work_lock);
पूर्ण

अटल स्थिर काष्ठा net_device_ops cxgb_netdev_ops = अणु
	.nकरो_खोलो		= cxgb_खोलो,
	.nकरो_stop		= cxgb_बंद,
	.nकरो_start_xmit		= t1_start_xmit,
	.nकरो_get_stats		= t1_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= t1_set_rxmode,
	.nकरो_करो_ioctl		= t1_ioctl,
	.nकरो_change_mtu		= t1_change_mtu,
	.nकरो_set_mac_address	= t1_set_mac_addr,
	.nकरो_fix_features	= t1_fix_features,
	.nकरो_set_features	= t1_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= t1_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक i, err, pci_using_dac = 0;
	अचिन्हित दीर्घ mmio_start, mmio_len;
	स्थिर काष्ठा board_info *bi;
	काष्ठा adapter *adapter = शून्य;
	काष्ठा port_info *pi;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		pr_err("%s: cannot find PCI device memory base address\n",
		       pci_name(pdev));
		err = -ENODEV;
		जाओ out_disable_pdev;
	पूर्ण

	अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
		pci_using_dac = 1;

		अगर (dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
			pr_err("%s: unable to obtain 64-bit DMA for coherent allocations\n",
			       pci_name(pdev));
			err = -ENODEV;
			जाओ out_disable_pdev;
		पूर्ण

	पूर्ण अन्यथा अगर ((err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) != 0) अणु
		pr_err("%s: no usable DMA configuration\n", pci_name(pdev));
		जाओ out_disable_pdev;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		pr_err("%s: cannot obtain PCI resources\n", pci_name(pdev));
		जाओ out_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	mmio_start = pci_resource_start(pdev, 0);
	mmio_len = pci_resource_len(pdev, 0);
	bi = t1_get_board_info(ent->driver_data);

	क्रम (i = 0; i < bi->port_number; ++i) अणु
		काष्ठा net_device *netdev;

		netdev = alloc_etherdev(adapter ? 0 : माप(*adapter));
		अगर (!netdev) अणु
			err = -ENOMEM;
			जाओ out_मुक्त_dev;
		पूर्ण

		SET_NETDEV_DEV(netdev, &pdev->dev);

		अगर (!adapter) अणु
			adapter = netdev_priv(netdev);
			adapter->pdev = pdev;
			adapter->port[0].dev = netdev;  /* so we करोn't leak it */

			adapter->regs = ioremap(mmio_start, mmio_len);
			अगर (!adapter->regs) अणु
				pr_err("%s: cannot map device registers\n",
				       pci_name(pdev));
				err = -ENOMEM;
				जाओ out_मुक्त_dev;
			पूर्ण

			अगर (t1_get_board_rev(adapter, bi, &adapter->params)) अणु
				err = -ENODEV;	  /* Can't handle this chip rev */
				जाओ out_मुक्त_dev;
			पूर्ण

			adapter->name = pci_name(pdev);
			adapter->msg_enable = dflt_msg_enable;
			adapter->mmio_len = mmio_len;

			spin_lock_init(&adapter->tpi_lock);
			spin_lock_init(&adapter->work_lock);
			spin_lock_init(&adapter->async_lock);
			spin_lock_init(&adapter->mac_lock);

			INIT_DELAYED_WORK(&adapter->stats_update_task,
					  mac_stats_task);

			pci_set_drvdata(pdev, netdev);
		पूर्ण

		pi = &adapter->port[i];
		pi->dev = netdev;
		netअगर_carrier_off(netdev);
		netdev->irq = pdev->irq;
		netdev->अगर_port = i;
		netdev->mem_start = mmio_start;
		netdev->mem_end = mmio_start + mmio_len - 1;
		netdev->ml_priv = adapter;
		netdev->hw_features |= NETIF_F_SG | NETIF_F_IP_CSUM |
			NETIF_F_RXCSUM;
		netdev->features |= NETIF_F_SG | NETIF_F_IP_CSUM |
			NETIF_F_RXCSUM | NETIF_F_LLTX;

		अगर (pci_using_dac)
			netdev->features |= NETIF_F_HIGHDMA;
		अगर (vlan_tso_capable(adapter)) अणु
			netdev->features |=
				NETIF_F_HW_VLAN_CTAG_TX |
				NETIF_F_HW_VLAN_CTAG_RX;
			netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_RX;

			/* T204: disable TSO */
			अगर (!(is_T2(adapter)) || bi->port_number != 4) अणु
				netdev->hw_features |= NETIF_F_TSO;
				netdev->features |= NETIF_F_TSO;
			पूर्ण
		पूर्ण

		netdev->netdev_ops = &cxgb_netdev_ops;
		netdev->hard_header_len += (netdev->hw_features & NETIF_F_TSO) ?
			माप(काष्ठा cpl_tx_pkt_lso) : माप(काष्ठा cpl_tx_pkt);

		netअगर_napi_add(netdev, &adapter->napi, t1_poll, 64);

		netdev->ethtool_ops = &t1_ethtool_ops;

		चयन (bi->board) अणु
		हाल CHBT_BOARD_CHT110:
		हाल CHBT_BOARD_N110:
		हाल CHBT_BOARD_N210:
		हाल CHBT_BOARD_CHT210:
			netdev->max_mtu = PM3393_MAX_FRAME_SIZE -
					  (ETH_HLEN + ETH_FCS_LEN);
			अवरोध;
		हाल CHBT_BOARD_CHN204:
			netdev->max_mtu = VSC7326_MAX_MTU;
			अवरोध;
		शेष:
			netdev->max_mtu = ETH_DATA_LEN;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (t1_init_sw_modules(adapter, bi) < 0) अणु
		err = -ENODEV;
		जाओ out_मुक्त_dev;
	पूर्ण

	/*
	 * The card is now पढ़ोy to go.  If any errors occur during device
	 * registration we करो not fail the whole card but rather proceed only
	 * with the ports we manage to रेजिस्टर successfully.  However we must
	 * रेजिस्टर at least one net device.
	 */
	क्रम (i = 0; i < bi->port_number; ++i) अणु
		err = रेजिस्टर_netdev(adapter->port[i].dev);
		अगर (err)
			pr_warn("%s: cannot register net device %s, skipping\n",
				pci_name(pdev), adapter->port[i].dev->name);
		अन्यथा अणु
			/*
			 * Change the name we use क्रम messages to the name of
			 * the first successfully रेजिस्टरed पूर्णांकerface.
			 */
			अगर (!adapter->रेजिस्टरed_device_map)
				adapter->name = adapter->port[i].dev->name;

			__set_bit(i, &adapter->रेजिस्टरed_device_map);
		पूर्ण
	पूर्ण
	अगर (!adapter->रेजिस्टरed_device_map) अणु
		pr_err("%s: could not register any net devices\n",
		       pci_name(pdev));
		जाओ out_release_adapter_res;
	पूर्ण

	pr_info("%s: %s (rev %d), %s %dMHz/%d-bit\n",
		adapter->name, bi->desc, adapter->params.chip_revision,
		adapter->params.pci.is_pcix ? "PCIX" : "PCI",
		adapter->params.pci.speed, adapter->params.pci.width);

	/*
	 * Set the T1B ASIC and memory घड़ीs.
	 */
	अगर (t1घातersave)
		adapter->t1घातersave = LCLOCK;	/* HW शेष is घातersave mode. */
	अन्यथा
		adapter->t1घातersave = HCLOCK;
	अगर (t1_is_T1B(adapter))
		t1_घड़ी(adapter, t1घातersave);

	वापस 0;

out_release_adapter_res:
	t1_मुक्त_sw_modules(adapter);
out_मुक्त_dev:
	अगर (adapter) अणु
		अगर (adapter->regs)
			iounmap(adapter->regs);
		क्रम (i = bi->port_number - 1; i >= 0; --i)
			अगर (adapter->port[i].dev)
				मुक्त_netdev(adapter->port[i].dev);
	पूर्ण
	pci_release_regions(pdev);
out_disable_pdev:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

अटल व्योम bit_bang(काष्ठा adapter *adapter, पूर्णांक bitdata, पूर्णांक nbits)
अणु
	पूर्णांक data;
	पूर्णांक i;
	u32 val;

	क्रमागत अणु
		S_CLOCK = 1 << 3,
		S_DATA = 1 << 4
	पूर्ण;

	क्रम (i = (nbits - 1); i > -1; i--) अणु

		udelay(50);

		data = ((bitdata >> i) & 0x1);
		__t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);

		अगर (data)
			val |= S_DATA;
		अन्यथा
			val &= ~S_DATA;

		udelay(50);

		/* Set SCLOCK low */
		val &= ~S_CLOCK;
		__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);

		udelay(50);

		/* Write SCLOCK high */
		val |= S_CLOCK;
		__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);

	पूर्ण
पूर्ण

अटल पूर्णांक t1_घड़ी(काष्ठा adapter *adapter, पूर्णांक mode)
अणु
	u32 val;
	पूर्णांक M_CORE_VAL;
	पूर्णांक M_MEM_VAL;

	क्रमागत अणु
		M_CORE_BITS	= 9,
		T_CORE_VAL	= 0,
		T_CORE_BITS	= 2,
		N_CORE_VAL	= 0,
		N_CORE_BITS	= 2,
		M_MEM_BITS	= 9,
		T_MEM_VAL	= 0,
		T_MEM_BITS	= 2,
		N_MEM_VAL	= 0,
		N_MEM_BITS	= 2,
		NP_LOAD		= 1 << 17,
		S_LOAD_MEM	= 1 << 5,
		S_LOAD_CORE	= 1 << 6,
		S_CLOCK		= 1 << 3
	पूर्ण;

	अगर (!t1_is_T1B(adapter))
		वापस -ENODEV;	/* Can't re-घड़ी this chip. */

	अगर (mode & 2)
		वापस 0;	/* show current mode. */

	अगर ((adapter->t1घातersave & 1) == (mode & 1))
		वापस -EALREADY;	/* ASIC alपढ़ोy running in mode. */

	अगर ((mode & 1) == HCLOCK) अणु
		M_CORE_VAL = 0x14;
		M_MEM_VAL = 0x18;
		adapter->t1घातersave = HCLOCK;	/* overघड़ी */
	पूर्ण अन्यथा अणु
		M_CORE_VAL = 0xe;
		M_MEM_VAL = 0x10;
		adapter->t1घातersave = LCLOCK;	/* underघड़ी */
	पूर्ण

	/* Don't पूर्णांकerrupt this serial stream! */
	spin_lock(&adapter->tpi_lock);

	/* Initialize क्रम ASIC core */
	__t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val |= NP_LOAD;
	udelay(50);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(50);
	__t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val &= ~S_LOAD_CORE;
	val &= ~S_CLOCK;
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(50);

	/* Serial program the ASIC घड़ी synthesizer */
	bit_bang(adapter, T_CORE_VAL, T_CORE_BITS);
	bit_bang(adapter, N_CORE_VAL, N_CORE_BITS);
	bit_bang(adapter, M_CORE_VAL, M_CORE_BITS);
	udelay(50);

	/* Finish ASIC core */
	__t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val |= S_LOAD_CORE;
	udelay(50);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(50);
	__t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val &= ~S_LOAD_CORE;
	udelay(50);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(50);

	/* Initialize क्रम memory */
	__t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val |= NP_LOAD;
	udelay(50);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(50);
	__t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val &= ~S_LOAD_MEM;
	val &= ~S_CLOCK;
	udelay(50);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(50);

	/* Serial program the memory घड़ी synthesizer */
	bit_bang(adapter, T_MEM_VAL, T_MEM_BITS);
	bit_bang(adapter, N_MEM_VAL, N_MEM_BITS);
	bit_bang(adapter, M_MEM_VAL, M_MEM_BITS);
	udelay(50);

	/* Finish memory */
	__t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val |= S_LOAD_MEM;
	udelay(50);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(50);
	__t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val &= ~S_LOAD_MEM;
	udelay(50);
	__t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);

	spin_unlock(&adapter->tpi_lock);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम t1_sw_reset(काष्ठा pci_dev *pdev)
अणु
	pci_ग_लिखो_config_dword(pdev, A_PCICFG_PM_CSR, 3);
	pci_ग_लिखो_config_dword(pdev, A_PCICFG_PM_CSR, 0);
पूर्ण

अटल व्योम हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा adapter *adapter = dev->ml_priv;
	पूर्णांक i;

	क्रम_each_port(adapter, i) अणु
		अगर (test_bit(i, &adapter->रेजिस्टरed_device_map))
			unरेजिस्टर_netdev(adapter->port[i].dev);
	पूर्ण

	t1_मुक्त_sw_modules(adapter);
	iounmap(adapter->regs);

	जबतक (--i >= 0) अणु
		अगर (adapter->port[i].dev)
			मुक्त_netdev(adapter->port[i].dev);
	पूर्ण

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	t1_sw_reset(pdev);
पूर्ण

अटल काष्ठा pci_driver cxgb_pci_driver = अणु
	.name     = DRV_NAME,
	.id_table = t1_pci_tbl,
	.probe    = init_one,
	.हटाओ   = हटाओ_one,
पूर्ण;

module_pci_driver(cxgb_pci_driver);
