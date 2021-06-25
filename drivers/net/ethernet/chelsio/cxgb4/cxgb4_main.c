<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
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

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/crc32.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/init.h>
#समावेश <linux/log2.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sockios.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <net/neighbour.h>
#समावेश <net/netevent.h>
#समावेश <net/addrconf.h>
#समावेश <net/bonding.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/crash_dump.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/xfrm.h>
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
#समावेश <net/tls.h>
#पूर्ण_अगर

#समावेश "cxgb4.h"
#समावेश "cxgb4_filter.h"
#समावेश "t4_regs.h"
#समावेश "t4_values.h"
#समावेश "t4_msg.h"
#समावेश "t4fw_api.h"
#समावेश "t4fw_version.h"
#समावेश "cxgb4_dcb.h"
#समावेश "srq.h"
#समावेश "cxgb4_debugfs.h"
#समावेश "clip_tbl.h"
#समावेश "l2t.h"
#समावेश "smt.h"
#समावेश "sched.h"
#समावेश "cxgb4_tc_u32.h"
#समावेश "cxgb4_tc_flower.h"
#समावेश "cxgb4_tc_mqprio.h"
#समावेश "cxgb4_tc_matchall.h"
#समावेश "cxgb4_ptp.h"
#समावेश "cxgb4_cudbg.h"

अक्षर cxgb4_driver_name[] = KBUILD_MODNAME;

#घोषणा DRV_DESC "Chelsio T4/T5/T6 Network Driver"

#घोषणा DFLT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK | \
			 NETIF_MSG_TIMER | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP |\
			 NETIF_MSG_RX_ERR | NETIF_MSG_TX_ERR)

/* Macros needed to support the PCI Device ID Table ...
 */
#घोषणा CH_PCI_DEVICE_ID_TABLE_DEFINE_BEGIN \
	अटल स्थिर काष्ठा pci_device_id cxgb4_pci_tbl[] = अणु
#घोषणा CXGB4_UNIFIED_PF 0x4

#घोषणा CH_PCI_DEVICE_ID_FUNCTION CXGB4_UNIFIED_PF

/* Include PCI Device IDs क्रम both PF4 and PF0-3 so our PCI probe() routine is
 * called क्रम both.
 */
#घोषणा CH_PCI_DEVICE_ID_FUNCTION2 0x0

#घोषणा CH_PCI_ID_TABLE_ENTRY(devid) \
		अणुPCI_VDEVICE(CHELSIO, (devid)), CXGB4_UNIFIED_PFपूर्ण

#घोषणा CH_PCI_DEVICE_ID_TABLE_DEFINE_END \
		अणु 0, पूर्ण \
	पूर्ण

#समावेश "t4_pci_id_tbl.h"

#घोषणा FW4_FNAME "cxgb4/t4fw.bin"
#घोषणा FW5_FNAME "cxgb4/t5fw.bin"
#घोषणा FW6_FNAME "cxgb4/t6fw.bin"
#घोषणा FW4_CFNAME "cxgb4/t4-config.txt"
#घोषणा FW5_CFNAME "cxgb4/t5-config.txt"
#घोषणा FW6_CFNAME "cxgb4/t6-config.txt"
#घोषणा PHY_AQ1202_FIRMWARE "cxgb4/aq1202_fw.cld"
#घोषणा PHY_BCM84834_FIRMWARE "cxgb4/bcm8483.bin"
#घोषणा PHY_AQ1202_DEVICEID 0x4409
#घोषणा PHY_BCM84834_DEVICEID 0x4486

MODULE_DESCRIPTION(DRV_DESC);
MODULE_AUTHOR("Chelsio Communications");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DEVICE_TABLE(pci, cxgb4_pci_tbl);
MODULE_FIRMWARE(FW4_FNAME);
MODULE_FIRMWARE(FW5_FNAME);
MODULE_FIRMWARE(FW6_FNAME);

/*
 * The driver uses the best पूर्णांकerrupt scheme available on a platक्रमm in the
 * order MSI-X, MSI, legacy INTx पूर्णांकerrupts.  This parameter determines which
 * of these schemes the driver may consider as follows:
 *
 * msi = 2: choose from among all three options
 * msi = 1: only consider MSI and INTx पूर्णांकerrupts
 * msi = 0: क्रमce INTx पूर्णांकerrupts
 */
अटल पूर्णांक msi = 2;

module_param(msi, पूर्णांक, 0644);
MODULE_PARM_DESC(msi, "whether to use INTx (0), MSI (1) or MSI-X (2)");

/*
 * Normally we tell the chip to deliver Ingress Packets पूर्णांकo our DMA buffers
 * offset by 2 bytes in order to have the IP headers line up on 4-byte
 * boundaries.  This is a requirement क्रम many architectures which will throw
 * a machine check fault अगर an attempt is made to access one of the 4-byte IP
 * header fields on a non-4-byte boundary.  And it's a major perक्रमmance issue
 * even on some architectures which allow it like some implementations of the
 * x86 ISA.  However, some architectures करोn't mind this and क्रम some very
 * edge-हाल perक्रमmance sensitive applications (like क्रमwarding large volumes
 * of small packets), setting this DMA offset to 0 will decrease the number of
 * PCI-E Bus transfers enough to measurably affect perक्रमmance.
 */
अटल पूर्णांक rx_dma_offset = 2;

/* TX Queue select used to determine what algorithm to use क्रम selecting TX
 * queue. Select between the kernel provided function (select_queue=0) or user
 * cxgb_select_queue function (select_queue=1)
 *
 * Default: select_queue=0
 */
अटल पूर्णांक select_queue;
module_param(select_queue, पूर्णांक, 0644);
MODULE_PARM_DESC(select_queue,
		 "Select between kernel provided method of selecting or driver method of selecting TX queue. Default is kernel method.");

अटल काष्ठा dentry *cxgb4_debugfs_root;

LIST_HEAD(adapter_list);
DEFINE_MUTEX(uld_mutex);
LIST_HEAD(uld_list);

अटल पूर्णांक cfg_queues(काष्ठा adapter *adap);

अटल व्योम link_report(काष्ठा net_device *dev)
अणु
	अगर (!netअगर_carrier_ok(dev))
		netdev_info(dev, "link down\n");
	अन्यथा अणु
		अटल स्थिर अक्षर *fc[] = अणु "no", "Rx", "Tx", "Tx/Rx" पूर्ण;

		स्थिर अक्षर *s;
		स्थिर काष्ठा port_info *p = netdev_priv(dev);

		चयन (p->link_cfg.speed) अणु
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
		हाल 50000:
			s = "50Gbps";
			अवरोध;
		हाल 100000:
			s = "100Gbps";
			अवरोध;
		शेष:
			pr_info("%s: unsupported speed: %d\n",
				dev->name, p->link_cfg.speed);
			वापस;
		पूर्ण

		netdev_info(dev, "link up, %s, full-duplex, %s PAUSE\n", s,
			    fc[p->link_cfg.fc]);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
/* Set up/tear करोwn Data Center Bridging Priority mapping क्रम a net device. */
अटल व्योम dcb_tx_queue_prio_enable(काष्ठा net_device *dev, पूर्णांक enable)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge_eth_txq *txq = &adap->sge.ethtxq[pi->first_qset];
	पूर्णांक i;

	/* We use a simple mapping of Port TX Queue Index to DCB
	 * Priority when we're enabling DCB.
	 */
	क्रम (i = 0; i < pi->nqsets; i++, txq++) अणु
		u32 name, value;
		पूर्णांक err;

		name = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
			FW_PARAMS_PARAM_X_V(
				FW_PARAMS_PARAM_DMAQ_EQ_DCBPRIO_ETH) |
			FW_PARAMS_PARAM_YZ_V(txq->q.cntxt_id));
		value = enable ? i : 0xffffffff;

		/* Since we can be called जबतक atomic (from "पूर्णांकerrupt
		 * level") we need to issue the Set Parameters Commannd
		 * without sleeping (समयout < 0).
		 */
		err = t4_set_params_समयout(adap, adap->mbox, adap->pf, 0, 1,
					    &name, &value,
					    -FW_CMD_MAX_TIMEOUT);

		अगर (err)
			dev_err(adap->pdev_dev,
				"Can't %s DCB Priority on port %d, TX Queue %d: err=%d\n",
				enable ? "set" : "unset", pi->port_id, i, -err);
		अन्यथा
			txq->dcb_prio = enable ? value : 0;
	पूर्ण
पूर्ण

पूर्णांक cxgb4_dcb_enabled(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);

	अगर (!pi->dcb.enabled)
		वापस 0;

	वापस ((pi->dcb.state == CXGB4_DCB_STATE_FW_ALLSYNCED) ||
		(pi->dcb.state == CXGB4_DCB_STATE_HOST));
पूर्ण
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_DCB */

व्योम t4_os_link_changed(काष्ठा adapter *adapter, पूर्णांक port_id, पूर्णांक link_stat)
अणु
	काष्ठा net_device *dev = adapter->port[port_id];

	/* Skip changes from disabled ports. */
	अगर (netअगर_running(dev) && link_stat != netअगर_carrier_ok(dev)) अणु
		अगर (link_stat)
			netअगर_carrier_on(dev);
		अन्यथा अणु
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
			अगर (cxgb4_dcb_enabled(dev)) अणु
				cxgb4_dcb_reset(dev);
				dcb_tx_queue_prio_enable(dev, false);
			पूर्ण
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_DCB */
			netअगर_carrier_off(dev);
		पूर्ण

		link_report(dev);
	पूर्ण
पूर्ण

व्योम t4_os_porपंचांगod_changed(काष्ठा adapter *adap, पूर्णांक port_id)
अणु
	अटल स्थिर अक्षर *mod_str[] = अणु
		शून्य, "LR", "SR", "ER", "passive DA", "active DA", "LRM"
	पूर्ण;

	काष्ठा net_device *dev = adap->port[port_id];
	काष्ठा port_info *pi = netdev_priv(dev);

	अगर (pi->mod_type == FW_PORT_MOD_TYPE_NONE)
		netdev_info(dev, "port module unplugged\n");
	अन्यथा अगर (pi->mod_type < ARRAY_SIZE(mod_str))
		netdev_info(dev, "%s module inserted\n", mod_str[pi->mod_type]);
	अन्यथा अगर (pi->mod_type == FW_PORT_MOD_TYPE_NOTSUPPORTED)
		netdev_info(dev, "%s: unsupported port module inserted\n",
			    dev->name);
	अन्यथा अगर (pi->mod_type == FW_PORT_MOD_TYPE_UNKNOWN)
		netdev_info(dev, "%s: unknown port module inserted\n",
			    dev->name);
	अन्यथा अगर (pi->mod_type == FW_PORT_MOD_TYPE_ERROR)
		netdev_info(dev, "%s: transceiver module error\n", dev->name);
	अन्यथा
		netdev_info(dev, "%s: unknown module type %d inserted\n",
			    dev->name, pi->mod_type);

	/* If the पूर्णांकerface is running, then we'll need any "sticky" Link
	 * Parameters reकरोne with a new Transceiver Module.
	 */
	pi->link_cfg.reकरो_l1cfg = netअगर_running(dev);
पूर्ण

पूर्णांक dbfअगरo_पूर्णांक_thresh = 10; /* 10 == 640 entry threshold */
module_param(dbfअगरo_पूर्णांक_thresh, पूर्णांक, 0644);
MODULE_PARM_DESC(dbfअगरo_पूर्णांक_thresh, "doorbell fifo interrupt threshold");

/*
 * usecs to sleep जबतक draining the dbfअगरo
 */
अटल पूर्णांक dbfअगरo_drain_delay = 1000;
module_param(dbfअगरo_drain_delay, पूर्णांक, 0644);
MODULE_PARM_DESC(dbfअगरo_drain_delay,
		 "usecs to sleep while draining the dbfifo");

अटल अंतरभूत पूर्णांक cxgb4_set_addr_hash(काष्ठा port_info *pi)
अणु
	काष्ठा adapter *adap = pi->adapter;
	u64 vec = 0;
	bool ucast = false;
	काष्ठा hash_mac_addr *entry;

	/* Calculate the hash vector क्रम the updated list and program it */
	list_क्रम_each_entry(entry, &adap->mac_hlist, list) अणु
		ucast |= is_unicast_ether_addr(entry->addr);
		vec |= (1ULL << hash_mac_addr(entry->addr));
	पूर्ण
	वापस t4_set_addr_hash(adap, adap->mbox, pi->viid, ucast,
				vec, false);
पूर्ण

अटल पूर्णांक cxgb4_mac_sync(काष्ठा net_device *netdev, स्थिर u8 *mac_addr)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक ret;
	u64 mhash = 0;
	u64 uhash = 0;
	/* idx stores the index of allocated filters,
	 * its size should be modअगरied based on the number of
	 * MAC addresses that we allocate filters क्रम
	 */

	u16 idx[1] = अणुपूर्ण;
	bool मुक्त = false;
	bool ucast = is_unicast_ether_addr(mac_addr);
	स्थिर u8 *maclist[1] = अणुmac_addrपूर्ण;
	काष्ठा hash_mac_addr *new_entry;

	ret = cxgb4_alloc_mac_filt(adap, pi->viid, मुक्त, 1, maclist,
				   idx, ucast ? &uhash : &mhash, false);
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
		list_add_tail(&new_entry->list, &adap->mac_hlist);
		ret = cxgb4_set_addr_hash(pi);
	पूर्ण
out:
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक cxgb4_mac_unsync(काष्ठा net_device *netdev, स्थिर u8 *mac_addr)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक ret;
	स्थिर u8 *maclist[1] = अणुmac_addrपूर्ण;
	काष्ठा hash_mac_addr *entry, *पंचांगp;

	/* If the MAC address to be हटाओd is in the hash addr
	 * list, delete it from the list and update hash vector
	 */
	list_क्रम_each_entry_safe(entry, पंचांगp, &adap->mac_hlist, list) अणु
		अगर (ether_addr_equal(entry->addr, mac_addr)) अणु
			list_del(&entry->list);
			kमुक्त(entry);
			वापस cxgb4_set_addr_hash(pi);
		पूर्ण
	पूर्ण

	ret = cxgb4_मुक्त_mac_filt(adap, pi->viid, 1, maclist, false);
	वापस ret < 0 ? -EINVAL : 0;
पूर्ण

/*
 * Set Rx properties of a port, such as promiscruity, address filters, and MTU.
 * If @mtu is -1 it is left unchanged.
 */
अटल पूर्णांक set_rxmode(काष्ठा net_device *dev, पूर्णांक mtu, bool sleep_ok)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	__dev_uc_sync(dev, cxgb4_mac_sync, cxgb4_mac_unsync);
	__dev_mc_sync(dev, cxgb4_mac_sync, cxgb4_mac_unsync);

	वापस t4_set_rxmode(adapter, adapter->mbox, pi->viid, pi->viid_mirror,
			     mtu, (dev->flags & IFF_PROMISC) ? 1 : 0,
			     (dev->flags & IFF_ALLMULTI) ? 1 : 0, 1, -1,
			     sleep_ok);
पूर्ण

/**
 *	cxgb4_change_mac - Update match filter क्रम a MAC address.
 *	@pi: the port_info
 *	@viid: the VI id
 *	@tcam_idx: TCAM index of existing filter क्रम old value of MAC address,
 *		   or -1
 *	@addr: the new MAC address value
 *	@persist: whether a new MAC allocation should be persistent
 *	@smt_idx: the destination to store the new SMT index.
 *
 *	Modअगरies an MPS filter and sets it to the new MAC address अगर
 *	@tcam_idx >= 0, or adds the MAC address to a new filter अगर
 *	@tcam_idx < 0. In the latter हाल the address is added persistently
 *	अगर @persist is %true.
 *	Addresses are programmed to hash region, अगर tcam runs out of entries.
 *
 */
पूर्णांक cxgb4_change_mac(काष्ठा port_info *pi, अचिन्हित पूर्णांक viid,
		     पूर्णांक *tcam_idx, स्थिर u8 *addr, bool persist,
		     u8 *smt_idx)
अणु
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा hash_mac_addr *entry, *new_entry;
	पूर्णांक ret;

	ret = t4_change_mac(adapter, adapter->mbox, viid,
			    *tcam_idx, addr, persist, smt_idx);
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
		ret = cxgb4_set_addr_hash(pi);
	पूर्ण अन्यथा अगर (ret >= 0) अणु
		*tcam_idx = ret;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 *	link_start - enable a port
 *	@dev: the port to enable
 *
 *	Perक्रमms the MAC and PHY actions needed to enable a port.
 */
