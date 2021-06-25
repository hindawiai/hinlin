<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (c) 1999-2013 Petko Manolov (petkan@nucleusys.com)
 *
 *	ChangeLog:
 *		....	Most of the समय spent on पढ़ोing sources & करोcs.
 *		v0.2.x	First official release क्रम the Linux kernel.
 *		v0.3.0	Beutअगरied and काष्ठाured, some bugs fixed.
 *		v0.3.x	URBअगरying bulk requests and bugfixing. First relatively
 *			stable release. Still can touch device's रेजिस्टरs only
 *			from top-halves.
 *		v0.4.0	Control messages reमुख्यed unurbअगरied are now URBs.
 *			Now we can touch the HW at any समय.
 *		v0.4.9	Control urbs again use process context to रुको. Argh...
 *			Some दीर्घ standing bugs (enable_net_traffic) fixed.
 *			Also nasty trick about resubmiting control urb from
 *			पूर्णांकerrupt context used. Please let me know how it
 *			behaves. Pegasus II support added since this version.
 *			TODO: suppressing HCD warnings spewage on disconnect.
 *		v0.4.13	Ethernet address is now set at probe(), not at खोलो()
 *			समय as this seems to अवरोध dhcpd.
 *		v0.5.0	branch to 2.5.x kernels
 *		v0.5.1	ethtool support added
 *		v0.5.5	rx socket buffers are in a pool and the their allocation
 *			is out of the पूर्णांकerrupt routine.
 *		...
 *		v0.9.3	simplअगरied [get|set]_रेजिस्टर(s), async update रेजिस्टरs
 *			logic revisited, receive skb_pool हटाओd.
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश "pegasus.h"

/*
 * Version Inक्रमmation
 */
#घोषणा DRIVER_VERSION "v0.9.3 (2013/04/25)"
#घोषणा DRIVER_AUTHOR "Petko Manolov <petkan@nucleusys.com>"
#घोषणा DRIVER_DESC "Pegasus/Pegasus II USB Ethernet driver"

अटल स्थिर अक्षर driver_name[] = "pegasus";

#अघोषित	PEGASUS_WRITE_EEPROM
#घोषणा	BMSR_MEDIA	(BMSR_10HALF | BMSR_10FULL | BMSR_100HALF | \
			BMSR_100FULL | BMSR_ANEGCAPABLE)
#घोषणा CARRIER_CHECK_DELAY (2 * HZ)

अटल bool loopback;
अटल bool mii_mode;
अटल अक्षर *devid;

अटल काष्ठा usb_eth_dev usb_dev_id[] = अणु
#घोषणा	PEGASUS_DEV(pn, vid, pid, flags)	\
	अणु.name = pn, .venकरोr = vid, .device = pid, .निजी = flagsपूर्ण,
#घोषणा PEGASUS_DEV_CLASS(pn, vid, pid, dclass, flags) \
	PEGASUS_DEV(pn, vid, pid, flags)
#समावेश "pegasus.h"
#अघोषित	PEGASUS_DEV
#अघोषित	PEGASUS_DEV_CLASS
	अणुशून्य, 0, 0, 0पूर्ण,
	अणुशून्य, 0, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा usb_device_id pegasus_ids[] = अणु
#घोषणा	PEGASUS_DEV(pn, vid, pid, flags) \
	अणु.match_flags = USB_DEVICE_ID_MATCH_DEVICE, .idVenकरोr = vid, .idProduct = pidपूर्ण,
/*
 * The Belkin F8T012xx1 bluetooth adaptor has the same venकरोr and product
 * IDs as the Belkin F5D5050, so we need to teach the pegasus driver to
 * ignore adaptors beदीर्घing to the "Wireless" class 0xE0. For this one
 * हाल anyway, seeing as the pegasus is क्रम "Wired" adaptors.
 */
#घोषणा PEGASUS_DEV_CLASS(pn, vid, pid, dclass, flags) \
	अणु.match_flags = (USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_DEV_CLASS), \
	.idVenकरोr = vid, .idProduct = pid, .bDeviceClass = dclassपूर्ण,
#समावेश "pegasus.h"
#अघोषित	PEGASUS_DEV
#अघोषित	PEGASUS_DEV_CLASS
	अणुपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
module_param(loopback, bool, 0);
module_param(mii_mode, bool, 0);
module_param(devid, अक्षरp, 0);
MODULE_PARM_DESC(loopback, "Enable MAC loopback mode (bit 0)");
MODULE_PARM_DESC(mii_mode, "Enable HomePNA mode (bit 0),default=MII mode = 0");
MODULE_PARM_DESC(devid, "The format is: 'DEV_name:VendorID:DeviceID:Flags'");

/* use ethtool to change the level क्रम any given device */
अटल पूर्णांक msg_level = -1;
module_param(msg_level, पूर्णांक, 0);
MODULE_PARM_DESC(msg_level, "Override default message level");

MODULE_DEVICE_TABLE(usb, pegasus_ids);
अटल स्थिर काष्ठा net_device_ops pegasus_netdev_ops;

/*****/

अटल व्योम async_ctrl_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req = (काष्ठा usb_ctrlrequest *)urb->context;
	पूर्णांक status = urb->status;

	अगर (status < 0)
		dev_dbg(&urb->dev->dev, "%s failed with %d", __func__, status);
	kमुक्त(req);
	usb_मुक्त_urb(urb);
पूर्ण

अटल पूर्णांक get_रेजिस्टरs(pegasus_t *pegasus, __u16 indx, __u16 size, व्योम *data)
अणु
	वापस usb_control_msg_recv(pegasus->usb, 0, PEGASUS_REQ_GET_REGS,
				   PEGASUS_REQT_READ, 0, indx, data, size,
				   1000, GFP_NOIO);
पूर्ण

अटल पूर्णांक set_रेजिस्टरs(pegasus_t *pegasus, __u16 indx, __u16 size,
			 स्थिर व्योम *data)
अणु
	वापस usb_control_msg_send(pegasus->usb, 0, PEGASUS_REQ_SET_REGS,
				    PEGASUS_REQT_WRITE, 0, indx, data, size,
				    1000, GFP_NOIO);
पूर्ण

/*
 * There is only one way to ग_लिखो to a single ADM8511 रेजिस्टर and this is via
 * specअगरic control request.  'data' is ignored by the device, but it is here to
 * not अवरोध the API.
 */
