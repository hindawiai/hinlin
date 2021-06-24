<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * DaVinci Ethernet Medium Access Controller
 *
 * DaVinci EMAC is based upon CPPI 3.0 TI DMA engine
 *
 * Copyright (C) 2009 Texas Instruments.
 *
 * ---------------------------------------------------------------------------
 * History:
 * 0-5 A number of folks worked on this driver in bits and pieces but the major
 *     contribution came from Suraj Iyer and Anant Gole
 * 6.0 Anant Gole - rewrote the driver as per Linux conventions
 * 6.1 Chaithrika U S - added support क्रम Gigabit and RMII features,
 *     PHY layer usage
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/phy.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/davinci_emac.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_net.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/page.h>

#समावेश "cpsw.h"
#समावेश "davinci_cpdma.h"

अटल पूर्णांक debug_level;
module_param(debug_level, पूर्णांक, 0);
MODULE_PARM_DESC(debug_level, "DaVinci EMAC debug level (NETIF_MSG bits)");

/* Netअगर debug messages possible */
#घोषणा DAVINCI_EMAC_DEBUG	(NETIF_MSG_DRV | \
				NETIF_MSG_PROBE | \
				NETIF_MSG_LINK | \
				NETIF_MSG_TIMER | \
				NETIF_MSG_IFDOWN | \
				NETIF_MSG_IFUP | \
				NETIF_MSG_RX_ERR | \
				NETIF_MSG_TX_ERR | \
				NETIF_MSG_TX_QUEUED | \
				NETIF_MSG_INTR | \
				NETIF_MSG_TX_DONE | \
				NETIF_MSG_RX_STATUS | \
				NETIF_MSG_PKTDATA | \
				NETIF_MSG_HW | \
				NETIF_MSG_WOL)

/* version info */
#घोषणा EMAC_MAJOR_VERSION	6
#घोषणा EMAC_MINOR_VERSION	1
#घोषणा EMAC_MODULE_VERSION	"6.1"
MODULE_VERSION(EMAC_MODULE_VERSION);
अटल स्थिर अक्षर emac_version_string[] = "TI DaVinci EMAC Linux v6.1";

/* Configuration items */
#घोषणा EMAC_DEF_PASS_CRC		(0) /* Do not pass CRC up to frames */
#घोषणा EMAC_DEF_QOS_EN			(0) /* EMAC proprietary QoS disabled */
#घोषणा EMAC_DEF_NO_BUFF_CHAIN		(0) /* No buffer chain */
#घोषणा EMAC_DEF_MACCTRL_FRAME_EN	(0) /* Discard Maccontrol frames */
#घोषणा EMAC_DEF_SHORT_FRAME_EN		(0) /* Discard लघु frames */
#घोषणा EMAC_DEF_ERROR_FRAME_EN		(0) /* Discard error frames */
#घोषणा EMAC_DEF_PROM_EN		(0) /* Promiscuous disabled */
#घोषणा EMAC_DEF_PROM_CH		(0) /* Promiscuous channel is 0 */
#घोषणा EMAC_DEF_BCAST_EN		(1) /* Broadcast enabled */
#घोषणा EMAC_DEF_BCAST_CH		(0) /* Broadcast channel is 0 */
#घोषणा EMAC_DEF_MCAST_EN		(1) /* Multicast enabled */
#घोषणा EMAC_DEF_MCAST_CH		(0) /* Multicast channel is 0 */

#घोषणा EMAC_DEF_TXPRIO_FIXED		(1) /* TX Priority is fixed */
#घोषणा EMAC_DEF_TXPACING_EN		(0) /* TX pacing NOT supported*/

#घोषणा EMAC_DEF_BUFFER_OFFSET		(0) /* Buffer offset to DMA (future) */
#घोषणा EMAC_DEF_MIN_ETHPKTSIZE		(60) /* Minimum ethernet pkt size */
#घोषणा EMAC_DEF_MAX_FRAME_SIZE		(1500 + 14 + 4 + 4)
#घोषणा EMAC_DEF_TX_CH			(0) /* Default 0th channel */
#घोषणा EMAC_DEF_RX_CH			(0) /* Default 0th channel */
#घोषणा EMAC_DEF_RX_NUM_DESC		(128)
#घोषणा EMAC_DEF_MAX_TX_CH		(1) /* Max TX channels configured */
#घोषणा EMAC_DEF_MAX_RX_CH		(1) /* Max RX channels configured */
#घोषणा EMAC_POLL_WEIGHT		(64) /* Default NAPI poll weight */

/* Buffer descriptor parameters */
#घोषणा EMAC_DEF_TX_MAX_SERVICE		(32) /* TX max service BD's */
#घोषणा EMAC_DEF_RX_MAX_SERVICE		(64) /* should = netdev->weight */

/* EMAC रेजिस्टर related defines */
#घोषणा EMAC_ALL_MULTI_REG_VALUE	(0xFFFFFFFF)
#घोषणा EMAC_NUM_MULTICAST_BITS		(64)
#घोषणा EMAC_TX_CONTROL_TX_ENABLE_VAL	(0x1)
#घोषणा EMAC_RX_CONTROL_RX_ENABLE_VAL	(0x1)
#घोषणा EMAC_MAC_HOST_ERR_INTMASK_VAL	(0x2)
#घोषणा EMAC_RX_UNICAST_CLEAR_ALL	(0xFF)
#घोषणा EMAC_INT_MASK_CLEAR		(0xFF)

/* RX MBP रेजिस्टर bit positions */
#घोषणा EMAC_RXMBP_PASSCRC_MASK		BIT(30)
#घोषणा EMAC_RXMBP_QOSEN_MASK		BIT(29)
#घोषणा EMAC_RXMBP_NOCHAIN_MASK		BIT(28)
#घोषणा EMAC_RXMBP_CMFEN_MASK		BIT(24)
#घोषणा EMAC_RXMBP_CSFEN_MASK		BIT(23)
#घोषणा EMAC_RXMBP_CEFEN_MASK		BIT(22)
#घोषणा EMAC_RXMBP_CAFEN_MASK		BIT(21)
#घोषणा EMAC_RXMBP_PROMCH_SHIFT		(16)
#घोषणा EMAC_RXMBP_PROMCH_MASK		(0x7 << 16)
#घोषणा EMAC_RXMBP_BROADEN_MASK		BIT(13)
#घोषणा EMAC_RXMBP_BROADCH_SHIFT	(8)
#घोषणा EMAC_RXMBP_BROADCH_MASK		(0x7 << 8)
#घोषणा EMAC_RXMBP_MULTIEN_MASK		BIT(5)
#घोषणा EMAC_RXMBP_MULTICH_SHIFT	(0)
#घोषणा EMAC_RXMBP_MULTICH_MASK		(0x7)
#घोषणा EMAC_RXMBP_CHMASK		(0x7)

/* EMAC रेजिस्टर definitions/bit maps used */
# define EMAC_MBP_RXPROMISC		(0x00200000)
# define EMAC_MBP_PROMISCCH(ch)		(((ch) & 0x7) << 16)
# define EMAC_MBP_RXBCAST		(0x00002000)
# define EMAC_MBP_BCASTCHAN(ch)		(((ch) & 0x7) << 8)
# define EMAC_MBP_RXMCAST		(0x00000020)
# define EMAC_MBP_MCASTCHAN(ch)		((ch) & 0x7)

/* EMAC mac_control रेजिस्टर */
#घोषणा EMAC_MACCONTROL_TXPTYPE		BIT(9)
#घोषणा EMAC_MACCONTROL_TXPACEEN	BIT(6)
#घोषणा EMAC_MACCONTROL_GMIIEN		BIT(5)
#घोषणा EMAC_MACCONTROL_GIGABITEN	BIT(7)
#घोषणा EMAC_MACCONTROL_FULLDUPLEXEN	BIT(0)
#घोषणा EMAC_MACCONTROL_RMIISPEED_MASK	BIT(15)

/* GIGABIT MODE related bits */
#घोषणा EMAC_DM646X_MACCONTORL_GIG	BIT(7)
#घोषणा EMAC_DM646X_MACCONTORL_GIGFORCE	BIT(17)

/* EMAC mac_status रेजिस्टर */
#घोषणा EMAC_MACSTATUS_TXERRCODE_MASK	(0xF00000)
#घोषणा EMAC_MACSTATUS_TXERRCODE_SHIFT	(20)
#घोषणा EMAC_MACSTATUS_TXERRCH_MASK	(0x70000)
#घोषणा EMAC_MACSTATUS_TXERRCH_SHIFT	(16)
#घोषणा EMAC_MACSTATUS_RXERRCODE_MASK	(0xF000)
#घोषणा EMAC_MACSTATUS_RXERRCODE_SHIFT	(12)
#घोषणा EMAC_MACSTATUS_RXERRCH_MASK	(0x700)
#घोषणा EMAC_MACSTATUS_RXERRCH_SHIFT	(8)

/* EMAC RX रेजिस्टर masks */
#घोषणा EMAC_RX_MAX_LEN_MASK		(0xFFFF)
#घोषणा EMAC_RX_BUFFER_OFFSET_MASK	(0xFFFF)

/* MAC_IN_VECTOR (0x180) रेजिस्टर bit fields */
#घोषणा EMAC_DM644X_MAC_IN_VECTOR_HOST_INT	BIT(17)
#घोषणा EMAC_DM644X_MAC_IN_VECTOR_STATPEND_INT	BIT(16)
#घोषणा EMAC_DM644X_MAC_IN_VECTOR_RX_INT_VEC	BIT(8)
#घोषणा EMAC_DM644X_MAC_IN_VECTOR_TX_INT_VEC	BIT(0)

/** NOTE:: For DM646x the IN_VECTOR has changed */
#घोषणा EMAC_DM646X_MAC_IN_VECTOR_RX_INT_VEC	BIT(EMAC_DEF_RX_CH)
#घोषणा EMAC_DM646X_MAC_IN_VECTOR_TX_INT_VEC	BIT(16 + EMAC_DEF_TX_CH)
#घोषणा EMAC_DM646X_MAC_IN_VECTOR_HOST_INT	BIT(26)
#घोषणा EMAC_DM646X_MAC_IN_VECTOR_STATPEND_INT	BIT(27)

/* CPPI bit positions */
#घोषणा EMAC_CPPI_SOP_BIT		BIT(31)
#घोषणा EMAC_CPPI_EOP_BIT		BIT(30)
#घोषणा EMAC_CPPI_OWNERSHIP_BIT		BIT(29)
#घोषणा EMAC_CPPI_EOQ_BIT		BIT(28)
#घोषणा EMAC_CPPI_TEARDOWN_COMPLETE_BIT BIT(27)
#घोषणा EMAC_CPPI_PASS_CRC_BIT		BIT(26)
#घोषणा EMAC_RX_BD_BUF_SIZE		(0xFFFF)
#घोषणा EMAC_BD_LENGTH_FOR_CACHE	(16) /* only CPPI bytes */
#घोषणा EMAC_RX_BD_PKT_LENGTH_MASK	(0xFFFF)

