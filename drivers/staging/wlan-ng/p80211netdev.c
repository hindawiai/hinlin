<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/* src/p80211/p80211knetdev.c
 *
 * Linux Kernel net device पूर्णांकerface
 *
 * Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * linux-wlan
 *
 *   The contents of this file are subject to the Mozilla Public
 *   License Version 1.1 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.mozilla.org/MPL/
 *
 *   Software distributed under the License is distributed on an "AS
 *   IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 *   implied. See the License क्रम the specअगरic language governing
 *   rights and limitations under the License.
 *
 *   Alternatively, the contents of this file may be used under the
 *   terms of the GNU Public License version 2 (the "GPL"), in which
 *   हाल the provisions of the GPL are applicable instead of the
 *   above.  If you wish to allow the use of your version of this file
 *   only under the terms of the GPL and not to allow others to use
 *   your version of this file under the MPL, indicate your decision
 *   by deleting the provisions above and replace them with the notice
 *   and other provisions required by the GPL.  If you करो not delete
 *   the provisions above, a recipient may use your version of this
 *   file under either the MPL or the GPL.
 *
 * --------------------------------------------------------------------
 *
 * Inquiries regarding the linux-wlan Open Source project can be
 * made directly to:
 *
 * AbsoluteValue Systems Inc.
 * info@linux-wlan.com
 * http://www.linux-wlan.com
 *
 * --------------------------------------------------------------------
 *
 * Portions of the development of this software were funded by
 * Intersil Corporation as part of PRISM(R) chipset product development.
 *
 * --------------------------------------------------------------------
 *
 * The functions required क्रम a Linux network device are defined here.
 *
 * --------------------------------------------------------------------
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/kmod.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/wireless.h>
#समावेश <linux/sockios.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>

#अगर_घोषित SIOCETHTOOL
#समावेश <linux/ethtool.h>
#पूर्ण_अगर

#समावेश <net/iw_handler.h>
#समावेश <net/net_namespace.h>
#समावेश <net/cfg80211.h>

#समावेश "p80211types.h"
#समावेश "p80211hdr.h"
#समावेश "p80211conv.h"
#समावेश "p80211mgmt.h"
#समावेश "p80211msg.h"
#समावेश "p80211netdev.h"
#समावेश "p80211ioctl.h"
#समावेश "p80211req.h"
#समावेश "p80211metastruct.h"
#समावेश "p80211metadef.h"

#समावेश "cfg80211.c"

/* netdevice method functions */
अटल पूर्णांक p80211knetdev_init(काष्ठा net_device *netdev);
अटल पूर्णांक p80211knetdev_खोलो(काष्ठा net_device *netdev);
अटल पूर्णांक p80211knetdev_stop(काष्ठा net_device *netdev);
अटल netdev_tx_t p80211knetdev_hard_start_xmit(काष्ठा sk_buff *skb,
						 काष्ठा net_device *netdev);
अटल व्योम p80211knetdev_set_multicast_list(काष्ठा net_device *dev);
अटल पूर्णांक p80211knetdev_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
				  पूर्णांक cmd);
अटल पूर्णांक p80211knetdev_set_mac_address(काष्ठा net_device *dev, व्योम *addr);
अटल व्योम p80211knetdev_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue);
अटल पूर्णांक p80211_rx_typedrop(काष्ठा wlandevice *wlandev, u16 fc);

पूर्णांक wlan_watchकरोg = 5000;
module_param(wlan_watchकरोg, पूर्णांक, 0644);
MODULE_PARM_DESC(wlan_watchकरोg, "transmit timeout in milliseconds");

पूर्णांक wlan_wext_ग_लिखो = 1;
module_param(wlan_wext_ग_लिखो, पूर्णांक, 0644);
MODULE_PARM_DESC(wlan_wext_ग_लिखो, "enable write wireless extensions");

/*----------------------------------------------------------------
 * p80211knetdev_init
 *
 * Init method क्रम a Linux netdevice.  Called in response to
 * रेजिस्टर_netdev.
 *
 * Arguments:
 *	none
 *
 * Returns:
 *	nothing
 *----------------------------------------------------------------
 */
अटल पूर्णांक p80211knetdev_init(काष्ठा net_device *netdev)
अणु
	/* Called in response to रेजिस्टर_netdev */
	/* This is usually the probe function, but the probe has */
	/* alपढ़ोy been करोne by the MSD and the create_kdev */
	/* function.  All we करो here is वापस success */
	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * p80211knetdev_खोलो
 *
 * Linux netdevice खोलो method.  Following a successful call here,
 * the device is supposed to be पढ़ोy क्रम tx and rx.  In our
 * situation that may not be entirely true due to the state of the
 * MAC below.
 *
 * Arguments:
 *	netdev		Linux network device काष्ठाure
 *
 * Returns:
 *	zero on success, non-zero otherwise
 *----------------------------------------------------------------
 */
