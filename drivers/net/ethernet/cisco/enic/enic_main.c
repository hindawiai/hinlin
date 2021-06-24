<शैली गुरु>
/*
 * Copyright 2008-2010 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/prefetch.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/numa.h>
#अगर_घोषित CONFIG_RFS_ACCEL
#समावेश <linux/cpu_rmap.h>
#पूर्ण_अगर
#समावेश <linux/crash_dump.h>
#समावेश <net/busy_poll.h>
#समावेश <net/vxlan.h>

#समावेश "cq_enet_desc.h"
#समावेश "vnic_dev.h"
#समावेश "vnic_intr.h"
#समावेश "vnic_stats.h"
#समावेश "vnic_vic.h"
#समावेश "enic_res.h"
#समावेश "enic.h"
#समावेश "enic_dev.h"
#समावेश "enic_pp.h"
#समावेश "enic_clsf.h"

#घोषणा ENIC_NOTIFY_TIMER_PERIOD	(2 * HZ)
#घोषणा WQ_ENET_MAX_DESC_LEN		(1 << WQ_ENET_LEN_BITS)
#घोषणा MAX_TSO				(1 << 16)
#घोषणा ENIC_DESC_MAX_SPLITS		(MAX_TSO / WQ_ENET_MAX_DESC_LEN + 1)

#घोषणा PCI_DEVICE_ID_CISCO_VIC_ENET         0x0043  /* ethernet vnic */
#घोषणा PCI_DEVICE_ID_CISCO_VIC_ENET_DYN     0x0044  /* enet dynamic vnic */
#घोषणा PCI_DEVICE_ID_CISCO_VIC_ENET_VF      0x0071  /* enet SRIOV VF */

#घोषणा RX_COPYBREAK_DEFAULT		256

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id enic_id_table[] = अणु
	अणु PCI_VDEVICE(CISCO, PCI_DEVICE_ID_CISCO_VIC_ENET) पूर्ण,
	अणु PCI_VDEVICE(CISCO, PCI_DEVICE_ID_CISCO_VIC_ENET_DYN) पूर्ण,
	अणु PCI_VDEVICE(CISCO, PCI_DEVICE_ID_CISCO_VIC_ENET_VF) पूर्ण,
	अणु 0, पूर्ण	/* end of table */
पूर्ण;

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR("Scott Feldman <scofeldm@cisco.com>");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, enic_id_table);

#घोषणा ENIC_LARGE_PKT_THRESHOLD		1000
#घोषणा ENIC_MAX_COALESCE_TIMERS		10
/*  Interrupt moderation table, which will be used to decide the
 *  coalescing समयr values
 *  अणुrx_rate in Mbps, mapping percentage of the rangeपूर्ण
 */
अटल काष्ठा enic_पूर्णांकr_mod_table mod_table[ENIC_MAX_COALESCE_TIMERS + 1] = अणु
	अणु4000,  0पूर्ण,
	अणु4400, 10पूर्ण,
	अणु5060, 20पूर्ण,
	अणु5230, 30पूर्ण,
	अणु5540, 40पूर्ण,
	अणु5820, 50पूर्ण,
	अणु6120, 60पूर्ण,
	अणु6435, 70पूर्ण,
	अणु6745, 80पूर्ण,
	अणु7000, 90पूर्ण,
	अणु0xFFFFFFFF, 100पूर्ण
पूर्ण;

/* This table helps the driver to pick dअगरferent ranges क्रम rx coalescing
 * समयr depending on the link speed.
 */
अटल काष्ठा enic_पूर्णांकr_mod_range mod_range[ENIC_MAX_LINK_SPEEDS] = अणु
	अणु0,  0पूर्ण, /* 0  - 4  Gbps */
	अणु0,  3पूर्ण, /* 4  - 10 Gbps */
	अणु3,  6पूर्ण, /* 10 - 40 Gbps */
पूर्ण;

अटल व्योम enic_init_affinity_hपूर्णांक(काष्ठा enic *enic)
अणु
	पूर्णांक numa_node = dev_to_node(&enic->pdev->dev);
	पूर्णांक i;

	क्रम (i = 0; i < enic->पूर्णांकr_count; i++) अणु
		अगर (enic_is_err_पूर्णांकr(enic, i) || enic_is_notअगरy_पूर्णांकr(enic, i) ||
		    (cpumask_available(enic->msix[i].affinity_mask) &&
		     !cpumask_empty(enic->msix[i].affinity_mask)))
			जारी;
		अगर (zalloc_cpumask_var(&enic->msix[i].affinity_mask,
				       GFP_KERNEL))
			cpumask_set_cpu(cpumask_local_spपढ़ो(i, numa_node),
					enic->msix[i].affinity_mask);
	पूर्ण
पूर्ण

अटल व्योम enic_मुक्त_affinity_hपूर्णांक(काष्ठा enic *enic)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < enic->पूर्णांकr_count; i++) अणु
		अगर (enic_is_err_पूर्णांकr(enic, i) || enic_is_notअगरy_पूर्णांकr(enic, i))
			जारी;
		मुक्त_cpumask_var(enic->msix[i].affinity_mask);
	पूर्ण
पूर्ण

अटल व्योम enic_set_affinity_hपूर्णांक(काष्ठा enic *enic)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < enic->पूर्णांकr_count; i++) अणु
		अगर (enic_is_err_पूर्णांकr(enic, i)		||
		    enic_is_notअगरy_पूर्णांकr(enic, i)	||
		    !cpumask_available(enic->msix[i].affinity_mask) ||
		    cpumask_empty(enic->msix[i].affinity_mask))
			जारी;
		err = irq_set_affinity_hपूर्णांक(enic->msix_entry[i].vector,
					    enic->msix[i].affinity_mask);
		अगर (err)
			netdev_warn(enic->netdev, "irq_set_affinity_hint failed, err %d\n",
				    err);
	पूर्ण

	क्रम (i = 0; i < enic->wq_count; i++) अणु
		पूर्णांक wq_पूर्णांकr = enic_msix_wq_पूर्णांकr(enic, i);

		अगर (cpumask_available(enic->msix[wq_पूर्णांकr].affinity_mask) &&
		    !cpumask_empty(enic->msix[wq_पूर्णांकr].affinity_mask))
			netअगर_set_xps_queue(enic->netdev,
					    enic->msix[wq_पूर्णांकr].affinity_mask,
					    i);
	पूर्ण
पूर्ण

अटल व्योम enic_unset_affinity_hपूर्णांक(काष्ठा enic *enic)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < enic->पूर्णांकr_count; i++)
		irq_set_affinity_hपूर्णांक(enic->msix_entry[i].vector, शून्य);
पूर्ण

अटल पूर्णांक enic_udp_tunnel_set_port(काष्ठा net_device *netdev,
				    अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक entry,
				    काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);

	err = vnic_dev_overlay_offload_cfg(enic->vdev,
					   OVERLAY_CFG_VXLAN_PORT_UPDATE,
					   ntohs(ti->port));
	अगर (err)
		जाओ error;

	err = vnic_dev_overlay_offload_ctrl(enic->vdev, OVERLAY_FEATURE_VXLAN,
					    enic->vxlan.patch_level);
	अगर (err)
		जाओ error;

	enic->vxlan.vxlan_udp_port_number = ntohs(ti->port);
error:
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

अटल पूर्णांक enic_udp_tunnel_unset_port(काष्ठा net_device *netdev,
				      अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक entry,
				      काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);

	err = vnic_dev_overlay_offload_ctrl(enic->vdev, OVERLAY_FEATURE_VXLAN,
					    OVERLAY_OFFLOAD_DISABLE);
	अगर (err)
		जाओ unlock;

	enic->vxlan.vxlan_udp_port_number = 0;

unlock:
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info enic_udp_tunnels = अणु
	.set_port	= enic_udp_tunnel_set_port,
	.unset_port	= enic_udp_tunnel_unset_port,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN, पूर्ण,
	पूर्ण,
पूर्ण, enic_udp_tunnels_v4 = अणु
	.set_port	= enic_udp_tunnel_set_port,
	.unset_port	= enic_udp_tunnel_unset_port,
	.flags		= UDP_TUNNEL_NIC_INFO_IPV4_ONLY,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN, पूर्ण,
	पूर्ण,
पूर्ण;

अटल netdev_features_t enic_features_check(काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	स्थिर काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb_inner_mac_header(skb);
	काष्ठा enic *enic = netdev_priv(dev);
	काष्ठा udphdr *udph;
	u16 port = 0;
	u8 proto;

	अगर (!skb->encapsulation)
		वापस features;

	features = vxlan_features_check(skb, features);

	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IPV6):
		अगर (!(enic->vxlan.flags & ENIC_VXLAN_OUTER_IPV6))
			जाओ out;
		proto = ipv6_hdr(skb)->nexthdr;
		अवरोध;
	हाल htons(ETH_P_IP):
		proto = ip_hdr(skb)->protocol;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	चयन (eth->h_proto) अणु
	हाल ntohs(ETH_P_IPV6):
		अगर (!(enic->vxlan.flags & ENIC_VXLAN_INNER_IPV6))
			जाओ out;
		fallthrough;
	हाल ntohs(ETH_P_IP):
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण


	अगर (proto == IPPROTO_UDP) अणु
		udph = udp_hdr(skb);
		port = be16_to_cpu(udph->dest);
	पूर्ण

	/* HW supports offload of only one UDP port. Remove CSUM and GSO MASK
	 * क्रम other UDP port tunnels
	 */
	अगर (port  != enic->vxlan.vxlan_udp_port_number)
		जाओ out;

	वापस features;

out:
	वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
पूर्ण

पूर्णांक enic_is_dynamic(काष्ठा enic *enic)
अणु
	वापस enic->pdev->device == PCI_DEVICE_ID_CISCO_VIC_ENET_DYN;
पूर्ण

पूर्णांक enic_sriov_enabled(काष्ठा enic *enic)
अणु
	वापस (enic->priv_flags & ENIC_SRIOV_ENABLED) ? 1 : 0;
पूर्ण

अटल पूर्णांक enic_is_sriov_vf(काष्ठा enic *enic)
अणु
	वापस enic->pdev->device == PCI_DEVICE_ID_CISCO_VIC_ENET_VF;
पूर्ण

पूर्णांक enic_is_valid_vf(काष्ठा enic *enic, पूर्णांक vf)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	वापस vf >= 0 && vf < enic->num_vfs;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल व्योम enic_मुक्त_wq_buf(काष्ठा vnic_wq *wq, काष्ठा vnic_wq_buf *buf)
अणु
	काष्ठा enic *enic = vnic_dev_priv(wq->vdev);

	अगर (buf->sop)
		dma_unmap_single(&enic->pdev->dev, buf->dma_addr, buf->len,
				 DMA_TO_DEVICE);
	अन्यथा
		dma_unmap_page(&enic->pdev->dev, buf->dma_addr, buf->len,
			       DMA_TO_DEVICE);

	अगर (buf->os_buf)
		dev_kमुक्त_skb_any(buf->os_buf);
पूर्ण

अटल व्योम enic_wq_मुक्त_buf(काष्ठा vnic_wq *wq,
	काष्ठा cq_desc *cq_desc, काष्ठा vnic_wq_buf *buf, व्योम *opaque)
अणु
	enic_मुक्त_wq_buf(wq, buf);
पूर्ण

अटल पूर्णांक enic_wq_service(काष्ठा vnic_dev *vdev, काष्ठा cq_desc *cq_desc,
	u8 type, u16 q_number, u16 completed_index, व्योम *opaque)
अणु
	काष्ठा enic *enic = vnic_dev_priv(vdev);

	spin_lock(&enic->wq_lock[q_number]);

	vnic_wq_service(&enic->wq[q_number], cq_desc,
		completed_index, enic_wq_मुक्त_buf,
		opaque);

	अगर (netअगर_tx_queue_stopped(netdev_get_tx_queue(enic->netdev, q_number)) &&
	    vnic_wq_desc_avail(&enic->wq[q_number]) >=
	    (MAX_SKB_FRAGS + ENIC_DESC_MAX_SPLITS))
		netअगर_wake_subqueue(enic->netdev, q_number);

	spin_unlock(&enic->wq_lock[q_number]);

	वापस 0;
पूर्ण

अटल bool enic_log_q_error(काष्ठा enic *enic)
अणु
	अचिन्हित पूर्णांक i;
	u32 error_status;
	bool err = false;

	क्रम (i = 0; i < enic->wq_count; i++) अणु
		error_status = vnic_wq_error_status(&enic->wq[i]);
		err |= error_status;
		अगर (error_status)
			netdev_err(enic->netdev, "WQ[%d] error_status %d\n",
				i, error_status);
	पूर्ण

	क्रम (i = 0; i < enic->rq_count; i++) अणु
		error_status = vnic_rq_error_status(&enic->rq[i]);
		err |= error_status;
		अगर (error_status)
			netdev_err(enic->netdev, "RQ[%d] error_status %d\n",
				i, error_status);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम enic_msglvl_check(काष्ठा enic *enic)
अणु
	u32 msg_enable = vnic_dev_msg_lvl(enic->vdev);

	अगर (msg_enable != enic->msg_enable) अणु
		netdev_info(enic->netdev, "msg lvl changed from 0x%x to 0x%x\n",
			enic->msg_enable, msg_enable);
		enic->msg_enable = msg_enable;
	पूर्ण
पूर्ण

अटल व्योम enic_mtu_check(काष्ठा enic *enic)
अणु
	u32 mtu = vnic_dev_mtu(enic->vdev);
	काष्ठा net_device *netdev = enic->netdev;

	अगर (mtu && mtu != enic->port_mtu) अणु
		enic->port_mtu = mtu;
		अगर (enic_is_dynamic(enic) || enic_is_sriov_vf(enic)) अणु
			mtu = max_t(पूर्णांक, ENIC_MIN_MTU,
				min_t(पूर्णांक, ENIC_MAX_MTU, mtu));
			अगर (mtu != netdev->mtu)
				schedule_work(&enic->change_mtu_work);
		पूर्ण अन्यथा अणु
			अगर (mtu < netdev->mtu)
				netdev_warn(netdev,
					"interface MTU (%d) set higher "
					"than switch port MTU (%d)\n",
					netdev->mtu, mtu);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम enic_link_check(काष्ठा enic *enic)
