<शैली गुरु>
#अगर_अघोषित LLC_SAP_H
#घोषणा LLC_SAP_H

#समावेश <यंत्र/types.h>

/*
 * Copyright (c) 1997 by Procom Technology,Inc.
 * 		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
काष्ठा llc_sap;
काष्ठा net_device;
काष्ठा sk_buff;
काष्ठा sock;

व्योम llc_sap_rtn_pdu(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
व्योम llc_save_primitive(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			अचिन्हित अक्षर prim);
काष्ठा sk_buff *llc_alloc_frame(काष्ठा sock *sk, काष्ठा net_device *dev,
				u8 type, u32 data_size);

व्योम llc_build_and_send_test_pkt(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb,
				 अचिन्हित अक्षर *dmac, अचिन्हित अक्षर dsap);
व्योम llc_build_and_send_xid_pkt(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb,
				अचिन्हित अक्षर *dmac, अचिन्हित अक्षर dsap);
#पूर्ण_अगर /* LLC_SAP_H */
