<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/ibm/emac/core.h
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller.
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Copyright (c) 2004, 2005 Zultys Technologies.
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *
 * Based on original work by
 *      Armin Kuster <akuster@mvista.com>
 * 	Johnnie Peters <jpeters@mvista.com>
 *      Copyright 2000, 2001 MontaVista Softare Inc.
 */
#अगर_अघोषित __IBM_NEWEMAC_CORE_H
#घोषणा __IBM_NEWEMAC_CORE_H

#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dcr.h>

#समावेश "emac.h"
#समावेश "phy.h"
#समावेश "zmii.h"
#समावेश "rgmii.h"
#समावेश "mal.h"
#समावेश "tah.h"
#समावेश "debug.h"

#घोषणा NUM_TX_BUFF			CONFIG_IBM_EMAC_TXB
#घोषणा NUM_RX_BUFF			CONFIG_IBM_EMAC_RXB

/* Simple sanity check */
#अगर NUM_TX_BUFF > 256 || NUM_RX_BUFF > 256
#त्रुटि Invalid number of buffer descriptors (greater than 256)
#पूर्ण_अगर

#घोषणा EMAC_MIN_MTU			46

/* Maximum L2 header length (VLAN tagged, no FCS) */
#घोषणा EMAC_MTU_OVERHEAD		(6 * 2 + 2 + 4)

/* RX BD size क्रम the given MTU */
अटल अंतरभूत पूर्णांक emac_rx_size(पूर्णांक mtu)
अणु
	अगर (mtu > ETH_DATA_LEN)
		वापस MAL_MAX_RX_SIZE;
	अन्यथा
		वापस mal_rx_size(ETH_DATA_LEN + EMAC_MTU_OVERHEAD);
पूर्ण

/* Size of RX skb क्रम the given MTU */
अटल अंतरभूत पूर्णांक emac_rx_skb_size(पूर्णांक mtu)
अणु
	पूर्णांक size = max(mtu + EMAC_MTU_OVERHEAD, emac_rx_size(mtu));

	वापस SKB_DATA_ALIGN(size + NET_IP_ALIGN) + NET_SKB_PAD;
पूर्ण

/* RX DMA sync size */
अटल अंतरभूत पूर्णांक emac_rx_sync_size(पूर्णांक mtu)
अणु
	वापस SKB_DATA_ALIGN(emac_rx_size(mtu) + NET_IP_ALIGN);
पूर्ण

/* Driver statistcs is split पूर्णांकo two parts to make it more cache मित्रly:
 *   - normal statistics (packet count, etc)
 *   - error statistics
 *
 * When statistics is requested by ethtool, these parts are concatenated,
 * normal one goes first.
 *
 * Please, keep these काष्ठाures in sync with emac_stats_keys.
 */

/* Normal TX/RX Statistics */
काष्ठा emac_stats अणु
	u64 rx_packets;
	u64 rx_bytes;
	u64 tx_packets;
	u64 tx_bytes;
	u64 rx_packets_csum;
	u64 tx_packets_csum;
पूर्ण;

/* Error statistics */
काष्ठा emac_error_stats अणु
	u64 tx_unकरो;

	/* Software RX Errors */
	u64 rx_dropped_stack;
	u64 rx_dropped_oom;
	u64 rx_dropped_error;
	u64 rx_dropped_resize;
	u64 rx_dropped_mtu;
	u64 rx_stopped;
	/* BD reported RX errors */
	u64 rx_bd_errors;
	u64 rx_bd_overrun;
	u64 rx_bd_bad_packet;
	u64 rx_bd_runt_packet;
	u64 rx_bd_लघु_event;
	u64 rx_bd_alignment_error;
	u64 rx_bd_bad_fcs;
	u64 rx_bd_packet_too_दीर्घ;
	u64 rx_bd_out_of_range;
	u64 rx_bd_in_range;
	/* EMAC IRQ reported RX errors */
	u64 rx_parity;
	u64 rx_fअगरo_overrun;
	u64 rx_overrun;
	u64 rx_bad_packet;
	u64 rx_runt_packet;
	u64 rx_लघु_event;
	u64 rx_alignment_error;
	u64 rx_bad_fcs;
	u64 rx_packet_too_दीर्घ;
	u64 rx_out_of_range;
	u64 rx_in_range;

	/* Software TX Errors */
	u64 tx_dropped;
	/* BD reported TX errors */
	u64 tx_bd_errors;
	u64 tx_bd_bad_fcs;
	u64 tx_bd_carrier_loss;
	u64 tx_bd_excessive_deferral;
	u64 tx_bd_excessive_collisions;
	u64 tx_bd_late_collision;
	u64 tx_bd_multple_collisions;
	u64 tx_bd_single_collision;
	u64 tx_bd_underrun;
	u64 tx_bd_sqe;
	/* EMAC IRQ reported TX errors */
	u64 tx_parity;
	u64 tx_underrun;
	u64 tx_sqe;
	u64 tx_errors;
