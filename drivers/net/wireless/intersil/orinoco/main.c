<शैली गुरु>
/* मुख्य.c - (क्रमmerly known as dldwd_cs.c, orinoco_cs.c and orinoco.c)
 *
 * A driver क्रम Hermes or Prism 2 chipset based PCMCIA wireless
 * adaptors, with Lucent/Agere, Intersil or Symbol firmware.
 *
 * Current मुख्यtainers (as of 29 September 2003) are:
 *	Pavel Roskin <proski AT gnu.org>
 * and	David Gibson <hermes AT gibson.dropbear.id.au>
 *
 * (C) Copyright David Gibson, IBM Corporation 2001-2003.
 * Copyright (C) 2000 David Gibson, Linuxcare Australia.
 *	With some help from :
 * Copyright (C) 2001 Jean Tourrilhes, HP Lअसल
 * Copyright (C) 2001 Benjamin Herrenschmidt
 *
 * Based on dummy_cs.c 1.27 2000/06/12 21:27:25
 *
 * Portions based on wvlan_cs.c 1.0.6, Copyright Andreas Neuhaus <andy
 * AT fasta.fh-करोrपंचांगund.de>
 *      http://www.stud.fh-करोrपंचांगund.de/~andy/wvlan/
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License.
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds AT users.sourceक्रमge.net>.  Portions created by David
 * A. Hinds are Copyright (C) 1999 David A. Hinds.  All Rights
 * Reserved.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in
 * which हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use your
 * version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.  */

/*
 * TODO
 *	o Handle de-encapsulation within network layer, provide 802.11
 *	  headers (patch from Thomas 'Dent' Mirlacher)
 *	o Fix possible races in SPY handling.
 *	o Disconnect wireless extensions from fundamental configuration.
 *	o (maybe) Software WEP support (patch from Stano Meduna).
 *	o (maybe) Use multiple Tx buffers - driver handling queue
 *	  rather than firmware.
 */

/* Locking and synchronization:
 *
 * The basic principle is that everything is serialized through a
 * single spinlock, priv->lock.  The lock is used in user, bh and irq
 * context, so when taken outside hardirq context it should always be
 * taken with पूर्णांकerrupts disabled.  The lock protects both the
 * hardware and the काष्ठा orinoco_निजी.
 *
 * Another flag, priv->hw_unavailable indicates that the hardware is
 * unavailable क्रम an extended period of समय (e.g. suspended, or in
 * the middle of a hard reset).  This flag is रक्षित by the
 * spinlock.  All code which touches the hardware should check the
 * flag after taking the lock, and अगर it is set, give up on whatever
 * they are करोing and drop the lock again.  The orinoco_lock()
 * function handles this (it unlocks and वापसs -EBUSY अगर
 * hw_unavailable is non-zero).
 */

#घोषणा DRIVER_NAME "orinoco"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/suspend.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/wireless.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/iw_handler.h>
#समावेश <net/cfg80211.h>

#समावेश "hermes_rid.h"
#समावेश "hermes_dld.h"
#समावेश "hw.h"
#समावेश "scan.h"
#समावेश "mic.h"
#समावेश "fw.h"
#समावेश "wext.h"
#समावेश "cfg.h"
#समावेश "main.h"

#समावेश "orinoco.h"

/********************************************************************/
/* Module inक्रमmation                                               */
/********************************************************************/

MODULE_AUTHOR("Pavel Roskin <proski@gnu.org> & "
	      "David Gibson <hermes@gibson.dropbear.id.au>");
MODULE_DESCRIPTION("Driver for Lucent Orinoco, Prism II based "
		   "and similar wireless cards");
MODULE_LICENSE("Dual MPL/GPL");

/* Level of debugging. Used in the macros in orinoco.h */
#अगर_घोषित ORINOCO_DEBUG
पूर्णांक orinoco_debug = ORINOCO_DEBUG;
EXPORT_SYMBOL(orinoco_debug);
module_param(orinoco_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(orinoco_debug, "Debug level");
#पूर्ण_अगर

अटल bool suppress_linkstatus; /* = 0 */
module_param(suppress_linkstatus, bool, 0644);
MODULE_PARM_DESC(suppress_linkstatus, "Don't log link status changes");

अटल पूर्णांक ignore_disconnect; /* = 0 */
module_param(ignore_disconnect, पूर्णांक, 0644);
MODULE_PARM_DESC(ignore_disconnect,
		 "Don't report lost link to the network layer");

पूर्णांक क्रमce_monitor; /* = 0 */
module_param(क्रमce_monitor, पूर्णांक, 0644);
MODULE_PARM_DESC(क्रमce_monitor, "Allow monitor mode for all firmware versions");

/********************************************************************/
/* Internal स्थिरants                                               */
/********************************************************************/

/* 802.2 LLC/SNAP header used क्रम Ethernet encapsulation over 802.11 */
अटल स्थिर u8 encaps_hdr[] = अणु0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00पूर्ण;
#घोषणा ENCAPS_OVERHEAD		(माप(encaps_hdr) + 2)

#घोषणा ORINOCO_MIN_MTU		256
#घोषणा ORINOCO_MAX_MTU		(IEEE80211_MAX_DATA_LEN - ENCAPS_OVERHEAD)

#घोषणा MAX_IRQLOOPS_PER_IRQ	10
#घोषणा MAX_IRQLOOPS_PER_JIFFY	(20000 / HZ)	/* Based on a guestimate of
						 * how many events the
						 * device could
						 * legitimately generate */

#घोषणा DUMMY_FID		0xFFFF

/*#घोषणा MAX_MULTICAST(priv)	(priv->firmware_type == FIRMWARE_TYPE_AGERE ? \
  HERMES_MAX_MULTICAST : 0)*/
#घोषणा MAX_MULTICAST(priv)	(HERMES_MAX_MULTICAST)

#घोषणा ORINOCO_INTEN		(HERMES_EV_RX | HERMES_EV_ALLOC \
				 | HERMES_EV_TX | HERMES_EV_TXEXC \
				 | HERMES_EV_WTERR | HERMES_EV_INFO \
				 | HERMES_EV_INFDROP)

/********************************************************************/
/* Data types                                                       */
/********************************************************************/

/* Beginning of the Tx descriptor, used in TxExc handling */
काष्ठा hermes_txexc_data अणु
	काष्ठा hermes_tx_descriptor desc;
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
पूर्ण __packed;

/* Rx frame header except compatibility 802.3 header */
काष्ठा hermes_rx_descriptor अणु
	/* Control */
	__le16 status;
	__le32 समय;
	u8 silence;
	u8 संकेत;
	u8 rate;
	u8 rxflow;
	__le32 reserved;

	/* 802.11 header */
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 addr4[ETH_ALEN];

	/* Data length */
	__le16 data_len;
पूर्ण __packed;

काष्ठा orinoco_rx_data अणु
	काष्ठा hermes_rx_descriptor *desc;
	काष्ठा sk_buff *skb;
	काष्ठा list_head list;
पूर्ण;

काष्ठा orinoco_scan_data अणु
	व्योम *buf;
	माप_प्रकार len;
	पूर्णांक type;
	काष्ठा list_head list;
पूर्ण;

/********************************************************************/
/* Function prototypes                                              */
/********************************************************************/

अटल पूर्णांक __orinoco_set_multicast_list(काष्ठा net_device *dev);
अटल पूर्णांक __orinoco_up(काष्ठा orinoco_निजी *priv);
अटल पूर्णांक __orinoco_करोwn(काष्ठा orinoco_निजी *priv);
अटल पूर्णांक __orinoco_commit(काष्ठा orinoco_निजी *priv);

/********************************************************************/
/* Internal helper functions                                        */
/********************************************************************/

व्योम set_port_type(काष्ठा orinoco_निजी *priv)
अणु
	चयन (priv->iw_mode) अणु
	हाल NL80211_IFTYPE_STATION:
		priv->port_type = 1;
		priv->createibss = 0;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		अगर (priv->prefer_port3) अणु
			priv->port_type = 3;
			priv->createibss = 0;
		पूर्ण अन्यथा अणु
			priv->port_type = priv->ibss_port;
			priv->createibss = 1;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		priv->port_type = 3;
		priv->createibss = 0;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s: Invalid priv->iw_mode in set_port_type()\n",
		       priv->ndev->name);
	पूर्ण
पूर्ण

/********************************************************************/
/* Device methods                                                   */
/********************************************************************/

पूर्णांक orinoco_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	err = __orinoco_up(priv);

	अगर (!err)
		priv->खोलो = 1;

	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण
EXPORT_SYMBOL(orinoco_खोलो);

पूर्णांक orinoco_stop(काष्ठा net_device *dev)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक err = 0;

	/* We mustn't use orinoco_lock() here, because we need to be
	   able to बंद the पूर्णांकerface even अगर hw_unavailable is set
	   (e.g. as we're released after a PC Card removal) */
	orinoco_lock_irq(priv);

	priv->खोलो = 0;

	err = __orinoco_करोwn(priv);

	orinoco_unlock_irq(priv);

	वापस err;
पूर्ण
EXPORT_SYMBOL(orinoco_stop);

व्योम orinoco_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0) अणु
		prपूर्णांकk(KERN_DEBUG "%s: orinoco_set_multicast_list() "
		       "called when hw_unavailable\n", dev->name);
		वापस;
	पूर्ण

	__orinoco_set_multicast_list(dev);
	orinoco_unlock(priv, &flags);
पूर्ण
EXPORT_SYMBOL(orinoco_set_multicast_list);

पूर्णांक orinoco_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);

	/* MTU + encapsulation + header length */
	अगर ((new_mtu + ENCAPS_OVERHEAD + माप(काष्ठा ieee80211_hdr)) >
	     (priv->nicbuf_size - ETH_HLEN))
		वापस -EINVAL;

	dev->mtu = new_mtu;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(orinoco_change_mtu);

/********************************************************************/
/* Tx path                                                          */
/********************************************************************/

