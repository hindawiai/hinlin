<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (c) 2002 Petko Manolov (petkan@users.sourceक्रमge.net)
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/usb.h>
#समावेश <linux/uaccess.h>

/* Version Inक्रमmation */
#घोषणा DRIVER_VERSION "v0.6.2 (2004/08/27)"
#घोषणा DRIVER_AUTHOR "Petko Manolov <petkan@users.sourceforge.net>"
#घोषणा DRIVER_DESC "rtl8150 based usb-ethernet driver"

#घोषणा	IDR			0x0120
#घोषणा	MAR			0x0126
#घोषणा	CR			0x012e
#घोषणा	TCR			0x012f
#घोषणा	RCR			0x0130
#घोषणा	TSR			0x0132
#घोषणा	RSR			0x0133
#घोषणा	CON0			0x0135
#घोषणा	CON1			0x0136
#घोषणा	MSR			0x0137
#घोषणा	PHYADD			0x0138
#घोषणा	PHYDAT			0x0139
#घोषणा	PHYCNT			0x013b
#घोषणा	GPPC			0x013d
#घोषणा	BMCR			0x0140
#घोषणा	BMSR			0x0142
#घोषणा	ANAR			0x0144
#घोषणा	ANLP			0x0146
#घोषणा	AER			0x0148
#घोषणा CSCR			0x014C  /* This one has the link status */
#घोषणा CSCR_LINK_STATUS	(1 << 3)

#घोषणा	IDR_EEPROM		0x1202

#घोषणा	PHY_READ		0
#घोषणा	PHY_WRITE		0x20
#घोषणा	PHY_GO			0x40

#घोषणा	MII_TIMEOUT		10
#घोषणा	INTबफ_मानE		8

#घोषणा	RTL8150_REQT_READ	0xc0
#घोषणा	RTL8150_REQT_WRITE	0x40
#घोषणा	RTL8150_REQ_GET_REGS	0x05
#घोषणा	RTL8150_REQ_SET_REGS	0x05


/* Transmit status रेजिस्टर errors */
#घोषणा TSR_ECOL		(1<<5)
#घोषणा TSR_LCOL		(1<<4)
#घोषणा TSR_LOSS_CRS		(1<<3)
#घोषणा TSR_JBR			(1<<2)
#घोषणा TSR_ERRORS		(TSR_ECOL | TSR_LCOL | TSR_LOSS_CRS | TSR_JBR)
/* Receive status रेजिस्टर errors */
#घोषणा RSR_CRC			(1<<2)
#घोषणा RSR_FAE			(1<<1)
#घोषणा RSR_ERRORS		(RSR_CRC | RSR_FAE)

/* Media status रेजिस्टर definitions */
#घोषणा MSR_DUPLEX		(1<<4)
#घोषणा MSR_SPEED		(1<<3)
#घोषणा MSR_LINK		(1<<2)

/* Interrupt pipe data */
#घोषणा INT_TSR			0x00
#घोषणा INT_RSR			0x01
#घोषणा INT_MSR			0x02
#घोषणा INT_WAKSR		0x03
#घोषणा INT_TXOK_CNT		0x04
#घोषणा INT_RXLOST_CNT		0x05
#घोषणा INT_CRERR_CNT		0x06
#घोषणा INT_COL_CNT		0x07


#घोषणा	RTL8150_MTU		1540
#घोषणा	RTL8150_TX_TIMEOUT	(HZ)
#घोषणा	RX_SKB_POOL_SIZE	4

/* rtl8150 flags */
#घोषणा	RTL8150_HW_CRC		0
#घोषणा	RX_REG_SET		1
#घोषणा	RTL8150_UNPLUG		2
#घोषणा	RX_URB_FAIL		3

/* Define these values to match your device */
#घोषणा	VENDOR_ID_REALTEK		0x0bda
#घोषणा	VENDOR_ID_MELCO			0x0411
#घोषणा	VENDOR_ID_MICRONET		0x3980
#घोषणा	VENDOR_ID_LONGSHINE		0x07b8
#घोषणा	VENDOR_ID_OQO			0x1557
#घोषणा	VENDOR_ID_ZYXEL			0x0586

#घोषणा PRODUCT_ID_RTL8150		0x8150
#घोषणा	PRODUCT_ID_LUAKTX		0x0012
#घोषणा	PRODUCT_ID_LCS8138TX		0x401a
#घोषणा PRODUCT_ID_SP128AR		0x0003
#घोषणा	PRODUCT_ID_PRESTIGE		0x401a

