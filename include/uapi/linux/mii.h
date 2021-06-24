<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * linux/mii.h: definitions क्रम MII-compatible transceivers
 * Originally drivers/net/sunhme.h.
 *
 * Copyright (C) 1996, 1999, 2001 David S. Miller (davem@redhat.com)
 */

#अगर_अघोषित _UAPI__LINUX_MII_H__
#घोषणा _UAPI__LINUX_MII_H__

#समावेश <linux/types.h>
#समावेश <linux/ethtool.h>

/* Generic MII रेजिस्टरs. */
#घोषणा MII_BMCR		0x00	/* Basic mode control रेजिस्टर */
#घोषणा MII_BMSR		0x01	/* Basic mode status रेजिस्टर  */
#घोषणा MII_PHYSID1		0x02	/* PHYS ID 1                   */
#घोषणा MII_PHYSID2		0x03	/* PHYS ID 2                   */
#घोषणा MII_ADVERTISE		0x04	/* Advertisement control reg   */
#घोषणा MII_LPA			0x05	/* Link partner ability reg    */
#घोषणा MII_EXPANSION		0x06	/* Expansion रेजिस्टर          */
#घोषणा MII_CTRL1000		0x09	/* 1000BASE-T control          */
#घोषणा MII_STAT1000		0x0a	/* 1000BASE-T status           */
#घोषणा	MII_MMD_CTRL		0x0d	/* MMD Access Control Register */
#घोषणा	MII_MMD_DATA		0x0e	/* MMD Access Data Register */
#घोषणा MII_ESTATUS		0x0f	/* Extended Status             */
#घोषणा MII_DCOUNTER		0x12	/* Disconnect counter          */
#घोषणा MII_FCSCOUNTER		0x13	/* False carrier counter       */
#घोषणा MII_NWAYTEST		0x14	/* N-way स्वतः-neg test reg     */
#घोषणा MII_RERRCOUNTER		0x15	/* Receive error counter       */
#घोषणा MII_SREVISION		0x16	/* Silicon revision            */
#घोषणा MII_RESV1		0x17	/* Reserved...                 */
#घोषणा MII_LBRERROR		0x18	/* Lpback, rx, bypass error    */
#घोषणा MII_PHYADDR		0x19	/* PHY address                 */
#घोषणा MII_RESV2		0x1a	/* Reserved...                 */
#घोषणा MII_TPISTATUS		0x1b	/* TPI status क्रम 10mbps       */
#घोषणा MII_NCONFIG		0x1c	/* Network पूर्णांकerface config    */

/* Basic mode control रेजिस्टर. */
#घोषणा BMCR_RESV		0x003f	/* Unused...                   */
#घोषणा BMCR_SPEED1000		0x0040	/* MSB of Speed (1000)         */
#घोषणा BMCR_CTST		0x0080	/* Collision test              */
#घोषणा BMCR_FULLDPLX		0x0100	/* Full duplex                 */
#घोषणा BMCR_ANRESTART		0x0200	/* Auto negotiation restart    */
#घोषणा BMCR_ISOLATE		0x0400	/* Isolate data paths from MII */
#घोषणा BMCR_PDOWN		0x0800	/* Enable low घातer state      */
#घोषणा BMCR_ANENABLE		0x1000	/* Enable स्वतः negotiation     */
#घोषणा BMCR_SPEED100		0x2000	/* Select 100Mbps              */
#घोषणा BMCR_LOOPBACK		0x4000	/* TXD loopback bits           */
#घोषणा BMCR_RESET		0x8000	/* Reset to शेष state      */
#घोषणा BMCR_SPEED10		0x0000	/* Select 10Mbps               */

/* Basic mode status रेजिस्टर. */
#घोषणा BMSR_ERCAP		0x0001	/* Ext-reg capability          */
#घोषणा BMSR_JCD		0x0002	/* Jabber detected             */
#घोषणा BMSR_LSTATUS		0x0004	/* Link status                 */
#घोषणा BMSR_ANEGCAPABLE	0x0008	/* Able to करो स्वतः-negotiation */
#घोषणा BMSR_RFAULT		0x0010	/* Remote fault detected       */
#घोषणा BMSR_ANEGCOMPLETE	0x0020	/* Auto-negotiation complete   */
#घोषणा BMSR_RESV		0x00c0	/* Unused...                   */
#घोषणा BMSR_ESTATEN		0x0100	/* Extended Status in R15      */
#घोषणा BMSR_100HALF2		0x0200	/* Can करो 100BASE-T2 HDX       */
#घोषणा BMSR_100FULL2		0x0400	/* Can करो 100BASE-T2 FDX       */
#घोषणा BMSR_10HALF		0x0800	/* Can करो 10mbps, half-duplex  */
#घोषणा BMSR_10FULL		0x1000	/* Can करो 10mbps, full-duplex  */
#घोषणा BMSR_100HALF		0x2000	/* Can करो 100mbps, half-duplex */
#घोषणा BMSR_100FULL		0x4000	/* Can करो 100mbps, full-duplex */
#घोषणा BMSR_100BASE4		0x8000	/* Can करो 100mbps, 4k packets  */