/* Max hardware defines */
#घोषणा EMAC_MAX_TXRX_CHANNELS		 (8)  /* Max hardware channels */
#घोषणा EMAC_DEF_MAX_MULTICAST_ADDRESSES (64) /* Max mcast addr's */

/* EMAC Peripheral Device Register Memory Layout काष्ठाure */
#घोषणा EMAC_MACINVECTOR	0x90

#घोषणा EMAC_DM646X_MACEOIVECTOR	0x94

#घोषणा EMAC_MACINTSTATRAW	0xB0
#घोषणा EMAC_MACINTSTATMASKED	0xB4
#घोषणा EMAC_MACINTMASKSET	0xB8
#घोषणा EMAC_MACINTMASKCLEAR	0xBC

#घोषणा EMAC_RXMBPENABLE	0x100
#घोषणा EMAC_RXUNICASTSET	0x104
#घोषणा EMAC_RXUNICASTCLEAR	0x108
#घोषणा EMAC_RXMAXLEN		0x10C
#घोषणा EMAC_RXBUFFEROFFSET	0x110
#घोषणा EMAC_RXFILTERLOWTHRESH	0x114

#घोषणा EMAC_MACCONTROL		0x160
#घोषणा EMAC_MACSTATUS		0x164
#घोषणा EMAC_EMCONTROL		0x168
#घोषणा EMAC_FIFOCONTROL	0x16C
#घोषणा EMAC_MACCONFIG		0x170
#घोषणा EMAC_SOFTRESET		0x174
#घोषणा EMAC_MACSRCADDRLO	0x1D0
#घोषणा EMAC_MACSRCADDRHI	0x1D4
#घोषणा EMAC_MACHASH1		0x1D8
#घोषणा EMAC_MACHASH2		0x1DC
#घोषणा EMAC_MACADDRLO		0x500
#घोषणा EMAC_MACADDRHI		0x504
#घोषणा EMAC_MACINDEX		0x508

/* EMAC statistics रेजिस्टरs */
#घोषणा EMAC_RXGOODFRAMES	0x200
#घोषणा EMAC_RXBCASTFRAMES	0x204
#घोषणा EMAC_RXMCASTFRAMES	0x208
#घोषणा EMAC_RXPAUSEFRAMES	0x20C
#घोषणा EMAC_RXCRCERRORS	0x210
#घोषणा EMAC_RXALIGNCODEERRORS	0x214
#घोषणा EMAC_RXOVERSIZED	0x218
#घोषणा EMAC_RXJABBER		0x21C
#घोषणा EMAC_RXUNDERSIZED	0x220
#घोषणा EMAC_RXFRAGMENTS	0x224
#घोषणा EMAC_RXFILTERED		0x228
#घोषणा EMAC_RXQOSFILTERED	0x22C
#घोषणा EMAC_RXOCTETS		0x230
#घोषणा EMAC_TXGOODFRAMES	0x234
#घोषणा EMAC_TXBCASTFRAMES	0x238
#घोषणा EMAC_TXMCASTFRAMES	0x23C
#घोषणा EMAC_TXPAUSEFRAMES	0x240
#घोषणा EMAC_TXDEFERRED		0x244
#घोषणा EMAC_TXCOLLISION	0x248
#घोषणा EMAC_TXSINGLECOLL	0x24C
#घोषणा EMAC_TXMULTICOLL	0x250
#घोषणा EMAC_TXEXCESSIVECOLL	0x254
#घोषणा EMAC_TXLATECOLL		0x258
#घोषणा EMAC_TXUNDERRUN		0x25C
#घोषणा EMAC_TXCARRIERSENSE	0x260
#घोषणा EMAC_TXOCTETS		0x264
#घोषणा EMAC_NETOCTETS		0x280
#घोषणा EMAC_RXSOFOVERRUNS	0x284
#घोषणा EMAC_RXMOFOVERRUNS	0x288
#घोषणा EMAC_RXDMAOVERRUNS	0x28C

/* EMAC DM644x control रेजिस्टरs */
#घोषणा EMAC_CTRL_EWCTL		(0x4)
#घोषणा EMAC_CTRL_EWINTTCNT	(0x8)

/* EMAC DM644x control module masks */
#घोषणा EMAC_DM644X_EWINTCNT_MASK	0x1FFFF
#घोषणा EMAC_DM644X_INTMIN_INTVL	0x1
#घोषणा EMAC_DM644X_INTMAX_INTVL	(EMAC_DM644X_EWINTCNT_MASK)

/* EMAC DM646X control module रेजिस्टरs */
#घोषणा EMAC_DM646X_CMINTCTRL	0x0C
#घोषणा EMAC_DM646X_CMRXINTEN	0x14
#घोषणा EMAC_DM646X_CMTXINTEN	0x18
#घोषणा EMAC_DM646X_CMRXINTMAX	0x70
#घोषणा EMAC_DM646X_CMTXINTMAX	0x74

/* EMAC DM646X control module masks */
#घोषणा EMAC_DM646X_INTPACEEN		(0x3 << 16)
#घोषणा EMAC_DM646X_INTPRESCALE_MASK	(0x7FF << 0)
#घोषणा EMAC_DM646X_CMINTMAX_CNT	63
#घोषणा EMAC_DM646X_CMINTMIN_CNT	2
#घोषणा EMAC_DM646X_CMINTMAX_INTVL	(1000 / EMAC_DM646X_CMINTMIN_CNT)
#घोषणा EMAC_DM646X_CMINTMIN_INTVL	((1000 / EMAC_DM646X_CMINTMAX_CNT) + 1)


/* EMAC EOI codes क्रम C0 */
#घोषणा EMAC_DM646X_MAC_EOI_C0_RXEN	(0x01)
#घोषणा EMAC_DM646X_MAC_EOI_C0_TXEN	(0x02)

/* EMAC Stats Clear Mask */
#घोषणा EMAC_STATS_CLR_MASK    (0xFFFFFFFF)

/* emac_priv: EMAC निजी data काष्ठाure
 *
 * EMAC adapter निजी data काष्ठाure
 */
काष्ठा emac_priv अणु
	u32 msg_enable;
	काष्ठा net_device *ndev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा napi_काष्ठा napi;
	अक्षर mac_addr[6];
	व्योम __iomem *remap_addr;
	u32 emac_base_phys;
	व्योम __iomem *emac_base;
	व्योम __iomem *ctrl_base;
	काष्ठा cpdma_ctlr *dma;
	काष्ठा cpdma_chan *txchan;
	काष्ठा cpdma_chan *rxchan;
	u32 link; /* 1=link on, 0=link off */
	u32 speed; /* 0=Auto Neg, 1=No PHY, 10,100, 1000 - mbps */
	u32 duplex; /* Link duplex: 0=Half, 1=Full */
	u32 rx_buf_size;
	u32 isr_count;
	u32 coal_पूर्णांकvl;
	u32 bus_freq_mhz;
	u8 rmii_en;
	u8 version;
	u32 mac_hash1;
	u32 mac_hash2;
	u32 multicast_hash_cnt[EMAC_NUM_MULTICAST_BITS];
	u32 rx_addr_type;
	स्थिर अक्षर *phy_id;
	काष्ठा device_node *phy_node;
	spinlock_t lock;
	/*platक्रमm specअगरic members*/
	व्योम (*पूर्णांक_enable) (व्योम);
	व्योम (*पूर्णांक_disable) (व्योम);
पूर्ण;

/* EMAC TX Host Error description strings */
अटल अक्षर *emac_txhost_errcodes[16] = अणु
	"No error", "SOP error", "Ownership bit not set in SOP buffer",
	"Zero Next Buffer Descriptor Pointer Without EOP",
	"Zero Buffer Pointer", "Zero Buffer Length", "Packet Length Error",
	"Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
	"Reserved", "Reserved", "Reserved", "Reserved"
पूर्ण;

/* EMAC RX Host Error description strings */
अटल अक्षर *emac_rxhost_errcodes[16] = अणु
	"No error", "Reserved", "Ownership bit not set in input buffer",
	"Reserved", "Zero Buffer Pointer", "Reserved", "Reserved",
	"Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
	"Reserved", "Reserved", "Reserved", "Reserved"
पूर्ण;

/* Helper macros */
#घोषणा emac_पढ़ो(reg)		  ioपढ़ो32(priv->emac_base + (reg))
#घोषणा emac_ग_लिखो(reg, val)      ioग_लिखो32(val, priv->emac_base + (reg))

#घोषणा emac_ctrl_पढ़ो(reg)	  ioपढ़ो32((priv->ctrl_base + (reg)))
#घोषणा emac_ctrl_ग_लिखो(reg, val) ioग_लिखो32(val, (priv->ctrl_base + (reg)))

/**
 * emac_get_drvinfo - Get EMAC driver inक्रमmation
 * @ndev: The DaVinci EMAC network adapter
 * @info: ethtool info काष्ठाure containing name and version
 *
 * Returns EMAC driver inक्रमmation (name and version)
 *
 */
अटल व्योम emac_get_drvinfo(काष्ठा net_device *ndev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, emac_version_string, माप(info->driver));
	strlcpy(info->version, EMAC_MODULE_VERSION, माप(info->version));
पूर्ण

/**
 * emac_get_coalesce - Get पूर्णांकerrupt coalesce settings क्रम this device
 * @ndev : The DaVinci EMAC network adapter
 * @coal : ethtool coalesce settings काष्ठाure
 *
 * Fetch the current पूर्णांकerrupt coalesce settings
 *
 */
