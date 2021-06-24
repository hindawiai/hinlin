<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/* src/p80211/p80211conv.c
 *
 * Ether/802.11 conversions and packet buffer routines
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
 * This file defines the functions that perक्रमm Ethernet to/from
 * 802.11 frame conversions.
 *
 * --------------------------------------------------------------------
 *
 *================================================================
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/byteorder/generic.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "p80211types.h"
#समावेश "p80211hdr.h"
#समावेश "p80211conv.h"
#समावेश "p80211mgmt.h"
#समावेश "p80211msg.h"
#समावेश "p80211netdev.h"
#समावेश "p80211ioctl.h"
#समावेश "p80211req.h"

अटल स्थिर u8 oui_rfc1042[] = अणु 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 oui_8021h[] = अणु 0x00, 0x00, 0xf8 पूर्ण;

/*----------------------------------------------------------------
 * p80211pb_ether_to_80211
 *
 * Uses the contents of the ether frame and the etherconv setting
 * to build the elements of the 802.11 frame.
 *
 * We करोn't actually set
 * up the frame header here.  That's the MAC's job.  We're only handling
 * conversion of DIXII or 802.3+LLC frames to something that works
 * with 802.11.
 *
 * Note -- 802.11 header is NOT part of the skb.  Likewise, the 802.11
 *         FCS is also not present and will need to be added अन्यथाwhere.
 *
 * Arguments:
 *	ethconv		Conversion type to perक्रमm
 *	skb		skbuff containing the ether frame
 *       p80211_hdr      802.11 header
 *
 * Returns:
 *	0 on success, non-zero otherwise
 *
 * Call context:
 *	May be called in पूर्णांकerrupt or non-पूर्णांकerrupt context
 *----------------------------------------------------------------
 */
पूर्णांक skb_ether_to_p80211(काष्ठा wlandevice *wlandev, u32 ethconv,
			काष्ठा sk_buff *skb, जोड़ p80211_hdr *p80211_hdr,
			काष्ठा p80211_metawep *p80211_wep)