#अघोषित	EEPROM_WRITE

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id rtl8150_table[] = अणु
	अणुUSB_DEVICE(VENDOR_ID_REALTEK, PRODUCT_ID_RTL8150)पूर्ण,
	अणुUSB_DEVICE(VENDOR_ID_MELCO, PRODUCT_ID_LUAKTX)पूर्ण,
	अणुUSB_DEVICE(VENDOR_ID_MICRONET, PRODUCT_ID_SP128AR)पूर्ण,
	अणुUSB_DEVICE(VENDOR_ID_LONGSHINE, PRODUCT_ID_LCS8138TX)पूर्ण,
	अणुUSB_DEVICE(VENDOR_ID_OQO, PRODUCT_ID_RTL8150)पूर्ण,
	अणुUSB_DEVICE(VENDOR_ID_ZYXEL, PRODUCT_ID_PRESTIGE)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, rtl8150_table);

काष्ठा rtl8150 अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_device *udev;
	काष्ठा tasklet_काष्ठा tl;
	काष्ठा net_device *netdev;
	काष्ठा urb *rx_urb, *tx_urb, *पूर्णांकr_urb;
	काष्ठा sk_buff *tx_skb, *rx_skb;
	काष्ठा sk_buff *rx_skb_pool[RX_SKB_POOL_SIZE];
	spinlock_t rx_pool_lock;
	काष्ठा usb_ctrlrequest dr;
	पूर्णांक पूर्णांकr_पूर्णांकerval;
	u8 *पूर्णांकr_buff;
	u8 phy;
पूर्ण;

प्रकार काष्ठा rtl8150 rtl8150_t;

काष्ठा async_req अणु
	काष्ठा usb_ctrlrequest dr;
	u16 rx_creg;
पूर्ण;

अटल स्थिर अक्षर driver_name [] = "rtl8150";

/*
**
**	device related part of the code
**
*/
अटल पूर्णांक get_रेजिस्टरs(rtl8150_t * dev, u16 indx, u16 size, व्योम *data)
अणु
	वापस usb_control_msg_recv(dev->udev, 0, RTL8150_REQ_GET_REGS,
				    RTL8150_REQT_READ, indx, 0, data, size,
				    1000, GFP_NOIO);
पूर्ण

अटल पूर्णांक set_रेजिस्टरs(rtl8150_t * dev, u16 indx, u16 size, स्थिर व्योम *data)
अणु
	वापस usb_control_msg_send(dev->udev, 0, RTL8150_REQ_SET_REGS,
				    RTL8150_REQT_WRITE, indx, 0, data, size,
				    1000, GFP_NOIO);
पूर्ण

अटल व्योम async_set_reg_cb(काष्ठा urb *urb)
अणु
	काष्ठा async_req *req = (काष्ठा async_req *)urb->context;
	पूर्णांक status = urb->status;

	अगर (status < 0)
		dev_dbg(&urb->dev->dev, "%s failed with %d", __func__, status);
	kमुक्त(req);
	usb_मुक्त_urb(urb);
पूर्ण

अटल पूर्णांक async_set_रेजिस्टरs(rtl8150_t *dev, u16 indx, u16 size, u16 reg)
अणु
	पूर्णांक res = -ENOMEM;
	काष्ठा urb *async_urb;
	काष्ठा async_req *req;

	req = kदो_स्मृति(माप(काष्ठा async_req), GFP_ATOMIC);
	अगर (req == शून्य)
		वापस res;
	async_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (async_urb == शून्य) अणु
		kमुक्त(req);
		वापस res;
	पूर्ण
	req->rx_creg = cpu_to_le16(reg);
	req->dr.bRequestType = RTL8150_REQT_WRITE;
	req->dr.bRequest = RTL8150_REQ_SET_REGS;
	req->dr.wIndex = 0;
	req->dr.wValue = cpu_to_le16(indx);
	req->dr.wLength = cpu_to_le16(size);
	usb_fill_control_urb(async_urb, dev->udev,
	                     usb_sndctrlpipe(dev->udev, 0), (व्योम *)&req->dr,
			     &req->rx_creg, size, async_set_reg_cb, req);
	res = usb_submit_urb(async_urb, GFP_ATOMIC);
	अगर (res) अणु
		अगर (res == -ENODEV)
			netअगर_device_detach(dev->netdev);
		dev_err(&dev->udev->dev, "%s failed with %d\n", __func__, res);
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक पढ़ो_mii_word(rtl8150_t * dev, u8 phy, __u8 indx, u16 * reg)
अणु
	पूर्णांक i;
	u8 data[3], पंचांगp;

	data[0] = phy;
	data[1] = data[2] = 0;
	पंचांगp = indx | PHY_READ | PHY_GO;
	i = 0;

	set_रेजिस्टरs(dev, PHYADD, माप(data), data);
	set_रेजिस्टरs(dev, PHYCNT, 1, &पंचांगp);
	करो अणु
		get_रेजिस्टरs(dev, PHYCNT, 1, data);
	पूर्ण जबतक ((data[0] & PHY_GO) && (i++ < MII_TIMEOUT));

	अगर (i <= MII_TIMEOUT) अणु
		get_रेजिस्टरs(dev, PHYDAT, 2, data);
		*reg = data[0] | (data[1] << 8);
		वापस 0;
	पूर्ण अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक ग_लिखो_mii_word(rtl8150_t * dev, u8 phy, __u8 indx, u16 reg)