अटल पूर्णांक link_start(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	अचिन्हित पूर्णांक mb = pi->adapter->mbox;
	पूर्णांक ret;

	/*
	 * We करो not set address filters and promiscuity here, the stack करोes
	 * that step explicitly.
	 */
	ret = t4_set_rxmode(pi->adapter, mb, pi->viid, pi->viid_mirror,
			    dev->mtu, -1, -1, -1,
			    !!(dev->features & NETIF_F_HW_VLAN_CTAG_RX), true);
	अगर (ret == 0)
		ret = cxgb4_update_mac_filt(pi, pi->viid, &pi->xact_addr_filt,
					    dev->dev_addr, true, &pi->smt_idx);
	अगर (ret == 0)
		ret = t4_link_l1cfg(pi->adapter, mb, pi->tx_chan,
				    &pi->link_cfg);
	अगर (ret == 0) अणु
		local_bh_disable();
		ret = t4_enable_pi_params(pi->adapter, mb, pi, true,
					  true, CXGB4_DCB_ENABLED);
		local_bh_enable();
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
/* Handle a Data Center Bridging update message from the firmware. */
अटल व्योम dcb_rpl(काष्ठा adapter *adap, स्थिर काष्ठा fw_port_cmd *pcmd)
अणु
	पूर्णांक port = FW_PORT_CMD_PORTID_G(ntohl(pcmd->op_to_portid));
	काष्ठा net_device *dev = adap->port[adap->chan_map[port]];
	पूर्णांक old_dcb_enabled = cxgb4_dcb_enabled(dev);
	पूर्णांक new_dcb_enabled;

	cxgb4_dcb_handle_fw_update(adap, pcmd);
	new_dcb_enabled = cxgb4_dcb_enabled(dev);

	/* If the DCB has become enabled or disabled on the port then we're
	 * going to need to set up/tear करोwn DCB Priority parameters क्रम the
	 * TX Queues associated with the port.
	 */
	अगर (new_dcb_enabled != old_dcb_enabled)
		dcb_tx_queue_prio_enable(dev, new_dcb_enabled);
पूर्ण
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_DCB */

/* Response queue handler क्रम the FW event queue.
 */
अटल पूर्णांक fwevtq_handler(काष्ठा sge_rspq *q, स्थिर __be64 *rsp,
			  स्थिर काष्ठा pkt_gl *gl)
अणु
	u8 opcode = ((स्थिर काष्ठा rss_header *)rsp)->opcode;

	rsp++;                                          /* skip RSS header */

	/* FW can send EGR_UPDATEs encapsulated in a CPL_FW4_MSG.
	 */
	अगर (unlikely(opcode == CPL_FW4_MSG &&
	   ((स्थिर काष्ठा cpl_fw4_msg *)rsp)->type == FW_TYPE_RSSCPL)) अणु
		rsp++;
		opcode = ((स्थिर काष्ठा rss_header *)rsp)->opcode;
		rsp++;
		अगर (opcode != CPL_SGE_EGR_UPDATE) अणु
			dev_err(q->adap->pdev_dev, "unexpected FW4/CPL %#x on FW event queue\n"
				, opcode);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (likely(opcode == CPL_SGE_EGR_UPDATE)) अणु
		स्थिर काष्ठा cpl_sge_egr_update *p = (व्योम *)rsp;
		अचिन्हित पूर्णांक qid = EGR_QID_G(ntohl(p->opcode_qid));
		काष्ठा sge_txq *txq;

		txq = q->adap->sge.egr_map[qid - q->adap->sge.egr_start];
		txq->restarts++;
		अगर (txq->q_type == CXGB4_TXQ_ETH) अणु
			काष्ठा sge_eth_txq *eq;

			eq = container_of(txq, काष्ठा sge_eth_txq, q);
			t4_sge_eth_txq_egress_update(q->adap, eq, -1);
		पूर्ण अन्यथा अणु
			काष्ठा sge_uld_txq *oq;

			oq = container_of(txq, काष्ठा sge_uld_txq, q);
			tasklet_schedule(&oq->qresume_tsk);
		पूर्ण
	पूर्ण अन्यथा अगर (opcode == CPL_FW6_MSG || opcode == CPL_FW4_MSG) अणु
		स्थिर काष्ठा cpl_fw6_msg *p = (व्योम *)rsp;

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
		स्थिर काष्ठा fw_port_cmd *pcmd = (स्थिर व्योम *)p->data;
		अचिन्हित पूर्णांक cmd = FW_CMD_OP_G(ntohl(pcmd->op_to_portid));
		अचिन्हित पूर्णांक action =
			FW_PORT_CMD_ACTION_G(ntohl(pcmd->action_to_len16));

		अगर (cmd == FW_PORT_CMD &&
		    (action == FW_PORT_ACTION_GET_PORT_INFO ||
		     action == FW_PORT_ACTION_GET_PORT_INFO32)) अणु
			पूर्णांक port = FW_PORT_CMD_PORTID_G(
					be32_to_cpu(pcmd->op_to_portid));
			काष्ठा net_device *dev;
			पूर्णांक dcbxdis, state_input;

			dev = q->adap->port[q->adap->chan_map[port]];
			dcbxdis = (action == FW_PORT_ACTION_GET_PORT_INFO
			  ? !!(pcmd->u.info.dcbxdis_pkd & FW_PORT_CMD_DCBXDIS_F)
			  : !!(be32_to_cpu(pcmd->u.info32.lstatus32_to_cbllen32)
			       & FW_PORT_CMD_DCBXDIS32_F));
			state_input = (dcbxdis
				       ? CXGB4_DCB_INPUT_FW_DISABLED
				       : CXGB4_DCB_INPUT_FW_ENABLED);

			cxgb4_dcb_state_fsm(dev, state_input);
		पूर्ण

		अगर (cmd == FW_PORT_CMD &&
		    action == FW_PORT_ACTION_L2_DCB_CFG)
			dcb_rpl(q->adap, pcmd);
		अन्यथा
#पूर्ण_अगर
			अगर (p->type == 0)
				t4_handle_fw_rpl(q->adap, p->data);
	पूर्ण अन्यथा अगर (opcode == CPL_L2T_WRITE_RPL) अणु
		स्थिर काष्ठा cpl_l2t_ग_लिखो_rpl *p = (व्योम *)rsp;

		करो_l2t_ग_लिखो_rpl(q->adap, p);
	पूर्ण अन्यथा अगर (opcode == CPL_SMT_WRITE_RPL) अणु
		स्थिर काष्ठा cpl_smt_ग_लिखो_rpl *p = (व्योम *)rsp;

		करो_smt_ग_लिखो_rpl(q->adap, p);
	पूर्ण अन्यथा अगर (opcode == CPL_SET_TCB_RPL) अणु
		स्थिर काष्ठा cpl_set_tcb_rpl *p = (व्योम *)rsp;

		filter_rpl(q->adap, p);
	पूर्ण अन्यथा अगर (opcode == CPL_ACT_OPEN_RPL) अणु
		स्थिर काष्ठा cpl_act_खोलो_rpl *p = (व्योम *)rsp;

		hash_filter_rpl(q->adap, p);
	पूर्ण अन्यथा अगर (opcode == CPL_ABORT_RPL_RSS) अणु
		स्थिर काष्ठा cpl_पात_rpl_rss *p = (व्योम *)rsp;

		hash_del_filter_rpl(q->adap, p);
	पूर्ण अन्यथा अगर (opcode == CPL_SRQ_TABLE_RPL) अणु
		स्थिर काष्ठा cpl_srq_table_rpl *p = (व्योम *)rsp;

		करो_srq_table_rpl(q->adap, p);
	पूर्ण अन्यथा
		dev_err(q->adap->pdev_dev,
			"unexpected CPL %#x on FW event queue\n", opcode);
out:
	वापस 0;
पूर्ण

अटल व्योम disable_msi(काष्ठा adapter *adapter)
अणु
	अगर (adapter->flags & CXGB4_USING_MSIX) अणु
		pci_disable_msix(adapter->pdev);
		adapter->flags &= ~CXGB4_USING_MSIX;
	पूर्ण अन्यथा अगर (adapter->flags & CXGB4_USING_MSI) अणु
		pci_disable_msi(adapter->pdev);
		adapter->flags &= ~CXGB4_USING_MSI;
	पूर्ण
पूर्ण

/*
 * Interrupt handler क्रम non-data events used with MSI-X.
 */
अटल irqवापस_t t4_nondata_पूर्णांकr(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा adapter *adap = cookie;
	u32 v = t4_पढ़ो_reg(adap, MYPF_REG(PL_PF_INT_CAUSE_A));

	अगर (v & PFSW_F) अणु
		adap->swपूर्णांकr = 1;
		t4_ग_लिखो_reg(adap, MYPF_REG(PL_PF_INT_CAUSE_A), v);
	पूर्ण
	अगर (adap->flags & CXGB4_MASTER_PF)
		t4_slow_पूर्णांकr_handler(adap);
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक cxgb4_set_msix_aff(काष्ठा adapter *adap, अचिन्हित लघु vec,
		       cpumask_var_t *aff_mask, पूर्णांक idx)
अणु
	पूर्णांक rv;

	अगर (!zalloc_cpumask_var(aff_mask, GFP_KERNEL)) अणु
		dev_err(adap->pdev_dev, "alloc_cpumask_var failed\n");
		वापस -ENOMEM;
	पूर्ण

	cpumask_set_cpu(cpumask_local_spपढ़ो(idx, dev_to_node(adap->pdev_dev)),
			*aff_mask);

	rv = irq_set_affinity_hपूर्णांक(vec, *aff_mask);
	अगर (rv)
		dev_warn(adap->pdev_dev,
			 "irq_set_affinity_hint %u failed %d\n",
			 vec, rv);

	वापस 0;
पूर्ण

व्योम cxgb4_clear_msix_aff(अचिन्हित लघु vec, cpumask_var_t aff_mask)
अणु
	irq_set_affinity_hपूर्णांक(vec, शून्य);
	मुक्त_cpumask_var(aff_mask);
पूर्ण

अटल पूर्णांक request_msix_queue_irqs(काष्ठा adapter *adap)
अणु
	काष्ठा sge *s = &adap->sge;
	काष्ठा msix_info *minfo;
	पूर्णांक err, ethqidx;

	अगर (s->fwevtq_msix_idx < 0)
		वापस -ENOMEM;

	err = request_irq(adap->msix_info[s->fwevtq_msix_idx].vec,
			  t4_sge_पूर्णांकr_msix, 0,
			  adap->msix_info[s->fwevtq_msix_idx].desc,
			  &s->fw_evtq);
	अगर (err)
		वापस err;

	क्रम_each_ethrxq(s, ethqidx) अणु
		minfo = s->ethrxq[ethqidx].msix;
		err = request_irq(minfo->vec,
				  t4_sge_पूर्णांकr_msix, 0,
				  minfo->desc,
				  &s->ethrxq[ethqidx].rspq);
		अगर (err)
			जाओ unwind;

		cxgb4_set_msix_aff(adap, minfo->vec,
				   &minfo->aff_mask, ethqidx);
	पूर्ण
	वापस 0;

unwind:
	जबतक (--ethqidx >= 0) अणु
		minfo = s->ethrxq[ethqidx].msix;
		cxgb4_clear_msix_aff(minfo->vec, minfo->aff_mask);
		मुक्त_irq(minfo->vec, &s->ethrxq[ethqidx].rspq);
	पूर्ण
	मुक्त_irq(adap->msix_info[s->fwevtq_msix_idx].vec, &s->fw_evtq);
	वापस err;
पूर्ण

अटल व्योम मुक्त_msix_queue_irqs(काष्ठा adapter *adap)
अणु
	काष्ठा sge *s = &adap->sge;
	काष्ठा msix_info *minfo;
	पूर्णांक i;

	मुक्त_irq(adap->msix_info[s->fwevtq_msix_idx].vec, &s->fw_evtq);
	क्रम_each_ethrxq(s, i) अणु
		minfo = s->ethrxq[i].msix;
		cxgb4_clear_msix_aff(minfo->vec, minfo->aff_mask);
		मुक्त_irq(minfo->vec, &s->ethrxq[i].rspq);
	पूर्ण
पूर्ण

अटल पूर्णांक setup_ppod_edram(काष्ठा adapter *adap)
अणु
	अचिन्हित पूर्णांक param, val;
	पूर्णांक ret;

	/* Driver sends FW_PARAMS_PARAM_DEV_PPOD_EDRAM पढ़ो command to check
	 * अगर firmware supports ppod edram feature or not. If firmware
	 * वापसs 1, then driver can enable this feature by sending
	 * FW_PARAMS_PARAM_DEV_PPOD_EDRAM ग_लिखो command with value 1 to
	 * enable ppod edram feature.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_PPOD_EDRAM));

	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1, &param, &val);
	अगर (ret < 0) अणु
		dev_warn(adap->pdev_dev,
			 "querying PPOD_EDRAM support failed: %d\n",
			 ret);
		वापस -1;
	पूर्ण

	अगर (val != 1)
		वापस -1;

	ret = t4_set_params(adap, adap->mbox, adap->pf, 0, 1, &param, &val);
	अगर (ret < 0) अणु
		dev_err(adap->pdev_dev,
			"setting PPOD_EDRAM failed: %d\n", ret);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adap_config_hpfilter(काष्ठा adapter *adapter)
अणु
	u32 param, val = 0;
	पूर्णांक ret;

	/* Enable HP filter region. Older fw will fail this request and
	 * it is fine.
	 */
	param = FW_PARAM_DEV(HPFILTER_REGION_SUPPORT);
	ret = t4_set_params(adapter, adapter->mbox, adapter->pf, 0,
			    1, &param, &val);

	/* An error means FW करोesn't know about HP filter support,
	 * it's not a problem, don't वापस an error.
	 */
	अगर (ret < 0)
		dev_err(adapter->pdev_dev,
			"HP filter region isn't supported by FW\n");
पूर्ण

अटल पूर्णांक cxgb4_config_rss(स्थिर काष्ठा port_info *pi, u16 *rss,
			    u16 rss_size, u16 viid)
अणु
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक ret;

	ret = t4_config_rss_range(adap, adap->mbox, viid, 0, rss_size, rss,
				  rss_size);
	अगर (ret)
		वापस ret;

	/* If Tunnel All Lookup isn't specअगरied in the global RSS
	 * Configuration, then we need to specअगरy a शेष Ingress
	 * Queue क्रम any ingress packets which aren't hashed.  We'll
	 * use our first ingress queue ...
	 */
	वापस t4_config_vi_rss(adap, adap->mbox, viid,
				FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F |
				FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F |
				FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F |
				FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F |
				FW_RSS_VI_CONFIG_CMD_UDPEN_F,
				rss[0]);
पूर्ण

/**
 *	cxgb4_ग_लिखो_rss - ग_लिखो the RSS table क्रम a given port
 *	@pi: the port
 *	@queues: array of queue indices क्रम RSS
 *
 *	Sets up the portion of the HW RSS table क्रम the port's VI to distribute
 *	packets to the Rx queues in @queues.
 *	Should never be called beक्रमe setting up sge eth rx queues
 */
पूर्णांक cxgb4_ग_लिखो_rss(स्थिर काष्ठा port_info *pi, स्थिर u16 *queues)
अणु
	काष्ठा adapter *adapter = pi->adapter;
	स्थिर काष्ठा sge_eth_rxq *rxq;
	पूर्णांक i, err;
	u16 *rss;

	rxq = &adapter->sge.ethrxq[pi->first_qset];
	rss = kदो_स्मृति_array(pi->rss_size, माप(u16), GFP_KERNEL);
	अगर (!rss)
		वापस -ENOMEM;

	/* map the queue indices to queue ids */
	क्रम (i = 0; i < pi->rss_size; i++, queues++)
		rss[i] = rxq[*queues].rspq.असल_id;

	err = cxgb4_config_rss(pi, rss, pi->rss_size, pi->viid);
	kमुक्त(rss);
	वापस err;
पूर्ण

/**
 *	setup_rss - configure RSS
 *	@adap: the adapter
 *
 *	Sets up RSS क्रम each port.
 */
अटल पूर्णांक setup_rss(काष्ठा adapter *adap)
अणु
	पूर्णांक i, j, err;

	क्रम_each_port(adap, i) अणु
		स्थिर काष्ठा port_info *pi = adap2pinfo(adap, i);

		/* Fill शेष values with equal distribution */
		क्रम (j = 0; j < pi->rss_size; j++)
			pi->rss[j] = j % pi->nqsets;

		err = cxgb4_ग_लिखो_rss(pi, pi->rss);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return the channel of the ingress queue with the given qid.
 */
अटल अचिन्हित पूर्णांक rxq_to_chan(स्थिर काष्ठा sge *p, अचिन्हित पूर्णांक qid)
अणु
	qid -= p->ingr_start;
	वापस netdev2pinfo(p->ingr_map[qid]->netdev)->tx_chan;
पूर्ण

व्योम cxgb4_quiesce_rx(काष्ठा sge_rspq *q)
अणु
	अगर (q->handler)
		napi_disable(&q->napi);
पूर्ण

/*
 * Wait until all NAPI handlers are descheduled.
 */
अटल व्योम quiesce_rx(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adap->sge.ingr_sz; i++) अणु
		काष्ठा sge_rspq *q = adap->sge.ingr_map[i];

		अगर (!q)
			जारी;

		cxgb4_quiesce_rx(q);
	पूर्ण
पूर्ण

/* Disable पूर्णांकerrupt and napi handler */
अटल व्योम disable_पूर्णांकerrupts(काष्ठा adapter *adap)
अणु
	काष्ठा sge *s = &adap->sge;

	अगर (adap->flags & CXGB4_FULL_INIT_DONE) अणु
		t4_पूर्णांकr_disable(adap);
		अगर (adap->flags & CXGB4_USING_MSIX) अणु
			मुक्त_msix_queue_irqs(adap);
			मुक्त_irq(adap->msix_info[s->nd_msix_idx].vec,
				 adap);
		पूर्ण अन्यथा अणु
			मुक्त_irq(adap->pdev->irq, adap);
		पूर्ण
		quiesce_rx(adap);
	पूर्ण
पूर्ण

व्योम cxgb4_enable_rx(काष्ठा adapter *adap, काष्ठा sge_rspq *q)
अणु
	अगर (q->handler)
		napi_enable(&q->napi);

	/* 0-increment GTS to start the समयr and enable पूर्णांकerrupts */
	t4_ग_लिखो_reg(adap, MYPF_REG(SGE_PF_GTS_A),
		     SEINTARM_V(q->पूर्णांकr_params) |
		     INGRESSQID_V(q->cntxt_id));
पूर्ण

/*
 * Enable NAPI scheduling and पूर्णांकerrupt generation क्रम all Rx queues.
 */
अटल व्योम enable_rx(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adap->sge.ingr_sz; i++) अणु
		काष्ठा sge_rspq *q = adap->sge.ingr_map[i];

		अगर (!q)
			जारी;

		cxgb4_enable_rx(adap, q);
	पूर्ण
पूर्ण

अटल पूर्णांक setup_non_data_पूर्णांकr(काष्ठा adapter *adap)
अणु
	पूर्णांक msix;

	adap->sge.nd_msix_idx = -1;
	अगर (!(adap->flags & CXGB4_USING_MSIX))
		वापस 0;

	/* Request MSI-X vector क्रम non-data पूर्णांकerrupt */
	msix = cxgb4_get_msix_idx_from_bmap(adap);
	अगर (msix < 0)
		वापस -ENOMEM;

	snम_लिखो(adap->msix_info[msix].desc,
		 माप(adap->msix_info[msix].desc),
		 "%s", adap->port[0]->name);

	adap->sge.nd_msix_idx = msix;
	वापस 0;
पूर्ण

अटल पूर्णांक setup_fw_sge_queues(काष्ठा adapter *adap)
अणु
	काष्ठा sge *s = &adap->sge;
	पूर्णांक msix, err = 0;

	biपंचांगap_zero(s->starving_fl, s->egr_sz);
	biपंचांगap_zero(s->txq_maperr, s->egr_sz);

	अगर (adap->flags & CXGB4_USING_MSIX) अणु
		s->fwevtq_msix_idx = -1;
		msix = cxgb4_get_msix_idx_from_bmap(adap);
		अगर (msix < 0)
			वापस -ENOMEM;

		snम_लिखो(adap->msix_info[msix].desc,
			 माप(adap->msix_info[msix].desc),
			 "%s-FWeventq", adap->port[0]->name);
	पूर्ण अन्यथा अणु
		err = t4_sge_alloc_rxq(adap, &s->पूर्णांकrq, false, adap->port[0], 0,
				       शून्य, शून्य, शून्य, -1);
		अगर (err)
			वापस err;
		msix = -((पूर्णांक)s->पूर्णांकrq.असल_id + 1);
	पूर्ण

	err = t4_sge_alloc_rxq(adap, &s->fw_evtq, true, adap->port[0],
			       msix, शून्य, fwevtq_handler, शून्य, -1);
	अगर (err && msix >= 0)
		cxgb4_मुक्त_msix_idx_in_bmap(adap, msix);

	s->fwevtq_msix_idx = msix;
	वापस err;
पूर्ण

/**
 *	setup_sge_queues - configure SGE Tx/Rx/response queues
 *	@adap: the adapter
 *
 *	Determines how many sets of SGE queues to use and initializes them.
 *	We support multiple queue sets per port अगर we have MSI-X, otherwise
 *	just one queue set per port.
 */
अटल पूर्णांक setup_sge_queues(काष्ठा adapter *adap)
अणु
	काष्ठा sge_uld_rxq_info *rxq_info = शून्य;
	काष्ठा sge *s = &adap->sge;
	अचिन्हित पूर्णांक cmplqid = 0;
	पूर्णांक err, i, j, msix = 0;

	अगर (is_uld(adap))
		rxq_info = s->uld_rxq_info[CXGB4_ULD_RDMA];

	अगर (!(adap->flags & CXGB4_USING_MSIX))
		msix = -((पूर्णांक)s->पूर्णांकrq.असल_id + 1);

	क्रम_each_port(adap, i) अणु
		काष्ठा net_device *dev = adap->port[i];
		काष्ठा port_info *pi = netdev_priv(dev);
		काष्ठा sge_eth_rxq *q = &s->ethrxq[pi->first_qset];
		काष्ठा sge_eth_txq *t = &s->ethtxq[pi->first_qset];

		क्रम (j = 0; j < pi->nqsets; j++, q++) अणु
			अगर (msix >= 0) अणु
				msix = cxgb4_get_msix_idx_from_bmap(adap);
				अगर (msix < 0) अणु
					err = msix;
					जाओ मुक्तout;
				पूर्ण

				snम_लिखो(adap->msix_info[msix].desc,
					 माप(adap->msix_info[msix].desc),
					 "%s-Rx%d", dev->name, j);
				q->msix = &adap->msix_info[msix];
			पूर्ण

			err = t4_sge_alloc_rxq(adap, &q->rspq, false, dev,
					       msix, &q->fl,
					       t4_ethrx_handler,
					       शून्य,
					       t4_get_tp_ch_map(adap,
								pi->tx_chan));
			अगर (err)
				जाओ मुक्तout;
			q->rspq.idx = j;
			स_रखो(&q->stats, 0, माप(q->stats));
		पूर्ण

		q = &s->ethrxq[pi->first_qset];
		क्रम (j = 0; j < pi->nqsets; j++, t++, q++) अणु
			err = t4_sge_alloc_eth_txq(adap, t, dev,
					netdev_get_tx_queue(dev, j),
					q->rspq.cntxt_id,
					!!(adap->flags & CXGB4_SGE_DBQ_TIMER));
			अगर (err)
				जाओ मुक्तout;
		पूर्ण
	पूर्ण

	क्रम_each_port(adap, i) अणु
		/* Note that cmplqid below is 0 अगर we करोn't
		 * have RDMA queues, and that's the right value.
		 */
		अगर (rxq_info)
			cmplqid	= rxq_info->uldrxq[i].rspq.cntxt_id;

		err = t4_sge_alloc_ctrl_txq(adap, &s->ctrlq[i], adap->port[i],
					    s->fw_evtq.cntxt_id, cmplqid);
		अगर (err)
			जाओ मुक्तout;
	पूर्ण

	अगर (!is_t4(adap->params.chip)) अणु
		err = t4_sge_alloc_eth_txq(adap, &s->ptptxq, adap->port[0],
					   netdev_get_tx_queue(adap->port[0], 0)
					   , s->fw_evtq.cntxt_id, false);
		अगर (err)
			जाओ मुक्तout;
	पूर्ण

	t4_ग_लिखो_reg(adap, is_t4(adap->params.chip) ?
				MPS_TRC_RSS_CONTROL_A :
				MPS_T5_TRC_RSS_CONTROL_A,
		     RSSCONTROL_V(netdev2pinfo(adap->port[0])->tx_chan) |
		     QUEUENUMBER_V(s->ethrxq[0].rspq.असल_id));
	वापस 0;
मुक्तout:
	dev_err(adap->pdev_dev, "Can't allocate queues, err=%d\n", -err);
	t4_मुक्त_sge_resources(adap);
	वापस err;
पूर्ण

अटल u16 cxgb_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			     काष्ठा net_device *sb_dev)
अणु
	पूर्णांक txq;

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	/* If a Data Center Bridging has been successfully negotiated on this
	 * link then we'll use the skb's priority to map it to a TX Queue.
	 * The skb's priority is determined via the VLAN Tag Priority Code
	 * Poपूर्णांक field.
	 */
	अगर (cxgb4_dcb_enabled(dev) && !is_kdump_kernel()) अणु
		u16 vlan_tci;
		पूर्णांक err;

		err = vlan_get_tag(skb, &vlan_tci);
		अगर (unlikely(err)) अणु
			अगर (net_ratelimit())
				netdev_warn(dev,
					    "TX Packet without VLAN Tag on DCB Link\n");
			txq = 0;
		पूर्ण अन्यथा अणु
			txq = (vlan_tci & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
#अगर_घोषित CONFIG_CHELSIO_T4_FCOE
			अगर (skb->protocol == htons(ETH_P_FCOE))
				txq = skb->priority & 0x7;
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */
		पूर्ण
		वापस txq;
	पूर्ण
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_DCB */

	अगर (dev->num_tc) अणु
		काष्ठा port_info *pi = netdev2pinfo(dev);
		u8 ver, proto;

		ver = ip_hdr(skb)->version;
		proto = (ver == 6) ? ipv6_hdr(skb)->nexthdr :
				     ip_hdr(skb)->protocol;

		/* Send unsupported traffic pattern to normal NIC queues. */
		txq = netdev_pick_tx(dev, skb, sb_dev);
		अगर (xfrm_offload(skb) || is_ptp_enabled(skb, dev) ||
		    skb->encapsulation ||
		    cxgb4_is_ktls_skb(skb) ||
		    (proto != IPPROTO_TCP && proto != IPPROTO_UDP))
			txq = txq % pi->nqsets;

		वापस txq;
	पूर्ण

	अगर (select_queue) अणु
		txq = (skb_rx_queue_recorded(skb)
			? skb_get_rx_queue(skb)
			: smp_processor_id());

		जबतक (unlikely(txq >= dev->real_num_tx_queues))
			txq -= dev->real_num_tx_queues;

		वापस txq;
	पूर्ण

	वापस netdev_pick_tx(dev, skb, शून्य) % dev->real_num_tx_queues;
पूर्ण

अटल पूर्णांक बंदst_समयr(स्थिर काष्ठा sge *s, पूर्णांक समय)
अणु
	पूर्णांक i, delta, match = 0, min_delta = पूर्णांक_उच्च;

	क्रम (i = 0; i < ARRAY_SIZE(s->समयr_val); i++) अणु
		delta = समय - s->समयr_val[i];
		अगर (delta < 0)
			delta = -delta;
		अगर (delta < min_delta) अणु
			min_delta = delta;
			match = i;
		पूर्ण
	पूर्ण
	वापस match;
पूर्ण

अटल पूर्णांक बंदst_thres(स्थिर काष्ठा sge *s, पूर्णांक thres)
अणु
	पूर्णांक i, delta, match = 0, min_delta = पूर्णांक_उच्च;

	क्रम (i = 0; i < ARRAY_SIZE(s->counter_val); i++) अणु
		delta = thres - s->counter_val[i];
		अगर (delta < 0)
			delta = -delta;
		अगर (delta < min_delta) अणु
			min_delta = delta;
			match = i;
		पूर्ण
	पूर्ण
	वापस match;
पूर्ण

/**
 *	cxgb4_set_rspq_पूर्णांकr_params - set a queue's पूर्णांकerrupt holकरोff parameters
 *	@q: the Rx queue
 *	@us: the hold-off समय in us, or 0 to disable समयr
 *	@cnt: the hold-off packet count, or 0 to disable counter
 *
 *	Sets an Rx queue's पूर्णांकerrupt hold-off समय and packet count.  At least
 *	one of the two needs to be enabled क्रम the queue to generate पूर्णांकerrupts.
 */
पूर्णांक cxgb4_set_rspq_पूर्णांकr_params(काष्ठा sge_rspq *q,
			       अचिन्हित पूर्णांक us, अचिन्हित पूर्णांक cnt)
अणु
	काष्ठा adapter *adap = q->adap;

	अगर ((us | cnt) == 0)
		cnt = 1;

	अगर (cnt) अणु
		पूर्णांक err;
		u32 v, new_idx;

		new_idx = बंदst_thres(&adap->sge, cnt);
		अगर (q->desc && q->pktcnt_idx != new_idx) अणु
			/* the queue has alपढ़ोy been created, update it */
			v = FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
			    FW_PARAMS_PARAM_X_V(
					FW_PARAMS_PARAM_DMAQ_IQ_INTCNTTHRESH) |
			    FW_PARAMS_PARAM_YZ_V(q->cntxt_id);
			err = t4_set_params(adap, adap->mbox, adap->pf, 0, 1,
					    &v, &new_idx);
			अगर (err)
				वापस err;
		पूर्ण
		q->pktcnt_idx = new_idx;
	पूर्ण

	us = us == 0 ? 6 : बंदst_समयr(&adap->sge, us);
	q->पूर्णांकr_params = QINTR_TIMER_IDX_V(us) | QINTR_CNT_EN_V(cnt > 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	netdev_features_t changed = dev->features ^ features;
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	पूर्णांक err;

	अगर (!(changed & NETIF_F_HW_VLAN_CTAG_RX))
		वापस 0;

	err = t4_set_rxmode(pi->adapter, pi->adapter->mbox, pi->viid,
			    pi->viid_mirror, -1, -1, -1, -1,
			    !!(features & NETIF_F_HW_VLAN_CTAG_RX), true);
	अगर (unlikely(err))
		dev->features = features ^ NETIF_F_HW_VLAN_CTAG_RX;
	वापस err;
पूर्ण

अटल पूर्णांक setup_debugfs(काष्ठा adapter *adap)
अणु
	अगर (IS_ERR_OR_शून्य(adap->debugfs_root))
		वापस -1;

#अगर_घोषित CONFIG_DEBUG_FS
	t4_setup_debugfs(adap);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम cxgb4_port_mirror_मुक्त_rxq(काष्ठा adapter *adap,
				       काष्ठा sge_eth_rxq *mirror_rxq)
अणु
	अगर ((adap->flags & CXGB4_FULL_INIT_DONE) &&
	    !(adap->flags & CXGB4_SHUTTING_DOWN))
		cxgb4_quiesce_rx(&mirror_rxq->rspq);

	अगर (adap->flags & CXGB4_USING_MSIX) अणु
		cxgb4_clear_msix_aff(mirror_rxq->msix->vec,
				     mirror_rxq->msix->aff_mask);
		मुक्त_irq(mirror_rxq->msix->vec, &mirror_rxq->rspq);
		cxgb4_मुक्त_msix_idx_in_bmap(adap, mirror_rxq->msix->idx);
	पूर्ण

	मुक्त_rspq_fl(adap, &mirror_rxq->rspq, &mirror_rxq->fl);
पूर्ण

अटल पूर्णांक cxgb4_port_mirror_alloc_queues(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा sge_eth_rxq *mirror_rxq;
	काष्ठा sge *s = &adap->sge;
	पूर्णांक ret = 0, msix = 0;
	u16 i, rxqid;
	u16 *rss;

	अगर (!pi->vi_mirror_count)
		वापस 0;

	अगर (s->mirror_rxq[pi->port_id])
		वापस 0;

	mirror_rxq = kसुस्मृति(pi->nmirrorqsets, माप(*mirror_rxq), GFP_KERNEL);
	अगर (!mirror_rxq)
		वापस -ENOMEM;

	s->mirror_rxq[pi->port_id] = mirror_rxq;

	अगर (!(adap->flags & CXGB4_USING_MSIX))
		msix = -((पूर्णांक)adap->sge.पूर्णांकrq.असल_id + 1);

	क्रम (i = 0, rxqid = 0; i < pi->nmirrorqsets; i++, rxqid++) अणु
		mirror_rxq = &s->mirror_rxq[pi->port_id][i];

		/* Allocate Mirror Rxqs */
		अगर (msix >= 0) अणु
			msix = cxgb4_get_msix_idx_from_bmap(adap);
			अगर (msix < 0) अणु
				ret = msix;
				जाओ out_मुक्त_queues;
			पूर्ण

			mirror_rxq->msix = &adap->msix_info[msix];
			snम_लिखो(mirror_rxq->msix->desc,
				 माप(mirror_rxq->msix->desc),
				 "%s-mirrorrxq%d", dev->name, i);
		पूर्ण

		init_rspq(adap, &mirror_rxq->rspq,
			  CXGB4_MIRROR_RXQ_DEFAULT_INTR_USEC,
			  CXGB4_MIRROR_RXQ_DEFAULT_PKT_CNT,
			  CXGB4_MIRROR_RXQ_DEFAULT_DESC_NUM,
			  CXGB4_MIRROR_RXQ_DEFAULT_DESC_SIZE);

		mirror_rxq->fl.size = CXGB4_MIRROR_FLQ_DEFAULT_DESC_NUM;

		ret = t4_sge_alloc_rxq(adap, &mirror_rxq->rspq, false,
				       dev, msix, &mirror_rxq->fl,
				       t4_ethrx_handler, शून्य, 0);
		अगर (ret)
			जाओ out_मुक्त_msix_idx;

		/* Setup MSI-X vectors क्रम Mirror Rxqs */
		अगर (adap->flags & CXGB4_USING_MSIX) अणु
			ret = request_irq(mirror_rxq->msix->vec,
					  t4_sge_पूर्णांकr_msix, 0,
					  mirror_rxq->msix->desc,
					  &mirror_rxq->rspq);
			अगर (ret)
				जाओ out_मुक्त_rxq;

			cxgb4_set_msix_aff(adap, mirror_rxq->msix->vec,
					   &mirror_rxq->msix->aff_mask, i);
		पूर्ण

		/* Start NAPI क्रम Mirror Rxqs */
		cxgb4_enable_rx(adap, &mirror_rxq->rspq);
	पूर्ण

	/* Setup RSS क्रम Mirror Rxqs */
	rss = kसुस्मृति(pi->rss_size, माप(u16), GFP_KERNEL);
	अगर (!rss) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_queues;
	पूर्ण

	mirror_rxq = &s->mirror_rxq[pi->port_id][0];
	क्रम (i = 0; i < pi->rss_size; i++)
		rss[i] = mirror_rxq[i % pi->nmirrorqsets].rspq.असल_id;

	ret = cxgb4_config_rss(pi, rss, pi->rss_size, pi->viid_mirror);
	kमुक्त(rss);
	अगर (ret)
		जाओ out_मुक्त_queues;

	वापस 0;

out_मुक्त_rxq:
	मुक्त_rspq_fl(adap, &mirror_rxq->rspq, &mirror_rxq->fl);

out_मुक्त_msix_idx:
	cxgb4_मुक्त_msix_idx_in_bmap(adap, mirror_rxq->msix->idx);

out_मुक्त_queues:
	जबतक (rxqid-- > 0)
		cxgb4_port_mirror_मुक्त_rxq(adap,
					   &s->mirror_rxq[pi->port_id][rxqid]);

	kमुक्त(s->mirror_rxq[pi->port_id]);
	s->mirror_rxq[pi->port_id] = शून्य;
	वापस ret;
पूर्ण

अटल व्योम cxgb4_port_mirror_मुक्त_queues(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा sge *s = &adap->sge;
	u16 i;

	अगर (!pi->vi_mirror_count)
		वापस;

	अगर (!s->mirror_rxq[pi->port_id])
		वापस;

	क्रम (i = 0; i < pi->nmirrorqsets; i++)
		cxgb4_port_mirror_मुक्त_rxq(adap,
					   &s->mirror_rxq[pi->port_id][i]);

	kमुक्त(s->mirror_rxq[pi->port_id]);
	s->mirror_rxq[pi->port_id] = शून्य;
पूर्ण

अटल पूर्णांक cxgb4_port_mirror_start(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	पूर्णांक ret, idx = -1;

	अगर (!pi->vi_mirror_count)
		वापस 0;

	/* Mirror VIs can be created dynamically after stack had
	 * alपढ़ोy setup Rx modes like MTU, promisc, allmulti, etc.
	 * on मुख्य VI. So, parse what the stack had setup on the
	 * मुख्य VI and update the same on the mirror VI.
	 */
	ret = t4_set_rxmode(adap, adap->mbox, pi->viid, pi->viid_mirror,
			    dev->mtu, (dev->flags & IFF_PROMISC) ? 1 : 0,
			    (dev->flags & IFF_ALLMULTI) ? 1 : 0, 1,
			    !!(dev->features & NETIF_F_HW_VLAN_CTAG_RX), true);
	अगर (ret) अणु
		dev_err(adap->pdev_dev,
			"Failed start up Rx mode for Mirror VI 0x%x, ret: %d\n",
			pi->viid_mirror, ret);
		वापस ret;
	पूर्ण

	/* Enable replication bit क्रम the device's MAC address
	 * in MPS TCAM, so that the packets क्रम the मुख्य VI are
	 * replicated to mirror VI.
	 */
	ret = cxgb4_update_mac_filt(pi, pi->viid_mirror, &idx,
				    dev->dev_addr, true, शून्य);
	अगर (ret) अणु
		dev_err(adap->pdev_dev,
			"Failed updating MAC filter for Mirror VI 0x%x, ret: %d\n",
			pi->viid_mirror, ret);
		वापस ret;
	पूर्ण

	/* Enabling a Virtual Interface can result in an पूर्णांकerrupt
	 * during the processing of the VI Enable command and, in some
	 * paths, result in an attempt to issue another command in the
	 * पूर्णांकerrupt context. Thus, we disable पूर्णांकerrupts during the
	 * course of the VI Enable command ...
	 */
	local_bh_disable();
	ret = t4_enable_vi_params(adap, adap->mbox, pi->viid_mirror, true, true,
				  false);
	local_bh_enable();
	अगर (ret)
		dev_err(adap->pdev_dev,
			"Failed starting Mirror VI 0x%x, ret: %d\n",
			pi->viid_mirror, ret);

	वापस ret;
पूर्ण

अटल व्योम cxgb4_port_mirror_stop(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);

	अगर (!pi->vi_mirror_count)
		वापस;

	t4_enable_vi_params(adap, adap->mbox, pi->viid_mirror, false, false,
			    false);
पूर्ण

पूर्णांक cxgb4_port_mirror_alloc(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	पूर्णांक ret = 0;

	अगर (!pi->nmirrorqsets)
		वापस -EOPNOTSUPP;

	mutex_lock(&pi->vi_mirror_mutex);
	अगर (pi->viid_mirror) अणु
		pi->vi_mirror_count++;
		जाओ out_unlock;
	पूर्ण

	ret = t4_init_port_mirror(pi, adap->mbox, pi->port_id, adap->pf, 0,
				  &pi->viid_mirror);
	अगर (ret)
		जाओ out_unlock;

	pi->vi_mirror_count = 1;

	अगर (adap->flags & CXGB4_FULL_INIT_DONE) अणु
		ret = cxgb4_port_mirror_alloc_queues(dev);
		अगर (ret)
			जाओ out_मुक्त_vi;

		ret = cxgb4_port_mirror_start(dev);
		अगर (ret)
			जाओ out_मुक्त_queues;
	पूर्ण

	mutex_unlock(&pi->vi_mirror_mutex);
	वापस 0;

out_मुक्त_queues:
	cxgb4_port_mirror_मुक्त_queues(dev);

out_मुक्त_vi:
	pi->vi_mirror_count = 0;
	t4_मुक्त_vi(adap, adap->mbox, adap->pf, 0, pi->viid_mirror);
	pi->viid_mirror = 0;

out_unlock:
	mutex_unlock(&pi->vi_mirror_mutex);
	वापस ret;
पूर्ण

व्योम cxgb4_port_mirror_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);

	mutex_lock(&pi->vi_mirror_mutex);
	अगर (!pi->viid_mirror)
		जाओ out_unlock;

	अगर (pi->vi_mirror_count > 1) अणु
		pi->vi_mirror_count--;
		जाओ out_unlock;
	पूर्ण

	cxgb4_port_mirror_stop(dev);
	cxgb4_port_mirror_मुक्त_queues(dev);

	pi->vi_mirror_count = 0;
	t4_मुक्त_vi(adap, adap->mbox, adap->pf, 0, pi->viid_mirror);
	pi->viid_mirror = 0;

out_unlock:
	mutex_unlock(&pi->vi_mirror_mutex);
पूर्ण

/*
 * upper-layer driver support
 */

/*
 * Allocate an active-खोलो TID and set it to the supplied value.
 */
पूर्णांक cxgb4_alloc_atid(काष्ठा tid_info *t, व्योम *data)
अणु
	पूर्णांक atid = -1;

	spin_lock_bh(&t->atid_lock);
	अगर (t->aमुक्त) अणु
		जोड़ aखोलो_entry *p = t->aमुक्त;

		atid = (p - t->atid_tab) + t->atid_base;
		t->aमुक्त = p->next;
		p->data = data;
		t->atids_in_use++;
	पूर्ण
	spin_unlock_bh(&t->atid_lock);
	वापस atid;
पूर्ण
EXPORT_SYMBOL(cxgb4_alloc_atid);

/*
 * Release an active-खोलो TID.
 */
व्योम cxgb4_मुक्त_atid(काष्ठा tid_info *t, अचिन्हित पूर्णांक atid)
अणु
	जोड़ aखोलो_entry *p = &t->atid_tab[atid - t->atid_base];

	spin_lock_bh(&t->atid_lock);
	p->next = t->aमुक्त;
	t->aमुक्त = p;
	t->atids_in_use--;
	spin_unlock_bh(&t->atid_lock);
पूर्ण
EXPORT_SYMBOL(cxgb4_मुक्त_atid);

/*
 * Allocate a server TID and set it to the supplied value.
 */
पूर्णांक cxgb4_alloc_stid(काष्ठा tid_info *t, पूर्णांक family, व्योम *data)
अणु
	पूर्णांक stid;

	spin_lock_bh(&t->stid_lock);
	अगर (family == PF_INET) अणु
		stid = find_first_zero_bit(t->stid_bmap, t->nstids);
		अगर (stid < t->nstids)
			__set_bit(stid, t->stid_bmap);
		अन्यथा
			stid = -1;
	पूर्ण अन्यथा अणु
		stid = biपंचांगap_find_मुक्त_region(t->stid_bmap, t->nstids, 1);
		अगर (stid < 0)
			stid = -1;
	पूर्ण
	अगर (stid >= 0) अणु
		t->stid_tab[stid].data = data;
		stid += t->stid_base;
		/* IPv6 requires max of 520 bits or 16 cells in TCAM
		 * This is equivalent to 4 TIDs. With CLIP enabled it
		 * needs 2 TIDs.
		 */
		अगर (family == PF_INET6) अणु
			t->stids_in_use += 2;
			t->v6_stids_in_use += 2;
		पूर्ण अन्यथा अणु
			t->stids_in_use++;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&t->stid_lock);
	वापस stid;
पूर्ण
EXPORT_SYMBOL(cxgb4_alloc_stid);

/* Allocate a server filter TID and set it to the supplied value.
 */
पूर्णांक cxgb4_alloc_sftid(काष्ठा tid_info *t, पूर्णांक family, व्योम *data)
अणु
	पूर्णांक stid;

	spin_lock_bh(&t->stid_lock);
	अगर (family == PF_INET) अणु
		stid = find_next_zero_bit(t->stid_bmap,
				t->nstids + t->nsftids, t->nstids);
		अगर (stid < (t->nstids + t->nsftids))
			__set_bit(stid, t->stid_bmap);
		अन्यथा
			stid = -1;
	पूर्ण अन्यथा अणु
		stid = -1;
	पूर्ण
	अगर (stid >= 0) अणु
		t->stid_tab[stid].data = data;
		stid -= t->nstids;
		stid += t->sftid_base;
		t->sftids_in_use++;
	पूर्ण
	spin_unlock_bh(&t->stid_lock);
	वापस stid;
पूर्ण
EXPORT_SYMBOL(cxgb4_alloc_sftid);

/* Release a server TID.
 */
व्योम cxgb4_मुक्त_stid(काष्ठा tid_info *t, अचिन्हित पूर्णांक stid, पूर्णांक family)
अणु
	/* Is it a server filter TID? */
	अगर (t->nsftids && (stid >= t->sftid_base)) अणु
		stid -= t->sftid_base;
		stid += t->nstids;
	पूर्ण अन्यथा अणु
		stid -= t->stid_base;
	पूर्ण

	spin_lock_bh(&t->stid_lock);
	अगर (family == PF_INET)
		__clear_bit(stid, t->stid_bmap);
	अन्यथा
		biपंचांगap_release_region(t->stid_bmap, stid, 1);
	t->stid_tab[stid].data = शून्य;
	अगर (stid < t->nstids) अणु
		अगर (family == PF_INET6) अणु
			t->stids_in_use -= 2;
			t->v6_stids_in_use -= 2;
		पूर्ण अन्यथा अणु
			t->stids_in_use--;
		पूर्ण
	पूर्ण अन्यथा अणु
		t->sftids_in_use--;
	पूर्ण

	spin_unlock_bh(&t->stid_lock);
पूर्ण
EXPORT_SYMBOL(cxgb4_मुक्त_stid);

/*
 * Populate a TID_RELEASE WR.  Caller must properly size the skb.
 */
अटल व्योम mk_tid_release(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक chan,
			   अचिन्हित पूर्णांक tid)
अणु
	काष्ठा cpl_tid_release *req;

	set_wr_txq(skb, CPL_PRIORITY_SETUP, chan);
	req = __skb_put(skb, माप(*req));
	INIT_TP_WR(req, tid);
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_TID_RELEASE, tid));
पूर्ण

/*
 * Queue a TID release request and अगर necessary schedule a work queue to
 * process it.
 */
अटल व्योम cxgb4_queue_tid_release(काष्ठा tid_info *t, अचिन्हित पूर्णांक chan,
				    अचिन्हित पूर्णांक tid)
अणु
	काष्ठा adapter *adap = container_of(t, काष्ठा adapter, tids);
	व्योम **p = &t->tid_tab[tid - t->tid_base];

	spin_lock_bh(&adap->tid_release_lock);
	*p = adap->tid_release_head;
	/* Low 2 bits encode the Tx channel number */
	adap->tid_release_head = (व्योम **)((uपूर्णांकptr_t)p | chan);
	अगर (!adap->tid_release_task_busy) अणु
		adap->tid_release_task_busy = true;
		queue_work(adap->workq, &adap->tid_release_task);
	पूर्ण
	spin_unlock_bh(&adap->tid_release_lock);
पूर्ण

/*
 * Process the list of pending TID release requests.
 */
अटल व्योम process_tid_release_list(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा adapter *adap;

	adap = container_of(work, काष्ठा adapter, tid_release_task);

	spin_lock_bh(&adap->tid_release_lock);
	जबतक (adap->tid_release_head) अणु
		व्योम **p = adap->tid_release_head;
		अचिन्हित पूर्णांक chan = (uपूर्णांकptr_t)p & 3;
		p = (व्योम *)p - chan;

		adap->tid_release_head = *p;
		*p = शून्य;
		spin_unlock_bh(&adap->tid_release_lock);

		जबतक (!(skb = alloc_skb(माप(काष्ठा cpl_tid_release),
					 GFP_KERNEL)))
			schedule_समयout_unपूर्णांकerruptible(1);

		mk_tid_release(skb, chan, p - adap->tids.tid_tab);
		t4_ofld_send(adap, skb);
		spin_lock_bh(&adap->tid_release_lock);
	पूर्ण
	adap->tid_release_task_busy = false;
	spin_unlock_bh(&adap->tid_release_lock);
पूर्ण

/*
 * Release a TID and inक्रमm HW.  If we are unable to allocate the release
 * message we defer to a work queue.
 */
व्योम cxgb4_हटाओ_tid(काष्ठा tid_info *t, अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक tid,
		      अचिन्हित लघु family)
अणु
	काष्ठा adapter *adap = container_of(t, काष्ठा adapter, tids);
	काष्ठा sk_buff *skb;

	WARN_ON(tid_out_of_range(&adap->tids, tid));

	अगर (t->tid_tab[tid - adap->tids.tid_base]) अणु
		t->tid_tab[tid - adap->tids.tid_base] = शून्य;
		atomic_dec(&t->conns_in_use);
		अगर (t->hash_base && (tid >= t->hash_base)) अणु
			अगर (family == AF_INET6)
				atomic_sub(2, &t->hash_tids_in_use);
			अन्यथा
				atomic_dec(&t->hash_tids_in_use);
		पूर्ण अन्यथा अणु
			अगर (family == AF_INET6)
				atomic_sub(2, &t->tids_in_use);
			अन्यथा
				atomic_dec(&t->tids_in_use);
		पूर्ण
	पूर्ण

	skb = alloc_skb(माप(काष्ठा cpl_tid_release), GFP_ATOMIC);
	अगर (likely(skb)) अणु
		mk_tid_release(skb, chan, tid);
		t4_ofld_send(adap, skb);
	पूर्ण अन्यथा
		cxgb4_queue_tid_release(t, chan, tid);
पूर्ण
EXPORT_SYMBOL(cxgb4_हटाओ_tid);

/*
 * Allocate and initialize the TID tables.  Returns 0 on success.
 */
अटल पूर्णांक tid_init(काष्ठा tid_info *t)
अणु
	काष्ठा adapter *adap = container_of(t, काष्ठा adapter, tids);
	अचिन्हित पूर्णांक max_ftids = t->nftids + t->nsftids;
	अचिन्हित पूर्णांक natids = t->natids;
	अचिन्हित पूर्णांक hpftid_bmap_size;
	अचिन्हित पूर्णांक eotid_bmap_size;
	अचिन्हित पूर्णांक stid_bmap_size;
	अचिन्हित पूर्णांक ftid_bmap_size;
	माप_प्रकार size;

	stid_bmap_size = BITS_TO_LONGS(t->nstids + t->nsftids);
	ftid_bmap_size = BITS_TO_LONGS(t->nftids);
	hpftid_bmap_size = BITS_TO_LONGS(t->nhpftids);
	eotid_bmap_size = BITS_TO_LONGS(t->neotids);
	size = t->ntids * माप(*t->tid_tab) +
	       natids * माप(*t->atid_tab) +
	       t->nstids * माप(*t->stid_tab) +
	       t->nsftids * माप(*t->stid_tab) +
	       stid_bmap_size * माप(दीर्घ) +
	       t->nhpftids * माप(*t->hpftid_tab) +
	       hpftid_bmap_size * माप(दीर्घ) +
	       max_ftids * माप(*t->ftid_tab) +
	       ftid_bmap_size * माप(दीर्घ) +
	       t->neotids * माप(*t->eotid_tab) +
	       eotid_bmap_size * माप(दीर्घ);

	t->tid_tab = kvzalloc(size, GFP_KERNEL);
	अगर (!t->tid_tab)
		वापस -ENOMEM;

	t->atid_tab = (जोड़ aखोलो_entry *)&t->tid_tab[t->ntids];
	t->stid_tab = (काष्ठा serv_entry *)&t->atid_tab[natids];
	t->stid_bmap = (अचिन्हित दीर्घ *)&t->stid_tab[t->nstids + t->nsftids];
	t->hpftid_tab = (काष्ठा filter_entry *)&t->stid_bmap[stid_bmap_size];
	t->hpftid_bmap = (अचिन्हित दीर्घ *)&t->hpftid_tab[t->nhpftids];
	t->ftid_tab = (काष्ठा filter_entry *)&t->hpftid_bmap[hpftid_bmap_size];
	t->ftid_bmap = (अचिन्हित दीर्घ *)&t->ftid_tab[max_ftids];
	t->eotid_tab = (काष्ठा eotid_entry *)&t->ftid_bmap[ftid_bmap_size];
	t->eotid_bmap = (अचिन्हित दीर्घ *)&t->eotid_tab[t->neotids];
	spin_lock_init(&t->stid_lock);
	spin_lock_init(&t->atid_lock);
	spin_lock_init(&t->ftid_lock);

	t->stids_in_use = 0;
	t->v6_stids_in_use = 0;
	t->sftids_in_use = 0;
	t->aमुक्त = शून्य;
	t->atids_in_use = 0;
	atomic_set(&t->tids_in_use, 0);
	atomic_set(&t->conns_in_use, 0);
	atomic_set(&t->hash_tids_in_use, 0);
	atomic_set(&t->eotids_in_use, 0);

	/* Setup the मुक्त list क्रम atid_tab and clear the stid biपंचांगap. */
	अगर (natids) अणु
		जबतक (--natids)
			t->atid_tab[natids - 1].next = &t->atid_tab[natids];
		t->aमुक्त = t->atid_tab;
	पूर्ण

	अगर (is_offload(adap)) अणु
		biपंचांगap_zero(t->stid_bmap, t->nstids + t->nsftids);
		/* Reserve stid 0 क्रम T4/T5 adapters */
		अगर (!t->stid_base &&
		    CHELSIO_CHIP_VERSION(adap->params.chip) <= CHELSIO_T5)
			__set_bit(0, t->stid_bmap);

		अगर (t->neotids)
			biपंचांगap_zero(t->eotid_bmap, t->neotids);
	पूर्ण

	अगर (t->nhpftids)
		biपंचांगap_zero(t->hpftid_bmap, t->nhpftids);
	biपंचांगap_zero(t->ftid_bmap, t->nftids);
	वापस 0;
पूर्ण

/**
 *	cxgb4_create_server - create an IP server
 *	@dev: the device
 *	@stid: the server TID
 *	@sip: local IP address to bind server to
 *	@sport: the server's TCP port
 *	@vlan: the VLAN header inक्रमmation
 *	@queue: queue to direct messages from this server to
 *
 *	Create an IP server क्रम the given port and address.
 *	Returns <0 on error and one of the %NET_XMIT_* values on success.
 */
पूर्णांक cxgb4_create_server(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
			__be32 sip, __be16 sport, __be16 vlan,
			अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक chan;
	काष्ठा sk_buff *skb;
	काष्ठा adapter *adap;
	काष्ठा cpl_pass_खोलो_req *req;
	पूर्णांक ret;

	skb = alloc_skb(माप(*req), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	adap = netdev2adap(dev);
	req = __skb_put(skb, माप(*req));
	INIT_TP_WR(req, 0);
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_PASS_OPEN_REQ, stid));
	req->local_port = sport;
	req->peer_port = htons(0);
	req->local_ip = sip;
	req->peer_ip = htonl(0);
	chan = rxq_to_chan(&adap->sge, queue);
	req->opt0 = cpu_to_be64(TX_CHAN_V(chan));
	req->opt1 = cpu_to_be64(CONN_POLICY_V(CPL_CONN_POLICY_ASK) |
				SYN_RSS_ENABLE_F | SYN_RSS_QUEUE_V(queue));
	ret = t4_mgmt_tx(adap, skb);
	वापस net_xmit_eval(ret);
पूर्ण
EXPORT_SYMBOL(cxgb4_create_server);

/*	cxgb4_create_server6 - create an IPv6 server
 *	@dev: the device
 *	@stid: the server TID
 *	@sip: local IPv6 address to bind server to
 *	@sport: the server's TCP port
 *	@queue: queue to direct messages from this server to
 *
 *	Create an IPv6 server क्रम the given port and address.
 *	Returns <0 on error and one of the %NET_XMIT_* values on success.
 */
पूर्णांक cxgb4_create_server6(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
			 स्थिर काष्ठा in6_addr *sip, __be16 sport,
			 अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक chan;
	काष्ठा sk_buff *skb;
	काष्ठा adapter *adap;
	काष्ठा cpl_pass_खोलो_req6 *req;
	पूर्णांक ret;

	skb = alloc_skb(माप(*req), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	adap = netdev2adap(dev);
	req = __skb_put(skb, माप(*req));
	INIT_TP_WR(req, 0);
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_PASS_OPEN_REQ6, stid));
	req->local_port = sport;
	req->peer_port = htons(0);
	req->local_ip_hi = *(__be64 *)(sip->s6_addr);
	req->local_ip_lo = *(__be64 *)(sip->s6_addr + 8);
	req->peer_ip_hi = cpu_to_be64(0);
	req->peer_ip_lo = cpu_to_be64(0);
	chan = rxq_to_chan(&adap->sge, queue);
	req->opt0 = cpu_to_be64(TX_CHAN_V(chan));
	req->opt1 = cpu_to_be64(CONN_POLICY_V(CPL_CONN_POLICY_ASK) |
				SYN_RSS_ENABLE_F | SYN_RSS_QUEUE_V(queue));
	ret = t4_mgmt_tx(adap, skb);
	वापस net_xmit_eval(ret);
पूर्ण
EXPORT_SYMBOL(cxgb4_create_server6);

पूर्णांक cxgb4_हटाओ_server(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
			अचिन्हित पूर्णांक queue, bool ipv6)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा adapter *adap;
	काष्ठा cpl_बंद_listsvr_req *req;
	पूर्णांक ret;

	adap = netdev2adap(dev);

	skb = alloc_skb(माप(*req), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	req = __skb_put(skb, माप(*req));
	INIT_TP_WR(req, 0);
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_CLOSE_LISTSRV_REQ, stid));
	req->reply_ctrl = htons(NO_REPLY_V(0) | (ipv6 ? LISTSVR_IPV6_V(1) :
				LISTSVR_IPV6_V(0)) | QUEUENO_V(queue));
	ret = t4_mgmt_tx(adap, skb);
	वापस net_xmit_eval(ret);
पूर्ण
EXPORT_SYMBOL(cxgb4_हटाओ_server);

/**
 *	cxgb4_best_mtu - find the entry in the MTU table बंदst to an MTU
 *	@mtus: the HW MTU table
 *	@mtu: the target MTU
 *	@idx: index of selected entry in the MTU table
 *
 *	Returns the index and the value in the HW MTU table that is बंदst to
 *	but करोes not exceed @mtu, unless @mtu is smaller than any value in the
 *	table, in which हाल that smallest available value is selected.
 */
अचिन्हित पूर्णांक cxgb4_best_mtu(स्थिर अचिन्हित लघु *mtus, अचिन्हित लघु mtu,
			    अचिन्हित पूर्णांक *idx)
अणु
	अचिन्हित पूर्णांक i = 0;

	जबतक (i < NMTUS - 1 && mtus[i + 1] <= mtu)
		++i;
	अगर (idx)
		*idx = i;
	वापस mtus[i];
पूर्ण
EXPORT_SYMBOL(cxgb4_best_mtu);

/**
 *     cxgb4_best_aligned_mtu - find best MTU, [hopefully] data size aligned
 *     @mtus: the HW MTU table
 *     @header_size: Header Size
 *     @data_size_max: maximum Data Segment Size
 *     @data_size_align: desired Data Segment Size Alignment (2^N)
 *     @mtu_idxp: HW MTU Table Index वापस value poपूर्णांकer (possibly शून्य)
 *
 *     Similar to cxgb4_best_mtu() but instead of searching the Hardware
 *     MTU Table based solely on a Maximum MTU parameter, we अवरोध that
 *     parameter up पूर्णांकo a Header Size and Maximum Data Segment Size, and
 *     provide a desired Data Segment Size Alignment.  If we find an MTU in
 *     the Hardware MTU Table which will result in a Data Segment Size with
 *     the requested alignment _and_ that MTU isn't "too far" from the
 *     बंदst MTU, then we'll वापस that rather than the बंदst MTU.
 */
अचिन्हित पूर्णांक cxgb4_best_aligned_mtu(स्थिर अचिन्हित लघु *mtus,
				    अचिन्हित लघु header_size,
				    अचिन्हित लघु data_size_max,
				    अचिन्हित लघु data_size_align,
				    अचिन्हित पूर्णांक *mtu_idxp)
अणु
	अचिन्हित लघु max_mtu = header_size + data_size_max;
	अचिन्हित लघु data_size_align_mask = data_size_align - 1;
	पूर्णांक mtu_idx, aligned_mtu_idx;

	/* Scan the MTU Table till we find an MTU which is larger than our
	 * Maximum MTU or we reach the end of the table.  Aदीर्घ the way,
	 * record the last MTU found, अगर any, which will result in a Data
	 * Segment Length matching the requested alignment.
	 */
	क्रम (mtu_idx = 0, aligned_mtu_idx = -1; mtu_idx < NMTUS; mtu_idx++) अणु
		अचिन्हित लघु data_size = mtus[mtu_idx] - header_size;

		/* If this MTU minus the Header Size would result in a
		 * Data Segment Size of the desired alignment, remember it.
		 */
		अगर ((data_size & data_size_align_mask) == 0)
			aligned_mtu_idx = mtu_idx;

		/* If we're not at the end of the Hardware MTU Table and the
		 * next element is larger than our Maximum MTU, drop out of
		 * the loop.
		 */
		अगर (mtu_idx+1 < NMTUS && mtus[mtu_idx+1] > max_mtu)
			अवरोध;
	पूर्ण

	/* If we fell out of the loop because we ran to the end of the table,
	 * then we just have to use the last [largest] entry.
	 */
	अगर (mtu_idx == NMTUS)
		mtu_idx--;

	/* If we found an MTU which resulted in the requested Data Segment
	 * Length alignment and that's "not far" from the largest MTU which is
	 * less than or equal to the maximum MTU, then use that.
	 */
	अगर (aligned_mtu_idx >= 0 &&
	    mtu_idx - aligned_mtu_idx <= 1)
		mtu_idx = aligned_mtu_idx;

	/* If the caller has passed in an MTU Index poपूर्णांकer, pass the
	 * MTU Index back.  Return the MTU value.
	 */
	अगर (mtu_idxp)
		*mtu_idxp = mtu_idx;
	वापस mtus[mtu_idx];
पूर्ण
EXPORT_SYMBOL(cxgb4_best_aligned_mtu);

/**
 *	cxgb4_port_chan - get the HW channel of a port
 *	@dev: the net device क्रम the port
 *
 *	Return the HW Tx channel of the given port.
 */
अचिन्हित पूर्णांक cxgb4_port_chan(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev2pinfo(dev)->tx_chan;
पूर्ण
EXPORT_SYMBOL(cxgb4_port_chan);

/**
 *      cxgb4_port_e2cchan - get the HW c-channel of a port
 *      @dev: the net device क्रम the port
 *
 *      Return the HW RX c-channel of the given port.
 */
अचिन्हित पूर्णांक cxgb4_port_e2cchan(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev2pinfo(dev)->rx_cchan;
पूर्ण
EXPORT_SYMBOL(cxgb4_port_e2cchan);

अचिन्हित पूर्णांक cxgb4_dbfअगरo_count(स्थिर काष्ठा net_device *dev, पूर्णांक lpfअगरo)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	u32 v1, v2, lp_count, hp_count;

	v1 = t4_पढ़ो_reg(adap, SGE_DBFIFO_STATUS_A);
	v2 = t4_पढ़ो_reg(adap, SGE_DBFIFO_STATUS2_A);
	अगर (is_t4(adap->params.chip)) अणु
		lp_count = LP_COUNT_G(v1);
		hp_count = HP_COUNT_G(v1);
	पूर्ण अन्यथा अणु
		lp_count = LP_COUNT_T5_G(v1);
		hp_count = HP_COUNT_T5_G(v2);
	पूर्ण
	वापस lpfअगरo ? lp_count : hp_count;
पूर्ण
EXPORT_SYMBOL(cxgb4_dbfअगरo_count);

/**
 *	cxgb4_port_viid - get the VI id of a port
 *	@dev: the net device क्रम the port
 *
 *	Return the VI id of the given port.
 */
अचिन्हित पूर्णांक cxgb4_port_viid(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev2pinfo(dev)->viid;
पूर्ण
EXPORT_SYMBOL(cxgb4_port_viid);

/**
 *	cxgb4_port_idx - get the index of a port
 *	@dev: the net device क्रम the port
 *
 *	Return the index of the given port.
 */
अचिन्हित पूर्णांक cxgb4_port_idx(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev2pinfo(dev)->port_id;
पूर्ण
EXPORT_SYMBOL(cxgb4_port_idx);

व्योम cxgb4_get_tcp_stats(काष्ठा pci_dev *pdev, काष्ठा tp_tcp_stats *v4,
			 काष्ठा tp_tcp_stats *v6)
अणु
	काष्ठा adapter *adap = pci_get_drvdata(pdev);

	spin_lock(&adap->stats_lock);
	t4_tp_get_tcp_stats(adap, v4, v6, false);
	spin_unlock(&adap->stats_lock);
पूर्ण
EXPORT_SYMBOL(cxgb4_get_tcp_stats);

व्योम cxgb4_iscsi_init(काष्ठा net_device *dev, अचिन्हित पूर्णांक tag_mask,
		      स्थिर अचिन्हित पूर्णांक *pgsz_order)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

	t4_ग_लिखो_reg(adap, ULP_RX_ISCSI_TAGMASK_A, tag_mask);
	t4_ग_लिखो_reg(adap, ULP_RX_ISCSI_PSZ_A, HPZ0_V(pgsz_order[0]) |
		     HPZ1_V(pgsz_order[1]) | HPZ2_V(pgsz_order[2]) |
		     HPZ3_V(pgsz_order[3]));
पूर्ण
EXPORT_SYMBOL(cxgb4_iscsi_init);

पूर्णांक cxgb4_flush_eq_cache(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

	वापस t4_sge_ctxt_flush(adap, adap->mbox, CTXT_EGRESS);
पूर्ण
EXPORT_SYMBOL(cxgb4_flush_eq_cache);

अटल पूर्णांक पढ़ो_eq_indices(काष्ठा adapter *adap, u16 qid, u16 *pidx, u16 *cidx)
अणु
	u32 addr = t4_पढ़ो_reg(adap, SGE_DBQ_CTXT_BADDR_A) + 24 * qid + 8;
	__be64 indices;
	पूर्णांक ret;

	spin_lock(&adap->win0_lock);
	ret = t4_memory_rw(adap, 0, MEM_EDC0, addr,
			   माप(indices), (__be32 *)&indices,
			   T4_MEMORY_READ);
	spin_unlock(&adap->win0_lock);
	अगर (!ret) अणु
		*cidx = (be64_to_cpu(indices) >> 25) & 0xffff;
		*pidx = (be64_to_cpu(indices) >> 9) & 0xffff;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक cxgb4_sync_txq_pidx(काष्ठा net_device *dev, u16 qid, u16 pidx,
			u16 size)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	u16 hw_pidx, hw_cidx;
	पूर्णांक ret;

	ret = पढ़ो_eq_indices(adap, qid, &hw_pidx, &hw_cidx);
	अगर (ret)
		जाओ out;

	अगर (pidx != hw_pidx) अणु
		u16 delta;
		u32 val;

		अगर (pidx >= hw_pidx)
			delta = pidx - hw_pidx;
		अन्यथा
			delta = size - hw_pidx + pidx;

		अगर (is_t4(adap->params.chip))
			val = PIDX_V(delta);
		अन्यथा
			val = PIDX_T5_V(delta);
		wmb();
		t4_ग_लिखो_reg(adap, MYPF_REG(SGE_PF_KDOORBELL_A),
			     QID_V(qid) | val);
	पूर्ण
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cxgb4_sync_txq_pidx);

पूर्णांक cxgb4_पढ़ो_tpte(काष्ठा net_device *dev, u32 stag, __be32 *tpte)
अणु
	u32 edc0_size, edc1_size, mc0_size, mc1_size, size;
	u32 edc0_end, edc1_end, mc0_end, mc1_end;
	u32 offset, memtype, memaddr;
	काष्ठा adapter *adap;
	u32 hma_size = 0;
	पूर्णांक ret;

	adap = netdev2adap(dev);

	offset = ((stag >> 8) * 32) + adap->vres.stag.start;

	/* Figure out where the offset lands in the Memory Type/Address scheme.
	 * This code assumes that the memory is laid out starting at offset 0
	 * with no अवरोधs as: EDC0, EDC1, MC0, MC1. All cards have both EDC0
	 * and EDC1.  Some cards will have neither MC0 nor MC1, most cards have
	 * MC0, and some have both MC0 and MC1.
	 */
	size = t4_पढ़ो_reg(adap, MA_EDRAM0_BAR_A);
	edc0_size = EDRAM0_SIZE_G(size) << 20;
	size = t4_पढ़ो_reg(adap, MA_EDRAM1_BAR_A);
	edc1_size = EDRAM1_SIZE_G(size) << 20;
	size = t4_पढ़ो_reg(adap, MA_EXT_MEMORY0_BAR_A);
	mc0_size = EXT_MEM0_SIZE_G(size) << 20;

	अगर (t4_पढ़ो_reg(adap, MA_TARGET_MEM_ENABLE_A) & HMA_MUX_F) अणु
		size = t4_पढ़ो_reg(adap, MA_EXT_MEMORY1_BAR_A);
		hma_size = EXT_MEM1_SIZE_G(size) << 20;
	पूर्ण
	edc0_end = edc0_size;
	edc1_end = edc0_end + edc1_size;
	mc0_end = edc1_end + mc0_size;

	अगर (offset < edc0_end) अणु
		memtype = MEM_EDC0;
		memaddr = offset;
	पूर्ण अन्यथा अगर (offset < edc1_end) अणु
		memtype = MEM_EDC1;
		memaddr = offset - edc0_end;
	पूर्ण अन्यथा अणु
		अगर (hma_size && (offset < (edc1_end + hma_size))) अणु
			memtype = MEM_HMA;
			memaddr = offset - edc1_end;
		पूर्ण अन्यथा अगर (offset < mc0_end) अणु
			memtype = MEM_MC0;
			memaddr = offset - edc1_end;
		पूर्ण अन्यथा अगर (is_t5(adap->params.chip)) अणु
			size = t4_पढ़ो_reg(adap, MA_EXT_MEMORY1_BAR_A);
			mc1_size = EXT_MEM1_SIZE_G(size) << 20;
			mc1_end = mc0_end + mc1_size;
			अगर (offset < mc1_end) अणु
				memtype = MEM_MC1;
				memaddr = offset - mc0_end;
			पूर्ण अन्यथा अणु
				/* offset beyond the end of any memory */
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* T4/T6 only has a single memory channel */
			जाओ err;
		पूर्ण
	पूर्ण

	spin_lock(&adap->win0_lock);
	ret = t4_memory_rw(adap, 0, memtype, memaddr, 32, tpte, T4_MEMORY_READ);
	spin_unlock(&adap->win0_lock);
	वापस ret;

err:
	dev_err(adap->pdev_dev, "stag %#x, offset %#x out of range\n",
		stag, offset);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(cxgb4_पढ़ो_tpte);

u64 cxgb4_पढ़ो_sge_बारtamp(काष्ठा net_device *dev)
अणु
	u32 hi, lo;
	काष्ठा adapter *adap;

	adap = netdev2adap(dev);
	lo = t4_पढ़ो_reg(adap, SGE_TIMESTAMP_LO_A);
	hi = TSVAL_G(t4_पढ़ो_reg(adap, SGE_TIMESTAMP_HI_A));

	वापस ((u64)hi << 32) | (u64)lo;
पूर्ण
EXPORT_SYMBOL(cxgb4_पढ़ो_sge_बारtamp);

पूर्णांक cxgb4_bar2_sge_qregs(काष्ठा net_device *dev,
			 अचिन्हित पूर्णांक qid,
			 क्रमागत cxgb4_bar2_qtype qtype,
			 पूर्णांक user,
			 u64 *pbar2_qoffset,
			 अचिन्हित पूर्णांक *pbar2_qid)
अणु
	वापस t4_bar2_sge_qregs(netdev2adap(dev),
				 qid,
				 (qtype == CXGB4_BAR2_QTYPE_EGRESS
				  ? T4_BAR2_QTYPE_EGRESS
				  : T4_BAR2_QTYPE_INGRESS),
				 user,
				 pbar2_qoffset,
				 pbar2_qid);
पूर्ण
EXPORT_SYMBOL(cxgb4_bar2_sge_qregs);

अटल काष्ठा pci_driver cxgb4_driver;

अटल व्योम check_neigh_update(काष्ठा neighbour *neigh)
अणु
	स्थिर काष्ठा device *parent;
	स्थिर काष्ठा net_device *netdev = neigh->dev;

	अगर (is_vlan_dev(netdev))
		netdev = vlan_dev_real_dev(netdev);
	parent = netdev->dev.parent;
	अगर (parent && parent->driver == &cxgb4_driver.driver)
		t4_l2t_update(dev_get_drvdata(parent), neigh);
पूर्ण

अटल पूर्णांक netevent_cb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
		       व्योम *data)
अणु
	चयन (event) अणु
	हाल NETEVENT_NEIGH_UPDATE:
		check_neigh_update(data);
		अवरोध;
	हाल NETEVENT_REसूचीECT:
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool netevent_रेजिस्टरed;
अटल काष्ठा notअगरier_block cxgb4_netevent_nb = अणु
	.notअगरier_call = netevent_cb
पूर्ण;

अटल व्योम drain_db_fअगरo(काष्ठा adapter *adap, पूर्णांक usecs)
अणु
	u32 v1, v2, lp_count, hp_count;

	करो अणु
		v1 = t4_पढ़ो_reg(adap, SGE_DBFIFO_STATUS_A);
		v2 = t4_पढ़ो_reg(adap, SGE_DBFIFO_STATUS2_A);
		अगर (is_t4(adap->params.chip)) अणु
			lp_count = LP_COUNT_G(v1);
			hp_count = HP_COUNT_G(v1);
		पूर्ण अन्यथा अणु
			lp_count = LP_COUNT_T5_G(v1);
			hp_count = HP_COUNT_T5_G(v2);
		पूर्ण

		अगर (lp_count == 0 && hp_count == 0)
			अवरोध;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(usecs_to_jअगरfies(usecs));
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम disable_txq_db(काष्ठा sge_txq *q)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->db_lock, flags);
	q->db_disabled = 1;
	spin_unlock_irqrestore(&q->db_lock, flags);
पूर्ण

अटल व्योम enable_txq_db(काष्ठा adapter *adap, काष्ठा sge_txq *q)
अणु
	spin_lock_irq(&q->db_lock);
	अगर (q->db_pidx_inc) अणु
		/* Make sure that all ग_लिखोs to the TX descriptors
		 * are committed beक्रमe we tell HW about them.
		 */
		wmb();
		t4_ग_लिखो_reg(adap, MYPF_REG(SGE_PF_KDOORBELL_A),
			     QID_V(q->cntxt_id) | PIDX_V(q->db_pidx_inc));
		q->db_pidx_inc = 0;
	पूर्ण
	q->db_disabled = 0;
	spin_unlock_irq(&q->db_lock);
पूर्ण

अटल व्योम disable_dbs(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम_each_ethrxq(&adap->sge, i)
		disable_txq_db(&adap->sge.ethtxq[i].q);
	अगर (is_offload(adap)) अणु
		काष्ठा sge_uld_txq_info *txq_info =
			adap->sge.uld_txq_info[CXGB4_TX_OFLD];

		अगर (txq_info) अणु
			क्रम_each_ofldtxq(&adap->sge, i) अणु
				काष्ठा sge_uld_txq *txq = &txq_info->uldtxq[i];

				disable_txq_db(&txq->q);
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम_each_port(adap, i)
		disable_txq_db(&adap->sge.ctrlq[i].q);
पूर्ण

अटल व्योम enable_dbs(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम_each_ethrxq(&adap->sge, i)
		enable_txq_db(adap, &adap->sge.ethtxq[i].q);
	अगर (is_offload(adap)) अणु
		काष्ठा sge_uld_txq_info *txq_info =
			adap->sge.uld_txq_info[CXGB4_TX_OFLD];

		अगर (txq_info) अणु
			क्रम_each_ofldtxq(&adap->sge, i) अणु
				काष्ठा sge_uld_txq *txq = &txq_info->uldtxq[i];

				enable_txq_db(adap, &txq->q);
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम_each_port(adap, i)
		enable_txq_db(adap, &adap->sge.ctrlq[i].q);
पूर्ण

अटल व्योम notअगरy_rdma_uld(काष्ठा adapter *adap, क्रमागत cxgb4_control cmd)
अणु
	क्रमागत cxgb4_uld type = CXGB4_ULD_RDMA;

	अगर (adap->uld && adap->uld[type].handle)
		adap->uld[type].control(adap->uld[type].handle, cmd);
पूर्ण

अटल व्योम process_db_full(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adap;

	adap = container_of(work, काष्ठा adapter, db_full_task);

	drain_db_fअगरo(adap, dbfअगरo_drain_delay);
	enable_dbs(adap);
	notअगरy_rdma_uld(adap, CXGB4_CONTROL_DB_EMPTY);
	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) <= CHELSIO_T5)
		t4_set_reg_field(adap, SGE_INT_ENABLE3_A,
				 DBFIFO_HP_INT_F | DBFIFO_LP_INT_F,
				 DBFIFO_HP_INT_F | DBFIFO_LP_INT_F);
	अन्यथा
		t4_set_reg_field(adap, SGE_INT_ENABLE3_A,
				 DBFIFO_LP_INT_F, DBFIFO_LP_INT_F);
पूर्ण

अटल व्योम sync_txq_pidx(काष्ठा adapter *adap, काष्ठा sge_txq *q)
अणु
	u16 hw_pidx, hw_cidx;
	पूर्णांक ret;

	spin_lock_irq(&q->db_lock);
	ret = पढ़ो_eq_indices(adap, (u16)q->cntxt_id, &hw_pidx, &hw_cidx);
	अगर (ret)
		जाओ out;
	अगर (q->db_pidx != hw_pidx) अणु
		u16 delta;
		u32 val;

		अगर (q->db_pidx >= hw_pidx)
			delta = q->db_pidx - hw_pidx;
		अन्यथा
			delta = q->size - hw_pidx + q->db_pidx;

		अगर (is_t4(adap->params.chip))
			val = PIDX_V(delta);
		अन्यथा
			val = PIDX_T5_V(delta);
		wmb();
		t4_ग_लिखो_reg(adap, MYPF_REG(SGE_PF_KDOORBELL_A),
			     QID_V(q->cntxt_id) | val);
	पूर्ण
out:
	q->db_disabled = 0;
	q->db_pidx_inc = 0;
	spin_unlock_irq(&q->db_lock);
	अगर (ret)
		CH_WARN(adap, "DB drop recovery failed.\n");
पूर्ण

अटल व्योम recover_all_queues(काष्ठा adapter *adap)
अणु
	पूर्णांक i;

	क्रम_each_ethrxq(&adap->sge, i)
		sync_txq_pidx(adap, &adap->sge.ethtxq[i].q);
	अगर (is_offload(adap)) अणु
		काष्ठा sge_uld_txq_info *txq_info =
			adap->sge.uld_txq_info[CXGB4_TX_OFLD];
		अगर (txq_info) अणु
			क्रम_each_ofldtxq(&adap->sge, i) अणु
				काष्ठा sge_uld_txq *txq = &txq_info->uldtxq[i];

				sync_txq_pidx(adap, &txq->q);
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम_each_port(adap, i)
		sync_txq_pidx(adap, &adap->sge.ctrlq[i].q);
पूर्ण

अटल व्योम process_db_drop(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adap;

	adap = container_of(work, काष्ठा adapter, db_drop_task);

	अगर (is_t4(adap->params.chip)) अणु
		drain_db_fअगरo(adap, dbfअगरo_drain_delay);
		notअगरy_rdma_uld(adap, CXGB4_CONTROL_DB_DROP);
		drain_db_fअगरo(adap, dbfअगरo_drain_delay);
		recover_all_queues(adap);
		drain_db_fअगरo(adap, dbfअगरo_drain_delay);
		enable_dbs(adap);
		notअगरy_rdma_uld(adap, CXGB4_CONTROL_DB_EMPTY);
	पूर्ण अन्यथा अगर (is_t5(adap->params.chip)) अणु
		u32 dropped_db = t4_पढ़ो_reg(adap, 0x010ac);
		u16 qid = (dropped_db >> 15) & 0x1ffff;
		u16 pidx_inc = dropped_db & 0x1fff;
		u64 bar2_qoffset;
		अचिन्हित पूर्णांक bar2_qid;
		पूर्णांक ret;

		ret = t4_bar2_sge_qregs(adap, qid, T4_BAR2_QTYPE_EGRESS,
					0, &bar2_qoffset, &bar2_qid);
		अगर (ret)
			dev_err(adap->pdev_dev, "doorbell drop recovery: "
				"qid=%d, pidx_inc=%d\n", qid, pidx_inc);
		अन्यथा
			ग_लिखोl(PIDX_T5_V(pidx_inc) | QID_V(bar2_qid),
			       adap->bar2 + bar2_qoffset + SGE_UDB_KDOORBELL);

		/* Re-enable BAR2 WC */
		t4_set_reg_field(adap, 0x10b0, 1<<15, 1<<15);
	पूर्ण

	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) <= CHELSIO_T5)
		t4_set_reg_field(adap, SGE_DOORBELL_CONTROL_A, DROPPED_DB_F, 0);
पूर्ण

व्योम t4_db_full(काष्ठा adapter *adap)
अणु
	अगर (is_t4(adap->params.chip)) अणु
		disable_dbs(adap);
		notअगरy_rdma_uld(adap, CXGB4_CONTROL_DB_FULL);
		t4_set_reg_field(adap, SGE_INT_ENABLE3_A,
				 DBFIFO_HP_INT_F | DBFIFO_LP_INT_F, 0);
		queue_work(adap->workq, &adap->db_full_task);
	पूर्ण
पूर्ण

व्योम t4_db_dropped(काष्ठा adapter *adap)
अणु
	अगर (is_t4(adap->params.chip)) अणु
		disable_dbs(adap);
		notअगरy_rdma_uld(adap, CXGB4_CONTROL_DB_FULL);
	पूर्ण
	queue_work(adap->workq, &adap->db_drop_task);
पूर्ण

व्योम t4_रेजिस्टर_netevent_notअगरier(व्योम)
अणु
	अगर (!netevent_रेजिस्टरed) अणु
		रेजिस्टर_netevent_notअगरier(&cxgb4_netevent_nb);
		netevent_रेजिस्टरed = true;
	पूर्ण
पूर्ण

अटल व्योम detach_ulds(काष्ठा adapter *adap)
अणु
	अचिन्हित पूर्णांक i;

	mutex_lock(&uld_mutex);
	list_del(&adap->list_node);

	क्रम (i = 0; i < CXGB4_ULD_MAX; i++)
		अगर (adap->uld && adap->uld[i].handle)
			adap->uld[i].state_change(adap->uld[i].handle,
					     CXGB4_STATE_DETACH);

	अगर (netevent_रेजिस्टरed && list_empty(&adapter_list)) अणु
		unरेजिस्टर_netevent_notअगरier(&cxgb4_netevent_nb);
		netevent_रेजिस्टरed = false;
	पूर्ण
	mutex_unlock(&uld_mutex);
पूर्ण

अटल व्योम notअगरy_ulds(काष्ठा adapter *adap, क्रमागत cxgb4_state new_state)
अणु
	अचिन्हित पूर्णांक i;

	mutex_lock(&uld_mutex);
	क्रम (i = 0; i < CXGB4_ULD_MAX; i++)
		अगर (adap->uld && adap->uld[i].handle)
			adap->uld[i].state_change(adap->uld[i].handle,
						  new_state);
	mutex_unlock(&uld_mutex);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक cxgb4_inet6addr_handler(काष्ठा notअगरier_block *this,
				   अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा inet6_अगरaddr *अगरa = data;
	काष्ठा net_device *event_dev = अगरa->idev->dev;
	स्थिर काष्ठा device *parent = शून्य;
#अगर IS_ENABLED(CONFIG_BONDING)
	काष्ठा adapter *adap;
#पूर्ण_अगर
	अगर (is_vlan_dev(event_dev))
		event_dev = vlan_dev_real_dev(event_dev);
#अगर IS_ENABLED(CONFIG_BONDING)
	अगर (event_dev->flags & IFF_MASTER) अणु
		list_क्रम_each_entry(adap, &adapter_list, list_node) अणु
			चयन (event) अणु
			हाल NETDEV_UP:
				cxgb4_clip_get(adap->port[0],
					       (स्थिर u32 *)अगरa, 1);
				अवरोध;
			हाल NETDEV_DOWN:
				cxgb4_clip_release(adap->port[0],
						   (स्थिर u32 *)अगरa, 1);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		वापस NOTIFY_OK;
	पूर्ण
#पूर्ण_अगर

	अगर (event_dev)
		parent = event_dev->dev.parent;

	अगर (parent && parent->driver == &cxgb4_driver.driver) अणु
		चयन (event) अणु
		हाल NETDEV_UP:
			cxgb4_clip_get(event_dev, (स्थिर u32 *)अगरa, 1);
			अवरोध;
		हाल NETDEV_DOWN:
			cxgb4_clip_release(event_dev, (स्थिर u32 *)अगरa, 1);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल bool inet6addr_रेजिस्टरed;
अटल काष्ठा notअगरier_block cxgb4_inet6addr_notअगरier = अणु
	.notअगरier_call = cxgb4_inet6addr_handler
पूर्ण;

अटल व्योम update_clip(स्थिर काष्ठा adapter *adap)
अणु
	पूर्णांक i;
	काष्ठा net_device *dev;
	पूर्णांक ret;

	rcu_पढ़ो_lock();

	क्रम (i = 0; i < MAX_NPORTS; i++) अणु
		dev = adap->port[i];
		ret = 0;

		अगर (dev)
			ret = cxgb4_update_root_dev_clip(dev);

		अगर (ret < 0)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */

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
	काष्ठा sge *s = &adap->sge;
	पूर्णांक err;

	mutex_lock(&uld_mutex);
	err = setup_sge_queues(adap);
	अगर (err)
		जाओ rel_lock;
	err = setup_rss(adap);
	अगर (err)
		जाओ मुक्तq;

	अगर (adap->flags & CXGB4_USING_MSIX) अणु
		अगर (s->nd_msix_idx < 0) अणु
			err = -ENOMEM;
			जाओ irq_err;
		पूर्ण

		err = request_irq(adap->msix_info[s->nd_msix_idx].vec,
				  t4_nondata_पूर्णांकr, 0,
				  adap->msix_info[s->nd_msix_idx].desc, adap);
		अगर (err)
			जाओ irq_err;

		err = request_msix_queue_irqs(adap);
		अगर (err)
			जाओ irq_err_मुक्त_nd_msix;
	पूर्ण अन्यथा अणु
		err = request_irq(adap->pdev->irq, t4_पूर्णांकr_handler(adap),
				  (adap->flags & CXGB4_USING_MSI) ? 0
								  : IRQF_SHARED,
				  adap->port[0]->name, adap);
		अगर (err)
			जाओ irq_err;
	पूर्ण

	enable_rx(adap);
	t4_sge_start(adap);
	t4_पूर्णांकr_enable(adap);
	adap->flags |= CXGB4_FULL_INIT_DONE;
	mutex_unlock(&uld_mutex);

	notअगरy_ulds(adap, CXGB4_STATE_UP);
#अगर IS_ENABLED(CONFIG_IPV6)
	update_clip(adap);
#पूर्ण_अगर
	वापस err;

irq_err_मुक्त_nd_msix:
	मुक्त_irq(adap->msix_info[s->nd_msix_idx].vec, adap);
irq_err:
	dev_err(adap->pdev_dev, "request_irq failed, err %d\n", err);
मुक्तq:
	t4_मुक्त_sge_resources(adap);
rel_lock:
	mutex_unlock(&uld_mutex);
	वापस err;
पूर्ण

अटल व्योम cxgb_करोwn(काष्ठा adapter *adapter)
अणु
	cancel_work_sync(&adapter->tid_release_task);
	cancel_work_sync(&adapter->db_full_task);
	cancel_work_sync(&adapter->db_drop_task);
	adapter->tid_release_task_busy = false;
	adapter->tid_release_head = शून्य;

	t4_sge_stop(adapter);
	t4_मुक्त_sge_resources(adapter);

	adapter->flags &= ~CXGB4_FULL_INIT_DONE;
पूर्ण

/*
 * net_device operations
 */
अटल पूर्णांक cxgb_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक err;

	netअगर_carrier_off(dev);

	अगर (!(adapter->flags & CXGB4_FULL_INIT_DONE)) अणु
		err = cxgb_up(adapter);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* It's possible that the basic port inक्रमmation could have
	 * changed since we first पढ़ो it.
	 */
	err = t4_update_port_info(pi);
	अगर (err < 0)
		वापस err;

	err = link_start(dev);
	अगर (err)
		वापस err;

	अगर (pi->nmirrorqsets) अणु
		mutex_lock(&pi->vi_mirror_mutex);
		err = cxgb4_port_mirror_alloc_queues(dev);
		अगर (err)
			जाओ out_unlock;

		err = cxgb4_port_mirror_start(dev);
		अगर (err)
			जाओ out_मुक्त_queues;
		mutex_unlock(&pi->vi_mirror_mutex);
	पूर्ण

	netअगर_tx_start_all_queues(dev);
	वापस 0;

out_मुक्त_queues:
	cxgb4_port_mirror_मुक्त_queues(dev);

out_unlock:
	mutex_unlock(&pi->vi_mirror_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक cxgb_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;

	netअगर_tx_stop_all_queues(dev);
	netअगर_carrier_off(dev);
	ret = t4_enable_pi_params(adapter, adapter->pf, pi,
				  false, false, false);
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	cxgb4_dcb_reset(dev);
	dcb_tx_queue_prio_enable(dev, false);
#पूर्ण_अगर
	अगर (ret)
		वापस ret;

	अगर (pi->nmirrorqsets) अणु
		mutex_lock(&pi->vi_mirror_mutex);
		cxgb4_port_mirror_stop(dev);
		cxgb4_port_mirror_मुक्त_queues(dev);
		mutex_unlock(&pi->vi_mirror_mutex);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxgb4_create_server_filter(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
		__be32 sip, __be16 sport, __be16 vlan,
		अचिन्हित पूर्णांक queue, अचिन्हित अक्षर port, अचिन्हित अक्षर mask)
अणु
	पूर्णांक ret;
	काष्ठा filter_entry *f;
	काष्ठा adapter *adap;
	पूर्णांक i;
	u8 *val;

	adap = netdev2adap(dev);

	/* Adjust stid to correct filter index */
	stid -= adap->tids.sftid_base;
	stid += adap->tids.nftids;

	/* Check to make sure the filter requested is writable ...
	 */
	f = &adap->tids.ftid_tab[stid];
	ret = writable_filter(f);
	अगर (ret)
		वापस ret;

	/* Clear out any old resources being used by the filter beक्रमe
	 * we start स्थिरructing the new filter.
	 */
	अगर (f->valid)
		clear_filter(adap, f);

	/* Clear out filter specअगरications */
	स_रखो(&f->fs, 0, माप(काष्ठा ch_filter_specअगरication));
	f->fs.val.lport = be16_to_cpu(sport);
	f->fs.mask.lport  = ~0;
	val = (u8 *)&sip;
	अगर ((val[0] | val[1] | val[2] | val[3]) != 0) अणु
		क्रम (i = 0; i < 4; i++) अणु
			f->fs.val.lip[i] = val[i];
			f->fs.mask.lip[i] = ~0;
		पूर्ण
		अगर (adap->params.tp.vlan_pri_map & PORT_F) अणु
			f->fs.val.iport = port;
			f->fs.mask.iport = mask;
		पूर्ण
	पूर्ण

	अगर (adap->params.tp.vlan_pri_map & PROTOCOL_F) अणु
		f->fs.val.proto = IPPROTO_TCP;
		f->fs.mask.proto = ~0;
	पूर्ण

	f->fs.dirsteer = 1;
	f->fs.iq = queue;
	/* Mark filter as locked */
	f->locked = 1;
	f->fs.rpttid = 1;

	/* Save the actual tid. We need this to get the corresponding
	 * filter entry काष्ठाure in filter_rpl.
	 */
	f->tid = stid + adap->tids.ftid_base;
	ret = set_filter_wr(adap, stid);
	अगर (ret) अणु
		clear_filter(adap, f);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cxgb4_create_server_filter);

पूर्णांक cxgb4_हटाओ_server_filter(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
		अचिन्हित पूर्णांक queue, bool ipv6)
अणु
	काष्ठा filter_entry *f;
	काष्ठा adapter *adap;

	adap = netdev2adap(dev);

	/* Adjust stid to correct filter index */
	stid -= adap->tids.sftid_base;
	stid += adap->tids.nftids;

	f = &adap->tids.ftid_tab[stid];
	/* Unlock the filter */
	f->locked = 0;

	वापस delete_filter(adap, stid);
पूर्ण
EXPORT_SYMBOL(cxgb4_हटाओ_server_filter);

अटल व्योम cxgb_get_stats(काष्ठा net_device *dev,
			   काष्ठा rtnl_link_stats64 *ns)
अणु
	काष्ठा port_stats stats;
	काष्ठा port_info *p = netdev_priv(dev);
	काष्ठा adapter *adapter = p->adapter;

	/* Block retrieving statistics during EEH error
	 * recovery. Otherwise, the recovery might fail
	 * and the PCI device will be हटाओd permanently
	 */
	spin_lock(&adapter->stats_lock);
	अगर (!netअगर_device_present(dev)) अणु
		spin_unlock(&adapter->stats_lock);
		वापस;
	पूर्ण
	t4_get_port_stats_offset(adapter, p->tx_chan, &stats,
				 &p->stats_base);
	spin_unlock(&adapter->stats_lock);

	ns->tx_bytes   = stats.tx_octets;
	ns->tx_packets = stats.tx_frames;
	ns->rx_bytes   = stats.rx_octets;
	ns->rx_packets = stats.rx_frames;
	ns->multicast  = stats.rx_mcast_frames;

	/* detailed rx_errors */
	ns->rx_length_errors = stats.rx_jabber + stats.rx_too_दीर्घ +
			       stats.rx_runt;
	ns->rx_over_errors   = 0;
	ns->rx_crc_errors    = stats.rx_fcs_err;
	ns->rx_frame_errors  = stats.rx_symbol_err;
	ns->rx_dropped	     = stats.rx_ovflow0 + stats.rx_ovflow1 +
			       stats.rx_ovflow2 + stats.rx_ovflow3 +
			       stats.rx_trunc0 + stats.rx_trunc1 +
			       stats.rx_trunc2 + stats.rx_trunc3;
	ns->rx_missed_errors = 0;

	/* detailed tx_errors */
	ns->tx_पातed_errors   = 0;
	ns->tx_carrier_errors   = 0;
	ns->tx_fअगरo_errors      = 0;
	ns->tx_heartbeat_errors = 0;
	ns->tx_winकरोw_errors    = 0;

	ns->tx_errors = stats.tx_error_frames;
	ns->rx_errors = stats.rx_symbol_err + stats.rx_fcs_err +
		ns->rx_length_errors + stats.rx_len_err + ns->rx_fअगरo_errors;
पूर्ण

अटल पूर्णांक cxgb_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	अचिन्हित पूर्णांक mbox;
	पूर्णांक ret = 0, prtad, devad;
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा mii_ioctl_data *data = (काष्ठा mii_ioctl_data *)&req->अगरr_data;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		अगर (pi->mdio_addr < 0)
			वापस -EOPNOTSUPP;
		data->phy_id = pi->mdio_addr;
		अवरोध;
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		अगर (mdio_phy_id_is_c45(data->phy_id)) अणु
			prtad = mdio_phy_id_prtad(data->phy_id);
			devad = mdio_phy_id_devad(data->phy_id);
		पूर्ण अन्यथा अगर (data->phy_id < 32) अणु
			prtad = data->phy_id;
			devad = 0;
			data->reg_num &= 0x1f;
		पूर्ण अन्यथा
			वापस -EINVAL;

		mbox = pi->adapter->pf;
		अगर (cmd == SIOCGMIIREG)
			ret = t4_mdio_rd(pi->adapter, mbox, prtad, devad,
					 data->reg_num, &data->val_out);
		अन्यथा
			ret = t4_mdio_wr(pi->adapter, mbox, prtad, devad,
					 data->reg_num, data->val_in);
		अवरोध;
	हाल SIOCGHWTSTAMP:
		वापस copy_to_user(req->अगरr_data, &pi->tstamp_config,
				    माप(pi->tstamp_config)) ?
			-EFAULT : 0;
	हाल SIOCSHWTSTAMP:
		अगर (copy_from_user(&pi->tstamp_config, req->अगरr_data,
				   माप(pi->tstamp_config)))
			वापस -EFAULT;

		अगर (!is_t4(adapter->params.chip)) अणु
			चयन (pi->tstamp_config.tx_type) अणु
			हाल HWTSTAMP_TX_OFF:
			हाल HWTSTAMP_TX_ON:
				अवरोध;
			शेष:
				वापस -दुस्फल;
			पूर्ण

			चयन (pi->tstamp_config.rx_filter) अणु
			हाल HWTSTAMP_FILTER_NONE:
				pi->rxtstamp = false;
				अवरोध;
			हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
			हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
				cxgb4_ptprx_बारtamping(pi, pi->port_id,
							 PTP_TS_L4);
				अवरोध;
			हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
				cxgb4_ptprx_बारtamping(pi, pi->port_id,
							 PTP_TS_L2_L4);
				अवरोध;
			हाल HWTSTAMP_FILTER_ALL:
			हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
			हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
			हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
			हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
				pi->rxtstamp = true;
				अवरोध;
			शेष:
				pi->tstamp_config.rx_filter =
					HWTSTAMP_FILTER_NONE;
				वापस -दुस्फल;
			पूर्ण

			अगर ((pi->tstamp_config.tx_type == HWTSTAMP_TX_OFF) &&
			    (pi->tstamp_config.rx_filter ==
				HWTSTAMP_FILTER_NONE)) अणु
				अगर (cxgb4_ptp_txtype(adapter, pi->port_id) >= 0)
					pi->ptp_enable = false;
			पूर्ण

			अगर (pi->tstamp_config.rx_filter !=
				HWTSTAMP_FILTER_NONE) अणु
				अगर (cxgb4_ptp_redirect_rx_packet(adapter,
								 pi) >= 0)
					pi->ptp_enable = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* For T4 Adapters */
			चयन (pi->tstamp_config.rx_filter) अणु
			हाल HWTSTAMP_FILTER_NONE:
			pi->rxtstamp = false;
			अवरोध;
			हाल HWTSTAMP_FILTER_ALL:
			pi->rxtstamp = true;
			अवरोध;
			शेष:
			pi->tstamp_config.rx_filter =
			HWTSTAMP_FILTER_NONE;
			वापस -दुस्फल;
			पूर्ण
		पूर्ण
		वापस copy_to_user(req->अगरr_data, &pi->tstamp_config,
				    माप(pi->tstamp_config)) ?
			-EFAULT : 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम cxgb_set_rxmode(काष्ठा net_device *dev)
अणु
	/* unक्रमtunately we can't वापस errors to the stack */
	set_rxmode(dev, -1, false);
पूर्ण

अटल पूर्णांक cxgb_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	पूर्णांक ret;

	ret = t4_set_rxmode(pi->adapter, pi->adapter->mbox, pi->viid,
			    pi->viid_mirror, new_mtu, -1, -1, -1, -1, true);
	अगर (!ret)
		dev->mtu = new_mtu;
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
अटल पूर्णांक cxgb4_mgmt_खोलो(काष्ठा net_device *dev)
अणु
	/* Turn carrier off since we करोn't have to transmit anything on this
	 * पूर्णांकerface.
	 */
	netअगर_carrier_off(dev);
	वापस 0;
पूर्ण

/* Fill MAC address that will be asचिन्हित by the FW */
अटल व्योम cxgb4_mgmt_fill_vf_station_mac_addr(काष्ठा adapter *adap)
अणु
	u8 hw_addr[ETH_ALEN], macaddr[ETH_ALEN];
	अचिन्हित पूर्णांक i, vf, nvfs;
	u16 a, b;
	पूर्णांक err;
	u8 *na;

	err = t4_get_raw_vpd_params(adap, &adap->params.vpd);
	अगर (err)
		वापस;

	na = adap->params.vpd.na;
	क्रम (i = 0; i < ETH_ALEN; i++)
		hw_addr[i] = (hex2val(na[2 * i + 0]) * 16 +
			      hex2val(na[2 * i + 1]));

	a = (hw_addr[0] << 8) | hw_addr[1];
	b = (hw_addr[1] << 8) | hw_addr[2];
	a ^= b;
	a |= 0x0200;    /* locally asचिन्हित Ethernet MAC address */
	a &= ~0x0100;   /* not a multicast Ethernet MAC address */
	macaddr[0] = a >> 8;
	macaddr[1] = a & 0xff;

	क्रम (i = 2; i < 5; i++)
		macaddr[i] = hw_addr[i + 1];

	क्रम (vf = 0, nvfs = pci_sriov_get_totalvfs(adap->pdev);
		vf < nvfs; vf++) अणु
		macaddr[5] = adap->pf * nvfs + vf;
		ether_addr_copy(adap->vfinfo[vf].vf_mac_addr, macaddr);
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb4_mgmt_set_vf_mac(काष्ठा net_device *dev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक ret;

	/* verअगरy MAC addr is valid */
	अगर (!is_valid_ether_addr(mac)) अणु
		dev_err(pi->adapter->pdev_dev,
			"Invalid Ethernet address %pM for VF %d\n",
			mac, vf);
		वापस -EINVAL;
	पूर्ण

	dev_info(pi->adapter->pdev_dev,
		 "Setting MAC %pM on VF %d\n", mac, vf);
	ret = t4_set_vf_mac_acl(adap, vf + 1, 1, mac);
	अगर (!ret)
		ether_addr_copy(adap->vfinfo[vf].vf_mac_addr, mac);
	वापस ret;
पूर्ण

अटल पूर्णांक cxgb4_mgmt_get_vf_config(काष्ठा net_device *dev,
				    पूर्णांक vf, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा vf_info *vfinfo;

	अगर (vf >= adap->num_vfs)
		वापस -EINVAL;
	vfinfo = &adap->vfinfo[vf];

	ivi->vf = vf;
	ivi->max_tx_rate = vfinfo->tx_rate;
	ivi->min_tx_rate = 0;
	ether_addr_copy(ivi->mac, vfinfo->vf_mac_addr);
	ivi->vlan = vfinfo->vlan;
	ivi->linkstate = vfinfo->link_state;
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_mgmt_get_phys_port_id(काष्ठा net_device *dev,
				       काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	अचिन्हित पूर्णांक phy_port_id;

	phy_port_id = pi->adapter->adap_idx * 10 + pi->port_id;
	ppid->id_len = माप(phy_port_id);
	स_नकल(ppid->id, &phy_port_id, ppid->id_len);
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_mgmt_set_vf_rate(काष्ठा net_device *dev, पूर्णांक vf,
				  पूर्णांक min_tx_rate, पूर्णांक max_tx_rate)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	अचिन्हित पूर्णांक link_ok, speed, mtu;
	u32 fw_pfvf, fw_class;
	पूर्णांक class_id = vf;
	पूर्णांक ret;
	u16 pktsize;

	अगर (vf >= adap->num_vfs)
		वापस -EINVAL;

	अगर (min_tx_rate) अणु
		dev_err(adap->pdev_dev,
			"Min tx rate (%d) (> 0) for VF %d is Invalid.\n",
			min_tx_rate, vf);
		वापस -EINVAL;
	पूर्ण

	अगर (max_tx_rate == 0) अणु
		/* unbind VF to to any Traffic Class */
		fw_pfvf =
		    (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) |
		     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_SCHEDCLASS_ETH));
		fw_class = 0xffffffff;
		ret = t4_set_params(adap, adap->mbox, adap->pf, vf + 1, 1,
				    &fw_pfvf, &fw_class);
		अगर (ret) अणु
			dev_err(adap->pdev_dev,
				"Err %d in unbinding PF %d VF %d from TX Rate Limiting\n",
				ret, adap->pf, vf);
			वापस -EINVAL;
		पूर्ण
		dev_info(adap->pdev_dev,
			 "PF %d VF %d is unbound from TX Rate Limiting\n",
			 adap->pf, vf);
		adap->vfinfo[vf].tx_rate = 0;
		वापस 0;
	पूर्ण

	ret = t4_get_link_params(pi, &link_ok, &speed, &mtu);
	अगर (ret != FW_SUCCESS) अणु
		dev_err(adap->pdev_dev,
			"Failed to get link information for VF %d\n", vf);
		वापस -EINVAL;
	पूर्ण

	अगर (!link_ok) अणु
		dev_err(adap->pdev_dev, "Link down for VF %d\n", vf);
		वापस -EINVAL;
	पूर्ण

	अगर (max_tx_rate > speed) अणु
		dev_err(adap->pdev_dev,
			"Max tx rate %d for VF %d can't be > link-speed %u",
			max_tx_rate, vf, speed);
		वापस -EINVAL;
	पूर्ण

	pktsize = mtu;
	/* subtract ethhdr size and 4 bytes crc since, f/w appends it */
	pktsize = pktsize - माप(काष्ठा ethhdr) - 4;
	/* subtract ipv4 hdr size, tcp hdr size to get typical IPv4 MSS size */
	pktsize = pktsize - माप(काष्ठा iphdr) - माप(काष्ठा tcphdr);
	/* configure Traffic Class क्रम rate-limiting */
	ret = t4_sched_params(adap, SCHED_CLASS_TYPE_PACKET,
			      SCHED_CLASS_LEVEL_CL_RL,
			      SCHED_CLASS_MODE_CLASS,
			      SCHED_CLASS_RATEUNIT_BITS,
			      SCHED_CLASS_RATEMODE_ABS,
			      pi->tx_chan, class_id, 0,
			      max_tx_rate * 1000, 0, pktsize, 0);
	अगर (ret) अणु
		dev_err(adap->pdev_dev, "Err %d for Traffic Class config\n",
			ret);
		वापस -EINVAL;
	पूर्ण
	dev_info(adap->pdev_dev,
		 "Class %d with MSS %u configured with rate %u\n",
		 class_id, pktsize, max_tx_rate);

	/* bind VF to configured Traffic Class */
	fw_pfvf = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) |
		   FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_SCHEDCLASS_ETH));
	fw_class = class_id;
	ret = t4_set_params(adap, adap->mbox, adap->pf, vf + 1, 1, &fw_pfvf,
			    &fw_class);
	अगर (ret) अणु
		dev_err(adap->pdev_dev,
			"Err %d in binding PF %d VF %d to Traffic Class %d\n",
			ret, adap->pf, vf, class_id);
		वापस -EINVAL;
	पूर्ण
	dev_info(adap->pdev_dev, "PF %d VF %d is bound to Class %d\n",
		 adap->pf, vf, class_id);
	adap->vfinfo[vf].tx_rate = max_tx_rate;
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_mgmt_set_vf_vlan(काष्ठा net_device *dev, पूर्णांक vf,
				  u16 vlan, u8 qos, __be16 vlan_proto)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक ret;

	अगर (vf >= adap->num_vfs || vlan > 4095 || qos > 7)
		वापस -EINVAL;

	अगर (vlan_proto != htons(ETH_P_8021Q) || qos != 0)
		वापस -EPROTONOSUPPORT;

	ret = t4_set_vlan_acl(adap, adap->mbox, vf + 1, vlan);
	अगर (!ret) अणु
		adap->vfinfo[vf].vlan = vlan;
		वापस 0;
	पूर्ण

	dev_err(adap->pdev_dev, "Err %d %s VLAN ACL for PF/VF %d/%d\n",
		ret, (vlan ? "setting" : "clearing"), adap->pf, vf);
	वापस ret;
पूर्ण

अटल पूर्णांक cxgb4_mgmt_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक vf,
					पूर्णांक link)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	u32 param, val;
	पूर्णांक ret = 0;

	अगर (vf >= adap->num_vfs)
		वापस -EINVAL;

	चयन (link) अणु
	हाल IFLA_VF_LINK_STATE_AUTO:
		val = FW_VF_LINK_STATE_AUTO;
		अवरोध;

	हाल IFLA_VF_LINK_STATE_ENABLE:
		val = FW_VF_LINK_STATE_ENABLE;
		अवरोध;

	हाल IFLA_VF_LINK_STATE_DISABLE:
		val = FW_VF_LINK_STATE_DISABLE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_LINK_STATE));
	ret = t4_set_params(adap, adap->mbox, adap->pf, vf + 1, 1,
			    &param, &val);
	अगर (ret) अणु
		dev_err(adap->pdev_dev,
			"Error %d in setting PF %d VF %d link state\n",
			ret, adap->pf, vf);
		वापस -EINVAL;
	पूर्ण

	adap->vfinfo[vf].link_state = link;
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

अटल पूर्णांक cxgb_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक ret;
	काष्ठा sockaddr *addr = p;
	काष्ठा port_info *pi = netdev_priv(dev);

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	ret = cxgb4_update_mac_filt(pi, pi->viid, &pi->xact_addr_filt,
				    addr->sa_data, true, &pi->smt_idx);
	अगर (ret < 0)
		वापस ret;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम cxgb_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;

	अगर (adap->flags & CXGB4_USING_MSIX) अणु
		पूर्णांक i;
		काष्ठा sge_eth_rxq *rx = &adap->sge.ethrxq[pi->first_qset];

		क्रम (i = pi->nqsets; i; i--, rx++)
			t4_sge_पूर्णांकr_msix(0, &rx->rspq);
	पूर्ण अन्यथा
		t4_पूर्णांकr_handler(adap)(0, adap);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cxgb_set_tx_maxrate(काष्ठा net_device *dev, पूर्णांक index, u32 rate)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा ch_sched_queue qe = अणु 0 पूर्ण;
	काष्ठा ch_sched_params p = अणु 0 पूर्ण;
	काष्ठा sched_class *e;
	u32 req_rate;
	पूर्णांक err = 0;

	अगर (!can_sched(dev))
		वापस -ENOTSUPP;

	अगर (index < 0 || index > pi->nqsets - 1)
		वापस -EINVAL;

	अगर (!(adap->flags & CXGB4_FULL_INIT_DONE)) अणु
		dev_err(adap->pdev_dev,
			"Failed to rate limit on queue %d. Link Down?\n",
			index);
		वापस -EINVAL;
	पूर्ण

	qe.queue = index;
	e = cxgb4_sched_queue_lookup(dev, &qe);
	अगर (e && e->info.u.params.level != SCHED_CLASS_LEVEL_CL_RL) अणु
		dev_err(adap->pdev_dev,
			"Queue %u already bound to class %u of type: %u\n",
			index, e->idx, e->info.u.params.level);
		वापस -EBUSY;
	पूर्ण

	/* Convert from Mbps to Kbps */
	req_rate = rate * 1000;

	/* Max rate is 100 Gbps */
	अगर (req_rate > SCHED_MAX_RATE_KBPS) अणु
		dev_err(adap->pdev_dev,
			"Invalid rate %u Mbps, Max rate is %u Mbps\n",
			rate, SCHED_MAX_RATE_KBPS / 1000);
		वापस -दुस्फल;
	पूर्ण

	/* First unbind the queue from any existing class */
	स_रखो(&qe, 0, माप(qe));
	qe.queue = index;
	qe.class = SCHED_CLS_NONE;

	err = cxgb4_sched_class_unbind(dev, (व्योम *)(&qe), SCHED_QUEUE);
	अगर (err) अणु
		dev_err(adap->pdev_dev,
			"Unbinding Queue %d on port %d fail. Err: %d\n",
			index, pi->port_id, err);
		वापस err;
	पूर्ण

	/* Queue alपढ़ोy unbound */
	अगर (!req_rate)
		वापस 0;

	/* Fetch any available unused or matching scheduling class */
	p.type = SCHED_CLASS_TYPE_PACKET;
	p.u.params.level    = SCHED_CLASS_LEVEL_CL_RL;
	p.u.params.mode     = SCHED_CLASS_MODE_CLASS;
	p.u.params.rateunit = SCHED_CLASS_RATEUNIT_BITS;
	p.u.params.ratemode = SCHED_CLASS_RATEMODE_ABS;
	p.u.params.channel  = pi->tx_chan;
	p.u.params.class    = SCHED_CLS_NONE;
	p.u.params.minrate  = 0;
	p.u.params.maxrate  = req_rate;
	p.u.params.weight   = 0;
	p.u.params.pktsize  = dev->mtu;

	e = cxgb4_sched_class_alloc(dev, &p);
	अगर (!e)
		वापस -ENOMEM;

	/* Bind the queue to a scheduling class */
	स_रखो(&qe, 0, माप(qe));
	qe.queue = index;
	qe.class = e->idx;

	err = cxgb4_sched_class_bind(dev, (व्योम *)(&qe), SCHED_QUEUE);
	अगर (err)
		dev_err(adap->pdev_dev,
			"Queue rate limiting failed. Err: %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक cxgb_setup_tc_flower(काष्ठा net_device *dev,
				काष्ठा flow_cls_offload *cls_flower)
अणु
	चयन (cls_flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस cxgb4_tc_flower_replace(dev, cls_flower);
	हाल FLOW_CLS_DESTROY:
		वापस cxgb4_tc_flower_destroy(dev, cls_flower);
	हाल FLOW_CLS_STATS:
		वापस cxgb4_tc_flower_stats(dev, cls_flower);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb_setup_tc_cls_u32(काष्ठा net_device *dev,
				 काष्ठा tc_cls_u32_offload *cls_u32)
अणु
	चयन (cls_u32->command) अणु
	हाल TC_CLSU32_NEW_KNODE:
	हाल TC_CLSU32_REPLACE_KNODE:
		वापस cxgb4_config_knode(dev, cls_u32);
	हाल TC_CLSU32_DELETE_KNODE:
		वापस cxgb4_delete_knode(dev, cls_u32);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb_setup_tc_matchall(काष्ठा net_device *dev,
				  काष्ठा tc_cls_matchall_offload *cls_matchall,
				  bool ingress)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

	अगर (!adap->tc_matchall)
		वापस -ENOMEM;

	चयन (cls_matchall->command) अणु
	हाल TC_CLSMATCHALL_REPLACE:
		वापस cxgb4_tc_matchall_replace(dev, cls_matchall, ingress);
	हाल TC_CLSMATCHALL_DESTROY:
		वापस cxgb4_tc_matchall_destroy(dev, cls_matchall, ingress);
	हाल TC_CLSMATCHALL_STATS:
		अगर (ingress)
			वापस cxgb4_tc_matchall_stats(dev, cls_matchall);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक cxgb_setup_tc_block_ingress_cb(क्रमागत tc_setup_type type,
					  व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा net_device *dev = cb_priv;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);

	अगर (!(adap->flags & CXGB4_FULL_INIT_DONE)) अणु
		dev_err(adap->pdev_dev,
			"Failed to setup tc on port %d. Link Down?\n",
			pi->port_id);
		वापस -EINVAL;
	पूर्ण

	अगर (!tc_cls_can_offload_and_chain0(dev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSU32:
		वापस cxgb_setup_tc_cls_u32(dev, type_data);
	हाल TC_SETUP_CLSFLOWER:
		वापस cxgb_setup_tc_flower(dev, type_data);
	हाल TC_SETUP_CLSMATCHALL:
		वापस cxgb_setup_tc_matchall(dev, type_data, true);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb_setup_tc_block_egress_cb(क्रमागत tc_setup_type type,
					 व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा net_device *dev = cb_priv;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);

	अगर (!(adap->flags & CXGB4_FULL_INIT_DONE)) अणु
		dev_err(adap->pdev_dev,
			"Failed to setup tc on port %d. Link Down?\n",
			pi->port_id);
		वापस -EINVAL;
	पूर्ण

	अगर (!tc_cls_can_offload_and_chain0(dev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSMATCHALL:
		वापस cxgb_setup_tc_matchall(dev, type_data, false);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक cxgb_setup_tc_mqprio(काष्ठा net_device *dev,
				काष्ठा tc_mqprio_qopt_offload *mqprio)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

	अगर (!is_ethofld(adap) || !adap->tc_mqprio)
		वापस -ENOMEM;

	वापस cxgb4_setup_tc_mqprio(dev, mqprio);
पूर्ण

अटल LIST_HEAD(cxgb_block_cb_list);

अटल पूर्णांक cxgb_setup_tc_block(काष्ठा net_device *dev,
			       काष्ठा flow_block_offload *f)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	flow_setup_cb_t *cb;
	bool ingress_only;

	pi->tc_block_shared = f->block_shared;
	अगर (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS) अणु
		cb = cxgb_setup_tc_block_egress_cb;
		ingress_only = false;
	पूर्ण अन्यथा अणु
		cb = cxgb_setup_tc_block_ingress_cb;
		ingress_only = true;
	पूर्ण

	वापस flow_block_cb_setup_simple(f, &cxgb_block_cb_list,
					  cb, pi, dev, ingress_only);
पूर्ण

अटल पूर्णांक cxgb_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			 व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_QDISC_MQPRIO:
		वापस cxgb_setup_tc_mqprio(dev, type_data);
	हाल TC_SETUP_BLOCK:
		वापस cxgb_setup_tc_block(dev, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb_udp_tunnel_unset_port(काष्ठा net_device *netdev,
				      अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक entry,
				      काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adapter = pi->adapter;
	u8 match_all_mac[] = अणु 0, 0, 0, 0, 0, 0 पूर्ण;
	पूर्णांक ret = 0, i;

	चयन (ti->type) अणु
	हाल UDP_TUNNEL_TYPE_VXLAN:
		adapter->vxlan_port = 0;
		t4_ग_लिखो_reg(adapter, MPS_RX_VXLAN_TYPE_A, 0);
		अवरोध;
	हाल UDP_TUNNEL_TYPE_GENEVE:
		adapter->geneve_port = 0;
		t4_ग_लिखो_reg(adapter, MPS_RX_GENEVE_TYPE_A, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Matchall mac entries can be deleted only after all tunnel ports
	 * are brought करोwn or हटाओd.
	 */
	अगर (!adapter->rawf_cnt)
		वापस 0;
	क्रम_each_port(adapter, i) अणु
		pi = adap2pinfo(adapter, i);
		ret = t4_मुक्त_raw_mac_filt(adapter, pi->viid,
					   match_all_mac, match_all_mac,
					   adapter->rawf_start + pi->port_id,
					   1, pi->port_id, false);
		अगर (ret < 0) अणु
			netdev_info(netdev, "Failed to free mac filter entry, for port %d\n",
				    i);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb_udp_tunnel_set_port(काष्ठा net_device *netdev,
				    अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक entry,
				    काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adapter = pi->adapter;
	u8 match_all_mac[] = अणु 0, 0, 0, 0, 0, 0 पूर्ण;
	पूर्णांक i, ret;

	चयन (ti->type) अणु
	हाल UDP_TUNNEL_TYPE_VXLAN:
		adapter->vxlan_port = ti->port;
		t4_ग_लिखो_reg(adapter, MPS_RX_VXLAN_TYPE_A,
			     VXLAN_V(be16_to_cpu(ti->port)) | VXLAN_EN_F);
		अवरोध;
	हाल UDP_TUNNEL_TYPE_GENEVE:
		adapter->geneve_port = ti->port;
		t4_ग_लिखो_reg(adapter, MPS_RX_GENEVE_TYPE_A,
			     GENEVE_V(be16_to_cpu(ti->port)) | GENEVE_EN_F);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Create a 'match all' mac filter entry क्रम inner mac,
	 * अगर raw mac पूर्णांकerface is supported. Once the linux kernel provides
	 * driver entry poपूर्णांकs क्रम adding/deleting the inner mac addresses,
	 * we will हटाओ this 'match all' entry and fallback to adding
	 * exact match filters.
	 */
	क्रम_each_port(adapter, i) अणु
		pi = adap2pinfo(adapter, i);

		ret = t4_alloc_raw_mac_filt(adapter, pi->viid,
					    match_all_mac,
					    match_all_mac,
					    adapter->rawf_start + pi->port_id,
					    1, pi->port_id, false);
		अगर (ret < 0) अणु
			netdev_info(netdev, "Failed to allocate a mac filter entry, not adding port %d\n",
				    be16_to_cpu(ti->port));
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info cxgb_udp_tunnels = अणु
	.set_port	= cxgb_udp_tunnel_set_port,
	.unset_port	= cxgb_udp_tunnel_unset_port,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN,  पूर्ण,
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_GENEVE, पूर्ण,
	पूर्ण,
पूर्ण;

अटल netdev_features_t cxgb_features_check(काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) < CHELSIO_T6)
		वापस features;

	/* Check अगर hw supports offload क्रम this packet */
	अगर (!skb->encapsulation || cxgb_encap_offload_supported(skb))
		वापस features;

	/* Offload is not supported क्रम this encapsulated packet */
	वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
पूर्ण

अटल netdev_features_t cxgb_fix_features(काष्ठा net_device *dev,
					   netdev_features_t features)
अणु
	/* Disable GRO, अगर RX_CSUM is disabled */
	अगर (!(features & NETIF_F_RXCSUM))
		features &= ~NETIF_F_GRO;

	वापस features;
पूर्ण

अटल स्थिर काष्ठा net_device_ops cxgb4_netdev_ops = अणु
	.nकरो_खोलो             = cxgb_खोलो,
	.nकरो_stop             = cxgb_बंद,
	.nकरो_start_xmit       = t4_start_xmit,
	.nकरो_select_queue     =	cxgb_select_queue,
	.nकरो_get_stats64      = cxgb_get_stats,
	.nकरो_set_rx_mode      = cxgb_set_rxmode,
	.nकरो_set_mac_address  = cxgb_set_mac_addr,
	.nकरो_set_features     = cxgb_set_features,
	.nकरो_validate_addr    = eth_validate_addr,
	.nकरो_करो_ioctl         = cxgb_ioctl,
	.nकरो_change_mtu       = cxgb_change_mtu,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller  = cxgb_netpoll,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CHELSIO_T4_FCOE
	.nकरो_fcoe_enable      = cxgb_fcoe_enable,
	.nकरो_fcoe_disable     = cxgb_fcoe_disable,
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */
	.nकरो_set_tx_maxrate   = cxgb_set_tx_maxrate,
	.nकरो_setup_tc         = cxgb_setup_tc,
	.nकरो_features_check   = cxgb_features_check,
	.nकरो_fix_features     = cxgb_fix_features,
पूर्ण;

#अगर_घोषित CONFIG_PCI_IOV
अटल स्थिर काष्ठा net_device_ops cxgb4_mgmt_netdev_ops = अणु
	.nकरो_खोलो               = cxgb4_mgmt_खोलो,
	.nकरो_set_vf_mac         = cxgb4_mgmt_set_vf_mac,
	.nकरो_get_vf_config      = cxgb4_mgmt_get_vf_config,
	.nकरो_set_vf_rate        = cxgb4_mgmt_set_vf_rate,
	.nकरो_get_phys_port_id   = cxgb4_mgmt_get_phys_port_id,
	.nकरो_set_vf_vlan        = cxgb4_mgmt_set_vf_vlan,
	.nकरो_set_vf_link_state	= cxgb4_mgmt_set_vf_link_state,
पूर्ण;
#पूर्ण_अगर

अटल व्योम cxgb4_mgmt_get_drvinfo(काष्ठा net_device *dev,
				   काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);

	strlcpy(info->driver, cxgb4_driver_name, माप(info->driver));
	strlcpy(info->bus_info, pci_name(adapter->pdev),
		माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops cxgb4_mgmt_ethtool_ops = अणु
	.get_drvinfo       = cxgb4_mgmt_get_drvinfo,
पूर्ण;

अटल व्योम notअगरy_fatal_err(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adap;

	adap = container_of(work, काष्ठा adapter, fatal_err_notअगरy_task);
	notअगरy_ulds(adap, CXGB4_STATE_FATAL_ERROR);
पूर्ण

व्योम t4_fatal_err(काष्ठा adapter *adap)
अणु
	पूर्णांक port;

	अगर (pci_channel_offline(adap->pdev))
		वापस;

	/* Disable the SGE since ULDs are going to मुक्त resources that
	 * could be exposed to the adapter.  RDMA MWs क्रम example...
	 */
	t4_shutकरोwn_adapter(adap);
	क्रम_each_port(adap, port) अणु
		काष्ठा net_device *dev = adap->port[port];

		/* If we get here in very early initialization the network
		 * devices may not have been set up yet.
		 */
		अगर (!dev)
			जारी;

		netअगर_tx_stop_all_queues(dev);
		netअगर_carrier_off(dev);
	पूर्ण
	dev_alert(adap->pdev_dev, "encountered fatal error, adapter stopped\n");
	queue_work(adap->workq, &adap->fatal_err_notअगरy_task);
पूर्ण

अटल व्योम setup_memwin(काष्ठा adapter *adap)
अणु
	u32 nic_win_base = t4_get_util_winकरोw(adap);

	t4_setup_memwin(adap, nic_win_base, MEMWIN_NIC);
पूर्ण

अटल व्योम setup_memwin_rdma(काष्ठा adapter *adap)
अणु
	अगर (adap->vres.ocq.size) अणु
		u32 start;
		अचिन्हित पूर्णांक sz_kb;

		start = t4_पढ़ो_pcie_cfg4(adap, PCI_BASE_ADDRESS_2);
		start &= PCI_BASE_ADDRESS_MEM_MASK;
		start += OCQ_WIN_OFFSET(adap->pdev, &adap->vres);
		sz_kb = roundup_घात_of_two(adap->vres.ocq.size) >> 10;
		t4_ग_लिखो_reg(adap,
			     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, 3),
			     start | BIR_V(1) | WINDOW_V(ilog2(sz_kb)));
		t4_ग_लिखो_reg(adap,
			     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, 3),
			     adap->vres.ocq.start);
		t4_पढ़ो_reg(adap,
			    PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, 3));
	पूर्ण
पूर्ण

/* HMA Definitions */

/* The maximum number of address that can be send in a single FW cmd */
#घोषणा HMA_MAX_ADDR_IN_CMD	5

#घोषणा HMA_PAGE_SIZE		PAGE_SIZE

#घोषणा HMA_MAX_NO_FW_ADDRESS	(16 << 10)  /* FW supports 16K addresses */

#घोषणा HMA_PAGE_ORDER					\
	((HMA_PAGE_SIZE < HMA_MAX_NO_FW_ADDRESS) ?	\
	ilog2(HMA_MAX_NO_FW_ADDRESS / HMA_PAGE_SIZE) : 0)

/* The minimum and maximum possible HMA sizes that can be specअगरied in the FW
 * configuration(in units of MB).
 */
#घोषणा HMA_MIN_TOTAL_SIZE	1
#घोषणा HMA_MAX_TOTAL_SIZE				\
	(((HMA_PAGE_SIZE << HMA_PAGE_ORDER) *		\
	  HMA_MAX_NO_FW_ADDRESS) >> 20)

अटल व्योम adap_मुक्त_hma_mem(काष्ठा adapter *adapter)
अणु
	काष्ठा scatterlist *iter;
	काष्ठा page *page;
	पूर्णांक i;

	अगर (!adapter->hma.sgt)
		वापस;

	अगर (adapter->hma.flags & HMA_DMA_MAPPED_FLAG) अणु
		dma_unmap_sg(adapter->pdev_dev, adapter->hma.sgt->sgl,
			     adapter->hma.sgt->nents, PCI_DMA_BIसूचीECTIONAL);
		adapter->hma.flags &= ~HMA_DMA_MAPPED_FLAG;
	पूर्ण

	क्रम_each_sg(adapter->hma.sgt->sgl, iter,
		    adapter->hma.sgt->orig_nents, i) अणु
		page = sg_page(iter);
		अगर (page)
			__मुक्त_pages(page, HMA_PAGE_ORDER);
	पूर्ण

	kमुक्त(adapter->hma.phy_addr);
	sg_मुक्त_table(adapter->hma.sgt);
	kमुक्त(adapter->hma.sgt);
	adapter->hma.sgt = शून्य;
पूर्ण

अटल पूर्णांक adap_config_hma(काष्ठा adapter *adapter)
अणु
	काष्ठा scatterlist *sgl, *iter;
	काष्ठा sg_table *sgt;
	काष्ठा page *newpage;
	अचिन्हित पूर्णांक i, j, k;
	u32 param, hma_size;
	अचिन्हित पूर्णांक ncmds;
	माप_प्रकार page_size;
	u32 page_order;
	पूर्णांक node, ret;

	/* HMA is supported only क्रम T6+ cards.
	 * Aव्योम initializing HMA in kdump kernels.
	 */
	अगर (is_kdump_kernel() ||
	    CHELSIO_CHIP_VERSION(adapter->params.chip) < CHELSIO_T6)
		वापस 0;

	/* Get the HMA region size required by fw */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_HMA_SIZE));
	ret = t4_query_params(adapter, adapter->mbox, adapter->pf, 0,
			      1, &param, &hma_size);
	/* An error means card has its own memory or HMA is not supported by
	 * the firmware. Return without any errors.
	 */
	अगर (ret || !hma_size)
		वापस 0;

	अगर (hma_size < HMA_MIN_TOTAL_SIZE ||
	    hma_size > HMA_MAX_TOTAL_SIZE) अणु
		dev_err(adapter->pdev_dev,
			"HMA size %uMB beyond bounds(%u-%lu)MB\n",
			hma_size, HMA_MIN_TOTAL_SIZE, HMA_MAX_TOTAL_SIZE);
		वापस -EINVAL;
	पूर्ण

	page_size = HMA_PAGE_SIZE;
	page_order = HMA_PAGE_ORDER;
	adapter->hma.sgt = kzalloc(माप(*adapter->hma.sgt), GFP_KERNEL);
	अगर (unlikely(!adapter->hma.sgt)) अणु
		dev_err(adapter->pdev_dev, "HMA SG table allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	sgt = adapter->hma.sgt;
	/* FW वापसed value will be in MB's
	 */
	sgt->orig_nents = (hma_size << 20) / (page_size << page_order);
	अगर (sg_alloc_table(sgt, sgt->orig_nents, GFP_KERNEL)) अणु
		dev_err(adapter->pdev_dev, "HMA SGL allocation failed\n");
		kमुक्त(adapter->hma.sgt);
		adapter->hma.sgt = शून्य;
		वापस -ENOMEM;
	पूर्ण

	sgl = adapter->hma.sgt->sgl;
	node = dev_to_node(adapter->pdev_dev);
	क्रम_each_sg(sgl, iter, sgt->orig_nents, i) अणु
		newpage = alloc_pages_node(node, __GFP_NOWARN | GFP_KERNEL |
					   __GFP_ZERO, page_order);
		अगर (!newpage) अणु
			dev_err(adapter->pdev_dev,
				"Not enough memory for HMA page allocation\n");
			ret = -ENOMEM;
			जाओ मुक्त_hma;
		पूर्ण
		sg_set_page(iter, newpage, page_size << page_order, 0);
	पूर्ण

	sgt->nents = dma_map_sg(adapter->pdev_dev, sgl, sgt->orig_nents,
				DMA_BIसूचीECTIONAL);
	अगर (!sgt->nents) अणु
		dev_err(adapter->pdev_dev,
			"Not enough memory for HMA DMA mapping");
		ret = -ENOMEM;
		जाओ मुक्त_hma;
	पूर्ण
	adapter->hma.flags |= HMA_DMA_MAPPED_FLAG;

	adapter->hma.phy_addr = kसुस्मृति(sgt->nents, माप(dma_addr_t),
					GFP_KERNEL);
	अगर (unlikely(!adapter->hma.phy_addr))
		जाओ मुक्त_hma;

	क्रम_each_sg(sgl, iter, sgt->nents, i) अणु
		newpage = sg_page(iter);
		adapter->hma.phy_addr[i] = sg_dma_address(iter);
	पूर्ण

	ncmds = DIV_ROUND_UP(sgt->nents, HMA_MAX_ADDR_IN_CMD);
	/* Pass on the addresses to firmware */
	क्रम (i = 0, k = 0; i < ncmds; i++, k += HMA_MAX_ADDR_IN_CMD) अणु
		काष्ठा fw_hma_cmd hma_cmd;
		u8 naddr = HMA_MAX_ADDR_IN_CMD;
		u8 soc = 0, eoc = 0;
		u8 hma_mode = 1; /* Presently we support only Page table mode */

		soc = (i == 0) ? 1 : 0;
		eoc = (i == ncmds - 1) ? 1 : 0;

		/* For last cmd, set naddr corresponding to reमुख्यing
		 * addresses
		 */
		अगर (i == ncmds - 1) अणु
			naddr = sgt->nents % HMA_MAX_ADDR_IN_CMD;
			naddr = naddr ? naddr : HMA_MAX_ADDR_IN_CMD;
		पूर्ण
		स_रखो(&hma_cmd, 0, माप(hma_cmd));
		hma_cmd.op_pkd = htonl(FW_CMD_OP_V(FW_HMA_CMD) |
				       FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
		hma_cmd.retval_len16 = htonl(FW_LEN16(hma_cmd));

		hma_cmd.mode_to_pcie_params =
			htonl(FW_HMA_CMD_MODE_V(hma_mode) |
			      FW_HMA_CMD_SOC_V(soc) | FW_HMA_CMD_EOC_V(eoc));

		/* HMA cmd size specअगरied in MB's */
		hma_cmd.naddr_size =
			htonl(FW_HMA_CMD_SIZE_V(hma_size) |
			      FW_HMA_CMD_NADDR_V(naddr));

		/* Total Page size specअगरied in units of 4K */
		hma_cmd.addr_size_pkd =
			htonl(FW_HMA_CMD_ADDR_SIZE_V
				((page_size << page_order) >> 12));

		/* Fill the 5 addresses */
		क्रम (j = 0; j < naddr; j++) अणु
			hma_cmd.phy_address[j] =
				cpu_to_be64(adapter->hma.phy_addr[j + k]);
		पूर्ण
		ret = t4_wr_mbox(adapter, adapter->mbox, &hma_cmd,
				 माप(hma_cmd), &hma_cmd);
		अगर (ret) अणु
			dev_err(adapter->pdev_dev,
				"HMA FW command failed with err %d\n", ret);
			जाओ मुक्त_hma;
		पूर्ण
	पूर्ण

	अगर (!ret)
		dev_info(adapter->pdev_dev,
			 "Reserved %uMB host memory for HMA\n", hma_size);
	वापस ret;

मुक्त_hma:
	adap_मुक्त_hma_mem(adapter);
	वापस ret;
पूर्ण

अटल पूर्णांक adap_init1(काष्ठा adapter *adap, काष्ठा fw_caps_config_cmd *c)
अणु
	u32 v;
	पूर्णांक ret;

	/* Now that we've successfully configured and initialized the adapter
	 * can ask the Firmware what resources it has provisioned क्रम us.
	 */
	ret = t4_get_pfres(adap);
	अगर (ret) अणु
		dev_err(adap->pdev_dev,
			"Unable to retrieve resource provisioning information\n");
		वापस ret;
	पूर्ण

	/* get device capabilities */
	स_रखो(c, 0, माप(*c));
	c->op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
			       FW_CMD_REQUEST_F | FW_CMD_READ_F);
	c->cfvalid_to_len16 = htonl(FW_LEN16(*c));
	ret = t4_wr_mbox(adap, adap->mbox, c, माप(*c), c);
	अगर (ret < 0)
		वापस ret;

	c->op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
			       FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	ret = t4_wr_mbox(adap, adap->mbox, c, माप(*c), शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = t4_config_glbl_rss(adap, adap->pf,
				 FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL,
				 FW_RSS_GLB_CONFIG_CMD_TNLMAPEN_F |
				 FW_RSS_GLB_CONFIG_CMD_TNLALLLKP_F);
	अगर (ret < 0)
		वापस ret;

	ret = t4_cfg_pfvf(adap, adap->mbox, adap->pf, 0, adap->sge.egr_sz, 64,
			  MAX_INGQ, 0, 0, 4, 0xf, 0xf, 16, FW_CMD_CAP_PF,
			  FW_CMD_CAP_PF);
	अगर (ret < 0)
		वापस ret;

	t4_sge_init(adap);

	/* tweak some settings */
	t4_ग_लिखो_reg(adap, TP_SHIFT_CNT_A, 0x64f8849);
	t4_ग_लिखो_reg(adap, ULP_RX_TDDP_PSZ_A, HPZ0_V(PAGE_SHIFT - 12));
	t4_ग_लिखो_reg(adap, TP_PIO_ADDR_A, TP_INGRESS_CONFIG_A);
	v = t4_पढ़ो_reg(adap, TP_PIO_DATA_A);
	t4_ग_लिखो_reg(adap, TP_PIO_DATA_A, v & ~CSUM_HAS_PSEUDO_HDR_F);

	/* first 4 Tx modulation queues poपूर्णांक to consecutive Tx channels */
	adap->params.tp.tx_modq_map = 0xE4;
	t4_ग_लिखो_reg(adap, TP_TX_MOD_QUEUE_REQ_MAP_A,
		     TX_MOD_QUEUE_REQ_MAP_V(adap->params.tp.tx_modq_map));

	/* associate each Tx modulation queue with consecutive Tx channels */
	v = 0x84218421;
	t4_ग_लिखो_indirect(adap, TP_PIO_ADDR_A, TP_PIO_DATA_A,
			  &v, 1, TP_TX_SCHED_HDR_A);
	t4_ग_लिखो_indirect(adap, TP_PIO_ADDR_A, TP_PIO_DATA_A,
			  &v, 1, TP_TX_SCHED_FIFO_A);
	t4_ग_लिखो_indirect(adap, TP_PIO_ADDR_A, TP_PIO_DATA_A,
			  &v, 1, TP_TX_SCHED_PCMD_A);

#घोषणा T4_TX_MODQ_10G_WEIGHT_DEFAULT 16 /* in KB units */
	अगर (is_offload(adap)) अणु
		t4_ग_लिखो_reg(adap, TP_TX_MOD_QUEUE_WEIGHT0_A,
			     TX_MODQ_WEIGHT0_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT1_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT2_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT3_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT));
		t4_ग_लिखो_reg(adap, TP_TX_MOD_CHANNEL_WEIGHT_A,
			     TX_MODQ_WEIGHT0_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT1_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT2_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT) |
			     TX_MODQ_WEIGHT3_V(T4_TX_MODQ_10G_WEIGHT_DEFAULT));
	पूर्ण

	/* get basic stuff going */
	वापस t4_early_init(adap, adap->pf);
पूर्ण

/*
 * Max # of ATIDs.  The असलolute HW max is 16K but we keep it lower.
 */
#घोषणा MAX_ATIDS 8192U

/*
 * Phase 0 of initialization: contact FW, obtain config, perक्रमm basic init.
 *
 * If the firmware we're dealing with has Configuration File support, then
 * we use that to perक्रमm all configuration
 */

/*
 * Tweak configuration based on module parameters, etc.  Most of these have
 * शेषs asचिन्हित to them by Firmware Configuration Files (अगर we're using
 * them) but need to be explicitly set अगर we're using hard-coded
 * initialization.  But even in the हाल of using Firmware Configuration
 * Files, we'd like to expose the ability to change these via module
 * parameters so these are essentially common tweaks/settings क्रम
 * Configuration Files and hard-coded initialization ...
 */
अटल पूर्णांक adap_init0_tweaks(काष्ठा adapter *adapter)
अणु
	/*
	 * Fix up various Host-Dependent Parameters like Page Size, Cache
	 * Line Size, etc.  The firmware शेष is क्रम a 4KB Page Size and
	 * 64B Cache Line Size ...
	 */
	t4_fixup_host_params(adapter, PAGE_SIZE, L1_CACHE_BYTES);

	/*
	 * Process module parameters which affect early initialization.
	 */
	अगर (rx_dma_offset != 2 && rx_dma_offset != 0) अणु
		dev_err(&adapter->pdev->dev,
			"Ignoring illegal rx_dma_offset=%d, using 2\n",
			rx_dma_offset);
		rx_dma_offset = 2;
	पूर्ण
	t4_set_reg_field(adapter, SGE_CONTROL_A,
			 PKTSHIFT_V(PKTSHIFT_M),
			 PKTSHIFT_V(rx_dma_offset));

	/*
	 * Don't include the "IP Pseudo Header" in CPL_RX_PKT checksums: Linux
	 * adds the pseuकरो header itself.
	 */
	t4_tp_wr_bits_indirect(adapter, TP_INGRESS_CONFIG_A,
			       CSUM_HAS_PSEUDO_HDR_F, 0);

	वापस 0;
पूर्ण

/* 10Gb/s-BT PHY Support. chip-बाह्यal 10Gb/s-BT PHYs are complex chips
 * unto themselves and they contain their own firmware to perक्रमm their
 * tasks ...
 */
अटल पूर्णांक phy_aq1202_version(स्थिर u8 *phy_fw_data,
			      माप_प्रकार phy_fw_size)
अणु
	पूर्णांक offset;

	/* At offset 0x8 you're looking for the primary image's
	 * starting offset which is 3 Bytes wide
	 *
	 * At offset 0xa of the primary image, you look क्रम the offset
	 * of the DRAM segment which is 3 Bytes wide.
	 *
	 * The FW version is at offset 0x27e of the DRAM and is 2 Bytes
	 * wide
	 */
	#घोषणा be16(__p) (((__p)[0] << 8) | (__p)[1])
	#घोषणा le16(__p) ((__p)[0] | ((__p)[1] << 8))
	#घोषणा le24(__p) (le16(__p) | ((__p)[2] << 16))

	offset = le24(phy_fw_data + 0x8) << 12;
	offset = le24(phy_fw_data + offset + 0xa);
	वापस be16(phy_fw_data + offset + 0x27e);

	#अघोषित be16
	#अघोषित le16
	#अघोषित le24
पूर्ण

अटल काष्ठा info_10gbt_phy_fw अणु
	अचिन्हित पूर्णांक phy_fw_id;		/* PCI Device ID */
	अक्षर *phy_fw_file;		/* /lib/firmware/ PHY Firmware file */
	पूर्णांक (*phy_fw_version)(स्थिर u8 *phy_fw_data, माप_प्रकार phy_fw_size);
	पूर्णांक phy_flash;			/* Has FLASH क्रम PHY Firmware */
पूर्ण phy_info_array[] = अणु
	अणु
		PHY_AQ1202_DEVICEID,
		PHY_AQ1202_FIRMWARE,
		phy_aq1202_version,
		1,
	पूर्ण,
	अणु
		PHY_BCM84834_DEVICEID,
		PHY_BCM84834_FIRMWARE,
		शून्य,
		0,
	पूर्ण,
	अणु 0, शून्य, शून्य पूर्ण,
पूर्ण;

अटल काष्ठा info_10gbt_phy_fw *find_phy_info(पूर्णांक devid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(phy_info_array); i++) अणु
		अगर (phy_info_array[i].phy_fw_id == devid)
			वापस &phy_info_array[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/* Handle updating of chip-बाह्यal 10Gb/s-BT PHY firmware.  This needs to
 * happen after the FW_RESET_CMD but beक्रमe the FW_INITIALIZE_CMD.  On error
 * we वापस a negative error number.  If we transfer new firmware we वापस 1
 * (from t4_load_phy_fw()).  If we करोn't करो anything we वापस 0.
 */
अटल पूर्णांक adap_init0_phy(काष्ठा adapter *adap)
अणु
	स्थिर काष्ठा firmware *phyf;
	पूर्णांक ret;
	काष्ठा info_10gbt_phy_fw *phy_info;

	/* Use the device ID to determine which PHY file to flash.
	 */
	phy_info = find_phy_info(adap->pdev->device);
	अगर (!phy_info) अणु
		dev_warn(adap->pdev_dev,
			 "No PHY Firmware file found for this PHY\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* If we have a T4 PHY firmware file under /lib/firmware/cxgb4/, then
	 * use that. The adapter firmware provides us with a memory buffer
	 * where we can load a PHY firmware file from the host अगर we want to
	 * override the PHY firmware File in flash.
	 */
	ret = request_firmware_direct(&phyf, phy_info->phy_fw_file,
				      adap->pdev_dev);
	अगर (ret < 0) अणु
		/* For adapters without FLASH attached to PHY क्रम their
		 * firmware, it's obviously a fatal error if we can't get the
		 * firmware to the adapter.  For adapters with PHY firmware
		 * FLASH storage, it's worth a warning if we can't find the
		 * PHY Firmware but we'll neuter the error ...
		 */
		dev_err(adap->pdev_dev, "unable to find PHY Firmware image "
			"/lib/firmware/%s, error %d\n",
			phy_info->phy_fw_file, -ret);
		अगर (phy_info->phy_flash) अणु
			पूर्णांक cur_phy_fw_ver = 0;

			t4_phy_fw_ver(adap, &cur_phy_fw_ver);
			dev_warn(adap->pdev_dev, "continuing with, on-adapter "
				 "FLASH copy, version %#x\n", cur_phy_fw_ver);
			ret = 0;
		पूर्ण

		वापस ret;
	पूर्ण

	/* Load PHY Firmware onto adapter.
	 */
	ret = t4_load_phy_fw(adap, MEMWIN_NIC, phy_info->phy_fw_version,
			     (u8 *)phyf->data, phyf->size);
	अगर (ret < 0)
		dev_err(adap->pdev_dev, "PHY Firmware transfer error %d\n",
			-ret);
	अन्यथा अगर (ret > 0) अणु
		पूर्णांक new_phy_fw_ver = 0;

		अगर (phy_info->phy_fw_version)
			new_phy_fw_ver = phy_info->phy_fw_version(phyf->data,
								  phyf->size);
		dev_info(adap->pdev_dev, "Successfully transferred PHY "
			 "Firmware /lib/firmware/%s, version %#x\n",
			 phy_info->phy_fw_file, new_phy_fw_ver);
	पूर्ण

	release_firmware(phyf);

	वापस ret;
पूर्ण

/*
 * Attempt to initialize the adapter via a Firmware Configuration File.
 */
अटल पूर्णांक adap_init0_config(काष्ठा adapter *adapter, पूर्णांक reset)
अणु
	अक्षर *fw_config_file, fw_config_file_path[256];
	u32 finiver, finicsum, cfcsum, param, val;
	काष्ठा fw_caps_config_cmd caps_cmd;
	अचिन्हित दीर्घ mtype = 0, maddr = 0;
	स्थिर काष्ठा firmware *cf;
	अक्षर *config_name = शून्य;
	पूर्णांक config_issued = 0;
	पूर्णांक ret;

	/*
	 * Reset device अगर necessary.
	 */
	अगर (reset) अणु
		ret = t4_fw_reset(adapter, adapter->mbox,
				  PIORSTMODE_F | PIORST_F);
		अगर (ret < 0)
			जाओ bye;
	पूर्ण

	/* If this is a 10Gb/s-BT adapter make sure the chip-बाह्यal
	 * 10Gb/s-BT PHYs have up-to-date firmware.  Note that this step needs
	 * to be perक्रमmed after any global adapter RESET above since some
	 * PHYs only have local RAM copies of the PHY firmware.
	 */
	अगर (is_10gbt_device(adapter->pdev->device)) अणु
		ret = adap_init0_phy(adapter);
		अगर (ret < 0)
			जाओ bye;
	पूर्ण
	/*
	 * If we have a T4 configuration file under /lib/firmware/cxgb4/,
	 * then use that.  Otherwise, use the configuration file stored
	 * in the adapter flash ...
	 */
	चयन (CHELSIO_CHIP_VERSION(adapter->params.chip)) अणु
	हाल CHELSIO_T4:
		fw_config_file = FW4_CFNAME;
		अवरोध;
	हाल CHELSIO_T5:
		fw_config_file = FW5_CFNAME;
		अवरोध;
	हाल CHELSIO_T6:
		fw_config_file = FW6_CFNAME;
		अवरोध;
	शेष:
		dev_err(adapter->pdev_dev, "Device %d is not supported\n",
		       adapter->pdev->device);
		ret = -EINVAL;
		जाओ bye;
	पूर्ण

	ret = request_firmware(&cf, fw_config_file, adapter->pdev_dev);
	अगर (ret < 0) अणु
		config_name = "On FLASH";
		mtype = FW_MEMTYPE_CF_FLASH;
		maddr = t4_flash_cfg_addr(adapter);
	पूर्ण अन्यथा अणु
		u32 params[7], val[7];

		प्र_लिखो(fw_config_file_path,
			"/lib/firmware/%s", fw_config_file);
		config_name = fw_config_file_path;

		अगर (cf->size >= FLASH_CFG_MAX_SIZE)
			ret = -ENOMEM;
		अन्यथा अणु
			params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_CF));
			ret = t4_query_params(adapter, adapter->mbox,
					      adapter->pf, 0, 1, params, val);
			अगर (ret == 0) अणु
				/*
				 * For t4_memory_rw() below addresses and
				 * sizes have to be in terms of multiples of 4
				 * bytes.  So, अगर the Configuration File isn't
				 * a multiple of 4 bytes in length we'll have
				 * to ग_लिखो that out separately since we can't
				 * guarantee that the bytes following the
				 * residual byte in the buffer वापसed by
				 * request_firmware() are zeroed out ...
				 */
				माप_प्रकार resid = cf->size & 0x3;
				माप_प्रकार size = cf->size & ~0x3;
				__be32 *data = (__be32 *)cf->data;

				mtype = FW_PARAMS_PARAM_Y_G(val[0]);
				maddr = FW_PARAMS_PARAM_Z_G(val[0]) << 16;

				spin_lock(&adapter->win0_lock);
				ret = t4_memory_rw(adapter, 0, mtype, maddr,
						   size, data, T4_MEMORY_WRITE);
				अगर (ret == 0 && resid != 0) अणु
					जोड़ अणु
						__be32 word;
						अक्षर buf[4];
					पूर्ण last;
					पूर्णांक i;

					last.word = data[size >> 2];
					क्रम (i = resid; i < 4; i++)
						last.buf[i] = 0;
					ret = t4_memory_rw(adapter, 0, mtype,
							   maddr + size,
							   4, &last.word,
							   T4_MEMORY_WRITE);
				पूर्ण
				spin_unlock(&adapter->win0_lock);
			पूर्ण
		पूर्ण

		release_firmware(cf);
		अगर (ret)
			जाओ bye;
	पूर्ण

	val = 0;

	/* Ofld + Hash filter is supported. Older fw will fail this request and
	 * it is fine.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_HASHFILTER_WITH_OFLD));
	ret = t4_set_params(adapter, adapter->mbox, adapter->pf, 0,
			    1, &param, &val);

	/* FW करोesn't know about Hash filter + ofld support,
	 * it's not a problem, don't वापस an error.
	 */
	अगर (ret < 0) अणु
		dev_warn(adapter->pdev_dev,
			 "Hash filter with ofld is not supported by FW\n");
	पूर्ण

	/*
	 * Issue a Capability Configuration command to the firmware to get it
	 * to parse the Configuration File.  We करोn't use t4_fw_config_file()
	 * because we want the ability to modअगरy various features after we've
	 * processed the configuration file ...
	 */
	स_रखो(&caps_cmd, 0, माप(caps_cmd));
	caps_cmd.op_to_ग_लिखो =
		htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
		      FW_CMD_REQUEST_F |
		      FW_CMD_READ_F);
	caps_cmd.cfvalid_to_len16 =
		htonl(FW_CAPS_CONFIG_CMD_CFVALID_F |
		      FW_CAPS_CONFIG_CMD_MEMTYPE_CF_V(mtype) |
		      FW_CAPS_CONFIG_CMD_MEMADDR64K_CF_V(maddr >> 16) |
		      FW_LEN16(caps_cmd));
	ret = t4_wr_mbox(adapter, adapter->mbox, &caps_cmd, माप(caps_cmd),
			 &caps_cmd);

	/* If the CAPS_CONFIG failed with an ENOENT (क्रम a Firmware
	 * Configuration File in FLASH), our last gasp efक्रमt is to use the
	 * Firmware Configuration File which is embedded in the firmware.  A
	 * very few early versions of the firmware didn't have one embedded
	 * but we can ignore those.
	 */
	अगर (ret == -ENOENT) अणु
		स_रखो(&caps_cmd, 0, माप(caps_cmd));
		caps_cmd.op_to_ग_लिखो =
			htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
					FW_CMD_REQUEST_F |
					FW_CMD_READ_F);
		caps_cmd.cfvalid_to_len16 = htonl(FW_LEN16(caps_cmd));
		ret = t4_wr_mbox(adapter, adapter->mbox, &caps_cmd,
				माप(caps_cmd), &caps_cmd);
		config_name = "Firmware Default";
	पूर्ण

	config_issued = 1;
	अगर (ret < 0)
		जाओ bye;

	finiver = ntohl(caps_cmd.finiver);
	finicsum = ntohl(caps_cmd.finicsum);
	cfcsum = ntohl(caps_cmd.cfcsum);
	अगर (finicsum != cfcsum)
		dev_warn(adapter->pdev_dev, "Configuration File checksum "\
			 "mismatch: [fini] csum=%#x, computed csum=%#x\n",
			 finicsum, cfcsum);

	/*
	 * And now tell the firmware to use the configuration we just loaded.
	 */
	caps_cmd.op_to_ग_लिखो =
		htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
		      FW_CMD_REQUEST_F |
		      FW_CMD_WRITE_F);
	caps_cmd.cfvalid_to_len16 = htonl(FW_LEN16(caps_cmd));
	ret = t4_wr_mbox(adapter, adapter->mbox, &caps_cmd, माप(caps_cmd),
			 शून्य);
	अगर (ret < 0)
		जाओ bye;

	/*
	 * Tweak configuration based on प्रणाली architecture, module
	 * parameters, etc.
	 */
	ret = adap_init0_tweaks(adapter);
	अगर (ret < 0)
		जाओ bye;

	/* We will proceed even अगर HMA init fails. */
	ret = adap_config_hma(adapter);
	अगर (ret)
		dev_err(adapter->pdev_dev,
			"HMA configuration failed with error %d\n", ret);

	अगर (is_t6(adapter->params.chip)) अणु
		adap_config_hpfilter(adapter);
		ret = setup_ppod_edram(adapter);
		अगर (!ret)
			dev_info(adapter->pdev_dev, "Successfully enabled "
				 "ppod edram feature\n");
	पूर्ण

	/*
	 * And finally tell the firmware to initialize itself using the
	 * parameters from the Configuration File.
	 */
	ret = t4_fw_initialize(adapter, adapter->mbox);
	अगर (ret < 0)
		जाओ bye;

	/* Emit Firmware Configuration File inक्रमmation and वापस
	 * successfully.
	 */
	dev_info(adapter->pdev_dev, "Successfully configured using Firmware "\
		 "Configuration File \"%s\", version %#x, computed checksum %#x\n",
		 config_name, finiver, cfcsum);
	वापस 0;

	/*
	 * Something bad happened.  Return the error ...  (If the "error"
	 * is that there's no Configuration File on the adapter we don't
	 * want to issue a warning since this is fairly common.)
	 */
bye:
	अगर (config_issued && ret != -ENOENT)
		dev_warn(adapter->pdev_dev, "\"%s\" configuration file error %d\n",
			 config_name, -ret);
	वापस ret;
पूर्ण

अटल काष्ठा fw_info fw_info_array[] = अणु
	अणु
		.chip = CHELSIO_T4,
		.fs_name = FW4_CFNAME,
		.fw_mod_name = FW4_FNAME,
		.fw_hdr = अणु
			.chip = FW_HDR_CHIP_T4,
			.fw_ver = __cpu_to_be32(FW_VERSION(T4)),
			.पूर्णांकfver_nic = FW_INTFVER(T4, NIC),
			.पूर्णांकfver_vnic = FW_INTFVER(T4, VNIC),
			.पूर्णांकfver_ri = FW_INTFVER(T4, RI),
			.पूर्णांकfver_iscsi = FW_INTFVER(T4, ISCSI),
			.पूर्णांकfver_fcoe = FW_INTFVER(T4, FCOE),
		पूर्ण,
	पूर्ण, अणु
		.chip = CHELSIO_T5,
		.fs_name = FW5_CFNAME,
		.fw_mod_name = FW5_FNAME,
		.fw_hdr = अणु
			.chip = FW_HDR_CHIP_T5,
			.fw_ver = __cpu_to_be32(FW_VERSION(T5)),
			.पूर्णांकfver_nic = FW_INTFVER(T5, NIC),
			.पूर्णांकfver_vnic = FW_INTFVER(T5, VNIC),
			.पूर्णांकfver_ri = FW_INTFVER(T5, RI),
			.पूर्णांकfver_iscsi = FW_INTFVER(T5, ISCSI),
			.पूर्णांकfver_fcoe = FW_INTFVER(T5, FCOE),
		पूर्ण,
	पूर्ण, अणु
		.chip = CHELSIO_T6,
		.fs_name = FW6_CFNAME,
		.fw_mod_name = FW6_FNAME,
		.fw_hdr = अणु
			.chip = FW_HDR_CHIP_T6,
			.fw_ver = __cpu_to_be32(FW_VERSION(T6)),
			.पूर्णांकfver_nic = FW_INTFVER(T6, NIC),
			.पूर्णांकfver_vnic = FW_INTFVER(T6, VNIC),
			.पूर्णांकfver_ofld = FW_INTFVER(T6, OFLD),
			.पूर्णांकfver_ri = FW_INTFVER(T6, RI),
			.पूर्णांकfver_iscsipdu = FW_INTFVER(T6, ISCSIPDU),
			.पूर्णांकfver_iscsi = FW_INTFVER(T6, ISCSI),
			.पूर्णांकfver_fcoepdu = FW_INTFVER(T6, FCOEPDU),
			.पूर्णांकfver_fcoe = FW_INTFVER(T6, FCOE),
		पूर्ण,
	पूर्ण

पूर्ण;

अटल काष्ठा fw_info *find_fw_info(पूर्णांक chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fw_info_array); i++) अणु
		अगर (fw_info_array[i].chip == chip)
			वापस &fw_info_array[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Phase 0 of initialization: contact FW, obtain config, perक्रमm basic init.
 */
अटल पूर्णांक adap_init0(काष्ठा adapter *adap, पूर्णांक vpd_skip)
अणु
	काष्ठा fw_caps_config_cmd caps_cmd;
	u32 params[7], val[7];
	क्रमागत dev_state state;
	u32 v, port_vec;
	पूर्णांक reset = 1;
	पूर्णांक ret;

	/* Grab Firmware Device Log parameters as early as possible so we have
	 * access to it क्रम debugging, etc.
	 */
	ret = t4_init_devlog_params(adap);
	अगर (ret < 0)
		वापस ret;

	/* Contact FW, advertising Master capability */
	ret = t4_fw_hello(adap, adap->mbox, adap->mbox,
			  is_kdump_kernel() ? MASTER_MUST : MASTER_MAY, &state);
	अगर (ret < 0) अणु
		dev_err(adap->pdev_dev, "could not connect to FW, error %d\n",
			ret);
		वापस ret;
	पूर्ण
	अगर (ret == adap->mbox)
		adap->flags |= CXGB4_MASTER_PF;

	/*
	 * If we're the Master PF Driver and the device is uninitialized,
	 * then let's consider upgrading the firmware ...  (We always want
	 * to check the firmware version number in order to A. get it क्रम
	 * later reporting and B. to warn अगर the currently loaded firmware
	 * is excessively mismatched relative to the driver.)
	 */

	t4_get_version_info(adap);
	ret = t4_check_fw_version(adap);
	/* If firmware is too old (not supported by driver) क्रमce an update. */
	अगर (ret)
		state = DEV_STATE_UNINIT;
	अगर ((adap->flags & CXGB4_MASTER_PF) && state != DEV_STATE_INIT) अणु
		काष्ठा fw_info *fw_info;
		काष्ठा fw_hdr *card_fw;
		स्थिर काष्ठा firmware *fw;
		स्थिर u8 *fw_data = शून्य;
		अचिन्हित पूर्णांक fw_size = 0;

		/* This is the firmware whose headers the driver was compiled
		 * against
		 */
		fw_info = find_fw_info(CHELSIO_CHIP_VERSION(adap->params.chip));
		अगर (fw_info == शून्य) अणु
			dev_err(adap->pdev_dev,
				"unable to get firmware info for chip %d.\n",
				CHELSIO_CHIP_VERSION(adap->params.chip));
			वापस -EINVAL;
		पूर्ण

		/* allocate memory to पढ़ो the header of the firmware on the
		 * card
		 */
		card_fw = kvzalloc(माप(*card_fw), GFP_KERNEL);
		अगर (!card_fw) अणु
			ret = -ENOMEM;
			जाओ bye;
		पूर्ण

		/* Get FW from from /lib/firmware/ */
		ret = request_firmware(&fw, fw_info->fw_mod_name,
				       adap->pdev_dev);
		अगर (ret < 0) अणु
			dev_err(adap->pdev_dev,
				"unable to load firmware image %s, error %d\n",
				fw_info->fw_mod_name, ret);
		पूर्ण अन्यथा अणु
			fw_data = fw->data;
			fw_size = fw->size;
		पूर्ण

		/* upgrade FW logic */
		ret = t4_prep_fw(adap, fw_info, fw_data, fw_size, card_fw,
				 state, &reset);

		/* Cleaning up */
		release_firmware(fw);
		kvमुक्त(card_fw);

		अगर (ret < 0)
			जाओ bye;
	पूर्ण

	/* If the firmware is initialized alपढ़ोy, emit a simply note to that
	 * effect. Otherwise, it's समय to try initializing the adapter.
	 */
	अगर (state == DEV_STATE_INIT) अणु
		ret = adap_config_hma(adap);
		अगर (ret)
			dev_err(adap->pdev_dev,
				"HMA configuration failed with error %d\n",
				ret);
		dev_info(adap->pdev_dev, "Coming up as %s: "\
			 "Adapter already initialized\n",
			 adap->flags & CXGB4_MASTER_PF ? "MASTER" : "SLAVE");
	पूर्ण अन्यथा अणु
		dev_info(adap->pdev_dev, "Coming up as MASTER: "\
			 "Initializing adapter\n");

		/* Find out whether we're dealing with a version of the
		 * firmware which has configuration file support.
		 */
		params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_CF));
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1,
				      params, val);

		/* If the firmware करोesn't support Configuration Files,
		 * वापस an error.
		 */
		अगर (ret < 0) अणु
			dev_err(adap->pdev_dev, "firmware doesn't support "
				"Firmware Configuration Files\n");
			जाओ bye;
		पूर्ण

		/* The firmware provides us with a memory buffer where we can
		 * load a Configuration File from the host अगर we want to
		 * override the Configuration File in flash.
		 */
		ret = adap_init0_config(adap, reset);
		अगर (ret == -ENOENT) अणु
			dev_err(adap->pdev_dev, "no Configuration File "
				"present on adapter.\n");
			जाओ bye;
		पूर्ण
		अगर (ret < 0) अणु
			dev_err(adap->pdev_dev, "could not initialize "
				"adapter, error %d\n", -ret);
			जाओ bye;
		पूर्ण
	पूर्ण

	/* Now that we've successfully configured and initialized the adapter
	 * (or found it alपढ़ोy initialized), we can ask the Firmware what
	 * resources it has provisioned क्रम us.
	 */
	ret = t4_get_pfres(adap);
	अगर (ret) अणु
		dev_err(adap->pdev_dev,
			"Unable to retrieve resource provisioning information\n");
		जाओ bye;
	पूर्ण

	/* Grab VPD parameters.  This should be करोne after we establish a
	 * connection to the firmware since some of the VPD parameters
	 * (notably the Core Clock frequency) are retrieved via requests to
	 * the firmware.  On the other hand, we need these fairly early on
	 * so we करो this right after getting ahold of the firmware.
	 *
	 * We need to करो this after initializing the adapter because someone
	 * could have FLASHed a new VPD which won't be पढ़ो by the firmware
	 * until we करो the RESET ...
	 */
	अगर (!vpd_skip) अणु
		ret = t4_get_vpd_params(adap, &adap->params.vpd);
		अगर (ret < 0)
			जाओ bye;
	पूर्ण

	/* Find out what ports are available to us.  Note that we need to करो
	 * this beक्रमe calling adap_init0_no_config() since it needs nports
	 * and portvec ...
	 */
	v =
	    FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
	    FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_PORTVEC);
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1, &v, &port_vec);
	अगर (ret < 0)
		जाओ bye;

	adap->params.nports = hweight32(port_vec);
	adap->params.portvec = port_vec;

	/* Give the SGE code a chance to pull in anything that it needs ...
	 * Note that this must be called after we retrieve our VPD parameters
	 * in order to know how to convert core ticks to seconds, etc.
	 */
	ret = t4_sge_init(adap);
	अगर (ret < 0)
		जाओ bye;

	/* Grab the SGE Doorbell Queue Timer values.  If successful, that
	 * indicates that the Firmware and Hardware support this.
	 */
	params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		    FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DBQ_TIMERTICK));
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0,
			      1, params, val);

	अगर (!ret) अणु
		adap->sge.dbqसमयr_tick = val[0];
		ret = t4_पढ़ो_sge_dbqसमयrs(adap,
					    ARRAY_SIZE(adap->sge.dbqसमयr_val),
					    adap->sge.dbqसमयr_val);
	पूर्ण

	अगर (!ret)
		adap->flags |= CXGB4_SGE_DBQ_TIMER;

	अगर (is_bypass_device(adap->pdev->device))
		adap->params.bypass = 1;

	/*
	 * Grab some of our basic fundamental operating parameters.
	 */
	params[0] = FW_PARAM_PFVF(EQ_START);
	params[1] = FW_PARAM_PFVF(L2T_START);
	params[2] = FW_PARAM_PFVF(L2T_END);
	params[3] = FW_PARAM_PFVF(FILTER_START);
	params[4] = FW_PARAM_PFVF(FILTER_END);
	params[5] = FW_PARAM_PFVF(IQFLINT_START);
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 6, params, val);
	अगर (ret < 0)
		जाओ bye;
	adap->sge.egr_start = val[0];
	adap->l2t_start = val[1];
	adap->l2t_end = val[2];
	adap->tids.ftid_base = val[3];
	adap->tids.nftids = val[4] - val[3] + 1;
	adap->sge.ingr_start = val[5];

	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) > CHELSIO_T5) अणु
		params[0] = FW_PARAM_PFVF(HPFILTER_START);
		params[1] = FW_PARAM_PFVF(HPFILTER_END);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2,
				      params, val);
		अगर (ret < 0)
			जाओ bye;

		adap->tids.hpftid_base = val[0];
		adap->tids.nhpftids = val[1] - val[0] + 1;

		/* Read the raw mps entries. In T6, the last 2 tcam entries
		 * are reserved क्रम raw mac addresses (rawf = 2, one per port).
		 */
		params[0] = FW_PARAM_PFVF(RAWF_START);
		params[1] = FW_PARAM_PFVF(RAWF_END);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2,
				      params, val);
		अगर (ret == 0) अणु
			adap->rawf_start = val[0];
			adap->rawf_cnt = val[1] - val[0] + 1;
		पूर्ण

		adap->tids.tid_base =
			t4_पढ़ो_reg(adap, LE_DB_ACTIVE_TABLE_START_INDEX_A);
	पूर्ण

	/* qids (ingress/egress) वापसed from firmware can be anywhere
	 * in the range from EQ(IQFLINT)_START to EQ(IQFLINT)_END.
	 * Hence driver needs to allocate memory क्रम this range to
	 * store the queue info. Get the highest IQFLINT/EQ index वापसed
	 * in FW_EQ_*_CMD.alloc command.
	 */
	params[0] = FW_PARAM_PFVF(EQ_END);
	params[1] = FW_PARAM_PFVF(IQFLINT_END);
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2, params, val);
	अगर (ret < 0)
		जाओ bye;
	adap->sge.egr_sz = val[0] - adap->sge.egr_start + 1;
	adap->sge.ingr_sz = val[1] - adap->sge.ingr_start + 1;

	adap->sge.egr_map = kसुस्मृति(adap->sge.egr_sz,
				    माप(*adap->sge.egr_map), GFP_KERNEL);
	अगर (!adap->sge.egr_map) अणु
		ret = -ENOMEM;
		जाओ bye;
	पूर्ण

	adap->sge.ingr_map = kसुस्मृति(adap->sge.ingr_sz,
				     माप(*adap->sge.ingr_map), GFP_KERNEL);
	अगर (!adap->sge.ingr_map) अणु
		ret = -ENOMEM;
		जाओ bye;
	पूर्ण

	/* Allocate the memory क्रम the vaious egress queue biपंचांगaps
	 * ie starving_fl, txq_maperr and blocked_fl.
	 */
	adap->sge.starving_fl =	kसुस्मृति(BITS_TO_LONGS(adap->sge.egr_sz),
					माप(दीर्घ), GFP_KERNEL);
	अगर (!adap->sge.starving_fl) अणु
		ret = -ENOMEM;
		जाओ bye;
	पूर्ण

	adap->sge.txq_maperr = kसुस्मृति(BITS_TO_LONGS(adap->sge.egr_sz),
				       माप(दीर्घ), GFP_KERNEL);
	अगर (!adap->sge.txq_maperr) अणु
		ret = -ENOMEM;
		जाओ bye;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	adap->sge.blocked_fl = kसुस्मृति(BITS_TO_LONGS(adap->sge.egr_sz),
				       माप(दीर्घ), GFP_KERNEL);
	अगर (!adap->sge.blocked_fl) अणु
		ret = -ENOMEM;
		जाओ bye;
	पूर्ण
