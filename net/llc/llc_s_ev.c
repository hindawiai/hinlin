<शैली गुरु>
/*
 * llc_s_ev.c - Defines SAP component events
 *
 * The followed event functions are SAP component events which are described
 * in 802.2 LLC protocol standard करोcument.
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
#समावेश <linux/socket.h>
#समावेश <net/sock.h>
#समावेश <net/llc_अगर.h>
#समावेश <net/llc_s_ev.h>
#समावेश <net/llc_pdu.h>

पूर्णांक llc_sap_ev_activation_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_SIMPLE &&
	       ev->prim_type == LLC_SAP_EV_ACTIVATION_REQ ? 0 : 1;
पूर्ण

पूर्णांक llc_sap_ev_rx_ui(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_CMD(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_CMD(pdu) == LLC_1_PDU_CMD_UI ? 0 : 1;
पूर्ण

पूर्णांक llc_sap_ev_unitdata_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_PRIM &&
	       ev->prim == LLC_DATAUNIT_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;

पूर्ण

पूर्णांक llc_sap_ev_xid_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_PRIM &&
	       ev->prim == LLC_XID_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
पूर्ण

पूर्णांक llc_sap_ev_rx_xid_c(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_CMD(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_CMD(pdu) == LLC_1_PDU_CMD_XID ? 0 : 1;
पूर्ण

पूर्णांक llc_sap_ev_rx_xid_r(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_RSP(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_RSP(pdu) == LLC_1_PDU_CMD_XID ? 0 : 1;
पूर्ण

पूर्णांक llc_sap_ev_test_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_PRIM &&
	       ev->prim == LLC_TEST_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
पूर्ण

पूर्णांक llc_sap_ev_rx_test_c(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_CMD(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_CMD(pdu) == LLC_1_PDU_CMD_TEST ? 0 : 1;
पूर्ण

पूर्णांक llc_sap_ev_rx_test_r(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_RSP(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_RSP(pdu) == LLC_1_PDU_CMD_TEST ? 0 : 1;
पूर्ण

पूर्णांक llc_sap_ev_deactivation_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sap_state_ev *ev = llc_sap_ev(skb);

	वापस ev->type == LLC_SAP_EV_TYPE_SIMPLE &&
	       ev->prim_type == LLC_SAP_EV_DEACTIVATION_REQ ? 0 : 1;
पूर्ण
