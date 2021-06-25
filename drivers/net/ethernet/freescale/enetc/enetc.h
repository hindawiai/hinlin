<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2017-2019 NXP */

#समावेश <linux/समयr.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/phylink.h>
#समावेश <linux/dim.h>

#समावेश "enetc_hw.h"

#घोषणा ENETC_MAC_MAXFRM_SIZE	9600
#घोषणा ENETC_MAX_MTU		(ENETC_MAC_MAXFRM_SIZE - \
				(ETH_FCS_LEN + ETH_HLEN + VLAN_HLEN))

काष्ठा enetc_tx_swbd अणु
	जोड़ अणु
		काष्ठा sk_buff *skb;
		काष्ठा xdp_frame *xdp_frame;
	पूर्ण;
	dma_addr_t dma;
	काष्ठा page *page;	/* valid only अगर is_xdp_tx */
	u16 page_offset;	/* valid only अगर is_xdp_tx */
	u16 len;
	क्रमागत dma_data_direction dir;
	u8 is_dma_page:1;
	u8 check_wb:1;
	u8 करो_twostep_tstamp:1;
	u8 is_eof:1;
	u8 is_xdp_tx:1;
	u8 is_xdp_redirect:1;
पूर्ण;

#घोषणा ENETC_RX_MAXFRM_SIZE	ENETC_MAC_MAXFRM_SIZE
#घोषणा ENETC_RXB_TRUESIZE	2048 /* PAGE_SIZE >> 1 */
#घोषणा ENETC_RXB_PAD		NET_SKB_PAD /* add extra space अगर needed */
#घोषणा ENETC_RXB_DMA_SIZE	\
	(SKB_WITH_OVERHEAD(ENETC_RXB_TRUESIZE) - ENETC_RXB_PAD)
#घोषणा ENETC_RXB_DMA_SIZE_XDP	\
	(SKB_WITH_OVERHEAD(ENETC_RXB_TRUESIZE) - XDP_PACKET_HEADROOM)

काष्ठा enetc_rx_swbd अणु
	dma_addr_t dma;
	काष्ठा page *page;
	u16 page_offset;
	क्रमागत dma_data_direction dir;
	u16 len;
पूर्ण;

/* ENETC overhead: optional extension BD + 1 BD gap */
#घोषणा ENETC_TXBDS_NEEDED(val)	((val) + 2)
/* max # of chained Tx BDs is 15, including head and extension BD */
#घोषणा ENETC_MAX_SKB_FRAGS	13
#घोषणा ENETC_TXBDS_MAX_NEEDED	ENETC_TXBDS_NEEDED(ENETC_MAX_SKB_FRAGS + 1)

काष्ठा enetc_ring_stats अणु
	अचिन्हित पूर्णांक packets;
	अचिन्हित पूर्णांक bytes;
	अचिन्हित पूर्णांक rx_alloc_errs;
	अचिन्हित पूर्णांक xdp_drops;
	अचिन्हित पूर्णांक xdp_tx;
	अचिन्हित पूर्णांक xdp_tx_drops;
	अचिन्हित पूर्णांक xdp_redirect;
	अचिन्हित पूर्णांक xdp_redirect_failures;
	अचिन्हित पूर्णांक xdp_redirect_sg;
	अचिन्हित पूर्णांक recycles;
	अचिन्हित पूर्णांक recycle_failures;
पूर्ण;

काष्ठा enetc_xdp_data अणु
	काष्ठा xdp_rxq_info rxq;
	काष्ठा bpf_prog *prog;
	पूर्णांक xdp_tx_in_flight;
पूर्ण;

#घोषणा ENETC_RX_RING_DEFAULT_SIZE	2048
#घोषणा ENETC_TX_RING_DEFAULT_SIZE	2048
#घोषणा ENETC_DEFAULT_TX_WORK		(ENETC_TX_RING_DEFAULT_SIZE / 2)