#पूर्ण_अगर

	params[0] = FW_PARAM_PFVF(CLIP_START);
	params[1] = FW_PARAM_PFVF(CLIP_END);
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2, params, val);
	अगर (ret < 0)
		जाओ bye;
	adap->clipt_start = val[0];
	adap->clipt_end = val[1];

	/* Get the supported number of traffic classes */
	params[0] = FW_PARAM_DEV(NUM_TM_CLASS);
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1, params, val);
	अगर (ret < 0) अणु
		/* We couldn't retrieve the number of Traffic Classes
		 * supported by the hardware/firmware. So we hard
		 * code it here.
		 */
		adap->params.nsched_cls = is_t4(adap->params.chip) ? 15 : 16;
	पूर्ण अन्यथा अणु
		adap->params.nsched_cls = val[0];
	पूर्ण

	/* query params related to active filter region */
	params[0] = FW_PARAM_PFVF(ACTIVE_FILTER_START);
	params[1] = FW_PARAM_PFVF(ACTIVE_FILTER_END);
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2, params, val);
	/* If Active filter size is set we enable establishing
	 * offload connection through firmware work request
	 */
	अगर ((val[0] != val[1]) && (ret >= 0)) अणु
		adap->flags |= CXGB4_FW_OFLD_CONN;
		adap->tids.aftid_base = val[0];
		adap->tids.aftid_end = val[1];
	पूर्ण

	/* If we're running on newer firmware, let it know that we're
	 * prepared to deal with encapsulated CPL messages.  Older
	 * firmware won't understand this and we'll just get
	 * unencapsulated messages ...
	 */
	params[0] = FW_PARAM_PFVF(CPLFW4MSG_ENCAP);
	val[0] = 1;
	(व्योम)t4_set_params(adap, adap->mbox, adap->pf, 0, 1, params, val);

	/*
	 * Find out whether we're allowed to use the T5+ ULPTX MEMWRITE DSGL
	 * capability.  Earlier versions of the firmware didn't have the
	 * ULPTX_MEMWRITE_DSGL so we'll पूर्णांकerpret a query failure as no
	 * permission to use ULPTX MEMWRITE DSGL.
	 */
	अगर (is_t4(adap->params.chip)) अणु
		adap->params.ulptx_memग_लिखो_dsgl = false;
	पूर्ण अन्यथा अणु
		params[0] = FW_PARAM_DEV(ULPTX_MEMWRITE_DSGL);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0,
				      1, params, val);
		adap->params.ulptx_memग_लिखो_dsgl = (ret == 0 && val[0] != 0);
	पूर्ण

	/* See अगर FW supports FW_RI_FR_NSMR_TPTE_WR work request */
	params[0] = FW_PARAM_DEV(RI_FR_NSMR_TPTE_WR);
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0,
			      1, params, val);
	adap->params.fr_nsmr_tpte_wr_support = (ret == 0 && val[0] != 0);

	/* See अगर FW supports FW_FILTER2 work request */
	अगर (is_t4(adap->params.chip)) अणु
		adap->params.filter2_wr_support = false;
	पूर्ण अन्यथा अणु
		params[0] = FW_PARAM_DEV(FILTER2_WR);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0,
				      1, params, val);
		adap->params.filter2_wr_support = (ret == 0 && val[0] != 0);
	पूर्ण

	/* Check अगर FW supports वापसing vin and smt index.
	 * If this is not supported, driver will पूर्णांकerpret
	 * these values from viid.
	 */
	params[0] = FW_PARAM_DEV(OPAQUE_VIID_SMT_EXTN);
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0,
			      1, params, val);
	adap->params.viid_smt_extn_support = (ret == 0 && val[0] != 0);

	/*
	 * Get device capabilities so we can determine what resources we need
	 * to manage.
	 */
	स_रखो(&caps_cmd, 0, माप(caps_cmd));
	caps_cmd.op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
				     FW_CMD_REQUEST_F | FW_CMD_READ_F);
	caps_cmd.cfvalid_to_len16 = htonl(FW_LEN16(caps_cmd));
	ret = t4_wr_mbox(adap, adap->mbox, &caps_cmd, माप(caps_cmd),
			 &caps_cmd);
	अगर (ret < 0)
		जाओ bye;

	/* hash filter has some mandatory रेजिस्टर settings to be tested and क्रम
	 * that it needs to test whether offload is enabled or not, hence
	 * checking and setting it here.
	 */
	अगर (caps_cmd.ofldcaps)
		adap->params.offload = 1;

	अगर (caps_cmd.ofldcaps ||
	    (caps_cmd.niccaps & htons(FW_CAPS_CONFIG_NIC_HASHFILTER)) ||
	    (caps_cmd.niccaps & htons(FW_CAPS_CONFIG_NIC_ETHOFLD))) अणु
		/* query offload-related parameters */
		params[0] = FW_PARAM_DEV(NTID);
		params[1] = FW_PARAM_PFVF(SERVER_START);
		params[2] = FW_PARAM_PFVF(SERVER_END);
		params[3] = FW_PARAM_PFVF(TDDP_START);
		params[4] = FW_PARAM_PFVF(TDDP_END);
		params[5] = FW_PARAM_DEV(FLOWC_BUFFIFO_SZ);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 6,
				      params, val);
		अगर (ret < 0)
			जाओ bye;
		adap->tids.ntids = val[0];
		adap->tids.natids = min(adap->tids.ntids / 2, MAX_ATIDS);
		adap->tids.stid_base = val[1];
		adap->tids.nstids = val[2] - val[1] + 1;
		/*
		 * Setup server filter region. Divide the available filter
		 * region पूर्णांकo two parts. Regular filters get 1/3rd and server
		 * filters get 2/3rd part. This is only enabled अगर workarond
		 * path is enabled.
		 * 1. For regular filters.
		 * 2. Server filter: This are special filters which are used
		 * to redirect SYN packets to offload queue.
		 */
		अगर (adap->flags & CXGB4_FW_OFLD_CONN && !is_bypass(adap)) अणु
			adap->tids.sftid_base = adap->tids.ftid_base +
					DIV_ROUND_UP(adap->tids.nftids, 3);
			adap->tids.nsftids = adap->tids.nftids -
					 DIV_ROUND_UP(adap->tids.nftids, 3);
			adap->tids.nftids = adap->tids.sftid_base -
						adap->tids.ftid_base;
		पूर्ण
		adap->vres.ddp.start = val[3];
		adap->vres.ddp.size = val[4] - val[3] + 1;
		adap->params.ofldq_wr_cred = val[5];

		अगर (caps_cmd.niccaps & htons(FW_CAPS_CONFIG_NIC_HASHFILTER)) अणु
			init_hash_filter(adap);
		पूर्ण अन्यथा अणु
			adap->num_ofld_uld += 1;
		पूर्ण

		अगर (caps_cmd.niccaps & htons(FW_CAPS_CONFIG_NIC_ETHOFLD)) अणु
			params[0] = FW_PARAM_PFVF(ETHOFLD_START);
			params[1] = FW_PARAM_PFVF(ETHOFLD_END);
			ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2,
					      params, val);
			अगर (!ret) अणु
				adap->tids.eotid_base = val[0];
				adap->tids.neotids = min_t(u32, MAX_ATIDS,
							   val[1] - val[0] + 1);
				adap->params.ethofld = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (caps_cmd.rdmacaps) अणु
		params[0] = FW_PARAM_PFVF(STAG_START);
		params[1] = FW_PARAM_PFVF(STAG_END);
		params[2] = FW_PARAM_PFVF(RQ_START);
		params[3] = FW_PARAM_PFVF(RQ_END);
		params[4] = FW_PARAM_PFVF(PBL_START);
		params[5] = FW_PARAM_PFVF(PBL_END);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 6,
				      params, val);
		अगर (ret < 0)
			जाओ bye;
		adap->vres.stag.start = val[0];
		adap->vres.stag.size = val[1] - val[0] + 1;
		adap->vres.rq.start = val[2];
		adap->vres.rq.size = val[3] - val[2] + 1;
		adap->vres.pbl.start = val[4];
		adap->vres.pbl.size = val[5] - val[4] + 1;

		params[0] = FW_PARAM_PFVF(SRQ_START);
		params[1] = FW_PARAM_PFVF(SRQ_END);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2,
				      params, val);
		अगर (!ret) अणु
			adap->vres.srq.start = val[0];
			adap->vres.srq.size = val[1] - val[0] + 1;
		पूर्ण
		अगर (adap->vres.srq.size) अणु
			adap->srq = t4_init_srq(adap->vres.srq.size);
			अगर (!adap->srq)
				dev_warn(&adap->pdev->dev, "could not allocate SRQ, continuing\n");
		पूर्ण

		params[0] = FW_PARAM_PFVF(SQRQ_START);
		params[1] = FW_PARAM_PFVF(SQRQ_END);
		params[2] = FW_PARAM_PFVF(CQ_START);
		params[3] = FW_PARAM_PFVF(CQ_END);
		params[4] = FW_PARAM_PFVF(OCQ_START);
		params[5] = FW_PARAM_PFVF(OCQ_END);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 6, params,
				      val);
		अगर (ret < 0)
			जाओ bye;
		adap->vres.qp.start = val[0];
		adap->vres.qp.size = val[1] - val[0] + 1;
		adap->vres.cq.start = val[2];
		adap->vres.cq.size = val[3] - val[2] + 1;
		adap->vres.ocq.start = val[4];
		adap->vres.ocq.size = val[5] - val[4] + 1;

		params[0] = FW_PARAM_DEV(MAXORसूचीD_QP);
		params[1] = FW_PARAM_DEV(MAXIRD_ADAPTER);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2, params,
				      val);
		अगर (ret < 0) अणु
			adap->params.max_ordird_qp = 8;
			adap->params.max_ird_adapter = 32 * adap->tids.ntids;
			ret = 0;
		पूर्ण अन्यथा अणु
			adap->params.max_ordird_qp = val[0];
			adap->params.max_ird_adapter = val[1];
		पूर्ण
		dev_info(adap->pdev_dev,
			 "max_ordird_qp %d max_ird_adapter %d\n",
			 adap->params.max_ordird_qp,
			 adap->params.max_ird_adapter);

		/* Enable ग_लिखो_with_immediate अगर FW supports it */
		params[0] = FW_PARAM_DEV(RDMA_WRITE_WITH_IMM);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1, params,
				      val);
		adap->params.ग_लिखो_w_imm_support = (ret == 0 && val[0] != 0);

		/* Enable ग_लिखो_cmpl अगर FW supports it */
		params[0] = FW_PARAM_DEV(RI_WRITE_CMPL_WR);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1, params,
				      val);
		adap->params.ग_लिखो_cmpl_support = (ret == 0 && val[0] != 0);
		adap->num_ofld_uld += 2;
	पूर्ण
	अगर (caps_cmd.iscsicaps) अणु
		params[0] = FW_PARAM_PFVF(ISCSI_START);
		params[1] = FW_PARAM_PFVF(ISCSI_END);
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2,
				      params, val);
		अगर (ret < 0)
			जाओ bye;
		adap->vres.iscsi.start = val[0];
		adap->vres.iscsi.size = val[1] - val[0] + 1;
		अगर (is_t6(adap->params.chip)) अणु
			params[0] = FW_PARAM_PFVF(PPOD_EDRAM_START);
			params[1] = FW_PARAM_PFVF(PPOD_EDRAM_END);
			ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2,
					      params, val);
			अगर (!ret) अणु
				adap->vres.ppod_edram.start = val[0];
				adap->vres.ppod_edram.size =
					val[1] - val[0] + 1;

				dev_info(adap->pdev_dev,
					 "ppod edram start 0x%x end 0x%x size 0x%x\n",
					 val[0], val[1],
					 adap->vres.ppod_edram.size);
			पूर्ण
		पूर्ण
		/* LIO target and cxgb4i initiaitor */
		adap->num_ofld_uld += 2;
	पूर्ण
	अगर (caps_cmd.cryptocaps) अणु
		अगर (ntohs(caps_cmd.cryptocaps) &
		    FW_CAPS_CONFIG_CRYPTO_LOOKASIDE) अणु
			params[0] = FW_PARAM_PFVF(NCRYPTO_LOOKASIDE);
			ret = t4_query_params(adap, adap->mbox, adap->pf, 0,
					      2, params, val);
			अगर (ret < 0) अणु
				अगर (ret != -EINVAL)
					जाओ bye;
			पूर्ण अन्यथा अणु
				adap->vres.ncrypto_fc = val[0];
			पूर्ण
			adap->num_ofld_uld += 1;
		पूर्ण
		अगर (ntohs(caps_cmd.cryptocaps) &
		    FW_CAPS_CONFIG_TLS_INLINE) अणु
			params[0] = FW_PARAM_PFVF(TLS_START);
			params[1] = FW_PARAM_PFVF(TLS_END);
			ret = t4_query_params(adap, adap->mbox, adap->pf, 0,
					      2, params, val);
			अगर (ret < 0)
				जाओ bye;
			adap->vres.key.start = val[0];
			adap->vres.key.size = val[1] - val[0] + 1;
			adap->num_uld += 1;
		पूर्ण
		adap->params.crypto = ntohs(caps_cmd.cryptocaps);
	पूर्ण

	/* The MTU/MSS Table is initialized by now, so load their values.  If
	 * we're initializing the adapter, then we'll make any modअगरications
	 * we want to the MTU/MSS Table and also initialize the congestion
	 * parameters.
	 */
	t4_पढ़ो_mtu_tbl(adap, adap->params.mtus, शून्य);
	अगर (state != DEV_STATE_INIT) अणु
		पूर्णांक i;

		/* The शेष MTU Table contains values 1492 and 1500.
		 * However, क्रम TCP, it's better to have two values which are
		 * a multiple of 8 +/- 4 bytes apart near this popular MTU.
		 * This allows us to have a TCP Data Payload which is a
		 * multiple of 8 regardless of what combination of TCP Options
		 * are in use (always a multiple of 4 bytes) which is
		 * important क्रम perक्रमmance reasons.  For instance, अगर no
		 * options are in use, then we have a 20-byte IP header and a
		 * 20-byte TCP header.  In this हाल, a 1500-byte MSS would
		 * result in a TCP Data Payload of 1500 - 40 == 1460 bytes
		 * which is not a multiple of 8.  So using an MSS of 1488 in
		 * this हाल results in a TCP Data Payload of 1448 bytes which
		 * is a multiple of 8.  On the other hand, अगर 12-byte TCP Time
		 * Stamps have been negotiated, then an MTU of 1500 bytes
		 * results in a TCP Data Payload of 1448 bytes which, as
		 * above, is a multiple of 8 bytes ...
		 */
		क्रम (i = 0; i < NMTUS; i++)
			अगर (adap->params.mtus[i] == 1492) अणु
				adap->params.mtus[i] = 1488;
				अवरोध;
			पूर्ण

		t4_load_mtus(adap, adap->params.mtus, adap->params.a_wnd,
			     adap->params.b_wnd);
	पूर्ण
	t4_init_sge_params(adap);
	adap->flags |= CXGB4_FW_OK;
	t4_init_tp_params(adap, true);
	वापस 0;

	/*
	 * Something bad happened.  If a command समयd out or failed with EIO
	 * FW करोes not operate within its spec or something catastrophic
	 * happened to HW/FW, stop issuing commands.
	 */
