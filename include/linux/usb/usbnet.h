<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB Networking Link Interface
 *
 * Copyright (C) 2000-2005 by David Brownell <dbrownell@users.sourceक्रमge.net>
 * Copyright (C) 2003-2005 David Hollis <dhollis@davehollis.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#अगर_अघोषित	__LINUX_USB_USBNET_H
#घोषणा	__LINUX_USB_USBNET_H

/* पूर्णांकerface from usbnet core to each USB networking link we handle */
काष्ठा usbnet अणु
	/* housekeeping */
	काष्ठा usb_device	*udev;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;
	स्थिर काष्ठा driver_info *driver_info;
	स्थिर अक्षर		*driver_name;
	व्योम			*driver_priv;
	रुको_queue_head_t	रुको;
	काष्ठा mutex		phy_mutex;
	अचिन्हित अक्षर		suspend_count;
	अचिन्हित अक्षर		pkt_cnt, pkt_err;
	अचिन्हित लघु		rx_qlen, tx_qlen;
	अचिन्हित		can_dma_sg:1;

	/* i/o info: pipes etc */
	अचिन्हित		in, out;
	काष्ठा usb_host_endpoपूर्णांक *status;
	अचिन्हित		maxpacket;
	काष्ठा समयr_list	delay;
	स्थिर अक्षर		*padding_pkt;

	/* protocol/पूर्णांकerface state */
	काष्ठा net_device	*net;
	पूर्णांक			msg_enable;
	अचिन्हित दीर्घ		data[5];
	u32			xid;
	u32			hard_mtu;	/* count any extra framing */
	माप_प्रकार			rx_urb_size;	/* size क्रम rx urbs */
	काष्ठा mii_अगर_info	mii;
	दीर्घ			rx_speed;	/* If MII not used */
	दीर्घ			tx_speed;	/* If MII not used */
#		define SPEED_UNSET	-1

	/* various kinds of pending driver work */
	काष्ठा sk_buff_head	rxq;
	काष्ठा sk_buff_head	txq;
	काष्ठा sk_buff_head	करोne;
	काष्ठा sk_buff_head	rxq_छोड़ो;
	काष्ठा urb		*पूर्णांकerrupt;
	अचिन्हित		पूर्णांकerrupt_count;
	काष्ठा mutex		पूर्णांकerrupt_mutex;
	काष्ठा usb_anchor	deferred;
	काष्ठा tasklet_काष्ठा	bh;

	काष्ठा work_काष्ठा	kevent;
	अचिन्हित दीर्घ		flags;
#		define EVENT_TX_HALT	0
#		define EVENT_RX_HALT	1
#		define EVENT_RX_MEMORY	2
#		define EVENT_STS_SPLIT	3
#		define EVENT_LINK_RESET	4
#		define EVENT_RX_PAUSED	5
#		define EVENT_DEV_ASLEEP 6
#		define EVENT_DEV_OPEN	7
#		define EVENT_DEVICE_REPORT_IDLE	8
#		define EVENT_NO_RUNTIME_PM	9
#		define EVENT_RX_KILL	10
#		define EVENT_LINK_CHANGE	11
#		define EVENT_SET_RX_MODE	12
#		define EVENT_NO_IP_ALIGN	13
पूर्ण;