काष्ठा enetc_bdr अणु
	काष्ठा device *dev; /* क्रम DMA mapping */
	काष्ठा net_device *ndev;
	व्योम *bd_base; /* poपूर्णांकs to Rx or Tx BD ring */
	जोड़ अणु
		व्योम __iomem *tpir;
		व्योम __iomem *rcir;
	पूर्ण;
	u16 index;
	पूर्णांक bd_count; /* # of BDs */
	पूर्णांक next_to_use;
	पूर्णांक next_to_clean;
	जोड़ अणु
		काष्ठा enetc_tx_swbd *tx_swbd;
		काष्ठा enetc_rx_swbd *rx_swbd;
	पूर्ण;
	जोड़ अणु
		व्योम __iomem *tcir; /* Tx */
		पूर्णांक next_to_alloc; /* Rx */
	पूर्ण;
	व्योम __iomem *idr; /* Interrupt Detect Register poपूर्णांकer */

	पूर्णांक buffer_offset;
	काष्ठा enetc_xdp_data xdp;

	काष्ठा enetc_ring_stats stats;

	dma_addr_t bd_dma_base;
	u8 tsd_enable; /* Time specअगरic departure */
	bool ext_en; /* enable h/w descriptor extensions */
पूर्ण ____cacheline_aligned_in_smp;

अटल अंतरभूत व्योम enetc_bdr_idx_inc(काष्ठा enetc_bdr *bdr, पूर्णांक *i)
अणु
	अगर (unlikely(++*i == bdr->bd_count))
		*i = 0;
पूर्ण

अटल अंतरभूत पूर्णांक enetc_bd_unused(काष्ठा enetc_bdr *bdr)
अणु
	अगर (bdr->next_to_clean > bdr->next_to_use)
		वापस bdr->next_to_clean - bdr->next_to_use - 1;

	वापस bdr->bd_count + bdr->next_to_clean - bdr->next_to_use - 1;
पूर्ण

अटल अंतरभूत पूर्णांक enetc_swbd_unused(काष्ठा enetc_bdr *bdr)
अणु
	अगर (bdr->next_to_clean > bdr->next_to_alloc)
		वापस bdr->next_to_clean - bdr->next_to_alloc - 1;

	वापस bdr->bd_count + bdr->next_to_clean - bdr->next_to_alloc - 1;
पूर्ण

/* Control BD ring */
#घोषणा ENETC_CBDR_DEFAULT_SIZE	64
काष्ठा enetc_cbdr अणु
	व्योम *bd_base; /* poपूर्णांकs to Rx or Tx BD ring */
	व्योम __iomem *pir;
	व्योम __iomem *cir;
	व्योम __iomem *mr; /* mode रेजिस्टर */

	पूर्णांक bd_count; /* # of BDs */
	पूर्णांक next_to_use;
	पूर्णांक next_to_clean;

	dma_addr_t bd_dma_base;
	काष्ठा device *dma_dev;
पूर्ण;

#घोषणा ENETC_TXBD(BDR, i) (&(((जोड़ enetc_tx_bd *)((BDR).bd_base))[i]))

अटल अंतरभूत जोड़ enetc_rx_bd *enetc_rxbd(काष्ठा enetc_bdr *rx_ring, पूर्णांक i)
अणु
	पूर्णांक hw_idx = i;

#अगर_घोषित CONFIG_FSL_ENETC_PTP_CLOCK
	अगर (rx_ring->ext_en)
		hw_idx = 2 * i;
#पूर्ण_अगर
	वापस &(((जोड़ enetc_rx_bd *)rx_ring->bd_base)[hw_idx]);
पूर्ण

अटल अंतरभूत व्योम enetc_rxbd_next(काष्ठा enetc_bdr *rx_ring,
				   जोड़ enetc_rx_bd **old_rxbd, पूर्णांक *old_index)