अणु
	पूर्णांक link_status = vnic_dev_link_status(enic->vdev);
	पूर्णांक carrier_ok = netअगर_carrier_ok(enic->netdev);

	अगर (link_status && !carrier_ok) अणु
		netdev_info(enic->netdev, "Link UP\n");
		netअगर_carrier_on(enic->netdev);
	पूर्ण अन्यथा अगर (!link_status && carrier_ok) अणु
		netdev_info(enic->netdev, "Link DOWN\n");
		netअगर_carrier_off(enic->netdev);
	पूर्ण
पूर्ण

अटल व्योम enic_notअगरy_check(काष्ठा enic *enic)
अणु
	enic_msglvl_check(enic);
	enic_mtu_check(enic);
	enic_link_check(enic);
पूर्ण

#घोषणा ENIC_TEST_INTR(pba, i) (pba & (1 << i))

अटल irqवापस_t enic_isr_legacy(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा enic *enic = netdev_priv(netdev);
	अचिन्हित पूर्णांक io_पूर्णांकr = enic_legacy_io_पूर्णांकr();
	अचिन्हित पूर्णांक err_पूर्णांकr = enic_legacy_err_पूर्णांकr();
	अचिन्हित पूर्णांक notअगरy_पूर्णांकr = enic_legacy_notअगरy_पूर्णांकr();
	u32 pba;

	vnic_पूर्णांकr_mask(&enic->पूर्णांकr[io_पूर्णांकr]);

	pba = vnic_पूर्णांकr_legacy_pba(enic->legacy_pba);
	अगर (!pba) अणु
		vnic_पूर्णांकr_unmask(&enic->पूर्णांकr[io_पूर्णांकr]);
		वापस IRQ_NONE;	/* not our पूर्णांकerrupt */
	पूर्ण

	अगर (ENIC_TEST_INTR(pba, notअगरy_पूर्णांकr)) अणु
		enic_notअगरy_check(enic);
		vnic_पूर्णांकr_वापस_all_credits(&enic->पूर्णांकr[notअगरy_पूर्णांकr]);
	पूर्ण

	अगर (ENIC_TEST_INTR(pba, err_पूर्णांकr)) अणु
		vnic_पूर्णांकr_वापस_all_credits(&enic->पूर्णांकr[err_पूर्णांकr]);
		enic_log_q_error(enic);
		/* schedule recovery from WQ/RQ error */
		schedule_work(&enic->reset);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (ENIC_TEST_INTR(pba, io_पूर्णांकr))
		napi_schedule_irqoff(&enic->napi[0]);
	अन्यथा
		vnic_पूर्णांकr_unmask(&enic->पूर्णांकr[io_पूर्णांकr]);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t enic_isr_msi(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा enic *enic = data;

	/* With MSI, there is no sharing of पूर्णांकerrupts, so this is
	 * our पूर्णांकerrupt and there is no need to ack it.  The device
	 * is not providing per-vector masking, so the OS will not
	 * ग_लिखो to PCI config space to mask/unmask the पूर्णांकerrupt.
	 * We're using mask_on_निश्चितion क्रम MSI, so the device
	 * स्वतःmatically masks the पूर्णांकerrupt when the पूर्णांकerrupt is
	 * generated.  Later, when निकासing polling, the पूर्णांकerrupt
	 * will be unmasked (see enic_poll).
	 *
	 * Also, the device uses the same PCIe Traffic Class (TC)
	 * क्रम Memory Write data and MSI, so there are no ordering
	 * issues; the MSI will always arrive at the Root Complex
	 * _after_ corresponding Memory Writes (i.e. descriptor
	 * ग_लिखोs).
	 */

	napi_schedule_irqoff(&enic->napi[0]);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t enic_isr_msix(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा napi_काष्ठा *napi = data;

	napi_schedule_irqoff(napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t enic_isr_msix_err(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा enic *enic = data;
	अचिन्हित पूर्णांक पूर्णांकr = enic_msix_err_पूर्णांकr(enic);

	vnic_पूर्णांकr_वापस_all_credits(&enic->पूर्णांकr[पूर्णांकr]);

	अगर (enic_log_q_error(enic))
		/* schedule recovery from WQ/RQ error */
		schedule_work(&enic->reset);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t enic_isr_msix_notअगरy(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा enic *enic = data;
	अचिन्हित पूर्णांक पूर्णांकr = enic_msix_notअगरy_पूर्णांकr(enic);

	enic_notअगरy_check(enic);
	vnic_पूर्णांकr_वापस_all_credits(&enic->पूर्णांकr[पूर्णांकr]);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक enic_queue_wq_skb_cont(काष्ठा enic *enic, काष्ठा vnic_wq *wq,
				  काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len_left,
				  पूर्णांक loopback)
अणु
	स्थिर skb_frag_t *frag;
	dma_addr_t dma_addr;

	/* Queue additional data fragments */
	क्रम (frag = skb_shinfo(skb)->frags; len_left; frag++) अणु
		len_left -= skb_frag_size(frag);
		dma_addr = skb_frag_dma_map(&enic->pdev->dev, frag, 0,
					    skb_frag_size(frag),
					    DMA_TO_DEVICE);
		अगर (unlikely(enic_dma_map_check(enic, dma_addr)))
			वापस -ENOMEM;
		enic_queue_wq_desc_cont(wq, skb, dma_addr, skb_frag_size(frag),
					(len_left == 0),	/* EOP? */
					loopback);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enic_queue_wq_skb_vlan(काष्ठा enic *enic, काष्ठा vnic_wq *wq,
				  काष्ठा sk_buff *skb, पूर्णांक vlan_tag_insert,
				  अचिन्हित पूर्णांक vlan_tag, पूर्णांक loopback)
अणु
	अचिन्हित पूर्णांक head_len = skb_headlen(skb);
	अचिन्हित पूर्णांक len_left = skb->len - head_len;
	पूर्णांक eop = (len_left == 0);
	dma_addr_t dma_addr;
	पूर्णांक err = 0;

	dma_addr = dma_map_single(&enic->pdev->dev, skb->data, head_len,
				  DMA_TO_DEVICE);
	अगर (unlikely(enic_dma_map_check(enic, dma_addr)))
		वापस -ENOMEM;

	/* Queue the मुख्य skb fragment. The fragments are no larger
	 * than max MTU(9000)+ETH_HDR_LEN(14) bytes, which is less
	 * than WQ_ENET_MAX_DESC_LEN length. So only one descriptor
	 * per fragment is queued.
	 */
	enic_queue_wq_desc(wq, skb, dma_addr, head_len,	vlan_tag_insert,
			   vlan_tag, eop, loopback);

	अगर (!eop)
		err = enic_queue_wq_skb_cont(enic, wq, skb, len_left, loopback);

	वापस err;
पूर्ण

अटल पूर्णांक enic_queue_wq_skb_csum_l4(काष्ठा enic *enic, काष्ठा vnic_wq *wq,
				     काष्ठा sk_buff *skb, पूर्णांक vlan_tag_insert,
				     अचिन्हित पूर्णांक vlan_tag, पूर्णांक loopback)
अणु
	अचिन्हित पूर्णांक head_len = skb_headlen(skb);
	अचिन्हित पूर्णांक len_left = skb->len - head_len;
	अचिन्हित पूर्णांक hdr_len = skb_checksum_start_offset(skb);
	अचिन्हित पूर्णांक csum_offset = hdr_len + skb->csum_offset;
	पूर्णांक eop = (len_left == 0);
	dma_addr_t dma_addr;
	पूर्णांक err = 0;

	dma_addr = dma_map_single(&enic->pdev->dev, skb->data, head_len,
				  DMA_TO_DEVICE);
	अगर (unlikely(enic_dma_map_check(enic, dma_addr)))
		वापस -ENOMEM;

	/* Queue the मुख्य skb fragment. The fragments are no larger
	 * than max MTU(9000)+ETH_HDR_LEN(14) bytes, which is less
	 * than WQ_ENET_MAX_DESC_LEN length. So only one descriptor
	 * per fragment is queued.
	 */
	enic_queue_wq_desc_csum_l4(wq, skb, dma_addr, head_len,	csum_offset,
				   hdr_len, vlan_tag_insert, vlan_tag, eop,
				   loopback);

	अगर (!eop)
		err = enic_queue_wq_skb_cont(enic, wq, skb, len_left, loopback);

	वापस err;
पूर्ण

अटल व्योम enic_preload_tcp_csum_encap(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb_inner_mac_header(skb);

	चयन (eth->h_proto) अणु
	हाल ntohs(ETH_P_IP):
		inner_ip_hdr(skb)->check = 0;
		inner_tcp_hdr(skb)->check =
			~csum_tcpudp_magic(inner_ip_hdr(skb)->saddr,
					   inner_ip_hdr(skb)->daddr, 0,
					   IPPROTO_TCP, 0);
		अवरोध;
	हाल ntohs(ETH_P_IPV6):
		inner_tcp_hdr(skb)->check =
			~csum_ipv6_magic(&inner_ipv6_hdr(skb)->saddr,
					 &inner_ipv6_hdr(skb)->daddr, 0,
					 IPPROTO_TCP, 0);
		अवरोध;
	शेष:
		WARN_ONCE(1, "Non ipv4/ipv6 inner pkt for encap offload");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम enic_preload_tcp_csum(काष्ठा sk_buff *skb)
अणु
	/* Preload TCP csum field with IP pseuकरो hdr calculated
	 * with IP length set to zero.  HW will later add in length
	 * to each TCP segment resulting from the TSO.
	 */

	अगर (skb->protocol == cpu_to_be16(ETH_P_IP)) अणु
		ip_hdr(skb)->check = 0;
		tcp_hdr(skb)->check = ~csum_tcpudp_magic(ip_hdr(skb)->saddr,
			ip_hdr(skb)->daddr, 0, IPPROTO_TCP, 0);
	पूर्ण अन्यथा अगर (skb->protocol == cpu_to_be16(ETH_P_IPV6)) अणु
		tcp_v6_gso_csum_prep(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक enic_queue_wq_skb_tso(काष्ठा enic *enic, काष्ठा vnic_wq *wq,
				 काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mss,
				 पूर्णांक vlan_tag_insert, अचिन्हित पूर्णांक vlan_tag,
				 पूर्णांक loopback)
अणु
	अचिन्हित पूर्णांक frag_len_left = skb_headlen(skb);
	अचिन्हित पूर्णांक len_left = skb->len - frag_len_left;
	पूर्णांक eop = (len_left == 0);
	अचिन्हित पूर्णांक offset = 0;
	अचिन्हित पूर्णांक hdr_len;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक len;
	skb_frag_t *frag;

	अगर (skb->encapsulation) अणु
		hdr_len = skb_inner_transport_header(skb) - skb->data;
		hdr_len += inner_tcp_hdrlen(skb);
		enic_preload_tcp_csum_encap(skb);
	पूर्ण अन्यथा अणु
		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		enic_preload_tcp_csum(skb);
	पूर्ण

	/* Queue WQ_ENET_MAX_DESC_LEN length descriptors
	 * क्रम the मुख्य skb fragment
	 */
	जबतक (frag_len_left) अणु
		len = min(frag_len_left, (अचिन्हित पूर्णांक)WQ_ENET_MAX_DESC_LEN);
		dma_addr = dma_map_single(&enic->pdev->dev,
					  skb->data + offset, len,
					  DMA_TO_DEVICE);
		अगर (unlikely(enic_dma_map_check(enic, dma_addr)))
			वापस -ENOMEM;
		enic_queue_wq_desc_tso(wq, skb, dma_addr, len, mss, hdr_len,
				       vlan_tag_insert, vlan_tag,
				       eop && (len == frag_len_left), loopback);
		frag_len_left -= len;
		offset += len;
	पूर्ण

	अगर (eop)
		वापस 0;

	/* Queue WQ_ENET_MAX_DESC_LEN length descriptors
	 * क्रम additional data fragments
	 */
	क्रम (frag = skb_shinfo(skb)->frags; len_left; frag++) अणु
		len_left -= skb_frag_size(frag);
		frag_len_left = skb_frag_size(frag);
		offset = 0;

		जबतक (frag_len_left) अणु
			len = min(frag_len_left,
				(अचिन्हित पूर्णांक)WQ_ENET_MAX_DESC_LEN);
			dma_addr = skb_frag_dma_map(&enic->pdev->dev, frag,
						    offset, len,
						    DMA_TO_DEVICE);
			अगर (unlikely(enic_dma_map_check(enic, dma_addr)))
				वापस -ENOMEM;
			enic_queue_wq_desc_cont(wq, skb, dma_addr, len,
						(len_left == 0) &&
						 (len == frag_len_left),/*EOP*/
						loopback);
			frag_len_left -= len;
			offset += len;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक enic_queue_wq_skb_encap(काष्ठा enic *enic, काष्ठा vnic_wq *wq,
					  काष्ठा sk_buff *skb,
					  पूर्णांक vlan_tag_insert,
					  अचिन्हित पूर्णांक vlan_tag, पूर्णांक loopback)
अणु
	अचिन्हित पूर्णांक head_len = skb_headlen(skb);
	अचिन्हित पूर्णांक len_left = skb->len - head_len;
	/* Hardware will overग_लिखो the checksum fields, calculating from
	 * scratch and ignoring the value placed by software.
	 * Offload mode = 00
	 * mss[2], mss[1], mss[0] bits are set
	 */
	अचिन्हित पूर्णांक mss_or_csum = 7;
	पूर्णांक eop = (len_left == 0);
	dma_addr_t dma_addr;
	पूर्णांक err = 0;

	dma_addr = dma_map_single(&enic->pdev->dev, skb->data, head_len,
				  DMA_TO_DEVICE);
	अगर (unlikely(enic_dma_map_check(enic, dma_addr)))
		वापस -ENOMEM;

	enic_queue_wq_desc_ex(wq, skb, dma_addr, head_len, mss_or_csum, 0,
			      vlan_tag_insert, vlan_tag,
			      WQ_ENET_OFFLOAD_MODE_CSUM, eop, 1 /* SOP */, eop,
			      loopback);
	अगर (!eop)
		err = enic_queue_wq_skb_cont(enic, wq, skb, len_left, loopback);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक enic_queue_wq_skb(काष्ठा enic *enic,
	काष्ठा vnic_wq *wq, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक mss = skb_shinfo(skb)->gso_size;
	अचिन्हित पूर्णांक vlan_tag = 0;
	पूर्णांक vlan_tag_insert = 0;
	पूर्णांक loopback = 0;
	पूर्णांक err;

	अगर (skb_vlan_tag_present(skb)) अणु
		/* VLAN tag from trunking driver */
		vlan_tag_insert = 1;
		vlan_tag = skb_vlan_tag_get(skb);
	पूर्ण अन्यथा अगर (enic->loop_enable) अणु
		vlan_tag = enic->loop_tag;
		loopback = 1;
	पूर्ण

	अगर (mss)
		err = enic_queue_wq_skb_tso(enic, wq, skb, mss,
					    vlan_tag_insert, vlan_tag,
					    loopback);
	अन्यथा अगर (skb->encapsulation)
		err = enic_queue_wq_skb_encap(enic, wq, skb, vlan_tag_insert,
					      vlan_tag, loopback);
	अन्यथा अगर	(skb->ip_summed == CHECKSUM_PARTIAL)
		err = enic_queue_wq_skb_csum_l4(enic, wq, skb, vlan_tag_insert,
						vlan_tag, loopback);
	अन्यथा
		err = enic_queue_wq_skb_vlan(enic, wq, skb, vlan_tag_insert,
					     vlan_tag, loopback);
	अगर (unlikely(err)) अणु
		काष्ठा vnic_wq_buf *buf;

		buf = wq->to_use->prev;
		/* जबतक not EOP of previous pkt && queue not empty.
		 * For all non EOP bufs, os_buf is शून्य.
		 */
		जबतक (!buf->os_buf && (buf->next != wq->to_clean)) अणु
			enic_मुक्त_wq_buf(wq, buf);
			wq->ring.desc_avail++;
			buf = buf->prev;
		पूर्ण
		wq->to_use = buf->next;
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस err;
पूर्ण

/* netअगर_tx_lock held, process context with BHs disabled, or BH */
अटल netdev_tx_t enic_hard_start_xmit(काष्ठा sk_buff *skb,
	काष्ठा net_device *netdev)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा vnic_wq *wq;
	अचिन्हित पूर्णांक txq_map;
	काष्ठा netdev_queue *txq;

	अगर (skb->len <= 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	txq_map = skb_get_queue_mapping(skb) % enic->wq_count;
	wq = &enic->wq[txq_map];
	txq = netdev_get_tx_queue(netdev, txq_map);

	/* Non-TSO sends must fit within ENIC_NON_TSO_MAX_DESC descs,
	 * which is very likely.  In the off chance it's going to take
	 * more than * ENIC_NON_TSO_MAX_DESC, linearize the skb.
	 */

	अगर (skb_shinfo(skb)->gso_size == 0 &&
	    skb_shinfo(skb)->nr_frags + 1 > ENIC_NON_TSO_MAX_DESC &&
	    skb_linearize(skb)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	spin_lock(&enic->wq_lock[txq_map]);

	अगर (vnic_wq_desc_avail(wq) <
	    skb_shinfo(skb)->nr_frags + ENIC_DESC_MAX_SPLITS) अणु
		netअगर_tx_stop_queue(txq);
		/* This is a hard error, log it */
		netdev_err(netdev, "BUG! Tx ring full when queue awake!\n");
		spin_unlock(&enic->wq_lock[txq_map]);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (enic_queue_wq_skb(enic, wq, skb))
		जाओ error;

	अगर (vnic_wq_desc_avail(wq) < MAX_SKB_FRAGS + ENIC_DESC_MAX_SPLITS)
		netअगर_tx_stop_queue(txq);
	skb_tx_बारtamp(skb);
	अगर (!netdev_xmit_more() || netअगर_xmit_stopped(txq))
		vnic_wq_करोorbell(wq);

error:
	spin_unlock(&enic->wq_lock[txq_map]);

	वापस NETDEV_TX_OK;
पूर्ण

/* dev_base_lock rwlock held, nominally process context */
अटल व्योम enic_get_stats(काष्ठा net_device *netdev,
			   काष्ठा rtnl_link_stats64 *net_stats)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा vnic_stats *stats;
	पूर्णांक err;

	err = enic_dev_stats_dump(enic, &stats);
	/* वापस only when pci_zalloc_consistent fails in vnic_dev_stats_dump
	 * For other failures, like devcmd failure, we वापस previously
	 * recorded stats.
	 */
	अगर (err == -ENOMEM)
		वापस;

	net_stats->tx_packets = stats->tx.tx_frames_ok;
	net_stats->tx_bytes = stats->tx.tx_bytes_ok;
	net_stats->tx_errors = stats->tx.tx_errors;
	net_stats->tx_dropped = stats->tx.tx_drops;

	net_stats->rx_packets = stats->rx.rx_frames_ok;
	net_stats->rx_bytes = stats->rx.rx_bytes_ok;
	net_stats->rx_errors = stats->rx.rx_errors;
	net_stats->multicast = stats->rx.rx_multicast_frames_ok;
	net_stats->rx_over_errors = enic->rq_truncated_pkts;
	net_stats->rx_crc_errors = enic->rq_bad_fcs;
	net_stats->rx_dropped = stats->rx.rx_no_bufs + stats->rx.rx_drop;
पूर्ण

अटल पूर्णांक enic_mc_sync(काष्ठा net_device *netdev, स्थिर u8 *mc_addr)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);

	अगर (enic->mc_count == ENIC_MULTICAST_PERFECT_FILTERS) अणु
		अचिन्हित पूर्णांक mc_count = netdev_mc_count(netdev);

		netdev_warn(netdev, "Registering only %d out of %d multicast addresses\n",
			    ENIC_MULTICAST_PERFECT_FILTERS, mc_count);

		वापस -ENOSPC;
	पूर्ण

	enic_dev_add_addr(enic, mc_addr);
	enic->mc_count++;

	वापस 0;
पूर्ण

अटल पूर्णांक enic_mc_unsync(काष्ठा net_device *netdev, स्थिर u8 *mc_addr)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);

	enic_dev_del_addr(enic, mc_addr);
	enic->mc_count--;

	वापस 0;
पूर्ण

अटल पूर्णांक enic_uc_sync(काष्ठा net_device *netdev, स्थिर u8 *uc_addr)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);

	अगर (enic->uc_count == ENIC_UNICAST_PERFECT_FILTERS) अणु
		अचिन्हित पूर्णांक uc_count = netdev_uc_count(netdev);

		netdev_warn(netdev, "Registering only %d out of %d unicast addresses\n",
			    ENIC_UNICAST_PERFECT_FILTERS, uc_count);

		वापस -ENOSPC;
	पूर्ण

	enic_dev_add_addr(enic, uc_addr);
	enic->uc_count++;

	वापस 0;
पूर्ण

अटल पूर्णांक enic_uc_unsync(काष्ठा net_device *netdev, स्थिर u8 *uc_addr)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);

	enic_dev_del_addr(enic, uc_addr);
	enic->uc_count--;

	वापस 0;
पूर्ण

व्योम enic_reset_addr_lists(काष्ठा enic *enic)
अणु
	काष्ठा net_device *netdev = enic->netdev;

	__dev_uc_unsync(netdev, शून्य);
	__dev_mc_unsync(netdev, शून्य);

	enic->mc_count = 0;
	enic->uc_count = 0;
	enic->flags = 0;
पूर्ण

अटल पूर्णांक enic_set_mac_addr(काष्ठा net_device *netdev, अक्षर *addr)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);

	अगर (enic_is_dynamic(enic) || enic_is_sriov_vf(enic)) अणु
		अगर (!is_valid_ether_addr(addr) && !is_zero_ether_addr(addr))
			वापस -EADDRNOTAVAIL;
	पूर्ण अन्यथा अणु
		अगर (!is_valid_ether_addr(addr))
			वापस -EADDRNOTAVAIL;
	पूर्ण

	स_नकल(netdev->dev_addr, addr, netdev->addr_len);

	वापस 0;
पूर्ण

अटल पूर्णांक enic_set_mac_address_dynamic(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा sockaddr *saddr = p;
	अक्षर *addr = saddr->sa_data;
	पूर्णांक err;

	अगर (netअगर_running(enic->netdev)) अणु
		err = enic_dev_del_station_addr(enic);
		अगर (err)
			वापस err;
	पूर्ण

	err = enic_set_mac_addr(netdev, addr);
	अगर (err)
		वापस err;

	अगर (netअगर_running(enic->netdev)) अणु
		err = enic_dev_add_station_addr(enic);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक enic_set_mac_address(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा sockaddr *saddr = p;
	अक्षर *addr = saddr->sa_data;
	काष्ठा enic *enic = netdev_priv(netdev);
	पूर्णांक err;

	err = enic_dev_del_station_addr(enic);
	अगर (err)
		वापस err;

	err = enic_set_mac_addr(netdev, addr);
	अगर (err)
		वापस err;

	वापस enic_dev_add_station_addr(enic);
पूर्ण

/* netअगर_tx_lock held, BHs disabled */
अटल व्योम enic_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	पूर्णांक directed = 1;
	पूर्णांक multicast = (netdev->flags & IFF_MULTICAST) ? 1 : 0;
	पूर्णांक broadcast = (netdev->flags & IFF_BROADCAST) ? 1 : 0;
	पूर्णांक promisc = (netdev->flags & IFF_PROMISC) ||
		netdev_uc_count(netdev) > ENIC_UNICAST_PERFECT_FILTERS;
	पूर्णांक allmulti = (netdev->flags & IFF_ALLMULTI) ||
		netdev_mc_count(netdev) > ENIC_MULTICAST_PERFECT_FILTERS;
	अचिन्हित पूर्णांक flags = netdev->flags |
		(allmulti ? IFF_ALLMULTI : 0) |
		(promisc ? IFF_PROMISC : 0);

	अगर (enic->flags != flags) अणु
		enic->flags = flags;
		enic_dev_packet_filter(enic, directed,
			multicast, broadcast, promisc, allmulti);
	पूर्ण

	अगर (!promisc) अणु
		__dev_uc_sync(netdev, enic_uc_sync, enic_uc_unsync);
		अगर (!allmulti)
			__dev_mc_sync(netdev, enic_mc_sync, enic_mc_unsync);
	पूर्ण
पूर्ण

/* netअगर_tx_lock held, BHs disabled */
अटल व्योम enic_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	schedule_work(&enic->tx_hang_reset);
पूर्ण

अटल पूर्णांक enic_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा enic_port_profile *pp;
	पूर्णांक err;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	अगर (err)
		वापस err;

	अगर (is_valid_ether_addr(mac) || is_zero_ether_addr(mac)) अणु
		अगर (vf == PORT_SELF_VF) अणु
			स_नकल(pp->vf_mac, mac, ETH_ALEN);
			वापस 0;
		पूर्ण अन्यथा अणु
			/*
			 * For sriov vf's set the mac in hw
			 */
			ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic,
				vnic_dev_set_mac_addr, mac);
			वापस enic_dev_status_to_त्रुटि_सं(err);
		पूर्ण
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक enic_set_vf_port(काष्ठा net_device *netdev, पूर्णांक vf,
	काष्ठा nlattr *port[])
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा enic_port_profile prev_pp;
	काष्ठा enic_port_profile *pp;
	पूर्णांक err = 0, restore_pp = 1;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	अगर (err)
		वापस err;

	अगर (!port[IFLA_PORT_REQUEST])
		वापस -EOPNOTSUPP;

	स_नकल(&prev_pp, pp, माप(*enic->pp));
	स_रखो(pp, 0, माप(*enic->pp));

	pp->set |= ENIC_SET_REQUEST;
	pp->request = nla_get_u8(port[IFLA_PORT_REQUEST]);

	अगर (port[IFLA_PORT_PROखाता]) अणु
		pp->set |= ENIC_SET_NAME;
		स_नकल(pp->name, nla_data(port[IFLA_PORT_PROखाता]),
			PORT_PROखाता_MAX);
	पूर्ण

	अगर (port[IFLA_PORT_INSTANCE_UUID]) अणु
		pp->set |= ENIC_SET_INSTANCE;
		स_नकल(pp->instance_uuid,
			nla_data(port[IFLA_PORT_INSTANCE_UUID]), PORT_UUID_MAX);
	पूर्ण

	अगर (port[IFLA_PORT_HOST_UUID]) अणु
		pp->set |= ENIC_SET_HOST;
		स_नकल(pp->host_uuid,
			nla_data(port[IFLA_PORT_HOST_UUID]), PORT_UUID_MAX);
	पूर्ण

	अगर (vf == PORT_SELF_VF) अणु
		/* Special हाल handling: mac came from IFLA_VF_MAC */
		अगर (!is_zero_ether_addr(prev_pp.vf_mac))
			स_नकल(pp->mac_addr, prev_pp.vf_mac, ETH_ALEN);

		अगर (is_zero_ether_addr(netdev->dev_addr))
			eth_hw_addr_अक्रमom(netdev);
	पूर्ण अन्यथा अणु
		/* SR-IOV VF: get mac from adapter */
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic,
			vnic_dev_get_mac_addr, pp->mac_addr);
		अगर (err) अणु
			netdev_err(netdev, "Error getting mac for vf %d\n", vf);
			स_नकल(pp, &prev_pp, माप(*pp));
			वापस enic_dev_status_to_त्रुटि_सं(err);
		पूर्ण
	पूर्ण

	err = enic_process_set_pp_request(enic, vf, &prev_pp, &restore_pp);
	अगर (err) अणु
		अगर (restore_pp) अणु
			/* Things are still the way they were: Implicit
			 * DISASSOCIATE failed
			 */
			स_नकल(pp, &prev_pp, माप(*pp));
		पूर्ण अन्यथा अणु
			स_रखो(pp, 0, माप(*pp));
			अगर (vf == PORT_SELF_VF)
				eth_zero_addr(netdev->dev_addr);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Set flag to indicate that the port assoc/disassoc
		 * request has been sent out to fw
		 */
		pp->set |= ENIC_PORT_REQUEST_APPLIED;

		/* If DISASSOCIATE, clean up all asचिन्हित/saved macaddresses */
		अगर (pp->request == PORT_REQUEST_DISASSOCIATE) अणु
			eth_zero_addr(pp->mac_addr);
			अगर (vf == PORT_SELF_VF)
				eth_zero_addr(netdev->dev_addr);
		पूर्ण
	पूर्ण

	अगर (vf == PORT_SELF_VF)
		eth_zero_addr(pp->vf_mac);

	वापस err;
पूर्ण

अटल पूर्णांक enic_get_vf_port(काष्ठा net_device *netdev, पूर्णांक vf,
	काष्ठा sk_buff *skb)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	u16 response = PORT_PROखाता_RESPONSE_SUCCESS;
	काष्ठा enic_port_profile *pp;
	पूर्णांक err;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	अगर (err)
		वापस err;

	अगर (!(pp->set & ENIC_PORT_REQUEST_APPLIED))
		वापस -ENODATA;

	err = enic_process_get_pp_request(enic, vf, pp->request, &response);
	अगर (err)
		वापस err;

	अगर (nla_put_u16(skb, IFLA_PORT_REQUEST, pp->request) ||
	    nla_put_u16(skb, IFLA_PORT_RESPONSE, response) ||
	    ((pp->set & ENIC_SET_NAME) &&
	     nla_put(skb, IFLA_PORT_PROखाता, PORT_PROखाता_MAX, pp->name)) ||
	    ((pp->set & ENIC_SET_INSTANCE) &&
	     nla_put(skb, IFLA_PORT_INSTANCE_UUID, PORT_UUID_MAX,
		     pp->instance_uuid)) ||
	    ((pp->set & ENIC_SET_HOST) &&
	     nla_put(skb, IFLA_PORT_HOST_UUID, PORT_UUID_MAX, pp->host_uuid)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम enic_मुक्त_rq_buf(काष्ठा vnic_rq *rq, काष्ठा vnic_rq_buf *buf)
अणु
	काष्ठा enic *enic = vnic_dev_priv(rq->vdev);

	अगर (!buf->os_buf)
		वापस;

	dma_unmap_single(&enic->pdev->dev, buf->dma_addr, buf->len,
			 DMA_FROM_DEVICE);
	dev_kमुक्त_skb_any(buf->os_buf);
	buf->os_buf = शून्य;
पूर्ण

अटल पूर्णांक enic_rq_alloc_buf(काष्ठा vnic_rq *rq)
अणु
	काष्ठा enic *enic = vnic_dev_priv(rq->vdev);
	काष्ठा net_device *netdev = enic->netdev;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len = netdev->mtu + VLAN_ETH_HLEN;
	अचिन्हित पूर्णांक os_buf_index = 0;
	dma_addr_t dma_addr;
	काष्ठा vnic_rq_buf *buf = rq->to_use;

	अगर (buf->os_buf) अणु
		enic_queue_rq_desc(rq, buf->os_buf, os_buf_index, buf->dma_addr,
				   buf->len);

		वापस 0;
	पूर्ण
	skb = netdev_alloc_skb_ip_align(netdev, len);
	अगर (!skb)
		वापस -ENOMEM;

	dma_addr = dma_map_single(&enic->pdev->dev, skb->data, len,
				  DMA_FROM_DEVICE);
	अगर (unlikely(enic_dma_map_check(enic, dma_addr))) अणु
		dev_kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	enic_queue_rq_desc(rq, skb, os_buf_index,
		dma_addr, len);

	वापस 0;
पूर्ण

अटल व्योम enic_पूर्णांकr_update_pkt_size(काष्ठा vnic_rx_bytes_counter *pkt_size,
				      u32 pkt_len)
अणु
	अगर (ENIC_LARGE_PKT_THRESHOLD <= pkt_len)
		pkt_size->large_pkt_bytes_cnt += pkt_len;
	अन्यथा
		pkt_size->small_pkt_bytes_cnt += pkt_len;
पूर्ण

अटल bool enic_rxcopyअवरोध(काष्ठा net_device *netdev, काष्ठा sk_buff **skb,
			     काष्ठा vnic_rq_buf *buf, u16 len)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा sk_buff *new_skb;

	अगर (len > enic->rx_copyअवरोध)
		वापस false;
	new_skb = netdev_alloc_skb_ip_align(netdev, len);
	अगर (!new_skb)
		वापस false;
	dma_sync_single_क्रम_cpu(&enic->pdev->dev, buf->dma_addr, len,
				DMA_FROM_DEVICE);
	स_नकल(new_skb->data, (*skb)->data, len);
	*skb = new_skb;

	वापस true;
पूर्ण

अटल व्योम enic_rq_indicate_buf(काष्ठा vnic_rq *rq,
	काष्ठा cq_desc *cq_desc, काष्ठा vnic_rq_buf *buf,
	पूर्णांक skipped, व्योम *opaque)
अणु
	काष्ठा enic *enic = vnic_dev_priv(rq->vdev);
	काष्ठा net_device *netdev = enic->netdev;
	काष्ठा sk_buff *skb;
	काष्ठा vnic_cq *cq = &enic->cq[enic_cq_rq(enic, rq->index)];

	u8 type, color, eop, sop, ingress_port, vlan_stripped;
	u8 fcoe, fcoe_sof, fcoe_fc_crc_ok, fcoe_enc_error, fcoe_eof;
	u8 tcp_udp_csum_ok, udp, tcp, ipv4_csum_ok;
	u8 ipv6, ipv4, ipv4_fragment, fcs_ok, rss_type, csum_not_calc;
	u8 packet_error;
	u16 q_number, completed_index, bytes_written, vlan_tci, checksum;
	u32 rss_hash;
	bool outer_csum_ok = true, encap = false;

	अगर (skipped)
		वापस;

	skb = buf->os_buf;

	cq_enet_rq_desc_dec((काष्ठा cq_enet_rq_desc *)cq_desc,
		&type, &color, &q_number, &completed_index,
		&ingress_port, &fcoe, &eop, &sop, &rss_type,
		&csum_not_calc, &rss_hash, &bytes_written,
		&packet_error, &vlan_stripped, &vlan_tci, &checksum,
		&fcoe_sof, &fcoe_fc_crc_ok, &fcoe_enc_error,
		&fcoe_eof, &tcp_udp_csum_ok, &udp, &tcp,
		&ipv4_csum_ok, &ipv6, &ipv4, &ipv4_fragment,
		&fcs_ok);

	अगर (packet_error) अणु

		अगर (!fcs_ok) अणु
			अगर (bytes_written > 0)
				enic->rq_bad_fcs++;
			अन्यथा अगर (bytes_written == 0)
				enic->rq_truncated_pkts++;
		पूर्ण

		dma_unmap_single(&enic->pdev->dev, buf->dma_addr, buf->len,
				 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
		buf->os_buf = शून्य;

		वापस;
	पूर्ण

	अगर (eop && bytes_written > 0) अणु

		/* Good receive
		 */

		अगर (!enic_rxcopyअवरोध(netdev, &skb, buf, bytes_written)) अणु
			buf->os_buf = शून्य;
			dma_unmap_single(&enic->pdev->dev, buf->dma_addr,
					 buf->len, DMA_FROM_DEVICE);
		पूर्ण
		prefetch(skb->data - NET_IP_ALIGN);

		skb_put(skb, bytes_written);
		skb->protocol = eth_type_trans(skb, netdev);
		skb_record_rx_queue(skb, q_number);
		अगर ((netdev->features & NETIF_F_RXHASH) && rss_hash &&
		    (type == 3)) अणु
			चयन (rss_type) अणु
			हाल CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv4:
			हाल CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv6:
			हाल CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv6_EX:
				skb_set_hash(skb, rss_hash, PKT_HASH_TYPE_L4);
				अवरोध;
			हाल CQ_ENET_RQ_DESC_RSS_TYPE_IPv4:
			हाल CQ_ENET_RQ_DESC_RSS_TYPE_IPv6:
			हाल CQ_ENET_RQ_DESC_RSS_TYPE_IPv6_EX:
				skb_set_hash(skb, rss_hash, PKT_HASH_TYPE_L3);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (enic->vxlan.vxlan_udp_port_number) अणु
			चयन (enic->vxlan.patch_level) अणु
			हाल 0:
				अगर (fcoe) अणु
					encap = true;
					outer_csum_ok = fcoe_fc_crc_ok;
				पूर्ण
				अवरोध;
			हाल 2:
				अगर ((type == 7) &&
				    (rss_hash & BIT(0))) अणु
					encap = true;
					outer_csum_ok = (rss_hash & BIT(1)) &&
							(rss_hash & BIT(2));
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		/* Hardware करोes not provide whole packet checksum. It only
		 * provides pseuकरो checksum. Since hw validates the packet
		 * checksum but not provide us the checksum value. use
		 * CHECSUM_UNNECESSARY.
		 *
		 * In हाल of encap pkt tcp_udp_csum_ok/tcp_udp_csum_ok is
		 * inner csum_ok. outer_csum_ok is set by hw when outer udp
		 * csum is correct or is zero.
		 */
		अगर ((netdev->features & NETIF_F_RXCSUM) && !csum_not_calc &&
		    tcp_udp_csum_ok && outer_csum_ok &&
		    (ipv4_csum_ok || ipv6)) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			skb->csum_level = encap;
		पूर्ण

		अगर (vlan_stripped)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tci);

		skb_mark_napi_id(skb, &enic->napi[rq->index]);
		अगर (!(netdev->features & NETIF_F_GRO))
			netअगर_receive_skb(skb);
		अन्यथा
			napi_gro_receive(&enic->napi[q_number], skb);
		अगर (enic->rx_coalesce_setting.use_adaptive_rx_coalesce)
			enic_पूर्णांकr_update_pkt_size(&cq->pkt_size_counter,
						  bytes_written);
	पूर्ण अन्यथा अणु

		/* Buffer overflow
		 */

		dma_unmap_single(&enic->pdev->dev, buf->dma_addr, buf->len,
				 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
		buf->os_buf = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक enic_rq_service(काष्ठा vnic_dev *vdev, काष्ठा cq_desc *cq_desc,
	u8 type, u16 q_number, u16 completed_index, व्योम *opaque)
अणु
	काष्ठा enic *enic = vnic_dev_priv(vdev);

	vnic_rq_service(&enic->rq[q_number], cq_desc,
		completed_index, VNIC_RQ_RETURN_DESC,
		enic_rq_indicate_buf, opaque);

	वापस 0;
पूर्ण

अटल व्योम enic_set_पूर्णांक_moderation(काष्ठा enic *enic, काष्ठा vnic_rq *rq)
अणु
	अचिन्हित पूर्णांक पूर्णांकr = enic_msix_rq_पूर्णांकr(enic, rq->index);
	काष्ठा vnic_cq *cq = &enic->cq[enic_cq_rq(enic, rq->index)];
	u32 समयr = cq->tobe_rx_coal_समयval;

	अगर (cq->tobe_rx_coal_समयval != cq->cur_rx_coal_समयval) अणु
		vnic_पूर्णांकr_coalescing_समयr_set(&enic->पूर्णांकr[पूर्णांकr], समयr);
		cq->cur_rx_coal_समयval = cq->tobe_rx_coal_समयval;
	पूर्ण
पूर्ण

अटल व्योम enic_calc_पूर्णांक_moderation(काष्ठा enic *enic, काष्ठा vnic_rq *rq)
अणु
	काष्ठा enic_rx_coal *rx_coal = &enic->rx_coalesce_setting;
	काष्ठा vnic_cq *cq = &enic->cq[enic_cq_rq(enic, rq->index)];
	काष्ठा vnic_rx_bytes_counter *pkt_size_counter = &cq->pkt_size_counter;
	पूर्णांक index;
	u32 समयr;
	u32 range_start;
	u32 traffic;
	u64 delta;
	kसमय_प्रकार now = kसमय_get();

	delta = kसमय_us_delta(now, cq->prev_ts);
	अगर (delta < ENIC_AIC_TS_BREAK)
		वापस;
	cq->prev_ts = now;

	traffic = pkt_size_counter->large_pkt_bytes_cnt +
		  pkt_size_counter->small_pkt_bytes_cnt;
	/* The table takes Mbps
	 * traffic *= 8    => bits
	 * traffic *= (10^6 / delta)    => bps
	 * traffic /= 10^6     => Mbps
	 *
	 * Combining, traffic *= (8 / delta)
	 */

	traffic <<= 3;
	traffic = delta > अच_पूर्णांक_उच्च ? 0 : traffic / (u32)delta;

	क्रम (index = 0; index < ENIC_MAX_COALESCE_TIMERS; index++)
		अगर (traffic < mod_table[index].rx_rate)
			अवरोध;
	range_start = (pkt_size_counter->small_pkt_bytes_cnt >
		       pkt_size_counter->large_pkt_bytes_cnt << 1) ?
		      rx_coal->small_pkt_range_start :
		      rx_coal->large_pkt_range_start;
	समयr = range_start + ((rx_coal->range_end - range_start) *
			       mod_table[index].range_percent / 100);
	/* Damping */
	cq->tobe_rx_coal_समयval = (समयr + cq->tobe_rx_coal_समयval) >> 1;

	pkt_size_counter->large_pkt_bytes_cnt = 0;
	pkt_size_counter->small_pkt_bytes_cnt = 0;
पूर्ण

अटल पूर्णांक enic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा net_device *netdev = napi->dev;
	काष्ठा enic *enic = netdev_priv(netdev);
	अचिन्हित पूर्णांक cq_rq = enic_cq_rq(enic, 0);
	अचिन्हित पूर्णांक cq_wq = enic_cq_wq(enic, 0);
	अचिन्हित पूर्णांक पूर्णांकr = enic_legacy_io_पूर्णांकr();
	अचिन्हित पूर्णांक rq_work_to_करो = budget;
	अचिन्हित पूर्णांक wq_work_to_करो = ENIC_WQ_NAPI_BUDGET;
	अचिन्हित पूर्णांक  work_करोne, rq_work_करोne = 0, wq_work_करोne;
	पूर्णांक err;

	wq_work_करोne = vnic_cq_service(&enic->cq[cq_wq], wq_work_to_करो,
				       enic_wq_service, शून्य);

	अगर (budget > 0)
		rq_work_करोne = vnic_cq_service(&enic->cq[cq_rq],
			rq_work_to_करो, enic_rq_service, शून्य);

	/* Accumulate पूर्णांकr event credits क्रम this polling
	 * cycle.  An पूर्णांकr event is the completion of a
	 * a WQ or RQ packet.
	 */

	work_करोne = rq_work_करोne + wq_work_करोne;

	अगर (work_करोne > 0)
		vnic_पूर्णांकr_वापस_credits(&enic->पूर्णांकr[पूर्णांकr],
			work_करोne,
			0 /* करोn't unmask पूर्णांकr */,
			0 /* करोn't reset पूर्णांकr समयr */);

	err = vnic_rq_fill(&enic->rq[0], enic_rq_alloc_buf);

	/* Buffer allocation failed. Stay in polling
	 * mode so we can try to fill the ring again.
	 */

	अगर (err)
		rq_work_करोne = rq_work_to_करो;
	अगर (enic->rx_coalesce_setting.use_adaptive_rx_coalesce)
		/* Call the function which refreshes the पूर्णांकr coalescing समयr
		 * value based on the traffic.
		 */
		enic_calc_पूर्णांक_moderation(enic, &enic->rq[0]);

	अगर ((rq_work_करोne < budget) && napi_complete_करोne(napi, rq_work_करोne)) अणु

		/* Some work करोne, but not enough to stay in polling,
		 * निकास polling
		 */

		अगर (enic->rx_coalesce_setting.use_adaptive_rx_coalesce)
			enic_set_पूर्णांक_moderation(enic, &enic->rq[0]);
		vnic_पूर्णांकr_unmask(&enic->पूर्णांकr[पूर्णांकr]);
	पूर्ण

	वापस rq_work_करोne;
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
अटल व्योम enic_मुक्त_rx_cpu_rmap(काष्ठा enic *enic)
अणु
	मुक्त_irq_cpu_rmap(enic->netdev->rx_cpu_rmap);
	enic->netdev->rx_cpu_rmap = शून्य;
पूर्ण

अटल व्योम enic_set_rx_cpu_rmap(काष्ठा enic *enic)
अणु
	पूर्णांक i, res;

	अगर (vnic_dev_get_पूर्णांकr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX) अणु
		enic->netdev->rx_cpu_rmap = alloc_irq_cpu_rmap(enic->rq_count);
		अगर (unlikely(!enic->netdev->rx_cpu_rmap))
			वापस;
		क्रम (i = 0; i < enic->rq_count; i++) अणु
			res = irq_cpu_rmap_add(enic->netdev->rx_cpu_rmap,
					       enic->msix_entry[i].vector);
			अगर (unlikely(res)) अणु
				enic_मुक्त_rx_cpu_rmap(enic);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम enic_मुक्त_rx_cpu_rmap(काष्ठा enic *enic)
अणु
पूर्ण

अटल व्योम enic_set_rx_cpu_rmap(काष्ठा enic *enic)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

अटल पूर्णांक enic_poll_msix_wq(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा net_device *netdev = napi->dev;
	काष्ठा enic *enic = netdev_priv(netdev);
	अचिन्हित पूर्णांक wq_index = (napi - &enic->napi[0]) - enic->rq_count;
	काष्ठा vnic_wq *wq = &enic->wq[wq_index];
	अचिन्हित पूर्णांक cq;
	अचिन्हित पूर्णांक पूर्णांकr;
	अचिन्हित पूर्णांक wq_work_to_करो = ENIC_WQ_NAPI_BUDGET;
	अचिन्हित पूर्णांक wq_work_करोne;
	अचिन्हित पूर्णांक wq_irq;

	wq_irq = wq->index;
	cq = enic_cq_wq(enic, wq_irq);
	पूर्णांकr = enic_msix_wq_पूर्णांकr(enic, wq_irq);
	wq_work_करोne = vnic_cq_service(&enic->cq[cq], wq_work_to_करो,
				       enic_wq_service, शून्य);

	vnic_पूर्णांकr_वापस_credits(&enic->पूर्णांकr[पूर्णांकr], wq_work_करोne,
				 0 /* करोn't unmask पूर्णांकr */,
				 1 /* reset पूर्णांकr समयr */);
	अगर (!wq_work_करोne) अणु
		napi_complete(napi);
		vnic_पूर्णांकr_unmask(&enic->पूर्णांकr[पूर्णांकr]);
		वापस 0;
	पूर्ण

	वापस budget;
पूर्ण

अटल पूर्णांक enic_poll_msix_rq(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा net_device *netdev = napi->dev;
	काष्ठा enic *enic = netdev_priv(netdev);
	अचिन्हित पूर्णांक rq = (napi - &enic->napi[0]);
	अचिन्हित पूर्णांक cq = enic_cq_rq(enic, rq);
	अचिन्हित पूर्णांक पूर्णांकr = enic_msix_rq_पूर्णांकr(enic, rq);
	अचिन्हित पूर्णांक work_to_करो = budget;
	अचिन्हित पूर्णांक work_करोne = 0;
	पूर्णांक err;

	/* Service RQ
	 */

	अगर (budget > 0)
		work_करोne = vnic_cq_service(&enic->cq[cq],
			work_to_करो, enic_rq_service, शून्य);

	/* Return पूर्णांकr event credits क्रम this polling
	 * cycle.  An पूर्णांकr event is the completion of a
	 * RQ packet.
	 */

	अगर (work_करोne > 0)
		vnic_पूर्णांकr_वापस_credits(&enic->पूर्णांकr[पूर्णांकr],
			work_करोne,
			0 /* करोn't unmask पूर्णांकr */,
			0 /* करोn't reset पूर्णांकr समयr */);

	err = vnic_rq_fill(&enic->rq[rq], enic_rq_alloc_buf);

	/* Buffer allocation failed. Stay in polling mode
	 * so we can try to fill the ring again.
	 */

	अगर (err)
		work_करोne = work_to_करो;
	अगर (enic->rx_coalesce_setting.use_adaptive_rx_coalesce)
		/* Call the function which refreshes the पूर्णांकr coalescing समयr
		 * value based on the traffic.
		 */
		enic_calc_पूर्णांक_moderation(enic, &enic->rq[rq]);

	अगर ((work_करोne < budget) && napi_complete_करोne(napi, work_करोne)) अणु

		/* Some work करोne, but not enough to stay in polling,
		 * निकास polling
		 */

		अगर (enic->rx_coalesce_setting.use_adaptive_rx_coalesce)
			enic_set_पूर्णांक_moderation(enic, &enic->rq[rq]);
		vnic_पूर्णांकr_unmask(&enic->पूर्णांकr[पूर्णांकr]);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल व्योम enic_notअगरy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा enic *enic = from_समयr(enic, t, notअगरy_समयr);

	enic_notअगरy_check(enic);

	mod_समयr(&enic->notअगरy_समयr,
		round_jअगरfies(jअगरfies + ENIC_NOTIFY_TIMER_PERIOD));
पूर्ण

अटल व्योम enic_मुक्त_पूर्णांकr(काष्ठा enic *enic)
अणु
	काष्ठा net_device *netdev = enic->netdev;
	अचिन्हित पूर्णांक i;

	enic_मुक्त_rx_cpu_rmap(enic);
	चयन (vnic_dev_get_पूर्णांकr_mode(enic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_INTX:
		मुक्त_irq(enic->pdev->irq, netdev);
		अवरोध;
	हाल VNIC_DEV_INTR_MODE_MSI:
		मुक्त_irq(enic->pdev->irq, enic);
		अवरोध;
	हाल VNIC_DEV_INTR_MODE_MSIX:
		क्रम (i = 0; i < ARRAY_SIZE(enic->msix); i++)
			अगर (enic->msix[i].requested)
				मुक्त_irq(enic->msix_entry[i].vector,
					enic->msix[i].devid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक enic_request_पूर्णांकr(काष्ठा enic *enic)
अणु
	काष्ठा net_device *netdev = enic->netdev;
	अचिन्हित पूर्णांक i, पूर्णांकr;
	पूर्णांक err = 0;

	enic_set_rx_cpu_rmap(enic);
	चयन (vnic_dev_get_पूर्णांकr_mode(enic->vdev)) अणु

	हाल VNIC_DEV_INTR_MODE_INTX:

		err = request_irq(enic->pdev->irq, enic_isr_legacy,
			IRQF_SHARED, netdev->name, netdev);
		अवरोध;

	हाल VNIC_DEV_INTR_MODE_MSI:

		err = request_irq(enic->pdev->irq, enic_isr_msi,
			0, netdev->name, enic);
		अवरोध;

	हाल VNIC_DEV_INTR_MODE_MSIX:

		क्रम (i = 0; i < enic->rq_count; i++) अणु
			पूर्णांकr = enic_msix_rq_पूर्णांकr(enic, i);
			snम_लिखो(enic->msix[पूर्णांकr].devname,
				माप(enic->msix[पूर्णांकr].devname),
				"%s-rx-%u", netdev->name, i);
			enic->msix[पूर्णांकr].isr = enic_isr_msix;
			enic->msix[पूर्णांकr].devid = &enic->napi[i];
		पूर्ण

		क्रम (i = 0; i < enic->wq_count; i++) अणु
			पूर्णांक wq = enic_cq_wq(enic, i);

			पूर्णांकr = enic_msix_wq_पूर्णांकr(enic, i);
			snम_लिखो(enic->msix[पूर्णांकr].devname,
				माप(enic->msix[पूर्णांकr].devname),
				"%s-tx-%u", netdev->name, i);
			enic->msix[पूर्णांकr].isr = enic_isr_msix;
			enic->msix[पूर्णांकr].devid = &enic->napi[wq];
		पूर्ण

		पूर्णांकr = enic_msix_err_पूर्णांकr(enic);
		snम_लिखो(enic->msix[पूर्णांकr].devname,
			माप(enic->msix[पूर्णांकr].devname),
			"%s-err", netdev->name);
		enic->msix[पूर्णांकr].isr = enic_isr_msix_err;
		enic->msix[पूर्णांकr].devid = enic;

		पूर्णांकr = enic_msix_notअगरy_पूर्णांकr(enic);
		snम_लिखो(enic->msix[पूर्णांकr].devname,
			माप(enic->msix[पूर्णांकr].devname),
			"%s-notify", netdev->name);
		enic->msix[पूर्णांकr].isr = enic_isr_msix_notअगरy;
		enic->msix[पूर्णांकr].devid = enic;

		क्रम (i = 0; i < ARRAY_SIZE(enic->msix); i++)
			enic->msix[i].requested = 0;

		क्रम (i = 0; i < enic->पूर्णांकr_count; i++) अणु
			err = request_irq(enic->msix_entry[i].vector,
				enic->msix[i].isr, 0,
				enic->msix[i].devname,
				enic->msix[i].devid);
			अगर (err) अणु
				enic_मुक्त_पूर्णांकr(enic);
				अवरोध;
			पूर्ण
			enic->msix[i].requested = 1;
		पूर्ण

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम enic_synchronize_irqs(काष्ठा enic *enic)
अणु
	अचिन्हित पूर्णांक i;

	चयन (vnic_dev_get_पूर्णांकr_mode(enic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_INTX:
	हाल VNIC_DEV_INTR_MODE_MSI:
		synchronize_irq(enic->pdev->irq);
		अवरोध;
	हाल VNIC_DEV_INTR_MODE_MSIX:
		क्रम (i = 0; i < enic->पूर्णांकr_count; i++)
			synchronize_irq(enic->msix_entry[i].vector);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम enic_set_rx_coal_setting(काष्ठा enic *enic)
अणु
	अचिन्हित पूर्णांक speed;
	पूर्णांक index = -1;
	काष्ठा enic_rx_coal *rx_coal = &enic->rx_coalesce_setting;

	/* 1. Read the link speed from fw
	 * 2. Pick the शेष range क्रम the speed
	 * 3. Update it in enic->rx_coalesce_setting
	 */
	speed = vnic_dev_port_speed(enic->vdev);
	अगर (ENIC_LINK_SPEED_10G < speed)
		index = ENIC_LINK_40G_INDEX;
	अन्यथा अगर (ENIC_LINK_SPEED_4G < speed)
		index = ENIC_LINK_10G_INDEX;
	अन्यथा
		index = ENIC_LINK_4G_INDEX;

	rx_coal->small_pkt_range_start = mod_range[index].small_pkt_range_start;
	rx_coal->large_pkt_range_start = mod_range[index].large_pkt_range_start;
	rx_coal->range_end = ENIC_RX_COALESCE_RANGE_END;

	/* Start with the value provided by UCSM */
	क्रम (index = 0; index < enic->rq_count; index++)
		enic->cq[index].cur_rx_coal_समयval =
				enic->config.पूर्णांकr_समयr_usec;

	rx_coal->use_adaptive_rx_coalesce = 1;
पूर्ण

अटल पूर्णांक enic_dev_notअगरy_set(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	spin_lock_bh(&enic->devcmd_lock);
	चयन (vnic_dev_get_पूर्णांकr_mode(enic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_INTX:
		err = vnic_dev_notअगरy_set(enic->vdev,
			enic_legacy_notअगरy_पूर्णांकr());
		अवरोध;
	हाल VNIC_DEV_INTR_MODE_MSIX:
		err = vnic_dev_notअगरy_set(enic->vdev,
			enic_msix_notअगरy_पूर्णांकr(enic));
		अवरोध;
	शेष:
		err = vnic_dev_notअगरy_set(enic->vdev, -1 /* no पूर्णांकr */);
		अवरोध;
	पूर्ण
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

अटल व्योम enic_notअगरy_समयr_start(काष्ठा enic *enic)
अणु
	चयन (vnic_dev_get_पूर्णांकr_mode(enic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_MSI:
		mod_समयr(&enic->notअगरy_समयr, jअगरfies);
		अवरोध;
	शेष:
		/* Using पूर्णांकr क्रम notअगरication क्रम INTx/MSI-X */
		अवरोध;
	पूर्ण
पूर्ण

/* rtnl lock is held, process context */
अटल पूर्णांक enic_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	अचिन्हित पूर्णांक i;
	पूर्णांक err, ret;

	err = enic_request_पूर्णांकr(enic);
	अगर (err) अणु
		netdev_err(netdev, "Unable to request irq.\n");
		वापस err;
	पूर्ण
	enic_init_affinity_hपूर्णांक(enic);
	enic_set_affinity_hपूर्णांक(enic);

	err = enic_dev_notअगरy_set(enic);
	अगर (err) अणु
		netdev_err(netdev,
			"Failed to alloc notify buffer, aborting.\n");
		जाओ err_out_मुक्त_पूर्णांकr;
	पूर्ण

	क्रम (i = 0; i < enic->rq_count; i++) अणु
		/* enable rq beक्रमe updating rq desc */
		vnic_rq_enable(&enic->rq[i]);
		vnic_rq_fill(&enic->rq[i], enic_rq_alloc_buf);
		/* Need at least one buffer on ring to get going */
		अगर (vnic_rq_desc_used(&enic->rq[i]) == 0) अणु
			netdev_err(netdev, "Unable to alloc receive buffers\n");
			err = -ENOMEM;
			जाओ err_out_मुक्त_rq;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < enic->wq_count; i++)
		vnic_wq_enable(&enic->wq[i]);

	अगर (!enic_is_dynamic(enic) && !enic_is_sriov_vf(enic))
		enic_dev_add_station_addr(enic);

	enic_set_rx_mode(netdev);

	netअगर_tx_wake_all_queues(netdev);

	क्रम (i = 0; i < enic->rq_count; i++)
		napi_enable(&enic->napi[i]);

	अगर (vnic_dev_get_पूर्णांकr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX)
		क्रम (i = 0; i < enic->wq_count; i++)
			napi_enable(&enic->napi[enic_cq_wq(enic, i)]);
	enic_dev_enable(enic);

	क्रम (i = 0; i < enic->पूर्णांकr_count; i++)
		vnic_पूर्णांकr_unmask(&enic->पूर्णांकr[i]);

	enic_notअगरy_समयr_start(enic);
	enic_rfs_समयr_start(enic);

	वापस 0;

err_out_मुक्त_rq:
	क्रम (i = 0; i < enic->rq_count; i++) अणु
		ret = vnic_rq_disable(&enic->rq[i]);
		अगर (!ret)
			vnic_rq_clean(&enic->rq[i], enic_मुक्त_rq_buf);
	पूर्ण
	enic_dev_notअगरy_unset(enic);
err_out_मुक्त_पूर्णांकr:
	enic_unset_affinity_hपूर्णांक(enic);
	enic_मुक्त_पूर्णांकr(enic);

	वापस err;
पूर्ण

/* rtnl lock is held, process context */
अटल पूर्णांक enic_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < enic->पूर्णांकr_count; i++) अणु
		vnic_पूर्णांकr_mask(&enic->पूर्णांकr[i]);
		(व्योम)vnic_पूर्णांकr_masked(&enic->पूर्णांकr[i]); /* flush ग_लिखो */
	पूर्ण

	enic_synchronize_irqs(enic);

	del_समयr_sync(&enic->notअगरy_समयr);
	enic_rfs_flw_tbl_मुक्त(enic);

	enic_dev_disable(enic);

	क्रम (i = 0; i < enic->rq_count; i++)
		napi_disable(&enic->napi[i]);

	netअगर_carrier_off(netdev);
	अगर (vnic_dev_get_पूर्णांकr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX)
		क्रम (i = 0; i < enic->wq_count; i++)
			napi_disable(&enic->napi[enic_cq_wq(enic, i)]);
	netअगर_tx_disable(netdev);

	अगर (!enic_is_dynamic(enic) && !enic_is_sriov_vf(enic))
		enic_dev_del_station_addr(enic);

	क्रम (i = 0; i < enic->wq_count; i++) अणु
		err = vnic_wq_disable(&enic->wq[i]);
		अगर (err)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < enic->rq_count; i++) अणु
		err = vnic_rq_disable(&enic->rq[i]);
		अगर (err)
			वापस err;
	पूर्ण

	enic_dev_notअगरy_unset(enic);
	enic_unset_affinity_hपूर्णांक(enic);
	enic_मुक्त_पूर्णांकr(enic);

	क्रम (i = 0; i < enic->wq_count; i++)
		vnic_wq_clean(&enic->wq[i], enic_मुक्त_wq_buf);
	क्रम (i = 0; i < enic->rq_count; i++)
		vnic_rq_clean(&enic->rq[i], enic_मुक्त_rq_buf);
	क्रम (i = 0; i < enic->cq_count; i++)
		vnic_cq_clean(&enic->cq[i]);
	क्रम (i = 0; i < enic->पूर्णांकr_count; i++)
		vnic_पूर्णांकr_clean(&enic->पूर्णांकr[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक _enic_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	bool running = netअगर_running(netdev);
	पूर्णांक err = 0;

	ASSERT_RTNL();
	अगर (running) अणु
		err = enic_stop(netdev);
		अगर (err)
			वापस err;
	पूर्ण

	netdev->mtu = new_mtu;

	अगर (running) अणु
		err = enic_खोलो(netdev);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enic_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);

	अगर (enic_is_dynamic(enic) || enic_is_sriov_vf(enic))
		वापस -EOPNOTSUPP;

	अगर (netdev->mtu > enic->port_mtu)
		netdev_warn(netdev,
			    "interface MTU (%d) set higher than port MTU (%d)\n",
			    netdev->mtu, enic->port_mtu);

	वापस _enic_change_mtu(netdev, new_mtu);
पूर्ण

अटल व्योम enic_change_mtu_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा enic *enic = container_of(work, काष्ठा enic, change_mtu_work);
	काष्ठा net_device *netdev = enic->netdev;
	पूर्णांक new_mtu = vnic_dev_mtu(enic->vdev);

	rtnl_lock();
	(व्योम)_enic_change_mtu(netdev, new_mtu);
	rtnl_unlock();

	netdev_info(netdev, "interface MTU set as %d\n", netdev->mtu);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम enic_poll_controller(काष्ठा net_device *netdev)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा vnic_dev *vdev = enic->vdev;
	अचिन्हित पूर्णांक i, पूर्णांकr;

	चयन (vnic_dev_get_पूर्णांकr_mode(vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_MSIX:
		क्रम (i = 0; i < enic->rq_count; i++) अणु
			पूर्णांकr = enic_msix_rq_पूर्णांकr(enic, i);
			enic_isr_msix(enic->msix_entry[पूर्णांकr].vector,
				      &enic->napi[i]);
		पूर्ण

		क्रम (i = 0; i < enic->wq_count; i++) अणु
			पूर्णांकr = enic_msix_wq_पूर्णांकr(enic, i);
			enic_isr_msix(enic->msix_entry[पूर्णांकr].vector,
				      &enic->napi[enic_cq_wq(enic, i)]);
		पूर्ण

		अवरोध;
	हाल VNIC_DEV_INTR_MODE_MSI:
		enic_isr_msi(enic->pdev->irq, enic);
		अवरोध;
	हाल VNIC_DEV_INTR_MODE_INTX:
		enic_isr_legacy(enic->pdev->irq, netdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक enic_dev_रुको(काष्ठा vnic_dev *vdev,
	पूर्णांक (*start)(काष्ठा vnic_dev *, पूर्णांक),
	पूर्णांक (*finished)(काष्ठा vnic_dev *, पूर्णांक *),
	पूर्णांक arg)
अणु
	अचिन्हित दीर्घ समय;
	पूर्णांक करोne;
	पूर्णांक err;

	err = start(vdev, arg);
	अगर (err)
		वापस err;

	/* Wait क्रम func to complete...2 seconds max
	 */

	समय = jअगरfies + (HZ * 2);
	करो अणु

		err = finished(vdev, &करोne);
		अगर (err)
			वापस err;

		अगर (करोne)
			वापस 0;

		schedule_समयout_unपूर्णांकerruptible(HZ / 10);

	पूर्ण जबतक (समय_after(समय, jअगरfies));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक enic_dev_खोलो(काष्ठा enic *enic)
अणु
	पूर्णांक err;
	u32 flags = CMD_OPENF_IG_DESCCACHE;

	err = enic_dev_रुको(enic->vdev, vnic_dev_खोलो,
		vnic_dev_खोलो_करोne, flags);
	अगर (err)
		dev_err(enic_get_dev(enic), "vNIC device open failed, err %d\n",
			err);

	वापस err;
पूर्ण

अटल पूर्णांक enic_dev_soft_reset(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	err = enic_dev_रुको(enic->vdev, vnic_dev_soft_reset,
			    vnic_dev_soft_reset_करोne, 0);
	अगर (err)
		netdev_err(enic->netdev, "vNIC soft reset failed, err %d\n",
			   err);

	वापस err;
पूर्ण

अटल पूर्णांक enic_dev_hang_reset(काष्ठा enic *enic)
अणु
	पूर्णांक err;

	err = enic_dev_रुको(enic->vdev, vnic_dev_hang_reset,
		vnic_dev_hang_reset_करोne, 0);
	अगर (err)
		netdev_err(enic->netdev, "vNIC hang reset failed, err %d\n",
			err);

	वापस err;
पूर्ण

पूर्णांक __enic_set_rsskey(काष्ठा enic *enic)
अणु
	जोड़ vnic_rss_key *rss_key_buf_va;
	dma_addr_t rss_key_buf_pa;
	पूर्णांक i, kidx, bidx, err;

	rss_key_buf_va = dma_alloc_coherent(&enic->pdev->dev,
					    माप(जोड़ vnic_rss_key),
					    &rss_key_buf_pa, GFP_ATOMIC);
	अगर (!rss_key_buf_va)
		वापस -ENOMEM;

	क्रम (i = 0; i < ENIC_RSS_LEN; i++) अणु
		kidx = i / ENIC_RSS_BYTES_PER_KEY;
		bidx = i % ENIC_RSS_BYTES_PER_KEY;
		rss_key_buf_va->key[kidx].b[bidx] = enic->rss_key[i];
	पूर्ण
	spin_lock_bh(&enic->devcmd_lock);
	err = enic_set_rss_key(enic,
		rss_key_buf_pa,
		माप(जोड़ vnic_rss_key));
	spin_unlock_bh(&enic->devcmd_lock);

	dma_मुक्त_coherent(&enic->pdev->dev, माप(जोड़ vnic_rss_key),
			  rss_key_buf_va, rss_key_buf_pa);

	वापस err;
पूर्ण

अटल पूर्णांक enic_set_rsskey(काष्ठा enic *enic)
अणु
	netdev_rss_key_fill(enic->rss_key, ENIC_RSS_LEN);

	वापस __enic_set_rsskey(enic);
पूर्ण

अटल पूर्णांक enic_set_rsscpu(काष्ठा enic *enic, u8 rss_hash_bits)
अणु
	dma_addr_t rss_cpu_buf_pa;
	जोड़ vnic_rss_cpu *rss_cpu_buf_va = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	rss_cpu_buf_va = dma_alloc_coherent(&enic->pdev->dev,
					    माप(जोड़ vnic_rss_cpu),
					    &rss_cpu_buf_pa, GFP_ATOMIC);
	अगर (!rss_cpu_buf_va)
		वापस -ENOMEM;

	क्रम (i = 0; i < (1 << rss_hash_bits); i++)
		(*rss_cpu_buf_va).cpu[i/4].b[i%4] = i % enic->rq_count;

	spin_lock_bh(&enic->devcmd_lock);
	err = enic_set_rss_cpu(enic,
		rss_cpu_buf_pa,
		माप(जोड़ vnic_rss_cpu));
	spin_unlock_bh(&enic->devcmd_lock);

	dma_मुक्त_coherent(&enic->pdev->dev, माप(जोड़ vnic_rss_cpu),
			  rss_cpu_buf_va, rss_cpu_buf_pa);

	वापस err;
पूर्ण

अटल पूर्णांक enic_set_niccfg(काष्ठा enic *enic, u8 rss_शेष_cpu,
	u8 rss_hash_type, u8 rss_hash_bits, u8 rss_base_cpu, u8 rss_enable)
अणु
	स्थिर u8 tso_ipid_split_en = 0;
	स्थिर u8 ig_vlan_strip_en = 1;
	पूर्णांक err;

	/* Enable VLAN tag stripping.
	*/

	spin_lock_bh(&enic->devcmd_lock);
	err = enic_set_nic_cfg(enic,
		rss_शेष_cpu, rss_hash_type,
		rss_hash_bits, rss_base_cpu,
		rss_enable, tso_ipid_split_en,
		ig_vlan_strip_en);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस err;
पूर्ण

अटल पूर्णांक enic_set_rss_nic_cfg(काष्ठा enic *enic)
अणु
	काष्ठा device *dev = enic_get_dev(enic);
	स्थिर u8 rss_शेष_cpu = 0;
	स्थिर u8 rss_hash_bits = 7;
	स्थिर u8 rss_base_cpu = 0;
	u8 rss_hash_type;
	पूर्णांक res;
	u8 rss_enable = ENIC_SETTING(enic, RSS) && (enic->rq_count > 1);

	spin_lock_bh(&enic->devcmd_lock);
	res = vnic_dev_capable_rss_hash_type(enic->vdev, &rss_hash_type);
	spin_unlock_bh(&enic->devcmd_lock);
	अगर (res) अणु
		/* शेषs क्रम old adapters
		 */
		rss_hash_type = NIC_CFG_RSS_HASH_TYPE_IPV4	|
				NIC_CFG_RSS_HASH_TYPE_TCP_IPV4	|
				NIC_CFG_RSS_HASH_TYPE_IPV6	|
				NIC_CFG_RSS_HASH_TYPE_TCP_IPV6;
	पूर्ण

	अगर (rss_enable) अणु
		अगर (!enic_set_rsskey(enic)) अणु
			अगर (enic_set_rsscpu(enic, rss_hash_bits)) अणु
				rss_enable = 0;
				dev_warn(dev, "RSS disabled, "
					"Failed to set RSS cpu indirection table.");
			पूर्ण
		पूर्ण अन्यथा अणु
			rss_enable = 0;
			dev_warn(dev, "RSS disabled, Failed to set RSS key.\n");
		पूर्ण
	पूर्ण

	वापस enic_set_niccfg(enic, rss_शेष_cpu, rss_hash_type,
		rss_hash_bits, rss_base_cpu, rss_enable);
पूर्ण

अटल व्योम enic_set_api_busy(काष्ठा enic *enic, bool busy)
अणु
	spin_lock(&enic->enic_api_lock);
	enic->enic_api_busy = busy;
	spin_unlock(&enic->enic_api_lock);
पूर्ण

अटल व्योम enic_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा enic *enic = container_of(work, काष्ठा enic, reset);

	अगर (!netअगर_running(enic->netdev))
		वापस;

	rtnl_lock();

	/* Stop any activity from infiniband */
	enic_set_api_busy(enic, true);

	enic_stop(enic->netdev);
	enic_dev_soft_reset(enic);
	enic_reset_addr_lists(enic);
	enic_init_vnic_resources(enic);
	enic_set_rss_nic_cfg(enic);
	enic_dev_set_ig_vlan_reग_लिखो_mode(enic);
	enic_खोलो(enic->netdev);

	/* Allow infiniband to fiddle with the device again */
	enic_set_api_busy(enic, false);

	call_netdevice_notअगरiers(NETDEV_REBOOT, enic->netdev);

	rtnl_unlock();
पूर्ण

अटल व्योम enic_tx_hang_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा enic *enic = container_of(work, काष्ठा enic, tx_hang_reset);

	rtnl_lock();

	/* Stop any activity from infiniband */
	enic_set_api_busy(enic, true);

	enic_dev_hang_notअगरy(enic);
	enic_stop(enic->netdev);
	enic_dev_hang_reset(enic);
	enic_reset_addr_lists(enic);
	enic_init_vnic_resources(enic);
	enic_set_rss_nic_cfg(enic);
	enic_dev_set_ig_vlan_reग_लिखो_mode(enic);
	enic_खोलो(enic->netdev);

	/* Allow infiniband to fiddle with the device again */
	enic_set_api_busy(enic, false);

	call_netdevice_notअगरiers(NETDEV_REBOOT, enic->netdev);

	rtnl_unlock();
पूर्ण

अटल पूर्णांक enic_set_पूर्णांकr_mode(काष्ठा enic *enic)
अणु
	अचिन्हित पूर्णांक n = min_t(अचिन्हित पूर्णांक, enic->rq_count, ENIC_RQ_MAX);
	अचिन्हित पूर्णांक m = min_t(अचिन्हित पूर्णांक, enic->wq_count, ENIC_WQ_MAX);
	अचिन्हित पूर्णांक i;

	/* Set पूर्णांकerrupt mode (INTx, MSI, MSI-X) depending
	 * on प्रणाली capabilities.
	 *
	 * Try MSI-X first
	 *
	 * We need n RQs, m WQs, n+m CQs, and n+m+2 INTRs
	 * (the second to last INTR is used क्रम WQ/RQ errors)
	 * (the last INTR is used क्रम notअगरications)
	 */

	BUG_ON(ARRAY_SIZE(enic->msix_entry) < n + m + 2);
	क्रम (i = 0; i < n + m + 2; i++)
		enic->msix_entry[i].entry = i;

	/* Use multiple RQs अगर RSS is enabled
	 */

	अगर (ENIC_SETTING(enic, RSS) &&
	    enic->config.पूर्णांकr_mode < 1 &&
	    enic->rq_count >= n &&
	    enic->wq_count >= m &&
	    enic->cq_count >= n + m &&
	    enic->पूर्णांकr_count >= n + m + 2) अणु

		अगर (pci_enable_msix_range(enic->pdev, enic->msix_entry,
					  n + m + 2, n + m + 2) > 0) अणु

			enic->rq_count = n;
			enic->wq_count = m;
			enic->cq_count = n + m;
			enic->पूर्णांकr_count = n + m + 2;

			vnic_dev_set_पूर्णांकr_mode(enic->vdev,
				VNIC_DEV_INTR_MODE_MSIX);

			वापस 0;
		पूर्ण
	पूर्ण

	अगर (enic->config.पूर्णांकr_mode < 1 &&
	    enic->rq_count >= 1 &&
	    enic->wq_count >= m &&
	    enic->cq_count >= 1 + m &&
	    enic->पूर्णांकr_count >= 1 + m + 2) अणु
		अगर (pci_enable_msix_range(enic->pdev, enic->msix_entry,
					  1 + m + 2, 1 + m + 2) > 0) अणु

			enic->rq_count = 1;
			enic->wq_count = m;
			enic->cq_count = 1 + m;
			enic->पूर्णांकr_count = 1 + m + 2;

			vnic_dev_set_पूर्णांकr_mode(enic->vdev,
				VNIC_DEV_INTR_MODE_MSIX);

			वापस 0;
		पूर्ण
	पूर्ण

	/* Next try MSI
	 *
	 * We need 1 RQ, 1 WQ, 2 CQs, and 1 INTR
	 */

	अगर (enic->config.पूर्णांकr_mode < 2 &&
	    enic->rq_count >= 1 &&
	    enic->wq_count >= 1 &&
	    enic->cq_count >= 2 &&
	    enic->पूर्णांकr_count >= 1 &&
	    !pci_enable_msi(enic->pdev)) अणु

		enic->rq_count = 1;
		enic->wq_count = 1;
		enic->cq_count = 2;
		enic->पूर्णांकr_count = 1;

		vnic_dev_set_पूर्णांकr_mode(enic->vdev, VNIC_DEV_INTR_MODE_MSI);

		वापस 0;
	पूर्ण

	/* Next try INTx
	 *
	 * We need 1 RQ, 1 WQ, 2 CQs, and 3 INTRs
	 * (the first INTR is used क्रम WQ/RQ)
	 * (the second INTR is used क्रम WQ/RQ errors)
	 * (the last INTR is used क्रम notअगरications)
	 */

	अगर (enic->config.पूर्णांकr_mode < 3 &&
	    enic->rq_count >= 1 &&
	    enic->wq_count >= 1 &&
	    enic->cq_count >= 2 &&
	    enic->पूर्णांकr_count >= 3) अणु

		enic->rq_count = 1;
		enic->wq_count = 1;
		enic->cq_count = 2;
		enic->पूर्णांकr_count = 3;

		vnic_dev_set_पूर्णांकr_mode(enic->vdev, VNIC_DEV_INTR_MODE_INTX);

		वापस 0;
	पूर्ण

	vnic_dev_set_पूर्णांकr_mode(enic->vdev, VNIC_DEV_INTR_MODE_UNKNOWN);

	वापस -EINVAL;
पूर्ण

अटल व्योम enic_clear_पूर्णांकr_mode(काष्ठा enic *enic)
अणु
	चयन (vnic_dev_get_पूर्णांकr_mode(enic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_MSIX:
		pci_disable_msix(enic->pdev);
		अवरोध;
	हाल VNIC_DEV_INTR_MODE_MSI:
		pci_disable_msi(enic->pdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	vnic_dev_set_पूर्णांकr_mode(enic->vdev, VNIC_DEV_INTR_MODE_UNKNOWN);
पूर्ण

अटल स्थिर काष्ठा net_device_ops enic_netdev_dynamic_ops = अणु
	.nकरो_खोलो		= enic_खोलो,
	.nकरो_stop		= enic_stop,
	.nकरो_start_xmit		= enic_hard_start_xmit,
	.nकरो_get_stats64	= enic_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= enic_set_rx_mode,
	.nकरो_set_mac_address	= enic_set_mac_address_dynamic,
	.nकरो_change_mtu		= enic_change_mtu,
	.nकरो_vlan_rx_add_vid	= enic_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= enic_vlan_rx_समाप्त_vid,
	.nकरो_tx_समयout		= enic_tx_समयout,
	.nकरो_set_vf_port	= enic_set_vf_port,
	.nकरो_get_vf_port	= enic_get_vf_port,
	.nकरो_set_vf_mac		= enic_set_vf_mac,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= enic_poll_controller,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer	= enic_rx_flow_steer,
#पूर्ण_अगर
	.nकरो_features_check	= enic_features_check,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops enic_netdev_ops = अणु
	.nकरो_खोलो		= enic_खोलो,
	.nकरो_stop		= enic_stop,
	.nकरो_start_xmit		= enic_hard_start_xmit,
	.nकरो_get_stats64	= enic_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= enic_set_mac_address,
	.nकरो_set_rx_mode	= enic_set_rx_mode,
	.nकरो_change_mtu		= enic_change_mtu,
	.nकरो_vlan_rx_add_vid	= enic_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= enic_vlan_rx_समाप्त_vid,
	.nकरो_tx_समयout		= enic_tx_समयout,
	.nकरो_set_vf_port	= enic_set_vf_port,
	.nकरो_get_vf_port	= enic_get_vf_port,
	.nकरो_set_vf_mac		= enic_set_vf_mac,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= enic_poll_controller,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer	= enic_rx_flow_steer,
#पूर्ण_अगर
	.nकरो_features_check	= enic_features_check,
पूर्ण;

अटल व्योम enic_dev_deinit(काष्ठा enic *enic)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < enic->rq_count; i++)
		__netअगर_napi_del(&enic->napi[i]);

	अगर (vnic_dev_get_पूर्णांकr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX)
		क्रम (i = 0; i < enic->wq_count; i++)
			__netअगर_napi_del(&enic->napi[enic_cq_wq(enic, i)]);

	/* observe RCU grace period after __netअगर_napi_del() calls */
	synchronize_net();

	enic_मुक्त_vnic_resources(enic);
	enic_clear_पूर्णांकr_mode(enic);
	enic_मुक्त_affinity_hपूर्णांक(enic);
पूर्ण

अटल व्योम enic_kdump_kernel_config(काष्ठा enic *enic)
अणु
	अगर (is_kdump_kernel()) अणु
		dev_info(enic_get_dev(enic), "Running from within kdump kernel. Using minimal resources\n");
		enic->rq_count = 1;
		enic->wq_count = 1;
		enic->config.rq_desc_count = ENIC_MIN_RQ_DESCS;
		enic->config.wq_desc_count = ENIC_MIN_WQ_DESCS;
		enic->config.mtu = min_t(u16, 1500, enic->config.mtu);
	पूर्ण
पूर्ण

अटल पूर्णांक enic_dev_init(काष्ठा enic *enic)
अणु
	काष्ठा device *dev = enic_get_dev(enic);
	काष्ठा net_device *netdev = enic->netdev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/* Get पूर्णांकerrupt coalesce समयr info */
	err = enic_dev_पूर्णांकr_coal_समयr_info(enic);
	अगर (err) अणु
		dev_warn(dev, "Using default conversion factor for "
			"interrupt coalesce timer\n");
		vnic_dev_पूर्णांकr_coal_समयr_info_शेष(enic->vdev);
	पूर्ण

	/* Get vNIC configuration
	 */

	err = enic_get_vnic_config(enic);
	अगर (err) अणु
		dev_err(dev, "Get vNIC configuration failed, aborting\n");
		वापस err;
	पूर्ण

	/* Get available resource counts
	 */

	enic_get_res_counts(enic);

	/* modअगरy resource count अगर we are in kdump_kernel
	 */
	enic_kdump_kernel_config(enic);

	/* Set पूर्णांकerrupt mode based on resource counts and प्रणाली
	 * capabilities
	 */

	err = enic_set_पूर्णांकr_mode(enic);
	अगर (err) अणु
		dev_err(dev, "Failed to set intr mode based on resource "
			"counts and system capabilities, aborting\n");
		वापस err;
	पूर्ण

	/* Allocate and configure vNIC resources
	 */

	err = enic_alloc_vnic_resources(enic);
	अगर (err) अणु
		dev_err(dev, "Failed to alloc vNIC resources, aborting\n");
		जाओ err_out_मुक्त_vnic_resources;
	पूर्ण

	enic_init_vnic_resources(enic);

	err = enic_set_rss_nic_cfg(enic);
	अगर (err) अणु
		dev_err(dev, "Failed to config nic, aborting\n");
		जाओ err_out_मुक्त_vnic_resources;
	पूर्ण

	चयन (vnic_dev_get_पूर्णांकr_mode(enic->vdev)) अणु
	शेष:
		netअगर_napi_add(netdev, &enic->napi[0], enic_poll, 64);
		अवरोध;
	हाल VNIC_DEV_INTR_MODE_MSIX:
		क्रम (i = 0; i < enic->rq_count; i++) अणु
			netअगर_napi_add(netdev, &enic->napi[i],
				enic_poll_msix_rq, NAPI_POLL_WEIGHT);
		पूर्ण
		क्रम (i = 0; i < enic->wq_count; i++)
			netअगर_napi_add(netdev, &enic->napi[enic_cq_wq(enic, i)],
				       enic_poll_msix_wq, NAPI_POLL_WEIGHT);
		अवरोध;
	पूर्ण

	वापस 0;

err_out_मुक्त_vnic_resources:
	enic_मुक्त_affinity_hपूर्णांक(enic);
	enic_clear_पूर्णांकr_mode(enic);
	enic_मुक्त_vnic_resources(enic);

	वापस err;
पूर्ण

अटल व्योम enic_iounmap(काष्ठा enic *enic)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(enic->bar); i++)
		अगर (enic->bar[i].vaddr)
			iounmap(enic->bar[i].vaddr);
पूर्ण

अटल पूर्णांक enic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *netdev;
	काष्ठा enic *enic;
	पूर्णांक using_dac = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
#अगर_घोषित CONFIG_PCI_IOV
	पूर्णांक pos = 0;
#पूर्ण_अगर
	पूर्णांक num_pps = 1;

	/* Allocate net device काष्ठाure and initialize.  Private
	 * instance data is initialized to zero.
	 */

	netdev = alloc_etherdev_mqs(माप(काष्ठा enic),
				    ENIC_RQ_MAX, ENIC_WQ_MAX);
	अगर (!netdev)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, netdev);

	SET_NETDEV_DEV(netdev, &pdev->dev);

	enic = netdev_priv(netdev);
	enic->netdev = netdev;
	enic->pdev = pdev;

	/* Setup PCI resources
	 */

	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(dev, "Cannot enable PCI device, aborting\n");
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "Cannot request PCI regions, aborting\n");
		जाओ err_out_disable_device;
	पूर्ण

	pci_set_master(pdev);

	/* Query PCI controller on प्रणाली क्रम DMA addressing
	 * limitation क्रम the device.  Try 47-bit first, and
	 * fail to 32-bit.
	 */

	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(47));
	अगर (err) अणु
		err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(dev, "No usable DMA configuration, aborting\n");
			जाओ err_out_release_regions;
		पूर्ण
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(dev, "Unable to obtain %u-bit DMA "
				"for consistent allocations, aborting\n", 32);
			जाओ err_out_release_regions;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(47));
		अगर (err) अणु
			dev_err(dev, "Unable to obtain %u-bit DMA "
				"for consistent allocations, aborting\n", 47);
			जाओ err_out_release_regions;
		पूर्ण
		using_dac = 1;
	पूर्ण

	/* Map vNIC resources from BAR0-5
	 */

	क्रम (i = 0; i < ARRAY_SIZE(enic->bar); i++) अणु
		अगर (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM))
			जारी;
		enic->bar[i].len = pci_resource_len(pdev, i);
		enic->bar[i].vaddr = pci_iomap(pdev, i, enic->bar[i].len);
		अगर (!enic->bar[i].vaddr) अणु
			dev_err(dev, "Cannot memory-map BAR %d, aborting\n", i);
			err = -ENODEV;
			जाओ err_out_iounmap;
		पूर्ण
		enic->bar[i].bus_addr = pci_resource_start(pdev, i);
	पूर्ण

	/* Register vNIC device
	 */

	enic->vdev = vnic_dev_रेजिस्टर(शून्य, enic, pdev, enic->bar,
		ARRAY_SIZE(enic->bar));
	अगर (!enic->vdev) अणु
		dev_err(dev, "vNIC registration failed, aborting\n");
		err = -ENODEV;
		जाओ err_out_iounmap;
	पूर्ण

	err = vnic_devcmd_init(enic->vdev);

	अगर (err)
		जाओ err_out_vnic_unरेजिस्टर;

#अगर_घोषित CONFIG_PCI_IOV
	/* Get number of subvnics */
	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	अगर (pos) अणु
		pci_पढ़ो_config_word(pdev, pos + PCI_SRIOV_TOTAL_VF,
			&enic->num_vfs);
		अगर (enic->num_vfs) अणु
			err = pci_enable_sriov(pdev, enic->num_vfs);
			अगर (err) अणु
				dev_err(dev, "SRIOV enable failed, aborting."
					" pci_enable_sriov() returned %d\n",
					err);
				जाओ err_out_vnic_unरेजिस्टर;
			पूर्ण
			enic->priv_flags |= ENIC_SRIOV_ENABLED;
			num_pps = enic->num_vfs;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Allocate काष्ठाure क्रम port profiles */
	enic->pp = kसुस्मृति(num_pps, माप(*enic->pp), GFP_KERNEL);
	अगर (!enic->pp) अणु
		err = -ENOMEM;
		जाओ err_out_disable_sriov_pp;
	पूर्ण

	/* Issue device खोलो to get device in known state
	 */

	err = enic_dev_खोलो(enic);
	अगर (err) अणु
		dev_err(dev, "vNIC dev open failed, aborting\n");
		जाओ err_out_disable_sriov;
	पूर्ण

	/* Setup devcmd lock
	 */

	spin_lock_init(&enic->devcmd_lock);
	spin_lock_init(&enic->enic_api_lock);

	/*
	 * Set ingress vlan reग_लिखो mode beक्रमe vnic initialization
	 */

	err = enic_dev_set_ig_vlan_reग_लिखो_mode(enic);
	अगर (err) अणु
		dev_err(dev,
			"Failed to set ingress vlan rewrite mode, aborting.\n");
		जाओ err_out_dev_बंद;
	पूर्ण

	/* Issue device init to initialize the vnic-to-चयन link.
	 * We'll start with carrier off and रुको क्रम link UP
	 * notअगरication later to turn on carrier.  We करोn't need
	 * to रुको here क्रम the vnic-to-चयन link initialization
	 * to complete; link UP notअगरication is the indication that
	 * the process is complete.
	 */

	netअगर_carrier_off(netdev);

	/* Do not call dev_init क्रम a dynamic vnic.
	 * For a dynamic vnic, init_prov_info will be
	 * called later by an upper layer.
	 */

	अगर (!enic_is_dynamic(enic)) अणु
		err = vnic_dev_init(enic->vdev, 0);
		अगर (err) अणु
			dev_err(dev, "vNIC dev init failed, aborting\n");
			जाओ err_out_dev_बंद;
		पूर्ण
	पूर्ण

	err = enic_dev_init(enic);
	अगर (err) अणु
		dev_err(dev, "Device initialization failed, aborting\n");
		जाओ err_out_dev_बंद;
	पूर्ण

	netअगर_set_real_num_tx_queues(netdev, enic->wq_count);
	netअगर_set_real_num_rx_queues(netdev, enic->rq_count);

	/* Setup notअगरication समयr, HW reset task, and wq locks
	 */

	समयr_setup(&enic->notअगरy_समयr, enic_notअगरy_समयr, 0);

	enic_rfs_flw_tbl_init(enic);
	enic_set_rx_coal_setting(enic);
	INIT_WORK(&enic->reset, enic_reset);
	INIT_WORK(&enic->tx_hang_reset, enic_tx_hang_reset);
	INIT_WORK(&enic->change_mtu_work, enic_change_mtu_work);

	क्रम (i = 0; i < enic->wq_count; i++)
		spin_lock_init(&enic->wq_lock[i]);

	/* Register net device
	 */

	enic->port_mtu = enic->config.mtu;

	err = enic_set_mac_addr(netdev, enic->mac_addr);
	अगर (err) अणु
		dev_err(dev, "Invalid MAC address, aborting\n");
		जाओ err_out_dev_deinit;
	पूर्ण

	enic->tx_coalesce_usecs = enic->config.पूर्णांकr_समयr_usec;
	/* rx coalesce समय alपढ़ोy got initialized. This माला_लो used
	 * अगर adaptive coal is turned off
	 */
	enic->rx_coalesce_usecs = enic->tx_coalesce_usecs;

	अगर (enic_is_dynamic(enic) || enic_is_sriov_vf(enic))
		netdev->netdev_ops = &enic_netdev_dynamic_ops;
	अन्यथा
		netdev->netdev_ops = &enic_netdev_ops;

	netdev->watchकरोg_समयo = 2 * HZ;
	enic_set_ethtool_ops(netdev);

	netdev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
	अगर (ENIC_SETTING(enic, LOOP)) अणु
		netdev->features &= ~NETIF_F_HW_VLAN_CTAG_TX;
		enic->loop_enable = 1;
		enic->loop_tag = enic->config.loop_tag;
		dev_info(dev, "loopback tag=0x%04x\n", enic->loop_tag);
	पूर्ण
	अगर (ENIC_SETTING(enic, TXCSUM))
		netdev->hw_features |= NETIF_F_SG | NETIF_F_HW_CSUM;
	अगर (ENIC_SETTING(enic, TSO))
		netdev->hw_features |= NETIF_F_TSO |
			NETIF_F_TSO6 | NETIF_F_TSO_ECN;
	अगर (ENIC_SETTING(enic, RSS))
		netdev->hw_features |= NETIF_F_RXHASH;
	अगर (ENIC_SETTING(enic, RXCSUM))
		netdev->hw_features |= NETIF_F_RXCSUM;
	अगर (ENIC_SETTING(enic, VXLAN)) अणु
		u64 patch_level;
		u64 a1 = 0;

		netdev->hw_enc_features |= NETIF_F_RXCSUM		|
					   NETIF_F_TSO			|
					   NETIF_F_TSO6			|
					   NETIF_F_TSO_ECN		|
					   NETIF_F_GSO_UDP_TUNNEL	|
					   NETIF_F_HW_CSUM		|
					   NETIF_F_GSO_UDP_TUNNEL_CSUM;
		netdev->hw_features |= netdev->hw_enc_features;
		/* get bit mask from hw about supported offload bit level
		 * BIT(0) = fw supports patch_level 0
		 *	    fcoe bit = encap
		 *	    fcoe_fc_crc_ok = outer csum ok
		 * BIT(1) = always set by fw
		 * BIT(2) = fw supports patch_level 2
		 *	    BIT(0) in rss_hash = encap
		 *	    BIT(1,2) in rss_hash = outer_ip_csum_ok/
		 *				   outer_tcp_csum_ok
		 * used in enic_rq_indicate_buf
		 */
		err = vnic_dev_get_supported_feature_ver(enic->vdev,
							 VIC_FEATURE_VXLAN,
							 &patch_level, &a1);
		अगर (err)
			patch_level = 0;
		enic->vxlan.flags = (u8)a1;
		/* mask bits that are supported by driver
		 */
		patch_level &= BIT_ULL(0) | BIT_ULL(2);
		patch_level = fls(patch_level);
		patch_level = patch_level ? patch_level - 1 : 0;
		enic->vxlan.patch_level = patch_level;

		अगर (vnic_dev_get_res_count(enic->vdev, RES_TYPE_WQ) == 1 ||
		    enic->vxlan.flags & ENIC_VXLAN_MULTI_WQ) अणु
			netdev->udp_tunnel_nic_info = &enic_udp_tunnels_v4;
			अगर (enic->vxlan.flags & ENIC_VXLAN_OUTER_IPV6)
				netdev->udp_tunnel_nic_info = &enic_udp_tunnels;
		पूर्ण
	पूर्ण

	netdev->features |= netdev->hw_features;
	netdev->vlan_features |= netdev->features;

#अगर_घोषित CONFIG_RFS_ACCEL
	netdev->hw_features |= NETIF_F_NTUPLE;
#पूर्ण_अगर

	अगर (using_dac)
		netdev->features |= NETIF_F_HIGHDMA;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	/* MTU range: 68 - 9000 */
	netdev->min_mtu = ENIC_MIN_MTU;
	netdev->max_mtu = ENIC_MAX_MTU;
	netdev->mtu	= enic->port_mtu;

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(dev, "Cannot register net device, aborting\n");
		जाओ err_out_dev_deinit;
	पूर्ण
	enic->rx_copyअवरोध = RX_COPYBREAK_DEFAULT;

	वापस 0;

err_out_dev_deinit:
	enic_dev_deinit(enic);
err_out_dev_बंद:
	vnic_dev_बंद(enic->vdev);
err_out_disable_sriov:
	kमुक्त(enic->pp);
err_out_disable_sriov_pp:
#अगर_घोषित CONFIG_PCI_IOV
	अगर (enic_sriov_enabled(enic)) अणु
		pci_disable_sriov(pdev);
		enic->priv_flags &= ~ENIC_SRIOV_ENABLED;
	पूर्ण
#पूर्ण_अगर
err_out_vnic_unरेजिस्टर:
	vnic_dev_unरेजिस्टर(enic->vdev);
err_out_iounmap:
	enic_iounmap(enic);
err_out_release_regions:
	pci_release_regions(pdev);
err_out_disable_device:
	pci_disable_device(pdev);
err_out_मुक्त_netdev:
	मुक्त_netdev(netdev);

	वापस err;
पूर्ण

अटल व्योम enic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);

	अगर (netdev) अणु
		काष्ठा enic *enic = netdev_priv(netdev);

		cancel_work_sync(&enic->reset);
		cancel_work_sync(&enic->change_mtu_work);
		unरेजिस्टर_netdev(netdev);
		enic_dev_deinit(enic);
		vnic_dev_बंद(enic->vdev);
#अगर_घोषित CONFIG_PCI_IOV
		अगर (enic_sriov_enabled(enic)) अणु
			pci_disable_sriov(pdev);
			enic->priv_flags &= ~ENIC_SRIOV_ENABLED;
		पूर्ण
#पूर्ण_अगर
		kमुक्त(enic->pp);
		vnic_dev_unरेजिस्टर(enic->vdev);
		enic_iounmap(enic);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		मुक्त_netdev(netdev);
	पूर्ण
पूर्ण

अटल काष्ठा pci_driver enic_driver = अणु
	.name = DRV_NAME,
	.id_table = enic_id_table,
	.probe = enic_probe,
	.हटाओ = enic_हटाओ,
पूर्ण;

module_pci_driver(enic_driver);