अटल अंतरभूत काष्ठा usb_driver *driver_of(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस to_usb_driver(पूर्णांकf->dev.driver);
पूर्ण

/* पूर्णांकerface from the device/framing level "minidriver" to core */
काष्ठा driver_info अणु
	अक्षर		*description;

	पूर्णांक		flags;
/* framing is CDC Ethernet, not writing ZLPs (hw issues), or optionally: */
#घोषणा FLAG_FRAMING_NC	0x0001		/* guard against device dropouts */
#घोषणा FLAG_FRAMING_GL	0x0002		/* genelink batches packets */
#घोषणा FLAG_FRAMING_Z	0x0004		/* zaurus adds a trailer */
#घोषणा FLAG_FRAMING_RN	0x0008		/* RNDIS batches, plus huge header */

#घोषणा FLAG_NO_SETINT	0x0010		/* device can't set_पूर्णांकerface() */
#घोषणा FLAG_ETHER	0x0020		/* maybe use "eth%d" names */

#घोषणा FLAG_FRAMING_AX 0x0040		/* AX88772/178 packets */
#घोषणा FLAG_WLAN	0x0080		/* use "wlan%d" names */
#घोषणा FLAG_AVOID_UNLINK_URBS 0x0100	/* करोn't unlink urbs at usbnet_stop() */
#घोषणा FLAG_SEND_ZLP	0x0200		/* hw requires ZLPs are sent */
#घोषणा FLAG_WWAN	0x0400		/* use "wwan%d" names */

#घोषणा FLAG_LINK_INTR	0x0800		/* updates link (carrier) status */

#घोषणा FLAG_POINTTOPOINT 0x1000	/* possibly use "usb%d" names */

/*
 * Indicates to usbnet, that USB driver accumulates multiple IP packets.
 * Affects statistic (counters) and लघु packet handling.
 */
#घोषणा FLAG_MULTI_PACKET	0x2000
#घोषणा FLAG_RX_ASSEMBLE	0x4000	/* rx packets may span >1 frames */
#घोषणा FLAG_NOARP		0x8000	/* device can't करो ARP */

	/* init device ... can sleep, or cause probe() failure */
	पूर्णांक	(*bind)(काष्ठा usbnet *, काष्ठा usb_पूर्णांकerface *);

	/* cleanup device ... can sleep, but can't fail */
	व्योम	(*unbind)(काष्ठा usbnet *, काष्ठा usb_पूर्णांकerface *);

	/* reset device ... can sleep */
	पूर्णांक	(*reset)(काष्ठा usbnet *);

	/* stop device ... can sleep */
	पूर्णांक	(*stop)(काष्ठा usbnet *);

	/* see अगर peer is connected ... can sleep */
	पूर्णांक	(*check_connect)(काष्ठा usbnet *);

	/* (dis)activate runसमय घातer management */
	पूर्णांक	(*manage_घातer)(काष्ठा usbnet *, पूर्णांक);

	/* क्रम status polling */
	व्योम	(*status)(काष्ठा usbnet *, काष्ठा urb *);

	/* link reset handling, called from defer_kevent */
	पूर्णांक	(*link_reset)(काष्ठा usbnet *);

	/* fixup rx packet (strip framing) */
	पूर्णांक	(*rx_fixup)(काष्ठा usbnet *dev, काष्ठा sk_buff *skb);

	/* fixup tx packet (add framing) */
	काष्ठा sk_buff	*(*tx_fixup)(काष्ठा usbnet *dev,
				काष्ठा sk_buff *skb, gfp_t flags);

	/* recover from समयout */
	व्योम	(*recover)(काष्ठा usbnet *dev);

	/* early initialization code, can sleep. This is क्रम minidrivers
	 * having 'subminidrivers' that need to करो extra initialization
	 * right after minidriver have initialized hardware. */
	पूर्णांक	(*early_init)(काष्ठा usbnet *dev);

	/* called by minidriver when receiving indication */
	व्योम	(*indication)(काष्ठा usbnet *dev, व्योम *ind, पूर्णांक indlen);

	/* rx mode change (device changes address list filtering) */
	व्योम	(*set_rx_mode)(काष्ठा usbnet *dev);

	/* क्रम new devices, use the descriptor-पढ़ोing code instead */
	पूर्णांक		in;		/* rx endpoपूर्णांक */
	पूर्णांक		out;		/* tx endpoपूर्णांक */

	अचिन्हित दीर्घ	data;		/* Misc driver specअगरic data */
पूर्ण;

/* Minidrivers are just drivers using the "usbnet" core as a घातerful
 * network-specअगरic subroutine library ... that happens to करो pretty
 * much everything except custom framing and chip-specअगरic stuff.
 */
बाह्य पूर्णांक usbnet_probe(काष्ठा usb_पूर्णांकerface *, स्थिर काष्ठा usb_device_id *);
बाह्य पूर्णांक usbnet_suspend(काष्ठा usb_पूर्णांकerface *, pm_message_t);
बाह्य पूर्णांक usbnet_resume(काष्ठा usb_पूर्णांकerface *);
बाह्य व्योम usbnet_disconnect(काष्ठा usb_पूर्णांकerface *);
बाह्य व्योम usbnet_device_suggests_idle(काष्ठा usbnet *dev);

बाह्य पूर्णांक usbnet_पढ़ो_cmd(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
		    u16 value, u16 index, व्योम *data, u16 size);
बाह्य पूर्णांक usbnet_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
		    u16 value, u16 index, स्थिर व्योम *data, u16 size);
बाह्य पूर्णांक usbnet_पढ़ो_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
		    u16 value, u16 index, व्योम *data, u16 size);
बाह्य पूर्णांक usbnet_ग_लिखो_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
		    u16 value, u16 index, स्थिर व्योम *data, u16 size);
बाह्य पूर्णांक usbnet_ग_लिखो_cmd_async(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
		    u16 value, u16 index, स्थिर व्योम *data, u16 size);

/* Drivers that reuse some of the standard USB CDC infraकाष्ठाure
 * (notably, using multiple पूर्णांकerfaces according to the CDC
 * जोड़ descriptor) get some helper code.
 */
काष्ठा cdc_state अणु
	काष्ठा usb_cdc_header_desc	*header;
	काष्ठा usb_cdc_जोड़_desc	*u;
	काष्ठा usb_cdc_ether_desc	*ether;
	काष्ठा usb_पूर्णांकerface		*control;
	काष्ठा usb_पूर्णांकerface		*data;
पूर्ण;