अणु
	पूर्णांक i;
	u8 data[3], पंचांगp;

	data[0] = phy;
	data[1] = reg & 0xff;
	data[2] = (reg >> 8) & 0xff;
	पंचांगp = indx | PHY_WRITE | PHY_GO;
	i = 0;

	set_रेजिस्टरs(dev, PHYADD, माप(data), data);
	set_रेजिस्टरs(dev, PHYCNT, 1, &पंचांगp);
	करो अणु
		get_रेजिस्टरs(dev, PHYCNT, 1, data);
	पूर्ण जबतक ((data[0] & PHY_GO) && (i++ < MII_TIMEOUT));

	अगर (i <= MII_TIMEOUT)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल व्योम set_ethernet_addr(rtl8150_t *dev)
अणु
	u8 node_id[ETH_ALEN];
	पूर्णांक ret;

	ret = get_रेजिस्टरs(dev, IDR, माप(node_id), node_id);

	अगर (!ret) अणु
		ether_addr_copy(dev->netdev->dev_addr, node_id);
	पूर्ण अन्यथा अणु
		eth_hw_addr_अक्रमom(dev->netdev);
		netdev_notice(dev->netdev, "Assigned a random MAC address: %pM\n",
			      dev->netdev->dev_addr);
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8150_set_mac_address(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	rtl8150_t *dev = netdev_priv(netdev);

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	netdev_dbg(netdev, "Setting MAC address to %pM\n", netdev->dev_addr);
	/* Set the IDR रेजिस्टरs. */
	set_रेजिस्टरs(dev, IDR, netdev->addr_len, netdev->dev_addr);
#अगर_घोषित EEPROM_WRITE
	अणु
	पूर्णांक i;
	u8 cr;
	/* Get the CR contents. */
	get_रेजिस्टरs(dev, CR, 1, &cr);
	/* Set the WEPROM bit (eeprom ग_लिखो enable). */
	cr |= 0x20;
	set_रेजिस्टरs(dev, CR, 1, &cr);
	/* Write the MAC address पूर्णांकo eeprom. Eeprom ग_लिखोs must be word-sized,
	   so we need to split them up. */
	क्रम (i = 0; i * 2 < netdev->addr_len; i++) अणु
		set_रेजिस्टरs(dev, IDR_EEPROM + (i * 2), 2,
		netdev->dev_addr + (i * 2));
	पूर्ण
	/* Clear the WEPROM bit (preventing accidental eeprom ग_लिखोs). */
	cr &= 0xdf;
	set_रेजिस्टरs(dev, CR, 1, &cr);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक rtl8150_reset(rtl8150_t * dev)
अणु
	u8 data = 0x10;
	पूर्णांक i = HZ;

	set_रेजिस्टरs(dev, CR, 1, &data);
	करो अणु
		get_रेजिस्टरs(dev, CR, 1, &data);
	पूर्ण जबतक ((data & 0x10) && --i);

	वापस (i > 0) ? 1 : 0;
पूर्ण

अटल पूर्णांक alloc_all_urbs(rtl8150_t * dev)
अणु
	dev->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->rx_urb)
		वापस 0;
	dev->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->tx_urb) अणु
		usb_मुक्त_urb(dev->rx_urb);
		वापस 0;
	पूर्ण
	dev->पूर्णांकr_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->पूर्णांकr_urb) अणु
		usb_मुक्त_urb(dev->rx_urb);
		usb_मुक्त_urb(dev->tx_urb);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम मुक्त_all_urbs(rtl8150_t * dev)
