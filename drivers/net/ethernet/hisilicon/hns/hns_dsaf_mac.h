<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#अगर_अघोषित _HNS_DSAF_MAC_H
#घोषणा _HNS_DSAF_MAC_H

#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>
#समावेश "hns_dsaf_main.h"

काष्ठा dsaf_device;

#घोषणा MAC_GMAC_SUPPORTED \
	(SUPPORTED_10baseT_Half \
	| SUPPORTED_10baseT_Full \
	| SUPPORTED_100baseT_Half \
	| SUPPORTED_100baseT_Full \
	| SUPPORTED_Autoneg)

#घोषणा MAC_DEFAULT_MTU	(ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN + ETH_DATA_LEN)
#घोषणा MAC_MAX_MTU		9600
#घोषणा MAC_MAX_MTU_V2		9728
#घोषणा MAC_MIN_MTU		68
#घोषणा MAC_MAX_MTU_DBG		MAC_DEFAULT_MTU

#घोषणा MAC_DEFAULT_PAUSE_TIME 0xffff

#घोषणा MAC_GMAC_IDX 0
#घोषणा MAC_XGMAC_IDX 1

#घोषणा ETH_STATIC_REG	 1
#घोषणा ETH_DUMP_REG	 5
/* check mac addr broadcast */
#घोषणा MAC_IS_BROADCAST(p)	((*(p) == 0xff) && (*((p) + 1) == 0xff) && \
		(*((p) + 2) == 0xff) &&  (*((p) + 3) == 0xff)  && \
		(*((p) + 4) == 0xff) && (*((p) + 5) == 0xff))

/* check mac addr is 01-00-5e-xx-xx-xx*/
#घोषणा MAC_IS_L3_MULTICAST(p) ((*((p) + 0) == 0x01) && \
			(*((p) + 1) == 0x00)   && \
			(*((p) + 2) == 0x5e))

/*check the mac addr is 0 in all bit*/
#घोषणा MAC_IS_ALL_ZEROS(p)   ((*(p) == 0) && (*((p) + 1) == 0) && \
	(*((p) + 2) == 0) && (*((p) + 3) == 0) && \
	(*((p) + 4) == 0) && (*((p) + 5) == 0))

/*check mac addr multicast*/
#घोषणा MAC_IS_MULTICAST(p)	((*((u8 *)((p) + 0)) & 0x01) ? (1) : (0))

काष्ठा mac_priv अणु
	व्योम *mac;
पूर्ण;

/* net speed */
क्रमागत mac_speed अणु
	MAC_SPEED_10	= 10,	   /**< 10 Mbps */
	MAC_SPEED_100	= 100,	  /**< 100 Mbps */
	MAC_SPEED_1000  = 1000,	 /**< 1000 Mbps = 1 Gbps */
	MAC_SPEED_10000 = 10000	 /**< 10000 Mbps = 10 Gbps */
पूर्ण;

/*mac पूर्णांकerface keyword	*/
क्रमागत mac_पूर्णांकf अणु
	MAC_IF_NONE  = 0x00000000,   /**< पूर्णांकerface not invalid */
	MAC_IF_MII   = 0x00010000,   /**< MII पूर्णांकerface */
	MAC_IF_RMII  = 0x00020000,   /**< RMII पूर्णांकerface */
	MAC_IF_SMII  = 0x00030000,   /**< SMII पूर्णांकerface */
	MAC_IF_GMII  = 0x00040000,   /**< GMII पूर्णांकerface */
	MAC_IF_RGMII = 0x00050000,   /**< RGMII पूर्णांकerface */
	MAC_IF_TBI   = 0x00060000,   /**< TBI पूर्णांकerface */
	MAC_IF_RTBI  = 0x00070000,   /**< RTBI पूर्णांकerface */
	MAC_IF_SGMII = 0x00080000,   /**< SGMII पूर्णांकerface */
	MAC_IF_XGMII = 0x00090000,   /**< XGMII पूर्णांकerface */
	MAC_IF_QSGMII = 0x000a0000	/**< QSGMII पूर्णांकerface */
