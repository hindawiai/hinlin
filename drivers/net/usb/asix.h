<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ASIX AX8817X based USB 2.0 Ethernet Devices
 * Copyright (C) 2003-2006 David Hollis <dhollis@davehollis.com>
 * Copyright (C) 2005 Phil Chang <pchang23@sbcglobal.net>
 * Copyright (C) 2006 James Paपूर्णांकer <jamie.paपूर्णांकer@iname.com>
 * Copyright (c) 2002-2003 TiVo Inc.
 */

#अगर_अघोषित _ASIX_H
#घोषणा _ASIX_H

// #घोषणा	DEBUG			// error path messages, extra info
// #घोषणा	VERBOSE			// more; success messages

#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_vlan.h>

#घोषणा DRIVER_VERSION "22-Dec-2011"
#घोषणा DRIVER_NAME "asix"

/* ASIX AX8817X based USB 2.0 Ethernet Devices */

#घोषणा AX_CMD_SET_SW_MII		0x06
#घोषणा AX_CMD_READ_MII_REG		0x07
#घोषणा AX_CMD_WRITE_MII_REG		0x08
#घोषणा AX_CMD_STATMNGSTS_REG		0x09
#घोषणा AX_CMD_SET_HW_MII		0x0a
#घोषणा AX_CMD_READ_EEPROM		0x0b
#घोषणा AX_CMD_WRITE_EEPROM		0x0c
#घोषणा AX_CMD_WRITE_ENABLE		0x0d
#घोषणा AX_CMD_WRITE_DISABLE		0x0e
#घोषणा AX_CMD_READ_RX_CTL		0x0f
#घोषणा AX_CMD_WRITE_RX_CTL		0x10
#घोषणा AX_CMD_READ_IPG012		0x11
#घोषणा AX_CMD_WRITE_IPG0		0x12
#घोषणा AX_CMD_WRITE_IPG1		0x13
#घोषणा AX_CMD_READ_NODE_ID		0x13
#घोषणा AX_CMD_WRITE_NODE_ID		0x14
#घोषणा AX_CMD_WRITE_IPG2		0x14
#घोषणा AX_CMD_WRITE_MULTI_FILTER	0x16
#घोषणा AX88172_CMD_READ_NODE_ID	0x17
#घोषणा AX_CMD_READ_PHY_ID		0x19
#घोषणा AX_CMD_READ_MEDIUM_STATUS	0x1a
#घोषणा AX_CMD_WRITE_MEDIUM_MODE	0x1b
#घोषणा AX_CMD_READ_MONITOR_MODE	0x1c
#घोषणा AX_CMD_WRITE_MONITOR_MODE	0x1d
#घोषणा AX_CMD_READ_GPIOS		0x1e
#घोषणा AX_CMD_WRITE_GPIOS		0x1f
#घोषणा AX_CMD_SW_RESET			0x20
#घोषणा AX_CMD_SW_PHY_STATUS		0x21
#घोषणा AX_CMD_SW_PHY_SELECT		0x22
#घोषणा AX_QCTCTRL			0x2A

#घोषणा AX_CHIPCODE_MASK		0x70
#घोषणा AX_AX88772_CHIPCODE		0x00
#घोषणा AX_AX88772A_CHIPCODE		0x10
#घोषणा AX_AX88772B_CHIPCODE		0x20
#घोषणा AX_HOST_EN			0x01

#घोषणा AX_PHYSEL_PSEL			0x01
#घोषणा AX_PHYSEL_SSMII			0
#घोषणा AX_PHYSEL_SSEN			0x10

#घोषणा AX_PHY_SELECT_MASK		(BIT(3) | BIT(2))
#घोषणा AX_PHY_SELECT_INTERNAL		0
#घोषणा AX_PHY_SELECT_EXTERNAL		BIT(2)

#घोषणा AX_MONITOR_MODE			0x01
#घोषणा AX_MONITOR_LINK			0x02
#घोषणा AX_MONITOR_MAGIC		0x04
#घोषणा AX_MONITOR_HSFS			0x10

/* AX88172 Medium Status Register values */
#घोषणा AX88172_MEDIUM_FD		0x02
#घोषणा AX88172_MEDIUM_TX		0x04
#घोषणा AX88172_MEDIUM_FC		0x10
#घोषणा AX88172_MEDIUM_DEFAULT \
		( AX88172_MEDIUM_FD | AX88172_MEDIUM_TX | AX88172_MEDIUM_FC )

