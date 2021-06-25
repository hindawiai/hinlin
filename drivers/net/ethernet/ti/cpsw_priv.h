<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Texas Instruments Ethernet Switch Driver
 */

#अगर_अघोषित DRIVERS_NET_ETHERNET_TI_CPSW_PRIV_H_
#घोषणा DRIVERS_NET_ETHERNET_TI_CPSW_PRIV_H_

#समावेश "davinci_cpdma.h"

#घोषणा CPSW_DEBUG	(NETIF_MSG_HW		| NETIF_MSG_WOL		| \
			 NETIF_MSG_DRV		| NETIF_MSG_LINK	| \
			 NETIF_MSG_IFUP		| NETIF_MSG_INTR	| \
			 NETIF_MSG_PROBE	| NETIF_MSG_TIMER	| \
			 NETIF_MSG_IFDOWN	| NETIF_MSG_RX_ERR	| \
			 NETIF_MSG_TX_ERR	| NETIF_MSG_TX_DONE	| \
			 NETIF_MSG_PKTDATA	| NETIF_MSG_TX_QUEUED	| \
			 NETIF_MSG_RX_STATUS)

#घोषणा cpsw_info(priv, type, क्रमmat, ...)		\
करो अणु								\
	अगर (netअगर_msg_##type(priv) && net_ratelimit())		\
		dev_info(priv->dev, क्रमmat, ## __VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा cpsw_err(priv, type, क्रमmat, ...)		\
करो अणु								\
	अगर (netअगर_msg_##type(priv) && net_ratelimit())		\
		dev_err(priv->dev, क्रमmat, ## __VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा cpsw_dbg(priv, type, क्रमmat, ...)		\
करो अणु								\
	अगर (netअगर_msg_##type(priv) && net_ratelimit())		\
		dev_dbg(priv->dev, क्रमmat, ## __VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा cpsw_notice(priv, type, क्रमmat, ...)		\
करो अणु								\
	अगर (netअगर_msg_##type(priv) && net_ratelimit())		\
		dev_notice(priv->dev, क्रमmat, ## __VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा ALE_ALL_PORTS		0x7

#घोषणा CPSW_MAJOR_VERSION(reg)		(reg >> 8 & 0x7)
#घोषणा CPSW_MINOR_VERSION(reg)		(reg & 0xff)
#घोषणा CPSW_RTL_VERSION(reg)		((reg >> 11) & 0x1f)

#घोषणा CPSW_VERSION_1		0x19010a
#घोषणा CPSW_VERSION_2		0x19010c
#घोषणा CPSW_VERSION_3		0x19010f
#घोषणा CPSW_VERSION_4		0x190112

#घोषणा HOST_PORT_NUM		0
#घोषणा CPSW_ALE_PORTS_NUM	3
#घोषणा CPSW_SLAVE_PORTS_NUM	2
#घोषणा SLIVER_SIZE		0x40

#घोषणा CPSW1_HOST_PORT_OFFSET	0x028
#घोषणा CPSW1_SLAVE_OFFSET	0x050
#घोषणा CPSW1_SLAVE_SIZE	0x040
#घोषणा CPSW1_CPDMA_OFFSET	0x100
#घोषणा CPSW1_STATERAM_OFFSET	0x200
#घोषणा CPSW1_HW_STATS		0x400
#घोषणा CPSW1_CPTS_OFFSET	0x500
#घोषणा CPSW1_ALE_OFFSET	0x600
#घोषणा CPSW1_SLIVER_OFFSET	0x700
#घोषणा CPSW1_WR_OFFSET		0x900

#घोषणा CPSW2_HOST_PORT_OFFSET	0x108
#घोषणा CPSW2_SLAVE_OFFSET	0x200
#घोषणा CPSW2_SLAVE_SIZE	0x100
#घोषणा CPSW2_CPDMA_OFFSET	0x800
#घोषणा CPSW2_HW_STATS		0x900
#घोषणा CPSW2_STATERAM_OFFSET	0xa00
#घोषणा CPSW2_CPTS_OFFSET	0xc00
#घोषणा CPSW2_ALE_OFFSET	0xd00
#घोषणा CPSW2_SLIVER_OFFSET	0xd80
#घोषणा CPSW2_BD_OFFSET		0x2000
#घोषणा CPSW2_WR_OFFSET		0x1200

#घोषणा CPDMA_RXTHRESH		0x0c0
#घोषणा CPDMA_RXFREE		0x0e0
#घोषणा CPDMA_TXHDP		0x00
#घोषणा CPDMA_RXHDP		0x20
#घोषणा CPDMA_TXCP		0x40
#घोषणा CPDMA_RXCP		0x60

#घोषणा CPSW_POLL_WEIGHT	64
#घोषणा CPSW_RX_VLAN_ENCAP_HDR_SIZE		4
#घोषणा CPSW_MIN_PACKET_SIZE	(VLAN_ETH_ZLEN)
#घोषणा CPSW_MAX_PACKET_SIZE	(VLAN_ETH_FRAME_LEN +\
				 ETH_FCS_LEN +\
				 CPSW_RX_VLAN_ENCAP_HDR_SIZE)

#घोषणा RX_PRIORITY_MAPPING	0x76543210
#घोषणा TX_PRIORITY_MAPPING	0x33221100
#घोषणा CPDMA_TX_PRIORITY_MAP	0x76543210

#घोषणा CPSW_VLAN_AWARE		BIT(1)
#घोषणा CPSW_RX_VLAN_ENCAP	BIT(2)
#घोषणा CPSW_ALE_VLAN_AWARE	1

#घोषणा CPSW_FIFO_NORMAL_MODE		(0 << 16)
#घोषणा CPSW_FIFO_DUAL_MAC_MODE		(1 << 16)
#घोषणा CPSW_FIFO_RATE_LIMIT_MODE	(2 << 16)

#घोषणा CPSW_INTPACEEN		(0x3f << 16)
#घोषणा CPSW_INTPRESCALE_MASK	(0x7FF << 0)
#घोषणा CPSW_CMINTMAX_CNT	63
#घोषणा CPSW_CMINTMIN_CNT	2
#घोषणा CPSW_CMINTMAX_INTVL	(1000 / CPSW_CMINTMIN_CNT)
#घोषणा CPSW_CMINTMIN_INTVL	((1000 / CPSW_CMINTMAX_CNT) + 1)

#घोषणा IRQ_NUM			2
#घोषणा CPSW_MAX_QUEUES		8
#घोषणा CPSW_CPDMA_DESCS_POOL_SIZE_DEFAULT 256
#घोषणा CPSW_ALE_AGEOUT_DEFAULT		10 /* sec */
#घोषणा CPSW_FIFO_QUEUE_TYPE_SHIFT	16
#घोषणा CPSW_FIFO_SHAPE_EN_SHIFT	16
#घोषणा CPSW_FIFO_RATE_EN_SHIFT		20
#घोषणा CPSW_TC_NUM			4
#घोषणा CPSW_FIFO_SHAPERS_NUM		(CPSW_TC_NUM - 1)
#घोषणा CPSW_PCT_MASK			0x7f
#घोषणा CPSW_BD_RAM_SIZE		0x2000

#घोषणा CPSW_RX_VLAN_ENCAP_HDR_PRIO_SHIFT	29
#घोषणा CPSW_RX_VLAN_ENCAP_HDR_PRIO_MSK		GENMASK(2, 0)
#घोषणा CPSW_RX_VLAN_ENCAP_HDR_VID_SHIFT	16
#घोषणा CPSW_RX_VLAN_ENCAP_HDR_PKT_TYPE_SHIFT	8
#घोषणा CPSW_RX_VLAN_ENCAP_HDR_PKT_TYPE_MSK	GENMASK(1, 0)
क्रमागत अणु
	CPSW_RX_VLAN_ENCAP_HDR_PKT_VLAN_TAG = 0,
	CPSW_RX_VLAN_ENCAP_HDR_PKT_RESERV,
	CPSW_RX_VLAN_ENCAP_HDR_PKT_PRIO_TAG,
	CPSW_RX_VLAN_ENCAP_HDR_PKT_UNTAG,
पूर्ण;

काष्ठा cpsw_wr_regs अणु
	u32	id_ver;
	u32	soft_reset;
	u32	control;
	u32	पूर्णांक_control;
	u32	rx_thresh_en;
	u32	rx_en;
	u32	tx_en;
	u32	misc_en;
	u32	mem_allign1[8];
	u32	rx_thresh_stat;
	u32	rx_stat;
	u32	tx_stat;
	u32	misc_stat;
	u32	mem_allign2[8];
	u32	rx_imax;
	u32	tx_imax;

पूर्ण;

काष्ठा cpsw_ss_regs अणु
	u32	id_ver;
	u32	control;
	u32	soft_reset;
	u32	stat_port_en;
	u32	ptype;
	u32	soft_idle;
	u32	thru_rate;
	u32	gap_thresh;
	u32	tx_start_wds;
	u32	flow_control;
	u32	vlan_ltype;
	u32	ts_ltype;
	u32	dlr_ltype;
पूर्ण;

/* CPSW_PORT_V1 */
#घोषणा CPSW1_MAX_BLKS      0x00 /* Maximum FIFO Blocks */
#घोषणा CPSW1_BLK_CNT       0x04 /* FIFO Block Usage Count (Read Only) */
#घोषणा CPSW1_TX_IN_CTL     0x08 /* Transmit FIFO Control */
#घोषणा CPSW1_PORT_VLAN     0x0c /* VLAN Register */
#घोषणा CPSW1_TX_PRI_MAP    0x10 /* Tx Header Priority to Switch Pri Mapping */
#घोषणा CPSW1_TS_CTL        0x14 /* Time Sync Control */
#घोषणा CPSW1_TS_SEQ_LTYPE  0x18 /* Time Sync Sequence ID Offset and Msg Type */
#घोषणा CPSW1_TS_VLAN       0x1c /* Time Sync VLAN1 and VLAN2 */

/* CPSW_PORT_V2 */
#घोषणा CPSW2_CONTROL       0x00 /* Control Register */
#घोषणा CPSW2_MAX_BLKS      0x08 /* Maximum FIFO Blocks */
#घोषणा CPSW2_BLK_CNT       0x0c /* FIFO Block Usage Count (Read Only) */
#घोषणा CPSW2_TX_IN_CTL     0x10 /* Transmit FIFO Control */
#घोषणा CPSW2_PORT_VLAN     0x14 /* VLAN Register */
#घोषणा CPSW2_TX_PRI_MAP    0x18 /* Tx Header Priority to Switch Pri Mapping */
#घोषणा CPSW2_TS_SEQ_MTYPE  0x1c /* Time Sync Sequence ID Offset and Msg Type */

/* CPSW_PORT_V1 and V2 */
#घोषणा SA_LO               0x20 /* CPGMAC_SL Source Address Low */
#घोषणा SA_HI               0x24 /* CPGMAC_SL Source Address High */
#घोषणा SEND_PERCENT        0x28 /* Transmit Queue Send Percentages */

/* CPSW_PORT_V2 only */
#घोषणा RX_DSCP_PRI_MAP0    0x30 /* Rx DSCP Priority to Rx Packet Mapping */
#घोषणा RX_DSCP_PRI_MAP1    0x34 /* Rx DSCP Priority to Rx Packet Mapping */
#घोषणा RX_DSCP_PRI_MAP2    0x38 /* Rx DSCP Priority to Rx Packet Mapping */
#घोषणा RX_DSCP_PRI_MAP3    0x3c /* Rx DSCP Priority to Rx Packet Mapping */
#घोषणा RX_DSCP_PRI_MAP4    0x40 /* Rx DSCP Priority to Rx Packet Mapping */
#घोषणा RX_DSCP_PRI_MAP5    0x44 /* Rx DSCP Priority to Rx Packet Mapping */
#घोषणा RX_DSCP_PRI_MAP6    0x48 /* Rx DSCP Priority to Rx Packet Mapping */
#घोषणा RX_DSCP_PRI_MAP7    0x4c /* Rx DSCP Priority to Rx Packet Mapping */

/* Bit definitions क्रम the CPSW2_CONTROL रेजिस्टर */
#घोषणा PASS_PRI_TAGGED     BIT(24) /* Pass Priority Tagged */
#घोषणा VLAN_LTYPE2_EN      BIT(21) /* VLAN LTYPE 2 enable */
#घोषणा VLAN_LTYPE1_EN      BIT(20) /* VLAN LTYPE 1 enable */
#घोषणा DSCP_PRI_EN         BIT(16) /* DSCP Priority Enable */
#घोषणा TS_107              BIT(15) /* Tyme Sync Dest IP Address 107 */
#घोषणा TS_320              BIT(14) /* Time Sync Dest Port 320 enable */
#घोषणा TS_319              BIT(13) /* Time Sync Dest Port 319 enable */
#घोषणा TS_132              BIT(12) /* Time Sync Dest IP Addr 132 enable */
#घोषणा TS_131              BIT(11) /* Time Sync Dest IP Addr 131 enable */
#घोषणा TS_130              BIT(10) /* Time Sync Dest IP Addr 130 enable */
#घोषणा TS_129              BIT(9)  /* Time Sync Dest IP Addr 129 enable */
#घोषणा TS_TTL_NONZERO      BIT(8)  /* Time Sync Time To Live Non-zero enable */
#घोषणा TS_ANNEX_F_EN       BIT(6)  /* Time Sync Annex F enable */
#घोषणा TS_ANNEX_D_EN       BIT(4)  /* Time Sync Annex D enable */
#घोषणा TS_LTYPE2_EN        BIT(3)  /* Time Sync LTYPE 2 enable */
#घोषणा TS_LTYPE1_EN        BIT(2)  /* Time Sync LTYPE 1 enable */
#घोषणा TS_TX_EN            BIT(1)  /* Time Sync Transmit Enable */
#घोषणा TS_RX_EN            BIT(0)  /* Time Sync Receive Enable */

#घोषणा CTRL_V2_TS_BITS \
	(TS_320 | TS_319 | TS_132 | TS_131 | TS_130 | TS_129 |\
	 TS_TTL_NONZERO  | TS_ANNEX_D_EN | TS_LTYPE1_EN | VLAN_LTYPE1_EN)

#घोषणा CTRL_V2_ALL_TS_MASK (CTRL_V2_TS_BITS | TS_TX_EN | TS_RX_EN)
#घोषणा CTRL_V2_TX_TS_BITS  (CTRL_V2_TS_BITS | TS_TX_EN)
#घोषणा CTRL_V2_RX_TS_BITS  (CTRL_V2_TS_BITS | TS_RX_EN)


#घोषणा CTRL_V3_TS_BITS \
	(TS_107 | TS_320 | TS_319 | TS_132 | TS_131 | TS_130 | TS_129 |\
	 TS_TTL_NONZERO | TS_ANNEX_F_EN | TS_ANNEX_D_EN |\
	 TS_LTYPE1_EN | VLAN_LTYPE1_EN)

#घोषणा CTRL_V3_ALL_TS_MASK (CTRL_V3_TS_BITS | TS_TX_EN | TS_RX_EN)
#घोषणा CTRL_V3_TX_TS_BITS  (CTRL_V3_TS_BITS | TS_TX_EN)
#घोषणा CTRL_V3_RX_TS_BITS  (CTRL_V3_TS_BITS | TS_RX_EN)

/* Bit definitions क्रम the CPSW2_TS_SEQ_MTYPE रेजिस्टर */
#घोषणा TS_SEQ_ID_OFFSET_SHIFT   (16)    /* Time Sync Sequence ID Offset */
#घोषणा TS_SEQ_ID_OFFSET_MASK    (0x3f)
#घोषणा TS_MSG_TYPE_EN_SHIFT     (0)     /* Time Sync Message Type Enable */
#घोषणा TS_MSG_TYPE_EN_MASK      (0xffff)

/* The PTP event messages - Sync, Delay_Req, Pdelay_Req, and Pdelay_Resp. */
#घोषणा EVENT_MSG_BITS ((1<<0) | (1<<1) | (1<<2) | (1<<3))

/* Bit definitions क्रम the CPSW1_TS_CTL रेजिस्टर */
#घोषणा CPSW_V1_TS_RX_EN		BIT(0)
#घोषणा CPSW_V1_TS_TX_EN		BIT(4)
#घोषणा CPSW_V1_MSG_TYPE_OFS		16

/* Bit definitions क्रम the CPSW1_TS_SEQ_LTYPE रेजिस्टर */
#घोषणा CPSW_V1_SEQ_ID_OFS_SHIFT	16

#घोषणा CPSW_MAX_BLKS_TX		15
#घोषणा CPSW_MAX_BLKS_TX_SHIFT		4
#घोषणा CPSW_MAX_BLKS_RX		5

काष्ठा cpsw_host_regs अणु
	u32	max_blks;
	u32	blk_cnt;
	u32	tx_in_ctl;
	u32	port_vlan;
	u32	tx_pri_map;
	u32	cpdma_tx_pri_map;
	u32	cpdma_rx_chan_map;
पूर्ण;

काष्ठा cpsw_slave_data अणु
	काष्ठा device_node *slave_node;
	काष्ठा device_node *phy_node;
	अक्षर		phy_id[MII_BUS_ID_SIZE];
	phy_पूर्णांकerface_t	phy_अगर;
	u8		mac_addr[ETH_ALEN];
	u16		dual_emac_res_vlan;	/* Reserved VLAN क्रम DualEMAC */
	काष्ठा phy	*अगरphy;
	bool		disabled;
पूर्ण;

काष्ठा cpsw_platक्रमm_data अणु
	काष्ठा cpsw_slave_data	*slave_data;
	u32	ss_reg_ofs;	/* Subप्रणाली control रेजिस्टर offset */
	u32	channels;	/* number of cpdma channels (symmetric) */
	u32	slaves;		/* number of slave cpgmac ports */
	u32	active_slave;/* समय stamping, ethtool and SIOCGMIIPHY slave */
	u32	bd_ram_size;	/*buffer descriptor ram size */
	u32	mac_control;	/* Mac control रेजिस्टर */
	u16	शेष_vlan;	/* Def VLAN क्रम ALE lookup in VLAN aware mode*/
	bool	dual_emac;	/* Enable Dual EMAC mode */
पूर्ण;

काष्ठा cpsw_slave अणु
	व्योम __iomem			*regs;
	पूर्णांक				slave_num;
	u32				mac_control;
	काष्ठा cpsw_slave_data		*data;
	काष्ठा phy_device		*phy;
	काष्ठा net_device		*ndev;
	u32				port_vlan;
	काष्ठा cpsw_sl			*mac_sl;
पूर्ण;

अटल अंतरभूत u32 slave_पढ़ो(काष्ठा cpsw_slave *slave, u32 offset)
अणु
	वापस पढ़ोl_relaxed(slave->regs + offset);
पूर्ण

अटल अंतरभूत व्योम slave_ग_लिखो(काष्ठा cpsw_slave *slave, u32 val, u32 offset)
अणु
	ग_लिखोl_relaxed(val, slave->regs + offset);
पूर्ण

काष्ठा cpsw_vector अणु
	काष्ठा cpdma_chan *ch;
	पूर्णांक budget;
पूर्ण;

काष्ठा cpsw_common अणु
	काष्ठा device			*dev;
	काष्ठा cpsw_platक्रमm_data	data;
	काष्ठा napi_काष्ठा		napi_rx;
	काष्ठा napi_काष्ठा		napi_tx;
	काष्ठा cpsw_ss_regs __iomem	*regs;
	काष्ठा cpsw_wr_regs __iomem	*wr_regs;
	u8 __iomem			*hw_stats;
	काष्ठा cpsw_host_regs __iomem	*host_port_regs;
	u32				version;
	u32				coal_पूर्णांकvl;
	u32				bus_freq_mhz;
	पूर्णांक				rx_packet_max;
	पूर्णांक				descs_pool_size;
	काष्ठा cpsw_slave		*slaves;
	काष्ठा cpdma_ctlr		*dma;
	काष्ठा cpsw_vector		txv[CPSW_MAX_QUEUES];
	काष्ठा cpsw_vector		rxv[CPSW_MAX_QUEUES];
	काष्ठा cpsw_ale			*ale;
	bool				quirk_irq;
	bool				rx_irq_disabled;
	bool				tx_irq_disabled;
	u32 irqs_table[IRQ_NUM];
	पूर्णांक misc_irq;
	काष्ठा cpts			*cpts;
	काष्ठा devlink *devlink;
	पूर्णांक				rx_ch_num, tx_ch_num;
	पूर्णांक				speed;
	पूर्णांक				usage_count;
	काष्ठा page_pool		*page_pool[CPSW_MAX_QUEUES];
	u8 br_members;
	काष्ठा net_device *hw_bridge_dev;
	bool ale_bypass;
	u8 base_mac[ETH_ALEN];
पूर्ण;

काष्ठा cpsw_priv अणु
	काष्ठा net_device		*ndev;
	काष्ठा device			*dev;
	u32				msg_enable;
	u8				mac_addr[ETH_ALEN];
	bool				rx_छोड़ो;
	bool				tx_छोड़ो;
	bool				mqprio_hw;
	पूर्णांक				fअगरo_bw[CPSW_TC_NUM];
	पूर्णांक				shp_cfg_speed;
	पूर्णांक				tx_ts_enabled;
	पूर्णांक				rx_ts_enabled;
	काष्ठा bpf_prog			*xdp_prog;
	काष्ठा xdp_rxq_info		xdp_rxq[CPSW_MAX_QUEUES];
	काष्ठा xdp_attachment_info	xdpi;

	u32 emac_port;
	काष्ठा cpsw_common *cpsw;
	पूर्णांक offload_fwd_mark;
पूर्ण;

#घोषणा ndev_to_cpsw(ndev) (((काष्ठा cpsw_priv *)netdev_priv(ndev))->cpsw)
#घोषणा napi_to_cpsw(napi)	container_of(napi, काष्ठा cpsw_common, napi)

बाह्य पूर्णांक (*cpsw_slave_index)(काष्ठा cpsw_common *cpsw,
			       काष्ठा cpsw_priv *priv);

काष्ठा addr_sync_ctx अणु
	काष्ठा net_device *ndev;
	स्थिर u8 *addr;		/* address to be synched */
	पूर्णांक consumed;		/* number of address instances */
	पूर्णांक flush;		/* flush flag */
पूर्ण;

#घोषणा CPSW_XMETA_OFFSET	ALIGN(माप(काष्ठा xdp_frame), माप(दीर्घ))

#घोषणा CPSW_XDP_CONSUMED		1
#घोषणा CPSW_XDP_PASS			0

काष्ठा __aligned(माप(दीर्घ)) cpsw_meta_xdp अणु
	काष्ठा net_device *ndev;
	पूर्णांक ch;
पूर्ण;

/* The buf includes headroom compatible with both skb and xdpf */
#घोषणा CPSW_HEADROOM_NA (max(XDP_PACKET_HEADROOM, NET_SKB_PAD) + NET_IP_ALIGN)
#घोषणा CPSW_HEADROOM  ALIGN(CPSW_HEADROOM_NA, माप(दीर्घ))

अटल अंतरभूत पूर्णांक cpsw_is_xdpf_handle(व्योम *handle)
अणु
	वापस (अचिन्हित दीर्घ)handle & BIT(0);
पूर्ण

अटल अंतरभूत व्योम *cpsw_xdpf_to_handle(काष्ठा xdp_frame *xdpf)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)xdpf | BIT(0));
पूर्ण

अटल अंतरभूत काष्ठा xdp_frame *cpsw_handle_to_xdpf(व्योम *handle)
अणु
	वापस (काष्ठा xdp_frame *)((अचिन्हित दीर्घ)handle & ~BIT(0));
पूर्ण

पूर्णांक cpsw_init_common(काष्ठा cpsw_common *cpsw, व्योम __iomem *ss_regs,
		     पूर्णांक ale_ageout, phys_addr_t desc_mem_phys,
		     पूर्णांक descs_pool_size);
व्योम cpsw_split_res(काष्ठा cpsw_common *cpsw);
पूर्णांक cpsw_fill_rx_channels(काष्ठा cpsw_priv *priv);
व्योम cpsw_पूर्णांकr_enable(काष्ठा cpsw_common *cpsw);
व्योम cpsw_पूर्णांकr_disable(काष्ठा cpsw_common *cpsw);
व्योम cpsw_tx_handler(व्योम *token, पूर्णांक len, पूर्णांक status);
पूर्णांक cpsw_create_xdp_rxqs(काष्ठा cpsw_common *cpsw);
व्योम cpsw_destroy_xdp_rxqs(काष्ठा cpsw_common *cpsw);
पूर्णांक cpsw_nकरो_bpf(काष्ठा net_device *ndev, काष्ठा netdev_bpf *bpf);
पूर्णांक cpsw_xdp_tx_frame(काष्ठा cpsw_priv *priv, काष्ठा xdp_frame *xdpf,
		      काष्ठा page *page, पूर्णांक port);
पूर्णांक cpsw_run_xdp(काष्ठा cpsw_priv *priv, पूर्णांक ch, काष्ठा xdp_buff *xdp,
		 काष्ठा page *page, पूर्णांक port, पूर्णांक *len);
irqवापस_t cpsw_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t cpsw_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t cpsw_misc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
पूर्णांक cpsw_tx_mq_poll(काष्ठा napi_काष्ठा *napi_tx, पूर्णांक budget);
पूर्णांक cpsw_tx_poll(काष्ठा napi_काष्ठा *napi_tx, पूर्णांक budget);
पूर्णांक cpsw_rx_mq_poll(काष्ठा napi_काष्ठा *napi_rx, पूर्णांक budget);
पूर्णांक cpsw_rx_poll(काष्ठा napi_काष्ठा *napi_rx, पूर्णांक budget);
व्योम cpsw_rx_vlan_encap(काष्ठा sk_buff *skb);
व्योम soft_reset(स्थिर अक्षर *module, व्योम __iomem *reg);
व्योम cpsw_set_slave_mac(काष्ठा cpsw_slave *slave, काष्ठा cpsw_priv *priv);
व्योम cpsw_nकरो_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue);
पूर्णांक cpsw_need_resplit(काष्ठा cpsw_common *cpsw);
पूर्णांक cpsw_nकरो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *req, पूर्णांक cmd);
पूर्णांक cpsw_nकरो_set_tx_maxrate(काष्ठा net_device *ndev, पूर्णांक queue, u32 rate);
पूर्णांक cpsw_nकरो_setup_tc(काष्ठा net_device *ndev, क्रमागत tc_setup_type type,
		      व्योम *type_data);
bool cpsw_shp_is_off(काष्ठा cpsw_priv *priv);
व्योम cpsw_cbs_resume(काष्ठा cpsw_slave *slave, काष्ठा cpsw_priv *priv);
व्योम cpsw_mqprio_resume(काष्ठा cpsw_slave *slave, काष्ठा cpsw_priv *priv);

/* ethtool */
u32 cpsw_get_msglevel(काष्ठा net_device *ndev);
व्योम cpsw_set_msglevel(काष्ठा net_device *ndev, u32 value);
पूर्णांक cpsw_get_coalesce(काष्ठा net_device *ndev, काष्ठा ethtool_coalesce *coal);
पूर्णांक cpsw_set_coalesce(काष्ठा net_device *ndev, काष्ठा ethtool_coalesce *coal);
पूर्णांक cpsw_get_sset_count(काष्ठा net_device *ndev, पूर्णांक sset);
व्योम cpsw_get_strings(काष्ठा net_device *ndev, u32 stringset, u8 *data);
व्योम cpsw_get_ethtool_stats(काष्ठा net_device *ndev,
			    काष्ठा ethtool_stats *stats, u64 *data);
व्योम cpsw_get_छोड़ोparam(काष्ठा net_device *ndev,
			 काष्ठा ethtool_छोड़ोparam *छोड़ो);
व्योम cpsw_get_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol);
पूर्णांक cpsw_set_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol);
पूर्णांक cpsw_get_regs_len(काष्ठा net_device *ndev);
व्योम cpsw_get_regs(काष्ठा net_device *ndev, काष्ठा ethtool_regs *regs, व्योम *p);
पूर्णांक cpsw_ethtool_op_begin(काष्ठा net_device *ndev);
व्योम cpsw_ethtool_op_complete(काष्ठा net_device *ndev);
व्योम cpsw_get_channels(काष्ठा net_device *ndev, काष्ठा ethtool_channels *ch);
पूर्णांक cpsw_get_link_ksettings(काष्ठा net_device *ndev,
			    काष्ठा ethtool_link_ksettings *ecmd);
पूर्णांक cpsw_set_link_ksettings(काष्ठा net_device *ndev,
			    स्थिर काष्ठा ethtool_link_ksettings *ecmd);
पूर्णांक cpsw_get_eee(काष्ठा net_device *ndev, काष्ठा ethtool_eee *edata);
पूर्णांक cpsw_set_eee(काष्ठा net_device *ndev, काष्ठा ethtool_eee *edata);
पूर्णांक cpsw_nway_reset(काष्ठा net_device *ndev);
व्योम cpsw_get_ringparam(काष्ठा net_device *ndev,
			काष्ठा ethtool_ringparam *ering);
पूर्णांक cpsw_set_ringparam(काष्ठा net_device *ndev,
		       काष्ठा ethtool_ringparam *ering);
पूर्णांक cpsw_set_channels_common(काष्ठा net_device *ndev,
			     काष्ठा ethtool_channels *chs,
			     cpdma_handler_fn rx_handler);
पूर्णांक cpsw_get_ts_info(काष्ठा net_device *ndev, काष्ठा ethtool_ts_info *info);

#पूर्ण_अगर /* DRIVERS_NET_ETHERNET_TI_CPSW_PRIV_H_ */