पूर्ण;

/*mac mode */
क्रमागत mac_mode अणु
	/**< Invalid Ethernet mode */
	MAC_MODE_INVALID	 = 0,
	/**<	10 Mbps MII   */
	MAC_MODE_MII_10	  = (MAC_IF_MII   | MAC_SPEED_10),
	/**<   100 Mbps MII   */
	MAC_MODE_MII_100	 = (MAC_IF_MII   | MAC_SPEED_100),
	/**<	10 Mbps RMII  */
	MAC_MODE_RMII_10	 = (MAC_IF_RMII  | MAC_SPEED_10),
	/**<   100 Mbps RMII  */
	MAC_MODE_RMII_100	= (MAC_IF_RMII  | MAC_SPEED_100),
	/**<	10 Mbps SMII  */
	MAC_MODE_SMII_10	 = (MAC_IF_SMII  | MAC_SPEED_10),
	/**<   100 Mbps SMII  */
	MAC_MODE_SMII_100	= (MAC_IF_SMII  | MAC_SPEED_100),
	/**<  1000 Mbps GMII  */
	MAC_MODE_GMII_1000   = (MAC_IF_GMII  | MAC_SPEED_1000),
	/**<	10 Mbps RGMII */
	MAC_MODE_RGMII_10	= (MAC_IF_RGMII | MAC_SPEED_10),
	/**<   100 Mbps RGMII */
	MAC_MODE_RGMII_100   = (MAC_IF_RGMII | MAC_SPEED_100),
	/**<  1000 Mbps RGMII */
	MAC_MODE_RGMII_1000  = (MAC_IF_RGMII | MAC_SPEED_1000),
	/**<  1000 Mbps TBI   */
	MAC_MODE_TBI_1000	= (MAC_IF_TBI   | MAC_SPEED_1000),
	/**<  1000 Mbps RTBI  */
	MAC_MODE_RTBI_1000   = (MAC_IF_RTBI  | MAC_SPEED_1000),
	/**<	10 Mbps SGMII */
	MAC_MODE_SGMII_10	= (MAC_IF_SGMII | MAC_SPEED_10),
	/**<   100 Mbps SGMII */
	MAC_MODE_SGMII_100   = (MAC_IF_SGMII | MAC_SPEED_100),
	/**<  1000 Mbps SGMII */
	MAC_MODE_SGMII_1000  = (MAC_IF_SGMII | MAC_SPEED_1000),
	/**< 10000 Mbps XGMII */
	MAC_MODE_XGMII_10000 = (MAC_IF_XGMII | MAC_SPEED_10000),
	/**<  1000 Mbps QSGMII */
	MAC_MODE_QSGMII_1000 = (MAC_IF_QSGMII | MAC_SPEED_1000)
पूर्ण;

/*mac communicate mode*/
क्रमागत mac_commom_mode अणु
	MAC_COMM_MODE_NONE	  = 0, /**< No transmit/receive communication */
	MAC_COMM_MODE_RX		= 1, /**< Only receive communication */
	MAC_COMM_MODE_TX		= 2, /**< Only transmit communication */
	MAC_COMM_MODE_RX_AND_TX = 3  /**< Both tx and rx communication */
पूर्ण;