bye:
	adap_मुक्त_hma_mem(adap);
	kमुक्त(adap->sge.egr_map);
	kमुक्त(adap->sge.ingr_map);
	kमुक्त(adap->sge.starving_fl);
	kमुक्त(adap->sge.txq_maperr);
#अगर_घोषित CONFIG_DEBUG_FS
	kमुक्त(adap->sge.blocked_fl);
#पूर्ण_अगर
	अगर (ret != -ETIMEDOUT && ret != -EIO)
		t4_fw_bye(adap, adap->mbox);
	वापस ret;
पूर्ण

/* EEH callbacks */

अटल pci_ers_result_t eeh_err_detected(काष्ठा pci_dev *pdev,
					 pci_channel_state_t state)
अणु
	पूर्णांक i;
	काष्ठा adapter *adap = pci_get_drvdata(pdev);

	अगर (!adap)
		जाओ out;

	rtnl_lock();
	adap->flags &= ~CXGB4_FW_OK;
	notअगरy_ulds(adap, CXGB4_STATE_START_RECOVERY);
	spin_lock(&adap->stats_lock);
	क्रम_each_port(adap, i) अणु
		काष्ठा net_device *dev = adap->port[i];
		अगर (dev) अणु
			netअगर_device_detach(dev);
			netअगर_carrier_off(dev);
		पूर्ण
	पूर्ण
	spin_unlock(&adap->stats_lock);
	disable_पूर्णांकerrupts(adap);
	अगर (adap->flags & CXGB4_FULL_INIT_DONE)
		cxgb_करोwn(adap);
	rtnl_unlock();
	अगर ((adap->flags & CXGB4_DEV_ENABLED)) अणु
		pci_disable_device(pdev);
		adap->flags &= ~CXGB4_DEV_ENABLED;
	पूर्ण
