<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************
  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#अगर_अघोषित __STMMAC_H__
#घोषणा __STMMAC_H__

#घोषणा STMMAC_RESOURCE_NAME   "stmmaceth"
#घोषणा DRV_MODULE_VERSION	"Jan_2016"

#समावेश <linux/clk.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/sपंचांगmac.h>
#समावेश <linux/phylink.h>
#समावेश <linux/pci.h>
#समावेश "common.h"
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/reset.h>
#समावेश <net/page_pool.h>

काष्ठा sपंचांगmac_resources अणु
	व्योम __iomem *addr;
	u8 mac[ETH_ALEN];
	पूर्णांक wol_irq;
	पूर्णांक lpi_irq;
	पूर्णांक irq;
	पूर्णांक sfty_ce_irq;
	पूर्णांक sfty_ue_irq;
	पूर्णांक rx_irq[MTL_MAX_RX_QUEUES];
	पूर्णांक tx_irq[MTL_MAX_TX_QUEUES];
पूर्ण;

क्रमागत sपंचांगmac_txbuf_type अणु
	STMMAC_TXBUF_T_SKB,
	STMMAC_TXBUF_T_XDP_TX,
	STMMAC_TXBUF_T_XDP_NDO,
	STMMAC_TXBUF_T_XSK_TX,
पूर्ण;

काष्ठा sपंचांगmac_tx_info अणु
	dma_addr_t buf;
	bool map_as_page;
	अचिन्हित len;
	bool last_segment;
	bool is_jumbo;
	क्रमागत sपंचांगmac_txbuf_type buf_type;
पूर्ण;

#घोषणा STMMAC_TBS_AVAIL	BIT(0)
#घोषणा STMMAC_TBS_EN		BIT(1)

/* Frequently used values are kept adjacent क्रम cache effect */
काष्ठा sपंचांगmac_tx_queue अणु
	u32 tx_count_frames;
	पूर्णांक tbs;
	काष्ठा hrसमयr txसमयr;
	u32 queue_index;
	काष्ठा sपंचांगmac_priv *priv_data;
	काष्ठा dma_extended_desc *dma_etx ____cacheline_aligned_in_smp;
	काष्ठा dma_edesc *dma_entx;
	काष्ठा dma_desc *dma_tx;
	जोड़ अणु
		काष्ठा sk_buff **tx_skbuff;
		काष्ठा xdp_frame **xdpf;
	पूर्ण;
	काष्ठा sपंचांगmac_tx_info *tx_skbuff_dma;
	काष्ठा xsk_buff_pool *xsk_pool;
	u32 xsk_frames_करोne;
	अचिन्हित पूर्णांक cur_tx;
	अचिन्हित पूर्णांक dirty_tx;
	dma_addr_t dma_tx_phy;
	u32 tx_tail_addr;
	u32 mss;
पूर्ण;

काष्ठा sपंचांगmac_rx_buffer अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा page *page;
			dma_addr_t addr;
			__u32 page_offset;
		पूर्ण;
		काष्ठा xdp_buff *xdp;
	पूर्ण;
	काष्ठा page *sec_page;
	dma_addr_t sec_addr;
पूर्ण;

काष्ठा sपंचांगmac_rx_queue अणु
	u32 rx_count_frames;
	u32 queue_index;
	काष्ठा xdp_rxq_info xdp_rxq;
	काष्ठा xsk_buff_pool *xsk_pool;
	काष्ठा page_pool *page_pool;
	काष्ठा sपंचांगmac_rx_buffer *buf_pool;
	काष्ठा sपंचांगmac_priv *priv_data;
	काष्ठा dma_extended_desc *dma_erx;
	काष्ठा dma_desc *dma_rx ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक cur_rx;
	अचिन्हित पूर्णांक dirty_rx;
	अचिन्हित पूर्णांक buf_alloc_num;
	u32 rx_zeroc_thresh;
	dma_addr_t dma_rx_phy;
	u32 rx_tail_addr;
	अचिन्हित पूर्णांक state_saved;
	काष्ठा अणु
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक len;
		अचिन्हित पूर्णांक error;
	पूर्ण state;