/*mac statistics */
काष्ठा mac_statistics अणु
	u64  stat_pkts64; /* r-10G tr-DT 64 byte frame counter */
	u64  stat_pkts65to127; /* r-10G 65 to 127 byte frame counter */
	u64  stat_pkts128to255; /* r-10G 128 to 255 byte frame counter */
	u64  stat_pkts256to511; /*r-10G 256 to 511 byte frame counter */
	u64  stat_pkts512to1023;/* r-10G 512 to 1023 byte frame counter */
	u64  stat_pkts1024to1518; /* r-10G 1024 to 1518 byte frame counter */
	u64  stat_pkts1519to1522; /* r-10G 1519 to 1522 byte good frame count*/
	/* Total number of packets that were less than 64 octets */
	/*			दीर्घ with a wrong CRC.*/
	u64  stat_fragments;
	/* Total number of packets दीर्घer than valid maximum length octets */
	u64  stat_jabbers;
	/* number of dropped packets due to पूर्णांकernal errors of */
	/*			the MAC Client. */
	u64  stat_drop_events;
	/* Incremented when frames of correct length but with */
	/*			CRC error are received.*/
	u64  stat_crc_align_errors;
	/* Total number of packets that were less than 64 octets */
	/*			दीर्घ with a good CRC.*/
	u64  stat_undersize_pkts;
	u64  stat_oversize_pkts;  /**< T,B.D*/

	u64  stat_rx_छोड़ो;		   /**< Pause MAC Control received */
	u64  stat_tx_छोड़ो;		   /**< Pause MAC Control sent */

	u64  in_octets;		/**< Total number of byte received. */
	u64  in_pkts;		/* Total number of packets received.*/
	u64  in_mcast_pkts;	/* Total number of multicast frame received */
	u64  in_bcast_pkts;	/* Total number of broadcast frame received */
				/* Frames received, but discarded due to */
				/* problems within the MAC RX. */
	u64  in_discards;
	u64  in_errors;		/* Number of frames received with error: */
				/*	- FIFO Overflow Error */
				/*	- CRC Error */
				/*	- Frame Too Long Error */
				/*	- Alignment Error */
	u64  out_octets; /*Total number of byte sent. */
	u64  out_pkts;	/**< Total number of packets sent .*/
	u64  out_mcast_pkts; /* Total number of multicast frame sent */
	u64  out_bcast_pkts; /* Total number of multicast frame sent */
	/* Frames received, but discarded due to problems within */
	/*			the MAC TX N/A!.*/
	u64  out_discards;
	u64  out_errors;	/*Number of frames transmitted with error: */
			/*	- FIFO Overflow Error */
			/*	- FIFO Underflow Error */
			/*	 - Other */
पूर्ण;

/*mac para काष्ठा ,mac get param from nic or dsaf when initialize*/
काष्ठा mac_params अणु
	अक्षर addr[ETH_ALEN];
	u8 __iomem *vaddr; /*भव address*/
	काष्ठा device *dev;
	u8 mac_id;
	/**< Ethernet operation mode (MAC-PHY पूर्णांकerface and speed) */
	क्रमागत mac_mode mac_mode;
पूर्ण;

काष्ठा mac_info अणु
	u16 speed;/* The क्रमced speed (lower bits) in */
		/*		 *mbps. Please use */
		/*		 * ethtool_cmd_speed()/_set() to */
		/*		 * access it */
	u8 duplex;		/* Duplex, half or full */
	u8 स्वतः_neg;	/* Enable or disable स्वतःnegotiation */
	क्रमागत hnae_loop loop_mode;
	u8 tx_छोड़ो_en;
	u8 tx_छोड़ो_समय;
	u8 rx_छोड़ो_en;
	u8 pad_and_crc_en;
	u8 promiscuous_en;
	u8 port_en;	 /*port enable*/
पूर्ण;

काष्ठा mac_entry_idx अणु
	u8 addr[ETH_ALEN];
	u16 vlan_id:12;
	u16 valid:1;
	u16 qos:3;
पूर्ण;