अटल पूर्णांक emac_get_coalesce(काष्ठा net_device *ndev,
				काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा emac_priv *priv = netdev_priv(ndev);

	coal->rx_coalesce_usecs = priv->coal_पूर्णांकvl;
	वापस 0;

पूर्ण

/**
 * emac_set_coalesce - Set पूर्णांकerrupt coalesce settings क्रम this device
 * @ndev : The DaVinci EMAC network adapter
 * @coal : ethtool coalesce settings काष्ठाure
 *
 * Set पूर्णांकerrupt coalesce parameters
 *
 */
अटल पूर्णांक emac_set_coalesce(काष्ठा net_device *ndev,
				काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा emac_priv *priv = netdev_priv(ndev);
	u32 पूर्णांक_ctrl, num_पूर्णांकerrupts = 0;
	u32 prescale = 0, addnl_dvdr = 1, coal_पूर्णांकvl = 0;

	अगर (!coal->rx_coalesce_usecs)
		वापस -EINVAL;

	coal_पूर्णांकvl = coal->rx_coalesce_usecs;

	चयन (priv->version) अणु
	हाल EMAC_VERSION_2:
		पूर्णांक_ctrl =  emac_ctrl_पढ़ो(EMAC_DM646X_CMINTCTRL);
		prescale = priv->bus_freq_mhz * 4;

		अगर (coal_पूर्णांकvl < EMAC_DM646X_CMINTMIN_INTVL)
			coal_पूर्णांकvl = EMAC_DM646X_CMINTMIN_INTVL;

		अगर (coal_पूर्णांकvl > EMAC_DM646X_CMINTMAX_INTVL) अणु
			/*
			 * Interrupt pacer works with 4us Pulse, we can
			 * throttle further by dilating the 4us pulse.
			 */
			addnl_dvdr = EMAC_DM646X_INTPRESCALE_MASK / prescale;

			अगर (addnl_dvdr > 1) अणु
				prescale *= addnl_dvdr;
				अगर (coal_पूर्णांकvl > (EMAC_DM646X_CMINTMAX_INTVL
							* addnl_dvdr))
					coal_पूर्णांकvl = (EMAC_DM646X_CMINTMAX_INTVL
							* addnl_dvdr);
			पूर्ण अन्यथा अणु
				addnl_dvdr = 1;
				coal_पूर्णांकvl = EMAC_DM646X_CMINTMAX_INTVL;
			पूर्ण
		पूर्ण

		num_पूर्णांकerrupts = (1000 * addnl_dvdr) / coal_पूर्णांकvl;

		पूर्णांक_ctrl |= EMAC_DM646X_INTPACEEN;
		पूर्णांक_ctrl &= (~EMAC_DM646X_INTPRESCALE_MASK);
		पूर्णांक_ctrl |= (prescale & EMAC_DM646X_INTPRESCALE_MASK);
		emac_ctrl_ग_लिखो(EMAC_DM646X_CMINTCTRL, पूर्णांक_ctrl);

		emac_ctrl_ग_लिखो(EMAC_DM646X_CMRXINTMAX, num_पूर्णांकerrupts);
		emac_ctrl_ग_लिखो(EMAC_DM646X_CMTXINTMAX, num_पूर्णांकerrupts);

		अवरोध;
	शेष:
		पूर्णांक_ctrl = emac_ctrl_पढ़ो(EMAC_CTRL_EWINTTCNT);
		पूर्णांक_ctrl &= (~EMAC_DM644X_EWINTCNT_MASK);
		prescale = coal_पूर्णांकvl * priv->bus_freq_mhz;
		अगर (prescale > EMAC_DM644X_EWINTCNT_MASK) अणु
			prescale = EMAC_DM644X_EWINTCNT_MASK;
			coal_पूर्णांकvl = prescale / priv->bus_freq_mhz;
		पूर्ण
		emac_ctrl_ग_लिखो(EMAC_CTRL_EWINTTCNT, (पूर्णांक_ctrl | prescale));

		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO"Set coalesce to %d usecs.\n", coal_पूर्णांकvl);
	priv->coal_पूर्णांकvl = coal_पूर्णांकvl;

	वापस 0;

पूर्ण


/* ethtool_ops: DaVinci EMAC Ethtool काष्ठाure
 *
 * Ethtool support क्रम EMAC adapter
 */
अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS,
	.get_drvinfo = emac_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_coalesce = emac_get_coalesce,
	.set_coalesce =  emac_set_coalesce,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

/**
 * emac_update_phystatus - Update Phy status
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 *
 * Updates phy status and takes action क्रम network queue अगर required
 * based upon link status
 *
 */
अटल व्योम emac_update_phystatus(काष्ठा emac_priv *priv)
अणु
	u32 mac_control;
	u32 new_duplex;
	u32 cur_duplex;
	काष्ठा net_device *ndev = priv->ndev;

	mac_control = emac_पढ़ो(EMAC_MACCONTROL);
	cur_duplex = (mac_control & EMAC_MACCONTROL_FULLDUPLEXEN) ?
			DUPLEX_FULL : DUPLEX_HALF;
	अगर (ndev->phydev)
		new_duplex = ndev->phydev->duplex;
	अन्यथा
		new_duplex = DUPLEX_FULL;

	/* We get called only अगर link has changed (speed/duplex/status) */
	अगर ((priv->link) && (new_duplex != cur_duplex)) अणु
		priv->duplex = new_duplex;
		अगर (DUPLEX_FULL == priv->duplex)
			mac_control |= (EMAC_MACCONTROL_FULLDUPLEXEN);
		अन्यथा
			mac_control &= ~(EMAC_MACCONTROL_FULLDUPLEXEN);
	पूर्ण

	अगर (priv->speed == SPEED_1000 && (priv->version == EMAC_VERSION_2)) अणु
		mac_control = emac_पढ़ो(EMAC_MACCONTROL);
		mac_control |= (EMAC_DM646X_MACCONTORL_GIG |
				EMAC_DM646X_MACCONTORL_GIGFORCE);
	पूर्ण अन्यथा अणु
		/* Clear the GIG bit and GIGFORCE bit */
		mac_control &= ~(EMAC_DM646X_MACCONTORL_GIGFORCE |
					EMAC_DM646X_MACCONTORL_GIG);

		अगर (priv->rmii_en && (priv->speed == SPEED_100))
			mac_control |= EMAC_MACCONTROL_RMIISPEED_MASK;
		अन्यथा
			mac_control &= ~EMAC_MACCONTROL_RMIISPEED_MASK;
	पूर्ण

	/* Update mac_control अगर changed */
	emac_ग_लिखो(EMAC_MACCONTROL, mac_control);

	अगर (priv->link) अणु
		/* link ON */
		अगर (!netअगर_carrier_ok(ndev))
			netअगर_carrier_on(ndev);
	/* reactivate the transmit queue अगर it is stopped */
		अगर (netअगर_running(ndev) && netअगर_queue_stopped(ndev))
			netअगर_wake_queue(ndev);
	पूर्ण अन्यथा अणु
		/* link OFF */
		अगर (netअगर_carrier_ok(ndev))
			netअगर_carrier_off(ndev);
		अगर (!netअगर_queue_stopped(ndev))
			netअगर_stop_queue(ndev);
	पूर्ण
पूर्ण

/**
 * hash_get - Calculate hash value from mac address
 * @addr: mac address to delete from hash table
 *
 * Calculates hash value from mac address
 *
 */
अटल u32 hash_get(u8 *addr)
अणु
	u32 hash;
	u8 पंचांगpval;
	पूर्णांक cnt;
	hash = 0;

	क्रम (cnt = 0; cnt < 2; cnt++) अणु
		पंचांगpval = *addr++;
		hash ^= (पंचांगpval >> 2) ^ (पंचांगpval << 4);
		पंचांगpval = *addr++;
		hash ^= (पंचांगpval >> 4) ^ (पंचांगpval << 2);
		पंचांगpval = *addr++;
		hash ^= (पंचांगpval >> 6) ^ (पंचांगpval);
	पूर्ण

	वापस hash & 0x3F;
पूर्ण

/**
 * emac_hash_add - Hash function to add mac addr from hash table
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 * @mac_addr: mac address to delete from hash table
 *
 * Adds mac address to the पूर्णांकernal hash table
 *
 */
अटल पूर्णांक emac_hash_add(काष्ठा emac_priv *priv, u8 *mac_addr)
अणु
	काष्ठा device *emac_dev = &priv->ndev->dev;
	u32 rc = 0;
	u32 hash_bit;
	u32 hash_value = hash_get(mac_addr);

	अगर (hash_value >= EMAC_NUM_MULTICAST_BITS) अणु
		अगर (netअगर_msg_drv(priv)) अणु
			dev_err(emac_dev, "DaVinci EMAC: emac_hash_add(): Invalid "\
				"Hash %08x, should not be greater than %08x",
				hash_value, (EMAC_NUM_MULTICAST_BITS - 1));
		पूर्ण
		वापस -1;
	पूर्ण

	/* set the hash bit only अगर not previously set */
	अगर (priv->multicast_hash_cnt[hash_value] == 0) अणु
		rc = 1; /* hash value changed */
		अगर (hash_value < 32) अणु
			hash_bit = BIT(hash_value);
			priv->mac_hash1 |= hash_bit;
		पूर्ण अन्यथा अणु
			hash_bit = BIT((hash_value - 32));
			priv->mac_hash2 |= hash_bit;
		पूर्ण
	पूर्ण

	/* incr counter क्रम num of mcast addr's mapped to "this" hash bit */
	++priv->multicast_hash_cnt[hash_value];

	वापस rc;
पूर्ण

/**
 * emac_hash_del - Hash function to delete mac addr from hash table
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 * @mac_addr: mac address to delete from hash table
 *
 * Removes mac address from the पूर्णांकernal hash table
 *
 */
अटल पूर्णांक emac_hash_del(काष्ठा emac_priv *priv, u8 *mac_addr)
अणु
	u32 hash_value;
	u32 hash_bit;

	hash_value = hash_get(mac_addr);
	अगर (priv->multicast_hash_cnt[hash_value] > 0) अणु
		/* dec cntr क्रम num of mcast addr's mapped to this hash bit */
		--priv->multicast_hash_cnt[hash_value];
	पूर्ण

	/* अगर counter still > 0, at least one multicast address refers
	 * to this hash bit. so वापस 0 */
	अगर (priv->multicast_hash_cnt[hash_value] > 0)
		वापस 0;

	अगर (hash_value < 32) अणु
		hash_bit = BIT(hash_value);
		priv->mac_hash1 &= ~hash_bit;
	पूर्ण अन्यथा अणु
		hash_bit = BIT((hash_value - 32));
		priv->mac_hash2 &= ~hash_bit;
	पूर्ण

	/* वापस 1 to indicate change in mac_hash रेजिस्टरs reqd */
	वापस 1;
पूर्ण

/* EMAC multicast operation */
#घोषणा EMAC_MULTICAST_ADD	0
#घोषणा EMAC_MULTICAST_DEL	1
#घोषणा EMAC_ALL_MULTI_SET	2
#घोषणा EMAC_ALL_MULTI_CLR	3

/**
 * emac_add_mcast - Set multicast address in the EMAC adapter (Internal)
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 * @action: multicast operation to perक्रमm
 * @mac_addr: mac address to set
 *
 * Set multicast addresses in EMAC adapter - पूर्णांकernal function
 *
 */
अटल व्योम emac_add_mcast(काष्ठा emac_priv *priv, u32 action, u8 *mac_addr)
अणु
	काष्ठा device *emac_dev = &priv->ndev->dev;
	पूर्णांक update = -1;

	चयन (action) अणु
	हाल EMAC_MULTICAST_ADD:
		update = emac_hash_add(priv, mac_addr);
		अवरोध;
	हाल EMAC_MULTICAST_DEL:
		update = emac_hash_del(priv, mac_addr);
		अवरोध;
	हाल EMAC_ALL_MULTI_SET:
		update = 1;
		priv->mac_hash1 = EMAC_ALL_MULTI_REG_VALUE;
		priv->mac_hash2 = EMAC_ALL_MULTI_REG_VALUE;
		अवरोध;
	हाल EMAC_ALL_MULTI_CLR:
		update = 1;
		priv->mac_hash1 = 0;
		priv->mac_hash2 = 0;
		स_रखो(&(priv->multicast_hash_cnt[0]), 0,
		माप(priv->multicast_hash_cnt[0]) *
		       EMAC_NUM_MULTICAST_BITS);
		अवरोध;
	शेष:
		अगर (netअगर_msg_drv(priv))
			dev_err(emac_dev, "DaVinci EMAC: add_mcast"\
				": bad operation %d", action);
		अवरोध;
	पूर्ण

	/* ग_लिखो to the hardware only अगर the रेजिस्टर status chances */
	अगर (update > 0) अणु
		emac_ग_लिखो(EMAC_MACHASH1, priv->mac_hash1);
		emac_ग_लिखो(EMAC_MACHASH2, priv->mac_hash2);
	पूर्ण
पूर्ण

/**
 * emac_dev_mcast_set - Set multicast address in the EMAC adapter
 * @ndev: The DaVinci EMAC network adapter
 *
 * Set multicast addresses in EMAC adapter
 *
 */
अटल व्योम emac_dev_mcast_set(काष्ठा net_device *ndev)
अणु
	u32 mbp_enable;
	काष्ठा emac_priv *priv = netdev_priv(ndev);

	mbp_enable = emac_पढ़ो(EMAC_RXMBPENABLE);
	अगर (ndev->flags & IFF_PROMISC) अणु
		mbp_enable &= (~EMAC_MBP_PROMISCCH(EMAC_DEF_PROM_CH));
		mbp_enable |= (EMAC_MBP_RXPROMISC);
	पूर्ण अन्यथा अणु
		mbp_enable = (mbp_enable & ~EMAC_MBP_RXPROMISC);
		अगर ((ndev->flags & IFF_ALLMULTI) ||
		    netdev_mc_count(ndev) > EMAC_DEF_MAX_MULTICAST_ADDRESSES) अणु
			mbp_enable = (mbp_enable | EMAC_MBP_RXMCAST);
			emac_add_mcast(priv, EMAC_ALL_MULTI_SET, शून्य);
		पूर्ण अन्यथा अगर (!netdev_mc_empty(ndev)) अणु
			काष्ठा netdev_hw_addr *ha;

			mbp_enable = (mbp_enable | EMAC_MBP_RXMCAST);
			emac_add_mcast(priv, EMAC_ALL_MULTI_CLR, शून्य);
			/* program multicast address list पूर्णांकo EMAC hardware */
			netdev_क्रम_each_mc_addr(ha, ndev) अणु
				emac_add_mcast(priv, EMAC_MULTICAST_ADD,
					       (u8 *) ha->addr);
			पूर्ण
		पूर्ण अन्यथा अणु
			mbp_enable = (mbp_enable & ~EMAC_MBP_RXMCAST);
			emac_add_mcast(priv, EMAC_ALL_MULTI_CLR, शून्य);
		पूर्ण
	पूर्ण
	/* Set mbp config रेजिस्टर */
	emac_ग_लिखो(EMAC_RXMBPENABLE, mbp_enable);
पूर्ण

/*************************************************************************
 *  EMAC Hardware manipulation
 *************************************************************************/

/**
 * emac_पूर्णांक_disable - Disable EMAC module पूर्णांकerrupt (from adapter)
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 *
 * Disable EMAC पूर्णांकerrupt on the adapter
 *
 */
अटल व्योम emac_पूर्णांक_disable(काष्ठा emac_priv *priv)
अणु
	अगर (priv->version == EMAC_VERSION_2) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);

		/* Program C0_Int_En to zero to turn off
		* पूर्णांकerrupts to the CPU */
		emac_ctrl_ग_लिखो(EMAC_DM646X_CMRXINTEN, 0x0);
		emac_ctrl_ग_लिखो(EMAC_DM646X_CMTXINTEN, 0x0);
		/* NOTE: Rx Threshold and Misc पूर्णांकerrupts are not disabled */
		अगर (priv->पूर्णांक_disable)
			priv->पूर्णांक_disable();

		/* NOTE: Rx Threshold and Misc पूर्णांकerrupts are not enabled */

		/* ack rxen only then a new pulse will be generated */
		emac_ग_लिखो(EMAC_DM646X_MACEOIVECTOR,
			EMAC_DM646X_MAC_EOI_C0_RXEN);

		/* ack txen- only then a new pulse will be generated */
		emac_ग_लिखो(EMAC_DM646X_MACEOIVECTOR,
			EMAC_DM646X_MAC_EOI_C0_TXEN);

		local_irq_restore(flags);

	पूर्ण अन्यथा अणु
		/* Set DM644x control रेजिस्टरs क्रम पूर्णांकerrupt control */
		emac_ctrl_ग_लिखो(EMAC_CTRL_EWCTL, 0x0);
	पूर्ण
