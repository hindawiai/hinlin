<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ASIX AX88179/178A USB 3.0/2.0 to Gigabit Ethernet Devices
 *
 * Copyright (C) 2011-2013 ASIX
 */

#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <uapi/linux/mdपन.स>
#समावेश <linux/mdपन.स>

#घोषणा AX88179_PHY_ID				0x03
#घोषणा AX_EEPROM_LEN				0x100
#घोषणा AX88179_EEPROM_MAGIC			0x17900b95
#घोषणा AX_MCAST_FLTSIZE			8
#घोषणा AX_MAX_MCAST				64
#घोषणा AX_INT_PPLS_LINK			((u32)BIT(16))
#घोषणा AX_RXHDR_L4_TYPE_MASK			0x1c
#घोषणा AX_RXHDR_L4_TYPE_UDP			4
#घोषणा AX_RXHDR_L4_TYPE_TCP			16
#घोषणा AX_RXHDR_L3CSUM_ERR			2
#घोषणा AX_RXHDR_L4CSUM_ERR			1
#घोषणा AX_RXHDR_CRC_ERR			((u32)BIT(29))
#घोषणा AX_RXHDR_DROP_ERR			((u32)BIT(31))
#घोषणा AX_ACCESS_MAC				0x01
#घोषणा AX_ACCESS_PHY				0x02
#घोषणा AX_ACCESS_EEPROM			0x04
#घोषणा AX_ACCESS_EFUS				0x05
#घोषणा AX_RELOAD_EEPROM_EFUSE			0x06
#घोषणा AX_PAUSE_WATERLVL_HIGH			0x54
#घोषणा AX_PAUSE_WATERLVL_LOW			0x55

#घोषणा PHYSICAL_LINK_STATUS			0x02
	#घोषणा	AX_USB_SS		0x04
	#घोषणा	AX_USB_HS		0x02

#घोषणा GENERAL_STATUS				0x03
/* Check AX88179 version. UA1:Bit2 = 0,  UA2:Bit2 = 1 */
	#घोषणा	AX_SECLD		0x04

#घोषणा AX_SROM_ADDR				0x07
#घोषणा AX_SROM_CMD				0x0a
	#घोषणा EEP_RD			0x04
	#घोषणा EEP_BUSY		0x10

#घोषणा AX_SROM_DATA_LOW			0x08
#घोषणा AX_SROM_DATA_HIGH			0x09

#घोषणा AX_RX_CTL				0x0b
	#घोषणा AX_RX_CTL_DROPCRCERR	0x0100
	#घोषणा AX_RX_CTL_IPE		0x0200
	#घोषणा AX_RX_CTL_START		0x0080
	#घोषणा AX_RX_CTL_AP		0x0020
	#घोषणा AX_RX_CTL_AM		0x0010
	#घोषणा AX_RX_CTL_AB		0x0008
	#घोषणा AX_RX_CTL_AMALL		0x0002
	#घोषणा AX_RX_CTL_PRO		0x0001
	#घोषणा AX_RX_CTL_STOP		0x0000

#घोषणा AX_NODE_ID				0x10
#घोषणा AX_MULFLTARY				0x16

#घोषणा AX_MEDIUM_STATUS_MODE			0x22
	#घोषणा AX_MEDIUM_GIGAMODE	0x01
	#घोषणा AX_MEDIUM_FULL_DUPLEX	0x02
	#घोषणा AX_MEDIUM_EN_125MHZ	0x08
	#घोषणा AX_MEDIUM_RXFLOW_CTRLEN	0x10
	#घोषणा AX_MEDIUM_TXFLOW_CTRLEN	0x20
	#घोषणा AX_MEDIUM_RECEIVE_EN	0x100
	#घोषणा AX_MEDIUM_PS		0x200
	#घोषणा AX_MEDIUM_JUMBO_EN	0x8040

#घोषणा AX_MONITOR_MOD				0x24
	#घोषणा AX_MONITOR_MODE_RWLC	0x02
	#घोषणा AX_MONITOR_MODE_RWMP	0x04
	#घोषणा AX_MONITOR_MODE_PMEPOL	0x20
	#घोषणा AX_MONITOR_MODE_PMETYPE	0x40

#घोषणा AX_GPIO_CTRL				0x25
	#घोषणा AX_GPIO_CTRL_GPIO3EN	0x80
	#घोषणा AX_GPIO_CTRL_GPIO2EN	0x40
	#घोषणा AX_GPIO_CTRL_GPIO1EN	0x20

#घोषणा AX_PHYPWR_RSTCTL			0x26
	#घोषणा AX_PHYPWR_RSTCTL_BZ	0x0010
	#घोषणा AX_PHYPWR_RSTCTL_IPRL	0x0020
	#घोषणा AX_PHYPWR_RSTCTL_AT	0x1000

#घोषणा AX_RX_BULKIN_QCTRL			0x2e
#घोषणा AX_CLK_SELECT				0x33
	#घोषणा AX_CLK_SELECT_BCS	0x01
	#घोषणा AX_CLK_SELECT_ACS	0x02
	#घोषणा AX_CLK_SELECT_ULR	0x08

#घोषणा AX_RXCOE_CTL				0x34
	#घोषणा AX_RXCOE_IP		0x01
	#घोषणा AX_RXCOE_TCP		0x02
	#घोषणा AX_RXCOE_UDP		0x04
	#घोषणा AX_RXCOE_TCPV6		0x20
	#घोषणा AX_RXCOE_UDPV6		0x40

#घोषणा AX_TXCOE_CTL				0x35
	#घोषणा AX_TXCOE_IP		0x01
	#घोषणा AX_TXCOE_TCP		0x02
	#घोषणा AX_TXCOE_UDP		0x04
	#घोषणा AX_TXCOE_TCPV6		0x20
	#घोषणा AX_TXCOE_UDPV6		0x40

#घोषणा AX_LEDCTRL				0x73

#घोषणा GMII_PHY_PHYSR				0x11
	#घोषणा GMII_PHY_PHYSR_SMASK	0xc000
	#घोषणा GMII_PHY_PHYSR_GIGA	0x8000
	#घोषणा GMII_PHY_PHYSR_100	0x4000
	#घोषणा GMII_PHY_PHYSR_FULL	0x2000
	#घोषणा GMII_PHY_PHYSR_LINK	0x400

#घोषणा GMII_LED_ACT				0x1a
	#घोषणा	GMII_LED_ACTIVE_MASK	0xff8f
	#घोषणा	GMII_LED0_ACTIVE	BIT(4)
	#घोषणा	GMII_LED1_ACTIVE	BIT(5)
	#घोषणा	GMII_LED2_ACTIVE	BIT(6)

#घोषणा GMII_LED_LINK				0x1c
	#घोषणा	GMII_LED_LINK_MASK	0xf888
	#घोषणा	GMII_LED0_LINK_10	BIT(0)
	#घोषणा	GMII_LED0_LINK_100	BIT(1)
	#घोषणा	GMII_LED0_LINK_1000	BIT(2)
	#घोषणा	GMII_LED1_LINK_10	BIT(4)
	#घोषणा	GMII_LED1_LINK_100	BIT(5)
	#घोषणा	GMII_LED1_LINK_1000	BIT(6)
	#घोषणा	GMII_LED2_LINK_10	BIT(8)
	#घोषणा	GMII_LED2_LINK_100	BIT(9)
	#घोषणा	GMII_LED2_LINK_1000	BIT(10)
	#घोषणा	LED0_ACTIVE		BIT(0)
	#घोषणा	LED0_LINK_10		BIT(1)
	#घोषणा	LED0_LINK_100		BIT(2)
	#घोषणा	LED0_LINK_1000		BIT(3)
	#घोषणा	LED0_FD			BIT(4)
	#घोषणा	LED0_USB3_MASK		0x001f
	#घोषणा	LED1_ACTIVE		BIT(5)
	#घोषणा	LED1_LINK_10		BIT(6)
	#घोषणा	LED1_LINK_100		BIT(7)
	#घोषणा	LED1_LINK_1000		BIT(8)
	#घोषणा	LED1_FD			BIT(9)
	#घोषणा	LED1_USB3_MASK		0x03e0
	#घोषणा	LED2_ACTIVE		BIT(10)
	#घोषणा	LED2_LINK_1000		BIT(13)
	#घोषणा	LED2_LINK_100		BIT(12)
	#घोषणा	LED2_LINK_10		BIT(11)
	#घोषणा	LED2_FD			BIT(14)
	#घोषणा	LED_VALID		BIT(15)
	#घोषणा	LED2_USB3_MASK		0x7c00