काष्ठा mac_hw_stats अणु
	u64 rx_good_pkts;	/* only क्रम xgmac */
	u64 rx_good_bytes;
	u64 rx_total_pkts;	/* only क्रम xgmac */
	u64 rx_total_bytes;	/* only क्रम xgmac */
	u64 rx_bad_bytes;	/* only क्रम gmac */
	u64 rx_uc_pkts;
	u64 rx_mc_pkts;
	u64 rx_bc_pkts;
	u64 rx_fragment_err;	/* only क्रम xgmac */
	u64 rx_undersize;	/* only क्रम xgmac */
	u64 rx_under_min;
	u64 rx_mपूर्णांकo64;		/* only क्रम gmac */
	u64 rx_64bytes;
	u64 rx_65to127;
	u64 rx_128to255;
	u64 rx_256to511;
	u64 rx_512to1023;
	u64 rx_1024to1518;
	u64 rx_1519tomax;
	u64 rx_1519tomax_good;	/* only क्रम xgmac */
	u64 rx_oversize;
	u64 rx_jabber_err;
	u64 rx_fcs_err;
	u64 rx_vlan_pkts;	/* only क्रम gmac */
	u64 rx_data_err;	/* only क्रम gmac */
	u64 rx_align_err;	/* only क्रम gmac */
	u64 rx_दीर्घ_err;	/* only क्रम gmac */
	u64 rx_pfc_tc0;
	u64 rx_pfc_tc1;		/* only क्रम xgmac */
	u64 rx_pfc_tc2;		/* only क्रम xgmac */
	u64 rx_pfc_tc3;		/* only क्रम xgmac */
	u64 rx_pfc_tc4;		/* only क्रम xgmac */
	u64 rx_pfc_tc5;		/* only क्रम xgmac */
	u64 rx_pfc_tc6;		/* only क्रम xgmac */
	u64 rx_pfc_tc7;		/* only क्रम xgmac */
	u64 rx_unknown_ctrl;
	u64 rx_filter_pkts;	/* only क्रम gmac */
	u64 rx_filter_bytes;	/* only क्रम gmac */
	u64 rx_fअगरo_overrun_err;/* only क्रम gmac */
	u64 rx_len_err;		/* only क्रम gmac */
	u64 rx_comma_err;	/* only क्रम gmac */
	u64 rx_symbol_err;	/* only क्रम xgmac */
	u64 tx_good_to_sw;	/* only क्रम xgmac */
	u64 tx_bad_to_sw;	/* only क्रम xgmac */
	u64 rx_1731_pkts;	/* only क्रम xgmac */

	u64 tx_good_bytes;
	u64 tx_good_pkts;	/* only क्रम xgmac */
	u64 tx_total_bytes;	/* only क्रम xgmac */
	u64 tx_total_pkts;	/* only क्रम xgmac */
	u64 tx_bad_bytes;	/* only क्रम gmac */
	u64 tx_bad_pkts;	/* only क्रम xgmac */
	u64 tx_uc_pkts;
	u64 tx_mc_pkts;
	u64 tx_bc_pkts;
	u64 tx_undersize;	/* only क्रम xgmac */
	u64 tx_fragment_err;	/* only क्रम xgmac */
	u64 tx_under_min_pkts;	/* only क्रम gmac */
	u64 tx_64bytes;
	u64 tx_65to127;
	u64 tx_128to255;
	u64 tx_256to511;
	u64 tx_512to1023;
	u64 tx_1024to1518;
	u64 tx_1519tomax;
	u64 tx_1519tomax_good;	/* only क्रम xgmac */
	u64 tx_oversize;	/* only क्रम xgmac */
	u64 tx_jabber_err;
	u64 tx_underrun_err;	/* only क्रम gmac */
	u64 tx_vlan;		/* only क्रम gmac */
	u64 tx_crc_err;		/* only क्रम gmac */
	u64 tx_pfc_tc0;
	u64 tx_pfc_tc1;		/* only क्रम xgmac */
	u64 tx_pfc_tc2;		/* only क्रम xgmac */
	u64 tx_pfc_tc3;		/* only क्रम xgmac */
	u64 tx_pfc_tc4;		/* only क्रम xgmac */
	u64 tx_pfc_tc5;		/* only क्रम xgmac */
	u64 tx_pfc_tc6;		/* only क्रम xgmac */
	u64 tx_pfc_tc7;		/* only क्रम xgmac */
	u64 tx_ctrl;		/* only क्रम xgmac */
	u64 tx_1731_pkts;	/* only क्रम xgmac */
	u64 tx_1588_pkts;	/* only क्रम xgmac */
	u64 rx_good_from_sw;	/* only क्रम xgmac */
	u64 rx_bad_from_sw;	/* only क्रम xgmac */
