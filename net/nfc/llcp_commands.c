<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "llcp: %s: " fmt, __func__

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nfc.h>

#समावेश <net/nfc/nfc.h>

#समावेश "nfc.h"
#समावेश "llcp.h"

अटल u8 llcp_tlv_length[LLCP_TLV_MAX] = अणु
	0,
	1, /* VERSION */
	2, /* MIUX */
	2, /* WKS */
	1, /* LTO */
	1, /* RW */
	0, /* SN */
	1, /* OPT */
	0, /* SDREQ */
	2, /* SDRES */

पूर्ण;

अटल u8 llcp_tlv8(u8 *tlv, u8 type)
अणु
	अगर (tlv[0] != type || tlv[1] != llcp_tlv_length[tlv[0]])
		वापस 0;

	वापस tlv[2];
पूर्ण

अटल u16 llcp_tlv16(u8 *tlv, u8 type)
अणु
	अगर (tlv[0] != type || tlv[1] != llcp_tlv_length[tlv[0]])
		वापस 0;

	वापस be16_to_cpu(*((__be16 *)(tlv + 2)));
पूर्ण


अटल u8 llcp_tlv_version(u8 *tlv)
अणु
	वापस llcp_tlv8(tlv, LLCP_TLV_VERSION);
पूर्ण

अटल u16 llcp_tlv_miux(u8 *tlv)
अणु
	वापस llcp_tlv16(tlv, LLCP_TLV_MIUX) & 0x7ff;
पूर्ण

अटल u16 llcp_tlv_wks(u8 *tlv)
अणु
	वापस llcp_tlv16(tlv, LLCP_TLV_WKS);
पूर्ण

अटल u16 llcp_tlv_lto(u8 *tlv)
अणु
	वापस llcp_tlv8(tlv, LLCP_TLV_LTO);
पूर्ण

अटल u8 llcp_tlv_opt(u8 *tlv)
अणु
	वापस llcp_tlv8(tlv, LLCP_TLV_OPT);
पूर्ण

अटल u8 llcp_tlv_rw(u8 *tlv)
अणु
	वापस llcp_tlv8(tlv, LLCP_TLV_RW) & 0xf;
पूर्ण

u8 *nfc_llcp_build_tlv(u8 type, u8 *value, u8 value_length, u8 *tlv_length)
अणु
	u8 *tlv, length;

	pr_debug("type %d\n", type);

	अगर (type >= LLCP_TLV_MAX)
		वापस शून्य;

	length = llcp_tlv_length[type];
	अगर (length == 0 && value_length == 0)
		वापस शून्य;
	अन्यथा अगर (length == 0)
		length = value_length;

	*tlv_length = 2 + length;
	tlv = kzalloc(2 + length, GFP_KERNEL);
	अगर (tlv == शून्य)
		वापस tlv;

	tlv[0] = type;
	tlv[1] = length;
	स_नकल(tlv + 2, value, length);

	वापस tlv;
पूर्ण

काष्ठा nfc_llcp_sdp_tlv *nfc_llcp_build_sdres_tlv(u8 tid, u8 sap)
अणु
	काष्ठा nfc_llcp_sdp_tlv *sdres;
	u8 value[2];

	sdres = kzalloc(माप(काष्ठा nfc_llcp_sdp_tlv), GFP_KERNEL);
	अगर (sdres == शून्य)
		वापस शून्य;

	value[0] = tid;
	value[1] = sap;

	sdres->tlv = nfc_llcp_build_tlv(LLCP_TLV_SDRES, value, 2,
					&sdres->tlv_len);
	अगर (sdres->tlv == शून्य) अणु
		kमुक्त(sdres);
		वापस शून्य;
	पूर्ण

	sdres->tid = tid;
	sdres->sap = sap;

	INIT_HLIST_NODE(&sdres->node);

	वापस sdres;
पूर्ण

काष्ठा nfc_llcp_sdp_tlv *nfc_llcp_build_sdreq_tlv(u8 tid, अक्षर *uri,
						  माप_प्रकार uri_len)