अणु
	जोड़ enetc_rx_bd *new_rxbd = *old_rxbd;
	पूर्णांक new_index = *old_index;

	new_rxbd++;

#अगर_घोषित CONFIG_FSL_ENETC_PTP_CLOCK
	अगर (rx_ring->ext_en)
		new_rxbd++;
#पूर्ण_अगर

	अगर (unlikely(++new_index == rx_ring->bd_count)) अणु
		new_rxbd = rx_ring->bd_base;
		new_index = 0;
	पूर्ण

	*old_rxbd = new_rxbd;
	*old_index = new_index;
पूर्ण

अटल अंतरभूत जोड़ enetc_rx_bd *enetc_rxbd_ext(जोड़ enetc_rx_bd *rxbd)
अणु
	वापस ++rxbd;
पूर्ण

काष्ठा enetc_msg_swbd अणु
	व्योम *vaddr;
	dma_addr_t dma;
	पूर्णांक size;
पूर्ण;

#घोषणा ENETC_REV1	0x1
क्रमागत enetc_errata अणु
	ENETC_ERR_VLAN_ISOL	= BIT(0),
	ENETC_ERR_UCMCSWP	= BIT(1),
पूर्ण;

#घोषणा ENETC_SI_F_QBV BIT(0)
#घोषणा ENETC_SI_F_PSFP BIT(1)

/* PCI IEP device data */
काष्ठा enetc_si अणु
	काष्ठा pci_dev *pdev;
	काष्ठा enetc_hw hw;
	क्रमागत enetc_errata errata;

	काष्ठा net_device *ndev; /* back ref. */

	काष्ठा enetc_cbdr cbd_ring;

	पूर्णांक num_rx_rings; /* how many rings are available in the SI */
	पूर्णांक num_tx_rings;
	पूर्णांक num_fs_entries;
	पूर्णांक num_rss; /* number of RSS buckets */
	अचिन्हित लघु pad;
	पूर्णांक hw_features;
पूर्ण;

#घोषणा ENETC_SI_ALIGN	32

अटल अंतरभूत व्योम *enetc_si_priv(स्थिर काष्ठा enetc_si *si)
अणु
	वापस (अक्षर *)si + ALIGN(माप(काष्ठा enetc_si), ENETC_SI_ALIGN);
पूर्ण

अटल अंतरभूत bool enetc_si_is_pf(काष्ठा enetc_si *si)
अणु
	वापस !!(si->hw.port);
पूर्ण

अटल अंतरभूत पूर्णांक enetc_pf_to_port(काष्ठा pci_dev *pf_pdev)
अणु
	चयन (pf_pdev->devfn) अणु
	हाल 0:
		वापस 0;
	हाल 1:
		वापस 1;
	हाल 2:
		वापस 2;
	हाल 6:
		वापस 3;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

#घोषणा ENETC_MAX_NUM_TXQS	8
#घोषणा ENETC_INT_NAME_MAX	(IFNAMSIZ + 8)

काष्ठा enetc_पूर्णांक_vector अणु
	व्योम __iomem *rbier;
	व्योम __iomem *tbier_base;
	व्योम __iomem *ricr1;
	अचिन्हित दीर्घ tx_rings_map;
	पूर्णांक count_tx_rings;
	u32 rx_ictt;
	u16 comp_cnt;
	bool rx_dim_en, rx_napi_work;
	काष्ठा napi_काष्ठा napi ____cacheline_aligned_in_smp;
	काष्ठा dim rx_dim ____cacheline_aligned_in_smp;
	अक्षर name[ENETC_INT_NAME_MAX];

	काष्ठा enetc_bdr rx_ring;
	काष्ठा enetc_bdr tx_ring[];
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा enetc_cls_rule अणु
	काष्ठा ethtool_rx_flow_spec fs;
	पूर्णांक used;
पूर्ण;