पूर्ण;

काष्ठा hns_mac_cb अणु
	काष्ठा device *dev;
	काष्ठा dsaf_device *dsaf_dev;
	काष्ठा mac_priv priv;
	काष्ठा fwnode_handle *fw_port;
	u8 __iomem *vaddr;
	u8 __iomem *sys_ctl_vaddr;
	u8 __iomem *serdes_vaddr;
	काष्ठा regmap *serdes_ctrl;
	काष्ठा regmap *cpld_ctrl;
	अक्षर mc_mask[ETH_ALEN];
	u32 cpld_ctrl_reg;
	u32 port_rst_off;
	u32 port_mode_off;
	काष्ठा mac_entry_idx addr_entry_idx[DSAF_MAX_VM_NUM];
	u8 sfp_prsnt;
	u8 cpld_led_value;
	u8 mac_id;

	u8 link;
	u8 half_duplex;
	u16 speed;
	u16 max_speed;
	u16 max_frm;
	u16 tx_छोड़ो_frm_समय;
	u32 अगर_support;
	u64 txpkt_क्रम_led;
	u64 rxpkt_क्रम_led;
	क्रमागत hnae_port_type mac_type;
	क्रमागत hnae_media_type media_type;
	phy_पूर्णांकerface_t phy_अगर;
	क्रमागत hnae_loop loop_mode;

	काष्ठा phy_device *phy_dev;

	काष्ठा mac_hw_stats hw_stats;
पूर्ण;

काष्ठा mac_driver अणु
	/*init Mac when init nic or dsaf*/
	व्योम (*mac_init)(व्योम *mac_drv);
	/*हटाओ mac when हटाओ nic or dsaf*/
	व्योम (*mac_मुक्त)(व्योम *mac_drv);
	/*enable mac when enable nic or dsaf*/
	व्योम (*mac_enable)(व्योम *mac_drv, क्रमागत mac_commom_mode mode);
	/*disable mac when disable nic or dsaf*/
	व्योम (*mac_disable)(व्योम *mac_drv, क्रमागत mac_commom_mode mode);
	/* config mac address*/
	व्योम (*set_mac_addr)(व्योम *mac_drv,	अक्षर *mac_addr);
	/*adjust mac mode of port,include speed and duplex*/
	पूर्णांक (*adjust_link)(व्योम *mac_drv, क्रमागत mac_speed speed,
			   u32 full_duplex);
	/* need adjust link */
	bool (*need_adjust_link)(व्योम *mac_drv, क्रमागत mac_speed speed,
				 पूर्णांक duplex);
	/* config स्वतःegotaite mode of port*/
	व्योम (*set_an_mode)(व्योम *mac_drv, u8 enable);
	/* config loopbank mode */
	पूर्णांक (*config_loopback)(व्योम *mac_drv, क्रमागत hnae_loop loop_mode,
			       u8 enable);
	/* config mtu*/
	व्योम (*config_max_frame_length)(व्योम *mac_drv, u16 newval);
	/*config PAD and CRC enable */
	व्योम (*config_pad_and_crc)(व्योम *mac_drv, u8 newval);
	/*config tx छोड़ो समय,अगर छोड़ो_समय is zero,disable tx छोड़ो enable*/
	व्योम (*set_tx_स्वतः_छोड़ो_frames)(व्योम *mac_drv, u16 छोड़ो_समय);
	/* config rx mode क्रम promiscuous*/
	व्योम (*set_promiscuous)(व्योम *mac_drv, u8 enable);
	व्योम (*mac_छोड़ोfrm_cfg)(व्योम *mac_drv, u32 rx_en, u32 tx_en);

	व्योम (*स्वतःneg_stat)(व्योम *mac_drv, u32 *enable);
	पूर्णांक (*set_छोड़ो_enable)(व्योम *mac_drv, u32 rx_en, u32 tx_en);
	व्योम (*get_छोड़ो_enable)(व्योम *mac_drv, u32 *rx_en, u32 *tx_en);
	व्योम (*get_link_status)(व्योम *mac_drv, u32 *link_stat);
	/* get the imporant regs*/
	व्योम (*get_regs)(व्योम *mac_drv, व्योम *data);
	पूर्णांक (*get_regs_count)(व्योम);
	/* get strings name क्रम ethtool statistic */
	व्योम (*get_strings)(u32 stringset, u8 *data);
	/* get the number of strings*/
	पूर्णांक (*get_sset_count)(पूर्णांक stringset);

	/* get the statistic by ethtools*/
	व्योम (*get_ethtool_stats)(व्योम *mac_drv, u64 *data);

	/* get mac inक्रमmation */
	व्योम (*get_info)(व्योम *mac_drv, काष्ठा mac_info *mac_info);

	व्योम (*update_stats)(व्योम *mac_drv);
	पूर्णांक (*रुको_fअगरo_clean)(व्योम *mac_drv);

	क्रमागत mac_mode mac_mode;
	u8 mac_id;
	काष्ठा hns_mac_cb *mac_cb;
	u8 __iomem *io_base;
	अचिन्हित पूर्णांक mac_en_flg;/*you'd better don't enable mac twice*/
	अचिन्हित पूर्णांक virt_dev_num;
	काष्ठा device *dev;