/* Add encapsulation and MIC to the existing SKB.
 * The मुख्य xmit routine will then send the whole lot to the card.
 * Need 8 bytes headroom
 * Need 8 bytes tailroom
 *
 *                          With encapsulated ethernet II frame
 *                          --------
 *                          803.3 header (14 bytes)
 *                           dst[6]
 * --------                  src[6]
 * 803.3 header (14 bytes)   len[2]
 *  dst[6]                  803.2 header (8 bytes)
 *  src[6]                   encaps[6]
 *  len[2] <- leave alone -> len[2]
 * --------                 -------- <-- 0
 * Payload                  Payload
 * ...                      ...
 *
 * --------                 --------
 *                          MIC (8 bytes)
 *                          --------
 *
 * वापसs 0 on success, -ENOMEM on error.
 */
पूर्णांक orinoco_process_xmit_skb(काष्ठा sk_buff *skb,
			     काष्ठा net_device *dev,
			     काष्ठा orinoco_निजी *priv,
			     पूर्णांक *tx_control,
			     u8 *mic_buf)
अणु
	काष्ठा orinoco_tkip_key *key;
	काष्ठा ethhdr *eh;
	पूर्णांक करो_mic;

	key = (काष्ठा orinoco_tkip_key *) priv->keys[priv->tx_key].key;

	करो_mic = ((priv->encode_alg == ORINOCO_ALG_TKIP) &&
		  (key != शून्य));

	अगर (करो_mic)
		*tx_control |= (priv->tx_key << HERMES_MIC_KEY_ID_SHIFT) |
			HERMES_TXCTRL_MIC;

	eh = (काष्ठा ethhdr *)skb->data;

	/* Encapsulate Ethernet-II frames */
	अगर (ntohs(eh->h_proto) > ETH_DATA_LEN) अणु /* Ethernet-II frame */
		काष्ठा header_काष्ठा अणु
			काष्ठा ethhdr eth;	/* 802.3 header */
			u8 encap[6];		/* 802.2 header */
		पूर्ण __packed hdr;
		पूर्णांक len = skb->len + माप(encaps_hdr) - (2 * ETH_ALEN);

		अगर (skb_headroom(skb) < ENCAPS_OVERHEAD) अणु
			अगर (net_ratelimit())
				prपूर्णांकk(KERN_ERR
				       "%s: Not enough headroom for 802.2 headers %d\n",
				       dev->name, skb_headroom(skb));
			वापस -ENOMEM;
		पूर्ण

		/* Fill in new header */
		स_नकल(&hdr.eth, eh, 2 * ETH_ALEN);
		hdr.eth.h_proto = htons(len);
		स_नकल(hdr.encap, encaps_hdr, माप(encaps_hdr));

		/* Make room क्रम the new header, and copy it in */
		eh = skb_push(skb, ENCAPS_OVERHEAD);
		स_नकल(eh, &hdr, माप(hdr));
	पूर्ण

	/* Calculate Michael MIC */
	अगर (करो_mic) अणु
		माप_प्रकार len = skb->len - ETH_HLEN;
		u8 *mic = &mic_buf[0];

		/* Have to ग_लिखो to an even address, so copy the spare
		 * byte across */
		अगर (skb->len % 2) अणु
			*mic = skb->data[skb->len - 1];
			mic++;
		पूर्ण

		orinoco_mic(priv->tx_tfm_mic, key->tx_mic,
			    eh->h_dest, eh->h_source, 0 /* priority */,
			    skb->data + ETH_HLEN,
			    len, mic);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(orinoco_process_xmit_skb);

अटल netdev_tx_t orinoco_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err = 0;
	u16 txfid = priv->txfid;
	पूर्णांक tx_control;
	अचिन्हित दीर्घ flags;
	u8 mic_buf[MICHAEL_MIC_LEN + 1];

	अगर (!netअगर_running(dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: Tx on stopped device!\n",
		       dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (netअगर_queue_stopped(dev)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Tx while transmitter busy!\n",
		       dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (orinoco_lock(priv, &flags) != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: orinoco_xmit() called while hw_unavailable\n",
		       dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (!netअगर_carrier_ok(dev) ||
	    (priv->iw_mode == NL80211_IFTYPE_MONITOR)) अणु
		/* Oops, the firmware hasn't established a connection,
		   silently drop the packet (this seems to be the
		   safest approach). */
		जाओ drop;
	पूर्ण

	/* Check packet length */
	अगर (skb->len < ETH_HLEN)
		जाओ drop;

	tx_control = HERMES_TXCTRL_TX_OK | HERMES_TXCTRL_TX_EX;

	err = orinoco_process_xmit_skb(skb, dev, priv, &tx_control,
				       &mic_buf[0]);
	अगर (err)
		जाओ drop;

	अगर (priv->has_alt_txcntl) अणु
		/* WPA enabled firmwares have tx_cntl at the end of
		 * the 802.11 header.  So ग_लिखो zeroed descriptor and
		 * 802.11 header at the same समय
		 */
		अक्षर desc[HERMES_802_3_OFFSET];
		__le16 *txcntl = (__le16 *) &desc[HERMES_TXCNTL2_OFFSET];

		स_रखो(&desc, 0, माप(desc));

		*txcntl = cpu_to_le16(tx_control);
		err = hw->ops->bap_pग_लिखो(hw, USER_BAP, &desc, माप(desc),
					  txfid, 0);
		अगर (err) अणु
			अगर (net_ratelimit())
				prपूर्णांकk(KERN_ERR "%s: Error %d writing Tx "
				       "descriptor to BAP\n", dev->name, err);
			जाओ busy;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा hermes_tx_descriptor desc;

		स_रखो(&desc, 0, माप(desc));

		desc.tx_control = cpu_to_le16(tx_control);
		err = hw->ops->bap_pग_लिखो(hw, USER_BAP, &desc, माप(desc),
					  txfid, 0);
		अगर (err) अणु
			अगर (net_ratelimit())
				prपूर्णांकk(KERN_ERR "%s: Error %d writing Tx "
				       "descriptor to BAP\n", dev->name, err);
			जाओ busy;
		पूर्ण

		/* Clear the 802.11 header and data length fields - some
		 * firmwares (e.g. Lucent/Agere 8.xx) appear to get confused
		 * अगर this isn't करोne. */
		hermes_clear_words(hw, HERMES_DATA0,
				   HERMES_802_3_OFFSET - HERMES_802_11_OFFSET);
	पूर्ण

	err = hw->ops->bap_pग_लिखो(hw, USER_BAP, skb->data, skb->len,
				  txfid, HERMES_802_3_OFFSET);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d writing packet to BAP\n",
		       dev->name, err);
		जाओ busy;
	पूर्ण

	अगर (tx_control & HERMES_TXCTRL_MIC) अणु
		माप_प्रकार offset = HERMES_802_3_OFFSET + skb->len;
		माप_प्रकार len = MICHAEL_MIC_LEN;

		अगर (offset % 2) अणु
			offset--;
			len++;
		पूर्ण
		err = hw->ops->bap_pग_लिखो(hw, USER_BAP, &mic_buf[0], len,
					  txfid, offset);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d writing MIC to BAP\n",
			       dev->name, err);
			जाओ busy;
		पूर्ण
	पूर्ण

	/* Finally, we actually initiate the send */
	netअगर_stop_queue(dev);

	err = hw->ops->cmd_रुको(hw, HERMES_CMD_TX | HERMES_CMD_RECL,
				txfid, शून्य);
	अगर (err) अणु
		netअगर_start_queue(dev);
		अगर (net_ratelimit())
			prपूर्णांकk(KERN_ERR "%s: Error %d transmitting packet\n",
				dev->name, err);
		जाओ busy;
	पूर्ण

	stats->tx_bytes += HERMES_802_3_OFFSET + skb->len;
	जाओ ok;

 drop:
	stats->tx_errors++;
	stats->tx_dropped++;

 ok:
	orinoco_unlock(priv, &flags);
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;

 busy:
	अगर (err == -EIO)
		schedule_work(&priv->reset_work);
	orinoco_unlock(priv, &flags);
	वापस NETDEV_TX_BUSY;
पूर्ण

अटल व्योम __orinoco_ev_alloc(काष्ठा net_device *dev, काष्ठा hermes *hw)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	u16 fid = hermes_पढ़ो_regn(hw, ALLOCFID);

	अगर (fid != priv->txfid) अणु
		अगर (fid != DUMMY_FID)
			prपूर्णांकk(KERN_WARNING "%s: Allocate event on unexpected fid (%04X)\n",
			       dev->name, fid);
		वापस;
	पूर्ण

	hermes_ग_लिखो_regn(hw, ALLOCFID, DUMMY_FID);
पूर्ण

अटल व्योम __orinoco_ev_tx(काष्ठा net_device *dev, काष्ठा hermes *hw)
अणु
	dev->stats.tx_packets++;

	netअगर_wake_queue(dev);

	hermes_ग_लिखो_regn(hw, TXCOMPLFID, DUMMY_FID);
पूर्ण

अटल व्योम __orinoco_ev_txexc(काष्ठा net_device *dev, काष्ठा hermes *hw)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	u16 fid = hermes_पढ़ो_regn(hw, TXCOMPLFID);
	u16 status;
	काष्ठा hermes_txexc_data hdr;
	पूर्णांक err = 0;

	अगर (fid == DUMMY_FID)
		वापस; /* Nothing's really happened */

	/* Read part of the frame header - we need status and addr1 */
	err = hw->ops->bap_pपढ़ो(hw, IRQ_BAP, &hdr,
				 माप(काष्ठा hermes_txexc_data),
				 fid, 0);

	hermes_ग_लिखो_regn(hw, TXCOMPLFID, DUMMY_FID);
	stats->tx_errors++;

	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: Unable to read descriptor on Tx error "
		       "(FID=%04X error %d)\n",
		       dev->name, fid, err);
		वापस;
	पूर्ण

	DEBUG(1, "%s: Tx error, err %d (FID=%04X)\n", dev->name,
	      err, fid);

	/* We produce a TXDROP event only क्रम retry or lअगरeसमय
	 * exceeded, because that's the only status that really mean
	 * that this particular node went away.
	 * Other errors means that *we* screwed up. - Jean II */
	status = le16_to_cpu(hdr.desc.status);
	अगर (status & (HERMES_TXSTAT_RETRYERR | HERMES_TXSTAT_AGEDERR)) अणु
		जोड़ iwreq_data	wrqu;

		/* Copy 802.11 dest address.
		 * We use the 802.11 header because the frame may
		 * not be 802.3 or may be mangled...
		 * In Ad-Hoc mode, it will be the node address.
		 * In managed mode, it will be most likely the AP addr
		 * User space will figure out how to convert it to
		 * whatever it needs (IP address or अन्यथा).
		 * - Jean II */
		स_नकल(wrqu.addr.sa_data, hdr.addr1, ETH_ALEN);
		wrqu.addr.sa_family = ARPHRD_ETHER;

		/* Send event to user space */
		wireless_send_event(dev, IWEVTXDROP, &wrqu, शून्य);
	पूर्ण

	netअगर_wake_queue(dev);
पूर्ण

व्योम orinoco_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा hermes *hw = &priv->hw;

	prपूर्णांकk(KERN_WARNING "%s: Tx timeout! "
	       "ALLOCFID=%04x, TXCOMPLFID=%04x, EVSTAT=%04x\n",
	       dev->name, hermes_पढ़ो_regn(hw, ALLOCFID),
	       hermes_पढ़ो_regn(hw, TXCOMPLFID), hermes_पढ़ो_regn(hw, EVSTAT));

	stats->tx_errors++;

	schedule_work(&priv->reset_work);
पूर्ण
EXPORT_SYMBOL(orinoco_tx_समयout);

/********************************************************************/
/* Rx path (data frames)                                            */
/********************************************************************/

/* Does the frame have a SNAP header indicating it should be
 * de-encapsulated to Ethernet-II? */
अटल अंतरभूत पूर्णांक is_ethersnap(व्योम *_hdr)
अणु
	u8 *hdr = _hdr;

	/* We de-encapsulate all packets which, a) have SNAP headers
	 * (i.e. SSAP=DSAP=0xaa and CTRL=0x3 in the 802.2 LLC header
	 * and where b) the OUI of the SNAP header is 00:00:00 or
	 * 00:00:f8 - we need both because dअगरferent APs appear to use
	 * dअगरferent OUIs क्रम some reason */
	वापस (स_भेद(hdr, &encaps_hdr, 5) == 0)
		&& ((hdr[5] == 0x00) || (hdr[5] == 0xf8));
पूर्ण

अटल अंतरभूत व्योम orinoco_spy_gather(काष्ठा net_device *dev, u_अक्षर *mac,
				      पूर्णांक level, पूर्णांक noise)
अणु
	काष्ठा iw_quality wstats;
	wstats.level = level - 0x95;
	wstats.noise = noise - 0x95;
	wstats.qual = (level > noise) ? (level - noise) : 0;
	wstats.updated = IW_QUAL_ALL_UPDATED | IW_QUAL_DBM;
	/* Update spy records */
	wireless_spy_update(dev, mac, &wstats);
पूर्ण

अटल व्योम orinoco_stat_gather(काष्ठा net_device *dev,
				काष्ठा sk_buff *skb,
				काष्ठा hermes_rx_descriptor *desc)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);

	/* Using spy support with lots of Rx packets, like in an
	 * infraकाष्ठाure (AP), will really slow करोwn everything, because
	 * the MAC address must be compared to each entry of the spy list.
	 * If the user really asks क्रम it (set some address in the
	 * spy list), we करो it, but he will pay the price.
	 * Note that to get here, you need both WIRELESS_SPY
	 * compiled in AND some addresses in the list !!!
	 */
	/* Note : gcc will optimise the whole section away अगर
	 * WIRELESS_SPY is not defined... - Jean II */
	अगर (SPY_NUMBER(priv)) अणु
		orinoco_spy_gather(dev, skb_mac_header(skb) + ETH_ALEN,
				   desc->संकेत, desc->silence);
	पूर्ण