#घोषणा ENETC_MAX_BDR_INT	2 /* fixed to max # of available cpus */
काष्ठा psfp_cap अणु
	u32 max_streamid;
	u32 max_psfp_filter;
	u32 max_psfp_gate;
	u32 max_psfp_gatelist;
	u32 max_psfp_meter;
पूर्ण;

#घोषणा ENETC_F_TX_TSTAMP_MASK	0xff
/* TODO: more hardware offloads */
क्रमागत enetc_active_offloads अणु
	/* 8 bits reserved क्रम TX बारtamp types (hwtstamp_tx_types) */
	ENETC_F_TX_TSTAMP		= BIT(0),
	ENETC_F_TX_ONESTEP_SYNC_TSTAMP	= BIT(1),

	ENETC_F_RX_TSTAMP		= BIT(8),
	ENETC_F_QBV			= BIT(9),
	ENETC_F_QCI			= BIT(10),
पूर्ण;

क्रमागत enetc_flags_bit अणु
	ENETC_TX_ONESTEP_TSTAMP_IN_PROGRESS = 0,
पूर्ण;

/* पूर्णांकerrupt coalescing modes */
क्रमागत enetc_ic_mode अणु
	/* one पूर्णांकerrupt per frame */
	ENETC_IC_NONE = 0,
	/* activated when पूर्णांक coalescing समय is set to a non-0 value */
	ENETC_IC_RX_MANUAL = BIT(0),
	ENETC_IC_TX_MANUAL = BIT(1),
	/* use dynamic पूर्णांकerrupt moderation */
	ENETC_IC_RX_ADAPTIVE = BIT(2),
पूर्ण;

#घोषणा ENETC_RXIC_PKTTHR	min_t(u32, 256, ENETC_RX_RING_DEFAULT_SIZE / 2)
#घोषणा ENETC_TXIC_PKTTHR	min_t(u32, 128, ENETC_TX_RING_DEFAULT_SIZE / 2)
#घोषणा ENETC_TXIC_TIMETHR	enetc_usecs_to_cycles(600)

काष्ठा enetc_ndev_priv अणु
	काष्ठा net_device *ndev;
	काष्ठा device *dev; /* dma-mapping device */
	काष्ठा enetc_si *si;

	पूर्णांक bdr_पूर्णांक_num; /* number of Rx/Tx ring पूर्णांकerrupts */
	काष्ठा enetc_पूर्णांक_vector *पूर्णांक_vector[ENETC_MAX_BDR_INT];
	u16 num_rx_rings, num_tx_rings;
	u16 rx_bd_count, tx_bd_count;

	u16 msg_enable;
	क्रमागत enetc_active_offloads active_offloads;

	u32 speed; /* store speed क्रम compare update pspeed */

	काष्ठा enetc_bdr **xdp_tx_ring;
	काष्ठा enetc_bdr *tx_ring[16];
	काष्ठा enetc_bdr *rx_ring[16];

	काष्ठा enetc_cls_rule *cls_rules;

	काष्ठा psfp_cap psfp_cap;

	काष्ठा phylink *phylink;
	पूर्णांक ic_mode;
	u32 tx_ictt;

	काष्ठा bpf_prog *xdp_prog;

	अचिन्हित दीर्घ flags;

	काष्ठा work_काष्ठा	tx_onestep_tstamp;
	काष्ठा sk_buff_head	tx_skbs;
पूर्ण;

/* Messaging */

/* VF-PF set primary MAC address message क्रमmat */
काष्ठा enetc_msg_cmd_set_primary_mac अणु
	काष्ठा enetc_msg_cmd_header header;
	काष्ठा sockaddr mac;
पूर्ण;

#घोषणा ENETC_CBD(R, i)	(&(((काष्ठा enetc_cbd *)((R).bd_base))[i]))

#घोषणा ENETC_CBDR_TIMEOUT	1000 /* usecs */

/* PTP driver exports */
बाह्य पूर्णांक enetc_phc_index;