पूर्ण;

काष्ठा mac_stats_string अणु
	स्थिर अक्षर desc[ETH_GSTRING_LEN];
	अचिन्हित दीर्घ offset;
पूर्ण;

#घोषणा MAC_MAKE_MODE(पूर्णांकerface, speed) (क्रमागत mac_mode)((पूर्णांकerface) | (speed))
#घोषणा MAC_INTERFACE_FROM_MODE(mode) (क्रमागत mac_पूर्णांकf)((mode) & 0xFFFF0000)
#घोषणा MAC_SPEED_FROM_MODE(mode) (क्रमागत mac_speed)((mode) & 0x0000FFFF)
#घोषणा MAC_STATS_FIELD_OFF(field) (दुरत्व(काष्ठा mac_hw_stats, field))

अटल अंतरभूत काष्ठा mac_driver *hns_mac_get_drv(
	स्थिर काष्ठा hns_mac_cb *mac_cb)
अणु
	वापस (काष्ठा mac_driver *)(mac_cb->priv.mac);
पूर्ण

व्योम *hns_gmac_config(काष्ठा hns_mac_cb *mac_cb,
		      काष्ठा mac_params *mac_param);
व्योम *hns_xgmac_config(काष्ठा hns_mac_cb *mac_cb,
		       काष्ठा mac_params *mac_param);

पूर्णांक hns_mac_init(काष्ठा dsaf_device *dsaf_dev);
व्योम mac_adjust_link(काष्ठा net_device *net_dev);
bool hns_mac_need_adjust_link(काष्ठा hns_mac_cb *mac_cb, पूर्णांक speed, पूर्णांक duplex);
व्योम hns_mac_get_link_status(काष्ठा hns_mac_cb *mac_cb,	u32 *link_status);
पूर्णांक hns_mac_change_vf_addr(काष्ठा hns_mac_cb *mac_cb, u32 vmid, अक्षर *addr);
पूर्णांक hns_mac_set_multi(काष्ठा hns_mac_cb *mac_cb,
		      u32 port_num, अक्षर *addr, bool enable);
