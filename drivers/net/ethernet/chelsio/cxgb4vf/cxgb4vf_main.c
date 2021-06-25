<शैली गुरु>
/*
 * This file is part of the Chelsio T4 PCI-E SR-IOV Virtual Function Ethernet
 * driver क्रम Linux.
 *
 * Copyright (c) 2009-2010 Chelsio Communications, Inc. All rights reserved.
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
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mdपन.स>

#समावेश "t4vf_common.h"
#समावेश "t4vf_defs.h"

#समावेश "../cxgb4/t4_regs.h"
#समावेश "../cxgb4/t4_msg.h"

/*
 * Generic inक्रमmation about the driver.
 */
#घोषणा DRV_DESC "Chelsio T4/T5/T6 Virtual Function (VF) Network Driver"

/*
 * Module Parameters.
 * ==================
 */

/*
 * Default ethtool "message level" क्रम adapters.
 */
#घोषणा DFLT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK | \
			 NETIF_MSG_TIMER | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP |\
			 NETIF_MSG_RX_ERR | NETIF_MSG_TX_ERR)

/*
 * The driver uses the best पूर्णांकerrupt scheme available on a platक्रमm in the
 * order MSI-X then MSI.  This parameter determines which of these schemes the
 * driver may consider as follows:
 *
 *     msi = 2: choose from among MSI-X and MSI
 *     msi = 1: only consider MSI पूर्णांकerrupts
 *
 * Note that unlike the Physical Function driver, this Virtual Function driver
 * करोes _not_ support legacy INTx पूर्णांकerrupts (this limitation is mandated by
 * the PCI-E SR-IOV standard).
 */
#घोषणा MSI_MSIX	2
#घोषणा MSI_MSI		1
#घोषणा MSI_DEFAULT	MSI_MSIX

अटल पूर्णांक msi = MSI_DEFAULT;

module_param(msi, पूर्णांक, 0644);
MODULE_PARM_DESC(msi, "whether to use MSI-X or MSI");

/*
 * Fundamental स्थिरants.
 * ======================
 */

क्रमागत अणु
	MAX_TXQ_ENTRIES		= 16384,
	MAX_RSPQ_ENTRIES	= 16384,
	MAX_RX_BUFFERS		= 16384,

	MIN_TXQ_ENTRIES		= 32,
	MIN_RSPQ_ENTRIES	= 128,
	MIN_FL_ENTRIES		= 16,

	/*
	 * For purposes of manipulating the Free List size we need to
	 * recognize that Free Lists are actually Egress Queues (the host
	 * produces मुक्त buffers which the hardware consumes), Egress Queues
	 * indices are all in units of Egress Context Units bytes, and मुक्त
	 * list entries are 64-bit PCI DMA addresses.  And since the state of
	 * the Producer Index == the Consumer Index implies an EMPTY list, we
	 * always have at least one Egress Unit's worth of Free List entries
	 * unused.  See sge.c क्रम more details ...
	 */
	EQ_UNIT = SGE_EQ_IDXSIZE,
	FL_PER_EQ_UNIT = EQ_UNIT / माप(__be64),
	MIN_FL_RESID = FL_PER_EQ_UNIT,
पूर्ण;

/*
 * Global driver state.
 * ====================
 */

अटल काष्ठा dentry *cxgb4vf_debugfs_root;

/*
 * OS "Callback" functions.
 * ========================
 */

/*
 * The link status has changed on the indicated "port" (Virtual Interface).
 */
व्योम t4vf_os_link_changed(काष्ठा adapter *adapter, पूर्णांक pidx, पूर्णांक link_ok)
अणु
	काष्ठा net_device *dev = adapter->port[pidx];

	/*
	 * If the port is disabled or the current recorded "link up"
	 * status matches the new status, just वापस.
	 */
	अगर (!netअगर_running(dev) || link_ok == netअगर_carrier_ok(dev))
		वापस;

	/*
	 * Tell the OS that the link status has changed and prपूर्णांक a लघु
	 * inक्रमmative message on the console about the event.
	 */
	अगर (link_ok) अणु
		स्थिर अक्षर *s;
		स्थिर अक्षर *fc;
		स्थिर काष्ठा port_info *pi = netdev_priv(dev);

		netअगर_carrier_on(dev);

		चयन (pi->link_cfg.speed) अणु
		हाल 100:
			s = "100Mbps";
			अवरोध;
		हाल 1000:
			s = "1Gbps";
			अवरोध;
		हाल 10000:
			s = "10Gbps";
			अवरोध;
		हाल 25000:
			s = "25Gbps";
			अवरोध;
		हाल 40000:
			s = "40Gbps";
			अवरोध;
		हाल 100000:
			s = "100Gbps";
			अवरोध;

		शेष:
			s = "unknown";
			अवरोध;
		पूर्ण

		चयन ((पूर्णांक)pi->link_cfg.fc) अणु
		हाल PAUSE_RX:
			fc = "RX";
			अवरोध;

		हाल PAUSE_TX:
			fc = "TX";
			अवरोध;

		हाल PAUSE_RX | PAUSE_TX:
			fc = "RX/TX";
			अवरोध;

		शेष:
			fc = "no";
			अवरोध;
		पूर्ण

		netdev_info(dev, "link up, %s, full-duplex, %s PAUSE\n", s, fc);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(dev);
		netdev_info(dev, "link down\n");
	पूर्ण
पूर्ण

/*
 * THe port module type has changed on the indicated "port" (Virtual
 * Interface).
 */
व्योम t4vf_os_porपंचांगod_changed(काष्ठा adapter *adapter, पूर्णांक pidx)
अणु
	अटल स्थिर अक्षर * स्थिर mod_str[] = अणु
		शून्य, "LR", "SR", "ER", "passive DA", "active DA", "LRM"
	पूर्ण;
	स्थिर काष्ठा net_device *dev = adapter->port[pidx];
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);

	अगर (pi->mod_type == FW_PORT_MOD_TYPE_NONE)
		dev_info(adapter->pdev_dev, "%s: port module unplugged\n",
			 dev->name);
	अन्यथा अगर (pi->mod_type < ARRAY_SIZE(mod_str))
		dev_info(adapter->pdev_dev, "%s: %s port module inserted\n",
			 dev->name, mod_str[pi->mod_type]);
	अन्यथा अगर (pi->mod_type == FW_PORT_MOD_TYPE_NOTSUPPORTED)
		dev_info(adapter->pdev_dev, "%s: unsupported optical port "
			 "module inserted\n", dev->name);
	अन्यथा अगर (pi->mod_type == FW_PORT_MOD_TYPE_UNKNOWN)
		dev_info(adapter->pdev_dev, "%s: unknown port module inserted,"
			 "forcing TWINAX\n", dev->name);
	अन्यथा अगर (pi->mod_type == FW_PORT_MOD_TYPE_ERROR)
		dev_info(adapter->pdev_dev, "%s: transceiver module error\n",
			 dev->name);
	अन्यथा
		dev_info(adapter->pdev_dev, "%s: unknown module type %d "
			 "inserted\n", dev->name, pi->mod_type);
पूर्ण

अटल पूर्णांक cxgb4vf_set_addr_hash(काष्ठा port_info *pi)
अणु
	काष्ठा adapter *adapter = pi->adapter;
	u64 vec = 0;
	bool ucast = false;
	काष्ठा hash_mac_addr *entry;

	/* Calculate the hash vector क्रम the updated list and program it */
	list_क्रम_each_entry(entry, &adapter->mac_hlist, list) अणु
		ucast |= is_unicast_ether_addr(entry->addr);
		vec |= (1ULL << hash_mac_addr(entry->addr));
	पूर्ण
	वापस t4vf_set_addr_hash(adapter, pi->viid, ucast, vec, false);
पूर्ण

/**
 *	cxgb4vf_change_mac - Update match filter क्रम a MAC address.
 *	@pi: the port_info
 *	@viid: the VI id
 *	@tcam_idx: TCAM index of existing filter क्रम old value of MAC address,
 *		   or -1
 *	@addr: the new MAC address value
 *	@persistent: whether a new MAC allocation should be persistent
 *
 *	Modअगरies an MPS filter and sets it to the new MAC address अगर
 *	@tcam_idx >= 0, or adds the MAC address to a new filter अगर
 *	@tcam_idx < 0. In the latter हाल the address is added persistently
 *	अगर @persist is %true.
 *	Addresses are programmed to hash region, अगर tcam runs out of entries.
 *
 */
अटल पूर्णांक cxgb4vf_change_mac(काष्ठा port_info *pi, अचिन्हित पूर्णांक viid,
			      पूर्णांक *tcam_idx, स्थिर u8 *addr, bool persistent)
अणु
	काष्ठा hash_mac_addr *new_entry, *entry;
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;

	ret = t4vf_change_mac(adapter, viid, *tcam_idx, addr, persistent);
	/* We ran out of TCAM entries. try programming hash region. */
	अगर (ret == -ENOMEM) अणु
		/* If the MAC address to be updated is in the hash addr
		 * list, update it from the list
		 */
		list_क्रम_each_entry(entry, &adapter->mac_hlist, list) अणु
			अगर (entry->अगरace_mac) अणु
				ether_addr_copy(entry->addr, addr);
				जाओ set_hash;
			पूर्ण
		पूर्ण
		new_entry = kzalloc(माप(*new_entry), GFP_KERNEL);
		अगर (!new_entry)
			वापस -ENOMEM;
		ether_addr_copy(new_entry->addr, addr);
		new_entry->अगरace_mac = true;
		list_add_tail(&new_entry->list, &adapter->mac_hlist);
set_hash:
		ret = cxgb4vf_set_addr_hash(pi);
	पूर्ण अन्यथा अगर (ret >= 0) अणु
		*tcam_idx = ret;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Net device operations.
 * ======================
 */




/*
 * Perक्रमm the MAC and PHY actions needed to enable a "port" (Virtual
 * Interface).
 */
