<शैली गुरु>
/*
 * llc_station.c - station component of LLC
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 * 		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <net/llc.h>
#समावेश <net/llc_sap.h>
#समावेश <net/llc_conn.h>
#समावेश <net/llc_c_ac.h>
#समावेश <net/llc_s_ac.h>
#समावेश <net/llc_c_ev.h>
#समावेश <net/llc_c_st.h>
#समावेश <net/llc_s_ev.h>
#समावेश <net/llc_s_st.h>
#समावेश <net/llc_pdu.h>

अटल पूर्णांक llc_stat_ev_rx_null_dsap_xid_c(काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) &&			/* command PDU */
	       LLC_PDU_TYPE_IS_U(pdu) &&		/* U type PDU */
	       LLC_U_PDU_CMD(pdu) == LLC_1_PDU_CMD_XID &&
	       !pdu->dsap;				/* शून्य DSAP value */
पूर्ण

अटल पूर्णांक llc_stat_ev_rx_null_dsap_test_c(काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस LLC_PDU_IS_CMD(pdu) &&			/* command PDU */
	       LLC_PDU_TYPE_IS_U(pdu) &&		/* U type PDU */
	       LLC_U_PDU_CMD(pdu) == LLC_1_PDU_CMD_TEST &&
	       !pdu->dsap;				/* शून्य DSAP */
पूर्ण

अटल पूर्णांक llc_station_ac_send_xid_r(काष्ठा sk_buff *skb)
अणु
	u8 mac_da[ETH_ALEN], dsap;
	पूर्णांक rc = 1;
	काष्ठा sk_buff *nskb = llc_alloc_frame(शून्य, skb->dev, LLC_PDU_TYPE_U,
					       माप(काष्ठा llc_xid_info));

	अगर (!nskb)
		जाओ out;
	llc_pdu_decode_sa(skb, mac_da);
	llc_pdu_decode_ssap(skb, &dsap);
	llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, 0, dsap, LLC_PDU_RSP);
	llc_pdu_init_as_xid_rsp(nskb, LLC_XID_शून्य_CLASS_2, 127);
	rc = llc_mac_hdr_init(nskb, skb->dev->dev_addr, mac_da);
	अगर (unlikely(rc))
		जाओ मुक्त;
	dev_queue_xmit(nskb);
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

अटल पूर्णांक llc_station_ac_send_test_r(काष्ठा sk_buff *skb)
अणु
	u8 mac_da[ETH_ALEN], dsap;
	पूर्णांक rc = 1;
	u32 data_size;
	काष्ठा sk_buff *nskb;

	/* The test request command is type U (llc_len = 3) */
	data_size = ntohs(eth_hdr(skb)->h_proto) - 3;
	nskb = llc_alloc_frame(शून्य, skb->dev, LLC_PDU_TYPE_U, data_size);

	अगर (!nskb)
		जाओ out;
	llc_pdu_decode_sa(skb, mac_da);
	llc_pdu_decode_ssap(skb, &dsap);
	llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, 0, dsap, LLC_PDU_RSP);
	llc_pdu_init_as_test_rsp(nskb, skb);
	rc = llc_mac_hdr_init(nskb, skb->dev->dev_addr, mac_da);
	अगर (unlikely(rc))
		जाओ मुक्त;
	dev_queue_xmit(nskb);
out:
	वापस rc;
मुक्त:
	kमुक्त_skb(nskb);
	जाओ out;
पूर्ण

/**
 *	llc_station_rcv - send received pdu to the station state machine
 *	@skb: received frame.
 *
 *	Sends data unit to station state machine.
 */
अटल व्योम llc_station_rcv(काष्ठा sk_buff *skb)
अणु
	अगर (llc_stat_ev_rx_null_dsap_xid_c(skb))
		llc_station_ac_send_xid_r(skb);
	अन्यथा अगर (llc_stat_ev_rx_null_dsap_test_c(skb))
		llc_station_ac_send_test_r(skb);
	kमुक्त_skb(skb);
पूर्ण

व्योम __init llc_station_init(व्योम)
अणु
	llc_set_station_handler(llc_station_rcv);
पूर्ण

व्योम llc_station_निकास(व्योम)
अणु
	llc_set_station_handler(शून्य);
पूर्ण