अटल पूर्णांक set_रेजिस्टर(pegasus_t *pegasus, __u16 indx, __u8 data)
अणु
	व्योम *buf = &data;

	वापस usb_control_msg_send(pegasus->usb, 0, PEGASUS_REQ_SET_REG,
				    PEGASUS_REQT_WRITE, data, indx, buf, 1,
				    1000, GFP_NOIO);
पूर्ण

अटल पूर्णांक update_eth_regs_async(pegasus_t *pegasus)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा urb *async_urb;
	काष्ठा usb_ctrlrequest *req;

	req = kदो_स्मृति(माप(काष्ठा usb_ctrlrequest), GFP_ATOMIC);
	अगर (req == शून्य)
		वापस ret;

	async_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (async_urb == शून्य) अणु
		kमुक्त(req);
		वापस ret;
	पूर्ण
	req->bRequestType = PEGASUS_REQT_WRITE;
	req->bRequest = PEGASUS_REQ_SET_REGS;
	req->wValue = cpu_to_le16(0);
	req->wIndex = cpu_to_le16(EthCtrl0);
	req->wLength = cpu_to_le16(3);

	usb_fill_control_urb(async_urb, pegasus->usb,
			     usb_sndctrlpipe(pegasus->usb, 0), (व्योम *)req,
			     pegasus->eth_regs, 3, async_ctrl_callback, req);

	ret = usb_submit_urb(async_urb, GFP_ATOMIC);
	अगर (ret) अणु
		अगर (ret == -ENODEV)
			netअगर_device_detach(pegasus->net);
		netअगर_err(pegasus, drv, pegasus->net,
			  "%s returned %d\n", __func__, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __mii_op(pegasus_t *p, __u8 phy, __u8 indx, __u16 *regd, __u8 cmd)
अणु
	पूर्णांक i;
	__u8 data[4] = अणु phy, 0, 0, indx पूर्ण;
	__le16 regdi;
	पूर्णांक ret = -ETIMEDOUT;

	अगर (cmd & PHY_WRITE) अणु
		__le16 *t = (__le16 *) & data[1];
		*t = cpu_to_le16(*regd);
	पूर्ण
	set_रेजिस्टर(p, PhyCtrl, 0);
	set_रेजिस्टरs(p, PhyAddr, माप(data), data);
	set_रेजिस्टर(p, PhyCtrl, (indx | cmd));
	क्रम (i = 0; i < REG_TIMEOUT; i++) अणु
		ret = get_रेजिस्टरs(p, PhyCtrl, 1, data);
		अगर (ret < 0)
			जाओ fail;
		अगर (data[0] & PHY_DONE)
			अवरोध;
	पूर्ण
	अगर (i >= REG_TIMEOUT)
		जाओ fail;
	अगर (cmd & PHY_READ) अणु
		ret = get_रेजिस्टरs(p, PhyData, 2, &regdi);
		*regd = le16_to_cpu(regdi);
		वापस ret;
	पूर्ण
	वापस 0;
fail:
	netअगर_dbg(p, drv, p->net, "%s failed\n", __func__);
	वापस ret;
पूर्ण

/* Returns non-negative पूर्णांक on success, error on failure */
अटल पूर्णांक पढ़ो_mii_word(pegasus_t *pegasus, __u8 phy, __u8 indx, __u16 *regd)
अणु
	वापस __mii_op(pegasus, phy, indx, regd, PHY_READ);
पूर्ण

/* Returns zero on success, error on failure */
अटल पूर्णांक ग_लिखो_mii_word(pegasus_t *pegasus, __u8 phy, __u8 indx, __u16 *regd)
अणु
	वापस __mii_op(pegasus, phy, indx, regd, PHY_WRITE);
पूर्ण

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक loc)
अणु
	pegasus_t *pegasus = netdev_priv(dev);
	u16 res;

	पढ़ो_mii_word(pegasus, phy_id, loc, &res);
	वापस (पूर्णांक)res;
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक val)
अणु
	pegasus_t *pegasus = netdev_priv(dev);
	u16 data = val;

	ग_लिखो_mii_word(pegasus, phy_id, loc, &data);
पूर्ण

अटल पूर्णांक पढ़ो_eprom_word(pegasus_t *pegasus, __u8 index, __u16 *retdata)
अणु
	पूर्णांक i;
	__u8 पंचांगp = 0;
	__le16 retdatai;
	पूर्णांक ret;

	set_रेजिस्टर(pegasus, EpromCtrl, 0);
	set_रेजिस्टर(pegasus, EpromOffset, index);
	set_रेजिस्टर(pegasus, EpromCtrl, EPROM_READ);

	क्रम (i = 0; i < REG_TIMEOUT; i++) अणु
		ret = get_रेजिस्टरs(pegasus, EpromCtrl, 1, &पंचांगp);
		अगर (पंचांगp & EPROM_DONE)
			अवरोध;
		अगर (ret == -ESHUTDOWN)
			जाओ fail;
	पूर्ण
	अगर (i >= REG_TIMEOUT)
		जाओ fail;

	ret = get_रेजिस्टरs(pegasus, EpromData, 2, &retdatai);
	*retdata = le16_to_cpu(retdatai);
	वापस ret;

fail:
	netअगर_warn(pegasus, drv, pegasus->net, "%s failed\n", __func__);
	वापस -ETIMEDOUT;
पूर्ण

#अगर_घोषित	PEGASUS_WRITE_EEPROM
अटल अंतरभूत व्योम enable_eprom_ग_लिखो(pegasus_t *pegasus)
अणु
	__u8 पंचांगp;

	get_रेजिस्टरs(pegasus, EthCtrl2, 1, &पंचांगp);
	set_रेजिस्टर(pegasus, EthCtrl2, पंचांगp | EPROM_WR_ENABLE);
पूर्ण

अटल अंतरभूत व्योम disable_eprom_ग_लिखो(pegasus_t *pegasus)
अणु
	__u8 पंचांगp;

	get_रेजिस्टरs(pegasus, EthCtrl2, 1, &पंचांगp);
	set_रेजिस्टर(pegasus, EpromCtrl, 0);
	set_रेजिस्टर(pegasus, EthCtrl2, पंचांगp & ~EPROM_WR_ENABLE);
पूर्ण