#घोषणा AX_MCAST_FILTER_SIZE		8
#घोषणा AX_MAX_MCAST			64

#घोषणा AX_SWRESET_CLEAR		0x00
#घोषणा AX_SWRESET_RR			0x01
#घोषणा AX_SWRESET_RT			0x02
#घोषणा AX_SWRESET_PRTE			0x04
#घोषणा AX_SWRESET_PRL			0x08
#घोषणा AX_SWRESET_BZ			0x10
#घोषणा AX_SWRESET_IPRL			0x20
#घोषणा AX_SWRESET_IPPD			0x40

#घोषणा AX88772_IPG0_DEFAULT		0x15
#घोषणा AX88772_IPG1_DEFAULT		0x0c
#घोषणा AX88772_IPG2_DEFAULT		0x12

/* AX88772 & AX88178 Medium Mode Register */
#घोषणा AX_MEDIUM_PF		0x0080
#घोषणा AX_MEDIUM_JFE		0x0040
#घोषणा AX_MEDIUM_TFC		0x0020
#घोषणा AX_MEDIUM_RFC		0x0010
#घोषणा AX_MEDIUM_ENCK		0x0008
#घोषणा AX_MEDIUM_AC		0x0004
#घोषणा AX_MEDIUM_FD		0x0002
#घोषणा AX_MEDIUM_GM		0x0001
#घोषणा AX_MEDIUM_SM		0x1000
#घोषणा AX_MEDIUM_SBP		0x0800
#घोषणा AX_MEDIUM_PS		0x0200
#घोषणा AX_MEDIUM_RE		0x0100

#घोषणा AX88178_MEDIUM_DEFAULT	\
	(AX_MEDIUM_PS | AX_MEDIUM_FD | AX_MEDIUM_AC | \
	 AX_MEDIUM_RFC | AX_MEDIUM_TFC | AX_MEDIUM_JFE | \
	 AX_MEDIUM_RE)

#घोषणा AX88772_MEDIUM_DEFAULT	\
	(AX_MEDIUM_FD | AX_MEDIUM_RFC | \
	 AX_MEDIUM_TFC | AX_MEDIUM_PS | \
	 AX_MEDIUM_AC | AX_MEDIUM_RE)

/* AX88772 & AX88178 RX_CTL values */
#घोषणा AX_RX_CTL_SO		0x0080
#घोषणा AX_RX_CTL_AP		0x0020
#घोषणा AX_RX_CTL_AM		0x0010
#घोषणा AX_RX_CTL_AB		0x0008
#घोषणा AX_RX_CTL_SEP		0x0004
#घोषणा AX_RX_CTL_AMALL		0x0002
#घोषणा AX_RX_CTL_PRO		0x0001
#घोषणा AX_RX_CTL_MFB_2048	0x0000
#घोषणा AX_RX_CTL_MFB_4096	0x0100
#घोषणा AX_RX_CTL_MFB_8192	0x0200
#घोषणा AX_RX_CTL_MFB_16384	0x0300

#घोषणा AX_DEFAULT_RX_CTL	(AX_RX_CTL_SO | AX_RX_CTL_AB)

/* GPIO 0 .. 2 toggles */
#घोषणा AX_GPIO_GPO0EN		0x01	/* GPIO0 Output enable */
#घोषणा AX_GPIO_GPO_0		0x02	/* GPIO0 Output value */
#घोषणा AX_GPIO_GPO1EN		0x04	/* GPIO1 Output enable */
#घोषणा AX_GPIO_GPO_1		0x08	/* GPIO1 Output value */
#घोषणा AX_GPIO_GPO2EN		0x10	/* GPIO2 Output enable */
#घोषणा AX_GPIO_GPO_2		0x20	/* GPIO2 Output value */
#घोषणा AX_GPIO_RESERVED	0x40	/* Reserved */
#घोषणा AX_GPIO_RSE		0x80	/* Reload serial EEPROM */

#घोषणा AX_EEPROM_MAGIC		0xdeadbeef
#घोषणा AX_EEPROM_LEN		0x200

