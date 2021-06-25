<शैली गुरु>
/*
 * Copyright (c) 2005-2008 Chelsio, Inc. All rights reserved.
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
#अगर_अघोषित __CHELSIO_COMMON_H
#घोषणा __CHELSIO_COMMON_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mdपन.स>
#समावेश "version.h"

#घोषणा CH_ERR(adap, fmt, ...)   dev_err(&adap->pdev->dev, fmt, ##__VA_ARGS__)
#घोषणा CH_WARN(adap, fmt, ...)  dev_warn(&adap->pdev->dev, fmt, ##__VA_ARGS__)
#घोषणा CH_ALERT(adap, fmt, ...) dev_alert(&adap->pdev->dev, fmt, ##__VA_ARGS__)

/*
 * More घातerful macro that selectively prपूर्णांकs messages based on msg_enable.
 * For info and debugging messages.
 */
#घोषणा CH_MSG(adapter, level, category, fmt, ...) करो अणु \
	अगर ((adapter)->msg_enable & NETIF_MSG_##category) \
		dev_prपूर्णांकk(KERN_##level, &adapter->pdev->dev, fmt, \
			   ## __VA_ARGS__); \
पूर्ण जबतक (0)

#अगर_घोषित DEBUG
# define CH_DBG(adapter, category, fmt, ...) \
	CH_MSG(adapter, DEBUG, category, fmt, ## __VA_ARGS__)
#अन्यथा
# define CH_DBG(adapter, category, fmt, ...)
#पूर्ण_अगर

/* Additional NETIF_MSG_* categories */
#घोषणा NETIF_MSG_MMIO 0x8000000

क्रमागत अणु
	MAX_NPORTS = 2,		/* max # of ports */
	MAX_FRAME_SIZE = 10240,	/* max MAC frame size, including header + FCS */
	EEPROMSIZE = 8192,	/* Serial EEPROM size */
	SERNUM_LEN     = 16,    /* Serial # length */
	RSS_TABLE_SIZE = 64,	/* size of RSS lookup and mapping tables */
	TCB_SIZE = 128,		/* TCB size */
	NMTUS = 16,		/* size of MTU table */
	NCCTRL_WIN = 32,	/* # of congestion control winकरोws */
	PROTO_SRAM_LINES = 128, /* size of TP sram */
पूर्ण;

#घोषणा MAX_RX_COALESCING_LEN 12288U

क्रमागत अणु
	PAUSE_RX = 1 << 0,
	PAUSE_TX = 1 << 1,
	PAUSE_AUTONEG = 1 << 2
पूर्ण;

क्रमागत अणु
	SUPPORTED_IRQ      = 1 << 24
पूर्ण;

क्रमागत अणु				/* adapter पूर्णांकerrupt-मुख्यtained statistics */
	STAT_ULP_CH0_PBL_OOB,
	STAT_ULP_CH1_PBL_OOB,
	STAT_PCI_CORR_ECC,

	IRQ_NUM_STATS		/* keep last */
पूर्ण;

#घोषणा TP_VERSION_MAJOR	1
#घोषणा TP_VERSION_MINOR	1
#घोषणा TP_VERSION_MICRO	0

#घोषणा S_TP_VERSION_MAJOR		16
#घोषणा M_TP_VERSION_MAJOR		0xFF
#घोषणा V_TP_VERSION_MAJOR(x)		((x) << S_TP_VERSION_MAJOR)
#घोषणा G_TP_VERSION_MAJOR(x)		\
	    (((x) >> S_TP_VERSION_MAJOR) & M_TP_VERSION_MAJOR)

#घोषणा S_TP_VERSION_MINOR		8
#घोषणा M_TP_VERSION_MINOR		0xFF
#घोषणा V_TP_VERSION_MINOR(x)		((x) << S_TP_VERSION_MINOR)
#घोषणा G_TP_VERSION_MINOR(x)		\
	    (((x) >> S_TP_VERSION_MINOR) & M_TP_VERSION_MINOR)

#घोषणा S_TP_VERSION_MICRO		0
#घोषणा M_TP_VERSION_MICRO		0xFF
#घोषणा V_TP_VERSION_MICRO(x)		((x) << S_TP_VERSION_MICRO)
#घोषणा G_TP_VERSION_MICRO(x)		\
	    (((x) >> S_TP_VERSION_MICRO) & M_TP_VERSION_MICRO)

क्रमागत अणु
	SGE_QSETS = 8,		/* # of SGE Tx/Rx/RspQ sets */
	SGE_RXQ_PER_SET = 2,	/* # of Rx queues per set */
	SGE_TXQ_PER_SET = 3	/* # of Tx queues per set */
पूर्ण;

क्रमागत sge_context_type अणु		/* SGE egress context types */
	SGE_CNTXT_RDMA = 0,
	SGE_CNTXT_ETH = 2,
	SGE_CNTXT_OFLD = 4,
	SGE_CNTXT_CTRL = 5
पूर्ण;

क्रमागत अणु
	AN_PKT_SIZE = 32,	/* async notअगरication packet size */
	IMMED_PKT_SIZE = 48	/* packet size क्रम immediate data */
पूर्ण;

काष्ठा sg_ent अणु			/* SGE scatter/gather entry */
	__be32 len[2];
	__be64 addr[2];
पूर्ण;

#अगर_अघोषित SGE_NUM_GENBITS
/* Must be 1 or 2 */
# define SGE_NUM_GENBITS 2
#पूर्ण_अगर

#घोषणा TX_DESC_FLITS 16U
#घोषणा WR_FLITS (TX_DESC_FLITS + 1 - SGE_NUM_GENBITS)

काष्ठा cphy;
काष्ठा adapter;

काष्ठा mdio_ops अणु
	पूर्णांक (*पढ़ो)(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
		    u16 reg_addr);
	पूर्णांक (*ग_लिखो)(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
		     u16 reg_addr, u16 val);
	अचिन्हित mode_support;
पूर्ण;

काष्ठा adapter_info अणु
	अचिन्हित अक्षर nports0;        /* # of ports on channel 0 */
	अचिन्हित अक्षर nports1;        /* # of ports on channel 1 */
	अचिन्हित अक्षर phy_base_addr;	/* MDIO PHY base address */
	अचिन्हित पूर्णांक gpio_out;	/* GPIO output settings */
	अचिन्हित अक्षर gpio_पूर्णांकr[MAX_NPORTS]; /* GPIO PHY IRQ pins */
	अचिन्हित दीर्घ caps;	/* adapter capabilities */
	स्थिर काष्ठा mdio_ops *mdio_ops;	/* MDIO operations */
	स्थिर अक्षर *desc;	/* product description */
पूर्ण;

काष्ठा mc5_stats अणु
	अचिन्हित दीर्घ parity_err;
	अचिन्हित दीर्घ active_rgn_full;
	अचिन्हित दीर्घ nfa_srch_err;
	अचिन्हित दीर्घ unknown_cmd;
	अचिन्हित दीर्घ reqq_parity_err;
	अचिन्हित दीर्घ dispq_parity_err;
	अचिन्हित दीर्घ del_act_empty;
पूर्ण;

काष्ठा mc7_stats अणु
	अचिन्हित दीर्घ corr_err;
	अचिन्हित दीर्घ uncorr_err;
	अचिन्हित दीर्घ parity_err;
	अचिन्हित दीर्घ addr_err;
पूर्ण;

काष्ठा mac_stats अणु
	u64 tx_octets;		/* total # of octets in good frames */
	u64 tx_octets_bad;	/* total # of octets in error frames */
	u64 tx_frames;		/* all good frames */
	u64 tx_mcast_frames;	/* good multicast frames */
	u64 tx_bcast_frames;	/* good broadcast frames */
	u64 tx_छोड़ो;		/* # of transmitted छोड़ो frames */
	u64 tx_deferred;	/* frames with deferred transmissions */
	u64 tx_late_collisions;	/* # of late collisions */
	u64 tx_total_collisions;	/* # of total collisions */
	u64 tx_excess_collisions;	/* frame errors from excessive collissions */
	u64 tx_underrun;	/* # of Tx FIFO underruns */
	u64 tx_len_errs;	/* # of Tx length errors */
	u64 tx_mac_पूर्णांकernal_errs;	/* # of पूर्णांकernal MAC errors on Tx */
	u64 tx_excess_deferral;	/* # of frames with excessive deferral */
	u64 tx_fcs_errs;	/* # of frames with bad FCS */

	u64 tx_frames_64;	/* # of Tx frames in a particular range */
	u64 tx_frames_65_127;
	u64 tx_frames_128_255;
	u64 tx_frames_256_511;
	u64 tx_frames_512_1023;
	u64 tx_frames_1024_1518;
	u64 tx_frames_1519_max;

	u64 rx_octets;		/* total # of octets in good frames */
	u64 rx_octets_bad;	/* total # of octets in error frames */
	u64 rx_frames;		/* all good frames */
	u64 rx_mcast_frames;	/* good multicast frames */
	u64 rx_bcast_frames;	/* good broadcast frames */
	u64 rx_छोड़ो;		/* # of received छोड़ो frames */
	u64 rx_fcs_errs;	/* # of received frames with bad FCS */
	u64 rx_align_errs;	/* alignment errors */
	u64 rx_symbol_errs;	/* symbol errors */
	u64 rx_data_errs;	/* data errors */
	u64 rx_sequence_errs;	/* sequence errors */
	u64 rx_runt;		/* # of runt frames */
	u64 rx_jabber;		/* # of jabber frames */
	u64 rx_लघु;		/* # of लघु frames */
	u64 rx_too_दीर्घ;	/* # of oversized frames */
	u64 rx_mac_पूर्णांकernal_errs;	/* # of पूर्णांकernal MAC errors on Rx */

	u64 rx_frames_64;	/* # of Rx frames in a particular range */
	u64 rx_frames_65_127;
	u64 rx_frames_128_255;
	u64 rx_frames_256_511;
	u64 rx_frames_512_1023;
	u64 rx_frames_1024_1518;
	u64 rx_frames_1519_max;

	u64 rx_cong_drops;	/* # of Rx drops due to SGE congestion */

	अचिन्हित दीर्घ tx_fअगरo_parity_err;
	अचिन्हित दीर्घ rx_fअगरo_parity_err;
	अचिन्हित दीर्घ tx_fअगरo_urun;
	अचिन्हित दीर्घ rx_fअगरo_ovfl;
	अचिन्हित दीर्घ serdes_संकेत_loss;
	अचिन्हित दीर्घ xaui_pcs_ctc_err;
	अचिन्हित दीर्घ xaui_pcs_align_change;

	अचिन्हित दीर्घ num_toggled; /* # बार toggled TxEn due to stuck TX */
	अचिन्हित दीर्घ num_resets;  /* # बार reset due to stuck TX */

	अचिन्हित दीर्घ link_faults;  /* # detected link faults */
पूर्ण;

काष्ठा tp_mib_stats अणु
	u32 ipInReceive_hi;
	u32 ipInReceive_lo;
	u32 ipInHdrErrors_hi;
	u32 ipInHdrErrors_lo;
	u32 ipInAddrErrors_hi;
	u32 ipInAddrErrors_lo;
	u32 ipInUnknownProtos_hi;
	u32 ipInUnknownProtos_lo;
	u32 ipInDiscards_hi;
	u32 ipInDiscards_lo;
	u32 ipInDelivers_hi;
	u32 ipInDelivers_lo;
	u32 ipOutRequests_hi;
	u32 ipOutRequests_lo;
	u32 ipOutDiscards_hi;
	u32 ipOutDiscards_lo;
	u32 ipOutNoRoutes_hi;
	u32 ipOutNoRoutes_lo;
	u32 ipReयंत्रTimeout;
	u32 ipReयंत्रReqds;
	u32 ipReयंत्रOKs;
	u32 ipReयंत्रFails;

	u32 reserved[8];

	u32 tcpActiveOpens;
	u32 tcpPassiveOpens;
	u32 tcpAttemptFails;
	u32 tcpEstabResets;
	u32 tcpOutRsts;
	u32 tcpCurrEstab;
	u32 tcpInSegs_hi;
	u32 tcpInSegs_lo;
	u32 tcpOutSegs_hi;
	u32 tcpOutSegs_lo;
	u32 tcpRetransSeg_hi;
	u32 tcpRetransSeg_lo;
	u32 tcpInErrs_hi;
	u32 tcpInErrs_lo;
	u32 tcpRtoMin;
	u32 tcpRtoMax;
पूर्ण;

काष्ठा tp_params अणु
	अचिन्हित पूर्णांक nchan;	/* # of channels */
	अचिन्हित पूर्णांक pmrx_size;	/* total PMRX capacity */
	अचिन्हित पूर्णांक pmtx_size;	/* total PMTX capacity */
	अचिन्हित पूर्णांक cm_size;	/* total CM capacity */
	अचिन्हित पूर्णांक chan_rx_size;	/* per channel Rx size */
	अचिन्हित पूर्णांक chan_tx_size;	/* per channel Tx size */
	अचिन्हित पूर्णांक rx_pg_size;	/* Rx page size */
	अचिन्हित पूर्णांक tx_pg_size;	/* Tx page size */
	अचिन्हित पूर्णांक rx_num_pgs;	/* # of Rx pages */
	अचिन्हित पूर्णांक tx_num_pgs;	/* # of Tx pages */
	अचिन्हित पूर्णांक nसमयr_qs;	/* # of समयr queues */
पूर्ण;

काष्ठा qset_params अणु		/* SGE queue set parameters */
	अचिन्हित पूर्णांक polling;	/* polling/पूर्णांकerrupt service क्रम rspq */
	अचिन्हित पूर्णांक coalesce_usecs;	/* irq coalescing समयr */
	अचिन्हित पूर्णांक rspq_size;	/* # of entries in response queue */
	अचिन्हित पूर्णांक fl_size;	/* # of entries in regular मुक्त list */
	अचिन्हित पूर्णांक jumbo_size;	/* # of entries in jumbo मुक्त list */
	अचिन्हित पूर्णांक txq_size[SGE_TXQ_PER_SET];	/* Tx queue sizes */
	अचिन्हित पूर्णांक cong_thres;	/* FL congestion threshold */
	अचिन्हित पूर्णांक vector;		/* Interrupt (line or vector) number */
पूर्ण;

काष्ठा sge_params अणु
	अचिन्हित पूर्णांक max_pkt_size;	/* max offload pkt size */
	काष्ठा qset_params qset[SGE_QSETS];
पूर्ण;

काष्ठा mc5_params अणु
	अचिन्हित पूर्णांक mode;	/* selects MC5 width */
	अचिन्हित पूर्णांक nservers;	/* size of server region */
	अचिन्हित पूर्णांक nfilters;	/* size of filter region */
	अचिन्हित पूर्णांक nroutes;	/* size of routing region */
पूर्ण;

/* Default MC5 region sizes */
क्रमागत अणु
	DEFAULT_NSERVERS = 512,
	DEFAULT_NFILTERS = 128
पूर्ण;

/* MC5 modes, these must be non-0 */
क्रमागत अणु
	MC5_MODE_144_BIT = 1,
	MC5_MODE_72_BIT = 2
पूर्ण;

/* MC5 min active region size */
क्रमागत अणु MC5_MIN_TIDS = 16 पूर्ण;

काष्ठा vpd_params अणु
	अचिन्हित पूर्णांक cclk;
	अचिन्हित पूर्णांक mclk;
	अचिन्हित पूर्णांक uclk;
	अचिन्हित पूर्णांक mdc;
	अचिन्हित पूर्णांक mem_timing;
	u8 sn[SERNUM_LEN + 1];
	u8 eth_base[6];
	u8 port_type[MAX_NPORTS];
	अचिन्हित लघु xauicfg[2];
पूर्ण;

काष्ठा pci_params अणु
	अचिन्हित पूर्णांक vpd_cap_addr;
	अचिन्हित लघु speed;
	अचिन्हित अक्षर width;
	अचिन्हित अक्षर variant;
पूर्ण;

क्रमागत अणु
	PCI_VARIANT_PCI,
	PCI_VARIANT_PCIX_MODE1_PARITY,
	PCI_VARIANT_PCIX_MODE1_ECC,
	PCI_VARIANT_PCIX_266_MODE2,
	PCI_VARIANT_PCIE
पूर्ण;

काष्ठा adapter_params अणु
	काष्ठा sge_params sge;
	काष्ठा mc5_params mc5;
	काष्ठा tp_params tp;
	काष्ठा vpd_params vpd;
	काष्ठा pci_params pci;

	स्थिर काष्ठा adapter_info *info;

	अचिन्हित लघु mtus[NMTUS];
	अचिन्हित लघु a_wnd[NCCTRL_WIN];
	अचिन्हित लघु b_wnd[NCCTRL_WIN];

	अचिन्हित पूर्णांक nports;	/* # of ethernet ports */
	अचिन्हित पूर्णांक chan_map;  /* biपंचांगap of in-use Tx channels */
	अचिन्हित पूर्णांक stats_update_period;	/* MAC stats accumulation period */
	अचिन्हित पूर्णांक linkpoll_period;	/* link poll period in 0.1s */
	अचिन्हित पूर्णांक rev;	/* chip revision */
	अचिन्हित पूर्णांक offload;
पूर्ण;

क्रमागत अणु					    /* chip revisions */
	T3_REV_A  = 0,
	T3_REV_B  = 2,
	T3_REV_B2 = 3,
	T3_REV_C  = 4,
पूर्ण;

काष्ठा trace_params अणु
	u32 sip;
	u32 sip_mask;
	u32 dip;
	u32 dip_mask;
	u16 sport;
	u16 sport_mask;
	u16 dport;
	u16 dport_mask;
	u32 vlan:12;
	u32 vlan_mask:12;
	u32 पूर्णांकf:4;
	u32 पूर्णांकf_mask:4;
	u8 proto;
	u8 proto_mask;
पूर्ण;

काष्ठा link_config अणु
	अचिन्हित पूर्णांक supported;	/* link capabilities */
	अचिन्हित पूर्णांक advertising;	/* advertised capabilities */
	अचिन्हित लघु requested_speed;	/* speed user has requested */
	अचिन्हित लघु speed;	/* actual link speed */
	अचिन्हित अक्षर requested_duplex;	/* duplex user has requested */
	अचिन्हित अक्षर duplex;	/* actual link duplex */
	अचिन्हित अक्षर requested_fc;	/* flow control user has requested */
	अचिन्हित अक्षर fc;	/* actual link flow control */
	अचिन्हित अक्षर स्वतःneg;	/* स्वतःnegotiating? */
	अचिन्हित पूर्णांक link_ok;	/* link up? */
पूर्ण;

#घोषणा SPEED_INVALID   0xffff
#घोषणा DUPLEX_INVALID  0xff

काष्ठा mc5 अणु
	काष्ठा adapter *adapter;
	अचिन्हित पूर्णांक tcam_size;
	अचिन्हित अक्षर part_type;
	अचिन्हित अक्षर parity_enabled;
	अचिन्हित अक्षर mode;
	काष्ठा mc5_stats stats;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक t3_mc5_size(स्थिर काष्ठा mc5 *p)
अणु
	वापस p->tcam_size;
पूर्ण

काष्ठा mc7 अणु
	काष्ठा adapter *adapter;	/* backpoपूर्णांकer to adapter */
	अचिन्हित पूर्णांक size;	/* memory size in bytes */
	अचिन्हित पूर्णांक width;	/* MC7 पूर्णांकerface width */
	अचिन्हित पूर्णांक offset;	/* रेजिस्टर address offset क्रम MC7 instance */
	स्थिर अक्षर *name;	/* name of MC7 instance */
	काष्ठा mc7_stats stats;	/* MC7 statistics */
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक t3_mc7_size(स्थिर काष्ठा mc7 *p)
अणु
	वापस p->size;
पूर्ण

काष्ठा cmac अणु
	काष्ठा adapter *adapter;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक nucast;	/* # of address filters क्रम unicast MACs */
	अचिन्हित पूर्णांक tx_tcnt;
	अचिन्हित पूर्णांक tx_xcnt;
	u64 tx_mcnt;
	अचिन्हित पूर्णांक rx_xcnt;
	अचिन्हित पूर्णांक rx_ocnt;
	u64 rx_mcnt;
	अचिन्हित पूर्णांक toggle_cnt;
	अचिन्हित पूर्णांक txen;
	u64 rx_छोड़ो;
	काष्ठा mac_stats stats;
पूर्ण;

क्रमागत अणु
	MAC_सूचीECTION_RX = 1,
	MAC_सूचीECTION_TX = 2,
	MAC_RXFIFO_SIZE = 32768
पूर्ण;

/* PHY loopback direction */
क्रमागत अणु
	PHY_LOOPBACK_TX = 1,
	PHY_LOOPBACK_RX = 2
पूर्ण;

/* PHY पूर्णांकerrupt types */
क्रमागत अणु
	cphy_cause_link_change = 1,
	cphy_cause_fअगरo_error = 2,
	cphy_cause_module_change = 4,
पूर्ण;

/* PHY module types */
क्रमागत अणु
	phy_modtype_none,
	phy_modtype_sr,
	phy_modtype_lr,
	phy_modtype_lrm,
	phy_modtype_twinax,
	phy_modtype_twinax_दीर्घ,
	phy_modtype_unknown
पूर्ण;

/* PHY operations */
काष्ठा cphy_ops अणु
	पूर्णांक (*reset)(काष्ठा cphy *phy, पूर्णांक रुको);

	पूर्णांक (*पूर्णांकr_enable)(काष्ठा cphy *phy);
	पूर्णांक (*पूर्णांकr_disable)(काष्ठा cphy *phy);
	पूर्णांक (*पूर्णांकr_clear)(काष्ठा cphy *phy);
	पूर्णांक (*पूर्णांकr_handler)(काष्ठा cphy *phy);

	पूर्णांक (*स्वतःneg_enable)(काष्ठा cphy *phy);
	पूर्णांक (*स्वतःneg_restart)(काष्ठा cphy *phy);

	पूर्णांक (*advertise)(काष्ठा cphy *phy, अचिन्हित पूर्णांक advertise_map);
	पूर्णांक (*set_loopback)(काष्ठा cphy *phy, पूर्णांक mmd, पूर्णांक dir, पूर्णांक enable);
	पूर्णांक (*set_speed_duplex)(काष्ठा cphy *phy, पूर्णांक speed, पूर्णांक duplex);
	पूर्णांक (*get_link_status)(काष्ठा cphy *phy, पूर्णांक *link_ok, पूर्णांक *speed,
			       पूर्णांक *duplex, पूर्णांक *fc);
	पूर्णांक (*घातer_करोwn)(काष्ठा cphy *phy, पूर्णांक enable);

	u32 mmds;
पूर्ण;
क्रमागत अणु
	EDC_OPT_AEL2005 = 0,
	EDC_OPT_AEL2005_SIZE = 1084,
	EDC_TWX_AEL2005 = 1,
	EDC_TWX_AEL2005_SIZE = 1464,
	EDC_TWX_AEL2020 = 2,
	EDC_TWX_AEL2020_SIZE = 1628,
	EDC_MAX_SIZE = EDC_TWX_AEL2020_SIZE, /* Max cache size */
पूर्ण;

/* A PHY instance */
काष्ठा cphy अणु
	u8 modtype;			/* PHY module type */
	लघु priv;			/* scratch pad */
	अचिन्हित पूर्णांक caps;		/* PHY capabilities */
	काष्ठा adapter *adapter;	/* associated adapter */
	स्थिर अक्षर *desc;		/* PHY description */
	अचिन्हित दीर्घ fअगरo_errors;	/* FIFO over/under-flows */
	स्थिर काष्ठा cphy_ops *ops;	/* PHY operations */
	काष्ठा mdio_अगर_info mdio;
	u16 phy_cache[EDC_MAX_SIZE];	/* EDC cache */
पूर्ण;

/* Convenience MDIO पढ़ो/ग_लिखो wrappers */
अटल अंतरभूत पूर्णांक t3_mdio_पढ़ो(काष्ठा cphy *phy, पूर्णांक mmd, पूर्णांक reg,
			       अचिन्हित पूर्णांक *valp)
अणु
	पूर्णांक rc = phy->mdio.mdio_पढ़ो(phy->mdio.dev, phy->mdio.prtad, mmd, reg);
	*valp = (rc >= 0) ? rc : -1;
	वापस (rc >= 0) ? 0 : rc;
पूर्ण

अटल अंतरभूत पूर्णांक t3_mdio_ग_लिखो(काष्ठा cphy *phy, पूर्णांक mmd, पूर्णांक reg,
				अचिन्हित पूर्णांक val)
अणु
	वापस phy->mdio.mdio_ग_लिखो(phy->mdio.dev, phy->mdio.prtad, mmd,
				    reg, val);
पूर्ण

/* Convenience initializer */
अटल अंतरभूत व्योम cphy_init(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			     पूर्णांक phy_addr, स्थिर काष्ठा cphy_ops *phy_ops,
			     स्थिर काष्ठा mdio_ops *mdio_ops,
			      अचिन्हित पूर्णांक caps, स्थिर अक्षर *desc)
अणु
	phy->caps = caps;
	phy->adapter = adapter;
	phy->desc = desc;
	phy->ops = phy_ops;
	अगर (mdio_ops) अणु
		phy->mdio.prtad = phy_addr;
		phy->mdio.mmds = phy_ops->mmds;
		phy->mdio.mode_support = mdio_ops->mode_support;
		phy->mdio.mdio_पढ़ो = mdio_ops->पढ़ो;
		phy->mdio.mdio_ग_लिखो = mdio_ops->ग_लिखो;
	पूर्ण
पूर्ण

/* Accumulate MAC statistics every 180 seconds.  For 1G we multiply by 10. */
#घोषणा MAC_STATS_ACCUM_SECS 180

#घोषणा XGM_REG(reg_addr, idx) \
	((reg_addr) + (idx) * (XGMAC0_1_BASE_ADDR - XGMAC0_0_BASE_ADDR))

काष्ठा addr_val_pair अणु
	अचिन्हित पूर्णांक reg_addr;
	अचिन्हित पूर्णांक val;
पूर्ण;

#समावेश "adapter.h"

#अगर_अघोषित PCI_VENDOR_ID_CHELSIO
# define PCI_VENDOR_ID_CHELSIO 0x1425
#पूर्ण_अगर

#घोषणा क्रम_each_port(adapter, iter) \
	क्रम (iter = 0; iter < (adapter)->params.nports; ++iter)

#घोषणा adapter_info(adap) ((adap)->params.info)

अटल अंतरभूत पूर्णांक uses_xaui(स्थिर काष्ठा adapter *adap)
अणु
	वापस adapter_info(adap)->caps & SUPPORTED_AUI;
पूर्ण

अटल अंतरभूत पूर्णांक is_10G(स्थिर काष्ठा adapter *adap)
अणु
	वापस adapter_info(adap)->caps & SUPPORTED_10000baseT_Full;
पूर्ण

अटल अंतरभूत पूर्णांक is_offload(स्थिर काष्ठा adapter *adap)
अणु
	वापस adap->params.offload;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक core_ticks_per_usec(स्थिर काष्ठा adapter *adap)
अणु
	वापस adap->params.vpd.cclk / 1000;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक is_pcie(स्थिर काष्ठा adapter *adap)
अणु
	वापस adap->params.pci.variant == PCI_VARIANT_PCIE;
पूर्ण

व्योम t3_set_reg_field(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr, u32 mask,
		      u32 val);
व्योम t3_ग_लिखो_regs(काष्ठा adapter *adapter, स्थिर काष्ठा addr_val_pair *p,
		   पूर्णांक n, अचिन्हित पूर्णांक offset);
पूर्णांक t3_रुको_op_करोne_val(काष्ठा adapter *adapter, पूर्णांक reg, u32 mask,
			पूर्णांक polarity, पूर्णांक attempts, पूर्णांक delay, u32 *valp);
अटल अंतरभूत पूर्णांक t3_रुको_op_करोne(काष्ठा adapter *adapter, पूर्णांक reg, u32 mask,
				  पूर्णांक polarity, पूर्णांक attempts, पूर्णांक delay)
अणु
	वापस t3_रुको_op_करोne_val(adapter, reg, mask, polarity, attempts,
				   delay, शून्य);
पूर्ण
पूर्णांक t3_mdio_change_bits(काष्ठा cphy *phy, पूर्णांक mmd, पूर्णांक reg, अचिन्हित पूर्णांक clear,
			अचिन्हित पूर्णांक set);
पूर्णांक t3_phy_reset(काष्ठा cphy *phy, पूर्णांक mmd, पूर्णांक रुको);
पूर्णांक t3_phy_advertise(काष्ठा cphy *phy, अचिन्हित पूर्णांक advert);
पूर्णांक t3_phy_advertise_fiber(काष्ठा cphy *phy, अचिन्हित पूर्णांक advert);
पूर्णांक t3_set_phy_speed_duplex(काष्ठा cphy *phy, पूर्णांक speed, पूर्णांक duplex);
पूर्णांक t3_phy_lasi_पूर्णांकr_enable(काष्ठा cphy *phy);
पूर्णांक t3_phy_lasi_पूर्णांकr_disable(काष्ठा cphy *phy);
पूर्णांक t3_phy_lasi_पूर्णांकr_clear(काष्ठा cphy *phy);
पूर्णांक t3_phy_lasi_पूर्णांकr_handler(काष्ठा cphy *phy);

व्योम t3_पूर्णांकr_enable(काष्ठा adapter *adapter);
व्योम t3_पूर्णांकr_disable(काष्ठा adapter *adapter);
व्योम t3_पूर्णांकr_clear(काष्ठा adapter *adapter);
व्योम t3_xgm_पूर्णांकr_enable(काष्ठा adapter *adapter, पूर्णांक idx);
व्योम t3_xgm_पूर्णांकr_disable(काष्ठा adapter *adapter, पूर्णांक idx);
व्योम t3_port_पूर्णांकr_enable(काष्ठा adapter *adapter, पूर्णांक idx);
व्योम t3_port_पूर्णांकr_disable(काष्ठा adapter *adapter, पूर्णांक idx);
पूर्णांक t3_slow_पूर्णांकr_handler(काष्ठा adapter *adapter);
पूर्णांक t3_phy_पूर्णांकr_handler(काष्ठा adapter *adapter);

व्योम t3_link_changed(काष्ठा adapter *adapter, पूर्णांक port_id);
व्योम t3_link_fault(काष्ठा adapter *adapter, पूर्णांक port_id);
पूर्णांक t3_link_start(काष्ठा cphy *phy, काष्ठा cmac *mac, काष्ठा link_config *lc);
स्थिर काष्ठा adapter_info *t3_get_adapter_info(अचिन्हित पूर्णांक board_id);
पूर्णांक t3_seeprom_पढ़ो(काष्ठा adapter *adapter, u32 addr, __le32 *data);
पूर्णांक t3_seeprom_ग_लिखो(काष्ठा adapter *adapter, u32 addr, __le32 data);
पूर्णांक t3_seeprom_wp(काष्ठा adapter *adapter, पूर्णांक enable);
पूर्णांक t3_get_tp_version(काष्ठा adapter *adapter, u32 *vers);
पूर्णांक t3_check_tpsram_version(काष्ठा adapter *adapter);
पूर्णांक t3_check_tpsram(काष्ठा adapter *adapter, स्थिर u8 *tp_ram,
		    अचिन्हित पूर्णांक size);
पूर्णांक t3_set_proto_sram(काष्ठा adapter *adap, स्थिर u8 *data);
पूर्णांक t3_load_fw(काष्ठा adapter *adapter, स्थिर u8 * fw_data, अचिन्हित पूर्णांक size);
पूर्णांक t3_get_fw_version(काष्ठा adapter *adapter, u32 *vers);
पूर्णांक t3_check_fw_version(काष्ठा adapter *adapter);
पूर्णांक t3_init_hw(काष्ठा adapter *adapter, u32 fw_params);
पूर्णांक t3_reset_adapter(काष्ठा adapter *adapter);
पूर्णांक t3_prep_adapter(काष्ठा adapter *adapter, स्थिर काष्ठा adapter_info *ai,
		    पूर्णांक reset);
पूर्णांक t3_replay_prep_adapter(काष्ठा adapter *adapter);
व्योम t3_led_पढ़ोy(काष्ठा adapter *adapter);
व्योम t3_fatal_err(काष्ठा adapter *adapter);
व्योम t3_set_vlan_accel(काष्ठा adapter *adapter, अचिन्हित पूर्णांक ports, पूर्णांक on);
व्योम t3_config_rss(काष्ठा adapter *adapter, अचिन्हित पूर्णांक rss_config,
		   स्थिर u8 * cpus, स्थिर u16 *rspq);
पूर्णांक t3_cim_ctl_blk_पढ़ो(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr,
			अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक *valp);
पूर्णांक t3_mc7_bd_पढ़ो(काष्ठा mc7 *mc7, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक n,
		   u64 *buf);

पूर्णांक t3_mac_reset(काष्ठा cmac *mac);
व्योम t3b_pcs_reset(काष्ठा cmac *mac);
व्योम t3_mac_disable_exact_filters(काष्ठा cmac *mac);
व्योम t3_mac_enable_exact_filters(काष्ठा cmac *mac);
पूर्णांक t3_mac_enable(काष्ठा cmac *mac, पूर्णांक which);
पूर्णांक t3_mac_disable(काष्ठा cmac *mac, पूर्णांक which);
पूर्णांक t3_mac_set_mtu(काष्ठा cmac *mac, अचिन्हित पूर्णांक mtu);
पूर्णांक t3_mac_set_rx_mode(काष्ठा cmac *mac, काष्ठा net_device *dev);
पूर्णांक t3_mac_set_address(काष्ठा cmac *mac, अचिन्हित पूर्णांक idx, u8 addr[6]);
पूर्णांक t3_mac_set_num_ucast(काष्ठा cmac *mac, पूर्णांक n);
स्थिर काष्ठा mac_stats *t3_mac_update_stats(काष्ठा cmac *mac);
पूर्णांक t3_mac_set_speed_duplex_fc(काष्ठा cmac *mac, पूर्णांक speed, पूर्णांक duplex, पूर्णांक fc);
पूर्णांक t3b2_mac_watchकरोg_task(काष्ठा cmac *mac);

व्योम t3_mc5_prep(काष्ठा adapter *adapter, काष्ठा mc5 *mc5, पूर्णांक mode);
पूर्णांक t3_mc5_init(काष्ठा mc5 *mc5, अचिन्हित पूर्णांक nservers, अचिन्हित पूर्णांक nfilters,
		अचिन्हित पूर्णांक nroutes);
व्योम t3_mc5_पूर्णांकr_handler(काष्ठा mc5 *mc5);

व्योम t3_tp_set_offload_mode(काष्ठा adapter *adap, पूर्णांक enable);
व्योम t3_tp_get_mib_stats(काष्ठा adapter *adap, काष्ठा tp_mib_stats *tps);
व्योम t3_load_mtus(काष्ठा adapter *adap, अचिन्हित लघु mtus[NMTUS],
		  अचिन्हित लघु alpha[NCCTRL_WIN],
		  अचिन्हित लघु beta[NCCTRL_WIN], अचिन्हित लघु mtu_cap);
व्योम t3_config_trace_filter(काष्ठा adapter *adapter,
			    स्थिर काष्ठा trace_params *tp, पूर्णांक filter_index,
			    पूर्णांक invert, पूर्णांक enable);
पूर्णांक t3_config_sched(काष्ठा adapter *adap, अचिन्हित पूर्णांक kbps, पूर्णांक sched);

व्योम t3_sge_prep(काष्ठा adapter *adap, काष्ठा sge_params *p);
व्योम t3_sge_init(काष्ठा adapter *adap, काष्ठा sge_params *p);
पूर्णांक t3_sge_init_ecntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, पूर्णांक gts_enable,
		       क्रमागत sge_context_type type, पूर्णांक respq, u64 base_addr,
		       अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक token, पूर्णांक gen,
		       अचिन्हित पूर्णांक cidx);
पूर्णांक t3_sge_init_flcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id,
			पूर्णांक gts_enable, u64 base_addr, अचिन्हित पूर्णांक size,
			अचिन्हित पूर्णांक esize, अचिन्हित पूर्णांक cong_thres, पूर्णांक gen,
			अचिन्हित पूर्णांक cidx);
पूर्णांक t3_sge_init_rspcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id,
			 पूर्णांक irq_vec_idx, u64 base_addr, अचिन्हित पूर्णांक size,
			 अचिन्हित पूर्णांक fl_thres, पूर्णांक gen, अचिन्हित पूर्णांक cidx);
पूर्णांक t3_sge_init_cqcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, u64 base_addr,
			अचिन्हित पूर्णांक size, पूर्णांक rspq, पूर्णांक ovfl_mode,
			अचिन्हित पूर्णांक credits, अचिन्हित पूर्णांक credit_thres);
पूर्णांक t3_sge_enable_ecntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, पूर्णांक enable);
पूर्णांक t3_sge_disable_fl(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id);
पूर्णांक t3_sge_disable_rspcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id);
पूर्णांक t3_sge_disable_cqcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id);
पूर्णांक t3_sge_cqcntxt_op(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक op,
		      अचिन्हित पूर्णांक credits);

पूर्णांक t3_vsc8211_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops);
पूर्णांक t3_ael1002_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops);
पूर्णांक t3_ael1006_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops);
पूर्णांक t3_ael2005_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops);
पूर्णांक t3_ael2020_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops);
पूर्णांक t3_qt2045_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter, पूर्णांक phy_addr,
		       स्थिर काष्ठा mdio_ops *mdio_ops);
पूर्णांक t3_xaui_direct_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			    पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops);
पूर्णांक t3_aq100x_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			    पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops);
#पूर्ण_अगर				/* __CHELSIO_COMMON_H */