पूर्ण;

#घोषणा EMAC_ETHTOOL_STATS_COUNT	((माप(काष्ठा emac_stats) + \
					  माप(काष्ठा emac_error_stats)) \
					 / माप(u64))

काष्ठा emac_instance अणु
	काष्ठा net_device		*ndev;
	काष्ठा emac_regs		__iomem *emacp;
	काष्ठा platक्रमm_device		*ofdev;
	काष्ठा device_node		**blist; /* bootlist entry */

	/* MAL linkage */
	u32				mal_ph;
	काष्ठा platक्रमm_device		*mal_dev;
	u32				mal_rx_chan;
	u32				mal_tx_chan;
	काष्ठा mal_instance		*mal;
	काष्ठा mal_commac		commac;

	/* PHY infos */
	phy_पूर्णांकerface_t			phy_mode;
	u32				phy_map;
	u32				phy_address;
	u32				phy_feat_exc;
	काष्ठा mii_phy			phy;
	काष्ठा mutex			link_lock;
	काष्ठा delayed_work		link_work;
	पूर्णांक				link_polling;

	/* GPCS PHY infos */
	u32				gpcs_address;

	/* Shared MDIO अगर any */
	u32				mdio_ph;
	काष्ठा platक्रमm_device		*mdio_dev;
	काष्ठा emac_instance		*mdio_instance;
	काष्ठा mutex			mdio_lock;

	/* Device-tree based phy configuration */
	काष्ठा mii_bus			*mii_bus;
	काष्ठा phy_device		*phy_dev;

	/* ZMII infos अगर any */
	u32				zmii_ph;
	u32				zmii_port;
	काष्ठा platक्रमm_device		*zmii_dev;

	/* RGMII infos अगर any */
	u32				rgmii_ph;
	u32				rgmii_port;
	काष्ठा platक्रमm_device		*rgmii_dev;

	/* TAH infos अगर any */
	u32				tah_ph;
	u32				tah_port;
	काष्ठा platक्रमm_device		*tah_dev;

	/* IRQs */
	पूर्णांक				wol_irq;
	पूर्णांक				emac_irq;

	/* OPB bus frequency in Mhz */
	u32				opb_bus_freq;

	/* Cell index within an ASIC (क्रम clk mgmnt) */
	u32				cell_index;

	/* Max supported MTU */
	u32				max_mtu;

	/* Feature bits (from probe table) */
	अचिन्हित पूर्णांक			features;

	/* Tx and Rx fअगरo sizes & other infos in bytes */
	u32				tx_fअगरo_size;
	u32				tx_fअगरo_size_gige;
	u32				rx_fअगरo_size;
	u32				rx_fअगरo_size_gige;
	u32				fअगरo_entry_size;
	u32				mal_burst_size; /* move to MAL ? */

	/* IAHT and GAHT filter parameterization */
	u32				xaht_slots_shअगरt;
	u32				xaht_width_shअगरt;

	/* Descriptor management
	 */
	काष्ठा mal_descriptor		*tx_desc;
	पूर्णांक				tx_cnt;
	पूर्णांक				tx_slot;
	पूर्णांक				ack_slot;

	काष्ठा mal_descriptor		*rx_desc;
	पूर्णांक				rx_slot;
	काष्ठा sk_buff			*rx_sg_skb;	/* 1 */
	पूर्णांक 				rx_skb_size;
	पूर्णांक				rx_sync_size;

	काष्ठा sk_buff			*tx_skb[NUM_TX_BUFF];
	काष्ठा sk_buff			*rx_skb[NUM_RX_BUFF];

	/* Stats
	 */
	काष्ठा emac_error_stats		estats;
	काष्ठा emac_stats 		stats;

	/* Misc
	 */
	पूर्णांक				reset_failed;
	पूर्णांक				stop_समयout;	/* in us */
	पूर्णांक				no_mcast;
	पूर्णांक				mcast_pending;
	पूर्णांक				खोलोed;
	काष्ठा work_काष्ठा		reset_work;
	spinlock_t			lock;