#घोषणा GMII_PHYPAGE				0x1e
#घोषणा GMII_PHY_PAGE_SELECT			0x1f
	#घोषणा GMII_PHY_PGSEL_EXT	0x0007
	#घोषणा GMII_PHY_PGSEL_PAGE0	0x0000
	#घोषणा GMII_PHY_PGSEL_PAGE3	0x0003
	#घोषणा GMII_PHY_PGSEL_PAGE5	0x0005

काष्ठा ax88179_data अणु
	u8  eee_enabled;
	u8  eee_active;
	u16 rxctl;
	u16 reserved;
पूर्ण;

काष्ठा ax88179_पूर्णांक_data अणु
	__le32 पूर्णांकdata1;
	__le32 पूर्णांकdata2;
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर ctrl, समयr_l, समयr_h, size, अगरg;
पूर्ण AX88179_BULKIN_SIZE[] =	अणु
	अणु7, 0x4f, 0,	0x12, 0xffपूर्ण,
	अणु7, 0x20, 3,	0x16, 0xffपूर्ण,
	अणु7, 0xae, 7,	0x18, 0xffपूर्ण,
	अणु7, 0xcc, 0x4c, 0x18, 8पूर्ण,
पूर्ण;

अटल पूर्णांक __ax88179_पढ़ो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
			      u16 size, व्योम *data, पूर्णांक in_pm)
अणु
	पूर्णांक ret;
	पूर्णांक (*fn)(काष्ठा usbnet *, u8, u8, u16, u16, व्योम *, u16);

	BUG_ON(!dev);

	अगर (!in_pm)
		fn = usbnet_पढ़ो_cmd;
	अन्यथा
		fn = usbnet_पढ़ो_cmd_nopm;

	ret = fn(dev, cmd, USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		 value, index, data, size);

	अगर (unlikely(ret < 0))
		netdev_warn(dev->net, "Failed to read reg index 0x%04x: %d\n",
			    index, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __ax88179_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
			       u16 size, व्योम *data, पूर्णांक in_pm)
अणु
	पूर्णांक ret;
	पूर्णांक (*fn)(काष्ठा usbnet *, u8, u8, u16, u16, स्थिर व्योम *, u16);

	BUG_ON(!dev);

	अगर (!in_pm)
		fn = usbnet_ग_लिखो_cmd;
	अन्यथा
		fn = usbnet_ग_लिखो_cmd_nopm;

	ret = fn(dev, cmd, USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		 value, index, data, size);

	अगर (unlikely(ret < 0))
		netdev_warn(dev->net, "Failed to write reg index 0x%04x: %d\n",
			    index, ret);

	वापस ret;
पूर्ण

अटल व्योम ax88179_ग_लिखो_cmd_async(काष्ठा usbnet *dev, u8 cmd, u16 value,
				    u16 index, u16 size, व्योम *data)
अणु
	u16 buf;

	अगर (2 == size) अणु
		buf = *((u16 *)data);
		cpu_to_le16s(&buf);
		usbnet_ग_लिखो_cmd_async(dev, cmd, USB_सूची_OUT | USB_TYPE_VENDOR |
				       USB_RECIP_DEVICE, value, index, &buf,
				       size);
	पूर्ण अन्यथा अणु
		usbnet_ग_लिखो_cmd_async(dev, cmd, USB_सूची_OUT | USB_TYPE_VENDOR |
				       USB_RECIP_DEVICE, value, index, data,
				       size);
	पूर्ण
पूर्ण

अटल पूर्णांक ax88179_पढ़ो_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u16 value,
				 u16 index, u16 size, व्योम *data)
अणु
	पूर्णांक ret;

	अगर (2 == size) अणु
		u16 buf;
		ret = __ax88179_पढ़ो_cmd(dev, cmd, value, index, size, &buf, 1);
		le16_to_cpus(&buf);
		*((u16 *)data) = buf;
	पूर्ण अन्यथा अगर (4 == size) अणु
		u32 buf;
		ret = __ax88179_पढ़ो_cmd(dev, cmd, value, index, size, &buf, 1);
		le32_to_cpus(&buf);
		*((u32 *)data) = buf;
	पूर्ण अन्यथा अणु
		ret = __ax88179_पढ़ो_cmd(dev, cmd, value, index, size, data, 1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ax88179_ग_लिखो_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u16 value,
				  u16 index, u16 size, व्योम *data)
अणु
	पूर्णांक ret;

	अगर (2 == size) अणु
		u16 buf;
		buf = *((u16 *)data);
		cpu_to_le16s(&buf);
		ret = __ax88179_ग_लिखो_cmd(dev, cmd, value, index,
					  size, &buf, 1);
	पूर्ण अन्यथा अणु
		ret = __ax88179_ग_लिखो_cmd(dev, cmd, value, index,
					  size, data, 1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ax88179_पढ़ो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
			    u16 size, व्योम *data)
अणु
	पूर्णांक ret;

	अगर (2 == size) अणु
		u16 buf = 0;
		ret = __ax88179_पढ़ो_cmd(dev, cmd, value, index, size, &buf, 0);
		le16_to_cpus(&buf);
		*((u16 *)data) = buf;
	पूर्ण अन्यथा अगर (4 == size) अणु
		u32 buf = 0;
		ret = __ax88179_पढ़ो_cmd(dev, cmd, value, index, size, &buf, 0);
		le32_to_cpus(&buf);
		*((u32 *)data) = buf;
	पूर्ण अन्यथा अणु
		ret = __ax88179_पढ़ो_cmd(dev, cmd, value, index, size, data, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ax88179_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
			     u16 size, व्योम *data)
अणु
	पूर्णांक ret;

	अगर (2 == size) अणु
		u16 buf;
		buf = *((u16 *)data);
		cpu_to_le16s(&buf);
		ret = __ax88179_ग_लिखो_cmd(dev, cmd, value, index,
					  size, &buf, 0);
	पूर्ण अन्यथा अणु
		ret = __ax88179_ग_लिखो_cmd(dev, cmd, value, index,
					  size, data, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ax88179_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	काष्ठा ax88179_पूर्णांक_data *event;
	u32 link;

	अगर (urb->actual_length < 8)
		वापस;

	event = urb->transfer_buffer;
	le32_to_cpus((व्योम *)&event->पूर्णांकdata1);

	link = (((__क्रमce u32)event->पूर्णांकdata1) & AX_INT_PPLS_LINK) >> 16;

	अगर (netअगर_carrier_ok(dev->net) != link) अणु
		usbnet_link_change(dev, link, 1);
		netdev_info(dev->net, "ax88179 - Link status is: %d\n", link);
	पूर्ण
पूर्ण

अटल पूर्णांक ax88179_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	u16 res;

	ax88179_पढ़ो_cmd(dev, AX_ACCESS_PHY, phy_id, (__u16)loc, 2, &res);
	वापस res;
पूर्ण

अटल व्योम ax88179_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc,
			       पूर्णांक val)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	u16 res = (u16) val;

	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, phy_id, (__u16)loc, 2, &res);
पूर्ण

अटल अंतरभूत पूर्णांक ax88179_phy_mmd_indirect(काष्ठा usbnet *dev, u16 prtad,
					   u16 devad)
अणु
	u16 पंचांगp16;
	पूर्णांक ret;

	पंचांगp16 = devad;
	ret = ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_CTRL, 2, &पंचांगp16);

	पंचांगp16 = prtad;
	ret = ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_DATA, 2, &पंचांगp16);

	पंचांगp16 = devad | MII_MMD_CTRL_NOINCR;
	ret = ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_CTRL, 2, &पंचांगp16);

	वापस ret;
पूर्ण

अटल पूर्णांक
ax88179_phy_पढ़ो_mmd_indirect(काष्ठा usbnet *dev, u16 prtad, u16 devad)
अणु
	पूर्णांक ret;
	u16 पंचांगp16;

	ax88179_phy_mmd_indirect(dev, prtad, devad);

	ret = ax88179_पढ़ो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			       MII_MMD_DATA, 2, &पंचांगp16);
	अगर (ret < 0)
		वापस ret;

	वापस पंचांगp16;
पूर्ण

अटल पूर्णांक
ax88179_phy_ग_लिखो_mmd_indirect(काष्ठा usbnet *dev, u16 prtad, u16 devad,
			       u16 data)
