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

#अगर_अघोषित _ENIC_H_
#घोषणा _ENIC_H_

#समावेश "vnic_enet.h"
#समावेश "vnic_dev.h"
#समावेश "vnic_wq.h"
#समावेश "vnic_rq.h"
#समावेश "vnic_cq.h"
#समावेश "vnic_intr.h"
#समावेश "vnic_stats.h"
#समावेश "vnic_nic.h"
#समावेश "vnic_rss.h"
#समावेश <linux/irq.h>

#घोषणा DRV_NAME		"enic"
#घोषणा DRV_DESCRIPTION		"Cisco VIC Ethernet NIC Driver"

#घोषणा ENIC_BARS_MAX		6

#घोषणा ENIC_WQ_MAX		8
#घोषणा ENIC_RQ_MAX		8
#घोषणा ENIC_CQ_MAX		(ENIC_WQ_MAX + ENIC_RQ_MAX)
#घोषणा ENIC_INTR_MAX		(ENIC_CQ_MAX + 2)

#घोषणा ENIC_WQ_NAPI_BUDGET	256

#घोषणा ENIC_AIC_LARGE_PKT_DIFF	3

काष्ठा enic_msix_entry अणु
	पूर्णांक requested;
	अक्षर devname[IFNAMSIZ + 8];
	irqवापस_t (*isr)(पूर्णांक, व्योम *);
	व्योम *devid;
	cpumask_var_t affinity_mask;
पूर्ण;

/* Store only the lower range.  Higher range is given by fw. */
काष्ठा enic_पूर्णांकr_mod_range अणु
	u32 small_pkt_range_start;
	u32 large_pkt_range_start;
पूर्ण;

काष्ठा enic_पूर्णांकr_mod_table अणु
	u32 rx_rate;
	u32 range_percent;
पूर्ण;

#घोषणा ENIC_MAX_LINK_SPEEDS		3
#घोषणा ENIC_LINK_SPEED_10G		10000
#घोषणा ENIC_LINK_SPEED_4G		4000
#घोषणा ENIC_LINK_40G_INDEX		2
#घोषणा ENIC_LINK_10G_INDEX		1
#घोषणा ENIC_LINK_4G_INDEX		0
#घोषणा ENIC_RX_COALESCE_RANGE_END	125
#घोषणा ENIC_AIC_TS_BREAK		100

काष्ठा enic_rx_coal अणु
	u32 small_pkt_range_start;
	u32 large_pkt_range_start;
	u32 range_end;
	u32 use_adaptive_rx_coalesce;
पूर्ण;

/* priv_flags */
#घोषणा ENIC_SRIOV_ENABLED		(1 << 0)

/* enic port profile set flags */
#घोषणा ENIC_PORT_REQUEST_APPLIED	(1 << 0)
#घोषणा ENIC_SET_REQUEST		(1 << 1)
#घोषणा ENIC_SET_NAME			(1 << 2)
#घोषणा ENIC_SET_INSTANCE		(1 << 3)
#घोषणा ENIC_SET_HOST			(1 << 4)

काष्ठा enic_port_profile अणु
	u32 set;
	u8 request;
	अक्षर name[PORT_PROखाता_MAX];
	u8 instance_uuid[PORT_UUID_MAX];
	u8 host_uuid[PORT_UUID_MAX];
	u8 vf_mac[ETH_ALEN];
	u8 mac_addr[ETH_ALEN];
पूर्ण;

/* enic_rfs_fltr_node - rfs filter node in hash table
 *	@@keys: IPv4 5 tuple
 *	@flow_id: flow_id of clsf filter provided by kernel
 *	@fltr_id: filter id of clsf filter वापसed by adaptor
 *	@rq_id: desired rq index
 *	@node: hlist_node
 */
काष्ठा enic_rfs_fltr_node अणु
	काष्ठा flow_keys keys;
	u32 flow_id;
	u16 fltr_id;
	u16 rq_id;
	काष्ठा hlist_node node;
पूर्ण;

/* enic_rfs_flw_tbl - rfs flow table
 *	@max: Maximum number of filters vNIC supports
 *	@मुक्त: Number of मुक्त filters available
 *	@toclean: hash table index to clean next
 *	@ht_head: hash table list head
 *	@lock: spin lock
 *	@rfs_may_expire: समयr function क्रम enic_rps_may_expire_flow
 */