out:	वापस state == pci_channel_io_perm_failure ?
		PCI_ERS_RESULT_DISCONNECT : PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t eeh_slot_reset(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i, ret;
	काष्ठा fw_caps_config_cmd c;
	काष्ठा adapter *adap = pci_get_drvdata(pdev);

	अगर (!adap) अणु
		pci_restore_state(pdev);
		pci_save_state(pdev);
		वापस PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	अगर (!(adap->flags & CXGB4_DEV_ENABLED)) अणु
		अगर (pci_enable_device(pdev)) अणु
			dev_err(&pdev->dev, "Cannot reenable PCI "
					    "device after reset\n");
			वापस PCI_ERS_RESULT_DISCONNECT;
		पूर्ण
		adap->flags |= CXGB4_DEV_ENABLED;
	पूर्ण

	pci_set_master(pdev);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	अगर (t4_रुको_dev_पढ़ोy(adap->regs) < 0)
		वापस PCI_ERS_RESULT_DISCONNECT;
	अगर (t4_fw_hello(adap, adap->mbox, adap->pf, MASTER_MUST, शून्य) < 0)
		वापस PCI_ERS_RESULT_DISCONNECT;
	adap->flags |= CXGB4_FW_OK;
	अगर (adap_init1(adap, &c))
		वापस PCI_ERS_RESULT_DISCONNECT;

	क्रम_each_port(adap, i) अणु
		काष्ठा port_info *pi = adap2pinfo(adap, i);
		u8 vivld = 0, vin = 0;

		ret = t4_alloc_vi(adap, adap->mbox, pi->tx_chan, adap->pf, 0, 1,
				  शून्य, शून्य, &vivld, &vin);
		अगर (ret < 0)
			वापस PCI_ERS_RESULT_DISCONNECT;
		pi->viid = ret;
		pi->xact_addr_filt = -1;
		/* If fw supports वापसing the VIN as part of FW_VI_CMD,
		 * save the वापसed values.
		 */
		अगर (adap->params.viid_smt_extn_support) अणु
			pi->vivld = vivld;
			pi->vin = vin;
		पूर्ण अन्यथा अणु
			/* Retrieve the values from VIID */
			pi->vivld = FW_VIID_VIVLD_G(pi->viid);
			pi->vin = FW_VIID_VIN_G(pi->viid);
		पूर्ण
	पूर्ण

	t4_load_mtus(adap, adap->params.mtus, adap->params.a_wnd,
		     adap->params.b_wnd);
	setup_memwin(adap);
	अगर (cxgb_up(adap))
		वापस PCI_ERS_RESULT_DISCONNECT;
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम eeh_resume(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा adapter *adap = pci_get_drvdata(pdev);

	अगर (!adap)
		वापस;

	rtnl_lock();
	क्रम_each_port(adap, i) अणु
		काष्ठा net_device *dev = adap->port[i];
		अगर (dev) अणु
			अगर (netअगर_running(dev)) अणु
				link_start(dev);
				cxgb_set_rxmode(dev);
			पूर्ण
			netअगर_device_attach(dev);
		पूर्ण
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल व्योम eeh_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adapter *adapter = pci_get_drvdata(pdev);
	पूर्णांक i;

	अगर (adapter->pf != 4)
		वापस;

	adapter->flags &= ~CXGB4_FW_OK;

	notअगरy_ulds(adapter, CXGB4_STATE_DOWN);

	क्रम_each_port(adapter, i)
		अगर (adapter->port[i]->reg_state == NETREG_REGISTERED)
			cxgb_बंद(adapter->port[i]);

	disable_पूर्णांकerrupts(adapter);
	cxgb4_मुक्त_mps_ref_entries(adapter);

	adap_मुक्त_hma_mem(adapter);

	अगर (adapter->flags & CXGB4_FULL_INIT_DONE)
		cxgb_करोwn(adapter);
पूर्ण

अटल व्योम eeh_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adapter *adapter = pci_get_drvdata(pdev);
	पूर्णांक err, i;

	अगर (adapter->pf != 4)
		वापस;

	err = t4_रुको_dev_पढ़ोy(adapter->regs);
	अगर (err < 0) अणु
		dev_err(adapter->pdev_dev,
			"Device not ready, err %d", err);
		वापस;
	पूर्ण

	setup_memwin(adapter);

	err = adap_init0(adapter, 1);
	अगर (err) अणु
		dev_err(adapter->pdev_dev,
			"Adapter init failed, err %d", err);
		वापस;
	पूर्ण

	setup_memwin_rdma(adapter);

	अगर (adapter->flags & CXGB4_FW_OK) अणु
		err = t4_port_init(adapter, adapter->pf, adapter->pf, 0);
		अगर (err) अणु
			dev_err(adapter->pdev_dev,
				"Port init failed, err %d", err);
			वापस;
		पूर्ण
	पूर्ण

	err = cfg_queues(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev,
			"Config queues failed, err %d", err);
		वापस;
	पूर्ण

	cxgb4_init_mps_ref_entries(adapter);

	err = setup_fw_sge_queues(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev,
			"FW sge queue allocation failed, err %d", err);
		वापस;
	पूर्ण

	क्रम_each_port(adapter, i)
		अगर (adapter->port[i]->reg_state == NETREG_REGISTERED)
			cxgb_खोलो(adapter->port[i]);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers cxgb4_eeh = अणु
	.error_detected = eeh_err_detected,
	.slot_reset     = eeh_slot_reset,
	.resume         = eeh_resume,
	.reset_prepare  = eeh_reset_prepare,
	.reset_करोne     = eeh_reset_करोne,
पूर्ण;

/* Return true अगर the Link Configuration supports "High Speeds" (those greater
 * than 1Gb/s).
 */
अटल अंतरभूत bool is_x_10g_port(स्थिर काष्ठा link_config *lc)
अणु
	अचिन्हित पूर्णांक speeds, high_speeds;

	speeds = FW_PORT_CAP32_SPEED_V(FW_PORT_CAP32_SPEED_G(lc->pcaps));
	high_speeds = speeds &
			~(FW_PORT_CAP32_SPEED_100M | FW_PORT_CAP32_SPEED_1G);

	वापस high_speeds != 0;
पूर्ण

/* Perक्रमm शेष configuration of DMA queues depending on the number and type
 * of ports we found and the number of available CPUs.  Most settings can be
 * modअगरied by the admin prior to actual use.
 */
अटल पूर्णांक cfg_queues(काष्ठा adapter *adap)
अणु
	u32 avail_qsets, avail_eth_qsets, avail_uld_qsets;
	u32 ncpus = num_online_cpus();
	u32 niqflपूर्णांक, neq, num_ulds;
	काष्ठा sge *s = &adap->sge;
	u32 i, n10g = 0, qidx = 0;
	u32 q10g = 0, q1g;

	/* Reduce memory usage in kdump environment, disable all offload. */
	अगर (is_kdump_kernel() || (is_uld(adap) && t4_uld_mem_alloc(adap))) अणु
		adap->params.offload = 0;
		adap->params.crypto = 0;
		adap->params.ethofld = 0;
	पूर्ण

	/* Calculate the number of Ethernet Queue Sets available based on
	 * resources provisioned क्रम us.  We always have an Asynchronous
	 * Firmware Event Ingress Queue.  If we're operating in MSI or Legacy
	 * IRQ Pin Interrupt mode, then we'll also have a Forwarded Interrupt
	 * Ingress Queue.  Meanजबतक, we need two Egress Queues क्रम each
	 * Queue Set: one क्रम the Free List and one क्रम the Ethernet TX Queue.
	 *
	 * Note that we should also take पूर्णांकo account all of the various
	 * Offload Queues.  But, in any situation where we're operating in
	 * a Resource Constrained Provisioning environment, करोing any Offload
	 * at all is problematic ...
	 */
	niqflपूर्णांक = adap->params.pfres.niqflपूर्णांक - 1;
	अगर (!(adap->flags & CXGB4_USING_MSIX))
		niqflपूर्णांक--;
	neq = adap->params.pfres.neq / 2;
	avail_qsets = min(niqflपूर्णांक, neq);

	अगर (avail_qsets < adap->params.nports) अणु
		dev_err(adap->pdev_dev, "avail_eth_qsets=%d < nports=%d\n",
			avail_qsets, adap->params.nports);
		वापस -ENOMEM;
	पूर्ण

	/* Count the number of 10Gb/s or better ports */
	क्रम_each_port(adap, i)
		n10g += is_x_10g_port(&adap2pinfo(adap, i)->link_cfg);

	avail_eth_qsets = min_t(u32, avail_qsets, MAX_ETH_QSETS);

	/* We शेष to 1 queue per non-10G port and up to # of cores queues
	 * per 10G port.
	 */
	अगर (n10g)
		q10g = (avail_eth_qsets - (adap->params.nports - n10g)) / n10g;

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	/* For Data Center Bridging support we need to be able to support up
	 * to 8 Traffic Priorities; each of which will be asचिन्हित to its
	 * own TX Queue in order to prevent Head-Of-Line Blocking.
	 */
	q1g = 8;
	अगर (adap->params.nports * 8 > avail_eth_qsets) अणु
		dev_err(adap->pdev_dev, "DCB avail_eth_qsets=%d < %d!\n",
			avail_eth_qsets, adap->params.nports * 8);
		वापस -ENOMEM;
	पूर्ण

	अगर (adap->params.nports * ncpus < avail_eth_qsets)
		q10g = max(8U, ncpus);
	अन्यथा
		q10g = max(8U, q10g);

	जबतक ((q10g * n10g) >
	       (avail_eth_qsets - (adap->params.nports - n10g) * q1g))
		q10g--;

#अन्यथा /* !CONFIG_CHELSIO_T4_DCB */
	q1g = 1;
	q10g = min(q10g, ncpus);
#पूर्ण_अगर /* !CONFIG_CHELSIO_T4_DCB */
	अगर (is_kdump_kernel()) अणु
		q10g = 1;
		q1g = 1;
	पूर्ण

	क्रम_each_port(adap, i) अणु
		काष्ठा port_info *pi = adap2pinfo(adap, i);

		pi->first_qset = qidx;
		pi->nqsets = is_x_10g_port(&pi->link_cfg) ? q10g : q1g;
		qidx += pi->nqsets;
	पूर्ण

	s->ethqsets = qidx;
	s->max_ethqsets = qidx;   /* MSI-X may lower it later */
	avail_qsets -= qidx;

	अगर (is_uld(adap)) अणु
		/* For offload we use 1 queue/channel अगर all ports are up to 1G,
		 * otherwise we भागide all available queues amongst the channels
		 * capped by the number of available cores.
		 */
		num_ulds = adap->num_uld + adap->num_ofld_uld;
		i = min_t(u32, MAX_OFLD_QSETS, ncpus);
		avail_uld_qsets = roundup(i, adap->params.nports);
		अगर (avail_qsets < num_ulds * adap->params.nports) अणु
			adap->params.offload = 0;
			adap->params.crypto = 0;
			s->ofldqsets = 0;
		पूर्ण अन्यथा अगर (avail_qsets < num_ulds * avail_uld_qsets || !n10g) अणु
			s->ofldqsets = adap->params.nports;
		पूर्ण अन्यथा अणु
			s->ofldqsets = avail_uld_qsets;
		पूर्ण

		avail_qsets -= num_ulds * s->ofldqsets;
	पूर्ण

	/* ETHOFLD Queues used क्रम QoS offload should follow same
	 * allocation scheme as normal Ethernet Queues.
	 */
	अगर (is_ethofld(adap)) अणु
		अगर (avail_qsets < s->max_ethqsets) अणु
			adap->params.ethofld = 0;
			s->eoqsets = 0;
		पूर्ण अन्यथा अणु
			s->eoqsets = s->max_ethqsets;
		पूर्ण
		avail_qsets -= s->eoqsets;
	पूर्ण

	/* Mirror queues must follow same scheme as normal Ethernet
	 * Queues, when there are enough queues available. Otherwise,
	 * allocate at least 1 queue per port. If even 1 queue is not
	 * available, then disable mirror queues support.
	 */
	अगर (avail_qsets >= s->max_ethqsets)
		s->mirrorqsets = s->max_ethqsets;
	अन्यथा अगर (avail_qsets >= adap->params.nports)
		s->mirrorqsets = adap->params.nports;
	अन्यथा
		s->mirrorqsets = 0;
	avail_qsets -= s->mirrorqsets;

	क्रम (i = 0; i < ARRAY_SIZE(s->ethrxq); i++) अणु
		काष्ठा sge_eth_rxq *r = &s->ethrxq[i];

		init_rspq(adap, &r->rspq, 5, 10, 1024, 64);
		r->fl.size = 72;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(s->ethtxq); i++)
		s->ethtxq[i].q.size = 1024;

	क्रम (i = 0; i < ARRAY_SIZE(s->ctrlq); i++)
		s->ctrlq[i].q.size = 512;

	अगर (!is_t4(adap->params.chip))
		s->ptptxq.q.size = 8;

	init_rspq(adap, &s->fw_evtq, 0, 1, 1024, 64);
	init_rspq(adap, &s->पूर्णांकrq, 0, 1, 512, 64);

	वापस 0;
पूर्ण

/*
 * Reduce the number of Ethernet queues across all ports to at most n.
 * n provides at least one queue per port.
 */
अटल व्योम reduce_ethqs(काष्ठा adapter *adap, पूर्णांक n)
अणु
	पूर्णांक i;
	काष्ठा port_info *pi;

	जबतक (n < adap->sge.ethqsets)
		क्रम_each_port(adap, i) अणु
			pi = adap2pinfo(adap, i);
			अगर (pi->nqsets > 1) अणु
				pi->nqsets--;
				adap->sge.ethqsets--;
				अगर (adap->sge.ethqsets <= n)
					अवरोध;
			पूर्ण
		पूर्ण

	n = 0;
	क्रम_each_port(adap, i) अणु
		pi = adap2pinfo(adap, i);
		pi->first_qset = n;
		n += pi->nqsets;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_msix_info(काष्ठा adapter *adap, u32 num_vec)
अणु
	काष्ठा msix_info *msix_info;

	msix_info = kसुस्मृति(num_vec, माप(*msix_info), GFP_KERNEL);
	अगर (!msix_info)
		वापस -ENOMEM;

	adap->msix_bmap.msix_bmap = kसुस्मृति(BITS_TO_LONGS(num_vec),
					    माप(दीर्घ), GFP_KERNEL);
	अगर (!adap->msix_bmap.msix_bmap) अणु
		kमुक्त(msix_info);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&adap->msix_bmap.lock);
	adap->msix_bmap.mapsize = num_vec;

	adap->msix_info = msix_info;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_msix_info(काष्ठा adapter *adap)