अणु
	काष्ठा nfc_llcp_sdp_tlv *sdreq;

	pr_debug("uri: %s, len: %zu\n", uri, uri_len);

	/* sdreq->tlv_len is u8, takes uri_len, + 3 क्रम header, + 1 क्रम शून्य */
	अगर (WARN_ON_ONCE(uri_len > U8_MAX - 4))
		वापस शून्य;

	sdreq = kzalloc(माप(काष्ठा nfc_llcp_sdp_tlv), GFP_KERNEL);
	अगर (sdreq == शून्य)
		वापस शून्य;

	sdreq->tlv_len = uri_len + 3;

	अगर (uri[uri_len - 1] == 0)
		sdreq->tlv_len--;

	sdreq->tlv = kzalloc(sdreq->tlv_len + 1, GFP_KERNEL);
	अगर (sdreq->tlv == शून्य) अणु
		kमुक्त(sdreq);
		वापस शून्य;
	पूर्ण

	sdreq->tlv[0] = LLCP_TLV_SDREQ;
	sdreq->tlv[1] = sdreq->tlv_len - 2;
	sdreq->tlv[2] = tid;

	sdreq->tid = tid;
	sdreq->uri = sdreq->tlv + 3;
	स_नकल(sdreq->uri, uri, uri_len);

	sdreq->समय = jअगरfies;

	INIT_HLIST_NODE(&sdreq->node);

	वापस sdreq;
पूर्ण

व्योम nfc_llcp_मुक्त_sdp_tlv(काष्ठा nfc_llcp_sdp_tlv *sdp)
अणु
	kमुक्त(sdp->tlv);
	kमुक्त(sdp);
पूर्ण

व्योम nfc_llcp_मुक्त_sdp_tlv_list(काष्ठा hlist_head *head)
अणु
	काष्ठा nfc_llcp_sdp_tlv *sdp;
	काष्ठा hlist_node *n;

	hlist_क्रम_each_entry_safe(sdp, n, head, node) अणु
		hlist_del(&sdp->node);

		nfc_llcp_मुक्त_sdp_tlv(sdp);
	पूर्ण
पूर्ण

पूर्णांक nfc_llcp_parse_gb_tlv(काष्ठा nfc_llcp_local *local,
			  u8 *tlv_array, u16 tlv_array_len)
अणु
	u8 *tlv = tlv_array, type, length, offset = 0;

	pr_debug("TLV array length %d\n", tlv_array_len);

	अगर (local == शून्य)
		वापस -ENODEV;

	जबतक (offset < tlv_array_len) अणु
		type = tlv[0];
		length = tlv[1];

		pr_debug("type 0x%x length %d\n", type, length);

		चयन (type) अणु
		हाल LLCP_TLV_VERSION:
			local->remote_version = llcp_tlv_version(tlv);
			अवरोध;
		हाल LLCP_TLV_MIUX:
			local->remote_miu = llcp_tlv_miux(tlv) + 128;
			अवरोध;
		हाल LLCP_TLV_WKS:
			local->remote_wks = llcp_tlv_wks(tlv);
			अवरोध;
		हाल LLCP_TLV_LTO:
			local->remote_lto = llcp_tlv_lto(tlv) * 10;
			अवरोध;
		हाल LLCP_TLV_OPT:
			local->remote_opt = llcp_tlv_opt(tlv);
			अवरोध;
		शेष:
			pr_err("Invalid gt tlv value 0x%x\n", type);
			अवरोध;
		पूर्ण

		offset += length + 2;
		tlv += length + 2;
	पूर्ण

	pr_debug("version 0x%x miu %d lto %d opt 0x%x wks 0x%x\n",
		 local->remote_version, local->remote_miu,
		 local->remote_lto, local->remote_opt,
		 local->remote_wks);

	वापस 0;
पूर्ण

पूर्णांक nfc_llcp_parse_connection_tlv(काष्ठा nfc_llcp_sock *sock,
				  u8 *tlv_array, u16 tlv_array_len)
अणु
	u8 *tlv = tlv_array, type, length, offset = 0;

	pr_debug("TLV array length %d\n", tlv_array_len);

	अगर (sock == शून्य)
		वापस -ENOTCONN;

	जबतक (offset < tlv_array_len) अणु
		type = tlv[0];
		length = tlv[1];

		pr_debug("type 0x%x length %d\n", type, length);

		चयन (type) अणु
		हाल LLCP_TLV_MIUX:
			sock->remote_miu = llcp_tlv_miux(tlv) + 128;
			अवरोध;
		हाल LLCP_TLV_RW:
			sock->remote_rw = llcp_tlv_rw(tlv);
			अवरोध;
		हाल LLCP_TLV_SN:
			अवरोध;
		शेष:
			pr_err("Invalid gt tlv value 0x%x\n", type);
			अवरोध;
		पूर्ण

		offset += length + 2;
		tlv += length + 2;
	पूर्ण

	pr_debug("sock %p rw %d miu %d\n", sock,
		 sock->remote_rw, sock->remote_miu);

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *llcp_add_header(काष्ठा sk_buff *pdu,
				       u8 dsap, u8 ssap, u8 ptype)
