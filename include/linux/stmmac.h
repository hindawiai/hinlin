<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************

  Header file क्रम sपंचांगmac platक्रमm data

  Copyright (C) 2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#अगर_अघोषित __STMMAC_PLATFORM_DATA
#घोषणा __STMMAC_PLATFORM_DATA

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>

#घोषणा MTL_MAX_RX_QUEUES	8
#घोषणा MTL_MAX_TX_QUEUES	8
#घोषणा STMMAC_CH_MAX		8

#घोषणा STMMAC_RX_COE_NONE	0
#घोषणा STMMAC_RX_COE_TYPE1	1
#घोषणा STMMAC_RX_COE_TYPE2	2

/* Define the macros क्रम CSR घड़ी range parameters to be passed by
 * platक्रमm code.
 * This could also be configured at run समय using CPU freq framework. */

/* MDC Clock Selection define*/
#घोषणा	STMMAC_CSR_60_100M	0x0	/* MDC = clk_scr_i/42 */
#घोषणा	STMMAC_CSR_100_150M	0x1	/* MDC = clk_scr_i/62 */
#घोषणा	STMMAC_CSR_20_35M	0x2	/* MDC = clk_scr_i/16 */
#घोषणा	STMMAC_CSR_35_60M	0x3	/* MDC = clk_scr_i/26 */
#घोषणा	STMMAC_CSR_150_250M	0x4	/* MDC = clk_scr_i/102 */
#घोषणा	STMMAC_CSR_250_300M	0x5	/* MDC = clk_scr_i/122 */

/* MTL algorithms identअगरiers */
#घोषणा MTL_TX_ALGORITHM_WRR	0x0
#घोषणा MTL_TX_ALGORITHM_WFQ	0x1
#घोषणा MTL_TX_ALGORITHM_DWRR	0x2
#घोषणा MTL_TX_ALGORITHM_SP	0x3
#घोषणा MTL_RX_ALGORITHM_SP	0x4
#घोषणा MTL_RX_ALGORITHM_WSP	0x5

/* RX/TX Queue Mode */
#घोषणा MTL_QUEUE_AVB		0x0
#घोषणा MTL_QUEUE_DCB		0x1

/* The MDC घड़ी could be set higher than the IEEE 802.3
 * specअगरied frequency limit 0f 2.5 MHz, by programming a घड़ी भागider
 * of value dअगरferent than the above defined values. The resultant MDIO
 * घड़ी frequency of 12.5 MHz is applicable क्रम the पूर्णांकerfacing chips
 * supporting higher MDC घड़ीs.
 * The MDC घड़ी selection macros need to be defined क्रम MDC घड़ी rate
 * of 12.5 MHz, corresponding to the following selection.
 */
#घोषणा STMMAC_CSR_I_4		0x8	/* clk_csr_i/4 */
#घोषणा STMMAC_CSR_I_6		0x9	/* clk_csr_i/6 */
#घोषणा STMMAC_CSR_I_8		0xA	/* clk_csr_i/8 */
#घोषणा STMMAC_CSR_I_10		0xB	/* clk_csr_i/10 */
#घोषणा STMMAC_CSR_I_12		0xC	/* clk_csr_i/12 */
#घोषणा STMMAC_CSR_I_14		0xD	/* clk_csr_i/14 */
#घोषणा STMMAC_CSR_I_16		0xE	/* clk_csr_i/16 */
#घोषणा STMMAC_CSR_I_18		0xF	/* clk_csr_i/18 */

/* AXI DMA Burst length supported */
#घोषणा DMA_AXI_BLEN_4		(1 << 1)
#घोषणा DMA_AXI_BLEN_8		(1 << 2)
#घोषणा DMA_AXI_BLEN_16		(1 << 3)
#घोषणा DMA_AXI_BLEN_32		(1 << 4)
#घोषणा DMA_AXI_BLEN_64		(1 << 5)
#घोषणा DMA_AXI_BLEN_128	(1 << 6)
#घोषणा DMA_AXI_BLEN_256	(1 << 7)
#घोषणा DMA_AXI_BLEN_ALL (DMA_AXI_BLEN_4 | DMA_AXI_BLEN_8 | DMA_AXI_BLEN_16 \
			| DMA_AXI_BLEN_32 | DMA_AXI_BLEN_64 \
			| DMA_AXI_BLEN_128 | DMA_AXI_BLEN_256)

