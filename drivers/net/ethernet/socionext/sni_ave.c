<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * sni_ave.c - Socionext UniPhier AVE ethernet driver
 * Copyright 2014 Panasonic Corporation
 * Copyright 2015-2017 Socionext Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/types.h>
#समावेश <linux/u64_stats_sync.h>

/* General Register Group */
#घोषणा AVE_IDR			0x000	/* ID */
#घोषणा AVE_VR			0x004	/* Version */
#घोषणा AVE_GRR			0x008	/* Global Reset */
#घोषणा AVE_CFGR		0x00c	/* Configuration */

/* Interrupt Register Group */
#घोषणा AVE_GIMR		0x100	/* Global Interrupt Mask */
#घोषणा AVE_GISR		0x104	/* Global Interrupt Status */

/* MAC Register Group */
#घोषणा AVE_TXCR		0x200	/* TX Setup */
#घोषणा AVE_RXCR		0x204	/* RX Setup */
#घोषणा AVE_RXMAC1R		0x208	/* MAC address (lower) */
#घोषणा AVE_RXMAC2R		0x20c	/* MAC address (upper) */
#घोषणा AVE_MDIOCTR		0x214	/* MDIO Control */
#घोषणा AVE_MDIOAR		0x218	/* MDIO Address */
#घोषणा AVE_MDIOWDR		0x21c	/* MDIO Data */
#घोषणा AVE_MDIOSR		0x220	/* MDIO Status */
#घोषणा AVE_MDIORDR		0x224	/* MDIO Rd Data */

/* Descriptor Control Register Group */
#घोषणा AVE_DESCC		0x300	/* Descriptor Control */
#घोषणा AVE_TXDC		0x304	/* TX Descriptor Configuration */
#घोषणा AVE_RXDC0		0x308	/* RX Descriptor Ring0 Configuration */
#घोषणा AVE_IIRQC		0x34c	/* Interval IRQ Control */

/* Packet Filter Register Group */
#घोषणा AVE_PKTF_BASE		0x800	/* PF Base Address */
#घोषणा AVE_PFMBYTE_BASE	0xd00	/* PF Mask Byte Base Address */
#घोषणा AVE_PFMBIT_BASE		0xe00	/* PF Mask Bit Base Address */
#घोषणा AVE_PFSEL_BASE		0xf00	/* PF Selector Base Address */
#घोषणा AVE_PFEN		0xffc	/* Packet Filter Enable */
#घोषणा AVE_PKTF(ent)		(AVE_PKTF_BASE + (ent) * 0x40)
#घोषणा AVE_PFMBYTE(ent)	(AVE_PFMBYTE_BASE + (ent) * 8)
#घोषणा AVE_PFMBIT(ent)		(AVE_PFMBIT_BASE + (ent) * 4)
#घोषणा AVE_PFSEL(ent)		(AVE_PFSEL_BASE + (ent) * 4)

/* 64bit descriptor memory */
#घोषणा AVE_DESC_SIZE_64	12	/* Descriptor Size */

#घोषणा AVE_TXDM_64		0x1000	/* Tx Descriptor Memory */
#घोषणा AVE_RXDM_64		0x1c00	/* Rx Descriptor Memory */

#घोषणा AVE_TXDM_SIZE_64	0x0ba0	/* Tx Descriptor Memory Size 3KB */
#घोषणा AVE_RXDM_SIZE_64	0x6000	/* Rx Descriptor Memory Size 24KB */

/* 32bit descriptor memory */
#घोषणा AVE_DESC_SIZE_32	8	/* Descriptor Size */

#घोषणा AVE_TXDM_32		0x1000	/* Tx Descriptor Memory */
#घोषणा AVE_RXDM_32		0x1800	/* Rx Descriptor Memory */

#घोषणा AVE_TXDM_SIZE_32	0x07c0	/* Tx Descriptor Memory Size 2KB */
#घोषणा AVE_RXDM_SIZE_32	0x4000	/* Rx Descriptor Memory Size 16KB */

/* RMII Bridge Register Group */
#घोषणा AVE_RSTCTRL		0x8028	/* Reset control */
#घोषणा AVE_RSTCTRL_RMIIRST	BIT(16)
#घोषणा AVE_LINKSEL		0x8034	/* Link speed setting */
#घोषणा AVE_LINKSEL_100M	BIT(0)

/* AVE_GRR */
#घोषणा AVE_GRR_RXFFR		BIT(5)	/* Reset RxFIFO */
#घोषणा AVE_GRR_PHYRST		BIT(4)	/* Reset बाह्यal PHY */
#घोषणा AVE_GRR_GRST		BIT(0)	/* Reset all MAC */

/* AVE_CFGR */
#घोषणा AVE_CFGR_FLE		BIT(31)	/* Filter Function */
#घोषणा AVE_CFGR_CHE		BIT(30)	/* Checksum Function */
#घोषणा AVE_CFGR_MII		BIT(27)	/* Func mode (1:MII/RMII, 0:RGMII) */
#घोषणा AVE_CFGR_IPFCEN		BIT(24)	/* IP fragment sum Enable */

/* AVE_GISR (common with GIMR) */
#घोषणा AVE_GI_PHY		BIT(24)	/* PHY पूर्णांकerrupt */
#घोषणा AVE_GI_TX		BIT(16)	/* Tx complete */
#घोषणा AVE_GI_RXERR		BIT(8)	/* Receive frame more than max size */
#घोषणा AVE_GI_RXOVF		BIT(7)	/* Overflow at the RxFIFO */
#घोषणा AVE_GI_RXDROP		BIT(6)	/* Drop packet */
#घोषणा AVE_GI_RXIINT		BIT(5)	/* Interval पूर्णांकerrupt */

/* AVE_TXCR */
#घोषणा AVE_TXCR_FLOCTR		BIT(18)	/* Flow control */
#घोषणा AVE_TXCR_TXSPD_1G	BIT(17)
#घोषणा AVE_TXCR_TXSPD_100	BIT(16)

/* AVE_RXCR */
#घोषणा AVE_RXCR_RXEN		BIT(30)	/* Rx enable */
#घोषणा AVE_RXCR_FDUPEN		BIT(22)	/* Interface mode */
#घोषणा AVE_RXCR_FLOCTR		BIT(21)	/* Flow control */
#घोषणा AVE_RXCR_AFEN		BIT(19)	/* MAC address filter */
#घोषणा AVE_RXCR_DRPEN		BIT(18)	/* Drop छोड़ो frame */
#घोषणा AVE_RXCR_MPSIZ_MASK	GENMASK(10, 0)

/* AVE_MDIOCTR */
#घोषणा AVE_MDIOCTR_RREQ	BIT(3)	/* Read request */
#घोषणा AVE_MDIOCTR_WREQ	BIT(2)	/* Write request */

/* AVE_MDIOSR */
#घोषणा AVE_MDIOSR_STS		BIT(0)	/* access status */

/* AVE_DESCC */
#घोषणा AVE_DESCC_STATUS_MASK	GENMASK(31, 16)
#घोषणा AVE_DESCC_RD0		BIT(8)	/* Enable Rx descriptor Ring0 */
#घोषणा AVE_DESCC_RDSTP		BIT(4)	/* Pause Rx descriptor */
#घोषणा AVE_DESCC_TD		BIT(0)	/* Enable Tx descriptor */

/* AVE_TXDC */
#घोषणा AVE_TXDC_SIZE		GENMASK(27, 16)	/* Size of Tx descriptor */
#घोषणा AVE_TXDC_ADDR		GENMASK(11, 0)	/* Start address */
#घोषणा AVE_TXDC_ADDR_START	0

/* AVE_RXDC0 */
#घोषणा AVE_RXDC0_SIZE		GENMASK(30, 16)	/* Size of Rx descriptor */
#घोषणा AVE_RXDC0_ADDR		GENMASK(14, 0)	/* Start address */
#घोषणा AVE_RXDC0_ADDR_START	0

/* AVE_IIRQC */
#घोषणा AVE_IIRQC_EN0		BIT(27)	/* Enable पूर्णांकerval पूर्णांकerrupt Ring0 */
#घोषणा AVE_IIRQC_BSCK		GENMASK(15, 0)	/* Interval count unit */

/* Command status क्रम descriptor */
#घोषणा AVE_STS_OWN		BIT(31)	/* Descriptor ownership */
#घोषणा AVE_STS_INTR		BIT(29)	/* Request क्रम पूर्णांकerrupt */
#घोषणा AVE_STS_OK		BIT(27)	/* Normal transmit */
/* TX */
#घोषणा AVE_STS_NOCSUM		BIT(28)	/* No use HW checksum */
#घोषणा AVE_STS_1ST		BIT(26)	/* Head of buffer chain */
#घोषणा AVE_STS_LAST		BIT(25)	/* Tail of buffer chain */
#घोषणा AVE_STS_OWC		BIT(21)	/* Out of winकरोw,Late Collision */
#घोषणा AVE_STS_EC		BIT(20)	/* Excess collision occurred */
#घोषणा AVE_STS_PKTLEN_TX_MASK	GENMASK(15, 0)
/* RX */
#घोषणा AVE_STS_CSSV		BIT(21)	/* Checksum check perक्रमmed */
#घोषणा AVE_STS_CSER		BIT(20)	/* Checksum error detected */
#घोषणा AVE_STS_PKTLEN_RX_MASK	GENMASK(10, 0)