पूर्ण

/*
 * orinoco_rx_monitor - handle received monitor frames.
 *
 * Arguments:
 *	dev		network device
 *	rxfid		received FID
 *	desc		rx descriptor of the frame
 *
 * Call context: पूर्णांकerrupt
 */
अटल व्योम orinoco_rx_monitor(काष्ठा net_device *dev, u16 rxfid,
			       काष्ठा hermes_rx_descriptor *desc)
अणु
	u32 hdrlen = 30;	/* वापस full header by शेष */
	u32 datalen = 0;
	u16 fc;
	पूर्णांक err;
	पूर्णांक len;
	काष्ठा sk_buff *skb;
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा hermes *hw = &priv->hw;

	len = le16_to_cpu(desc->data_len);

	/* Determine the size of the header and the data */
	fc = le16_to_cpu(desc->frame_ctl);
	चयन (fc & IEEE80211_FCTL_FTYPE) अणु
	हाल IEEE80211_FTYPE_DATA:
		अगर ((fc & IEEE80211_FCTL_TODS)
		    && (fc & IEEE80211_FCTL_FROMDS))
			hdrlen = 30;
		अन्यथा
			hdrlen = 24;
		datalen = len;
		अवरोध;
	हाल IEEE80211_FTYPE_MGMT:
		hdrlen = 24;
		datalen = len;
		अवरोध;
	हाल IEEE80211_FTYPE_CTL:
		चयन (fc & IEEE80211_FCTL_STYPE) अणु
		हाल IEEE80211_STYPE_PSPOLL:
		हाल IEEE80211_STYPE_RTS:
		हाल IEEE80211_STYPE_CFEND:
		हाल IEEE80211_STYPE_CFENDACK:
			hdrlen = 16;
			अवरोध;
		हाल IEEE80211_STYPE_CTS:
		हाल IEEE80211_STYPE_ACK:
			hdrlen = 10;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		/* Unknown frame type */
		अवरोध;
	पूर्ण

	/* sanity check the length */
	अगर (datalen > IEEE80211_MAX_DATA_LEN + 12) अणु
		prपूर्णांकk(KERN_DEBUG "%s: oversized monitor frame, "
		       "data length = %d\n", dev->name, datalen);
		stats->rx_length_errors++;
		जाओ update_stats;
	पूर्ण

	skb = dev_alloc_skb(hdrlen + datalen);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_WARNING "%s: Cannot allocate skb for monitor frame\n",
		       dev->name);
		जाओ update_stats;
	पूर्ण

	/* Copy the 802.11 header to the skb */
	skb_put_data(skb, &(desc->frame_ctl), hdrlen);
	skb_reset_mac_header(skb);

	/* If any, copy the data from the card to the skb */
	अगर (datalen > 0) अणु
		err = hw->ops->bap_pपढ़ो(hw, IRQ_BAP, skb_put(skb, datalen),
					 ALIGN(datalen, 2), rxfid,
					 HERMES_802_2_OFFSET);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: error %d reading monitor frame\n",
			       dev->name, err);
			जाओ drop;
		पूर्ण
	पूर्ण

	skb->dev = dev;
	skb->ip_summed = CHECKSUM_NONE;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = cpu_to_be16(ETH_P_802_2);

	stats->rx_packets++;
	stats->rx_bytes += skb->len;

	netअगर_rx(skb);
	वापस;

 drop:
	dev_kमुक्त_skb_irq(skb);
 update_stats:
	stats->rx_errors++;
	stats->rx_dropped++;
पूर्ण

व्योम __orinoco_ev_rx(काष्ठा net_device *dev, काष्ठा hermes *hw)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा iw_statistics *wstats = &priv->wstats;
	काष्ठा sk_buff *skb = शून्य;
	u16 rxfid, status;
	पूर्णांक length;
	काष्ठा hermes_rx_descriptor *desc;
	काष्ठा orinoco_rx_data *rx_data;
	पूर्णांक err;

	desc = kदो_स्मृति(माप(*desc), GFP_ATOMIC);
	अगर (!desc)
		जाओ update_stats;

	rxfid = hermes_पढ़ो_regn(hw, RXFID);

	err = hw->ops->bap_pपढ़ो(hw, IRQ_BAP, desc, माप(*desc),
				 rxfid, 0);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: error %d reading Rx descriptor. "
		       "Frame dropped.\n", dev->name, err);
		जाओ update_stats;
	पूर्ण

	status = le16_to_cpu(desc->status);

	अगर (status & HERMES_RXSTAT_BADCRC) अणु
		DEBUG(1, "%s: Bad CRC on Rx. Frame dropped.\n",
		      dev->name);
		stats->rx_crc_errors++;
		जाओ update_stats;
	पूर्ण

	/* Handle frames in monitor mode */
	अगर (priv->iw_mode == NL80211_IFTYPE_MONITOR) अणु
		orinoco_rx_monitor(dev, rxfid, desc);
		जाओ out;
	पूर्ण

	अगर (status & HERMES_RXSTAT_UNDECRYPTABLE) अणु
		DEBUG(1, "%s: Undecryptable frame on Rx. Frame dropped.\n",
		      dev->name);
		wstats->discard.code++;
		जाओ update_stats;
	पूर्ण

	length = le16_to_cpu(desc->data_len);

	/* Sanity checks */
	अगर (length < 3) अणु /* No क्रम even an 802.2 LLC header */
		/* At least on Symbol firmware with PCF we get quite a
		   lot of these legitimately - Poll frames with no
		   data. */
		जाओ out;
	पूर्ण
	अगर (length > IEEE80211_MAX_DATA_LEN) अणु
		prपूर्णांकk(KERN_WARNING "%s: Oversized frame received (%d bytes)\n",
		       dev->name, length);
		stats->rx_length_errors++;
		जाओ update_stats;
	पूर्ण

	/* Payload size करोes not include Michael MIC. Increase payload
	 * size to पढ़ो it together with the data. */
	अगर (status & HERMES_RXSTAT_MIC)
		length += MICHAEL_MIC_LEN;

	/* We need space क्रम the packet data itself, plus an ethernet
	   header, plus 2 bytes so we can align the IP header on a
	   32bit boundary, plus 1 byte so we can पढ़ो in odd length
	   packets from the card, which has an IO granularity of 16
	   bits */
	skb = dev_alloc_skb(length + ETH_HLEN + 2 + 1);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_WARNING "%s: Can't allocate skb for Rx\n",
		       dev->name);
		जाओ update_stats;
	पूर्ण

	/* We'll prepend the header, so reserve space क्रम it.  The worst
	   हाल is no decapsulation, when 802.3 header is prepended and
	   nothing is हटाओd.  2 is क्रम aligning the IP header.  */
	skb_reserve(skb, ETH_HLEN + 2);

	err = hw->ops->bap_pपढ़ो(hw, IRQ_BAP, skb_put(skb, length),
				 ALIGN(length, 2), rxfid,
				 HERMES_802_2_OFFSET);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: error %d reading frame. "
		       "Frame dropped.\n", dev->name, err);
		जाओ drop;
	पूर्ण

	/* Add desc and skb to rx queue */
	rx_data = kzalloc(माप(*rx_data), GFP_ATOMIC);
	अगर (!rx_data)
		जाओ drop;

	rx_data->desc = desc;
	rx_data->skb = skb;
	list_add_tail(&rx_data->list, &priv->rx_list);
	tasklet_schedule(&priv->rx_tasklet);

	वापस;