/* This काष्ठाure cannot exceed माप(अचिन्हित दीर्घ [5]) AKA 20 bytes */
काष्ठा asix_data अणु
	u8 multi_filter[AX_MCAST_FILTER_SIZE];
	u8 mac_addr[ETH_ALEN];
	u8 phymode;
	u8 ledmode;
	u8 res;
पूर्ण;

काष्ठा asix_rx_fixup_info अणु
	काष्ठा sk_buff *ax_skb;
	u32 header;
	u16 reमुख्यing;
	bool split_head;
पूर्ण;

काष्ठा asix_common_निजी अणु
	व्योम (*resume)(काष्ठा usbnet *dev);
	व्योम (*suspend)(काष्ठा usbnet *dev);
	u16 presvd_phy_advertise;
	u16 presvd_phy_bmcr;
	काष्ठा asix_rx_fixup_info rx_fixup_info;
पूर्ण;

बाह्य स्थिर काष्ठा driver_info ax88172a_info;

/* ASIX specअगरic flags */
#घोषणा FLAG_EEPROM_MAC		(1UL << 0)  /* init device MAC from eeprom */

पूर्णांक asix_पढ़ो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
		  u16 size, व्योम *data, पूर्णांक in_pm);

पूर्णांक asix_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
		   u16 size, व्योम *data, पूर्णांक in_pm);

व्योम asix_ग_लिखो_cmd_async(काष्ठा usbnet *dev, u8 cmd, u16 value,
			  u16 index, u16 size, व्योम *data);

पूर्णांक asix_rx_fixup_पूर्णांकernal(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
			   काष्ठा asix_rx_fixup_info *rx);
पूर्णांक asix_rx_fixup_common(काष्ठा usbnet *dev, काष्ठा sk_buff *skb);
व्योम asix_rx_fixup_common_मुक्त(काष्ठा asix_common_निजी *dp);

काष्ठा sk_buff *asix_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
			      gfp_t flags);

पूर्णांक asix_set_sw_mii(काष्ठा usbnet *dev, पूर्णांक in_pm);
पूर्णांक asix_set_hw_mii(काष्ठा usbnet *dev, पूर्णांक in_pm);

पूर्णांक asix_पढ़ो_phy_addr(काष्ठा usbnet *dev, पूर्णांक पूर्णांकernal);
पूर्णांक asix_get_phy_addr(काष्ठा usbnet *dev);

पूर्णांक asix_sw_reset(काष्ठा usbnet *dev, u8 flags, पूर्णांक in_pm);

u16 asix_पढ़ो_rx_ctl(काष्ठा usbnet *dev, पूर्णांक in_pm);
पूर्णांक asix_ग_लिखो_rx_ctl(काष्ठा usbnet *dev, u16 mode, पूर्णांक in_pm);

u16 asix_पढ़ो_medium_status(काष्ठा usbnet *dev, पूर्णांक in_pm);
पूर्णांक asix_ग_लिखो_medium_mode(काष्ठा usbnet *dev, u16 mode, पूर्णांक in_pm);

पूर्णांक asix_ग_लिखो_gpio(काष्ठा usbnet *dev, u16 value, पूर्णांक sleep, पूर्णांक in_pm);

व्योम asix_set_multicast(काष्ठा net_device *net);

पूर्णांक asix_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc);
व्योम asix_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक val);

पूर्णांक asix_mdio_पढ़ो_nopm(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc);
व्योम asix_mdio_ग_लिखो_nopm(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc,
			  पूर्णांक val);

व्योम asix_get_wol(काष्ठा net_device *net, काष्ठा ethtool_wolinfo *wolinfo);
पूर्णांक asix_set_wol(काष्ठा net_device *net, काष्ठा ethtool_wolinfo *wolinfo);

पूर्णांक asix_get_eeprom_len(काष्ठा net_device *net);
पूर्णांक asix_get_eeprom(काष्ठा net_device *net, काष्ठा ethtool_eeprom *eeprom,
		    u8 *data);
पूर्णांक asix_set_eeprom(काष्ठा net_device *net, काष्ठा ethtool_eeprom *eeprom,
		    u8 *data);

व्योम asix_get_drvinfo(काष्ठा net_device *net, काष्ठा ethtool_drvinfo *info);

पूर्णांक asix_set_mac_address(काष्ठा net_device *net, व्योम *p);

#पूर्ण_अगर /* _ASIX_H */