/* Packet filter */
#घोषणा AVE_PFMBYTE_MASK0	(GENMASK(31, 8) | GENMASK(5, 0))
#घोषणा AVE_PFMBYTE_MASK1	GENMASK(25, 0)
#घोषणा AVE_PFMBIT_MASK		GENMASK(15, 0)

#घोषणा AVE_PF_SIZE		17	/* Number of all packet filter */
#घोषणा AVE_PF_MULTICAST_SIZE	7	/* Number of multicast filter */

#घोषणा AVE_PFNUM_FILTER	0	/* No.0 */
#घोषणा AVE_PFNUM_UNICAST	1	/* No.1 */
#घोषणा AVE_PFNUM_BROADCAST	2	/* No.2 */
#घोषणा AVE_PFNUM_MULTICAST	11	/* No.11-17 */

/* NETIF Message control */
#घोषणा AVE_DEFAULT_MSG_ENABLE	(NETIF_MSG_DRV    |	\
				 NETIF_MSG_PROBE  |	\
				 NETIF_MSG_LINK   |	\
				 NETIF_MSG_TIMER  |	\
				 NETIF_MSG_IFDOWN |	\
				 NETIF_MSG_IFUP   |	\
				 NETIF_MSG_RX_ERR |	\
				 NETIF_MSG_TX_ERR)

/* Parameter क्रम descriptor */
#घोषणा AVE_NR_TXDESC		64	/* Tx descriptor */
#घोषणा AVE_NR_RXDESC		256	/* Rx descriptor */

#घोषणा AVE_DESC_OFS_CMDSTS	0
#घोषणा AVE_DESC_OFS_ADDRL	4
#घोषणा AVE_DESC_OFS_ADDRU	8

/* Parameter क्रम ethernet frame */
#घोषणा AVE_MAX_ETHFRAME	1518
#घोषणा AVE_FRAME_HEADROOM	2

/* Parameter क्रम पूर्णांकerrupt */
#घोषणा AVE_INTM_COUNT		20
#घोषणा AVE_FORCE_TXINTCNT	1

/* SG */
#घोषणा SG_ETPINMODE		0x540
#घोषणा SG_ETPINMODE_EXTPHY	BIT(1)	/* क्रम LD11 */
#घोषणा SG_ETPINMODE_RMII(ins)	BIT(ins)

#घोषणा IS_DESC_64BIT(p)	((p)->data->is_desc_64bit)

#घोषणा AVE_MAX_CLKS		4
#घोषणा AVE_MAX_RSTS		2

क्रमागत desc_id अणु
	AVE_DESCID_RX,
	AVE_DESCID_TX,
पूर्ण;

क्रमागत desc_state अणु
	AVE_DESC_RX_PERMIT,
	AVE_DESC_RX_SUSPEND,
	AVE_DESC_START,
	AVE_DESC_STOP,
पूर्ण;

काष्ठा ave_desc अणु
	काष्ठा sk_buff	*skbs;
	dma_addr_t	skbs_dma;
	माप_प्रकार		skbs_dmalen;
पूर्ण;

काष्ठा ave_desc_info अणु
	u32	ndesc;		/* number of descriptor */
	u32	daddr;		/* start address of descriptor */
	u32	proc_idx;	/* index of processing packet */
	u32	करोne_idx;	/* index of processed packet */
	काष्ठा ave_desc *desc;	/* skb info related descriptor */
पूर्ण;

काष्ठा ave_stats अणु
	काष्ठा	u64_stats_sync	syncp;
	u64	packets;
	u64	bytes;
	u64	errors;
	u64	dropped;
	u64	collisions;
	u64	fअगरo_errors;
पूर्ण;

काष्ठा ave_निजी अणु
	व्योम __iomem            *base;
	पूर्णांक                     irq;
	पूर्णांक			phy_id;
	अचिन्हित पूर्णांक		desc_size;
	u32			msg_enable;
	पूर्णांक			nclks;
	काष्ठा clk		*clk[AVE_MAX_CLKS];
	पूर्णांक			nrsts;
	काष्ठा reset_control	*rst[AVE_MAX_RSTS];
	phy_पूर्णांकerface_t		phy_mode;
	काष्ठा phy_device	*phydev;
	काष्ठा mii_bus		*mdio;
	काष्ठा regmap		*regmap;
	अचिन्हित पूर्णांक		pinmode_mask;
	अचिन्हित पूर्णांक		pinmode_val;
	u32			wolopts;

	/* stats */
	काष्ठा ave_stats	stats_rx;
	काष्ठा ave_stats	stats_tx;

	/* NAPI support */
	काष्ठा net_device	*ndev;
	काष्ठा napi_काष्ठा	napi_rx;
	काष्ठा napi_काष्ठा	napi_tx;

	/* descriptor */
	काष्ठा ave_desc_info	rx;
	काष्ठा ave_desc_info	tx;

	/* flow control */
	पूर्णांक छोड़ो_स्वतः;
	पूर्णांक छोड़ो_rx;
	पूर्णांक छोड़ो_tx;

	स्थिर काष्ठा ave_soc_data *data;
पूर्ण;

काष्ठा ave_soc_data अणु
	bool	is_desc_64bit;
	स्थिर अक्षर	*घड़ी_names[AVE_MAX_CLKS];
	स्थिर अक्षर	*reset_names[AVE_MAX_RSTS];
	पूर्णांक	(*get_pinmode)(काष्ठा ave_निजी *priv,
			       phy_पूर्णांकerface_t phy_mode, u32 arg);
पूर्ण;

अटल u32 ave_desc_पढ़ो(काष्ठा net_device *ndev, क्रमागत desc_id id, पूर्णांक entry,
			 पूर्णांक offset)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 addr;

	addr = ((id == AVE_DESCID_TX) ? priv->tx.daddr : priv->rx.daddr)
		+ entry * priv->desc_size + offset;

	वापस पढ़ोl(priv->base + addr);
पूर्ण

अटल u32 ave_desc_पढ़ो_cmdsts(काष्ठा net_device *ndev, क्रमागत desc_id id,
				पूर्णांक entry)
अणु
	वापस ave_desc_पढ़ो(ndev, id, entry, AVE_DESC_OFS_CMDSTS);
पूर्ण

अटल व्योम ave_desc_ग_लिखो(काष्ठा net_device *ndev, क्रमागत desc_id id,
			   पूर्णांक entry, पूर्णांक offset, u32 val)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 addr;

	addr = ((id == AVE_DESCID_TX) ? priv->tx.daddr : priv->rx.daddr)
		+ entry * priv->desc_size + offset;

	ग_लिखोl(val, priv->base + addr);
पूर्ण

अटल व्योम ave_desc_ग_लिखो_cmdsts(काष्ठा net_device *ndev, क्रमागत desc_id id,
				  पूर्णांक entry, u32 val)
अणु
	ave_desc_ग_लिखो(ndev, id, entry, AVE_DESC_OFS_CMDSTS, val);
पूर्ण

अटल व्योम ave_desc_ग_लिखो_addr(काष्ठा net_device *ndev, क्रमागत desc_id id,
				पूर्णांक entry, dma_addr_t paddr)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	ave_desc_ग_लिखो(ndev, id, entry, AVE_DESC_OFS_ADDRL,
		       lower_32_bits(paddr));
	अगर (IS_DESC_64BIT(priv))
		ave_desc_ग_लिखो(ndev, id,
			       entry, AVE_DESC_OFS_ADDRU,
			       upper_32_bits(paddr));
पूर्ण