पूर्ण

/**
 * emac_पूर्णांक_enable - Enable EMAC module पूर्णांकerrupt (from adapter)
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 *
 * Enable EMAC पूर्णांकerrupt on the adapter
 *
 */
अटल व्योम emac_पूर्णांक_enable(काष्ठा emac_priv *priv)
अणु
	अगर (priv->version == EMAC_VERSION_2) अणु
		अगर (priv->पूर्णांक_enable)
			priv->पूर्णांक_enable();

		emac_ctrl_ग_लिखो(EMAC_DM646X_CMRXINTEN, 0xff);
		emac_ctrl_ग_लिखो(EMAC_DM646X_CMTXINTEN, 0xff);

		/* In addition to turning on पूर्णांकerrupt Enable, we need
		 * ack by writing appropriate values to the EOI
		 * रेजिस्टर */

		/* NOTE: Rx Threshold and Misc पूर्णांकerrupts are not enabled */
	पूर्ण अन्यथा अणु
		/* Set DM644x control रेजिस्टरs क्रम पूर्णांकerrupt control */
		emac_ctrl_ग_लिखो(EMAC_CTRL_EWCTL, 0x1);
	पूर्ण
पूर्ण

/**
 * emac_irq - EMAC पूर्णांकerrupt handler
 * @irq: पूर्णांकerrupt number
 * @dev_id: EMAC network adapter data काष्ठाure ptr
 *
 * EMAC Interrupt handler - we only schedule NAPI and not process any packets
 * here. EVen the पूर्णांकerrupt status is checked (TX/RX/Err) in NAPI poll function
 *
 * Returns पूर्णांकerrupt handled condition
 */
अटल irqवापस_t emac_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)dev_id;
	काष्ठा emac_priv *priv = netdev_priv(ndev);

	++priv->isr_count;
	अगर (likely(netअगर_running(priv->ndev))) अणु
		emac_पूर्णांक_disable(priv);
		napi_schedule(&priv->napi);
	पूर्ण अन्यथा अणु
		/* we are closing करोwn, so करोnt process anything */
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा sk_buff *emac_rx_alloc(काष्ठा emac_priv *priv)
अणु
	काष्ठा sk_buff *skb = netdev_alloc_skb(priv->ndev, priv->rx_buf_size);
	अगर (WARN_ON(!skb))
		वापस शून्य;
	skb_reserve(skb, NET_IP_ALIGN);
	वापस skb;
पूर्ण

अटल व्योम emac_rx_handler(व्योम *token, पूर्णांक len, पूर्णांक status)
अणु
	काष्ठा sk_buff		*skb = token;
	काष्ठा net_device	*ndev = skb->dev;
	काष्ठा emac_priv	*priv = netdev_priv(ndev);
	काष्ठा device		*emac_dev = &ndev->dev;
	पूर्णांक			ret;

	/* मुक्त and bail अगर we are shutting करोwn */
	अगर (unlikely(!netअगर_running(ndev))) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	/* recycle on receive error */
	अगर (status < 0) अणु
		ndev->stats.rx_errors++;
		जाओ recycle;
	पूर्ण

	/* feed received packet up the stack */
	skb_put(skb, len);
	skb->protocol = eth_type_trans(skb, ndev);
	netअगर_receive_skb(skb);
	ndev->stats.rx_bytes += len;
	ndev->stats.rx_packets++;

	/* alloc a new packet क्रम receive */
	skb = emac_rx_alloc(priv);
	अगर (!skb) अणु
		अगर (netअगर_msg_rx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "failed rx buffer alloc\n");
		वापस;
	पूर्ण

recycle:
	ret = cpdma_chan_submit(priv->rxchan, skb, skb->data,
			skb_tailroom(skb), 0);

	WARN_ON(ret == -ENOMEM);
	अगर (unlikely(ret < 0))
		dev_kमुक्त_skb_any(skb);
पूर्ण

अटल व्योम emac_tx_handler(व्योम *token, पूर्णांक len, पूर्णांक status)
अणु
	काष्ठा sk_buff		*skb = token;
	काष्ठा net_device	*ndev = skb->dev;

	/* Check whether the queue is stopped due to stalled tx dma, अगर the
	 * queue is stopped then start the queue as we have मुक्त desc क्रम tx
	 */
	अगर (unlikely(netअगर_queue_stopped(ndev)))
		netअगर_wake_queue(ndev);
	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += len;
	dev_kमुक्त_skb_any(skb);
पूर्ण

/**
 * emac_dev_xmit - EMAC Transmit function
 * @skb: SKB poपूर्णांकer
 * @ndev: The DaVinci EMAC network adapter
 *
 * Called by the प्रणाली to transmit a packet  - we queue the packet in
 * EMAC hardware transmit queue
 *
 * Returns success(NETDEV_TX_OK) or error code (typically out of desc's)
 */
अटल पूर्णांक emac_dev_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा device *emac_dev = &ndev->dev;
	पूर्णांक ret_code;
	काष्ठा emac_priv *priv = netdev_priv(ndev);

	/* If no link, वापस */
	अगर (unlikely(!priv->link)) अणु
		अगर (netअगर_msg_tx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "DaVinci EMAC: No link to transmit");
		जाओ fail_tx;
	पूर्ण

	ret_code = skb_padto(skb, EMAC_DEF_MIN_ETHPKTSIZE);
	अगर (unlikely(ret_code < 0)) अणु
		अगर (netअगर_msg_tx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "DaVinci EMAC: packet pad failed");
		जाओ fail_tx;
	पूर्ण

	skb_tx_बारtamp(skb);

	ret_code = cpdma_chan_submit(priv->txchan, skb, skb->data, skb->len,
				     0);
	अगर (unlikely(ret_code != 0)) अणु
		अगर (netअगर_msg_tx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "DaVinci EMAC: desc submit failed");
		जाओ fail_tx;
	पूर्ण

	/* If there is no more tx desc left मुक्त then we need to
	 * tell the kernel to stop sending us tx frames.
	 */
	अगर (unlikely(!cpdma_check_मुक्त_tx_desc(priv->txchan)))
		netअगर_stop_queue(ndev);

	वापस NETDEV_TX_OK;

fail_tx:
	ndev->stats.tx_dropped++;
	netअगर_stop_queue(ndev);
	वापस NETDEV_TX_BUSY;