अटल पूर्णांक p80211knetdev_खोलो(काष्ठा net_device *netdev)
अणु
	पूर्णांक result = 0;		/* success */
	काष्ठा wlandevice *wlandev = netdev->ml_priv;

	/* Check to make sure the MSD is running */
	अगर (wlandev->msdstate != WLAN_MSD_RUNNING)
		वापस -ENODEV;

	/* Tell the MSD to खोलो */
	अगर (wlandev->खोलो) अणु
		result = wlandev->खोलो(wlandev);
		अगर (result == 0) अणु
			netअगर_start_queue(wlandev->netdev);
			wlandev->state = WLAN_DEVICE_OPEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		result = -EAGAIN;
	पूर्ण

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * p80211knetdev_stop
 *
 * Linux netdevice stop (बंद) method.  Following this call,
 * no frames should go up or करोwn through this पूर्णांकerface.
 *
 * Arguments:
 *	netdev		Linux network device काष्ठाure
 *
 * Returns:
 *	zero on success, non-zero otherwise
 *----------------------------------------------------------------
 */
अटल पूर्णांक p80211knetdev_stop(काष्ठा net_device *netdev)
अणु
	पूर्णांक result = 0;
	काष्ठा wlandevice *wlandev = netdev->ml_priv;

	अगर (wlandev->बंद)
		result = wlandev->बंद(wlandev);

	netअगर_stop_queue(wlandev->netdev);
	wlandev->state = WLAN_DEVICE_CLOSED;

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * p80211netdev_rx
 *
 * Frame receive function called by the mac specअगरic driver.
 *
 * Arguments:
 *	wlandev		WLAN network device काष्ठाure
 *	skb		skbuff containing a full 802.11 frame.
 * Returns:
 *	nothing
 * Side effects:
 *
 *----------------------------------------------------------------
 */
व्योम p80211netdev_rx(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb)
अणु
	/* Enqueue क्रम post-irq processing */
	skb_queue_tail(&wlandev->nsd_rxq, skb);
	tasklet_schedule(&wlandev->rx_bh);
पूर्ण

#घोषणा CONV_TO_ETHER_SKIPPED	0x01
#घोषणा CONV_TO_ETHER_FAILED	0x02

/**
 * p80211_convert_to_ether - conversion from 802.11 frame to ethernet frame
 * @wlandev: poपूर्णांकer to WLAN device
 * @skb: poपूर्णांकer to socket buffer
 *
 * Returns: 0 अगर conversion succeeded
 *	    CONV_TO_ETHER_FAILED अगर conversion failed
 *	    CONV_TO_ETHER_SKIPPED अगर frame is ignored
 */