drop:
	dev_kमुक्त_skb_irq(skb);
update_stats:
	stats->rx_errors++;
	stats->rx_dropped++;
out:
	kमुक्त(desc);
पूर्ण
EXPORT_SYMBOL(__orinoco_ev_rx);

अटल व्योम orinoco_rx(काष्ठा net_device *dev,
		       काष्ठा hermes_rx_descriptor *desc,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	u16 status, fc;
	पूर्णांक length;
	काष्ठा ethhdr *hdr;

	status = le16_to_cpu(desc->status);
	length = le16_to_cpu(desc->data_len);
	fc = le16_to_cpu(desc->frame_ctl);

	/* Calculate and check MIC */
	अगर (status & HERMES_RXSTAT_MIC) अणु
		काष्ठा orinoco_tkip_key *key;
		पूर्णांक key_id = ((status & HERMES_RXSTAT_MIC_KEY_ID) >>
			      HERMES_MIC_KEY_ID_SHIFT);
		u8 mic[MICHAEL_MIC_LEN];
		u8 *rxmic;
		u8 *src = (fc & IEEE80211_FCTL_FROMDS) ?
			desc->addr3 : desc->addr2;

		/* Extract Michael MIC from payload */
		rxmic = skb->data + skb->len - MICHAEL_MIC_LEN;

		skb_trim(skb, skb->len - MICHAEL_MIC_LEN);
		length -= MICHAEL_MIC_LEN;

		key = (काष्ठा orinoco_tkip_key *) priv->keys[key_id].key;

		अगर (!key) अणु
			prपूर्णांकk(KERN_WARNING "%s: Received encrypted frame from "
			       "%pM using key %i, but key is not installed\n",
			       dev->name, src, key_id);
			जाओ drop;
		पूर्ण

		orinoco_mic(priv->rx_tfm_mic, key->rx_mic, desc->addr1, src,
			    0, /* priority or QoS? */
			    skb->data, skb->len, &mic[0]);

		अगर (स_भेद(mic, rxmic,
			   MICHAEL_MIC_LEN)) अणु
			जोड़ iwreq_data wrqu;
			काष्ठा iw_michaelmicfailure wxmic;

			prपूर्णांकk(KERN_WARNING "%s: "
			       "Invalid Michael MIC in data frame from %pM, "
			       "using key %i\n",
			       dev->name, src, key_id);

			/* TODO: update stats */

			/* Notअगरy userspace */
			स_रखो(&wxmic, 0, माप(wxmic));
			wxmic.flags = key_id & IW_MICFAILURE_KEY_ID;
			wxmic.flags |= (desc->addr1[0] & 1) ?
				IW_MICFAILURE_GROUP : IW_MICFAILURE_PAIRWISE;
			wxmic.src_addr.sa_family = ARPHRD_ETHER;
			स_नकल(wxmic.src_addr.sa_data, src, ETH_ALEN);

			(व्योम) orinoco_hw_get_tkip_iv(priv, key_id,
						      &wxmic.tsc[0]);

			स_रखो(&wrqu, 0, माप(wrqu));
			wrqu.data.length = माप(wxmic);
			wireless_send_event(dev, IWEVMICHAELMICFAILURE, &wrqu,
					    (अक्षर *) &wxmic);

			जाओ drop;
		पूर्ण
	पूर्ण

	/* Handle decapsulation
	 * In most हालs, the firmware tell us about SNAP frames.
	 * For some reason, the SNAP frames sent by LinkSys APs
	 * are not properly recognised by most firmwares.
	 * So, check ourselves */
	अगर (length >= ENCAPS_OVERHEAD &&
	    (((status & HERMES_RXSTAT_MSGTYPE) == HERMES_RXSTAT_1042) ||
	     ((status & HERMES_RXSTAT_MSGTYPE) == HERMES_RXSTAT_TUNNEL) ||
	     is_ethersnap(skb->data))) अणु
		/* These indicate a SNAP within 802.2 LLC within
		   802.11 frame which we'll need to de-encapsulate to
		   the original EthernetII frame. */
		hdr = skb_push(skb, ETH_HLEN - ENCAPS_OVERHEAD);
	पूर्ण अन्यथा अणु
		/* 802.3 frame - prepend 802.3 header as is */
		hdr = skb_push(skb, ETH_HLEN);
		hdr->h_proto = htons(length);
	पूर्ण
	स_नकल(hdr->h_dest, desc->addr1, ETH_ALEN);
	अगर (fc & IEEE80211_FCTL_FROMDS)
		स_नकल(hdr->h_source, desc->addr3, ETH_ALEN);
	अन्यथा
		स_नकल(hdr->h_source, desc->addr2, ETH_ALEN);

	skb->protocol = eth_type_trans(skb, dev);
	skb->ip_summed = CHECKSUM_NONE;
	अगर (fc & IEEE80211_FCTL_TODS)
		skb->pkt_type = PACKET_OTHERHOST;

	/* Process the wireless stats अगर needed */
	orinoco_stat_gather(dev, skb, desc);

	/* Pass the packet to the networking stack */
	netअगर_rx(skb);
	stats->rx_packets++;
	stats->rx_bytes += length;

	वापस;

 drop:
	dev_kमुक्त_skb(skb);
	stats->rx_errors++;
	stats->rx_dropped++;
पूर्ण

अटल व्योम orinoco_rx_isr_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा orinoco_निजी *priv = from_tasklet(priv, t, rx_tasklet);
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा orinoco_rx_data *rx_data, *temp;
	काष्ठा hermes_rx_descriptor *desc;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	/* orinoco_rx requires the driver lock, and we also need to
	 * protect priv->rx_list, so just hold the lock over the
	 * lot.
	 *
	 * If orinoco_lock fails, we've unplugged the card. In this
	 * हाल just पात. */
	अगर (orinoco_lock(priv, &flags) != 0)
		वापस;

	/* extract desc and skb from queue */
	list_क्रम_each_entry_safe(rx_data, temp, &priv->rx_list, list) अणु
		desc = rx_data->desc;
		skb = rx_data->skb;
		list_del(&rx_data->list);
		kमुक्त(rx_data);

		orinoco_rx(dev, desc, skb);

		kमुक्त(desc);
	पूर्ण

	orinoco_unlock(priv, &flags);
पूर्ण

/********************************************************************/
/* Rx path (info frames)                                            */
/********************************************************************/

अटल व्योम prपूर्णांक_linkstatus(काष्ठा net_device *dev, u16 status)
अणु
	अक्षर *s;

	अगर (suppress_linkstatus)
		वापस;

	चयन (status) अणु
	हाल HERMES_LINKSTATUS_NOT_CONNECTED:
		s = "Not Connected";
		अवरोध;
	हाल HERMES_LINKSTATUS_CONNECTED:
		s = "Connected";
		अवरोध;
	हाल HERMES_LINKSTATUS_DISCONNECTED:
		s = "Disconnected";
		अवरोध;
	हाल HERMES_LINKSTATUS_AP_CHANGE:
		s = "AP Changed";
		अवरोध;
	हाल HERMES_LINKSTATUS_AP_OUT_OF_RANGE:
		s = "AP Out of Range";
		अवरोध;
	हाल HERMES_LINKSTATUS_AP_IN_RANGE:
		s = "AP In Range";
		अवरोध;
	हाल HERMES_LINKSTATUS_ASSOC_FAILED:
		s = "Association Failed";
		अवरोध;
	शेष:
		s = "UNKNOWN";
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: New link status: %s (%04x)\n",
	       dev->name, s, status);
पूर्ण