अटल पूर्णांक link_start(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा port_info *pi = netdev_priv(dev);

	/*
	 * We करो not set address filters and promiscuity here, the stack करोes
	 * that step explicitly. Enable vlan accel.
	 */
	ret = t4vf_set_rxmode(pi->adapter, pi->viid, dev->mtu, -1, -1, -1, 1,
			      true);
	अगर (ret == 0)
		ret = cxgb4vf_change_mac(pi, pi->viid,
					 &pi->xact_addr_filt,
					 dev->dev_addr, true);

	/*
	 * We करोn't need to actually "start the link" itself since the
	 * firmware will करो that क्रम us when the first Virtual Interface
	 * is enabled on a port.
	 */
	अगर (ret == 0)
		ret = t4vf_enable_pi(pi->adapter, pi, true, true);

	वापस ret;
पूर्ण

/*
 * Name the MSI-X पूर्णांकerrupts.
 */
अटल व्योम name_msix_vecs(काष्ठा adapter *adapter)
अणु
	पूर्णांक namelen = माप(adapter->msix_info[0].desc) - 1;
	पूर्णांक pidx;

	/*
	 * Firmware events.
	 */
	snम_लिखो(adapter->msix_info[MSIX_FW].desc, namelen,
		 "%s-FWeventq", adapter->name);
	adapter->msix_info[MSIX_FW].desc[namelen] = 0;

	/*
	 * Ethernet queues.
	 */
	क्रम_each_port(adapter, pidx) अणु
		काष्ठा net_device *dev = adapter->port[pidx];
		स्थिर काष्ठा port_info *pi = netdev_priv(dev);
		पूर्णांक qs, msi;

		क्रम (qs = 0, msi = MSIX_IQFLINT; qs < pi->nqsets; qs++, msi++) अणु
			snम_लिखो(adapter->msix_info[msi].desc, namelen,
				 "%s-%d", dev->name, qs);
			adapter->msix_info[msi].desc[namelen] = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Request all of our MSI-X resources.
 */
अटल पूर्णांक request_msix_queue_irqs(काष्ठा adapter *adapter)
अणु
	काष्ठा sge *s = &adapter->sge;
	पूर्णांक rxq, msi, err;

	/*
	 * Firmware events.
	 */
	err = request_irq(adapter->msix_info[MSIX_FW].vec, t4vf_sge_पूर्णांकr_msix,
			  0, adapter->msix_info[MSIX_FW].desc, &s->fw_evtq);
	अगर (err)
		वापस err;

	/*
	 * Ethernet queues.
	 */
	msi = MSIX_IQFLINT;
	क्रम_each_ethrxq(s, rxq) अणु
		err = request_irq(adapter->msix_info[msi].vec,
				  t4vf_sge_पूर्णांकr_msix, 0,
				  adapter->msix_info[msi].desc,
				  &s->ethrxq[rxq].rspq);
		अगर (err)
			जाओ err_मुक्त_irqs;
		msi++;
	पूर्ण
	वापस 0;

err_मुक्त_irqs:
	जबतक (--rxq >= 0)
		मुक्त_irq(adapter->msix_info[--msi].vec, &s->ethrxq[rxq].rspq);
	मुक्त_irq(adapter->msix_info[MSIX_FW].vec, &s->fw_evtq);
	वापस err;
पूर्ण

/*
 * Free our MSI-X resources.
 */
अटल व्योम मुक्त_msix_queue_irqs(काष्ठा adapter *adapter)
अणु
	काष्ठा sge *s = &adapter->sge;
	पूर्णांक rxq, msi;

	मुक्त_irq(adapter->msix_info[MSIX_FW].vec, &s->fw_evtq);
	msi = MSIX_IQFLINT;
	क्रम_each_ethrxq(s, rxq)
		मुक्त_irq(adapter->msix_info[msi++].vec,
			 &s->ethrxq[rxq].rspq);
पूर्ण

/*
 * Turn on NAPI and start up पूर्णांकerrupts on a response queue.
 */
अटल व्योम qenable(काष्ठा sge_rspq *rspq)
अणु
	napi_enable(&rspq->napi);

	/*
	 * 0-increment the Going To Sleep रेजिस्टर to start the समयr and
	 * enable पूर्णांकerrupts.
	 */
	t4_ग_लिखो_reg(rspq->adapter, T4VF_SGE_BASE_ADDR + SGE_VF_GTS,
		     CIDXINC_V(0) |
		     SEINTARM_V(rspq->पूर्णांकr_params) |
		     INGRESSQID_V(rspq->cntxt_id));
पूर्ण

/*
 * Enable NAPI scheduling and पूर्णांकerrupt generation क्रम all Receive Queues.
 */
अटल व्योम enable_rx(काष्ठा adapter *adapter)
अणु
	पूर्णांक rxq;
	काष्ठा sge *s = &adapter->sge;

	क्रम_each_ethrxq(s, rxq)
		qenable(&s->ethrxq[rxq].rspq);
	qenable(&s->fw_evtq);

	/*
	 * The पूर्णांकerrupt queue करोesn't use NAPI so we करो the 0-increment of
	 * its Going To Sleep रेजिस्टर here to get it started.
	 */
	अगर (adapter->flags & CXGB4VF_USING_MSI)
		t4_ग_लिखो_reg(adapter, T4VF_SGE_BASE_ADDR + SGE_VF_GTS,
			     CIDXINC_V(0) |
			     SEINTARM_V(s->पूर्णांकrq.पूर्णांकr_params) |
			     INGRESSQID_V(s->पूर्णांकrq.cntxt_id));

पूर्ण

/*
 * Wait until all NAPI handlers are descheduled.
 */
अटल व्योम quiesce_rx(काष्ठा adapter *adapter)
अणु
	काष्ठा sge *s = &adapter->sge;
	पूर्णांक rxq;

	क्रम_each_ethrxq(s, rxq)
		napi_disable(&s->ethrxq[rxq].rspq.napi);
	napi_disable(&s->fw_evtq.napi);
पूर्ण

/*
 * Response queue handler क्रम the firmware event queue.
 */
अटल पूर्णांक fwevtq_handler(काष्ठा sge_rspq *rspq, स्थिर __be64 *rsp,
			  स्थिर काष्ठा pkt_gl *gl)
अणु
	/*
	 * Extract response opcode and get poपूर्णांकer to CPL message body.
	 */
	काष्ठा adapter *adapter = rspq->adapter;
	u8 opcode = ((स्थिर काष्ठा rss_header *)rsp)->opcode;
	व्योम *cpl = (व्योम *)(rsp + 1);

	चयन (opcode) अणु
	हाल CPL_FW6_MSG: अणु
		/*
		 * We've received an asynchronous message from the firmware.
		 */
		स्थिर काष्ठा cpl_fw6_msg *fw_msg = cpl;
		अगर (fw_msg->type == FW6_TYPE_CMD_RPL)
			t4vf_handle_fw_rpl(adapter, fw_msg->data);
		अवरोध;
	पूर्ण

	हाल CPL_FW4_MSG: अणु
		/* FW can send EGR_UPDATEs encapsulated in a CPL_FW4_MSG.
		 */
		स्थिर काष्ठा cpl_sge_egr_update *p = (व्योम *)(rsp + 3);
		opcode = CPL_OPCODE_G(ntohl(p->opcode_qid));
		अगर (opcode != CPL_SGE_EGR_UPDATE) अणु
			dev_err(adapter->pdev_dev, "unexpected FW4/CPL %#x on FW event queue\n"
				, opcode);
			अवरोध;
		पूर्ण
		cpl = (व्योम *)p;
	पूर्ण
		fallthrough;

	हाल CPL_SGE_EGR_UPDATE: अणु
		/*
		 * We've received an Egress Queue Status Update message.  We
		 * get these, अगर the SGE is configured to send these when the
		 * firmware passes certain poपूर्णांकs in processing our TX
		 * Ethernet Queue or अगर we make an explicit request क्रम one.
		 * We use these updates to determine when we may need to
		 * restart a TX Ethernet Queue which was stopped क्रम lack of
		 * मुक्त TX Queue Descriptors ...
		 */
		स्थिर काष्ठा cpl_sge_egr_update *p = cpl;
		अचिन्हित पूर्णांक qid = EGR_QID_G(be32_to_cpu(p->opcode_qid));
		काष्ठा sge *s = &adapter->sge;
		काष्ठा sge_txq *tq;
		काष्ठा sge_eth_txq *txq;
		अचिन्हित पूर्णांक eq_idx;

		/*
		 * Perक्रमm sanity checking on the Queue ID to make sure it
		 * really refers to one of our TX Ethernet Egress Queues which
		 * is active and matches the queue's ID.  None of these error
		 * conditions should ever happen so we may want to either make
		 * them fatal and/or conditionalized under DEBUG.
		 */
		eq_idx = EQ_IDX(s, qid);
		अगर (unlikely(eq_idx >= MAX_EGRQ)) अणु
			dev_err(adapter->pdev_dev,
				"Egress Update QID %d out of range\n", qid);
			अवरोध;
		पूर्ण
		tq = s->egr_map[eq_idx];
		अगर (unlikely(tq == शून्य)) अणु
			dev_err(adapter->pdev_dev,
				"Egress Update QID %d TXQ=NULL\n", qid);
			अवरोध;
		पूर्ण
		txq = container_of(tq, काष्ठा sge_eth_txq, q);
		अगर (unlikely(tq->असल_id != qid)) अणु
			dev_err(adapter->pdev_dev,
				"Egress Update QID %d refers to TXQ %d\n",
				qid, tq->असल_id);
			अवरोध;
		पूर्ण

		/*
		 * Restart a stopped TX Queue which has less than half of its
		 * TX ring in use ...
		 */
		txq->q.restarts++;
		netअगर_tx_wake_queue(txq->txq);
		अवरोध;
	पूर्ण

	शेष:
		dev_err(adapter->pdev_dev,
			"unexpected CPL %#x on FW event queue\n", opcode);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Allocate SGE TX/RX response queues.  Determine how many sets of SGE queues
 * to use and initializes them.  We support multiple "Queue Sets" per port अगर
 * we have MSI-X, otherwise just one queue set per port.
 */
अटल पूर्णांक setup_sge_queues(काष्ठा adapter *adapter)
अणु
	काष्ठा sge *s = &adapter->sge;
	पूर्णांक err, pidx, msix;

	/*
	 * Clear "Queue Set" Free List Starving and TX Queue Mapping Error
	 * state.
	 */
	biपंचांगap_zero(s->starving_fl, MAX_EGRQ);

	/*
	 * If we're using MSI पूर्णांकerrupt mode we need to set up a "क्रमwarded
	 * पूर्णांकerrupt" queue which we'll set up with our MSI vector.  The rest
	 * of the ingress queues will be set up to क्रमward their पूर्णांकerrupts to
	 * this queue ...  This must be first since t4vf_sge_alloc_rxq() uses
	 * the पूर्णांकrq's queue ID as the पूर्णांकerrupt क्रमwarding queue क्रम the
	 * subsequent calls ...
	 */
	अगर (adapter->flags & CXGB4VF_USING_MSI) अणु
		err = t4vf_sge_alloc_rxq(adapter, &s->पूर्णांकrq, false,
					 adapter->port[0], 0, शून्य, शून्य);
		अगर (err)
			जाओ err_मुक्त_queues;
	पूर्ण

	/*
	 * Allocate our ingress queue क्रम asynchronous firmware messages.
	 */
	err = t4vf_sge_alloc_rxq(adapter, &s->fw_evtq, true, adapter->port[0],
				 MSIX_FW, शून्य, fwevtq_handler);
	अगर (err)
		जाओ err_मुक्त_queues;

	/*
	 * Allocate each "port"'s initial Queue Sets.  These can be changed
	 * later on ... up to the poपूर्णांक where any पूर्णांकerface on the adapter is
	 * brought up at which poपूर्णांक lots of things get nailed करोwn
	 * permanently ...
	 */
	msix = MSIX_IQFLINT;
	क्रम_each_port(adapter, pidx) अणु
		काष्ठा net_device *dev = adapter->port[pidx];
		काष्ठा port_info *pi = netdev_priv(dev);
		काष्ठा sge_eth_rxq *rxq = &s->ethrxq[pi->first_qset];
		काष्ठा sge_eth_txq *txq = &s->ethtxq[pi->first_qset];
		पूर्णांक qs;

		क्रम (qs = 0; qs < pi->nqsets; qs++, rxq++, txq++) अणु
			err = t4vf_sge_alloc_rxq(adapter, &rxq->rspq, false,
						 dev, msix++,
						 &rxq->fl, t4vf_ethrx_handler);
			अगर (err)
				जाओ err_मुक्त_queues;

			err = t4vf_sge_alloc_eth_txq(adapter, txq, dev,
					     netdev_get_tx_queue(dev, qs),
					     s->fw_evtq.cntxt_id);
			अगर (err)
				जाओ err_मुक्त_queues;

			rxq->rspq.idx = qs;
			स_रखो(&rxq->stats, 0, माप(rxq->stats));
		पूर्ण
	पूर्ण

	/*
	 * Create the reverse mappings क्रम the queues.
	 */
	s->egr_base = s->ethtxq[0].q.असल_id - s->ethtxq[0].q.cntxt_id;
	s->ingr_base = s->ethrxq[0].rspq.असल_id - s->ethrxq[0].rspq.cntxt_id;
	IQ_MAP(s, s->fw_evtq.असल_id) = &s->fw_evtq;
	क्रम_each_port(adapter, pidx) अणु
		काष्ठा net_device *dev = adapter->port[pidx];
		काष्ठा port_info *pi = netdev_priv(dev);
		काष्ठा sge_eth_rxq *rxq = &s->ethrxq[pi->first_qset];
		काष्ठा sge_eth_txq *txq = &s->ethtxq[pi->first_qset];
		पूर्णांक qs;

		क्रम (qs = 0; qs < pi->nqsets; qs++, rxq++, txq++) अणु
			IQ_MAP(s, rxq->rspq.असल_id) = &rxq->rspq;
			EQ_MAP(s, txq->q.असल_id) = &txq->q;

			/*
			 * The FW_IQ_CMD करोesn't वापस the Absolute Queue IDs
			 * क्रम Free Lists but since all of the Egress Queues
			 * (including Free Lists) have Relative Queue IDs
			 * which are computed as Absolute - Base Queue ID, we
			 * can synthesize the Absolute Queue IDs क्रम the Free
			 * Lists.  This is useful क्रम debugging purposes when
			 * we want to dump Queue Contexts via the PF Driver.
			 */
			rxq->fl.असल_id = rxq->fl.cntxt_id + s->egr_base;
			EQ_MAP(s, rxq->fl.असल_id) = &rxq->fl;
		पूर्ण
	पूर्ण
	वापस 0;

err_मुक्त_queues:
	t4vf_मुक्त_sge_resources(adapter);
	वापस err;
पूर्ण

/*
 * Set up Receive Side Scaling (RSS) to distribute packets to multiple receive
 * queues.  We configure the RSS CPU lookup table to distribute to the number
 * of HW receive queues, and the response queue lookup table to narrow that
 * करोwn to the response queues actually configured क्रम each "port" (Virtual
 * Interface).  We always configure the RSS mapping क्रम all ports since the
 * mapping table has plenty of entries.
 */
अटल पूर्णांक setup_rss(काष्ठा adapter *adapter)
अणु
	पूर्णांक pidx;

	क्रम_each_port(adapter, pidx) अणु
		काष्ठा port_info *pi = adap2pinfo(adapter, pidx);
		काष्ठा sge_eth_rxq *rxq = &adapter->sge.ethrxq[pi->first_qset];
		u16 rss[MAX_PORT_QSETS];
		पूर्णांक qs, err;

		क्रम (qs = 0; qs < pi->nqsets; qs++)
			rss[qs] = rxq[qs].rspq.असल_id;

		err = t4vf_config_rss_range(adapter, pi->viid,
					    0, pi->rss_size, rss, pi->nqsets);
		अगर (err)
			वापस err;

		/*
		 * Perक्रमm Global RSS Mode-specअगरic initialization.
		 */
		चयन (adapter->params.rss.mode) अणु
		हाल FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL:
			/*
			 * If Tunnel All Lookup isn't specअगरied in the global
			 * RSS Configuration, then we need to specअगरy a
			 * शेष Ingress Queue क्रम any ingress packets which
			 * aren't hashed.  We'll use our first ingress queue
			 * ...
			 */
			अगर (!adapter->params.rss.u.basicभव.tnlalllookup) अणु
				जोड़ rss_vi_config config;
				err = t4vf_पढ़ो_rss_vi_config(adapter,
							      pi->viid,
							      &config);
				अगर (err)
					वापस err;
				config.basicभव.शेषq =
					rxq[0].rspq.असल_id;
				err = t4vf_ग_लिखो_rss_vi_config(adapter,
							       pi->viid,
							       &config);
				अगर (err)
					वापस err;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Bring the adapter up.  Called whenever we go from no "ports" खोलो to having
 * one खोलो.  This function perक्रमms the actions necessary to make an adapter
 * operational, such as completing the initialization of HW modules, and
 * enabling पूर्णांकerrupts.  Must be called with the rtnl lock held.  (Note that
 * this is called "cxgb_up" in the PF Driver.)
 */
अटल पूर्णांक adapter_up(काष्ठा adapter *adapter)
अणु
	पूर्णांक err;

	/*
	 * If this is the first समय we've been called, perक्रमm basic
	 * adapter setup.  Once we've करोne this, many of our adapter
	 * parameters can no दीर्घer be changed ...
	 */
	अगर ((adapter->flags & CXGB4VF_FULL_INIT_DONE) == 0) अणु
		err = setup_sge_queues(adapter);
		अगर (err)
			वापस err;
		err = setup_rss(adapter);
		अगर (err) अणु
			t4vf_मुक्त_sge_resources(adapter);
			वापस err;
		पूर्ण

		अगर (adapter->flags & CXGB4VF_USING_MSIX)
			name_msix_vecs(adapter);

		adapter->flags |= CXGB4VF_FULL_INIT_DONE;
	पूर्ण

	/*
	 * Acquire our पूर्णांकerrupt resources.  We only support MSI-X and MSI.
	 */
	BUG_ON((adapter->flags &
	       (CXGB4VF_USING_MSIX | CXGB4VF_USING_MSI)) == 0);
	अगर (adapter->flags & CXGB4VF_USING_MSIX)
		err = request_msix_queue_irqs(adapter);
	अन्यथा
		err = request_irq(adapter->pdev->irq,
				  t4vf_पूर्णांकr_handler(adapter), 0,
				  adapter->name, adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev, "request_irq failed, err %d\n",
			err);
		वापस err;
	पूर्ण

	/*
	 * Enable NAPI ingress processing and वापस success.
	 */
	enable_rx(adapter);
	t4vf_sge_start(adapter);

	वापस 0;
पूर्ण

/*
 * Bring the adapter करोwn.  Called whenever the last "port" (Virtual
 * Interface) बंदd.  (Note that this routine is called "cxgb_down" in the PF
 * Driver.)
 */
अटल व्योम adapter_करोwn(काष्ठा adapter *adapter)
अणु
	/*
	 * Free पूर्णांकerrupt resources.
	 */
	अगर (adapter->flags & CXGB4VF_USING_MSIX)
		मुक्त_msix_queue_irqs(adapter);
	अन्यथा
		मुक्त_irq(adapter->pdev->irq, adapter);

	/*
	 * Wait क्रम NAPI handlers to finish.
	 */
	quiesce_rx(adapter);
पूर्ण

/*
 * Start up a net device.
 */
अटल पूर्णांक cxgb4vf_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक err;
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	/*
	 * If we करोn't have a connection to the firmware there's nothing we
	 * can करो.
	 */
	अगर (!(adapter->flags & CXGB4VF_FW_OK))
		वापस -ENXIO;

	/*
	 * If this is the first पूर्णांकerface that we're खोलोing on the "adapter",
	 * bring the "adapter" up now.
	 */
	अगर (adapter->खोलो_device_map == 0) अणु
		err = adapter_up(adapter);
		अगर (err)
			वापस err;
	पूर्ण

	/* It's possible that the basic port inक्रमmation could have
	 * changed since we first पढ़ो it.
	 */
	err = t4vf_update_port_info(pi);
	अगर (err < 0)
		वापस err;

	/*
	 * Note that this पूर्णांकerface is up and start everything up ...
	 */
	err = link_start(dev);
	अगर (err)
		जाओ err_unwind;

	pi->vlan_id = t4vf_get_vf_vlan_acl(adapter);

	netअगर_tx_start_all_queues(dev);
	set_bit(pi->port_id, &adapter->खोलो_device_map);
	वापस 0;

err_unwind:
	अगर (adapter->खोलो_device_map == 0)
		adapter_करोwn(adapter);
	वापस err;
पूर्ण

/*
 * Shut करोwn a net device.  This routine is called "cxgb_close" in the PF
 * Driver ...
 */
अटल पूर्णांक cxgb4vf_stop(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	netअगर_tx_stop_all_queues(dev);
	netअगर_carrier_off(dev);
	t4vf_enable_pi(adapter, pi, false, false);

	clear_bit(pi->port_id, &adapter->खोलो_device_map);
	अगर (adapter->खोलो_device_map == 0)
		adapter_करोwn(adapter);
	वापस 0;
पूर्ण

/*
 * Translate our basic statistics पूर्णांकo the standard "ifconfig" statistics.
 */
अटल काष्ठा net_device_stats *cxgb4vf_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा t4vf_port_stats stats;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा net_device_stats *ns = &dev->stats;
	पूर्णांक err;

	spin_lock(&adapter->stats_lock);
	err = t4vf_get_port_stats(adapter, pi->pidx, &stats);
	spin_unlock(&adapter->stats_lock);

	स_रखो(ns, 0, माप(*ns));
	अगर (err)
		वापस ns;

	ns->tx_bytes = (stats.tx_bcast_bytes + stats.tx_mcast_bytes +
			stats.tx_ucast_bytes + stats.tx_offload_bytes);
	ns->tx_packets = (stats.tx_bcast_frames + stats.tx_mcast_frames +
			  stats.tx_ucast_frames + stats.tx_offload_frames);
	ns->rx_bytes = (stats.rx_bcast_bytes + stats.rx_mcast_bytes +
			stats.rx_ucast_bytes);
	ns->rx_packets = (stats.rx_bcast_frames + stats.rx_mcast_frames +
			  stats.rx_ucast_frames);
	ns->multicast = stats.rx_mcast_frames;
	ns->tx_errors = stats.tx_drop_frames;
	ns->rx_errors = stats.rx_err_frames;

	वापस ns;
पूर्ण

अटल पूर्णांक cxgb4vf_mac_sync(काष्ठा net_device *netdev, स्थिर u8 *mac_addr)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;
	u64 mhash = 0;
	u64 uhash = 0;
	bool मुक्त = false;
	bool ucast = is_unicast_ether_addr(mac_addr);
	स्थिर u8 *maclist[1] = अणुmac_addrपूर्ण;
	काष्ठा hash_mac_addr *new_entry;

	ret = t4vf_alloc_mac_filt(adapter, pi->viid, मुक्त, 1, maclist,
				  शून्य, ucast ? &uhash : &mhash, false);
	अगर (ret < 0)
		जाओ out;
	/* अगर hash != 0, then add the addr to hash addr list
	 * so on the end we will calculate the hash क्रम the
	 * list and program it
	 */
	अगर (uhash || mhash) अणु
		new_entry = kzalloc(माप(*new_entry), GFP_ATOMIC);
		अगर (!new_entry)
			वापस -ENOMEM;
		ether_addr_copy(new_entry->addr, mac_addr);
		list_add_tail(&new_entry->list, &adapter->mac_hlist);
		ret = cxgb4vf_set_addr_hash(pi);
	पूर्ण
out:
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक cxgb4vf_mac_unsync(काष्ठा net_device *netdev, स्थिर u8 *mac_addr)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;
	स्थिर u8 *maclist[1] = अणुmac_addrपूर्ण;
	काष्ठा hash_mac_addr *entry, *पंचांगp;

	/* If the MAC address to be हटाओd is in the hash addr
	 * list, delete it from the list and update hash vector
	 */
	list_क्रम_each_entry_safe(entry, पंचांगp, &adapter->mac_hlist, list) अणु
		अगर (ether_addr_equal(entry->addr, mac_addr)) अणु
			list_del(&entry->list);
			kमुक्त(entry);
			वापस cxgb4vf_set_addr_hash(pi);
		पूर्ण
	पूर्ण

	ret = t4vf_मुक्त_mac_filt(adapter, pi->viid, 1, maclist, false);
	वापस ret < 0 ? -EINVAL : 0;
पूर्ण

/*
 * Set RX properties of a port, such as promiscruity, address filters, and MTU.
 * If @mtu is -1 it is left unchanged.
 */
अटल पूर्णांक set_rxmode(काष्ठा net_device *dev, पूर्णांक mtu, bool sleep_ok)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);

	__dev_uc_sync(dev, cxgb4vf_mac_sync, cxgb4vf_mac_unsync);
	__dev_mc_sync(dev, cxgb4vf_mac_sync, cxgb4vf_mac_unsync);
	वापस t4vf_set_rxmode(pi->adapter, pi->viid, -1,
			       (dev->flags & IFF_PROMISC) != 0,
			       (dev->flags & IFF_ALLMULTI) != 0,
			       1, -1, sleep_ok);
पूर्ण

/*
 * Set the current receive modes on the device.
 */
अटल व्योम cxgb4vf_set_rxmode(काष्ठा net_device *dev)
अणु
	/* unक्रमtunately we can't वापस errors to the stack */
	set_rxmode(dev, -1, false);
पूर्ण

/*
 * Find the entry in the पूर्णांकerrupt holकरोff समयr value array which comes
 * बंदst to the specअगरied पूर्णांकerrupt holकरोff value.
 */
अटल पूर्णांक बंदst_समयr(स्थिर काष्ठा sge *s, पूर्णांक us)
अणु
	पूर्णांक i, समयr_idx = 0, min_delta = पूर्णांक_उच्च;

	क्रम (i = 0; i < ARRAY_SIZE(s->समयr_val); i++) अणु
		पूर्णांक delta = us - s->समयr_val[i];
		अगर (delta < 0)
			delta = -delta;
		अगर (delta < min_delta) अणु
			min_delta = delta;
			समयr_idx = i;
		पूर्ण
	पूर्ण
	वापस समयr_idx;
पूर्ण

अटल पूर्णांक बंदst_thres(स्थिर काष्ठा sge *s, पूर्णांक thres)
अणु
	पूर्णांक i, delta, pktcnt_idx = 0, min_delta = पूर्णांक_उच्च;

	क्रम (i = 0; i < ARRAY_SIZE(s->counter_val); i++) अणु
		delta = thres - s->counter_val[i];
		अगर (delta < 0)
			delta = -delta;
		अगर (delta < min_delta) अणु
			min_delta = delta;
			pktcnt_idx = i;
		पूर्ण
	पूर्ण
	वापस pktcnt_idx;
पूर्ण

/*
 * Return a queue's पूर्णांकerrupt hold-off समय in us.  0 means no समयr.
 */
अटल अचिन्हित पूर्णांक qसमयr_val(स्थिर काष्ठा adapter *adapter,
			       स्थिर काष्ठा sge_rspq *rspq)
अणु
	अचिन्हित पूर्णांक समयr_idx = QINTR_TIMER_IDX_G(rspq->पूर्णांकr_params);

	वापस समयr_idx < SGE_NTIMERS
		? adapter->sge.समयr_val[समयr_idx]
		: 0;
पूर्ण

/**
 *	set_rxq_पूर्णांकr_params - set a queue's पूर्णांकerrupt holकरोff parameters
 *	@adapter: the adapter
 *	@rspq: the RX response queue
 *	@us: the hold-off समय in us, or 0 to disable समयr
 *	@cnt: the hold-off packet count, or 0 to disable counter
 *
 *	Sets an RX response queue's पूर्णांकerrupt hold-off समय and packet count.
 *	At least one of the two needs to be enabled क्रम the queue to generate
 *	पूर्णांकerrupts.
 */
अटल पूर्णांक set_rxq_पूर्णांकr_params(काष्ठा adapter *adapter, काष्ठा sge_rspq *rspq,
			       अचिन्हित पूर्णांक us, अचिन्हित पूर्णांक cnt)
अणु
	अचिन्हित पूर्णांक समयr_idx;

	/*
	 * If both the पूर्णांकerrupt holकरोff समयr and count are specअगरied as
	 * zero, शेष to a holकरोff count of 1 ...
	 */
	अगर ((us | cnt) == 0)
		cnt = 1;

	/*
	 * If an पूर्णांकerrupt holकरोff count has been specअगरied, then find the
	 * बंदst configured holकरोff count and use that.  If the response
	 * queue has alपढ़ोy been created, then update its queue context
	 * parameters ...
	 */
	अगर (cnt) अणु
		पूर्णांक err;
		u32 v, pktcnt_idx;

		pktcnt_idx = बंदst_thres(&adapter->sge, cnt);
		अगर (rspq->desc && rspq->pktcnt_idx != pktcnt_idx) अणु
			v = FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
			    FW_PARAMS_PARAM_X_V(
					FW_PARAMS_PARAM_DMAQ_IQ_INTCNTTHRESH) |
			    FW_PARAMS_PARAM_YZ_V(rspq->cntxt_id);
			err = t4vf_set_params(adapter, 1, &v, &pktcnt_idx);
			अगर (err)
				वापस err;
		पूर्ण
		rspq->pktcnt_idx = pktcnt_idx;
	पूर्ण

	/*
	 * Compute the बंदst holकरोff समयr index from the supplied holकरोff
	 * समयr value.
	 */
	समयr_idx = (us == 0
		     ? SGE_TIMER_RSTRT_CNTR
		     : बंदst_समयr(&adapter->sge, us));

	/*
	 * Update the response queue's पूर्णांकerrupt coalescing parameters and
	 * वापस success.
	 */
	rspq->पूर्णांकr_params = (QINTR_TIMER_IDX_V(समयr_idx) |
			     QINTR_CNT_EN_V(cnt > 0));
	वापस 0;
पूर्ण

/*
 * Return a version number to identअगरy the type of adapter.  The scheme is:
 * - bits 0..9: chip version
 * - bits 10..15: chip revision
 */
अटल अंतरभूत अचिन्हित पूर्णांक mk_adap_vers(स्थिर काष्ठा adapter *adapter)
अणु
	/*
	 * Chip version 4, revision 0x3f (cxgb4vf).
	 */
	वापस CHELSIO_CHIP_VERSION(adapter->params.chip) | (0x3f << 10);
पूर्ण

/*
 * Execute the specअगरied ioctl command.
 */
अटल पूर्णांक cxgb4vf_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	    /*
	     * The VF Driver करोesn't have access to any of the other
	     * common Ethernet device ioctl()'s (like पढ़ोing/writing
	     * PHY रेजिस्टरs, etc.
	     */

	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Change the device's MTU.
 */
अटल पूर्णांक cxgb4vf_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	पूर्णांक ret;
	काष्ठा port_info *pi = netdev_priv(dev);

	ret = t4vf_set_rxmode(pi->adapter, pi->viid, new_mtu,
			      -1, -1, -1, -1, true);
	अगर (!ret)
		dev->mtu = new_mtu;
	वापस ret;
पूर्ण

अटल netdev_features_t cxgb4vf_fix_features(काष्ठा net_device *dev,
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

अटल पूर्णांक cxgb4vf_set_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	netdev_features_t changed = dev->features ^ features;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		t4vf_set_rxmode(pi->adapter, pi->viid, -1, -1, -1, -1,
				features & NETIF_F_HW_VLAN_CTAG_TX, 0);

	वापस 0;
पूर्ण

/*
 * Change the devices MAC address.
 */
अटल पूर्णांक cxgb4vf_set_mac_addr(काष्ठा net_device *dev, व्योम *_addr)
अणु
	पूर्णांक ret;
	काष्ठा sockaddr *addr = _addr;
	काष्ठा port_info *pi = netdev_priv(dev);

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	ret = cxgb4vf_change_mac(pi, pi->viid, &pi->xact_addr_filt,
				 addr->sa_data, true);
	अगर (ret < 0)
		वापस ret;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Poll all of our receive queues.  This is called outside of normal पूर्णांकerrupt
 * context.
 */
अटल व्योम cxgb4vf_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	अगर (adapter->flags & CXGB4VF_USING_MSIX) अणु
		काष्ठा sge_eth_rxq *rxq;
		पूर्णांक nqsets;

		rxq = &adapter->sge.ethrxq[pi->first_qset];
		क्रम (nqsets = pi->nqsets; nqsets; nqsets--) अणु
			t4vf_sge_पूर्णांकr_msix(0, &rxq->rspq);
			rxq++;
		पूर्ण
	पूर्ण अन्यथा
		t4vf_पूर्णांकr_handler(adapter)(0, adapter);
पूर्ण
#पूर्ण_अगर

/*
 * Ethtool operations.
 * ===================
 *
 * Note that we करोn't support any ethtool operations which change the physical
 * state of the port to which we're linked.
 */

/**
 *	from_fw_port_mod_type - translate Firmware Port/Module type to Ethtool
 *	@port_type: Firmware Port Type
 *	@mod_type: Firmware Module Type
 *
 *	Translate Firmware Port/Module type to Ethtool Port Type.
 */
अटल पूर्णांक from_fw_port_mod_type(क्रमागत fw_port_type port_type,
				 क्रमागत fw_port_module_type mod_type)
अणु
	अगर (port_type == FW_PORT_TYPE_BT_SGMII ||
	    port_type == FW_PORT_TYPE_BT_XFI ||
	    port_type == FW_PORT_TYPE_BT_XAUI) अणु
		वापस PORT_TP;
	पूर्ण अन्यथा अगर (port_type == FW_PORT_TYPE_FIBER_XFI ||
		   port_type == FW_PORT_TYPE_FIBER_XAUI) अणु
		वापस PORT_FIBRE;
	पूर्ण अन्यथा अगर (port_type == FW_PORT_TYPE_SFP ||
		   port_type == FW_PORT_TYPE_QSFP_10G ||
		   port_type == FW_PORT_TYPE_QSA ||
		   port_type == FW_PORT_TYPE_QSFP ||
		   port_type == FW_PORT_TYPE_CR4_QSFP ||
		   port_type == FW_PORT_TYPE_CR_QSFP ||
		   port_type == FW_PORT_TYPE_CR2_QSFP ||
		   port_type == FW_PORT_TYPE_SFP28) अणु
		अगर (mod_type == FW_PORT_MOD_TYPE_LR ||
		    mod_type == FW_PORT_MOD_TYPE_SR ||
		    mod_type == FW_PORT_MOD_TYPE_ER ||
		    mod_type == FW_PORT_MOD_TYPE_LRM)
			वापस PORT_FIBRE;
		अन्यथा अगर (mod_type == FW_PORT_MOD_TYPE_TWINAX_PASSIVE ||
			 mod_type == FW_PORT_MOD_TYPE_TWINAX_ACTIVE)
			वापस PORT_DA;
		अन्यथा
			वापस PORT_OTHER;
	पूर्ण अन्यथा अगर (port_type == FW_PORT_TYPE_KR4_100G ||
		   port_type == FW_PORT_TYPE_KR_SFP28 ||
		   port_type == FW_PORT_TYPE_KR_XLAUI) अणु
		वापस PORT_NONE;
	पूर्ण

	वापस PORT_OTHER;
पूर्ण

/**
 *	fw_caps_to_lmm - translate Firmware to ethtool Link Mode Mask
 *	@port_type: Firmware Port Type
 *	@fw_caps: Firmware Port Capabilities
 *	@link_mode_mask: ethtool Link Mode Mask
 *
 *	Translate a Firmware Port Capabilities specअगरication to an ethtool
 *	Link Mode Mask.
 */
अटल व्योम fw_caps_to_lmm(क्रमागत fw_port_type port_type,
			   अचिन्हित पूर्णांक fw_caps,
			   अचिन्हित दीर्घ *link_mode_mask)
अणु
	#घोषणा SET_LMM(__lmm_name) \
		__set_bit(ETHTOOL_LINK_MODE_ ## __lmm_name ## _BIT, \
			  link_mode_mask)

	#घोषणा FW_CAPS_TO_LMM(__fw_name, __lmm_name) \
		करो अणु \
			अगर (fw_caps & FW_PORT_CAP32_ ## __fw_name) \
				SET_LMM(__lmm_name); \
		पूर्ण जबतक (0)

	चयन (port_type) अणु
	हाल FW_PORT_TYPE_BT_SGMII:
	हाल FW_PORT_TYPE_BT_XFI:
	हाल FW_PORT_TYPE_BT_XAUI:
		SET_LMM(TP);
		FW_CAPS_TO_LMM(SPEED_100M, 100baseT_Full);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KX4:
	हाल FW_PORT_TYPE_KX:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKX4_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KR:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		अवरोध;

	हाल FW_PORT_TYPE_BP_AP:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseR_FEC);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		अवरोध;

	हाल FW_PORT_TYPE_BP4_AP:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseR_FEC);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKX4_Full);
		अवरोध;

	हाल FW_PORT_TYPE_FIBER_XFI:
	हाल FW_PORT_TYPE_FIBER_XAUI:
	हाल FW_PORT_TYPE_SFP:
	हाल FW_PORT_TYPE_QSFP_10G:
	हाल FW_PORT_TYPE_QSA:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		अवरोध;

	हाल FW_PORT_TYPE_BP40_BA:
	हाल FW_PORT_TYPE_QSFP:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_40G, 40000baseSR4_Full);
		अवरोध;

	हाल FW_PORT_TYPE_CR_QSFP:
	हाल FW_PORT_TYPE_SFP28:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_25G, 25000baseCR_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KR_SFP28:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_25G, 25000baseKR_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KR_XLAUI:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_40G, 40000baseKR4_Full);
		अवरोध;

	हाल FW_PORT_TYPE_CR2_QSFP:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_50G, 50000baseSR2_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KR4_100G:
	हाल FW_PORT_TYPE_CR4_QSFP:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G,  1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_40G, 40000baseSR4_Full);
		FW_CAPS_TO_LMM(SPEED_25G, 25000baseCR_Full);
		FW_CAPS_TO_LMM(SPEED_50G, 50000baseCR2_Full);
		FW_CAPS_TO_LMM(SPEED_100G, 100000baseCR4_Full);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (fw_caps & FW_PORT_CAP32_FEC_V(FW_PORT_CAP32_FEC_M)) अणु
		FW_CAPS_TO_LMM(FEC_RS, FEC_RS);
		FW_CAPS_TO_LMM(FEC_BASER_RS, FEC_BASER);
	पूर्ण अन्यथा अणु
		SET_LMM(FEC_NONE);
	पूर्ण

	FW_CAPS_TO_LMM(ANEG, Autoneg);
	FW_CAPS_TO_LMM(802_3_PAUSE, Pause);
	FW_CAPS_TO_LMM(802_3_ASM_सूची, Asym_Pause);

	#अघोषित FW_CAPS_TO_LMM
	#अघोषित SET_LMM