अणु
	पूर्णांक ret;

	ax88179_phy_mmd_indirect(dev, prtad, devad);

	ret = ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_DATA, 2, &data);

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	u16 पंचांगp16;
	u8 पंचांगp8;

	usbnet_suspend(पूर्णांकf, message);

	/* Disable RX path */
	ax88179_पढ़ो_cmd_nopm(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			      2, 2, &पंचांगp16);
	पंचांगp16 &= ~AX_MEDIUM_RECEIVE_EN;
	ax88179_ग_लिखो_cmd_nopm(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			       2, 2, &पंचांगp16);

	/* Force bulk-in zero length */
	ax88179_पढ़ो_cmd_nopm(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL,
			      2, 2, &पंचांगp16);

	पंचांगp16 |= AX_PHYPWR_RSTCTL_BZ | AX_PHYPWR_RSTCTL_IPRL;
	ax88179_ग_लिखो_cmd_nopm(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL,
			       2, 2, &पंचांगp16);

	/* change घड़ी */
	पंचांगp8 = 0;
	ax88179_ग_लिखो_cmd_nopm(dev, AX_ACCESS_MAC, AX_CLK_SELECT, 1, 1, &पंचांगp8);

	/* Configure RX control रेजिस्टर => stop operation */
	पंचांगp16 = AX_RX_CTL_STOP;
	ax88179_ग_लिखो_cmd_nopm(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2, &पंचांगp16);

	वापस 0;
पूर्ण

/* This function is used to enable the स्वतःdetach function. */
/* This function is determined by offset 0x43 of EEPROM */
अटल पूर्णांक ax88179_स्वतः_detach(काष्ठा usbnet *dev, पूर्णांक in_pm)
अणु
	u16 पंचांगp16;
	u8 पंचांगp8;
	पूर्णांक (*fnr)(काष्ठा usbnet *, u8, u16, u16, u16, व्योम *);
	पूर्णांक (*fnw)(काष्ठा usbnet *, u8, u16, u16, u16, व्योम *);

	अगर (!in_pm) अणु
		fnr = ax88179_पढ़ो_cmd;
		fnw = ax88179_ग_लिखो_cmd;
	पूर्ण अन्यथा अणु
		fnr = ax88179_पढ़ो_cmd_nopm;
		fnw = ax88179_ग_लिखो_cmd_nopm;
	पूर्ण

	अगर (fnr(dev, AX_ACCESS_EEPROM, 0x43, 1, 2, &पंचांगp16) < 0)
		वापस 0;

	अगर ((पंचांगp16 == 0xFFFF) || (!(पंचांगp16 & 0x0100)))
		वापस 0;

	/* Enable Auto Detach bit */
	पंचांगp8 = 0;
	fnr(dev, AX_ACCESS_MAC, AX_CLK_SELECT, 1, 1, &पंचांगp8);
	पंचांगp8 |= AX_CLK_SELECT_ULR;
	fnw(dev, AX_ACCESS_MAC, AX_CLK_SELECT, 1, 1, &पंचांगp8);

	fnr(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, &पंचांगp16);
	पंचांगp16 |= AX_PHYPWR_RSTCTL_AT;
	fnw(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, &पंचांगp16);

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	u16 पंचांगp16;
	u8 पंचांगp8;

	usbnet_link_change(dev, 0, 0);

	/* Power up ethernet PHY */
	पंचांगp16 = 0;
	ax88179_ग_लिखो_cmd_nopm(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL,
			       2, 2, &पंचांगp16);
	udelay(1000);

	पंचांगp16 = AX_PHYPWR_RSTCTL_IPRL;
	ax88179_ग_लिखो_cmd_nopm(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL,
			       2, 2, &पंचांगp16);
	msleep(200);

	/* Ethernet PHY Auto Detach*/
	ax88179_स्वतः_detach(dev, 1);

	/* Enable घड़ी */
	ax88179_पढ़ो_cmd_nopm(dev, AX_ACCESS_MAC,  AX_CLK_SELECT, 1, 1, &पंचांगp8);
	पंचांगp8 |= AX_CLK_SELECT_ACS | AX_CLK_SELECT_BCS;
	ax88179_ग_लिखो_cmd_nopm(dev, AX_ACCESS_MAC, AX_CLK_SELECT, 1, 1, &पंचांगp8);
	msleep(100);

	/* Configure RX control रेजिस्टर => start operation */
	पंचांगp16 = AX_RX_CTL_DROPCRCERR | AX_RX_CTL_IPE | AX_RX_CTL_START |
		AX_RX_CTL_AP | AX_RX_CTL_AMALL | AX_RX_CTL_AB;
	ax88179_ग_लिखो_cmd_nopm(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2, &पंचांगp16);

	वापस usbnet_resume(पूर्णांकf);
पूर्ण

अटल व्योम
ax88179_get_wol(काष्ठा net_device *net, काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u8 opt;

	अगर (ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_MONITOR_MOD,
			     1, 1, &opt) < 0) अणु
		wolinfo->supported = 0;
		wolinfo->wolopts = 0;
		वापस;
	पूर्ण

	wolinfo->supported = WAKE_PHY | WAKE_MAGIC;
	wolinfo->wolopts = 0;
	अगर (opt & AX_MONITOR_MODE_RWLC)
		wolinfo->wolopts |= WAKE_PHY;
	अगर (opt & AX_MONITOR_MODE_RWMP)
		wolinfo->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक
