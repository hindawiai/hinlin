<शैली गुरु>
/*
 * Copyright (c) 2003-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/sockios.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/firmware.h>
#समावेश <linux/log2.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/nospec.h>

#समावेश "common.h"
#समावेश "cxgb3_ioctl.h"
#समावेश "regs.h"
#समावेश "cxgb3_offload.h"
#समावेश "version.h"

#समावेश "cxgb3_ctl_defs.h"
#समावेश "t3_cpl.h"
#समावेश "firmware_exports.h"

क्रमागत अणु
	MAX_TXQ_ENTRIES = 16384,
	MAX_CTRL_TXQ_ENTRIES = 1024,
	MAX_RSPQ_ENTRIES = 16384,
	MAX_RX_BUFFERS = 16384,
	MAX_RX_JUMBO_BUFFERS = 16384,
	MIN_TXQ_ENTRIES = 4,
	MIN_CTRL_TXQ_ENTRIES = 4,
	MIN_RSPQ_ENTRIES = 32,
	MIN_FL_ENTRIES = 32
पूर्ण;

#घोषणा PORT_MASK ((1 << MAX_NPORTS) - 1)

#घोषणा DFLT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK | \
			 NETIF_MSG_TIMER | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP |\
			 NETIF_MSG_RX_ERR | NETIF_MSG_TX_ERR)

#घोषणा EEPROM_MAGIC 0x38E2F10C

#घोषणा CH_DEVICE(devid, idx) \
	अणु PCI_VENDOR_ID_CHELSIO, devid, PCI_ANY_ID, PCI_ANY_ID, 0, 0, idx पूर्ण

अटल स्थिर काष्ठा pci_device_id cxgb3_pci_tbl[] = अणु
	CH_DEVICE(0x20, 0),	/* PE9000 */
	CH_DEVICE(0x21, 1),	/* T302E */
	CH_DEVICE(0x22, 2),	/* T310E */
	CH_DEVICE(0x23, 3),	/* T320X */
	CH_DEVICE(0x24, 1),	/* T302X */
	CH_DEVICE(0x25, 3),	/* T320E */
	CH_DEVICE(0x26, 2),	/* T310X */
	CH_DEVICE(0x30, 2),	/* T3B10 */
	CH_DEVICE(0x31, 3),	/* T3B20 */
	CH_DEVICE(0x32, 1),	/* T3B02 */
	CH_DEVICE(0x35, 6),	/* T3C20-derived T3C10 */
	CH_DEVICE(0x36, 3),	/* S320E-CR */
	CH_DEVICE(0x37, 7),	/* N320E-G2 */
	अणु0,पूर्ण
पूर्ण;

MODULE_DESCRIPTION(DRV_DESC);
MODULE_AUTHOR("Chelsio Communications");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DEVICE_TABLE(pci, cxgb3_pci_tbl);

अटल पूर्णांक dflt_msg_enable = DFLT_MSG_ENABLE;

module_param(dflt_msg_enable, पूर्णांक, 0644);
MODULE_PARM_DESC(dflt_msg_enable, "Chelsio T3 default message enable bitmap");

/*
 * The driver uses the best पूर्णांकerrupt scheme available on a platक्रमm in the
 * order MSI-X, MSI, legacy pin पूर्णांकerrupts.  This parameter determines which
 * of these schemes the driver may consider as follows:
 *
 * msi = 2: choose from among all three options
 * msi = 1: only consider MSI and pin पूर्णांकerrupts
 * msi = 0: क्रमce pin पूर्णांकerrupts
 */
अटल पूर्णांक msi = 2;

module_param(msi, पूर्णांक, 0644);
MODULE_PARM_DESC(msi, "whether to use MSI or MSI-X");

/*
 * The driver enables offload as a शेष.
 * To disable it, use ofld_disable = 1.
 */

अटल पूर्णांक ofld_disable = 0;

module_param(ofld_disable, पूर्णांक, 0644);
MODULE_PARM_DESC(ofld_disable, "whether to enable offload at init time or not");

/*
 * We have work elements that we need to cancel when an पूर्णांकerface is taken
 * करोwn.  Normally the work elements would be executed by keventd but that
 * can deadlock because of linkwatch.  If our बंद method takes the rtnl
 * lock and linkwatch is ahead of our work elements in keventd, linkwatch
 * will block keventd as it needs the rtnl lock, and we'll deadlock रुकोing
 * क्रम our work to complete.  Get our own work queue to solve this.
 */
काष्ठा workqueue_काष्ठा *cxgb3_wq;

/**
 *	link_report - show link status and link speed/duplex
 *	@dev: the port whose settings are to be reported
 *
 *	Shows the link status, speed, and duplex of a port.
 */
अटल व्योम link_report(काष्ठा net_device *dev)
अणु
	अगर (!netअगर_carrier_ok(dev))
		netdev_info(dev, "link down\n");
	अन्यथा अणु
		स्थिर अक्षर *s = "10Mbps";
		स्थिर काष्ठा port_info *p = netdev_priv(dev);

		चयन (p->link_config.speed) अणु
		हाल SPEED_10000:
			s = "10Gbps";
			अवरोध;
		हाल SPEED_1000:
			s = "1000Mbps";
			अवरोध;
		हाल SPEED_100:
			s = "100Mbps";
			अवरोध;
		पूर्ण

		netdev_info(dev, "link up, %s, %s-duplex\n",
			    s, p->link_config.duplex == DUPLEX_FULL
			    ? "full" : "half");
	पूर्ण
पूर्ण

अटल व्योम enable_tx_fअगरo_drain(काष्ठा adapter *adapter,
				 काष्ठा port_info *pi)
अणु
	t3_set_reg_field(adapter, A_XGM_TXFIFO_CFG + pi->mac.offset, 0,
			 F_ENDROPPKT);
	t3_ग_लिखो_reg(adapter, A_XGM_RX_CTRL + pi->mac.offset, 0);
	t3_ग_लिखो_reg(adapter, A_XGM_TX_CTRL + pi->mac.offset, F_TXEN);
	t3_ग_लिखो_reg(adapter, A_XGM_RX_CTRL + pi->mac.offset, F_RXEN);
पूर्ण

अटल व्योम disable_tx_fअगरo_drain(काष्ठा adapter *adapter,
				  काष्ठा port_info *pi)
अणु
	t3_set_reg_field(adapter, A_XGM_TXFIFO_CFG + pi->mac.offset,
			 F_ENDROPPKT, 0);
पूर्ण

व्योम t3_os_link_fault(काष्ठा adapter *adap, पूर्णांक port_id, पूर्णांक state)
अणु
	काष्ठा net_device *dev = adap->port[port_id];
	काष्ठा port_info *pi = netdev_priv(dev);

	अगर (state == netअगर_carrier_ok(dev))
		वापस;

	अगर (state) अणु
		काष्ठा cmac *mac = &pi->mac;

		netअगर_carrier_on(dev);

		disable_tx_fअगरo_drain(adap, pi);

		/* Clear local faults */
		t3_xgm_पूर्णांकr_disable(adap, pi->port_id);
		t3_पढ़ो_reg(adap, A_XGM_INT_STATUS +
				    pi->mac.offset);
		t3_ग_लिखो_reg(adap,
			     A_XGM_INT_CAUSE + pi->mac.offset,
			     F_XGM_INT);

		t3_set_reg_field(adap,
				 A_XGM_INT_ENABLE +
				 pi->mac.offset,
				 F_XGM_INT, F_XGM_INT);
		t3_xgm_पूर्णांकr_enable(adap, pi->port_id);

		t3_mac_enable(mac, MAC_सूचीECTION_TX);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(dev);

		/* Flush TX FIFO */
		enable_tx_fअगरo_drain(adap, pi);
	पूर्ण
	link_report(dev);
पूर्ण

/**
 *	t3_os_link_changed - handle link status changes
 *	@adapter: the adapter associated with the link change
 *	@port_id: the port index whose limk status has changed
 *	@link_stat: the new status of the link
 *	@speed: the new speed setting
 *	@duplex: the new duplex setting
 *	@छोड़ो: the new flow-control setting
 *
 *	This is the OS-dependent handler क्रम link status changes.  The OS
 *	neutral handler takes care of most of the processing क्रम these events,
 *	then calls this handler क्रम any OS-specअगरic processing.
 */
व्योम t3_os_link_changed(काष्ठा adapter *adapter, पूर्णांक port_id, पूर्णांक link_stat,
			पूर्णांक speed, पूर्णांक duplex, पूर्णांक छोड़ो)
अणु
	काष्ठा net_device *dev = adapter->port[port_id];
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा cmac *mac = &pi->mac;

	/* Skip changes from disabled ports. */
	अगर (!netअगर_running(dev))
		वापस;

	अगर (link_stat != netअगर_carrier_ok(dev)) अणु
		अगर (link_stat) अणु
			disable_tx_fअगरo_drain(adapter, pi);

			t3_mac_enable(mac, MAC_सूचीECTION_RX);

			/* Clear local faults */
			t3_xgm_पूर्णांकr_disable(adapter, pi->port_id);
			t3_पढ़ो_reg(adapter, A_XGM_INT_STATUS +
				    pi->mac.offset);
			t3_ग_लिखो_reg(adapter,
				     A_XGM_INT_CAUSE + pi->mac.offset,
				     F_XGM_INT);

			t3_set_reg_field(adapter,
					 A_XGM_INT_ENABLE + pi->mac.offset,
					 F_XGM_INT, F_XGM_INT);
			t3_xgm_पूर्णांकr_enable(adapter, pi->port_id);

			netअगर_carrier_on(dev);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(dev);

			t3_xgm_पूर्णांकr_disable(adapter, pi->port_id);
			t3_पढ़ो_reg(adapter, A_XGM_INT_STATUS + pi->mac.offset);
			t3_set_reg_field(adapter,
					 A_XGM_INT_ENABLE + pi->mac.offset,
					 F_XGM_INT, 0);

			अगर (is_10G(adapter))
				pi->phy.ops->घातer_करोwn(&pi->phy, 1);

			t3_पढ़ो_reg(adapter, A_XGM_INT_STATUS + pi->mac.offset);
			t3_mac_disable(mac, MAC_सूचीECTION_RX);
			t3_link_start(&pi->phy, mac, &pi->link_config);

			/* Flush TX FIFO */
			enable_tx_fअगरo_drain(adapter, pi);
		पूर्ण

		link_report(dev);
	पूर्ण
पूर्ण

/**
 *	t3_os_phymod_changed - handle PHY module changes
 *	@adap: the adapter associated with the link change
 *	@port_id: the port index whose limk status has changed
 *
 *	This is the OS-dependent handler क्रम PHY module changes.  It is
 *	invoked when a PHY module is हटाओd or inserted क्रम any OS-specअगरic
 *	processing.
 */
व्योम t3_os_phymod_changed(काष्ठा adapter *adap, पूर्णांक port_id)
अणु
	अटल स्थिर अक्षर *mod_str[] = अणु
		शून्य, "SR", "LR", "LRM", "TWINAX", "TWINAX", "unknown"
	पूर्ण;

	स्थिर काष्ठा net_device *dev = adap->port[port_id];
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);

	अगर (pi->phy.modtype == phy_modtype_none)
		netdev_info(dev, "PHY module unplugged\n");
	अन्यथा
		netdev_info(dev, "%s PHY module inserted\n",
			    mod_str[pi->phy.modtype]);
पूर्ण

अटल व्योम cxgb_set_rxmode(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);

	t3_mac_set_rx_mode(&pi->mac, dev);
पूर्ण

/**
 *	link_start - enable a port
 *	@dev: the device to enable
 *
 *	Perक्रमms the MAC and PHY actions needed to enable a port.
 */