पूर्ण

अटल पूर्णांक cxgb4vf_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा ethtool_link_settings *base = &link_ksettings->base;

	/* For the nonce, the Firmware करोesn't send up Port State changes
	 * when the Virtual Interface attached to the Port is करोwn.  So
	 * अगर it's down, let's grab any changes.
	 */
	अगर (!netअगर_running(dev))
		(व्योम)t4vf_update_port_info(pi);

	ethtool_link_ksettings_zero_link_mode(link_ksettings, supported);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, advertising);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, lp_advertising);

	base->port = from_fw_port_mod_type(pi->port_type, pi->mod_type);

	अगर (pi->mdio_addr >= 0) अणु
		base->phy_address = pi->mdio_addr;
		base->mdio_support = (pi->port_type == FW_PORT_TYPE_BT_SGMII
				      ? ETH_MDIO_SUPPORTS_C22
				      : ETH_MDIO_SUPPORTS_C45);
	पूर्ण अन्यथा अणु
		base->phy_address = 255;
		base->mdio_support = 0;
	पूर्ण

	fw_caps_to_lmm(pi->port_type, pi->link_cfg.pcaps,
		       link_ksettings->link_modes.supported);
	fw_caps_to_lmm(pi->port_type, pi->link_cfg.acaps,
		       link_ksettings->link_modes.advertising);
	fw_caps_to_lmm(pi->port_type, pi->link_cfg.lpacaps,
		       link_ksettings->link_modes.lp_advertising);

	अगर (netअगर_carrier_ok(dev)) अणु
		base->speed = pi->link_cfg.speed;
		base->duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		base->speed = SPEED_UNKNOWN;
		base->duplex = DUPLEX_UNKNOWN;
	पूर्ण

	base->स्वतःneg = pi->link_cfg.स्वतःneg;
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_ANEG)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Autoneg);
	अगर (pi->link_cfg.स्वतःneg)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Autoneg);

	वापस 0;