अणु
	__le16 fc;
	u16 proto;
	काष्ठा wlan_ethhdr e_hdr;
	काष्ठा wlan_llc *e_llc;
	काष्ठा wlan_snap *e_snap;
	पूर्णांक foo;

	स_नकल(&e_hdr, skb->data, माप(e_hdr));

	अगर (skb->len <= 0) अणु
		pr_debug("zero-length skb!\n");
		वापस 1;
	पूर्ण

	अगर (ethconv == WLAN_ETHCONV_ENCAP) अणु	/* simplest हाल */
		pr_debug("ENCAP len: %d\n", skb->len);
		/* here, we करोn't care what kind of ether frm. Just stick it */
		/*  in the 80211 payload */
		/* which is to say, leave the skb alone. */
	पूर्ण अन्यथा अणु
		/* step 1: classअगरy ether frame, DIX or 802.3? */
		proto = ntohs(e_hdr.type);
		अगर (proto <= ETH_DATA_LEN) अणु
			pr_debug("802.3 len: %d\n", skb->len);
			/* codes <= 1500 reserved क्रम 802.3 lengths */
			/* it's 802.3, pass ether payload unchanged,  */

			/* trim off ethernet header */
			skb_pull(skb, ETH_HLEN);

			/*   leave off any PAD octets.  */
			skb_trim(skb, proto);
		पूर्ण अन्यथा अणु
			pr_debug("DIXII len: %d\n", skb->len);
			/* it's DIXII, समय क्रम some conversion */

			/* trim off ethernet header */
			skb_pull(skb, ETH_HLEN);

			/* tack on SNAP */
			e_snap = skb_push(skb, माप(काष्ठा wlan_snap));
			e_snap->type = htons(proto);
			अगर (ethconv == WLAN_ETHCONV_8021h &&
			    p80211_stt_findproto(proto)) अणु
				स_नकल(e_snap->oui, oui_8021h,
				       WLAN_IEEE_OUI_LEN);
			पूर्ण अन्यथा अणु
				स_नकल(e_snap->oui, oui_rfc1042,
				       WLAN_IEEE_OUI_LEN);
			पूर्ण

			/* tack on llc */
			e_llc = skb_push(skb, माप(काष्ठा wlan_llc));
			e_llc->dsap = 0xAA;	/* SNAP, see IEEE 802 */
			e_llc->ssap = 0xAA;
			e_llc->ctl = 0x03;
		पूर्ण
	पूर्ण

	/* Set up the 802.11 header */
	/* It's a data frame */
	fc = cpu_to_le16(WLAN_SET_FC_FTYPE(WLAN_FTYPE_DATA) |
			 WLAN_SET_FC_FSTYPE(WLAN_FSTYPE_DATAONLY));

	चयन (wlandev->macmode) अणु
	हाल WLAN_MACMODE_IBSS_STA:
		स_नकल(p80211_hdr->a3.a1, &e_hdr.daddr, ETH_ALEN);
		स_नकल(p80211_hdr->a3.a2, wlandev->netdev->dev_addr, ETH_ALEN);
		स_नकल(p80211_hdr->a3.a3, wlandev->bssid, ETH_ALEN);
		अवरोध;
	हाल WLAN_MACMODE_ESS_STA:
		fc |= cpu_to_le16(WLAN_SET_FC_TODS(1));
		स_नकल(p80211_hdr->a3.a1, wlandev->bssid, ETH_ALEN);
		स_नकल(p80211_hdr->a3.a2, wlandev->netdev->dev_addr, ETH_ALEN);
		स_नकल(p80211_hdr->a3.a3, &e_hdr.daddr, ETH_ALEN);
		अवरोध;
	हाल WLAN_MACMODE_ESS_AP:
		fc |= cpu_to_le16(WLAN_SET_FC_FROMDS(1));
		स_नकल(p80211_hdr->a3.a1, &e_hdr.daddr, ETH_ALEN);
		स_नकल(p80211_hdr->a3.a2, wlandev->bssid, ETH_ALEN);
		स_नकल(p80211_hdr->a3.a3, &e_hdr.saddr, ETH_ALEN);
		अवरोध;
	शेष:
		netdev_err(wlandev->netdev,
			   "Error: Converting eth to wlan in unknown mode.\n");
		वापस 1;
	पूर्ण

	p80211_wep->data = शून्य;

	अगर ((wlandev->hostwep & HOSTWEP_PRIVACYINVOKED) &&
	    (wlandev->hostwep & HOSTWEP_ENCRYPT)) अणु
		/* XXXX need to pick keynum other than शेष? */

		p80211_wep->data = kदो_स्मृति(skb->len, GFP_ATOMIC);
		अगर (!p80211_wep->data)
			वापस -ENOMEM;
		foo = wep_encrypt(wlandev, skb->data, p80211_wep->data,
				  skb->len,
				  wlandev->hostwep & HOSTWEP_DEFAULTKEY_MASK,
				  p80211_wep->iv, p80211_wep->icv);
		अगर (foo) अणु
			netdev_warn(wlandev->netdev,
				    "Host en-WEP failed, dropping frame (%d).\n",
				    foo);
			kमुक्त(p80211_wep->data);
			वापस 2;
		पूर्ण
		fc |= cpu_to_le16(WLAN_SET_FC_ISWEP(1));
	पूर्ण

	/*      skb->nh.raw = skb->data; */

	p80211_hdr->a3.fc = fc;
	p80211_hdr->a3.dur = 0;
	p80211_hdr->a3.seq = 0;

	वापस 0;
पूर्ण

/* jkriegl: from orinoco, modअगरied */
अटल व्योम orinoco_spy_gather(काष्ठा wlandevice *wlandev, अक्षर *mac,
			       काष्ठा p80211_rxmeta *rxmeta)