अणु
	usb_मुक्त_urb(dev->rx_urb);
	usb_मुक्त_urb(dev->tx_urb);
	usb_मुक्त_urb(dev->पूर्णांकr_urb);
पूर्ण

अटल व्योम unlink_all_urbs(rtl8150_t * dev)
अणु
	usb_समाप्त_urb(dev->rx_urb);
	usb_समाप्त_urb(dev->tx_urb);
	usb_समाप्त_urb(dev->पूर्णांकr_urb);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *pull_skb(rtl8150_t *dev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < RX_SKB_POOL_SIZE; i++) अणु
		अगर (dev->rx_skb_pool[i]) अणु
			skb = dev->rx_skb_pool[i];
			dev->rx_skb_pool[i] = शून्य;
			वापस skb;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	rtl8150_t *dev;
	अचिन्हित pkt_len, res;
	काष्ठा sk_buff *skb;
	काष्ठा net_device *netdev;
	पूर्णांक status = urb->status;
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	dev = urb->context;
	अगर (!dev)
		वापस;
	अगर (test_bit(RTL8150_UNPLUG, &dev->flags))
		वापस;
	netdev = dev->netdev;
	अगर (!netअगर_device_present(netdev))
		वापस;

	चयन (status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
		वापस;	/* the urb is in unlink state */
	हाल -ETIME:
		अगर (prपूर्णांकk_ratelimit())
			dev_warn(&urb->dev->dev, "may be reset is needed?..\n");
		जाओ goon;
	शेष:
		अगर (prपूर्णांकk_ratelimit())
			dev_warn(&urb->dev->dev, "Rx status %d\n", status);
		जाओ goon;
	पूर्ण

	अगर (!dev->rx_skb)
		जाओ resched;
	/* protect against लघु packets (tell me why we got some?!?) */
	अगर (urb->actual_length < 4)
		जाओ goon;

	res = urb->actual_length;
	pkt_len = res - 4;

	skb_put(dev->rx_skb, pkt_len);
	dev->rx_skb->protocol = eth_type_trans(dev->rx_skb, netdev);
	netअगर_rx(dev->rx_skb);
	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += pkt_len;

	spin_lock_irqsave(&dev->rx_pool_lock, flags);
	skb = pull_skb(dev);
	spin_unlock_irqrestore(&dev->rx_pool_lock, flags);
	अगर (!skb)
		जाओ resched;

	dev->rx_skb = skb;
goon:
	usb_fill_bulk_urb(dev->rx_urb, dev->udev, usb_rcvbulkpipe(dev->udev, 1),
		      dev->rx_skb->data, RTL8150_MTU, पढ़ो_bulk_callback, dev);
	result = usb_submit_urb(dev->rx_urb, GFP_ATOMIC);
	अगर (result == -ENODEV)
		netअगर_device_detach(dev->netdev);
	अन्यथा अगर (result) अणु
		set_bit(RX_URB_FAIL, &dev->flags);
		जाओ resched;
	पूर्ण अन्यथा अणु
		clear_bit(RX_URB_FAIL, &dev->flags);
	पूर्ण

	वापस;
resched:
	tasklet_schedule(&dev->tl);
पूर्ण

अटल व्योम ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	rtl8150_t *dev;
	पूर्णांक status = urb->status;

	dev = urb->context;
	अगर (!dev)
		वापस;
	dev_kमुक्त_skb_irq(dev->tx_skb);
	अगर (!netअगर_device_present(dev->netdev))
		वापस;
	अगर (status)
		dev_info(&urb->dev->dev, "%s: Tx status %d\n",
			 dev->netdev->name, status);
	netअगर_trans_update(dev->netdev);
	netअगर_wake_queue(dev->netdev);
पूर्ण

अटल व्योम पूर्णांकr_callback(काष्ठा urb *urb)
अणु
	rtl8150_t *dev;
	__u8 *d;
	पूर्णांक status = urb->status;
	पूर्णांक res;

	dev = urb->context;
	अगर (!dev)
		वापस;
	चयन (status) अणु
	हाल 0:			/* success */
		अवरोध;
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	/* -EPIPE:  should clear the halt */
	शेष:
		dev_info(&urb->dev->dev, "%s: intr status %d\n",
			 dev->netdev->name, status);
		जाओ resubmit;
	पूर्ण

	d = urb->transfer_buffer;
	अगर (d[0] & TSR_ERRORS) अणु
		dev->netdev->stats.tx_errors++;
		अगर (d[INT_TSR] & (TSR_ECOL | TSR_JBR))
			dev->netdev->stats.tx_पातed_errors++;
		अगर (d[INT_TSR] & TSR_LCOL)
			dev->netdev->stats.tx_winकरोw_errors++;
		अगर (d[INT_TSR] & TSR_LOSS_CRS)
			dev->netdev->stats.tx_carrier_errors++;
	पूर्ण
	/* Report link status changes to the network stack */
	अगर ((d[INT_MSR] & MSR_LINK) == 0) अणु
		अगर (netअगर_carrier_ok(dev->netdev)) अणु
			netअगर_carrier_off(dev->netdev);
			netdev_dbg(dev->netdev, "%s: LINK LOST\n", __func__);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!netअगर_carrier_ok(dev->netdev)) अणु
			netअगर_carrier_on(dev->netdev);
			netdev_dbg(dev->netdev, "%s: LINK CAME BACK\n", __func__);
		पूर्ण
	पूर्ण