अटल पूर्णांक ग_लिखो_eprom_word(pegasus_t *pegasus, __u8 index, __u16 data)
अणु
	पूर्णांक i;
	__u8 पंचांगp, d[4] = अणु 0x3f, 0, 0, EPROM_WRITE पूर्ण;
	पूर्णांक ret;
	__le16 le_data = cpu_to_le16(data);

	set_रेजिस्टरs(pegasus, EpromOffset, 4, d);
	enable_eprom_ग_लिखो(pegasus);
	set_रेजिस्टर(pegasus, EpromOffset, index);
	set_रेजिस्टरs(pegasus, EpromData, 2, &le_data);
	set_रेजिस्टर(pegasus, EpromCtrl, EPROM_WRITE);

	क्रम (i = 0; i < REG_TIMEOUT; i++) अणु
		ret = get_रेजिस्टरs(pegasus, EpromCtrl, 1, &पंचांगp);
		अगर (ret == -ESHUTDOWN)
			जाओ fail;
		अगर (पंचांगp & EPROM_DONE)
			अवरोध;
	पूर्ण
	disable_eprom_ग_लिखो(pegasus);
	अगर (i >= REG_TIMEOUT)
		जाओ fail;

	वापस ret;

fail:
	netअगर_warn(pegasus, drv, pegasus->net, "%s failed\n", __func__);
	वापस -ETIMEDOUT;
पूर्ण
#पूर्ण_अगर				/* PEGASUS_WRITE_EEPROM */

अटल अंतरभूत पूर्णांक get_node_id(pegasus_t *pegasus, u8 *id)
अणु
	पूर्णांक i, ret;
	u16 w16;

	क्रम (i = 0; i < 3; i++) अणु
		ret = पढ़ो_eprom_word(pegasus, i, &w16);
		अगर (ret < 0)
			वापस ret;
		((__le16 *) id)[i] = cpu_to_le16(w16);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_ethernet_addr(pegasus_t *pegasus)
अणु
	पूर्णांक ret;
	u8 node_id[6];

	अगर (pegasus->features & PEGASUS_II) अणु
		ret = get_रेजिस्टरs(pegasus, 0x10, माप(node_id), node_id);
		अगर (ret < 0)
			जाओ err;
	पूर्ण अन्यथा अणु
		ret = get_node_id(pegasus, node_id);
		अगर (ret < 0)
			जाओ err;
		ret = set_रेजिस्टरs(pegasus, EthID, माप(node_id), node_id);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	स_नकल(pegasus->net->dev_addr, node_id, माप(node_id));

	वापस;
err:
	eth_hw_addr_अक्रमom(pegasus->net);
	dev_info(&pegasus->पूर्णांकf->dev, "software assigned MAC address.\n");

	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक reset_mac(pegasus_t *pegasus)
अणु
	__u8 data = 0x8;
	पूर्णांक i;

	set_रेजिस्टर(pegasus, EthCtrl1, data);
	क्रम (i = 0; i < REG_TIMEOUT; i++) अणु
		get_रेजिस्टरs(pegasus, EthCtrl1, 1, &data);
		अगर (~data & 0x08) अणु
			अगर (loopback)
				अवरोध;
			अगर (mii_mode && (pegasus->features & HAS_HOME_PNA))
				set_रेजिस्टर(pegasus, Gpio1, 0x34);
			अन्यथा
				set_रेजिस्टर(pegasus, Gpio1, 0x26);
			set_रेजिस्टर(pegasus, Gpio0, pegasus->features);
			set_रेजिस्टर(pegasus, Gpio0, DEFAULT_GPIO_SET);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == REG_TIMEOUT)
		वापस -ETIMEDOUT;

	अगर (usb_dev_id[pegasus->dev_index].venकरोr == VENDOR_LINKSYS ||
	    usb_dev_id[pegasus->dev_index].venकरोr == VENDOR_DLINK) अणु
		set_रेजिस्टर(pegasus, Gpio0, 0x24);
		set_रेजिस्टर(pegasus, Gpio0, 0x26);
	पूर्ण
	अगर (usb_dev_id[pegasus->dev_index].venकरोr == VENDOR_ELCON) अणु
		__u16 auxmode;
		पढ़ो_mii_word(pegasus, 3, 0x1b, &auxmode);
		auxmode |= 4;
		ग_लिखो_mii_word(pegasus, 3, 0x1b, &auxmode);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enable_net_traffic(काष्ठा net_device *dev, काष्ठा usb_device *usb)
अणु
	__u16 linkpart;
	__u8 data[4];
	pegasus_t *pegasus = netdev_priv(dev);
	पूर्णांक ret;

	पढ़ो_mii_word(pegasus, pegasus->phy, MII_LPA, &linkpart);
	data[0] = 0xc8; /* TX & RX enable, append status, no CRC */
	data[1] = 0;
	अगर (linkpart & (ADVERTISE_100FULL | ADVERTISE_10FULL))
		data[1] |= 0x20;	/* set full duplex */
	अगर (linkpart & (ADVERTISE_100FULL | ADVERTISE_100HALF))
		data[1] |= 0x10;	/* set 100 Mbps */
	अगर (mii_mode)
		data[1] = 0;
	data[2] = loopback ? 0x09 : 0x01;

	स_नकल(pegasus->eth_regs, data, माप(data));
	ret = set_रेजिस्टरs(pegasus, EthCtrl0, 3, data);

	अगर (usb_dev_id[pegasus->dev_index].venकरोr == VENDOR_LINKSYS ||
	    usb_dev_id[pegasus->dev_index].venकरोr == VENDOR_LINKSYS2 ||
	    usb_dev_id[pegasus->dev_index].venकरोr == VENDOR_DLINK) अणु
		u16 auxmode;
		पढ़ो_mii_word(pegasus, 0, 0x1b, &auxmode);
		auxmode |= 4;
		ग_लिखो_mii_word(pegasus, 0, 0x1b, &auxmode);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	pegasus_t *pegasus = urb->context;
	काष्ठा net_device *net;
	पूर्णांक rx_status, count = urb->actual_length;
	पूर्णांक status = urb->status;
	u8 *buf = urb->transfer_buffer;
	__u16 pkt_len;

	अगर (!pegasus)
		वापस;

	net = pegasus->net;
	अगर (!netअगर_device_present(net) || !netअगर_running(net))
		वापस;

	चयन (status) अणु
	हाल 0:
		अवरोध;
	हाल -ETIME:
		netअगर_dbg(pegasus, rx_err, net, "reset MAC\n");
		pegasus->flags &= ~PEGASUS_RX_BUSY;
		अवरोध;
	हाल -EPIPE:		/* stall, or disconnect from TT */
		/* FIXME schedule work to clear the halt */
		netअगर_warn(pegasus, rx_err, net, "no rx stall recovery\n");
		वापस;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		netअगर_dbg(pegasus, अगरकरोwn, net, "rx unlink, %d\n", status);
		वापस;
	शेष:
		netअगर_dbg(pegasus, rx_err, net, "RX status %d\n", status);
		जाओ goon;
	पूर्ण

	अगर (count < 4)
		जाओ goon;

	rx_status = buf[count - 2];
	अगर (rx_status & 0x1e) अणु
		netअगर_dbg(pegasus, rx_err, net,
			  "RX packet error %x\n", rx_status);
		net->stats.rx_errors++;
		अगर (rx_status & 0x06)	/* दीर्घ or runt	*/
			net->stats.rx_length_errors++;
		अगर (rx_status & 0x08)
			net->stats.rx_crc_errors++;
		अगर (rx_status & 0x10)	/* extra bits	*/
			net->stats.rx_frame_errors++;
		जाओ goon;
	पूर्ण
	अगर (pegasus->chip == 0x8513) अणु
		pkt_len = le32_to_cpu(*(__le32 *)urb->transfer_buffer);
		pkt_len &= 0x0fff;
		pegasus->rx_skb->data += 2;
	पूर्ण अन्यथा अणु
		pkt_len = buf[count - 3] << 8;
		pkt_len += buf[count - 4];
		pkt_len &= 0xfff;
		pkt_len -= 4;
	पूर्ण

	/*
	 * If the packet is unreasonably दीर्घ, quietly drop it rather than
	 * kernel panicing by calling skb_put.
	 */
	अगर (pkt_len > PEGASUS_MTU)
		जाओ goon;

	/*
	 * at this poपूर्णांक we are sure pegasus->rx_skb != शून्य
	 * so we go ahead and pass up the packet.
	 */
	skb_put(pegasus->rx_skb, pkt_len);
	pegasus->rx_skb->protocol = eth_type_trans(pegasus->rx_skb, net);
	netअगर_rx(pegasus->rx_skb);
	net->stats.rx_packets++;
	net->stats.rx_bytes += pkt_len;

	अगर (pegasus->flags & PEGASUS_UNPLUG)
		वापस;

	pegasus->rx_skb = __netdev_alloc_skb_ip_align(pegasus->net, PEGASUS_MTU,
						      GFP_ATOMIC);

	अगर (pegasus->rx_skb == शून्य)
		जाओ tl_sched;