/* Advertisement control रेजिस्टर. */
#घोषणा ADVERTISE_SLCT		0x001f	/* Selector bits               */
#घोषणा ADVERTISE_CSMA		0x0001	/* Only selector supported     */
#घोषणा ADVERTISE_10HALF	0x0020	/* Try क्रम 10mbps half-duplex  */
#घोषणा ADVERTISE_1000XFULL	0x0020	/* Try क्रम 1000BASE-X full-duplex */
#घोषणा ADVERTISE_10FULL	0x0040	/* Try क्रम 10mbps full-duplex  */
#घोषणा ADVERTISE_1000XHALF	0x0040	/* Try क्रम 1000BASE-X half-duplex */
#घोषणा ADVERTISE_100HALF	0x0080	/* Try क्रम 100mbps half-duplex */
#घोषणा ADVERTISE_1000XPAUSE	0x0080	/* Try क्रम 1000BASE-X छोड़ो    */
#घोषणा ADVERTISE_100FULL	0x0100	/* Try क्रम 100mbps full-duplex */
#घोषणा ADVERTISE_1000XPSE_ASYM	0x0100	/* Try क्रम 1000BASE-X asym छोड़ो */
#घोषणा ADVERTISE_100BASE4	0x0200	/* Try क्रम 100mbps 4k packets  */
#घोषणा ADVERTISE_PAUSE_CAP	0x0400	/* Try क्रम छोड़ो               */
#घोषणा ADVERTISE_PAUSE_ASYM	0x0800	/* Try क्रम asymetric छोड़ो     */
#घोषणा ADVERTISE_RESV		0x1000	/* Unused...                   */
#घोषणा ADVERTISE_RFAULT	0x2000	/* Say we can detect faults    */
#घोषणा ADVERTISE_LPACK		0x4000	/* Ack link partners response  */
#घोषणा ADVERTISE_NPAGE		0x8000	/* Next page bit               */

#घोषणा ADVERTISE_FULL		(ADVERTISE_100FULL | ADVERTISE_10FULL | \
				  ADVERTISE_CSMA)
#घोषणा ADVERTISE_ALL		(ADVERTISE_10HALF | ADVERTISE_10FULL | \
				  ADVERTISE_100HALF | ADVERTISE_100FULL)

/* Link partner ability रेजिस्टर. */
#घोषणा LPA_SLCT		0x001f	/* Same as advertise selector  */
#घोषणा LPA_10HALF		0x0020	/* Can करो 10mbps half-duplex   */
#घोषणा LPA_1000XFULL		0x0020	/* Can करो 1000BASE-X full-duplex */
#घोषणा LPA_10FULL		0x0040	/* Can करो 10mbps full-duplex   */
#घोषणा LPA_1000XHALF		0x0040	/* Can करो 1000BASE-X half-duplex */
#घोषणा LPA_100HALF		0x0080	/* Can करो 100mbps half-duplex  */
#घोषणा LPA_1000XPAUSE		0x0080	/* Can करो 1000BASE-X छोड़ो     */
#घोषणा LPA_100FULL		0x0100	/* Can करो 100mbps full-duplex  */
#घोषणा LPA_1000XPAUSE_ASYM	0x0100	/* Can करो 1000BASE-X छोड़ो asym*/
#घोषणा LPA_100BASE4		0x0200	/* Can करो 100mbps 4k packets   */
#घोषणा LPA_PAUSE_CAP		0x0400	/* Can छोड़ो                   */
#घोषणा LPA_PAUSE_ASYM		0x0800	/* Can छोड़ो asymetrically     */
#घोषणा LPA_RESV		0x1000	/* Unused...                   */
#घोषणा LPA_RFAULT		0x2000	/* Link partner faulted        */
#घोषणा LPA_LPACK		0x4000	/* Link partner acked us       */
#घोषणा LPA_NPAGE		0x8000	/* Next page bit               */

#घोषणा LPA_DUPLEX		(LPA_10FULL | LPA_100FULL)
#घोषणा LPA_100			(LPA_100FULL | LPA_100HALF | LPA_100BASE4)

/* Expansion रेजिस्टर क्रम स्वतः-negotiation. */
#घोषणा EXPANSION_NWAY		0x0001	/* Can करो N-way स्वतः-nego      */
#घोषणा EXPANSION_LCWP		0x0002	/* Got new RX page code word   */
#घोषणा EXPANSION_ENABLENPAGE	0x0004	/* This enables npage words    */
#घोषणा EXPANSION_NPCAPABLE	0x0008	/* Link partner supports npage */
#घोषणा EXPANSION_MFAULTS	0x0010	/* Multiple faults detected    */
#घोषणा EXPANSION_RESV		0xffe0	/* Unused...                   */