ax88179_set_wol(काष्ठा net_device *net, काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u8 opt = 0;

	अगर (wolinfo->wolopts & ~(WAKE_PHY | WAKE_MAGIC))
		वापस -EINVAL;

	अगर (wolinfo->wolopts & WAKE_PHY)
		opt |= AX_MONITOR_MODE_RWLC;
	अगर (wolinfo->wolopts & WAKE_MAGIC)
		opt |= AX_MONITOR_MODE_RWMP;

	अगर (ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_MONITOR_MOD,
			      1, 1, &opt) < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_get_eeprom_len(काष्ठा net_device *net)
अणु
	वापस AX_EEPROM_LEN;
पूर्ण

अटल पूर्णांक
ax88179_get_eeprom(काष्ठा net_device *net, काष्ठा ethtool_eeprom *eeprom,
		   u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u16 *eeprom_buff;
	पूर्णांक first_word, last_word;
	पूर्णांक i, ret;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	eeprom->magic = AX88179_EEPROM_MAGIC;

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;
	eeprom_buff = kदो_स्मृति_array(last_word - first_word + 1, माप(u16),
				    GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	/* ax88179/178A वापसs 2 bytes from eeprom on पढ़ो */
	क्रम (i = first_word; i <= last_word; i++) अणु
		ret = __ax88179_पढ़ो_cmd(dev, AX_ACCESS_EEPROM, i, 1, 2,
					 &eeprom_buff[i - first_word],
					 0);
		अगर (ret < 0) अणु
			kमुक्त(eeprom_buff);
			वापस -EIO;
		पूर्ण
	पूर्ण

	स_नकल(data, (u8 *)eeprom_buff + (eeprom->offset & 1), eeprom->len);
	kमुक्त(eeprom_buff);
	वापस 0;
पूर्ण

अटल पूर्णांक
ax88179_set_eeprom(काष्ठा net_device *net, काष्ठा ethtool_eeprom *eeprom,
		   u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u16 *eeprom_buff;
	पूर्णांक first_word;
	पूर्णांक last_word;
	पूर्णांक ret;
	पूर्णांक i;

	netdev_dbg(net, "write EEPROM len %d, offset %d, magic 0x%x\n",
		   eeprom->len, eeprom->offset, eeprom->magic);

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	अगर (eeprom->magic != AX88179_EEPROM_MAGIC)
		वापस -EINVAL;

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;

	eeprom_buff = kदो_स्मृति_array(last_word - first_word + 1, माप(u16),
				    GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	/* align data to 16 bit boundaries, पढ़ो the missing data from
	   the EEPROM */
	अगर (eeprom->offset & 1) अणु
		ret = ax88179_पढ़ो_cmd(dev, AX_ACCESS_EEPROM, first_word, 1, 2,
				       &eeprom_buff[0]);
		अगर (ret < 0) अणु
			netdev_err(net, "Failed to read EEPROM at offset 0x%02x.\n", first_word);
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	अगर ((eeprom->offset + eeprom->len) & 1) अणु
		ret = ax88179_पढ़ो_cmd(dev, AX_ACCESS_EEPROM, last_word, 1, 2,
				       &eeprom_buff[last_word - first_word]);
		अगर (ret < 0) अणु
			netdev_err(net, "Failed to read EEPROM at offset 0x%02x.\n", last_word);
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	स_नकल((u8 *)eeprom_buff + (eeprom->offset & 1), data, eeprom->len);

	क्रम (i = first_word; i <= last_word; i++) अणु
		netdev_dbg(net, "write to EEPROM at offset 0x%02x, data 0x%04x\n",
			   i, eeprom_buff[i - first_word]);
		ret = ax88179_ग_लिखो_cmd(dev, AX_ACCESS_EEPROM, i, 1, 2,
					&eeprom_buff[i - first_word]);
		अगर (ret < 0) अणु
			netdev_err(net, "Failed to write EEPROM at offset 0x%02x.\n", i);
			जाओ मुक्त;
		पूर्ण
		msleep(20);
	पूर्ण

	/* reload EEPROM data */
	ret = ax88179_ग_लिखो_cmd(dev, AX_RELOAD_EEPROM_EFUSE, 0x0000, 0, 0, शून्य);
	अगर (ret < 0) अणु
		netdev_err(net, "Failed to reload EEPROM data\n");
		जाओ मुक्त;
	पूर्ण

	ret = 0;
मुक्त:
	kमुक्त(eeprom_buff);
	वापस ret;
पूर्ण

अटल पूर्णांक ax88179_get_link_ksettings(काष्ठा net_device *net,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	mii_ethtool_get_link_ksettings(&dev->mii, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_set_link_ksettings(काष्ठा net_device *net,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	वापस mii_ethtool_set_link_ksettings(&dev->mii, cmd);
पूर्ण

अटल पूर्णांक
ax88179_ethtool_get_eee(काष्ठा usbnet *dev, काष्ठा ethtool_eee *data)
अणु
	पूर्णांक val;

	/* Get Supported EEE */
	val = ax88179_phy_पढ़ो_mmd_indirect(dev, MDIO_PCS_EEE_ABLE,
					    MDIO_MMD_PCS);
	अगर (val < 0)
		वापस val;
	data->supported = mmd_eee_cap_to_ethtool_sup_t(val);

	/* Get advertisement EEE */
	val = ax88179_phy_पढ़ो_mmd_indirect(dev, MDIO_AN_EEE_ADV,
					    MDIO_MMD_AN);
	अगर (val < 0)
		वापस val;
	data->advertised = mmd_eee_adv_to_ethtool_adv_t(val);

	/* Get LP advertisement EEE */
	val = ax88179_phy_पढ़ो_mmd_indirect(dev, MDIO_AN_EEE_LPABLE,
					    MDIO_MMD_AN);
	अगर (val < 0)
		वापस val;
	data->lp_advertised = mmd_eee_adv_to_ethtool_adv_t(val);

	वापस 0;
पूर्ण

अटल पूर्णांक
ax88179_ethtool_set_eee(काष्ठा usbnet *dev, काष्ठा ethtool_eee *data)
अणु
	u16 पंचांगp16 = ethtool_adv_to_mmd_eee_adv_t(data->advertised);

	वापस ax88179_phy_ग_लिखो_mmd_indirect(dev, MDIO_AN_EEE_ADV,
					      MDIO_MMD_AN, पंचांगp16);
पूर्ण

अटल पूर्णांक ax88179_chk_eee(काष्ठा usbnet *dev)
अणु
	काष्ठा ethtool_cmd ecmd = अणु .cmd = ETHTOOL_GSET पूर्ण;
	काष्ठा ax88179_data *priv = (काष्ठा ax88179_data *)dev->data;

	mii_ethtool_gset(&dev->mii, &ecmd);

	अगर (ecmd.duplex & DUPLEX_FULL) अणु
		पूर्णांक eee_lp, eee_cap, eee_adv;
		u32 lp, cap, adv, supported = 0;

		eee_cap = ax88179_phy_पढ़ो_mmd_indirect(dev,
							MDIO_PCS_EEE_ABLE,
							MDIO_MMD_PCS);
		अगर (eee_cap < 0) अणु
			priv->eee_active = 0;
			वापस false;
		पूर्ण

		cap = mmd_eee_cap_to_ethtool_sup_t(eee_cap);
		अगर (!cap) अणु
			priv->eee_active = 0;
			वापस false;
		पूर्ण

		eee_lp = ax88179_phy_पढ़ो_mmd_indirect(dev,
						       MDIO_AN_EEE_LPABLE,
						       MDIO_MMD_AN);
		अगर (eee_lp < 0) अणु
			priv->eee_active = 0;
			वापस false;
		पूर्ण

		eee_adv = ax88179_phy_पढ़ो_mmd_indirect(dev,
							MDIO_AN_EEE_ADV,
							MDIO_MMD_AN);

		अगर (eee_adv < 0) अणु
			priv->eee_active = 0;
			वापस false;
		पूर्ण

		adv = mmd_eee_adv_to_ethtool_adv_t(eee_adv);
		lp = mmd_eee_adv_to_ethtool_adv_t(eee_lp);
		supported = (ecmd.speed == SPEED_1000) ?
			     SUPPORTED_1000baseT_Full :
			     SUPPORTED_100baseT_Full;

		अगर (!(lp & adv & supported)) अणु
			priv->eee_active = 0;
			वापस false;
		पूर्ण

		priv->eee_active = 1;
		वापस true;
	पूर्ण

	priv->eee_active = 0;
	वापस false;
पूर्ण

अटल व्योम ax88179_disable_eee(काष्ठा usbnet *dev)
अणु
	u16 पंचांगp16;

	पंचांगp16 = GMII_PHY_PGSEL_PAGE3;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &पंचांगp16);

	पंचांगp16 = 0x3246;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  MII_PHYADDR, 2, &पंचांगp16);

	पंचांगp16 = GMII_PHY_PGSEL_PAGE0;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &पंचांगp16);
पूर्ण

अटल व्योम ax88179_enable_eee(काष्ठा usbnet *dev)
अणु
	u16 पंचांगp16;

	पंचांगp16 = GMII_PHY_PGSEL_PAGE3;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &पंचांगp16);

	पंचांगp16 = 0x3247;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  MII_PHYADDR, 2, &पंचांगp16);

	पंचांगp16 = GMII_PHY_PGSEL_PAGE5;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &पंचांगp16);

	पंचांगp16 = 0x0680;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  MII_BMSR, 2, &पंचांगp16);

	पंचांगp16 = GMII_PHY_PGSEL_PAGE0;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &पंचांगp16);
पूर्ण