अणु
	u8 header[2];

	pr_debug("ptype 0x%x dsap 0x%x ssap 0x%x\n", ptype, dsap, ssap);

	header[0] = (u8)((dsap << 2) | (ptype >> 2));
	header[1] = (u8)((ptype << 6) | ssap);

	pr_debug("header 0x%x 0x%x\n", header[0], header[1]);

	skb_put_data(pdu, header, LLCP_HEADER_SIZE);

	वापस pdu;
पूर्ण

अटल काष्ठा sk_buff *llcp_add_tlv(काष्ठा sk_buff *pdu, u8 *tlv,
				    u8 tlv_length)
अणु
	/* XXX Add an skb length check */

	अगर (tlv == शून्य)
		वापस शून्य;

	skb_put_data(pdu, tlv, tlv_length);

	वापस pdu;
पूर्ण

अटल काष्ठा sk_buff *llcp_allocate_pdu(काष्ठा nfc_llcp_sock *sock,
					 u8 cmd, u16 size)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (sock->ssap == 0)
		वापस शून्य;

	skb = nfc_alloc_send_skb(sock->dev, &sock->sk, MSG_DONTWAIT,
				 size + LLCP_HEADER_SIZE, &err);
	अगर (skb == शून्य) अणु
		pr_err("Could not allocate PDU\n");
		वापस शून्य;
	पूर्ण

	skb = llcp_add_header(skb, sock->dsap, sock->ssap, cmd);

	वापस skb;
पूर्ण

पूर्णांक nfc_llcp_send_disconnect(काष्ठा nfc_llcp_sock *sock)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nfc_dev *dev;
	काष्ठा nfc_llcp_local *local;

	pr_debug("Sending DISC\n");

	local = sock->local;
	अगर (local == शून्य)
		वापस -ENODEV;

	dev = sock->dev;
	अगर (dev == शून्य)
		वापस -ENODEV;

	skb = llcp_allocate_pdu(sock, LLCP_PDU_DISC, 0);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	skb_queue_tail(&local->tx_queue, skb);

	वापस 0;
पूर्ण