पूर्ण

/* Translate the Firmware FEC value पूर्णांकo the ethtool value. */
अटल अंतरभूत अचिन्हित पूर्णांक fwcap_to_eth_fec(अचिन्हित पूर्णांक fw_fec)
अणु
	अचिन्हित पूर्णांक eth_fec = 0;

	अगर (fw_fec & FW_PORT_CAP32_FEC_RS)
		eth_fec |= ETHTOOL_FEC_RS;
	अगर (fw_fec & FW_PORT_CAP32_FEC_BASER_RS)
		eth_fec |= ETHTOOL_FEC_BASER;

	/* अगर nothing is set, then FEC is off */
	अगर (!eth_fec)
		eth_fec = ETHTOOL_FEC_OFF;

	वापस eth_fec;
पूर्ण

/* Translate Common Code FEC value पूर्णांकo ethtool value. */
अटल अंतरभूत अचिन्हित पूर्णांक cc_to_eth_fec(अचिन्हित पूर्णांक cc_fec)
अणु
	अचिन्हित पूर्णांक eth_fec = 0;

	अगर (cc_fec & FEC_AUTO)
		eth_fec |= ETHTOOL_FEC_AUTO;
	अगर (cc_fec & FEC_RS)
		eth_fec |= ETHTOOL_FEC_RS;
	अगर (cc_fec & FEC_BASER_RS)
		eth_fec |= ETHTOOL_FEC_BASER;

	/* अगर nothing is set, then FEC is off */
	अगर (!eth_fec)
		eth_fec = ETHTOOL_FEC_OFF;

	वापस eth_fec;
पूर्ण

अटल पूर्णांक cxgb4vf_get_fecparam(काष्ठा net_device *dev,
				काष्ठा ethtool_fecparam *fec)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	स्थिर काष्ठा link_config *lc = &pi->link_cfg;

	/* Translate the Firmware FEC Support पूर्णांकo the ethtool value.  We
	 * always support IEEE 802.3 "automatic" selection of Link FEC type अगर
	 * any FEC is supported.
	 */
	fec->fec = fwcap_to_eth_fec(lc->pcaps);
	अगर (fec->fec != ETHTOOL_FEC_OFF)
		fec->fec |= ETHTOOL_FEC_AUTO;

	/* Translate the current पूर्णांकernal FEC parameters पूर्णांकo the
	 * ethtool values.
	 */
	fec->active_fec = cc_to_eth_fec(lc->fec);
	वापस 0;
पूर्ण

/*
 * Return our driver inक्रमmation.
 */
अटल व्योम cxgb4vf_get_drvinfo(काष्ठा net_device *dev,
				काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);

	strlcpy(drvinfo->driver, KBUILD_MODNAME, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, pci_name(to_pci_dev(dev->dev.parent)),
		माप(drvinfo->bus_info));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%u.%u.%u.%u, TP %u.%u.%u.%u",
		 FW_HDR_FW_VER_MAJOR_G(adapter->params.dev.fwrev),
		 FW_HDR_FW_VER_MINOR_G(adapter->params.dev.fwrev),
		 FW_HDR_FW_VER_MICRO_G(adapter->params.dev.fwrev),
		 FW_HDR_FW_VER_BUILD_G(adapter->params.dev.fwrev),
		 FW_HDR_FW_VER_MAJOR_G(adapter->params.dev.tprev),
		 FW_HDR_FW_VER_MINOR_G(adapter->params.dev.tprev),
		 FW_HDR_FW_VER_MICRO_G(adapter->params.dev.tprev),
		 FW_HDR_FW_VER_BUILD_G(adapter->params.dev.tprev));
पूर्ण

/*
 * Return current adapter message level.
 */
अटल u32 cxgb4vf_get_msglevel(काष्ठा net_device *dev)
अणु
	वापस netdev2adap(dev)->msg_enable;
पूर्ण

/*
 * Set current adapter message level.
 */
अटल व्योम cxgb4vf_set_msglevel(काष्ठा net_device *dev, u32 msglevel)
अणु
	netdev2adap(dev)->msg_enable = msglevel;
पूर्ण

/*
 * Return the device's current Queue Set ring size parameters aदीर्घ with the
 * allowed maximum values.  Since ethtool करोesn't understand the concept of
 * multi-queue devices, we just वापस the current values associated with the
 * first Queue Set.
 */
अटल व्योम cxgb4vf_get_ringparam(काष्ठा net_device *dev,
				  काष्ठा ethtool_ringparam *rp)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	स्थिर काष्ठा sge *s = &pi->adapter->sge;

	rp->rx_max_pending = MAX_RX_BUFFERS;
	rp->rx_mini_max_pending = MAX_RSPQ_ENTRIES;
	rp->rx_jumbo_max_pending = 0;
	rp->tx_max_pending = MAX_TXQ_ENTRIES;

	rp->rx_pending = s->ethrxq[pi->first_qset].fl.size - MIN_FL_RESID;
	rp->rx_mini_pending = s->ethrxq[pi->first_qset].rspq.size;
	rp->rx_jumbo_pending = 0;
	rp->tx_pending = s->ethtxq[pi->first_qset].q.size;
पूर्ण

/*
 * Set the Queue Set ring size parameters क्रम the device.  Again, since
 * ethtool करोesn't allow for the concept of multiple queues per device, we'll
 * apply these new values across all of the Queue Sets associated with the
 * device -- after vetting them of course!
 */
अटल पूर्णांक cxgb4vf_set_ringparam(काष्ठा net_device *dev,
				 काष्ठा ethtool_ringparam *rp)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा sge *s = &adapter->sge;
	पूर्णांक qs;

	अगर (rp->rx_pending > MAX_RX_BUFFERS ||
	    rp->rx_jumbo_pending ||
	    rp->tx_pending > MAX_TXQ_ENTRIES ||
	    rp->rx_mini_pending > MAX_RSPQ_ENTRIES ||
	    rp->rx_mini_pending < MIN_RSPQ_ENTRIES ||
	    rp->rx_pending < MIN_FL_ENTRIES ||
	    rp->tx_pending < MIN_TXQ_ENTRIES)
		वापस -EINVAL;

	अगर (adapter->flags & CXGB4VF_FULL_INIT_DONE)
		वापस -EBUSY;

	क्रम (qs = pi->first_qset; qs < pi->first_qset + pi->nqsets; qs++) अणु
		s->ethrxq[qs].fl.size = rp->rx_pending + MIN_FL_RESID;
		s->ethrxq[qs].rspq.size = rp->rx_mini_pending;
		s->ethtxq[qs].q.size = rp->tx_pending;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return the पूर्णांकerrupt holकरोff समयr and count क्रम the first Queue Set on the
 * device.  Our extension ioctl() (the cxgbtool पूर्णांकerface) allows the
 * पूर्णांकerrupt holकरोff समयr to be पढ़ो on all of the device's Queue Sets.
 */
अटल पूर्णांक cxgb4vf_get_coalesce(काष्ठा net_device *dev,
				काष्ठा ethtool_coalesce *coalesce)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	स्थिर काष्ठा adapter *adapter = pi->adapter;
	स्थिर काष्ठा sge_rspq *rspq = &adapter->sge.ethrxq[pi->first_qset].rspq;

	coalesce->rx_coalesce_usecs = qसमयr_val(adapter, rspq);
	coalesce->rx_max_coalesced_frames =
		((rspq->पूर्णांकr_params & QINTR_CNT_EN_F)
		 ? adapter->sge.counter_val[rspq->pktcnt_idx]
		 : 0);
	वापस 0;
पूर्ण

/*
 * Set the RX पूर्णांकerrupt holकरोff समयr and count क्रम the first Queue Set on the
 * पूर्णांकerface.  Our extension ioctl() (the cxgbtool पूर्णांकerface) allows us to set
 * the पूर्णांकerrupt holकरोff समयr on any of the device's Queue Sets.
 */
अटल पूर्णांक cxgb4vf_set_coalesce(काष्ठा net_device *dev,
				काष्ठा ethtool_coalesce *coalesce)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	वापस set_rxq_पूर्णांकr_params(adapter,
				   &adapter->sge.ethrxq[pi->first_qset].rspq,
				   coalesce->rx_coalesce_usecs,
				   coalesce->rx_max_coalesced_frames);
पूर्ण

/*
 * Report current port link छोड़ो parameter settings.
 */
अटल व्योम cxgb4vf_get_छोड़ोparam(काष्ठा net_device *dev,
				   काष्ठा ethtool_छोड़ोparam *छोड़ोparam)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);

	छोड़ोparam->स्वतःneg = (pi->link_cfg.requested_fc & PAUSE_AUTONEG) != 0;
	छोड़ोparam->rx_छोड़ो = (pi->link_cfg.advertised_fc & PAUSE_RX) != 0;
	छोड़ोparam->tx_छोड़ो = (pi->link_cfg.advertised_fc & PAUSE_TX) != 0;
पूर्ण

/*
 * Identअगरy the port by blinking the port's LED.
 */
अटल पूर्णांक cxgb4vf_phys_id(काष्ठा net_device *dev,
			   क्रमागत ethtool_phys_id_state state)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा port_info *pi = netdev_priv(dev);

	अगर (state == ETHTOOL_ID_ACTIVE)
		val = 0xffff;
	अन्यथा अगर (state == ETHTOOL_ID_INACTIVE)
		val = 0;
	अन्यथा
		वापस -EINVAL;

	वापस t4vf_identअगरy_port(pi->adapter, pi->viid, val);
पूर्ण

/*
 * Port stats मुख्यtained per queue of the port.
 */
काष्ठा queue_port_stats अणु
	u64 tso;
	u64 tx_csum;
	u64 rx_csum;
	u64 vlan_ex;
	u64 vlan_ins;
	u64 lro_pkts;
	u64 lro_merged;
पूर्ण;

/*
 * Strings क्रम the ETH_SS_STATS statistics set ("ethtool -S").  Note that
 * these need to match the order of statistics वापसed by
 * t4vf_get_port_stats().
 */
अटल स्थिर अक्षर stats_strings[][ETH_GSTRING_LEN] = अणु
	/*
	 * These must match the layout of the t4vf_port_stats काष्ठाure.
	 */
	"TxBroadcastBytes  ",
	"TxBroadcastFrames ",
	"TxMulticastBytes  ",
	"TxMulticastFrames ",
	"TxUnicastBytes    ",
	"TxUnicastFrames   ",
	"TxDroppedFrames   ",
	"TxOffloadBytes    ",
	"TxOffloadFrames   ",
	"RxBroadcastBytes  ",
	"RxBroadcastFrames ",
	"RxMulticastBytes  ",
	"RxMulticastFrames ",
	"RxUnicastBytes    ",
	"RxUnicastFrames   ",
	"RxErrorFrames     ",

	/*
	 * These are accumulated per-queue statistics and must match the
	 * order of the fields in the queue_port_stats काष्ठाure.
	 */
	"TSO               ",
	"TxCsumOffload     ",
	"RxCsumGood        ",
	"VLANextractions   ",
	"VLANinsertions    ",
	"GROPackets        ",
	"GROMerged         ",
पूर्ण;

/*
 * Return the number of statistics in the specअगरied statistics set.
 */
अटल पूर्णांक cxgb4vf_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(stats_strings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	/*NOTREACHED*/
पूर्ण

/*
 * Return the strings क्रम the specअगरied statistics set.
 */
अटल व्योम cxgb4vf_get_strings(काष्ठा net_device *dev,
				u32 sset,
				u8 *data)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, stats_strings, माप(stats_strings));
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Small utility routine to accumulate queue statistics across the queues of
 * a "port".
 */
अटल व्योम collect_sge_port_stats(स्थिर काष्ठा adapter *adapter,
				   स्थिर काष्ठा port_info *pi,
				   काष्ठा queue_port_stats *stats)