/* SI common */
पूर्णांक enetc_pci_probe(काष्ठा pci_dev *pdev, स्थिर अक्षर *name, पूर्णांक माप_priv);
व्योम enetc_pci_हटाओ(काष्ठा pci_dev *pdev);
पूर्णांक enetc_alloc_msix(काष्ठा enetc_ndev_priv *priv);
व्योम enetc_मुक्त_msix(काष्ठा enetc_ndev_priv *priv);
व्योम enetc_get_si_caps(काष्ठा enetc_si *si);
व्योम enetc_init_si_rings_params(काष्ठा enetc_ndev_priv *priv);
पूर्णांक enetc_alloc_si_resources(काष्ठा enetc_ndev_priv *priv);
व्योम enetc_मुक्त_si_resources(काष्ठा enetc_ndev_priv *priv);
पूर्णांक enetc_configure_si(काष्ठा enetc_ndev_priv *priv);

पूर्णांक enetc_खोलो(काष्ठा net_device *ndev);
पूर्णांक enetc_बंद(काष्ठा net_device *ndev);
व्योम enetc_start(काष्ठा net_device *ndev);
व्योम enetc_stop(काष्ठा net_device *ndev);
netdev_tx_t enetc_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev);
काष्ठा net_device_stats *enetc_get_stats(काष्ठा net_device *ndev);
पूर्णांक enetc_set_features(काष्ठा net_device *ndev,
		       netdev_features_t features);
पूर्णांक enetc_ioctl(काष्ठा net_device *ndev, काष्ठा अगरreq *rq, पूर्णांक cmd);
पूर्णांक enetc_setup_tc(काष्ठा net_device *ndev, क्रमागत tc_setup_type type,
		   व्योम *type_data);
पूर्णांक enetc_setup_bpf(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp);
पूर्णांक enetc_xdp_xmit(काष्ठा net_device *ndev, पूर्णांक num_frames,
		   काष्ठा xdp_frame **frames, u32 flags);

/* ethtool */
व्योम enetc_set_ethtool_ops(काष्ठा net_device *ndev);

/* control buffer descriptor ring (CBDR) */
पूर्णांक enetc_setup_cbdr(काष्ठा device *dev, काष्ठा enetc_hw *hw, पूर्णांक bd_count,
		     काष्ठा enetc_cbdr *cbdr);
व्योम enetc_tearकरोwn_cbdr(काष्ठा enetc_cbdr *cbdr);
पूर्णांक enetc_set_mac_flt_entry(काष्ठा enetc_si *si, पूर्णांक index,
			    अक्षर *mac_addr, पूर्णांक si_map);
पूर्णांक enetc_clear_mac_flt_entry(काष्ठा enetc_si *si, पूर्णांक index);
पूर्णांक enetc_set_fs_entry(काष्ठा enetc_si *si, काष्ठा enetc_cmd_rfse *rfse,
		       पूर्णांक index);
व्योम enetc_set_rss_key(काष्ठा enetc_hw *hw, स्थिर u8 *bytes);
पूर्णांक enetc_get_rss_table(काष्ठा enetc_si *si, u32 *table, पूर्णांक count);
पूर्णांक enetc_set_rss_table(काष्ठा enetc_si *si, स्थिर u32 *table, पूर्णांक count);
पूर्णांक enetc_send_cmd(काष्ठा enetc_si *si, काष्ठा enetc_cbd *cbd);

#अगर_घोषित CONFIG_FSL_ENETC_QOS
पूर्णांक enetc_setup_tc_taprio(काष्ठा net_device *ndev, व्योम *type_data);
व्योम enetc_sched_speed_set(काष्ठा enetc_ndev_priv *priv, पूर्णांक speed);
पूर्णांक enetc_setup_tc_cbs(काष्ठा net_device *ndev, व्योम *type_data);
पूर्णांक enetc_setup_tc_txसमय(काष्ठा net_device *ndev, व्योम *type_data);
पूर्णांक enetc_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
			    व्योम *cb_priv);