पूर्ण;

काष्ठा sपंचांगmac_channel अणु
	काष्ठा napi_काष्ठा rx_napi ____cacheline_aligned_in_smp;
	काष्ठा napi_काष्ठा tx_napi ____cacheline_aligned_in_smp;
	काष्ठा napi_काष्ठा rxtx_napi ____cacheline_aligned_in_smp;
	काष्ठा sपंचांगmac_priv *priv_data;
	spinlock_t lock;
	u32 index;
पूर्ण;

काष्ठा sपंचांगmac_tc_entry अणु
	bool in_use;
	bool in_hw;
	bool is_last;
	bool is_frag;
	व्योम *frag_ptr;
	अचिन्हित पूर्णांक table_pos;
	u32 handle;
	u32 prio;
	काष्ठा अणु
		u32 match_data;
		u32 match_en;
		u8 af:1;
		u8 rf:1;
		u8 im:1;
		u8 nc:1;
		u8 res1:4;
		u8 frame_offset;
		u8 ok_index;
		u8 dma_ch_no;
		u32 res2;
	पूर्ण __packed val;
पूर्ण;

#घोषणा STMMAC_PPS_MAX		4
काष्ठा sपंचांगmac_pps_cfg अणु
	bool available;
	काष्ठा बारpec64 start;
	काष्ठा बारpec64 period;
पूर्ण;

काष्ठा sपंचांगmac_rss अणु
	पूर्णांक enable;
	u8 key[STMMAC_RSS_HASH_KEY_SIZE];
	u32 table[STMMAC_RSS_MAX_TABLE_SIZE];
पूर्ण;

#घोषणा STMMAC_FLOW_ACTION_DROP		BIT(0)
काष्ठा sपंचांगmac_flow_entry अणु
	अचिन्हित दीर्घ cookie;
	अचिन्हित दीर्घ action;
	u8 ip_proto;
	पूर्णांक in_use;
	पूर्णांक idx;
	पूर्णांक is_l4;
पूर्ण;