/* Search scan results क्रम requested BSSID, join it अगर found */
अटल व्योम orinoco_join_ap(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा orinoco_निजी *priv =
		container_of(work, काष्ठा orinoco_निजी, join_work);
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	काष्ठा join_req अणु
		u8 bssid[ETH_ALEN];
		__le16 channel;
	पूर्ण __packed req;
	स्थिर पूर्णांक atom_len = दुरत्व(काष्ठा prism2_scan_apinfo, atim);
	काष्ठा prism2_scan_apinfo *atom = शून्य;
	पूर्णांक offset = 4;
	पूर्णांक found = 0;
	u8 *buf;
	u16 len;

	/* Allocate buffer क्रम scan results */
	buf = kदो_स्मृति(MAX_SCAN_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस;

	अगर (orinoco_lock(priv, &flags) != 0)
		जाओ fail_lock;

	/* Sanity checks in हाल user changed something in the meanसमय */
	अगर (!priv->bssid_fixed)
		जाओ out;

	अगर (म_माप(priv->desired_essid) == 0)
		जाओ out;

	/* Read scan results from the firmware */
	err = hw->ops->पढ़ो_ltv(hw, USER_BAP,
				HERMES_RID_SCANRESULTSTABLE,
				MAX_SCAN_LEN, &len, buf);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot read scan results\n",
		       dev->name);
		जाओ out;
	पूर्ण

	len = HERMES_RECLEN_TO_BYTES(len);

	/* Go through the scan results looking क्रम the channel of the AP
	 * we were requested to join */
	क्रम (; offset + atom_len <= len; offset += atom_len) अणु
		atom = (काष्ठा prism2_scan_apinfo *) (buf + offset);
		अगर (स_भेद(&atom->bssid, priv->desired_bssid, ETH_ALEN) == 0) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		DEBUG(1, "%s: Requested AP not found in scan results\n",
		      dev->name);
		जाओ out;
	पूर्ण

	स_नकल(req.bssid, priv->desired_bssid, ETH_ALEN);
	req.channel = atom->channel;	/* both are little-endian */
	err = HERMES_WRITE_RECORD(hw, USER_BAP, HERMES_RID_CNFJOINREQUEST,
				  &req);
	अगर (err)
		prपूर्णांकk(KERN_ERR "%s: Error issuing join request\n", dev->name);

 out:
	orinoco_unlock(priv, &flags);

 fail_lock:
	kमुक्त(buf);
पूर्ण

/* Send new BSSID to userspace */
अटल व्योम orinoco_send_bssid_wevent(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	जोड़ iwreq_data wrqu;
	पूर्णांक err;

	err = hw->ops->पढ़ो_ltv(hw, USER_BAP, HERMES_RID_CURRENTBSSID,
				ETH_ALEN, शून्य, wrqu.ap_addr.sa_data);
	अगर (err != 0)
		वापस;

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	/* Send event to user space */
	wireless_send_event(dev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण

अटल व्योम orinoco_send_assocreqie_wevent(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	जोड़ iwreq_data wrqu;
	पूर्णांक err;
	u8 buf[88];
	u8 *ie;

	अगर (!priv->has_wpa)
		वापस;

	err = hw->ops->पढ़ो_ltv(hw, USER_BAP, HERMES_RID_CURRENT_ASSOC_REQ_INFO,
				माप(buf), शून्य, &buf);
	अगर (err != 0)
		वापस;

	ie = orinoco_get_wpa_ie(buf, माप(buf));
	अगर (ie) अणु
		पूर्णांक rem = माप(buf) - (ie - &buf[0]);
		wrqu.data.length = ie[1] + 2;
		अगर (wrqu.data.length > rem)
			wrqu.data.length = rem;

		अगर (wrqu.data.length)
			/* Send event to user space */
			wireless_send_event(dev, IWEVASSOCREQIE, &wrqu, ie);
	पूर्ण
पूर्ण

अटल व्योम orinoco_send_assocrespie_wevent(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	जोड़ iwreq_data wrqu;
	पूर्णांक err;
	u8 buf[88]; /* TODO: verअगरy max size or IW_GENERIC_IE_MAX */
	u8 *ie;

	अगर (!priv->has_wpa)
		वापस;

	err = hw->ops->पढ़ो_ltv(hw, USER_BAP,
				HERMES_RID_CURRENT_ASSOC_RESP_INFO,
				माप(buf), शून्य, &buf);
	अगर (err != 0)
		वापस;

	ie = orinoco_get_wpa_ie(buf, माप(buf));
	अगर (ie) अणु
		पूर्णांक rem = माप(buf) - (ie - &buf[0]);
		wrqu.data.length = ie[1] + 2;
		अगर (wrqu.data.length > rem)
			wrqu.data.length = rem;

		अगर (wrqu.data.length)
			/* Send event to user space */
			wireless_send_event(dev, IWEVASSOCRESPIE, &wrqu, ie);
	पूर्ण
पूर्ण

अटल व्योम orinoco_send_wevents(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा orinoco_निजी *priv =
		container_of(work, काष्ठा orinoco_निजी, wevent_work);
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस;

	orinoco_send_assocreqie_wevent(priv);
	orinoco_send_assocrespie_wevent(priv);
	orinoco_send_bssid_wevent(priv);

	orinoco_unlock(priv, &flags);
पूर्ण

अटल व्योम qbuf_scan(काष्ठा orinoco_निजी *priv, व्योम *buf,
		      पूर्णांक len, पूर्णांक type)
अणु
	काष्ठा orinoco_scan_data *sd;
	अचिन्हित दीर्घ flags;

	sd = kदो_स्मृति(माप(*sd), GFP_ATOMIC);
	अगर (!sd)
		वापस;

	sd->buf = buf;
	sd->len = len;
	sd->type = type;

	spin_lock_irqsave(&priv->scan_lock, flags);
	list_add_tail(&sd->list, &priv->scan_list);
	spin_unlock_irqrestore(&priv->scan_lock, flags);

	schedule_work(&priv->process_scan);
पूर्ण

अटल व्योम qपात_scan(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा orinoco_scan_data *sd;
	अचिन्हित दीर्घ flags;

	sd = kदो_स्मृति(माप(*sd), GFP_ATOMIC);
	अगर (!sd)
		वापस;

	sd->len = -1; /* Abort */

	spin_lock_irqsave(&priv->scan_lock, flags);
	list_add_tail(&sd->list, &priv->scan_list);
	spin_unlock_irqrestore(&priv->scan_lock, flags);

	schedule_work(&priv->process_scan);
पूर्ण

अटल व्योम orinoco_process_scan_results(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा orinoco_निजी *priv =
		container_of(work, काष्ठा orinoco_निजी, process_scan);
	काष्ठा orinoco_scan_data *sd, *temp;
	अचिन्हित दीर्घ flags;
	व्योम *buf;
	पूर्णांक len;
	पूर्णांक type;

	spin_lock_irqsave(&priv->scan_lock, flags);
	list_क्रम_each_entry_safe(sd, temp, &priv->scan_list, list) अणु

		buf = sd->buf;
		len = sd->len;
		type = sd->type;

		list_del(&sd->list);
		spin_unlock_irqrestore(&priv->scan_lock, flags);
		kमुक्त(sd);

		अगर (len > 0) अणु
			अगर (type == HERMES_INQ_CHANNELINFO)
				orinoco_add_extscan_result(priv, buf, len);
			अन्यथा
				orinoco_add_hostscan_results(priv, buf, len);

			kमुक्त(buf);
		पूर्ण अन्यथा अणु
			/* Either पात or complete the scan */
			orinoco_scan_करोne(priv, (len < 0));
		पूर्ण

		spin_lock_irqsave(&priv->scan_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&priv->scan_lock, flags);
पूर्ण

व्योम __orinoco_ev_info(काष्ठा net_device *dev, काष्ठा hermes *hw)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	u16 infofid;
	काष्ठा अणु
		__le16 len;
		__le16 type;
	पूर्ण __packed info;
	पूर्णांक len, type;
	पूर्णांक err;

	/* This is an answer to an INQUIRE command that we did earlier,
	 * or an inक्रमmation "event" generated by the card
	 * The controller वापस to us a pseuकरो frame containing
	 * the inक्रमmation in question - Jean II */
	infofid = hermes_पढ़ो_regn(hw, INFOFID);

	/* Read the info frame header - करोn't try too hard */
	err = hw->ops->bap_pपढ़ो(hw, IRQ_BAP, &info, माप(info),
				 infofid, 0);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: error %d reading info frame. "
		       "Frame dropped.\n", dev->name, err);
		वापस;
	पूर्ण

	len = HERMES_RECLEN_TO_BYTES(le16_to_cpu(info.len));
	type = le16_to_cpu(info.type);

	चयन (type) अणु
	हाल HERMES_INQ_TALLIES: अणु
		काष्ठा hermes_tallies_frame tallies;
		काष्ठा iw_statistics *wstats = &priv->wstats;

		अगर (len > माप(tallies)) अणु
			prपूर्णांकk(KERN_WARNING "%s: Tallies frame too long (%d bytes)\n",
			       dev->name, len);
			len = माप(tallies);
		पूर्ण

		err = hw->ops->bap_pपढ़ो(hw, IRQ_BAP, &tallies, len,
					 infofid, माप(info));
		अगर (err)
			अवरोध;

		/* Increment our various counters */
		/* wstats->discard.nwid - no wrong BSSID stuff */
		wstats->discard.code +=
			le16_to_cpu(tallies.RxWEPUndecryptable);
		अगर (len == माप(tallies))
			wstats->discard.code +=
				le16_to_cpu(tallies.RxDiscards_WEPICVError) +
				le16_to_cpu(tallies.RxDiscards_WEPExcluded);
		wstats->discard.misc +=
			le16_to_cpu(tallies.TxDiscardsWrongSA);
		wstats->discard.fragment +=
			le16_to_cpu(tallies.RxMsgInBadMsgFragments);
		wstats->discard.retries +=
			le16_to_cpu(tallies.TxRetryLimitExceeded);
		/* wstats->miss.beacon - no match */
	पूर्ण
	अवरोध;
	हाल HERMES_INQ_LINKSTATUS: अणु
		काष्ठा hermes_linkstatus linkstatus;
		u16 newstatus;
		पूर्णांक connected;

		अगर (priv->iw_mode == NL80211_IFTYPE_MONITOR)
			अवरोध;

		अगर (len != माप(linkstatus)) अणु
			prपूर्णांकk(KERN_WARNING "%s: Unexpected size for linkstatus frame (%d bytes)\n",
			       dev->name, len);
			अवरोध;
		पूर्ण

		err = hw->ops->bap_pपढ़ो(hw, IRQ_BAP, &linkstatus, len,
					 infofid, माप(info));
		अगर (err)
			अवरोध;
		newstatus = le16_to_cpu(linkstatus.linkstatus);

		/* Symbol firmware uses "out of range" to संकेत that
		 * the hostscan frame can be requested.  */
		अगर (newstatus == HERMES_LINKSTATUS_AP_OUT_OF_RANGE &&
		    priv->firmware_type == FIRMWARE_TYPE_SYMBOL &&
		    priv->has_hostscan && priv->scan_request) अणु
			hermes_inquire(hw, HERMES_INQ_HOSTSCAN_SYMBOL);
			अवरोध;
		पूर्ण

		connected = (newstatus == HERMES_LINKSTATUS_CONNECTED)
			|| (newstatus == HERMES_LINKSTATUS_AP_CHANGE)
			|| (newstatus == HERMES_LINKSTATUS_AP_IN_RANGE);

		अगर (connected)
			netअगर_carrier_on(dev);
		अन्यथा अगर (!ignore_disconnect)
			netअगर_carrier_off(dev);

		अगर (newstatus != priv->last_linkstatus) अणु
			priv->last_linkstatus = newstatus;
			prपूर्णांक_linkstatus(dev, newstatus);
			/* The info frame contains only one word which is the
			 * status (see hermes.h). The status is pretty boring
			 * in itself, that's why we export the new BSSID...
			 * Jean II */
			schedule_work(&priv->wevent_work);
		पूर्ण
	पूर्ण
	अवरोध;
	हाल HERMES_INQ_SCAN:
		अगर (!priv->scan_request && priv->bssid_fixed &&
		    priv->firmware_type == FIRMWARE_TYPE_INTERSIL) अणु
			schedule_work(&priv->join_work);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल HERMES_INQ_HOSTSCAN:
	हाल HERMES_INQ_HOSTSCAN_SYMBOL: अणु
		/* Result of a scanning. Contains inक्रमmation about
		 * cells in the vicinity - Jean II */
		अचिन्हित अक्षर *buf;

		/* Sanity check */
		अगर (len > 4096) अणु
			prपूर्णांकk(KERN_WARNING "%s: Scan results too large (%d bytes)\n",
			       dev->name, len);
			qपात_scan(priv);
			अवरोध;
		पूर्ण

		/* Allocate buffer क्रम results */
		buf = kदो_स्मृति(len, GFP_ATOMIC);
		अगर (buf == शून्य) अणु
			/* No memory, so can't prपूर्णांकk()... */
			qपात_scan(priv);
			अवरोध;
		पूर्ण

		/* Read scan data */
		err = hw->ops->bap_pपढ़ो(hw, IRQ_BAP, (व्योम *) buf, len,
					 infofid, माप(info));
		अगर (err) अणु
			kमुक्त(buf);
			qपात_scan(priv);
			अवरोध;
		पूर्ण

#अगर_घोषित ORINOCO_DEBUG
		अणु
			पूर्णांक	i;
			prपूर्णांकk(KERN_DEBUG "Scan result [%02X", buf[0]);
			क्रम (i = 1; i < (len * 2); i++)
				prपूर्णांकk(":%02X", buf[i]);
			prपूर्णांकk("]\n");
		पूर्ण
#पूर्ण_अगर	/* ORINOCO_DEBUG */

		qbuf_scan(priv, buf, len, type);
	पूर्ण
	अवरोध;
	हाल HERMES_INQ_CHANNELINFO:
	अणु
		काष्ठा agere_ext_scan_info *bss;

		अगर (!priv->scan_request) अणु
			prपूर्णांकk(KERN_DEBUG "%s: Got chaninfo without scan, "
			       "len=%d\n", dev->name, len);
			अवरोध;
		पूर्ण

		/* An empty result indicates that the scan is complete */
		अगर (len == 0) अणु
			qbuf_scan(priv, शून्य, len, type);
			अवरोध;
		पूर्ण

		/* Sanity check */
		अन्यथा अगर (len < (दुरत्व(काष्ठा agere_ext_scan_info,
					   data) + 2)) अणु
			/* Drop this result now so we करोn't have to
			 * keep checking later */
			prपूर्णांकk(KERN_WARNING
			       "%s: Ext scan results too short (%d bytes)\n",
			       dev->name, len);
			अवरोध;
		पूर्ण

		bss = kदो_स्मृति(len, GFP_ATOMIC);
		अगर (bss == शून्य)
			अवरोध;

		/* Read scan data */
		err = hw->ops->bap_pपढ़ो(hw, IRQ_BAP, (व्योम *) bss, len,
					 infofid, माप(info));
		अगर (err)
			kमुक्त(bss);
		अन्यथा
			qbuf_scan(priv, bss, len, type);

		अवरोध;
	पूर्ण
	हाल HERMES_INQ_SEC_STAT_AGERE:
		/* Security status (Agere specअगरic) */
		/* Ignore this frame क्रम now */
		अगर (priv->firmware_type == FIRMWARE_TYPE_AGERE)
			अवरोध;
		fallthrough;
	शेष:
		prपूर्णांकk(KERN_DEBUG "%s: Unknown information frame received: "
		       "type 0x%04x, length %d\n", dev->name, type, len);
		/* We करोn't actually करो anything about it */
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__orinoco_ev_info);

अटल व्योम __orinoco_ev_infdrop(काष्ठा net_device *dev, काष्ठा hermes *hw)
अणु
	अगर (net_ratelimit())
		prपूर्णांकk(KERN_DEBUG "%s: Information frame lost.\n", dev->name);
पूर्ण

/********************************************************************/
/* Internal hardware control routines                               */
/********************************************************************/

अटल पूर्णांक __orinoco_up(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;

	netअगर_carrier_off(dev); /* just to make sure */

	err = __orinoco_commit(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d configuring card\n",
		       dev->name, err);
		वापस err;
	पूर्ण

	/* Fire things up again */
	hermes_set_irqmask(hw, ORINOCO_INTEN);
	err = hermes_enable_port(hw, 0);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d enabling MAC port\n",
		       dev->name, err);
		वापस err;
	पूर्ण

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __orinoco_करोwn(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;

	netअगर_stop_queue(dev);

	अगर (!priv->hw_unavailable) अणु
		अगर (!priv->broken_disableport) अणु
			err = hermes_disable_port(hw, 0);
			अगर (err) अणु
				/* Some firmwares (e.g. Intersil 1.3.x) seem
				 * to have problems disabling the port, oh
				 * well, too bad. */
				prपूर्णांकk(KERN_WARNING "%s: Error %d disabling MAC port\n",
				       dev->name, err);
				priv->broken_disableport = 1;
			पूर्ण
		पूर्ण
		hermes_set_irqmask(hw, 0);
		hermes_ग_लिखो_regn(hw, EVACK, 0xffff);
	पूर्ण

	orinoco_scan_करोne(priv, true);

	/* firmware will have to reassociate */
	netअगर_carrier_off(dev);
	priv->last_linkstatus = 0xffff;

	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_reinit_firmware(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;

	err = hw->ops->init(hw);
	अगर (priv->करो_fw_करोwnload && !err) अणु
		err = orinoco_करोwnload(priv);
		अगर (err)
			priv->करो_fw_करोwnload = 0;
	पूर्ण
	अगर (!err)
		err = orinoco_hw_allocate_fid(priv);

	वापस err;
पूर्ण

अटल पूर्णांक
__orinoco_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक err = 0;
	पूर्णांक promisc, mc_count;

	/* The Hermes करोesn't seem to have an allmulti mode, so we go
	 * पूर्णांकo promiscuous mode and let the upper levels deal. */
	अगर ((dev->flags & IFF_PROMISC) || (dev->flags & IFF_ALLMULTI) ||
	    (netdev_mc_count(dev) > MAX_MULTICAST(priv))) अणु
		promisc = 1;
		mc_count = 0;
	पूर्ण अन्यथा अणु
		promisc = 0;
		mc_count = netdev_mc_count(dev);
	पूर्ण

	err = __orinoco_hw_set_multicast_list(priv, dev, mc_count, promisc);

	वापस err;
पूर्ण

/* This must be called from user context, without locks held - use
 * schedule_work() */
व्योम orinoco_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा orinoco_निजी *priv =
		container_of(work, काष्ठा orinoco_निजी, reset_work);
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		/* When the hardware becomes available again, whatever
		 * detects that is responsible क्रम re-initializing
		 * it. So no need क्रम anything further */
		वापस;

	netअगर_stop_queue(dev);

	/* Shut off पूर्णांकerrupts.  Depending on what state the hardware
	 * is in, this might not work, but we'll try anyway */
	hermes_set_irqmask(hw, 0);
	hermes_ग_लिखो_regn(hw, EVACK, 0xffff);

	priv->hw_unavailable++;
	priv->last_linkstatus = 0xffff; /* firmware will have to reassociate */
	netअगर_carrier_off(dev);

	orinoco_unlock(priv, &flags);

	/* Scanning support: Notअगरy scan cancellation */
	orinoco_scan_करोne(priv, true);

	अगर (priv->hard_reset) अणु
		err = (*priv->hard_reset)(priv);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: orinoco_reset: Error %d "
			       "performing hard reset\n", dev->name, err);
			जाओ disable;
		पूर्ण
	पूर्ण

	err = orinoco_reinit_firmware(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: orinoco_reset: Error %d re-initializing firmware\n",
		       dev->name, err);
		जाओ disable;
	पूर्ण

	/* This has to be called from user context */
	orinoco_lock_irq(priv);

	priv->hw_unavailable--;

	/* priv->खोलो or priv->hw_unavailable might have changed जबतक
	 * we dropped the lock */
	अगर (priv->खोलो && (!priv->hw_unavailable)) अणु
		err = __orinoco_up(priv);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: orinoco_reset: Error %d reenabling card\n",
			       dev->name, err);
		पूर्ण अन्यथा
			netअगर_trans_update(dev);
	पूर्ण

	orinoco_unlock_irq(priv);

	वापस;
 disable:
	hermes_set_irqmask(hw, 0);
	netअगर_device_detach(dev);
	prपूर्णांकk(KERN_ERR "%s: Device has been disabled!\n", dev->name);
पूर्ण

अटल पूर्णांक __orinoco_commit(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	पूर्णांक err = 0;

	/* If we've called commit, we are reconfiguring or bringing the
	 * पूर्णांकerface up. Maपूर्णांकaining countermeasures across this would
	 * be confusing, so note that we've disabled them. The port will
	 * be enabled later in orinoco_commit or __orinoco_up. */
	priv->tkip_cm_active = 0;

	err = orinoco_hw_program_rids(priv);

	/* FIXME: what about netअगर_tx_lock */
	(व्योम) __orinoco_set_multicast_list(dev);

	वापस err;
पूर्ण

/* Ensures configuration changes are applied. May result in a reset.
 * The caller should hold priv->lock
 */
पूर्णांक orinoco_commit(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;

	अगर (priv->broken_disableport) अणु
		schedule_work(&priv->reset_work);
		वापस 0;
	पूर्ण

	err = hermes_disable_port(hw, 0);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: Unable to disable port "
		       "while reconfiguring card\n", dev->name);
		priv->broken_disableport = 1;
		जाओ out;
	पूर्ण

	err = __orinoco_commit(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: Unable to reconfigure card\n",
		       dev->name);
		जाओ out;
	पूर्ण

	err = hermes_enable_port(hw, 0);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: Unable to enable port while reconfiguring card\n",
		       dev->name);
		जाओ out;
	पूर्ण

 out:
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: Resetting instead...\n", dev->name);
		schedule_work(&priv->reset_work);
		err = 0;
	पूर्ण
	वापस err;
पूर्ण

/********************************************************************/
/* Interrupt handler                                                */
/********************************************************************/

अटल व्योम __orinoco_ev_tick(काष्ठा net_device *dev, काष्ठा hermes *hw)
अणु
	prपूर्णांकk(KERN_DEBUG "%s: TICK\n", dev->name);
पूर्ण

अटल व्योम __orinoco_ev_wterr(काष्ठा net_device *dev, काष्ठा hermes *hw)
अणु
	/* This seems to happen a fair bit under load, but ignoring it
	   seems to work fine...*/
	prपूर्णांकk(KERN_DEBUG "%s: MAC controller error (WTERR). Ignoring.\n",
	       dev->name);
पूर्ण

irqवापस_t orinoco_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा orinoco_निजी *priv = dev_id;
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक count = MAX_IRQLOOPS_PER_IRQ;
	u16 evstat, events;
	/* These are used to detect a runaway पूर्णांकerrupt situation.
	 *
	 * If we get more than MAX_IRQLOOPS_PER_JIFFY iterations in a jअगरfy,
	 * we panic and shut करोwn the hardware
	 */
	/* jअगरfies value the last समय we were called */
	अटल पूर्णांक last_irq_jअगरfy; /* = 0 */
	अटल पूर्णांक loops_this_jअगरfy; /* = 0 */
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0) अणु
		/* If hw is unavailable - we करोn't know अगर the irq was
		 * क्रम us or not */
		वापस IRQ_HANDLED;
	पूर्ण

	evstat = hermes_पढ़ो_regn(hw, EVSTAT);
	events = evstat & hw->पूर्णांकen;
	अगर (!events) अणु
		orinoco_unlock(priv, &flags);
		वापस IRQ_NONE;
	पूर्ण

	अगर (jअगरfies != last_irq_jअगरfy)
		loops_this_jअगरfy = 0;
	last_irq_jअगरfy = jअगरfies;

	जबतक (events && count--) अणु
		अगर (++loops_this_jअगरfy > MAX_IRQLOOPS_PER_JIFFY) अणु
			prपूर्णांकk(KERN_WARNING "%s: IRQ handler is looping too "
			       "much! Resetting.\n", dev->name);
			/* Disable पूर्णांकerrupts क्रम now */
			hermes_set_irqmask(hw, 0);
			schedule_work(&priv->reset_work);
			अवरोध;
		पूर्ण

		/* Check the card hasn't been हटाओd */
		अगर (!hermes_present(hw)) अणु
			DEBUG(0, "orinoco_interrupt(): card removed\n");
			अवरोध;
		पूर्ण

		अगर (events & HERMES_EV_TICK)
			__orinoco_ev_tick(dev, hw);
		अगर (events & HERMES_EV_WTERR)
			__orinoco_ev_wterr(dev, hw);
		अगर (events & HERMES_EV_INFDROP)
			__orinoco_ev_infdrop(dev, hw);
		अगर (events & HERMES_EV_INFO)
			__orinoco_ev_info(dev, hw);
		अगर (events & HERMES_EV_RX)
			__orinoco_ev_rx(dev, hw);
		अगर (events & HERMES_EV_TXEXC)
			__orinoco_ev_txexc(dev, hw);
		अगर (events & HERMES_EV_TX)
			__orinoco_ev_tx(dev, hw);
		अगर (events & HERMES_EV_ALLOC)
			__orinoco_ev_alloc(dev, hw);

		hermes_ग_लिखो_regn(hw, EVACK, evstat);

		evstat = hermes_पढ़ो_regn(hw, EVSTAT);
		events = evstat & hw->पूर्णांकen;
	पूर्ण

	orinoco_unlock(priv, &flags);
	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(orinoco_पूर्णांकerrupt);

/********************************************************************/
/* Power management                                                 */
/********************************************************************/
#अगर defined(CONFIG_PM_SLEEP) && !defined(CONFIG_HERMES_CACHE_FW_ON_INIT)
अटल पूर्णांक orinoco_pm_notअगरier(काष्ठा notअगरier_block *notअगरier,
			       अचिन्हित दीर्घ pm_event,
			       व्योम *unused)
अणु
	काष्ठा orinoco_निजी *priv = container_of(notअगरier,
						    काष्ठा orinoco_निजी,
						    pm_notअगरier);

	/* All we need to करो is cache the firmware beक्रमe suspend, and
	 * release it when we come out.
	 *
	 * Only need to करो this अगर we're करोwnloading firmware. */
	अगर (!priv->करो_fw_करोwnload)
		वापस NOTIFY_DONE;

	चयन (pm_event) अणु
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_SUSPEND_PREPARE:
		orinoco_cache_fw(priv, 0);
		अवरोध;

	हाल PM_POST_RESTORE:
		/* Restore from hibernation failed. We need to clean
		 * up in exactly the same way, so fall through. */
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_SUSPEND:
		orinoco_uncache_fw(priv);
		अवरोध;

	हाल PM_RESTORE_PREPARE:
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम orinoco_रेजिस्टर_pm_notअगरier(काष्ठा orinoco_निजी *priv)
अणु
	priv->pm_notअगरier.notअगरier_call = orinoco_pm_notअगरier;
	रेजिस्टर_pm_notअगरier(&priv->pm_notअगरier);
पूर्ण

अटल व्योम orinoco_unरेजिस्टर_pm_notअगरier(काष्ठा orinoco_निजी *priv)
अणु
	unरेजिस्टर_pm_notअगरier(&priv->pm_notअगरier);
पूर्ण
#अन्यथा /* !PM_SLEEP || HERMES_CACHE_FW_ON_INIT */
#घोषणा orinoco_रेजिस्टर_pm_notअगरier(priv) करो अणु पूर्ण जबतक (0)
#घोषणा orinoco_unरेजिस्टर_pm_notअगरier(priv) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/********************************************************************/
/* Initialization                                                   */
/********************************************************************/

पूर्णांक orinoco_init(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा wiphy *wiphy = priv_to_wiphy(priv);
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err = 0;

	/* No need to lock, the hw_unavailable flag is alपढ़ोy set in
	 * alloc_orinocodev() */
	priv->nicbuf_size = IEEE80211_MAX_FRAME_LEN + ETH_HLEN;

	/* Initialize the firmware */
	err = hw->ops->init(hw);
	अगर (err != 0) अणु
		dev_err(dev, "Failed to initialize firmware (err = %d)\n",
			err);
		जाओ out;
	पूर्ण

	err = determine_fw_capabilities(priv, wiphy->fw_version,
					माप(wiphy->fw_version),
					&wiphy->hw_version);
	अगर (err != 0) अणु
		dev_err(dev, "Incompatible firmware, aborting\n");
		जाओ out;
	पूर्ण

	अगर (priv->करो_fw_करोwnload) अणु
#अगर_घोषित CONFIG_HERMES_CACHE_FW_ON_INIT
		orinoco_cache_fw(priv, 0);
#पूर्ण_अगर

		err = orinoco_करोwnload(priv);
		अगर (err)
			priv->करो_fw_करोwnload = 0;

		/* Check firmware version again */
		err = determine_fw_capabilities(priv, wiphy->fw_version,
						माप(wiphy->fw_version),
						&wiphy->hw_version);
		अगर (err != 0) अणु
			dev_err(dev, "Incompatible firmware, aborting\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (priv->has_port3)
		dev_info(dev, "Ad-hoc demo mode supported\n");
	अगर (priv->has_ibss)
		dev_info(dev, "IEEE standard IBSS ad-hoc mode supported\n");
	अगर (priv->has_wep)
		dev_info(dev, "WEP supported, %s-bit key\n",
			 priv->has_big_wep ? "104" : "40");
	अगर (priv->has_wpa) अणु
		dev_info(dev, "WPA-PSK supported\n");
		अगर (orinoco_mic_init(priv)) अणु
			dev_err(dev, "Failed to setup MIC crypto algorithm. "
				"Disabling WPA support\n");
			priv->has_wpa = 0;
		पूर्ण
	पूर्ण

	err = orinoco_hw_पढ़ो_card_settings(priv, wiphy->perm_addr);
	अगर (err)
		जाओ out;

	err = orinoco_hw_allocate_fid(priv);
	अगर (err) अणु
		dev_err(dev, "Failed to allocate NIC buffer!\n");
		जाओ out;
	पूर्ण

	/* Set up the शेष configuration */
	priv->iw_mode = NL80211_IFTYPE_STATION;
	/* By शेष use IEEE/IBSS ad-hoc mode अगर we have it */
	priv->prefer_port3 = priv->has_port3 && (!priv->has_ibss);
	set_port_type(priv);
	priv->channel = 0; /* use firmware शेष */

	priv->promiscuous = 0;
	priv->encode_alg = ORINOCO_ALG_NONE;
	priv->tx_key = 0;
	priv->wpa_enabled = 0;
	priv->tkip_cm_active = 0;
	priv->key_mgmt = 0;
	priv->wpa_ie_len = 0;
	priv->wpa_ie = शून्य;

	अगर (orinoco_wiphy_रेजिस्टर(wiphy)) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	/* Make the hardware available, as दीर्घ as it hasn't been
	 * हटाओd अन्यथाwhere (e.g. by PCMCIA hot unplug) */
	orinoco_lock_irq(priv);
	priv->hw_unavailable--;
	orinoco_unlock_irq(priv);

	dev_dbg(dev, "Ready\n");

 out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(orinoco_init);

अटल स्थिर काष्ठा net_device_ops orinoco_netdev_ops = अणु
	.nकरो_खोलो		= orinoco_खोलो,
	.nकरो_stop		= orinoco_stop,
	.nकरो_start_xmit		= orinoco_xmit,
	.nकरो_set_rx_mode	= orinoco_set_multicast_list,
	.nकरो_change_mtu		= orinoco_change_mtu,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout		= orinoco_tx_समयout,
पूर्ण;

/* Allocate निजी data.
 *
 * This driver has a number of काष्ठाures associated with it
 *  netdev - Net device काष्ठाure क्रम each network पूर्णांकerface
 *  wiphy - काष्ठाure associated with wireless phy
 *  wireless_dev (wdev) - काष्ठाure क्रम each wireless पूर्णांकerface
 *  hw - काष्ठाure क्रम hermes chip info
 *  card - card specअगरic काष्ठाure क्रम use by the card driver
 *         (airport, orinoco_cs)
 *  priv - orinoco निजी data
 *  device - generic linux device काष्ठाure
 *
 *  +---------+    +---------+
 *  |  wiphy  |    | netdev  |
 *  | +-------+    | +-------+
 *  | | priv  |    | | wdev  |
 *  | | +-----+    +-+-------+
 *  | | | hw  |
 *  | +-+-----+
 *  | | card  |
 *  +-+-------+
 *
 * priv has a link to netdev and device
 * wdev has a link to wiphy
 */
काष्ठा orinoco_निजी
*alloc_orinocodev(पूर्णांक माप_card,
		  काष्ठा device *device,
		  पूर्णांक (*hard_reset)(काष्ठा orinoco_निजी *),
		  पूर्णांक (*stop_fw)(काष्ठा orinoco_निजी *, पूर्णांक))
अणु
	काष्ठा orinoco_निजी *priv;
	काष्ठा wiphy *wiphy;

	/* allocate wiphy
	 * NOTE: We only support a single भव पूर्णांकerface
	 *       but this may change when monitor mode is added
	 */
	wiphy = wiphy_new(&orinoco_cfg_ops,
			  माप(काष्ठा orinoco_निजी) + माप_card);
	अगर (!wiphy)
		वापस शून्य;

	priv = wiphy_priv(wiphy);
	priv->dev = device;

	अगर (माप_card)
		priv->card = (व्योम *)((अचिन्हित दीर्घ)priv
				      + माप(काष्ठा orinoco_निजी));
	अन्यथा
		priv->card = शून्य;

	orinoco_wiphy_init(wiphy);

#अगर_घोषित WIRELESS_SPY
	priv->wireless_data.spy_data = &priv->spy_data;
#पूर्ण_अगर

	/* Set up शेष callbacks */
	priv->hard_reset = hard_reset;
	priv->stop_fw = stop_fw;

	spin_lock_init(&priv->lock);
	priv->खोलो = 0;
	priv->hw_unavailable = 1; /* orinoco_init() must clear this
				   * beक्रमe anything अन्यथा touches the
				   * hardware */
	INIT_WORK(&priv->reset_work, orinoco_reset);
	INIT_WORK(&priv->join_work, orinoco_join_ap);
	INIT_WORK(&priv->wevent_work, orinoco_send_wevents);

	INIT_LIST_HEAD(&priv->rx_list);
	tasklet_setup(&priv->rx_tasklet, orinoco_rx_isr_tasklet);

	spin_lock_init(&priv->scan_lock);
	INIT_LIST_HEAD(&priv->scan_list);
	INIT_WORK(&priv->process_scan, orinoco_process_scan_results);

	priv->last_linkstatus = 0xffff;

#अगर defined(CONFIG_HERMES_CACHE_FW_ON_INIT) || defined(CONFIG_PM_SLEEP)
	priv->cached_pri_fw = शून्य;
	priv->cached_fw = शून्य;
#पूर्ण_अगर

	/* Register PM notअगरiers */
	orinoco_रेजिस्टर_pm_notअगरier(priv);

	वापस priv;
पूर्ण
EXPORT_SYMBOL(alloc_orinocodev);

/* We can only support a single पूर्णांकerface. We provide a separate
 * function to set it up to distinguish between hardware
 * initialisation and पूर्णांकerface setup.
 *
 * The base_addr and irq parameters are passed on to netdev क्रम use
 * with SIOCGIFMAP.
 */
पूर्णांक orinoco_अगर_add(काष्ठा orinoco_निजी *priv,
		   अचिन्हित दीर्घ base_addr,
		   अचिन्हित पूर्णांक irq,
		   स्थिर काष्ठा net_device_ops *ops)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(priv);
	काष्ठा wireless_dev *wdev;
	काष्ठा net_device *dev;
	पूर्णांक ret;

	dev = alloc_etherdev(माप(काष्ठा wireless_dev));

	अगर (!dev)
		वापस -ENOMEM;

	/* Initialise wireless_dev */
	wdev = netdev_priv(dev);
	wdev->wiphy = wiphy;
	wdev->अगरtype = NL80211_IFTYPE_STATION;

	/* Setup / override net_device fields */
	dev->ieee80211_ptr = wdev;
	dev->watchकरोg_समयo = HZ; /* 1 second समयout */
	dev->wireless_handlers = &orinoco_handler_def;
#अगर_घोषित WIRELESS_SPY
	dev->wireless_data = &priv->wireless_data;
#पूर्ण_अगर
	/* Default to standard ops अगर not set */
	अगर (ops)
		dev->netdev_ops = ops;
	अन्यथा
		dev->netdev_ops = &orinoco_netdev_ops;

	/* we use the शेष eth_mac_addr क्रम setting the MAC addr */

	/* Reserve space in skb क्रम the SNAP header */
	dev->needed_headroom = ENCAPS_OVERHEAD;

	netअगर_carrier_off(dev);

	स_नकल(dev->dev_addr, wiphy->perm_addr, ETH_ALEN);

	dev->base_addr = base_addr;
	dev->irq = irq;

	dev->min_mtu = ORINOCO_MIN_MTU;
	dev->max_mtu = ORINOCO_MAX_MTU;

	SET_NETDEV_DEV(dev, priv->dev);
	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ fail;

	priv->ndev = dev;

	/* Report what we've करोne */
	dev_dbg(priv->dev, "Registered interface %s.\n", dev->name);

	वापस 0;

 fail:
	मुक्त_netdev(dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(orinoco_अगर_add);

व्योम orinoco_अगर_del(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;

	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
पूर्ण
EXPORT_SYMBOL(orinoco_अगर_del);

व्योम मुक्त_orinocodev(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(priv);
	काष्ठा orinoco_rx_data *rx_data, *temp;
	काष्ठा orinoco_scan_data *sd, *sdtemp;

	/* If the tasklet is scheduled when we call tasklet_समाप्त it
	 * will run one final समय. However the tasklet will only
	 * drain priv->rx_list अगर the hw is still available. */
	tasklet_समाप्त(&priv->rx_tasklet);

	/* Explicitly drain priv->rx_list */
	list_क्रम_each_entry_safe(rx_data, temp, &priv->rx_list, list) अणु
		list_del(&rx_data->list);

		dev_kमुक्त_skb(rx_data->skb);
		kमुक्त(rx_data->desc);
		kमुक्त(rx_data);
	पूर्ण

	cancel_work_sync(&priv->process_scan);
	/* Explicitly drain priv->scan_list */
	list_क्रम_each_entry_safe(sd, sdtemp, &priv->scan_list, list) अणु
		list_del(&sd->list);

		अगर (sd->len > 0)
			kमुक्त(sd->buf);
		kमुक्त(sd);
	पूर्ण

	orinoco_unरेजिस्टर_pm_notअगरier(priv);
	orinoco_uncache_fw(priv);

	priv->wpa_ie_len = 0;
	kमुक्त(priv->wpa_ie);
	orinoco_mic_मुक्त(priv);
	wiphy_मुक्त(wiphy);
पूर्ण
EXPORT_SYMBOL(मुक्त_orinocodev);

पूर्णांक orinoco_up(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	priv->hw.ops->lock_irqsave(&priv->lock, &flags);

	err = orinoco_reinit_firmware(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d re-initializing firmware\n",
		       dev->name, err);
		जाओ निकास;
	पूर्ण

	netअगर_device_attach(dev);
	priv->hw_unavailable--;

	अगर (priv->खोलो && !priv->hw_unavailable) अणु
		err = __orinoco_up(priv);
		अगर (err)
			prपूर्णांकk(KERN_ERR "%s: Error %d restarting card\n",
			       dev->name, err);
	पूर्ण

निकास:
	priv->hw.ops->unlock_irqrestore(&priv->lock, &flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(orinoco_up);

व्योम orinoco_करोwn(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	priv->hw.ops->lock_irqsave(&priv->lock, &flags);
	err = __orinoco_करोwn(priv);
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: Error %d downing interface\n",
		       dev->name, err);

	netअगर_device_detach(dev);
	priv->hw_unavailable++;
	priv->hw.ops->unlock_irqrestore(&priv->lock, &flags);
पूर्ण
EXPORT_SYMBOL(orinoco_करोwn);

/********************************************************************/
/* Module initialization                                            */
/********************************************************************/

/* Can't be declared "const" or the whole __initdata section will
 * become स्थिर */
अटल अक्षर version[] __initdata = DRIVER_NAME " " DRIVER_VERSION
	" (David Gibson <hermes@gibson.dropbear.id.au>, "
	"Pavel Roskin <proski@gnu.org>, et al)";

अटल पूर्णांक __init init_orinoco(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "%s\n", version);
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_orinoco(व्योम)
अणु
पूर्ण

module_init(init_orinoco);
module_निकास(निकास_orinoco);
