<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  The NFC Controller Interface is the communication protocol between an
 *  NFC Controller (NFCC) and a Device Host (DH).
 *
 *  Copyright (C) 2011 Texas Instruments, Inc.
 *  Copyright (C) 2014 Marvell International Ltd.
 *
 *  Written by Ilan Elias <ilane@ti.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt, __func__

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <linux/skbuff.h>

#समावेश "../nfc.h"
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश <linux/nfc.h>

/* Complete data exchange transaction and क्रमward skb to nfc core */
व्योम nci_data_exchange_complete(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb,
				__u8 conn_id, पूर्णांक err)
अणु
	काष्ठा nci_conn_info    *conn_info;
	data_exchange_cb_t cb;
	व्योम *cb_context;

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	अगर (!conn_info) अणु
		kमुक्त_skb(skb);
		जाओ निकास;
	पूर्ण

	cb = conn_info->data_exchange_cb;
	cb_context = conn_info->data_exchange_cb_context;

	pr_debug("len %d, err %d\n", skb ? skb->len : 0, err);

	/* data exchange is complete, stop the data समयr */
	del_समयr_sync(&ndev->data_समयr);
	clear_bit(NCI_DATA_EXCHANGE_TO, &ndev->flags);

	अगर (cb) अणु
		/* क्रमward skb to nfc core */
		cb(cb_context, skb, err);
	पूर्ण अन्यथा अगर (skb) अणु
		pr_err("no rx callback, dropping rx data...\n");

		/* no रुकोing callback, मुक्त skb */
		kमुक्त_skb(skb);
	पूर्ण

निकास:
	clear_bit(NCI_DATA_EXCHANGE, &ndev->flags);
पूर्ण

/* ----------------- NCI TX Data ----------------- */

अटल अंतरभूत व्योम nci_push_data_hdr(काष्ठा nci_dev *ndev,
				     __u8 conn_id,
				     काष्ठा sk_buff *skb,
				     __u8 pbf)
अणु
	काष्ठा nci_data_hdr *hdr;
	पूर्णांक plen = skb->len;

	hdr = skb_push(skb, NCI_DATA_HDR_SIZE);
	hdr->conn_id = conn_id;
	hdr->rfu = 0;
	hdr->plen = plen;

	nci_mt_set((__u8 *)hdr, NCI_MT_DATA_PKT);
	nci_pbf_set((__u8 *)hdr, pbf);
पूर्ण

पूर्णांक nci_conn_max_data_pkt_payload_size(काष्ठा nci_dev *ndev, __u8 conn_id)
अणु
	काष्ठा nci_conn_info *conn_info;

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	अगर (!conn_info)
		वापस -EPROTO;

	वापस conn_info->max_pkt_payload_len;
पूर्ण
EXPORT_SYMBOL(nci_conn_max_data_pkt_payload_size);

अटल पूर्णांक nci_queue_tx_data_frags(काष्ठा nci_dev *ndev,
				   __u8 conn_id,
				   काष्ठा sk_buff *skb) अणु
	काष्ठा nci_conn_info    *conn_info;
	पूर्णांक total_len = skb->len;
	अचिन्हित अक्षर *data = skb->data;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff_head frags_q;
	काष्ठा sk_buff *skb_frag;
	पूर्णांक frag_len;
	पूर्णांक rc = 0;

	pr_debug("conn_id 0x%x, total_len %d\n", conn_id, total_len);

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	अगर (!conn_info) अणु
		rc = -EPROTO;
		जाओ निकास;
	पूर्ण

	__skb_queue_head_init(&frags_q);

	जबतक (total_len) अणु
		frag_len =
			min_t(पूर्णांक, total_len, conn_info->max_pkt_payload_len);

		skb_frag = nci_skb_alloc(ndev,
					 (NCI_DATA_HDR_SIZE + frag_len),
					 GFP_KERNEL);
		अगर (skb_frag == शून्य) अणु
			rc = -ENOMEM;
			जाओ मुक्त_निकास;
		पूर्ण
		skb_reserve(skb_frag, NCI_DATA_HDR_SIZE);

		/* first, copy the data */
		skb_put_data(skb_frag, data, frag_len);

		/* second, set the header */
		nci_push_data_hdr(ndev, conn_id, skb_frag,
				  ((total_len == frag_len) ?
				   (NCI_PBF_LAST) : (NCI_PBF_CONT)));

		__skb_queue_tail(&frags_q, skb_frag);

		data += frag_len;
		total_len -= frag_len;

		pr_debug("frag_len %d, remaining total_len %d\n",
			 frag_len, total_len);
	पूर्ण

	/* queue all fragments atomically */
	spin_lock_irqsave(&ndev->tx_q.lock, flags);

	जबतक ((skb_frag = __skb_dequeue(&frags_q)) != शून्य)
		__skb_queue_tail(&ndev->tx_q, skb_frag);

	spin_unlock_irqrestore(&ndev->tx_q.lock, flags);

	/* मुक्त the original skb */
	kमुक्त_skb(skb);

	जाओ निकास;