पूर्ण

/**
 * emac_dev_tx_समयout - EMAC Transmit समयout function
 * @ndev: The DaVinci EMAC network adapter
 * @txqueue: the index of the hung transmit queue
 *
 * Called when प्रणाली detects that a skb समयout period has expired
 * potentially due to a fault in the adapter in not being able to send
 * it out on the wire. We tearकरोwn the TX channel assuming a hardware
 * error and re-initialize the TX channel क्रम hardware operation
 *
 */
अटल व्योम emac_dev_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा emac_priv *priv = netdev_priv(ndev);
	काष्ठा device *emac_dev = &ndev->dev;

	अगर (netअगर_msg_tx_err(priv))
		dev_err(emac_dev, "DaVinci EMAC: xmit timeout, restarting TX");

	ndev->stats.tx_errors++;
	emac_पूर्णांक_disable(priv);
	cpdma_chan_stop(priv->txchan);
	cpdma_chan_start(priv->txchan);
	emac_पूर्णांक_enable(priv);
पूर्ण

/**
 * emac_set_type0addr - Set EMAC Type0 mac address
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 * @ch: RX channel number
 * @mac_addr: MAC address to set in device
 *
 * Called पूर्णांकernally to set Type0 mac address of the adapter (Device)
 *
 * Returns success (0) or appropriate error code (none as of now)
 */
अटल व्योम emac_set_type0addr(काष्ठा emac_priv *priv, u32 ch, अक्षर *mac_addr)
अणु
	u32 val;
	val = ((mac_addr[5] << 8) | (mac_addr[4]));
	emac_ग_लिखो(EMAC_MACSRCADDRLO, val);

	val = ((mac_addr[3] << 24) | (mac_addr[2] << 16) | \
	       (mac_addr[1] << 8) | (mac_addr[0]));
	emac_ग_लिखो(EMAC_MACSRCADDRHI, val);
	val = emac_पढ़ो(EMAC_RXUNICASTSET);
	val |= BIT(ch);
	emac_ग_लिखो(EMAC_RXUNICASTSET, val);
	val = emac_पढ़ो(EMAC_RXUNICASTCLEAR);
	val &= ~BIT(ch);
	emac_ग_लिखो(EMAC_RXUNICASTCLEAR, val);
पूर्ण

/**
 * emac_set_type1addr - Set EMAC Type1 mac address
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 * @ch: RX channel number
 * @mac_addr: MAC address to set in device
 *
 * Called पूर्णांकernally to set Type1 mac address of the adapter (Device)
 *
 * Returns success (0) or appropriate error code (none as of now)
 */
अटल व्योम emac_set_type1addr(काष्ठा emac_priv *priv, u32 ch, अक्षर *mac_addr)
अणु
	u32 val;
	emac_ग_लिखो(EMAC_MACINDEX, ch);
	val = ((mac_addr[5] << 8) | mac_addr[4]);
	emac_ग_लिखो(EMAC_MACADDRLO, val);
	val = ((mac_addr[3] << 24) | (mac_addr[2] << 16) | \
	       (mac_addr[1] << 8) | (mac_addr[0]));
	emac_ग_लिखो(EMAC_MACADDRHI, val);
	emac_set_type0addr(priv, ch, mac_addr);
पूर्ण

/**
 * emac_set_type2addr - Set EMAC Type2 mac address
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 * @ch: RX channel number
 * @mac_addr: MAC address to set in device
 * @index: index पूर्णांकo RX address entries
 * @match: match parameter क्रम RX address matching logic
 *
 * Called पूर्णांकernally to set Type2 mac address of the adapter (Device)
 *
 * Returns success (0) or appropriate error code (none as of now)
 */
अटल व्योम emac_set_type2addr(काष्ठा emac_priv *priv, u32 ch,
			       अक्षर *mac_addr, पूर्णांक index, पूर्णांक match)
अणु
	u32 val;
	emac_ग_लिखो(EMAC_MACINDEX, index);
	val = ((mac_addr[3] << 24) | (mac_addr[2] << 16) | \
	       (mac_addr[1] << 8) | (mac_addr[0]));
	emac_ग_लिखो(EMAC_MACADDRHI, val);
	val = ((mac_addr[5] << 8) | mac_addr[4] | ((ch & 0x7) << 16) | \
	       (match << 19) | BIT(20));
	emac_ग_लिखो(EMAC_MACADDRLO, val);
	emac_set_type0addr(priv, ch, mac_addr);
पूर्ण

/**
 * emac_seपंचांगac - Set mac address in the adapter (पूर्णांकernal function)
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 * @ch: RX channel number
 * @mac_addr: MAC address to set in device
 *
 * Called पूर्णांकernally to set the mac address of the adapter (Device)
 *
 * Returns success (0) or appropriate error code (none as of now)
 */
अटल व्योम emac_seपंचांगac(काष्ठा emac_priv *priv, u32 ch, अक्षर *mac_addr)
अणु
	काष्ठा device *emac_dev = &priv->ndev->dev;

	अगर (priv->rx_addr_type == 0) अणु
		emac_set_type0addr(priv, ch, mac_addr);
	पूर्ण अन्यथा अगर (priv->rx_addr_type == 1) अणु
		u32 cnt;
		क्रम (cnt = 0; cnt < EMAC_MAX_TXRX_CHANNELS; cnt++)
			emac_set_type1addr(priv, ch, mac_addr);
	पूर्ण अन्यथा अगर (priv->rx_addr_type == 2) अणु
		emac_set_type2addr(priv, ch, mac_addr, ch, 1);
		emac_set_type0addr(priv, ch, mac_addr);
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_drv(priv))
			dev_err(emac_dev, "DaVinci EMAC: Wrong addressing\n");
	पूर्ण
पूर्ण

/**
 * emac_dev_seपंचांगac_addr - Set mac address in the adapter
 * @ndev: The DaVinci EMAC network adapter
 * @addr: MAC address to set in device
 *
 * Called by the प्रणाली to set the mac address of the adapter (Device)
 *
 * Returns success (0) or appropriate error code (none as of now)
 */