पूर्णांक enetc_setup_tc_psfp(काष्ठा net_device *ndev, व्योम *type_data);
पूर्णांक enetc_psfp_init(काष्ठा enetc_ndev_priv *priv);
पूर्णांक enetc_psfp_clean(काष्ठा enetc_ndev_priv *priv);

अटल अंतरभूत व्योम enetc_get_max_cap(काष्ठा enetc_ndev_priv *priv)
अणु
	u32 reg;

	reg = enetc_port_rd(&priv->si->hw, ENETC_PSIDCAPR);
	priv->psfp_cap.max_streamid = reg & ENETC_PSIDCAPR_MSK;
	/* Port stream filter capability */
	reg = enetc_port_rd(&priv->si->hw, ENETC_PSFCAPR);
	priv->psfp_cap.max_psfp_filter = reg & ENETC_PSFCAPR_MSK;
	/* Port stream gate capability */
	reg = enetc_port_rd(&priv->si->hw, ENETC_PSGCAPR);
	priv->psfp_cap.max_psfp_gate = (reg & ENETC_PSGCAPR_SGIT_MSK);
	priv->psfp_cap.max_psfp_gatelist = (reg & ENETC_PSGCAPR_GCL_MSK) >> 16;
	/* Port flow meter capability */
	reg = enetc_port_rd(&priv->si->hw, ENETC_PFMCAPR);
	priv->psfp_cap.max_psfp_meter = reg & ENETC_PFMCAPR_MSK;
पूर्ण

अटल अंतरभूत पूर्णांक enetc_psfp_enable(काष्ठा enetc_ndev_priv *priv)
अणु
	काष्ठा enetc_hw *hw = &priv->si->hw;
	पूर्णांक err;

	enetc_get_max_cap(priv);

	err = enetc_psfp_init(priv);
	अगर (err)
		वापस err;

	enetc_wr(hw, ENETC_PPSFPMR, enetc_rd(hw, ENETC_PPSFPMR) |
		 ENETC_PPSFPMR_PSFPEN | ENETC_PPSFPMR_VS |
		 ENETC_PPSFPMR_PVC | ENETC_PPSFPMR_PVZC);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक enetc_psfp_disable(काष्ठा enetc_ndev_priv *priv)
अणु
	काष्ठा enetc_hw *hw = &priv->si->hw;
	पूर्णांक err;

	err = enetc_psfp_clean(priv);
	अगर (err)
		वापस err;

	enetc_wr(hw, ENETC_PPSFPMR, enetc_rd(hw, ENETC_PPSFPMR) &
		 ~ENETC_PPSFPMR_PSFPEN & ~ENETC_PPSFPMR_VS &
		 ~ENETC_PPSFPMR_PVC & ~ENETC_PPSFPMR_PVZC);

	स_रखो(&priv->psfp_cap, 0, माप(काष्ठा psfp_cap));

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा enetc_setup_tc_taprio(ndev, type_data) -EOPNOTSUPP
#घोषणा enetc_sched_speed_set(priv, speed) (व्योम)0
#घोषणा enetc_setup_tc_cbs(ndev, type_data) -EOPNOTSUPP
#घोषणा enetc_setup_tc_txसमय(ndev, type_data) -EOPNOTSUPP
#घोषणा enetc_setup_tc_psfp(ndev, type_data) -EOPNOTSUPP
#घोषणा enetc_setup_tc_block_cb शून्य

#घोषणा enetc_get_max_cap(p)		\
	स_रखो(&((p)->psfp_cap), 0, माप(काष्ठा psfp_cap))

अटल अंतरभूत पूर्णांक enetc_psfp_enable(काष्ठा enetc_ndev_priv *priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक enetc_psfp_disable(काष्ठा enetc_ndev_priv *priv)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