मुक्त_निकास:
	जबतक ((skb_frag = __skb_dequeue(&frags_q)) != शून्य)
		kमुक्त_skb(skb_frag);

निकास:
	वापस rc;
पूर्ण

/* Send NCI data */
पूर्णांक nci_send_data(काष्ठा nci_dev *ndev, __u8 conn_id, काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_conn_info    *conn_info;
	पूर्णांक rc = 0;

	pr_debug("conn_id 0x%x, plen %d\n", conn_id, skb->len);

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	अगर (!conn_info) अणु
		rc = -EPROTO;
		जाओ मुक्त_निकास;
	पूर्ण

	/* check अगर the packet need to be fragmented */
	अगर (skb->len <= conn_info->max_pkt_payload_len) अणु
		/* no need to fragment packet */
		nci_push_data_hdr(ndev, conn_id, skb, NCI_PBF_LAST);

		skb_queue_tail(&ndev->tx_q, skb);
	पूर्ण अन्यथा अणु
		/* fragment packet and queue the fragments */
		rc = nci_queue_tx_data_frags(ndev, conn_id, skb);
		अगर (rc) अणु
			pr_err("failed to fragment tx data packet\n");
			जाओ मुक्त_निकास;
		पूर्ण
	पूर्ण

	ndev->cur_conn_id = conn_id;
	queue_work(ndev->tx_wq, &ndev->tx_work);

	जाओ निकास;

मुक्त_निकास:
	kमुक्त_skb(skb);

निकास:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(nci_send_data);

/* ----------------- NCI RX Data ----------------- */

अटल व्योम nci_add_rx_data_frag(काष्ठा nci_dev *ndev,
				 काष्ठा sk_buff *skb,
				 __u8 pbf, __u8 conn_id, __u8 status)
अणु
	पूर्णांक reassembly_len;
	पूर्णांक err = 0;

	अगर (status) अणु
		err = status;
		जाओ निकास;
	पूर्ण

	अगर (ndev->rx_data_reassembly) अणु
		reassembly_len = ndev->rx_data_reassembly->len;

		/* first, make enough room क्रम the alपढ़ोy accumulated data */
		अगर (skb_cow_head(skb, reassembly_len)) अणु
			pr_err("error adding room for accumulated rx data\n");

			kमुक्त_skb(skb);
			skb = शून्य;

			kमुक्त_skb(ndev->rx_data_reassembly);
			ndev->rx_data_reassembly = शून्य;

			err = -ENOMEM;
			जाओ निकास;
		पूर्ण

		/* second, combine the two fragments */
		स_नकल(skb_push(skb, reassembly_len),
		       ndev->rx_data_reassembly->data,
		       reassembly_len);

		/* third, मुक्त old reassembly */
		kमुक्त_skb(ndev->rx_data_reassembly);
		ndev->rx_data_reassembly = शून्य;
	पूर्ण

	अगर (pbf == NCI_PBF_CONT) अणु
		/* need to रुको क्रम next fragment, store skb and निकास */
		ndev->rx_data_reassembly = skb;
		वापस;
	पूर्ण

निकास:
	अगर (ndev->nfc_dev->rf_mode == NFC_RF_TARGET) अणु
		/* Data received in Target mode, क्रमward to nfc core */
		err = nfc_पंचांग_data_received(ndev->nfc_dev, skb);
		अगर (err)
			pr_err("unable to handle received data\n");
	पूर्ण अन्यथा अणु
		nci_data_exchange_complete(ndev, skb, conn_id, err);
	पूर्ण
पूर्ण

/* Rx Data packet */
व्योम nci_rx_data_packet(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	__u8 pbf = nci_pbf(skb->data);
	__u8 status = 0;
	__u8 conn_id = nci_conn_id(skb->data);
	काष्ठा nci_conn_info    *conn_info;

	pr_debug("len %d\n", skb->len);

	pr_debug("NCI RX: MT=data, PBF=%d, conn_id=%d, plen=%d\n",
		 nci_pbf(skb->data),
		 nci_conn_id(skb->data),
		 nci_plen(skb->data));

	conn_info = nci_get_conn_info_by_conn_id(ndev, nci_conn_id(skb->data));
	अगर (!conn_info)
		वापस;

	/* strip the nci data header */
	skb_pull(skb, NCI_DATA_HDR_SIZE);

	अगर (ndev->target_active_prot == NFC_PROTO_MIFARE ||
	    ndev->target_active_prot == NFC_PROTO_JEWEL ||
	    ndev->target_active_prot == NFC_PROTO_FELICA ||
	    ndev->target_active_prot == NFC_PROTO_ISO15693) अणु
		/* frame I/F => हटाओ the status byte */
		pr_debug("frame I/F => remove the status byte\n");
		status = skb->data[skb->len - 1];
		skb_trim(skb, (skb->len - 1));
	पूर्ण

	nci_add_rx_data_frag(ndev, skb, pbf, conn_id, nci_to_त्रुटि_सं(status));
पूर्ण