अणु
	kमुक्त(adap->msix_bmap.msix_bmap);
	kमुक्त(adap->msix_info);
पूर्ण

पूर्णांक cxgb4_get_msix_idx_from_bmap(काष्ठा adapter *adap)
अणु
	काष्ठा msix_bmap *bmap = &adap->msix_bmap;
	अचिन्हित पूर्णांक msix_idx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bmap->lock, flags);
	msix_idx = find_first_zero_bit(bmap->msix_bmap, bmap->mapsize);
	अगर (msix_idx < bmap->mapsize) अणु
		__set_bit(msix_idx, bmap->msix_bmap);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&bmap->lock, flags);
		वापस -ENOSPC;
	पूर्ण

	spin_unlock_irqrestore(&bmap->lock, flags);
	वापस msix_idx;
पूर्ण

व्योम cxgb4_मुक्त_msix_idx_in_bmap(काष्ठा adapter *adap,
				 अचिन्हित पूर्णांक msix_idx)
अणु
	काष्ठा msix_bmap *bmap = &adap->msix_bmap;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bmap->lock, flags);
	__clear_bit(msix_idx, bmap->msix_bmap);
	spin_unlock_irqrestore(&bmap->lock, flags);
पूर्ण

/* 2 MSI-X vectors needed क्रम the FW queue and non-data पूर्णांकerrupts */
#घोषणा EXTRA_VECS 2