अटल व्योम link_start(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा cmac *mac = &pi->mac;

	t3_mac_reset(mac);
	t3_mac_set_num_ucast(mac, MAX_MAC_IDX);
	t3_mac_set_mtu(mac, dev->mtu);
	t3_mac_set_address(mac, LAN_MAC_IDX, dev->dev_addr);
	t3_mac_set_address(mac, SAN_MAC_IDX, pi->iscsic.mac_addr);
	t3_mac_set_rx_mode(mac, dev);
	t3_link_start(&pi->phy, mac, &pi->link_config);
	t3_mac_enable(mac, MAC_सूचीECTION_RX | MAC_सूचीECTION_TX);
पूर्ण

अटल अंतरभूत व्योम cxgb_disable_msi(काष्ठा adapter *adapter)
अणु
	अगर (adapter->flags & USING_MSIX) अणु
		pci_disable_msix(adapter->pdev);
		adapter->flags &= ~USING_MSIX;
	पूर्ण अन्यथा अगर (adapter->flags & USING_MSI) अणु
		pci_disable_msi(adapter->pdev);
		adapter->flags &= ~USING_MSI;
	पूर्ण
पूर्ण

/*
 * Interrupt handler क्रम asynchronous events used with MSI-X.
 */
अटल irqवापस_t t3_async_पूर्णांकr_handler(पूर्णांक irq, व्योम *cookie)
अणु
	t3_slow_पूर्णांकr_handler(cookie);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Name the MSI-X पूर्णांकerrupts.
 */
अटल व्योम name_msix_vecs(काष्ठा adapter *adap)
अणु
	पूर्णांक i, j, msi_idx = 1, n = माप(adap->msix_info[0].desc) - 1;

	snम_लिखो(adap->msix_info[0].desc, n, "%s", adap->name);
	adap->msix_info[0].desc[n] = 0;

	क्रम_each_port(adap, j) अणु
		काष्ठा net_device *d = adap->port[j];
		स्थिर काष्ठा port_info *pi = netdev_priv(d);

		क्रम (i = 0; i < pi->nqsets; i++, msi_idx++) अणु
			snम_लिखो(adap->msix_info[msi_idx].desc, n,
				 "%s-%d", d->name, pi->first_qset + i);
			adap->msix_info[msi_idx].desc[n] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक request_msix_data_irqs(काष्ठा adapter *adap)
अणु
	पूर्णांक i, j, err, qidx = 0;

	क्रम_each_port(adap, i) अणु
		पूर्णांक nqsets = adap2pinfo(adap, i)->nqsets;

		क्रम (j = 0; j < nqsets; ++j) अणु
			err = request_irq(adap->msix_info[qidx + 1].vec,
					  t3_पूर्णांकr_handler(adap,
							  adap->sge.qs[qidx].
							  rspq.polling), 0,
					  adap->msix_info[qidx + 1].desc,
					  &adap->sge.qs[qidx]);
			अगर (err) अणु
				जबतक (--qidx >= 0)
					मुक्त_irq(adap->msix_info[qidx + 1].vec,
						 &adap->sge.qs[qidx]);
				वापस err;
			पूर्ण
			qidx++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम मुक्त_irq_resources(काष्ठा adapter *adapter)
अणु
	अगर (adapter->flags & USING_MSIX) अणु
		पूर्णांक i, n = 0;

		मुक्त_irq(adapter->msix_info[0].vec, adapter);
		क्रम_each_port(adapter, i)
			n += adap2pinfo(adapter, i)->nqsets;

		क्रम (i = 0; i < n; ++i)
			मुक्त_irq(adapter->msix_info[i + 1].vec,
				 &adapter->sge.qs[i]);
	पूर्ण अन्यथा
		मुक्त_irq(adapter->pdev->irq, adapter);
पूर्ण

अटल पूर्णांक aरुको_mgmt_replies(काष्ठा adapter *adap, अचिन्हित दीर्घ init_cnt,
			      अचिन्हित दीर्घ n)
अणु
	पूर्णांक attempts = 10;

	जबतक (adap->sge.qs[0].rspq.offload_pkts < init_cnt + n) अणु
		अगर (!--attempts)
			वापस -ETIMEDOUT;
		msleep(10);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक init_tp_parity(काष्ठा adapter *adap)
अणु
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा cpl_set_tcb_field *greq;
	अचिन्हित दीर्घ cnt = adap->sge.qs[0].rspq.offload_pkts;

	t3_tp_set_offload_mode(adap, 1);

	क्रम (i = 0; i < 16; i++) अणु
		काष्ठा cpl_smt_ग_लिखो_req *req;

		skb = alloc_skb(माप(*req), GFP_KERNEL);
		अगर (!skb)
			skb = adap->nofail_skb;
		अगर (!skb)
			जाओ alloc_skb_fail;

		req = __skb_put_zero(skb, माप(*req));
		req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
		OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SMT_WRITE_REQ, i));
		req->mtu_idx = NMTUS - 1;
		req->अगरf = i;
		t3_mgmt_tx(adap, skb);
		अगर (skb == adap->nofail_skb) अणु
			aरुको_mgmt_replies(adap, cnt, i + 1);
			adap->nofail_skb = alloc_skb(माप(*greq), GFP_KERNEL);
			अगर (!adap->nofail_skb)
				जाओ alloc_skb_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2048; i++) अणु
		काष्ठा cpl_l2t_ग_लिखो_req *req;

		skb = alloc_skb(माप(*req), GFP_KERNEL);
		अगर (!skb)
			skb = adap->nofail_skb;
		अगर (!skb)
			जाओ alloc_skb_fail;

		req = __skb_put_zero(skb, माप(*req));
		req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
		OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_L2T_WRITE_REQ, i));
		req->params = htonl(V_L2T_W_IDX(i));
		t3_mgmt_tx(adap, skb);
		अगर (skb == adap->nofail_skb) अणु
			aरुको_mgmt_replies(adap, cnt, 16 + i + 1);
			adap->nofail_skb = alloc_skb(माप(*greq), GFP_KERNEL);
			अगर (!adap->nofail_skb)
				जाओ alloc_skb_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2048; i++) अणु
		काष्ठा cpl_rte_ग_लिखो_req *req;

		skb = alloc_skb(माप(*req), GFP_KERNEL);
		अगर (!skb)
			skb = adap->nofail_skb;
		अगर (!skb)
			जाओ alloc_skb_fail;

		req = __skb_put_zero(skb, माप(*req));
		req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
		OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_RTE_WRITE_REQ, i));
		req->l2t_idx = htonl(V_L2T_W_IDX(i));
		t3_mgmt_tx(adap, skb);
		अगर (skb == adap->nofail_skb) अणु
			aरुको_mgmt_replies(adap, cnt, 16 + 2048 + i + 1);
			adap->nofail_skb = alloc_skb(माप(*greq), GFP_KERNEL);
			अगर (!adap->nofail_skb)
				जाओ alloc_skb_fail;
		पूर्ण
	पूर्ण

	skb = alloc_skb(माप(*greq), GFP_KERNEL);
	अगर (!skb)
		skb = adap->nofail_skb;
	अगर (!skb)
		जाओ alloc_skb_fail;

	greq = __skb_put_zero(skb, माप(*greq));
	greq->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(greq) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, 0));
	greq->mask = cpu_to_be64(1);
	t3_mgmt_tx(adap, skb);

	i = aरुको_mgmt_replies(adap, cnt, 16 + 2048 + 2048 + 1);
	अगर (skb == adap->nofail_skb) अणु
		i = aरुको_mgmt_replies(adap, cnt, 16 + 2048 + 2048 + 1);
		adap->nofail_skb = alloc_skb(माप(*greq), GFP_KERNEL);
	पूर्ण

	t3_tp_set_offload_mode(adap, 0);
	वापस i;

alloc_skb_fail:
	t3_tp_set_offload_mode(adap, 0);
	वापस -ENOMEM;
पूर्ण

/**
 *	setup_rss - configure RSS
 *	@adap: the adapter
 *
 *	Sets up RSS to distribute packets to multiple receive queues.  We
 *	configure the RSS CPU lookup table to distribute to the number of HW
 *	receive queues, and the response queue lookup table to narrow that
 *	करोwn to the response queues actually configured क्रम each port.
 *	We always configure the RSS mapping क्रम two ports since the mapping
 *	table has plenty of entries.
 */
अटल व्योम setup_rss(काष्ठा adapter *adap)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक nq0 = adap2pinfo(adap, 0)->nqsets;
	अचिन्हित पूर्णांक nq1 = adap->port[1] ? adap2pinfo(adap, 1)->nqsets : 1;
	u8 cpus[SGE_QSETS + 1];
	u16 rspq_map[RSS_TABLE_SIZE + 1];

	क्रम (i = 0; i < SGE_QSETS; ++i)
		cpus[i] = i;
	cpus[SGE_QSETS] = 0xff;	/* terminator */

	क्रम (i = 0; i < RSS_TABLE_SIZE / 2; ++i) अणु
		rspq_map[i] = i % nq0;
		rspq_map[i + RSS_TABLE_SIZE / 2] = (i % nq1) + nq0;
	पूर्ण
	rspq_map[RSS_TABLE_SIZE] = 0xffff; /* terminator */

	t3_config_rss(adap, F_RQFEEDBACKENABLE | F_TNLLKPEN | F_TNLMAPEN |
		      F_TNLPRTEN | F_TNL2TUPEN | F_TNL4TUPEN |
		      V_RRCPLCPUSIZE(6) | F_HASHTOEPLITZ, cpus, rspq_map);
पूर्ण

अटल व्योम ring_dbs(काष्ठा adapter *adap)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < SGE_QSETS; i++) अणु
		काष्ठा sge_qset *qs = &adap->sge.qs[i];

		अगर (qs->adap)
			क्रम (j = 0; j < SGE_TXQ_PER_SET; j++)
				t3_ग_लिखो_reg(adap, A_SG_KDOORBELL, F_SELEGRCNTX | V_EGRCNTX(qs->txq[j].cntxt_id));
	पूर्ण
पूर्ण

अटल व्योम init_napi(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SGE_QSETS; i++) अणु
		काष्ठा sge_qset *qs = &adap->sge.qs[i];

		अगर (qs->adap)
			netअगर_napi_add(qs->netdev, &qs->napi, qs->napi.poll,
				       64);
	पूर्ण

	/*
	 * netअगर_napi_add() can be called only once per napi_काष्ठा because it
	 * adds each new napi_काष्ठा to a list.  Be careful not to call it a
	 * second समय, e.g., during EEH recovery, by making a note of it.
	 */
	adap->flags |= NAPI_INIT;
पूर्ण

/*
 * Wait until all NAPI handlers are descheduled.  This includes the handlers of
 * both netdevices representing पूर्णांकerfaces and the dummy ones क्रम the extra
 * queues.
 */
अटल व्योम quiesce_rx(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SGE_QSETS; i++)
		अगर (adap->sge.qs[i].adap)
			napi_disable(&adap->sge.qs[i].napi);
पूर्ण

अटल व्योम enable_all_napi(काष्ठा adapter *adap)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < SGE_QSETS; i++)
		अगर (adap->sge.qs[i].adap)
			napi_enable(&adap->sge.qs[i].napi);
पूर्ण

/**
 *	setup_sge_qsets - configure SGE Tx/Rx/response queues
 *	@adap: the adapter
 *
 *	Determines how many sets of SGE queues to use and initializes them.
 *	We support multiple queue sets per port अगर we have MSI-X, otherwise
 *	just one queue set per port.
 */
अटल पूर्णांक setup_sge_qsets(काष्ठा adapter *adap)
अणु
	पूर्णांक i, j, err, irq_idx = 0, qset_idx = 0;
	अचिन्हित पूर्णांक ntxq = SGE_TXQ_PER_SET;

	अगर (adap->params.rev > 0 && !(adap->flags & USING_MSI))
		irq_idx = -1;

	क्रम_each_port(adap, i) अणु
		काष्ठा net_device *dev = adap->port[i];
		काष्ठा port_info *pi = netdev_priv(dev);

		pi->qs = &adap->sge.qs[pi->first_qset];
		क्रम (j = 0; j < pi->nqsets; ++j, ++qset_idx) अणु
			err = t3_sge_alloc_qset(adap, qset_idx, 1,
				(adap->flags & USING_MSIX) ? qset_idx + 1 :
							     irq_idx,
				&adap->params.sge.qset[qset_idx], ntxq, dev,
				netdev_get_tx_queue(dev, j));
			अगर (err) अणु
				t3_मुक्त_sge_resources(adap);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार attr_show(काष्ठा device *d, अक्षर *buf,
			 sमाप_प्रकार(*क्रमmat) (काष्ठा net_device *, अक्षर *))
अणु
	sमाप_प्रकार len;

	/* Synchronize with ioctls that may shut करोwn the device */
	rtnl_lock();
	len = (*क्रमmat) (to_net_dev(d), buf);
	rtnl_unlock();
	वापस len;
पूर्ण

अटल sमाप_प्रकार attr_store(काष्ठा device *d,
			  स्थिर अक्षर *buf, माप_प्रकार len,
			  sमाप_प्रकार(*set) (काष्ठा net_device *, अचिन्हित पूर्णांक),
			  अचिन्हित पूर्णांक min_val, अचिन्हित पूर्णांक max_val)
अणु
	sमाप_प्रकार ret;
	अचिन्हित पूर्णांक val;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	ret = kstrtouपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;
	अगर (val < min_val || val > max_val)
		वापस -EINVAL;

	rtnl_lock();
	ret = (*set) (to_net_dev(d), val);
	अगर (!ret)
		ret = len;
	rtnl_unlock();
	वापस ret;
पूर्ण

#घोषणा CXGB3_SHOW(name, val_expr) \
अटल sमाप_प्रकार क्रमmat_##name(काष्ठा net_device *dev, अक्षर *buf) \
अणु \
	काष्ठा port_info *pi = netdev_priv(dev); \
	काष्ठा adapter *adap = pi->adapter; \
	वापस प्र_लिखो(buf, "%u\n", val_expr); \
पूर्ण \
अटल sमाप_प्रकार show_##name(काष्ठा device *d, काष्ठा device_attribute *attr, \
			   अक्षर *buf) \