काष्ठा enic_rfs_flw_tbl अणु
	u16 max;
	पूर्णांक मुक्त;

#घोषणा ENIC_RFS_FLW_BITSHIFT	(10)
#घोषणा ENIC_RFS_FLW_MASK	((1 << ENIC_RFS_FLW_BITSHIFT) - 1)
	u16 toclean:ENIC_RFS_FLW_BITSHIFT;
	काष्ठा hlist_head ht_head[1 << ENIC_RFS_FLW_BITSHIFT];
	spinlock_t lock;
	काष्ठा समयr_list rfs_may_expire;
पूर्ण;

काष्ठा vxlan_offload अणु
	u16 vxlan_udp_port_number;
	u8 patch_level;
	u8 flags;
पूर्ण;

/* Per-instance निजी data काष्ठाure */
काष्ठा enic अणु
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;
	काष्ठा vnic_enet_config config;
	काष्ठा vnic_dev_bar bar[ENIC_BARS_MAX];
	काष्ठा vnic_dev *vdev;
	काष्ठा समयr_list notअगरy_समयr;
	काष्ठा work_काष्ठा reset;
	काष्ठा work_काष्ठा tx_hang_reset;
	काष्ठा work_काष्ठा change_mtu_work;
	काष्ठा msix_entry msix_entry[ENIC_INTR_MAX];
	काष्ठा enic_msix_entry msix[ENIC_INTR_MAX];
	u32 msg_enable;
	spinlock_t devcmd_lock;
	u8 mac_addr[ETH_ALEN];
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक priv_flags;
	अचिन्हित पूर्णांक mc_count;
	अचिन्हित पूर्णांक uc_count;
	u32 port_mtu;
	काष्ठा enic_rx_coal rx_coalesce_setting;
	u32 rx_coalesce_usecs;
	u32 tx_coalesce_usecs;
#अगर_घोषित CONFIG_PCI_IOV
	u16 num_vfs;
#पूर्ण_अगर
	spinlock_t enic_api_lock;
	bool enic_api_busy;
	काष्ठा enic_port_profile *pp;

	/* work queue cache line section */
	____cacheline_aligned काष्ठा vnic_wq wq[ENIC_WQ_MAX];
	spinlock_t wq_lock[ENIC_WQ_MAX];
	अचिन्हित पूर्णांक wq_count;
	u16 loop_enable;
	u16 loop_tag;

	/* receive queue cache line section */
	____cacheline_aligned काष्ठा vnic_rq rq[ENIC_RQ_MAX];
	अचिन्हित पूर्णांक rq_count;
	काष्ठा vxlan_offload vxlan;
	u64 rq_truncated_pkts;
	u64 rq_bad_fcs;
	काष्ठा napi_काष्ठा napi[ENIC_RQ_MAX + ENIC_WQ_MAX];

	/* पूर्णांकerrupt resource cache line section */
	____cacheline_aligned काष्ठा vnic_पूर्णांकr पूर्णांकr[ENIC_INTR_MAX];
	अचिन्हित पूर्णांक पूर्णांकr_count;
	u32 __iomem *legacy_pba;		/* memory-mapped */

	/* completion queue cache line section */
	____cacheline_aligned काष्ठा vnic_cq cq[ENIC_CQ_MAX];
	अचिन्हित पूर्णांक cq_count;
	काष्ठा enic_rfs_flw_tbl rfs_h;
	u32 rx_copyअवरोध;
	u8 rss_key[ENIC_RSS_LEN];
	काष्ठा vnic_gen_stats gen_stats;
पूर्ण;

अटल अंतरभूत काष्ठा net_device *vnic_get_netdev(काष्ठा vnic_dev *vdev)
अणु
	काष्ठा enic *enic = vdev->priv;

	वापस enic->netdev;
पूर्ण

/* wrappers function क्रम kernel log
 */