पूर्णांक hns_mac_vm_config_bc_en(काष्ठा hns_mac_cb *mac_cb, u32 vm, bool enable);
व्योम hns_mac_start(काष्ठा hns_mac_cb *mac_cb);
व्योम hns_mac_stop(काष्ठा hns_mac_cb *mac_cb);
व्योम hns_mac_uninit(काष्ठा dsaf_device *dsaf_dev);
व्योम hns_mac_adjust_link(काष्ठा hns_mac_cb *mac_cb, पूर्णांक speed, पूर्णांक duplex);
व्योम hns_mac_reset(काष्ठा hns_mac_cb *mac_cb);
व्योम hns_mac_get_स्वतःneg(काष्ठा hns_mac_cb *mac_cb, u32 *स्वतः_neg);
व्योम hns_mac_get_छोड़ोparam(काष्ठा hns_mac_cb *mac_cb, u32 *rx_en, u32 *tx_en);
पूर्णांक hns_mac_set_स्वतःneg(काष्ठा hns_mac_cb *mac_cb, u8 enable);
पूर्णांक hns_mac_set_छोड़ोparam(काष्ठा hns_mac_cb *mac_cb, u32 rx_en, u32 tx_en);
पूर्णांक hns_mac_set_mtu(काष्ठा hns_mac_cb *mac_cb, u32 new_mtu, u32 buf_size);
पूर्णांक hns_mac_get_port_info(काष्ठा hns_mac_cb *mac_cb,
			  u8 *स्वतः_neg, u16 *speed, u8 *duplex);
पूर्णांक hns_mac_config_mac_loopback(काष्ठा hns_mac_cb *mac_cb,
				क्रमागत hnae_loop loop, पूर्णांक en);
व्योम hns_mac_update_stats(काष्ठा hns_mac_cb *mac_cb);
व्योम hns_mac_get_stats(काष्ठा hns_mac_cb *mac_cb, u64 *data);
व्योम hns_mac_get_strings(काष्ठा hns_mac_cb *mac_cb, पूर्णांक stringset, u8 *data);
पूर्णांक hns_mac_get_sset_count(काष्ठा hns_mac_cb *mac_cb, पूर्णांक stringset);
व्योम hns_mac_get_regs(काष्ठा hns_mac_cb *mac_cb, व्योम *data);
पूर्णांक hns_mac_get_regs_count(काष्ठा hns_mac_cb *mac_cb);
व्योम hns_set_led_opt(काष्ठा hns_mac_cb *mac_cb);
पूर्णांक hns_cpld_led_set_id(काष्ठा hns_mac_cb *mac_cb,
			क्रमागत hnae_led_state status);
व्योम hns_mac_set_promisc(काष्ठा hns_mac_cb *mac_cb, u8 en);
पूर्णांक hns_mac_get_inner_port_num(काष्ठा hns_mac_cb *mac_cb,
			       u8 vmid, u8 *port_num);
पूर्णांक hns_mac_add_uc_addr(काष्ठा hns_mac_cb *mac_cb, u8 vf_id,
			स्थिर अचिन्हित अक्षर *addr);
पूर्णांक hns_mac_rm_uc_addr(काष्ठा hns_mac_cb *mac_cb, u8 vf_id,
		       स्थिर अचिन्हित अक्षर *addr);
पूर्णांक hns_mac_clr_multicast(काष्ठा hns_mac_cb *mac_cb, पूर्णांक vfn);
व्योम hns_mac_enable(काष्ठा hns_mac_cb *mac_cb, क्रमागत mac_commom_mode mode);
व्योम hns_mac_disable(काष्ठा hns_mac_cb *mac_cb, क्रमागत mac_commom_mode mode);
पूर्णांक hns_mac_रुको_fअगरo_clean(काष्ठा hns_mac_cb *mac_cb);

#पूर्ण_अगर /* _HNS_DSAF_MAC_H */