पूर्णांक nfc_llcp_send_symm(काष्ठा nfc_dev *dev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nfc_llcp_local *local;
	u16 size = 0;

	pr_debug("Sending SYMM\n");

	local = nfc_llcp_find_local(dev);
	अगर (local == शून्य)
		वापस -ENODEV;

	size += LLCP_HEADER_SIZE;
	size += dev->tx_headroom + dev->tx_tailroom + NFC_HEADER_SIZE;

	skb = alloc_skb(size, GFP_KERNEL);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	skb_reserve(skb, dev->tx_headroom + NFC_HEADER_SIZE);

	skb = llcp_add_header(skb, 0, 0, LLCP_PDU_SYMM);

	__net_बारtamp(skb);

	nfc_llcp_send_to_raw_sock(local, skb, NFC_सूचीECTION_TX);

	वापस nfc_data_exchange(dev, local->target_idx, skb,
				 nfc_llcp_recv, local);
पूर्ण

पूर्णांक nfc_llcp_send_connect(काष्ठा nfc_llcp_sock *sock)
अणु
	काष्ठा nfc_llcp_local *local;
	काष्ठा sk_buff *skb;
	u8 *service_name_tlv = शून्य, service_name_tlv_length;
	u8 *miux_tlv = शून्य, miux_tlv_length;
	u8 *rw_tlv = शून्य, rw_tlv_length, rw;
	पूर्णांक err;
	u16 size = 0;
	__be16 miux;

	pr_debug("Sending CONNECT\n");

	local = sock->local;
	अगर (local == शून्य)
		वापस -ENODEV;

	अगर (sock->service_name != शून्य) अणु
		service_name_tlv = nfc_llcp_build_tlv(LLCP_TLV_SN,
						      sock->service_name,
						      sock->service_name_len,
						      &service_name_tlv_length);
		अगर (!service_name_tlv) अणु
			err = -ENOMEM;
			जाओ error_tlv;
		पूर्ण
		size += service_name_tlv_length;
	पूर्ण

	/* If the socket parameters are not set, use the local ones */
	miux = be16_to_cpu(sock->miux) > LLCP_MAX_MIUX ?
		local->miux : sock->miux;
	rw = sock->rw > LLCP_MAX_RW ? local->rw : sock->rw;

	miux_tlv = nfc_llcp_build_tlv(LLCP_TLV_MIUX, (u8 *)&miux, 0,
				      &miux_tlv_length);
	अगर (!miux_tlv) अणु
		err = -ENOMEM;
		जाओ error_tlv;
	पूर्ण
	size += miux_tlv_length;

	rw_tlv = nfc_llcp_build_tlv(LLCP_TLV_RW, &rw, 0, &rw_tlv_length);
	अगर (!rw_tlv) अणु
		err = -ENOMEM;
		जाओ error_tlv;
	पूर्ण
	size += rw_tlv_length;

	pr_debug("SKB size %d SN length %zu\n", size, sock->service_name_len);

	skb = llcp_allocate_pdu(sock, LLCP_PDU_CONNECT, size);
	अगर (skb == शून्य) अणु
		err = -ENOMEM;
		जाओ error_tlv;
	पूर्ण

	llcp_add_tlv(skb, service_name_tlv, service_name_tlv_length);
	llcp_add_tlv(skb, miux_tlv, miux_tlv_length);
	llcp_add_tlv(skb, rw_tlv, rw_tlv_length);

	skb_queue_tail(&local->tx_queue, skb);

	err = 0;

error_tlv:
	अगर (err)
		pr_err("error %d\n", err);

	kमुक्त(service_name_tlv);
	kमुक्त(miux_tlv);
	kमुक्त(rw_tlv);

	वापस err;
पूर्ण

पूर्णांक nfc_llcp_send_cc(काष्ठा nfc_llcp_sock *sock)
अणु
	काष्ठा nfc_llcp_local *local;
	काष्ठा sk_buff *skb;
	u8 *miux_tlv = शून्य, miux_tlv_length;
	u8 *rw_tlv = शून्य, rw_tlv_length, rw;
	पूर्णांक err;
	u16 size = 0;
	__be16 miux;

	pr_debug("Sending CC\n");

	local = sock->local;
	अगर (local == शून्य)
		वापस -ENODEV;

	/* If the socket parameters are not set, use the local ones */
	miux = be16_to_cpu(sock->miux) > LLCP_MAX_MIUX ?
		local->miux : sock->miux;
	rw = sock->rw > LLCP_MAX_RW ? local->rw : sock->rw;

	miux_tlv = nfc_llcp_build_tlv(LLCP_TLV_MIUX, (u8 *)&miux, 0,
				      &miux_tlv_length);
	अगर (!miux_tlv) अणु
		err = -ENOMEM;
		जाओ error_tlv;
	पूर्ण
	size += miux_tlv_length;

	rw_tlv = nfc_llcp_build_tlv(LLCP_TLV_RW, &rw, 0, &rw_tlv_length);
	अगर (!rw_tlv) अणु
		err = -ENOMEM;
		जाओ error_tlv;
	पूर्ण
	size += rw_tlv_length;

	skb = llcp_allocate_pdu(sock, LLCP_PDU_CC, size);
	अगर (skb == शून्य) अणु
		err = -ENOMEM;
		जाओ error_tlv;
	पूर्ण

	llcp_add_tlv(skb, miux_tlv, miux_tlv_length);
	llcp_add_tlv(skb, rw_tlv, rw_tlv_length);

	skb_queue_tail(&local->tx_queue, skb);

	err = 0;

error_tlv:
	अगर (err)
		pr_err("error %d\n", err);

	kमुक्त(miux_tlv);
	kमुक्त(rw_tlv);

	वापस err;
पूर्ण

अटल काष्ठा sk_buff *nfc_llcp_allocate_snl(काष्ठा nfc_llcp_local *local,
					     माप_प्रकार tlv_length)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nfc_dev *dev;
	u16 size = 0;

	अगर (local == शून्य)
		वापस ERR_PTR(-ENODEV);

	dev = local->dev;
	अगर (dev == शून्य)
		वापस ERR_PTR(-ENODEV);

	size += LLCP_HEADER_SIZE;
	size += dev->tx_headroom + dev->tx_tailroom + NFC_HEADER_SIZE;
	size += tlv_length;

	skb = alloc_skb(size, GFP_KERNEL);
	अगर (skb == शून्य)
		वापस ERR_PTR(-ENOMEM);

	skb_reserve(skb, dev->tx_headroom + NFC_HEADER_SIZE);

	skb = llcp_add_header(skb, LLCP_SAP_SDP, LLCP_SAP_SDP, LLCP_PDU_SNL);

	वापस skb;
पूर्ण

पूर्णांक nfc_llcp_send_snl_sdres(काष्ठा nfc_llcp_local *local,
			    काष्ठा hlist_head *tlv_list, माप_प्रकार tlvs_len)
अणु
	काष्ठा nfc_llcp_sdp_tlv *sdp;
	काष्ठा hlist_node *n;
	काष्ठा sk_buff *skb;

	skb = nfc_llcp_allocate_snl(local, tlvs_len);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	hlist_क्रम_each_entry_safe(sdp, n, tlv_list, node) अणु
		skb_put_data(skb, sdp->tlv, sdp->tlv_len);

		hlist_del(&sdp->node);

		nfc_llcp_मुक्त_sdp_tlv(sdp);
	पूर्ण

	skb_queue_tail(&local->tx_queue, skb);

	वापस 0;
पूर्ण

पूर्णांक nfc_llcp_send_snl_sdreq(काष्ठा nfc_llcp_local *local,
			    काष्ठा hlist_head *tlv_list, माप_प्रकार tlvs_len)
अणु
	काष्ठा nfc_llcp_sdp_tlv *sdreq;
	काष्ठा hlist_node *n;
	काष्ठा sk_buff *skb;

	skb = nfc_llcp_allocate_snl(local, tlvs_len);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mutex_lock(&local->sdreq_lock);

	अगर (hlist_empty(&local->pending_sdreqs))
		mod_समयr(&local->sdreq_समयr,
			  jअगरfies + msecs_to_jअगरfies(3 * local->remote_lto));

	hlist_क्रम_each_entry_safe(sdreq, n, tlv_list, node) अणु
		pr_debug("tid %d for %s\n", sdreq->tid, sdreq->uri);

		skb_put_data(skb, sdreq->tlv, sdreq->tlv_len);

		hlist_del(&sdreq->node);

		hlist_add_head(&sdreq->node, &local->pending_sdreqs);
	पूर्ण

	mutex_unlock(&local->sdreq_lock);

	skb_queue_tail(&local->tx_queue, skb);

	वापस 0;
पूर्ण

पूर्णांक nfc_llcp_send_dm(काष्ठा nfc_llcp_local *local, u8 ssap, u8 dsap, u8 reason)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nfc_dev *dev;
	u16 size = 1; /* Reason code */

	pr_debug("Sending DM reason 0x%x\n", reason);

	अगर (local == शून्य)
		वापस -ENODEV;

	dev = local->dev;
	अगर (dev == शून्य)
		वापस -ENODEV;

	size += LLCP_HEADER_SIZE;
	size += dev->tx_headroom + dev->tx_tailroom + NFC_HEADER_SIZE;

	skb = alloc_skb(size, GFP_KERNEL);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	skb_reserve(skb, dev->tx_headroom + NFC_HEADER_SIZE);

	skb = llcp_add_header(skb, dsap, ssap, LLCP_PDU_DM);

	skb_put_data(skb, &reason, 1);

	skb_queue_head(&local->tx_queue, skb);

	वापस 0;
पूर्ण

पूर्णांक nfc_llcp_send_i_frame(काष्ठा nfc_llcp_sock *sock,
			  काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sk_buff *pdu;
	काष्ठा sock *sk = &sock->sk;
	काष्ठा nfc_llcp_local *local;
	माप_प्रकार frag_len = 0, reमुख्यing_len;
	u8 *msg_data, *msg_ptr;
	u16 remote_miu;

	pr_debug("Send I frame len %zd\n", len);

	local = sock->local;
	अगर (local == शून्य)
		वापस -ENODEV;

	/* Remote is पढ़ोy but has not acknowledged our frames */
	अगर((sock->remote_पढ़ोy &&
	    skb_queue_len(&sock->tx_pending_queue) >= sock->remote_rw &&
	    skb_queue_len(&sock->tx_queue) >= 2 * sock->remote_rw)) अणु
		pr_err("Pending queue is full %d frames\n",
		       skb_queue_len(&sock->tx_pending_queue));
		वापस -ENOBUFS;
	पूर्ण

	/* Remote is not पढ़ोy and we've been queueing enough frames */
	अगर ((!sock->remote_पढ़ोy &&
	     skb_queue_len(&sock->tx_queue) >= 2 * sock->remote_rw)) अणु
		pr_err("Tx queue is full %d frames\n",
		       skb_queue_len(&sock->tx_queue));
		वापस -ENOBUFS;
	पूर्ण

	msg_data = kदो_स्मृति(len, GFP_USER | __GFP_NOWARN);
	अगर (msg_data == शून्य)
		वापस -ENOMEM;

	अगर (स_नकल_from_msg(msg_data, msg, len)) अणु
		kमुक्त(msg_data);
		वापस -EFAULT;
	पूर्ण

	reमुख्यing_len = len;
	msg_ptr = msg_data;

	करो अणु
		remote_miu = sock->remote_miu > LLCP_MAX_MIU ?
				LLCP_DEFAULT_MIU : sock->remote_miu;

		frag_len = min_t(माप_प्रकार, remote_miu, reमुख्यing_len);

		pr_debug("Fragment %zd bytes remaining %zd",
			 frag_len, reमुख्यing_len);

		pdu = llcp_allocate_pdu(sock, LLCP_PDU_I,
					frag_len + LLCP_SEQUENCE_SIZE);
		अगर (pdu == शून्य) अणु
			kमुक्त(msg_data);
			वापस -ENOMEM;
		पूर्ण

		skb_put(pdu, LLCP_SEQUENCE_SIZE);

		अगर (likely(frag_len > 0))
			skb_put_data(pdu, msg_ptr, frag_len);

		skb_queue_tail(&sock->tx_queue, pdu);

		lock_sock(sk);

		nfc_llcp_queue_i_frames(sock);

		release_sock(sk);

		reमुख्यing_len -= frag_len;
		msg_ptr += frag_len;
	पूर्ण जबतक (reमुख्यing_len > 0);

	kमुक्त(msg_data);

	वापस len;
पूर्ण

पूर्णांक nfc_llcp_send_ui_frame(काष्ठा nfc_llcp_sock *sock, u8 ssap, u8 dsap,
			   काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sk_buff *pdu;
	काष्ठा nfc_llcp_local *local;
	माप_प्रकार frag_len = 0, reमुख्यing_len;
	u8 *msg_ptr, *msg_data;
	u16 remote_miu;
	पूर्णांक err;

	pr_debug("Send UI frame len %zd\n", len);

	local = sock->local;
	अगर (local == शून्य)
		वापस -ENODEV;

	msg_data = kदो_स्मृति(len, GFP_USER | __GFP_NOWARN);
	अगर (msg_data == शून्य)
		वापस -ENOMEM;

	अगर (स_नकल_from_msg(msg_data, msg, len)) अणु
		kमुक्त(msg_data);
		वापस -EFAULT;
	पूर्ण

	reमुख्यing_len = len;
	msg_ptr = msg_data;

	करो अणु
		remote_miu = sock->remote_miu > LLCP_MAX_MIU ?
				local->remote_miu : sock->remote_miu;

		frag_len = min_t(माप_प्रकार, remote_miu, reमुख्यing_len);

		pr_debug("Fragment %zd bytes remaining %zd",
			 frag_len, reमुख्यing_len);

		pdu = nfc_alloc_send_skb(sock->dev, &sock->sk, 0,
					 frag_len + LLCP_HEADER_SIZE, &err);
		अगर (pdu == शून्य) अणु
			pr_err("Could not allocate PDU (error=%d)\n", err);
			len -= reमुख्यing_len;
			अगर (len == 0)
				len = err;
			अवरोध;
		पूर्ण

		pdu = llcp_add_header(pdu, dsap, ssap, LLCP_PDU_UI);

		अगर (likely(frag_len > 0))
			skb_put_data(pdu, msg_ptr, frag_len);

		/* No need to check क्रम the peer RW क्रम UI frames */
		skb_queue_tail(&local->tx_queue, pdu);

		reमुख्यing_len -= frag_len;
		msg_ptr += frag_len;
	पूर्ण जबतक (reमुख्यing_len > 0);

	kमुक्त(msg_data);

	वापस len;
पूर्ण

पूर्णांक nfc_llcp_send_rr(काष्ठा nfc_llcp_sock *sock)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nfc_llcp_local *local;

	pr_debug("Send rr nr %d\n", sock->recv_n);

	local = sock->local;
	अगर (local == शून्य)
		वापस -ENODEV;

	skb = llcp_allocate_pdu(sock, LLCP_PDU_RR, LLCP_SEQUENCE_SIZE);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	skb_put(skb, LLCP_SEQUENCE_SIZE);

	skb->data[2] = sock->recv_n;

	skb_queue_head(&local->tx_queue, skb);

	वापस 0;
पूर्ण