#घोषणा vdev_err(vdev, fmt, ...)					\
	dev_err(&(vdev)->pdev->dev, fmt, ##__VA_ARGS__)
#घोषणा vdev_warn(vdev, fmt, ...)					\
	dev_warn(&(vdev)->pdev->dev, fmt, ##__VA_ARGS__)
#घोषणा vdev_info(vdev, fmt, ...)					\
	dev_info(&(vdev)->pdev->dev, fmt, ##__VA_ARGS__)

#घोषणा vdev_neterr(vdev, fmt, ...)					\
	netdev_err(vnic_get_netdev(vdev), fmt, ##__VA_ARGS__)
#घोषणा vdev_netwarn(vdev, fmt, ...)					\
	netdev_warn(vnic_get_netdev(vdev), fmt, ##__VA_ARGS__)
#घोषणा vdev_netinfo(vdev, fmt, ...)					\
	netdev_info(vnic_get_netdev(vdev), fmt, ##__VA_ARGS__)

अटल अंतरभूत काष्ठा device *enic_get_dev(काष्ठा enic *enic)
अणु
	वापस &(enic->pdev->dev);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक enic_cq_rq(काष्ठा enic *enic, अचिन्हित पूर्णांक rq)
अणु
	वापस rq;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक enic_cq_wq(काष्ठा enic *enic, अचिन्हित पूर्णांक wq)
अणु
	वापस enic->rq_count + wq;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक enic_legacy_io_पूर्णांकr(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक enic_legacy_err_पूर्णांकr(व्योम)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक enic_legacy_notअगरy_पूर्णांकr(व्योम)
अणु
	वापस 2;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक enic_msix_rq_पूर्णांकr(काष्ठा enic *enic,
	अचिन्हित पूर्णांक rq)
अणु
	वापस enic->cq[enic_cq_rq(enic, rq)].पूर्णांकerrupt_offset;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक enic_msix_wq_पूर्णांकr(काष्ठा enic *enic,
	अचिन्हित पूर्णांक wq)
अणु
	वापस enic->cq[enic_cq_wq(enic, wq)].पूर्णांकerrupt_offset;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक enic_msix_err_पूर्णांकr(काष्ठा enic *enic)
अणु
	वापस enic->rq_count + enic->wq_count;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक enic_msix_notअगरy_पूर्णांकr(काष्ठा enic *enic)
अणु
	वापस enic->rq_count + enic->wq_count + 1;
पूर्ण

अटल अंतरभूत bool enic_is_err_पूर्णांकr(काष्ठा enic *enic, पूर्णांक पूर्णांकr)
अणु
	चयन (vnic_dev_get_पूर्णांकr_mode(enic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_INTX:
		वापस पूर्णांकr == enic_legacy_err_पूर्णांकr();
	हाल VNIC_DEV_INTR_MODE_MSIX:
		वापस पूर्णांकr == enic_msix_err_पूर्णांकr(enic);
	हाल VNIC_DEV_INTR_MODE_MSI:
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool enic_is_notअगरy_पूर्णांकr(काष्ठा enic *enic, पूर्णांक पूर्णांकr)
अणु
	चयन (vnic_dev_get_पूर्णांकr_mode(enic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_INTX:
		वापस पूर्णांकr == enic_legacy_notअगरy_पूर्णांकr();
	हाल VNIC_DEV_INTR_MODE_MSIX:
		वापस पूर्णांकr == enic_msix_notअगरy_पूर्णांकr(enic);
	हाल VNIC_DEV_INTR_MODE_MSI:
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक enic_dma_map_check(काष्ठा enic *enic, dma_addr_t dma_addr)
अणु
	अगर (unlikely(pci_dma_mapping_error(enic->pdev, dma_addr))) अणु
		net_warn_ratelimited("%s: PCI dma mapping failed!\n",
				     enic->netdev->name);
		enic->gen_stats.dma_map_error++;

		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम enic_reset_addr_lists(काष्ठा enic *enic);
पूर्णांक enic_sriov_enabled(काष्ठा enic *enic);
पूर्णांक enic_is_valid_vf(काष्ठा enic *enic, पूर्णांक vf);
पूर्णांक enic_is_dynamic(काष्ठा enic *enic);
व्योम enic_set_ethtool_ops(काष्ठा net_device *netdev);
पूर्णांक __enic_set_rsskey(काष्ठा enic *enic);

#पूर्ण_अगर /* _ENIC_H_ */
