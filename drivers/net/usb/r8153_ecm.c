<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/usb/r8152.h>

#घोषणा OCP_BASE		0xe86c

अटल पूर्णांक pla_पढ़ो_word(काष्ठा usbnet *dev, u16 index)
अणु
	u16 byen = BYTE_EN_WORD;
	u8 shअगरt = index & 2;
	__le32 पंचांगp;
	पूर्णांक ret;

	अगर (shअगरt)
		byen <<= shअगरt;

	index &= ~3;

	ret = usbnet_पढ़ो_cmd(dev, RTL8152_REQ_GET_REGS, RTL8152_REQT_READ, index,
			      MCU_TYPE_PLA | byen, &पंचांगp, माप(पंचांगp));
	अगर (ret < 0)
		जाओ out;

	ret = __le32_to_cpu(पंचांगp);
	ret >>= (shअगरt * 8);
	ret &= 0xffff;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक pla_ग_लिखो_word(काष्ठा usbnet *dev, u16 index, u32 data)
अणु
	u32 mask = 0xffff;
	u16 byen = BYTE_EN_WORD;
	u8 shअगरt = index & 2;
	__le32 पंचांगp;
	पूर्णांक ret;

	data &= mask;

	अगर (shअगरt) अणु
		byen <<= shअगरt;
		mask <<= (shअगरt * 8);
		data <<= (shअगरt * 8);
	पूर्ण

	index &= ~3;

	ret = usbnet_पढ़ो_cmd(dev, RTL8152_REQ_GET_REGS, RTL8152_REQT_READ, index,
			      MCU_TYPE_PLA | byen, &पंचांगp, माप(पंचांगp));

	अगर (ret < 0)
		जाओ out;

	data |= __le32_to_cpu(पंचांगp) & ~mask;
	पंचांगp = __cpu_to_le32(data);

	ret = usbnet_ग_लिखो_cmd(dev, RTL8152_REQ_SET_REGS, RTL8152_REQT_WRITE, index,
			       MCU_TYPE_PLA | byen, &पंचांगp, माप(पंचांगp));

out:
	वापस ret;
पूर्ण

अटल पूर्णांक r8153_ecm_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	पूर्णांक ret;

	ret = pla_ग_लिखो_word(dev, OCP_BASE, 0xa000);
	अगर (ret < 0)
		जाओ out;

	ret = pla_पढ़ो_word(dev, 0xb400 + reg * 2);

out:
	वापस ret;
पूर्ण

अटल व्योम r8153_ecm_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	पूर्णांक ret;

	ret = pla_ग_लिखो_word(dev, OCP_BASE, 0xa000);
	अगर (ret < 0)
		वापस;

	ret = pla_ग_लिखो_word(dev, 0xb400 + reg * 2, val);
पूर्ण

अटल पूर्णांक r8153_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक status;

	status = usbnet_cdc_bind(dev, पूर्णांकf);
	अगर (status < 0)
		वापस status;

	dev->mii.dev = dev->net;
	dev->mii.mdio_पढ़ो = r8153_ecm_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = r8153_ecm_mdio_ग_लिखो;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.supports_gmii = 1;

	वापस status;
पूर्ण

अटल स्थिर काष्ठा driver_info r8153_info = अणु
	.description =	"RTL8153 ECM Device",
	.flags =	FLAG_ETHER,
	.bind =		r8153_bind,
	.unbind =	usbnet_cdc_unbind,
	.status =	usbnet_cdc_status,
	.manage_घातer =	usbnet_manage_घातer,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id products[] = अणु
/* Realtek RTL8153 Based USB 3.0 Ethernet Adapters */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(VENDOR_ID_REALTEK, 0x8153, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&r8153_info,
पूर्ण,

/* Lenovo Powered USB-C Travel Hub (4X90S92381, based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(VENDOR_ID_LENOVO, 0x721e, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&r8153_info,
पूर्ण,

	अणु पूर्ण,		/* END */
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल पूर्णांक rtl8153_ecm_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा usb_device_id *id)
अणु
#अगर IS_REACHABLE(CONFIG_USB_RTL8152)
	अगर (rtl8152_get_version(पूर्णांकf))
		वापस -ENODEV;
#पूर्ण_अगर

	वापस usbnet_probe(पूर्णांकf, id);
पूर्ण

अटल काष्ठा usb_driver r8153_ecm_driver = अणु
	.name =		"r8153_ecm",
	.id_table =	products,
	.probe =	rtl8153_ecm_probe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.reset_resume =	usbnet_resume,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(r8153_ecm_driver);

MODULE_AUTHOR("Hayes Wang");
MODULE_DESCRIPTION("Realtek USB ECM device");
MODULE_LICENSE("GPL");