resubmit:
	res = usb_submit_urb (urb, GFP_ATOMIC);
	अगर (res == -ENODEV)
		netअगर_device_detach(dev->netdev);
	अन्यथा अगर (res)
		dev_err(&dev->udev->dev,
			"can't resubmit intr, %s-%s/input0, status %d\n",
			dev->udev->bus->bus_name, dev->udev->devpath, res);
पूर्ण

अटल पूर्णांक rtl8150_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	rtl8150_t *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	netअगर_device_detach(dev->netdev);

	अगर (netअगर_running(dev->netdev)) अणु
		usb_समाप्त_urb(dev->rx_urb);
		usb_समाप्त_urb(dev->पूर्णांकr_urb);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtl8150_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	rtl8150_t *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	netअगर_device_attach(dev->netdev);
	अगर (netअगर_running(dev->netdev)) अणु
		dev->rx_urb->status = 0;
		dev->rx_urb->actual_length = 0;
		पढ़ो_bulk_callback(dev->rx_urb);

		dev->पूर्णांकr_urb->status = 0;
		dev->पूर्णांकr_urb->actual_length = 0;
		पूर्णांकr_callback(dev->पूर्णांकr_urb);
	पूर्ण
	वापस 0;
पूर्ण

/*
**
**	network related part of the code
**
*/

अटल व्योम fill_skb_pool(rtl8150_t *dev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < RX_SKB_POOL_SIZE; i++) अणु
		अगर (dev->rx_skb_pool[i])
			जारी;
		skb = dev_alloc_skb(RTL8150_MTU + 2);
		अगर (!skb) अणु
			वापस;
		पूर्ण
		skb_reserve(skb, 2);
		dev->rx_skb_pool[i] = skb;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_skb_pool(rtl8150_t *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RX_SKB_POOL_SIZE; i++)
		dev_kमुक्त_skb(dev->rx_skb_pool[i]);
पूर्ण