goon:
	usb_fill_bulk_urb(pegasus->rx_urb, pegasus->usb,
			  usb_rcvbulkpipe(pegasus->usb, 1),
			  pegasus->rx_skb->data, PEGASUS_MTU,
			  पढ़ो_bulk_callback, pegasus);
	rx_status = usb_submit_urb(pegasus->rx_urb, GFP_ATOMIC);
	अगर (rx_status == -ENODEV)
		netअगर_device_detach(pegasus->net);
	अन्यथा अगर (rx_status) अणु
		pegasus->flags |= PEGASUS_RX_URB_FAIL;
		जाओ tl_sched;
	पूर्ण अन्यथा अणु
		pegasus->flags &= ~PEGASUS_RX_URB_FAIL;
	पूर्ण

	वापस;

tl_sched:
	tasklet_schedule(&pegasus->rx_tl);
पूर्ण

अटल व्योम rx_fixup(काष्ठा tasklet_काष्ठा *t)
अणु
	pegasus_t *pegasus = from_tasklet(pegasus, t, rx_tl);
	पूर्णांक status;

	अगर (pegasus->flags & PEGASUS_UNPLUG)
		वापस;

	अगर (pegasus->flags & PEGASUS_RX_URB_FAIL)
		अगर (pegasus->rx_skb)
			जाओ try_again;
	अगर (pegasus->rx_skb == शून्य)
		pegasus->rx_skb = __netdev_alloc_skb_ip_align(pegasus->net,
							      PEGASUS_MTU,
							      GFP_ATOMIC);
	अगर (pegasus->rx_skb == शून्य) अणु
		netअगर_warn(pegasus, rx_err, pegasus->net, "low on memory\n");
		tasklet_schedule(&pegasus->rx_tl);
		वापस;
	पूर्ण
	usb_fill_bulk_urb(pegasus->rx_urb, pegasus->usb,
			  usb_rcvbulkpipe(pegasus->usb, 1),
			  pegasus->rx_skb->data, PEGASUS_MTU,
			  पढ़ो_bulk_callback, pegasus);
try_again:
	status = usb_submit_urb(pegasus->rx_urb, GFP_ATOMIC);
	अगर (status == -ENODEV)
		netअगर_device_detach(pegasus->net);
	अन्यथा अगर (status) अणु
		pegasus->flags |= PEGASUS_RX_URB_FAIL;
		tasklet_schedule(&pegasus->rx_tl);
	पूर्ण अन्यथा अणु
		pegasus->flags &= ~PEGASUS_RX_URB_FAIL;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	pegasus_t *pegasus = urb->context;
	काष्ठा net_device *net;
	पूर्णांक status = urb->status;

	अगर (!pegasus)
		वापस;

	net = pegasus->net;

	अगर (!netअगर_device_present(net) || !netअगर_running(net))
		वापस;

	चयन (status) अणु
	हाल -EPIPE:
		/* FIXME schedule_work() to clear the tx halt */
		netअगर_stop_queue(net);
		netअगर_warn(pegasus, tx_err, net, "no tx stall recovery\n");
		वापस;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		netअगर_dbg(pegasus, अगरकरोwn, net, "tx unlink, %d\n", status);
		वापस;
	शेष:
		netअगर_info(pegasus, tx_err, net, "TX status %d\n", status);
		fallthrough;
	हाल 0:
		अवरोध;
	पूर्ण

	netअगर_trans_update(net); /* prevent tx समयout */
	netअगर_wake_queue(net);
पूर्ण