अटल पूर्णांक ax88179_get_eee(काष्ठा net_device *net, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा ax88179_data *priv = (काष्ठा ax88179_data *)dev->data;

	edata->eee_enabled = priv->eee_enabled;
	edata->eee_active = priv->eee_active;

	वापस ax88179_ethtool_get_eee(dev, edata);
पूर्ण

अटल पूर्णांक ax88179_set_eee(काष्ठा net_device *net, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा ax88179_data *priv = (काष्ठा ax88179_data *)dev->data;
	पूर्णांक ret;

	priv->eee_enabled = edata->eee_enabled;
	अगर (!priv->eee_enabled) अणु
		ax88179_disable_eee(dev);
	पूर्ण अन्यथा अणु
		priv->eee_enabled = ax88179_chk_eee(dev);
		अगर (!priv->eee_enabled)
			वापस -EOPNOTSUPP;

		ax88179_enable_eee(dev);
	पूर्ण

	ret = ax88179_ethtool_set_eee(dev, edata);
	अगर (ret)
		वापस ret;

	mii_nway_restart(&dev->mii);

	usbnet_link_change(dev, 0, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक ax88179_ioctl(काष्ठा net_device *net, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	वापस generic_mii_ioctl(&dev->mii, अगर_mii(rq), cmd, शून्य);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ax88179_ethtool_ops = अणु
	.get_link		= ethtool_op_get_link,
	.get_msglevel		= usbnet_get_msglevel,
	.set_msglevel		= usbnet_set_msglevel,
	.get_wol		= ax88179_get_wol,
	.set_wol		= ax88179_set_wol,
	.get_eeprom_len		= ax88179_get_eeprom_len,
	.get_eeprom		= ax88179_get_eeprom,
	.set_eeprom		= ax88179_set_eeprom,
	.get_eee		= ax88179_get_eee,
	.set_eee		= ax88179_set_eee,
	.nway_reset		= usbnet_nway_reset,
	.get_link_ksettings	= ax88179_get_link_ksettings,
	.set_link_ksettings	= ax88179_set_link_ksettings,
	.get_ts_info		= ethtool_op_get_ts_info,
पूर्ण;

अटल व्योम ax88179_set_multicast(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा ax88179_data *data = (काष्ठा ax88179_data *)dev->data;
	u8 *m_filter = ((u8 *)dev->data) + 12;

	data->rxctl = (AX_RX_CTL_START | AX_RX_CTL_AB | AX_RX_CTL_IPE);

	अगर (net->flags & IFF_PROMISC) अणु
		data->rxctl |= AX_RX_CTL_PRO;
	पूर्ण अन्यथा अगर (net->flags & IFF_ALLMULTI ||
		   netdev_mc_count(net) > AX_MAX_MCAST) अणु
		data->rxctl |= AX_RX_CTL_AMALL;
	पूर्ण अन्यथा अगर (netdev_mc_empty(net)) अणु
		/* just broadcast and directed */
	पूर्ण अन्यथा अणु
		/* We use the 20 byte dev->data क्रम our 8 byte filter buffer
		 * to aव्योम allocating memory that is tricky to मुक्त later
		 */
		u32 crc_bits;
		काष्ठा netdev_hw_addr *ha;

		स_रखो(m_filter, 0, AX_MCAST_FLTSIZE);

		netdev_क्रम_each_mc_addr(ha, net) अणु
			crc_bits = ether_crc(ETH_ALEN, ha->addr) >> 26;
			*(m_filter + (crc_bits >> 3)) |= (1 << (crc_bits & 7));
		पूर्ण

		ax88179_ग_लिखो_cmd_async(dev, AX_ACCESS_MAC, AX_MULFLTARY,
					AX_MCAST_FLTSIZE, AX_MCAST_FLTSIZE,
					m_filter);

		data->rxctl |= AX_RX_CTL_AM;
	पूर्ण

	ax88179_ग_लिखो_cmd_async(dev, AX_ACCESS_MAC, AX_RX_CTL,
				2, 2, &data->rxctl);
पूर्ण

अटल पूर्णांक
ax88179_set_features(काष्ठा net_device *net, netdev_features_t features)
अणु
	u8 पंचांगp;
	काष्ठा usbnet *dev = netdev_priv(net);
	netdev_features_t changed = net->features ^ features;

	अगर (changed & NETIF_F_IP_CSUM) अणु
		ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTL, 1, 1, &पंचांगp);
		पंचांगp ^= AX_TXCOE_TCP | AX_TXCOE_UDP;
		ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTL, 1, 1, &पंचांगp);
	पूर्ण

	अगर (changed & NETIF_F_IPV6_CSUM) अणु
		ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTL, 1, 1, &पंचांगp);
		पंचांगp ^= AX_TXCOE_TCPV6 | AX_TXCOE_UDPV6;
		ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTL, 1, 1, &पंचांगp);
	पूर्ण

	अगर (changed & NETIF_F_RXCSUM) अणु
		ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_RXCOE_CTL, 1, 1, &पंचांगp);
		पंचांगp ^= AX_RXCOE_IP | AX_RXCOE_TCP | AX_RXCOE_UDP |
		       AX_RXCOE_TCPV6 | AX_RXCOE_UDPV6;
		ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RXCOE_CTL, 1, 1, &पंचांगp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_change_mtu(काष्ठा net_device *net, पूर्णांक new_mtu)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u16 पंचांगp16;

	net->mtu = new_mtu;
	dev->hard_mtu = net->mtu + net->hard_header_len;

	अगर (net->mtu > 1500) अणु
		ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
				 2, 2, &पंचांगp16);
		पंचांगp16 |= AX_MEDIUM_JUMBO_EN;
		ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
				  2, 2, &पंचांगp16);
	पूर्ण अन्यथा अणु
		ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
				 2, 2, &पंचांगp16);
		पंचांगp16 &= ~AX_MEDIUM_JUMBO_EN;
		ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
				  2, 2, &पंचांगp16);
	पूर्ण

	/* max qlen depend on hard_mtu and rx_urb_size */
	usbnet_update_max_qlen(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_set_mac_addr(काष्ठा net_device *net, व्योम *p)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा sockaddr *addr = p;
	पूर्णांक ret;

	अगर (netअगर_running(net))
		वापस -EBUSY;
	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(net->dev_addr, addr->sa_data, ETH_ALEN);

	/* Set the MAC address */
	ret = ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_NODE_ID, ETH_ALEN,
				 ETH_ALEN, net->dev_addr);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ax88179_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_change_mtu		= ax88179_change_mtu,
	.nकरो_set_mac_address	= ax88179_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= ax88179_ioctl,
	.nकरो_set_rx_mode	= ax88179_set_multicast,
	.nकरो_set_features	= ax88179_set_features,
पूर्ण;

अटल पूर्णांक ax88179_check_eeprom(काष्ठा usbnet *dev)
अणु
	u8 i, buf, eeprom[20];
	u16 csum, delay = HZ / 10;
	अचिन्हित दीर्घ jसमयout;

	/* Read EEPROM content */
	क्रम (i = 0; i < 6; i++) अणु
		buf = i;
		अगर (ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_SROM_ADDR,
				      1, 1, &buf) < 0)
			वापस -EINVAL;

		buf = EEP_RD;
		अगर (ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_SROM_CMD,
				      1, 1, &buf) < 0)
			वापस -EINVAL;

		jसमयout = jअगरfies + delay;
		करो अणु
			ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_SROM_CMD,
					 1, 1, &buf);

			अगर (समय_after(jअगरfies, jसमयout))
				वापस -EINVAL;

		पूर्ण जबतक (buf & EEP_BUSY);

		__ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_SROM_DATA_LOW,
				   2, 2, &eeprom[i * 2], 0);

		अगर ((i == 0) && (eeprom[0] == 0xFF))
			वापस -EINVAL;
	पूर्ण

	csum = eeprom[6] + eeprom[7] + eeprom[8] + eeprom[9];
	csum = (csum >> 8) + (csum & 0xff);
	अगर ((csum + eeprom[10]) != 0xff)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_check_efuse(काष्ठा usbnet *dev, u16 *ledmode)