अटल पूर्णांक p80211_convert_to_ether(काष्ठा wlandevice *wlandev,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा p80211_hdr_a3 *hdr;

	hdr = (काष्ठा p80211_hdr_a3 *)skb->data;
	अगर (p80211_rx_typedrop(wlandev, le16_to_cpu(hdr->fc)))
		वापस CONV_TO_ETHER_SKIPPED;

	/* perक्रमm mcast filtering: allow my local address through but reject
	 * anything अन्यथा that isn't multicast
	 */
	अगर (wlandev->netdev->flags & IFF_ALLMULTI) अणु
		अगर (!ether_addr_equal_unaligned(wlandev->netdev->dev_addr,
						hdr->a1)) अणु
			अगर (!is_multicast_ether_addr(hdr->a1))
				वापस CONV_TO_ETHER_SKIPPED;
		पूर्ण
	पूर्ण

	अगर (skb_p80211_to_ether(wlandev, wlandev->ethconv, skb) == 0) अणु
		wlandev->netdev->stats.rx_packets++;
		wlandev->netdev->stats.rx_bytes += skb->len;
		netअगर_rx_ni(skb);
		वापस 0;
	पूर्ण

	netdev_dbg(wlandev->netdev, "%s failed.\n", __func__);
	वापस CONV_TO_ETHER_FAILED;
पूर्ण

/**
 * p80211netdev_rx_bh - deferred processing of all received frames
 *
 * @t: poपूर्णांकer to the tasklet associated with this handler
 */
अटल व्योम p80211netdev_rx_bh(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा wlandevice *wlandev = from_tasklet(wlandev, t, rx_bh);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा net_device *dev = wlandev->netdev;

	/* Let's empty our queue */
	जबतक ((skb = skb_dequeue(&wlandev->nsd_rxq))) अणु
		अगर (wlandev->state == WLAN_DEVICE_OPEN) अणु
			अगर (dev->type != ARPHRD_ETHER) अणु
				/* RAW frame; we shouldn't convert it */
				/* XXX Append the Prism Header here instead. */

				/* set up various data fields */
				skb->dev = dev;
				skb_reset_mac_header(skb);
				skb->ip_summed = CHECKSUM_NONE;
				skb->pkt_type = PACKET_OTHERHOST;
				skb->protocol = htons(ETH_P_80211_RAW);

				dev->stats.rx_packets++;
				dev->stats.rx_bytes += skb->len;
				netअगर_rx_ni(skb);
				जारी;
			पूर्ण अन्यथा अणु
				अगर (!p80211_convert_to_ether(wlandev, skb))
					जारी;
			पूर्ण
		पूर्ण
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * p80211knetdev_hard_start_xmit
 *
 * Linux netdevice method क्रम transmitting a frame.
 *
 * Arguments:
 *	skb	Linux sk_buff containing the frame.
 *	netdev	Linux netdevice.
 *
 * Side effects:
 *	If the lower layers report that buffers are full. netdev->tbusy
 *	will be set to prevent higher layers from sending more traffic.
 *
 *	Note: If this function वापसs non-zero, higher layers retain
 *	      ownership of the skb.
 *
 * Returns:
 *	zero on success, non-zero on failure.
 *----------------------------------------------------------------
 */
अटल netdev_tx_t p80211knetdev_hard_start_xmit(काष्ठा sk_buff *skb,
						 काष्ठा net_device *netdev)
अणु
	पूर्णांक result = 0;
	पूर्णांक txresult = -1;
	काष्ठा wlandevice *wlandev = netdev->ml_priv;
	जोड़ p80211_hdr p80211_hdr;
	काष्ठा p80211_metawep p80211_wep;

	p80211_wep.data = शून्य;

	अगर (!skb)
		वापस NETDEV_TX_OK;

	अगर (wlandev->state != WLAN_DEVICE_OPEN) अणु
		result = 1;
		जाओ failed;
	पूर्ण

	स_रखो(&p80211_hdr, 0, माप(p80211_hdr));
	स_रखो(&p80211_wep, 0, माप(p80211_wep));

	अगर (netअगर_queue_stopped(netdev)) अणु
		netdev_dbg(netdev, "called when queue stopped.\n");
		result = 1;
		जाओ failed;
	पूर्ण

	netअगर_stop_queue(netdev);

	/* Check to see that a valid mode is set */
	चयन (wlandev->macmode) अणु
	हाल WLAN_MACMODE_IBSS_STA:
	हाल WLAN_MACMODE_ESS_STA:
	हाल WLAN_MACMODE_ESS_AP:
		अवरोध;
	शेष:
		/* Mode isn't set yet, just drop the frame
		 * and वापस success .
		 * TODO: we need a saner way to handle this
		 */
		अगर (be16_to_cpu(skb->protocol) != ETH_P_80211_RAW) अणु
			netअगर_start_queue(wlandev->netdev);
			netdev_notice(netdev, "Tx attempt prior to association, frame dropped.\n");
			netdev->stats.tx_dropped++;
			result = 0;
			जाओ failed;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Check क्रम raw transmits */
	अगर (be16_to_cpu(skb->protocol) == ETH_P_80211_RAW) अणु
		अगर (!capable(CAP_NET_ADMIN)) अणु
			result = 1;
			जाओ failed;
		पूर्ण
		/* move the header over */
		स_नकल(&p80211_hdr, skb->data, माप(p80211_hdr));
		skb_pull(skb, माप(p80211_hdr));
	पूर्ण अन्यथा अणु
		अगर (skb_ether_to_p80211
		    (wlandev, wlandev->ethconv, skb, &p80211_hdr,
		     &p80211_wep) != 0) अणु
			/* convert failed */
			netdev_dbg(netdev, "ether_to_80211(%d) failed.\n",
				   wlandev->ethconv);
			result = 1;
			जाओ failed;
		पूर्ण
	पूर्ण
	अगर (!wlandev->txframe) अणु
		result = 1;
		जाओ failed;
	पूर्ण

	netअगर_trans_update(netdev);

	netdev->stats.tx_packets++;
	/* count only the packet payload */
	netdev->stats.tx_bytes += skb->len;

	txresult = wlandev->txframe(wlandev, skb, &p80211_hdr, &p80211_wep);

	अगर (txresult == 0) अणु
		/* success and more buf */
		/* avail, re: hw_txdata */
		netअगर_wake_queue(wlandev->netdev);
		result = NETDEV_TX_OK;
	पूर्ण अन्यथा अगर (txresult == 1) अणु
		/* success, no more avail */
		netdev_dbg(netdev, "txframe success, no more bufs\n");
		/* netdev->tbusy = 1;  करोn't set here, irqhdlr */
		/*   may have alपढ़ोy cleared it */
		result = NETDEV_TX_OK;
	पूर्ण अन्यथा अगर (txresult == 2) अणु
		/* alloc failure, drop frame */
		netdev_dbg(netdev, "txframe returned alloc_fail\n");
		result = NETDEV_TX_BUSY;
	पूर्ण अन्यथा अणु
		/* buffer full or queue busy, drop frame. */
		netdev_dbg(netdev, "txframe returned full or busy\n");
		result = NETDEV_TX_BUSY;
	पूर्ण

failed:
	/* Free up the WEP buffer अगर it's not the same as the skb */
	अगर ((p80211_wep.data) && (p80211_wep.data != skb->data))
		kमुक्त_sensitive(p80211_wep.data);

	/* we always मुक्त the skb here, never in a lower level. */
	अगर (!result)
		dev_kमुक्त_skb(skb);

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * p80211knetdev_set_multicast_list
 *
 * Called from higher layers whenever there's a need to set/clear
 * promiscuous mode or reग_लिखो the multicast list.
 *
 * Arguments:
 *	none
 *
 * Returns:
 *	nothing
 *----------------------------------------------------------------
 */
अटल व्योम p80211knetdev_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा wlandevice *wlandev = dev->ml_priv;

	/* TODO:  real multicast support as well */

	अगर (wlandev->set_multicast_list)
		wlandev->set_multicast_list(wlandev, dev);
पूर्ण

#अगर_घोषित SIOCETHTOOL

अटल पूर्णांक p80211netdev_ethtool(काष्ठा wlandevice *wlandev,
				व्योम __user *useraddr)
अणु
	u32 ethcmd;
	काष्ठा ethtool_drvinfo info;
	काष्ठा ethtool_value edata;

	स_रखो(&info, 0, माप(info));
	स_रखो(&edata, 0, माप(edata));

	अगर (copy_from_user(&ethcmd, useraddr, माप(ethcmd)))
		वापस -EFAULT;

	चयन (ethcmd) अणु
	हाल ETHTOOL_GDRVINFO:
		info.cmd = ethcmd;
		snम_लिखो(info.driver, माप(info.driver), "p80211_%s",
			 wlandev->nsdname);
		snम_लिखो(info.version, माप(info.version), "%s",
			 WLAN_RELEASE);

		अगर (copy_to_user(useraddr, &info, माप(info)))
			वापस -EFAULT;
		वापस 0;
#अगर_घोषित ETHTOOL_GLINK
	हाल ETHTOOL_GLINK:
		edata.cmd = ethcmd;

		अगर (wlandev->linkstatus &&
		    (wlandev->macmode != WLAN_MACMODE_NONE)) अणु
			edata.data = 1;
		पूर्ण अन्यथा अणु
			edata.data = 0;
		पूर्ण

		अगर (copy_to_user(useraddr, &edata, माप(edata)))
			वापस -EFAULT;
		वापस 0;
#पूर्ण_अगर
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर

/*----------------------------------------------------------------
 * p80211knetdev_करो_ioctl
 *
 * Handle an ioctl call on one of our devices.  Everything Linux
 * ioctl specअगरic is करोne here.  Then we pass the contents of the
 * अगरr->data to the request message handler.
 *
 * Arguments:
 *	dev	Linux kernel netdevice
 *	अगरr	Our निजी ioctl request काष्ठाure, typed क्रम the
 *		generic काष्ठा अगरreq so we can use ptr to func
 *		w/o cast.
 *
 * Returns:
 *	zero on success, a negative त्रुटि_सं on failure.  Possible values:
 *		-ENETDOWN Device isn't up.
 *		-EBUSY	cmd alपढ़ोy in progress
 *		-ETIME	p80211 cmd समयd out (MSD may have its own समयrs)
 *		-EFAULT memory fault copying msg from user buffer
 *		-ENOMEM unable to allocate kernel msg buffer
 *		-EINVAL	bad magic, it the cmd really क्रम us?
 *		-Eपूर्णांकR	sleeping on cmd, awakened by संकेत, cmd cancelled.
 *
 * Call Context:
 *	Process thपढ़ो (ioctl caller).  TODO: SMP support may require
 *	locks.
 *----------------------------------------------------------------
 */
अटल पूर्णांक p80211knetdev_करो_ioctl(काष्ठा net_device *dev,
				  काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	पूर्णांक result = 0;
	काष्ठा p80211ioctl_req *req = (काष्ठा p80211ioctl_req *)अगरr;
	काष्ठा wlandevice *wlandev = dev->ml_priv;
	u8 *msgbuf;

	netdev_dbg(dev, "rx'd ioctl, cmd=%d, len=%d\n", cmd, req->len);

#अगर_घोषित SIOCETHTOOL
	अगर (cmd == SIOCETHTOOL) अणु
		result =
		    p80211netdev_ethtool(wlandev, (व्योम __user *)अगरr->अगरr_data);
		जाओ bail;
	पूर्ण
#पूर्ण_अगर

	/* Test the magic, assume अगरr is good अगर it's there */
	अगर (req->magic != P80211_IOCTL_MAGIC) अणु
		result = -EINVAL;
		जाओ bail;
	पूर्ण

	अगर (cmd == P80211_IFTEST) अणु
		result = 0;
		जाओ bail;
	पूर्ण अन्यथा अगर (cmd != P80211_IFREQ) अणु
		result = -EINVAL;
		जाओ bail;
	पूर्ण

	msgbuf = memdup_user((व्योम __user *)req->data, req->len);
	अगर (IS_ERR(msgbuf)) अणु
		result = PTR_ERR(msgbuf);
		जाओ bail;
	पूर्ण

	result = p80211req_करोrequest(wlandev, msgbuf);

	अगर (result == 0) अणु
		अगर (copy_to_user
		    ((व्योम __user *)req->data, msgbuf, req->len)) अणु
			result = -EFAULT;
		पूर्ण
	पूर्ण
	kमुक्त(msgbuf);

bail:
	/* If allocate,copyfrom or copyto fails, वापस त्रुटि_सं */
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * p80211knetdev_set_mac_address
 *
 * Handles the ioctl क्रम changing the MACAddress of a netdevice
 *
 * references: linux/netdevice.h and drivers/net/net_init.c
 *
 * NOTE: [MSM] We only prevent address changes when the netdev is
 * up.  We करोn't control anything based on करोt11 state.  If the
 * address is changed on a STA that's currently associated, you
 * will probably lose the ability to send and receive data frames.
 * Just be aware.  Thereक्रमe, this should usually only be करोne
 * prior to scan/join/auth/assoc.
 *
 * Arguments:
 *	dev	netdevice काष्ठा
 *	addr	the new MACAddress (a काष्ठा)
 *
 * Returns:
 *	zero on success, a negative त्रुटि_सं on failure.  Possible values:
 *		-EBUSY	device is bussy (cmd not possible)
 *		-and errors वापसed by: p80211req_करोrequest(..)
 *
 * by: Collin R. Mulliner <collin@mulliner.org>
 *----------------------------------------------------------------
 */
अटल पूर्णांक p80211knetdev_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *new_addr = addr;
	काष्ठा p80211msg_करोt11req_mibset करोt11req;
	काष्ठा p80211item_unk392 *mibattr;
	काष्ठा p80211item_pstr6 *macaddr;
	काष्ठा p80211item_uपूर्णांक32 *resultcode;
	पूर्णांक result;

	/* If we're running, we don't allow MAC address changes */
	अगर (netअगर_running(dev))
		वापस -EBUSY;

	/* Set up some convenience poपूर्णांकers. */
	mibattr = &करोt11req.mibattribute;
	macaddr = (काष्ठा p80211item_pstr6 *)&mibattr->data;
	resultcode = &करोt11req.resultcode;

	/* Set up a करोt11req_mibset */
	स_रखो(&करोt11req, 0, माप(करोt11req));
	करोt11req.msgcode = DIDMSG_DOT11REQ_MIBSET;
	करोt11req.msglen = माप(करोt11req);
	स_नकल(करोt11req.devname,
	       ((काष्ठा wlandevice *)dev->ml_priv)->name,
	       WLAN_DEVNAMELEN_MAX - 1);

	/* Set up the mibattribute argument */
	mibattr->did = DIDMSG_DOT11REQ_MIBSET_MIBATTRIBUTE;
	mibattr->status = P80211ENUM_msgitem_status_data_ok;
	mibattr->len = माप(mibattr->data);

	macaddr->did = DIDMIB_DOT11MAC_OPERATIONTABLE_MACADDRESS;
	macaddr->status = P80211ENUM_msgitem_status_data_ok;
	macaddr->len = माप(macaddr->data);
	macaddr->data.len = ETH_ALEN;
	स_नकल(&macaddr->data.data, new_addr->sa_data, ETH_ALEN);

	/* Set up the resultcode argument */
	resultcode->did = DIDMSG_DOT11REQ_MIBSET_RESULTCODE;
	resultcode->status = P80211ENUM_msgitem_status_no_value;
	resultcode->len = माप(resultcode->data);
	resultcode->data = 0;

	/* now fire the request */
	result = p80211req_करोrequest(dev->ml_priv, (u8 *)&करोt11req);

	/* If the request wasn't successful, report an error and don't
	 * change the netdev address
	 */
	अगर (result != 0 || resultcode->data != P80211ENUM_resultcode_success) अणु
		netdev_err(dev, "Low-level driver failed dot11req_mibset(dot11MACAddress).\n");
		result = -EADDRNOTAVAIL;
	पूर्ण अन्यथा अणु
		/* everything's ok, change the addr in netdev */
		स_नकल(dev->dev_addr, new_addr->sa_data, dev->addr_len);
	पूर्ण

	वापस result;
पूर्ण

अटल स्थिर काष्ठा net_device_ops p80211_netdev_ops = अणु
	.nकरो_init = p80211knetdev_init,
	.nकरो_खोलो = p80211knetdev_खोलो,
	.nकरो_stop = p80211knetdev_stop,
	.nकरो_start_xmit = p80211knetdev_hard_start_xmit,
	.nकरो_set_rx_mode = p80211knetdev_set_multicast_list,
	.nकरो_करो_ioctl = p80211knetdev_करो_ioctl,
	.nकरो_set_mac_address = p80211knetdev_set_mac_address,
	.nकरो_tx_समयout = p80211knetdev_tx_समयout,
	.nकरो_validate_addr = eth_validate_addr,
पूर्ण;

/*----------------------------------------------------------------
 * wlan_setup
 *
 * Roughly matches the functionality of ether_setup.  Here
 * we set up any members of the wlandevice काष्ठाure that are common
 * to all devices.  Additionally, we allocate a linux 'struct device'
 * and perक्रमm the same setup as ether_setup.
 *
 * Note: It's important that the caller have setup the wlandev->name
 *	ptr prior to calling this function.
 *
 * Arguments:
 *	wlandev		ptr to the wlandev काष्ठाure क्रम the
 *			पूर्णांकerface.
 *	physdev		ptr to usb device
 * Returns:
 *	zero on success, non-zero otherwise.
 * Call Context:
 *	Should be process thपढ़ो.  We'll assume it might be
 *	पूर्णांकerrupt though.  When we add support क्रम अटलally
 *	compiled drivers, this function will be called in the
 *	context of the kernel startup code.
 *----------------------------------------------------------------
 */
पूर्णांक wlan_setup(काष्ठा wlandevice *wlandev, काष्ठा device *physdev)
अणु
	पूर्णांक result = 0;
	काष्ठा net_device *netdev;
	काष्ठा wiphy *wiphy;
	काष्ठा wireless_dev *wdev;

	/* Set up the wlandev */
	wlandev->state = WLAN_DEVICE_CLOSED;
	wlandev->ethconv = WLAN_ETHCONV_8021h;
	wlandev->macmode = WLAN_MACMODE_NONE;

	/* Set up the rx queue */
	skb_queue_head_init(&wlandev->nsd_rxq);
	tasklet_setup(&wlandev->rx_bh, p80211netdev_rx_bh);

	/* Allocate and initialize the wiphy काष्ठा */
	wiphy = wlan_create_wiphy(physdev, wlandev);
	अगर (!wiphy) अणु
		dev_err(physdev, "Failed to alloc wiphy.\n");
		वापस 1;
	पूर्ण

	/* Allocate and initialize the काष्ठा device */
	netdev = alloc_netdev(माप(काष्ठा wireless_dev), "wlan%d",
			      NET_NAME_UNKNOWN, ether_setup);
	अगर (!netdev) अणु
		dev_err(physdev, "Failed to alloc netdev.\n");
		wlan_मुक्त_wiphy(wiphy);
		result = 1;
	पूर्ण अन्यथा अणु
		wlandev->netdev = netdev;
		netdev->ml_priv = wlandev;
		netdev->netdev_ops = &p80211_netdev_ops;
		wdev = netdev_priv(netdev);
		wdev->wiphy = wiphy;
		wdev->अगरtype = NL80211_IFTYPE_STATION;
		netdev->ieee80211_ptr = wdev;
		netdev->min_mtu = 68;
		/* 2312 is max 802.11 payload, 20 is overhead,
		 * (ether + llc + snap) and another 8 क्रम wep.
		 */
		netdev->max_mtu = (2312 - 20 - 8);

		netअगर_stop_queue(netdev);
		netअगर_carrier_off(netdev);
	पूर्ण

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * wlan_unsetup
 *
 * This function is paired with the wlan_setup routine.  It should
 * be called after unरेजिस्टर_wlandev.  Basically, all it करोes is
 * मुक्त the 'struct device' that's associated with the wlandev.
 * We करो it here because the 'struct device' isn't allocated
 * explicitly in the driver code, it's करोne in wlan_setup.  To
 * करो the मुक्त in the driver might seem like 'magic'.
 *
 * Arguments:
 *	wlandev		ptr to the wlandev काष्ठाure क्रम the
 *			पूर्णांकerface.
 * Call Context:
 *	Should be process thपढ़ो.  We'll assume it might be
 *	पूर्णांकerrupt though.  When we add support क्रम अटलally
 *	compiled drivers, this function will be called in the
 *	context of the kernel startup code.
 *----------------------------------------------------------------
 */
व्योम wlan_unsetup(काष्ठा wlandevice *wlandev)
अणु
	काष्ठा wireless_dev *wdev;

	tasklet_समाप्त(&wlandev->rx_bh);

	अगर (wlandev->netdev) अणु
		wdev = netdev_priv(wlandev->netdev);
		अगर (wdev->wiphy)
			wlan_मुक्त_wiphy(wdev->wiphy);
		मुक्त_netdev(wlandev->netdev);
		wlandev->netdev = शून्य;
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * रेजिस्टर_wlandev
 *
 * Roughly matches the functionality of रेजिस्टर_netdev.  This function
 * is called after the driver has successfully probed and set up the
 * resources क्रम the device.  It's now पढ़ोy to become a named device
 * in the Linux प्रणाली.
 *
 * First we allocate a name क्रम the device (अगर not alपढ़ोy set), then
 * we call the Linux function रेजिस्टर_netdevice.
 *
 * Arguments:
 *	wlandev		ptr to the wlandev काष्ठाure क्रम the
 *			पूर्णांकerface.
 * Returns:
 *	zero on success, non-zero otherwise.
 * Call Context:
 *	Can be either पूर्णांकerrupt or not.
 *----------------------------------------------------------------
 */
पूर्णांक रेजिस्टर_wlandev(काष्ठा wlandevice *wlandev)
अणु
	वापस रेजिस्टर_netdev(wlandev->netdev);
पूर्ण

/*----------------------------------------------------------------
 * unरेजिस्टर_wlandev
 *
 * Roughly matches the functionality of unरेजिस्टर_netdev.  This
 * function is called to हटाओ a named device from the प्रणाली.
 *
 * First we tell linux that the device should no दीर्घer exist.
 * Then we हटाओ it from the list of known wlan devices.
 *
 * Arguments:
 *	wlandev		ptr to the wlandev काष्ठाure क्रम the
 *			पूर्णांकerface.
 * Returns:
 *	zero on success, non-zero otherwise.
 * Call Context:
 *	Can be either पूर्णांकerrupt or not.
 *----------------------------------------------------------------
 */
पूर्णांक unरेजिस्टर_wlandev(काष्ठा wlandevice *wlandev)
अणु
	काष्ठा sk_buff *skb;

	unरेजिस्टर_netdev(wlandev->netdev);

	/* Now to clean out the rx queue */
	जबतक ((skb = skb_dequeue(&wlandev->nsd_rxq)))
		dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * p80211netdev_hwहटाओd
 *
 * Hardware हटाओd notअगरication. This function should be called
 * immediately after an MSD has detected that the underlying hardware
 * has been yanked out from under us.  The primary things we need
 * to करो are:
 *   - Mark the wlandev
 *   - Prevent any further traffic from the knetdev i/f
 *   - Prevent any further requests from mgmt i/f
 *   - If there are any रुकोq'd mgmt requests or mgmt-frame exchanges,
 *     shut them करोwn.
 *   - Call the MSD hwहटाओd function.
 *
 * The reमुख्यder of the cleanup will be handled by unरेजिस्टर().
 * Our primary goal here is to prevent as much tickling of the MSD
 * as possible since the MSD is alपढ़ोy in a 'wounded' state.
 *
 * TODO: As new features are added, this function should be
 *       updated.
 *
 * Arguments:
 *	wlandev		WLAN network device काष्ठाure
 * Returns:
 *	nothing
 * Side effects:
 *
 * Call context:
 *	Usually पूर्णांकerrupt.
 *----------------------------------------------------------------
 */
व्योम p80211netdev_hwहटाओd(काष्ठा wlandevice *wlandev)
अणु
	wlandev->hwहटाओd = 1;
	अगर (wlandev->state == WLAN_DEVICE_OPEN)
		netअगर_stop_queue(wlandev->netdev);

	netअगर_device_detach(wlandev->netdev);
पूर्ण

/*----------------------------------------------------------------
 * p80211_rx_typedrop
 *
 * Classअगरies the frame, increments the appropriate counter, and
 * वापसs 0|1|2 indicating whether the driver should handle, ignore, or
 * drop the frame
 *
 * Arguments:
 *	wlandev		wlan device काष्ठाure
 *	fc		frame control field
 *
 * Returns:
 *	zero अगर the frame should be handled by the driver,
 *       one अगर the frame should be ignored
 *       anything अन्यथा means we drop it.
 *
 * Side effects:
 *
 * Call context:
 *	पूर्णांकerrupt
 *----------------------------------------------------------------
 */
अटल पूर्णांक p80211_rx_typedrop(काष्ठा wlandevice *wlandev, u16 fc)
अणु
	u16 ftype;
	u16 fstype;
	पूर्णांक drop = 0;
	/* Classअगरy frame, increment counter */
	ftype = WLAN_GET_FC_FTYPE(fc);
	fstype = WLAN_GET_FC_FSTYPE(fc);
	चयन (ftype) अणु
	हाल WLAN_FTYPE_MGMT:
		अगर ((wlandev->netdev->flags & IFF_PROMISC) ||
		    (wlandev->netdev->flags & IFF_ALLMULTI)) अणु
			drop = 1;
			अवरोध;
		पूर्ण
		netdev_dbg(wlandev->netdev, "rx'd mgmt:\n");
		wlandev->rx.mgmt++;
		चयन (fstype) अणु
		हाल WLAN_FSTYPE_ASSOCREQ:
			/* prपूर्णांकk("assocreq"); */
			wlandev->rx.assocreq++;
			अवरोध;
		हाल WLAN_FSTYPE_ASSOCRESP:
			/* prपूर्णांकk("assocresp"); */
			wlandev->rx.assocresp++;
			अवरोध;
		हाल WLAN_FSTYPE_REASSOCREQ:
			/* prपूर्णांकk("reassocreq"); */
			wlandev->rx.reassocreq++;
			अवरोध;
		हाल WLAN_FSTYPE_REASSOCRESP:
			/* prपूर्णांकk("reassocresp"); */
			wlandev->rx.reassocresp++;
			अवरोध;
		हाल WLAN_FSTYPE_PROBEREQ:
			/* prपूर्णांकk("probereq"); */
			wlandev->rx.probereq++;
			अवरोध;
		हाल WLAN_FSTYPE_PROBERESP:
			/* prपूर्णांकk("proberesp"); */
			wlandev->rx.proberesp++;
			अवरोध;
		हाल WLAN_FSTYPE_BEACON:
			/* prपूर्णांकk("beacon"); */
			wlandev->rx.beacon++;
			अवरोध;
		हाल WLAN_FSTYPE_ATIM:
			/* prपूर्णांकk("atim"); */
			wlandev->rx.atim++;
			अवरोध;
		हाल WLAN_FSTYPE_DISASSOC:
			/* prपूर्णांकk("disassoc"); */
			wlandev->rx.disassoc++;
			अवरोध;
		हाल WLAN_FSTYPE_AUTHEN:
			/* prपूर्णांकk("authen"); */
			wlandev->rx.authen++;
			अवरोध;
		हाल WLAN_FSTYPE_DEAUTHEN:
			/* prपूर्णांकk("deauthen"); */
			wlandev->rx.deauthen++;
			अवरोध;
		शेष:
			/* prपूर्णांकk("unknown"); */
			wlandev->rx.mgmt_unknown++;
			अवरोध;
		पूर्ण
		/* prपूर्णांकk("\n"); */
		drop = 2;
		अवरोध;

	हाल WLAN_FTYPE_CTL:
		अगर ((wlandev->netdev->flags & IFF_PROMISC) ||
		    (wlandev->netdev->flags & IFF_ALLMULTI)) अणु
			drop = 1;
			अवरोध;
		पूर्ण
		netdev_dbg(wlandev->netdev, "rx'd ctl:\n");
		wlandev->rx.ctl++;
		चयन (fstype) अणु
		हाल WLAN_FSTYPE_PSPOLL:
			/* prपूर्णांकk("pspoll"); */
			wlandev->rx.pspoll++;
			अवरोध;
		हाल WLAN_FSTYPE_RTS:
			/* prपूर्णांकk("rts"); */
			wlandev->rx.rts++;
			अवरोध;
		हाल WLAN_FSTYPE_CTS:
			/* prपूर्णांकk("cts"); */
			wlandev->rx.cts++;
			अवरोध;
		हाल WLAN_FSTYPE_ACK:
			/* prपूर्णांकk("ack"); */
			wlandev->rx.ack++;
			अवरोध;
		हाल WLAN_FSTYPE_CFEND:
			/* prपूर्णांकk("cfend"); */
			wlandev->rx.cfend++;
			अवरोध;
		हाल WLAN_FSTYPE_CFENDCFACK:
			/* prपूर्णांकk("cfendcfack"); */
			wlandev->rx.cfendcfack++;
			अवरोध;
		शेष:
			/* prपूर्णांकk("unknown"); */
			wlandev->rx.ctl_unknown++;
			अवरोध;
		पूर्ण
		/* prपूर्णांकk("\n"); */
		drop = 2;
		अवरोध;

	हाल WLAN_FTYPE_DATA:
		wlandev->rx.data++;
		चयन (fstype) अणु
		हाल WLAN_FSTYPE_DATAONLY:
			wlandev->rx.dataonly++;
			अवरोध;
		हाल WLAN_FSTYPE_DATA_CFACK:
			wlandev->rx.data_cfack++;
			अवरोध;
		हाल WLAN_FSTYPE_DATA_CFPOLL:
			wlandev->rx.data_cfpoll++;
			अवरोध;
		हाल WLAN_FSTYPE_DATA_CFACK_CFPOLL:
			wlandev->rx.data__cfack_cfpoll++;
			अवरोध;
		हाल WLAN_FSTYPE_शून्य:
			netdev_dbg(wlandev->netdev, "rx'd data:null\n");
			wlandev->rx.null++;
			अवरोध;
		हाल WLAN_FSTYPE_CFACK:
			netdev_dbg(wlandev->netdev, "rx'd data:cfack\n");
			wlandev->rx.cfack++;
			अवरोध;
		हाल WLAN_FSTYPE_CFPOLL:
			netdev_dbg(wlandev->netdev, "rx'd data:cfpoll\n");
			wlandev->rx.cfpoll++;
			अवरोध;
		हाल WLAN_FSTYPE_CFACK_CFPOLL:
			netdev_dbg(wlandev->netdev, "rx'd data:cfack_cfpoll\n");
			wlandev->rx.cfack_cfpoll++;
			अवरोध;
		शेष:
			/* prपूर्णांकk("unknown"); */
			wlandev->rx.data_unknown++;
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण
	वापस drop;
पूर्ण

अटल व्योम p80211knetdev_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा wlandevice *wlandev = netdev->ml_priv;

	अगर (wlandev->tx_समयout) अणु
		wlandev->tx_समयout(wlandev);
	पूर्ण अन्यथा अणु
		netdev_warn(netdev, "Implement tx_timeout for %s\n",
			    wlandev->nsdname);
		netअगर_wake_queue(wlandev->netdev);
	पूर्ण
पूर्ण