काष्ठा sपंचांगmac_priv अणु
	/* Frequently used values are kept adjacent क्रम cache effect */
	u32 tx_coal_frames[MTL_MAX_TX_QUEUES];
	u32 tx_coal_समयr[MTL_MAX_TX_QUEUES];
	u32 rx_coal_frames[MTL_MAX_TX_QUEUES];

	पूर्णांक tx_coalesce;
	पूर्णांक hwts_tx_en;
	bool tx_path_in_lpi_mode;
	bool tso;
	पूर्णांक sph;
	पूर्णांक sph_cap;
	u32 sarc_type;

	अचिन्हित पूर्णांक dma_buf_sz;
	अचिन्हित पूर्णांक rx_copyअवरोध;
	u32 rx_riwt[MTL_MAX_TX_QUEUES];
	पूर्णांक hwts_rx_en;

	व्योम __iomem *ioaddr;
	काष्ठा net_device *dev;
	काष्ठा device *device;
	काष्ठा mac_device_info *hw;
	पूर्णांक (*hwअगर_quirks)(काष्ठा sपंचांगmac_priv *priv);
	काष्ठा mutex lock;

	/* RX Queue */
	काष्ठा sपंचांगmac_rx_queue rx_queue[MTL_MAX_RX_QUEUES];
	अचिन्हित पूर्णांक dma_rx_size;

	/* TX Queue */
	काष्ठा sपंचांगmac_tx_queue tx_queue[MTL_MAX_TX_QUEUES];
	अचिन्हित पूर्णांक dma_tx_size;

	/* Generic channel क्रम NAPI */
	काष्ठा sपंचांगmac_channel channel[STMMAC_CH_MAX];

	पूर्णांक speed;
	अचिन्हित पूर्णांक flow_ctrl;
	अचिन्हित पूर्णांक छोड़ो;
	काष्ठा mii_bus *mii;
	पूर्णांक mii_irq[PHY_MAX_ADDR];

	काष्ठा phylink_config phylink_config;
	काष्ठा phylink *phylink;

	काष्ठा sपंचांगmac_extra_stats xstats ____cacheline_aligned_in_smp;
	काष्ठा sपंचांगmac_safety_stats sstats;
	काष्ठा plat_sपंचांगmacenet_data *plat;
	काष्ठा dma_features dma_cap;
	काष्ठा sपंचांगmac_counters mmc;
	पूर्णांक hw_cap_support;
	पूर्णांक synopsys_id;
	u32 msg_enable;
	पूर्णांक wolopts;
	पूर्णांक wol_irq;
	पूर्णांक clk_csr;
	काष्ठा समयr_list eee_ctrl_समयr;
	पूर्णांक lpi_irq;
	पूर्णांक eee_enabled;
	पूर्णांक eee_active;
	पूर्णांक tx_lpi_समयr;
	पूर्णांक tx_lpi_enabled;
	पूर्णांक eee_tw_समयr;
	bool eee_sw_समयr_en;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक chain_mode;
	पूर्णांक extend_desc;
	काष्ठा hwtstamp_config tstamp_config;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_घड़ी_ops;
	अचिन्हित पूर्णांक शेष_addend;
	u32 sub_second_inc;
	u32 sysसमय_flags;
	u32 adv_ts;
	पूर्णांक use_riwt;
	पूर्णांक irq_wake;
	spinlock_t ptp_lock;
	/* Protects auxiliary snapshot रेजिस्टरs from concurrent access. */
	काष्ठा mutex aux_ts_lock;

	व्योम __iomem *mmcaddr;
	व्योम __iomem *ptpaddr;
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	पूर्णांक sfty_ce_irq;
	पूर्णांक sfty_ue_irq;
	पूर्णांक rx_irq[MTL_MAX_RX_QUEUES];
	पूर्णांक tx_irq[MTL_MAX_TX_QUEUES];
	/*irq name */
	अक्षर पूर्णांक_name_mac[IFNAMSIZ + 9];
	अक्षर पूर्णांक_name_wol[IFNAMSIZ + 9];
	अक्षर पूर्णांक_name_lpi[IFNAMSIZ + 9];
	अक्षर पूर्णांक_name_sfty_ce[IFNAMSIZ + 10];
	अक्षर पूर्णांक_name_sfty_ue[IFNAMSIZ + 10];
	अक्षर पूर्णांक_name_rx_irq[MTL_MAX_TX_QUEUES][IFNAMSIZ + 14];
	अक्षर पूर्णांक_name_tx_irq[MTL_MAX_TX_QUEUES][IFNAMSIZ + 18];

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dbgfs_dir;
#पूर्ण_अगर

	अचिन्हित दीर्घ state;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा service_task;

	/* Workqueue क्रम handling FPE hand-shaking */
	अचिन्हित दीर्घ fpe_task_state;
	काष्ठा workqueue_काष्ठा *fpe_wq;
	काष्ठा work_काष्ठा fpe_task;
	अक्षर wq_name[IFNAMSIZ + 4];

	/* TC Handling */
	अचिन्हित पूर्णांक tc_entries_max;
	अचिन्हित पूर्णांक tc_off_max;
	काष्ठा sपंचांगmac_tc_entry *tc_entries;
	अचिन्हित पूर्णांक flow_entries_max;
	काष्ठा sपंचांगmac_flow_entry *flow_entries;

	/* Pulse Per Second output */
	काष्ठा sपंचांगmac_pps_cfg pps[STMMAC_PPS_MAX];

	/* Receive Side Scaling */
	काष्ठा sपंचांगmac_rss rss;

	/* XDP BPF Program */
	अचिन्हित दीर्घ *af_xdp_zc_qps;
	काष्ठा bpf_prog *xdp_prog;
पूर्ण;

क्रमागत sपंचांगmac_state अणु
	STMMAC_DOWN,
	STMMAC_RESET_REQUESTED,
	STMMAC_RESETING,
	STMMAC_SERVICE_SCHED,
पूर्ण;