अटल पूर्णांक enable_msix(काष्ठा adapter *adap)
अणु
	u32 eth_need, uld_need = 0, ethofld_need = 0, mirror_need = 0;
	u32 ethqsets = 0, ofldqsets = 0, eoqsets = 0, mirrorqsets = 0;
	u8 num_uld = 0, nchan = adap->params.nports;
	u32 i, want, need, num_vec;
	काष्ठा sge *s = &adap->sge;
	काष्ठा msix_entry *entries;
	काष्ठा port_info *pi;
	पूर्णांक allocated, ret;

	want = s->max_ethqsets;
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	/* For Data Center Bridging we need 8 Ethernet TX Priority Queues क्रम
	 * each port.
	 */
	need = 8 * nchan;
#अन्यथा
	need = nchan;
#पूर्ण_अगर
	eth_need = need;
	अगर (is_uld(adap)) अणु
		num_uld = adap->num_ofld_uld + adap->num_uld;
		want += num_uld * s->ofldqsets;
		uld_need = num_uld * nchan;
		need += uld_need;
	पूर्ण

	अगर (is_ethofld(adap)) अणु
		want += s->eoqsets;
		ethofld_need = eth_need;
		need += ethofld_need;
	पूर्ण

	अगर (s->mirrorqsets) अणु
		want += s->mirrorqsets;
		mirror_need = nchan;
		need += mirror_need;
	पूर्ण

	want += EXTRA_VECS;
	need += EXTRA_VECS;

	entries = kदो_स्मृति_array(want, माप(*entries), GFP_KERNEL);
	अगर (!entries)
		वापस -ENOMEM;

	क्रम (i = 0; i < want; i++)
		entries[i].entry = i;

	allocated = pci_enable_msix_range(adap->pdev, entries, need, want);
	अगर (allocated < 0) अणु
		/* Disable offload and attempt to get vectors क्रम NIC
		 * only mode.
		 */
		want = s->max_ethqsets + EXTRA_VECS;
		need = eth_need + EXTRA_VECS;
		allocated = pci_enable_msix_range(adap->pdev, entries,
						  need, want);
		अगर (allocated < 0) अणु
			dev_info(adap->pdev_dev,
				 "Disabling MSI-X due to insufficient MSI-X vectors\n");
			ret = allocated;
			जाओ out_मुक्त;
		पूर्ण

		dev_info(adap->pdev_dev,
			 "Disabling offload due to insufficient MSI-X vectors\n");
		adap->params.offload = 0;
		adap->params.crypto = 0;
		adap->params.ethofld = 0;
		s->ofldqsets = 0;
		s->eoqsets = 0;
		s->mirrorqsets = 0;
		uld_need = 0;
		ethofld_need = 0;
		mirror_need = 0;
	पूर्ण

	num_vec = allocated;
	अगर (num_vec < want) अणु
		/* Distribute available vectors to the various queue groups.
		 * Every group माला_लो its minimum requirement and NIC माला_लो top
		 * priority क्रम leftovers.
		 */
		ethqsets = eth_need;
		अगर (is_uld(adap))
			ofldqsets = nchan;
		अगर (is_ethofld(adap))
			eoqsets = ethofld_need;
		अगर (s->mirrorqsets)
			mirrorqsets = mirror_need;

		num_vec -= need;
		जबतक (num_vec) अणु
			अगर (num_vec < eth_need + ethofld_need ||
			    ethqsets > s->max_ethqsets)
				अवरोध;

			क्रम_each_port(adap, i) अणु
				pi = adap2pinfo(adap, i);
				अगर (pi->nqsets < 2)
					जारी;

				ethqsets++;
				num_vec--;
				अगर (ethofld_need) अणु
					eoqsets++;
					num_vec--;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (is_uld(adap)) अणु
			जबतक (num_vec) अणु
				अगर (num_vec < uld_need ||
				    ofldqsets > s->ofldqsets)
					अवरोध;

				ofldqsets++;
				num_vec -= uld_need;
			पूर्ण
		पूर्ण

		अगर (s->mirrorqsets) अणु
			जबतक (num_vec) अणु
				अगर (num_vec < mirror_need ||
				    mirrorqsets > s->mirrorqsets)
					अवरोध;

				mirrorqsets++;
				num_vec -= mirror_need;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ethqsets = s->max_ethqsets;
		अगर (is_uld(adap))
			ofldqsets = s->ofldqsets;
		अगर (is_ethofld(adap))
			eoqsets = s->eoqsets;
		अगर (s->mirrorqsets)
			mirrorqsets = s->mirrorqsets;
	पूर्ण

	अगर (ethqsets < s->max_ethqsets) अणु
		s->max_ethqsets = ethqsets;
		reduce_ethqs(adap, ethqsets);
	पूर्ण

	अगर (is_uld(adap)) अणु
		s->ofldqsets = ofldqsets;
		s->nqs_per_uld = s->ofldqsets;
	पूर्ण

	अगर (is_ethofld(adap))
		s->eoqsets = eoqsets;

	अगर (s->mirrorqsets) अणु
		s->mirrorqsets = mirrorqsets;
		क्रम_each_port(adap, i) अणु
			pi = adap2pinfo(adap, i);
			pi->nmirrorqsets = s->mirrorqsets / nchan;
			mutex_init(&pi->vi_mirror_mutex);
		पूर्ण
	पूर्ण

	/* map क्रम msix */
	ret = alloc_msix_info(adap, allocated);
	अगर (ret)
		जाओ out_disable_msix;

	क्रम (i = 0; i < allocated; i++) अणु
		adap->msix_info[i].vec = entries[i].vector;
		adap->msix_info[i].idx = i;
	पूर्ण

	dev_info(adap->pdev_dev,
		 "%d MSI-X vectors allocated, nic %d eoqsets %d per uld %d mirrorqsets %d\n",
		 allocated, s->max_ethqsets, s->eoqsets, s->nqs_per_uld,
		 s->mirrorqsets);

	kमुक्त(entries);
	वापस 0;

out_disable_msix:
	pci_disable_msix(adap->pdev);

out_मुक्त:
	kमुक्त(entries);
	वापस ret;
पूर्ण

#अघोषित EXTRA_VECS

अटल पूर्णांक init_rss(काष्ठा adapter *adap)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = t4_init_rss_mode(adap, adap->mbox);
	अगर (err)
		वापस err;

	क्रम_each_port(adap, i) अणु
		काष्ठा port_info *pi = adap2pinfo(adap, i);

		pi->rss = kसुस्मृति(pi->rss_size, माप(u16), GFP_KERNEL);
		अगर (!pi->rss)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/* Dump basic inक्रमmation about the adapter */
अटल व्योम prपूर्णांक_adapter_info(काष्ठा adapter *adapter)
अणु
	/* Hardware/Firmware/etc. Version/Revision IDs */
	t4_dump_version_info(adapter);

	/* Software/Hardware configuration */
	dev_info(adapter->pdev_dev, "Configuration: %sNIC %s, %s capable\n",
		 is_offload(adapter) ? "R" : "",
		 ((adapter->flags & CXGB4_USING_MSIX) ? "MSI-X" :
		  (adapter->flags & CXGB4_USING_MSI) ? "MSI" : ""),
		 is_offload(adapter) ? "Offload" : "non-Offload");
पूर्ण

अटल व्योम prपूर्णांक_port_info(स्थिर काष्ठा net_device *dev)
अणु
	अक्षर buf[80];
	अक्षर *bufp = buf;
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	स्थिर काष्ठा adapter *adap = pi->adapter;

	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_100M)
		bufp += प्र_लिखो(bufp, "100M/");
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_1G)
		bufp += प्र_लिखो(bufp, "1G/");
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_10G)
		bufp += प्र_लिखो(bufp, "10G/");
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_25G)
		bufp += प्र_लिखो(bufp, "25G/");
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_40G)
		bufp += प्र_लिखो(bufp, "40G/");
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_50G)
		bufp += प्र_लिखो(bufp, "50G/");
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_100G)
		bufp += प्र_लिखो(bufp, "100G/");
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_200G)
		bufp += प्र_लिखो(bufp, "200G/");
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_SPEED_400G)
		bufp += प्र_लिखो(bufp, "400G/");
	अगर (bufp != buf)
		--bufp;
	प्र_लिखो(bufp, "BASE-%s", t4_get_port_type_description(pi->port_type));

	netdev_info(dev, "%s: Chelsio %s (%s) %s\n",
		    dev->name, adap->params.vpd.id, adap->name, buf);
पूर्ण

/*
 * Free the following resources:
 * - memory used क्रम tables
 * - MSI/MSI-X
 * - net devices
 * - resources FW is holding क्रम us
 */
अटल व्योम मुक्त_some_resources(काष्ठा adapter *adapter)
अणु
	अचिन्हित पूर्णांक i;

	kvमुक्त(adapter->smt);
	kvमुक्त(adapter->l2t);
	kvमुक्त(adapter->srq);
	t4_cleanup_sched(adapter);
	kvमुक्त(adapter->tids.tid_tab);
	cxgb4_cleanup_tc_matchall(adapter);
	cxgb4_cleanup_tc_mqprio(adapter);
	cxgb4_cleanup_tc_flower(adapter);
	cxgb4_cleanup_tc_u32(adapter);
	cxgb4_cleanup_ethtool_filters(adapter);
	kमुक्त(adapter->sge.egr_map);
	kमुक्त(adapter->sge.ingr_map);
	kमुक्त(adapter->sge.starving_fl);
	kमुक्त(adapter->sge.txq_maperr);
#अगर_घोषित CONFIG_DEBUG_FS
	kमुक्त(adapter->sge.blocked_fl);
#पूर्ण_अगर
	disable_msi(adapter);

	क्रम_each_port(adapter, i)
		अगर (adapter->port[i]) अणु
			काष्ठा port_info *pi = adap2pinfo(adapter, i);

			अगर (pi->viid != 0)
				t4_मुक्त_vi(adapter, adapter->mbox, adapter->pf,
					   0, pi->viid);
			kमुक्त(adap2pinfo(adapter, i)->rss);
			मुक्त_netdev(adapter->port[i]);
		पूर्ण
	अगर (adapter->flags & CXGB4_FW_OK)
		t4_fw_bye(adapter, adapter->pf);
पूर्ण

#घोषणा TSO_FLAGS (NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_TSO_ECN | \
		   NETIF_F_GSO_UDP_L4)
#घोषणा VLAN_FEAT (NETIF_F_SG | NETIF_F_IP_CSUM | TSO_FLAGS | \
		   NETIF_F_GRO | NETIF_F_IPV6_CSUM | NETIF_F_HIGHDMA)
#घोषणा SEGMENT_SIZE 128

अटल पूर्णांक t4_get_chip_type(काष्ठा adapter *adap, पूर्णांक ver)
अणु
	u32 pl_rev = REV_G(t4_पढ़ो_reg(adap, PL_REV_A));

	चयन (ver) अणु
	हाल CHELSIO_T4:
		वापस CHELSIO_CHIP_CODE(CHELSIO_T4, pl_rev);
	हाल CHELSIO_T5:
		वापस CHELSIO_CHIP_CODE(CHELSIO_T5, pl_rev);
	हाल CHELSIO_T6:
		वापस CHELSIO_CHIP_CODE(CHELSIO_T6, pl_rev);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
अटल व्योम cxgb4_mgmt_setup(काष्ठा net_device *dev)
अणु
	dev->type = ARPHRD_NONE;
	dev->mtu = 0;
	dev->hard_header_len = 0;
	dev->addr_len = 0;
	dev->tx_queue_len = 0;
	dev->flags |= IFF_NOARP;
	dev->priv_flags |= IFF_NO_QUEUE;

	/* Initialize the device काष्ठाure. */
	dev->netdev_ops = &cxgb4_mgmt_netdev_ops;
	dev->ethtool_ops = &cxgb4_mgmt_ethtool_ops;
पूर्ण

अटल पूर्णांक cxgb4_iov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा adapter *adap = pci_get_drvdata(pdev);
	पूर्णांक err = 0;
	पूर्णांक current_vfs = pci_num_vf(pdev);
	u32 pcie_fw;

	pcie_fw = पढ़ोl(adap->regs + PCIE_FW_A);
	/* Check अगर fw is initialized */
	अगर (!(pcie_fw & PCIE_FW_INIT_F)) अणु
		dev_warn(&pdev->dev, "Device not initialized\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* If any of the VF's is alपढ़ोy asचिन्हित to Guest OS, then
	 * SRIOV क्रम the same cannot be modअगरied
	 */
	अगर (current_vfs && pci_vfs_asचिन्हित(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot modify SR-IOV while VFs are assigned\n");
		वापस current_vfs;
	पूर्ण
	/* Note that the upper-level code ensures that we're never called with
	 * a non-zero "num_vfs" when we alपढ़ोy have VFs instantiated.  But
	 * it never hurts to code defensively.
	 */
	अगर (num_vfs != 0 && current_vfs != 0)
		वापस -EBUSY;

	/* Nothing to करो क्रम no change. */
	अगर (num_vfs == current_vfs)
		वापस num_vfs;

	/* Disable SRIOV when zero is passed. */
	अगर (!num_vfs) अणु
		pci_disable_sriov(pdev);
		/* मुक्त VF Management Interface */
		unरेजिस्टर_netdev(adap->port[0]);
		मुक्त_netdev(adap->port[0]);
		adap->port[0] = शून्य;

		/* मुक्त VF resources */
		adap->num_vfs = 0;
		kमुक्त(adap->vfinfo);
		adap->vfinfo = शून्य;
		वापस 0;
	पूर्ण

	अगर (!current_vfs) अणु
		काष्ठा fw_pfvf_cmd port_cmd, port_rpl;
		काष्ठा net_device *netdev;
		अचिन्हित पूर्णांक pmask, port;
		काष्ठा pci_dev *pbridge;
		काष्ठा port_info *pi;
		अक्षर name[IFNAMSIZ];
		u32 devcap2;
		u16 flags;

		/* If we want to instantiate Virtual Functions, then our
		 * parent bridge's PCI-E needs to support Alternative Routing
		 * ID (ARI) because our VFs will show up at function offset 8
		 * and above.
		 */
		pbridge = pdev->bus->self;
		pcie_capability_पढ़ो_word(pbridge, PCI_EXP_FLAGS, &flags);
		pcie_capability_पढ़ो_dword(pbridge, PCI_EXP_DEVCAP2, &devcap2);

		अगर ((flags & PCI_EXP_FLAGS_VERS) < 2 ||
		    !(devcap2 & PCI_EXP_DEVCAP2_ARI)) अणु
			/* Our parent bridge करोes not support ARI so issue a
			 * warning and skip instantiating the VFs.  They
			 * won't be reachable.
			 */
			dev_warn(&pdev->dev, "Parent bridge %02x:%02x.%x doesn't support ARI; can't instantiate Virtual Functions\n",
				 pbridge->bus->number, PCI_SLOT(pbridge->devfn),
				 PCI_FUNC(pbridge->devfn));
			वापस -ENOTSUPP;
		पूर्ण
		स_रखो(&port_cmd, 0, माप(port_cmd));
		port_cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PFVF_CMD) |
						 FW_CMD_REQUEST_F |
						 FW_CMD_READ_F |
						 FW_PFVF_CMD_PFN_V(adap->pf) |
						 FW_PFVF_CMD_VFN_V(0));
		port_cmd.retval_len16 = cpu_to_be32(FW_LEN16(port_cmd));
		err = t4_wr_mbox(adap, adap->mbox, &port_cmd, माप(port_cmd),
				 &port_rpl);
		अगर (err)
			वापस err;
		pmask = FW_PFVF_CMD_PMASK_G(be32_to_cpu(port_rpl.type_to_neq));
		port = ffs(pmask) - 1;
		/* Allocate VF Management Interface. */
		snम_लिखो(name, IFNAMSIZ, "mgmtpf%d,%d", adap->adap_idx,
			 adap->pf);
		netdev = alloc_netdev(माप(काष्ठा port_info),
				      name, NET_NAME_UNKNOWN, cxgb4_mgmt_setup);
		अगर (!netdev)
			वापस -ENOMEM;

		pi = netdev_priv(netdev);
		pi->adapter = adap;
		pi->lport = port;
		pi->tx_chan = port;
		SET_NETDEV_DEV(netdev, &pdev->dev);

		adap->port[0] = netdev;
		pi->port_id = 0;

		err = रेजिस्टर_netdev(adap->port[0]);
		अगर (err) अणु
			pr_info("Unable to register VF mgmt netdev %s\n", name);
			मुक्त_netdev(adap->port[0]);
			adap->port[0] = शून्य;
			वापस err;
		पूर्ण
		/* Allocate and set up VF Inक्रमmation. */
		adap->vfinfo = kसुस्मृति(pci_sriov_get_totalvfs(pdev),
				       माप(काष्ठा vf_info), GFP_KERNEL);
		अगर (!adap->vfinfo) अणु
			unरेजिस्टर_netdev(adap->port[0]);
			मुक्त_netdev(adap->port[0]);
			adap->port[0] = शून्य;
			वापस -ENOMEM;
		पूर्ण
		cxgb4_mgmt_fill_vf_station_mac_addr(adap);
	पूर्ण
	/* Instantiate the requested number of VFs. */
	err = pci_enable_sriov(pdev, num_vfs);
	अगर (err) अणु
		pr_info("Unable to instantiate %d VFs\n", num_vfs);
		अगर (!current_vfs) अणु
			unरेजिस्टर_netdev(adap->port[0]);
			मुक्त_netdev(adap->port[0]);
			adap->port[0] = शून्य;
			kमुक्त(adap->vfinfo);
			adap->vfinfo = शून्य;
		पूर्ण
		वापस err;
	पूर्ण

	adap->num_vfs = num_vfs;
	वापस num_vfs;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE) || IS_ENABLED(CONFIG_CHELSIO_IPSEC_INLINE)

