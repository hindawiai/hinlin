<शैली गुरु>
#अगर_अघोषित LLC_S_EV_H
#घोषणा LLC_S_EV_H
/*
 * Copyright (c) 1997 by Procom Technology,Inc.
 * 		 2001 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */

#समावेश <linux/skbuff.h>

/* Defines SAP component events */
/* Types of events (possible values in 'ev->type') */
#घोषणा LLC_SAP_EV_TYPE_SIMPLE		1
#घोषणा LLC_SAP_EV_TYPE_CONDITION	2
#घोषणा LLC_SAP_EV_TYPE_PRIM		3
#घोषणा LLC_SAP_EV_TYPE_PDU		4   /* command/response PDU */
#घोषणा LLC_SAP_EV_TYPE_ACK_TMR		5
#घोषणा LLC_SAP_EV_TYPE_RPT_STATUS	6

#घोषणा LLC_SAP_EV_ACTIVATION_REQ	 1
#घोषणा LLC_SAP_EV_RX_UI		 2
#घोषणा LLC_SAP_EV_UNITDATA_REQ		 3
#घोषणा LLC_SAP_EV_XID_REQ		 4
#घोषणा LLC_SAP_EV_RX_XID_C		 5
#घोषणा LLC_SAP_EV_RX_XID_R		 6
#घोषणा LLC_SAP_EV_TEST_REQ		 7
#घोषणा LLC_SAP_EV_RX_TEST_C		 8
#घोषणा LLC_SAP_EV_RX_TEST_R		 9
#घोषणा LLC_SAP_EV_DEACTIVATION_REQ	10

काष्ठा llc_sap_state_ev अणु
	u8		prim;
	u8		prim_type;
	u8		type;
	u8		reason;
	u8		ind_cfm_flag;
	काष्ठा llc_addr saddr;
	काष्ठा llc_addr daddr;
पूर्ण;

अटल __अंतरभूत__ काष्ठा llc_sap_state_ev *llc_sap_ev(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा llc_sap_state_ev *)skb->cb;
पूर्ण

काष्ठा llc_sap;

प्रकार पूर्णांक (*llc_sap_ev_t)(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);

पूर्णांक llc_sap_ev_activation_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_ev_rx_ui(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_ev_unitdata_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_ev_xid_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_ev_rx_xid_c(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_ev_rx_xid_r(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_ev_test_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_ev_rx_test_c(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_ev_rx_test_r(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_ev_deactivation_req(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
#पूर्ण_अगर /* LLC_S_EV_H */