अटल व्योम पूर्णांकr_callback(काष्ठा urb *urb)
अणु
	pegasus_t *pegasus = urb->context;
	काष्ठा net_device *net;
	पूर्णांक res, status = urb->status;

	अगर (!pegasus)
		वापस;
	net = pegasus->net;

	चयन (status) अणु
	हाल 0:
		अवरोध;
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:
		/* some Pegasus-I products report LOTS of data
		 * toggle errors... aव्योम log spamming
		 */
		netअगर_dbg(pegasus, समयr, net, "intr status %d\n", status);
	पूर्ण

	अगर (urb->actual_length >= 6) अणु
		u8 *d = urb->transfer_buffer;

		/* byte 0 == tx_status1, reg 2B */
		अगर (d[0] & (TX_UNDERRUN|EXCESSIVE_COL
					|LATE_COL|JABBER_TIMEOUT)) अणु
			net->stats.tx_errors++;
			अगर (d[0] & TX_UNDERRUN)
				net->stats.tx_fअगरo_errors++;
			अगर (d[0] & (EXCESSIVE_COL | JABBER_TIMEOUT))
				net->stats.tx_पातed_errors++;
			अगर (d[0] & LATE_COL)
				net->stats.tx_winकरोw_errors++;
		पूर्ण

		/* d[5].LINK_STATUS lies on some adapters.
		 * d[0].NO_CARRIER kicks in only with failed TX.
		 * ... so monitoring with MII may be safest.
		 */

		/* bytes 3-4 == rx_lostpkt, reg 2E/2F */
		net->stats.rx_missed_errors += ((d[3] & 0x7f) << 8) | d[4];
	पूर्ण

	res = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (res == -ENODEV)
		netअगर_device_detach(pegasus->net);
	अगर (res)
		netअगर_err(pegasus, समयr, net,
			  "can't resubmit interrupt urb, %d\n", res);
पूर्ण

अटल व्योम pegasus_tx_समयout(काष्ठा net_device *net, अचिन्हित पूर्णांक txqueue)
अणु
	pegasus_t *pegasus = netdev_priv(net);
	netअगर_warn(pegasus, समयr, net, "tx timeout\n");
	usb_unlink_urb(pegasus->tx_urb);
	net->stats.tx_errors++;
पूर्ण

अटल netdev_tx_t pegasus_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *net)
अणु
	pegasus_t *pegasus = netdev_priv(net);
	पूर्णांक count = ((skb->len + 2) & 0x3f) ? skb->len + 2 : skb->len + 3;
	पूर्णांक res;
	__u16 l16 = skb->len;

	netअगर_stop_queue(net);

	((__le16 *) pegasus->tx_buff)[0] = cpu_to_le16(l16);
	skb_copy_from_linear_data(skb, pegasus->tx_buff + 2, skb->len);
	usb_fill_bulk_urb(pegasus->tx_urb, pegasus->usb,
			  usb_sndbulkpipe(pegasus->usb, 2),
			  pegasus->tx_buff, count,
			  ग_लिखो_bulk_callback, pegasus);
	अगर ((res = usb_submit_urb(pegasus->tx_urb, GFP_ATOMIC))) अणु
		netअगर_warn(pegasus, tx_err, net, "fail tx, %d\n", res);
		चयन (res) अणु
		हाल -EPIPE:		/* stall, or disconnect from TT */
			/* cleanup should alपढ़ोy have been scheduled */
			अवरोध;
		हाल -ENODEV:		/* disconnect() upcoming */
		हाल -EPERM:
			netअगर_device_detach(pegasus->net);
			अवरोध;
		शेष:
			net->stats.tx_errors++;
			netअगर_start_queue(net);
		पूर्ण
	पूर्ण अन्यथा अणु
		net->stats.tx_packets++;
		net->stats.tx_bytes += skb->len;
	पूर्ण
	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल अंतरभूत व्योम disable_net_traffic(pegasus_t *pegasus)
अणु
	__le16 पंचांगp = cpu_to_le16(0);

	set_रेजिस्टरs(pegasus, EthCtrl0, माप(पंचांगp), &पंचांगp);
पूर्ण

अटल अंतरभूत व्योम get_पूर्णांकerrupt_पूर्णांकerval(pegasus_t *pegasus)
अणु
	u16 data;
	u8 पूर्णांकerval;

	पढ़ो_eprom_word(pegasus, 4, &data);
	पूर्णांकerval = data >> 8;
	अगर (pegasus->usb->speed != USB_SPEED_HIGH) अणु
		अगर (पूर्णांकerval < 0x80) अणु
			netअगर_info(pegasus, समयr, pegasus->net,
				   "intr interval changed from %ums to %ums\n",
				   पूर्णांकerval, 0x80);
			पूर्णांकerval = 0x80;
			data = (data & 0x00FF) | ((u16)पूर्णांकerval << 8);
#अगर_घोषित PEGASUS_WRITE_EEPROM
			ग_लिखो_eprom_word(pegasus, 4, data);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	pegasus->पूर्णांकr_पूर्णांकerval = पूर्णांकerval;
पूर्ण

अटल व्योम set_carrier(काष्ठा net_device *net)
अणु
	pegasus_t *pegasus = netdev_priv(net);
	u16 पंचांगp;

	अगर (पढ़ो_mii_word(pegasus, pegasus->phy, MII_BMSR, &पंचांगp))
		वापस;

	अगर (पंचांगp & BMSR_LSTATUS)
		netअगर_carrier_on(net);
	अन्यथा
		netअगर_carrier_off(net);
पूर्ण

अटल व्योम मुक्त_all_urbs(pegasus_t *pegasus)
अणु
	usb_मुक्त_urb(pegasus->पूर्णांकr_urb);
	usb_मुक्त_urb(pegasus->tx_urb);
	usb_मुक्त_urb(pegasus->rx_urb);
पूर्ण

अटल व्योम unlink_all_urbs(pegasus_t *pegasus)
अणु
	usb_समाप्त_urb(pegasus->पूर्णांकr_urb);
	usb_समाप्त_urb(pegasus->tx_urb);
	usb_समाप्त_urb(pegasus->rx_urb);
पूर्ण

अटल पूर्णांक alloc_urbs(pegasus_t *pegasus)
अणु
	पूर्णांक res = -ENOMEM;

	pegasus->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pegasus->rx_urb) अणु
		वापस res;
	पूर्ण
	pegasus->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pegasus->tx_urb) अणु
		usb_मुक्त_urb(pegasus->rx_urb);
		वापस res;
	पूर्ण
	pegasus->पूर्णांकr_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pegasus->पूर्णांकr_urb) अणु
		usb_मुक्त_urb(pegasus->tx_urb);
		usb_मुक्त_urb(pegasus->rx_urb);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pegasus_खोलो(काष्ठा net_device *net)