अणु
	u8	i;
	u8	efuse[64];
	u16	csum = 0;

	अगर (ax88179_पढ़ो_cmd(dev, AX_ACCESS_EFUS, 0, 64, 64, efuse) < 0)
		वापस -EINVAL;

	अगर (*efuse == 0xFF)
		वापस -EINVAL;

	क्रम (i = 0; i < 64; i++)
		csum = csum + efuse[i];

	जबतक (csum > 255)
		csum = (csum & 0x00FF) + ((csum >> 8) & 0x00FF);

	अगर (csum != 0xFF)
		वापस -EINVAL;

	*ledmode = (efuse[51] << 8) | efuse[52];

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_convert_old_led(काष्ठा usbnet *dev, u16 *ledvalue)
अणु
	u16 led;

	/* Loaded the old eFuse LED Mode */
	अगर (ax88179_पढ़ो_cmd(dev, AX_ACCESS_EEPROM, 0x3C, 1, 2, &led) < 0)
		वापस -EINVAL;

	led >>= 8;
	चयन (led) अणु
	हाल 0xFF:
		led = LED0_ACTIVE | LED1_LINK_10 | LED1_LINK_100 |
		      LED1_LINK_1000 | LED2_ACTIVE | LED2_LINK_10 |
		      LED2_LINK_100 | LED2_LINK_1000 | LED_VALID;
		अवरोध;
	हाल 0xFE:
		led = LED0_ACTIVE | LED1_LINK_1000 | LED2_LINK_100 | LED_VALID;
		अवरोध;
	हाल 0xFD:
		led = LED0_ACTIVE | LED1_LINK_1000 | LED2_LINK_100 |
		      LED2_LINK_10 | LED_VALID;
		अवरोध;
	हाल 0xFC:
		led = LED0_ACTIVE | LED1_ACTIVE | LED1_LINK_1000 | LED2_ACTIVE |
		      LED2_LINK_100 | LED2_LINK_10 | LED_VALID;
		अवरोध;
	शेष:
		led = LED0_ACTIVE | LED1_LINK_10 | LED1_LINK_100 |
		      LED1_LINK_1000 | LED2_ACTIVE | LED2_LINK_10 |
		      LED2_LINK_100 | LED2_LINK_1000 | LED_VALID;
		अवरोध;
	पूर्ण

	*ledvalue = led;

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_led_setting(काष्ठा usbnet *dev)
अणु
	u8 ledfd, value = 0;
	u16 पंचांगp, ledact, ledlink, ledvalue = 0, delay = HZ / 10;
	अचिन्हित दीर्घ jसमयout;

	/* Check AX88179 version. UA1 or UA2*/
	ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, GENERAL_STATUS, 1, 1, &value);

	अगर (!(value & AX_SECLD)) अणु	/* UA1 */
		value = AX_GPIO_CTRL_GPIO3EN | AX_GPIO_CTRL_GPIO2EN |
			AX_GPIO_CTRL_GPIO1EN;
		अगर (ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_GPIO_CTRL,
				      1, 1, &value) < 0)
			वापस -EINVAL;
	पूर्ण

	/* Check EEPROM */
	अगर (!ax88179_check_eeprom(dev)) अणु
		value = 0x42;
		अगर (ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_SROM_ADDR,
				      1, 1, &value) < 0)
			वापस -EINVAL;

		value = EEP_RD;
		अगर (ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_SROM_CMD,
				      1, 1, &value) < 0)
			वापस -EINVAL;

		jसमयout = jअगरfies + delay;
		करो अणु
			ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_SROM_CMD,
					 1, 1, &value);

			अगर (समय_after(jअगरfies, jसमयout))
				वापस -EINVAL;

		पूर्ण जबतक (value & EEP_BUSY);

		ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_SROM_DATA_HIGH,
				 1, 1, &value);
		ledvalue = (value << 8);

		ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_SROM_DATA_LOW,
				 1, 1, &value);
		ledvalue |= value;

		/* load पूर्णांकernal ROM क्रम defaule setting */
		अगर ((ledvalue == 0xFFFF) || ((ledvalue & LED_VALID) == 0))
			ax88179_convert_old_led(dev, &ledvalue);

	पूर्ण अन्यथा अगर (!ax88179_check_efuse(dev, &ledvalue)) अणु
		अगर ((ledvalue == 0xFFFF) || ((ledvalue & LED_VALID) == 0))
			ax88179_convert_old_led(dev, &ledvalue);
	पूर्ण अन्यथा अणु
		ax88179_convert_old_led(dev, &ledvalue);
	पूर्ण

	पंचांगp = GMII_PHY_PGSEL_EXT;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &पंचांगp);

	पंचांगp = 0x2c;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHYPAGE, 2, &पंचांगp);

	ax88179_पढ़ो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			 GMII_LED_ACT, 2, &ledact);

	ax88179_पढ़ो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			 GMII_LED_LINK, 2, &ledlink);

	ledact &= GMII_LED_ACTIVE_MASK;
	ledlink &= GMII_LED_LINK_MASK;

	अगर (ledvalue & LED0_ACTIVE)
		ledact |= GMII_LED0_ACTIVE;

	अगर (ledvalue & LED1_ACTIVE)
		ledact |= GMII_LED1_ACTIVE;

	अगर (ledvalue & LED2_ACTIVE)
		ledact |= GMII_LED2_ACTIVE;

	अगर (ledvalue & LED0_LINK_10)
		ledlink |= GMII_LED0_LINK_10;

	अगर (ledvalue & LED1_LINK_10)
		ledlink |= GMII_LED1_LINK_10;

	अगर (ledvalue & LED2_LINK_10)
		ledlink |= GMII_LED2_LINK_10;

	अगर (ledvalue & LED0_LINK_100)
		ledlink |= GMII_LED0_LINK_100;

	अगर (ledvalue & LED1_LINK_100)
		ledlink |= GMII_LED1_LINK_100;

	अगर (ledvalue & LED2_LINK_100)
		ledlink |= GMII_LED2_LINK_100;

	अगर (ledvalue & LED0_LINK_1000)
		ledlink |= GMII_LED0_LINK_1000;

	अगर (ledvalue & LED1_LINK_1000)
		ledlink |= GMII_LED1_LINK_1000;

	अगर (ledvalue & LED2_LINK_1000)
		ledlink |= GMII_LED2_LINK_1000;

	पंचांगp = ledact;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_LED_ACT, 2, &पंचांगp);

	पंचांगp = ledlink;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_LED_LINK, 2, &पंचांगp);

	पंचांगp = GMII_PHY_PGSEL_PAGE0;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &पंचांगp);

	/* LED full duplex setting */
	ledfd = 0;
	अगर (ledvalue & LED0_FD)
		ledfd |= 0x01;
	अन्यथा अगर ((ledvalue & LED0_USB3_MASK) == 0)
		ledfd |= 0x02;

	अगर (ledvalue & LED1_FD)
		ledfd |= 0x04;
	अन्यथा अगर ((ledvalue & LED1_USB3_MASK) == 0)
		ledfd |= 0x08;

	अगर (ledvalue & LED2_FD)
		ledfd |= 0x10;
	अन्यथा अगर ((ledvalue & LED2_USB3_MASK) == 0)
		ledfd |= 0x20;

	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_LEDCTRL, 1, 1, &ledfd);

	वापस 0;
पूर्ण

अटल व्योम ax88179_get_mac_addr(काष्ठा usbnet *dev)
अणु
	u8 mac[ETH_ALEN];

	स_रखो(mac, 0, माप(mac));

	/* Maybe the boot loader passed the MAC address via device tree */
	अगर (!eth_platक्रमm_get_mac_address(&dev->udev->dev, mac)) अणु
		netअगर_dbg(dev, अगरup, dev->net,
			  "MAC address read from device tree");
	पूर्ण अन्यथा अणु
		ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_NODE_ID, ETH_ALEN,
				 ETH_ALEN, mac);
		netअगर_dbg(dev, अगरup, dev->net,
			  "MAC address read from ASIX chip");
	पूर्ण

	अगर (is_valid_ether_addr(mac)) अणु
		स_नकल(dev->net->dev_addr, mac, ETH_ALEN);
	पूर्ण अन्यथा अणु
		netdev_info(dev->net, "invalid MAC address, using random\n");
		eth_hw_addr_अक्रमom(dev->net);
	पूर्ण

	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_NODE_ID, ETH_ALEN, ETH_ALEN,
			  dev->net->dev_addr);
पूर्ण

अटल पूर्णांक ax88179_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	u8 buf[5];
	u16 *पंचांगp16;
	u8 *पंचांगp;
	काष्ठा ax88179_data *ax179_data = (काष्ठा ax88179_data *)dev->data;
	काष्ठा ethtool_eee eee_data;

	usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);

	पंचांगp16 = (u16 *)buf;
	पंचांगp = (u8 *)buf;

	स_रखो(ax179_data, 0, माप(*ax179_data));

	/* Power up ethernet PHY */
	*पंचांगp16 = 0;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, पंचांगp16);
	*पंचांगp16 = AX_PHYPWR_RSTCTL_IPRL;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, पंचांगp16);
	msleep(200);

	*पंचांगp = AX_CLK_SELECT_ACS | AX_CLK_SELECT_BCS;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_CLK_SELECT, 1, 1, पंचांगp);
	msleep(100);

	/* Read MAC address from DTB or asix chip */
	ax88179_get_mac_addr(dev);
	स_नकल(dev->net->perm_addr, dev->net->dev_addr, ETH_ALEN);

	/* RX bulk configuration */
	स_नकल(पंचांगp, &AX88179_BULKIN_SIZE[0], 5);
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RX_BULKIN_QCTRL, 5, 5, पंचांगp);

	dev->rx_urb_size = 1024 * 20;

	*पंचांगp = 0x34;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_PAUSE_WATERLVL_LOW, 1, 1, पंचांगp);

	*पंचांगp = 0x52;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_PAUSE_WATERLVL_HIGH,
			  1, 1, पंचांगp);

	dev->net->netdev_ops = &ax88179_netdev_ops;
	dev->net->ethtool_ops = &ax88179_ethtool_ops;
	dev->net->needed_headroom = 8;
	dev->net->max_mtu = 4088;

	/* Initialize MII काष्ठाure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_पढ़ो = ax88179_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = ax88179_mdio_ग_लिखो;
	dev->mii.phy_id_mask = 0xff;
	dev->mii.reg_num_mask = 0xff;
	dev->mii.phy_id = 0x03;
	dev->mii.supports_gmii = 1;

	dev->net->features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			      NETIF_F_RXCSUM;

	dev->net->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				 NETIF_F_RXCSUM;

	/* Enable checksum offload */
	*पंचांगp = AX_RXCOE_IP | AX_RXCOE_TCP | AX_RXCOE_UDP |
	       AX_RXCOE_TCPV6 | AX_RXCOE_UDPV6;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RXCOE_CTL, 1, 1, पंचांगp);

	*पंचांगp = AX_TXCOE_IP | AX_TXCOE_TCP | AX_TXCOE_UDP |
	       AX_TXCOE_TCPV6 | AX_TXCOE_UDPV6;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTL, 1, 1, पंचांगp);

	/* Configure RX control रेजिस्टर => start operation */
	*पंचांगp16 = AX_RX_CTL_DROPCRCERR | AX_RX_CTL_IPE | AX_RX_CTL_START |
		 AX_RX_CTL_AP | AX_RX_CTL_AMALL | AX_RX_CTL_AB;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2, पंचांगp16);

	*पंचांगp = AX_MONITOR_MODE_PMETYPE | AX_MONITOR_MODE_PMEPOL |
	       AX_MONITOR_MODE_RWMP;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_MONITOR_MOD, 1, 1, पंचांगp);

	/* Configure शेष medium type => giga */
	*पंचांगp16 = AX_MEDIUM_RECEIVE_EN | AX_MEDIUM_TXFLOW_CTRLEN |
		 AX_MEDIUM_RXFLOW_CTRLEN | AX_MEDIUM_FULL_DUPLEX |
		 AX_MEDIUM_GIGAMODE;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, पंचांगp16);

	ax88179_led_setting(dev);

	ax179_data->eee_enabled = 0;
	ax179_data->eee_active = 0;

	ax88179_disable_eee(dev);

	ax88179_ethtool_get_eee(dev, &eee_data);
	eee_data.advertised = 0;
	ax88179_ethtool_set_eee(dev, &eee_data);

	/* Restart स्वतःneg */
	mii_nway_restart(&dev->mii);

	usbnet_link_change(dev, 0, 0);

	वापस 0;