अणु
	स्थिर काष्ठा sge_eth_txq *txq = &adapter->sge.ethtxq[pi->first_qset];
	स्थिर काष्ठा sge_eth_rxq *rxq = &adapter->sge.ethrxq[pi->first_qset];
	पूर्णांक qs;

	स_रखो(stats, 0, माप(*stats));
	क्रम (qs = 0; qs < pi->nqsets; qs++, rxq++, txq++) अणु
		stats->tso += txq->tso;
		stats->tx_csum += txq->tx_cso;
		stats->rx_csum += rxq->stats.rx_cso;
		stats->vlan_ex += rxq->stats.vlan_ex;
		stats->vlan_ins += txq->vlan_ins;
		stats->lro_pkts += rxq->stats.lro_pkts;
		stats->lro_merged += rxq->stats.lro_merged;
	पूर्ण
पूर्ण

/*
 * Return the ETH_SS_STATS statistics set.
 */
अटल व्योम cxgb4vf_get_ethtool_stats(काष्ठा net_device *dev,
				      काष्ठा ethtool_stats *stats,
				      u64 *data)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक err = t4vf_get_port_stats(adapter, pi->pidx,
				      (काष्ठा t4vf_port_stats *)data);
	अगर (err)
		स_रखो(data, 0, माप(काष्ठा t4vf_port_stats));

	data += माप(काष्ठा t4vf_port_stats) / माप(u64);
	collect_sge_port_stats(adapter, pi, (काष्ठा queue_port_stats *)data);
पूर्ण

/*
 * Return the size of our रेजिस्टर map.
 */
अटल पूर्णांक cxgb4vf_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस T4VF_REGMAP_SIZE;
पूर्ण

/*
 * Dump a block of रेजिस्टरs, start to end inclusive, पूर्णांकo a buffer.
 */
अटल व्योम reg_block_dump(काष्ठा adapter *adapter, व्योम *regbuf,
			   अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	u32 *bp = regbuf + start - T4VF_REGMAP_START;

	क्रम ( ; start <= end; start += माप(u32)) अणु
		/*
		 * Aव्योम पढ़ोing the Mailbox Control रेजिस्टर since that
		 * can trigger a Mailbox Ownership Arbitration cycle and
		 * पूर्णांकerfere with communication with the firmware.
		 */
		अगर (start == T4VF_CIM_BASE_ADDR + CIM_VF_EXT_MAILBOX_CTRL)
			*bp++ = 0xffff;
		अन्यथा
			*bp++ = t4_पढ़ो_reg(adapter, start);
	पूर्ण
पूर्ण

/*
 * Copy our entire रेजिस्टर map पूर्णांकo the provided buffer.
 */
अटल व्योम cxgb4vf_get_regs(काष्ठा net_device *dev,
			     काष्ठा ethtool_regs *regs,
			     व्योम *regbuf)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);

	regs->version = mk_adap_vers(adapter);

	/*
	 * Fill in रेजिस्टर buffer with our रेजिस्टर map.
	 */
	स_रखो(regbuf, 0, T4VF_REGMAP_SIZE);

	reg_block_dump(adapter, regbuf,
		       T4VF_SGE_BASE_ADDR + T4VF_MOD_MAP_SGE_FIRST,
		       T4VF_SGE_BASE_ADDR + T4VF_MOD_MAP_SGE_LAST);
	reg_block_dump(adapter, regbuf,
		       T4VF_MPS_BASE_ADDR + T4VF_MOD_MAP_MPS_FIRST,
		       T4VF_MPS_BASE_ADDR + T4VF_MOD_MAP_MPS_LAST);

	/* T5 adds new रेजिस्टरs in the PL Register map.
	 */
	reg_block_dump(adapter, regbuf,
		       T4VF_PL_BASE_ADDR + T4VF_MOD_MAP_PL_FIRST,
		       T4VF_PL_BASE_ADDR + (is_t4(adapter->params.chip)
		       ? PL_VF_WHOAMI_A : PL_VF_REVISION_A));
	reg_block_dump(adapter, regbuf,
		       T4VF_CIM_BASE_ADDR + T4VF_MOD_MAP_CIM_FIRST,
		       T4VF_CIM_BASE_ADDR + T4VF_MOD_MAP_CIM_LAST);

	reg_block_dump(adapter, regbuf,
		       T4VF_MBDATA_BASE_ADDR + T4VF_MBDATA_FIRST,
		       T4VF_MBDATA_BASE_ADDR + T4VF_MBDATA_LAST);
पूर्ण

/*
 * Report current Wake On LAN settings.
 */
अटल व्योम cxgb4vf_get_wol(काष्ठा net_device *dev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	wol->supported = 0;
	wol->wolopts = 0;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

/*
 * TCP Segmentation Offload flags which we support.
 */
#घोषणा TSO_FLAGS (NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_TSO_ECN)
#घोषणा VLAN_FEAT (NETIF_F_SG | NETIF_F_IP_CSUM | TSO_FLAGS | \
		   NETIF_F_GRO | NETIF_F_IPV6_CSUM | NETIF_F_HIGHDMA)

अटल स्थिर काष्ठा ethtool_ops cxgb4vf_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_RX_MAX_FRAMES,
	.get_link_ksettings	= cxgb4vf_get_link_ksettings,
	.get_fecparam		= cxgb4vf_get_fecparam,
	.get_drvinfo		= cxgb4vf_get_drvinfo,
	.get_msglevel		= cxgb4vf_get_msglevel,
	.set_msglevel		= cxgb4vf_set_msglevel,
	.get_ringparam		= cxgb4vf_get_ringparam,
	.set_ringparam		= cxgb4vf_set_ringparam,
	.get_coalesce		= cxgb4vf_get_coalesce,
	.set_coalesce		= cxgb4vf_set_coalesce,
	.get_छोड़ोparam		= cxgb4vf_get_छोड़ोparam,
	.get_link		= ethtool_op_get_link,
	.get_strings		= cxgb4vf_get_strings,
	.set_phys_id		= cxgb4vf_phys_id,
	.get_sset_count		= cxgb4vf_get_sset_count,
	.get_ethtool_stats	= cxgb4vf_get_ethtool_stats,
	.get_regs_len		= cxgb4vf_get_regs_len,
	.get_regs		= cxgb4vf_get_regs,
	.get_wol		= cxgb4vf_get_wol,
पूर्ण;

/*
 * /sys/kernel/debug/cxgb4vf support code and data.
 * ================================================
 */

/*
 * Show Firmware Mailbox Command/Reply Log
 *
 * Note that we करोn't करो any locking when dumping the Firmware Mailbox Log so
 * it's possible that we can catch things during a log update and thereक्रमe
 * see partially corrupted log entries.  But i9t's probably Good Enough(पंचांग).
 * If we ever decide that we want to make sure that we're dumping a coherent
 * log, we'd need to perक्रमm locking in the mailbox logging and in
 * mboxlog_खोलो() where we'd need to grab the entire mailbox log in one go
 * like we करो क्रम the Firmware Device Log.  But as stated above, meh ...
 */
अटल पूर्णांक mboxlog_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	काष्ठा mbox_cmd_log *log = adapter->mbox_log;
	काष्ठा mbox_cmd *entry;
	पूर्णांक entry_idx, i;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq,
			   "%10s  %15s  %5s  %5s  %s\n",
			   "Seq#", "Tstamp", "Atime", "Etime",
			   "Command/Reply");
		वापस 0;
	पूर्ण

	entry_idx = log->cursor + ((uपूर्णांकptr_t)v - 2);
	अगर (entry_idx >= log->size)
		entry_idx -= log->size;
	entry = mbox_cmd_log_entry(log, entry_idx);

	/* skip over unused entries */
	अगर (entry->बारtamp == 0)
		वापस 0;

	seq_म_लिखो(seq, "%10u  %15llu  %5d  %5d",
		   entry->seqno, entry->बारtamp,
		   entry->access, entry->execute);
	क्रम (i = 0; i < MBOX_LEN / 8; i++) अणु
		u64 flit = entry->cmd[i];
		u32 hi = (u32)(flit >> 32);
		u32 lo = (u32)flit;

		seq_म_लिखो(seq, "  %08x %08x", hi, lo);
	पूर्ण
	seq_माला_दो(seq, "\n");
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *mboxlog_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	काष्ठा mbox_cmd_log *log = adapter->mbox_log;

	वापस ((pos <= log->size) ? (व्योम *)(uपूर्णांकptr_t)(pos + 1) : शून्य);
पूर्ण

अटल व्योम *mboxlog_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos ? mboxlog_get_idx(seq, *pos) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *mboxlog_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस mboxlog_get_idx(seq, *pos);
पूर्ण

अटल व्योम mboxlog_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations mboxlog_sops = अणु
	.start = mboxlog_start,
	.next  = mboxlog_next,
	.stop  = mboxlog_stop,
	.show  = mboxlog_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(mboxlog);
/*
 * Show SGE Queue Set inक्रमmation.  We display QPL Queues Sets per line.
 */
#घोषणा QPL	4