अणु
	पूर्णांक i;

	/* Gather wireless spy statistics: क्रम each packet, compare the
	 * source address with out list, and अगर match, get the stats...
	 */

	क्रम (i = 0; i < wlandev->spy_number; i++) अणु
		अगर (!स_भेद(wlandev->spy_address[i], mac, ETH_ALEN)) अणु
			wlandev->spy_stat[i].level = rxmeta->संकेत;
			wlandev->spy_stat[i].noise = rxmeta->noise;
			wlandev->spy_stat[i].qual =
			    (rxmeta->संकेत >
			     rxmeta->noise) ? (rxmeta->संकेत -
					       rxmeta->noise) : 0;
			wlandev->spy_stat[i].updated = 0x7;
		पूर्ण
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * p80211pb_80211_to_ether
 *
 * Uses the contents of a received 802.11 frame and the etherconv
 * setting to build an ether frame.
 *
 * This function extracts the src and dest address from the 802.11
 * frame to use in the स्थिरruction of the eth frame.
 *
 * Arguments:
 *	ethconv		Conversion type to perक्रमm
 *	skb		Packet buffer containing the 802.11 frame
 *
 * Returns:
 *	0 on success, non-zero otherwise
 *
 * Call context:
 *	May be called in पूर्णांकerrupt or non-पूर्णांकerrupt context
 *----------------------------------------------------------------
 */