पूर्ण

अटल व्योम ax88179_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	u16 पंचांगp16;

	/* Configure RX control रेजिस्टर => stop operation */
	पंचांगp16 = AX_RX_CTL_STOP;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2, &पंचांगp16);

	पंचांगp16 = 0;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_CLK_SELECT, 1, 1, &पंचांगp16);

	/* Power करोwn ethernet PHY */
	पंचांगp16 = 0;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, &पंचांगp16);
पूर्ण

अटल व्योम
ax88179_rx_checksum(काष्ठा sk_buff *skb, u32 *pkt_hdr)
अणु
	skb->ip_summed = CHECKSUM_NONE;

	/* checksum error bit is set */
	अगर ((*pkt_hdr & AX_RXHDR_L3CSUM_ERR) ||
	    (*pkt_hdr & AX_RXHDR_L4CSUM_ERR))
		वापस;

	/* It must be a TCP or UDP packet with a valid checksum */
	अगर (((*pkt_hdr & AX_RXHDR_L4_TYPE_MASK) == AX_RXHDR_L4_TYPE_TCP) ||
	    ((*pkt_hdr & AX_RXHDR_L4_TYPE_MASK) == AX_RXHDR_L4_TYPE_UDP))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

अटल पूर्णांक ax88179_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *ax_skb;
	पूर्णांक pkt_cnt;
	u32 rx_hdr;
	u16 hdr_off;
	u32 *pkt_hdr;

	/* This check is no दीर्घer करोne by usbnet */
	अगर (skb->len < dev->net->hard_header_len)
		वापस 0;

	skb_trim(skb, skb->len - 4);
	rx_hdr = get_unaligned_le32(skb_tail_poपूर्णांकer(skb));

	pkt_cnt = (u16)rx_hdr;
	hdr_off = (u16)(rx_hdr >> 16);
	pkt_hdr = (u32 *)(skb->data + hdr_off);

	जबतक (pkt_cnt--) अणु
		u16 pkt_len;

		le32_to_cpus(pkt_hdr);
		pkt_len = (*pkt_hdr >> 16) & 0x1fff;

		/* Check CRC or runt packet */
		अगर ((*pkt_hdr & AX_RXHDR_CRC_ERR) ||
		    (*pkt_hdr & AX_RXHDR_DROP_ERR)) अणु
			skb_pull(skb, (pkt_len + 7) & 0xFFF8);
			pkt_hdr++;
			जारी;
		पूर्ण

		अगर (pkt_cnt == 0) अणु
			skb->len = pkt_len;
			/* Skip IP alignment pseuकरो header */
			skb_pull(skb, 2);
			skb_set_tail_poपूर्णांकer(skb, skb->len);
			skb->truesize = pkt_len + माप(काष्ठा sk_buff);
			ax88179_rx_checksum(skb, pkt_hdr);
			वापस 1;
		पूर्ण

		ax_skb = skb_clone(skb, GFP_ATOMIC);
		अगर (ax_skb) अणु
			ax_skb->len = pkt_len;
			/* Skip IP alignment pseuकरो header */
			skb_pull(ax_skb, 2);
			skb_set_tail_poपूर्णांकer(ax_skb, ax_skb->len);
			ax_skb->truesize = pkt_len + माप(काष्ठा sk_buff);
			ax88179_rx_checksum(ax_skb, pkt_hdr);
			usbnet_skb_वापस(dev, ax_skb);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण

		skb_pull(skb, (pkt_len + 7) & 0xFFF8);
		pkt_hdr++;
	पूर्ण
	वापस 1;
पूर्ण