अटल व्योम rx_fixup(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rtl8150 *dev = from_tasklet(dev, t, tl);
	काष्ठा sk_buff *skb;
	पूर्णांक status;

	spin_lock_irq(&dev->rx_pool_lock);
	fill_skb_pool(dev);
	spin_unlock_irq(&dev->rx_pool_lock);
	अगर (test_bit(RX_URB_FAIL, &dev->flags))
		अगर (dev->rx_skb)
			जाओ try_again;
	spin_lock_irq(&dev->rx_pool_lock);
	skb = pull_skb(dev);
	spin_unlock_irq(&dev->rx_pool_lock);
	अगर (skb == शून्य)
		जाओ tlsched;
	dev->rx_skb = skb;
	usb_fill_bulk_urb(dev->rx_urb, dev->udev, usb_rcvbulkpipe(dev->udev, 1),
		      dev->rx_skb->data, RTL8150_MTU, पढ़ो_bulk_callback, dev);
try_again:
	status = usb_submit_urb(dev->rx_urb, GFP_ATOMIC);
	अगर (status == -ENODEV) अणु
		netअगर_device_detach(dev->netdev);
	पूर्ण अन्यथा अगर (status) अणु
		set_bit(RX_URB_FAIL, &dev->flags);
		जाओ tlsched;
	पूर्ण अन्यथा अणु
		clear_bit(RX_URB_FAIL, &dev->flags);
	पूर्ण

	वापस;
tlsched:
	tasklet_schedule(&dev->tl);
पूर्ण

अटल पूर्णांक enable_net_traffic(rtl8150_t * dev)
अणु
	u8 cr, tcr, rcr, msr;

	अगर (!rtl8150_reset(dev)) अणु
		dev_warn(&dev->udev->dev, "device reset failed\n");
	पूर्ण
	/* RCR bit7=1 attach Rx info at the end;  =0 HW CRC (which is broken) */
	rcr = 0x9e;
	tcr = 0xd8;
	cr = 0x0c;
	अगर (!(rcr & 0x80))
		set_bit(RTL8150_HW_CRC, &dev->flags);
	set_रेजिस्टरs(dev, RCR, 1, &rcr);
	set_रेजिस्टरs(dev, TCR, 1, &tcr);
	set_रेजिस्टरs(dev, CR, 1, &cr);
	get_रेजिस्टरs(dev, MSR, 1, &msr);

	वापस 0;
पूर्ण

अटल व्योम disable_net_traffic(rtl8150_t * dev)
अणु
	u8 cr;

	get_रेजिस्टरs(dev, CR, 1, &cr);
	cr &= 0xf3;
	set_रेजिस्टरs(dev, CR, 1, &cr);
पूर्ण

अटल व्योम rtl8150_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	rtl8150_t *dev = netdev_priv(netdev);
	dev_warn(&netdev->dev, "Tx timeout.\n");
	usb_unlink_urb(dev->tx_urb);
	netdev->stats.tx_errors++;
पूर्ण

अटल व्योम rtl8150_set_multicast(काष्ठा net_device *netdev)
अणु
	rtl8150_t *dev = netdev_priv(netdev);
	u16 rx_creg = 0x9e;

	netअगर_stop_queue(netdev);
	अगर (netdev->flags & IFF_PROMISC) अणु
		rx_creg |= 0x0001;
		dev_info(&netdev->dev, "%s: promiscuous mode\n", netdev->name);
	पूर्ण अन्यथा अगर (!netdev_mc_empty(netdev) ||
		   (netdev->flags & IFF_ALLMULTI)) अणु
		rx_creg &= 0xfffe;
		rx_creg |= 0x0002;
		dev_dbg(&netdev->dev, "%s: allmulti set\n", netdev->name);
	पूर्ण अन्यथा अणु
		/* ~RX_MULTICAST, ~RX_PROMISCUOUS */
		rx_creg &= 0x00fc;
	पूर्ण
	async_set_रेजिस्टरs(dev, RCR, माप(rx_creg), rx_creg);
	netअगर_wake_queue(netdev);
पूर्ण

अटल netdev_tx_t rtl8150_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *netdev)
अणु
	rtl8150_t *dev = netdev_priv(netdev);
	पूर्णांक count, res;

	netअगर_stop_queue(netdev);
	count = (skb->len < 60) ? 60 : skb->len;
	count = (count & 0x3f) ? count : count + 1;
	dev->tx_skb = skb;
	usb_fill_bulk_urb(dev->tx_urb, dev->udev, usb_sndbulkpipe(dev->udev, 2),
		      skb->data, count, ग_लिखो_bulk_callback, dev);
	अगर ((res = usb_submit_urb(dev->tx_urb, GFP_ATOMIC))) अणु
		/* Can we get/handle EPIPE here? */
		अगर (res == -ENODEV)
			netअगर_device_detach(dev->netdev);
		अन्यथा अणु
			dev_warn(&netdev->dev, "failed tx_urb %d\n", res);
			netdev->stats.tx_errors++;
			netअगर_start_queue(netdev);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += skb->len;
		netअगर_trans_update(netdev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण


अटल व्योम set_carrier(काष्ठा net_device *netdev)
अणु
	rtl8150_t *dev = netdev_priv(netdev);
	लघु पंचांगp;

	get_रेजिस्टरs(dev, CSCR, 2, &पंचांगp);
	अगर (पंचांगp & CSCR_LINK_STATUS)
		netअगर_carrier_on(netdev);
	अन्यथा
		netअगर_carrier_off(netdev);
पूर्ण

अटल पूर्णांक rtl8150_खोलो(काष्ठा net_device *netdev)
अणु
	rtl8150_t *dev = netdev_priv(netdev);
	पूर्णांक res;

	अगर (dev->rx_skb == शून्य)
		dev->rx_skb = pull_skb(dev);
	अगर (!dev->rx_skb)
		वापस -ENOMEM;

	set_रेजिस्टरs(dev, IDR, 6, netdev->dev_addr);

	usb_fill_bulk_urb(dev->rx_urb, dev->udev, usb_rcvbulkpipe(dev->udev, 1),
		      dev->rx_skb->data, RTL8150_MTU, पढ़ो_bulk_callback, dev);
	अगर ((res = usb_submit_urb(dev->rx_urb, GFP_KERNEL))) अणु
		अगर (res == -ENODEV)
			netअगर_device_detach(dev->netdev);
		dev_warn(&netdev->dev, "rx_urb submit failed: %d\n", res);
		वापस res;
	पूर्ण
	usb_fill_पूर्णांक_urb(dev->पूर्णांकr_urb, dev->udev, usb_rcvपूर्णांकpipe(dev->udev, 3),
		     dev->पूर्णांकr_buff, INTबफ_मानE, पूर्णांकr_callback,
		     dev, dev->पूर्णांकr_पूर्णांकerval);
	अगर ((res = usb_submit_urb(dev->पूर्णांकr_urb, GFP_KERNEL))) अणु
		अगर (res == -ENODEV)
			netअगर_device_detach(dev->netdev);
		dev_warn(&netdev->dev, "intr_urb submit failed: %d\n", res);
		usb_समाप्त_urb(dev->rx_urb);
		वापस res;
	पूर्ण
	enable_net_traffic(dev);
	set_carrier(netdev);
	netअगर_start_queue(netdev);

	वापस res;
पूर्ण

अटल पूर्णांक rtl8150_बंद(काष्ठा net_device *netdev)
अणु
	rtl8150_t *dev = netdev_priv(netdev);

	netअगर_stop_queue(netdev);
	अगर (!test_bit(RTL8150_UNPLUG, &dev->flags))
		disable_net_traffic(dev);
	unlink_all_urbs(dev);

	वापस 0;
पूर्ण

अटल व्योम rtl8150_get_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *info)
अणु
	rtl8150_t *dev = netdev_priv(netdev);

	strlcpy(info->driver, driver_name, माप(info->driver));
	strlcpy(info->version, DRIVER_VERSION, माप(info->version));
	usb_make_path(dev->udev, info->bus_info, माप(info->bus_info));