अटल u32 ave_irq_disable_all(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 ret;

	ret = पढ़ोl(priv->base + AVE_GIMR);
	ग_लिखोl(0, priv->base + AVE_GIMR);

	वापस ret;
पूर्ण

अटल व्योम ave_irq_restore(काष्ठा net_device *ndev, u32 val)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	ग_लिखोl(val, priv->base + AVE_GIMR);
पूर्ण

अटल व्योम ave_irq_enable(काष्ठा net_device *ndev, u32 bitflag)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	ग_लिखोl(पढ़ोl(priv->base + AVE_GIMR) | bitflag, priv->base + AVE_GIMR);
	ग_लिखोl(bitflag, priv->base + AVE_GISR);
पूर्ण

अटल व्योम ave_hw_ग_लिखो_macaddr(काष्ठा net_device *ndev,
				 स्थिर अचिन्हित अक्षर *mac_addr,
				 पूर्णांक reg1, पूर्णांक reg2)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	ग_लिखोl(mac_addr[0] | mac_addr[1] << 8 |
	       mac_addr[2] << 16 | mac_addr[3] << 24, priv->base + reg1);
	ग_लिखोl(mac_addr[4] | mac_addr[5] << 8, priv->base + reg2);
पूर्ण

अटल व्योम ave_hw_पढ़ो_version(काष्ठा net_device *ndev, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 major, minor, vr;

	vr = पढ़ोl(priv->base + AVE_VR);
	major = (vr & GENMASK(15, 8)) >> 8;
	minor = (vr & GENMASK(7, 0));
	snम_लिखो(buf, len, "v%u.%u", major, minor);
पूर्ण

अटल व्योम ave_ethtool_get_drvinfo(काष्ठा net_device *ndev,
				    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा device *dev = ndev->dev.parent;

	strlcpy(info->driver, dev->driver->name, माप(info->driver));
	strlcpy(info->bus_info, dev_name(dev), माप(info->bus_info));
	ave_hw_पढ़ो_version(ndev, info->fw_version, माप(info->fw_version));
पूर्ण

अटल u32 ave_ethtool_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम ave_ethtool_set_msglevel(काष्ठा net_device *ndev, u32 val)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	priv->msg_enable = val;
पूर्ण

अटल व्योम ave_ethtool_get_wol(काष्ठा net_device *ndev,
				काष्ठा ethtool_wolinfo *wol)
अणु
	wol->supported = 0;
	wol->wolopts   = 0;

	अगर (ndev->phydev)
		phy_ethtool_get_wol(ndev->phydev, wol);
पूर्ण

अटल पूर्णांक __ave_ethtool_set_wol(काष्ठा net_device *ndev,
				 काष्ठा ethtool_wolinfo *wol)
अणु
	अगर (!ndev->phydev ||
	    (wol->wolopts & (WAKE_ARP | WAKE_MAGICSECURE)))
		वापस -EOPNOTSUPP;

	वापस phy_ethtool_set_wol(ndev->phydev, wol);
पूर्ण

अटल पूर्णांक ave_ethtool_set_wol(काष्ठा net_device *ndev,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक ret;

	ret = __ave_ethtool_set_wol(ndev, wol);
	अगर (!ret)
		device_set_wakeup_enable(&ndev->dev, !!wol->wolopts);

	वापस ret;
पूर्ण

अटल व्योम ave_ethtool_get_छोड़ोparam(काष्ठा net_device *ndev,
				       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	छोड़ो->स्वतःneg  = priv->छोड़ो_स्वतः;
	छोड़ो->rx_छोड़ो = priv->छोड़ो_rx;
	छोड़ो->tx_छोड़ो = priv->छोड़ो_tx;
पूर्ण

अटल पूर्णांक ave_ethtool_set_छोड़ोparam(काष्ठा net_device *ndev,
				      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (!phydev)
		वापस -EINVAL;

	priv->छोड़ो_स्वतः = छोड़ो->स्वतःneg;
	priv->छोड़ो_rx   = छोड़ो->rx_छोड़ो;
	priv->छोड़ो_tx   = छोड़ो->tx_छोड़ो;

	phy_set_asym_छोड़ो(phydev, छोड़ो->rx_छोड़ो, छोड़ो->tx_छोड़ो);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ave_ethtool_ops = अणु
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
	.get_drvinfo		= ave_ethtool_get_drvinfo,
	.nway_reset		= phy_ethtool_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_msglevel		= ave_ethtool_get_msglevel,
	.set_msglevel		= ave_ethtool_set_msglevel,
	.get_wol		= ave_ethtool_get_wol,
	.set_wol		= ave_ethtool_set_wol,
	.get_छोड़ोparam         = ave_ethtool_get_छोड़ोparam,
	.set_छोड़ोparam         = ave_ethtool_set_छोड़ोparam,
पूर्ण;

अटल पूर्णांक ave_mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyid, पूर्णांक regnum)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा ave_निजी *priv;
	u32 mdioctl, mdiosr;
	पूर्णांक ret;

	priv = netdev_priv(ndev);

	/* ग_लिखो address */
	ग_लिखोl((phyid << 8) | regnum, priv->base + AVE_MDIOAR);

	/* पढ़ो request */
	mdioctl = पढ़ोl(priv->base + AVE_MDIOCTR);
	ग_लिखोl((mdioctl | AVE_MDIOCTR_RREQ) & ~AVE_MDIOCTR_WREQ,
	       priv->base + AVE_MDIOCTR);

	ret = पढ़ोl_poll_समयout(priv->base + AVE_MDIOSR, mdiosr,
				 !(mdiosr & AVE_MDIOSR_STS), 20, 2000);
	अगर (ret) अणु
		netdev_err(ndev, "failed to read (phy:%d reg:%x)\n",
			   phyid, regnum);
		वापस ret;
	पूर्ण

	वापस पढ़ोl(priv->base + AVE_MDIORDR) & GENMASK(15, 0);
पूर्ण

अटल पूर्णांक ave_mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phyid, पूर्णांक regnum,
			     u16 val)
अणु
	काष्ठा net_device *ndev = bus->priv;
	काष्ठा ave_निजी *priv;
	u32 mdioctl, mdiosr;
	पूर्णांक ret;

	priv = netdev_priv(ndev);

	/* ग_लिखो address */
	ग_लिखोl((phyid << 8) | regnum, priv->base + AVE_MDIOAR);

	/* ग_लिखो data */
	ग_लिखोl(val, priv->base + AVE_MDIOWDR);

	/* ग_लिखो request */
	mdioctl = पढ़ोl(priv->base + AVE_MDIOCTR);
	ग_लिखोl((mdioctl | AVE_MDIOCTR_WREQ) & ~AVE_MDIOCTR_RREQ,
	       priv->base + AVE_MDIOCTR);

	ret = पढ़ोl_poll_समयout(priv->base + AVE_MDIOSR, mdiosr,
				 !(mdiosr & AVE_MDIOSR_STS), 20, 2000);
	अगर (ret)
		netdev_err(ndev, "failed to write (phy:%d reg:%x)\n",
			   phyid, regnum);

	वापस ret;
पूर्ण

अटल पूर्णांक ave_dma_map(काष्ठा net_device *ndev, काष्ठा ave_desc *desc,
		       व्योम *ptr, माप_प्रकार len, क्रमागत dma_data_direction dir,
		       dma_addr_t *paddr)
अणु
	dma_addr_t map_addr;

	map_addr = dma_map_single(ndev->dev.parent, ptr, len, dir);
	अगर (unlikely(dma_mapping_error(ndev->dev.parent, map_addr)))
		वापस -ENOMEM;

	desc->skbs_dma = map_addr;
	desc->skbs_dmalen = len;
	*paddr = map_addr;

	वापस 0;
पूर्ण

अटल व्योम ave_dma_unmap(काष्ठा net_device *ndev, काष्ठा ave_desc *desc,
			  क्रमागत dma_data_direction dir)
अणु
	अगर (!desc->skbs_dma)
		वापस;

	dma_unmap_single(ndev->dev.parent,
			 desc->skbs_dma, desc->skbs_dmalen, dir);
	desc->skbs_dma = 0;
पूर्ण

/* Prepare Rx descriptor and memory */
अटल पूर्णांक ave_rxdesc_prepare(काष्ठा net_device *ndev, पूर्णांक entry)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;
	पूर्णांक ret;

	skb = priv->rx.desc[entry].skbs;
	अगर (!skb) अणु
		skb = netdev_alloc_skb(ndev, AVE_MAX_ETHFRAME);
		अगर (!skb) अणु
			netdev_err(ndev, "can't allocate skb for Rx\n");
			वापस -ENOMEM;
		पूर्ण
		skb->data += AVE_FRAME_HEADROOM;
		skb->tail += AVE_FRAME_HEADROOM;
	पूर्ण

	/* set disable to cmdsts */
	ave_desc_ग_लिखो_cmdsts(ndev, AVE_DESCID_RX, entry,
			      AVE_STS_INTR | AVE_STS_OWN);

	/* map Rx buffer
	 * Rx buffer set to the Rx descriptor has two restrictions:
	 * - Rx buffer address is 4 byte aligned.
	 * - Rx buffer begins with 2 byte headroom, and data will be put from
	 *   (buffer + 2).
	 * To satisfy this, specअगरy the address to put back the buffer
	 * poपूर्णांकer advanced by AVE_FRAME_HEADROOM, and expand the map size
	 * by AVE_FRAME_HEADROOM.
	 */
	ret = ave_dma_map(ndev, &priv->rx.desc[entry],
			  skb->data - AVE_FRAME_HEADROOM,
			  AVE_MAX_ETHFRAME + AVE_FRAME_HEADROOM,
			  DMA_FROM_DEVICE, &paddr);
	अगर (ret) अणु
		netdev_err(ndev, "can't map skb for Rx\n");
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण
	priv->rx.desc[entry].skbs = skb;

	/* set buffer poपूर्णांकer */
	ave_desc_ग_लिखो_addr(ndev, AVE_DESCID_RX, entry, paddr);

	/* set enable to cmdsts */
	ave_desc_ग_लिखो_cmdsts(ndev, AVE_DESCID_RX, entry,
			      AVE_STS_INTR | AVE_MAX_ETHFRAME);

	वापस ret;
पूर्ण

/* Switch state of descriptor */
अटल पूर्णांक ave_desc_चयन(काष्ठा net_device *ndev, क्रमागत desc_state state)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	पूर्णांक ret = 0;
	u32 val;

	चयन (state) अणु
	हाल AVE_DESC_START:
		ग_लिखोl(AVE_DESCC_TD | AVE_DESCC_RD0, priv->base + AVE_DESCC);
		अवरोध;

	हाल AVE_DESC_STOP:
		ग_लिखोl(0, priv->base + AVE_DESCC);
		अगर (पढ़ोl_poll_समयout(priv->base + AVE_DESCC, val, !val,
				       150, 15000)) अणु
			netdev_err(ndev, "can't stop descriptor\n");
			ret = -EBUSY;
		पूर्ण
		अवरोध;

	हाल AVE_DESC_RX_SUSPEND:
		val = पढ़ोl(priv->base + AVE_DESCC);
		val |= AVE_DESCC_RDSTP;
		val &= ~AVE_DESCC_STATUS_MASK;
		ग_लिखोl(val, priv->base + AVE_DESCC);
		अगर (पढ़ोl_poll_समयout(priv->base + AVE_DESCC, val,
				       val & (AVE_DESCC_RDSTP << 16),
				       150, 150000)) अणु
			netdev_err(ndev, "can't suspend descriptor\n");
			ret = -EBUSY;
		पूर्ण
		अवरोध;

	हाल AVE_DESC_RX_PERMIT:
		val = पढ़ोl(priv->base + AVE_DESCC);
		val &= ~AVE_DESCC_RDSTP;
		val &= ~AVE_DESCC_STATUS_MASK;
		ग_लिखोl(val, priv->base + AVE_DESCC);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ave_tx_complete(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 proc_idx, करोne_idx, ndesc, cmdsts;
	अचिन्हित पूर्णांक nr_मुक्तbuf = 0;
	अचिन्हित पूर्णांक tx_packets = 0;
	अचिन्हित पूर्णांक tx_bytes = 0;

	proc_idx = priv->tx.proc_idx;
	करोne_idx = priv->tx.करोne_idx;
	ndesc    = priv->tx.ndesc;

	/* मुक्त pre-stored skb from करोne_idx to proc_idx */
	जबतक (proc_idx != करोne_idx) अणु
		cmdsts = ave_desc_पढ़ो_cmdsts(ndev, AVE_DESCID_TX, करोne_idx);

		/* करो nothing अगर owner is HW (==1 क्रम Tx) */
		अगर (cmdsts & AVE_STS_OWN)
			अवरोध;

		/* check Tx status and updates statistics */
		अगर (cmdsts & AVE_STS_OK) अणु
			tx_bytes += cmdsts & AVE_STS_PKTLEN_TX_MASK;
			/* success */
			अगर (cmdsts & AVE_STS_LAST)
				tx_packets++;
		पूर्ण अन्यथा अणु
			/* error */
			अगर (cmdsts & AVE_STS_LAST) अणु
				priv->stats_tx.errors++;
				अगर (cmdsts & (AVE_STS_OWC | AVE_STS_EC))
					priv->stats_tx.collisions++;
			पूर्ण
		पूर्ण

		/* release skb */
		अगर (priv->tx.desc[करोne_idx].skbs) अणु
			ave_dma_unmap(ndev, &priv->tx.desc[करोne_idx],
				      DMA_TO_DEVICE);
			dev_consume_skb_any(priv->tx.desc[करोne_idx].skbs);
			priv->tx.desc[करोne_idx].skbs = शून्य;
			nr_मुक्तbuf++;
		पूर्ण
		करोne_idx = (करोne_idx + 1) % ndesc;
	पूर्ण

	priv->tx.करोne_idx = करोne_idx;

	/* update stats */
	u64_stats_update_begin(&priv->stats_tx.syncp);
	priv->stats_tx.packets += tx_packets;
	priv->stats_tx.bytes   += tx_bytes;
	u64_stats_update_end(&priv->stats_tx.syncp);

	/* wake queue क्रम मुक्तing buffer */
	अगर (unlikely(netअगर_queue_stopped(ndev)) && nr_मुक्तbuf)
		netअगर_wake_queue(ndev);

	वापस nr_मुक्तbuf;
पूर्ण

अटल पूर्णांक ave_rx_receive(काष्ठा net_device *ndev, पूर्णांक num)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक rx_packets = 0;
	अचिन्हित पूर्णांक rx_bytes = 0;
	u32 proc_idx, करोne_idx;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक pktlen;
	पूर्णांक restpkt, npkts;
	u32 ndesc, cmdsts;

	proc_idx = priv->rx.proc_idx;
	करोne_idx = priv->rx.करोne_idx;
	ndesc    = priv->rx.ndesc;
	restpkt  = ((proc_idx + ndesc - 1) - करोne_idx) % ndesc;

	क्रम (npkts = 0; npkts < num; npkts++) अणु
		/* we can't receive more packet, so fill desc quickly */
		अगर (--restpkt < 0)
			अवरोध;

		cmdsts = ave_desc_पढ़ो_cmdsts(ndev, AVE_DESCID_RX, proc_idx);

		/* करो nothing अगर owner is HW (==0 क्रम Rx) */
		अगर (!(cmdsts & AVE_STS_OWN))
			अवरोध;

		अगर (!(cmdsts & AVE_STS_OK)) अणु
			priv->stats_rx.errors++;
			proc_idx = (proc_idx + 1) % ndesc;
			जारी;
		पूर्ण

		pktlen = cmdsts & AVE_STS_PKTLEN_RX_MASK;

		/* get skbuff क्रम rx */
		skb = priv->rx.desc[proc_idx].skbs;
		priv->rx.desc[proc_idx].skbs = शून्य;

		ave_dma_unmap(ndev, &priv->rx.desc[proc_idx], DMA_FROM_DEVICE);

		skb->dev = ndev;
		skb_put(skb, pktlen);
		skb->protocol = eth_type_trans(skb, ndev);

		अगर ((cmdsts & AVE_STS_CSSV) && (!(cmdsts & AVE_STS_CSER)))
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		rx_packets++;
		rx_bytes += pktlen;

		netअगर_receive_skb(skb);

		proc_idx = (proc_idx + 1) % ndesc;
	पूर्ण

	priv->rx.proc_idx = proc_idx;

	/* update stats */
	u64_stats_update_begin(&priv->stats_rx.syncp);
	priv->stats_rx.packets += rx_packets;
	priv->stats_rx.bytes   += rx_bytes;
	u64_stats_update_end(&priv->stats_rx.syncp);

	/* refill the Rx buffers */
	जबतक (proc_idx != करोne_idx) अणु
		अगर (ave_rxdesc_prepare(ndev, करोne_idx))
			अवरोध;
		करोne_idx = (करोne_idx + 1) % ndesc;
	पूर्ण

	priv->rx.करोne_idx = करोne_idx;

	वापस npkts;
पूर्ण

अटल पूर्णांक ave_napi_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ave_निजी *priv;
	काष्ठा net_device *ndev;
	पूर्णांक num;

	priv = container_of(napi, काष्ठा ave_निजी, napi_rx);
	ndev = priv->ndev;

	num = ave_rx_receive(ndev, budget);
	अगर (num < budget) अणु
		napi_complete_करोne(napi, num);

		/* enable Rx पूर्णांकerrupt when NAPI finishes */
		ave_irq_enable(ndev, AVE_GI_RXIINT);
	पूर्ण

	वापस num;
पूर्ण

अटल पूर्णांक ave_napi_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ave_निजी *priv;
	काष्ठा net_device *ndev;
	पूर्णांक num;

	priv = container_of(napi, काष्ठा ave_निजी, napi_tx);
	ndev = priv->ndev;

	num = ave_tx_complete(ndev);
	napi_complete(napi);

	/* enable Tx पूर्णांकerrupt when NAPI finishes */
	ave_irq_enable(ndev, AVE_GI_TX);

	वापस num;
पूर्ण

अटल व्योम ave_global_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 val;

	/* set config रेजिस्टर */
	val = AVE_CFGR_FLE | AVE_CFGR_IPFCEN | AVE_CFGR_CHE;
	अगर (!phy_पूर्णांकerface_mode_is_rgmii(priv->phy_mode))
		val |= AVE_CFGR_MII;
	ग_लिखोl(val, priv->base + AVE_CFGR);

	/* reset RMII रेजिस्टर */
	val = पढ़ोl(priv->base + AVE_RSTCTRL);
	val &= ~AVE_RSTCTRL_RMIIRST;
	ग_लिखोl(val, priv->base + AVE_RSTCTRL);

	/* निश्चित reset */
	ग_लिखोl(AVE_GRR_GRST | AVE_GRR_PHYRST, priv->base + AVE_GRR);
	msleep(20);

	/* 1st, negate PHY reset only */
	ग_लिखोl(AVE_GRR_GRST, priv->base + AVE_GRR);
	msleep(40);

	/* negate reset */
	ग_लिखोl(0, priv->base + AVE_GRR);
	msleep(40);

	/* negate RMII रेजिस्टर */
	val = पढ़ोl(priv->base + AVE_RSTCTRL);
	val |= AVE_RSTCTRL_RMIIRST;
	ग_लिखोl(val, priv->base + AVE_RSTCTRL);

	ave_irq_disable_all(ndev);
पूर्ण

अटल व्योम ave_rxfअगरo_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 rxcr_org;

	/* save and disable MAC receive op */
	rxcr_org = पढ़ोl(priv->base + AVE_RXCR);
	ग_लिखोl(rxcr_org & (~AVE_RXCR_RXEN), priv->base + AVE_RXCR);

	/* suspend Rx descriptor */
	ave_desc_चयन(ndev, AVE_DESC_RX_SUSPEND);

	/* receive all packets beक्रमe descriptor starts */
	ave_rx_receive(ndev, priv->rx.ndesc);

	/* निश्चित reset */
	ग_लिखोl(AVE_GRR_RXFFR, priv->base + AVE_GRR);
	udelay(50);

	/* negate reset */
	ग_लिखोl(0, priv->base + AVE_GRR);
	udelay(20);

	/* negate पूर्णांकerrupt status */
	ग_लिखोl(AVE_GI_RXOVF, priv->base + AVE_GISR);

	/* permit descriptor */
	ave_desc_चयन(ndev, AVE_DESC_RX_PERMIT);

	/* restore MAC reccieve op */
	ग_लिखोl(rxcr_org, priv->base + AVE_RXCR);
पूर्ण

अटल irqवापस_t ave_irq_handler(पूर्णांक irq, व्योम *netdev)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)netdev;
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 gimr_val, gisr_val;

	gimr_val = ave_irq_disable_all(ndev);

	/* get पूर्णांकerrupt status */
	gisr_val = पढ़ोl(priv->base + AVE_GISR);

	/* PHY */
	अगर (gisr_val & AVE_GI_PHY)
		ग_लिखोl(AVE_GI_PHY, priv->base + AVE_GISR);

	/* check exceeding packet */
	अगर (gisr_val & AVE_GI_RXERR) अणु
		ग_लिखोl(AVE_GI_RXERR, priv->base + AVE_GISR);
		netdev_err(ndev, "receive a packet exceeding frame buffer\n");
	पूर्ण

	gisr_val &= gimr_val;
	अगर (!gisr_val)
		जाओ निकास_isr;

	/* RxFIFO overflow */
	अगर (gisr_val & AVE_GI_RXOVF) अणु
		priv->stats_rx.fअगरo_errors++;
		ave_rxfअगरo_reset(ndev);
		जाओ निकास_isr;
	पूर्ण

	/* Rx drop */
	अगर (gisr_val & AVE_GI_RXDROP) अणु
		priv->stats_rx.dropped++;
		ग_लिखोl(AVE_GI_RXDROP, priv->base + AVE_GISR);
	पूर्ण

	/* Rx पूर्णांकerval */
	अगर (gisr_val & AVE_GI_RXIINT) अणु
		napi_schedule(&priv->napi_rx);
		/* still क्रमce to disable Rx पूर्णांकerrupt until NAPI finishes */
		gimr_val &= ~AVE_GI_RXIINT;
	पूर्ण

	/* Tx completed */
	अगर (gisr_val & AVE_GI_TX) अणु
		napi_schedule(&priv->napi_tx);
		/* still क्रमce to disable Tx पूर्णांकerrupt until NAPI finishes */
		gimr_val &= ~AVE_GI_TX;
	पूर्ण

निकास_isr:
	ave_irq_restore(ndev, gimr_val);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ave_pfsel_start(काष्ठा net_device *ndev, अचिन्हित पूर्णांक entry)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 val;

	अगर (WARN_ON(entry > AVE_PF_SIZE))
		वापस -EINVAL;

	val = पढ़ोl(priv->base + AVE_PFEN);
	ग_लिखोl(val | BIT(entry), priv->base + AVE_PFEN);

	वापस 0;
पूर्ण

अटल पूर्णांक ave_pfsel_stop(काष्ठा net_device *ndev, अचिन्हित पूर्णांक entry)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 val;

	अगर (WARN_ON(entry > AVE_PF_SIZE))
		वापस -EINVAL;

	val = पढ़ोl(priv->base + AVE_PFEN);
	ग_लिखोl(val & ~BIT(entry), priv->base + AVE_PFEN);

	वापस 0;
पूर्ण

अटल पूर्णांक ave_pfsel_set_macaddr(काष्ठा net_device *ndev,
				 अचिन्हित पूर्णांक entry,
				 स्थिर अचिन्हित अक्षर *mac_addr,
				 अचिन्हित पूर्णांक set_size)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	अगर (WARN_ON(entry > AVE_PF_SIZE))
		वापस -EINVAL;
	अगर (WARN_ON(set_size > 6))
		वापस -EINVAL;

	ave_pfsel_stop(ndev, entry);

	/* set MAC address क्रम the filter */
	ave_hw_ग_लिखो_macaddr(ndev, mac_addr,
			     AVE_PKTF(entry), AVE_PKTF(entry) + 4);

	/* set byte mask */
	ग_लिखोl(GENMASK(31, set_size) & AVE_PFMBYTE_MASK0,
	       priv->base + AVE_PFMBYTE(entry));
	ग_लिखोl(AVE_PFMBYTE_MASK1, priv->base + AVE_PFMBYTE(entry) + 4);

	/* set bit mask filter */
	ग_लिखोl(AVE_PFMBIT_MASK, priv->base + AVE_PFMBIT(entry));

	/* set selector to ring 0 */
	ग_लिखोl(0, priv->base + AVE_PFSEL(entry));

	/* restart filter */
	ave_pfsel_start(ndev, entry);

	वापस 0;
पूर्ण

अटल व्योम ave_pfsel_set_promisc(काष्ठा net_device *ndev,
				  अचिन्हित पूर्णांक entry, u32 rxring)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	अगर (WARN_ON(entry > AVE_PF_SIZE))
		वापस;

	ave_pfsel_stop(ndev, entry);

	/* set byte mask */
	ग_लिखोl(AVE_PFMBYTE_MASK0, priv->base + AVE_PFMBYTE(entry));
	ग_लिखोl(AVE_PFMBYTE_MASK1, priv->base + AVE_PFMBYTE(entry) + 4);

	/* set bit mask filter */
	ग_लिखोl(AVE_PFMBIT_MASK, priv->base + AVE_PFMBIT(entry));

	/* set selector to rxring */
	ग_लिखोl(rxring, priv->base + AVE_PFSEL(entry));

	ave_pfsel_start(ndev, entry);
पूर्ण

अटल व्योम ave_pfsel_init(काष्ठा net_device *ndev)
अणु
	अचिन्हित अक्षर bcast_mac[ETH_ALEN];
	पूर्णांक i;

	eth_broadcast_addr(bcast_mac);

	क्रम (i = 0; i < AVE_PF_SIZE; i++)
		ave_pfsel_stop(ndev, i);

	/* promiscious entry, select ring 0 */
	ave_pfsel_set_promisc(ndev, AVE_PFNUM_FILTER, 0);

	/* unicast entry */
	ave_pfsel_set_macaddr(ndev, AVE_PFNUM_UNICAST, ndev->dev_addr, 6);

	/* broadcast entry */
	ave_pfsel_set_macaddr(ndev, AVE_PFNUM_BROADCAST, bcast_mac, 6);
पूर्ण

अटल व्योम ave_phy_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;
	u32 val, txcr, rxcr, rxcr_org;
	u16 rmt_adv = 0, lcl_adv = 0;
	u8 cap;

	/* set RGMII speed */
	val = पढ़ोl(priv->base + AVE_TXCR);
	val &= ~(AVE_TXCR_TXSPD_100 | AVE_TXCR_TXSPD_1G);

	अगर (phy_पूर्णांकerface_is_rgmii(phydev) && phydev->speed == SPEED_1000)
		val |= AVE_TXCR_TXSPD_1G;
	अन्यथा अगर (phydev->speed == SPEED_100)
		val |= AVE_TXCR_TXSPD_100;

	ग_लिखोl(val, priv->base + AVE_TXCR);

	/* set RMII speed (100M/10M only) */
	अगर (!phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		val = पढ़ोl(priv->base + AVE_LINKSEL);
		अगर (phydev->speed == SPEED_10)
			val &= ~AVE_LINKSEL_100M;
		अन्यथा
			val |= AVE_LINKSEL_100M;
		ग_लिखोl(val, priv->base + AVE_LINKSEL);
	पूर्ण

	/* check current RXCR/TXCR */
	rxcr = पढ़ोl(priv->base + AVE_RXCR);
	txcr = पढ़ोl(priv->base + AVE_TXCR);
	rxcr_org = rxcr;

	अगर (phydev->duplex) अणु
		rxcr |= AVE_RXCR_FDUPEN;

		अगर (phydev->छोड़ो)
			rmt_adv |= LPA_PAUSE_CAP;
		अगर (phydev->asym_छोड़ो)
			rmt_adv |= LPA_PAUSE_ASYM;

		lcl_adv = linkmode_adv_to_lcl_adv_t(phydev->advertising);
		cap = mii_resolve_flowctrl_fdx(lcl_adv, rmt_adv);
		अगर (cap & FLOW_CTRL_TX)
			txcr |= AVE_TXCR_FLOCTR;
		अन्यथा
			txcr &= ~AVE_TXCR_FLOCTR;
		अगर (cap & FLOW_CTRL_RX)
			rxcr |= AVE_RXCR_FLOCTR;
		अन्यथा
			rxcr &= ~AVE_RXCR_FLOCTR;
	पूर्ण अन्यथा अणु
		rxcr &= ~AVE_RXCR_FDUPEN;
		rxcr &= ~AVE_RXCR_FLOCTR;
		txcr &= ~AVE_TXCR_FLOCTR;
	पूर्ण

	अगर (rxcr_org != rxcr) अणु
		/* disable Rx mac */
		ग_लिखोl(rxcr & ~AVE_RXCR_RXEN, priv->base + AVE_RXCR);
		/* change and enable TX/Rx mac */
		ग_लिखोl(txcr, priv->base + AVE_TXCR);
		ग_लिखोl(rxcr, priv->base + AVE_RXCR);
	पूर्ण

	phy_prपूर्णांक_status(phydev);
पूर्ण

अटल व्योम ave_macaddr_init(काष्ठा net_device *ndev)
अणु
	ave_hw_ग_लिखो_macaddr(ndev, ndev->dev_addr, AVE_RXMAC1R, AVE_RXMAC2R);

	/* pfsel unicast entry */
	ave_pfsel_set_macaddr(ndev, AVE_PFNUM_UNICAST, ndev->dev_addr, 6);
पूर्ण

अटल पूर्णांक ave_init(काष्ठा net_device *ndev)
अणु
	काष्ठा ethtool_wolinfo wol = अणु .cmd = ETHTOOL_GWOL पूर्ण;
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	काष्ठा device *dev = ndev->dev.parent;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *mdio_np;
	काष्ठा phy_device *phydev;
	पूर्णांक nc, nr, ret;

	/* enable clk because of hw access until nकरो_खोलो */
	क्रम (nc = 0; nc < priv->nclks; nc++) अणु
		ret = clk_prepare_enable(priv->clk[nc]);
		अगर (ret) अणु
			dev_err(dev, "can't enable clock\n");
			जाओ out_clk_disable;
		पूर्ण
	पूर्ण

	क्रम (nr = 0; nr < priv->nrsts; nr++) अणु
		ret = reset_control_deनिश्चित(priv->rst[nr]);
		अगर (ret) अणु
			dev_err(dev, "can't deassert reset\n");
			जाओ out_reset_निश्चित;
		पूर्ण
	पूर्ण

	ret = regmap_update_bits(priv->regmap, SG_ETPINMODE,
				 priv->pinmode_mask, priv->pinmode_val);
	अगर (ret)
		जाओ out_reset_निश्चित;

	ave_global_reset(ndev);

	mdio_np = of_get_child_by_name(np, "mdio");
	अगर (!mdio_np) अणु
		dev_err(dev, "mdio node not found\n");
		ret = -EINVAL;
		जाओ out_reset_निश्चित;
	पूर्ण
	ret = of_mdiobus_रेजिस्टर(priv->mdio, mdio_np);
	of_node_put(mdio_np);
	अगर (ret) अणु
		dev_err(dev, "failed to register mdiobus\n");
		जाओ out_reset_निश्चित;
	पूर्ण

	phydev = of_phy_get_and_connect(ndev, np, ave_phy_adjust_link);
	अगर (!phydev) अणु
		dev_err(dev, "could not attach to PHY\n");
		ret = -ENODEV;
		जाओ out_mdio_unरेजिस्टर;
	पूर्ण

	priv->phydev = phydev;

	ave_ethtool_get_wol(ndev, &wol);
	device_set_wakeup_capable(&ndev->dev, !!wol.supported);

	/* set wol initial state disabled */
	wol.wolopts = 0;
	__ave_ethtool_set_wol(ndev, &wol);

	अगर (!phy_पूर्णांकerface_is_rgmii(phydev))
		phy_set_max_speed(phydev, SPEED_100);

	phy_support_asym_छोड़ो(phydev);

	phy_attached_info(phydev);

	वापस 0;

out_mdio_unरेजिस्टर:
	mdiobus_unरेजिस्टर(priv->mdio);
out_reset_निश्चित:
	जबतक (--nr >= 0)
		reset_control_निश्चित(priv->rst[nr]);
out_clk_disable:
	जबतक (--nc >= 0)
		clk_disable_unprepare(priv->clk[nc]);

	वापस ret;
पूर्ण

अटल व्योम ave_uninit(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	पूर्णांक i;

	phy_disconnect(priv->phydev);
	mdiobus_unरेजिस्टर(priv->mdio);

	/* disable clk because of hw access after nकरो_stop */
	क्रम (i = 0; i < priv->nrsts; i++)
		reset_control_निश्चित(priv->rst[i]);
	क्रम (i = 0; i < priv->nclks; i++)
		clk_disable_unprepare(priv->clk[i]);
पूर्ण

अटल पूर्णांक ave_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	पूर्णांक entry;
	पूर्णांक ret;
	u32 val;

	ret = request_irq(priv->irq, ave_irq_handler, IRQF_SHARED, ndev->name,
			  ndev);
	अगर (ret)
		वापस ret;

	priv->tx.desc = kसुस्मृति(priv->tx.ndesc, माप(*priv->tx.desc),
				GFP_KERNEL);
	अगर (!priv->tx.desc) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_irq;
	पूर्ण

	priv->rx.desc = kसुस्मृति(priv->rx.ndesc, माप(*priv->rx.desc),
				GFP_KERNEL);
	अगर (!priv->rx.desc) अणु
		kमुक्त(priv->tx.desc);
		ret = -ENOMEM;
		जाओ out_मुक्त_irq;
	पूर्ण

	/* initialize Tx work and descriptor */
	priv->tx.proc_idx = 0;
	priv->tx.करोne_idx = 0;
	क्रम (entry = 0; entry < priv->tx.ndesc; entry++) अणु
		ave_desc_ग_लिखो_cmdsts(ndev, AVE_DESCID_TX, entry, 0);
		ave_desc_ग_लिखो_addr(ndev, AVE_DESCID_TX, entry, 0);
	पूर्ण
	ग_लिखोl(AVE_TXDC_ADDR_START |
	       (((priv->tx.ndesc * priv->desc_size) << 16) & AVE_TXDC_SIZE),
	       priv->base + AVE_TXDC);

	/* initialize Rx work and descriptor */
	priv->rx.proc_idx = 0;
	priv->rx.करोne_idx = 0;
	क्रम (entry = 0; entry < priv->rx.ndesc; entry++) अणु
		अगर (ave_rxdesc_prepare(ndev, entry))
			अवरोध;
	पूर्ण
	ग_लिखोl(AVE_RXDC0_ADDR_START |
	       (((priv->rx.ndesc * priv->desc_size) << 16) & AVE_RXDC0_SIZE),
	       priv->base + AVE_RXDC0);

	ave_desc_चयन(ndev, AVE_DESC_START);

	ave_pfsel_init(ndev);
	ave_macaddr_init(ndev);

	/* set Rx configuration */
	/* full duplex, enable छोड़ो drop, enalbe flow control */
	val = AVE_RXCR_RXEN | AVE_RXCR_FDUPEN | AVE_RXCR_DRPEN |
		AVE_RXCR_FLOCTR | (AVE_MAX_ETHFRAME & AVE_RXCR_MPSIZ_MASK);
	ग_लिखोl(val, priv->base + AVE_RXCR);

	/* set Tx configuration */
	/* enable flow control, disable loopback */
	ग_लिखोl(AVE_TXCR_FLOCTR, priv->base + AVE_TXCR);

	/* enable समयr, clear EN,INTM, and mask पूर्णांकerval unit(BSCK) */
	val = पढ़ोl(priv->base + AVE_IIRQC) & AVE_IIRQC_BSCK;
	val |= AVE_IIRQC_EN0 | (AVE_INTM_COUNT << 16);
	ग_लिखोl(val, priv->base + AVE_IIRQC);

	val = AVE_GI_RXIINT | AVE_GI_RXOVF | AVE_GI_TX | AVE_GI_RXDROP;
	ave_irq_restore(ndev, val);

	napi_enable(&priv->napi_rx);
	napi_enable(&priv->napi_tx);

	phy_start(ndev->phydev);
	phy_start_aneg(ndev->phydev);
	netअगर_start_queue(ndev);

	वापस 0;

out_मुक्त_irq:
	disable_irq(priv->irq);
	मुक्त_irq(priv->irq, ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक ave_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	पूर्णांक entry;

	ave_irq_disable_all(ndev);
	disable_irq(priv->irq);
	मुक्त_irq(priv->irq, ndev);

	netअगर_tx_disable(ndev);
	phy_stop(ndev->phydev);
	napi_disable(&priv->napi_tx);
	napi_disable(&priv->napi_rx);

	ave_desc_चयन(ndev, AVE_DESC_STOP);

	/* मुक्त Tx buffer */
	क्रम (entry = 0; entry < priv->tx.ndesc; entry++) अणु
		अगर (!priv->tx.desc[entry].skbs)
			जारी;

		ave_dma_unmap(ndev, &priv->tx.desc[entry], DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(priv->tx.desc[entry].skbs);
		priv->tx.desc[entry].skbs = शून्य;
	पूर्ण
	priv->tx.proc_idx = 0;
	priv->tx.करोne_idx = 0;

	/* मुक्त Rx buffer */
	क्रम (entry = 0; entry < priv->rx.ndesc; entry++) अणु
		अगर (!priv->rx.desc[entry].skbs)
			जारी;

		ave_dma_unmap(ndev, &priv->rx.desc[entry], DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(priv->rx.desc[entry].skbs);
		priv->rx.desc[entry].skbs = शून्य;
	पूर्ण
	priv->rx.proc_idx = 0;
	priv->rx.करोne_idx = 0;

	kमुक्त(priv->tx.desc);
	kमुक्त(priv->rx.desc);

	वापस 0;
पूर्ण

अटल netdev_tx_t ave_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	u32 proc_idx, करोne_idx, ndesc, cmdsts;
	पूर्णांक ret, मुक्तpkt;
	dma_addr_t paddr;

	proc_idx = priv->tx.proc_idx;
	करोne_idx = priv->tx.करोne_idx;
	ndesc = priv->tx.ndesc;
	मुक्तpkt = ((करोne_idx + ndesc - 1) - proc_idx) % ndesc;

	/* stop queue when not enough entry */
	अगर (unlikely(मुक्तpkt < 1)) अणु
		netअगर_stop_queue(ndev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* add padding क्रम लघु packet */
	अगर (skb_put_padto(skb, ETH_ZLEN)) अणु
		priv->stats_tx.dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	/* map Tx buffer
	 * Tx buffer set to the Tx descriptor करोesn't have any restriction.
	 */
	ret = ave_dma_map(ndev, &priv->tx.desc[proc_idx],
			  skb->data, skb->len, DMA_TO_DEVICE, &paddr);
	अगर (ret) अणु
		dev_kमुक्त_skb_any(skb);
		priv->stats_tx.dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	priv->tx.desc[proc_idx].skbs = skb;

	ave_desc_ग_लिखो_addr(ndev, AVE_DESCID_TX, proc_idx, paddr);

	cmdsts = AVE_STS_OWN | AVE_STS_1ST | AVE_STS_LAST |
		(skb->len & AVE_STS_PKTLEN_TX_MASK);

	/* set पूर्णांकerrupt per AVE_FORCE_TXINTCNT or when queue is stopped */
	अगर (!(proc_idx % AVE_FORCE_TXINTCNT) || netअगर_queue_stopped(ndev))
		cmdsts |= AVE_STS_INTR;

	/* disable checksum calculation when skb करोesn't calurate checksum */
	अगर (skb->ip_summed == CHECKSUM_NONE ||
	    skb->ip_summed == CHECKSUM_UNNECESSARY)
		cmdsts |= AVE_STS_NOCSUM;

	ave_desc_ग_लिखो_cmdsts(ndev, AVE_DESCID_TX, proc_idx, cmdsts);

	priv->tx.proc_idx = (proc_idx + 1) % ndesc;

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ave_ioctl(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	वापस phy_mii_ioctl(ndev->phydev, अगरr, cmd);
पूर्ण

अटल स्थिर u8 v4multi_macadr[] = अणु 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 v6multi_macadr[] = अणु 0x33, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;

अटल व्योम ave_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	काष्ठा netdev_hw_addr *hw_adr;
	पूर्णांक count, mc_cnt;
	u32 val;

	/* MAC addr filter enable क्रम promiscious mode */
	mc_cnt = netdev_mc_count(ndev);
	val = पढ़ोl(priv->base + AVE_RXCR);
	अगर (ndev->flags & IFF_PROMISC || !mc_cnt)
		val &= ~AVE_RXCR_AFEN;
	अन्यथा
		val |= AVE_RXCR_AFEN;
	ग_लिखोl(val, priv->base + AVE_RXCR);

	/* set all multicast address */
	अगर ((ndev->flags & IFF_ALLMULTI) || mc_cnt > AVE_PF_MULTICAST_SIZE) अणु
		ave_pfsel_set_macaddr(ndev, AVE_PFNUM_MULTICAST,
				      v4multi_macadr, 1);
		ave_pfsel_set_macaddr(ndev, AVE_PFNUM_MULTICAST + 1,
				      v6multi_macadr, 1);
	पूर्ण अन्यथा अणु
		/* stop all multicast filter */
		क्रम (count = 0; count < AVE_PF_MULTICAST_SIZE; count++)
			ave_pfsel_stop(ndev, AVE_PFNUM_MULTICAST + count);

		/* set multicast addresses */
		count = 0;
		netdev_क्रम_each_mc_addr(hw_adr, ndev) अणु
			अगर (count == mc_cnt)
				अवरोध;
			ave_pfsel_set_macaddr(ndev, AVE_PFNUM_MULTICAST + count,
					      hw_adr->addr, 6);
			count++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ave_get_stats64(काष्ठा net_device *ndev,
			    काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक start;

	करो अणु
		start = u64_stats_fetch_begin_irq(&priv->stats_rx.syncp);
		stats->rx_packets = priv->stats_rx.packets;
		stats->rx_bytes	  = priv->stats_rx.bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&priv->stats_rx.syncp, start));

	करो अणु
		start = u64_stats_fetch_begin_irq(&priv->stats_tx.syncp);
		stats->tx_packets = priv->stats_tx.packets;
		stats->tx_bytes	  = priv->stats_tx.bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&priv->stats_tx.syncp, start));

	stats->rx_errors      = priv->stats_rx.errors;
	stats->tx_errors      = priv->stats_tx.errors;
	stats->rx_dropped     = priv->stats_rx.dropped;
	stats->tx_dropped     = priv->stats_tx.dropped;
	stats->rx_fअगरo_errors = priv->stats_rx.fअगरo_errors;
	stats->collisions     = priv->stats_tx.collisions;
पूर्ण

अटल पूर्णांक ave_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	पूर्णांक ret = eth_mac_addr(ndev, p);

	अगर (ret)
		वापस ret;

	ave_macaddr_init(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ave_netdev_ops = अणु
	.nकरो_init		= ave_init,
	.nकरो_uninit		= ave_uninit,
	.nकरो_खोलो		= ave_खोलो,
	.nकरो_stop		= ave_stop,
	.nकरो_start_xmit		= ave_start_xmit,
	.nकरो_करो_ioctl		= ave_ioctl,
	.nकरो_set_rx_mode	= ave_set_rx_mode,
	.nकरो_get_stats64	= ave_get_stats64,
	.nकरो_set_mac_address	= ave_set_mac_address,
पूर्ण;

अटल पूर्णांक ave_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा ave_soc_data *data;
	काष्ठा device *dev = &pdev->dev;
	अक्षर buf[ETHTOOL_FWVERS_LEN];
	काष्ठा of_phandle_args args;
	phy_पूर्णांकerface_t phy_mode;
	काष्ठा ave_निजी *priv;
	काष्ठा net_device *ndev;
	काष्ठा device_node *np;
	व्योम __iomem *base;
	स्थिर अक्षर *name;
	पूर्णांक i, irq, ret;
	u64 dma_mask;
	u32 ave_id;

	data = of_device_get_match_data(dev);
	अगर (WARN_ON(!data))
		वापस -EINVAL;

	np = dev->of_node;
	ret = of_get_phy_mode(np, &phy_mode);
	अगर (ret) अणु
		dev_err(dev, "phy-mode not found\n");
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	ndev = devm_alloc_etherdev(dev, माप(काष्ठा ave_निजी));
	अगर (!ndev) अणु
		dev_err(dev, "can't allocate ethernet device\n");
		वापस -ENOMEM;
	पूर्ण

	ndev->netdev_ops = &ave_netdev_ops;
	ndev->ethtool_ops = &ave_ethtool_ops;
	SET_NETDEV_DEV(ndev, dev);

	ndev->features    |= (NETIF_F_IP_CSUM | NETIF_F_RXCSUM);
	ndev->hw_features |= (NETIF_F_IP_CSUM | NETIF_F_RXCSUM);

	ndev->max_mtu = AVE_MAX_ETHFRAME - (ETH_HLEN + ETH_FCS_LEN);

	ret = of_get_mac_address(np, ndev->dev_addr);
	अगर (ret) अणु
		/* अगर the mac address is invalid, use अक्रमom mac address */
		eth_hw_addr_अक्रमom(ndev);
		dev_warn(dev, "Using random MAC address: %pM\n",
			 ndev->dev_addr);
	पूर्ण

	priv = netdev_priv(ndev);
	priv->base = base;
	priv->irq = irq;
	priv->ndev = ndev;
	priv->msg_enable = netअगर_msg_init(-1, AVE_DEFAULT_MSG_ENABLE);
	priv->phy_mode = phy_mode;
	priv->data = data;

	अगर (IS_DESC_64BIT(priv)) अणु
		priv->desc_size = AVE_DESC_SIZE_64;
		priv->tx.daddr  = AVE_TXDM_64;
		priv->rx.daddr  = AVE_RXDM_64;
		dma_mask = DMA_BIT_MASK(64);
	पूर्ण अन्यथा अणु
		priv->desc_size = AVE_DESC_SIZE_32;
		priv->tx.daddr  = AVE_TXDM_32;
		priv->rx.daddr  = AVE_RXDM_32;
		dma_mask = DMA_BIT_MASK(32);
	पूर्ण
	ret = dma_set_mask(dev, dma_mask);
	अगर (ret)
		वापस ret;

	priv->tx.ndesc = AVE_NR_TXDESC;
	priv->rx.ndesc = AVE_NR_RXDESC;

	u64_stats_init(&priv->stats_tx.syncp);
	u64_stats_init(&priv->stats_rx.syncp);

	क्रम (i = 0; i < AVE_MAX_CLKS; i++) अणु
		name = priv->data->घड़ी_names[i];
		अगर (!name)
			अवरोध;
		priv->clk[i] = devm_clk_get(dev, name);
		अगर (IS_ERR(priv->clk[i]))
			वापस PTR_ERR(priv->clk[i]);
		priv->nclks++;
	पूर्ण

	क्रम (i = 0; i < AVE_MAX_RSTS; i++) अणु
		name = priv->data->reset_names[i];
		अगर (!name)
			अवरोध;
		priv->rst[i] = devm_reset_control_get_shared(dev, name);
		अगर (IS_ERR(priv->rst[i]))
			वापस PTR_ERR(priv->rst[i]);
		priv->nrsts++;
	पूर्ण

	ret = of_parse_phandle_with_fixed_args(np,
					       "socionext,syscon-phy-mode",
					       1, 0, &args);
	अगर (ret) अणु
		dev_err(dev, "can't get syscon-phy-mode property\n");
		वापस ret;
	पूर्ण
	priv->regmap = syscon_node_to_regmap(args.np);
	of_node_put(args.np);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(dev, "can't map syscon-phy-mode\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण
	ret = priv->data->get_pinmode(priv, phy_mode, args.args[0]);
	अगर (ret) अणु
		dev_err(dev, "invalid phy-mode setting\n");
		वापस ret;
	पूर्ण

	priv->mdio = devm_mdiobus_alloc(dev);
	अगर (!priv->mdio)
		वापस -ENOMEM;
	priv->mdio->priv = ndev;
	priv->mdio->parent = dev;
	priv->mdio->पढ़ो = ave_mdiobus_पढ़ो;
	priv->mdio->ग_लिखो = ave_mdiobus_ग_लिखो;
	priv->mdio->name = "uniphier-mdio";
	snम_लिखो(priv->mdio->id, MII_BUS_ID_SIZE, "%s-%x",
		 pdev->name, pdev->id);

	/* Register as a NAPI supported driver */
	netअगर_napi_add(ndev, &priv->napi_rx, ave_napi_poll_rx,
		       NAPI_POLL_WEIGHT);
	netअगर_tx_napi_add(ndev, &priv->napi_tx, ave_napi_poll_tx,
			  NAPI_POLL_WEIGHT);

	platक्रमm_set_drvdata(pdev, ndev);

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		dev_err(dev, "failed to register netdevice\n");
		जाओ out_del_napi;
	पूर्ण

	/* get ID and version */
	ave_id = पढ़ोl(priv->base + AVE_IDR);
	ave_hw_पढ़ो_version(ndev, buf, माप(buf));

	dev_info(dev, "Socionext %c%c%c%c Ethernet IP %s (irq=%d, phy=%s)\n",
		 (ave_id >> 24) & 0xff, (ave_id >> 16) & 0xff,
		 (ave_id >> 8) & 0xff, (ave_id >> 0) & 0xff,
		 buf, priv->irq, phy_modes(phy_mode));

	वापस 0;

out_del_napi:
	netअगर_napi_del(&priv->napi_rx);
	netअगर_napi_del(&priv->napi_tx);

	वापस ret;
पूर्ण

अटल पूर्णांक ave_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा ave_निजी *priv = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);
	netअगर_napi_del(&priv->napi_rx);
	netअगर_napi_del(&priv->napi_tx);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ave_suspend(काष्ठा device *dev)
अणु
	काष्ठा ethtool_wolinfo wol = अणु .cmd = ETHTOOL_GWOL पूर्ण;
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	पूर्णांक ret = 0;

	अगर (netअगर_running(ndev)) अणु
		ret = ave_stop(ndev);
		netअगर_device_detach(ndev);
	पूर्ण

	ave_ethtool_get_wol(ndev, &wol);
	priv->wolopts = wol.wolopts;

	वापस ret;
पूर्ण

अटल पूर्णांक ave_resume(काष्ठा device *dev)
अणु
	काष्ठा ethtool_wolinfo wol = अणु .cmd = ETHTOOL_GWOL पूर्ण;
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा ave_निजी *priv = netdev_priv(ndev);
	पूर्णांक ret = 0;

	ave_global_reset(ndev);

	ave_ethtool_get_wol(ndev, &wol);
	wol.wolopts = priv->wolopts;
	__ave_ethtool_set_wol(ndev, &wol);

	अगर (ndev->phydev) अणु
		ret = phy_resume(ndev->phydev);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (netअगर_running(ndev)) अणु
		ret = ave_खोलो(ndev);
		netअगर_device_attach(ndev);
	पूर्ण

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ave_pm_ops, ave_suspend, ave_resume);
#घोषणा AVE_PM_OPS	(&ave_pm_ops)
#अन्यथा
#घोषणा AVE_PM_OPS	शून्य
#पूर्ण_अगर

अटल पूर्णांक ave_pro4_get_pinmode(काष्ठा ave_निजी *priv,
				phy_पूर्णांकerface_t phy_mode, u32 arg)
अणु
	अगर (arg > 0)
		वापस -EINVAL;

	priv->pinmode_mask = SG_ETPINMODE_RMII(0);

	चयन (phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RMII:
		priv->pinmode_val = SG_ETPINMODE_RMII(0);
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		priv->pinmode_val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ave_ld11_get_pinmode(काष्ठा ave_निजी *priv,
				phy_पूर्णांकerface_t phy_mode, u32 arg)
अणु
	अगर (arg > 0)
		वापस -EINVAL;

	priv->pinmode_mask = SG_ETPINMODE_EXTPHY | SG_ETPINMODE_RMII(0);

	चयन (phy_mode) अणु
	हाल PHY_INTERFACE_MODE_INTERNAL:
		priv->pinmode_val = 0;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		priv->pinmode_val = SG_ETPINMODE_EXTPHY | SG_ETPINMODE_RMII(0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ave_ld20_get_pinmode(काष्ठा ave_निजी *priv,
				phy_पूर्णांकerface_t phy_mode, u32 arg)
अणु
	अगर (arg > 0)
		वापस -EINVAL;

	priv->pinmode_mask = SG_ETPINMODE_RMII(0);

	चयन (phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RMII:
		priv->pinmode_val = SG_ETPINMODE_RMII(0);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		priv->pinmode_val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ave_pxs3_get_pinmode(काष्ठा ave_निजी *priv,
				phy_पूर्णांकerface_t phy_mode, u32 arg)
अणु
	अगर (arg > 1)
		वापस -EINVAL;

	priv->pinmode_mask = SG_ETPINMODE_RMII(arg);

	चयन (phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RMII:
		priv->pinmode_val = SG_ETPINMODE_RMII(arg);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		priv->pinmode_val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ave_soc_data ave_pro4_data = अणु
	.is_desc_64bit = false,
	.घड़ी_names = अणु
		"gio", "ether", "ether-gb", "ether-phy",
	पूर्ण,
	.reset_names = अणु
		"gio", "ether",
	पूर्ण,
	.get_pinmode = ave_pro4_get_pinmode,
पूर्ण;

अटल स्थिर काष्ठा ave_soc_data ave_pxs2_data = अणु
	.is_desc_64bit = false,
	.घड़ी_names = अणु
		"ether",
	पूर्ण,
	.reset_names = अणु
		"ether",
	पूर्ण,
	.get_pinmode = ave_pro4_get_pinmode,
पूर्ण;

अटल स्थिर काष्ठा ave_soc_data ave_ld11_data = अणु
	.is_desc_64bit = false,
	.घड़ी_names = अणु
		"ether",
	पूर्ण,
	.reset_names = अणु
		"ether",
	पूर्ण,
	.get_pinmode = ave_ld11_get_pinmode,
पूर्ण;

अटल स्थिर काष्ठा ave_soc_data ave_ld20_data = अणु
	.is_desc_64bit = true,
	.घड़ी_names = अणु
		"ether",
	पूर्ण,
	.reset_names = अणु
		"ether",
	पूर्ण,
	.get_pinmode = ave_ld20_get_pinmode,
पूर्ण;

अटल स्थिर काष्ठा ave_soc_data ave_pxs3_data = अणु
	.is_desc_64bit = false,
	.घड़ी_names = अणु
		"ether",
	पूर्ण,
	.reset_names = अणु
		"ether",
	पूर्ण,
	.get_pinmode = ave_pxs3_get_pinmode,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_ave_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-pro4-ave4",
		.data = &ave_pro4_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-ave4",
		.data = &ave_pxs2_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld11-ave4",
		.data = &ave_ld11_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-ave4",
		.data = &ave_ld20_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-ave4",
		.data = &ave_pxs3_data,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_ave_match);

अटल काष्ठा platक्रमm_driver ave_driver = अणु
	.probe  = ave_probe,
	.हटाओ = ave_हटाओ,
	.driver	= अणु
		.name = "ave",
		.pm   = AVE_PM_OPS,
		.of_match_table	= of_ave_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ave_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("Socionext UniPhier AVE ethernet driver");
MODULE_LICENSE("GPL v2");