अटल पूर्णांक emac_dev_seपंचांगac_addr(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा emac_priv *priv = netdev_priv(ndev);
	काष्ठा device *emac_dev = &priv->ndev->dev;
	काष्ठा sockaddr *sa = addr;

	अगर (!is_valid_ether_addr(sa->sa_data))
		वापस -EADDRNOTAVAIL;

	/* Store mac addr in priv and rx channel and set it in EMAC hw */
	स_नकल(priv->mac_addr, sa->sa_data, ndev->addr_len);
	स_नकल(ndev->dev_addr, sa->sa_data, ndev->addr_len);

	/* MAC address is configured only after the पूर्णांकerface is enabled. */
	अगर (netअगर_running(ndev)) अणु
		emac_seपंचांगac(priv, EMAC_DEF_RX_CH, priv->mac_addr);
	पूर्ण

	अगर (netअगर_msg_drv(priv))
		dev_notice(emac_dev, "DaVinci EMAC: emac_dev_setmac_addr %pM\n",
					priv->mac_addr);

	वापस 0;
पूर्ण

/**
 * emac_hw_enable - Enable EMAC hardware क्रम packet transmission/reception
 * @priv: The DaVinci EMAC निजी adapter काष्ठाure
 *
 * Enables EMAC hardware क्रम packet processing - enables PHY, enables RX
 * क्रम packet reception and enables device पूर्णांकerrupts and then NAPI
 *
 * Returns success (0) or appropriate error code (none right now)
 */
अटल पूर्णांक emac_hw_enable(काष्ठा emac_priv *priv)
अणु
	u32 val, mbp_enable, mac_control;

	/* Soft reset */
	emac_ग_लिखो(EMAC_SOFTRESET, 1);
	जबतक (emac_पढ़ो(EMAC_SOFTRESET))
		cpu_relax();

	/* Disable पूर्णांकerrupt & Set pacing क्रम more पूर्णांकerrupts initially */
	emac_पूर्णांक_disable(priv);

	/* Full duplex enable bit set when स्वतः negotiation happens */
	mac_control =
		(((EMAC_DEF_TXPRIO_FIXED) ? (EMAC_MACCONTROL_TXPTYPE) : 0x0) |
		((priv->speed == 1000) ? EMAC_MACCONTROL_GIGABITEN : 0x0) |
		((EMAC_DEF_TXPACING_EN) ? (EMAC_MACCONTROL_TXPACEEN) : 0x0) |
		((priv->duplex == DUPLEX_FULL) ? 0x1 : 0));
	emac_ग_लिखो(EMAC_MACCONTROL, mac_control);

	mbp_enable =
		(((EMAC_DEF_PASS_CRC) ? (EMAC_RXMBP_PASSCRC_MASK) : 0x0) |
		((EMAC_DEF_QOS_EN) ? (EMAC_RXMBP_QOSEN_MASK) : 0x0) |
		 ((EMAC_DEF_NO_BUFF_CHAIN) ? (EMAC_RXMBP_NOCHAIN_MASK) : 0x0) |
		 ((EMAC_DEF_MACCTRL_FRAME_EN) ? (EMAC_RXMBP_CMFEN_MASK) : 0x0) |
		 ((EMAC_DEF_SHORT_FRAME_EN) ? (EMAC_RXMBP_CSFEN_MASK) : 0x0) |
		 ((EMAC_DEF_ERROR_FRAME_EN) ? (EMAC_RXMBP_CEFEN_MASK) : 0x0) |
		 ((EMAC_DEF_PROM_EN) ? (EMAC_RXMBP_CAFEN_MASK) : 0x0) |
		 ((EMAC_DEF_PROM_CH & EMAC_RXMBP_CHMASK) << \
			EMAC_RXMBP_PROMCH_SHIFT) |
		 ((EMAC_DEF_BCAST_EN) ? (EMAC_RXMBP_BROADEN_MASK) : 0x0) |
		 ((EMAC_DEF_BCAST_CH & EMAC_RXMBP_CHMASK) << \
			EMAC_RXMBP_BROADCH_SHIFT) |
		 ((EMAC_DEF_MCAST_EN) ? (EMAC_RXMBP_MULTIEN_MASK) : 0x0) |
		 ((EMAC_DEF_MCAST_CH & EMAC_RXMBP_CHMASK) << \
			EMAC_RXMBP_MULTICH_SHIFT));
	emac_ग_लिखो(EMAC_RXMBPENABLE, mbp_enable);
	emac_ग_लिखो(EMAC_RXMAXLEN, (EMAC_DEF_MAX_FRAME_SIZE &
				   EMAC_RX_MAX_LEN_MASK));
	emac_ग_लिखो(EMAC_RXBUFFEROFFSET, (EMAC_DEF_BUFFER_OFFSET &
					 EMAC_RX_BUFFER_OFFSET_MASK));
	emac_ग_लिखो(EMAC_RXFILTERLOWTHRESH, 0);
	emac_ग_लिखो(EMAC_RXUNICASTCLEAR, EMAC_RX_UNICAST_CLEAR_ALL);
	priv->rx_addr_type = (emac_पढ़ो(EMAC_MACCONFIG) >> 8) & 0xFF;

	emac_ग_लिखो(EMAC_MACINTMASKSET, EMAC_MAC_HOST_ERR_INTMASK_VAL);

	emac_seपंचांगac(priv, EMAC_DEF_RX_CH, priv->mac_addr);

	/* Enable MII */
	val = emac_पढ़ो(EMAC_MACCONTROL);
	val |= (EMAC_MACCONTROL_GMIIEN);
	emac_ग_लिखो(EMAC_MACCONTROL, val);

	/* Enable NAPI and पूर्णांकerrupts */
	napi_enable(&priv->napi);
	emac_पूर्णांक_enable(priv);
	वापस 0;

पूर्ण

/**
 * emac_poll - EMAC NAPI Poll function
 * @napi: poपूर्णांकer to the napi_काष्ठा containing The DaVinci EMAC network adapter
 * @budget: Number of receive packets to process (as told by NAPI layer)
 *
 * NAPI Poll function implemented to process packets as per budget. We check
 * the type of पूर्णांकerrupt on the device and accordingly call the TX or RX
 * packet processing functions. We follow the budget क्रम RX processing and
 * also put a cap on number of TX pkts processed through config param. The
 * NAPI schedule function is called अगर more packets pending.
 *
 * Returns number of packets received (in most हालs; अन्यथा TX pkts - rarely)
 */
अटल पूर्णांक emac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक mask;
	काष्ठा emac_priv *priv = container_of(napi, काष्ठा emac_priv, napi);
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा device *emac_dev = &ndev->dev;
	u32 status = 0;
	u32 num_rx_pkts = 0;

	/* Check पूर्णांकerrupt vectors and call packet processing */
	status = emac_पढ़ो(EMAC_MACINVECTOR);

	mask = EMAC_DM644X_MAC_IN_VECTOR_TX_INT_VEC;

	अगर (priv->version == EMAC_VERSION_2)
		mask = EMAC_DM646X_MAC_IN_VECTOR_TX_INT_VEC;

	अगर (status & mask) अणु
		cpdma_chan_process(priv->txchan, EMAC_DEF_TX_MAX_SERVICE);
	पूर्ण /* TX processing */

	mask = EMAC_DM644X_MAC_IN_VECTOR_RX_INT_VEC;

	अगर (priv->version == EMAC_VERSION_2)
		mask = EMAC_DM646X_MAC_IN_VECTOR_RX_INT_VEC;

	अगर (status & mask) अणु
		num_rx_pkts = cpdma_chan_process(priv->rxchan, budget);
	पूर्ण /* RX processing */

	mask = EMAC_DM644X_MAC_IN_VECTOR_HOST_INT;
	अगर (priv->version == EMAC_VERSION_2)
		mask = EMAC_DM646X_MAC_IN_VECTOR_HOST_INT;

	अगर (unlikely(status & mask)) अणु
		u32 ch, cause;
		dev_err(emac_dev, "DaVinci EMAC: Fatal Hardware Error\n");
		netअगर_stop_queue(ndev);
		napi_disable(&priv->napi);

		status = emac_पढ़ो(EMAC_MACSTATUS);
		cause = ((status & EMAC_MACSTATUS_TXERRCODE_MASK) >>
			 EMAC_MACSTATUS_TXERRCODE_SHIFT);
		अगर (cause) अणु
			ch = ((status & EMAC_MACSTATUS_TXERRCH_MASK) >>
			      EMAC_MACSTATUS_TXERRCH_SHIFT);
			अगर (net_ratelimit()) अणु
				dev_err(emac_dev, "TX Host error %s on ch=%d\n",
					&emac_txhost_errcodes[cause][0], ch);
			पूर्ण
		पूर्ण
		cause = ((status & EMAC_MACSTATUS_RXERRCODE_MASK) >>
			 EMAC_MACSTATUS_RXERRCODE_SHIFT);
		अगर (cause) अणु
			ch = ((status & EMAC_MACSTATUS_RXERRCH_MASK) >>
			      EMAC_MACSTATUS_RXERRCH_SHIFT);
			अगर (netअगर_msg_hw(priv) && net_ratelimit())
				dev_err(emac_dev, "RX Host error %s on ch=%d\n",
					&emac_rxhost_errcodes[cause][0], ch);
		पूर्ण
	पूर्ण अन्यथा अगर (num_rx_pkts < budget) अणु
		napi_complete_करोne(napi, num_rx_pkts);
		emac_पूर्णांक_enable(priv);
	पूर्ण

	वापस num_rx_pkts;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * emac_poll_controller - EMAC Poll controller function
 * @ndev: The DaVinci EMAC network adapter
 *
 * Polled functionality used by netconsole and others in non पूर्णांकerrupt mode
 *
 */
अटल व्योम emac_poll_controller(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_priv *priv = netdev_priv(ndev);

	emac_पूर्णांक_disable(priv);
	emac_irq(ndev->irq, ndev);
	emac_पूर्णांक_enable(priv);
पूर्ण
#पूर्ण_अगर

अटल व्योम emac_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;
	अचिन्हित दीर्घ flags;
	पूर्णांक new_state = 0;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (phydev->link) अणु
		/* check the mode of operation - full/half duplex */
		अगर (phydev->duplex != priv->duplex) अणु
			new_state = 1;
			priv->duplex = phydev->duplex;
		पूर्ण
		अगर (phydev->speed != priv->speed) अणु
			new_state = 1;
			priv->speed = phydev->speed;
		पूर्ण
		अगर (!priv->link) अणु
			new_state = 1;
			priv->link = 1;
		पूर्ण

	पूर्ण अन्यथा अगर (priv->link) अणु
		new_state = 1;
		priv->link = 0;
		priv->speed = 0;
		priv->duplex = ~0;
	पूर्ण
	अगर (new_state) अणु
		emac_update_phystatus(priv);
		phy_prपूर्णांक_status(ndev->phydev);
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

/*************************************************************************
 *  Linux Driver Model
 *************************************************************************/

/**
 * emac_devioctl - EMAC adapter ioctl
 * @ndev: The DaVinci EMAC network adapter
 * @अगरrq: request parameter
 * @cmd: command parameter
 *
 * EMAC driver ioctl function
 *
 * Returns success(0) or appropriate error code
 */
अटल पूर्णांक emac_devioctl(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरrq, पूर्णांक cmd)
अणु
	अगर (!(netअगर_running(ndev)))
		वापस -EINVAL;

	/* TODO: Add phy पढ़ो and ग_लिखो and निजी statistics get feature */

	अगर (ndev->phydev)
		वापस phy_mii_ioctl(ndev->phydev, अगरrq, cmd);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक match_first_device(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	अगर (dev->parent && dev->parent->of_node)
		वापस of_device_is_compatible(dev->parent->of_node,
					       "ti,davinci_mdio");

	वापस !म_भेदन(dev_name(dev), "davinci_mdio", 12);
पूर्ण

/**
 * emac_dev_खोलो - EMAC device खोलो
 * @ndev: The DaVinci EMAC network adapter
 *
 * Called when प्रणाली wants to start the पूर्णांकerface. We init TX/RX channels
 * and enable the hardware क्रम packet reception/transmission and start the
 * network queue.
 *
 * Returns 0 क्रम a successful खोलो, or appropriate error code
 */
अटल पूर्णांक emac_dev_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा device *emac_dev = &ndev->dev;
	u32 cnt;
	काष्ठा resource *res;
	पूर्णांक q, m, ret;
	पूर्णांक res_num = 0, irq_num = 0;
	पूर्णांक i = 0;
	काष्ठा emac_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = शून्य;
	काष्ठा device *phy = शून्य;

	ret = pm_runसमय_get_sync(&priv->pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&priv->pdev->dev);
		dev_err(&priv->pdev->dev, "%s: failed to get_sync(%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	netअगर_carrier_off(ndev);
	क्रम (cnt = 0; cnt < ETH_ALEN; cnt++)
		ndev->dev_addr[cnt] = priv->mac_addr[cnt];

	/* Configuration items */
	priv->rx_buf_size = EMAC_DEF_MAX_FRAME_SIZE + NET_IP_ALIGN;

	priv->mac_hash1 = 0;
	priv->mac_hash2 = 0;
	emac_ग_लिखो(EMAC_MACHASH1, 0);
	emac_ग_लिखो(EMAC_MACHASH2, 0);

	क्रम (i = 0; i < EMAC_DEF_RX_NUM_DESC; i++) अणु
		काष्ठा sk_buff *skb = emac_rx_alloc(priv);

		अगर (!skb)
			अवरोध;

		ret = cpdma_chan_idle_submit(priv->rxchan, skb, skb->data,
					     skb_tailroom(skb), 0);
		अगर (WARN_ON(ret < 0))
			अवरोध;
	पूर्ण

	/* Request IRQ */
	जबतक ((res = platक्रमm_get_resource(priv->pdev, IORESOURCE_IRQ,
					    res_num))) अणु
		क्रम (irq_num = res->start; irq_num <= res->end; irq_num++) अणु
			अगर (request_irq(irq_num, emac_irq, 0, ndev->name,
					ndev)) अणु
				dev_err(emac_dev,
					"DaVinci EMAC: request_irq() failed\n");
				ret = -EBUSY;

				जाओ rollback;
			पूर्ण
		पूर्ण
		res_num++;
	पूर्ण
	/* prepare counters क्रम rollback in हाल of an error */
	res_num--;
	irq_num--;

	/* Start/Enable EMAC hardware */
	emac_hw_enable(priv);

	/* Enable Interrupt pacing अगर configured */
	अगर (priv->coal_पूर्णांकvl != 0) अणु
		काष्ठा ethtool_coalesce coal;

		coal.rx_coalesce_usecs = (priv->coal_पूर्णांकvl << 4);
		emac_set_coalesce(ndev, &coal);
	पूर्ण

	cpdma_ctlr_start(priv->dma);

	अगर (priv->phy_node) अणु
		phydev = of_phy_connect(ndev, priv->phy_node,
					&emac_adjust_link, 0, 0);
		अगर (!phydev) अणु
			dev_err(emac_dev, "could not connect to phy %pOF\n",
				priv->phy_node);
			ret = -ENODEV;
			जाओ err;
		पूर्ण
	पूर्ण

	/* use the first phy on the bus अगर pdata did not give us a phy id */
	अगर (!phydev && !priv->phy_id) अणु
		/* NOTE: we can't use bus_find_device_by_name() here because
		 * the device name is not guaranteed to be 'davinci_mdio'. On
		 * some प्रणालीs it can be 'davinci_mdio.0' so we need to use
		 * म_भेदन() against the first part of the string to correctly
		 * match it.
		 */
		phy = bus_find_device(&mdio_bus_type, शून्य, शून्य,
				      match_first_device);
		अगर (phy) अणु
			priv->phy_id = dev_name(phy);
			अगर (!priv->phy_id || !*priv->phy_id)
				put_device(phy);
		पूर्ण
	पूर्ण

	अगर (!phydev && priv->phy_id && *priv->phy_id) अणु
		phydev = phy_connect(ndev, priv->phy_id,
				     &emac_adjust_link,
				     PHY_INTERFACE_MODE_MII);
		put_device(phy);	/* reference taken by bus_find_device */
		अगर (IS_ERR(phydev)) अणु
			dev_err(emac_dev, "could not connect to phy %s\n",
				priv->phy_id);
			ret = PTR_ERR(phydev);
			जाओ err;
		पूर्ण

		priv->link = 0;
		priv->speed = 0;
		priv->duplex = ~0;

		phy_attached_info(phydev);
	पूर्ण

	अगर (!phydev) अणु
		/* No PHY , fix the link, speed and duplex settings */
		dev_notice(emac_dev, "no phy, defaulting to 100/full\n");
		priv->link = 1;
		priv->speed = SPEED_100;
		priv->duplex = DUPLEX_FULL;
		emac_update_phystatus(priv);
	पूर्ण

	अगर (netअगर_msg_drv(priv))
		dev_notice(emac_dev, "DaVinci EMAC: Opened %s\n", ndev->name);

	अगर (phydev)
		phy_start(phydev);

	वापस 0;

err:
	emac_पूर्णांक_disable(priv);
	napi_disable(&priv->napi);

rollback:
	क्रम (q = res_num; q >= 0; q--) अणु
		res = platक्रमm_get_resource(priv->pdev, IORESOURCE_IRQ, q);
		/* at the first iteration, irq_num is alपढ़ोy set to the
		 * right value
		 */
		अगर (q != res_num)
			irq_num = res->end;

		क्रम (m = irq_num; m >= res->start; m--)
			मुक्त_irq(m, ndev);
	पूर्ण
	cpdma_ctlr_stop(priv->dma);
	pm_runसमय_put(&priv->pdev->dev);
	वापस ret;
पूर्ण

/**
 * emac_dev_stop - EMAC device stop
 * @ndev: The DaVinci EMAC network adapter
 *
 * Called when प्रणाली wants to stop or करोwn the पूर्णांकerface. We stop the network
 * queue, disable पूर्णांकerrupts and cleanup TX/RX channels.
 *
 * We वापस the statistics in net_device_stats काष्ठाure pulled from emac
 */
अटल पूर्णांक emac_dev_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा resource *res;
	पूर्णांक i = 0;
	पूर्णांक irq_num;
	काष्ठा emac_priv *priv = netdev_priv(ndev);
	काष्ठा device *emac_dev = &ndev->dev;

	/* inक्रमm the upper layers. */
	netअगर_stop_queue(ndev);
	napi_disable(&priv->napi);

	netअगर_carrier_off(ndev);
	emac_पूर्णांक_disable(priv);
	cpdma_ctlr_stop(priv->dma);
	emac_ग_लिखो(EMAC_SOFTRESET, 1);

	अगर (ndev->phydev)
		phy_disconnect(ndev->phydev);

	/* Free IRQ */
	जबतक ((res = platक्रमm_get_resource(priv->pdev, IORESOURCE_IRQ, i))) अणु
		क्रम (irq_num = res->start; irq_num <= res->end; irq_num++)
			मुक्त_irq(irq_num, priv->ndev);
		i++;
	पूर्ण

	अगर (netअगर_msg_drv(priv))
		dev_notice(emac_dev, "DaVinci EMAC: %s stopped\n", ndev->name);

	pm_runसमय_put(&priv->pdev->dev);
	वापस 0;
पूर्ण

/**
 * emac_dev_getnetstats - EMAC get statistics function
 * @ndev: The DaVinci EMAC network adapter
 *
 * Called when प्रणाली wants to get statistics from the device.
 *
 * We वापस the statistics in net_device_stats काष्ठाure pulled from emac
 */
अटल काष्ठा net_device_stats *emac_dev_getnetstats(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_priv *priv = netdev_priv(ndev);
	u32 mac_control;
	u32 stats_clear_mask;
	पूर्णांक err;

	err = pm_runसमय_get_sync(&priv->pdev->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(&priv->pdev->dev);
		dev_err(&priv->pdev->dev, "%s: failed to get_sync(%d)\n",
			__func__, err);
		वापस &ndev->stats;
	पूर्ण

	/* update emac hardware stats and reset the रेजिस्टरs*/

	mac_control = emac_पढ़ो(EMAC_MACCONTROL);

	अगर (mac_control & EMAC_MACCONTROL_GMIIEN)
		stats_clear_mask = EMAC_STATS_CLR_MASK;
	अन्यथा
		stats_clear_mask = 0;

	ndev->stats.multicast += emac_पढ़ो(EMAC_RXMCASTFRAMES);
	emac_ग_लिखो(EMAC_RXMCASTFRAMES, stats_clear_mask);

	ndev->stats.collisions += (emac_पढ़ो(EMAC_TXCOLLISION) +
					   emac_पढ़ो(EMAC_TXSINGLECOLL) +
					   emac_पढ़ो(EMAC_TXMULTICOLL));
	emac_ग_लिखो(EMAC_TXCOLLISION, stats_clear_mask);
	emac_ग_लिखो(EMAC_TXSINGLECOLL, stats_clear_mask);
	emac_ग_लिखो(EMAC_TXMULTICOLL, stats_clear_mask);

	ndev->stats.rx_length_errors += (emac_पढ़ो(EMAC_RXOVERSIZED) +
						emac_पढ़ो(EMAC_RXJABBER) +
						emac_पढ़ो(EMAC_RXUNDERSIZED));
	emac_ग_लिखो(EMAC_RXOVERSIZED, stats_clear_mask);
	emac_ग_लिखो(EMAC_RXJABBER, stats_clear_mask);
	emac_ग_लिखो(EMAC_RXUNDERSIZED, stats_clear_mask);

	ndev->stats.rx_over_errors += (emac_पढ़ो(EMAC_RXSOFOVERRUNS) +
					       emac_पढ़ो(EMAC_RXMOFOVERRUNS));
	emac_ग_लिखो(EMAC_RXSOFOVERRUNS, stats_clear_mask);
	emac_ग_लिखो(EMAC_RXMOFOVERRUNS, stats_clear_mask);

	ndev->stats.rx_fअगरo_errors += emac_पढ़ो(EMAC_RXDMAOVERRUNS);
	emac_ग_लिखो(EMAC_RXDMAOVERRUNS, stats_clear_mask);

	ndev->stats.tx_carrier_errors +=
		emac_पढ़ो(EMAC_TXCARRIERSENSE);
	emac_ग_लिखो(EMAC_TXCARRIERSENSE, stats_clear_mask);

	ndev->stats.tx_fअगरo_errors += emac_पढ़ो(EMAC_TXUNDERRUN);
	emac_ग_लिखो(EMAC_TXUNDERRUN, stats_clear_mask);

	pm_runसमय_put(&priv->pdev->dev);

	वापस &ndev->stats;
पूर्ण

अटल स्थिर काष्ठा net_device_ops emac_netdev_ops = अणु
	.nकरो_खोलो		= emac_dev_खोलो,
	.nकरो_stop		= emac_dev_stop,
	.nकरो_start_xmit		= emac_dev_xmit,
	.nकरो_set_rx_mode	= emac_dev_mcast_set,
	.nकरो_set_mac_address	= emac_dev_seपंचांगac_addr,
	.nकरो_करो_ioctl		= emac_devioctl,
	.nकरो_tx_समयout		= emac_dev_tx_समयout,
	.nकरो_get_stats		= emac_dev_getnetstats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= emac_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा of_device_id davinci_emac_of_match[];

अटल काष्ठा emac_platक्रमm_data *
davinci_emac_of_get_pdata(काष्ठा platक्रमm_device *pdev, काष्ठा emac_priv *priv)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा emac_platक्रमm_data *auxdata;
	काष्ठा emac_platक्रमm_data *pdata = शून्य;

	अगर (!IS_ENABLED(CONFIG_OF) || !pdev->dev.of_node)
		वापस dev_get_platdata(&pdev->dev);

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	np = pdev->dev.of_node;
	pdata->version = EMAC_VERSION_2;

	अगर (!is_valid_ether_addr(pdata->mac_addr))
		of_get_mac_address(np, pdata->mac_addr);

	of_property_पढ़ो_u32(np, "ti,davinci-ctrl-reg-offset",
			     &pdata->ctrl_reg_offset);

	of_property_पढ़ो_u32(np, "ti,davinci-ctrl-mod-reg-offset",
			     &pdata->ctrl_mod_reg_offset);

	of_property_पढ़ो_u32(np, "ti,davinci-ctrl-ram-offset",
			     &pdata->ctrl_ram_offset);

	of_property_पढ़ो_u32(np, "ti,davinci-ctrl-ram-size",
			     &pdata->ctrl_ram_size);

	of_property_पढ़ो_u8(np, "ti,davinci-rmii-en", &pdata->rmii_en);

	pdata->no_bd_ram = of_property_पढ़ो_bool(np, "ti,davinci-no-bd-ram");

	priv->phy_node = of_parse_phandle(np, "phy-handle", 0);
	अगर (!priv->phy_node) अणु
		अगर (!of_phy_is_fixed_link(np))
			pdata->phy_id = शून्य;
		अन्यथा अगर (of_phy_रेजिस्टर_fixed_link(np) >= 0)
			priv->phy_node = of_node_get(np);
	पूर्ण

	auxdata = pdev->dev.platक्रमm_data;
	अगर (auxdata) अणु
		pdata->पूर्णांकerrupt_enable = auxdata->पूर्णांकerrupt_enable;
		pdata->पूर्णांकerrupt_disable = auxdata->पूर्णांकerrupt_disable;
	पूर्ण

	match = of_match_device(davinci_emac_of_match, &pdev->dev);
	अगर (match && match->data) अणु
		auxdata = match->data;
		pdata->version = auxdata->version;
		pdata->hw_ram_addr = auxdata->hw_ram_addr;
	पूर्ण

	वापस  pdata;
पूर्ण

अटल पूर्णांक davinci_emac_try_get_mac(काष्ठा platक्रमm_device *pdev,
				    पूर्णांक instance, u8 *mac_addr)
अणु
	अगर (!pdev->dev.of_node)
		वापस -EINVAL;

	वापस ti_cm_get_macid(&pdev->dev, instance, mac_addr);
पूर्ण

/**
 * davinci_emac_probe - EMAC device probe
 * @pdev: The DaVinci EMAC device that we are removing
 *
 * Called when probing क्रम emac devicesr. We get details of instances and
 * resource inक्रमmation from platक्रमm init and रेजिस्टर a network device
 * and allocate resources necessary क्रम driver to perक्रमm
 */
अटल पूर्णांक davinci_emac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक rc = 0;
	काष्ठा resource *res, *res_ctrl;
	काष्ठा net_device *ndev;
	काष्ठा emac_priv *priv;
	अचिन्हित दीर्घ hw_ram_addr;
	काष्ठा emac_platक्रमm_data *pdata;
	काष्ठा cpdma_params dma_params;
	काष्ठा clk *emac_clk;
	अचिन्हित दीर्घ emac_bus_frequency;


	/* obtain emac घड़ी from kernel */
	emac_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(emac_clk)) अणु
		dev_err(&pdev->dev, "failed to get EMAC clock\n");
		वापस -EBUSY;
	पूर्ण
	emac_bus_frequency = clk_get_rate(emac_clk);
	devm_clk_put(&pdev->dev, emac_clk);

	/* TODO: Probe PHY here अगर possible */

	ndev = alloc_etherdev(माप(काष्ठा emac_priv));
	अगर (!ndev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ndev);
	priv = netdev_priv(ndev);
	priv->pdev = pdev;
	priv->ndev = ndev;
	priv->msg_enable = netअगर_msg_init(debug_level, DAVINCI_EMAC_DEBUG);

	spin_lock_init(&priv->lock);

	pdata = davinci_emac_of_get_pdata(pdev, priv);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data\n");
		rc = -ENODEV;
		जाओ err_मुक्त_netdev;
	पूर्ण

	/* MAC addr and PHY mask , RMII enable info from platक्रमm_data */
	स_नकल(priv->mac_addr, pdata->mac_addr, ETH_ALEN);
	priv->phy_id = pdata->phy_id;
	priv->rmii_en = pdata->rmii_en;
	priv->version = pdata->version;
	priv->पूर्णांक_enable = pdata->पूर्णांकerrupt_enable;
	priv->पूर्णांक_disable = pdata->पूर्णांकerrupt_disable;

	priv->coal_पूर्णांकvl = 0;
	priv->bus_freq_mhz = (u32)(emac_bus_frequency / 1000000);

	/* Get EMAC platक्रमm data */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->emac_base_phys = res->start + pdata->ctrl_reg_offset;
	priv->remap_addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->remap_addr)) अणु
		rc = PTR_ERR(priv->remap_addr);
		जाओ no_pdata;
	पूर्ण

	res_ctrl = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res_ctrl) अणु
		priv->ctrl_base =
			devm_ioremap_resource(&pdev->dev, res_ctrl);
		अगर (IS_ERR(priv->ctrl_base)) अणु
			rc = PTR_ERR(priv->ctrl_base);
			जाओ no_pdata;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->ctrl_base = priv->remap_addr + pdata->ctrl_mod_reg_offset;
	पूर्ण

	priv->emac_base = priv->remap_addr + pdata->ctrl_reg_offset;
	ndev->base_addr = (अचिन्हित दीर्घ)priv->remap_addr;

	hw_ram_addr = pdata->hw_ram_addr;
	अगर (!hw_ram_addr)
		hw_ram_addr = (u32 __क्रमce)res->start + pdata->ctrl_ram_offset;

	स_रखो(&dma_params, 0, माप(dma_params));
	dma_params.dev			= &pdev->dev;
	dma_params.dmaregs		= priv->emac_base;
	dma_params.rxthresh		= priv->emac_base + 0x120;
	dma_params.rxमुक्त		= priv->emac_base + 0x140;
	dma_params.txhdp		= priv->emac_base + 0x600;
	dma_params.rxhdp		= priv->emac_base + 0x620;
	dma_params.txcp			= priv->emac_base + 0x640;
	dma_params.rxcp			= priv->emac_base + 0x660;
	dma_params.num_chan		= EMAC_MAX_TXRX_CHANNELS;
	dma_params.min_packet_size	= EMAC_DEF_MIN_ETHPKTSIZE;
	dma_params.desc_hw_addr		= hw_ram_addr;
	dma_params.desc_mem_size	= pdata->ctrl_ram_size;
	dma_params.desc_align		= 16;

	dma_params.desc_mem_phys = pdata->no_bd_ram ? 0 :
			(u32 __क्रमce)res->start + pdata->ctrl_ram_offset;

	priv->dma = cpdma_ctlr_create(&dma_params);
	अगर (!priv->dma) अणु
		dev_err(&pdev->dev, "error initializing DMA\n");
		rc = -ENOMEM;
		जाओ no_pdata;
	पूर्ण

	priv->txchan = cpdma_chan_create(priv->dma, EMAC_DEF_TX_CH,
					 emac_tx_handler, 0);
	अगर (IS_ERR(priv->txchan)) अणु
		dev_err(&pdev->dev, "error initializing tx dma channel\n");
		rc = PTR_ERR(priv->txchan);
		जाओ err_मुक्त_dma;
	पूर्ण

	priv->rxchan = cpdma_chan_create(priv->dma, EMAC_DEF_RX_CH,
					 emac_rx_handler, 1);
	अगर (IS_ERR(priv->rxchan)) अणु
		dev_err(&pdev->dev, "error initializing rx dma channel\n");
		rc = PTR_ERR(priv->rxchan);
		जाओ err_मुक्त_txchan;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "error getting irq res\n");
		rc = -ENOENT;
		जाओ err_मुक्त_rxchan;
	पूर्ण
	ndev->irq = res->start;

	rc = davinci_emac_try_get_mac(pdev, res_ctrl ? 0 : 1, priv->mac_addr);
	अगर (!rc)
		ether_addr_copy(ndev->dev_addr, priv->mac_addr);

	अगर (!is_valid_ether_addr(priv->mac_addr)) अणु
		/* Use अक्रमom MAC अगर still none obtained. */
		eth_hw_addr_अक्रमom(ndev);
		स_नकल(priv->mac_addr, ndev->dev_addr, ndev->addr_len);
		dev_warn(&pdev->dev, "using random MAC addr: %pM\n",
			 priv->mac_addr);
	पूर्ण

	ndev->netdev_ops = &emac_netdev_ops;
	ndev->ethtool_ops = &ethtool_ops;
	netअगर_napi_add(ndev, &priv->napi, emac_poll, EMAC_POLL_WEIGHT);

	pm_runसमय_enable(&pdev->dev);
	rc = pm_runसमय_get_sync(&pdev->dev);
	अगर (rc < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		dev_err(&pdev->dev, "%s: failed to get_sync(%d)\n",
			__func__, rc);
		जाओ err_napi_del;
	पूर्ण

	/* रेजिस्टर the network device */
	SET_NETDEV_DEV(ndev, &pdev->dev);
	rc = रेजिस्टर_netdev(ndev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "error in register_netdev\n");
		rc = -ENODEV;
		pm_runसमय_put(&pdev->dev);
		जाओ err_napi_del;
	पूर्ण


	अगर (netअगर_msg_probe(priv)) अणु
		dev_notice(&pdev->dev, "DaVinci EMAC Probe found device "
			   "(regs: %pa, irq: %d)\n",
			   &priv->emac_base_phys, ndev->irq);
	पूर्ण
	pm_runसमय_put(&pdev->dev);

	वापस 0;

err_napi_del:
	netअगर_napi_del(&priv->napi);
err_मुक्त_rxchan:
	cpdma_chan_destroy(priv->rxchan);
err_मुक्त_txchan:
	cpdma_chan_destroy(priv->txchan);
err_मुक्त_dma:
	cpdma_ctlr_destroy(priv->dma);
no_pdata:
	अगर (of_phy_is_fixed_link(np))
		of_phy_deरेजिस्टर_fixed_link(np);
	of_node_put(priv->phy_node);
err_मुक्त_netdev:
	मुक्त_netdev(ndev);
	वापस rc;
पूर्ण

/**
 * davinci_emac_हटाओ - EMAC device हटाओ
 * @pdev: The DaVinci EMAC device that we are removing
 *
 * Called when removing the device driver. We disable घड़ी usage and release
 * the resources taken up by the driver and unरेजिस्टर network device
 */
अटल पूर्णांक davinci_emac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा emac_priv *priv = netdev_priv(ndev);
	काष्ठा device_node *np = pdev->dev.of_node;

	dev_notice(&ndev->dev, "DaVinci EMAC: davinci_emac_remove()\n");

	अगर (priv->txchan)
		cpdma_chan_destroy(priv->txchan);
	अगर (priv->rxchan)
		cpdma_chan_destroy(priv->rxchan);
	cpdma_ctlr_destroy(priv->dma);

	unरेजिस्टर_netdev(ndev);
	of_node_put(priv->phy_node);
	pm_runसमय_disable(&pdev->dev);
	अगर (of_phy_is_fixed_link(np))
		of_phy_deरेजिस्टर_fixed_link(np);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_emac_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);

	अगर (netअगर_running(ndev))
		emac_dev_stop(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_emac_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);

	अगर (netअगर_running(ndev))
		emac_dev_खोलो(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops davinci_emac_pm_ops = अणु
	.suspend	= davinci_emac_suspend,
	.resume		= davinci_emac_resume,
पूर्ण;

अटल स्थिर काष्ठा emac_platक्रमm_data am3517_emac_data = अणु
	.version		= EMAC_VERSION_2,
	.hw_ram_addr		= 0x01e20000,
पूर्ण;

अटल स्थिर काष्ठा emac_platक्रमm_data dm816_emac_data = अणु
	.version		= EMAC_VERSION_2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id davinci_emac_of_match[] = अणु
	अणु.compatible = "ti,davinci-dm6467-emac", पूर्ण,
	अणु.compatible = "ti,am3517-emac", .data = &am3517_emac_data, पूर्ण,
	अणु.compatible = "ti,dm816-emac", .data = &dm816_emac_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_emac_of_match);

/* davinci_emac_driver: EMAC platक्रमm driver काष्ठाure */
अटल काष्ठा platक्रमm_driver davinci_emac_driver = अणु
	.driver = अणु
		.name	 = "davinci_emac",
		.pm	 = &davinci_emac_pm_ops,
		.of_match_table = davinci_emac_of_match,
	पूर्ण,
	.probe = davinci_emac_probe,
	.हटाओ = davinci_emac_हटाओ,
पूर्ण;

/**
 * davinci_emac_init - EMAC driver module init
 *
 * Called when initializing the driver. We रेजिस्टर the driver with
 * the platक्रमm.
 */
अटल पूर्णांक __init davinci_emac_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&davinci_emac_driver);
पूर्ण
late_initcall(davinci_emac_init);

/**
 * davinci_emac_निकास - EMAC driver module निकास
 *
 * Called when निकासing the driver completely. We unरेजिस्टर the driver with
 * the platक्रमm and निकास
 */
अटल व्योम __निकास davinci_emac_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&davinci_emac_driver);
पूर्ण
module_निकास(davinci_emac_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DaVinci EMAC Maintainer: Anant Gole <anantgole@ti.com>");
MODULE_AUTHOR("DaVinci EMAC Maintainer: Chaithrika U S <chaithrika@ti.com>");
MODULE_DESCRIPTION("DaVinci EMAC Ethernet driver");