अटल पूर्णांक sge_qinfo_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	पूर्णांक eth_entries = DIV_ROUND_UP(adapter->sge.ethqsets, QPL);
	पूर्णांक qs, r = (uपूर्णांकptr_t)v - 1;

	अगर (r)
		seq_अ_दो(seq, '\n');

	#घोषणा S3(fmt_spec, s, v) \
		करो अणु\
			seq_म_लिखो(seq, "%-12s", s); \
			क्रम (qs = 0; qs < n; ++qs) \
				seq_म_लिखो(seq, " %16" fmt_spec, v); \
			seq_अ_दो(seq, '\n'); \
		पूर्ण जबतक (0)
	#घोषणा S(s, v)		S3("s", s, v)
	#घोषणा T(s, v)		S3("u", s, txq[qs].v)
	#घोषणा R(s, v)		S3("u", s, rxq[qs].v)

	अगर (r < eth_entries) अणु
		स्थिर काष्ठा sge_eth_rxq *rxq = &adapter->sge.ethrxq[r * QPL];
		स्थिर काष्ठा sge_eth_txq *txq = &adapter->sge.ethtxq[r * QPL];
		पूर्णांक n = min(QPL, adapter->sge.ethqsets - QPL * r);

		S("QType:", "Ethernet");
		S("Interface:",
		  (rxq[qs].rspq.netdev
		   ? rxq[qs].rspq.netdev->name
		   : "N/A"));
		S3("d", "Port:",
		   (rxq[qs].rspq.netdev
		    ? ((काष्ठा port_info *)
		       netdev_priv(rxq[qs].rspq.netdev))->port_id
		    : -1));
		T("TxQ ID:", q.असल_id);
		T("TxQ size:", q.size);
		T("TxQ inuse:", q.in_use);
		T("TxQ PIdx:", q.pidx);
		T("TxQ CIdx:", q.cidx);
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		S3("u", "Intr delay:", qसमयr_val(adapter, &rxq[qs].rspq));
		S3("u", "Intr pktcnt:",
		   adapter->sge.counter_val[rxq[qs].rspq.pktcnt_idx]);
		R("RspQ CIdx:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		R("FL ID:", fl.असल_id);
		R("FL size:", fl.size - MIN_FL_RESID);
		R("FL avail:", fl.avail);
		R("FL PIdx:", fl.pidx);
		R("FL CIdx:", fl.cidx);
		वापस 0;
	पूर्ण

	r -= eth_entries;
	अगर (r == 0) अणु
		स्थिर काष्ठा sge_rspq *evtq = &adapter->sge.fw_evtq;

		seq_म_लिखो(seq, "%-12s %16s\n", "QType:", "FW event queue");
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ ID:", evtq->असल_id);
		seq_म_लिखो(seq, "%-12s %16u\n", "Intr delay:",
			   qसमयr_val(adapter, evtq));
		seq_म_लिखो(seq, "%-12s %16u\n", "Intr pktcnt:",
			   adapter->sge.counter_val[evtq->pktcnt_idx]);
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ Cidx:", evtq->cidx);
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ Gen:", evtq->gen);
	पूर्ण अन्यथा अगर (r == 1) अणु
		स्थिर काष्ठा sge_rspq *पूर्णांकrq = &adapter->sge.पूर्णांकrq;

		seq_म_लिखो(seq, "%-12s %16s\n", "QType:", "Interrupt Queue");
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ ID:", पूर्णांकrq->असल_id);
		seq_म_लिखो(seq, "%-12s %16u\n", "Intr delay:",
			   qसमयr_val(adapter, पूर्णांकrq));
		seq_म_लिखो(seq, "%-12s %16u\n", "Intr pktcnt:",
			   adapter->sge.counter_val[पूर्णांकrq->pktcnt_idx]);
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ Cidx:", पूर्णांकrq->cidx);
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ Gen:", पूर्णांकrq->gen);
	पूर्ण

	#अघोषित R
	#अघोषित T
	#अघोषित S
	#अघोषित S3

	वापस 0;
पूर्ण

/*
 * Return the number of "entries" in our "file".  We group the multi-Queue
 * sections with QPL Queue Sets per "entry".  The sections of the output are:
 *
 *     Ethernet RX/TX Queue Sets
 *     Firmware Event Queue
 *     Forwarded Interrupt Queue (अगर in MSI mode)
 */
अटल पूर्णांक sge_queue_entries(स्थिर काष्ठा adapter *adapter)
अणु
	वापस DIV_ROUND_UP(adapter->sge.ethqsets, QPL) + 1 +
		((adapter->flags & CXGB4VF_USING_MSI) != 0);
पूर्ण

अटल व्योम *sge_queue_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	पूर्णांक entries = sge_queue_entries(seq->निजी);

	वापस *pos < entries ? (व्योम *)((uपूर्णांकptr_t)*pos + 1) : शून्य;
पूर्ण

अटल व्योम sge_queue_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल व्योम *sge_queue_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	पूर्णांक entries = sge_queue_entries(seq->निजी);

	++*pos;
	वापस *pos < entries ? (व्योम *)((uपूर्णांकptr_t)*pos + 1) : शून्य;
पूर्ण

अटल स्थिर काष्ठा seq_operations sge_qinfo_sops = अणु
	.start = sge_queue_start,
	.next  = sge_queue_next,
	.stop  = sge_queue_stop,
	.show  = sge_qinfo_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(sge_qinfo);

/*
 * Show SGE Queue Set statistics.  We display QPL Queues Sets per line.
 */
#घोषणा QPL	4

अटल पूर्णांक sge_qstats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	पूर्णांक eth_entries = DIV_ROUND_UP(adapter->sge.ethqsets, QPL);
	पूर्णांक qs, r = (uपूर्णांकptr_t)v - 1;

	अगर (r)
		seq_अ_दो(seq, '\n');

	#घोषणा S3(fmt, s, v) \
		करो अणु \
			seq_म_लिखो(seq, "%-16s", s); \
			क्रम (qs = 0; qs < n; ++qs) \
				seq_म_लिखो(seq, " %8" fmt, v); \
			seq_अ_दो(seq, '\n'); \
		पूर्ण जबतक (0)
	#घोषणा S(s, v)		S3("s", s, v)

	#घोषणा T3(fmt, s, v)	S3(fmt, s, txq[qs].v)
	#घोषणा T(s, v)		T3("lu", s, v)

	#घोषणा R3(fmt, s, v)	S3(fmt, s, rxq[qs].v)
	#घोषणा R(s, v)		R3("lu", s, v)

	अगर (r < eth_entries) अणु
		स्थिर काष्ठा sge_eth_rxq *rxq = &adapter->sge.ethrxq[r * QPL];
		स्थिर काष्ठा sge_eth_txq *txq = &adapter->sge.ethtxq[r * QPL];
		पूर्णांक n = min(QPL, adapter->sge.ethqsets - QPL * r);

		S("QType:", "Ethernet");
		S("Interface:",
		  (rxq[qs].rspq.netdev
		   ? rxq[qs].rspq.netdev->name
		   : "N/A"));
		R3("u", "RspQNullInts:", rspq.unhandled_irqs);
		R("RxPackets:", stats.pkts);
		R("RxCSO:", stats.rx_cso);
		R("VLANxtract:", stats.vlan_ex);
		R("LROmerged:", stats.lro_merged);
		R("LROpackets:", stats.lro_pkts);
		R("RxDrops:", stats.rx_drops);
		T("TSO:", tso);
		T("TxCSO:", tx_cso);
		T("VLANins:", vlan_ins);
		T("TxQFull:", q.stops);
		T("TxQRestarts:", q.restarts);
		T("TxMapErr:", mapping_err);
		R("FLAllocErr:", fl.alloc_failed);
		R("FLLrgAlcErr:", fl.large_alloc_failed);
		R("FLStarving:", fl.starving);
		वापस 0;
	पूर्ण

	r -= eth_entries;
	अगर (r == 0) अणु
		स्थिर काष्ठा sge_rspq *evtq = &adapter->sge.fw_evtq;

		seq_म_लिखो(seq, "%-8s %16s\n", "QType:", "FW event queue");
		seq_म_लिखो(seq, "%-16s %8u\n", "RspQNullInts:",
			   evtq->unhandled_irqs);
		seq_म_लिखो(seq, "%-16s %8u\n", "RspQ CIdx:", evtq->cidx);
		seq_म_लिखो(seq, "%-16s %8u\n", "RspQ Gen:", evtq->gen);
	पूर्ण अन्यथा अगर (r == 1) अणु
		स्थिर काष्ठा sge_rspq *पूर्णांकrq = &adapter->sge.पूर्णांकrq;

		seq_म_लिखो(seq, "%-8s %16s\n", "QType:", "Interrupt Queue");
		seq_म_लिखो(seq, "%-16s %8u\n", "RspQNullInts:",
			   पूर्णांकrq->unhandled_irqs);
		seq_म_लिखो(seq, "%-16s %8u\n", "RspQ CIdx:", पूर्णांकrq->cidx);
		seq_म_लिखो(seq, "%-16s %8u\n", "RspQ Gen:", पूर्णांकrq->gen);
	पूर्ण

	#अघोषित R
	#अघोषित T
	#अघोषित S
	#अघोषित R3
	#अघोषित T3
	#अघोषित S3

	वापस 0;
पूर्ण

/*
 * Return the number of "entries" in our "file".  We group the multi-Queue
 * sections with QPL Queue Sets per "entry".  The sections of the output are:
 *
 *     Ethernet RX/TX Queue Sets
 *     Firmware Event Queue
 *     Forwarded Interrupt Queue (अगर in MSI mode)
 */
अटल पूर्णांक sge_qstats_entries(स्थिर काष्ठा adapter *adapter)
अणु
	वापस DIV_ROUND_UP(adapter->sge.ethqsets, QPL) + 1 +
		((adapter->flags & CXGB4VF_USING_MSI) != 0);
पूर्ण

अटल व्योम *sge_qstats_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	पूर्णांक entries = sge_qstats_entries(seq->निजी);

	वापस *pos < entries ? (व्योम *)((uपूर्णांकptr_t)*pos + 1) : शून्य;
पूर्ण

अटल व्योम sge_qstats_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल व्योम *sge_qstats_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	पूर्णांक entries = sge_qstats_entries(seq->निजी);

	(*pos)++;
	वापस *pos < entries ? (व्योम *)((uपूर्णांकptr_t)*pos + 1) : शून्य;
पूर्ण

अटल स्थिर काष्ठा seq_operations sge_qstats_sops = अणु
	.start = sge_qstats_start,
	.next  = sge_qstats_next,
	.stop  = sge_qstats_stop,
	.show  = sge_qstats_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(sge_qstats);

/*
 * Show PCI-E SR-IOV Virtual Function Resource Limits.
 */
अटल पूर्णांक resources_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	काष्ठा vf_resources *vfres = &adapter->params.vfres;

	#घोषणा S(desc, fmt, var) \
		seq_म_लिखो(seq, "%-60s " fmt "\n", \
			   desc " (" #var "):", vfres->var)

	S("Virtual Interfaces", "%d", nvi);
	S("Egress Queues", "%d", neq);
	S("Ethernet Control", "%d", nethctrl);
	S("Ingress Queues/w Free Lists/Interrupts", "%d", niqflपूर्णांक);
	S("Ingress Queues", "%d", niq);
	S("Traffic Class", "%d", tc);
	S("Port Access Rights Mask", "%#x", pmask);
	S("MAC Address Filters", "%d", nexactf);
	S("Firmware Command Read Capabilities", "%#x", r_caps);
	S("Firmware Command Write/Execute Capabilities", "%#x", wx_caps);

	#अघोषित S

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(resources);

/*
 * Show Virtual Interfaces.
 */
अटल पूर्णांक पूर्णांकerfaces_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Interface  Port   VIID\n");
	पूर्ण अन्यथा अणु
		काष्ठा adapter *adapter = seq->निजी;
		पूर्णांक pidx = (uपूर्णांकptr_t)v - 2;
		काष्ठा net_device *dev = adapter->port[pidx];
		काष्ठा port_info *pi = netdev_priv(dev);

		seq_म_लिखो(seq, "%9s  %4d  %#5x\n",
			   dev->name, pi->port_id, pi->viid);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *पूर्णांकerfaces_get_idx(काष्ठा adapter *adapter, loff_t pos)
अणु
	वापस pos <= adapter->params.nports
		? (व्योम *)(uपूर्णांकptr_t)(pos + 1)
		: शून्य;
पूर्ण

अटल व्योम *पूर्णांकerfaces_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos
		? पूर्णांकerfaces_get_idx(seq->निजी, *pos)
		: SEQ_START_TOKEN;
पूर्ण

अटल व्योम *पूर्णांकerfaces_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस पूर्णांकerfaces_get_idx(seq->निजी, *pos);
पूर्ण

अटल व्योम पूर्णांकerfaces_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations पूर्णांकerfaces_sops = अणु
	.start = पूर्णांकerfaces_start,
	.next  = पूर्णांकerfaces_next,
	.stop  = पूर्णांकerfaces_stop,
	.show  = पूर्णांकerfaces_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(पूर्णांकerfaces);

/*
 * /sys/kernel/debugfs/cxgb4vf/ files list.
 */
काष्ठा cxgb4vf_debugfs_entry अणु
	स्थिर अक्षर *name;		/* name of debugfs node */
	umode_t mode;			/* file प्रणाली mode */
	स्थिर काष्ठा file_operations *fops;
पूर्ण;

अटल काष्ठा cxgb4vf_debugfs_entry debugfs_files[] = अणु
	अणु "mboxlog",    0444, &mboxlog_fops पूर्ण,
	अणु "sge_qinfo",  0444, &sge_qinfo_fops पूर्ण,
	अणु "sge_qstats", 0444, &sge_qstats_fops पूर्ण,
	अणु "resources",  0444, &resources_fops पूर्ण,
	अणु "interfaces", 0444, &पूर्णांकerfaces_fops पूर्ण,
पूर्ण;

/*
 * Module and device initialization and cleanup code.
 * ==================================================
 */

/*
 * Set up out /sys/kernel/debug/cxgb4vf sub-nodes.  We assume that the
 * directory (debugfs_root) has alपढ़ोy been set up.
 */
अटल पूर्णांक setup_debugfs(काष्ठा adapter *adapter)
अणु
	पूर्णांक i;

	BUG_ON(IS_ERR_OR_शून्य(adapter->debugfs_root));

	/*
	 * Debugfs support is best efक्रमt.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(debugfs_files); i++)
		debugfs_create_file(debugfs_files[i].name,
				    debugfs_files[i].mode,
				    adapter->debugfs_root, adapter,
				    debugfs_files[i].fops);

	वापस 0;
पूर्ण

/*
 * Tear करोwn the /sys/kernel/debug/cxgb4vf sub-nodes created above.  We leave
 * it to our caller to tear करोwn the directory (debugfs_root).
 */
अटल व्योम cleanup_debugfs(काष्ठा adapter *adapter)
अणु
	BUG_ON(IS_ERR_OR_शून्य(adapter->debugfs_root));

	/*
	 * Unlike our sister routine cleanup_proc(), we करोn't need to हटाओ
	 * inभागidual entries because a call will be made to
	 * debugfs_हटाओ_recursive().  We just need to clean up any ancillary
	 * persistent state.
	 */
	/* nothing to करो */
पूर्ण

/* Figure out how many Ports and Queue Sets we can support.  This depends on
 * knowing our Virtual Function Resources and may be called a second समय अगर
 * we fall back from MSI-X to MSI Interrupt Mode.
 */
अटल व्योम size_nports_qsets(काष्ठा adapter *adapter)
अणु
	काष्ठा vf_resources *vfres = &adapter->params.vfres;
	अचिन्हित पूर्णांक ethqsets, pmask_nports;

	/* The number of "ports" which we support is equal to the number of
	 * Virtual Interfaces with which we've been provisioned.
	 */
	adapter->params.nports = vfres->nvi;
	अगर (adapter->params.nports > MAX_NPORTS) अणु
		dev_warn(adapter->pdev_dev, "only using %d of %d maximum"
			 " allowed virtual interfaces\n", MAX_NPORTS,
			 adapter->params.nports);
		adapter->params.nports = MAX_NPORTS;
	पूर्ण

	/* We may have been provisioned with more VIs than the number of
	 * ports we're allowed to access (our Port Access Rights Mask).
	 * This is obviously a configuration conflict but we करोn't want to
	 * crash the kernel or anything silly just because of that.
	 */
	pmask_nports = hweight32(adapter->params.vfres.pmask);
	अगर (pmask_nports < adapter->params.nports) अणु
		dev_warn(adapter->pdev_dev, "only using %d of %d provisioned"
			 " virtual interfaces; limited by Port Access Rights"
			 " mask %#x\n", pmask_nports, adapter->params.nports,
			 adapter->params.vfres.pmask);
		adapter->params.nports = pmask_nports;
	पूर्ण

	/* We need to reserve an Ingress Queue क्रम the Asynchronous Firmware
	 * Event Queue.  And अगर we're using MSI Interrupts, we'll also need to
	 * reserve an Ingress Queue क्रम a Forwarded Interrupts.
	 *
	 * The rest of the FL/Intr-capable ingress queues will be matched up
	 * one-क्रम-one with Ethernet/Control egress queues in order to क्रमm
	 * "Queue Sets" which will be aportioned between the "ports".  For
	 * each Queue Set, we'll need the ability to allocate two Egress
	 * Contexts -- one क्रम the Ingress Queue Free List and one क्रम the TX
	 * Ethernet Queue.
	 *
	 * Note that even अगर we're currently configured to use MSI-X
	 * Interrupts (module variable msi == MSI_MSIX) we may get करोwngraded
	 * to MSI Interrupts अगर we can't get enough MSI-X Interrupts.  If that
	 * happens we'll need to adjust things later.
	 */
	ethqsets = vfres->niqflपूर्णांक - 1 - (msi == MSI_MSI);
	अगर (vfres->nethctrl != ethqsets)
		ethqsets = min(vfres->nethctrl, ethqsets);
	अगर (vfres->neq < ethqsets*2)
		ethqsets = vfres->neq/2;
	अगर (ethqsets > MAX_ETH_QSETS)
		ethqsets = MAX_ETH_QSETS;
	adapter->sge.max_ethqsets = ethqsets;

	अगर (adapter->sge.max_ethqsets < adapter->params.nports) अणु
		dev_warn(adapter->pdev_dev, "only using %d of %d available"
			 " virtual interfaces (too few Queue Sets)\n",
			 adapter->sge.max_ethqsets, adapter->params.nports);
		adapter->params.nports = adapter->sge.max_ethqsets;
	पूर्ण
पूर्ण

/*
 * Perक्रमm early "adapter" initialization.  This is where we discover what
 * adapter parameters we're going to be using and initialize basic adapter
 * hardware support.
 */
अटल पूर्णांक adap_init0(काष्ठा adapter *adapter)
अणु
	काष्ठा sge_params *sge_params = &adapter->params.sge;
	काष्ठा sge *s = &adapter->sge;
	पूर्णांक err;
	u32 param, val = 0;

	/*
	 * Some environments करो not properly handle PCIE FLRs -- e.g. in Linux
	 * 2.6.31 and later we can't call pci_reset_function() in order to
	 * issue an FLR because of a self- deadlock on the device semaphore.
	 * Meanजबतक, the OS infraकाष्ठाure करोesn't issue FLRs in all the
	 * हालs where they're needed -- क्रम instance, some versions of KVM
	 * fail to reset "Assigned Devices" when the VM reboots.  Thereक्रमe we
	 * use the firmware based reset in order to reset any per function
	 * state.
	 */
	err = t4vf_fw_reset(adapter);
	अगर (err < 0) अणु
		dev_err(adapter->pdev_dev, "FW reset failed: err=%d\n", err);
		वापस err;
	पूर्ण

	/*
	 * Grab basic operational parameters.  These will preकरोminantly have
	 * been set up by the Physical Function Driver or will be hard coded
	 * पूर्णांकo the adapter.  We just have to live with them ...  Note that
	 * we _must_ get our VPD parameters beक्रमe our SGE parameters because
	 * we need to know the adapter's core घड़ी from the VPD in order to
	 * properly decode the SGE Timer Values.
	 */
	err = t4vf_get_dev_params(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev, "unable to retrieve adapter"
			" device parameters: err=%d\n", err);
		वापस err;
	पूर्ण
	err = t4vf_get_vpd_params(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev, "unable to retrieve adapter"
			" VPD parameters: err=%d\n", err);
		वापस err;
	पूर्ण
	err = t4vf_get_sge_params(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev, "unable to retrieve adapter"
			" SGE parameters: err=%d\n", err);
		वापस err;
	पूर्ण
	err = t4vf_get_rss_glb_config(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev, "unable to retrieve adapter"
			" RSS parameters: err=%d\n", err);
		वापस err;
	पूर्ण
	अगर (adapter->params.rss.mode !=
	    FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL) अणु
		dev_err(adapter->pdev_dev, "unable to operate with global RSS"
			" mode %d\n", adapter->params.rss.mode);
		वापस -EINVAL;
	पूर्ण
	err = t4vf_sge_init(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev, "unable to use adapter parameters:"
			" err=%d\n", err);
		वापस err;
	पूर्ण

	/* If we're running on newer firmware, let it know that we're
	 * prepared to deal with encapsulated CPL messages.  Older
	 * firmware won't understand this and we'll just get
	 * unencapsulated messages ...
	 */
	param = FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) |
		FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_CPLFW4MSG_ENCAP);
	val = 1;
	(व्योम) t4vf_set_params(adapter, 1, &param, &val);

	/*
	 * Retrieve our RX पूर्णांकerrupt holकरोff समयr values and counter
	 * threshold values from the SGE parameters.
	 */
	s->समयr_val[0] = core_ticks_to_us(adapter,
		TIMERVALUE0_G(sge_params->sge_समयr_value_0_and_1));
	s->समयr_val[1] = core_ticks_to_us(adapter,
		TIMERVALUE1_G(sge_params->sge_समयr_value_0_and_1));
	s->समयr_val[2] = core_ticks_to_us(adapter,
		TIMERVALUE0_G(sge_params->sge_समयr_value_2_and_3));
	s->समयr_val[3] = core_ticks_to_us(adapter,
		TIMERVALUE1_G(sge_params->sge_समयr_value_2_and_3));
	s->समयr_val[4] = core_ticks_to_us(adapter,
		TIMERVALUE0_G(sge_params->sge_समयr_value_4_and_5));
	s->समयr_val[5] = core_ticks_to_us(adapter,
		TIMERVALUE1_G(sge_params->sge_समयr_value_4_and_5));

	s->counter_val[0] = THRESHOLD_0_G(sge_params->sge_ingress_rx_threshold);
	s->counter_val[1] = THRESHOLD_1_G(sge_params->sge_ingress_rx_threshold);
	s->counter_val[2] = THRESHOLD_2_G(sge_params->sge_ingress_rx_threshold);
	s->counter_val[3] = THRESHOLD_3_G(sge_params->sge_ingress_rx_threshold);

	/*
	 * Grab our Virtual Interface resource allocation, extract the
	 * features that we're पूर्णांकerested in and करो a bit of sanity testing on
	 * what we discover.
	 */
	err = t4vf_get_vfres(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev, "unable to get virtual interface"
			" resources: err=%d\n", err);
		वापस err;
	पूर्ण

	/* Check क्रम various parameter sanity issues */
	अगर (adapter->params.vfres.pmask == 0) अणु
		dev_err(adapter->pdev_dev, "no port access configured\n"
			"usable!\n");
		वापस -EINVAL;
	पूर्ण
	अगर (adapter->params.vfres.nvi == 0) अणु
		dev_err(adapter->pdev_dev, "no virtual interfaces configured/"
			"usable!\n");
		वापस -EINVAL;
	पूर्ण

	/* Initialize nports and max_ethqsets now that we have our Virtual
	 * Function Resources.
	 */
	size_nports_qsets(adapter);

	adapter->flags |= CXGB4VF_FW_OK;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम init_rspq(काष्ठा sge_rspq *rspq, u8 समयr_idx,
			     u8 pkt_cnt_idx, अचिन्हित पूर्णांक size,
			     अचिन्हित पूर्णांक iqe_size)