अणु
	pegasus_t *pegasus = netdev_priv(net);
	पूर्णांक res=-ENOMEM;

	अगर (pegasus->rx_skb == शून्य)
		pegasus->rx_skb = __netdev_alloc_skb_ip_align(pegasus->net,
							      PEGASUS_MTU,
							      GFP_KERNEL);
	अगर (!pegasus->rx_skb)
		जाओ निकास;

	res = set_रेजिस्टरs(pegasus, EthID, 6, net->dev_addr);

	usb_fill_bulk_urb(pegasus->rx_urb, pegasus->usb,
			  usb_rcvbulkpipe(pegasus->usb, 1),
			  pegasus->rx_skb->data, PEGASUS_MTU,
			  पढ़ो_bulk_callback, pegasus);
	अगर ((res = usb_submit_urb(pegasus->rx_urb, GFP_KERNEL))) अणु
		अगर (res == -ENODEV)
			netअगर_device_detach(pegasus->net);
		netअगर_dbg(pegasus, अगरup, net, "failed rx_urb, %d\n", res);
		जाओ निकास;
	पूर्ण

	usb_fill_पूर्णांक_urb(pegasus->पूर्णांकr_urb, pegasus->usb,
			 usb_rcvपूर्णांकpipe(pegasus->usb, 3),
			 pegasus->पूर्णांकr_buff, माप(pegasus->पूर्णांकr_buff),
			 पूर्णांकr_callback, pegasus, pegasus->पूर्णांकr_पूर्णांकerval);
	अगर ((res = usb_submit_urb(pegasus->पूर्णांकr_urb, GFP_KERNEL))) अणु
		अगर (res == -ENODEV)
			netअगर_device_detach(pegasus->net);
		netअगर_dbg(pegasus, अगरup, net, "failed intr_urb, %d\n", res);
		usb_समाप्त_urb(pegasus->rx_urb);
		जाओ निकास;
	पूर्ण
	res = enable_net_traffic(net, pegasus->usb);
	अगर (res < 0) अणु
		netअगर_dbg(pegasus, अगरup, net,
			  "can't enable_net_traffic() - %d\n", res);
		res = -EIO;
		usb_समाप्त_urb(pegasus->rx_urb);
		usb_समाप्त_urb(pegasus->पूर्णांकr_urb);
		जाओ निकास;
	पूर्ण
	set_carrier(net);
	netअगर_start_queue(net);
	netअगर_dbg(pegasus, अगरup, net, "open\n");
	res = 0;
निकास:
	वापस res;
पूर्ण

अटल पूर्णांक pegasus_बंद(काष्ठा net_device *net)
अणु
	pegasus_t *pegasus = netdev_priv(net);

	netअगर_stop_queue(net);
	अगर (!(pegasus->flags & PEGASUS_UNPLUG))
		disable_net_traffic(pegasus);
	tasklet_समाप्त(&pegasus->rx_tl);
	unlink_all_urbs(pegasus);

	वापस 0;
पूर्ण

अटल व्योम pegasus_get_drvinfo(काष्ठा net_device *dev,
				काष्ठा ethtool_drvinfo *info)
अणु
	pegasus_t *pegasus = netdev_priv(dev);

	strlcpy(info->driver, driver_name, माप(info->driver));
	strlcpy(info->version, DRIVER_VERSION, माप(info->version));
	usb_make_path(pegasus->usb, info->bus_info, माप(info->bus_info));
पूर्ण

/* also handles three patterns of some kind in hardware */
#घोषणा	WOL_SUPPORTED	(WAKE_MAGIC|WAKE_PHY)

अटल व्योम
pegasus_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	pegasus_t	*pegasus = netdev_priv(dev);

	wol->supported = WAKE_MAGIC | WAKE_PHY;
	wol->wolopts = pegasus->wolopts;
पूर्ण

अटल पूर्णांक
pegasus_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	pegasus_t	*pegasus = netdev_priv(dev);
	u8		reg78 = 0x04;
	पूर्णांक		ret;

	अगर (wol->wolopts & ~WOL_SUPPORTED)
		वापस -EINVAL;

	अगर (wol->wolopts & WAKE_MAGIC)
		reg78 |= 0x80;
	अगर (wol->wolopts & WAKE_PHY)
		reg78 |= 0x40;
	/* FIXME this 0x10 bit still needs to get set in the chip... */
	अगर (wol->wolopts)
		pegasus->eth_regs[0] |= 0x10;
	अन्यथा
		pegasus->eth_regs[0] &= ~0x10;
	pegasus->wolopts = wol->wolopts;

	ret = set_रेजिस्टर(pegasus, WakeupControl, reg78);
	अगर (!ret)
		ret = device_set_wakeup_enable(&pegasus->usb->dev,
						wol->wolopts);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम pegasus_reset_wol(काष्ठा net_device *dev)
अणु
	काष्ठा ethtool_wolinfo wol;

	स_रखो(&wol, 0, माप wol);
	(व्योम) pegasus_set_wol(dev, &wol);
पूर्ण

अटल पूर्णांक
pegasus_get_link_ksettings(काष्ठा net_device *dev,
			   काष्ठा ethtool_link_ksettings *ecmd)
अणु
	pegasus_t *pegasus;

	pegasus = netdev_priv(dev);
	mii_ethtool_get_link_ksettings(&pegasus->mii, ecmd);
	वापस 0;
पूर्ण