अणु \
	वापस attr_show(d, buf, क्रमmat_##name); \
पूर्ण

अटल sमाप_प्रकार set_nfilters(काष्ठा net_device *dev, अचिन्हित पूर्णांक val)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक min_tids = is_offload(adap) ? MC5_MIN_TIDS : 0;

	अगर (adap->flags & FULL_INIT_DONE)
		वापस -EBUSY;
	अगर (val && adap->params.rev == 0)
		वापस -EINVAL;
	अगर (val > t3_mc5_size(&adap->mc5) - adap->params.mc5.nservers -
	    min_tids)
		वापस -EINVAL;
	adap->params.mc5.nfilters = val;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार store_nfilters(काष्ठा device *d, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस attr_store(d, buf, len, set_nfilters, 0, ~0);
पूर्ण

अटल sमाप_प्रकार set_nservers(काष्ठा net_device *dev, अचिन्हित पूर्णांक val)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;

	अगर (adap->flags & FULL_INIT_DONE)
		वापस -EBUSY;
	अगर (val > t3_mc5_size(&adap->mc5) - adap->params.mc5.nfilters -
	    MC5_MIN_TIDS)
		वापस -EINVAL;
	adap->params.mc5.nservers = val;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार store_nservers(काष्ठा device *d, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस attr_store(d, buf, len, set_nservers, 0, ~0);
पूर्ण

#घोषणा CXGB3_ATTR_R(name, val_expr) \
CXGB3_SHOW(name, val_expr) \
अटल DEVICE_ATTR(name, 0444, show_##name, शून्य)

#घोषणा CXGB3_ATTR_RW(name, val_expr, store_method) \
CXGB3_SHOW(name, val_expr) \
अटल DEVICE_ATTR(name, 0644, show_##name, store_method)

CXGB3_ATTR_R(cam_size, t3_mc5_size(&adap->mc5));
CXGB3_ATTR_RW(nfilters, adap->params.mc5.nfilters, store_nfilters);
CXGB3_ATTR_RW(nservers, adap->params.mc5.nservers, store_nservers);

अटल काष्ठा attribute *cxgb3_attrs[] = अणु
	&dev_attr_cam_size.attr,
	&dev_attr_nfilters.attr,
	&dev_attr_nservers.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cxgb3_attr_group = अणु
	.attrs = cxgb3_attrs,
पूर्ण;

अटल sमाप_प्रकार पंचांग_attr_show(काष्ठा device *d,
			    अक्षर *buf, पूर्णांक sched)
अणु
	काष्ठा port_info *pi = netdev_priv(to_net_dev(d));
	काष्ठा adapter *adap = pi->adapter;
	अचिन्हित पूर्णांक v, addr, bpt, cpt;
	sमाप_प्रकार len;

	addr = A_TP_TX_MOD_Q1_Q0_RATE_LIMIT - sched / 2;
	rtnl_lock();
	t3_ग_लिखो_reg(adap, A_TP_TM_PIO_ADDR, addr);
	v = t3_पढ़ो_reg(adap, A_TP_TM_PIO_DATA);
	अगर (sched & 1)
		v >>= 16;
	bpt = (v >> 8) & 0xff;
	cpt = v & 0xff;
	अगर (!cpt)
		len = प्र_लिखो(buf, "disabled\n");
	अन्यथा अणु
		v = (adap->params.vpd.cclk * 1000) / cpt;
		len = प्र_लिखो(buf, "%u Kbps\n", (v * bpt) / 125);
	पूर्ण
	rtnl_unlock();
	वापस len;
पूर्ण

अटल sमाप_प्रकार पंचांग_attr_store(काष्ठा device *d,
			     स्थिर अक्षर *buf, माप_प्रकार len, पूर्णांक sched)
अणु
	काष्ठा port_info *pi = netdev_priv(to_net_dev(d));
	काष्ठा adapter *adap = pi->adapter;
	अचिन्हित पूर्णांक val;
	sमाप_प्रकार ret;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	ret = kstrtouपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;
	अगर (val > 10000000)
		वापस -EINVAL;

	rtnl_lock();
	ret = t3_config_sched(adap, val, sched);
	अगर (!ret)
		ret = len;
	rtnl_unlock();
	वापस ret;
पूर्ण

#घोषणा TM_ATTR(name, sched) \
अटल sमाप_प्रकार show_##name(काष्ठा device *d, काष्ठा device_attribute *attr, \
			   अक्षर *buf) \
अणु \
	वापस पंचांग_attr_show(d, buf, sched); \
पूर्ण \
अटल sमाप_प्रकार store_##name(काष्ठा device *d, काष्ठा device_attribute *attr, \
			    स्थिर अक्षर *buf, माप_प्रकार len) \
अणु \
	वापस पंचांग_attr_store(d, buf, len, sched); \
पूर्ण \
अटल DEVICE_ATTR(name, 0644, show_##name, store_##name)

TM_ATTR(sched0, 0);
TM_ATTR(sched1, 1);
TM_ATTR(sched2, 2);
TM_ATTR(sched3, 3);
TM_ATTR(sched4, 4);
TM_ATTR(sched5, 5);
TM_ATTR(sched6, 6);
TM_ATTR(sched7, 7);

अटल काष्ठा attribute *offload_attrs[] = अणु
	&dev_attr_sched0.attr,
	&dev_attr_sched1.attr,
	&dev_attr_sched2.attr,
	&dev_attr_sched3.attr,
	&dev_attr_sched4.attr,
	&dev_attr_sched5.attr,
	&dev_attr_sched6.attr,
	&dev_attr_sched7.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group offload_attr_group = अणु
	.attrs = offload_attrs,
पूर्ण;

/*
 * Sends an sk_buff to an offload queue driver
 * after dealing with any active network taps.
 */
अटल अंतरभूत पूर्णांक offload_tx(काष्ठा t3cdev *tdev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	local_bh_disable();
	ret = t3_offload_tx(tdev, skb);
	local_bh_enable();
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_smt_entry(काष्ठा adapter *adapter, पूर्णांक idx)
अणु
	काष्ठा cpl_smt_ग_लिखो_req *req;
	काष्ठा port_info *pi = netdev_priv(adapter->port[idx]);
	काष्ठा sk_buff *skb = alloc_skb(माप(*req), GFP_KERNEL);

	अगर (!skb)
		वापस -ENOMEM;

	req = __skb_put(skb, माप(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SMT_WRITE_REQ, idx));
	req->mtu_idx = NMTUS - 1;	/* should be 0 but there's a T3 bug */
	req->अगरf = idx;
	स_नकल(req->src_mac0, adapter->port[idx]->dev_addr, ETH_ALEN);
	स_नकल(req->src_mac1, pi->iscsic.mac_addr, ETH_ALEN);
	skb->priority = 1;
	offload_tx(&adapter->tdev, skb);
	वापस 0;
पूर्ण

अटल पूर्णांक init_smt(काष्ठा adapter *adapter)
अणु
	पूर्णांक i;

	क्रम_each_port(adapter, i)
	    ग_लिखो_smt_entry(adapter, i);
	वापस 0;
पूर्ण

अटल व्योम init_port_mtus(काष्ठा adapter *adapter)
अणु
	अचिन्हित पूर्णांक mtus = adapter->port[0]->mtu;

	अगर (adapter->port[1])
		mtus |= adapter->port[1]->mtu << 16;
	t3_ग_लिखो_reg(adapter, A_TP_MTU_PORT_TABLE, mtus);
पूर्ण

अटल पूर्णांक send_pktsched_cmd(काष्ठा adapter *adap, पूर्णांक sched, पूर्णांक qidx, पूर्णांक lo,
			      पूर्णांक hi, पूर्णांक port)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा mngt_pktsched_wr *req;
	पूर्णांक ret;

	skb = alloc_skb(माप(*req), GFP_KERNEL);
	अगर (!skb)
		skb = adap->nofail_skb;
	अगर (!skb)
		वापस -ENOMEM;

	req = skb_put(skb, माप(*req));
	req->wr_hi = htonl(V_WR_OP(FW_WROPCODE_MNGT));
	req->mngt_opcode = FW_MNGTOPCODE_PKTSCHED_SET;
	req->sched = sched;
	req->idx = qidx;
	req->min = lo;
	req->max = hi;
	req->binding = port;
	ret = t3_mgmt_tx(adap, skb);
	अगर (skb == adap->nofail_skb) अणु
		adap->nofail_skb = alloc_skb(माप(काष्ठा cpl_set_tcb_field),
					     GFP_KERNEL);
		अगर (!adap->nofail_skb)
			ret = -ENOMEM;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bind_qsets(काष्ठा adapter *adap)
अणु
	पूर्णांक i, j, err = 0;

	क्रम_each_port(adap, i) अणु
		स्थिर काष्ठा port_info *pi = adap2pinfo(adap, i);

		क्रम (j = 0; j < pi->nqsets; ++j) अणु
			पूर्णांक ret = send_pktsched_cmd(adap, 1,
						    pi->first_qset + j, -1,
						    -1, i);
			अगर (ret)
				err = ret;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

#घोषणा FW_VERSION __stringअगरy(FW_VERSION_MAJOR) "."			\
	__stringअगरy(FW_VERSION_MINOR) "." __stringअगरy(FW_VERSION_MICRO)
#घोषणा FW_FNAME "cxgb3/t3fw-" FW_VERSION ".bin"
#घोषणा TPSRAM_VERSION __stringअगरy(TP_VERSION_MAJOR) "."		\
	__stringअगरy(TP_VERSION_MINOR) "." __stringअगरy(TP_VERSION_MICRO)
#घोषणा TPSRAM_NAME "cxgb3/t3%c_psram-" TPSRAM_VERSION ".bin"
#घोषणा AEL2005_OPT_EDC_NAME "cxgb3/ael2005_opt_edc.bin"
#घोषणा AEL2005_TWX_EDC_NAME "cxgb3/ael2005_twx_edc.bin"
#घोषणा AEL2020_TWX_EDC_NAME "cxgb3/ael2020_twx_edc.bin"
MODULE_FIRMWARE(FW_FNAME);
MODULE_FIRMWARE("cxgb3/t3b_psram-" TPSRAM_VERSION ".bin");
MODULE_FIRMWARE("cxgb3/t3c_psram-" TPSRAM_VERSION ".bin");
MODULE_FIRMWARE(AEL2005_OPT_EDC_NAME);
MODULE_FIRMWARE(AEL2005_TWX_EDC_NAME);
MODULE_FIRMWARE(AEL2020_TWX_EDC_NAME);

अटल अंतरभूत स्थिर अक्षर *get_edc_fw_name(पूर्णांक edc_idx)
अणु
	स्थिर अक्षर *fw_name = शून्य;

	चयन (edc_idx) अणु
	हाल EDC_OPT_AEL2005:
		fw_name = AEL2005_OPT_EDC_NAME;
		अवरोध;
	हाल EDC_TWX_AEL2005:
		fw_name = AEL2005_TWX_EDC_NAME;
		अवरोध;
	हाल EDC_TWX_AEL2020:
		fw_name = AEL2020_TWX_EDC_NAME;
		अवरोध;
	पूर्ण
	वापस fw_name;
पूर्ण

पूर्णांक t3_get_edc_fw(काष्ठा cphy *phy, पूर्णांक edc_idx, पूर्णांक size)
अणु
	काष्ठा adapter *adapter = phy->adapter;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name;
	u32 csum;
	स्थिर __be32 *p;
	u16 *cache = phy->phy_cache;
	पूर्णांक i, ret = -EINVAL;

	fw_name = get_edc_fw_name(edc_idx);
	अगर (fw_name)
		ret = request_firmware(&fw, fw_name, &adapter->pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&adapter->pdev->dev,
			"could not upgrade firmware: unable to load %s\n",
			fw_name);
		वापस ret;
	पूर्ण

	/* check size, take checksum in account */
	अगर (fw->size > size + 4) अणु
		CH_ERR(adapter, "firmware image too large %u, expected %d\n",
		       (अचिन्हित पूर्णांक)fw->size, size + 4);
		ret = -EINVAL;
	पूर्ण

	/* compute checksum */
	p = (स्थिर __be32 *)fw->data;
	क्रम (csum = 0, i = 0; i < fw->size / माप(csum); i++)
		csum += ntohl(p[i]);

	अगर (csum != 0xffffffff) अणु
		CH_ERR(adapter, "corrupted firmware image, checksum %u\n",
		       csum);
		ret = -EINVAL;
	पूर्ण

	क्रम (i = 0; i < size / 4 ; i++) अणु
		*cache++ = (be32_to_cpu(p[i]) & 0xffff0000) >> 16;
		*cache++ = be32_to_cpu(p[i]) & 0xffff;
	पूर्ण

	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक upgrade_fw(काष्ठा adapter *adap)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw;
	काष्ठा device *dev = &adap->pdev->dev;

	ret = request_firmware(&fw, FW_FNAME, dev);
	अगर (ret < 0) अणु
		dev_err(dev, "could not upgrade firmware: unable to load %s\n",
			FW_FNAME);
		वापस ret;
	पूर्ण
	ret = t3_load_fw(adap, fw->data, fw->size);
	release_firmware(fw);

	अगर (ret == 0)
		dev_info(dev, "successful upgrade to firmware %d.%d.%d\n",
			 FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_MICRO);
	अन्यथा
		dev_err(dev, "failed to upgrade to firmware %d.%d.%d\n",
			FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_MICRO);

	वापस ret;
पूर्ण

अटल अंतरभूत अक्षर t3rev2अक्षर(काष्ठा adapter *adapter)
अणु
	अक्षर rev = 0;

	चयन(adapter->params.rev) अणु
	हाल T3_REV_B:
	हाल T3_REV_B2:
		rev = 'b';
		अवरोध;
	हाल T3_REV_C:
		rev = 'c';
		अवरोध;
	पूर्ण
	वापस rev;
पूर्ण

अटल पूर्णांक update_tpsram(काष्ठा adapter *adap)
अणु
	स्थिर काष्ठा firmware *tpsram;
	अक्षर buf[64];
	काष्ठा device *dev = &adap->pdev->dev;
	पूर्णांक ret;
	अक्षर rev;

	rev = t3rev2अक्षर(adap);
	अगर (!rev)
		वापस 0;

	snम_लिखो(buf, माप(buf), TPSRAM_NAME, rev);

	ret = request_firmware(&tpsram, buf, dev);
	अगर (ret < 0) अणु
		dev_err(dev, "could not load TP SRAM: unable to load %s\n",
			buf);
		वापस ret;
	पूर्ण

	ret = t3_check_tpsram(adap, tpsram->data, tpsram->size);
	अगर (ret)
		जाओ release_tpsram;

	ret = t3_set_proto_sram(adap, tpsram->data);
	अगर (ret == 0)
		dev_info(dev,
			 "successful update of protocol engine "
			 "to %d.%d.%d\n",
			 TP_VERSION_MAJOR, TP_VERSION_MINOR, TP_VERSION_MICRO);
	अन्यथा
		dev_err(dev, "failed to update of protocol engine %d.%d.%d\n",
			TP_VERSION_MAJOR, TP_VERSION_MINOR, TP_VERSION_MICRO);
	अगर (ret)
		dev_err(dev, "loading protocol SRAM failed\n");

release_tpsram:
	release_firmware(tpsram);

	वापस ret;
पूर्ण

/**
 * t3_synchronize_rx - रुको क्रम current Rx processing on a port to complete
 * @adap: the adapter
 * @p: the port
 *
 * Ensures that current Rx processing on any of the queues associated with
 * the given port completes beक्रमe वापसing.  We करो this by acquiring and
 * releasing the locks of the response queues associated with the port.
 */
अटल व्योम t3_synchronize_rx(काष्ठा adapter *adap, स्थिर काष्ठा port_info *p)
अणु
	पूर्णांक i;

	क्रम (i = p->first_qset; i < p->first_qset + p->nqsets; i++) अणु
		काष्ठा sge_rspq *q = &adap->sge.qs[i].rspq;

		spin_lock_irq(&q->lock);
		spin_unlock_irq(&q->lock);
	पूर्ण
पूर्ण

अटल व्योम cxgb_vlan_mode(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	अगर (adapter->params.rev > 0) अणु
		t3_set_vlan_accel(adapter, 1 << pi->port_id,
				  features & NETIF_F_HW_VLAN_CTAG_RX);
	पूर्ण अन्यथा अणु
		/* single control क्रम all ports */
		अचिन्हित पूर्णांक i, have_vlans = features & NETIF_F_HW_VLAN_CTAG_RX;

		क्रम_each_port(adapter, i)
			have_vlans |=
				adapter->port[i]->features &
				NETIF_F_HW_VLAN_CTAG_RX;

		t3_set_vlan_accel(adapter, 1, have_vlans);
	पूर्ण
	t3_synchronize_rx(adapter, pi);
पूर्ण

/**
 *	cxgb_up - enable the adapter
 *	@adap: adapter being enabled
 *
 *	Called when the first port is enabled, this function perक्रमms the
 *	actions necessary to make an adapter operational, such as completing
 *	the initialization of HW modules, and enabling पूर्णांकerrupts.
 *
 *	Must be called with the rtnl lock held.
 */
अटल पूर्णांक cxgb_up(काष्ठा adapter *adap)
अणु
	पूर्णांक i, err;

	अगर (!(adap->flags & FULL_INIT_DONE)) अणु
		err = t3_check_fw_version(adap);
		अगर (err == -EINVAL) अणु
			err = upgrade_fw(adap);
			CH_WARN(adap, "FW upgrade to %d.%d.%d %s\n",
				FW_VERSION_MAJOR, FW_VERSION_MINOR,
				FW_VERSION_MICRO, err ? "failed" : "succeeded");
		पूर्ण

		err = t3_check_tpsram_version(adap);
		अगर (err == -EINVAL) अणु
			err = update_tpsram(adap);
			CH_WARN(adap, "TP upgrade to %d.%d.%d %s\n",
				TP_VERSION_MAJOR, TP_VERSION_MINOR,
				TP_VERSION_MICRO, err ? "failed" : "succeeded");
		पूर्ण

		/*
		 * Clear पूर्णांकerrupts now to catch errors अगर t3_init_hw fails.
		 * We clear them again later as initialization may trigger
		 * conditions that can पूर्णांकerrupt.
		 */
		t3_पूर्णांकr_clear(adap);

		err = t3_init_hw(adap, 0);
		अगर (err)
			जाओ out;

		t3_set_reg_field(adap, A_TP_PARA_REG5, 0, F_RXDDPOFFINIT);
		t3_ग_लिखो_reg(adap, A_ULPRX_TDDP_PSZ, V_HPZ0(PAGE_SHIFT - 12));

		err = setup_sge_qsets(adap);
		अगर (err)
			जाओ out;

		क्रम_each_port(adap, i)
			cxgb_vlan_mode(adap->port[i], adap->port[i]->features);

		setup_rss(adap);
		अगर (!(adap->flags & NAPI_INIT))
			init_napi(adap);

		t3_start_sge_समयrs(adap);
		adap->flags |= FULL_INIT_DONE;
	पूर्ण

	t3_पूर्णांकr_clear(adap);

	अगर (adap->flags & USING_MSIX) अणु
		name_msix_vecs(adap);
		err = request_irq(adap->msix_info[0].vec,
				  t3_async_पूर्णांकr_handler, 0,
				  adap->msix_info[0].desc, adap);
		अगर (err)
			जाओ irq_err;

		err = request_msix_data_irqs(adap);
		अगर (err) अणु
			मुक्त_irq(adap->msix_info[0].vec, adap);
			जाओ irq_err;
		पूर्ण
	पूर्ण अन्यथा अगर ((err = request_irq(adap->pdev->irq,
				      t3_पूर्णांकr_handler(adap,
						      adap->sge.qs[0].rspq.
						      polling),
				      (adap->flags & USING_MSI) ?
				       0 : IRQF_SHARED,
				      adap->name, adap)))
		जाओ irq_err;

	enable_all_napi(adap);
	t3_sge_start(adap);
	t3_पूर्णांकr_enable(adap);

	अगर (adap->params.rev >= T3_REV_C && !(adap->flags & TP_PARITY_INIT) &&
	    is_offload(adap) && init_tp_parity(adap) == 0)
		adap->flags |= TP_PARITY_INIT;

	अगर (adap->flags & TP_PARITY_INIT) अणु
		t3_ग_लिखो_reg(adap, A_TP_INT_CAUSE,
			     F_CMCACHEPERR | F_ARPLUTPERR);
		t3_ग_लिखो_reg(adap, A_TP_INT_ENABLE, 0x7fbfffff);
	पूर्ण

	अगर (!(adap->flags & QUEUES_BOUND)) अणु
		पूर्णांक ret = bind_qsets(adap);

		अगर (ret < 0) अणु
			CH_ERR(adap, "failed to bind qsets, err %d\n", ret);
			t3_पूर्णांकr_disable(adap);
			मुक्त_irq_resources(adap);
			err = ret;
			जाओ out;
		पूर्ण
		adap->flags |= QUEUES_BOUND;
	पूर्ण

out:
	वापस err;
irq_err:
	CH_ERR(adap, "request_irq failed, err %d\n", err);
	जाओ out;
पूर्ण

/*
 * Release resources when all the ports and offloading have been stopped.
 */
अटल व्योम cxgb_करोwn(काष्ठा adapter *adapter, पूर्णांक on_wq)
अणु
	t3_sge_stop(adapter);
	spin_lock_irq(&adapter->work_lock);	/* sync with PHY पूर्णांकr task */
	t3_पूर्णांकr_disable(adapter);
	spin_unlock_irq(&adapter->work_lock);

	मुक्त_irq_resources(adapter);
	quiesce_rx(adapter);
	t3_sge_stop(adapter);
	अगर (!on_wq)
		flush_workqueue(cxgb3_wq);/* रुको क्रम बाह्यal IRQ handler */
पूर्ण

अटल व्योम schedule_chk_task(काष्ठा adapter *adap)
अणु
	अचिन्हित पूर्णांक समयo;

	समयo = adap->params.linkpoll_period ?
	    (HZ * adap->params.linkpoll_period) / 10 :
	    adap->params.stats_update_period * HZ;
	अगर (समयo)
		queue_delayed_work(cxgb3_wq, &adap->adap_check_task, समयo);
पूर्ण

अटल पूर्णांक offload_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा t3cdev *tdev = dev2t3cdev(dev);
	पूर्णांक adap_up = adapter->खोलो_device_map & PORT_MASK;
	पूर्णांक err;

	अगर (test_and_set_bit(OFFLOAD_DEVMAP_BIT, &adapter->खोलो_device_map))
		वापस 0;

	अगर (!adap_up && (err = cxgb_up(adapter)) < 0)
		जाओ out;

	t3_tp_set_offload_mode(adapter, 1);
	tdev->lldev = adapter->port[0];
	err = cxgb3_offload_activate(adapter);
	अगर (err)
		जाओ out;

	init_port_mtus(adapter);
	t3_load_mtus(adapter, adapter->params.mtus, adapter->params.a_wnd,
		     adapter->params.b_wnd,
		     adapter->params.rev == 0 ?
		     adapter->port[0]->mtu : 0xffff);
	init_smt(adapter);

	अगर (sysfs_create_group(&tdev->lldev->dev.kobj, &offload_attr_group))
		dev_dbg(&dev->dev, "cannot create sysfs group\n");

	/* Call back all रेजिस्टरed clients */
	cxgb3_add_clients(tdev);

out:
	/* restore them in हाल the offload module has changed them */
	अगर (err) अणु
		t3_tp_set_offload_mode(adapter, 0);
		clear_bit(OFFLOAD_DEVMAP_BIT, &adapter->खोलो_device_map);
		cxgb3_set_dummy_ops(tdev);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक offload_बंद(काष्ठा t3cdev *tdev)
अणु
	काष्ठा adapter *adapter = tdev2adap(tdev);
	काष्ठा t3c_data *td = T3C_DATA(tdev);

	अगर (!test_bit(OFFLOAD_DEVMAP_BIT, &adapter->खोलो_device_map))
		वापस 0;

	/* Call back all रेजिस्टरed clients */
	cxgb3_हटाओ_clients(tdev);

	sysfs_हटाओ_group(&tdev->lldev->dev.kobj, &offload_attr_group);

	/* Flush work scheduled जबतक releasing TIDs */
	flush_work(&td->tid_release_task);

	tdev->lldev = शून्य;
	cxgb3_set_dummy_ops(tdev);
	t3_tp_set_offload_mode(adapter, 0);
	clear_bit(OFFLOAD_DEVMAP_BIT, &adapter->खोलो_device_map);

	अगर (!adapter->खोलो_device_map)
		cxgb_करोwn(adapter, 0);

	cxgb3_offload_deactivate(adapter);
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक other_ports = adapter->खोलो_device_map & PORT_MASK;
	पूर्णांक err;

	अगर (!adapter->खोलो_device_map && (err = cxgb_up(adapter)) < 0)
		वापस err;

	set_bit(pi->port_id, &adapter->खोलो_device_map);
	अगर (is_offload(adapter) && !ofld_disable) अणु
		err = offload_खोलो(dev);
		अगर (err)
			pr_warn("Could not initialize offload capabilities\n");
	पूर्ण

	netअगर_set_real_num_tx_queues(dev, pi->nqsets);
	err = netअगर_set_real_num_rx_queues(dev, pi->nqsets);
	अगर (err)
		वापस err;
	link_start(dev);
	t3_port_पूर्णांकr_enable(adapter, pi->port_id);
	netअगर_tx_start_all_queues(dev);
	अगर (!other_ports)
		schedule_chk_task(adapter);

	cxgb3_event_notअगरy(&adapter->tdev, OFFLOAD_PORT_UP, pi->port_id);
	वापस 0;
पूर्ण

अटल पूर्णांक __cxgb_बंद(काष्ठा net_device *dev, पूर्णांक on_wq)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	
	अगर (!adapter->खोलो_device_map)
		वापस 0;

	/* Stop link fault पूर्णांकerrupts */
	t3_xgm_पूर्णांकr_disable(adapter, pi->port_id);
	t3_पढ़ो_reg(adapter, A_XGM_INT_STATUS + pi->mac.offset);

	t3_port_पूर्णांकr_disable(adapter, pi->port_id);
	netअगर_tx_stop_all_queues(dev);
	pi->phy.ops->घातer_करोwn(&pi->phy, 1);
	netअगर_carrier_off(dev);
	t3_mac_disable(&pi->mac, MAC_सूचीECTION_TX | MAC_सूचीECTION_RX);

	spin_lock_irq(&adapter->work_lock);	/* sync with update task */
	clear_bit(pi->port_id, &adapter->खोलो_device_map);
	spin_unlock_irq(&adapter->work_lock);

	अगर (!(adapter->खोलो_device_map & PORT_MASK))
		cancel_delayed_work_sync(&adapter->adap_check_task);

	अगर (!adapter->खोलो_device_map)
		cxgb_करोwn(adapter, on_wq);

	cxgb3_event_notअगरy(&adapter->tdev, OFFLOAD_PORT_DOWN, pi->port_id);
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb_बंद(काष्ठा net_device *dev)
अणु
	वापस __cxgb_बंद(dev, 0);
पूर्ण

अटल काष्ठा net_device_stats *cxgb_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा net_device_stats *ns = &dev->stats;
	स्थिर काष्ठा mac_stats *pstats;

	spin_lock(&adapter->stats_lock);
	pstats = t3_mac_update_stats(&pi->mac);
	spin_unlock(&adapter->stats_lock);

	ns->tx_bytes = pstats->tx_octets;
	ns->tx_packets = pstats->tx_frames;
	ns->rx_bytes = pstats->rx_octets;
	ns->rx_packets = pstats->rx_frames;
	ns->multicast = pstats->rx_mcast_frames;

	ns->tx_errors = pstats->tx_underrun;
	ns->rx_errors = pstats->rx_symbol_errs + pstats->rx_fcs_errs +
	    pstats->rx_too_दीर्घ + pstats->rx_jabber + pstats->rx_लघु +
	    pstats->rx_fअगरo_ovfl;

	/* detailed rx_errors */
	ns->rx_length_errors = pstats->rx_jabber + pstats->rx_too_दीर्घ;
	ns->rx_over_errors = 0;
	ns->rx_crc_errors = pstats->rx_fcs_errs;
	ns->rx_frame_errors = pstats->rx_symbol_errs;
	ns->rx_fअगरo_errors = pstats->rx_fअगरo_ovfl;
	ns->rx_missed_errors = pstats->rx_cong_drops;

	/* detailed tx_errors */
	ns->tx_पातed_errors = 0;
	ns->tx_carrier_errors = 0;
	ns->tx_fअगरo_errors = pstats->tx_underrun;
	ns->tx_heartbeat_errors = 0;
	ns->tx_winकरोw_errors = 0;
	वापस ns;
पूर्ण

अटल u32 get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	वापस adapter->msg_enable;
पूर्ण

अटल व्योम set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	adapter->msg_enable = val;
पूर्ण

अटल स्थिर अक्षर stats_strings[][ETH_GSTRING_LEN] = अणु
	"TxOctetsOK         ",
	"TxFramesOK         ",
	"TxMulticastFramesOK",
	"TxBroadcastFramesOK",
	"TxPauseFrames      ",
	"TxUnderrun         ",
	"TxExtUnderrun      ",

	"TxFrames64         ",
	"TxFrames65To127    ",
	"TxFrames128To255   ",
	"TxFrames256To511   ",
	"TxFrames512To1023  ",
	"TxFrames1024To1518 ",
	"TxFrames1519ToMax  ",

	"RxOctetsOK         ",
	"RxFramesOK         ",
	"RxMulticastFramesOK",
	"RxBroadcastFramesOK",
	"RxPauseFrames      ",
	"RxFCSErrors        ",
	"RxSymbolErrors     ",
	"RxShortErrors      ",
	"RxJabberErrors     ",
	"RxLengthErrors     ",
	"RxFIFOoverflow     ",

	"RxFrames64         ",
	"RxFrames65To127    ",
	"RxFrames128To255   ",
	"RxFrames256To511   ",
	"RxFrames512To1023  ",
	"RxFrames1024To1518 ",
	"RxFrames1519ToMax  ",

	"PhyFIFOErrors      ",
	"TSO                ",
	"VLANextractions    ",
	"VLANinsertions     ",
	"TxCsumOffload      ",
	"RxCsumGood         ",
	"LroAggregated      ",
	"LroFlushed         ",
	"LroNoDesc          ",
	"RxDrops            ",

	"CheckTXEnToggled   ",
	"CheckResets        ",

	"LinkFaults         ",
पूर्ण;

अटल पूर्णांक get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(stats_strings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

#घोषणा T3_REGMAP_SIZE (3 * 1024)

अटल पूर्णांक get_regs_len(काष्ठा net_device *dev)
अणु
	वापस T3_REGMAP_SIZE;
पूर्ण

अटल पूर्णांक get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस EEPROMSIZE;
पूर्ण

अटल व्योम get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	u32 fw_vers = 0;
	u32 tp_vers = 0;

	spin_lock(&adapter->stats_lock);
	t3_get_fw_version(adapter, &fw_vers);
	t3_get_tp_version(adapter, &tp_vers);
	spin_unlock(&adapter->stats_lock);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(adapter->pdev),
		माप(info->bus_info));
	अगर (fw_vers)
		snम_लिखो(info->fw_version, माप(info->fw_version),
			 "%s %u.%u.%u TP %u.%u.%u",
			 G_FW_VERSION_TYPE(fw_vers) ? "T" : "N",
			 G_FW_VERSION_MAJOR(fw_vers),
			 G_FW_VERSION_MINOR(fw_vers),
			 G_FW_VERSION_MICRO(fw_vers),
			 G_TP_VERSION_MAJOR(tp_vers),
			 G_TP_VERSION_MINOR(tp_vers),
			 G_TP_VERSION_MICRO(tp_vers));
पूर्ण

अटल व्योम get_strings(काष्ठा net_device *dev, u32 stringset, u8 * data)
अणु
	अगर (stringset == ETH_SS_STATS)
		स_नकल(data, stats_strings, माप(stats_strings));
पूर्ण

अटल अचिन्हित दीर्घ collect_sge_port_stats(काष्ठा adapter *adapter,
					    काष्ठा port_info *p, पूर्णांक idx)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ tot = 0;

	क्रम (i = p->first_qset; i < p->first_qset + p->nqsets; ++i)
		tot += adapter->sge.qs[i].port_stats[idx];
	वापस tot;
पूर्ण

अटल व्योम get_stats(काष्ठा net_device *dev, काष्ठा ethtool_stats *stats,
		      u64 *data)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	स्थिर काष्ठा mac_stats *s;

	spin_lock(&adapter->stats_lock);
	s = t3_mac_update_stats(&pi->mac);
	spin_unlock(&adapter->stats_lock);

	*data++ = s->tx_octets;
	*data++ = s->tx_frames;
	*data++ = s->tx_mcast_frames;
	*data++ = s->tx_bcast_frames;
	*data++ = s->tx_छोड़ो;
	*data++ = s->tx_underrun;
	*data++ = s->tx_fअगरo_urun;

	*data++ = s->tx_frames_64;
	*data++ = s->tx_frames_65_127;
	*data++ = s->tx_frames_128_255;
	*data++ = s->tx_frames_256_511;
	*data++ = s->tx_frames_512_1023;
	*data++ = s->tx_frames_1024_1518;
	*data++ = s->tx_frames_1519_max;

	*data++ = s->rx_octets;
	*data++ = s->rx_frames;
	*data++ = s->rx_mcast_frames;
	*data++ = s->rx_bcast_frames;
	*data++ = s->rx_छोड़ो;
	*data++ = s->rx_fcs_errs;
	*data++ = s->rx_symbol_errs;
	*data++ = s->rx_लघु;
	*data++ = s->rx_jabber;
	*data++ = s->rx_too_दीर्घ;
	*data++ = s->rx_fअगरo_ovfl;

	*data++ = s->rx_frames_64;
	*data++ = s->rx_frames_65_127;
	*data++ = s->rx_frames_128_255;
	*data++ = s->rx_frames_256_511;
	*data++ = s->rx_frames_512_1023;
	*data++ = s->rx_frames_1024_1518;
	*data++ = s->rx_frames_1519_max;

	*data++ = pi->phy.fअगरo_errors;

	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_TSO);
	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_VLANEX);
	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_VLANINS);
	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_TX_CSUM);
	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_RX_CSUM_GOOD);
	*data++ = 0;
	*data++ = 0;
	*data++ = 0;
	*data++ = s->rx_cong_drops;

	*data++ = s->num_toggled;
	*data++ = s->num_resets;

	*data++ = s->link_faults;
पूर्ण

अटल अंतरभूत व्योम reg_block_dump(काष्ठा adapter *ap, व्योम *buf,
				  अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	u32 *p = buf + start;

	क्रम (; start <= end; start += माप(u32))
		*p++ = t3_पढ़ो_reg(ap, start);
पूर्ण

अटल व्योम get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
		     व्योम *buf)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *ap = pi->adapter;

	/*
	 * Version scheme:
	 * bits 0..9: chip version
	 * bits 10..15: chip revision
	 * bit 31: set क्रम PCIe cards
	 */
	regs->version = 3 | (ap->params.rev << 10) | (is_pcie(ap) << 31);

	/*
	 * We skip the MAC statistics रेजिस्टरs because they are clear-on-पढ़ो.
	 * Also पढ़ोing multi-रेजिस्टर stats would need to synchronize with the
	 * periodic mac stats accumulation.  Hard to justअगरy the complनिकासy.
	 */
	स_रखो(buf, 0, T3_REGMAP_SIZE);
	reg_block_dump(ap, buf, 0, A_SG_RSPQ_CREDIT_RETURN);
	reg_block_dump(ap, buf, A_SG_HI_DRB_HI_THRSH, A_ULPRX_PBL_ULIMIT);
	reg_block_dump(ap, buf, A_ULPTX_CONFIG, A_MPS_INT_CAUSE);
	reg_block_dump(ap, buf, A_CPL_SWITCH_CNTRL, A_CPL_MAP_TBL_DATA);
	reg_block_dump(ap, buf, A_SMB_GLOBAL_TIME_CFG, A_XGM_SERDES_STAT3);
	reg_block_dump(ap, buf, A_XGM_SERDES_STATUS0,
		       XGM_REG(A_XGM_SERDES_STAT3, 1));
	reg_block_dump(ap, buf, XGM_REG(A_XGM_SERDES_STATUS0, 1),
		       XGM_REG(A_XGM_RX_SPI4_SOP_EOP_CNT, 1));
पूर्ण

अटल पूर्णांक restart_स्वतःneg(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *p = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस -EAGAIN;
	अगर (p->link_config.स्वतःneg != AUTONEG_ENABLE)
		वापस -EINVAL;
	p->phy.ops->स्वतःneg_restart(&p->phy);
	वापस 0;
पूर्ण

अटल पूर्णांक set_phys_id(काष्ठा net_device *dev,
		       क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		वापस 1;	/* cycle on/off once per second */

	हाल ETHTOOL_ID_OFF:
		t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, F_GPIO0_OUT_VAL, 0);
		अवरोध;

	हाल ETHTOOL_ID_ON:
	हाल ETHTOOL_ID_INACTIVE:
		t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, F_GPIO0_OUT_VAL,
			 F_GPIO0_OUT_VAL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_link_ksettings(काष्ठा net_device *dev,
			      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा port_info *p = netdev_priv(dev);
	u32 supported;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						p->link_config.supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						p->link_config.advertising);

	अगर (netअगर_carrier_ok(dev)) अणु
		cmd->base.speed = p->link_config.speed;
		cmd->base.duplex = p->link_config.duplex;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);

	cmd->base.port = (supported & SUPPORTED_TP) ? PORT_TP : PORT_FIBRE;
	cmd->base.phy_address = p->phy.mdio.prtad;
	cmd->base.स्वतःneg = p->link_config.स्वतःneg;
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
	काष्ठा port_info *p = netdev_priv(dev);
	काष्ठा link_config *lc = &p->link_config;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (!(lc->supported & SUPPORTED_Autoneg)) अणु
		/*
		 * PHY offers a single speed/duplex.  See अगर that's what's
		 * being requested.
		 */
		अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE) अणु
			u32 speed = cmd->base.speed;
			पूर्णांक cap = speed_duplex_to_caps(speed, cmd->base.duplex);
			अगर (lc->supported & cap)
				वापस 0;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

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
		advertising &= lc->supported;
		अगर (!advertising)
			वापस -EINVAL;
		lc->requested_speed = SPEED_INVALID;
		lc->requested_duplex = DUPLEX_INVALID;
		lc->advertising = advertising | ADVERTISED_Autoneg;
	पूर्ण
	lc->स्वतःneg = cmd->base.स्वतःneg;
	अगर (netअगर_running(dev))
		t3_link_start(&p->phy, &p->mac, lc);
	वापस 0;