अणु
	rspq->पूर्णांकr_params = (QINTR_TIMER_IDX_V(समयr_idx) |
			     (pkt_cnt_idx < SGE_NCOUNTERS ?
			      QINTR_CNT_EN_F : 0));
	rspq->pktcnt_idx = (pkt_cnt_idx < SGE_NCOUNTERS
			    ? pkt_cnt_idx
			    : 0);
	rspq->iqe_len = iqe_size;
	rspq->size = size;
पूर्ण

/*
 * Perक्रमm शेष configuration of DMA queues depending on the number and
 * type of ports we found and the number of available CPUs.  Most settings can
 * be modअगरied by the admin via ethtool and cxgbtool prior to the adapter
 * being brought up क्रम the first समय.
 */
अटल व्योम cfg_queues(काष्ठा adapter *adapter)
अणु
	काष्ठा sge *s = &adapter->sge;
	पूर्णांक q10g, n10g, qidx, pidx, qs;
	माप_प्रकार iqe_size;

	/*
	 * We should not be called till we know how many Queue Sets we can
	 * support.  In particular, this means that we need to know what kind
	 * of पूर्णांकerrupts we'll be using ...
	 */
	BUG_ON((adapter->flags &
	       (CXGB4VF_USING_MSIX | CXGB4VF_USING_MSI)) == 0);

	/*
	 * Count the number of 10GbE Virtual Interfaces that we have.
	 */
	n10g = 0;
	क्रम_each_port(adapter, pidx)
		n10g += is_x_10g_port(&adap2pinfo(adapter, pidx)->link_cfg);

	/*
	 * We शेष to 1 queue per non-10G port and up to # of cores queues
	 * per 10G port.
	 */
	अगर (n10g == 0)
		q10g = 0;
	अन्यथा अणु
		पूर्णांक n1g = (adapter->params.nports - n10g);
		q10g = (adapter->sge.max_ethqsets - n1g) / n10g;
		अगर (q10g > num_online_cpus())
			q10g = num_online_cpus();
	पूर्ण

	/*
	 * Allocate the "Queue Sets" to the various Virtual Interfaces.
	 * The layout will be established in setup_sge_queues() when the
	 * adapter is brough up क्रम the first समय.
	 */
	qidx = 0;
	क्रम_each_port(adapter, pidx) अणु
		काष्ठा port_info *pi = adap2pinfo(adapter, pidx);

		pi->first_qset = qidx;
		pi->nqsets = is_x_10g_port(&pi->link_cfg) ? q10g : 1;
		qidx += pi->nqsets;
	पूर्ण
	s->ethqsets = qidx;

	/*
	 * The Ingress Queue Entry Size क्रम our various Response Queues needs
	 * to be big enough to accommodate the largest message we can receive
	 * from the chip/firmware; which is 64 bytes ...
	 */
	iqe_size = 64;

	/*
	 * Set up शेष Queue Set parameters ...  Start off with the
	 * लघुest पूर्णांकerrupt holकरोff समयr.
	 */
	क्रम (qs = 0; qs < s->max_ethqsets; qs++) अणु
		काष्ठा sge_eth_rxq *rxq = &s->ethrxq[qs];
		काष्ठा sge_eth_txq *txq = &s->ethtxq[qs];

		init_rspq(&rxq->rspq, 0, 0, 1024, iqe_size);
		rxq->fl.size = 72;
		txq->q.size = 1024;
	पूर्ण

	/*
	 * The firmware event queue is used क्रम link state changes and
	 * notअगरications of TX DMA completions.
	 */
	init_rspq(&s->fw_evtq, SGE_TIMER_RSTRT_CNTR, 0, 512, iqe_size);

	/*
	 * The क्रमwarded पूर्णांकerrupt queue is used when we're in MSI पूर्णांकerrupt
	 * mode.  In this mode all पूर्णांकerrupts associated with RX queues will
	 * be क्रमwarded to a single queue which we'll associate with our MSI
	 * पूर्णांकerrupt vector.  The messages dropped in the क्रमwarded पूर्णांकerrupt
	 * queue will indicate which ingress queue needs servicing ...  This
	 * queue needs to be large enough to accommodate all of the ingress
	 * queues which are क्रमwarding their पूर्णांकerrupt (+1 to prevent the PIDX
	 * from equalling the CIDX अगर every ingress queue has an outstanding
	 * पूर्णांकerrupt).  The queue करोesn't need to be any larger because no
	 * ingress queue will ever have more than one outstanding पूर्णांकerrupt at
	 * any समय ...
	 */
	init_rspq(&s->पूर्णांकrq, SGE_TIMER_RSTRT_CNTR, 0, MSIX_ENTRIES + 1,
		  iqe_size);
पूर्ण

/*
 * Reduce the number of Ethernet queues across all ports to at most n.
 * n provides at least one queue per port.
 */
अटल व्योम reduce_ethqs(काष्ठा adapter *adapter, पूर्णांक n)
अणु
	पूर्णांक i;
	काष्ठा port_info *pi;

	/*
	 * While we have too many active Ether Queue Sets, पूर्णांकerate across the
	 * "ports" and reduce their inभागidual Queue Set allocations.
	 */
	BUG_ON(n < adapter->params.nports);
	जबतक (n < adapter->sge.ethqsets)
		क्रम_each_port(adapter, i) अणु
			pi = adap2pinfo(adapter, i);
			अगर (pi->nqsets > 1) अणु
				pi->nqsets--;
				adapter->sge.ethqsets--;
				अगर (adapter->sge.ethqsets <= n)
					अवरोध;
			पूर्ण
		पूर्ण

	/*
	 * Reassign the starting Queue Sets क्रम each of the "ports" ...
	 */
	n = 0;
	क्रम_each_port(adapter, i) अणु
		pi = adap2pinfo(adapter, i);
		pi->first_qset = n;
		n += pi->nqsets;
	पूर्ण
पूर्ण

/*
 * We need to grab enough MSI-X vectors to cover our पूर्णांकerrupt needs.  Ideally
 * we get a separate MSI-X vector क्रम every "Queue Set" plus any extras we
 * need.  Minimally we need one क्रम every Virtual Interface plus those needed
 * क्रम our "extras".  Note that this process may lower the maximum number of
 * allowed Queue Sets ...
 */
अटल पूर्णांक enable_msix(काष्ठा adapter *adapter)
अणु
	पूर्णांक i, want, need, nqsets;
	काष्ठा msix_entry entries[MSIX_ENTRIES];
	काष्ठा sge *s = &adapter->sge;

	क्रम (i = 0; i < MSIX_ENTRIES; ++i)
		entries[i].entry = i;

	/*
	 * We _want_ enough MSI-X पूर्णांकerrupts to cover all of our "Queue Sets"
	 * plus those needed क्रम our "extras" (क्रम example, the firmware
	 * message queue).  We _need_ at least one "Queue Set" per Virtual
	 * Interface plus those needed क्रम our "extras".  So now we get to see
	 * अगर the song is right ...
	 */
	want = s->max_ethqsets + MSIX_EXTRAS;
	need = adapter->params.nports + MSIX_EXTRAS;

	want = pci_enable_msix_range(adapter->pdev, entries, need, want);
	अगर (want < 0)
		वापस want;

	nqsets = want - MSIX_EXTRAS;
	अगर (nqsets < s->max_ethqsets) अणु
		dev_warn(adapter->pdev_dev, "only enough MSI-X vectors"
			 " for %d Queue Sets\n", nqsets);
		s->max_ethqsets = nqsets;
		अगर (nqsets < s->ethqsets)
			reduce_ethqs(adapter, nqsets);
	पूर्ण
	क्रम (i = 0; i < want; ++i)
		adapter->msix_info[i].vec = entries[i].vector;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops cxgb4vf_netdev_ops	= अणु
	.nकरो_खोलो		= cxgb4vf_खोलो,
	.nकरो_stop		= cxgb4vf_stop,
	.nकरो_start_xmit		= t4vf_eth_xmit,
	.nकरो_get_stats		= cxgb4vf_get_stats,
	.nकरो_set_rx_mode	= cxgb4vf_set_rxmode,
	.nकरो_set_mac_address	= cxgb4vf_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= cxgb4vf_करो_ioctl,
	.nकरो_change_mtu		= cxgb4vf_change_mtu,
	.nकरो_fix_features	= cxgb4vf_fix_features,
	.nकरो_set_features	= cxgb4vf_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cxgb4vf_poll_controller,
#पूर्ण_अगर
पूर्ण;

/**
 *	cxgb4vf_get_port_mask - Get port mask क्रम the VF based on mac
 *				address stored on the adapter
 *	@adapter: The adapter
 *
 *	Find the the port mask क्रम the VF based on the index of mac
 *	address stored in the adapter. If no mac address is stored on
 *	the adapter क्रम the VF, use the port mask received from the
 *	firmware.
 */
अटल अचिन्हित पूर्णांक cxgb4vf_get_port_mask(काष्ठा adapter *adapter)
अणु
	अचिन्हित पूर्णांक naddr = 1, pidx = 0;
	अचिन्हित पूर्णांक pmask, rmask = 0;
	u8 mac[ETH_ALEN];
	पूर्णांक err;

	pmask = adapter->params.vfres.pmask;
	जबतक (pmask) अणु
		अगर (pmask & 1) अणु
			err = t4vf_get_vf_mac_acl(adapter, pidx, &naddr, mac);
			अगर (!err && !is_zero_ether_addr(mac))
				rmask |= (1 << pidx);
		पूर्ण
		pmask >>= 1;
		pidx++;
	पूर्ण
	अगर (!rmask)
		rmask = adapter->params.vfres.pmask;

	वापस rmask;
पूर्ण

/*
 * "Probe" a device: initialize a device and स्थिरruct all kernel and driver
 * state needed to manage the device.  This routine is called "init_one" in
 * the PF Driver ...
 */