अटल पूर्णांक
pegasus_set_link_ksettings(काष्ठा net_device *dev,
			   स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	pegasus_t *pegasus = netdev_priv(dev);
	वापस mii_ethtool_set_link_ksettings(&pegasus->mii, ecmd);
पूर्ण

अटल पूर्णांक pegasus_nway_reset(काष्ठा net_device *dev)
अणु
	pegasus_t *pegasus = netdev_priv(dev);
	वापस mii_nway_restart(&pegasus->mii);
पूर्ण

अटल u32 pegasus_get_link(काष्ठा net_device *dev)
अणु
	pegasus_t *pegasus = netdev_priv(dev);
	वापस mii_link_ok(&pegasus->mii);
पूर्ण

अटल u32 pegasus_get_msglevel(काष्ठा net_device *dev)
अणु
	pegasus_t *pegasus = netdev_priv(dev);
	वापस pegasus->msg_enable;
पूर्ण

अटल व्योम pegasus_set_msglevel(काष्ठा net_device *dev, u32 v)
अणु
	pegasus_t *pegasus = netdev_priv(dev);
	pegasus->msg_enable = v;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_drvinfo = pegasus_get_drvinfo,
	.nway_reset = pegasus_nway_reset,
	.get_link = pegasus_get_link,
	.get_msglevel = pegasus_get_msglevel,
	.set_msglevel = pegasus_set_msglevel,
	.get_wol = pegasus_get_wol,
	.set_wol = pegasus_set_wol,
	.get_link_ksettings = pegasus_get_link_ksettings,
	.set_link_ksettings = pegasus_set_link_ksettings,
पूर्ण;

अटल पूर्णांक pegasus_ioctl(काष्ठा net_device *net, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	__u16 *data = (__u16 *) &rq->अगरr_अगरru;
	pegasus_t *pegasus = netdev_priv(net);
	पूर्णांक res;

	चयन (cmd) अणु
	हाल SIOCDEVPRIVATE:
		data[0] = pegasus->phy;
		fallthrough;
	हाल SIOCDEVPRIVATE + 1:
		पढ़ो_mii_word(pegasus, data[0], data[1] & 0x1f, &data[3]);
		res = 0;
		अवरोध;
	हाल SIOCDEVPRIVATE + 2:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		ग_लिखो_mii_word(pegasus, pegasus->phy, data[1] & 0x1f, &data[2]);
		res = 0;
		अवरोध;
	शेष:
		res = -EOPNOTSUPP;
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम pegasus_set_multicast(काष्ठा net_device *net)
अणु
	pegasus_t *pegasus = netdev_priv(net);

	अगर (net->flags & IFF_PROMISC) अणु
		pegasus->eth_regs[EthCtrl2] |= RX_PROMISCUOUS;
		netअगर_info(pegasus, link, net, "Promiscuous mode enabled\n");
	पूर्ण अन्यथा अगर (!netdev_mc_empty(net) || (net->flags & IFF_ALLMULTI)) अणु
		pegasus->eth_regs[EthCtrl0] |= RX_MULTICAST;
		pegasus->eth_regs[EthCtrl2] &= ~RX_PROMISCUOUS;
		netअगर_dbg(pegasus, link, net, "set allmulti\n");
	पूर्ण अन्यथा अणु
		pegasus->eth_regs[EthCtrl0] &= ~RX_MULTICAST;
		pegasus->eth_regs[EthCtrl2] &= ~RX_PROMISCUOUS;
	पूर्ण
	update_eth_regs_async(pegasus);
पूर्ण

अटल __u8 mii_phy_probe(pegasus_t *pegasus)
अणु
	पूर्णांक i;
	__u16 पंचांगp;

	क्रम (i = 0; i < 32; i++) अणु
		पढ़ो_mii_word(pegasus, i, MII_BMSR, &पंचांगp);
		अगर (पंचांगp == 0 || पंचांगp == 0xffff || (पंचांगp & BMSR_MEDIA) == 0)
			जारी;
		अन्यथा
			वापस i;
	पूर्ण

	वापस 0xff;
पूर्ण

अटल अंतरभूत व्योम setup_pegasus_II(pegasus_t *pegasus)
अणु
	__u8 data = 0xa5;

	set_रेजिस्टर(pegasus, Reg1d, 0);
	set_रेजिस्टर(pegasus, Reg7b, 1);
	msleep(100);
	अगर ((pegasus->features & HAS_HOME_PNA) && mii_mode)
		set_रेजिस्टर(pegasus, Reg7b, 0);
	अन्यथा
		set_रेजिस्टर(pegasus, Reg7b, 2);

	set_रेजिस्टर(pegasus, 0x83, data);
	get_रेजिस्टरs(pegasus, 0x83, 1, &data);

	अगर (data == 0xa5)
		pegasus->chip = 0x8513;
	अन्यथा
		pegasus->chip = 0;

	set_रेजिस्टर(pegasus, 0x80, 0xc0);
	set_रेजिस्टर(pegasus, 0x83, 0xff);
	set_रेजिस्टर(pegasus, 0x84, 0x01);

	अगर (pegasus->features & HAS_HOME_PNA && mii_mode)
		set_रेजिस्टर(pegasus, Reg81, 6);
	अन्यथा
		set_रेजिस्टर(pegasus, Reg81, 2);
पूर्ण

अटल व्योम check_carrier(काष्ठा work_काष्ठा *work)
अणु
	pegasus_t *pegasus = container_of(work, pegasus_t, carrier_check.work);
	set_carrier(pegasus->net);
	अगर (!(pegasus->flags & PEGASUS_UNPLUG)) अणु
		queue_delayed_work(प्रणाली_दीर्घ_wq, &pegasus->carrier_check,
			CARRIER_CHECK_DELAY);
	पूर्ण
पूर्ण

अटल पूर्णांक pegasus_blacklisted(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_device_descriptor *udd = &udev->descriptor;

	/* Special quirk to keep the driver from handling the Belkin Bluetooth
	 * करोngle which happens to have the same ID.
	 */
	अगर ((udd->idVenकरोr == cpu_to_le16(VENDOR_BELKIN)) &&
	    (udd->idProduct == cpu_to_le16(0x0121)) &&
	    (udd->bDeviceClass == USB_CLASS_WIRELESS_CONTROLLER) &&
	    (udd->bDeviceProtocol == 1))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pegasus_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा net_device *net;
	pegasus_t *pegasus;
	पूर्णांक dev_index = id - pegasus_ids;
	पूर्णांक res = -ENOMEM;

	अगर (pegasus_blacklisted(dev))
		वापस -ENODEV;

	net = alloc_etherdev(माप(काष्ठा pegasus));
	अगर (!net)
		जाओ out;

	pegasus = netdev_priv(net);
	pegasus->dev_index = dev_index;

	res = alloc_urbs(pegasus);
	अगर (res < 0) अणु
		dev_err(&पूर्णांकf->dev, "can't allocate %s\n", "urbs");
		जाओ out1;
	पूर्ण

	tasklet_setup(&pegasus->rx_tl, rx_fixup);

	INIT_DELAYED_WORK(&pegasus->carrier_check, check_carrier);

	pegasus->पूर्णांकf = पूर्णांकf;
	pegasus->usb = dev;
	pegasus->net = net;


	net->watchकरोg_समयo = PEGASUS_TX_TIMEOUT;
	net->netdev_ops = &pegasus_netdev_ops;
	net->ethtool_ops = &ops;
	pegasus->mii.dev = net;
	pegasus->mii.mdio_पढ़ो = mdio_पढ़ो;
	pegasus->mii.mdio_ग_लिखो = mdio_ग_लिखो;
	pegasus->mii.phy_id_mask = 0x1f;
	pegasus->mii.reg_num_mask = 0x1f;
	pegasus->msg_enable = netअगर_msg_init(msg_level, NETIF_MSG_DRV
				| NETIF_MSG_PROBE | NETIF_MSG_LINK);

	pegasus->features = usb_dev_id[dev_index].निजी;
	get_पूर्णांकerrupt_पूर्णांकerval(pegasus);
	अगर (reset_mac(pegasus)) अणु
		dev_err(&पूर्णांकf->dev, "can't reset MAC\n");
		res = -EIO;
		जाओ out2;
	पूर्ण
	set_ethernet_addr(pegasus);
	अगर (pegasus->features & PEGASUS_II) अणु
		dev_info(&पूर्णांकf->dev, "setup Pegasus II specific registers\n");
		setup_pegasus_II(pegasus);
	पूर्ण
	pegasus->phy = mii_phy_probe(pegasus);
	अगर (pegasus->phy == 0xff) अणु
		dev_warn(&पूर्णांकf->dev, "can't locate MII phy, using default\n");
		pegasus->phy = 1;
	पूर्ण
	pegasus->mii.phy_id = pegasus->phy;
	usb_set_पूर्णांकfdata(पूर्णांकf, pegasus);
	SET_NETDEV_DEV(net, &पूर्णांकf->dev);
	pegasus_reset_wol(net);
	res = रेजिस्टर_netdev(net);
	अगर (res)
		जाओ out3;
	queue_delayed_work(प्रणाली_दीर्घ_wq, &pegasus->carrier_check,
			   CARRIER_CHECK_DELAY);
	dev_info(&पूर्णांकf->dev, "%s, %s, %pM\n", net->name,
		 usb_dev_id[dev_index].name, net->dev_addr);
	वापस 0;

out3:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
out2:
	मुक्त_all_urbs(pegasus);
out1:
	मुक्त_netdev(net);
out:
	वापस res;
पूर्ण

अटल व्योम pegasus_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा pegasus *pegasus = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (!pegasus) अणु
		dev_dbg(&पूर्णांकf->dev, "unregistering non-bound device?\n");
		वापस;
	पूर्ण

	pegasus->flags |= PEGASUS_UNPLUG;
	cancel_delayed_work_sync(&pegasus->carrier_check);
	unरेजिस्टर_netdev(pegasus->net);
	unlink_all_urbs(pegasus);
	मुक्त_all_urbs(pegasus);
	अगर (pegasus->rx_skb != शून्य) अणु
		dev_kमुक्त_skb(pegasus->rx_skb);
		pegasus->rx_skb = शून्य;
	पूर्ण
	मुक्त_netdev(pegasus->net);
पूर्ण

अटल पूर्णांक pegasus_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा pegasus *pegasus = usb_get_पूर्णांकfdata(पूर्णांकf);

	netअगर_device_detach(pegasus->net);
	cancel_delayed_work_sync(&pegasus->carrier_check);
	अगर (netअगर_running(pegasus->net)) अणु
		usb_समाप्त_urb(pegasus->rx_urb);
		usb_समाप्त_urb(pegasus->पूर्णांकr_urb);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pegasus_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा pegasus *pegasus = usb_get_पूर्णांकfdata(पूर्णांकf);

	netअगर_device_attach(pegasus->net);
	अगर (netअगर_running(pegasus->net)) अणु
		pegasus->rx_urb->status = 0;
		pegasus->rx_urb->actual_length = 0;
		पढ़ो_bulk_callback(pegasus->rx_urb);

		pegasus->पूर्णांकr_urb->status = 0;
		pegasus->पूर्णांकr_urb->actual_length = 0;
		पूर्णांकr_callback(pegasus->पूर्णांकr_urb);
	पूर्ण
	queue_delayed_work(प्रणाली_दीर्घ_wq, &pegasus->carrier_check,
				CARRIER_CHECK_DELAY);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops pegasus_netdev_ops = अणु
	.nकरो_खोलो =			pegasus_खोलो,
	.nकरो_stop =			pegasus_बंद,
	.nकरो_करो_ioctl =			pegasus_ioctl,
	.nकरो_start_xmit =		pegasus_start_xmit,
	.nकरो_set_rx_mode =		pegasus_set_multicast,
	.nकरो_tx_समयout =		pegasus_tx_समयout,
	.nकरो_set_mac_address =		eth_mac_addr,
	.nकरो_validate_addr =		eth_validate_addr,
पूर्ण;

अटल काष्ठा usb_driver pegasus_driver = अणु
	.name = driver_name,
	.probe = pegasus_probe,
	.disconnect = pegasus_disconnect,
	.id_table = pegasus_ids,
	.suspend = pegasus_suspend,
	.resume = pegasus_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

अटल व्योम __init parse_id(अक्षर *id)
अणु
	अचिन्हित पूर्णांक venकरोr_id = 0, device_id = 0, flags = 0, i = 0;
	अक्षर *token, *name = शून्य;

	अगर ((token = strsep(&id, ":")) != शून्य)
		name = token;
	/* name now poपूर्णांकs to a null terminated string*/
	अगर ((token = strsep(&id, ":")) != शून्य)
		venकरोr_id = simple_म_से_अदीर्घ(token, शून्य, 16);
	अगर ((token = strsep(&id, ":")) != शून्य)
		device_id = simple_म_से_अदीर्घ(token, शून्य, 16);
	flags = simple_म_से_अदीर्घ(id, शून्य, 16);
	pr_info("%s: new device %s, vendor ID 0x%04x, device ID 0x%04x, flags: 0x%x\n",
		driver_name, name, venकरोr_id, device_id, flags);

	अगर (venकरोr_id > 0x10000 || venकरोr_id == 0)
		वापस;
	अगर (device_id > 0x10000 || device_id == 0)
		वापस;

	क्रम (i = 0; usb_dev_id[i].name; i++);
	usb_dev_id[i].name = name;
	usb_dev_id[i].venकरोr = venकरोr_id;
	usb_dev_id[i].device = device_id;
	usb_dev_id[i].निजी = flags;
	pegasus_ids[i].match_flags = USB_DEVICE_ID_MATCH_DEVICE;
	pegasus_ids[i].idVenकरोr = venकरोr_id;
	pegasus_ids[i].idProduct = device_id;
पूर्ण

अटल पूर्णांक __init pegasus_init(व्योम)
अणु
	pr_info("%s: %s, " DRIVER_DESC "\n", driver_name, DRIVER_VERSION);
	अगर (devid)
		parse_id(devid);
	वापस usb_रेजिस्टर(&pegasus_driver);
पूर्ण

अटल व्योम __निकास pegasus_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&pegasus_driver);
पूर्ण

module_init(pegasus_init);
module_निकास(pegasus_निकास);