पूर्णांक skb_p80211_to_ether(काष्ठा wlandevice *wlandev, u32 ethconv,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *netdev = wlandev->netdev;
	u16 fc;
	अचिन्हित पूर्णांक payload_length;
	अचिन्हित पूर्णांक payload_offset;
	u8 daddr[ETH_ALEN];
	u8 saddr[ETH_ALEN];
	जोड़ p80211_hdr *w_hdr;
	काष्ठा wlan_ethhdr *e_hdr;
	काष्ठा wlan_llc *e_llc;
	काष्ठा wlan_snap *e_snap;

	पूर्णांक foo;

	payload_length = skb->len - WLAN_HDR_A3_LEN - WLAN_CRC_LEN;
	payload_offset = WLAN_HDR_A3_LEN;

	w_hdr = (जोड़ p80211_hdr *)skb->data;

	/* setup some vars क्रम convenience */
	fc = le16_to_cpu(w_hdr->a3.fc);
	अगर ((WLAN_GET_FC_TODS(fc) == 0) && (WLAN_GET_FC_FROMDS(fc) == 0)) अणु
		ether_addr_copy(daddr, w_hdr->a3.a1);
		ether_addr_copy(saddr, w_hdr->a3.a2);
	पूर्ण अन्यथा अगर ((WLAN_GET_FC_TODS(fc) == 0) &&
		   (WLAN_GET_FC_FROMDS(fc) == 1)) अणु
		ether_addr_copy(daddr, w_hdr->a3.a1);
		ether_addr_copy(saddr, w_hdr->a3.a3);
	पूर्ण अन्यथा अगर ((WLAN_GET_FC_TODS(fc) == 1) &&
		   (WLAN_GET_FC_FROMDS(fc) == 0)) अणु
		ether_addr_copy(daddr, w_hdr->a3.a3);
		ether_addr_copy(saddr, w_hdr->a3.a2);
	पूर्ण अन्यथा अणु
		payload_offset = WLAN_HDR_A4_LEN;
		अगर (payload_length < WLAN_HDR_A4_LEN - WLAN_HDR_A3_LEN) अणु
			netdev_err(netdev, "A4 frame too short!\n");
			वापस 1;
		पूर्ण
		payload_length -= (WLAN_HDR_A4_LEN - WLAN_HDR_A3_LEN);
		ether_addr_copy(daddr, w_hdr->a4.a3);
		ether_addr_copy(saddr, w_hdr->a4.a4);
	पूर्ण

	/* perक्रमm de-wep अगर necessary.. */
	अगर ((wlandev->hostwep & HOSTWEP_PRIVACYINVOKED) &&
	    WLAN_GET_FC_ISWEP(fc) &&
	    (wlandev->hostwep & HOSTWEP_DECRYPT)) अणु
		अगर (payload_length <= 8) अणु
			netdev_err(netdev,
				   "WEP frame too short (%u).\n", skb->len);
			वापस 1;
		पूर्ण
		foo = wep_decrypt(wlandev, skb->data + payload_offset + 4,
				  payload_length - 8, -1,
				  skb->data + payload_offset,
				  skb->data + payload_offset +
				  payload_length - 4);
		अगर (foo) अणु
			/* de-wep failed, drop skb. */
			pr_debug("Host de-WEP failed, dropping frame (%d).\n",
				 foo);
			wlandev->rx.decrypt_err++;
			वापस 2;
		पूर्ण

		/* subtract the IV+ICV length off the payload */
		payload_length -= 8;
		/* chop off the IV */
		skb_pull(skb, 4);
		/* chop off the ICV. */
		skb_trim(skb, skb->len - 4);

		wlandev->rx.decrypt++;
	पूर्ण

	e_hdr = (काष्ठा wlan_ethhdr *)(skb->data + payload_offset);

	e_llc = (काष्ठा wlan_llc *)(skb->data + payload_offset);
	e_snap =
	    (काष्ठा wlan_snap *)(skb->data + payload_offset +
		माप(काष्ठा wlan_llc));

	/* Test क्रम the various encodings */
	अगर ((payload_length >= माप(काष्ठा wlan_ethhdr)) &&
	    (e_llc->dsap != 0xaa || e_llc->ssap != 0xaa) &&
	    ((!ether_addr_equal_unaligned(daddr, e_hdr->daddr)) ||
	     (!ether_addr_equal_unaligned(saddr, e_hdr->saddr)))) अणु
		pr_debug("802.3 ENCAP len: %d\n", payload_length);
		/* 802.3 Encapsulated */
		/* Test क्रम an overlength frame */
		अगर (payload_length > (netdev->mtu + ETH_HLEN)) अणु
			/* A bogus length ethfrm has been encap'd. */
			/* Is someone trying an oflow attack? */
			netdev_err(netdev, "ENCAP frame too large (%d > %d)\n",
				   payload_length, netdev->mtu + ETH_HLEN);
			वापस 1;
		पूर्ण

		/* Chop off the 802.11 header.  it's alपढ़ोy sane. */
		skb_pull(skb, payload_offset);
		/* chop off the 802.11 CRC */
		skb_trim(skb, skb->len - WLAN_CRC_LEN);

	पूर्ण अन्यथा अगर ((payload_length >= माप(काष्ठा wlan_llc) +
		माप(काष्ठा wlan_snap)) &&
		(e_llc->dsap == 0xaa) &&
		(e_llc->ssap == 0xaa) &&
		(e_llc->ctl == 0x03) &&
		   (((स_भेद(e_snap->oui, oui_rfc1042,
		   WLAN_IEEE_OUI_LEN) == 0) &&
		   (ethconv == WLAN_ETHCONV_8021h) &&
		   (p80211_stt_findproto(be16_to_cpu(e_snap->type)))) ||
		   (स_भेद(e_snap->oui, oui_rfc1042, WLAN_IEEE_OUI_LEN) !=
			0))) अणु
		pr_debug("SNAP+RFC1042 len: %d\n", payload_length);
		/* it's a SNAP + RFC1042 frame && protocol is in STT */
		/* build 802.3 + RFC1042 */

		/* Test क्रम an overlength frame */
		अगर (payload_length > netdev->mtu) अणु
			/* A bogus length ethfrm has been sent. */
			/* Is someone trying an oflow attack? */
			netdev_err(netdev, "SNAP frame too large (%d > %d)\n",
				   payload_length, netdev->mtu);
			वापस 1;
		पूर्ण

		/* chop 802.11 header from skb. */
		skb_pull(skb, payload_offset);

		/* create 802.3 header at beginning of skb. */
		e_hdr = skb_push(skb, ETH_HLEN);
		ether_addr_copy(e_hdr->daddr, daddr);
		ether_addr_copy(e_hdr->saddr, saddr);
		e_hdr->type = htons(payload_length);

		/* chop off the 802.11 CRC */
		skb_trim(skb, skb->len - WLAN_CRC_LEN);

	पूर्ण अन्यथा अगर ((payload_length >= माप(काष्ठा wlan_llc) +
		माप(काष्ठा wlan_snap)) &&
		(e_llc->dsap == 0xaa) &&
		(e_llc->ssap == 0xaa) &&
		(e_llc->ctl == 0x03)) अणु
		pr_debug("802.1h/RFC1042 len: %d\n", payload_length);
		/* it's an 802.1h frame || (an RFC1042 && protocol not in STT)
		 * build a DIXII + RFC894
		 */

		/* Test क्रम an overlength frame */
		अगर ((payload_length - माप(काष्ठा wlan_llc) -
			माप(काष्ठा wlan_snap))
			> netdev->mtu) अणु
			/* A bogus length ethfrm has been sent. */
			/* Is someone trying an oflow attack? */
			netdev_err(netdev, "DIXII frame too large (%ld > %d)\n",
				   (दीर्घ)(payload_length -
				   माप(काष्ठा wlan_llc) -
				   माप(काष्ठा wlan_snap)), netdev->mtu);
			वापस 1;
		पूर्ण

		/* chop 802.11 header from skb. */
		skb_pull(skb, payload_offset);

		/* chop llc header from skb. */
		skb_pull(skb, माप(काष्ठा wlan_llc));

		/* chop snap header from skb. */
		skb_pull(skb, माप(काष्ठा wlan_snap));

		/* create 802.3 header at beginning of skb. */
		e_hdr = skb_push(skb, ETH_HLEN);
		e_hdr->type = e_snap->type;
		ether_addr_copy(e_hdr->daddr, daddr);
		ether_addr_copy(e_hdr->saddr, saddr);

		/* chop off the 802.11 CRC */
		skb_trim(skb, skb->len - WLAN_CRC_LEN);
	पूर्ण अन्यथा अणु
		pr_debug("NON-ENCAP len: %d\n", payload_length);
		/* any NON-ENCAP */
		/* it's a generic 80211+LLC or IPX 'Raw 802.3' */
		/*  build an 802.3 frame */
		/* allocate space and setup hostbuf */

		/* Test क्रम an overlength frame */
		अगर (payload_length > netdev->mtu) अणु
			/* A bogus length ethfrm has been sent. */
			/* Is someone trying an oflow attack? */
			netdev_err(netdev, "OTHER frame too large (%d > %d)\n",
				   payload_length, netdev->mtu);
			वापस 1;
		पूर्ण

		/* Chop off the 802.11 header. */
		skb_pull(skb, payload_offset);

		/* create 802.3 header at beginning of skb. */
		e_hdr = skb_push(skb, ETH_HLEN);
		ether_addr_copy(e_hdr->daddr, daddr);
		ether_addr_copy(e_hdr->saddr, saddr);
		e_hdr->type = htons(payload_length);

		/* chop off the 802.11 CRC */
		skb_trim(skb, skb->len - WLAN_CRC_LEN);
	पूर्ण

	/*
	 * Note that eth_type_trans() expects an skb w/ skb->data poपूर्णांकing
	 * at the MAC header, it then sets the following skb members:
	 * skb->mac_header,
	 * skb->data, and
	 * skb->pkt_type.
	 * It then _वापसs_ the value that _we're_ supposed to stuff in
	 * skb->protocol.  This is nuts.
	 */
	skb->protocol = eth_type_trans(skb, netdev);

	/* jkriegl: process संकेत and noise as set in hfa384x_पूर्णांक_rx() */
	/* jkriegl: only process संकेत/noise अगर requested by iwspy */
	अगर (wlandev->spy_number)
		orinoco_spy_gather(wlandev, eth_hdr(skb)->h_source,
				   p80211skb_rxmeta(skb));

	/* Free the metadata */
	p80211skb_rxmeta_detach(skb);

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * p80211_stt_findproto
 *
 * Searches the 802.1h Selective Translation Table क्रम a given
 * protocol.
 *
 * Arguments:
 *	proto	protocol number (in host order) to search क्रम.
 *
 * Returns:
 *	1 - अगर the table is empty or a match is found.
 *	0 - अगर the table is non-empty and a match is not found.
 *
 * Call context:
 *	May be called in पूर्णांकerrupt or non-पूर्णांकerrupt context
 *----------------------------------------------------------------
 */
पूर्णांक p80211_stt_findproto(u16 proto)
अणु
	/* Always वापस found क्रम now.  This is the behavior used by the */
	/* Zoom Win95 driver when 802.1h mode is selected */
	/* TODO: If necessary, add an actual search we'll probably
	 * need this to match the CMAC's way of करोing things.
	 * Need to करो some testing to confirm.
	 */

	अगर (proto == ETH_P_AARP)	/* APPLETALK */
		वापस 1;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * p80211skb_rxmeta_detach
 *
 * Disconnects the frmmeta and rxmeta from an skb.
 *
 * Arguments:
 *	wlandev		The wlandev this skb beदीर्घs to.
 *	skb		The skb we're attaching to.
 *
 * Returns:
 *	0 on success, non-zero otherwise
 *
 * Call context:
 *	May be called in पूर्णांकerrupt or non-पूर्णांकerrupt context
 *----------------------------------------------------------------
 */
व्योम p80211skb_rxmeta_detach(काष्ठा sk_buff *skb)
अणु
	काष्ठा p80211_rxmeta *rxmeta;
	काष्ठा p80211_frmmeta *frmmeta;

	/* Sanity checks */
	अगर (!skb) अणु	/* bad skb */
		pr_debug("Called w/ null skb.\n");
		वापस;
	पूर्ण
	frmmeta = p80211skb_frmmeta(skb);
	अगर (!frmmeta) अणु	/* no magic */
		pr_debug("Called w/ bad frmmeta magic.\n");
		वापस;
	पूर्ण
	rxmeta = frmmeta->rx;
	अगर (!rxmeta) अणु	/* bad meta ptr */
		pr_debug("Called w/ bad rxmeta ptr.\n");
		वापस;
	पूर्ण

	/* Free rxmeta */
	kमुक्त(rxmeta);

	/* Clear skb->cb */
	स_रखो(skb->cb, 0, माप(skb->cb));
पूर्ण

/*----------------------------------------------------------------
 * p80211skb_rxmeta_attach
 *
 * Allocates a p80211rxmeta काष्ठाure, initializes it, and attaches
 * it to an skb.
 *
 * Arguments:
 *	wlandev		The wlandev this skb beदीर्घs to.
 *	skb		The skb we're attaching to.
 *
 * Returns:
 *	0 on success, non-zero otherwise
 *
 * Call context:
 *	May be called in पूर्णांकerrupt or non-पूर्णांकerrupt context
 *----------------------------------------------------------------
 */
पूर्णांक p80211skb_rxmeta_attach(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक result = 0;
	काष्ठा p80211_rxmeta *rxmeta;
	काष्ठा p80211_frmmeta *frmmeta;

	/* If these alपढ़ोy have metadata, we error out! */
	अगर (p80211skb_rxmeta(skb)) अणु
		netdev_err(wlandev->netdev,
			   "%s: RXmeta already attached!\n", wlandev->name);
		result = 0;
		जाओ निकास;
	पूर्ण

	/* Allocate the rxmeta */
	rxmeta = kzalloc(माप(*rxmeta), GFP_ATOMIC);

	अगर (!rxmeta) अणु
		result = 1;
		जाओ निकास;
	पूर्ण

	/* Initialize the rxmeta */
	rxmeta->wlandev = wlandev;
	rxmeta->hostसमय = jअगरfies;

	/* Overlay a frmmeta_t onto skb->cb */
	स_रखो(skb->cb, 0, माप(काष्ठा p80211_frmmeta));
	frmmeta = (काष्ठा p80211_frmmeta *)(skb->cb);
	frmmeta->magic = P80211_FRMMETA_MAGIC;
	frmmeta->rx = rxmeta;
निकास:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * p80211skb_मुक्त
 *
 * Frees an entire p80211skb by checking and मुक्तing the meta काष्ठा
 * and then मुक्तing the skb.
 *
 * Arguments:
 *	wlandev		The wlandev this skb beदीर्घs to.
 *	skb		The skb we're attaching to.
 *
 * Returns:
 *	0 on success, non-zero otherwise
 *
 * Call context:
 *	May be called in पूर्णांकerrupt or non-पूर्णांकerrupt context
 *----------------------------------------------------------------
 */
व्योम p80211skb_मुक्त(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb)
अणु
	काष्ठा p80211_frmmeta *meta;

	meta = p80211skb_frmmeta(skb);
	अगर (meta && meta->rx)
		p80211skb_rxmeta_detach(skb);
	अन्यथा
		netdev_err(wlandev->netdev,
			   "Freeing an skb (%p) w/ no frmmeta.\n", skb);
	dev_kमुक्त_skb(skb);
पूर्ण
