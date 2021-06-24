<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAIF USB handler
 * Copyright (C) ST-Ericsson AB 2011
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/netns/generic.h>
#समावेश <net/caअगर/caअगर_dev.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfpkt.h>
#समावेश <net/caअगर/cfcnfg.h>

MODULE_LICENSE("GPL");

#घोषणा CFUSB_PAD_DESCR_SZ 1	/* Alignment descriptor length */
#घोषणा CFUSB_ALIGNMENT 4	/* Number of bytes to align. */
#घोषणा CFUSB_MAX_HEADLEN (CFUSB_PAD_DESCR_SZ + CFUSB_ALIGNMENT-1)
#घोषणा STE_USB_VID 0x04cc	/* USB Product ID क्रम ST-Ericsson */
#घोषणा STE_USB_PID_CAIF 0x230f	/* Product id क्रम CAIF Modems */

काष्ठा cfusbl अणु
	काष्ठा cflayer layer;
	u8 tx_eth_hdr[ETH_HLEN];
पूर्ण;

अटल bool pack_added;

अटल पूर्णांक cfusbl_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u8 hpad;

	/* Remove padding. */
	cfpkt_extr_head(pkt, &hpad, 1);
	cfpkt_extr_head(pkt, शून्य, hpad);
	वापस layr->up->receive(layr->up, pkt);
पूर्ण

अटल पूर्णांक cfusbl_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	काष्ठा caअगर_payload_info *info;
	u8 hpad;
	u8 zeros[CFUSB_ALIGNMENT];
	काष्ठा sk_buff *skb;
	काष्ठा cfusbl *usbl = container_of(layr, काष्ठा cfusbl, layer);

	skb = cfpkt_tonative(pkt);

	skb_reset_network_header(skb);
	skb->protocol = htons(ETH_P_IP);

	info = cfpkt_info(pkt);
	hpad = (info->hdr_len + CFUSB_PAD_DESCR_SZ) & (CFUSB_ALIGNMENT - 1);

	अगर (skb_headroom(skb) < ETH_HLEN + CFUSB_PAD_DESCR_SZ + hpad) अणु
		pr_warn("Headroom too small\n");
		kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण
	स_रखो(zeros, 0, hpad);

	cfpkt_add_head(pkt, zeros, hpad);
	cfpkt_add_head(pkt, &hpad, 1);
	cfpkt_add_head(pkt, usbl->tx_eth_hdr, माप(usbl->tx_eth_hdr));
	वापस layr->dn->transmit(layr->dn, pkt);
पूर्ण

अटल व्योम cfusbl_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			   पूर्णांक phyid)
अणु
	अगर (layr->up && layr->up->ctrlcmd)
		layr->up->ctrlcmd(layr->up, ctrl, layr->id);
पूर्ण

अटल काष्ठा cflayer *cfusbl_create(पूर्णांक phyid, u8 ethaddr[ETH_ALEN],
				      u8 braddr[ETH_ALEN])
अणु
	काष्ठा cfusbl *this = kदो_स्मृति(माप(काष्ठा cfusbl), GFP_ATOMIC);

	अगर (!this)
		वापस शून्य;

	caअगर_निश्चित(दुरत्व(काष्ठा cfusbl, layer) == 0);

	स_रखो(&this->layer, 0, माप(this->layer));
	this->layer.receive = cfusbl_receive;
	this->layer.transmit = cfusbl_transmit;
	this->layer.ctrlcmd = cfusbl_ctrlcmd;
	snम_लिखो(this->layer.name, CAIF_LAYER_NAME_SZ, "usb%d", phyid);
	this->layer.id = phyid;

	/*
	 * Conकाष्ठा TX ethernet header:
	 *	0-5	destination address
	 *	5-11	source address
	 *	12-13	protocol type
	 */
	ether_addr_copy(&this->tx_eth_hdr[ETH_ALEN], braddr);
	ether_addr_copy(&this->tx_eth_hdr[ETH_ALEN], ethaddr);
	this->tx_eth_hdr[12] = cpu_to_be16(ETH_P_802_EX1) & 0xff;
	this->tx_eth_hdr[13] = (cpu_to_be16(ETH_P_802_EX1) >> 8) & 0xff;
	pr_debug("caif ethernet TX-header dst:%pM src:%pM type:%02x%02x\n",
			this->tx_eth_hdr, this->tx_eth_hdr + ETH_ALEN,
			this->tx_eth_hdr[12], this->tx_eth_hdr[13]);

	वापस (काष्ठा cflayer *) this;
पूर्ण

अटल व्योम cfusbl_release(काष्ठा cflayer *layer)
अणु
	kमुक्त(layer);
पूर्ण

अटल काष्ठा packet_type caअगर_usb_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_802_EX1),
पूर्ण;

अटल पूर्णांक cfusbl_device_notअगरy(काष्ठा notअगरier_block *me, अचिन्हित दीर्घ what,
				व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा caअगर_dev_common common;
	काष्ठा cflayer *layer, *link_support;
	काष्ठा usbnet *usbnet;
	काष्ठा usb_device *usbdev;
	पूर्णांक res;

	/* Check whether we have a NCM device, and find its VID/PID. */
	अगर (!(dev->dev.parent && dev->dev.parent->driver &&
	      म_भेद(dev->dev.parent->driver->name, "cdc_ncm") == 0))
		वापस 0;

	usbnet = netdev_priv(dev);
	usbdev = usbnet->udev;

	pr_debug("USB CDC NCM device VID:0x%4x PID:0x%4x\n",
		le16_to_cpu(usbdev->descriptor.idVenकरोr),
		le16_to_cpu(usbdev->descriptor.idProduct));

	/* Check क्रम VID/PID that supports CAIF */
	अगर (!(le16_to_cpu(usbdev->descriptor.idVenकरोr) == STE_USB_VID &&
		le16_to_cpu(usbdev->descriptor.idProduct) == STE_USB_PID_CAIF))
		वापस 0;

	अगर (what == NETDEV_UNREGISTER)
		module_put(THIS_MODULE);

	अगर (what != NETDEV_REGISTER)
		वापस 0;

	__module_get(THIS_MODULE);

	स_रखो(&common, 0, माप(common));
	common.use_frag = false;
	common.use_fcs = false;
	common.use_stx = false;
	common.link_select = CAIF_LINK_HIGH_BANDW;
	common.flowctrl = शून्य;

	link_support = cfusbl_create(dev->अगरindex, dev->dev_addr,
					dev->broadcast);

	अगर (!link_support)
		वापस -ENOMEM;

	अगर (dev->num_tx_queues > 1)
		pr_warn("USB device uses more than one tx queue\n");

	res = caअगर_enroll_dev(dev, &common, link_support, CFUSB_MAX_HEADLEN,
			&layer, &caअगर_usb_type.func);
	अगर (res)
		जाओ err;

	अगर (!pack_added)
		dev_add_pack(&caअगर_usb_type);
	pack_added = true;

	strlcpy(layer->name, dev->name, माप(layer->name));

	वापस 0;
err:
	cfusbl_release(link_support);
	वापस res;
पूर्ण

अटल काष्ठा notअगरier_block caअगर_device_notअगरier = अणु
	.notअगरier_call = cfusbl_device_notअगरy,
	.priority = 0,
पूर्ण;

अटल पूर्णांक __init cfusbl_init(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&caअगर_device_notअगरier);
पूर्ण

अटल व्योम __निकास cfusbl_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&caअगर_device_notअगरier);
	dev_हटाओ_pack(&caअगर_usb_type);
पूर्ण

module_init(cfusbl_init);
module_निकास(cfusbl_निकास);