पूर्ण

अटल पूर्णांक rtl8150_get_link_ksettings(काष्ठा net_device *netdev,
				      काष्ठा ethtool_link_ksettings *ecmd)
अणु
	rtl8150_t *dev = netdev_priv(netdev);
	लघु lpa, bmcr;
	u32 supported;

	supported = (SUPPORTED_10baseT_Half |
			  SUPPORTED_10baseT_Full |
			  SUPPORTED_100baseT_Half |
			  SUPPORTED_100baseT_Full |
			  SUPPORTED_Autoneg |
			  SUPPORTED_TP | SUPPORTED_MII);
	ecmd->base.port = PORT_TP;
	ecmd->base.phy_address = dev->phy;
	get_रेजिस्टरs(dev, BMCR, 2, &bmcr);
	get_रेजिस्टरs(dev, ANLP, 2, &lpa);
	अगर (bmcr & BMCR_ANENABLE) अणु
		u32 speed = ((lpa & (LPA_100HALF | LPA_100FULL)) ?
			     SPEED_100 : SPEED_10);
		ecmd->base.speed = speed;
		ecmd->base.स्वतःneg = AUTONEG_ENABLE;
		अगर (speed == SPEED_100)
			ecmd->base.duplex = (lpa & LPA_100FULL) ?
			    DUPLEX_FULL : DUPLEX_HALF;
		अन्यथा
			ecmd->base.duplex = (lpa & LPA_10FULL) ?
			    DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		ecmd->base.स्वतःneg = AUTONEG_DISABLE;
		ecmd->base.speed = ((bmcr & BMCR_SPEED100) ?
					     SPEED_100 : SPEED_10);
		ecmd->base.duplex = (bmcr & BMCR_FULLDPLX) ?
		    DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_drvinfo = rtl8150_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_link_ksettings = rtl8150_get_link_ksettings,