अटल काष्ठा sk_buff *
ax88179_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags)
अणु
	u32 tx_hdr1, tx_hdr2;
	पूर्णांक frame_size = dev->maxpacket;
	पूर्णांक mss = skb_shinfo(skb)->gso_size;
	पूर्णांक headroom;
	व्योम *ptr;

	tx_hdr1 = skb->len;
	tx_hdr2 = mss;
	अगर (((skb->len + 8) % frame_size) == 0)
		tx_hdr2 |= 0x80008000;	/* Enable padding */

	headroom = skb_headroom(skb) - 8;

	अगर ((skb_header_cloned(skb) || headroom < 0) &&
	    pskb_expand_head(skb, headroom < 0 ? 8 : 0, 0, GFP_ATOMIC)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	ptr = skb_push(skb, 8);
	put_unaligned_le32(tx_hdr1, ptr);
	put_unaligned_le32(tx_hdr2, ptr + 4);

	वापस skb;
पूर्ण

अटल पूर्णांक ax88179_link_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा ax88179_data *ax179_data = (काष्ठा ax88179_data *)dev->data;
	u8 पंचांगp[5], link_sts;
	u16 mode, पंचांगp16, delay = HZ / 10;
	u32 पंचांगp32 = 0x40000000;
	अचिन्हित दीर्घ jसमयout;

	jसमयout = jअगरfies + delay;
	जबतक (पंचांगp32 & 0x40000000) अणु
		mode = 0;
		ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2, &mode);
		ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2,
				  &ax179_data->rxctl);

		/*link up, check the usb device control TX FIFO full or empty*/
		ax88179_पढ़ो_cmd(dev, 0x81, 0x8c, 0, 4, &पंचांगp32);

		अगर (समय_after(jअगरfies, jसमयout))
			वापस 0;
	पूर्ण

	mode = AX_MEDIUM_RECEIVE_EN | AX_MEDIUM_TXFLOW_CTRLEN |
	       AX_MEDIUM_RXFLOW_CTRLEN;

	ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, PHYSICAL_LINK_STATUS,
			 1, 1, &link_sts);

	ax88179_पढ़ो_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			 GMII_PHY_PHYSR, 2, &पंचांगp16);

	अगर (!(पंचांगp16 & GMII_PHY_PHYSR_LINK)) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (GMII_PHY_PHYSR_GIGA == (पंचांगp16 & GMII_PHY_PHYSR_SMASK)) अणु
		mode |= AX_MEDIUM_GIGAMODE | AX_MEDIUM_EN_125MHZ;
		अगर (dev->net->mtu > 1500)
			mode |= AX_MEDIUM_JUMBO_EN;

		अगर (link_sts & AX_USB_SS)
			स_नकल(पंचांगp, &AX88179_BULKIN_SIZE[0], 5);
		अन्यथा अगर (link_sts & AX_USB_HS)
			स_नकल(पंचांगp, &AX88179_BULKIN_SIZE[1], 5);
		अन्यथा
			स_नकल(पंचांगp, &AX88179_BULKIN_SIZE[3], 5);
	पूर्ण अन्यथा अगर (GMII_PHY_PHYSR_100 == (पंचांगp16 & GMII_PHY_PHYSR_SMASK)) अणु
		mode |= AX_MEDIUM_PS;

		अगर (link_sts & (AX_USB_SS | AX_USB_HS))
			स_नकल(पंचांगp, &AX88179_BULKIN_SIZE[2], 5);
		अन्यथा
			स_नकल(पंचांगp, &AX88179_BULKIN_SIZE[3], 5);
	पूर्ण अन्यथा अणु
		स_नकल(पंचांगp, &AX88179_BULKIN_SIZE[3], 5);
	पूर्ण

	/* RX bulk configuration */
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RX_BULKIN_QCTRL, 5, 5, पंचांगp);

	dev->rx_urb_size = (1024 * (पंचांगp[3] + 2));

	अगर (पंचांगp16 & GMII_PHY_PHYSR_FULL)
		mode |= AX_MEDIUM_FULL_DUPLEX;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, &mode);

	ax179_data->eee_enabled = ax88179_chk_eee(dev);

	netअगर_carrier_on(dev->net);

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_reset(काष्ठा usbnet *dev)
अणु
	u8 buf[5];
	u16 *पंचांगp16;
	u8 *पंचांगp;
	काष्ठा ax88179_data *ax179_data = (काष्ठा ax88179_data *)dev->data;
	काष्ठा ethtool_eee eee_data;

	पंचांगp16 = (u16 *)buf;
	पंचांगp = (u8 *)buf;

	/* Power up ethernet PHY */
	*पंचांगp16 = 0;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, पंचांगp16);

	*पंचांगp16 = AX_PHYPWR_RSTCTL_IPRL;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, पंचांगp16);
	msleep(200);

	*पंचांगp = AX_CLK_SELECT_ACS | AX_CLK_SELECT_BCS;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_CLK_SELECT, 1, 1, पंचांगp);
	msleep(100);

	/* Ethernet PHY Auto Detach*/
	ax88179_स्वतः_detach(dev, 0);

	/* Read MAC address from DTB or asix chip */
	ax88179_get_mac_addr(dev);

	/* RX bulk configuration */
	स_नकल(पंचांगp, &AX88179_BULKIN_SIZE[0], 5);
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RX_BULKIN_QCTRL, 5, 5, पंचांगp);

	dev->rx_urb_size = 1024 * 20;

	*पंचांगp = 0x34;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_PAUSE_WATERLVL_LOW, 1, 1, पंचांगp);

	*पंचांगp = 0x52;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_PAUSE_WATERLVL_HIGH,
			  1, 1, पंचांगp);

	dev->net->features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			      NETIF_F_RXCSUM;

	dev->net->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				 NETIF_F_RXCSUM;

	/* Enable checksum offload */
	*पंचांगp = AX_RXCOE_IP | AX_RXCOE_TCP | AX_RXCOE_UDP |
	       AX_RXCOE_TCPV6 | AX_RXCOE_UDPV6;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RXCOE_CTL, 1, 1, पंचांगp);

	*पंचांगp = AX_TXCOE_IP | AX_TXCOE_TCP | AX_TXCOE_UDP |
	       AX_TXCOE_TCPV6 | AX_TXCOE_UDPV6;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTL, 1, 1, पंचांगp);

	/* Configure RX control रेजिस्टर => start operation */
	*पंचांगp16 = AX_RX_CTL_DROPCRCERR | AX_RX_CTL_IPE | AX_RX_CTL_START |
		 AX_RX_CTL_AP | AX_RX_CTL_AMALL | AX_RX_CTL_AB;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2, पंचांगp16);

	*पंचांगp = AX_MONITOR_MODE_PMETYPE | AX_MONITOR_MODE_PMEPOL |
	       AX_MONITOR_MODE_RWMP;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_MONITOR_MOD, 1, 1, पंचांगp);

	/* Configure शेष medium type => giga */
	*पंचांगp16 = AX_MEDIUM_RECEIVE_EN | AX_MEDIUM_TXFLOW_CTRLEN |
		 AX_MEDIUM_RXFLOW_CTRLEN | AX_MEDIUM_FULL_DUPLEX |
		 AX_MEDIUM_GIGAMODE;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, पंचांगp16);

	ax88179_led_setting(dev);

	ax179_data->eee_enabled = 0;
	ax179_data->eee_active = 0;

	ax88179_disable_eee(dev);

	ax88179_ethtool_get_eee(dev, &eee_data);
	eee_data.advertised = 0;
	ax88179_ethtool_set_eee(dev, &eee_data);

	/* Restart स्वतःneg */
	mii_nway_restart(&dev->mii);

	usbnet_link_change(dev, 0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ax88179_stop(काष्ठा usbnet *dev)
अणु
	u16 पंचांगp16;

	ax88179_पढ़ो_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			 2, 2, &पंचांगp16);
	पंचांगp16 &= ~AX_MEDIUM_RECEIVE_EN;
	ax88179_ग_लिखो_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, &पंचांगp16);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा driver_info ax88179_info = अणु
	.description = "ASIX AX88179 USB 3.0 Gigabit Ethernet",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset = ax88179_reset,
	.stop = ax88179_stop,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info ax88178a_info = अणु
	.description = "ASIX AX88178A USB 2.0 Gigabit Ethernet",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset = ax88179_reset,
	.stop = ax88179_stop,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info cypress_GX3_info = अणु
	.description = "Cypress GX3 SuperSpeed to Gigabit Ethernet Controller",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset = ax88179_reset,
	.stop = ax88179_stop,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info dlink_dub1312_info = अणु
	.description = "D-Link DUB-1312 USB 3.0 to Gigabit Ethernet Adapter",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset = ax88179_reset,
	.stop = ax88179_stop,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info sitecom_info = अणु
	.description = "Sitecom USB 3.0 to Gigabit Adapter",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset = ax88179_reset,
	.stop = ax88179_stop,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info samsung_info = अणु
	.description = "Samsung USB Ethernet Adapter",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset = ax88179_reset,
	.stop = ax88179_stop,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info lenovo_info = अणु
	.description = "Lenovo OneLinkDock Gigabit LAN",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset = ax88179_reset,
	.stop = ax88179_stop,
	.flags = FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info belkin_info = अणु
	.description = "Belkin USB Ethernet Adapter",
	.bind	= ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset	= ax88179_reset,
	.stop	= ax88179_stop,
	.flags	= FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info toshiba_info = अणु
	.description = "Toshiba USB Ethernet Adapter",
	.bind	= ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset	= ax88179_reset,
	.stop = ax88179_stop,
	.flags	= FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info mct_info = अणु
	.description = "MCT USB 3.0 Gigabit Ethernet Adapter",
	.bind	= ax88179_bind,
	.unbind	= ax88179_unbind,
	.status	= ax88179_status,
	.link_reset = ax88179_link_reset,
	.reset	= ax88179_reset,
	.stop	= ax88179_stop,
	.flags	= FLAG_ETHER | FLAG_FRAMING_AX,
	.rx_fixup = ax88179_rx_fixup,
	.tx_fixup = ax88179_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id products[] = अणु
अणु
	/* ASIX AX88179 10/100/1000 */
	USB_DEVICE(0x0b95, 0x1790),
	.driver_info = (अचिन्हित दीर्घ)&ax88179_info,
पूर्ण, अणु
	/* ASIX AX88178A 10/100/1000 */
	USB_DEVICE(0x0b95, 0x178a),
	.driver_info = (अचिन्हित दीर्घ)&ax88178a_info,
पूर्ण, अणु
	/* Cypress GX3 SuperSpeed to Gigabit Ethernet Bridge Controller */
	USB_DEVICE(0x04b4, 0x3610),
	.driver_info = (अचिन्हित दीर्घ)&cypress_GX3_info,
पूर्ण, अणु
	/* D-Link DUB-1312 USB 3.0 to Gigabit Ethernet Adapter */
	USB_DEVICE(0x2001, 0x4a00),
	.driver_info = (अचिन्हित दीर्घ)&dlink_dub1312_info,
पूर्ण, अणु
	/* Sitecom USB 3.0 to Gigabit Adapter */
	USB_DEVICE(0x0df6, 0x0072),
	.driver_info = (अचिन्हित दीर्घ)&sitecom_info,
पूर्ण, अणु
	/* Samsung USB Ethernet Adapter */
	USB_DEVICE(0x04e8, 0xa100),
	.driver_info = (अचिन्हित दीर्घ)&samsung_info,
पूर्ण, अणु
	/* Lenovo OneLinkDock Gigabit LAN */
	USB_DEVICE(0x17ef, 0x304b),
	.driver_info = (अचिन्हित दीर्घ)&lenovo_info,
पूर्ण, अणु
	/* Belkin B2B128 USB 3.0 Hub + Gigabit Ethernet Adapter */
	USB_DEVICE(0x050d, 0x0128),
	.driver_info = (अचिन्हित दीर्घ)&belkin_info,
पूर्ण, अणु
	/* Toshiba USB 3.0 GBit Ethernet Adapter */
	USB_DEVICE(0x0930, 0x0a13),
	.driver_info = (अचिन्हित दीर्घ)&toshiba_info,
पूर्ण, अणु
	/* Magic Control Technology U3-A9003 USB 3.0 Gigabit Ethernet Adapter */
	USB_DEVICE(0x0711, 0x0179),
	.driver_info = (अचिन्हित दीर्घ)&mct_info,
पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver ax88179_178a_driver = अणु
	.name =		"ax88179_178a",
	.id_table =	products,
	.probe =	usbnet_probe,
	.suspend =	ax88179_suspend,
	.resume =	ax88179_resume,
	.reset_resume =	ax88179_resume,
	.disconnect =	usbnet_disconnect,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(ax88179_178a_driver);

MODULE_DESCRIPTION("ASIX AX88179/178A based USB 3.0/2.0 Gigabit Ethernet Devices");
MODULE_LICENSE("GPL");