#घोषणा ESTATUS_1000_XFULL	0x8000	/* Can करो 1000BaseX Full       */
#घोषणा ESTATUS_1000_XHALF	0x4000	/* Can करो 1000BaseX Half       */
#घोषणा ESTATUS_1000_TFULL	0x2000	/* Can करो 1000BT Full          */
#घोषणा ESTATUS_1000_THALF	0x1000	/* Can करो 1000BT Half          */

/* N-way test रेजिस्टर. */
#घोषणा NWAYTEST_RESV1		0x00ff	/* Unused...                   */
#घोषणा NWAYTEST_LOOPBACK	0x0100	/* Enable loopback क्रम N-way   */
#घोषणा NWAYTEST_RESV2		0xfe00	/* Unused...                   */

/* MAC and PHY tx_config_Reg[15:0] क्रम SGMII in-band स्वतः-negotiation.*/
#घोषणा ADVERTISE_SGMII		0x0001	/* MAC can करो SGMII            */
#घोषणा LPA_SGMII		0x0001	/* PHY can करो SGMII            */
#घोषणा LPA_SGMII_SPD_MASK	0x0c00	/* SGMII speed mask            */
#घोषणा LPA_SGMII_FULL_DUPLEX	0x1000	/* SGMII full duplex           */
#घोषणा LPA_SGMII_DPX_SPD_MASK	0x1C00	/* SGMII duplex and speed bits */
#घोषणा LPA_SGMII_10		0x0000	/* 10Mbps                      */
#घोषणा LPA_SGMII_10HALF	0x0000	/* Can करो 10mbps half-duplex   */
#घोषणा LPA_SGMII_10FULL	0x1000	/* Can करो 10mbps full-duplex   */
#घोषणा LPA_SGMII_100		0x0400	/* 100Mbps                     */
#घोषणा LPA_SGMII_100HALF	0x0400	/* Can करो 100mbps half-duplex  */
#घोषणा LPA_SGMII_100FULL	0x1400	/* Can करो 100mbps full-duplex  */
#घोषणा LPA_SGMII_1000		0x0800	/* 1000Mbps                    */
#घोषणा LPA_SGMII_1000HALF	0x0800	/* Can करो 1000mbps half-duplex */
#घोषणा LPA_SGMII_1000FULL	0x1800	/* Can करो 1000mbps full-duplex */
#घोषणा LPA_SGMII_LINK		0x8000	/* PHY link with copper-side partner */

/* 1000BASE-T Control रेजिस्टर */
#घोषणा ADVERTISE_1000FULL	0x0200  /* Advertise 1000BASE-T full duplex */
#घोषणा ADVERTISE_1000HALF	0x0100  /* Advertise 1000BASE-T half duplex */
#घोषणा CTL1000_PREFER_MASTER	0x0400  /* prefer to operate as master */
#घोषणा CTL1000_AS_MASTER	0x0800
#घोषणा CTL1000_ENABLE_MASTER	0x1000

/* 1000BASE-T Status रेजिस्टर */
#घोषणा LPA_1000MSFAIL		0x8000	/* Master/Slave resolution failure */
#घोषणा LPA_1000MSRES		0x4000	/* Master/Slave resolution status */
#घोषणा LPA_1000LOCALRXOK	0x2000	/* Link partner local receiver status */
#घोषणा LPA_1000REMRXOK		0x1000	/* Link partner remote receiver status */
#घोषणा LPA_1000FULL		0x0800	/* Link partner 1000BASE-T full duplex */
#घोषणा LPA_1000HALF		0x0400	/* Link partner 1000BASE-T half duplex */

/* Flow control flags */
#घोषणा FLOW_CTRL_TX		0x01
#घोषणा FLOW_CTRL_RX		0x02

/* MMD Access Control रेजिस्टर fields */
#घोषणा MII_MMD_CTRL_DEVAD_MASK	0x1f	/* Mask MMD DEVAD*/
#घोषणा MII_MMD_CTRL_ADDR	0x0000	/* Address */
#घोषणा MII_MMD_CTRL_NOINCR	0x4000	/* no post increment */
#घोषणा MII_MMD_CTRL_INCR_RDWT	0x8000	/* post increment on पढ़ोs & ग_लिखोs */
#घोषणा MII_MMD_CTRL_INCR_ON_WT	0xC000	/* post increment on ग_लिखोs only */

/* This काष्ठाure is used in all SIOCxMIIxxx ioctl calls */
काष्ठा mii_ioctl_data अणु
	__u16		phy_id;
	__u16		reg_num;
	__u16		val_in;
	__u16		val_out;
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_MII_H__ */
