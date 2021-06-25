<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * llc_output.c - LLC minimal output path
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 * 		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>
#समावेश <net/llc.h>
#समावेश <net/llc_pdu.h>

/**
 *	llc_mac_hdr_init - fills MAC header fields
 *	@skb: Address of the frame to initialize its MAC header
 *	@sa: The MAC source address
 *	@da: The MAC destination address
 *
 *	Fills MAC header fields, depending on MAC type. Returns 0, If MAC type
 *	is a valid type and initialization completes correctly 1, otherwise.
 */
पूर्णांक llc_mac_hdr_init(काष्ठा sk_buff *skb,
		     स्थिर अचिन्हित अक्षर *sa, स्थिर अचिन्हित अक्षर *da)
अणु
	पूर्णांक rc = -EINVAL;

	चयन (skb->dev->type) अणु
	हाल ARPHRD_ETHER:
	हाल ARPHRD_LOOPBACK:
		rc = dev_hard_header(skb, skb->dev, ETH_P_802_2, da, sa,
				     skb->len);
		अगर (rc > 0)
			rc = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

/**
 *	llc_build_and_send_ui_pkt - unitdata request पूर्णांकerface क्रम upper layers
 *	@sap: sap to use
 *	@skb: packet to send
 *	@dmac: destination mac address
 *	@dsap: destination sap
 *
 *	Upper layers calls this function when upper layer wants to send data
 *	using connection-less mode communication (UI pdu).
 *
 *	Accept data frame from network layer to be sent using connection-
 *	less mode communication; समयout/retries handled by network layer;
 *	package primitive as an event and send to SAP event handler
 */
पूर्णांक llc_build_and_send_ui_pkt(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb,
			      अचिन्हित अक्षर *dmac, अचिन्हित अक्षर dsap)
अणु
	पूर्णांक rc;
	llc_pdu_header_init(skb, LLC_PDU_TYPE_U, sap->laddr.lsap,
			    dsap, LLC_PDU_CMD);
	llc_pdu_init_as_ui_cmd(skb);
	rc = llc_mac_hdr_init(skb, skb->dev->dev_addr, dmac);
	अगर (likely(!rc))
		rc = dev_queue_xmit(skb);
	अन्यथा
		kमुक्त_skb(skb);
	वापस rc;
पूर्ण

EXPORT_SYMBOL(llc_mac_hdr_init);
EXPORT_SYMBOL(llc_build_and_send_ui_pkt);