अटल पूर्णांक chcr_offload_state(काष्ठा adapter *adap,
			      क्रमागत cxgb4_netdev_tls_ops op_val)
अणु
	चयन (op_val) अणु
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	हाल CXGB4_TLSDEV_OPS:
		अगर (!adap->uld[CXGB4_ULD_KTLS].handle) अणु
			dev_dbg(adap->pdev_dev, "ch_ktls driver is not loaded\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (!adap->uld[CXGB4_ULD_KTLS].tlsdev_ops) अणु
			dev_dbg(adap->pdev_dev,
				"ch_ktls driver has no registered tlsdev_ops\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* CONFIG_CHELSIO_TLS_DEVICE */
#अगर IS_ENABLED(CONFIG_CHELSIO_IPSEC_INLINE)
	हाल CXGB4_XFRMDEV_OPS:
		अगर (!adap->uld[CXGB4_ULD_IPSEC].handle) अणु
			dev_dbg(adap->pdev_dev, "chipsec driver is not loaded\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (!adap->uld[CXGB4_ULD_IPSEC].xfrmdev_ops) अणु
			dev_dbg(adap->pdev_dev,
				"chipsec driver has no registered xfrmdev_ops\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* CONFIG_CHELSIO_IPSEC_INLINE */
	शेष:
		dev_dbg(adap->pdev_dev,
			"driver has no support for offload %d\n", op_val);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_CHELSIO_TLS_DEVICE || CONFIG_CHELSIO_IPSEC_INLINE */

#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)

अटल पूर्णांक cxgb4_ktls_dev_add(काष्ठा net_device *netdev, काष्ठा sock *sk,
			      क्रमागत tls_offload_ctx_dir direction,
			      काष्ठा tls_crypto_info *crypto_info,
			      u32 tcp_sn)
अणु
	काष्ठा adapter *adap = netdev2adap(netdev);
	पूर्णांक ret;

	mutex_lock(&uld_mutex);
	ret = chcr_offload_state(adap, CXGB4_TLSDEV_OPS);
	अगर (ret)
		जाओ out_unlock;

	ret = cxgb4_set_ktls_feature(adap, FW_PARAMS_PARAM_DEV_KTLS_HW_ENABLE);
	अगर (ret)
		जाओ out_unlock;

	ret = adap->uld[CXGB4_ULD_KTLS].tlsdev_ops->tls_dev_add(netdev, sk,
								direction,
								crypto_info,
								tcp_sn);
	/* अगर there is a failure, clear the refcount */
	अगर (ret)
		cxgb4_set_ktls_feature(adap,
				       FW_PARAMS_PARAM_DEV_KTLS_HW_DISABLE);
out_unlock:
	mutex_unlock(&uld_mutex);
	वापस ret;
पूर्ण

अटल व्योम cxgb4_ktls_dev_del(काष्ठा net_device *netdev,
			       काष्ठा tls_context *tls_ctx,
			       क्रमागत tls_offload_ctx_dir direction)
अणु
	काष्ठा adapter *adap = netdev2adap(netdev);

	mutex_lock(&uld_mutex);
	अगर (chcr_offload_state(adap, CXGB4_TLSDEV_OPS))
		जाओ out_unlock;

	adap->uld[CXGB4_ULD_KTLS].tlsdev_ops->tls_dev_del(netdev, tls_ctx,
							  direction);

out_unlock:
	cxgb4_set_ktls_feature(adap, FW_PARAMS_PARAM_DEV_KTLS_HW_DISABLE);
	mutex_unlock(&uld_mutex);
पूर्ण

अटल स्थिर काष्ठा tlsdev_ops cxgb4_ktls_ops = अणु
	.tls_dev_add = cxgb4_ktls_dev_add,
	.tls_dev_del = cxgb4_ktls_dev_del,
पूर्ण;
#पूर्ण_अगर /* CONFIG_CHELSIO_TLS_DEVICE */

#अगर IS_ENABLED(CONFIG_CHELSIO_IPSEC_INLINE)

अटल पूर्णांक cxgb4_xfrm_add_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा adapter *adap = netdev2adap(x->xso.dev);
	पूर्णांक ret;

	अगर (!mutex_trylock(&uld_mutex)) अणु
		dev_dbg(adap->pdev_dev,
			"crypto uld critical resource is under use\n");
		वापस -EBUSY;
	पूर्ण
	ret = chcr_offload_state(adap, CXGB4_XFRMDEV_OPS);
	अगर (ret)
		जाओ out_unlock;

	ret = adap->uld[CXGB4_ULD_IPSEC].xfrmdev_ops->xकरो_dev_state_add(x);

out_unlock:
	mutex_unlock(&uld_mutex);

	वापस ret;
पूर्ण

अटल व्योम cxgb4_xfrm_del_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा adapter *adap = netdev2adap(x->xso.dev);

	अगर (!mutex_trylock(&uld_mutex)) अणु
		dev_dbg(adap->pdev_dev,
			"crypto uld critical resource is under use\n");
		वापस;
	पूर्ण
	अगर (chcr_offload_state(adap, CXGB4_XFRMDEV_OPS))
		जाओ out_unlock;

	adap->uld[CXGB4_ULD_IPSEC].xfrmdev_ops->xकरो_dev_state_delete(x);

out_unlock:
	mutex_unlock(&uld_mutex);
पूर्ण

अटल व्योम cxgb4_xfrm_मुक्त_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा adapter *adap = netdev2adap(x->xso.dev);

	अगर (!mutex_trylock(&uld_mutex)) अणु
		dev_dbg(adap->pdev_dev,
			"crypto uld critical resource is under use\n");
		वापस;
	पूर्ण
	अगर (chcr_offload_state(adap, CXGB4_XFRMDEV_OPS))
		जाओ out_unlock;

	adap->uld[CXGB4_ULD_IPSEC].xfrmdev_ops->xकरो_dev_state_मुक्त(x);

out_unlock:
	mutex_unlock(&uld_mutex);
पूर्ण

अटल bool cxgb4_ipsec_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x)
अणु
	काष्ठा adapter *adap = netdev2adap(x->xso.dev);
	bool ret = false;

	अगर (!mutex_trylock(&uld_mutex)) अणु
		dev_dbg(adap->pdev_dev,
			"crypto uld critical resource is under use\n");
		वापस ret;
	पूर्ण
	अगर (chcr_offload_state(adap, CXGB4_XFRMDEV_OPS))
		जाओ out_unlock;

	ret = adap->uld[CXGB4_ULD_IPSEC].xfrmdev_ops->xकरो_dev_offload_ok(skb, x);

out_unlock:
	mutex_unlock(&uld_mutex);
	वापस ret;
पूर्ण

अटल व्योम cxgb4_advance_esn_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा adapter *adap = netdev2adap(x->xso.dev);

	अगर (!mutex_trylock(&uld_mutex)) अणु
		dev_dbg(adap->pdev_dev,
			"crypto uld critical resource is under use\n");
		वापस;
	पूर्ण
	अगर (chcr_offload_state(adap, CXGB4_XFRMDEV_OPS))
		जाओ out_unlock;

	adap->uld[CXGB4_ULD_IPSEC].xfrmdev_ops->xकरो_dev_state_advance_esn(x);

out_unlock:
	mutex_unlock(&uld_mutex);
पूर्ण

अटल स्थिर काष्ठा xfrmdev_ops cxgb4_xfrmdev_ops = अणु
	.xकरो_dev_state_add      = cxgb4_xfrm_add_state,
	.xकरो_dev_state_delete   = cxgb4_xfrm_del_state,
	.xकरो_dev_state_मुक्त     = cxgb4_xfrm_मुक्त_state,
	.xकरो_dev_offload_ok     = cxgb4_ipsec_offload_ok,
	.xकरो_dev_state_advance_esn = cxgb4_advance_esn_state,
पूर्ण;

#पूर्ण_अगर /* CONFIG_CHELSIO_IPSEC_INLINE */

अटल पूर्णांक init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा adapter *adapter;
	अटल पूर्णांक adap_idx = 1;
	पूर्णांक s_qpp, qpp, num_seg;
	काष्ठा port_info *pi;
	bool highdma = false;
	क्रमागत chip_type chip;
	व्योम __iomem *regs;
	पूर्णांक func, chip_ver;
	u16 device_id;
	पूर्णांक i, err;
	u32 whoami;

	err = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (err) अणु
		/* Just info, some other driver may have claimed the device. */
		dev_info(&pdev->dev, "cannot obtain PCI resources\n");
		वापस err;
	पूर्ण

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		जाओ out_release_regions;
	पूर्ण

	regs = pci_ioremap_bar(pdev, 0);
	अगर (!regs) अणु
		dev_err(&pdev->dev, "cannot map device registers\n");
		err = -ENOMEM;
		जाओ out_disable_device;
	पूर्ण

	adapter = kzalloc(माप(*adapter), GFP_KERNEL);
	अगर (!adapter) अणु
		err = -ENOMEM;
		जाओ out_unmap_bar0;
	पूर्ण

	adapter->regs = regs;
	err = t4_रुको_dev_पढ़ोy(regs);
	अगर (err < 0)
		जाओ out_मुक्त_adapter;

	/* We control everything through one PF */
	whoami = t4_पढ़ो_reg(adapter, PL_WHOAMI_A);
	pci_पढ़ो_config_word(pdev, PCI_DEVICE_ID, &device_id);
	chip = t4_get_chip_type(adapter, CHELSIO_PCI_ID_VER(device_id));
	अगर ((पूर्णांक)chip < 0) अणु
		dev_err(&pdev->dev, "Device %d is not supported\n", device_id);
		err = chip;
		जाओ out_मुक्त_adapter;
	पूर्ण
	chip_ver = CHELSIO_CHIP_VERSION(chip);
	func = chip_ver <= CHELSIO_T5 ?
	       SOURCEPF_G(whoami) : T6_SOURCEPF_G(whoami);

	adapter->pdev = pdev;
	adapter->pdev_dev = &pdev->dev;
	adapter->name = pci_name(pdev);
	adapter->mbox = func;
	adapter->pf = func;
	adapter->params.chip = chip;
	adapter->adap_idx = adap_idx;
	adapter->msg_enable = DFLT_MSG_ENABLE;
	adapter->mbox_log = kzalloc(माप(*adapter->mbox_log) +
				    (माप(काष्ठा mbox_cmd) *
				     T4_OS_LOG_MBOX_CMDS),
				    GFP_KERNEL);
	अगर (!adapter->mbox_log) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_adapter;
	पूर्ण
	spin_lock_init(&adapter->mbox_lock);
	INIT_LIST_HEAD(&adapter->mlist.list);
	adapter->mbox_log->size = T4_OS_LOG_MBOX_CMDS;
	pci_set_drvdata(pdev, adapter);

	अगर (func != ent->driver_data) अणु
		pci_disable_device(pdev);
		pci_save_state(pdev);        /* to restore SR-IOV later */
		वापस 0;
	पूर्ण

	अगर (!pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) अणु
		highdma = true;
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
		अगर (err) अणु
			dev_err(&pdev->dev, "unable to obtain 64-bit DMA for "
				"coherent allocations\n");
			जाओ out_मुक्त_adapter;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "no usable DMA configuration\n");
			जाओ out_मुक्त_adapter;
		पूर्ण
	पूर्ण

	pci_enable_pcie_error_reporting(pdev);
	pci_set_master(pdev);
	pci_save_state(pdev);
	adap_idx++;
	adapter->workq = create_singlethपढ़ो_workqueue("cxgb4");
	अगर (!adapter->workq) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_adapter;
	पूर्ण

	/* PCI device has been enabled */
	adapter->flags |= CXGB4_DEV_ENABLED;
	स_रखो(adapter->chan_map, 0xff, माप(adapter->chan_map));

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
		adapter->flags |= CXGB4_ROOT_NO_RELAXED_ORDERING;

	spin_lock_init(&adapter->stats_lock);
	spin_lock_init(&adapter->tid_release_lock);
	spin_lock_init(&adapter->win0_lock);

	INIT_WORK(&adapter->tid_release_task, process_tid_release_list);
	INIT_WORK(&adapter->db_full_task, process_db_full);
	INIT_WORK(&adapter->db_drop_task, process_db_drop);
	INIT_WORK(&adapter->fatal_err_notअगरy_task, notअगरy_fatal_err);

	err = t4_prep_adapter(adapter);
	अगर (err)
		जाओ out_मुक्त_adapter;

	अगर (is_kdump_kernel()) अणु
		/* Collect hardware state and append to /proc/vmcore */
		err = cxgb4_cudbg_vmcore_add_dump(adapter);
		अगर (err) अणु
			dev_warn(adapter->pdev_dev,
				 "Fail collecting vmcore device dump, err: %d. Continuing\n",
				 err);
			err = 0;
		पूर्ण
	पूर्ण

	अगर (!is_t4(adapter->params.chip)) अणु
		s_qpp = (QUEUESPERPAGEPF0_S +
			(QUEUESPERPAGEPF1_S - QUEUESPERPAGEPF0_S) *
			adapter->pf);
		qpp = 1 << QUEUESPERPAGEPF0_G(t4_पढ़ो_reg(adapter,
		      SGE_EGRESS_QUEUES_PER_PAGE_PF_A) >> s_qpp);
		num_seg = PAGE_SIZE / SEGMENT_SIZE;

		/* Each segment size is 128B. Write coalescing is enabled only
		 * when SGE_EGRESS_QUEUES_PER_PAGE_PF reg value क्रम the
		 * queue is less no of segments that can be accommodated in
		 * a page size.
		 */
		अगर (qpp > num_seg) अणु
			dev_err(&pdev->dev,
				"Incorrect number of egress queues per page\n");
			err = -EINVAL;
			जाओ out_मुक्त_adapter;
		पूर्ण
		adapter->bar2 = ioremap_wc(pci_resource_start(pdev, 2),
		pci_resource_len(pdev, 2));
		अगर (!adapter->bar2) अणु
			dev_err(&pdev->dev, "cannot map device bar2 region\n");
			err = -ENOMEM;
			जाओ out_मुक्त_adapter;
		पूर्ण
	पूर्ण

	setup_memwin(adapter);
	err = adap_init0(adapter, 0);
#अगर_घोषित CONFIG_DEBUG_FS
	biपंचांगap_zero(adapter->sge.blocked_fl, adapter->sge.egr_sz);
#पूर्ण_अगर
	setup_memwin_rdma(adapter);
	अगर (err)
		जाओ out_unmap_bar;

	/* configure SGE_STAT_CFG_A to पढ़ो WC stats */
	अगर (!is_t4(adapter->params.chip))
		t4_ग_लिखो_reg(adapter, SGE_STAT_CFG_A, STATSOURCE_T5_V(7) |
			     (is_t5(adapter->params.chip) ? STATMODE_V(0) :
			      T6_STATMODE_V(0)));

	/* Initialize hash mac addr list */
	INIT_LIST_HEAD(&adapter->mac_hlist);

	क्रम_each_port(adapter, i) अणु
		/* For supporting MQPRIO Offload, need some extra
		 * queues क्रम each ETHOFLD TIDs. Keep it equal to
		 * MAX_ATIDs क्रम now. Once we connect to firmware
		 * later and query the EOTID params, we'll come to
		 * know the actual # of EOTIDs supported.
		 */
		netdev = alloc_etherdev_mq(माप(काष्ठा port_info),
					   MAX_ETH_QSETS + MAX_ATIDS);
		अगर (!netdev) अणु
			err = -ENOMEM;
			जाओ out_मुक्त_dev;
		पूर्ण

		SET_NETDEV_DEV(netdev, &pdev->dev);

		adapter->port[i] = netdev;
		pi = netdev_priv(netdev);
		pi->adapter = adapter;
		pi->xact_addr_filt = -1;
		pi->port_id = i;
		netdev->irq = pdev->irq;

		netdev->hw_features = NETIF_F_SG | TSO_FLAGS |
			NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			NETIF_F_RXCSUM | NETIF_F_RXHASH | NETIF_F_GRO |
			NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
			NETIF_F_HW_TC | NETIF_F_NTUPLE;

		अगर (chip_ver > CHELSIO_T5) अणु
			netdev->hw_enc_features |= NETIF_F_IP_CSUM |
						   NETIF_F_IPV6_CSUM |
						   NETIF_F_RXCSUM |
						   NETIF_F_GSO_UDP_TUNNEL |
						   NETIF_F_GSO_UDP_TUNNEL_CSUM |
						   NETIF_F_TSO | NETIF_F_TSO6;

			netdev->hw_features |= NETIF_F_GSO_UDP_TUNNEL |
					       NETIF_F_GSO_UDP_TUNNEL_CSUM |
					       NETIF_F_HW_TLS_RECORD;

			अगर (adapter->rawf_cnt)
				netdev->udp_tunnel_nic_info = &cxgb_udp_tunnels;
		पूर्ण

		अगर (highdma)
			netdev->hw_features |= NETIF_F_HIGHDMA;
		netdev->features |= netdev->hw_features;
		netdev->vlan_features = netdev->features & VLAN_FEAT;
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
		अगर (pi->adapter->params.crypto & FW_CAPS_CONFIG_TLS_HW) अणु
			netdev->hw_features |= NETIF_F_HW_TLS_TX;
			netdev->tlsdev_ops = &cxgb4_ktls_ops;
			/* initialize the refcount */
			refcount_set(&pi->adapter->chcr_ktls.ktls_refcount, 0);
		पूर्ण
#पूर्ण_अगर /* CONFIG_CHELSIO_TLS_DEVICE */
#अगर IS_ENABLED(CONFIG_CHELSIO_IPSEC_INLINE)
		अगर (pi->adapter->params.crypto & FW_CAPS_CONFIG_IPSEC_INLINE) अणु
			netdev->hw_enc_features |= NETIF_F_HW_ESP;
			netdev->features |= NETIF_F_HW_ESP;
			netdev->xfrmdev_ops = &cxgb4_xfrmdev_ops;
		पूर्ण
#पूर्ण_अगर /* CONFIG_CHELSIO_IPSEC_INLINE */

		netdev->priv_flags |= IFF_UNICAST_FLT;

		/* MTU range: 81 - 9600 */
		netdev->min_mtu = 81;              /* accommodate SACK */
		netdev->max_mtu = MAX_MTU;

		netdev->netdev_ops = &cxgb4_netdev_ops;
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
		netdev->dcbnl_ops = &cxgb4_dcb_ops;
		cxgb4_dcb_state_init(netdev);
		cxgb4_dcb_version_init(netdev);
#पूर्ण_अगर
		cxgb4_set_ethtool_ops(netdev);
	पूर्ण

	cxgb4_init_ethtool_dump(adapter);

	pci_set_drvdata(pdev, adapter);

	अगर (adapter->flags & CXGB4_FW_OK) अणु
		err = t4_port_init(adapter, func, func, 0);
		अगर (err)
			जाओ out_मुक्त_dev;
	पूर्ण अन्यथा अगर (adapter->params.nports == 1) अणु
		/* If we करोn't have a connection to the firmware -- possibly
		 * because of an error -- grab the raw VPD parameters so we
		 * can set the proper MAC Address on the debug network
		 * पूर्णांकerface that we've created.
		 */
		u8 hw_addr[ETH_ALEN];
		u8 *na = adapter->params.vpd.na;

		err = t4_get_raw_vpd_params(adapter, &adapter->params.vpd);
		अगर (!err) अणु
			क्रम (i = 0; i < ETH_ALEN; i++)
				hw_addr[i] = (hex2val(na[2 * i + 0]) * 16 +
					      hex2val(na[2 * i + 1]));
			t4_set_hw_addr(adapter, 0, hw_addr);
		पूर्ण
	पूर्ण

	अगर (!(adapter->flags & CXGB4_FW_OK))
		जाओ fw_attach_fail;

	/* Configure queues and allocate tables now, they can be needed as
	 * soon as the first रेजिस्टर_netdev completes.
	 */
	err = cfg_queues(adapter);
	अगर (err)
		जाओ out_मुक्त_dev;

	adapter->smt = t4_init_smt();
	अगर (!adapter->smt) अणु
		/* We tolerate a lack of SMT, giving up some functionality */
		dev_warn(&pdev->dev, "could not allocate SMT, continuing\n");
	पूर्ण

	adapter->l2t = t4_init_l2t(adapter->l2t_start, adapter->l2t_end);
	अगर (!adapter->l2t) अणु
		/* We tolerate a lack of L2T, giving up some functionality */
		dev_warn(&pdev->dev, "could not allocate L2T, continuing\n");
		adapter->params.offload = 0;
	पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (chip_ver <= CHELSIO_T5 &&
	    (!(t4_पढ़ो_reg(adapter, LE_DB_CONFIG_A) & ASLIPCOMPEN_F))) अणु
		/* CLIP functionality is not present in hardware,
		 * hence disable all offload features
		 */
		dev_warn(&pdev->dev,
			 "CLIP not enabled in hardware, continuing\n");
		adapter->params.offload = 0;
	पूर्ण अन्यथा अणु
		adapter->clipt = t4_init_clip_tbl(adapter->clipt_start,
						  adapter->clipt_end);
		अगर (!adapter->clipt) अणु
			/* We tolerate a lack of clip_table, giving up
			 * some functionality
			 */
			dev_warn(&pdev->dev,
				 "could not allocate Clip table, continuing\n");
			adapter->params.offload = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	क्रम_each_port(adapter, i) अणु
		pi = adap2pinfo(adapter, i);
		pi->sched_tbl = t4_init_sched(adapter->params.nsched_cls);
		अगर (!pi->sched_tbl)
			dev_warn(&pdev->dev,
				 "could not activate scheduling on port %d\n",
				 i);
	पूर्ण

	अगर (is_offload(adapter) || is_hashfilter(adapter)) अणु
		अगर (t4_पढ़ो_reg(adapter, LE_DB_CONFIG_A) & HASHEN_F) अणु
			u32 v;

			v = t4_पढ़ो_reg(adapter, LE_DB_HASH_CONFIG_A);
			अगर (chip_ver <= CHELSIO_T5) अणु
				adapter->tids.nhash = 1 << HASHTIDSIZE_G(v);
				v = t4_पढ़ो_reg(adapter, LE_DB_TID_HASHBASE_A);
				adapter->tids.hash_base = v / 4;
			पूर्ण अन्यथा अणु
				adapter->tids.nhash = HASHTBLSIZE_G(v) << 3;
				v = t4_पढ़ो_reg(adapter,
						T6_LE_DB_HASH_TID_BASE_A);
				adapter->tids.hash_base = v;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (tid_init(&adapter->tids) < 0) अणु
		dev_warn(&pdev->dev, "could not allocate TID table, "
			 "continuing\n");
		adapter->params.offload = 0;
	पूर्ण अन्यथा अणु
		adapter->tc_u32 = cxgb4_init_tc_u32(adapter);
		अगर (!adapter->tc_u32)
			dev_warn(&pdev->dev,
				 "could not offload tc u32, continuing\n");

		अगर (cxgb4_init_tc_flower(adapter))
			dev_warn(&pdev->dev,
				 "could not offload tc flower, continuing\n");

		अगर (cxgb4_init_tc_mqprio(adapter))
			dev_warn(&pdev->dev,
				 "could not offload tc mqprio, continuing\n");

		अगर (cxgb4_init_tc_matchall(adapter))
			dev_warn(&pdev->dev,
				 "could not offload tc matchall, continuing\n");
		अगर (cxgb4_init_ethtool_filters(adapter))
			dev_warn(&pdev->dev,
				 "could not initialize ethtool filters, continuing\n");
	पूर्ण

	/* See what पूर्णांकerrupts we'll be using */
	अगर (msi > 1 && enable_msix(adapter) == 0)
		adapter->flags |= CXGB4_USING_MSIX;
	अन्यथा अगर (msi > 0 && pci_enable_msi(pdev) == 0) अणु
		adapter->flags |= CXGB4_USING_MSI;
		अगर (msi > 1)
			मुक्त_msix_info(adapter);
	पूर्ण

	/* check क्रम PCI Express bandwidth capabiltites */
	pcie_prपूर्णांक_link_status(pdev);

	cxgb4_init_mps_ref_entries(adapter);

	err = init_rss(adapter);
	अगर (err)
		जाओ out_मुक्त_dev;

	err = setup_non_data_पूर्णांकr(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev,
			"Non Data interrupt allocation failed, err: %d\n", err);
		जाओ out_मुक्त_dev;
	पूर्ण

	err = setup_fw_sge_queues(adapter);
	अगर (err) अणु
		dev_err(adapter->pdev_dev,
			"FW sge queue allocation failed, err %d", err);
		जाओ out_मुक्त_dev;
	पूर्ण

fw_attach_fail:
	/*
	 * The card is now पढ़ोy to go.  If any errors occur during device
	 * registration we करो not fail the whole card but rather proceed only
	 * with the ports we manage to रेजिस्टर successfully.  However we must
	 * रेजिस्टर at least one net device.
	 */
	क्रम_each_port(adapter, i) अणु
		pi = adap2pinfo(adapter, i);
		adapter->port[i]->dev_port = pi->lport;
		netअगर_set_real_num_tx_queues(adapter->port[i], pi->nqsets);
		netअगर_set_real_num_rx_queues(adapter->port[i], pi->nqsets);

		netअगर_carrier_off(adapter->port[i]);

		err = रेजिस्टर_netdev(adapter->port[i]);
		अगर (err)
			अवरोध;
		adapter->chan_map[pi->tx_chan] = i;
		prपूर्णांक_port_info(adapter->port[i]);
	पूर्ण
	अगर (i == 0) अणु
		dev_err(&pdev->dev, "could not register any net devices\n");
		जाओ out_मुक्त_dev;
	पूर्ण
	अगर (err) अणु
		dev_warn(&pdev->dev, "only %d net devices registered\n", i);
		err = 0;
	पूर्ण

	अगर (cxgb4_debugfs_root) अणु
		adapter->debugfs_root = debugfs_create_dir(pci_name(pdev),
							   cxgb4_debugfs_root);
		setup_debugfs(adapter);
	पूर्ण

	/* PCIe EEH recovery on घातerpc platक्रमms needs fundamental reset */
	pdev->needs_freset = 1;

	अगर (is_uld(adapter))
		cxgb4_uld_enable(adapter);

	अगर (!is_t4(adapter->params.chip))
		cxgb4_ptp_init(adapter);

	अगर (IS_REACHABLE(CONFIG_THERMAL) &&
	    !is_t4(adapter->params.chip) && (adapter->flags & CXGB4_FW_OK))
		cxgb4_thermal_init(adapter);

	prपूर्णांक_adapter_info(adapter);
	वापस 0;

 out_मुक्त_dev:
	t4_मुक्त_sge_resources(adapter);
	मुक्त_some_resources(adapter);
	अगर (adapter->flags & CXGB4_USING_MSIX)
		मुक्त_msix_info(adapter);
	अगर (adapter->num_uld || adapter->num_ofld_uld)
		t4_uld_mem_मुक्त(adapter);
 out_unmap_bar:
	अगर (!is_t4(adapter->params.chip))
		iounmap(adapter->bar2);
 out_मुक्त_adapter:
	अगर (adapter->workq)
		destroy_workqueue(adapter->workq);

	kमुक्त(adapter->mbox_log);
	kमुक्त(adapter);
 out_unmap_bar0:
	iounmap(regs);
 out_disable_device:
	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);
 out_release_regions:
	pci_release_regions(pdev);
	वापस err;
पूर्ण

अटल व्योम हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा hash_mac_addr *entry, *पंचांगp;

	अगर (!adapter) अणु
		pci_release_regions(pdev);
		वापस;
	पूर्ण

	/* If we allocated filters, मुक्त up state associated with any
	 * valid filters ...
	 */
	clear_all_filters(adapter);

	adapter->flags |= CXGB4_SHUTTING_DOWN;

	अगर (adapter->pf == 4) अणु
		पूर्णांक i;

		/* Tear करोwn per-adapter Work Queue first since it can contain
		 * references to our adapter data काष्ठाure.
		 */
		destroy_workqueue(adapter->workq);

		अगर (is_uld(adapter)) अणु
			detach_ulds(adapter);
			t4_uld_clean_up(adapter);
		पूर्ण

		adap_मुक्त_hma_mem(adapter);

		disable_पूर्णांकerrupts(adapter);

		cxgb4_मुक्त_mps_ref_entries(adapter);

		क्रम_each_port(adapter, i)
			अगर (adapter->port[i]->reg_state == NETREG_REGISTERED)
				unरेजिस्टर_netdev(adapter->port[i]);

		debugfs_हटाओ_recursive(adapter->debugfs_root);

		अगर (!is_t4(adapter->params.chip))
			cxgb4_ptp_stop(adapter);
		अगर (IS_REACHABLE(CONFIG_THERMAL))
			cxgb4_thermal_हटाओ(adapter);

		अगर (adapter->flags & CXGB4_FULL_INIT_DONE)
			cxgb_करोwn(adapter);

		अगर (adapter->flags & CXGB4_USING_MSIX)
			मुक्त_msix_info(adapter);
		अगर (adapter->num_uld || adapter->num_ofld_uld)
			t4_uld_mem_मुक्त(adapter);
		मुक्त_some_resources(adapter);
		list_क्रम_each_entry_safe(entry, पंचांगp, &adapter->mac_hlist,
					 list) अणु
			list_del(&entry->list);
			kमुक्त(entry);
		पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
		t4_cleanup_clip_tbl(adapter);
#पूर्ण_अगर
		अगर (!is_t4(adapter->params.chip))
			iounmap(adapter->bar2);
	पूर्ण
#अगर_घोषित CONFIG_PCI_IOV
	अन्यथा अणु
		cxgb4_iov_configure(adapter->pdev, 0);
	पूर्ण
#पूर्ण_अगर
	iounmap(adapter->regs);
	pci_disable_pcie_error_reporting(pdev);
	अगर ((adapter->flags & CXGB4_DEV_ENABLED)) अणु
		pci_disable_device(pdev);
		adapter->flags &= ~CXGB4_DEV_ENABLED;
	पूर्ण
	pci_release_regions(pdev);
	kमुक्त(adapter->mbox_log);
	synchronize_rcu();
	kमुक्त(adapter);
पूर्ण

/* "Shutdown" quiesces the device, stopping Ingress Packet and Interrupt
 * delivery.  This is essentially a stripped करोwn version of the PCI हटाओ()
 * function where we करो the minimal amount of work necessary to shutकरोwn any
 * further activity.
 */
अटल व्योम shutकरोwn_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adapter *adapter = pci_get_drvdata(pdev);

	/* As with हटाओ_one() above (see extended comment), we only want करो
	 * करो cleanup on PCI Devices which went all the way through init_one()
	 * ...
	 */
	अगर (!adapter) अणु
		pci_release_regions(pdev);
		वापस;
	पूर्ण

	adapter->flags |= CXGB4_SHUTTING_DOWN;

	अगर (adapter->pf == 4) अणु
		पूर्णांक i;

		क्रम_each_port(adapter, i)
			अगर (adapter->port[i]->reg_state == NETREG_REGISTERED)
				cxgb_बंद(adapter->port[i]);

		rtnl_lock();
		cxgb4_mqprio_stop_offload(adapter);
		rtnl_unlock();

		अगर (is_uld(adapter)) अणु
			detach_ulds(adapter);
			t4_uld_clean_up(adapter);
		पूर्ण

		disable_पूर्णांकerrupts(adapter);
		disable_msi(adapter);

		t4_sge_stop(adapter);
		अगर (adapter->flags & CXGB4_FW_OK)
			t4_fw_bye(adapter, adapter->mbox);
	पूर्ण
पूर्ण

अटल काष्ठा pci_driver cxgb4_driver = अणु
	.name     = KBUILD_MODNAME,
	.id_table = cxgb4_pci_tbl,
	.probe    = init_one,
	.हटाओ   = हटाओ_one,
	.shutकरोwn = shutकरोwn_one,
#अगर_घोषित CONFIG_PCI_IOV
	.sriov_configure = cxgb4_iov_configure,
#पूर्ण_अगर
	.err_handler = &cxgb4_eeh,
पूर्ण;

अटल पूर्णांक __init cxgb4_init_module(व्योम)
अणु
	पूर्णांक ret;

	cxgb4_debugfs_root = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	ret = pci_रेजिस्टर_driver(&cxgb4_driver);
	अगर (ret < 0)
		जाओ err_pci;

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (!inet6addr_रेजिस्टरed) अणु
		ret = रेजिस्टर_inet6addr_notअगरier(&cxgb4_inet6addr_notअगरier);
		अगर (ret)
			pci_unरेजिस्टर_driver(&cxgb4_driver);
		अन्यथा
			inet6addr_रेजिस्टरed = true;
	पूर्ण
#पूर्ण_अगर

	अगर (ret == 0)
		वापस ret;

err_pci:
	debugfs_हटाओ(cxgb4_debugfs_root);

	वापस ret;
पूर्ण

अटल व्योम __निकास cxgb4_cleanup_module(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (inet6addr_रेजिस्टरed) अणु
		unरेजिस्टर_inet6addr_notअगरier(&cxgb4_inet6addr_notअगरier);
		inet6addr_रेजिस्टरed = false;
	पूर्ण
#पूर्ण_अगर
	pci_unरेजिस्टर_driver(&cxgb4_driver);
	debugfs_हटाओ(cxgb4_debugfs_root);  /* शून्य ok */
पूर्ण

module_init(cxgb4_init_module);
module_निकास(cxgb4_cleanup_module);