पूर्णांक sपंचांगmac_mdio_unरेजिस्टर(काष्ठा net_device *ndev);
पूर्णांक sपंचांगmac_mdio_रेजिस्टर(काष्ठा net_device *ndev);
पूर्णांक sपंचांगmac_mdio_reset(काष्ठा mii_bus *mii);
व्योम sपंचांगmac_set_ethtool_ops(काष्ठा net_device *netdev);

व्योम sपंचांगmac_ptp_रेजिस्टर(काष्ठा sपंचांगmac_priv *priv);
व्योम sपंचांगmac_ptp_unरेजिस्टर(काष्ठा sपंचांगmac_priv *priv);
पूर्णांक sपंचांगmac_खोलो(काष्ठा net_device *dev);
पूर्णांक sपंचांगmac_release(काष्ठा net_device *dev);
पूर्णांक sपंचांगmac_resume(काष्ठा device *dev);
पूर्णांक sपंचांगmac_suspend(काष्ठा device *dev);
पूर्णांक sपंचांगmac_dvr_हटाओ(काष्ठा device *dev);
पूर्णांक sपंचांगmac_dvr_probe(काष्ठा device *device,
		     काष्ठा plat_sपंचांगmacenet_data *plat_dat,
		     काष्ठा sपंचांगmac_resources *res);
व्योम sपंचांगmac_disable_eee_mode(काष्ठा sपंचांगmac_priv *priv);
bool sपंचांगmac_eee_init(काष्ठा sपंचांगmac_priv *priv);
पूर्णांक sपंचांगmac_reinit_queues(काष्ठा net_device *dev, u32 rx_cnt, u32 tx_cnt);
पूर्णांक sपंचांगmac_reinit_ringparam(काष्ठा net_device *dev, u32 rx_size, u32 tx_size);
पूर्णांक sपंचांगmac_bus_clks_config(काष्ठा sपंचांगmac_priv *priv, bool enabled);
व्योम sपंचांगmac_fpe_handshake(काष्ठा sपंचांगmac_priv *priv, bool enable);

अटल अंतरभूत bool sपंचांगmac_xdp_is_enabled(काष्ठा sपंचांगmac_priv *priv)
अणु
	वापस !!priv->xdp_prog;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sपंचांगmac_rx_offset(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (sपंचांगmac_xdp_is_enabled(priv))
		वापस XDP_PACKET_HEADROOM;

	वापस 0;
पूर्ण

व्योम sपंचांगmac_disable_rx_queue(काष्ठा sपंचांगmac_priv *priv, u32 queue);
व्योम sपंचांगmac_enable_rx_queue(काष्ठा sपंचांगmac_priv *priv, u32 queue);
व्योम sपंचांगmac_disable_tx_queue(काष्ठा sपंचांगmac_priv *priv, u32 queue);
व्योम sपंचांगmac_enable_tx_queue(काष्ठा sपंचांगmac_priv *priv, u32 queue);
पूर्णांक sपंचांगmac_xsk_wakeup(काष्ठा net_device *dev, u32 queue, u32 flags);

#अगर IS_ENABLED(CONFIG_STMMAC_SELFTESTS)
व्योम sपंचांगmac_selftest_run(काष्ठा net_device *dev,
			 काष्ठा ethtool_test *etest, u64 *buf);
व्योम sपंचांगmac_selftest_get_strings(काष्ठा sपंचांगmac_priv *priv, u8 *data);
पूर्णांक sपंचांगmac_selftest_get_count(काष्ठा sपंचांगmac_priv *priv);
#अन्यथा
अटल अंतरभूत व्योम sपंचांगmac_selftest_run(काष्ठा net_device *dev,
				       काष्ठा ethtool_test *etest, u64 *buf)
अणु
	/* Not enabled */
पूर्ण
अटल अंतरभूत व्योम sपंचांगmac_selftest_get_strings(काष्ठा sपंचांगmac_priv *priv,
					       u8 *data)
अणु
	/* Not enabled */
पूर्ण
अटल अंतरभूत पूर्णांक sपंचांगmac_selftest_get_count(काष्ठा sपंचांगmac_priv *priv)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_STMMAC_SELFTESTS */

#पूर्ण_अगर /* __STMMAC_H__ */
