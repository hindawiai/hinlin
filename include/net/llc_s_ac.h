<शैली गुरु>
#अगर_अघोषित LLC_S_AC_H
#घोषणा LLC_S_AC_H
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
/* SAP component actions */
#घोषणा SAP_ACT_UNITDATA_IND	1
#घोषणा SAP_ACT_SEND_UI		2
#घोषणा SAP_ACT_SEND_XID_C	3
#घोषणा SAP_ACT_SEND_XID_R	4
#घोषणा SAP_ACT_SEND_TEST_C	5
#घोषणा SAP_ACT_SEND_TEST_R	6
#घोषणा SAP_ACT_REPORT_STATUS	7
#घोषणा SAP_ACT_XID_IND		8
#घोषणा SAP_ACT_TEST_IND	9

/* All action functions must look like this */
प्रकार पूर्णांक (*llc_sap_action_t)(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);

पूर्णांक llc_sap_action_unitdata_ind(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_action_send_ui(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_action_send_xid_c(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_action_send_xid_r(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_action_send_test_c(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_action_send_test_r(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_action_report_status(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_action_xid_ind(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
पूर्णांक llc_sap_action_test_ind(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
#पूर्ण_अगर /* LLC_S_AC_H */