पूर्ण;

/*
 * Features of various EMAC implementations
 */

/*
 * No flow control on 40x according to the original driver
 */
#घोषणा EMAC_FTR_NO_FLOW_CONTROL_40x	0x00000001
/*
 * Cell is an EMAC4
 */
#घोषणा EMAC_FTR_EMAC4			0x00000002
/*
 * For the 440SPe, AMCC inexplicably changed the polarity of
 * the "operation complete" bit in the MII control रेजिस्टर.
 */
#घोषणा EMAC_FTR_STACR_OC_INVERT	0x00000004
/*
 * Set अगर we have a TAH.
 */
#घोषणा EMAC_FTR_HAS_TAH		0x00000008
/*
 * Set अगर we have a ZMII.
 */
#घोषणा EMAC_FTR_HAS_ZMII		0x00000010
/*
 * Set अगर we have a RGMII.
 */
#घोषणा EMAC_FTR_HAS_RGMII		0x00000020
/*
 * Set अगर we have new type STACR with STAOPC
 */
#घोषणा EMAC_FTR_HAS_NEW_STACR		0x00000040
/*
 * Set अगर we need phy घड़ी workaround क्रम 440gx
 */
#घोषणा EMAC_FTR_440GX_PHY_CLK_FIX	0x00000080
/*
 * Set अगर we need phy घड़ी workaround क्रम 440ep or 440gr
 */
#घोषणा EMAC_FTR_440EP_PHY_CLK_FIX	0x00000100
/*
 * The 405EX and 460EX contain the EMAC4SYNC core
 */
#घोषणा EMAC_FTR_EMAC4SYNC		0x00000200
/*
 * Set अगर we need phy घड़ी workaround क्रम 460ex or 460gt
 */
#घोषणा EMAC_FTR_460EX_PHY_CLK_FIX	0x00000400
/*
 * APM821xx requires Jumbo frame size set explicitly
 */
#घोषणा EMAC_APM821XX_REQ_JUMBO_FRAME_SIZE	0x00000800
/*
 * APM821xx करोes not support Half Duplex mode
 */
#घोषणा EMAC_FTR_APM821XX_NO_HALF_DUPLEX	0x00001000

/* Right now, we करोn't quite handle the always/possible masks on the
 * most optimal way as we करोn't have a way to say something like
 * always EMAC4. Patches welcome.
 */
क्रमागत अणु
	EMAC_FTRS_ALWAYS	= 0,

	EMAC_FTRS_POSSIBLE	=
#अगर_घोषित CONFIG_IBM_EMAC_EMAC4
	    EMAC_FTR_EMAC4	| EMAC_FTR_EMAC4SYNC	|
	    EMAC_FTR_HAS_NEW_STACR	|
	    EMAC_FTR_STACR_OC_INVERT | EMAC_FTR_440GX_PHY_CLK_FIX |
#पूर्ण_अगर
#अगर_घोषित CONFIG_IBM_EMAC_TAH
	    EMAC_FTR_HAS_TAH	|
#पूर्ण_अगर
#अगर_घोषित CONFIG_IBM_EMAC_ZMII
	    EMAC_FTR_HAS_ZMII	|
#पूर्ण_अगर
#अगर_घोषित CONFIG_IBM_EMAC_RGMII
	    EMAC_FTR_HAS_RGMII	|
#पूर्ण_अगर
#अगर_घोषित CONFIG_IBM_EMAC_NO_FLOW_CTRL
	    EMAC_FTR_NO_FLOW_CONTROL_40x |
#पूर्ण_अगर
	EMAC_FTR_460EX_PHY_CLK_FIX |
	EMAC_FTR_440EP_PHY_CLK_FIX |
	EMAC_APM821XX_REQ_JUMBO_FRAME_SIZE |
	EMAC_FTR_APM821XX_NO_HALF_DUPLEX,
पूर्ण;

अटल अंतरभूत पूर्णांक emac_has_feature(काष्ठा emac_instance *dev,
				   अचिन्हित दीर्घ feature)
अणु
	वापस (EMAC_FTRS_ALWAYS & feature) ||
	       (EMAC_FTRS_POSSIBLE & dev->features & feature);
पूर्ण

