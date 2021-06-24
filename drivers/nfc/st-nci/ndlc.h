<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * NCI based Driver क्रम STMicroelectronics NFC Chip
 *
 * Copyright (C) 2014-2015  STMicroelectronics SAS. All rights reserved.
 */

#अगर_अघोषित __LOCAL_NDLC_H_
#घोषणा __LOCAL_NDLC_H_

#समावेश <linux/skbuff.h>
#समावेश <net/nfc/nfc.h>

काष्ठा st_nci_se_status;

/* Low Level Transport description */
काष्ठा llt_ndlc अणु
	काष्ठा nci_dev *ndev;
	काष्ठा nfc_phy_ops *ops;
	व्योम *phy_id;

	काष्ठा समयr_list t1_समयr;
	bool t1_active;

	काष्ठा समयr_list t2_समयr;
	bool t2_active;

	काष्ठा sk_buff_head rcv_q;
	काष्ठा sk_buff_head send_q;
	काष्ठा sk_buff_head ack_pending_q;

	काष्ठा work_काष्ठा sm_work;

	काष्ठा device *dev;

	/*
	 * < 0 अगर hardware error occurred
	 * and prevents normal operation.
	 */
	पूर्णांक hard_fault;
	पूर्णांक घातered;
पूर्ण;

पूर्णांक ndlc_खोलो(काष्ठा llt_ndlc *ndlc);
व्योम ndlc_बंद(काष्ठा llt_ndlc *ndlc);
पूर्णांक ndlc_send(काष्ठा llt_ndlc *ndlc, काष्ठा sk_buff *skb);
व्योम ndlc_recv(काष्ठा llt_ndlc *ndlc, काष्ठा sk_buff *skb);
पूर्णांक ndlc_probe(व्योम *phy_id, काष्ठा nfc_phy_ops *phy_ops, काष्ठा device *dev,
	       पूर्णांक phy_headroom, पूर्णांक phy_tailroom, काष्ठा llt_ndlc **ndlc_id,
	       काष्ठा st_nci_se_status *se_status);
व्योम ndlc_हटाओ(काष्ठा llt_ndlc *ndlc);
#पूर्ण_अगर /* __LOCAL_NDLC_H__ */