/* Platfrom data क्रम platक्रमm device काष्ठाure's platक्रमm_data field */

काष्ठा sपंचांगmac_mdio_bus_data अणु
	अचिन्हित पूर्णांक phy_mask;
	अचिन्हित पूर्णांक has_xpcs;
	अचिन्हित पूर्णांक xpcs_an_inband;
	पूर्णांक *irqs;
	पूर्णांक probed_phy_irq;
	bool needs_reset;
पूर्ण;

काष्ठा sपंचांगmac_dma_cfg अणु
	पूर्णांक pbl;
	पूर्णांक txpbl;
	पूर्णांक rxpbl;
	bool pblx8;
	पूर्णांक fixed_burst;
	पूर्णांक mixed_burst;
	bool aal;
	bool eame;
	bool multi_msi_en;
	bool dche;
पूर्ण;

#घोषणा AXI_BLEN	7
काष्ठा sपंचांगmac_axi अणु
	bool axi_lpi_en;
	bool axi_xit_frm;
	u32 axi_wr_osr_lmt;
	u32 axi_rd_osr_lmt;
	bool axi_kbbe;
	u32 axi_blen[AXI_BLEN];
	bool axi_fb;
	bool axi_mb;
	bool axi_rb;
पूर्ण;

#घोषणा EST_GCL		1024
काष्ठा sपंचांगmac_est अणु
	पूर्णांक enable;
	u32 btr_offset[2];
	u32 btr[2];
	u32 ctr[2];
	u32 ter;
	u32 gcl_unaligned[EST_GCL];
	u32 gcl[EST_GCL];
	u32 gcl_size;
पूर्ण;

काष्ठा sपंचांगmac_rxq_cfg अणु
	u8 mode_to_use;
	u32 chan;
	u8 pkt_route;
	bool use_prio;
	u32 prio;
पूर्ण;

काष्ठा sपंचांगmac_txq_cfg अणु
	u32 weight;
	u8 mode_to_use;
	/* Credit Base Shaper parameters */
	u32 send_slope;
	u32 idle_slope;
	u32 high_credit;
	u32 low_credit;
	bool use_prio;
	u32 prio;
	पूर्णांक tbs_en;
पूर्ण;

/* FPE link state */
क्रमागत sपंचांगmac_fpe_state अणु
	FPE_STATE_OFF = 0,
	FPE_STATE_CAPABLE = 1,
	FPE_STATE_ENTERING_ON = 2,
	FPE_STATE_ON = 3,
पूर्ण;

/* FPE link-partner hand-shaking mPacket type */
क्रमागत sपंचांगmac_mpacket_type अणु
	MPACKET_VERIFY = 0,
	MPACKET_RESPONSE = 1,
पूर्ण;

क्रमागत sपंचांगmac_fpe_task_state_t अणु
	__FPE_REMOVING,
	__FPE_TASK_SCHED,
पूर्ण;

काष्ठा sपंचांगmac_fpe_cfg अणु
	bool enable;				/* FPE enable */
	bool hs_enable;				/* FPE handshake enable */
	क्रमागत sपंचांगmac_fpe_state lp_fpe_state;	/* Link Partner FPE state */
	क्रमागत sपंचांगmac_fpe_state lo_fpe_state;	/* Local station FPE state */
पूर्ण;