अटल पूर्णांक cxgb4vf_pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा adapter *adapter;
	काष्ठा net_device *netdev;
	काष्ठा port_info *pi;
	अचिन्हित पूर्णांक pmask;
	पूर्णांक pci_using_dac;
	पूर्णांक err, pidx;

	/*
	 * Initialize generic PCI device state.
	 */
	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		वापस err;
	पूर्ण

	/*
	 * Reserve PCI resources क्रम the device.  If we can't get them some
	 * other driver may have alपढ़ोy claimed the device ...
	 */
	err = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot obtain PCI resources\n");
		जाओ err_disable_device;
	पूर्ण

	/*
	 * Set up our DMA mask: try क्रम 64-bit address masking first and
	 * fall back to 32-bit अगर we can't get 64 bits ...
	 */
	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err == 0) अणु
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
		अगर (err) अणु
			dev_err(&pdev->dev, "unable to obtain 64-bit DMA for"
				" coherent allocations\n");
			जाओ err_release_regions;
		पूर्ण
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err != 0) अणु
			dev_err(&pdev->dev, "no usable DMA configuration\n");
			जाओ err_release_regions;
		पूर्ण
		pci_using_dac = 0;
	पूर्ण

	/*
	 * Enable bus mastering क्रम the device ...
	 */
	pci_set_master(pdev);

	/*
	 * Allocate our adapter data काष्ठाure and attach it to the device.
	 */
	adapter = kzalloc(माप(*adapter), GFP_KERNEL);
	अगर (!adapter) अणु
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण
	pci_set_drvdata(pdev, adapter);
	adapter->pdev = pdev;
	adapter->pdev_dev = &pdev->dev;

	adapter->mbox_log = kzalloc(माप(*adapter->mbox_log) +
				    (माप(काष्ठा mbox_cmd) *
				     T4VF_OS_LOG_MBOX_CMDS),
				    GFP_KERNEL);
	अगर (!adapter->mbox_log) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_adapter;
	पूर्ण
	adapter->mbox_log->size = T4VF_OS_LOG_MBOX_CMDS;

	/*
	 * Initialize SMP data synchronization resources.
	 */
	spin_lock_init(&adapter->stats_lock);
	spin_lock_init(&adapter->mbox_lock);
	INIT_LIST_HEAD(&adapter->mlist.list);

	/*
	 * Map our I/O रेजिस्टरs in BAR0.
	 */
	adapter->regs = pci_ioremap_bar(pdev, 0);
	अगर (!adapter->regs) अणु
		dev_err(&pdev->dev, "cannot map device registers\n");
		err = -ENOMEM;
		जाओ err_मुक्त_adapter;
	पूर्ण

	/* Wait क्रम the device to become पढ़ोy beक्रमe proceeding ...
	 */
	err = t4vf_prep_adapter(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev, "device didn't become ready:"
			" err=%d\n", err);
		जाओ err_unmap_bar0;
	पूर्ण

	/* For T5 and later we want to use the new BAR-based User Doorbells,
	 * so we need to map BAR2 here ...
	 */
	अगर (!is_t4(adapter->params.chip)) अणु
		adapter->bar2 = ioremap_wc(pci_resource_start(pdev, 2),
					   pci_resource_len(pdev, 2));
		अगर (!adapter->bar2) अणु
			dev_err(adapter->pdev_dev, "cannot map BAR2 doorbells\n");
			err = -ENOMEM;
			जाओ err_unmap_bar0;
		पूर्ण
	पूर्ण
	/*
	 * Initialize adapter level features.
	 */
	adapter->name = pci_name(pdev);
	adapter->msg_enable = DFLT_MSG_ENABLE;

	/* If possible, we use PCIe Relaxed Ordering Attribute to deliver
	 * Ingress Packet Data to Free List Buffers in order to allow क्रम
	 * chipset perक्रमmance optimizations between the Root Complex and
	 * Memory Controllers.  (Messages to the associated Ingress Queue
	 * notअगरying new Packet Placement in the Free Lists Buffers will be
	 * send without the Relaxed Ordering Attribute thus guaranteeing that
	 * all preceding PCIe Transaction Layer Packets will be processed
	 * first.)  But some Root Complexes have various issues with Upstream
	 * Transaction Layer Packets with the Relaxed Ordering Attribute set.
	 * The PCIe devices which under the Root Complexes will be cleared the
	 * Relaxed Ordering bit in the configuration space, So we check our
	 * PCIe configuration space to see अगर it's flagged with advice against
	 * using Relaxed Ordering.
	 */
	अगर (!pcie_relaxed_ordering_enabled(pdev))
		adapter->flags |= CXGB4VF_ROOT_NO_RELAXED_ORDERING;

	err = adap_init0(adapter);
	अगर (err)
		dev_err(&pdev->dev,
			"Adapter initialization failed, error %d. Continuing in debug mode\n",
			err);

	/* Initialize hash mac addr list */
	INIT_LIST_HEAD(&adapter->mac_hlist);

	/*
	 * Allocate our "adapter ports" and stitch everything together.
	 */
	pmask = cxgb4vf_get_port_mask(adapter);
	क्रम_each_port(adapter, pidx) अणु
		पूर्णांक port_id, viid;
		u8 mac[ETH_ALEN];
		अचिन्हित पूर्णांक naddr = 1;

		/*
		 * We simplistically allocate our भव पूर्णांकerfaces
		 * sequentially across the port numbers to which we have
		 * access rights.  This should be configurable in some manner
		 * ...
		 */
		अगर (pmask == 0)
			अवरोध;
		port_id = ffs(pmask) - 1;
		pmask &= ~(1 << port_id);

		/*
		 * Allocate our network device and stitch things together.
		 */
		netdev = alloc_etherdev_mq(माप(काष्ठा port_info),
					   MAX_PORT_QSETS);
		अगर (netdev == शून्य) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_dev;
		पूर्ण
		adapter->port[pidx] = netdev;
		SET_NETDEV_DEV(netdev, &pdev->dev);
		pi = netdev_priv(netdev);
		pi->adapter = adapter;
		pi->pidx = pidx;
		pi->port_id = port_id;

		/*
		 * Initialize the starting state of our "port" and रेजिस्टर
		 * it.
		 */
		pi->xact_addr_filt = -1;
		netdev->irq = pdev->irq;

		netdev->hw_features = NETIF_F_SG | TSO_FLAGS | NETIF_F_GRO |
			NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM |
			NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
		netdev->features = netdev->hw_features;
		अगर (pci_using_dac)
			netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features = netdev->features & VLAN_FEAT;

		netdev->priv_flags |= IFF_UNICAST_FLT;
		netdev->min_mtu = 81;
		netdev->max_mtu = ETH_MAX_MTU;

		netdev->netdev_ops = &cxgb4vf_netdev_ops;
		netdev->ethtool_ops = &cxgb4vf_ethtool_ops;
		netdev->dev_port = pi->port_id;

		/*
		 * If we haven't been able to contact the firmware, there's
		 * nothing अन्यथा we can करो क्रम this "port" ...
		 */
		अगर (!(adapter->flags & CXGB4VF_FW_OK))
			जारी;

		viid = t4vf_alloc_vi(adapter, port_id);
		अगर (viid < 0) अणु
			dev_err(&pdev->dev,
				"cannot allocate VI for port %d: err=%d\n",
				port_id, viid);
			err = viid;
			जाओ err_मुक्त_dev;
		पूर्ण
		pi->viid = viid;

		/*
		 * Initialize the hardware/software state क्रम the port.
		 */
		err = t4vf_port_init(adapter, pidx);
		अगर (err) अणु
			dev_err(&pdev->dev, "cannot initialize port %d\n",
				pidx);
			जाओ err_मुक्त_dev;
		पूर्ण

		err = t4vf_get_vf_mac_acl(adapter, port_id, &naddr, mac);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"unable to determine MAC ACL address, "
				"continuing anyway.. (status %d)\n", err);
		पूर्ण अन्यथा अगर (naddr && adapter->params.vfres.nvi == 1) अणु
			काष्ठा sockaddr addr;

			ether_addr_copy(addr.sa_data, mac);
			err = cxgb4vf_set_mac_addr(netdev, &addr);
			अगर (err) अणु
				dev_err(&pdev->dev,
					"unable to set MAC address %pM\n",
					mac);
				जाओ err_मुक्त_dev;
			पूर्ण
			dev_info(&pdev->dev,
				 "Using assigned MAC ACL: %pM\n", mac);
		पूर्ण
	पूर्ण

	/* See what पूर्णांकerrupts we'll be using.  If we've been configured to
	 * use MSI-X पूर्णांकerrupts, try to enable them but fall back to using
	 * MSI पूर्णांकerrupts अगर we can't enable MSI-X interrupts.  If we can't
	 * get MSI पूर्णांकerrupts we bail with the error.
	 */
	अगर (msi == MSI_MSIX && enable_msix(adapter) == 0)
		adapter->flags |= CXGB4VF_USING_MSIX;
	अन्यथा अणु
		अगर (msi == MSI_MSIX) अणु
			dev_info(adapter->pdev_dev,
				 "Unable to use MSI-X Interrupts; falling "
				 "back to MSI Interrupts\n");

			/* We're going to need a Forwarded Interrupt Queue so
			 * that may cut पूर्णांकo how many Queue Sets we can
			 * support.
			 */
			msi = MSI_MSI;
			size_nports_qsets(adapter);
		पूर्ण
		err = pci_enable_msi(pdev);
		अगर (err) अणु
			dev_err(&pdev->dev, "Unable to allocate MSI Interrupts;"
				" err=%d\n", err);
			जाओ err_मुक्त_dev;
		पूर्ण
		adapter->flags |= CXGB4VF_USING_MSI;
	पूर्ण

	/* Now that we know how many "ports" we have and what पूर्णांकerrupt
	 * mechanism we're going to use, we can configure our queue resources.
	 */
	cfg_queues(adapter);

	/*
	 * The "card" is now पढ़ोy to go.  If any errors occur during device
	 * registration we करो not fail the whole "card" but rather proceed
	 * only with the ports we manage to रेजिस्टर successfully.  However we
	 * must रेजिस्टर at least one net device.
	 */
	क्रम_each_port(adapter, pidx) अणु
		काष्ठा port_info *pi = netdev_priv(adapter->port[pidx]);
		netdev = adapter->port[pidx];
		अगर (netdev == शून्य)
			जारी;

		netअगर_set_real_num_tx_queues(netdev, pi->nqsets);
		netअगर_set_real_num_rx_queues(netdev, pi->nqsets);

		err = रेजिस्टर_netdev(netdev);
		अगर (err) अणु
			dev_warn(&pdev->dev, "cannot register net device %s,"
				 " skipping\n", netdev->name);
			जारी;
		पूर्ण

		netअगर_carrier_off(netdev);
		set_bit(pidx, &adapter->रेजिस्टरed_device_map);
	पूर्ण
	अगर (adapter->रेजिस्टरed_device_map == 0) अणु
		dev_err(&pdev->dev, "could not register any net devices\n");
		जाओ err_disable_पूर्णांकerrupts;
	पूर्ण

	/*
	 * Set up our debugfs entries.
	 */
	अगर (!IS_ERR_OR_शून्य(cxgb4vf_debugfs_root)) अणु
		adapter->debugfs_root =
			debugfs_create_dir(pci_name(pdev),
					   cxgb4vf_debugfs_root);
		setup_debugfs(adapter);
	पूर्ण

	/*
	 * Prपूर्णांक a लघु notice on the existence and configuration of the new
	 * VF network device ...
	 */
	क्रम_each_port(adapter, pidx) अणु
		dev_info(adapter->pdev_dev, "%s: Chelsio VF NIC PCIe %s\n",
			 adapter->port[pidx]->name,
			 (adapter->flags & CXGB4VF_USING_MSIX) ? "MSI-X" :
			 (adapter->flags & CXGB4VF_USING_MSI)  ? "MSI" : "");
	पूर्ण

	/*
	 * Return success!
	 */
	वापस 0;

	/*
	 * Error recovery and निकास code.  Unwind state that's been created
	 * so far and वापस the error.
	 */
err_disable_पूर्णांकerrupts:
	अगर (adapter->flags & CXGB4VF_USING_MSIX) अणु
		pci_disable_msix(adapter->pdev);
		adapter->flags &= ~CXGB4VF_USING_MSIX;
	पूर्ण अन्यथा अगर (adapter->flags & CXGB4VF_USING_MSI) अणु
		pci_disable_msi(adapter->pdev);
		adapter->flags &= ~CXGB4VF_USING_MSI;
	पूर्ण

err_मुक्त_dev:
	क्रम_each_port(adapter, pidx) अणु
		netdev = adapter->port[pidx];
		अगर (netdev == शून्य)
			जारी;
		pi = netdev_priv(netdev);
		अगर (pi->viid)
			t4vf_मुक्त_vi(adapter, pi->viid);
		अगर (test_bit(pidx, &adapter->रेजिस्टरed_device_map))
			unरेजिस्टर_netdev(netdev);
		मुक्त_netdev(netdev);
	पूर्ण

	अगर (!is_t4(adapter->params.chip))
		iounmap(adapter->bar2);

err_unmap_bar0:
	iounmap(adapter->regs);

err_मुक्त_adapter:
	kमुक्त(adapter->mbox_log);
	kमुक्त(adapter);

err_release_regions:
	pci_release_regions(pdev);
	pci_clear_master(pdev);

err_disable_device:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

/*
 * "Remove" a device: tear करोwn all kernel and driver state created in the
 * "probe" routine and quiesce the device (disable पूर्णांकerrupts, etc.).  (Note
 * that this is called "remove_one" in the PF Driver.)
 */
अटल व्योम cxgb4vf_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा hash_mac_addr *entry, *पंचांगp;

	/*
	 * Tear करोwn driver state associated with device.
	 */
	अगर (adapter) अणु
		पूर्णांक pidx;

		/*
		 * Stop all of our activity.  Unरेजिस्टर network port,
		 * disable पूर्णांकerrupts, etc.
		 */
		क्रम_each_port(adapter, pidx)
			अगर (test_bit(pidx, &adapter->रेजिस्टरed_device_map))
				unरेजिस्टर_netdev(adapter->port[pidx]);
		t4vf_sge_stop(adapter);
		अगर (adapter->flags & CXGB4VF_USING_MSIX) अणु
			pci_disable_msix(adapter->pdev);
			adapter->flags &= ~CXGB4VF_USING_MSIX;
		पूर्ण अन्यथा अगर (adapter->flags & CXGB4VF_USING_MSI) अणु
			pci_disable_msi(adapter->pdev);
			adapter->flags &= ~CXGB4VF_USING_MSI;
		पूर्ण

		/*
		 * Tear करोwn our debugfs entries.
		 */
		अगर (!IS_ERR_OR_शून्य(adapter->debugfs_root)) अणु
			cleanup_debugfs(adapter);
			debugfs_हटाओ_recursive(adapter->debugfs_root);
		पूर्ण

		/*
		 * Free all of the various resources which we've acquired ...
		 */
		t4vf_मुक्त_sge_resources(adapter);
		क्रम_each_port(adapter, pidx) अणु
			काष्ठा net_device *netdev = adapter->port[pidx];
			काष्ठा port_info *pi;

			अगर (netdev == शून्य)
				जारी;

			pi = netdev_priv(netdev);
			अगर (pi->viid)
				t4vf_मुक्त_vi(adapter, pi->viid);
			मुक्त_netdev(netdev);
		पूर्ण
		iounmap(adapter->regs);
		अगर (!is_t4(adapter->params.chip))
			iounmap(adapter->bar2);
		kमुक्त(adapter->mbox_log);
		list_क्रम_each_entry_safe(entry, पंचांगp, &adapter->mac_hlist,
					 list) अणु
			list_del(&entry->list);
			kमुक्त(entry);
		पूर्ण
		kमुक्त(adapter);
	पूर्ण

	/*
	 * Disable the device and release its PCI resources.
	 */
	pci_disable_device(pdev);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
पूर्ण

/*
 * "Shutdown" quiesce the device, stopping Ingress Packet and Interrupt
 * delivery.
 */
अटल व्योम cxgb4vf_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adapter *adapter;
	पूर्णांक pidx;

	adapter = pci_get_drvdata(pdev);
	अगर (!adapter)
		वापस;

	/* Disable all Virtual Interfaces.  This will shut करोwn the
	 * delivery of all ingress packets पूर्णांकo the chip क्रम these
	 * Virtual Interfaces.
	 */
	क्रम_each_port(adapter, pidx)
		अगर (test_bit(pidx, &adapter->रेजिस्टरed_device_map))
			unरेजिस्टर_netdev(adapter->port[pidx]);

	/* Free up all Queues which will prevent further DMA and
	 * Interrupts allowing various पूर्णांकernal pathways to drain.
	 */
	t4vf_sge_stop(adapter);
	अगर (adapter->flags & CXGB4VF_USING_MSIX) अणु
		pci_disable_msix(adapter->pdev);
		adapter->flags &= ~CXGB4VF_USING_MSIX;
	पूर्ण अन्यथा अगर (adapter->flags & CXGB4VF_USING_MSI) अणु
		pci_disable_msi(adapter->pdev);
		adapter->flags &= ~CXGB4VF_USING_MSI;
	पूर्ण

	/*
	 * Free up all Queues which will prevent further DMA and
	 * Interrupts allowing various पूर्णांकernal pathways to drain.
	 */
	t4vf_मुक्त_sge_resources(adapter);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

/* Macros needed to support the PCI Device ID Table ...
 */
#घोषणा CH_PCI_DEVICE_ID_TABLE_DEFINE_BEGIN \
	अटल स्थिर काष्ठा pci_device_id cxgb4vf_pci_tbl[] = अणु
#घोषणा CH_PCI_DEVICE_ID_FUNCTION	0x8

#घोषणा CH_PCI_ID_TABLE_ENTRY(devid) \
		अणु PCI_VDEVICE(CHELSIO, (devid)), 0 पूर्ण

#घोषणा CH_PCI_DEVICE_ID_TABLE_DEFINE_END अणु 0, पूर्ण पूर्ण

#समावेश "../cxgb4/t4_pci_id_tbl.h"

MODULE_DESCRIPTION(DRV_DESC);
MODULE_AUTHOR("Chelsio Communications");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DEVICE_TABLE(pci, cxgb4vf_pci_tbl);

अटल काष्ठा pci_driver cxgb4vf_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= cxgb4vf_pci_tbl,
	.probe		= cxgb4vf_pci_probe,
	.हटाओ		= cxgb4vf_pci_हटाओ,
	.shutकरोwn	= cxgb4vf_pci_shutकरोwn,
पूर्ण;

/*
 * Initialize global driver state.
 */
अटल पूर्णांक __init cxgb4vf_module_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * Vet our module parameters.
	 */
	अगर (msi != MSI_MSIX && msi != MSI_MSI) अणु
		pr_warn("bad module parameter msi=%d; must be %d (MSI-X or MSI) or %d (MSI)\n",
			msi, MSI_MSIX, MSI_MSI);
		वापस -EINVAL;
	पूर्ण

	/* Debugfs support is optional, debugfs will warn अगर this fails */
	cxgb4vf_debugfs_root = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	ret = pci_रेजिस्टर_driver(&cxgb4vf_driver);
	अगर (ret < 0)
		debugfs_हटाओ(cxgb4vf_debugfs_root);
	वापस ret;
पूर्ण

/*
 * Tear करोwn global driver state.
 */
अटल व्योम __निकास cxgb4vf_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cxgb4vf_driver);
	debugfs_हटाओ(cxgb4vf_debugfs_root);
पूर्ण

module_init(cxgb4vf_module_init);
module_निकास(cxgb4vf_module_निकास);