पूर्ण

अटल व्योम get_छोड़ोparam(काष्ठा net_device *dev,
			   काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा port_info *p = netdev_priv(dev);

	eछोड़ो->स्वतःneg = (p->link_config.requested_fc & PAUSE_AUTONEG) != 0;
	eछोड़ो->rx_छोड़ो = (p->link_config.fc & PAUSE_RX) != 0;
	eछोड़ो->tx_छोड़ो = (p->link_config.fc & PAUSE_TX) != 0;
पूर्ण

अटल पूर्णांक set_छोड़ोparam(काष्ठा net_device *dev,
			  काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा port_info *p = netdev_priv(dev);
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
			t3_link_start(&p->phy, &p->mac, lc);
	पूर्ण अन्यथा अणु
		lc->fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);
		अगर (netअगर_running(dev))
			t3_mac_set_speed_duplex_fc(&p->mac, -1, -1, lc->fc);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम get_sge_param(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *e)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	स्थिर काष्ठा qset_params *q = &adapter->params.sge.qset[pi->first_qset];

	e->rx_max_pending = MAX_RX_BUFFERS;
	e->rx_jumbo_max_pending = MAX_RX_JUMBO_BUFFERS;
	e->tx_max_pending = MAX_TXQ_ENTRIES;

	e->rx_pending = q->fl_size;
	e->rx_mini_pending = q->rspq_size;
	e->rx_jumbo_pending = q->jumbo_size;
	e->tx_pending = q->txq_size[0];
पूर्ण

अटल पूर्णांक set_sge_param(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *e)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा qset_params *q;
	पूर्णांक i;

	अगर (e->rx_pending > MAX_RX_BUFFERS ||
	    e->rx_jumbo_pending > MAX_RX_JUMBO_BUFFERS ||
	    e->tx_pending > MAX_TXQ_ENTRIES ||
	    e->rx_mini_pending > MAX_RSPQ_ENTRIES ||
	    e->rx_mini_pending < MIN_RSPQ_ENTRIES ||
	    e->rx_pending < MIN_FL_ENTRIES ||
	    e->rx_jumbo_pending < MIN_FL_ENTRIES ||
	    e->tx_pending < adapter->params.nports * MIN_TXQ_ENTRIES)
		वापस -EINVAL;

	अगर (adapter->flags & FULL_INIT_DONE)
		वापस -EBUSY;

	q = &adapter->params.sge.qset[pi->first_qset];
	क्रम (i = 0; i < pi->nqsets; ++i, ++q) अणु
		q->rspq_size = e->rx_mini_pending;
		q->fl_size = e->rx_pending;
		q->jumbo_size = e->rx_jumbo_pending;
		q->txq_size[0] = e->tx_pending;
		q->txq_size[1] = e->tx_pending;
		q->txq_size[2] = e->tx_pending;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा qset_params *qsp;
	काष्ठा sge_qset *qs;
	पूर्णांक i;

	अगर (c->rx_coalesce_usecs * 10 > M_NEWTIMER)
		वापस -EINVAL;

	क्रम (i = 0; i < pi->nqsets; i++) अणु
		qsp = &adapter->params.sge.qset[i];
		qs = &adapter->sge.qs[i];
		qsp->coalesce_usecs = c->rx_coalesce_usecs;
		t3_update_qset_coalesce(qs, qsp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा qset_params *q = adapter->params.sge.qset;

	c->rx_coalesce_usecs = q->coalesce_usecs;
	वापस 0;
पूर्ण

अटल पूर्णांक get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *e,
		      u8 * data)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक i, err = 0;

	u8 *buf = kदो_स्मृति(EEPROMSIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	e->magic = EEPROM_MAGIC;
	क्रम (i = e->offset & ~3; !err && i < e->offset + e->len; i += 4)
		err = t3_seeprom_पढ़ो(adapter, i, (__le32 *) & buf[i]);

	अगर (!err)
		स_नकल(data, buf + e->offset, e->len);
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक set_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
		      u8 * data)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	u32 aligned_offset, aligned_len;
	__le32 *p;
	u8 *buf;
	पूर्णांक err;

	अगर (eeprom->magic != EEPROM_MAGIC)
		वापस -EINVAL;

	aligned_offset = eeprom->offset & ~3;
	aligned_len = (eeprom->len + (eeprom->offset & 3) + 3) & ~3;

	अगर (aligned_offset != eeprom->offset || aligned_len != eeprom->len) अणु
		buf = kदो_स्मृति(aligned_len, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
		err = t3_seeprom_पढ़ो(adapter, aligned_offset, (__le32 *) buf);
		अगर (!err && aligned_len > 4)
			err = t3_seeprom_पढ़ो(adapter,
					      aligned_offset + aligned_len - 4,
					      (__le32 *) & buf[aligned_len - 4]);
		अगर (err)
			जाओ out;
		स_नकल(buf + (eeprom->offset & 3), data, eeprom->len);
	पूर्ण अन्यथा
		buf = data;

	err = t3_seeprom_wp(adapter, 0);
	अगर (err)
		जाओ out;

	क्रम (p = (__le32 *) buf; !err && aligned_len; aligned_len -= 4, p++) अणु
		err = t3_seeprom_ग_लिखो(adapter, aligned_offset, *p);
		aligned_offset += 4;
	पूर्ण

	अगर (!err)
		err = t3_seeprom_wp(adapter, 1);
out:
	अगर (buf != data)
		kमुक्त(buf);
	वापस err;
पूर्ण

अटल व्योम get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	wol->supported = 0;
	wol->wolopts = 0;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops cxgb_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS,
	.get_drvinfo = get_drvinfo,
	.get_msglevel = get_msglevel,
	.set_msglevel = set_msglevel,
	.get_ringparam = get_sge_param,
	.set_ringparam = set_sge_param,
	.get_coalesce = get_coalesce,
	.set_coalesce = set_coalesce,
	.get_eeprom_len = get_eeprom_len,
	.get_eeprom = get_eeprom,
	.set_eeprom = set_eeprom,
	.get_छोड़ोparam = get_छोड़ोparam,
	.set_छोड़ोparam = set_छोड़ोparam,
	.get_link = ethtool_op_get_link,
	.get_strings = get_strings,
	.set_phys_id = set_phys_id,
	.nway_reset = restart_स्वतःneg,
	.get_sset_count = get_sset_count,
	.get_ethtool_stats = get_stats,
	.get_regs_len = get_regs_len,
	.get_regs = get_regs,
	.get_wol = get_wol,
	.get_link_ksettings = get_link_ksettings,
	.set_link_ksettings = set_link_ksettings,
पूर्ण;

अटल पूर्णांक in_range(पूर्णांक val, पूर्णांक lo, पूर्णांक hi)
अणु
	वापस val < 0 || (val <= hi && val >= lo);
पूर्ण

अटल पूर्णांक cxgb_extension_ioctl(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	u32 cmd;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, useraddr, माप(cmd)))
		वापस -EFAULT;

	चयन (cmd) अणु
	हाल CHELSIO_SET_QSET_PARAMS:अणु
		पूर्णांक i;
		काष्ठा qset_params *q;
		काष्ठा ch_qset_params t;
		पूर्णांक q1 = pi->first_qset;
		पूर्णांक nqsets = pi->nqsets;

		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (copy_from_user(&t, useraddr, माप(t)))
			वापस -EFAULT;
		अगर (t.cmd != CHELSIO_SET_QSET_PARAMS)
			वापस -EINVAL;
		अगर (t.qset_idx >= SGE_QSETS)
			वापस -EINVAL;
		अगर (!in_range(t.पूर्णांकr_lat, 0, M_NEWTIMER) ||
		    !in_range(t.cong_thres, 0, 255) ||
		    !in_range(t.txq_size[0], MIN_TXQ_ENTRIES,
			      MAX_TXQ_ENTRIES) ||
		    !in_range(t.txq_size[1], MIN_TXQ_ENTRIES,
			      MAX_TXQ_ENTRIES) ||
		    !in_range(t.txq_size[2], MIN_CTRL_TXQ_ENTRIES,
			      MAX_CTRL_TXQ_ENTRIES) ||
		    !in_range(t.fl_size[0], MIN_FL_ENTRIES,
			      MAX_RX_BUFFERS) ||
		    !in_range(t.fl_size[1], MIN_FL_ENTRIES,
			      MAX_RX_JUMBO_BUFFERS) ||
		    !in_range(t.rspq_size, MIN_RSPQ_ENTRIES,
			      MAX_RSPQ_ENTRIES))
			वापस -EINVAL;

		अगर ((adapter->flags & FULL_INIT_DONE) &&
			(t.rspq_size >= 0 || t.fl_size[0] >= 0 ||
			t.fl_size[1] >= 0 || t.txq_size[0] >= 0 ||
			t.txq_size[1] >= 0 || t.txq_size[2] >= 0 ||
			t.polling >= 0 || t.cong_thres >= 0))
			वापस -EBUSY;

		/* Allow setting of any available qset when offload enabled */
		अगर (test_bit(OFFLOAD_DEVMAP_BIT, &adapter->खोलो_device_map)) अणु
			q1 = 0;
			क्रम_each_port(adapter, i) अणु
				pi = adap2pinfo(adapter, i);
				nqsets += pi->first_qset + pi->nqsets;
			पूर्ण
		पूर्ण

		अगर (t.qset_idx < q1)
			वापस -EINVAL;
		अगर (t.qset_idx > q1 + nqsets - 1)
			वापस -EINVAL;

		q = &adapter->params.sge.qset[t.qset_idx];

		अगर (t.rspq_size >= 0)
			q->rspq_size = t.rspq_size;
		अगर (t.fl_size[0] >= 0)
			q->fl_size = t.fl_size[0];
		अगर (t.fl_size[1] >= 0)
			q->jumbo_size = t.fl_size[1];
		अगर (t.txq_size[0] >= 0)
			q->txq_size[0] = t.txq_size[0];
		अगर (t.txq_size[1] >= 0)
			q->txq_size[1] = t.txq_size[1];
		अगर (t.txq_size[2] >= 0)
			q->txq_size[2] = t.txq_size[2];
		अगर (t.cong_thres >= 0)
			q->cong_thres = t.cong_thres;
		अगर (t.पूर्णांकr_lat >= 0) अणु
			काष्ठा sge_qset *qs =
				&adapter->sge.qs[t.qset_idx];

			q->coalesce_usecs = t.पूर्णांकr_lat;
			t3_update_qset_coalesce(qs, q);
		पूर्ण
		अगर (t.polling >= 0) अणु
			अगर (adapter->flags & USING_MSIX)
				q->polling = t.polling;
			अन्यथा अणु
				/* No polling with INTx क्रम T3A */
				अगर (adapter->params.rev == 0 &&
					!(adapter->flags & USING_MSI))
					t.polling = 0;

				क्रम (i = 0; i < SGE_QSETS; i++) अणु
					q = &adapter->params.sge.
						qset[i];
					q->polling = t.polling;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (t.lro >= 0) अणु
			अगर (t.lro)
				dev->wanted_features |= NETIF_F_GRO;
			अन्यथा
				dev->wanted_features &= ~NETIF_F_GRO;
			netdev_update_features(dev);
		पूर्ण

		अवरोध;
	पूर्ण
	हाल CHELSIO_GET_QSET_PARAMS:अणु
		काष्ठा qset_params *q;
		काष्ठा ch_qset_params t;
		पूर्णांक q1 = pi->first_qset;
		पूर्णांक nqsets = pi->nqsets;
		पूर्णांक i;

		अगर (copy_from_user(&t, useraddr, माप(t)))
			वापस -EFAULT;

		अगर (t.cmd != CHELSIO_GET_QSET_PARAMS)
			वापस -EINVAL;

		/* Display qsets क्रम all ports when offload enabled */
		अगर (test_bit(OFFLOAD_DEVMAP_BIT, &adapter->खोलो_device_map)) अणु
			q1 = 0;
			क्रम_each_port(adapter, i) अणु
				pi = adap2pinfo(adapter, i);
				nqsets = pi->first_qset + pi->nqsets;
			पूर्ण
		पूर्ण

		अगर (t.qset_idx >= nqsets)
			वापस -EINVAL;
		t.qset_idx = array_index_nospec(t.qset_idx, nqsets);

		q = &adapter->params.sge.qset[q1 + t.qset_idx];
		t.rspq_size = q->rspq_size;
		t.txq_size[0] = q->txq_size[0];
		t.txq_size[1] = q->txq_size[1];
		t.txq_size[2] = q->txq_size[2];
		t.fl_size[0] = q->fl_size;
		t.fl_size[1] = q->jumbo_size;
		t.polling = q->polling;
		t.lro = !!(dev->features & NETIF_F_GRO);
		t.पूर्णांकr_lat = q->coalesce_usecs;
		t.cong_thres = q->cong_thres;
		t.qnum = q1;

		अगर (adapter->flags & USING_MSIX)
			t.vector = adapter->msix_info[q1 + t.qset_idx + 1].vec;
		अन्यथा
			t.vector = adapter->pdev->irq;

		अगर (copy_to_user(useraddr, &t, माप(t)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल CHELSIO_SET_QSET_NUM:अणु
		काष्ठा ch_reg edata;
		अचिन्हित पूर्णांक i, first_qset = 0, other_qsets = 0;

		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (adapter->flags & FULL_INIT_DONE)
			वापस -EBUSY;
		अगर (copy_from_user(&edata, useraddr, माप(edata)))
			वापस -EFAULT;
		अगर (edata.cmd != CHELSIO_SET_QSET_NUM)
			वापस -EINVAL;
		अगर (edata.val < 1 ||
			(edata.val > 1 && !(adapter->flags & USING_MSIX)))
			वापस -EINVAL;

		क्रम_each_port(adapter, i)
			अगर (adapter->port[i] && adapter->port[i] != dev)
				other_qsets += adap2pinfo(adapter, i)->nqsets;

		अगर (edata.val + other_qsets > SGE_QSETS)
			वापस -EINVAL;

		pi->nqsets = edata.val;

		क्रम_each_port(adapter, i)
			अगर (adapter->port[i]) अणु
				pi = adap2pinfo(adapter, i);
				pi->first_qset = first_qset;
				first_qset += pi->nqsets;
			पूर्ण
		अवरोध;
	पूर्ण
	हाल CHELSIO_GET_QSET_NUM:अणु
		काष्ठा ch_reg edata;

		स_रखो(&edata, 0, माप(काष्ठा ch_reg));

		edata.cmd = CHELSIO_GET_QSET_NUM;
		edata.val = pi->nqsets;
		अगर (copy_to_user(useraddr, &edata, माप(edata)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल CHELSIO_LOAD_FW:अणु
		u8 *fw_data;
		काष्ठा ch_mem_range t;

		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EPERM;
		अगर (copy_from_user(&t, useraddr, माप(t)))
			वापस -EFAULT;
		अगर (t.cmd != CHELSIO_LOAD_FW)
			वापस -EINVAL;
		/* Check t.len sanity ? */
		fw_data = memdup_user(useraddr + माप(t), t.len);
		अगर (IS_ERR(fw_data))
			वापस PTR_ERR(fw_data);

		ret = t3_load_fw(adapter, fw_data, t.len);
		kमुक्त(fw_data);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण
	हाल CHELSIO_SETMTUTAB:अणु
		काष्ठा ch_mtus m;
		पूर्णांक i;

		अगर (!is_offload(adapter))
			वापस -EOPNOTSUPP;
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (offload_running(adapter))
			वापस -EBUSY;
		अगर (copy_from_user(&m, useraddr, माप(m)))
			वापस -EFAULT;
		अगर (m.cmd != CHELSIO_SETMTUTAB)
			वापस -EINVAL;
		अगर (m.nmtus != NMTUS)
			वापस -EINVAL;
		अगर (m.mtus[0] < 81)	/* accommodate SACK */
			वापस -EINVAL;

		/* MTUs must be in ascending order */
		क्रम (i = 1; i < NMTUS; ++i)
			अगर (m.mtus[i] < m.mtus[i - 1])
				वापस -EINVAL;

		स_नकल(adapter->params.mtus, m.mtus,
			माप(adapter->params.mtus));
		अवरोध;
	पूर्ण
	हाल CHELSIO_GET_PM:अणु
		काष्ठा tp_params *p = &adapter->params.tp;
		काष्ठा ch_pm m = अणु.cmd = CHELSIO_GET_PM पूर्ण;

		अगर (!is_offload(adapter))
			वापस -EOPNOTSUPP;
		m.tx_pg_sz = p->tx_pg_size;
		m.tx_num_pg = p->tx_num_pgs;
		m.rx_pg_sz = p->rx_pg_size;
		m.rx_num_pg = p->rx_num_pgs;
		m.pm_total = p->pmtx_size + p->chan_rx_size * p->nchan;
		अगर (copy_to_user(useraddr, &m, माप(m)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल CHELSIO_SET_PM:अणु
		काष्ठा ch_pm m;
		काष्ठा tp_params *p = &adapter->params.tp;

		अगर (!is_offload(adapter))
			वापस -EOPNOTSUPP;
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (adapter->flags & FULL_INIT_DONE)
			वापस -EBUSY;
		अगर (copy_from_user(&m, useraddr, माप(m)))
			वापस -EFAULT;
		अगर (m.cmd != CHELSIO_SET_PM)
			वापस -EINVAL;
		अगर (!is_घातer_of_2(m.rx_pg_sz) ||
			!is_घातer_of_2(m.tx_pg_sz))
			वापस -EINVAL;	/* not घातer of 2 */
		अगर (!(m.rx_pg_sz & 0x14000))
			वापस -EINVAL;	/* not 16KB or 64KB */
		अगर (!(m.tx_pg_sz & 0x1554000))
			वापस -EINVAL;
		अगर (m.tx_num_pg == -1)
			m.tx_num_pg = p->tx_num_pgs;
		अगर (m.rx_num_pg == -1)
			m.rx_num_pg = p->rx_num_pgs;
		अगर (m.tx_num_pg % 24 || m.rx_num_pg % 24)
			वापस -EINVAL;
		अगर (m.rx_num_pg * m.rx_pg_sz > p->chan_rx_size ||
			m.tx_num_pg * m.tx_pg_sz > p->chan_tx_size)
			वापस -EINVAL;
		p->rx_pg_size = m.rx_pg_sz;
		p->tx_pg_size = m.tx_pg_sz;
		p->rx_num_pgs = m.rx_num_pg;
		p->tx_num_pgs = m.tx_num_pg;
		अवरोध;
	पूर्ण
	हाल CHELSIO_GET_MEM:अणु
		काष्ठा ch_mem_range t;
		काष्ठा mc7 *mem;
		u64 buf[32];

		अगर (!is_offload(adapter))
			वापस -EOPNOTSUPP;
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (!(adapter->flags & FULL_INIT_DONE))
			वापस -EIO;	/* need the memory controllers */
		अगर (copy_from_user(&t, useraddr, माप(t)))
			वापस -EFAULT;
		अगर (t.cmd != CHELSIO_GET_MEM)
			वापस -EINVAL;
		अगर ((t.addr & 7) || (t.len & 7))
			वापस -EINVAL;
		अगर (t.mem_id == MEM_CM)
			mem = &adapter->cm;
		अन्यथा अगर (t.mem_id == MEM_PMRX)
			mem = &adapter->pmrx;
		अन्यथा अगर (t.mem_id == MEM_PMTX)
			mem = &adapter->pmtx;
		अन्यथा
			वापस -EINVAL;

		/*
		 * Version scheme:
		 * bits 0..9: chip version
		 * bits 10..15: chip revision
		 */
		t.version = 3 | (adapter->params.rev << 10);
		अगर (copy_to_user(useraddr, &t, माप(t)))
			वापस -EFAULT;

		/*
		 * Read 256 bytes at a समय as len can be large and we करोn't
		 * want to use huge पूर्णांकermediate buffers.
		 */
		useraddr += माप(t);	/* advance to start of buffer */
		जबतक (t.len) अणु
			अचिन्हित पूर्णांक chunk =
				min_t(अचिन्हित पूर्णांक, t.len, माप(buf));

			ret =
				t3_mc7_bd_पढ़ो(mem, t.addr / 8, chunk / 8,
						buf);
			अगर (ret)
				वापस ret;
			अगर (copy_to_user(useraddr, buf, chunk))
				वापस -EFAULT;
			useraddr += chunk;
			t.addr += chunk;
			t.len -= chunk;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल CHELSIO_SET_TRACE_FILTER:अणु
		काष्ठा ch_trace t;
		स्थिर काष्ठा trace_params *tp;

		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (!offload_running(adapter))
			वापस -EAGAIN;
		अगर (copy_from_user(&t, useraddr, माप(t)))
			वापस -EFAULT;
		अगर (t.cmd != CHELSIO_SET_TRACE_FILTER)
			वापस -EINVAL;

		tp = (स्थिर काष्ठा trace_params *)&t.sip;
		अगर (t.config_tx)
			t3_config_trace_filter(adapter, tp, 0,
						t.invert_match,
						t.trace_tx);
		अगर (t.config_rx)
			t3_config_trace_filter(adapter, tp, 1,
						t.invert_match,
						t.trace_rx);
		अवरोध;
	पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *data = अगर_mii(req);
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	चयन (cmd) अणु
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		/* Convert phy_id from older PRTAD/DEVAD क्रमmat */
		अगर (is_10G(adapter) &&
		    !mdio_phy_id_is_c45(data->phy_id) &&
		    (data->phy_id & 0x1f00) &&
		    !(data->phy_id & 0xe0e0))
			data->phy_id = mdio_phy_id_c45(data->phy_id >> 8,
						       data->phy_id & 0x1f);
		fallthrough;
	हाल SIOCGMIIPHY:
		वापस mdio_mii_ioctl(&pi->phy.mdio, data, cmd);
	हाल SIOCCHIOCTL:
		वापस cxgb_extension_ioctl(dev, req->अगरr_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;

	अगर ((ret = t3_mac_set_mtu(&pi->mac, new_mtu)))
		वापस ret;
	dev->mtu = new_mtu;
	init_port_mtus(adapter);
	अगर (adapter->params.rev == 0 && offload_running(adapter))
		t3_load_mtus(adapter, adapter->params.mtus,
			     adapter->params.a_wnd, adapter->params.b_wnd,
			     adapter->port[0]->mtu);
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	t3_mac_set_address(&pi->mac, LAN_MAC_IDX, dev->dev_addr);
	अगर (offload_running(adapter))
		ग_लिखो_smt_entry(adapter, pi->port_id);
	वापस 0;
पूर्ण

अटल netdev_features_t cxgb_fix_features(काष्ठा net_device *dev,
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

अटल पूर्णांक cxgb_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	netdev_features_t changed = dev->features ^ features;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		cxgb_vlan_mode(dev, features);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम cxgb_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक qidx;

	क्रम (qidx = pi->first_qset; qidx < pi->first_qset + pi->nqsets; qidx++) अणु
		काष्ठा sge_qset *qs = &adapter->sge.qs[qidx];
		व्योम *source;

		अगर (adapter->flags & USING_MSIX)
			source = qs;
		अन्यथा
			source = adapter;

		t3_पूर्णांकr_handler(adapter, qs->rspq.polling) (0, source);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * Periodic accumulation of MAC statistics.
 */
अटल व्योम mac_stats_update(काष्ठा adapter *adapter)
अणु
	पूर्णांक i;

	क्रम_each_port(adapter, i) अणु
		काष्ठा net_device *dev = adapter->port[i];
		काष्ठा port_info *p = netdev_priv(dev);

		अगर (netअगर_running(dev)) अणु
			spin_lock(&adapter->stats_lock);
			t3_mac_update_stats(&p->mac);
			spin_unlock(&adapter->stats_lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम check_link_status(काष्ठा adapter *adapter)
अणु
	पूर्णांक i;

	क्रम_each_port(adapter, i) अणु
		काष्ठा net_device *dev = adapter->port[i];
		काष्ठा port_info *p = netdev_priv(dev);
		पूर्णांक link_fault;

		spin_lock_irq(&adapter->work_lock);
		link_fault = p->link_fault;
		spin_unlock_irq(&adapter->work_lock);

		अगर (link_fault) अणु
			t3_link_fault(adapter, i);
			जारी;
		पूर्ण

		अगर (!(p->phy.caps & SUPPORTED_IRQ) && netअगर_running(dev)) अणु
			t3_xgm_पूर्णांकr_disable(adapter, i);
			t3_पढ़ो_reg(adapter, A_XGM_INT_STATUS + p->mac.offset);

			t3_link_changed(adapter, i);
			t3_xgm_पूर्णांकr_enable(adapter, i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम check_t3b2_mac(काष्ठा adapter *adapter)
अणु
	पूर्णांक i;

	अगर (!rtnl_trylock())	/* synchronize with अगरकरोwn */
		वापस;

	क्रम_each_port(adapter, i) अणु
		काष्ठा net_device *dev = adapter->port[i];
		काष्ठा port_info *p = netdev_priv(dev);
		पूर्णांक status;

		अगर (!netअगर_running(dev))
			जारी;

		status = 0;
		अगर (netअगर_running(dev) && netअगर_carrier_ok(dev))
			status = t3b2_mac_watchकरोg_task(&p->mac);
		अगर (status == 1)
			p->mac.stats.num_toggled++;
		अन्यथा अगर (status == 2) अणु
			काष्ठा cmac *mac = &p->mac;

			t3_mac_set_mtu(mac, dev->mtu);
			t3_mac_set_address(mac, LAN_MAC_IDX, dev->dev_addr);
			cxgb_set_rxmode(dev);
			t3_link_start(&p->phy, mac, &p->link_config);
			t3_mac_enable(mac, MAC_सूचीECTION_RX | MAC_सूचीECTION_TX);
			t3_port_पूर्णांकr_enable(adapter, p->port_id);
			p->mac.stats.num_resets++;
		पूर्ण
	पूर्ण
	rtnl_unlock();
पूर्ण


अटल व्योम t3_adap_check_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adapter = container_of(work, काष्ठा adapter,
					       adap_check_task.work);
	स्थिर काष्ठा adapter_params *p = &adapter->params;
	पूर्णांक port;
	अचिन्हित पूर्णांक v, status, reset;

	adapter->check_task_cnt++;

	check_link_status(adapter);

	/* Accumulate MAC stats अगर needed */
	अगर (!p->linkpoll_period ||
	    (adapter->check_task_cnt * p->linkpoll_period) / 10 >=
	    p->stats_update_period) अणु
		mac_stats_update(adapter);
		adapter->check_task_cnt = 0;
	पूर्ण

	अगर (p->rev == T3_REV_B2)
		check_t3b2_mac(adapter);

	/*
	 * Scan the XGMAC's to check क्रम various conditions which we want to
	 * monitor in a periodic polling manner rather than via an पूर्णांकerrupt
	 * condition.  This is used क्रम conditions which would otherwise flood
	 * the प्रणाली with पूर्णांकerrupts and we only really need to know that the
	 * conditions are "happening" ...  For each condition we count the
	 * detection of the condition and reset it क्रम the next polling loop.
	 */
	क्रम_each_port(adapter, port) अणु
		काष्ठा cmac *mac =  &adap2pinfo(adapter, port)->mac;
		u32 cause;

		cause = t3_पढ़ो_reg(adapter, A_XGM_INT_CAUSE + mac->offset);
		reset = 0;
		अगर (cause & F_RXFIFO_OVERFLOW) अणु
			mac->stats.rx_fअगरo_ovfl++;
			reset |= F_RXFIFO_OVERFLOW;
		पूर्ण

		t3_ग_लिखो_reg(adapter, A_XGM_INT_CAUSE + mac->offset, reset);
	पूर्ण

	/*
	 * We करो the same as above क्रम FL_EMPTY पूर्णांकerrupts.
	 */
	status = t3_पढ़ो_reg(adapter, A_SG_INT_CAUSE);
	reset = 0;

	अगर (status & F_FLEMPTY) अणु
		काष्ठा sge_qset *qs = &adapter->sge.qs[0];
		पूर्णांक i = 0;

		reset |= F_FLEMPTY;

		v = (t3_पढ़ो_reg(adapter, A_SG_RSPQ_FL_STATUS) >> S_FL0EMPTY) &
		    0xffff;

		जबतक (v) अणु
			qs->fl[i].empty += (v & 1);
			अगर (i)
				qs++;
			i ^= 1;
			v >>= 1;
		पूर्ण
	पूर्ण

	t3_ग_लिखो_reg(adapter, A_SG_INT_CAUSE, reset);

	/* Schedule the next check update अगर any port is active. */
	spin_lock_irq(&adapter->work_lock);
	अगर (adapter->खोलो_device_map & PORT_MASK)
		schedule_chk_task(adapter);
	spin_unlock_irq(&adapter->work_lock);
पूर्ण

अटल व्योम db_full_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adapter = container_of(work, काष्ठा adapter,
					       db_full_task);

	cxgb3_event_notअगरy(&adapter->tdev, OFFLOAD_DB_FULL, 0);
पूर्ण

अटल व्योम db_empty_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adapter = container_of(work, काष्ठा adapter,
					       db_empty_task);

	cxgb3_event_notअगरy(&adapter->tdev, OFFLOAD_DB_EMPTY, 0);
पूर्ण

अटल व्योम db_drop_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adapter = container_of(work, काष्ठा adapter,
					       db_drop_task);
	अचिन्हित दीर्घ delay = 1000;
	अचिन्हित लघु r;

	cxgb3_event_notअगरy(&adapter->tdev, OFFLOAD_DB_DROP, 0);

	/*
	 * Sleep a जबतक beक्रमe ringing the driver qset dbs.
	 * The delay is between 1000-2023 usecs.
	 */
	get_अक्रमom_bytes(&r, 2);
	delay += r & 1023;
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_समयout(usecs_to_jअगरfies(delay));
	ring_dbs(adapter);
पूर्ण

/*
 * Processes बाह्यal (PHY) पूर्णांकerrupts in process context.
 */
अटल व्योम ext_पूर्णांकr_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adapter = container_of(work, काष्ठा adapter,
					       ext_पूर्णांकr_handler_task);
	पूर्णांक i;

	/* Disable link fault पूर्णांकerrupts */
	क्रम_each_port(adapter, i) अणु
		काष्ठा net_device *dev = adapter->port[i];
		काष्ठा port_info *p = netdev_priv(dev);

		t3_xgm_पूर्णांकr_disable(adapter, i);
		t3_पढ़ो_reg(adapter, A_XGM_INT_STATUS + p->mac.offset);
	पूर्ण

	/* Re-enable link fault पूर्णांकerrupts */
	t3_phy_पूर्णांकr_handler(adapter);

	क्रम_each_port(adapter, i)
		t3_xgm_पूर्णांकr_enable(adapter, i);

	/* Now reenable बाह्यal पूर्णांकerrupts */
	spin_lock_irq(&adapter->work_lock);
	अगर (adapter->slow_पूर्णांकr_mask) अणु
		adapter->slow_पूर्णांकr_mask |= F_T3DBG;
		t3_ग_लिखो_reg(adapter, A_PL_INT_CAUSE0, F_T3DBG);
		t3_ग_लिखो_reg(adapter, A_PL_INT_ENABLE0,
			     adapter->slow_पूर्णांकr_mask);
	पूर्ण
	spin_unlock_irq(&adapter->work_lock);
पूर्ण

/*
 * Interrupt-context handler क्रम बाह्यal (PHY) पूर्णांकerrupts.
 */
व्योम t3_os_ext_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	/*
	 * Schedule a task to handle बाह्यal पूर्णांकerrupts as they may be slow
	 * and we use a mutex to protect MDIO रेजिस्टरs.  We disable PHY
	 * पूर्णांकerrupts in the meanसमय and let the task reenable them when
	 * it's करोne.
	 */
	spin_lock(&adapter->work_lock);
	अगर (adapter->slow_पूर्णांकr_mask) अणु
		adapter->slow_पूर्णांकr_mask &= ~F_T3DBG;
		t3_ग_लिखो_reg(adapter, A_PL_INT_ENABLE0,
			     adapter->slow_पूर्णांकr_mask);
		queue_work(cxgb3_wq, &adapter->ext_पूर्णांकr_handler_task);
	पूर्ण
	spin_unlock(&adapter->work_lock);
पूर्ण

व्योम t3_os_link_fault_handler(काष्ठा adapter *adapter, पूर्णांक port_id)
अणु
	काष्ठा net_device *netdev = adapter->port[port_id];
	काष्ठा port_info *pi = netdev_priv(netdev);

	spin_lock(&adapter->work_lock);
	pi->link_fault = 1;
	spin_unlock(&adapter->work_lock);
पूर्ण

अटल पूर्णांक t3_adapter_error(काष्ठा adapter *adapter, पूर्णांक reset, पूर्णांक on_wq)
अणु
	पूर्णांक i, ret = 0;

	अगर (is_offload(adapter) &&
	    test_bit(OFFLOAD_DEVMAP_BIT, &adapter->खोलो_device_map)) अणु
		cxgb3_event_notअगरy(&adapter->tdev, OFFLOAD_STATUS_DOWN, 0);
		offload_बंद(&adapter->tdev);
	पूर्ण

	/* Stop all ports */
	क्रम_each_port(adapter, i) अणु
		काष्ठा net_device *netdev = adapter->port[i];

		अगर (netअगर_running(netdev))
			__cxgb_बंद(netdev, on_wq);
	पूर्ण

	/* Stop SGE समयrs */
	t3_stop_sge_समयrs(adapter);

	adapter->flags &= ~FULL_INIT_DONE;

	अगर (reset)
		ret = t3_reset_adapter(adapter);

	pci_disable_device(adapter->pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक t3_reenable_adapter(काष्ठा adapter *adapter)
अणु
	अगर (pci_enable_device(adapter->pdev)) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
		जाओ err;
	पूर्ण
	pci_set_master(adapter->pdev);
	pci_restore_state(adapter->pdev);
	pci_save_state(adapter->pdev);

	/* Free sge resources */
	t3_मुक्त_sge_resources(adapter);

	अगर (t3_replay_prep_adapter(adapter))
		जाओ err;

	वापस 0;
err:
	वापस -1;
पूर्ण

अटल व्योम t3_resume_ports(काष्ठा adapter *adapter)
अणु
	पूर्णांक i;

	/* Restart the ports */
	क्रम_each_port(adapter, i) अणु
		काष्ठा net_device *netdev = adapter->port[i];

		अगर (netअगर_running(netdev)) अणु
			अगर (cxgb_खोलो(netdev)) अणु
				dev_err(&adapter->pdev->dev,
					"can't bring device back up"
					" after reset\n");
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (is_offload(adapter) && !ofld_disable)
		cxgb3_event_notअगरy(&adapter->tdev, OFFLOAD_STATUS_UP, 0);
पूर्ण

/*
 * processes a fatal error.
 * Bring the ports करोwn, reset the chip, bring the ports back up.
 */
अटल व्योम fatal_error_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adapter = container_of(work, काष्ठा adapter,
					       fatal_error_handler_task);
	पूर्णांक err = 0;

	rtnl_lock();
	err = t3_adapter_error(adapter, 1, 1);
	अगर (!err)
		err = t3_reenable_adapter(adapter);
	अगर (!err)
		t3_resume_ports(adapter);

	CH_ALERT(adapter, "adapter reset %s\n", err ? "failed" : "succeeded");
	rtnl_unlock();
पूर्ण

व्योम t3_fatal_err(काष्ठा adapter *adapter)
अणु
	अचिन्हित पूर्णांक fw_status[4];

	अगर (adapter->flags & FULL_INIT_DONE) अणु
		t3_sge_stop_dma(adapter);
		t3_ग_लिखो_reg(adapter, A_XGM_TX_CTRL, 0);
		t3_ग_लिखो_reg(adapter, A_XGM_RX_CTRL, 0);
		t3_ग_लिखो_reg(adapter, XGM_REG(A_XGM_TX_CTRL, 1), 0);
		t3_ग_लिखो_reg(adapter, XGM_REG(A_XGM_RX_CTRL, 1), 0);

		spin_lock(&adapter->work_lock);
		t3_पूर्णांकr_disable(adapter);
		queue_work(cxgb3_wq, &adapter->fatal_error_handler_task);
		spin_unlock(&adapter->work_lock);
	पूर्ण
	CH_ALERT(adapter, "encountered fatal error, operation suspended\n");
	अगर (!t3_cim_ctl_blk_पढ़ो(adapter, 0xa0, 4, fw_status))
		CH_ALERT(adapter, "FW status: 0x%x, 0x%x, 0x%x, 0x%x\n",
			 fw_status[0], fw_status[1],
			 fw_status[2], fw_status[3]);
पूर्ण

/**
 * t3_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t t3_io_error_detected(काष्ठा pci_dev *pdev,
					     pci_channel_state_t state)
अणु
	काष्ठा adapter *adapter = pci_get_drvdata(pdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	t3_adapter_error(adapter, 0, 0);

	/* Request a slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * t3_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot.
 */
अटल pci_ers_result_t t3_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adapter *adapter = pci_get_drvdata(pdev);

	अगर (!t3_reenable_adapter(adapter))
		वापस PCI_ERS_RESULT_RECOVERED;

	वापस PCI_ERS_RESULT_DISCONNECT;
पूर्ण

/**
 * t3_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation.
 */
अटल व्योम t3_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adapter *adapter = pci_get_drvdata(pdev);

	CH_ALERT(adapter, "adapter recovering, PEX ERR 0x%x\n",
		 t3_पढ़ो_reg(adapter, A_PCIE_PEX_ERR));

	rtnl_lock();
	t3_resume_ports(adapter);
	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers t3_err_handler = अणु
	.error_detected = t3_io_error_detected,
	.slot_reset = t3_io_slot_reset,
	.resume = t3_io_resume,
पूर्ण;

/*
 * Set the number of qsets based on the number of CPUs and the number of ports,
 * not to exceed the number of available qsets, assuming there are enough qsets
 * per port in HW.
 */
अटल व्योम set_nqsets(काष्ठा adapter *adap)
अणु
	पूर्णांक i, j = 0;
	पूर्णांक num_cpus = netअगर_get_num_शेष_rss_queues();
	पूर्णांक hwports = adap->params.nports;
	पूर्णांक nqsets = adap->msix_nvectors - 1;

	अगर (adap->params.rev > 0 && adap->flags & USING_MSIX) अणु
		अगर (hwports == 2 &&
		    (hwports * nqsets > SGE_QSETS ||
		     num_cpus >= nqsets / hwports))
			nqsets /= hwports;
		अगर (nqsets > num_cpus)
			nqsets = num_cpus;
		अगर (nqsets < 1 || hwports == 4)
			nqsets = 1;
	पूर्ण अन्यथा
		nqsets = 1;

	क्रम_each_port(adap, i) अणु
		काष्ठा port_info *pi = adap2pinfo(adap, i);

		pi->first_qset = j;
		pi->nqsets = nqsets;
		j = pi->first_qset + nqsets;

		dev_info(&adap->pdev->dev,
			 "Port %d using %d queue sets.\n", i, nqsets);
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb_enable_msix(काष्ठा adapter *adap)
अणु
	काष्ठा msix_entry entries[SGE_QSETS + 1];
	पूर्णांक vectors;
	पूर्णांक i;

	vectors = ARRAY_SIZE(entries);
	क्रम (i = 0; i < vectors; ++i)
		entries[i].entry = i;

	vectors = pci_enable_msix_range(adap->pdev, entries,
					adap->params.nports + 1, vectors);
	अगर (vectors < 0)
		वापस vectors;

	क्रम (i = 0; i < vectors; ++i)
		adap->msix_info[i].vec = entries[i].vector;
	adap->msix_nvectors = vectors;

	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_port_info(काष्ठा adapter *adap, स्थिर काष्ठा adapter_info *ai)
अणु
	अटल स्थिर अक्षर *pci_variant[] = अणु
		"PCI", "PCI-X", "PCI-X ECC", "PCI-X 266", "PCI Express"
	पूर्ण;

	पूर्णांक i;
	अक्षर buf[80];

	अगर (is_pcie(adap))
		snम_लिखो(buf, माप(buf), "%s x%d",
			 pci_variant[adap->params.pci.variant],
			 adap->params.pci.width);
	अन्यथा
		snम_लिखो(buf, माप(buf), "%s %dMHz/%d-bit",
			 pci_variant[adap->params.pci.variant],
			 adap->params.pci.speed, adap->params.pci.width);

	क्रम_each_port(adap, i) अणु
		काष्ठा net_device *dev = adap->port[i];
		स्थिर काष्ठा port_info *pi = netdev_priv(dev);

		अगर (!test_bit(i, &adap->रेजिस्टरed_device_map))
			जारी;
		netdev_info(dev, "%s %s %sNIC (rev %d) %s%s\n",
			    ai->desc, pi->phy.desc,
			    is_offload(adap) ? "R" : "", adap->params.rev, buf,
			    (adap->flags & USING_MSIX) ? " MSI-X" :
			    (adap->flags & USING_MSI) ? " MSI" : "");
		अगर (adap->name == dev->name && adap->params.vpd.mclk)
			pr_info("%s: %uMB CM, %uMB PMTX, %uMB PMRX, S/N: %s\n",
			       adap->name, t3_mc7_size(&adap->cm) >> 20,
			       t3_mc7_size(&adap->pmtx) >> 20,
			       t3_mc7_size(&adap->pmrx) >> 20,
			       adap->params.vpd.sn);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops cxgb_netdev_ops = अणु
	.nकरो_खोलो		= cxgb_खोलो,
	.nकरो_stop		= cxgb_बंद,
	.nकरो_start_xmit		= t3_eth_xmit,
	.nकरो_get_stats		= cxgb_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= cxgb_set_rxmode,
	.nकरो_करो_ioctl		= cxgb_ioctl,
	.nकरो_change_mtu		= cxgb_change_mtu,
	.nकरो_set_mac_address	= cxgb_set_mac_addr,
	.nकरो_fix_features	= cxgb_fix_features,
	.nकरो_set_features	= cxgb_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cxgb_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल व्योम cxgb3_init_iscsi_mac(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);

	स_नकल(pi->iscsic.mac_addr, dev->dev_addr, ETH_ALEN);
	pi->iscsic.mac_addr[3] |= 0x80;
पूर्ण

#घोषणा TSO_FLAGS (NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_TSO_ECN)
#घोषणा VLAN_FEAT (NETIF_F_SG | NETIF_F_IP_CSUM | TSO_FLAGS | \
			NETIF_F_IPV6_CSUM | NETIF_F_HIGHDMA)
अटल पूर्णांक init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक i, err, pci_using_dac = 0;
	resource_माप_प्रकार mmio_start, mmio_len;
	स्थिर काष्ठा adapter_info *ai;
	काष्ठा adapter *adapter = शून्य;
	काष्ठा port_info *pi;

	अगर (!cxgb3_wq) अणु
		cxgb3_wq = create_singlethपढ़ो_workqueue(DRV_NAME);
		अगर (!cxgb3_wq) अणु
			pr_err("cannot initialize work queue\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		जाओ out;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		/* Just info, some other driver may have claimed the device. */
		dev_info(&pdev->dev, "cannot obtain PCI resources\n");
		जाओ out_disable_device;
	पूर्ण

	अगर (!pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) अणु
		pci_using_dac = 1;
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
		अगर (err) अणु
			dev_err(&pdev->dev, "unable to obtain 64-bit DMA for "
			       "coherent allocations\n");
			जाओ out_release_regions;
		पूर्ण
	पूर्ण अन्यथा अगर ((err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32))) != 0) अणु
		dev_err(&pdev->dev, "no usable DMA configuration\n");
		जाओ out_release_regions;
	पूर्ण

	pci_set_master(pdev);
	pci_save_state(pdev);

	mmio_start = pci_resource_start(pdev, 0);
	mmio_len = pci_resource_len(pdev, 0);
	ai = t3_get_adapter_info(ent->driver_data);

	adapter = kzalloc(माप(*adapter), GFP_KERNEL);
	अगर (!adapter) अणु
		err = -ENOMEM;
		जाओ out_release_regions;
	पूर्ण

	adapter->nofail_skb =
		alloc_skb(माप(काष्ठा cpl_set_tcb_field), GFP_KERNEL);
	अगर (!adapter->nofail_skb) अणु
		dev_err(&pdev->dev, "cannot allocate nofail buffer\n");
		err = -ENOMEM;
		जाओ out_मुक्त_adapter;
	पूर्ण

	adapter->regs = ioremap(mmio_start, mmio_len);
	अगर (!adapter->regs) अणु
		dev_err(&pdev->dev, "cannot map device registers\n");
		err = -ENOMEM;
		जाओ out_मुक्त_adapter_nofail;
	पूर्ण

	adapter->pdev = pdev;
	adapter->name = pci_name(pdev);
	adapter->msg_enable = dflt_msg_enable;
	adapter->mmio_len = mmio_len;

	mutex_init(&adapter->mdio_lock);
	spin_lock_init(&adapter->work_lock);
	spin_lock_init(&adapter->stats_lock);

	INIT_LIST_HEAD(&adapter->adapter_list);
	INIT_WORK(&adapter->ext_पूर्णांकr_handler_task, ext_पूर्णांकr_task);
	INIT_WORK(&adapter->fatal_error_handler_task, fatal_error_task);

	INIT_WORK(&adapter->db_full_task, db_full_task);
	INIT_WORK(&adapter->db_empty_task, db_empty_task);
	INIT_WORK(&adapter->db_drop_task, db_drop_task);

	INIT_DELAYED_WORK(&adapter->adap_check_task, t3_adap_check_task);

	क्रम (i = 0; i < ai->nports0 + ai->nports1; ++i) अणु
		काष्ठा net_device *netdev;

		netdev = alloc_etherdev_mq(माप(काष्ठा port_info), SGE_QSETS);
		अगर (!netdev) अणु
			err = -ENOMEM;
			जाओ out_मुक्त_dev;
		पूर्ण

		SET_NETDEV_DEV(netdev, &pdev->dev);

		adapter->port[i] = netdev;
		pi = netdev_priv(netdev);
		pi->adapter = adapter;
		pi->port_id = i;
		netअगर_carrier_off(netdev);
		netdev->irq = pdev->irq;
		netdev->mem_start = mmio_start;
		netdev->mem_end = mmio_start + mmio_len - 1;
		netdev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM |
			NETIF_F_TSO | NETIF_F_RXCSUM | NETIF_F_HW_VLAN_CTAG_RX;
		netdev->features |= netdev->hw_features |
				    NETIF_F_HW_VLAN_CTAG_TX;
		netdev->vlan_features |= netdev->features & VLAN_FEAT;
		अगर (pci_using_dac)
			netdev->features |= NETIF_F_HIGHDMA;

		netdev->netdev_ops = &cxgb_netdev_ops;
		netdev->ethtool_ops = &cxgb_ethtool_ops;
		netdev->min_mtu = 81;
		netdev->max_mtu = ETH_MAX_MTU;
		netdev->dev_port = pi->port_id;
	पूर्ण

	pci_set_drvdata(pdev, adapter);
	अगर (t3_prep_adapter(adapter, ai, 1) < 0) अणु
		err = -ENODEV;
		जाओ out_मुक्त_dev;
	पूर्ण

	/*
	 * The card is now पढ़ोy to go.  If any errors occur during device
	 * registration we करो not fail the whole card but rather proceed only
	 * with the ports we manage to रेजिस्टर successfully.  However we must
	 * रेजिस्टर at least one net device.
	 */
	क्रम_each_port(adapter, i) अणु
		err = रेजिस्टर_netdev(adapter->port[i]);
		अगर (err)
			dev_warn(&pdev->dev,
				 "cannot register net device %s, skipping\n",
				 adapter->port[i]->name);
		अन्यथा अणु
			/*
			 * Change the name we use क्रम messages to the name of
			 * the first successfully रेजिस्टरed पूर्णांकerface.
			 */
			अगर (!adapter->रेजिस्टरed_device_map)
				adapter->name = adapter->port[i]->name;

			__set_bit(i, &adapter->रेजिस्टरed_device_map);
		पूर्ण
	पूर्ण
	अगर (!adapter->रेजिस्टरed_device_map) अणु
		dev_err(&pdev->dev, "could not register any net devices\n");
		जाओ out_मुक्त_dev;
	पूर्ण

	क्रम_each_port(adapter, i)
		cxgb3_init_iscsi_mac(adapter->port[i]);

	/* Driver's पढ़ोy. Reflect it on LEDs */
	t3_led_पढ़ोy(adapter);

	अगर (is_offload(adapter)) अणु
		__set_bit(OFFLOAD_DEVMAP_BIT, &adapter->रेजिस्टरed_device_map);
		cxgb3_adapter_ofld(adapter);
	पूर्ण

	/* See what पूर्णांकerrupts we'll be using */
	अगर (msi > 1 && cxgb_enable_msix(adapter) == 0)
		adapter->flags |= USING_MSIX;
	अन्यथा अगर (msi > 0 && pci_enable_msi(pdev) == 0)
		adapter->flags |= USING_MSI;

	set_nqsets(adapter);

	err = sysfs_create_group(&adapter->port[0]->dev.kobj,
				 &cxgb3_attr_group);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot create sysfs group\n");
		जाओ out_बंद_led;
	पूर्ण

	prपूर्णांक_port_info(adapter, ai);
	वापस 0;

out_बंद_led:
	t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, F_GPIO0_OUT_VAL, 0);

out_मुक्त_dev:
	iounmap(adapter->regs);
	क्रम (i = ai->nports0 + ai->nports1 - 1; i >= 0; --i)
		अगर (adapter->port[i])
			मुक्त_netdev(adapter->port[i]);

out_मुक्त_adapter_nofail:
	kमुक्त_skb(adapter->nofail_skb);

out_मुक्त_adapter:
	kमुक्त(adapter);

out_release_regions:
	pci_release_regions(pdev);
out_disable_device:
	pci_disable_device(pdev);
out:
	वापस err;
पूर्ण

अटल व्योम हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adapter *adapter = pci_get_drvdata(pdev);

	अगर (adapter) अणु
		पूर्णांक i;

		t3_sge_stop(adapter);
		sysfs_हटाओ_group(&adapter->port[0]->dev.kobj,
				   &cxgb3_attr_group);

		अगर (is_offload(adapter)) अणु
			cxgb3_adapter_unofld(adapter);
			अगर (test_bit(OFFLOAD_DEVMAP_BIT,
				     &adapter->खोलो_device_map))
				offload_बंद(&adapter->tdev);
		पूर्ण

		क्रम_each_port(adapter, i)
		    अगर (test_bit(i, &adapter->रेजिस्टरed_device_map))
			unरेजिस्टर_netdev(adapter->port[i]);

		t3_stop_sge_समयrs(adapter);
		t3_मुक्त_sge_resources(adapter);
		cxgb_disable_msi(adapter);

		क्रम_each_port(adapter, i)
			अगर (adapter->port[i])
				मुक्त_netdev(adapter->port[i]);

		iounmap(adapter->regs);
		kमुक्त_skb(adapter->nofail_skb);
		kमुक्त(adapter);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
	पूर्ण
पूर्ण

अटल काष्ठा pci_driver driver = अणु
	.name = DRV_NAME,
	.id_table = cxgb3_pci_tbl,
	.probe = init_one,
	.हटाओ = हटाओ_one,
	.err_handler = &t3_err_handler,
पूर्ण;

अटल पूर्णांक __init cxgb3_init_module(व्योम)
अणु
	पूर्णांक ret;

	cxgb3_offload_init();

	ret = pci_रेजिस्टर_driver(&driver);
	वापस ret;
पूर्ण

अटल व्योम __निकास cxgb3_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&driver);
	अगर (cxgb3_wq)
		destroy_workqueue(cxgb3_wq);
पूर्ण

module_init(cxgb3_init_module);
module_निकास(cxgb3_cleanup_module);