काष्ठा plat_sपंचांगmacenet_data अणु
	पूर्णांक bus_id;
	पूर्णांक phy_addr;
	पूर्णांक पूर्णांकerface;
	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	काष्ठा sपंचांगmac_mdio_bus_data *mdio_bus_data;
	काष्ठा device_node *phy_node;
	काष्ठा device_node *phylink_node;
	काष्ठा device_node *mdio_node;
	काष्ठा sपंचांगmac_dma_cfg *dma_cfg;
	काष्ठा sपंचांगmac_est *est;
	काष्ठा sपंचांगmac_fpe_cfg *fpe_cfg;
	पूर्णांक clk_csr;
	पूर्णांक has_gmac;
	पूर्णांक enh_desc;
	पूर्णांक tx_coe;
	पूर्णांक rx_coe;
	पूर्णांक bugged_jumbo;
	पूर्णांक pmt;
	पूर्णांक क्रमce_sf_dma_mode;
	पूर्णांक क्रमce_thresh_dma_mode;
	पूर्णांक riwt_off;
	पूर्णांक max_speed;
	पूर्णांक maxmtu;
	पूर्णांक multicast_filter_bins;
	पूर्णांक unicast_filter_entries;
	पूर्णांक tx_fअगरo_size;
	पूर्णांक rx_fअगरo_size;
	u32 addr64;
	u32 rx_queues_to_use;
	u32 tx_queues_to_use;
	u8 rx_sched_algorithm;
	u8 tx_sched_algorithm;
	काष्ठा sपंचांगmac_rxq_cfg rx_queues_cfg[MTL_MAX_RX_QUEUES];
	काष्ठा sपंचांगmac_txq_cfg tx_queues_cfg[MTL_MAX_TX_QUEUES];
	व्योम (*fix_mac_speed)(व्योम *priv, अचिन्हित पूर्णांक speed);
	पूर्णांक (*serdes_घातerup)(काष्ठा net_device *ndev, व्योम *priv);
	व्योम (*serdes_घातerकरोwn)(काष्ठा net_device *ndev, व्योम *priv);
	व्योम (*ptp_clk_freq_config)(व्योम *priv);
	पूर्णांक (*init)(काष्ठा platक्रमm_device *pdev, व्योम *priv);
	व्योम (*निकास)(काष्ठा platक्रमm_device *pdev, व्योम *priv);
	काष्ठा mac_device_info *(*setup)(व्योम *priv);
	पूर्णांक (*clks_config)(व्योम *priv, bool enabled);
	पूर्णांक (*crosststamp)(kसमय_प्रकार *device, काष्ठा प्रणाली_counterval_t *प्रणाली,
			   व्योम *ctx);
	व्योम *bsp_priv;
	काष्ठा clk *sपंचांगmac_clk;
	काष्ठा clk *pclk;
	काष्ठा clk *clk_ptp_ref;
	अचिन्हित पूर्णांक clk_ptp_rate;
	अचिन्हित पूर्णांक clk_ref_rate;
	s32 ptp_max_adj;
	काष्ठा reset_control *sपंचांगmac_rst;
	काष्ठा sपंचांगmac_axi *axi;
	पूर्णांक has_gmac4;
	bool has_sun8i;
	bool tso_en;
	पूर्णांक rss_en;
	पूर्णांक mac_port_sel_speed;
	bool en_tx_lpi_घड़ीgating;
	पूर्णांक has_xgmac;
	bool vlan_fail_q_en;
	u8 vlan_fail_q;
	अचिन्हित पूर्णांक eee_usecs_rate;
	काष्ठा pci_dev *pdev;
	bool has_crossts;
	पूर्णांक पूर्णांक_snapshot_num;
	पूर्णांक ext_snapshot_num;
	bool ext_snapshot_en;
	bool multi_msi_en;
	पूर्णांक msi_mac_vec;
	पूर्णांक msi_wol_vec;
	पूर्णांक msi_lpi_vec;
	पूर्णांक msi_sfty_ce_vec;
	पूर्णांक msi_sfty_ue_vec;
	पूर्णांक msi_rx_base_vec;
	पूर्णांक msi_tx_base_vec;
पूर्ण;
#पूर्ण_अगर