/*
 * Various instances of the EMAC core have varying 1) number of
 * address match slots, 2) width of the रेजिस्टरs क्रम handling address
 * match slots, 3) number of रेजिस्टरs क्रम handling address match
 * slots and 4) base offset क्रम those रेजिस्टरs.
 *
 * These macros and अंतरभूतs handle these dअगरferences based on
 * parameters supplied by the device काष्ठाure which are, in turn,
 * initialized based on the "compatible" entry in the device tree.
 */

#घोषणा	EMAC4_XAHT_SLOTS_SHIFT		6
#घोषणा	EMAC4_XAHT_WIDTH_SHIFT		4

#घोषणा	EMAC4SYNC_XAHT_SLOTS_SHIFT	8
#घोषणा	EMAC4SYNC_XAHT_WIDTH_SHIFT	5

/* The largest span between slots and widths above is 3 */
#घोषणा	EMAC_XAHT_MAX_REGS		(1 << 3)

#घोषणा	EMAC_XAHT_SLOTS(dev)         	(1 << (dev)->xaht_slots_shअगरt)
#घोषणा	EMAC_XAHT_WIDTH(dev)         	(1 << (dev)->xaht_width_shअगरt)
#घोषणा	EMAC_XAHT_REGS(dev)          	(1 << ((dev)->xaht_slots_shअगरt - \
					       (dev)->xaht_width_shअगरt))

#घोषणा	EMAC_XAHT_CRC_TO_SLOT(dev, crc)			\
	((EMAC_XAHT_SLOTS(dev) - 1) -			\
	 ((crc) >> ((माप (u32) * BITS_PER_BYTE) -	\
		    (dev)->xaht_slots_shअगरt)))

#घोषणा	EMAC_XAHT_SLOT_TO_REG(dev, slot)		\
	((slot) >> (dev)->xaht_width_shअगरt)

#घोषणा	EMAC_XAHT_SLOT_TO_MASK(dev, slot)		\
	((u32)(1 << (EMAC_XAHT_WIDTH(dev) - 1)) >>	\
	 ((slot) & (u32)(EMAC_XAHT_WIDTH(dev) - 1)))

अटल अंतरभूत u32 *emac_xaht_base(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	पूर्णांक offset;

	/* The first IAHT entry always is the base of the block of
	 * IAHT and GAHT रेजिस्टरs.
	 */
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4SYNC))
		offset = दुरत्व(काष्ठा emac_regs, u1.emac4sync.iaht1);
	अन्यथा
		offset = दुरत्व(काष्ठा emac_regs, u0.emac4.iaht1);

	वापस (u32 *)((सूचक_भेद_प्रकार)p + offset);
पूर्ण

अटल अंतरभूत u32 *emac_gaht_base(काष्ठा emac_instance *dev)
अणु
	/* GAHT रेजिस्टरs always come after an identical number of
	 * IAHT रेजिस्टरs.
	 */
	वापस emac_xaht_base(dev) + EMAC_XAHT_REGS(dev);
पूर्ण

अटल अंतरभूत u32 *emac_iaht_base(काष्ठा emac_instance *dev)
अणु
	/* IAHT रेजिस्टरs always come beक्रमe an identical number of
	 * GAHT रेजिस्टरs.
	 */
	वापस emac_xaht_base(dev);
पूर्ण

/* Ethtool get_regs complex data.
 * We want to get not just EMAC रेजिस्टरs, but also MAL, ZMII, RGMII, TAH
 * when available.
 *
 * Returned BLOB consists of the ibm_emac_ethtool_regs_hdr,
 * MAL रेजिस्टरs, EMAC रेजिस्टरs and optional ZMII, RGMII, TAH रेजिस्टरs.
 * Each रेजिस्टर component is preceded with emac_ethtool_regs_subhdr.
 * Order of the optional headers follows their relative bit posititions
 * in emac_ethtool_regs_hdr.components
 */
#घोषणा EMAC_ETHTOOL_REGS_ZMII		0x00000001
#घोषणा EMAC_ETHTOOL_REGS_RGMII		0x00000002
#घोषणा EMAC_ETHTOOL_REGS_TAH		0x00000004

काष्ठा emac_ethtool_regs_hdr अणु
	u32 components;
पूर्ण;

काष्ठा emac_ethtool_regs_subhdr अणु
	u32 version;
	u32 index;
पूर्ण;

#घोषणा EMAC_ETHTOOL_REGS_VER		3
#घोषणा EMAC4_ETHTOOL_REGS_VER		4
#घोषणा EMAC4SYNC_ETHTOOL_REGS_VER	5

#पूर्ण_अगर /* __IBM_NEWEMAC_CORE_H */