बाह्य व्योम usbnet_cdc_update_filter(काष्ठा usbnet *dev);
बाह्य पूर्णांक usbnet_generic_cdc_bind(काष्ठा usbnet *, काष्ठा usb_पूर्णांकerface *);
बाह्य पूर्णांक usbnet_ether_cdc_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य पूर्णांक usbnet_cdc_bind(काष्ठा usbnet *, काष्ठा usb_पूर्णांकerface *);
बाह्य व्योम usbnet_cdc_unbind(काष्ठा usbnet *, काष्ठा usb_पूर्णांकerface *);
बाह्य व्योम usbnet_cdc_status(काष्ठा usbnet *, काष्ठा urb *);

/* CDC and RNDIS support the same host-chosen packet filters क्रम IN transfers */
#घोषणा	DEFAULT_FILTER	(USB_CDC_PACKET_TYPE_BROADCAST \
			|USB_CDC_PACKET_TYPE_ALL_MULTICAST \
			|USB_CDC_PACKET_TYPE_PROMISCUOUS \
			|USB_CDC_PACKET_TYPE_सूचीECTED)


/* we record the state क्रम each of our queued skbs */
क्रमागत skb_state अणु
	illegal = 0,
	tx_start, tx_करोne,
	rx_start, rx_करोne, rx_cleanup,
	unlink_start
पूर्ण;

काष्ठा skb_data अणु	/* skb->cb is one of these */
	काष्ठा urb		*urb;
	काष्ठा usbnet		*dev;
	क्रमागत skb_state		state;
	दीर्घ			length;
	अचिन्हित दीर्घ		packets;
पूर्ण;

/* Drivers that set FLAG_MULTI_PACKET must call this in their
 * tx_fixup method beक्रमe वापसing an skb.
 */
अटल अंतरभूत व्योम
usbnet_set_skb_tx_stats(काष्ठा sk_buff *skb,
			अचिन्हित दीर्घ packets, दीर्घ bytes_delta)
अणु
	काष्ठा skb_data *entry = (काष्ठा skb_data *) skb->cb;

	entry->packets = packets;
	entry->length = bytes_delta;
पूर्ण

बाह्य पूर्णांक usbnet_खोलो(काष्ठा net_device *net);
बाह्य पूर्णांक usbnet_stop(काष्ठा net_device *net);
बाह्य netdev_tx_t usbnet_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *net);
बाह्य व्योम usbnet_tx_समयout(काष्ठा net_device *net, अचिन्हित पूर्णांक txqueue);
बाह्य पूर्णांक usbnet_change_mtu(काष्ठा net_device *net, पूर्णांक new_mtu);

बाह्य पूर्णांक usbnet_get_endpoपूर्णांकs(काष्ठा usbnet *, काष्ठा usb_पूर्णांकerface *);
बाह्य पूर्णांक usbnet_get_ethernet_addr(काष्ठा usbnet *, पूर्णांक);
बाह्य व्योम usbnet_defer_kevent(काष्ठा usbnet *, पूर्णांक);
बाह्य व्योम usbnet_skb_वापस(काष्ठा usbnet *, काष्ठा sk_buff *);
बाह्य व्योम usbnet_unlink_rx_urbs(काष्ठा usbnet *);

बाह्य व्योम usbnet_छोड़ो_rx(काष्ठा usbnet *);
बाह्य व्योम usbnet_resume_rx(काष्ठा usbnet *);
बाह्य व्योम usbnet_purge_छोड़ोd_rxq(काष्ठा usbnet *);

बाह्य पूर्णांक usbnet_get_link_ksettings_mii(काष्ठा net_device *net,
				     काष्ठा ethtool_link_ksettings *cmd);
बाह्य पूर्णांक usbnet_set_link_ksettings_mii(काष्ठा net_device *net,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd);
बाह्य पूर्णांक usbnet_get_link_ksettings_पूर्णांकernal(काष्ठा net_device *net,
				     काष्ठा ethtool_link_ksettings *cmd);
बाह्य u32 usbnet_get_link(काष्ठा net_device *net);
बाह्य u32 usbnet_get_msglevel(काष्ठा net_device *);
बाह्य व्योम usbnet_set_msglevel(काष्ठा net_device *, u32);
बाह्य व्योम usbnet_set_rx_mode(काष्ठा net_device *net);
बाह्य व्योम usbnet_get_drvinfo(काष्ठा net_device *, काष्ठा ethtool_drvinfo *);
बाह्य पूर्णांक usbnet_nway_reset(काष्ठा net_device *net);

बाह्य पूर्णांक usbnet_manage_घातer(काष्ठा usbnet *, पूर्णांक);
बाह्य व्योम usbnet_link_change(काष्ठा usbnet *, bool, bool);

बाह्य पूर्णांक usbnet_status_start(काष्ठा usbnet *dev, gfp_t mem_flags);
बाह्य व्योम usbnet_status_stop(काष्ठा usbnet *dev);

बाह्य व्योम usbnet_update_max_qlen(काष्ठा usbnet *dev);

#पूर्ण_अगर /* __LINUX_USB_USBNET_H */
