<शैली गुरु>
/*
 * llc_s_ac.c - actions perक्रमmed during sap state transition.
 *
 * Description :
 *   Functions in this module are implementation of sap component actions.
 *   Details of actions can be found in IEEE-802.2 standard करोcument.
 *   All functions have one sap and one event as input argument. All of
 *   them वापस 0 On success and 1 otherwise.
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 *		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */

#समावेश <linux/netdevice.h>
#समावेश <net/llc.h>
#समावेश <net/llc_pdu.h>
#समावेश <net/llc_s_ac.h>
#समावेश <net/llc_s_ev.h>
#समावेश <net/llc_sap.h>


/**
 *	llc_sap_action_unitdata_ind - क्रमward UI PDU to network layer
 *	@sap: SAP
 *	@skb: the event to क्रमward
 *
 *	Received a UI PDU from MAC layer; क्रमward to network layer as a
 *	UNITDATA INDICATION; verअगरy our event is the kind we expect
 */
पूर्णांक llc_sap_action_unitdata_ind(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	llc_sap_rtn_pdu(sap, skb);
	वापस 0;
पूर्ण

/**
 *	llc_sap_action_send_ui - sends UI PDU resp to UNITDATA REQ to MAC layer
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Sends a UI PDU to the MAC layer in response to a UNITDATA REQUEST
 *	primitive from the network layer. Verअगरies event is a primitive type of
 *	event. Verअगरy the primitive is a UNITDATA REQUEST.
 */
पूर्णांक llc_sap_action_send_ui(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);
	पूर्णांक rc;

	llc_pdu_header_init(skb, LLC_PDU_TYPE_U, ev->saddr.lsap,
			    ev->daddr.lsap, LLC_PDU_CMD);
	llc_pdu_init_as_ui_cmd(skb);
	rc = llc_mac_hdr_init(skb, ev->saddr.mac, ev->daddr.mac);
	अगर (likely(!rc)) अणु
		skb_get(skb);
		rc = dev_queue_xmit(skb);
	पूर्ण
	वापस rc;
पूर्ण

/**
 *	llc_sap_action_send_xid_c - send XID PDU as response to XID REQ
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send a XID command PDU to MAC layer in response to a XID REQUEST
 *	primitive from the network layer. Verअगरy event is a primitive type
 *	event. Verअगरy the primitive is a XID REQUEST.
 */
पूर्णांक llc_sap_action_send_xid_c(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);
	पूर्णांक rc;

	llc_pdu_header_init(skb, LLC_PDU_TYPE_U, ev->saddr.lsap,
			    ev->daddr.lsap, LLC_PDU_CMD);
	llc_pdu_init_as_xid_cmd(skb, LLC_XID_शून्य_CLASS_2, 0);
	rc = llc_mac_hdr_init(skb, ev->saddr.mac, ev->daddr.mac);
	अगर (likely(!rc)) अणु
		skb_get(skb);
		rc = dev_queue_xmit(skb);
	पूर्ण
	वापस rc;
पूर्ण

/**
 *	llc_sap_action_send_xid_r - send XID PDU resp to MAC क्रम received XID
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send XID response PDU to MAC in response to an earlier received XID
 *	command PDU. Verअगरy event is a PDU type event
 */
पूर्णांक llc_sap_action_send_xid_r(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	u8 mac_da[ETH_ALEN], mac_sa[ETH_ALEN], dsap;
	पूर्णांक rc = 1;
	काष्ठा sk_buff *nskb;

	llc_pdu_decode_sa(skb, mac_da);
	llc_pdu_decode_da(skb, mac_sa);
	llc_pdu_decode_ssap(skb, &dsap);
	nskb = llc_alloc_frame(शून्य, skb->dev, LLC_PDU_TYPE_U,
			       माप(काष्ठा llc_xid_info));
	अगर (!nskb)
		जाओ out;
	llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap, dsap,
			    LLC_PDU_RSP);
	llc_pdu_init_as_xid_rsp(nskb, LLC_XID_शून्य_CLASS_2, 0);
	rc = llc_mac_hdr_init(nskb, mac_sa, mac_da);
	अगर (likely(!rc))
		rc = dev_queue_xmit(nskb);
out:
	वापस rc;
पूर्ण

/**
 *	llc_sap_action_send_test_c - send TEST PDU to MAC in resp to TEST REQ
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send a TEST command PDU to the MAC layer in response to a TEST REQUEST
 *	primitive from the network layer. Verअगरy event is a primitive type
 *	event; verअगरy the primitive is a TEST REQUEST.
 */
पूर्णांक llc_sap_action_send_test_c(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);
	पूर्णांक rc;

	llc_pdu_header_init(skb, LLC_PDU_TYPE_U, ev->saddr.lsap,
			    ev->daddr.lsap, LLC_PDU_CMD);
	llc_pdu_init_as_test_cmd(skb);
	rc = llc_mac_hdr_init(skb, ev->saddr.mac, ev->daddr.mac);
	अगर (likely(!rc)) अणु
		skb_get(skb);
		rc = dev_queue_xmit(skb);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक llc_sap_action_send_test_r(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	u8 mac_da[ETH_ALEN], mac_sa[ETH_ALEN], dsap;
	काष्ठा sk_buff *nskb;
	पूर्णांक rc = 1;
	u32 data_size;

	llc_pdu_decode_sa(skb, mac_da);
	llc_pdu_decode_da(skb, mac_sa);
	llc_pdu_decode_ssap(skb, &dsap);

	/* The test request command is type U (llc_len = 3) */
	data_size = ntohs(eth_hdr(skb)->h_proto) - 3;
	nskb = llc_alloc_frame(शून्य, skb->dev, LLC_PDU_TYPE_U, data_size);
	अगर (!nskb)
		जाओ out;
	llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap, dsap,
			    LLC_PDU_RSP);
	llc_pdu_init_as_test_rsp(nskb, skb);
	rc = llc_mac_hdr_init(nskb, mac_sa, mac_da);
	अगर (likely(!rc))
		rc = dev_queue_xmit(nskb);
out:
	वापस rc;
पूर्ण

/**
 *	llc_sap_action_report_status - report data link status to layer mgmt
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Report data link status to layer management. Verअगरy our event is the
 *	kind we expect.
 */
पूर्णांक llc_sap_action_report_status(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

/**
 *	llc_sap_action_xid_ind - send XID PDU resp to net layer via XID IND
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send a XID response PDU to the network layer via a XID INDICATION
 *	primitive.
 */
पूर्णांक llc_sap_action_xid_ind(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	llc_sap_rtn_pdu(sap, skb);
	वापस 0;
पूर्ण

/**
 *	llc_sap_action_test_ind - send TEST PDU to net layer via TEST IND
 *	@sap: SAP
 *	@skb: the event to send
 *
 *	Send a TEST response PDU to the network layer via a TEST INDICATION
 *	primitive. Verअगरy our event is a PDU type event.
 */
पूर्णांक llc_sap_action_test_ind(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	llc_sap_rtn_pdu(sap, skb);
	वापस 0;
पूर्ण