पूर्ण;

अटल पूर्णांक rtl8150_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	rtl8150_t *dev = netdev_priv(netdev);
	u16 *data = (u16 *) & rq->अगरr_अगरru;
	पूर्णांक res = 0;

	चयन (cmd) अणु
	हाल SIOCDEVPRIVATE:
		data[0] = dev->phy;
		fallthrough;
	हाल SIOCDEVPRIVATE + 1:
		पढ़ो_mii_word(dev, dev->phy, (data[1] & 0x1f), &data[3]);
		अवरोध;
	हाल SIOCDEVPRIVATE + 2:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		ग_लिखो_mii_word(dev, dev->phy, (data[1] & 0x1f), data[2]);
		अवरोध;
	शेष:
		res = -EOPNOTSUPP;
	पूर्ण

	वापस res;
पूर्ण

अटल स्थिर काष्ठा net_device_ops rtl8150_netdev_ops = अणु
	.nकरो_खोलो		= rtl8150_खोलो,
	.nकरो_stop		= rtl8150_बंद,
	.nकरो_करो_ioctl		= rtl8150_ioctl,
	.nकरो_start_xmit		= rtl8150_start_xmit,
	.nकरो_tx_समयout		= rtl8150_tx_समयout,
	.nकरो_set_rx_mode	= rtl8150_set_multicast,
	.nकरो_set_mac_address	= rtl8150_set_mac_address,

	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक rtl8150_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	rtl8150_t *dev;
	काष्ठा net_device *netdev;

	netdev = alloc_etherdev(माप(rtl8150_t));
	अगर (!netdev)
		वापस -ENOMEM;

	dev = netdev_priv(netdev);

	dev->पूर्णांकr_buff = kदो_स्मृति(INTबफ_मानE, GFP_KERNEL);
	अगर (!dev->पूर्णांकr_buff) अणु
		मुक्त_netdev(netdev);
		वापस -ENOMEM;
	पूर्ण

	tasklet_setup(&dev->tl, rx_fixup);
	spin_lock_init(&dev->rx_pool_lock);

	dev->udev = udev;
	dev->netdev = netdev;
	netdev->netdev_ops = &rtl8150_netdev_ops;
	netdev->watchकरोg_समयo = RTL8150_TX_TIMEOUT;
	netdev->ethtool_ops = &ops;
	dev->पूर्णांकr_पूर्णांकerval = 100;	/* 100ms */

	अगर (!alloc_all_urbs(dev)) अणु
		dev_err(&पूर्णांकf->dev, "out of memory\n");
		जाओ out;
	पूर्ण
	अगर (!rtl8150_reset(dev)) अणु
		dev_err(&पूर्णांकf->dev, "couldn't reset the device\n");
		जाओ out1;
	पूर्ण
	fill_skb_pool(dev);
	set_ethernet_addr(dev);

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);
	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);
	अगर (रेजिस्टर_netdev(netdev) != 0) अणु
		dev_err(&पूर्णांकf->dev, "couldn't register the device\n");
		जाओ out2;
	पूर्ण

	dev_info(&पूर्णांकf->dev, "%s: rtl8150 is detected\n", netdev->name);

	वापस 0;

out2:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	मुक्त_skb_pool(dev);
out1:
	मुक्त_all_urbs(dev);
out:
	kमुक्त(dev->पूर्णांकr_buff);
	मुक्त_netdev(netdev);
	वापस -EIO;
पूर्ण

अटल व्योम rtl8150_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	rtl8150_t *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (dev) अणु
		set_bit(RTL8150_UNPLUG, &dev->flags);
		tasklet_समाप्त(&dev->tl);
		unरेजिस्टर_netdev(dev->netdev);
		unlink_all_urbs(dev);
		मुक्त_all_urbs(dev);
		मुक्त_skb_pool(dev);
		dev_kमुक्त_skb(dev->rx_skb);
		kमुक्त(dev->पूर्णांकr_buff);
		मुक्त_netdev(dev->netdev);
	पूर्ण
पूर्ण

अटल काष्ठा usb_driver rtl8150_driver = अणु
	.name		= driver_name,
	.probe		= rtl8150_probe,
	.disconnect	= rtl8150_disconnect,
	.id_table	= rtl8150_table,
	.suspend	= rtl8150_suspend,
	.resume		= rtl8150_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(rtl8150_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
